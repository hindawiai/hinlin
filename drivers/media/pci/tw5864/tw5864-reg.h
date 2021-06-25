<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  TW5864 driver - रेजिस्टरs description
 *
 *  Copyright (C) 2016 Bluecherry, LLC <मुख्यtainers@bluecherrydvr.com>
 */

/* According to TW5864_datasheet_0.6d.pdf, tw5864b1-ds.pdf */

/* Register Description - Direct Map Space */
/* 0x0000 ~ 0x1ffc - H264 Register Map */
/* [15:0] The Version रेजिस्टर क्रम H264 core (Read Only) */
#घोषणा TW5864_H264REV 0x0000

#घोषणा TW5864_EMU 0x0004
/* Define controls in रेजिस्टर TW5864_EMU */
/* DDR controller enabled */
#घोषणा TW5864_EMU_EN_DDR BIT(0)
/* Enable bit क्रम Inter module */
#घोषणा TW5864_EMU_EN_ME BIT(1)
/* Enable bit क्रम Sensor Interface module */
#घोषणा TW5864_EMU_EN_SEN BIT(2)
/* Enable bit क्रम Host Burst Access */
#घोषणा TW5864_EMU_EN_BHOST BIT(3)
/* Enable bit क्रम Loop Filter module */
#घोषणा TW5864_EMU_EN_LPF BIT(4)
/* Enable bit क्रम PLBK module */
#घोषणा TW5864_EMU_EN_PLBK BIT(5)
/*
 * Video Frame mapping in DDR
 * 00 CIF
 * 01 D1
 * 10 Reserved
 * 11 Reserved
 *
 */
#घोषणा TW5864_DSP_FRAME_TYPE (3 << 6)
#घोषणा TW5864_DSP_FRAME_TYPE_D1 BIT(6)

#घोषणा TW5864_UNDECLARED_H264REV_PART2 0x0008

#घोषणा TW5864_SLICE 0x000c
/* Define controls in रेजिस्टर TW5864_SLICE */
/* VLC Slice end flag */
#घोषणा TW5864_VLC_SLICE_END BIT(0)
/* Master Slice End Flag */
#घोषणा TW5864_MAS_SLICE_END BIT(4)
/* Host to start a new slice Address */
#घोषणा TW5864_START_NSLICE BIT(15)

/*
 * [15:0] Two bit क्रम each channel (channel 0 ~ 7). Each two bits are the buffer
 * poपूर्णांकer क्रम the last encoded frame of the corresponding channel.
 */
#घोषणा TW5864_ENC_BUF_PTR_REC1 0x0010

/* [5:0] DSP_MB_QP and [15:10] DSP_LPF_OFFSET */
#घोषणा TW5864_DSP_QP 0x0018
/* Define controls in रेजिस्टर TW5864_DSP_QP */
/* [5:0] H264 QP Value क्रम codec */
#घोषणा TW5864_DSP_MB_QP 0x003f
/*
 * [15:10] H264 LPF_OFFSET Address
 * (Default 0)
 */
#घोषणा TW5864_DSP_LPF_OFFSET 0xfc00

#घोषणा TW5864_DSP_CODEC 0x001c
/* Define controls in रेजिस्टर TW5864_DSP_CODEC */
/*
 * 0: Encode (TW5864 Default)
 * 1: Decode
 */
#घोषणा TW5864_DSP_CODEC_MODE BIT(0)
/*
 * 0->3 4 VLC data buffer in DDR (1M each)
 * 0->7 8 VLC data buffer in DDR (512k each)
 */
#घोषणा TW5864_VLC_BUF_ID (7 << 2)
/*
 * 0 4CIF in 1 MB
 * 1 1CIF in 1 MB
 */
#घोषणा TW5864_CIF_MAP_MD BIT(6)
/*
 * 0 2 falf D1 in 1 MB
 * 1 1 half D1 in 1 MB
 */
#घोषणा TW5864_HD1_MAP_MD BIT(7)
/* VLC Stream valid */
#घोषणा TW5864_VLC_VLD BIT(8)
/* MV Vector Valid */
#घोषणा TW5864_MV_VECT_VLD BIT(9)
/* MV Flag Valid */
#घोषणा TW5864_MV_FLAG_VLD BIT(10)

#घोषणा TW5864_DSP_SEN 0x0020
/* Define controls in रेजिस्टर TW5864_DSP_SEN */
/* Org Buffer Base क्रम Luma (शेष 0) */
#घोषणा TW5864_DSP_SEN_PIC_LU 0x000f
/* Org Buffer Base क्रम Chroma (शेष 4) */
#घोषणा TW5864_DSP_SEN_PIC_CHM 0x00f0
/* Maximum Number of Buffers (शेष 4) */
#घोषणा TW5864_DSP_SEN_PIC_MAX 0x0700
/*
 * Original Frame D1 or HD1 चयन
 * (Default 0)
 */
#घोषणा TW5864_DSP_SEN_HFULL 0x1000

#घोषणा TW5864_DSP_REF_PIC 0x0024
/* Define controls in रेजिस्टर TW5864_DSP_REF_PIC */
/* Ref Buffer Base क्रम Luma (शेष 0) */
#घोषणा TW5864_DSP_REF_PIC_LU 0x000f
/* Ref Buffer Base क्रम Chroma (शेष 4) */
#घोषणा TW5864_DSP_REF_PIC_CHM 0x00f0
/* Maximum Number of Buffers (शेष 4) */
#घोषणा TW5864_DSP_REF_PIC_MAX 0x0700

/* [15:0] SEN_EN_CH[n] SENIF original frame capture enable क्रम each channel */
#घोषणा TW5864_SEN_EN_CH 0x0028

#घोषणा TW5864_DSP 0x002c
/* Define controls in रेजिस्टर TW5864_DSP */
/* The ID क्रम channel selected क्रम encoding operation */
#घोषणा TW5864_DSP_ENC_CHN 0x000f
/* See DSP_MB_DELAY below */
#घोषणा TW5864_DSP_MB_WAIT 0x0010
/*
 * DSP Chroma Switch
 * 0 DDRB
 * 1 DDRA
 */
#घोषणा TW5864_DSP_CHROM_SW 0x0020
/* VLC Flow Control: 1 क्रम enable */
#घोषणा TW5864_DSP_FLW_CNTL 0x0040
/*
 * If DSP_MB_WAIT == 0, MB delay is DSP_MB_DELAY * 16
 * If DSP_MB_DELAY == 1, MB delay is DSP_MB_DELAY * 128
 */
#घोषणा TW5864_DSP_MB_DELAY 0x0f00

#घोषणा TW5864_DDR 0x0030
/* Define controls in रेजिस्टर TW5864_DDR */
/* DDR Single Access Page Number */
#घोषणा TW5864_DDR_PAGE_CNTL 0x00ff
/* DDR-DPR Burst Read Enable */
#घोषणा TW5864_DDR_BRST_EN BIT(13)
/*
 * DDR A/B Select as HOST access
 * 0 Select DDRA
 * 1 Select DDRB
 */
#घोषणा TW5864_DDR_AB_SEL BIT(14)
/*
 * DDR Access Mode Select
 * 0 Single R/W Access (Host <-> DDR)
 * 1 Burst R/W Access (Host <-> DPR)
 */
#घोषणा TW5864_DDR_MODE BIT(15)

/* The original frame capture poपूर्णांकer. Two bits क्रम each channel */
/* SENIF_ORG_FRM_PTR [15:0] */
#घोषणा TW5864_SENIF_ORG_FRM_PTR1 0x0038
/* SENIF_ORG_FRM_PTR [31:16] */
#घोषणा TW5864_SENIF_ORG_FRM_PTR2 0x003c

#घोषणा TW5864_DSP_SEN_MODE 0x0040
/* Define controls in रेजिस्टर TW5864_DSP_SEN_MODE */
#घोषणा TW5864_DSP_SEN_MODE_CH0 0x000f
#घोषणा TW5864_DSP_SEN_MODE_CH1 0x00f0

/*
 * [15:0]: ENC_BUF_PTR_REC[31:16] Two bit क्रम each channel (channel 8 ~ 15).
 * Each two bits are the buffer poपूर्णांकer क्रम the last encoded frame of a channel
 */
#घोषणा TW5864_ENC_BUF_PTR_REC2 0x004c

/* Current MV Flag Status Poपूर्णांकer क्रम Channel n. (Read only) */
/*
 * [1:0] CH0_MV_PTR, ..., [15:14] CH7_MV_PTR
 */
#घोषणा TW5864_CH_MV_PTR1 0x0060
/*
 * [1:0] CH8_MV_PTR, ..., [15:14] CH15_MV_PTR
 */
#घोषणा TW5864_CH_MV_PTR2 0x0064

/*
 * [15:0] Reset Current MV Flag Status Poपूर्णांकer क्रम Channel n (one bit each)
 */
#घोषणा TW5864_RST_MV_PTR 0x0068
#घोषणा TW5864_INTERLACING 0x0200
/* Define controls in रेजिस्टर TW5864_INTERLACING */
/*
 * Inter_Mode Start. 2-nd bit? A guess. Missing in datasheet. Without this bit
 * set, the output video is पूर्णांकerlaced (stripy).
 */
#घोषणा TW5864_DSP_INTER_ST BIT(1)
/* Deपूर्णांकerlacer Enable */
#घोषणा TW5864_DI_EN BIT(2)
/*
 * De-पूर्णांकerlacer Mode
 * 1 Shuffled frame
 * 0 Normal Un-Shuffled Frame
 */
#घोषणा TW5864_DI_MD BIT(3)
/*
 * Down scale original frame in X direction
 * 11: Un-used
 * 10: करोwn-sample to 1/4
 * 01: करोwn-sample to 1/2
 * 00: करोwn-sample disabled
 */
#घोषणा TW5864_DSP_DWN_X (3 << 4)
/*
 * Down scale original frame in Y direction
 * 11: Un-used
 * 10: करोwn-sample to 1/4
 * 01: करोwn-sample to 1/2
 * 00: करोwn-sample disabled
 */
#घोषणा TW5864_DSP_DWN_Y (3 << 6)
/*
 * 1 Dual Stream
 * 0 Single Stream
 */
#घोषणा TW5864_DUAL_STR BIT(8)

#घोषणा TW5864_DSP_REF 0x0204
/* Define controls in रेजिस्टर TW5864_DSP_REF */
/* Number of reference frame (Default 1 क्रम TW5864B) */
#घोषणा TW5864_DSP_REF_FRM 0x000f
/* Winकरोw size */
#घोषणा TW5864_DSP_WIN_SIZE 0x02f0

#घोषणा TW5864_DSP_SKIP 0x0208
/* Define controls in रेजिस्टर TW5864_DSP_SKIP */
/*
 * Skip Offset Enable bit
 * 0 DSP_SKIP_OFFSET value is not used (शेष 8)
 * 1 DSP_SKIP_OFFSET value is used in HW
 */
#घोषणा TW5864_DSP_SKIP_OFEN 0x0080
/* Skip mode cost offset (शेष 8) */
#घोषणा TW5864_DSP_SKIP_OFFSET 0x007f

#घोषणा TW5864_MOTION_SEARCH_ETC 0x020c
/* Define controls in रेजिस्टर TW5864_MOTION_SEARCH_ETC */
/* Enable quarter pel search mode */
#घोषणा TW5864_QPEL_EN BIT(0)
/* Enable half pel search mode */
#घोषणा TW5864_HPEL_EN BIT(1)
/* Enable motion search mode */
#घोषणा TW5864_ME_EN BIT(2)
/* Enable Intra mode */
#घोषणा TW5864_INTRA_EN BIT(3)
/* Enable Skip Mode */
#घोषणा TW5864_SKIP_EN BIT(4)
/* Search Option (Default 2"b01) */
#घोषणा TW5864_SRCH_OPT (3 << 5)

#घोषणा TW5864_DSP_ENC_REC 0x0210
/* Define controls in रेजिस्टर TW5864_DSP_ENC_REC */
/* Reference Buffer Poपूर्णांकer क्रम encoding */
#घोषणा TW5864_DSP_ENC_REF_PTR 0x0007
/* Reस्थिरruct Buffer poपूर्णांकer */
#घोषणा TW5864_DSP_REC_BUF_PTR 0x7000

/* [15:0] Lambda Value क्रम H264 */
#घोषणा TW5864_DSP_REF_MVP_LAMBDA 0x0214

#घोषणा TW5864_DSP_PIC_MAX_MB 0x0218
/* Define controls in रेजिस्टर TW5864_DSP_PIC_MAX_MB */
/* The MB number in Y direction क्रम a frame */
#घोषणा TW5864_DSP_PIC_MAX_MB_Y 0x007f
/* The MB number in X direction क्रम a frame */
#घोषणा TW5864_DSP_PIC_MAX_MB_X 0x7f00

/* The original frame poपूर्णांकer क्रम encoding */
#घोषणा TW5864_DSP_ENC_ORG_PTR_REG 0x021c
/* Mask to use with TW5864_DSP_ENC_ORG_PTR */
#घोषणा TW5864_DSP_ENC_ORG_PTR_MASK 0x7000
/* Number of bits to shअगरt with TW5864_DSP_ENC_ORG_PTR */
#घोषणा TW5864_DSP_ENC_ORG_PTR_SHIFT 12

