<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// MAX9867 ALSA SoC codec driver
//
// Copyright 2013-2015 Maxim Integrated Products
// Copyright 2018 Ladislav Michl <ladis@linux-mips.org>
//

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश "max9867.h"

काष्ठा max9867_priv अणु
	काष्ठा regmap *regmap;
	स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *स्थिरraपूर्णांकs;
	अचिन्हित पूर्णांक sysclk, pclk;
	bool master, dsp_a;
	अचिन्हित पूर्णांक adc_dac_active;
पूर्ण;

अटल स्थिर अक्षर *स्थिर max9867_spmode[] = अणु
	"Stereo Diff", "Mono Diff",
	"Stereo Cap", "Mono Cap",
	"Stereo Single", "Mono Single",
	"Stereo Single Fast", "Mono Single Fast"
पूर्ण;
अटल स्थिर अक्षर *स्थिर max9867_filter_text[] = अणु"IIR", "FIR"पूर्ण;

अटल स्थिर अक्षर *स्थिर max9867_adc_dac_filter_text[] = अणु
	"Disabled",
	"Elliptical/16/256",
	"Butterworth/16/500",
	"Elliptical/8/256",
	"Butterworth/8/500",
	"Butterworth/8-24"
पूर्ण;

क्रमागत max9867_adc_dac अणु
	MAX9867_ADC_LEFT,
	MAX9867_ADC_RIGHT,
	MAX9867_DAC_LEFT,
	MAX9867_DAC_RIGHT,
पूर्ण;

अटल पूर्णांक max9867_adc_dac_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा max9867_priv *max9867 = snd_soc_component_get_drvdata(component);
	क्रमागत max9867_adc_dac adc_dac;

	अगर (!म_भेद(w->name, "ADCL"))
		adc_dac = MAX9867_ADC_LEFT;
	अन्यथा अगर (!म_भेद(w->name, "ADCR"))
		adc_dac = MAX9867_ADC_RIGHT;
	अन्यथा अगर (!म_भेद(w->name, "DACL"))
		adc_dac = MAX9867_DAC_LEFT;
	अन्यथा अगर (!म_भेद(w->name, "DACR"))
		adc_dac = MAX9867_DAC_RIGHT;
	अन्यथा
		वापस 0;

	अगर (SND_SOC_DAPM_EVENT_ON(event))
		max9867->adc_dac_active |= BIT(adc_dac);
	अन्यथा अगर (SND_SOC_DAPM_EVENT_OFF(event))
		max9867->adc_dac_active &= ~BIT(adc_dac);

	वापस 0;
पूर्ण

