<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * max77693.h - Driver क्रम the Maxim 77693
 *
 *  Copyright (C) 2012 Samsung Electrnoics
 *  SangYoung Son <hello.son@samsung.com>
 *
 * This program is not provided / owned by Maxim Integrated Products.
 *
 * This driver is based on max8997.h
 *
 * MAX77693 has PMIC, Charger, Flash LED, Haptic, MUIC devices.
 * The devices share the same I2C bus and included in
 * this mfd driver.
 */

#अगर_अघोषित __LINUX_MFD_MAX77693_H
#घोषणा __LINUX_MFD_MAX77693_H

/* MAX77693 regulator IDs */
क्रमागत max77693_regulators अणु
	MAX77693_ESAFEOUT1 = 0,
	MAX77693_ESAFEOUT2,
	MAX77693_CHARGER,
	MAX77693_REG_MAX,
पूर्ण;

काष्ठा max77693_reg_data अणु
	u8 addr;
	u8 data;
पूर्ण;

काष्ठा max77693_muic_platक्रमm_data अणु
	काष्ठा max77693_reg_data *init_data;
	पूर्णांक num_init_data;

	पूर्णांक detcable_delay_ms;

	/*
	 * Default usb/uart path whether UART/USB or AUX_UART/AUX_USB
	 * h/w path of COMP2/COMN1 on CONTROL1 रेजिस्टर.
	 */
	पूर्णांक path_usb;
	पूर्णांक path_uart;
पूर्ण;

/* MAX77693 led flash */

/* triggers */
क्रमागत max77693_led_trigger अणु
	MAX77693_LED_TRIG_OFF,
	MAX77693_LED_TRIG_FLASH,
	MAX77693_LED_TRIG_TORCH,
	MAX77693_LED_TRIG_EXT,
	MAX77693_LED_TRIG_SOFT,
पूर्ण;

/* trigger types */
क्रमागत max77693_led_trigger_type अणु
	MAX77693_LED_TRIG_TYPE_EDGE,
	MAX77693_LED_TRIG_TYPE_LEVEL,
पूर्ण;

/* boost modes */
क्रमागत max77693_led_boost_mode अणु
	MAX77693_LED_BOOST_NONE,
	MAX77693_LED_BOOST_ADAPTIVE,
	MAX77693_LED_BOOST_FIXED,
पूर्ण;

/* MAX77693 */

काष्ठा max77693_platक्रमm_data अणु
	/* muic data */
	काष्ठा max77693_muic_platक्रमm_data *muic_data;
	काष्ठा max77693_led_platक्रमm_data *led_data;
पूर्ण;
#पूर्ण_अगर	/* __LINUX_MFD_MAX77693_H */
