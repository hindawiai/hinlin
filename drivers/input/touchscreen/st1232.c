<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ST1232 Touchscreen Controller Driver
 *
 * Copyright (C) 2010 Renesas Solutions Corp.
 *	Tony SIM <chinyeow.sim.xt@renesas.com>
 *
 * Using code from:
 *  - android.git.kernel.org: projects/kernel/common.git: synaptics_i2c_rmi.c
 *	Copyright (C) 2007 Google, Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#घोषणा ST1232_TS_NAME	"st1232-ts"
#घोषणा ST1633_TS_NAME	"st1633-ts"

#घोषणा REG_STATUS		0x01	/* Device Status | Error Code */

#घोषणा STATUS_NORMAL		0x00
#घोषणा STATUS_INIT		0x01
#घोषणा STATUS_ERROR		0x02
#घोषणा STATUS_AUTO_TUNING	0x03
#घोषणा STATUS_IDLE		0x04
#घोषणा STATUS_POWER_DOWN	0x05

#घोषणा ERROR_NONE		0x00
#घोषणा ERROR_INVALID_ADDRESS	0x10
#घोषणा ERROR_INVALID_VALUE	0x20
#घोषणा ERROR_INVALID_PLATFORM	0x30

#घोषणा REG_XY_RESOLUTION	0x04
#घोषणा REG_XY_COORDINATES	0x12
#घोषणा ST_TS_MAX_FINGERS	10

काष्ठा st_chip_info अणु
	bool	have_z;
	u16	max_area;
	u16	max_fingers;
पूर्ण;

काष्ठा st1232_ts_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input_dev;
	काष्ठा touchscreen_properties prop;
	काष्ठा dev_pm_qos_request low_latency_req;
	काष्ठा gpio_desc *reset_gpio;
	स्थिर काष्ठा st_chip_info *chip_info;
	पूर्णांक पढ़ो_buf_len;
	u8 *पढ़ो_buf;
पूर्ण;

अटल पूर्णांक st1232_ts_पढ़ो_data(काष्ठा st1232_ts_data *ts, u8 reg,
			       अचिन्हित पूर्णांक n)
अणु
	काष्ठा i2c_client *client = ts->client;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr	= client->addr,
			.len	= माप(reg),
			.buf	= &reg,
		पूर्ण,
		अणु
			.addr	= client->addr,
			.flags	= I2C_M_RD | I2C_M_DMA_SAFE,
			.len	= n,
			.buf	= ts->पढ़ो_buf,
		पूर्ण
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
	अगर (ret != ARRAY_SIZE(msg))
		वापस ret < 0 ? ret : -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक st1232_ts_रुको_पढ़ोy(काष्ठा st1232_ts_data *ts)
अणु
	अचिन्हित पूर्णांक retries;
	पूर्णांक error;

	क्रम (retries = 10; retries; retries--) अणु
		error = st1232_ts_पढ़ो_data(ts, REG_STATUS, 1);
		अगर (!error) अणु
			चयन (ts->पढ़ो_buf[0]) अणु
			हाल STATUS_NORMAL | ERROR_NONE:
			हाल STATUS_IDLE | ERROR_NONE:
				वापस 0;
			पूर्ण
		पूर्ण

		usleep_range(1000, 2000);
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक st1232_ts_पढ़ो_resolution(काष्ठा st1232_ts_data *ts, u16 *max_x,
				     u16 *max_y)
अणु
	u8 *buf;
	पूर्णांक error;

	/* select resolution रेजिस्टर */
	error = st1232_ts_पढ़ो_data(ts, REG_XY_RESOLUTION, 3);
	अगर (error)
		वापस error;

	buf = ts->पढ़ो_buf;

	*max_x = (((buf[0] & 0x0070) << 4) | buf[1]) - 1;
	*max_y = (((buf[0] & 0x0007) << 8) | buf[2]) - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक st1232_ts_parse_and_report(काष्ठा st1232_ts_data *ts)
