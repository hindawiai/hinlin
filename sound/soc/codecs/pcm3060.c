<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// PCM3060 codec driver
//
// Copyright (C) 2018 Kirill Marinushkin <kmarinushkin@birdec.com>

#समावेश <linux/module.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "pcm3060.h"

/* dai */

अटल पूर्णांक pcm3060_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
			      अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *comp = dai->component;
	काष्ठा pcm3060_priv *priv = snd_soc_component_get_drvdata(comp);
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक val;

	अगर (dir != SND_SOC_CLOCK_IN) अणु
		dev_err(comp->dev, "unsupported sysclock dir: %d\n", dir);
		वापस -EINVAL;
	पूर्ण

	चयन (clk_id) अणु
	हाल PCM3060_CLK_DEF:
		val = 0;
		अवरोध;

	हाल PCM3060_CLK1:
		val = (dai->id == PCM3060_DAI_ID_DAC ? PCM3060_REG_CSEL : 0);
		अवरोध;

	हाल PCM3060_CLK2:
		val = (dai->id == PCM3060_DAI_ID_DAC ? 0 : PCM3060_REG_CSEL);
		अवरोध;

	शेष:
		dev_err(comp->dev, "unsupported sysclock id: %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	अगर (dai->id == PCM3060_DAI_ID_DAC)
		reg = PCM3060_REG67;
	अन्यथा
		reg = PCM3060_REG72;

	regmap_update_bits(priv->regmap, reg, PCM3060_REG_CSEL, val);

	priv->dai[dai->id].sclk_freq = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक pcm3060_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *comp = dai->component;
	काष्ठा pcm3060_priv *priv = snd_soc_component_get_drvdata(comp);
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक val;

	अगर ((fmt & SND_SOC_DAIFMT_INV_MASK) != SND_SOC_DAIFMT_NB_NF) अणु
		dev_err(comp->dev, "unsupported DAI polarity: 0x%x\n", fmt);
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		priv->dai[dai->id].is_master = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		priv->dai[dai->id].is_master = false;
		अवरोध;
	शेष:
		dev_err(comp->dev, "unsupported DAI master mode: 0x%x\n", fmt);
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		val = PCM3060_REG_FMT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		val = PCM3060_REG_FMT_RJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		val = PCM3060_REG_FMT_LJ;
		अवरोध;
	शेष:
		dev_err(comp->dev, "unsupported DAI format: 0x%x\n", fmt);
		वापस -EINVAL;
	पूर्ण

	अगर (dai->id == PCM3060_DAI_ID_DAC)
		reg = PCM3060_REG67;
	अन्यथा
		reg = PCM3060_REG72;

	regmap_update_bits(priv->regmap, reg, PCM3060_REG_MASK_FMT, val);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm3060_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *comp = dai->component;
	काष्ठा pcm3060_priv *priv = snd_soc_component_get_drvdata(comp);
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक ratio;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक val;

	अगर (!priv->dai[dai->id].is_master) अणु
		val = PCM3060_REG_MS_S;
		जाओ val_पढ़ोy;
	पूर्ण

	rate = params_rate(params);
	अगर (!rate) अणु
		dev_err(comp->dev, "rate is not configured\n");
		वापस -EINVAL;
	पूर्ण

	ratio = priv->dai[dai->id].sclk_freq / rate;

	चयन (ratio) अणु
	हाल 768:
		val = PCM3060_REG_MS_M768;
		अवरोध;
	हाल 512:
		val = PCM3060_REG_MS_M512;
		अवरोध;
	हाल 384:
		val = PCM3060_REG_MS_M384;
		अवरोध;
	हाल 256:
		val = PCM3060_REG_MS_M256;
		अवरोध;
	हाल 192:
		val = PCM3060_REG_MS_M192;
		अवरोध;
	हाल 128:
		val = PCM3060_REG_MS_M128;
		अवरोध;
	शेष:
		dev_err(comp->dev, "unsupported ratio: %d\n", ratio);
		वापस -EINVAL;
	पूर्ण

val_पढ़ोy:
	अगर (dai->id == PCM3060_DAI_ID_DAC)
		reg = PCM3060_REG67;
	अन्यथा
		reg = PCM3060_REG72;

	regmap_update_bits(priv->regmap, reg, PCM3060_REG_MASK_MS, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops pcm3060_dai_ops = अणु
	.set_sysclk = pcm3060_set_sysclk,
	.set_fmt = pcm3060_set_fmt,
	.hw_params = pcm3060_hw_params,
पूर्ण;

#घोषणा PCM3060_DAI_RATES_ADC	(SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_32000 | \
				 SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 | \
				 SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000)

#घोषणा PCM3060_DAI_RATES_DAC	(PCM3060_DAI_RATES_ADC | \
				 SNDRV_PCM_RATE_176400 | SNDRV_PCM_RATE_192000)

अटल काष्ठा snd_soc_dai_driver pcm3060_dai[] = अणु
	अणु
		.name = "pcm3060-dac",
		.id = PCM3060_DAI_ID_DAC,
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = PCM3060_DAI_RATES_DAC,
			.क्रमmats = SNDRV_PCM_FMTBIT_S24_LE,
		पूर्ण,
		.ops = &pcm3060_dai_ops,
	पूर्ण,
	अणु
		.name = "pcm3060-adc",
		.id = PCM3060_DAI_ID_ADC,
		.capture = अणु
			.stream_name = "Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = PCM3060_DAI_RATES_ADC,
			.क्रमmats = SNDRV_PCM_FMTBIT_S24_LE,
		पूर्ण,
		.ops = &pcm3060_dai_ops,
	पूर्ण,
पूर्ण;

/* dapm */

