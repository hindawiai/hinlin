<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aपंचांगel Aपंचांगegaxx Capacitive Touch Button Driver
 *
 * Copyright (C) 2016 Google, inc.
 */

/*
 * It's irrelevant that the HW used to develop captouch driver is based
 * on Aपंचांगega88PA part and uses QtouchADC parts क्रम sensing touch.
 * Calling this driver "captouch" is an arbitrary way to distinguish
 * the protocol this driver supported by other aपंचांगel/qtouch drivers.
 *
 * Captouch driver supports a newer/dअगरferent version of the I2C
 * रेजिस्टरs/commands than the qt1070.c driver.
 * Don't let the similarity of the general driver काष्ठाure fool you.
 *
 * For raw i2c access from userspace, use i2cset/i2cget
 * to poke at /dev/i2c-N devices.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

/* Maximum number of buttons supported */
#घोषणा MAX_NUM_OF_BUTTONS		8

/* Registers */
#घोषणा REG_KEY1_THRESHOLD		0x02
#घोषणा REG_KEY2_THRESHOLD		0x03
#घोषणा REG_KEY3_THRESHOLD		0x04
#घोषणा REG_KEY4_THRESHOLD		0x05

#घोषणा REG_KEY1_REF_H			0x20
#घोषणा REG_KEY1_REF_L			0x21
#घोषणा REG_KEY2_REF_H			0x22
#घोषणा REG_KEY2_REF_L			0x23
#घोषणा REG_KEY3_REF_H			0x24
#घोषणा REG_KEY3_REF_L			0x25
#घोषणा REG_KEY4_REF_H			0x26
#घोषणा REG_KEY4_REF_L			0x27

#घोषणा REG_KEY1_DLT_H			0x30
#घोषणा REG_KEY1_DLT_L			0x31
#घोषणा REG_KEY2_DLT_H			0x32
#घोषणा REG_KEY2_DLT_L			0x33
#घोषणा REG_KEY3_DLT_H			0x34
#घोषणा REG_KEY3_DLT_L			0x35
#घोषणा REG_KEY4_DLT_H			0x36
#घोषणा REG_KEY4_DLT_L			0x37

#घोषणा REG_KEY_STATE			0x3C

/*
 * @i2c_client: I2C slave device client poपूर्णांकer
 * @input: Input device poपूर्णांकer
 * @num_btn: Number of buttons
 * @keycodes: map of button# to KeyCode
 * @prev_btn: Previous key state to detect button "press" or "release"
 * @xfer_buf: I2C transfer buffer
 */
काष्ठा aपंचांगel_captouch_device अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	u32 num_btn;
	u32 keycodes[MAX_NUM_OF_BUTTONS];
	u8 prev_btn;
	u8 xfer_buf[8] ____cacheline_aligned;
पूर्ण;

/*
 * Read from I2C slave device
 * The protocol is that the client has to provide both the रेजिस्टर address
 * and the length, and जबतक पढ़ोing back the device would prepend the data
 * with address and length क्रम verअगरication.
 */
अटल पूर्णांक aपंचांगel_पढ़ो(काष्ठा aपंचांगel_captouch_device *capdev,
			 u8 reg, u8 *data, माप_प्रकार len)
अणु
	काष्ठा i2c_client *client = capdev->client;
	काष्ठा device *dev = &client->dev;
	काष्ठा i2c_msg msg[2];
	पूर्णांक err;

	अगर (len > माप(capdev->xfer_buf) - 2)
		वापस -EINVAL;

	capdev->xfer_buf[0] = reg;
	capdev->xfer_buf[1] = len;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].buf = capdev->xfer_buf;
	msg[0].len = 2;

	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].buf = capdev->xfer_buf;
	msg[1].len = len + 2;

	err = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
	अगर (err != ARRAY_SIZE(msg))
		वापस err < 0 ? err : -EIO;

	अगर (capdev->xfer_buf[0] != reg) अणु
		dev_err(dev,
			"I2C read error: register address does not match (%#02x vs %02x)\n",
			capdev->xfer_buf[0], reg);
		वापस -ECOMM;
	पूर्ण

	स_नकल(data, &capdev->xfer_buf[2], len);

	वापस 0;
पूर्ण

/*
 * Handle पूर्णांकerrupt and report the key changes to the input प्रणाली.
 * Multi-touch can be supported; however, it really depends on whether
 * the device can multi-touch.
 */
