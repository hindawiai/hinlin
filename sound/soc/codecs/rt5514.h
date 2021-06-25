<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * rt5514.h  --  RT5514 ALSA SoC audio driver
 *
 * Copyright 2015 Realtek Microelectronics
 * Author: Oder Chiou <oder_chiou@realtek.com>
 */

#अगर_अघोषित __RT5514_H__
#घोषणा __RT5514_H__

#समावेश <linux/clk.h>
#समावेश <sound/rt5514.h>

#घोषणा RT5514_DEVICE_ID			0x10ec5514

#घोषणा RT5514_RESET				0x2000
#घोषणा RT5514_PWR_ANA1				0x2004
#घोषणा RT5514_PWR_ANA2				0x2008
#घोषणा RT5514_I2S_CTRL1			0x2010
#घोषणा RT5514_I2S_CTRL2			0x2014
#घोषणा RT5514_VAD_CTRL6			0x2030
#घोषणा RT5514_EXT_VAD_CTRL			0x206c
#घोषणा RT5514_DIG_IO_CTRL			0x2070
#घोषणा RT5514_PAD_CTRL1			0x2080
#घोषणा RT5514_DMIC_DATA_CTRL			0x20a0
#घोषणा RT5514_DIG_SOURCE_CTRL			0x20a4
#घोषणा RT5514_SRC_CTRL				0x20ac
#घोषणा RT5514_DOWNFILTER2_CTRL1		0x20d0
#घोषणा RT5514_PLL_SOURCE_CTRL			0x2100
#घोषणा RT5514_CLK_CTRL1			0x2104
#घोषणा RT5514_CLK_CTRL2			0x2108
#घोषणा RT5514_PLL3_CALIB_CTRL1			0x2110
#घोषणा RT5514_PLL3_CALIB_CTRL4			0x2120
#घोषणा RT5514_PLL3_CALIB_CTRL5			0x2124
#घोषणा RT5514_PLL3_CALIB_CTRL6			0x2128
#घोषणा RT5514_DELAY_BUF_CTRL1			0x2140
#घोषणा RT5514_DELAY_BUF_CTRL3			0x2148
#घोषणा RT5514_ASRC_IN_CTRL1			0x2180
#घोषणा RT5514_DOWNFILTER0_CTRL1		0x2190
#घोषणा RT5514_DOWNFILTER0_CTRL2		0x2194
#घोषणा RT5514_DOWNFILTER0_CTRL3		0x2198
#घोषणा RT5514_DOWNFILTER1_CTRL1		0x21a0
#घोषणा RT5514_DOWNFILTER1_CTRL2		0x21a4
#घोषणा RT5514_DOWNFILTER1_CTRL3		0x21a8
#घोषणा RT5514_ANA_CTRL_LDO10			0x2200
#घोषणा RT5514_ANA_CTRL_LDO18_16		0x2204
#घोषणा RT5514_ANA_CTRL_ADC12			0x2210
#घोषणा RT5514_ANA_CTRL_ADC21			0x2214
#घोषणा RT5514_ANA_CTRL_ADC22			0x2218
#घोषणा RT5514_ANA_CTRL_ADC23			0x221c
#घोषणा RT5514_ANA_CTRL_MICBST			0x2220
#घोषणा RT5514_ANA_CTRL_ADCFED			0x2224
#घोषणा RT5514_ANA_CTRL_INBUF			0x2228
#घोषणा RT5514_ANA_CTRL_VREF			0x222c
#घोषणा RT5514_ANA_CTRL_PLL3			0x2240
#घोषणा RT5514_ANA_CTRL_PLL1_1			0x2260
#घोषणा RT5514_ANA_CTRL_PLL1_2			0x2264
#घोषणा RT5514_DMIC_LP_CTRL			0x2e00
#घोषणा RT5514_MISC_CTRL_DSP			0x2e04
#घोषणा RT5514_DSP_CTRL1			0x2f00
#घोषणा RT5514_DSP_CTRL3			0x2f08
#घोषणा RT5514_DSP_CTRL4			0x2f10
#घोषणा RT5514_VENDOR_ID1			0x2ff0
#घोषणा RT5514_VENDOR_ID2			0x2ff4

#घोषणा RT5514_DSP_MAPPING			0x18000000

/* RT5514_PWR_ANA1 (0x2004) */
#घोषणा RT5514_POW_LDO18_IN			(0x1 << 5)
#घोषणा RT5514_POW_LDO18_IN_BIT			5
#घोषणा RT5514_POW_LDO18_ADC			(0x1 << 4)
#घोषणा RT5514_POW_LDO18_ADC_BIT		4
#घोषणा RT5514_POW_LDO21			(0x1 << 3)
#घोषणा RT5514_POW_LDO21_BIT			3
#घोषणा RT5514_POW_BG_LDO18_IN			(0x1 << 2)
#घोषणा RT5514_POW_BG_LDO18_IN_BIT		2
#घोषणा RT5514_POW_BG_LDO21			(0x1 << 1)
#घोषणा RT5514_POW_BG_LDO21_BIT			1

