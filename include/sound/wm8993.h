<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/wm8993.h -- Platक्रमm data क्रम WM8993
 *
 * Copyright 2009 Wolfson Microelectronics. PLC.
 */

#अगर_अघोषित __LINUX_SND_WM8993_H
#घोषणा __LINUX_SND_WM8993_H

/* Note that EQ1 only contains the enable/disable bit so will be
   ignored but is included क्रम simplicity.
 */
काष्ठा wm8993_retune_mobile_setting अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक rate;
	u16 config[24];
पूर्ण;

काष्ठा wm8993_platक्रमm_data अणु
	काष्ठा wm8993_retune_mobile_setting *retune_configs;
	पूर्णांक num_retune_configs;

	/* LINEOUT can be dअगरferential or single ended */
	अचिन्हित पूर्णांक lineout1_dअगरf:1;
	अचिन्हित पूर्णांक lineout2_dअगरf:1;

	/* Common mode feedback */
	अचिन्हित पूर्णांक lineout1fb:1;
	अचिन्हित पूर्णांक lineout2fb:1;

	/* Delay to add क्रम microphones to stabalise after घातer up */
	पूर्णांक micbias1_delay;
	पूर्णांक micbias2_delay;

	/* Microphone biases: 0=0.9*AVDD1 1=0.65*AVVD1 */
	अचिन्हित पूर्णांक micbias1_lvl:1;
	अचिन्हित पूर्णांक micbias2_lvl:1;

	/* Jack detect threshold levels, see datasheet क्रम values */
	अचिन्हित पूर्णांक jd_scthr:2;
	अचिन्हित पूर्णांक jd_thr:2;
पूर्ण;

#पूर्ण_अगर
