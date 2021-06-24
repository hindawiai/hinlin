<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
 */
#अगर_अघोषित SI_ENUMS_H
#घोषणा SI_ENUMS_H

#घोषणा VBLANK_INT_MASK                (1 << 0)
#घोषणा DC_HPDx_INT_EN                 (1 << 16)
#घोषणा VBLANK_ACK                     (1 << 4)
#घोषणा VLINE_ACK                      (1 << 4)

#घोषणा CURSOR_WIDTH 64
#घोषणा CURSOR_HEIGHT 64

#घोषणा VGA_VSTATUS_CNTL               0xFFFCFFFF
#घोषणा PRIORITY_MARK_MASK             0x7fff
#घोषणा PRIORITY_OFF                   (1 << 16)
#घोषणा PRIORITY_ALWAYS_ON             (1 << 20)
#घोषणा INTERLEAVE_EN                  (1 << 0)

#घोषणा LATENCY_WATERMARK_MASK(x)      ((x) << 16)
#घोषणा DC_LB_MEMORY_CONFIG(x)         ((x) << 20)
#घोषणा ICON_DEGAMMA_MODE(x)           (((x) & 0x3) << 8)

#घोषणा GRPH_ENDIAN_SWAP(x)            (((x) & 0x3) << 0)
#घोषणा GRPH_ENDIAN_NONE               0
#घोषणा GRPH_ENDIAN_8IN16              1
#घोषणा GRPH_ENDIAN_8IN32              2
#घोषणा GRPH_ENDIAN_8IN64              3
#घोषणा GRPH_RED_CROSSBAR(x)           (((x) & 0x3) << 4)
#घोषणा GRPH_RED_SEL_R                 0
#घोषणा GRPH_RED_SEL_G                 1
#घोषणा GRPH_RED_SEL_B                 2
#घोषणा GRPH_RED_SEL_A                 3
#घोषणा GRPH_GREEN_CROSSBAR(x)         (((x) & 0x3) << 6)
#घोषणा GRPH_GREEN_SEL_G               0
#घोषणा GRPH_GREEN_SEL_B               1
#घोषणा GRPH_GREEN_SEL_A               2
#घोषणा GRPH_GREEN_SEL_R               3
#घोषणा GRPH_BLUE_CROSSBAR(x)          (((x) & 0x3) << 8)
#घोषणा GRPH_BLUE_SEL_B                0
#घोषणा GRPH_BLUE_SEL_A                1
#घोषणा GRPH_BLUE_SEL_R                2
#घोषणा GRPH_BLUE_SEL_G                3
#घोषणा GRPH_ALPHA_CROSSBAR(x)         (((x) & 0x3) << 10)
#घोषणा GRPH_ALPHA_SEL_A               0
#घोषणा GRPH_ALPHA_SEL_R               1
#घोषणा GRPH_ALPHA_SEL_G               2
#घोषणा GRPH_ALPHA_SEL_B               3

#घोषणा GRPH_DEPTH(x)                  (((x) & 0x3) << 0)
#घोषणा GRPH_DEPTH_8BPP                0
#घोषणा GRPH_DEPTH_16BPP               1
#घोषणा GRPH_DEPTH_32BPP               2

#घोषणा GRPH_FORMAT(x)                 (((x) & 0x7) << 8)
#घोषणा GRPH_FORMAT_INDEXED            0
#घोषणा GRPH_FORMAT_ARGB1555           0
#घोषणा GRPH_FORMAT_ARGB565            1
#घोषणा GRPH_FORMAT_ARGB4444           2
#घोषणा GRPH_FORMAT_AI88               3
#घोषणा GRPH_FORMAT_MONO16             4
#घोषणा GRPH_FORMAT_BGRA5551           5
#घोषणा GRPH_FORMAT_ARGB8888           0
#घोषणा GRPH_FORMAT_ARGB2101010        1
#घोषणा GRPH_FORMAT_32BPP_DIG          2
#घोषणा GRPH_FORMAT_8B_ARGB2101010     3
#घोषणा GRPH_FORMAT_BGRA1010102        4
#घोषणा GRPH_FORMAT_8B_BGRA1010102     5
#घोषणा GRPH_FORMAT_RGB111110          6
#घोषणा GRPH_FORMAT_BGR101111          7

