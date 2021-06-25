<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs42l42.c -- CS42L42 ALSA SoC audio driver
 *
 * Copyright 2016 Cirrus Logic, Inc.
 *
 * Author: James Schulman <james.schulman@cirrus.com>
 * Author: Brian Austin <brian.austin@cirrus.com>
 * Author: Michael White <michael.white@cirrus.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/version.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <dt-bindings/sound/cs42l42.h>

#समावेश "cs42l42.h"

अटल स्थिर काष्ठा reg_शेष cs42l42_reg_शेषs[] = अणु
	अणु CS42L42_FRZ_CTL,			0x00 पूर्ण,
	अणु CS42L42_SRC_CTL,			0x10 पूर्ण,
	अणु CS42L42_MCLK_STATUS,			0x02 पूर्ण,
	अणु CS42L42_MCLK_CTL,			0x02 पूर्ण,
	अणु CS42L42_SFTRAMP_RATE,			0xA4 पूर्ण,
	अणु CS42L42_I2C_DEBOUNCE,			0x88 पूर्ण,
	अणु CS42L42_I2C_STRETCH,			0x03 पूर्ण,
	अणु CS42L42_I2C_TIMEOUT,			0xB7 पूर्ण,
	अणु CS42L42_PWR_CTL1,			0xFF पूर्ण,
	अणु CS42L42_PWR_CTL2,			0x84 पूर्ण,
	अणु CS42L42_PWR_CTL3,			0x20 पूर्ण,
	अणु CS42L42_RSENSE_CTL1,			0x40 पूर्ण,
	अणु CS42L42_RSENSE_CTL2,			0x00 पूर्ण,
	अणु CS42L42_OSC_SWITCH,			0x00 पूर्ण,
	अणु CS42L42_OSC_SWITCH_STATUS,		0x05 पूर्ण,
	अणु CS42L42_RSENSE_CTL3,			0x1B पूर्ण,
	अणु CS42L42_TSENSE_CTL,			0x1B पूर्ण,
	अणु CS42L42_TSRS_INT_DISABLE,		0x00 पूर्ण,
	अणु CS42L42_TRSENSE_STATUS,		0x00 पूर्ण,
	अणु CS42L42_HSDET_CTL1,			0x77 पूर्ण,
	अणु CS42L42_HSDET_CTL2,			0x00 पूर्ण,
	अणु CS42L42_HS_SWITCH_CTL,		0xF3 पूर्ण,
	अणु CS42L42_HS_DET_STATUS,		0x00 पूर्ण,
	अणु CS42L42_HS_CLAMP_DISABLE,		0x00 पूर्ण,
	अणु CS42L42_MCLK_SRC_SEL,			0x00 पूर्ण,
	अणु CS42L42_SPDIF_CLK_CFG,		0x00 पूर्ण,
	अणु CS42L42_FSYNC_PW_LOWER,		0x00 पूर्ण,
	अणु CS42L42_FSYNC_PW_UPPER,		0x00 पूर्ण,
	अणु CS42L42_FSYNC_P_LOWER,		0xF9 पूर्ण,
	अणु CS42L42_FSYNC_P_UPPER,		0x00 पूर्ण,
	अणु CS42L42_ASP_CLK_CFG,			0x00 पूर्ण,
	अणु CS42L42_ASP_FRM_CFG,			0x10 पूर्ण,
	अणु CS42L42_FS_RATE_EN,			0x00 पूर्ण,
	अणु CS42L42_IN_ASRC_CLK,			0x00 पूर्ण,
	अणु CS42L42_OUT_ASRC_CLK,			0x00 पूर्ण,
	अणु CS42L42_PLL_DIV_CFG1,			0x00 पूर्ण,
	अणु CS42L42_ADC_OVFL_STATUS,		0x00 पूर्ण,
	अणु CS42L42_MIXER_STATUS,			0x00 पूर्ण,
	अणु CS42L42_SRC_STATUS,			0x00 पूर्ण,
	अणु CS42L42_ASP_RX_STATUS,		0x00 पूर्ण,
	अणु CS42L42_ASP_TX_STATUS,		0x00 पूर्ण,
	अणु CS42L42_CODEC_STATUS,			0x00 पूर्ण,
	अणु CS42L42_DET_INT_STATUS1,		0x00 पूर्ण,
	अणु CS42L42_DET_INT_STATUS2,		0x00 पूर्ण,
	अणु CS42L42_SRCPL_INT_STATUS,		0x00 पूर्ण,
	अणु CS42L42_VPMON_STATUS,			0x00 पूर्ण,
	अणु CS42L42_PLL_LOCK_STATUS,		0x00 पूर्ण,
	अणु CS42L42_TSRS_PLUG_STATUS,		0x00 पूर्ण,
	अणु CS42L42_ADC_OVFL_INT_MASK,		0x01 पूर्ण,
	अणु CS42L42_MIXER_INT_MASK,		0x0F पूर्ण,
	अणु CS42L42_SRC_INT_MASK,			0x0F पूर्ण,
	अणु CS42L42_ASP_RX_INT_MASK,		0x1F पूर्ण,
	अणु CS42L42_ASP_TX_INT_MASK,		0x0F पूर्ण,
	अणु CS42L42_CODEC_INT_MASK,		0x03 पूर्ण,
	अणु CS42L42_SRCPL_INT_MASK,		0xFF पूर्ण,
	अणु CS42L42_VPMON_INT_MASK,		0x01 पूर्ण,
	अणु CS42L42_PLL_LOCK_INT_MASK,		0x01 पूर्ण,
	अणु CS42L42_TSRS_PLUG_INT_MASK,		0x0F पूर्ण,
	अणु CS42L42_PLL_CTL1,			0x00 पूर्ण,
	अणु CS42L42_PLL_DIV_FRAC0,		0x00 पूर्ण,
	अणु CS42L42_PLL_DIV_FRAC1,		0x00 पूर्ण,
	अणु CS42L42_PLL_DIV_FRAC2,		0x00 पूर्ण,
	अणु CS42L42_PLL_DIV_INT,			0x40 पूर्ण,
	अणु CS42L42_PLL_CTL3,			0x10 पूर्ण,
	अणु CS42L42_PLL_CAL_RATIO,		0x80 पूर्ण,
	अणु CS42L42_PLL_CTL4,			0x03 पूर्ण,
	अणु CS42L42_LOAD_DET_RCSTAT,		0x00 पूर्ण,
	अणु CS42L42_LOAD_DET_DONE,		0x00 पूर्ण,
	अणु CS42L42_LOAD_DET_EN,			0x00 पूर्ण,
	अणु CS42L42_HSBIAS_SC_AUTOCTL,		0x03 पूर्ण,
	अणु CS42L42_WAKE_CTL,			0xC0 पूर्ण,
	अणु CS42L42_ADC_DISABLE_MUTE,		0x00 पूर्ण,
	अणु CS42L42_TIPSENSE_CTL,			0x02 पूर्ण,
	अणु CS42L42_MISC_DET_CTL,			0x03 पूर्ण,
	अणु CS42L42_MIC_DET_CTL1,			0x1F पूर्ण,
	अणु CS42L42_MIC_DET_CTL2,			0x2F पूर्ण,
	अणु CS42L42_DET_STATUS1,			0x00 पूर्ण,
	अणु CS42L42_DET_STATUS2,			0x00 पूर्ण,
	अणु CS42L42_DET_INT1_MASK,		0xE0 पूर्ण,
	अणु CS42L42_DET_INT2_MASK,		0xFF पूर्ण,
	अणु CS42L42_HS_BIAS_CTL,			0xC2 पूर्ण,
	अणु CS42L42_ADC_CTL,			0x00 पूर्ण,
	अणु CS42L42_ADC_VOLUME,			0x00 पूर्ण,
	अणु CS42L42_ADC_WNF_HPF_CTL,		0x71 पूर्ण,
	अणु CS42L42_DAC_CTL1,			0x00 पूर्ण,
	अणु CS42L42_DAC_CTL2,			0x02 पूर्ण,
	अणु CS42L42_HP_CTL,			0x0D पूर्ण,
	अणु CS42L42_CLASSH_CTL,			0x07 पूर्ण,
	अणु CS42L42_MIXER_CHA_VOL,		0x3F पूर्ण,
	अणु CS42L42_MIXER_ADC_VOL,		0x3F पूर्ण,
	अणु CS42L42_MIXER_CHB_VOL,		0x3F पूर्ण,
	अणु CS42L42_EQ_COEF_IN0,			0x22 पूर्ण,
	अणु CS42L42_EQ_COEF_IN1,			0x00 पूर्ण,
	अणु CS42L42_EQ_COEF_IN2,			0x00 पूर्ण,
	अणु CS42L42_EQ_COEF_IN3,			0x00 पूर्ण,
	अणु CS42L42_EQ_COEF_RW,			0x00 पूर्ण,
	अणु CS42L42_EQ_COEF_OUT0,			0x00 पूर्ण,
	अणु CS42L42_EQ_COEF_OUT1,			0x00 पूर्ण,
	अणु CS42L42_EQ_COEF_OUT2,			0x00 पूर्ण,
	अणु CS42L42_EQ_COEF_OUT3,			0x00 पूर्ण,
	अणु CS42L42_EQ_INIT_STAT,			0x00 पूर्ण,
	अणु CS42L42_EQ_START_FILT,		0x00 पूर्ण,
	अणु CS42L42_EQ_MUTE_CTL,			0x00 पूर्ण,
	अणु CS42L42_SP_RX_CH_SEL,			0x04 पूर्ण,
	अणु CS42L42_SP_RX_ISOC_CTL,		0x04 पूर्ण,
	अणु CS42L42_SP_RX_FS,			0x8C पूर्ण,
	अणु CS42l42_SPDIF_CH_SEL,			0x0E पूर्ण,
	अणु CS42L42_SP_TX_ISOC_CTL,		0x04 पूर्ण,
	अणु CS42L42_SP_TX_FS,			0xCC पूर्ण,
	अणु CS42L42_SPDIF_SW_CTL1,		0x3F पूर्ण,
	अणु CS42L42_SRC_SDIN_FS,			0x40 पूर्ण,
	अणु CS42L42_SRC_SDOUT_FS,			0x40 पूर्ण,
	अणु CS42L42_SPDIF_CTL1,			0x01 पूर्ण,
	अणु CS42L42_SPDIF_CTL2,			0x00 पूर्ण,
	अणु CS42L42_SPDIF_CTL3,			0x00 पूर्ण,
	अणु CS42L42_SPDIF_CTL4,			0x42 पूर्ण,
	अणु CS42L42_ASP_TX_SZ_EN,			0x00 पूर्ण,
	अणु CS42L42_ASP_TX_CH_EN,			0x00 पूर्ण,
	अणु CS42L42_ASP_TX_CH_AP_RES,		0x0F पूर्ण,
	अणु CS42L42_ASP_TX_CH1_BIT_MSB,		0x00 पूर्ण,
	अणु CS42L42_ASP_TX_CH1_BIT_LSB,		0x00 पूर्ण,
	अणु CS42L42_ASP_TX_HIZ_DLY_CFG,		0x00 पूर्ण,
	अणु CS42L42_ASP_TX_CH2_BIT_MSB,		0x00 पूर्ण,
	अणु CS42L42_ASP_TX_CH2_BIT_LSB,		0x00 पूर्ण,
	अणु CS42L42_ASP_RX_DAI0_EN,		0x00 पूर्ण,
	अणु CS42L42_ASP_RX_DAI0_CH1_AP_RES,	0x03 पूर्ण,
	अणु CS42L42_ASP_RX_DAI0_CH1_BIT_MSB,	0x00 पूर्ण,
	अणु CS42L42_ASP_RX_DAI0_CH1_BIT_LSB,	0x00 पूर्ण,
	अणु CS42L42_ASP_RX_DAI0_CH2_AP_RES,	0x03 पूर्ण,
	अणु CS42L42_ASP_RX_DAI0_CH2_BIT_MSB,	0x00 पूर्ण,
	अणु CS42L42_ASP_RX_DAI0_CH2_BIT_LSB,	0x00 पूर्ण,
	अणु CS42L42_ASP_RX_DAI0_CH3_AP_RES,	0x03 पूर्ण,
	अणु CS42L42_ASP_RX_DAI0_CH3_BIT_MSB,	0x00 पूर्ण,
	अणु CS42L42_ASP_RX_DAI0_CH3_BIT_LSB,	0x00 पूर्ण,
	अणु CS42L42_ASP_RX_DAI0_CH4_AP_RES,	0x03 पूर्ण,
	अणु CS42L42_ASP_RX_DAI0_CH4_BIT_MSB,	0x00 पूर्ण,
	अणु CS42L42_ASP_RX_DAI0_CH4_BIT_LSB,	0x00 पूर्ण,
	अणु CS42L42_ASP_RX_DAI1_CH1_AP_RES,	0x03 पूर्ण,
	अणु CS42L42_ASP_RX_DAI1_CH1_BIT_MSB,	0x00 पूर्ण,
	अणु CS42L42_ASP_RX_DAI1_CH1_BIT_LSB,	0x00 पूर्ण,
	अणु CS42L42_ASP_RX_DAI1_CH2_AP_RES,	0x03 पूर्ण,
	अणु CS42L42_ASP_RX_DAI1_CH2_BIT_MSB,	0x00 पूर्ण,
	अणु CS42L42_ASP_RX_DAI1_CH2_BIT_LSB,	0x00 पूर्ण,
	अणु CS42L42_SUB_REVID,			0x03 पूर्ण,
