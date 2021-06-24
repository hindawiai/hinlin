<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sound/soc/codecs/si476x.c -- Codec driver क्रम SI476X chips
 *
 * Copyright (C) 2012 Innovative Converged Devices(ICD)
 * Copyright (C) 2013 Andrey Smirnov
 *
 * Author: Andrey Smirnov <andrew.smirnov@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>

#समावेश <linux/i2c.h>

#समावेश <linux/mfd/si476x-core.h>

क्रमागत si476x_audio_रेजिस्टरs अणु
	SI476X_DIGITAL_IO_OUTPUT_FORMAT		= 0x0203,
	SI476X_DIGITAL_IO_OUTPUT_SAMPLE_RATE	= 0x0202,
पूर्ण;

क्रमागत si476x_digital_io_output_क्रमmat अणु
	SI476X_DIGITAL_IO_SLOT_SIZE_SHIFT	= 11,
	SI476X_DIGITAL_IO_SAMPLE_SIZE_SHIFT	= 8,
पूर्ण;

#घोषणा SI476X_DIGITAL_IO_OUTPUT_WIDTH_MASK	((0x7 << SI476X_DIGITAL_IO_SLOT_SIZE_SHIFT) | \
						  (0x7 << SI476X_DIGITAL_IO_SAMPLE_SIZE_SHIFT))
#घोषणा SI476X_DIGITAL_IO_OUTPUT_FORMAT_MASK	(0x7e)

क्रमागत si476x_daudio_क्रमmats अणु
	SI476X_DAUDIO_MODE_I2S		= (0x0 << 1),
	SI476X_DAUDIO_MODE_DSP_A	= (0x6 << 1),
	SI476X_DAUDIO_MODE_DSP_B	= (0x7 << 1),
	SI476X_DAUDIO_MODE_LEFT_J	= (0x8 << 1),
	SI476X_DAUDIO_MODE_RIGHT_J	= (0x9 << 1),

	SI476X_DAUDIO_MODE_IB		= (1 << 5),
	SI476X_DAUDIO_MODE_IF		= (1 << 6),
पूर्ण;

क्रमागत si476x_pcm_क्रमmat अणु
	SI476X_PCM_FORMAT_S8		= 2,
	SI476X_PCM_FORMAT_S16_LE	= 4,
	SI476X_PCM_FORMAT_S20_3LE	= 5,
	SI476X_PCM_FORMAT_S24_LE	= 6,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget si476x_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_OUTPUT("LOUT"),
