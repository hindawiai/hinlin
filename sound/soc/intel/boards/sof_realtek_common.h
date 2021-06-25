<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2020 Intel Corporation.
 */

/*
 * This file defines data काष्ठाures used in Machine Driver क्रम Intel
 * platक्रमms with Realtek Codecs.
 */
#अगर_अघोषित __SOF_REALTEK_COMMON_H
#घोषणा __SOF_REALTEK_COMMON_H

#समावेश <sound/soc.h>

#घोषणा RT1011_CODEC_DAI	"rt1011-aif"
#घोषणा RT1011_DEV0_NAME	"i2c-10EC1011:00"
#घोषणा RT1011_DEV1_NAME	"i2c-10EC1011:01"
#घोषणा RT1011_DEV2_NAME	"i2c-10EC1011:02"
#घोषणा RT1011_DEV3_NAME	"i2c-10EC1011:03"

व्योम sof_rt1011_dai_link(काष्ठा snd_soc_dai_link *link);
व्योम sof_rt1011_codec_conf(काष्ठा snd_soc_card *card);

#घोषणा RT1015P_CODEC_DAI	"HiFi"
#घोषणा RT1015P_DEV0_NAME	"RTL1015:00"
#घोषणा RT1015P_DEV1_NAME	"RTL1015:01"

व्योम sof_rt1015p_dai_link(काष्ठा snd_soc_dai_link *link);
व्योम sof_rt1015p_codec_conf(काष्ठा snd_soc_card *card);

#पूर्ण_अगर /* __SOF_REALTEK_COMMON_H */
