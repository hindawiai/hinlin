<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Audio driver क्रम PCM1789
// Copyright (C) 2018 Bootlin
// Mylथउne Josseअक्रम <mylene.josseअक्रम@bootlin.com>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/workqueue.h>

#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "pcm1789.h"

#घोषणा PCM1789_MUTE_CONTROL	0x10
#घोषणा PCM1789_FMT_CONTROL	0x11
#घोषणा PCM1789_SOFT_MUTE	0x14
#घोषणा PCM1789_DAC_VOL_LEFT	0x18
#घोषणा PCM1789_DAC_VOL_RIGHT	0x19

#घोषणा PCM1789_FMT_MASK	0x07
#घोषणा PCM1789_MUTE_MASK	0x03
#घोषणा PCM1789_MUTE_SRET	0x06

काष्ठा pcm1789_निजी अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक क्रमmat;
	अचिन्हित पूर्णांक rate;
	काष्ठा gpio_desc *reset;
	काष्ठा work_काष्ठा work;
	काष्ठा device *dev;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष pcm1789_reg_शेषs[] = अणु
	अणु PCM1789_FMT_CONTROL, 0x00 पूर्ण,
	अणु PCM1789_SOFT_MUTE, 0x00 पूर्ण,
	अणु PCM1789_DAC_VOL_LEFT, 0xff पूर्ण,
	अणु PCM1789_DAC_VOL_RIGHT, 0xff पूर्ण,
पूर्ण;

अटल bool pcm1789_accessible_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg >= PCM1789_MUTE_CONTROL && reg <= PCM1789_DAC_VOL_RIGHT;
पूर्ण

अटल bool pcm1789_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस pcm1789_accessible_reg(dev, reg);
पूर्ण

अटल पूर्णांक pcm1789_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			       अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा pcm1789_निजी *priv = snd_soc_component_get_drvdata(component);

	priv->क्रमmat = क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक pcm1789_mute(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा pcm1789_निजी *priv = snd_soc_component_get_drvdata(component);

	वापस regmap_update_bits(priv->regmap, PCM1789_SOFT_MUTE,
				  PCM1789_MUTE_MASK,
				  mute ? 0 : PCM1789_MUTE_MASK);
पूर्ण

अटल पूर्णांक pcm1789_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *codec_dai)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा pcm1789_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक val = 0, ret;

	priv->rate = params_rate(params);

	चयन (priv->क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_RIGHT_J:
		चयन (params_width(params)) अणु
		हाल 24:
			val = 2;
			अवरोध;
		हाल 16:
			val = 3;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		चयन (params_width(params)) अणु
		हाल 16:
		हाल 24:
		हाल 32:
			val = 0;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		चयन (params_width(params)) अणु
		हाल 16:
		हाल 24:
		हाल 32:
			val = 1;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI format\n");
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(priv->regmap, PCM1789_FMT_CONTROL,
				 PCM1789_FMT_MASK, val);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम pcm1789_work_queue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pcm1789_निजी *priv = container_of(work,
						    काष्ठा pcm1789_निजी,
						    work);

	/* Perक्रमm a software reset to हटाओ codec from desynchronized state */
	अगर (regmap_update_bits(priv->regmap, PCM1789_MUTE_CONTROL,
			       0x3 << PCM1789_MUTE_SRET, 0) < 0)
		dev_err(priv->dev, "Error while setting SRET");
पूर्ण

अटल पूर्णांक pcm1789_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm1789_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		schedule_work(&priv->work);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops pcm1789_dai_ops = अणु
	.set_fmt	= pcm1789_set_dai_fmt,
	.hw_params	= pcm1789_hw_params,
	.mute_stream	= pcm1789_mute,
	.trigger	= pcm1789_trigger,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(pcm1789_dac_tlv, -12000, 50, 1);

अटल स्थिर काष्ठा snd_kcontrol_new pcm1789_controls[] = अणु
	SOC_DOUBLE_R_RANGE_TLV("DAC Playback Volume", PCM1789_DAC_VOL_LEFT,
			       PCM1789_DAC_VOL_RIGHT, 0, 0xf, 0xff, 0,
			       pcm1789_dac_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget pcm1789_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("IOUTL+"),
	SND_SOC_DAPM_OUTPUT("IOUTL-"),
	SND_SOC_DAPM_OUTPUT("IOUTR+"),
	SND_SOC_DAPM_OUTPUT("IOUTR-"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route pcm1789_dapm_routes[] = अणु
	अणु "IOUTL+", शून्य, "Playback" पूर्ण,
	अणु "IOUTL-", शून्य, "Playback" पूर्ण,
	अणु "IOUTR+", शून्य, "Playback" पूर्ण,
	अणु "IOUTR-", शून्य, "Playback" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver pcm1789_dai = अणु
	.name = "pcm1789-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min = 10000,
		.rate_max = 200000,
		.क्रमmats = PCM1789_FORMATS,
	पूर्ण,
	.ops = &pcm1789_dai_ops,
पूर्ण;

स्थिर काष्ठा regmap_config pcm1789_regmap_config = अणु
	.reg_bits		= 8,
	.val_bits		= 8,
	.max_रेजिस्टर		= PCM1789_DAC_VOL_RIGHT,
	.reg_शेषs		= pcm1789_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(pcm1789_reg_शेषs),
	.ग_लिखोable_reg		= pcm1789_ग_लिखोable_reg,
	.पढ़ोable_reg		= pcm1789_accessible_reg,
पूर्ण;
EXPORT_SYMBOL_GPL(pcm1789_regmap_config);

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_pcm1789 = अणु
	.controls		= pcm1789_controls,
	.num_controls		= ARRAY_SIZE(pcm1789_controls),
	.dapm_widमाला_लो		= pcm1789_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(pcm1789_dapm_widमाला_लो),
	.dapm_routes		= pcm1789_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(pcm1789_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

पूर्णांक pcm1789_common_init(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	काष्ठा pcm1789_निजी *pcm1789;

	pcm1789 = devm_kzalloc(dev, माप(काष्ठा pcm1789_निजी),
			       GFP_KERNEL);
	अगर (!pcm1789)
		वापस -ENOMEM;

	pcm1789->regmap = regmap;
	pcm1789->dev = dev;
	dev_set_drvdata(dev, pcm1789);

	pcm1789->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(pcm1789->reset))
		वापस PTR_ERR(pcm1789->reset);

	gpiod_set_value_cansleep(pcm1789->reset, 0);
	msleep(300);

	INIT_WORK(&pcm1789->work, pcm1789_work_queue);

	वापस devm_snd_soc_रेजिस्टर_component(dev, &soc_component_dev_pcm1789,
					       &pcm1789_dai, 1);
पूर्ण
EXPORT_SYMBOL_GPL(pcm1789_common_init);

पूर्णांक pcm1789_common_निकास(काष्ठा device *dev)
अणु
	काष्ठा pcm1789_निजी *priv = dev_get_drvdata(dev);

	flush_work(&priv->work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pcm1789_common_निकास);

MODULE_DESCRIPTION("ASoC PCM1789 driver");
MODULE_AUTHOR("Mylथउne Josserand <mylene.josserand@free-electrons.com>");
MODULE_LICENSE("GPL");