#घोषणा GRPH_NUM_BANKS(x)              (((x) & 0x3) << 2)
#घोषणा GRPH_ARRAY_MODE(x)             (((x) & 0x7) << 20)
#घोषणा GRPH_ARRAY_LINEAR_GENERAL      0
#घोषणा GRPH_ARRAY_LINEAR_ALIGNED      1
#घोषणा GRPH_ARRAY_1D_TILED_THIN1      2
#घोषणा GRPH_ARRAY_2D_TILED_THIN1      4
#घोषणा GRPH_TILE_SPLIT(x)             (((x) & 0x7) << 13)
#घोषणा GRPH_BANK_WIDTH(x)             (((x) & 0x3) << 6)
#घोषणा GRPH_BANK_HEIGHT(x)            (((x) & 0x3) << 11)
#घोषणा GRPH_MACRO_TILE_ASPECT(x)      (((x) & 0x3) << 18)
#घोषणा GRPH_ARRAY_MODE(x)             (((x) & 0x7) << 20)
#घोषणा GRPH_PIPE_CONFIG(x)                   (((x) & 0x1f) << 24)

#घोषणा CURSOR_EN                      (1 << 0)
#घोषणा CURSOR_MODE(x)                 (((x) & 0x3) << 8)
#घोषणा CURSOR_MONO                    0
#घोषणा CURSOR_24_1                    1
#घोषणा CURSOR_24_8_PRE_MULT           2
#घोषणा CURSOR_24_8_UNPRE_MULT         3
#घोषणा CURSOR_2X_MAGNIFY              (1 << 16)
#घोषणा CURSOR_FORCE_MC_ON             (1 << 20)
#घोषणा CURSOR_URGENT_CONTROL(x)       (((x) & 0x7) << 24)
#घोषणा CURSOR_URGENT_ALWAYS           0
#घोषणा CURSOR_URGENT_1_8              1
#घोषणा CURSOR_URGENT_1_4              2
#घोषणा CURSOR_URGENT_3_8              3
#घोषणा CURSOR_URGENT_1_2              4
#घोषणा CURSOR_UPDATE_PENDING          (1 << 0)
#घोषणा CURSOR_UPDATE_TAKEN            (1 << 1)
#घोषणा CURSOR_UPDATE_LOCK             (1 << 16)
#घोषणा CURSOR_DISABLE_MULTIPLE_UPDATE (1 << 24)

#घोषणा SI_CRTC0_REGISTER_OFFSET                0
#घोषणा SI_CRTC1_REGISTER_OFFSET                0x300
#घोषणा SI_CRTC2_REGISTER_OFFSET                0x2600
#घोषणा SI_CRTC3_REGISTER_OFFSET                0x2900
#घोषणा SI_CRTC4_REGISTER_OFFSET                0x2c00
#घोषणा SI_CRTC5_REGISTER_OFFSET                0x2f00

#घोषणा DMA0_REGISTER_OFFSET 0x000
#घोषणा DMA1_REGISTER_OFFSET 0x200
#घोषणा ES_AND_GS_AUTO       3
#घोषणा RADEON_PACKET_TYPE3  3
#घोषणा CE_PARTITION_BASE    3
#घोषणा BUF_SWAP_32BIT       (2 << 16)

#घोषणा GFX_POWER_STATUS                           (1 << 1)
#घोषणा GFX_CLOCK_STATUS                           (1 << 2)
#घोषणा GFX_LS_STATUS                              (1 << 3)
#घोषणा RLC_BUSY_STATUS                            (1 << 0)

#घोषणा RLC_PUD(x)                               ((x) << 0)
#घोषणा RLC_PUD_MASK                             (0xff << 0)
#घोषणा RLC_PDD(x)                               ((x) << 8)
#घोषणा RLC_PDD_MASK                             (0xff << 8)
#घोषणा RLC_TTPD(x)                              ((x) << 16)
#घोषणा RLC_TTPD_MASK                            (0xff << 16)
#घोषणा RLC_MSD(x)                               ((x) << 24)
#घोषणा RLC_MSD_MASK                             (0xff << 24)
#घोषणा WRITE_DATA_ENGINE_SEL(x) ((x) << 30)
#घोषणा WRITE_DATA_DST_SEL(x) ((x) << 8)
#घोषणा EVENT_TYPE(x) ((x) << 0)
#घोषणा EVENT_INDEX(x) ((x) << 8)
#घोषणा WAIT_REG_MEM_MEM_SPACE(x)               ((x) << 4)
#घोषणा WAIT_REG_MEM_FUNCTION(x)                ((x) << 0)
#घोषणा WAIT_REG_MEM_ENGINE(x)                  ((x) << 8)

