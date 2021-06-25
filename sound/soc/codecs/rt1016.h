<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * rt1016.h  --  RT1016 ALSA SoC audio amplअगरier driver
 *
 * Copyright 2020 Realtek Semiconductor Corp.
 * Author: Oder Chiou <oder_chiou@realtek.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित __RT1016_H__
#घोषणा __RT1016_H__

#घोषणा RT1016_DEVICE_ID_VAL	0x6595

#घोषणा RT1016_RESET		0x00
#घोषणा RT1016_PADS_CTRL_1	0x01
#घोषणा RT1016_PADS_CTRL_2	0x02
#घोषणा RT1016_I2C_CTRL		0x03
#घोषणा RT1016_VOL_CTRL_1	0x04
#घोषणा RT1016_VOL_CTRL_2	0x05
#घोषणा RT1016_VOL_CTRL_3	0x06
#घोषणा RT1016_ANA_CTRL_1	0x07
#घोषणा RT1016_MUX_SEL		0x08
#घोषणा RT1016_RX_I2S_CTRL	0x09
#घोषणा RT1016_ANA_FLAG		0x0a
#घोषणा RT1016_VERSION2_ID	0x0c
#घोषणा RT1016_VERSION1_ID	0x0d
#घोषणा RT1016_VENDER_ID	0x0e
#घोषणा RT1016_DEVICE_ID	0x0f
#घोषणा RT1016_ANA_CTRL_2	0x11
#घोषणा RT1016_TEST_SIGNAL	0x1c
#घोषणा RT1016_TEST_CTRL_1	0x1d
#घोषणा RT1016_TEST_CTRL_2	0x1e
#घोषणा RT1016_TEST_CTRL_3	0x1f
#घोषणा RT1016_CLOCK_1		0x20
#घोषणा RT1016_CLOCK_2		0x21
#घोषणा RT1016_CLOCK_3		0x22
#घोषणा RT1016_CLOCK_4		0x23
#घोषणा RT1016_CLOCK_5		0x24
#घोषणा RT1016_CLOCK_6		0x25
#घोषणा RT1016_CLOCK_7		0x26
#घोषणा RT1016_I2S_CTRL		0x40
#घोषणा RT1016_DAC_CTRL_1	0x60
#घोषणा RT1016_SC_CTRL_1	0x80
#घोषणा RT1016_SC_CTRL_2	0x81
#घोषणा RT1016_SC_CTRL_3	0x82
#घोषणा RT1016_SC_CTRL_4	0x83
#घोषणा RT1016_SIL_DET		0xa0
#घोषणा RT1016_SYS_CLK		0xc0
#घोषणा RT1016_BIAS_CUR		0xc1
#घोषणा RT1016_DAC_CTRL_2	0xc2
#घोषणा RT1016_LDO_CTRL		0xc3
#घोषणा RT1016_CLASSD_1		0xc4
#घोषणा RT1016_PLL1		0xc5
#घोषणा RT1016_PLL2		0xc6
#घोषणा RT1016_PLL3		0xc7
#घोषणा RT1016_CLASSD_2		0xc8
#घोषणा RT1016_CLASSD_OUT	0xc9
#घोषणा RT1016_CLASSD_3		0xca
#घोषणा RT1016_CLASSD_4		0xcb
#घोषणा RT1016_CLASSD_5		0xcc
#घोषणा RT1016_PWR_CTRL		0xcf

/* global definition */
#घोषणा RT1016_L_VOL_MASK			(0xff << 8)
#घोषणा RT1016_L_VOL_SFT			8
#घोषणा RT1016_R_VOL_MASK			(0xff)
#घोषणा RT1016_R_VOL_SFT			0

/* 0x04 */
#घोषणा RT1016_DA_MUTE_L_SFT			7
#घोषणा RT1016_DA_MUTE_R_SFT			6

/* 0x20 */
#घोषणा RT1016_CLK_SYS_SEL_MASK			(0x1 << 15)
#घोषणा RT1016_CLK_SYS_SEL_SFT			15
#घोषणा RT1016_CLK_SYS_SEL_MCLK			(0x0 << 15)
#घोषणा RT1016_CLK_SYS_SEL_PLL			(0x1 << 15)
#घोषणा RT1016_PLL_SEL_MASK			(0x1 << 13)
#घोषणा RT1016_PLL_SEL_SFT			13
#घोषणा RT1016_PLL_SEL_MCLK			(0x0 << 13)
#घोषणा RT1016_PLL_SEL_BCLK			(0x1 << 13)

