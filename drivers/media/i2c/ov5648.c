<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 Bootlin
 * Author: Paul Kocialkowski <paul.kocialkowski@bootlin.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-image-sizes.h>
#समावेश <media/v4l2-mediabus.h>

/* Clock rate */

#घोषणा OV5648_XVCLK_RATE			24000000

/* Register definitions */

/* System */

#घोषणा OV5648_SW_STANDBY_REG			0x100
#घोषणा OV5648_SW_STANDBY_STREAM_ON		BIT(0)

#घोषणा OV5648_SW_RESET_REG			0x103
#घोषणा OV5648_SW_RESET_RESET			BIT(0)

#घोषणा OV5648_PAD_OEN0_REG			0x3000
#घोषणा OV5648_PAD_OEN1_REG			0x3001
#घोषणा OV5648_PAD_OEN2_REG			0x3002
#घोषणा OV5648_PAD_OUT0_REG			0x3008
#घोषणा OV5648_PAD_OUT1_REG			0x3009

#घोषणा OV5648_CHIP_ID_H_REG			0x300a
#घोषणा OV5648_CHIP_ID_H_VALUE			0x56
#घोषणा OV5648_CHIP_ID_L_REG			0x300b
#घोषणा OV5648_CHIP_ID_L_VALUE			0x48

#घोषणा OV5648_PAD_OUT2_REG			0x300d
#घोषणा OV5648_PAD_SEL0_REG			0x300e
#घोषणा OV5648_PAD_SEL1_REG			0x300f
#घोषणा OV5648_PAD_SEL2_REG			0x3010
#घोषणा OV5648_PAD_PK_REG			0x3011
#घोषणा OV5648_PAD_PK_PD_DATO_EN		BIT(7)
#घोषणा OV5648_PAD_PK_DRIVE_STRENGTH_1X		(0 << 5)
#घोषणा OV5648_PAD_PK_DRIVE_STRENGTH_2X		(2 << 5)
#घोषणा OV5648_PAD_PK_FREX_N			BIT(1)

#घोषणा OV5648_A_PWC_PK_O0_REG			0x3013
#घोषणा OV5648_A_PWC_PK_O0_BP_REGULATOR_N	BIT(3)
#घोषणा OV5648_A_PWC_PK_O1_REG			0x3014

#घोषणा OV5648_MIPI_PHY0_REG			0x3016
#घोषणा OV5648_MIPI_PHY1_REG			0x3017
#घोषणा OV5648_MIPI_SC_CTRL0_REG		0x3018
#घोषणा OV5648_MIPI_SC_CTRL0_MIPI_LANES(v)	(((v) << 5) & GENMASK(7, 5))
#घोषणा OV5648_MIPI_SC_CTRL0_PHY_HS_TX_PD	BIT(4)
#घोषणा OV5648_MIPI_SC_CTRL0_PHY_LP_RX_PD	BIT(3)
#घोषणा OV5648_MIPI_SC_CTRL0_MIPI_EN		BIT(2)
#घोषणा OV5648_MIPI_SC_CTRL0_MIPI_SUSP		BIT(1)
#घोषणा OV5648_MIPI_SC_CTRL0_LANE_DIS_OP	BIT(0)
#घोषणा OV5648_MIPI_SC_CTRL1_REG		0x3019
#घोषणा OV5648_MISC_CTRL0_REG			0x3021
#घोषणा OV5648_MIPI_SC_CTRL2_REG		0x3022
#घोषणा OV5648_SUB_ID_REG			0x302a

#घोषणा OV5648_PLL_CTRL0_REG			0x3034
#घोषणा OV5648_PLL_CTRL0_PLL_CHARGE_PUMP(v)	(((v) << 4) & GENMASK(6, 4))
#घोषणा OV5648_PLL_CTRL0_BITS(v)		((v) & GENMASK(3, 0))
#घोषणा OV5648_PLL_CTRL1_REG			0x3035
#घोषणा OV5648_PLL_CTRL1_SYS_DIV(v)		(((v) << 4) & GENMASK(7, 4))
#घोषणा OV5648_PLL_CTRL1_MIPI_DIV(v)		((v) & GENMASK(3, 0))
#घोषणा OV5648_PLL_MUL_REG			0x3036
#घोषणा OV5648_PLL_MUL(v)			((v) & GENMASK(7, 0))
#घोषणा OV5648_PLL_DIV_REG			0x3037
#घोषणा OV5648_PLL_DIV_ROOT_DIV(v)		((((v) - 1) << 4) & BIT(4))
#घोषणा OV5648_PLL_DIV_PLL_PRE_DIV(v)		((v) & GENMASK(3, 0))
#घोषणा OV5648_PLL_DEBUG_REG			0x3038
#घोषणा OV5648_PLL_BYPASS_REG			0x3039

#घोषणा OV5648_PLLS_BYPASS_REG			0x303a
#घोषणा OV5648_PLLS_MUL_REG			0x303b
#घोषणा OV5648_PLLS_MUL(v)			((v) & GENMASK(4, 0))
#घोषणा OV5648_PLLS_CTRL_REG			0x303c
#घोषणा OV5648_PLLS_CTRL_PLL_CHARGE_PUMP(v)	(((v) << 4) & GENMASK(6, 4))
#घोषणा OV5648_PLLS_CTRL_SYS_DIV(v)		((v) & GENMASK(3, 0))
#घोषणा OV5648_PLLS_DIV_REG			0x303d
#घोषणा OV5648_PLLS_DIV_PLLS_PRE_DIV(v)		(((v) << 4) & GENMASK(5, 4))
#घोषणा OV5648_PLLS_DIV_PLLS_DIV_R(v)		((((v) - 1) << 2) & BIT(2))
#घोषणा OV5648_PLLS_DIV_PLLS_SEL_DIV(v)		((v) & GENMASK(1, 0))

#घोषणा OV5648_SRB_CTRL_REG			0x3106
#घोषणा OV5648_SRB_CTRL_SCLK_DIV(v)		(((v) << 2) & GENMASK(3, 2))
#घोषणा OV5648_SRB_CTRL_RESET_ARBITER_EN	BIT(1)
#घोषणा OV5648_SRB_CTRL_SCLK_ARBITER_EN		BIT(0)

/* Group Hold */

#घोषणा OV5648_GROUP_ADR0_REG			0x3200
#घोषणा OV5648_GROUP_ADR1_REG			0x3201
#घोषणा OV5648_GROUP_ADR2_REG			0x3202
#घोषणा OV5648_GROUP_ADR3_REG			0x3203
#घोषणा OV5648_GROUP_LEN0_REG			0x3204
#घोषणा OV5648_GROUP_LEN1_REG			0x3205
#घोषणा OV5648_GROUP_LEN2_REG			0x3206
#घोषणा OV5648_GROUP_LEN3_REG			0x3207
#घोषणा OV5648_GROUP_ACCESS_REG			0x3208

/* Exposure/gain/banding */

#घोषणा OV5648_EXPOSURE_CTRL_HH_REG		0x3500
#घोषणा OV5648_EXPOSURE_CTRL_HH(v)		(((v) & GENMASK(19, 16)) >> 16)
#घोषणा OV5648_EXPOSURE_CTRL_HH_VALUE(v)	(((v) << 16) & GENMASK(19, 16))
#घोषणा OV5648_EXPOSURE_CTRL_H_REG		0x3501
#घोषणा OV5648_EXPOSURE_CTRL_H(v)		(((v) & GENMASK(15, 8)) >> 8)
#घोषणा OV5648_EXPOSURE_CTRL_H_VALUE(v)		(((v) << 8) & GENMASK(15, 8))
#घोषणा OV5648_EXPOSURE_CTRL_L_REG		0x3502
#घोषणा OV5648_EXPOSURE_CTRL_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV5648_EXPOSURE_CTRL_L_VALUE(v)		((v) & GENMASK(7, 0))
#घोषणा OV5648_MANUAL_CTRL_REG			0x3503
#घोषणा OV5648_MANUAL_CTRL_FRAME_DELAY(v)	(((v) << 4) & GENMASK(5, 4))
#घोषणा OV5648_MANUAL_CTRL_AGC_MANUAL_EN	BIT(1)
#घोषणा OV5648_MANUAL_CTRL_AEC_MANUAL_EN	BIT(0)
#घोषणा OV5648_GAIN_CTRL_H_REG			0x350a
#घोषणा OV5648_GAIN_CTRL_H(v)			(((v) & GENMASK(9, 8)) >> 8)
#घोषणा OV5648_GAIN_CTRL_H_VALUE(v)		(((v) << 8) & GENMASK(9, 8))
#घोषणा OV5648_GAIN_CTRL_L_REG			0x350b
#घोषणा OV5648_GAIN_CTRL_L(v)			((v) & GENMASK(7, 0))
#घोषणा OV5648_GAIN_CTRL_L_VALUE(v)		((v) & GENMASK(7, 0))

#घोषणा OV5648_ANALOG_CTRL0_REG_BASE		0x3600
#घोषणा OV5648_ANALOG_CTRL1_REG_BASE		0x3700

#घोषणा OV5648_AEC_CTRL0_REG			0x3a00
#घोषणा OV5648_AEC_CTRL0_DEBUG			BIT(6)
#घोषणा OV5648_AEC_CTRL0_DEBAND_EN		BIT(5)
#घोषणा OV5648_AEC_CTRL0_DEBAND_LOW_LIMIT_EN	BIT(4)
#घोषणा OV5648_AEC_CTRL0_START_SEL_EN		BIT(3)
#घोषणा OV5648_AEC_CTRL0_NIGHT_MODE_EN		BIT(2)
#घोषणा OV5648_AEC_CTRL0_FREEZE_EN		BIT(0)
#घोषणा OV5648_EXPOSURE_MIN_REG			0x3a01
#घोषणा OV5648_EXPOSURE_MAX_60_H_REG		0x3a02
#घोषणा OV5648_EXPOSURE_MAX_60_L_REG		0x3a03
#घोषणा OV5648_AEC_CTRL5_REG			0x3a05
#घोषणा OV5648_AEC_CTRL6_REG			0x3a06
#घोषणा OV5648_AEC_CTRL7_REG			0x3a07
#घोषणा OV5648_BANDING_STEP_50_H_REG		0x3a08
#घोषणा OV5648_BANDING_STEP_50_L_REG		0x3a09
#घोषणा OV5648_BANDING_STEP_60_H_REG		0x3a0a
#घोषणा OV5648_BANDING_STEP_60_L_REG		0x3a0b
#घोषणा OV5648_AEC_CTRLC_REG			0x3a0c
#घोषणा OV5648_BANDING_MAX_60_REG		0x3a0d
#घोषणा OV5648_BANDING_MAX_50_REG		0x3a0e
#घोषणा OV5648_WPT_REG				0x3a0f
#घोषणा OV5648_BPT_REG				0x3a10
#घोषणा OV5648_VPT_HIGH_REG			0x3a11
#घोषणा OV5648_AVG_MANUAL_REG			0x3a12
#घोषणा OV5648_PRE_GAIN_REG			0x3a13
#घोषणा OV5648_EXPOSURE_MAX_50_H_REG		0x3a14
#घोषणा OV5648_EXPOSURE_MAX_50_L_REG		0x3a15
#घोषणा OV5648_GAIN_BASE_NIGHT_REG		0x3a17
#घोषणा OV5648_AEC_GAIN_CEILING_H_REG		0x3a18
#घोषणा OV5648_AEC_GAIN_CEILING_L_REG		0x3a19
#घोषणा OV5648_DIFF_MAX_REG			0x3a1a
#घोषणा OV5648_WPT2_REG				0x3a1b
#घोषणा OV5648_LED_ADD_ROW_H_REG		0x3a1c
#घोषणा OV5648_LED_ADD_ROW_L_REG		0x3a1d
#घोषणा OV5648_BPT2_REG				0x3a1e
#घोषणा OV5648_VPT_LOW_REG			0x3a1f
#घोषणा OV5648_AEC_CTRL20_REG			0x3a20
#घोषणा OV5648_AEC_CTRL21_REG			0x3a21

#घोषणा OV5648_AVG_START_X_H_REG		0x5680
#घोषणा OV5648_AVG_START_X_L_REG		0x5681
#घोषणा OV5648_AVG_START_Y_H_REG		0x5682
#घोषणा OV5648_AVG_START_Y_L_REG		0x5683
#घोषणा OV5648_AVG_WINDOW_X_H_REG		0x5684
#घोषणा OV5648_AVG_WINDOW_X_L_REG		0x5685
#घोषणा OV5648_AVG_WINDOW_Y_H_REG		0x5686
#घोषणा OV5648_AVG_WINDOW_Y_L_REG		0x5687
#घोषणा OV5648_AVG_WEIGHT00_REG			0x5688
#घोषणा OV5648_AVG_WEIGHT01_REG			0x5689
#घोषणा OV5648_AVG_WEIGHT02_REG			0x568a
#घोषणा OV5648_AVG_WEIGHT03_REG			0x568b
#घोषणा OV5648_AVG_WEIGHT04_REG			0x568c
#घोषणा OV5648_AVG_WEIGHT05_REG			0x568d
#घोषणा OV5648_AVG_WEIGHT06_REG			0x568e
#घोषणा OV5648_AVG_WEIGHT07_REG			0x568f
#घोषणा OV5648_AVG_CTRL10_REG			0x5690
#घोषणा OV5648_AVG_WEIGHT_SUM_REG		0x5691
#घोषणा OV5648_AVG_READOUT_REG			0x5693

