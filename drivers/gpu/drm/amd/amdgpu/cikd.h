<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Alex Deucher
 */
#अगर_अघोषित CIK_H
#घोषणा CIK_H

#घोषणा MC_SEQ_MISC0__MT__MASK	0xf0000000
#घोषणा MC_SEQ_MISC0__MT__GDDR1  0x10000000
#घोषणा MC_SEQ_MISC0__MT__DDR2   0x20000000
#घोषणा MC_SEQ_MISC0__MT__GDDR3  0x30000000
#घोषणा MC_SEQ_MISC0__MT__GDDR4  0x40000000
#घोषणा MC_SEQ_MISC0__MT__GDDR5  0x50000000
#घोषणा MC_SEQ_MISC0__MT__HBM    0x60000000
#घोषणा MC_SEQ_MISC0__MT__DDR3   0xB0000000

#घोषणा CP_ME_TABLE_SIZE    96

/* display controller offsets used क्रम crtc/cur/lut/grph/viewport/etc. */
#घोषणा CRTC0_REGISTER_OFFSET                 (0x1b7c - 0x1b7c)
#घोषणा CRTC1_REGISTER_OFFSET                 (0x1e7c - 0x1b7c)
#घोषणा CRTC2_REGISTER_OFFSET                 (0x417c - 0x1b7c)
#घोषणा CRTC3_REGISTER_OFFSET                 (0x447c - 0x1b7c)
#घोषणा CRTC4_REGISTER_OFFSET                 (0x477c - 0x1b7c)
#घोषणा CRTC5_REGISTER_OFFSET                 (0x4a7c - 0x1b7c)

/* hpd instance offsets */
#घोषणा HPD0_REGISTER_OFFSET                 (0x1807 - 0x1807)
#घोषणा HPD1_REGISTER_OFFSET                 (0x180a - 0x1807)
#घोषणा HPD2_REGISTER_OFFSET                 (0x180d - 0x1807)
#घोषणा HPD3_REGISTER_OFFSET                 (0x1810 - 0x1807)
#घोषणा HPD4_REGISTER_OFFSET                 (0x1813 - 0x1807)
#घोषणा HPD5_REGISTER_OFFSET                 (0x1816 - 0x1807)

#घोषणा BONAIRE_GB_ADDR_CONFIG_GOLDEN        0x12010001
#घोषणा HAWAII_GB_ADDR_CONFIG_GOLDEN         0x12011003

#घोषणा		PIPEID(x)					((x) << 0)
#घोषणा		MEID(x)						((x) << 2)
#घोषणा		VMID(x)						((x) << 4)
#घोषणा		QUEUEID(x)					((x) << 8)

#घोषणा mmCC_DRM_ID_STRAPS				0x1559
#घोषणा CC_DRM_ID_STRAPS__ATI_REV_ID_MASK		0xf0000000

#घोषणा mmCHUB_CONTROL					0x619
#घोषणा		BYPASS_VM					(1 << 0)

#घोषणा		SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU	(0 << 5)

#घोषणा mmGRPH_LUT_10BIT_BYPASS_CONTROL			0x1a02
#घोषणा		LUT_10BIT_BYPASS_EN			(1 << 8)

#       define CURSOR_MONO                    0
#       define CURSOR_24_1                    1
#       define CURSOR_24_8_PRE_MULT           2
#       define CURSOR_24_8_UNPRE_MULT         3
#       define CURSOR_URGENT_ALWAYS           0
#       define CURSOR_URGENT_1_8              1
#       define CURSOR_URGENT_1_4              2
#       define CURSOR_URGENT_3_8              3
#       define CURSOR_URGENT_1_2              4

