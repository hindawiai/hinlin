<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Analog Devices ADAU1373 Audio Codec drive
 *
 * Copyright 2011 Analog Devices Inc.
 * Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/gcd.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश <sound/soc.h>
#समावेश <sound/adau1373.h>

#समावेश "adau1373.h"
#समावेश "adau-utils.h"

काष्ठा adau1373_dai अणु
	अचिन्हित पूर्णांक clk_src;
	अचिन्हित पूर्णांक sysclk;
	bool enable_src;
	bool master;
पूर्ण;

काष्ठा adau1373 अणु
	काष्ठा regmap *regmap;
	काष्ठा adau1373_dai dais[3];
पूर्ण;

#घोषणा ADAU1373_INPUT_MODE	0x00
#घोषणा ADAU1373_AINL_CTRL(x)	(0x01 + (x) * 2)
#घोषणा ADAU1373_AINR_CTRL(x)	(0x02 + (x) * 2)
#घोषणा ADAU1373_LLINE_OUT(x)	(0x9 + (x) * 2)
#घोषणा ADAU1373_RLINE_OUT(x)	(0xa + (x) * 2)
#घोषणा ADAU1373_LSPK_OUT	0x0d
#घोषणा ADAU1373_RSPK_OUT	0x0e
#घोषणा ADAU1373_LHP_OUT	0x0f
#घोषणा ADAU1373_RHP_OUT	0x10
#घोषणा ADAU1373_ADC_GAIN	0x11
#घोषणा ADAU1373_LADC_MIXER	0x12
#घोषणा ADAU1373_RADC_MIXER	0x13
#घोषणा ADAU1373_LLINE1_MIX	0x14
#घोषणा ADAU1373_RLINE1_MIX	0x15
#घोषणा ADAU1373_LLINE2_MIX	0x16
#घोषणा ADAU1373_RLINE2_MIX	0x17
#घोषणा ADAU1373_LSPK_MIX	0x18
#घोषणा ADAU1373_RSPK_MIX	0x19
#घोषणा ADAU1373_LHP_MIX	0x1a
#घोषणा ADAU1373_RHP_MIX	0x1b
#घोषणा ADAU1373_EP_MIX		0x1c
#घोषणा ADAU1373_HP_CTRL	0x1d
#घोषणा ADAU1373_HP_CTRL2	0x1e
#घोषणा ADAU1373_LS_CTRL	0x1f
#घोषणा ADAU1373_EP_CTRL	0x21
#घोषणा ADAU1373_MICBIAS_CTRL1	0x22
#घोषणा ADAU1373_MICBIAS_CTRL2	0x23
#घोषणा ADAU1373_OUTPUT_CTRL	0x24
#घोषणा ADAU1373_PWDN_CTRL1	0x25
#घोषणा ADAU1373_PWDN_CTRL2	0x26
#घोषणा ADAU1373_PWDN_CTRL3	0x27
#घोषणा ADAU1373_DPLL_CTRL(x)	(0x28 + (x) * 7)
#घोषणा ADAU1373_PLL_CTRL1(x)	(0x29 + (x) * 7)
#घोषणा ADAU1373_PLL_CTRL2(x)	(0x2a + (x) * 7)
#घोषणा ADAU1373_PLL_CTRL3(x)	(0x2b + (x) * 7)
#घोषणा ADAU1373_PLL_CTRL4(x)	(0x2c + (x) * 7)
#घोषणा ADAU1373_PLL_CTRL5(x)	(0x2d + (x) * 7)
#घोषणा ADAU1373_PLL_CTRL6(x)	(0x2e + (x) * 7)
#घोषणा ADAU1373_HEADDECT	0x36
#घोषणा ADAU1373_ADC_DAC_STATUS	0x37
#घोषणा ADAU1373_ADC_CTRL	0x3c
#घोषणा ADAU1373_DAI(x)		(0x44 + (x))
#घोषणा ADAU1373_CLK_SRC_DIV(x)	(0x40 + (x) * 2)
#घोषणा ADAU1373_BCLKDIV(x)	(0x47 + (x))
#घोषणा ADAU1373_SRC_RATIOA(x)	(0x4a + (x) * 2)
#घोषणा ADAU1373_SRC_RATIOB(x)	(0x4b + (x) * 2)
#घोषणा ADAU1373_DEEMP_CTRL	0x50
#घोषणा ADAU1373_SRC_DAI_CTRL(x) (0x51 + (x))
#घोषणा ADAU1373_DIN_MIX_CTRL(x) (0x56 + (x))
#घोषणा ADAU1373_DOUT_MIX_CTRL(x) (0x5b + (x))
#घोषणा ADAU1373_DAI_PBL_VOL(x)	(0x62 + (x) * 2)
#घोषणा ADAU1373_DAI_PBR_VOL(x)	(0x63 + (x) * 2)
#घोषणा ADAU1373_DAI_RECL_VOL(x) (0x68 + (x) * 2)
#घोषणा ADAU1373_DAI_RECR_VOL(x) (0x69 + (x) * 2)
#घोषणा ADAU1373_DAC1_PBL_VOL	0x6e
#घोषणा ADAU1373_DAC1_PBR_VOL	0x6f
#घोषणा ADAU1373_DAC2_PBL_VOL	0x70
#घोषणा ADAU1373_DAC2_PBR_VOL	0x71
#घोषणा ADAU1373_ADC_RECL_VOL	0x72
#घोषणा ADAU1373_ADC_RECR_VOL	0x73
#घोषणा ADAU1373_DMIC_RECL_VOL	0x74
#घोषणा ADAU1373_DMIC_RECR_VOL	0x75
#घोषणा ADAU1373_VOL_GAIN1	0x76
#घोषणा ADAU1373_VOL_GAIN2	0x77
#घोषणा ADAU1373_VOL_GAIN3	0x78
#घोषणा ADAU1373_HPF_CTRL	0x7d
#घोषणा ADAU1373_BASS1		0x7e
#घोषणा ADAU1373_BASS2		0x7f
#घोषणा ADAU1373_DRC(x)		(0x80 + (x) * 0x10)
#घोषणा ADAU1373_3D_CTRL1	0xc0
#घोषणा ADAU1373_3D_CTRL2	0xc1
#घोषणा ADAU1373_FDSP_SEL1	0xdc
#घोषणा ADAU1373_FDSP_SEL2	0xdd
#घोषणा ADAU1373_FDSP_SEL3	0xde
#घोषणा ADAU1373_FDSP_SEL4	0xdf
#घोषणा ADAU1373_DIGMICCTRL	0xe2
#घोषणा ADAU1373_DIGEN		0xeb
#घोषणा ADAU1373_SOFT_RESET	0xff


#घोषणा ADAU1373_PLL_CTRL6_DPLL_BYPASS	BIT(1)
#घोषणा ADAU1373_PLL_CTRL6_PLL_EN	BIT(0)

#घोषणा ADAU1373_DAI_INVERT_BCLK	BIT(7)
#घोषणा ADAU1373_DAI_MASTER		BIT(6)
#घोषणा ADAU1373_DAI_INVERT_LRCLK	BIT(4)
#घोषणा ADAU1373_DAI_WLEN_16		0x0
#घोषणा ADAU1373_DAI_WLEN_20		0x4
#घोषणा ADAU1373_DAI_WLEN_24		0x8
#घोषणा ADAU1373_DAI_WLEN_32		0xc
#घोषणा ADAU1373_DAI_WLEN_MASK		0xc
#घोषणा ADAU1373_DAI_FORMAT_RIGHT_J	0x0
#घोषणा ADAU1373_DAI_FORMAT_LEFT_J	0x1
#घोषणा ADAU1373_DAI_FORMAT_I2S		0x2
#घोषणा ADAU1373_DAI_FORMAT_DSP		0x3

#घोषणा ADAU1373_BCLKDIV_SOURCE		BIT(5)
#घोषणा ADAU1373_BCLKDIV_SR_MASK	(0x07 << 2)
#घोषणा ADAU1373_BCLKDIV_BCLK_MASK	0x03
#घोषणा ADAU1373_BCLKDIV_32		0x03
#घोषणा ADAU1373_BCLKDIV_64		0x02
#घोषणा ADAU1373_BCLKDIV_128		0x01
#घोषणा ADAU1373_BCLKDIV_256		0x00

#घोषणा ADAU1373_ADC_CTRL_PEAK_DETECT	BIT(0)
#घोषणा ADAU1373_ADC_CTRL_RESET		BIT(1)
#घोषणा ADAU1373_ADC_CTRL_RESET_FORCE	BIT(2)

#घोषणा ADAU1373_OUTPUT_CTRL_LDIFF	BIT(3)
#घोषणा ADAU1373_OUTPUT_CTRL_LNFBEN	BIT(2)

#घोषणा ADAU1373_PWDN_CTRL3_PWR_EN BIT(0)

#घोषणा ADAU1373_EP_CTRL_MICBIAS1_OFFSET 4
#घोषणा ADAU1373_EP_CTRL_MICBIAS2_OFFSET 2

