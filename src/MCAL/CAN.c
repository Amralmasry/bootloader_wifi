
#include <stm32f4xx.h>
#include "CAN.h"


//static uint32_t txCounter = 0;

void CAN1_Init(void)
{
	/* Configure GPIO with AF9, CAN1 connected to APB1 with 45MHz clock
	 * CAN1_RX  -> PA11 (IN)
	 * CAN1_TX  -> PA12 (OUT)
	 * ***********************/

	/* Enable port A clock */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	/* Select alternate function mode */
	GPIOA->MODER &= ~(GPIO_MODER_MODER11 | GPIO_MODER_MODER12);
	GPIOA->MODER |= (GPIO_MODER_MODER11_1 | GPIO_MODER_MODER12_1);

	/* Select output type push-pull */
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_12);

	/* Select output speed medium */
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR12);
	GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR12_0);

	/* Select pull up */
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR11 | GPIO_PUPDR_PUPDR12);
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPDR11_0 | GPIO_PUPDR_PUPDR12_0);

	/* Select AF9 */
	GPIOA->AFR[1] &= ~(GPIO_AFRH_AFRH11 | GPIO_AFRH_AFRH12);
	GPIOA->AFR[1] |= (GPIO_AFRH_AFRH11_AF9 | GPIO_AFRH_AFRH12_AF9);

	/* Configure CAN1 */
	/* Enable CAN1 clock */
	RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;

	/* Configuration after reset:
	 * **************************
	 * CAN reception/transmission frozen during debug.
	 * Time Triggered Communication mode disabled.
	 * The Sleep mode is left on software request.
	 * Automatic retransmission.
	 * Receive FIFO not locked on overrun.
	 * */

	/* Set automatic bus-off management */
	CAN1->MCR |= CAN_MCR_ABOM;

	/* Set transmit FIFO priority driven by the request order */
	CAN1->MCR |= CAN_MCR_TXFP;

	/* Initialization request */
	CAN1->MCR |= CAN_MCR_INRQ;

	/* Request to exit Sleep mode */
	CAN1->MCR &= ~CAN_MCR_SLEEP;

	/* Wait for initialization mode */
	while((CAN_MSR_SLAK == (CAN_MSR_SLAK & CAN1->MSR))
			|| (CAN_MSR_INAK != (CAN_MSR_INAK & CAN1->MSR)))
	{
		/* Do nothing until initialization mode is entered */
	}

	/* Setup timing parameters,
	 * BaudRate = 1 Mbps, BRP[9:0] = 4, TS1[3:0] = 6, TS2[2:0] = 0, SJW[1:0] = 0
	 * tq = (BRP[9:0] + 1) x tPCLK = 5 * 0,0222 = 0,111 us
	 * tBS1 = tq x (TS1[3:0] + 1) = 0.111 * 7 = 0.777 us
	 * tBS2 = tq x (TS2[2:0] + 1) = 0.111 * 1 = 0.111 us
	 * NominalBitTime = 1 × tq + tBS1 + tBS2 = 0.111 + 0.777 + 0.111 = 0,9999 (1) us
	 * BaudRate = 1 / NominalBitTime = 1 MBits/s */
	CAN1->BTR = 0x00060004;

	/* Reset identifier register, no extension, no remote */
	CAN1->sTxMailBox[0].TIR = 0;

	/* Set CAN standard identifier = 0x100 */
	CAN1->sTxMailBox[0].TIR |= (0x25<<21);

	/* Set CAN frame length to 8 */
	CAN1->sTxMailBox[0].TDTR &= ~CAN_TDT0R_DLC;
	CAN1->sTxMailBox[0].TDTR |= 0x00000008;

	/* Reset transmit data registers  */
	CAN1->sTxMailBox[0].TDLR = 0;
	CAN1->sTxMailBox[0].TDHR = 0;

	/* Filter setup,
	 * Filter 1 0x25           Turn on/off green led
	 * Filter 2 (0x10 - 0x1F)  Turn on/off green led
	 * Filter 3 0x15           Turn on/off red led
	 * Filter 4 0x20 - 0x2F    Turn on/off red led
	 *
	 * After reset filters in init mode and for CAN1
	 * filter until number 13. Filter scale dual 16-bit */

	/* Set Filter init mode */
	CAN1->FMR |= CAN_FMR_FINIT;

	/* Set filer mode, 1 and 3 list, 2 and 4 mask */
	CAN1->FM1R &= ~(CAN_FM1R_FBM2 | CAN_FM1R_FBM4);
	CAN1->FM1R |= (CAN_FM1R_FBM1 | CAN_FM1R_FBM3);

	/* Set FIFO 0 for all filters */
	CAN1->FFA1R &= ~(CAN_FFA1R_FFA1 | CAN_FFA1R_FFA2
			| CAN_FFA1R_FFA3 | CAN_FFA1R_FFA4);

	/* Filter mapping
	 *   15-8          7-5    4   3    2-0
	 * STID[10:3] STID[2:0] RTR IDE EXID[17:15]
	 * */

	/* Filter 0 Deactivated ID Mask (16-bit) No. 0, 1 */

	/* Set filter 1, list mode with ID = 0x25 */
	CAN1->sFilterRegister[1].FR1 = 0x04A004A0; /* No. 2, 3 */
	CAN1->sFilterRegister[1].FR2 = 0x04A004A0; /* No. 4, 5 */

	/* Set filter 2, mask mode with ID = 0x10:0x1F */
	CAN1->sFilterRegister[2].FR1 = 0xFE1F0200; /* No. 6 */
	CAN1->sFilterRegister[2].FR2 = 0xFE1F0200; /* No. 7 */

	/* Set filter 3, list mode with ID = 0x15 */
	CAN1->sFilterRegister[3].FR1 = 0x02A002A0; /* No. 8, 9 */
	CAN1->sFilterRegister[3].FR2 = 0x02A002A0; /* No. 10, 11 */

	/* Set filter 4, mask mode with ID = 0x20:0x2F */
	CAN1->sFilterRegister[4].FR1 = 0xFE1F0400; /* No. 12 */
	CAN1->sFilterRegister[4].FR2 = 0xFE1F0400; /* No. 13 */

	/* Activate filters */
	CAN1->FA1R |= (CAN_FA1R_FACT1 | CAN_FA1R_FACT2
			| CAN_FA1R_FACT3 | CAN_FA1R_FACT4);

	/* Active filters mode */
	CAN1->FMR &= ~CAN_FMR_FINIT;

	/* Request normal mode */
	CAN1->MCR &= ~(CAN_MCR_INRQ | CAN_MCR_SLEEP);
}