#       define GRPH_DEPTH_8BPP                0
#       define GRPH_DEPTH_16BPP               1
#       define GRPH_DEPTH_32BPP               2
/* 8 BPP */
#       define GRPH_FORMAT_INDEXED            0
/* 16 BPP */
#       define GRPH_FORMAT_ARGB1555           0
#       define GRPH_FORMAT_ARGB565            1
#       define GRPH_FORMAT_ARGB4444           2
#       define GRPH_FORMAT_AI88               3
#       define GRPH_FORMAT_MONO16             4
#       define GRPH_FORMAT_BGRA5551           5
/* 32 BPP */
#       define GRPH_FORMAT_ARGB8888           0
#       define GRPH_FORMAT_ARGB2101010        1
#       define GRPH_FORMAT_32BPP_DIG          2
#       define GRPH_FORMAT_8B_ARGB2101010     3
#       define GRPH_FORMAT_BGRA1010102        4
#       define GRPH_FORMAT_8B_BGRA1010102     5
#       define GRPH_FORMAT_RGB111110          6
#       define GRPH_FORMAT_BGR101111          7
#       define ADDR_SURF_MACRO_TILE_ASPECT_1  0
#       define ADDR_SURF_MACRO_TILE_ASPECT_2  1
#       define ADDR_SURF_MACRO_TILE_ASPECT_4  2
#       define ADDR_SURF_MACRO_TILE_ASPECT_8  3
#       define GRPH_ARRAY_LINEAR_GENERAL      0
#       define GRPH_ARRAY_LINEAR_ALIGNED      1
#       define GRPH_ARRAY_1D_TILED_THIN1      2
#       define GRPH_ARRAY_2D_TILED_THIN1      4
#       define DISPLAY_MICRO_TILING          0
#       define THIN_MICRO_TILING             1
#       define DEPTH_MICRO_TILING            2
#       define ROTATED_MICRO_TILING          4
#       define GRPH_ENDIAN_NONE               0
#       define GRPH_ENDIAN_8IN16              1
#       define GRPH_ENDIAN_8IN32              2
#       define GRPH_ENDIAN_8IN64              3
#       define GRPH_RED_SEL_R                 0
#       define GRPH_RED_SEL_G                 1
#       define GRPH_RED_SEL_B                 2
#       define GRPH_RED_SEL_A                 3
#       define GRPH_GREEN_SEL_G               0
#       define GRPH_GREEN_SEL_B               1
#       define GRPH_GREEN_SEL_A               2
#       define GRPH_GREEN_SEL_R               3
#       define GRPH_BLUE_SEL_B                0
#       define GRPH_BLUE_SEL_A                1
#       define GRPH_BLUE_SEL_R                2
#       define GRPH_BLUE_SEL_G                3
#       define GRPH_ALPHA_SEL_A               0
#       define GRPH_ALPHA_SEL_R               1
#       define GRPH_ALPHA_SEL_G               2
#       define GRPH_ALPHA_SEL_B               3
#       define INPUT_GAMMA_USE_LUT                  0
#       define INPUT_GAMMA_BYPASS                   1
#       define INPUT_GAMMA_SRGB_24                  2
#       define INPUT_GAMMA_XVYCC_222                3

#       define INPUT_CSC_BYPASS                     0
#       define INPUT_CSC_PROG_COEFF                 1
#       define INPUT_CSC_PROG_SHARED_MATRIXA        2

#       define OUTPUT_CSC_BYPASS                    0
#       define OUTPUT_CSC_TV_RGB                    1
#       define OUTPUT_CSC_YCBCR_601                 2
#       define OUTPUT_CSC_YCBCR_709                 3
#       define OUTPUT_CSC_PROG_COEFF                4
#       define OUTPUT_CSC_PROG_SHARED_MATRIXB       5

#       define DEGAMMA_BYPASS                       0
#       define DEGAMMA_SRGB_24                      1
#       define DEGAMMA_XVYCC_222                    2
#       define GAMUT_REMAP_BYPASS                   0
#       define GAMUT_REMAP_PROG_COEFF               1
#       define GAMUT_REMAP_PROG_SHARED_MATRIXA      2
#       define GAMUT_REMAP_PROG_SHARED_MATRIXB      3

#       define REGAMMA_BYPASS                       0
#       define REGAMMA_SRGB_24                      1
#       define REGAMMA_XVYCC_222                    2
#       define REGAMMA_PROG_A                       3
#       define REGAMMA_PROG_B                       4

#       define FMT_CLAMP_6BPC                0
#       define FMT_CLAMP_8BPC                1
#       define FMT_CLAMP_10BPC               2

