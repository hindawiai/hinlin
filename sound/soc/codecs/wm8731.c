<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8731.c  --  WM8731 ALSA SoC Audio driver
 *
 * Copyright 2005 Openedhand Ltd.
 * Copyright 2006-12 Wolfson Microelectronics, plc
 *
 * Author: Riअक्षरd Purdie <riअक्षरd@खोलोedhand.com>
 *
 * Based on wm8753.c by Liam Girdwood
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/clk.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm8731.h"

#घोषणा WM8731_NUM_SUPPLIES 4
अटल स्थिर अक्षर *wm8731_supply_names[WM8731_NUM_SUPPLIES] = अणु
	"AVDD",
	"HPVDD",
	"DCVDD",
	"DBVDD",
पूर्ण;

/* codec निजी data */
काष्ठा wm8731_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा clk *mclk;
	काष्ठा regulator_bulk_data supplies[WM8731_NUM_SUPPLIES];
	स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *स्थिरraपूर्णांकs;
	अचिन्हित पूर्णांक sysclk;
	पूर्णांक sysclk_type;
	पूर्णांक playback_fs;
	bool deemph;

	काष्ठा mutex lock;
पूर्ण;


/*
 * wm8731 रेजिस्टर cache
 */
अटल स्थिर काष्ठा reg_शेष wm8731_reg_शेषs[] = अणु
	अणु 0, 0x0097 पूर्ण,
	अणु 1, 0x0097 पूर्ण,
	अणु 2, 0x0079 पूर्ण,
	अणु 3, 0x0079 पूर्ण,
	अणु 4, 0x000a पूर्ण,
	अणु 5, 0x0008 पूर्ण,
	अणु 6, 0x009f पूर्ण,
	अणु 7, 0x000a पूर्ण,
	अणु 8, 0x0000 पूर्ण,
	अणु 9, 0x0000 पूर्ण,
पूर्ण;

अटल bool wm8731_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == WM8731_RESET;
पूर्ण

#घोषणा wm8731_reset(m)	regmap_ग_लिखो(m, WM8731_RESET, 0)

अटल स्थिर अक्षर *wm8731_input_select[] = अणु"Line In", "Mic"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm8731_insel_क्रमागत,
			    WM8731_APANA, 2, wm8731_input_select);

अटल पूर्णांक wm8731_deemph[] = अणु 0, 32000, 44100, 48000 पूर्ण;

