<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * es8328.c  --  ES8328 ALSA SoC Audio driver
 *
 * Copyright 2014 Sutajio Ko-Usagi PTE LTD
 *
 * Author: Sean Cross <xobs@kosagi.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश "es8328.h"

अटल स्थिर अचिन्हित पूर्णांक rates_12288[] = अणु
	8000, 12000, 16000, 24000, 32000, 48000, 96000,
पूर्ण;

अटल स्थिर पूर्णांक ratios_12288[] = अणु
	10, 7, 6, 4, 3, 2, 0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_12288 = अणु
	.count	= ARRAY_SIZE(rates_12288),
	.list	= rates_12288,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates_11289[] = अणु
	8018, 11025, 22050, 44100, 88200,
पूर्ण;

अटल स्थिर पूर्णांक ratios_11289[] = अणु
	9, 7, 4, 2, 0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_11289 = अणु
	.count	= ARRAY_SIZE(rates_11289),
	.list	= rates_11289,
पूर्ण;

/* regulator supplies क्रम sgtl5000, VDDD is an optional बाह्यal supply */
क्रमागत sgtl5000_regulator_supplies अणु
	DVDD,
	AVDD,
	PVDD,
	HPVDD,
	ES8328_SUPPLY_NUM
पूर्ण;

/* vddd is optional supply */
अटल स्थिर अक्षर * स्थिर supply_names[ES8328_SUPPLY_NUM] = अणु
	"DVDD",
	"AVDD",
	"PVDD",
	"HPVDD",
पूर्ण;

#घोषणा ES8328_RATES (SNDRV_PCM_RATE_192000 | \
		SNDRV_PCM_RATE_96000 | \
		SNDRV_PCM_RATE_88200 | \
		SNDRV_PCM_RATE_8000_48000)
#घोषणा ES8328_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | \
		SNDRV_PCM_FMTBIT_S18_3LE | \
		SNDRV_PCM_FMTBIT_S20_3LE | \
		SNDRV_PCM_FMTBIT_S24_LE | \
		SNDRV_PCM_FMTBIT_S32_LE)

काष्ठा es8328_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा clk *clk;
	पूर्णांक playback_fs;
	bool deemph;
	पूर्णांक mclkभाग2;
	स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *sysclk_स्थिरraपूर्णांकs;
	स्थिर पूर्णांक *mclk_ratios;
	bool master;
	काष्ठा regulator_bulk_data supplies[ES8328_SUPPLY_NUM];
पूर्ण;

/*
 * ES8328 Controls
 */

अटल स्थिर अक्षर * स्थिर adcpol_txt[] = अणु"Normal", "L Invert", "R Invert",
					  "L + R Invert"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(adcpol,
			    ES8328_ADCCONTROL6, 6, adcpol_txt);

