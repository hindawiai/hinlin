<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * es8316.c -- es8316 ALSA SoC audio driver
 * Copyright Everest Semiconductor Co.,Ltd
 *
 * Authors: David Yang <yangxiaohua@everest-semi.com>,
 *          Daniel Drake <drake@endlessm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>
#समावेश <sound/jack.h>
#समावेश "es8316.h"

/* In slave mode at single speed, the codec is करोcumented as accepting 5
 * MCLK/LRCK ratios, but we also add ratio 400, which is commonly used on
 * Intel Cherry Trail platक्रमms (19.2MHz MCLK, 48kHz LRCK).
 */
#घोषणा NR_SUPPORTED_MCLK_LRCK_RATIOS 6
अटल स्थिर अचिन्हित पूर्णांक supported_mclk_lrck_ratios[] = अणु
	256, 384, 400, 512, 768, 1024
पूर्ण;

काष्ठा es8316_priv अणु
	काष्ठा mutex lock;
	काष्ठा clk *mclk;
	काष्ठा regmap *regmap;
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_jack *jack;
	पूर्णांक irq;
	अचिन्हित पूर्णांक sysclk;
	अचिन्हित पूर्णांक allowed_rates[NR_SUPPORTED_MCLK_LRCK_RATIOS];
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list sysclk_स्थिरraपूर्णांकs;
	bool jd_inverted;
पूर्ण;

/*
 * ES8316 controls
 */
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_SCALE(dac_vol_tlv, -9600, 50, 1);
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_SCALE(adc_vol_tlv, -9600, 50, 1);
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_SCALE(alc_max_gain_tlv, -650, 150, 0);
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_SCALE(alc_min_gain_tlv, -1200, 150, 0);
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_SCALE(alc_target_tlv, -1650, 150, 0);
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_RANGE(hpmixer_gain_tlv,
	0, 4, TLV_DB_SCALE_ITEM(-1200, 150, 0),
	8, 11, TLV_DB_SCALE_ITEM(-450, 150, 0),
);

अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_RANGE(adc_pga_gain_tlv,
	0, 0, TLV_DB_SCALE_ITEM(-350, 0, 0),
	1, 1, TLV_DB_SCALE_ITEM(0, 0, 0),
	2, 2, TLV_DB_SCALE_ITEM(250, 0, 0),
	3, 3, TLV_DB_SCALE_ITEM(450, 0, 0),
	4, 7, TLV_DB_SCALE_ITEM(700, 300, 0),
	8, 10, TLV_DB_SCALE_ITEM(1800, 300, 0),
);

अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_RANGE(hpout_vol_tlv,
	0, 0, TLV_DB_SCALE_ITEM(-4800, 0, 0),
	1, 3, TLV_DB_SCALE_ITEM(-2400, 1200, 0),
);

अटल स्थिर अक्षर * स्थिर ng_type_txt[] =
	अणु "Constant PGA Gain", "Mute ADC Output" पूर्ण;
अटल स्थिर काष्ठा soc_क्रमागत ng_type =
	SOC_ENUM_SINGLE(ES8316_ADC_ALC_NG, 6, 2, ng_type_txt);

अटल स्थिर अक्षर * स्थिर adcpol_txt[] = अणु "Normal", "Invert" पूर्ण;
अटल स्थिर काष्ठा soc_क्रमागत adcpol =
	SOC_ENUM_SINGLE(ES8316_ADC_MUTE, 1, 2, adcpol_txt);
अटल स्थिर अक्षर *स्थिर dacpol_txt[] =
	अणु "Normal", "R Invert", "L Invert", "L + R Invert" पूर्ण;
अटल स्थिर काष्ठा soc_क्रमागत dacpol =
	SOC_ENUM_SINGLE(ES8316_DAC_SET1, 0, 4, dacpol_txt);

