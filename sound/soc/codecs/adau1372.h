<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ADAU1372 driver
 *
 * Copyright 2016 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#अगर_अघोषित SOUND_SOC_CODECS_ADAU1372_H
#घोषणा SOUND_SOC_CODECS_ADAU1372_H

#समावेश <linux/regmap.h>

काष्ठा device;

पूर्णांक adau1372_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		   व्योम (*चयन_mode)(काष्ठा device *dev));

बाह्य स्थिर काष्ठा regmap_config adau1372_regmap_config;

#पूर्ण_अगर
