<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// ASoC simple sound card support
//
// Copyright (C) 2012 Renesas Solutions Corp.
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/माला.स>
#समावेश <sound/simple_card.h>
#समावेश <sound/soc-dai.h>
#समावेश <sound/soc.h>

#घोषणा DPCM_SELECTABLE 1

#घोषणा DAI	"sound-dai"
#घोषणा CELL	"#sound-dai-cells"
#घोषणा PREFIX	"simple-audio-card,"

अटल स्थिर काष्ठा snd_soc_ops simple_ops = अणु
	.startup	= asoc_simple_startup,
	.shutकरोwn	= asoc_simple_shutकरोwn,
	.hw_params	= asoc_simple_hw_params,
पूर्ण;

अटल पूर्णांक asoc_simple_parse_dai(काष्ठा device_node *node,
				 काष्ठा snd_soc_dai_link_component *dlc,
				 पूर्णांक *is_single_link)
अणु
	काष्ठा of_phandle_args args;
	पूर्णांक ret;

	अगर (!node)
		वापस 0;

	/*
	 * Get node via "sound-dai = <&phandle port>"
	 * it will be used as xxx_of_node on soc_bind_dai_link()
	 */
	ret = of_parse_phandle_with_args(node, DAI, CELL, 0, &args);
	अगर (ret)
		वापस ret;

	/*
	 * FIXME
	 *
	 * Here, dlc->dai_name is poपूर्णांकer to CPU/Codec DAI name.
	 * If user unbinded CPU or Codec driver, but not क्रम Sound Card,
	 * dlc->dai_name is keeping unbinded CPU or Codec
	 * driver's poपूर्णांकer.
	 *
	 * If user re-bind CPU or Codec driver again, ALSA SoC will try
	 * to rebind Card via snd_soc_try_rebind_card(), but because of
	 * above reason, it might can't bind Sound Card.
	 * Because Sound Card is poपूर्णांकing to released dai_name poपूर्णांकer.
	 *
	 * To aव्योम this rebind Card issue,
	 * 1) It needs to alloc memory to keep dai_name eventhough
	 *    CPU or Codec driver was unbinded, or
	 * 2) user need to rebind Sound Card everyसमय
	 *    अगर he unbinded CPU or Codec.
	 */
	ret = snd_soc_of_get_dai_name(node, &dlc->dai_name);
	अगर (ret < 0)
		वापस ret;

	dlc->of_node = args.np;

	अगर (is_single_link)
		*is_single_link = !args.args_count;

	वापस 0;
पूर्ण

अटल व्योम simple_parse_convert(काष्ठा device *dev,
				 काष्ठा device_node *np,
				 काष्ठा asoc_simple_data *adata)
अणु
	काष्ठा device_node *top = dev->of_node;
	काष्ठा device_node *node = of_get_parent(np);

	asoc_simple_parse_convert(top,  PREFIX, adata);
	asoc_simple_parse_convert(node, PREFIX, adata);
	asoc_simple_parse_convert(node, शून्य,   adata);
	asoc_simple_parse_convert(np,   शून्य,   adata);

	of_node_put(node);
पूर्ण

अटल व्योम simple_parse_mclk_fs(काष्ठा device_node *top,
				 काष्ठा device_node *np,
				 काष्ठा simple_dai_props *props,
				 अक्षर *prefix)
अणु
	काष्ठा device_node *node = of_get_parent(np);
	अक्षर prop[128];

	snम_लिखो(prop, माप(prop), "%smclk-fs", PREFIX);
	of_property_पढ़ो_u32(top,	prop, &props->mclk_fs);

	snम_लिखो(prop, माप(prop), "%smclk-fs", prefix);
	of_property_पढ़ो_u32(node,	prop, &props->mclk_fs);
	of_property_पढ़ो_u32(np,	prop, &props->mclk_fs);

	of_node_put(node);
पूर्ण

अटल पूर्णांक simple_parse_node(काष्ठा asoc_simple_priv *priv,
			     काष्ठा device_node *np,
			     काष्ठा link_info *li,
			     अक्षर *prefix,
			     पूर्णांक *cpu)
