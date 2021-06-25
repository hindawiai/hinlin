<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/rt5668.h -- Platक्रमm data क्रम RT5668
 *
 * Copyright 2018 Realtek Microelectronics
 */

#अगर_अघोषित __LINUX_SND_RT5668_H
#घोषणा __LINUX_SND_RT5668_H

क्रमागत rt5668_dmic1_data_pin अणु
	RT5668_DMIC1_शून्य,
	RT5668_DMIC1_DATA_GPIO2,
	RT5668_DMIC1_DATA_GPIO5,
पूर्ण;

क्रमागत rt5668_dmic1_clk_pin अणु
	RT5668_DMIC1_CLK_GPIO1,
	RT5668_DMIC1_CLK_GPIO3,
पूर्ण;

क्रमागत rt5668_jd_src अणु
	RT5668_JD_शून्य,
	RT5668_JD1,
पूर्ण;

काष्ठा rt5668_platक्रमm_data अणु

	पूर्णांक lकरो1_en; /* GPIO क्रम LDO1_EN */

	क्रमागत rt5668_dmic1_data_pin dmic1_data_pin;
	क्रमागत rt5668_dmic1_clk_pin dmic1_clk_pin;
	क्रमागत rt5668_jd_src jd_src;
पूर्ण;

#पूर्ण_अगर

