<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/rt5665.h -- Platक्रमm data क्रम RT5665
 *
 * Copyright 2016 Realtek Microelectronics
 */

#अगर_अघोषित __LINUX_SND_RT5665_H
#घोषणा __LINUX_SND_RT5665_H

क्रमागत rt5665_dmic1_data_pin अणु
	RT5665_DMIC1_शून्य,
	RT5665_DMIC1_DATA_GPIO4,
	RT5665_DMIC1_DATA_IN2N,
पूर्ण;

क्रमागत rt5665_dmic2_data_pin अणु
	RT5665_DMIC2_शून्य,
	RT5665_DMIC2_DATA_GPIO5,
	RT5665_DMIC2_DATA_IN2P,
पूर्ण;

क्रमागत rt5665_jd_src अणु
	RT5665_JD_शून्य,
	RT5665_JD1,
पूर्ण;

काष्ठा rt5665_platक्रमm_data अणु
	bool in1_dअगरf;
	bool in2_dअगरf;
	bool in3_dअगरf;
	bool in4_dअगरf;

	पूर्णांक lकरो1_en; /* GPIO क्रम LDO1_EN */

	क्रमागत rt5665_dmic1_data_pin dmic1_data_pin;
	क्रमागत rt5665_dmic2_data_pin dmic2_data_pin;
	क्रमागत rt5665_jd_src jd_src;

	अचिन्हित पूर्णांक sar_hs_type;
पूर्ण;

#पूर्ण_अगर

