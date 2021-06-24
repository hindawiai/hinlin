<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा ILI2XXX_POLL_PERIOD	20

#घोषणा ILI210X_DATA_SIZE	64
#घोषणा ILI211X_DATA_SIZE	43
#घोषणा ILI251X_DATA_SIZE1	31
#घोषणा ILI251X_DATA_SIZE2	20

/* Touchscreen commands */
#घोषणा REG_TOUCHDATA		0x10
#घोषणा REG_PANEL_INFO		0x20
#घोषणा REG_CALIBRATE		0xcc

काष्ठा ili2xxx_chip अणु
	पूर्णांक (*पढ़ो_reg)(काष्ठा i2c_client *client, u8 reg,
			व्योम *buf, माप_प्रकार len);
	पूर्णांक (*get_touch_data)(काष्ठा i2c_client *client, u8 *data);
	bool (*parse_touch_data)(स्थिर u8 *data, अचिन्हित पूर्णांक finger,
				 अचिन्हित पूर्णांक *x, अचिन्हित पूर्णांक *y,
				 अचिन्हित पूर्णांक *z);
	bool (*जारी_polling)(स्थिर u8 *data, bool touch);
	अचिन्हित पूर्णांक max_touches;
	अचिन्हित पूर्णांक resolution;
	bool has_calibrate_reg;
	bool has_pressure_reg;
पूर्ण;

काष्ठा ili210x अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा touchscreen_properties prop;
	स्थिर काष्ठा ili2xxx_chip *chip;
	bool stop;
पूर्ण;

अटल पूर्णांक ili210x_पढ़ो_reg(काष्ठा i2c_client *client,
			    u8 reg, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr	= client->addr,
			.flags	= 0,
			.len	= 1,
			.buf	= &reg,
		पूर्ण,
		अणु
			.addr	= client->addr,
			.flags	= I2C_M_RD,
			.len	= len,
			.buf	= buf,
		पूर्ण
	पूर्ण;
	पूर्णांक error, ret;

	ret = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
	अगर (ret != ARRAY_SIZE(msg)) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&client->dev, "%s failed: %d\n", __func__, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ili210x_पढ़ो_touch_data(काष्ठा i2c_client *client, u8 *data)
अणु
	वापस ili210x_पढ़ो_reg(client, REG_TOUCHDATA,
				data, ILI210X_DATA_SIZE);
पूर्ण

अटल bool ili210x_touchdata_to_coords(स्थिर u8 *touchdata,
					अचिन्हित पूर्णांक finger,
					अचिन्हित पूर्णांक *x, अचिन्हित पूर्णांक *y,
					अचिन्हित पूर्णांक *z)
अणु
	अगर (!(touchdata[0] & BIT(finger)))
		वापस false;

	*x = get_unaligned_be16(touchdata + 1 + (finger * 4) + 0);
	*y = get_unaligned_be16(touchdata + 1 + (finger * 4) + 2);

	वापस true;
पूर्ण

अटल bool ili210x_check_जारी_polling(स्थिर u8 *data, bool touch)
अणु
	वापस data[0] & 0xf3;
पूर्ण

अटल स्थिर काष्ठा ili2xxx_chip ili210x_chip = अणु
	.पढ़ो_reg		= ili210x_पढ़ो_reg,
	.get_touch_data		= ili210x_पढ़ो_touch_data,
	.parse_touch_data	= ili210x_touchdata_to_coords,
	.जारी_polling	= ili210x_check_जारी_polling,
	.max_touches		= 2,
	.has_calibrate_reg	= true,
पूर्ण;

अटल पूर्णांक ili211x_पढ़ो_touch_data(काष्ठा i2c_client *client, u8 *data)
अणु
	s16 sum = 0;
	पूर्णांक error;
	पूर्णांक ret;
	पूर्णांक i;

	ret = i2c_master_recv(client, data, ILI211X_DATA_SIZE);
	अगर (ret != ILI211X_DATA_SIZE) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&client->dev, "%s failed: %d\n", __func__, error);
		वापस error;
	पूर्ण

	/* This chip uses custom checksum at the end of data */
	क्रम (i = 0; i < ILI211X_DATA_SIZE - 1; i++)
		sum = (sum + data[i]) & 0xff;

	अगर ((-sum & 0xff) != data[ILI211X_DATA_SIZE - 1]) अणु
		dev_err(&client->dev,
			"CRC error (crc=0x%02x expected=0x%02x)\n",
			sum, data[ILI211X_DATA_SIZE - 1]);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ili211x_touchdata_to_coords(स्थिर u8 *touchdata,
					अचिन्हित पूर्णांक finger,
					अचिन्हित पूर्णांक *x, अचिन्हित पूर्णांक *y,
					अचिन्हित पूर्णांक *z)