void CAN1_Transmit(uint32_t data)
{
	/* Check if transmission mailbox empty */
	if(CAN_TSR_TME0 == (CAN_TSR_TME0 & CAN1->TSR))
	{
		//	UART_Write_Array(USART2,"TX",2);

		/* Increment TX counter */
		//    txCounter++;
		/* Set TX data */
		CAN1->sTxMailBox[0].TDLR = data;

		/* Transmission request */
		CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;
	}
	else
	{
		debug_values(1,data);
	}
}


uint32_t CAN1_Receive(void)
{
	uint32_t rxData = 0;
	uint8_t dlc;
	uint8_t filterIndex;

	/* Check FIFO message pending */
	if(0 != (CAN_RF0R_FMP0 & CAN1->RF0R))
	{
		//UART_Write_Array(USART2,"RX",3);

		/* FIFO not empty, read data */
		rxData = (uint32_t)(CAN1->sFIFOMailBox[0].RDLR);

		/* Get filter match index */
		filterIndex = (uint8_t)(CAN1->sFIFOMailBox[0].RDTR >> 8);

		/* Get data length code */
		dlc = (uint8_t)(CAN1->sFIFOMailBox[0].RDTR);

		CAN1->RF0R |= CAN_RF0R_RFOM0;

	}
	return rxData;
}