/* DDR base address of OSD rectangle attribute data */
#घोषणा TW5864_DSP_OSD_ATTRI_BASE 0x0220
/* OSD enable bit क्रम each channel */
#घोषणा TW5864_DSP_OSD_ENABLE 0x0228

/* 0x0280 ~ 0x029c ै  Motion Vector क्रम 1st 4x4 Block, e.g., 80 (X), 84 (Y) */
#घोषणा TW5864_ME_MV_VEC1 0x0280
/* 0x02a0 ~ 0x02bc ै  Motion Vector क्रम 2nd 4x4 Block, e.g., A0 (X), A4 (Y) */
#घोषणा TW5864_ME_MV_VEC2 0x02a0
/* 0x02c0 ~ 0x02dc ै  Motion Vector क्रम 3rd 4x4 Block, e.g., C0 (X), C4 (Y) */
#घोषणा TW5864_ME_MV_VEC3 0x02c0
/* 0x02e0 ~ 0x02fc ै  Motion Vector क्रम 4th 4x4 Block, e.g., E0 (X), E4 (Y) */
#घोषणा TW5864_ME_MV_VEC4 0x02e0

/*
 * [5:0]
 * अगर (पूर्णांकra16x16_cost < (पूर्णांकra4x4_cost+dsp_i4x4_offset))
 * Intra_mode = पूर्णांकra16x16_mode
 * Else
 * Intra_mode = पूर्णांकra4x4_mode
 */
#घोषणा TW5864_DSP_I4x4_OFFSET 0x040c

/*
 * [6:4]
 * 0x5 Only 4x4
 * 0x6 Only 16x16
 * 0x7 16x16 & 4x4
 */
#घोषणा TW5864_DSP_INTRA_MODE 0x0410
#घोषणा TW5864_DSP_INTRA_MODE_SHIFT 4
#घोषणा TW5864_DSP_INTRA_MODE_MASK (7 << 4)
#घोषणा TW5864_DSP_INTRA_MODE_4x4 0x5
#घोषणा TW5864_DSP_INTRA_MODE_16x16 0x6
#घोषणा TW5864_DSP_INTRA_MODE_4x4_AND_16x16 0x7
/*
 * [5:0] WEIGHT Factor क्रम I4x4 cost calculation (QP dependent)
 */
#घोषणा TW5864_DSP_I4x4_WEIGHT 0x0414

/*
 * [7:0] Offset used to affect Intra/ME model decision
 * If (me_cost < पूर्णांकra_cost + dsp_resid_mode_offset)
 * Pred_Mode = me_mode
 * Else
 * Pred_mode = पूर्णांकra_mode
 */
#घोषणा TW5864_DSP_RESID_MODE_OFFSET 0x0604

/* 0x0800 ~ 0x09ff - Quantization TABLE Values */
#घोषणा TW5864_QUAN_TAB 0x0800

/* Valid channel value [0; f], frame value [0; 3] */
#घोषणा TW5864_RT_CNTR_CH_FRM(channel, frame) \
	(0x0c00 | (channel << 4) | (frame << 2))

#घोषणा TW5864_FRAME_BUS1 0x0d00
/*
 * 1 Progressive in part A in bus n
 * 0 Interlaced in part A in bus n
 */
#घोषणा TW5864_PROG_A BIT(0)
/*
 * 1 Progressive in part B in bus n
 * 0 Interlaced in part B in bus n
 */
#घोषणा TW5864_PROG_B BIT(1)
/*
 * 1 Frame Mode in bus n
 * 0 Field Mode in bus n
 */
#घोषणा TW5864_FRAME BIT(2)
/*
 * 0 4CIF in bus n
 * 1 1D1 + 4 CIF in bus n
 * 2 2D1 in bus n
 */
#घोषणा TW5864_BUS_D1 (3 << 3)
/* Bus 1 goes in TW5864_FRAME_BUS1 in [4:0] */
/* Bus 2 goes in TW5864_FRAME_BUS1 in [12:8] */
#घोषणा TW5864_FRAME_BUS2 0x0d04
/* Bus 3 goes in TW5864_FRAME_BUS2 in [4:0] */
/* Bus 4 goes in TW5864_FRAME_BUS2 in [12:8] */

/* [15:0] Horizontal Mirror क्रम channel n */
#घोषणा TW5864_SENIF_HOR_MIR 0x0d08
/* [15:0] Vertical Mirror क्रम channel n */
#घोषणा TW5864_SENIF_VER_MIR 0x0d0c

/*
 * FRAME_WIDTH_BUSn_A
 * 0x15f: 4 CIF
 * 0x2cf: 1 D1 + 3 CIF
 * 0x2cf: 2 D1
 * FRAME_WIDTH_BUSn_B
 * 0x15f: 4 CIF
 * 0x2cf: 1 D1 + 3 CIF
 * 0x2cf: 2 D1
 * FRAME_HEIGHT_BUSn_A
 * 0x11f: 4CIF (PAL)
 * 0x23f: 1D1 + 3CIF (PAL)
 * 0x23f: 2 D1 (PAL)
 * 0x0ef: 4CIF (NTSC)
 * 0x1df: 1D1 + 3CIF (NTSC)
 * 0x1df: 2 D1 (NTSC)
 * FRAME_HEIGHT_BUSn_B
 * 0x11f: 4CIF (PAL)
 * 0x23f: 1D1 + 3CIF (PAL)
 * 0x23f: 2 D1 (PAL)
 * 0x0ef: 4CIF (NTSC)
 * 0x1df: 1D1 + 3CIF (NTSC)
 * 0x1df: 2 D1 (NTSC)
 */
#घोषणा TW5864_FRAME_WIDTH_BUS_A(bus) (0x0d10 + 0x0010 * bus)
#घोषणा TW5864_FRAME_WIDTH_BUS_B(bus) (0x0d14 + 0x0010 * bus)
#घोषणा TW5864_FRAME_HEIGHT_BUS_A(bus) (0x0d18 + 0x0010 * bus)
#घोषणा TW5864_FRAME_HEIGHT_BUS_B(bus) (0x0d1c + 0x0010 * bus)

/*
 * 1: the bus mapped Channel n Full D1
 * 0: the bus mapped Channel n Half D1
 */
#घोषणा TW5864_FULL_HALF_FLAG 0x0d50

/*
 * 0 The bus mapped Channel select partA Mode
 * 1 The bus mapped Channel select partB Mode
 */
#घोषणा TW5864_FULL_HALF_MODE_SEL 0x0d54

#घोषणा TW5864_VLC 0x1000
/* Define controls in रेजिस्टर TW5864_VLC */
/* QP Value used by H264 CAVLC */
#घोषणा TW5864_VLC_SLICE_QP 0x003f
/*
 * Swap byte order of VLC stream in d-word.
 * 1 Normal (VLC output= [31:0])
 * 0 Swap (VLC output=अणु[23:16],[31:24],[7:0], [15:8]पूर्ण)
 */
#घोषणा TW5864_VLC_BYTE_SWP BIT(6)
/* Enable Adding 03 circuit क्रम VLC stream */
#घोषणा TW5864_VLC_ADD03_EN BIT(7)
/* Number of bit क्रम VLC bit Align */
#घोषणा TW5864_VLC_BIT_ALIGN_SHIFT 8
#घोषणा TW5864_VLC_BIT_ALIGN_MASK (0x1f << 8)
/*
 * Synchronous Interface select क्रम VLC Stream
 * 1 CDC_VLCS_MAS पढ़ो VLC stream
 * 0 CPU पढ़ो VLC stream
 */
#घोषणा TW5864_VLC_INF_SEL BIT(13)
/* Enable VLC overflow control */
#घोषणा TW5864_VLC_OVFL_CNTL BIT(14)
/*
 * 1 PCI Master Mode
 * 0 Non PCI Master Mode
 */
#घोषणा TW5864_VLC_PCI_SEL BIT(15)
/*
 * 0 Enable Adding 03 to VLC header and stream
 * 1 Disable Adding 03 to VLC header of "00000001"
 */
#घोषणा TW5864_VLC_A03_DISAB BIT(16)
/*
 * Status of VLC stream in DDR (one bit क्रम each buffer)
 * 1 VLC is पढ़ोy in buffer n (HW set)
 * 0 VLC is not पढ़ोy in buffer n (SW clear)
 */
#घोषणा TW5864_VLC_BUF_RDY_SHIFT 24
#घोषणा TW5864_VLC_BUF_RDY_MASK (0xff << 24)

/* Total number of bit in the slice */
#घोषणा TW5864_SLICE_TOTAL_BIT 0x1004
/* Total number of bit in the residue */
#घोषणा TW5864_RES_TOTAL_BIT 0x1008

#घोषणा TW5864_VLC_BUF 0x100c
/* Define controls in रेजिस्टर TW5864_VLC_BUF */
/* VLC BK0 full status, ग_लिखो ै 1ै  to clear */
#घोषणा TW5864_VLC_BK0_FULL BIT(0)
/* VLC BK1 full status, ग_लिखो ै 1ै  to clear */
#घोषणा TW5864_VLC_BK1_FULL BIT(1)
/* VLC end slice status, ग_लिखो ै 1ै  to clear */
#घोषणा TW5864_VLC_END_SLICE BIT(2)
/* VLC Buffer overflow status, ग_लिखो ै 1ै  to clear */
#घोषणा TW5864_DSP_RD_OF BIT(3)
/* VLC string length in either buffer 0 or 1 at end of frame */
#घोषणा TW5864_VLC_STREAM_LEN_SHIFT 4
#घोषणा TW5864_VLC_STREAM_LEN_MASK (0x1ff << 4)

/* [15:0] Total coefficient number in a frame */
#घोषणा TW5864_TOTAL_COEF_NO 0x1010
/* [0] VLC Encoder Interrupt. Write ै 1ै  to clear */
#घोषणा TW5864_VLC_DSP_INTR 0x1014
/* [31:0] VLC stream CRC checksum */
#घोषणा TW5864_VLC_STREAM_CRC 0x1018

#घोषणा TW5864_VLC_RD 0x101c
/* Define controls in रेजिस्टर TW5864_VLC_RD */
/*
 * 1 Read VLC lookup Memory
 * 0 Read VLC Stream Memory
 */
#घोषणा TW5864_VLC_RD_MEM BIT(0)
/*
 * 1 Read VLC Stream Memory in burst mode
 * 0 Read VLC Stream Memory in single mode
 */
#घोषणा TW5864_VLC_RD_BRST BIT(1)

/* 0x2000 ~ 0x2ffc -- H264 Stream Memory Map */
/*
 * A word is 4 bytes. I.e.,
 * VLC_STREAM_MEM[0] address: 0x2000
 * VLC_STREAM_MEM[1] address: 0x2004
 * ...
 * VLC_STREAM_MEM[3FF] address: 0x2ffc
 */
#घोषणा TW5864_VLC_STREAM_MEM_START 0x2000
#घोषणा TW5864_VLC_STREAM_MEM_MAX_OFFSET 0x3ff
#घोषणा TW5864_VLC_STREAM_MEM(offset) (TW5864_VLC_STREAM_MEM_START + 4 * offset)

/* 0x4000 ~ 0x4ffc -- Audio Register Map */
/* [31:0] config 1ms cnt = Realसमय clk/1000 */
#घोषणा TW5864_CFG_1MS_CNT 0x4000

#घोषणा TW5864_ADPCM 0x4004
/* Define controls in रेजिस्टर TW5864_ADPCM */
/* ADPCM decoder enable */
#घोषणा TW5864_ADPCM_DEC BIT(0)
/* ADPCM input data enable */
#घोषणा TW5864_ADPCM_IN_DATA BIT(1)
/* ADPCM encoder enable */
#घोषणा TW5864_ADPCM_ENC BIT(2)

#घोषणा TW5864_AUD 0x4008
/* Define controls in रेजिस्टर TW5864_AUD */
/* Record path PCM Audio enable bit क्रम each channel */
#घोषणा TW5864_AUD_ORG_CH_EN 0x00ff
/* Speaker path PCM Audio Enable */
#घोषणा TW5864_SPK_ORG_EN BIT(16)
/*
 * 0 16bit
 * 1 8bit
 */
#घोषणा TW5864_AD_BIT_MODE BIT(17)
#घोषणा TW5864_AUD_TYPE_SHIFT 18
/*
 * 0 PCM
 * 3 ADPCM
 */
#घोषणा TW5864_AUD_TYPE (0xf << 18)
#घोषणा TW5864_AUD_SAMPLE_RATE_SHIFT 22
/*
 * 0 8K
 * 1 16K
 */
#घोषणा TW5864_AUD_SAMPLE_RATE (3 << 22)
/* Channel ID used to select audio channel (0 to 16) क्रम loopback */
#घोषणा TW5864_TESTLOOP_CHID_SHIFT 24
#घोषणा TW5864_TESTLOOP_CHID (0x1f << 24)
/* Enable AD Loopback Test */
#घोषणा TW5864_TEST_ADLOOP_EN BIT(30)
/*
 * 0 Asynchronous Mode or PCI target mode
 * 1 PCI Initiator Mode
 */
