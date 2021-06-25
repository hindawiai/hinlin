<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// simple-card-utils.c
//
// Copyright (c) 2016 Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>

#समावेश <linux/clk.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_graph.h>
#समावेश <sound/jack.h>
#समावेश <sound/simple_card_utils.h>

व्योम asoc_simple_convert_fixup(काष्ठा asoc_simple_data *data,
			       काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_CHANNELS);

	अगर (data->convert_rate)
		rate->min =
		rate->max = data->convert_rate;

	अगर (data->convert_channels)
		channels->min =
		channels->max = data->convert_channels;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_convert_fixup);

व्योम asoc_simple_parse_convert(काष्ठा device_node *np,
			       अक्षर *prefix,
			       काष्ठा asoc_simple_data *data)
अणु
	अक्षर prop[128];

	अगर (!prefix)
		prefix = "";

	/* sampling rate convert */
	snम_लिखो(prop, माप(prop), "%s%s", prefix, "convert-rate");
	of_property_पढ़ो_u32(np, prop, &data->convert_rate);

	/* channels transfer */
	snम_लिखो(prop, माप(prop), "%s%s", prefix, "convert-channels");
	of_property_पढ़ो_u32(np, prop, &data->convert_channels);
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_parse_convert);

पूर्णांक asoc_simple_parse_daअगरmt(काष्ठा device *dev,
			     काष्ठा device_node *node,
			     काष्ठा device_node *codec,
			     अक्षर *prefix,
			     अचिन्हित पूर्णांक *retfmt)
अणु
	काष्ठा device_node *bitclkmaster = शून्य;
	काष्ठा device_node *framemaster = शून्य;
	अचिन्हित पूर्णांक daअगरmt;

	daअगरmt = snd_soc_of_parse_daअगरmt(node, prefix,
					 &bitclkmaster, &framemaster);
	daअगरmt &= ~SND_SOC_DAIFMT_MASTER_MASK;

	अगर (!bitclkmaster && !framemaster) अणु
		/*
		 * No dai-link level and master setting was not found from
		 * sound node level, revert back to legacy DT parsing and
		 * take the settings from codec node.
		 */
		dev_dbg(dev, "Revert to legacy daifmt parsing\n");

		daअगरmt = snd_soc_of_parse_daअगरmt(codec, शून्य, शून्य, शून्य) |
			(daअगरmt & ~SND_SOC_DAIFMT_CLOCK_MASK);
	पूर्ण अन्यथा अणु
		अगर (codec == bitclkmaster)
			daअगरmt |= (codec == framemaster) ?
				SND_SOC_DAIFMT_CBM_CFM : SND_SOC_DAIFMT_CBM_CFS;
		अन्यथा
			daअगरmt |= (codec == framemaster) ?
				SND_SOC_DAIFMT_CBS_CFM : SND_SOC_DAIFMT_CBS_CFS;
	पूर्ण

	of_node_put(bitclkmaster);
	of_node_put(framemaster);

	*retfmt = daअगरmt;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_parse_daअगरmt);

पूर्णांक asoc_simple_set_dailink_name(काष्ठा device *dev,
				 काष्ठा snd_soc_dai_link *dai_link,
				 स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	अक्षर *name = शून्य;
	पूर्णांक ret = -ENOMEM;

	बहु_शुरू(ap, fmt);
	name = devm_kvaप्र_लिखो(dev, GFP_KERNEL, fmt, ap);
	बहु_पूर्ण(ap);

	अगर (name) अणु
		ret = 0;

		dai_link->name		= name;
		dai_link->stream_name	= name;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_set_dailink_name);

पूर्णांक asoc_simple_parse_card_name(काष्ठा snd_soc_card *card,
				अक्षर *prefix)
अणु
	पूर्णांक ret;

	अगर (!prefix)
		prefix = "";

	/* Parse the card name from DT */
	ret = snd_soc_of_parse_card_name(card, "label");
	अगर (ret < 0 || !card->name) अणु
		अक्षर prop[128];

		snम_लिखो(prop, माप(prop), "%sname", prefix);
		ret = snd_soc_of_parse_card_name(card, prop);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (!card->name && card->dai_link)
		card->name = card->dai_link->name;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_parse_card_name);

