<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2020 Kथऊvin L'hथखpital <kevin.lhopital@bootlin.com>
 * Copyright 2020 Bootlin
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

#घोषणा OV8865_EXTCLK_RATE			24000000

/* Register definitions */

/* System */

#घोषणा OV8865_SW_STANDBY_REG			0x100
#घोषणा OV8865_SW_STANDBY_STREAM_ON		BIT(0)

#घोषणा OV8865_SW_RESET_REG			0x103
#घोषणा OV8865_SW_RESET_RESET			BIT(0)

#घोषणा OV8865_PLL_CTRL0_REG			0x300
#घोषणा OV8865_PLL_CTRL0_PRE_DIV(v)		((v) & GENMASK(2, 0))
#घोषणा OV8865_PLL_CTRL1_REG			0x301
#घोषणा OV8865_PLL_CTRL1_MUL_H(v)		(((v) & GENMASK(9, 8)) >> 8)
#घोषणा OV8865_PLL_CTRL2_REG			0x302
#घोषणा OV8865_PLL_CTRL2_MUL_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV8865_PLL_CTRL3_REG			0x303
#घोषणा OV8865_PLL_CTRL3_M_DIV(v)		(((v) - 1) & GENMASK(3, 0))
#घोषणा OV8865_PLL_CTRL4_REG			0x304
#घोषणा OV8865_PLL_CTRL4_MIPI_DIV(v)		((v) & GENMASK(1, 0))
#घोषणा OV8865_PLL_CTRL5_REG			0x305
#घोषणा OV8865_PLL_CTRL5_SYS_PRE_DIV(v)		((v) & GENMASK(1, 0))
#घोषणा OV8865_PLL_CTRL6_REG			0x306
#घोषणा OV8865_PLL_CTRL6_SYS_DIV(v)		(((v) - 1) & BIT(0))

#घोषणा OV8865_PLL_CTRL8_REG			0x308
#घोषणा OV8865_PLL_CTRL9_REG			0x309
#घोषणा OV8865_PLL_CTRLA_REG			0x30a
#घोषणा OV8865_PLL_CTRLA_PRE_DIV_HALF(v)	(((v) - 1) & BIT(0))
#घोषणा OV8865_PLL_CTRLB_REG			0x30b
#घोषणा OV8865_PLL_CTRLB_PRE_DIV(v)		((v) & GENMASK(2, 0))
#घोषणा OV8865_PLL_CTRLC_REG			0x30c
#घोषणा OV8865_PLL_CTRLC_MUL_H(v)		(((v) & GENMASK(9, 8)) >> 8)
#घोषणा OV8865_PLL_CTRLD_REG			0x30d
#घोषणा OV8865_PLL_CTRLD_MUL_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV8865_PLL_CTRLE_REG			0x30e
#घोषणा OV8865_PLL_CTRLE_SYS_DIV(v)		((v) & GENMASK(2, 0))
#घोषणा OV8865_PLL_CTRLF_REG			0x30f
#घोषणा OV8865_PLL_CTRLF_SYS_PRE_DIV(v)		(((v) - 1) & GENMASK(3, 0))
#घोषणा OV8865_PLL_CTRL10_REG			0x310
#घोषणा OV8865_PLL_CTRL11_REG			0x311
#घोषणा OV8865_PLL_CTRL12_REG			0x312
#घोषणा OV8865_PLL_CTRL12_PRE_DIV_HALF(v)	((((v) - 1) << 4) & BIT(4))
#घोषणा OV8865_PLL_CTRL12_DAC_DIV(v)		(((v) - 1) & GENMASK(3, 0))

#घोषणा OV8865_PLL_CTRL1B_REG			0x31b
#घोषणा OV8865_PLL_CTRL1C_REG			0x31c

#घोषणा OV8865_PLL_CTRL1E_REG			0x31e
#घोषणा OV8865_PLL_CTRL1E_PLL1_NO_LAT		BIT(3)

#घोषणा OV8865_PAD_OEN0_REG			0x3000

#घोषणा OV8865_PAD_OEN2_REG			0x3002

#घोषणा OV8865_CLK_RST5_REG			0x3005

#घोषणा OV8865_CHIP_ID_HH_REG			0x300a
#घोषणा OV8865_CHIP_ID_HH_VALUE			0x00
#घोषणा OV8865_CHIP_ID_H_REG			0x300b
#घोषणा OV8865_CHIP_ID_H_VALUE			0x88
#घोषणा OV8865_CHIP_ID_L_REG			0x300c
#घोषणा OV8865_CHIP_ID_L_VALUE			0x65
#घोषणा OV8865_PAD_OUT2_REG			0x300d

#घोषणा OV8865_PAD_SEL2_REG			0x3010
#घोषणा OV8865_PAD_PK_REG			0x3011
#घोषणा OV8865_PAD_PK_DRIVE_STRENGTH_1X		(0 << 5)
#घोषणा OV8865_PAD_PK_DRIVE_STRENGTH_2X		(1 << 5)
#घोषणा OV8865_PAD_PK_DRIVE_STRENGTH_3X		(2 << 5)
#घोषणा OV8865_PAD_PK_DRIVE_STRENGTH_4X		(3 << 5)

#घोषणा OV8865_PUMP_CLK_DIV_REG			0x3015
#घोषणा OV8865_PUMP_CLK_DIV_PUMP_N(v)		(((v) << 4) & GENMASK(6, 4))
#घोषणा OV8865_PUMP_CLK_DIV_PUMP_P(v)		((v) & GENMASK(2, 0))

#घोषणा OV8865_MIPI_SC_CTRL0_REG		0x3018
#घोषणा OV8865_MIPI_SC_CTRL0_LANES(v)		((((v) - 1) << 5) & \
						 GENMASK(7, 5))
#घोषणा OV8865_MIPI_SC_CTRL0_MIPI_EN		BIT(4)
#घोषणा OV8865_MIPI_SC_CTRL0_UNKNOWN		BIT(1)
#घोषणा OV8865_MIPI_SC_CTRL0_LANES_PD_MIPI	BIT(0)
#घोषणा OV8865_MIPI_SC_CTRL1_REG		0x3019
#घोषणा OV8865_CLK_RST0_REG			0x301a
#घोषणा OV8865_CLK_RST1_REG			0x301b
#घोषणा OV8865_CLK_RST2_REG			0x301c
#घोषणा OV8865_CLK_RST3_REG			0x301d
#घोषणा OV8865_CLK_RST4_REG			0x301e

#घोषणा OV8865_PCLK_SEL_REG			0x3020
#घोषणा OV8865_PCLK_SEL_PCLK_DIV_MASK		BIT(3)
#घोषणा OV8865_PCLK_SEL_PCLK_DIV(v)		((((v) - 1) << 3) & BIT(3))

#घोषणा OV8865_MISC_CTRL_REG			0x3021
#घोषणा OV8865_MIPI_SC_CTRL2_REG		0x3022
#घोषणा OV8865_MIPI_SC_CTRL2_CLK_LANES_PD_MIPI	BIT(1)
#घोषणा OV8865_MIPI_SC_CTRL2_PD_MIPI_RST_SYNC	BIT(0)

#घोषणा OV8865_MIPI_BIT_SEL_REG			0x3031
#घोषणा OV8865_MIPI_BIT_SEL(v)			(((v) << 0) & GENMASK(4, 0))
#घोषणा OV8865_CLK_SEL0_REG			0x3032
#घोषणा OV8865_CLK_SEL0_PLL1_SYS_SEL(v)		(((v) << 7) & BIT(7))
#घोषणा OV8865_CLK_SEL1_REG			0x3033
#घोषणा OV8865_CLK_SEL1_MIPI_खातापूर्ण		BIT(5)
#घोषणा OV8865_CLK_SEL1_UNKNOWN			BIT(2)
#घोषणा OV8865_CLK_SEL1_PLL_SCLK_SEL_MASK	BIT(1)
#घोषणा OV8865_CLK_SEL1_PLL_SCLK_SEL(v)		(((v) << 1) & BIT(1))

#घोषणा OV8865_SCLK_CTRL_REG			0x3106
#घोषणा OV8865_SCLK_CTRL_SCLK_DIV(v)		(((v) << 4) & GENMASK(7, 4))
#घोषणा OV8865_SCLK_CTRL_SCLK_PRE_DIV(v)	(((v) << 2) & GENMASK(3, 2))
#घोषणा OV8865_SCLK_CTRL_UNKNOWN		BIT(0)

/* Exposure/gain */

#घोषणा OV8865_EXPOSURE_CTRL_HH_REG		0x3500
#घोषणा OV8865_EXPOSURE_CTRL_HH(v)		(((v) & GENMASK(19, 16)) >> 16)
#घोषणा OV8865_EXPOSURE_CTRL_H_REG		0x3501
#घोषणा OV8865_EXPOSURE_CTRL_H(v)		(((v) & GENMASK(15, 8)) >> 8)
#घोषणा OV8865_EXPOSURE_CTRL_L_REG		0x3502
#घोषणा OV8865_EXPOSURE_CTRL_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV8865_EXPOSURE_GAIN_MANUAL_REG		0x3503

#घोषणा OV8865_GAIN_CTRL_H_REG			0x3508
#घोषणा OV8865_GAIN_CTRL_H(v)			(((v) & GENMASK(12, 8)) >> 8)
#घोषणा OV8865_GAIN_CTRL_L_REG			0x3509
#घोषणा OV8865_GAIN_CTRL_L(v)			((v) & GENMASK(7, 0))

/* Timing */

#घोषणा OV8865_CROP_START_X_H_REG		0x3800
#घोषणा OV8865_CROP_START_X_H(v)		(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV8865_CROP_START_X_L_REG		0x3801
#घोषणा OV8865_CROP_START_X_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV8865_CROP_START_Y_H_REG		0x3802
#घोषणा OV8865_CROP_START_Y_H(v)		(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV8865_CROP_START_Y_L_REG		0x3803
#घोषणा OV8865_CROP_START_Y_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV8865_CROP_END_X_H_REG			0x3804
#घोषणा OV8865_CROP_END_X_H(v)			(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV8865_CROP_END_X_L_REG			0x3805
#घोषणा OV8865_CROP_END_X_L(v)			((v) & GENMASK(7, 0))
#घोषणा OV8865_CROP_END_Y_H_REG			0x3806
#घोषणा OV8865_CROP_END_Y_H(v)			(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV8865_CROP_END_Y_L_REG			0x3807
#घोषणा OV8865_CROP_END_Y_L(v)			((v) & GENMASK(7, 0))
#घोषणा OV8865_OUTPUT_SIZE_X_H_REG		0x3808
#घोषणा OV8865_OUTPUT_SIZE_X_H(v)		(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV8865_OUTPUT_SIZE_X_L_REG		0x3809
#घोषणा OV8865_OUTPUT_SIZE_X_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV8865_OUTPUT_SIZE_Y_H_REG		0x380a
#घोषणा OV8865_OUTPUT_SIZE_Y_H(v)		(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV8865_OUTPUT_SIZE_Y_L_REG		0x380b
#घोषणा OV8865_OUTPUT_SIZE_Y_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV8865_HTS_H_REG			0x380c
#घोषणा OV8865_HTS_H(v)				(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV8865_HTS_L_REG			0x380d
#घोषणा OV8865_HTS_L(v)				((v) & GENMASK(7, 0))
#घोषणा OV8865_VTS_H_REG			0x380e
#घोषणा OV8865_VTS_H(v)				(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV8865_VTS_L_REG			0x380f
#घोषणा OV8865_VTS_L(v)				((v) & GENMASK(7, 0))
#घोषणा OV8865_OFFSET_X_H_REG			0x3810
#घोषणा OV8865_OFFSET_X_H(v)			(((v) & GENMASK(15, 8)) >> 8)
#घोषणा OV8865_OFFSET_X_L_REG			0x3811
#घोषणा OV8865_OFFSET_X_L(v)			((v) & GENMASK(7, 0))
#घोषणा OV8865_OFFSET_Y_H_REG			0x3812
#घोषणा OV8865_OFFSET_Y_H(v)			(((v) & GENMASK(14, 8)) >> 8)
#घोषणा OV8865_OFFSET_Y_L_REG			0x3813
#घोषणा OV8865_OFFSET_Y_L(v)			((v) & GENMASK(7, 0))
#घोषणा OV8865_INC_X_ODD_REG			0x3814
#घोषणा OV8865_INC_X_ODD(v)			((v) & GENMASK(4, 0))
#घोषणा OV8865_INC_X_EVEN_REG			0x3815
#घोषणा OV8865_INC_X_EVEN(v)			((v) & GENMASK(4, 0))
#घोषणा OV8865_VSYNC_START_H_REG		0x3816
#घोषणा OV8865_VSYNC_START_H(v)			(((v) & GENMASK(15, 8)) >> 8)
#घोषणा OV8865_VSYNC_START_L_REG		0x3817
#घोषणा OV8865_VSYNC_START_L(v)			((v) & GENMASK(7, 0))
#घोषणा OV8865_VSYNC_END_H_REG			0x3818
#घोषणा OV8865_VSYNC_END_H(v)			(((v) & GENMASK(15, 8)) >> 8)
#घोषणा OV8865_VSYNC_END_L_REG			0x3819
#घोषणा OV8865_VSYNC_END_L(v)			((v) & GENMASK(7, 0))
#घोषणा OV8865_HSYNC_FIRST_H_REG		0x381a
#घोषणा OV8865_HSYNC_FIRST_H(v)			(((v) & GENMASK(15, 8)) >> 8)
#घोषणा OV8865_HSYNC_FIRST_L_REG		0x381b
#घोषणा OV8865_HSYNC_FIRST_L(v)			((v) & GENMASK(7, 0))

#घोषणा OV8865_FORMAT1_REG			0x3820
#घोषणा OV8865_FORMAT1_FLIP_VERT_ISP_EN		BIT(2)
#घोषणा OV8865_FORMAT1_FLIP_VERT_SENSOR_EN	BIT(1)
#घोषणा OV8865_FORMAT2_REG			0x3821
#घोषणा OV8865_FORMAT2_HSYNC_EN			BIT(6)
#घोषणा OV8865_FORMAT2_FST_VBIN_EN		BIT(5)
#घोषणा OV8865_FORMAT2_FST_HBIN_EN		BIT(4)
#घोषणा OV8865_FORMAT2_ISP_HORZ_VAR2_EN		BIT(3)
#घोषणा OV8865_FORMAT2_FLIP_HORZ_ISP_EN		BIT(2)
#घोषणा OV8865_FORMAT2_FLIP_HORZ_SENSOR_EN	BIT(1)
#घोषणा OV8865_FORMAT2_SYNC_HBIN_EN		BIT(0)

