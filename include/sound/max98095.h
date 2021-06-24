<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Platक्रमm data क्रम MAX98095
 *
 * Copyright 2011 Maxim Integrated Products
 */

#अगर_अघोषित __SOUND_MAX98095_PDATA_H__
#घोषणा __SOUND_MAX98095_PDATA_H__

/* Equalizer filter response configuration */
काष्ठा max98095_eq_cfg अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक rate;
	u16 band1[5];
	u16 band2[5];
	u16 band3[5];
	u16 band4[5];
	u16 band5[5];
पूर्ण;

/* Biquad filter response configuration */
काष्ठा max98095_biquad_cfg अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक rate;
	u16 band1[5];
	u16 band2[5];
पूर्ण;

/* codec platक्रमm data */
काष्ठा max98095_pdata अणु

	/* Equalizers क्रम DAI1 and DAI2 */
	काष्ठा max98095_eq_cfg *eq_cfg;
	अचिन्हित पूर्णांक eq_cfgcnt;

	/* Biquad filter क्रम DAI1 and DAI2 */
	काष्ठा max98095_biquad_cfg *bq_cfg;
	अचिन्हित पूर्णांक bq_cfgcnt;

	/* Analog/digital microphone configuration:
	 * 0 = analog microphone input (normal setting)
	 * 1 = digital microphone input
	 */
	अचिन्हित पूर्णांक digmic_left_mode:1;
	अचिन्हित पूर्णांक digmic_right_mode:1;

	/* Pin5 is the mechanical method of sensing jack insertion
	 * but it is something that might not be supported.
	 * 0 = PIN5 not supported
	 * 1 = PIN5 supported
	 */
	अचिन्हित पूर्णांक jack_detect_pin5en:1;

	/* Slew amount क्रम jack detection. Calculated as 4 * (delay + 1).
	 * Default delay is 24 to get a समय of 100ms.
	 */
	अचिन्हित पूर्णांक jack_detect_delay;
पूर्ण;

#पूर्ण_अगर