अणु
	u32 data;

	data = get_unaligned_be32(touchdata + 1 + (finger * 4) + 0);
	अगर (data == 0xffffffff)	/* Finger up */
		वापस false;

	*x = ((touchdata[1 + (finger * 4) + 0] & 0xf0) << 4) |
	     touchdata[1 + (finger * 4) + 1];
	*y = ((touchdata[1 + (finger * 4) + 0] & 0x0f) << 8) |
	     touchdata[1 + (finger * 4) + 2];

	वापस true;
पूर्ण

अटल bool ili211x_decline_polling(स्थिर u8 *data, bool touch)
अणु
	वापस false;
पूर्ण

अटल स्थिर काष्ठा ili2xxx_chip ili211x_chip = अणु
	.पढ़ो_reg		= ili210x_पढ़ो_reg,
	.get_touch_data		= ili211x_पढ़ो_touch_data,
	.parse_touch_data	= ili211x_touchdata_to_coords,
	.जारी_polling	= ili211x_decline_polling,
	.max_touches		= 10,
	.resolution		= 2048,
पूर्ण;

अटल bool ili212x_touchdata_to_coords(स्थिर u8 *touchdata,
					अचिन्हित पूर्णांक finger,
					अचिन्हित पूर्णांक *x, अचिन्हित पूर्णांक *y,
					अचिन्हित पूर्णांक *z)
अणु
	u16 val;

	val = get_unaligned_be16(touchdata + 3 + (finger * 5) + 0);
	अगर (!(val & BIT(15)))	/* Touch indication */
		वापस false;

	*x = val & 0x3fff;
	*y = get_unaligned_be16(touchdata + 3 + (finger * 5) + 2);

	वापस true;
पूर्ण

अटल bool ili212x_check_जारी_polling(स्थिर u8 *data, bool touch)
अणु
	वापस touch;
पूर्ण

अटल स्थिर काष्ठा ili2xxx_chip ili212x_chip = अणु
	.पढ़ो_reg		= ili210x_पढ़ो_reg,
	.get_touch_data		= ili210x_पढ़ो_touch_data,
	.parse_touch_data	= ili212x_touchdata_to_coords,
	.जारी_polling	= ili212x_check_जारी_polling,
	.max_touches		= 10,
	.has_calibrate_reg	= true,
पूर्ण;

