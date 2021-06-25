<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Driver क्रम buttons on GPIO lines not capable of generating पूर्णांकerrupts
 *
 *  Copyright (C) 2007-2010 Gabor Juhos <juhosg@खोलोwrt.org>
 *  Copyright (C) 2010 Nuno Goncalves <nunojpg@gmail.com>
 *
 *  This file was based on: /drivers/input/misc/cobalt_btns.c
 *	Copyright (C) 2007 Yoichi Yuasa <yoichi_yuasa@tripeaks.co.jp>
 *
 *  also was based on: /drivers/input/keyboard/gpio_keys.c
 *	Copyright 2005 Phil Blundell
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/property.h>

#घोषणा DRV_NAME	"gpio-keys-polled"

काष्ठा gpio_keys_button_data अणु
	काष्ठा gpio_desc *gpiod;
	पूर्णांक last_state;
	पूर्णांक count;
	पूर्णांक threshold;
पूर्ण;

काष्ठा gpio_keys_polled_dev अणु
	काष्ठा input_dev *input;
	काष्ठा device *dev;
	स्थिर काष्ठा gpio_keys_platक्रमm_data *pdata;
	अचिन्हित दीर्घ rel_axis_seen[BITS_TO_LONGS(REL_CNT)];
	अचिन्हित दीर्घ असल_axis_seen[BITS_TO_LONGS(ABS_CNT)];
	काष्ठा gpio_keys_button_data data[];
पूर्ण;

अटल व्योम gpio_keys_button_event(काष्ठा input_dev *input,
				   स्थिर काष्ठा gpio_keys_button *button,
				   पूर्णांक state)
अणु
	काष्ठा gpio_keys_polled_dev *bdev = input_get_drvdata(input);
	अचिन्हित पूर्णांक type = button->type ?: EV_KEY;

	अगर (type == EV_REL) अणु
		अगर (state) अणु
			input_event(input, type, button->code, button->value);
			__set_bit(button->code, bdev->rel_axis_seen);
		पूर्ण
	पूर्ण अन्यथा अगर (type == EV_ABS) अणु
		अगर (state) अणु
			input_event(input, type, button->code, button->value);
			__set_bit(button->code, bdev->असल_axis_seen);
		पूर्ण
	पूर्ण अन्यथा अणु
		input_event(input, type, button->code, state);
		input_sync(input);
	पूर्ण
पूर्ण

अटल व्योम gpio_keys_polled_check_state(काष्ठा input_dev *input,
					 स्थिर काष्ठा gpio_keys_button *button,
					 काष्ठा gpio_keys_button_data *bdata)
अणु
	पूर्णांक state;

	state = gpiod_get_value_cansleep(bdata->gpiod);
	अगर (state < 0) अणु
		dev_err(input->dev.parent,
			"failed to get gpio state: %d\n", state);
	पूर्ण अन्यथा अणु
		gpio_keys_button_event(input, button, state);

		अगर (state != bdata->last_state) अणु
			bdata->count = 0;
			bdata->last_state = state;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gpio_keys_polled_poll(काष्ठा input_dev *input)
अणु
	काष्ठा gpio_keys_polled_dev *bdev = input_get_drvdata(input);
	स्थिर काष्ठा gpio_keys_platक्रमm_data *pdata = bdev->pdata;
	पूर्णांक i;

	स_रखो(bdev->rel_axis_seen, 0, माप(bdev->rel_axis_seen));
	स_रखो(bdev->असल_axis_seen, 0, माप(bdev->असल_axis_seen));

	क्रम (i = 0; i < pdata->nbuttons; i++) अणु
		काष्ठा gpio_keys_button_data *bdata = &bdev->data[i];

		अगर (bdata->count < bdata->threshold) अणु
			bdata->count++;
			gpio_keys_button_event(input, &pdata->buttons[i],
					       bdata->last_state);
		पूर्ण अन्यथा अणु
			gpio_keys_polled_check_state(input, &pdata->buttons[i],
						     bdata);
		पूर्ण
	पूर्ण

	क्रम_each_set_bit(i, input->relbit, REL_CNT) अणु
		अगर (!test_bit(i, bdev->rel_axis_seen))
			input_event(input, EV_REL, i, 0);
	पूर्ण

	क्रम_each_set_bit(i, input->असलbit, ABS_CNT) अणु
		अगर (!test_bit(i, bdev->असल_axis_seen))
			input_event(input, EV_ABS, i, 0);
	पूर्ण

	input_sync(input);
