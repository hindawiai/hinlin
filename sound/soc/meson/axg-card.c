<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
//
// Copyright (c) 2018 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "axg-tdm.h"
#समावेश "meson-card.h"

काष्ठा axg_dai_link_tdm_mask अणु
	u32 tx;
	u32 rx;
पूर्ण;

काष्ठा axg_dai_link_tdm_data अणु
	अचिन्हित पूर्णांक mclk_fs;
	अचिन्हित पूर्णांक slots;
	अचिन्हित पूर्णांक slot_width;
	u32 *tx_mask;
	u32 *rx_mask;
	काष्ठा axg_dai_link_tdm_mask *codec_masks;
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

अटल पूर्णांक axg_card_tdm_be_hw_params(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा meson_card *priv = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा axg_dai_link_tdm_data *be =
		(काष्ठा axg_dai_link_tdm_data *)priv->link_data[rtd->num];

	वापस meson_card_i2s_set_sysclk(substream, params, be->mclk_fs);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops axg_card_tdm_be_ops = अणु
	.hw_params = axg_card_tdm_be_hw_params,
पूर्ण;

अटल पूर्णांक axg_card_tdm_dai_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा meson_card *priv = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा axg_dai_link_tdm_data *be =
		(काष्ठा axg_dai_link_tdm_data *)priv->link_data[rtd->num];
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक ret, i;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		ret = snd_soc_dai_set_tdm_slot(codec_dai,
					       be->codec_masks[i].tx,
					       be->codec_masks[i].rx,
					       be->slots, be->slot_width);
		अगर (ret && ret != -ENOTSUPP) अणु
			dev_err(codec_dai->dev,
				"setting tdm link slots failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = axg_tdm_set_tdm_slots(asoc_rtd_to_cpu(rtd, 0), be->tx_mask, be->rx_mask,
				    be->slots, be->slot_width);
	अगर (ret) अणु
		dev_err(asoc_rtd_to_cpu(rtd, 0)->dev, "setting tdm link slots failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axg_card_tdm_dai_lb_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा meson_card *priv = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा axg_dai_link_tdm_data *be =
		(काष्ठा axg_dai_link_tdm_data *)priv->link_data[rtd->num];
	पूर्णांक ret;

	/* The loopback rx_mask is the pad tx_mask */
	ret = axg_tdm_set_tdm_slots(asoc_rtd_to_cpu(rtd, 0), शून्य, be->tx_mask,
				    be->slots, be->slot_width);
	अगर (ret) अणु
		dev_err(asoc_rtd_to_cpu(rtd, 0)->dev, "setting tdm link slots failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axg_card_add_tdm_loopback(काष्ठा snd_soc_card *card,
				     पूर्णांक *index)
अणु
	काष्ठा meson_card *priv = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai_link *pad = &card->dai_link[*index];
	काष्ठा snd_soc_dai_link *lb;
	काष्ठा snd_soc_dai_link_component *dlc;
	पूर्णांक ret;

	/* extend links */
	ret = meson_card_पुनः_स्मृतिate_links(card, card->num_links + 1);
	अगर (ret)
		वापस ret;

	lb = &card->dai_link[*index + 1];

	lb->name = devm_kaप्र_लिखो(card->dev, GFP_KERNEL, "%s-lb", pad->name);
	अगर (!lb->name)
		वापस -ENOMEM;

	dlc = devm_kzalloc(card->dev, 2 * माप(*dlc), GFP_KERNEL);
	अगर (!dlc)
		वापस -ENOMEM;

	lb->cpus = &dlc[0];
	lb->codecs = &dlc[1];
	lb->num_cpus = 1;
	lb->num_codecs = 1;

	lb->stream_name = lb->name;
	lb->cpus->of_node = pad->cpus->of_node;
	lb->cpus->dai_name = "TDM Loopback";
	lb->codecs->name = "snd-soc-dummy";
	lb->codecs->dai_name = "snd-soc-dummy-dai";
	lb->dpcm_capture = 1;
	lb->no_pcm = 1;
	lb->ops = &axg_card_tdm_be_ops;
	lb->init = axg_card_tdm_dai_lb_init;

	/* Provide the same link data to the loopback */
	priv->link_data[*index + 1] = priv->link_data[*index];

	/*
	 * axg_card_clean_references() will iterate over this link,
	 * make sure the node count is balanced
	 */
	of_node_get(lb->cpus->of_node);

	/* Let add_links जारी where it should */
	*index += 1;

	वापस 0;
पूर्ण

अटल पूर्णांक axg_card_parse_cpu_tdm_slots(काष्ठा snd_soc_card *card,
					काष्ठा snd_soc_dai_link *link,
					काष्ठा device_node *node,
					काष्ठा axg_dai_link_tdm_data *be)
अणु
	अक्षर propname[32];
	u32 tx, rx;
	पूर्णांक i;

	be->tx_mask = devm_kसुस्मृति(card->dev, AXG_TDM_NUM_LANES,
				   माप(*be->tx_mask), GFP_KERNEL);
	be->rx_mask = devm_kसुस्मृति(card->dev, AXG_TDM_NUM_LANES,
				   माप(*be->rx_mask), GFP_KERNEL);
	अगर (!be->tx_mask || !be->rx_mask)
		वापस -ENOMEM;

	क्रम (i = 0, tx = 0; i < AXG_TDM_NUM_LANES; i++) अणु
		snम_लिखो(propname, 32, "dai-tdm-slot-tx-mask-%d", i);
		snd_soc_of_get_slot_mask(node, propname, &be->tx_mask[i]);
		tx = max(tx, be->tx_mask[i]);
	पूर्ण

	/* Disable playback is the पूर्णांकerface has no tx slots */
	अगर (!tx)
		link->dpcm_playback = 0;

	क्रम (i = 0, rx = 0; i < AXG_TDM_NUM_LANES; i++) अणु
		snम_लिखो(propname, 32, "dai-tdm-slot-rx-mask-%d", i);
		snd_soc_of_get_slot_mask(node, propname, &be->rx_mask[i]);
		rx = max(rx, be->rx_mask[i]);
	पूर्ण

	/* Disable capture is the पूर्णांकerface has no rx slots */
	अगर (!rx)
		link->dpcm_capture = 0;

	/* ... but the पूर्णांकerface should at least have one of them */
	अगर (!tx && !rx) अणु
		dev_err(card->dev, "tdm link has no cpu slots\n");
		वापस -EINVAL;
	पूर्ण

	of_property_पढ़ो_u32(node, "dai-tdm-slot-num", &be->slots);
	अगर (!be->slots) अणु
		/*
		 * If the slot number is not provided, set it such as it
		 * accommodates the largest mask
		 */
		be->slots = fls(max(tx, rx));
	पूर्ण अन्यथा अगर (be->slots < fls(max(tx, rx)) || be->slots > 32) अणु
		/*
		 * Error अगर the slots can't accommodate the largest mask or
		 * अगर it is just too big
		 */
		dev_err(card->dev, "bad slot number\n");
		वापस -EINVAL;
	पूर्ण

	of_property_पढ़ो_u32(node, "dai-tdm-slot-width", &be->slot_width);

	वापस 0;
पूर्ण

अटल पूर्णांक axg_card_parse_codecs_masks(काष्ठा snd_soc_card *card,
				       काष्ठा snd_soc_dai_link *link,
				       काष्ठा device_node *node,
				       काष्ठा axg_dai_link_tdm_data *be)
अणु
	काष्ठा axg_dai_link_tdm_mask *codec_mask;
	काष्ठा device_node *np;

	codec_mask = devm_kसुस्मृति(card->dev, link->num_codecs,
				  माप(*codec_mask), GFP_KERNEL);
	अगर (!codec_mask)
		वापस -ENOMEM;

	be->codec_masks = codec_mask;

	क्रम_each_child_of_node(node, np) अणु
		snd_soc_of_get_slot_mask(np, "dai-tdm-slot-rx-mask",
					 &codec_mask->rx);
		snd_soc_of_get_slot_mask(np, "dai-tdm-slot-tx-mask",
					 &codec_mask->tx);

		codec_mask++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axg_card_parse_tdm(काष्ठा snd_soc_card *card,
			      काष्ठा device_node *node,
			      पूर्णांक *index)
अणु
	काष्ठा meson_card *priv = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai_link *link = &card->dai_link[*index];
	काष्ठा axg_dai_link_tdm_data *be;
	पूर्णांक ret;

	/* Allocate tdm link parameters */
	be = devm_kzalloc(card->dev, माप(*be), GFP_KERNEL);
	अगर (!be)
		वापस -ENOMEM;
	priv->link_data[*index] = be;

	/* Setup tdm link */
	link->ops = &axg_card_tdm_be_ops;
	link->init = axg_card_tdm_dai_init;
	link->dai_fmt = meson_card_parse_daअगरmt(node, link->cpus->of_node);

	of_property_पढ़ो_u32(node, "mclk-fs", &be->mclk_fs);

	ret = axg_card_parse_cpu_tdm_slots(card, link, node, be);
	अगर (ret) अणु
		dev_err(card->dev, "error parsing tdm link slots\n");
		वापस ret;
	पूर्ण

	ret = axg_card_parse_codecs_masks(card, link, node, be);
	अगर (ret)
		वापस ret;

	/* Add loopback अगर the pad dai has playback */
	अगर (link->dpcm_playback) अणु
		ret = axg_card_add_tdm_loopback(card, index);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axg_card_cpu_is_capture_fe(काष्ठा device_node *np)
अणु
	वापस of_device_is_compatible(np, DT_PREFIX "axg-toddr");
पूर्ण

अटल पूर्णांक axg_card_cpu_is_playback_fe(काष्ठा device_node *np)
अणु
	वापस of_device_is_compatible(np, DT_PREFIX "axg-frddr");
पूर्ण

अटल पूर्णांक axg_card_cpu_is_tdm_अगरace(काष्ठा device_node *np)
अणु
	वापस of_device_is_compatible(np, DT_PREFIX "axg-tdm-iface");
पूर्ण

अटल पूर्णांक axg_card_cpu_is_codec(काष्ठा device_node *np)
अणु
	वापस of_device_is_compatible(np, DT_PREFIX "g12a-tohdmitx") ||
		of_device_is_compatible(np, DT_PREFIX "g12a-toacodec");
पूर्ण

अटल पूर्णांक axg_card_add_link(काष्ठा snd_soc_card *card, काष्ठा device_node *np,
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

	अगर (axg_card_cpu_is_playback_fe(dai_link->cpus->of_node))
		वापस meson_card_set_fe_link(card, dai_link, np, true);
	अन्यथा अगर (axg_card_cpu_is_capture_fe(dai_link->cpus->of_node))
		वापस meson_card_set_fe_link(card, dai_link, np, false);


	ret = meson_card_set_be_link(card, dai_link, np);
	अगर (ret)
		वापस ret;

	अगर (axg_card_cpu_is_codec(dai_link->cpus->of_node)) अणु
		dai_link->params = &codec_params;
	पूर्ण अन्यथा अणु
		dai_link->no_pcm = 1;
		snd_soc_dai_link_set_capabilities(dai_link);
		अगर (axg_card_cpu_is_tdm_अगरace(dai_link->cpus->of_node))
			ret = axg_card_parse_tdm(card, np, index);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा meson_card_match_data axg_card_match_data = अणु
	.add_link = axg_card_add_link,
पूर्ण;

अटल स्थिर काष्ठा of_device_id axg_card_of_match[] = अणु
	अणु
		.compatible = "amlogic,axg-sound-card",
		.data = &axg_card_match_data,
	पूर्ण, अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axg_card_of_match);

अटल काष्ठा platक्रमm_driver axg_card_pdrv = अणु
	.probe = meson_card_probe,
	.हटाओ = meson_card_हटाओ,
	.driver = अणु
		.name = "axg-sound-card",
		.of_match_table = axg_card_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(axg_card_pdrv);

MODULE_DESCRIPTION("Amlogic AXG ALSA machine driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
