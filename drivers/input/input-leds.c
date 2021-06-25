<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED support क्रम the input layer
 *
 * Copyright 2010-2015 Samuel Thibault <samuel.thibault@ens-lyon.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/leds.h>
#समावेश <linux/input.h>

#अगर IS_ENABLED(CONFIG_VT)
#घोषणा VT_TRIGGER(_name)	.trigger = _name
#अन्यथा
#घोषणा VT_TRIGGER(_name)	.trigger = शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *trigger;
पूर्ण input_led_info[LED_CNT] = अणु
	[LED_NUML]	= अणु "numlock", VT_TRIGGER("kbd-numlock") पूर्ण,
	[LED_CAPSL]	= अणु "capslock", VT_TRIGGER("kbd-capslock") पूर्ण,
	[LED_SCROLLL]	= अणु "scrolllock", VT_TRIGGER("kbd-scrolllock") पूर्ण,
	[LED_COMPOSE]	= अणु "compose" पूर्ण,
	[LED_KANA]	= अणु "kana", VT_TRIGGER("kbd-kanalock") पूर्ण,
	[LED_SLEEP]	= अणु "sleep" पूर्ण ,
	[LED_SUSPEND]	= अणु "suspend" पूर्ण,
	[LED_MUTE]	= अणु "mute" पूर्ण,
	[LED_MISC]	= अणु "misc" पूर्ण,
	[LED_MAIL]	= अणु "mail" पूर्ण,
	[LED_CHARGING]	= अणु "charging" पूर्ण,
पूर्ण;

काष्ठा input_led अणु
	काष्ठा led_classdev cdev;
	काष्ठा input_handle *handle;
	अचिन्हित पूर्णांक code; /* One of LED_* स्थिरants */
पूर्ण;

काष्ठा input_leds अणु
	काष्ठा input_handle handle;
	अचिन्हित पूर्णांक num_leds;
	काष्ठा input_led leds[];
पूर्ण;

अटल क्रमागत led_brightness input_leds_brightness_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा input_led *led = container_of(cdev, काष्ठा input_led, cdev);
	काष्ठा input_dev *input = led->handle->dev;

	वापस test_bit(led->code, input->led) ? cdev->max_brightness : 0;
पूर्ण

अटल व्योम input_leds_brightness_set(काष्ठा led_classdev *cdev,
				      क्रमागत led_brightness brightness)
अणु
	काष्ठा input_led *led = container_of(cdev, काष्ठा input_led, cdev);

	input_inject_event(led->handle, EV_LED, led->code, !!brightness);
पूर्ण

अटल व्योम input_leds_event(काष्ठा input_handle *handle, अचिन्हित पूर्णांक type,
			     अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
पूर्ण

अटल पूर्णांक input_leds_get_count(काष्ठा input_dev *dev)
अणु
	अचिन्हित पूर्णांक led_code;
	पूर्णांक count = 0;

	क्रम_each_set_bit(led_code, dev->ledbit, LED_CNT)
		अगर (input_led_info[led_code].name)
			count++;

	वापस count;
पूर्ण

अटल पूर्णांक input_leds_connect(काष्ठा input_handler *handler,
			      काष्ठा input_dev *dev,
			      स्थिर काष्ठा input_device_id *id)
अणु
	काष्ठा input_leds *leds;
	काष्ठा input_led *led;
	अचिन्हित पूर्णांक num_leds;
	अचिन्हित पूर्णांक led_code;
	पूर्णांक led_no;
	पूर्णांक error;

	num_leds = input_leds_get_count(dev);
	अगर (!num_leds)
		वापस -ENXIO;

	leds = kzalloc(काष्ठा_size(leds, leds, num_leds), GFP_KERNEL);
	अगर (!leds)
		वापस -ENOMEM;

	leds->num_leds = num_leds;

	leds->handle.dev = dev;
	leds->handle.handler = handler;
	leds->handle.name = "leds";
	leds->handle.निजी = leds;

	error = input_रेजिस्टर_handle(&leds->handle);
	अगर (error)
		जाओ err_मुक्त_mem;

	error = input_खोलो_device(&leds->handle);
	अगर (error)
		जाओ err_unरेजिस्टर_handle;

	led_no = 0;
	क्रम_each_set_bit(led_code, dev->ledbit, LED_CNT) अणु
		अगर (!input_led_info[led_code].name)
			जारी;

		led = &leds->leds[led_no];
		led->handle = &leds->handle;
		led->code = led_code;

		led->cdev.name = kaप्र_लिखो(GFP_KERNEL, "%s::%s",
					   dev_name(&dev->dev),
					   input_led_info[led_code].name);
		अगर (!led->cdev.name) अणु
			error = -ENOMEM;
			जाओ err_unरेजिस्टर_leds;
		पूर्ण

		led->cdev.max_brightness = 1;
		led->cdev.brightness_get = input_leds_brightness_get;
		led->cdev.brightness_set = input_leds_brightness_set;
		led->cdev.शेष_trigger = input_led_info[led_code].trigger;

		error = led_classdev_रेजिस्टर(&dev->dev, &led->cdev);
		अगर (error) अणु
			dev_err(&dev->dev, "failed to register LED %s: %d\n",
				led->cdev.name, error);
			kमुक्त(led->cdev.name);
			जाओ err_unरेजिस्टर_leds;
		पूर्ण

		led_no++;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_leds:
	जबतक (--led_no >= 0) अणु
		काष्ठा input_led *led = &leds->leds[led_no];

		led_classdev_unरेजिस्टर(&led->cdev);
		kमुक्त(led->cdev.name);
	पूर्ण

	input_बंद_device(&leds->handle);

err_unरेजिस्टर_handle:
	input_unरेजिस्टर_handle(&leds->handle);

err_मुक्त_mem:
	kमुक्त(leds);
	वापस error;
पूर्ण

अटल व्योम input_leds_disconnect(काष्ठा input_handle *handle)
अणु
	काष्ठा input_leds *leds = handle->निजी;
	पूर्णांक i;

	क्रम (i = 0; i < leds->num_leds; i++) अणु
		काष्ठा input_led *led = &leds->leds[i];

		led_classdev_unरेजिस्टर(&led->cdev);
		kमुक्त(led->cdev.name);
	पूर्ण

	input_बंद_device(handle);
	input_unरेजिस्टर_handle(handle);

	kमुक्त(leds);
पूर्ण

अटल स्थिर काष्ठा input_device_id input_leds_ids[] = अणु
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = अणु BIT_MASK(EV_LED) पूर्ण,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(input, input_leds_ids);

अटल काष्ठा input_handler input_leds_handler = अणु
	.event =	input_leds_event,
	.connect =	input_leds_connect,
	.disconnect =	input_leds_disconnect,
	.name =		"leds",
	.id_table =	input_leds_ids,
पूर्ण;

अटल पूर्णांक __init input_leds_init(व्योम)
अणु
	वापस input_रेजिस्टर_handler(&input_leds_handler);
पूर्ण
module_init(input_leds_init);

अटल व्योम __निकास input_leds_निकास(व्योम)
अणु
	input_unरेजिस्टर_handler(&input_leds_handler);
पूर्ण
module_निकास(input_leds_निकास);

MODULE_AUTHOR("Samuel Thibault <samuel.thibault@ens-lyon.org>");
MODULE_AUTHOR("Dmitry Torokhov <dmitry.torokhov@gmail.com>");
MODULE_DESCRIPTION("Input -> LEDs Bridge");
MODULE_LICENSE("GPL v2");