अणु
	काष्ठा device *dev = simple_priv_to_dev(priv);
	काष्ठा device_node *top = dev->of_node;
	काष्ठा snd_soc_dai_link *dai_link = simple_priv_to_link(priv, li->link);
	काष्ठा simple_dai_props *dai_props = simple_priv_to_props(priv, li->link);
	काष्ठा snd_soc_dai_link_component *dlc;
	काष्ठा asoc_simple_dai *dai;
	पूर्णांक ret;

	अगर (cpu) अणु
		dlc = asoc_link_to_cpu(dai_link, 0);
		dai = simple_props_to_dai_cpu(dai_props, 0);
	पूर्ण अन्यथा अणु
		dlc = asoc_link_to_codec(dai_link, 0);
		dai = simple_props_to_dai_codec(dai_props, 0);
	पूर्ण

	simple_parse_mclk_fs(top, np, dai_props, prefix);

	ret = asoc_simple_parse_dai(np, dlc, cpu);
	अगर (ret)
		वापस ret;

	ret = asoc_simple_parse_clk(dev, np, dai, dlc);
	अगर (ret)
		वापस ret;

	ret = asoc_simple_parse_tdm(np, dai);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक simple_link_init(काष्ठा asoc_simple_priv *priv,
			    काष्ठा device_node *node,
			    काष्ठा device_node *codec,
			    काष्ठा link_info *li,
			    अक्षर *prefix, अक्षर *name)
अणु
	काष्ठा device *dev = simple_priv_to_dev(priv);
	काष्ठा snd_soc_dai_link *dai_link = simple_priv_to_link(priv, li->link);
	पूर्णांक ret;

	ret = asoc_simple_parse_daअगरmt(dev, node, codec,
				       prefix, &dai_link->dai_fmt);
	अगर (ret < 0)
		वापस 0;

	dai_link->init			= asoc_simple_dai_init;
	dai_link->ops			= &simple_ops;

	वापस asoc_simple_set_dailink_name(dev, dai_link, name);
पूर्ण

अटल पूर्णांक simple_dai_link_of_dpcm(काष्ठा asoc_simple_priv *priv,
				   काष्ठा device_node *np,
				   काष्ठा device_node *codec,
				   काष्ठा link_info *li,
				   bool is_top)
अणु
	काष्ठा device *dev = simple_priv_to_dev(priv);
	काष्ठा snd_soc_dai_link *dai_link = simple_priv_to_link(priv, li->link);
	काष्ठा simple_dai_props *dai_props = simple_priv_to_props(priv, li->link);
	काष्ठा device_node *top = dev->of_node;
	काष्ठा device_node *node = of_get_parent(np);
	अक्षर *prefix = "";
	अक्षर dai_name[64];
	पूर्णांक ret;

	dev_dbg(dev, "link_of DPCM (%pOF)\n", np);

	/* For single DAI link & old style of DT node */
	अगर (is_top)
		prefix = PREFIX;

	अगर (li->cpu) अणु
		काष्ठा snd_soc_dai_link_component *cpus = asoc_link_to_cpu(dai_link, 0);
		काष्ठा snd_soc_dai_link_component *platक्रमms = asoc_link_to_platक्रमm(dai_link, 0);
		पूर्णांक is_single_links = 0;

		/* Codec is dummy */

		/* FE settings */
		dai_link->dynamic		= 1;
		dai_link->dpcm_merged_क्रमmat	= 1;

		ret = simple_parse_node(priv, np, li, prefix, &is_single_links);
		अगर (ret < 0)
			जाओ out_put_node;

		snम_लिखो(dai_name, माप(dai_name), "fe.%s", cpus->dai_name);

		asoc_simple_canonicalize_cpu(cpus, is_single_links);
		asoc_simple_canonicalize_platक्रमm(platक्रमms, cpus);
	पूर्ण अन्यथा अणु
		काष्ठा snd_soc_dai_link_component *codecs = asoc_link_to_codec(dai_link, 0);
		काष्ठा snd_soc_codec_conf *cconf;

		/* CPU is dummy */

		/* BE settings */
		dai_link->no_pcm		= 1;
		dai_link->be_hw_params_fixup	= asoc_simple_be_hw_params_fixup;

		cconf	= simple_props_to_codec_conf(dai_props, 0);

		ret = simple_parse_node(priv, np, li, prefix, शून्य);
		अगर (ret < 0)
			जाओ out_put_node;

		snम_लिखो(dai_name, माप(dai_name), "be.%s", codecs->dai_name);

		/* check "prefix" from top node */
		snd_soc_of_parse_node_prefix(top, cconf, codecs->of_node,
					      PREFIX "prefix");
		snd_soc_of_parse_node_prefix(node, cconf, codecs->of_node,
					     "prefix");
		snd_soc_of_parse_node_prefix(np, cconf, codecs->of_node,
					     "prefix");
	पूर्ण

	simple_parse_convert(dev, np, &dai_props->adata);

	snd_soc_dai_link_set_capabilities(dai_link);

	ret = simple_link_init(priv, node, codec, li, prefix, dai_name);

