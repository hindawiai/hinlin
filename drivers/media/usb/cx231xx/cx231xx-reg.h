<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
   cx231xx-reg.h - driver क्रम Conexant Cx23100/101/102
	       USB video capture devices

   Copyright (C) 2008 <srinivasa.deevi at conexant करोt com>

 */

#अगर_अघोषित _CX231XX_REG_H
#घोषणा _CX231XX_REG_H

/*****************************************************************************
				* VBI codes *
*****************************************************************************/

#घोषणा SAV_ACTIVE_VIDEO_FIELD1		0x80
#घोषणा EAV_ACTIVE_VIDEO_FIELD1		0x90

#घोषणा SAV_ACTIVE_VIDEO_FIELD2		0xc0
#घोषणा EAV_ACTIVE_VIDEO_FIELD2		0xd0

#घोषणा SAV_VBLANK_FIELD1		0xa0
#घोषणा EAV_VBLANK_FIELD1		0xb0

#घोषणा SAV_VBLANK_FIELD2		0xe0
#घोषणा EAV_VBLANK_FIELD2		0xf0

#घोषणा SAV_VBI_FIELD1			0x20
#घोषणा EAV_VBI_FIELD1			0x30

#घोषणा SAV_VBI_FIELD2			0x60
#घोषणा EAV_VBI_FIELD2			0x70

/*****************************************************************************/
/* Audio ADC Registers */
#घोषणा CH_PWR_CTRL1			0x0000000e
#घोषणा CH_PWR_CTRL2			0x0000000f
/*****************************************************************************/

#घोषणा      HOST_REG1                0x000
#घोषणा      FLD_FORCE_CHIP_SEL       0x80
#घोषणा      FLD_AUTO_INC_DIS         0x20
#घोषणा      FLD_PREFETCH_EN          0x10
/* Reserved [2:3] */
#घोषणा      FLD_DIGITAL_PWR_DN       0x02
#घोषणा      FLD_SLEEP                0x01

/*****************************************************************************/
#घोषणा      HOST_REG2                0x001

/*****************************************************************************/
#घोषणा      HOST_REG3                0x002

/*****************************************************************************/
/* added क्रम polaris */
#घोषणा      GPIO_PIN_CTL0            0x3
#घोषणा      GPIO_PIN_CTL1            0x4
#घोषणा      GPIO_PIN_CTL2            0x5
#घोषणा      GPIO_PIN_CTL3            0x6
#घोषणा      TS1_PIN_CTL0             0x7
#घोषणा      TS1_PIN_CTL1             0x8
/*****************************************************************************/

#घोषणा      FLD_CLK_IN_EN            0x80
#घोषणा      FLD_XTAL_CTRL            0x70
#घोषणा      FLD_BB_CLK_MODE          0x0C
#घोषणा      FLD_REF_DIV_PLL          0x02
#घोषणा      FLD_REF_SEL_PLL1         0x01

/*****************************************************************************/
#घोषणा      CHIP_CTRL                0x100
/* Reserved [27] */
/* Reserved [31:21] */
#घोषणा      FLD_CHIP_ACFG_DIS        0x00100000
/* Reserved [19] */
#घोषणा      FLD_DUAL_MODE_ADC2       0x00040000
#घोषणा      FLD_SIF_EN               0x00020000
#घोषणा      FLD_SOFT_RST             0x00010000
#घोषणा      FLD_DEVICE_ID            0x0000ffff

/*****************************************************************************/
#घोषणा      AFE_CTRL                 0x104
#घोषणा      AFE_CTRL_C2HH_SRC_CTRL   0x104
#घोषणा      FLD_DIF_OUT_SEL          0xc0000000
#घोषणा      FLD_AUX_PLL_CLK_ALT_SEL  0x3c000000
#घोषणा      FLD_UV_ORDER_MODE        0x02000000
#घोषणा      FLD_FUNC_MODE            0x01800000
#घोषणा      FLD_ROT1_PHASE_CTL       0x007f8000
#घोषणा      FLD_AUD_IN_SEL           0x00004000
#घोषणा      FLD_LUMA_IN_SEL          0x00002000
#घोषणा      FLD_CHROMA_IN_SEL        0x00001000
/* reserve [11:10] */
#घोषणा      FLD_INV_SPEC_DIS         0x00000200
#घोषणा      FLD_VGA_SEL_CH3          0x00000100
#घोषणा      FLD_VGA_SEL_CH2          0x00000080
#घोषणा      FLD_VGA_SEL_CH1          0x00000040
#घोषणा      FLD_DCR_BYP_CH1          0x00000020
#घोषणा      FLD_DCR_BYP_CH2          0x00000010
#घोषणा      FLD_DCR_BYP_CH3          0x00000008
#घोषणा      FLD_EN_12DB_CH3          0x00000004
#घोषणा      FLD_EN_12DB_CH2          0x00000002
#घोषणा      FLD_EN_12DB_CH1          0x00000001

/* redefine in Cx231xx */
/*****************************************************************************/
#घोषणा      DC_CTRL1                 0x108
/* reserve [31:30] */
#घोषणा      FLD_CLAMP_LVL_CH1        0x3fff8000
#घोषणा      FLD_CLAMP_LVL_CH2        0x00007fff
/*****************************************************************************/

/*****************************************************************************/
#घोषणा      DC_CTRL2                 0x10c
/* reserve [31:28] */
#घोषणा      FLD_CLAMP_LVL_CH3        0x00fffe00
#घोषणा      FLD_CLAMP_WIND_LENTH     0x000001e0
#घोषणा      FLD_C2HH_SAT_MIN         0x0000001e
#घोषणा      FLD_FLT_BYP_SEL          0x00000001
/*****************************************************************************/

/*****************************************************************************/
#घोषणा      DC_CTRL3                 0x110
/* reserve [31:16] */
#घोषणा      FLD_ERR_GAIN_CTL         0x00070000
#घोषणा      FLD_LPF_MIN              0x0000ffff
/*****************************************************************************/

/*****************************************************************************/
#घोषणा      DC_CTRL4                 0x114
/* reserve [31:31] */
#घोषणा      FLD_INTG_CH1             0x7fffffff
/*****************************************************************************/

/*****************************************************************************/
#घोषणा      DC_CTRL5                 0x118
/* reserve [31:31] */
#घोषणा      FLD_INTG_CH2             0x7fffffff
/*****************************************************************************/

/*****************************************************************************/
#घोषणा      DC_CTRL6                 0x11c
/* reserve [31:31] */
#घोषणा      FLD_INTG_CH3             0x7fffffff
/*****************************************************************************/

/*****************************************************************************/
#घोषणा      PIN_CTRL                 0x120
#घोषणा      FLD_OEF_AGC_RF           0x00000001
#घोषणा      FLD_OEF_AGC_IFVGA        0x00000002
#घोषणा      FLD_OEF_AGC_IF           0x00000004
#घोषणा      FLD_REG_BO_PUD           0x80000000
#घोषणा      FLD_IR_IRQ_STAT          0x40000000
#घोषणा      FLD_AUD_IRQ_STAT         0x20000000
#घोषणा      FLD_VID_IRQ_STAT         0x10000000
/* Reserved [27:26] */
#घोषणा      FLD_IRQ_N_OUT_EN         0x02000000
#घोषणा      FLD_IRQ_N_POLAR          0x01000000
/* Reserved [23:6] */
#घोषणा      FLD_OE_AUX_PLL_CLK       0x00000020
#घोषणा      FLD_OE_I2S_BCLK          0x00000010
#घोषणा      FLD_OE_I2S_WCLK          0x00000008
#घोषणा      FLD_OE_AGC_IF            0x00000004
#घोषणा      FLD_OE_AGC_IFVGA         0x00000002
#घोषणा      FLD_OE_AGC_RF            0x00000001

/*****************************************************************************/
#घोषणा      AUD_IO_CTRL              0x124
/* Reserved [31:8] */
#घोषणा      FLD_I2S_PORT_सूची         0x00000080
#घोषणा      FLD_I2S_OUT_SRC          0x00000040
#घोषणा      FLD_AUD_CHAN3_SRC        0x00000030
#घोषणा      FLD_AUD_CHAN2_SRC        0x0000000c
#घोषणा      FLD_AUD_CHAN1_SRC        0x00000003

/*****************************************************************************/
#घोषणा      AUD_LOCK1                0x128
#घोषणा      FLD_AUD_LOCK_KI_SHIFT    0xc0000000
#घोषणा      FLD_AUD_LOCK_KD_SHIFT    0x30000000
/* Reserved [27:25] */
#घोषणा      FLD_EN_AV_LOCK           0x01000000
#घोषणा      FLD_VID_COUNT            0x00ffffff

/*****************************************************************************/
#घोषणा      AUD_LOCK2                0x12c
#घोषणा      FLD_AUD_LOCK_KI_MULT     0xf0000000
#घोषणा      FLD_AUD_LOCK_KD_MULT     0x0F000000
/* Reserved [23:22] */
#घोषणा      FLD_AUD_LOCK_FREQ_SHIFT  0x00300000
#घोषणा      FLD_AUD_COUNT            0x000fffff

/*****************************************************************************/
#घोषणा      AFE_DIAG_CTRL1           0x134
/* Reserved [31:16] */
#घोषणा      FLD_CUV_DLY_LENGTH       0x0000ff00
#घोषणा      FLD_YC_DLY_LENGTH        0x000000ff

/*****************************************************************************/
/* Poalris redefine */
#घोषणा      AFE_DIAG_CTRL3           0x138
/* Reserved [31:26] */
#घोषणा      FLD_AUD_DUAL_FLAG_POL    0x02000000
#घोषणा      FLD_VID_DUAL_FLAG_POL    0x01000000
/* Reserved [23:23] */
#घोषणा      FLD_COL_CLAMP_DIS_CH1    0x00400000
#घोषणा      FLD_COL_CLAMP_DIS_CH2    0x00200000
#घोषणा      FLD_COL_CLAMP_DIS_CH3    0x00100000