अटल पूर्णांक asoc_simple_clk_enable(काष्ठा asoc_simple_dai *dai)
अणु
	अगर (dai)
		वापस clk_prepare_enable(dai->clk);

	वापस 0;
पूर्ण

अटल व्योम asoc_simple_clk_disable(काष्ठा asoc_simple_dai *dai)
अणु
	अगर (dai)
		clk_disable_unprepare(dai->clk);
पूर्ण

पूर्णांक asoc_simple_parse_clk(काष्ठा device *dev,
			  काष्ठा device_node *node,
			  काष्ठा asoc_simple_dai *simple_dai,
			  काष्ठा snd_soc_dai_link_component *dlc)
अणु
	काष्ठा clk *clk;
	u32 val;

	/*
	 * Parse dai->sysclk come from "clocks = <&xxx>"
	 * (अगर प्रणाली has common घड़ी)
	 *  or "system-clock-frequency = <xxx>"
	 *  or device's module घड़ी.
	 */
	clk = devm_get_clk_from_child(dev, node, शून्य);
	अगर (!IS_ERR(clk)) अणु
		simple_dai->sysclk = clk_get_rate(clk);

		simple_dai->clk = clk;
	पूर्ण अन्यथा अगर (!of_property_पढ़ो_u32(node, "system-clock-frequency", &val)) अणु
		simple_dai->sysclk = val;
	पूर्ण अन्यथा अणु
		clk = devm_get_clk_from_child(dev, dlc->of_node, शून्य);
		अगर (!IS_ERR(clk))
			simple_dai->sysclk = clk_get_rate(clk);
	पूर्ण

	अगर (of_property_पढ़ो_bool(node, "system-clock-direction-out"))
		simple_dai->clk_direction = SND_SOC_CLOCK_OUT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_parse_clk);

पूर्णांक asoc_simple_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा asoc_simple_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा simple_dai_props *props = simple_priv_to_props(priv, rtd->num);
	काष्ठा asoc_simple_dai *dai;
	पूर्णांक i1, i2, i;
	पूर्णांक ret;

	क्रम_each_prop_dai_cpu(props, i1, dai) अणु
		ret = asoc_simple_clk_enable(dai);
		अगर (ret)
			जाओ cpu_err;
	पूर्ण

	क्रम_each_prop_dai_codec(props, i2, dai) अणु
		ret = asoc_simple_clk_enable(dai);
		अगर (ret)
			जाओ codec_err;
	पूर्ण

	वापस 0;

codec_err:
	क्रम_each_prop_dai_codec(props, i, dai) अणु
		अगर (i >= i2)
			अवरोध;
		asoc_simple_clk_disable(dai);
	पूर्ण
cpu_err:
	क्रम_each_prop_dai_cpu(props, i, dai) अणु
		अगर (i >= i1)
			अवरोध;
		asoc_simple_clk_disable(dai);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_startup);

व्योम asoc_simple_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा asoc_simple_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा simple_dai_props *props = simple_priv_to_props(priv, rtd->num);
	काष्ठा asoc_simple_dai *dai;
	पूर्णांक i;

	अगर (props->mclk_fs) अणु
		snd_soc_dai_set_sysclk(codec_dai, 0, 0, SND_SOC_CLOCK_IN);
		snd_soc_dai_set_sysclk(cpu_dai, 0, 0, SND_SOC_CLOCK_OUT);
	पूर्ण

	क्रम_each_prop_dai_cpu(props, i, dai)
		asoc_simple_clk_disable(dai);
	क्रम_each_prop_dai_codec(props, i, dai)
		asoc_simple_clk_disable(dai);
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_shutकरोwn);

अटल पूर्णांक asoc_simple_set_clk_rate(काष्ठा asoc_simple_dai *simple_dai,
				    अचिन्हित दीर्घ rate)
अणु
	अगर (!simple_dai)
		वापस 0;

	अगर (!simple_dai->clk)
		वापस 0;

	अगर (clk_get_rate(simple_dai->clk) == rate)
		वापस 0;

	वापस clk_set_rate(simple_dai->clk, rate);
पूर्ण