अटल स्थिर DECLARE_TLV_DB_SCALE(play_tlv, -3000, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_adc_tlv, -9600, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(bypass_tlv, -1500, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_tlv, 0, 300, 0);

अटल स्थिर काष्ठा अणु
	पूर्णांक rate;
	अचिन्हित पूर्णांक val;
पूर्ण deemph_settings[] = अणु
	अणु 0,     ES8328_DACCONTROL6_DEEMPH_OFF पूर्ण,
	अणु 32000, ES8328_DACCONTROL6_DEEMPH_32k पूर्ण,
	अणु 44100, ES8328_DACCONTROL6_DEEMPH_44_1k पूर्ण,
	अणु 48000, ES8328_DACCONTROL6_DEEMPH_48k पूर्ण,
पूर्ण;

अटल पूर्णांक es8328_set_deemph(काष्ठा snd_soc_component *component)
अणु
	काष्ठा es8328_priv *es8328 = snd_soc_component_get_drvdata(component);
	पूर्णांक val, i, best;

	/*
	 * If we're using deemphasis select the nearest available sample
	 * rate.
	 */
	अगर (es8328->deemph) अणु
		best = 0;
		क्रम (i = 1; i < ARRAY_SIZE(deemph_settings); i++) अणु
			अगर (असल(deemph_settings[i].rate - es8328->playback_fs) <
			    असल(deemph_settings[best].rate - es8328->playback_fs))
				best = i;
		पूर्ण

		val = deemph_settings[best].val;
	पूर्ण अन्यथा अणु
		val = ES8328_DACCONTROL6_DEEMPH_OFF;
	पूर्ण

	dev_dbg(component->dev, "Set deemphasis %d\n", val);

	वापस snd_soc_component_update_bits(component, ES8328_DACCONTROL6,
			ES8328_DACCONTROL6_DEEMPH_MASK, val);
पूर्ण

अटल पूर्णांक es8328_get_deemph(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा es8328_priv *es8328 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = es8328->deemph;
	वापस 0;
पूर्ण

अटल पूर्णांक es8328_put_deemph(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा es8328_priv *es8328 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक deemph = ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक ret;

	अगर (deemph > 1)
		वापस -EINVAL;

	ret = es8328_set_deemph(component);
	अगर (ret < 0)
		वापस ret;

	es8328->deemph = deemph;

	वापस 0;
पूर्ण



अटल स्थिर काष्ठा snd_kcontrol_new es8328_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("Capture Digital Volume",
		ES8328_ADCCONTROL8, ES8328_ADCCONTROL9,
		 0, 0xc0, 1, dac_adc_tlv),
	SOC_SINGLE("Capture ZC Switch", ES8328_ADCCONTROL7, 6, 1, 0),

	SOC_SINGLE_BOOL_EXT("DAC Deemphasis Switch", 0,
		    es8328_get_deemph, es8328_put_deemph),

	SOC_ENUM("Capture Polarity", adcpol),

	SOC_SINGLE_TLV("Left Mixer Left Bypass Volume",
			ES8328_DACCONTROL17, 3, 7, 1, bypass_tlv),
	SOC_SINGLE_TLV("Left Mixer Right Bypass Volume",
			ES8328_DACCONTROL19, 3, 7, 1, bypass_tlv),
	SOC_SINGLE_TLV("Right Mixer Left Bypass Volume",
			ES8328_DACCONTROL18, 3, 7, 1, bypass_tlv),
	SOC_SINGLE_TLV("Right Mixer Right Bypass Volume",
			ES8328_DACCONTROL20, 3, 7, 1, bypass_tlv),

	SOC_DOUBLE_R_TLV("PCM Volume",
			ES8328_LDACVOL, ES8328_RDACVOL,
			0, ES8328_DACVOL_MAX, 1, dac_adc_tlv),

	SOC_DOUBLE_R_TLV("Output 1 Playback Volume",
			ES8328_LOUT1VOL, ES8328_ROUT1VOL,
			0, ES8328_OUT1VOL_MAX, 0, play_tlv),

	SOC_DOUBLE_R_TLV("Output 2 Playback Volume",
			ES8328_LOUT2VOL, ES8328_ROUT2VOL,
			0, ES8328_OUT2VOL_MAX, 0, play_tlv),

	SOC_DOUBLE_TLV("Mic PGA Volume", ES8328_ADCCONTROL1,
			4, 0, 8, 0, mic_tlv),
पूर्ण;

/*
 * DAPM Controls
 */

अटल स्थिर अक्षर * स्थिर es8328_line_texts[] = अणु
	"Line 1", "Line 2", "PGA", "Differential"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत es8328_lline_क्रमागत =
	SOC_ENUM_SINGLE(ES8328_DACCONTROL16, 3,
			      ARRAY_SIZE(es8328_line_texts),
			      es8328_line_texts);
अटल स्थिर काष्ठा snd_kcontrol_new es8328_left_line_controls =
	SOC_DAPM_ENUM("Route", es8328_lline_क्रमागत);

अटल स्थिर काष्ठा soc_क्रमागत es8328_rline_क्रमागत =
	SOC_ENUM_SINGLE(ES8328_DACCONTROL16, 0,
			      ARRAY_SIZE(es8328_line_texts),
			      es8328_line_texts);
अटल स्थिर काष्ठा snd_kcontrol_new es8328_right_line_controls =
	SOC_DAPM_ENUM("Route", es8328_rline_क्रमागत);

/* Left Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new es8328_left_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Playback Switch", ES8328_DACCONTROL17, 7, 1, 0),
	SOC_DAPM_SINGLE("Left Bypass Switch", ES8328_DACCONTROL17, 6, 1, 0),
	SOC_DAPM_SINGLE("Right Playback Switch", ES8328_DACCONTROL18, 7, 1, 0),
	SOC_DAPM_SINGLE("Right Bypass Switch", ES8328_DACCONTROL18, 6, 1, 0),
पूर्ण;

/* Right Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new es8328_right_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left Playback Switch", ES8328_DACCONTROL19, 7, 1, 0),
	SOC_DAPM_SINGLE("Left Bypass Switch", ES8328_DACCONTROL19, 6, 1, 0),
	SOC_DAPM_SINGLE("Playback Switch", ES8328_DACCONTROL20, 7, 1, 0),
	SOC_DAPM_SINGLE("Right Bypass Switch", ES8328_DACCONTROL20, 6, 1, 0),
पूर्ण;

अटल स्थिर अक्षर * स्थिर es8328_pga_sel[] = अणु
	"Line 1", "Line 2", "Line 3", "Differential"पूर्ण;

/* Left PGA Mux */
अटल स्थिर काष्ठा soc_क्रमागत es8328_lpga_क्रमागत =
	SOC_ENUM_SINGLE(ES8328_ADCCONTROL2, 6,
			      ARRAY_SIZE(es8328_pga_sel),
			      es8328_pga_sel);
अटल स्थिर काष्ठा snd_kcontrol_new es8328_left_pga_controls =
	SOC_DAPM_ENUM("Route", es8328_lpga_क्रमागत);

/* Right PGA Mux */
अटल स्थिर काष्ठा soc_क्रमागत es8328_rpga_क्रमागत =
	SOC_ENUM_SINGLE(ES8328_ADCCONTROL2, 4,
			      ARRAY_SIZE(es8328_pga_sel),
			      es8328_pga_sel);
अटल स्थिर काष्ठा snd_kcontrol_new es8328_right_pga_controls =
	SOC_DAPM_ENUM("Route", es8328_rpga_क्रमागत);

/* Dअगरferential Mux */
अटल स्थिर अक्षर * स्थिर es8328_dअगरf_sel[] = अणु"Line 1", "Line 2"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dअगरfmux,
			    ES8328_ADCCONTROL3, 7, es8328_dअगरf_sel);
अटल स्थिर काष्ठा snd_kcontrol_new es8328_dअगरfmux_controls =
	SOC_DAPM_ENUM("Route", dअगरfmux);

/* Mono ADC Mux */
अटल स्थिर अक्षर * स्थिर es8328_mono_mux[] = अणु"Stereo", "Mono (Left)",
	"Mono (Right)", "Digital Mono"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(monomux,
			    ES8328_ADCCONTROL3, 3, es8328_mono_mux);
अटल स्थिर काष्ठा snd_kcontrol_new es8328_monomux_controls =
	SOC_DAPM_ENUM("Route", monomux);

अटल स्थिर काष्ठा snd_soc_dapm_widget es8328_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("Differential Mux", SND_SOC_NOPM, 0, 0,
		&es8328_dअगरfmux_controls),
	SND_SOC_DAPM_MUX("Left ADC Mux", SND_SOC_NOPM, 0, 0,
		&es8328_monomux_controls),
	SND_SOC_DAPM_MUX("Right ADC Mux", SND_SOC_NOPM, 0, 0,
		&es8328_monomux_controls),

	SND_SOC_DAPM_MUX("Left PGA Mux", ES8328_ADCPOWER,
			ES8328_ADCPOWER_AINL_OFF, 1,
			&es8328_left_pga_controls),
	SND_SOC_DAPM_MUX("Right PGA Mux", ES8328_ADCPOWER,
			ES8328_ADCPOWER_AINR_OFF, 1,
			&es8328_right_pga_controls),

	SND_SOC_DAPM_MUX("Left Line Mux", SND_SOC_NOPM, 0, 0,
		&es8328_left_line_controls),
	SND_SOC_DAPM_MUX("Right Line Mux", SND_SOC_NOPM, 0, 0,
		&es8328_right_line_controls),

	SND_SOC_DAPM_ADC("Right ADC", "Right Capture", ES8328_ADCPOWER,
			ES8328_ADCPOWER_ADCR_OFF, 1),
	SND_SOC_DAPM_ADC("Left ADC", "Left Capture", ES8328_ADCPOWER,
			ES8328_ADCPOWER_ADCL_OFF, 1),

	SND_SOC_DAPM_SUPPLY("Mic Bias", ES8328_ADCPOWER,
			ES8328_ADCPOWER_MIC_BIAS_OFF, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Mic Bias Gen", ES8328_ADCPOWER,
			ES8328_ADCPOWER_ADC_BIAS_GEN_OFF, 1, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("DAC STM", ES8328_CHIPPOWER,
			ES8328_CHIPPOWER_DACSTM_RESET, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC STM", ES8328_CHIPPOWER,
			ES8328_CHIPPOWER_ADCSTM_RESET, 1, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("DAC DIG", ES8328_CHIPPOWER,
			ES8328_CHIPPOWER_DACDIG_OFF, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC DIG", ES8328_CHIPPOWER,
			ES8328_CHIPPOWER_ADCDIG_OFF, 1, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("DAC DLL", ES8328_CHIPPOWER,
			ES8328_CHIPPOWER_DACDLL_OFF, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC DLL", ES8328_CHIPPOWER,
			ES8328_CHIPPOWER_ADCDLL_OFF, 1, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("ADC Vref", ES8328_CHIPPOWER,
			ES8328_CHIPPOWER_ADCVREF_OFF, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC Vref", ES8328_CHIPPOWER,
			ES8328_CHIPPOWER_DACVREF_OFF, 1, शून्य, 0),

	SND_SOC_DAPM_DAC("Right DAC", "Right Playback", ES8328_DACPOWER,
			ES8328_DACPOWER_RDAC_OFF, 1),
	SND_SOC_DAPM_DAC("Left DAC", "Left Playback", ES8328_DACPOWER,
			ES8328_DACPOWER_LDAC_OFF, 1),

	SND_SOC_DAPM_MIXER("Left Mixer", SND_SOC_NOPM, 0, 0,
		&es8328_left_mixer_controls[0],
		ARRAY_SIZE(es8328_left_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right Mixer", SND_SOC_NOPM, 0, 0,
		&es8328_right_mixer_controls[0],
		ARRAY_SIZE(es8328_right_mixer_controls)),

	SND_SOC_DAPM_PGA("Right Out 2", ES8328_DACPOWER,
			ES8328_DACPOWER_ROUT2_ON, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Left Out 2", ES8328_DACPOWER,
			ES8328_DACPOWER_LOUT2_ON, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Out 1", ES8328_DACPOWER,
			ES8328_DACPOWER_ROUT1_ON, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Left Out 1", ES8328_DACPOWER,
			ES8328_DACPOWER_LOUT1_ON, 0, शून्य, 0),

	SND_SOC_DAPM_OUTPUT("LOUT1"),
	SND_SOC_DAPM_OUTPUT("ROUT1"),
	SND_SOC_DAPM_OUTPUT("LOUT2"),
	SND_SOC_DAPM_OUTPUT("ROUT2"),

	SND_SOC_DAPM_INPUT("LINPUT1"),
	SND_SOC_DAPM_INPUT("LINPUT2"),
	SND_SOC_DAPM_INPUT("RINPUT1"),
	SND_SOC_DAPM_INPUT("RINPUT2"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route es8328_dapm_routes[] = अणु

	अणु "Left Line Mux", "Line 1", "LINPUT1" पूर्ण,
	अणु "Left Line Mux", "Line 2", "LINPUT2" पूर्ण,
	अणु "Left Line Mux", "PGA", "Left PGA Mux" पूर्ण,
	अणु "Left Line Mux", "Differential", "Differential Mux" पूर्ण,

	अणु "Right Line Mux", "Line 1", "RINPUT1" पूर्ण,
	अणु "Right Line Mux", "Line 2", "RINPUT2" पूर्ण,
	अणु "Right Line Mux", "PGA", "Right PGA Mux" पूर्ण,
	अणु "Right Line Mux", "Differential", "Differential Mux" पूर्ण,

	अणु "Left PGA Mux", "Line 1", "LINPUT1" पूर्ण,
	अणु "Left PGA Mux", "Line 2", "LINPUT2" पूर्ण,
	अणु "Left PGA Mux", "Differential", "Differential Mux" पूर्ण,

	अणु "Right PGA Mux", "Line 1", "RINPUT1" पूर्ण,
	अणु "Right PGA Mux", "Line 2", "RINPUT2" पूर्ण,
	अणु "Right PGA Mux", "Differential", "Differential Mux" पूर्ण,

	अणु "Differential Mux", "Line 1", "LINPUT1" पूर्ण,
	अणु "Differential Mux", "Line 1", "RINPUT1" पूर्ण,
	अणु "Differential Mux", "Line 2", "LINPUT2" पूर्ण,
	अणु "Differential Mux", "Line 2", "RINPUT2" पूर्ण,

	अणु "Left ADC Mux", "Stereo", "Left PGA Mux" पूर्ण,
	अणु "Left ADC Mux", "Mono (Left)", "Left PGA Mux" पूर्ण,
	अणु "Left ADC Mux", "Digital Mono", "Left PGA Mux" पूर्ण,

	अणु "Right ADC Mux", "Stereo", "Right PGA Mux" पूर्ण,
	अणु "Right ADC Mux", "Mono (Right)", "Right PGA Mux" पूर्ण,
	अणु "Right ADC Mux", "Digital Mono", "Right PGA Mux" पूर्ण,

	अणु "Left ADC", शून्य, "Left ADC Mux" पूर्ण,
	अणु "Right ADC", शून्य, "Right ADC Mux" पूर्ण,

	अणु "ADC DIG", शून्य, "ADC STM" पूर्ण,
	अणु "ADC DIG", शून्य, "ADC Vref" पूर्ण,
	अणु "ADC DIG", शून्य, "ADC DLL" पूर्ण,

	अणु "Left ADC", शून्य, "ADC DIG" पूर्ण,
	अणु "Right ADC", शून्य, "ADC DIG" पूर्ण,

	अणु "Mic Bias", शून्य, "Mic Bias Gen" पूर्ण,

	अणु "Left Line Mux", "Line 1", "LINPUT1" पूर्ण,
	अणु "Left Line Mux", "Line 2", "LINPUT2" पूर्ण,
	अणु "Left Line Mux", "PGA", "Left PGA Mux" पूर्ण,
	अणु "Left Line Mux", "Differential", "Differential Mux" पूर्ण,

	अणु "Right Line Mux", "Line 1", "RINPUT1" पूर्ण,
	अणु "Right Line Mux", "Line 2", "RINPUT2" पूर्ण,
	अणु "Right Line Mux", "PGA", "Right PGA Mux" पूर्ण,
	अणु "Right Line Mux", "Differential", "Differential Mux" पूर्ण,

	अणु "Left Out 1", शून्य, "Left DAC" पूर्ण,
	अणु "Right Out 1", शून्य, "Right DAC" पूर्ण,
	अणु "Left Out 2", शून्य, "Left DAC" पूर्ण,
	अणु "Right Out 2", शून्य, "Right DAC" पूर्ण,

	अणु "Left Mixer", "Playback Switch", "Left DAC" पूर्ण,
	अणु "Left Mixer", "Left Bypass Switch", "Left Line Mux" पूर्ण,
	अणु "Left Mixer", "Right Playback Switch", "Right DAC" पूर्ण,
	अणु "Left Mixer", "Right Bypass Switch", "Right Line Mux" पूर्ण,

	अणु "Right Mixer", "Left Playback Switch", "Left DAC" पूर्ण,
	अणु "Right Mixer", "Left Bypass Switch", "Left Line Mux" पूर्ण,
	अणु "Right Mixer", "Playback Switch", "Right DAC" पूर्ण,
	अणु "Right Mixer", "Right Bypass Switch", "Right Line Mux" पूर्ण,

	अणु "DAC DIG", शून्य, "DAC STM" पूर्ण,
	अणु "DAC DIG", शून्य, "DAC Vref" पूर्ण,
	अणु "DAC DIG", शून्य, "DAC DLL" पूर्ण,

	अणु "Left DAC", शून्य, "DAC DIG" पूर्ण,
	अणु "Right DAC", शून्य, "DAC DIG" पूर्ण,

	अणु "Left Out 1", शून्य, "Left Mixer" पूर्ण,
	अणु "LOUT1", शून्य, "Left Out 1" पूर्ण,
	अणु "Right Out 1", शून्य, "Right Mixer" पूर्ण,
	अणु "ROUT1", शून्य, "Right Out 1" पूर्ण,

	अणु "Left Out 2", शून्य, "Left Mixer" पूर्ण,
	अणु "LOUT2", शून्य, "Left Out 2" पूर्ण,
	अणु "Right Out 2", शून्य, "Right Mixer" पूर्ण,
	अणु "ROUT2", शून्य, "Right Out 2" पूर्ण,
पूर्ण;

अटल पूर्णांक es8328_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	वापस snd_soc_component_update_bits(dai->component, ES8328_DACCONTROL3,
			ES8328_DACCONTROL3_DACMUTE,
			mute ? ES8328_DACCONTROL3_DACMUTE : 0);
पूर्ण

अटल पूर्णांक es8328_startup(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा es8328_priv *es8328 = snd_soc_component_get_drvdata(component);

	अगर (es8328->master && es8328->sysclk_स्थिरraपूर्णांकs)
		snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE,
				es8328->sysclk_स्थिरraपूर्णांकs);

	वापस 0;
पूर्ण

अटल पूर्णांक es8328_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा es8328_priv *es8328 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;
	पूर्णांक reg;
	पूर्णांक wl;
	पूर्णांक ratio;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		reg = ES8328_DACCONTROL2;
	अन्यथा
		reg = ES8328_ADCCONTROL5;

	अगर (es8328->master) अणु
		अगर (!es8328->sysclk_स्थिरraपूर्णांकs) अणु
			dev_err(component->dev, "No MCLK configured\n");
			वापस -EINVAL;
		पूर्ण

		क्रम (i = 0; i < es8328->sysclk_स्थिरraपूर्णांकs->count; i++)
			अगर (es8328->sysclk_स्थिरraपूर्णांकs->list[i] ==
			    params_rate(params))
				अवरोध;

		अगर (i == es8328->sysclk_स्थिरraपूर्णांकs->count) अणु
			dev_err(component->dev,
				"LRCLK %d unsupported with current clock\n",
				params_rate(params));
			वापस -EINVAL;
		पूर्ण
		ratio = es8328->mclk_ratios[i];
	पूर्ण अन्यथा अणु
		ratio = 0;
		es8328->mclkभाग2 = 0;
	पूर्ण

	snd_soc_component_update_bits(component, ES8328_MASTERMODE,
			ES8328_MASTERMODE_MCLKDIV2,
			es8328->mclkभाग2 ? ES8328_MASTERMODE_MCLKDIV2 : 0);

	चयन (params_width(params)) अणु
	हाल 16:
		wl = 3;
		अवरोध;
	हाल 18:
		wl = 2;
		अवरोध;
	हाल 20:
		wl = 1;
		अवरोध;
	हाल 24:
		wl = 0;
		अवरोध;
	हाल 32:
		wl = 4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		snd_soc_component_update_bits(component, ES8328_DACCONTROL1,
				ES8328_DACCONTROL1_DACWL_MASK,
				wl << ES8328_DACCONTROL1_DACWL_SHIFT);

		es8328->playback_fs = params_rate(params);
		es8328_set_deemph(component);
	पूर्ण अन्यथा
		snd_soc_component_update_bits(component, ES8328_ADCCONTROL4,
				ES8328_ADCCONTROL4_ADCWL_MASK,
				wl << ES8328_ADCCONTROL4_ADCWL_SHIFT);

	वापस snd_soc_component_update_bits(component, reg, ES8328_RATEMASK, ratio);
पूर्ण

अटल पूर्णांक es8328_set_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा es8328_priv *es8328 = snd_soc_component_get_drvdata(component);
	पूर्णांक mclkभाग2 = 0;

	चयन (freq) अणु
	हाल 0:
		es8328->sysclk_स्थिरraपूर्णांकs = शून्य;
		es8328->mclk_ratios = शून्य;
		अवरोध;
	हाल 22579200:
		mclkभाग2 = 1;
		fallthrough;
	हाल 11289600:
		es8328->sysclk_स्थिरraपूर्णांकs = &स्थिरraपूर्णांकs_11289;
		es8328->mclk_ratios = ratios_11289;
		अवरोध;
	हाल 24576000:
		mclkभाग2 = 1;
		fallthrough;
	हाल 12288000:
		es8328->sysclk_स्थिरraपूर्णांकs = &स्थिरraपूर्णांकs_12288;
		es8328->mclk_ratios = ratios_12288;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	es8328->mclkभाग2 = mclkभाग2;
	वापस 0;
पूर्ण

अटल पूर्णांक es8328_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा es8328_priv *es8328 = snd_soc_component_get_drvdata(component);
	u8 dac_mode = 0;
	u8 adc_mode = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* Master serial port mode, with BCLK generated स्वतःmatically */
		snd_soc_component_update_bits(component, ES8328_MASTERMODE,
				    ES8328_MASTERMODE_MSC,
				    ES8328_MASTERMODE_MSC);
		es8328->master = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* Slave serial port mode */
		snd_soc_component_update_bits(component, ES8328_MASTERMODE,
				    ES8328_MASTERMODE_MSC, 0);
		es8328->master = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		dac_mode |= ES8328_DACCONTROL1_DACFORMAT_I2S;
		adc_mode |= ES8328_ADCCONTROL4_ADCFORMAT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		dac_mode |= ES8328_DACCONTROL1_DACFORMAT_RJUST;
		adc_mode |= ES8328_ADCCONTROL4_ADCFORMAT_RJUST;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		dac_mode |= ES8328_DACCONTROL1_DACFORMAT_LJUST;
		adc_mode |= ES8328_ADCCONTROL4_ADCFORMAT_LJUST;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	अगर ((fmt & SND_SOC_DAIFMT_INV_MASK) != SND_SOC_DAIFMT_NB_NF)
		वापस -EINVAL;

	snd_soc_component_update_bits(component, ES8328_DACCONTROL1,
			ES8328_DACCONTROL1_DACFORMAT_MASK, dac_mode);
	snd_soc_component_update_bits(component, ES8328_ADCCONTROL4,
			ES8328_ADCCONTROL4_ADCFORMAT_MASK, adc_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक es8328_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		/* VREF, VMID=2x50k, digital enabled */
		snd_soc_component_ग_लिखो(component, ES8328_CHIPPOWER, 0);
		snd_soc_component_update_bits(component, ES8328_CONTROL1,
				ES8328_CONTROL1_VMIDSEL_MASK |
				ES8328_CONTROL1_ENREF,
				ES8328_CONTROL1_VMIDSEL_50k |
				ES8328_CONTROL1_ENREF);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			snd_soc_component_update_bits(component, ES8328_CONTROL1,
					ES8328_CONTROL1_VMIDSEL_MASK |
					ES8328_CONTROL1_ENREF,
					ES8328_CONTROL1_VMIDSEL_5k |
					ES8328_CONTROL1_ENREF);

			/* Charge caps */
			msleep(100);
		पूर्ण

		snd_soc_component_ग_लिखो(component, ES8328_CONTROL2,
				ES8328_CONTROL2_OVERCURRENT_ON |
				ES8328_CONTROL2_THERMAL_SHUTDOWN_ON);

		/* VREF, VMID=2*500k, digital stopped */
		snd_soc_component_update_bits(component, ES8328_CONTROL1,
				ES8328_CONTROL1_VMIDSEL_MASK |
				ES8328_CONTROL1_ENREF,
				ES8328_CONTROL1_VMIDSEL_500k |
				ES8328_CONTROL1_ENREF);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, ES8328_CONTROL1,
				ES8328_CONTROL1_VMIDSEL_MASK |
				ES8328_CONTROL1_ENREF,
				0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops es8328_dai_ops = अणु
	.startup	= es8328_startup,
	.hw_params	= es8328_hw_params,
	.mute_stream	= es8328_mute,
	.set_sysclk	= es8328_set_sysclk,
	.set_fmt	= es8328_set_dai_fmt,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver es8328_dai = अणु
	.name = "es8328-hifi-analog",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = ES8328_RATES,
		.क्रमmats = ES8328_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = ES8328_RATES,
		.क्रमmats = ES8328_FORMATS,
	पूर्ण,
	.ops = &es8328_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक es8328_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा es8328_priv *es8328;
	पूर्णांक ret;

	es8328 = snd_soc_component_get_drvdata(component);

	clk_disable_unprepare(es8328->clk);

	ret = regulator_bulk_disable(ARRAY_SIZE(es8328->supplies),
			es8328->supplies);
	अगर (ret) अणु
		dev_err(component->dev, "unable to disable regulators\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक es8328_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा regmap *regmap = dev_get_regmap(component->dev, शून्य);
	काष्ठा es8328_priv *es8328;
	पूर्णांक ret;

	es8328 = snd_soc_component_get_drvdata(component);

	ret = clk_prepare_enable(es8328->clk);
	अगर (ret) अणु
		dev_err(component->dev, "unable to enable clock\n");
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(es8328->supplies),
					es8328->supplies);
	अगर (ret) अणु
		dev_err(component->dev, "unable to enable regulators\n");
		वापस ret;
	पूर्ण

	regcache_mark_dirty(regmap);
	ret = regcache_sync(regmap);
	अगर (ret) अणु
		dev_err(component->dev, "unable to sync regcache\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक es8328_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा es8328_priv *es8328;
	पूर्णांक ret;

	es8328 = snd_soc_component_get_drvdata(component);

	ret = regulator_bulk_enable(ARRAY_SIZE(es8328->supplies),
					es8328->supplies);
	अगर (ret) अणु
		dev_err(component->dev, "unable to enable regulators\n");
		वापस ret;
	पूर्ण

	/* Setup घड़ीs */
	es8328->clk = devm_clk_get(component->dev, शून्य);
	अगर (IS_ERR(es8328->clk)) अणु
		dev_err(component->dev, "codec clock missing or invalid\n");
		ret = PTR_ERR(es8328->clk);
		जाओ clk_fail;
	पूर्ण

	ret = clk_prepare_enable(es8328->clk);
	अगर (ret) अणु
		dev_err(component->dev, "unable to prepare codec clk\n");
		जाओ clk_fail;
	पूर्ण

	वापस 0;

clk_fail:
	regulator_bulk_disable(ARRAY_SIZE(es8328->supplies),
			       es8328->supplies);
	वापस ret;
पूर्ण

अटल व्योम es8328_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा es8328_priv *es8328;

	es8328 = snd_soc_component_get_drvdata(component);

	clk_disable_unprepare(es8328->clk);

	regulator_bulk_disable(ARRAY_SIZE(es8328->supplies),
			       es8328->supplies);
पूर्ण

स्थिर काष्ठा regmap_config es8328_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= ES8328_REG_MAX,
	.cache_type	= REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;
EXPORT_SYMBOL_GPL(es8328_regmap_config);

अटल स्थिर काष्ठा snd_soc_component_driver es8328_component_driver = अणु
	.probe			= es8328_component_probe,
	.हटाओ			= es8328_हटाओ,
	.suspend		= es8328_suspend,
	.resume			= es8328_resume,
	.set_bias_level		= es8328_set_bias_level,
	.controls		= es8328_snd_controls,
	.num_controls		= ARRAY_SIZE(es8328_snd_controls),
	.dapm_widमाला_लो		= es8328_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(es8328_dapm_widमाला_लो),
	.dapm_routes		= es8328_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(es8328_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

पूर्णांक es8328_probe(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	काष्ठा es8328_priv *es8328;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	es8328 = devm_kzalloc(dev, माप(*es8328), GFP_KERNEL);
	अगर (es8328 == शून्य)
		वापस -ENOMEM;

	es8328->regmap = regmap;

	क्रम (i = 0; i < ARRAY_SIZE(es8328->supplies); i++)
		es8328->supplies[i].supply = supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(es8328->supplies),
				es8328->supplies);
	अगर (ret) अणु
		dev_err(dev, "unable to get regulators\n");
		वापस ret;
	पूर्ण

	dev_set_drvdata(dev, es8328);

	वापस devm_snd_soc_रेजिस्टर_component(dev,
			&es8328_component_driver, &es8328_dai, 1);
पूर्ण
EXPORT_SYMBOL_GPL(es8328_probe);

MODULE_DESCRIPTION("ASoC ES8328 driver");
MODULE_AUTHOR("Sean Cross <xobs@kosagi.com>");
MODULE_LICENSE("GPL");
