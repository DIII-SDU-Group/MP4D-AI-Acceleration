// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xinvert_image.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XInvert_image_CfgInitialize(XInvert_image *InstancePtr, XInvert_image_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Bus_a_BaseAddress = ConfigPtr->Bus_a_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XInvert_image_Start(XInvert_image *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XInvert_image_ReadReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_AP_CTRL) & 0x80;
    XInvert_image_WriteReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_AP_CTRL, Data | 0x01);
}

u32 XInvert_image_IsDone(XInvert_image *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XInvert_image_ReadReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XInvert_image_IsIdle(XInvert_image *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XInvert_image_ReadReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XInvert_image_IsReady(XInvert_image *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XInvert_image_ReadReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XInvert_image_EnableAutoRestart(XInvert_image *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XInvert_image_WriteReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_AP_CTRL, 0x80);
}

void XInvert_image_DisableAutoRestart(XInvert_image *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XInvert_image_WriteReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_AP_CTRL, 0);
}

u32 XInvert_image_Get_image_in_BaseAddress(XInvert_image *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Bus_a_BaseAddress + XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_BASE);
}

u32 XInvert_image_Get_image_in_HighAddress(XInvert_image *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Bus_a_BaseAddress + XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_HIGH);
}

u32 XInvert_image_Get_image_in_TotalBytes(XInvert_image *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_HIGH - XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_BASE + 1);
}

u32 XInvert_image_Get_image_in_BitWidth(XInvert_image *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XINVERT_IMAGE_BUS_A_WIDTH_IMAGE_IN;
}

u32 XInvert_image_Get_image_in_Depth(XInvert_image *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XINVERT_IMAGE_BUS_A_DEPTH_IMAGE_IN;
}

u32 XInvert_image_Write_image_in_Words(XInvert_image *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_HIGH - XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Bus_a_BaseAddress + XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XInvert_image_Read_image_in_Words(XInvert_image *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_HIGH - XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Bus_a_BaseAddress + XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_BASE + (offset + i)*4);
    }
    return length;
}

u32 XInvert_image_Write_image_in_Bytes(XInvert_image *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_HIGH - XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Bus_a_BaseAddress + XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XInvert_image_Read_image_in_Bytes(XInvert_image *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_HIGH - XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Bus_a_BaseAddress + XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_BASE + offset + i);
    }
    return length;
}

u32 XInvert_image_Get_image_out_BaseAddress(XInvert_image *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Bus_a_BaseAddress + XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_BASE);
}

u32 XInvert_image_Get_image_out_HighAddress(XInvert_image *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Bus_a_BaseAddress + XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_HIGH);
}

u32 XInvert_image_Get_image_out_TotalBytes(XInvert_image *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_HIGH - XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_BASE + 1);
}

u32 XInvert_image_Get_image_out_BitWidth(XInvert_image *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XINVERT_IMAGE_BUS_A_WIDTH_IMAGE_OUT;
}

u32 XInvert_image_Get_image_out_Depth(XInvert_image *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XINVERT_IMAGE_BUS_A_DEPTH_IMAGE_OUT;
}

u32 XInvert_image_Write_image_out_Words(XInvert_image *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_HIGH - XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Bus_a_BaseAddress + XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XInvert_image_Read_image_out_Words(XInvert_image *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_HIGH - XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Bus_a_BaseAddress + XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_BASE + (offset + i)*4);
    }
    return length;
}

u32 XInvert_image_Write_image_out_Bytes(XInvert_image *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_HIGH - XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Bus_a_BaseAddress + XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XInvert_image_Read_image_out_Bytes(XInvert_image *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_HIGH - XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Bus_a_BaseAddress + XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_BASE + offset + i);
    }
    return length;
}

void XInvert_image_InterruptGlobalEnable(XInvert_image *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XInvert_image_WriteReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_GIE, 1);
}

void XInvert_image_InterruptGlobalDisable(XInvert_image *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XInvert_image_WriteReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_GIE, 0);
}

void XInvert_image_InterruptEnable(XInvert_image *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XInvert_image_ReadReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_IER);
    XInvert_image_WriteReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_IER, Register | Mask);
}

void XInvert_image_InterruptDisable(XInvert_image *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XInvert_image_ReadReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_IER);
    XInvert_image_WriteReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_IER, Register & (~Mask));
}

void XInvert_image_InterruptClear(XInvert_image *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XInvert_image_WriteReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_ISR, Mask);
}

u32 XInvert_image_InterruptGetEnabled(XInvert_image *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XInvert_image_ReadReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_IER);
}

u32 XInvert_image_InterruptGetStatus(XInvert_image *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XInvert_image_ReadReg(InstancePtr->Bus_a_BaseAddress, XINVERT_IMAGE_BUS_A_ADDR_ISR);
}

