<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_LEDS_H_
#घोषणा B43_LEDS_H_

काष्ठा b43_wl;
काष्ठा b43_wldev;

#अगर_घोषित CONFIG_B43_LEDS

#समावेश <linux/types.h>
#समावेश <linux/leds.h>
#समावेश <linux/workqueue.h>


#घोषणा B43_LED_MAX_NAME_LEN	31

काष्ठा b43_led अणु
	काष्ठा b43_wl *wl;
	/* The LED class device */
	काष्ठा led_classdev led_dev;
	/* The index number of the LED. */
	u8 index;
	/* If activelow is true, the LED is ON अगर the
	 * bit is चयनed off. */
	bool activelow;
	/* The unique name string क्रम this LED device. */
	अक्षर name[B43_LED_MAX_NAME_LEN + 1];
	/* The current status of the LED. This is updated locklessly. */
	atomic_t state;
	/* The active state in hardware. */
	bool hw_state;
पूर्ण;

काष्ठा b43_leds अणु
	काष्ठा b43_led led_tx;
	काष्ठा b43_led led_rx;
	काष्ठा b43_led led_radio;
	काष्ठा b43_led led_assoc;

	bool stop;
	काष्ठा work_काष्ठा work;
पूर्ण;

#घोषणा B43_MAX_NR_LEDS			4

#घोषणा B43_LED_BEHAVIOUR		0x7F
#घोषणा B43_LED_ACTIVELOW		0x80
/* LED behaviour values */
क्रमागत b43_led_behaviour अणु
	B43_LED_OFF,
	B43_LED_ON,
	B43_LED_ACTIVITY,
	B43_LED_RADIO_ALL,
	B43_LED_RADIO_A,
	B43_LED_RADIO_B,
	B43_LED_MODE_BG,
	B43_LED_TRANSFER,
	B43_LED_APTRANSFER,
	B43_LED_WEIRD,		//FIXME
	B43_LED_ASSOC,
	B43_LED_INACTIVE,
पूर्ण;

व्योम b43_leds_रेजिस्टर(काष्ठा b43_wldev *dev);
व्योम b43_leds_unरेजिस्टर(काष्ठा b43_wl *wl);
व्योम b43_leds_init(काष्ठा b43_wldev *dev);
व्योम b43_leds_निकास(काष्ठा b43_wldev *dev);
व्योम b43_leds_stop(काष्ठा b43_wldev *dev);


#अन्यथा /* CONFIG_B43_LEDS */
/* LED support disabled */

काष्ठा b43_leds अणु
	/* empty */
पूर्ण;

अटल अंतरभूत व्योम b43_leds_रेजिस्टर(काष्ठा b43_wldev *dev)
अणु
पूर्ण
अटल अंतरभूत व्योम b43_leds_unरेजिस्टर(काष्ठा b43_wl *wl)
अणु
पूर्ण
अटल अंतरभूत व्योम b43_leds_init(काष्ठा b43_wldev *dev)
अणु
पूर्ण
अटल अंतरभूत व्योम b43_leds_निकास(काष्ठा b43_wldev *dev)
अणु
पूर्ण
अटल अंतरभूत व्योम b43_leds_stop(काष्ठा b43_wldev *dev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_B43_LEDS */

#पूर्ण_अगर /* B43_LEDS_H_ */
