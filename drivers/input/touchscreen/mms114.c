<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Melfas MMS114/MMS136/MMS152 touchscreen device driver
//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
// Author: Joonyoung Shim <jy0922.shim@samsung.com>

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

/* Write only रेजिस्टरs */
#घोषणा MMS114_MODE_CONTROL		0x01
#घोषणा MMS114_OPERATION_MODE_MASK	0xE
#घोषणा MMS114_ACTIVE			BIT(1)

#घोषणा MMS114_XY_RESOLUTION_H		0x02
#घोषणा MMS114_X_RESOLUTION		0x03
#घोषणा MMS114_Y_RESOLUTION		0x04
#घोषणा MMS114_CONTACT_THRESHOLD	0x05
#घोषणा MMS114_MOVING_THRESHOLD		0x06

/* Read only रेजिस्टरs */
#घोषणा MMS114_PACKET_SIZE		0x0F
#घोषणा MMS114_INFORMATION		0x10
#घोषणा MMS114_TSP_REV			0xF0

#घोषणा MMS152_FW_REV			0xE1
#घोषणा MMS152_COMPAT_GROUP		0xF2

/* Minimum delay समय is 50us between stop and start संकेत of i2c */
#घोषणा MMS114_I2C_DELAY		50

/* 200ms needs after घातer on */
#घोषणा MMS114_POWERON_DELAY		200

/* Touchscreen असलolute values */
#घोषणा MMS114_MAX_AREA			0xff

#घोषणा MMS114_MAX_TOUCH		10
#घोषणा MMS114_EVENT_SIZE		8
#घोषणा MMS136_EVENT_SIZE		6

/* Touch type */
#घोषणा MMS114_TYPE_NONE		0
#घोषणा MMS114_TYPE_TOUCHSCREEN		1
#घोषणा MMS114_TYPE_TOUCHKEY		2

क्रमागत mms_type अणु
	TYPE_MMS114	= 114,
	TYPE_MMS136	= 136,
	TYPE_MMS152	= 152,
	TYPE_MMS345L	= 345,
पूर्ण;

काष्ठा mms114_data अणु
	काष्ठा i2c_client	*client;
	काष्ठा input_dev	*input_dev;
	काष्ठा regulator	*core_reg;
	काष्ठा regulator	*io_reg;
	काष्ठा touchscreen_properties props;
	क्रमागत mms_type		type;
	अचिन्हित पूर्णांक		contact_threshold;
	अचिन्हित पूर्णांक		moving_threshold;

	/* Use cache data क्रम mode control रेजिस्टर(ग_लिखो only) */
	u8			cache_mode_control;
पूर्ण;

काष्ठा mms114_touch अणु
	u8 id:4, reserved_bit4:1, type:2, pressed:1;
	u8 x_hi:4, y_hi:4;
	u8 x_lo;
	u8 y_lo;
	u8 width;
	u8 strength;
	u8 reserved[2];
पूर्ण __packed;

अटल पूर्णांक __mms114_पढ़ो_reg(काष्ठा mms114_data *data, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक len, u8 *val)
अणु
	काष्ठा i2c_client *client = data->client;
	काष्ठा i2c_msg xfer[2];
	u8 buf = reg & 0xff;
	पूर्णांक error;

	अगर (reg <= MMS114_MODE_CONTROL && reg + len > MMS114_MODE_CONTROL)
		BUG();

	/* Write रेजिस्टर */
	xfer[0].addr = client->addr;
	xfer[0].flags = client->flags & I2C_M_TEN;
	xfer[0].len = 1;
	xfer[0].buf = &buf;

	/* Read data */
	xfer[1].addr = client->addr;
	xfer[1].flags = (client->flags & I2C_M_TEN) | I2C_M_RD;
	xfer[1].len = len;
	xfer[1].buf = val;

	error = i2c_transfer(client->adapter, xfer, 2);
	अगर (error != 2) अणु
		dev_err(&client->dev,
			"%s: i2c transfer failed (%d)\n", __func__, error);
		वापस error < 0 ? error : -EIO;
	पूर्ण
	udelay(MMS114_I2C_DELAY);

	वापस 0;
