#include "stm32f4xx.h"
#include "BOOT.h"
#include "stdint.h"
#include "string.h"
#include "../MCAL/UART.h"
#include "../Services_layers/debug.h"
#include "../MCAL/CAN.h"
#include "stm32f4xx_crc.h"
#include "stm32f4xx_flash.h"
#include "../Services_layers/Speical_Timer.h"
#include "../Services_layers/Queue.h"
#include "../Services_layers/delay.h"
#include "../Services_layers/Services_layers.h"

#define   CAN_ID   0x25
uint8_t supported_commands[] = {
		BL_FLASH_ERASE,
		BL_MEM_WRITE
} ;




void BootLoader_Init (void)
{



}


uint8_t BootLoader_CheckNewAppCAN(void)
{
	debug_write("send ack 1 \n");

//	CAN1_Transmit(BOOT_NEW_APP_CHECK,1,CAN_ID)	;
	_delay_ms(6000);
	uint32_t REC = Can_Read_Queue();

	if (REC == BOOT_NEW_APP_FOUND  )
	{
//		CAN1_Transmit(BOOT_NEW_APP_CHECK,1,CAN_ID)	;
		return true ;
	}
	return false ;
}

void BootLoader_SendResponse(uint8_t  data  )
{
//	CAN1_Transmit(data,1,CAN_ID);
}
int BOOT_IsCommandAvailble (void)
{
//	return Can_GetSize_Queue();
}

void BOOT_READ_ARRAY (unsigned char* arr, int size)
{
	for (int i = 0 ; (i < size)  ; i++)
	{
		arr[i] = Can_Read_Queue();
	}
}

uint8_t execute_mem_write(uint8_t *pBuffer, uint32_t mem_address, uint32_t len)
{
	uint8_t status = FLASH_COMPLETE ;

	FLASH_Unlock();

	for(uint32_t i = 0 ; i <len ; i++)
	{
		status = FLASH_ProgramByte(mem_address+i,pBuffer[i] );
	}

	FLASH_Lock();
	return status;
}


void bootloader_send_ack(uint8_t command_code, uint8_t follow_len)
{
	uint8_t ack_buf[2];
	ack_buf[0] = BL_ACK;
	ack_buf[1] = follow_len;
//	CAN1_Transmit(*((uint16_t*)ack_buf),2,CAN_ID);

}

void bootloader_send_nack(void)
{
	uint8_t nack = BL_NACK;
//	CAN1_Transmit(nack,1,CAN_ID);
}

uint8_t bootloader_verify_crc (uint8_t *pData, uint32_t len, uint32_t crc_host)
{
	uint32_t uwCRCValue=0xff;
	CRC_ResetDR();
	for (uint32_t i=0 ; i < len ; i++)
	{
		uint32_t i_data = pData[i];
		uwCRCValue = CRC_CalcCRC(i_data);
	}

	CRC_ResetDR();

	if( uwCRCValue == crc_host)
	{
		return VERIFY_CRC_SUCCESS;
	}

	return VERIFY_CRC_FAIL;
}



uint8_t verify_address(uint32_t go_address)
{

	if ( go_address >= SRAM1_BASE && go_address <= SRAM1_END)
	{
		return ADDR_VALID;
	}
	else if ( go_address >= SRAM2_BASE && go_address <= SRAM2_END)
	{
		return ADDR_VALID;
	}
	else if ( go_address >= FLASH_BASE && go_address <= FLASH_END)
	{
		return ADDR_VALID;
	}
	else if ( go_address >= BKPSRAM_BASE && go_address <= BKPSRAM_END)
	{
		return ADDR_VALID;
	}
	else
		return ADDR_INVALID;
}

