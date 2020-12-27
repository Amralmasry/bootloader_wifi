

#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include "BOOT_LOADER/BOOT.h"
#include "Services_layers/debug.h"
#include "Services_layers/Queue.h"
#include "Services_layers/Speical_Timer.h"

int main(void)
{



	RCC->AHB1ENR |= RCC_AHB1ENR_CRCEN;
	debug_init();
	debug_write("***********************************\n");
	debug_write("Boot Loader check for host\n");
	BootLoader_Init();


	RCC->AHB1ENR |=  4;                 /* enable GPIOC clock */

	GPIOC->MODER &= ~0x0C000000;        /* clear pin mode to input mode */
	uint8_t RC = 0 ;
	if (GPIOC->IDR & 0x2000)
	{
		RC = BootLoader_CheckNewAppCAN();
 	}
	else
	{
		RC=BootLoader_CheckNewAppBUTTON();

	}
	while(1)
	{
		if (!RC)
		{

			bootloader_jump_to_user_app();
		}
		else
		{

			uint8_t FIRST_TIME = 1 ;

			uint8_t rcv_len=0;
			debug_write("***********************************\n");
			debug_write("boot command wait \n");

			while(1)
			{

				if (BOOT_IsCommandAvailble())
				{
					SpecialTimer_Start(BOOT_REV_TIMEOUT);
				}

				if ( SpecialTimer_Check(BOOT_LOADER_COMMAND_TIMEOUT,2000))
				{
					SpecialTimer_Stop(BOOT_LOADER_COMMAND_TIMEOUT);
					SpecialTimer_Reset(BOOT_LOADER_COMMAND_TIMEOUT);

					bootloader_jump_to_user_app();
				}
				if (BOOT_IsCommandAvailble() && SpecialTimer_Check(BOOT_REV_TIMEOUT,5))
				{

					SpecialTimer_Start(BOOT_LOADER_COMMAND_TIMEOUT);
					SpecialTimer_Reset(BOOT_LOADER_COMMAND_TIMEOUT);


					SpecialTimer_Stop(BOOT_REV_TIMEOUT);
					SpecialTimer_Reset(BOOT_REV_TIMEOUT);

					BOOT_READ_ARRAY(BOOTLOADER_RX_BUFFER,1);
					debug_write("***********************************\n");
					debug_write("took command  \n");

					rcv_len= BOOTLOADER_RX_BUFFER[0];


					BOOT_READ_ARRAY(&BOOTLOADER_RX_BUFFER[1],rcv_len);
					switch(BOOTLOADER_RX_BUFFER[1])
					{
					case BL_FLASH_ERASE:
						bootloader_handle_flash_erase_cmd(BOOTLOADER_RX_BUFFER);
						break;
					case BL_MEM_WRITE:
						if (FIRST_TIME)
						{
							FIRST_TIME = 0 ;
							execute_flash_erase(2,2);
						}
						bootloader_handle_mem_write_cmd(BOOTLOADER_RX_BUFFER);
						break;

					default:
						debug_write("Invalid command code received from host \n");
						break;
					}
				}
			}

		}
	}
}



