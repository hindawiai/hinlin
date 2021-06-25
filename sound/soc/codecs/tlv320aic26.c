<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Texas Instruments TLV320AIC26 low घातer audio CODEC
 * ALSA SoC CODEC driver
 *
 * Copyright (C) 2008 Secret Lab Technologies Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>

#समावेश "tlv320aic26.h"

MODULE_DESCRIPTION("ASoC TLV320AIC26 codec driver");
MODULE_AUTHOR("Grant Likely <grant.likely@secretlab.ca>");
MODULE_LICENSE("GPL");

/* AIC26 driver निजी data */
काष्ठा aic26 अणु
	काष्ठा spi_device *spi;
	काष्ठा regmap *regmap;
	काष्ठा snd_soc_component *component;
	पूर्णांक master;
	पूर्णांक datfm;
	पूर्णांक mclk;

	/* Keyclick parameters */
	पूर्णांक keyclick_amplitude;
	पूर्णांक keyclick_freq;
	पूर्णांक keyclick_len;
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tlv320aic26_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("MICIN"),
SND_SOC_DAPM_INPUT("AUX"),

SND_SOC_DAPM_OUTPUT("HPL"),
SND_SOC_DAPM_OUTPUT("HPR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tlv320aic26_dapm_routes[] = अणु
	अणु "Capture", शून्य, "MICIN" पूर्ण,
	अणु "Capture", शून्य, "AUX" पूर्ण,

	अणु "HPL", शून्य, "Playback" पूर्ण,
	अणु "HPR", शून्य, "Playback" पूर्ण,
पूर्ण;

/* ---------------------------------------------------------------------
 * Digital Audio Interface Operations
 */
अटल पूर्णांक aic26_hw_params(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_pcm_hw_params *params,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा aic26 *aic26 = snd_soc_component_get_drvdata(component);
	पूर्णांक fsref, भागisor, wlen, pval, jval, dval, qval;
	u16 reg;

	dev_dbg(&aic26->spi->dev, "aic26_hw_params(substream=%p, params=%p)\n",
		substream, params);
	dev_dbg(&aic26->spi->dev, "rate=%i width=%d\n", params_rate(params),
		params_width(params));

	चयन (params_rate(params)) अणु
	हाल 8000:  fsref = 48000; भागisor = AIC26_DIV_6; अवरोध;
	हाल 11025: fsref = 44100; भागisor = AIC26_DIV_4; अवरोध;
	हाल 12000: fsref = 48000; भागisor = AIC26_DIV_4; अवरोध;
	हाल 16000: fsref = 48000; भागisor = AIC26_DIV_3; अवरोध;
	हाल 22050: fsref = 44100; भागisor = AIC26_DIV_2; अवरोध;
	हाल 24000: fsref = 48000; भागisor = AIC26_DIV_2; अवरोध;
	हाल 32000: fsref = 48000; भागisor = AIC26_DIV_1_5; अवरोध;
	हाल 44100: fsref = 44100; भागisor = AIC26_DIV_1; अवरोध;
	हाल 48000: fsref = 48000; भागisor = AIC26_DIV_1; अवरोध;
	शेष:
		dev_dbg(&aic26->spi->dev, "bad rate\n"); वापस -EINVAL;
	पूर्ण

	/* select data word length */
	चयन (params_width(params)) अणु
	हाल 8:  wlen = AIC26_WLEN_16; अवरोध;
	हाल 16: wlen = AIC26_WLEN_16; अवरोध;
	हाल 24: wlen = AIC26_WLEN_24; अवरोध;
	हाल 32: wlen = AIC26_WLEN_32; अवरोध;
	शेष:
		dev_dbg(&aic26->spi->dev, "bad format\n"); वापस -EINVAL;
	पूर्ण

	/**
	 * Configure PLL
	 * fsref = (mclk * PLLM) / 2048
	 * where PLLM = J.DDDD (DDDD रेजिस्टर ranges from 0 to 9999, decimal)
	 */
	pval = 1;
	/* compute J portion of multiplier */
	jval = fsref / (aic26->mclk / 2048);
	/* compute fractional DDDD component of multiplier */
	dval = fsref - (jval * (aic26->mclk / 2048));
	dval = (10000 * dval) / (aic26->mclk / 2048);
	dev_dbg(&aic26->spi->dev, "Setting PLLM to %d.%04d\n", jval, dval);
	qval = 0;
	reg = 0x8000 | qval << 11 | pval << 8 | jval << 2;
	snd_soc_component_ग_लिखो(component, AIC26_REG_PLL_PROG1, reg);
	reg = dval << 2;
	snd_soc_component_ग_लिखो(component, AIC26_REG_PLL_PROG2, reg);

	/* Audio Control 3 (master mode, fsref rate) */
	अगर (aic26->master)
		reg = 0x0800;
	अगर (fsref == 48000)
		reg = 0x2000;
	snd_soc_component_update_bits(component, AIC26_REG_AUDIO_CTRL3, 0xf800, reg);

	/* Audio Control 1 (FSref भागisor) */
	reg = wlen | aic26->datfm | (भागisor << 3) | भागisor;
	snd_soc_component_update_bits(component, AIC26_REG_AUDIO_CTRL1, 0xfff, reg);

	वापस 0;
पूर्ण

/*
 * aic26_mute - Mute control to reduce noise when changing audio क्रमmat
 */
अटल पूर्णांक aic26_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा aic26 *aic26 = snd_soc_component_get_drvdata(component);
	u16 reg;

	dev_dbg(&aic26->spi->dev, "aic26_mute(dai=%p, mute=%i)\n",
		dai, mute);

	अगर (mute)
		reg = 0x8080;
	अन्यथा
		reg = 0;
	snd_soc_component_update_bits(component, AIC26_REG_DAC_GAIN, 0x8000, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक aic26_set_sysclk(काष्ठा snd_soc_dai *codec_dai,
			    पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा aic26 *aic26 = snd_soc_component_get_drvdata(component);

	dev_dbg(&aic26->spi->dev, "aic26_set_sysclk(dai=%p, clk_id==%i,"
		" freq=%i, dir=%i)\n",
		codec_dai, clk_id, freq, dir);

	/* MCLK needs to fall between 2MHz and 50 MHz */
	अगर ((freq < 2000000) || (freq > 50000000))
		वापस -EINVAL;

	aic26->mclk = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक aic26_set_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा aic26 *aic26 = snd_soc_component_get_drvdata(component);

	dev_dbg(&aic26->spi->dev, "aic26_set_fmt(dai=%p, fmt==%i)\n",
		codec_dai, fmt);

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM: aic26->master = 1; अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS: aic26->master = 0; अवरोध;
	शेष:
		dev_dbg(&aic26->spi->dev, "bad master\n"); वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:     aic26->datfm = AIC26_DATFM_I2S; अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:   aic26->datfm = AIC26_DATFM_DSP; अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J: aic26->datfm = AIC26_DATFM_RIGHTJ; अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:  aic26->datfm = AIC26_DATFM_LEFTJ; अवरोध;
	शेष:
		dev_dbg(&aic26->spi->dev, "bad format\n"); वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------
 * Digital Audio Interface Definition
 */
#घोषणा AIC26_RATES	(SNDRV_PCM_RATE_8000  | SNDRV_PCM_RATE_11025 |\
			 SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 |\
			 SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |\
			 SNDRV_PCM_RATE_48000)
#घोषणा AIC26_FORMATS	(SNDRV_PCM_FMTBIT_S8     | SNDRV_PCM_FMTBIT_S16_BE |\
			 SNDRV_PCM_FMTBIT_S24_BE | SNDRV_PCM_FMTBIT_S32_BE)

अटल स्थिर काष्ठा snd_soc_dai_ops aic26_dai_ops = अणु
	.hw_params	= aic26_hw_params,
	.mute_stream	= aic26_mute,
	.set_sysclk	= aic26_set_sysclk,
	.set_fmt	= aic26_set_fmt,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver aic26_dai = अणु
	.name = "tlv320aic26-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = AIC26_RATES,
		.क्रमmats = AIC26_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = AIC26_RATES,
		.क्रमmats = AIC26_FORMATS,
	पूर्ण,
	.ops = &aic26_dai_ops,
पूर्ण;

/* ---------------------------------------------------------------------
 * ALSA controls
 */
अटल स्थिर अक्षर *aic26_capture_src_text[] = अणु"Mic", "Aux"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(aic26_capture_src_क्रमागत,
			    AIC26_REG_AUDIO_CTRL1, 12,
			    aic26_capture_src_text);

अटल स्थिर काष्ठा snd_kcontrol_new aic26_snd_controls[] = अणु
	/* Output */
	SOC_DOUBLE("PCM Playback Volume", AIC26_REG_DAC_GAIN, 8, 0, 0x7f, 1),
	SOC_DOUBLE("PCM Playback Switch", AIC26_REG_DAC_GAIN, 15, 7, 1, 1),
	SOC_SINGLE("PCM Capture Volume", AIC26_REG_ADC_GAIN, 8, 0x7f, 0),
	SOC_SINGLE("PCM Capture Mute", AIC26_REG_ADC_GAIN, 15, 1, 1),
	SOC_SINGLE("Keyclick activate", AIC26_REG_AUDIO_CTRL2, 15, 0x1, 0),
	SOC_SINGLE("Keyclick amplitude", AIC26_REG_AUDIO_CTRL2, 12, 0x7, 0),
	SOC_SINGLE("Keyclick frequency", AIC26_REG_AUDIO_CTRL2, 8, 0x7, 0),
	SOC_SINGLE("Keyclick period", AIC26_REG_AUDIO_CTRL2, 4, 0xf, 0),
	SOC_ENUM("Capture Source", aic26_capture_src_क्रमागत),
पूर्ण;

/* ---------------------------------------------------------------------
 * SPI device portion of driver: sysfs files क्रम debugging
 */

अटल sमाप_प्रकार aic26_keyclick_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aic26 *aic26 = dev_get_drvdata(dev);
	पूर्णांक val, amp, freq, len;

	val = snd_soc_component_पढ़ो(aic26->component, AIC26_REG_AUDIO_CTRL2);
	amp = (val >> 12) & 0x7;
	freq = (125 << ((val >> 8) & 0x7)) >> 1;
	len = 2 * (1 + ((val >> 4) & 0xf));

	वापस प्र_लिखो(buf, "amp=%x freq=%iHz len=%iclks\n", amp, freq, len);
पूर्ण

/* Any ग_लिखो to the keyclick attribute will trigger the keyclick event */
अटल sमाप_प्रकार aic26_keyclick_set(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aic26 *aic26 = dev_get_drvdata(dev);

	snd_soc_component_update_bits(aic26->component, AIC26_REG_AUDIO_CTRL2,
			    0x8000, 0x800);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(keyclick, 0644, aic26_keyclick_show, aic26_keyclick_set);

/* ---------------------------------------------------------------------
 * SoC CODEC portion of driver: probe and release routines
 */
अटल पूर्णांक aic26_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aic26 *aic26 = dev_get_drvdata(component->dev);
	पूर्णांक ret, reg;

	aic26->component = component;

	/* Reset the codec to घातer on शेषs */
	snd_soc_component_ग_लिखो(component, AIC26_REG_RESET, 0xBB00);

	/* Power up CODEC */
	snd_soc_component_ग_लिखो(component, AIC26_REG_POWER_CTRL, 0);

	/* Audio Control 3 (master mode, fsref rate) */
	reg = snd_soc_component_पढ़ो(component, AIC26_REG_AUDIO_CTRL3);
	reg &= ~0xf800;
	reg |= 0x0800; /* set master mode */
	snd_soc_component_ग_लिखो(component, AIC26_REG_AUDIO_CTRL3, reg);

	/* Register the sysfs files क्रम debugging */
	/* Create SysFS files */
	ret = device_create_file(component->dev, &dev_attr_keyclick);
	अगर (ret)
		dev_info(component->dev, "error creating sysfs files\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver aic26_soc_component_dev = अणु
	.probe			= aic26_probe,
	.controls		= aic26_snd_controls,
	.num_controls		= ARRAY_SIZE(aic26_snd_controls),
	.dapm_widमाला_लो		= tlv320aic26_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tlv320aic26_dapm_widमाला_लो),
	.dapm_routes		= tlv320aic26_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(tlv320aic26_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config aic26_regmap = अणु
	.reg_bits = 16,
	.val_bits = 16,
पूर्ण;

/* ---------------------------------------------------------------------
 * SPI device portion of driver: probe and release routines and SPI
 * 				 driver registration.
 */
अटल पूर्णांक aic26_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा aic26 *aic26;
	पूर्णांक ret;

	dev_dbg(&spi->dev, "probing tlv320aic26 spi device\n");

	/* Allocate driver data */
	aic26 = devm_kzalloc(&spi->dev, माप *aic26, GFP_KERNEL);
	अगर (!aic26)
		वापस -ENOMEM;

	aic26->regmap = devm_regmap_init_spi(spi, &aic26_regmap);
	अगर (IS_ERR(aic26->regmap))
		वापस PTR_ERR(aic26->regmap);

	/* Initialize the driver data */
	aic26->spi = spi;
	dev_set_drvdata(&spi->dev, aic26);
	aic26->master = 1;

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
			&aic26_soc_component_dev, &aic26_dai, 1);
	वापस ret;
पूर्ण

अटल काष्ठा spi_driver aic26_spi = अणु
	.driver = अणु
		.name = "tlv320aic26-codec",
	पूर्ण,
	.probe = aic26_spi_probe,
पूर्ण;

module_spi_driver(aic26_spi);