#घोषणा OV8865_INC_Y_ODD_REG			0x382a
#घोषणा OV8865_INC_Y_ODD(v)			((v) & GENMASK(4, 0))
#घोषणा OV8865_INC_Y_EVEN_REG			0x382b
#घोषणा OV8865_INC_Y_EVEN(v)			((v) & GENMASK(4, 0))

#घोषणा OV8865_ABLC_NUM_REG			0x3830
#घोषणा OV8865_ABLC_NUM(v)			((v) & GENMASK(4, 0))

#घोषणा OV8865_ZLINE_NUM_REG			0x3836
#घोषणा OV8865_ZLINE_NUM(v)			((v) & GENMASK(4, 0))

#घोषणा OV8865_AUTO_SIZE_CTRL_REG		0x3841
#घोषणा OV8865_AUTO_SIZE_CTRL_OFFSET_Y_REG	BIT(5)
#घोषणा OV8865_AUTO_SIZE_CTRL_OFFSET_X_REG	BIT(4)
#घोषणा OV8865_AUTO_SIZE_CTRL_CROP_END_Y_REG	BIT(3)
#घोषणा OV8865_AUTO_SIZE_CTRL_CROP_END_X_REG	BIT(2)
#घोषणा OV8865_AUTO_SIZE_CTRL_CROP_START_Y_REG	BIT(1)
#घोषणा OV8865_AUTO_SIZE_CTRL_CROP_START_X_REG	BIT(0)
#घोषणा OV8865_AUTO_SIZE_X_OFFSET_H_REG		0x3842
#घोषणा OV8865_AUTO_SIZE_X_OFFSET_L_REG		0x3843
#घोषणा OV8865_AUTO_SIZE_Y_OFFSET_H_REG		0x3844
#घोषणा OV8865_AUTO_SIZE_Y_OFFSET_L_REG		0x3845
#घोषणा OV8865_AUTO_SIZE_BOUNDARIES_REG		0x3846
#घोषणा OV8865_AUTO_SIZE_BOUNDARIES_Y(v)	(((v) << 4) & GENMASK(7, 4))
#घोषणा OV8865_AUTO_SIZE_BOUNDARIES_X(v)	((v) & GENMASK(3, 0))

/* PSRAM */

#घोषणा OV8865_PSRAM_CTRL8_REG			0x3f08

/* Black Level */

#घोषणा OV8865_BLC_CTRL0_REG			0x4000
#घोषणा OV8865_BLC_CTRL0_TRIG_RANGE_EN		BIT(7)
#घोषणा OV8865_BLC_CTRL0_TRIG_FORMAT_EN		BIT(6)
#घोषणा OV8865_BLC_CTRL0_TRIG_GAIN_EN		BIT(5)
#घोषणा OV8865_BLC_CTRL0_TRIG_EXPOSURE_EN	BIT(4)
#घोषणा OV8865_BLC_CTRL0_TRIG_MANUAL_EN		BIT(3)
#घोषणा OV8865_BLC_CTRL0_FREEZE_EN		BIT(2)
#घोषणा OV8865_BLC_CTRL0_ALWAYS_EN		BIT(1)
#घोषणा OV8865_BLC_CTRL0_FILTER_EN		BIT(0)
#घोषणा OV8865_BLC_CTRL1_REG			0x4001
#घोषणा OV8865_BLC_CTRL1_DITHER_EN		BIT(7)
#घोषणा OV8865_BLC_CTRL1_ZERO_LINE_DIFF_EN	BIT(6)
#घोषणा OV8865_BLC_CTRL1_COL_SHIFT_256		(0 << 4)
#घोषणा OV8865_BLC_CTRL1_COL_SHIFT_128		(1 << 4)
#घोषणा OV8865_BLC_CTRL1_COL_SHIFT_64		(2 << 4)
#घोषणा OV8865_BLC_CTRL1_COL_SHIFT_32		(3 << 4)
#घोषणा OV8865_BLC_CTRL1_OFFSET_LIMIT_EN	BIT(2)
#घोषणा OV8865_BLC_CTRL1_COLUMN_CANCEL_EN	BIT(1)
#घोषणा OV8865_BLC_CTRL2_REG			0x4002
#घोषणा OV8865_BLC_CTRL3_REG			0x4003
#घोषणा OV8865_BLC_CTRL4_REG			0x4004
#घोषणा OV8865_BLC_CTRL5_REG			0x4005
#घोषणा OV8865_BLC_CTRL6_REG			0x4006
#घोषणा OV8865_BLC_CTRL7_REG			0x4007
#घोषणा OV8865_BLC_CTRL8_REG			0x4008
#घोषणा OV8865_BLC_CTRL9_REG			0x4009
#घोषणा OV8865_BLC_CTRLA_REG			0x400a
#घोषणा OV8865_BLC_CTRLB_REG			0x400b
#घोषणा OV8865_BLC_CTRLC_REG			0x400c
#घोषणा OV8865_BLC_CTRLD_REG			0x400d
#घोषणा OV8865_BLC_CTRLD_OFFSET_TRIGGER(v)	((v) & GENMASK(7, 0))

#घोषणा OV8865_BLC_CTRL1F_REG			0x401f
#घोषणा OV8865_BLC_CTRL1F_RB_REVERSE		BIT(3)
#घोषणा OV8865_BLC_CTRL1F_INTERPOL_X_EN		BIT(2)
#घोषणा OV8865_BLC_CTRL1F_INTERPOL_Y_EN		BIT(1)

#घोषणा OV8865_BLC_ANCHOR_LEFT_START_H_REG	0x4020
#घोषणा OV8865_BLC_ANCHOR_LEFT_START_H(v)	(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV8865_BLC_ANCHOR_LEFT_START_L_REG	0x4021
#घोषणा OV8865_BLC_ANCHOR_LEFT_START_L(v)	((v) & GENMASK(7, 0))
#घोषणा OV8865_BLC_ANCHOR_LEFT_END_H_REG	0x4022
#घोषणा OV8865_BLC_ANCHOR_LEFT_END_H(v)		(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV8865_BLC_ANCHOR_LEFT_END_L_REG	0x4023
#घोषणा OV8865_BLC_ANCHOR_LEFT_END_L(v)		((v) & GENMASK(7, 0))
#घोषणा OV8865_BLC_ANCHOR_RIGHT_START_H_REG	0x4024
#घोषणा OV8865_BLC_ANCHOR_RIGHT_START_H(v)	(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV8865_BLC_ANCHOR_RIGHT_START_L_REG	0x4025
#घोषणा OV8865_BLC_ANCHOR_RIGHT_START_L(v)	((v) & GENMASK(7, 0))
#घोषणा OV8865_BLC_ANCHOR_RIGHT_END_H_REG	0x4026
#घोषणा OV8865_BLC_ANCHOR_RIGHT_END_H(v)	(((v) & GENMASK(11, 8)) >> 8)
#घोषणा OV8865_BLC_ANCHOR_RIGHT_END_L_REG	0x4027
#घोषणा OV8865_BLC_ANCHOR_RIGHT_END_L(v)	((v) & GENMASK(7, 0))

#घोषणा OV8865_BLC_TOP_ZLINE_START_REG		0x4028
#घोषणा OV8865_BLC_TOP_ZLINE_START(v)		((v) & GENMASK(5, 0))
#घोषणा OV8865_BLC_TOP_ZLINE_NUM_REG		0x4029
#घोषणा OV8865_BLC_TOP_ZLINE_NUM(v)		((v) & GENMASK(4, 0))
#घोषणा OV8865_BLC_TOP_BLKLINE_START_REG	0x402a
#घोषणा OV8865_BLC_TOP_BLKLINE_START(v)		((v) & GENMASK(5, 0))
#घोषणा OV8865_BLC_TOP_BLKLINE_NUM_REG		0x402b
#घोषणा OV8865_BLC_TOP_BLKLINE_NUM(v)		((v) & GENMASK(4, 0))
#घोषणा OV8865_BLC_BOT_ZLINE_START_REG		0x402c
#घोषणा OV8865_BLC_BOT_ZLINE_START(v)		((v) & GENMASK(5, 0))
#घोषणा OV8865_BLC_BOT_ZLINE_NUM_REG		0x402d
#घोषणा OV8865_BLC_BOT_ZLINE_NUM(v)		((v) & GENMASK(4, 0))
#घोषणा OV8865_BLC_BOT_BLKLINE_START_REG	0x402e
#घोषणा OV8865_BLC_BOT_BLKLINE_START(v)		((v) & GENMASK(5, 0))
#घोषणा OV8865_BLC_BOT_BLKLINE_NUM_REG		0x402f
#घोषणा OV8865_BLC_BOT_BLKLINE_NUM(v)		((v) & GENMASK(4, 0))

#घोषणा OV8865_BLC_OFFSET_LIMIT_REG		0x4034
#घोषणा OV8865_BLC_OFFSET_LIMIT(v)		((v) & GENMASK(7, 0))

/* VFIFO */

#घोषणा OV8865_VFIFO_READ_START_H_REG		0x4600
#घोषणा OV8865_VFIFO_READ_START_H(v)		(((v) & GENMASK(15, 8)) >> 8)
#घोषणा OV8865_VFIFO_READ_START_L_REG		0x4601
#घोषणा OV8865_VFIFO_READ_START_L(v)		((v) & GENMASK(7, 0))

/* MIPI */

#घोषणा OV8865_MIPI_CTRL0_REG			0x4800
#घोषणा OV8865_MIPI_CTRL1_REG			0x4801
#घोषणा OV8865_MIPI_CTRL2_REG			0x4802
#घोषणा OV8865_MIPI_CTRL3_REG			0x4803
#घोषणा OV8865_MIPI_CTRL4_REG			0x4804
#घोषणा OV8865_MIPI_CTRL5_REG			0x4805
#घोषणा OV8865_MIPI_CTRL6_REG			0x4806
#घोषणा OV8865_MIPI_CTRL7_REG			0x4807
#घोषणा OV8865_MIPI_CTRL8_REG			0x4808

#घोषणा OV8865_MIPI_FCNT_MAX_H_REG		0x4810
#घोषणा OV8865_MIPI_FCNT_MAX_L_REG		0x4811

#घोषणा OV8865_MIPI_CTRL13_REG			0x4813
#घोषणा OV8865_MIPI_CTRL14_REG			0x4814
#घोषणा OV8865_MIPI_CTRL15_REG			0x4815
#घोषणा OV8865_MIPI_EMBEDDED_DT_REG		0x4816

#घोषणा OV8865_MIPI_HS_ZERO_MIN_H_REG		0x4818
#घोषणा OV8865_MIPI_HS_ZERO_MIN_L_REG		0x4819
#घोषणा OV8865_MIPI_HS_TRAIL_MIN_H_REG		0x481a
#घोषणा OV8865_MIPI_HS_TRAIL_MIN_L_REG		0x481b
#घोषणा OV8865_MIPI_CLK_ZERO_MIN_H_REG		0x481c
#घोषणा OV8865_MIPI_CLK_ZERO_MIN_L_REG		0x481d
#घोषणा OV8865_MIPI_CLK_PREPARE_MAX_REG		0x481e
#घोषणा OV8865_MIPI_CLK_PREPARE_MIN_REG		0x481f
#घोषणा OV8865_MIPI_CLK_POST_MIN_H_REG		0x4820
#घोषणा OV8865_MIPI_CLK_POST_MIN_L_REG		0x4821
#घोषणा OV8865_MIPI_CLK_TRAIL_MIN_H_REG		0x4822
#घोषणा OV8865_MIPI_CLK_TRAIL_MIN_L_REG		0x4823
#घोषणा OV8865_MIPI_LPX_P_MIN_H_REG		0x4824
#घोषणा OV8865_MIPI_LPX_P_MIN_L_REG		0x4825
#घोषणा OV8865_MIPI_HS_PREPARE_MIN_REG		0x4826
#घोषणा OV8865_MIPI_HS_PREPARE_MAX_REG		0x4827
#घोषणा OV8865_MIPI_HS_EXIT_MIN_H_REG		0x4828
#घोषणा OV8865_MIPI_HS_EXIT_MIN_L_REG		0x4829
#घोषणा OV8865_MIPI_UI_HS_ZERO_MIN_REG		0x482a
#घोषणा OV8865_MIPI_UI_HS_TRAIL_MIN_REG		0x482b
#घोषणा OV8865_MIPI_UI_CLK_ZERO_MIN_REG		0x482c
#घोषणा OV8865_MIPI_UI_CLK_PREPARE_REG		0x482d
#घोषणा OV8865_MIPI_UI_CLK_POST_MIN_REG		0x482e
#घोषणा OV8865_MIPI_UI_CLK_TRAIL_MIN_REG	0x482f
#घोषणा OV8865_MIPI_UI_LPX_P_MIN_REG		0x4830
#घोषणा OV8865_MIPI_UI_HS_PREPARE_REG		0x4831
#घोषणा OV8865_MIPI_UI_HS_EXIT_MIN_REG		0x4832
#घोषणा OV8865_MIPI_PKT_START_SIZE_REG		0x4833

#घोषणा OV8865_MIPI_PCLK_PERIOD_REG		0x4837
#घोषणा OV8865_MIPI_LP_GPIO0_REG		0x4838
#घोषणा OV8865_MIPI_LP_GPIO1_REG		0x4839

#घोषणा OV8865_MIPI_CTRL3C_REG			0x483c
#घोषणा OV8865_MIPI_LP_GPIO4_REG		0x483d

#घोषणा OV8865_MIPI_CTRL4A_REG			0x484a
#घोषणा OV8865_MIPI_CTRL4B_REG			0x484b
#घोषणा OV8865_MIPI_CTRL4C_REG			0x484c
#घोषणा OV8865_MIPI_LANE_TEST_PATTERN_REG	0x484d
#घोषणा OV8865_MIPI_FRAME_END_DELAY_REG		0x484e
#घोषणा OV8865_MIPI_CLOCK_TEST_PATTERN_REG	0x484f
#घोषणा OV8865_MIPI_LANE_SEL01_REG		0x4850
#घोषणा OV8865_MIPI_LANE_SEL01_LANE0(v)		(((v) << 0) & GENMASK(2, 0))
#घोषणा OV8865_MIPI_LANE_SEL01_LANE1(v)		(((v) << 4) & GENMASK(6, 4))
#घोषणा OV8865_MIPI_LANE_SEL23_REG		0x4851
#घोषणा OV8865_MIPI_LANE_SEL23_LANE2(v)		(((v) << 0) & GENMASK(2, 0))
#घोषणा OV8865_MIPI_LANE_SEL23_LANE3(v)		(((v) << 4) & GENMASK(6, 4))

/* ISP */

