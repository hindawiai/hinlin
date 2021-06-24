<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AD193X Audio Codec driver supporting AD1936/7/8/9
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "ad193x.h"

/* codec निजी data */
काष्ठा ad193x_priv अणु
	काष्ठा regmap *regmap;
	क्रमागत ad193x_type type;
	पूर्णांक sysclk;
पूर्ण;

/*
 * AD193X volume/mute/de-emphasis etc. controls
 */
अटल स्थिर अक्षर * स्थिर ad193x_deemp[] = अणु"None", "48kHz", "44.1kHz", "32kHz"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(ad193x_deemp_क्रमागत, AD193X_DAC_CTRL2, 1,
			    ad193x_deemp);

अटल स्थिर DECLARE_TLV_DB_MINMAX(adau193x_tlv, -9563, 0);

अटल स्थिर अचिन्हित पूर्णांक ad193x_sb[] = अणु32पूर्ण;

अटल काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरr = अणु
	.list = ad193x_sb,
	.count = ARRAY_SIZE(ad193x_sb),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ad193x_snd_controls[] = अणु
	/* DAC volume control */
	SOC_DOUBLE_R_TLV("DAC1 Volume", AD193X_DAC_L1_VOL,
			AD193X_DAC_R1_VOL, 0, 0xFF, 1, adau193x_tlv),
	SOC_DOUBLE_R_TLV("DAC2 Volume", AD193X_DAC_L2_VOL,
			AD193X_DAC_R2_VOL, 0, 0xFF, 1, adau193x_tlv),
	SOC_DOUBLE_R_TLV("DAC3 Volume", AD193X_DAC_L3_VOL,
			AD193X_DAC_R3_VOL, 0, 0xFF, 1, adau193x_tlv),
	SOC_DOUBLE_R_TLV("DAC4 Volume", AD193X_DAC_L4_VOL,
			AD193X_DAC_R4_VOL, 0, 0xFF, 1, adau193x_tlv),

	/* DAC चयन control */
	SOC_DOUBLE("DAC1 Switch", AD193X_DAC_CHNL_MUTE, AD193X_DACL1_MUTE,
		AD193X_DACR1_MUTE, 1, 1),
	SOC_DOUBLE("DAC2 Switch", AD193X_DAC_CHNL_MUTE, AD193X_DACL2_MUTE,
		AD193X_DACR2_MUTE, 1, 1),
	SOC_DOUBLE("DAC3 Switch", AD193X_DAC_CHNL_MUTE, AD193X_DACL3_MUTE,
		AD193X_DACR3_MUTE, 1, 1),
	SOC_DOUBLE("DAC4 Switch", AD193X_DAC_CHNL_MUTE, AD193X_DACL4_MUTE,
		AD193X_DACR4_MUTE, 1, 1),

	/* DAC de-emphasis */
	SOC_ENUM("Playback Deemphasis", ad193x_deemp_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ad193x_adc_snd_controls[] = अणु
	/* ADC चयन control */
	SOC_DOUBLE("ADC1 Switch", AD193X_ADC_CTRL0, AD193X_ADCL1_MUTE,
		AD193X_ADCR1_MUTE, 1, 1),
	SOC_DOUBLE("ADC2 Switch", AD193X_ADC_CTRL0, AD193X_ADCL2_MUTE,
		AD193X_ADCR2_MUTE, 1, 1),

	/* ADC high-pass filter */
	SOC_SINGLE("ADC High Pass Filter Switch", AD193X_ADC_CTRL0,
			AD193X_ADC_HIGHPASS_FILTER, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget ad193x_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DAC", "Playback", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_PGA("DAC Output", AD193X_DAC_CTRL0, 0, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL_PWR", AD193X_PLL_CLK_CTRL0, 0, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SYSCLK", AD193X_PLL_CLK_CTRL0, 7, 0, शून्य, 0),
	SND_SOC_DAPM_VMID("VMID"),
	SND_SOC_DAPM_OUTPUT("DAC1OUT"),
	SND_SOC_DAPM_OUTPUT("DAC2OUT"),
	SND_SOC_DAPM_OUTPUT("DAC3OUT"),
	SND_SOC_DAPM_OUTPUT("DAC4OUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget ad193x_adc_widमाला_लो[] = अणु
	SND_SOC_DAPM_ADC("ADC", "Capture", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SUPPLY("ADC_PWR", AD193X_ADC_CTRL0, 0, 1, शून्य, 0),
	SND_SOC_DAPM_INPUT("ADC1IN"),
	SND_SOC_DAPM_INPUT("ADC2IN"),
पूर्ण;

अटल पूर्णांक ad193x_check_pll(काष्ठा snd_soc_dapm_widget *source,
			    काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा ad193x_priv *ad193x = snd_soc_component_get_drvdata(component);

	वापस !!ad193x->sysclk;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route audio_paths[] = अणु
	अणु "DAC", शून्य, "SYSCLK" पूर्ण,
	अणु "DAC Output", शून्य, "DAC" पूर्ण,
	अणु "DAC Output", शून्य, "VMID" पूर्ण,
	अणु "DAC1OUT", शून्य, "DAC Output" पूर्ण,
	अणु "DAC2OUT", शून्य, "DAC Output" पूर्ण,
	अणु "DAC3OUT", शून्य, "DAC Output" पूर्ण,
	अणु "DAC4OUT", शून्य, "DAC Output" पूर्ण,
	अणु "SYSCLK", शून्य, "PLL_PWR", &ad193x_check_pll पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ad193x_adc_audio_paths[] = अणु
	अणु "ADC", शून्य, "SYSCLK" पूर्ण,
	अणु "ADC", शून्य, "ADC_PWR" पूर्ण,
	अणु "ADC", शून्य, "ADC1IN" पूर्ण,
	अणु "ADC", शून्य, "ADC2IN" पूर्ण,
पूर्ण;

अटल अंतरभूत bool ad193x_has_adc(स्थिर काष्ठा ad193x_priv *ad193x)
अणु
	चयन (ad193x->type) अणु
	हाल AD1933:
	हाल AD1934:
		वापस false;
	शेष:
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

/*
 * DAI ops entries
 */

अटल पूर्णांक ad193x_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा ad193x_priv *ad193x = snd_soc_component_get_drvdata(dai->component);

	अगर (mute)
		regmap_update_bits(ad193x->regmap, AD193X_DAC_CTRL2,
				    AD193X_DAC_MASTER_MUTE,
				    AD193X_DAC_MASTER_MUTE);
	अन्यथा
		regmap_update_bits(ad193x->regmap, AD193X_DAC_CTRL2,
				    AD193X_DAC_MASTER_MUTE, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ad193x_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			       अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक width)
अणु
	काष्ठा ad193x_priv *ad193x = snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक channels;

	चयन (slots) अणु
	हाल 2:
		channels = AD193X_2_CHANNELS;
		अवरोध;
	हाल 4:
		channels = AD193X_4_CHANNELS;
		अवरोध;
	हाल 8:
		channels = AD193X_8_CHANNELS;
		अवरोध;
	हाल 16:
		channels = AD193X_16_CHANNELS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(ad193x->regmap, AD193X_DAC_CTRL1,
		AD193X_DAC_CHAN_MASK, channels << AD193X_DAC_CHAN_SHFT);
	अगर (ad193x_has_adc(ad193x))
		regmap_update_bits(ad193x->regmap, AD193X_ADC_CTRL2,
				   AD193X_ADC_CHAN_MASK,
				   channels << AD193X_ADC_CHAN_SHFT);

	वापस 0;
पूर्ण

अटल पूर्णांक ad193x_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा ad193x_priv *ad193x = snd_soc_component_get_drvdata(codec_dai->component);
	अचिन्हित पूर्णांक adc_serfmt = 0;
	अचिन्हित पूर्णांक dac_serfmt = 0;
	अचिन्हित पूर्णांक adc_fmt = 0;
	अचिन्हित पूर्णांक dac_fmt = 0;

	/* At present, the driver only support AUX ADC mode(SND_SOC_DAIFMT_I2S
	 * with TDM), ADC&DAC TDM mode(SND_SOC_DAIFMT_DSP_A) and DAC I2S mode
	 * (SND_SOC_DAIFMT_I2S)
	 */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		adc_serfmt |= AD193X_ADC_SERFMT_TDM;
		dac_serfmt |= AD193X_DAC_SERFMT_STEREO;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		adc_serfmt |= AD193X_ADC_SERFMT_AUX;
		dac_serfmt |= AD193X_DAC_SERFMT_TDM;
		अवरोध;
	शेष:
		अगर (ad193x_has_adc(ad193x))
			वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF: /* normal bit घड़ी + frame */
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF: /* normal bclk + invert frm */
		adc_fmt |= AD193X_ADC_LEFT_HIGH;
		dac_fmt |= AD193X_DAC_LEFT_HIGH;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF: /* invert bclk + normal frm */
		adc_fmt |= AD193X_ADC_BCLK_INV;
		dac_fmt |= AD193X_DAC_BCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF: /* invert bclk + frm */
		adc_fmt |= AD193X_ADC_LEFT_HIGH;
		adc_fmt |= AD193X_ADC_BCLK_INV;
		dac_fmt |= AD193X_DAC_LEFT_HIGH;
		dac_fmt |= AD193X_DAC_BCLK_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* For DSP_*, LRCLK's polarity must be inverted */
	अगर (fmt & SND_SOC_DAIFMT_DSP_A)
		dac_fmt ^= AD193X_DAC_LEFT_HIGH;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM: /* codec clk & frm master */
		adc_fmt |= AD193X_ADC_LCR_MASTER;
		adc_fmt |= AD193X_ADC_BCLK_MASTER;
		dac_fmt |= AD193X_DAC_LCR_MASTER;
		dac_fmt |= AD193X_DAC_BCLK_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM: /* codec clk slave & frm master */
		adc_fmt |= AD193X_ADC_LCR_MASTER;
		dac_fmt |= AD193X_DAC_LCR_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS: /* codec clk master & frame slave */
		adc_fmt |= AD193X_ADC_BCLK_MASTER;
		dac_fmt |= AD193X_DAC_BCLK_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS: /* codec clk & frm slave */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ad193x_has_adc(ad193x)) अणु
		regmap_update_bits(ad193x->regmap, AD193X_ADC_CTRL1,
				   AD193X_ADC_SERFMT_MASK, adc_serfmt);
		regmap_update_bits(ad193x->regmap, AD193X_ADC_CTRL2,
				   AD193X_ADC_FMT_MASK, adc_fmt);
	पूर्ण
	regmap_update_bits(ad193x->regmap, AD193X_DAC_CTRL0,
			   AD193X_DAC_SERFMT_MASK, dac_serfmt);
	regmap_update_bits(ad193x->regmap, AD193X_DAC_CTRL1,
		AD193X_DAC_FMT_MASK, dac_fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक ad193x_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा ad193x_priv *ad193x = snd_soc_component_get_drvdata(component);

	अगर (clk_id == AD193X_SYSCLK_MCLK) अणु
		/* MCLK must be 512 x fs */
		अगर (dir == SND_SOC_CLOCK_OUT || freq != 24576000)
			वापस -EINVAL;

		regmap_update_bits(ad193x->regmap, AD193X_PLL_CLK_CTRL1,
				   AD193X_PLL_SRC_MASK,
				   AD193X_PLL_DAC_SRC_MCLK |
				   AD193X_PLL_CLK_SRC_MCLK);

		snd_soc_dapm_sync(dapm);
		वापस 0;
	पूर्ण
	चयन (freq) अणु
	हाल 12288000:
	हाल 18432000:
	हाल 24576000:
	हाल 36864000:
		ad193x->sysclk = freq;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad193x_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params,
		काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक word_len = 0, master_rate = 0;
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ad193x_priv *ad193x = snd_soc_component_get_drvdata(component);

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		word_len = 3;
		अवरोध;
	हाल 20:
		word_len = 1;
		अवरोध;
	हाल 24:
	हाल 32:
		word_len = 0;
		अवरोध;
	पूर्ण

	चयन (ad193x->sysclk) अणु
	हाल 12288000:
		master_rate = AD193X_PLL_INPUT_256;
		अवरोध;
	हाल 18432000:
		master_rate = AD193X_PLL_INPUT_384;
		अवरोध;
	हाल 24576000:
		master_rate = AD193X_PLL_INPUT_512;
		अवरोध;
	हाल 36864000:
		master_rate = AD193X_PLL_INPUT_768;
		अवरोध;
	पूर्ण

	regmap_update_bits(ad193x->regmap, AD193X_PLL_CLK_CTRL0,
			    AD193X_PLL_INPUT_MASK, master_rate);

	regmap_update_bits(ad193x->regmap, AD193X_DAC_CTRL2,
			    AD193X_DAC_WORD_LEN_MASK,
			    word_len << AD193X_DAC_WORD_LEN_SHFT);

	अगर (ad193x_has_adc(ad193x))
		regmap_update_bits(ad193x->regmap, AD193X_ADC_CTRL1,
				   AD193X_ADC_WORD_LEN_MASK, word_len);

	वापस 0;
पूर्ण

अटल पूर्णांक ad193x_startup(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_soc_dai *dai)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_SAMPLE_BITS,
				   &स्थिरr);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ad193x_dai_ops = अणु
	.startup = ad193x_startup,
	.hw_params = ad193x_hw_params,
	.mute_stream = ad193x_mute,
	.set_tdm_slot = ad193x_set_tdm_slot,
	.set_sysclk	= ad193x_set_dai_sysclk,
	.set_fmt = ad193x_set_dai_fmt,
	.no_capture_mute = 1,
पूर्ण;

/* codec DAI instance */
अटल काष्ठा snd_soc_dai_driver ad193x_dai = अणु
	.name = "ad193x-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_LE |
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 4,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_LE |
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
	.ops = &ad193x_dai_ops,
पूर्ण;

/* codec DAI instance क्रम DAC only */
अटल काष्ठा snd_soc_dai_driver ad193x_no_adc_dai = अणु
	.name = "ad193x-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_LE |
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
	.ops = &ad193x_dai_ops,
पूर्ण;

/* codec रेजिस्टर values to set after reset */
अटल व्योम ad193x_reg_शेष_init(काष्ठा ad193x_priv *ad193x)
अणु
	अटल स्थिर काष्ठा reg_sequence reg_init[] = अणु
		अणु  0, 0x99 पूर्ण,	/* PLL_CLK_CTRL0: pll input: mclki/xi 12.288Mhz */
		अणु  1, 0x04 पूर्ण,	/* PLL_CLK_CTRL1: no on-chip Vref */
		अणु  2, 0x40 पूर्ण,	/* DAC_CTRL0: TDM mode */
		अणु  3, 0x00 पूर्ण,	/* DAC_CTRL1: reset */
		अणु  4, 0x1A पूर्ण,	/* DAC_CTRL2: 48kHz de-emphasis, unmute dac */
		अणु  5, 0x00 पूर्ण,	/* DAC_CHNL_MUTE: unmute DAC channels */
		अणु  6, 0x00 पूर्ण,	/* DAC_L1_VOL: no attenuation */
		अणु  7, 0x00 पूर्ण,	/* DAC_R1_VOL: no attenuation */
		अणु  8, 0x00 पूर्ण,	/* DAC_L2_VOL: no attenuation */
		अणु  9, 0x00 पूर्ण,	/* DAC_R2_VOL: no attenuation */
		अणु 10, 0x00 पूर्ण,	/* DAC_L3_VOL: no attenuation */
		अणु 11, 0x00 पूर्ण,	/* DAC_R3_VOL: no attenuation */
		अणु 12, 0x00 पूर्ण,	/* DAC_L4_VOL: no attenuation */
		अणु 13, 0x00 पूर्ण,	/* DAC_R4_VOL: no attenuation */
	पूर्ण;
	अटल स्थिर काष्ठा reg_sequence reg_adc_init[] = अणु
		अणु 14, 0x03 पूर्ण,	/* ADC_CTRL0: high-pass filter enable */
		अणु 15, 0x43 पूर्ण,	/* ADC_CTRL1: sata delay=1, adc aux mode */
		अणु 16, 0x00 पूर्ण,	/* ADC_CTRL2: reset */
	पूर्ण;

	regmap_multi_reg_ग_लिखो(ad193x->regmap, reg_init, ARRAY_SIZE(reg_init));

	अगर (ad193x_has_adc(ad193x)) अणु
		regmap_multi_reg_ग_लिखो(ad193x->regmap, reg_adc_init,
				       ARRAY_SIZE(reg_adc_init));
	पूर्ण
पूर्ण

अटल पूर्णांक ad193x_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ad193x_priv *ad193x = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	पूर्णांक num, ret;

	/* शेष setting क्रम ad193x */
	ad193x_reg_शेष_init(ad193x);

	/* adc only */
	अगर (ad193x_has_adc(ad193x)) अणु
		/* add adc controls */
		num = ARRAY_SIZE(ad193x_adc_snd_controls);
		ret = snd_soc_add_component_controls(component,
						 ad193x_adc_snd_controls,
						 num);
		अगर (ret)
			वापस ret;

		/* add adc widमाला_लो */
		num = ARRAY_SIZE(ad193x_adc_widमाला_लो);
		ret = snd_soc_dapm_new_controls(dapm,
						ad193x_adc_widमाला_लो,
						num);
		अगर (ret)
			वापस ret;

		/* add adc routes */
		num = ARRAY_SIZE(ad193x_adc_audio_paths);
		ret = snd_soc_dapm_add_routes(dapm,
					      ad193x_adc_audio_paths,
					      num);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_ad193x = अणु
	.probe			= ad193x_component_probe,
	.controls		= ad193x_snd_controls,
	.num_controls		= ARRAY_SIZE(ad193x_snd_controls),
	.dapm_widमाला_लो		= ad193x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ad193x_dapm_widमाला_लो),
	.dapm_routes		= audio_paths,
	.num_dapm_routes	= ARRAY_SIZE(audio_paths),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

स्थिर काष्ठा regmap_config ad193x_regmap_config = अणु
	.max_रेजिस्टर = AD193X_NUM_REGS - 1,
पूर्ण;
EXPORT_SYMBOL_GPL(ad193x_regmap_config);

पूर्णांक ad193x_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		 क्रमागत ad193x_type type)
अणु
	काष्ठा ad193x_priv *ad193x;

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	ad193x = devm_kzalloc(dev, माप(*ad193x), GFP_KERNEL);
	अगर (ad193x == शून्य)
		वापस -ENOMEM;

	ad193x->regmap = regmap;
	ad193x->type = type;

	dev_set_drvdata(dev, ad193x);

	अगर (ad193x_has_adc(ad193x))
		वापस devm_snd_soc_रेजिस्टर_component(dev, &soc_component_dev_ad193x,
						       &ad193x_dai, 1);
	वापस devm_snd_soc_रेजिस्टर_component(dev, &soc_component_dev_ad193x,
		&ad193x_no_adc_dai, 1);
पूर्ण
EXPORT_SYMBOL_GPL(ad193x_probe);

MODULE_DESCRIPTION("ASoC ad193x driver");
MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_LICENSE("GPL");