पूर्ण;

अटल bool cs42l42_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS42L42_PAGE_REGISTER:
	हाल CS42L42_DEVID_AB:
	हाल CS42L42_DEVID_CD:
	हाल CS42L42_DEVID_E:
	हाल CS42L42_FABID:
	हाल CS42L42_REVID:
	हाल CS42L42_FRZ_CTL:
	हाल CS42L42_SRC_CTL:
	हाल CS42L42_MCLK_STATUS:
	हाल CS42L42_MCLK_CTL:
	हाल CS42L42_SFTRAMP_RATE:
	हाल CS42L42_I2C_DEBOUNCE:
	हाल CS42L42_I2C_STRETCH:
	हाल CS42L42_I2C_TIMEOUT:
	हाल CS42L42_PWR_CTL1:
	हाल CS42L42_PWR_CTL2:
	हाल CS42L42_PWR_CTL3:
	हाल CS42L42_RSENSE_CTL1:
	हाल CS42L42_RSENSE_CTL2:
	हाल CS42L42_OSC_SWITCH:
	हाल CS42L42_OSC_SWITCH_STATUS:
	हाल CS42L42_RSENSE_CTL3:
	हाल CS42L42_TSENSE_CTL:
	हाल CS42L42_TSRS_INT_DISABLE:
	हाल CS42L42_TRSENSE_STATUS:
	हाल CS42L42_HSDET_CTL1:
	हाल CS42L42_HSDET_CTL2:
	हाल CS42L42_HS_SWITCH_CTL:
	हाल CS42L42_HS_DET_STATUS:
	हाल CS42L42_HS_CLAMP_DISABLE:
	हाल CS42L42_MCLK_SRC_SEL:
	हाल CS42L42_SPDIF_CLK_CFG:
	हाल CS42L42_FSYNC_PW_LOWER:
	हाल CS42L42_FSYNC_PW_UPPER:
	हाल CS42L42_FSYNC_P_LOWER:
	हाल CS42L42_FSYNC_P_UPPER:
	हाल CS42L42_ASP_CLK_CFG:
	हाल CS42L42_ASP_FRM_CFG:
	हाल CS42L42_FS_RATE_EN:
	हाल CS42L42_IN_ASRC_CLK:
	हाल CS42L42_OUT_ASRC_CLK:
	हाल CS42L42_PLL_DIV_CFG1:
	हाल CS42L42_ADC_OVFL_STATUS:
	हाल CS42L42_MIXER_STATUS:
	हाल CS42L42_SRC_STATUS:
	हाल CS42L42_ASP_RX_STATUS:
	हाल CS42L42_ASP_TX_STATUS:
	हाल CS42L42_CODEC_STATUS:
	हाल CS42L42_DET_INT_STATUS1:
	हाल CS42L42_DET_INT_STATUS2:
	हाल CS42L42_SRCPL_INT_STATUS:
	हाल CS42L42_VPMON_STATUS:
	हाल CS42L42_PLL_LOCK_STATUS:
	हाल CS42L42_TSRS_PLUG_STATUS:
	हाल CS42L42_ADC_OVFL_INT_MASK:
	हाल CS42L42_MIXER_INT_MASK:
	हाल CS42L42_SRC_INT_MASK:
	हाल CS42L42_ASP_RX_INT_MASK:
	हाल CS42L42_ASP_TX_INT_MASK:
	हाल CS42L42_CODEC_INT_MASK:
	हाल CS42L42_SRCPL_INT_MASK:
	हाल CS42L42_VPMON_INT_MASK:
	हाल CS42L42_PLL_LOCK_INT_MASK:
	हाल CS42L42_TSRS_PLUG_INT_MASK:
	हाल CS42L42_PLL_CTL1:
	हाल CS42L42_PLL_DIV_FRAC0:
	हाल CS42L42_PLL_DIV_FRAC1:
	हाल CS42L42_PLL_DIV_FRAC2:
	हाल CS42L42_PLL_DIV_INT:
	हाल CS42L42_PLL_CTL3:
	हाल CS42L42_PLL_CAL_RATIO:
	हाल CS42L42_PLL_CTL4:
	हाल CS42L42_LOAD_DET_RCSTAT:
	हाल CS42L42_LOAD_DET_DONE:
	हाल CS42L42_LOAD_DET_EN:
	हाल CS42L42_HSBIAS_SC_AUTOCTL:
	हाल CS42L42_WAKE_CTL:
	हाल CS42L42_ADC_DISABLE_MUTE:
	हाल CS42L42_TIPSENSE_CTL:
	हाल CS42L42_MISC_DET_CTL:
	हाल CS42L42_MIC_DET_CTL1:
	हाल CS42L42_MIC_DET_CTL2:
	हाल CS42L42_DET_STATUS1:
	हाल CS42L42_DET_STATUS2:
	हाल CS42L42_DET_INT1_MASK:
	हाल CS42L42_DET_INT2_MASK:
	हाल CS42L42_HS_BIAS_CTL:
	हाल CS42L42_ADC_CTL:
	हाल CS42L42_ADC_VOLUME:
	हाल CS42L42_ADC_WNF_HPF_CTL:
	हाल CS42L42_DAC_CTL1:
	हाल CS42L42_DAC_CTL2:
	हाल CS42L42_HP_CTL:
	हाल CS42L42_CLASSH_CTL:
	हाल CS42L42_MIXER_CHA_VOL:
	हाल CS42L42_MIXER_ADC_VOL:
	हाल CS42L42_MIXER_CHB_VOL:
	हाल CS42L42_EQ_COEF_IN0:
	हाल CS42L42_EQ_COEF_IN1:
	हाल CS42L42_EQ_COEF_IN2:
	हाल CS42L42_EQ_COEF_IN3:
	हाल CS42L42_EQ_COEF_RW:
	हाल CS42L42_EQ_COEF_OUT0:
	हाल CS42L42_EQ_COEF_OUT1:
	हाल CS42L42_EQ_COEF_OUT2:
	हाल CS42L42_EQ_COEF_OUT3:
	हाल CS42L42_EQ_INIT_STAT:
	हाल CS42L42_EQ_START_FILT:
	हाल CS42L42_EQ_MUTE_CTL:
	हाल CS42L42_SP_RX_CH_SEL:
	हाल CS42L42_SP_RX_ISOC_CTL:
	हाल CS42L42_SP_RX_FS:
	हाल CS42l42_SPDIF_CH_SEL:
	हाल CS42L42_SP_TX_ISOC_CTL:
	हाल CS42L42_SP_TX_FS:
	हाल CS42L42_SPDIF_SW_CTL1:
	हाल CS42L42_SRC_SDIN_FS:
	हाल CS42L42_SRC_SDOUT_FS:
	हाल CS42L42_SPDIF_CTL1:
	हाल CS42L42_SPDIF_CTL2:
	हाल CS42L42_SPDIF_CTL3:
	हाल CS42L42_SPDIF_CTL4:
	हाल CS42L42_ASP_TX_SZ_EN:
	हाल CS42L42_ASP_TX_CH_EN:
	हाल CS42L42_ASP_TX_CH_AP_RES:
	हाल CS42L42_ASP_TX_CH1_BIT_MSB:
	हाल CS42L42_ASP_TX_CH1_BIT_LSB:
	हाल CS42L42_ASP_TX_HIZ_DLY_CFG:
	हाल CS42L42_ASP_TX_CH2_BIT_MSB:
	हाल CS42L42_ASP_TX_CH2_BIT_LSB:
	हाल CS42L42_ASP_RX_DAI0_EN:
	हाल CS42L42_ASP_RX_DAI0_CH1_AP_RES:
	हाल CS42L42_ASP_RX_DAI0_CH1_BIT_MSB:
	हाल CS42L42_ASP_RX_DAI0_CH1_BIT_LSB:
	हाल CS42L42_ASP_RX_DAI0_CH2_AP_RES:
	हाल CS42L42_ASP_RX_DAI0_CH2_BIT_MSB:
	हाल CS42L42_ASP_RX_DAI0_CH2_BIT_LSB:
	हाल CS42L42_ASP_RX_DAI0_CH3_AP_RES:
	हाल CS42L42_ASP_RX_DAI0_CH3_BIT_MSB:
	हाल CS42L42_ASP_RX_DAI0_CH3_BIT_LSB:
	हाल CS42L42_ASP_RX_DAI0_CH4_AP_RES:
	हाल CS42L42_ASP_RX_DAI0_CH4_BIT_MSB:
	हाल CS42L42_ASP_RX_DAI0_CH4_BIT_LSB:
	हाल CS42L42_ASP_RX_DAI1_CH1_AP_RES:
	हाल CS42L42_ASP_RX_DAI1_CH1_BIT_MSB:
	हाल CS42L42_ASP_RX_DAI1_CH1_BIT_LSB:
	हाल CS42L42_ASP_RX_DAI1_CH2_AP_RES:
	हाल CS42L42_ASP_RX_DAI1_CH2_BIT_MSB:
	हाल CS42L42_ASP_RX_DAI1_CH2_BIT_LSB:
	हाल CS42L42_SUB_REVID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs42l42_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS42L42_DEVID_AB:
	हाल CS42L42_DEVID_CD:
	हाल CS42L42_DEVID_E:
	हाल CS42L42_MCLK_STATUS:
	हाल CS42L42_TRSENSE_STATUS:
	हाल CS42L42_HS_DET_STATUS:
	हाल CS42L42_ADC_OVFL_STATUS:
	हाल CS42L42_MIXER_STATUS:
	हाल CS42L42_SRC_STATUS:
	हाल CS42L42_ASP_RX_STATUS:
	हाल CS42L42_ASP_TX_STATUS:
	हाल CS42L42_CODEC_STATUS:
	हाल CS42L42_DET_INT_STATUS1:
	हाल CS42L42_DET_INT_STATUS2:
	हाल CS42L42_SRCPL_INT_STATUS:
	हाल CS42L42_VPMON_STATUS:
	हाल CS42L42_PLL_LOCK_STATUS:
	हाल CS42L42_TSRS_PLUG_STATUS:
	हाल CS42L42_LOAD_DET_RCSTAT:
	हाल CS42L42_LOAD_DET_DONE:
	हाल CS42L42_DET_STATUS1:
	हाल CS42L42_DET_STATUS2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_range_cfg cs42l42_page_range = अणु
	.name = "Pages",
	.range_min = 0,
	.range_max = CS42L42_MAX_REGISTER,
	.selector_reg = CS42L42_PAGE_REGISTER,
	.selector_mask = 0xff,
	.selector_shअगरt = 0,
	.winकरोw_start = 0,
	.winकरोw_len = 256,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cs42l42_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.पढ़ोable_reg = cs42l42_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = cs42l42_अस्थिर_रेजिस्टर,

	.ranges = &cs42l42_page_range,
	.num_ranges = 1,

	.max_रेजिस्टर = CS42L42_MAX_REGISTER,
	.reg_शेषs = cs42l42_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(cs42l42_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,

	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल DECLARE_TLV_DB_SCALE(adc_tlv, -9600, 100, false);
अटल DECLARE_TLV_DB_SCALE(mixer_tlv, -6300, 100, true);

अटल स्थिर अक्षर * स्थिर cs42l42_hpf_freq_text[] = अणु
	"1.86Hz", "120Hz", "235Hz", "466Hz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(cs42l42_hpf_freq_क्रमागत, CS42L42_ADC_WNF_HPF_CTL,
			    CS42L42_ADC_HPF_CF_SHIFT,
			    cs42l42_hpf_freq_text);

अटल स्थिर अक्षर * स्थिर cs42l42_wnf3_freq_text[] = अणु
	"160Hz", "180Hz", "200Hz", "220Hz",
	"240Hz", "260Hz", "280Hz", "300Hz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(cs42l42_wnf3_freq_क्रमागत, CS42L42_ADC_WNF_HPF_CTL,
			    CS42L42_ADC_WNF_CF_SHIFT,
			    cs42l42_wnf3_freq_text);

अटल स्थिर अक्षर * स्थिर cs42l42_wnf05_freq_text[] = अणु
	"280Hz", "315Hz", "350Hz", "385Hz",
	"420Hz", "455Hz", "490Hz", "525Hz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(cs42l42_wnf05_freq_क्रमागत, CS42L42_ADC_WNF_HPF_CTL,
			    CS42L42_ADC_WNF_CF_SHIFT,
			    cs42l42_wnf05_freq_text);