पूर्ण

अटल पूर्णांक mms114_पढ़ो_reg(काष्ठा mms114_data *data, अचिन्हित पूर्णांक reg)
अणु
	u8 val;
	पूर्णांक error;

	अगर (reg == MMS114_MODE_CONTROL)
		वापस data->cache_mode_control;

	error = __mms114_पढ़ो_reg(data, reg, 1, &val);
	वापस error < 0 ? error : val;
पूर्ण

अटल पूर्णांक mms114_ग_लिखो_reg(काष्ठा mms114_data *data, अचिन्हित पूर्णांक reg,
			    अचिन्हित पूर्णांक val)
अणु
	काष्ठा i2c_client *client = data->client;
	u8 buf[2];
	पूर्णांक error;

	buf[0] = reg & 0xff;
	buf[1] = val & 0xff;

	error = i2c_master_send(client, buf, 2);
	अगर (error != 2) अणु
		dev_err(&client->dev,
			"%s: i2c send failed (%d)\n", __func__, error);
		वापस error < 0 ? error : -EIO;
	पूर्ण
	udelay(MMS114_I2C_DELAY);

	अगर (reg == MMS114_MODE_CONTROL)
		data->cache_mode_control = val;

	वापस 0;
पूर्ण

अटल व्योम mms114_process_mt(काष्ठा mms114_data *data, काष्ठा mms114_touch *touch)
अणु
	काष्ठा i2c_client *client = data->client;
	काष्ठा input_dev *input_dev = data->input_dev;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक x;
	अचिन्हित पूर्णांक y;

	अगर (touch->id > MMS114_MAX_TOUCH) अणु
		dev_err(&client->dev, "Wrong touch id (%d)\n", touch->id);
		वापस;
	पूर्ण

	अगर (touch->type != MMS114_TYPE_TOUCHSCREEN) अणु
		dev_err(&client->dev, "Wrong touch type (%d)\n", touch->type);
		वापस;
	पूर्ण

	id = touch->id - 1;
	x = touch->x_lo | touch->x_hi << 8;
	y = touch->y_lo | touch->y_hi << 8;

	dev_dbg(&client->dev,
		"id: %d, type: %d, pressed: %d, x: %d, y: %d, width: %d, strength: %d\n",
		id, touch->type, touch->pressed,
		x, y, touch->width, touch->strength);

	input_mt_slot(input_dev, id);
	input_mt_report_slot_state(input_dev, MT_TOOL_FINGER, touch->pressed);

	अगर (touch->pressed) अणु
		touchscreen_report_pos(input_dev, &data->props, x, y, true);
		input_report_असल(input_dev, ABS_MT_TOUCH_MAJOR, touch->width);
		input_report_असल(input_dev, ABS_MT_PRESSURE, touch->strength);
	पूर्ण
पूर्ण

अटल irqवापस_t mms114_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mms114_data *data = dev_id;
	काष्ठा input_dev *input_dev = data->input_dev;
	काष्ठा mms114_touch touch[MMS114_MAX_TOUCH];
	पूर्णांक packet_size;
	पूर्णांक touch_size;
	पूर्णांक index;
	पूर्णांक error;

	mutex_lock(&input_dev->mutex);
	अगर (!input_device_enabled(input_dev)) अणु
		mutex_unlock(&input_dev->mutex);
		जाओ out;
	पूर्ण
	mutex_unlock(&input_dev->mutex);

	packet_size = mms114_पढ़ो_reg(data, MMS114_PACKET_SIZE);
	अगर (packet_size <= 0)
		जाओ out;

	/* MMS136 has slightly dअगरferent event size */
	अगर (data->type == TYPE_MMS136)
		touch_size = packet_size / MMS136_EVENT_SIZE;
	अन्यथा
		touch_size = packet_size / MMS114_EVENT_SIZE;

	error = __mms114_पढ़ो_reg(data, MMS114_INFORMATION, packet_size,
			(u8 *)touch);
	अगर (error < 0)
		जाओ out;

	क्रम (index = 0; index < touch_size; index++)
		mms114_process_mt(data, touch + index);

	input_mt_report_poपूर्णांकer_emulation(data->input_dev, true);
	input_sync(data->input_dev);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mms114_set_active(काष्ठा mms114_data *data, bool active)
