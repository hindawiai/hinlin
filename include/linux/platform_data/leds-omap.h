<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2006 Samsung Electronics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 */
#अगर_अघोषित ASMARM_ARCH_LED_H
#घोषणा ASMARM_ARCH_LED_H

काष्ठा omap_led_config अणु
	काष्ठा led_classdev	cdev;
	s16			gpio;
पूर्ण;

काष्ठा omap_led_platक्रमm_data अणु
	s16			nr_leds;
	काष्ठा omap_led_config	*leds;
पूर्ण;

#पूर्ण_अगर