#घोषणा OV5648_DIG_CTRL0_REG			0x5a00
#घोषणा OV5648_DIG_COMP_MAN_H_REG		0x5a02
#घोषणा OV5648_DIG_COMP_MAN_L_REG		0x5a03

#घोषणा OV5648_GAINC_MAN_H_REG			0x5a20
#घोषणा OV5648_GAINC_MAN_L_REG			0x5a21
#घोषणा OV5648_GAINC_DGC_MAN_H_REG		0x5a22
#घोषणा OV5648_GAINC_DGC_MAN_L_REG		0x5a23
#घोषणा OV5648_GAINC_CTRL0_REG			0x5a24

#घोषणा OV5648_GAINF_ANA_NUM_REG		0x5a40
#घोषणा OV5648_GAINF_DIG_GAIN_REG		0x5a41

/* Timing */

#घोषणा OV5648_CROP_START_X_H_REG		0x3800
#घोषणा OV5648_CROP_START_X_H(v)		(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV5648_CROP_START_X_L_REG		0x3801
#घोषणा OV5648_CROP_START_X_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV5648_CROP_START_Y_H_REG		0x3802
#घोषणा OV5648_CROP_START_Y_H(v)		(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV5648_CROP_START_Y_L_REG		0x3803
#घोषणा OV5648_CROP_START_Y_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV5648_CROP_END_X_H_REG			0x3804
#घोषणा OV5648_CROP_END_X_H(v)			(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV5648_CROP_END_X_L_REG			0x3805
#घोषणा OV5648_CROP_END_X_L(v)			((v) & GENMASK(7, 0))
#घोषणा OV5648_CROP_END_Y_H_REG			0x3806
#घोषणा OV5648_CROP_END_Y_H(v)			(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV5648_CROP_END_Y_L_REG			0x3807
#घोषणा OV5648_CROP_END_Y_L(v)			((v) & GENMASK(7, 0))
#घोषणा OV5648_OUTPUT_SIZE_X_H_REG		0x3808
#घोषणा OV5648_OUTPUT_SIZE_X_H(v)		(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV5648_OUTPUT_SIZE_X_L_REG		0x3809
#घोषणा OV5648_OUTPUT_SIZE_X_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV5648_OUTPUT_SIZE_Y_H_REG		0x380a
#घोषणा OV5648_OUTPUT_SIZE_Y_H(v)		(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV5648_OUTPUT_SIZE_Y_L_REG		0x380b
#घोषणा OV5648_OUTPUT_SIZE_Y_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV5648_HTS_H_REG			0x380c
#घोषणा OV5648_HTS_H(v)				(((v) & GENMASK(12, 8)) >> 8)
#घोषणा OV5648_HTS_L_REG			0x380d
#घोषणा OV5648_HTS_L(v)				((v) & GENMASK(7, 0))
#घोषणा OV5648_VTS_H_REG			0x380e
#घोषणा OV5648_VTS_H(v)				(((v) & GENMASK(15, 8)) >> 8)
#घोषणा OV5648_VTS_L_REG			0x380f
#घोषणा OV5648_VTS_L(v)				((v) & GENMASK(7, 0))
#घोषणा OV5648_OFFSET_X_H_REG			0x3810
#घोषणा OV5648_OFFSET_X_H(v)			(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV5648_OFFSET_X_L_REG			0x3811
#घोषणा OV5648_OFFSET_X_L(v)			((v) & GENMASK(7, 0))
#घोषणा OV5648_OFFSET_Y_H_REG			0x3812
#घोषणा OV5648_OFFSET_Y_H(v)			(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV5648_OFFSET_Y_L_REG			0x3813
#घोषणा OV5648_OFFSET_Y_L(v)			((v) & GENMASK(7, 0))
#घोषणा OV5648_SUB_INC_X_REG			0x3814
#घोषणा OV5648_SUB_INC_X_ODD(v)			(((v) << 4) & GENMASK(7, 4))
#घोषणा OV5648_SUB_INC_X_EVEN(v)		((v) & GENMASK(3, 0))
#घोषणा OV5648_SUB_INC_Y_REG			0x3815
#घोषणा OV5648_SUB_INC_Y_ODD(v)			(((v) << 4) & GENMASK(7, 4))
#घोषणा OV5648_SUB_INC_Y_EVEN(v)		((v) & GENMASK(3, 0))
#घोषणा OV5648_HSYNCST_H_REG			0x3816
#घोषणा OV5648_HSYNCST_H(v)			(((v) >> 8) & 0xf)
#घोषणा OV5648_HSYNCST_L_REG			0x3817
#घोषणा OV5648_HSYNCST_L(v)			((v) & GENMASK(7, 0))
#घोषणा OV5648_HSYNCW_H_REG			0x3818
#घोषणा OV5648_HSYNCW_H(v)			(((v) >> 8) & 0xf)
#घोषणा OV5648_HSYNCW_L_REG			0x3819
#घोषणा OV5648_HSYNCW_L(v)			((v) & GENMASK(7, 0))

#घोषणा OV5648_TC20_REG				0x3820
#घोषणा OV5648_TC20_DEBUG			BIT(6)
#घोषणा OV5648_TC20_FLIP_VERT_ISP_EN		BIT(2)
#घोषणा OV5648_TC20_FLIP_VERT_SENSOR_EN		BIT(1)
#घोषणा OV5648_TC20_BINNING_VERT_EN		BIT(0)
#घोषणा OV5648_TC21_REG				0x3821
#घोषणा OV5648_TC21_FLIP_HORZ_ISP_EN		BIT(2)
#घोषणा OV5648_TC21_FLIP_HORZ_SENSOR_EN		BIT(1)
#घोषणा OV5648_TC21_BINNING_HORZ_EN		BIT(0)

/* Strobe/exposure */

#घोषणा OV5648_STROBE_REG			0x3b00
#घोषणा OV5648_FREX_EXP_HH_REG			0x3b01
#घोषणा OV5648_SHUTTER_DLY_H_REG		0x3b02
#घोषणा OV5648_SHUTTER_DLY_L_REG		0x3b03
#घोषणा OV5648_FREX_EXP_H_REG			0x3b04
#घोषणा OV5648_FREX_EXP_L_REG			0x3b05
#घोषणा OV5648_FREX_CTRL_REG			0x3b06
#घोषणा OV5648_FREX_MODE_SEL_REG		0x3b07
#घोषणा OV5648_FREX_MODE_SEL_FREX_SA1		BIT(4)
#घोषणा OV5648_FREX_MODE_SEL_FX1_FM_EN		BIT(3)
#घोषणा OV5648_FREX_MODE_SEL_FREX_INV		BIT(2)
#घोषणा OV5648_FREX_MODE_SEL_MODE1		0x0
#घोषणा OV5648_FREX_MODE_SEL_MODE2		0x1
#घोषणा OV5648_FREX_MODE_SEL_ROLLING		0x2
#घोषणा OV5648_FREX_EXP_REQ_REG			0x3b08
#घोषणा OV5648_FREX_SHUTTER_DLY_REG		0x3b09
#घोषणा OV5648_FREX_RST_LEN_REG			0x3b0a
#घोषणा OV5648_STROBE_WIDTH_HH_REG		0x3b0b
#घोषणा OV5648_STROBE_WIDTH_H_REG		0x3b0c

/* OTP */

#घोषणा OV5648_OTP_DATA_REG_BASE		0x3d00
#घोषणा OV5648_OTP_PROGRAM_CTRL_REG		0x3d80
#घोषणा OV5648_OTP_LOAD_CTRL_REG		0x3d81

/* PSRAM */

#घोषणा OV5648_PSRAM_CTRL1_REG			0x3f01
#घोषणा OV5648_PSRAM_CTRLF_REG			0x3f0f

/* Black Level */

#घोषणा OV5648_BLC_CTRL0_REG			0x4000
#घोषणा OV5648_BLC_CTRL1_REG			0x4001
#घोषणा OV5648_BLC_CTRL1_START_LINE(v)		((v) & GENMASK(5, 0))
#घोषणा OV5648_BLC_CTRL2_REG			0x4002
#घोषणा OV5648_BLC_CTRL2_AUTO_EN		BIT(6)
#घोषणा OV5648_BLC_CTRL2_RESET_FRAME_NUM(v)	((v) & GENMASK(5, 0))
#घोषणा OV5648_BLC_CTRL3_REG			0x4003
#घोषणा OV5648_BLC_LINE_NUM_REG			0x4004
#घोषणा OV5648_BLC_LINE_NUM(v)			((v) & GENMASK(7, 0))
#घोषणा OV5648_BLC_CTRL5_REG			0x4005
#घोषणा OV5648_BLC_CTRL5_UPDATE_EN		BIT(1)
#घोषणा OV5648_BLC_LEVEL_REG			0x4009

/* Frame */

#घोषणा OV5648_FRAME_CTRL_REG			0x4200
#घोषणा OV5648_FRAME_ON_NUM_REG			0x4201
#घोषणा OV5648_FRAME_OFF_NUM_REG		0x4202

/* MIPI CSI-2 */

#घोषणा OV5648_MIPI_CTRL0_REG			0x4800
#घोषणा OV5648_MIPI_CTRL0_CLK_LANE_AUTOGATE	BIT(5)
#घोषणा OV5648_MIPI_CTRL0_LANE_SYNC_EN		BIT(4)
#घोषणा OV5648_MIPI_CTRL0_LANE_SELECT_LANE1	0
#घोषणा OV5648_MIPI_CTRL0_LANE_SELECT_LANE2	BIT(3)
#घोषणा OV5648_MIPI_CTRL0_IDLE_LP00		0
#घोषणा OV5648_MIPI_CTRL0_IDLE_LP11		BIT(2)

#घोषणा OV5648_MIPI_CTRL1_REG			0x4801
#घोषणा OV5648_MIPI_CTRL2_REG			0x4802
#घोषणा OV5648_MIPI_CTRL3_REG			0x4803
#घोषणा OV5648_MIPI_CTRL4_REG			0x4804
#घोषणा OV5648_MIPI_CTRL5_REG			0x4805
#घोषणा OV5648_MIPI_MAX_FRAME_COUNT_H_REG	0x4810
#घोषणा OV5648_MIPI_MAX_FRAME_COUNT_L_REG	0x4811
#घोषणा OV5648_MIPI_CTRL14_REG			0x4814
#घोषणा OV5648_MIPI_DT_SPKT_REG			0x4815
#घोषणा OV5648_MIPI_HS_ZERO_MIN_H_REG		0x4818
#घोषणा OV5648_MIPI_HS_ZERO_MIN_L_REG		0x4819
#घोषणा OV5648_MIPI_HS_TRAIN_MIN_H_REG		0x481a
#घोषणा OV5648_MIPI_HS_TRAIN_MIN_L_REG		0x481b
#घोषणा OV5648_MIPI_CLK_ZERO_MIN_H_REG		0x481c
#घोषणा OV5648_MIPI_CLK_ZERO_MIN_L_REG		0x481d
#घोषणा OV5648_MIPI_CLK_PREPARE_MIN_H_REG	0x481e
#घोषणा OV5648_MIPI_CLK_PREPARE_MIN_L_REG	0x481f
#घोषणा OV5648_MIPI_CLK_POST_MIN_H_REG		0x4820
#घोषणा OV5648_MIPI_CLK_POST_MIN_L_REG		0x4821
#घोषणा OV5648_MIPI_CLK_TRAIL_MIN_H_REG		0x4822
#घोषणा OV5648_MIPI_CLK_TRAIL_MIN_L_REG		0x4823
#घोषणा OV5648_MIPI_LPX_P_MIN_H_REG		0x4824
#घोषणा OV5648_MIPI_LPX_P_MIN_L_REG		0x4825
#घोषणा OV5648_MIPI_HS_PREPARE_MIN_H_REG	0x4826
#घोषणा OV5648_MIPI_HS_PREPARE_MIN_L_REG	0x4827
#घोषणा OV5648_MIPI_HS_EXIT_MIN_H_REG		0x4828
#घोषणा OV5648_MIPI_HS_EXIT_MIN_L_REG		0x4829
#घोषणा OV5648_MIPI_HS_ZERO_MIN_UI_REG		0x482a
#घोषणा OV5648_MIPI_HS_TRAIL_MIN_UI_REG		0x482b
#घोषणा OV5648_MIPI_CLK_ZERO_MIN_UI_REG		0x482c
#घोषणा OV5648_MIPI_CLK_PREPARE_MIN_UI_REG	0x482d
#घोषणा OV5648_MIPI_CLK_POST_MIN_UI_REG		0x482e
#घोषणा OV5648_MIPI_CLK_TRAIL_MIN_UI_REG	0x482f
#घोषणा OV5648_MIPI_LPX_P_MIN_UI_REG		0x4830
#घोषणा OV5648_MIPI_HS_PREPARE_MIN_UI_REG	0x4831
#घोषणा OV5648_MIPI_HS_EXIT_MIN_UI_REG		0x4832
#घोषणा OV5648_MIPI_REG_MIN_H_REG		0x4833
#घोषणा OV5648_MIPI_REG_MIN_L_REG		0x4834
#घोषणा OV5648_MIPI_REG_MAX_H_REG		0x4835
#घोषणा OV5648_MIPI_REG_MAX_L_REG		0x4836
#घोषणा OV5648_MIPI_PCLK_PERIOD_REG		0x4837
#घोषणा OV5648_MIPI_WKUP_DLY_REG		0x4838
#घोषणा OV5648_MIPI_LP_GPIO_REG			0x483b
#घोषणा OV5648_MIPI_SNR_PCLK_DIV_REG		0x4843

