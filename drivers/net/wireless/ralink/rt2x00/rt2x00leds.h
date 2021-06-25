<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00lib
	Abstract: rt2x00 led dataकाष्ठाures and routines
 */

#अगर_अघोषित RT2X00LEDS_H
#घोषणा RT2X00LEDS_H

क्रमागत led_type अणु
	LED_TYPE_RADIO,
	LED_TYPE_ASSOC,
	LED_TYPE_ACTIVITY,
	LED_TYPE_QUALITY,
पूर्ण;

काष्ठा rt2x00_led अणु
	काष्ठा rt2x00_dev *rt2x00dev;
	काष्ठा led_classdev led_dev;

	क्रमागत led_type type;
	अचिन्हित पूर्णांक flags;
#घोषणा LED_INITIALIZED		( 1 << 0 )
#घोषणा LED_REGISTERED		( 1 << 1 )
पूर्ण;

#पूर्ण_अगर /* RT2X00LEDS_H */
