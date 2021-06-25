<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ADAU1977/ADAU1978/ADAU1979 driver
 *
 * Copyright 2014 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#अगर_अघोषित __SOUND_SOC_CODECS_ADAU1977_H__
#घोषणा __SOUND_SOC_CODECS_ADAU1977_H__

#समावेश <linux/regmap.h>

काष्ठा device;

क्रमागत adau1977_type अणु
	ADAU1977,
	ADAU1978,
	ADAU1979,
पूर्ण;

पूर्णांक adau1977_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
	क्रमागत adau1977_type type, व्योम (*चयन_mode)(काष्ठा device *dev));

बाह्य स्थिर काष्ठा regmap_config adau1977_regmap_config;

क्रमागत adau1977_clk_id अणु
	ADAU1977_SYSCLK,
पूर्ण;

क्रमागत adau1977_sysclk_src अणु
	ADAU1977_SYSCLK_SRC_MCLK,
	ADAU1977_SYSCLK_SRC_LRCLK,
पूर्ण;

#पूर्ण_अगर