अणु
	काष्ठा input_dev *input = ts->input_dev;
	काष्ठा input_mt_pos pos[ST_TS_MAX_FINGERS];
	u8 z[ST_TS_MAX_FINGERS];
	पूर्णांक slots[ST_TS_MAX_FINGERS];
	पूर्णांक n_contacts = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ts->chip_info->max_fingers; i++) अणु
		u8 *buf = &ts->पढ़ो_buf[i * 4];

		अगर (buf[0] & BIT(7)) अणु
			अचिन्हित पूर्णांक x = ((buf[0] & 0x70) << 4) | buf[1];
			अचिन्हित पूर्णांक y = ((buf[0] & 0x07) << 8) | buf[2];

			touchscreen_set_mt_pos(&pos[n_contacts],
					       &ts->prop, x, y);

			/* st1232 includes a z-axis / touch strength */
			अगर (ts->chip_info->have_z)
				z[n_contacts] = ts->पढ़ो_buf[i + 6];

			n_contacts++;
		पूर्ण
	पूर्ण

	input_mt_assign_slots(input, slots, pos, n_contacts, 0);
	क्रम (i = 0; i < n_contacts; i++) अणु
		input_mt_slot(input, slots[i]);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, true);
		input_report_असल(input, ABS_MT_POSITION_X, pos[i].x);
		input_report_असल(input, ABS_MT_POSITION_Y, pos[i].y);
		अगर (ts->chip_info->have_z)
			input_report_असल(input, ABS_MT_TOUCH_MAJOR, z[i]);
	पूर्ण

	input_mt_sync_frame(input);
	input_sync(input);

	वापस n_contacts;
पूर्ण

अटल irqवापस_t st1232_ts_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा st1232_ts_data *ts = dev_id;
	पूर्णांक count;
	पूर्णांक error;

	error = st1232_ts_पढ़ो_data(ts, REG_XY_COORDINATES, ts->पढ़ो_buf_len);
	अगर (error)
		जाओ out;

	count = st1232_ts_parse_and_report(ts);
	अगर (!count) अणु
		अगर (ts->low_latency_req.dev) अणु
			dev_pm_qos_हटाओ_request(&ts->low_latency_req);
			ts->low_latency_req.dev = शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (!ts->low_latency_req.dev) अणु
		/* First contact, request 100 us latency. */
		dev_pm_qos_add_ancestor_request(&ts->client->dev,
						&ts->low_latency_req,
						DEV_PM_QOS_RESUME_LATENCY, 100);
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम st1232_ts_घातer(काष्ठा st1232_ts_data *ts, bool घातeron)
अणु
	अगर (ts->reset_gpio)
		gpiod_set_value_cansleep(ts->reset_gpio, !घातeron);
पूर्ण

अटल व्योम st1232_ts_घातer_off(व्योम *data)
अणु
	st1232_ts_घातer(data, false);
पूर्ण

अटल स्थिर काष्ठा st_chip_info st1232_chip_info = अणु
	.have_z		= true,
	.max_area	= 0xff,
	.max_fingers	= 2,
पूर्ण;

अटल स्थिर काष्ठा st_chip_info st1633_chip_info = अणु
	.have_z		= false,
	.max_area	= 0x00,
	.max_fingers	= 5,
पूर्ण;

