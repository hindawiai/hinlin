<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/rt5660.h -- Platक्रमm data क्रम RT5660
 *
 * Copyright 2016 Realtek Semiconductor Corp.
 * Author: Oder Chiou <oder_chiou@realtek.com>
 */

#अगर_अघोषित __LINUX_SND_RT5660_H
#घोषणा __LINUX_SND_RT5660_H

क्रमागत rt5660_dmic1_data_pin अणु
	RT5660_DMIC1_शून्य,
	RT5660_DMIC1_DATA_GPIO2,
	RT5660_DMIC1_DATA_IN1P,
पूर्ण;

काष्ठा rt5660_platक्रमm_data अणु
	/* IN1 & IN3 can optionally be dअगरferential */
	bool in1_dअगरf;
	bool in3_dअगरf;
	bool use_lकरो2;
	bool घातeroff_codec_in_suspend;

	क्रमागत rt5660_dmic1_data_pin dmic1_data_pin;
पूर्ण;

#पूर्ण_अगर