अटल स्थिर काष्ठा snd_kcontrol_new cs42l42_snd_controls[] = अणु
	/* ADC Volume and Filter Controls */
	SOC_SINGLE("ADC Notch Switch", CS42L42_ADC_CTL,
				CS42L42_ADC_NOTCH_DIS_SHIFT, true, false),
	SOC_SINGLE("ADC Weak Force Switch", CS42L42_ADC_CTL,
				CS42L42_ADC_FORCE_WEAK_VCM_SHIFT, true, false),
	SOC_SINGLE("ADC Invert Switch", CS42L42_ADC_CTL,
				CS42L42_ADC_INV_SHIFT, true, false),
	SOC_SINGLE("ADC Boost Switch", CS42L42_ADC_CTL,
				CS42L42_ADC_DIG_BOOST_SHIFT, true, false),
	SOC_SINGLE_SX_TLV("ADC Volume", CS42L42_ADC_VOLUME,
				CS42L42_ADC_VOL_SHIFT, 0xA0, 0x6C, adc_tlv),
	SOC_SINGLE("ADC WNF Switch", CS42L42_ADC_WNF_HPF_CTL,
				CS42L42_ADC_WNF_EN_SHIFT, true, false),
	SOC_SINGLE("ADC HPF Switch", CS42L42_ADC_WNF_HPF_CTL,
				CS42L42_ADC_HPF_EN_SHIFT, true, false),
	SOC_ENUM("HPF Corner Freq", cs42l42_hpf_freq_क्रमागत),
	SOC_ENUM("WNF 3dB Freq", cs42l42_wnf3_freq_क्रमागत),
	SOC_ENUM("WNF 05dB Freq", cs42l42_wnf05_freq_क्रमागत),

	/* DAC Volume and Filter Controls */
	SOC_SINGLE("DACA Invert Switch", CS42L42_DAC_CTL1,
				CS42L42_DACA_INV_SHIFT, true, false),
	SOC_SINGLE("DACB Invert Switch", CS42L42_DAC_CTL1,
				CS42L42_DACB_INV_SHIFT, true, false),
	SOC_SINGLE("DAC HPF Switch", CS42L42_DAC_CTL2,
				CS42L42_DAC_HPF_EN_SHIFT, true, false),
	SOC_DOUBLE_R_TLV("Mixer Volume", CS42L42_MIXER_CHA_VOL,
			 CS42L42_MIXER_CHB_VOL, CS42L42_MIXER_CH_VOL_SHIFT,
				0x3f, 1, mixer_tlv)
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cs42l42_dapm_widमाला_लो[] = अणु
	/* Playback Path */
	SND_SOC_DAPM_OUTPUT("HP"),
	SND_SOC_DAPM_DAC("DAC", शून्य, CS42L42_PWR_CTL1, CS42L42_HP_PDN_SHIFT, 1),
	SND_SOC_DAPM_MIXER("MIXER", CS42L42_PWR_CTL1, CS42L42_MIXER_PDN_SHIFT, 1, शून्य, 0),
	SND_SOC_DAPM_AIF_IN("SDIN1", शून्य, 0, CS42L42_ASP_RX_DAI0_EN, CS42L42_ASP_RX0_CH1_SHIFT, 0),
	SND_SOC_DAPM_AIF_IN("SDIN2", शून्य, 1, CS42L42_ASP_RX_DAI0_EN, CS42L42_ASP_RX0_CH2_SHIFT, 0),

	/* Playback Requirements */
	SND_SOC_DAPM_SUPPLY("ASP DAI0", CS42L42_PWR_CTL1, CS42L42_ASP_DAI_PDN_SHIFT, 1, शून्य, 0),

	/* Capture Path */
	SND_SOC_DAPM_INPUT("HS"),
	SND_SOC_DAPM_ADC("ADC", शून्य, CS42L42_PWR_CTL1, CS42L42_ADC_PDN_SHIFT, 1),
	SND_SOC_DAPM_AIF_OUT("SDOUT1", शून्य, 0, CS42L42_ASP_TX_CH_EN, CS42L42_ASP_TX0_CH1_SHIFT, 0),
	SND_SOC_DAPM_AIF_OUT("SDOUT2", शून्य, 1, CS42L42_ASP_TX_CH_EN, CS42L42_ASP_TX0_CH2_SHIFT, 0),

	/* Capture Requirements */
	SND_SOC_DAPM_SUPPLY("ASP DAO0", CS42L42_PWR_CTL1, CS42L42_ASP_DAO_PDN_SHIFT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ASP TX EN", CS42L42_ASP_TX_SZ_EN, CS42L42_ASP_TX_EN_SHIFT, 0, शून्य, 0),

	/* Playback/Capture Requirements */
	SND_SOC_DAPM_SUPPLY("SCLK", CS42L42_ASP_CLK_CFG, CS42L42_ASP_SCLK_EN_SHIFT, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs42l42_audio_map[] = अणु
	/* Playback Path */
	अणु"HP", शून्य, "DAC"पूर्ण,
	अणु"DAC", शून्य, "MIXER"पूर्ण,
	अणु"MIXER", शून्य, "SDIN1"पूर्ण,
	अणु"MIXER", शून्य, "SDIN2"पूर्ण,
	अणु"SDIN1", शून्य, "Playback"पूर्ण,
	अणु"SDIN2", शून्य, "Playback"पूर्ण,

	/* Playback Requirements */
	अणु"SDIN1", शून्य, "ASP DAI0"पूर्ण,
	अणु"SDIN2", शून्य, "ASP DAI0"पूर्ण,
	अणु"SDIN1", शून्य, "SCLK"पूर्ण,
	अणु"SDIN2", शून्य, "SCLK"पूर्ण,

	/* Capture Path */
	अणु"ADC", शून्य, "HS"पूर्ण,
	अणु "SDOUT1", शून्य, "ADC" पूर्ण,
	अणु "SDOUT2", शून्य, "ADC" पूर्ण,
	अणु "Capture", शून्य, "SDOUT1" पूर्ण,
	अणु "Capture", शून्य, "SDOUT2" पूर्ण,

	/* Capture Requirements */
	अणु "SDOUT1", शून्य, "ASP DAO0" पूर्ण,
	अणु "SDOUT2", शून्य, "ASP DAO0" पूर्ण,
	अणु "SDOUT1", शून्य, "SCLK" पूर्ण,
	अणु "SDOUT2", शून्य, "SCLK" पूर्ण,
	अणु "SDOUT1", शून्य, "ASP TX EN" पूर्ण,
	अणु "SDOUT2", शून्य, "ASP TX EN" पूर्ण,
पूर्ण;

अटल पूर्णांक cs42l42_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs42l42_निजी *cs42l42 =
		(काष्ठा cs42l42_निजी *)snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_card *crd = component->card;
	पूर्णांक ret = 0;

	cs42l42->component = component;

	ret = snd_soc_card_jack_new(crd, "CS42L42 Headset", SND_JACK_HEADSET | SND_JACK_BTN_0 |
				    SND_JACK_BTN_1 | SND_JACK_BTN_2 | SND_JACK_BTN_3,
				    &cs42l42->jack, शून्य, 0);
	अगर (ret < 0)
		dev_err(component->dev, "Cannot create CS42L42 Headset: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_cs42l42 = अणु
	.probe			= cs42l42_component_probe,
	.dapm_widमाला_लो		= cs42l42_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs42l42_dapm_widमाला_लो),
	.dapm_routes		= cs42l42_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(cs42l42_audio_map),
	.controls		= cs42l42_snd_controls,
	.num_controls		= ARRAY_SIZE(cs42l42_snd_controls),
	.idle_bias_on		= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

/* Switch to SCLK. Atomic delay after the ग_लिखो to allow the चयन to complete. */
अटल स्थिर काष्ठा reg_sequence cs42l42_to_sclk_seq[] = अणु
	अणु
		.reg = CS42L42_OSC_SWITCH,
		.def = CS42L42_SCLK_PRESENT_MASK,
		.delay_us = CS42L42_CLOCK_SWITCH_DELAY_US,
	पूर्ण,
पूर्ण;

/* Switch to OSC. Atomic delay after the ग_लिखो to allow the चयन to complete. */
अटल स्थिर काष्ठा reg_sequence cs42l42_to_osc_seq[] = अणु
	अणु
		.reg = CS42L42_OSC_SWITCH,
		.def = 0,
		.delay_us = CS42L42_CLOCK_SWITCH_DELAY_US,
	पूर्ण,
पूर्ण;

काष्ठा cs42l42_pll_params अणु
	u32 sclk;
	u8 mclk_भाग;
	u8 mclk_src_sel;
	u8 sclk_preभाग;
	u8 pll_भाग_पूर्णांक;
	u32 pll_भाग_frac;
	u8 pll_mode;
	u8 pll_भागout;
	u32 mclk_पूर्णांक;
	u8 pll_cal_ratio;
पूर्ण;

/*
 * Common PLL Settings क्रम given SCLK
 * Table 4-5 from the Datasheet
 */
अटल स्थिर काष्ठा cs42l42_pll_params pll_ratio_table[] = अणु
	अणु 1536000, 0, 1, 0x00, 0x7D, 0x000000, 0x03, 0x10, 12000000, 125 पूर्ण,
	अणु 2822400, 0, 1, 0x00, 0x40, 0x000000, 0x03, 0x10, 11289600, 128 पूर्ण,
	अणु 3000000, 0, 1, 0x00, 0x40, 0x000000, 0x03, 0x10, 12000000, 128 पूर्ण,
	अणु 3072000, 0, 1, 0x00, 0x3E, 0x800000, 0x03, 0x10, 12000000, 125 पूर्ण,
	अणु 4000000, 0, 1, 0x00, 0x30, 0x800000, 0x03, 0x10, 12000000, 96 पूर्ण,
	अणु 4096000, 0, 1, 0x00, 0x2E, 0xE00000, 0x03, 0x10, 12000000, 94 पूर्ण,
	अणु 5644800, 0, 1, 0x01, 0x40, 0x000000, 0x03, 0x10, 11289600, 128 पूर्ण,
	अणु 6000000, 0, 1, 0x01, 0x40, 0x000000, 0x03, 0x10, 12000000, 128 पूर्ण,
	अणु 6144000, 0, 1, 0x01, 0x3E, 0x800000, 0x03, 0x10, 12000000, 125 पूर्ण,
	अणु 11289600, 0, 0, 0, 0, 0, 0, 0, 11289600, 0 पूर्ण,
	अणु 12000000, 0, 0, 0, 0, 0, 0, 0, 12000000, 0 पूर्ण,
	अणु 12288000, 0, 0, 0, 0, 0, 0, 0, 12288000, 0 पूर्ण,
	अणु 22579200, 1, 0, 0, 0, 0, 0, 0, 22579200, 0 पूर्ण,
	अणु 24000000, 1, 0, 0, 0, 0, 0, 0, 24000000, 0 पूर्ण,
	अणु 24576000, 1, 0, 0, 0, 0, 0, 0, 24576000, 0 पूर्ण
पूर्ण;

अटल पूर्णांक cs42l42_pll_config(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs42l42_निजी *cs42l42 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;
	u32 clk;
	u32 fsync;

	अगर (!cs42l42->sclk)
		clk = cs42l42->bclk;
	अन्यथा
		clk = cs42l42->sclk;

	क्रम (i = 0; i < ARRAY_SIZE(pll_ratio_table); i++) अणु
		अगर (pll_ratio_table[i].sclk == clk) अणु
			/* Configure the पूर्णांकernal sample rate */
			snd_soc_component_update_bits(component, CS42L42_MCLK_CTL,
					CS42L42_INTERNAL_FS_MASK,
					((pll_ratio_table[i].mclk_पूर्णांक !=
					12000000) &&
					(pll_ratio_table[i].mclk_पूर्णांक !=
					24000000)) <<
					CS42L42_INTERNAL_FS_SHIFT);
			/* Set the MCLK src (PLL or SCLK) and the भागide
			 * ratio
			 */
			snd_soc_component_update_bits(component, CS42L42_MCLK_SRC_SEL,
					CS42L42_MCLK_SRC_SEL_MASK |
					CS42L42_MCLKDIV_MASK,
					(pll_ratio_table[i].mclk_src_sel
					<< CS42L42_MCLK_SRC_SEL_SHIFT) |
					(pll_ratio_table[i].mclk_भाग <<
					CS42L42_MCLKDIV_SHIFT));
			/* Set up the LRCLK */
			fsync = clk / cs42l42->srate;
			अगर (((fsync * cs42l42->srate) != clk)
				|| ((fsync % 2) != 0)) अणु
				dev_err(component->dev,
					"Unsupported sclk %d/sample rate %d\n",
					clk,
					cs42l42->srate);
				वापस -EINVAL;
			पूर्ण
			/* Set the LRCLK period */
			snd_soc_component_update_bits(component,
					CS42L42_FSYNC_P_LOWER,
					CS42L42_FSYNC_PERIOD_MASK,
					CS42L42_FRAC0_VAL(fsync - 1) <<
					CS42L42_FSYNC_PERIOD_SHIFT);
			snd_soc_component_update_bits(component,
					CS42L42_FSYNC_P_UPPER,
					CS42L42_FSYNC_PERIOD_MASK,
					CS42L42_FRAC1_VAL(fsync - 1) <<
					CS42L42_FSYNC_PERIOD_SHIFT);
			/* Set the LRCLK to 50% duty cycle */
			fsync = fsync / 2;
			snd_soc_component_update_bits(component,
					CS42L42_FSYNC_PW_LOWER,
					CS42L42_FSYNC_PULSE_WIDTH_MASK,
					CS42L42_FRAC0_VAL(fsync - 1) <<
					CS42L42_FSYNC_PULSE_WIDTH_SHIFT);
			snd_soc_component_update_bits(component,
					CS42L42_FSYNC_PW_UPPER,
					CS42L42_FSYNC_PULSE_WIDTH_MASK,
					CS42L42_FRAC1_VAL(fsync - 1) <<
					CS42L42_FSYNC_PULSE_WIDTH_SHIFT);
			snd_soc_component_update_bits(component,
					CS42L42_ASP_FRM_CFG,
					CS42L42_ASP_5050_MASK,
					CS42L42_ASP_5050_MASK);
			/* Set the frame delay to 1.0 SCLK घड़ीs */
			snd_soc_component_update_bits(component, CS42L42_ASP_FRM_CFG,
					CS42L42_ASP_FSD_MASK,
					CS42L42_ASP_FSD_1_0 <<
					CS42L42_ASP_FSD_SHIFT);
			/* Set the sample rates (96k or lower) */
			snd_soc_component_update_bits(component, CS42L42_FS_RATE_EN,
					CS42L42_FS_EN_MASK,
					(CS42L42_FS_EN_IASRC_96K |
					CS42L42_FS_EN_OASRC_96K) <<
					CS42L42_FS_EN_SHIFT);
			/* Set the input/output पूर्णांकernal MCLK घड़ी ~12 MHz */
			snd_soc_component_update_bits(component, CS42L42_IN_ASRC_CLK,
					CS42L42_CLK_IASRC_SEL_MASK,
					CS42L42_CLK_IASRC_SEL_12 <<
					CS42L42_CLK_IASRC_SEL_SHIFT);
			snd_soc_component_update_bits(component,
					CS42L42_OUT_ASRC_CLK,
					CS42L42_CLK_OASRC_SEL_MASK,
					CS42L42_CLK_OASRC_SEL_12 <<
					CS42L42_CLK_OASRC_SEL_SHIFT);
			अगर (pll_ratio_table[i].mclk_src_sel == 0) अणु
				/* Pass the घड़ी straight through */
				snd_soc_component_update_bits(component,
					CS42L42_PLL_CTL1,
					CS42L42_PLL_START_MASK,	0);
			पूर्ण अन्यथा अणु
				/* Configure PLL per table 4-5 */
				snd_soc_component_update_bits(component,
					CS42L42_PLL_DIV_CFG1,
					CS42L42_SCLK_PREDIV_MASK,
					pll_ratio_table[i].sclk_preभाग
					<< CS42L42_SCLK_PREDIV_SHIFT);
				snd_soc_component_update_bits(component,
					CS42L42_PLL_DIV_INT,
					CS42L42_PLL_DIV_INT_MASK,
					pll_ratio_table[i].pll_भाग_पूर्णांक
					<< CS42L42_PLL_DIV_INT_SHIFT);
				snd_soc_component_update_bits(component,
					CS42L42_PLL_DIV_FRAC0,
					CS42L42_PLL_DIV_FRAC_MASK,
					CS42L42_FRAC0_VAL(
					pll_ratio_table[i].pll_भाग_frac)
					<< CS42L42_PLL_DIV_FRAC_SHIFT);
				snd_soc_component_update_bits(component,
					CS42L42_PLL_DIV_FRAC1,
					CS42L42_PLL_DIV_FRAC_MASK,
					CS42L42_FRAC1_VAL(
					pll_ratio_table[i].pll_भाग_frac)
					<< CS42L42_PLL_DIV_FRAC_SHIFT);
				snd_soc_component_update_bits(component,
					CS42L42_PLL_DIV_FRAC2,
					CS42L42_PLL_DIV_FRAC_MASK,
					CS42L42_FRAC2_VAL(
					pll_ratio_table[i].pll_भाग_frac)
					<< CS42L42_PLL_DIV_FRAC_SHIFT);
				snd_soc_component_update_bits(component,
					CS42L42_PLL_CTL4,
					CS42L42_PLL_MODE_MASK,
					pll_ratio_table[i].pll_mode
					<< CS42L42_PLL_MODE_SHIFT);
				snd_soc_component_update_bits(component,
					CS42L42_PLL_CTL3,
					CS42L42_PLL_DIVOUT_MASK,
					pll_ratio_table[i].pll_भागout
					<< CS42L42_PLL_DIVOUT_SHIFT);
				snd_soc_component_update_bits(component,
					CS42L42_PLL_CAL_RATIO,
					CS42L42_PLL_CAL_RATIO_MASK,
					pll_ratio_table[i].pll_cal_ratio
					<< CS42L42_PLL_CAL_RATIO_SHIFT);
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cs42l42_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u32 asp_cfg_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFM:
		asp_cfg_val |= CS42L42_ASP_MASTER_MODE <<
				CS42L42_ASP_MODE_SHIFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		asp_cfg_val |= CS42L42_ASP_SLAVE_MODE <<
				CS42L42_ASP_MODE_SHIFT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_LEFT_J:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Bitघड़ी/frame inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		asp_cfg_val |= CS42L42_ASP_SCPOL_NOR << CS42L42_ASP_SCPOL_SHIFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		asp_cfg_val |= CS42L42_ASP_SCPOL_NOR << CS42L42_ASP_SCPOL_SHIFT;
		asp_cfg_val |= CS42L42_ASP_LCPOL_INV << CS42L42_ASP_LCPOL_SHIFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		asp_cfg_val |= CS42L42_ASP_LCPOL_INV << CS42L42_ASP_LCPOL_SHIFT;
		अवरोध;
	पूर्ण

	snd_soc_component_update_bits(component, CS42L42_ASP_CLK_CFG, CS42L42_ASP_MODE_MASK |
								      CS42L42_ASP_SCPOL_MASK |
								      CS42L42_ASP_LCPOL_MASK,
								      asp_cfg_val);

	वापस 0;
पूर्ण

अटल पूर्णांक cs42l42_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs42l42_निजी *cs42l42 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक channels = params_channels(params);
	अचिन्हित पूर्णांक width = (params_width(params) / 8) - 1;
	अचिन्हित पूर्णांक val = 0;

	cs42l42->srate = params_rate(params);
	cs42l42->bclk = snd_soc_params_to_bclk(params);

	चयन(substream->stream) अणु
	हाल SNDRV_PCM_STREAM_CAPTURE:
		अगर (channels == 2) अणु
			val |= CS42L42_ASP_TX_CH2_AP_MASK;
			val |= width << CS42L42_ASP_TX_CH2_RES_SHIFT;
		पूर्ण
		val |= width << CS42L42_ASP_TX_CH1_RES_SHIFT;

		snd_soc_component_update_bits(component, CS42L42_ASP_TX_CH_AP_RES,
				CS42L42_ASP_TX_CH1_AP_MASK | CS42L42_ASP_TX_CH2_AP_MASK |
				CS42L42_ASP_TX_CH2_RES_MASK | CS42L42_ASP_TX_CH1_RES_MASK, val);
		अवरोध;
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		val |= width << CS42L42_ASP_RX_CH_RES_SHIFT;
		/* channel 1 on low LRCLK */
		snd_soc_component_update_bits(component, CS42L42_ASP_RX_DAI0_CH1_AP_RES,
							 CS42L42_ASP_RX_CH_AP_MASK |
							 CS42L42_ASP_RX_CH_RES_MASK, val);
		/* Channel 2 on high LRCLK */
		val |= CS42L42_ASP_RX_CH_AP_HI << CS42L42_ASP_RX_CH_AP_SHIFT;
		snd_soc_component_update_bits(component, CS42L42_ASP_RX_DAI0_CH2_AP_RES,
							 CS42L42_ASP_RX_CH_AP_MASK |
							 CS42L42_ASP_RX_CH_RES_MASK, val);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस cs42l42_pll_config(component);
पूर्ण

अटल पूर्णांक cs42l42_set_sysclk(काष्ठा snd_soc_dai *dai,
				पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs42l42_निजी *cs42l42 = snd_soc_component_get_drvdata(component);

	cs42l42->sclk = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक cs42l42_mute_stream(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs42l42_निजी *cs42l42 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक regval;
	u8 fullScaleVol;
	पूर्णांक ret;

	अगर (mute) अणु
		/* Mute the headphone */
		अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
			snd_soc_component_update_bits(component, CS42L42_HP_CTL,
						      CS42L42_HP_ANA_AMUTE_MASK |
						      CS42L42_HP_ANA_BMUTE_MASK,
						      CS42L42_HP_ANA_AMUTE_MASK |
						      CS42L42_HP_ANA_BMUTE_MASK);

		cs42l42->stream_use &= ~(1 << stream);
		अगर(!cs42l42->stream_use) अणु
			/*
			 * Switch to the पूर्णांकernal oscillator.
			 * SCLK must reमुख्य running until after this घड़ी चयन.
			 * Without a source of घड़ी the I2C bus करोesn't work.
			 */
			regmap_multi_reg_ग_लिखो(cs42l42->regmap, cs42l42_to_osc_seq,
					       ARRAY_SIZE(cs42l42_to_osc_seq));
			snd_soc_component_update_bits(component, CS42L42_PLL_CTL1,
						      CS42L42_PLL_START_MASK, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!cs42l42->stream_use) अणु
			/* SCLK must be running beक्रमe codec unmute */
			अगर ((cs42l42->bclk < 11289600) && (cs42l42->sclk < 11289600)) अणु
				snd_soc_component_update_bits(component, CS42L42_PLL_CTL1,
							      CS42L42_PLL_START_MASK, 1);
				ret = regmap_पढ़ो_poll_समयout(cs42l42->regmap,
							       CS42L42_PLL_LOCK_STATUS,
							       regval,
							       (regval & 1),
							       CS42L42_PLL_LOCK_POLL_US,
							       CS42L42_PLL_LOCK_TIMEOUT_US);
				अगर (ret < 0)
					dev_warn(component->dev, "PLL failed to lock: %d\n", ret);
			पूर्ण

			/* Mark SCLK as present, turn off पूर्णांकernal oscillator */
			regmap_multi_reg_ग_लिखो(cs42l42->regmap, cs42l42_to_sclk_seq,
					       ARRAY_SIZE(cs42l42_to_sclk_seq));
		पूर्ण
		cs42l42->stream_use |= 1 << stream;

		अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			/* Read the headphone load */
			regval = snd_soc_component_पढ़ो(component, CS42L42_LOAD_DET_RCSTAT);
			अगर (((regval & CS42L42_RLA_STAT_MASK) >> CS42L42_RLA_STAT_SHIFT) ==
			    CS42L42_RLA_STAT_15_OHM) अणु
				fullScaleVol = CS42L42_HP_FULL_SCALE_VOL_MASK;
			पूर्ण अन्यथा अणु
				fullScaleVol = 0;
			पूर्ण

			/* Un-mute the headphone, set the full scale volume flag */
			snd_soc_component_update_bits(component, CS42L42_HP_CTL,
						      CS42L42_HP_ANA_AMUTE_MASK |
						      CS42L42_HP_ANA_BMUTE_MASK |
						      CS42L42_HP_FULL_SCALE_VOL_MASK, fullScaleVol);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा CS42L42_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			 SNDRV_PCM_FMTBIT_S24_LE |\
			 SNDRV_PCM_FMTBIT_S32_LE )


अटल स्थिर काष्ठा snd_soc_dai_ops cs42l42_ops = अणु
	.hw_params	= cs42l42_pcm_hw_params,
	.set_fmt	= cs42l42_set_dai_fmt,
	.set_sysclk	= cs42l42_set_sysclk,
	.mute_stream	= cs42l42_mute_stream,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs42l42_dai = अणु
		.name = "cs42l42",
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = CS42L42_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = CS42L42_FORMATS,
		पूर्ण,
		.symmetric_rate = 1,
		.symmetric_sample_bits = 1,
		.ops = &cs42l42_ops,
पूर्ण;

अटल व्योम cs42l42_process_hs_type_detect(काष्ठा cs42l42_निजी *cs42l42)
अणु
	अचिन्हित पूर्णांक hs_det_status;
	अचिन्हित पूर्णांक पूर्णांक_status;

	/* Mask the स्वतः detect पूर्णांकerrupt */
	regmap_update_bits(cs42l42->regmap,
		CS42L42_CODEC_INT_MASK,
		CS42L42_PDN_DONE_MASK |
		CS42L42_HSDET_AUTO_DONE_MASK,
		(1 << CS42L42_PDN_DONE_SHIFT) |
		(1 << CS42L42_HSDET_AUTO_DONE_SHIFT));

	/* Set hs detect to स्वतःmatic, disabled mode */
	regmap_update_bits(cs42l42->regmap,
		CS42L42_HSDET_CTL2,
		CS42L42_HSDET_CTRL_MASK |
		CS42L42_HSDET_SET_MASK |
		CS42L42_HSBIAS_REF_MASK |
		CS42L42_HSDET_AUTO_TIME_MASK,
		(2 << CS42L42_HSDET_CTRL_SHIFT) |
		(2 << CS42L42_HSDET_SET_SHIFT) |
		(0 << CS42L42_HSBIAS_REF_SHIFT) |
		(3 << CS42L42_HSDET_AUTO_TIME_SHIFT));

	/* Read and save the hs detection result */
	regmap_पढ़ो(cs42l42->regmap, CS42L42_HS_DET_STATUS, &hs_det_status);

	cs42l42->hs_type = (hs_det_status & CS42L42_HSDET_TYPE_MASK) >>
				CS42L42_HSDET_TYPE_SHIFT;

	/* Set up button detection */
	अगर ((cs42l42->hs_type == CS42L42_PLUG_CTIA) ||
	      (cs42l42->hs_type == CS42L42_PLUG_OMTP)) अणु
		/* Set स्वतः HS bias settings to शेष */
		regmap_update_bits(cs42l42->regmap,
			CS42L42_HSBIAS_SC_AUTOCTL,
			CS42L42_HSBIAS_SENSE_EN_MASK |
			CS42L42_AUTO_HSBIAS_HIZ_MASK |
			CS42L42_TIP_SENSE_EN_MASK |
			CS42L42_HSBIAS_SENSE_TRIP_MASK,
			(0 << CS42L42_HSBIAS_SENSE_EN_SHIFT) |
			(0 << CS42L42_AUTO_HSBIAS_HIZ_SHIFT) |
			(0 << CS42L42_TIP_SENSE_EN_SHIFT) |
			(3 << CS42L42_HSBIAS_SENSE_TRIP_SHIFT));

		/* Set up hs detect level sensitivity */
		regmap_update_bits(cs42l42->regmap,
			CS42L42_MIC_DET_CTL1,
			CS42L42_LATCH_TO_VP_MASK |
			CS42L42_EVENT_STAT_SEL_MASK |
			CS42L42_HS_DET_LEVEL_MASK,
			(1 << CS42L42_LATCH_TO_VP_SHIFT) |
			(0 << CS42L42_EVENT_STAT_SEL_SHIFT) |
			(cs42l42->bias_thresholds[0] <<
			CS42L42_HS_DET_LEVEL_SHIFT));

		/* Set स्वतः HS bias settings to शेष */
		regmap_update_bits(cs42l42->regmap,
			CS42L42_HSBIAS_SC_AUTOCTL,
			CS42L42_HSBIAS_SENSE_EN_MASK |
			CS42L42_AUTO_HSBIAS_HIZ_MASK |
			CS42L42_TIP_SENSE_EN_MASK |
			CS42L42_HSBIAS_SENSE_TRIP_MASK,
			(1 << CS42L42_HSBIAS_SENSE_EN_SHIFT) |
			(1 << CS42L42_AUTO_HSBIAS_HIZ_SHIFT) |
			(0 << CS42L42_TIP_SENSE_EN_SHIFT) |
			(3 << CS42L42_HSBIAS_SENSE_TRIP_SHIFT));

		/* Turn on level detect circuitry */
		regmap_update_bits(cs42l42->regmap,
			CS42L42_MISC_DET_CTL,
			CS42L42_DETECT_MODE_MASK |
			CS42L42_HSBIAS_CTL_MASK |
			CS42L42_PDN_MIC_LVL_DET_MASK,
			(0 << CS42L42_DETECT_MODE_SHIFT) |
			(3 << CS42L42_HSBIAS_CTL_SHIFT) |
			(0 << CS42L42_PDN_MIC_LVL_DET_SHIFT));

		msleep(cs42l42->btn_det_init_dbnce);

		/* Clear any button पूर्णांकerrupts beक्रमe unmasking them */
		regmap_पढ़ो(cs42l42->regmap, CS42L42_DET_INT_STATUS2,
			    &पूर्णांक_status);

		/* Unmask button detect पूर्णांकerrupts */
		regmap_update_bits(cs42l42->regmap,
			CS42L42_DET_INT2_MASK,
			CS42L42_M_DETECT_TF_MASK |
			CS42L42_M_DETECT_FT_MASK |
			CS42L42_M_HSBIAS_HIZ_MASK |
			CS42L42_M_SHORT_RLS_MASK |
			CS42L42_M_SHORT_DET_MASK,
			(0 << CS42L42_M_DETECT_TF_SHIFT) |
			(0 << CS42L42_M_DETECT_FT_SHIFT) |
			(0 << CS42L42_M_HSBIAS_HIZ_SHIFT) |
			(1 << CS42L42_M_SHORT_RLS_SHIFT) |
			(1 << CS42L42_M_SHORT_DET_SHIFT));
	पूर्ण अन्यथा अणु
		/* Make sure button detect and HS bias circuits are off */
		regmap_update_bits(cs42l42->regmap,
			CS42L42_MISC_DET_CTL,
			CS42L42_DETECT_MODE_MASK |
			CS42L42_HSBIAS_CTL_MASK |
			CS42L42_PDN_MIC_LVL_DET_MASK,
			(0 << CS42L42_DETECT_MODE_SHIFT) |
			(1 << CS42L42_HSBIAS_CTL_SHIFT) |
			(1 << CS42L42_PDN_MIC_LVL_DET_SHIFT));
	पूर्ण

	regmap_update_bits(cs42l42->regmap,
				CS42L42_DAC_CTL2,
				CS42L42_HPOUT_PULLDOWN_MASK |
				CS42L42_HPOUT_LOAD_MASK |
				CS42L42_HPOUT_CLAMP_MASK |
				CS42L42_DAC_HPF_EN_MASK |
				CS42L42_DAC_MON_EN_MASK,
				(0 << CS42L42_HPOUT_PULLDOWN_SHIFT) |
				(0 << CS42L42_HPOUT_LOAD_SHIFT) |
				(0 << CS42L42_HPOUT_CLAMP_SHIFT) |
				(1 << CS42L42_DAC_HPF_EN_SHIFT) |
				(0 << CS42L42_DAC_MON_EN_SHIFT));

	/* Unmask tip sense पूर्णांकerrupts */
	regmap_update_bits(cs42l42->regmap,
		CS42L42_TSRS_PLUG_INT_MASK,
		CS42L42_RS_PLUG_MASK |
		CS42L42_RS_UNPLUG_MASK |
		CS42L42_TS_PLUG_MASK |
		CS42L42_TS_UNPLUG_MASK,
		(1 << CS42L42_RS_PLUG_SHIFT) |
		(1 << CS42L42_RS_UNPLUG_SHIFT) |
		(0 << CS42L42_TS_PLUG_SHIFT) |
		(0 << CS42L42_TS_UNPLUG_SHIFT));
पूर्ण

अटल व्योम cs42l42_init_hs_type_detect(काष्ठा cs42l42_निजी *cs42l42)
अणु
	/* Mask tip sense पूर्णांकerrupts */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_TSRS_PLUG_INT_MASK,
				CS42L42_RS_PLUG_MASK |
				CS42L42_RS_UNPLUG_MASK |
				CS42L42_TS_PLUG_MASK |
				CS42L42_TS_UNPLUG_MASK,
				(1 << CS42L42_RS_PLUG_SHIFT) |
				(1 << CS42L42_RS_UNPLUG_SHIFT) |
				(1 << CS42L42_TS_PLUG_SHIFT) |
				(1 << CS42L42_TS_UNPLUG_SHIFT));

	/* Make sure button detect and HS bias circuits are off */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_MISC_DET_CTL,
				CS42L42_DETECT_MODE_MASK |
				CS42L42_HSBIAS_CTL_MASK |
				CS42L42_PDN_MIC_LVL_DET_MASK,
				(0 << CS42L42_DETECT_MODE_SHIFT) |
				(1 << CS42L42_HSBIAS_CTL_SHIFT) |
				(1 << CS42L42_PDN_MIC_LVL_DET_SHIFT));

	/* Set स्वतः HS bias settings to शेष */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_HSBIAS_SC_AUTOCTL,
				CS42L42_HSBIAS_SENSE_EN_MASK |
				CS42L42_AUTO_HSBIAS_HIZ_MASK |
				CS42L42_TIP_SENSE_EN_MASK |
				CS42L42_HSBIAS_SENSE_TRIP_MASK,
				(0 << CS42L42_HSBIAS_SENSE_EN_SHIFT) |
				(0 << CS42L42_AUTO_HSBIAS_HIZ_SHIFT) |
				(0 << CS42L42_TIP_SENSE_EN_SHIFT) |
				(3 << CS42L42_HSBIAS_SENSE_TRIP_SHIFT));

	/* Set hs detect to manual, disabled mode */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_HSDET_CTL2,
				CS42L42_HSDET_CTRL_MASK |
				CS42L42_HSDET_SET_MASK |
				CS42L42_HSBIAS_REF_MASK |
				CS42L42_HSDET_AUTO_TIME_MASK,
				(0 << CS42L42_HSDET_CTRL_SHIFT) |
				(2 << CS42L42_HSDET_SET_SHIFT) |
				(0 << CS42L42_HSBIAS_REF_SHIFT) |
				(3 << CS42L42_HSDET_AUTO_TIME_SHIFT));

	regmap_update_bits(cs42l42->regmap,
				CS42L42_DAC_CTL2,
				CS42L42_HPOUT_PULLDOWN_MASK |
				CS42L42_HPOUT_LOAD_MASK |
				CS42L42_HPOUT_CLAMP_MASK |
				CS42L42_DAC_HPF_EN_MASK |
				CS42L42_DAC_MON_EN_MASK,
				(8 << CS42L42_HPOUT_PULLDOWN_SHIFT) |
				(0 << CS42L42_HPOUT_LOAD_SHIFT) |
				(1 << CS42L42_HPOUT_CLAMP_SHIFT) |
				(1 << CS42L42_DAC_HPF_EN_SHIFT) |
				(1 << CS42L42_DAC_MON_EN_SHIFT));

	/* Power up HS bias to 2.7V */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_MISC_DET_CTL,
				CS42L42_DETECT_MODE_MASK |
				CS42L42_HSBIAS_CTL_MASK |
				CS42L42_PDN_MIC_LVL_DET_MASK,
				(0 << CS42L42_DETECT_MODE_SHIFT) |
				(3 << CS42L42_HSBIAS_CTL_SHIFT) |
				(1 << CS42L42_PDN_MIC_LVL_DET_SHIFT));

	/* Wait क्रम HS bias to ramp up */
	msleep(cs42l42->hs_bias_ramp_समय);

	/* Unmask स्वतः detect पूर्णांकerrupt */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_CODEC_INT_MASK,
				CS42L42_PDN_DONE_MASK |
				CS42L42_HSDET_AUTO_DONE_MASK,
				(1 << CS42L42_PDN_DONE_SHIFT) |
				(0 << CS42L42_HSDET_AUTO_DONE_SHIFT));

	/* Set hs detect to स्वतःmatic, enabled mode */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_HSDET_CTL2,
				CS42L42_HSDET_CTRL_MASK |
				CS42L42_HSDET_SET_MASK |
				CS42L42_HSBIAS_REF_MASK |
				CS42L42_HSDET_AUTO_TIME_MASK,
				(3 << CS42L42_HSDET_CTRL_SHIFT) |
				(2 << CS42L42_HSDET_SET_SHIFT) |
				(0 << CS42L42_HSBIAS_REF_SHIFT) |
				(3 << CS42L42_HSDET_AUTO_TIME_SHIFT));
