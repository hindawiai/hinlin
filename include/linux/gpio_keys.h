<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _GPIO_KEYS_H
#घोषणा _GPIO_KEYS_H

#समावेश <linux/types.h>

काष्ठा device;

/**
 * काष्ठा gpio_keys_button - configuration parameters
 * @code:		input event code (KEY_*, SW_*)
 * @gpio:		%-1 अगर this key करोes not support gpio
 * @active_low:		%true indicates that button is considered
 *			depressed when gpio is low
 * @desc:		label that will be attached to button's gpio
 * @type:		input event type (%EV_KEY, %EV_SW, %EV_ABS)
 * @wakeup:		configure the button as a wake-up source
 * @wakeup_event_action:	event action to trigger wakeup
 * @debounce_पूर्णांकerval:	debounce ticks पूर्णांकerval in msecs
 * @can_disable:	%true indicates that userspace is allowed to
 *			disable button via sysfs
 * @value:		axis value क्रम %EV_ABS
 * @irq:		Irq number in हाल of पूर्णांकerrupt keys
 */
काष्ठा gpio_keys_button अणु
	अचिन्हित पूर्णांक code;
	पूर्णांक gpio;
	पूर्णांक active_low;
	स्थिर अक्षर *desc;
	अचिन्हित पूर्णांक type;
	पूर्णांक wakeup;
	पूर्णांक wakeup_event_action;
	पूर्णांक debounce_पूर्णांकerval;
	bool can_disable;
	पूर्णांक value;
	अचिन्हित पूर्णांक irq;
पूर्ण;

/**
 * काष्ठा gpio_keys_platक्रमm_data - platक्रमm data क्रम gpio_keys driver
 * @buttons:		poपूर्णांकer to array of &gpio_keys_button काष्ठाures
 *			describing buttons attached to the device
 * @nbuttons:		number of elements in @buttons array
 * @poll_पूर्णांकerval:	polling पूर्णांकerval in msecs - क्रम polling driver only
 * @rep:		enable input subप्रणाली स्वतः repeat
 * @enable:		platक्रमm hook क्रम enabling the device
 * @disable:		platक्रमm hook क्रम disabling the device
 * @name:		input device name
 */
काष्ठा gpio_keys_platक्रमm_data अणु
	स्थिर काष्ठा gpio_keys_button *buttons;
	पूर्णांक nbuttons;
	अचिन्हित पूर्णांक poll_पूर्णांकerval;
	अचिन्हित पूर्णांक rep:1;
	पूर्णांक (*enable)(काष्ठा device *dev);
	व्योम (*disable)(काष्ठा device *dev);
	स्थिर अक्षर *name;
पूर्ण;

#पूर्ण_अगर
