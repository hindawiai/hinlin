<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Microchip AT42QT1050 QTouch Sensor Controller
 *
 *  Copyright (C) 2019 Pengutronix, Marco Felsch <kernel@pengutronix.de>
 *
 *  Base on AT42QT1070 driver by:
 *  Bo Shen <voice.shen@aपंचांगel.com>
 *  Copyright (C) 2011 Aपंचांगel
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

/* Chip ID */
#घोषणा QT1050_CHIP_ID		0x00
#घोषणा QT1050_CHIP_ID_VER	0x46

/* Firmware version */
#घोषणा QT1050_FW_VERSION	0x01

/* Detection status */
#घोषणा QT1050_DET_STATUS	0x02

/* Key status */
#घोषणा QT1050_KEY_STATUS	0x03

/* Key Signals */
#घोषणा QT1050_KEY_SIGNAL_0_MSB	0x06
#घोषणा QT1050_KEY_SIGNAL_0_LSB	0x07
#घोषणा QT1050_KEY_SIGNAL_1_MSB	0x08
#घोषणा QT1050_KEY_SIGNAL_1_LSB	0x09
#घोषणा QT1050_KEY_SIGNAL_2_MSB	0x0c
#घोषणा QT1050_KEY_SIGNAL_2_LSB	0x0d
#घोषणा QT1050_KEY_SIGNAL_3_MSB	0x0e
#घोषणा QT1050_KEY_SIGNAL_3_LSB	0x0f
#घोषणा QT1050_KEY_SIGNAL_4_MSB	0x10
#घोषणा QT1050_KEY_SIGNAL_4_LSB	0x11

/* Reference data */
#घोषणा QT1050_REF_DATA_0_MSB	0x14
#घोषणा QT1050_REF_DATA_0_LSB	0x15
#घोषणा QT1050_REF_DATA_1_MSB	0x16
#घोषणा QT1050_REF_DATA_1_LSB	0x17
#घोषणा QT1050_REF_DATA_2_MSB	0x1a
#घोषणा QT1050_REF_DATA_2_LSB	0x1b
#घोषणा QT1050_REF_DATA_3_MSB	0x1c
#घोषणा QT1050_REF_DATA_3_LSB	0x1d
#घोषणा QT1050_REF_DATA_4_MSB	0x1e
#घोषणा QT1050_REF_DATA_4_LSB	0x1f

/* Negative threshold level */
#घोषणा QT1050_NTHR_0		0x21
#घोषणा QT1050_NTHR_1		0x22
#घोषणा QT1050_NTHR_2		0x24
#घोषणा QT1050_NTHR_3		0x25
#घोषणा QT1050_NTHR_4		0x26

/* Pulse / Scale  */
#घोषणा QT1050_PULSE_SCALE_0	0x28
#घोषणा QT1050_PULSE_SCALE_1	0x29
#घोषणा QT1050_PULSE_SCALE_2	0x2b
#घोषणा QT1050_PULSE_SCALE_3	0x2c
#घोषणा QT1050_PULSE_SCALE_4	0x2d

/* Detection पूर्णांकegrator counter / AKS */
#घोषणा QT1050_DI_AKS_0		0x2f
#घोषणा QT1050_DI_AKS_1		0x30
#घोषणा QT1050_DI_AKS_2		0x32
#घोषणा QT1050_DI_AKS_3		0x33
#घोषणा QT1050_DI_AKS_4		0x34

/* Charge Share Delay */
#घोषणा QT1050_CSD_0		0x36
#घोषणा QT1050_CSD_1		0x37
#घोषणा QT1050_CSD_2		0x39
#घोषणा QT1050_CSD_3		0x3a
#घोषणा QT1050_CSD_4		0x3b

/* Low Power Mode */
#घोषणा QT1050_LPMODE		0x3d

/* Calibration and Reset */
#घोषणा QT1050_RES_CAL		0x3f
#घोषणा QT1050_RES_CAL_RESET		BIT(7)
#घोषणा QT1050_RES_CAL_CALIBRATE	BIT(1)

#घोषणा QT1050_MAX_KEYS		5
#घोषणा QT1050_RESET_TIME	255

काष्ठा qt1050_key_regs अणु
	अचिन्हित पूर्णांक nthr;
	अचिन्हित पूर्णांक pulse_scale;
	अचिन्हित पूर्णांक di_aks;
	अचिन्हित पूर्णांक csd;
पूर्ण;