/* RT5514_PWR_ANA2 (0x2008) */
#घोषणा RT5514_POW_PLL1				(0x1 << 18)
#घोषणा RT5514_POW_PLL1_BIT			18
#घोषणा RT5514_POW_PLL1_LDO			(0x1 << 16)
#घोषणा RT5514_POW_PLL1_LDO_BIT			16
#घोषणा RT5514_POW_BG_MBIAS			(0x1 << 15)
#घोषणा RT5514_POW_BG_MBIAS_BIT			15
#घोषणा RT5514_POW_MBIAS			(0x1 << 14)
#घोषणा RT5514_POW_MBIAS_BIT			14
#घोषणा RT5514_POW_VREF2			(0x1 << 13)
#घोषणा RT5514_POW_VREF2_BIT			13
#घोषणा RT5514_POW_VREF1			(0x1 << 12)
#घोषणा RT5514_POW_VREF1_BIT			12
#घोषणा RT5514_POWR_LDO16			(0x1 << 11)
#घोषणा RT5514_POWR_LDO16_BIT			11
#घोषणा RT5514_POWL_LDO16			(0x1 << 10)
#घोषणा RT5514_POWL_LDO16_BIT			10
#घोषणा RT5514_POW_ADC2				(0x1 << 9)
#घोषणा RT5514_POW_ADC2_BIT			9
#घोषणा RT5514_POW_INPUT_BUF			(0x1 << 8)
#घोषणा RT5514_POW_INPUT_BUF_BIT		8
#घोषणा RT5514_POW_ADC1_R			(0x1 << 7)
#घोषणा RT5514_POW_ADC1_R_BIT			7
#घोषणा RT5514_POW_ADC1_L			(0x1 << 6)
#घोषणा RT5514_POW_ADC1_L_BIT			6
#घोषणा RT5514_POW2_BSTR			(0x1 << 5)
#घोषणा RT5514_POW2_BSTR_BIT			5
#घोषणा RT5514_POW2_BSTL			(0x1 << 4)
#घोषणा RT5514_POW2_BSTL_BIT			4
#घोषणा RT5514_POW_BSTR				(0x1 << 3)
#घोषणा RT5514_POW_BSTR_BIT			3
#घोषणा RT5514_POW_BSTL				(0x1 << 2)
#घोषणा RT5514_POW_BSTL_BIT			2
#घोषणा RT5514_POW_ADCFEDR			(0x1 << 1)
#घोषणा RT5514_POW_ADCFEDR_BIT			1
#घोषणा RT5514_POW_ADCFEDL			(0x1 << 0)
#घोषणा RT5514_POW_ADCFEDL_BIT			0