out_put_node:
	li->link++;

	of_node_put(node);
	वापस ret;
पूर्ण

अटल पूर्णांक simple_dai_link_of(काष्ठा asoc_simple_priv *priv,
			      काष्ठा device_node *np,
			      काष्ठा device_node *codec,
			      काष्ठा link_info *li,
			      bool is_top)
अणु
	काष्ठा device *dev = simple_priv_to_dev(priv);
	काष्ठा snd_soc_dai_link *dai_link = simple_priv_to_link(priv, li->link);
	काष्ठा snd_soc_dai_link_component *cpus = asoc_link_to_cpu(dai_link, 0);
	काष्ठा snd_soc_dai_link_component *codecs = asoc_link_to_codec(dai_link, 0);
	काष्ठा snd_soc_dai_link_component *platक्रमms = asoc_link_to_platक्रमm(dai_link, 0);
	काष्ठा device_node *cpu = शून्य;
	काष्ठा device_node *node = शून्य;
	काष्ठा device_node *plat = शून्य;
	अक्षर dai_name[64];
	अक्षर prop[128];
	अक्षर *prefix = "";
	पूर्णांक ret, single_cpu = 0;

	cpu  = np;
	node = of_get_parent(np);

	dev_dbg(dev, "link_of (%pOF)\n", node);

	/* For single DAI link & old style of DT node */
	अगर (is_top)
		prefix = PREFIX;

	snम_लिखो(prop, माप(prop), "%splat", prefix);
	plat = of_get_child_by_name(node, prop);

	ret = simple_parse_node(priv, cpu, li, prefix, &single_cpu);
	अगर (ret < 0)
		जाओ dai_link_of_err;

	ret = simple_parse_node(priv, codec, li, prefix, शून्य);
	अगर (ret < 0)
		जाओ dai_link_of_err;

	ret = asoc_simple_parse_dai(plat, platक्रमms, शून्य);
	अगर (ret < 0)
		जाओ dai_link_of_err;

	snम_लिखो(dai_name, माप(dai_name),
		 "%s-%s", cpus->dai_name, codecs->dai_name);

	asoc_simple_canonicalize_cpu(cpus, single_cpu);
	asoc_simple_canonicalize_platक्रमm(platक्रमms, cpus);

	ret = simple_link_init(priv, node, codec, li, prefix, dai_name);

dai_link_of_err:
	of_node_put(plat);
	of_node_put(node);

	li->link++;

	वापस ret;
पूर्ण

अटल पूर्णांक __simple_क्रम_each_link(काष्ठा asoc_simple_priv *priv,
			काष्ठा link_info *li,
			पूर्णांक (*func_noml)(काष्ठा asoc_simple_priv *priv,
					 काष्ठा device_node *np,
					 काष्ठा device_node *codec,
					 काष्ठा link_info *li, bool is_top),
			पूर्णांक (*func_dpcm)(काष्ठा asoc_simple_priv *priv,
					 काष्ठा device_node *np,
					 काष्ठा device_node *codec,
					 काष्ठा link_info *li, bool is_top))
