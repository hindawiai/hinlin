<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ON pin driver क्रम Dialog DA9052 PMICs
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/mfd/da9052/da9052.h>
#समावेश <linux/mfd/da9052/reg.h>

काष्ठा da9052_onkey अणु
	काष्ठा da9052 *da9052;
	काष्ठा input_dev *input;
	काष्ठा delayed_work work;
पूर्ण;

अटल व्योम da9052_onkey_query(काष्ठा da9052_onkey *onkey)
अणु
	पूर्णांक ret;

	ret = da9052_reg_पढ़ो(onkey->da9052, DA9052_STATUS_A_REG);
	अगर (ret < 0) अणु
		dev_err(onkey->da9052->dev,
			"Failed to read onkey event err=%d\n", ret);
	पूर्ण अन्यथा अणु
		/*
		 * Since पूर्णांकerrupt क्रम deनिश्चितion of ONKEY pin is not
		 * generated, onkey event state determines the onkey
		 * button state.
		 */
		bool pressed = !(ret & DA9052_STATUSA_NONKEY);

		input_report_key(onkey->input, KEY_POWER, pressed);
		input_sync(onkey->input);

		/*
		 * Interrupt is generated only when the ONKEY pin
		 * is निश्चितed.  Hence the deनिश्चितion of the pin
		 * is simulated through work queue.
		 */
		अगर (pressed)
			schedule_delayed_work(&onkey->work,
						msecs_to_jअगरfies(50));
	पूर्ण
पूर्ण

अटल व्योम da9052_onkey_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा da9052_onkey *onkey = container_of(work, काष्ठा da9052_onkey,
						  work.work);

	da9052_onkey_query(onkey);
पूर्ण

अटल irqवापस_t da9052_onkey_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9052_onkey *onkey = data;

	da9052_onkey_query(onkey);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक da9052_onkey_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9052 *da9052 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा da9052_onkey *onkey;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	अगर (!da9052) अणु
		dev_err(&pdev->dev, "Failed to get the driver's data\n");
		वापस -EINVAL;
	पूर्ण

	onkey = kzalloc(माप(*onkey), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!onkey || !input_dev) अणु
		dev_err(&pdev->dev, "Failed to allocate memory\n");
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	onkey->input = input_dev;
	onkey->da9052 = da9052;
	INIT_DELAYED_WORK(&onkey->work, da9052_onkey_work);

	input_dev->name = "da9052-onkey";
	input_dev->phys = "da9052-onkey/input0";
	input_dev->dev.parent = &pdev->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY);
	__set_bit(KEY_POWER, input_dev->keybit);

	error = da9052_request_irq(onkey->da9052, DA9052_IRQ_NONKEY, "ONKEY",
			    da9052_onkey_irq, onkey);
	अगर (error < 0) अणु
		dev_err(onkey->da9052->dev,
			"Failed to register ONKEY IRQ: %d\n", error);
		जाओ err_मुक्त_mem;
	पूर्ण

	error = input_रेजिस्टर_device(onkey->input);
	अगर (error) अणु
		dev_err(&pdev->dev, "Unable to register input device, %d\n",
			error);
		जाओ err_मुक्त_irq;
	पूर्ण

	platक्रमm_set_drvdata(pdev, onkey);
	वापस 0;

err_मुक्त_irq:
	da9052_मुक्त_irq(onkey->da9052, DA9052_IRQ_NONKEY, onkey);
	cancel_delayed_work_sync(&onkey->work);
err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	kमुक्त(onkey);

	वापस error;
पूर्ण

अटल पूर्णांक da9052_onkey_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9052_onkey *onkey = platक्रमm_get_drvdata(pdev);

	da9052_मुक्त_irq(onkey->da9052, DA9052_IRQ_NONKEY, onkey);
	cancel_delayed_work_sync(&onkey->work);

	input_unरेजिस्टर_device(onkey->input);
	kमुक्त(onkey);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9052_onkey_driver = अणु
	.probe	= da9052_onkey_probe,
	.हटाओ	= da9052_onkey_हटाओ,
	.driver = अणु
		.name	= "da9052-onkey",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(da9052_onkey_driver);

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("Onkey driver for DA9052");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9052-onkey");
