<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * leds-regulator.h - platक्रमm data काष्ठाure क्रम regulator driven LEDs.
 *
 * Copyright (C) 2009 Antonio Ospite <ospite@studenti.unina.it>
 */

#अगर_अघोषित __LINUX_LEDS_REGULATOR_H
#घोषणा __LINUX_LEDS_REGULATOR_H

/*
 * Use "vled" as supply id when declaring the regulator consumer:
 *
 * अटल काष्ठा regulator_consumer_supply pcap_regulator_VVIB_consumers [] = अणु
 * 	अणु .dev_name = "leds-regulator.0", .supply = "vled" पूर्ण,
 * पूर्ण;
 *
 * If you have several regulator driven LEDs, you can append a numerical id to
 * .dev_name as करोne above, and use the same id when declaring the platक्रमm
 * device:
 *
 * अटल काष्ठा led_regulator_platक्रमm_data a780_vibrator_data = अणु
 * 	.name   = "a780::vibrator",
 * पूर्ण;
 *
 * अटल काष्ठा platक्रमm_device a780_vibrator = अणु
 * 	.name = "leds-regulator",
 * 	.id   = 0,
 * 	.dev  = अणु
 * 		.platक्रमm_data = &a780_vibrator_data,
 * 	पूर्ण,
 * पूर्ण;
 */

#समावेश <linux/leds.h>

काष्ठा led_regulator_platक्रमm_data अणु
	अक्षर *name;                     /* LED name as expected by LED class */
	क्रमागत led_brightness brightness; /* initial brightness value */
पूर्ण;

#पूर्ण_अगर /* __LINUX_LEDS_REGULATOR_H */
