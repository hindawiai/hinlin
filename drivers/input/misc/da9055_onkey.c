<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ON pin driver क्रम Dialog DA9055 PMICs
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mfd/da9055/core.h>
#समावेश <linux/mfd/da9055/reg.h>

काष्ठा da9055_onkey अणु
	काष्ठा da9055 *da9055;
	काष्ठा input_dev *input;
	काष्ठा delayed_work work;
पूर्ण;

अटल व्योम da9055_onkey_query(काष्ठा da9055_onkey *onkey)
अणु
	पूर्णांक key_stat;

	key_stat = da9055_reg_पढ़ो(onkey->da9055, DA9055_REG_STATUS_A);
	अगर (key_stat < 0) अणु
		dev_err(onkey->da9055->dev,
			"Failed to read onkey event %d\n", key_stat);
	पूर्ण अन्यथा अणु
		key_stat &= DA9055_NOKEY_STS;
		/*
		 * Onkey status bit is cleared when onkey button is released.
		 */
		अगर (!key_stat) अणु
			input_report_key(onkey->input, KEY_POWER, 0);
			input_sync(onkey->input);
		पूर्ण
	पूर्ण

	/*
	 * Interrupt is generated only when the ONKEY pin is निश्चितed.
	 * Hence the deनिश्चितion of the pin is simulated through work queue.
	 */
	अगर (key_stat)
		schedule_delayed_work(&onkey->work, msecs_to_jअगरfies(10));

पूर्ण

अटल व्योम da9055_onkey_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा da9055_onkey *onkey = container_of(work, काष्ठा da9055_onkey,
						  work.work);

	da9055_onkey_query(onkey);
पूर्ण

अटल irqवापस_t da9055_onkey_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9055_onkey *onkey = data;

	input_report_key(onkey->input, KEY_POWER, 1);
	input_sync(onkey->input);

	da9055_onkey_query(onkey);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक da9055_onkey_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9055 *da9055 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा da9055_onkey *onkey;
	काष्ठा input_dev *input_dev;
	पूर्णांक irq, err;

	irq = platक्रमm_get_irq_byname(pdev, "ONKEY");
	अगर (irq < 0)
		वापस -EINVAL;

	onkey = devm_kzalloc(&pdev->dev, माप(*onkey), GFP_KERNEL);
	अगर (!onkey) अणु
		dev_err(&pdev->dev, "Failed to allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	input_dev = input_allocate_device();
	अगर (!input_dev) अणु
		dev_err(&pdev->dev, "Failed to allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	onkey->input = input_dev;
	onkey->da9055 = da9055;
	input_dev->name = "da9055-onkey";
	input_dev->phys = "da9055-onkey/input0";
	input_dev->dev.parent = &pdev->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY);
	__set_bit(KEY_POWER, input_dev->keybit);

	INIT_DELAYED_WORK(&onkey->work, da9055_onkey_work);

	err = request_thपढ़ोed_irq(irq, शून्य, da9055_onkey_irq,
				   IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
				   "ONKEY", onkey);
	अगर (err < 0) अणु
		dev_err(&pdev->dev,
			"Failed to register ONKEY IRQ %d, error = %d\n",
			irq, err);
		जाओ err_मुक्त_input;
	पूर्ण

	err = input_रेजिस्टर_device(input_dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Unable to register input device, %d\n",
			err);
		जाओ err_मुक्त_irq;
	पूर्ण

	platक्रमm_set_drvdata(pdev, onkey);

	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(irq, onkey);
	cancel_delayed_work_sync(&onkey->work);
err_मुक्त_input:
	input_मुक्त_device(input_dev);

	वापस err;
पूर्ण

अटल पूर्णांक da9055_onkey_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9055_onkey *onkey = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq = platक्रमm_get_irq_byname(pdev, "ONKEY");

	irq = regmap_irq_get_virq(onkey->da9055->irq_data, irq);
	मुक्त_irq(irq, onkey);
	cancel_delayed_work_sync(&onkey->work);
	input_unरेजिस्टर_device(onkey->input);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9055_onkey_driver = अणु
	.probe	= da9055_onkey_probe,
	.हटाओ	= da9055_onkey_हटाओ,
	.driver = अणु
		.name	= "da9055-onkey",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(da9055_onkey_driver);

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("Onkey driver for DA9055");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9055-onkey");
