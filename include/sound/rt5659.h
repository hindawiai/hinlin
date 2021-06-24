<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/rt5659.h -- Platक्रमm data क्रम RT5659
 *
 * Copyright 2013 Realtek Microelectronics
 */

#अगर_अघोषित __LINUX_SND_RT5659_H
#घोषणा __LINUX_SND_RT5659_H

क्रमागत rt5659_dmic1_data_pin अणु
	RT5659_DMIC1_शून्य,
	RT5659_DMIC1_DATA_IN2N,
	RT5659_DMIC1_DATA_GPIO5,
	RT5659_DMIC1_DATA_GPIO9,
	RT5659_DMIC1_DATA_GPIO11,
पूर्ण;

क्रमागत rt5659_dmic2_data_pin अणु
	RT5659_DMIC2_शून्य,
	RT5659_DMIC2_DATA_IN2P,
	RT5659_DMIC2_DATA_GPIO6,
	RT5659_DMIC2_DATA_GPIO10,
	RT5659_DMIC2_DATA_GPIO12,
पूर्ण;

क्रमागत rt5659_jd_src अणु
	RT5659_JD_शून्य,
	RT5659_JD3,
	RT5659_JD_HDA_HEADER,
पूर्ण;

काष्ठा rt5659_platक्रमm_data अणु
	bool in1_dअगरf;
	bool in3_dअगरf;
	bool in4_dअगरf;

	पूर्णांक lकरो1_en; /* GPIO क्रम LDO1_EN */
	पूर्णांक reset; /* GPIO क्रम RESET */

	क्रमागत rt5659_dmic1_data_pin dmic1_data_pin;
	क्रमागत rt5659_dmic2_data_pin dmic2_data_pin;
	क्रमागत rt5659_jd_src jd_src;
पूर्ण;

#पूर्ण_अगर

