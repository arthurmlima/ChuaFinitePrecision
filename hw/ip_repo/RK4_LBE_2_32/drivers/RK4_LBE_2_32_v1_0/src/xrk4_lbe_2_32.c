// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.1 (64-bit)
// Tool Version Limit: 2023.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xrk4_lbe_2_32.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XRk4_lbe_2_32_CfgInitialize(XRk4_lbe_2_32 *InstancePtr, XRk4_lbe_2_32_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XRk4_lbe_2_32_Start(XRk4_lbe_2_32 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XRk4_lbe_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_AP_CTRL) & 0x80;
    XRk4_lbe_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XRk4_lbe_2_32_IsDone(XRk4_lbe_2_32 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XRk4_lbe_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XRk4_lbe_2_32_IsIdle(XRk4_lbe_2_32 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XRk4_lbe_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XRk4_lbe_2_32_IsReady(XRk4_lbe_2_32 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XRk4_lbe_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XRk4_lbe_2_32_EnableAutoRestart(XRk4_lbe_2_32 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XRk4_lbe_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_AP_CTRL, 0x80);
}

void XRk4_lbe_2_32_DisableAutoRestart(XRk4_lbe_2_32 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XRk4_lbe_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_AP_CTRL, 0);
}

void XRk4_lbe_2_32_Set_media(XRk4_lbe_2_32 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XRk4_lbe_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_MEDIA_DATA, Data);
}

u32 XRk4_lbe_2_32_Get_media(XRk4_lbe_2_32 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XRk4_lbe_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_MEDIA_DATA);
    return Data;
}

void XRk4_lbe_2_32_InterruptGlobalEnable(XRk4_lbe_2_32 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XRk4_lbe_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_GIE, 1);
}

void XRk4_lbe_2_32_InterruptGlobalDisable(XRk4_lbe_2_32 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XRk4_lbe_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_GIE, 0);
}

void XRk4_lbe_2_32_InterruptEnable(XRk4_lbe_2_32 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XRk4_lbe_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_IER);
    XRk4_lbe_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_IER, Register | Mask);
}

void XRk4_lbe_2_32_InterruptDisable(XRk4_lbe_2_32 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XRk4_lbe_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_IER);
    XRk4_lbe_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_IER, Register & (~Mask));
}

void XRk4_lbe_2_32_InterruptClear(XRk4_lbe_2_32 *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XRk4_lbe_2_32_WriteReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_ISR, Mask);
}

u32 XRk4_lbe_2_32_InterruptGetEnabled(XRk4_lbe_2_32 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XRk4_lbe_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_IER);
}

u32 XRk4_lbe_2_32_InterruptGetStatus(XRk4_lbe_2_32 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XRk4_lbe_2_32_ReadReg(InstancePtr->Ctrl_BaseAddress, XRK4_LBE_2_32_CTRL_ADDR_ISR);
}