/* 0x21 */
#घोषणा RT1016_FS_PD_MASK			(0x7 << 13)
#घोषणा RT1016_FS_PD_SFT			13
#घोषणा RT1016_OSR_PD_MASK			(0x3 << 10)
#घोषणा RT1016_OSR_PD_SFT			10

/* 0x22 */
#घोषणा RT1016_PWR_DAC_FILTER			(0x1 << 11)
#घोषणा RT1016_PWR_DAC_FILTER_BIT		11
#घोषणा RT1016_PWR_DACMOD			(0x1 << 10)
#घोषणा RT1016_PWR_DACMOD_BIT			10
#घोषणा RT1016_PWR_CLK_FIFO			(0x1 << 9)
#घोषणा RT1016_PWR_CLK_FIFO_BIT			9
#घोषणा RT1016_PWR_CLK_PUREDC			(0x1 << 8)
#घोषणा RT1016_PWR_CLK_PUREDC_BIT		8
#घोषणा RT1016_PWR_SIL_DET			(0x1 << 7)
#घोषणा RT1016_PWR_SIL_DET_BIT			7
#घोषणा RT1016_PWR_RC_25M			(0x1 << 6)
#घोषणा RT1016_PWR_RC_25M_BIT			6
#घोषणा RT1016_PWR_PLL1				(0x1 << 5)
#घोषणा RT1016_PWR_PLL1_BIT			5
#घोषणा RT1016_PWR_ANA_CTRL			(0x1 << 4)
#घोषणा RT1016_PWR_ANA_CTRL_BIT			4
#घोषणा RT1016_PWR_CLK_SYS			(0x1 << 3)
#घोषणा RT1016_PWR_CLK_SYS_BIT			3

/* 0x23 */
#घोषणा RT1016_PWR_LRCK_DET			(0x1 << 15)
#घोषणा RT1016_PWR_LRCK_DET_BIT			15
#घोषणा RT1016_PWR_BCLK_DET			(0x1 << 11)
#घोषणा RT1016_PWR_BCLK_DET_BIT			11

/* 0x40 */
#घोषणा RT1016_I2S_BCLK_MS_MASK			(0x1 << 15)
#घोषणा RT1016_I2S_BCLK_MS_SFT			15
#घोषणा RT1016_I2S_BCLK_MS_32			(0x0 << 15)
#घोषणा RT1016_I2S_BCLK_MS_64			(0x1 << 15)
#घोषणा RT1016_I2S_BCLK_POL_MASK		(0x1 << 13)
#घोषणा RT1016_I2S_BCLK_POL_SFT			13
#घोषणा RT1016_I2S_BCLK_POL_NOR			(0x0 << 13)
#घोषणा RT1016_I2S_BCLK_POL_INV			(0x1 << 13)
#घोषणा RT1016_I2S_DATA_SWAP_MASK		(0x1 << 10)
#घोषणा RT1016_I2S_DATA_SWAP_SFT		10
#घोषणा RT1016_I2S_DL_MASK			(0x7 << 4)
#घोषणा RT1016_I2S_DL_SFT			4
#घोषणा RT1016_I2S_DL_16			(0x1 << 4)
#घोषणा RT1016_I2S_DL_20			(0x2 << 4)
#घोषणा RT1016_I2S_DL_24			(0x3 << 4)
#घोषणा RT1016_I2S_DL_32			(0x4 << 4)
#घोषणा RT1016_I2S_MS_MASK			(0x1 << 3)
#घोषणा RT1016_I2S_MS_SFT			3
#घोषणा RT1016_I2S_MS_M				(0x0 << 3)
#घोषणा RT1016_I2S_MS_S				(0x1 << 3)
#घोषणा RT1016_I2S_DF_MASK			(0x7 << 0)
#घोषणा RT1016_I2S_DF_SFT			0
#घोषणा RT1016_I2S_DF_I2S			(0x0)
#घोषणा RT1016_I2S_DF_LEFT			(0x1)
#घोषणा RT1016_I2S_DF_PCM_A			(0x2)
#घोषणा RT1016_I2S_DF_PCM_B			(0x3)