पूर्ण

अटल व्योम cs42l42_cancel_hs_type_detect(काष्ठा cs42l42_निजी *cs42l42)
अणु
	/* Mask button detect पूर्णांकerrupts */
	regmap_update_bits(cs42l42->regmap,
		CS42L42_DET_INT2_MASK,
		CS42L42_M_DETECT_TF_MASK |
		CS42L42_M_DETECT_FT_MASK |
		CS42L42_M_HSBIAS_HIZ_MASK |
		CS42L42_M_SHORT_RLS_MASK |
		CS42L42_M_SHORT_DET_MASK,
		(1 << CS42L42_M_DETECT_TF_SHIFT) |
		(1 << CS42L42_M_DETECT_FT_SHIFT) |
		(1 << CS42L42_M_HSBIAS_HIZ_SHIFT) |
		(1 << CS42L42_M_SHORT_RLS_SHIFT) |
		(1 << CS42L42_M_SHORT_DET_SHIFT));

	/* Ground HS bias */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_MISC_DET_CTL,
				CS42L42_DETECT_MODE_MASK |
				CS42L42_HSBIAS_CTL_MASK |
				CS42L42_PDN_MIC_LVL_DET_MASK,
				(0 << CS42L42_DETECT_MODE_SHIFT) |
				(1 << CS42L42_HSBIAS_CTL_SHIFT) |
				(1 << CS42L42_PDN_MIC_LVL_DET_SHIFT));

	/* Set स्वतः HS bias settings to शेष */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_HSBIAS_SC_AUTOCTL,
				CS42L42_HSBIAS_SENSE_EN_MASK |
				CS42L42_AUTO_HSBIAS_HIZ_MASK |
				CS42L42_TIP_SENSE_EN_MASK |
				CS42L42_HSBIAS_SENSE_TRIP_MASK,
				(0 << CS42L42_HSBIAS_SENSE_EN_SHIFT) |
				(0 << CS42L42_AUTO_HSBIAS_HIZ_SHIFT) |
				(0 << CS42L42_TIP_SENSE_EN_SHIFT) |
				(3 << CS42L42_HSBIAS_SENSE_TRIP_SHIFT));

	/* Set hs detect to manual, disabled mode */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_HSDET_CTL2,
				CS42L42_HSDET_CTRL_MASK |
				CS42L42_HSDET_SET_MASK |
				CS42L42_HSBIAS_REF_MASK |
				CS42L42_HSDET_AUTO_TIME_MASK,
				(0 << CS42L42_HSDET_CTRL_SHIFT) |
				(2 << CS42L42_HSDET_SET_SHIFT) |
				(0 << CS42L42_HSBIAS_REF_SHIFT) |
				(3 << CS42L42_HSDET_AUTO_TIME_SHIFT));
