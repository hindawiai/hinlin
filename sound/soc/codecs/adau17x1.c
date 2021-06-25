<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Common code क्रम ADAU1X61 and ADAU1X81 codecs
 *
 * Copyright 2011-2014 Analog Devices Inc.
 * Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <linux/gcd.h>
#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "sigmadsp.h"
#समावेश "adau17x1.h"
#समावेश "adau-utils.h"

#घोषणा ADAU17X1_SAFELOAD_TARGET_ADDRESS 0x0006
#घोषणा ADAU17X1_SAFELOAD_TRIGGER 0x0007
#घोषणा ADAU17X1_SAFELOAD_DATA 0x0001
#घोषणा ADAU17X1_SAFELOAD_DATA_SIZE 20
#घोषणा ADAU17X1_WORD_SIZE 4

अटल स्थिर अक्षर * स्थिर adau17x1_capture_mixer_boost_text[] = अणु
	"Normal operation", "Boost Level 1", "Boost Level 2", "Boost Level 3",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adau17x1_capture_boost_क्रमागत,
	ADAU17X1_REC_POWER_MGMT, 5, adau17x1_capture_mixer_boost_text);

अटल स्थिर अक्षर * स्थिर adau17x1_mic_bias_mode_text[] = अणु
	"Normal operation", "High performance",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adau17x1_mic_bias_mode_क्रमागत,
	ADAU17X1_MICBIAS, 3, adau17x1_mic_bias_mode_text);

अटल स्थिर DECLARE_TLV_DB_MINMAX(adau17x1_digital_tlv, -9563, 0);

अटल स्थिर काष्ठा snd_kcontrol_new adau17x1_controls[] = अणु
	SOC_DOUBLE_R_TLV("Digital Capture Volume",
		ADAU17X1_LEFT_INPUT_DIGITAL_VOL,
		ADAU17X1_RIGHT_INPUT_DIGITAL_VOL,
		0, 0xff, 1, adau17x1_digital_tlv),
	SOC_DOUBLE_R_TLV("Digital Playback Volume", ADAU17X1_DAC_CONTROL1,
		ADAU17X1_DAC_CONTROL2, 0, 0xff, 1, adau17x1_digital_tlv),

	SOC_SINGLE("ADC High Pass Filter Switch", ADAU17X1_ADC_CONTROL,
		5, 1, 0),
	SOC_SINGLE("Playback De-emphasis Switch", ADAU17X1_DAC_CONTROL0,
		2, 1, 0),

	SOC_ENUM("Capture Boost", adau17x1_capture_boost_क्रमागत),

	SOC_ENUM("Mic Bias Mode", adau17x1_mic_bias_mode_क्रमागत),
पूर्ण;

अटल पूर्णांक adau17x1_setup_firmware(काष्ठा snd_soc_component *component,
	अचिन्हित पूर्णांक rate);

अटल पूर्णांक adau17x1_pll_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		adau->pll_regs[5] = 1;
	पूर्ण अन्यथा अणु
		adau->pll_regs[5] = 0;
		/* Bypass the PLL when disabled, otherwise रेजिस्टरs will become
		 * inaccessible. */
		regmap_update_bits(adau->regmap, ADAU17X1_CLOCK_CONTROL,
			ADAU17X1_CLOCK_CONTROL_CORECLK_SRC_PLL, 0);
	पूर्ण

	/* The PLL रेजिस्टर is 6 bytes दीर्घ and can only be written at once. */
	regmap_raw_ग_लिखो(adau->regmap, ADAU17X1_PLL_CONTROL,
			adau->pll_regs, ARRAY_SIZE(adau->pll_regs));

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		mdelay(5);
		regmap_update_bits(adau->regmap, ADAU17X1_CLOCK_CONTROL,
			ADAU17X1_CLOCK_CONTROL_CORECLK_SRC_PLL,
			ADAU17X1_CLOCK_CONTROL_CORECLK_SRC_PLL);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adau17x1_adc_fixup(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);

	/*
	 * If we are capturing, toggle the ADOSR bit in Converter Control 0 to
	 * aव्योम losing SNR (workaround from ADI). This must be करोne after
	 * the ADC(s) have been enabled. According to the data sheet, it is
	 * normally illegal to set this bit when the sampling rate is 96 kHz,
	 * but according to ADI it is acceptable क्रम this workaround.
	 */
	regmap_update_bits(adau->regmap, ADAU17X1_CONVERTER0,
		ADAU17X1_CONVERTER0_ADOSR, ADAU17X1_CONVERTER0_ADOSR);
	regmap_update_bits(adau->regmap, ADAU17X1_CONVERTER0,
		ADAU17X1_CONVERTER0_ADOSR, 0);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर adau17x1_mono_stereo_text[] = अणु
	"Stereo",
	"Mono Left Channel (L+R)",
	"Mono Right Channel (L+R)",
	"Mono (L+R)",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adau17x1_dac_mode_क्रमागत,
	ADAU17X1_DAC_CONTROL0, 6, adau17x1_mono_stereo_text);