पूर्णांक asoc_simple_hw_params(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा asoc_simple_dai *pdai;
	काष्ठा snd_soc_dai *sdai;
	काष्ठा asoc_simple_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा simple_dai_props *props = simple_priv_to_props(priv, rtd->num);
	अचिन्हित पूर्णांक mclk, mclk_fs = 0;
	पूर्णांक i, ret;

	अगर (props->mclk_fs)
		mclk_fs = props->mclk_fs;

	अगर (mclk_fs) अणु
		mclk = params_rate(params) * mclk_fs;

		क्रम_each_prop_dai_codec(props, i, pdai) अणु
			ret = asoc_simple_set_clk_rate(pdai, mclk);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		क्रम_each_prop_dai_cpu(props, i, pdai) अणु
			ret = asoc_simple_set_clk_rate(pdai, mclk);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		क्रम_each_rtd_codec_dais(rtd, i, sdai) अणु
			ret = snd_soc_dai_set_sysclk(sdai, 0, mclk, SND_SOC_CLOCK_IN);
			अगर (ret && ret != -ENOTSUPP)
				वापस ret;
		पूर्ण
		क्रम_each_rtd_cpu_dais(rtd, i, sdai) अणु
			ret = snd_soc_dai_set_sysclk(sdai, 0, mclk, SND_SOC_CLOCK_OUT);
			अगर (ret && ret != -ENOTSUPP)
				वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_hw_params);

पूर्णांक asoc_simple_be_hw_params_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
				   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा asoc_simple_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा simple_dai_props *dai_props = simple_priv_to_props(priv, rtd->num);

	asoc_simple_convert_fixup(&dai_props->adata, params);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_be_hw_params_fixup);

अटल पूर्णांक asoc_simple_init_dai(काष्ठा snd_soc_dai *dai,
				     काष्ठा asoc_simple_dai *simple_dai)
अणु
	पूर्णांक ret;

	अगर (!simple_dai)
		वापस 0;

	अगर (simple_dai->sysclk) अणु
		ret = snd_soc_dai_set_sysclk(dai, 0, simple_dai->sysclk,
					     simple_dai->clk_direction);
		अगर (ret && ret != -ENOTSUPP) अणु
			dev_err(dai->dev, "simple-card: set_sysclk error\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (simple_dai->slots) अणु
		ret = snd_soc_dai_set_tdm_slot(dai,
					       simple_dai->tx_slot_mask,
					       simple_dai->rx_slot_mask,
					       simple_dai->slots,
					       simple_dai->slot_width);
		अगर (ret && ret != -ENOTSUPP) अणु
			dev_err(dai->dev, "simple-card: set_tdm_slot error\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक asoc_simple_init_dai_link_params(काष्ठा snd_soc_pcm_runसमय *rtd,
					    काष्ठा simple_dai_props *dai_props)
अणु
	काष्ठा snd_soc_dai_link *dai_link = rtd->dai_link;
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_pcm_stream *params;
	काष्ठा snd_pcm_hardware hw;
	पूर्णांक i, ret, stream;

	/* Only codecs should have non_legacy_dai_naming set. */
	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (!component->driver->non_legacy_dai_naming)
			वापस 0;
	पूर्ण

	/* Assumes the capabilities are the same क्रम all supported streams */
	क्रम_each_pcm_streams(stream) अणु
		ret = snd_soc_runसमय_calc_hw(rtd, &hw, stream);
		अगर (ret == 0)
			अवरोध;
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(rtd->dev, "simple-card: no valid dai_link params\n");
		वापस ret;
	पूर्ण

	params = devm_kzalloc(rtd->dev, माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	params->क्रमmats = hw.क्रमmats;
	params->rates = hw.rates;
	params->rate_min = hw.rate_min;
	params->rate_max = hw.rate_max;
	params->channels_min = hw.channels_min;
	params->channels_max = hw.channels_max;

	dai_link->params = params;
	dai_link->num_params = 1;

	वापस 0;
पूर्ण

पूर्णांक asoc_simple_dai_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा asoc_simple_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा simple_dai_props *props = simple_priv_to_props(priv, rtd->num);
	काष्ठा asoc_simple_dai *dai;
	पूर्णांक i, ret;

	क्रम_each_prop_dai_codec(props, i, dai) अणु
		ret = asoc_simple_init_dai(asoc_rtd_to_codec(rtd, i), dai);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	क्रम_each_prop_dai_cpu(props, i, dai) अणु
		ret = asoc_simple_init_dai(asoc_rtd_to_cpu(rtd, i), dai);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = asoc_simple_init_dai_link_params(rtd, props);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_dai_init);

व्योम asoc_simple_canonicalize_platक्रमm(काष्ठा snd_soc_dai_link_component *platक्रमms,
				       काष्ठा snd_soc_dai_link_component *cpus)
अणु
	/* Assumes platक्रमm == cpu */
	अगर (!platक्रमms->of_node)
		platक्रमms->of_node = cpus->of_node;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_canonicalize_platक्रमm);