#घोषणा TW5864_AUD_MODE BIT(31)

#घोषणा TW5864_AUD_ADPCM 0x400c
/* Define controls in रेजिस्टर TW5864_AUD_ADPCM */
/* Record path ADPCM audio channel enable, one bit क्रम each */
#घोषणा TW5864_AUD_ADPCM_CH_EN 0x00ff
/* Speaker path ADPCM audio channel enable */
#घोषणा TW5864_SPK_ADPCM_EN BIT(16)

#घोषणा TW5864_PC_BLOCK_ADPCM_RD_NO 0x4018
#घोषणा TW5864_PC_BLOCK_ADPCM_RD_NO_MASK 0x1f

/*
 * For ADPCM_ENC_WR_PTR, ADPCM_ENC_RD_PTR (see below):
 * Bit[2:0] ch0
 * Bit[5:3] ch1
 * Bit[8:6] ch2
 * Bit[11:9] ch3
 * Bit[14:12] ch4
 * Bit[17:15] ch5
 * Bit[20:18] ch6
 * Bit[23:21] ch7
 * Bit[26:24] ch8
 * Bit[29:27] ch9
 * Bit[32:30] ch10
 * Bit[35:33] ch11
 * Bit[38:36] ch12
 * Bit[41:39] ch13
 * Bit[44:42] ch14
 * Bit[47:45] ch15
 * Bit[50:48] ch16
 */
#घोषणा TW5864_ADPCM_ENC_XX_MASK 0x3fff
#घोषणा TW5864_ADPCM_ENC_XX_PTR2_SHIFT 30
/* ADPCM_ENC_WR_PTR[29:0] */
#घोषणा TW5864_ADPCM_ENC_WR_PTR1 0x401c
/* ADPCM_ENC_WR_PTR[50:30] */
#घोषणा TW5864_ADPCM_ENC_WR_PTR2 0x4020

/* ADPCM_ENC_RD_PTR[29:0] */
#घोषणा TW5864_ADPCM_ENC_RD_PTR1 0x4024
/* ADPCM_ENC_RD_PTR[50:30] */
#घोषणा TW5864_ADPCM_ENC_RD_PTR2 0x4028

/* [3:0] rd ch0, [7:4] rd ch1, [11:8] wr ch0, [15:12] wr ch1 */
#घोषणा TW5864_ADPCM_DEC_RD_WR_PTR 0x402c

/*
 * For TW5864_AD_ORIG_WR_PTR, TW5864_AD_ORIG_RD_PTR:
 * Bit[3:0] ch0
 * Bit[7:4] ch1
 * Bit[11:8] ch2
 * Bit[15:12] ch3
 * Bit[19:16] ch4
 * Bit[23:20] ch5
 * Bit[27:24] ch6
 * Bit[31:28] ch7
 * Bit[35:32] ch8
 * Bit[39:36] ch9
 * Bit[43:40] ch10
 * Bit[47:44] ch11
 * Bit[51:48] ch12
 * Bit[55:52] ch13
 * Bit[59:56] ch14
 * Bit[63:60] ch15
 * Bit[67:64] ch16
 */
/* AD_ORIG_WR_PTR[31:0] */
#घोषणा TW5864_AD_ORIG_WR_PTR1 0x4030
/* AD_ORIG_WR_PTR[63:32] */
#घोषणा TW5864_AD_ORIG_WR_PTR2 0x4034
/* AD_ORIG_WR_PTR[67:64] */
#घोषणा TW5864_AD_ORIG_WR_PTR3 0x4038

/* AD_ORIG_RD_PTR[31:0] */
#घोषणा TW5864_AD_ORIG_RD_PTR1 0x403c
/* AD_ORIG_RD_PTR[63:32] */
#घोषणा TW5864_AD_ORIG_RD_PTR2 0x4040
/* AD_ORIG_RD_PTR[67:64] */
#घोषणा TW5864_AD_ORIG_RD_PTR3 0x4044

#घोषणा TW5864_PC_BLOCK_ORIG_RD_NO 0x4048
#घोषणा TW5864_PC_BLOCK_ORIG_RD_NO_MASK 0x1f

#घोषणा TW5864_PCI_AUD 0x404c
/* Define controls in रेजिस्टर TW5864_PCI_AUD */
/*
 * The रेजिस्टर is applicable to PCI initiator mode only. Used to select PCM(0)
 * or ADPCM(1) audio data sent to PC. One bit क्रम each channel
 */
#घोषणा TW5864_PCI_DATA_SEL 0xffff
/*
 * Audio flow control mode selection bit.
 * 0 Flow control disabled. TW5864 continuously sends audio frame to PC
 * (initiator mode)
 * 1 Flow control enabled
 */
#घोषणा TW5864_PCI_FLOW_EN BIT(16)
/*
 * When PCI_FLOW_EN is set, PCI need to toggle this bit to send an audio frame
 * to PC. One toggle to send one frame.
 */
#घोषणा TW5864_PCI_AUD_FRM_EN BIT(17)

/* [1:0] CS valid to data valid CLK cycles when writing operation */
#घोषणा TW5864_CS2DAT_CNT 0x8000
/* [2:0] Data valid संकेत width by प्रणाली घड़ी cycles */
#घोषणा TW5864_DATA_VLD_WIDTH 0x8004

#घोषणा TW5864_SYNC 0x8008
/* Define controls in रेजिस्टर TW5864_SYNC */
/*
 * 0 vlc stream to syncrous port
 * 1 vlc stream to ddr buffers
 */
#घोषणा TW5864_SYNC_CFG BIT(7)
/*
 * 0 SYNC Address sampled on Rising edge
 * 1 SYNC Address sampled on Falling edge
 */
#घोषणा TW5864_SYNC_ADR_EDGE BIT(0)
#घोषणा TW5864_VLC_STR_DELAY_SHIFT 1
/*
 * 0 No प्रणाली delay
 * 1 One प्रणाली घड़ी delay
 * 2 Two प्रणाली घड़ी delay
 * 3 Three प्रणाली घड़ी delay
 */
#घोषणा TW5864_VLC_STR_DELAY (3 << 1)
/*
 * 0 Rising edge output
 * 1 Falling edge output
 */
#घोषणा TW5864_VLC_OUT_EDGE BIT(3)

/*
 * [1:0]
 * 2ै b00 phase set to 180 degree
 * 2ै b01 phase set to 270 degree
 * 2ै b10 phase set to 0 degree
 * 2ै b11 phase set to 90 degree
 */
#घोषणा TW5864_I2C_PHASE_CFG 0x800c

/*
 * The प्रणाली / DDR घड़ी (166 MHz) is generated with an on-chip प्रणाली घड़ी
 * PLL (SYSPLL) using input crystal घड़ी of 27 MHz. The प्रणाली घड़ी PLL
 * frequency is controlled with the following equation.
 * CLK_OUT = CLK_IN * (M+1) / ((N+1) * P)
 * SYSPLL_M M parameter
 * SYSPLL_N N parameter
 * SYSPLL_P P parameter
 */
/* SYSPLL_M[7:0] */
#घोषणा TW5864_SYSPLL1 0x8018
/* Define controls in रेजिस्टर TW5864_SYSPLL1 */
#घोषणा TW5864_SYSPLL_M_LOW 0x00ff

/* [2:0]: SYSPLL_M[10:8], [7:3]: SYSPLL_N[4:0] */
#घोषणा TW5864_SYSPLL2 0x8019
/* Define controls in रेजिस्टर TW5864_SYSPLL2 */
#घोषणा TW5864_SYSPLL_M_HI 0x07
#घोषणा TW5864_SYSPLL_N_LOW_SHIFT 3
#घोषणा TW5864_SYSPLL_N_LOW (0x1f << 3)

/*
 * [1:0]: SYSPLL_N[6:5], [3:2]: SYSPLL_P, [4]: SYSPLL_IREF, [7:5]: SYSPLL_CP_SEL
 */
#घोषणा TW5864_SYSPLL3 0x8020
/* Define controls in रेजिस्टर TW5864_SYSPLL3 */
#घोषणा TW5864_SYSPLL_N_HI 0x03
#घोषणा TW5864_SYSPLL_P_SHIFT 2
#घोषणा TW5864_SYSPLL_P (0x03 << 2)
/*
 * SYSPLL bias current control
 * 0 Lower current (शेष)
 * 1 30% higher current
 */
#घोषणा TW5864_SYSPLL_IREF BIT(4)
/*
 * SYSPLL अक्षरge pump current selection
 * 0 1,5 uA
 * 1 4 uA
 * 2 9 uA
 * 3 19 uA
 * 4 39 uA
 * 5 79 uA
 * 6 159 uA
 * 7 319 uA
 */
#घोषणा TW5864_SYSPLL_CP_SEL_SHIFT 5
#घोषणा TW5864_SYSPLL_CP_SEL (0x07 << 5)

/*
 * [1:0]: SYSPLL_VCO, [3:2]: SYSPLL_LP_X8, [5:4]: SYSPLL_ICP_SEL,
 * [6]: SYSPLL_LPF_5PF, [7]: SYSPLL_ED_SEL
 */
#घोषणा TW5864_SYSPLL4 0x8021
/* Define controls in रेजिस्टर TW5864_SYSPLL4 */
/*
 * SYSPLL_VCO VCO Range selection
 * 00 5 ~ 75 MHz
 * 01 50 ~ 140 MHz
 * 10 110 ~ 320 MHz
 * 11 270 ~ 700 MHz
 */
#घोषणा TW5864_SYSPLL_VCO 0x03
#घोषणा TW5864_SYSPLL_LP_X8_SHIFT 2
/*
 * Loop resister
 * 0 38.5K ohms
 * 1 6.6K ohms (शेष)
 * 2 2.2K ohms
 * 3 1.1K ohms
 */
#घोषणा TW5864_SYSPLL_LP_X8 (0x03 << 2)
#घोषणा TW5864_SYSPLL_ICP_SEL_SHIFT 4
/*
 * PLL अक्षरge pump fine tune
 * 00 x1 (शेष)
 * 01 x1/2
 * 10 x1/7
 * 11 x1/8
 */
#घोषणा TW5864_SYSPLL_ICP_SEL (0x03 << 4)
/*
 * PLL low pass filter phase margin adjusपंचांगent
 * 0 no 5pF (शेष)
 * 1 5pF added
 */
#घोषणा TW5864_SYSPLL_LPF_5PF BIT(6)
/*
 * PFD select edge क्रम detection
 * 0 Falling edge (शेष)
 * 1 Rising edge
 */
#घोषणा TW5864_SYSPLL_ED_SEL BIT(7)

/* [0]: SYSPLL_RST, [4]: SYSPLL_PD */
#घोषणा TW5864_SYSPLL5 0x8024
/* Define controls in रेजिस्टर TW5864_SYSPLL5 */
/* Reset SYSPLL */
#घोषणा TW5864_SYSPLL_RST BIT(0)
/* Power करोwn SYSPLL */
#घोषणा TW5864_SYSPLL_PD BIT(4)

#घोषणा TW5864_PLL_CFG 0x801c
/* Define controls in रेजिस्टर TW5864_PLL_CFG */
/*
 * Issue Soft Reset from Async Host Interface / PCI Interface घड़ी करोमुख्य.
 * Become valid after sync to the xtal घड़ी करोमुख्य. This bit is set only अगर
 * LOAD रेजिस्टर bit is also set to 1.
 */
#घोषणा TW5864_SRST BIT(0)
/*
 * Issue SYSPLL (166 MHz) configuration latch from Async host पूर्णांकerface / PCI
 * Interface घड़ी करोमुख्य. The configuration setting becomes effective only अगर
 * LOAD रेजिस्टर bit is also set to 1.
 */
#घोषणा TW5864_SYSPLL_CFG BIT(2)
/*
 * Issue SPLL (108 MHz) configuration load from Async host पूर्णांकerface / PCI
 * Interface घड़ी करोमुख्य. The configuration setting becomes effective only अगर
 * the LOAD रेजिस्टर bit is also set to 1.
 */
#घोषणा TW5864_SPLL_CFG BIT(4)
/*
 * Set this bit to latch the SRST, SYSPLL_CFG, SPLL_CFG setting पूर्णांकo the xtal
 * घड़ी करोमुख्य to restart the PLL. This bit is self cleared.
 */
#घोषणा TW5864_LOAD BIT(3)

/* SPLL_IREF, SPLL_LPX4, SPLL_CPX4, SPLL_PD, SPLL_DBG */
#घोषणा TW5864_SPLL 0x8028

/* 0x8800 ~ 0x88fc -- Interrupt Register Map */
/*
 * Trigger mode of पूर्णांकerrupt source 0 ~ 15
 * 1 Edge trigger mode
 * 0 Level trigger mode
 */