#घोषणा OV8865_ISP_CTRL0_REG			0x5000
#घोषणा OV8865_ISP_CTRL0_LENC_EN		BIT(7)
#घोषणा OV8865_ISP_CTRL0_WHITE_BALANCE_EN	BIT(4)
#घोषणा OV8865_ISP_CTRL0_DPC_BLACK_EN		BIT(2)
#घोषणा OV8865_ISP_CTRL0_DPC_WHITE_EN		BIT(1)
#घोषणा OV8865_ISP_CTRL1_REG			0x5001
#घोषणा OV8865_ISP_CTRL1_BLC_EN			BIT(0)
#घोषणा OV8865_ISP_CTRL2_REG			0x5002
#घोषणा OV8865_ISP_CTRL2_DEBUG			BIT(3)
#घोषणा OV8865_ISP_CTRL2_VARIOPIXEL_EN		BIT(2)
#घोषणा OV8865_ISP_CTRL2_VSYNC_LATCH_EN		BIT(0)
#घोषणा OV8865_ISP_CTRL3_REG			0x5003

#घोषणा OV8865_ISP_GAIN_RED_H_REG		0x5018
#घोषणा OV8865_ISP_GAIN_RED_H(v)		(((v) & GENMASK(13, 6)) >> 6)
#घोषणा OV8865_ISP_GAIN_RED_L_REG		0x5019
#घोषणा OV8865_ISP_GAIN_RED_L(v)		((v) & GENMASK(5, 0))
#घोषणा OV8865_ISP_GAIN_GREEN_H_REG		0x501a
#घोषणा OV8865_ISP_GAIN_GREEN_H(v)		(((v) & GENMASK(13, 6)) >> 6)
#घोषणा OV8865_ISP_GAIN_GREEN_L_REG		0x501b
#घोषणा OV8865_ISP_GAIN_GREEN_L(v)		((v) & GENMASK(5, 0))
#घोषणा OV8865_ISP_GAIN_BLUE_H_REG		0x501c
#घोषणा OV8865_ISP_GAIN_BLUE_H(v)		(((v) & GENMASK(13, 6)) >> 6)
#घोषणा OV8865_ISP_GAIN_BLUE_L_REG		0x501d
#घोषणा OV8865_ISP_GAIN_BLUE_L(v)		((v) & GENMASK(5, 0))

/* VarioPixel */

#घोषणा OV8865_VAP_CTRL0_REG			0x5900
#घोषणा OV8865_VAP_CTRL1_REG			0x5901
#घोषणा OV8865_VAP_CTRL1_HSUB_COEF(v)		((((v) - 1) << 2) & \
						 GENMASK(3, 2))
#घोषणा OV8865_VAP_CTRL1_VSUB_COEF(v)		(((v) - 1) & GENMASK(1, 0))

/* Pre-DSP */

#घोषणा OV8865_PRE_CTRL0_REG			0x5e00
#घोषणा OV8865_PRE_CTRL0_PATTERN_EN		BIT(7)
#घोषणा OV8865_PRE_CTRL0_ROLLING_BAR_EN		BIT(6)
#घोषणा OV8865_PRE_CTRL0_TRANSPARENT_MODE	BIT(5)
#घोषणा OV8865_PRE_CTRL0_SQUARES_BW_MODE	BIT(4)
#घोषणा OV8865_PRE_CTRL0_PATTERN_COLOR_BARS	0
#घोषणा OV8865_PRE_CTRL0_PATTERN_RANDOM_DATA	1
#घोषणा OV8865_PRE_CTRL0_PATTERN_COLOR_SQUARES	2
#घोषणा OV8865_PRE_CTRL0_PATTERN_BLACK		3

/* Macros */

#घोषणा ov8865_subdev_sensor(s) \
	container_of(s, काष्ठा ov8865_sensor, subdev)

#घोषणा ov8865_ctrl_subdev(c) \
	(&container_of((c)->handler, काष्ठा ov8865_sensor, \
		       ctrls.handler)->subdev)

/* Data काष्ठाures */

काष्ठा ov8865_रेजिस्टर_value अणु
	u16 address;
	u8 value;
	अचिन्हित पूर्णांक delay_ms;
पूर्ण;

/*
 * PLL1 Clock Tree:
 *
 * +-< EXTCLK
 * |
 * +-+ pll_pre_भाग_half (0x30a [0])
 *   |
 *   +-+ pll_pre_भाग (0x300 [2:0], special values:
 *     |              0: 1, 1: 1.5, 3: 2.5, 4: 3, 5: 4, 7: 8)
 *     +-+ pll_mul (0x301 [1:0], 0x302 [7:0])
 *       |
 *       +-+ m_भाग (0x303 [3:0])
 *       | |
 *       | +-> PHY_SCLK
 *       | |
 *       | +-+ mipi_भाग (0x304 [1:0], special values: 0: 4, 1: 5, 2: 6, 3: 8)
 *       |   |
 *       |   +-+ pclk_भाग (0x3020 [3])
 *       |     |
 *       |     +-> PCLK
 *       |
 *       +-+ sys_pre_भाग (0x305 [1:0], special values: 0: 3, 1: 4, 2: 5, 3: 6)
 *         |
 *         +-+ sys_भाग (0x306 [0])
 *           |
 *           +-+ sys_sel (0x3032 [7], 0: PLL1, 1: PLL2)
 *             |
 *             +-+ sclk_sel (0x3033 [1], 0: sys_sel, 1: PLL2 DAC_CLK)
 *               |
 *               +-+ sclk_pre_भाग (0x3106 [3:2], special values:
 *                 |               0: 1, 1: 2, 2: 4, 3: 1)
 *                 |
 *                 +-+ sclk_भाग (0x3106 [7:4], special values: 0: 1)
 *                   |
 *                   +-> SCLK
 */

काष्ठा ov8865_pll1_config अणु
	अचिन्हित पूर्णांक pll_pre_भाग_half;
	अचिन्हित पूर्णांक pll_pre_भाग;
	अचिन्हित पूर्णांक pll_mul;
	अचिन्हित पूर्णांक m_भाग;
	अचिन्हित पूर्णांक mipi_भाग;
	अचिन्हित पूर्णांक pclk_भाग;
	अचिन्हित पूर्णांक sys_pre_भाग;
	अचिन्हित पूर्णांक sys_भाग;
पूर्ण;

/*
 * PLL2 Clock Tree:
 *
 * +-< EXTCLK
 * |
 * +-+ pll_pre_भाग_half (0x312 [4])
 *   |
 *   +-+ pll_pre_भाग (0x30b [2:0], special values:
 *     |              0: 1, 1: 1.5, 3: 2.5, 4: 3, 5: 4, 7: 8)
 *     +-+ pll_mul (0x30c [1:0], 0x30d [7:0])
 *       |
 *       +-+ dac_भाग (0x312 [3:0])
 *       | |
 *       | +-> DAC_CLK
 *       |
 *       +-+ sys_pre_भाग (0x30f [3:0])
 *         |
 *         +-+ sys_भाग (0x30e [2:0], special values:
 *           |          0: 1, 1: 1.5, 3: 2.5, 4: 3, 5: 3.5, 6: 4, 7:5)
 *           |
 *           +-+ sys_sel (0x3032 [7], 0: PLL1, 1: PLL2)
 *             |
 *             +-+ sclk_sel (0x3033 [1], 0: sys_sel, 1: PLL2 DAC_CLK)
 *               |
 *               +-+ sclk_pre_भाग (0x3106 [3:2], special values:
 *                 |               0: 1, 1: 2, 2: 4, 3: 1)
 *                 |
 *                 +-+ sclk_भाग (0x3106 [7:4], special values: 0: 1)
 *                   |
 *                   +-> SCLK
 */

काष्ठा ov8865_pll2_config अणु
	अचिन्हित पूर्णांक pll_pre_भाग_half;
	अचिन्हित पूर्णांक pll_pre_भाग;
	अचिन्हित पूर्णांक pll_mul;
	अचिन्हित पूर्णांक dac_भाग;
	अचिन्हित पूर्णांक sys_pre_भाग;
	अचिन्हित पूर्णांक sys_भाग;
पूर्ण;

काष्ठा ov8865_sclk_config अणु
	अचिन्हित पूर्णांक sys_sel;
	अचिन्हित पूर्णांक sclk_sel;
	अचिन्हित पूर्णांक sclk_pre_भाग;
	अचिन्हित पूर्णांक sclk_भाग;
पूर्ण;

/*
 * General क्रमmulas क्रम (array-centered) mode calculation:
 * - photo_array_width = 3296
 * - crop_start_x = (photo_array_width - output_size_x) / 2
 * - crop_end_x = crop_start_x + offset_x + output_size_x - 1
 *
 * - photo_array_height = 2480
 * - crop_start_y = (photo_array_height - output_size_y) / 2
 * - crop_end_y = crop_start_y + offset_y + output_size_y - 1
 */

काष्ठा ov8865_mode अणु
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

	/* With स्वतः size, only output and total sizes need to be set. */
	bool size_स्वतः;
	अचिन्हित पूर्णांक size_स्वतः_boundary_x;
	अचिन्हित पूर्णांक size_स्वतः_boundary_y;

	bool binning_x;
	bool binning_y;
	bool variopixel;
	अचिन्हित पूर्णांक variopixel_hsub_coef;
	अचिन्हित पूर्णांक variopixel_vsub_coef;

	/* Bits क्रम the क्रमmat रेजिस्टर, used क्रम binning. */
	bool sync_hbin;
	bool horz_var2;

	अचिन्हित पूर्णांक inc_x_odd;
	अचिन्हित पूर्णांक inc_x_even;
	अचिन्हित पूर्णांक inc_y_odd;
	अचिन्हित पूर्णांक inc_y_even;

	अचिन्हित पूर्णांक vfअगरo_पढ़ो_start;

	अचिन्हित पूर्णांक ablc_num;
	अचिन्हित पूर्णांक zline_num;

	अचिन्हित पूर्णांक blc_top_zero_line_start;
	अचिन्हित पूर्णांक blc_top_zero_line_num;
	अचिन्हित पूर्णांक blc_top_black_line_start;
	अचिन्हित पूर्णांक blc_top_black_line_num;

	अचिन्हित पूर्णांक blc_bottom_zero_line_start;
	अचिन्हित पूर्णांक blc_bottom_zero_line_num;
	अचिन्हित पूर्णांक blc_bottom_black_line_start;
	अचिन्हित पूर्णांक blc_bottom_black_line_num;

	u8 blc_col_shअगरt_mask;

	अचिन्हित पूर्णांक blc_anchor_left_start;
	अचिन्हित पूर्णांक blc_anchor_left_end;
	अचिन्हित पूर्णांक blc_anchor_right_start;
	अचिन्हित पूर्णांक blc_anchor_right_end;

	काष्ठा v4l2_fract frame_पूर्णांकerval;

	स्थिर काष्ठा ov8865_pll1_config *pll1_config;
	स्थिर काष्ठा ov8865_pll2_config *pll2_config;
	स्थिर काष्ठा ov8865_sclk_config *sclk_config;

	स्थिर काष्ठा ov8865_रेजिस्टर_value *रेजिस्टर_values;
	अचिन्हित पूर्णांक रेजिस्टर_values_count;
पूर्ण;

काष्ठा ov8865_state अणु
	स्थिर काष्ठा ov8865_mode *mode;
	u32 mbus_code;

	bool streaming;
पूर्ण;

काष्ठा ov8865_ctrls अणु
	काष्ठा v4l2_ctrl *link_freq;
	काष्ठा v4l2_ctrl *pixel_rate;

	काष्ठा v4l2_ctrl_handler handler;
पूर्ण;

काष्ठा ov8865_sensor अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *i2c_client;
	काष्ठा gpio_desc *reset;
	काष्ठा gpio_desc *घातerकरोwn;
	काष्ठा regulator *avdd;
	काष्ठा regulator *dvdd;
	काष्ठा regulator *करोvdd;
	काष्ठा clk *extclk;

	काष्ठा v4l2_fwnode_endpoपूर्णांक endpoपूर्णांक;
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pad;

	काष्ठा mutex mutex;

	काष्ठा ov8865_state state;
	काष्ठा ov8865_ctrls ctrls;
पूर्ण;

/* Static definitions */

/*
 * EXTCLK = 24 MHz
 * PHY_SCLK = 720 MHz
 * MIPI_PCLK = 90 MHz
 */
अटल स्थिर काष्ठा ov8865_pll1_config ov8865_pll1_config_native = अणु
	.pll_pre_भाग_half	= 1,
	.pll_pre_भाग		= 0,
	.pll_mul		= 30,
	.m_भाग			= 1,
	.mipi_भाग		= 3,
	.pclk_भाग		= 1,
	.sys_pre_भाग		= 1,
	.sys_भाग		= 2,
पूर्ण;

/*
 * EXTCLK = 24 MHz
 * DAC_CLK = 360 MHz
 * SCLK = 144 MHz
 */

अटल स्थिर काष्ठा ov8865_pll2_config ov8865_pll2_config_native = अणु
	.pll_pre_भाग_half	= 1,
	.pll_pre_भाग		= 0,
	.pll_mul		= 30,
	.dac_भाग		= 2,
	.sys_pre_भाग		= 5,
	.sys_भाग		= 0,
पूर्ण;

/*
 * EXTCLK = 24 MHz
 * DAC_CLK = 360 MHz
 * SCLK = 80 MHz
 */

अटल स्थिर काष्ठा ov8865_pll2_config ov8865_pll2_config_binning = अणु
	.pll_pre_भाग_half	= 1,
	.pll_pre_भाग		= 0,
	.pll_mul		= 30,
	.dac_भाग		= 2,
	.sys_pre_भाग		= 10,
	.sys_भाग		= 0,
पूर्ण;

अटल स्थिर काष्ठा ov8865_sclk_config ov8865_sclk_config_native = अणु
	.sys_sel		= 1,
	.sclk_sel		= 0,
	.sclk_pre_भाग		= 0,
	.sclk_भाग		= 0,
पूर्ण;

