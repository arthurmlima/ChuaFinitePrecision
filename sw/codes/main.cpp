/******************************************************************************
 * Copyright (C) 2010 - 2022 Xilinx, Inc.  All rights reserved.
 * SPDX-License-Identifier: MIT
 ******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file xaxidma_example_simple_intr.c
 *
 * This file demonstrates how to use the xaxidma driver on the Xilinx AXI
 * DMA core (AXIDMA) to transfer packets.in interrupt mode when the AXIDMA core
 * is configured in simple mode
 *
 * This code assumes a loopback hardware widget is connected to the AXI DMA
 * core for data packet loopback.
 *
 * To see the debug print, you need a Uart16550 or uartlite in your system,
 * and please set "-DDEBUG" in your compiler options. You need to rebuild your
 * software executable.
 *
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- ---- -------- -------------------------------------------------------
 * 4.00a rkv  02/22/11 New example created for simple DMA, this example is for
 *       	       simple DMA,Added interrupt support for Zynq.
 * 4.00a srt  08/04/11 Changed a typo in the RxIntrHandler, changed
 *		       XAXIDMA_DMA_TO_DEVICE to XAXIDMA_DEVICE_TO_DMA
 * 5.00a srt  03/06/12 Added Flushing and Invalidation of Caches to fix CRs
 *		       648103, 648701.
 *		       Added V7 DDR Base Address to fix CR 649405.
 * 6.00a srt  03/27/12 Changed API calls to support MCDMA driver.
 * 7.00a srt  06/18/12 API calls are reverted back for backward compatibility.
 * 7.01a srt  11/02/12 Buffer sizes (Tx and Rx) are modified to meet maximum
 *		       DDR memory limit of the h/w system built with Area mode
 * 7.02a srt  03/01/13 Updated DDR base address for IPI designs (CR 703656).
 * 9.1   adk  01/07/16 Updated DDR base address for Ultrascale (CR 799532) and
 *		       removed the defines for S6/V6.
 * 9.2   vak  15/04/16 Fixed compilation warnings in the example
 * 9.3   ms   01/23/17 Modified xil_printf statement in main function to
 *                     ensure that "Successfully ran" and "Failed" strings are
 *                     available in all examples. This is a fix for CR-965028.
 * 9.6   rsp  02/14/18 Support data buffers above 4GB.Use UINTPTR for typecasting
 *                     buffer address (CR-992638).
 * 9.9   rsp  01/21/19 Fix use of #elif check in deriving DDR_BASE_ADDR.
 * 9.10  rsp  09/17/19 Fix cache maintenance ops for source and dest buffer.
 * 9.14  sk   03/08/22 Delete DDR memory limits comments as they are not
 * 		       relevant to this driver version.
 * </pre>
 *
 * ***************************************************************************
 */

/***************************** Include Files *********************************/

#include "parameters.h"

int main(void)
{

	union FloatUInt32 cmedia;

	int Index;

	u32 Value;

	TxBufferPtr = (u32 *)TX_BUFFER_BASE;
	RxBufferPtr = (u32 *)RX_BUFFER_BASE;

	/* Initial setup for Uart16550 */
#ifdef XPAR_UARTNS550_0_BASEADDR
	Uart550_Setup();
#endif

	xil_printf("\r\n--- Entering main() --- \r\n");

	Config = XAxiDma_LookupConfig(DMA_DEV_ID);
	if (!Config)
	{
		xil_printf("No config found for %d\r\n", DMA_DEV_ID);

		return XST_FAILURE;
	}

	tm_cfg = XCce_1_32_LookupConfig(XPAR_Cce_1_32_0_DEVICE_ID);
	if (tm_cfg)
	{
		int status = XCce_1_32_CfgInitialize(&tm, tm_cfg);
		if (status != XST_SUCCESS)
			printf("core\n");
	}

	// seta os parametros da imagem mu_diff, dt
	cmedia.f = 0.5007f;
	XCce_1_32_Set_media(&tm, cmedia.i);

	XCce_1_32_Start(&tm);

	/* Initialize DMA engine */
	Status = XAxiDma_CfgInitialize(&AxiDma, Config);

	if (Status != XST_SUCCESS)
	{
		xil_printf("Initialization failed %d\r\n", Status);
		return XST_FAILURE;
	}

	if (XAxiDma_HasSg(&AxiDma))
	{
		xil_printf("Device configured as SG mode \r\n");
		return XST_FAILURE;
	}

	/* Set up Interrupt system  */
	Status = SetupIntrSystem(&Intc, &AxiDma, RX_INTR_ID);
	if (Status != XST_SUCCESS)
	{

		xil_printf("Failed intr setup\r\n");
		return XST_FAILURE;
	}

	/* Disable all interrupts before setup */

	XAxiDma_IntrDisable(&AxiDma, XAXIDMA_IRQ_ALL_MASK,
						XAXIDMA_DEVICE_TO_DMA);

	/* Enable all interrupts */

	XAxiDma_IntrEnable(&AxiDma, XAXIDMA_IRQ_ALL_MASK,
					   XAXIDMA_DEVICE_TO_DMA);

	/* Initialize flags before start transfer test  */
	TxDone = 0;
	RxDone = 0;
	Error = 0;

	/* Flush the buffers before the DMA transfer, in case the Data Cache
	 * is enabled
	 */
	Xil_DCacheFlushRange((UINTPTR)RxBuffer, 4 * MAX_PKT_LEN);

	/* Send image */

	Status = XAxiDma_SimpleTransfer(&AxiDma, (UINTPTR)RxBuffer, 4 * MAX_PKT_LEN, XAXIDMA_DEVICE_TO_DMA);

	if (Status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}

	while (RxDone == 1)
	{
		;
		;
	}

	for (int yt = 40000; yt < 90000; yt++)
	{
		printf("%f  \n", RxBuffer[yt]);
	}

	printf("--- Exiting main() --- \r\n");

	return XST_SUCCESS;
}
