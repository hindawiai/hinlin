<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम keys on TCA6416 I2C IO expander
 *
 * Copyright (C) 2010 Texas Instruments
 *
 * Author : Sriramakrishnan.A.G. <srk@ti.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/tca6416_keypad.h>

#घोषणा TCA6416_INPUT          0
#घोषणा TCA6416_OUTPUT         1
#घोषणा TCA6416_INVERT         2
#घोषणा TCA6416_सूचीECTION      3

अटल स्थिर काष्ठा i2c_device_id tca6416_id[] = अणु
	अणु "tca6416-keys", 16, पूर्ण,
	अणु "tca6408-keys", 8, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tca6416_id);

काष्ठा tca6416_drv_data अणु
	काष्ठा input_dev *input;
	काष्ठा tca6416_button data[];
पूर्ण;

काष्ठा tca6416_keypad_chip अणु
	uपूर्णांक16_t reg_output;
	uपूर्णांक16_t reg_direction;
	uपूर्णांक16_t reg_input;

	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा delayed_work dwork;
	पूर्णांक io_size;
	पूर्णांक irqnum;
	u16 pinmask;
	bool use_polling;
	काष्ठा tca6416_button buttons[];
पूर्ण;

अटल पूर्णांक tca6416_ग_लिखो_reg(काष्ठा tca6416_keypad_chip *chip, पूर्णांक reg, u16 val)
अणु
	पूर्णांक error;

	error = chip->io_size > 8 ?
		i2c_smbus_ग_लिखो_word_data(chip->client, reg << 1, val) :
		i2c_smbus_ग_लिखो_byte_data(chip->client, reg, val);
	अगर (error < 0) अणु
		dev_err(&chip->client->dev,
			"%s failed, reg: %d, val: %d, error: %d\n",
			__func__, reg, val, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tca6416_पढ़ो_reg(काष्ठा tca6416_keypad_chip *chip, पूर्णांक reg, u16 *val)
अणु
	पूर्णांक retval;

	retval = chip->io_size > 8 ?
		 i2c_smbus_पढ़ो_word_data(chip->client, reg << 1) :
		 i2c_smbus_पढ़ो_byte_data(chip->client, reg);
	अगर (retval < 0) अणु
		dev_err(&chip->client->dev, "%s failed, reg: %d, error: %d\n",
			__func__, reg, retval);
		वापस retval;
	पूर्ण

	*val = (u16)retval;
	वापस 0;
पूर्ण

अटल व्योम tca6416_keys_scan(काष्ठा tca6416_keypad_chip *chip)
अणु
	काष्ठा input_dev *input = chip->input;
	u16 reg_val, val;
	पूर्णांक error, i, pin_index;

	error = tca6416_पढ़ो_reg(chip, TCA6416_INPUT, &reg_val);
	अगर (error)
		वापस;

	reg_val &= chip->pinmask;

	/* Figure out which lines have changed */
	val = reg_val ^ chip->reg_input;
	chip->reg_input = reg_val;

	क्रम (i = 0, pin_index = 0; i < 16; i++) अणु
		अगर (val & (1 << i)) अणु
			काष्ठा tca6416_button *button = &chip->buttons[pin_index];
			अचिन्हित पूर्णांक type = button->type ?: EV_KEY;
			पूर्णांक state = ((reg_val & (1 << i)) ? 1 : 0)
						^ button->active_low;

			input_event(input, type, button->code, !!state);
			input_sync(input);
		पूर्ण

		अगर (chip->pinmask & (1 << i))
			pin_index++;
	पूर्ण
पूर्ण

/*
 * This is thपढ़ोed IRQ handler and this can (and will) sleep.
 */
अटल irqवापस_t tca6416_keys_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tca6416_keypad_chip *chip = dev_id;

	tca6416_keys_scan(chip);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tca6416_keys_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tca6416_keypad_chip *chip =
		container_of(work, काष्ठा tca6416_keypad_chip, dwork.work);

	tca6416_keys_scan(chip);
	schedule_delayed_work(&chip->dwork, msecs_to_jअगरfies(100));
पूर्ण

अटल पूर्णांक tca6416_keys_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा tca6416_keypad_chip *chip = input_get_drvdata(dev);

	/* Get initial device state in हाल it has चयनes */
	tca6416_keys_scan(chip);

	अगर (chip->use_polling)
		schedule_delayed_work(&chip->dwork, msecs_to_jअगरfies(100));
	अन्यथा
		enable_irq(chip->irqnum);

	वापस 0;
पूर्ण

अटल व्योम tca6416_keys_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा tca6416_keypad_chip *chip = input_get_drvdata(dev);

	अगर (chip->use_polling)
		cancel_delayed_work_sync(&chip->dwork);
	अन्यथा
		disable_irq(chip->irqnum);
पूर्ण

अटल पूर्णांक tca6416_setup_रेजिस्टरs(काष्ठा tca6416_keypad_chip *chip)
अणु
	पूर्णांक error;

	error = tca6416_पढ़ो_reg(chip, TCA6416_OUTPUT, &chip->reg_output);
	अगर (error)
		वापस error;

	error = tca6416_पढ़ो_reg(chip, TCA6416_सूचीECTION, &chip->reg_direction);
	अगर (error)
		वापस error;

	/* ensure that keypad pins are set to input */
	error = tca6416_ग_लिखो_reg(chip, TCA6416_सूचीECTION,
				  chip->reg_direction | chip->pinmask);
	अगर (error)
		वापस error;

	error = tca6416_पढ़ो_reg(chip, TCA6416_सूचीECTION, &chip->reg_direction);
	अगर (error)
		वापस error;

	error = tca6416_पढ़ो_reg(chip, TCA6416_INPUT, &chip->reg_input);
	अगर (error)
		वापस error;

	chip->reg_input &= chip->pinmask;

	वापस 0;
पूर्ण

अटल पूर्णांक tca6416_keypad_probe(काष्ठा i2c_client *client,
				   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tca6416_keys_platक्रमm_data *pdata;
	काष्ठा tca6416_keypad_chip *chip;
	काष्ठा input_dev *input;
	पूर्णांक error;
	पूर्णांक i;

	/* Check functionality */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE)) अणु
		dev_err(&client->dev, "%s adapter not supported\n",
			dev_driver_string(&client->adapter->dev));
		वापस -ENODEV;
	पूर्ण

	pdata = dev_get_platdata(&client->dev);
	अगर (!pdata) अणु
		dev_dbg(&client->dev, "no platform data\n");
		वापस -EINVAL;
	पूर्ण

	chip = kzalloc(काष्ठा_size(chip, buttons, pdata->nbuttons), GFP_KERNEL);
	input = input_allocate_device();
	अगर (!chip || !input) अणु
		error = -ENOMEM;
		जाओ fail1;
	पूर्ण

	chip->client = client;
	chip->input = input;
	chip->io_size = id->driver_data;
	chip->pinmask = pdata->pinmask;
	chip->use_polling = pdata->use_polling;

	INIT_DELAYED_WORK(&chip->dwork, tca6416_keys_work_func);

	input->phys = "tca6416-keys/input0";
	input->name = client->name;
	input->dev.parent = &client->dev;

	input->खोलो = tca6416_keys_खोलो;
	input->बंद = tca6416_keys_बंद;

	input->id.bustype = BUS_HOST;
	input->id.venकरोr = 0x0001;
	input->id.product = 0x0001;
	input->id.version = 0x0100;

	/* Enable स्वतः repeat feature of Linux input subप्रणाली */
	अगर (pdata->rep)
		__set_bit(EV_REP, input->evbit);

	क्रम (i = 0; i < pdata->nbuttons; i++) अणु
		अचिन्हित पूर्णांक type;

		chip->buttons[i] = pdata->buttons[i];
		type = (pdata->buttons[i].type) ?: EV_KEY;
		input_set_capability(input, type, pdata->buttons[i].code);
	पूर्ण

	input_set_drvdata(input, chip);

	/*
	 * Initialize cached रेजिस्टरs from their original values.
	 * we can't share this chip with another i2c master.
	 */
	error = tca6416_setup_रेजिस्टरs(chip);
	अगर (error)
		जाओ fail1;

	अगर (!chip->use_polling) अणु
		अगर (pdata->irq_is_gpio)
			chip->irqnum = gpio_to_irq(client->irq);
		अन्यथा
			chip->irqnum = client->irq;

		error = request_thपढ़ोed_irq(chip->irqnum, शून्य,
					     tca6416_keys_isr,
					     IRQF_TRIGGER_FALLING |
					     IRQF_ONESHOT | IRQF_NO_AUTOEN,
					     "tca6416-keypad", chip);
		अगर (error) अणु
			dev_dbg(&client->dev,
				"Unable to claim irq %d; error %d\n",
				chip->irqnum, error);
			जाओ fail1;
		पूर्ण
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_dbg(&client->dev,
			"Unable to register input device, error: %d\n", error);
		जाओ fail2;
	पूर्ण

	i2c_set_clientdata(client, chip);
	device_init_wakeup(&client->dev, 1);

	वापस 0;

