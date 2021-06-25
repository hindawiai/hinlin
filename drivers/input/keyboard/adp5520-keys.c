<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Keypad driver क्रम Analog Devices ADP5520 MFD PMICs
 *
 * Copyright 2009 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/mfd/adp5520.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>

काष्ठा adp5520_keys अणु
	काष्ठा input_dev *input;
	काष्ठा notअगरier_block notअगरier;
	काष्ठा device *master;
	अचिन्हित लघु keycode[ADP5520_KEYMAPSIZE];
पूर्ण;

अटल व्योम adp5520_keys_report_event(काष्ठा adp5520_keys *dev,
					अचिन्हित लघु keymask, पूर्णांक value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ADP5520_MAXKEYS; i++)
		अगर (keymask & (1 << i))
			input_report_key(dev->input, dev->keycode[i], value);

	input_sync(dev->input);
पूर्ण

अटल पूर्णांक adp5520_keys_notअगरier(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा adp5520_keys *dev;
	uपूर्णांक8_t reg_val_lo, reg_val_hi;
	अचिन्हित लघु keymask;

	dev = container_of(nb, काष्ठा adp5520_keys, notअगरier);

	अगर (event & ADP5520_KP_INT) अणु
		adp5520_पढ़ो(dev->master, ADP5520_KP_INT_STAT_1, &reg_val_lo);
		adp5520_पढ़ो(dev->master, ADP5520_KP_INT_STAT_2, &reg_val_hi);

		keymask = (reg_val_hi << 8) | reg_val_lo;
		/* Read twice to clear */
		adp5520_पढ़ो(dev->master, ADP5520_KP_INT_STAT_1, &reg_val_lo);
		adp5520_पढ़ो(dev->master, ADP5520_KP_INT_STAT_2, &reg_val_hi);
		keymask |= (reg_val_hi << 8) | reg_val_lo;
		adp5520_keys_report_event(dev, keymask, 1);
	पूर्ण

	अगर (event & ADP5520_KR_INT) अणु
		adp5520_पढ़ो(dev->master, ADP5520_KR_INT_STAT_1, &reg_val_lo);
		adp5520_पढ़ो(dev->master, ADP5520_KR_INT_STAT_2, &reg_val_hi);

		keymask = (reg_val_hi << 8) | reg_val_lo;
		/* Read twice to clear */
		adp5520_पढ़ो(dev->master, ADP5520_KR_INT_STAT_1, &reg_val_lo);
		adp5520_पढ़ो(dev->master, ADP5520_KR_INT_STAT_2, &reg_val_hi);
		keymask |= (reg_val_hi << 8) | reg_val_lo;
		adp5520_keys_report_event(dev, keymask, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adp5520_keys_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा adp5520_keys_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा input_dev *input;
	काष्ठा adp5520_keys *dev;
	पूर्णांक ret, i;
	अचिन्हित अक्षर en_mask, ctl_mask = 0;

	अगर (pdev->id != ID_ADP5520) अणु
		dev_err(&pdev->dev, "only ADP5520 supports Keypad\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "missing platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!(pdata->rows_en_mask && pdata->cols_en_mask))
		वापस -EINVAL;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		dev_err(&pdev->dev, "failed to alloc memory\n");
		वापस -ENOMEM;
	पूर्ण

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	dev->master = pdev->dev.parent;
	dev->input = input;

	input->name = pdev->name;
	input->phys = "adp5520-keys/input0";
	input->dev.parent = &pdev->dev;

	input->id.bustype = BUS_I2C;
	input->id.venकरोr = 0x0001;
	input->id.product = 0x5520;
	input->id.version = 0x0001;

	input->keycodesize = माप(dev->keycode[0]);
	input->keycodemax = pdata->keymapsize;
	input->keycode = dev->keycode;

	स_नकल(dev->keycode, pdata->keymap,
		pdata->keymapsize * input->keycodesize);

	/* setup input device */
	__set_bit(EV_KEY, input->evbit);

	अगर (pdata->repeat)
		__set_bit(EV_REP, input->evbit);

	क्रम (i = 0; i < input->keycodemax; i++)
		__set_bit(dev->keycode[i], input->keybit);
	__clear_bit(KEY_RESERVED, input->keybit);

	ret = input_रेजिस्टर_device(input);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to register input device\n");
		वापस ret;
	पूर्ण

	en_mask = pdata->rows_en_mask | pdata->cols_en_mask;

	ret = adp5520_set_bits(dev->master, ADP5520_GPIO_CFG_1, en_mask);

	अगर (en_mask & ADP5520_COL_C3)
		ctl_mask |= ADP5520_C3_MODE;

	अगर (en_mask & ADP5520_ROW_R3)
		ctl_mask |= ADP5520_R3_MODE;

	अगर (ctl_mask)
		ret |= adp5520_set_bits(dev->master, ADP5520_LED_CONTROL,
			ctl_mask);

	ret |= adp5520_set_bits(dev->master, ADP5520_GPIO_PULLUP,
		pdata->rows_en_mask);

	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to write\n");
		वापस -EIO;
	पूर्ण

	dev->notअगरier.notअगरier_call = adp5520_keys_notअगरier;
	ret = adp5520_रेजिस्टर_notअगरier(dev->master, &dev->notअगरier,
			ADP5520_KP_IEN | ADP5520_KR_IEN);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register notifier\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dev);
	वापस 0;
पूर्ण

अटल पूर्णांक adp5520_keys_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा adp5520_keys *dev = platक्रमm_get_drvdata(pdev);

	adp5520_unरेजिस्टर_notअगरier(dev->master, &dev->notअगरier,
				ADP5520_KP_IEN | ADP5520_KR_IEN);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver adp5520_keys_driver = अणु
	.driver	= अणु
		.name	= "adp5520-keys",
	पूर्ण,
	.probe		= adp5520_keys_probe,
	.हटाओ		= adp5520_keys_हटाओ,
पूर्ण;
module_platक्रमm_driver(adp5520_keys_driver);

MODULE_AUTHOR("Michael Hennerich <hennerich@blackfin.uclinux.org>");
MODULE_DESCRIPTION("Keys ADP5520 Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:adp5520-keys");