#घोषणा      TEST_CTRL1               0x144
/* Reserved [31:29] */
#घोषणा      FLD_LBIST_EN             0x10000000
/* Reserved [27:10] */
#घोषणा      FLD_FI_BIST_INTR_R       0x0000200
#घोषणा      FLD_FI_BIST_INTR_L       0x0000100
#घोषणा      FLD_BIST_FAIL_AUD_PLL    0x0000080
#घोषणा      FLD_BIST_INTR_AUD_PLL    0x0000040
#घोषणा      FLD_BIST_FAIL_VID_PLL    0x0000020
#घोषणा      FLD_BIST_INTR_VID_PLL    0x0000010
/* Reserved [3:1] */
#घोषणा      FLD_CIR_TEST_DIS         0x00000001

/*****************************************************************************/
#घोषणा      TEST_CTRL2               0x148
#घोषणा      FLD_TSXCLK_POL_CTL       0x80000000
#घोषणा      FLD_ISO_CTL_SEL          0x40000000
#घोषणा      FLD_ISO_CTL_EN           0x20000000
#घोषणा      FLD_BIST_DEBUGZ          0x10000000
#घोषणा      FLD_AUD_BIST_TEST_H      0x0f000000
/* Reserved [23:22] */
#घोषणा      FLD_FLTRN_BIST_TEST_H    0x00020000
#घोषणा      FLD_VID_BIST_TEST_H      0x00010000
/* Reserved [19:17] */
#घोषणा      FLD_BIST_TEST_H          0x00010000
/* Reserved [15:13] */
#घोषणा      FLD_TAB_EN               0x00001000
/* Reserved [11:0] */

/*****************************************************************************/
#घोषणा      BIST_STAT                0x14c
#घोषणा      FLD_AUD_BIST_FAIL_H      0xfff00000
#घोषणा      FLD_FLTRN_BIST_FAIL_H    0x00180000
#घोषणा      FLD_VID_BIST_FAIL_H      0x00070000
#घोषणा      FLD_AUD_BIST_TST_DONE    0x0000fff0
#घोषणा      FLD_FLTRN_BIST_TST_DONE  0x00000008
#घोषणा      FLD_VID_BIST_TST_DONE    0x00000007

/*****************************************************************************/
/* DirectIF रेजिस्टरs definition have been moved to DIF_reg.h                */
/*****************************************************************************/
#घोषणा      MODE_CTRL                0x400
#घोषणा      FLD_AFD_PAL60_DIS        0x20000000
#घोषणा      FLD_AFD_FORCE_SECAM      0x10000000
#घोषणा      FLD_AFD_FORCE_PALNC      0x08000000
#घोषणा      FLD_AFD_FORCE_PAL        0x04000000
#घोषणा      FLD_AFD_PALM_SEL         0x03000000
#घोषणा      FLD_CKILL_MODE           0x00300000
#घोषणा      FLD_COMB_NOTCH_MODE      0x00c00000       /* bit[19:18] */
#घोषणा      FLD_CLR_LOCK_STAT        0x00020000
#घोषणा      FLD_FAST_LOCK_MD         0x00010000
#घोषणा      FLD_WCEN                 0x00008000
#घोषणा      FLD_CAGCEN               0x00004000
#घोषणा      FLD_CKILLEN              0x00002000
#घोषणा      FLD_AUTO_SC_LOCK         0x00001000
#घोषणा      FLD_MAN_SC_FAST_LOCK     0x00000800
#घोषणा      FLD_INPUT_MODE           0x00000600
#घोषणा      FLD_AFD_ACQUIRE          0x00000100
#घोषणा      FLD_AFD_NTSC_SEL         0x00000080
#घोषणा      FLD_AFD_PAL_SEL          0x00000040
#घोषणा      FLD_ACFG_DIS             0x00000020
#घोषणा      FLD_SQ_PIXEL             0x00000010
#घोषणा      FLD_VID_FMT_SEL          0x0000000f

/*****************************************************************************/
#घोषणा      OUT_CTRL1                0x404
#घोषणा      FLD_POLAR                0x7f000000
/* Reserved [23] */
#घोषणा      FLD_RND_MODE             0x00600000
#घोषणा      FLD_VIPCLAMP_EN          0x00100000
#घोषणा      FLD_VIPBLANK_EN          0x00080000
#घोषणा      FLD_VIP_OPT_AL           0x00040000
#घोषणा      FLD_IDID0_SOURCE         0x00020000
#घोषणा      FLD_DCMODE               0x00010000
#घोषणा      FLD_CLK_GATING           0x0000c000
#घोषणा      FLD_CLK_INVERT           0x00002000
#घोषणा      FLD_HSFMT                0x00001000
#घोषणा      FLD_VALIDFMT             0x00000800
#घोषणा      FLD_ACTFMT               0x00000400
#घोषणा      FLD_SWAPRAW              0x00000200
#घोषणा      FLD_CLAMPRAW_EN          0x00000100
#घोषणा      FLD_BLUE_FIELD_EN        0x00000080
#घोषणा      FLD_BLUE_FIELD_ACT       0x00000040
#घोषणा      FLD_TASKBIT_VAL          0x00000020
#घोषणा      FLD_ANC_DATA_EN          0x00000010
#घोषणा      FLD_VBIHACTRAW_EN        0x00000008
#घोषणा      FLD_MODE10B              0x00000004
#घोषणा      FLD_OUT_MODE             0x00000003

/*****************************************************************************/
#घोषणा      OUT_CTRL2                0x408
#घोषणा      FLD_AUD_GRP              0xc0000000
#घोषणा      FLD_SAMPLE_RATE          0x30000000
#घोषणा      FLD_AUD_ANC_EN           0x08000000
#घोषणा      FLD_EN_C                 0x04000000
#घोषणा      FLD_EN_B                 0x02000000
#घोषणा      FLD_EN_A                 0x01000000
/* Reserved [23:20] */
#घोषणा      FLD_IDID1_LSB            0x000c0000
#घोषणा      FLD_IDID0_LSB            0x00030000
#घोषणा      FLD_IDID1_MSB            0x0000ff00
#घोषणा      FLD_IDID0_MSB            0x000000ff

/*****************************************************************************/
#घोषणा      GEN_STAT                 0x40c
#घोषणा      FLD_VCR_DETECT           0x00800000
#घोषणा      FLD_SPECIAL_PLAY_N       0x00400000
#घोषणा      FLD_VPRES                0x00200000
#घोषणा      FLD_AGC_LOCK             0x00100000
#घोषणा      FLD_CSC_LOCK             0x00080000
#घोषणा      FLD_VLOCK                0x00040000
#घोषणा      FLD_SRC_LOCK             0x00020000
#घोषणा      FLD_HLOCK                0x00010000
#घोषणा      FLD_VSYNC_N              0x00008000
#घोषणा      FLD_SRC_FIFO_UFLOW       0x00004000
#घोषणा      FLD_SRC_FIFO_OFLOW       0x00002000
#घोषणा      FLD_FIELD                0x00001000
#घोषणा      FLD_AFD_FMT_STAT         0x00000f00
#घोषणा      FLD_MV_TYPE2_PAIR        0x00000080
#घोषणा      FLD_MV_T3CS              0x00000040
#घोषणा      FLD_MV_CS                0x00000020
#घोषणा      FLD_MV_PSP               0x00000010
/* Reserved [3] */
#घोषणा      FLD_MV_CDAT              0x00000003

/*****************************************************************************/
#घोषणा      INT_STAT_MASK            0x410
#घोषणा      FLD_COMB_3D_FIFO_MSK     0x80000000
#घोषणा      FLD_WSS_DAT_AVAIL_MSK    0x40000000
#घोषणा      FLD_GS2_DAT_AVAIL_MSK    0x20000000
#घोषणा      FLD_GS1_DAT_AVAIL_MSK    0x10000000
#घोषणा      FLD_CC_DAT_AVAIL_MSK     0x08000000
#घोषणा      FLD_VPRES_CHANGE_MSK     0x04000000
#घोषणा      FLD_MV_CHANGE_MSK        0x02000000
#घोषणा      FLD_END_VBI_EVEN_MSK     0x01000000
#घोषणा      FLD_END_VBI_ODD_MSK      0x00800000
#घोषणा      FLD_FMT_CHANGE_MSK       0x00400000
#घोषणा      FLD_VSYNC_TRAIL_MSK      0x00200000
#घोषणा      FLD_HLOCK_CHANGE_MSK     0x00100000
#घोषणा      FLD_VLOCK_CHANGE_MSK     0x00080000
#घोषणा      FLD_CSC_LOCK_CHANGE_MSK  0x00040000
#घोषणा      FLD_SRC_FIFO_UFLOW_MSK   0x00020000
#घोषणा      FLD_SRC_FIFO_OFLOW_MSK   0x00010000
#घोषणा      FLD_COMB_3D_FIFO_STAT    0x00008000
#घोषणा      FLD_WSS_DAT_AVAIL_STAT   0x00004000
#घोषणा      FLD_GS2_DAT_AVAIL_STAT   0x00002000
#घोषणा      FLD_GS1_DAT_AVAIL_STAT   0x00001000
#घोषणा      FLD_CC_DAT_AVAIL_STAT    0x00000800
#घोषणा      FLD_VPRES_CHANGE_STAT    0x00000400
#घोषणा      FLD_MV_CHANGE_STAT       0x00000200
#घोषणा      FLD_END_VBI_EVEN_STAT    0x00000100
#घोषणा      FLD_END_VBI_ODD_STAT     0x00000080
#घोषणा      FLD_FMT_CHANGE_STAT      0x00000040
#घोषणा      FLD_VSYNC_TRAIL_STAT     0x00000020
#घोषणा      FLD_HLOCK_CHANGE_STAT    0x00000010
#घोषणा      FLD_VLOCK_CHANGE_STAT    0x00000008
#घोषणा      FLD_CSC_LOCK_CHANGE_STAT 0x00000004
#घोषणा      FLD_SRC_FIFO_UFLOW_STAT  0x00000002
#घोषणा      FLD_SRC_FIFO_OFLOW_STAT  0x00000001

/*****************************************************************************/
#घोषणा      LUMA_CTRL                0x414
#घोषणा      BRIGHTNESS_CTRL_BYTE     0x414
#घोषणा      CONTRAST_CTRL_BYTE       0x415
#घोषणा      LUMA_CTRL_BYTE_3         0x416
#घोषणा      FLD_LUMA_CORE_SEL        0x00c00000
#घोषणा      FLD_RANGE                0x00300000
/* Reserved [19] */
#घोषणा      FLD_PEAK_EN              0x00040000
#घोषणा      FLD_PEAK_SEL             0x00030000
#घोषणा      FLD_CNTRST               0x0000ff00
#घोषणा      FLD_BRITE                0x000000ff

