<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Definitions क्रम RTL8187 leds
 *
 * Copyright 2009 Larry Finger <Larry.Finger@lwfinger.net>
 *
 * Based on the LED handling in the r8187 driver, which is:
 * Copyright (c) Realtek Semiconductor Corp. All rights reserved.
 */

#अगर_अघोषित RTL8187_LED_H
#घोषणा RTL8187_LED_H

#अगर_घोषित CONFIG_RTL8187_LEDS

#घोषणा RTL8187_LED_MAX_NAME_LEN	21

#समावेश <linux/leds.h>
#समावेश <linux/types.h>

क्रमागत अणु
	LED_PIN_LED0,
	LED_PIN_LED1,
	LED_PIN_GPIO0,
	LED_PIN_HW
पूर्ण;

क्रमागत अणु
	EEPROM_CID_RSVD0 = 0x00,
	EEPROM_CID_RSVD1 = 0xFF,
	EEPROM_CID_ALPHA0 = 0x01,
	EEPROM_CID_SERCOMM_PS = 0x02,
	EEPROM_CID_HW = 0x03,
	EEPROM_CID_TOSHIBA = 0x04,
	EEPROM_CID_QMI = 0x07,
	EEPROM_CID_DELL = 0x08
पूर्ण;

काष्ठा rtl8187_led अणु
	काष्ठा ieee80211_hw *dev;
	/* The LED class device */
	काष्ठा led_classdev led_dev;
	/* The pin/method used to control the led */
	u8 ledpin;
	/* The unique name string क्रम this LED device. */
	अक्षर name[RTL8187_LED_MAX_NAME_LEN + 1];
	/* If the LED is radio or tx/rx */
	bool is_radio;
पूर्ण;

व्योम rtl8187_leds_init(काष्ठा ieee80211_hw *dev, u16 code);
व्योम rtl8187_leds_निकास(काष्ठा ieee80211_hw *dev);

#पूर्ण_अगर /* def CONFIG_RTL8187_LEDS */

#पूर्ण_अगर /* RTL8187_LED_H */
