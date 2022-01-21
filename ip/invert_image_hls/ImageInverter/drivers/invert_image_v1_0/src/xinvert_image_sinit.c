// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xinvert_image.h"

extern XInvert_image_Config XInvert_image_ConfigTable[];

XInvert_image_Config *XInvert_image_LookupConfig(u16 DeviceId) {
	XInvert_image_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XINVERT_IMAGE_NUM_INSTANCES; Index++) {
		if (XInvert_image_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XInvert_image_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XInvert_image_Initialize(XInvert_image *InstancePtr, u16 DeviceId) {
	XInvert_image_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XInvert_image_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XInvert_image_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