अटल स्थिर काष्ठा snd_kcontrol_new es8316_snd_controls[] = अणु
	SOC_DOUBLE_TLV("Headphone Playback Volume", ES8316_CPHP_ICAL_VOL,
		       4, 0, 3, 1, hpout_vol_tlv),
	SOC_DOUBLE_TLV("Headphone Mixer Volume", ES8316_HPMIX_VOL,
		       4, 0, 11, 0, hpmixer_gain_tlv),

	SOC_ENUM("Playback Polarity", dacpol),
	SOC_DOUBLE_R_TLV("DAC Playback Volume", ES8316_DAC_VOLL,
			 ES8316_DAC_VOLR, 0, 0xc0, 1, dac_vol_tlv),
	SOC_SINGLE("DAC Soft Ramp Switch", ES8316_DAC_SET1, 4, 1, 1),
	SOC_SINGLE("DAC Soft Ramp Rate", ES8316_DAC_SET1, 2, 4, 0),
	SOC_SINGLE("DAC Notch Filter Switch", ES8316_DAC_SET2, 6, 1, 0),
	SOC_SINGLE("DAC Double Fs Switch", ES8316_DAC_SET2, 7, 1, 0),
	SOC_SINGLE("DAC Stereo Enhancement", ES8316_DAC_SET3, 0, 7, 0),
	SOC_SINGLE("DAC Mono Mix Switch", ES8316_DAC_SET3, 3, 1, 0),

	SOC_ENUM("Capture Polarity", adcpol),
	SOC_SINGLE("Mic Boost Switch", ES8316_ADC_D2SEPGA, 0, 1, 0),
	SOC_SINGLE_TLV("ADC Capture Volume", ES8316_ADC_VOLUME,
		       0, 0xc0, 1, adc_vol_tlv),
	SOC_SINGLE_TLV("ADC PGA Gain Volume", ES8316_ADC_PGAGAIN,
		       4, 10, 0, adc_pga_gain_tlv),
	SOC_SINGLE("ADC Soft Ramp Switch", ES8316_ADC_MUTE, 4, 1, 0),
	SOC_SINGLE("ADC Double Fs Switch", ES8316_ADC_DMIC, 4, 1, 0),

	SOC_SINGLE("ALC Capture Switch", ES8316_ADC_ALC1, 6, 1, 0),
	SOC_SINGLE_TLV("ALC Capture Max Volume", ES8316_ADC_ALC1, 0, 28, 0,
		       alc_max_gain_tlv),
	SOC_SINGLE_TLV("ALC Capture Min Volume", ES8316_ADC_ALC2, 0, 28, 0,
		       alc_min_gain_tlv),
	SOC_SINGLE_TLV("ALC Capture Target Volume", ES8316_ADC_ALC3, 4, 10, 0,
		       alc_target_tlv),
	SOC_SINGLE("ALC Capture Hold Time", ES8316_ADC_ALC3, 0, 10, 0),
	SOC_SINGLE("ALC Capture Decay Time", ES8316_ADC_ALC4, 4, 10, 0),
	SOC_SINGLE("ALC Capture Attack Time", ES8316_ADC_ALC4, 0, 10, 0),
	SOC_SINGLE("ALC Capture Noise Gate Switch", ES8316_ADC_ALC_NG,
		   5, 1, 0),
	SOC_SINGLE("ALC Capture Noise Gate Threshold", ES8316_ADC_ALC_NG,
		   0, 31, 0),
	SOC_ENUM("ALC Capture Noise Gate Type", ng_type),
पूर्ण;

/* Analog Input Mux */
अटल स्थिर अक्षर * स्थिर es8316_analog_in_txt[] = अणु
		"lin1-rin1",
		"lin2-rin2",
		"lin1-rin1 with 20db Boost",
		"lin2-rin2 with 20db Boost"
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक es8316_analog_in_values[] = अणु 0, 1, 2, 3 पूर्ण;
अटल स्थिर काष्ठा soc_क्रमागत es8316_analog_input_क्रमागत =
	SOC_VALUE_ENUM_SINGLE(ES8316_ADC_PDN_LINSEL, 4, 3,
			      ARRAY_SIZE(es8316_analog_in_txt),
			      es8316_analog_in_txt,
			      es8316_analog_in_values);
अटल स्थिर काष्ठा snd_kcontrol_new es8316_analog_in_mux_controls =
	SOC_DAPM_ENUM("Route", es8316_analog_input_क्रमागत);

अटल स्थिर अक्षर * स्थिर es8316_dmic_txt[] = अणु
		"dmic disable",
		"dmic data at high level",
		"dmic data at low level",
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक es8316_dmic_values[] = अणु 0, 1, 2 पूर्ण;
अटल स्थिर काष्ठा soc_क्रमागत es8316_dmic_src_क्रमागत =
	SOC_VALUE_ENUM_SINGLE(ES8316_ADC_DMIC, 0, 3,
			      ARRAY_SIZE(es8316_dmic_txt),
			      es8316_dmic_txt,
			      es8316_dmic_values);
अटल स्थिर काष्ठा snd_kcontrol_new es8316_dmic_src_controls =
	SOC_DAPM_ENUM("Route", es8316_dmic_src_क्रमागत);

/* hp mixer mux */
अटल स्थिर अक्षर * स्थिर es8316_hpmux_texts[] = अणु
	"lin1-rin1",
	"lin2-rin2",
	"lin-rin with Boost",
	"lin-rin with Boost and PGA"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(es8316_left_hpmux_क्रमागत, ES8316_HPMIX_SEL,
	4, es8316_hpmux_texts);

