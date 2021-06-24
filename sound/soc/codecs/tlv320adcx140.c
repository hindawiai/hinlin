<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// TLV320ADCX140 Sound driver
// Copyright (C) 2020 Texas Instruments Incorporated - https://www.ti.com/

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/acpi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "tlv320adcx140.h"

काष्ठा adcx140_priv अणु
	काष्ठा snd_soc_component *component;
	काष्ठा regulator *supply_areg;
	काष्ठा gpio_desc *gpio_reset;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;

	bool micbias_vg;

	अचिन्हित पूर्णांक dai_fmt;
	अचिन्हित पूर्णांक tdm_delay;
	अचिन्हित पूर्णांक slot_width;
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpo_config_names[] = अणु
	"ti,gpo-config-1",
	"ti,gpo-config-2",
	"ti,gpo-config-3",
	"ti,gpo-config-4",
पूर्ण;

अटल स्थिर काष्ठा reg_शेष adcx140_reg_शेषs[] = अणु
	अणु ADCX140_PAGE_SELECT, 0x00 पूर्ण,
	अणु ADCX140_SW_RESET, 0x00 पूर्ण,
	अणु ADCX140_SLEEP_CFG, 0x00 पूर्ण,
	अणु ADCX140_SHDN_CFG, 0x05 पूर्ण,
	अणु ADCX140_ASI_CFG0, 0x30 पूर्ण,
	अणु ADCX140_ASI_CFG1, 0x00 पूर्ण,
	अणु ADCX140_ASI_CFG2, 0x00 पूर्ण,
	अणु ADCX140_ASI_CH1, 0x00 पूर्ण,
	अणु ADCX140_ASI_CH2, 0x01 पूर्ण,
	अणु ADCX140_ASI_CH3, 0x02 पूर्ण,
	अणु ADCX140_ASI_CH4, 0x03 पूर्ण,
	अणु ADCX140_ASI_CH5, 0x04 पूर्ण,
	अणु ADCX140_ASI_CH6, 0x05 पूर्ण,
	अणु ADCX140_ASI_CH7, 0x06 पूर्ण,
	अणु ADCX140_ASI_CH8, 0x07 पूर्ण,
	अणु ADCX140_MST_CFG0, 0x02 पूर्ण,
	अणु ADCX140_MST_CFG1, 0x48 पूर्ण,
	अणु ADCX140_ASI_STS, 0xff पूर्ण,
	अणु ADCX140_CLK_SRC, 0x10 पूर्ण,
	अणु ADCX140_PDMCLK_CFG, 0x40 पूर्ण,
	अणु ADCX140_PDM_CFG, 0x00 पूर्ण,
	अणु ADCX140_GPIO_CFG0, 0x22 पूर्ण,
	अणु ADCX140_GPO_CFG0, 0x00 पूर्ण,
	अणु ADCX140_GPO_CFG1, 0x00 पूर्ण,
	अणु ADCX140_GPO_CFG2, 0x00 पूर्ण,
	अणु ADCX140_GPO_CFG3, 0x00 पूर्ण,
	अणु ADCX140_GPO_VAL, 0x00 पूर्ण,
	अणु ADCX140_GPIO_MON, 0x00 पूर्ण,
	अणु ADCX140_GPI_CFG0, 0x00 पूर्ण,
	अणु ADCX140_GPI_CFG1, 0x00 पूर्ण,
	अणु ADCX140_GPI_MON, 0x00 पूर्ण,
	अणु ADCX140_INT_CFG, 0x00 पूर्ण,
	अणु ADCX140_INT_MASK0, 0xff पूर्ण,
	अणु ADCX140_INT_LTCH0, 0x00 पूर्ण,
	अणु ADCX140_BIAS_CFG, 0x00 पूर्ण,
	अणु ADCX140_CH1_CFG0, 0x00 पूर्ण,
	अणु ADCX140_CH1_CFG1, 0x00 पूर्ण,
	अणु ADCX140_CH1_CFG2, 0xc9 पूर्ण,
	अणु ADCX140_CH1_CFG3, 0x80 पूर्ण,
	अणु ADCX140_CH1_CFG4, 0x00 पूर्ण,
	अणु ADCX140_CH2_CFG0, 0x00 पूर्ण,
	अणु ADCX140_CH2_CFG1, 0x00 पूर्ण,
	अणु ADCX140_CH2_CFG2, 0xc9 पूर्ण,
	अणु ADCX140_CH2_CFG3, 0x80 पूर्ण,
	अणु ADCX140_CH2_CFG4, 0x00 पूर्ण,
	अणु ADCX140_CH3_CFG0, 0x00 पूर्ण,
	अणु ADCX140_CH3_CFG1, 0x00 पूर्ण,
	अणु ADCX140_CH3_CFG2, 0xc9 पूर्ण,
	अणु ADCX140_CH3_CFG3, 0x80 पूर्ण,
	अणु ADCX140_CH3_CFG4, 0x00 पूर्ण,
	अणु ADCX140_CH4_CFG0, 0x00 पूर्ण,
	अणु ADCX140_CH4_CFG1, 0x00 पूर्ण,
	अणु ADCX140_CH4_CFG2, 0xc9 पूर्ण,
	अणु ADCX140_CH4_CFG3, 0x80 पूर्ण,
	अणु ADCX140_CH4_CFG4, 0x00 पूर्ण,
	अणु ADCX140_CH5_CFG2, 0xc9 पूर्ण,
	अणु ADCX140_CH5_CFG3, 0x80 पूर्ण,
	अणु ADCX140_CH5_CFG4, 0x00 पूर्ण,
	अणु ADCX140_CH6_CFG2, 0xc9 पूर्ण,
	अणु ADCX140_CH6_CFG3, 0x80 पूर्ण,
	अणु ADCX140_CH6_CFG4, 0x00 पूर्ण,
	अणु ADCX140_CH7_CFG2, 0xc9 पूर्ण,
	अणु ADCX140_CH7_CFG3, 0x80 पूर्ण,
	अणु ADCX140_CH7_CFG4, 0x00 पूर्ण,
	अणु ADCX140_CH8_CFG2, 0xc9 पूर्ण,
	अणु ADCX140_CH8_CFG3, 0x80 पूर्ण,
	अणु ADCX140_CH8_CFG4, 0x00 पूर्ण,
	अणु ADCX140_DSP_CFG0, 0x01 पूर्ण,
	अणु ADCX140_DSP_CFG1, 0x40 पूर्ण,
	अणु ADCX140_DRE_CFG0, 0x7b पूर्ण,
	अणु ADCX140_AGC_CFG0, 0xe7 पूर्ण,
	अणु ADCX140_IN_CH_EN, 0xf0 पूर्ण,
	अणु ADCX140_ASI_OUT_CH_EN, 0x00 पूर्ण,
	अणु ADCX140_PWR_CFG, 0x00 पूर्ण,
	अणु ADCX140_DEV_STS0, 0x00 पूर्ण,
	अणु ADCX140_DEV_STS1, 0x80 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range_cfg adcx140_ranges[] = अणु
	अणु
		.range_min = 0,
		.range_max = 12 * 128,
		.selector_reg = ADCX140_PAGE_SELECT,
		.selector_mask = 0xff,
		.selector_shअगरt = 0,
		.winकरोw_start = 0,
		.winकरोw_len = 128,
	पूर्ण,
