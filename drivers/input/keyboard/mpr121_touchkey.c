<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Touchkey driver क्रम Freescale MPR121 Controllor
 *
 * Copyright (C) 2011 Freescale Semiconductor, Inc.
 * Author: Zhang Jiejing <jiejing.zhang@मुक्तscale.com>
 *
 * Based on mcs_touchkey.c
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

/* Register definitions */
#घोषणा ELE_TOUCH_STATUS_0_ADDR	0x0
#घोषणा ELE_TOUCH_STATUS_1_ADDR	0X1
#घोषणा MHD_RISING_ADDR		0x2b
#घोषणा NHD_RISING_ADDR		0x2c
#घोषणा NCL_RISING_ADDR		0x2d
#घोषणा FDL_RISING_ADDR		0x2e
#घोषणा MHD_FALLING_ADDR	0x2f
#घोषणा NHD_FALLING_ADDR	0x30
#घोषणा NCL_FALLING_ADDR	0x31
#घोषणा FDL_FALLING_ADDR	0x32
#घोषणा ELE0_TOUCH_THRESHOLD_ADDR	0x41
#घोषणा ELE0_RELEASE_THRESHOLD_ADDR	0x42
#घोषणा AFE_CONF_ADDR			0x5c
#घोषणा FILTER_CONF_ADDR		0x5d

/*
 * ELECTRODE_CONF_ADDR: This रेजिस्टर configures the number of
 * enabled capacitance sensing inमाला_दो and its run/suspend mode.
 */
#घोषणा ELECTRODE_CONF_ADDR		0x5e
#घोषणा ELECTRODE_CONF_QUICK_CHARGE	0x80
#घोषणा AUTO_CONFIG_CTRL_ADDR		0x7b
#घोषणा AUTO_CONFIG_USL_ADDR		0x7d
#घोषणा AUTO_CONFIG_LSL_ADDR		0x7e
#घोषणा AUTO_CONFIG_TL_ADDR		0x7f

/* Threshold of touch/release trigger */
#घोषणा TOUCH_THRESHOLD			0x08
#घोषणा RELEASE_THRESHOLD		0x05
/* Masks क्रम touch and release triggers */
#घोषणा TOUCH_STATUS_MASK		0xfff
/* MPR121 has 12 keys */
#घोषणा MPR121_MAX_KEY_COUNT		12

#घोषणा MPR121_MIN_POLL_INTERVAL	10
#घोषणा MPR121_MAX_POLL_INTERVAL	200

काष्ठा mpr121_touchkey अणु
	काष्ठा i2c_client	*client;
	काष्ठा input_dev	*input_dev;
	अचिन्हित पूर्णांक		statusbits;
	अचिन्हित पूर्णांक		keycount;
	u32			keycodes[MPR121_MAX_KEY_COUNT];
पूर्ण;

काष्ठा mpr121_init_रेजिस्टर अणु
	पूर्णांक addr;
	u8 val;
पूर्ण;

अटल स्थिर काष्ठा mpr121_init_रेजिस्टर init_reg_table[] = अणु
	अणु MHD_RISING_ADDR,	0x1 पूर्ण,
	अणु NHD_RISING_ADDR,	0x1 पूर्ण,
	अणु MHD_FALLING_ADDR,	0x1 पूर्ण,
	अणु NHD_FALLING_ADDR,	0x1 पूर्ण,
	अणु NCL_FALLING_ADDR,	0xff पूर्ण,
	अणु FDL_FALLING_ADDR,	0x02 पूर्ण,
	अणु FILTER_CONF_ADDR,	0x04 पूर्ण,
	अणु AFE_CONF_ADDR,	0x0b पूर्ण,
	अणु AUTO_CONFIG_CTRL_ADDR, 0x0b पूर्ण,
पूर्ण;

अटल व्योम mpr121_vdd_supply_disable(व्योम *data)
अणु
	काष्ठा regulator *vdd_supply = data;

	regulator_disable(vdd_supply);
पूर्ण

अटल काष्ठा regulator *mpr121_vdd_supply_init(काष्ठा device *dev)
अणु
	काष्ठा regulator *vdd_supply;
	पूर्णांक err;

	vdd_supply = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(vdd_supply)) अणु
		dev_err(dev, "failed to get vdd regulator: %ld\n",
			PTR_ERR(vdd_supply));
		वापस vdd_supply;
	पूर्ण

	err = regulator_enable(vdd_supply);
	अगर (err) अणु
		dev_err(dev, "failed to enable vdd regulator: %d\n", err);
		वापस ERR_PTR(err);
	पूर्ण

	err = devm_add_action(dev, mpr121_vdd_supply_disable, vdd_supply);
	अगर (err) अणु
		regulator_disable(vdd_supply);
		dev_err(dev, "failed to add disable regulator action: %d\n",
			err);
		वापस ERR_PTR(err);
	पूर्ण

	वापस vdd_supply;
पूर्ण