/* ISP */

#घोषणा OV5648_ISP_CTRL0_REG			0x5000
#घोषणा OV5648_ISP_CTRL0_BLACK_CORRECT_EN	BIT(2)
#घोषणा OV5648_ISP_CTRL0_WHITE_CORRECT_EN	BIT(1)
#घोषणा OV5648_ISP_CTRL1_REG			0x5001
#घोषणा OV5648_ISP_CTRL1_AWB_EN			BIT(0)
#घोषणा OV5648_ISP_CTRL2_REG			0x5002
#घोषणा OV5648_ISP_CTRL2_WIN_EN			BIT(6)
#घोषणा OV5648_ISP_CTRL2_OTP_EN			BIT(1)
#घोषणा OV5648_ISP_CTRL2_AWB_GAIN_EN		BIT(0)
#घोषणा OV5648_ISP_CTRL3_REG			0x5003
#घोषणा OV5648_ISP_CTRL3_BUF_EN			BIT(3)
#घोषणा OV5648_ISP_CTRL3_BIN_MAN_SET		BIT(2)
#घोषणा OV5648_ISP_CTRL3_BIN_AUTO_EN		BIT(1)
#घोषणा OV5648_ISP_CTRL4_REG			0x5004
#घोषणा OV5648_ISP_CTRL5_REG			0x5005
#घोषणा OV5648_ISP_CTRL6_REG			0x5006
#घोषणा OV5648_ISP_CTRL7_REG			0x5007
#घोषणा OV5648_ISP_MAN_OFFSET_X_H_REG		0x5008
#घोषणा OV5648_ISP_MAN_OFFSET_X_L_REG		0x5009
#घोषणा OV5648_ISP_MAN_OFFSET_Y_H_REG		0x500a
#घोषणा OV5648_ISP_MAN_OFFSET_Y_L_REG		0x500b
#घोषणा OV5648_ISP_MAN_WIN_OFFSET_X_H_REG	0x500c
#घोषणा OV5648_ISP_MAN_WIN_OFFSET_X_L_REG	0x500d
#घोषणा OV5648_ISP_MAN_WIN_OFFSET_Y_H_REG	0x500e
#घोषणा OV5648_ISP_MAN_WIN_OFFSET_Y_L_REG	0x500f
#घोषणा OV5648_ISP_MAN_WIN_OUTPUT_X_H_REG	0x5010
#घोषणा OV5648_ISP_MAN_WIN_OUTPUT_X_L_REG	0x5011
#घोषणा OV5648_ISP_MAN_WIN_OUTPUT_Y_H_REG	0x5012
#घोषणा OV5648_ISP_MAN_WIN_OUTPUT_Y_L_REG	0x5013
#घोषणा OV5648_ISP_MAN_INPUT_X_H_REG		0x5014
#घोषणा OV5648_ISP_MAN_INPUT_X_L_REG		0x5015
#घोषणा OV5648_ISP_MAN_INPUT_Y_H_REG		0x5016
#घोषणा OV5648_ISP_MAN_INPUT_Y_L_REG		0x5017
#घोषणा OV5648_ISP_CTRL18_REG			0x5018
#घोषणा OV5648_ISP_CTRL19_REG			0x5019
#घोषणा OV5648_ISP_CTRL1A_REG			0x501a
#घोषणा OV5648_ISP_CTRL1D_REG			0x501d
#घोषणा OV5648_ISP_CTRL1F_REG			0x501f
#घोषणा OV5648_ISP_CTRL1F_OUTPUT_EN		3
#घोषणा OV5648_ISP_CTRL25_REG			0x5025

#घोषणा OV5648_ISP_CTRL3D_REG			0x503d
#घोषणा OV5648_ISP_CTRL3D_PATTERN_EN		BIT(7)
#घोषणा OV5648_ISP_CTRL3D_ROLLING_BAR_EN	BIT(6)
#घोषणा OV5648_ISP_CTRL3D_TRANSPARENT_MODE	BIT(5)
#घोषणा OV5648_ISP_CTRL3D_SQUARES_BW_MODE	BIT(4)
#घोषणा OV5648_ISP_CTRL3D_PATTERN_COLOR_BARS	0
#घोषणा OV5648_ISP_CTRL3D_PATTERN_RANDOM_DATA	1
#घोषणा OV5648_ISP_CTRL3D_PATTERN_COLOR_SQUARES	2
#घोषणा OV5648_ISP_CTRL3D_PATTERN_INPUT		3

#घोषणा OV5648_ISP_CTRL3E_REG			0x503e
#घोषणा OV5648_ISP_CTRL4B_REG			0x504b
#घोषणा OV5648_ISP_CTRL4B_POST_BIN_H_EN		BIT(5)
#घोषणा OV5648_ISP_CTRL4B_POST_BIN_V_EN		BIT(4)
#घोषणा OV5648_ISP_CTRL4C_REG			0x504c
#घोषणा OV5648_ISP_CTRL57_REG			0x5057
#घोषणा OV5648_ISP_CTRL58_REG			0x5058
#घोषणा OV5648_ISP_CTRL59_REG			0x5059

#घोषणा OV5648_ISP_WINDOW_START_X_H_REG		0x5980
#घोषणा OV5648_ISP_WINDOW_START_X_L_REG		0x5981
#घोषणा OV5648_ISP_WINDOW_START_Y_H_REG		0x5982
#घोषणा OV5648_ISP_WINDOW_START_Y_L_REG		0x5983
#घोषणा OV5648_ISP_WINDOW_WIN_X_H_REG		0x5984
#घोषणा OV5648_ISP_WINDOW_WIN_X_L_REG		0x5985
#घोषणा OV5648_ISP_WINDOW_WIN_Y_H_REG		0x5986
#घोषणा OV5648_ISP_WINDOW_WIN_Y_L_REG		0x5987
#घोषणा OV5648_ISP_WINDOW_MAN_REG		0x5988

/* White Balance */

#घोषणा OV5648_AWB_CTRL_REG			0x5180
#घोषणा OV5648_AWB_CTRL_FAST_AWB		BIT(6)
#घोषणा OV5648_AWB_CTRL_GAIN_FREEZE_EN		BIT(5)
#घोषणा OV5648_AWB_CTRL_SUM_FREEZE_EN		BIT(4)
#घोषणा OV5648_AWB_CTRL_GAIN_MANUAL_EN		BIT(3)

#घोषणा OV5648_AWB_DELTA_REG			0x5181
#घोषणा OV5648_AWB_STABLE_RANGE_REG		0x5182
#घोषणा OV5648_AWB_STABLE_RANGE_WIDE_REG	0x5183
#घोषणा OV5648_HSIZE_MAN_REG			0x5185

#घोषणा OV5648_GAIN_RED_MAN_H_REG		0x5186
#घोषणा OV5648_GAIN_RED_MAN_H(v)		(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV5648_GAIN_RED_MAN_L_REG		0x5187
#घोषणा OV5648_GAIN_RED_MAN_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV5648_GAIN_GREEN_MAN_H_REG		0x5188
#घोषणा OV5648_GAIN_GREEN_MAN_H(v)		(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV5648_GAIN_GREEN_MAN_L_REG		0x5189
#घोषणा OV5648_GAIN_GREEN_MAN_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV5648_GAIN_BLUE_MAN_H_REG		0x518a
#घोषणा OV5648_GAIN_BLUE_MAN_H(v)		(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV5648_GAIN_BLUE_MAN_L_REG		0x518b
#घोषणा OV5648_GAIN_BLUE_MAN_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV5648_GAIN_RED_LIMIT_REG		0x518c
#घोषणा OV5648_GAIN_GREEN_LIMIT_REG		0x518d
#घोषणा OV5648_GAIN_BLUE_LIMIT_REG		0x518e
#घोषणा OV5648_AWB_FRAME_COUNT_REG		0x518f
#घोषणा OV5648_AWB_BASE_MAN_REG			0x51df

/* Macros */

#घोषणा ov5648_subdev_sensor(s) \
	container_of(s, काष्ठा ov5648_sensor, subdev)

#घोषणा ov5648_ctrl_subdev(c) \
	(&container_of((c)->handler, काष्ठा ov5648_sensor, \
		       ctrls.handler)->subdev)

/* Data काष्ठाures */

काष्ठा ov5648_रेजिस्टर_value अणु
	u16 address;
	u8 value;
	अचिन्हित पूर्णांक delay_ms;
पूर्ण;

/*
 * PLL1 Clock Tree:
 *
 * +-< XVCLK
 * |
 * +-+ pll_pre_भाग (0x3037 [3:0], special values: 5: 1.5, 7: 2.5)
 *   |
 *   +-+ pll_mul (0x3036 [7:0])
 *     |
 *     +-+ sys_भाग (0x3035 [7:4])
 *       |
 *       +-+ mipi_भाग (0x3035 [3:0])
 *       | |
 *       | +-> MIPI_SCLK
 *       | |
 *       | +-+ mipi_phy_भाग (2)
 *       |   |
 *       |   +-> MIPI_CLK
 *       |
 *       +-+ root_भाग (0x3037 [4])
 *         |
 *         +-+ bit_भाग (0x3034 [3:0], 8 bits: 2, 10 bits: 2.5, other: 1)
 *           |
 *           +-+ sclk_भाग (0x3106 [3:2])
 *             |
 *             +-> SCLK
 *             |
 *             +-+ mipi_भाग (0x3035, 1: PCLK = SCLK)
 *               |
 *               +-> PCLK
 */

काष्ठा ov5648_pll1_config अणु
	अचिन्हित पूर्णांक pll_pre_भाग;
	अचिन्हित पूर्णांक pll_mul;
	अचिन्हित पूर्णांक sys_भाग;
	अचिन्हित पूर्णांक root_भाग;
	अचिन्हित पूर्णांक sclk_भाग;
	अचिन्हित पूर्णांक mipi_भाग;
पूर्ण;

/*
 * PLL2 Clock Tree:
 *
 * +-< XVCLK
 * |
 * +-+ plls_pre_भाग (0x303d [5:4], special values: 0: 1, 1: 1.5)
 *   |
 *   +-+ plls_भाग_r (0x303d [2])
 *     |
 *     +-+ plls_mul (0x303b [4:0])
 *       |
 *       +-+ sys_भाग (0x303c [3:0])
 *         |
 *         +-+ sel_भाग (0x303d [1:0], special values: 0: 1, 3: 2.5)
 *           |
 *           +-> ADCLK
 */

काष्ठा ov5648_pll2_config अणु
	अचिन्हित पूर्णांक plls_pre_भाग;
	अचिन्हित पूर्णांक plls_भाग_r;
	अचिन्हित पूर्णांक plls_mul;
	अचिन्हित पूर्णांक sys_भाग;
	अचिन्हित पूर्णांक sel_भाग;
पूर्ण;

/*
 * General क्रमmulas क्रम (array-centered) mode calculation:
 * - photo_array_width = 2624
 * - crop_start_x = (photo_array_width - output_size_x) / 2
 * - crop_end_x = crop_start_x + offset_x + output_size_x - 1
 *
 * - photo_array_height = 1956
 * - crop_start_y = (photo_array_height - output_size_y) / 2
 * - crop_end_y = crop_start_y + offset_y + output_size_y - 1
 */

काष्ठा ov5648_mode अणु
	अचिन्हित पूर्णांक crop_start_x;
	अचिन्हित पूर्णांक offset_x;
	अचिन्हित पूर्णांक output_size_x;
	अचिन्हित पूर्णांक crop_end_x;
	अचिन्हित पूर्णांक hts;

	अचिन्हित पूर्णांक crop_start_y;
	अचिन्हित पूर्णांक offset_y;
	अचिन्हित पूर्णांक output_size_y;
	अचिन्हित पूर्णांक crop_end_y;
	अचिन्हित पूर्णांक vts;

	bool binning_x;
	bool binning_y;

	अचिन्हित पूर्णांक inc_x_odd;
	अचिन्हित पूर्णांक inc_x_even;
	अचिन्हित पूर्णांक inc_y_odd;
	अचिन्हित पूर्णांक inc_y_even;

	/* 8-bit frame पूर्णांकerval followed by 10-bit frame पूर्णांकerval. */
	काष्ठा v4l2_fract frame_पूर्णांकerval[2];

	/* 8-bit config followed by 10-bit config. */
	स्थिर काष्ठा ov5648_pll1_config *pll1_config[2];
	स्थिर काष्ठा ov5648_pll2_config *pll2_config;

	स्थिर काष्ठा ov5648_रेजिस्टर_value *रेजिस्टर_values;
	अचिन्हित पूर्णांक रेजिस्टर_values_count;