/*****************************************************************************/
#घोषणा      HSCALE_CTRL              0x418
#घोषणा      FLD_HFILT                0x03000000
#घोषणा      FLD_HSCALE               0x00ffffff

/*****************************************************************************/
#घोषणा      VSCALE_CTRL              0x41c
#घोषणा      FLD_LINE_AVG_DIS         0x01000000
/* Reserved [23:20] */
#घोषणा      FLD_VS_INTRLACE          0x00080000
#घोषणा      FLD_VFILT                0x00070000
/* Reserved [15:13] */
#घोषणा      FLD_VSCALE               0x00001fff

/*****************************************************************************/
#घोषणा      CHROMA_CTRL              0x420
#घोषणा      USAT_CTRL_BYTE           0x420
#घोषणा      VSAT_CTRL_BYTE           0x421
#घोषणा      HUE_CTRL_BYTE            0x422
#घोषणा      FLD_C_LPF_EN             0x20000000
#घोषणा      FLD_CHR_DELAY            0x1c000000
#घोषणा      FLD_C_CORE_SEL           0x03000000
#घोषणा      FLD_HUE                  0x00ff0000
#घोषणा      FLD_VSAT                 0x0000ff00
#घोषणा      FLD_USAT                 0x000000ff

/*****************************************************************************/
#घोषणा      VBI_LINE_CTRL1           0x424
#घोषणा      FLD_VBI_MD_LINE4         0xff000000
#घोषणा      FLD_VBI_MD_LINE3         0x00ff0000
#घोषणा      FLD_VBI_MD_LINE2         0x0000ff00
#घोषणा      FLD_VBI_MD_LINE1         0x000000ff

/*****************************************************************************/
#घोषणा      VBI_LINE_CTRL2           0x428
#घोषणा      FLD_VBI_MD_LINE8         0xff000000
#घोषणा      FLD_VBI_MD_LINE7         0x00ff0000
#घोषणा      FLD_VBI_MD_LINE6         0x0000ff00
#घोषणा      FLD_VBI_MD_LINE5         0x000000ff

/*****************************************************************************/
#घोषणा      VBI_LINE_CTRL3           0x42c
#घोषणा      FLD_VBI_MD_LINE12        0xff000000
#घोषणा      FLD_VBI_MD_LINE11        0x00ff0000
#घोषणा      FLD_VBI_MD_LINE10        0x0000ff00
#घोषणा      FLD_VBI_MD_LINE9         0x000000ff

/*****************************************************************************/
#घोषणा      VBI_LINE_CTRL4           0x430
#घोषणा      FLD_VBI_MD_LINE16        0xff000000
#घोषणा      FLD_VBI_MD_LINE15        0x00ff0000
#घोषणा      FLD_VBI_MD_LINE14        0x0000ff00
#घोषणा      FLD_VBI_MD_LINE13        0x000000ff

/*****************************************************************************/
#घोषणा      VBI_LINE_CTRL5           0x434
#घोषणा      FLD_VBI_MD_LINE17        0x000000ff

/*****************************************************************************/
#घोषणा      VBI_FC_CFG               0x438
#घोषणा      FLD_FC_ALT2              0xff000000
#घोषणा      FLD_FC_ALT1              0x00ff0000
#घोषणा      FLD_FC_ALT2_TYPE         0x0000f000
#घोषणा      FLD_FC_ALT1_TYPE         0x00000f00
/* Reserved [7:1] */
#घोषणा      FLD_FC_SEARCH_MODE       0x00000001

/*****************************************************************************/
#घोषणा      VBI_MISC_CFG1            0x43c
#घोषणा      FLD_TTX_PKTADRU          0xfff00000
#घोषणा      FLD_TTX_PKTADRL          0x000fff00
/* Reserved [7:6] */
#घोषणा      FLD_MOJI_PACK_DIS        0x00000020
#घोषणा      FLD_VPS_DEC_DIS          0x00000010
#घोषणा      FLD_CRI_MARG_SCALE       0x0000000c
#घोषणा      FLD_EDGE_RESYNC_EN       0x00000002
#घोषणा      FLD_ADAPT_SLICE_DIS      0x00000001

/*****************************************************************************/
#घोषणा      VBI_MISC_CFG2            0x440
#घोषणा      FLD_HAMMING_TYPE         0x0f000000
/* Reserved [23:20] */
#घोषणा      FLD_WSS_FIFO_RST         0x00080000
#घोषणा      FLD_GS2_FIFO_RST         0x00040000
#घोषणा      FLD_GS1_FIFO_RST         0x00020000
#घोषणा      FLD_CC_FIFO_RST          0x00010000
/* Reserved [15:12] */
#घोषणा      FLD_VBI3_SDID            0x00000f00
#घोषणा      FLD_VBI2_SDID            0x000000f0
#घोषणा      FLD_VBI1_SDID            0x0000000f

/*****************************************************************************/
#घोषणा      VBI_PAY1                 0x444
#घोषणा      FLD_GS1_FIFO_DAT         0xFF000000
#घोषणा      FLD_GS1_STAT             0x00FF0000
#घोषणा      FLD_CC_FIFO_DAT          0x0000FF00
#घोषणा      FLD_CC_STAT              0x000000FF

/*****************************************************************************/
#घोषणा      VBI_PAY2                 0x448
#घोषणा      FLD_WSS_FIFO_DAT         0xff000000
#घोषणा      FLD_WSS_STAT             0x00ff0000
#घोषणा      FLD_GS2_FIFO_DAT         0x0000ff00
#घोषणा      FLD_GS2_STAT             0x000000ff

/*****************************************************************************/
#घोषणा      VBI_CUST1_CFG1           0x44c
/* Reserved [31] */
#घोषणा      FLD_VBI1_CRIWIN          0x7f000000
#घोषणा      FLD_VBI1_SLICE_DIST      0x00f00000
#घोषणा      FLD_VBI1_BITINC          0x000fff00
#घोषणा      FLD_VBI1_HDELAY          0x000000ff

/*****************************************************************************/
#घोषणा      VBI_CUST1_CFG2           0x450
#घोषणा      FLD_VBI1_FC_LENGTH       0x1f000000
#घोषणा      FLD_VBI1_FRAME_CODE      0x00ffffff

/*****************************************************************************/
#घोषणा      VBI_CUST1_CFG3           0x454
#घोषणा      FLD_VBI1_HAM_EN          0x80000000
#घोषणा      FLD_VBI1_FIFO_MODE       0x70000000
#घोषणा      FLD_VBI1_FORMAT_TYPE     0x0f000000
#घोषणा      FLD_VBI1_PAYLD_LENGTH    0x00ff0000
#घोषणा      FLD_VBI1_CRI_LENGTH      0x0000f000
#घोषणा      FLD_VBI1_CRI_MARGIN      0x00000f00
#घोषणा      FLD_VBI1_CRI_TIME        0x000000ff

/*****************************************************************************/
#घोषणा      VBI_CUST2_CFG1           0x458
/* Reserved [31] */
#घोषणा      FLD_VBI2_CRIWIN          0x7f000000
#घोषणा      FLD_VBI2_SLICE_DIST      0x00f00000
#घोषणा      FLD_VBI2_BITINC          0x000fff00
#घोषणा      FLD_VBI2_HDELAY          0x000000ff

/*****************************************************************************/
#घोषणा      VBI_CUST2_CFG2           0x45c
#घोषणा      FLD_VBI2_FC_LENGTH       0x1f000000
#घोषणा      FLD_VBI2_FRAME_CODE      0x00ffffff

/*****************************************************************************/
#घोषणा      VBI_CUST2_CFG3           0x460
#घोषणा      FLD_VBI2_HAM_EN          0x80000000
#घोषणा      FLD_VBI2_FIFO_MODE       0x70000000
#घोषणा      FLD_VBI2_FORMAT_TYPE     0x0f000000
#घोषणा      FLD_VBI2_PAYLD_LENGTH    0x00ff0000
#घोषणा      FLD_VBI2_CRI_LENGTH      0x0000f000
#घोषणा      FLD_VBI2_CRI_MARGIN      0x00000f00
#घोषणा      FLD_VBI2_CRI_TIME        0x000000ff

/*****************************************************************************/
#घोषणा      VBI_CUST3_CFG1           0x464
/* Reserved [31] */
#घोषणा      FLD_VBI3_CRIWIN          0x7f000000
#घोषणा      FLD_VBI3_SLICE_DIST      0x00f00000
#घोषणा      FLD_VBI3_BITINC          0x000fff00
#घोषणा      FLD_VBI3_HDELAY          0x000000ff

/*****************************************************************************/
#घोषणा      VBI_CUST3_CFG2           0x468
#घोषणा      FLD_VBI3_FC_LENGTH       0x1f000000
#घोषणा      FLD_VBI3_FRAME_CODE      0x00ffffff

/*****************************************************************************/
#घोषणा      VBI_CUST3_CFG3           0x46c
#घोषणा      FLD_VBI3_HAM_EN          0x80000000
#घोषणा      FLD_VBI3_FIFO_MODE       0x70000000
#घोषणा      FLD_VBI3_FORMAT_TYPE     0x0f000000
#घोषणा      FLD_VBI3_PAYLD_LENGTH    0x00ff0000
#घोषणा      FLD_VBI3_CRI_LENGTH      0x0000f000
#घोषणा      FLD_VBI3_CRI_MARGIN      0x00000f00
#घोषणा      FLD_VBI3_CRI_TIME        0x000000ff

/*****************************************************************************/
#घोषणा      HORIZ_TIM_CTRL           0x470
#घोषणा      FLD_BGDEL_CNT            0xff000000
/* Reserved [23:22] */
#घोषणा      FLD_HACTIVE_CNT          0x003ff000
/* Reserved [11:10] */
#घोषणा      FLD_HBLANK_CNT           0x000003ff

/*****************************************************************************/
#घोषणा      VERT_TIM_CTRL            0x474
#घोषणा      FLD_V656BLANK_CNT        0xff000000
/* Reserved [23:22] */
#घोषणा      FLD_VACTIVE_CNT          0x003ff000
/* Reserved [11:10] */
#घोषणा      FLD_VBLANK_CNT           0x000003ff