अटल पूर्णांक wm8731_set_deemph(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8731_priv *wm8731 = snd_soc_component_get_drvdata(component);
	पूर्णांक val, i, best;

	/* If we're using deemphasis select the nearest available sample
	 * rate.
	 */
	अगर (wm8731->deemph) अणु
		best = 1;
		क्रम (i = 2; i < ARRAY_SIZE(wm8731_deemph); i++) अणु
			अगर (असल(wm8731_deemph[i] - wm8731->playback_fs) <
			    असल(wm8731_deemph[best] - wm8731->playback_fs))
				best = i;
		पूर्ण

		val = best << 1;
	पूर्ण अन्यथा अणु
		best = 0;
		val = 0;
	पूर्ण

	dev_dbg(component->dev, "Set deemphasis %d (%dHz)\n",
		best, wm8731_deemph[best]);

	वापस snd_soc_component_update_bits(component, WM8731_APDIGI, 0x6, val);
पूर्ण

अटल पूर्णांक wm8731_get_deemph(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8731_priv *wm8731 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = wm8731->deemph;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8731_put_deemph(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8731_priv *wm8731 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक deemph = ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक ret = 0;

	अगर (deemph > 1)
		वापस -EINVAL;

	mutex_lock(&wm8731->lock);
	अगर (wm8731->deemph != deemph) अणु
		wm8731->deemph = deemph;

		wm8731_set_deemph(component);

		ret = 1;
	पूर्ण
	mutex_unlock(&wm8731->lock);

	वापस ret;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(in_tlv, -3450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(sidetone_tlv, -1500, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -12100, 100, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_tlv, 0, 2000, 0);

अटल स्थिर काष्ठा snd_kcontrol_new wm8731_snd_controls[] = अणु

SOC_DOUBLE_R_TLV("Master Playback Volume", WM8731_LOUT1V, WM8731_ROUT1V,
		 0, 127, 0, out_tlv),
SOC_DOUBLE_R("Master Playback ZC Switch", WM8731_LOUT1V, WM8731_ROUT1V,
	7, 1, 0),

SOC_DOUBLE_R_TLV("Capture Volume", WM8731_LINVOL, WM8731_RINVOL, 0, 31, 0,
		 in_tlv),
SOC_DOUBLE_R("Line Capture Switch", WM8731_LINVOL, WM8731_RINVOL, 7, 1, 1),

SOC_SINGLE_TLV("Mic Boost Volume", WM8731_APANA, 0, 1, 0, mic_tlv),
SOC_SINGLE("Mic Capture Switch", WM8731_APANA, 1, 1, 1),

SOC_SINGLE_TLV("Sidetone Playback Volume", WM8731_APANA, 6, 3, 1,
	       sidetone_tlv),

SOC_SINGLE("ADC High Pass Filter Switch", WM8731_APDIGI, 0, 1, 1),
SOC_SINGLE("Store DC Offset Switch", WM8731_APDIGI, 4, 1, 0),

SOC_SINGLE_BOOL_EXT("Playback Deemphasis Switch", 0,
		    wm8731_get_deemph, wm8731_put_deemph),
पूर्ण;

/* Output Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8731_output_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Line Bypass Switch", WM8731_APANA, 3, 1, 0),
SOC_DAPM_SINGLE("Mic Sidetone Switch", WM8731_APANA, 5, 1, 0),
SOC_DAPM_SINGLE("HiFi Playback Switch", WM8731_APANA, 4, 1, 0),
पूर्ण;

/* Input mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8731_input_mux_controls =
SOC_DAPM_ENUM("Input Select", wm8731_insel_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8731_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_SUPPLY("ACTIVE",WM8731_ACTIVE, 0, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("OSC", WM8731_PWR, 5, 1, शून्य, 0),
SND_SOC_DAPM_MIXER("Output Mixer", WM8731_PWR, 4, 1,
	&wm8731_output_mixer_controls[0],
	ARRAY_SIZE(wm8731_output_mixer_controls)),
SND_SOC_DAPM_DAC("DAC", "HiFi Playback", WM8731_PWR, 3, 1),
SND_SOC_DAPM_OUTPUT("LOUT"),
SND_SOC_DAPM_OUTPUT("LHPOUT"),
SND_SOC_DAPM_OUTPUT("ROUT"),
SND_SOC_DAPM_OUTPUT("RHPOUT"),
SND_SOC_DAPM_ADC("ADC", "HiFi Capture", WM8731_PWR, 2, 1),
SND_SOC_DAPM_MUX("Input Mux", SND_SOC_NOPM, 0, 0, &wm8731_input_mux_controls),
SND_SOC_DAPM_PGA("Line Input", WM8731_PWR, 0, 1, शून्य, 0),
SND_SOC_DAPM_MICBIAS("Mic Bias", WM8731_PWR, 1, 1),
SND_SOC_DAPM_INPUT("MICIN"),
SND_SOC_DAPM_INPUT("RLINEIN"),
SND_SOC_DAPM_INPUT("LLINEIN"),
पूर्ण;

अटल पूर्णांक wm8731_check_osc(काष्ठा snd_soc_dapm_widget *source,
			    काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा wm8731_priv *wm8731 = snd_soc_component_get_drvdata(component);

	वापस wm8731->sysclk_type == WM8731_SYSCLK_XTAL;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route wm8731_पूर्णांकercon[] = अणु
	अणु"DAC", शून्य, "OSC", wm8731_check_oscपूर्ण,
	अणु"ADC", शून्य, "OSC", wm8731_check_oscपूर्ण,
	अणु"DAC", शून्य, "ACTIVE"पूर्ण,
	अणु"ADC", शून्य, "ACTIVE"पूर्ण,

	/* output mixer */
	अणु"Output Mixer", "Line Bypass Switch", "Line Input"पूर्ण,
	अणु"Output Mixer", "HiFi Playback Switch", "DAC"पूर्ण,
	अणु"Output Mixer", "Mic Sidetone Switch", "Mic Bias"पूर्ण,

	/* outमाला_दो */
	अणु"RHPOUT", शून्य, "Output Mixer"पूर्ण,
	अणु"ROUT", शून्य, "Output Mixer"पूर्ण,
	अणु"LHPOUT", शून्य, "Output Mixer"पूर्ण,
	अणु"LOUT", शून्य, "Output Mixer"पूर्ण,

	/* input mux */
	अणु"Input Mux", "Line In", "Line Input"पूर्ण,
	अणु"Input Mux", "Mic", "Mic Bias"पूर्ण,
	अणु"ADC", शून्य, "Input Mux"पूर्ण,

	/* inमाला_दो */
	अणु"Line Input", शून्य, "LLINEIN"पूर्ण,
	अणु"Line Input", शून्य, "RLINEIN"पूर्ण,
	अणु"Mic Bias", शून्य, "MICIN"पूर्ण,
पूर्ण;

काष्ठा _coeff_भाग अणु
	u32 mclk;
	u32 rate;
	u16 fs;
	u8 sr:4;
	u8 bosr:1;
	u8 usb:1;
पूर्ण;

/* codec mclk घड़ी भागider coefficients */
अटल स्थिर काष्ठा _coeff_भाग coeff_भाग[] = अणु
	/* 48k */
	अणु12288000, 48000, 256, 0x0, 0x0, 0x0पूर्ण,
	अणु18432000, 48000, 384, 0x0, 0x1, 0x0पूर्ण,
	अणु12000000, 48000, 250, 0x0, 0x0, 0x1पूर्ण,

	/* 32k */
	अणु12288000, 32000, 384, 0x6, 0x0, 0x0पूर्ण,
	अणु18432000, 32000, 576, 0x6, 0x1, 0x0पूर्ण,
	अणु12000000, 32000, 375, 0x6, 0x0, 0x1पूर्ण,

	/* 8k */
	अणु12288000, 8000, 1536, 0x3, 0x0, 0x0पूर्ण,
	अणु18432000, 8000, 2304, 0x3, 0x1, 0x0पूर्ण,
	अणु11289600, 8000, 1408, 0xb, 0x0, 0x0पूर्ण,
	अणु16934400, 8000, 2112, 0xb, 0x1, 0x0पूर्ण,
	अणु12000000, 8000, 1500, 0x3, 0x0, 0x1पूर्ण,

	/* 96k */
	अणु12288000, 96000, 128, 0x7, 0x0, 0x0पूर्ण,
	अणु18432000, 96000, 192, 0x7, 0x1, 0x0पूर्ण,
	अणु12000000, 96000, 125, 0x7, 0x0, 0x1पूर्ण,

	/* 44.1k */
	अणु11289600, 44100, 256, 0x8, 0x0, 0x0पूर्ण,
	अणु16934400, 44100, 384, 0x8, 0x1, 0x0पूर्ण,
	अणु12000000, 44100, 272, 0x8, 0x1, 0x1पूर्ण,

	/* 88.2k */
	अणु11289600, 88200, 128, 0xf, 0x0, 0x0पूर्ण,
	अणु16934400, 88200, 192, 0xf, 0x1, 0x0पूर्ण,
	अणु12000000, 88200, 136, 0xf, 0x1, 0x1पूर्ण,
पूर्ण;

/* rates स्थिरraपूर्णांकs */
अटल स्थिर अचिन्हित पूर्णांक wm8731_rates_12000000[] = अणु
	8000, 32000, 44100, 48000, 96000, 88200,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक wm8731_rates_12288000_18432000[] = अणु
	8000, 32000, 48000, 96000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक wm8731_rates_11289600_16934400[] = अणु
	8000, 44100, 88200,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list wm8731_स्थिरraपूर्णांकs_12000000 = अणु
	.list = wm8731_rates_12000000,
	.count = ARRAY_SIZE(wm8731_rates_12000000),
पूर्ण;

अटल स्थिर
काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list wm8731_स्थिरraपूर्णांकs_12288000_18432000 = अणु
	.list = wm8731_rates_12288000_18432000,
	.count = ARRAY_SIZE(wm8731_rates_12288000_18432000),
पूर्ण;

अटल स्थिर
काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list wm8731_स्थिरraपूर्णांकs_11289600_16934400 = अणु
	.list = wm8731_rates_11289600_16934400,
	.count = ARRAY_SIZE(wm8731_rates_11289600_16934400),
पूर्ण;

अटल अंतरभूत पूर्णांक get_coeff(पूर्णांक mclk, पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(coeff_भाग); i++) अणु
		अगर (coeff_भाग[i].rate == rate && coeff_भाग[i].mclk == mclk)
			वापस i;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wm8731_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8731_priv *wm8731 = snd_soc_component_get_drvdata(component);
	u16 अगरace = snd_soc_component_पढ़ो(component, WM8731_IFACE) & 0xfff3;
	पूर्णांक i = get_coeff(wm8731->sysclk, params_rate(params));
	u16 srate = (coeff_भाग[i].sr << 2) |
		(coeff_भाग[i].bosr << 1) | coeff_भाग[i].usb;

	wm8731->playback_fs = params_rate(params);

	snd_soc_component_ग_लिखो(component, WM8731_SRATE, srate);

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		अगरace |= 0x0004;
		अवरोध;
	हाल 24:
		अगरace |= 0x0008;
		अवरोध;
	हाल 32:
		अगरace |= 0x000c;
		अवरोध;
	पूर्ण

	wm8731_set_deemph(component);

	snd_soc_component_ग_लिखो(component, WM8731_IFACE, अगरace);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8731_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 mute_reg = snd_soc_component_पढ़ो(component, WM8731_APDIGI) & 0xfff7;

	अगर (mute)
		snd_soc_component_ग_लिखो(component, WM8731_APDIGI, mute_reg | 0x8);
	अन्यथा
		snd_soc_component_ग_लिखो(component, WM8731_APDIGI, mute_reg);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8731_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा wm8731_priv *wm8731 = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल WM8731_SYSCLK_XTAL:
	हाल WM8731_SYSCLK_MCLK:
		अगर (wm8731->mclk && clk_set_rate(wm8731->mclk, freq))
			वापस -EINVAL;
		wm8731->sysclk_type = clk_id;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (freq) अणु
	हाल 0:
		wm8731->स्थिरraपूर्णांकs = शून्य;
		अवरोध;
	हाल 12000000:
		wm8731->स्थिरraपूर्णांकs = &wm8731_स्थिरraपूर्णांकs_12000000;
		अवरोध;
	हाल 12288000:
	हाल 18432000:
		wm8731->स्थिरraपूर्णांकs = &wm8731_स्थिरraपूर्णांकs_12288000_18432000;
		अवरोध;
	हाल 16934400:
	हाल 11289600:
		wm8731->स्थिरraपूर्णांकs = &wm8731_स्थिरraपूर्णांकs_11289600_16934400;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	wm8731->sysclk = freq;

	snd_soc_dapm_sync(dapm);

	वापस 0;
पूर्ण


अटल पूर्णांक wm8731_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 अगरace = 0;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगरace |= 0x0040;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= 0x0002;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= 0x0001;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace |= 0x0013;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगरace |= 0x0003;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= 0x0090;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= 0x0080;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगरace |= 0x0010;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set अगरace */
	snd_soc_component_ग_लिखो(component, WM8731_IFACE, अगरace);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8731_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8731_priv *wm8731 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;
	u16 reg;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अगर (wm8731->mclk) अणु
			ret = clk_prepare_enable(wm8731->mclk);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8731->supplies),
						    wm8731->supplies);
			अगर (ret != 0)
				वापस ret;

			regcache_sync(wm8731->regmap);
		पूर्ण

		/* Clear PWROFF, gate CLKOUT, everything अन्यथा as-is */
		reg = snd_soc_component_पढ़ो(component, WM8731_PWR) & 0xff7f;
		snd_soc_component_ग_लिखो(component, WM8731_PWR, reg | 0x0040);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		अगर (wm8731->mclk)
			clk_disable_unprepare(wm8731->mclk);
		snd_soc_component_ग_लिखो(component, WM8731_PWR, 0xffff);
		regulator_bulk_disable(ARRAY_SIZE(wm8731->supplies),
				       wm8731->supplies);
		regcache_mark_dirty(wm8731->regmap);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wm8731_startup(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा wm8731_priv *wm8731 = snd_soc_component_get_drvdata(dai->component);

	अगर (wm8731->स्थिरraपूर्णांकs)
		snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					   SNDRV_PCM_HW_PARAM_RATE,
					   wm8731->स्थिरraपूर्णांकs);

	वापस 0;
पूर्ण

#घोषणा WM8731_RATES SNDRV_PCM_RATE_8000_96000

#घोषणा WM8731_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
	SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8731_dai_ops = अणु
	.startup	= wm8731_startup,
	.hw_params	= wm8731_hw_params,
	.mute_stream	= wm8731_mute,
	.set_sysclk	= wm8731_set_dai_sysclk,
	.set_fmt	= wm8731_set_dai_fmt,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8731_dai = अणु
	.name = "wm8731-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8731_RATES,
		.क्रमmats = WM8731_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8731_RATES,
		.क्रमmats = WM8731_FORMATS,पूर्ण,
	.ops = &wm8731_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक wm8731_request_supplies(काष्ठा device *dev,
		काष्ठा wm8731_priv *wm8731)
अणु
	पूर्णांक ret = 0, i;

	क्रम (i = 0; i < ARRAY_SIZE(wm8731->supplies); i++)
		wm8731->supplies[i].supply = wm8731_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(wm8731->supplies),
				 wm8731->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8731->supplies),
				    wm8731->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8731_hw_init(काष्ठा device *dev, काष्ठा wm8731_priv *wm8731)
अणु
	पूर्णांक ret = 0;

	ret = wm8731_reset(wm8731->regmap);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to issue reset: %d\n", ret);
		जाओ err_regulator_enable;
	पूर्ण

	/* Clear POWEROFF, keep everything अन्यथा disabled */
	regmap_ग_लिखो(wm8731->regmap, WM8731_PWR, 0x7f);

	/* Latch the update bits */
	regmap_update_bits(wm8731->regmap, WM8731_LOUT1V, 0x100, 0);
	regmap_update_bits(wm8731->regmap, WM8731_ROUT1V, 0x100, 0);
	regmap_update_bits(wm8731->regmap, WM8731_LINVOL, 0x100, 0);
	regmap_update_bits(wm8731->regmap, WM8731_RINVOL, 0x100, 0);

	/* Disable bypass path by शेष */
	regmap_update_bits(wm8731->regmap, WM8731_APANA, 0x8, 0);

	regcache_mark_dirty(wm8731->regmap);

err_regulator_enable:
	/* Regulators will be enabled by bias management */
	regulator_bulk_disable(ARRAY_SIZE(wm8731->supplies), wm8731->supplies);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8731 = अणु
	.set_bias_level		= wm8731_set_bias_level,
	.controls		= wm8731_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8731_snd_controls),
	.dapm_widमाला_लो		= wm8731_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8731_dapm_widमाला_लो),
	.dapm_routes		= wm8731_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(wm8731_पूर्णांकercon),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wm8731_of_match[] = अणु
	अणु .compatible = "wlf,wm8731", पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, wm8731_of_match);