अणु
	काष्ठा device *dev = simple_priv_to_dev(priv);
	काष्ठा device_node *top = dev->of_node;
	काष्ठा device_node *node;
	uपूर्णांकptr_t dpcm_selectable = (uपूर्णांकptr_t)of_device_get_match_data(dev);
	bool is_top = 0;
	पूर्णांक ret = 0;

	/* Check अगर it has dai-link */
	node = of_get_child_by_name(top, PREFIX "dai-link");
	अगर (!node) अणु
		node = of_node_get(top);
		is_top = 1;
	पूर्ण

	/* loop क्रम all dai-link */
	करो अणु
		काष्ठा asoc_simple_data adata;
		काष्ठा device_node *codec;
		काष्ठा device_node *plat;
		काष्ठा device_node *np;
		पूर्णांक num = of_get_child_count(node);

		/* get codec */
		codec = of_get_child_by_name(node, is_top ?
					     PREFIX "codec" : "codec");
		अगर (!codec) अणु
			ret = -ENODEV;
			जाओ error;
		पूर्ण
		/* get platक्रमm */
		plat = of_get_child_by_name(node, is_top ?
					    PREFIX "plat" : "plat");

		/* get convert-xxx property */
		स_रखो(&adata, 0, माप(adata));
		क्रम_each_child_of_node(node, np)
			simple_parse_convert(dev, np, &adata);

		/* loop क्रम all CPU/Codec node */
		क्रम_each_child_of_node(node, np) अणु
			अगर (plat == np)
				जारी;
			/*
			 * It is DPCM
			 * अगर it has many CPUs,
			 * or has convert-xxx property
			 */
			अगर (dpcm_selectable &&
			    (num > 2 ||
			     adata.convert_rate || adata.convert_channels)) अणु
				/*
				 * np
				 *	 |1(CPU)|0(Codec)  li->cpu
				 * CPU	 |Pass  |वापस
				 * Codec |वापस|Pass
				 */
				अगर (li->cpu != (np == codec))
					ret = func_dpcm(priv, np, codec, li, is_top);
			/* अन्यथा normal sound */
			पूर्ण अन्यथा अणु
				/*
				 * np
				 *	 |1(CPU)|0(Codec)  li->cpu
				 * CPU	 |Pass  |वापस
				 * Codec |वापस|वापस
				 */
				अगर (li->cpu && (np != codec))
					ret = func_noml(priv, np, codec, li, is_top);
			पूर्ण

			अगर (ret < 0) अणु
				of_node_put(codec);
				of_node_put(np);
				जाओ error;
			पूर्ण
		पूर्ण

		of_node_put(codec);
		node = of_get_next_child(top, node);
	पूर्ण जबतक (!is_top && node);

 error:
	of_node_put(node);
	वापस ret;
पूर्ण

अटल पूर्णांक simple_क्रम_each_link(काष्ठा asoc_simple_priv *priv,
				काष्ठा link_info *li,
				पूर्णांक (*func_noml)(काष्ठा asoc_simple_priv *priv,
						 काष्ठा device_node *np,
						 काष्ठा device_node *codec,
						 काष्ठा link_info *li, bool is_top),
				पूर्णांक (*func_dpcm)(काष्ठा asoc_simple_priv *priv,
						 काष्ठा device_node *np,
						 काष्ठा device_node *codec,
						 काष्ठा link_info *li, bool is_top))
अणु
	पूर्णांक ret;
	/*
	 * Detect all CPU first, and Detect all Codec 2nd.
	 *
	 * In Normal sound हाल, all DAIs are detected
	 * as "CPU-Codec".
	 *
	 * In DPCM sound हाल,
	 * all CPUs   are detected as "CPU-dummy", and
	 * all Codecs are detected as "dummy-Codec".
	 * To aव्योम अक्रमom sub-device numbering,
	 * detect "dummy-Codec" in last;
	 */
	क्रम (li->cpu = 1; li->cpu >= 0; li->cpu--) अणु
		ret = __simple_क्रम_each_link(priv, li, func_noml, func_dpcm);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक simple_parse_of(काष्ठा asoc_simple_priv *priv, काष्ठा link_info *li)
अणु
	काष्ठा snd_soc_card *card = simple_priv_to_card(priv);
	पूर्णांक ret;

	ret = asoc_simple_parse_widमाला_लो(card, PREFIX);
	अगर (ret < 0)
		वापस ret;

	ret = asoc_simple_parse_routing(card, PREFIX);
	अगर (ret < 0)
		वापस ret;

	ret = asoc_simple_parse_pin_चयनes(card, PREFIX);
	अगर (ret < 0)
		वापस ret;

	/* Single/Muti DAI link(s) & New style of DT node */
	स_रखो(li, 0, माप(*li));
	ret = simple_क्रम_each_link(priv, li,
				   simple_dai_link_of,
				   simple_dai_link_of_dpcm);
	अगर (ret < 0)
		वापस ret;

	ret = asoc_simple_parse_card_name(card, PREFIX);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_of_parse_aux_devs(card, PREFIX "aux-devs");

	वापस ret;