#       define HDMI_24BIT_DEEP_COLOR         0
#       define HDMI_30BIT_DEEP_COLOR         1
#       define HDMI_36BIT_DEEP_COLOR         2
#       define HDMI_ACR_HW                   0
#       define HDMI_ACR_32                   1
#       define HDMI_ACR_44                   2
#       define HDMI_ACR_48                   3
#       define HDMI_ACR_X1                   1
#       define HDMI_ACR_X2                   2
#       define HDMI_ACR_X4                   4
#       define AFMT_AVI_INFO_Y_RGB           0
#       define AFMT_AVI_INFO_Y_YCBCR422      1
#       define AFMT_AVI_INFO_Y_YCBCR444      2

#घोषणा			NO_AUTO						0
#घोषणा			ES_AUTO						1
#घोषणा			GS_AUTO						2
#घोषणा			ES_AND_GS_AUTO					3

#       define ARRAY_MODE(x)					((x) << 2)
#       define PIPE_CONFIG(x)					((x) << 6)
#       define TILE_SPLIT(x)					((x) << 11)
#       define MICRO_TILE_MODE_NEW(x)				((x) << 22)
#       define SAMPLE_SPLIT(x)					((x) << 25)
#       define BANK_WIDTH(x)					((x) << 0)
#       define BANK_HEIGHT(x)					((x) << 2)
#       define MACRO_TILE_ASPECT(x)				((x) << 4)
#       define NUM_BANKS(x)					((x) << 6)

#घोषणा		MSG_ENTER_RLC_SAFE_MODE			1
#घोषणा		MSG_EXIT_RLC_SAFE_MODE			0

/*
 * PM4
 */
#घोषणा	PACKET_TYPE0	0
#घोषणा	PACKET_TYPE1	1
#घोषणा	PACKET_TYPE2	2
#घोषणा	PACKET_TYPE3	3

#घोषणा CP_PACKET_GET_TYPE(h) (((h) >> 30) & 3)
#घोषणा CP_PACKET_GET_COUNT(h) (((h) >> 16) & 0x3FFF)
#घोषणा CP_PACKET0_GET_REG(h) ((h) & 0xFFFF)
#घोषणा CP_PACKET3_GET_OPCODE(h) (((h) >> 8) & 0xFF)
#घोषणा PACKET0(reg, n)	((PACKET_TYPE0 << 30) |				\
			 ((reg) & 0xFFFF) |			\
			 ((n) & 0x3FFF) << 16)
#घोषणा CP_PACKET2			0x80000000
#घोषणा		PACKET2_PAD_SHIFT		0
#घोषणा		PACKET2_PAD_MASK		(0x3fffffff << 0)

#घोषणा PACKET2(v)	(CP_PACKET2 | REG_SET(PACKET2_PAD, (v)))

#घोषणा PACKET3(op, n)	((PACKET_TYPE3 << 30) |				\
			 (((op) & 0xFF) << 8) |				\
			 ((n) & 0x3FFF) << 16)

#घोषणा PACKET3_COMPUTE(op, n) (PACKET3(op, n) | 1 << 1)

/* Packet 3 types */
#घोषणा	PACKET3_NOP					0x10
#घोषणा	PACKET3_SET_BASE				0x11
#घोषणा		PACKET3_BASE_INDEX(x)                  ((x) << 0)
#घोषणा			CE_PARTITION_BASE		3
#घोषणा	PACKET3_CLEAR_STATE				0x12
#घोषणा	PACKET3_INDEX_BUFFER_SIZE			0x13
#घोषणा	PACKET3_DISPATCH_सूचीECT				0x15
#घोषणा	PACKET3_DISPATCH_INसूचीECT			0x16
#घोषणा	PACKET3_ATOMIC_GDS				0x1D
#घोषणा	PACKET3_ATOMIC_MEM				0x1E
#घोषणा	PACKET3_OCCLUSION_QUERY				0x1F
#घोषणा	PACKET3_SET_PREDICATION				0x20
#घोषणा	PACKET3_REG_RMW					0x21
#घोषणा	PACKET3_COND_EXEC				0x22
#घोषणा	PACKET3_PRED_EXEC				0x23
#घोषणा	PACKET3_DRAW_INसूचीECT				0x24
#घोषणा	PACKET3_DRAW_INDEX_INसूचीECT			0x25
#घोषणा	PACKET3_INDEX_BASE				0x26
#घोषणा	PACKET3_DRAW_INDEX_2				0x27
#घोषणा	PACKET3_CONTEXT_CONTROL				0x28
#घोषणा	PACKET3_INDEX_TYPE				0x2A
#घोषणा	PACKET3_DRAW_INसूचीECT_MULTI			0x2C
#घोषणा	PACKET3_DRAW_INDEX_AUTO				0x2D
#घोषणा	PACKET3_NUM_INSTANCES				0x2F
#घोषणा	PACKET3_DRAW_INDEX_MULTI_AUTO			0x30
#घोषणा	PACKET3_INसूचीECT_BUFFER_CONST			0x33
#घोषणा	PACKET3_STRMOUT_BUFFER_UPDATE			0x34
#घोषणा	PACKET3_DRAW_INDEX_OFFSET_2			0x35
#घोषणा	PACKET3_DRAW_PREAMBLE				0x36
#घोषणा	PACKET3_WRITE_DATA				0x37
#घोषणा		WRITE_DATA_DST_SEL(x)                   ((x) << 8)
		/* 0 - रेजिस्टर
		 * 1 - memory (sync - via GRBM)
		 * 2 - gl2
		 * 3 - gds
		 * 4 - reserved
		 * 5 - memory (async - direct)
		 */
