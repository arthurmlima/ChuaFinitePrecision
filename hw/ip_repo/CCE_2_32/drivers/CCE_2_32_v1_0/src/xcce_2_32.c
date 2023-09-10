// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.1 (64-bit)
// Tool Version Limit: 2023.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xcce_2_32.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XCce_2_32_CfgInitialize(XCce_2_32 *InstancePtr, XCce_2_32_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XCce_2_32_Start(XCce_2_32 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCce_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_AP_CTRL) & 0x80;
    XCce_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XCce_2_32_IsDone(XCce_2_32 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCce_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XCce_2_32_IsIdle(XCce_2_32 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCce_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XCce_2_32_IsReady(XCce_2_32 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCce_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XCce_2_32_EnableAutoRestart(XCce_2_32 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCce_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_AP_CTRL, 0x80);
}

void XCce_2_32_DisableAutoRestart(XCce_2_32 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCce_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_AP_CTRL, 0);
}

void XCce_2_32_Set_media(XCce_2_32 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCce_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_MEDIA_DATA, Data);
}

u32 XCce_2_32_Get_media(XCce_2_32 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCce_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_MEDIA_DATA);
    return Data;
}

void XCce_2_32_InterruptGlobalEnable(XCce_2_32 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCce_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_GIE, 1);
}

void XCce_2_32_InterruptGlobalDisable(XCce_2_32 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCce_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_GIE, 0);
}

void XCce_2_32_InterruptEnable(XCce_2_32 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XCce_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_IER);
    XCce_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_IER, Register | Mask);
}

void XCce_2_32_InterruptDisable(XCce_2_32 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XCce_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_IER);
    XCce_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_IER, Register & (~Mask));
}

void XCce_2_32_InterruptClear(XCce_2_32 *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCce_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_ISR, Mask);
}

u32 XCce_2_32_InterruptGetEnabled(XCce_2_32 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCce_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_IER);
}

u32 XCce_2_32_InterruptGetStatus(XCce_2_32 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCce_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XCCE_2_32_CTRL_ADDR_ISR);
}

