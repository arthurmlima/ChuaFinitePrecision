// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.1 (64-bit)
// Tool Version Limit: 2023.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XRK4_LBE_2_32_H
#define XRK4_LBE_2_32_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xrk4_lbe_2_32_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Ctrl_BaseAddress;
} XRk4_lbe_2_32_Config;
#endif

typedef struct {
    u64 Ctrl_BaseAddress;
    u32 IsReady;
} XRk4_lbe_2_32;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XRk4_lbe_2_32_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XRk4_lbe_2_32_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XRk4_lbe_2_32_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XRk4_lbe_2_32_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XRk4_lbe_2_32_Initialize(XRk4_lbe_2_32 *InstancePtr, u16 DeviceId);
XRk4_lbe_2_32_Config* XRk4_lbe_2_32_LookupConfig(u16 DeviceId);
int XRk4_lbe_2_32_CfgInitialize(XRk4_lbe_2_32 *InstancePtr, XRk4_lbe_2_32_Config *ConfigPtr);
#else
int XRk4_lbe_2_32_Initialize(XRk4_lbe_2_32 *InstancePtr, const char* InstanceName);
int XRk4_lbe_2_32_Release(XRk4_lbe_2_32 *InstancePtr);
#endif

void XRk4_lbe_2_32_Start(XRk4_lbe_2_32 *InstancePtr);
u32 XRk4_lbe_2_32_IsDone(XRk4_lbe_2_32 *InstancePtr);
u32 XRk4_lbe_2_32_IsIdle(XRk4_lbe_2_32 *InstancePtr);
u32 XRk4_lbe_2_32_IsReady(XRk4_lbe_2_32 *InstancePtr);
void XRk4_lbe_2_32_EnableAutoRestart(XRk4_lbe_2_32 *InstancePtr);
void XRk4_lbe_2_32_DisableAutoRestart(XRk4_lbe_2_32 *InstancePtr);

void XRk4_lbe_2_32_Set_media(XRk4_lbe_2_32 *InstancePtr, u32 Data);
u32 XRk4_lbe_2_32_Get_media(XRk4_lbe_2_32 *InstancePtr);

void XRk4_lbe_2_32_InterruptGlobalEnable(XRk4_lbe_2_32 *InstancePtr);
void XRk4_lbe_2_32_InterruptGlobalDisable(XRk4_lbe_2_32 *InstancePtr);
void XRk4_lbe_2_32_InterruptEnable(XRk4_lbe_2_32 *InstancePtr, u32 Mask);
void XRk4_lbe_2_32_InterruptDisable(XRk4_lbe_2_32 *InstancePtr, u32 Mask);
void XRk4_lbe_2_32_InterruptClear(XRk4_lbe_2_32 *InstancePtr, u32 Mask);
u32 XRk4_lbe_2_32_InterruptGetEnabled(XRk4_lbe_2_32 *InstancePtr);
u32 XRk4_lbe_2_32_InterruptGetStatus(XRk4_lbe_2_32 *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