#घोषणा TW5864_TRIGGER_MODE_L 0x8800
/* Trigger mode of पूर्णांकerrupt source 16 ~ 31 */
#घोषणा TW5864_TRIGGER_MODE_H 0x8804
/* Enable of पूर्णांकerrupt source 0 ~ 15 */
#घोषणा TW5864_INTR_ENABLE_L 0x8808
/* Enable of पूर्णांकerrupt source 16 ~ 31 */
#घोषणा TW5864_INTR_ENABLE_H 0x880c
/* Clear पूर्णांकerrupt command of पूर्णांकerrupt source 0 ~ 15 */
#घोषणा TW5864_INTR_CLR_L 0x8810
/* Clear पूर्णांकerrupt command of पूर्णांकerrupt source 16 ~ 31 */
#घोषणा TW5864_INTR_CLR_H 0x8814
/*
 * Assertion of पूर्णांकerrupt source 0 ~ 15
 * 1 High level or pos-edge is निश्चितion
 * 0 Low level or neg-edge is निश्चितion
 */
#घोषणा TW5864_INTR_ASSERT_L 0x8818
/* Assertion of पूर्णांकerrupt source 16 ~ 31 */
#घोषणा TW5864_INTR_ASSERT_H 0x881c
/*
 * Output level of पूर्णांकerrupt
 * 1 Interrupt output is high निश्चितion
 * 0 Interrupt output is low निश्चितion
 */
#घोषणा TW5864_INTR_OUT_LEVEL 0x8820
/*
 * Status of पूर्णांकerrupt source 0 ~ 15
 * Bit[0]: VLC 4k RAM पूर्णांकerrupt
 * Bit[1]: BURST DDR RAM पूर्णांकerrupt
 * Bit[2]: MV DSP पूर्णांकerrupt
 * Bit[3]: video lost पूर्णांकerrupt
 * Bit[4]: gpio 0 पूर्णांकerrupt
 * Bit[5]: gpio 1 पूर्णांकerrupt
 * Bit[6]: gpio 2 पूर्णांकerrupt
 * Bit[7]: gpio 3 पूर्णांकerrupt
 * Bit[8]: gpio 4 पूर्णांकerrupt
 * Bit[9]: gpio 5 पूर्णांकerrupt
 * Bit[10]: gpio 6 पूर्णांकerrupt
 * Bit[11]: gpio 7 पूर्णांकerrupt
 * Bit[12]: JPEG पूर्णांकerrupt
 * Bit[13:15]: Reserved
 */
#घोषणा TW5864_INTR_STATUS_L 0x8838
/*
 * Status of पूर्णांकerrupt source 16 ~ 31
 * Bit[0]: Reserved
 * Bit[1]: VLC करोne पूर्णांकerrupt
 * Bit[2]: Reserved
 * Bit[3]: AD Vsync पूर्णांकerrupt
 * Bit[4]: Preview eof पूर्णांकerrupt
 * Bit[5]: Preview overflow पूर्णांकerrupt
 * Bit[6]: Timer पूर्णांकerrupt
 * Bit[7]: Reserved
 * Bit[8]: Audio eof पूर्णांकerrupt
 * Bit[9]: I2C करोne पूर्णांकerrupt
 * Bit[10]: AD पूर्णांकerrupt
 * Bit[11:15]: Reserved
 */
#घोषणा TW5864_INTR_STATUS_H 0x883c

/* Defines of पूर्णांकerrupt bits, united क्रम both low and high word रेजिस्टरs */
#घोषणा TW5864_INTR_VLC_RAM BIT(0)
#घोषणा TW5864_INTR_BURST BIT(1)
#घोषणा TW5864_INTR_MV_DSP BIT(2)
#घोषणा TW5864_INTR_VIN_LOST BIT(3)
/* n beदीर्घs to [0; 7] */
#घोषणा TW5864_INTR_GPIO(n) (1 << (4 + n))
#घोषणा TW5864_INTR_JPEG BIT(12)
#घोषणा TW5864_INTR_VLC_DONE BIT(17)
#घोषणा TW5864_INTR_AD_VSYNC BIT(19)
#घोषणा TW5864_INTR_PV_खातापूर्ण BIT(20)
#घोषणा TW5864_INTR_PV_OVERFLOW BIT(21)
#घोषणा TW5864_INTR_TIMER BIT(22)
#घोषणा TW5864_INTR_AUD_खातापूर्ण BIT(24)
#घोषणा TW5864_INTR_I2C_DONE BIT(25)
#घोषणा TW5864_INTR_AD BIT(26)

/* 0x9000 ~ 0x920c -- Video Capture (VIF) Register Map */
/*
 * H264EN_CH_STATUS[n] Status of Vsync synchronized H264EN_CH_EN (Read Only)
 * 1 Channel Enabled
 * 0 Channel Disabled
 */
#घोषणा TW5864_H264EN_CH_STATUS 0x9000
/*
 * [15:0] H264EN_CH_EN[n] H264 Encoding Path Enable क्रम channel
 * 1 Channel Enabled
 * 0 Channel Disabled
 */
#घोषणा TW5864_H264EN_CH_EN 0x9004
/*
 * H264EN_CH_DNS[n] H264 Encoding Path Downscale Video Decoder Input क्रम
 * channel n
 * 1 Downscale Y to 1/2
 * 0 Does not करोwnscale
 */
#घोषणा TW5864_H264EN_CH_DNS 0x9008
/*
 * H264EN_CH_PROG[n] H264 Encoding Path channel n is progressive
 * 1 Progressive (Not valid क्रम TW5864)
 * 0 Interlaced (TW5864 शेष)
 */
#घोषणा TW5864_H264EN_CH_PROG 0x900c
/*
 * [3:0] H264EN_BUS_MAX_CH[n]
 * H264 Encoding Path maximum number of channel on BUS n
 * 0 Max 4 channels
 * 1 Max 2 channels
 */
#घोषणा TW5864_H264EN_BUS_MAX_CH 0x9010

/*
 * H264EN_RATE_MAX_LINE_n H264 Encoding path Rate Mapping Maximum Line Number
 * on Bus n
 */
#घोषणा TW5864_H264EN_RATE_MAX_LINE_EVEN 0x1f
#घोषणा TW5864_H264EN_RATE_MAX_LINE_ODD_SHIFT 5
#घोषणा TW5864_H264EN_RATE_MAX_LINE_ODD (0x1f << 5)
/*
 * [4:0] H264EN_RATE_MAX_LINE_0
 * [9:5] H264EN_RATE_MAX_LINE_1
 */
#घोषणा TW5864_H264EN_RATE_MAX_LINE_REG1 0x9014
/*
 * [4:0] H264EN_RATE_MAX_LINE_2
 * [9:5] H264EN_RATE_MAX_LINE_3
 */
#घोषणा TW5864_H264EN_RATE_MAX_LINE_REG2 0x9018

/*
 * H264EN_CHn_FMT H264 Encoding Path Format configuration of Channel n
 * 00 D1 (For D1 and hD1 frame)
 * 01 (Reserved)
 * 10 (Reserved)
 * 11 D1 with 1/2 size in X (क्रम CIF frame)
 * Note: To be used with 0x9008 रेजिस्टर to configure the frame size
 */
/*
 * [1:0]: H264EN_CH0_FMT,
 * ..., [15:14]: H264EN_CH7_FMT
 */
#घोषणा TW5864_H264EN_CH_FMT_REG1 0x9020
/*
 * [1:0]: H264EN_CH8_FMT (?),
 * ..., [15:14]: H264EN_CH15_FMT (?)
 */
#घोषणा TW5864_H264EN_CH_FMT_REG2 0x9024

/*
 * H264EN_RATE_CNTL_BUSm_CHn H264 Encoding Path BUS m Rate Control क्रम Channel n
 */
#घोषणा TW5864_H264EN_RATE_CNTL_LO_WORD(bus, channel) \
	(0x9100 + bus * 0x20 + channel * 0x08)
#घोषणा TW5864_H264EN_RATE_CNTL_HI_WORD(bus, channel) \
	(0x9104 + bus * 0x20 + channel * 0x08)

/*
 * H264EN_BUSm_MAP_CHn The 16-to-1 MUX configuration रेजिस्टर क्रम each encoding
 * channel (total of 16 channels). Four bits क्रम each channel.
 */
#घोषणा TW5864_H264EN_BUS0_MAP 0x9200
#घोषणा TW5864_H264EN_BUS1_MAP 0x9204
#घोषणा TW5864_H264EN_BUS2_MAP 0x9208
#घोषणा TW5864_H264EN_BUS3_MAP 0x920c

/* This रेजिस्टर is not defined in datasheet, but used in reference driver */
#घोषणा TW5864_UNDECLARED_ERROR_FLAGS_0x9218 0x9218

#घोषणा TW5864_GPIO1 0x9800
#घोषणा TW5864_GPIO2 0x9804
/* Define controls in रेजिस्टरs TW5864_GPIO1, TW5864_GPIO2 */
/* GPIO DATA of Group n */
#घोषणा TW5864_GPIO_DATA 0x00ff
#घोषणा TW5864_GPIO_OEN_SHIFT 8
/* GPIO Output Enable of Group n */
#घोषणा TW5864_GPIO_OEN (0xff << 8)

/* 0xa000 ~ 0xa8ff ै  DDR Controller Register Map */
/* DDR Controller A */
/*
 * [2:0] Data valid counter after पढ़ो command to DDR. This is the delay value
 * to show how many cycles the data will be back from DDR after we issue a पढ़ो
 * command.
 */
#घोषणा TW5864_RD_ACK_VLD_MUX 0xa000

#घोषणा TW5864_DDR_PERIODS 0xa004
/* Define controls in रेजिस्टर TW5864_DDR_PERIODS */
/*
 * Tras value, the minimum cycle of active to preअक्षरge command period,
 * शेष is 7
 */
#घोषणा TW5864_TRAS_CNT_MAX 0x000f
/*
 * Trfc value, the minimum cycle of refresh to active or refresh command period,
 * शेष is 4"hf
 */
#घोषणा TW5864_RFC_CNT_MAX_SHIFT 8
#घोषणा TW5864_RFC_CNT_MAX (0x0f << 8)
/*
 * Trcd value, the minimum cycle of active to पूर्णांकernal पढ़ो/ग_लिखो command
 * period, शेष is 4"h2
 */
#घोषणा TW5864_TCD_CNT_MAX_SHIFT 4
#घोषणा TW5864_TCD_CNT_MAX (0x0f << 4)
/* Twr value, ग_लिखो recovery समय, शेष is 4"h3 */
#घोषणा TW5864_TWR_CNT_MAX_SHIFT 12
#घोषणा TW5864_TWR_CNT_MAX (0x0f << 12)

/*
 * [2:0] CAS latency, the delay cycle between पूर्णांकernal पढ़ो command and the
 * availability of the first bit of output data, शेष is 3
 */
#घोषणा TW5864_CAS_LATENCY 0xa008
/*
 * [15:0] Maximum average periodic refresh, the value is based on the current
 * frequency to match 7.8mcs
 */
#घोषणा TW5864_DDR_REF_CNTR_MAX 0xa00c
/*
 * DDR_ON_CHIP_MAP [1:0]
 * 0 256M DDR on board
 * 1 512M DDR on board
 * 2 1G DDR on board
 * DDR_ON_CHIP_MAP [2]
 * 0 Only one DDR chip
 * 1 Two DDR chips
 */
#घोषणा TW5864_DDR_ON_CHIP_MAP 0xa01c
#घोषणा TW5864_DDR_SELFTEST_MODE 0xa020
/* Define controls in रेजिस्टर TW5864_DDR_SELFTEST_MODE */
/*
 * 0 Common पढ़ो/ग_लिखो mode
 * 1 DDR self-test mode
 */
#घोषणा TW5864_MASTER_MODE BIT(0)
/*
 * 0 DDR self-test single पढ़ो/ग_लिखो
 * 1 DDR self-test burst पढ़ो/ग_लिखो
 */
#घोषणा TW5864_SINGLE_PROC BIT(1)
/*
 * 0 DDR self-test ग_लिखो command
 * 1 DDR self-test पढ़ो command
 */
#घोषणा TW5864_WRITE_FLAG BIT(2)
#घोषणा TW5864_DATA_MODE_SHIFT 4
/*
 * 0 ग_लिखो 32'haaaa5555 to DDR
 * 1 ग_लिखो 32'hffffffff to DDR
 * 2 ग_लिखो 32'hha5a55a5a to DDR
 * 3 ग_लिखो increasing data to DDR
 */
#घोषणा TW5864_DATA_MODE (0x3 << 4)

/* [7:0] The maximum data of one burst in DDR self-test mode */
#घोषणा TW5864_BURST_CNTR_MAX 0xa024
/* [15:0] The maximum burst counter (bit 15~0) in DDR self-test mode */
#घोषणा TW5864_DDR_PROC_CNTR_MAX_L 0xa028
/* The maximum burst counter (bit 31~16) in DDR self-test mode */
#घोषणा TW5864_DDR_PROC_CNTR_MAX_H 0xa02c
/* [0]: Start one DDR self-test */
#घोषणा TW5864_DDR_SELF_TEST_CMD 0xa030
/* The maximum error counter (bit 15 ~ 0) in DDR self-test */
#घोषणा TW5864_ERR_CNTR_L 0xa034

#घोषणा TW5864_ERR_CNTR_H_AND_FLAG 0xa038
/* Define controls in रेजिस्टर TW5864_ERR_CNTR_H_AND_FLAG */
/* The maximum error counter (bit 30 ~ 16) in DDR self-test */
#घोषणा TW5864_ERR_CNTR_H_MASK 0x3fff
/* DDR self-test end flag */
#घोषणा TW5864_END_FLAG 0x8000