अटल स्थिर काष्ठा snd_kcontrol_new es8316_left_hpmux_controls =
	SOC_DAPM_ENUM("Route", es8316_left_hpmux_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(es8316_right_hpmux_क्रमागत, ES8316_HPMIX_SEL,
	0, es8316_hpmux_texts);

अटल स्थिर काष्ठा snd_kcontrol_new es8316_right_hpmux_controls =
	SOC_DAPM_ENUM("Route", es8316_right_hpmux_क्रमागत);

/* headphone Output Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new es8316_out_left_mix[] = अणु
	SOC_DAPM_SINGLE("LLIN Switch", ES8316_HPMIX_SWITCH, 6, 1, 0),
	SOC_DAPM_SINGLE("Left DAC Switch", ES8316_HPMIX_SWITCH, 7, 1, 0),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new es8316_out_right_mix[] = अणु
	SOC_DAPM_SINGLE("RLIN Switch", ES8316_HPMIX_SWITCH, 2, 1, 0),
	SOC_DAPM_SINGLE("Right DAC Switch", ES8316_HPMIX_SWITCH, 3, 1, 0),
पूर्ण;

/* DAC data source mux */
अटल स्थिर अक्षर * स्थिर es8316_dacsrc_texts[] = अणु
	"LDATA TO LDAC, RDATA TO RDAC",
	"LDATA TO LDAC, LDATA TO RDAC",
	"RDATA TO LDAC, RDATA TO RDAC",
	"RDATA TO LDAC, LDATA TO RDAC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(es8316_dacsrc_mux_क्रमागत, ES8316_DAC_SET1,
	6, es8316_dacsrc_texts);