पूर्ण

अटल पूर्णांक simple_count_noml(काष्ठा asoc_simple_priv *priv,
			     काष्ठा device_node *np,
			     काष्ठा device_node *codec,
			     काष्ठा link_info *li, bool is_top)
अणु
	अगर (li->link >= SNDRV_MAX_LINKS) अणु
		काष्ठा device *dev = simple_priv_to_dev(priv);

		dev_err(dev, "too many links\n");
		वापस -EINVAL;
	पूर्ण

	li->num[li->link].cpus		= 1;
	li->num[li->link].codecs	= 1;
	li->num[li->link].platक्रमms	= 1;

	li->link += 1;

	वापस 0;
पूर्ण

अटल पूर्णांक simple_count_dpcm(काष्ठा asoc_simple_priv *priv,
			     काष्ठा device_node *np,
			     काष्ठा device_node *codec,
			     काष्ठा link_info *li, bool is_top)
अणु
	अगर (li->link >= SNDRV_MAX_LINKS) अणु
		काष्ठा device *dev = simple_priv_to_dev(priv);

		dev_err(dev, "too many links\n");
		वापस -EINVAL;
	पूर्ण

	अगर (li->cpu) अणु
		li->num[li->link].cpus		= 1;
		li->num[li->link].platक्रमms	= 1;

		li->link++; /* CPU-dummy */
	पूर्ण अन्यथा अणु
		li->num[li->link].codecs	= 1;

		li->link++; /* dummy-Codec */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक simple_get_dais_count(काष्ठा asoc_simple_priv *priv,
				 काष्ठा link_info *li)
अणु
	काष्ठा device *dev = simple_priv_to_dev(priv);
	काष्ठा device_node *top = dev->of_node;

	/*
	 * link_num :	number of links.
	 *		CPU-Codec / CPU-dummy / dummy-Codec
	 * dais_num :	number of DAIs
	 * ccnf_num :	number of codec_conf
	 *		same number क्रम "dummy-Codec"
	 *
	 * ex1)
	 * CPU0 --- Codec0	link : 5
	 * CPU1 --- Codec1	dais : 7
	 * CPU2 -/		ccnf : 1
	 * CPU3 --- Codec2
	 *
	 *	=> 5 links = 2xCPU-Codec + 2xCPU-dummy + 1xdummy-Codec
	 *	=> 7 DAIs  = 4xCPU + 3xCodec
	 *	=> 1 ccnf  = 1xdummy-Codec
	 *
	 * ex2)
	 * CPU0 --- Codec0	link : 5
	 * CPU1 --- Codec1	dais : 6
	 * CPU2 -/		ccnf : 1
	 * CPU3 -/
	 *
	 *	=> 5 links = 1xCPU-Codec + 3xCPU-dummy + 1xdummy-Codec
	 *	=> 6 DAIs  = 4xCPU + 2xCodec
	 *	=> 1 ccnf  = 1xdummy-Codec
	 *
	 * ex3)
	 * CPU0 --- Codec0	link : 6
	 * CPU1 -/		dais : 6
	 * CPU2 --- Codec1	ccnf : 2
	 * CPU3 -/
	 *
	 *	=> 6 links = 0xCPU-Codec + 4xCPU-dummy + 2xdummy-Codec
	 *	=> 6 DAIs  = 4xCPU + 2xCodec
	 *	=> 2 ccnf  = 2xdummy-Codec
	 *
	 * ex4)
	 * CPU0 --- Codec0 (convert-rate)	link : 3
	 * CPU1 --- Codec1			dais : 4
	 *					ccnf : 1
	 *
	 *	=> 3 links = 1xCPU-Codec + 1xCPU-dummy + 1xdummy-Codec
	 *	=> 4 DAIs  = 2xCPU + 2xCodec
	 *	=> 1 ccnf  = 1xdummy-Codec
	 */
	अगर (!top) अणु
		li->num[0].cpus		= 1;
		li->num[0].codecs	= 1;
		li->num[0].platक्रमms	= 1;

		li->link = 1;
		वापस 0;
	पूर्ण

	वापस simple_क्रम_each_link(priv, li,
				    simple_count_noml,
				    simple_count_dpcm);
पूर्ण