अटल स्थिर काष्ठा ov8865_रेजिस्टर_value ov8865_रेजिस्टर_values_native[] = अणु
	/* Sensor */

	अणु 0x3700, 0x48 पूर्ण,
	अणु 0x3701, 0x18 पूर्ण,
	अणु 0x3702, 0x50 पूर्ण,
	अणु 0x3703, 0x32 पूर्ण,
	अणु 0x3704, 0x28 पूर्ण,
	अणु 0x3706, 0x70 पूर्ण,
	अणु 0x3707, 0x08 पूर्ण,
	अणु 0x3708, 0x48 पूर्ण,
	अणु 0x3709, 0x80 पूर्ण,
	अणु 0x370a, 0x01 पूर्ण,
	अणु 0x370b, 0x70 पूर्ण,
	अणु 0x370c, 0x07 पूर्ण,
	अणु 0x3718, 0x14 पूर्ण,
	अणु 0x3712, 0x44 पूर्ण,
	अणु 0x371e, 0x31 पूर्ण,
	अणु 0x371f, 0x7f पूर्ण,
	अणु 0x3720, 0x0a पूर्ण,
	अणु 0x3721, 0x0a पूर्ण,
	अणु 0x3724, 0x04 पूर्ण,
	अणु 0x3725, 0x04 पूर्ण,
	अणु 0x3726, 0x0c पूर्ण,
	अणु 0x3728, 0x0a पूर्ण,
	अणु 0x3729, 0x03 पूर्ण,
	अणु 0x372a, 0x06 पूर्ण,
	अणु 0x372b, 0xa6 पूर्ण,
	अणु 0x372c, 0xa6 पूर्ण,
	अणु 0x372d, 0xa6 पूर्ण,
	अणु 0x372e, 0x0c पूर्ण,
	अणु 0x372f, 0x20 पूर्ण,
	अणु 0x3730, 0x02 पूर्ण,
	अणु 0x3731, 0x0c पूर्ण,
	अणु 0x3732, 0x28 पूर्ण,
	अणु 0x3736, 0x30 पूर्ण,
	अणु 0x373a, 0x04 पूर्ण,
	अणु 0x373b, 0x18 पूर्ण,
	अणु 0x373c, 0x14 पूर्ण,
	अणु 0x373e, 0x06 पूर्ण,
	अणु 0x375a, 0x0c पूर्ण,
	अणु 0x375b, 0x26 पूर्ण,
	अणु 0x375d, 0x04 पूर्ण,
	अणु 0x375f, 0x28 पूर्ण,
	अणु 0x3767, 0x1e पूर्ण,
	अणु 0x3772, 0x46 पूर्ण,
	अणु 0x3773, 0x04 पूर्ण,
	अणु 0x3774, 0x2c पूर्ण,
	अणु 0x3775, 0x13 पूर्ण,
	अणु 0x3776, 0x10 पूर्ण,
	अणु 0x37a0, 0x88 पूर्ण,
	अणु 0x37a1, 0x7a पूर्ण,
	अणु 0x37a2, 0x7a पूर्ण,
	अणु 0x37a3, 0x02 पूर्ण,
	अणु 0x37a5, 0x09 पूर्ण,
	अणु 0x37a7, 0x88 पूर्ण,
	अणु 0x37a8, 0xb0 पूर्ण,
	अणु 0x37a9, 0xb0 पूर्ण,
	अणु 0x37aa, 0x88 पूर्ण,
	अणु 0x37ab, 0x5c पूर्ण,
	अणु 0x37ac, 0x5c पूर्ण,
	अणु 0x37ad, 0x55 पूर्ण,
	अणु 0x37ae, 0x19 पूर्ण,
	अणु 0x37af, 0x19 पूर्ण,
	अणु 0x37b3, 0x84 पूर्ण,
	अणु 0x37b4, 0x84 पूर्ण,
	अणु 0x37b5, 0x66 पूर्ण,

	/* PSRAM */

	अणु OV8865_PSRAM_CTRL8_REG, 0x16 पूर्ण,

	/* ADC Sync */

	अणु 0x4500, 0x68 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov8865_रेजिस्टर_value ov8865_रेजिस्टर_values_binning[] = अणु
	/* Sensor */

	अणु 0x3700, 0x24 पूर्ण,
	अणु 0x3701, 0x0c पूर्ण,
	अणु 0x3702, 0x28 पूर्ण,
	अणु 0x3703, 0x19 पूर्ण,
	अणु 0x3704, 0x14 पूर्ण,
	अणु 0x3706, 0x38 पूर्ण,
	अणु 0x3707, 0x04 पूर्ण,
	अणु 0x3708, 0x24 पूर्ण,
	अणु 0x3709, 0x40 पूर्ण,
	अणु 0x370a, 0x00 पूर्ण,
	अणु 0x370b, 0xb8 पूर्ण,
	अणु 0x370c, 0x04 पूर्ण,
	अणु 0x3718, 0x12 पूर्ण,
	अणु 0x3712, 0x42 पूर्ण,
	अणु 0x371e, 0x19 पूर्ण,
	अणु 0x371f, 0x40 पूर्ण,
	अणु 0x3720, 0x05 पूर्ण,
	अणु 0x3721, 0x05 पूर्ण,
	अणु 0x3724, 0x02 पूर्ण,
	अणु 0x3725, 0x02 पूर्ण,
	अणु 0x3726, 0x06 पूर्ण,
	अणु 0x3728, 0x05 पूर्ण,
	अणु 0x3729, 0x02 पूर्ण,
	अणु 0x372a, 0x03 पूर्ण,
	अणु 0x372b, 0x53 पूर्ण,
	अणु 0x372c, 0xa3 पूर्ण,
	अणु 0x372d, 0x53 पूर्ण,
	अणु 0x372e, 0x06 पूर्ण,
	अणु 0x372f, 0x10 पूर्ण,
	अणु 0x3730, 0x01 पूर्ण,
	अणु 0x3731, 0x06 पूर्ण,
	अणु 0x3732, 0x14 पूर्ण,
	अणु 0x3736, 0x20 पूर्ण,
	अणु 0x373a, 0x02 पूर्ण,
	अणु 0x373b, 0x0c पूर्ण,
	अणु 0x373c, 0x0a पूर्ण,
	अणु 0x373e, 0x03 पूर्ण,
	अणु 0x375a, 0x06 पूर्ण,
	अणु 0x375b, 0x13 पूर्ण,
	अणु 0x375d, 0x02 पूर्ण,
	अणु 0x375f, 0x14 पूर्ण,
	अणु 0x3767, 0x1c पूर्ण,
	अणु 0x3772, 0x23 पूर्ण,
	अणु 0x3773, 0x02 पूर्ण,
	अणु 0x3774, 0x16 पूर्ण,
	अणु 0x3775, 0x12 पूर्ण,
	अणु 0x3776, 0x08 पूर्ण,
	अणु 0x37a0, 0x44 पूर्ण,
	अणु 0x37a1, 0x3d पूर्ण,
	अणु 0x37a2, 0x3d पूर्ण,
	अणु 0x37a3, 0x01 पूर्ण,
	अणु 0x37a5, 0x08 पूर्ण,
	अणु 0x37a7, 0x44 पूर्ण,
	अणु 0x37a8, 0x58 पूर्ण,
	अणु 0x37a9, 0x58 पूर्ण,
	अणु 0x37aa, 0x44 पूर्ण,
	अणु 0x37ab, 0x2e पूर्ण,
	अणु 0x37ac, 0x2e पूर्ण,
	अणु 0x37ad, 0x33 पूर्ण,
	अणु 0x37ae, 0x0d पूर्ण,
	अणु 0x37af, 0x0d पूर्ण,
	अणु 0x37b3, 0x42 पूर्ण,
	अणु 0x37b4, 0x42 पूर्ण,
	अणु 0x37b5, 0x33 पूर्ण,

	/* PSRAM */

	अणु OV8865_PSRAM_CTRL8_REG, 0x0b पूर्ण,

	/* ADC Sync */

	अणु 0x4500, 0x40 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov8865_mode ov8865_modes[] = अणु
	/* 3264x2448 */
	अणु
		/* Horizontal */
		.output_size_x			= 3264,
		.hts				= 1944,

		/* Vertical */
		.output_size_y			= 2448,
		.vts				= 2470,

		.size_स्वतः			= true,
		.size_स्वतः_boundary_x		= 8,
		.size_स्वतः_boundary_y		= 4,

		/* Subsample increase */
		.inc_x_odd			= 1,
		.inc_x_even			= 1,
		.inc_y_odd			= 1,
		.inc_y_even			= 1,

		/* VFIFO */
		.vfअगरo_पढ़ो_start		= 16,

		.ablc_num			= 4,
		.zline_num			= 1,

		/* Black Level */

		.blc_top_zero_line_start	= 0,
		.blc_top_zero_line_num		= 2,
		.blc_top_black_line_start	= 4,
		.blc_top_black_line_num		= 4,

		.blc_bottom_zero_line_start	= 2,
		.blc_bottom_zero_line_num	= 2,
		.blc_bottom_black_line_start	= 8,
		.blc_bottom_black_line_num	= 2,

		.blc_anchor_left_start		= 576,
		.blc_anchor_left_end		= 831,
		.blc_anchor_right_start		= 1984,
		.blc_anchor_right_end		= 2239,

		/* Frame Interval */
		.frame_पूर्णांकerval			= अणु 1, 30 पूर्ण,

		/* PLL */
		.pll1_config			= &ov8865_pll1_config_native,
		.pll2_config			= &ov8865_pll2_config_native,
		.sclk_config			= &ov8865_sclk_config_native,

		/* Registers */
		.रेजिस्टर_values	= ov8865_रेजिस्टर_values_native,
		.रेजिस्टर_values_count	=
			ARRAY_SIZE(ov8865_रेजिस्टर_values_native),
	पूर्ण,
	/* 3264x1836 */
	अणु
		/* Horizontal */
		.output_size_x			= 3264,
		.hts				= 2582,

		/* Vertical */
		.output_size_y			= 1836,
		.vts				= 2002,

		.size_स्वतः			= true,
		.size_स्वतः_boundary_x		= 8,
		.size_स्वतः_boundary_y		= 4,

		/* Subsample increase */
		.inc_x_odd			= 1,
		.inc_x_even			= 1,
		.inc_y_odd			= 1,
		.inc_y_even			= 1,

		/* VFIFO */
		.vfअगरo_पढ़ो_start		= 16,

		.ablc_num			= 4,
		.zline_num			= 1,

		/* Black Level */

		.blc_top_zero_line_start	= 0,
		.blc_top_zero_line_num		= 2,
		.blc_top_black_line_start	= 4,
		.blc_top_black_line_num		= 4,

		.blc_bottom_zero_line_start	= 2,
		.blc_bottom_zero_line_num	= 2,
		.blc_bottom_black_line_start	= 8,
		.blc_bottom_black_line_num	= 2,

		.blc_anchor_left_start		= 576,
		.blc_anchor_left_end		= 831,
		.blc_anchor_right_start		= 1984,
		.blc_anchor_right_end		= 2239,

		/* Frame Interval */
		.frame_पूर्णांकerval			= अणु 1, 30 पूर्ण,

		/* PLL */
		.pll1_config			= &ov8865_pll1_config_native,
		.pll2_config			= &ov8865_pll2_config_native,
		.sclk_config			= &ov8865_sclk_config_native,

		/* Registers */
		.रेजिस्टर_values	= ov8865_रेजिस्टर_values_native,
		.रेजिस्टर_values_count	=
			ARRAY_SIZE(ov8865_रेजिस्टर_values_native),
	पूर्ण,
	/* 1632x1224 */
	अणु
		/* Horizontal */
		.output_size_x			= 1632,
		.hts				= 1923,

		/* Vertical */
		.output_size_y			= 1224,
		.vts				= 1248,

		.size_स्वतः			= true,
		.size_स्वतः_boundary_x		= 8,
		.size_स्वतः_boundary_y		= 8,

		/* Subsample increase */
		.inc_x_odd			= 3,
		.inc_x_even			= 1,
		.inc_y_odd			= 3,
		.inc_y_even			= 1,

		/* Binning */
		.binning_y			= true,
		.sync_hbin			= true,

		/* VFIFO */
		.vfअगरo_पढ़ो_start		= 116,

		.ablc_num			= 8,
		.zline_num			= 2,

		/* Black Level */

		.blc_top_zero_line_start	= 0,
		.blc_top_zero_line_num		= 2,
		.blc_top_black_line_start	= 4,
		.blc_top_black_line_num		= 4,

		.blc_bottom_zero_line_start	= 2,
		.blc_bottom_zero_line_num	= 2,
		.blc_bottom_black_line_start	= 8,
		.blc_bottom_black_line_num	= 2,

		.blc_anchor_left_start		= 288,
		.blc_anchor_left_end		= 415,
		.blc_anchor_right_start		= 992,
		.blc_anchor_right_end		= 1119,

		/* Frame Interval */
		.frame_पूर्णांकerval			= अणु 1, 30 पूर्ण,

		/* PLL */
		.pll1_config			= &ov8865_pll1_config_native,
		.pll2_config			= &ov8865_pll2_config_binning,
		.sclk_config			= &ov8865_sclk_config_native,

		/* Registers */
		.रेजिस्टर_values	= ov8865_रेजिस्टर_values_binning,
		.रेजिस्टर_values_count	=
			ARRAY_SIZE(ov8865_रेजिस्टर_values_binning),
	पूर्ण,
	/* 800x600 (SVGA) */
	अणु
		/* Horizontal */
		.output_size_x			= 800,
		.hts				= 1250,

		/* Vertical */
		.output_size_y			= 600,
		.vts				= 640,

		.size_स्वतः			= true,
		.size_स्वतः_boundary_x		= 8,
		.size_स्वतः_boundary_y		= 8,

		/* Subsample increase */
		.inc_x_odd			= 3,
		.inc_x_even			= 1,
		.inc_y_odd			= 5,
		.inc_y_even			= 3,

		/* Binning */
		.binning_y			= true,
		.variopixel			= true,
		.variopixel_hsub_coef		= 2,
		.variopixel_vsub_coef		= 1,
		.sync_hbin			= true,
		.horz_var2			= true,

		/* VFIFO */
		.vfअगरo_पढ़ो_start		= 80,

		.ablc_num			= 8,
		.zline_num			= 2,

		/* Black Level */

		.blc_top_zero_line_start	= 0,
		.blc_top_zero_line_num		= 2,
		.blc_top_black_line_start	= 2,
		.blc_top_black_line_num		= 2,

		.blc_bottom_zero_line_start	= 0,
		.blc_bottom_zero_line_num	= 0,
		.blc_bottom_black_line_start	= 4,
		.blc_bottom_black_line_num	= 2,

		.blc_col_shअगरt_mask	= OV8865_BLC_CTRL1_COL_SHIFT_128,

		.blc_anchor_left_start		= 288,
		.blc_anchor_left_end		= 415,
		.blc_anchor_right_start		= 992,
		.blc_anchor_right_end		= 1119,

		/* Frame Interval */
		.frame_पूर्णांकerval			= अणु 1, 90 पूर्ण,

		/* PLL */
		.pll1_config			= &ov8865_pll1_config_native,
		.pll2_config			= &ov8865_pll2_config_binning,
		.sclk_config			= &ov8865_sclk_config_native,

		/* Registers */
		.रेजिस्टर_values	= ov8865_रेजिस्टर_values_binning,
		.रेजिस्टर_values_count	=
			ARRAY_SIZE(ov8865_रेजिस्टर_values_binning),
	पूर्ण,