पूर्ण;

काष्ठा ov5648_state अणु
	स्थिर काष्ठा ov5648_mode *mode;
	u32 mbus_code;

	bool streaming;
पूर्ण;

काष्ठा ov5648_ctrls अणु
	काष्ठा v4l2_ctrl *exposure_स्वतः;
	काष्ठा v4l2_ctrl *exposure;

	काष्ठा v4l2_ctrl *gain_स्वतः;
	काष्ठा v4l2_ctrl *gain;

	काष्ठा v4l2_ctrl *white_balance_स्वतः;
	काष्ठा v4l2_ctrl *red_balance;
	काष्ठा v4l2_ctrl *blue_balance;

	काष्ठा v4l2_ctrl *link_freq;
	काष्ठा v4l2_ctrl *pixel_rate;

	काष्ठा v4l2_ctrl_handler handler;
पूर्ण __packed;

काष्ठा ov5648_sensor अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *i2c_client;
	काष्ठा gpio_desc *reset;
	काष्ठा gpio_desc *घातerकरोwn;
	काष्ठा regulator *avdd;
	काष्ठा regulator *dvdd;
	काष्ठा regulator *करोvdd;
	काष्ठा clk *xvclk;

	काष्ठा v4l2_fwnode_endpoपूर्णांक endpoपूर्णांक;
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pad;

	काष्ठा mutex mutex;

	काष्ठा ov5648_state state;
	काष्ठा ov5648_ctrls ctrls;
पूर्ण;

/* Static definitions */

/*
 * XVCLK = 24 MHz
 * SCLK  = 84 MHz
 * PCLK  = 84 MHz
 */
अटल स्थिर काष्ठा ov5648_pll1_config ov5648_pll1_config_native_8_bits = अणु
	.pll_pre_भाग	= 3,
	.pll_mul	= 84,
	.sys_भाग	= 2,
	.root_भाग	= 1,
	.sclk_भाग	= 1,
	.mipi_भाग	= 1,
पूर्ण;

/*
 * XVCLK = 24 MHz
 * SCLK  = 84 MHz
 * PCLK  = 84 MHz
 */
अटल स्थिर काष्ठा ov5648_pll1_config ov5648_pll1_config_native_10_bits = अणु
	.pll_pre_भाग	= 3,
	.pll_mul	= 105,
	.sys_भाग	= 2,
	.root_भाग	= 1,
	.sclk_भाग	= 1,
	.mipi_भाग	= 1,
पूर्ण;

/*
 * XVCLK = 24 MHz
 * ADCLK = 200 MHz
 */
अटल स्थिर काष्ठा ov5648_pll2_config ov5648_pll2_config_native = अणु
	.plls_pre_भाग	= 3,
	.plls_भाग_r	= 1,
	.plls_mul	= 25,
	.sys_भाग	= 1,
	.sel_भाग	= 1,
पूर्ण;

अटल स्थिर काष्ठा ov5648_mode ov5648_modes[] = अणु
	/* 2592x1944 */
	अणु
		/* Horizontal */
		.crop_start_x	= 16,
		.offset_x	= 0,
		.output_size_x	= 2592,
		.crop_end_x	= 2607,
		.hts		= 2816,

		/* Vertical */
		.crop_start_y	= 6,
		.offset_y	= 0,
		.output_size_y	= 1944,
		.crop_end_y	= 1949,
		.vts		= 1984,

		/* Subsample increase */
		.inc_x_odd	= 1,
		.inc_x_even	= 1,
		.inc_y_odd	= 1,
		.inc_y_even	= 1,

		/* Frame Interval */
		.frame_पूर्णांकerval	= अणु
			अणु 1,	15 पूर्ण,
			अणु 1,	15 पूर्ण,
		पूर्ण,

		/* PLL */
		.pll1_config	= अणु
			&ov5648_pll1_config_native_8_bits,
			&ov5648_pll1_config_native_10_bits,
		पूर्ण,
		.pll2_config	= &ov5648_pll2_config_native,
	पूर्ण,
	/* 1600x1200 (UXGA) */
	अणु
		/* Horizontal */
		.crop_start_x	= 512,
		.offset_x	= 0,
		.output_size_x	= 1600,
		.crop_end_x	= 2111,
		.hts		= 2816,

		/* Vertical */
		.crop_start_y	= 378,
		.offset_y	= 0,
		.output_size_y	= 1200,
		.crop_end_y	= 1577,
		.vts		= 1984,

		/* Subsample increase */
		.inc_x_odd	= 1,
		.inc_x_even	= 1,
		.inc_y_odd	= 1,
		.inc_y_even	= 1,

		/* Frame Interval */
		.frame_पूर्णांकerval	= अणु
			अणु 1,	15 पूर्ण,
			अणु 1,	15 पूर्ण,
		पूर्ण,

		/* PLL */
		.pll1_config	= अणु
			&ov5648_pll1_config_native_8_bits,
			&ov5648_pll1_config_native_10_bits,
		पूर्ण,
		.pll2_config	= &ov5648_pll2_config_native,
	पूर्ण,
	/* 1920x1080 (Full HD) */
	अणु
		/* Horizontal */
		.crop_start_x	= 352,
		.offset_x	= 0,
		.output_size_x	= 1920,
		.crop_end_x	= 2271,
		.hts		= 2816,

		/* Vertical */
		.crop_start_y	= 438,
		.offset_y	= 0,
		.output_size_y	= 1080,
		.crop_end_y	= 1517,
		.vts		= 1984,

		/* Subsample increase */
		.inc_x_odd	= 1,
		.inc_x_even	= 1,
		.inc_y_odd	= 1,
		.inc_y_even	= 1,

		/* Frame Interval */
		.frame_पूर्णांकerval	= अणु
			अणु 1,	15 पूर्ण,
			अणु 1,	15 पूर्ण,
		पूर्ण,

		/* PLL */
		.pll1_config	= अणु
			&ov5648_pll1_config_native_8_bits,
			&ov5648_pll1_config_native_10_bits,
		पूर्ण,
		.pll2_config	= &ov5648_pll2_config_native,
	पूर्ण,
	/* 1280x960 */
	अणु
		/* Horizontal */
		.crop_start_x	= 16,
		.offset_x	= 8,
		.output_size_x	= 1280,
		.crop_end_x	= 2607,
		.hts		= 1912,

		/* Vertical */
		.crop_start_y	= 6,
		.offset_y	= 6,
		.output_size_y	= 960,
		.crop_end_y	= 1949,
		.vts		= 1496,

		/* Binning */
		.binning_x	= true,

		/* Subsample increase */
		.inc_x_odd	= 3,
		.inc_x_even	= 1,
		.inc_y_odd	= 3,
		.inc_y_even	= 1,

		/* Frame Interval */
		.frame_पूर्णांकerval	= अणु
			अणु 1,	30 पूर्ण,
			अणु 1,	30 पूर्ण,
		पूर्ण,

		/* PLL */
		.pll1_config	= अणु
			&ov5648_pll1_config_native_8_bits,
			&ov5648_pll1_config_native_10_bits,
		पूर्ण,
		.pll2_config	= &ov5648_pll2_config_native,
	पूर्ण,
	/* 1280x720 (HD) */
	अणु
		/* Horizontal */
		.crop_start_x	= 16,
		.offset_x	= 8,
		.output_size_x	= 1280,
		.crop_end_x	= 2607,
		.hts		= 1912,

		/* Vertical */
		.crop_start_y	= 254,
		.offset_y	= 2,
		.output_size_y	= 720,
		.crop_end_y	= 1701,
		.vts		= 1496,

		/* Binning */
		.binning_x	= true,

		/* Subsample increase */
		.inc_x_odd	= 3,
		.inc_x_even	= 1,
		.inc_y_odd	= 3,
		.inc_y_even	= 1,

		/* Frame Interval */
		.frame_पूर्णांकerval	= अणु
			अणु 1,	30 पूर्ण,
			अणु 1,	30 पूर्ण,
		पूर्ण,

		/* PLL */
		.pll1_config	= अणु
			&ov5648_pll1_config_native_8_bits,
			&ov5648_pll1_config_native_10_bits,
		पूर्ण,
		.pll2_config	= &ov5648_pll2_config_native,
	पूर्ण,
	/* 640x480 (VGA) */
	अणु
		/* Horizontal */
		.crop_start_x	= 0,
		.offset_x	= 8,
		.output_size_x	= 640,
		.crop_end_x	= 2623,
		.hts		= 1896,

		/* Vertical */
		.crop_start_y	= 0,
		.offset_y	= 2,
		.output_size_y	= 480,
		.crop_end_y	= 1953,
		.vts		= 984,

		/* Binning */
		.binning_x	= true,

		/* Subsample increase */
		.inc_x_odd	= 7,
		.inc_x_even	= 1,
		.inc_y_odd	= 7,
		.inc_y_even	= 1,

		/* Frame Interval */
		.frame_पूर्णांकerval	= अणु
			अणु 1,	30 पूर्ण,
			अणु 1,	30 पूर्ण,
		पूर्ण,

		/* PLL */
		.pll1_config	= अणु
			&ov5648_pll1_config_native_8_bits,
			&ov5648_pll1_config_native_10_bits,
		पूर्ण,
		.pll2_config	= &ov5648_pll2_config_native,
	पूर्ण,
पूर्ण;

अटल स्थिर u32 ov5648_mbus_codes[] = अणु
	MEDIA_BUS_FMT_SBGGR8_1X8,
	MEDIA_BUS_FMT_SBGGR10_1X10,
पूर्ण;

अटल स्थिर काष्ठा ov5648_रेजिस्टर_value ov5648_init_sequence[] = अणु
	/* PSRAM */
	अणु OV5648_PSRAM_CTRL1_REG, 0x0d पूर्ण,
	अणु OV5648_PSRAM_CTRLF_REG, 0xf5 पूर्ण,
पूर्ण;

अटल स्थिर s64 ov5648_link_freq_menu[] = अणु
	210000000,
	168000000,
पूर्ण;

अटल स्थिर अक्षर *स्थिर ov5648_test_pattern_menu[] = अणु
	"Disabled",
	"Random data",
	"Color bars",
	"Color bars with rolling bar",
	"Color squares",
	"Color squares with rolling bar"
पूर्ण;

अटल स्थिर u8 ov5648_test_pattern_bits[] = अणु
	0,
	OV5648_ISP_CTRL3D_PATTERN_EN | OV5648_ISP_CTRL3D_PATTERN_RANDOM_DATA,
	OV5648_ISP_CTRL3D_PATTERN_EN | OV5648_ISP_CTRL3D_PATTERN_COLOR_BARS,
	OV5648_ISP_CTRL3D_PATTERN_EN | OV5648_ISP_CTRL3D_ROLLING_BAR_EN |
	OV5648_ISP_CTRL3D_PATTERN_COLOR_BARS,
	OV5648_ISP_CTRL3D_PATTERN_EN | OV5648_ISP_CTRL3D_PATTERN_COLOR_SQUARES,
	OV5648_ISP_CTRL3D_PATTERN_EN | OV5648_ISP_CTRL3D_ROLLING_BAR_EN |
	OV5648_ISP_CTRL3D_PATTERN_COLOR_SQUARES,
पूर्ण;

/* Input/Output */

अटल पूर्णांक ov5648_पढ़ो(काष्ठा ov5648_sensor *sensor, u16 address, u8 *value)
अणु
	अचिन्हित अक्षर data[2] = अणु address >> 8, address & 0xff पूर्ण;
	काष्ठा i2c_client *client = sensor->i2c_client;
	पूर्णांक ret;

	ret = i2c_master_send(client, data, माप(data));
	अगर (ret < 0) अणु
		dev_dbg(&client->dev, "i2c send error at address %#04x\n",
			address);
		वापस ret;
	पूर्ण

	ret = i2c_master_recv(client, value, 1);
	अगर (ret < 0) अणु
		dev_dbg(&client->dev, "i2c recv error at address %#04x\n",
			address);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5648_ग_लिखो(काष्ठा ov5648_sensor *sensor, u16 address, u8 value)
अणु
	अचिन्हित अक्षर data[3] = अणु address >> 8, address & 0xff, value पूर्ण;
	काष्ठा i2c_client *client = sensor->i2c_client;
	पूर्णांक ret;

	ret = i2c_master_send(client, data, माप(data));
	अगर (ret < 0) अणु
		dev_dbg(&client->dev, "i2c send error at address %#04x\n",
			address);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5648_ग_लिखो_sequence(काष्ठा ov5648_sensor *sensor,
				 स्थिर काष्ठा ov5648_रेजिस्टर_value *sequence,
				 अचिन्हित पूर्णांक sequence_count)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < sequence_count; i++) अणु
		ret = ov5648_ग_लिखो(sensor, sequence[i].address,
				   sequence[i].value);
		अगर (ret)
			अवरोध;

		अगर (sequence[i].delay_ms)
			msleep(sequence[i].delay_ms);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ov5648_update_bits(काष्ठा ov5648_sensor *sensor, u16 address,
			      u8 mask, u8 bits)
