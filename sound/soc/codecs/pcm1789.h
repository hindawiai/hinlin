<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Definitions क्रम PCM1789 audio driver
// Copyright (C) 2018 Bootlin
// Mylथउne Josseअक्रम <mylene.josseअक्रम@bootlin.com>

#अगर_अघोषित __PCM1789_H__
#घोषणा __PCM1789_H__

#घोषणा PCM1789_FORMATS (SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S24_LE | \
			 SNDRV_PCM_FMTBIT_S16_LE)

बाह्य स्थिर काष्ठा regmap_config pcm1789_regmap_config;

पूर्णांक pcm1789_common_init(काष्ठा device *dev, काष्ठा regmap *regmap);
पूर्णांक pcm1789_common_निकास(काष्ठा device *dev);

#पूर्ण_अगर
