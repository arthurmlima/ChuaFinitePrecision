// Include guards to ensure the header file is included only once
#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include "xaxidma.h"
#include "xCce_1_32.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "xdebug.h"
#include "AxiTimer.h"

#ifdef XPAR_UARTNS550_0_BASEADDR
#include "xuartns550_l.h"       /* to use uartns550 */
#endif

#ifdef XPAR_INTC_0_DEVICE_ID
 #include "xintc.h"
#else
 #include "xscugic.h"
#endif

/************************** Constant Definitions *****************************/

/*
 * Device hardware build related constants.
 */

#define DMA_DEV_ID		XPAR_AXIDMA_0_DEVICE_ID

#ifdef XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
#define DDR_BASE_ADDR		XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
#elif defined (XPAR_MIG7SERIES_0_BASEADDR)
#define DDR_BASE_ADDR	XPAR_MIG7SERIES_0_BASEADDR
#elif defined (XPAR_MIG_0_BASEADDR)
#define DDR_BASE_ADDR	XPAR_MIG_0_BASEADDR
#elif defined (XPAR_PSU_DDR_0_S_AXI_BASEADDR)
#define DDR_BASE_ADDR	XPAR_PSU_DDR_0_S_AXI_BASEADDR
#endif

#ifndef DDR_BASE_ADDR
#warning CHECK FOR THE VALID DDR ADDRESS IN XPARAMETERS.H, \
		DEFAULT SET TO 0x01000000
#define MEM_BASE_ADDR		0x01000000
#else
#define MEM_BASE_ADDR		(DDR_BASE_ADDR + 0x1000000)
#endif

#ifdef XPAR_INTC_0_DEVICE_ID
#define RX_INTR_ID		XPAR_INTC_0_AXI_DMA_0_S2MM_INTROUT_VEC_ID
#define TX_INTR_ID		XPAR_INTC_0_AXI_DMA_0_MM2S_INTROUT_VEC_ID
#else
#define RX_INTR_ID		XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR
#endif

#define TX_BUFFER_BASE		(MEM_BASE_ADDR + 0x00100000)
#define RX_BUFFER_BASE		(MEM_BASE_ADDR + 0x00900000)
#define RX_BUFFER_HIGH		(MEM_BASE_ADDR + 0x010FFFFF)

#ifdef XPAR_INTC_0_DEVICE_ID
#define INTC_DEVICE_ID          XPAR_INTC_0_DEVICE_ID
#else
#define INTC_DEVICE_ID          XPAR_SCUGIC_SINGLE_DEVICE_ID
#endif

#ifdef XPAR_INTC_0_DEVICE_ID
 #define INTC		XIntc
 #define INTC_HANDLER	XIntc_InterruptHandler
#else
 #define INTC		XScuGic
 #define INTC_HANDLER	XScuGic_InterruptHandler
#endif


#define RESET_TIMEOUT_COUNTER	10000

#define TEST_START_VALUE	0xC

#define MAX_PKT_LEN		90000

#define NUMBER_OF_TRANSFERS	10



// ... other #define statements ...

#ifndef DEBUG
extern void xil_printf(const char *format, ...);
#endif

#ifdef XPAR_UARTNS550_0_BASEADDR
static void Uart550_Setup(void);
#endif

static int CheckData(int Length, u8 StartValue);
static void TxIntrHandler(void *Callback);
static void RxIntrHandler(void *Callback);
static int SetupIntrSystem(INTC * IntcInstancePtr, XAxiDma * AxiDmaPtr, u16 RxIntrId);
static void DisableIntrSystem(INTC * IntcInstancePtr, u16 RxIntrId);

static XAxiDma AxiDma; // Instance of the XAxiDma
static INTC Intc;     // Instance of the Interrupt Controller

volatile int RxDone;
volatile int Error;

XCce_1_32 tm;
XCce_1_32_Config *tm_cfg;

u32 *TxBufferPtr;
u32 *RxBufferPtr;
int Status;

XAxiDma_Config *Config;

union FloatUInt32 {
    float f;
    uint32_t i;
};
extern float RxBuffer[90000];

#endif  // HEADER_HPP