अणु
	u8 value = 0;
	पूर्णांक ret;

	ret = ov5648_पढ़ो(sensor, address, &value);
	अगर (ret)
		वापस ret;

	value &= ~mask;
	value |= bits;

	ret = ov5648_ग_लिखो(sensor, address, value);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/* Sensor */

अटल पूर्णांक ov5648_sw_reset(काष्ठा ov5648_sensor *sensor)
अणु
	वापस ov5648_ग_लिखो(sensor, OV5648_SW_RESET_REG, OV5648_SW_RESET_RESET);
पूर्ण

अटल पूर्णांक ov5648_sw_standby(काष्ठा ov5648_sensor *sensor, पूर्णांक standby)
अणु
	u8 value = 0;

	अगर (!standby)
		value = OV5648_SW_STANDBY_STREAM_ON;

	वापस ov5648_ग_लिखो(sensor, OV5648_SW_STANDBY_REG, value);
पूर्ण

अटल पूर्णांक ov5648_chip_id_check(काष्ठा ov5648_sensor *sensor)
अणु
	u16 regs[] = अणु OV5648_CHIP_ID_H_REG, OV5648_CHIP_ID_L_REG पूर्ण;
	u8 values[] = अणु OV5648_CHIP_ID_H_VALUE, OV5648_CHIP_ID_L_VALUE पूर्ण;
	अचिन्हित पूर्णांक i;
	u8 value;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++) अणु
		ret = ov5648_पढ़ो(sensor, regs[i], &value);
		अगर (ret < 0)
			वापस ret;

		अगर (value != values[i]) अणु
			dev_err(sensor->dev,
				"chip id value mismatch: %#x instead of %#x\n",
				value, values[i]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5648_avdd_पूर्णांकernal_घातer(काष्ठा ov5648_sensor *sensor, पूर्णांक on)
अणु
	वापस ov5648_ग_लिखो(sensor, OV5648_A_PWC_PK_O0_REG,
			    on ? 0 : OV5648_A_PWC_PK_O0_BP_REGULATOR_N);
पूर्ण

अटल पूर्णांक ov5648_pad_configure(काष्ठा ov5648_sensor *sensor)
अणु
	पूर्णांक ret;

	/* Configure pads as input. */

	ret = ov5648_ग_लिखो(sensor, OV5648_PAD_OEN1_REG, 0);
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_PAD_OEN2_REG, 0);
	अगर (ret)
		वापस ret;

	/* Disable FREX pin. */

	वापस ov5648_ग_लिखो(sensor, OV5648_PAD_PK_REG,
			    OV5648_PAD_PK_DRIVE_STRENGTH_1X |
			    OV5648_PAD_PK_FREX_N);
पूर्ण

अटल पूर्णांक ov5648_mipi_configure(काष्ठा ov5648_sensor *sensor)
अणु
	काष्ठा v4l2_fwnode_bus_mipi_csi2 *bus_mipi_csi2 =
		&sensor->endpoपूर्णांक.bus.mipi_csi2;
	अचिन्हित पूर्णांक lanes_count = bus_mipi_csi2->num_data_lanes;
	पूर्णांक ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_MIPI_CTRL0_REG,
			   OV5648_MIPI_CTRL0_CLK_LANE_AUTOGATE |
			   OV5648_MIPI_CTRL0_LANE_SELECT_LANE1 |
			   OV5648_MIPI_CTRL0_IDLE_LP11);
	अगर (ret)
		वापस ret;

	वापस ov5648_ग_लिखो(sensor, OV5648_MIPI_SC_CTRL0_REG,
			    OV5648_MIPI_SC_CTRL0_MIPI_LANES(lanes_count) |
			    OV5648_MIPI_SC_CTRL0_PHY_LP_RX_PD |
			    OV5648_MIPI_SC_CTRL0_MIPI_EN);
पूर्ण

अटल पूर्णांक ov5648_black_level_configure(काष्ठा ov5648_sensor *sensor)
अणु
	पूर्णांक ret;

	/* Up to 6 lines are available क्रम black level calibration. */

	ret = ov5648_ग_लिखो(sensor, OV5648_BLC_CTRL1_REG,
			   OV5648_BLC_CTRL1_START_LINE(2));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_BLC_CTRL2_REG,
			   OV5648_BLC_CTRL2_AUTO_EN |
			   OV5648_BLC_CTRL2_RESET_FRAME_NUM(5));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_BLC_LINE_NUM_REG,
			   OV5648_BLC_LINE_NUM(4));
	अगर (ret)
		वापस ret;

	वापस ov5648_update_bits(sensor, OV5648_BLC_CTRL5_REG,
				  OV5648_BLC_CTRL5_UPDATE_EN,
				  OV5648_BLC_CTRL5_UPDATE_EN);
पूर्ण

अटल पूर्णांक ov5648_isp_configure(काष्ठा ov5648_sensor *sensor)
अणु
	u8 bits;
	पूर्णांक ret;

	/* Enable black and white level correction. */
	bits = OV5648_ISP_CTRL0_BLACK_CORRECT_EN |
	       OV5648_ISP_CTRL0_WHITE_CORRECT_EN;

	ret = ov5648_update_bits(sensor, OV5648_ISP_CTRL0_REG, bits, bits);
	अगर (ret)
		वापस ret;

	/* Enable AWB. */
	ret = ov5648_ग_लिखो(sensor, OV5648_ISP_CTRL1_REG,
			   OV5648_ISP_CTRL1_AWB_EN);
	अगर (ret)
		वापस ret;

	/* Enable AWB gain and winकरोwing. */
	ret = ov5648_ग_लिखो(sensor, OV5648_ISP_CTRL2_REG,
			   OV5648_ISP_CTRL2_WIN_EN |
			   OV5648_ISP_CTRL2_AWB_GAIN_EN);
	अगर (ret)
		वापस ret;

	/* Enable buffering and स्वतः-binning. */
	ret = ov5648_ग_लिखो(sensor, OV5648_ISP_CTRL3_REG,
			   OV5648_ISP_CTRL3_BUF_EN |
			   OV5648_ISP_CTRL3_BIN_AUTO_EN);
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_ISP_CTRL4_REG, 0);
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_ISP_CTRL1F_REG,
			   OV5648_ISP_CTRL1F_OUTPUT_EN);
	अगर (ret)
		वापस ret;

	/* Enable post-binning filters. */
	ret = ov5648_ग_लिखो(sensor, OV5648_ISP_CTRL4B_REG,
			   OV5648_ISP_CTRL4B_POST_BIN_H_EN |
			   OV5648_ISP_CTRL4B_POST_BIN_V_EN);
	अगर (ret)
		वापस ret;

	/* Disable debanding and night mode. Debug bit seems necessary. */
	ret = ov5648_ग_लिखो(sensor, OV5648_AEC_CTRL0_REG,
			   OV5648_AEC_CTRL0_DEBUG |
			   OV5648_AEC_CTRL0_START_SEL_EN);
	अगर (ret)
		वापस ret;

	वापस ov5648_ग_लिखो(sensor, OV5648_MANUAL_CTRL_REG,
			    OV5648_MANUAL_CTRL_FRAME_DELAY(1));
पूर्ण

अटल अचिन्हित दीर्घ ov5648_mode_pll1_rate(काष्ठा ov5648_sensor *sensor,
					   स्थिर काष्ठा ov5648_pll1_config *config)
अणु
	अचिन्हित दीर्घ xvclk_rate;
	अचिन्हित दीर्घ pll1_rate;

	xvclk_rate = clk_get_rate(sensor->xvclk);
	pll1_rate = xvclk_rate * config->pll_mul;

	चयन (config->pll_pre_भाग) अणु
	हाल 5:
		pll1_rate *= 3;
		pll1_rate /= 2;
		अवरोध;
	हाल 7:
		pll1_rate *= 5;
		pll1_rate /= 2;
		अवरोध;
	शेष:
		pll1_rate /= config->pll_pre_भाग;
		अवरोध;
	पूर्ण

	वापस pll1_rate;
पूर्ण

अटल पूर्णांक ov5648_mode_pll1_configure(काष्ठा ov5648_sensor *sensor,
				      स्थिर काष्ठा ov5648_mode *mode,
				      u32 mbus_code)
अणु
	स्थिर काष्ठा ov5648_pll1_config *config;
	u8 value;
	पूर्णांक ret;

	value = OV5648_PLL_CTRL0_PLL_CHARGE_PUMP(1);

	चयन (mbus_code) अणु
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		config = mode->pll1_config[0];
		value |= OV5648_PLL_CTRL0_BITS(8);
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
		config = mode->pll1_config[1];
		value |= OV5648_PLL_CTRL0_BITS(10);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = ov5648_ग_लिखो(sensor, OV5648_PLL_CTRL0_REG, value);
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_PLL_DIV_REG,
			   OV5648_PLL_DIV_ROOT_DIV(config->root_भाग) |
			   OV5648_PLL_DIV_PLL_PRE_DIV(config->pll_pre_भाग));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_PLL_MUL_REG,
			   OV5648_PLL_MUL(config->pll_mul));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_PLL_CTRL1_REG,
			   OV5648_PLL_CTRL1_SYS_DIV(config->sys_भाग) |
			   OV5648_PLL_CTRL1_MIPI_DIV(config->mipi_भाग));
	अगर (ret)
		वापस ret;

	वापस ov5648_ग_लिखो(sensor, OV5648_SRB_CTRL_REG,
			    OV5648_SRB_CTRL_SCLK_DIV(config->sclk_भाग) |
			    OV5648_SRB_CTRL_SCLK_ARBITER_EN);
पूर्ण

अटल पूर्णांक ov5648_mode_pll2_configure(काष्ठा ov5648_sensor *sensor,
				      स्थिर काष्ठा ov5648_mode *mode)
अणु
	स्थिर काष्ठा ov5648_pll2_config *config = mode->pll2_config;
	पूर्णांक ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_PLLS_DIV_REG,
			   OV5648_PLLS_DIV_PLLS_PRE_DIV(config->plls_pre_भाग) |
			   OV5648_PLLS_DIV_PLLS_DIV_R(config->plls_भाग_r) |
			   OV5648_PLLS_DIV_PLLS_SEL_DIV(config->sel_भाग));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_PLLS_MUL_REG,
			   OV5648_PLLS_MUL(config->plls_mul));
	अगर (ret)
		वापस ret;

	वापस ov5648_ग_लिखो(sensor, OV5648_PLLS_CTRL_REG,
			    OV5648_PLLS_CTRL_PLL_CHARGE_PUMP(1) |
			    OV5648_PLLS_CTRL_SYS_DIV(config->sys_भाग));
पूर्ण

अटल पूर्णांक ov5648_mode_configure(काष्ठा ov5648_sensor *sensor,
				 स्थिर काष्ठा ov5648_mode *mode, u32 mbus_code)