/* RT5514_I2S_CTRL1 (0x2010) */
#घोषणा RT5514_TDM_MODE2			(0x1 << 30)
#घोषणा RT5514_TDM_MODE2_SFT			30
#घोषणा RT5514_TDM_MODE				(0x1 << 28)
#घोषणा RT5514_TDM_MODE_SFT			28
#घोषणा RT5514_I2S_LR_MASK			(0x1 << 26)
#घोषणा RT5514_I2S_LR_SFT			26
#घोषणा RT5514_I2S_LR_NOR			(0x0 << 26)
#घोषणा RT5514_I2S_LR_INV			(0x1 << 26)
#घोषणा RT5514_I2S_BP_MASK			(0x1 << 25)
#घोषणा RT5514_I2S_BP_SFT			25
#घोषणा RT5514_I2S_BP_NOR			(0x0 << 25)
#घोषणा RT5514_I2S_BP_INV			(0x1 << 25)
#घोषणा RT5514_I2S_DF_MASK			(0x7 << 16)
#घोषणा RT5514_I2S_DF_SFT			16
#घोषणा RT5514_I2S_DF_I2S			(0x0 << 16)
#घोषणा RT5514_I2S_DF_LEFT			(0x1 << 16)
#घोषणा RT5514_I2S_DF_PCM_A			(0x2 << 16)
#घोषणा RT5514_I2S_DF_PCM_B			(0x3 << 16)
#घोषणा RT5514_TDMSLOT_SEL_RX_MASK		(0x3 << 10)
#घोषणा RT5514_TDMSLOT_SEL_RX_SFT		10
#घोषणा RT5514_TDMSLOT_SEL_RX_4CH		(0x1 << 10)
#घोषणा RT5514_TDMSLOT_SEL_RX_6CH		(0x2 << 10)
#घोषणा RT5514_TDMSLOT_SEL_RX_8CH		(0x3 << 10)
#घोषणा RT5514_CH_LEN_RX_MASK			(0x3 << 8)
#घोषणा RT5514_CH_LEN_RX_SFT			8
#घोषणा RT5514_CH_LEN_RX_16			(0x0 << 8)
#घोषणा RT5514_CH_LEN_RX_20			(0x1 << 8)
#घोषणा RT5514_CH_LEN_RX_24			(0x2 << 8)
#घोषणा RT5514_CH_LEN_RX_32			(0x3 << 8)
#घोषणा RT5514_TDMSLOT_SEL_TX_MASK		(0x3 << 6)
#घोषणा RT5514_TDMSLOT_SEL_TX_SFT		6
#घोषणा RT5514_TDMSLOT_SEL_TX_4CH		(0x1 << 6)
#घोषणा RT5514_TDMSLOT_SEL_TX_6CH		(0x2 << 6)
#घोषणा RT5514_TDMSLOT_SEL_TX_8CH		(0x3 << 6)
#घोषणा RT5514_CH_LEN_TX_MASK			(0x3 << 4)
#घोषणा RT5514_CH_LEN_TX_SFT			4
#घोषणा RT5514_CH_LEN_TX_16			(0x0 << 4)
#घोषणा RT5514_CH_LEN_TX_20			(0x1 << 4)
#घोषणा RT5514_CH_LEN_TX_24			(0x2 << 4)
#घोषणा RT5514_CH_LEN_TX_32			(0x3 << 4)
#घोषणा RT5514_I2S_DL_MASK			(0x3 << 0)
#घोषणा RT5514_I2S_DL_SFT			0
#घोषणा RT5514_I2S_DL_16			(0x0 << 0)
#घोषणा RT5514_I2S_DL_20			(0x1 << 0)
#घोषणा RT5514_I2S_DL_24			(0x2 << 0)
#घोषणा RT5514_I2S_DL_8				(0x3 << 0)

/* RT5514_I2S_CTRL2 (0x2014) */
#घोषणा RT5514_TDM_DOCKING_MODE			(0x1 << 31)
#घोषणा RT5514_TDM_DOCKING_MODE_SFT		31
#घोषणा RT5514_TDM_DOCKING_VALID_CH_MASK	(0x1 << 29)
#घोषणा RT5514_TDM_DOCKING_VALID_CH_SFT		29
#घोषणा RT5514_TDM_DOCKING_VALID_CH2		(0x0 << 29)
#घोषणा RT5514_TDM_DOCKING_VALID_CH4		(0x1 << 29)
#घोषणा RT5514_TDM_DOCKING_START_MASK		(0x1 << 28)
#घोषणा RT5514_TDM_DOCKING_START_SFT		28
#घोषणा RT5514_TDM_DOCKING_START_SLOT0		(0x0 << 28)
#घोषणा RT5514_TDM_DOCKING_START_SLOT4		(0x1 << 28)

/* RT5514_DIG_SOURCE_CTRL (0x20a4) */
#घोषणा RT5514_AD1_DMIC_INPUT_SEL		(0x1 << 1)
#घोषणा RT5514_AD1_DMIC_INPUT_SEL_SFT		1
#घोषणा RT5514_AD0_DMIC_INPUT_SEL		(0x1 << 0)
#घोषणा RT5514_AD0_DMIC_INPUT_SEL_SFT		0

/* RT5514_PLL_SOURCE_CTRL (0x2100) */
#घोषणा RT5514_PLL_1_SEL_MASK			(0x7 << 12)
#घोषणा RT5514_PLL_1_SEL_SFT			12
#घोषणा RT5514_PLL_1_SEL_SCLK			(0x3 << 12)
#घोषणा RT5514_PLL_1_SEL_MCLK			(0x4 << 12)

/* RT5514_CLK_CTRL1 (0x2104) */
#घोषणा RT5514_CLK_AD_ANA1_EN			(0x1 << 31)
#घोषणा RT5514_CLK_AD_ANA1_EN_BIT		31
#घोषणा RT5514_CLK_AD1_EN			(0x1 << 24)
#घोषणा RT5514_CLK_AD1_EN_BIT			24
#घोषणा RT5514_CLK_AD0_EN			(0x1 << 23)
#घोषणा RT5514_CLK_AD0_EN_BIT			23
#घोषणा RT5514_CLK_DMIC_OUT_SEL_MASK		(0x7 << 8)
#घोषणा RT5514_CLK_DMIC_OUT_SEL_SFT		8
#घोषणा RT5514_CLK_AD_ANA1_SEL_MASK		(0xf << 0)
#घोषणा RT5514_CLK_AD_ANA1_SEL_SFT		0

