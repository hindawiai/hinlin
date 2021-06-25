<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * simple_card_utils.h
 *
 * Copyright (c) 2016 Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */

#अगर_अघोषित __SIMPLE_CARD_UTILS_H
#घोषणा __SIMPLE_CARD_UTILS_H

#समावेश <linux/clk.h>
#समावेश <sound/soc.h>

#घोषणा asoc_simple_init_hp(card, sjack, prefix) \
	asoc_simple_init_jack(card, sjack, 1, prefix, शून्य)
#घोषणा asoc_simple_init_mic(card, sjack, prefix) \
	asoc_simple_init_jack(card, sjack, 0, prefix, शून्य)

काष्ठा asoc_simple_dai अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक sysclk;
	पूर्णांक clk_direction;
	पूर्णांक slots;
	पूर्णांक slot_width;
	अचिन्हित पूर्णांक tx_slot_mask;
	अचिन्हित पूर्णांक rx_slot_mask;
	काष्ठा clk *clk;
पूर्ण;

काष्ठा asoc_simple_data अणु
	u32 convert_rate;
	u32 convert_channels;
पूर्ण;

काष्ठा asoc_simple_jack अणु
	काष्ठा snd_soc_jack jack;
	काष्ठा snd_soc_jack_pin pin;
	काष्ठा snd_soc_jack_gpio gpio;
पूर्ण;

काष्ठा prop_nums अणु
	पूर्णांक cpus;
	पूर्णांक codecs;
	पूर्णांक platक्रमms;
पूर्ण;

काष्ठा asoc_simple_priv अणु
	काष्ठा snd_soc_card snd_card;
	काष्ठा simple_dai_props अणु
		काष्ठा asoc_simple_dai *cpu_dai;
		काष्ठा asoc_simple_dai *codec_dai;
		काष्ठा snd_soc_dai_link_component *cpus;
		काष्ठा snd_soc_dai_link_component *codecs;
		काष्ठा snd_soc_dai_link_component *platक्रमms;
		काष्ठा asoc_simple_data adata;
		काष्ठा snd_soc_codec_conf *codec_conf;
		काष्ठा prop_nums num;
		अचिन्हित पूर्णांक mclk_fs;
	पूर्ण *dai_props;
	काष्ठा asoc_simple_jack hp_jack;
	काष्ठा asoc_simple_jack mic_jack;
	काष्ठा snd_soc_dai_link *dai_link;
	काष्ठा asoc_simple_dai *dais;
	काष्ठा snd_soc_dai_link_component *dlcs;
	काष्ठा snd_soc_dai_link_component dummy;
	काष्ठा snd_soc_codec_conf *codec_conf;
	काष्ठा gpio_desc *pa_gpio;
	स्थिर काष्ठा snd_soc_ops *ops;
	अचिन्हित पूर्णांक dpcm_selectable:1;
	अचिन्हित पूर्णांक क्रमce_dpcm:1;
पूर्ण;
#घोषणा simple_priv_to_card(priv)	(&(priv)->snd_card)
#घोषणा simple_priv_to_props(priv, i)	((priv)->dai_props + (i))
#घोषणा simple_priv_to_dev(priv)	(simple_priv_to_card(priv)->dev)
#घोषणा simple_priv_to_link(priv, i)	(simple_priv_to_card(priv)->dai_link + (i))

#घोषणा simple_props_to_dlc_cpu(props, i)	((props)->cpus + i)
#घोषणा simple_props_to_dlc_codec(props, i)	((props)->codecs + i)
#घोषणा simple_props_to_dlc_platक्रमm(props, i)	((props)->platक्रमms + i)

#घोषणा simple_props_to_dai_cpu(props, i)	((props)->cpu_dai + i)
#घोषणा simple_props_to_dai_codec(props, i)	((props)->codec_dai + i)
#घोषणा simple_props_to_codec_conf(props, i)	((props)->codec_conf + i)

#घोषणा क्रम_each_prop_dlc_cpus(props, i, cpu)				\
	क्रम ((i) = 0;							\
	     ((i) < (props)->num.cpus) &&				\
		     ((cpu) = simple_props_to_dlc_cpu(props, i));	\
	     (i)++)
#घोषणा क्रम_each_prop_dlc_codecs(props, i, codec)			\
	क्रम ((i) = 0;							\
	     ((i) < (props)->num.codecs) &&				\
		     ((codec) = simple_props_to_dlc_codec(props, i));	\
	     (i)++)