अटल स्थिर काष्ठा snd_kcontrol_new es8316_dacsrc_mux_controls =
	SOC_DAPM_ENUM("Route", es8316_dacsrc_mux_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget es8316_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("Bias", ES8316_SYS_PDN, 3, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Analog power", ES8316_SYS_PDN, 4, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Mic Bias", ES8316_SYS_PDN, 5, 1, शून्य, 0),

	SND_SOC_DAPM_INPUT("DMIC"),
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),

	/* Input Mux */
	SND_SOC_DAPM_MUX("Differential Mux", SND_SOC_NOPM, 0, 0,
			 &es8316_analog_in_mux_controls),

	SND_SOC_DAPM_SUPPLY("ADC Vref", ES8316_SYS_PDN, 1, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC bias", ES8316_SYS_PDN, 2, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC Clock", ES8316_CLKMGR_CLKSW, 3, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Line input PGA", ES8316_ADC_PDN_LINSEL,
			 7, 1, शून्य, 0),
	SND_SOC_DAPM_ADC("Mono ADC", शून्य, ES8316_ADC_PDN_LINSEL, 6, 1),
	SND_SOC_DAPM_MUX("Digital Mic Mux", SND_SOC_NOPM, 0, 0,
			 &es8316_dmic_src_controls),

	/* Digital Interface */
	SND_SOC_DAPM_AIF_OUT("I2S OUT", "I2S1 Capture",  1,
			     ES8316_SERDATA_ADC, 6, 1),
	SND_SOC_DAPM_AIF_IN("I2S IN", "I2S1 Playback", 0,
			    SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MUX("DAC Source Mux", SND_SOC_NOPM, 0, 0,
			 &es8316_dacsrc_mux_controls),

	SND_SOC_DAPM_SUPPLY("DAC Vref", ES8316_SYS_PDN, 0, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC Clock", ES8316_CLKMGR_CLKSW, 2, 0, शून्य, 0),
	SND_SOC_DAPM_DAC("Right DAC", शून्य, ES8316_DAC_PDN, 0, 1),
	SND_SOC_DAPM_DAC("Left DAC", शून्य, ES8316_DAC_PDN, 4, 1),

	/* Headphone Output Side */
	SND_SOC_DAPM_MUX("Left Headphone Mux", SND_SOC_NOPM, 0, 0,
			 &es8316_left_hpmux_controls),
	SND_SOC_DAPM_MUX("Right Headphone Mux", SND_SOC_NOPM, 0, 0,
			 &es8316_right_hpmux_controls),
	SND_SOC_DAPM_MIXER("Left Headphone Mixer", ES8316_HPMIX_PDN,
			   5, 1, &es8316_out_left_mix[0],
			   ARRAY_SIZE(es8316_out_left_mix)),
	SND_SOC_DAPM_MIXER("Right Headphone Mixer", ES8316_HPMIX_PDN,
			   1, 1, &es8316_out_right_mix[0],
			   ARRAY_SIZE(es8316_out_right_mix)),
	SND_SOC_DAPM_PGA("Left Headphone Mixer Out", ES8316_HPMIX_PDN,
			 4, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Headphone Mixer Out", ES8316_HPMIX_PDN,
			 0, 1, शून्य, 0),

	SND_SOC_DAPM_OUT_DRV("Left Headphone Charge Pump", ES8316_CPHP_OUTEN,
			     6, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("Right Headphone Charge Pump", ES8316_CPHP_OUTEN,
			     2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Headphone Charge Pump", ES8316_CPHP_PDN2,
			    5, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Headphone Charge Pump Clock", ES8316_CLKMGR_CLKSW,
			    4, 0, शून्य, 0),

	SND_SOC_DAPM_OUT_DRV("Left Headphone Driver", ES8316_CPHP_OUTEN,
			     5, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("Right Headphone Driver", ES8316_CPHP_OUTEN,
			     1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Headphone Out", ES8316_CPHP_PDN1, 2, 1, शून्य, 0),

	/* pdn_Lical and pdn_Rical bits are करोcumented as Reserved, but must
	 * be explicitly unset in order to enable HP output
	 */
	SND_SOC_DAPM_SUPPLY("Left Headphone ical", ES8316_CPHP_ICAL_VOL,
			    7, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Right Headphone ical", ES8316_CPHP_ICAL_VOL,
			    3, 1, शून्य, 0),

	SND_SOC_DAPM_OUTPUT("HPOL"),
	SND_SOC_DAPM_OUTPUT("HPOR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route es8316_dapm_routes[] = अणु
	/* Recording */
	अणु"MIC1", शून्य, "Mic Bias"पूर्ण,
	अणु"MIC2", शून्य, "Mic Bias"पूर्ण,
	अणु"MIC1", शून्य, "Bias"पूर्ण,
	अणु"MIC2", शून्य, "Bias"पूर्ण,
	अणु"MIC1", शून्य, "Analog power"पूर्ण,
	अणु"MIC2", शून्य, "Analog power"पूर्ण,

	अणु"Differential Mux", "lin1-rin1", "MIC1"पूर्ण,
	अणु"Differential Mux", "lin2-rin2", "MIC2"पूर्ण,
	अणु"Line input PGA", शून्य, "Differential Mux"पूर्ण,

	अणु"Mono ADC", शून्य, "ADC Clock"पूर्ण,
	अणु"Mono ADC", शून्य, "ADC Vref"पूर्ण,
	अणु"Mono ADC", शून्य, "ADC bias"पूर्ण,
	अणु"Mono ADC", शून्य, "Line input PGA"पूर्ण,

	/* It's not clear why, but to aव्योम recording only silence,
	 * the DAC घड़ी must be running क्रम the ADC to work.
	 */
	अणु"Mono ADC", शून्य, "DAC Clock"पूर्ण,

	अणु"Digital Mic Mux", "dmic disable", "Mono ADC"पूर्ण,

	अणु"I2S OUT", शून्य, "Digital Mic Mux"पूर्ण,

	/* Playback */
	अणु"DAC Source Mux", "LDATA TO LDAC, RDATA TO RDAC", "I2S IN"पूर्ण,

	अणु"Left DAC", शून्य, "DAC Clock"पूर्ण,
	अणु"Right DAC", शून्य, "DAC Clock"पूर्ण,

	अणु"Left DAC", शून्य, "DAC Vref"पूर्ण,
	अणु"Right DAC", शून्य, "DAC Vref"पूर्ण,

	अणु"Left DAC", शून्य, "DAC Source Mux"पूर्ण,
	अणु"Right DAC", शून्य, "DAC Source Mux"पूर्ण,

	अणु"Left Headphone Mux", "lin-rin with Boost and PGA", "Line input PGA"पूर्ण,
	अणु"Right Headphone Mux", "lin-rin with Boost and PGA", "Line input PGA"पूर्ण,

	अणु"Left Headphone Mixer", "LLIN Switch", "Left Headphone Mux"पूर्ण,
	अणु"Left Headphone Mixer", "Left DAC Switch", "Left DAC"पूर्ण,

	अणु"Right Headphone Mixer", "RLIN Switch", "Right Headphone Mux"पूर्ण,
	अणु"Right Headphone Mixer", "Right DAC Switch", "Right DAC"पूर्ण,

	अणु"Left Headphone Mixer Out", शून्य, "Left Headphone Mixer"पूर्ण,
	अणु"Right Headphone Mixer Out", शून्य, "Right Headphone Mixer"पूर्ण,

	अणु"Left Headphone Charge Pump", शून्य, "Left Headphone Mixer Out"पूर्ण,
	अणु"Right Headphone Charge Pump", शून्य, "Right Headphone Mixer Out"पूर्ण,

	अणु"Left Headphone Charge Pump", शून्य, "Headphone Charge Pump"पूर्ण,
	अणु"Right Headphone Charge Pump", शून्य, "Headphone Charge Pump"पूर्ण,

	अणु"Left Headphone Charge Pump", शून्य, "Headphone Charge Pump Clock"पूर्ण,
	अणु"Right Headphone Charge Pump", शून्य, "Headphone Charge Pump Clock"पूर्ण,

	अणु"Left Headphone Driver", शून्य, "Left Headphone Charge Pump"पूर्ण,
	अणु"Right Headphone Driver", शून्य, "Right Headphone Charge Pump"पूर्ण,

	अणु"HPOL", शून्य, "Left Headphone Driver"पूर्ण,
	अणु"HPOR", शून्य, "Right Headphone Driver"पूर्ण,

	अणु"HPOL", शून्य, "Left Headphone ical"पूर्ण,
	अणु"HPOR", शून्य, "Right Headphone ical"पूर्ण,

	अणु"Headphone Out", शून्य, "Bias"पूर्ण,
	अणु"Headphone Out", शून्य, "Analog power"पूर्ण,
	अणु"HPOL", शून्य, "Headphone Out"पूर्ण,
	अणु"HPOR", शून्य, "Headphone Out"पूर्ण,
पूर्ण;

अटल पूर्णांक es8316_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा es8316_priv *es8316 = snd_soc_component_get_drvdata(component);
	पूर्णांक i, ret;
	पूर्णांक count = 0;

	es8316->sysclk = freq;

	अगर (freq == 0) अणु
		es8316->sysclk_स्थिरraपूर्णांकs.list = शून्य;
		es8316->sysclk_स्थिरraपूर्णांकs.count = 0;

		वापस 0;
	पूर्ण

	ret = clk_set_rate(es8316->mclk, freq);
	अगर (ret)
		वापस ret;

	/* Limit supported sample rates to ones that can be स्वतःdetected
	 * by the codec running in slave mode.
	 */
	क्रम (i = 0; i < NR_SUPPORTED_MCLK_LRCK_RATIOS; i++) अणु
		स्थिर अचिन्हित पूर्णांक ratio = supported_mclk_lrck_ratios[i];

		अगर (freq % ratio == 0)
			es8316->allowed_rates[count++] = freq / ratio;
	पूर्ण

	es8316->sysclk_स्थिरraपूर्णांकs.list = es8316->allowed_rates;
	es8316->sysclk_स्थिरraपूर्णांकs.count = count;

	वापस 0;
पूर्ण

अटल पूर्णांक es8316_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			      अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u8 serdata1 = 0;
	u8 serdata2 = 0;
	u8 clksw;
	u8 mask;

	अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS) अणु
		dev_err(component->dev, "Codec driver only supports slave mode\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((fmt & SND_SOC_DAIFMT_FORMAT_MASK) != SND_SOC_DAIFMT_I2S) अणु
		dev_err(component->dev, "Codec driver only supports I2S format\n");
		वापस -EINVAL;
	पूर्ण

	/* Clock inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		serdata1 |= ES8316_SERDATA1_BCLK_INV;
		serdata2 |= ES8316_SERDATA2_ADCLRP;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		serdata1 |= ES8316_SERDATA1_BCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		serdata2 |= ES8316_SERDATA2_ADCLRP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mask = ES8316_SERDATA1_MASTER | ES8316_SERDATA1_BCLK_INV;
	snd_soc_component_update_bits(component, ES8316_SERDATA1, mask, serdata1);

	mask = ES8316_SERDATA2_FMT_MASK | ES8316_SERDATA2_ADCLRP;
	snd_soc_component_update_bits(component, ES8316_SERDATA_ADC, mask, serdata2);
	snd_soc_component_update_bits(component, ES8316_SERDATA_DAC, mask, serdata2);

	/* Enable BCLK and MCLK inमाला_दो in slave mode */
	clksw = ES8316_CLKMGR_CLKSW_MCLK_ON | ES8316_CLKMGR_CLKSW_BCLK_ON;
	snd_soc_component_update_bits(component, ES8316_CLKMGR_CLKSW, clksw, clksw);

	वापस 0;
पूर्ण

अटल पूर्णांक es8316_pcm_startup(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा es8316_priv *es8316 = snd_soc_component_get_drvdata(component);

	अगर (es8316->sysclk_स्थिरraपूर्णांकs.list)
		snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					   SNDRV_PCM_HW_PARAM_RATE,
					   &es8316->sysclk_स्थिरraपूर्णांकs);

	वापस 0;
पूर्ण

अटल पूर्णांक es8316_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा es8316_priv *es8316 = snd_soc_component_get_drvdata(component);
	u8 wordlen = 0;
	पूर्णांक i;

	/* Validate supported sample rates that are स्वतःdetected from MCLK */
	क्रम (i = 0; i < NR_SUPPORTED_MCLK_LRCK_RATIOS; i++) अणु
		स्थिर अचिन्हित पूर्णांक ratio = supported_mclk_lrck_ratios[i];

		अगर (es8316->sysclk % ratio != 0)
			जारी;
		अगर (es8316->sysclk / ratio == params_rate(params))
			अवरोध;
	पूर्ण
	अगर (i == NR_SUPPORTED_MCLK_LRCK_RATIOS)
		वापस -EINVAL;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		wordlen = ES8316_SERDATA2_LEN_16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		wordlen = ES8316_SERDATA2_LEN_20;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		wordlen = ES8316_SERDATA2_LEN_24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		wordlen = ES8316_SERDATA2_LEN_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, ES8316_SERDATA_DAC,
			    ES8316_SERDATA2_LEN_MASK, wordlen);
	snd_soc_component_update_bits(component, ES8316_SERDATA_ADC,
			    ES8316_SERDATA2_LEN_MASK, wordlen);
	वापस 0;
पूर्ण

अटल पूर्णांक es8316_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	snd_soc_component_update_bits(dai->component, ES8316_DAC_SET1, 0x20,
			    mute ? 0x20 : 0);
	वापस 0;
पूर्ण

#घोषणा ES8316_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops es8316_ops = अणु
	.startup = es8316_pcm_startup,
	.hw_params = es8316_pcm_hw_params,
	.set_fmt = es8316_set_dai_fmt,
	.set_sysclk = es8316_set_dai_sysclk,
	.mute_stream = es8316_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver es8316_dai = अणु
	.name = "ES8316 HiFi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = ES8316_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = ES8316_FORMATS,
	पूर्ण,
	.ops = &es8316_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल व्योम es8316_enable_micbias_क्रम_mic_gnd_लघु_detect(
	काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_dapm_mutex_lock(dapm);
	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "Bias");
	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "Analog power");
	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "Mic Bias");
	snd_soc_dapm_sync_unlocked(dapm);
	snd_soc_dapm_mutex_unlock(dapm);

	msleep(20);
पूर्ण

अटल व्योम es8316_disable_micbias_क्रम_mic_gnd_लघु_detect(
	काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_dapm_mutex_lock(dapm);
	snd_soc_dapm_disable_pin_unlocked(dapm, "Mic Bias");
	snd_soc_dapm_disable_pin_unlocked(dapm, "Analog power");
	snd_soc_dapm_disable_pin_unlocked(dapm, "Bias");
	snd_soc_dapm_sync_unlocked(dapm);
	snd_soc_dapm_mutex_unlock(dapm);
पूर्ण

अटल irqवापस_t es8316_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा es8316_priv *es8316 = data;
	काष्ठा snd_soc_component *comp = es8316->component;
	अचिन्हित पूर्णांक flags;

	mutex_lock(&es8316->lock);

	regmap_पढ़ो(es8316->regmap, ES8316_GPIO_FLAG, &flags);
	अगर (flags == 0x00)
		जाओ out; /* Powered-करोwn / reset */

	/* Catch spurious IRQ beक्रमe set_jack is called */
	अगर (!es8316->jack)
		जाओ out;

	अगर (es8316->jd_inverted)
		flags ^= ES8316_GPIO_FLAG_HP_NOT_INSERTED;

	dev_dbg(comp->dev, "gpio flags %#04x\n", flags);
	अगर (flags & ES8316_GPIO_FLAG_HP_NOT_INSERTED) अणु
		/* Jack हटाओd, or spurious IRQ? */
		अगर (es8316->jack->status & SND_JACK_MICROPHONE)
			es8316_disable_micbias_क्रम_mic_gnd_लघु_detect(comp);

		अगर (es8316->jack->status & SND_JACK_HEADPHONE) अणु
			snd_soc_jack_report(es8316->jack, 0,
					    SND_JACK_HEADSET | SND_JACK_BTN_0);
			dev_dbg(comp->dev, "jack unplugged\n");
		पूर्ण
	पूर्ण अन्यथा अगर (!(es8316->jack->status & SND_JACK_HEADPHONE)) अणु
		/* Jack inserted, determine type */
		es8316_enable_micbias_क्रम_mic_gnd_लघु_detect(comp);
		regmap_पढ़ो(es8316->regmap, ES8316_GPIO_FLAG, &flags);
		अगर (es8316->jd_inverted)
			flags ^= ES8316_GPIO_FLAG_HP_NOT_INSERTED;
		dev_dbg(comp->dev, "gpio flags %#04x\n", flags);
		अगर (flags & ES8316_GPIO_FLAG_HP_NOT_INSERTED) अणु
			/* Jack unplugged underneath us */
			es8316_disable_micbias_क्रम_mic_gnd_लघु_detect(comp);
		पूर्ण अन्यथा अगर (flags & ES8316_GPIO_FLAG_GM_NOT_SHORTED) अणु
			/* Open, headset */
			snd_soc_jack_report(es8316->jack,
					    SND_JACK_HEADSET,
					    SND_JACK_HEADSET);
			/* Keep mic-gnd-लघु detection on क्रम button press */
		पूर्ण अन्यथा अणु
			/* Shorted, headphones */
			snd_soc_jack_report(es8316->jack,
					    SND_JACK_HEADPHONE,
					    SND_JACK_HEADSET);
			/* No दीर्घer need mic-gnd-लघु detection */
			es8316_disable_micbias_क्रम_mic_gnd_लघु_detect(comp);
		पूर्ण
	पूर्ण अन्यथा अगर (es8316->jack->status & SND_JACK_MICROPHONE) अणु
		/* Interrupt जबतक jack inserted, report button state */
		अगर (flags & ES8316_GPIO_FLAG_GM_NOT_SHORTED) अणु
			/* Open, button release */
			snd_soc_jack_report(es8316->jack, 0, SND_JACK_BTN_0);
		पूर्ण अन्यथा अणु
			/* Short, button press */
			snd_soc_jack_report(es8316->jack,
					    SND_JACK_BTN_0,
					    SND_JACK_BTN_0);
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&es8316->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम es8316_enable_jack_detect(काष्ठा snd_soc_component *component,
				      काष्ठा snd_soc_jack *jack)
अणु
	काष्ठा es8316_priv *es8316 = snd_soc_component_get_drvdata(component);

	/*
	 * Init es8316->jd_inverted here and not in the probe, as we cannot
	 * guarantee that the bytchr-es8316 driver, which might set this
	 * property, will probe beक्रमe us.
	 */
	es8316->jd_inverted = device_property_पढ़ो_bool(component->dev,
							"everest,jack-detect-inverted");

	mutex_lock(&es8316->lock);

	es8316->jack = jack;

	अगर (es8316->jack->status & SND_JACK_MICROPHONE)
		es8316_enable_micbias_क्रम_mic_gnd_लघु_detect(component);

	snd_soc_component_update_bits(component, ES8316_GPIO_DEBOUNCE,
				      ES8316_GPIO_ENABLE_INTERRUPT,
				      ES8316_GPIO_ENABLE_INTERRUPT);

	mutex_unlock(&es8316->lock);

	/* Enable irq and sync initial jack state */
	enable_irq(es8316->irq);
	es8316_irq(es8316->irq, es8316);
पूर्ण

अटल व्योम es8316_disable_jack_detect(काष्ठा snd_soc_component *component)
अणु
	काष्ठा es8316_priv *es8316 = snd_soc_component_get_drvdata(component);

	अगर (!es8316->jack)
		वापस; /* Alपढ़ोy disabled (or never enabled) */

	disable_irq(es8316->irq);

	mutex_lock(&es8316->lock);

	snd_soc_component_update_bits(component, ES8316_GPIO_DEBOUNCE,
				      ES8316_GPIO_ENABLE_INTERRUPT, 0);

	अगर (es8316->jack->status & SND_JACK_MICROPHONE) अणु
		es8316_disable_micbias_क्रम_mic_gnd_लघु_detect(component);
		snd_soc_jack_report(es8316->jack, 0, SND_JACK_BTN_0);
	पूर्ण

	es8316->jack = शून्य;

	mutex_unlock(&es8316->lock);
पूर्ण

अटल पूर्णांक es8316_set_jack(काष्ठा snd_soc_component *component,
			   काष्ठा snd_soc_jack *jack, व्योम *data)
अणु
	अगर (jack)
		es8316_enable_jack_detect(component, jack);
	अन्यथा
		es8316_disable_jack_detect(component);

	वापस 0;
पूर्ण

अटल पूर्णांक es8316_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा es8316_priv *es8316 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	es8316->component = component;

	es8316->mclk = devm_clk_get_optional(component->dev, "mclk");
	अगर (IS_ERR(es8316->mclk)) अणु
		dev_err(component->dev, "unable to get mclk\n");
		वापस PTR_ERR(es8316->mclk);
	पूर्ण
	अगर (!es8316->mclk)
		dev_warn(component->dev, "assuming static mclk\n");

	ret = clk_prepare_enable(es8316->mclk);
	अगर (ret) अणु
		dev_err(component->dev, "unable to enable mclk\n");
		वापस ret;
	पूर्ण

	/* Reset codec and enable current state machine */
	snd_soc_component_ग_लिखो(component, ES8316_RESET, 0x3f);
	usleep_range(5000, 5500);
	snd_soc_component_ग_लिखो(component, ES8316_RESET, ES8316_RESET_CSM_ON);
	msleep(30);

	/*
	 * Documentation is unclear, but this value from the venकरोr driver is
	 * needed otherwise audio output is silent.
	 */
	snd_soc_component_ग_लिखो(component, ES8316_SYS_VMIDSEL, 0xff);

	/*
	 * Documentation क्रम this रेजिस्टर is unclear and incomplete,
	 * but here is a venकरोr-provided value that improves volume
	 * and quality क्रम Intel CHT platक्रमms.
	 */
	snd_soc_component_ग_लिखो(component, ES8316_CLKMGR_ADCOSR, 0x32);

	वापस 0;
पूर्ण

अटल व्योम es8316_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा es8316_priv *es8316 = snd_soc_component_get_drvdata(component);

	clk_disable_unprepare(es8316->mclk);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_es8316 = अणु
	.probe			= es8316_probe,
	.हटाओ			= es8316_हटाओ,
	.set_jack		= es8316_set_jack,
	.controls		= es8316_snd_controls,
	.num_controls		= ARRAY_SIZE(es8316_snd_controls),
	.dapm_widमाला_लो		= es8316_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(es8316_dapm_widमाला_लो),
	.dapm_routes		= es8316_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(es8316_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_range es8316_अस्थिर_ranges[] = अणु
	regmap_reg_range(ES8316_GPIO_FLAG, ES8316_GPIO_FLAG),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table es8316_अस्थिर_table = अणु
	.yes_ranges	= es8316_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(es8316_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config es8316_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x53,
	.अस्थिर_table	= &es8316_अस्थिर_table,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक es8316_i2c_probe(काष्ठा i2c_client *i2c_client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &i2c_client->dev;
	काष्ठा es8316_priv *es8316;
	पूर्णांक ret;

	es8316 = devm_kzalloc(&i2c_client->dev, माप(काष्ठा es8316_priv),
			      GFP_KERNEL);
	अगर (es8316 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c_client, es8316);

	es8316->regmap = devm_regmap_init_i2c(i2c_client, &es8316_regmap);
	अगर (IS_ERR(es8316->regmap))
		वापस PTR_ERR(es8316->regmap);

	es8316->irq = i2c_client->irq;
	mutex_init(&es8316->lock);

	ret = devm_request_thपढ़ोed_irq(dev, es8316->irq, शून्य, es8316_irq,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"es8316", es8316);
	अगर (ret == 0) अणु
		/* Gets re-enabled by es8316_set_jack() */
		disable_irq(es8316->irq);
	पूर्ण अन्यथा अणु
		dev_warn(dev, "Failed to get IRQ %d: %d\n", es8316->irq, ret);
		es8316->irq = -ENXIO;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&i2c_client->dev,
				      &soc_component_dev_es8316,
				      &es8316_dai, 1);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id es8316_i2c_id[] = अणु
	अणु"es8316", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, es8316_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id es8316_of_match[] = अणु
	अणु .compatible = "everest,es8316", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, es8316_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id es8316_acpi_match[] = अणु
	अणु"ESSX8316", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, es8316_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver es8316_i2c_driver = अणु
	.driver = अणु
		.name			= "es8316",
		.acpi_match_table	= ACPI_PTR(es8316_acpi_match),
		.of_match_table		= of_match_ptr(es8316_of_match),
	पूर्ण,
	.probe		= es8316_i2c_probe,
	.id_table	= es8316_i2c_id,
पूर्ण;
module_i2c_driver(es8316_i2c_driver);

MODULE_DESCRIPTION("Everest Semi ES8316 ALSA SoC Codec Driver");
MODULE_AUTHOR("David Yang <yangxiaohua@everest-semi.com>");
MODULE_LICENSE("GPL v2");
