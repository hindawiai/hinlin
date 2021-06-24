<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PCM1681 ASoC codec driver
 *
 * Copyright (c) StreamUnlimited GmbH 2013
 *	Marek Belisko <marek.belisko@streamunlimited.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#घोषणा PCM1681_PCM_FORMATS (SNDRV_PCM_FMTBIT_S16_LE  |		\
			     SNDRV_PCM_FMTBIT_S24_LE)

#घोषणा PCM1681_PCM_RATES   (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 | \
			     SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100  | \
			     SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200  | \
			     SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_192000)

#घोषणा PCM1681_SOFT_MUTE_ALL		0xff
#घोषणा PCM1681_DEEMPH_RATE_MASK	0x18
#घोषणा PCM1681_DEEMPH_MASK		0x01

#घोषणा PCM1681_ATT_CONTROL(X)	(X <= 6 ? X : X + 9) /* Attenuation level */
#घोषणा PCM1681_SOFT_MUTE	0x07	/* Soft mute control रेजिस्टर */
#घोषणा PCM1681_DAC_CONTROL	0x08	/* DAC operation control */
#घोषणा PCM1681_FMT_CONTROL	0x09	/* Audio पूर्णांकerface data क्रमmat */
#घोषणा PCM1681_DEEMPH_CONTROL	0x0a	/* De-emphasis control */
#घोषणा PCM1681_ZERO_DETECT_STATUS	0x0e	/* Zero detect status reg */

अटल स्थिर काष्ठा reg_शेष pcm1681_reg_शेषs[] = अणु
	अणु 0x01,	0xff पूर्ण,
	अणु 0x02,	0xff पूर्ण,
	अणु 0x03,	0xff पूर्ण,
	अणु 0x04,	0xff पूर्ण,
	अणु 0x05,	0xff पूर्ण,
	अणु 0x06,	0xff पूर्ण,
	अणु 0x07,	0x00 पूर्ण,
	अणु 0x08,	0x00 पूर्ण,
	अणु 0x09,	0x06 पूर्ण,
	अणु 0x0A,	0x00 पूर्ण,
	अणु 0x0B,	0xff पूर्ण,
	अणु 0x0C,	0x0f पूर्ण,
	अणु 0x0D,	0x00 पूर्ण,
	अणु 0x10,	0xff पूर्ण,
	अणु 0x11,	0xff पूर्ण,
	अणु 0x12,	0x00 पूर्ण,
	अणु 0x13,	0x00 पूर्ण,
पूर्ण;

अटल bool pcm1681_accessible_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस !((reg == 0x00) || (reg == 0x0f));
पूर्ण

अटल bool pcm1681_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस pcm1681_accessible_reg(dev, reg) &&
		(reg != PCM1681_ZERO_DETECT_STATUS);
पूर्ण

काष्ठा pcm1681_निजी अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक क्रमmat;
	/* Current deemphasis status */
	अचिन्हित पूर्णांक deemph;
	/* Current rate क्रम deemphasis control */
	अचिन्हित पूर्णांक rate;
पूर्ण;

अटल स्थिर पूर्णांक pcm1681_deemph[] = अणु 44100, 48000, 32000 पूर्ण;

अटल पूर्णांक pcm1681_set_deemph(काष्ठा snd_soc_component *component)
अणु
	काष्ठा pcm1681_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक i, val = -1, enable = 0;

	अगर (priv->deemph) अणु
		क्रम (i = 0; i < ARRAY_SIZE(pcm1681_deemph); i++) अणु
			अगर (pcm1681_deemph[i] == priv->rate) अणु
				val = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (val != -1) अणु
		regmap_update_bits(priv->regmap, PCM1681_DEEMPH_CONTROL,
				   PCM1681_DEEMPH_RATE_MASK, val << 3);
		enable = 1;
	पूर्ण अन्यथा अणु
		enable = 0;
	पूर्ण

	/* enable/disable deemphasis functionality */
	वापस regmap_update_bits(priv->regmap, PCM1681_DEEMPH_CONTROL,
					PCM1681_DEEMPH_MASK, enable);
पूर्ण

