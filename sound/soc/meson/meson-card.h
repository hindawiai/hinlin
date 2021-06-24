<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2020 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#अगर_अघोषित _MESON_SND_CARD_H
#घोषणा _MESON_SND_CARD_H

काष्ठा device_node;
काष्ठा platक्रमm_device;

काष्ठा snd_soc_card;
काष्ठा snd_pcm_substream;
काष्ठा snd_pcm_hw_params;

#घोषणा DT_PREFIX "amlogic,"

काष्ठा meson_card_match_data अणु
	पूर्णांक (*add_link)(काष्ठा snd_soc_card *card,
			काष्ठा device_node *node,
			पूर्णांक *index);
पूर्ण;

काष्ठा meson_card अणु
	स्थिर काष्ठा meson_card_match_data *match_data;
	काष्ठा snd_soc_card card;
	व्योम **link_data;
पूर्ण;

अचिन्हित पूर्णांक meson_card_parse_daअगरmt(काष्ठा device_node *node,
				     काष्ठा device_node *cpu_node);

पूर्णांक meson_card_i2s_set_sysclk(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params,
			      अचिन्हित पूर्णांक mclk_fs);

पूर्णांक meson_card_पुनः_स्मृतिate_links(काष्ठा snd_soc_card *card,
				अचिन्हित पूर्णांक num_links);
पूर्णांक meson_card_parse_dai(काष्ठा snd_soc_card *card,
			 काष्ठा device_node *node,
			 काष्ठा device_node **dai_of_node,
			 स्थिर अक्षर **dai_name);
पूर्णांक meson_card_set_be_link(काष्ठा snd_soc_card *card,
			   काष्ठा snd_soc_dai_link *link,
			   काष्ठा device_node *node);
पूर्णांक meson_card_set_fe_link(काष्ठा snd_soc_card *card,
			   काष्ठा snd_soc_dai_link *link,
			   काष्ठा device_node *node,
			   bool is_playback);

पूर्णांक meson_card_probe(काष्ठा platक्रमm_device *pdev);
पूर्णांक meson_card_हटाओ(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर /* _MESON_SND_CARD_H */