पूर्ण

अटल पूर्णांक cs42l42_handle_button_press(काष्ठा cs42l42_निजी *cs42l42)
अणु
	पूर्णांक bias_level;
	अचिन्हित पूर्णांक detect_status;

	/* Mask button detect पूर्णांकerrupts */
	regmap_update_bits(cs42l42->regmap,
		CS42L42_DET_INT2_MASK,
		CS42L42_M_DETECT_TF_MASK |
		CS42L42_M_DETECT_FT_MASK |
		CS42L42_M_HSBIAS_HIZ_MASK |
		CS42L42_M_SHORT_RLS_MASK |
		CS42L42_M_SHORT_DET_MASK,
		(1 << CS42L42_M_DETECT_TF_SHIFT) |
		(1 << CS42L42_M_DETECT_FT_SHIFT) |
		(1 << CS42L42_M_HSBIAS_HIZ_SHIFT) |
		(1 << CS42L42_M_SHORT_RLS_SHIFT) |
		(1 << CS42L42_M_SHORT_DET_SHIFT));

	usleep_range(cs42l42->btn_det_event_dbnce * 1000,
		     cs42l42->btn_det_event_dbnce * 2000);

	/* Test all 4 level detect biases */
	bias_level = 1;
	करो अणु
		/* Adjust button detect level sensitivity */
		regmap_update_bits(cs42l42->regmap,
			CS42L42_MIC_DET_CTL1,
			CS42L42_LATCH_TO_VP_MASK |
			CS42L42_EVENT_STAT_SEL_MASK |
			CS42L42_HS_DET_LEVEL_MASK,
			(1 << CS42L42_LATCH_TO_VP_SHIFT) |
			(0 << CS42L42_EVENT_STAT_SEL_SHIFT) |
			(cs42l42->bias_thresholds[bias_level] <<
			CS42L42_HS_DET_LEVEL_SHIFT));

		regmap_पढ़ो(cs42l42->regmap, CS42L42_DET_STATUS2,
				&detect_status);
	पूर्ण जबतक ((detect_status & CS42L42_HS_TRUE_MASK) &&
		(++bias_level < CS42L42_NUM_BIASES));

	चयन (bias_level) अणु
	हाल 1: /* Function C button press */
		bias_level = SND_JACK_BTN_2;
		dev_dbg(cs42l42->component->dev, "Function C button press\n");
		अवरोध;
	हाल 2: /* Function B button press */
		bias_level = SND_JACK_BTN_1;
		dev_dbg(cs42l42->component->dev, "Function B button press\n");
		अवरोध;
	हाल 3: /* Function D button press */
		bias_level = SND_JACK_BTN_3;
		dev_dbg(cs42l42->component->dev, "Function D button press\n");
		अवरोध;
	हाल 4: /* Function A button press */
		bias_level = SND_JACK_BTN_0;
		dev_dbg(cs42l42->component->dev, "Function A button press\n");
		अवरोध;
	शेष:
		bias_level = 0;
		अवरोध;
	पूर्ण

	/* Set button detect level sensitivity back to शेष */
	regmap_update_bits(cs42l42->regmap,
		CS42L42_MIC_DET_CTL1,
		CS42L42_LATCH_TO_VP_MASK |
		CS42L42_EVENT_STAT_SEL_MASK |
		CS42L42_HS_DET_LEVEL_MASK,
		(1 << CS42L42_LATCH_TO_VP_SHIFT) |
		(0 << CS42L42_EVENT_STAT_SEL_SHIFT) |
		(cs42l42->bias_thresholds[0] << CS42L42_HS_DET_LEVEL_SHIFT));

	/* Clear any button पूर्णांकerrupts beक्रमe unmasking them */
	regmap_पढ़ो(cs42l42->regmap, CS42L42_DET_INT_STATUS2,
		    &detect_status);

	/* Unmask button detect पूर्णांकerrupts */
	regmap_update_bits(cs42l42->regmap,
		CS42L42_DET_INT2_MASK,
		CS42L42_M_DETECT_TF_MASK |
		CS42L42_M_DETECT_FT_MASK |
		CS42L42_M_HSBIAS_HIZ_MASK |
		CS42L42_M_SHORT_RLS_MASK |
		CS42L42_M_SHORT_DET_MASK,
		(0 << CS42L42_M_DETECT_TF_SHIFT) |
		(0 << CS42L42_M_DETECT_FT_SHIFT) |
		(0 << CS42L42_M_HSBIAS_HIZ_SHIFT) |
		(1 << CS42L42_M_SHORT_RLS_SHIFT) |
		(1 << CS42L42_M_SHORT_DET_SHIFT));

	वापस bias_level;
