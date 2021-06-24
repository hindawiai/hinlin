<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015, Heiner Kallweit <hkallweit1@gmail.com>
 */

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "leds.h"

DEFINE_LED_TRIGGER(bt_घातer_led_trigger);

काष्ठा hci_basic_led_trigger अणु
	काष्ठा led_trigger	led_trigger;
	काष्ठा hci_dev		*hdev;
पूर्ण;

#घोषणा to_hci_basic_led_trigger(arg) container_of(arg, \
			काष्ठा hci_basic_led_trigger, led_trigger)

व्योम hci_leds_update_घातered(काष्ठा hci_dev *hdev, bool enabled)
अणु
	अगर (hdev->घातer_led)
		led_trigger_event(hdev->घातer_led,
				  enabled ? LED_FULL : LED_OFF);

	अगर (!enabled) अणु
		काष्ठा hci_dev *d;

		पढ़ो_lock(&hci_dev_list_lock);

		list_क्रम_each_entry(d, &hci_dev_list, list) अणु
			अगर (test_bit(HCI_UP, &d->flags))
				enabled = true;
		पूर्ण

		पढ़ो_unlock(&hci_dev_list_lock);
	पूर्ण

	led_trigger_event(bt_घातer_led_trigger, enabled ? LED_FULL : LED_OFF);
पूर्ण

अटल पूर्णांक घातer_activate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा hci_basic_led_trigger *htrig;
	bool घातered;

	htrig = to_hci_basic_led_trigger(led_cdev->trigger);
	घातered = test_bit(HCI_UP, &htrig->hdev->flags);

	led_trigger_event(led_cdev->trigger, घातered ? LED_FULL : LED_OFF);

	वापस 0;
पूर्ण

अटल काष्ठा led_trigger *led_allocate_basic(काष्ठा hci_dev *hdev,
			पूर्णांक (*activate)(काष्ठा led_classdev *led_cdev),
			स्थिर अक्षर *name)
अणु
	काष्ठा hci_basic_led_trigger *htrig;

	htrig =	devm_kzalloc(&hdev->dev, माप(*htrig), GFP_KERNEL);
	अगर (!htrig)
		वापस शून्य;

	htrig->hdev = hdev;
	htrig->led_trigger.activate = activate;
	htrig->led_trigger.name = devm_kaप्र_लिखो(&hdev->dev, GFP_KERNEL,
						 "%s-%s", hdev->name,
						 name);
	अगर (!htrig->led_trigger.name)
		जाओ err_alloc;

	अगर (devm_led_trigger_रेजिस्टर(&hdev->dev, &htrig->led_trigger))
		जाओ err_रेजिस्टर;

	वापस &htrig->led_trigger;

err_रेजिस्टर:
	devm_kमुक्त(&hdev->dev, (व्योम *)htrig->led_trigger.name);
err_alloc:
	devm_kमुक्त(&hdev->dev, htrig);
	वापस शून्य;
पूर्ण

व्योम hci_leds_init(काष्ठा hci_dev *hdev)
अणु
	/* initialize घातer_led */
	hdev->घातer_led = led_allocate_basic(hdev, घातer_activate, "power");
पूर्ण

व्योम bt_leds_init(व्योम)
अणु
	led_trigger_रेजिस्टर_simple("bluetooth-power", &bt_घातer_led_trigger);
पूर्ण

व्योम bt_leds_cleanup(व्योम)
अणु
	led_trigger_unरेजिस्टर_simple(bt_घातer_led_trigger);
पूर्ण
