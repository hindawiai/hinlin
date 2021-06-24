<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic GPIO beeper driver
 *
 * Copyright (C) 2013-2014 Alexander Shiyan <shc_work@mail.ru>
 */

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा BEEPER_MODNAME		"gpio-beeper"

काष्ठा gpio_beeper अणु
	काष्ठा work_काष्ठा	work;
	काष्ठा gpio_desc	*desc;
	bool			beeping;
पूर्ण;

अटल व्योम gpio_beeper_toggle(काष्ठा gpio_beeper *beep, bool on)
अणु
	gpiod_set_value_cansleep(beep->desc, on);
पूर्ण

अटल व्योम gpio_beeper_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gpio_beeper *beep = container_of(work, काष्ठा gpio_beeper, work);

	gpio_beeper_toggle(beep, beep->beeping);
पूर्ण

अटल पूर्णांक gpio_beeper_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
			     अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा gpio_beeper *beep = input_get_drvdata(dev);

	अगर (type != EV_SND || code != SND_BELL)
		वापस -ENOTSUPP;

	अगर (value < 0)
		वापस -EINVAL;

	beep->beeping = value;
	/* Schedule work to actually turn the beeper on or off */
	schedule_work(&beep->work);

	वापस 0;
पूर्ण

अटल व्योम gpio_beeper_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा gpio_beeper *beep = input_get_drvdata(input);

	cancel_work_sync(&beep->work);
	gpio_beeper_toggle(beep, false);
पूर्ण

अटल पूर्णांक gpio_beeper_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_beeper *beep;
	काष्ठा input_dev *input;

	beep = devm_kzalloc(&pdev->dev, माप(*beep), GFP_KERNEL);
	अगर (!beep)
		वापस -ENOMEM;

	beep->desc = devm_gpiod_get(&pdev->dev, शून्य, GPIOD_OUT_LOW);
	अगर (IS_ERR(beep->desc))
		वापस PTR_ERR(beep->desc);

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	INIT_WORK(&beep->work, gpio_beeper_work);

	input->name		= pdev->name;
	input->id.bustype	= BUS_HOST;
	input->id.venकरोr	= 0x0001;
	input->id.product	= 0x0001;
	input->id.version	= 0x0100;
	input->बंद		= gpio_beeper_बंद;
	input->event		= gpio_beeper_event;

	input_set_capability(input, EV_SND, SND_BELL);

	input_set_drvdata(input, beep);

	वापस input_रेजिस्टर_device(input);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id gpio_beeper_of_match[] = अणु
	अणु .compatible = BEEPER_MODNAME, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_beeper_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver gpio_beeper_platक्रमm_driver = अणु
	.driver	= अणु
		.name		= BEEPER_MODNAME,
		.of_match_table	= of_match_ptr(gpio_beeper_of_match),
	पूर्ण,
	.probe	= gpio_beeper_probe,
पूर्ण;
module_platक्रमm_driver(gpio_beeper_platक्रमm_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Shiyan <shc_work@mail.ru>");
MODULE_DESCRIPTION("Generic GPIO beeper driver");