पूर्ण

काष्ठा cs42l42_irq_params अणु
	u16 status_addr;
	u16 mask_addr;
	u8 mask;
पूर्ण;

अटल स्थिर काष्ठा cs42l42_irq_params irq_params_table[] = अणु
	अणुCS42L42_ADC_OVFL_STATUS, CS42L42_ADC_OVFL_INT_MASK,
		CS42L42_ADC_OVFL_VAL_MASKपूर्ण,
	अणुCS42L42_MIXER_STATUS, CS42L42_MIXER_INT_MASK,
		CS42L42_MIXER_VAL_MASKपूर्ण,
	अणुCS42L42_SRC_STATUS, CS42L42_SRC_INT_MASK,
		CS42L42_SRC_VAL_MASKपूर्ण,
	अणुCS42L42_ASP_RX_STATUS, CS42L42_ASP_RX_INT_MASK,
		CS42L42_ASP_RX_VAL_MASKपूर्ण,
	अणुCS42L42_ASP_TX_STATUS, CS42L42_ASP_TX_INT_MASK,
		CS42L42_ASP_TX_VAL_MASKपूर्ण,
	अणुCS42L42_CODEC_STATUS, CS42L42_CODEC_INT_MASK,
		CS42L42_CODEC_VAL_MASKपूर्ण,
	अणुCS42L42_DET_INT_STATUS1, CS42L42_DET_INT1_MASK,
		CS42L42_DET_INT_VAL1_MASKपूर्ण,
	अणुCS42L42_DET_INT_STATUS2, CS42L42_DET_INT2_MASK,
		CS42L42_DET_INT_VAL2_MASKपूर्ण,
	अणुCS42L42_SRCPL_INT_STATUS, CS42L42_SRCPL_INT_MASK,
		CS42L42_SRCPL_VAL_MASKपूर्ण,
	अणुCS42L42_VPMON_STATUS, CS42L42_VPMON_INT_MASK,
		CS42L42_VPMON_VAL_MASKपूर्ण,
	अणुCS42L42_PLL_LOCK_STATUS, CS42L42_PLL_LOCK_INT_MASK,
		CS42L42_PLL_LOCK_VAL_MASKपूर्ण,
	अणुCS42L42_TSRS_PLUG_STATUS, CS42L42_TSRS_PLUG_INT_MASK,
		CS42L42_TSRS_PLUG_VAL_MASKपूर्ण
पूर्ण;

अटल irqवापस_t cs42l42_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cs42l42_निजी *cs42l42 = (काष्ठा cs42l42_निजी *)data;
	काष्ठा snd_soc_component *component = cs42l42->component;
	अचिन्हित पूर्णांक stickies[12];
	अचिन्हित पूर्णांक masks[12];
	अचिन्हित पूर्णांक current_plug_status;
	अचिन्हित पूर्णांक current_button_status;
	अचिन्हित पूर्णांक i;
	पूर्णांक report = 0;


	/* Read sticky रेजिस्टरs to clear पूर्णांकerurpt */
	क्रम (i = 0; i < ARRAY_SIZE(stickies); i++) अणु
		regmap_पढ़ो(cs42l42->regmap, irq_params_table[i].status_addr,
				&(stickies[i]));
		regmap_पढ़ो(cs42l42->regmap, irq_params_table[i].mask_addr,
				&(masks[i]));
		stickies[i] = stickies[i] & (~masks[i]) &
				irq_params_table[i].mask;
	पूर्ण

	/* Read tip sense status beक्रमe handling type detect */
	current_plug_status = (stickies[11] &
		(CS42L42_TS_PLUG_MASK | CS42L42_TS_UNPLUG_MASK)) >>
		CS42L42_TS_PLUG_SHIFT;

	/* Read button sense status */
	current_button_status = stickies[7] &
		(CS42L42_M_DETECT_TF_MASK |
		CS42L42_M_DETECT_FT_MASK |
		CS42L42_M_HSBIAS_HIZ_MASK);

	/* Check स्वतः-detect status */
	अगर ((~masks[5]) & irq_params_table[5].mask) अणु
		अगर (stickies[5] & CS42L42_HSDET_AUTO_DONE_MASK) अणु
			cs42l42_process_hs_type_detect(cs42l42);
			चयन(cs42l42->hs_type)अणु
			हाल CS42L42_PLUG_CTIA:
			हाल CS42L42_PLUG_OMTP:
				snd_soc_jack_report(&cs42l42->jack, SND_JACK_HEADSET,
						    SND_JACK_HEADSET);
				अवरोध;
			हाल CS42L42_PLUG_HEADPHONE:
				snd_soc_jack_report(&cs42l42->jack, SND_JACK_HEADPHONE,
						    SND_JACK_HEADPHONE);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			dev_dbg(component->dev, "Auto detect done (%d)\n", cs42l42->hs_type);
		पूर्ण
	पूर्ण

	/* Check tip sense status */
	अगर ((~masks[11]) & irq_params_table[11].mask) अणु
		चयन (current_plug_status) अणु
		हाल CS42L42_TS_PLUG:
			अगर (cs42l42->plug_state != CS42L42_TS_PLUG) अणु
				cs42l42->plug_state = CS42L42_TS_PLUG;
				cs42l42_init_hs_type_detect(cs42l42);
			पूर्ण
			अवरोध;

		हाल CS42L42_TS_UNPLUG:
			अगर (cs42l42->plug_state != CS42L42_TS_UNPLUG) अणु
				cs42l42->plug_state = CS42L42_TS_UNPLUG;
				cs42l42_cancel_hs_type_detect(cs42l42);

				चयन(cs42l42->hs_type)अणु
				हाल CS42L42_PLUG_CTIA:
				हाल CS42L42_PLUG_OMTP:
					snd_soc_jack_report(&cs42l42->jack, 0, SND_JACK_HEADSET);
					अवरोध;
				हाल CS42L42_PLUG_HEADPHONE:
					snd_soc_jack_report(&cs42l42->jack, 0, SND_JACK_HEADPHONE);
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
				dev_dbg(component->dev, "Unplug event\n");
			पूर्ण
			अवरोध;

		शेष:
			अगर (cs42l42->plug_state != CS42L42_TS_TRANS)
				cs42l42->plug_state = CS42L42_TS_TRANS;
		पूर्ण
	पूर्ण

	/* Check button detect status */
	अगर ((~masks[7]) & irq_params_table[7].mask) अणु
		अगर (!(current_button_status &
			CS42L42_M_HSBIAS_HIZ_MASK)) अणु

			अगर (current_button_status & CS42L42_M_DETECT_TF_MASK) अणु
				dev_dbg(component->dev, "Button released\n");
				report = 0;
			पूर्ण अन्यथा अगर (current_button_status & CS42L42_M_DETECT_FT_MASK) अणु
				report = cs42l42_handle_button_press(cs42l42);

			पूर्ण
			snd_soc_jack_report(&cs42l42->jack, report, SND_JACK_BTN_0 | SND_JACK_BTN_1 |
								   SND_JACK_BTN_2 | SND_JACK_BTN_3);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम cs42l42_set_पूर्णांकerrupt_masks(काष्ठा cs42l42_निजी *cs42l42)
