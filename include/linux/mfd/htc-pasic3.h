<शैली गुरु>
/*
 * HTC PASIC3 driver - LEDs and DS1WM
 *
 * Copyright (c) 2007 Philipp Zabel <philipp.zabel@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 */

#अगर_अघोषित __PASIC3_H
#घोषणा __PASIC3_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>

बाह्य व्योम pasic3_ग_लिखो_रेजिस्टर(काष्ठा device *dev, u32 reg, u8 val);
बाह्य u8 pasic3_पढ़ो_रेजिस्टर(काष्ठा device *dev, u32 reg);

/*
 * mask क्रम रेजिस्टरs 0x20,0x21,0x22
 */
#घोषणा PASIC3_MASK_LED0 0x04
#घोषणा PASIC3_MASK_LED1 0x08
#घोषणा PASIC3_MASK_LED2 0x40

/*
 * bits in रेजिस्टर 0x06
 */
#घोषणा PASIC3_BIT2_LED0 0x08
#घोषणा PASIC3_BIT2_LED1 0x10
#घोषणा PASIC3_BIT2_LED2 0x20

काष्ठा pasic3_led अणु
	काष्ठा led_classdev         led;
	अचिन्हित पूर्णांक                hw_num;
	अचिन्हित पूर्णांक                bit2;
	अचिन्हित पूर्णांक                mask;
	काष्ठा pasic3_leds_machinfo *pdata;
पूर्ण;

काष्ठा pasic3_leds_machinfo अणु
	अचिन्हित पूर्णांक      num_leds;
	अचिन्हित पूर्णांक      घातer_gpio;
	काष्ठा pasic3_led *leds;
पूर्ण;

काष्ठा pasic3_platक्रमm_data अणु
	काष्ठा pasic3_leds_machinfo *led_pdata;
	अचिन्हित पूर्णांक                 घड़ी_rate;
पूर्ण;

#पूर्ण_अगर
