<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ALSA SoC CQ0093 Voice Codec Driver क्रम DaVinci platक्रमms
 *
 * Copyright (C) 2010 Texas Instruments, Inc
 *
 * Author: Miguel Aguilar <miguel.aguilar@ridgerun.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/mfd/davinci_voicecodec.h>
#समावेश <linux/spi/spi.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>

अटल स्थिर काष्ठा snd_kcontrol_new cq93vc_snd_controls[] = अणु
	SOC_SINGLE("PGA Capture Volume", DAVINCI_VC_REG05, 0, 0x03, 0),
	SOC_SINGLE("Mono DAC Playback Volume", DAVINCI_VC_REG09, 0, 0x3f, 0),
पूर्ण;

अटल पूर्णांक cq93vc_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 reg;

	अगर (mute)
		reg = DAVINCI_VC_REG09_MUTE;
	अन्यथा
		reg = 0;

	snd_soc_component_update_bits(component, DAVINCI_VC_REG09, DAVINCI_VC_REG09_MUTE,
			    reg);

	वापस 0;
पूर्ण

अटल पूर्णांक cq93vc_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	चयन (freq) अणु
	हाल 22579200:
	हाल 27000000:
	हाल 33868800:
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cq93vc_set_bias_level(काष्ठा snd_soc_component *component,
				क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		snd_soc_component_ग_लिखो(component, DAVINCI_VC_REG12,
			     DAVINCI_VC_REG12_POWER_ALL_ON);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		snd_soc_component_ग_लिखो(component, DAVINCI_VC_REG12,
			     DAVINCI_VC_REG12_POWER_ALL_OFF);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* क्रमce all घातer off */
		snd_soc_component_ग_लिखो(component, DAVINCI_VC_REG12,
			     DAVINCI_VC_REG12_POWER_ALL_OFF);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा CQ93VC_RATES	(SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000)
#घोषणा CQ93VC_FORMATS	(SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops cq93vc_dai_ops = अणु
	.mute_stream	= cq93vc_mute,
	.set_sysclk	= cq93vc_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cq93vc_dai = अणु
	.name = "cq93vc-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = CQ93VC_RATES,
		.क्रमmats = CQ93VC_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = CQ93VC_RATES,
		.क्रमmats = CQ93VC_FORMATS,पूर्ण,
	.ops = &cq93vc_dai_ops,
पूर्ण;

अटल पूर्णांक cq93vc_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा davinci_vc *davinci_vc = component->dev->platक्रमm_data;

	snd_soc_component_init_regmap(component, davinci_vc->regmap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_cq93vc = अणु
	.set_bias_level		= cq93vc_set_bias_level,
	.probe			= cq93vc_probe,
	.controls		= cq93vc_snd_controls,
	.num_controls		= ARRAY_SIZE(cq93vc_snd_controls),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक cq93vc_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_cq93vc, &cq93vc_dai, 1);
पूर्ण

अटल पूर्णांक cq93vc_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cq93vc_codec_driver = अणु
	.driver = अणु
			.name = "cq93vc-codec",
	पूर्ण,

	.probe = cq93vc_platक्रमm_probe,
	.हटाओ = cq93vc_platक्रमm_हटाओ,
पूर्ण;

module_platक्रमm_driver(cq93vc_codec_driver);

MODULE_DESCRIPTION("Texas Instruments DaVinci ASoC CQ0093 Voice Codec Driver");
MODULE_AUTHOR("Miguel Aguilar");
MODULE_LICENSE("GPL");
