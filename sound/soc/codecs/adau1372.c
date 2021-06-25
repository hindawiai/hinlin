<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Analog Devices ADAU1372 Audio Codec driver
 *
 * Copyright 2016 Analog Devices Inc.
 * Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gcd.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश <sound/soc.h>

#समावेश "adau1372.h"
#समावेश "adau-utils.h"

काष्ठा adau1372 अणु
	काष्ठा clk *clk;
	काष्ठा regmap *regmap;
	व्योम (*चयन_mode)(काष्ठा device *dev);
	bool use_pll;
	bool enabled;
	bool master;

	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list rate_स्थिरraपूर्णांकs;
	अचिन्हित पूर्णांक slot_width;

	काष्ठा clk *mclk;
	काष्ठा gpio_desc *pd_gpio;
	काष्ठा device *dev;
पूर्ण;

#घोषणा ADAU1372_REG_CLK_CTRL		0x00
#घोषणा ADAU1372_REG_PLL(x)		(0x01 + (x))
#घोषणा ADAU1372_REG_DAC_SOURCE		0x11
#घोषणा ADAU1372_REG_SOUT_SOURCE_0_1	0x13
#घोषणा ADAU1372_REG_SOUT_SOURCE_2_3	0x14
#घोषणा ADAU1372_REG_SOUT_SOURCE_4_5	0x15
#घोषणा ADAU1372_REG_SOUT_SOURCE_6_7	0x16
#घोषणा ADAU1372_REG_ADC_SDATA_CH	0x17
#घोषणा ADAU1372_REG_ASRCO_SOURCE_0_1	0x18
#घोषणा ADAU1372_REG_ASRCO_SOURCE_2_3	0x19
#घोषणा ADAU1372_REG_ASRC_MODE		0x1a
#घोषणा ADAU1372_REG_ADC_CTRL0		0x1b
#घोषणा ADAU1372_REG_ADC_CTRL1		0x1c
#घोषणा ADAU1372_REG_ADC_CTRL2		0x1d
#घोषणा ADAU1372_REG_ADC_CTRL3		0x1e
#घोषणा ADAU1372_REG_ADC_VOL(x)		(0x1f + (x))
#घोषणा ADAU1372_REG_PGA_CTRL(x)	(0x23 + (x))
#घोषणा ADAU1372_REG_PGA_BOOST		0x28
#घोषणा ADAU1372_REG_MICBIAS		0x2d
#घोषणा ADAU1372_REG_DAC_CTRL		0x2e
#घोषणा ADAU1372_REG_DAC_VOL(x)		(0x2f + (x))
#घोषणा ADAU1372_REG_OP_STAGE_MUTE	0x31
#घोषणा ADAU1372_REG_SAI0		0x32
#घोषणा ADAU1372_REG_SAI1		0x33
#घोषणा ADAU1372_REG_SOUT_CTRL		0x34
#घोषणा ADAU1372_REG_MODE_MP(x)		(0x38 + (x))
#घोषणा ADAU1372_REG_OP_STAGE_CTRL	0x43
#घोषणा ADAU1372_REG_DECIM_PWR		0x44
#घोषणा ADAU1372_REG_INTERP_PWR		0x45
#घोषणा ADAU1372_REG_BIAS_CTRL0		0x46
#घोषणा ADAU1372_REG_BIAS_CTRL1		0x47

#घोषणा ADAU1372_CLK_CTRL_PLL_EN	BIT(7)
#घोषणा ADAU1372_CLK_CTRL_XTAL_DIS	BIT(4)
#घोषणा ADAU1372_CLK_CTRL_CLKSRC	BIT(3)
#घोषणा ADAU1372_CLK_CTRL_CC_MDIV	BIT(1)
#घोषणा ADAU1372_CLK_CTRL_MCLK_EN	BIT(0)

#घोषणा ADAU1372_SAI0_DELAY1		(0x0 << 6)
#घोषणा ADAU1372_SAI0_DELAY0		(0x1 << 6)
#घोषणा ADAU1372_SAI0_DELAY_MASK	(0x3 << 6)
#घोषणा ADAU1372_SAI0_SAI_I2S		(0x0 << 4)
#घोषणा ADAU1372_SAI0_SAI_TDM2		(0x1 << 4)
#घोषणा ADAU1372_SAI0_SAI_TDM4		(0x2 << 4)
#घोषणा ADAU1372_SAI0_SAI_TDM8		(0x3 << 4)
#घोषणा ADAU1372_SAI0_SAI_MASK		(0x3 << 4)
#घोषणा ADAU1372_SAI0_FS_48		0x0
#घोषणा ADAU1372_SAI0_FS_8		0x1
#घोषणा ADAU1372_SAI0_FS_12		0x2
#घोषणा ADAU1372_SAI0_FS_16		0x3
#घोषणा ADAU1372_SAI0_FS_24		0x4
#घोषणा ADAU1372_SAI0_FS_32		0x5
#घोषणा ADAU1372_SAI0_FS_96		0x6
#घोषणा ADAU1372_SAI0_FS_192		0x7
#घोषणा ADAU1372_SAI0_FS_MASK		0xf

#घोषणा ADAU1372_SAI1_TDM_TS		BIT(7)
#घोषणा ADAU1372_SAI1_BCLK_TDMC		BIT(6)
#घोषणा ADAU1372_SAI1_LR_MODE		BIT(5)
#घोषणा ADAU1372_SAI1_LR_POL		BIT(4)
#घोषणा ADAU1372_SAI1_BCLKRATE		BIT(2)
#घोषणा ADAU1372_SAI1_BCLKEDGE		BIT(1)
#घोषणा ADAU1372_SAI1_MS		BIT(0)

अटल स्थिर अचिन्हित पूर्णांक adau1372_rates[] = अणु
	[ADAU1372_SAI0_FS_8] = 8000,
	[ADAU1372_SAI0_FS_12] = 12000,
	[ADAU1372_SAI0_FS_16] = 16000,
	[ADAU1372_SAI0_FS_24] = 24000,
	[ADAU1372_SAI0_FS_32] = 32000,
	[ADAU1372_SAI0_FS_48] = 48000,
	[ADAU1372_SAI0_FS_96] = 96000,
	[ADAU1372_SAI0_FS_192] = 192000,
पूर्ण;

/* 8k, 12k, 24k, 48k */
#घोषणा ADAU1372_RATE_MASK_TDM8 0x17
/* + 16k, 96k */
#घोषणा ADAU1372_RATE_MASK_TDM4_MASTER (ADAU1372_RATE_MASK_TDM8 | 0x48 | 0x20)
/* +32k */
#घोषणा ADAU1372_RATE_MASK_TDM4 (ADAU1372_RATE_MASK_TDM4_MASTER | 0x20)
/* + 192k */
#घोषणा ADAU1372_RATE_MASK_TDM2 (ADAU1372_RATE_MASK_TDM4 | 0x80)

अटल स्थिर DECLARE_TLV_DB_MINMAX(adau1372_digital_tlv, -9563, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adau1372_pga_tlv, -1200, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adau1372_pga_boost_tlv, 0, 1000, 0);

