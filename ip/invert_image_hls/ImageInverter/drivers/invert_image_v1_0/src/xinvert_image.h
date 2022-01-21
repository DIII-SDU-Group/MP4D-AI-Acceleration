// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XINVERT_IMAGE_H
#define XINVERT_IMAGE_H

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
#include "xinvert_image_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Bus_a_BaseAddress;
} XInvert_image_Config;
#endif

typedef struct {
    u64 Bus_a_BaseAddress;
    u32 IsReady;
} XInvert_image;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XInvert_image_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XInvert_image_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XInvert_image_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XInvert_image_ReadReg(BaseAddress, RegOffset) \
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
int XInvert_image_Initialize(XInvert_image *InstancePtr, u16 DeviceId);
XInvert_image_Config* XInvert_image_LookupConfig(u16 DeviceId);
int XInvert_image_CfgInitialize(XInvert_image *InstancePtr, XInvert_image_Config *ConfigPtr);
#else
int XInvert_image_Initialize(XInvert_image *InstancePtr, const char* InstanceName);
int XInvert_image_Release(XInvert_image *InstancePtr);
#endif

void XInvert_image_Start(XInvert_image *InstancePtr);
u32 XInvert_image_IsDone(XInvert_image *InstancePtr);
u32 XInvert_image_IsIdle(XInvert_image *InstancePtr);
u32 XInvert_image_IsReady(XInvert_image *InstancePtr);
void XInvert_image_EnableAutoRestart(XInvert_image *InstancePtr);
void XInvert_image_DisableAutoRestart(XInvert_image *InstancePtr);

u32 XInvert_image_Get_image_in_BaseAddress(XInvert_image *InstancePtr);
u32 XInvert_image_Get_image_in_HighAddress(XInvert_image *InstancePtr);
u32 XInvert_image_Get_image_in_TotalBytes(XInvert_image *InstancePtr);
u32 XInvert_image_Get_image_in_BitWidth(XInvert_image *InstancePtr);
u32 XInvert_image_Get_image_in_Depth(XInvert_image *InstancePtr);
u32 XInvert_image_Write_image_in_Words(XInvert_image *InstancePtr, int offset, word_type *data, int length);
u32 XInvert_image_Read_image_in_Words(XInvert_image *InstancePtr, int offset, word_type *data, int length);
u32 XInvert_image_Write_image_in_Bytes(XInvert_image *InstancePtr, int offset, char *data, int length);
u32 XInvert_image_Read_image_in_Bytes(XInvert_image *InstancePtr, int offset, char *data, int length);
u32 XInvert_image_Get_image_out_BaseAddress(XInvert_image *InstancePtr);
u32 XInvert_image_Get_image_out_HighAddress(XInvert_image *InstancePtr);
u32 XInvert_image_Get_image_out_TotalBytes(XInvert_image *InstancePtr);
u32 XInvert_image_Get_image_out_BitWidth(XInvert_image *InstancePtr);
u32 XInvert_image_Get_image_out_Depth(XInvert_image *InstancePtr);
u32 XInvert_image_Write_image_out_Words(XInvert_image *InstancePtr, int offset, word_type *data, int length);
u32 XInvert_image_Read_image_out_Words(XInvert_image *InstancePtr, int offset, word_type *data, int length);
u32 XInvert_image_Write_image_out_Bytes(XInvert_image *InstancePtr, int offset, char *data, int length);
u32 XInvert_image_Read_image_out_Bytes(XInvert_image *InstancePtr, int offset, char *data, int length);

void XInvert_image_InterruptGlobalEnable(XInvert_image *InstancePtr);
void XInvert_image_InterruptGlobalDisable(XInvert_image *InstancePtr);
void XInvert_image_InterruptEnable(XInvert_image *InstancePtr, u32 Mask);
void XInvert_image_InterruptDisable(XInvert_image *InstancePtr, u32 Mask);
void XInvert_image_InterruptClear(XInvert_image *InstancePtr, u32 Mask);
u32 XInvert_image_InterruptGetEnabled(XInvert_image *InstancePtr);
u32 XInvert_image_InterruptGetStatus(XInvert_image *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