पूर्ण;

अटल स्थिर u32 ov8865_mbus_codes[] = अणु
	MEDIA_BUS_FMT_SBGGR10_1X10,
पूर्ण;

अटल स्थिर काष्ठा ov8865_रेजिस्टर_value ov8865_init_sequence[] = अणु
	/* Analog */

	अणु 0x3604, 0x04 पूर्ण,
	अणु 0x3602, 0x30 पूर्ण,
	अणु 0x3605, 0x00 पूर्ण,
	अणु 0x3607, 0x20 पूर्ण,
	अणु 0x3608, 0x11 पूर्ण,
	अणु 0x3609, 0x68 पूर्ण,
	अणु 0x360a, 0x40 पूर्ण,
	अणु 0x360c, 0xdd पूर्ण,
	अणु 0x360e, 0x0c पूर्ण,
	अणु 0x3610, 0x07 पूर्ण,
	अणु 0x3612, 0x86 पूर्ण,
	अणु 0x3613, 0x58 पूर्ण,
	अणु 0x3614, 0x28 पूर्ण,
	अणु 0x3617, 0x40 पूर्ण,
	अणु 0x3618, 0x5a पूर्ण,
	अणु 0x3619, 0x9b पूर्ण,
	अणु 0x361c, 0x00 पूर्ण,
	अणु 0x361d, 0x60 पूर्ण,
	अणु 0x3631, 0x60 पूर्ण,
	अणु 0x3633, 0x10 पूर्ण,
	अणु 0x3634, 0x10 पूर्ण,
	अणु 0x3635, 0x10 पूर्ण,
	अणु 0x3636, 0x10 पूर्ण,
	अणु 0x3638, 0xff पूर्ण,
	अणु 0x3641, 0x55 पूर्ण,
	अणु 0x3646, 0x86 पूर्ण,
	अणु 0x3647, 0x27 पूर्ण,
	अणु 0x364a, 0x1b पूर्ण,

	/* Sensor */

	अणु 0x3700, 0x24 पूर्ण,
	अणु 0x3701, 0x0c पूर्ण,
	अणु 0x3702, 0x28 पूर्ण,
	अणु 0x3703, 0x19 पूर्ण,
	अणु 0x3704, 0x14 पूर्ण,
	अणु 0x3705, 0x00 पूर्ण,
	अणु 0x3706, 0x38 पूर्ण,
	अणु 0x3707, 0x04 पूर्ण,
	अणु 0x3708, 0x24 पूर्ण,
	अणु 0x3709, 0x40 पूर्ण,
	अणु 0x370a, 0x00 पूर्ण,
	अणु 0x370b, 0xb8 पूर्ण,
	अणु 0x370c, 0x04 पूर्ण,
	अणु 0x3718, 0x12 पूर्ण,
	अणु 0x3719, 0x31 पूर्ण,
	अणु 0x3712, 0x42 पूर्ण,
	अणु 0x3714, 0x12 पूर्ण,
	अणु 0x371e, 0x19 पूर्ण,
	अणु 0x371f, 0x40 पूर्ण,
	अणु 0x3720, 0x05 पूर्ण,
	अणु 0x3721, 0x05 पूर्ण,
	अणु 0x3724, 0x02 पूर्ण,
	अणु 0x3725, 0x02 पूर्ण,
	अणु 0x3726, 0x06 पूर्ण,
	अणु 0x3728, 0x05 पूर्ण,
	अणु 0x3729, 0x02 पूर्ण,
	अणु 0x372a, 0x03 पूर्ण,
	अणु 0x372b, 0x53 पूर्ण,
	अणु 0x372c, 0xa3 पूर्ण,
	अणु 0x372d, 0x53 पूर्ण,
	अणु 0x372e, 0x06 पूर्ण,
	अणु 0x372f, 0x10 पूर्ण,
	अणु 0x3730, 0x01 पूर्ण,
	अणु 0x3731, 0x06 पूर्ण,
	अणु 0x3732, 0x14 पूर्ण,
	अणु 0x3733, 0x10 पूर्ण,
	अणु 0x3734, 0x40 पूर्ण,
	अणु 0x3736, 0x20 पूर्ण,
	अणु 0x373a, 0x02 पूर्ण,
	अणु 0x373b, 0x0c पूर्ण,
	अणु 0x373c, 0x0a पूर्ण,
	अणु 0x373e, 0x03 पूर्ण,
	अणु 0x3755, 0x40 पूर्ण,
	अणु 0x3758, 0x00 पूर्ण,
	अणु 0x3759, 0x4c पूर्ण,
	अणु 0x375a, 0x06 पूर्ण,
	अणु 0x375b, 0x13 पूर्ण,
	अणु 0x375c, 0x40 पूर्ण,
	अणु 0x375d, 0x02 पूर्ण,
	अणु 0x375e, 0x00 पूर्ण,
	अणु 0x375f, 0x14 पूर्ण,
	अणु 0x3767, 0x1c पूर्ण,
	अणु 0x3768, 0x04 पूर्ण,
	अणु 0x3769, 0x20 पूर्ण,
	अणु 0x376c, 0xc0 पूर्ण,
	अणु 0x376d, 0xc0 पूर्ण,
	अणु 0x376a, 0x08 पूर्ण,
	अणु 0x3761, 0x00 पूर्ण,
	अणु 0x3762, 0x00 पूर्ण,
	अणु 0x3763, 0x00 पूर्ण,
	अणु 0x3766, 0xff पूर्ण,
	अणु 0x376b, 0x42 पूर्ण,
	अणु 0x3772, 0x23 पूर्ण,
	अणु 0x3773, 0x02 पूर्ण,
	अणु 0x3774, 0x16 पूर्ण,
	अणु 0x3775, 0x12 पूर्ण,
	अणु 0x3776, 0x08 पूर्ण,
	अणु 0x37a0, 0x44 पूर्ण,
	अणु 0x37a1, 0x3d पूर्ण,
	अणु 0x37a2, 0x3d पूर्ण,
	अणु 0x37a3, 0x01 पूर्ण,
	अणु 0x37a4, 0x00 पूर्ण,
	अणु 0x37a5, 0x08 पूर्ण,
	अणु 0x37a6, 0x00 पूर्ण,
	अणु 0x37a7, 0x44 पूर्ण,
	अणु 0x37a8, 0x58 पूर्ण,
	अणु 0x37a9, 0x58 पूर्ण,
	अणु 0x3760, 0x00 पूर्ण,
	अणु 0x376f, 0x01 पूर्ण,
	अणु 0x37aa, 0x44 पूर्ण,
	अणु 0x37ab, 0x2e पूर्ण,
	अणु 0x37ac, 0x2e पूर्ण,
	अणु 0x37ad, 0x33 पूर्ण,
	अणु 0x37ae, 0x0d पूर्ण,
	अणु 0x37af, 0x0d पूर्ण,
	अणु 0x37b0, 0x00 पूर्ण,
	अणु 0x37b1, 0x00 पूर्ण,
	अणु 0x37b2, 0x00 पूर्ण,
	अणु 0x37b3, 0x42 पूर्ण,
	अणु 0x37b4, 0x42 पूर्ण,
	अणु 0x37b5, 0x33 पूर्ण,
	अणु 0x37b6, 0x00 पूर्ण,
	अणु 0x37b7, 0x00 पूर्ण,
	अणु 0x37b8, 0x00 पूर्ण,
	अणु 0x37b9, 0xff पूर्ण,

	/* ADC Sync */

	अणु 0x4503, 0x10 पूर्ण,
पूर्ण;

अटल स्थिर s64 ov8865_link_freq_menu[] = अणु
	360000000,
पूर्ण;

अटल स्थिर अक्षर *स्थिर ov8865_test_pattern_menu[] = अणु
	"Disabled",
	"Random data",
	"Color bars",
	"Color bars with rolling bar",
	"Color squares",
	"Color squares with rolling bar"
पूर्ण;

अटल स्थिर u8 ov8865_test_pattern_bits[] = अणु
	0,
	OV8865_PRE_CTRL0_PATTERN_EN | OV8865_PRE_CTRL0_PATTERN_RANDOM_DATA,
	OV8865_PRE_CTRL0_PATTERN_EN | OV8865_PRE_CTRL0_PATTERN_COLOR_BARS,
	OV8865_PRE_CTRL0_PATTERN_EN | OV8865_PRE_CTRL0_ROLLING_BAR_EN |
	OV8865_PRE_CTRL0_PATTERN_COLOR_BARS,
	OV8865_PRE_CTRL0_PATTERN_EN | OV8865_PRE_CTRL0_PATTERN_COLOR_SQUARES,
	OV8865_PRE_CTRL0_PATTERN_EN | OV8865_PRE_CTRL0_ROLLING_BAR_EN |
	OV8865_PRE_CTRL0_PATTERN_COLOR_SQUARES,
पूर्ण;

/* Input/Output */

अटल पूर्णांक ov8865_पढ़ो(काष्ठा ov8865_sensor *sensor, u16 address, u8 *value)
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

अटल पूर्णांक ov8865_ग_लिखो(काष्ठा ov8865_sensor *sensor, u16 address, u8 value)
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

अटल पूर्णांक ov8865_ग_लिखो_sequence(काष्ठा ov8865_sensor *sensor,
				 स्थिर काष्ठा ov8865_रेजिस्टर_value *sequence,
				 अचिन्हित पूर्णांक sequence_count)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < sequence_count; i++) अणु
		ret = ov8865_ग_लिखो(sensor, sequence[i].address,
				   sequence[i].value);
		अगर (ret)
			अवरोध;

		अगर (sequence[i].delay_ms)
			msleep(sequence[i].delay_ms);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ov8865_update_bits(काष्ठा ov8865_sensor *sensor, u16 address,
			      u8 mask, u8 bits)
अणु
	u8 value = 0;
	पूर्णांक ret;

	ret = ov8865_पढ़ो(sensor, address, &value);
	अगर (ret)
		वापस ret;

	value &= ~mask;
	value |= bits;

	वापस ov8865_ग_लिखो(sensor, address, value);
पूर्ण

/* Sensor */

अटल पूर्णांक ov8865_sw_reset(काष्ठा ov8865_sensor *sensor)
अणु
	वापस ov8865_ग_लिखो(sensor, OV8865_SW_RESET_REG, OV8865_SW_RESET_RESET);
पूर्ण

अटल पूर्णांक ov8865_sw_standby(काष्ठा ov8865_sensor *sensor, पूर्णांक standby)
अणु
	u8 value = 0;

	अगर (!standby)
		value = OV8865_SW_STANDBY_STREAM_ON;

	वापस ov8865_ग_लिखो(sensor, OV8865_SW_STANDBY_REG, value);
पूर्ण

अटल पूर्णांक ov8865_chip_id_check(काष्ठा ov8865_sensor *sensor)
अणु
	u16 regs[] = अणु OV8865_CHIP_ID_HH_REG, OV8865_CHIP_ID_H_REG,
		       OV8865_CHIP_ID_L_REG पूर्ण;
	u8 values[] = अणु OV8865_CHIP_ID_HH_VALUE, OV8865_CHIP_ID_H_VALUE,
			OV8865_CHIP_ID_L_VALUE पूर्ण;
	अचिन्हित पूर्णांक i;
	u8 value;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++) अणु
		ret = ov8865_पढ़ो(sensor, regs[i], &value);
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

अटल पूर्णांक ov8865_अक्षरge_pump_configure(काष्ठा ov8865_sensor *sensor)
अणु
	वापस ov8865_ग_लिखो(sensor, OV8865_PUMP_CLK_DIV_REG,
			    OV8865_PUMP_CLK_DIV_PUMP_P(1));
पूर्ण

अटल पूर्णांक ov8865_mipi_configure(काष्ठा ov8865_sensor *sensor)
अणु
	काष्ठा v4l2_fwnode_bus_mipi_csi2 *bus_mipi_csi2 =
		&sensor->endpoपूर्णांक.bus.mipi_csi2;
	अचिन्हित पूर्णांक lanes_count = bus_mipi_csi2->num_data_lanes;
	पूर्णांक ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_MIPI_SC_CTRL0_REG,
			   OV8865_MIPI_SC_CTRL0_LANES(lanes_count) |
			   OV8865_MIPI_SC_CTRL0_MIPI_EN |
			   OV8865_MIPI_SC_CTRL0_UNKNOWN);
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_MIPI_SC_CTRL2_REG,
			   OV8865_MIPI_SC_CTRL2_PD_MIPI_RST_SYNC);
	अगर (ret)
		वापस ret;

	अगर (lanes_count >= 2) अणु
		ret = ov8865_ग_लिखो(sensor, OV8865_MIPI_LANE_SEL01_REG,
				   OV8865_MIPI_LANE_SEL01_LANE0(0) |
				   OV8865_MIPI_LANE_SEL01_LANE1(1));
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (lanes_count >= 4) अणु
		ret = ov8865_ग_लिखो(sensor, OV8865_MIPI_LANE_SEL23_REG,
				   OV8865_MIPI_LANE_SEL23_LANE2(2) |
				   OV8865_MIPI_LANE_SEL23_LANE3(3));
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = ov8865_update_bits(sensor, OV8865_CLK_SEL1_REG,
				 OV8865_CLK_SEL1_MIPI_खातापूर्ण,
				 OV8865_CLK_SEL1_MIPI_खातापूर्ण);
	अगर (ret)
		वापस ret;

	/*
	 * This value might need to change depending on PCLK rate,
	 * but it's unclear how. This value seems to generally work
	 * जबतक the शेष value was found to cause transmission errors.
	 */
	वापस ov8865_ग_लिखो(sensor, OV8865_MIPI_PCLK_PERIOD_REG, 0x16);
पूर्ण

अटल पूर्णांक ov8865_black_level_configure(काष्ठा ov8865_sensor *sensor)
अणु
	पूर्णांक ret;

	/* Trigger BLC on relevant events and enable filter. */
	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_CTRL0_REG,
			   OV8865_BLC_CTRL0_TRIG_RANGE_EN |
			   OV8865_BLC_CTRL0_TRIG_FORMAT_EN |
			   OV8865_BLC_CTRL0_TRIG_GAIN_EN |
			   OV8865_BLC_CTRL0_TRIG_EXPOSURE_EN |
			   OV8865_BLC_CTRL0_FILTER_EN);
	अगर (ret)
		वापस ret;

	/* Lower BLC offset trigger threshold. */
	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_CTRLD_REG,
			   OV8865_BLC_CTRLD_OFFSET_TRIGGER(16));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_CTRL1F_REG, 0);
	अगर (ret)
		वापस ret;

	/* Increase BLC offset maximum limit. */
	वापस ov8865_ग_लिखो(sensor, OV8865_BLC_OFFSET_LIMIT_REG,
			    OV8865_BLC_OFFSET_LIMIT(63));