#घोषणा		WR_ONE_ADDR                             (1 << 16)
#घोषणा		WR_CONFIRM                              (1 << 20)
#घोषणा		WRITE_DATA_CACHE_POLICY(x)              ((x) << 25)
		/* 0 - LRU
		 * 1 - Stream
		 */
#घोषणा		WRITE_DATA_ENGINE_SEL(x)                ((x) << 30)
		/* 0 - me
		 * 1 - pfp
		 * 2 - ce
		 */
#घोषणा	PACKET3_DRAW_INDEX_INसूचीECT_MULTI		0x38
#घोषणा	PACKET3_MEM_SEMAPHORE				0x39
#              define PACKET3_SEM_USE_MAILBOX       (0x1 << 16)
#              define PACKET3_SEM_SEL_SIGNAL_TYPE   (0x1 << 20) /* 0 = increment, 1 = ग_लिखो 1 */
#              define PACKET3_SEM_CLIENT_CODE	    ((x) << 24) /* 0 = CP, 1 = CB, 2 = DB */
#              define PACKET3_SEM_SEL_SIGNAL	    (0x6 << 29)
#              define PACKET3_SEM_SEL_WAIT	    (0x7 << 29)
#घोषणा	PACKET3_COPY_DW					0x3B
#घोषणा	PACKET3_WAIT_REG_MEM				0x3C
#घोषणा		WAIT_REG_MEM_FUNCTION(x)                ((x) << 0)
		/* 0 - always
		 * 1 - <
		 * 2 - <=
		 * 3 - ==
		 * 4 - !=
		 * 5 - >=
		 * 6 - >
		 */
#घोषणा		WAIT_REG_MEM_MEM_SPACE(x)               ((x) << 4)
		/* 0 - reg
		 * 1 - mem
		 */
#घोषणा		WAIT_REG_MEM_OPERATION(x)               ((x) << 6)
		/* 0 - रुको_reg_mem
		 * 1 - wr_रुको_wr_reg
		 */
#घोषणा		WAIT_REG_MEM_ENGINE(x)                  ((x) << 8)
		/* 0 - me
		 * 1 - pfp
		 */
#घोषणा	PACKET3_INसूचीECT_BUFFER				0x3F
#घोषणा		INसूचीECT_BUFFER_TCL2_VOLATILE           (1 << 22)
#घोषणा		INसूचीECT_BUFFER_VALID                   (1 << 23)
#घोषणा		INसूचीECT_BUFFER_CACHE_POLICY(x)         ((x) << 28)
		/* 0 - LRU
		 * 1 - Stream
		 * 2 - Bypass
		 */