काष्ठा qt1050_key अणु
	u32 num;
	u32 अक्षरge_delay;
	u32 thr_cnt;
	u32 samples;
	u32 scale;
	u32 keycode;
पूर्ण;

काष्ठा qt1050_priv अणु
	काष्ठा i2c_client	*client;
	काष्ठा input_dev	*input;
	काष्ठा regmap		*regmap;
	काष्ठा qt1050_key	keys[QT1050_MAX_KEYS];
	अचिन्हित लघु		keycodes[QT1050_MAX_KEYS];
	u8			reg_keys;
	u8			last_keys;
पूर्ण;

अटल स्थिर काष्ठा qt1050_key_regs qt1050_key_regs_data[] = अणु
	अणु
		.nthr = QT1050_NTHR_0,
		.pulse_scale = QT1050_PULSE_SCALE_0,
		.di_aks = QT1050_DI_AKS_0,
		.csd = QT1050_CSD_0,
	पूर्ण, अणु
		.nthr = QT1050_NTHR_1,
		.pulse_scale = QT1050_PULSE_SCALE_1,
		.di_aks = QT1050_DI_AKS_1,
		.csd = QT1050_CSD_1,
	पूर्ण, अणु
		.nthr = QT1050_NTHR_2,
		.pulse_scale = QT1050_PULSE_SCALE_2,
		.di_aks = QT1050_DI_AKS_2,
		.csd = QT1050_CSD_2,
	पूर्ण, अणु
		.nthr = QT1050_NTHR_3,
		.pulse_scale = QT1050_PULSE_SCALE_3,
		.di_aks = QT1050_DI_AKS_3,
		.csd = QT1050_CSD_3,
	पूर्ण, अणु
		.nthr = QT1050_NTHR_4,
		.pulse_scale = QT1050_PULSE_SCALE_4,
		.di_aks = QT1050_DI_AKS_4,
		.csd = QT1050_CSD_4,
	पूर्ण
पूर्ण;

