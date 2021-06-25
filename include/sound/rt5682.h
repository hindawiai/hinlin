<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/rt5682.h -- Platक्रमm data क्रम RT5682
 *
 * Copyright 2018 Realtek Microelectronics
 */

#अगर_अघोषित __LINUX_SND_RT5682_H
#घोषणा __LINUX_SND_RT5682_H

क्रमागत rt5682_dmic1_data_pin अणु
	RT5682_DMIC1_शून्य,
	RT5682_DMIC1_DATA_GPIO2,
	RT5682_DMIC1_DATA_GPIO5,
पूर्ण;

क्रमागत rt5682_dmic1_clk_pin अणु
	RT5682_DMIC1_CLK_GPIO1,
	RT5682_DMIC1_CLK_GPIO3,
पूर्ण;

क्रमागत rt5682_jd_src अणु
	RT5682_JD_शून्य,
	RT5682_JD1,
पूर्ण;

क्रमागत rt5682_dai_clks अणु
	RT5682_DAI_WCLK_IDX,
	RT5682_DAI_BCLK_IDX,
	RT5682_DAI_NUM_CLKS,
पूर्ण;

काष्ठा rt5682_platक्रमm_data अणु

	पूर्णांक lकरो1_en; /* GPIO क्रम LDO1_EN */

	क्रमागत rt5682_dmic1_data_pin dmic1_data_pin;
	क्रमागत rt5682_dmic1_clk_pin dmic1_clk_pin;
	क्रमागत rt5682_jd_src jd_src;
	अचिन्हित पूर्णांक btndet_delay;
	अचिन्हित पूर्णांक dmic_clk_rate;
	अचिन्हित पूर्णांक dmic_delay;
	bool dmic_clk_driving_high;

	स्थिर अक्षर *dai_clk_names[RT5682_DAI_NUM_CLKS];
पूर्ण;

#पूर्ण_अगर