अटल पूर्णांक pcm1681_get_deemph(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा pcm1681_निजी *priv = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = priv->deemph;

	वापस 0;
पूर्ण

अटल पूर्णांक pcm1681_put_deemph(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा pcm1681_निजी *priv = snd_soc_component_get_drvdata(component);

	priv->deemph = ucontrol->value.पूर्णांकeger.value[0];

	वापस pcm1681_set_deemph(component);
पूर्ण

अटल पूर्णांक pcm1681_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			      अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा pcm1681_निजी *priv = snd_soc_component_get_drvdata(component);

	/* The PCM1681 can only be slave to all घड़ीs */
	अगर ((क्रमmat & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS) अणु
		dev_err(component->dev, "Invalid clocking mode\n");
		वापस -EINVAL;
	पूर्ण

	priv->क्रमmat = क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक pcm1681_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm1681_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक val;

	अगर (mute)
		val = PCM1681_SOFT_MUTE_ALL;
	अन्यथा
		val = 0;

	वापस regmap_ग_लिखो(priv->regmap, PCM1681_SOFT_MUTE, val);
पूर्ण

अटल पूर्णांक pcm1681_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm1681_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक val = 0, ret;

	priv->rate = params_rate(params);

	चयन (priv->क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_RIGHT_J:
		चयन (params_width(params)) अणु
		हाल 24:
			val = 0;
			अवरोध;
		हाल 16:
			val = 3;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		val = 0x04;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		val = 0x05;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI format\n");
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(priv->regmap, PCM1681_FMT_CONTROL, 0x0f, val);
	अगर (ret < 0)
		वापस ret;

	वापस pcm1681_set_deemph(component);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops pcm1681_dai_ops = अणु
	.set_fmt	= pcm1681_set_dai_fmt,
	.hw_params	= pcm1681_hw_params,
	.mute_stream	= pcm1681_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget pcm1681_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_OUTPUT("VOUT1"),
SND_SOC_DAPM_OUTPUT("VOUT2"),
SND_SOC_DAPM_OUTPUT("VOUT3"),
SND_SOC_DAPM_OUTPUT("VOUT4"),
SND_SOC_DAPM_OUTPUT("VOUT5"),
SND_SOC_DAPM_OUTPUT("VOUT6"),
SND_SOC_DAPM_OUTPUT("VOUT7"),
SND_SOC_DAPM_OUTPUT("VOUT8"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route pcm1681_dapm_routes[] = अणु
	अणु "VOUT1", शून्य, "Playback" पूर्ण,
	अणु "VOUT2", शून्य, "Playback" पूर्ण,
	अणु "VOUT3", शून्य, "Playback" पूर्ण,
	अणु "VOUT4", शून्य, "Playback" पूर्ण,
	अणु "VOUT5", शून्य, "Playback" पूर्ण,
	अणु "VOUT6", शून्य, "Playback" पूर्ण,
	अणु "VOUT7", शून्य, "Playback" पूर्ण,
	अणु "VOUT8", शून्य, "Playback" पूर्ण,
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(pcm1681_dac_tlv, -6350, 50, 1);

अटल स्थिर काष्ठा snd_kcontrol_new pcm1681_controls[] = अणु
	SOC_DOUBLE_R_TLV("Channel 1/2 Playback Volume",
			PCM1681_ATT_CONTROL(1), PCM1681_ATT_CONTROL(2), 0,
			0x7f, 0, pcm1681_dac_tlv),
	SOC_DOUBLE_R_TLV("Channel 3/4 Playback Volume",
			PCM1681_ATT_CONTROL(3), PCM1681_ATT_CONTROL(4), 0,
			0x7f, 0, pcm1681_dac_tlv),
	SOC_DOUBLE_R_TLV("Channel 5/6 Playback Volume",
			PCM1681_ATT_CONTROL(5), PCM1681_ATT_CONTROL(6), 0,
			0x7f, 0, pcm1681_dac_tlv),
	SOC_DOUBLE_R_TLV("Channel 7/8 Playback Volume",
			PCM1681_ATT_CONTROL(7), PCM1681_ATT_CONTROL(8), 0,
			0x7f, 0, pcm1681_dac_tlv),
	SOC_SINGLE_BOOL_EXT("De-emphasis Switch", 0,
			    pcm1681_get_deemph, pcm1681_put_deemph),
पूर्ण;

अटल काष्ठा snd_soc_dai_driver pcm1681_dai = अणु
	.name = "pcm1681-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 8,
		.rates = PCM1681_PCM_RATES,
		.क्रमmats = PCM1681_PCM_FORMATS,
	पूर्ण,
	.ops = &pcm1681_dai_ops,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pcm1681_dt_ids[] = अणु
	अणु .compatible = "ti,pcm1681", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcm1681_dt_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा regmap_config pcm1681_regmap = अणु
	.reg_bits		= 8,
	.val_bits		= 8,
	.max_रेजिस्टर		= 0x13,
	.reg_शेषs		= pcm1681_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(pcm1681_reg_शेषs),
	.ग_लिखोable_reg		= pcm1681_ग_लिखोable_reg,
	.पढ़ोable_reg		= pcm1681_accessible_reg,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_pcm1681 = अणु
	.controls		= pcm1681_controls,
	.num_controls		= ARRAY_SIZE(pcm1681_controls),
	.dapm_widमाला_लो		= pcm1681_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(pcm1681_dapm_widमाला_लो),
	.dapm_routes		= pcm1681_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(pcm1681_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id pcm1681_i2c_id[] = अणु
	अणु"pcm1681", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcm1681_i2c_id);

अटल पूर्णांक pcm1681_i2c_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा pcm1681_निजी *priv;

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regmap = devm_regmap_init_i2c(client, &pcm1681_regmap);
	अगर (IS_ERR(priv->regmap)) अणु
		ret = PTR_ERR(priv->regmap);
		dev_err(&client->dev, "Failed to create regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(client, priv);

	वापस devm_snd_soc_रेजिस्टर_component(&client->dev,
		&soc_component_dev_pcm1681,
		&pcm1681_dai, 1);
पूर्ण

अटल काष्ठा i2c_driver pcm1681_i2c_driver = अणु
	.driver = अणु
		.name	= "pcm1681",
		.of_match_table = of_match_ptr(pcm1681_dt_ids),
	पूर्ण,
	.id_table	= pcm1681_i2c_id,
	.probe		= pcm1681_i2c_probe,
पूर्ण;

module_i2c_driver(pcm1681_i2c_driver);

MODULE_DESCRIPTION("Texas Instruments PCM1681 ALSA SoC Codec Driver");
MODULE_AUTHOR("Marek Belisko <marek.belisko@streamunlimited.com>");
MODULE_LICENSE("GPL");
