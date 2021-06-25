<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2020 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <sound/soc.h>

#समावेश "meson-card.h"

पूर्णांक meson_card_i2s_set_sysclk(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params,
			      अचिन्हित पूर्णांक mclk_fs)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai;
	अचिन्हित पूर्णांक mclk;
	पूर्णांक ret, i;

	अगर (!mclk_fs)
		वापस 0;

	mclk = params_rate(params) * mclk_fs;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		ret = snd_soc_dai_set_sysclk(codec_dai, 0, mclk,
					     SND_SOC_CLOCK_IN);
		अगर (ret && ret != -ENOTSUPP)
			वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(asoc_rtd_to_cpu(rtd, 0), 0, mclk,
				     SND_SOC_CLOCK_OUT);
	अगर (ret && ret != -ENOTSUPP)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(meson_card_i2s_set_sysclk);

पूर्णांक meson_card_पुनः_स्मृतिate_links(काष्ठा snd_soc_card *card,
				अचिन्हित पूर्णांक num_links)
अणु
	काष्ठा meson_card *priv = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai_link *links;
	व्योम **ldata;

	links = kपुनः_स्मृति(priv->card.dai_link,
			 num_links * माप(*priv->card.dai_link),
			 GFP_KERNEL | __GFP_ZERO);
	अगर (!links)
		जाओ err_links;

	ldata = kपुनः_स्मृति(priv->link_data,
			 num_links * माप(*priv->link_data),
			 GFP_KERNEL | __GFP_ZERO);
	अगर (!ldata)
		जाओ err_ldata;

	priv->card.dai_link = links;
	priv->link_data = ldata;
	priv->card.num_links = num_links;
	वापस 0;

err_ldata:
	kमुक्त(links);
err_links:
	dev_err(priv->card.dev, "failed to allocate links\n");
	वापस -ENOMEM;

पूर्ण
EXPORT_SYMBOL_GPL(meson_card_पुनः_स्मृतिate_links);

पूर्णांक meson_card_parse_dai(काष्ठा snd_soc_card *card,
			 काष्ठा device_node *node,
			 काष्ठा device_node **dai_of_node,
			 स्थिर अक्षर **dai_name)
अणु
	काष्ठा of_phandle_args args;
	पूर्णांक ret;

	अगर (!dai_name || !dai_of_node || !node)
		वापस -EINVAL;

	ret = of_parse_phandle_with_args(node, "sound-dai",
					 "#sound-dai-cells", 0, &args);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(card->dev, "can't parse dai %d\n", ret);
		वापस ret;
	पूर्ण
	*dai_of_node = args.np;

	वापस snd_soc_get_dai_name(&args, dai_name);
पूर्ण
EXPORT_SYMBOL_GPL(meson_card_parse_dai);

अटल पूर्णांक meson_card_set_link_name(काष्ठा snd_soc_card *card,
				    काष्ठा snd_soc_dai_link *link,
				    काष्ठा device_node *node,
				    स्थिर अक्षर *prefix)
अणु
	अक्षर *name = devm_kaप्र_लिखो(card->dev, GFP_KERNEL, "%s.%s",
				    prefix, node->full_name);
	अगर (!name)
		वापस -ENOMEM;

	link->name = name;
	link->stream_name = name;

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक meson_card_parse_daअगरmt(काष्ठा device_node *node,
				     काष्ठा device_node *cpu_node)
अणु
	काष्ठा device_node *bitclkmaster = शून्य;
	काष्ठा device_node *framemaster = शून्य;
	अचिन्हित पूर्णांक daअगरmt;

	daअगरmt = snd_soc_of_parse_daअगरmt(node, "",
					 &bitclkmaster, &framemaster);
	daअगरmt &= ~SND_SOC_DAIFMT_MASTER_MASK;

	/* If no master is provided, शेष to cpu master */
	अगर (!bitclkmaster || bitclkmaster == cpu_node) अणु
		daअगरmt |= (!framemaster || framemaster == cpu_node) ?
			SND_SOC_DAIFMT_CBS_CFS : SND_SOC_DAIFMT_CBS_CFM;
	पूर्ण अन्यथा अणु
		daअगरmt |= (!framemaster || framemaster == cpu_node) ?
			SND_SOC_DAIFMT_CBM_CFS : SND_SOC_DAIFMT_CBM_CFM;
	पूर्ण

	of_node_put(bitclkmaster);
	of_node_put(framemaster);

	वापस daअगरmt;
पूर्ण
EXPORT_SYMBOL_GPL(meson_card_parse_daअगरmt);

पूर्णांक meson_card_set_be_link(काष्ठा snd_soc_card *card,
			   काष्ठा snd_soc_dai_link *link,
			   काष्ठा device_node *node)
अणु
	काष्ठा snd_soc_dai_link_component *codec;
	काष्ठा device_node *np;
	पूर्णांक ret, num_codecs;

	num_codecs = of_get_child_count(node);
	अगर (!num_codecs) अणु
		dev_err(card->dev, "be link %s has no codec\n",
			node->full_name);
		वापस -EINVAL;
	पूर्ण

	codec = devm_kसुस्मृति(card->dev, num_codecs, माप(*codec), GFP_KERNEL);
	अगर (!codec)
		वापस -ENOMEM;

	link->codecs = codec;
	link->num_codecs = num_codecs;

	क्रम_each_child_of_node(node, np) अणु
		ret = meson_card_parse_dai(card, np, &codec->of_node,
					   &codec->dai_name);
		अगर (ret) अणु
			of_node_put(np);
			वापस ret;
		पूर्ण

		codec++;
	पूर्ण

	ret = meson_card_set_link_name(card, link, node, "be");
	अगर (ret)
		dev_err(card->dev, "error setting %pOFn link name\n", np);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(meson_card_set_be_link);