/*****************************************************************************/
#घोषणा      SRC_COMB_CFG             0x478
#घोषणा      FLD_CCOMB_2LN_CHECK      0x80000000
#घोषणा      FLD_CCOMB_3LN_EN         0x40000000
#घोषणा      FLD_CCOMB_2LN_EN         0x20000000
#घोषणा      FLD_CCOMB_3D_EN          0x10000000
/* Reserved [27] */
#घोषणा      FLD_LCOMB_3LN_EN         0x04000000
#घोषणा      FLD_LCOMB_2LN_EN         0x02000000
#घोषणा      FLD_LCOMB_3D_EN          0x01000000
#घोषणा      FLD_LUMA_LPF_SEL         0x00c00000
#घोषणा      FLD_UV_LPF_SEL           0x00300000
#घोषणा      FLD_BLEND_SLOPE          0x000f0000
#घोषणा      FLD_CCOMB_REDUCE_EN      0x00008000
/* Reserved [14:10] */
#घोषणा      FLD_SRC_DECIM_RATIO      0x000003ff

/*****************************************************************************/
#घोषणा      CHROMA_VBIOFF_CFG        0x47c
#घोषणा      FLD_VBI_VOFFSET          0x1f000000
/* Reserved [23:20] */
#घोषणा      FLD_SC_STEP              0x000fffff

/*****************************************************************************/
#घोषणा      FIELD_COUNT              0x480
#घोषणा      FLD_FIELD_COUNT_FLD      0x000003ff

/*****************************************************************************/
#घोषणा      MISC_TIM_CTRL            0x484
#घोषणा      FLD_DEBOUNCE_COUNT       0xc0000000
#घोषणा      FLD_VT_LINE_CNT_HYST     0x30000000
/* Reserved [27] */
#घोषणा      FLD_AFD_STAT             0x07ff0000
#घोषणा      FLD_VPRES_VERT_EN        0x00008000
/* Reserved [14:12] */
#घोषणा      FLD_HR32                 0x00000800
#घोषणा      FLD_TDALGN               0x00000400
#घोषणा      FLD_TDFIELD              0x00000200
/* Reserved [8:6] */
#घोषणा      FLD_TEMPDEC              0x0000003f

/*****************************************************************************/
#घोषणा      DFE_CTRL1                0x488
#घोषणा      FLD_CLAMP_AUTO_EN        0x80000000
#घोषणा      FLD_AGC_AUTO_EN          0x40000000
#घोषणा      FLD_VGA_CRUSH_EN         0x20000000
#घोषणा      FLD_VGA_AUTO_EN          0x10000000
#घोषणा      FLD_VBI_GATE_EN          0x08000000
#घोषणा      FLD_CLAMP_LEVEL          0x07000000
/* Reserved [23:22] */
#घोषणा      FLD_CLAMP_SKIP_CNT       0x00300000
#घोषणा      FLD_AGC_GAIN             0x000fff00
/* Reserved [7:6] */
#घोषणा      FLD_VGA_GAIN             0x0000003f

/*****************************************************************************/
#घोषणा      DFE_CTRL2                0x48c
#घोषणा      FLD_VGA_ACQUIRE_RANGE    0x00ff0000
#घोषणा      FLD_VGA_TRACK_RANGE      0x0000ff00
#घोषणा      FLD_VGA_SYNC             0x000000ff

/*****************************************************************************/
#घोषणा      DFE_CTRL3                0x490
#घोषणा      FLD_BP_PERCENT           0xff000000
#घोषणा      FLD_DFT_THRESHOLD        0x00ff0000
/* Reserved [15:12] */
#घोषणा      FLD_SYNC_WIDTH_SEL       0x00000600
#घोषणा      FLD_BP_LOOP_GAIN         0x00000300
#घोषणा      FLD_SYNC_LOOP_GAIN       0x000000c0
/* Reserved [5:4] */
#घोषणा      FLD_AGC_LOOP_GAIN        0x0000000c
#घोषणा      FLD_DCC_LOOP_GAIN        0x00000003

/*****************************************************************************/
#घोषणा      PLL_CTRL                 0x494
#घोषणा      FLD_PLL_KD               0xff000000
#घोषणा      FLD_PLL_KI               0x00ff0000
#घोषणा      FLD_PLL_MAX_OFFSET       0x0000ffff

/*****************************************************************************/
#घोषणा      HTL_CTRL                 0x498
/* Reserved [31:24] */
#घोषणा      FLD_AUTO_LOCK_SPD        0x00080000
#घोषणा      FLD_MAN_FAST_LOCK        0x00040000
#घोषणा      FLD_HTL_15K_EN           0x00020000
#घोषणा      FLD_HTL_500K_EN          0x00010000
#घोषणा      FLD_HTL_KD               0x0000ff00
#घोषणा      FLD_HTL_KI               0x000000ff

/*****************************************************************************/
#घोषणा      COMB_CTRL                0x49c
#घोषणा      FLD_COMB_PHASE_LIMIT     0xff000000
#घोषणा      FLD_CCOMB_ERR_LIMIT      0x00ff0000
#घोषणा      FLD_LUMA_THRESHOLD       0x0000ff00
#घोषणा      FLD_LCOMB_ERR_LIMIT      0x000000ff

/*****************************************************************************/
#घोषणा      CRUSH_CTRL               0x4a0
#घोषणा      FLD_WTW_EN               0x00400000
#घोषणा      FLD_CRUSH_FREQ           0x00200000
#घोषणा      FLD_MAJ_SEL_EN           0x00100000
#घोषणा      FLD_MAJ_SEL              0x000c0000
/* Reserved [17:15] */
#घोषणा      FLD_SYNC_TIP_REDUCE      0x00007e00
/* Reserved [8:6] */
#घोषणा      FLD_SYNC_TIP_INC         0x0000003f

/*****************************************************************************/
#घोषणा      SOFT_RST_CTRL            0x4a4
#घोषणा      FLD_VD_SOFT_RST          0x00008000
/* Reserved [14:12] */
#घोषणा      FLD_REG_RST_MSK          0x00000800
#घोषणा      FLD_VOF_RST_MSK          0x00000400
#घोषणा      FLD_MVDET_RST_MSK        0x00000200
#घोषणा      FLD_VBI_RST_MSK          0x00000100
#घोषणा      FLD_SCALE_RST_MSK        0x00000080
#घोषणा      FLD_CHROMA_RST_MSK       0x00000040
#घोषणा      FLD_LUMA_RST_MSK         0x00000020
#घोषणा      FLD_VTG_RST_MSK          0x00000010
#घोषणा      FLD_YCSEP_RST_MSK        0x00000008
#घोषणा      FLD_SRC_RST_MSK          0x00000004
#घोषणा      FLD_DFE_RST_MSK          0x00000002
/* Reserved [0] */

/*****************************************************************************/
#घोषणा      MV_DT_CTRL1              0x4a8
/* Reserved [31:29] */
#घोषणा      FLD_PSP_STOP_LINE        0x1f000000
/* Reserved [23:21] */
#घोषणा      FLD_PSP_STRT_LINE        0x001f0000
/* Reserved [15] */
#घोषणा      FLD_PSP_LLIMW            0x00007f00
/* Reserved [7] */
#घोषणा      FLD_PSP_ULIMW            0x0000007f

/*****************************************************************************/
#घोषणा      MV_DT_CTRL2              0x4aC
#घोषणा      FLD_CS_STOPWIN           0xff000000
#घोषणा      FLD_CS_STRTWIN           0x00ff0000
#घोषणा      FLD_CS_WIDTH             0x0000ff00
#घोषणा      FLD_PSP_SPEC_VAL         0x000000ff

/*****************************************************************************/
#घोषणा      MV_DT_CTRL3              0x4B0
#घोषणा      FLD_AUTO_RATE_DIS        0x80000000
#घोषणा      FLD_HLOCK_DIS            0x40000000
#घोषणा      FLD_SEL_FIELD_CNT        0x20000000
#घोषणा      FLD_CS_TYPE2_SEL         0x10000000
#घोषणा      FLD_CS_LINE_THRSH_SEL    0x08000000
#घोषणा      FLD_CS_ATHRESH_SEL       0x04000000
#घोषणा      FLD_PSP_SPEC_SEL         0x02000000
#घोषणा      FLD_PSP_LINES_SEL        0x01000000
#घोषणा      FLD_FIELD_CNT            0x00f00000
#घोषणा      FLD_CS_TYPE2_CNT         0x000fc000
#घोषणा      FLD_CS_LINE_CNT          0x00003f00
#घोषणा      FLD_CS_ATHRESH_LEV       0x000000ff

/*****************************************************************************/
#घोषणा      CHIP_VERSION             0x4b4
/* Cx231xx redefine  */
#घोषणा      VERSION                  0x4b4
#घोषणा      FLD_REV_ID               0x000000ff

/*****************************************************************************/
#घोषणा      MISC_DIAG_CTRL           0x4b8
/* Reserved [31:24] */
#घोषणा      FLD_SC_CONVERGE_THRESH   0x00ff0000
#घोषणा      FLD_CCOMB_ERR_LIMIT_3D   0x0000ff00
#घोषणा      FLD_LCOMB_ERR_LIMIT_3D   0x000000ff

/*****************************************************************************/
#घोषणा      VBI_PASS_CTRL            0x4bc
#घोषणा      FLD_VBI_PASS_MD          0x00200000
#घोषणा      FLD_VBI_SETUP_DIS        0x00100000
#घोषणा      FLD_PASS_LINE_CTRL       0x000fffff

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      VCR_DET_CTRL             0x4c0
#घोषणा      FLD_EN_FIELD_PHASE_DET   0x80000000
#घोषणा      FLD_EN_HEAD_SW_DET       0x40000000
#घोषणा      FLD_FIELD_PHASE_LENGTH   0x01ff0000
/* Reserved [29:25] */
#घोषणा      FLD_FIELD_PHASE_DELAY    0x0000ff00
#घोषणा      FLD_FIELD_PHASE_LIMIT    0x000000f0
#घोषणा      FLD_HEAD_SW_DET_LIMIT    0x0000000f

