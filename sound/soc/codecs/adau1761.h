<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ADAU1361/ADAU1461/ADAU1761/ADAU1961 driver
 *
 * Copyright 2014 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#अगर_अघोषित __SOUND_SOC_CODECS_ADAU1761_H__
#घोषणा __SOUND_SOC_CODECS_ADAU1761_H__

#समावेश <linux/regmap.h>
#समावेश "adau17x1.h"

काष्ठा device;

पूर्णांक adau1761_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
	क्रमागत adau17x1_type type, व्योम (*चयन_mode)(काष्ठा device *dev));

बाह्य स्थिर काष्ठा regmap_config adau1761_regmap_config;

#पूर्ण_अगर