अटल स्थिर काष्ठा regmap_config wm8731_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,

	.max_रेजिस्टर = WM8731_RESET,
	.अस्थिर_reg = wm8731_अस्थिर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = wm8731_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8731_reg_शेषs),
पूर्ण;

#अगर defined(CONFIG_SPI_MASTER)
अटल पूर्णांक wm8731_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wm8731_priv *wm8731;
	पूर्णांक ret;

	wm8731 = devm_kzalloc(&spi->dev, माप(*wm8731), GFP_KERNEL);
	अगर (wm8731 == शून्य)
		वापस -ENOMEM;

	wm8731->mclk = devm_clk_get(&spi->dev, "mclk");
	अगर (IS_ERR(wm8731->mclk)) अणु
		ret = PTR_ERR(wm8731->mclk);
		अगर (ret == -ENOENT) अणु
			wm8731->mclk = शून्य;
			dev_warn(&spi->dev, "Assuming static MCLK\n");
		पूर्ण अन्यथा अणु
			dev_err(&spi->dev, "Failed to get MCLK: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_init(&wm8731->lock);

	spi_set_drvdata(spi, wm8731);

	ret = wm8731_request_supplies(&spi->dev, wm8731);
	अगर (ret != 0)
		वापस ret;

	wm8731->regmap = devm_regmap_init_spi(spi, &wm8731_regmap);
	अगर (IS_ERR(wm8731->regmap)) अणु
		ret = PTR_ERR(wm8731->regmap);
		dev_err(&spi->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = wm8731_hw_init(&spi->dev, wm8731);
	अगर (ret != 0)
		वापस ret;

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
			&soc_component_dev_wm8731, &wm8731_dai, 1);
	अगर (ret != 0) अणु
		dev_err(&spi->dev, "Failed to register CODEC: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8731_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा spi_driver wm8731_spi_driver = अणु
	.driver = अणु
		.name	= "wm8731",
		.of_match_table = wm8731_of_match,
	पूर्ण,
	.probe		= wm8731_spi_probe,
	.हटाओ		= wm8731_spi_हटाओ,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SPI_MASTER */

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक wm8731_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8731_priv *wm8731;
	पूर्णांक ret;

	wm8731 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8731_priv),
			      GFP_KERNEL);
	अगर (wm8731 == शून्य)
		वापस -ENOMEM;

	wm8731->mclk = devm_clk_get(&i2c->dev, "mclk");
	अगर (IS_ERR(wm8731->mclk)) अणु
		ret = PTR_ERR(wm8731->mclk);
		अगर (ret == -ENOENT) अणु
			wm8731->mclk = शून्य;
			dev_warn(&i2c->dev, "Assuming static MCLK\n");
		पूर्ण अन्यथा अणु
			dev_err(&i2c->dev, "Failed to get MCLK: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_init(&wm8731->lock);

	i2c_set_clientdata(i2c, wm8731);

	ret = wm8731_request_supplies(&i2c->dev, wm8731);
	अगर (ret != 0)
		वापस ret;

	wm8731->regmap = devm_regmap_init_i2c(i2c, &wm8731_regmap);
	अगर (IS_ERR(wm8731->regmap)) अणु
		ret = PTR_ERR(wm8731->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = wm8731_hw_init(&i2c->dev, wm8731);
	अगर (ret != 0)
		वापस ret;

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8731, &wm8731_dai, 1);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to register CODEC: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8731_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8731_i2c_id[] = अणु
	अणु "wm8731", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8731_i2c_id);

अटल काष्ठा i2c_driver wm8731_i2c_driver = अणु
	.driver = अणु
		.name = "wm8731",
		.of_match_table = wm8731_of_match,
	पूर्ण,
	.probe =    wm8731_i2c_probe,
	.हटाओ =   wm8731_i2c_हटाओ,
	.id_table = wm8731_i2c_id,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init wm8731_modinit(व्योम)
अणु
	पूर्णांक ret = 0;
#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&wm8731_i2c_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register WM8731 I2C driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&wm8731_spi_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register WM8731 SPI driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण
module_init(wm8731_modinit);

अटल व्योम __निकास wm8731_निकास(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&wm8731_i2c_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&wm8731_spi_driver);
#पूर्ण_अगर
पूर्ण
module_निकास(wm8731_निकास);

MODULE_DESCRIPTION("ASoC WM8731 driver");
MODULE_AUTHOR("Richard Purdie");
MODULE_LICENSE("GPL");