/*****************************************************************************/
#घोषणा      DL_CTL                   0x800
#घोषणा      DL_CTL_ADDRESS_LOW       0x800    /* Byte 1 in DL_CTL */
#घोषणा      DL_CTL_ADDRESS_HIGH      0x801    /* Byte 2 in DL_CTL */
#घोषणा      DL_CTL_DATA              0x802    /* Byte 3 in DL_CTL */
#घोषणा      DL_CTL_CONTROL           0x803    /* Byte 4 in DL_CTL */
/* Reserved [31:5] */
#घोषणा      FLD_START_8051           0x10000000
#घोषणा      FLD_DL_ENABLE            0x08000000
#घोषणा      FLD_DL_AUTO_INC          0x04000000
#घोषणा      FLD_DL_MAP               0x03000000

/*****************************************************************************/
#घोषणा      STD_DET_STATUS           0x804
#घोषणा      FLD_SPARE_STATUS1        0xff000000
#घोषणा      FLD_SPARE_STATUS0        0x00ff0000
#घोषणा      FLD_MOD_DET_STATUS1      0x0000ff00
#घोषणा      FLD_MOD_DET_STATUS0      0x000000ff

/*****************************************************************************/
#घोषणा      AUD_BUILD_NUM            0x806
#घोषणा      AUD_VER_NUM              0x807
#घोषणा      STD_DET_CTL              0x808
#घोषणा      STD_DET_CTL_AUD_CTL      0x808    /* Byte 1 in STD_DET_CTL */
#घोषणा      STD_DET_CTL_PREF_MODE    0x809    /* Byte 2 in STD_DET_CTL */
#घोषणा      FLD_SPARE_CTL0           0xff000000
#घोषणा      FLD_DIS_DBX              0x00800000
#घोषणा      FLD_DIS_BTSC             0x00400000
#घोषणा      FLD_DIS_NICAM_A2         0x00200000
#घोषणा      FLD_VIDEO_PRESENT        0x00100000
#घोषणा      FLD_DW8051_VIDEO_FORMAT  0x000f0000
#घोषणा      FLD_PREF_DEC_MODE        0x0000ff00
#घोषणा      FLD_AUD_CONFIG           0x000000ff

/*****************************************************************************/
#घोषणा      DW8051_INT               0x80c
#घोषणा      FLD_VIDEO_PRESENT_CHANGE 0x80000000
#घोषणा      FLD_VIDEO_CHANGE         0x40000000
#घोषणा      FLD_RDS_READY            0x20000000
#घोषणा      FLD_AC97_INT             0x10000000
#घोषणा      FLD_NICAM_BIT_ERROR_TOO_HIGH         0x08000000
#घोषणा      FLD_NICAM_LOCK           0x04000000
#घोषणा      FLD_NICAM_UNLOCK         0x02000000
#घोषणा      FLD_DFT4_TH_CMP          0x01000000
/* Reserved [23:22] */
#घोषणा      FLD_LOCK_IND_INT         0x00200000
#घोषणा      FLD_DFT3_TH_CMP          0x00100000
#घोषणा      FLD_DFT2_TH_CMP          0x00080000
#घोषणा      FLD_DFT1_TH_CMP          0x00040000
#घोषणा      FLD_FM2_DFT_TH_CMP       0x00020000
#घोषणा      FLD_FM1_DFT_TH_CMP       0x00010000
#घोषणा      FLD_VIDEO_PRESENT_EN     0x00008000
#घोषणा      FLD_VIDEO_CHANGE_EN      0x00004000
#घोषणा      FLD_RDS_READY_EN         0x00002000
#घोषणा      FLD_AC97_INT_EN          0x00001000
#घोषणा      FLD_NICAM_BIT_ERROR_TOO_HIGH_EN      0x00000800
#घोषणा      FLD_NICAM_LOCK_EN        0x00000400
#घोषणा      FLD_NICAM_UNLOCK_EN      0x00000200
#घोषणा      FLD_DFT4_TH_CMP_EN       0x00000100
/* Reserved [7] */
#घोषणा      FLD_DW8051_INT6_CTL1     0x00000040
#घोषणा      FLD_DW8051_INT5_CTL1     0x00000020
#घोषणा      FLD_DW8051_INT4_CTL1     0x00000010
#घोषणा      FLD_DW8051_INT3_CTL1     0x00000008
#घोषणा      FLD_DW8051_INT2_CTL1     0x00000004
#घोषणा      FLD_DW8051_INT1_CTL1     0x00000002
#घोषणा      FLD_DW8051_INT0_CTL1     0x00000001

/*****************************************************************************/
#घोषणा      GENERAL_CTL              0x810
#घोषणा      FLD_RDS_INT              0x80000000
#घोषणा      FLD_NBER_INT             0x40000000
#घोषणा      FLD_NLL_INT              0x20000000
#घोषणा      FLD_IFL_INT              0x10000000
#घोषणा      FLD_FDL_INT              0x08000000
#घोषणा      FLD_AFC_INT              0x04000000
#घोषणा      FLD_AMC_INT              0x02000000
#घोषणा      FLD_AC97_INT_CTL         0x01000000
#घोषणा      FLD_RDS_INT_DIS          0x00800000
#घोषणा      FLD_NBER_INT_DIS         0x00400000
#घोषणा      FLD_NLL_INT_DIS          0x00200000
#घोषणा      FLD_IFL_INT_DIS          0x00100000
#घोषणा      FLD_FDL_INT_DIS          0x00080000
#घोषणा      FLD_FC_INT_DIS           0x00040000
#घोषणा      FLD_AMC_INT_DIS          0x00020000
#घोषणा      FLD_AC97_INT_DIS         0x00010000
#घोषणा      FLD_REV_NUM              0x0000ff00
/* Reserved [7:5] */
#घोषणा      FLD_DBX_SOFT_RESET_REG   0x00000010
#घोषणा      FLD_AD_SOFT_RESET_REG    0x00000008
#घोषणा      FLD_SRC_SOFT_RESET_REG   0x00000004
#घोषणा      FLD_CDMOD_SOFT_RESET     0x00000002
#घोषणा      FLD_8051_SOFT_RESET      0x00000001

/*****************************************************************************/
#घोषणा      AAGC_CTL                 0x814
#घोषणा      FLD_AFE_12DB_EN          0x80000000
#घोषणा      FLD_AAGC_DEFAULT_EN      0x40000000
#घोषणा      FLD_AAGC_DEFAULT         0x3f000000
/* Reserved [23] */
#घोषणा      FLD_AAGC_GAIN            0x00600000
#घोषणा      FLD_AAGC_TH              0x001f0000
/* Reserved [15:14] */
#घोषणा      FLD_AAGC_HYST2           0x00003f00
/* Reserved [7:6] */
#घोषणा      FLD_AAGC_HYST1           0x0000003f

/*****************************************************************************/
#घोषणा      IF_SRC_CTL               0x818
#घोषणा      FLD_DBX_BYPASS           0x80000000
/* Reserved [30:25] */
#घोषणा      FLD_IF_SRC_MODE          0x01000000
/* Reserved [23:18] */
#घोषणा      FLD_IF_SRC_PHASE_INC     0x0001ffff

/*****************************************************************************/
#घोषणा      ANALOG_DEMOD_CTL         0x81c
#घोषणा      FLD_ROT1_PHACC_PROG      0xffff0000
/* Reserved [15] */
#घोषणा      FLD_FM1_DELAY_FIX        0x00007000
#घोषणा      FLD_PDF4_SHIFT           0x00000c00
#घोषणा      FLD_PDF3_SHIFT           0x00000300
#घोषणा      FLD_PDF2_SHIFT           0x000000c0
#घोषणा      FLD_PDF1_SHIFT           0x00000030
#घोषणा      FLD_FMBYPASS_MODE2       0x00000008
#घोषणा      FLD_FMBYPASS_MODE1       0x00000004
#घोषणा      FLD_NICAM_MODE           0x00000002
#घोषणा      FLD_BTSC_FMRADIO_MODE    0x00000001

/*****************************************************************************/
#घोषणा      ROT_FREQ_CTL             0x820
#घोषणा      FLD_ROT3_PHACC_PROG      0xffff0000
#घोषणा      FLD_ROT2_PHACC_PROG      0x0000ffff

/*****************************************************************************/
#घोषणा      FM_CTL                   0x824
#घोषणा      FLD_FM2_DC_FB_SHIFT      0xf0000000
#घोषणा      FLD_FM2_DC_INT_SHIFT     0x0f000000
#घोषणा      FLD_FM2_AFC_RESET        0x00800000
#घोषणा      FLD_FM2_DC_PASS_IN       0x00400000
#घोषणा      FLD_FM2_DAGC_SHIFT       0x00380000
#घोषणा      FLD_FM2_CORDIC_SHIFT     0x00070000
#घोषणा      FLD_FM1_DC_FB_SHIFT      0x0000f000
#घोषणा      FLD_FM1_DC_INT_SHIFT     0x00000f00
#घोषणा      FLD_FM1_AFC_RESET        0x00000080
#घोषणा      FLD_FM1_DC_PASS_IN       0x00000040
#घोषणा      FLD_FM1_DAGC_SHIFT       0x00000038
#घोषणा      FLD_FM1_CORDIC_SHIFT     0x00000007

/*****************************************************************************/
#घोषणा      LPF_PDF_CTL              0x828
/* Reserved [31:30] */
#घोषणा      FLD_LPF32_SHIFT1         0x30000000
#घोषणा      FLD_LPF32_SHIFT2         0x0c000000
#घोषणा      FLD_LPF160_SHIFTA        0x03000000
#घोषणा      FLD_LPF160_SHIFTB        0x00c00000
#घोषणा      FLD_LPF160_SHIFTC        0x00300000
#घोषणा      FLD_LPF32_COEF_SEL2      0x000c0000
#घोषणा      FLD_LPF32_COEF_SEL1      0x00030000
#घोषणा      FLD_LPF160_COEF_SELC     0x0000c000
#घोषणा      FLD_LPF160_COEF_SELB     0x00003000
#घोषणा      FLD_LPF160_COEF_SELA     0x00000c00
#घोषणा      FLD_LPF160_IN_EN_REG     0x00000300
#घोषणा      FLD_PDF4_PDF_SEL         0x000000c0
#घोषणा      FLD_PDF3_PDF_SEL         0x00000030
#घोषणा      FLD_PDF2_PDF_SEL         0x0000000c
#घोषणा      FLD_PDF1_PDF_SEL         0x00000003