#घोषणा	PACKET3_COPY_DATA				0x40
#घोषणा	PACKET3_PFP_SYNC_ME				0x42
#घोषणा	PACKET3_SURFACE_SYNC				0x43
#              define PACKET3_DEST_BASE_0_ENA      (1 << 0)
#              define PACKET3_DEST_BASE_1_ENA      (1 << 1)
#              define PACKET3_CB0_DEST_BASE_ENA    (1 << 6)
#              define PACKET3_CB1_DEST_BASE_ENA    (1 << 7)
#              define PACKET3_CB2_DEST_BASE_ENA    (1 << 8)
#              define PACKET3_CB3_DEST_BASE_ENA    (1 << 9)
#              define PACKET3_CB4_DEST_BASE_ENA    (1 << 10)
#              define PACKET3_CB5_DEST_BASE_ENA    (1 << 11)
#              define PACKET3_CB6_DEST_BASE_ENA    (1 << 12)
#              define PACKET3_CB7_DEST_BASE_ENA    (1 << 13)
#              define PACKET3_DB_DEST_BASE_ENA     (1 << 14)
#              define PACKET3_TCL1_VOL_ACTION_ENA  (1 << 15)
#              define PACKET3_TC_VOL_ACTION_ENA    (1 << 16) /* L2 */
#              define PACKET3_TC_WB_ACTION_ENA     (1 << 18) /* L2 */
#              define PACKET3_DEST_BASE_2_ENA      (1 << 19)
#              define PACKET3_DEST_BASE_3_ENA      (1 << 21)
#              define PACKET3_TCL1_ACTION_ENA      (1 << 22)
#              define PACKET3_TC_ACTION_ENA        (1 << 23) /* L2 */
#              define PACKET3_CB_ACTION_ENA        (1 << 25)
#              define PACKET3_DB_ACTION_ENA        (1 << 26)
#              define PACKET3_SH_KCACHE_ACTION_ENA (1 << 27)
#              define PACKET3_SH_KCACHE_VOL_ACTION_ENA (1 << 28)
#              define PACKET3_SH_ICACHE_ACTION_ENA (1 << 29)
#घोषणा	PACKET3_COND_WRITE				0x45
#घोषणा	PACKET3_EVENT_WRITE				0x46
#घोषणा		EVENT_TYPE(x)                           ((x) << 0)
#घोषणा		EVENT_INDEX(x)                          ((x) << 8)
		/* 0 - any non-TS event
		 * 1 - ZPASS_DONE, PIXEL_PIPE_STAT_*
		 * 2 - SAMPLE_PIPELINESTAT
		 * 3 - SAMPLE_STREAMOUTSTAT*
		 * 4 - *S_PARTIAL_FLUSH
		 * 5 - EOP events
		 * 6 - EOS events
		 */
#घोषणा	PACKET3_EVENT_WRITE_EOP				0x47
#घोषणा		EOP_TCL1_VOL_ACTION_EN                  (1 << 12)
#घोषणा		EOP_TC_VOL_ACTION_EN                    (1 << 13) /* L2 */
#घोषणा		EOP_TC_WB_ACTION_EN                     (1 << 15) /* L2 */
#घोषणा		EOP_TCL1_ACTION_EN                      (1 << 16)
#घोषणा		EOP_TC_ACTION_EN                        (1 << 17) /* L2 */
#घोषणा		EOP_TCL2_VOLATILE                       (1 << 24)
#घोषणा		EOP_CACHE_POLICY(x)                     ((x) << 25)
		/* 0 - LRU
		 * 1 - Stream
		 * 2 - Bypass
		 */
#घोषणा		DATA_SEL(x)                             ((x) << 29)
		/* 0 - discard
		 * 1 - send low 32bit data
		 * 2 - send 64bit data
		 * 3 - send 64bit GPU counter value
		 * 4 - send 64bit sys counter value
		 */
#घोषणा		INT_SEL(x)                              ((x) << 24)
		/* 0 - none
		 * 1 - पूर्णांकerrupt only (DATA_SEL = 0)
		 * 2 - पूर्णांकerrupt when data ग_लिखो is confirmed
		 */
#घोषणा		DST_SEL(x)                              ((x) << 16)
		/* 0 - MC
		 * 1 - TC/L2
		 */
#घोषणा	PACKET3_EVENT_WRITE_EOS				0x48
#घोषणा	PACKET3_RELEASE_MEM				0x49
#घोषणा	PACKET3_PREAMBLE_CNTL				0x4A
#              define PACKET3_PREAMBLE_BEGIN_CLEAR_STATE     (2 << 28)
#              define PACKET3_PREAMBLE_END_CLEAR_STATE       (3 << 28)
#घोषणा	PACKET3_DMA_DATA				0x50
/* 1. header
 * 2. CONTROL
 * 3. SRC_ADDR_LO or DATA [31:0]
 * 4. SRC_ADDR_HI [31:0]
 * 5. DST_ADDR_LO [31:0]
 * 6. DST_ADDR_HI [7:0]
 * 7. COMMAND [30:21] | BYTE_COUNT [20:0]
 */
