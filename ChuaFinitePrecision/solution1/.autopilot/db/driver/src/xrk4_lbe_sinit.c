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
#include "xrk4_lbe.h"

extern XRk4_lbe_Config XRk4_lbe_ConfigTable[];

XRk4_lbe_Config *XRk4_lbe_LookupConfig(u16 DeviceId) {
	XRk4_lbe_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XRK4_LBE_NUM_INSTANCES; Index++) {
		if (XRk4_lbe_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XRk4_lbe_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XRk4_lbe_Initialize(XRk4_lbe *InstancePtr, u16 DeviceId) {
	XRk4_lbe_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XRk4_lbe_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XRk4_lbe_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