/*****************************************************************************/
#घोषणा      DFT1_CTL1                0x82c
#घोषणा      FLD_DFT1_DWELL           0xffff0000
#घोषणा      FLD_DFT1_FREQ            0x0000ffff

/*****************************************************************************/
#घोषणा      DFT1_CTL2                0x830
#घोषणा      FLD_DFT1_THRESHOLD       0xffffff00
#घोषणा      FLD_DFT1_CMP_CTL         0x00000080
#घोषणा      FLD_DFT1_AVG             0x00000070
/* Reserved [3:1] */
#घोषणा      FLD_DFT1_START           0x00000001

/*****************************************************************************/
#घोषणा      DFT1_STATUS              0x834
#घोषणा      FLD_DFT1_DONE            0x80000000
#घोषणा      FLD_DFT1_TH_CMP_STAT     0x40000000
#घोषणा      FLD_DFT1_RESULT          0x3fffffff

/*****************************************************************************/
#घोषणा      DFT2_CTL1                0x838
#घोषणा      FLD_DFT2_DWELL           0xffff0000
#घोषणा      FLD_DFT2_FREQ            0x0000ffff

/*****************************************************************************/
#घोषणा      DFT2_CTL2                0x83C
#घोषणा      FLD_DFT2_THRESHOLD       0xffffff00
#घोषणा      FLD_DFT2_CMP_CTL         0x00000080
#घोषणा      FLD_DFT2_AVG             0x00000070
/* Reserved [3:1] */
#घोषणा      FLD_DFT2_START           0x00000001

/*****************************************************************************/
#घोषणा      DFT2_STATUS              0x840
#घोषणा      FLD_DFT2_DONE            0x80000000
#घोषणा      FLD_DFT2_TH_CMP_STAT     0x40000000
#घोषणा      FLD_DFT2_RESULT          0x3fffffff

/*****************************************************************************/
#घोषणा      DFT3_CTL1                0x844
#घोषणा      FLD_DFT3_DWELL           0xffff0000
#घोषणा      FLD_DFT3_FREQ            0x0000ffff

/*****************************************************************************/
#घोषणा      DFT3_CTL2                0x848
#घोषणा      FLD_DFT3_THRESHOLD       0xffffff00
#घोषणा      FLD_DFT3_CMP_CTL         0x00000080
#घोषणा      FLD_DFT3_AVG             0x00000070
/* Reserved [3:1] */
#घोषणा      FLD_DFT3_START           0x00000001

/*****************************************************************************/
#घोषणा      DFT3_STATUS              0x84c
#घोषणा      FLD_DFT3_DONE            0x80000000
#घोषणा      FLD_DFT3_TH_CMP_STAT     0x40000000
#घोषणा      FLD_DFT3_RESULT          0x3fffffff

/*****************************************************************************/
#घोषणा      DFT4_CTL1                0x850
#घोषणा      FLD_DFT4_DWELL           0xffff0000
#घोषणा      FLD_DFT4_FREQ            0x0000ffff

/*****************************************************************************/
#घोषणा      DFT4_CTL2                0x854
#घोषणा      FLD_DFT4_THRESHOLD       0xffffff00
#घोषणा      FLD_DFT4_CMP_CTL         0x00000080
#घोषणा      FLD_DFT4_AVG             0x00000070
/* Reserved [3:1] */
#घोषणा      FLD_DFT4_START           0x00000001

/*****************************************************************************/
#घोषणा      DFT4_STATUS              0x858
#घोषणा      FLD_DFT4_DONE            0x80000000
#घोषणा      FLD_DFT4_TH_CMP_STAT     0x40000000
#घोषणा      FLD_DFT4_RESULT          0x3fffffff

/*****************************************************************************/
#घोषणा      AM_MTS_DET               0x85c
#घोषणा      FLD_AM_MTS_MODE          0x80000000
/* Reserved [30:26] */
#घोषणा      FLD_AM_SUB               0x02000000
#घोषणा      FLD_AM_GAIN_EN           0x01000000
/* Reserved [23:16] */
#घोषणा      FLD_AMMTS_GAIN_SCALE     0x0000e000
#घोषणा      FLD_MTS_PDF_SHIFT        0x00001800
#घोषणा      FLD_AM_REG_GAIN          0x00000700
#घोषणा      FLD_AGC_REF              0x000000ff

/*****************************************************************************/
#घोषणा      ANALOG_MUX_CTL           0x860
/* Reserved [31:29] */
#घोषणा      FLD_MUX21_SEL            0x10000000
#घोषणा      FLD_MUX20_SEL            0x08000000
#घोषणा      FLD_MUX19_SEL            0x04000000
#घोषणा      FLD_MUX18_SEL            0x02000000
#घोषणा      FLD_MUX17_SEL            0x01000000
#घोषणा      FLD_MUX16_SEL            0x00800000
#घोषणा      FLD_MUX15_SEL            0x00400000
#घोषणा      FLD_MUX14_SEL            0x00300000
#घोषणा      FLD_MUX13_SEL            0x000C0000
#घोषणा      FLD_MUX12_SEL            0x00020000
#घोषणा      FLD_MUX11_SEL            0x00018000
#घोषणा      FLD_MUX10_SEL            0x00004000
#घोषणा      FLD_MUX9_SEL             0x00002000
#घोषणा      FLD_MUX8_SEL             0x00001000
#घोषणा      FLD_MUX7_SEL             0x00000800
#घोषणा      FLD_MUX6_SEL             0x00000600
#घोषणा      FLD_MUX5_SEL             0x00000100
#घोषणा      FLD_MUX4_SEL             0x000000c0
#घोषणा      FLD_MUX3_SEL             0x00000030
#घोषणा      FLD_MUX2_SEL             0x0000000c
#घोषणा      FLD_MUX1_SEL             0x00000003

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      DPLL_CTRL1               0x864
#घोषणा      DIG_PLL_CTL1             0x864

#घोषणा      FLD_PLL_STATUS           0x07000000
#घोषणा      FLD_BANDWIDTH_SELECT     0x00030000
#घोषणा      FLD_PLL_SHIFT_REG        0x00007000
#घोषणा      FLD_PHASE_SHIFT          0x000007ff

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      DPLL_CTRL2               0x868
#घोषणा      DIG_PLL_CTL2             0x868
#घोषणा      FLD_PLL_UNLOCK_THR       0xff000000
#घोषणा      FLD_PLL_LOCK_THR         0x00ff0000
/* Reserved [15:8] */
#घोषणा      FLD_AM_PDF_SEL2          0x000000c0
#घोषणा      FLD_AM_PDF_SEL1          0x00000030
#घोषणा      FLD_DPLL_FSM_CTRL        0x0000000c
/* Reserved [1] */
#घोषणा      FLD_PLL_PILOT_DET        0x00000001

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      DPLL_CTRL3               0x86c
#घोषणा      DIG_PLL_CTL3             0x86c
#घोषणा      FLD_DISABLE_LOOP         0x01000000
#घोषणा      FLD_A1_DS1_SEL           0x000c0000
#घोषणा      FLD_A1_DS2_SEL           0x00030000
#घोषणा      FLD_A1_KI                0x0000ff00
#घोषणा      FLD_A1_KD                0x000000ff

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      DPLL_CTRL4               0x870
#घोषणा      DIG_PLL_CTL4             0x870
#घोषणा      FLD_A2_DS1_SEL           0x000c0000
#घोषणा      FLD_A2_DS2_SEL           0x00030000
#घोषणा      FLD_A2_KI                0x0000ff00
#घोषणा      FLD_A2_KD                0x000000ff

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      DPLL_CTRL5               0x874
#घोषणा      DIG_PLL_CTL5             0x874
#घोषणा      FLD_TRK_DS1_SEL          0x000c0000
#घोषणा      FLD_TRK_DS2_SEL          0x00030000
#घोषणा      FLD_TRK_KI               0x0000ff00
#घोषणा      FLD_TRK_KD               0x000000ff

/*****************************************************************************/
#घोषणा      DEEMPH_GAIN_CTL          0x878
#घोषणा      FLD_DEEMPH2_GAIN         0xFFFF0000
#घोषणा      FLD_DEEMPH1_GAIN         0x0000FFFF

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      DEEMPH_COEFF1            0x87c
#घोषणा      DEEMPH_COEF1             0x87c
#घोषणा      FLD_DEEMPH_B0            0xffff0000
#घोषणा      FLD_DEEMPH_A0            0x0000ffff

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      DEEMPH_COEFF2            0x880
#घोषणा      DEEMPH_COEF2             0x880
#घोषणा      FLD_DEEMPH_B1            0xFFFF0000
#घोषणा      FLD_DEEMPH_A1            0x0000FFFF

/*****************************************************************************/
#घोषणा      DBX1_CTL1                0x884
#घोषणा      FLD_DBX1_WBE_GAIN        0xffff0000
#घोषणा      FLD_DBX1_IN_GAIN         0x0000ffff

/*****************************************************************************/
#घोषणा      DBX1_CTL2                0x888
#घोषणा      FLD_DBX1_SE_BYPASS       0xffff0000
#घोषणा      FLD_DBX1_SE_GAIN         0x0000ffff

/*****************************************************************************/
#घोषणा      DBX1_RMS_SE              0x88C
#घोषणा      FLD_DBX1_RMS_WBE         0xffff0000
#घोषणा      FLD_DBX1_RMS_SE_FLD      0x0000ffff

/*****************************************************************************/
#घोषणा      DBX2_CTL1                0x890
#घोषणा      FLD_DBX2_WBE_GAIN        0xffff0000
#घोषणा      FLD_DBX2_IN_GAIN         0x0000ffff

/*****************************************************************************/
#घोषणा      DBX2_CTL2                0x894
#घोषणा      FLD_DBX2_SE_BYPASS       0xffff0000
#घोषणा      FLD_DBX2_SE_GAIN         0x0000ffff

/*****************************************************************************/
#घोषणा      DBX2_RMS_SE              0x898
#घोषणा      FLD_DBX2_RMS_WBE         0xffff0000
#घोषणा      FLD_DBX2_RMS_SE_FLD      0x0000ffff

/*****************************************************************************/
#घोषणा      AM_FM_DIFF               0x89c
/* Reserved [31] */
#घोषणा      FLD_FM_DIFF_OUT          0x7fff0000
/* Reserved [15] */
#घोषणा      FLD_AM_DIFF_OUT          0x00007fff