#घोषणा GFX6_NUM_GFX_RINGS     1
#घोषणा GFX6_NUM_COMPUTE_RINGS 2
#घोषणा RLC_SAVE_AND_RESTORE_STARTING_OFFSET 0x90
#घोषणा RLC_CLEAR_STATE_DESCRIPTOR_OFFSET    0x3D

#घोषणा TAHITI_GB_ADDR_CONFIG_GOLDEN        0x12011003
#घोषणा VERDE_GB_ADDR_CONFIG_GOLDEN         0x02010002
#घोषणा HAIन_अंक_GB_ADDR_CONFIG_GOLDEN        0x02011003

#घोषणा PACKET3(op, n)  ((RADEON_PACKET_TYPE3 << 30) |                  \
                         (((op) & 0xFF) << 8) |                         \
                         ((n) & 0x3FFF) << 16)
#घोषणा PACKET3_COMPUTE(op, n) (PACKET3(op, n) | 1 << 1)
#घोषणा	PACKET3_NOP					0x10
#घोषणा	PACKET3_SET_BASE				0x11
#घोषणा		PACKET3_BASE_INDEX(x)                  ((x) << 0)
#घोषणा	PACKET3_CLEAR_STATE				0x12
#घोषणा	PACKET3_INDEX_BUFFER_SIZE			0x13
#घोषणा	PACKET3_DISPATCH_सूचीECT				0x15
#घोषणा	PACKET3_DISPATCH_INसूचीECT			0x16
#घोषणा	PACKET3_ALLOC_GDS				0x1B
#घोषणा	PACKET3_WRITE_GDS_RAM				0x1C
#घोषणा	PACKET3_ATOMIC_GDS				0x1D
#घोषणा	PACKET3_ATOMIC					0x1E
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
#घोषणा	PACKET3_DRAW_INDEX_IMMD				0x2E
#घोषणा	PACKET3_NUM_INSTANCES				0x2F
#घोषणा	PACKET3_DRAW_INDEX_MULTI_AUTO			0x30
#घोषणा	PACKET3_INसूचीECT_BUFFER_CONST			0x31
#घोषणा	PACKET3_INसूचीECT_BUFFER				0x3F
#घोषणा	PACKET3_STRMOUT_BUFFER_UPDATE			0x34
#घोषणा	PACKET3_DRAW_INDEX_OFFSET_2			0x35
#घोषणा	PACKET3_DRAW_INDEX_MULTI_ELEMENT		0x36
#घोषणा	PACKET3_WRITE_DATA				0x37
#घोषणा	PACKET3_DRAW_INDEX_INसूचीECT_MULTI		0x38
#घोषणा	PACKET3_MEM_SEMAPHORE				0x39
#घोषणा	PACKET3_MPEG_INDEX				0x3A
#घोषणा	PACKET3_COPY_DW					0x3B
#घोषणा	PACKET3_WAIT_REG_MEM				0x3C
#घोषणा	PACKET3_MEM_WRITE				0x3D
#घोषणा	PACKET3_COPY_DATA				0x40
#घोषणा	PACKET3_CP_DMA					0x41
#              define PACKET3_CP_DMA_DST_SEL(x)    ((x) << 20)
#              define PACKET3_CP_DMA_ENGINE(x)     ((x) << 27)
#              define PACKET3_CP_DMA_SRC_SEL(x)    ((x) << 29)
#              define PACKET3_CP_DMA_CP_SYNC       (1 << 31)
#              define PACKET3_CP_DMA_DIS_WC        (1 << 21)
#              define PACKET3_CP_DMA_CMD_SRC_SWAP(x) ((x) << 22)
#              define PACKET3_CP_DMA_CMD_DST_SWAP(x) ((x) << 24)
#              define PACKET3_CP_DMA_CMD_SAS       (1 << 26)
#              define PACKET3_CP_DMA_CMD_DAS       (1 << 27)
#              define PACKET3_CP_DMA_CMD_SAIC      (1 << 28)
#              define PACKET3_CP_DMA_CMD_DAIC      (1 << 29)
#              define PACKET3_CP_DMA_CMD_RAW_WAIT  (1 << 30)
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
#              define PACKET3_DEST_BASE_2_ENA      (1 << 19)
#              define PACKET3_DEST_BASE_3_ENA      (1 << 21)
#              define PACKET3_TCL1_ACTION_ENA      (1 << 22)
#              define PACKET3_TC_ACTION_ENA        (1 << 23)
#              define PACKET3_CB_ACTION_ENA        (1 << 25)
#              define PACKET3_DB_ACTION_ENA        (1 << 26)
#              define PACKET3_SH_KCACHE_ACTION_ENA (1 << 27)
#              define PACKET3_SH_ICACHE_ACTION_ENA (1 << 29)
#घोषणा	PACKET3_ME_INITIALIZE				0x44
#घोषणा		PACKET3_ME_INITIALIZE_DEVICE_ID(x) ((x) << 16)
#घोषणा	PACKET3_COND_WRITE				0x45
#घोषणा	PACKET3_EVENT_WRITE				0x46
#घोषणा	PACKET3_EVENT_WRITE_EOP				0x47
#घोषणा	PACKET3_EVENT_WRITE_EOS				0x48
#घोषणा	PACKET3_PREAMBLE_CNTL				0x4A
#              define PACKET3_PREAMBLE_BEGIN_CLEAR_STATE     (2 << 28)
#              define PACKET3_PREAMBLE_END_CLEAR_STATE       (3 << 28)
#घोषणा	PACKET3_ONE_REG_WRITE				0x57
#घोषणा	PACKET3_LOAD_CONFIG_REG				0x5F
#घोषणा	PACKET3_LOAD_CONTEXT_REG			0x60
#घोषणा	PACKET3_LOAD_SH_REG				0x61
#घोषणा	PACKET3_SET_CONFIG_REG				0x68
#घोषणा		PACKET3_SET_CONFIG_REG_START			0x00002000
#घोषणा		PACKET3_SET_CONFIG_REG_END			0x00002c00
#घोषणा	PACKET3_SET_CONTEXT_REG				0x69
#घोषणा		PACKET3_SET_CONTEXT_REG_START			0x000a000
#घोषणा		PACKET3_SET_CONTEXT_REG_END			0x000a400
#घोषणा	PACKET3_SET_CONTEXT_REG_INसूचीECT		0x73
#घोषणा	PACKET3_SET_RESOURCE_INसूचीECT			0x74
#घोषणा	PACKET3_SET_SH_REG				0x76
#घोषणा		PACKET3_SET_SH_REG_START			0x00002c00
#घोषणा		PACKET3_SET_SH_REG_END				0x00003000
#घोषणा	PACKET3_SET_SH_REG_OFFSET			0x77
#घोषणा	PACKET3_ME_WRITE				0x7A
#घोषणा	PACKET3_SCRATCH_RAM_WRITE			0x7D
#घोषणा	PACKET3_SCRATCH_RAM_READ			0x7E
#घोषणा	PACKET3_CE_WRITE				0x7F
#घोषणा	PACKET3_LOAD_CONST_RAM				0x80
#घोषणा	PACKET3_WRITE_CONST_RAM				0x81
#घोषणा	PACKET3_WRITE_CONST_RAM_OFFSET			0x82
#घोषणा	PACKET3_DUMP_CONST_RAM				0x83
#घोषणा	PACKET3_INCREMENT_CE_COUNTER			0x84
#घोषणा	PACKET3_INCREMENT_DE_COUNTER			0x85
#घोषणा	PACKET3_WAIT_ON_CE_COUNTER			0x86
#घोषणा	PACKET3_WAIT_ON_DE_COUNTER			0x87
#घोषणा	PACKET3_WAIT_ON_DE_COUNTER_DIFF			0x88
#घोषणा	PACKET3_SET_CE_DE_COUNTERS			0x89
#घोषणा	PACKET3_WAIT_ON_AVAIL_BUFFER			0x8A
#घोषणा	PACKET3_SWITCH_BUFFER				0x8B
#घोषणा PACKET3_SEM_WAIT_ON_SIGNAL    (0x1 << 12)
#घोषणा PACKET3_SEM_SEL_SIGNAL	    (0x6 << 29)
#घोषणा PACKET3_SEM_SEL_WAIT	    (0x7 << 29)

#पूर्ण_अगर
