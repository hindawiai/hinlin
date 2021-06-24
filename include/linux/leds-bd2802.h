<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * leds-bd2802.h - RGB LED Driver
 *
 * Copyright (C) 2009 Samsung Electronics
 * Kim Kyuwon <q1.kim@samsung.com>
 *
 * Datasheet: http://www.rohm.com/products/databook/driver/pdf/bd2802gu-e.pdf
 */
#अगर_अघोषित _LEDS_BD2802_H_
#घोषणा _LEDS_BD2802_H_

काष्ठा bd2802_led_platक्रमm_dataअणु
	u8	rgb_समय;
पूर्ण;

#घोषणा RGB_TIME(slopeकरोwn, slopeup, waveक्रमm) \
	((slopeकरोwn) << 6 | (slopeup) << 4 | (waveक्रमm))

#पूर्ण_अगर /* _LEDS_BD2802_H_ */