पूर्ण;

अटल bool adcx140_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ADCX140_SW_RESET:
	हाल ADCX140_DEV_STS0:
	हाल ADCX140_DEV_STS1:
	हाल ADCX140_ASI_STS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config adcx140_i2c_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.reg_शेषs = adcx140_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(adcx140_reg_शेषs),
	.cache_type = REGCACHE_FLAT,
	.ranges = adcx140_ranges,
	.num_ranges = ARRAY_SIZE(adcx140_ranges),
	.max_रेजिस्टर = 12 * 128,
	.अस्थिर_reg = adcx140_अस्थिर,
पूर्ण;

/* Digital Volume control. From -100 to 27 dB in 0.5 dB steps */
अटल DECLARE_TLV_DB_SCALE(dig_vol_tlv, -10050, 50, 0);

/* ADC gain. From 0 to 42 dB in 1 dB steps */
अटल DECLARE_TLV_DB_SCALE(adc_tlv, 0, 100, 0);

/* DRE Level. From -12 dB to -66 dB in 1 dB steps */
अटल DECLARE_TLV_DB_SCALE(dre_thresh_tlv, -6600, 100, 0);
/* DRE Max Gain. From 2 dB to 26 dB in 2 dB steps */
अटल DECLARE_TLV_DB_SCALE(dre_gain_tlv, 200, 200, 0);

/* AGC Level. From -6 dB to -36 dB in 2 dB steps */
अटल DECLARE_TLV_DB_SCALE(agc_thresh_tlv, -3600, 200, 0);
/* AGC Max Gain. From 3 dB to 42 dB in 3 dB steps */
अटल DECLARE_TLV_DB_SCALE(agc_gain_tlv, 300, 300, 0);

अटल स्थिर अक्षर * स्थिर decimation_filter_text[] = अणु
	"Linear Phase", "Low Latency", "Ultra-low Latency"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(decimation_filter_क्रमागत, ADCX140_DSP_CFG0, 4,
			    decimation_filter_text);

अटल स्थिर काष्ठा snd_kcontrol_new decimation_filter_controls[] = अणु
	SOC_DAPM_ENUM("Decimation Filter", decimation_filter_क्रमागत),
पूर्ण;

अटल स्थिर अक्षर * स्थिर pdmclk_text[] = अणु
	"2.8224 MHz", "1.4112 MHz", "705.6 kHz", "5.6448 MHz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(pdmclk_select_क्रमागत, ADCX140_PDMCLK_CFG, 0,
			    pdmclk_text);

अटल स्थिर काष्ठा snd_kcontrol_new pdmclk_भाग_controls[] = अणु
	SOC_DAPM_ENUM("PDM Clk Divider Select", pdmclk_select_क्रमागत),
पूर्ण;

अटल स्थिर अक्षर * स्थिर resistor_text[] = अणु
	"2.5 kOhm", "10 kOhm", "20 kOhm"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(in1_resistor_क्रमागत, ADCX140_CH1_CFG0, 2,
			    resistor_text);
अटल SOC_ENUM_SINGLE_DECL(in2_resistor_क्रमागत, ADCX140_CH2_CFG0, 2,
			    resistor_text);
अटल SOC_ENUM_SINGLE_DECL(in3_resistor_क्रमागत, ADCX140_CH3_CFG0, 2,
			    resistor_text);
अटल SOC_ENUM_SINGLE_DECL(in4_resistor_क्रमागत, ADCX140_CH4_CFG0, 2,
			    resistor_text);