अणु
	पूर्णांक ret;

	/* Crop Start X */

	ret = ov5648_ग_लिखो(sensor, OV5648_CROP_START_X_H_REG,
			   OV5648_CROP_START_X_H(mode->crop_start_x));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_CROP_START_X_L_REG,
			   OV5648_CROP_START_X_L(mode->crop_start_x));
	अगर (ret)
		वापस ret;

	/* Offset X */

	ret = ov5648_ग_लिखो(sensor, OV5648_OFFSET_X_H_REG,
			   OV5648_OFFSET_X_H(mode->offset_x));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_OFFSET_X_L_REG,
			   OV5648_OFFSET_X_L(mode->offset_x));
	अगर (ret)
		वापस ret;

	/* Output Size X */

	ret = ov5648_ग_लिखो(sensor, OV5648_OUTPUT_SIZE_X_H_REG,
			   OV5648_OUTPUT_SIZE_X_H(mode->output_size_x));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_OUTPUT_SIZE_X_L_REG,
			   OV5648_OUTPUT_SIZE_X_L(mode->output_size_x));
	अगर (ret)
		वापस ret;

	/* Crop End X */

	ret = ov5648_ग_लिखो(sensor, OV5648_CROP_END_X_H_REG,
			   OV5648_CROP_END_X_H(mode->crop_end_x));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_CROP_END_X_L_REG,
			   OV5648_CROP_END_X_L(mode->crop_end_x));
	अगर (ret)
		वापस ret;

	/* Horizontal Total Size */

	ret = ov5648_ग_लिखो(sensor, OV5648_HTS_H_REG, OV5648_HTS_H(mode->hts));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_HTS_L_REG, OV5648_HTS_L(mode->hts));
	अगर (ret)
		वापस ret;

	/* Crop Start Y */

	ret = ov5648_ग_लिखो(sensor, OV5648_CROP_START_Y_H_REG,
			   OV5648_CROP_START_Y_H(mode->crop_start_y));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_CROP_START_Y_L_REG,
			   OV5648_CROP_START_Y_L(mode->crop_start_y));
	अगर (ret)
		वापस ret;

	/* Offset Y */

	ret = ov5648_ग_लिखो(sensor, OV5648_OFFSET_Y_H_REG,
			   OV5648_OFFSET_Y_H(mode->offset_y));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_OFFSET_Y_L_REG,
			   OV5648_OFFSET_Y_L(mode->offset_y));
	अगर (ret)
		वापस ret;

	/* Output Size Y */

	ret = ov5648_ग_लिखो(sensor, OV5648_OUTPUT_SIZE_Y_H_REG,
			   OV5648_OUTPUT_SIZE_Y_H(mode->output_size_y));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_OUTPUT_SIZE_Y_L_REG,
			   OV5648_OUTPUT_SIZE_Y_L(mode->output_size_y));
	अगर (ret)
		वापस ret;

	/* Crop End Y */

	ret = ov5648_ग_लिखो(sensor, OV5648_CROP_END_Y_H_REG,
			   OV5648_CROP_END_Y_H(mode->crop_end_y));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_CROP_END_Y_L_REG,
			   OV5648_CROP_END_Y_L(mode->crop_end_y));
	अगर (ret)
		वापस ret;

	/* Vertical Total Size */

	ret = ov5648_ग_लिखो(sensor, OV5648_VTS_H_REG, OV5648_VTS_H(mode->vts));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_VTS_L_REG, OV5648_VTS_L(mode->vts));
	अगर (ret)
		वापस ret;

	/* Flip/Mirror/Binning */

	/*
	 * A debug bit is enabled by शेष and needs to be cleared क्रम
	 * subsampling to work.
	 */
	ret = ov5648_update_bits(sensor, OV5648_TC20_REG,
				 OV5648_TC20_DEBUG |
				 OV5648_TC20_BINNING_VERT_EN,
				 mode->binning_y ? OV5648_TC20_BINNING_VERT_EN :
				 0);
	अगर (ret)
		वापस ret;

	ret = ov5648_update_bits(sensor, OV5648_TC21_REG,
				 OV5648_TC21_BINNING_HORZ_EN,
				 mode->binning_x ? OV5648_TC21_BINNING_HORZ_EN :
				 0);
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_SUB_INC_X_REG,
			   OV5648_SUB_INC_X_ODD(mode->inc_x_odd) |
			   OV5648_SUB_INC_X_EVEN(mode->inc_x_even));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_SUB_INC_Y_REG,
			   OV5648_SUB_INC_Y_ODD(mode->inc_y_odd) |
			   OV5648_SUB_INC_Y_EVEN(mode->inc_y_even));
	अगर (ret)
		वापस ret;

	/* PLLs */

	ret = ov5648_mode_pll1_configure(sensor, mode, mbus_code);
	अगर (ret)
		वापस ret;

	ret = ov5648_mode_pll2_configure(sensor, mode);
	अगर (ret)
		वापस ret;

	/* Extra रेजिस्टरs */

	अगर (mode->रेजिस्टर_values) अणु
		ret = ov5648_ग_लिखो_sequence(sensor, mode->रेजिस्टर_values,
					    mode->रेजिस्टर_values_count);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ ov5648_mode_mipi_clk_rate(काष्ठा ov5648_sensor *sensor,
					       स्थिर काष्ठा ov5648_mode *mode,
					       u32 mbus_code)
अणु
	स्थिर काष्ठा ov5648_pll1_config *config;
	अचिन्हित दीर्घ pll1_rate;

	चयन (mbus_code) अणु
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		config = mode->pll1_config[0];
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
		config = mode->pll1_config[1];
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	pll1_rate = ov5648_mode_pll1_rate(sensor, config);

	वापस pll1_rate / config->sys_भाग / config->mipi_भाग / 2;
पूर्ण

/* Exposure */

अटल पूर्णांक ov5648_exposure_स्वतः_configure(काष्ठा ov5648_sensor *sensor,
					  bool enable)
अणु
	वापस ov5648_update_bits(sensor, OV5648_MANUAL_CTRL_REG,
				  OV5648_MANUAL_CTRL_AEC_MANUAL_EN,
				  enable ? 0 : OV5648_MANUAL_CTRL_AEC_MANUAL_EN);
पूर्ण

अटल पूर्णांक ov5648_exposure_configure(काष्ठा ov5648_sensor *sensor, u32 exposure)
अणु
	काष्ठा ov5648_ctrls *ctrls = &sensor->ctrls;
	पूर्णांक ret;

	अगर (ctrls->exposure_स्वतः->val != V4L2_EXPOSURE_MANUAL)
		वापस -EINVAL;

	ret = ov5648_ग_लिखो(sensor, OV5648_EXPOSURE_CTRL_HH_REG,
			   OV5648_EXPOSURE_CTRL_HH(exposure));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_EXPOSURE_CTRL_H_REG,
			   OV5648_EXPOSURE_CTRL_H(exposure));
	अगर (ret)
		वापस ret;

	वापस ov5648_ग_लिखो(sensor, OV5648_EXPOSURE_CTRL_L_REG,
			    OV5648_EXPOSURE_CTRL_L(exposure));
पूर्ण

अटल पूर्णांक ov5648_exposure_value(काष्ठा ov5648_sensor *sensor,
				 u32 *exposure)
अणु
	u8 exposure_hh = 0, exposure_h = 0, exposure_l = 0;
	पूर्णांक ret;

	ret = ov5648_पढ़ो(sensor, OV5648_EXPOSURE_CTRL_HH_REG, &exposure_hh);
	अगर (ret)
		वापस ret;

	ret = ov5648_पढ़ो(sensor, OV5648_EXPOSURE_CTRL_H_REG, &exposure_h);
	अगर (ret)
		वापस ret;

	ret = ov5648_पढ़ो(sensor, OV5648_EXPOSURE_CTRL_L_REG, &exposure_l);
	अगर (ret)
		वापस ret;

	*exposure = OV5648_EXPOSURE_CTRL_HH_VALUE((u32)exposure_hh) |
		    OV5648_EXPOSURE_CTRL_H_VALUE((u32)exposure_h) |
		    OV5648_EXPOSURE_CTRL_L_VALUE((u32)exposure_l);

	वापस 0;
पूर्ण

/* Gain */

अटल पूर्णांक ov5648_gain_स्वतः_configure(काष्ठा ov5648_sensor *sensor, bool enable)
अणु
	वापस ov5648_update_bits(sensor, OV5648_MANUAL_CTRL_REG,
				  OV5648_MANUAL_CTRL_AGC_MANUAL_EN,
				  enable ? 0 : OV5648_MANUAL_CTRL_AGC_MANUAL_EN);
पूर्ण

अटल पूर्णांक ov5648_gain_configure(काष्ठा ov5648_sensor *sensor, u32 gain)
अणु
	काष्ठा ov5648_ctrls *ctrls = &sensor->ctrls;
	पूर्णांक ret;

	अगर (ctrls->gain_स्वतः->val)
		वापस -EINVAL;

	ret = ov5648_ग_लिखो(sensor, OV5648_GAIN_CTRL_H_REG,
			   OV5648_GAIN_CTRL_H(gain));
	अगर (ret)
		वापस ret;

	वापस ov5648_ग_लिखो(sensor, OV5648_GAIN_CTRL_L_REG,
			    OV5648_GAIN_CTRL_L(gain));
पूर्ण

अटल पूर्णांक ov5648_gain_value(काष्ठा ov5648_sensor *sensor, u32 *gain)
अणु
	u8 gain_h = 0, gain_l = 0;
	पूर्णांक ret;

	ret = ov5648_पढ़ो(sensor, OV5648_GAIN_CTRL_H_REG, &gain_h);
	अगर (ret)
		वापस ret;

	ret = ov5648_पढ़ो(sensor, OV5648_GAIN_CTRL_L_REG, &gain_l);
	अगर (ret)
		वापस ret;

	*gain = OV5648_GAIN_CTRL_H_VALUE((u32)gain_h) |
		OV5648_GAIN_CTRL_L_VALUE((u32)gain_l);

	वापस 0;
पूर्ण

/* White Balance */

अटल पूर्णांक ov5648_white_balance_स्वतः_configure(काष्ठा ov5648_sensor *sensor,
					       bool enable)
अणु
	वापस ov5648_ग_लिखो(sensor, OV5648_AWB_CTRL_REG,
			    enable ? 0 : OV5648_AWB_CTRL_GAIN_MANUAL_EN);
पूर्ण

अटल पूर्णांक ov5648_white_balance_configure(काष्ठा ov5648_sensor *sensor,
					  u32 red_balance, u32 blue_balance)
अणु
	काष्ठा ov5648_ctrls *ctrls = &sensor->ctrls;
	पूर्णांक ret;

	अगर (ctrls->white_balance_स्वतः->val)
		वापस -EINVAL;

	ret = ov5648_ग_लिखो(sensor, OV5648_GAIN_RED_MAN_H_REG,
			   OV5648_GAIN_RED_MAN_H(red_balance));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_GAIN_RED_MAN_L_REG,
			   OV5648_GAIN_RED_MAN_L(red_balance));
	अगर (ret)
		वापस ret;

	ret = ov5648_ग_लिखो(sensor, OV5648_GAIN_BLUE_MAN_H_REG,
			   OV5648_GAIN_BLUE_MAN_H(blue_balance));
	अगर (ret)
		वापस ret;

	वापस ov5648_ग_लिखो(sensor, OV5648_GAIN_BLUE_MAN_L_REG,
			    OV5648_GAIN_BLUE_MAN_L(blue_balance));
पूर्ण

/* Flip */

अटल पूर्णांक ov5648_flip_vert_configure(काष्ठा ov5648_sensor *sensor, bool enable)
अणु
	u8 bits = OV5648_TC20_FLIP_VERT_ISP_EN |
		  OV5648_TC20_FLIP_VERT_SENSOR_EN;

	वापस ov5648_update_bits(sensor, OV5648_TC20_REG, bits,
				  enable ? bits : 0);
पूर्ण

अटल पूर्णांक ov5648_flip_horz_configure(काष्ठा ov5648_sensor *sensor, bool enable)
अणु
	u8 bits = OV5648_TC21_FLIP_HORZ_ISP_EN |
		  OV5648_TC21_FLIP_HORZ_SENSOR_EN;

	वापस ov5648_update_bits(sensor, OV5648_TC21_REG, bits,
				  enable ? bits : 0);
पूर्ण

/* Test Pattern */

अटल पूर्णांक ov5648_test_pattern_configure(काष्ठा ov5648_sensor *sensor,
					 अचिन्हित पूर्णांक index)
अणु
	अगर (index >= ARRAY_SIZE(ov5648_test_pattern_bits))
		वापस -EINVAL;

	वापस ov5648_ग_लिखो(sensor, OV5648_ISP_CTRL3D_REG,
			    ov5648_test_pattern_bits[index]);
पूर्ण

/* State */

अटल पूर्णांक ov5648_state_mipi_configure(काष्ठा ov5648_sensor *sensor,
				       स्थिर काष्ठा ov5648_mode *mode,
				       u32 mbus_code)
अणु
	काष्ठा ov5648_ctrls *ctrls = &sensor->ctrls;
	काष्ठा v4l2_fwnode_bus_mipi_csi2 *bus_mipi_csi2 =
		&sensor->endpoपूर्णांक.bus.mipi_csi2;
	अचिन्हित दीर्घ mipi_clk_rate;
	अचिन्हित पूर्णांक bits_per_sample;
	अचिन्हित पूर्णांक lanes_count;
	अचिन्हित पूर्णांक i, j;
	s64 mipi_pixel_rate;

	mipi_clk_rate = ov5648_mode_mipi_clk_rate(sensor, mode, mbus_code);
	अगर (!mipi_clk_rate)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(ov5648_link_freq_menu); i++) अणु
		s64 freq = ov5648_link_freq_menu[i];

		अगर (freq == mipi_clk_rate)
			अवरोध;
	पूर्ण

	क्रम (j = 0; j < sensor->endpoपूर्णांक.nr_of_link_frequencies; j++) अणु
		u64 freq = sensor->endpoपूर्णांक.link_frequencies[j];

		अगर (freq == mipi_clk_rate)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(ov5648_link_freq_menu)) अणु
		dev_err(sensor->dev,
			"failed to find %lu clk rate in link freq\n",
			mipi_clk_rate);
	पूर्ण अन्यथा अगर (j == sensor->endpoपूर्णांक.nr_of_link_frequencies) अणु
		dev_err(sensor->dev,
			"failed to find %lu clk rate in endpoint link-frequencies\n",
			mipi_clk_rate);
	पूर्ण अन्यथा अणु
		__v4l2_ctrl_s_ctrl(ctrls->link_freq, i);
	पूर्ण

	चयन (mbus_code) अणु
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		bits_per_sample = 8;
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
		bits_per_sample = 10;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	lanes_count = bus_mipi_csi2->num_data_lanes;
	mipi_pixel_rate = mipi_clk_rate * 2 * lanes_count / bits_per_sample;

	__v4l2_ctrl_s_ctrl_पूर्णांक64(ctrls->pixel_rate, mipi_pixel_rate);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5648_state_configure(काष्ठा ov5648_sensor *sensor,
				  स्थिर काष्ठा ov5648_mode *mode,
				  u32 mbus_code)
