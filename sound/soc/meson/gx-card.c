<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
//
// Copyright (c) 2020 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "meson-card.h"

काष्ठा gx_dai_link_i2s_data अणु
	अचिन्हित पूर्णांक mclk_fs;
पूर्ण;

/*
 * Base params क्रम the codec to codec links
 * Those will be over-written by the CPU side of the link
 */
अटल स्थिर काष्ठा snd_soc_pcm_stream codec_params = अणु
	.क्रमmats = SNDRV_PCM_FMTBIT_S24_LE,
	.rate_min = 5525,
	.rate_max = 192000,
	.channels_min = 1,
	.channels_max = 8,
पूर्ण;

अटल पूर्णांक gx_card_i2s_be_hw_params(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा meson_card *priv = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा gx_dai_link_i2s_data *be =
		(काष्ठा gx_dai_link_i2s_data *)priv->link_data[rtd->num];

	वापस meson_card_i2s_set_sysclk(substream, params, be->mclk_fs);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops gx_card_i2s_be_ops = अणु
	.hw_params = gx_card_i2s_be_hw_params,
पूर्ण;

अटल पूर्णांक gx_card_parse_i2s(काष्ठा snd_soc_card *card,
			     काष्ठा device_node *node,
			     पूर्णांक *index)
अणु
	काष्ठा meson_card *priv = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai_link *link = &card->dai_link[*index];
	काष्ठा gx_dai_link_i2s_data *be;

	/* Allocate i2s link parameters */
	be = devm_kzalloc(card->dev, माप(*be), GFP_KERNEL);
	अगर (!be)
		वापस -ENOMEM;
	priv->link_data[*index] = be;

	/* Setup i2s link */
	link->ops = &gx_card_i2s_be_ops;
	link->dai_fmt = meson_card_parse_daअगरmt(node, link->cpus->of_node);

	of_property_पढ़ो_u32(node, "mclk-fs", &be->mclk_fs);

	वापस 0;
पूर्ण

अटल पूर्णांक gx_card_cpu_identअगरy(काष्ठा snd_soc_dai_link_component *c,
				अक्षर *match)
अणु
	अगर (of_device_is_compatible(c->of_node, DT_PREFIX "aiu")) अणु
		अगर (म_माला(c->dai_name, match))
			वापस 1;
	पूर्ण

	/* dai not matched */
	वापस 0;
पूर्ण

अटल पूर्णांक gx_card_add_link(काष्ठा snd_soc_card *card, काष्ठा device_node *np,
			    पूर्णांक *index)
अणु
	काष्ठा snd_soc_dai_link *dai_link = &card->dai_link[*index];
	काष्ठा snd_soc_dai_link_component *cpu;
	पूर्णांक ret;

	cpu = devm_kzalloc(card->dev, माप(*cpu), GFP_KERNEL);
	अगर (!cpu)
		वापस -ENOMEM;

	dai_link->cpus = cpu;
	dai_link->num_cpus = 1;

	ret = meson_card_parse_dai(card, np, &dai_link->cpus->of_node,
				   &dai_link->cpus->dai_name);
	अगर (ret)
		वापस ret;

	अगर (gx_card_cpu_identअगरy(dai_link->cpus, "FIFO"))
		वापस  meson_card_set_fe_link(card, dai_link, np, true);

	ret = meson_card_set_be_link(card, dai_link, np);
	अगर (ret)
		वापस ret;

	/* Or apply codec to codec params अगर necessary */
	अगर (gx_card_cpu_identअगरy(dai_link->cpus, "CODEC CTRL")) अणु
		dai_link->params = &codec_params;
	पूर्ण अन्यथा अणु
		dai_link->no_pcm = 1;
		snd_soc_dai_link_set_capabilities(dai_link);
		/* Check अगर the cpu is the i2s encoder and parse i2s data */
		अगर (gx_card_cpu_identअगरy(dai_link->cpus, "I2S Encoder"))
			ret = gx_card_parse_i2s(card, np, index);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा meson_card_match_data gx_card_match_data = अणु
	.add_link = gx_card_add_link,
पूर्ण;

अटल स्थिर काष्ठा of_device_id gx_card_of_match[] = अणु
	अणु
		.compatible = "amlogic,gx-sound-card",
		.data = &gx_card_match_data,
	पूर्ण, अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gx_card_of_match);

अटल काष्ठा platक्रमm_driver gx_card_pdrv = अणु
	.probe = meson_card_probe,
	.हटाओ = meson_card_हटाओ,
	.driver = अणु
		.name = "gx-sound-card",
		.of_match_table = gx_card_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(gx_card_pdrv);

MODULE_DESCRIPTION("Amlogic GX ALSA machine driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