अटल bool qt1050_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल QT1050_DET_STATUS:
	हाल QT1050_KEY_STATUS:
	हाल QT1050_KEY_SIGNAL_0_MSB:
	हाल QT1050_KEY_SIGNAL_0_LSB:
	हाल QT1050_KEY_SIGNAL_1_MSB:
	हाल QT1050_KEY_SIGNAL_1_LSB:
	हाल QT1050_KEY_SIGNAL_2_MSB:
	हाल QT1050_KEY_SIGNAL_2_LSB:
	हाल QT1050_KEY_SIGNAL_3_MSB:
	हाल QT1050_KEY_SIGNAL_3_LSB:
	हाल QT1050_KEY_SIGNAL_4_MSB:
	हाल QT1050_KEY_SIGNAL_4_LSB:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_range qt1050_पढ़ोable_ranges[] = अणु
	regmap_reg_range(QT1050_CHIP_ID, QT1050_KEY_STATUS),
	regmap_reg_range(QT1050_KEY_SIGNAL_0_MSB, QT1050_KEY_SIGNAL_1_LSB),
	regmap_reg_range(QT1050_KEY_SIGNAL_2_MSB, QT1050_KEY_SIGNAL_4_LSB),
	regmap_reg_range(QT1050_REF_DATA_0_MSB, QT1050_REF_DATA_1_LSB),
	regmap_reg_range(QT1050_REF_DATA_2_MSB, QT1050_REF_DATA_4_LSB),
	regmap_reg_range(QT1050_NTHR_0, QT1050_NTHR_1),
	regmap_reg_range(QT1050_NTHR_2, QT1050_NTHR_4),
	regmap_reg_range(QT1050_PULSE_SCALE_0, QT1050_PULSE_SCALE_1),
	regmap_reg_range(QT1050_PULSE_SCALE_2, QT1050_PULSE_SCALE_4),
	regmap_reg_range(QT1050_DI_AKS_0, QT1050_DI_AKS_1),
	regmap_reg_range(QT1050_DI_AKS_2, QT1050_DI_AKS_4),
	regmap_reg_range(QT1050_CSD_0, QT1050_CSD_1),
	regmap_reg_range(QT1050_CSD_2, QT1050_RES_CAL),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table qt1050_पढ़ोable_table = अणु
	.yes_ranges = qt1050_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(qt1050_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range qt1050_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(QT1050_NTHR_0, QT1050_NTHR_1),
	regmap_reg_range(QT1050_NTHR_2, QT1050_NTHR_4),
	regmap_reg_range(QT1050_PULSE_SCALE_0, QT1050_PULSE_SCALE_1),
	regmap_reg_range(QT1050_PULSE_SCALE_2, QT1050_PULSE_SCALE_4),
	regmap_reg_range(QT1050_DI_AKS_0, QT1050_DI_AKS_1),
	regmap_reg_range(QT1050_DI_AKS_2, QT1050_DI_AKS_4),
	regmap_reg_range(QT1050_CSD_0, QT1050_CSD_1),
	regmap_reg_range(QT1050_CSD_2, QT1050_RES_CAL),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table qt1050_ग_लिखोable_table = अणु
	.yes_ranges = qt1050_ग_लिखोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(qt1050_ग_लिखोable_ranges),
पूर्ण;

अटल काष्ठा regmap_config qt1050_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = QT1050_RES_CAL,

	.cache_type = REGCACHE_RBTREE,

	.wr_table = &qt1050_ग_लिखोable_table,
	.rd_table = &qt1050_पढ़ोable_table,
	.अस्थिर_reg = qt1050_अस्थिर_reg,
पूर्ण;

अटल bool qt1050_identअगरy(काष्ठा qt1050_priv *ts)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	/* Read Chip ID */
	regmap_पढ़ो(ts->regmap, QT1050_CHIP_ID, &val);
	अगर (val != QT1050_CHIP_ID_VER) अणु
		dev_err(&ts->client->dev, "ID %d not supported\n", val);
		वापस false;
	पूर्ण

	/* Read firmware version */
	err = regmap_पढ़ो(ts->regmap, QT1050_FW_VERSION, &val);
	अगर (err) अणु
		dev_err(&ts->client->dev, "could not read the firmware version\n");
		वापस false;
	पूर्ण

	dev_info(&ts->client->dev, "AT42QT1050 firmware version %1d.%1d\n",
		 val >> 4, val & 0xf);

	वापस true;
पूर्ण

अटल irqवापस_t qt1050_irq_thपढ़ोed(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा qt1050_priv *ts = dev_id;
	काष्ठा input_dev *input = ts->input;
	अचिन्हित दीर्घ new_keys, changed;
	अचिन्हित पूर्णांक val;
	पूर्णांक i, err;

	/* Read the detected status रेजिस्टर, thus clearing पूर्णांकerrupt */
	err = regmap_पढ़ो(ts->regmap, QT1050_DET_STATUS, &val);
	अगर (err) अणु
		dev_err(&ts->client->dev, "Fail to read detection status: %d\n",
			err);
		वापस IRQ_NONE;
	पूर्ण

	/* Read which key changed, keys are not continuous */
	err = regmap_पढ़ो(ts->regmap, QT1050_KEY_STATUS, &val);
	अगर (err) अणु
		dev_err(&ts->client->dev,
			"Fail to determine the key status: %d\n", err);
		वापस IRQ_NONE;
	पूर्ण
	new_keys = (val & 0x70) >> 2 | (val & 0x6) >> 1;
	changed = ts->last_keys ^ new_keys;
	/* Report रेजिस्टरed keys only */
	changed &= ts->reg_keys;

	क्रम_each_set_bit(i, &changed, QT1050_MAX_KEYS)
		input_report_key(input, ts->keys[i].keycode,
				 test_bit(i, &new_keys));

	ts->last_keys = new_keys;
	input_sync(input);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा qt1050_key_regs *qt1050_get_key_regs(पूर्णांक key_num)
अणु
	वापस &qt1050_key_regs_data[key_num];
पूर्ण

अटल पूर्णांक qt1050_set_key(काष्ठा regmap *map, पूर्णांक number, पूर्णांक on)
अणु
	स्थिर काष्ठा qt1050_key_regs *key_regs;

	key_regs = qt1050_get_key_regs(number);

	वापस regmap_update_bits(map, key_regs->di_aks, 0xfc,
				  on ? BIT(4) : 0x00);
पूर्ण

अटल पूर्णांक qt1050_apply_fw_data(काष्ठा qt1050_priv *ts)
अणु
	काष्ठा regmap *map = ts->regmap;
	काष्ठा qt1050_key *button = &ts->keys[0];
	स्थिर काष्ठा qt1050_key_regs *key_regs;
	पूर्णांक i, err;

	/* Disable all keys and enable only the specअगरied ones */
	क्रम (i = 0; i < QT1050_MAX_KEYS; i++) अणु
		err = qt1050_set_key(map, i, 0);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < QT1050_MAX_KEYS; i++, button++) अणु
		/* Keep KEY_RESERVED keys off */
		अगर (button->keycode == KEY_RESERVED)
			जारी;

		err = qt1050_set_key(map, button->num, 1);
		अगर (err)
			वापस err;

		key_regs = qt1050_get_key_regs(button->num);

		err = regmap_ग_लिखो(map, key_regs->pulse_scale,
				   (button->samples << 4) | (button->scale));
		अगर (err)
			वापस err;
		err = regmap_ग_लिखो(map, key_regs->csd, button->अक्षरge_delay);
		अगर (err)
			वापस err;
		err = regmap_ग_लिखो(map, key_regs->nthr, button->thr_cnt);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qt1050_parse_fw(काष्ठा qt1050_priv *ts)
अणु
	काष्ठा device *dev = &ts->client->dev;
	काष्ठा fwnode_handle *child;
	पूर्णांक nbuttons;

	nbuttons = device_get_child_node_count(dev);
	अगर (nbuttons == 0 || nbuttons > QT1050_MAX_KEYS)
		वापस -ENODEV;

	device_क्रम_each_child_node(dev, child) अणु
		काष्ठा qt1050_key button;

		/* Required properties */
		अगर (fwnode_property_पढ़ो_u32(child, "linux,code",
					     &button.keycode)) अणु
			dev_err(dev, "Button without keycode\n");
			जाओ err;
		पूर्ण
		अगर (button.keycode >= KEY_MAX) अणु
			dev_err(dev, "Invalid keycode 0x%x\n",
				button.keycode);
			जाओ err;
		पूर्ण

		अगर (fwnode_property_पढ़ो_u32(child, "reg",
					     &button.num)) अणु
			dev_err(dev, "Button without pad number\n");
			जाओ err;
		पूर्ण
		अगर (button.num < 0 || button.num > QT1050_MAX_KEYS - 1)
			जाओ err;

		ts->reg_keys |= BIT(button.num);

		/* Optional properties */
		अगर (fwnode_property_पढ़ो_u32(child,
					     "microchip,pre-charge-time-ns",
					     &button.अक्षरge_delay)) अणु
			button.अक्षरge_delay = 0;
		पूर्ण अन्यथा अणु
			अगर (button.अक्षरge_delay % 2500 == 0)
				button.अक्षरge_delay =
					button.अक्षरge_delay / 2500;
			अन्यथा
				button.अक्षरge_delay = 0;
		पूर्ण

		अगर (fwnode_property_पढ़ो_u32(child, "microchip,average-samples",
					 &button.samples)) अणु
			button.samples = 0;
		पूर्ण अन्यथा अणु
			अगर (is_घातer_of_2(button.samples))
				button.samples = ilog2(button.samples);
			अन्यथा
				button.samples = 0;
		पूर्ण

		अगर (fwnode_property_पढ़ो_u32(child, "microchip,average-scaling",
					     &button.scale)) अणु
			button.scale = 0;
		पूर्ण अन्यथा अणु
			अगर (is_घातer_of_2(button.scale))
				button.scale = ilog2(button.scale);
			अन्यथा
				button.scale = 0;

		पूर्ण

		अगर (fwnode_property_पढ़ो_u32(child, "microchip,threshold",
					 &button.thr_cnt)) अणु
			button.thr_cnt = 20;
		पूर्ण अन्यथा अणु
			अगर (button.thr_cnt > 255)
				button.thr_cnt = 20;
		पूर्ण

		ts->keys[button.num] = button;
	पूर्ण

	वापस 0;

err:
	fwnode_handle_put(child);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक qt1050_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा qt1050_priv *ts;
	काष्ठा input_dev *input;
	काष्ठा device *dev = &client->dev;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक status, i;
	पूर्णांक err;

	/* Check basic functionality */
	err = i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE);
	अगर (!err) अणु
		dev_err(&client->dev, "%s adapter not supported\n",
			dev_driver_string(&client->adapter->dev));
		वापस -ENODEV;
	पूर्ण

	अगर (!client->irq) अणु
		dev_err(dev, "assign a irq line to this device\n");
		वापस -EINVAL;
	पूर्ण

	ts = devm_kzalloc(dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	map = devm_regmap_init_i2c(client, &qt1050_regmap_config);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	ts->client = client;
	ts->input = input;
	ts->regmap = map;

	i2c_set_clientdata(client, ts);

	/* Identअगरy the qt1050 chip */
	अगर (!qt1050_identअगरy(ts))
		वापस -ENODEV;

	/* Get pdata */
	err = qt1050_parse_fw(ts);
	अगर (err) अणु
		dev_err(dev, "Failed to parse firmware: %d\n", err);
		वापस err;
	पूर्ण

	input->name = "AT42QT1050 QTouch Sensor";
	input->dev.parent = &client->dev;
	input->id.bustype = BUS_I2C;

	/* Add the keycode */
	input->keycode = ts->keycodes;
	input->keycodesize = माप(ts->keycodes[0]);
	input->keycodemax = QT1050_MAX_KEYS;

	__set_bit(EV_KEY, input->evbit);
	क्रम (i = 0; i < QT1050_MAX_KEYS; i++) अणु
		ts->keycodes[i] = ts->keys[i].keycode;
		__set_bit(ts->keycodes[i], input->keybit);
	पूर्ण

	/* Trigger re-calibration */
	err = regmap_update_bits(ts->regmap, QT1050_RES_CAL, 0x7f,
				 QT1050_RES_CAL_CALIBRATE);
	अगर (err) अणु
		dev_err(dev, "Trigger calibration failed: %d\n", err);
		वापस err;
	पूर्ण
	err = regmap_पढ़ो_poll_समयout(ts->regmap, QT1050_DET_STATUS, status,
				 status >> 7 == 1, 10000, 200000);
	अगर (err) अणु
		dev_err(dev, "Calibration failed: %d\n", err);
		वापस err;
	पूर्ण

	/* Soft reset to set शेषs */
	err = regmap_update_bits(ts->regmap, QT1050_RES_CAL,
				 QT1050_RES_CAL_RESET, QT1050_RES_CAL_RESET);
	अगर (err) अणु
		dev_err(dev, "Trigger soft reset failed: %d\n", err);
		वापस err;
	पूर्ण
	msleep(QT1050_RESET_TIME);

	/* Set pdata */
	err = qt1050_apply_fw_data(ts);
	अगर (err) अणु
		dev_err(dev, "Failed to set firmware data: %d\n", err);
		वापस err;
	पूर्ण

	err = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
					qt1050_irq_thपढ़ोed, IRQF_ONESHOT,
					"qt1050", ts);
	अगर (err) अणु
		dev_err(&client->dev, "Failed to request irq: %d\n", err);
		वापस err;
	पूर्ण

	/* Clear #CHANGE line */
	err = regmap_पढ़ो(ts->regmap, QT1050_DET_STATUS, &status);
	अगर (err) अणु
		dev_err(dev, "Failed to clear #CHANGE line level: %d\n", err);
		वापस err;
	पूर्ण

	/* Register the input device */
	err = input_रेजिस्टर_device(ts->input);
	अगर (err) अणु
		dev_err(&client->dev, "Failed to register input device: %d\n",
			err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qt1050_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा qt1050_priv *ts = i2c_get_clientdata(client);

	disable_irq(client->irq);

	/*
	 * Set measurement पूर्णांकerval to 1s (125 x 8ms) अगर wakeup is allowed
	 * अन्यथा turn off. The 1s पूर्णांकerval seems to be a good compromise between
	 * low घातer and response समय.
	 */
	वापस regmap_ग_लिखो(ts->regmap, QT1050_LPMODE,
			    device_may_wakeup(dev) ? 125 : 0);
पूर्ण

अटल पूर्णांक __maybe_unused qt1050_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा qt1050_priv *ts = i2c_get_clientdata(client);

	enable_irq(client->irq);

	/* Set measurement पूर्णांकerval back to 16ms (2 x 8ms) */
	वापस regmap_ग_लिखो(ts->regmap, QT1050_LPMODE, 2);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(qt1050_pm_ops, qt1050_suspend, qt1050_resume);

अटल स्थिर काष्ठा of_device_id __maybe_unused qt1050_of_match[] = अणु
	अणु .compatible = "microchip,qt1050", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, qt1050_of_match);

अटल काष्ठा i2c_driver qt1050_driver = अणु
	.driver	= अणु
		.name = "qt1050",
		.of_match_table = of_match_ptr(qt1050_of_match),
		.pm = &qt1050_pm_ops,
	पूर्ण,
	.probe_new = qt1050_probe,
पूर्ण;

module_i2c_driver(qt1050_driver);

MODULE_AUTHOR("Marco Felsch <kernel@pengutronix.de");
MODULE_DESCRIPTION("Driver for AT42QT1050 QTouch sensor");
MODULE_LICENSE("GPL v2");
