<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
* Simple driver क्रम Texas Instruments LM3630 LED Flash driver chip
* Copyright (C) 2012 Texas Instruments
*/

#अगर_अघोषित __LINUX_LM3639_H
#घोषणा __LINUX_LM3639_H

#घोषणा LM3639_NAME "lm3639_bl"

क्रमागत lm3639_pwm अणु
	LM3639_PWM_DISABLE = 0x00,
	LM3639_PWM_EN_ACTLOW = 0x48,
	LM3639_PWM_EN_ACTHIGH = 0x40,
पूर्ण;

क्रमागत lm3639_strobe अणु
	LM3639_STROBE_DISABLE = 0x00,
	LM3639_STROBE_EN_ACTLOW = 0x10,
	LM3639_STROBE_EN_ACTHIGH = 0x30,
पूर्ण;

क्रमागत lm3639_txpin अणु
	LM3639_TXPIN_DISABLE = 0x00,
	LM3639_TXPIN_EN_ACTLOW = 0x04,
	LM3639_TXPIN_EN_ACTHIGH = 0x0C,
पूर्ण;

क्रमागत lm3639_fleds अणु
	LM3639_FLED_DIASBLE_ALL = 0x00,
	LM3639_FLED_EN_1 = 0x40,
	LM3639_FLED_EN_2 = 0x20,
	LM3639_FLED_EN_ALL = 0x60,
पूर्ण;

क्रमागत lm3639_bleds अणु
	LM3639_BLED_DIASBLE_ALL = 0x00,
	LM3639_BLED_EN_1 = 0x10,
	LM3639_BLED_EN_2 = 0x08,
	LM3639_BLED_EN_ALL = 0x18,
पूर्ण;
क्रमागत lm3639_bled_mode अणु
	LM3639_BLED_MODE_EXPONETIAL = 0x00,
	LM3639_BLED_MODE_LINEAR = 0x10,
पूर्ण;

काष्ठा lm3639_platक्रमm_data अणु
	अचिन्हित पूर्णांक max_brt_led;
	अचिन्हित पूर्णांक init_brt_led;

	/* input pins */
	क्रमागत lm3639_pwm pin_pwm;
	क्रमागत lm3639_strobe pin_strobe;
	क्रमागत lm3639_txpin pin_tx;

	/* output pins */
	क्रमागत lm3639_fleds fled_pins;
	क्रमागत lm3639_bleds bled_pins;
	क्रमागत lm3639_bled_mode bled_mode;

	व्योम (*pwm_set_पूर्णांकensity) (पूर्णांक brightness, पूर्णांक max_brightness);
	पूर्णांक (*pwm_get_पूर्णांकensity) (व्योम);
पूर्ण;
#पूर्ण_अगर /* __LINUX_LM3639_H */