अटल स्थिर काष्ठा reg_शेष adau1373_reg_शेषs[] = अणु
	अणु ADAU1373_INPUT_MODE,		0x00 पूर्ण,
	अणु ADAU1373_AINL_CTRL(0),	0x00 पूर्ण,
	अणु ADAU1373_AINR_CTRL(0),	0x00 पूर्ण,
	अणु ADAU1373_AINL_CTRL(1),	0x00 पूर्ण,
	अणु ADAU1373_AINR_CTRL(1),	0x00 पूर्ण,
	अणु ADAU1373_AINL_CTRL(2),	0x00 पूर्ण,
	अणु ADAU1373_AINR_CTRL(2),	0x00 पूर्ण,
	अणु ADAU1373_AINL_CTRL(3),	0x00 पूर्ण,
	अणु ADAU1373_AINR_CTRL(3),	0x00 पूर्ण,
	अणु ADAU1373_LLINE_OUT(0),	0x00 पूर्ण,
	अणु ADAU1373_RLINE_OUT(0),	0x00 पूर्ण,
	अणु ADAU1373_LLINE_OUT(1),	0x00 पूर्ण,
	अणु ADAU1373_RLINE_OUT(1),	0x00 पूर्ण,
	अणु ADAU1373_LSPK_OUT,		0x00 पूर्ण,
	अणु ADAU1373_RSPK_OUT,		0x00 पूर्ण,
	अणु ADAU1373_LHP_OUT,		0x00 पूर्ण,
	अणु ADAU1373_RHP_OUT,		0x00 पूर्ण,
	अणु ADAU1373_ADC_GAIN,		0x00 पूर्ण,
	अणु ADAU1373_LADC_MIXER,		0x00 पूर्ण,
	अणु ADAU1373_RADC_MIXER,		0x00 पूर्ण,
	अणु ADAU1373_LLINE1_MIX,		0x00 पूर्ण,
	अणु ADAU1373_RLINE1_MIX,		0x00 पूर्ण,
	अणु ADAU1373_LLINE2_MIX,		0x00 पूर्ण,
	अणु ADAU1373_RLINE2_MIX,		0x00 पूर्ण,
	अणु ADAU1373_LSPK_MIX,		0x00 पूर्ण,
	अणु ADAU1373_RSPK_MIX,		0x00 पूर्ण,
	अणु ADAU1373_LHP_MIX,		0x00 पूर्ण,
	अणु ADAU1373_RHP_MIX,		0x00 पूर्ण,
	अणु ADAU1373_EP_MIX,		0x00 पूर्ण,
	अणु ADAU1373_HP_CTRL,		0x00 पूर्ण,
	अणु ADAU1373_HP_CTRL2,		0x00 पूर्ण,
	अणु ADAU1373_LS_CTRL,		0x00 पूर्ण,
	अणु ADAU1373_EP_CTRL,		0x00 पूर्ण,
	अणु ADAU1373_MICBIAS_CTRL1,	0x00 पूर्ण,
	अणु ADAU1373_MICBIAS_CTRL2,	0x00 पूर्ण,
	अणु ADAU1373_OUTPUT_CTRL,		0x00 पूर्ण,
	अणु ADAU1373_PWDN_CTRL1,		0x00 पूर्ण,
	अणु ADAU1373_PWDN_CTRL2,		0x00 पूर्ण,
	अणु ADAU1373_PWDN_CTRL3,		0x00 पूर्ण,
	अणु ADAU1373_DPLL_CTRL(0),	0x00 पूर्ण,
	अणु ADAU1373_PLL_CTRL1(0),	0x00 पूर्ण,
	अणु ADAU1373_PLL_CTRL2(0),	0x00 पूर्ण,
	अणु ADAU1373_PLL_CTRL3(0),	0x00 पूर्ण,
	अणु ADAU1373_PLL_CTRL4(0),	0x00 पूर्ण,
	अणु ADAU1373_PLL_CTRL5(0),	0x00 पूर्ण,
	अणु ADAU1373_PLL_CTRL6(0),	0x02 पूर्ण,
	अणु ADAU1373_DPLL_CTRL(1),	0x00 पूर्ण,
	अणु ADAU1373_PLL_CTRL1(1),	0x00 पूर्ण,
	अणु ADAU1373_PLL_CTRL2(1),	0x00 पूर्ण,
	अणु ADAU1373_PLL_CTRL3(1),	0x00 पूर्ण,
	अणु ADAU1373_PLL_CTRL4(1),	0x00 पूर्ण,
	अणु ADAU1373_PLL_CTRL5(1),	0x00 पूर्ण,
	अणु ADAU1373_PLL_CTRL6(1),	0x02 पूर्ण,
	अणु ADAU1373_HEADDECT,		0x00 पूर्ण,
	अणु ADAU1373_ADC_CTRL,		0x00 पूर्ण,
	अणु ADAU1373_CLK_SRC_DIV(0),	0x00 पूर्ण,
	अणु ADAU1373_CLK_SRC_DIV(1),	0x00 पूर्ण,
	अणु ADAU1373_DAI(0),		0x0a पूर्ण,
	अणु ADAU1373_DAI(1),		0x0a पूर्ण,
	अणु ADAU1373_DAI(2),		0x0a पूर्ण,
	अणु ADAU1373_BCLKDIV(0),		0x00 पूर्ण,
	अणु ADAU1373_BCLKDIV(1),		0x00 पूर्ण,
	अणु ADAU1373_BCLKDIV(2),		0x00 पूर्ण,
	अणु ADAU1373_SRC_RATIOA(0),	0x00 पूर्ण,
	अणु ADAU1373_SRC_RATIOB(0),	0x00 पूर्ण,
	अणु ADAU1373_SRC_RATIOA(1),	0x00 पूर्ण,
	अणु ADAU1373_SRC_RATIOB(1),	0x00 पूर्ण,
	अणु ADAU1373_SRC_RATIOA(2),	0x00 पूर्ण,
	अणु ADAU1373_SRC_RATIOB(2),	0x00 पूर्ण,
	अणु ADAU1373_DEEMP_CTRL,		0x00 पूर्ण,
	अणु ADAU1373_SRC_DAI_CTRL(0),	0x08 पूर्ण,
	अणु ADAU1373_SRC_DAI_CTRL(1),	0x08 पूर्ण,
	अणु ADAU1373_SRC_DAI_CTRL(2),	0x08 पूर्ण,
	अणु ADAU1373_DIN_MIX_CTRL(0),	0x00 पूर्ण,
	अणु ADAU1373_DIN_MIX_CTRL(1),	0x00 पूर्ण,
	अणु ADAU1373_DIN_MIX_CTRL(2),	0x00 पूर्ण,
	अणु ADAU1373_DIN_MIX_CTRL(3),	0x00 पूर्ण,
	अणु ADAU1373_DIN_MIX_CTRL(4),	0x00 पूर्ण,
	अणु ADAU1373_DOUT_MIX_CTRL(0),	0x00 पूर्ण,
	अणु ADAU1373_DOUT_MIX_CTRL(1),	0x00 पूर्ण,
	अणु ADAU1373_DOUT_MIX_CTRL(2),	0x00 पूर्ण,
	अणु ADAU1373_DOUT_MIX_CTRL(3),	0x00 पूर्ण,
	अणु ADAU1373_DOUT_MIX_CTRL(4),	0x00 पूर्ण,
	अणु ADAU1373_DAI_PBL_VOL(0),	0x00 पूर्ण,
	अणु ADAU1373_DAI_PBR_VOL(0),	0x00 पूर्ण,
	अणु ADAU1373_DAI_PBL_VOL(1),	0x00 पूर्ण,
	अणु ADAU1373_DAI_PBR_VOL(1),	0x00 पूर्ण,
	अणु ADAU1373_DAI_PBL_VOL(2),	0x00 पूर्ण,
	अणु ADAU1373_DAI_PBR_VOL(2),	0x00 पूर्ण,
	अणु ADAU1373_DAI_RECL_VOL(0),	0x00 पूर्ण,
	अणु ADAU1373_DAI_RECR_VOL(0),	0x00 पूर्ण,
	अणु ADAU1373_DAI_RECL_VOL(1),	0x00 पूर्ण,
	अणु ADAU1373_DAI_RECR_VOL(1),	0x00 पूर्ण,
	अणु ADAU1373_DAI_RECL_VOL(2),	0x00 पूर्ण,
	अणु ADAU1373_DAI_RECR_VOL(2),	0x00 पूर्ण,
	अणु ADAU1373_DAC1_PBL_VOL,	0x00 पूर्ण,
	अणु ADAU1373_DAC1_PBR_VOL,	0x00 पूर्ण,
	अणु ADAU1373_DAC2_PBL_VOL,	0x00 पूर्ण,
	अणु ADAU1373_DAC2_PBR_VOL,	0x00 पूर्ण,
	अणु ADAU1373_ADC_RECL_VOL,	0x00 पूर्ण,
	अणु ADAU1373_ADC_RECR_VOL,	0x00 पूर्ण,
	अणु ADAU1373_DMIC_RECL_VOL,	0x00 पूर्ण,
	अणु ADAU1373_DMIC_RECR_VOL,	0x00 पूर्ण,
	अणु ADAU1373_VOL_GAIN1,		0x00 पूर्ण,
	अणु ADAU1373_VOL_GAIN2,		0x00 पूर्ण,
	अणु ADAU1373_VOL_GAIN3,		0x00 पूर्ण,
	अणु ADAU1373_HPF_CTRL,		0x00 पूर्ण,
	अणु ADAU1373_BASS1,		0x00 पूर्ण,
	अणु ADAU1373_BASS2,		0x00 पूर्ण,
	अणु ADAU1373_DRC(0) + 0x0,	0x78 पूर्ण,
	अणु ADAU1373_DRC(0) + 0x1,	0x18 पूर्ण,
	अणु ADAU1373_DRC(0) + 0x2,	0x00 पूर्ण,
	अणु ADAU1373_DRC(0) + 0x3,	0x00 पूर्ण,
	अणु ADAU1373_DRC(0) + 0x4,	0x00 पूर्ण,
	अणु ADAU1373_DRC(0) + 0x5,	0xc0 पूर्ण,
	अणु ADAU1373_DRC(0) + 0x6,	0x00 पूर्ण,
	अणु ADAU1373_DRC(0) + 0x7,	0x00 पूर्ण,
	अणु ADAU1373_DRC(0) + 0x8,	0x00 पूर्ण,
	अणु ADAU1373_DRC(0) + 0x9,	0xc0 पूर्ण,
	अणु ADAU1373_DRC(0) + 0xa,	0x88 पूर्ण,
	अणु ADAU1373_DRC(0) + 0xb,	0x7a पूर्ण,
	अणु ADAU1373_DRC(0) + 0xc,	0xdf पूर्ण,
	अणु ADAU1373_DRC(0) + 0xd,	0x20 पूर्ण,
	अणु ADAU1373_DRC(0) + 0xe,	0x00 पूर्ण,
	अणु ADAU1373_DRC(0) + 0xf,	0x00 पूर्ण,
	अणु ADAU1373_DRC(1) + 0x0,	0x78 पूर्ण,
	अणु ADAU1373_DRC(1) + 0x1,	0x18 पूर्ण,
	अणु ADAU1373_DRC(1) + 0x2,	0x00 पूर्ण,
	अणु ADAU1373_DRC(1) + 0x3,	0x00 पूर्ण,
	अणु ADAU1373_DRC(1) + 0x4,	0x00 पूर्ण,
	अणु ADAU1373_DRC(1) + 0x5,	0xc0 पूर्ण,
	अणु ADAU1373_DRC(1) + 0x6,	0x00 पूर्ण,
	अणु ADAU1373_DRC(1) + 0x7,	0x00 पूर्ण,
	अणु ADAU1373_DRC(1) + 0x8,	0x00 पूर्ण,
	अणु ADAU1373_DRC(1) + 0x9,	0xc0 पूर्ण,
	अणु ADAU1373_DRC(1) + 0xa,	0x88 पूर्ण,
	अणु ADAU1373_DRC(1) + 0xb,	0x7a पूर्ण,
	अणु ADAU1373_DRC(1) + 0xc,	0xdf पूर्ण,
	अणु ADAU1373_DRC(1) + 0xd,	0x20 पूर्ण,
	अणु ADAU1373_DRC(1) + 0xe,	0x00 पूर्ण,
	अणु ADAU1373_DRC(1) + 0xf,	0x00 पूर्ण,
	अणु ADAU1373_DRC(2) + 0x0,	0x78 पूर्ण,
	अणु ADAU1373_DRC(2) + 0x1,	0x18 पूर्ण,
	अणु ADAU1373_DRC(2) + 0x2,	0x00 पूर्ण,
	अणु ADAU1373_DRC(2) + 0x3,	0x00 पूर्ण,
	अणु ADAU1373_DRC(2) + 0x4,	0x00 पूर्ण,
	अणु ADAU1373_DRC(2) + 0x5,	0xc0 पूर्ण,
	अणु ADAU1373_DRC(2) + 0x6,	0x00 पूर्ण,
	अणु ADAU1373_DRC(2) + 0x7,	0x00 पूर्ण,
	अणु ADAU1373_DRC(2) + 0x8,	0x00 पूर्ण,
	अणु ADAU1373_DRC(2) + 0x9,	0xc0 पूर्ण,
	अणु ADAU1373_DRC(2) + 0xa,	0x88 पूर्ण,
	अणु ADAU1373_DRC(2) + 0xb,	0x7a पूर्ण,
	अणु ADAU1373_DRC(2) + 0xc,	0xdf पूर्ण,
	अणु ADAU1373_DRC(2) + 0xd,	0x20 पूर्ण,
	अणु ADAU1373_DRC(2) + 0xe,	0x00 पूर्ण,
	अणु ADAU1373_DRC(2) + 0xf,	0x00 पूर्ण,
	अणु ADAU1373_3D_CTRL1,		0x00 पूर्ण,
	अणु ADAU1373_3D_CTRL2,		0x00 पूर्ण,
	अणु ADAU1373_FDSP_SEL1,		0x00 पूर्ण,
	अणु ADAU1373_FDSP_SEL2,		0x00 पूर्ण,
	अणु ADAU1373_FDSP_SEL2,		0x00 पूर्ण,
	अणु ADAU1373_FDSP_SEL4,		0x00 पूर्ण,
	अणु ADAU1373_DIGMICCTRL,		0x00 पूर्ण,
	अणु ADAU1373_DIGEN,		0x00 पूर्ण,
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_RANGE(adau1373_out_tlv,
	0, 7, TLV_DB_SCALE_ITEM(-7900, 400, 1),
	8, 15, TLV_DB_SCALE_ITEM(-4700, 300, 0),
	16, 23, TLV_DB_SCALE_ITEM(-2300, 200, 0),
	24, 31, TLV_DB_SCALE_ITEM(-700, 100, 0)
);

