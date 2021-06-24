<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * definitions क्रम PCM179X
 *
 * Copyright 2013 Amarula Solutions
 */

#अगर_अघोषित __PCM179X_H__
#घोषणा __PCM179X_H__

#घोषणा PCM1792A_FORMATS (SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S24_LE | \
			  SNDRV_PCM_FMTBIT_S16_LE)

बाह्य स्थिर काष्ठा regmap_config pcm179x_regmap_config;

पूर्णांक pcm179x_common_init(काष्ठा device *dev, काष्ठा regmap *regmap);

#पूर्ण_अगर