/*
 * DDR Controller B: same as 0xa000 ~ 0xa038, but add TW5864_DDR_B_OFFSET to all
 * addresses
 */
#घोषणा TW5864_DDR_B_OFFSET 0x0800

/* 0xb004 ~ 0xb018 ै  HW version/ARB12 Register Map */
/* [15:0] Default is C013 */
#घोषणा TW5864_HW_VERSION 0xb004

#घोषणा TW5864_REQS_ENABLE 0xb010
/* Define controls in रेजिस्टर TW5864_REQS_ENABLE */
/* Audio data in to DDR enable (शेष 1) */
#घोषणा TW5864_AUD_DATA_IN_ENB BIT(0)
/* Audio encode request to DDR enable (शेष 1) */
#घोषणा TW5864_AUD_ENC_REQ_ENB BIT(1)
/* Audio decode request0 to DDR enable (शेष 1) */
#घोषणा TW5864_AUD_DEC_REQ0_ENB BIT(2)
/* Audio decode request1 to DDR enable (शेष 1) */
#घोषणा TW5864_AUD_DEC_REQ1_ENB BIT(3)
/* VLC stream request to DDR enable (शेष 1) */
#घोषणा TW5864_VLC_STRM_REQ_ENB BIT(4)
/* H264 MV request to DDR enable (शेष 1) */
#घोषणा TW5864_DVM_MV_REQ_ENB BIT(5)
/* mux_core MVD request to DDR enable (शेष 1) */
#घोषणा TW5864_MVD_REQ_ENB BIT(6)
/* mux_core MVD temp data request to DDR enable (शेष 1) */
#घोषणा TW5864_MVD_TMP_REQ_ENB BIT(7)
/* JPEG request to DDR enable (शेष 1) */
#घोषणा TW5864_JPEG_REQ_ENB BIT(8)
/* mv_flag request to DDR enable (शेष 1) */
#घोषणा TW5864_MV_FLAG_REQ_ENB BIT(9)

#घोषणा TW5864_ARB12 0xb018
/* Define controls in रेजिस्टर TW5864_ARB12 */
/* ARB12 Enable (शेष 1) */
#घोषणा TW5864_ARB12_ENB BIT(15)
/* ARB12 maximum value of समय out counter (शेष 15"h1FF) */
#घोषणा TW5864_ARB12_TIME_OUT_CNT 0x7fff

/* 0xb800 ~ 0xb80c -- Indirect Access Register Map */
/*
 * Spec says:
 * In order to access the indirect रेजिस्टर space, the following procedure is
 * followed.
 * But reference driver implementation, and current driver, too, करोes it
 * dअगरferently.
 *
 * Write Registers:
 * (1) Write IND_DATA at 0xb804 ~ 0xb807
 * (2) Read BUSY flag from 0xb803. Wait until BUSY संकेत is 0.
 * (3) Write IND_ADDR at 0xb800 ~ 0xb801. Set R/W to "1", ENABLE to "1"
 * Read Registers:
 * (1) Read BUSY flag from 0xb803. Wait until BUSY संकेत is 0.
 * (2) Write IND_ADDR at 0xb800 ~ 0xb801. Set R/W to "0", ENABLE to "1"
 * (3) Read BUSY flag from 0xb803. Wait until BUSY संकेत is 0.
 * (4) Read IND_DATA from 0xb804 ~ 0xb807
 */
#घोषणा TW5864_IND_CTL 0xb800
/* Define controls in रेजिस्टर TW5864_IND_CTL */
/* Address used to access indirect रेजिस्टर space */
#घोषणा TW5864_IND_ADDR 0x0000ffff
/* Wait until this bit is "0" beक्रमe using indirect access */
#घोषणा TW5864_BUSY BIT(31)
/* Activate the indirect access. This bit is self cleared */
#घोषणा TW5864_ENABLE BIT(25)
/* Read/Write command */
#घोषणा TW5864_RW BIT(24)

/* [31:0] Data used to पढ़ो/ग_लिखो indirect रेजिस्टर space */
#घोषणा TW5864_IND_DATA 0xb804

/* 0xc000 ~ 0xc7fc -- Preview Register Map */
/* Mostly skipped this section. */
/*
 * [15:0] Status of Vsync Synchronized PCI_PV_CH_EN (Read Only)
 * 1 Channel Enabled
 * 0 Channel Disabled
 */
#घोषणा TW5864_PCI_PV_CH_STATUS 0xc000
/*
 * [15:0] PCI Preview Path Enable क्रम channel n
 * 1 Channel Enable
 * 0 Channel Disable
 */
#घोषणा TW5864_PCI_PV_CH_EN 0xc004

/* 0xc800 ~ 0xc804 -- JPEG Capture Register Map */
/* Skipped. */
/* 0xd000 ~ 0xd0fc -- JPEG Control Register Map */
/* Skipped. */

/* 0xe000 ~ 0xfc04 ै  Motion Vector Register Map */

/* ME Motion Vector data (Four Byte Each) 0xe000 ~ 0xe7fc */
#घोषणा TW5864_ME_MV_VEC_START 0xe000
#घोषणा TW5864_ME_MV_VEC_MAX_OFFSET 0x1ff
#घोषणा TW5864_ME_MV_VEC(offset) (TW5864_ME_MV_VEC_START + 4 * offset)

#घोषणा TW5864_MV 0xfc00
/* Define controls in रेजिस्टर TW5864_MV */
/* mv bank0 full status , ग_लिखो "1" to clear */
#घोषणा TW5864_MV_BK0_FULL BIT(0)
/* mv bank1 full status , ग_लिखो "1" to clear */
#घोषणा TW5864_MV_BK1_FULL BIT(1)
/* slice end status; ग_लिखो "1" to clear */
#घोषणा TW5864_MV_खातापूर्ण BIT(2)
/* mv encode पूर्णांकerrupt status; ग_लिखो "1" to clear */
#घोषणा TW5864_MV_DSP_INTR BIT(3)
/* mv ग_लिखो memory overflow, ग_लिखो "1" to clear */
#घोषणा TW5864_DSP_WR_OF BIT(4)
#घोषणा TW5864_MV_LEN_SHIFT 5
/* mv stream length */
#घोषणा TW5864_MV_LEN (0xff << 5)
/* The configured status bit written पूर्णांकo bit 15 of 0xfc04 */
#घोषणा TW5864_MPI_DDR_SEL BIT(13)

#घोषणा TW5864_MPI_DDR_SEL_REG 0xfc04
/* Define controls in रेजिस्टर TW5864_MPI_DDR_SEL_REG */
/*
 * SW configure रेजिस्टर
 * 0 MV is saved in पूर्णांकernal DPR
 * 1 MV is saved in DDR
 */
#घोषणा TW5864_MPI_DDR_SEL2 BIT(15)

/* 0x18000 ~ 0x181fc ै  PCI Master/Slave Control Map */
#घोषणा TW5864_PCI_INTR_STATUS 0x18000
/* Define controls in रेजिस्टर TW5864_PCI_INTR_STATUS */
/* vlc करोne */
#घोषणा TW5864_VLC_DONE_INTR BIT(1)
/* ad vsync */
#घोषणा TW5864_AD_VSYNC_INTR BIT(3)
/* preview eof */
#घोषणा TW5864_PREV_खातापूर्ण_INTR BIT(4)
/* preview overflow पूर्णांकerrupt */
#घोषणा TW5864_PREV_OVERFLOW_INTR BIT(5)
/* समयr पूर्णांकerrupt */
#घोषणा TW5864_TIMER_INTR BIT(6)
/* audio eof */
#घोषणा TW5864_AUDIO_खातापूर्ण_INTR BIT(8)
/* IIC करोne */
#घोषणा TW5864_IIC_DONE_INTR BIT(24)
/* ad पूर्णांकerrupt (e.g.: video lost, video क्रमmat changed) */
#घोषणा TW5864_AD_INTR_REG BIT(25)

#घोषणा TW5864_PCI_INTR_CTL 0x18004
/* Define controls in रेजिस्टर TW5864_PCI_INTR_CTL */
/* master enable */
#घोषणा TW5864_PCI_MAST_ENB BIT(0)
/* mvd&vlc master enable */
#घोषणा TW5864_MVD_VLC_MAST_ENB 0x06
/* (Need to set 0 in TW5864A) */
#घोषणा TW5864_AD_MAST_ENB BIT(3)
/* preview master enable */
#घोषणा TW5864_PREV_MAST_ENB BIT(4)
/* preview overflow enable */
#घोषणा TW5864_PREV_OVERFLOW_ENB BIT(5)
/* समयr पूर्णांकerrupt enable */
#घोषणा TW5864_TIMER_INTR_ENB BIT(6)
/* JPEG master (push mode) enable */
#घोषणा TW5864_JPEG_MAST_ENB BIT(7)
#घोषणा TW5864_AU_MAST_ENB_CHN_SHIFT 8
/* audio master channel enable */
#घोषणा TW5864_AU_MAST_ENB_CHN (0xffff << 8)
/* IIC पूर्णांकerrupt enable */
#घोषणा TW5864_IIC_INTR_ENB BIT(24)
/* ad पूर्णांकerrupt enable */
#घोषणा TW5864_AD_INTR_ENB BIT(25)
/* target burst enable */
#घोषणा TW5864_PCI_TAR_BURST_ENB BIT(26)
/* vlc stream burst enable */
#घोषणा TW5864_PCI_VLC_BURST_ENB BIT(27)
/* ddr burst enable (1 enable, and must set DDR_BRST_EN) */
#घोषणा TW5864_PCI_DDR_BURST_ENB BIT(28)

/*
 * Because preview and audio have 16 channels separately, so using this
 * रेजिस्टरs to indicate पूर्णांकerrupt status क्रम every channels. This is secondary
 * पूर्णांकerrupt status रेजिस्टर. OR operating of the PREV_INTR_REG is
 * PREV_खातापूर्ण_INTR, OR operating of the AU_INTR_REG bits is AUDIO_खातापूर्ण_INTR
 */
#घोषणा TW5864_PREV_AND_AU_INTR 0x18008
/* Define controls in रेजिस्टर TW5864_PREV_AND_AU_INTR */
/* preview eof पूर्णांकerrupt flag */
#घोषणा TW5864_PREV_INTR_REG 0x0000ffff
#घोषणा TW5864_AU_INTR_REG_SHIFT 16
/* audio eof पूर्णांकerrupt flag */
#घोषणा TW5864_AU_INTR_REG (0xffff << 16)

#घोषणा TW5864_MASTER_ENB_REG 0x1800c
/* Define controls in रेजिस्टर TW5864_MASTER_ENB_REG */
/* master enable */
#घोषणा TW5864_PCI_VLC_INTR_ENB BIT(1)
/* mvd and vlc master enable */
#घोषणा TW5864_PCI_PREV_INTR_ENB BIT(4)
/* ad vsync master enable */
#घोषणा TW5864_PCI_PREV_OF_INTR_ENB BIT(5)
/* jpeg master enable */
#घोषणा TW5864_PCI_JPEG_INTR_ENB BIT(7)
/* preview master enable */
#घोषणा TW5864_PCI_AUD_INTR_ENB BIT(8)

/*
 * Every channel of preview and audio have ping-pong buffers in प्रणाली memory,
 * this रेजिस्टर is the buffer flag to notअगरy software which buffer is been
 * operated.
 */
#घोषणा TW5864_PREV_AND_AU_BUF_FLAG 0x18010
/* Define controls in रेजिस्टर TW5864_PREV_AND_AU_BUF_FLAG */
/* preview buffer A/B flag */
#घोषणा TW5864_PREV_BUF_FLAG 0xffff
#घोषणा TW5864_AUDIO_BUF_FLAG_SHIFT 16
/* audio buffer A/B flag */
#घोषणा TW5864_AUDIO_BUF_FLAG (0xffff << 16)

#घोषणा TW5864_IIC 0x18014
/* Define controls in रेजिस्टर TW5864_IIC */
/* रेजिस्टर data */
#घोषणा TW5864_IIC_DATA 0x00ff
#घोषणा TW5864_IIC_REG_ADDR_SHIFT 8
/* रेजिस्टर addr */
#घोषणा TW5864_IIC_REG_ADDR (0xff << 8)
/* rd/wr flag rd=1,wr=0 */
#घोषणा TW5864_IIC_RW BIT(16)
#घोषणा TW5864_IIC_DEV_ADDR_SHIFT 17
/* device addr */
#घोषणा TW5864_IIC_DEV_ADDR (0x7f << 17)
/*
 * iic करोne, software kick off one समय iic transaction through setting this
 * bit to 1. Then poll this bit, value 1 indicate iic transaction have
 * completed, अगर पढ़ो, valid data have been stored in iic_data
 */
#घोषणा TW5864_IIC_DONE BIT(24)

#घोषणा TW5864_RST_AND_IF_INFO 0x18018
/* Define controls in रेजिस्टर TW5864_RST_AND_IF_INFO */
/* application software soft reset */
#घोषणा TW5864_APP_SOFT_RST BIT(0)
#घोषणा TW5864_PCI_INF_VERSION_SHIFT 16
/* PCI पूर्णांकerface version, पढ़ो only */
#घोषणा TW5864_PCI_INF_VERSION (0xffff << 16)