/* CONTROL */
#              define PACKET3_DMA_DATA_ENGINE(x)     ((x) << 0)
		/* 0 - ME
		 * 1 - PFP
		 */
#              define PACKET3_DMA_DATA_SRC_CACHE_POLICY(x) ((x) << 13)
		/* 0 - LRU
		 * 1 - Stream
		 * 2 - Bypass
		 */
#              define PACKET3_DMA_DATA_SRC_VOLATILE (1 << 15)
#              define PACKET3_DMA_DATA_DST_SEL(x)  ((x) << 20)
		/* 0 - DST_ADDR using DAS
		 * 1 - GDS
		 * 3 - DST_ADDR using L2
		 */
#              define PACKET3_DMA_DATA_DST_CACHE_POLICY(x) ((x) << 25)
		/* 0 - LRU
		 * 1 - Stream
		 * 2 - Bypass
		 */
#              define PACKET3_DMA_DATA_DST_VOLATILE (1 << 27)
#              define PACKET3_DMA_DATA_SRC_SEL(x)  ((x) << 29)
		/* 0 - SRC_ADDR using SAS
		 * 1 - GDS
		 * 2 - DATA
		 * 3 - SRC_ADDR using L2
		 */
#              define PACKET3_DMA_DATA_CP_SYNC     (1 << 31)
/* COMMAND */
#              define PACKET3_DMA_DATA_DIS_WC      (1 << 21)
#              define PACKET3_DMA_DATA_CMD_SRC_SWAP(x) ((x) << 22)
		/* 0 - none
		 * 1 - 8 in 16
		 * 2 - 8 in 32
		 * 3 - 8 in 64
		 */
#              define PACKET3_DMA_DATA_CMD_DST_SWAP(x) ((x) << 24)
		/* 0 - none
		 * 1 - 8 in 16
		 * 2 - 8 in 32
		 * 3 - 8 in 64
		 */
#              define PACKET3_DMA_DATA_CMD_SAS     (1 << 26)
		/* 0 - memory
		 * 1 - रेजिस्टर
		 */
#              define PACKET3_DMA_DATA_CMD_DAS     (1 << 27)
		/* 0 - memory
		 * 1 - रेजिस्टर
		 */
#              define PACKET3_DMA_DATA_CMD_SAIC    (1 << 28)
#              define PACKET3_DMA_DATA_CMD_DAIC    (1 << 29)
#              define PACKET3_DMA_DATA_CMD_RAW_WAIT  (1 << 30)
#घोषणा	PACKET3_ACQUIRE_MEM				0x58
#घोषणा	PACKET3_REWIND					0x59
#घोषणा	PACKET3_LOAD_UCONFIG_REG			0x5E
#घोषणा	PACKET3_LOAD_SH_REG				0x5F
#घोषणा	PACKET3_LOAD_CONFIG_REG				0x60
#घोषणा	PACKET3_LOAD_CONTEXT_REG			0x61
#घोषणा	PACKET3_SET_CONFIG_REG				0x68
#घोषणा		PACKET3_SET_CONFIG_REG_START			0x00002000
#घोषणा		PACKET3_SET_CONFIG_REG_END			0x00002c00
#घोषणा	PACKET3_SET_CONTEXT_REG				0x69
#घोषणा		PACKET3_SET_CONTEXT_REG_START			0x0000a000
#घोषणा		PACKET3_SET_CONTEXT_REG_END			0x0000a400
#घोषणा	PACKET3_SET_CONTEXT_REG_INसूचीECT		0x73
#घोषणा	PACKET3_SET_SH_REG				0x76
#घोषणा		PACKET3_SET_SH_REG_START			0x00002c00
#घोषणा		PACKET3_SET_SH_REG_END				0x00003000
#घोषणा	PACKET3_SET_SH_REG_OFFSET			0x77
#घोषणा	PACKET3_SET_QUEUE_REG				0x78
#घोषणा	PACKET3_SET_UCONFIG_REG				0x79
#घोषणा		PACKET3_SET_UCONFIG_REG_START			0x0000c000
#घोषणा		PACKET3_SET_UCONFIG_REG_END			0x0000c400
#घोषणा	PACKET3_SCRATCH_RAM_WRITE			0x7D
#घोषणा	PACKET3_SCRATCH_RAM_READ			0x7E
#घोषणा	PACKET3_LOAD_CONST_RAM				0x80
#घोषणा	PACKET3_WRITE_CONST_RAM				0x81
#घोषणा	PACKET3_DUMP_CONST_RAM				0x83
#घोषणा	PACKET3_INCREMENT_CE_COUNTER			0x84
#घोषणा	PACKET3_INCREMENT_DE_COUNTER			0x85
#घोषणा	PACKET3_WAIT_ON_CE_COUNTER			0x86
#घोषणा	PACKET3_WAIT_ON_DE_COUNTER_DIFF			0x88
#घोषणा	PACKET3_SWITCH_BUFFER				0x8B