fail2:
	अगर (!chip->use_polling) अणु
		मुक्त_irq(chip->irqnum, chip);
		enable_irq(chip->irqnum);
	पूर्ण
fail1:
	input_मुक्त_device(input);
	kमुक्त(chip);
	वापस error;
पूर्ण

अटल पूर्णांक tca6416_keypad_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tca6416_keypad_chip *chip = i2c_get_clientdata(client);

	अगर (!chip->use_polling) अणु
		मुक्त_irq(chip->irqnum, chip);
		enable_irq(chip->irqnum);
	पूर्ण

	input_unरेजिस्टर_device(chip->input);
	kमुक्त(chip);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tca6416_keypad_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा tca6416_keypad_chip *chip = i2c_get_clientdata(client);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(chip->irqnum);

	वापस 0;
पूर्ण

अटल पूर्णांक tca6416_keypad_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा tca6416_keypad_chip *chip = i2c_get_clientdata(client);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(chip->irqnum);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tca6416_keypad_dev_pm_ops,
			 tca6416_keypad_suspend, tca6416_keypad_resume);

अटल काष्ठा i2c_driver tca6416_keypad_driver = अणु
	.driver = अणु
		.name	= "tca6416-keypad",
		.pm	= &tca6416_keypad_dev_pm_ops,
	पूर्ण,
	.probe		= tca6416_keypad_probe,
	.हटाओ		= tca6416_keypad_हटाओ,
	.id_table	= tca6416_id,
पूर्ण;

अटल पूर्णांक __init tca6416_keypad_init(व्योम)
अणु
	वापस i2c_add_driver(&tca6416_keypad_driver);
पूर्ण

subsys_initcall(tca6416_keypad_init);

अटल व्योम __निकास tca6416_keypad_निकास(व्योम)
अणु
	i2c_del_driver(&tca6416_keypad_driver);
पूर्ण
module_निकास(tca6416_keypad_निकास);

MODULE_AUTHOR("Sriramakrishnan <srk@ti.com>");
MODULE_DESCRIPTION("Keypad driver over tca6416 IO expander");
MODULE_LICENSE("GPL");
