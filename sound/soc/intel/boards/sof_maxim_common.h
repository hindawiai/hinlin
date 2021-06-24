<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2020 Intel Corporation.
 */

/*
 * This file defines data काष्ठाures used in Machine Driver क्रम Intel
 * platक्रमms with Maxim Codecs.
 */
#अगर_अघोषित __SOF_MAXIM_COMMON_H
#घोषणा __SOF_MAXIM_COMMON_H

#समावेश <sound/soc.h>

#घोषणा MAX_98373_CODEC_DAI	"max98373-aif1"
#घोषणा MAX_98373_DEV0_NAME	"i2c-MX98373:00"
#घोषणा MAX_98373_DEV1_NAME	"i2c-MX98373:01"

बाह्य काष्ठा snd_soc_dai_link_component max_98373_components[2];
बाह्य काष्ठा snd_soc_ops max_98373_ops;
बाह्य स्थिर काष्ठा snd_soc_dapm_route max_98373_dapm_routes[];

पूर्णांक max98373_spk_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd);
व्योम sof_max98373_codec_conf(काष्ठा snd_soc_card *card);
पूर्णांक max98373_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd);

#पूर्ण_अगर /* __SOF_MAXIM_COMMON_H */