अटल पूर्णांक st1232_ts_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा st_chip_info *match;
	काष्ठा st1232_ts_data *ts;
	काष्ठा input_dev *input_dev;
	u16 max_x, max_y;
	पूर्णांक error;

	match = device_get_match_data(&client->dev);
	अगर (!match && id)
		match = (स्थिर व्योम *)id->driver_data;
	अगर (!match) अणु
		dev_err(&client->dev, "unknown device model\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "need I2C_FUNC_I2C\n");
		वापस -EIO;
	पूर्ण

	अगर (!client->irq) अणु
		dev_err(&client->dev, "no IRQ?\n");
		वापस -EINVAL;
	पूर्ण

	ts = devm_kzalloc(&client->dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	ts->chip_info = match;

	/* allocate a buffer according to the number of रेजिस्टरs to पढ़ो */
	ts->पढ़ो_buf_len = ts->chip_info->max_fingers * 4;
	ts->पढ़ो_buf = devm_kzalloc(&client->dev, ts->पढ़ो_buf_len, GFP_KERNEL);
	अगर (!ts->पढ़ो_buf)
		वापस -ENOMEM;

	input_dev = devm_input_allocate_device(&client->dev);
	अगर (!input_dev)
		वापस -ENOMEM;

	ts->client = client;
	ts->input_dev = input_dev;

	ts->reset_gpio = devm_gpiod_get_optional(&client->dev, शून्य,
						 GPIOD_OUT_HIGH);
	अगर (IS_ERR(ts->reset_gpio)) अणु
		error = PTR_ERR(ts->reset_gpio);
		dev_err(&client->dev, "Unable to request GPIO pin: %d.\n",
			error);
		वापस error;
	पूर्ण

	st1232_ts_घातer(ts, true);

	error = devm_add_action_or_reset(&client->dev, st1232_ts_घातer_off, ts);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to install power off action: %d\n", error);
		वापस error;
	पूर्ण

	input_dev->name = "st1232-touchscreen";
	input_dev->id.bustype = BUS_I2C;

	/* Wait until device is पढ़ोy */
	error = st1232_ts_रुको_पढ़ोy(ts);
	अगर (error)
		वापस error;

	/* Read resolution from the chip */
	error = st1232_ts_पढ़ो_resolution(ts, &max_x, &max_y);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to read resolution: %d\n", error);
		वापस error;
	पूर्ण

	अगर (ts->chip_info->have_z)
		input_set_असल_params(input_dev, ABS_MT_TOUCH_MAJOR, 0,
				     ts->chip_info->max_area, 0, 0);

	input_set_असल_params(input_dev, ABS_MT_POSITION_X,
			     0, max_x, 0, 0);
	input_set_असल_params(input_dev, ABS_MT_POSITION_Y,
			     0, max_y, 0, 0);

	touchscreen_parse_properties(input_dev, true, &ts->prop);

	error = input_mt_init_slots(input_dev, ts->chip_info->max_fingers,
				    INPUT_MT_सूचीECT | INPUT_MT_TRACK |
					INPUT_MT_DROP_UNUSED);
	अगर (error) अणु
		dev_err(&client->dev, "failed to initialize MT slots\n");
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, st1232_ts_irq_handler,
					  IRQF_ONESHOT,
					  client->name, ts);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to register interrupt\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(ts->input_dev);
	अगर (error) अणु
		dev_err(&client->dev, "Unable to register %s input device\n",
			input_dev->name);
		वापस error;
	पूर्ण

	i2c_set_clientdata(client, ts);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused st1232_ts_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा st1232_ts_data *ts = i2c_get_clientdata(client);

	disable_irq(client->irq);

	अगर (!device_may_wakeup(&client->dev))
		st1232_ts_घातer(ts, false);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused st1232_ts_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा st1232_ts_data *ts = i2c_get_clientdata(client);

	अगर (!device_may_wakeup(&client->dev))
		st1232_ts_घातer(ts, true);

	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(st1232_ts_pm_ops,
			 st1232_ts_suspend, st1232_ts_resume);

अटल स्थिर काष्ठा i2c_device_id st1232_ts_id[] = अणु
	अणु ST1232_TS_NAME, (अचिन्हित दीर्घ)&st1232_chip_info पूर्ण,
	अणु ST1633_TS_NAME, (अचिन्हित दीर्घ)&st1633_chip_info पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, st1232_ts_id);

अटल स्थिर काष्ठा of_device_id st1232_ts_dt_ids[] = अणु
	अणु .compatible = "sitronix,st1232", .data = &st1232_chip_info पूर्ण,
	अणु .compatible = "sitronix,st1633", .data = &st1633_chip_info पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, st1232_ts_dt_ids);

अटल काष्ठा i2c_driver st1232_ts_driver = अणु
	.probe		= st1232_ts_probe,
	.id_table	= st1232_ts_id,
	.driver = अणु
		.name	= ST1232_TS_NAME,
		.of_match_table = st1232_ts_dt_ids,
		.pm	= &st1232_ts_pm_ops,
	पूर्ण,
पूर्ण;

module_i2c_driver(st1232_ts_driver);

MODULE_AUTHOR("Tony SIM <chinyeow.sim.xt@renesas.com>");
MODULE_AUTHOR("Martin Kepplinger <martin.kepplinger@ginzinger.com>");
MODULE_DESCRIPTION("SITRONIX ST1232 Touchscreen Controller Driver");
MODULE_LICENSE("GPL v2");