/* SDMA - first instance at 0xd000, second at 0xd800 */
#घोषणा SDMA0_REGISTER_OFFSET                             0x0 /* not a रेजिस्टर */
#घोषणा SDMA1_REGISTER_OFFSET                             0x200 /* not a रेजिस्टर */
#घोषणा SDMA_MAX_INSTANCE 2

#घोषणा SDMA_PACKET(op, sub_op, e)	((((e) & 0xFFFF) << 16) |	\
					 (((sub_op) & 0xFF) << 8) |	\
					 (((op) & 0xFF) << 0))
/* sDMA opcodes */
#घोषणा	SDMA_OPCODE_NOP					  0
#	define SDMA_NOP_COUNT(x)			  (((x) & 0x3FFF) << 16)
#घोषणा	SDMA_OPCODE_COPY				  1
#       define SDMA_COPY_SUB_OPCODE_LINEAR                0
#       define SDMA_COPY_SUB_OPCODE_TILED                 1
#       define SDMA_COPY_SUB_OPCODE_SOA                   3
#       define SDMA_COPY_SUB_OPCODE_LINEAR_SUB_WINDOW     4
#       define SDMA_COPY_SUB_OPCODE_TILED_SUB_WINDOW      5
#       define SDMA_COPY_SUB_OPCODE_T2T_SUB_WINDOW        6
#घोषणा	SDMA_OPCODE_WRITE				  2
#       define SDMA_WRITE_SUB_OPCODE_LINEAR               0
#       define SDMA_WRITE_SUB_OPCODE_TILED                1
#घोषणा	SDMA_OPCODE_INसूचीECT_BUFFER			  4
#घोषणा	SDMA_OPCODE_FENCE				  5
#घोषणा	SDMA_OPCODE_TRAP				  6
#घोषणा	SDMA_OPCODE_SEMAPHORE				  7
#       define SDMA_SEMAPHORE_EXTRA_O                     (1 << 13)
		/* 0 - increment
		 * 1 - ग_लिखो 1
		 */
#       define SDMA_SEMAPHORE_EXTRA_S                     (1 << 14)
		/* 0 - रुको
		 * 1 - संकेत
		 */
#       define SDMA_SEMAPHORE_EXTRA_M                     (1 << 15)
		/* mailbox */
#घोषणा	SDMA_OPCODE_POLL_REG_MEM			  8
#       define SDMA_POLL_REG_MEM_EXTRA_OP(x)              ((x) << 10)
		/* 0 - रुको_reg_mem
		 * 1 - wr_रुको_wr_reg
		 */
#       define SDMA_POLL_REG_MEM_EXTRA_FUNC(x)            ((x) << 12)
		/* 0 - always
		 * 1 - <
		 * 2 - <=
		 * 3 - ==
		 * 4 - !=
		 * 5 - >=
		 * 6 - >
		 */
#       define SDMA_POLL_REG_MEM_EXTRA_M                  (1 << 15)
		/* 0 = रेजिस्टर
		 * 1 = memory
		 */
#घोषणा	SDMA_OPCODE_COND_EXEC				  9
#घोषणा	SDMA_OPCODE_CONSTANT_FILL			  11
#       define SDMA_CONSTANT_FILL_EXTRA_SIZE(x)           ((x) << 14)
		/* 0 = byte fill
		 * 2 = DW fill
		 */