पूर्ण

अटल पूर्णांक gpio_keys_polled_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा gpio_keys_polled_dev *bdev = input_get_drvdata(input);
	स्थिर काष्ठा gpio_keys_platक्रमm_data *pdata = bdev->pdata;

	अगर (pdata->enable)
		pdata->enable(bdev->dev);

	वापस 0;
पूर्ण

अटल व्योम gpio_keys_polled_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा gpio_keys_polled_dev *bdev = input_get_drvdata(input);
	स्थिर काष्ठा gpio_keys_platक्रमm_data *pdata = bdev->pdata;

	अगर (pdata->disable)
		pdata->disable(bdev->dev);
पूर्ण

अटल काष्ठा gpio_keys_platक्रमm_data *
gpio_keys_polled_get_devtree_pdata(काष्ठा device *dev)
अणु
	काष्ठा gpio_keys_platक्रमm_data *pdata;
	काष्ठा gpio_keys_button *button;
	काष्ठा fwnode_handle *child;
	पूर्णांक nbuttons;

	nbuttons = device_get_child_node_count(dev);
	अगर (nbuttons == 0)
		वापस ERR_PTR(-EINVAL);

	pdata = devm_kzalloc(dev, माप(*pdata) + nbuttons * माप(*button),
			     GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	button = (काष्ठा gpio_keys_button *)(pdata + 1);

	pdata->buttons = button;
	pdata->nbuttons = nbuttons;

	pdata->rep = device_property_present(dev, "autorepeat");
	device_property_पढ़ो_u32(dev, "poll-interval", &pdata->poll_पूर्णांकerval);

	device_property_पढ़ो_string(dev, "label", &pdata->name);

	device_क्रम_each_child_node(dev, child) अणु
		अगर (fwnode_property_पढ़ो_u32(child, "linux,code",
					     &button->code)) अणु
			dev_err(dev, "button without keycode\n");
			fwnode_handle_put(child);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		fwnode_property_पढ़ो_string(child, "label", &button->desc);

		अगर (fwnode_property_पढ़ो_u32(child, "linux,input-type",
					     &button->type))
			button->type = EV_KEY;

		अगर (fwnode_property_पढ़ो_u32(child, "linux,input-value",
					     (u32 *)&button->value))
			button->value = 1;

		button->wakeup =
			fwnode_property_पढ़ो_bool(child, "wakeup-source") ||
			/* legacy name */
			fwnode_property_पढ़ो_bool(child, "gpio-key,wakeup");

		अगर (fwnode_property_पढ़ो_u32(child, "debounce-interval",
					     &button->debounce_पूर्णांकerval))
			button->debounce_पूर्णांकerval = 5;

		button++;
	पूर्ण

	वापस pdata;
पूर्ण

अटल व्योम gpio_keys_polled_set_असल_params(काष्ठा input_dev *input,
	स्थिर काष्ठा gpio_keys_platक्रमm_data *pdata, अचिन्हित पूर्णांक code)
अणु
	पूर्णांक i, min = 0, max = 0;

	क्रम (i = 0; i < pdata->nbuttons; i++) अणु
		स्थिर काष्ठा gpio_keys_button *button = &pdata->buttons[i];

		अगर (button->type != EV_ABS || button->code != code)
			जारी;

		अगर (button->value < min)
			min = button->value;
		अगर (button->value > max)
			max = button->value;
	पूर्ण

	input_set_असल_params(input, code, min, max, 0, 0);
पूर्ण

अटल स्थिर काष्ठा of_device_id gpio_keys_polled_of_match[] = अणु
	अणु .compatible = "gpio-keys-polled", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_keys_polled_of_match);