अटल स्थिर DECLARE_TLV_DB_MINMAX(adau1373_digital_tlv, -9563, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adau1373_in_pga_tlv, -1300, 100, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(adau1373_ep_tlv, -600, 600, 1);

अटल स्थिर DECLARE_TLV_DB_SCALE(adau1373_input_boost_tlv, 0, 2000, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adau1373_gain_boost_tlv, 0, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adau1373_speaker_boost_tlv, 1200, 600, 0);

अटल स्थिर अक्षर *adau1373_fdsp_sel_text[] = अणु
	"None",
	"Channel 1",
	"Channel 2",
	"Channel 3",
	"Channel 4",
	"Channel 5",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adau1373_drc1_channel_क्रमागत,
	ADAU1373_FDSP_SEL1, 4, adau1373_fdsp_sel_text);
अटल SOC_ENUM_SINGLE_DECL(adau1373_drc2_channel_क्रमागत,
	ADAU1373_FDSP_SEL1, 0, adau1373_fdsp_sel_text);
अटल SOC_ENUM_SINGLE_DECL(adau1373_drc3_channel_क्रमागत,
	ADAU1373_FDSP_SEL2, 0, adau1373_fdsp_sel_text);
अटल SOC_ENUM_SINGLE_DECL(adau1373_hpf_channel_क्रमागत,
	ADAU1373_FDSP_SEL3, 0, adau1373_fdsp_sel_text);
अटल SOC_ENUM_SINGLE_DECL(adau1373_bass_channel_क्रमागत,
	ADAU1373_FDSP_SEL4, 4, adau1373_fdsp_sel_text);

अटल स्थिर अक्षर *adau1373_hpf_cutoff_text[] = अणु
	"3.7Hz", "50Hz", "100Hz", "150Hz", "200Hz", "250Hz", "300Hz", "350Hz",
	"400Hz", "450Hz", "500Hz", "550Hz", "600Hz", "650Hz", "700Hz", "750Hz",
	"800Hz",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adau1373_hpf_cutoff_क्रमागत,
	ADAU1373_HPF_CTRL, 3, adau1373_hpf_cutoff_text);

अटल स्थिर अक्षर *adau1373_bass_lpf_cutoff_text[] = अणु
	"801Hz", "1001Hz",
पूर्ण;

अटल स्थिर अक्षर *adau1373_bass_clip_level_text[] = अणु
	"0.125", "0.250", "0.370", "0.500", "0.625", "0.750", "0.875",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक adau1373_bass_clip_level_values[] = अणु
	1, 2, 3, 4, 5, 6, 7,
पूर्ण;

अटल स्थिर अक्षर *adau1373_bass_hpf_cutoff_text[] = अणु
	"158Hz", "232Hz", "347Hz", "520Hz",
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_RANGE(adau1373_bass_tlv,
	0, 2, TLV_DB_SCALE_ITEM(-600, 600, 1),
	3, 4, TLV_DB_SCALE_ITEM(950, 250, 0),
	5, 7, TLV_DB_SCALE_ITEM(1400, 150, 0)
);

अटल SOC_ENUM_SINGLE_DECL(adau1373_bass_lpf_cutoff_क्रमागत,
	ADAU1373_BASS1, 5, adau1373_bass_lpf_cutoff_text);

अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1373_bass_clip_level_क्रमागत,
	ADAU1373_BASS1, 2, 7, adau1373_bass_clip_level_text,
	adau1373_bass_clip_level_values);

अटल SOC_ENUM_SINGLE_DECL(adau1373_bass_hpf_cutoff_क्रमागत,
	ADAU1373_BASS1, 0, adau1373_bass_hpf_cutoff_text);

अटल स्थिर अक्षर *adau1373_3d_level_text[] = अणु
	"0%", "6.67%", "13.33%", "20%", "26.67%", "33.33%",
	"40%", "46.67%", "53.33%", "60%", "66.67%", "73.33%",
	"80%", "86.67", "99.33%", "100%"
पूर्ण;

अटल स्थिर अक्षर *adau1373_3d_cutoff_text[] = अणु
	"No 3D", "0.03125 fs", "0.04583 fs", "0.075 fs", "0.11458 fs",
	"0.16875 fs", "0.27083 fs"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adau1373_3d_level_क्रमागत,
	ADAU1373_3D_CTRL1, 4, adau1373_3d_level_text);
अटल SOC_ENUM_SINGLE_DECL(adau1373_3d_cutoff_क्रमागत,
	ADAU1373_3D_CTRL1, 0, adau1373_3d_cutoff_text);

अटल स्थिर DECLARE_TLV_DB_RANGE(adau1373_3d_tlv,
	0, 0, TLV_DB_SCALE_ITEM(0, 0, 0),
	1, 7, TLV_DB_LINEAR_ITEM(-1800, -120)
);

अटल स्थिर अक्षर *adau1373_lr_mux_text[] = अणु
	"Mute",
	"Right Channel (L+R)",
	"Left Channel (L+R)",
	"Stereo",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adau1373_lineout1_lr_mux_क्रमागत,
	ADAU1373_OUTPUT_CTRL, 4, adau1373_lr_mux_text);
अटल SOC_ENUM_SINGLE_DECL(adau1373_lineout2_lr_mux_क्रमागत,
	ADAU1373_OUTPUT_CTRL, 6, adau1373_lr_mux_text);