पूर्ण

अटल पूर्णांक ov8865_isp_configure(काष्ठा ov8865_sensor *sensor)
अणु
	पूर्णांक ret;

	/* Disable lens correction. */
	ret = ov8865_ग_लिखो(sensor, OV8865_ISP_CTRL0_REG,
			   OV8865_ISP_CTRL0_WHITE_BALANCE_EN |
			   OV8865_ISP_CTRL0_DPC_BLACK_EN |
			   OV8865_ISP_CTRL0_DPC_WHITE_EN);
	अगर (ret)
		वापस ret;

	वापस ov8865_ग_लिखो(sensor, OV8865_ISP_CTRL1_REG,
			    OV8865_ISP_CTRL1_BLC_EN);
पूर्ण

अटल अचिन्हित दीर्घ ov8865_mode_pll1_rate(काष्ठा ov8865_sensor *sensor,
					   स्थिर काष्ठा ov8865_mode *mode)
अणु
	स्थिर काष्ठा ov8865_pll1_config *config = mode->pll1_config;
	अचिन्हित दीर्घ extclk_rate;
	अचिन्हित दीर्घ pll1_rate;

	extclk_rate = clk_get_rate(sensor->extclk);
	pll1_rate = extclk_rate * config->pll_mul / config->pll_pre_भाग_half;

	चयन (config->pll_pre_भाग) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		pll1_rate *= 3;
		pll1_rate /= 2;
		अवरोध;
	हाल 3:
		pll1_rate *= 5;
		pll1_rate /= 2;
		अवरोध;
	हाल 4:
		pll1_rate /= 3;
		अवरोध;
	हाल 5:
		pll1_rate /= 4;
		अवरोध;
	हाल 7:
		pll1_rate /= 8;
		अवरोध;
	शेष:
		pll1_rate /= config->pll_pre_भाग;
		अवरोध;
	पूर्ण

	वापस pll1_rate;
पूर्ण

अटल पूर्णांक ov8865_mode_pll1_configure(काष्ठा ov8865_sensor *sensor,
				      स्थिर काष्ठा ov8865_mode *mode,
				      u32 mbus_code)
अणु
	स्थिर काष्ठा ov8865_pll1_config *config = mode->pll1_config;
	u8 value;
	पूर्णांक ret;

	चयन (mbus_code) अणु
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
		value = OV8865_MIPI_BIT_SEL(10);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = ov8865_ग_लिखो(sensor, OV8865_MIPI_BIT_SEL_REG, value);
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_PLL_CTRLA_REG,
			   OV8865_PLL_CTRLA_PRE_DIV_HALF(config->pll_pre_भाग_half));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_PLL_CTRL0_REG,
			   OV8865_PLL_CTRL0_PRE_DIV(config->pll_pre_भाग));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_PLL_CTRL1_REG,
			   OV8865_PLL_CTRL1_MUL_H(config->pll_mul));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_PLL_CTRL2_REG,
			   OV8865_PLL_CTRL2_MUL_L(config->pll_mul));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_PLL_CTRL3_REG,
			   OV8865_PLL_CTRL3_M_DIV(config->m_भाग));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_PLL_CTRL4_REG,
			   OV8865_PLL_CTRL4_MIPI_DIV(config->mipi_भाग));
	अगर (ret)
		वापस ret;

	ret = ov8865_update_bits(sensor, OV8865_PCLK_SEL_REG,
				 OV8865_PCLK_SEL_PCLK_DIV_MASK,
				 OV8865_PCLK_SEL_PCLK_DIV(config->pclk_भाग));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_PLL_CTRL5_REG,
			   OV8865_PLL_CTRL5_SYS_PRE_DIV(config->sys_pre_भाग));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_PLL_CTRL6_REG,
			   OV8865_PLL_CTRL6_SYS_DIV(config->sys_भाग));
	अगर (ret)
		वापस ret;

	वापस ov8865_update_bits(sensor, OV8865_PLL_CTRL1E_REG,
				  OV8865_PLL_CTRL1E_PLL1_NO_LAT,
				  OV8865_PLL_CTRL1E_PLL1_NO_LAT);
पूर्ण

अटल पूर्णांक ov8865_mode_pll2_configure(काष्ठा ov8865_sensor *sensor,
				      स्थिर काष्ठा ov8865_mode *mode)
अणु
	स्थिर काष्ठा ov8865_pll2_config *config = mode->pll2_config;
	पूर्णांक ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_PLL_CTRL12_REG,
			   OV8865_PLL_CTRL12_PRE_DIV_HALF(config->pll_pre_भाग_half) |
			   OV8865_PLL_CTRL12_DAC_DIV(config->dac_भाग));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_PLL_CTRLB_REG,
			   OV8865_PLL_CTRLB_PRE_DIV(config->pll_pre_भाग));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_PLL_CTRLC_REG,
			   OV8865_PLL_CTRLC_MUL_H(config->pll_mul));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_PLL_CTRLD_REG,
			   OV8865_PLL_CTRLD_MUL_L(config->pll_mul));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_PLL_CTRLF_REG,
			   OV8865_PLL_CTRLF_SYS_PRE_DIV(config->sys_pre_भाग));
	अगर (ret)
		वापस ret;

	वापस ov8865_ग_लिखो(sensor, OV8865_PLL_CTRLE_REG,
			    OV8865_PLL_CTRLE_SYS_DIV(config->sys_भाग));
पूर्ण

अटल पूर्णांक ov8865_mode_sclk_configure(काष्ठा ov8865_sensor *sensor,
				      स्थिर काष्ठा ov8865_mode *mode)
अणु
	स्थिर काष्ठा ov8865_sclk_config *config = mode->sclk_config;
	पूर्णांक ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_CLK_SEL0_REG,
			   OV8865_CLK_SEL0_PLL1_SYS_SEL(config->sys_sel));
	अगर (ret)
		वापस ret;

	ret = ov8865_update_bits(sensor, OV8865_CLK_SEL1_REG,
				 OV8865_CLK_SEL1_PLL_SCLK_SEL_MASK,
				 OV8865_CLK_SEL1_PLL_SCLK_SEL(config->sclk_sel));
	अगर (ret)
		वापस ret;

	वापस ov8865_ग_लिखो(sensor, OV8865_SCLK_CTRL_REG,
			    OV8865_SCLK_CTRL_UNKNOWN |
			    OV8865_SCLK_CTRL_SCLK_DIV(config->sclk_भाग) |
			    OV8865_SCLK_CTRL_SCLK_PRE_DIV(config->sclk_pre_भाग));
पूर्ण

अटल पूर्णांक ov8865_mode_binning_configure(काष्ठा ov8865_sensor *sensor,
					 स्थिर काष्ठा ov8865_mode *mode)
अणु
	अचिन्हित पूर्णांक variopixel_hsub_coef, variopixel_vsub_coef;
	u8 value;
	पूर्णांक ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_FORMAT1_REG, 0);
	अगर (ret)
		वापस ret;

	value = OV8865_FORMAT2_HSYNC_EN;

	अगर (mode->binning_x)
		value |= OV8865_FORMAT2_FST_HBIN_EN;

	अगर (mode->binning_y)
		value |= OV8865_FORMAT2_FST_VBIN_EN;

	अगर (mode->sync_hbin)
		value |= OV8865_FORMAT2_SYNC_HBIN_EN;

	अगर (mode->horz_var2)
		value |= OV8865_FORMAT2_ISP_HORZ_VAR2_EN;

	ret = ov8865_ग_लिखो(sensor, OV8865_FORMAT2_REG, value);
	अगर (ret)
		वापस ret;

	ret = ov8865_update_bits(sensor, OV8865_ISP_CTRL2_REG,
				 OV8865_ISP_CTRL2_VARIOPIXEL_EN,
				 mode->variopixel ?
				 OV8865_ISP_CTRL2_VARIOPIXEL_EN : 0);
	अगर (ret)
		वापस ret;

	अगर (mode->variopixel) अणु
		/* VarioPixel coefs needs to be > 1. */
		variopixel_hsub_coef = mode->variopixel_hsub_coef;
		variopixel_vsub_coef = mode->variopixel_vsub_coef;
	पूर्ण अन्यथा अणु
		variopixel_hsub_coef = 1;
		variopixel_vsub_coef = 1;
	पूर्ण

	ret = ov8865_ग_लिखो(sensor, OV8865_VAP_CTRL1_REG,
			   OV8865_VAP_CTRL1_HSUB_COEF(variopixel_hsub_coef) |
			   OV8865_VAP_CTRL1_VSUB_COEF(variopixel_vsub_coef));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_INC_X_ODD_REG,
			   OV8865_INC_X_ODD(mode->inc_x_odd));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_INC_X_EVEN_REG,
			   OV8865_INC_X_EVEN(mode->inc_x_even));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_INC_Y_ODD_REG,
			   OV8865_INC_Y_ODD(mode->inc_y_odd));
	अगर (ret)
		वापस ret;

	वापस ov8865_ग_लिखो(sensor, OV8865_INC_Y_EVEN_REG,
			    OV8865_INC_Y_EVEN(mode->inc_y_even));
पूर्ण

अटल पूर्णांक ov8865_mode_black_level_configure(काष्ठा ov8865_sensor *sensor,
					     स्थिर काष्ठा ov8865_mode *mode)
अणु
	पूर्णांक ret;

	/* Note that a zero value क्रम blc_col_shअगरt_mask is the शेष 256. */
	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_CTRL1_REG,
			   mode->blc_col_shअगरt_mask |
			   OV8865_BLC_CTRL1_OFFSET_LIMIT_EN);
	अगर (ret)
		वापस ret;

	/* BLC top zero line */

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_TOP_ZLINE_START_REG,
			   OV8865_BLC_TOP_ZLINE_START(mode->blc_top_zero_line_start));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_TOP_ZLINE_NUM_REG,
			   OV8865_BLC_TOP_ZLINE_NUM(mode->blc_top_zero_line_num));
	अगर (ret)
		वापस ret;

	/* BLC top black line */

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_TOP_BLKLINE_START_REG,
			   OV8865_BLC_TOP_BLKLINE_START(mode->blc_top_black_line_start));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_TOP_BLKLINE_NUM_REG,
			   OV8865_BLC_TOP_BLKLINE_NUM(mode->blc_top_black_line_num));
	अगर (ret)
		वापस ret;

	/* BLC bottom zero line */

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_BOT_ZLINE_START_REG,
			   OV8865_BLC_BOT_ZLINE_START(mode->blc_bottom_zero_line_start));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_BOT_ZLINE_NUM_REG,
			   OV8865_BLC_BOT_ZLINE_NUM(mode->blc_bottom_zero_line_num));
	अगर (ret)
		वापस ret;

	/* BLC bottom black line */

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_BOT_BLKLINE_START_REG,
			   OV8865_BLC_BOT_BLKLINE_START(mode->blc_bottom_black_line_start));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_BOT_BLKLINE_NUM_REG,
			   OV8865_BLC_BOT_BLKLINE_NUM(mode->blc_bottom_black_line_num));
	अगर (ret)
		वापस ret;

	/* BLC anchor */

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_ANCHOR_LEFT_START_H_REG,
			   OV8865_BLC_ANCHOR_LEFT_START_H(mode->blc_anchor_left_start));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_ANCHOR_LEFT_START_L_REG,
			   OV8865_BLC_ANCHOR_LEFT_START_L(mode->blc_anchor_left_start));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_ANCHOR_LEFT_END_H_REG,
			   OV8865_BLC_ANCHOR_LEFT_END_H(mode->blc_anchor_left_end));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_ANCHOR_LEFT_END_L_REG,
			   OV8865_BLC_ANCHOR_LEFT_END_L(mode->blc_anchor_left_end));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_ANCHOR_RIGHT_START_H_REG,
			   OV8865_BLC_ANCHOR_RIGHT_START_H(mode->blc_anchor_right_start));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_ANCHOR_RIGHT_START_L_REG,
			   OV8865_BLC_ANCHOR_RIGHT_START_L(mode->blc_anchor_right_start));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_BLC_ANCHOR_RIGHT_END_H_REG,
			   OV8865_BLC_ANCHOR_RIGHT_END_H(mode->blc_anchor_right_end));
	अगर (ret)
		वापस ret;

	वापस ov8865_ग_लिखो(sensor, OV8865_BLC_ANCHOR_RIGHT_END_L_REG,
			    OV8865_BLC_ANCHOR_RIGHT_END_L(mode->blc_anchor_right_end));
पूर्ण

अटल पूर्णांक ov8865_mode_configure(काष्ठा ov8865_sensor *sensor,
				 स्थिर काष्ठा ov8865_mode *mode, u32 mbus_code)