व्योम asoc_simple_canonicalize_cpu(काष्ठा snd_soc_dai_link_component *cpus,
				  पूर्णांक is_single_links)
अणु
	/*
	 * In soc_bind_dai_link() will check cpu name after
	 * of_node matching अगर dai_link has cpu_dai_name.
	 * but, it will never match अगर name was created by
	 * fmt_single_name() हटाओ cpu_dai_name अगर cpu_args
	 * was 0. See:
	 *	fmt_single_name()
	 *	fmt_multiple_name()
	 */
	अगर (is_single_links)
		cpus->dai_name = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_canonicalize_cpu);

पूर्णांक asoc_simple_clean_reference(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dai_link *dai_link;
	काष्ठा snd_soc_dai_link_component *cpu;
	काष्ठा snd_soc_dai_link_component *codec;
	पूर्णांक i, j;

	क्रम_each_card_prelinks(card, i, dai_link) अणु
		क्रम_each_link_cpus(dai_link, j, cpu)
			of_node_put(cpu->of_node);
		क्रम_each_link_codecs(dai_link, j, codec)
			of_node_put(codec->of_node);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_clean_reference);

पूर्णांक asoc_simple_parse_routing(काष्ठा snd_soc_card *card,
			      अक्षर *prefix)
अणु
	काष्ठा device_node *node = card->dev->of_node;
	अक्षर prop[128];

	अगर (!prefix)
		prefix = "";

	snम_लिखो(prop, माप(prop), "%s%s", prefix, "routing");

	अगर (!of_property_पढ़ो_bool(node, prop))
		वापस 0;

	वापस snd_soc_of_parse_audio_routing(card, prop);
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_parse_routing);

पूर्णांक asoc_simple_parse_widमाला_लो(काष्ठा snd_soc_card *card,
			      अक्षर *prefix)
अणु
	काष्ठा device_node *node = card->dev->of_node;
	अक्षर prop[128];

	अगर (!prefix)
		prefix = "";

	snम_लिखो(prop, माप(prop), "%s%s", prefix, "widgets");

	अगर (of_property_पढ़ो_bool(node, prop))
		वापस snd_soc_of_parse_audio_simple_widमाला_लो(card, prop);

	/* no widमाला_लो is not error */
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_parse_widमाला_लो);

पूर्णांक asoc_simple_parse_pin_चयनes(काष्ठा snd_soc_card *card,
				   अक्षर *prefix)
अणु
	स्थिर अचिन्हित पूर्णांक nb_controls_max = 16;
	स्थिर अक्षर **strings, *control_name;
	काष्ठा snd_kcontrol_new *controls;
	काष्ठा device *dev = card->dev;
	अचिन्हित पूर्णांक i, nb_controls;
	अक्षर prop[128];
	पूर्णांक ret;

	अगर (!prefix)
		prefix = "";

	snम_लिखो(prop, माप(prop), "%s%s", prefix, "pin-switches");

	अगर (!of_property_पढ़ो_bool(dev->of_node, prop))
		वापस 0;

	strings = devm_kसुस्मृति(dev, nb_controls_max,
			       माप(*strings), GFP_KERNEL);
	अगर (!strings)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_string_array(dev->of_node, prop,
					    strings, nb_controls_max);
	अगर (ret < 0)
		वापस ret;

	nb_controls = (अचिन्हित पूर्णांक)ret;

	controls = devm_kसुस्मृति(dev, nb_controls,
				माप(*controls), GFP_KERNEL);
	अगर (!controls)
		वापस -ENOMEM;

	क्रम (i = 0; i < nb_controls; i++) अणु
		control_name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
					      "%s Switch", strings[i]);
		अगर (!control_name)
			वापस -ENOMEM;

		controls[i].अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
		controls[i].name = control_name;
		controls[i].info = snd_soc_dapm_info_pin_चयन;
		controls[i].get = snd_soc_dapm_get_pin_चयन;
		controls[i].put = snd_soc_dapm_put_pin_चयन;
		controls[i].निजी_value = (अचिन्हित दीर्घ)strings[i];
	पूर्ण

	card->controls = controls;
	card->num_controls = nb_controls;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_parse_pin_चयनes);