/* vlc stream crc value, it is calculated in pci module */
#घोषणा TW5864_VLC_CRC_REG 0x1801c
/*
 * vlc max length, it is defined by software based on software assign memory
 * space क्रम vlc
 */
#घोषणा TW5864_VLC_MAX_LENGTH 0x18020
/* vlc length of one frame */
#घोषणा TW5864_VLC_LENGTH 0x18024
/* vlc original crc value */
#घोषणा TW5864_VLC_INTRA_CRC_I_REG 0x18028
/* vlc original crc value */
#घोषणा TW5864_VLC_INTRA_CRC_O_REG 0x1802c
/* mv stream crc value, it is calculated in pci module */
#घोषणा TW5864_VLC_PAR_CRC_REG 0x18030
/* mv length */
#घोषणा TW5864_VLC_PAR_LENGTH_REG 0x18034
/* mv original crc value */
#घोषणा TW5864_VLC_PAR_I_REG 0x18038
/* mv original crc value */
#घोषणा TW5864_VLC_PAR_O_REG 0x1803c

/*
 * Configuration रेजिस्टर क्रम 9[or 10] CIFs or 1D1+15QCIF Preview mode.
 * PREV_PCI_ENB_CHN[0] Enable 9th preview channel (9CIF prev) or 1D1 channel in
 * (1D1+15QCIF prev)
 * PREV_PCI_ENB_CHN[1] Enable 10th preview channel
 */
#घोषणा TW5864_PREV_PCI_ENB_CHN 0x18040
/* Description skipped. */
#घोषणा TW5864_PREV_FRAME_FORMAT_IN 0x18044
/* IIC enable */
#घोषणा TW5864_IIC_ENB 0x18048
/*
 * Timer पूर्णांकerrupt पूर्णांकerval
 * 0 1ms
 * 1 2ms
 * 2 4ms
 * 3 8ms
 */
#घोषणा TW5864_PCI_INTTM_SCALE 0x1804c

/*
 * The above रेजिस्टर is pci base address रेजिस्टरs. Application software will
 * initialize them to tell chip where the corresponding stream will be dumped
 * to. Application software will select appropriate base address पूर्णांकerval based
 * on the stream length.
 */
/* VLC stream base address */
#घोषणा TW5864_VLC_STREAM_BASE_ADDR 0x18080
/* MV stream base address */
#घोषणा TW5864_MV_STREAM_BASE_ADDR 0x18084
/* 0x180a0 ै  0x180bc: audio burst base address. Skipped. */
/* 0x180c0 ~ 0x180dc ै  JPEG Push Mode Buffer Base Address. Skipped. */
/* 0x18100 ै  0x1817c: preview burst base address. Skipped. */

/* 0x80000 ~ 0x87fff -- DDR Burst RW Register Map */
#घोषणा TW5864_DDR_CTL 0x80000
/* Define controls in रेजिस्टर TW5864_DDR_CTL */
#घोषणा TW5864_BRST_LENGTH_SHIFT 2
/* Length of 32-bit data burst */
#घोषणा TW5864_BRST_LENGTH (0x3fff << 2)
/*
 * Burst Read/Write
 * 0 Read Burst from DDR
 * 1 Write Burst to DDR
 */
#घोषणा TW5864_BRST_RW BIT(16)
/* Begin a new DDR Burst. This bit is self cleared */
#घोषणा TW5864_NEW_BRST_CMD BIT(17)
/* DDR Burst End Flag */
#घोषणा TW5864_BRST_END BIT(24)
/* Enable Error Interrupt क्रम Single DDR Access */
#घोषणा TW5864_SING_ERR_INTR BIT(25)
/* Enable Error Interrupt क्रम Burst DDR Access */
#घोषणा TW5864_BRST_ERR_INTR BIT(26)
/* Enable Interrupt क्रम End of DDR Burst Access */
#घोषणा TW5864_BRST_END_INTR BIT(27)
/* DDR Single Access Error Flag */
#घोषणा TW5864_SINGLE_ERR BIT(28)
/* DDR Single Access Busy Flag */
#घोषणा TW5864_SINGLE_BUSY BIT(29)
/* DDR Burst Access Error Flag */
#घोषणा TW5864_BRST_ERR BIT(30)
/* DDR Burst Access Busy Flag */
#घोषणा TW5864_BRST_BUSY BIT(31)

/* [27:0] DDR Access Address. Bit [1:0] has to be 0 */
#घोषणा TW5864_DDR_ADDR 0x80004
/* DDR Access Internal Buffer Address. Bit [1:0] has to be 0 */
#घोषणा TW5864_DPR_BUF_ADDR 0x80008
/* SRAM Buffer MPI Access Space. Totally 16 KB */
#घोषणा TW5864_DPR_BUF_START 0x84000
/* 0x84000 - 0x87ffc */
#घोषणा TW5864_DPR_BUF_SIZE 0x4000

/* Indirect Map Space */
/*
 * The indirect space is accessed through 0xb800 ~ 0xb807 रेजिस्टरs in direct
 * access space
 */
/* Analog Video / Audio Decoder / Encoder */
/* Allowed channel values: [0; 3] */
/* Read-only रेजिस्टर */
#घोषणा TW5864_INसूची_VIN_0(channel) (0x000 + channel * 0x010)
/* Define controls in रेजिस्टर TW5864_INसूची_VIN_0 */
/*
 * 1 Video not present. (sync is not detected in number of consecutive line
 * periods specअगरied by MISSCNT रेजिस्टर)
 * 0 Video detected.
 */
#घोषणा TW5864_INसूची_VIN_0_VDLOSS BIT(7)
/*
 * 1 Horizontal sync PLL is locked to the incoming video source.
 * 0 Horizontal sync PLL is not locked.
 */
#घोषणा TW5864_INसूची_VIN_0_HLOCK BIT(6)
/*
 * 1 Sub-carrier PLL is locked to the incoming video source.
 * 0 Sub-carrier PLL is not locked.
 */
#घोषणा TW5864_INसूची_VIN_0_SLOCK BIT(5)
/*
 * 1 Even field is being decoded.
 * 0 Odd field is being decoded.
 */
#घोषणा TW5864_INसूची_VIN_0_FLD BIT(4)
/*
 * 1 Vertical logic is locked to the incoming video source.
 * 0 Vertical logic is not locked.
 */
#घोषणा TW5864_INसूची_VIN_0_VLOCK BIT(3)
/*
 * 1 No color burst संकेत detected.
 * 0 Color burst संकेत detected.
 */
#घोषणा TW5864_INसूची_VIN_0_MONO BIT(1)
/*
 * 0 60Hz source detected
 * 1 50Hz source detected
 * The actual vertical scanning frequency depends on the current standard
 * invoked.
 */
#घोषणा TW5864_INसूची_VIN_0_DET50 BIT(0)

#घोषणा TW5864_INसूची_VIN_1(channel) (0x001 + channel * 0x010)
/* VCR संकेत indicator. Read-only. */
#घोषणा TW5864_INसूची_VIN_1_VCR BIT(7)
/* Weak संकेत indicator 2. Read-only. */
#घोषणा TW5864_INसूची_VIN_1_WKAIR BIT(6)
/* Weak संकेत indicator controlled by WKTH. Read-only. */
#घोषणा TW5864_INसूची_VIN_1_WKAIR1 BIT(5)
/*
 * 1 = Standard संकेत
 * 0 = Non-standard संकेत
 * Read-only
 */
#घोषणा TW5864_INसूची_VIN_1_VSTD BIT(4)
/*
 * 1 = Non-पूर्णांकerlaced संकेत
 * 0 = पूर्णांकerlaced संकेत
 * Read-only
 */
#घोषणा TW5864_INसूची_VIN_1_NINTL BIT(3)
/*
 * Vertical Sharpness Control. Writable.
 * 0 = None (शेष)
 * 7 = Highest
 * **Note: VSHP must be set to ै 0ै  अगर COMB = 0
 */
#घोषणा TW5864_INसूची_VIN_1_VSHP 0x07

/* HDELAY_XY[7:0] */
#घोषणा TW5864_INसूची_VIN_2_HDELAY_XY_LO(channel) (0x002 + channel * 0x010)
/* HACTIVE_XY[7:0] */
#घोषणा TW5864_INसूची_VIN_3_HACTIVE_XY_LO(channel) (0x003 + channel * 0x010)
/* VDELAY_XY[7:0] */
#घोषणा TW5864_INसूची_VIN_4_VDELAY_XY_LO(channel) (0x004 + channel * 0x010)
/* VACTIVE_XY[7:0] */
#घोषणा TW5864_INसूची_VIN_5_VACTIVE_XY_LO(channel) (0x005 + channel * 0x010)

#घोषणा TW5864_INसूची_VIN_6(channel) (0x006 + channel * 0x010)
/* Define controls in रेजिस्टर TW5864_INसूची_VIN_6 */
#घोषणा TW5864_INसूची_VIN_6_HDELAY_XY_HI 0x03
#घोषणा TW5864_INसूची_VIN_6_HACTIVE_XY_HI_SHIFT 2
#घोषणा TW5864_INसूची_VIN_6_HACTIVE_XY_HI (0x03 << 2)
#घोषणा TW5864_INसूची_VIN_6_VDELAY_XY_HI BIT(4)
#घोषणा TW5864_INसूची_VIN_6_VACTIVE_XY_HI BIT(5)

/*
 * HDELAY_XY This 10bit रेजिस्टर defines the starting location of horizontal
 * active pixel क्रम display / record path. A unit is 1 pixel. The शेष value
 * is 0x00f क्रम NTSC and 0x00a क्रम PAL.
 *
 * HACTIVE_XY This 10bit रेजिस्टर defines the number of horizontal active pixel
 * क्रम display / record path. A unit is 1 pixel. The शेष value is decimal
 * 720.
 *
 * VDELAY_XY This 9bit रेजिस्टर defines the starting location of vertical
 * active क्रम display / record path. A unit is 1 line. The शेष value is
 * decimal 6.
 *
 * VACTIVE_XY This 9bit रेजिस्टर defines the number of vertical active lines
 * क्रम display / record path. A unit is 1 line. The शेष value is decimal
 * 240.
 */

/* HUE These bits control the color hue as 2's complement number. They have
 * value from +36o (7Fh) to -36o (80h) with an increment of 2.8o. The 2 LSB has
 * no effect. The positive value gives greenish tone and negative value gives
 * purplish tone. The शेष value is 0o (00h). This is effective only on NTSC
 * प्रणाली. The शेष is 00h.
 */
#घोषणा TW5864_INसूची_VIN_7_HUE(channel) (0x007 + channel * 0x010)

#घोषणा TW5864_INसूची_VIN_8(channel) (0x008 + channel * 0x010)
/* Define controls in रेजिस्टर TW5864_INसूची_VIN_8 */
/*
 * This bit controls the center frequency of the peaking filter.
 * The corresponding gain adjusपंचांगent is HFLT.
 * 0 Low
 * 1 center
 */
#घोषणा TW5864_INसूची_VIN_8_SCURVE BIT(7)
/* CTI level selection. The शेष is 1.
 * 0 None
 * 3 Highest
 */
#घोषणा TW5864_INसूची_VIN_8_CTI_SHIFT 4
#घोषणा TW5864_INसूची_VIN_8_CTI (0x03 << 4)

/*
 * These bits control the amount of sharpness enhancement on the luminance
 * संकेतs. There are 16 levels of control with "0" having no effect on the
 * output image. 1 through 15 provides sharpness enhancement with "F" being the
 * strongest. The शेष is 1.
 */
#घोषणा TW5864_INसूची_VIN_8_SHARPNESS 0x0f

/*
 * These bits control the luminance contrast gain. A value of 100 (64h) has a
 * gain of 1. The range adjusपंचांगent is from 0% to 255% at 1% per step. The
 * शेष is 64h.
 */
#घोषणा TW5864_INसूची_VIN_9_CNTRST(channel) (0x009 + channel * 0x010)

/*
 * These bits control the brightness. They have value of ै 128 to 127 in 2's
 * complement क्रमm. Positive value increases brightness. A value 0 has no
 * effect on the data. The शेष is 00h.
 */
#घोषणा TW5864_INसूची_VIN_A_BRIGHT(channel) (0x00a + channel * 0x010)

/*
 * These bits control the digital gain adjusपंचांगent to the U (or Cb) component of
 * the digital video संकेत. The color saturation can be adjusted by adjusting
 * the U and V color gain components by the same amount in the normal
 * situation. The U and V can also be adjusted independently to provide greater
 * flexibility. The range of adjusपंचांगent is 0 to 200%. A value of 128 (80h) has
 * gain of 100%. The शेष is 80h.
 */
#घोषणा TW5864_INसूची_VIN_B_SAT_U(channel) (0x00b + channel * 0x010)

/*
 * These bits control the digital gain adjusपंचांगent to the V (or Cr) component of
 * the digital video संकेत. The color saturation can be adjusted by adjusting
 * the U and V color gain components by the same amount in the normal
 * situation. The U and V can also be adjusted independently to provide greater
 * flexibility. The range of adjusपंचांगent is 0 to 200%. A value of 128 (80h) has
 * gain of 100%. The शेष is 80h.
 */
