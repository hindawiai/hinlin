<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// ASoC audio graph sound card support
//
// Copyright (C) 2016 Renesas Solutions Corp.
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
//
// based on $अणुLINUXपूर्ण/sound/soc/generic/simple-card.c

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/माला.स>
#समावेश <sound/graph_card.h>

#घोषणा DPCM_SELECTABLE 1

अटल पूर्णांक graph_outdrv_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol,
			      पूर्णांक event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा asoc_simple_priv *priv = snd_soc_card_get_drvdata(dapm->card);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		gpiod_set_value_cansleep(priv->pa_gpio, 1);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		gpiod_set_value_cansleep(priv->pa_gpio, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget graph_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUT_DRV_E("Amplifier", SND_SOC_NOPM,
			       0, 0, शून्य, 0, graph_outdrv_event,
			       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops graph_ops = अणु
	.startup	= asoc_simple_startup,
	.shutकरोwn	= asoc_simple_shutकरोwn,
	.hw_params	= asoc_simple_hw_params,
पूर्ण;

अटल पूर्णांक graph_get_dai_id(काष्ठा device_node *ep)
अणु
	काष्ठा device_node *node;
	काष्ठा device_node *endpoपूर्णांक;
	काष्ठा of_endpoपूर्णांक info;
	पूर्णांक i, id;
	स्थिर u32 *reg;
	पूर्णांक ret;

	/* use driver specअगरied DAI ID अगर exist */
	ret = snd_soc_get_dai_id(ep);
	अगर (ret != -ENOTSUPP)
		वापस ret;

	/* use endpoपूर्णांक/port reg अगर exist */
	ret = of_graph_parse_endpoपूर्णांक(ep, &info);
	अगर (ret == 0) अणु
		/*
		 * Because it will count port/endpoपूर्णांक अगर it करोesn't have "reg".
		 * But, we can't judge whether it has "no reg", or "reg = <0>"
		 * only of_graph_parse_endpoपूर्णांक().
		 * We need to check "reg" property
		 */
		अगर (of_get_property(ep,   "reg", शून्य))
			वापस info.id;

		node = of_get_parent(ep);
		reg = of_get_property(node, "reg", शून्य);
		of_node_put(node);
		अगर (reg)
			वापस info.port;
	पूर्ण
	node = of_graph_get_port_parent(ep);

	/*
	 * Non HDMI sound हाल, counting port/endpoपूर्णांक on its DT
	 * is enough. Let's count it.
	 */
	i = 0;
	id = -1;
	क्रम_each_endpoपूर्णांक_of_node(node, endpoपूर्णांक) अणु
		अगर (endpoपूर्णांक == ep)
			id = i;
		i++;
	पूर्ण

	of_node_put(node);

	अगर (id < 0)
		वापस -ENODEV;

	वापस id;
पूर्ण

अटल bool soc_component_is_pcm(काष्ठा snd_soc_dai_link_component *dlc)
अणु
	काष्ठा snd_soc_dai *dai = snd_soc_find_dai_with_mutex(dlc);

	अगर (dai && (dai->component->driver->pcm_स्थिरruct ||
		    dai->driver->pcm_new))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक asoc_simple_parse_dai(काष्ठा device_node *ep,
				 काष्ठा snd_soc_dai_link_component *dlc,
				 पूर्णांक *is_single_link)
अणु
	काष्ठा device_node *node;
	काष्ठा of_phandle_args args;
	पूर्णांक ret;

	अगर (!ep)
		वापस 0;

	node = of_graph_get_port_parent(ep);

	/* Get dai->name */
	args.np		= node;
	args.args[0]	= graph_get_dai_id(ep);
	args.args_count	= (of_graph_get_endpoपूर्णांक_count(node) > 1);

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
	ret = snd_soc_get_dai_name(&args, &dlc->dai_name);
	अगर (ret < 0)
		वापस ret;

	dlc->of_node = node;

	अगर (is_single_link)
		*is_single_link = of_graph_get_endpoपूर्णांक_count(node) == 1;

	वापस 0;
पूर्ण

अटल व्योम graph_parse_convert(काष्ठा device *dev,
				काष्ठा device_node *ep,
				काष्ठा asoc_simple_data *adata)
अणु
	काष्ठा device_node *top = dev->of_node;
	काष्ठा device_node *port = of_get_parent(ep);
	काष्ठा device_node *ports = of_get_parent(port);
	काष्ठा device_node *node = of_graph_get_port_parent(ep);

	asoc_simple_parse_convert(top,   शून्य,   adata);
	अगर (of_node_name_eq(ports, "ports"))
		asoc_simple_parse_convert(ports, शून्य, adata);
	asoc_simple_parse_convert(port,  शून्य,   adata);
	asoc_simple_parse_convert(ep,    शून्य,   adata);

	of_node_put(port);
	of_node_put(ports);
	of_node_put(node);
पूर्ण

अटल व्योम graph_parse_mclk_fs(काष्ठा device_node *top,
				काष्ठा device_node *ep,
				काष्ठा simple_dai_props *props)
अणु
	काष्ठा device_node *port	= of_get_parent(ep);
	काष्ठा device_node *ports	= of_get_parent(port);

	of_property_पढ़ो_u32(top,	"mclk-fs", &props->mclk_fs);
	अगर (of_node_name_eq(ports, "ports"))
		of_property_पढ़ो_u32(ports, "mclk-fs", &props->mclk_fs);
	of_property_पढ़ो_u32(port,	"mclk-fs", &props->mclk_fs);
	of_property_पढ़ो_u32(ep,	"mclk-fs", &props->mclk_fs);

	of_node_put(port);
	of_node_put(ports);
पूर्ण

अटल पूर्णांक graph_parse_node(काष्ठा asoc_simple_priv *priv,
			    काष्ठा device_node *ep,
			    काष्ठा link_info *li,
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

	graph_parse_mclk_fs(top, ep, dai_props);

	ret = asoc_simple_parse_dai(ep, dlc, cpu);
	अगर (ret < 0)
		वापस ret;

	ret = asoc_simple_parse_tdm(ep, dai);
	अगर (ret < 0)
		वापस ret;

	ret = asoc_simple_parse_clk(dev, ep, dai, dlc);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक graph_link_init(काष्ठा asoc_simple_priv *priv,
			   काष्ठा device_node *cpu_ep,
			   काष्ठा device_node *codec_ep,
			   काष्ठा link_info *li,
			   अक्षर *name)
अणु
	काष्ठा device *dev = simple_priv_to_dev(priv);
	काष्ठा snd_soc_dai_link *dai_link = simple_priv_to_link(priv, li->link);
	पूर्णांक ret;

	ret = asoc_simple_parse_daअगरmt(dev, cpu_ep, codec_ep,
				       शून्य, &dai_link->dai_fmt);
	अगर (ret < 0)
		वापस ret;

	dai_link->init		= asoc_simple_dai_init;
	dai_link->ops		= &graph_ops;
	अगर (priv->ops)
		dai_link->ops	= priv->ops;

	वापस asoc_simple_set_dailink_name(dev, dai_link, name);
पूर्ण

अटल पूर्णांक graph_dai_link_of_dpcm(काष्ठा asoc_simple_priv *priv,
				  काष्ठा device_node *cpu_ep,
				  काष्ठा device_node *codec_ep,
				  काष्ठा link_info *li)
अणु
	काष्ठा device *dev = simple_priv_to_dev(priv);
	काष्ठा snd_soc_dai_link *dai_link = simple_priv_to_link(priv, li->link);
	काष्ठा simple_dai_props *dai_props = simple_priv_to_props(priv, li->link);
	काष्ठा device_node *top = dev->of_node;
	काष्ठा device_node *ep = li->cpu ? cpu_ep : codec_ep;
	अक्षर dai_name[64];
	पूर्णांक ret;

	dev_dbg(dev, "link_of DPCM (%pOF)\n", ep);

	अगर (li->cpu) अणु
		काष्ठा snd_soc_card *card = simple_priv_to_card(priv);
		काष्ठा snd_soc_dai_link_component *cpus = asoc_link_to_cpu(dai_link, 0);
		पूर्णांक is_single_links = 0;

		/* Codec is dummy */

		/* FE settings */
		dai_link->dynamic		= 1;
		dai_link->dpcm_merged_क्रमmat	= 1;

		ret = graph_parse_node(priv, cpu_ep, li, &is_single_links);
		अगर (ret)
			वापस ret;

		snम_लिखो(dai_name, माप(dai_name),
			 "fe.%pOFP.%s", cpus->of_node, cpus->dai_name);
		/*
		 * In BE<->BE connections it is not required to create
		 * PCM devices at CPU end of the dai link and thus 'no_pcm'
		 * flag needs to be set. It is useful when there are many
		 * BE components and some of these have to be connected to
		 * क्रमm a valid audio path.
		 *
		 * For example: FE <-> BE1 <-> BE2 <-> ... <-> BEn where
		 * there are 'n' BE components in the path.
		 */
		अगर (card->component_chaining && !soc_component_is_pcm(cpus))
			dai_link->no_pcm = 1;

		asoc_simple_canonicalize_cpu(cpus, is_single_links);
	पूर्ण अन्यथा अणु
		काष्ठा snd_soc_codec_conf *cconf = simple_props_to_codec_conf(dai_props, 0);
		काष्ठा snd_soc_dai_link_component *codecs = asoc_link_to_codec(dai_link, 0);
		काष्ठा device_node *port;
		काष्ठा device_node *ports;

		/* CPU is dummy */

		/* BE settings */
		dai_link->no_pcm		= 1;
		dai_link->be_hw_params_fixup	= asoc_simple_be_hw_params_fixup;

		ret = graph_parse_node(priv, codec_ep, li, शून्य);
		अगर (ret < 0)
			वापस ret;

		snम_लिखो(dai_name, माप(dai_name),
			 "be.%pOFP.%s", codecs->of_node, codecs->dai_name);

		/* check "prefix" from top node */
		port = of_get_parent(ep);
		ports = of_get_parent(port);
		snd_soc_of_parse_node_prefix(top, cconf, codecs->of_node,
					      "prefix");
		अगर (of_node_name_eq(ports, "ports"))
			snd_soc_of_parse_node_prefix(ports, cconf, codecs->of_node, "prefix");
		snd_soc_of_parse_node_prefix(port, cconf, codecs->of_node,
					     "prefix");

		of_node_put(ports);
		of_node_put(port);
	पूर्ण

	graph_parse_convert(dev, ep, &dai_props->adata);

	snd_soc_dai_link_set_capabilities(dai_link);

	ret = graph_link_init(priv, cpu_ep, codec_ep, li, dai_name);

	li->link++;

	वापस ret;
पूर्ण

अटल पूर्णांक graph_dai_link_of(काष्ठा asoc_simple_priv *priv,
			     काष्ठा device_node *cpu_ep,
			     काष्ठा device_node *codec_ep,
			     काष्ठा link_info *li)
अणु
	काष्ठा device *dev = simple_priv_to_dev(priv);
	काष्ठा snd_soc_dai_link *dai_link = simple_priv_to_link(priv, li->link);
	काष्ठा snd_soc_dai_link_component *cpus = asoc_link_to_cpu(dai_link, 0);
	काष्ठा snd_soc_dai_link_component *codecs = asoc_link_to_codec(dai_link, 0);
	अक्षर dai_name[64];
	पूर्णांक ret, is_single_links = 0;

	dev_dbg(dev, "link_of (%pOF)\n", cpu_ep);

	ret = graph_parse_node(priv, cpu_ep, li, &is_single_links);
	अगर (ret < 0)
		वापस ret;

	ret = graph_parse_node(priv, codec_ep, li, शून्य);
	अगर (ret < 0)
		वापस ret;

	snम_लिखो(dai_name, माप(dai_name),
		 "%s-%s", cpus->dai_name, codecs->dai_name);

	asoc_simple_canonicalize_cpu(cpus, is_single_links);

	ret = graph_link_init(priv, cpu_ep, codec_ep, li, dai_name);
	अगर (ret < 0)
		वापस ret;

	li->link++;

	वापस 0;
पूर्ण

अटल अंतरभूत bool parse_as_dpcm_link(काष्ठा asoc_simple_priv *priv,
				      काष्ठा device_node *codec_port,
				      काष्ठा asoc_simple_data *adata)
अणु
	अगर (priv->क्रमce_dpcm)
		वापस true;

	अगर (!priv->dpcm_selectable)
		वापस false;

	/*
	 * It is DPCM
	 * अगर Codec port has many endpoपूर्णांकs,
	 * or has convert-xxx property
	 */
	अगर ((of_get_child_count(codec_port) > 1) ||
	    (adata->convert_rate || adata->convert_channels))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक __graph_क्रम_each_link(काष्ठा asoc_simple_priv *priv,
			काष्ठा link_info *li,
			पूर्णांक (*func_noml)(काष्ठा asoc_simple_priv *priv,
					 काष्ठा device_node *cpu_ep,
					 काष्ठा device_node *codec_ep,
					 काष्ठा link_info *li),
			पूर्णांक (*func_dpcm)(काष्ठा asoc_simple_priv *priv,
					 काष्ठा device_node *cpu_ep,
					 काष्ठा device_node *codec_ep,
					 काष्ठा link_info *li))
अणु
	काष्ठा of_phandle_iterator it;
	काष्ठा device *dev = simple_priv_to_dev(priv);
	काष्ठा device_node *node = dev->of_node;
	काष्ठा device_node *cpu_port;
	काष्ठा device_node *cpu_ep;
	काष्ठा device_node *codec_ep;
	काष्ठा device_node *codec_port;
	काष्ठा device_node *codec_port_old = शून्य;
	काष्ठा asoc_simple_data adata;
	पूर्णांक rc, ret = 0;

	/* loop क्रम all listed CPU port */
	of_क्रम_each_phandle(&it, rc, node, "dais", शून्य, 0) अणु
		cpu_port = it.node;
		cpu_ep	 = शून्य;

		/* loop क्रम all CPU endpoपूर्णांक */
		जबतक (1) अणु
			cpu_ep = of_get_next_child(cpu_port, cpu_ep);
			अगर (!cpu_ep)
				अवरोध;

			/* get codec */
			codec_ep = of_graph_get_remote_endpoपूर्णांक(cpu_ep);
			codec_port = of_get_parent(codec_ep);

			/* get convert-xxx property */
			स_रखो(&adata, 0, माप(adata));
			graph_parse_convert(dev, codec_ep, &adata);
			graph_parse_convert(dev, cpu_ep,   &adata);

			/* check अगर link requires DPCM parsing */
			अगर (parse_as_dpcm_link(priv, codec_port, &adata)) अणु
				/*
				 * Codec endpoपूर्णांक can be शून्य क्रम pluggable audio HW.
				 * Platक्रमm DT can populate the Codec endpoपूर्णांक depending on the
				 * plugged HW.
				 */
				/* Do it all CPU endpoपूर्णांक, and 1st Codec endpoपूर्णांक */
				अगर (li->cpu ||
				    ((codec_port_old != codec_port) && codec_ep))
					ret = func_dpcm(priv, cpu_ep, codec_ep, li);
			/* अन्यथा normal sound */
			पूर्ण अन्यथा अणु
				अगर (li->cpu)
					ret = func_noml(priv, cpu_ep, codec_ep, li);
			पूर्ण

			of_node_put(codec_ep);
			of_node_put(codec_port);

			अगर (ret < 0)
				वापस ret;

			codec_port_old = codec_port;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक graph_क्रम_each_link(काष्ठा asoc_simple_priv *priv,
			       काष्ठा link_info *li,
			       पूर्णांक (*func_noml)(काष्ठा asoc_simple_priv *priv,
						काष्ठा device_node *cpu_ep,
						काष्ठा device_node *codec_ep,
						काष्ठा link_info *li),
			       पूर्णांक (*func_dpcm)(काष्ठा asoc_simple_priv *priv,
						काष्ठा device_node *cpu_ep,
						काष्ठा device_node *codec_ep,
						काष्ठा link_info *li))
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
		ret = __graph_क्रम_each_link(priv, li, func_noml, func_dpcm);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक graph_get_dais_count(काष्ठा asoc_simple_priv *priv,
				काष्ठा link_info *li);

पूर्णांक audio_graph_parse_of(काष्ठा asoc_simple_priv *priv, काष्ठा device *dev)
अणु
	काष्ठा snd_soc_card *card = simple_priv_to_card(priv);
	काष्ठा link_info *li;
	पूर्णांक ret;

	li = devm_kzalloc(dev, माप(*li), GFP_KERNEL);
	अगर (!li)
		वापस -ENOMEM;

	card->owner = THIS_MODULE;
	card->dev = dev;

	ret = graph_get_dais_count(priv, li);
	अगर (ret < 0)
		वापस ret;

	अगर (!li->link)
		वापस -EINVAL;

	ret = asoc_simple_init_priv(priv, li);
	अगर (ret < 0)
		वापस ret;

	priv->pa_gpio = devm_gpiod_get_optional(dev, "pa", GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->pa_gpio)) अणु
		ret = PTR_ERR(priv->pa_gpio);
		dev_err(dev, "failed to get amplifier gpio: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = asoc_simple_parse_widमाला_लो(card, शून्य);
	अगर (ret < 0)
		वापस ret;

	ret = asoc_simple_parse_routing(card, शून्य);
	अगर (ret < 0)
		वापस ret;

	स_रखो(li, 0, माप(*li));
	ret = graph_क्रम_each_link(priv, li,
				  graph_dai_link_of,
				  graph_dai_link_of_dpcm);
	अगर (ret < 0)
		जाओ err;

	ret = asoc_simple_parse_card_name(card, शून्य);
	अगर (ret < 0)
		जाओ err;

	snd_soc_card_set_drvdata(card, priv);

	asoc_simple_debug_info(priv);

	ret = devm_snd_soc_रेजिस्टर_card(dev, card);
	अगर (ret < 0)
		जाओ err;

	devm_kमुक्त(dev, li);
	वापस 0;

err:
	asoc_simple_clean_reference(card);

	अगर (ret != -EPROBE_DEFER)
		dev_err(dev, "parse error %d\n", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(audio_graph_parse_of);

अटल पूर्णांक graph_count_noml(काष्ठा asoc_simple_priv *priv,
			    काष्ठा device_node *cpu_ep,
			    काष्ठा device_node *codec_ep,
			    काष्ठा link_info *li)
अणु
	काष्ठा device *dev = simple_priv_to_dev(priv);

	अगर (li->link >= SNDRV_MAX_LINKS) अणु
		dev_err(dev, "too many links\n");
		वापस -EINVAL;
	पूर्ण

	li->num[li->link].cpus		= 1;
	li->num[li->link].codecs	= 1;

	li->link += 1; /* 1xCPU-Codec */

	dev_dbg(dev, "Count As Normal\n");

	वापस 0;
पूर्ण

अटल पूर्णांक graph_count_dpcm(काष्ठा asoc_simple_priv *priv,
			    काष्ठा device_node *cpu_ep,
			    काष्ठा device_node *codec_ep,
			    काष्ठा link_info *li)
अणु
	काष्ठा device *dev = simple_priv_to_dev(priv);

	अगर (li->link >= SNDRV_MAX_LINKS) अणु
		dev_err(dev, "too many links\n");
		वापस -EINVAL;
	पूर्ण

	अगर (li->cpu) अणु
		li->num[li->link].cpus		= 1;

		li->link++; /* 1xCPU-dummy */
	पूर्ण अन्यथा अणु
		li->num[li->link].codecs	= 1;

		li->link++; /* 1xdummy-Codec */
	पूर्ण

	dev_dbg(dev, "Count As DPCM\n");

	वापस 0;
पूर्ण

अटल पूर्णांक graph_get_dais_count(काष्ठा asoc_simple_priv *priv,
				काष्ठा link_info *li)
अणु
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
	वापस graph_क्रम_each_link(priv, li,
				   graph_count_noml,
				   graph_count_dpcm);
पूर्ण

अटल पूर्णांक graph_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा asoc_simple_priv *priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा snd_soc_card *card;

	/* Allocate the निजी data and the DAI link array */
	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	card = simple_priv_to_card(priv);
	card->dapm_widमाला_लो	= graph_dapm_widमाला_लो;
	card->num_dapm_widमाला_लो	= ARRAY_SIZE(graph_dapm_widमाला_लो);
	card->probe		= asoc_graph_card_probe;

	अगर (of_device_get_match_data(dev))
		priv->dpcm_selectable = 1;

	वापस audio_graph_parse_of(priv, dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id graph_of_match[] = अणु
	अणु .compatible = "audio-graph-card", पूर्ण,
	अणु .compatible = "audio-graph-scu-card",
	  .data = (व्योम *)DPCM_SELECTABLE पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, graph_of_match);

अटल काष्ठा platक्रमm_driver graph_card = अणु
	.driver = अणु
		.name = "asoc-audio-graph-card",
		.pm = &snd_soc_pm_ops,
		.of_match_table = graph_of_match,
	पूर्ण,
	.probe = graph_probe,
	.हटाओ = asoc_simple_हटाओ,
पूर्ण;
module_platक्रमm_driver(graph_card);

MODULE_ALIAS("platform:asoc-audio-graph-card");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ASoC Audio Graph Sound Card");
MODULE_AUTHOR("Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>");
