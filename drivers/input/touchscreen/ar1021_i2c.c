<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Microchip AR1020 and AR1021 driver क्रम I2C
 *
 * Author: Christian Gmeiner <christian.gmeiner@gmail.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/of.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा AR1021_TOUCH_PKG_SIZE	5

#घोषणा AR1021_MAX_X	4095
#घोषणा AR1021_MAX_Y	4095

#घोषणा AR1021_CMD	0x55

#घोषणा AR1021_CMD_ENABLE_TOUCH		0x12

काष्ठा ar1021_i2c अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	u8 data[AR1021_TOUCH_PKG_SIZE];
पूर्ण;

अटल irqवापस_t ar1021_i2c_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ar1021_i2c *ar1021 = dev_id;
	काष्ठा input_dev *input = ar1021->input;
	u8 *data = ar1021->data;
	अचिन्हित पूर्णांक x, y, button;
	पूर्णांक retval;

	retval = i2c_master_recv(ar1021->client,
				 ar1021->data, माप(ar1021->data));
	अगर (retval != माप(ar1021->data))
		जाओ out;

	/* sync bit set ? */
	अगर (!(data[0] & BIT(7)))
		जाओ out;

	button = data[0] & BIT(0);
	x = ((data[2] & 0x1f) << 7) | (data[1] & 0x7f);
	y = ((data[4] & 0x1f) << 7) | (data[3] & 0x7f);

	input_report_असल(input, ABS_X, x);
	input_report_असल(input, ABS_Y, y);
	input_report_key(input, BTN_TOUCH, button);
	input_sync(input);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ar1021_i2c_खोलो(काष्ठा input_dev *dev)
अणु
	अटल स्थिर u8 cmd_enable_touch[] = अणु
		AR1021_CMD,
		0x01, /* number of bytes after this */
		AR1021_CMD_ENABLE_TOUCH
	पूर्ण;
	काष्ठा ar1021_i2c *ar1021 = input_get_drvdata(dev);
	काष्ठा i2c_client *client = ar1021->client;
	पूर्णांक error;

	error = i2c_master_send(ar1021->client, cmd_enable_touch,
				माप(cmd_enable_touch));
	अगर (error < 0)
		वापस error;

	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल व्योम ar1021_i2c_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा ar1021_i2c *ar1021 = input_get_drvdata(dev);
	काष्ठा i2c_client *client = ar1021->client;

	disable_irq(client->irq);
पूर्ण

अटल पूर्णांक ar1021_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ar1021_i2c *ar1021;
	काष्ठा input_dev *input;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "i2c_check_functionality error\n");
		वापस -ENXIO;
	पूर्ण

	ar1021 = devm_kzalloc(&client->dev, माप(*ar1021), GFP_KERNEL);
	अगर (!ar1021)
		वापस -ENOMEM;

	input = devm_input_allocate_device(&client->dev);
	अगर (!input)
		वापस -ENOMEM;

	ar1021->client = client;
	ar1021->input = input;

	input->name = "ar1021 I2C Touchscreen";
	input->id.bustype = BUS_I2C;
	input->dev.parent = &client->dev;
	input->खोलो = ar1021_i2c_खोलो;
	input->बंद = ar1021_i2c_बंद;

	__set_bit(INPUT_PROP_सूचीECT, input->propbit);
	input_set_capability(input, EV_KEY, BTN_TOUCH);
	input_set_असल_params(input, ABS_X, 0, AR1021_MAX_X, 0, 0);
	input_set_असल_params(input, ABS_Y, 0, AR1021_MAX_Y, 0, 0);

	input_set_drvdata(input, ar1021);

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, ar1021_i2c_irq,
					  IRQF_ONESHOT | IRQF_NO_AUTOEN,
					  "ar1021_i2c", ar1021);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to enable IRQ, error: %d\n", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(ar1021->input);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to register input device, error: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ar1021_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	disable_irq(client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ar1021_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ar1021_i2c_pm, ar1021_i2c_suspend, ar1021_i2c_resume);

अटल स्थिर काष्ठा i2c_device_id ar1021_i2c_id[] = अणु
	अणु "ar1021", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ar1021_i2c_id);

अटल स्थिर काष्ठा of_device_id ar1021_i2c_of_match[] = अणु
	अणु .compatible = "microchip,ar1021-i2c", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ar1021_i2c_of_match);

अटल काष्ठा i2c_driver ar1021_i2c_driver = अणु
	.driver	= अणु
		.name	= "ar1021_i2c",
		.pm	= &ar1021_i2c_pm,
		.of_match_table = ar1021_i2c_of_match,
	पूर्ण,

	.probe		= ar1021_i2c_probe,
	.id_table	= ar1021_i2c_id,
पूर्ण;
module_i2c_driver(ar1021_i2c_driver);

MODULE_AUTHOR("Christian Gmeiner <christian.gmeiner@gmail.com>");
MODULE_DESCRIPTION("Microchip AR1020 and AR1021 I2C Driver");
MODULE_LICENSE("GPL");
