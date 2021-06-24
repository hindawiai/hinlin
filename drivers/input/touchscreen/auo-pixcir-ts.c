<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम AUO in-cell touchscreens
 *
 * Copyright (c) 2011 Heiko Stuebner <heiko@sntech.de>
 *
 * loosely based on auo_touch.c from Dell Streak venकरोr-kernel
 *
 * Copyright (c) 2008 QUALCOMM Incorporated.
 * Copyright (c) 2008 QUALCOMM USA, INC.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/input/auo-pixcir-ts.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>

/*
 * Coordinate calculation:
 * X1 = X1_LSB + X1_MSB*256
 * Y1 = Y1_LSB + Y1_MSB*256
 * X2 = X2_LSB + X2_MSB*256
 * Y2 = Y2_LSB + Y2_MSB*256
 */
#घोषणा AUO_PIXCIR_REG_X1_LSB		0x00
#घोषणा AUO_PIXCIR_REG_X1_MSB		0x01
#घोषणा AUO_PIXCIR_REG_Y1_LSB		0x02
#घोषणा AUO_PIXCIR_REG_Y1_MSB		0x03
#घोषणा AUO_PIXCIR_REG_X2_LSB		0x04
#घोषणा AUO_PIXCIR_REG_X2_MSB		0x05
#घोषणा AUO_PIXCIR_REG_Y2_LSB		0x06
#घोषणा AUO_PIXCIR_REG_Y2_MSB		0x07

#घोषणा AUO_PIXCIR_REG_STRENGTH		0x0d
#घोषणा AUO_PIXCIR_REG_STRENGTH_X1_LSB	0x0e
#घोषणा AUO_PIXCIR_REG_STRENGTH_X1_MSB	0x0f

#घोषणा AUO_PIXCIR_REG_RAW_DATA_X	0x2b
#घोषणा AUO_PIXCIR_REG_RAW_DATA_Y	0x4f

#घोषणा AUO_PIXCIR_REG_X_SENSITIVITY	0x6f
#घोषणा AUO_PIXCIR_REG_Y_SENSITIVITY	0x70
#घोषणा AUO_PIXCIR_REG_INT_SETTING	0x71
#घोषणा AUO_PIXCIR_REG_INT_WIDTH	0x72
#घोषणा AUO_PIXCIR_REG_POWER_MODE	0x73

#घोषणा AUO_PIXCIR_REG_VERSION		0x77
#घोषणा AUO_PIXCIR_REG_CALIBRATE	0x78

#घोषणा AUO_PIXCIR_REG_TOUCHAREA_X1	0x1e
#घोषणा AUO_PIXCIR_REG_TOUCHAREA_Y1	0x1f
#घोषणा AUO_PIXCIR_REG_TOUCHAREA_X2	0x20
#घोषणा AUO_PIXCIR_REG_TOUCHAREA_Y2	0x21

#घोषणा AUO_PIXCIR_REG_EEPROM_CALIB_X	0x42
#घोषणा AUO_PIXCIR_REG_EEPROM_CALIB_Y	0xad

#घोषणा AUO_PIXCIR_INT_TPNUM_MASK	0xe0
#घोषणा AUO_PIXCIR_INT_TPNUM_SHIFT	5
#घोषणा AUO_PIXCIR_INT_RELEASE		(1 << 4)
#घोषणा AUO_PIXCIR_INT_ENABLE		(1 << 3)
#घोषणा AUO_PIXCIR_INT_POL_HIGH		(1 << 2)
#घोषणा AUO_PIXCIR_INT_MODE_MASK	0x03

/*
 * Power modes:
 * active:	scan speed 60Hz
 * sleep:	scan speed 10Hz can be स्वतः-activated, wakeup on 1st touch
 * deep sleep:	scan speed 1Hz can only be entered or left manually.
 */
#घोषणा AUO_PIXCIR_POWER_ACTIVE		0x00
#घोषणा AUO_PIXCIR_POWER_SLEEP		0x01
#घोषणा AUO_PIXCIR_POWER_DEEP_SLEEP	0x02
#घोषणा AUO_PIXCIR_POWER_MASK		0x03

