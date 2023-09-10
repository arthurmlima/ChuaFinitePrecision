// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.1 (64-bit)
// Tool Version Limit: 2023.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XCCE_1_64_H
#define XCCE_1_64_H

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
#include "xcce_1_64_hw.h"

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
} XCce_1_64_Config;
#endif

typedef struct {
    u64 Ctrl_BaseAddress;
    u32 IsReady;
} XCce_1_64;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XCce_1_64_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XCce_1_64_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XCce_1_64_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XCce_1_64_ReadReg(BaseAddress, RegOffset) \
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
int XCce_1_64_Initialize(XCce_1_64 *InstancePtr, u16 DeviceId);
XCce_1_64_Config* XCce_1_64_LookupConfig(u16 DeviceId);
int XCce_1_64_CfgInitialize(XCce_1_64 *InstancePtr, XCce_1_64_Config *ConfigPtr);
#else
int XCce_1_64_Initialize(XCce_1_64 *InstancePtr, const char* InstanceName);
int XCce_1_64_Release(XCce_1_64 *InstancePtr);
#endif

void XCce_1_64_Start(XCce_1_64 *InstancePtr);
u32 XCce_1_64_IsDone(XCce_1_64 *InstancePtr);
u32 XCce_1_64_IsIdle(XCce_1_64 *InstancePtr);
u32 XCce_1_64_IsReady(XCce_1_64 *InstancePtr);
void XCce_1_64_EnableAutoRestart(XCce_1_64 *InstancePtr);
void XCce_1_64_DisableAutoRestart(XCce_1_64 *InstancePtr);

void XCce_1_64_Set_media(XCce_1_64 *InstancePtr, u32 Data);
u32 XCce_1_64_Get_media(XCce_1_64 *InstancePtr);

void XCce_1_64_InterruptGlobalEnable(XCce_1_64 *InstancePtr);
void XCce_1_64_InterruptGlobalDisable(XCce_1_64 *InstancePtr);
void XCce_1_64_InterruptEnable(XCce_1_64 *InstancePtr, u32 Mask);
void XCce_1_64_InterruptDisable(XCce_1_64 *InstancePtr, u32 Mask);
void XCce_1_64_InterruptClear(XCce_1_64 *InstancePtr, u32 Mask);
u32 XCce_1_64_InterruptGetEnabled(XCce_1_64 *InstancePtr);
u32 XCce_1_64_InterruptGetStatus(XCce_1_64 *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