uint8_t execute_flash_erase(uint8_t sector_number , uint8_t number_of_sector)
{
	uint8_t status = 0 ;
	if( number_of_sector > 8 )
		return INVALID_SECTOR;

	if( (sector_number == 0xff ) || (sector_number <= 7) )
	{
		if(sector_number == (uint8_t) 0xff)
		{

			FLASH_Unlock();
			status =FLASH_EraseAllSectors(VoltageRange_3);
			FLASH_Lock();

		}
		else
		{
			FLASH_Unlock();
			uint8_t remanining_sector = 8 - sector_number;
			if( number_of_sector > remanining_sector)
			{
				number_of_sector = remanining_sector;
			}

			int i = sector_number;
			for (  ; i < (sector_number + number_of_sector) ; i++ )
			{
				status =	FLASH_EraseSector(i,VoltageRange_3);
			}
			FLASH_Lock();
		}
		return status;
	}
	return INVALID_SECTOR;
}

void system_deinit(void)
{
	TIM6->CR1 = 0 ;
	TIM6->CR1  = 0 ;
	TIM6->PSC =  0;
	TIM6->DIER = 0 ;
	TIM6->ARR = 0 ;
	USART2->CR1= 0;
	USART2->BRR = 0 ;
	USART2->CR3 =0;
	GPIOA->AFR[0] &= ~0x0F00;
	GPIOA->MODER  &= ~0x0030;
	NVIC_DisableIRQ(TIM6_DAC_IRQn);
	RCC->APB1ENR &=~( (1<<4)|(1<<5));
	RCC->AHB1ENR &=~0xf;
	RCC->APB1ENR &=~(1<<17);
}


void bootloader_jump_to_user_app(void)
{

	void (*app_reset_handler)(void);
	debug_write("bootloader_jump_to_user_app\n");
	uint32_t msp_value = *(volatile uint32_t *)FLASH_SECTOR2_BASE_ADDRESS;
	__set_MSP(msp_value);
	system_deinit();
	uint32_t resethandler_address = *(volatile uint32_t *) (FLASH_SECTOR2_BASE_ADDRESS + 4);
	app_reset_handler = (void*) resethandler_address;
	app_reset_handler();
}






void bootloader_handle_flash_erase_cmd(uint8_t *pBuffer)
{
	debug_write("bootloader_handle_flash_erase_cmd\n");

	uint32_t command_packet_len = pBuffer[0]+1 ;

	uint32_t host_crc = *((uint32_t * ) (pBuffer+command_packet_len - 4) ) ;

	if (! bootloader_verify_crc(&pBuffer[0],command_packet_len-4,host_crc))
	{
		debug_write("checksum success !!\n");
		bootloader_send_ack(pBuffer[0],1);
		uint8_t erase_status = 0x00;


		erase_status = execute_flash_erase(pBuffer[2] , pBuffer[3]);


		CAN1_Transmit(erase_status,1,CAN_ID);
		//		bootloader_uart_write_data(&erase_status,1);

	}else
	{
		debug_write("BL_DEBUG_MSG:checksum fail !!\n");
		bootloader_send_nack();
	}
}


uint8_t bootloader_handle_mem_write_cmd(uint8_t *pBuffer, uint16_t size )
{

	uint8_t write_status = 0x00;

	uint8_t payload_len = pBuffer[6];

	uint32_t mem_address = *((uint32_t *) ( &pBuffer[2]) );


	debug_write("bootloader_handle_mem_write_cmd\n");

	uint32_t command_packet_len = pBuffer[0]+1 ;


	uint32_t host_crc = *((uint32_t * ) (pBuffer+command_packet_len - 4) ) ;

	if (! bootloader_verify_crc(&pBuffer[0],command_packet_len-4,host_crc))
	{
		debug_write("checksum success !!\n");
		bootloader_send_ack(pBuffer[0],1);
		if( verify_address(mem_address) == ADDR_VALID )
		{
			debug_write("valid mem write address\n");
			write_status = execute_mem_write(&pBuffer[7],mem_address, payload_len);
			BootLoader_SendResponse(write_status);
		}
		else
		{
			debug_write("invalid mem write address\n");
			write_status = ADDR_INVALID;
			BootLoader_SendResponse(write_status );
		}
	}
	else
	{
		debug_write("checksum fail !!\n");
		bootloader_send_nack();
	}

}