#घोषणा TW5864_INसूची_VIN_C_SAT_V(channel) (0x00c + channel * 0x010)

/* Read-only */
#घोषणा TW5864_INसूची_VIN_D(channel) (0x00d + channel * 0x010)
/* Define controls in रेजिस्टर TW5864_INसूची_VIN_D */
/* Macrovision color stripe detection may be un-reliable */
#घोषणा TW5864_INसूची_VIN_D_CSBAD BIT(3)
/* Macrovision AGC pulse detected */
#घोषणा TW5864_INसूची_VIN_D_MCVSN BIT(2)
/* Macrovision color stripe protection burst detected */
#घोषणा TW5864_INसूची_VIN_D_CSTRIPE BIT(1)
/*
 * This bit is valid only when color stripe protection is detected, i.e. अगर
 * CSTRIPE=1,
 * 1 Type 2 color stripe protection
 * 0 Type 3 color stripe protection
 */
#घोषणा TW5864_INसूची_VIN_D_CTYPE2 BIT(0)

/* Read-only */
#घोषणा TW5864_INसूची_VIN_E(channel) (0x00e + channel * 0x010)
/* Define controls in रेजिस्टर TW5864_INसूची_VIN_E */
/*
 * Read-only.
 * 0 Idle
 * 1 Detection in progress
 */
#घोषणा TW5864_INसूची_VIN_E_DETSTUS BIT(7)
/*
 * STDNOW Current standard invoked
 * 0 NTSC (M)
 * 1 PAL (B, D, G, H, I)
 * 2 SECAM
 * 3 NTSC4.43
 * 4 PAL (M)
 * 5 PAL (CN)
 * 6 PAL 60
 * 7 Not valid
 */
#घोषणा TW5864_INसूची_VIN_E_STDNOW_SHIFT 4
#घोषणा TW5864_INसूची_VIN_E_STDNOW (0x07 << 4)

/*
 * 1 Disable the shaकरोw रेजिस्टरs
 * 0 Enable VACTIVE and HDELAY shaकरोw रेजिस्टरs value depending on STANDARD.
 * (Default)
 */
#घोषणा TW5864_INसूची_VIN_E_ATREG BIT(3)
/*
 * STANDARD Standard selection
 * 0 NTSC (M)
 * 1 PAL (B, D, G, H, I)
 * 2 SECAM
 * 3 NTSC4.43
 * 4 PAL (M)
 * 5 PAL (CN)
 * 6 PAL 60
 * 7 Auto detection (Default)
 */
#घोषणा TW5864_INसूची_VIN_E_STANDARD 0x07

#घोषणा TW5864_INसूची_VIN_F(channel) (0x00f + channel * 0x010)
/* Define controls in रेजिस्टर TW5864_INसूची_VIN_F */
/*
 * 1 Writing 1 to this bit will manually initiate the स्वतः क्रमmat detection
 * process. This bit is a self-clearing bit
 * 0 Manual initiation of स्वतः क्रमmat detection is करोne. (Default)
 */
#घोषणा TW5864_INसूची_VIN_F_ATSTART BIT(7)
/* Enable recognition of PAL60 (Default) */
#घोषणा TW5864_INसूची_VIN_F_PAL60EN BIT(6)
/* Enable recognition of PAL (CN). (Default) */
#घोषणा TW5864_INसूची_VIN_F_PALCNEN BIT(5)
/* Enable recognition of PAL (M). (Default) */
#घोषणा TW5864_INसूची_VIN_F_PALMEN BIT(4)
/* Enable recognition of NTSC 4.43. (Default) */
#घोषणा TW5864_INसूची_VIN_F_NTSC44EN BIT(3)
/* Enable recognition of SECAM. (Default) */
#घोषणा TW5864_INसूची_VIN_F_SECAMEN BIT(2)
/* Enable recognition of PAL (B, D, G, H, I). (Default) */
#घोषणा TW5864_INसूची_VIN_F_PALBEN BIT(1)
/* Enable recognition of NTSC (M). (Default) */
#घोषणा TW5864_INसूची_VIN_F_NTSCEN BIT(0)

/* Some रेजिस्टरs skipped. */

/* Use falling edge to sample VD1-VD4 from 54 MHz to 108 MHz */
#घोषणा TW5864_INसूची_VD_108_POL 0x041
#घोषणा TW5864_INसूची_VD_108_POL_VD12 BIT(0)
#घोषणा TW5864_INसूची_VD_108_POL_VD34 BIT(1)
#घोषणा TW5864_INसूची_VD_108_POL_BOTH \
	(TW5864_INसूची_VD_108_POL_VD12 | TW5864_INसूची_VD_108_POL_VD34)

/* Some रेजिस्टरs skipped. */

/*
 * Audio Input ADC gain control
 * 0 0.25
 * 1 0.31
 * 2 0.38
 * 3 0.44
 * 4 0.50
 * 5 0.63
 * 6 0.75
 * 7 0.88
 * 8 1.00 (शेष)
 * 9 1.25
 * 10 1.50
 * 11 1.75
 * 12 2.00
 * 13 2.25
 * 14 2.50
 * 15 2.75
 */
/* [3:0] channel 0, [7:4] channel 1 */
#घोषणा TW5864_INसूची_AIGAIN1 0x060
/* [3:0] channel 2, [7:4] channel 3 */
#घोषणा TW5864_INसूची_AIGAIN2 0x061

/* Some रेजिस्टरs skipped */

#घोषणा TW5864_INसूची_AIN_0x06D 0x06d
/* Define controls in रेजिस्टर TW5864_INसूची_AIN_0x06D */
/*
 * LAWMD Select u-Law/A-Law/PCM/SB data output क्रमmat on ADATR and ADATM pin.
 * 0 PCM output (शेष)
 * 1 SB (Signed MSB bit in PCM data is inverted) output
 * 2 u-Law output
 * 3 A-Law output
 */
#घोषणा TW5864_INसूची_AIN_LAWMD_SHIFT 6
#घोषणा TW5864_INसूची_AIN_LAWMD (0x03 << 6)
/*
 * Disable the mixing ratio value क्रम all audio.
 * 0 Apply inभागidual mixing ratio value क्रम each audio (शेष)
 * 1 Apply nominal value क्रम all audio commonly
 */
#घोषणा TW5864_INसूची_AIN_MIX_DERATIO BIT(5)
/*
 * Enable the mute function क्रम audio channel AINn when n is 0 to 3. It effects
 * only क्रम mixing. When n = 4, it enable the mute function of the playback
 * audio input. It effects only क्रम single chip or the last stage chip
 * 0 Normal
 * 1 Muted (शेष)
 */
#घोषणा TW5864_INसूची_AIN_MIX_MUTE 0x1f

/* Some रेजिस्टरs skipped */

#घोषणा TW5864_INसूची_AIN_0x0E3 0x0e3
/* Define controls in रेजिस्टर TW5864_INसूची_AIN_0x0E3 */
/*
 * ADATP संकेत is coming from बाह्यal ADPCM decoder, instead of on-chip ADPCM
 * decoder
 */
#घोषणा TW5864_INसूची_AIN_0x0E3_EXT_ADATP BIT(7)
/* ACLKP output संकेत polarity inverse */
#घोषणा TW5864_INसूची_AIN_0x0E3_ACLKPPOLO BIT(6)
/*
 * ACLKR input संकेत polarity inverse.
 * 0 Not inversed (Default)
 * 1 Inversed
 */
#घोषणा TW5864_INसूची_AIN_0x0E3_ACLKRPOL BIT(5)
/*
 * ACLKP input संकेत polarity inverse.
 * 0 Not inversed (Default)
 * 1 Inversed
 */
#घोषणा TW5864_INसूची_AIN_0x0E3_ACLKPPOLI BIT(4)
/*
 * ACKI [21:0] control स्वतःmatic set up with AFMD रेजिस्टरs
 * This mode is only effective when ACLKRMASTER=1
 * 0 ACKI [21:0] रेजिस्टरs set up ACKI control
 * 1 ACKI control is स्वतःmatically set up by AFMD रेजिस्टर values
 */
#घोषणा TW5864_INसूची_AIN_0x0E3_AFAUTO BIT(3)
/*
 * AFAUTO control mode
 * 0 8kHz setting (Default)
 * 1 16kHz setting
 * 2 32kHz setting
 * 3 44.1kHz setting
 * 4 48kHz setting
 */
#घोषणा TW5864_INसूची_AIN_0x0E3_AFMD 0x07

#घोषणा TW5864_INसूची_AIN_0x0E4 0x0e4
/* Define controls in रेजिस्टर TW5864_INसूची_AIN_0x0ED */
/*
 * 8bit I2S Record output mode.
 * 0 L/R half length separated output (Default).
 * 1 One continuous packed output equal to DSP output क्रमmat.
 */
#घोषणा TW5864_INसूची_AIN_0x0E4_I2S8MODE BIT(7)
/*
 * Audio Clock Master ACLKR output wave क्रमmat.
 * 0 High periods is one 27MHz घड़ी period (शेष).
 * 1 Almost duty 50-50% घड़ी output on ACLKR pin. If this mode is selected, two
 * बार bigger number value need to be set up on the ACKI रेजिस्टर. If
 * AFAUTO=1, ACKI control is स्वतःmatically set up even अगर MASCKMD=1.
 */
#घोषणा TW5864_INसूची_AIN_0x0E4_MASCKMD BIT(6)
/* Playback ACLKP/ASYNP/ADATP input data MSB-LSB swapping */
#घोषणा TW5864_INसूची_AIN_0x0E4_PBINSWAP BIT(5)
/*
 * ASYNR input संकेत delay.
 * 0 No delay
 * 1 Add one 27MHz period delay in ASYNR संकेत input
 */
#घोषणा TW5864_INसूची_AIN_0x0E4_ASYNRDLY BIT(4)
/*
 * ASYNP input संकेत delay.
 * 0 no delay
 * 1 add one 27MHz period delay in ASYNP संकेत input
 */
#घोषणा TW5864_INसूची_AIN_0x0E4_ASYNPDLY BIT(3)
/*
 * ADATP input data delay by one ACLKP घड़ी.
 * 0 No delay (Default). This is क्रम I2S type 1T delay input पूर्णांकerface.
 * 1 Add 1 ACLKP घड़ी delay in ADATP input data. This is क्रम left-justअगरied
 * type 0T delay input पूर्णांकerface.
 */
#घोषणा TW5864_INसूची_AIN_0x0E4_ADATPDLY BIT(2)
/*
 * Select u-Law/A-Law/PCM/SB data input क्रमmat on ADATP pin.
 * 0 PCM input (Default)
 * 1 SB (Signed MSB bit in PCM data is inverted) input
 * 2 u-Law input
 * 3 A-Law input
 */
#घोषणा TW5864_INसूची_AIN_0x0E4_INLAWMD 0x03

/*
 * Enable state रेजिस्टर updating and पूर्णांकerrupt request of audio AIN5 detection
 * क्रम each input
 */
#घोषणा TW5864_INसूची_AIN_A5DETENA 0x0e5

/* Some रेजिस्टरs skipped */

/*
 * [7:3]: DEV_ID The TW5864 product ID code is 01000
 * [2:0]: REV_ID The revision number is 0h
 */
#घोषणा TW5864_INसूची_ID 0x0fe

#घोषणा TW5864_INसूची_IN_PIC_WIDTH(channel) (0x200 + 4 * channel)
#घोषणा TW5864_INसूची_IN_PIC_HEIGHT(channel) (0x201 + 4 * channel)
#घोषणा TW5864_INसूची_OUT_PIC_WIDTH(channel) (0x202 + 4 * channel)
#घोषणा TW5864_INसूची_OUT_PIC_HEIGHT(channel) (0x203 + 4 * channel)

/* Some रेजिस्टरs skipped */

#घोषणा TW5864_INसूची_CROP_ETC 0x260
/* Define controls in रेजिस्टर TW5864_INसूची_CROP_ETC */
/* Enable cropping from 720 to 704 */
#घोषणा TW5864_INसूची_CROP_ETC_CROP_EN 0x4

/*
 * Interrupt status रेजिस्टर from the front-end. Write "1" to each bit to clear
 * the पूर्णांकerrupt
 * 15:0 Motion detection पूर्णांकerrupt क्रम channel 0 ~ 15
 * 31:16 Night detection पूर्णांकerrupt क्रम channel 0 ~ 15
 * 47:32 Blind detection पूर्णांकerrupt क्रम channel 0 ~ 15
 * 63:48 No video पूर्णांकerrupt क्रम channel 0 ~ 15
 * 79:64 Line mode underflow पूर्णांकerrupt क्रम channel 0 ~ 15
 * 95:80 Line mode overflow पूर्णांकerrupt क्रम channel 0 ~ 15
 */
/* 0x2d0~0x2d7: [63:0] bits */
#घोषणा TW5864_INसूची_INTERRUPT1 0x2d0
/* 0x2e0~0x2e3: [95:64] bits */
#घोषणा TW5864_INसूची_INTERRUPT2 0x2e0