अटल पूर्णांक ili251x_पढ़ो_reg(काष्ठा i2c_client *client,
			    u8 reg, व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक error;
	पूर्णांक ret;

	ret = i2c_master_send(client, &reg, 1);
	अगर (ret == 1) अणु
		usleep_range(5000, 5500);

		ret = i2c_master_recv(client, buf, len);
		अगर (ret == len)
			वापस 0;
	पूर्ण

	error = ret < 0 ? ret : -EIO;
	dev_err(&client->dev, "%s failed: %d\n", __func__, error);
	वापस ret;
पूर्ण

अटल पूर्णांक ili251x_पढ़ो_touch_data(काष्ठा i2c_client *client, u8 *data)
अणु
	पूर्णांक error;

	error = ili251x_पढ़ो_reg(client, REG_TOUCHDATA,
				 data, ILI251X_DATA_SIZE1);
	अगर (!error && data[0] == 2) अणु
		error = i2c_master_recv(client, data + ILI251X_DATA_SIZE1,
					ILI251X_DATA_SIZE2);
		अगर (error >= 0 && error != ILI251X_DATA_SIZE2)
			error = -EIO;
	पूर्ण

	वापस error;
पूर्ण

अटल bool ili251x_touchdata_to_coords(स्थिर u8 *touchdata,
					अचिन्हित पूर्णांक finger,
					अचिन्हित पूर्णांक *x, अचिन्हित पूर्णांक *y,
					अचिन्हित पूर्णांक *z)
अणु
	u16 val;

	val = get_unaligned_be16(touchdata + 1 + (finger * 5) + 0);
	अगर (!(val & BIT(15)))	/* Touch indication */
		वापस false;

	*x = val & 0x3fff;
	*y = get_unaligned_be16(touchdata + 1 + (finger * 5) + 2);
	*z = touchdata[1 + (finger * 5) + 4];

	वापस true;
पूर्ण

अटल bool ili251x_check_जारी_polling(स्थिर u8 *data, bool touch)
अणु
	वापस touch;
पूर्ण

अटल स्थिर काष्ठा ili2xxx_chip ili251x_chip = अणु
	.पढ़ो_reg		= ili251x_पढ़ो_reg,
	.get_touch_data		= ili251x_पढ़ो_touch_data,
	.parse_touch_data	= ili251x_touchdata_to_coords,
	.जारी_polling	= ili251x_check_जारी_polling,
	.max_touches		= 10,
	.has_calibrate_reg	= true,
	.has_pressure_reg	= true,
पूर्ण;

अटल bool ili210x_report_events(काष्ठा ili210x *priv, u8 *touchdata)
अणु
	काष्ठा input_dev *input = priv->input;
	पूर्णांक i;
	bool contact = false, touch;
	अचिन्हित पूर्णांक x = 0, y = 0, z = 0;

	क्रम (i = 0; i < priv->chip->max_touches; i++) अणु
		touch = priv->chip->parse_touch_data(touchdata, i, &x, &y, &z);

		input_mt_slot(input, i);
		अगर (input_mt_report_slot_state(input, MT_TOOL_FINGER, touch)) अणु
			touchscreen_report_pos(input, &priv->prop, x, y, true);
			अगर (priv->chip->has_pressure_reg)
				input_report_असल(input, ABS_MT_PRESSURE, z);
			contact = true;
		पूर्ण
	पूर्ण

	input_mt_report_poपूर्णांकer_emulation(input, false);
	input_sync(input);

	वापस contact;
पूर्ण

अटल irqवापस_t ili210x_irq(पूर्णांक irq, व्योम *irq_data)
अणु
	काष्ठा ili210x *priv = irq_data;
	काष्ठा i2c_client *client = priv->client;
	स्थिर काष्ठा ili2xxx_chip *chip = priv->chip;
	u8 touchdata[ILI210X_DATA_SIZE] = अणु 0 पूर्ण;
	bool keep_polling;
	bool touch;
	पूर्णांक error;

	करो अणु
		error = chip->get_touch_data(client, touchdata);
		अगर (error) अणु
			dev_err(&client->dev,
				"Unable to get touch data: %d\n", error);
			अवरोध;
		पूर्ण

		touch = ili210x_report_events(priv, touchdata);
		keep_polling = chip->जारी_polling(touchdata, touch);
		अगर (keep_polling)
			msleep(ILI2XXX_POLL_PERIOD);
	पूर्ण जबतक (!priv->stop && keep_polling);

	वापस IRQ_HANDLED;
पूर्ण

अटल sमाप_प्रकार ili210x_calibrate(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ili210x *priv = i2c_get_clientdata(client);
	अचिन्हित दीर्घ calibrate;
	पूर्णांक rc;
	u8 cmd = REG_CALIBRATE;

	अगर (kम_से_अदीर्घ(buf, 10, &calibrate))
		वापस -EINVAL;

	अगर (calibrate > 1)
		वापस -EINVAL;

	अगर (calibrate) अणु
		rc = i2c_master_send(priv->client, &cmd, माप(cmd));
		अगर (rc != माप(cmd))
			वापस -EIO;
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR(calibrate, S_IWUSR, शून्य, ili210x_calibrate);

अटल काष्ठा attribute *ili210x_attributes[] = अणु
	&dev_attr_calibrate.attr,
	शून्य,
पूर्ण;

अटल umode_t ili210x_calibrate_visible(काष्ठा kobject *kobj,
					  काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ili210x *priv = i2c_get_clientdata(client);

	वापस priv->chip->has_calibrate_reg ? attr->mode : 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group ili210x_attr_group = अणु
	.attrs = ili210x_attributes,
	.is_visible = ili210x_calibrate_visible,
पूर्ण;

अटल व्योम ili210x_घातer_करोwn(व्योम *data)
अणु
	काष्ठा gpio_desc *reset_gpio = data;

	gpiod_set_value_cansleep(reset_gpio, 1);
पूर्ण

अटल व्योम ili210x_stop(व्योम *data)
अणु
	काष्ठा ili210x *priv = data;

	/* Tell ISR to quit even अगर there is a contact. */
	priv->stop = true;
पूर्ण

अटल पूर्णांक ili210x_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	स्थिर काष्ठा ili2xxx_chip *chip;
	काष्ठा ili210x *priv;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा input_dev *input;
	पूर्णांक error;
	अचिन्हित पूर्णांक max_xy;

	dev_dbg(dev, "Probing for ILI210X I2C Touschreen driver");

	chip = device_get_match_data(dev);
	अगर (!chip && id)
		chip = (स्थिर काष्ठा ili2xxx_chip *)id->driver_data;
	अगर (!chip) अणु
		dev_err(&client->dev, "unknown device model\n");
		वापस -ENODEV;
	पूर्ण

	अगर (client->irq <= 0) अणु
		dev_err(dev, "No IRQ!\n");
		वापस -EINVAL;
	पूर्ण

	reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(reset_gpio))
		वापस PTR_ERR(reset_gpio);

	अगर (reset_gpio) अणु
		error = devm_add_action_or_reset(dev, ili210x_घातer_करोwn,
						 reset_gpio);
		अगर (error)
			वापस error;

		usleep_range(50, 100);
		gpiod_set_value_cansleep(reset_gpio, 0);
		msleep(100);
	पूर्ण

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	priv->client = client;
	priv->input = input;
	priv->reset_gpio = reset_gpio;
	priv->chip = chip;
	i2c_set_clientdata(client, priv);

	/* Setup input device */
	input->name = "ILI210x Touchscreen";
	input->id.bustype = BUS_I2C;

	/* Multi touch */
	max_xy = (chip->resolution ?: SZ_64K) - 1;
	input_set_असल_params(input, ABS_MT_POSITION_X, 0, max_xy, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0, max_xy, 0, 0);
	अगर (priv->chip->has_pressure_reg)
		input_set_असल_params(input, ABS_MT_PRESSURE, 0, 0xa, 0, 0);
	touchscreen_parse_properties(input, true, &priv->prop);

	error = input_mt_init_slots(input, priv->chip->max_touches,
				    INPUT_MT_सूचीECT);
	अगर (error) अणु
		dev_err(dev, "Unable to set up slots, err: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य, ili210x_irq,
					  IRQF_ONESHOT, client->name, priv);
	अगर (error) अणु
		dev_err(dev, "Unable to request touchscreen IRQ, err: %d\n",
			error);
		वापस error;
	पूर्ण

	error = devm_add_action_or_reset(dev, ili210x_stop, priv);
	अगर (error)
		वापस error;

	error = devm_device_add_group(dev, &ili210x_attr_group);
	अगर (error) अणु
		dev_err(dev, "Unable to create sysfs attributes, err: %d\n",
			error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(priv->input);
	अगर (error) अणु
		dev_err(dev, "Cannot register input device, err: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ili210x_i2c_id[] = अणु
	अणु "ili210x", (दीर्घ)&ili210x_chip पूर्ण,
	अणु "ili2117", (दीर्घ)&ili211x_chip पूर्ण,
	अणु "ili2120", (दीर्घ)&ili212x_chip पूर्ण,
	अणु "ili251x", (दीर्घ)&ili251x_chip पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ili210x_i2c_id);

अटल स्थिर काष्ठा of_device_id ili210x_dt_ids[] = अणु
	अणु .compatible = "ilitek,ili210x", .data = &ili210x_chip पूर्ण,
	अणु .compatible = "ilitek,ili2117", .data = &ili211x_chip पूर्ण,
	अणु .compatible = "ilitek,ili2120", .data = &ili212x_chip पूर्ण,
	अणु .compatible = "ilitek,ili251x", .data = &ili251x_chip पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ili210x_dt_ids);

अटल काष्ठा i2c_driver ili210x_ts_driver = अणु
	.driver = अणु
		.name = "ili210x_i2c",
		.of_match_table = ili210x_dt_ids,
	पूर्ण,
	.id_table = ili210x_i2c_id,
	.probe = ili210x_i2c_probe,
पूर्ण;

module_i2c_driver(ili210x_ts_driver);

MODULE_AUTHOR("Olivier Sobrie <olivier@sobrie.be>");
MODULE_DESCRIPTION("ILI210X I2C Touchscreen Driver");
MODULE_LICENSE("GPL");