अणु
	regmap_update_bits(cs42l42->regmap, CS42L42_ADC_OVFL_INT_MASK,
			CS42L42_ADC_OVFL_MASK,
			(1 << CS42L42_ADC_OVFL_SHIFT));

	regmap_update_bits(cs42l42->regmap, CS42L42_MIXER_INT_MASK,
			CS42L42_MIX_CHB_OVFL_MASK |
			CS42L42_MIX_CHA_OVFL_MASK |
			CS42L42_EQ_OVFL_MASK |
			CS42L42_EQ_BIQUAD_OVFL_MASK,
			(1 << CS42L42_MIX_CHB_OVFL_SHIFT) |
			(1 << CS42L42_MIX_CHA_OVFL_SHIFT) |
			(1 << CS42L42_EQ_OVFL_SHIFT) |
			(1 << CS42L42_EQ_BIQUAD_OVFL_SHIFT));

	regmap_update_bits(cs42l42->regmap, CS42L42_SRC_INT_MASK,
			CS42L42_SRC_ILK_MASK |
			CS42L42_SRC_OLK_MASK |
			CS42L42_SRC_IUNLK_MASK |
			CS42L42_SRC_OUNLK_MASK,
			(1 << CS42L42_SRC_ILK_SHIFT) |
			(1 << CS42L42_SRC_OLK_SHIFT) |
			(1 << CS42L42_SRC_IUNLK_SHIFT) |
			(1 << CS42L42_SRC_OUNLK_SHIFT));

	regmap_update_bits(cs42l42->regmap, CS42L42_ASP_RX_INT_MASK,
			CS42L42_ASPRX_NOLRCK_MASK |
			CS42L42_ASPRX_EARLY_MASK |
			CS42L42_ASPRX_LATE_MASK |
			CS42L42_ASPRX_ERROR_MASK |
			CS42L42_ASPRX_OVLD_MASK,
			(1 << CS42L42_ASPRX_NOLRCK_SHIFT) |
			(1 << CS42L42_ASPRX_EARLY_SHIFT) |
			(1 << CS42L42_ASPRX_LATE_SHIFT) |
			(1 << CS42L42_ASPRX_ERROR_SHIFT) |
			(1 << CS42L42_ASPRX_OVLD_SHIFT));

	regmap_update_bits(cs42l42->regmap, CS42L42_ASP_TX_INT_MASK,
			CS42L42_ASPTX_NOLRCK_MASK |
			CS42L42_ASPTX_EARLY_MASK |
			CS42L42_ASPTX_LATE_MASK |
			CS42L42_ASPTX_SMERROR_MASK,
			(1 << CS42L42_ASPTX_NOLRCK_SHIFT) |
			(1 << CS42L42_ASPTX_EARLY_SHIFT) |
			(1 << CS42L42_ASPTX_LATE_SHIFT) |
			(1 << CS42L42_ASPTX_SMERROR_SHIFT));

	regmap_update_bits(cs42l42->regmap, CS42L42_CODEC_INT_MASK,
			CS42L42_PDN_DONE_MASK |
			CS42L42_HSDET_AUTO_DONE_MASK,
			(1 << CS42L42_PDN_DONE_SHIFT) |
			(1 << CS42L42_HSDET_AUTO_DONE_SHIFT));

	regmap_update_bits(cs42l42->regmap, CS42L42_SRCPL_INT_MASK,
			CS42L42_SRCPL_ADC_LK_MASK |
			CS42L42_SRCPL_DAC_LK_MASK |
			CS42L42_SRCPL_ADC_UNLK_MASK |
			CS42L42_SRCPL_DAC_UNLK_MASK,
			(1 << CS42L42_SRCPL_ADC_LK_SHIFT) |
			(1 << CS42L42_SRCPL_DAC_LK_SHIFT) |
			(1 << CS42L42_SRCPL_ADC_UNLK_SHIFT) |
			(1 << CS42L42_SRCPL_DAC_UNLK_SHIFT));

	regmap_update_bits(cs42l42->regmap, CS42L42_DET_INT1_MASK,
			CS42L42_TIP_SENSE_UNPLUG_MASK |
			CS42L42_TIP_SENSE_PLUG_MASK |
			CS42L42_HSBIAS_SENSE_MASK,
			(1 << CS42L42_TIP_SENSE_UNPLUG_SHIFT) |
			(1 << CS42L42_TIP_SENSE_PLUG_SHIFT) |
			(1 << CS42L42_HSBIAS_SENSE_SHIFT));

	regmap_update_bits(cs42l42->regmap, CS42L42_DET_INT2_MASK,
			CS42L42_M_DETECT_TF_MASK |
			CS42L42_M_DETECT_FT_MASK |
			CS42L42_M_HSBIAS_HIZ_MASK |
			CS42L42_M_SHORT_RLS_MASK |
			CS42L42_M_SHORT_DET_MASK,
			(1 << CS42L42_M_DETECT_TF_SHIFT) |
			(1 << CS42L42_M_DETECT_FT_SHIFT) |
			(1 << CS42L42_M_HSBIAS_HIZ_SHIFT) |
			(1 << CS42L42_M_SHORT_RLS_SHIFT) |
			(1 << CS42L42_M_SHORT_DET_SHIFT));

	regmap_update_bits(cs42l42->regmap, CS42L42_VPMON_INT_MASK,
			CS42L42_VPMON_MASK,
			(1 << CS42L42_VPMON_SHIFT));

	regmap_update_bits(cs42l42->regmap, CS42L42_PLL_LOCK_INT_MASK,
			CS42L42_PLL_LOCK_MASK,
			(1 << CS42L42_PLL_LOCK_SHIFT));

	regmap_update_bits(cs42l42->regmap, CS42L42_TSRS_PLUG_INT_MASK,
			CS42L42_RS_PLUG_MASK |
			CS42L42_RS_UNPLUG_MASK |
			CS42L42_TS_PLUG_MASK |
			CS42L42_TS_UNPLUG_MASK,
			(1 << CS42L42_RS_PLUG_SHIFT) |
			(1 << CS42L42_RS_UNPLUG_SHIFT) |
			(0 << CS42L42_TS_PLUG_SHIFT) |
			(0 << CS42L42_TS_UNPLUG_SHIFT));
पूर्ण

अटल व्योम cs42l42_setup_hs_type_detect(काष्ठा cs42l42_निजी *cs42l42)
अणु
	अचिन्हित पूर्णांक reg;

	cs42l42->hs_type = CS42L42_PLUG_INVALID;

	/* Latch analog controls to VP घातer करोमुख्य */
	regmap_update_bits(cs42l42->regmap, CS42L42_MIC_DET_CTL1,
			CS42L42_LATCH_TO_VP_MASK |
			CS42L42_EVENT_STAT_SEL_MASK |
			CS42L42_HS_DET_LEVEL_MASK,
			(1 << CS42L42_LATCH_TO_VP_SHIFT) |
			(0 << CS42L42_EVENT_STAT_SEL_SHIFT) |
			(cs42l42->bias_thresholds[0] <<
			CS42L42_HS_DET_LEVEL_SHIFT));

	/* Remove ground noise-suppression clamps */
	regmap_update_bits(cs42l42->regmap,
			CS42L42_HS_CLAMP_DISABLE,
			CS42L42_HS_CLAMP_DISABLE_MASK,
			(1 << CS42L42_HS_CLAMP_DISABLE_SHIFT));

	/* Enable the tip sense circuit */
	regmap_update_bits(cs42l42->regmap, CS42L42_TIPSENSE_CTL,
			CS42L42_TIP_SENSE_CTRL_MASK |
			CS42L42_TIP_SENSE_INV_MASK |
			CS42L42_TIP_SENSE_DEBOUNCE_MASK,
			(3 << CS42L42_TIP_SENSE_CTRL_SHIFT) |
			(0 << CS42L42_TIP_SENSE_INV_SHIFT) |
			(2 << CS42L42_TIP_SENSE_DEBOUNCE_SHIFT));

	/* Save the initial status of the tip sense */
	regmap_पढ़ो(cs42l42->regmap,
			  CS42L42_TSRS_PLUG_STATUS,
			  &reg);
	cs42l42->plug_state = (((अक्षर) reg) &
		      (CS42L42_TS_PLUG_MASK | CS42L42_TS_UNPLUG_MASK)) >>
		      CS42L42_TS_PLUG_SHIFT;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक threshold_शेषs[] = अणु
	CS42L42_HS_DET_LEVEL_15,
	CS42L42_HS_DET_LEVEL_8,
	CS42L42_HS_DET_LEVEL_4,
	CS42L42_HS_DET_LEVEL_1
पूर्ण;

अटल पूर्णांक cs42l42_handle_device_data(काष्ठा i2c_client *i2c_client,
					काष्ठा cs42l42_निजी *cs42l42)
