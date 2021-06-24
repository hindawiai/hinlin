<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  qt2160.c - Aपंचांगel AT42QT2160 Touch Sense Controller
 *
 *  Copyright (C) 2009 Raphael Derosso Pereira <raphaelpereira@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>

#घोषणा QT2160_VALID_CHIPID  0x11

#घोषणा QT2160_CMD_CHIPID     0
#घोषणा QT2160_CMD_CODEVER    1
#घोषणा QT2160_CMD_GSTAT      2
#घोषणा QT2160_CMD_KEYS3      3
#घोषणा QT2160_CMD_KEYS4      4
#घोषणा QT2160_CMD_SLIDE      5
#घोषणा QT2160_CMD_GPIOS      6
#घोषणा QT2160_CMD_SUBVER     7
#घोषणा QT2160_CMD_CALIBRATE  10
#घोषणा QT2160_CMD_DRIVE_X    70
#घोषणा QT2160_CMD_PWMEN_X    74
#घोषणा QT2160_CMD_PWM_DUTY   76

#घोषणा QT2160_NUM_LEDS_X	8

#घोषणा QT2160_CYCLE_INTERVAL	(2*HZ)

अटल अचिन्हित अक्षर qt2160_key2code[] = अणु
	KEY_0, KEY_1, KEY_2, KEY_3,
	KEY_4, KEY_5, KEY_6, KEY_7,
	KEY_8, KEY_9, KEY_A, KEY_B,
	KEY_C, KEY_D, KEY_E, KEY_F,
पूर्ण;

#अगर_घोषित CONFIG_LEDS_CLASS
काष्ठा qt2160_led अणु
	काष्ठा qt2160_data *qt2160;
	काष्ठा led_classdev cdev;
	अक्षर name[32];
	पूर्णांक id;
	क्रमागत led_brightness brightness;
पूर्ण;
#पूर्ण_अगर

काष्ठा qt2160_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा delayed_work dwork;
	अचिन्हित लघु keycodes[ARRAY_SIZE(qt2160_key2code)];
	u16 key_matrix;
#अगर_घोषित CONFIG_LEDS_CLASS
	काष्ठा qt2160_led leds[QT2160_NUM_LEDS_X];
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक qt2160_पढ़ो(काष्ठा i2c_client *client, u8 reg);
अटल पूर्णांक qt2160_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 data);

#अगर_घोषित CONFIG_LEDS_CLASS

अटल पूर्णांक qt2160_led_set(काष्ठा led_classdev *cdev,
			  क्रमागत led_brightness value)
अणु
	काष्ठा qt2160_led *led = container_of(cdev, काष्ठा qt2160_led, cdev);
	काष्ठा qt2160_data *qt2160 = led->qt2160;
	काष्ठा i2c_client *client = qt2160->client;
	u32 drive, pwmen;

	अगर (value != led->brightness) अणु
		drive = qt2160_पढ़ो(client, QT2160_CMD_DRIVE_X);
		pwmen = qt2160_पढ़ो(client, QT2160_CMD_PWMEN_X);
		अगर (value != LED_OFF) अणु
			drive |= BIT(led->id);
			pwmen |= BIT(led->id);

		पूर्ण अन्यथा अणु
			drive &= ~BIT(led->id);
			pwmen &= ~BIT(led->id);
		पूर्ण
		qt2160_ग_लिखो(client, QT2160_CMD_DRIVE_X, drive);
		qt2160_ग_लिखो(client, QT2160_CMD_PWMEN_X, pwmen);

		/*
		 * Changing this रेजिस्टर will change the brightness
		 * of every LED in the qt2160. It's a HW limitation.
		 */
		अगर (value != LED_OFF)
			qt2160_ग_लिखो(client, QT2160_CMD_PWM_DUTY, value);

		led->brightness = value;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_LEDS_CLASS */