अटल स्थिर अक्षर * स्थिर adau1372_bias_text[] = अणु
	"Normal operation", "Extreme power saving", "Enhanced performance",
	"Power saving",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक adau1372_bias_adc_values[] = अणु
	0, 2, 3,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1372_bias_adc_text[] = अणु
	"Normal operation", "Enhanced performance", "Power saving",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1372_bias_dac_text[] = अणु
	"Normal operation", "Power saving", "Superior performance",
	"Enhanced performance",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adau1372_bias_hp_क्रमागत,
	ADAU1372_REG_BIAS_CTRL0, 6, adau1372_bias_text);
अटल SOC_ENUM_SINGLE_DECL(adau1372_bias_afe0_1_क्रमागत,
	ADAU1372_REG_BIAS_CTRL0, 4, adau1372_bias_text);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_bias_adc2_3_क्रमागत,
	ADAU1372_REG_BIAS_CTRL0, 2, 0x3, adau1372_bias_adc_text,
	adau1372_bias_adc_values);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_bias_adc0_1_क्रमागत,
	ADAU1372_REG_BIAS_CTRL0, 0, 0x3, adau1372_bias_adc_text,
	adau1372_bias_adc_values);
अटल SOC_ENUM_SINGLE_DECL(adau1372_bias_afe2_3_क्रमागत,
	ADAU1372_REG_BIAS_CTRL1, 4, adau1372_bias_text);
अटल SOC_ENUM_SINGLE_DECL(adau1372_bias_mic_क्रमागत,
	ADAU1372_REG_BIAS_CTRL1, 2, adau1372_bias_text);
अटल SOC_ENUM_SINGLE_DECL(adau1372_bias_dac_क्रमागत,
	ADAU1372_REG_BIAS_CTRL1, 0, adau1372_bias_dac_text);

अटल स्थिर अक्षर * स्थिर adau1372_hpf_text[] = अणु
	"Off",
	"1 Hz",
	"4 Hz",
	"8 Hz",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adau1372_hpf0_1_क्रमागत, ADAU1372_REG_ADC_CTRL2, 5,
			    adau1372_hpf_text);
अटल SOC_ENUM_SINGLE_DECL(adau1372_hpf2_3_क्रमागत, ADAU1372_REG_ADC_CTRL3, 5,
			    adau1372_hpf_text);
अटल स्थिर काष्ठा snd_kcontrol_new adau1372_controls[] = अणु
	SOC_SINGLE_TLV("ADC 0 Capture Volume", ADAU1372_REG_ADC_VOL(0),
		       0, 0xff, 1, adau1372_digital_tlv),
	SOC_SINGLE_TLV("ADC 1 Capture Volume", ADAU1372_REG_ADC_VOL(1),
		       0, 0xff, 1, adau1372_digital_tlv),
	SOC_SINGLE_TLV("ADC 2 Capture Volume", ADAU1372_REG_ADC_VOL(2),
		       0, 0xff, 1, adau1372_digital_tlv),
	SOC_SINGLE_TLV("ADC 3 Capture Volume", ADAU1372_REG_ADC_VOL(3),
		       0, 0xff, 1, adau1372_digital_tlv),
	SOC_SINGLE("ADC 0 Capture Switch", ADAU1372_REG_ADC_CTRL0, 3, 1, 1),
	SOC_SINGLE("ADC 1 Capture Switch", ADAU1372_REG_ADC_CTRL0, 4, 1, 1),
	SOC_SINGLE("ADC 2 Capture Switch", ADAU1372_REG_ADC_CTRL1, 3, 1, 1),
	SOC_SINGLE("ADC 3 Capture Switch", ADAU1372_REG_ADC_CTRL1, 4, 1, 1),

	SOC_ENUM("ADC 0+1 High-Pass-Filter", adau1372_hpf0_1_क्रमागत),
	SOC_ENUM("ADC 2+3 High-Pass-Filter", adau1372_hpf2_3_क्रमागत),

	SOC_SINGLE_TLV("PGA 0 Capture Volume", ADAU1372_REG_PGA_CTRL(0),
		       0, 0x3f, 0, adau1372_pga_tlv),
	SOC_SINGLE_TLV("PGA 1 Capture Volume", ADAU1372_REG_PGA_CTRL(1),
		       0, 0x3f, 0, adau1372_pga_tlv),
	SOC_SINGLE_TLV("PGA 2 Capture Volume", ADAU1372_REG_PGA_CTRL(2),
		       0, 0x3f, 0, adau1372_pga_tlv),
	SOC_SINGLE_TLV("PGA 3 Capture Volume", ADAU1372_REG_PGA_CTRL(3),
		       0, 0x3f, 0, adau1372_pga_tlv),
	SOC_SINGLE_TLV("PGA 0 Boost Capture Volume", ADAU1372_REG_PGA_BOOST,
		       0, 1, 0, adau1372_pga_boost_tlv),
	SOC_SINGLE_TLV("PGA 1 Boost Capture Volume", ADAU1372_REG_PGA_BOOST,
		       1, 1, 0, adau1372_pga_boost_tlv),
	SOC_SINGLE_TLV("PGA 2 Boost Capture Volume", ADAU1372_REG_PGA_BOOST,
		       2, 1, 0, adau1372_pga_boost_tlv),
	SOC_SINGLE_TLV("PGA 3 Boost Capture Volume", ADAU1372_REG_PGA_BOOST,
		       3, 1, 0, adau1372_pga_boost_tlv),
	SOC_SINGLE("PGA 0 Capture Switch", ADAU1372_REG_PGA_CTRL(0), 7, 1, 1),
	SOC_SINGLE("PGA 1 Capture Switch", ADAU1372_REG_PGA_CTRL(1), 7, 1, 1),
	SOC_SINGLE("PGA 2 Capture Switch", ADAU1372_REG_PGA_CTRL(2), 7, 1, 1),
	SOC_SINGLE("PGA 3 Capture Switch", ADAU1372_REG_PGA_CTRL(3), 7, 1, 1),

	SOC_SINGLE_TLV("DAC 0 Playback Volume", ADAU1372_REG_DAC_VOL(0),
		       0, 0xff, 1, adau1372_digital_tlv),
	SOC_SINGLE_TLV("DAC 1 Playback Volume", ADAU1372_REG_DAC_VOL(1),
		       0, 0xff, 1, adau1372_digital_tlv),
	SOC_SINGLE("DAC 0 Playback Switch", ADAU1372_REG_DAC_CTRL, 3, 1, 1),
	SOC_SINGLE("DAC 1 Playback Switch", ADAU1372_REG_DAC_CTRL, 4, 1, 1),

	SOC_ENUM("Headphone Bias", adau1372_bias_hp_क्रमागत),
	SOC_ENUM("Microphone Bias", adau1372_bias_mic_क्रमागत),
	SOC_ENUM("AFE 0+1 Bias", adau1372_bias_afe0_1_क्रमागत),
	SOC_ENUM("AFE 2+3 Bias", adau1372_bias_afe2_3_क्रमागत),
	SOC_ENUM("ADC 0+1 Bias", adau1372_bias_adc0_1_क्रमागत),
	SOC_ENUM("ADC 2+3 Bias", adau1372_bias_adc2_3_क्रमागत),
	SOC_ENUM("DAC 0+1 Bias", adau1372_bias_dac_क्रमागत),
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1372_decimator_mux_text[] = अणु
	"ADC",
	"DMIC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adau1372_decimator0_1_mux_क्रमागत, ADAU1372_REG_ADC_CTRL2,
			    2, adau1372_decimator_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new adau1372_decimator0_1_mux_control =
	SOC_DAPM_ENUM("Decimator 0+1 Capture Mux", adau1372_decimator0_1_mux_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(adau1372_decimator2_3_mux_क्रमागत, ADAU1372_REG_ADC_CTRL3,
			    2, adau1372_decimator_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new adau1372_decimator2_3_mux_control =
	SOC_DAPM_ENUM("Decimator 2+3 Capture Mux", adau1372_decimator2_3_mux_क्रमागत);

अटल स्थिर अचिन्हित पूर्णांक adau1372_asrco_mux_values[] = अणु
	4, 5, 6, 7,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1372_asrco_mux_text[] = अणु
	"Decimator0",
	"Decimator1",
	"Decimator2",
	"Decimator3",
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_asrco0_mux_क्रमागत, ADAU1372_REG_ASRCO_SOURCE_0_1,
				  0, 0xf, adau1372_asrco_mux_text, adau1372_asrco_mux_values);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_asrco1_mux_क्रमागत, ADAU1372_REG_ASRCO_SOURCE_0_1,
				  4, 0xf, adau1372_asrco_mux_text, adau1372_asrco_mux_values);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_asrco2_mux_क्रमागत, ADAU1372_REG_ASRCO_SOURCE_2_3,
				  0, 0xf, adau1372_asrco_mux_text, adau1372_asrco_mux_values);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_asrco3_mux_क्रमागत, ADAU1372_REG_ASRCO_SOURCE_2_3,
				  4, 0xf, adau1372_asrco_mux_text, adau1372_asrco_mux_values);