अणु
	पूर्णांक ret;

	अगर (sensor->state.streaming)
		वापस -EBUSY;

	/* State will be configured at first घातer on otherwise. */
	अगर (pm_runसमय_enabled(sensor->dev) &&
	    !pm_runसमय_suspended(sensor->dev)) अणु
		ret = ov5648_mode_configure(sensor, mode, mbus_code);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = ov5648_state_mipi_configure(sensor, mode, mbus_code);
	अगर (ret)
		वापस ret;

	sensor->state.mode = mode;
	sensor->state.mbus_code = mbus_code;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5648_state_init(काष्ठा ov5648_sensor *sensor)
अणु
	वापस ov5648_state_configure(sensor, &ov5648_modes[0],
				      ov5648_mbus_codes[0]);
पूर्ण

/* Sensor Base */

अटल पूर्णांक ov5648_sensor_init(काष्ठा ov5648_sensor *sensor)
अणु
	पूर्णांक ret;

	ret = ov5648_sw_reset(sensor);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to perform sw reset\n");
		वापस ret;
	पूर्ण

	ret = ov5648_sw_standby(sensor, 1);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to set sensor standby\n");
		वापस ret;
	पूर्ण

	ret = ov5648_chip_id_check(sensor);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to check sensor chip id\n");
		वापस ret;
	पूर्ण

	ret = ov5648_avdd_पूर्णांकernal_घातer(sensor, !sensor->avdd);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to set internal avdd power\n");
		वापस ret;
	पूर्ण

	ret = ov5648_ग_लिखो_sequence(sensor, ov5648_init_sequence,
				    ARRAY_SIZE(ov5648_init_sequence));
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to write init sequence\n");
		वापस ret;
	पूर्ण

	ret = ov5648_pad_configure(sensor);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to configure pad\n");
		वापस ret;
	पूर्ण

	ret = ov5648_mipi_configure(sensor);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to configure MIPI\n");
		वापस ret;
	पूर्ण

	ret = ov5648_isp_configure(sensor);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to configure ISP\n");
		वापस ret;
	पूर्ण

	ret = ov5648_black_level_configure(sensor);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to configure black level\n");
		वापस ret;
	पूर्ण

	/* Configure current mode. */
	ret = ov5648_state_configure(sensor, sensor->state.mode,
				     sensor->state.mbus_code);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to configure state\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5648_sensor_घातer(काष्ठा ov5648_sensor *sensor, bool on)
अणु
	/* Keep initialized to zero क्रम disable label. */
	पूर्णांक ret = 0;

	/*
	 * General notes about the घातer sequence:
	 * - घातer-करोwn GPIO must be active (low) during घातer-on;
	 * - reset GPIO state करोes not matter during घातer-on;
	 * - XVCLK must be provided 1 ms beक्रमe रेजिस्टर access;
	 * - 10 ms are needed between घातer-करोwn deनिश्चित and रेजिस्टर access.
	 */

	/* Note that regulator-and-GPIO-based घातer is untested. */
	अगर (on) अणु
		gpiod_set_value_cansleep(sensor->reset, 1);
		gpiod_set_value_cansleep(sensor->घातerकरोwn, 1);

		ret = regulator_enable(sensor->करोvdd);
		अगर (ret) अणु
			dev_err(sensor->dev,
				"failed to enable DOVDD regulator\n");
			जाओ disable;
		पूर्ण

		अगर (sensor->avdd) अणु
			ret = regulator_enable(sensor->avdd);
			अगर (ret) अणु
				dev_err(sensor->dev,
					"failed to enable AVDD regulator\n");
				जाओ disable;
			पूर्ण
		पूर्ण

		ret = regulator_enable(sensor->dvdd);
		अगर (ret) अणु
			dev_err(sensor->dev,
				"failed to enable DVDD regulator\n");
			जाओ disable;
		पूर्ण

		/* According to OV5648 घातer up diagram. */
		usleep_range(5000, 10000);

		ret = clk_prepare_enable(sensor->xvclk);
		अगर (ret) अणु
			dev_err(sensor->dev, "failed to enable XVCLK clock\n");
			जाओ disable;
		पूर्ण

		gpiod_set_value_cansleep(sensor->reset, 0);
		gpiod_set_value_cansleep(sensor->घातerकरोwn, 0);

		usleep_range(20000, 25000);
	पूर्ण अन्यथा अणु
disable:
		gpiod_set_value_cansleep(sensor->घातerकरोwn, 1);
		gpiod_set_value_cansleep(sensor->reset, 1);

		clk_disable_unprepare(sensor->xvclk);

		regulator_disable(sensor->dvdd);

		अगर (sensor->avdd)
			regulator_disable(sensor->avdd);

		regulator_disable(sensor->करोvdd);
	पूर्ण

	वापस ret;
पूर्ण

/* Controls */

