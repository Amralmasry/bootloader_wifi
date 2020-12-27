

#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include "BOOT_LOADER/BOOT.h"
#include "Services_layers/debug.h"
#include "Services_layers/Queue.h"
#include "Services_layers/Speical_Timer.h"

int main(void)
{

	uint8_t arr [80] ;
	uint8_t flag = 0 ;


	RCC->AHB1ENR |= RCC_AHB1ENR_CRCEN;
	debug_init();
	debug_write("***********************************\n");
	debug_write("Boot Loader check for host\n");
	BootLoader_Init();


	WIFI_LOCAL_SEND_DATA("BOOTLOADER?");
	if (WIFI_WAIT_RESPONSE(1,"YES"))
	{
		flag=1 ;
	}

	else
		flag = 0 ;





	while(1)
	{
		if (!flag)
		{

			bootloader_jump_to_user_app();
		}
		else
		{

			uint8_t FIRST_TIME = 1 ;



			while(1)
			{

				uint16_t size  = SpecialUart_wifi_local_array_DATA_ONLY (arr) ;

				if (size)
				{

					if (FIRST_TIME)
					{
						FIRST_TIME = 0 ;
						execute_flash_erase(2,2);
					}

					if (bootloader_handle_mem_write_cmd(arr,size))
					{
						WIFI_LOCAL_SEND_DATA("DONE");
					}
				}

			}
		}

	}

}

/* shkhakh  */

