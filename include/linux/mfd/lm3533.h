<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * lm3533.h -- LM3533 पूर्णांकerface
 *
 * Copyright (C) 2011-2012 Texas Instruments
 *
 * Author: Johan Hovold <jhovold@gmail.com>
 */

#अगर_अघोषित __LINUX_MFD_LM3533_H
#घोषणा __LINUX_MFD_LM3533_H

#घोषणा LM3533_ATTR_RO(_name) \
	DEVICE_ATTR(_name, S_IRUGO, show_##_name, शून्य)
#घोषणा LM3533_ATTR_RW(_name) \
	DEVICE_ATTR(_name, S_IRUGO | S_IWUSR , show_##_name, store_##_name)

काष्ठा device;
काष्ठा regmap;

काष्ठा lm3533 अणु
	काष्ठा device *dev;

	काष्ठा regmap *regmap;

	पूर्णांक gpio_hwen;
	पूर्णांक irq;

	अचिन्हित have_als:1;
	अचिन्हित have_backlights:1;
	अचिन्हित have_leds:1;
पूर्ण;

काष्ठा lm3533_ctrlbank अणु
	काष्ठा lm3533 *lm3533;
	काष्ठा device *dev;
	पूर्णांक id;
पूर्ण;

काष्ठा lm3533_als_platक्रमm_data अणु
	अचिन्हित pwm_mode:1;		/* PWM input mode (शेष analog) */
	u8 r_select;			/* 1 - 127 (ignored in PWM-mode) */
पूर्ण;

काष्ठा lm3533_bl_platक्रमm_data अणु
	अक्षर *name;
	u16 max_current;		/* 5000 - 29800 uA (800 uA step) */
	u8 शेष_brightness;		/* 0 - 255 */
	u8 pwm;				/* 0 - 0x3f */
पूर्ण;

काष्ठा lm3533_led_platक्रमm_data अणु
	अक्षर *name;
	स्थिर अक्षर *शेष_trigger;
	u16 max_current;		/* 5000 - 29800 uA (800 uA step) */
	u8 pwm;				/* 0 - 0x3f */
पूर्ण;

क्रमागत lm3533_boost_freq अणु
	LM3533_BOOST_FREQ_500KHZ,
	LM3533_BOOST_FREQ_1000KHZ,
पूर्ण;

क्रमागत lm3533_boost_ovp अणु
	LM3533_BOOST_OVP_16V,
	LM3533_BOOST_OVP_24V,
	LM3533_BOOST_OVP_32V,
	LM3533_BOOST_OVP_40V,
पूर्ण;

काष्ठा lm3533_platक्रमm_data अणु
	पूर्णांक gpio_hwen;

	क्रमागत lm3533_boost_ovp boost_ovp;
	क्रमागत lm3533_boost_freq boost_freq;

	काष्ठा lm3533_als_platक्रमm_data *als;

	काष्ठा lm3533_bl_platक्रमm_data *backlights;
	पूर्णांक num_backlights;

	काष्ठा lm3533_led_platक्रमm_data *leds;
	पूर्णांक num_leds;
पूर्ण;

बाह्य पूर्णांक lm3533_ctrlbank_enable(काष्ठा lm3533_ctrlbank *cb);
बाह्य पूर्णांक lm3533_ctrlbank_disable(काष्ठा lm3533_ctrlbank *cb);

बाह्य पूर्णांक lm3533_ctrlbank_set_brightness(काष्ठा lm3533_ctrlbank *cb, u8 val);
बाह्य पूर्णांक lm3533_ctrlbank_get_brightness(काष्ठा lm3533_ctrlbank *cb, u8 *val);
बाह्य पूर्णांक lm3533_ctrlbank_set_max_current(काष्ठा lm3533_ctrlbank *cb,
								u16 imax);
बाह्य पूर्णांक lm3533_ctrlbank_set_pwm(काष्ठा lm3533_ctrlbank *cb, u8 val);
बाह्य पूर्णांक lm3533_ctrlbank_get_pwm(काष्ठा lm3533_ctrlbank *cb, u8 *val);

बाह्य पूर्णांक lm3533_पढ़ो(काष्ठा lm3533 *lm3533, u8 reg, u8 *val);
बाह्य पूर्णांक lm3533_ग_लिखो(काष्ठा lm3533 *lm3533, u8 reg, u8 val);
बाह्य पूर्णांक lm3533_update(काष्ठा lm3533 *lm3533, u8 reg, u8 val, u8 mask);

#पूर्ण_अगर	/* __LINUX_MFD_LM3533_H */