अटल DECLARE_TLV_DB_SCALE(pcm3060_dapm_tlv, -10050, 50, 1);

अटल स्थिर काष्ठा snd_kcontrol_new pcm3060_dapm_controls[] = अणु
	SOC_DOUBLE_R_RANGE_TLV("Master Playback Volume",
			       PCM3060_REG65, PCM3060_REG66, 0,
			       PCM3060_REG_AT2_MIN, PCM3060_REG_AT2_MAX,
			       0, pcm3060_dapm_tlv),
	SOC_DOUBLE("Master Playback Switch", PCM3060_REG68,
		   PCM3060_REG_SHIFT_MUT21, PCM3060_REG_SHIFT_MUT22, 1, 1),

	SOC_DOUBLE_R_RANGE_TLV("Master Capture Volume",
			       PCM3060_REG70, PCM3060_REG71, 0,
			       PCM3060_REG_AT1_MIN, PCM3060_REG_AT1_MAX,
			       0, pcm3060_dapm_tlv),
	SOC_DOUBLE("Master Capture Switch", PCM3060_REG73,
		   PCM3060_REG_SHIFT_MUT11, PCM3060_REG_SHIFT_MUT12, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget pcm3060_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DAC", "Playback", PCM3060_REG64,
			 PCM3060_REG_SHIFT_DAPSV, 1),

	SND_SOC_DAPM_OUTPUT("OUTL"),
	SND_SOC_DAPM_OUTPUT("OUTR"),

	SND_SOC_DAPM_INPUT("INL"),
	SND_SOC_DAPM_INPUT("INR"),

	SND_SOC_DAPM_ADC("ADC", "Capture", PCM3060_REG64,
			 PCM3060_REG_SHIFT_ADPSV, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route pcm3060_dapm_map[] = अणु
	अणु "OUTL", शून्य, "DAC" पूर्ण,
	अणु "OUTR", शून्य, "DAC" पूर्ण,

	अणु "ADC", शून्य, "INL" पूर्ण,
	अणु "ADC", शून्य, "INR" पूर्ण,
पूर्ण;

/* soc component */

अटल स्थिर काष्ठा snd_soc_component_driver pcm3060_soc_comp_driver = अणु
	.controls = pcm3060_dapm_controls,
	.num_controls = ARRAY_SIZE(pcm3060_dapm_controls),
	.dapm_widमाला_लो = pcm3060_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(pcm3060_dapm_widमाला_लो),
	.dapm_routes = pcm3060_dapm_map,
	.num_dapm_routes = ARRAY_SIZE(pcm3060_dapm_map),
पूर्ण;

/* regmap */

अटल bool pcm3060_reg_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg >= PCM3060_REG64);
पूर्ण

अटल bool pcm3060_reg_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg >= PCM3060_REG64);
पूर्ण

अटल bool pcm3060_reg_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* PCM3060_REG64 is अस्थिर */
	वापस (reg == PCM3060_REG64);
पूर्ण

अटल स्थिर काष्ठा reg_शेष pcm3060_reg_शेषs[] = अणु
	अणु PCM3060_REG64,  0xF0 पूर्ण,
	अणु PCM3060_REG65,  0xFF पूर्ण,
	अणु PCM3060_REG66,  0xFF पूर्ण,
	अणु PCM3060_REG67,  0x00 पूर्ण,
	अणु PCM3060_REG68,  0x00 पूर्ण,
	अणु PCM3060_REG69,  0x00 पूर्ण,
	अणु PCM3060_REG70,  0xD7 पूर्ण,
	अणु PCM3060_REG71,  0xD7 पूर्ण,
	अणु PCM3060_REG72,  0x00 पूर्ण,
	अणु PCM3060_REG73,  0x00 पूर्ण,
पूर्ण;

स्थिर काष्ठा regmap_config pcm3060_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ग_लिखोable_reg = pcm3060_reg_ग_लिखोable,
	.पढ़ोable_reg = pcm3060_reg_पढ़ोable,
	.अस्थिर_reg = pcm3060_reg_अस्थिर,
	.max_रेजिस्टर = PCM3060_REG73,
	.reg_शेषs = pcm3060_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(pcm3060_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;
EXPORT_SYMBOL(pcm3060_regmap);

/* device */

अटल व्योम pcm3060_parse_dt(स्थिर काष्ठा device_node *np,
			     काष्ठा pcm3060_priv *priv)
अणु
	priv->out_se = of_property_पढ़ो_bool(np, "ti,out-single-ended");
पूर्ण

पूर्णांक pcm3060_probe(काष्ठा device *dev)
अणु
	पूर्णांक rc;
	काष्ठा pcm3060_priv *priv = dev_get_drvdata(dev);

	/* soft reset */
	rc = regmap_update_bits(priv->regmap, PCM3060_REG64,
				PCM3060_REG_MRST, 0);
	अगर (rc) अणु
		dev_err(dev, "failed to reset component, rc=%d\n", rc);
		वापस rc;
	पूर्ण

	अगर (dev->of_node)
		pcm3060_parse_dt(dev->of_node, priv);

	अगर (priv->out_se)
		regmap_update_bits(priv->regmap, PCM3060_REG64,
				   PCM3060_REG_SE, PCM3060_REG_SE);

	rc = devm_snd_soc_रेजिस्टर_component(dev, &pcm3060_soc_comp_driver,
					     pcm3060_dai,
					     ARRAY_SIZE(pcm3060_dai));
	अगर (rc) अणु
		dev_err(dev, "failed to register component, rc=%d\n", rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pcm3060_probe);

MODULE_DESCRIPTION("PCM3060 codec driver");
MODULE_AUTHOR("Kirill Marinushkin <kmarinushkin@birdec.com>");
MODULE_LICENSE("GPL v2");
