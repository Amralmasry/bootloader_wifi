

#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include "BOOT_LOADER/BOOT.h"
#include "Services_layers/debug.h"
#include "Services_layers/Queue.h"
#include "Services_layers/Speical_Timer.h"
#include "HAL/WIFI_LOCAL.h"
#include "Services_layers/Special_Uart_wifi_local.h"
int main(void)
{


	uint8_t arr [1000] ;

	debug_init();

	debug_write("***********************************\n");
	debug_write("Boot Loader check for host\n");


  	BootLoader_Init();



	if ( !boot_check_host())
	{
		debug_write("***********************************\n");
		debug_write("NO HOST JUMP TO USER\n");
		bootloader_jump_to_user_app();
	}

	debug_write("***********************************\n");
	debug_write("host is present\n");




	uint8_t FIRST_TIME = 1 ;
	SpecialTimer_Start(BOOT_TIMEOUT);
	uint32_t pack = 0 ;
	while(1)
	{

		uint16_t size  = SpecialUart_wifi_local_array_DATA_ONLY (arr) ;

		if (size)
		{
			debug_write( "packet " );
			debug_values(1,pack++);
			//debug_massege(arr,size);
			SpecialTimer_Reset(BOOT_TIMEOUT);
			if (!memcmp(arr, "FINISH",strlen( "FINISH")))
			{
				SpecialTimer_Stop(BOOT_TIMEOUT);
				SpecialTimer_Reset(BOOT_TIMEOUT);
				debug_write("***********************************\n");
				debug_write("done flashing\n");
				bootloader_jump_to_user_app();
			}
			if (FIRST_TIME)
			{
				FIRST_TIME = 0 ;
				execute_flash_erase(2,2);
			}

			if (bootloader_handle_mem_write_cmd(arr,size))
			{
				WIFI_LOCAL_SEND_IP((uint8_t *)"DONE",strlen("DONE"));
			}
		}
		else if (SpecialTimer_Check(BOOT_TIMEOUT,20000))
		{
			debug_write("***********************************\n");
			debug_write("host no data\n");
			SpecialTimer_Stop(BOOT_TIMEOUT);
			SpecialTimer_Reset(BOOT_TIMEOUT);
			NVIC_SystemReset();
		}
		else if (WIFI_LOCAL_RAED(arr))
		{
			if (!memcmp(arr,"0,CLOSED",strlen("0,CLOSED")))
			{
				debug_write("***********************************\n");
				debug_write("host closed\n");
				SpecialTimer_Stop(BOOT_TIMEOUT);
				SpecialTimer_Reset(BOOT_TIMEOUT);
				NVIC_SystemReset();
			}
		}

	}

}



