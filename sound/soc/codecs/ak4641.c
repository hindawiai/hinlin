<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ak4641.c  --  AK4641 ALSA Soc Audio driver
 *
 * Copyright (C) 2008 Harald Welte <laक्रमge@gnufiish.org>
 * Copyright (C) 2011 Dmitry Artamonow <mad_soft@inbox.ru>
 *
 * Based on ak4535.c by Riअक्षरd Purdie
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/ak4641.h>

/* AK4641 रेजिस्टर space */
#घोषणा AK4641_PM1		0x00
#घोषणा AK4641_PM2		0x01
#घोषणा AK4641_SIG1		0x02
#घोषणा AK4641_SIG2		0x03
#घोषणा AK4641_MODE1		0x04
#घोषणा AK4641_MODE2		0x05
#घोषणा AK4641_DAC		0x06
#घोषणा AK4641_MIC		0x07
#घोषणा AK4641_TIMER		0x08
#घोषणा AK4641_ALC1		0x09
#घोषणा AK4641_ALC2		0x0a
#घोषणा AK4641_PGA		0x0b
#घोषणा AK4641_LATT		0x0c
#घोषणा AK4641_RATT		0x0d
#घोषणा AK4641_VOL		0x0e
#घोषणा AK4641_STATUS		0x0f
#घोषणा AK4641_EQLO		0x10
#घोषणा AK4641_EQMID		0x11
#घोषणा AK4641_EQHI		0x12
#घोषणा AK4641_BTIF		0x13

/* codec निजी data */
काष्ठा ak4641_priv अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक sysclk;
	पूर्णांक deemph;
	पूर्णांक playback_fs;
पूर्ण;

/*
 * ak4641 रेजिस्टर cache
 */
अटल स्थिर काष्ठा reg_शेष ak4641_reg_शेषs[] = अणु
	अणु  0, 0x00 पूर्ण, अणु  1, 0x80 पूर्ण, अणु  2, 0x00 पूर्ण, अणु  3, 0x80 पूर्ण,
	अणु  4, 0x02 पूर्ण, अणु  5, 0x00 पूर्ण, अणु  6, 0x11 पूर्ण, अणु  7, 0x05 पूर्ण,
	अणु  8, 0x00 पूर्ण, अणु  9, 0x00 पूर्ण, अणु 10, 0x36 पूर्ण, अणु 11, 0x10 पूर्ण,
	अणु 12, 0x00 पूर्ण, अणु 13, 0x00 पूर्ण, अणु 14, 0x57 पूर्ण, अणु 15, 0x00 पूर्ण,
	अणु 16, 0x88 पूर्ण, अणु 17, 0x88 पूर्ण, अणु 18, 0x08 पूर्ण, अणु 19, 0x08 पूर्ण
पूर्ण;

अटल स्थिर पूर्णांक deemph_settings[] = अणु44100, 0, 48000, 32000पूर्ण;