#घोषणा क्रम_each_prop_dlc_platक्रमms(props, i, platक्रमm)			\
	क्रम ((i) = 0;							\
	     ((i) < (props)->num.platक्रमms) &&				\
		     ((platक्रमm) = simple_props_to_dlc_platक्रमm(props, i)); \
	     (i)++)
#घोषणा क्रम_each_prop_codec_conf(props, i, conf)			\
	क्रम ((i) = 0;							\
	     ((i) < (props)->num.codecs) &&				\
		     (props)->codec_conf &&				\
		     ((conf) = simple_props_to_codec_conf(props, i));	\
	     (i)++)

#घोषणा क्रम_each_prop_dai_cpu(props, i, cpu)				\
	क्रम ((i) = 0;							\
	     ((i) < (props)->num.cpus) &&				\
		     ((cpu) = simple_props_to_dai_cpu(props, i));	\
	     (i)++)
#घोषणा क्रम_each_prop_dai_codec(props, i, codec)			\
	क्रम ((i) = 0;							\
	     ((i) < (props)->num.codecs) &&				\
		     ((codec) = simple_props_to_dai_codec(props, i));	\
	     (i)++)

#घोषणा SNDRV_MAX_LINKS 128

काष्ठा link_info अणु
	पूर्णांक link; /* number of link */
	पूर्णांक cpu;  /* turn क्रम CPU / Codec */
	काष्ठा prop_nums num[SNDRV_MAX_LINKS];
पूर्ण;

पूर्णांक asoc_simple_parse_daअगरmt(काष्ठा device *dev,
			     काष्ठा device_node *node,
			     काष्ठा device_node *codec,
			     अक्षर *prefix,
			     अचिन्हित पूर्णांक *retfmt);
__म_लिखो(3, 4)
पूर्णांक asoc_simple_set_dailink_name(काष्ठा device *dev,
				 काष्ठा snd_soc_dai_link *dai_link,
				 स्थिर अक्षर *fmt, ...);
पूर्णांक asoc_simple_parse_card_name(काष्ठा snd_soc_card *card,
				अक्षर *prefix);

पूर्णांक asoc_simple_parse_clk(काष्ठा device *dev,
			  काष्ठा device_node *node,
			  काष्ठा asoc_simple_dai *simple_dai,
			  काष्ठा snd_soc_dai_link_component *dlc);
पूर्णांक asoc_simple_startup(काष्ठा snd_pcm_substream *substream);
व्योम asoc_simple_shutकरोwn(काष्ठा snd_pcm_substream *substream);
पूर्णांक asoc_simple_hw_params(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_pcm_hw_params *params);
पूर्णांक asoc_simple_dai_init(काष्ठा snd_soc_pcm_runसमय *rtd);
पूर्णांक asoc_simple_be_hw_params_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
				   काष्ठा snd_pcm_hw_params *params);

#घोषणा asoc_simple_parse_tdm(np, dai)			\
	snd_soc_of_parse_tdm_slot(np,	&(dai)->tx_slot_mask,	\
					&(dai)->rx_slot_mask,	\
					&(dai)->slots,		\
					&(dai)->slot_width);

व्योम asoc_simple_canonicalize_platक्रमm(काष्ठा snd_soc_dai_link_component *platक्रमms,
				       काष्ठा snd_soc_dai_link_component *cpus);
व्योम asoc_simple_canonicalize_cpu(काष्ठा snd_soc_dai_link_component *cpus,
				  पूर्णांक is_single_links);

पूर्णांक asoc_simple_clean_reference(काष्ठा snd_soc_card *card);

व्योम asoc_simple_convert_fixup(काष्ठा asoc_simple_data *data,
				      काष्ठा snd_pcm_hw_params *params);
व्योम asoc_simple_parse_convert(काष्ठा device_node *np, अक्षर *prefix,
			       काष्ठा asoc_simple_data *data);

पूर्णांक asoc_simple_parse_routing(काष्ठा snd_soc_card *card,
				      अक्षर *prefix);
पूर्णांक asoc_simple_parse_widमाला_लो(काष्ठा snd_soc_card *card,
				      अक्षर *prefix);
