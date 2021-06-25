<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * h3600 aपंचांगel micro companion support, key subdevice
 * based on previous kernel 2.4 version
 * Author : Alessandro Gardich <gremlin@gremlin.it>
 * Author : Linus Walleij <linus.walleij@linaro.org>
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/pm.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/ipaq-micro.h>

काष्ठा ipaq_micro_keys अणु
	काष्ठा ipaq_micro *micro;
	काष्ठा input_dev *input;
	u16 *codes;
पूर्ण;

अटल स्थिर u16 micro_keycodes[] = अणु
	KEY_RECORD,		/* 1:  Record button			*/
	KEY_CALENDAR,		/* 2:  Calendar				*/
	KEY_ADDRESSBOOK,	/* 3:  Contacts (looks like Outlook)	*/
	KEY_MAIL,		/* 4:  Envelope (Q on older iPAQs)	*/
	KEY_HOMEPAGE,		/* 5:  Start (looks like swoopy arrow)	*/
	KEY_UP,			/* 6:  Up				*/
	KEY_RIGHT,		/* 7:  Right				*/
	KEY_LEFT,		/* 8:  Left				*/
	KEY_DOWN,		/* 9:  Down				*/
पूर्ण;

अटल व्योम micro_key_receive(व्योम *data, पूर्णांक len, अचिन्हित अक्षर *msg)
अणु
	काष्ठा ipaq_micro_keys *keys = data;
	पूर्णांक key, करोwn;

	करोwn = 0x80 & msg[0];
	key  = 0x7f & msg[0];

	अगर (key < ARRAY_SIZE(micro_keycodes)) अणु
		input_report_key(keys->input, keys->codes[key], करोwn);
		input_sync(keys->input);
	पूर्ण
पूर्ण

अटल व्योम micro_key_start(काष्ठा ipaq_micro_keys *keys)
अणु
	spin_lock(&keys->micro->lock);
	keys->micro->key = micro_key_receive;
	keys->micro->key_data = keys;
	spin_unlock(&keys->micro->lock);
पूर्ण

अटल व्योम micro_key_stop(काष्ठा ipaq_micro_keys *keys)
अणु
	spin_lock(&keys->micro->lock);
	keys->micro->key = शून्य;
	keys->micro->key_data = शून्य;
	spin_unlock(&keys->micro->lock);
पूर्ण

अटल पूर्णांक micro_key_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा ipaq_micro_keys *keys = input_get_drvdata(input);

	micro_key_start(keys);

	वापस 0;
पूर्ण

अटल व्योम micro_key_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा ipaq_micro_keys *keys = input_get_drvdata(input);

	micro_key_stop(keys);
पूर्ण

अटल पूर्णांक micro_key_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ipaq_micro_keys *keys;
	पूर्णांक error;
	पूर्णांक i;

	keys = devm_kzalloc(&pdev->dev, माप(*keys), GFP_KERNEL);
	अगर (!keys)
		वापस -ENOMEM;

	keys->micro = dev_get_drvdata(pdev->dev.parent);

	keys->input = devm_input_allocate_device(&pdev->dev);
	अगर (!keys->input)
		वापस -ENOMEM;

	keys->input->keycodesize = माप(micro_keycodes[0]);
	keys->input->keycodemax = ARRAY_SIZE(micro_keycodes);
	keys->codes = devm_kmemdup(&pdev->dev, micro_keycodes,
			   keys->input->keycodesize * keys->input->keycodemax,
			   GFP_KERNEL);
	keys->input->keycode = keys->codes;

	__set_bit(EV_KEY, keys->input->evbit);
	क्रम (i = 0; i < ARRAY_SIZE(micro_keycodes); i++)
		__set_bit(micro_keycodes[i], keys->input->keybit);

	keys->input->name = "h3600 micro keys";
	keys->input->खोलो = micro_key_खोलो;
	keys->input->बंद = micro_key_बंद;
	input_set_drvdata(keys->input, keys);

	error = input_रेजिस्टर_device(keys->input);
	अगर (error)
		वापस error;

	platक्रमm_set_drvdata(pdev, keys);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused micro_key_suspend(काष्ठा device *dev)
अणु
	काष्ठा ipaq_micro_keys *keys = dev_get_drvdata(dev);

	micro_key_stop(keys);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused micro_key_resume(काष्ठा device *dev)
अणु
	काष्ठा ipaq_micro_keys *keys = dev_get_drvdata(dev);
	काष्ठा input_dev *input = keys->input;

	mutex_lock(&input->mutex);

	अगर (input_device_enabled(input))
		micro_key_start(keys);

	mutex_unlock(&input->mutex);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(micro_key_dev_pm_ops,
			 micro_key_suspend, micro_key_resume);

अटल काष्ठा platक्रमm_driver micro_key_device_driver = अणु
	.driver = अणु
		.name    = "ipaq-micro-keys",
		.pm	= &micro_key_dev_pm_ops,
	पूर्ण,
	.probe   = micro_key_probe,
पूर्ण;
module_platक्रमm_driver(micro_key_device_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("driver for iPAQ Atmel micro keys");
MODULE_ALIAS("platform:ipaq-micro-keys");