#घोषणा AUO_PIXCIR_POWER_ALLOW_SLEEP	(1 << 2)
#घोषणा AUO_PIXCIR_POWER_IDLE_TIME(ms)	((ms & 0xf) << 4)

#घोषणा AUO_PIXCIR_CALIBRATE		0x03

#घोषणा AUO_PIXCIR_EEPROM_CALIB_X_LEN	62
#घोषणा AUO_PIXCIR_EEPROM_CALIB_Y_LEN	36

#घोषणा AUO_PIXCIR_RAW_DATA_X_LEN	18
#घोषणा AUO_PIXCIR_RAW_DATA_Y_LEN	11

#घोषणा AUO_PIXCIR_STRENGTH_ENABLE	(1 << 0)

/* Touchscreen असलolute values */
#घोषणा AUO_PIXCIR_REPORT_POINTS	2
#घोषणा AUO_PIXCIR_MAX_AREA		0xff
#घोषणा AUO_PIXCIR_PENUP_TIMEOUT_MS	10

काष्ठा auo_pixcir_ts अणु
	काष्ठा i2c_client	*client;
	काष्ठा input_dev	*input;
	स्थिर काष्ठा auo_pixcir_ts_platdata *pdata;
	अक्षर			phys[32];

	/* special handling क्रम touch_indicate पूर्णांकerupt mode */
	bool			touch_ind_mode;

	रुको_queue_head_t	रुको;
	bool			stopped;
पूर्ण;

काष्ठा auo_poपूर्णांक_t अणु
	पूर्णांक	coord_x;
	पूर्णांक	coord_y;
	पूर्णांक	area_major;
	पूर्णांक	area_minor;
	पूर्णांक	orientation;
पूर्ण;

अटल पूर्णांक auo_pixcir_collect_data(काष्ठा auo_pixcir_ts *ts,
				   काष्ठा auo_poपूर्णांक_t *poपूर्णांक)