पूर्णांक asoc_simple_parse_pin_चयनes(काष्ठा snd_soc_card *card,
				   अक्षर *prefix);

पूर्णांक asoc_simple_init_jack(काष्ठा snd_soc_card *card,
			       काष्ठा asoc_simple_jack *sjack,
			       पूर्णांक is_hp, अक्षर *prefix, अक्षर *pin);
पूर्णांक asoc_simple_init_priv(काष्ठा asoc_simple_priv *priv,
			       काष्ठा link_info *li);
पूर्णांक asoc_simple_हटाओ(काष्ठा platक्रमm_device *pdev);

पूर्णांक asoc_graph_card_probe(काष्ठा snd_soc_card *card);

#अगर_घोषित DEBUG
अटल अंतरभूत व्योम asoc_simple_debug_dai(काष्ठा asoc_simple_priv *priv,
					 अक्षर *name,
					 काष्ठा asoc_simple_dai *dai)
अणु
	काष्ठा device *dev = simple_priv_to_dev(priv);

	/* dai might be शून्य */
	अगर (!dai)
		वापस;

	अगर (dai->name)
		dev_dbg(dev, "%s dai name = %s\n",
			name, dai->name);

	अगर (dai->slots)
		dev_dbg(dev, "%s slots = %d\n", name, dai->slots);
	अगर (dai->slot_width)
		dev_dbg(dev, "%s slot width = %d\n", name, dai->slot_width);
	अगर (dai->tx_slot_mask)
		dev_dbg(dev, "%s tx slot mask = %d\n", name, dai->tx_slot_mask);
	अगर (dai->rx_slot_mask)
		dev_dbg(dev, "%s rx slot mask = %d\n", name, dai->rx_slot_mask);
	अगर (dai->clk)
		dev_dbg(dev, "%s clk %luHz\n", name, clk_get_rate(dai->clk));
	अगर (dai->sysclk)
		dev_dbg(dev, "%s sysclk = %dHz\n",
			name, dai->sysclk);
	अगर (dai->clk || dai->sysclk)
		dev_dbg(dev, "%s direction = %s\n",
			name, dai->clk_direction ? "OUT" : "IN");
पूर्ण

अटल अंतरभूत व्योम asoc_simple_debug_info(काष्ठा asoc_simple_priv *priv)
अणु
	काष्ठा snd_soc_card *card = simple_priv_to_card(priv);
	काष्ठा device *dev = simple_priv_to_dev(priv);

	पूर्णांक i;

	अगर (card->name)
		dev_dbg(dev, "Card Name: %s\n", card->name);

	क्रम (i = 0; i < card->num_links; i++) अणु
		काष्ठा simple_dai_props *props = simple_priv_to_props(priv, i);
		काष्ठा snd_soc_dai_link *link = simple_priv_to_link(priv, i);
		काष्ठा asoc_simple_dai *dai;
		काष्ठा snd_soc_codec_conf *cnf;
		पूर्णांक j;

		dev_dbg(dev, "DAI%d\n", i);

		dev_dbg(dev, "cpu num = %d\n", link->num_cpus);
		क्रम_each_prop_dai_cpu(props, j, dai)
			asoc_simple_debug_dai(priv, "cpu", dai);
		dev_dbg(dev, "codec num = %d\n", link->num_codecs);
		क्रम_each_prop_dai_codec(props, j, dai)
			asoc_simple_debug_dai(priv, "codec", dai);

		अगर (link->name)
			dev_dbg(dev, "dai name = %s\n", link->name);
		अगर (link->dai_fmt)
			dev_dbg(dev, "dai format = %04x\n", link->dai_fmt);
		अगर (props->adata.convert_rate)
			dev_dbg(dev, "convert_rate = %d\n", props->adata.convert_rate);
		अगर (props->adata.convert_channels)
			dev_dbg(dev, "convert_channels = %d\n", props->adata.convert_channels);
		क्रम_each_prop_codec_conf(props, j, cnf)
			अगर (cnf->name_prefix)
				dev_dbg(dev, "name prefix = %s\n", cnf->name_prefix);
		अगर (props->mclk_fs)
			dev_dbg(dev, "mclk-fs = %d\n", props->mclk_fs);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा  asoc_simple_debug_info(priv)
#पूर्ण_अगर /* DEBUG */

#पूर्ण_अगर /* __SIMPLE_CARD_UTILS_H */