अटल पूर्णांक gpio_keys_polled_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fwnode_handle *child = शून्य;
	स्थिर काष्ठा gpio_keys_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा gpio_keys_polled_dev *bdev;
	काष्ठा input_dev *input;
	पूर्णांक error;
	पूर्णांक i;

	अगर (!pdata) अणु
		pdata = gpio_keys_polled_get_devtree_pdata(dev);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण

	अगर (!pdata->poll_पूर्णांकerval) अणु
		dev_err(dev, "missing poll_interval value\n");
		वापस -EINVAL;
	पूर्ण

	bdev = devm_kzalloc(dev, काष्ठा_size(bdev, data, pdata->nbuttons),
			    GFP_KERNEL);
	अगर (!bdev) अणु
		dev_err(dev, "no memory for private data\n");
		वापस -ENOMEM;
	पूर्ण

	input = devm_input_allocate_device(dev);
	अगर (!input) अणु
		dev_err(dev, "no memory for input device\n");
		वापस -ENOMEM;
	पूर्ण

	input_set_drvdata(input, bdev);

	input->name = pdata->name ?: pdev->name;
	input->phys = DRV_NAME"/input0";

	input->id.bustype = BUS_HOST;
	input->id.venकरोr = 0x0001;
	input->id.product = 0x0001;
	input->id.version = 0x0100;

	input->खोलो = gpio_keys_polled_खोलो;
	input->बंद = gpio_keys_polled_बंद;

	__set_bit(EV_KEY, input->evbit);
	अगर (pdata->rep)
		__set_bit(EV_REP, input->evbit);

	क्रम (i = 0; i < pdata->nbuttons; i++) अणु
		स्थिर काष्ठा gpio_keys_button *button = &pdata->buttons[i];
		काष्ठा gpio_keys_button_data *bdata = &bdev->data[i];
		अचिन्हित पूर्णांक type = button->type ?: EV_KEY;

		अगर (button->wakeup) अणु
			dev_err(dev, DRV_NAME " does not support wakeup\n");
			fwnode_handle_put(child);
			वापस -EINVAL;
		पूर्ण

		अगर (!dev_get_platdata(dev)) अणु
			/* No legacy अटल platक्रमm data */
			child = device_get_next_child_node(dev, child);
			अगर (!child) अणु
				dev_err(dev, "missing child device node\n");
				वापस -EINVAL;
			पूर्ण

			bdata->gpiod = devm_fwnode_gpiod_get(dev, child,
							     शून्य, GPIOD_IN,
							     button->desc);
			अगर (IS_ERR(bdata->gpiod)) अणु
				error = PTR_ERR(bdata->gpiod);
				अगर (error != -EPROBE_DEFER)
					dev_err(dev,
						"failed to get gpio: %d\n",
						error);
				fwnode_handle_put(child);
				वापस error;
			पूर्ण
		पूर्ण अन्यथा अगर (gpio_is_valid(button->gpio)) अणु
			/*
			 * Legacy GPIO number so request the GPIO here and
			 * convert it to descriptor.
			 */
			अचिन्हित flags = GPIOF_IN;

			अगर (button->active_low)
				flags |= GPIOF_ACTIVE_LOW;

			error = devm_gpio_request_one(dev, button->gpio,
					flags, button->desc ? : DRV_NAME);
			अगर (error) अणु
				dev_err(dev,
					"unable to claim gpio %u, err=%d\n",
					button->gpio, error);
				वापस error;
			पूर्ण

			bdata->gpiod = gpio_to_desc(button->gpio);
			अगर (!bdata->gpiod) अणु
				dev_err(dev,
					"unable to convert gpio %u to descriptor\n",
					button->gpio);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		bdata->last_state = -1;
		bdata->threshold = DIV_ROUND_UP(button->debounce_पूर्णांकerval,
						pdata->poll_पूर्णांकerval);

		input_set_capability(input, type, button->code);
		अगर (type == EV_ABS)
			gpio_keys_polled_set_असल_params(input, pdata,
							button->code);
	पूर्ण

	fwnode_handle_put(child);

	bdev->input = input;
	bdev->dev = dev;
	bdev->pdata = pdata;

	error = input_setup_polling(input, gpio_keys_polled_poll);
	अगर (error) अणु
		dev_err(dev, "unable to set up polling, err=%d\n", error);
		वापस error;
	पूर्ण

	input_set_poll_पूर्णांकerval(input, pdata->poll_पूर्णांकerval);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(dev, "unable to register polled device, err=%d\n",
			error);
		वापस error;
	पूर्ण

	/* report initial state of the buttons */
	क्रम (i = 0; i < pdata->nbuttons; i++)
		gpio_keys_polled_check_state(input, &pdata->buttons[i],
					     &bdev->data[i]);

	input_sync(input);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver gpio_keys_polled_driver = अणु
	.probe	= gpio_keys_polled_probe,
	.driver	= अणु
		.name	= DRV_NAME,
		.of_match_table = gpio_keys_polled_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(gpio_keys_polled_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Gabor Juhos <juhosg@openwrt.org>");
MODULE_DESCRIPTION("Polled GPIO Buttons driver");
MODULE_ALIAS("platform:" DRV_NAME);