अणु
	काष्ठा i2c_client *client = ts->client;
	स्थिर काष्ठा auo_pixcir_ts_platdata *pdata = ts->pdata;
	uपूर्णांक8_t raw_coord[8];
	uपूर्णांक8_t raw_area[4];
	पूर्णांक i, ret;

	/* touch coordinates */
	ret = i2c_smbus_पढ़ो_i2c_block_data(client, AUO_PIXCIR_REG_X1_LSB,
					    8, raw_coord);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to read coordinate, %d\n", ret);
		वापस ret;
	पूर्ण

	/* touch area */
	ret = i2c_smbus_पढ़ो_i2c_block_data(client, AUO_PIXCIR_REG_TOUCHAREA_X1,
					    4, raw_area);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "could not read touch area, %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < AUO_PIXCIR_REPORT_POINTS; i++) अणु
		poपूर्णांक[i].coord_x =
			raw_coord[4 * i + 1] << 8 | raw_coord[4 * i];
		poपूर्णांक[i].coord_y =
			raw_coord[4 * i + 3] << 8 | raw_coord[4 * i + 2];

		अगर (poपूर्णांक[i].coord_x > pdata->x_max ||
		    poपूर्णांक[i].coord_y > pdata->y_max) अणु
			dev_warn(&client->dev, "coordinates (%d,%d) invalid\n",
				poपूर्णांक[i].coord_x, poपूर्णांक[i].coord_y);
			poपूर्णांक[i].coord_x = poपूर्णांक[i].coord_y = 0;
		पूर्ण

		/* determine touch major, minor and orientation */
		poपूर्णांक[i].area_major = max(raw_area[2 * i], raw_area[2 * i + 1]);
		poपूर्णांक[i].area_minor = min(raw_area[2 * i], raw_area[2 * i + 1]);
		poपूर्णांक[i].orientation = raw_area[2 * i] > raw_area[2 * i + 1];
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t auo_pixcir_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा auo_pixcir_ts *ts = dev_id;
	स्थिर काष्ठा auo_pixcir_ts_platdata *pdata = ts->pdata;
	काष्ठा auo_poपूर्णांक_t poपूर्णांक[AUO_PIXCIR_REPORT_POINTS];
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक fingers = 0;
	पूर्णांक असल = -1;

	जबतक (!ts->stopped) अणु

		/* check क्रम up event in touch touch_ind_mode */
		अगर (ts->touch_ind_mode) अणु
			अगर (gpio_get_value(pdata->gpio_पूर्णांक) == 0) अणु
				input_mt_sync(ts->input);
				input_report_key(ts->input, BTN_TOUCH, 0);
				input_sync(ts->input);
				अवरोध;
			पूर्ण
		पूर्ण

		ret = auo_pixcir_collect_data(ts, poपूर्णांक);
		अगर (ret < 0) अणु
			/* we want to loop only in touch_ind_mode */
			अगर (!ts->touch_ind_mode)
				अवरोध;

			रुको_event_समयout(ts->रुको, ts->stopped,
				msecs_to_jअगरfies(AUO_PIXCIR_PENUP_TIMEOUT_MS));
			जारी;
		पूर्ण

		क्रम (i = 0; i < AUO_PIXCIR_REPORT_POINTS; i++) अणु
			अगर (poपूर्णांक[i].coord_x > 0 || poपूर्णांक[i].coord_y > 0) अणु
				input_report_असल(ts->input, ABS_MT_POSITION_X,
						 poपूर्णांक[i].coord_x);
				input_report_असल(ts->input, ABS_MT_POSITION_Y,
						 poपूर्णांक[i].coord_y);
				input_report_असल(ts->input, ABS_MT_TOUCH_MAJOR,
						 poपूर्णांक[i].area_major);
				input_report_असल(ts->input, ABS_MT_TOUCH_MINOR,
						 poपूर्णांक[i].area_minor);
				input_report_असल(ts->input, ABS_MT_ORIENTATION,
						 poपूर्णांक[i].orientation);
				input_mt_sync(ts->input);

				/* use first finger as source क्रम singletouch */
				अगर (fingers == 0)
					असल = i;

				/* number of touch poपूर्णांकs could also be queried
				 * via i2c but would require an additional call
				 */
				fingers++;
			पूर्ण
		पूर्ण

		input_report_key(ts->input, BTN_TOUCH, fingers > 0);

		अगर (असल > -1) अणु
			input_report_असल(ts->input, ABS_X, poपूर्णांक[असल].coord_x);
			input_report_असल(ts->input, ABS_Y, poपूर्णांक[असल].coord_y);
		पूर्ण

		input_sync(ts->input);

		/* we want to loop only in touch_ind_mode */
		अगर (!ts->touch_ind_mode)
			अवरोध;

		रुको_event_समयout(ts->रुको, ts->stopped,
				 msecs_to_jअगरfies(AUO_PIXCIR_PENUP_TIMEOUT_MS));
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Set the घातer mode of the device.
 * Valid modes are
 * - AUO_PIXCIR_POWER_ACTIVE
 * - AUO_PIXCIR_POWER_SLEEP - स्वतःmatically left on first touch
 * - AUO_PIXCIR_POWER_DEEP_SLEEP
 */