पूर्णांक meson_card_set_fe_link(काष्ठा snd_soc_card *card,
			   काष्ठा snd_soc_dai_link *link,
			   काष्ठा device_node *node,
			   bool is_playback)
अणु
	काष्ठा snd_soc_dai_link_component *codec;

	codec = devm_kzalloc(card->dev, माप(*codec), GFP_KERNEL);
	अगर (!codec)
		वापस -ENOMEM;

	link->codecs = codec;
	link->num_codecs = 1;

	link->dynamic = 1;
	link->dpcm_merged_क्रमmat = 1;
	link->dpcm_merged_chan = 1;
	link->dpcm_merged_rate = 1;
	link->codecs->dai_name = "snd-soc-dummy-dai";
	link->codecs->name = "snd-soc-dummy";

	अगर (is_playback)
		link->dpcm_playback = 1;
	अन्यथा
		link->dpcm_capture = 1;

	वापस meson_card_set_link_name(card, link, node, "fe");
पूर्ण
EXPORT_SYMBOL_GPL(meson_card_set_fe_link);

अटल पूर्णांक meson_card_add_links(काष्ठा snd_soc_card *card)
अणु
	काष्ठा meson_card *priv = snd_soc_card_get_drvdata(card);
	काष्ठा device_node *node = card->dev->of_node;
	काष्ठा device_node *np;
	पूर्णांक num, i, ret;

	num = of_get_child_count(node);
	अगर (!num) अणु
		dev_err(card->dev, "card has no links\n");
		वापस -EINVAL;
	पूर्ण

	ret = meson_card_पुनः_स्मृतिate_links(card, num);
	अगर (ret)
		वापस ret;

	i = 0;
	क्रम_each_child_of_node(node, np) अणु
		ret = priv->match_data->add_link(card, np, &i);
		अगर (ret) अणु
			of_node_put(np);
			वापस ret;
		पूर्ण

		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson_card_parse_of_optional(काष्ठा snd_soc_card *card,
					स्थिर अक्षर *propname,
					पूर्णांक (*func)(काष्ठा snd_soc_card *c,
						    स्थिर अक्षर *p))
अणु
	/* If property is not provided, करोn't fail ... */
	अगर (!of_property_पढ़ो_bool(card->dev->of_node, propname))
		वापस 0;

	/* ... but करो fail अगर it is provided and the parsing fails */
	वापस func(card, propname);
पूर्ण

अटल व्योम meson_card_clean_references(काष्ठा meson_card *priv)
अणु
	काष्ठा snd_soc_card *card = &priv->card;
	काष्ठा snd_soc_dai_link *link;
	काष्ठा snd_soc_dai_link_component *codec;
	काष्ठा snd_soc_aux_dev *aux;
	पूर्णांक i, j;

	अगर (card->dai_link) अणु
		क्रम_each_card_prelinks(card, i, link) अणु
			अगर (link->cpus)
				of_node_put(link->cpus->of_node);
			क्रम_each_link_codecs(link, j, codec)
				of_node_put(codec->of_node);
		पूर्ण
	पूर्ण

	अगर (card->aux_dev) अणु
		क्रम_each_card_pre_auxs(card, i, aux)
			of_node_put(aux->dlc.of_node);
	पूर्ण

	kमुक्त(card->dai_link);
	kमुक्त(priv->link_data);
पूर्ण

पूर्णांक meson_card_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा meson_card_match_data *data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा meson_card *priv;
	पूर्णांक ret;

	data = of_device_get_match_data(dev);
	अगर (!data) अणु
		dev_err(dev, "failed to match device\n");
		वापस -ENODEV;
	पूर्ण

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);
	snd_soc_card_set_drvdata(&priv->card, priv);

	priv->card.owner = THIS_MODULE;
	priv->card.dev = dev;
	priv->match_data = data;

	ret = snd_soc_of_parse_card_name(&priv->card, "model");
	अगर (ret < 0)
		वापस ret;

	ret = meson_card_parse_of_optional(&priv->card, "audio-routing",
					   snd_soc_of_parse_audio_routing);
	अगर (ret) अणु
		dev_err(dev, "error while parsing routing\n");
		वापस ret;
	पूर्ण

	ret = meson_card_parse_of_optional(&priv->card, "audio-widgets",
					   snd_soc_of_parse_audio_simple_widमाला_लो);
	अगर (ret) अणु
		dev_err(dev, "error while parsing widgets\n");
		वापस ret;
	पूर्ण

	ret = meson_card_add_links(&priv->card);
	अगर (ret)
		जाओ out_err;

	ret = snd_soc_of_parse_aux_devs(&priv->card, "audio-aux-devs");
	अगर (ret)
		जाओ out_err;

	ret = devm_snd_soc_रेजिस्टर_card(dev, &priv->card);
	अगर (ret)
		जाओ out_err;

	वापस 0;

out_err:
	meson_card_clean_references(priv);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(meson_card_probe);

पूर्णांक meson_card_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_card *priv = platक्रमm_get_drvdata(pdev);

	meson_card_clean_references(priv);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(meson_card_हटाओ);

MODULE_DESCRIPTION("Amlogic Sound Card Utils");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