अटल स्थिर काष्ठा snd_kcontrol_new adau1372_asrco0_mux_control =
	SOC_DAPM_ENUM("Output ASRC0 Capture Mux", adau1372_asrco0_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new adau1372_asrco1_mux_control =
	SOC_DAPM_ENUM("Output ASRC1 Capture Mux", adau1372_asrco1_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new adau1372_asrco2_mux_control =
	SOC_DAPM_ENUM("Output ASRC2 Capture Mux", adau1372_asrco2_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new adau1372_asrco3_mux_control =
	SOC_DAPM_ENUM("Output ASRC3 Capture Mux", adau1372_asrco3_mux_क्रमागत);

अटल स्थिर अचिन्हित पूर्णांक adau1372_sout_mux_values[] = अणु
	4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1372_sout_mux_text[] = अणु
	"Output ASRC0",
	"Output ASRC1",
	"Output ASRC2",
	"Output ASRC3",
	"Serial Input 0",
	"Serial Input 1",
	"Serial Input 2",
	"Serial Input 3",
	"Serial Input 4",
	"Serial Input 5",
	"Serial Input 6",
	"Serial Input 7",
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_sout0_mux_क्रमागत, ADAU1372_REG_SOUT_SOURCE_0_1,
				  0, 0xf, adau1372_sout_mux_text, adau1372_sout_mux_values);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_sout1_mux_क्रमागत, ADAU1372_REG_SOUT_SOURCE_0_1,
				  4, 0xf, adau1372_sout_mux_text, adau1372_sout_mux_values);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_sout2_mux_क्रमागत, ADAU1372_REG_SOUT_SOURCE_2_3,
				  0, 0xf, adau1372_sout_mux_text, adau1372_sout_mux_values);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_sout3_mux_क्रमागत, ADAU1372_REG_SOUT_SOURCE_2_3,
				  4, 0xf, adau1372_sout_mux_text, adau1372_sout_mux_values);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_sout4_mux_क्रमागत, ADAU1372_REG_SOUT_SOURCE_4_5,
				  0, 0xf, adau1372_sout_mux_text, adau1372_sout_mux_values);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_sout5_mux_क्रमागत, ADAU1372_REG_SOUT_SOURCE_4_5,
				  4, 0xf, adau1372_sout_mux_text, adau1372_sout_mux_values);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_sout6_mux_क्रमागत, ADAU1372_REG_SOUT_SOURCE_6_7,
				  0, 0xf, adau1372_sout_mux_text, adau1372_sout_mux_values);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_sout7_mux_क्रमागत, ADAU1372_REG_SOUT_SOURCE_6_7,
				  4, 0xf, adau1372_sout_mux_text, adau1372_sout_mux_values);

