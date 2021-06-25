<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright (c) 2018 Baylibre SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#अगर_अघोषित _MESON_CODEC_GLUE_H
#घोषणा _MESON_CODEC_GLUE_H

#समावेश <sound/soc.h>

काष्ठा meson_codec_glue_input अणु
	काष्ठा snd_soc_pcm_stream params;
	अचिन्हित पूर्णांक fmt;
पूर्ण;

/* Input helpers */
काष्ठा meson_codec_glue_input *
meson_codec_glue_input_get_data(काष्ठा snd_soc_dai *dai);
पूर्णांक meson_codec_glue_input_hw_params(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_hw_params *params,
				     काष्ठा snd_soc_dai *dai);
पूर्णांक meson_codec_glue_input_set_fmt(काष्ठा snd_soc_dai *dai,
				   अचिन्हित पूर्णांक fmt);
पूर्णांक meson_codec_glue_input_dai_probe(काष्ठा snd_soc_dai *dai);
पूर्णांक meson_codec_glue_input_dai_हटाओ(काष्ठा snd_soc_dai *dai);

/* Output helpers */
पूर्णांक meson_codec_glue_output_startup(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_soc_dai *dai);

#पूर्ण_अगर /* _MESON_CODEC_GLUE_H */