पूर्णांक asoc_simple_init_jack(काष्ठा snd_soc_card *card,
			  काष्ठा asoc_simple_jack *sjack,
			  पूर्णांक is_hp, अक्षर *prefix,
			  अक्षर *pin)
अणु
	काष्ठा device *dev = card->dev;
	क्रमागत of_gpio_flags flags;
	अक्षर prop[128];
	अक्षर *pin_name;
	अक्षर *gpio_name;
	पूर्णांक mask;
	पूर्णांक det;

	अगर (!prefix)
		prefix = "";

	sjack->gpio.gpio = -ENOENT;

	अगर (is_hp) अणु
		snम_लिखो(prop, माप(prop), "%shp-det-gpio", prefix);
		pin_name	= pin ? pin : "Headphones";
		gpio_name	= "Headphone detection";
		mask		= SND_JACK_HEADPHONE;
	पूर्ण अन्यथा अणु
		snम_लिखो(prop, माप(prop), "%smic-det-gpio", prefix);
		pin_name	= pin ? pin : "Mic Jack";
		gpio_name	= "Mic detection";
		mask		= SND_JACK_MICROPHONE;
	पूर्ण

	det = of_get_named_gpio_flags(dev->of_node, prop, 0, &flags);
	अगर (det == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	अगर (gpio_is_valid(det)) अणु
		sjack->pin.pin		= pin_name;
		sjack->pin.mask		= mask;

		sjack->gpio.name	= gpio_name;
		sjack->gpio.report	= mask;
		sjack->gpio.gpio	= det;
		sjack->gpio.invert	= !!(flags & OF_GPIO_ACTIVE_LOW);
		sjack->gpio.debounce_समय = 150;

		snd_soc_card_jack_new(card, pin_name, mask,
				      &sjack->jack,
				      &sjack->pin, 1);

		snd_soc_jack_add_gpios(&sjack->jack, 1,
				       &sjack->gpio);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_init_jack);

पूर्णांक asoc_simple_init_priv(काष्ठा asoc_simple_priv *priv,
			  काष्ठा link_info *li)