अणु
	पूर्णांक val;

	val = mms114_पढ़ो_reg(data, MMS114_MODE_CONTROL);
	अगर (val < 0)
		वापस val;

	val &= ~MMS114_OPERATION_MODE_MASK;

	/* If active is false, sleep mode */
	अगर (active)
		val |= MMS114_ACTIVE;

	वापस mms114_ग_लिखो_reg(data, MMS114_MODE_CONTROL, val);
पूर्ण

अटल पूर्णांक mms114_get_version(काष्ठा mms114_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	u8 buf[6];
	पूर्णांक group;
	पूर्णांक error;

	चयन (data->type) अणु
	हाल TYPE_MMS345L:
		error = __mms114_पढ़ो_reg(data, MMS152_FW_REV, 3, buf);
		अगर (error)
			वापस error;

		dev_info(dev, "TSP FW Rev: bootloader 0x%x / core 0x%x / config 0x%x\n",
			 buf[0], buf[1], buf[2]);
		अवरोध;

	हाल TYPE_MMS152:
		error = __mms114_पढ़ो_reg(data, MMS152_FW_REV, 3, buf);
		अगर (error)
			वापस error;

		group = i2c_smbus_पढ़ो_byte_data(data->client,
						  MMS152_COMPAT_GROUP);
		अगर (group < 0)
			वापस group;

		dev_info(dev, "TSP FW Rev: bootloader 0x%x / core 0x%x / config 0x%x, Compat group: %c\n",
			 buf[0], buf[1], buf[2], group);
		अवरोध;

	हाल TYPE_MMS114:
	हाल TYPE_MMS136:
		error = __mms114_पढ़ो_reg(data, MMS114_TSP_REV, 6, buf);
		अगर (error)
			वापस error;

		dev_info(dev, "TSP Rev: 0x%x, HW Rev: 0x%x, Firmware Ver: 0x%x\n",
			 buf[0], buf[1], buf[3]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mms114_setup_regs(काष्ठा mms114_data *data)
अणु
	स्थिर काष्ठा touchscreen_properties *props = &data->props;
	पूर्णांक val;
	पूर्णांक error;

	error = mms114_get_version(data);
	अगर (error < 0)
		वापस error;

	/* Only MMS114 and MMS136 have configuration and घातer on रेजिस्टरs */
	अगर (data->type != TYPE_MMS114 && data->type != TYPE_MMS136)
		वापस 0;

	error = mms114_set_active(data, true);
	अगर (error < 0)
		वापस error;

	val = (props->max_x >> 8) & 0xf;
	val |= ((props->max_y >> 8) & 0xf) << 4;
	error = mms114_ग_लिखो_reg(data, MMS114_XY_RESOLUTION_H, val);
	अगर (error < 0)
		वापस error;

	val = props->max_x & 0xff;
	error = mms114_ग_लिखो_reg(data, MMS114_X_RESOLUTION, val);
	अगर (error < 0)
		वापस error;

	val = props->max_x & 0xff;
	error = mms114_ग_लिखो_reg(data, MMS114_Y_RESOLUTION, val);
	अगर (error < 0)
		वापस error;

	अगर (data->contact_threshold) अणु
		error = mms114_ग_लिखो_reg(data, MMS114_CONTACT_THRESHOLD,
				data->contact_threshold);
		अगर (error < 0)
			वापस error;
	पूर्ण

	अगर (data->moving_threshold) अणु
		error = mms114_ग_लिखो_reg(data, MMS114_MOVING_THRESHOLD,
				data->moving_threshold);
		अगर (error < 0)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mms114_start(काष्ठा mms114_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक error;

	error = regulator_enable(data->core_reg);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to enable avdd: %d\n", error);
		वापस error;
	पूर्ण

	error = regulator_enable(data->io_reg);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to enable vdd: %d\n", error);
		regulator_disable(data->core_reg);
		वापस error;
	पूर्ण

	msleep(MMS114_POWERON_DELAY);

	error = mms114_setup_regs(data);
	अगर (error < 0) अणु
		regulator_disable(data->io_reg);
		regulator_disable(data->core_reg);
		वापस error;
	पूर्ण

	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल व्योम mms114_stop(काष्ठा mms114_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक error;

	disable_irq(client->irq);

	error = regulator_disable(data->io_reg);
	अगर (error)
		dev_warn(&client->dev, "Failed to disable vdd: %d\n", error);

	error = regulator_disable(data->core_reg);
	अगर (error)
		dev_warn(&client->dev, "Failed to disable avdd: %d\n", error);
पूर्ण

अटल पूर्णांक mms114_input_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा mms114_data *data = input_get_drvdata(dev);

	वापस mms114_start(data);
पूर्ण

अटल व्योम mms114_input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा mms114_data *data = input_get_drvdata(dev);

	mms114_stop(data);
पूर्ण

अटल पूर्णांक mms114_parse_legacy_bindings(काष्ठा mms114_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	काष्ठा touchscreen_properties *props = &data->props;

	अगर (device_property_पढ़ो_u32(dev, "x-size", &props->max_x)) अणु
		dev_dbg(dev, "failed to get legacy x-size property\n");
		वापस -EINVAL;
	पूर्ण

	अगर (device_property_पढ़ो_u32(dev, "y-size", &props->max_y)) अणु
		dev_dbg(dev, "failed to get legacy y-size property\n");
		वापस -EINVAL;
	पूर्ण

	device_property_पढ़ो_u32(dev, "contact-threshold",
				&data->contact_threshold);
	device_property_पढ़ो_u32(dev, "moving-threshold",
				&data->moving_threshold);

	अगर (device_property_पढ़ो_bool(dev, "x-invert"))
		props->invert_x = true;
	अगर (device_property_पढ़ो_bool(dev, "y-invert"))
		props->invert_y = true;

	props->swap_x_y = false;

	वापस 0;
पूर्ण

अटल पूर्णांक mms114_probe(काष्ठा i2c_client *client,
				  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mms114_data *data;
	काष्ठा input_dev *input_dev;
	स्थिर व्योम *match_data;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "Not supported I2C adapter\n");
		वापस -ENODEV;
	पूर्ण

	data = devm_kzalloc(&client->dev, माप(काष्ठा mms114_data),
			    GFP_KERNEL);
	input_dev = devm_input_allocate_device(&client->dev);
	अगर (!data || !input_dev) अणु
		dev_err(&client->dev, "Failed to allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	data->client = client;
	data->input_dev = input_dev;

	match_data = device_get_match_data(&client->dev);
	अगर (!match_data)
		वापस -EINVAL;

	data->type = (क्रमागत mms_type)match_data;

	input_set_capability(input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(input_dev, EV_ABS, ABS_MT_POSITION_Y);
	input_set_असल_params(input_dev, ABS_MT_PRESSURE, 0, 255, 0, 0);
	input_set_असल_params(input_dev, ABS_MT_TOUCH_MAJOR,
			     0, MMS114_MAX_AREA, 0, 0);

	touchscreen_parse_properties(input_dev, true, &data->props);
	अगर (!data->props.max_x || !data->props.max_y) अणु
		dev_dbg(&client->dev,
			"missing X/Y size properties, trying legacy bindings\n");
		error = mms114_parse_legacy_bindings(data);
		अगर (error)
			वापस error;

		input_set_असल_params(input_dev, ABS_MT_POSITION_X,
				     0, data->props.max_x, 0, 0);
		input_set_असल_params(input_dev, ABS_MT_POSITION_Y,
				     0, data->props.max_y, 0, 0);
	पूर्ण

	अगर (data->type == TYPE_MMS114 || data->type == TYPE_MMS136) अणु
		/*
		 * The firmware handles movement and pressure fuzz, so
		 * करोn't duplicate that in software.
		 */
		data->moving_threshold = input_असल_get_fuzz(input_dev,
							    ABS_MT_POSITION_X);
		data->contact_threshold = input_असल_get_fuzz(input_dev,
							     ABS_MT_PRESSURE);
		input_असल_set_fuzz(input_dev, ABS_MT_POSITION_X, 0);
		input_असल_set_fuzz(input_dev, ABS_MT_POSITION_Y, 0);
		input_असल_set_fuzz(input_dev, ABS_MT_PRESSURE, 0);
	पूर्ण

	input_dev->name = devm_kaप्र_लिखो(&client->dev, GFP_KERNEL,
					 "MELFAS MMS%d Touchscreen",
					 data->type);
	अगर (!input_dev->name)
		वापस -ENOMEM;

	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = &client->dev;
	input_dev->खोलो = mms114_input_खोलो;
	input_dev->बंद = mms114_input_बंद;

	error = input_mt_init_slots(input_dev, MMS114_MAX_TOUCH,
				    INPUT_MT_सूचीECT);
	अगर (error)
		वापस error;

	input_set_drvdata(input_dev, data);
	i2c_set_clientdata(client, data);

	data->core_reg = devm_regulator_get(&client->dev, "avdd");
	अगर (IS_ERR(data->core_reg)) अणु
		error = PTR_ERR(data->core_reg);
		dev_err(&client->dev,
			"Unable to get the Core regulator (%d)\n", error);
		वापस error;
	पूर्ण

	data->io_reg = devm_regulator_get(&client->dev, "vdd");
	अगर (IS_ERR(data->io_reg)) अणु
		error = PTR_ERR(data->io_reg);
		dev_err(&client->dev,
			"Unable to get the IO regulator (%d)\n", error);
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, mms114_पूर्णांकerrupt,
					  IRQF_ONESHOT | IRQF_NO_AUTOEN,
					  dev_name(&client->dev), data);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to register interrupt\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(data->input_dev);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to register input device\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mms114_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mms114_data *data = i2c_get_clientdata(client);
	काष्ठा input_dev *input_dev = data->input_dev;
	पूर्णांक id;

	/* Release all touch */
	क्रम (id = 0; id < MMS114_MAX_TOUCH; id++) अणु
		input_mt_slot(input_dev, id);
		input_mt_report_slot_inactive(input_dev);
	पूर्ण

	input_mt_report_poपूर्णांकer_emulation(input_dev, true);
	input_sync(input_dev);

	mutex_lock(&input_dev->mutex);
	अगर (input_device_enabled(input_dev))
		mms114_stop(data);
	mutex_unlock(&input_dev->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mms114_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mms114_data *data = i2c_get_clientdata(client);
	काष्ठा input_dev *input_dev = data->input_dev;
	पूर्णांक error;

	mutex_lock(&input_dev->mutex);
	अगर (input_device_enabled(input_dev)) अणु
		error = mms114_start(data);
		अगर (error < 0) अणु
			mutex_unlock(&input_dev->mutex);
			वापस error;
		पूर्ण
	पूर्ण
	mutex_unlock(&input_dev->mutex);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mms114_pm_ops, mms114_suspend, mms114_resume);

अटल स्थिर काष्ठा i2c_device_id mms114_id[] = अणु
	अणु "mms114", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mms114_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mms114_dt_match[] = अणु
	अणु
		.compatible = "melfas,mms114",
		.data = (व्योम *)TYPE_MMS114,
	पूर्ण, अणु
		.compatible = "melfas,mms136",
		.data = (व्योम *)TYPE_MMS136,
	पूर्ण, अणु
		.compatible = "melfas,mms152",
		.data = (व्योम *)TYPE_MMS152,
	पूर्ण, अणु
		.compatible = "melfas,mms345l",
		.data = (व्योम *)TYPE_MMS345L,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mms114_dt_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver mms114_driver = अणु
	.driver = अणु
		.name	= "mms114",
		.pm	= &mms114_pm_ops,
		.of_match_table = of_match_ptr(mms114_dt_match),
	पूर्ण,
	.probe		= mms114_probe,
	.id_table	= mms114_id,
पूर्ण;

module_i2c_driver(mms114_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Joonyoung Shim <jy0922.shim@samsung.com>");
MODULE_DESCRIPTION("MELFAS mms114 Touchscreen driver");
MODULE_LICENSE("GPL v2");
