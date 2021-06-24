<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43legacy_LEDS_H_
#घोषणा B43legacy_LEDS_H_

काष्ठा b43legacy_wldev;

#अगर_घोषित CONFIG_B43LEGACY_LEDS

#समावेश <linux/types.h>
#समावेश <linux/leds.h>


#घोषणा B43legacy_LED_MAX_NAME_LEN	31

काष्ठा b43legacy_led अणु
	काष्ठा b43legacy_wldev *dev;
	/* The LED class device */
	काष्ठा led_classdev led_dev;
	/* The index number of the LED. */
	u8 index;
	/* If activelow is true, the LED is ON अगर the
	 * bit is चयनed off. */
	bool activelow;
	/* The unique name string क्रम this LED device. */
	अक्षर name[B43legacy_LED_MAX_NAME_LEN + 1];
पूर्ण;

#घोषणा B43legacy_LED_BEHAVIOUR		0x7F
#घोषणा B43legacy_LED_ACTIVELOW		0x80
/* LED behaviour values */
क्रमागत b43legacy_led_behaviour अणु
	B43legacy_LED_OFF,
	B43legacy_LED_ON,
	B43legacy_LED_ACTIVITY,
	B43legacy_LED_RADIO_ALL,
	B43legacy_LED_RADIO_A,
	B43legacy_LED_RADIO_B,
	B43legacy_LED_MODE_BG,
	B43legacy_LED_TRANSFER,
	B43legacy_LED_APTRANSFER,
	B43legacy_LED_WEIRD,
	B43legacy_LED_ASSOC,
	B43legacy_LED_INACTIVE,
पूर्ण;

व्योम b43legacy_leds_init(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_leds_निकास(काष्ठा b43legacy_wldev *dev);

#अन्यथा /* CONFIG_B43LEGACY_LEDS */
/* LED support disabled */

काष्ठा b43legacy_led अणु
	/* empty */
पूर्ण;

अटल अंतरभूत व्योम b43legacy_leds_init(काष्ठा b43legacy_wldev *dev)
अणु
पूर्ण
अटल अंतरभूत व्योम b43legacy_leds_निकास(काष्ठा b43legacy_wldev *dev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_B43LEGACY_LEDS */

#पूर्ण_अगर /* B43legacy_LEDS_H_ */