अणु
	काष्ठा snd_soc_card *card = simple_priv_to_card(priv);
	काष्ठा device *dev = simple_priv_to_dev(priv);
	काष्ठा snd_soc_dai_link *dai_link;
	काष्ठा simple_dai_props *dai_props;
	काष्ठा asoc_simple_dai *dais;
	काष्ठा snd_soc_dai_link_component *dlcs;
	काष्ठा snd_soc_codec_conf *cconf = शून्य;
	पूर्णांक i, dai_num = 0, dlc_num = 0, cnf_num = 0;

	dai_props = devm_kसुस्मृति(dev, li->link, माप(*dai_props), GFP_KERNEL);
	dai_link  = devm_kसुस्मृति(dev, li->link, माप(*dai_link),  GFP_KERNEL);
	अगर (!dai_props || !dai_link)
		वापस -ENOMEM;

	/*
	 * dais (= CPU+Codec)
	 * dlcs (= CPU+Codec+Platक्रमm)
	 */
	क्रम (i = 0; i < li->link; i++) अणु
		पूर्णांक cc = li->num[i].cpus + li->num[i].codecs;

		dai_num += cc;
		dlc_num += cc + li->num[i].platक्रमms;

		अगर (!li->num[i].cpus)
			cnf_num += li->num[i].codecs;
	पूर्ण

	dais = devm_kसुस्मृति(dev, dai_num, माप(*dais),      GFP_KERNEL);
	dlcs = devm_kसुस्मृति(dev, dlc_num, माप(*dai_props), GFP_KERNEL);
	अगर (!dais || !dlcs)
		वापस -ENOMEM;

	अगर (cnf_num) अणु
		cconf = devm_kसुस्मृति(dev, cnf_num, माप(*cconf), GFP_KERNEL);
		अगर (!cconf)
			वापस -ENOMEM;
	पूर्ण

	dev_dbg(dev, "link %d, dais %d, ccnf %d\n",
		li->link, dai_num, cnf_num);

	/* dummy CPU/Codec */
	priv->dummy.of_node	= शून्य;
	priv->dummy.dai_name	= "snd-soc-dummy-dai";
	priv->dummy.name	= "snd-soc-dummy";

	priv->dai_props		= dai_props;
	priv->dai_link		= dai_link;
	priv->dais		= dais;
	priv->dlcs		= dlcs;
	priv->codec_conf	= cconf;

	card->dai_link		= priv->dai_link;
	card->num_links		= li->link;
	card->codec_conf	= cconf;
	card->num_configs	= cnf_num;

	क्रम (i = 0; i < li->link; i++) अणु
		अगर (li->num[i].cpus) अणु
			/* Normal CPU */
			dai_props[i].cpus	=
			dai_link[i].cpus	= dlcs;
			dai_props[i].num.cpus	=
			dai_link[i].num_cpus	= li->num[i].cpus;
			dai_props[i].cpu_dai	= dais;

			dlcs += li->num[i].cpus;
			dais += li->num[i].cpus;
		पूर्ण अन्यथा अणु
			/* DPCM Be's CPU = dummy */
			dai_props[i].cpus	=
			dai_link[i].cpus	= &priv->dummy;
			dai_props[i].num.cpus	=
			dai_link[i].num_cpus	= 1;
		पूर्ण

		अगर (li->num[i].codecs) अणु
			/* Normal Codec */
			dai_props[i].codecs	=
			dai_link[i].codecs	= dlcs;
			dai_props[i].num.codecs	=
			dai_link[i].num_codecs	= li->num[i].codecs;
			dai_props[i].codec_dai	= dais;

			dlcs += li->num[i].codecs;
			dais += li->num[i].codecs;

			अगर (!li->num[i].cpus) अणु
				/* DPCM Be's Codec */
				dai_props[i].codec_conf = cconf;
				cconf += li->num[i].codecs;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* DPCM Fe's Codec = dummy */
			dai_props[i].codecs	=
			dai_link[i].codecs	= &priv->dummy;
			dai_props[i].num.codecs	=
			dai_link[i].num_codecs	= 1;
		पूर्ण

		अगर (li->num[i].platक्रमms) अणु
			/* Have Platक्रमm */
			dai_props[i].platक्रमms		=
			dai_link[i].platक्रमms		= dlcs;
			dai_props[i].num.platक्रमms	=
			dai_link[i].num_platक्रमms	= li->num[i].platक्रमms;

			dlcs += li->num[i].platक्रमms;
		पूर्ण अन्यथा अणु
			/* Doesn't have Platक्रमm */
			dai_props[i].platक्रमms		=
			dai_link[i].platक्रमms		= शून्य;
			dai_props[i].num.platक्रमms	=
			dai_link[i].num_platक्रमms	= 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_init_priv);

पूर्णांक asoc_simple_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);

	वापस asoc_simple_clean_reference(card);
पूर्ण
EXPORT_SYMBOL_GPL(asoc_simple_हटाओ);

पूर्णांक asoc_graph_card_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा asoc_simple_priv *priv = snd_soc_card_get_drvdata(card);
	पूर्णांक ret;

	ret = asoc_simple_init_hp(card, &priv->hp_jack, शून्य);
	अगर (ret < 0)
		वापस ret;

	ret = asoc_simple_init_mic(card, &priv->mic_jack, शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_graph_card_probe);

/* Module inक्रमmation */
MODULE_AUTHOR("Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>");
MODULE_DESCRIPTION("ALSA SoC Simple Card Utils");
MODULE_LICENSE("GPL v2");
