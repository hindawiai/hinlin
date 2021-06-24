<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PCM179X ASoC codec driver
 *
 * Copyright (c) Amarula Solutions B.V. 2013
 *
 *     Michael Trimarchi <michael@amarulasolutions.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <linux/of.h>

#समावेश "pcm179x.h"

#घोषणा PCM179X_DAC_VOL_LEFT	0x10
#घोषणा PCM179X_DAC_VOL_RIGHT	0x11
#घोषणा PCM179X_FMT_CONTROL	0x12
#घोषणा PCM179X_MODE_CONTROL	0x13
#घोषणा PCM179X_SOFT_MUTE	PCM179X_FMT_CONTROL

#घोषणा PCM179X_FMT_MASK	0x70
#घोषणा PCM179X_FMT_SHIFT	4
#घोषणा PCM179X_MUTE_MASK	0x01
#घोषणा PCM179X_MUTE_SHIFT	0
#घोषणा PCM179X_ATLD_ENABLE	(1 << 7)

अटल स्थिर काष्ठा reg_शेष pcm179x_reg_शेषs[] = अणु
	अणु 0x10, 0xff पूर्ण,
	अणु 0x11, 0xff पूर्ण,
	अणु 0x12, 0x50 पूर्ण,
	अणु 0x13, 0x00 पूर्ण,
	अणु 0x14, 0x00 पूर्ण,
	अणु 0x15, 0x01 पूर्ण,
	अणु 0x16, 0x00 पूर्ण,
	अणु 0x17, 0x00 पूर्ण,
पूर्ण;

अटल bool pcm179x_accessible_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg >= 0x10 && reg <= 0x17;
पूर्ण

अटल bool pcm179x_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	bool accessible;

	accessible = pcm179x_accessible_reg(dev, reg);

	वापस accessible && reg != 0x16 && reg != 0x17;
पूर्ण

काष्ठा pcm179x_निजी अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक क्रमmat;
	अचिन्हित पूर्णांक rate;
पूर्ण;

अटल पूर्णांक pcm179x_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
                             अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा pcm179x_निजी *priv = snd_soc_component_get_drvdata(component);

	priv->क्रमmat = क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक pcm179x_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm179x_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = regmap_update_bits(priv->regmap, PCM179X_SOFT_MUTE,
				 PCM179X_MUTE_MASK, !!mute);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक pcm179x_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm179x_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक val = 0, ret;

	priv->rate = params_rate(params);

	चयन (priv->क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_RIGHT_J:
		चयन (params_width(params)) अणु
		हाल 24:
		हाल 32:
			val = 2;
			अवरोध;
		हाल 16:
			val = 0;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		चयन (params_width(params)) अणु
		हाल 24:
		हाल 32:
			val = 5;
			अवरोध;
		हाल 16:
			val = 4;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI format\n");
		वापस -EINVAL;
	पूर्ण

	val = val << PCM179X_FMT_SHIFT | PCM179X_ATLD_ENABLE;

	ret = regmap_update_bits(priv->regmap, PCM179X_FMT_CONTROL,
				 PCM179X_FMT_MASK | PCM179X_ATLD_ENABLE, val);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops pcm179x_dai_ops = अणु
	.set_fmt	= pcm179x_set_dai_fmt,
	.hw_params	= pcm179x_hw_params,
	.mute_stream	= pcm179x_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(pcm179x_dac_tlv, -12000, 50, 1);

अटल स्थिर काष्ठा snd_kcontrol_new pcm179x_controls[] = अणु
	SOC_DOUBLE_R_RANGE_TLV("DAC Playback Volume", PCM179X_DAC_VOL_LEFT,
			 PCM179X_DAC_VOL_RIGHT, 0, 0xf, 0xff, 0,
			 pcm179x_dac_tlv),
	SOC_SINGLE("DAC Invert Output Switch", PCM179X_MODE_CONTROL, 7, 1, 0),
	SOC_SINGLE("DAC Rolloff Filter Switch", PCM179X_MODE_CONTROL, 1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget pcm179x_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_OUTPUT("IOUTL+"),
SND_SOC_DAPM_OUTPUT("IOUTL-"),
SND_SOC_DAPM_OUTPUT("IOUTR+"),
SND_SOC_DAPM_OUTPUT("IOUTR-"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route pcm179x_dapm_routes[] = अणु
	अणु "IOUTL+", शून्य, "Playback" पूर्ण,
	अणु "IOUTL-", शून्य, "Playback" पूर्ण,
	अणु "IOUTR+", शून्य, "Playback" पूर्ण,
	अणु "IOUTR-", शून्य, "Playback" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver pcm179x_dai = अणु
	.name = "pcm179x-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min = 10000,
		.rate_max = 200000,
		.क्रमmats = PCM1792A_FORMATS, पूर्ण,
	.ops = &pcm179x_dai_ops,
पूर्ण;

स्थिर काष्ठा regmap_config pcm179x_regmap_config = अणु
	.reg_bits		= 8,
	.val_bits		= 8,
	.max_रेजिस्टर		= 23,
	.reg_शेषs		= pcm179x_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(pcm179x_reg_शेषs),
	.ग_लिखोable_reg		= pcm179x_ग_लिखोable_reg,
	.पढ़ोable_reg		= pcm179x_accessible_reg,
पूर्ण;
EXPORT_SYMBOL_GPL(pcm179x_regmap_config);

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_pcm179x = अणु
	.controls		= pcm179x_controls,
	.num_controls		= ARRAY_SIZE(pcm179x_controls),
	.dapm_widमाला_लो		= pcm179x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(pcm179x_dapm_widमाला_लो),
	.dapm_routes		= pcm179x_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(pcm179x_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

पूर्णांक pcm179x_common_init(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	काष्ठा pcm179x_निजी *pcm179x;

	pcm179x = devm_kzalloc(dev, माप(काष्ठा pcm179x_निजी),
				GFP_KERNEL);
	अगर (!pcm179x)
		वापस -ENOMEM;

	pcm179x->regmap = regmap;
	dev_set_drvdata(dev, pcm179x);

	वापस devm_snd_soc_रेजिस्टर_component(dev,
			&soc_component_dev_pcm179x, &pcm179x_dai, 1);
पूर्ण
EXPORT_SYMBOL_GPL(pcm179x_common_init);

MODULE_DESCRIPTION("ASoC PCM179X driver");
MODULE_AUTHOR("Michael Trimarchi <michael@amarulasolutions.com>");
MODULE_LICENSE("GPL");