अणु
	पूर्णांक ret;

	/* Output Size X */

	ret = ov8865_ग_लिखो(sensor, OV8865_OUTPUT_SIZE_X_H_REG,
			   OV8865_OUTPUT_SIZE_X_H(mode->output_size_x));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_OUTPUT_SIZE_X_L_REG,
			   OV8865_OUTPUT_SIZE_X_L(mode->output_size_x));
	अगर (ret)
		वापस ret;

	/* Horizontal Total Size */

	ret = ov8865_ग_लिखो(sensor, OV8865_HTS_H_REG, OV8865_HTS_H(mode->hts));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_HTS_L_REG, OV8865_HTS_L(mode->hts));
	अगर (ret)
		वापस ret;

	/* Output Size Y */

	ret = ov8865_ग_लिखो(sensor, OV8865_OUTPUT_SIZE_Y_H_REG,
			   OV8865_OUTPUT_SIZE_Y_H(mode->output_size_y));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_OUTPUT_SIZE_Y_L_REG,
			   OV8865_OUTPUT_SIZE_Y_L(mode->output_size_y));
	अगर (ret)
		वापस ret;

	/* Vertical Total Size */

	ret = ov8865_ग_लिखो(sensor, OV8865_VTS_H_REG, OV8865_VTS_H(mode->vts));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_VTS_L_REG, OV8865_VTS_L(mode->vts));
	अगर (ret)
		वापस ret;

	अगर (mode->size_स्वतः) अणु
		/* Auto Size */

		ret = ov8865_ग_लिखो(sensor, OV8865_AUTO_SIZE_CTRL_REG,
				   OV8865_AUTO_SIZE_CTRL_OFFSET_Y_REG |
				   OV8865_AUTO_SIZE_CTRL_OFFSET_X_REG |
				   OV8865_AUTO_SIZE_CTRL_CROP_END_Y_REG |
				   OV8865_AUTO_SIZE_CTRL_CROP_END_X_REG |
				   OV8865_AUTO_SIZE_CTRL_CROP_START_Y_REG |
				   OV8865_AUTO_SIZE_CTRL_CROP_START_X_REG);
		अगर (ret)
			वापस ret;

		ret = ov8865_ग_लिखो(sensor, OV8865_AUTO_SIZE_BOUNDARIES_REG,
				   OV8865_AUTO_SIZE_BOUNDARIES_Y(mode->size_स्वतः_boundary_y) |
				   OV8865_AUTO_SIZE_BOUNDARIES_X(mode->size_स्वतः_boundary_x));
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* Crop Start X */

		ret = ov8865_ग_लिखो(sensor, OV8865_CROP_START_X_H_REG,
				   OV8865_CROP_START_X_H(mode->crop_start_x));
		अगर (ret)
			वापस ret;

		ret = ov8865_ग_लिखो(sensor, OV8865_CROP_START_X_L_REG,
				   OV8865_CROP_START_X_L(mode->crop_start_x));
		अगर (ret)
			वापस ret;

		/* Offset X */

		ret = ov8865_ग_लिखो(sensor, OV8865_OFFSET_X_H_REG,
				   OV8865_OFFSET_X_H(mode->offset_x));
		अगर (ret)
			वापस ret;

		ret = ov8865_ग_लिखो(sensor, OV8865_OFFSET_X_L_REG,
				   OV8865_OFFSET_X_L(mode->offset_x));
		अगर (ret)
			वापस ret;

		/* Crop End X */

		ret = ov8865_ग_लिखो(sensor, OV8865_CROP_END_X_H_REG,
				   OV8865_CROP_END_X_H(mode->crop_end_x));
		अगर (ret)
			वापस ret;

		ret = ov8865_ग_लिखो(sensor, OV8865_CROP_END_X_L_REG,
				   OV8865_CROP_END_X_L(mode->crop_end_x));
		अगर (ret)
			वापस ret;

		/* Crop Start Y */

		ret = ov8865_ग_लिखो(sensor, OV8865_CROP_START_Y_H_REG,
				   OV8865_CROP_START_Y_H(mode->crop_start_y));
		अगर (ret)
			वापस ret;

		ret = ov8865_ग_लिखो(sensor, OV8865_CROP_START_Y_L_REG,
				   OV8865_CROP_START_Y_L(mode->crop_start_y));
		अगर (ret)
			वापस ret;

		/* Offset Y */

		ret = ov8865_ग_लिखो(sensor, OV8865_OFFSET_Y_H_REG,
				   OV8865_OFFSET_Y_H(mode->offset_y));
		अगर (ret)
			वापस ret;

		ret = ov8865_ग_लिखो(sensor, OV8865_OFFSET_Y_L_REG,
				   OV8865_OFFSET_Y_L(mode->offset_y));
		अगर (ret)
			वापस ret;

		/* Crop End Y */

		ret = ov8865_ग_लिखो(sensor, OV8865_CROP_END_Y_H_REG,
				   OV8865_CROP_END_Y_H(mode->crop_end_y));
		अगर (ret)
			वापस ret;

		ret = ov8865_ग_लिखो(sensor, OV8865_CROP_END_Y_L_REG,
				   OV8865_CROP_END_Y_L(mode->crop_end_y));
		अगर (ret)
			वापस ret;
	पूर्ण

	/* VFIFO */

	ret = ov8865_ग_लिखो(sensor, OV8865_VFIFO_READ_START_H_REG,
			   OV8865_VFIFO_READ_START_H(mode->vfअगरo_पढ़ो_start));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_VFIFO_READ_START_L_REG,
			   OV8865_VFIFO_READ_START_L(mode->vfअगरo_पढ़ो_start));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_ABLC_NUM_REG,
			   OV8865_ABLC_NUM(mode->ablc_num));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_ZLINE_NUM_REG,
			   OV8865_ZLINE_NUM(mode->zline_num));
	अगर (ret)
		वापस ret;

	/* Binning */

	ret = ov8865_mode_binning_configure(sensor, mode);
	अगर (ret)
		वापस ret;

	/* Black Level */

	ret = ov8865_mode_black_level_configure(sensor, mode);
	अगर (ret)
		वापस ret;

	/* PLLs */

	ret = ov8865_mode_pll1_configure(sensor, mode, mbus_code);
	अगर (ret)
		वापस ret;

	ret = ov8865_mode_pll2_configure(sensor, mode);
	अगर (ret)
		वापस ret;

	ret = ov8865_mode_sclk_configure(sensor, mode);
	अगर (ret)
		वापस ret;

	/* Extra रेजिस्टरs */

	अगर (mode->रेजिस्टर_values) अणु
		ret = ov8865_ग_लिखो_sequence(sensor, mode->रेजिस्टर_values,
					    mode->रेजिस्टर_values_count);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ ov8865_mode_mipi_clk_rate(काष्ठा ov8865_sensor *sensor,
					       स्थिर काष्ठा ov8865_mode *mode)
अणु
	स्थिर काष्ठा ov8865_pll1_config *config = mode->pll1_config;
	अचिन्हित दीर्घ pll1_rate;

	pll1_rate = ov8865_mode_pll1_rate(sensor, mode);

	वापस pll1_rate / config->m_भाग / 2;
पूर्ण

/* Exposure */

अटल पूर्णांक ov8865_exposure_configure(काष्ठा ov8865_sensor *sensor, u32 exposure)
अणु
	पूर्णांक ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_EXPOSURE_CTRL_HH_REG,
			   OV8865_EXPOSURE_CTRL_HH(exposure));
	अगर (ret)
		वापस ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_EXPOSURE_CTRL_H_REG,
			   OV8865_EXPOSURE_CTRL_H(exposure));
	अगर (ret)
		वापस ret;

	वापस ov8865_ग_लिखो(sensor, OV8865_EXPOSURE_CTRL_L_REG,
			    OV8865_EXPOSURE_CTRL_L(exposure));
पूर्ण

/* Gain */

अटल पूर्णांक ov8865_gain_configure(काष्ठा ov8865_sensor *sensor, u32 gain)
अणु
	पूर्णांक ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_GAIN_CTRL_H_REG,
			   OV8865_GAIN_CTRL_H(gain));
	अगर (ret)
		वापस ret;

	वापस ov8865_ग_लिखो(sensor, OV8865_GAIN_CTRL_L_REG,
			    OV8865_GAIN_CTRL_L(gain));
पूर्ण

/* White Balance */

अटल पूर्णांक ov8865_red_balance_configure(काष्ठा ov8865_sensor *sensor,
					u32 red_balance)
अणु
	पूर्णांक ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_ISP_GAIN_RED_H_REG,
			   OV8865_ISP_GAIN_RED_H(red_balance));
	अगर (ret)
		वापस ret;

	वापस ov8865_ग_लिखो(sensor, OV8865_ISP_GAIN_RED_L_REG,
			    OV8865_ISP_GAIN_RED_L(red_balance));
पूर्ण

अटल पूर्णांक ov8865_blue_balance_configure(काष्ठा ov8865_sensor *sensor,
					 u32 blue_balance)
अणु
	पूर्णांक ret;

	ret = ov8865_ग_लिखो(sensor, OV8865_ISP_GAIN_BLUE_H_REG,
			   OV8865_ISP_GAIN_BLUE_H(blue_balance));
	अगर (ret)
		वापस ret;

	वापस ov8865_ग_लिखो(sensor, OV8865_ISP_GAIN_BLUE_L_REG,
			    OV8865_ISP_GAIN_BLUE_L(blue_balance));
पूर्ण

/* Flip */

अटल पूर्णांक ov8865_flip_vert_configure(काष्ठा ov8865_sensor *sensor, bool enable)
अणु
	u8 bits = OV8865_FORMAT1_FLIP_VERT_ISP_EN |
		  OV8865_FORMAT1_FLIP_VERT_SENSOR_EN;

	वापस ov8865_update_bits(sensor, OV8865_FORMAT1_REG, bits,
				  enable ? bits : 0);
पूर्ण

अटल पूर्णांक ov8865_flip_horz_configure(काष्ठा ov8865_sensor *sensor, bool enable)
अणु
	u8 bits = OV8865_FORMAT2_FLIP_HORZ_ISP_EN |
		  OV8865_FORMAT2_FLIP_HORZ_SENSOR_EN;

	वापस ov8865_update_bits(sensor, OV8865_FORMAT2_REG, bits,
				  enable ? bits : 0);
पूर्ण

/* Test Pattern */

अटल पूर्णांक ov8865_test_pattern_configure(काष्ठा ov8865_sensor *sensor,
					 अचिन्हित पूर्णांक index)
अणु
	अगर (index >= ARRAY_SIZE(ov8865_test_pattern_bits))
		वापस -EINVAL;

	वापस ov8865_ग_लिखो(sensor, OV8865_PRE_CTRL0_REG,
			    ov8865_test_pattern_bits[index]);
पूर्ण

/* State */

अटल पूर्णांक ov8865_state_mipi_configure(काष्ठा ov8865_sensor *sensor,
				       स्थिर काष्ठा ov8865_mode *mode,
				       u32 mbus_code)
अणु
	काष्ठा ov8865_ctrls *ctrls = &sensor->ctrls;
	काष्ठा v4l2_fwnode_bus_mipi_csi2 *bus_mipi_csi2 =
		&sensor->endpoपूर्णांक.bus.mipi_csi2;
	अचिन्हित दीर्घ mipi_clk_rate;
	अचिन्हित पूर्णांक bits_per_sample;
	अचिन्हित पूर्णांक lanes_count;
	अचिन्हित पूर्णांक i, j;
	s64 mipi_pixel_rate;

	mipi_clk_rate = ov8865_mode_mipi_clk_rate(sensor, mode);
	अगर (!mipi_clk_rate)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(ov8865_link_freq_menu); i++) अणु
		s64 freq = ov8865_link_freq_menu[i];

		अगर (freq == mipi_clk_rate)
			अवरोध;
	पूर्ण

	क्रम (j = 0; j < sensor->endpoपूर्णांक.nr_of_link_frequencies; j++) अणु
		u64 freq = sensor->endpoपूर्णांक.link_frequencies[j];

		अगर (freq == mipi_clk_rate)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(ov8865_link_freq_menu)) अणु
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

अटल पूर्णांक ov8865_state_configure(काष्ठा ov8865_sensor *sensor,
				  स्थिर काष्ठा ov8865_mode *mode,
				  u32 mbus_code)
अणु
	पूर्णांक ret;

	अगर (sensor->state.streaming)
		वापस -EBUSY;

	/* State will be configured at first घातer on otherwise. */
	अगर (pm_runसमय_enabled(sensor->dev) &&
	    !pm_runसमय_suspended(sensor->dev)) अणु
		ret = ov8865_mode_configure(sensor, mode, mbus_code);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = ov8865_state_mipi_configure(sensor, mode, mbus_code);
	अगर (ret)
		वापस ret;

	sensor->state.mode = mode;
	sensor->state.mbus_code = mbus_code;

	वापस 0;
पूर्ण

अटल पूर्णांक ov8865_state_init(काष्ठा ov8865_sensor *sensor)
अणु
	वापस ov8865_state_configure(sensor, &ov8865_modes[0],
				      ov8865_mbus_codes[0]);
पूर्ण

/* Sensor Base */