अटल स्थिर काष्ठा snd_kcontrol_new adau1372_sout0_mux_control =
	SOC_DAPM_ENUM("Serial Output 0 Capture Mux", adau1372_sout0_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new adau1372_sout1_mux_control =
	SOC_DAPM_ENUM("Serial Output 1 Capture Mux", adau1372_sout1_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new adau1372_sout2_mux_control =
	SOC_DAPM_ENUM("Serial Output 2 Capture Mux", adau1372_sout2_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new adau1372_sout3_mux_control =
	SOC_DAPM_ENUM("Serial Output 3 Capture Mux", adau1372_sout3_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new adau1372_sout4_mux_control =
	SOC_DAPM_ENUM("Serial Output 4 Capture Mux", adau1372_sout4_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new adau1372_sout5_mux_control =
	SOC_DAPM_ENUM("Serial Output 5 Capture Mux", adau1372_sout5_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new adau1372_sout6_mux_control =
	SOC_DAPM_ENUM("Serial Output 6 Capture Mux", adau1372_sout6_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new adau1372_sout7_mux_control =
	SOC_DAPM_ENUM("Serial Output 7 Capture Mux", adau1372_sout7_mux_क्रमागत);

अटल स्थिर अक्षर * स्थिर adau1372_asrci_mux_text[] = अणु
	"Serial Input 0+1",
	"Serial Input 2+3",
	"Serial Input 4+5",
	"Serial Input 6+7",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adau1372_asrci_mux_क्रमागत,
	ADAU1372_REG_ASRC_MODE, 2, adau1372_asrci_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new adau1372_asrci_mux_control =
	SOC_DAPM_ENUM("Input ASRC Playback Mux", adau1372_asrci_mux_क्रमागत);

अटल स्थिर अचिन्हित पूर्णांक adau1372_dac_mux_values[] = अणु
	12, 13
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1372_dac_mux_text[] = अणु
	"Input ASRC0",
	"Input ASRC1",
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_dac0_mux_क्रमागत, ADAU1372_REG_DAC_SOURCE,
				  0, 0xf, adau1372_dac_mux_text, adau1372_dac_mux_values);
अटल SOC_VALUE_ENUM_SINGLE_DECL(adau1372_dac1_mux_क्रमागत, ADAU1372_REG_DAC_SOURCE,
				  4, 0xf, adau1372_dac_mux_text, adau1372_dac_mux_values);

अटल स्थिर काष्ठा snd_kcontrol_new adau1372_dac0_mux_control =
	SOC_DAPM_ENUM("DAC 0 Playback Mux", adau1372_dac0_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new adau1372_dac1_mux_control =
	SOC_DAPM_ENUM("DAC 1 Playback Mux", adau1372_dac1_mux_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget adau1372_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("AIN0"),
	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),
	SND_SOC_DAPM_INPUT("AIN3"),
	SND_SOC_DAPM_INPUT("DMIC0_1"),
	SND_SOC_DAPM_INPUT("DMIC2_3"),

	SND_SOC_DAPM_SUPPLY("MICBIAS0", ADAU1372_REG_MICBIAS, 4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS1", ADAU1372_REG_MICBIAS, 5, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("PGA0", ADAU1372_REG_PGA_CTRL(0), 6, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PGA1", ADAU1372_REG_PGA_CTRL(1), 6, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PGA2", ADAU1372_REG_PGA_CTRL(2), 6, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PGA3", ADAU1372_REG_PGA_CTRL(3), 6, 0, शून्य, 0),
	SND_SOC_DAPM_ADC("ADC0", शून्य, ADAU1372_REG_ADC_CTRL2, 0, 0),
	SND_SOC_DAPM_ADC("ADC1", शून्य, ADAU1372_REG_ADC_CTRL2, 1, 0),
	SND_SOC_DAPM_ADC("ADC2", शून्य, ADAU1372_REG_ADC_CTRL3, 0, 0),
	SND_SOC_DAPM_ADC("ADC3", शून्य, ADAU1372_REG_ADC_CTRL3, 1, 0),

	SND_SOC_DAPM_SUPPLY("ADC0 Filter", ADAU1372_REG_DECIM_PWR, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC1 Filter", ADAU1372_REG_DECIM_PWR, 1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC2 Filter", ADAU1372_REG_DECIM_PWR, 2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC3 Filter", ADAU1372_REG_DECIM_PWR, 3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Output ASRC0 Decimator", ADAU1372_REG_DECIM_PWR, 4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Output ASRC1 Decimator", ADAU1372_REG_DECIM_PWR, 5, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Output ASRC2 Decimator", ADAU1372_REG_DECIM_PWR, 6, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Output ASRC3 Decimator", ADAU1372_REG_DECIM_PWR, 7, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("Decimator0 Mux", SND_SOC_NOPM, 0, 0, &adau1372_decimator0_1_mux_control),
	SND_SOC_DAPM_MUX("Decimator1 Mux", SND_SOC_NOPM, 0, 0, &adau1372_decimator0_1_mux_control),
	SND_SOC_DAPM_MUX("Decimator2 Mux", SND_SOC_NOPM, 0, 0, &adau1372_decimator2_3_mux_control),
	SND_SOC_DAPM_MUX("Decimator3 Mux", SND_SOC_NOPM, 0, 0, &adau1372_decimator2_3_mux_control),

	SND_SOC_DAPM_MUX("Output ASRC0 Mux", SND_SOC_NOPM, 0, 0, &adau1372_asrco0_mux_control),
	SND_SOC_DAPM_MUX("Output ASRC1 Mux", SND_SOC_NOPM, 0, 0, &adau1372_asrco1_mux_control),
	SND_SOC_DAPM_MUX("Output ASRC2 Mux", SND_SOC_NOPM, 0, 0, &adau1372_asrco2_mux_control),
	SND_SOC_DAPM_MUX("Output ASRC3 Mux", SND_SOC_NOPM, 0, 0, &adau1372_asrco3_mux_control),
	SND_SOC_DAPM_MUX("Serial Output 0 Capture Mux", SND_SOC_NOPM, 0, 0,
			 &adau1372_sout0_mux_control),
	SND_SOC_DAPM_MUX("Serial Output 1 Capture Mux", SND_SOC_NOPM, 0, 0,
			 &adau1372_sout1_mux_control),
	SND_SOC_DAPM_MUX("Serial Output 2 Capture Mux", SND_SOC_NOPM, 0, 0,
			 &adau1372_sout2_mux_control),
	SND_SOC_DAPM_MUX("Serial Output 3 Capture Mux", SND_SOC_NOPM, 0, 0,
			 &adau1372_sout3_mux_control),
	SND_SOC_DAPM_MUX("Serial Output 4 Capture Mux", SND_SOC_NOPM, 0, 0,
			 &adau1372_sout4_mux_control),
	SND_SOC_DAPM_MUX("Serial Output 5 Capture Mux", SND_SOC_NOPM, 0, 0,
			 &adau1372_sout5_mux_control),
	SND_SOC_DAPM_MUX("Serial Output 6 Capture Mux", SND_SOC_NOPM, 0, 0,
			 &adau1372_sout6_mux_control),
	SND_SOC_DAPM_MUX("Serial Output 7 Capture Mux", SND_SOC_NOPM, 0, 0,
			 &adau1372_sout7_mux_control),

	SND_SOC_DAPM_AIF_IN("Serial Input 0", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("Serial Input 1", शून्य, 1, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("Serial Input 2", शून्य, 2, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("Serial Input 3", शून्य, 3, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("Serial Input 4", शून्य, 4, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("Serial Input 5", शून्य, 5, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("Serial Input 6", शून्य, 6, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("Serial Input 7", शून्य, 7, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_OUT("Serial Output 0", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("Serial Output 1", शून्य, 1, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("Serial Output 2", शून्य, 2, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("Serial Output 3", शून्य, 3, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("Serial Output 4", शून्य, 4, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("Serial Output 5", शून्य, 5, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("Serial Output 6", शून्य, 6, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("Serial Output 7", शून्य, 7, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SUPPLY("Output ASRC Supply", ADAU1372_REG_ASRC_MODE, 1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Input ASRC Supply", ADAU1372_REG_ASRC_MODE, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("DAC1 Modulator", ADAU1372_REG_INTERP_PWR, 3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC0 Modulator", ADAU1372_REG_INTERP_PWR, 2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Input ASRC1 Interpolator", ADAU1372_REG_INTERP_PWR, 1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Input ASRC0 Interpolator", ADAU1372_REG_INTERP_PWR, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("Input ASRC0 Mux", SND_SOC_NOPM, 0, 0, &adau1372_asrci_mux_control),
	SND_SOC_DAPM_MUX("Input ASRC1 Mux", SND_SOC_NOPM, 0, 0, &adau1372_asrci_mux_control),

	SND_SOC_DAPM_MUX("DAC 0 Mux", SND_SOC_NOPM, 0, 0, &adau1372_dac0_mux_control),
	SND_SOC_DAPM_MUX("DAC 1 Mux", SND_SOC_NOPM, 0, 0, &adau1372_dac1_mux_control),

	SND_SOC_DAPM_DAC("DAC0", शून्य, ADAU1372_REG_DAC_CTRL, 0, 0),
	SND_SOC_DAPM_DAC("DAC1", शून्य, ADAU1372_REG_DAC_CTRL, 1, 0),

	SND_SOC_DAPM_OUT_DRV("OP_STAGE_LP", ADAU1372_REG_OP_STAGE_CTRL, 0, 1, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("OP_STAGE_LN", ADAU1372_REG_OP_STAGE_CTRL, 1, 1, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("OP_STAGE_RP", ADAU1372_REG_OP_STAGE_CTRL, 2, 1, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("OP_STAGE_RN", ADAU1372_REG_OP_STAGE_CTRL, 3, 1, शून्य, 0),

	SND_SOC_DAPM_OUTPUT("HPOUTL"),
	SND_SOC_DAPM_OUTPUT("HPOUTR"),
पूर्ण;

#घोषणा ADAU1372_SOUT_ROUTES(x) \
	अणु "Serial Output " #x " Capture Mux", "Output ASRC0", "Output ASRC0 Mux" पूर्ण, \
	अणु "Serial Output " #x " Capture Mux", "Output ASRC1", "Output ASRC1 Mux" पूर्ण, \
	अणु "Serial Output " #x " Capture Mux", "Output ASRC2", "Output ASRC2 Mux" पूर्ण, \
	अणु "Serial Output " #x " Capture Mux", "Output ASRC3", "Output ASRC3 Mux" पूर्ण, \
	अणु "Serial Output " #x " Capture Mux", "Serial Input 0", "Serial Input 0" पूर्ण, \
	अणु "Serial Output " #x " Capture Mux", "Serial Input 1", "Serial Input 1" पूर्ण, \
	अणु "Serial Output " #x " Capture Mux", "Serial Input 2", "Serial Input 2" पूर्ण, \
	अणु "Serial Output " #x " Capture Mux", "Serial Input 3", "Serial Input 3" पूर्ण, \
	अणु "Serial Output " #x " Capture Mux", "Serial Input 4", "Serial Input 4" पूर्ण, \
	अणु "Serial Output " #x " Capture Mux", "Serial Input 5", "Serial Input 5" पूर्ण, \
	अणु "Serial Output " #x " Capture Mux", "Serial Input 6", "Serial Input 6" पूर्ण, \
	अणु "Serial Output " #x " Capture Mux", "Serial Input 7", "Serial Input 7" पूर्ण, \
	अणु "Serial Output " #x, शून्य, "Serial Output " #x " Capture Mux" पूर्ण, \
	अणु "Capture", शून्य, "Serial Output " #x पूर्ण

#घोषणा ADAU1372_ASRCO_ROUTES(x) \
	अणु "Output ASRC" #x " Mux", "Decimator0", "Decimator0 Mux" पूर्ण, \
	अणु "Output ASRC" #x " Mux", "Decimator1", "Decimator1 Mux" पूर्ण, \
	अणु "Output ASRC" #x " Mux", "Decimator2", "Decimator2 Mux" पूर्ण, \
	अणु "Output ASRC" #x " Mux", "Decimator3", "Decimator3 Mux" पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route adau1372_dapm_routes[] = अणु
	अणु "PGA0", शून्य, "AIN0" पूर्ण,
	अणु "PGA1", शून्य, "AIN1" पूर्ण,
	अणु "PGA2", शून्य, "AIN2" पूर्ण,
	अणु "PGA3", शून्य, "AIN3" पूर्ण,

	अणु "ADC0", शून्य, "PGA0" पूर्ण,
	अणु "ADC1", शून्य, "PGA1" पूर्ण,
	अणु "ADC2", शून्य, "PGA2" पूर्ण,
	अणु "ADC3", शून्य, "PGA3" पूर्ण,

	अणु "Decimator0 Mux", "ADC", "ADC0" पूर्ण,
	अणु "Decimator1 Mux", "ADC", "ADC1" पूर्ण,
	अणु "Decimator2 Mux", "ADC", "ADC2" पूर्ण,
	अणु "Decimator3 Mux", "ADC", "ADC3" पूर्ण,

	अणु "Decimator0 Mux", "DMIC", "DMIC0_1" पूर्ण,
	अणु "Decimator1 Mux", "DMIC", "DMIC0_1" पूर्ण,
	अणु "Decimator2 Mux", "DMIC", "DMIC2_3" पूर्ण,
	अणु "Decimator3 Mux", "DMIC", "DMIC2_3" पूर्ण,

	अणु "Decimator0 Mux", शून्य, "ADC0 Filter" पूर्ण,
	अणु "Decimator1 Mux", शून्य, "ADC1 Filter" पूर्ण,
	अणु "Decimator2 Mux", शून्य, "ADC2 Filter" पूर्ण,
	अणु "Decimator3 Mux", शून्य, "ADC3 Filter" पूर्ण,

	अणु "Output ASRC0 Mux", शून्य, "Output ASRC Supply" पूर्ण,
	अणु "Output ASRC1 Mux", शून्य, "Output ASRC Supply" पूर्ण,
	अणु "Output ASRC2 Mux", शून्य, "Output ASRC Supply" पूर्ण,
	अणु "Output ASRC3 Mux", शून्य, "Output ASRC Supply" पूर्ण,
	अणु "Output ASRC0 Mux", शून्य, "Output ASRC0 Decimator" पूर्ण,
	अणु "Output ASRC1 Mux", शून्य, "Output ASRC1 Decimator" पूर्ण,
	अणु "Output ASRC2 Mux", शून्य, "Output ASRC2 Decimator" पूर्ण,
	अणु "Output ASRC3 Mux", शून्य, "Output ASRC3 Decimator" पूर्ण,

	ADAU1372_ASRCO_ROUTES(0),
	ADAU1372_ASRCO_ROUTES(1),
	ADAU1372_ASRCO_ROUTES(2),
	ADAU1372_ASRCO_ROUTES(3),

	ADAU1372_SOUT_ROUTES(0),
	ADAU1372_SOUT_ROUTES(1),
	ADAU1372_SOUT_ROUTES(2),
	ADAU1372_SOUT_ROUTES(3),
	ADAU1372_SOUT_ROUTES(4),
	ADAU1372_SOUT_ROUTES(5),
	ADAU1372_SOUT_ROUTES(6),
	ADAU1372_SOUT_ROUTES(7),

	अणु "Serial Input 0", शून्य, "Playback" पूर्ण,
	अणु "Serial Input 1", शून्य, "Playback" पूर्ण,
	अणु "Serial Input 2", शून्य, "Playback" पूर्ण,
	अणु "Serial Input 3", शून्य, "Playback" पूर्ण,
	अणु "Serial Input 4", शून्य, "Playback" पूर्ण,
	अणु "Serial Input 5", शून्य, "Playback" पूर्ण,
	अणु "Serial Input 6", शून्य, "Playback" पूर्ण,
	अणु "Serial Input 7", शून्य, "Playback" पूर्ण,

	अणु "Input ASRC0 Mux", "Serial Input 0+1", "Serial Input 0" पूर्ण,
	अणु "Input ASRC1 Mux", "Serial Input 0+1", "Serial Input 1" पूर्ण,
	अणु "Input ASRC0 Mux", "Serial Input 2+3", "Serial Input 2" पूर्ण,
	अणु "Input ASRC1 Mux", "Serial Input 2+3", "Serial Input 3" पूर्ण,
	अणु "Input ASRC0 Mux", "Serial Input 4+5", "Serial Input 4" पूर्ण,
	अणु "Input ASRC1 Mux", "Serial Input 4+5", "Serial Input 5" पूर्ण,
	अणु "Input ASRC0 Mux", "Serial Input 6+7", "Serial Input 6" पूर्ण,
	अणु "Input ASRC1 Mux", "Serial Input 6+7", "Serial Input 7" पूर्ण,
	अणु "Input ASRC0 Mux", शून्य, "Input ASRC Supply" पूर्ण,
	अणु "Input ASRC1 Mux", शून्य, "Input ASRC Supply" पूर्ण,
	अणु "Input ASRC0 Mux", शून्य, "Input ASRC0 Interpolator" पूर्ण,
	अणु "Input ASRC1 Mux", शून्य, "Input ASRC1 Interpolator" पूर्ण,

	अणु "DAC 0 Mux", "Input ASRC0", "Input ASRC0 Mux" पूर्ण,
	अणु "DAC 0 Mux", "Input ASRC1", "Input ASRC1 Mux" पूर्ण,
	अणु "DAC 1 Mux", "Input ASRC0", "Input ASRC0 Mux" पूर्ण,
	अणु "DAC 1 Mux", "Input ASRC1", "Input ASRC1 Mux" पूर्ण,

	अणु "DAC0", शून्य, "DAC 0 Mux" पूर्ण,
	अणु "DAC1", शून्य, "DAC 1 Mux" पूर्ण,
	अणु "DAC0", शून्य, "DAC0 Modulator" पूर्ण,
	अणु "DAC1", शून्य, "DAC1 Modulator" पूर्ण,

	अणु "OP_STAGE_LP", शून्य, "DAC0" पूर्ण,
	अणु "OP_STAGE_LN", शून्य, "DAC0" पूर्ण,
	अणु "OP_STAGE_RP", शून्य, "DAC1" पूर्ण,
	अणु "OP_STAGE_RN", शून्य, "DAC1" पूर्ण,

	अणु "HPOUTL", शून्य, "OP_STAGE_LP" पूर्ण,
	अणु "HPOUTL", शून्य, "OP_STAGE_LN" पूर्ण,
	अणु "HPOUTR", शून्य, "OP_STAGE_RP" पूर्ण,
	अणु "HPOUTR", शून्य, "OP_STAGE_RN" पूर्ण,
पूर्ण;

अटल पूर्णांक adau1372_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा adau1372 *adau1372 = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक sai0 = 0, sai1 = 0;
	bool invert_lrclk = false;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		adau1372->master = true;
		sai1 |= ADAU1372_SAI1_MS;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		adau1372->master = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		invert_lrclk = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		invert_lrclk = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		invert_lrclk = false;
		sai1 |= ADAU1372_SAI1_BCLKEDGE;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		invert_lrclk = true;
		sai1 |= ADAU1372_SAI1_BCLKEDGE;
		अवरोध;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		sai0 |= ADAU1372_SAI0_DELAY1;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		sai0 |= ADAU1372_SAI0_DELAY0;
		invert_lrclk = !invert_lrclk;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		sai0 |= ADAU1372_SAI0_DELAY1;
		sai1 |= ADAU1372_SAI1_LR_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		sai0 |= ADAU1372_SAI0_DELAY0;
		sai1 |= ADAU1372_SAI1_LR_MODE;
		अवरोध;
	पूर्ण

	अगर (invert_lrclk)
		sai1 |= ADAU1372_SAI1_LR_POL;

	regmap_update_bits(adau1372->regmap, ADAU1372_REG_SAI0, ADAU1372_SAI0_DELAY_MASK, sai0);
	regmap_update_bits(adau1372->regmap, ADAU1372_REG_SAI1,
			   ADAU1372_SAI1_MS | ADAU1372_SAI1_BCLKEDGE |
			   ADAU1372_SAI1_LR_MODE | ADAU1372_SAI1_LR_POL, sai1);

	वापस 0;
पूर्ण

अटल पूर्णांक adau1372_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा adau1372 *adau1372 = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक slot_width;
	अचिन्हित पूर्णांक sai0, sai1;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(adau1372_rates); i++) अणु
		अगर (rate == adau1372_rates[i])
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(adau1372_rates))
		वापस -EINVAL;

	sai0 = i;

	slot_width = adau1372->slot_width;
	अगर (slot_width == 0)
		slot_width = params_width(params);

	चयन (slot_width) अणु
	हाल 16:
		sai1 = ADAU1372_SAI1_BCLKRATE;
		अवरोध;
	हाल 32:
		sai1 = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(adau1372->regmap, ADAU1372_REG_SAI0, ADAU1372_SAI0_FS_MASK, sai0);
	regmap_update_bits(adau1372->regmap, ADAU1372_REG_SAI1, ADAU1372_SAI1_BCLKRATE, sai1);

	वापस 0;
पूर्ण

अटल पूर्णांक adau1372_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
				 अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक width)
अणु
	काष्ठा adau1372 *adau1372 = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक sai0, sai1;

	/* I2S mode */
	अगर (slots == 0) अणु
		/* The other settings करोnt matter in I2S mode */
		regmap_update_bits(adau1372->regmap, ADAU1372_REG_SAI0,
				   ADAU1372_SAI0_SAI_MASK, ADAU1372_SAI0_SAI_I2S);
		adau1372->rate_स्थिरraपूर्णांकs.mask = ADAU1372_RATE_MASK_TDM2;
		adau1372->slot_width = 0;
		वापस 0;
	पूर्ण

	/* We have 8 channels anything outside that is not supported */
	अगर ((tx_mask & ~0xff) != 0 || (rx_mask & ~0xff) != 0)
		वापस -EINVAL;

	चयन (width) अणु
	हाल 16:
		sai1 = ADAU1372_SAI1_BCLK_TDMC;
		अवरोध;
	हाल 32:
		sai1 = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (slots) अणु
	हाल 2:
		sai0 = ADAU1372_SAI0_SAI_TDM2;
		adau1372->rate_स्थिरraपूर्णांकs.mask = ADAU1372_RATE_MASK_TDM2;
		अवरोध;
	हाल 4:
		sai0 = ADAU1372_SAI0_SAI_TDM4;
		अगर (adau1372->master)
			adau1372->rate_स्थिरraपूर्णांकs.mask = ADAU1372_RATE_MASK_TDM4_MASTER;
		अन्यथा
			adau1372->rate_स्थिरraपूर्णांकs.mask = ADAU1372_RATE_MASK_TDM4;
		अवरोध;
	हाल 8:
		sai0 = ADAU1372_SAI0_SAI_TDM8;
		adau1372->rate_स्थिरraपूर्णांकs.mask = ADAU1372_RATE_MASK_TDM8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	adau1372->slot_width = width;

	regmap_update_bits(adau1372->regmap, ADAU1372_REG_SAI0, ADAU1372_SAI0_SAI_MASK, sai0);
	regmap_update_bits(adau1372->regmap, ADAU1372_REG_SAI1, ADAU1372_SAI1_BCLK_TDMC, sai1);

	/* Mask is inverted in hardware */
	regmap_ग_लिखो(adau1372->regmap, ADAU1372_REG_SOUT_CTRL, ~tx_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक adau1372_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate)
अणु
	काष्ठा adau1372 *adau1372 = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक sai1;

	अगर (tristate)
		sai1 = ADAU1372_SAI1_TDM_TS;
	अन्यथा
		sai1 = 0;

	वापस regmap_update_bits(adau1372->regmap, ADAU1372_REG_SAI1, ADAU1372_SAI1_TDM_TS, sai1);
पूर्ण

अटल पूर्णांक adau1372_startup(काष्ठा snd_pcm_substream *substream, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा adau1372 *adau1372 = snd_soc_dai_get_drvdata(dai);

	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &adau1372->rate_स्थिरraपूर्णांकs);

	वापस 0;
पूर्ण

अटल व्योम adau1372_enable_pll(काष्ठा adau1372 *adau1372)
अणु
	अचिन्हित पूर्णांक val, समयout = 0;
	पूर्णांक ret;

	regmap_update_bits(adau1372->regmap, ADAU1372_REG_CLK_CTRL,
			   ADAU1372_CLK_CTRL_PLL_EN, ADAU1372_CLK_CTRL_PLL_EN);
	करो अणु
		/* Takes about 1ms to lock */
		usleep_range(1000, 2000);
		ret = regmap_पढ़ो(adau1372->regmap, ADAU1372_REG_PLL(5), &val);
		अगर (ret)
			अवरोध;
		समयout++;
	पूर्ण जबतक (!(val & 1) && समयout < 3);

	अगर (ret < 0 || !(val & 1))
		dev_err(adau1372->dev, "Failed to lock PLL\n");
पूर्ण

अटल व्योम adau1372_set_घातer(काष्ठा adau1372 *adau1372, bool enable)
अणु
	अगर (adau1372->enabled == enable)
		वापस;

	अगर (enable) अणु
		अचिन्हित पूर्णांक clk_ctrl = ADAU1372_CLK_CTRL_MCLK_EN;

		clk_prepare_enable(adau1372->mclk);
		अगर (adau1372->pd_gpio)
			gpiod_set_value(adau1372->pd_gpio, 0);

		अगर (adau1372->चयन_mode)
			adau1372->चयन_mode(adau1372->dev);

		regcache_cache_only(adau1372->regmap, false);

		/*
		 * Clocks needs to be enabled beक्रमe any other रेजिस्टर can be
		 * accessed.
		 */
		अगर (adau1372->use_pll) अणु
			adau1372_enable_pll(adau1372);
			clk_ctrl |= ADAU1372_CLK_CTRL_CLKSRC;
		पूर्ण

		regmap_update_bits(adau1372->regmap, ADAU1372_REG_CLK_CTRL,
				   ADAU1372_CLK_CTRL_MCLK_EN | ADAU1372_CLK_CTRL_CLKSRC, clk_ctrl);
		regcache_sync(adau1372->regmap);
	पूर्ण अन्यथा अणु
		अगर (adau1372->pd_gpio) अणु
			/*
			 * This will turn everything off and reset the रेजिस्टर
			 * map. No need to करो any रेजिस्टर ग_लिखोs to manually
			 * turn things off.
			 */
			gpiod_set_value(adau1372->pd_gpio, 1);
			regcache_mark_dirty(adau1372->regmap);
		पूर्ण अन्यथा अणु
			regmap_update_bits(adau1372->regmap, ADAU1372_REG_CLK_CTRL,
					   ADAU1372_CLK_CTRL_MCLK_EN | ADAU1372_CLK_CTRL_PLL_EN, 0);
		पूर्ण
		clk_disable_unprepare(adau1372->mclk);
		regcache_cache_only(adau1372->regmap, true);
	पूर्ण

	adau1372->enabled = enable;
पूर्ण

अटल पूर्णांक adau1372_set_bias_level(काष्ठा snd_soc_component *component,
				   क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा adau1372 *adau1372 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		adau1372_set_घातer(adau1372, true);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		adau1372_set_घातer(adau1372, false);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver adau1372_driver = अणु
	.set_bias_level = adau1372_set_bias_level,
	.controls = adau1372_controls,
	.num_controls = ARRAY_SIZE(adau1372_controls),
	.dapm_widमाला_लो = adau1372_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(adau1372_dapm_widमाला_लो),
	.dapm_routes = adau1372_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(adau1372_dapm_routes),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops adau1372_dai_ops = अणु
	.set_fmt = adau1372_set_dai_fmt,
	.set_tdm_slot = adau1372_set_tdm_slot,
	.set_tristate = adau1372_set_tristate,
	.hw_params = adau1372_hw_params,
	.startup = adau1372_startup,
पूर्ण;

#घोषणा ADAU1372_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |	SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver adau1372_dai_driver = अणु
	.name = "adau1372",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = ADAU1372_FORMATS,
		.sig_bits = 24,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = ADAU1372_FORMATS,
		.sig_bits = 24,
	पूर्ण,
	.ops = &adau1372_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक adau1372_setup_pll(काष्ठा adau1372 *adau1372, अचिन्हित पूर्णांक rate)
अणु
	u8 regs[5];
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = adau_calc_pll_cfg(rate, 49152000, regs);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++)
		regmap_ग_लिखो(adau1372->regmap, ADAU1372_REG_PLL(i), regs[i]);

	वापस 0;
पूर्ण

पूर्णांक adau1372_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		   व्योम (*चयन_mode)(काष्ठा device *dev))
अणु
	काष्ठा adau1372 *adau1372;
	अचिन्हित पूर्णांक clk_ctrl;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	adau1372 = devm_kzalloc(dev, माप(*adau1372), GFP_KERNEL);
	अगर (!adau1372)
		वापस -ENOMEM;

	adau1372->clk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(adau1372->clk))
		वापस PTR_ERR(adau1372->clk);

	adau1372->pd_gpio = devm_gpiod_get_optional(dev, "powerdown", GPIOD_OUT_HIGH);
	अगर (IS_ERR(adau1372->pd_gpio))
		वापस PTR_ERR(adau1372->pd_gpio);

	adau1372->regmap = regmap;
	adau1372->चयन_mode = चयन_mode;
	adau1372->dev = dev;
	adau1372->rate_स्थिरraपूर्णांकs.list = adau1372_rates;
	adau1372->rate_स्थिरraपूर्णांकs.count = ARRAY_SIZE(adau1372_rates);
	adau1372->rate_स्थिरraपूर्णांकs.mask = ADAU1372_RATE_MASK_TDM2;

	dev_set_drvdata(dev, adau1372);

	/*
	 * The datasheet says that the पूर्णांकernal MCLK always needs to run at
	 * 12.288MHz. Automatically choose a valid configuration from the
	 * बाह्यal घड़ी.
	 */
	rate = clk_get_rate(adau1372->clk);

	चयन (rate) अणु
	हाल 12288000:
		clk_ctrl = ADAU1372_CLK_CTRL_CC_MDIV;
		अवरोध;
	हाल 24576000:
		clk_ctrl = 0;
		अवरोध;
	शेष:
		clk_ctrl = 0;
		ret = adau1372_setup_pll(adau1372, rate);
		अगर (ret < 0)
			वापस ret;
		adau1372->use_pll = true;
		अवरोध;
	पूर्ण

	/*
	 * Most of the रेजिस्टरs are inaccessible unless the पूर्णांकernal घड़ी is
	 * enabled.
	 */
	regcache_cache_only(regmap, true);

	regmap_update_bits(regmap, ADAU1372_REG_CLK_CTRL, ADAU1372_CLK_CTRL_CC_MDIV, clk_ctrl);

	/*
	 * No pinctrl support yet, put the multi-purpose pins in the most
	 * sensible mode क्रम general purpose CODEC operation.
	 */
	regmap_ग_लिखो(regmap, ADAU1372_REG_MODE_MP(1), 0x00); /* SDATA OUT */
	regmap_ग_लिखो(regmap, ADAU1372_REG_MODE_MP(6), 0x12); /* CLOCKOUT */

	regmap_ग_लिखो(regmap, ADAU1372_REG_OP_STAGE_MUTE, 0x0);

	regmap_ग_लिखो(regmap, 0x7, 0x01); /* CLOCK OUT */

	वापस  devm_snd_soc_रेजिस्टर_component(dev, &adau1372_driver, &adau1372_dai_driver, 1);
पूर्ण
EXPORT_SYMBOL(adau1372_probe);

अटल स्थिर काष्ठा reg_शेष adau1372_reg_शेषs[] = अणु
	अणु ADAU1372_REG_CLK_CTRL,		0x00 पूर्ण,
	अणु ADAU1372_REG_PLL(0),			0x00 पूर्ण,
	अणु ADAU1372_REG_PLL(1),			0x00 पूर्ण,
	अणु ADAU1372_REG_PLL(2),			0x00 पूर्ण,
	अणु ADAU1372_REG_PLL(3),			0x00 पूर्ण,
	अणु ADAU1372_REG_PLL(4),			0x00 पूर्ण,
	अणु ADAU1372_REG_PLL(5),			0x00 पूर्ण,
	अणु ADAU1372_REG_DAC_SOURCE,		0x10 पूर्ण,
	अणु ADAU1372_REG_SOUT_SOURCE_0_1,		0x54 पूर्ण,
	अणु ADAU1372_REG_SOUT_SOURCE_2_3,		0x76 पूर्ण,
	अणु ADAU1372_REG_SOUT_SOURCE_4_5,		0x54 पूर्ण,
	अणु ADAU1372_REG_SOUT_SOURCE_6_7,		0x76 पूर्ण,
	अणु ADAU1372_REG_ADC_SDATA_CH,		0x04 पूर्ण,
	अणु ADAU1372_REG_ASRCO_SOURCE_0_1,	0x10 पूर्ण,
	अणु ADAU1372_REG_ASRCO_SOURCE_2_3,	0x32 पूर्ण,
	अणु ADAU1372_REG_ASRC_MODE,		0x00 पूर्ण,
	अणु ADAU1372_REG_ADC_CTRL0,		0x19 पूर्ण,
	अणु ADAU1372_REG_ADC_CTRL1,		0x19 पूर्ण,
	अणु ADAU1372_REG_ADC_CTRL2,		0x00 पूर्ण,
	अणु ADAU1372_REG_ADC_CTRL3,		0x00 पूर्ण,
	अणु ADAU1372_REG_ADC_VOL(0),		0x00 पूर्ण,
	अणु ADAU1372_REG_ADC_VOL(1),		0x00 पूर्ण,
	अणु ADAU1372_REG_ADC_VOL(2),		0x00 पूर्ण,
	अणु ADAU1372_REG_ADC_VOL(3),		0x00 पूर्ण,
	अणु ADAU1372_REG_PGA_CTRL(0),		0x40 पूर्ण,
	अणु ADAU1372_REG_PGA_CTRL(1),		0x40 पूर्ण,
	अणु ADAU1372_REG_PGA_CTRL(2),		0x40 पूर्ण,
	अणु ADAU1372_REG_PGA_CTRL(3),		0x40 पूर्ण,
	अणु ADAU1372_REG_PGA_BOOST,		0x00 पूर्ण,
	अणु ADAU1372_REG_MICBIAS,			0x00 पूर्ण,
	अणु ADAU1372_REG_DAC_CTRL,		0x18 पूर्ण,
	अणु ADAU1372_REG_DAC_VOL(0),		0x00 पूर्ण,
	अणु ADAU1372_REG_DAC_VOL(1),		0x00 पूर्ण,
	अणु ADAU1372_REG_OP_STAGE_MUTE,		0x0f पूर्ण,
	अणु ADAU1372_REG_SAI0,			0x00 पूर्ण,
	अणु ADAU1372_REG_SAI1,			0x00 पूर्ण,
	अणु ADAU1372_REG_SOUT_CTRL,		0x00 पूर्ण,
	अणु ADAU1372_REG_MODE_MP(0),		0x00 पूर्ण,
	अणु ADAU1372_REG_MODE_MP(1),		0x10 पूर्ण,
	अणु ADAU1372_REG_MODE_MP(4),		0x00 पूर्ण,
	अणु ADAU1372_REG_MODE_MP(5),		0x00 पूर्ण,
	अणु ADAU1372_REG_MODE_MP(6),		0x11 पूर्ण,
	अणु ADAU1372_REG_OP_STAGE_CTRL,		0x0f पूर्ण,
	अणु ADAU1372_REG_DECIM_PWR,		0x00 पूर्ण,
	अणु ADAU1372_REG_INTERP_PWR,		0x00 पूर्ण,
	अणु ADAU1372_REG_BIAS_CTRL0,		0x00 पूर्ण,
	अणु ADAU1372_REG_BIAS_CTRL1,		0x00 पूर्ण,
पूर्ण;

अटल bool adau1372_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg == ADAU1372_REG_PLL(5))
		वापस true;

	वापस false;
पूर्ण

स्थिर काष्ठा regmap_config adau1372_regmap_config = अणु
	.val_bits = 8,
	.reg_bits = 16,
	.max_रेजिस्टर = 0x4d,

	.reg_शेषs = adau1372_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(adau1372_reg_शेषs),
	.अस्थिर_reg = adau1372_अस्थिर_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;
EXPORT_SYMBOL_GPL(adau1372_regmap_config);

MODULE_DESCRIPTION("ASoC ADAU1372 CODEC driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL v2");