/*
 * Interrupt mask रेजिस्टर क्रम पूर्णांकerrupts in 0x2d0 ~ 0x2d7
 * 15:0 Motion detection पूर्णांकerrupt क्रम channel 0 ~ 15
 * 31:16 Night detection पूर्णांकerrupt क्रम channel 0 ~ 15
 * 47:32 Blind detection पूर्णांकerrupt क्रम channel 0 ~ 15
 * 63:48 No video पूर्णांकerrupt क्रम channel 0 ~ 15
 * 79:64 Line mode underflow पूर्णांकerrupt क्रम channel 0 ~ 15
 * 95:80 Line mode overflow पूर्णांकerrupt क्रम channel 0 ~ 15
 */
/* 0x2d8~0x2df: [63:0] bits */
#घोषणा TW5864_INसूची_INTERRUPT_MASK1 0x2d8
/* 0x2e8~0x2eb: [95:64] bits */
#घोषणा TW5864_INसूची_INTERRUPT_MASK2 0x2e8

/* [11:0]: Interrupt summary रेजिस्टर क्रम पूर्णांकerrupts & पूर्णांकerrupt mask from in
 * 0x2d0 ~ 0x2d7 and 0x2d8 ~ 0x2df
 * bit 0: पूर्णांकerrupt occurs in 0x2d0 & 0x2d8
 * bit 1: पूर्णांकerrupt occurs in 0x2d1 & 0x2d9
 * bit 2: पूर्णांकerrupt occurs in 0x2d2 & 0x2da
 * bit 3: पूर्णांकerrupt occurs in 0x2d3 & 0x2db
 * bit 4: पूर्णांकerrupt occurs in 0x2d4 & 0x2dc
 * bit 5: पूर्णांकerrupt occurs in 0x2d5 & 0x2dd
 * bit 6: पूर्णांकerrupt occurs in 0x2d6 & 0x2de
 * bit 7: पूर्णांकerrupt occurs in 0x2d7 & 0x2df
 * bit 8: पूर्णांकerrupt occurs in 0x2e0 & 0x2e8
 * bit 9: पूर्णांकerrupt occurs in 0x2e1 & 0x2e9
 * bit 10: पूर्णांकerrupt occurs in 0x2e2 & 0x2ea
 * bit 11: पूर्णांकerrupt occurs in 0x2e3 & 0x2eb
 */
#घोषणा TW5864_INसूची_INTERRUPT_SUMMARY 0x2f0

/* Motion / Blind / Night Detection */
/* valid value क्रम channel is [0:15] */
#घोषणा TW5864_INसूची_DETECTION_CTL0(channel) (0x300 + channel * 0x08)
/* Define controls in रेजिस्टर TW5864_INसूची_DETECTION_CTL0 */
/*
 * Disable the motion and blind detection.
 * 0 Enable motion and blind detection (शेष)
 * 1 Disable motion and blind detection
 */
#घोषणा TW5864_INसूची_DETECTION_CTL0_MD_DIS BIT(5)
/*
 * Request to start motion detection on manual trigger mode
 * 0 None Operation (शेष)
 * 1 Request to start motion detection
 */
#घोषणा TW5864_INसूची_DETECTION_CTL0_MD_STRB BIT(3)
/*
 * Select the trigger mode of motion detection
 * 0 Automatic trigger mode of motion detection (शेष)
 * 1 Manual trigger mode क्रम motion detection
 */
#घोषणा TW5864_INसूची_DETECTION_CTL0_MD_STRB_EN BIT(2)
/*
 * Define the threshold of cell क्रम blind detection.
 * 0 Low threshold (More sensitive) (शेष)
 * : :
 * 3 High threshold (Less sensitive)
 */
#घोषणा TW5864_INसूची_DETECTION_CTL0_BD_CELSENS 0x03

#घोषणा TW5864_INसूची_DETECTION_CTL1(channel) (0x301 + channel * 0x08)
/* Define controls in रेजिस्टर TW5864_INसूची_DETECTION_CTL1 */
/*
 * Control the temporal sensitivity of motion detector.
 * 0 More Sensitive (शेष)
 * : :
 * 15 Less Sensitive
 */
#घोषणा TW5864_INसूची_DETECTION_CTL1_MD_TMPSENS_SHIFT 4
#घोषणा TW5864_INसूची_DETECTION_CTL1_MD_TMPSENS (0x0f << 4)
/*
 * Adjust the horizontal starting position क्रम motion detection
 * 0 0 pixel (शेष)
 * : :
 * 15 15 pixels
 */
#घोषणा TW5864_INसूची_DETECTION_CTL1_MD_PIXEL_OS 0x0f

#घोषणा TW5864_INसूची_DETECTION_CTL2(channel) (0x302 + channel * 0x08)
/* Define controls in रेजिस्टर TW5864_INसूची_DETECTION_CTL2 */
/*
 * Control the updating समय of reference field क्रम motion detection.
 * 0 Update reference field every field (शेष)
 * 1 Update reference field according to MD_SPEED
 */
#घोषणा TW5864_INसूची_DETECTION_CTL2_MD_REFFLD BIT(7)
/*
 * Select the field क्रम motion detection.
 * 0 Detecting motion क्रम only odd field (शेष)
 * 1 Detecting motion क्रम only even field
 * 2 Detecting motion क्रम any field
 * 3 Detecting motion क्रम both odd and even field
 */
#घोषणा TW5864_INसूची_DETECTION_CTL2_MD_FIELD_SHIFT 5
#घोषणा TW5864_INसूची_DETECTION_CTL2_MD_FIELD (0x03 << 5)
/*
 * Control the level sensitivity of motion detector.
 * 0 More sensitive (शेष)
 * : :
 * 15 Less sensitive
 */
#घोषणा TW5864_INसूची_DETECTION_CTL2_MD_LVSENS 0x1f

#घोषणा TW5864_INसूची_DETECTION_CTL3(channel) (0x303 + channel * 0x08)
/* Define controls in रेजिस्टर TW5864_INसूची_DETECTION_CTL3 */
/*
 * Define the threshold of sub-cell number क्रम motion detection.
 * 0 Motion is detected अगर 1 sub-cell has motion (More sensitive) (शेष)
 * 1 Motion is detected अगर 2 sub-cells have motion
 * 2 Motion is detected अगर 3 sub-cells have motion
 * 3 Motion is detected अगर 4 sub-cells have motion (Less sensitive)
 */
#घोषणा TW5864_INसूची_DETECTION_CTL3_MD_CELSENS_SHIFT 6
#घोषणा TW5864_INसूची_DETECTION_CTL3_MD_CELSENS (0x03 << 6)
/*
 * Control the velocity of motion detector.
 * Large value is suitable क्रम slow motion detection.
 * In MD_DUAL_EN = 1, MD_SPEED should be limited to 0 ~ 31.
 * 0 1 field पूर्णांकervals (शेष)
 * 1 2 field पूर्णांकervals
 * : :
 * 61 62 field पूर्णांकervals
 * 62 63 field पूर्णांकervals
 * 63 Not supported
 */
#घोषणा TW5864_INसूची_DETECTION_CTL3_MD_SPEED 0x3f

#घोषणा TW5864_INसूची_DETECTION_CTL4(channel) (0x304 + channel * 0x08)
/* Define controls in रेजिस्टर TW5864_INसूची_DETECTION_CTL4 */
/*
 * Control the spatial sensitivity of motion detector.
 * 0 More Sensitive (शेष)
 * : :
 * 15 Less Sensitive
 */
#घोषणा TW5864_INसूची_DETECTION_CTL4_MD_SPSENS_SHIFT 4
#घोषणा TW5864_INसूची_DETECTION_CTL4_MD_SPSENS (0x0f << 4)
/*
 * Define the threshold of level क्रम blind detection.
 * 0 Low threshold (More sensitive) (शेष)
 * : :
 * 15 High threshold (Less sensitive)
 */
#घोषणा TW5864_INसूची_DETECTION_CTL4_BD_LVSENS 0x0f

#घोषणा TW5864_INसूची_DETECTION_CTL5(channel) (0x305 + channel * 0x08)
/*
 * Define the threshold of temporal sensitivity क्रम night detection.
 * 0 Low threshold (More sensitive) (शेष)
 * : :
 * 15 High threshold (Less sensitive)
 */
#घोषणा TW5864_INसूची_DETECTION_CTL5_ND_TMPSENS_SHIFT 4
#घोषणा TW5864_INसूची_DETECTION_CTL5_ND_TMPSENS (0x0f << 4)
/*
 * Define the threshold of level क्रम night detection.
 * 0 Low threshold (More sensitive) (शेष)
 * : :
 * 3 High threshold (Less sensitive)
 */
#घोषणा TW5864_INसूची_DETECTION_CTL5_ND_LVSENS 0x0f

/*
 * [11:0] The base address of the motion detection buffer. This address is in
 * unit of 64K bytes. The generated DDR address will be अणुMD_BASE_ADDR,
 * 16"h0000}. The default value should be 12"h000
 */
#घोषणा TW5864_INसूची_MD_BASE_ADDR 0x380

/*
 * This controls the channel of the motion detection result shown in रेजिस्टर
 * 0x3a0 ~ 0x3b7. Beक्रमe पढ़ोing back motion result, always set this first.
 */
#घोषणा TW5864_INसूची_RGR_MOTION_SEL 0x382

/* [15:0] MD strobe has been perक्रमmed at channel n (पढ़ो only) */
#घोषणा TW5864_INसूची_MD_STRB 0x386
/* NO_VIDEO Detected from channel n (पढ़ो only) */
#घोषणा TW5864_INसूची_NOVID_DET 0x388
/* Motion Detected from channel n (पढ़ो only) */
#घोषणा TW5864_INसूची_MD_DET 0x38a
/* Blind Detected from channel n (पढ़ो only) */
#घोषणा TW5864_INसूची_BD_DET 0x38c
/* Night Detected from channel n (पढ़ो only) */
#घोषणा TW5864_INसूची_ND_DET 0x38e

/* 192 bit motion flag of the channel specअगरied by RGR_MOTION_SEL in 0x382 */
#घोषणा TW5864_INसूची_MOTION_FLAG 0x3a0
#घोषणा TW5864_INसूची_MOTION_FLAG_BYTE_COUNT 24

/*
 * [9:0] The motion cell count of a specअगरic channel selected by 0x382. This is
 * क्रम DI purpose
 */
#घोषणा TW5864_INसूची_MD_DI_CNT 0x3b8
/* The motion detection cell sensitivity क्रम DI purpose */
#घोषणा TW5864_INसूची_MD_DI_CELLSENS 0x3ba
/* The motion detection threshold level क्रम DI purpose */
#घोषणा TW5864_INसूची_MD_DI_LVSENS 0x3bb

/* 192 bit motion mask of the channel specअगरied by MASK_CH_SEL in 0x3fe */
#घोषणा TW5864_INसूची_MOTION_MASK 0x3e0
#घोषणा TW5864_INसूची_MOTION_MASK_BYTE_COUNT 24

/* [4:0] The channel selection to access masks in 0x3e0 ~ 0x3f7 */
#घोषणा TW5864_INसूची_MASK_CH_SEL 0x3fe

/* Clock PLL / Analog IP Control */
/* Some रेजिस्टरs skipped */

#घोषणा TW5864_INसूची_DDRA_DLL_DQS_SEL0 0xee6
#घोषणा TW5864_INसूची_DDRA_DLL_DQS_SEL1 0xee7
#घोषणा TW5864_INसूची_DDRA_DLL_CLK90_SEL 0xee8
#घोषणा TW5864_INसूची_DDRA_DLL_TEST_SEL_AND_TAP_S 0xee9

#घोषणा TW5864_INसूची_DDRB_DLL_DQS_SEL0 0xeeb
#घोषणा TW5864_INसूची_DDRB_DLL_DQS_SEL1 0xeec
#घोषणा TW5864_INसूची_DDRB_DLL_CLK90_SEL 0xeed
#घोषणा TW5864_INसूची_DDRB_DLL_TEST_SEL_AND_TAP_S 0xeee

#घोषणा TW5864_INसूची_RESET 0xef0
#घोषणा TW5864_INसूची_RESET_VD BIT(7)
#घोषणा TW5864_INसूची_RESET_DLL BIT(6)
#घोषणा TW5864_INसूची_RESET_MUX_CORE BIT(5)

#घोषणा TW5864_INसूची_PV_VD_CK_POL 0xefd
#घोषणा TW5864_INसूची_PV_VD_CK_POL_PV(channel) BIT(channel)
#घोषणा TW5864_INसूची_PV_VD_CK_POL_VD(channel) BIT(channel + 4)

#घोषणा TW5864_INसूची_CLK0_SEL 0xefe
#घोषणा TW5864_INसूची_CLK0_SEL_VD_SHIFT 0
#घोषणा TW5864_INसूची_CLK0_SEL_VD_MASK 0x3
#घोषणा TW5864_INसूची_CLK0_SEL_PV_SHIFT 2
#घोषणा TW5864_INसूची_CLK0_SEL_PV_MASK (0x3 << 2)
#घोषणा TW5864_INसूची_CLK0_SEL_PV2_SHIFT 4
#घोषणा TW5864_INसूची_CLK0_SEL_PV2_MASK (0x3 << 4)