अटल पूर्णांक ov8865_sensor_init(काष्ठा ov8865_sensor *sensor)
अणु
	पूर्णांक ret;

	ret = ov8865_sw_reset(sensor);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to perform sw reset\n");
		वापस ret;
	पूर्ण

	ret = ov8865_sw_standby(sensor, 1);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to set sensor standby\n");
		वापस ret;
	पूर्ण

	ret = ov8865_chip_id_check(sensor);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to check sensor chip id\n");
		वापस ret;
	पूर्ण

	ret = ov8865_ग_लिखो_sequence(sensor, ov8865_init_sequence,
				    ARRAY_SIZE(ov8865_init_sequence));
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to write init sequence\n");
		वापस ret;
	पूर्ण

	ret = ov8865_अक्षरge_pump_configure(sensor);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to configure pad\n");
		वापस ret;
	पूर्ण

	ret = ov8865_mipi_configure(sensor);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to configure MIPI\n");
		वापस ret;
	पूर्ण

	ret = ov8865_isp_configure(sensor);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to configure ISP\n");
		वापस ret;
	पूर्ण

	ret = ov8865_black_level_configure(sensor);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to configure black level\n");
		वापस ret;
	पूर्ण

	/* Configure current mode. */
	ret = ov8865_state_configure(sensor, sensor->state.mode,
				     sensor->state.mbus_code);
	अगर (ret) अणु
		dev_err(sensor->dev, "failed to configure state\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov8865_sensor_घातer(काष्ठा ov8865_sensor *sensor, bool on)
अणु
	/* Keep initialized to zero क्रम disable label. */
	पूर्णांक ret = 0;

	अगर (on) अणु
		gpiod_set_value_cansleep(sensor->reset, 1);
		gpiod_set_value_cansleep(sensor->घातerकरोwn, 1);

		ret = regulator_enable(sensor->करोvdd);
		अगर (ret) अणु
			dev_err(sensor->dev,
				"failed to enable DOVDD regulator\n");
			जाओ disable;
		पूर्ण

		ret = regulator_enable(sensor->avdd);
		अगर (ret) अणु
			dev_err(sensor->dev,
				"failed to enable AVDD regulator\n");
			जाओ disable;
		पूर्ण

		ret = regulator_enable(sensor->dvdd);
		अगर (ret) अणु
			dev_err(sensor->dev,
				"failed to enable DVDD regulator\n");
			जाओ disable;
		पूर्ण

		ret = clk_prepare_enable(sensor->extclk);
		अगर (ret) अणु
			dev_err(sensor->dev, "failed to enable EXTCLK clock\n");
			जाओ disable;
		पूर्ण

		gpiod_set_value_cansleep(sensor->reset, 0);
		gpiod_set_value_cansleep(sensor->घातerकरोwn, 0);

		/* Time to enter streaming mode according to घातer timings. */
		usleep_range(10000, 12000);
	पूर्ण अन्यथा अणु
disable:
		gpiod_set_value_cansleep(sensor->घातerकरोwn, 1);
		gpiod_set_value_cansleep(sensor->reset, 1);

		clk_disable_unprepare(sensor->extclk);

		regulator_disable(sensor->dvdd);
		regulator_disable(sensor->avdd);
		regulator_disable(sensor->करोvdd);
	पूर्ण

	वापस ret;
पूर्ण

/* Controls */

अटल पूर्णांक ov8865_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *subdev = ov8865_ctrl_subdev(ctrl);
	काष्ठा ov8865_sensor *sensor = ov8865_subdev_sensor(subdev);
	अचिन्हित पूर्णांक index;
	पूर्णांक ret;

	/* Wait क्रम the sensor to be on beक्रमe setting controls. */
	अगर (pm_runसमय_suspended(sensor->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE:
		ret = ov8865_exposure_configure(sensor, ctrl->val);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल V4L2_CID_GAIN:
		ret = ov8865_gain_configure(sensor, ctrl->val);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल V4L2_CID_RED_BALANCE:
		वापस ov8865_red_balance_configure(sensor, ctrl->val);
	हाल V4L2_CID_BLUE_BALANCE:
		वापस ov8865_blue_balance_configure(sensor, ctrl->val);
	हाल V4L2_CID_HFLIP:
		वापस ov8865_flip_horz_configure(sensor, !!ctrl->val);
	हाल V4L2_CID_VFLIP:
		वापस ov8865_flip_vert_configure(sensor, !!ctrl->val);
	हाल V4L2_CID_TEST_PATTERN:
		index = (अचिन्हित पूर्णांक)ctrl->val;
		वापस ov8865_test_pattern_configure(sensor, index);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov8865_ctrl_ops = अणु
	.s_ctrl			= ov8865_s_ctrl,
पूर्ण;

अटल पूर्णांक ov8865_ctrls_init(काष्ठा ov8865_sensor *sensor)
अणु
	काष्ठा ov8865_ctrls *ctrls = &sensor->ctrls;
	काष्ठा v4l2_ctrl_handler *handler = &ctrls->handler;
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &ov8865_ctrl_ops;
	पूर्णांक ret;

	v4l2_ctrl_handler_init(handler, 32);

	/* Use our mutex क्रम ctrl locking. */
	handler->lock = &sensor->mutex;

	/* Exposure */

	v4l2_ctrl_new_std(handler, ops, V4L2_CID_EXPOSURE, 16, 1048575, 16,
			  512);

	/* Gain */

	v4l2_ctrl_new_std(handler, ops, V4L2_CID_GAIN, 128, 8191, 128, 128);

	/* White Balance */

	v4l2_ctrl_new_std(handler, ops, V4L2_CID_RED_BALANCE, 1, 32767, 1,
			  1024);

	v4l2_ctrl_new_std(handler, ops, V4L2_CID_BLUE_BALANCE, 1, 32767, 1,
			  1024);

	/* Flip */

	v4l2_ctrl_new_std(handler, ops, V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(handler, ops, V4L2_CID_VFLIP, 0, 1, 1, 0);

	/* Test Pattern */

	v4l2_ctrl_new_std_menu_items(handler, ops, V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(ov8865_test_pattern_menu) - 1,
				     0, 0, ov8865_test_pattern_menu);

	/* MIPI CSI-2 */

	ctrls->link_freq =
		v4l2_ctrl_new_पूर्णांक_menu(handler, शून्य, V4L2_CID_LINK_FREQ,
				       ARRAY_SIZE(ov8865_link_freq_menu) - 1,
				       0, ov8865_link_freq_menu);

	ctrls->pixel_rate =
		v4l2_ctrl_new_std(handler, शून्य, V4L2_CID_PIXEL_RATE, 1,
				  पूर्णांक_उच्च, 1, 1);

	अगर (handler->error) अणु
		ret = handler->error;
		जाओ error_ctrls;
	पूर्ण

	ctrls->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;
	ctrls->pixel_rate->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	sensor->subdev.ctrl_handler = handler;

	वापस 0;

error_ctrls:
	v4l2_ctrl_handler_मुक्त(handler);

	वापस ret;
पूर्ण

/* Subdev Video Operations */

अटल पूर्णांक ov8865_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	काष्ठा ov8865_sensor *sensor = ov8865_subdev_sensor(subdev);
	काष्ठा ov8865_state *state = &sensor->state;
	पूर्णांक ret;

	अगर (enable) अणु
		ret = pm_runसमय_get_sync(sensor->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(sensor->dev);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_lock(&sensor->mutex);
	ret = ov8865_sw_standby(sensor, !enable);
	mutex_unlock(&sensor->mutex);

	अगर (ret)
		वापस ret;

	state->streaming = !!enable;

	अगर (!enable)
		pm_runसमय_put(sensor->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ov8865_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *पूर्णांकerval)
अणु
	काष्ठा ov8865_sensor *sensor = ov8865_subdev_sensor(subdev);
	स्थिर काष्ठा ov8865_mode *mode;

	mutex_lock(&sensor->mutex);

	mode = sensor->state.mode;
	पूर्णांकerval->पूर्णांकerval = mode->frame_पूर्णांकerval;

	mutex_unlock(&sensor->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov8865_subdev_video_ops = अणु
	.s_stream		= ov8865_s_stream,
	.g_frame_पूर्णांकerval	= ov8865_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval	= ov8865_g_frame_पूर्णांकerval,
पूर्ण;

/* Subdev Pad Operations */

अटल पूर्णांक ov8865_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *config,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code_क्रमागत)
अणु
	अगर (code_क्रमागत->index >= ARRAY_SIZE(ov8865_mbus_codes))
		वापस -EINVAL;

	code_क्रमागत->code = ov8865_mbus_codes[code_क्रमागत->index];

	वापस 0;
पूर्ण

अटल व्योम ov8865_mbus_क्रमmat_fill(काष्ठा v4l2_mbus_framefmt *mbus_क्रमmat,
				    u32 mbus_code,
				    स्थिर काष्ठा ov8865_mode *mode)
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

अटल पूर्णांक ov8865_get_fmt(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *config,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov8865_sensor *sensor = ov8865_subdev_sensor(subdev);
	काष्ठा v4l2_mbus_framefmt *mbus_क्रमmat = &क्रमmat->क्रमmat;

	mutex_lock(&sensor->mutex);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		*mbus_क्रमmat = *v4l2_subdev_get_try_क्रमmat(subdev, config,
							   क्रमmat->pad);
	अन्यथा
		ov8865_mbus_क्रमmat_fill(mbus_क्रमmat, sensor->state.mbus_code,
					sensor->state.mode);

	mutex_unlock(&sensor->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov8865_set_fmt(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *config,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov8865_sensor *sensor = ov8865_subdev_sensor(subdev);
	काष्ठा v4l2_mbus_framefmt *mbus_क्रमmat = &क्रमmat->क्रमmat;
	स्थिर काष्ठा ov8865_mode *mode;
	u32 mbus_code = 0;
	अचिन्हित पूर्णांक index;
	पूर्णांक ret = 0;

	mutex_lock(&sensor->mutex);

	अगर (sensor->state.streaming) अणु
		ret = -EBUSY;
		जाओ complete;
	पूर्ण

	/* Try to find requested mbus code. */
	क्रम (index = 0; index < ARRAY_SIZE(ov8865_mbus_codes); index++) अणु
		अगर (ov8865_mbus_codes[index] == mbus_क्रमmat->code) अणु
			mbus_code = mbus_क्रमmat->code;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Fallback to शेष. */
	अगर (!mbus_code)
		mbus_code = ov8865_mbus_codes[0];

	/* Find the mode with nearest dimensions. */
	mode = v4l2_find_nearest_size(ov8865_modes, ARRAY_SIZE(ov8865_modes),
				      output_size_x, output_size_y,
				      mbus_क्रमmat->width, mbus_क्रमmat->height);
	अगर (!mode) अणु
		ret = -EINVAL;
		जाओ complete;
	पूर्ण

	ov8865_mbus_क्रमmat_fill(mbus_क्रमmat, mbus_code, mode);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		*v4l2_subdev_get_try_क्रमmat(subdev, config, क्रमmat->pad) =
			*mbus_क्रमmat;
	अन्यथा अगर (sensor->state.mode != mode ||
		 sensor->state.mbus_code != mbus_code)
		ret = ov8865_state_configure(sensor, mode, mbus_code);

complete:
	mutex_unlock(&sensor->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ov8865_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *config,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *size_क्रमागत)
अणु
	स्थिर काष्ठा ov8865_mode *mode;

	अगर (size_क्रमागत->index >= ARRAY_SIZE(ov8865_modes))
		वापस -EINVAL;

	mode = &ov8865_modes[size_क्रमागत->index];

	size_क्रमागत->min_width = size_क्रमागत->max_width = mode->output_size_x;
	size_क्रमागत->min_height = size_क्रमागत->max_height = mode->output_size_y;

	वापस 0;
पूर्ण

अटल पूर्णांक ov8865_क्रमागत_frame_पूर्णांकerval(काष्ठा v4l2_subdev *subdev,
				      काष्ठा v4l2_subdev_pad_config *config,
				      काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *पूर्णांकerval_क्रमागत)
अणु
	स्थिर काष्ठा ov8865_mode *mode = शून्य;
	अचिन्हित पूर्णांक mode_index;
	अचिन्हित पूर्णांक पूर्णांकerval_index;

	अगर (पूर्णांकerval_क्रमागत->index > 0)
		वापस -EINVAL;
	/*
	 * Multiple modes with the same dimensions may have dअगरferent frame
	 * पूर्णांकervals, so look up each relevant mode.
	 */
	क्रम (mode_index = 0, पूर्णांकerval_index = 0;
	     mode_index < ARRAY_SIZE(ov8865_modes); mode_index++) अणु
		mode = &ov8865_modes[mode_index];

		अगर (mode->output_size_x == पूर्णांकerval_क्रमागत->width &&
		    mode->output_size_y == पूर्णांकerval_क्रमागत->height) अणु
			अगर (पूर्णांकerval_index == पूर्णांकerval_क्रमागत->index)
				अवरोध;

			पूर्णांकerval_index++;
		पूर्ण
	पूर्ण

	अगर (mode_index == ARRAY_SIZE(ov8865_modes) || !mode)
		वापस -EINVAL;

	पूर्णांकerval_क्रमागत->पूर्णांकerval = mode->frame_पूर्णांकerval;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov8865_subdev_pad_ops = अणु
	.क्रमागत_mbus_code		= ov8865_क्रमागत_mbus_code,
	.get_fmt		= ov8865_get_fmt,
	.set_fmt		= ov8865_set_fmt,
	.क्रमागत_frame_size	= ov8865_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval	= ov8865_क्रमागत_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov8865_subdev_ops = अणु
	.video		= &ov8865_subdev_video_ops,
	.pad		= &ov8865_subdev_pad_ops,
पूर्ण;

अटल पूर्णांक ov8865_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा ov8865_sensor *sensor = ov8865_subdev_sensor(subdev);
	काष्ठा ov8865_state *state = &sensor->state;
	पूर्णांक ret = 0;

	mutex_lock(&sensor->mutex);

	अगर (state->streaming) अणु
		ret = ov8865_sw_standby(sensor, true);
		अगर (ret)
			जाओ complete;
	पूर्ण

	ret = ov8865_sensor_घातer(sensor, false);
	अगर (ret)
		ov8865_sw_standby(sensor, false);

complete:
	mutex_unlock(&sensor->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ov8865_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा ov8865_sensor *sensor = ov8865_subdev_sensor(subdev);
	काष्ठा ov8865_state *state = &sensor->state;
	पूर्णांक ret = 0;

	mutex_lock(&sensor->mutex);

	ret = ov8865_sensor_घातer(sensor, true);
	अगर (ret)
		जाओ complete;

	ret = ov8865_sensor_init(sensor);
	अगर (ret)
		जाओ error_घातer;

	ret = __v4l2_ctrl_handler_setup(&sensor->ctrls.handler);
	अगर (ret)
		जाओ error_घातer;

	अगर (state->streaming) अणु
		ret = ov8865_sw_standby(sensor, false);
		अगर (ret)
			जाओ error_घातer;
	पूर्ण

	जाओ complete;

error_घातer:
	ov8865_sensor_घातer(sensor, false);

complete:
	mutex_unlock(&sensor->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ov8865_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा fwnode_handle *handle;
	काष्ठा ov8865_sensor *sensor;
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
	अगर (IS_ERR(sensor->करोvdd)) अणु
		dev_err(dev, "cannot get DOVDD (digital I/O) regulator\n");
		ret = PTR_ERR(sensor->करोvdd);
		जाओ error_endpoपूर्णांक;
	पूर्ण

	/* AVDD: analog */
	sensor->avdd = devm_regulator_get(dev, "avdd");
	अगर (IS_ERR(sensor->avdd)) अणु
		dev_err(dev, "cannot get AVDD (analog) regulator\n");
		ret = PTR_ERR(sensor->avdd);
		जाओ error_endpoपूर्णांक;
	पूर्ण

	/* External Clock */

	sensor->extclk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(sensor->extclk)) अणु
		dev_err(dev, "failed to get external clock\n");
		ret = PTR_ERR(sensor->extclk);
		जाओ error_endpoपूर्णांक;
	पूर्ण

	rate = clk_get_rate(sensor->extclk);
	अगर (rate != OV8865_EXTCLK_RATE) अणु
		dev_err(dev, "clock rate %lu Hz is unsupported\n", rate);
		ret = -EINVAL;
		जाओ error_endpoपूर्णांक;
	पूर्ण

	/* Subdev, entity and pad */

	subdev = &sensor->subdev;
	v4l2_i2c_subdev_init(subdev, client, &ov8865_subdev_ops);

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

	ret = ov8865_ctrls_init(sensor);
	अगर (ret)
		जाओ error_mutex;

	ret = ov8865_state_init(sensor);
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

अटल पूर्णांक ov8865_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा ov8865_sensor *sensor = ov8865_subdev_sensor(subdev);

	v4l2_async_unरेजिस्टर_subdev(subdev);
	pm_runसमय_disable(sensor->dev);
	v4l2_ctrl_handler_मुक्त(&sensor->ctrls.handler);
	mutex_destroy(&sensor->mutex);
	media_entity_cleanup(&subdev->entity);

	v4l2_fwnode_endpoपूर्णांक_मुक्त(&sensor->endpoपूर्णांक);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ov8865_pm_ops = अणु
	SET_RUNTIME_PM_OPS(ov8865_suspend, ov8865_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id ov8865_of_match[] = अणु
	अणु .compatible = "ovti,ov8865" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ov8865_of_match);

अटल काष्ठा i2c_driver ov8865_driver = अणु
	.driver = अणु
		.name = "ov8865",
		.of_match_table = ov8865_of_match,
		.pm = &ov8865_pm_ops,
	पूर्ण,
	.probe_new = ov8865_probe,
	.हटाओ	 = ov8865_हटाओ,
पूर्ण;

module_i2c_driver(ov8865_driver);

MODULE_AUTHOR("Paul Kocialkowski <paul.kocialkowski@bootlin.com>");
MODULE_DESCRIPTION("V4L2 driver for the OmniVision OV8865 image sensor");
MODULE_LICENSE("GPL v2");
