<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम ADAU1381/ADAU1781 codec
 *
 * Copyright 2011-2013 Analog Devices Inc.
 * Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <linux/platक्रमm_data/adau17x1.h>

#समावेश "adau17x1.h"
#समावेश "adau1781.h"

#घोषणा ADAU1781_DMIC_BEEP_CTRL		0x4008
#घोषणा ADAU1781_LEFT_PGA		0x400e
#घोषणा ADAU1781_RIGHT_PGA		0x400f
#घोषणा ADAU1781_LEFT_PLAYBACK_MIXER	0x401c
#घोषणा ADAU1781_RIGHT_PLAYBACK_MIXER	0x401e
#घोषणा ADAU1781_MONO_PLAYBACK_MIXER	0x401f
#घोषणा ADAU1781_LEFT_LINEOUT		0x4025
#घोषणा ADAU1781_RIGHT_LINEOUT		0x4026
#घोषणा ADAU1781_SPEAKER		0x4027
#घोषणा ADAU1781_BEEP_ZC		0x4028
#घोषणा ADAU1781_DEJITTER		0x4032
#घोषणा ADAU1781_DIG_PWDN0		0x4080
#घोषणा ADAU1781_DIG_PWDN1		0x4081

#घोषणा ADAU1781_INPUT_DIFFERNTIAL BIT(3)

#घोषणा ADAU1381_FIRMWARE "adau1381.bin"
#घोषणा ADAU1781_FIRMWARE "adau1781.bin"

अटल स्थिर काष्ठा reg_शेष adau1781_reg_शेषs[] = अणु
	अणु ADAU1781_DMIC_BEEP_CTRL,		0x00 पूर्ण,
	अणु ADAU1781_LEFT_PGA,			0xc7 पूर्ण,
	अणु ADAU1781_RIGHT_PGA,			0xc7 पूर्ण,
	अणु ADAU1781_LEFT_PLAYBACK_MIXER,		0x00 पूर्ण,
	अणु ADAU1781_RIGHT_PLAYBACK_MIXER,	0x00 पूर्ण,
	अणु ADAU1781_MONO_PLAYBACK_MIXER,		0x00 पूर्ण,
	अणु ADAU1781_LEFT_LINEOUT,		0x00 पूर्ण,
	अणु ADAU1781_RIGHT_LINEOUT,		0x00 पूर्ण,
	अणु ADAU1781_SPEAKER,			0x00 पूर्ण,
	अणु ADAU1781_BEEP_ZC,			0x19 पूर्ण,
	अणु ADAU1781_DEJITTER,			0x60 पूर्ण,
	अणु ADAU1781_DIG_PWDN1,			0x0c पूर्ण,
	अणु ADAU1781_DIG_PWDN1,			0x00 पूर्ण,
	अणु ADAU17X1_CLOCK_CONTROL,		0x00 पूर्ण,
	अणु ADAU17X1_PLL_CONTROL,			0x00 पूर्ण,
	अणु ADAU17X1_REC_POWER_MGMT,		0x00 पूर्ण,
	अणु ADAU17X1_MICBIAS,			0x04 पूर्ण,
	अणु ADAU17X1_SERIAL_PORT0,		0x00 पूर्ण,
	अणु ADAU17X1_SERIAL_PORT1,		0x00 पूर्ण,
	अणु ADAU17X1_CONVERTER0,			0x00 पूर्ण,
	अणु ADAU17X1_CONVERTER1,			0x00 पूर्ण,
	अणु ADAU17X1_LEFT_INPUT_DIGITAL_VOL,	0x00 पूर्ण,
	अणु ADAU17X1_RIGHT_INPUT_DIGITAL_VOL,	0x00 पूर्ण,
	अणु ADAU17X1_ADC_CONTROL,			0x00 पूर्ण,
	अणु ADAU17X1_PLAY_POWER_MGMT,		0x00 पूर्ण,
	अणु ADAU17X1_DAC_CONTROL0,		0x00 पूर्ण,
	अणु ADAU17X1_DAC_CONTROL1,		0x00 पूर्ण,
	अणु ADAU17X1_DAC_CONTROL2,		0x00 पूर्ण,
	अणु ADAU17X1_SERIAL_PORT_PAD,		0x00 पूर्ण,
	अणु ADAU17X1_CONTROL_PORT_PAD0,		0x00 पूर्ण,
	अणु ADAU17X1_CONTROL_PORT_PAD1,		0x00 पूर्ण,
	अणु ADAU17X1_DSP_SAMPLING_RATE,		0x01 पूर्ण,
	अणु ADAU17X1_SERIAL_INPUT_ROUTE,		0x00 पूर्ण,
	अणु ADAU17X1_SERIAL_OUTPUT_ROUTE,		0x00 पूर्ण,
	अणु ADAU17X1_DSP_ENABLE,			0x00 पूर्ण,
	अणु ADAU17X1_DSP_RUN,			0x00 पूर्ण,
	अणु ADAU17X1_SERIAL_SAMPLING_RATE,	0x00 पूर्ण,
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(adau1781_speaker_tlv, 0, 200, 0);