/* 0xa0 */
#घोषणा RT1016_SIL_DET_EN			(0x1 << 15)
#घोषणा RT1016_SIL_DET_EN_BIT			15

/* 0xc2 */
#घोषणा RT1016_CKGEN_DAC			(0x1 << 13)
#घोषणा RT1016_CKGEN_DAC_BIT			13

/* 0xc4 */
#घोषणा RT1016_VCM_SLOW				(0x1 << 6)
#घोषणा RT1016_VCM_SLOW_BIT			6

/* 0xc5 */
#घोषणा RT1016_PLL_M_MAX			0xf
#घोषणा RT1016_PLL_M_MASK			(RT1016_PLL_M_MAX << 12)
#घोषणा RT1016_PLL_M_SFT			12
#घोषणा RT1016_PLL_M_BP				(0x1 << 11)
#घोषणा RT1016_PLL_M_BP_SFT			11
#घोषणा RT1016_PLL_N_MAX			0x1ff
#घोषणा RT1016_PLL_N_MASK			(RT1016_PLL_N_MAX << 0)
#घोषणा RT1016_PLL_N_SFT			0

/* 0xc6 */
#घोषणा RT1016_PLL2_EN				(0x1 << 15)
#घोषणा RT1016_PLL2_EN_BIT			15
#घोषणा RT1016_PLL_K_BP				(0x1 << 5)
#घोषणा RT1016_PLL_K_BP_SFT			5
#घोषणा RT1016_PLL_K_MAX			0x1f
#घोषणा RT1016_PLL_K_MASK			(RT1016_PLL_K_MAX)
#घोषणा RT1016_PLL_K_SFT			0

/* 0xcf */
#घोषणा RT1016_PWR_BG_1_2			(0x1 << 12)
#घोषणा RT1016_PWR_BG_1_2_BIT			12
#घोषणा RT1016_PWR_MBIAS_BG			(0x1 << 11)
#घोषणा RT1016_PWR_MBIAS_BG_BIT			11
#घोषणा RT1016_PWR_PLL				(0x1 << 9)
#घोषणा RT1016_PWR_PLL_BIT			9
#घोषणा RT1016_PWR_BASIC			(0x1 << 8)
#घोषणा RT1016_PWR_BASIC_BIT			8
#घोषणा RT1016_PWR_CLSD				(0x1 << 7)
#घोषणा RT1016_PWR_CLSD_BIT			7
#घोषणा RT1016_PWR_25M				(0x1 << 6)
#घोषणा RT1016_PWR_25M_BIT			6
#घोषणा RT1016_PWR_DACL				(0x1 << 4)
#घोषणा RT1016_PWR_DACL_BIT			4
#घोषणा RT1016_PWR_DACR				(0x1 << 3)
#घोषणा RT1016_PWR_DACR_BIT			3
#घोषणा RT1016_PWR_LDO2				(0x1 << 2)
#घोषणा RT1016_PWR_LDO2_BIT			2
#घोषणा RT1016_PWR_VREF				(0x1 << 1)
#घोषणा RT1016_PWR_VREF_BIT			1
#घोषणा RT1016_PWR_MBIAS			(0x1 << 0)
#घोषणा RT1016_PWR_MBIAS_BIT			0

/* System Clock Source */
क्रमागत अणु
	RT1016_SCLK_S_MCLK,
	RT1016_SCLK_S_PLL,
पूर्ण;

/* PLL1 Source */
क्रमागत अणु
	RT1016_PLL_S_MCLK,
	RT1016_PLL_S_BCLK,
पूर्ण;

क्रमागत अणु
	RT1016_AIF1,
	RT1016_AIFS,
पूर्ण;

काष्ठा rt1016_priv अणु
	काष्ठा snd_soc_component *component;
	काष्ठा regmap *regmap;
	पूर्णांक sysclk;
	पूर्णांक sysclk_src;
	पूर्णांक lrck;
	पूर्णांक bclk;
	पूर्णांक master;
	पूर्णांक pll_src;
	पूर्णांक pll_in;
	पूर्णांक pll_out;
पूर्ण;

#पूर्ण_अगर /* __RT1016_H__ */