SND_SOC_DAPM_OUTPUT("ROUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route si476x_dapm_routes[] = अणु
	अणु "Capture", शून्य, "LOUT" पूर्ण,
	अणु "Capture", शून्य, "ROUT" पूर्ण,
पूर्ण;

अटल पूर्णांक si476x_codec_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
				    अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा si476x_core *core = i2c_mfd_cell_to_core(codec_dai->dev);
	पूर्णांक err;
	u16 क्रमmat = 0;

	अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS)
		वापस -EINVAL;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		क्रमmat |= SI476X_DAUDIO_MODE_DSP_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		क्रमmat |= SI476X_DAUDIO_MODE_DSP_B;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		क्रमmat |= SI476X_DAUDIO_MODE_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		क्रमmat |= SI476X_DAUDIO_MODE_RIGHT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		क्रमmat |= SI476X_DAUDIO_MODE_LEFT_J;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			क्रमmat |= SI476X_DAUDIO_MODE_IB;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_RIGHT_J:
	हाल SND_SOC_DAIFMT_LEFT_J:
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			क्रमmat |= SI476X_DAUDIO_MODE_IB |
				SI476X_DAUDIO_MODE_IF;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			क्रमmat |= SI476X_DAUDIO_MODE_IB;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			क्रमmat |= SI476X_DAUDIO_MODE_IF;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	si476x_core_lock(core);

	err = snd_soc_component_update_bits(codec_dai->component, SI476X_DIGITAL_IO_OUTPUT_FORMAT,
				  SI476X_DIGITAL_IO_OUTPUT_FORMAT_MASK,
				  क्रमmat);

	si476x_core_unlock(core);

	अगर (err < 0) अणु
		dev_err(codec_dai->component->dev, "Failed to set output format\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si476x_codec_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा si476x_core *core = i2c_mfd_cell_to_core(dai->dev);
	पूर्णांक rate, width, err;

	rate = params_rate(params);
	अगर (rate < 32000 || rate > 48000) अणु
		dev_err(dai->component->dev, "Rate: %d is not supported\n", rate);
		वापस -EINVAL;
	पूर्ण

	चयन (params_width(params)) अणु
	हाल 8:
		width = SI476X_PCM_FORMAT_S8;
		अवरोध;
	हाल 16:
		width = SI476X_PCM_FORMAT_S16_LE;
		अवरोध;
	हाल 20:
		width = SI476X_PCM_FORMAT_S20_3LE;
		अवरोध;
	हाल 24:
		width = SI476X_PCM_FORMAT_S24_LE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	si476x_core_lock(core);

	err = snd_soc_component_ग_लिखो(dai->component, SI476X_DIGITAL_IO_OUTPUT_SAMPLE_RATE,
			    rate);
	अगर (err < 0) अणु
		dev_err(dai->component->dev, "Failed to set sample rate\n");
		जाओ out;
	पूर्ण

	err = snd_soc_component_update_bits(dai->component, SI476X_DIGITAL_IO_OUTPUT_FORMAT,
				  SI476X_DIGITAL_IO_OUTPUT_WIDTH_MASK,
				  (width << SI476X_DIGITAL_IO_SLOT_SIZE_SHIFT) |
				  (width << SI476X_DIGITAL_IO_SAMPLE_SIZE_SHIFT));
	अगर (err < 0) अणु
		dev_err(dai->component->dev, "Failed to set output width\n");
		जाओ out;
	पूर्ण

out:
	si476x_core_unlock(core);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops si476x_dai_ops = अणु
	.hw_params	= si476x_codec_hw_params,
	.set_fmt	= si476x_codec_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver si476x_dai = अणु
	.name		= "si476x-codec",
	.capture	= अणु
		.stream_name	= "Capture",
		.channels_min	= 2,
		.channels_max	= 2,

		.rates = SNDRV_PCM_RATE_32000 |
		SNDRV_PCM_RATE_44100 |
		SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S8 |
		SNDRV_PCM_FMTBIT_S16_LE |
		SNDRV_PCM_FMTBIT_S20_3LE |
		SNDRV_PCM_FMTBIT_S24_LE
	पूर्ण,
	.ops		= &si476x_dai_ops,
पूर्ण;

अटल पूर्णांक si476x_probe(काष्ठा snd_soc_component *component)
अणु
	snd_soc_component_init_regmap(component,
				dev_get_regmap(component->dev->parent, शून्य));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_si476x = अणु
	.probe			= si476x_probe,
	.dapm_widमाला_लो		= si476x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(si476x_dapm_widमाला_लो),
	.dapm_routes		= si476x_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(si476x_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक si476x_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
				      &soc_component_dev_si476x,
				      &si476x_dai, 1);
पूर्ण

MODULE_ALIAS("platform:si476x-codec");

अटल काष्ठा platक्रमm_driver si476x_platक्रमm_driver = अणु
	.driver		= अणु
		.name	= "si476x-codec",
	पूर्ण,
	.probe		= si476x_platक्रमm_probe,
पूर्ण;
module_platक्रमm_driver(si476x_platक्रमm_driver);

MODULE_AUTHOR("Andrey Smirnov <andrew.smirnov@gmail.com>");
MODULE_DESCRIPTION("ASoC Si4761/64 codec driver");
MODULE_LICENSE("GPL");
