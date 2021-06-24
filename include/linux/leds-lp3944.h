<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * leds-lp3944.h - platक्रमm data काष्ठाure क्रम lp3944 led controller
 *
 * Copyright (C) 2009 Antonio Ospite <ospite@studenti.unina.it>
 */

#अगर_अघोषित __LINUX_LEDS_LP3944_H
#घोषणा __LINUX_LEDS_LP3944_H

#घोषणा LP3944_LED0 0
#घोषणा LP3944_LED1 1
#घोषणा LP3944_LED2 2
#घोषणा LP3944_LED3 3
#घोषणा LP3944_LED4 4
#घोषणा LP3944_LED5 5
#घोषणा LP3944_LED6 6
#घोषणा LP3944_LED7 7
#घोषणा LP3944_LEDS_MAX 8

#घोषणा LP3944_LED_STATUS_MASK	0x03
क्रमागत lp3944_status अणु
	LP3944_LED_STATUS_OFF  = 0x0,
	LP3944_LED_STATUS_ON   = 0x1,
	LP3944_LED_STATUS_DIM0 = 0x2,
	LP3944_LED_STATUS_DIM1 = 0x3
पूर्ण;

क्रमागत lp3944_type अणु
	LP3944_LED_TYPE_NONE,
	LP3944_LED_TYPE_LED,
	LP3944_LED_TYPE_LED_INVERTED,
पूर्ण;

काष्ठा lp3944_led अणु
	अक्षर *name;
	क्रमागत lp3944_type type;
	क्रमागत lp3944_status status;
पूर्ण;

काष्ठा lp3944_platक्रमm_data अणु
	काष्ठा lp3944_led leds[LP3944_LEDS_MAX];
	u8 leds_size;
पूर्ण;

#पूर्ण_अगर /* __LINUX_LEDS_LP3944_H */