अटल पूर्णांक ov5648_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *subdev = ov5648_ctrl_subdev(ctrl);
	काष्ठा ov5648_sensor *sensor = ov5648_subdev_sensor(subdev);
	काष्ठा ov5648_ctrls *ctrls = &sensor->ctrls;
	पूर्णांक ret;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE_AUTO:
		ret = ov5648_exposure_value(sensor, &ctrls->exposure->val);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		ret = ov5648_gain_value(sensor, &ctrls->gain->val);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5648_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *subdev = ov5648_ctrl_subdev(ctrl);
	काष्ठा ov5648_sensor *sensor = ov5648_subdev_sensor(subdev);
	काष्ठा ov5648_ctrls *ctrls = &sensor->ctrls;
	अचिन्हित पूर्णांक index;
	bool enable;
	पूर्णांक ret;

	/* Wait क्रम the sensor to be on beक्रमe setting controls. */
	अगर (pm_runसमय_suspended(sensor->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE_AUTO:
		enable = ctrl->val == V4L2_EXPOSURE_AUTO;

		ret = ov5648_exposure_स्वतः_configure(sensor, enable);
		अगर (ret)
			वापस ret;

		अगर (!enable && ctrls->exposure->is_new) अणु
			ret = ov5648_exposure_configure(sensor,
							ctrls->exposure->val);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		enable = !!ctrl->val;

		ret = ov5648_gain_स्वतः_configure(sensor, enable);
		अगर (ret)
			वापस ret;

		अगर (!enable) अणु
			ret = ov5648_gain_configure(sensor, ctrls->gain->val);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		enable = !!ctrl->val;

		ret = ov5648_white_balance_स्वतः_configure(sensor, enable);
		अगर (ret)
			वापस ret;

		अगर (!enable) अणु
			ret = ov5648_white_balance_configure(sensor,
							     ctrls->red_balance->val,
							     ctrls->blue_balance->val);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;
	हाल V4L2_CID_HFLIP:
		enable = !!ctrl->val;
		वापस ov5648_flip_horz_configure(sensor, enable);
	हाल V4L2_CID_VFLIP:
		enable = !!ctrl->val;
		वापस ov5648_flip_vert_configure(sensor, enable);
	हाल V4L2_CID_TEST_PATTERN:
		index = (अचिन्हित पूर्णांक)ctrl->val;
		वापस ov5648_test_pattern_configure(sensor, index);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov5648_ctrl_ops = अणु
	.g_अस्थिर_ctrl	= ov5648_g_अस्थिर_ctrl,
	.s_ctrl			= ov5648_s_ctrl,
पूर्ण;

अटल पूर्णांक ov5648_ctrls_init(काष्ठा ov5648_sensor *sensor)
अणु
	काष्ठा ov5648_ctrls *ctrls = &sensor->ctrls;
	काष्ठा v4l2_ctrl_handler *handler = &ctrls->handler;
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &ov5648_ctrl_ops;
	पूर्णांक ret;

	v4l2_ctrl_handler_init(handler, 32);

	/* Use our mutex क्रम ctrl locking. */
	handler->lock = &sensor->mutex;

	/* Exposure */

	ctrls->exposure_स्वतः = v4l2_ctrl_new_std_menu(handler, ops,
						      V4L2_CID_EXPOSURE_AUTO,
						      V4L2_EXPOSURE_MANUAL, 0,
						      V4L2_EXPOSURE_AUTO);

	ctrls->exposure = v4l2_ctrl_new_std(handler, ops, V4L2_CID_EXPOSURE,
					    16, 1048575, 16, 512);

	v4l2_ctrl_स्वतः_cluster(2, &ctrls->exposure_स्वतः, 1, true);

	/* Gain */

	ctrls->gain_स्वतः =
		v4l2_ctrl_new_std(handler, ops, V4L2_CID_AUTOGAIN, 0, 1, 1, 1);

	ctrls->gain = v4l2_ctrl_new_std(handler, ops, V4L2_CID_GAIN, 16, 1023,
					16, 16);

	v4l2_ctrl_स्वतः_cluster(2, &ctrls->gain_स्वतः, 0, true);

	/* White Balance */

	ctrls->white_balance_स्वतः =
		v4l2_ctrl_new_std(handler, ops, V4L2_CID_AUTO_WHITE_BALANCE, 0,
				  1, 1, 1);

	ctrls->red_balance = v4l2_ctrl_new_std(handler, ops,
					       V4L2_CID_RED_BALANCE, 0, 4095,
					       1, 1024);

	ctrls->blue_balance = v4l2_ctrl_new_std(handler, ops,
						V4L2_CID_BLUE_BALANCE, 0, 4095,
						1, 1024);

	v4l2_ctrl_स्वतः_cluster(3, &ctrls->white_balance_स्वतः, 0, false);

	/* Flip */

	v4l2_ctrl_new_std(handler, ops, V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(handler, ops, V4L2_CID_VFLIP, 0, 1, 1, 0);

	/* Test Pattern */

	v4l2_ctrl_new_std_menu_items(handler, ops, V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(ov5648_test_pattern_menu) - 1,
				     0, 0, ov5648_test_pattern_menu);

	/* MIPI CSI-2 */

	ctrls->link_freq =
		v4l2_ctrl_new_पूर्णांक_menu(handler, शून्य, V4L2_CID_LINK_FREQ,
				       ARRAY_SIZE(ov5648_link_freq_menu) - 1,
				       0, ov5648_link_freq_menu);

	ctrls->pixel_rate =
		v4l2_ctrl_new_std(handler, शून्य, V4L2_CID_PIXEL_RATE, 1,
				  पूर्णांक_उच्च, 1, 1);

	अगर (handler->error) अणु
		ret = handler->error;
		जाओ error_ctrls;
	पूर्ण

	ctrls->exposure->flags |= V4L2_CTRL_FLAG_VOLATILE;
	ctrls->gain->flags |= V4L2_CTRL_FLAG_VOLATILE;

	ctrls->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;
	ctrls->pixel_rate->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	sensor->subdev.ctrl_handler = handler;

	वापस 0;

error_ctrls:
	v4l2_ctrl_handler_मुक्त(handler);

	वापस ret;
पूर्ण

/* Subdev Video Operations */

अटल पूर्णांक ov5648_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	काष्ठा ov5648_sensor *sensor = ov5648_subdev_sensor(subdev);
	काष्ठा ov5648_state *state = &sensor->state;
	पूर्णांक ret;

	अगर (enable) अणु
		ret = pm_runसमय_get_sync(sensor->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(sensor->dev);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_lock(&sensor->mutex);
	ret = ov5648_sw_standby(sensor, !enable);
	mutex_unlock(&sensor->mutex);

	अगर (ret)
		वापस ret;

	state->streaming = !!enable;

	अगर (!enable)
		pm_runसमय_put(sensor->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5648_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *पूर्णांकerval)
अणु
	काष्ठा ov5648_sensor *sensor = ov5648_subdev_sensor(subdev);
	स्थिर काष्ठा ov5648_mode *mode;
	पूर्णांक ret = 0;

	mutex_lock(&sensor->mutex);

	mode = sensor->state.mode;

	चयन (sensor->state.mbus_code) अणु
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		पूर्णांकerval->पूर्णांकerval = mode->frame_पूर्णांकerval[0];
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
		पूर्णांकerval->पूर्णांकerval = mode->frame_पूर्णांकerval[1];
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&sensor->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov5648_subdev_video_ops = अणु
	.s_stream		= ov5648_s_stream,
	.g_frame_पूर्णांकerval	= ov5648_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval	= ov5648_g_frame_पूर्णांकerval,
पूर्ण;

/* Subdev Pad Operations */

अटल पूर्णांक ov5648_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *config,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code_क्रमागत)
अणु
	अगर (code_क्रमागत->index >= ARRAY_SIZE(ov5648_mbus_codes))
		वापस -EINVAL;

	code_क्रमागत->code = ov5648_mbus_codes[code_क्रमागत->index];

	वापस 0;
पूर्ण

अटल व्योम ov5648_mbus_क्रमmat_fill(काष्ठा v4l2_mbus_framefmt *mbus_क्रमmat,
				    u32 mbus_code,
				    स्थिर काष्ठा ov5648_mode *mode)
अणु
	mbus_क्रमmat->width = mode->output_size_x;
	mbus_क्रमmat->height = mode->output_size_y;
	mbus_क्रमmat->code = mbus_code;

	mbus_क्रमmat->field = V4L2_FIELD_NONE;
	mbus_क्रमmat->colorspace = V4L2_COLORSPACE_RAW;
	mbus_क्रमmat->ycbcr_enc =
		V4L2_MAP_YCBCR_ENC_DEFAULT(mbus_क्रमmat->colorspace);
	mbus_क्रमmat->quantization = V4L2_QUANTIZATION_FULL_RANGE;
	mbus_क्रमmat->xfer_func =
		V4L2_MAP_XFER_FUNC_DEFAULT(mbus_क्रमmat->colorspace);
पूर्ण

अटल पूर्णांक ov5648_get_fmt(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *config,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov5648_sensor *sensor = ov5648_subdev_sensor(subdev);
	काष्ठा v4l2_mbus_framefmt *mbus_क्रमmat = &क्रमmat->क्रमmat;

	mutex_lock(&sensor->mutex);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		*mbus_क्रमmat = *v4l2_subdev_get_try_क्रमmat(subdev, config,
							   क्रमmat->pad);
	अन्यथा
		ov5648_mbus_क्रमmat_fill(mbus_क्रमmat, sensor->state.mbus_code,
					sensor->state.mode);

	mutex_unlock(&sensor->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5648_set_fmt(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *config,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov5648_sensor *sensor = ov5648_subdev_sensor(subdev);
	काष्ठा v4l2_mbus_framefmt *mbus_क्रमmat = &क्रमmat->क्रमmat;
	स्थिर काष्ठा ov5648_mode *mode;
	u32 mbus_code = 0;
	अचिन्हित पूर्णांक index;
	पूर्णांक ret = 0;

	mutex_lock(&sensor->mutex);

	अगर (sensor->state.streaming) अणु
		ret = -EBUSY;
		जाओ complete;
	पूर्ण

	/* Try to find requested mbus code. */
	क्रम (index = 0; index < ARRAY_SIZE(ov5648_mbus_codes); index++) अणु
		अगर (ov5648_mbus_codes[index] == mbus_क्रमmat->code) अणु
			mbus_code = mbus_क्रमmat->code;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Fallback to शेष. */
	अगर (!mbus_code)
		mbus_code = ov5648_mbus_codes[0];

	/* Find the mode with nearest dimensions. */
	mode = v4l2_find_nearest_size(ov5648_modes, ARRAY_SIZE(ov5648_modes),
				      output_size_x, output_size_y,
				      mbus_क्रमmat->width, mbus_क्रमmat->height);
	अगर (!mode) अणु
		ret = -EINVAL;
		जाओ complete;
	पूर्ण

	ov5648_mbus_क्रमmat_fill(mbus_क्रमmat, mbus_code, mode);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		*v4l2_subdev_get_try_क्रमmat(subdev, config, क्रमmat->pad) =
			*mbus_क्रमmat;
	अन्यथा अगर (sensor->state.mode != mode ||
		 sensor->state.mbus_code != mbus_code)
		ret = ov5648_state_configure(sensor, mode, mbus_code);

complete:
	mutex_unlock(&sensor->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5648_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *config,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *size_क्रमागत)
अणु
	स्थिर काष्ठा ov5648_mode *mode;

	अगर (size_क्रमागत->index >= ARRAY_SIZE(ov5648_modes))
		वापस -EINVAL;

	mode = &ov5648_modes[size_क्रमागत->index];

	size_क्रमागत->min_width = size_क्रमागत->max_width = mode->output_size_x;
	size_क्रमागत->min_height = size_क्रमागत->max_height = mode->output_size_y;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5648_क्रमागत_frame_पूर्णांकerval(काष्ठा v4l2_subdev *subdev,
				      काष्ठा v4l2_subdev_pad_config *config,
				      काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *पूर्णांकerval_क्रमागत)
अणु
	स्थिर काष्ठा ov5648_mode *mode = शून्य;
	अचिन्हित पूर्णांक mode_index;
	अचिन्हित पूर्णांक पूर्णांकerval_index;

	अगर (पूर्णांकerval_क्रमागत->index > 0)
		वापस -EINVAL;

	/*
	 * Multiple modes with the same dimensions may have dअगरferent frame
	 * पूर्णांकervals, so look up each relevant mode.
	 */
	क्रम (mode_index = 0, पूर्णांकerval_index = 0;
	     mode_index < ARRAY_SIZE(ov5648_modes); mode_index++) अणु
		mode = &ov5648_modes[mode_index];

		अगर (mode->output_size_x == पूर्णांकerval_क्रमागत->width &&
		    mode->output_size_y == पूर्णांकerval_क्रमागत->height) अणु
			अगर (पूर्णांकerval_index == पूर्णांकerval_क्रमागत->index)
				अवरोध;

			पूर्णांकerval_index++;
		पूर्ण
	पूर्ण

	अगर (mode_index == ARRAY_SIZE(ov5648_modes))
		वापस -EINVAL;

	चयन (पूर्णांकerval_क्रमागत->code) अणु
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		पूर्णांकerval_क्रमागत->पूर्णांकerval = mode->frame_पूर्णांकerval[0];
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
		पूर्णांकerval_क्रमागत->पूर्णांकerval = mode->frame_पूर्णांकerval[1];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov5648_subdev_pad_ops = अणु
	.क्रमागत_mbus_code		= ov5648_क्रमागत_mbus_code,
	.get_fmt		= ov5648_get_fmt,
	.set_fmt		= ov5648_set_fmt,
	.क्रमागत_frame_size	= ov5648_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval	= ov5648_क्रमागत_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov5648_subdev_ops = अणु
	.video		= &ov5648_subdev_video_ops,
	.pad		= &ov5648_subdev_pad_ops,
पूर्ण;

अटल पूर्णांक ov5648_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा ov5648_sensor *sensor = ov5648_subdev_sensor(subdev);
	काष्ठा ov5648_state *state = &sensor->state;
	पूर्णांक ret = 0;

	mutex_lock(&sensor->mutex);

	अगर (state->streaming) अणु
		ret = ov5648_sw_standby(sensor, true);
		अगर (ret)
			जाओ complete;
	पूर्ण

	ret = ov5648_sensor_घातer(sensor, false);
	अगर (ret)
		ov5648_sw_standby(sensor, false);

complete:
	mutex_unlock(&sensor->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5648_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा ov5648_sensor *sensor = ov5648_subdev_sensor(subdev);
	काष्ठा ov5648_state *state = &sensor->state;
	पूर्णांक ret = 0;

	mutex_lock(&sensor->mutex);

	ret = ov5648_sensor_घातer(sensor, true);
	अगर (ret)
		जाओ complete;

	ret = ov5648_sensor_init(sensor);
	अगर (ret)
		जाओ error_घातer;

	ret = __v4l2_ctrl_handler_setup(&sensor->ctrls.handler);
	अगर (ret)
		जाओ error_घातer;

	अगर (state->streaming) अणु
		ret = ov5648_sw_standby(sensor, false);
		अगर (ret)
			जाओ error_घातer;
	पूर्ण

	जाओ complete;

error_घातer:
	ov5648_sensor_घातer(sensor, false);

complete:
	mutex_unlock(&sensor->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5648_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा fwnode_handle *handle;
	काष्ठा ov5648_sensor *sensor;
	काष्ठा v4l2_subdev *subdev;
	काष्ठा media_pad *pad;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	sensor = devm_kzalloc(dev, माप(*sensor), GFP_KERNEL);
	अगर (!sensor)
		वापस -ENOMEM;

	sensor->dev = dev;
	sensor->i2c_client = client;

	/* Graph Endpoपूर्णांक */

	handle = fwnode_graph_get_next_endpoपूर्णांक(dev_fwnode(dev), शून्य);
	अगर (!handle) अणु
		dev_err(dev, "unable to find endpoint node\n");
		वापस -EINVAL;
	पूर्ण

	sensor->endpoपूर्णांक.bus_type = V4L2_MBUS_CSI2_DPHY;

	ret = v4l2_fwnode_endpoपूर्णांक_alloc_parse(handle, &sensor->endpoपूर्णांक);
	fwnode_handle_put(handle);
	अगर (ret) अणु
		dev_err(dev, "failed to parse endpoint node\n");
		वापस ret;
	पूर्ण

	/* GPIOs */

	sensor->घातerकरोwn = devm_gpiod_get_optional(dev, "powerdown",
						    GPIOD_OUT_HIGH);
	अगर (IS_ERR(sensor->घातerकरोwn)) अणु
		ret = PTR_ERR(sensor->घातerकरोwn);
		जाओ error_endpoपूर्णांक;
	पूर्ण

	sensor->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(sensor->reset)) अणु
		ret = PTR_ERR(sensor->reset);
		जाओ error_endpoपूर्णांक;
	पूर्ण

	/* Regulators */

	/* DVDD: digital core */
	sensor->dvdd = devm_regulator_get(dev, "dvdd");
	अगर (IS_ERR(sensor->dvdd)) अणु
		dev_err(dev, "cannot get DVDD (digital core) regulator\n");
		ret = PTR_ERR(sensor->dvdd);
		जाओ error_endpoपूर्णांक;
	पूर्ण

	/* DOVDD: digital I/O */
	sensor->करोvdd = devm_regulator_get(dev, "dovdd");
	अगर (IS_ERR(sensor->dvdd)) अणु
		dev_err(dev, "cannot get DOVDD (digital I/O) regulator\n");
		ret = PTR_ERR(sensor->dvdd);
		जाओ error_endpoपूर्णांक;
	पूर्ण

	/* AVDD: analog */
	sensor->avdd = devm_regulator_get_optional(dev, "avdd");
	अगर (IS_ERR(sensor->avdd)) अणु
		dev_info(dev, "no AVDD regulator provided, using internal\n");
		sensor->avdd = शून्य;
	पूर्ण

	/* External Clock */

	sensor->xvclk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(sensor->xvclk)) अणु
		dev_err(dev, "failed to get external clock\n");
		ret = PTR_ERR(sensor->xvclk);
		जाओ error_endpoपूर्णांक;
	पूर्ण

	rate = clk_get_rate(sensor->xvclk);
	अगर (rate != OV5648_XVCLK_RATE) अणु
		dev_err(dev, "clock rate %lu Hz is unsupported\n", rate);
		ret = -EINVAL;
		जाओ error_endpoपूर्णांक;
	पूर्ण

	/* Subdev, entity and pad */

	subdev = &sensor->subdev;
	v4l2_i2c_subdev_init(subdev, client, &ov5648_subdev_ops);

	subdev->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	subdev->entity.function = MEDIA_ENT_F_CAM_SENSOR;

	pad = &sensor->pad;
	pad->flags = MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&subdev->entity, 1, pad);
	अगर (ret)
		जाओ error_entity;

	/* Mutex */

	mutex_init(&sensor->mutex);

	/* Sensor */

	ret = ov5648_ctrls_init(sensor);
	अगर (ret)
		जाओ error_mutex;

	ret = ov5648_state_init(sensor);
	अगर (ret)
		जाओ error_ctrls;

	/* Runसमय PM */

	pm_runसमय_enable(sensor->dev);
	pm_runसमय_set_suspended(sensor->dev);

	/* V4L2 subdev रेजिस्टर */

	ret = v4l2_async_रेजिस्टर_subdev_sensor(subdev);
	अगर (ret)
		जाओ error_pm;

	वापस 0;

error_pm:
	pm_runसमय_disable(sensor->dev);

error_ctrls:
	v4l2_ctrl_handler_मुक्त(&sensor->ctrls.handler);

error_mutex:
	mutex_destroy(&sensor->mutex);

error_entity:
	media_entity_cleanup(&sensor->subdev.entity);

error_endpoपूर्णांक:
	v4l2_fwnode_endpoपूर्णांक_मुक्त(&sensor->endpoपूर्णांक);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5648_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा ov5648_sensor *sensor = ov5648_subdev_sensor(subdev);

	v4l2_async_unरेजिस्टर_subdev(subdev);
	pm_runसमय_disable(sensor->dev);
	v4l2_ctrl_handler_मुक्त(&sensor->ctrls.handler);
	mutex_destroy(&sensor->mutex);
	media_entity_cleanup(&subdev->entity);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ov5648_pm_ops = अणु
	SET_RUNTIME_PM_OPS(ov5648_suspend, ov5648_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id ov5648_of_match[] = अणु
	अणु .compatible = "ovti,ov5648" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ov5648_of_match);

अटल काष्ठा i2c_driver ov5648_driver = अणु
	.driver = अणु
		.name = "ov5648",
		.of_match_table = ov5648_of_match,
		.pm = &ov5648_pm_ops,
	पूर्ण,
	.probe_new = ov5648_probe,
	.हटाओ	 = ov5648_हटाओ,
पूर्ण;

module_i2c_driver(ov5648_driver);

MODULE_AUTHOR("Paul Kocialkowski <paul.kocialkowski@bootlin.com>");
MODULE_DESCRIPTION("V4L2 driver for the OmniVision OV5648 image sensor");
MODULE_LICENSE("GPL v2");