अटल व्योम mpr_touchkey_report(काष्ठा input_dev *dev)
अणु
	काष्ठा mpr121_touchkey *mpr121 = input_get_drvdata(dev);
	काष्ठा input_dev *input = mpr121->input_dev;
	काष्ठा i2c_client *client = mpr121->client;
	अचिन्हित दीर्घ bit_changed;
	अचिन्हित पूर्णांक key_num;
	पूर्णांक reg;

	reg = i2c_smbus_पढ़ो_byte_data(client, ELE_TOUCH_STATUS_1_ADDR);
	अगर (reg < 0) अणु
		dev_err(&client->dev, "i2c read error [%d]\n", reg);
		वापस;
	पूर्ण

	reg <<= 8;
	reg |= i2c_smbus_पढ़ो_byte_data(client, ELE_TOUCH_STATUS_0_ADDR);
	अगर (reg < 0) अणु
		dev_err(&client->dev, "i2c read error [%d]\n", reg);
		वापस;
	पूर्ण

	reg &= TOUCH_STATUS_MASK;
	/* use old press bit to figure out which bit changed */
	bit_changed = reg ^ mpr121->statusbits;
	mpr121->statusbits = reg;
	क्रम_each_set_bit(key_num, &bit_changed, mpr121->keycount) अणु
		अचिन्हित पूर्णांक key_val, pressed;

		pressed = reg & BIT(key_num);
		key_val = mpr121->keycodes[key_num];

		input_event(input, EV_MSC, MSC_SCAN, key_num);
		input_report_key(input, key_val, pressed);

		dev_dbg(&client->dev, "key %d %d %s\n", key_num, key_val,
			pressed ? "pressed" : "released");

	पूर्ण
	input_sync(input);
पूर्ण