अटल पूर्णांक simple_soc_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा asoc_simple_priv *priv = snd_soc_card_get_drvdata(card);
	पूर्णांक ret;

	ret = asoc_simple_init_hp(card, &priv->hp_jack, PREFIX);
	अगर (ret < 0)
		वापस ret;

	ret = asoc_simple_init_mic(card, &priv->mic_jack, PREFIX);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक asoc_simple_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा asoc_simple_priv *priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा snd_soc_card *card;
	काष्ठा link_info *li;
	पूर्णांक ret;

	/* Allocate the निजी data and the DAI link array */
	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	card = simple_priv_to_card(priv);
	card->owner		= THIS_MODULE;
	card->dev		= dev;
	card->probe		= simple_soc_probe;

	li = devm_kzalloc(dev, माप(*li), GFP_KERNEL);
	अगर (!li)
		वापस -ENOMEM;

	ret = simple_get_dais_count(priv, li);
	अगर (ret < 0)
		वापस ret;

	अगर (!li->link)
		वापस -EINVAL;

	ret = asoc_simple_init_priv(priv, li);
	अगर (ret < 0)
		वापस ret;

	अगर (np && of_device_is_available(np)) अणु

		ret = simple_parse_of(priv, li);
		अगर (ret < 0) अणु
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "parse error %d\n", ret);
			जाओ err;
		पूर्ण

	पूर्ण अन्यथा अणु
		काष्ठा asoc_simple_card_info *cinfo;
		काष्ठा snd_soc_dai_link_component *cpus;
		काष्ठा snd_soc_dai_link_component *codecs;
		काष्ठा snd_soc_dai_link_component *platक्रमm;
		काष्ठा snd_soc_dai_link *dai_link = priv->dai_link;
		काष्ठा simple_dai_props *dai_props = priv->dai_props;

		cinfo = dev->platक्रमm_data;
		अगर (!cinfo) अणु
			dev_err(dev, "no info for asoc-simple-card\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!cinfo->name ||
		    !cinfo->codec_dai.name ||
		    !cinfo->codec ||
		    !cinfo->platक्रमm ||
		    !cinfo->cpu_dai.name) अणु
			dev_err(dev, "insufficient asoc_simple_card_info settings\n");
			वापस -EINVAL;
		पूर्ण

		cpus			= dai_link->cpus;
		cpus->dai_name		= cinfo->cpu_dai.name;

		codecs			= dai_link->codecs;
		codecs->name		= cinfo->codec;
		codecs->dai_name	= cinfo->codec_dai.name;

		platक्रमm		= dai_link->platक्रमms;
		platक्रमm->name		= cinfo->platक्रमm;

		card->name		= (cinfo->card) ? cinfo->card : cinfo->name;
		dai_link->name		= cinfo->name;
		dai_link->stream_name	= cinfo->name;
		dai_link->dai_fmt	= cinfo->daअगरmt;
		dai_link->init		= asoc_simple_dai_init;
		स_नकल(dai_props->cpu_dai, &cinfo->cpu_dai,
					माप(*dai_props->cpu_dai));
		स_नकल(dai_props->codec_dai, &cinfo->codec_dai,
					माप(*dai_props->codec_dai));
	पूर्ण

	snd_soc_card_set_drvdata(card, priv);

	asoc_simple_debug_info(priv);

	ret = devm_snd_soc_रेजिस्टर_card(dev, card);
	अगर (ret < 0)
		जाओ err;

	devm_kमुक्त(dev, li);
	वापस 0;
err:
	asoc_simple_clean_reference(card);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id simple_of_match[] = अणु
	अणु .compatible = "simple-audio-card", पूर्ण,
	अणु .compatible = "simple-scu-audio-card",
	  .data = (व्योम *)DPCM_SELECTABLE पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, simple_of_match);

अटल काष्ठा platक्रमm_driver asoc_simple_card = अणु
	.driver = अणु
		.name = "asoc-simple-card",
		.pm = &snd_soc_pm_ops,
		.of_match_table = simple_of_match,
	पूर्ण,
	.probe = asoc_simple_probe,
	.हटाओ = asoc_simple_हटाओ,
पूर्ण;

module_platक्रमm_driver(asoc_simple_card);

MODULE_ALIAS("platform:asoc-simple-card");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ASoC Simple Sound Card");
MODULE_AUTHOR("Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>");
