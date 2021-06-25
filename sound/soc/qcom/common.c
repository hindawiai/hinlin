<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018, Linaro Limited.
// Copyright (c) 2018, The Linux Foundation. All rights reserved.

#समावेश <linux/module.h>
#समावेश "common.h"

पूर्णांक qcom_snd_parse_of(काष्ठा snd_soc_card *card)
अणु
	काष्ठा device_node *np;
	काष्ठा device_node *codec = शून्य;
	काष्ठा device_node *platक्रमm = शून्य;
	काष्ठा device_node *cpu = शून्य;
	काष्ठा device *dev = card->dev;
	काष्ठा snd_soc_dai_link *link;
	काष्ठा of_phandle_args args;
	काष्ठा snd_soc_dai_link_component *dlc;
	पूर्णांक ret, num_links;

	ret = snd_soc_of_parse_card_name(card, "model");
	अगर (ret == 0 && !card->name)
		/* Deprecated, only क्रम compatibility with old device trees */
		ret = snd_soc_of_parse_card_name(card, "qcom,model");
	अगर (ret) अणु
		dev_err(dev, "Error parsing card name: %d\n", ret);
		वापस ret;
	पूर्ण

	/* DAPM routes */
	अगर (of_property_पढ़ो_bool(dev->of_node, "audio-routing")) अणु
		ret = snd_soc_of_parse_audio_routing(card, "audio-routing");
		अगर (ret)
			वापस ret;
	पूर्ण
	/* Deprecated, only क्रम compatibility with old device trees */
	अगर (of_property_पढ़ो_bool(dev->of_node, "qcom,audio-routing")) अणु
		ret = snd_soc_of_parse_audio_routing(card, "qcom,audio-routing");
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = snd_soc_of_parse_aux_devs(card, "aux-devs");
	अगर (ret)
		वापस ret;

	/* Populate links */
	num_links = of_get_child_count(dev->of_node);

	/* Allocate the DAI link array */
	card->dai_link = devm_kसुस्मृति(dev, num_links, माप(*link), GFP_KERNEL);
	अगर (!card->dai_link)
		वापस -ENOMEM;

	card->num_links = num_links;
	link = card->dai_link;

	क्रम_each_child_of_node(dev->of_node, np) अणु
		dlc = devm_kzalloc(dev, 2 * माप(*dlc), GFP_KERNEL);
		अगर (!dlc) अणु
			ret = -ENOMEM;
			जाओ err_put_np;
		पूर्ण

		link->cpus	= &dlc[0];
		link->platक्रमms	= &dlc[1];

		link->num_cpus		= 1;
		link->num_platक्रमms	= 1;

		ret = of_property_पढ़ो_string(np, "link-name", &link->name);
		अगर (ret) अणु
			dev_err(card->dev, "error getting codec dai_link name\n");
			जाओ err_put_np;
		पूर्ण

		cpu = of_get_child_by_name(np, "cpu");
		platक्रमm = of_get_child_by_name(np, "platform");
		codec = of_get_child_by_name(np, "codec");

		अगर (!cpu) अणु
			dev_err(dev, "%s: Can't find cpu DT node\n", link->name);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		ret = of_parse_phandle_with_args(cpu, "sound-dai",
					"#sound-dai-cells", 0, &args);
		अगर (ret) अणु
			dev_err(card->dev, "%s: error getting cpu phandle\n", link->name);
			जाओ err;
		पूर्ण
		link->cpus->of_node = args.np;
		link->id = args.args[0];

		ret = snd_soc_of_get_dai_name(cpu, &link->cpus->dai_name);
		अगर (ret) अणु
			अगर (ret != -EPROBE_DEFER)
				dev_err(card->dev, "%s: error getting cpu dai name: %d\n",
					link->name, ret);
			जाओ err;
		पूर्ण

		अगर (platक्रमm) अणु
			link->platक्रमms->of_node = of_parse_phandle(platक्रमm,
					"sound-dai",
					0);
			अगर (!link->platक्रमms->of_node) अणु
				dev_err(card->dev, "%s: platform dai not found\n", link->name);
				ret = -EINVAL;
				जाओ err;
			पूर्ण
		पूर्ण अन्यथा अणु
			link->platक्रमms->of_node = link->cpus->of_node;
		पूर्ण

		अगर (codec) अणु
			ret = snd_soc_of_get_dai_link_codecs(dev, codec, link);
			अगर (ret < 0) अणु
				अगर (ret != -EPROBE_DEFER)
					dev_err(card->dev, "%s: codec dai not found: %d\n",
						link->name, ret);
				जाओ err;
			पूर्ण

			अगर (platक्रमm) अणु
				/* DPCM backend */
				link->no_pcm = 1;
				link->ignore_pmकरोwn_समय = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* DPCM frontend */
			dlc = devm_kzalloc(dev, माप(*dlc), GFP_KERNEL);
			अगर (!dlc) अणु
				ret = -ENOMEM;
				जाओ err;
			पूर्ण

			link->codecs	 = dlc;
			link->num_codecs = 1;

			link->codecs->dai_name = "snd-soc-dummy-dai";
			link->codecs->name = "snd-soc-dummy";
			link->dynamic = 1;
		पूर्ण

		अगर (platक्रमm || !codec) अणु
			/* DPCM */
			snd_soc_dai_link_set_capabilities(link);
			link->ignore_suspend = 1;
			link->nonatomic = 1;
		पूर्ण

		link->stream_name = link->name;
		link++;

		of_node_put(cpu);
		of_node_put(codec);
		of_node_put(platक्रमm);
	पूर्ण

	वापस 0;
err:
	of_node_put(cpu);
	of_node_put(codec);
	of_node_put(platक्रमm);
err_put_np:
	of_node_put(np);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(qcom_snd_parse_of);

MODULE_LICENSE("GPL v2");