अटल पूर्णांक max9867_filter_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max9867_priv *max9867 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(max9867->regmap, MAX9867_CODECFLTR, &reg);
	अगर (ret)
		वापस -EINVAL;

	अगर (reg & MAX9867_CODECFLTR_MODE)
		ucontrol->value.क्रमागतerated.item[0] = 1;
	अन्यथा
		ucontrol->value.क्रमागतerated.item[0] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक max9867_filter_set(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max9867_priv *max9867 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg, mode = ucontrol->value.क्रमागतerated.item[0];
	पूर्णांक ret;

	अगर (mode > 1)
		वापस -EINVAL;

	/* करोn't allow change अगर ADC/DAC active */
	अगर (max9867->adc_dac_active)
		वापस -EBUSY;

	/* पढ़ो current filter mode */
	ret = regmap_पढ़ो(max9867->regmap, MAX9867_CODECFLTR, &reg);
	अगर (ret)
		वापस -EINVAL;

	अगर (mode)
		mode = MAX9867_CODECFLTR_MODE;

	/* check अगर change is needed */
	अगर ((reg & MAX9867_CODECFLTR_MODE) == mode)
		वापस 0;

	/* shutकरोwn codec beक्रमe चयनing filter mode */
	regmap_update_bits(max9867->regmap, MAX9867_PWRMAN,
		MAX9867_PWRMAN_SHDN, 0);

	/* चयन filter mode */
	regmap_update_bits(max9867->regmap, MAX9867_CODECFLTR,
		MAX9867_CODECFLTR_MODE, mode);

	/* out of shutकरोwn now */
	regmap_update_bits(max9867->regmap, MAX9867_PWRMAN,
		MAX9867_PWRMAN_SHDN, MAX9867_PWRMAN_SHDN);

	वापस 0;
पूर्ण

अटल SOC_ENUM_SINGLE_EXT_DECL(max9867_filter, max9867_filter_text);
अटल SOC_ENUM_SINGLE_DECL(max9867_dac_filter, MAX9867_CODECFLTR, 0,
	max9867_adc_dac_filter_text);
अटल SOC_ENUM_SINGLE_DECL(max9867_adc_filter, MAX9867_CODECFLTR, 4,
	max9867_adc_dac_filter_text);
अटल SOC_ENUM_SINGLE_DECL(max9867_spkmode, MAX9867_MODECONFIG, 0,
	max9867_spmode);
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_RANGE(max9867_master_tlv,
	 0,  2, TLV_DB_SCALE_ITEM(-8600, 200, 1),
	 3, 17, TLV_DB_SCALE_ITEM(-7800, 400, 0),
	18, 25, TLV_DB_SCALE_ITEM(-2000, 200, 0),
	26, 34, TLV_DB_SCALE_ITEM( -500, 100, 0),
	35, 40, TLV_DB_SCALE_ITEM(  350,  50, 0),
);
अटल DECLARE_TLV_DB_SCALE(max9867_mic_tlv, 0, 100, 0);
अटल DECLARE_TLV_DB_SCALE(max9867_line_tlv, -600, 200, 0);
अटल DECLARE_TLV_DB_SCALE(max9867_adc_tlv, -1200, 100, 0);
अटल DECLARE_TLV_DB_SCALE(max9867_dac_tlv, -1500, 100, 0);
अटल DECLARE_TLV_DB_SCALE(max9867_dacboost_tlv, 0, 600, 0);
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_RANGE(max9867_micboost_tlv,
	0, 2, TLV_DB_SCALE_ITEM(-2000, 2000, 1),
	3, 3, TLV_DB_SCALE_ITEM(3000, 0, 0),
);

अटल स्थिर काष्ठा snd_kcontrol_new max9867_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("Master Playback Volume", MAX9867_LEFTVOL,
			MAX9867_RIGHTVOL, 0, 40, 1, max9867_master_tlv),
	SOC_DOUBLE_R_TLV("Line Capture Volume", MAX9867_LEFTLINELVL,
			MAX9867_RIGHTLINELVL, 0, 15, 1, max9867_line_tlv),
	SOC_DOUBLE_R_TLV("Mic Capture Volume", MAX9867_LEFTMICGAIN,
			MAX9867_RIGHTMICGAIN, 0, 20, 1, max9867_mic_tlv),
	SOC_DOUBLE_R_TLV("Mic Boost Capture Volume", MAX9867_LEFTMICGAIN,
			MAX9867_RIGHTMICGAIN, 5, 3, 0, max9867_micboost_tlv),
	SOC_SINGLE("Digital Sidetone Volume", MAX9867_SIDETONE, 0, 31, 1),
	SOC_SINGLE_TLV("Digital Playback Volume", MAX9867_DACLEVEL, 0, 15, 1,
			max9867_dac_tlv),
	SOC_SINGLE_TLV("Digital Boost Playback Volume", MAX9867_DACLEVEL, 4, 3, 0,
			max9867_dacboost_tlv),
	SOC_DOUBLE_TLV("Digital Capture Volume", MAX9867_ADCLEVEL, 4, 0, 15, 1,
			max9867_adc_tlv),
	SOC_ENUM("Speaker Mode", max9867_spkmode),
	SOC_SINGLE("Volume Smoothing Switch", MAX9867_MODECONFIG, 6, 1, 0),
	SOC_SINGLE("Line ZC Switch", MAX9867_MODECONFIG, 5, 1, 0),
	SOC_ENUM_EXT("DSP Filter", max9867_filter, max9867_filter_get, max9867_filter_set),
	SOC_ENUM("ADC Filter", max9867_adc_filter),
	SOC_ENUM("DAC Filter", max9867_dac_filter),
	SOC_SINGLE("Mono Playback Switch", MAX9867_IFC1B, 3, 1, 0),
पूर्ण;

/* Input mixer */
अटल स्थिर काष्ठा snd_kcontrol_new max9867_input_mixer_controls[] = अणु
	SOC_DAPM_DOUBLE("Line Capture Switch", MAX9867_INPUTCONFIG, 7, 5, 1, 0),
	SOC_DAPM_DOUBLE("Mic Capture Switch", MAX9867_INPUTCONFIG, 6, 4, 1, 0),
पूर्ण;

/* Output mixer */
अटल स्थिर काष्ठा snd_kcontrol_new max9867_output_mixer_controls[] = अणु
	SOC_DAPM_DOUBLE_R("Line Bypass Switch",
			  MAX9867_LEFTLINELVL, MAX9867_RIGHTLINELVL, 6, 1, 1),
पूर्ण;

/* Sidetone mixer */
अटल स्थिर काष्ठा snd_kcontrol_new max9867_sidetone_mixer_controls[] = अणु
	SOC_DAPM_DOUBLE("Sidetone Switch", MAX9867_SIDETONE, 6, 7, 1, 0),
पूर्ण;

/* Line out चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max9867_line_out_control =
	SOC_DAPM_DOUBLE_R("Switch",
			  MAX9867_LEFTVOL, MAX9867_RIGHTVOL, 6, 1, 1);

/* DMIC mux */
अटल स्थिर अक्षर *स्थिर dmic_mux_text[] = अणु
	"ADC", "DMIC"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(left_dmic_mux_क्रमागत,
			    MAX9867_MICCONFIG, 5, dmic_mux_text);
अटल SOC_ENUM_SINGLE_DECL(right_dmic_mux_क्रमागत,
			    MAX9867_MICCONFIG, 4, dmic_mux_text);
अटल स्थिर काष्ठा snd_kcontrol_new max9867_left_dmic_mux =
	SOC_DAPM_ENUM("DMICL Mux", left_dmic_mux_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new max9867_right_dmic_mux =
	SOC_DAPM_ENUM("DMICR Mux", right_dmic_mux_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget max9867_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("MICL"),
	SND_SOC_DAPM_INPUT("MICR"),
	SND_SOC_DAPM_INPUT("DMICL"),
	SND_SOC_DAPM_INPUT("DMICR"),
	SND_SOC_DAPM_INPUT("LINL"),
	SND_SOC_DAPM_INPUT("LINR"),

	SND_SOC_DAPM_PGA("Left Line Input", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Line Input", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER_NAMED_CTL("Input Mixer", SND_SOC_NOPM, 0, 0,
				     max9867_input_mixer_controls,
				     ARRAY_SIZE(max9867_input_mixer_controls)),
	SND_SOC_DAPM_MUX("DMICL Mux", SND_SOC_NOPM, 0, 0,
			 &max9867_left_dmic_mux),
	SND_SOC_DAPM_MUX("DMICR Mux", SND_SOC_NOPM, 0, 0,
			 &max9867_right_dmic_mux),
	SND_SOC_DAPM_ADC_E("ADCL", "HiFi Capture", SND_SOC_NOPM, 0, 0,
			   max9867_adc_dac_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_ADC_E("ADCR", "HiFi Capture", SND_SOC_NOPM, 0, 0,
			   max9867_adc_dac_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MIXER("Digital", SND_SOC_NOPM, 0, 0,
			   max9867_sidetone_mixer_controls,
			   ARRAY_SIZE(max9867_sidetone_mixer_controls)),
	SND_SOC_DAPM_MIXER_NAMED_CTL("Output Mixer", SND_SOC_NOPM, 0, 0,
				     max9867_output_mixer_controls,
				     ARRAY_SIZE(max9867_output_mixer_controls)),
	SND_SOC_DAPM_DAC_E("DACL", "HiFi Playback", SND_SOC_NOPM, 0, 0,
			   max9867_adc_dac_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("DACR", "HiFi Playback", SND_SOC_NOPM, 0, 0,
			   max9867_adc_dac_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SWITCH("Master Playback", SND_SOC_NOPM, 0, 0,
			    &max9867_line_out_control),
	SND_SOC_DAPM_OUTPUT("LOUT"),
	SND_SOC_DAPM_OUTPUT("ROUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max9867_audio_map[] = अणु
	अणु"Left Line Input", शून्य, "LINL"पूर्ण,
	अणु"Right Line Input", शून्य, "LINR"पूर्ण,
	अणु"Input Mixer", "Mic Capture Switch", "MICL"पूर्ण,
	अणु"Input Mixer", "Mic Capture Switch", "MICR"पूर्ण,
	अणु"Input Mixer", "Line Capture Switch", "Left Line Input"पूर्ण,
	अणु"Input Mixer", "Line Capture Switch", "Right Line Input"पूर्ण,
	अणु"DMICL Mux", "DMIC", "DMICL"पूर्ण,
	अणु"DMICR Mux", "DMIC", "DMICR"पूर्ण,
	अणु"DMICL Mux", "ADC", "Input Mixer"पूर्ण,
	अणु"DMICR Mux", "ADC", "Input Mixer"पूर्ण,
	अणु"ADCL", शून्य, "DMICL Mux"पूर्ण,
	अणु"ADCR", शून्य, "DMICR Mux"पूर्ण,

	अणु"Digital", "Sidetone Switch", "ADCL"पूर्ण,
	अणु"Digital", "Sidetone Switch", "ADCR"पूर्ण,
	अणु"DACL", शून्य, "Digital"पूर्ण,
	अणु"DACR", शून्य, "Digital"पूर्ण,

	अणु"Output Mixer", "Line Bypass Switch", "Left Line Input"पूर्ण,
	अणु"Output Mixer", "Line Bypass Switch", "Right Line Input"पूर्ण,
	अणु"Output Mixer", शून्य, "DACL"पूर्ण,
	अणु"Output Mixer", शून्य, "DACR"पूर्ण,
	अणु"Master Playback", "Switch", "Output Mixer"पूर्ण,
	अणु"LOUT", शून्य, "Master Playback"पूर्ण,
	अणु"ROUT", शून्य, "Master Playback"पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक max9867_rates_44k1[] = अणु
	11025, 22050, 44100,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list max9867_स्थिरraपूर्णांकs_44k1 = अणु
	.list = max9867_rates_44k1,
	.count = ARRAY_SIZE(max9867_rates_44k1),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक max9867_rates_48k[] = अणु
	8000, 16000, 32000, 48000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list max9867_स्थिरraपूर्णांकs_48k = अणु
	.list = max9867_rates_48k,
	.count = ARRAY_SIZE(max9867_rates_48k),
पूर्ण;

अटल पूर्णांक max9867_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
        काष्ठा max9867_priv *max9867 =
		snd_soc_component_get_drvdata(dai->component);

	अगर (max9867->स्थिरraपूर्णांकs)
		snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, max9867->स्थिरraपूर्णांकs);

	वापस 0;
पूर्ण

अटल पूर्णांक max9867_dai_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक value;
	अचिन्हित दीर्घ पूर्णांक rate, ratio;
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max9867_priv *max9867 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक ni = DIV_ROUND_CLOSEST_ULL(96ULL * 0x10000 * params_rate(params),
						max9867->pclk);

	/* set up the ni value */
	regmap_update_bits(max9867->regmap, MAX9867_AUDIOCLKHIGH,
		MAX9867_NI_HIGH_MASK, (0xFF00 & ni) >> 8);
	regmap_update_bits(max9867->regmap, MAX9867_AUDIOCLKLOW,
		MAX9867_NI_LOW_MASK, 0x00FF & ni);
	अगर (max9867->master) अणु
		अगर (max9867->dsp_a) अणु
			value = MAX9867_IFC1B_48X;
		पूर्ण अन्यथा अणु
			rate = params_rate(params) * 2 * params_width(params);
			ratio = max9867->pclk / rate;
			चयन (params_width(params)) अणु
			हाल 8:
			हाल 16:
				चयन (ratio) अणु
				हाल 2:
					value = MAX9867_IFC1B_PCLK_2;
					अवरोध;
				हाल 4:
					value = MAX9867_IFC1B_PCLK_4;
					अवरोध;
				हाल 8:
					value = MAX9867_IFC1B_PCLK_8;
					अवरोध;
				हाल 16:
					value = MAX9867_IFC1B_PCLK_16;
					अवरोध;
				शेष:
					वापस -EINVAL;
				पूर्ण
				अवरोध;
			हाल 24:
				value = MAX9867_IFC1B_48X;
				अवरोध;
			हाल 32:
				value = MAX9867_IFC1B_64X;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		regmap_update_bits(max9867->regmap, MAX9867_IFC1B,
			MAX9867_IFC1B_BCLK_MASK, value);
	पूर्ण अन्यथा अणु
		/*
		 * digital pll locks on to any बाह्यally supplied LRCLK संकेत
		 * and also enable rapid lock mode.
		 */
		regmap_update_bits(max9867->regmap, MAX9867_AUDIOCLKLOW,
			MAX9867_RAPID_LOCK, MAX9867_RAPID_LOCK);
		regmap_update_bits(max9867->regmap, MAX9867_AUDIOCLKHIGH,
			MAX9867_PLL, MAX9867_PLL);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max9867_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max9867_priv *max9867 = snd_soc_component_get_drvdata(component);

	वापस regmap_update_bits(max9867->regmap, MAX9867_DACLEVEL,
				  1 << 6, !!mute << 6);
पूर्ण

अटल पूर्णांक max9867_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा max9867_priv *max9867 = snd_soc_component_get_drvdata(component);
	पूर्णांक value = 0;

	/* Set the prescaler based on the master घड़ी frequency*/
	अगर (freq >= 10000000 && freq <= 20000000) अणु
		value |= MAX9867_PSCLK_10_20;
		max9867->pclk = freq;
	पूर्ण अन्यथा अगर (freq >= 20000000 && freq <= 40000000) अणु
		value |= MAX9867_PSCLK_20_40;
		max9867->pclk = freq / 2;
	पूर्ण अन्यथा अगर (freq >= 40000000 && freq <= 60000000) अणु
		value |= MAX9867_PSCLK_40_60;
		max9867->pclk = freq / 4;
	पूर्ण अन्यथा अणु
		dev_err(component->dev,
			"Invalid clock frequency %uHz (required 10-60MHz)\n",
			freq);
		वापस -EINVAL;
	पूर्ण
	अगर (freq % 48000 == 0)
		max9867->स्थिरraपूर्णांकs = &max9867_स्थिरraपूर्णांकs_48k;
	अन्यथा अगर (freq % 44100 == 0)
		max9867->स्थिरraपूर्णांकs = &max9867_स्थिरraपूर्णांकs_44k1;
	अन्यथा
		dev_warn(component->dev,
			 "Unable to set exact rate with %uHz clock frequency\n",
			 freq);
	max9867->sysclk = freq;
	value = value << MAX9867_PSCLK_SHIFT;
	/* exact पूर्णांकeger mode is not supported */
	value &= ~MAX9867_FREQ_MASK;
	regmap_update_bits(max9867->regmap, MAX9867_SYSCLK,
			MAX9867_PSCLK_MASK, value);
	वापस 0;
पूर्ण

अटल पूर्णांक max9867_dai_set_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा max9867_priv *max9867 = snd_soc_component_get_drvdata(component);
	u8 अगरace1A, अगरace1B;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		max9867->master = true;
		अगरace1A = MAX9867_MASTER;
		अगरace1B = MAX9867_IFC1B_48X;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		max9867->master = false;
		अगरace1A = अगरace1B = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		max9867->dsp_a = false;
		अगरace1A |= MAX9867_I2S_DLY;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		max9867->dsp_a = true;
		अगरace1A |= MAX9867_TDM_MODE | MAX9867_SDOUT_HIZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Clock inversion bits, BCI and WCI */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace1A |= MAX9867_WCI_MODE | MAX9867_BCI_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace1A |= MAX9867_BCI_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगरace1A |= MAX9867_WCI_MODE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(max9867->regmap, MAX9867_IFC1A, अगरace1A);
	regmap_update_bits(max9867->regmap, MAX9867_IFC1B,
			   MAX9867_IFC1B_BCLK_MASK, अगरace1B);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops max9867_dai_ops = अणु
	.set_sysclk	= max9867_set_dai_sysclk,
	.set_fmt	= max9867_dai_set_fmt,
	.mute_stream	= max9867_mute,
	.startup	= max9867_startup,
	.hw_params	= max9867_dai_hw_params,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver max9867_dai[] = अणु
	अणु
	.name = "max9867-aif1",
	.playback = अणु
		.stream_name = "HiFi Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "HiFi Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops = &max9867_dai_ops,
	.symmetric_rate = 1,
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक max9867_suspend(काष्ठा snd_soc_component *component)
अणु
	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक max9867_resume(काष्ठा snd_soc_component *component)
अणु
	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा max9867_suspend	शून्य
#घोषणा max9867_resume	शून्य
#पूर्ण_अगर

अटल पूर्णांक max9867_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	पूर्णांक err;
	काष्ठा max9867_priv *max9867 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			err = regcache_sync(max9867->regmap);
			अगर (err)
				वापस err;

			err = regmap_ग_लिखो(max9867->regmap,
					   MAX9867_PWRMAN, 0xff);
			अगर (err)
				वापस err;
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		err = regmap_ग_लिखो(max9867->regmap, MAX9867_PWRMAN, 0);
		अगर (err)
			वापस err;

		regcache_mark_dirty(max9867->regmap);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver max9867_component = अणु
	.controls		= max9867_snd_controls,
	.num_controls		= ARRAY_SIZE(max9867_snd_controls),
	.dapm_routes		= max9867_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(max9867_audio_map),
	.dapm_widमाला_लो		= max9867_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(max9867_dapm_widमाला_लो),
	.suspend		= max9867_suspend,
	.resume			= max9867_resume,
	.set_bias_level		= max9867_set_bias_level,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल bool max9867_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX9867_STATUS:
	हाल MAX9867_JACKSTATUS:
	हाल MAX9867_AUXHIGH:
	हाल MAX9867_AUXLOW:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config max9867_regmap = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= MAX9867_REVISION,
	.अस्थिर_reg	= max9867_अस्थिर_रेजिस्टर,
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक max9867_i2c_probe(काष्ठा i2c_client *i2c,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max9867_priv *max9867;
	पूर्णांक ret, reg;

	max9867 = devm_kzalloc(&i2c->dev, माप(*max9867), GFP_KERNEL);
	अगर (!max9867)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, max9867);
	max9867->regmap = devm_regmap_init_i2c(i2c, &max9867_regmap);
	अगर (IS_ERR(max9867->regmap)) अणु
		ret = PTR_ERR(max9867->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = regmap_पढ़ो(max9867->regmap, MAX9867_REVISION, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read: %d\n", ret);
		वापस ret;
	पूर्ण
	dev_info(&i2c->dev, "device revision: %x\n", reg);
	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev, &max9867_component,
			max9867_dai, ARRAY_SIZE(max9867_dai));
	अगर (ret < 0)
		dev_err(&i2c->dev, "Failed to register component: %d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max9867_i2c_id[] = अणु
	अणु "max9867", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max9867_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max9867_of_match[] = अणु
	अणु .compatible = "maxim,max9867", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max9867_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver max9867_i2c_driver = अणु
	.driver = अणु
		.name = "max9867",
		.of_match_table = of_match_ptr(max9867_of_match),
	पूर्ण,
	.probe  = max9867_i2c_probe,
	.id_table = max9867_i2c_id,
पूर्ण;

module_i2c_driver(max9867_i2c_driver);

MODULE_AUTHOR("Ladislav Michl <ladis@linux-mips.org>");
MODULE_DESCRIPTION("ASoC MAX9867 driver");
MODULE_LICENSE("GPL");