अटल स्थिर काष्ठा snd_kcontrol_new adau17x1_dac_mode_mux =
	SOC_DAPM_ENUM("DAC Mono-Stereo-Mode", adau17x1_dac_mode_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget adau17x1_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY_S("PLL", 3, SND_SOC_NOPM, 0, 0, adau17x1_pll_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY("AIFCLK", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("MICBIAS", ADAU17X1_MICBIAS, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Left Playback Enable", ADAU17X1_PLAY_POWER_MGMT,
		0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Right Playback Enable", ADAU17X1_PLAY_POWER_MGMT,
		1, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("Left DAC Mode Mux", SND_SOC_NOPM, 0, 0,
		&adau17x1_dac_mode_mux),
	SND_SOC_DAPM_MUX("Right DAC Mode Mux", SND_SOC_NOPM, 0, 0,
		&adau17x1_dac_mode_mux),

	SND_SOC_DAPM_ADC_E("Left Decimator", शून्य, ADAU17X1_ADC_CONTROL, 0, 0,
			   adau17x1_adc_fixup, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_ADC("Right Decimator", शून्य, ADAU17X1_ADC_CONTROL, 1, 0),
	SND_SOC_DAPM_DAC("Left DAC", शून्य, ADAU17X1_DAC_CONTROL0, 0, 0),
	SND_SOC_DAPM_DAC("Right DAC", शून्य, ADAU17X1_DAC_CONTROL0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau17x1_dapm_routes[] = अणु
	अणु "Left Decimator", शून्य, "SYSCLK" पूर्ण,
	अणु "Right Decimator", शून्य, "SYSCLK" पूर्ण,
	अणु "Left DAC", शून्य, "SYSCLK" पूर्ण,
	अणु "Right DAC", शून्य, "SYSCLK" पूर्ण,
	अणु "Capture", शून्य, "SYSCLK" पूर्ण,
	अणु "Playback", शून्य, "SYSCLK" पूर्ण,

	अणु "Left DAC", शून्य, "Left DAC Mode Mux" पूर्ण,
	अणु "Right DAC", शून्य, "Right DAC Mode Mux" पूर्ण,

	अणु "Capture", शून्य, "AIFCLK" पूर्ण,
	अणु "Playback", शून्य, "AIFCLK" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau17x1_dapm_pll_route = अणु
	"SYSCLK", शून्य, "PLL",
पूर्ण;

/*
 * The MUX रेजिस्टर क्रम the Capture and Playback MUXs selects either DSP as
 * source/destination or one of the TDM slots. The TDM slot is selected via
 * snd_soc_dai_set_tdm_slot(), so we only expose whether to go to the DSP or
 * directly to the DAI पूर्णांकerface with this control.
 */
अटल पूर्णांक adau17x1_dsp_mux_क्रमागत_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	काष्ठा snd_soc_dapm_update update = अणुपूर्ण;
	अचिन्हित पूर्णांक stream = e->shअगरt_l;
	अचिन्हित पूर्णांक val, change;
	पूर्णांक reg;

	अगर (ucontrol->value.क्रमागतerated.item[0] >= e->items)
		वापस -EINVAL;

	चयन (ucontrol->value.क्रमागतerated.item[0]) अणु
	हाल 0:
		val = 0;
		adau->dsp_bypass[stream] = false;
		अवरोध;
	शेष:
		val = (adau->tdm_slot[stream] * 2) + 1;
		adau->dsp_bypass[stream] = true;
		अवरोध;
	पूर्ण

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
		reg = ADAU17X1_SERIAL_INPUT_ROUTE;
	अन्यथा
		reg = ADAU17X1_SERIAL_OUTPUT_ROUTE;

	change = snd_soc_component_test_bits(component, reg, 0xff, val);
	अगर (change) अणु
		update.kcontrol = kcontrol;
		update.mask = 0xff;
		update.reg = reg;
		update.val = val;

		snd_soc_dapm_mux_update_घातer(dapm, kcontrol,
				ucontrol->value.क्रमागतerated.item[0], e, &update);
	पूर्ण

	वापस change;
पूर्ण

अटल पूर्णांक adau17x1_dsp_mux_क्रमागत_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक stream = e->shअगरt_l;
	अचिन्हित पूर्णांक reg, val;
	पूर्णांक ret;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
		reg = ADAU17X1_SERIAL_INPUT_ROUTE;
	अन्यथा
		reg = ADAU17X1_SERIAL_OUTPUT_ROUTE;

	ret = regmap_पढ़ो(adau->regmap, reg, &val);
	अगर (ret)
		वापस ret;

	अगर (val != 0)
		val = 1;
	ucontrol->value.क्रमागतerated.item[0] = val;

	वापस 0;
पूर्ण

#घोषणा DECLARE_ADAU17X1_DSP_MUX_CTRL(_name, _label, _stream, _text) \
	स्थिर काष्ठा snd_kcontrol_new _name = \
		SOC_DAPM_ENUM_EXT(_label, (स्थिर काष्ठा soc_क्रमागत)\
			SOC_ENUM_SINGLE(SND_SOC_NOPM, _stream, \
				ARRAY_SIZE(_text), _text), \
			adau17x1_dsp_mux_क्रमागत_get, adau17x1_dsp_mux_क्रमागत_put)

अटल स्थिर अक्षर * स्थिर adau17x1_dac_mux_text[] = अणु
	"DSP",
	"AIFIN",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adau17x1_capture_mux_text[] = अणु
	"DSP",
	"Decimator",
पूर्ण;

अटल DECLARE_ADAU17X1_DSP_MUX_CTRL(adau17x1_dac_mux, "DAC Playback Mux",
	SNDRV_PCM_STREAM_PLAYBACK, adau17x1_dac_mux_text);

अटल DECLARE_ADAU17X1_DSP_MUX_CTRL(adau17x1_capture_mux, "Capture Mux",
	SNDRV_PCM_STREAM_CAPTURE, adau17x1_capture_mux_text);

अटल स्थिर काष्ठा snd_soc_dapm_widget adau17x1_dsp_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_PGA("DSP", ADAU17X1_DSP_RUN, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SIGGEN("DSP Siggen"),

	SND_SOC_DAPM_MUX("DAC Playback Mux", SND_SOC_NOPM, 0, 0,
		&adau17x1_dac_mux),
	SND_SOC_DAPM_MUX("Capture Mux", SND_SOC_NOPM, 0, 0,
		&adau17x1_capture_mux),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau17x1_dsp_dapm_routes[] = अणु
	अणु "DAC Playback Mux", "DSP", "DSP" पूर्ण,
	अणु "DAC Playback Mux", "AIFIN", "Playback" पूर्ण,

	अणु "Left DAC Mode Mux", "Stereo", "DAC Playback Mux" पूर्ण,
	अणु "Left DAC Mode Mux", "Mono (L+R)", "DAC Playback Mux" पूर्ण,
	अणु "Left DAC Mode Mux", "Mono Left Channel (L+R)", "DAC Playback Mux" पूर्ण,
	अणु "Right DAC Mode Mux", "Stereo", "DAC Playback Mux" पूर्ण,
	अणु "Right DAC Mode Mux", "Mono (L+R)", "DAC Playback Mux" पूर्ण,
	अणु "Right DAC Mode Mux", "Mono Right Channel (L+R)", "DAC Playback Mux" पूर्ण,

	अणु "Capture Mux", "DSP", "DSP" पूर्ण,
	अणु "Capture Mux", "Decimator", "Left Decimator" पूर्ण,
	अणु "Capture Mux", "Decimator", "Right Decimator" पूर्ण,

	अणु "Capture", शून्य, "Capture Mux" पूर्ण,

	अणु "DSP", शून्य, "DSP Siggen" पूर्ण,

	अणु "DSP", शून्य, "Left Decimator" पूर्ण,
	अणु "DSP", शून्य, "Right Decimator" पूर्ण,
	अणु "DSP", शून्य, "Playback" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau17x1_no_dsp_dapm_routes[] = अणु
	अणु "Left DAC Mode Mux", "Stereo", "Playback" पूर्ण,
	अणु "Left DAC Mode Mux", "Mono (L+R)", "Playback" पूर्ण,
	अणु "Left DAC Mode Mux", "Mono Left Channel (L+R)", "Playback" पूर्ण,
	अणु "Right DAC Mode Mux", "Stereo", "Playback" पूर्ण,
	अणु "Right DAC Mode Mux", "Mono (L+R)", "Playback" पूर्ण,
	अणु "Right DAC Mode Mux", "Mono Right Channel (L+R)", "Playback" पूर्ण,
	अणु "Capture", शून्य, "Left Decimator" पूर्ण,
	अणु "Capture", शून्य, "Right Decimator" पूर्ण,
पूर्ण;

अटल bool adau17x1_has_dsp(काष्ठा adau *adau)
अणु
	चयन (adau->type) अणु
	हाल ADAU1761:
	हाल ADAU1381:
	हाल ADAU1781:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool adau17x1_has_safeload(काष्ठा adau *adau)
अणु
	चयन (adau->type) अणु
	हाल ADAU1761:
	हाल ADAU1781:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक adau17x1_set_dai_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id,
	पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	अगर (freq_in < 8000000 || freq_in > 27000000)
		वापस -EINVAL;

	ret = adau_calc_pll_cfg(freq_in, freq_out, adau->pll_regs);
	अगर (ret < 0)
		वापस ret;

	/* The PLL रेजिस्टर is 6 bytes दीर्घ and can only be written at once. */
	ret = regmap_raw_ग_लिखो(adau->regmap, ADAU17X1_PLL_CONTROL,
			adau->pll_regs, ARRAY_SIZE(adau->pll_regs));
	अगर (ret)
		वापस ret;

	adau->pll_freq = freq_out;

	वापस 0;
पूर्ण

अटल पूर्णांक adau17x1_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(dai->component);
	काष्ठा adau *adau = snd_soc_component_get_drvdata(dai->component);
	bool is_pll;
	bool was_pll;

	चयन (clk_id) अणु
	हाल ADAU17X1_CLK_SRC_MCLK:
		is_pll = false;
		अवरोध;
	हाल ADAU17X1_CLK_SRC_PLL_AUTO:
		अगर (!adau->mclk)
			वापस -EINVAL;
		fallthrough;
	हाल ADAU17X1_CLK_SRC_PLL:
		is_pll = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (adau->clk_src) अणु
	हाल ADAU17X1_CLK_SRC_MCLK:
		was_pll = false;
		अवरोध;
	हाल ADAU17X1_CLK_SRC_PLL:
	हाल ADAU17X1_CLK_SRC_PLL_AUTO:
		was_pll = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	adau->sysclk = freq;

	अगर (is_pll != was_pll) अणु
		अगर (is_pll) अणु
			snd_soc_dapm_add_routes(dapm,
				&adau17x1_dapm_pll_route, 1);
		पूर्ण अन्यथा अणु
			snd_soc_dapm_del_routes(dapm,
				&adau17x1_dapm_pll_route, 1);
		पूर्ण
	पूर्ण

	adau->clk_src = clk_id;

	वापस 0;
पूर्ण

अटल पूर्णांक adau17x1_स्वतः_pll(काष्ठा snd_soc_dai *dai,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा adau *adau = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक pll_rate;

	चयन (params_rate(params)) अणु
	हाल 48000:
	हाल 8000:
	हाल 12000:
	हाल 16000:
	हाल 24000:
	हाल 32000:
	हाल 96000:
		pll_rate = 48000 * 1024;
		अवरोध;
	हाल 44100:
	हाल 7350:
	हाल 11025:
	हाल 14700:
	हाल 22050:
	हाल 29400:
	हाल 88200:
		pll_rate = 44100 * 1024;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस adau17x1_set_dai_pll(dai, ADAU17X1_PLL, ADAU17X1_PLL_SRC_MCLK,
		clk_get_rate(adau->mclk), pll_rate);
पूर्ण

अटल पूर्णांक adau17x1_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val, भाग, dsp_भाग;
	अचिन्हित पूर्णांक freq;
	पूर्णांक ret;

	चयन (adau->clk_src) अणु
	हाल ADAU17X1_CLK_SRC_PLL_AUTO:
		ret = adau17x1_स्वतः_pll(dai, params);
		अगर (ret)
			वापस ret;
		fallthrough;
	हाल ADAU17X1_CLK_SRC_PLL:
		freq = adau->pll_freq;
		अवरोध;
	शेष:
		freq = adau->sysclk;
		अवरोध;
	पूर्ण

	अगर (freq % params_rate(params) != 0)
		वापस -EINVAL;

	चयन (freq / params_rate(params)) अणु
	हाल 1024: /* fs */
		भाग = 0;
		dsp_भाग = 1;
		अवरोध;
	हाल 6144: /* fs / 6 */
		भाग = 1;
		dsp_भाग = 6;
		अवरोध;
	हाल 4096: /* fs / 4 */
		भाग = 2;
		dsp_भाग = 5;
		अवरोध;
	हाल 3072: /* fs / 3 */
		भाग = 3;
		dsp_भाग = 4;
		अवरोध;
	हाल 2048: /* fs / 2 */
		भाग = 4;
		dsp_भाग = 3;
		अवरोध;
	हाल 1536: /* fs / 1.5 */
		भाग = 5;
		dsp_भाग = 2;
		अवरोध;
	हाल 512: /* fs / 0.5 */
		भाग = 6;
		dsp_भाग = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(adau->regmap, ADAU17X1_CONVERTER0,
		ADAU17X1_CONVERTER0_CONVSR_MASK, भाग);
	अगर (adau17x1_has_dsp(adau)) अणु
		regmap_ग_लिखो(adau->regmap, ADAU17X1_SERIAL_SAMPLING_RATE, भाग);
		regmap_ग_लिखो(adau->regmap, ADAU17X1_DSP_SAMPLING_RATE, dsp_भाग);
	पूर्ण

	अगर (adau->sigmadsp) अणु
		ret = adau17x1_setup_firmware(component, params_rate(params));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (adau->dai_fmt != SND_SOC_DAIFMT_RIGHT_J)
		वापस 0;

	चयन (params_width(params)) अणु
	हाल 16:
		val = ADAU17X1_SERIAL_PORT1_DELAY16;
		अवरोध;
	हाल 24:
		val = ADAU17X1_SERIAL_PORT1_DELAY8;
		अवरोध;
	हाल 32:
		val = ADAU17X1_SERIAL_PORT1_DELAY0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(adau->regmap, ADAU17X1_SERIAL_PORT1,
			ADAU17X1_SERIAL_PORT1_DELAY_MASK, val);
पूर्ण

अटल पूर्णांक adau17x1_set_dai_fmt(काष्ठा snd_soc_dai *dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा adau *adau = snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक ctrl0, ctrl1;
	अचिन्हित पूर्णांक ctrl0_mask;
	पूर्णांक lrclk_pol;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		ctrl0 = ADAU17X1_SERIAL_PORT0_MASTER;
		adau->master = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		ctrl0 = 0;
		adau->master = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		lrclk_pol = 0;
		ctrl1 = ADAU17X1_SERIAL_PORT1_DELAY1;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_RIGHT_J:
		lrclk_pol = 1;
		ctrl1 = ADAU17X1_SERIAL_PORT1_DELAY0;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		lrclk_pol = 1;
		ctrl0 |= ADAU17X1_SERIAL_PORT0_PULSE_MODE;
		ctrl1 = ADAU17X1_SERIAL_PORT1_DELAY1;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		lrclk_pol = 1;
		ctrl0 |= ADAU17X1_SERIAL_PORT0_PULSE_MODE;
		ctrl1 = ADAU17X1_SERIAL_PORT1_DELAY0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		ctrl0 |= ADAU17X1_SERIAL_PORT0_BCLK_POL;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		lrclk_pol = !lrclk_pol;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		ctrl0 |= ADAU17X1_SERIAL_PORT0_BCLK_POL;
		lrclk_pol = !lrclk_pol;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (lrclk_pol)
		ctrl0 |= ADAU17X1_SERIAL_PORT0_LRCLK_POL;

	/* Set the mask to update all relevant bits in ADAU17X1_SERIAL_PORT0 */
	ctrl0_mask = ADAU17X1_SERIAL_PORT0_MASTER |
		     ADAU17X1_SERIAL_PORT0_LRCLK_POL |
		     ADAU17X1_SERIAL_PORT0_BCLK_POL |
		     ADAU17X1_SERIAL_PORT0_PULSE_MODE;

	regmap_update_bits(adau->regmap, ADAU17X1_SERIAL_PORT0, ctrl0_mask,
			   ctrl0);
	regmap_update_bits(adau->regmap, ADAU17X1_SERIAL_PORT1,
			   ADAU17X1_SERIAL_PORT1_DELAY_MASK, ctrl1);

	adau->dai_fmt = fmt & SND_SOC_DAIFMT_FORMAT_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक adau17x1_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
	अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा adau *adau = snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक ser_ctrl0, ser_ctrl1;
	अचिन्हित पूर्णांक conv_ctrl0, conv_ctrl1;

	/* I2S mode */
	अगर (slots == 0) अणु
		slots = 2;
		rx_mask = 3;
		tx_mask = 3;
		slot_width = 32;
	पूर्ण

	चयन (slots) अणु
	हाल 2:
		ser_ctrl0 = ADAU17X1_SERIAL_PORT0_STEREO;
		अवरोध;
	हाल 4:
		ser_ctrl0 = ADAU17X1_SERIAL_PORT0_TDM4;
		अवरोध;
	हाल 8:
		अगर (adau->type == ADAU1361)
			वापस -EINVAL;

		ser_ctrl0 = ADAU17X1_SERIAL_PORT0_TDM8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (slot_width * slots) अणु
	हाल 32:
		अगर (adau->type == ADAU1761)
			वापस -EINVAL;

		ser_ctrl1 = ADAU17X1_SERIAL_PORT1_BCLK32;
		अवरोध;
	हाल 64:
		ser_ctrl1 = ADAU17X1_SERIAL_PORT1_BCLK64;
		अवरोध;
	हाल 48:
		ser_ctrl1 = ADAU17X1_SERIAL_PORT1_BCLK48;
		अवरोध;
	हाल 128:
		ser_ctrl1 = ADAU17X1_SERIAL_PORT1_BCLK128;
		अवरोध;
	हाल 256:
		अगर (adau->type == ADAU1361)
			वापस -EINVAL;

		ser_ctrl1 = ADAU17X1_SERIAL_PORT1_BCLK256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (rx_mask) अणु
	हाल 0x03:
		conv_ctrl1 = ADAU17X1_CONVERTER1_ADC_PAIR(1);
		adau->tdm_slot[SNDRV_PCM_STREAM_CAPTURE] = 0;
		अवरोध;
	हाल 0x0c:
		conv_ctrl1 = ADAU17X1_CONVERTER1_ADC_PAIR(2);
		adau->tdm_slot[SNDRV_PCM_STREAM_CAPTURE] = 1;
		अवरोध;
	हाल 0x30:
		conv_ctrl1 = ADAU17X1_CONVERTER1_ADC_PAIR(3);
		adau->tdm_slot[SNDRV_PCM_STREAM_CAPTURE] = 2;
		अवरोध;
	हाल 0xc0:
		conv_ctrl1 = ADAU17X1_CONVERTER1_ADC_PAIR(4);
		adau->tdm_slot[SNDRV_PCM_STREAM_CAPTURE] = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (tx_mask) अणु
	हाल 0x03:
		conv_ctrl0 = ADAU17X1_CONVERTER0_DAC_PAIR(1);
		adau->tdm_slot[SNDRV_PCM_STREAM_PLAYBACK] = 0;
		अवरोध;
	हाल 0x0c:
		conv_ctrl0 = ADAU17X1_CONVERTER0_DAC_PAIR(2);
		adau->tdm_slot[SNDRV_PCM_STREAM_PLAYBACK] = 1;
		अवरोध;
	हाल 0x30:
		conv_ctrl0 = ADAU17X1_CONVERTER0_DAC_PAIR(3);
		adau->tdm_slot[SNDRV_PCM_STREAM_PLAYBACK] = 2;
		अवरोध;
	हाल 0xc0:
		conv_ctrl0 = ADAU17X1_CONVERTER0_DAC_PAIR(4);
		adau->tdm_slot[SNDRV_PCM_STREAM_PLAYBACK] = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(adau->regmap, ADAU17X1_CONVERTER0,
		ADAU17X1_CONVERTER0_DAC_PAIR_MASK, conv_ctrl0);
	regmap_update_bits(adau->regmap, ADAU17X1_CONVERTER1,
		ADAU17X1_CONVERTER1_ADC_PAIR_MASK, conv_ctrl1);
	regmap_update_bits(adau->regmap, ADAU17X1_SERIAL_PORT0,
		ADAU17X1_SERIAL_PORT0_TDM_MASK, ser_ctrl0);
	regmap_update_bits(adau->regmap, ADAU17X1_SERIAL_PORT1,
		ADAU17X1_SERIAL_PORT1_BCLK_MASK, ser_ctrl1);

	अगर (!adau17x1_has_dsp(adau))
		वापस 0;

	अगर (adau->dsp_bypass[SNDRV_PCM_STREAM_PLAYBACK]) अणु
		regmap_ग_लिखो(adau->regmap, ADAU17X1_SERIAL_INPUT_ROUTE,
			(adau->tdm_slot[SNDRV_PCM_STREAM_PLAYBACK] * 2) + 1);
	पूर्ण

	अगर (adau->dsp_bypass[SNDRV_PCM_STREAM_CAPTURE]) अणु
		regmap_ग_लिखो(adau->regmap, ADAU17X1_SERIAL_OUTPUT_ROUTE,
			(adau->tdm_slot[SNDRV_PCM_STREAM_CAPTURE] * 2) + 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adau17x1_startup(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा adau *adau = snd_soc_component_get_drvdata(dai->component);

	अगर (adau->sigmadsp)
		वापस sigmadsp_restrict_params(adau->sigmadsp, substream);

	वापस 0;
पूर्ण

स्थिर काष्ठा snd_soc_dai_ops adau17x1_dai_ops = अणु
	.hw_params	= adau17x1_hw_params,
	.set_sysclk	= adau17x1_set_dai_sysclk,
	.set_fmt	= adau17x1_set_dai_fmt,
	.set_pll	= adau17x1_set_dai_pll,
	.set_tdm_slot	= adau17x1_set_dai_tdm_slot,
	.startup	= adau17x1_startup,
पूर्ण;
EXPORT_SYMBOL_GPL(adau17x1_dai_ops);

पूर्णांक adau17x1_set_micbias_voltage(काष्ठा snd_soc_component *component,
	क्रमागत adau17x1_micbias_voltage micbias)
अणु
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);

	चयन (micbias) अणु
	हाल ADAU17X1_MICBIAS_0_90_AVDD:
	हाल ADAU17X1_MICBIAS_0_65_AVDD:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_ग_लिखो(adau->regmap, ADAU17X1_MICBIAS, micbias << 2);
पूर्ण
EXPORT_SYMBOL_GPL(adau17x1_set_micbias_voltage);

bool adau17x1_precious_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* SigmaDSP parameter memory */
	अगर (reg < 0x400)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(adau17x1_precious_रेजिस्टर);

bool adau17x1_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* SigmaDSP parameter memory */
	अगर (reg < 0x400)
		वापस true;

	चयन (reg) अणु
	हाल ADAU17X1_CLOCK_CONTROL:
	हाल ADAU17X1_PLL_CONTROL:
	हाल ADAU17X1_REC_POWER_MGMT:
	हाल ADAU17X1_MICBIAS:
	हाल ADAU17X1_SERIAL_PORT0:
	हाल ADAU17X1_SERIAL_PORT1:
	हाल ADAU17X1_CONVERTER0:
	हाल ADAU17X1_CONVERTER1:
	हाल ADAU17X1_LEFT_INPUT_DIGITAL_VOL:
	हाल ADAU17X1_RIGHT_INPUT_DIGITAL_VOL:
	हाल ADAU17X1_ADC_CONTROL:
	हाल ADAU17X1_PLAY_POWER_MGMT:
	हाल ADAU17X1_DAC_CONTROL0:
	हाल ADAU17X1_DAC_CONTROL1:
	हाल ADAU17X1_DAC_CONTROL2:
	हाल ADAU17X1_SERIAL_PORT_PAD:
	हाल ADAU17X1_CONTROL_PORT_PAD0:
	हाल ADAU17X1_CONTROL_PORT_PAD1:
	हाल ADAU17X1_DSP_SAMPLING_RATE:
	हाल ADAU17X1_SERIAL_INPUT_ROUTE:
	हाल ADAU17X1_SERIAL_OUTPUT_ROUTE:
	हाल ADAU17X1_DSP_ENABLE:
	हाल ADAU17X1_DSP_RUN:
	हाल ADAU17X1_SERIAL_SAMPLING_RATE:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(adau17x1_पढ़ोable_रेजिस्टर);

bool adau17x1_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* SigmaDSP parameter and program memory */
	अगर (reg < 0x4000)
		वापस true;

	चयन (reg) अणु
	/* The PLL रेजिस्टर is 6 bytes दीर्घ */
	हाल ADAU17X1_PLL_CONTROL:
	हाल ADAU17X1_PLL_CONTROL + 1:
	हाल ADAU17X1_PLL_CONTROL + 2:
	हाल ADAU17X1_PLL_CONTROL + 3:
	हाल ADAU17X1_PLL_CONTROL + 4:
	हाल ADAU17X1_PLL_CONTROL + 5:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(adau17x1_अस्थिर_रेजिस्टर);

अटल पूर्णांक adau17x1_setup_firmware(काष्ठा snd_soc_component *component,
	अचिन्हित पूर्णांक rate)
अणु
	पूर्णांक ret;
	पूर्णांक dspsr, dsp_run;
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	/* Check अगर sample rate is the same as beक्रमe. If it is there is no
	 * poपूर्णांक in perक्रमming the below steps as the call to
	 * sigmadsp_setup(...) will वापस directly when it finds the sample
	 * rate to be the same as beक्रमe. By checking this we can prevent an
	 * audiable popping noise which occours when toggling DSP_RUN.
	 */
	अगर (adau->sigmadsp->current_samplerate == rate)
		वापस 0;

	snd_soc_dapm_mutex_lock(dapm);

	ret = regmap_पढ़ो(adau->regmap, ADAU17X1_DSP_SAMPLING_RATE, &dspsr);
	अगर (ret)
		जाओ err;

	ret = regmap_पढ़ो(adau->regmap, ADAU17X1_DSP_RUN, &dsp_run);
	अगर (ret)
		जाओ err;

	regmap_ग_लिखो(adau->regmap, ADAU17X1_DSP_ENABLE, 1);
	regmap_ग_लिखो(adau->regmap, ADAU17X1_DSP_SAMPLING_RATE, 0xf);
	regmap_ग_लिखो(adau->regmap, ADAU17X1_DSP_RUN, 0);

	ret = sigmadsp_setup(adau->sigmadsp, rate);
	अगर (ret) अणु
		regmap_ग_लिखो(adau->regmap, ADAU17X1_DSP_ENABLE, 0);
		जाओ err;
	पूर्ण
	regmap_ग_लिखो(adau->regmap, ADAU17X1_DSP_SAMPLING_RATE, dspsr);
	regmap_ग_लिखो(adau->regmap, ADAU17X1_DSP_RUN, dsp_run);

err:
	snd_soc_dapm_mutex_unlock(dapm);

	वापस ret;
पूर्ण

पूर्णांक adau17x1_add_widमाला_लो(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = snd_soc_add_component_controls(component, adau17x1_controls,
		ARRAY_SIZE(adau17x1_controls));
	अगर (ret)
		वापस ret;
	ret = snd_soc_dapm_new_controls(dapm, adau17x1_dapm_widमाला_लो,
		ARRAY_SIZE(adau17x1_dapm_widमाला_लो));
	अगर (ret)
		वापस ret;

	अगर (adau17x1_has_dsp(adau)) अणु
		ret = snd_soc_dapm_new_controls(dapm, adau17x1_dsp_dapm_widमाला_लो,
			ARRAY_SIZE(adau17x1_dsp_dapm_widमाला_लो));
		अगर (ret)
			वापस ret;

		अगर (!adau->sigmadsp)
			वापस 0;

		ret = sigmadsp_attach(adau->sigmadsp, component);
		अगर (ret) अणु
			dev_err(component->dev, "Failed to attach firmware: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adau17x1_add_widमाला_लो);

पूर्णांक adau17x1_add_routes(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = snd_soc_dapm_add_routes(dapm, adau17x1_dapm_routes,
		ARRAY_SIZE(adau17x1_dapm_routes));
	अगर (ret)
		वापस ret;

	अगर (adau17x1_has_dsp(adau)) अणु
		ret = snd_soc_dapm_add_routes(dapm, adau17x1_dsp_dapm_routes,
			ARRAY_SIZE(adau17x1_dsp_dapm_routes));
	पूर्ण अन्यथा अणु
		ret = snd_soc_dapm_add_routes(dapm, adau17x1_no_dsp_dapm_routes,
			ARRAY_SIZE(adau17x1_no_dsp_dapm_routes));
	पूर्ण

	अगर (adau->clk_src != ADAU17X1_CLK_SRC_MCLK)
		snd_soc_dapm_add_routes(dapm, &adau17x1_dapm_pll_route, 1);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(adau17x1_add_routes);

पूर्णांक adau17x1_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा adau *adau = snd_soc_component_get_drvdata(component);

	अगर (adau->चयन_mode)
		adau->चयन_mode(component->dev);

	regcache_sync(adau->regmap);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adau17x1_resume);

अटल पूर्णांक adau17x1_safeload(काष्ठा sigmadsp *sigmadsp, अचिन्हित पूर्णांक addr,
	स्थिर uपूर्णांक8_t bytes[], माप_प्रकार len)
अणु
	uपूर्णांक8_t buf[ADAU17X1_WORD_SIZE];
	uपूर्णांक8_t data[ADAU17X1_SAFELOAD_DATA_SIZE];
	अचिन्हित पूर्णांक addr_offset;
	अचिन्हित पूर्णांक nbr_words;
	पूर्णांक ret;

	/* ग_लिखो data to safeload addresses. Check अगर len is not a multiple of
	 * 4 bytes, अगर so we need to zero pad.
	 */
	nbr_words = len / ADAU17X1_WORD_SIZE;
	अगर ((len - nbr_words * ADAU17X1_WORD_SIZE) == 0) अणु
		ret = regmap_raw_ग_लिखो(sigmadsp->control_data,
			ADAU17X1_SAFELOAD_DATA, bytes, len);
	पूर्ण अन्यथा अणु
		nbr_words++;
		स_रखो(data, 0, ADAU17X1_SAFELOAD_DATA_SIZE);
		स_नकल(data, bytes, len);
		ret = regmap_raw_ग_लिखो(sigmadsp->control_data,
			ADAU17X1_SAFELOAD_DATA, data,
			nbr_words * ADAU17X1_WORD_SIZE);
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	/* Write target address, target address is offset by 1 */
	addr_offset = addr - 1;
	put_unaligned_be32(addr_offset, buf);
	ret = regmap_raw_ग_लिखो(sigmadsp->control_data,
		ADAU17X1_SAFELOAD_TARGET_ADDRESS, buf, ADAU17X1_WORD_SIZE);
	अगर (ret < 0)
		वापस ret;

	/* ग_लिखो nbr of words to trigger address */
	put_unaligned_be32(nbr_words, buf);
	ret = regmap_raw_ग_लिखो(sigmadsp->control_data,
		ADAU17X1_SAFELOAD_TRIGGER, buf, ADAU17X1_WORD_SIZE);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sigmadsp_ops adau17x1_sigmadsp_ops = अणु
	.safeload = adau17x1_safeload,
पूर्ण;

पूर्णांक adau17x1_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
	क्रमागत adau17x1_type type, व्योम (*चयन_mode)(काष्ठा device *dev),
	स्थिर अक्षर *firmware_name)
अणु
	काष्ठा adau *adau;
	पूर्णांक ret;

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	adau = devm_kzalloc(dev, माप(*adau), GFP_KERNEL);
	अगर (!adau)
		वापस -ENOMEM;

	adau->mclk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(adau->mclk)) अणु
		अगर (PTR_ERR(adau->mclk) != -ENOENT)
			वापस PTR_ERR(adau->mclk);
		/* Clock is optional (क्रम the driver) */
		adau->mclk = शून्य;
	पूर्ण अन्यथा अगर (adau->mclk) अणु
		adau->clk_src = ADAU17X1_CLK_SRC_PLL_AUTO;

		/*
		 * Any valid PLL output rate will work at this poपूर्णांक, use one
		 * that is likely to be chosen later as well. The रेजिस्टर will
		 * be written when the PLL is घातered up क्रम the first समय.
		 */
		ret = adau_calc_pll_cfg(clk_get_rate(adau->mclk), 48000 * 1024,
				adau->pll_regs);
		अगर (ret < 0)
			वापस ret;

		ret = clk_prepare_enable(adau->mclk);
		अगर (ret)
			वापस ret;
	पूर्ण

	adau->regmap = regmap;
	adau->चयन_mode = चयन_mode;
	adau->type = type;

	dev_set_drvdata(dev, adau);

	अगर (firmware_name) अणु
		अगर (adau17x1_has_safeload(adau)) अणु
			adau->sigmadsp = devm_sigmadsp_init_regmap(dev, regmap,
				&adau17x1_sigmadsp_ops, firmware_name);
		पूर्ण अन्यथा अणु
			adau->sigmadsp = devm_sigmadsp_init_regmap(dev, regmap,
				शून्य, firmware_name);
		पूर्ण
		अगर (IS_ERR(adau->sigmadsp)) अणु
			dev_warn(dev, "Could not find firmware file: %ld\n",
				PTR_ERR(adau->sigmadsp));
			adau->sigmadsp = शून्य;
		पूर्ण
	पूर्ण

	अगर (चयन_mode)
		चयन_mode(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adau17x1_probe);

व्योम adau17x1_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा adau *adau = dev_get_drvdata(dev);

	clk_disable_unprepare(adau->mclk);
पूर्ण
EXPORT_SYMBOL_GPL(adau17x1_हटाओ);

MODULE_DESCRIPTION("ASoC ADAU1X61/ADAU1X81 common code");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL");