अटल पूर्णांक qt2160_पढ़ो_block(काष्ठा i2c_client *client,
			     u8 inireg, u8 *buffer, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक error, idx = 0;

	/*
	 * Can't use SMBus block data पढ़ो. Check क्रम I2C functionality to speed
	 * things up whenever possible. Otherwise we will be क्रमced to पढ़ो
	 * sequentially.
	 */
	अगर (i2c_check_functionality(client->adapter, I2C_FUNC_I2C))	अणु

		error = i2c_smbus_ग_लिखो_byte(client, inireg + idx);
		अगर (error) अणु
			dev_err(&client->dev,
				"couldn't send request. Returned %d\n", error);
			वापस error;
		पूर्ण

		error = i2c_master_recv(client, buffer, count);
		अगर (error != count) अणु
			dev_err(&client->dev,
				"couldn't read registers. Returned %d bytes\n", error);
			वापस error;
		पूर्ण
	पूर्ण अन्यथा अणु

		जबतक (count--) अणु
			पूर्णांक data;

			error = i2c_smbus_ग_लिखो_byte(client, inireg + idx);
			अगर (error) अणु
				dev_err(&client->dev,
					"couldn't send request. Returned %d\n", error);
				वापस error;
			पूर्ण

			data = i2c_smbus_पढ़ो_byte(client);
			अगर (data < 0) अणु
				dev_err(&client->dev,
					"couldn't read register. Returned %d\n", data);
				वापस data;
			पूर्ण

			buffer[idx++] = data;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qt2160_get_key_matrix(काष्ठा qt2160_data *qt2160)
अणु
	काष्ठा i2c_client *client = qt2160->client;
	काष्ठा input_dev *input = qt2160->input;
	u8 regs[6];
	u16 old_matrix, new_matrix;
	पूर्णांक ret, i, mask;

	dev_dbg(&client->dev, "requesting keys...\n");

	/*
	 * Read all रेजिस्टरs from General Status Register
	 * to GPIOs रेजिस्टर
	 */
	ret = qt2160_पढ़ो_block(client, QT2160_CMD_GSTAT, regs, 6);
	अगर (ret) अणु
		dev_err(&client->dev,
			"could not perform chip read.\n");
		वापस ret;
	पूर्ण

	old_matrix = qt2160->key_matrix;
	qt2160->key_matrix = new_matrix = (regs[2] << 8) | regs[1];

	mask = 0x01;
	क्रम (i = 0; i < 16; ++i, mask <<= 1) अणु
		पूर्णांक keyval = new_matrix & mask;

		अगर ((old_matrix & mask) != keyval) अणु
			input_report_key(input, qt2160->keycodes[i], keyval);
			dev_dbg(&client->dev, "key %d %s\n",
				i, keyval ? "pressed" : "released");
		पूर्ण
	पूर्ण

	input_sync(input);

	वापस 0;
पूर्ण

अटल irqवापस_t qt2160_irq(पूर्णांक irq, व्योम *_qt2160)
अणु
	काष्ठा qt2160_data *qt2160 = _qt2160;

	mod_delayed_work(प्रणाली_wq, &qt2160->dwork, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम qt2160_schedule_पढ़ो(काष्ठा qt2160_data *qt2160)
अणु
	schedule_delayed_work(&qt2160->dwork, QT2160_CYCLE_INTERVAL);
पूर्ण

अटल व्योम qt2160_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qt2160_data *qt2160 =
		container_of(work, काष्ठा qt2160_data, dwork.work);

	dev_dbg(&qt2160->client->dev, "worker\n");

	qt2160_get_key_matrix(qt2160);

	/* Aव्योम device lock up by checking every so often */
	qt2160_schedule_पढ़ो(qt2160);
पूर्ण

अटल पूर्णांक qt2160_पढ़ो(काष्ठा i2c_client *client, u8 reg)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte(client, reg);
	अगर (ret) अणु
		dev_err(&client->dev,
			"couldn't send request. Returned %d\n", ret);
		वापस ret;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte(client);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"couldn't read register. Returned %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qt2160_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 data)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, reg, data);
	अगर (ret < 0)
		dev_err(&client->dev,
			"couldn't write data. Returned %d\n", ret);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_LEDS_CLASS

अटल पूर्णांक qt2160_रेजिस्टर_leds(काष्ठा qt2160_data *qt2160)
अणु
	काष्ठा i2c_client *client = qt2160->client;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < QT2160_NUM_LEDS_X; i++) अणु
		काष्ठा qt2160_led *led = &qt2160->leds[i];

		snम_लिखो(led->name, माप(led->name), "qt2160:x%d", i);
		led->cdev.name = led->name;
		led->cdev.brightness_set_blocking = qt2160_led_set;
		led->cdev.brightness = LED_OFF;
		led->id = i;
		led->qt2160 = qt2160;

		ret = led_classdev_रेजिस्टर(&client->dev, &led->cdev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Tur off LEDs */
	qt2160_ग_लिखो(client, QT2160_CMD_DRIVE_X, 0);
	qt2160_ग_लिखो(client, QT2160_CMD_PWMEN_X, 0);
	qt2160_ग_लिखो(client, QT2160_CMD_PWM_DUTY, 0);

	वापस 0;
पूर्ण

अटल व्योम qt2160_unरेजिस्टर_leds(काष्ठा qt2160_data *qt2160)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < QT2160_NUM_LEDS_X; i++)
		led_classdev_unरेजिस्टर(&qt2160->leds[i].cdev);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक qt2160_रेजिस्टर_leds(काष्ठा qt2160_data *qt2160)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qt2160_unरेजिस्टर_leds(काष्ठा qt2160_data *qt2160)
अणु
पूर्ण

#पूर्ण_अगर

अटल bool qt2160_identअगरy(काष्ठा i2c_client *client)
अणु
	पूर्णांक id, ver, rev;

	/* Read Chid ID to check अगर chip is valid */
	id = qt2160_पढ़ो(client, QT2160_CMD_CHIPID);
	अगर (id != QT2160_VALID_CHIPID) अणु
		dev_err(&client->dev, "ID %d not supported\n", id);
		वापस false;
	पूर्ण

	/* Read chip firmware version */
	ver = qt2160_पढ़ो(client, QT2160_CMD_CODEVER);
	अगर (ver < 0) अणु
		dev_err(&client->dev, "could not get firmware version\n");
		वापस false;
	पूर्ण

	/* Read chip firmware revision */
	rev = qt2160_पढ़ो(client, QT2160_CMD_SUBVER);
	अगर (rev < 0) अणु
		dev_err(&client->dev, "could not get firmware revision\n");
		वापस false;
	पूर्ण

	dev_info(&client->dev, "AT42QT2160 firmware version %d.%d.%d\n",
			ver >> 4, ver & 0xf, rev);

	वापस true;
पूर्ण

अटल पूर्णांक qt2160_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा qt2160_data *qt2160;
	काष्ठा input_dev *input;
	पूर्णांक i;
	पूर्णांक error;

	/* Check functionality */
	error = i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_BYTE);
	अगर (!error) अणु
		dev_err(&client->dev, "%s adapter not supported\n",
				dev_driver_string(&client->adapter->dev));
		वापस -ENODEV;
	पूर्ण

	अगर (!qt2160_identअगरy(client))
		वापस -ENODEV;

	/* Chip is valid and active. Allocate काष्ठाure */
	qt2160 = kzalloc(माप(काष्ठा qt2160_data), GFP_KERNEL);
	input = input_allocate_device();
	अगर (!qt2160 || !input) अणु
		dev_err(&client->dev, "insufficient memory\n");
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	qt2160->client = client;
	qt2160->input = input;
	INIT_DELAYED_WORK(&qt2160->dwork, qt2160_worker);

	input->name = "AT42QT2160 Touch Sense Keyboard";
	input->id.bustype = BUS_I2C;

	input->keycode = qt2160->keycodes;
	input->keycodesize = माप(qt2160->keycodes[0]);
	input->keycodemax = ARRAY_SIZE(qt2160_key2code);

	__set_bit(EV_KEY, input->evbit);
	__clear_bit(EV_REP, input->evbit);
	क्रम (i = 0; i < ARRAY_SIZE(qt2160_key2code); i++) अणु
		qt2160->keycodes[i] = qt2160_key2code[i];
		__set_bit(qt2160_key2code[i], input->keybit);
	पूर्ण
	__clear_bit(KEY_RESERVED, input->keybit);

	/* Calibrate device */
	error = qt2160_ग_लिखो(client, QT2160_CMD_CALIBRATE, 1);
	अगर (error) अणु
		dev_err(&client->dev, "failed to calibrate device\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	अगर (client->irq) अणु
		error = request_irq(client->irq, qt2160_irq,
				    IRQF_TRIGGER_FALLING, "qt2160", qt2160);
		अगर (error) अणु
			dev_err(&client->dev,
				"failed to allocate irq %d\n", client->irq);
			जाओ err_मुक्त_mem;
		पूर्ण
	पूर्ण

	error = qt2160_रेजिस्टर_leds(qt2160);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to register leds\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	error = input_रेजिस्टर_device(qt2160->input);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to register input device\n");
		जाओ err_unरेजिस्टर_leds;
	पूर्ण

	i2c_set_clientdata(client, qt2160);
	qt2160_schedule_पढ़ो(qt2160);

	वापस 0;

err_unरेजिस्टर_leds:
	qt2160_unरेजिस्टर_leds(qt2160);
err_मुक्त_irq:
	अगर (client->irq)
		मुक्त_irq(client->irq, qt2160);
err_मुक्त_mem:
	input_मुक्त_device(input);
	kमुक्त(qt2160);
	वापस error;
पूर्ण

अटल पूर्णांक qt2160_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा qt2160_data *qt2160 = i2c_get_clientdata(client);

	qt2160_unरेजिस्टर_leds(qt2160);

	/* Release IRQ so no queue will be scheduled */
	अगर (client->irq)
		मुक्त_irq(client->irq, qt2160);

	cancel_delayed_work_sync(&qt2160->dwork);

	input_unरेजिस्टर_device(qt2160->input);
	kमुक्त(qt2160);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id qt2160_idtable[] = अणु
	अणु "qt2160", 0, पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, qt2160_idtable);

अटल काष्ठा i2c_driver qt2160_driver = अणु
	.driver = अणु
		.name	= "qt2160",
	पूर्ण,

	.id_table	= qt2160_idtable,
	.probe		= qt2160_probe,
	.हटाओ		= qt2160_हटाओ,
पूर्ण;

module_i2c_driver(qt2160_driver);

MODULE_AUTHOR("Raphael Derosso Pereira <raphaelpereira@gmail.com>");
MODULE_DESCRIPTION("Driver for AT42QT2160 Touch Sensor");
MODULE_LICENSE("GPL");