अटल पूर्णांक ak4641_set_deemph(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ak4641_priv *ak4641 = snd_soc_component_get_drvdata(component);
	पूर्णांक i, best = 0;

	क्रम (i = 0 ; i < ARRAY_SIZE(deemph_settings); i++) अणु
		/* अगर deemphasis is on, select the nearest available rate */
		अगर (ak4641->deemph && deemph_settings[i] != 0 &&
		    असल(deemph_settings[i] - ak4641->playback_fs) <
		    असल(deemph_settings[best] - ak4641->playback_fs))
			best = i;

		अगर (!ak4641->deemph && deemph_settings[i] == 0)
			best = i;
	पूर्ण

	dev_dbg(component->dev, "Set deemphasis %d\n", best);

	वापस snd_soc_component_update_bits(component, AK4641_DAC, 0x3, best);
पूर्ण

अटल पूर्णांक ak4641_put_deemph(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा ak4641_priv *ak4641 = snd_soc_component_get_drvdata(component);
	पूर्णांक deemph = ucontrol->value.पूर्णांकeger.value[0];

	अगर (deemph > 1)
		वापस -EINVAL;

	ak4641->deemph = deemph;

	वापस ak4641_set_deemph(component);
पूर्ण

अटल पूर्णांक ak4641_get_deemph(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा ak4641_priv *ak4641 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = ak4641->deemph;
	वापस 0;
पूर्ण;

अटल स्थिर अक्षर *ak4641_mono_out[] = अणु"(L + R)/2", "Hi-Z"पूर्ण;
अटल स्थिर अक्षर *ak4641_hp_out[] = अणु"Stereo", "Mono"पूर्ण;
अटल स्थिर अक्षर *ak4641_mic_select[] = अणु"Internal", "External"पूर्ण;
अटल स्थिर अक्षर *ak4641_mic_or_dac[] = अणु"Microphone", "Voice DAC"पूर्ण;


अटल स्थिर DECLARE_TLV_DB_SCALE(mono_gain_tlv, -1700, 2300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_boost_tlv, 0, 2000, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(eq_tlv, -1050, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(master_tlv, -12750, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_stereo_sidetone_tlv, -2700, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_mono_sidetone_tlv, -400, 400, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(capture_tlv, -800, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(alc_tlv, -800, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(aux_in_tlv, -2100, 300, 0);


अटल SOC_ENUM_SINGLE_DECL(ak4641_mono_out_क्रमागत,
			    AK4641_SIG1, 6, ak4641_mono_out);
अटल SOC_ENUM_SINGLE_DECL(ak4641_hp_out_क्रमागत,
			    AK4641_MODE2, 2, ak4641_hp_out);
अटल SOC_ENUM_SINGLE_DECL(ak4641_mic_select_क्रमागत,
			    AK4641_MIC, 1, ak4641_mic_select);
अटल SOC_ENUM_SINGLE_DECL(ak4641_mic_or_dac_क्रमागत,
			    AK4641_BTIF, 4, ak4641_mic_or_dac);

अटल स्थिर काष्ठा snd_kcontrol_new ak4641_snd_controls[] = अणु
	SOC_ENUM("Mono 1 Output", ak4641_mono_out_क्रमागत),
	SOC_SINGLE_TLV("Mono 1 Gain Volume", AK4641_SIG1, 7, 1, 1,
							mono_gain_tlv),
	SOC_ENUM("Headphone Output", ak4641_hp_out_क्रमागत),
	SOC_SINGLE_BOOL_EXT("Playback Deemphasis Switch", 0,
					ak4641_get_deemph, ak4641_put_deemph),

	SOC_SINGLE_TLV("Mic Boost Volume", AK4641_MIC, 0, 1, 0, mic_boost_tlv),

	SOC_SINGLE("ALC Operation Time", AK4641_TIMER, 0, 3, 0),
	SOC_SINGLE("ALC Recovery Time", AK4641_TIMER, 2, 3, 0),
	SOC_SINGLE("ALC ZC Time", AK4641_TIMER, 4, 3, 0),

	SOC_SINGLE("ALC 1 Switch", AK4641_ALC1, 5, 1, 0),

	SOC_SINGLE_TLV("ALC Volume", AK4641_ALC2, 0, 71, 0, alc_tlv),
	SOC_SINGLE("Left Out Enable Switch", AK4641_SIG2, 1, 1, 0),
	SOC_SINGLE("Right Out Enable Switch", AK4641_SIG2, 0, 1, 0),

	SOC_SINGLE_TLV("Capture Volume", AK4641_PGA, 0, 71, 0, capture_tlv),

	SOC_DOUBLE_R_TLV("Master Playback Volume", AK4641_LATT,
				AK4641_RATT, 0, 255, 1, master_tlv),

	SOC_SINGLE_TLV("AUX In Volume", AK4641_VOL, 0, 15, 0, aux_in_tlv),

	SOC_SINGLE("Equalizer Switch", AK4641_DAC, 2, 1, 0),
	SOC_SINGLE_TLV("EQ1 100 Hz Volume", AK4641_EQLO, 0, 15, 1, eq_tlv),
	SOC_SINGLE_TLV("EQ2 250 Hz Volume", AK4641_EQLO, 4, 15, 1, eq_tlv),
	SOC_SINGLE_TLV("EQ3 1 kHz Volume", AK4641_EQMID, 0, 15, 1, eq_tlv),
	SOC_SINGLE_TLV("EQ4 3.5 kHz Volume", AK4641_EQMID, 4, 15, 1, eq_tlv),
	SOC_SINGLE_TLV("EQ5 10 kHz Volume", AK4641_EQHI, 0, 15, 1, eq_tlv),
पूर्ण;

/* Mono 1 Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new ak4641_mono1_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_TLV("Mic Mono Sidetone Volume", AK4641_VOL, 7, 1, 0,
						mic_mono_sidetone_tlv),
	SOC_DAPM_SINGLE("Mic Mono Sidetone Switch", AK4641_SIG1, 4, 1, 0),
	SOC_DAPM_SINGLE("Mono Playback Switch", AK4641_SIG1, 5, 1, 0),
पूर्ण;

/* Stereo Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new ak4641_stereo_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_TLV("Mic Sidetone Volume", AK4641_VOL, 4, 7, 0,
						mic_stereo_sidetone_tlv),
	SOC_DAPM_SINGLE("Mic Sidetone Switch", AK4641_SIG2, 4, 1, 0),
	SOC_DAPM_SINGLE("Playback Switch", AK4641_SIG2, 7, 1, 0),
	SOC_DAPM_SINGLE("Aux Bypass Switch", AK4641_SIG2, 5, 1, 0),
पूर्ण;

/* Input Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new ak4641_input_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Mic Capture Switch", AK4641_MIC, 2, 1, 0),
	SOC_DAPM_SINGLE("Aux Capture Switch", AK4641_MIC, 5, 1, 0),
पूर्ण;

/* Mic mux */
अटल स्थिर काष्ठा snd_kcontrol_new ak4641_mic_mux_control =
	SOC_DAPM_ENUM("Mic Select", ak4641_mic_select_क्रमागत);

/* Input mux */
अटल स्थिर काष्ठा snd_kcontrol_new ak4641_input_mux_control =
	SOC_DAPM_ENUM("Input Select", ak4641_mic_or_dac_क्रमागत);

/* mono 2 चयन */
अटल स्थिर काष्ठा snd_kcontrol_new ak4641_mono2_control =
	SOC_DAPM_SINGLE("Switch", AK4641_SIG1, 0, 1, 0);

/* ak4641 dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget ak4641_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIXER("Stereo Mixer", SND_SOC_NOPM, 0, 0,
		&ak4641_stereo_mixer_controls[0],
		ARRAY_SIZE(ak4641_stereo_mixer_controls)),
	SND_SOC_DAPM_MIXER("Mono1 Mixer", SND_SOC_NOPM, 0, 0,
		&ak4641_mono1_mixer_controls[0],
		ARRAY_SIZE(ak4641_mono1_mixer_controls)),
	SND_SOC_DAPM_MIXER("Input Mixer", SND_SOC_NOPM, 0, 0,
		&ak4641_input_mixer_controls[0],
		ARRAY_SIZE(ak4641_input_mixer_controls)),
	SND_SOC_DAPM_MUX("Mic Mux", SND_SOC_NOPM, 0, 0,
		&ak4641_mic_mux_control),
	SND_SOC_DAPM_MUX("Input Mux", SND_SOC_NOPM, 0, 0,
		&ak4641_input_mux_control),
	SND_SOC_DAPM_SWITCH("Mono 2 Enable", SND_SOC_NOPM, 0, 0,
		&ak4641_mono2_control),

	SND_SOC_DAPM_OUTPUT("LOUT"),
	SND_SOC_DAPM_OUTPUT("ROUT"),
	SND_SOC_DAPM_OUTPUT("MOUT1"),
	SND_SOC_DAPM_OUTPUT("MOUT2"),
	SND_SOC_DAPM_OUTPUT("MICOUT"),

	SND_SOC_DAPM_ADC("ADC", "HiFi Capture", AK4641_PM1, 0, 0),
	SND_SOC_DAPM_PGA("Mic", AK4641_PM1, 1, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("AUX In", AK4641_PM1, 2, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Mono Out", AK4641_PM1, 3, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Line Out", AK4641_PM1, 4, 0, शून्य, 0),

	SND_SOC_DAPM_DAC("DAC", "HiFi Playback", AK4641_PM2, 0, 0),
	SND_SOC_DAPM_PGA("Mono Out 2", AK4641_PM2, 3, 0, शून्य, 0),

	SND_SOC_DAPM_ADC("Voice ADC", "Voice Capture", AK4641_BTIF, 0, 0),
	SND_SOC_DAPM_DAC("Voice DAC", "Voice Playback", AK4641_BTIF, 1, 0),

	SND_SOC_DAPM_MICBIAS("Mic Int Bias", AK4641_MIC, 3, 0),
	SND_SOC_DAPM_MICBIAS("Mic Ext Bias", AK4641_MIC, 4, 0),

	SND_SOC_DAPM_INPUT("MICIN"),
	SND_SOC_DAPM_INPUT("MICEXT"),
	SND_SOC_DAPM_INPUT("AUX"),
	SND_SOC_DAPM_INPUT("AIN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ak4641_audio_map[] = अणु
	/* Stereo Mixer */
	अणु"Stereo Mixer", "Playback Switch", "DAC"पूर्ण,
	अणु"Stereo Mixer", "Mic Sidetone Switch", "Input Mux"पूर्ण,
	अणु"Stereo Mixer", "Aux Bypass Switch", "AUX In"पूर्ण,

	/* Mono 1 Mixer */
	अणु"Mono1 Mixer", "Mic Mono Sidetone Switch", "Input Mux"पूर्ण,
	अणु"Mono1 Mixer", "Mono Playback Switch", "DAC"पूर्ण,

	/* Mic */
	अणु"Mic", शून्य, "AIN"पूर्ण,
	अणु"Mic Mux", "Internal", "Mic Int Bias"पूर्ण,
	अणु"Mic Mux", "External", "Mic Ext Bias"पूर्ण,
	अणु"Mic Int Bias", शून्य, "MICIN"पूर्ण,
	अणु"Mic Ext Bias", शून्य, "MICEXT"पूर्ण,
	अणु"MICOUT", शून्य, "Mic Mux"पूर्ण,

	/* Input Mux */
	अणु"Input Mux", "Microphone", "Mic"पूर्ण,
	अणु"Input Mux", "Voice DAC", "Voice DAC"पूर्ण,

	/* Line Out */
	अणु"LOUT", शून्य, "Line Out"पूर्ण,
	अणु"ROUT", शून्य, "Line Out"पूर्ण,
	अणु"Line Out", शून्य, "Stereo Mixer"पूर्ण,

	/* Mono 1 Out */
	अणु"MOUT1", शून्य, "Mono Out"पूर्ण,
	अणु"Mono Out", शून्य, "Mono1 Mixer"पूर्ण,

	/* Mono 2 Out */
	अणु"MOUT2", शून्य, "Mono 2 Enable"पूर्ण,
	अणु"Mono 2 Enable", "Switch", "Mono Out 2"पूर्ण,
	अणु"Mono Out 2", शून्य, "Stereo Mixer"पूर्ण,

	अणु"Voice ADC", शून्य, "Mono 2 Enable"पूर्ण,

	/* Aux In */
	अणु"AUX In", शून्य, "AUX"पूर्ण,

	/* ADC */
	अणु"ADC", शून्य, "Input Mixer"पूर्ण,
	अणु"Input Mixer", "Mic Capture Switch", "Mic"पूर्ण,
	अणु"Input Mixer", "Aux Capture Switch", "AUX In"पूर्ण,
पूर्ण;

अटल पूर्णांक ak4641_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
	पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा ak4641_priv *ak4641 = snd_soc_component_get_drvdata(component);

	ak4641->sysclk = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक ak4641_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak4641_priv *ak4641 = snd_soc_component_get_drvdata(component);
	पूर्णांक rate = params_rate(params), fs = 256;
	u8 mode2;

	अगर (rate)
		fs = ak4641->sysclk / rate;
	अन्यथा
		वापस -EINVAL;

	/* set fs */
	चयन (fs) अणु
	हाल 1024:
		mode2 = (0x2 << 5);
		अवरोध;
	हाल 512:
		mode2 = (0x1 << 5);
		अवरोध;
	हाल 256:
		mode2 = (0x0 << 5);
		अवरोध;
	शेष:
		dev_err(component->dev, "Error: unsupported fs=%d\n", fs);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AK4641_MODE2, (0x3 << 5), mode2);

	/* Update de-emphasis filter क्रम the new rate */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ak4641->playback_fs = rate;
		ak4641_set_deemph(component);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ak4641_pcm_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
				  अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u8 btअगर;
	पूर्णांक ret;

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		btअगर = (0x3 << 5);
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		btअगर = (0x2 << 5);
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:	/* MSB after FRM */
		btअगर = (0x0 << 5);
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:	/* MSB during FRM */
		btअगर = (0x1 << 5);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(component, AK4641_BTIF, (0x3 << 5), btअगर);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ak4641_i2s_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u8 mode1 = 0;

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		mode1 = 0x02;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		mode1 = 0x01;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस snd_soc_component_ग_लिखो(component, AK4641_MODE1, mode1);
पूर्ण

अटल पूर्णांक ak4641_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	वापस snd_soc_component_update_bits(component, AK4641_DAC, 0x20, mute ? 0x20 : 0);
पूर्ण

अटल पूर्णांक ak4641_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा ak4641_priv *ak4641 = snd_soc_component_get_drvdata(component);
	काष्ठा ak4641_platक्रमm_data *pdata = component->dev->platक्रमm_data;
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		/* unmute */
		snd_soc_component_update_bits(component, AK4641_DAC, 0x20, 0);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		/* mute */
		snd_soc_component_update_bits(component, AK4641_DAC, 0x20, 0x20);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			अगर (pdata && gpio_is_valid(pdata->gpio_घातer))
				gpio_set_value(pdata->gpio_घातer, 1);
			mdelay(1);
			अगर (pdata && gpio_is_valid(pdata->gpio_npdn))
				gpio_set_value(pdata->gpio_npdn, 1);
			mdelay(1);

			ret = regcache_sync(ak4641->regmap);
			अगर (ret) अणु
				dev_err(component->dev,
					"Failed to sync cache: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		snd_soc_component_update_bits(component, AK4641_PM1, 0x80, 0x80);
		snd_soc_component_update_bits(component, AK4641_PM2, 0x80, 0);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, AK4641_PM1, 0x80, 0);
		अगर (pdata && gpio_is_valid(pdata->gpio_npdn))
			gpio_set_value(pdata->gpio_npdn, 0);
		अगर (pdata && gpio_is_valid(pdata->gpio_घातer))
			gpio_set_value(pdata->gpio_घातer, 0);
		regcache_mark_dirty(ak4641->regmap);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा AK4641_RATES	(SNDRV_PCM_RATE_8000_48000)
#घोषणा AK4641_RATES_BT (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
			 SNDRV_PCM_RATE_16000)
#घोषणा AK4641_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops ak4641_i2s_dai_ops = अणु
	.hw_params    = ak4641_i2s_hw_params,
	.set_fmt      = ak4641_i2s_set_dai_fmt,
	.mute_stream  = ak4641_mute,
	.set_sysclk   = ak4641_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops ak4641_pcm_dai_ops = अणु
	.hw_params    = शून्य, /* rates are controlled by BT chip */
	.set_fmt      = ak4641_pcm_set_dai_fmt,
	.mute_stream  = ak4641_mute,
	.set_sysclk   = ak4641_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ak4641_dai[] = अणु
अणु
	.name = "ak4641-hifi",
	.id = 1,
	.playback = अणु
		.stream_name = "HiFi Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = AK4641_RATES,
		.क्रमmats = AK4641_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "HiFi Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = AK4641_RATES,
		.क्रमmats = AK4641_FORMATS,
	पूर्ण,
	.ops = &ak4641_i2s_dai_ops,
	.symmetric_rate = 1,
पूर्ण,
अणु
	.name = "ak4641-voice",
	.id = 1,
	.playback = अणु
		.stream_name = "Voice Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = AK4641_RATES_BT,
		.क्रमmats = AK4641_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Voice Capture",
		.channels_min = 1,
		.channels_max = 1,
		.rates = AK4641_RATES_BT,
		.क्रमmats = AK4641_FORMATS,
	पूर्ण,
	.ops = &ak4641_pcm_dai_ops,
	.symmetric_rate = 1,
पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_ak4641 = अणु
	.controls		= ak4641_snd_controls,
	.num_controls		= ARRAY_SIZE(ak4641_snd_controls),
	.dapm_widमाला_लो		= ak4641_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ak4641_dapm_widमाला_लो),
	.dapm_routes		= ak4641_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(ak4641_audio_map),
	.set_bias_level		= ak4641_set_bias_level,
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ak4641_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = AK4641_BTIF,
	.reg_शेषs = ak4641_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(ak4641_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक ak4641_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ak4641_platक्रमm_data *pdata = i2c->dev.platक्रमm_data;
	काष्ठा ak4641_priv *ak4641;
	पूर्णांक ret;

	ak4641 = devm_kzalloc(&i2c->dev, माप(काष्ठा ak4641_priv),
			      GFP_KERNEL);
	अगर (!ak4641)
		वापस -ENOMEM;

	ak4641->regmap = devm_regmap_init_i2c(i2c, &ak4641_regmap);
	अगर (IS_ERR(ak4641->regmap))
		वापस PTR_ERR(ak4641->regmap);

	अगर (pdata) अणु
		अगर (gpio_is_valid(pdata->gpio_घातer)) अणु
			ret = gpio_request_one(pdata->gpio_घातer,
					GPIOF_OUT_INIT_LOW, "ak4641 power");
			अगर (ret)
				जाओ err_out;
		पूर्ण
		अगर (gpio_is_valid(pdata->gpio_npdn)) अणु
			ret = gpio_request_one(pdata->gpio_npdn,
					GPIOF_OUT_INIT_LOW, "ak4641 npdn");
			अगर (ret)
				जाओ err_gpio;

			udelay(1); /* > 150 ns */
			gpio_set_value(pdata->gpio_npdn, 1);
		पूर्ण
	पूर्ण

	i2c_set_clientdata(i2c, ak4641);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				&soc_component_dev_ak4641,
				ak4641_dai, ARRAY_SIZE(ak4641_dai));
	अगर (ret != 0)
		जाओ err_gpio2;

	वापस 0;

err_gpio2:
	अगर (pdata) अणु
		अगर (gpio_is_valid(pdata->gpio_घातer))
			gpio_set_value(pdata->gpio_घातer, 0);
		अगर (gpio_is_valid(pdata->gpio_npdn))
			gpio_मुक्त(pdata->gpio_npdn);
	पूर्ण
err_gpio:
	अगर (pdata && gpio_is_valid(pdata->gpio_घातer))
		gpio_मुक्त(pdata->gpio_घातer);
err_out:
	वापस ret;
पूर्ण

अटल पूर्णांक ak4641_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा ak4641_platक्रमm_data *pdata = i2c->dev.platक्रमm_data;

	अगर (pdata) अणु
		अगर (gpio_is_valid(pdata->gpio_घातer)) अणु
			gpio_set_value(pdata->gpio_घातer, 0);
			gpio_मुक्त(pdata->gpio_घातer);
		पूर्ण
		अगर (gpio_is_valid(pdata->gpio_npdn))
			gpio_मुक्त(pdata->gpio_npdn);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ak4641_i2c_id[] = अणु
	अणु "ak4641", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ak4641_i2c_id);

अटल काष्ठा i2c_driver ak4641_i2c_driver = अणु
	.driver = अणु
		.name = "ak4641",
	पूर्ण,
	.probe =    ak4641_i2c_probe,
	.हटाओ =   ak4641_i2c_हटाओ,
	.id_table = ak4641_i2c_id,
पूर्ण;

module_i2c_driver(ak4641_i2c_driver);

MODULE_DESCRIPTION("SoC AK4641 driver");
MODULE_AUTHOR("Harald Welte <laforge@gnufiish.org>");
MODULE_LICENSE("GPL");
