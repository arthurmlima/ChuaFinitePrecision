// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.1 (64-bit)
// Tool Version Limit: 2023.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xcce_1_32.h"

extern XCce_1_32_Config XCce_1_32_ConfigTable[];

XCce_1_32_Config *XCce_1_32_LookupConfig(u16 DeviceId) {
	XCce_1_32_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XCCE_1_32_NUM_INSTANCES; Index++) {
		if (XCce_1_32_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XCce_1_32_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XCce_1_32_Initialize(XCce_1_32 *InstancePtr, u16 DeviceId) {
	XCce_1_32_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XCce_1_32_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XCce_1_32_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