#घोषणा	SDMA_OPCODE_GENERATE_PTE_PDE			  12
#घोषणा	SDMA_OPCODE_TIMESTAMP				  13
#       define SDMA_TIMESTAMP_SUB_OPCODE_SET_LOCAL        0
#       define SDMA_TIMESTAMP_SUB_OPCODE_GET_LOCAL        1
#       define SDMA_TIMESTAMP_SUB_OPCODE_GET_GLOBAL       2
#घोषणा	SDMA_OPCODE_SRBM_WRITE				  14
#       define SDMA_SRBM_WRITE_EXTRA_BYTE_ENABLE(x)       ((x) << 12)
		/* byte mask */

#घोषणा VCE_CMD_NO_OP		0x00000000
#घोषणा VCE_CMD_END		0x00000001
#घोषणा VCE_CMD_IB		0x00000002
#घोषणा VCE_CMD_FENCE		0x00000003
#घोषणा VCE_CMD_TRAP		0x00000004
#घोषणा VCE_CMD_IB_AUTO		0x00000005
#घोषणा VCE_CMD_SEMAPHORE	0x00000006

/* अगर PTR32, these are the bases क्रम scratch and lds */
#घोषणा	PRIVATE_BASE(x)	((x) << 0) /* scratch */
#घोषणा	SHARED_BASE(x)	((x) << 16) /* LDS */

#घोषणा KFD_CIK_SDMA_QUEUE_OFFSET (mmSDMA0_RLC1_RB_CNTL - mmSDMA0_RLC0_RB_CNTL)

/* valid क्रम both DEFAULT_MTYPE and APE1_MTYPE */
क्रमागत अणु
	MTYPE_CACHED = 0,
	MTYPE_NONCACHED = 3
पूर्ण;

/* mmPA_SC_RASTER_CONFIG mask */
#घोषणा RB_MAP_PKR0(x)				((x) << 0)
#घोषणा RB_MAP_PKR0_MASK			(0x3 << 0)
#घोषणा RB_MAP_PKR1(x)				((x) << 2)
#घोषणा RB_MAP_PKR1_MASK			(0x3 << 2)
#घोषणा RB_XSEL2(x)				((x) << 4)
#घोषणा RB_XSEL2_MASK				(0x3 << 4)
#घोषणा RB_XSEL					(1 << 6)
#घोषणा RB_YSEL					(1 << 7)
#घोषणा PKR_MAP(x)				((x) << 8)
#घोषणा PKR_MAP_MASK				(0x3 << 8)
#घोषणा PKR_XSEL(x)				((x) << 10)
#घोषणा PKR_XSEL_MASK				(0x3 << 10)
#घोषणा PKR_YSEL(x)				((x) << 12)
#घोषणा PKR_YSEL_MASK				(0x3 << 12)
#घोषणा SC_MAP(x)				((x) << 16)
#घोषणा SC_MAP_MASK				(0x3 << 16)
#घोषणा SC_XSEL(x)				((x) << 18)
#घोषणा SC_XSEL_MASK				(0x3 << 18)
#घोषणा SC_YSEL(x)				((x) << 20)
#घोषणा SC_YSEL_MASK				(0x3 << 20)
#घोषणा SE_MAP(x)				((x) << 24)
#घोषणा SE_MAP_MASK				(0x3 << 24)
#घोषणा SE_XSEL(x)				((x) << 26)
#घोषणा SE_XSEL_MASK				(0x3 << 26)
#घोषणा SE_YSEL(x)				((x) << 28)
#घोषणा SE_YSEL_MASK				(0x3 << 28)

/* mmPA_SC_RASTER_CONFIG_1 mask */
#घोषणा SE_PAIR_MAP(x)				((x) << 0)
#घोषणा SE_PAIR_MAP_MASK			(0x3 << 0)
#घोषणा SE_PAIR_XSEL(x)				((x) << 2)
#घोषणा SE_PAIR_XSEL_MASK			(0x3 << 2)
#घोषणा SE_PAIR_YSEL(x)				((x) << 4)
#घोषणा SE_PAIR_YSEL_MASK			(0x3 << 4)

#पूर्ण_अगर
