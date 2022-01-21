// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// BUS_A
// 0x000000 : Control signals
//            bit 0  - ap_start (Read/Write/COH)
//            bit 1  - ap_done (Read/COR)
//            bit 2  - ap_idle (Read)
//            bit 3  - ap_ready (Read)
//            bit 7  - auto_restart (Read/Write)
//            others - reserved
// 0x000004 : Global Interrupt Enable Register
//            bit 0  - Global Interrupt Enable (Read/Write)
//            others - reserved
// 0x000008 : IP Interrupt Enable Register (Read/Write)
//            bit 0  - enable ap_done interrupt (Read/Write)
//            bit 1  - enable ap_ready interrupt (Read/Write)
//            others - reserved
// 0x00000c : IP Interrupt Status Register (Read/TOW)
//            bit 0  - ap_done (COR/TOW)
//            bit 1  - ap_ready (COR/TOW)
//            others - reserved
// 0x080000 ~
// 0x0fffff : Memory 'image_in' (307200 * 8b)
//            Word n : bit [ 7: 0] - image_in[4n]
//                     bit [15: 8] - image_in[4n+1]
//                     bit [23:16] - image_in[4n+2]
//                     bit [31:24] - image_in[4n+3]
// 0x100000 ~
// 0x17ffff : Memory 'image_out' (307200 * 8b)
//            Word n : bit [ 7: 0] - image_out[4n]
//                     bit [15: 8] - image_out[4n+1]
//                     bit [23:16] - image_out[4n+2]
//                     bit [31:24] - image_out[4n+3]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XINVERT_IMAGE_BUS_A_ADDR_AP_CTRL        0x000000
#define XINVERT_IMAGE_BUS_A_ADDR_GIE            0x000004
#define XINVERT_IMAGE_BUS_A_ADDR_IER            0x000008
#define XINVERT_IMAGE_BUS_A_ADDR_ISR            0x00000c
#define XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_BASE  0x080000
#define XINVERT_IMAGE_BUS_A_ADDR_IMAGE_IN_HIGH  0x0fffff
#define XINVERT_IMAGE_BUS_A_WIDTH_IMAGE_IN      8
#define XINVERT_IMAGE_BUS_A_DEPTH_IMAGE_IN      307200
#define XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_BASE 0x100000
#define XINVERT_IMAGE_BUS_A_ADDR_IMAGE_OUT_HIGH 0x17ffff
#define XINVERT_IMAGE_BUS_A_WIDTH_IMAGE_OUT     8
#define XINVERT_IMAGE_BUS_A_DEPTH_IMAGE_OUT     307200

