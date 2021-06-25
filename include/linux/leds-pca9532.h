<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * pca9532.h - platक्रमm data काष्ठाure क्रम pca9532 led controller
 *
 * Copyright (C) 2008 Riku Voipio <riku.voipio@movial.fi>
 *
 * Datasheet: http://www.nxp.com/acrobat/datasheets/PCA9532_3.pdf
 */

#अगर_अघोषित __LINUX_PCA9532_H
#घोषणा __LINUX_PCA9532_H

#समावेश <linux/leds.h>
#समावेश <linux/workqueue.h>
#समावेश <dt-bindings/leds/leds-pca9532.h>

क्रमागत pca9532_state अणु
	PCA9532_OFF  = 0x0,
	PCA9532_ON   = 0x1,
	PCA9532_PWM0 = 0x2,
	PCA9532_PWM1 = 0x3,
	PCA9532_KEEP = 0xff,
पूर्ण;

काष्ठा pca9532_led अणु
	u8 id;
	काष्ठा i2c_client *client;
	स्थिर अक्षर *name;
	स्थिर अक्षर *शेष_trigger;
	काष्ठा led_classdev ldev;
	काष्ठा work_काष्ठा work;
	u32 type;
	क्रमागत pca9532_state state;
पूर्ण;

काष्ठा pca9532_platक्रमm_data अणु
	काष्ठा pca9532_led leds[16];
	u8 pwm[2];
	u8 psc[2];
	पूर्णांक gpio_base;
पूर्ण;

#पूर्ण_अगर /* __LINUX_PCA9532_H */
