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
#include "xrk4_lbe_1_64.h"

extern XRk4_lbe_1_64_Config XRk4_lbe_1_64_ConfigTable[];

XRk4_lbe_1_64_Config *XRk4_lbe_1_64_LookupConfig(u16 DeviceId) {
	XRk4_lbe_1_64_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XRK4_LBE_1_64_NUM_INSTANCES; Index++) {
		if (XRk4_lbe_1_64_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XRk4_lbe_1_64_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XRk4_lbe_1_64_Initialize(XRk4_lbe_1_64 *InstancePtr, u16 DeviceId) {
	XRk4_lbe_1_64_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XRk4_lbe_1_64_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XRk4_lbe_1_64_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