अटल पूर्णांक auo_pixcir_घातer_mode(काष्ठा auo_pixcir_ts *ts, पूर्णांक mode)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, AUO_PIXCIR_REG_POWER_MODE);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "unable to read reg %Xh, %d\n",
			AUO_PIXCIR_REG_POWER_MODE, ret);
		वापस ret;
	पूर्ण

	ret &= ~AUO_PIXCIR_POWER_MASK;
	ret |= mode;

	ret = i2c_smbus_ग_लिखो_byte_data(client, AUO_PIXCIR_REG_POWER_MODE, ret);
	अगर (ret) अणु
		dev_err(&client->dev, "unable to write reg %Xh, %d\n",
			AUO_PIXCIR_REG_POWER_MODE, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक auo_pixcir_पूर्णांक_config(काष्ठा auo_pixcir_ts *ts,
					   पूर्णांक पूर्णांक_setting)
अणु
	काष्ठा i2c_client *client = ts->client;
	स्थिर काष्ठा auo_pixcir_ts_platdata *pdata = ts->pdata;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, AUO_PIXCIR_REG_INT_SETTING);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "unable to read reg %Xh, %d\n",
			AUO_PIXCIR_REG_INT_SETTING, ret);
		वापस ret;
	पूर्ण

	ret &= ~AUO_PIXCIR_INT_MODE_MASK;
	ret |= पूर्णांक_setting;
	ret |= AUO_PIXCIR_INT_POL_HIGH; /* always use high क्रम पूर्णांकerrupts */

	ret = i2c_smbus_ग_लिखो_byte_data(client, AUO_PIXCIR_REG_INT_SETTING,
					ret);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "unable to write reg %Xh, %d\n",
			AUO_PIXCIR_REG_INT_SETTING, ret);
		वापस ret;
	पूर्ण

	ts->touch_ind_mode = pdata->पूर्णांक_setting == AUO_PIXCIR_INT_TOUCH_IND;

	वापस 0;
पूर्ण