अटल irqवापस_t mpr_touchkey_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mpr121_touchkey *mpr121 = dev_id;

	mpr_touchkey_report(mpr121->input_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mpr121_phys_init(काष्ठा mpr121_touchkey *mpr121,
			    काष्ठा i2c_client *client, पूर्णांक vdd_uv)
अणु
	स्थिर काष्ठा mpr121_init_रेजिस्टर *reg;
	अचिन्हित अक्षर usl, lsl, tl, eleconf;
	पूर्णांक i, t, vdd, ret;

	/* Set up touch/release threshold क्रम ele0-ele11 */
	क्रम (i = 0; i <= MPR121_MAX_KEY_COUNT; i++) अणु
		t = ELE0_TOUCH_THRESHOLD_ADDR + (i * 2);
		ret = i2c_smbus_ग_लिखो_byte_data(client, t, TOUCH_THRESHOLD);
		अगर (ret < 0)
			जाओ err_i2c_ग_लिखो;
		ret = i2c_smbus_ग_लिखो_byte_data(client, t + 1,
						RELEASE_THRESHOLD);
		अगर (ret < 0)
			जाओ err_i2c_ग_लिखो;
	पूर्ण

	/* Set up init रेजिस्टर */
	क्रम (i = 0; i < ARRAY_SIZE(init_reg_table); i++) अणु
		reg = &init_reg_table[i];
		ret = i2c_smbus_ग_लिखो_byte_data(client, reg->addr, reg->val);
		अगर (ret < 0)
			जाओ err_i2c_ग_लिखो;
	पूर्ण


	/*
	 * Capacitance on sensing input varies and needs to be compensated.
	 * The पूर्णांकernal MPR121-स्वतः-configuration can करो this अगर it's
	 * रेजिस्टरs are set properly (based on vdd_uv).
	 */
	vdd = vdd_uv / 1000;
	usl = ((vdd - 700) * 256) / vdd;
	lsl = (usl * 65) / 100;
	tl = (usl * 90) / 100;
	ret = i2c_smbus_ग_लिखो_byte_data(client, AUTO_CONFIG_USL_ADDR, usl);
	ret |= i2c_smbus_ग_लिखो_byte_data(client, AUTO_CONFIG_LSL_ADDR, lsl);
	ret |= i2c_smbus_ग_लिखो_byte_data(client, AUTO_CONFIG_TL_ADDR, tl);

	/*
	 * Quick अक्षरge bit will let the capacitive अक्षरge to पढ़ोy
	 * state quickly, or the buttons may not function after प्रणाली
	 * boot.
	 */
	eleconf = mpr121->keycount | ELECTRODE_CONF_QUICK_CHARGE;
	ret |= i2c_smbus_ग_लिखो_byte_data(client, ELECTRODE_CONF_ADDR,
					 eleconf);
	अगर (ret != 0)
		जाओ err_i2c_ग_लिखो;

	dev_dbg(&client->dev, "set up with %x keys.\n", mpr121->keycount);

	वापस 0;

err_i2c_ग_लिखो:
	dev_err(&client->dev, "i2c write error: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mpr_touchkey_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा regulator *vdd_supply;
	पूर्णांक vdd_uv;
	काष्ठा mpr121_touchkey *mpr121;
	काष्ठा input_dev *input_dev;
	u32 poll_पूर्णांकerval = 0;
	पूर्णांक error;
	पूर्णांक i;

	vdd_supply = mpr121_vdd_supply_init(dev);
	अगर (IS_ERR(vdd_supply))
		वापस PTR_ERR(vdd_supply);

	vdd_uv = regulator_get_voltage(vdd_supply);

	mpr121 = devm_kzalloc(dev, माप(*mpr121), GFP_KERNEL);
	अगर (!mpr121)
		वापस -ENOMEM;

	input_dev = devm_input_allocate_device(dev);
	अगर (!input_dev)
		वापस -ENOMEM;

	mpr121->client = client;
	mpr121->input_dev = input_dev;
	mpr121->keycount = device_property_count_u32(dev, "linux,keycodes");
	अगर (mpr121->keycount > MPR121_MAX_KEY_COUNT) अणु
		dev_err(dev, "too many keys defined (%d)\n", mpr121->keycount);
		वापस -EINVAL;
	पूर्ण

	error = device_property_पढ़ो_u32_array(dev, "linux,keycodes",
					       mpr121->keycodes,
					       mpr121->keycount);
	अगर (error) अणु
		dev_err(dev,
			"failed to read linux,keycode property: %d\n", error);
		वापस error;
	पूर्ण

	input_dev->name = "Freescale MPR121 Touchkey";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = dev;
	अगर (device_property_पढ़ो_bool(dev, "autorepeat"))
		__set_bit(EV_REP, input_dev->evbit);
	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	input_set_drvdata(input_dev, mpr121);

	input_dev->keycode = mpr121->keycodes;
	input_dev->keycodesize = माप(mpr121->keycodes[0]);
	input_dev->keycodemax = mpr121->keycount;

	क्रम (i = 0; i < mpr121->keycount; i++)
		input_set_capability(input_dev, EV_KEY, mpr121->keycodes[i]);

	error = mpr121_phys_init(mpr121, client, vdd_uv);
	अगर (error) अणु
		dev_err(dev, "Failed to init register\n");
		वापस error;
	पूर्ण

	device_property_पढ़ो_u32(dev, "poll-interval", &poll_पूर्णांकerval);

	अगर (client->irq) अणु
		error = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
						  mpr_touchkey_पूर्णांकerrupt,
						  IRQF_TRIGGER_FALLING |
						  IRQF_ONESHOT,
						  dev->driver->name, mpr121);
		अगर (error) अणु
			dev_err(dev, "Failed to register interrupt\n");
			वापस error;
		पूर्ण
	पूर्ण अन्यथा अगर (poll_पूर्णांकerval) अणु
		अगर (poll_पूर्णांकerval < MPR121_MIN_POLL_INTERVAL)
			वापस -EINVAL;

		अगर (poll_पूर्णांकerval > MPR121_MAX_POLL_INTERVAL)
			वापस -EINVAL;

		error = input_setup_polling(input_dev, mpr_touchkey_report);
		अगर (error) अणु
			dev_err(dev, "Failed to setup polling\n");
			वापस error;
		पूर्ण

		input_set_poll_पूर्णांकerval(input_dev, poll_पूर्णांकerval);
		input_set_min_poll_पूर्णांकerval(input_dev,
					    MPR121_MIN_POLL_INTERVAL);
		input_set_max_poll_पूर्णांकerval(input_dev,
					    MPR121_MAX_POLL_INTERVAL);
	पूर्ण अन्यथा अणु
		dev_err(dev,
			"invalid IRQ number and polling not configured\n");
		वापस -EINVAL;
	पूर्ण

	error = input_रेजिस्टर_device(input_dev);
	अगर (error)
		वापस error;

	i2c_set_clientdata(client, mpr121);
	device_init_wakeup(dev,
			device_property_पढ़ो_bool(dev, "wakeup-source"));

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mpr_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	अगर (device_may_wakeup(&client->dev))
		enable_irq_wake(client->irq);

	i2c_smbus_ग_लिखो_byte_data(client, ELECTRODE_CONF_ADDR, 0x00);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mpr_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mpr121_touchkey *mpr121 = i2c_get_clientdata(client);

	अगर (device_may_wakeup(&client->dev))
		disable_irq_wake(client->irq);

	i2c_smbus_ग_लिखो_byte_data(client, ELECTRODE_CONF_ADDR,
				  mpr121->keycount);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mpr121_touchkey_pm_ops, mpr_suspend, mpr_resume);

अटल स्थिर काष्ठा i2c_device_id mpr121_id[] = अणु
	अणु "mpr121_touchkey", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mpr121_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mpr121_touchkey_dt_match_table[] = अणु
	अणु .compatible = "fsl,mpr121-touchkey" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mpr121_touchkey_dt_match_table);
#पूर्ण_अगर

अटल काष्ठा i2c_driver mpr_touchkey_driver = अणु
	.driver = अणु
		.name	= "mpr121",
		.pm	= &mpr121_touchkey_pm_ops,
		.of_match_table = of_match_ptr(mpr121_touchkey_dt_match_table),
	पूर्ण,
	.id_table	= mpr121_id,
	.probe		= mpr_touchkey_probe,
पूर्ण;

module_i2c_driver(mpr_touchkey_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zhang Jiejing <jiejing.zhang@freescale.com>");
MODULE_DESCRIPTION("Touch Key driver for Freescale MPR121 Chip");
