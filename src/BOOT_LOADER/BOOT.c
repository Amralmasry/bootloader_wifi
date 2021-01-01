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
#include "../Services_layers/Special_Uart_wifi_local.h"
#include "../HAL/WIFI_LOCAL.h"


uint8_t BootLoader_Init (void)
{
	uint8_t RC = 1 ;
	RCC->AHB1ENR |= RCC_AHB1ENR_CRCEN;
	WIFI_LOCAL_INIT();
//	RC = WIFI_LOCAL_JAP();
//	WIFI_START_SERVER();
	return RC ;
}

uint8_t boot_check_host (void)
{


	uint8_t RC = 0 ;
	WIFI_LOCAL_SEND_IP((uint8_t *)"BOOTLOADER?",strlen("BOOTLOADER?"));
	if (WIFI_WAIT_RESPONSE_data(1,"YES"))
	{
		RC=1 ;
		WIFI_LOCAL_SEND_IP((uint8_t *)"OK",strlen("OK"));
	}

	else
	{
		RC = 0 ;
	}

	return RC ;
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
	TIM7->CR1 = 0 ;
	TIM7->CR1  = 0 ;
	TIM7->PSC =  0;
	TIM7->DIER = 0 ;
	TIM7->ARR = 0 ;
	TIM6->CR1 = 0 ;
	TIM6->CR1  = 0 ;
	TIM6->PSC =  0;
	TIM6->DIER = 0 ;
	TIM6->ARR = 0 ;
	USART2->CR1= 0;
	USART2->BRR = 0 ;
	USART2->CR3 =0;
	USART1->CR1= 0;
	USART1->BRR = 0 ;
	USART1->CR3 =0;
	GPIOA->AFR[0] &= ~0x0F00;
	GPIOA->MODER  &= ~0x0030;

	NVIC_DisableIRQ(TIM6_DAC_IRQn);
	NVIC_DisableIRQ(TIM7_IRQn);
	NVIC_DisableIRQ(USART1_IRQn);

	RCC->APB2ENR &=~( RCC_APB2ENR_USART1EN );
	RCC->AHB1ENR &=~0xf;
	RCC->APB1ENR &=~(RCC_APB1ENR_TIM6EN | RCC_APB1ENR_TIM7EN| RCC_APB1ENR_USART2EN );
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


uint32_t mem_address = 0x08008000 ;



uint8_t bootloader_handle_mem_write_cmd(uint8_t *pBuffer, uint16_t command_packet_len )
{

	uint8_t write_status = 0x00;

	uint16_t payload_len = command_packet_len-4;

	//debug_write("bootloader_handle_mem_write_cmd\n");



	uint32_t host_crc = *((uint32_t * ) (pBuffer+command_packet_len - 4) ) ;

	if (! bootloader_verify_crc(pBuffer,payload_len,host_crc))
	{
		debug_write("checksum success !!\n");

		if( verify_address(mem_address) == ADDR_VALID )
		{

			write_status = execute_mem_write(pBuffer ,mem_address, payload_len);
			mem_address+=payload_len ;
		}
		else
		{
			debug_write("invalid mem write address\n");
			write_status = 0;
		}
	}
	else
	{
	//	debug_write("checksum fail !!\n");
	}
	return write_status ;
}