/*****************************************************************************/
#घोषणा      NICAM_FAW                0x8a0
#घोषणा      FLD_FAWDETWINEND         0xFc000000
#घोषणा      FLD_FAWDETWINSTR         0x03ff0000
/* Reserved [15:12] */
#घोषणा      FLD_FAWDETTHRSHLD3       0x00000f00
#घोषणा      FLD_FAWDETTHRSHLD2       0x000000f0
#घोषणा      FLD_FAWDETTHRSHLD1       0x0000000f

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      DEEMPH_GAIN              0x8a4
#घोषणा      NICAM_DEEMPHGAIN         0x8a4
/* Reserved [31:18] */
#घोषणा      FLD_DEEMPHGAIN           0x0003ffff

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      DEEMPH_NUMER1            0x8a8
#घोषणा      NICAM_DEEMPHNUMER1       0x8a8
/* Reserved [31:18] */
#घोषणा      FLD_DEEMPHNUMER1         0x0003ffff

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      DEEMPH_NUMER2            0x8ac
#घोषणा      NICAM_DEEMPHNUMER2       0x8ac
/* Reserved [31:18] */
#घोषणा      FLD_DEEMPHNUMER2         0x0003ffff

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      DEEMPH_DENOM1            0x8b0
#घोषणा      NICAM_DEEMPHDENOM1       0x8b0
/* Reserved [31:18] */
#घोषणा      FLD_DEEMPHDENOM1         0x0003ffff

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      DEEMPH_DENOM2            0x8b4
#घोषणा      NICAM_DEEMPHDENOM2       0x8b4
/* Reserved [31:18] */
#घोषणा      FLD_DEEMPHDENOM2         0x0003ffff

/*****************************************************************************/
#घोषणा      NICAM_ERRLOG_CTL1        0x8B8
/* Reserved [31:28] */
#घोषणा      FLD_ERRINTRPTTHSHLD1     0x0fff0000
/* Reserved [15:12] */
#घोषणा      FLD_ERRLOGPERIOD         0x00000fff

/*****************************************************************************/
#घोषणा      NICAM_ERRLOG_CTL2        0x8bc
/* Reserved [31:28] */
#घोषणा      FLD_ERRINTRPTTHSHLD3     0x0fff0000
/* Reserved [15:12] */
#घोषणा      FLD_ERRINTRPTTHSHLD2     0x00000fff

/*****************************************************************************/
#घोषणा      NICAM_ERRLOG_STS1        0x8c0
/* Reserved [31:28] */
#घोषणा      FLD_ERRLOG2              0x0fff0000
/* Reserved [15:12] */
#घोषणा      FLD_ERRLOG1              0x00000fff

/*****************************************************************************/
#घोषणा      NICAM_ERRLOG_STS2        0x8c4
/* Reserved [31:12] */
#घोषणा      FLD_ERRLOG3              0x00000fff

/*****************************************************************************/
#घोषणा      NICAM_STATUS             0x8c8
/* Reserved [31:20] */
#घोषणा      FLD_NICAM_CIB            0x000c0000
#घोषणा      FLD_NICAM_LOCK_STAT      0x00020000
#घोषणा      FLD_NICAM_MUTE           0x00010000
#घोषणा      FLD_NICAMADDIT_DATA      0x0000ffe0
#घोषणा      FLD_NICAMCNTRL           0x0000001f

/*****************************************************************************/
#घोषणा      DEMATRIX_CTL             0x8cc
#घोषणा      FLD_AC97_IN_SHIFT        0xf0000000
#घोषणा      FLD_I2S_IN_SHIFT         0x0f000000
#घोषणा      FLD_DEMATRIX_SEL_CTL     0x00ff0000
/* Reserved [15:11] */
#घोषणा      FLD_DMTRX_BYPASS         0x00000400
#घोषणा      FLD_DEMATRIX_MODE        0x00000300
/* Reserved [7:6] */
#घोषणा      FLD_PH_DBX_SEL           0x00000020
#घोषणा      FLD_PH_CH_SEL            0x00000010
#घोषणा      FLD_PHASE_FIX            0x0000000f

/*****************************************************************************/
#घोषणा      PATH1_CTL1               0x8d0
/* Reserved [31:29] */
#घोषणा      FLD_PATH1_MUTE_CTL       0x1f000000
/* Reserved [23:22] */
#घोषणा      FLD_PATH1_AVC_CG         0x00300000
#घोषणा      FLD_PATH1_AVC_RT         0x000f0000
#घोषणा      FLD_PATH1_AVC_AT         0x0000f000
#घोषणा      FLD_PATH1_AVC_STEREO     0x00000800
#घोषणा      FLD_PATH1_AVC_CR         0x00000700
#घोषणा      FLD_PATH1_AVC_RMS_CON    0x000000f0
#घोषणा      FLD_PATH1_SEL_CTL        0x0000000f

/*****************************************************************************/
#घोषणा      PATH1_VOL_CTL            0x8d4
#घोषणा      FLD_PATH1_AVC_THRESHOLD  0x7fff0000
#घोषणा      FLD_PATH1_BAL_LEFT       0x00008000
#घोषणा      FLD_PATH1_BAL_LEVEL      0x00007f00
#घोषणा      FLD_PATH1_VOLUME         0x000000ff

/*****************************************************************************/
#घोषणा      PATH1_EQ_CTL             0x8d8
/* Reserved [31:30] */
#घोषणा      FLD_PATH1_EQ_TREBLE_VOL  0x3f000000
/* Reserved [23:22] */
#घोषणा      FLD_PATH1_EQ_MID_VOL     0x003f0000
/* Reserved [15:14] */
#घोषणा      FLD_PATH1_EQ_BASS_VOL    0x00003f00
/* Reserved [7:1] */
#घोषणा      FLD_PATH1_EQ_BAND_SEL    0x00000001

/*****************************************************************************/
#घोषणा      PATH1_SC_CTL             0x8dc
#घोषणा      FLD_PATH1_SC_THRESHOLD   0x7fff0000
#घोषणा      FLD_PATH1_SC_RT          0x0000f000
#घोषणा      FLD_PATH1_SC_AT          0x00000f00
#घोषणा      FLD_PATH1_SC_STEREO      0x00000080
#घोषणा      FLD_PATH1_SC_CR          0x00000070
#घोषणा      FLD_PATH1_SC_RMS_CON     0x0000000f

/*****************************************************************************/
#घोषणा      PATH2_CTL1               0x8e0
/* Reserved [31:26] */
#घोषणा      FLD_PATH2_MUTE_CTL       0x03000000
/* Reserved [23:22] */
#घोषणा      FLD_PATH2_AVC_CG         0x00300000
#घोषणा      FLD_PATH2_AVC_RT         0x000f0000
#घोषणा      FLD_PATH2_AVC_AT         0x0000f000
#घोषणा      FLD_PATH2_AVC_STEREO     0x00000800
#घोषणा      FLD_PATH2_AVC_CR         0x00000700
#घोषणा      FLD_PATH2_AVC_RMS_CON    0x000000f0
#घोषणा      FLD_PATH2_SEL_CTL        0x0000000f

/*****************************************************************************/
#घोषणा      PATH2_VOL_CTL            0x8e4
#घोषणा      FLD_PATH2_AVC_THRESHOLD  0xffff0000
#घोषणा      FLD_PATH2_BAL_LEFT       0x00008000
#घोषणा      FLD_PATH2_BAL_LEVEL      0x00007f00
#घोषणा      FLD_PATH2_VOLUME         0x000000ff

/*****************************************************************************/
#घोषणा      PATH2_EQ_CTL             0x8e8
/* Reserved [31:30] */
#घोषणा      FLD_PATH2_EQ_TREBLE_VOL  0x3f000000
/* Reserved [23:22] */
#घोषणा      FLD_PATH2_EQ_MID_VOL     0x003f0000
/* Reserved [15:14] */
#घोषणा      FLD_PATH2_EQ_BASS_VOL    0x00003f00
/* Reserved [7:1] */
#घोषणा      FLD_PATH2_EQ_BAND_SEL    0x00000001

/*****************************************************************************/
#घोषणा      PATH2_SC_CTL             0x8eC
#घोषणा      FLD_PATH2_SC_THRESHOLD   0xffff0000
#घोषणा      FLD_PATH2_SC_RT          0x0000f000
#घोषणा      FLD_PATH2_SC_AT          0x00000f00
#घोषणा      FLD_PATH2_SC_STEREO      0x00000080
#घोषणा      FLD_PATH2_SC_CR          0x00000070
#घोषणा      FLD_PATH2_SC_RMS_CON     0x0000000f

/*****************************************************************************/
#घोषणा      SRC_CTL                  0x8f0
#घोषणा      FLD_SRC_STATUS           0xffffff00
#घोषणा      FLD_FIFO_LF_EN           0x000000fc
#घोषणा      FLD_BYPASS_LI            0x00000002
#घोषणा      FLD_BYPASS_PF            0x00000001

/*****************************************************************************/
#घोषणा      SRC_LF_COEF              0x8f4
#घोषणा      FLD_LOOP_FILTER_COEF2    0xffff0000
#घोषणा      FLD_LOOP_FILTER_COEF1    0x0000ffff

/*****************************************************************************/
#घोषणा      SRC1_CTL                 0x8f8
/* Reserved [31:28] */
#घोषणा      FLD_SRC1_FIFO_RD_TH      0x0f000000
/* Reserved [23:18] */
#घोषणा      FLD_SRC1_PHASE_INC       0x0003ffff

/*****************************************************************************/
#घोषणा      SRC2_CTL                 0x8fc
/* Reserved [31:28] */
#घोषणा      FLD_SRC2_FIFO_RD_TH      0x0f000000
/* Reserved [23:18] */
#घोषणा      FLD_SRC2_PHASE_INC       0x0003ffff

/*****************************************************************************/
#घोषणा      SRC3_CTL                 0x900
/* Reserved [31:28] */
#घोषणा      FLD_SRC3_FIFO_RD_TH      0x0f000000
/* Reserved [23:18] */
#घोषणा      FLD_SRC3_PHASE_INC       0x0003ffff

/*****************************************************************************/
#घोषणा      SRC4_CTL                 0x904
/* Reserved [31:28] */
#घोषणा      FLD_SRC4_FIFO_RD_TH      0x0f000000
/* Reserved [23:18] */
#घोषणा      FLD_SRC4_PHASE_INC       0x0003ffff