अटल SOC_ENUM_SINGLE_DECL(adau1373_speaker_lr_mux_क्रमागत,
	ADAU1373_LS_CTRL, 4, adau1373_lr_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new adau1373_controls[] = अणु
	SOC_DOUBLE_R_TLV("AIF1 Capture Volume", ADAU1373_DAI_RECL_VOL(0),
		ADAU1373_DAI_RECR_VOL(0), 0, 0xff, 1, adau1373_digital_tlv),
	SOC_DOUBLE_R_TLV("AIF2 Capture Volume", ADAU1373_DAI_RECL_VOL(1),
		ADAU1373_DAI_RECR_VOL(1), 0, 0xff, 1, adau1373_digital_tlv),
	SOC_DOUBLE_R_TLV("AIF3 Capture Volume", ADAU1373_DAI_RECL_VOL(2),
		ADAU1373_DAI_RECR_VOL(2), 0, 0xff, 1, adau1373_digital_tlv),

	SOC_DOUBLE_R_TLV("ADC Capture Volume", ADAU1373_ADC_RECL_VOL,
		ADAU1373_ADC_RECR_VOL, 0, 0xff, 1, adau1373_digital_tlv),
	SOC_DOUBLE_R_TLV("DMIC Capture Volume", ADAU1373_DMIC_RECL_VOL,
		ADAU1373_DMIC_RECR_VOL, 0, 0xff, 1, adau1373_digital_tlv),

	SOC_DOUBLE_R_TLV("AIF1 Playback Volume", ADAU1373_DAI_PBL_VOL(0),
		ADAU1373_DAI_PBR_VOL(0), 0, 0xff, 1, adau1373_digital_tlv),
	SOC_DOUBLE_R_TLV("AIF2 Playback Volume", ADAU1373_DAI_PBL_VOL(1),
		ADAU1373_DAI_PBR_VOL(1), 0, 0xff, 1, adau1373_digital_tlv),
	SOC_DOUBLE_R_TLV("AIF3 Playback Volume", ADAU1373_DAI_PBL_VOL(2),
		ADAU1373_DAI_PBR_VOL(2), 0, 0xff, 1, adau1373_digital_tlv),

	SOC_DOUBLE_R_TLV("DAC1 Playback Volume", ADAU1373_DAC1_PBL_VOL,
		ADAU1373_DAC1_PBR_VOL, 0, 0xff, 1, adau1373_digital_tlv),
	SOC_DOUBLE_R_TLV("DAC2 Playback Volume", ADAU1373_DAC2_PBL_VOL,
		ADAU1373_DAC2_PBR_VOL, 0, 0xff, 1, adau1373_digital_tlv),

	SOC_DOUBLE_R_TLV("Lineout1 Playback Volume", ADAU1373_LLINE_OUT(0),
		ADAU1373_RLINE_OUT(0), 0, 0x1f, 0, adau1373_out_tlv),
	SOC_DOUBLE_R_TLV("Speaker Playback Volume", ADAU1373_LSPK_OUT,
		ADAU1373_RSPK_OUT, 0, 0x1f, 0, adau1373_out_tlv),
	SOC_DOUBLE_R_TLV("Headphone Playback Volume", ADAU1373_LHP_OUT,
		ADAU1373_RHP_OUT, 0, 0x1f, 0, adau1373_out_tlv),

	SOC_DOUBLE_R_TLV("Input 1 Capture Volume", ADAU1373_AINL_CTRL(0),
		ADAU1373_AINR_CTRL(0), 0, 0x1f, 0, adau1373_in_pga_tlv),
	SOC_DOUBLE_R_TLV("Input 2 Capture Volume", ADAU1373_AINL_CTRL(1),
		ADAU1373_AINR_CTRL(1), 0, 0x1f, 0, adau1373_in_pga_tlv),
	SOC_DOUBLE_R_TLV("Input 3 Capture Volume", ADAU1373_AINL_CTRL(2),
		ADAU1373_AINR_CTRL(2), 0, 0x1f, 0, adau1373_in_pga_tlv),
	SOC_DOUBLE_R_TLV("Input 4 Capture Volume", ADAU1373_AINL_CTRL(3),
		ADAU1373_AINR_CTRL(3), 0, 0x1f, 0, adau1373_in_pga_tlv),

	SOC_SINGLE_TLV("Earpiece Playback Volume", ADAU1373_EP_CTRL, 0, 3, 0,
		adau1373_ep_tlv),

	SOC_DOUBLE_TLV("AIF3 Boost Playback Volume", ADAU1373_VOL_GAIN1, 4, 5,
		1, 0, adau1373_gain_boost_tlv),
	SOC_DOUBLE_TLV("AIF2 Boost Playback Volume", ADAU1373_VOL_GAIN1, 2, 3,
		1, 0, adau1373_gain_boost_tlv),
	SOC_DOUBLE_TLV("AIF1 Boost Playback Volume", ADAU1373_VOL_GAIN1, 0, 1,
		1, 0, adau1373_gain_boost_tlv),
	SOC_DOUBLE_TLV("AIF3 Boost Capture Volume", ADAU1373_VOL_GAIN2, 4, 5,
		1, 0, adau1373_gain_boost_tlv),
	SOC_DOUBLE_TLV("AIF2 Boost Capture Volume", ADAU1373_VOL_GAIN2, 2, 3,
		1, 0, adau1373_gain_boost_tlv),
	SOC_DOUBLE_TLV("AIF1 Boost Capture Volume", ADAU1373_VOL_GAIN2, 0, 1,
		1, 0, adau1373_gain_boost_tlv),
	SOC_DOUBLE_TLV("DMIC Boost Capture Volume", ADAU1373_VOL_GAIN3, 6, 7,
		1, 0, adau1373_gain_boost_tlv),
	SOC_DOUBLE_TLV("ADC Boost Capture Volume", ADAU1373_VOL_GAIN3, 4, 5,
		1, 0, adau1373_gain_boost_tlv),
	SOC_DOUBLE_TLV("DAC2 Boost Playback Volume", ADAU1373_VOL_GAIN3, 2, 3,
		1, 0, adau1373_gain_boost_tlv),
	SOC_DOUBLE_TLV("DAC1 Boost Playback Volume", ADAU1373_VOL_GAIN3, 0, 1,
		1, 0, adau1373_gain_boost_tlv),

	SOC_DOUBLE_TLV("Input 1 Boost Capture Volume", ADAU1373_ADC_GAIN, 0, 4,
		1, 0, adau1373_input_boost_tlv),
	SOC_DOUBLE_TLV("Input 2 Boost Capture Volume", ADAU1373_ADC_GAIN, 1, 5,
		1, 0, adau1373_input_boost_tlv),
	SOC_DOUBLE_TLV("Input 3 Boost Capture Volume", ADAU1373_ADC_GAIN, 2, 6,
		1, 0, adau1373_input_boost_tlv),
	SOC_DOUBLE_TLV("Input 4 Boost Capture Volume", ADAU1373_ADC_GAIN, 3, 7,
		1, 0, adau1373_input_boost_tlv),

	SOC_DOUBLE_TLV("Speaker Boost Playback Volume", ADAU1373_LS_CTRL, 2, 3,
		1, 0, adau1373_speaker_boost_tlv),

	SOC_ENUM("Lineout1 LR Mux", adau1373_lineout1_lr_mux_क्रमागत),
	SOC_ENUM("Speaker LR Mux", adau1373_speaker_lr_mux_क्रमागत),

	SOC_ENUM("HPF Cutoff", adau1373_hpf_cutoff_क्रमागत),
	SOC_DOUBLE("HPF Switch", ADAU1373_HPF_CTRL, 1, 0, 1, 0),
	SOC_ENUM("HPF Channel", adau1373_hpf_channel_क्रमागत),

	SOC_ENUM("Bass HPF Cutoff", adau1373_bass_hpf_cutoff_क्रमागत),
	SOC_ENUM("Bass Clip Level Threshold", adau1373_bass_clip_level_क्रमागत),
	SOC_ENUM("Bass LPF Cutoff", adau1373_bass_lpf_cutoff_क्रमागत),
	SOC_DOUBLE("Bass Playback Switch", ADAU1373_BASS2, 0, 1, 1, 0),
	SOC_SINGLE_TLV("Bass Playback Volume", ADAU1373_BASS2, 2, 7, 0,
	    adau1373_bass_tlv),
	SOC_ENUM("Bass Channel", adau1373_bass_channel_क्रमागत),

	SOC_ENUM("3D Freq", adau1373_3d_cutoff_क्रमागत),
	SOC_ENUM("3D Level", adau1373_3d_level_क्रमागत),
	SOC_SINGLE("3D Playback Switch", ADAU1373_3D_CTRL2, 0, 1, 0),
	SOC_SINGLE_TLV("3D Playback Volume", ADAU1373_3D_CTRL2, 2, 7, 0,
		adau1373_3d_tlv),
	SOC_ENUM("3D Channel", adau1373_bass_channel_क्रमागत),

	SOC_SINGLE("Zero Cross Switch", ADAU1373_PWDN_CTRL3, 7, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1373_lineout2_controls[] = अणु
	SOC_DOUBLE_R_TLV("Lineout2 Playback Volume", ADAU1373_LLINE_OUT(1),
		ADAU1373_RLINE_OUT(1), 0, 0x1f, 0, adau1373_out_tlv),
	SOC_ENUM("Lineout2 LR Mux", adau1373_lineout2_lr_mux_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1373_drc_controls[] = अणु
	SOC_ENUM("DRC1 Channel", adau1373_drc1_channel_क्रमागत),
	SOC_ENUM("DRC2 Channel", adau1373_drc2_channel_क्रमागत),
	SOC_ENUM("DRC3 Channel", adau1373_drc3_channel_क्रमागत),
पूर्ण;

अटल पूर्णांक adau1373_pll_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा adau1373 *adau1373 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक pll_id = w->name[3] - '1';
	अचिन्हित पूर्णांक val;

	अगर (SND_SOC_DAPM_EVENT_ON(event))
		val = ADAU1373_PLL_CTRL6_PLL_EN;
	अन्यथा
		val = 0;

	regmap_update_bits(adau1373->regmap, ADAU1373_PLL_CTRL6(pll_id),
		ADAU1373_PLL_CTRL6_PLL_EN, val);

	अगर (SND_SOC_DAPM_EVENT_ON(event))
		mdelay(5);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *adau1373_decimator_text[] = अणु
	"ADC",
	"DMIC1",
पूर्ण;

अटल SOC_ENUM_SINGLE_VIRT_DECL(adau1373_decimator_क्रमागत,
	adau1373_decimator_text);

अटल स्थिर काष्ठा snd_kcontrol_new adau1373_decimator_mux =
	SOC_DAPM_ENUM("Decimator Mux", adau1373_decimator_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new adau1373_left_adc_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("DAC1 Switch", ADAU1373_LADC_MIXER, 4, 1, 0),
	SOC_DAPM_SINGLE("Input 4 Switch", ADAU1373_LADC_MIXER, 3, 1, 0),
	SOC_DAPM_SINGLE("Input 3 Switch", ADAU1373_LADC_MIXER, 2, 1, 0),
	SOC_DAPM_SINGLE("Input 2 Switch", ADAU1373_LADC_MIXER, 1, 1, 0),
	SOC_DAPM_SINGLE("Input 1 Switch", ADAU1373_LADC_MIXER, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1373_right_adc_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("DAC1 Switch", ADAU1373_RADC_MIXER, 4, 1, 0),
	SOC_DAPM_SINGLE("Input 4 Switch", ADAU1373_RADC_MIXER, 3, 1, 0),
	SOC_DAPM_SINGLE("Input 3 Switch", ADAU1373_RADC_MIXER, 2, 1, 0),
	SOC_DAPM_SINGLE("Input 2 Switch", ADAU1373_RADC_MIXER, 1, 1, 0),
	SOC_DAPM_SINGLE("Input 1 Switch", ADAU1373_RADC_MIXER, 0, 1, 0),
पूर्ण;

#घोषणा DECLARE_ADAU1373_OUTPUT_MIXER_CTRLS(_name, _reg) \
स्थिर काष्ठा snd_kcontrol_new _name[] = अणु \
	SOC_DAPM_SINGLE("Left DAC2 Switch", _reg, 7, 1, 0), \
	SOC_DAPM_SINGLE("Right DAC2 Switch", _reg, 6, 1, 0), \
	SOC_DAPM_SINGLE("Left DAC1 Switch", _reg, 5, 1, 0), \
	SOC_DAPM_SINGLE("Right DAC1 Switch", _reg, 4, 1, 0), \
	SOC_DAPM_SINGLE("Input 4 Bypass Switch", _reg, 3, 1, 0), \
	SOC_DAPM_SINGLE("Input 3 Bypass Switch", _reg, 2, 1, 0), \
	SOC_DAPM_SINGLE("Input 2 Bypass Switch", _reg, 1, 1, 0), \
	SOC_DAPM_SINGLE("Input 1 Bypass Switch", _reg, 0, 1, 0), \
पूर्ण

अटल DECLARE_ADAU1373_OUTPUT_MIXER_CTRLS(adau1373_left_line1_mixer_controls,
	ADAU1373_LLINE1_MIX);
अटल DECLARE_ADAU1373_OUTPUT_MIXER_CTRLS(adau1373_right_line1_mixer_controls,
	ADAU1373_RLINE1_MIX);
अटल DECLARE_ADAU1373_OUTPUT_MIXER_CTRLS(adau1373_left_line2_mixer_controls,
	ADAU1373_LLINE2_MIX);
अटल DECLARE_ADAU1373_OUTPUT_MIXER_CTRLS(adau1373_right_line2_mixer_controls,
	ADAU1373_RLINE2_MIX);
अटल DECLARE_ADAU1373_OUTPUT_MIXER_CTRLS(adau1373_left_spk_mixer_controls,
	ADAU1373_LSPK_MIX);
अटल DECLARE_ADAU1373_OUTPUT_MIXER_CTRLS(adau1373_right_spk_mixer_controls,
	ADAU1373_RSPK_MIX);
अटल DECLARE_ADAU1373_OUTPUT_MIXER_CTRLS(adau1373_ep_mixer_controls,
	ADAU1373_EP_MIX);

अटल स्थिर काष्ठा snd_kcontrol_new adau1373_left_hp_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left DAC1 Switch", ADAU1373_LHP_MIX, 5, 1, 0),
	SOC_DAPM_SINGLE("Left DAC2 Switch", ADAU1373_LHP_MIX, 4, 1, 0),
	SOC_DAPM_SINGLE("Input 4 Bypass Switch", ADAU1373_LHP_MIX, 3, 1, 0),
	SOC_DAPM_SINGLE("Input 3 Bypass Switch", ADAU1373_LHP_MIX, 2, 1, 0),
	SOC_DAPM_SINGLE("Input 2 Bypass Switch", ADAU1373_LHP_MIX, 1, 1, 0),
	SOC_DAPM_SINGLE("Input 1 Bypass Switch", ADAU1373_LHP_MIX, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1373_right_hp_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Right DAC1 Switch", ADAU1373_RHP_MIX, 5, 1, 0),
	SOC_DAPM_SINGLE("Right DAC2 Switch", ADAU1373_RHP_MIX, 4, 1, 0),
	SOC_DAPM_SINGLE("Input 4 Bypass Switch", ADAU1373_RHP_MIX, 3, 1, 0),
	SOC_DAPM_SINGLE("Input 3 Bypass Switch", ADAU1373_RHP_MIX, 2, 1, 0),
	SOC_DAPM_SINGLE("Input 2 Bypass Switch", ADAU1373_RHP_MIX, 1, 1, 0),
	SOC_DAPM_SINGLE("Input 1 Bypass Switch", ADAU1373_RHP_MIX, 0, 1, 0),
पूर्ण;

#घोषणा DECLARE_ADAU1373_DSP_CHANNEL_MIXER_CTRLS(_name, _reg) \
स्थिर काष्ठा snd_kcontrol_new _name[] = अणु \
	SOC_DAPM_SINGLE("DMIC2 Swapped Switch", _reg, 6, 1, 0), \
	SOC_DAPM_SINGLE("DMIC2 Switch", _reg, 5, 1, 0), \
	SOC_DAPM_SINGLE("ADC/DMIC1 Swapped Switch", _reg, 4, 1, 0), \
	SOC_DAPM_SINGLE("ADC/DMIC1 Switch", _reg, 3, 1, 0), \
	SOC_DAPM_SINGLE("AIF3 Switch", _reg, 2, 1, 0), \
	SOC_DAPM_SINGLE("AIF2 Switch", _reg, 1, 1, 0), \
	SOC_DAPM_SINGLE("AIF1 Switch", _reg, 0, 1, 0), \
पूर्ण

अटल DECLARE_ADAU1373_DSP_CHANNEL_MIXER_CTRLS(adau1373_dsp_channel1_mixer_controls,
	ADAU1373_DIN_MIX_CTRL(0));
अटल DECLARE_ADAU1373_DSP_CHANNEL_MIXER_CTRLS(adau1373_dsp_channel2_mixer_controls,
	ADAU1373_DIN_MIX_CTRL(1));
अटल DECLARE_ADAU1373_DSP_CHANNEL_MIXER_CTRLS(adau1373_dsp_channel3_mixer_controls,
	ADAU1373_DIN_MIX_CTRL(2));
अटल DECLARE_ADAU1373_DSP_CHANNEL_MIXER_CTRLS(adau1373_dsp_channel4_mixer_controls,
	ADAU1373_DIN_MIX_CTRL(3));
अटल DECLARE_ADAU1373_DSP_CHANNEL_MIXER_CTRLS(adau1373_dsp_channel5_mixer_controls,
	ADAU1373_DIN_MIX_CTRL(4));

#घोषणा DECLARE_ADAU1373_DSP_OUTPUT_MIXER_CTRLS(_name, _reg) \
स्थिर काष्ठा snd_kcontrol_new _name[] = अणु \
	SOC_DAPM_SINGLE("DSP Channel5 Switch", _reg, 4, 1, 0), \
	SOC_DAPM_SINGLE("DSP Channel4 Switch", _reg, 3, 1, 0), \
	SOC_DAPM_SINGLE("DSP Channel3 Switch", _reg, 2, 1, 0), \
	SOC_DAPM_SINGLE("DSP Channel2 Switch", _reg, 1, 1, 0), \
	SOC_DAPM_SINGLE("DSP Channel1 Switch", _reg, 0, 1, 0), \
पूर्ण

अटल DECLARE_ADAU1373_DSP_OUTPUT_MIXER_CTRLS(adau1373_aअगर1_mixer_controls,
	ADAU1373_DOUT_MIX_CTRL(0));
अटल DECLARE_ADAU1373_DSP_OUTPUT_MIXER_CTRLS(adau1373_aअगर2_mixer_controls,
	ADAU1373_DOUT_MIX_CTRL(1));
अटल DECLARE_ADAU1373_DSP_OUTPUT_MIXER_CTRLS(adau1373_aअगर3_mixer_controls,
	ADAU1373_DOUT_MIX_CTRL(2));
अटल DECLARE_ADAU1373_DSP_OUTPUT_MIXER_CTRLS(adau1373_dac1_mixer_controls,
	ADAU1373_DOUT_MIX_CTRL(3));
अटल DECLARE_ADAU1373_DSP_OUTPUT_MIXER_CTRLS(adau1373_dac2_mixer_controls,
	ADAU1373_DOUT_MIX_CTRL(4));

अटल स्थिर काष्ठा snd_soc_dapm_widget adau1373_dapm_widमाला_लो[] = अणु
	/* Datasheet claims Left ADC is bit 6 and Right ADC is bit 7, but that
	 * करोesn't seem to be the हाल. */
	SND_SOC_DAPM_ADC("Left ADC", शून्य, ADAU1373_PWDN_CTRL1, 7, 0),
	SND_SOC_DAPM_ADC("Right ADC", शून्य, ADAU1373_PWDN_CTRL1, 6, 0),

	SND_SOC_DAPM_ADC("DMIC1", शून्य, ADAU1373_DIGMICCTRL, 0, 0),
	SND_SOC_DAPM_ADC("DMIC2", शून्य, ADAU1373_DIGMICCTRL, 2, 0),

	SND_SOC_DAPM_MUX("Decimator Mux", SND_SOC_NOPM, 0, 0,
		&adau1373_decimator_mux),

	SND_SOC_DAPM_SUPPLY("MICBIAS2", ADAU1373_PWDN_CTRL1, 5, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS1", ADAU1373_PWDN_CTRL1, 4, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("IN4PGA", ADAU1373_PWDN_CTRL1, 3, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IN3PGA", ADAU1373_PWDN_CTRL1, 2, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IN2PGA", ADAU1373_PWDN_CTRL1, 1, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IN1PGA", ADAU1373_PWDN_CTRL1, 0, 0, शून्य, 0),

	SND_SOC_DAPM_DAC("Left DAC2", शून्य, ADAU1373_PWDN_CTRL2, 7, 0),
	SND_SOC_DAPM_DAC("Right DAC2", शून्य, ADAU1373_PWDN_CTRL2, 6, 0),
	SND_SOC_DAPM_DAC("Left DAC1", शून्य, ADAU1373_PWDN_CTRL2, 5, 0),
	SND_SOC_DAPM_DAC("Right DAC1", शून्य, ADAU1373_PWDN_CTRL2, 4, 0),

	SOC_MIXER_ARRAY("Left ADC Mixer", SND_SOC_NOPM, 0, 0,
		adau1373_left_adc_mixer_controls),
	SOC_MIXER_ARRAY("Right ADC Mixer", SND_SOC_NOPM, 0, 0,
		adau1373_right_adc_mixer_controls),

	SOC_MIXER_ARRAY("Left Lineout2 Mixer", ADAU1373_PWDN_CTRL2, 3, 0,
		adau1373_left_line2_mixer_controls),
	SOC_MIXER_ARRAY("Right Lineout2 Mixer", ADAU1373_PWDN_CTRL2, 2, 0,
		adau1373_right_line2_mixer_controls),
	SOC_MIXER_ARRAY("Left Lineout1 Mixer", ADAU1373_PWDN_CTRL2, 1, 0,
		adau1373_left_line1_mixer_controls),
	SOC_MIXER_ARRAY("Right Lineout1 Mixer", ADAU1373_PWDN_CTRL2, 0, 0,
		adau1373_right_line1_mixer_controls),

	SOC_MIXER_ARRAY("Earpiece Mixer", ADAU1373_PWDN_CTRL3, 4, 0,
		adau1373_ep_mixer_controls),
	SOC_MIXER_ARRAY("Left Speaker Mixer", ADAU1373_PWDN_CTRL3, 3, 0,
		adau1373_left_spk_mixer_controls),
	SOC_MIXER_ARRAY("Right Speaker Mixer", ADAU1373_PWDN_CTRL3, 2, 0,
		adau1373_right_spk_mixer_controls),
	SOC_MIXER_ARRAY("Left Headphone Mixer", SND_SOC_NOPM, 0, 0,
		adau1373_left_hp_mixer_controls),
	SOC_MIXER_ARRAY("Right Headphone Mixer", SND_SOC_NOPM, 0, 0,
		adau1373_right_hp_mixer_controls),
	SND_SOC_DAPM_SUPPLY("Headphone Enable", ADAU1373_PWDN_CTRL3, 1, 0,
		शून्य, 0),

	SND_SOC_DAPM_SUPPLY("AIF1 CLK", ADAU1373_SRC_DAI_CTRL(0), 0, 0,
	    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AIF2 CLK", ADAU1373_SRC_DAI_CTRL(1), 0, 0,
	    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AIF3 CLK", ADAU1373_SRC_DAI_CTRL(2), 0, 0,
	    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AIF1 IN SRC", ADAU1373_SRC_DAI_CTRL(0), 2, 0,
	    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AIF1 OUT SRC", ADAU1373_SRC_DAI_CTRL(0), 1, 0,
	    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AIF2 IN SRC", ADAU1373_SRC_DAI_CTRL(1), 2, 0,
	    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AIF2 OUT SRC", ADAU1373_SRC_DAI_CTRL(1), 1, 0,
	    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AIF3 IN SRC", ADAU1373_SRC_DAI_CTRL(2), 2, 0,
	    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AIF3 OUT SRC", ADAU1373_SRC_DAI_CTRL(2), 1, 0,
	    शून्य, 0),

	SND_SOC_DAPM_AIF_IN("AIF1 IN", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1 OUT", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2 IN", "AIF2 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2 OUT", "AIF2 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF3 IN", "AIF3 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF3 OUT", "AIF3 Capture", 0, SND_SOC_NOPM, 0, 0),

	SOC_MIXER_ARRAY("DSP Channel1 Mixer", SND_SOC_NOPM, 0, 0,
		adau1373_dsp_channel1_mixer_controls),
	SOC_MIXER_ARRAY("DSP Channel2 Mixer", SND_SOC_NOPM, 0, 0,
		adau1373_dsp_channel2_mixer_controls),
	SOC_MIXER_ARRAY("DSP Channel3 Mixer", SND_SOC_NOPM, 0, 0,
		adau1373_dsp_channel3_mixer_controls),
	SOC_MIXER_ARRAY("DSP Channel4 Mixer", SND_SOC_NOPM, 0, 0,
		adau1373_dsp_channel4_mixer_controls),
	SOC_MIXER_ARRAY("DSP Channel5 Mixer", SND_SOC_NOPM, 0, 0,
		adau1373_dsp_channel5_mixer_controls),

	SOC_MIXER_ARRAY("AIF1 Mixer", SND_SOC_NOPM, 0, 0,
		adau1373_aअगर1_mixer_controls),
	SOC_MIXER_ARRAY("AIF2 Mixer", SND_SOC_NOPM, 0, 0,
		adau1373_aअगर2_mixer_controls),
	SOC_MIXER_ARRAY("AIF3 Mixer", SND_SOC_NOPM, 0, 0,
		adau1373_aअगर3_mixer_controls),
	SOC_MIXER_ARRAY("DAC1 Mixer", SND_SOC_NOPM, 0, 0,
		adau1373_dac1_mixer_controls),
	SOC_MIXER_ARRAY("DAC2 Mixer", SND_SOC_NOPM, 0, 0,
		adau1373_dac2_mixer_controls),

	SND_SOC_DAPM_SUPPLY("DSP", ADAU1373_DIGEN, 4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Recording Engine B", ADAU1373_DIGEN, 3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Recording Engine A", ADAU1373_DIGEN, 2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Playback Engine B", ADAU1373_DIGEN, 1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Playback Engine A", ADAU1373_DIGEN, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("PLL1", SND_SOC_NOPM, 0, 0, adau1373_pll_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("PLL2", SND_SOC_NOPM, 0, 0, adau1373_pll_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("SYSCLK1", ADAU1373_CLK_SRC_DIV(0), 7, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SYSCLK2", ADAU1373_CLK_SRC_DIV(1), 7, 0, शून्य, 0),

	SND_SOC_DAPM_INPUT("AIN1L"),
	SND_SOC_DAPM_INPUT("AIN1R"),
	SND_SOC_DAPM_INPUT("AIN2L"),
	SND_SOC_DAPM_INPUT("AIN2R"),
	SND_SOC_DAPM_INPUT("AIN3L"),
	SND_SOC_DAPM_INPUT("AIN3R"),
	SND_SOC_DAPM_INPUT("AIN4L"),
	SND_SOC_DAPM_INPUT("AIN4R"),

	SND_SOC_DAPM_INPUT("DMIC1DAT"),
	SND_SOC_DAPM_INPUT("DMIC2DAT"),

	SND_SOC_DAPM_OUTPUT("LOUT1L"),
	SND_SOC_DAPM_OUTPUT("LOUT1R"),
	SND_SOC_DAPM_OUTPUT("LOUT2L"),
	SND_SOC_DAPM_OUTPUT("LOUT2R"),
	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),
	SND_SOC_DAPM_OUTPUT("SPKL"),
	SND_SOC_DAPM_OUTPUT("SPKR"),
	SND_SOC_DAPM_OUTPUT("EP"),
पूर्ण;

अटल पूर्णांक adau1373_check_aअगर_clk(काष्ठा snd_soc_dapm_widget *source,
	काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा adau1373 *adau1373 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक dai;
	स्थिर अक्षर *clk;

	dai = sink->name[3] - '1';

	अगर (!adau1373->dais[dai].master)
		वापस 0;

	अगर (adau1373->dais[dai].clk_src == ADAU1373_CLK_SRC_PLL1)
		clk = "SYSCLK1";
	अन्यथा
		clk = "SYSCLK2";

	वापस म_भेद(source->name, clk) == 0;
पूर्ण

अटल पूर्णांक adau1373_check_src(काष्ठा snd_soc_dapm_widget *source,
	काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा adau1373 *adau1373 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक dai;

	dai = sink->name[3] - '1';

	वापस adau1373->dais[dai].enable_src;
पूर्ण

#घोषणा DSP_CHANNEL_MIXER_ROUTES(_sink) \
	अणु _sink, "DMIC2 Swapped Switch", "DMIC2" पूर्ण, \
	अणु _sink, "DMIC2 Switch", "DMIC2" पूर्ण, \
	अणु _sink, "ADC/DMIC1 Swapped Switch", "Decimator Mux" पूर्ण, \
	अणु _sink, "ADC/DMIC1 Switch", "Decimator Mux" पूर्ण, \
	अणु _sink, "AIF1 Switch", "AIF1 IN" पूर्ण, \
	अणु _sink, "AIF2 Switch", "AIF2 IN" पूर्ण, \
	अणु _sink, "AIF3 Switch", "AIF3 IN" पूर्ण

#घोषणा DSP_OUTPUT_MIXER_ROUTES(_sink) \
	अणु _sink, "DSP Channel1 Switch", "DSP Channel1 Mixer" पूर्ण, \
	अणु _sink, "DSP Channel2 Switch", "DSP Channel2 Mixer" पूर्ण, \
	अणु _sink, "DSP Channel3 Switch", "DSP Channel3 Mixer" पूर्ण, \
	अणु _sink, "DSP Channel4 Switch", "DSP Channel4 Mixer" पूर्ण, \
	अणु _sink, "DSP Channel5 Switch", "DSP Channel5 Mixer" पूर्ण

#घोषणा LEFT_OUTPUT_MIXER_ROUTES(_sink) \
	अणु _sink, "Right DAC2 Switch", "Right DAC2" पूर्ण, \
	अणु _sink, "Left DAC2 Switch", "Left DAC2" पूर्ण, \
	अणु _sink, "Right DAC1 Switch", "Right DAC1" पूर्ण, \
	अणु _sink, "Left DAC1 Switch", "Left DAC1" पूर्ण, \
	अणु _sink, "Input 1 Bypass Switch", "IN1PGA" पूर्ण, \
	अणु _sink, "Input 2 Bypass Switch", "IN2PGA" पूर्ण, \
	अणु _sink, "Input 3 Bypass Switch", "IN3PGA" पूर्ण, \
	अणु _sink, "Input 4 Bypass Switch", "IN4PGA" पूर्ण

#घोषणा RIGHT_OUTPUT_MIXER_ROUTES(_sink) \
	अणु _sink, "Right DAC2 Switch", "Right DAC2" पूर्ण, \
	अणु _sink, "Left DAC2 Switch", "Left DAC2" पूर्ण, \
	अणु _sink, "Right DAC1 Switch", "Right DAC1" पूर्ण, \
	अणु _sink, "Left DAC1 Switch", "Left DAC1" पूर्ण, \
	अणु _sink, "Input 1 Bypass Switch", "IN1PGA" पूर्ण, \
	अणु _sink, "Input 2 Bypass Switch", "IN2PGA" पूर्ण, \
	अणु _sink, "Input 3 Bypass Switch", "IN3PGA" पूर्ण, \
	अणु _sink, "Input 4 Bypass Switch", "IN4PGA" पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route adau1373_dapm_routes[] = अणु
	अणु "Left ADC Mixer", "DAC1 Switch", "Left DAC1" पूर्ण,
	अणु "Left ADC Mixer", "Input 1 Switch", "IN1PGA" पूर्ण,
	अणु "Left ADC Mixer", "Input 2 Switch", "IN2PGA" पूर्ण,
	अणु "Left ADC Mixer", "Input 3 Switch", "IN3PGA" पूर्ण,
	अणु "Left ADC Mixer", "Input 4 Switch", "IN4PGA" पूर्ण,

	अणु "Right ADC Mixer", "DAC1 Switch", "Right DAC1" पूर्ण,
	अणु "Right ADC Mixer", "Input 1 Switch", "IN1PGA" पूर्ण,
	अणु "Right ADC Mixer", "Input 2 Switch", "IN2PGA" पूर्ण,
	अणु "Right ADC Mixer", "Input 3 Switch", "IN3PGA" पूर्ण,
	अणु "Right ADC Mixer", "Input 4 Switch", "IN4PGA" पूर्ण,

	अणु "Left ADC", शून्य, "Left ADC Mixer" पूर्ण,
	अणु "Right ADC", शून्य, "Right ADC Mixer" पूर्ण,

	अणु "Decimator Mux", "ADC", "Left ADC" पूर्ण,
	अणु "Decimator Mux", "ADC", "Right ADC" पूर्ण,
	अणु "Decimator Mux", "DMIC1", "DMIC1" पूर्ण,

	DSP_CHANNEL_MIXER_ROUTES("DSP Channel1 Mixer"),
	DSP_CHANNEL_MIXER_ROUTES("DSP Channel2 Mixer"),
	DSP_CHANNEL_MIXER_ROUTES("DSP Channel3 Mixer"),
	DSP_CHANNEL_MIXER_ROUTES("DSP Channel4 Mixer"),
	DSP_CHANNEL_MIXER_ROUTES("DSP Channel5 Mixer"),

	DSP_OUTPUT_MIXER_ROUTES("AIF1 Mixer"),
	DSP_OUTPUT_MIXER_ROUTES("AIF2 Mixer"),
	DSP_OUTPUT_MIXER_ROUTES("AIF3 Mixer"),
	DSP_OUTPUT_MIXER_ROUTES("DAC1 Mixer"),
	DSP_OUTPUT_MIXER_ROUTES("DAC2 Mixer"),

	अणु "AIF1 OUT", शून्य, "AIF1 Mixer" पूर्ण,
	अणु "AIF2 OUT", शून्य, "AIF2 Mixer" पूर्ण,
	अणु "AIF3 OUT", शून्य, "AIF3 Mixer" पूर्ण,
	अणु "Left DAC1", शून्य, "DAC1 Mixer" पूर्ण,
	अणु "Right DAC1", शून्य, "DAC1 Mixer" पूर्ण,
	अणु "Left DAC2", शून्य, "DAC2 Mixer" पूर्ण,
	अणु "Right DAC2", शून्य, "DAC2 Mixer" पूर्ण,

	LEFT_OUTPUT_MIXER_ROUTES("Left Lineout1 Mixer"),
	RIGHT_OUTPUT_MIXER_ROUTES("Right Lineout1 Mixer"),
	LEFT_OUTPUT_MIXER_ROUTES("Left Lineout2 Mixer"),
	RIGHT_OUTPUT_MIXER_ROUTES("Right Lineout2 Mixer"),
	LEFT_OUTPUT_MIXER_ROUTES("Left Speaker Mixer"),
	RIGHT_OUTPUT_MIXER_ROUTES("Right Speaker Mixer"),

	अणु "Left Headphone Mixer", "Left DAC2 Switch", "Left DAC2" पूर्ण,
	अणु "Left Headphone Mixer", "Left DAC1 Switch", "Left DAC1" पूर्ण,
	अणु "Left Headphone Mixer", "Input 1 Bypass Switch", "IN1PGA" पूर्ण,
	अणु "Left Headphone Mixer", "Input 2 Bypass Switch", "IN2PGA" पूर्ण,
	अणु "Left Headphone Mixer", "Input 3 Bypass Switch", "IN3PGA" पूर्ण,
	अणु "Left Headphone Mixer", "Input 4 Bypass Switch", "IN4PGA" पूर्ण,
	अणु "Right Headphone Mixer", "Right DAC2 Switch", "Right DAC2" पूर्ण,
	अणु "Right Headphone Mixer", "Right DAC1 Switch", "Right DAC1" पूर्ण,
	अणु "Right Headphone Mixer", "Input 1 Bypass Switch", "IN1PGA" पूर्ण,
	अणु "Right Headphone Mixer", "Input 2 Bypass Switch", "IN2PGA" पूर्ण,
	अणु "Right Headphone Mixer", "Input 3 Bypass Switch", "IN3PGA" पूर्ण,
	अणु "Right Headphone Mixer", "Input 4 Bypass Switch", "IN4PGA" पूर्ण,

	अणु "Left Headphone Mixer", शून्य, "Headphone Enable" पूर्ण,
	अणु "Right Headphone Mixer", शून्य, "Headphone Enable" पूर्ण,

	अणु "Earpiece Mixer", "Right DAC2 Switch", "Right DAC2" पूर्ण,
	अणु "Earpiece Mixer", "Left DAC2 Switch", "Left DAC2" पूर्ण,
	अणु "Earpiece Mixer", "Right DAC1 Switch", "Right DAC1" पूर्ण,
	अणु "Earpiece Mixer", "Left DAC1 Switch", "Left DAC1" पूर्ण,
	अणु "Earpiece Mixer", "Input 1 Bypass Switch", "IN1PGA" पूर्ण,
	अणु "Earpiece Mixer", "Input 2 Bypass Switch", "IN2PGA" पूर्ण,
	अणु "Earpiece Mixer", "Input 3 Bypass Switch", "IN3PGA" पूर्ण,
	अणु "Earpiece Mixer", "Input 4 Bypass Switch", "IN4PGA" पूर्ण,

	अणु "LOUT1L", शून्य, "Left Lineout1 Mixer" पूर्ण,
	अणु "LOUT1R", शून्य, "Right Lineout1 Mixer" पूर्ण,
	अणु "LOUT2L", शून्य, "Left Lineout2 Mixer" पूर्ण,
	अणु "LOUT2R", शून्य, "Right Lineout2 Mixer" पूर्ण,
	अणु "SPKL", शून्य, "Left Speaker Mixer" पूर्ण,
	अणु "SPKR", शून्य, "Right Speaker Mixer" पूर्ण,
	अणु "HPL", शून्य, "Left Headphone Mixer" पूर्ण,
	अणु "HPR", शून्य, "Right Headphone Mixer" पूर्ण,
	अणु "EP", शून्य, "Earpiece Mixer" पूर्ण,

	अणु "IN1PGA", शून्य, "AIN1L" पूर्ण,
	अणु "IN2PGA", शून्य, "AIN2L" पूर्ण,
	अणु "IN3PGA", शून्य, "AIN3L" पूर्ण,
	अणु "IN4PGA", शून्य, "AIN4L" पूर्ण,
	अणु "IN1PGA", शून्य, "AIN1R" पूर्ण,
	अणु "IN2PGA", शून्य, "AIN2R" पूर्ण,
	अणु "IN3PGA", शून्य, "AIN3R" पूर्ण,
	अणु "IN4PGA", शून्य, "AIN4R" पूर्ण,

	अणु "SYSCLK1", शून्य, "PLL1" पूर्ण,
	अणु "SYSCLK2", शून्य, "PLL2" पूर्ण,

	अणु "Left DAC1", शून्य, "SYSCLK1" पूर्ण,
	अणु "Right DAC1", शून्य, "SYSCLK1" पूर्ण,
	अणु "Left DAC2", शून्य, "SYSCLK1" पूर्ण,
	अणु "Right DAC2", शून्य, "SYSCLK1" पूर्ण,
	अणु "Left ADC", शून्य, "SYSCLK1" पूर्ण,
	अणु "Right ADC", शून्य, "SYSCLK1" पूर्ण,

	अणु "DSP", शून्य, "SYSCLK1" पूर्ण,

	अणु "AIF1 Mixer", शून्य, "DSP" पूर्ण,
	अणु "AIF2 Mixer", शून्य, "DSP" पूर्ण,
	अणु "AIF3 Mixer", शून्य, "DSP" पूर्ण,
	अणु "DAC1 Mixer", शून्य, "DSP" पूर्ण,
	अणु "DAC2 Mixer", शून्य, "DSP" पूर्ण,
	अणु "DAC1 Mixer", शून्य, "Playback Engine A" पूर्ण,
	अणु "DAC2 Mixer", शून्य, "Playback Engine B" पूर्ण,
	अणु "Left ADC Mixer", शून्य, "Recording Engine A" पूर्ण,
	अणु "Right ADC Mixer", शून्य, "Recording Engine A" पूर्ण,

	अणु "AIF1 CLK", शून्य, "SYSCLK1", adau1373_check_aअगर_clk पूर्ण,
	अणु "AIF2 CLK", शून्य, "SYSCLK1", adau1373_check_aअगर_clk पूर्ण,
	अणु "AIF3 CLK", शून्य, "SYSCLK1", adau1373_check_aअगर_clk पूर्ण,
	अणु "AIF1 CLK", शून्य, "SYSCLK2", adau1373_check_aअगर_clk पूर्ण,
	अणु "AIF2 CLK", शून्य, "SYSCLK2", adau1373_check_aअगर_clk पूर्ण,
	अणु "AIF3 CLK", शून्य, "SYSCLK2", adau1373_check_aअगर_clk पूर्ण,

	अणु "AIF1 IN", शून्य, "AIF1 CLK" पूर्ण,
	अणु "AIF1 OUT", शून्य, "AIF1 CLK" पूर्ण,
	अणु "AIF2 IN", शून्य, "AIF2 CLK" पूर्ण,
	अणु "AIF2 OUT", शून्य, "AIF2 CLK" पूर्ण,
	अणु "AIF3 IN", शून्य, "AIF3 CLK" पूर्ण,
	अणु "AIF3 OUT", शून्य, "AIF3 CLK" पूर्ण,
	अणु "AIF1 IN", शून्य, "AIF1 IN SRC", adau1373_check_src पूर्ण,
	अणु "AIF1 OUT", शून्य, "AIF1 OUT SRC", adau1373_check_src पूर्ण,
	अणु "AIF2 IN", शून्य, "AIF2 IN SRC", adau1373_check_src पूर्ण,
	अणु "AIF2 OUT", शून्य, "AIF2 OUT SRC", adau1373_check_src पूर्ण,
	अणु "AIF3 IN", शून्य, "AIF3 IN SRC", adau1373_check_src पूर्ण,
	अणु "AIF3 OUT", शून्य, "AIF3 OUT SRC", adau1373_check_src पूर्ण,

	अणु "DMIC1", शून्य, "DMIC1DAT" पूर्ण,
	अणु "DMIC1", शून्य, "SYSCLK1" पूर्ण,
	अणु "DMIC1", शून्य, "Recording Engine A" पूर्ण,
	अणु "DMIC2", शून्य, "DMIC2DAT" पूर्ण,
	अणु "DMIC2", शून्य, "SYSCLK1" पूर्ण,
	अणु "DMIC2", शून्य, "Recording Engine B" पूर्ण,
पूर्ण;

अटल पूर्णांक adau1373_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा adau1373 *adau1373 = snd_soc_component_get_drvdata(component);
	काष्ठा adau1373_dai *adau1373_dai = &adau1373->dais[dai->id];
	अचिन्हित पूर्णांक भाग;
	अचिन्हित पूर्णांक freq;
	अचिन्हित पूर्णांक ctrl;

	freq = adau1373_dai->sysclk;

	अगर (freq % params_rate(params) != 0)
		वापस -EINVAL;

	चयन (freq / params_rate(params)) अणु
	हाल 1024: /* sysclk / 256 */
		भाग = 0;
		अवरोध;
	हाल 1536: /* 2/3 sysclk / 256 */
		भाग = 1;
		अवरोध;
	हाल 2048: /* 1/2 sysclk / 256 */
		भाग = 2;
		अवरोध;
	हाल 3072: /* 1/3 sysclk / 256 */
		भाग = 3;
		अवरोध;
	हाल 4096: /* 1/4 sysclk / 256 */
		भाग = 4;
		अवरोध;
	हाल 6144: /* 1/6 sysclk / 256 */
		भाग = 5;
		अवरोध;
	हाल 5632: /* 2/11 sysclk / 256 */
		भाग = 6;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	adau1373_dai->enable_src = (भाग != 0);

	regmap_update_bits(adau1373->regmap, ADAU1373_BCLKDIV(dai->id),
		ADAU1373_BCLKDIV_SR_MASK | ADAU1373_BCLKDIV_BCLK_MASK,
		(भाग << 2) | ADAU1373_BCLKDIV_64);

	चयन (params_width(params)) अणु
	हाल 16:
		ctrl = ADAU1373_DAI_WLEN_16;
		अवरोध;
	हाल 20:
		ctrl = ADAU1373_DAI_WLEN_20;
		अवरोध;
	हाल 24:
		ctrl = ADAU1373_DAI_WLEN_24;
		अवरोध;
	हाल 32:
		ctrl = ADAU1373_DAI_WLEN_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(adau1373->regmap, ADAU1373_DAI(dai->id),
			ADAU1373_DAI_WLEN_MASK, ctrl);
पूर्ण

अटल पूर्णांक adau1373_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा adau1373 *adau1373 = snd_soc_component_get_drvdata(component);
	काष्ठा adau1373_dai *adau1373_dai = &adau1373->dais[dai->id];
	अचिन्हित पूर्णांक ctrl;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		ctrl = ADAU1373_DAI_MASTER;
		adau1373_dai->master = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		ctrl = 0;
		adau1373_dai->master = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		ctrl |= ADAU1373_DAI_FORMAT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		ctrl |= ADAU1373_DAI_FORMAT_LEFT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		ctrl |= ADAU1373_DAI_FORMAT_RIGHT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		ctrl |= ADAU1373_DAI_FORMAT_DSP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		ctrl |= ADAU1373_DAI_INVERT_BCLK;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		ctrl |= ADAU1373_DAI_INVERT_LRCLK;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		ctrl |= ADAU1373_DAI_INVERT_LRCLK | ADAU1373_DAI_INVERT_BCLK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(adau1373->regmap, ADAU1373_DAI(dai->id),
		~ADAU1373_DAI_WLEN_MASK, ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक adau1373_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
	पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा adau1373 *adau1373 = snd_soc_component_get_drvdata(dai->component);
	काष्ठा adau1373_dai *adau1373_dai = &adau1373->dais[dai->id];

	चयन (clk_id) अणु
	हाल ADAU1373_CLK_SRC_PLL1:
	हाल ADAU1373_CLK_SRC_PLL2:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	adau1373_dai->sysclk = freq;
	adau1373_dai->clk_src = clk_id;

	regmap_update_bits(adau1373->regmap, ADAU1373_BCLKDIV(dai->id),
		ADAU1373_BCLKDIV_SOURCE, clk_id << 5);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops adau1373_dai_ops = अणु
	.hw_params	= adau1373_hw_params,
	.set_sysclk	= adau1373_set_dai_sysclk,
	.set_fmt	= adau1373_set_dai_fmt,
पूर्ण;

#घोषणा ADAU1373_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
	SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver adau1373_dai_driver[] = अणु
	अणु
		.id = 0,
		.name = "adau1373-aif1",
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = ADAU1373_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = ADAU1373_FORMATS,
		पूर्ण,
		.ops = &adau1373_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
	अणु
		.id = 1,
		.name = "adau1373-aif2",
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = ADAU1373_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = ADAU1373_FORMATS,
		पूर्ण,
		.ops = &adau1373_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
	अणु
		.id = 2,
		.name = "adau1373-aif3",
		.playback = अणु
			.stream_name = "AIF3 Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = ADAU1373_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF3 Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = ADAU1373_FORMATS,
		पूर्ण,
		.ops = &adau1373_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक adau1373_set_pll(काष्ठा snd_soc_component *component, पूर्णांक pll_id,
	पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा adau1373 *adau1373 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक dpll_भाग = 0;
	uपूर्णांक8_t pll_regs[5];
	पूर्णांक ret;

	चयन (pll_id) अणु
	हाल ADAU1373_PLL1:
	हाल ADAU1373_PLL2:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (source) अणु
	हाल ADAU1373_PLL_SRC_BCLK1:
	हाल ADAU1373_PLL_SRC_BCLK2:
	हाल ADAU1373_PLL_SRC_BCLK3:
	हाल ADAU1373_PLL_SRC_LRCLK1:
	हाल ADAU1373_PLL_SRC_LRCLK2:
	हाल ADAU1373_PLL_SRC_LRCLK3:
	हाल ADAU1373_PLL_SRC_MCLK1:
	हाल ADAU1373_PLL_SRC_MCLK2:
	हाल ADAU1373_PLL_SRC_GPIO1:
	हाल ADAU1373_PLL_SRC_GPIO2:
	हाल ADAU1373_PLL_SRC_GPIO3:
	हाल ADAU1373_PLL_SRC_GPIO4:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (freq_in < 7813 || freq_in > 27000000)
		वापस -EINVAL;

	अगर (freq_out < 45158000 || freq_out > 49152000)
		वापस -EINVAL;

	/* APLL input needs to be >= 8Mhz, so in हाल freq_in is less we use the
	 * DPLL to get it there. DPLL_out = (DPLL_in / भाग) * 1024 */
	जबतक (freq_in < 8000000) अणु
		freq_in *= 2;
		dpll_भाग++;
	पूर्ण

	ret = adau_calc_pll_cfg(freq_in, freq_out, pll_regs);
	अगर (ret)
		वापस -EINVAL;

	अगर (dpll_भाग) अणु
		dpll_भाग = 11 - dpll_भाग;
		regmap_update_bits(adau1373->regmap, ADAU1373_PLL_CTRL6(pll_id),
			ADAU1373_PLL_CTRL6_DPLL_BYPASS, 0);
	पूर्ण अन्यथा अणु
		regmap_update_bits(adau1373->regmap, ADAU1373_PLL_CTRL6(pll_id),
			ADAU1373_PLL_CTRL6_DPLL_BYPASS,
			ADAU1373_PLL_CTRL6_DPLL_BYPASS);
	पूर्ण

	regmap_ग_लिखो(adau1373->regmap, ADAU1373_DPLL_CTRL(pll_id),
		(source << 4) | dpll_भाग);
	regmap_ग_लिखो(adau1373->regmap, ADAU1373_PLL_CTRL1(pll_id), pll_regs[0]);
	regmap_ग_लिखो(adau1373->regmap, ADAU1373_PLL_CTRL2(pll_id), pll_regs[1]);
	regmap_ग_लिखो(adau1373->regmap, ADAU1373_PLL_CTRL3(pll_id), pll_regs[2]);
	regmap_ग_लिखो(adau1373->regmap, ADAU1373_PLL_CTRL4(pll_id), pll_regs[3]);
	regmap_ग_लिखो(adau1373->regmap, ADAU1373_PLL_CTRL5(pll_id), pll_regs[4]);

	/* Set sysclk to pll_rate / 4 */
	regmap_update_bits(adau1373->regmap, ADAU1373_CLK_SRC_DIV(pll_id), 0x3f, 0x09);

	वापस 0;
पूर्ण

अटल व्योम adau1373_load_drc_settings(काष्ठा adau1373 *adau1373,
	अचिन्हित पूर्णांक nr, uपूर्णांक8_t *drc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ADAU1373_DRC_SIZE; ++i)
		regmap_ग_लिखो(adau1373->regmap, ADAU1373_DRC(nr) + i, drc[i]);
पूर्ण

अटल bool adau1373_valid_micbias(क्रमागत adau1373_micbias_voltage micbias)
अणु
	चयन (micbias) अणु
	हाल ADAU1373_MICBIAS_2_9V:
	हाल ADAU1373_MICBIAS_2_2V:
	हाल ADAU1373_MICBIAS_2_6V:
	हाल ADAU1373_MICBIAS_1_8V:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक adau1373_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा adau1373 *adau1373 = snd_soc_component_get_drvdata(component);
	काष्ठा adau1373_platक्रमm_data *pdata = component->dev->platक्रमm_data;
	bool lineout_dअगरferential = false;
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	अगर (pdata) अणु
		अगर (pdata->num_drc > ARRAY_SIZE(pdata->drc_setting))
			वापस -EINVAL;

		अगर (!adau1373_valid_micbias(pdata->micbias1) ||
			!adau1373_valid_micbias(pdata->micbias2))
			वापस -EINVAL;

		क्रम (i = 0; i < pdata->num_drc; ++i) अणु
			adau1373_load_drc_settings(adau1373, i,
				pdata->drc_setting[i]);
		पूर्ण

		snd_soc_add_component_controls(component, adau1373_drc_controls,
			pdata->num_drc);

		val = 0;
		क्रम (i = 0; i < 4; ++i) अणु
			अगर (pdata->input_dअगरferential[i])
				val |= BIT(i);
		पूर्ण
		regmap_ग_लिखो(adau1373->regmap, ADAU1373_INPUT_MODE, val);

		val = 0;
		अगर (pdata->lineout_dअगरferential)
			val |= ADAU1373_OUTPUT_CTRL_LDIFF;
		अगर (pdata->lineout_ground_sense)
			val |= ADAU1373_OUTPUT_CTRL_LNFBEN;
		regmap_ग_लिखो(adau1373->regmap, ADAU1373_OUTPUT_CTRL, val);

		lineout_dअगरferential = pdata->lineout_dअगरferential;

		regmap_ग_लिखो(adau1373->regmap, ADAU1373_EP_CTRL,
			(pdata->micbias1 << ADAU1373_EP_CTRL_MICBIAS1_OFFSET) |
			(pdata->micbias2 << ADAU1373_EP_CTRL_MICBIAS2_OFFSET));
	पूर्ण

	अगर (!lineout_dअगरferential) अणु
		snd_soc_add_component_controls(component, adau1373_lineout2_controls,
			ARRAY_SIZE(adau1373_lineout2_controls));
	पूर्ण

	regmap_ग_लिखो(adau1373->regmap, ADAU1373_ADC_CTRL,
	    ADAU1373_ADC_CTRL_RESET_FORCE | ADAU1373_ADC_CTRL_PEAK_DETECT);

	वापस 0;
पूर्ण

अटल पूर्णांक adau1373_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा adau1373 *adau1373 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		regmap_update_bits(adau1373->regmap, ADAU1373_PWDN_CTRL3,
			ADAU1373_PWDN_CTRL3_PWR_EN, ADAU1373_PWDN_CTRL3_PWR_EN);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		regmap_update_bits(adau1373->regmap, ADAU1373_PWDN_CTRL3,
			ADAU1373_PWDN_CTRL3_PWR_EN, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adau1373_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा adau1373 *adau1373 = snd_soc_component_get_drvdata(component);

	regcache_sync(adau1373->regmap);

	वापस 0;
पूर्ण

अटल bool adau1373_रेजिस्टर_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ADAU1373_SOFT_RESET:
	हाल ADAU1373_ADC_DAC_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config adau1373_regmap_config = अणु
	.val_bits = 8,
	.reg_bits = 8,

	.अस्थिर_reg = adau1373_रेजिस्टर_अस्थिर,
	.max_रेजिस्टर = ADAU1373_SOFT_RESET,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = adau1373_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(adau1373_reg_शेषs),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver adau1373_component_driver = अणु
	.probe			= adau1373_probe,
	.resume			= adau1373_resume,
	.set_bias_level		= adau1373_set_bias_level,
	.set_pll		= adau1373_set_pll,
	.controls		= adau1373_controls,
	.num_controls		= ARRAY_SIZE(adau1373_controls),
	.dapm_widमाला_लो		= adau1373_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(adau1373_dapm_widमाला_लो),
	.dapm_routes		= adau1373_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(adau1373_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक adau1373_i2c_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adau1373 *adau1373;
	पूर्णांक ret;

	adau1373 = devm_kzalloc(&client->dev, माप(*adau1373), GFP_KERNEL);
	अगर (!adau1373)
		वापस -ENOMEM;

	adau1373->regmap = devm_regmap_init_i2c(client,
		&adau1373_regmap_config);
	अगर (IS_ERR(adau1373->regmap))
		वापस PTR_ERR(adau1373->regmap);

	regmap_ग_लिखो(adau1373->regmap, ADAU1373_SOFT_RESET, 0x00);

	dev_set_drvdata(&client->dev, adau1373);

	ret = devm_snd_soc_रेजिस्टर_component(&client->dev,
			&adau1373_component_driver,
			adau1373_dai_driver, ARRAY_SIZE(adau1373_dai_driver));
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adau1373_i2c_id[] = अणु
	अणु "adau1373", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adau1373_i2c_id);

अटल काष्ठा i2c_driver adau1373_i2c_driver = अणु
	.driver = अणु
		.name = "adau1373",
	पूर्ण,
	.probe = adau1373_i2c_probe,
	.id_table = adau1373_i2c_id,
पूर्ण;

module_i2c_driver(adau1373_i2c_driver);

MODULE_DESCRIPTION("ASoC ADAU1373 driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL");