अटल irqवापस_t aपंचांगel_captouch_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा aपंचांगel_captouch_device *capdev = data;
	काष्ठा device *dev = &capdev->client->dev;
	पूर्णांक error;
	पूर्णांक i;
	u8 new_btn;
	u8 changed_btn;

	error = aपंचांगel_पढ़ो(capdev, REG_KEY_STATE, &new_btn, 1);
	अगर (error) अणु
		dev_err(dev, "failed to read button state: %d\n", error);
		जाओ out;
	पूर्ण

	dev_dbg(dev, "%s: button state %#02x\n", __func__, new_btn);

	changed_btn = new_btn ^ capdev->prev_btn;
	capdev->prev_btn = new_btn;

	क्रम (i = 0; i < capdev->num_btn; i++) अणु
		अगर (changed_btn & BIT(i))
			input_report_key(capdev->input,
					 capdev->keycodes[i],
					 new_btn & BIT(i));
	पूर्ण

	input_sync(capdev->input);

out:
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Probe function to setup the device, input प्रणाली and पूर्णांकerrupt
 */
अटल पूर्णांक aपंचांगel_captouch_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा aपंचांगel_captouch_device *capdev;
	काष्ठा device *dev = &client->dev;
	काष्ठा device_node *node;
	पूर्णांक i;
	पूर्णांक err;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA |
					I2C_FUNC_SMBUS_WORD_DATA |
					I2C_FUNC_SMBUS_I2C_BLOCK)) अणु
		dev_err(dev, "needed i2c functionality is not supported\n");
		वापस -EINVAL;
	पूर्ण

	capdev = devm_kzalloc(dev, माप(*capdev), GFP_KERNEL);
	अगर (!capdev)
		वापस -ENOMEM;

	capdev->client = client;

	err = aपंचांगel_पढ़ो(capdev, REG_KEY_STATE,
			    &capdev->prev_btn, माप(capdev->prev_btn));
	अगर (err) अणु
		dev_err(dev, "failed to read initial button state: %d\n", err);
		वापस err;
	पूर्ण

	capdev->input = devm_input_allocate_device(dev);
	अगर (!capdev->input) अणु
		dev_err(dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	capdev->input->id.bustype = BUS_I2C;
	capdev->input->id.product = 0x880A;
	capdev->input->id.version = 0;
	capdev->input->name = "ATMegaXX Capacitive Button Controller";
	__set_bit(EV_KEY, capdev->input->evbit);

	node = dev->of_node;
	अगर (!node) अणु
		dev_err(dev, "failed to find matching node in device tree\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_bool(node, "autorepeat"))
		__set_bit(EV_REP, capdev->input->evbit);

	capdev->num_btn = of_property_count_u32_elems(node, "linux,keymap");
	अगर (capdev->num_btn > MAX_NUM_OF_BUTTONS)
		capdev->num_btn = MAX_NUM_OF_BUTTONS;

	err = of_property_पढ़ो_u32_array(node, "linux,keycodes",
					 capdev->keycodes,
					 capdev->num_btn);
	अगर (err) अणु
		dev_err(dev,
			"failed to read linux,keycode property: %d\n", err);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < capdev->num_btn; i++)
		__set_bit(capdev->keycodes[i], capdev->input->keybit);

	capdev->input->keycode = capdev->keycodes;
	capdev->input->keycodesize = माप(capdev->keycodes[0]);
	capdev->input->keycodemax = capdev->num_btn;

	err = input_रेजिस्टर_device(capdev->input);
	अगर (err)
		वापस err;

	err = devm_request_thपढ़ोed_irq(dev, client->irq,
					शून्य, aपंचांगel_captouch_isr,
					IRQF_ONESHOT,
					"atmel_captouch", capdev);
	अगर (err) अणु
		dev_err(dev, "failed to request irq %d: %d\n",
			client->irq, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id aपंचांगel_captouch_of_id[] = अणु
	अणु
		.compatible = "atmel,captouch",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_captouch_of_id);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id aपंचांगel_captouch_id[] = अणु
	अणु "atmel_captouch", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, aपंचांगel_captouch_id);

अटल काष्ठा i2c_driver aपंचांगel_captouch_driver = अणु
	.probe		= aपंचांगel_captouch_probe,
	.id_table	= aपंचांगel_captouch_id,
	.driver		= अणु
		.name	= "atmel_captouch",
		.of_match_table = of_match_ptr(aपंचांगel_captouch_of_id),
	पूर्ण,
पूर्ण;
module_i2c_driver(aपंचांगel_captouch_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Hung-yu Wu <hywu@google.com>");
MODULE_DESCRIPTION("Atmel ATmegaXX Capacitance Touch Sensor I2C Driver");
MODULE_LICENSE("GPL v2");