अटल स्थिर DECLARE_TLV_DB_RANGE(adau1781_pga_tlv,
	0, 1, TLV_DB_SCALE_ITEM(0, 600, 0),
	2, 3, TLV_DB_SCALE_ITEM(1000, 400, 0),
	4, 4, TLV_DB_SCALE_ITEM(1700, 0, 0),
	5, 7, TLV_DB_SCALE_ITEM(2000, 600, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(adau1781_beep_tlv,
	0, 1, TLV_DB_SCALE_ITEM(0, 600, 0),
	2, 3, TLV_DB_SCALE_ITEM(1000, 400, 0),
	4, 4, TLV_DB_SCALE_ITEM(-2300, 0, 0),
	5, 7, TLV_DB_SCALE_ITEM(2000, 600, 0)
);

अटल स्थिर DECLARE_TLV_DB_SCALE(adau1781_sidetone_tlv, -1800, 300, 1);

अटल स्थिर अक्षर * स्थिर adau1781_speaker_bias_select_text[] = अणु
	"Normal operation", "Power saving", "Enhanced performance",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1781_bias_select_text[] = अणु
	"Normal operation", "Extreme power saving", "Power saving",
	"Enhanced performance",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adau1781_adc_bias_क्रमागत,
		ADAU17X1_REC_POWER_MGMT, 3, adau1781_bias_select_text);
अटल SOC_ENUM_SINGLE_DECL(adau1781_speaker_bias_क्रमागत,
		ADAU17X1_PLAY_POWER_MGMT, 6, adau1781_speaker_bias_select_text);
अटल SOC_ENUM_SINGLE_DECL(adau1781_dac_bias_क्रमागत,
		ADAU17X1_PLAY_POWER_MGMT, 4, adau1781_bias_select_text);
अटल SOC_ENUM_SINGLE_DECL(adau1781_playback_bias_क्रमागत,
		ADAU17X1_PLAY_POWER_MGMT, 2, adau1781_bias_select_text);
अटल SOC_ENUM_SINGLE_DECL(adau1781_capture_bias_क्रमागत,
		ADAU17X1_REC_POWER_MGMT, 1, adau1781_bias_select_text);

अटल स्थिर काष्ठा snd_kcontrol_new adau1781_controls[] = अणु
	SOC_SINGLE_TLV("Beep Capture Volume", ADAU1781_DMIC_BEEP_CTRL, 0, 7, 0,
		adau1781_beep_tlv),
	SOC_DOUBLE_R_TLV("PGA Capture Volume", ADAU1781_LEFT_PGA,
		ADAU1781_RIGHT_PGA, 5, 7, 0, adau1781_pga_tlv),
	SOC_DOUBLE_R("PGA Capture Switch", ADAU1781_LEFT_PGA,
		ADAU1781_RIGHT_PGA, 1, 1, 0),

	SOC_DOUBLE_R("Lineout Playback Switch", ADAU1781_LEFT_LINEOUT,
		ADAU1781_RIGHT_LINEOUT, 1, 1, 0),
	SOC_SINGLE("Beep ZC Switch", ADAU1781_BEEP_ZC, 0, 1, 0),

	SOC_SINGLE("Mono Playback Switch", ADAU1781_MONO_PLAYBACK_MIXER,
		0, 1, 0),
	SOC_SINGLE_TLV("Mono Playback Volume", ADAU1781_SPEAKER, 6, 3, 0,
		adau1781_speaker_tlv),

	SOC_ENUM("ADC Bias", adau1781_adc_bias_क्रमागत),
	SOC_ENUM("DAC Bias", adau1781_dac_bias_क्रमागत),
	SOC_ENUM("Capture Bias", adau1781_capture_bias_क्रमागत),
	SOC_ENUM("Playback Bias", adau1781_playback_bias_क्रमागत),
	SOC_ENUM("Speaker Bias", adau1781_speaker_bias_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1781_beep_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Beep Capture Switch", ADAU1781_DMIC_BEEP_CTRL,
		3, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1781_left_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("Switch",
		ADAU1781_LEFT_PLAYBACK_MIXER, 5, 1, 0),
	SOC_DAPM_SINGLE_TLV("Beep Playback Volume",
		ADAU1781_LEFT_PLAYBACK_MIXER, 1, 8, 0, adau1781_sidetone_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1781_right_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("Switch",
		ADAU1781_RIGHT_PLAYBACK_MIXER, 6, 1, 0),
	SOC_DAPM_SINGLE_TLV("Beep Playback Volume",
		ADAU1781_LEFT_PLAYBACK_MIXER, 1, 8, 0, adau1781_sidetone_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1781_mono_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_AUTODISABLE("Left Switch",
		ADAU1781_MONO_PLAYBACK_MIXER, 7, 1, 0),
	SOC_DAPM_SINGLE_AUTODISABLE("Right Switch",
		 ADAU1781_MONO_PLAYBACK_MIXER, 6, 1, 0),
	SOC_DAPM_SINGLE_TLV("Beep Playback Volume",
		ADAU1781_MONO_PLAYBACK_MIXER, 2, 8, 0, adau1781_sidetone_tlv),
पूर्ण;

अटल पूर्णांक adau1781_dejitter_fixup(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);

	/* After any घातer changes have been made the dejitter circuit
	 * has to be reinitialized. */
	regmap_ग_लिखो(adau->regmap, ADAU1781_DEJITTER, 0);
	अगर (!adau->master)
		regmap_ग_लिखो(adau->regmap, ADAU1781_DEJITTER, 5);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget adau1781_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_PGA("Left PGA", ADAU1781_LEFT_PGA, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right PGA", ADAU1781_RIGHT_PGA, 0, 0, शून्य, 0),

	SND_SOC_DAPM_OUT_DRV("Speaker", ADAU1781_SPEAKER, 0, 0, शून्य, 0),

	SOC_MIXER_NAMED_CTL_ARRAY("Beep Mixer", ADAU17X1_MICBIAS, 4, 0,
		adau1781_beep_mixer_controls),

	SOC_MIXER_ARRAY("Left Lineout Mixer", SND_SOC_NOPM, 0, 0,
		adau1781_left_mixer_controls),
	SOC_MIXER_ARRAY("Right Lineout Mixer", SND_SOC_NOPM, 0, 0,
		adau1781_right_mixer_controls),
	SOC_MIXER_ARRAY("Mono Mixer", SND_SOC_NOPM, 0, 0,
		adau1781_mono_mixer_controls),

	SND_SOC_DAPM_SUPPLY("Serial Input Routing", ADAU1781_DIG_PWDN0,
		2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Serial Output Routing", ADAU1781_DIG_PWDN0,
		3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Clock Domain Transfer", ADAU1781_DIG_PWDN0,
		5, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Serial Ports", ADAU1781_DIG_PWDN0, 4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC Engine", ADAU1781_DIG_PWDN0, 7, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC Engine", ADAU1781_DIG_PWDN1, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Digital Mic", ADAU1781_DIG_PWDN1, 1, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Sound Engine", ADAU1781_DIG_PWDN0, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("SYSCLK", 1, ADAU1781_DIG_PWDN0, 1, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Zero Crossing Detector", ADAU1781_DIG_PWDN1, 2, 0,
		शून्य, 0),

	SND_SOC_DAPM_POST("Dejitter fixup", adau1781_dejitter_fixup),

	SND_SOC_DAPM_INPUT("BEEP"),

	SND_SOC_DAPM_OUTPUT("AOUTL"),
	SND_SOC_DAPM_OUTPUT("AOUTR"),
	SND_SOC_DAPM_OUTPUT("SP"),
	SND_SOC_DAPM_INPUT("LMIC"),
	SND_SOC_DAPM_INPUT("RMIC"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau1781_dapm_routes[] = अणु
	अणु "Left Lineout Mixer", शून्य, "Left Playback Enable" पूर्ण,
	अणु "Right Lineout Mixer", शून्य, "Right Playback Enable" पूर्ण,

	अणु "Left Lineout Mixer", "Beep Playback Volume", "Beep Mixer" पूर्ण,
	अणु "Left Lineout Mixer", "Switch", "Left DAC" पूर्ण,

	अणु "Right Lineout Mixer", "Beep Playback Volume", "Beep Mixer" पूर्ण,
	अणु "Right Lineout Mixer", "Switch", "Right DAC" पूर्ण,

	अणु "Mono Mixer", "Beep Playback Volume", "Beep Mixer" पूर्ण,
	अणु "Mono Mixer", "Right Switch", "Right DAC" पूर्ण,
	अणु "Mono Mixer", "Left Switch", "Left DAC" पूर्ण,
	अणु "Speaker", शून्य, "Mono Mixer" पूर्ण,

	अणु "Mono Mixer", शून्य, "SYSCLK" पूर्ण,
	अणु "Left Lineout Mixer", शून्य, "SYSCLK" पूर्ण,
	अणु "Left Lineout Mixer", शून्य, "SYSCLK" पूर्ण,

	अणु "Beep Mixer", "Beep Capture Switch", "BEEP" पूर्ण,
	अणु "Beep Mixer", शून्य, "Zero Crossing Detector" पूर्ण,

	अणु "Left DAC", शून्य, "DAC Engine" पूर्ण,
	अणु "Right DAC", शून्य, "DAC Engine" पूर्ण,

	अणु "Sound Engine", शून्य, "SYSCLK" पूर्ण,
	अणु "DSP", शून्य, "Sound Engine" पूर्ण,

	अणु "Left Decimator", शून्य, "ADC Engine" पूर्ण,
	अणु "Right Decimator", शून्य, "ADC Engine" पूर्ण,

	अणु "AIFCLK", शून्य, "SYSCLK" पूर्ण,

	अणु "Playback", शून्य, "Serial Input Routing" पूर्ण,
	अणु "Playback", शून्य, "Serial Ports" पूर्ण,
	अणु "Playback", शून्य, "Clock Domain Transfer" पूर्ण,
	अणु "Capture", शून्य, "Serial Output Routing" पूर्ण,
	अणु "Capture", शून्य, "Serial Ports" पूर्ण,
	अणु "Capture", शून्य, "Clock Domain Transfer" पूर्ण,

	अणु "AOUTL", शून्य, "Left Lineout Mixer" पूर्ण,
	अणु "AOUTR", शून्य, "Right Lineout Mixer" पूर्ण,
	अणु "SP", शून्य, "Speaker" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau1781_adc_dapm_routes[] = अणु
	अणु "Left PGA", शून्य, "LMIC" पूर्ण,
	अणु "Right PGA", शून्य, "RMIC" पूर्ण,

	अणु "Left Decimator", शून्य, "Left PGA" पूर्ण,
	अणु "Right Decimator", शून्य, "Right PGA" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau1781_dmic_select_text[] = अणु
	"DMIC1", "DMIC2",
पूर्ण;

अटल SOC_ENUM_SINGLE_VIRT_DECL(adau1781_dmic_select_क्रमागत,
	adau1781_dmic_select_text);

अटल स्थिर काष्ठा snd_kcontrol_new adau1781_dmic_mux =
	SOC_DAPM_ENUM("DMIC Select", adau1781_dmic_select_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget adau1781_dmic_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("DMIC Select", SND_SOC_NOPM, 0, 0, &adau1781_dmic_mux),

	SND_SOC_DAPM_ADC("DMIC1", शून्य, ADAU1781_DMIC_BEEP_CTRL, 4, 0),
	SND_SOC_DAPM_ADC("DMIC2", शून्य, ADAU1781_DMIC_BEEP_CTRL, 5, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau1781_dmic_dapm_routes[] = अणु
	अणु "DMIC1", शून्य, "LMIC" पूर्ण,
	अणु "DMIC2", शून्य, "RMIC" पूर्ण,

	अणु "DMIC1", शून्य, "Digital Mic" पूर्ण,
	अणु "DMIC2", शून्य, "Digital Mic" पूर्ण,

	अणु "DMIC Select", "DMIC1", "DMIC1" पूर्ण,
	अणु "DMIC Select", "DMIC2", "DMIC2" पूर्ण,

	अणु "Left Decimator", शून्य, "DMIC Select" पूर्ण,
	अणु "Right Decimator", शून्य, "DMIC Select" पूर्ण,
पूर्ण;

अटल पूर्णांक adau1781_set_bias_level(काष्ठा snd_soc_component *component,
		क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		regmap_update_bits(adau->regmap, ADAU17X1_CLOCK_CONTROL,
			ADAU17X1_CLOCK_CONTROL_SYSCLK_EN,
			ADAU17X1_CLOCK_CONTROL_SYSCLK_EN);

		/* Preअक्षरge */
		regmap_update_bits(adau->regmap, ADAU1781_DIG_PWDN1, 0x8, 0x8);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		regmap_update_bits(adau->regmap, ADAU1781_DIG_PWDN1, 0xc, 0x0);
		regmap_update_bits(adau->regmap, ADAU17X1_CLOCK_CONTROL,
			ADAU17X1_CLOCK_CONTROL_SYSCLK_EN, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool adau1781_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ADAU1781_DMIC_BEEP_CTRL:
	हाल ADAU1781_LEFT_PGA:
	हाल ADAU1781_RIGHT_PGA:
	हाल ADAU1781_LEFT_PLAYBACK_MIXER:
	हाल ADAU1781_RIGHT_PLAYBACK_MIXER:
	हाल ADAU1781_MONO_PLAYBACK_MIXER:
	हाल ADAU1781_LEFT_LINEOUT:
	हाल ADAU1781_RIGHT_LINEOUT:
	हाल ADAU1781_SPEAKER:
	हाल ADAU1781_BEEP_ZC:
	हाल ADAU1781_DEJITTER:
	हाल ADAU1781_DIG_PWDN0:
	हाल ADAU1781_DIG_PWDN1:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस adau17x1_पढ़ोable_रेजिस्टर(dev, reg);
पूर्ण

अटल पूर्णांक adau1781_set_input_mode(काष्ठा adau *adau, अचिन्हित पूर्णांक reg,
	bool dअगरferential)
अणु
	अचिन्हित पूर्णांक val;

	अगर (dअगरferential)
		val = ADAU1781_INPUT_DIFFERNTIAL;
	अन्यथा
		val = 0;

	वापस regmap_update_bits(adau->regmap, reg,
		ADAU1781_INPUT_DIFFERNTIAL, val);
पूर्ण

अटल पूर्णांक adau1781_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा adau1781_platक्रमm_data *pdata = dev_get_platdata(component->dev);
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = adau17x1_add_widमाला_लो(component);
	अगर (ret)
		वापस ret;

	अगर (pdata) अणु
		ret = adau1781_set_input_mode(adau, ADAU1781_LEFT_PGA,
			pdata->left_input_dअगरferential);
		अगर (ret)
			वापस ret;
		ret = adau1781_set_input_mode(adau, ADAU1781_RIGHT_PGA,
			pdata->right_input_dअगरferential);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (pdata && pdata->use_dmic) अणु
		ret = snd_soc_dapm_new_controls(dapm,
			adau1781_dmic_dapm_widमाला_लो,
			ARRAY_SIZE(adau1781_dmic_dapm_widमाला_लो));
		अगर (ret)
			वापस ret;
		ret = snd_soc_dapm_add_routes(dapm, adau1781_dmic_dapm_routes,
			ARRAY_SIZE(adau1781_dmic_dapm_routes));
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = snd_soc_dapm_add_routes(dapm, adau1781_adc_dapm_routes,
			ARRAY_SIZE(adau1781_adc_dapm_routes));
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = adau17x1_add_routes(component);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver adau1781_component_driver = अणु
	.probe			= adau1781_component_probe,
	.resume			= adau17x1_resume,
	.set_bias_level		= adau1781_set_bias_level,
	.controls		= adau1781_controls,
	.num_controls		= ARRAY_SIZE(adau1781_controls),
	.dapm_widमाला_लो		= adau1781_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(adau1781_dapm_widमाला_लो),
	.dapm_routes		= adau1781_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(adau1781_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

#घोषणा ADAU1781_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE | \
	SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver adau1781_dai_driver = अणु
	.name = "adau-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = ADAU1781_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = ADAU1781_FORMATS,
	पूर्ण,
	.ops = &adau17x1_dai_ops,
पूर्ण;

स्थिर काष्ठा regmap_config adau1781_regmap_config = अणु
	.val_bits		= 8,
	.reg_bits		= 16,
	.max_रेजिस्टर		= 0x40f8,
	.reg_शेषs		= adau1781_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(adau1781_reg_शेषs),
	.पढ़ोable_reg		= adau1781_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg		= adau17x1_अस्थिर_रेजिस्टर,
	.precious_reg		= adau17x1_precious_रेजिस्टर,
	.cache_type		= REGCACHE_RBTREE,
पूर्ण;
EXPORT_SYMBOL_GPL(adau1781_regmap_config);

पूर्णांक adau1781_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
	क्रमागत adau17x1_type type, व्योम (*चयन_mode)(काष्ठा device *dev))
अणु
	स्थिर अक्षर *firmware_name;
	पूर्णांक ret;

	चयन (type) अणु
	हाल ADAU1381:
		firmware_name = ADAU1381_FIRMWARE;
		अवरोध;
	हाल ADAU1781:
		firmware_name = ADAU1781_FIRMWARE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = adau17x1_probe(dev, regmap, type, चयन_mode, firmware_name);
	अगर (ret)
		वापस ret;

	वापस devm_snd_soc_रेजिस्टर_component(dev, &adau1781_component_driver,
		&adau1781_dai_driver, 1);
पूर्ण
EXPORT_SYMBOL_GPL(adau1781_probe);

MODULE_DESCRIPTION("ASoC ADAU1381/ADAU1781 driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL");