अटल स्थिर काष्ठा snd_kcontrol_new in1_resistor_controls[] = अणु
	SOC_DAPM_ENUM("CH1 Resistor Select", in1_resistor_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new in2_resistor_controls[] = अणु
	SOC_DAPM_ENUM("CH2 Resistor Select", in2_resistor_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new in3_resistor_controls[] = अणु
	SOC_DAPM_ENUM("CH3 Resistor Select", in3_resistor_क्रमागत),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new in4_resistor_controls[] = अणु
	SOC_DAPM_ENUM("CH4 Resistor Select", in4_resistor_क्रमागत),
पूर्ण;

/* Analog/Digital Selection */
अटल स्थिर अक्षर * स्थिर adcx140_mic_sel_text[] = अणु"Analog", "Line In", "Digital"पूर्ण;
अटल स्थिर अक्षर * स्थिर adcx140_analog_sel_text[] = अणु"Analog", "Line In"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adcx140_mic1p_क्रमागत,
			    ADCX140_CH1_CFG0, 5,
			    adcx140_mic_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_mic1p_control =
SOC_DAPM_ENUM("MIC1P MUX", adcx140_mic1p_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(adcx140_mic1_analog_क्रमागत,
			    ADCX140_CH1_CFG0, 7,
			    adcx140_analog_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_mic1_analog_control =
SOC_DAPM_ENUM("MIC1 Analog MUX", adcx140_mic1_analog_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(adcx140_mic1m_क्रमागत,
			    ADCX140_CH1_CFG0, 5,
			    adcx140_mic_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_mic1m_control =
SOC_DAPM_ENUM("MIC1M MUX", adcx140_mic1m_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(adcx140_mic2p_क्रमागत,
			    ADCX140_CH2_CFG0, 5,
			    adcx140_mic_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_mic2p_control =
SOC_DAPM_ENUM("MIC2P MUX", adcx140_mic2p_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(adcx140_mic2_analog_क्रमागत,
			    ADCX140_CH2_CFG0, 7,
			    adcx140_analog_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_mic2_analog_control =
SOC_DAPM_ENUM("MIC2 Analog MUX", adcx140_mic2_analog_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(adcx140_mic2m_क्रमागत,
			    ADCX140_CH2_CFG0, 5,
			    adcx140_mic_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_mic2m_control =
SOC_DAPM_ENUM("MIC2M MUX", adcx140_mic2m_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(adcx140_mic3p_क्रमागत,
			    ADCX140_CH3_CFG0, 5,
			    adcx140_mic_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_mic3p_control =
SOC_DAPM_ENUM("MIC3P MUX", adcx140_mic3p_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(adcx140_mic3_analog_क्रमागत,
			    ADCX140_CH3_CFG0, 7,
			    adcx140_analog_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_mic3_analog_control =
SOC_DAPM_ENUM("MIC3 Analog MUX", adcx140_mic3_analog_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(adcx140_mic3m_क्रमागत,
			    ADCX140_CH3_CFG0, 5,
			    adcx140_mic_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_mic3m_control =
SOC_DAPM_ENUM("MIC3M MUX", adcx140_mic3m_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(adcx140_mic4p_क्रमागत,
			    ADCX140_CH4_CFG0, 5,
			    adcx140_mic_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_mic4p_control =
SOC_DAPM_ENUM("MIC4P MUX", adcx140_mic4p_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(adcx140_mic4_analog_क्रमागत,
			    ADCX140_CH4_CFG0, 7,
			    adcx140_analog_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_mic4_analog_control =
SOC_DAPM_ENUM("MIC4 Analog MUX", adcx140_mic4_analog_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(adcx140_mic4m_क्रमागत,
			    ADCX140_CH4_CFG0, 5,
			    adcx140_mic_sel_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_mic4m_control =
SOC_DAPM_ENUM("MIC4M MUX", adcx140_mic4m_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_ch1_en_चयन =
	SOC_DAPM_SINGLE("Switch", ADCX140_ASI_OUT_CH_EN, 7, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_ch2_en_चयन =
	SOC_DAPM_SINGLE("Switch", ADCX140_ASI_OUT_CH_EN, 6, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_ch3_en_चयन =
	SOC_DAPM_SINGLE("Switch", ADCX140_ASI_OUT_CH_EN, 5, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_ch4_en_चयन =
	SOC_DAPM_SINGLE("Switch", ADCX140_ASI_OUT_CH_EN, 4, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_ch5_en_चयन =
	SOC_DAPM_SINGLE("Switch", ADCX140_ASI_OUT_CH_EN, 3, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_ch6_en_चयन =
	SOC_DAPM_SINGLE("Switch", ADCX140_ASI_OUT_CH_EN, 2, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_ch7_en_चयन =
	SOC_DAPM_SINGLE("Switch", ADCX140_ASI_OUT_CH_EN, 1, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_ch8_en_चयन =
	SOC_DAPM_SINGLE("Switch", ADCX140_ASI_OUT_CH_EN, 0, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_ch1_dre_en_चयन =
	SOC_DAPM_SINGLE("Switch", ADCX140_CH1_CFG0, 0, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_ch2_dre_en_चयन =
	SOC_DAPM_SINGLE("Switch", ADCX140_CH2_CFG0, 0, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_ch3_dre_en_चयन =
	SOC_DAPM_SINGLE("Switch", ADCX140_CH3_CFG0, 0, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_ch4_dre_en_चयन =
	SOC_DAPM_SINGLE("Switch", ADCX140_CH4_CFG0, 0, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_dapm_dre_en_चयन =
	SOC_DAPM_SINGLE("Switch", ADCX140_DSP_CFG1, 3, 1, 0);

/* Output Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new adcx140_output_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Digital CH1 Switch", 0, 0, 0, 0),
	SOC_DAPM_SINGLE("Digital CH2 Switch", 0, 0, 0, 0),
	SOC_DAPM_SINGLE("Digital CH3 Switch", 0, 0, 0, 0),
	SOC_DAPM_SINGLE("Digital CH4 Switch", 0, 0, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget adcx140_dapm_widमाला_लो[] = अणु
	/* Analog Dअगरferential Inमाला_दो */
	SND_SOC_DAPM_INPUT("MIC1P"),
	SND_SOC_DAPM_INPUT("MIC1M"),
	SND_SOC_DAPM_INPUT("MIC2P"),
	SND_SOC_DAPM_INPUT("MIC2M"),
	SND_SOC_DAPM_INPUT("MIC3P"),
	SND_SOC_DAPM_INPUT("MIC3M"),
	SND_SOC_DAPM_INPUT("MIC4P"),
	SND_SOC_DAPM_INPUT("MIC4M"),

	SND_SOC_DAPM_OUTPUT("CH1_OUT"),
	SND_SOC_DAPM_OUTPUT("CH2_OUT"),
	SND_SOC_DAPM_OUTPUT("CH3_OUT"),
	SND_SOC_DAPM_OUTPUT("CH4_OUT"),
	SND_SOC_DAPM_OUTPUT("CH5_OUT"),
	SND_SOC_DAPM_OUTPUT("CH6_OUT"),
	SND_SOC_DAPM_OUTPUT("CH7_OUT"),
	SND_SOC_DAPM_OUTPUT("CH8_OUT"),

	SND_SOC_DAPM_MIXER("Output Mixer", SND_SOC_NOPM, 0, 0,
		&adcx140_output_mixer_controls[0],
		ARRAY_SIZE(adcx140_output_mixer_controls)),

	/* Input Selection to MIC_PGA */
	SND_SOC_DAPM_MUX("MIC1P Input Mux", SND_SOC_NOPM, 0, 0,
			 &adcx140_dapm_mic1p_control),
	SND_SOC_DAPM_MUX("MIC2P Input Mux", SND_SOC_NOPM, 0, 0,
			 &adcx140_dapm_mic2p_control),
	SND_SOC_DAPM_MUX("MIC3P Input Mux", SND_SOC_NOPM, 0, 0,
			 &adcx140_dapm_mic3p_control),
	SND_SOC_DAPM_MUX("MIC4P Input Mux", SND_SOC_NOPM, 0, 0,
			 &adcx140_dapm_mic4p_control),

	/* Input Selection to MIC_PGA */
	SND_SOC_DAPM_MUX("MIC1 Analog Mux", SND_SOC_NOPM, 0, 0,
			 &adcx140_dapm_mic1_analog_control),
	SND_SOC_DAPM_MUX("MIC2 Analog Mux", SND_SOC_NOPM, 0, 0,
			 &adcx140_dapm_mic2_analog_control),
	SND_SOC_DAPM_MUX("MIC3 Analog Mux", SND_SOC_NOPM, 0, 0,
			 &adcx140_dapm_mic3_analog_control),
	SND_SOC_DAPM_MUX("MIC4 Analog Mux", SND_SOC_NOPM, 0, 0,
			 &adcx140_dapm_mic4_analog_control),

	SND_SOC_DAPM_MUX("MIC1M Input Mux", SND_SOC_NOPM, 0, 0,
			 &adcx140_dapm_mic1m_control),
	SND_SOC_DAPM_MUX("MIC2M Input Mux", SND_SOC_NOPM, 0, 0,
			 &adcx140_dapm_mic2m_control),
	SND_SOC_DAPM_MUX("MIC3M Input Mux", SND_SOC_NOPM, 0, 0,
			 &adcx140_dapm_mic3m_control),
	SND_SOC_DAPM_MUX("MIC4M Input Mux", SND_SOC_NOPM, 0, 0,
			 &adcx140_dapm_mic4m_control),

	SND_SOC_DAPM_PGA("MIC_GAIN_CTL_CH1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MIC_GAIN_CTL_CH2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MIC_GAIN_CTL_CH3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MIC_GAIN_CTL_CH4", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_ADC("CH1_ADC", "CH1 Capture", ADCX140_IN_CH_EN, 7, 0),
	SND_SOC_DAPM_ADC("CH2_ADC", "CH2 Capture", ADCX140_IN_CH_EN, 6, 0),
	SND_SOC_DAPM_ADC("CH3_ADC", "CH3 Capture", ADCX140_IN_CH_EN, 5, 0),
	SND_SOC_DAPM_ADC("CH4_ADC", "CH4 Capture", ADCX140_IN_CH_EN, 4, 0),

	SND_SOC_DAPM_ADC("CH1_DIG", "CH1 Capture", ADCX140_IN_CH_EN, 7, 0),
	SND_SOC_DAPM_ADC("CH2_DIG", "CH2 Capture", ADCX140_IN_CH_EN, 6, 0),
	SND_SOC_DAPM_ADC("CH3_DIG", "CH3 Capture", ADCX140_IN_CH_EN, 5, 0),
	SND_SOC_DAPM_ADC("CH4_DIG", "CH4 Capture", ADCX140_IN_CH_EN, 4, 0),
	SND_SOC_DAPM_ADC("CH5_DIG", "CH5 Capture", ADCX140_IN_CH_EN, 3, 0),
	SND_SOC_DAPM_ADC("CH6_DIG", "CH6 Capture", ADCX140_IN_CH_EN, 2, 0),
	SND_SOC_DAPM_ADC("CH7_DIG", "CH7 Capture", ADCX140_IN_CH_EN, 1, 0),
	SND_SOC_DAPM_ADC("CH8_DIG", "CH8 Capture", ADCX140_IN_CH_EN, 0, 0),


	SND_SOC_DAPM_SWITCH("CH1_ASI_EN", SND_SOC_NOPM, 0, 0,
			    &adcx140_dapm_ch1_en_चयन),
	SND_SOC_DAPM_SWITCH("CH2_ASI_EN", SND_SOC_NOPM, 0, 0,
			    &adcx140_dapm_ch2_en_चयन),
	SND_SOC_DAPM_SWITCH("CH3_ASI_EN", SND_SOC_NOPM, 0, 0,
			    &adcx140_dapm_ch3_en_चयन),
	SND_SOC_DAPM_SWITCH("CH4_ASI_EN", SND_SOC_NOPM, 0, 0,
			    &adcx140_dapm_ch4_en_चयन),

	SND_SOC_DAPM_SWITCH("CH5_ASI_EN", SND_SOC_NOPM, 0, 0,
			    &adcx140_dapm_ch5_en_चयन),
	SND_SOC_DAPM_SWITCH("CH6_ASI_EN", SND_SOC_NOPM, 0, 0,
			    &adcx140_dapm_ch6_en_चयन),
	SND_SOC_DAPM_SWITCH("CH7_ASI_EN", SND_SOC_NOPM, 0, 0,
			    &adcx140_dapm_ch7_en_चयन),
	SND_SOC_DAPM_SWITCH("CH8_ASI_EN", SND_SOC_NOPM, 0, 0,
			    &adcx140_dapm_ch8_en_चयन),

	SND_SOC_DAPM_SWITCH("DRE_ENABLE", SND_SOC_NOPM, 0, 0,
			    &adcx140_dapm_dre_en_चयन),

	SND_SOC_DAPM_SWITCH("CH1_DRE_EN", SND_SOC_NOPM, 0, 0,
			    &adcx140_dapm_ch1_dre_en_चयन),
	SND_SOC_DAPM_SWITCH("CH2_DRE_EN", SND_SOC_NOPM, 0, 0,
			    &adcx140_dapm_ch2_dre_en_चयन),
	SND_SOC_DAPM_SWITCH("CH3_DRE_EN", SND_SOC_NOPM, 0, 0,
			    &adcx140_dapm_ch3_dre_en_चयन),
	SND_SOC_DAPM_SWITCH("CH4_DRE_EN", SND_SOC_NOPM, 0, 0,
			    &adcx140_dapm_ch4_dre_en_चयन),

	SND_SOC_DAPM_MUX("IN1 Analog Mic Resistor", SND_SOC_NOPM, 0, 0,
			in1_resistor_controls),
	SND_SOC_DAPM_MUX("IN2 Analog Mic Resistor", SND_SOC_NOPM, 0, 0,
			in2_resistor_controls),
	SND_SOC_DAPM_MUX("IN3 Analog Mic Resistor", SND_SOC_NOPM, 0, 0,
			in3_resistor_controls),
	SND_SOC_DAPM_MUX("IN4 Analog Mic Resistor", SND_SOC_NOPM, 0, 0,
			in4_resistor_controls),

	SND_SOC_DAPM_MUX("PDM Clk Div Select", SND_SOC_NOPM, 0, 0,
			pdmclk_भाग_controls),

	SND_SOC_DAPM_MUX("Decimation Filter", SND_SOC_NOPM, 0, 0,
			decimation_filter_controls),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adcx140_audio_map[] = अणु
	/* Outमाला_दो */
	अणु"CH1_OUT", शून्य, "Output Mixer"पूर्ण,
	अणु"CH2_OUT", शून्य, "Output Mixer"पूर्ण,
	अणु"CH3_OUT", शून्य, "Output Mixer"पूर्ण,
	अणु"CH4_OUT", शून्य, "Output Mixer"पूर्ण,

	अणु"CH1_ASI_EN", "Switch", "CH1_ADC"पूर्ण,
	अणु"CH2_ASI_EN", "Switch", "CH2_ADC"पूर्ण,
	अणु"CH3_ASI_EN", "Switch", "CH3_ADC"पूर्ण,
	अणु"CH4_ASI_EN", "Switch", "CH4_ADC"पूर्ण,

	अणु"CH1_ASI_EN", "Switch", "CH1_DIG"पूर्ण,
	अणु"CH2_ASI_EN", "Switch", "CH2_DIG"पूर्ण,
	अणु"CH3_ASI_EN", "Switch", "CH3_DIG"पूर्ण,
	अणु"CH4_ASI_EN", "Switch", "CH4_DIG"पूर्ण,
	अणु"CH5_ASI_EN", "Switch", "CH5_DIG"पूर्ण,
	अणु"CH6_ASI_EN", "Switch", "CH6_DIG"पूर्ण,
	अणु"CH7_ASI_EN", "Switch", "CH7_DIG"पूर्ण,
	अणु"CH8_ASI_EN", "Switch", "CH8_DIG"पूर्ण,

	अणु"CH5_ASI_EN", "Switch", "CH5_OUT"पूर्ण,
	अणु"CH6_ASI_EN", "Switch", "CH6_OUT"पूर्ण,
	अणु"CH7_ASI_EN", "Switch", "CH7_OUT"पूर्ण,
	अणु"CH8_ASI_EN", "Switch", "CH8_OUT"पूर्ण,

	अणु"Decimation Filter", "Linear Phase", "DRE_ENABLE"पूर्ण,
	अणु"Decimation Filter", "Low Latency", "DRE_ENABLE"पूर्ण,
	अणु"Decimation Filter", "Ultra-low Latency", "DRE_ENABLE"पूर्ण,

	अणु"DRE_ENABLE", "Switch", "CH1_DRE_EN"पूर्ण,
	अणु"DRE_ENABLE", "Switch", "CH2_DRE_EN"पूर्ण,
	अणु"DRE_ENABLE", "Switch", "CH3_DRE_EN"पूर्ण,
	अणु"DRE_ENABLE", "Switch", "CH4_DRE_EN"पूर्ण,

	अणु"CH1_DRE_EN", "Switch", "CH1_ADC"पूर्ण,
	अणु"CH2_DRE_EN", "Switch", "CH2_ADC"पूर्ण,
	अणु"CH3_DRE_EN", "Switch", "CH3_ADC"पूर्ण,
	अणु"CH4_DRE_EN", "Switch", "CH4_ADC"पूर्ण,

	/* Mic input */
	अणु"CH1_ADC", शून्य, "MIC_GAIN_CTL_CH1"पूर्ण,
	अणु"CH2_ADC", शून्य, "MIC_GAIN_CTL_CH2"पूर्ण,
	अणु"CH3_ADC", शून्य, "MIC_GAIN_CTL_CH3"पूर्ण,
	अणु"CH4_ADC", शून्य, "MIC_GAIN_CTL_CH4"पूर्ण,

	अणु"MIC_GAIN_CTL_CH1", शून्य, "IN1 Analog Mic Resistor"पूर्ण,
	अणु"MIC_GAIN_CTL_CH1", शून्य, "IN1 Analog Mic Resistor"पूर्ण,
	अणु"MIC_GAIN_CTL_CH2", शून्य, "IN2 Analog Mic Resistor"पूर्ण,
	अणु"MIC_GAIN_CTL_CH2", शून्य, "IN2 Analog Mic Resistor"पूर्ण,
	अणु"MIC_GAIN_CTL_CH3", शून्य, "IN3 Analog Mic Resistor"पूर्ण,
	अणु"MIC_GAIN_CTL_CH3", शून्य, "IN3 Analog Mic Resistor"पूर्ण,
	अणु"MIC_GAIN_CTL_CH4", शून्य, "IN4 Analog Mic Resistor"पूर्ण,
	अणु"MIC_GAIN_CTL_CH4", शून्य, "IN4 Analog Mic Resistor"पूर्ण,

	अणु"IN1 Analog Mic Resistor", "2.5 kOhm", "MIC1P Input Mux"पूर्ण,
	अणु"IN1 Analog Mic Resistor", "10 kOhm", "MIC1P Input Mux"पूर्ण,
	अणु"IN1 Analog Mic Resistor", "20 kOhm", "MIC1P Input Mux"पूर्ण,

	अणु"IN1 Analog Mic Resistor", "2.5 kOhm", "MIC1M Input Mux"पूर्ण,
	अणु"IN1 Analog Mic Resistor", "10 kOhm", "MIC1M Input Mux"पूर्ण,
	अणु"IN1 Analog Mic Resistor", "20 kOhm", "MIC1M Input Mux"पूर्ण,

	अणु"IN2 Analog Mic Resistor", "2.5 kOhm", "MIC2P Input Mux"पूर्ण,
	अणु"IN2 Analog Mic Resistor", "10 kOhm", "MIC2P Input Mux"पूर्ण,
	अणु"IN2 Analog Mic Resistor", "20 kOhm", "MIC2P Input Mux"पूर्ण,

	अणु"IN2 Analog Mic Resistor", "2.5 kOhm", "MIC2M Input Mux"पूर्ण,
	अणु"IN2 Analog Mic Resistor", "10 kOhm", "MIC2M Input Mux"पूर्ण,
	अणु"IN2 Analog Mic Resistor", "20 kOhm", "MIC2M Input Mux"पूर्ण,

	अणु"IN3 Analog Mic Resistor", "2.5 kOhm", "MIC3P Input Mux"पूर्ण,
	अणु"IN3 Analog Mic Resistor", "10 kOhm", "MIC3P Input Mux"पूर्ण,
	अणु"IN3 Analog Mic Resistor", "20 kOhm", "MIC3P Input Mux"पूर्ण,

	अणु"IN3 Analog Mic Resistor", "2.5 kOhm", "MIC3M Input Mux"पूर्ण,
	अणु"IN3 Analog Mic Resistor", "10 kOhm", "MIC3M Input Mux"पूर्ण,
	अणु"IN3 Analog Mic Resistor", "20 kOhm", "MIC3M Input Mux"पूर्ण,

	अणु"IN4 Analog Mic Resistor", "2.5 kOhm", "MIC4P Input Mux"पूर्ण,
	अणु"IN4 Analog Mic Resistor", "10 kOhm", "MIC4P Input Mux"पूर्ण,
	अणु"IN4 Analog Mic Resistor", "20 kOhm", "MIC4P Input Mux"पूर्ण,

	अणु"IN4 Analog Mic Resistor", "2.5 kOhm", "MIC4M Input Mux"पूर्ण,
	अणु"IN4 Analog Mic Resistor", "10 kOhm", "MIC4M Input Mux"पूर्ण,
	अणु"IN4 Analog Mic Resistor", "20 kOhm", "MIC4M Input Mux"पूर्ण,

	अणु"PDM Clk Div Select", "2.8224 MHz", "MIC1P Input Mux"पूर्ण,
	अणु"PDM Clk Div Select", "1.4112 MHz", "MIC1P Input Mux"पूर्ण,
	अणु"PDM Clk Div Select", "705.6 kHz", "MIC1P Input Mux"पूर्ण,
	अणु"PDM Clk Div Select", "5.6448 MHz", "MIC1P Input Mux"पूर्ण,

	अणु"MIC1P Input Mux", शून्य, "CH1_DIG"पूर्ण,
	अणु"MIC1M Input Mux", शून्य, "CH2_DIG"पूर्ण,
	अणु"MIC2P Input Mux", शून्य, "CH3_DIG"पूर्ण,
	अणु"MIC2M Input Mux", शून्य, "CH4_DIG"पूर्ण,
	अणु"MIC3P Input Mux", शून्य, "CH5_DIG"पूर्ण,
	अणु"MIC3M Input Mux", शून्य, "CH6_DIG"पूर्ण,
	अणु"MIC4P Input Mux", शून्य, "CH7_DIG"पूर्ण,
	अणु"MIC4M Input Mux", शून्य, "CH8_DIG"पूर्ण,

	अणु"MIC1 Analog Mux", "Line In", "MIC1P"पूर्ण,
	अणु"MIC2 Analog Mux", "Line In", "MIC2P"पूर्ण,
	अणु"MIC3 Analog Mux", "Line In", "MIC3P"पूर्ण,
	अणु"MIC4 Analog Mux", "Line In", "MIC4P"पूर्ण,

	अणु"MIC1P Input Mux", "Analog", "MIC1P"पूर्ण,
	अणु"MIC1M Input Mux", "Analog", "MIC1M"पूर्ण,
	अणु"MIC2P Input Mux", "Analog", "MIC2P"पूर्ण,
	अणु"MIC2M Input Mux", "Analog", "MIC2M"पूर्ण,
	अणु"MIC3P Input Mux", "Analog", "MIC3P"पूर्ण,
	अणु"MIC3M Input Mux", "Analog", "MIC3M"पूर्ण,
	अणु"MIC4P Input Mux", "Analog", "MIC4P"पूर्ण,
	अणु"MIC4M Input Mux", "Analog", "MIC4M"पूर्ण,

	अणु"MIC1P Input Mux", "Digital", "MIC1P"पूर्ण,
	अणु"MIC1M Input Mux", "Digital", "MIC1M"पूर्ण,
	अणु"MIC2P Input Mux", "Digital", "MIC2P"पूर्ण,
	अणु"MIC2M Input Mux", "Digital", "MIC2M"पूर्ण,
	अणु"MIC3P Input Mux", "Digital", "MIC3P"पूर्ण,
	अणु"MIC3M Input Mux", "Digital", "MIC3M"पूर्ण,
	अणु"MIC4P Input Mux", "Digital", "MIC4P"पूर्ण,
	अणु"MIC4M Input Mux", "Digital", "MIC4M"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adcx140_snd_controls[] = अणु
	SOC_SINGLE_TLV("Analog CH1 Mic Gain Volume", ADCX140_CH1_CFG1, 2, 42, 0,
			adc_tlv),
	SOC_SINGLE_TLV("Analog CH2 Mic Gain Volume", ADCX140_CH2_CFG1, 2, 42, 0,
			adc_tlv),
	SOC_SINGLE_TLV("Analog CH3 Mic Gain Volume", ADCX140_CH3_CFG1, 2, 42, 0,
			adc_tlv),
	SOC_SINGLE_TLV("Analog CH4 Mic Gain Volume", ADCX140_CH4_CFG1, 2, 42, 0,
			adc_tlv),

	SOC_SINGLE_TLV("DRE Threshold", ADCX140_DRE_CFG0, 4, 9, 0,
		       dre_thresh_tlv),
	SOC_SINGLE_TLV("DRE Max Gain", ADCX140_DRE_CFG0, 0, 12, 0,
		       dre_gain_tlv),

	SOC_SINGLE_TLV("AGC Threshold", ADCX140_AGC_CFG0, 4, 15, 0,
		       agc_thresh_tlv),
	SOC_SINGLE_TLV("AGC Max Gain", ADCX140_AGC_CFG0, 0, 13, 0,
		       agc_gain_tlv),

	SOC_SINGLE_TLV("Digital CH1 Out Volume", ADCX140_CH1_CFG2,
			0, 0xff, 0, dig_vol_tlv),
	SOC_SINGLE_TLV("Digital CH2 Out Volume", ADCX140_CH2_CFG2,
			0, 0xff, 0, dig_vol_tlv),
	SOC_SINGLE_TLV("Digital CH3 Out Volume", ADCX140_CH3_CFG2,
			0, 0xff, 0, dig_vol_tlv),
	SOC_SINGLE_TLV("Digital CH4 Out Volume", ADCX140_CH4_CFG2,
			0, 0xff, 0, dig_vol_tlv),
	SOC_SINGLE_TLV("Digital CH5 Out Volume", ADCX140_CH5_CFG2,
			0, 0xff, 0, dig_vol_tlv),
	SOC_SINGLE_TLV("Digital CH6 Out Volume", ADCX140_CH6_CFG2,
			0, 0xff, 0, dig_vol_tlv),
	SOC_SINGLE_TLV("Digital CH7 Out Volume", ADCX140_CH7_CFG2,
			0, 0xff, 0, dig_vol_tlv),
	SOC_SINGLE_TLV("Digital CH8 Out Volume", ADCX140_CH8_CFG2,
			0, 0xff, 0, dig_vol_tlv),
पूर्ण;

अटल पूर्णांक adcx140_reset(काष्ठा adcx140_priv *adcx140)
अणु
	पूर्णांक ret = 0;

	अगर (adcx140->gpio_reset) अणु
		gpiod_direction_output(adcx140->gpio_reset, 0);
		/* 8.4.1: रुको क्रम hw shutकरोwn (25ms) + >= 1ms */
		usleep_range(30000, 100000);
		gpiod_direction_output(adcx140->gpio_reset, 1);
	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(adcx140->regmap, ADCX140_SW_RESET,
				   ADCX140_RESET);
	पूर्ण

	/* 8.4.2: रुको >= 10 ms after entering sleep mode. */
	usleep_range(10000, 100000);

	वापस ret;
पूर्ण

अटल व्योम adcx140_pwr_ctrl(काष्ठा adcx140_priv *adcx140, bool घातer_state)
अणु
	पूर्णांक pwr_ctrl = 0;

	अगर (घातer_state)
		pwr_ctrl = ADCX140_PWR_CFG_ADC_PDZ | ADCX140_PWR_CFG_PLL_PDZ;

	अगर (adcx140->micbias_vg && घातer_state)
		pwr_ctrl |= ADCX140_PWR_CFG_BIAS_PDZ;

	regmap_update_bits(adcx140->regmap, ADCX140_PWR_CFG,
			   ADCX140_PWR_CTRL_MSK, pwr_ctrl);
पूर्ण

अटल पूर्णांक adcx140_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा adcx140_priv *adcx140 = snd_soc_component_get_drvdata(component);
	u8 data = 0;

	चयन (params_width(params)) अणु
	हाल 16:
		data = ADCX140_16_BIT_WORD;
		अवरोध;
	हाल 20:
		data = ADCX140_20_BIT_WORD;
		अवरोध;
	हाल 24:
		data = ADCX140_24_BIT_WORD;
		अवरोध;
	हाल 32:
		data = ADCX140_32_BIT_WORD;
		अवरोध;
	शेष:
		dev_err(component->dev, "%s: Unsupported width %d\n",
			__func__, params_width(params));
		वापस -EINVAL;
	पूर्ण

	adcx140_pwr_ctrl(adcx140, false);

	snd_soc_component_update_bits(component, ADCX140_ASI_CFG0,
			    ADCX140_WORD_LEN_MSK, data);

	adcx140_pwr_ctrl(adcx140, true);

	वापस 0;
पूर्ण

अटल पूर्णांक adcx140_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			       अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा adcx140_priv *adcx140 = snd_soc_component_get_drvdata(component);
	u8 अगरace_reg1 = 0;
	u8 अगरace_reg2 = 0;
	पूर्णांक offset = 0;
	bool inverted_bclk = false;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगरace_reg2 |= ADCX140_BCLK_FSYNC_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
	हाल SND_SOC_DAIFMT_CBM_CFS:
	शेष:
		dev_err(component->dev, "Invalid DAI master/slave interface\n");
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace_reg1 |= ADCX140_I2S_MODE_BIT;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace_reg1 |= ADCX140_LEFT_JUST_BIT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		offset = 1;
		inverted_bclk = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		inverted_bclk = true;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI interface format\n");
		वापस -EINVAL;
	पूर्ण

	/* संकेत polarity */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_NF:
	हाल SND_SOC_DAIFMT_IB_IF:
		inverted_bclk = !inverted_bclk;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगरace_reg1 |= ADCX140_FSYNCINV_BIT;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI clock signal polarity\n");
		वापस -EINVAL;
	पूर्ण

	अगर (inverted_bclk)
		अगरace_reg1 |= ADCX140_BCLKINV_BIT;

	adcx140->dai_fmt = fmt & SND_SOC_DAIFMT_FORMAT_MASK;

	adcx140_pwr_ctrl(adcx140, false);

	snd_soc_component_update_bits(component, ADCX140_ASI_CFG0,
				      ADCX140_FSYNCINV_BIT |
				      ADCX140_BCLKINV_BIT |
				      ADCX140_ASI_FORMAT_MSK,
				      अगरace_reg1);
	snd_soc_component_update_bits(component, ADCX140_MST_CFG0,
				      ADCX140_BCLK_FSYNC_MASTER, अगरace_reg2);

	/* Configure data offset */
	snd_soc_component_update_bits(component, ADCX140_ASI_CFG1,
				      ADCX140_TX_OFFSET_MASK, offset);

	adcx140_pwr_ctrl(adcx140, true);

	वापस 0;
पूर्ण

अटल पूर्णांक adcx140_set_dai_tdm_slot(काष्ठा snd_soc_dai *codec_dai,
				  अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				  पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा adcx140_priv *adcx140 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक lsb;

	/* TDM based on DSP mode requires slots to be adjacent */
	lsb = __ffs(tx_mask);
	अगर ((lsb + 1) != __fls(tx_mask)) अणु
		dev_err(component->dev, "Invalid mask, slots must be adjacent\n");
		वापस -EINVAL;
	पूर्ण

	चयन (slot_width) अणु
	हाल 16:
	हाल 20:
	हाल 24:
	हाल 32:
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported slot width %d\n", slot_width);
		वापस -EINVAL;
	पूर्ण

	adcx140->tdm_delay = lsb;
	adcx140->slot_width = slot_width;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops adcx140_dai_ops = अणु
	.hw_params	= adcx140_hw_params,
	.set_fmt	= adcx140_set_dai_fmt,
	.set_tdm_slot	= adcx140_set_dai_tdm_slot,
पूर्ण;

अटल पूर्णांक adcx140_configure_gpo(काष्ठा adcx140_priv *adcx140)
अणु
	u32 gpo_outमाला_दो[ADCX140_NUM_GPOS];
	u32 gpo_output_val = 0;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ADCX140_NUM_GPOS; i++) अणु
		ret = device_property_पढ़ो_u32_array(adcx140->dev,
						     gpo_config_names[i],
						     gpo_outमाला_दो,
						     ADCX140_NUM_GPO_CFGS);
		अगर (ret)
			जारी;

		अगर (gpo_outमाला_दो[0] > ADCX140_GPO_CFG_MAX) अणु
			dev_err(adcx140->dev, "GPO%d config out of range\n", i + 1);
			वापस -EINVAL;
		पूर्ण

		अगर (gpo_outमाला_दो[1] > ADCX140_GPO_DRV_MAX) अणु
			dev_err(adcx140->dev, "GPO%d drive out of range\n", i + 1);
			वापस -EINVAL;
		पूर्ण

		gpo_output_val = gpo_outमाला_दो[0] << ADCX140_GPO_SHIFT |
				 gpo_outमाला_दो[1];
		ret = regmap_ग_लिखो(adcx140->regmap, ADCX140_GPO_CFG0 + i,
				   gpo_output_val);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक adcx140_configure_gpio(काष्ठा adcx140_priv *adcx140)
अणु
	पूर्णांक gpio_count = 0;
	u32 gpio_outमाला_दो[ADCX140_NUM_GPIO_CFGS];
	u32 gpio_output_val = 0;
	पूर्णांक ret;

	gpio_count = device_property_count_u32(adcx140->dev,
			"ti,gpio-config");
	अगर (gpio_count == 0)
		वापस 0;

	अगर (gpio_count != ADCX140_NUM_GPIO_CFGS)
		वापस -EINVAL;

	ret = device_property_पढ़ो_u32_array(adcx140->dev, "ti,gpio-config",
			gpio_outमाला_दो, gpio_count);
	अगर (ret)
		वापस ret;

	अगर (gpio_outमाला_दो[0] > ADCX140_GPIO_CFG_MAX) अणु
		dev_err(adcx140->dev, "GPIO config out of range\n");
		वापस -EINVAL;
	पूर्ण

	अगर (gpio_outमाला_दो[1] > ADCX140_GPIO_DRV_MAX) अणु
		dev_err(adcx140->dev, "GPIO drive out of range\n");
		वापस -EINVAL;
	पूर्ण

	gpio_output_val = gpio_outमाला_दो[0] << ADCX140_GPIO_SHIFT
		| gpio_outमाला_दो[1];

	वापस regmap_ग_लिखो(adcx140->regmap, ADCX140_GPIO_CFG0, gpio_output_val);
पूर्ण

अटल पूर्णांक adcx140_codec_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा adcx140_priv *adcx140 = snd_soc_component_get_drvdata(component);
	पूर्णांक sleep_cfg_val = ADCX140_WAKE_DEV;
	u32 bias_source;
	u32 vref_source;
	u8 bias_cfg;
	पूर्णांक pdm_count;
	u32 pdm_edges[ADCX140_NUM_PDM_EDGES];
	u32 pdm_edge_val = 0;
	पूर्णांक gpi_count;
	u32 gpi_inमाला_दो[ADCX140_NUM_GPI_PINS];
	u32 gpi_input_val = 0;
	पूर्णांक i;
	पूर्णांक ret;
	bool tx_high_z;

	ret = device_property_पढ़ो_u32(adcx140->dev, "ti,mic-bias-source",
				      &bias_source);
	अगर (ret || bias_source > ADCX140_MIC_BIAS_VAL_AVDD) अणु
		bias_source = ADCX140_MIC_BIAS_VAL_VREF;
		adcx140->micbias_vg = false;
	पूर्ण अन्यथा अणु
		adcx140->micbias_vg = true;
	पूर्ण

	ret = device_property_पढ़ो_u32(adcx140->dev, "ti,vref-source",
				      &vref_source);
	अगर (ret)
		vref_source = ADCX140_MIC_BIAS_VREF_275V;

	अगर (vref_source > ADCX140_MIC_BIAS_VREF_1375V) अणु
		dev_err(adcx140->dev, "Mic Bias source value is invalid\n");
		वापस -EINVAL;
	पूर्ण

	bias_cfg = bias_source << ADCX140_MIC_BIAS_SHIFT | vref_source;

	ret = adcx140_reset(adcx140);
	अगर (ret)
		जाओ out;

	अगर (adcx140->supply_areg == शून्य)
		sleep_cfg_val |= ADCX140_AREG_INTERNAL;

	ret = regmap_ग_लिखो(adcx140->regmap, ADCX140_SLEEP_CFG, sleep_cfg_val);
	अगर (ret) अणु
		dev_err(adcx140->dev, "setting sleep config failed %d\n", ret);
		जाओ out;
	पूर्ण

	/* 8.4.3: Wait >= 1ms after entering active mode. */
	usleep_range(1000, 100000);

	pdm_count = device_property_count_u32(adcx140->dev,
					      "ti,pdm-edge-select");
	अगर (pdm_count <= ADCX140_NUM_PDM_EDGES && pdm_count > 0) अणु
		ret = device_property_पढ़ो_u32_array(adcx140->dev,
						     "ti,pdm-edge-select",
						     pdm_edges, pdm_count);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < pdm_count; i++)
			pdm_edge_val |= pdm_edges[i] << (ADCX140_PDM_EDGE_SHIFT - i);

		ret = regmap_ग_लिखो(adcx140->regmap, ADCX140_PDM_CFG,
				   pdm_edge_val);
		अगर (ret)
			वापस ret;
	पूर्ण

	gpi_count = device_property_count_u32(adcx140->dev, "ti,gpi-config");
	अगर (gpi_count <= ADCX140_NUM_GPI_PINS && gpi_count > 0) अणु
		ret = device_property_पढ़ो_u32_array(adcx140->dev,
						     "ti,gpi-config",
						     gpi_inमाला_दो, gpi_count);
		अगर (ret)
			वापस ret;

		gpi_input_val = gpi_inमाला_दो[ADCX140_GPI1_INDEX] << ADCX140_GPI_SHIFT |
				gpi_inमाला_दो[ADCX140_GPI2_INDEX];

		ret = regmap_ग_लिखो(adcx140->regmap, ADCX140_GPI_CFG0,
				   gpi_input_val);
		अगर (ret)
			वापस ret;

		gpi_input_val = gpi_inमाला_दो[ADCX140_GPI3_INDEX] << ADCX140_GPI_SHIFT |
				gpi_inमाला_दो[ADCX140_GPI4_INDEX];

		ret = regmap_ग_लिखो(adcx140->regmap, ADCX140_GPI_CFG1,
				   gpi_input_val);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = adcx140_configure_gpio(adcx140);
	अगर (ret)
		वापस ret;

	ret = adcx140_configure_gpo(adcx140);
	अगर (ret)
		जाओ out;

	ret = regmap_update_bits(adcx140->regmap, ADCX140_BIAS_CFG,
				ADCX140_MIC_BIAS_VAL_MSK |
				ADCX140_MIC_BIAS_VREF_MSK, bias_cfg);
	अगर (ret)
		dev_err(adcx140->dev, "setting MIC bias failed %d\n", ret);

	tx_high_z = device_property_पढ़ो_bool(adcx140->dev, "ti,asi-tx-drive");
	अगर (tx_high_z) अणु
		ret = regmap_update_bits(adcx140->regmap, ADCX140_ASI_CFG0,
				 ADCX140_TX_FILL, ADCX140_TX_FILL);
		अगर (ret) अणु
			dev_err(adcx140->dev, "Setting Tx drive failed %d\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	adcx140_pwr_ctrl(adcx140, true);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक adcx140_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा adcx140_priv *adcx140 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
	हाल SND_SOC_BIAS_STANDBY:
		adcx140_pwr_ctrl(adcx140, true);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		adcx140_pwr_ctrl(adcx140, false);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_driver_adcx140 = अणु
	.probe			= adcx140_codec_probe,
	.set_bias_level		= adcx140_set_bias_level,
	.controls		= adcx140_snd_controls,
	.num_controls		= ARRAY_SIZE(adcx140_snd_controls),
	.dapm_widमाला_लो		= adcx140_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(adcx140_dapm_widमाला_लो),
	.dapm_routes		= adcx140_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(adcx140_audio_map),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 0,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver adcx140_dai_driver[] = अणु
	अणु
		.name = "tlv320adcx140-codec",
		.capture = अणु
			.stream_name	 = "Capture",
			.channels_min	 = 2,
			.channels_max	 = ADCX140_MAX_CHANNELS,
			.rates		 = ADCX140_RATES,
			.क्रमmats	 = ADCX140_FORMATS,
		पूर्ण,
		.ops = &adcx140_dai_ops,
		.symmetric_rate = 1,
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tlv320adcx140_of_match[] = अणु
	अणु .compatible = "ti,tlv320adc3140" पूर्ण,
	अणु .compatible = "ti,tlv320adc5140" पूर्ण,
	अणु .compatible = "ti,tlv320adc6140" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tlv320adcx140_of_match);
#पूर्ण_अगर

अटल पूर्णांक adcx140_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adcx140_priv *adcx140;
	पूर्णांक ret;

	adcx140 = devm_kzalloc(&i2c->dev, माप(*adcx140), GFP_KERNEL);
	अगर (!adcx140)
		वापस -ENOMEM;

	adcx140->dev = &i2c->dev;

	adcx140->gpio_reset = devm_gpiod_get_optional(adcx140->dev,
						      "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(adcx140->gpio_reset))
		dev_info(&i2c->dev, "Reset GPIO not defined\n");

	adcx140->supply_areg = devm_regulator_get_optional(adcx140->dev,
							   "areg");
	अगर (IS_ERR(adcx140->supply_areg)) अणु
		अगर (PTR_ERR(adcx140->supply_areg) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		adcx140->supply_areg = शून्य;
	पूर्ण अन्यथा अणु
		ret = regulator_enable(adcx140->supply_areg);
		अगर (ret) अणु
			dev_err(adcx140->dev, "Failed to enable areg\n");
			वापस ret;
		पूर्ण
	पूर्ण

	adcx140->regmap = devm_regmap_init_i2c(i2c, &adcx140_i2c_regmap);
	अगर (IS_ERR(adcx140->regmap)) अणु
		ret = PTR_ERR(adcx140->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, adcx140);

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
					       &soc_codec_driver_adcx140,
					       adcx140_dai_driver, 1);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adcx140_i2c_id[] = अणु
	अणु "tlv320adc3140", 0 पूर्ण,
	अणु "tlv320adc5140", 1 पूर्ण,
	अणु "tlv320adc6140", 2 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adcx140_i2c_id);

अटल काष्ठा i2c_driver adcx140_i2c_driver = अणु
	.driver = अणु
		.name	= "tlv320adcx140-codec",
		.of_match_table = of_match_ptr(tlv320adcx140_of_match),
	पूर्ण,
	.probe		= adcx140_i2c_probe,
	.id_table	= adcx140_i2c_id,
पूर्ण;
module_i2c_driver(adcx140_i2c_driver);

MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_DESCRIPTION("ASoC TLV320ADCX140 CODEC Driver");
MODULE_LICENSE("GPL v2");
