<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * soc-link.h
 *
 * Copyright (C) 2019 Renesas Electronics Corp.
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#अगर_अघोषित __SOC_LINK_H
#घोषणा __SOC_LINK_H

पूर्णांक snd_soc_link_init(काष्ठा snd_soc_pcm_runसमय *rtd);
व्योम snd_soc_link_निकास(काष्ठा snd_soc_pcm_runसमय *rtd);
पूर्णांक snd_soc_link_be_hw_params_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
				    काष्ठा snd_pcm_hw_params *params);

पूर्णांक snd_soc_link_startup(काष्ठा snd_pcm_substream *substream);
व्योम snd_soc_link_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			   पूर्णांक rollback);
पूर्णांक snd_soc_link_prepare(काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_soc_link_hw_params(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_pcm_hw_params *params);
व्योम snd_soc_link_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			  पूर्णांक rollback);

पूर्णांक snd_soc_link_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			 पूर्णांक rollback);
पूर्णांक snd_soc_link_compr_startup(काष्ठा snd_compr_stream *cstream);
व्योम snd_soc_link_compr_shutकरोwn(काष्ठा snd_compr_stream *cstream,
				 पूर्णांक rollback);
पूर्णांक snd_soc_link_compr_set_params(काष्ठा snd_compr_stream *cstream);

#पूर्ण_अगर /* __SOC_LINK_H */