/* control the generation of पूर्णांकerrupts on the device side */
अटल पूर्णांक auo_pixcir_पूर्णांक_toggle(काष्ठा auo_pixcir_ts *ts, bool enable)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, AUO_PIXCIR_REG_INT_SETTING);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "unable to read reg %Xh, %d\n",
			AUO_PIXCIR_REG_INT_SETTING, ret);
		वापस ret;
	पूर्ण

	अगर (enable)
		ret |= AUO_PIXCIR_INT_ENABLE;
	अन्यथा
		ret &= ~AUO_PIXCIR_INT_ENABLE;

	ret = i2c_smbus_ग_लिखो_byte_data(client, AUO_PIXCIR_REG_INT_SETTING,
					ret);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "unable to write reg %Xh, %d\n",
			AUO_PIXCIR_REG_INT_SETTING, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक auo_pixcir_start(काष्ठा auo_pixcir_ts *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक ret;

	ret = auo_pixcir_घातer_mode(ts, AUO_PIXCIR_POWER_ACTIVE);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "could not set power mode, %d\n",
			ret);
		वापस ret;
	पूर्ण

	ts->stopped = false;
	mb();
	enable_irq(client->irq);

	ret = auo_pixcir_पूर्णांक_toggle(ts, 1);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "could not enable interrupt, %d\n",
			ret);
		disable_irq(client->irq);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक auo_pixcir_stop(काष्ठा auo_pixcir_ts *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक ret;

	ret = auo_pixcir_पूर्णांक_toggle(ts, 0);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "could not disable interrupt, %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* disable receiving of पूर्णांकerrupts */
	disable_irq(client->irq);
	ts->stopped = true;
	mb();
	wake_up(&ts->रुको);

	वापस auo_pixcir_घातer_mode(ts, AUO_PIXCIR_POWER_DEEP_SLEEP);
पूर्ण

अटल पूर्णांक auo_pixcir_input_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा auo_pixcir_ts *ts = input_get_drvdata(dev);

	वापस auo_pixcir_start(ts);
पूर्ण

अटल व्योम auo_pixcir_input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा auo_pixcir_ts *ts = input_get_drvdata(dev);

	auo_pixcir_stop(ts);
पूर्ण

अटल पूर्णांक __maybe_unused auo_pixcir_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा auo_pixcir_ts *ts = i2c_get_clientdata(client);
	काष्ठा input_dev *input = ts->input;
	पूर्णांक ret = 0;

	mutex_lock(&input->mutex);

	/* when configured as wakeup source, device should always wake प्रणाली
	 * thereक्रमe start device अगर necessary
	 */
	अगर (device_may_wakeup(&client->dev)) अणु
		/* need to start device अगर not खोलो, to be wakeup source */
		अगर (!input_device_enabled(input)) अणु
			ret = auo_pixcir_start(ts);
			अगर (ret)
				जाओ unlock;
		पूर्ण

		enable_irq_wake(client->irq);
		ret = auo_pixcir_घातer_mode(ts, AUO_PIXCIR_POWER_SLEEP);
	पूर्ण अन्यथा अगर (input_device_enabled(input)) अणु
		ret = auo_pixcir_stop(ts);
	पूर्ण

unlock:
	mutex_unlock(&input->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused auo_pixcir_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा auo_pixcir_ts *ts = i2c_get_clientdata(client);
	काष्ठा input_dev *input = ts->input;
	पूर्णांक ret = 0;

	mutex_lock(&input->mutex);

	अगर (device_may_wakeup(&client->dev)) अणु
		disable_irq_wake(client->irq);

		/* need to stop device अगर it was not खोलो on suspend */
		अगर (!input_device_enabled(input)) अणु
			ret = auo_pixcir_stop(ts);
			अगर (ret)
				जाओ unlock;
		पूर्ण

		/* device wakes स्वतःmatically from SLEEP */
	पूर्ण अन्यथा अगर (input_device_enabled(input)) अणु
		ret = auo_pixcir_start(ts);
	पूर्ण

unlock:
	mutex_unlock(&input->mutex);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(auo_pixcir_pm_ops,
			 auo_pixcir_suspend, auo_pixcir_resume);

#अगर_घोषित CONFIG_OF
अटल काष्ठा auo_pixcir_ts_platdata *auo_pixcir_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा auo_pixcir_ts_platdata *pdata;
	काष्ठा device_node *np = dev->of_node;

	अगर (!np)
		वापस ERR_PTR(-ENOENT);

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	pdata->gpio_पूर्णांक = of_get_gpio(np, 0);
	अगर (!gpio_is_valid(pdata->gpio_पूर्णांक)) अणु
		dev_err(dev, "failed to get interrupt gpio\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pdata->gpio_rst = of_get_gpio(np, 1);
	अगर (!gpio_is_valid(pdata->gpio_rst)) अणु
		dev_err(dev, "failed to get reset gpio\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "x-size", &pdata->x_max)) अणु
		dev_err(dev, "failed to get x-size property\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "y-size", &pdata->y_max)) अणु
		dev_err(dev, "failed to get y-size property\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* शेष to निश्चितing the पूर्णांकerrupt when the screen is touched */
	pdata->पूर्णांक_setting = AUO_PIXCIR_INT_TOUCH_IND;

	वापस pdata;
पूर्ण
#अन्यथा
अटल काष्ठा auo_pixcir_ts_platdata *auo_pixcir_parse_dt(काष्ठा device *dev)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
#पूर्ण_अगर

अटल व्योम auo_pixcir_reset(व्योम *data)
अणु
	काष्ठा auo_pixcir_ts *ts = data;

	gpio_set_value(ts->pdata->gpio_rst, 0);
पूर्ण

अटल पूर्णांक auo_pixcir_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा auo_pixcir_ts_platdata *pdata;
	काष्ठा auo_pixcir_ts *ts;
	काष्ठा input_dev *input_dev;
	पूर्णांक version;
	पूर्णांक error;

	pdata = dev_get_platdata(&client->dev);
	अगर (!pdata) अणु
		pdata = auo_pixcir_parse_dt(&client->dev);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण

	ts = devm_kzalloc(&client->dev,
			  माप(काष्ठा auo_pixcir_ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	input_dev = devm_input_allocate_device(&client->dev);
	अगर (!input_dev) अणु
		dev_err(&client->dev, "could not allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	ts->pdata = pdata;
	ts->client = client;
	ts->input = input_dev;
	ts->touch_ind_mode = 0;
	ts->stopped = true;
	init_रुकोqueue_head(&ts->रुको);

	snम_लिखो(ts->phys, माप(ts->phys),
		 "%s/input0", dev_name(&client->dev));

	input_dev->name = "AUO-Pixcir touchscreen";
	input_dev->phys = ts->phys;
	input_dev->id.bustype = BUS_I2C;

	input_dev->खोलो = auo_pixcir_input_खोलो;
	input_dev->बंद = auo_pixcir_input_बंद;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);

	__set_bit(BTN_TOUCH, input_dev->keybit);

	/* For single touch */
	input_set_असल_params(input_dev, ABS_X, 0, pdata->x_max, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, pdata->y_max, 0, 0);

	/* For multi touch */
	input_set_असल_params(input_dev, ABS_MT_POSITION_X, 0,
			     pdata->x_max, 0, 0);
	input_set_असल_params(input_dev, ABS_MT_POSITION_Y, 0,
			     pdata->y_max, 0, 0);
	input_set_असल_params(input_dev, ABS_MT_TOUCH_MAJOR, 0,
			     AUO_PIXCIR_MAX_AREA, 0, 0);
	input_set_असल_params(input_dev, ABS_MT_TOUCH_MINOR, 0,
			     AUO_PIXCIR_MAX_AREA, 0, 0);
	input_set_असल_params(input_dev, ABS_MT_ORIENTATION, 0, 1, 0, 0);

	input_set_drvdata(ts->input, ts);

	error = devm_gpio_request_one(&client->dev, pdata->gpio_पूर्णांक,
				      GPIOF_सूची_IN, "auo_pixcir_ts_int");
	अगर (error) अणु
		dev_err(&client->dev, "request of gpio %d failed, %d\n",
			pdata->gpio_पूर्णांक, error);
		वापस error;
	पूर्ण

	error = devm_gpio_request_one(&client->dev, pdata->gpio_rst,
				      GPIOF_सूची_OUT | GPIOF_INIT_HIGH,
				      "auo_pixcir_ts_rst");
	अगर (error) अणु
		dev_err(&client->dev, "request of gpio %d failed, %d\n",
			pdata->gpio_rst, error);
		वापस error;
	पूर्ण

	error = devm_add_action_or_reset(&client->dev, auo_pixcir_reset, ts);
	अगर (error) अणु
		dev_err(&client->dev, "failed to register reset action, %d\n",
			error);
		वापस error;
	पूर्ण

	msleep(200);

	version = i2c_smbus_पढ़ो_byte_data(client, AUO_PIXCIR_REG_VERSION);
	अगर (version < 0) अणु
		error = version;
		वापस error;
	पूर्ण

	dev_info(&client->dev, "firmware version 0x%X\n", version);

	error = auo_pixcir_पूर्णांक_config(ts, pdata->पूर्णांक_setting);
	अगर (error)
		वापस error;

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, auo_pixcir_पूर्णांकerrupt,
					  IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					  input_dev->name, ts);
	अगर (error) अणु
		dev_err(&client->dev, "irq %d requested failed, %d\n",
			client->irq, error);
		वापस error;
	पूर्ण

	/* stop device and put it पूर्णांकo deep sleep until it is खोलोed */
	error = auo_pixcir_stop(ts);
	अगर (error)
		वापस error;

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&client->dev, "could not register input device, %d\n",
			error);
		वापस error;
	पूर्ण

	i2c_set_clientdata(client, ts);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id auo_pixcir_idtable[] = अणु
	अणु "auo_pixcir_ts", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, auo_pixcir_idtable);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id auo_pixcir_ts_dt_idtable[] = अणु
	अणु .compatible = "auo,auo_pixcir_ts" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, auo_pixcir_ts_dt_idtable);
#पूर्ण_अगर

अटल काष्ठा i2c_driver auo_pixcir_driver = अणु
	.driver = अणु
		.name	= "auo_pixcir_ts",
		.pm	= &auo_pixcir_pm_ops,
		.of_match_table	= of_match_ptr(auo_pixcir_ts_dt_idtable),
	पूर्ण,
	.probe		= auo_pixcir_probe,
	.id_table	= auo_pixcir_idtable,
पूर्ण;

module_i2c_driver(auo_pixcir_driver);

MODULE_DESCRIPTION("AUO-PIXCIR touchscreen driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Heiko Stuebner <heiko@sntech.de>");