अणु
	काष्ठा device_node *np = i2c_client->dev.of_node;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक thresholds[CS42L42_NUM_BIASES];
	पूर्णांक ret;
	पूर्णांक i;

	ret = of_property_पढ़ो_u32(np, "cirrus,ts-inv", &val);

	अगर (!ret) अणु
		चयन (val) अणु
		हाल CS42L42_TS_INV_EN:
		हाल CS42L42_TS_INV_DIS:
			cs42l42->ts_inv = val;
			अवरोध;
		शेष:
			dev_err(&i2c_client->dev,
				"Wrong cirrus,ts-inv DT value %d\n",
				val);
			cs42l42->ts_inv = CS42L42_TS_INV_DIS;
		पूर्ण
	पूर्ण अन्यथा अणु
		cs42l42->ts_inv = CS42L42_TS_INV_DIS;
	पूर्ण

	regmap_update_bits(cs42l42->regmap, CS42L42_TSENSE_CTL,
			CS42L42_TS_INV_MASK,
			(cs42l42->ts_inv << CS42L42_TS_INV_SHIFT));

	ret = of_property_पढ़ो_u32(np, "cirrus,ts-dbnc-rise", &val);

	अगर (!ret) अणु
		चयन (val) अणु
		हाल CS42L42_TS_DBNCE_0:
		हाल CS42L42_TS_DBNCE_125:
		हाल CS42L42_TS_DBNCE_250:
		हाल CS42L42_TS_DBNCE_500:
		हाल CS42L42_TS_DBNCE_750:
		हाल CS42L42_TS_DBNCE_1000:
		हाल CS42L42_TS_DBNCE_1250:
		हाल CS42L42_TS_DBNCE_1500:
			cs42l42->ts_dbnc_rise = val;
			अवरोध;
		शेष:
			dev_err(&i2c_client->dev,
				"Wrong cirrus,ts-dbnc-rise DT value %d\n",
				val);
			cs42l42->ts_dbnc_rise = CS42L42_TS_DBNCE_1000;
		पूर्ण
	पूर्ण अन्यथा अणु
		cs42l42->ts_dbnc_rise = CS42L42_TS_DBNCE_1000;
	पूर्ण

	regmap_update_bits(cs42l42->regmap, CS42L42_TSENSE_CTL,
			CS42L42_TS_RISE_DBNCE_TIME_MASK,
			(cs42l42->ts_dbnc_rise <<
			CS42L42_TS_RISE_DBNCE_TIME_SHIFT));

	ret = of_property_पढ़ो_u32(np, "cirrus,ts-dbnc-fall", &val);

	अगर (!ret) अणु
		चयन (val) अणु
		हाल CS42L42_TS_DBNCE_0:
		हाल CS42L42_TS_DBNCE_125:
		हाल CS42L42_TS_DBNCE_250:
		हाल CS42L42_TS_DBNCE_500:
		हाल CS42L42_TS_DBNCE_750:
		हाल CS42L42_TS_DBNCE_1000:
		हाल CS42L42_TS_DBNCE_1250:
		हाल CS42L42_TS_DBNCE_1500:
			cs42l42->ts_dbnc_fall = val;
			अवरोध;
		शेष:
			dev_err(&i2c_client->dev,
				"Wrong cirrus,ts-dbnc-fall DT value %d\n",
				val);
			cs42l42->ts_dbnc_fall = CS42L42_TS_DBNCE_0;
		पूर्ण
	पूर्ण अन्यथा अणु
		cs42l42->ts_dbnc_fall = CS42L42_TS_DBNCE_0;
	पूर्ण

	regmap_update_bits(cs42l42->regmap, CS42L42_TSENSE_CTL,
			CS42L42_TS_FALL_DBNCE_TIME_MASK,
			(cs42l42->ts_dbnc_fall <<
			CS42L42_TS_FALL_DBNCE_TIME_SHIFT));

	ret = of_property_पढ़ो_u32(np, "cirrus,btn-det-init-dbnce", &val);

	अगर (!ret) अणु
		अगर (val <= CS42L42_BTN_DET_INIT_DBNCE_MAX)
			cs42l42->btn_det_init_dbnce = val;
		अन्यथा अणु
			dev_err(&i2c_client->dev,
				"Wrong cirrus,btn-det-init-dbnce DT value %d\n",
				val);
			cs42l42->btn_det_init_dbnce =
				CS42L42_BTN_DET_INIT_DBNCE_DEFAULT;
		पूर्ण
	पूर्ण अन्यथा अणु
		cs42l42->btn_det_init_dbnce =
			CS42L42_BTN_DET_INIT_DBNCE_DEFAULT;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "cirrus,btn-det-event-dbnce", &val);

	अगर (!ret) अणु
		अगर (val <= CS42L42_BTN_DET_EVENT_DBNCE_MAX)
			cs42l42->btn_det_event_dbnce = val;
		अन्यथा अणु
			dev_err(&i2c_client->dev,
			"Wrong cirrus,btn-det-event-dbnce DT value %d\n", val);
			cs42l42->btn_det_event_dbnce =
				CS42L42_BTN_DET_EVENT_DBNCE_DEFAULT;
		पूर्ण
	पूर्ण अन्यथा अणु
		cs42l42->btn_det_event_dbnce =
			CS42L42_BTN_DET_EVENT_DBNCE_DEFAULT;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(np, "cirrus,bias-lvls",
				   (u32 *)thresholds, CS42L42_NUM_BIASES);

	अगर (!ret) अणु
		क्रम (i = 0; i < CS42L42_NUM_BIASES; i++) अणु
			अगर (thresholds[i] <= CS42L42_HS_DET_LEVEL_MAX)
				cs42l42->bias_thresholds[i] = thresholds[i];
			अन्यथा अणु
				dev_err(&i2c_client->dev,
				"Wrong cirrus,bias-lvls[%d] DT value %d\n", i,
					thresholds[i]);
				cs42l42->bias_thresholds[i] =
					threshold_शेषs[i];
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < CS42L42_NUM_BIASES; i++)
			cs42l42->bias_thresholds[i] = threshold_शेषs[i];
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "cirrus,hs-bias-ramp-rate", &val);

	अगर (!ret) अणु
		चयन (val) अणु
		हाल CS42L42_HSBIAS_RAMP_FAST_RISE_SLOW_FALL:
			cs42l42->hs_bias_ramp_rate = val;
			cs42l42->hs_bias_ramp_समय = CS42L42_HSBIAS_RAMP_TIME0;
			अवरोध;
		हाल CS42L42_HSBIAS_RAMP_FAST:
			cs42l42->hs_bias_ramp_rate = val;
			cs42l42->hs_bias_ramp_समय = CS42L42_HSBIAS_RAMP_TIME1;
			अवरोध;
		हाल CS42L42_HSBIAS_RAMP_SLOW:
			cs42l42->hs_bias_ramp_rate = val;
			cs42l42->hs_bias_ramp_समय = CS42L42_HSBIAS_RAMP_TIME2;
			अवरोध;
		हाल CS42L42_HSBIAS_RAMP_SLOWEST:
			cs42l42->hs_bias_ramp_rate = val;
			cs42l42->hs_bias_ramp_समय = CS42L42_HSBIAS_RAMP_TIME3;
			अवरोध;
		शेष:
			dev_err(&i2c_client->dev,
				"Wrong cirrus,hs-bias-ramp-rate DT value %d\n",
				val);
			cs42l42->hs_bias_ramp_rate = CS42L42_HSBIAS_RAMP_SLOW;
			cs42l42->hs_bias_ramp_समय = CS42L42_HSBIAS_RAMP_TIME2;
		पूर्ण
	पूर्ण अन्यथा अणु
		cs42l42->hs_bias_ramp_rate = CS42L42_HSBIAS_RAMP_SLOW;
		cs42l42->hs_bias_ramp_समय = CS42L42_HSBIAS_RAMP_TIME2;
	पूर्ण

	regmap_update_bits(cs42l42->regmap, CS42L42_HS_BIAS_CTL,
			CS42L42_HSBIAS_RAMP_MASK,
			(cs42l42->hs_bias_ramp_rate <<
			CS42L42_HSBIAS_RAMP_SHIFT));

	वापस 0;
पूर्ण

अटल पूर्णांक cs42l42_i2c_probe(काष्ठा i2c_client *i2c_client,
				       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs42l42_निजी *cs42l42;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक devid = 0;
	अचिन्हित पूर्णांक reg;

	cs42l42 = devm_kzalloc(&i2c_client->dev, माप(काष्ठा cs42l42_निजी),
			       GFP_KERNEL);
	अगर (!cs42l42)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c_client, cs42l42);

	cs42l42->regmap = devm_regmap_init_i2c(i2c_client, &cs42l42_regmap);
	अगर (IS_ERR(cs42l42->regmap)) अणु
		ret = PTR_ERR(cs42l42->regmap);
		dev_err(&i2c_client->dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(cs42l42->supplies); i++)
		cs42l42->supplies[i].supply = cs42l42_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c_client->dev,
				      ARRAY_SIZE(cs42l42->supplies),
				      cs42l42->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c_client->dev,
			"Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(cs42l42->supplies),
				    cs42l42->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c_client->dev,
			"Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Reset the Device */
	cs42l42->reset_gpio = devm_gpiod_get_optional(&i2c_client->dev,
		"reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(cs42l42->reset_gpio)) अणु
		ret = PTR_ERR(cs42l42->reset_gpio);
		जाओ err_disable;
	पूर्ण

	अगर (cs42l42->reset_gpio) अणु
		dev_dbg(&i2c_client->dev, "Found reset GPIO\n");
		gpiod_set_value_cansleep(cs42l42->reset_gpio, 1);
	पूर्ण
	usleep_range(CS42L42_BOOT_TIME_US, CS42L42_BOOT_TIME_US * 2);

	/* Request IRQ */
	ret = devm_request_thपढ़ोed_irq(&i2c_client->dev,
			i2c_client->irq,
			शून्य, cs42l42_irq_thपढ़ो,
			IRQF_ONESHOT | IRQF_TRIGGER_LOW,
			"cs42l42", cs42l42);

	अगर (ret != 0)
		dev_err(&i2c_client->dev,
			"Failed to request IRQ: %d\n", ret);

	/* initialize codec */
	ret = regmap_पढ़ो(cs42l42->regmap, CS42L42_DEVID_AB, &reg);
	devid = (reg & 0xFF) << 12;

	ret = regmap_पढ़ो(cs42l42->regmap, CS42L42_DEVID_CD, &reg);
	devid |= (reg & 0xFF) << 4;

	ret = regmap_पढ़ो(cs42l42->regmap, CS42L42_DEVID_E, &reg);
	devid |= (reg & 0xF0) >> 4;

	अगर (devid != CS42L42_CHIP_ID) अणु
		ret = -ENODEV;
		dev_err(&i2c_client->dev,
			"CS42L42 Device ID (%X). Expected %X\n",
			devid, CS42L42_CHIP_ID);
		जाओ err_disable;
	पूर्ण

	ret = regmap_पढ़ो(cs42l42->regmap, CS42L42_REVID, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c_client->dev, "Get Revision ID failed\n");
		जाओ err_disable;
	पूर्ण

	dev_info(&i2c_client->dev,
		 "Cirrus Logic CS42L42, Revision: %02X\n", reg & 0xFF);

	/* Power up the codec */
	regmap_update_bits(cs42l42->regmap, CS42L42_PWR_CTL1,
			CS42L42_ASP_DAO_PDN_MASK |
			CS42L42_ASP_DAI_PDN_MASK |
			CS42L42_MIXER_PDN_MASK |
			CS42L42_EQ_PDN_MASK |
			CS42L42_HP_PDN_MASK |
			CS42L42_ADC_PDN_MASK |
			CS42L42_PDN_ALL_MASK,
			(1 << CS42L42_ASP_DAO_PDN_SHIFT) |
			(1 << CS42L42_ASP_DAI_PDN_SHIFT) |
			(1 << CS42L42_MIXER_PDN_SHIFT) |
			(1 << CS42L42_EQ_PDN_SHIFT) |
			(1 << CS42L42_HP_PDN_SHIFT) |
			(1 << CS42L42_ADC_PDN_SHIFT) |
			(0 << CS42L42_PDN_ALL_SHIFT));

	अगर (i2c_client->dev.of_node) अणु
		ret = cs42l42_handle_device_data(i2c_client, cs42l42);
		अगर (ret != 0)
			जाओ err_disable;
	पूर्ण

	/* Setup headset detection */
	cs42l42_setup_hs_type_detect(cs42l42);

	/* Mask/Unmask Interrupts */
	cs42l42_set_पूर्णांकerrupt_masks(cs42l42);

	/* Register codec क्रम machine driver */
	ret = devm_snd_soc_रेजिस्टर_component(&i2c_client->dev,
			&soc_component_dev_cs42l42, &cs42l42_dai, 1);
	अगर (ret < 0)
		जाओ err_disable;
	वापस 0;

err_disable:
	regulator_bulk_disable(ARRAY_SIZE(cs42l42->supplies),
				cs42l42->supplies);
	वापस ret;
पूर्ण

अटल पूर्णांक cs42l42_i2c_हटाओ(काष्ठा i2c_client *i2c_client)
अणु
	काष्ठा cs42l42_निजी *cs42l42 = i2c_get_clientdata(i2c_client);

	devm_मुक्त_irq(&i2c_client->dev, i2c_client->irq, cs42l42);
	pm_runसमय_suspend(&i2c_client->dev);
	pm_runसमय_disable(&i2c_client->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक cs42l42_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा cs42l42_निजी *cs42l42 = dev_get_drvdata(dev);

	regcache_cache_only(cs42l42->regmap, true);
	regcache_mark_dirty(cs42l42->regmap);

	/* Hold करोwn reset */
	gpiod_set_value_cansleep(cs42l42->reset_gpio, 0);

	/* हटाओ घातer */
	regulator_bulk_disable(ARRAY_SIZE(cs42l42->supplies),
				cs42l42->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक cs42l42_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा cs42l42_निजी *cs42l42 = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* Enable घातer */
	ret = regulator_bulk_enable(ARRAY_SIZE(cs42l42->supplies),
					cs42l42->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable supplies: %d\n",
			ret);
		वापस ret;
	पूर्ण

	gpiod_set_value_cansleep(cs42l42->reset_gpio, 1);
	usleep_range(CS42L42_BOOT_TIME_US, CS42L42_BOOT_TIME_US * 2);

	regcache_cache_only(cs42l42->regmap, false);
	regcache_sync(cs42l42->regmap);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops cs42l42_runसमय_pm = अणु
	SET_RUNTIME_PM_OPS(cs42l42_runसमय_suspend, cs42l42_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id cs42l42_of_match[] = अणु
	अणु .compatible = "cirrus,cs42l42", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cs42l42_of_match);


अटल स्थिर काष्ठा i2c_device_id cs42l42_id[] = अणु
	अणु"cs42l42", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, cs42l42_id);

अटल काष्ठा i2c_driver cs42l42_i2c_driver = अणु
	.driver = अणु
		.name = "cs42l42",
		.pm = &cs42l42_runसमय_pm,
		.of_match_table = cs42l42_of_match,
		पूर्ण,
	.id_table = cs42l42_id,
	.probe = cs42l42_i2c_probe,
	.हटाओ = cs42l42_i2c_हटाओ,
पूर्ण;

module_i2c_driver(cs42l42_i2c_driver);

MODULE_DESCRIPTION("ASoC CS42L42 driver");
MODULE_AUTHOR("James Schulman, Cirrus Logic Inc, <james.schulman@cirrus.com>");
MODULE_AUTHOR("Brian Austin, Cirrus Logic Inc, <brian.austin@cirrus.com>");
MODULE_AUTHOR("Michael White, Cirrus Logic Inc, <michael.white@cirrus.com>");
MODULE_LICENSE("GPL");