/* RT5514_CLK_CTRL2 (0x2108) */
#घोषणा RT5514_CLK_AD1_ASRC_EN			(0x1 << 17)
#घोषणा RT5514_CLK_AD1_ASRC_EN_BIT		17
#घोषणा RT5514_CLK_AD0_ASRC_EN			(0x1 << 16)
#घोषणा RT5514_CLK_AD0_ASRC_EN_BIT		16
#घोषणा RT5514_CLK_SYS_DIV_OUT_MASK		(0x7 << 8)
#घोषणा RT5514_CLK_SYS_DIV_OUT_SFT		8
#घोषणा RT5514_SEL_ADC_OSR_MASK			(0x7 << 4)
#घोषणा RT5514_SEL_ADC_OSR_SFT			4
#घोषणा RT5514_CLK_SYS_PRE_SEL_MASK		(0x3 << 0)
#घोषणा RT5514_CLK_SYS_PRE_SEL_SFT		0
#घोषणा RT5514_CLK_SYS_PRE_SEL_MCLK		(0x2 << 0)
#घोषणा RT5514_CLK_SYS_PRE_SEL_PLL		(0x3 << 0)

/*  RT5514_DOWNFILTER_CTRL (0x2190 0x2194 0x21a0 0x21a4) */
#घोषणा RT5514_AD_DMIC_MIX			(0x1 << 11)
#घोषणा RT5514_AD_DMIC_MIX_BIT			11
#घोषणा RT5514_AD_AD_MIX			(0x1 << 10)
#घोषणा RT5514_AD_AD_MIX_BIT			10
#घोषणा RT5514_AD_AD_MUTE			(0x1 << 7)
#घोषणा RT5514_AD_AD_MUTE_BIT			7
#घोषणा RT5514_AD_GAIN_MASK			(0x3f << 1)
#घोषणा RT5514_AD_GAIN_SFT			1

/*  RT5514_ANA_CTRL_MICBST (0x2220) */
#घोषणा RT5514_SEL_BSTL_MASK			(0xf << 4)
#घोषणा RT5514_SEL_BSTL_SFT			4
#घोषणा RT5514_SEL_BSTR_MASK			(0xf << 0)
#घोषणा RT5514_SEL_BSTR_SFT			0

/*  RT5514_ANA_CTRL_PLL1_1 (0x2260) */
#घोषणा RT5514_PLL_K_MAX			0x1f
#घोषणा RT5514_PLL_K_MASK			(RT5514_PLL_K_MAX << 16)
#घोषणा RT5514_PLL_K_SFT			16
#घोषणा RT5514_PLL_N_MAX			0x1ff
#घोषणा RT5514_PLL_N_MASK			(RT5514_PLL_N_MAX << 7)
#घोषणा RT5514_PLL_N_SFT			4
#घोषणा RT5514_PLL_M_MAX			0xf
#घोषणा RT5514_PLL_M_MASK			(RT5514_PLL_M_MAX << 0)
#घोषणा RT5514_PLL_M_SFT			0

/*  RT5514_ANA_CTRL_PLL1_2 (0x2264) */
#घोषणा RT5514_PLL_M_BP				(0x1 << 2)
#घोषणा RT5514_PLL_M_BP_SFT			2
#घोषणा RT5514_PLL_K_BP				(0x1 << 1)
#घोषणा RT5514_PLL_K_BP_SFT			1
#घोषणा RT5514_EN_LDO_PLL1			(0x1 << 0)
#घोषणा RT5514_EN_LDO_PLL1_BIT			0

#घोषणा RT5514_PLL_INP_MAX			40000000
#घोषणा RT5514_PLL_INP_MIN			256000

#घोषणा RT5514_FIRMWARE1	"rt5514_dsp_fw1.bin"
#घोषणा RT5514_FIRMWARE2	"rt5514_dsp_fw2.bin"

/* System Clock Source */
क्रमागत अणु
	RT5514_SCLK_S_MCLK,
	RT5514_SCLK_S_PLL1,
पूर्ण;

/* PLL1 Source */
क्रमागत अणु
	RT5514_PLL1_S_MCLK,
	RT5514_PLL1_S_BCLK,
पूर्ण;

काष्ठा rt5514_priv अणु
	काष्ठा rt5514_platक्रमm_data pdata;
	काष्ठा snd_soc_component *component;
	काष्ठा regmap *i2c_regmap, *regmap;
	काष्ठा clk *mclk, *dsp_calib_clk;
	पूर्णांक sysclk;
	पूर्णांक sysclk_src;
	पूर्णांक lrck;
	पूर्णांक bclk;
	पूर्णांक pll_src;
	पूर्णांक pll_in;
	पूर्णांक pll_out;
	पूर्णांक dsp_enabled;
	अचिन्हित पूर्णांक pll3_cal_value;
पूर्ण;

#पूर्ण_अगर /* __RT5514_H__ */