/*****************************************************************************/
#घोषणा      SRC5_CTL                 0x908
/* Reserved [31:28] */
#घोषणा      FLD_SRC5_FIFO_RD_TH      0x0f000000
/* Reserved [23:18] */
#घोषणा      FLD_SRC5_PHASE_INC       0x0003ffff

/*****************************************************************************/
#घोषणा      SRC6_CTL                 0x90c
/* Reserved [31:28] */
#घोषणा      FLD_SRC6_FIFO_RD_TH      0x0f000000
/* Reserved [23:18] */
#घोषणा      FLD_SRC6_PHASE_INC       0x0003ffff

/*****************************************************************************/
#घोषणा      BAND_OUT_SEL             0x910
#घोषणा      FLD_SRC6_IN_SEL          0xc0000000
#घोषणा      FLD_SRC6_CLK_SEL         0x30000000
#घोषणा      FLD_SRC5_IN_SEL          0x0c000000
#घोषणा      FLD_SRC5_CLK_SEL         0x03000000
#घोषणा      FLD_SRC4_IN_SEL          0x00c00000
#घोषणा      FLD_SRC4_CLK_SEL         0x00300000
#घोषणा      FLD_SRC3_IN_SEL          0x000c0000
#घोषणा      FLD_SRC3_CLK_SEL         0x00030000
#घोषणा      FLD_BASEBAND_BYPASS_CTL  0x0000ff00
#घोषणा      FLD_AC97_SRC_SEL         0x000000c0
#घोषणा      FLD_I2S_SRC_SEL          0x00000030
#घोषणा      FLD_PARALLEL2_SRC_SEL    0x0000000c
#घोषणा      FLD_PARALLEL1_SRC_SEL    0x00000003

/*****************************************************************************/
#घोषणा      I2S_IN_CTL               0x914
/* Reserved [31:11] */
#घोषणा      FLD_I2S_UP2X_BW20K       0x00000400
#घोषणा      FLD_I2S_UP2X_BYPASS      0x00000200
#घोषणा      FLD_I2S_IN_MASTER_MODE   0x00000100
#घोषणा      FLD_I2S_IN_SONY_MODE     0x00000080
#घोषणा      FLD_I2S_IN_RIGHT_JUST    0x00000040
#घोषणा      FLD_I2S_IN_WS_SEL        0x00000020
#घोषणा      FLD_I2S_IN_BCN_DEL       0x0000001f

/*****************************************************************************/
#घोषणा      I2S_OUT_CTL              0x918
/* Reserved [31:17] */
#घोषणा      FLD_I2S_OUT_SOFT_RESET_EN  0x00010000
/* Reserved [15:9] */
#घोषणा      FLD_I2S_OUT_MASTER_MODE  0x00000100
#घोषणा      FLD_I2S_OUT_SONY_MODE    0x00000080
#घोषणा      FLD_I2S_OUT_RIGHT_JUST   0x00000040
#घोषणा      FLD_I2S_OUT_WS_SEL       0x00000020
#घोषणा      FLD_I2S_OUT_BCN_DEL      0x0000001f

/*****************************************************************************/
#घोषणा      AC97_CTL                 0x91c
/* Reserved [31:26] */
#घोषणा      FLD_AC97_UP2X_BW20K      0x02000000
#घोषणा      FLD_AC97_UP2X_BYPASS     0x01000000
/* Reserved [23:17] */
#घोषणा      FLD_AC97_RST_ACL         0x00010000
/* Reserved [15:9] */
#घोषणा      FLD_AC97_WAKE_UP_SYNC    0x00000100
/* Reserved [7:1] */
#घोषणा      FLD_AC97_SHUTDOWN        0x00000001

/* Cx231xx redefine */
#घोषणा      QPSK_IAGC_CTL1		0x94c
#घोषणा      QPSK_IAGC_CTL2		0x950
#घोषणा      QPSK_FEPR_FREQ		0x954
#घोषणा      QPSK_BTL_CTL1		0x958
#घोषणा      QPSK_BTL_CTL2		0x95c
#घोषणा      QPSK_CTL_CTL1		0x960
#घोषणा      QPSK_CTL_CTL2		0x964
#घोषणा      QPSK_MF_FAGC_CTL		0x968
#घोषणा      QPSK_EQ_CTL		0x96c
#घोषणा      QPSK_LOCK_CTL		0x970

/*****************************************************************************/
#घोषणा      FM1_DFT_CTL              0x9a8
#घोषणा      FLD_FM1_DFT_THRESHOLD    0xffff0000
/* Reserved [15:8] */
#घोषणा      FLD_FM1_DFT_CMP_CTL      0x00000080
#घोषणा      FLD_FM1_DFT_AVG          0x00000070
/* Reserved [3:1] */
#घोषणा      FLD_FM1_DFT_START        0x00000001

/*****************************************************************************/
#घोषणा      FM1_DFT_STATUS           0x9ac
#घोषणा      FLD_FM1_DFT_DONE         0x80000000
/* Reserved [30:19] */
#घोषणा      FLD_FM_DFT_TH_CMP        0x00040000
#घोषणा      FLD_FM1_DFT              0x0003ffff

/*****************************************************************************/
#घोषणा      FM2_DFT_CTL              0x9b0
#घोषणा      FLD_FM2_DFT_THRESHOLD    0xffff0000
/* Reserved [15:8] */
#घोषणा      FLD_FM2_DFT_CMP_CTL      0x00000080
#घोषणा      FLD_FM2_DFT_AVG          0x00000070
/* Reserved [3:1] */
#घोषणा      FLD_FM2_DFT_START        0x00000001

/*****************************************************************************/
#घोषणा      FM2_DFT_STATUS           0x9b4
#घोषणा      FLD_FM2_DFT_DONE         0x80000000
/* Reserved [30:19] */
#घोषणा      FLD_FM2_DFT_TH_CMP_STAT  0x00040000
#घोषणा      FLD_FM2_DFT              0x0003ffff

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      AAGC_STATUS_REG          0x9b8
#घोषणा      AAGC_STATUS              0x9b8
/* Reserved [31:27] */
#घोषणा      FLD_FM2_DAGC_OUT         0x07000000
/* Reserved [23:19] */
#घोषणा      FLD_FM1_DAGC_OUT         0x00070000
/* Reserved [15:6] */
#घोषणा      FLD_AFE_VGA_OUT          0x0000003f

/*****************************************************************************/
#घोषणा      MTS_GAIN_STATUS          0x9bc
/* Reserved [31:14] */
#घोषणा      FLD_MTS_GAIN             0x00003fff

#घोषणा      RDS_OUT                  0x9c0
#घोषणा      FLD_RDS_Q                0xffff0000
#घोषणा      FLD_RDS_I                0x0000ffff

/*****************************************************************************/
#घोषणा      AUTOCONFIG_REG           0x9c4
/* Reserved [31:4] */
#घोषणा      FLD_AUTOCONFIG_MODE      0x0000000f

#घोषणा      FM_AFC                   0x9c8
#घोषणा      FLD_FM2_AFC              0xffff0000
#घोषणा      FLD_FM1_AFC              0x0000ffff

/*****************************************************************************/
/* Cx231xx redefine */
#घोषणा      NEW_SPARE                0x9cc
#घोषणा      NEW_SPARE_REG            0x9cc

/*****************************************************************************/
#घोषणा      DBX_ADJ                  0x9d0
/* Reserved [31:28] */
#घोषणा      FLD_DBX2_ADJ             0x0fff0000
/* Reserved [15:12] */
#घोषणा      FLD_DBX1_ADJ             0x00000fff

#घोषणा      VID_FMT_AUTO              0
#घोषणा      VID_FMT_NTSC_M            1
#घोषणा      VID_FMT_NTSC_J            2
#घोषणा      VID_FMT_NTSC_443          3
#घोषणा      VID_FMT_PAL_BDGHI         4
#घोषणा      VID_FMT_PAL_M             5
#घोषणा      VID_FMT_PAL_N             6
#घोषणा      VID_FMT_PAL_NC            7
#घोषणा      VID_FMT_PAL_60            8
#घोषणा      VID_FMT_SECAM             12
#घोषणा      VID_FMT_SECAM_60          13

#घोषणा      INPUT_MODE_CVBS_0         0       /* INPUT_MODE_VALUE(0) */
#घोषणा      INPUT_MODE_YC_1           1       /* INPUT_MODE_VALUE(1) */
#घोषणा      INPUT_MODE_YC2_2          2       /* INPUT_MODE_VALUE(2) */
#घोषणा      INPUT_MODE_YUV_3          3       /* INPUT_MODE_VALUE(3) */

#घोषणा      LUMA_LPF_LOW_BANDPASS     0       /* 0.6Mhz LPF BW */
#घोषणा      LUMA_LPF_MEDIUM_BANDPASS  1       /* 1.0Mhz LPF BW */
#घोषणा      LUMA_LPF_HIGH_BANDPASS    2       /* 1.5Mhz LPF BW */

#घोषणा      UV_LPF_LOW_BANDPASS       0       /* 0.6Mhz LPF BW */
#घोषणा      UV_LPF_MEDIUM_BANDPASS    1       /* 1.0Mhz LPF BW */
#घोषणा      UV_LPF_HIGH_BANDPASS      2       /* 1.5Mhz LPF BW */

#घोषणा      TWO_TAP_FILT              0
#घोषणा      THREE_TAP_FILT            1
#घोषणा      FOUR_TAP_FILT             2
#घोषणा      FIVE_TAP_FILT             3

#घोषणा      AUD_CHAN_SRC_PARALLEL     0
#घोषणा      AUD_CHAN_SRC_I2S_INPUT    1
#घोषणा      AUD_CHAN_SRC_FLATIRON     2
#घोषणा      AUD_CHAN_SRC_PARALLEL3    3

#घोषणा      OUT_MODE_601              0
#घोषणा      OUT_MODE_656              1
#घोषणा      OUT_MODE_VIP11            2
#घोषणा      OUT_MODE_VIP20            3

#घोषणा      PHASE_INC_49MHZ          0x0df22
#घोषणा      PHASE_INC_56MHZ          0x0fa5b
#घोषणा      PHASE_INC_28MHZ          0x010000

#पूर्ण_अगर
