<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Pixcir I2C touchscreen controllers.
 *
 * Copyright (C) 2010-2011 Pixcir, Inc.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#घोषणा PIXCIR_MAX_SLOTS       5 /* Max fingers supported by driver */

/*
 * Register map
 */
#घोषणा PIXCIR_REG_POWER_MODE	51
#घोषणा PIXCIR_REG_INT_MODE	52

/*
 * Power modes:
 * active: max scan speed
 * idle: lower scan speed with स्वतःmatic transition to active on touch
 * halt: datasheet says sleep but this is more like halt as the chip
 *       घड़ीs are cut and it can only be brought out of this mode
 *	 using the RESET pin.
 */
क्रमागत pixcir_घातer_mode अणु
	PIXCIR_POWER_ACTIVE,
	PIXCIR_POWER_IDLE,
	PIXCIR_POWER_HALT,
पूर्ण;

#घोषणा PIXCIR_POWER_MODE_MASK	0x03
#घोषणा PIXCIR_POWER_ALLOW_IDLE (1UL << 2)

/*
 * Interrupt modes:
 * periodical: पूर्णांकerrupt is निश्चितed periodicaly
 * dअगरf coordinates: पूर्णांकerrupt is निश्चितed when coordinates change
 * level on touch: पूर्णांकerrupt level निश्चितed during touch
 * pulse on touch: पूर्णांकerrupt pulse निश्चितed during touch
 *
 */
क्रमागत pixcir_पूर्णांक_mode अणु
	PIXCIR_INT_PERIODICAL,
	PIXCIR_INT_DIFF_COORD,
	PIXCIR_INT_LEVEL_TOUCH,
	PIXCIR_INT_PULSE_TOUCH,
पूर्ण;

#घोषणा PIXCIR_INT_MODE_MASK	0x03
#घोषणा PIXCIR_INT_ENABLE	(1UL << 3)
#घोषणा PIXCIR_INT_POL_HIGH	(1UL << 2)

/**
 * काष्ठा pixcir_i2c_chip_data - chip related data
 * @max_fingers:	Max number of fingers reported simultaneously by h/w
 * @has_hw_ids:		Hardware supports finger tracking IDs
 *
 */
काष्ठा pixcir_i2c_chip_data अणु
	u8 max_fingers;
	bool has_hw_ids;
पूर्ण;

काष्ठा pixcir_i2c_ts_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा gpio_desc *gpio_attb;
	काष्ठा gpio_desc *gpio_reset;
	काष्ठा gpio_desc *gpio_enable;
	काष्ठा gpio_desc *gpio_wake;
	स्थिर काष्ठा pixcir_i2c_chip_data *chip;
	काष्ठा touchscreen_properties prop;
	bool running;
पूर्ण;

काष्ठा pixcir_report_data अणु
	पूर्णांक num_touches;
	काष्ठा input_mt_pos pos[PIXCIR_MAX_SLOTS];
	पूर्णांक ids[PIXCIR_MAX_SLOTS];
पूर्ण;

अटल व्योम pixcir_ts_parse(काष्ठा pixcir_i2c_ts_data *tsdata,
			    काष्ठा pixcir_report_data *report)
अणु
	u8 rdbuf[2 + PIXCIR_MAX_SLOTS * 5];
	u8 wrbuf[1] = अणु 0 पूर्ण;
	u8 *bufptr;
	u8 touch;
	पूर्णांक ret, i;
	पूर्णांक पढ़ोsize;
	स्थिर काष्ठा pixcir_i2c_chip_data *chip = tsdata->chip;

	स_रखो(report, 0, माप(काष्ठा pixcir_report_data));

	i = chip->has_hw_ids ? 1 : 0;
	पढ़ोsize = 2 + tsdata->chip->max_fingers * (4 + i);
	अगर (पढ़ोsize > माप(rdbuf))
		पढ़ोsize = माप(rdbuf);

	ret = i2c_master_send(tsdata->client, wrbuf, माप(wrbuf));
	अगर (ret != माप(wrbuf)) अणु
		dev_err(&tsdata->client->dev,
			"%s: i2c_master_send failed(), ret=%d\n",
			__func__, ret);
		वापस;
	पूर्ण

	ret = i2c_master_recv(tsdata->client, rdbuf, पढ़ोsize);
	अगर (ret != पढ़ोsize) अणु
		dev_err(&tsdata->client->dev,
			"%s: i2c_master_recv failed(), ret=%d\n",
			__func__, ret);
		वापस;
	पूर्ण

	touch = rdbuf[0] & 0x7;
	अगर (touch > tsdata->chip->max_fingers)
		touch = tsdata->chip->max_fingers;

	report->num_touches = touch;
	bufptr = &rdbuf[2];

	क्रम (i = 0; i < touch; i++) अणु
		touchscreen_set_mt_pos(&report->pos[i], &tsdata->prop,
				       get_unaligned_le16(bufptr),
				       get_unaligned_le16(bufptr + 2));
		अगर (chip->has_hw_ids) अणु
			report->ids[i] = bufptr[4];
			bufptr = bufptr + 5;
		पूर्ण अन्यथा अणु
			bufptr = bufptr + 4;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pixcir_ts_report(काष्ठा pixcir_i2c_ts_data *ts,
			     काष्ठा pixcir_report_data *report)
अणु
	पूर्णांक slots[PIXCIR_MAX_SLOTS];
	पूर्णांक n, i, slot;
	काष्ठा device *dev = &ts->client->dev;
	स्थिर काष्ठा pixcir_i2c_chip_data *chip = ts->chip;

	n = report->num_touches;
	अगर (n > PIXCIR_MAX_SLOTS)
		n = PIXCIR_MAX_SLOTS;

	अगर (!ts->chip->has_hw_ids)
		input_mt_assign_slots(ts->input, slots, report->pos, n, 0);

	क्रम (i = 0; i < n; i++) अणु
		अगर (chip->has_hw_ids) अणु
			slot = input_mt_get_slot_by_key(ts->input,
							report->ids[i]);
			अगर (slot < 0) अणु
				dev_dbg(dev, "no free slot for id 0x%x\n",
					report->ids[i]);
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			slot = slots[i];
		पूर्ण

		input_mt_slot(ts->input, slot);
		input_mt_report_slot_state(ts->input, MT_TOOL_FINGER, true);

		input_report_असल(ts->input, ABS_MT_POSITION_X,
				 report->pos[i].x);
		input_report_असल(ts->input, ABS_MT_POSITION_Y,
				 report->pos[i].y);

		dev_dbg(dev, "%d: slot %d, x %d, y %d\n",
			i, slot, report->pos[i].x, report->pos[i].y);
	पूर्ण

	input_mt_sync_frame(ts->input);
	input_sync(ts->input);
पूर्ण

अटल irqवापस_t pixcir_ts_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pixcir_i2c_ts_data *tsdata = dev_id;
	काष्ठा pixcir_report_data report;

	जबतक (tsdata->running) अणु
		/* parse packet */
		pixcir_ts_parse(tsdata, &report);

		/* report it */
		pixcir_ts_report(tsdata, &report);

		अगर (gpiod_get_value_cansleep(tsdata->gpio_attb)) अणु
			अगर (report.num_touches) अणु
				/*
				 * Last report with no finger up?
				 * Do it now then.
				 */
				input_mt_sync_frame(tsdata->input);
				input_sync(tsdata->input);
			पूर्ण
			अवरोध;
		पूर्ण

		msleep(20);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pixcir_reset(काष्ठा pixcir_i2c_ts_data *tsdata)
अणु
	अगर (!IS_ERR_OR_शून्य(tsdata->gpio_reset)) अणु
		gpiod_set_value_cansleep(tsdata->gpio_reset, 1);
		ndelay(100);	/* datasheet section 1.2.3 says 80ns min. */
		gpiod_set_value_cansleep(tsdata->gpio_reset, 0);
		/* रुको क्रम controller पढ़ोy. 100ms guess. */
		msleep(100);
	पूर्ण
पूर्ण

अटल पूर्णांक pixcir_set_घातer_mode(काष्ठा pixcir_i2c_ts_data *ts,
				 क्रमागत pixcir_घातer_mode mode)
अणु
	काष्ठा device *dev = &ts->client->dev;
	पूर्णांक ret;

	अगर (mode == PIXCIR_POWER_ACTIVE || mode == PIXCIR_POWER_IDLE) अणु
		अगर (ts->gpio_wake)
			gpiod_set_value_cansleep(ts->gpio_wake, 1);
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(ts->client, PIXCIR_REG_POWER_MODE);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: can't read reg %d : %d\n",
			__func__, PIXCIR_REG_POWER_MODE, ret);
		वापस ret;
	पूर्ण

	ret &= ~PIXCIR_POWER_MODE_MASK;
	ret |= mode;

	/* Always AUTO_IDLE */
	ret |= PIXCIR_POWER_ALLOW_IDLE;

	ret = i2c_smbus_ग_लिखो_byte_data(ts->client, PIXCIR_REG_POWER_MODE, ret);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: can't write reg %d : %d\n",
			__func__, PIXCIR_REG_POWER_MODE, ret);
		वापस ret;
	पूर्ण

	अगर (mode == PIXCIR_POWER_HALT) अणु
		अगर (ts->gpio_wake)
			gpiod_set_value_cansleep(ts->gpio_wake, 0);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set the पूर्णांकerrupt mode क्रम the device i.e. ATTB line behaviour
 *
 * @polarity : 1 क्रम active high, 0 क्रम active low.
 */
अटल पूर्णांक pixcir_set_पूर्णांक_mode(काष्ठा pixcir_i2c_ts_data *ts,
			       क्रमागत pixcir_पूर्णांक_mode mode, bool polarity)
अणु
	काष्ठा device *dev = &ts->client->dev;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(ts->client, PIXCIR_REG_INT_MODE);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: can't read reg %d : %d\n",
			__func__, PIXCIR_REG_INT_MODE, ret);
		वापस ret;
	पूर्ण

	ret &= ~PIXCIR_INT_MODE_MASK;
	ret |= mode;

	अगर (polarity)
		ret |= PIXCIR_INT_POL_HIGH;
	अन्यथा
		ret &= ~PIXCIR_INT_POL_HIGH;

	ret = i2c_smbus_ग_लिखो_byte_data(ts->client, PIXCIR_REG_INT_MODE, ret);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: can't write reg %d : %d\n",
			__func__, PIXCIR_REG_INT_MODE, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Enable/disable पूर्णांकerrupt generation
 */
अटल पूर्णांक pixcir_पूर्णांक_enable(काष्ठा pixcir_i2c_ts_data *ts, bool enable)
अणु
	काष्ठा device *dev = &ts->client->dev;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(ts->client, PIXCIR_REG_INT_MODE);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: can't read reg %d : %d\n",
			__func__, PIXCIR_REG_INT_MODE, ret);
		वापस ret;
	पूर्ण

	अगर (enable)
		ret |= PIXCIR_INT_ENABLE;
	अन्यथा
		ret &= ~PIXCIR_INT_ENABLE;

	ret = i2c_smbus_ग_लिखो_byte_data(ts->client, PIXCIR_REG_INT_MODE, ret);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: can't write reg %d : %d\n",
			__func__, PIXCIR_REG_INT_MODE, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pixcir_start(काष्ठा pixcir_i2c_ts_data *ts)
अणु
	काष्ठा device *dev = &ts->client->dev;
	पूर्णांक error;

	अगर (ts->gpio_enable) अणु
		gpiod_set_value_cansleep(ts->gpio_enable, 1);
		msleep(100);
	पूर्ण

	/* LEVEL_TOUCH पूर्णांकerrupt with active low polarity */
	error = pixcir_set_पूर्णांक_mode(ts, PIXCIR_INT_LEVEL_TOUCH, 0);
	अगर (error) अणु
		dev_err(dev, "Failed to set interrupt mode: %d\n", error);
		वापस error;
	पूर्ण

	ts->running = true;
	mb();	/* Update status beक्रमe IRQ can fire */

	/* enable पूर्णांकerrupt generation */
	error = pixcir_पूर्णांक_enable(ts, true);
	अगर (error) अणु
		dev_err(dev, "Failed to enable interrupt generation: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pixcir_stop(काष्ठा pixcir_i2c_ts_data *ts)
अणु
	पूर्णांक error;

	/* Disable पूर्णांकerrupt generation */
	error = pixcir_पूर्णांक_enable(ts, false);
	अगर (error) अणु
		dev_err(&ts->client->dev,
			"Failed to disable interrupt generation: %d\n",
			error);
		वापस error;
	पूर्ण

	/* Exit ISR अगर running, no more report parsing */
	ts->running = false;
	mb();	/* update status beक्रमe we synchronize irq */

	/* Wait till running ISR is complete */
	synchronize_irq(ts->client->irq);

	अगर (ts->gpio_enable)
		gpiod_set_value_cansleep(ts->gpio_enable, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक pixcir_input_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा pixcir_i2c_ts_data *ts = input_get_drvdata(dev);

	वापस pixcir_start(ts);
पूर्ण

अटल व्योम pixcir_input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा pixcir_i2c_ts_data *ts = input_get_drvdata(dev);

	pixcir_stop(ts);
पूर्ण

अटल पूर्णांक __maybe_unused pixcir_i2c_ts_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pixcir_i2c_ts_data *ts = i2c_get_clientdata(client);
	काष्ठा input_dev *input = ts->input;
	पूर्णांक ret = 0;

	mutex_lock(&input->mutex);

	अगर (device_may_wakeup(&client->dev)) अणु
		अगर (!input_device_enabled(input)) अणु
			ret = pixcir_start(ts);
			अगर (ret) अणु
				dev_err(dev, "Failed to start\n");
				जाओ unlock;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (input_device_enabled(input)) अणु
		ret = pixcir_stop(ts);
	पूर्ण

unlock:
	mutex_unlock(&input->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused pixcir_i2c_ts_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pixcir_i2c_ts_data *ts = i2c_get_clientdata(client);
	काष्ठा input_dev *input = ts->input;
	पूर्णांक ret = 0;

	mutex_lock(&input->mutex);

	अगर (device_may_wakeup(&client->dev)) अणु
		अगर (!input_device_enabled(input)) अणु
			ret = pixcir_stop(ts);
			अगर (ret) अणु
				dev_err(dev, "Failed to stop\n");
				जाओ unlock;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (input_device_enabled(input)) अणु
		ret = pixcir_start(ts);
	पूर्ण

unlock:
	mutex_unlock(&input->mutex);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pixcir_dev_pm_ops,
			 pixcir_i2c_ts_suspend, pixcir_i2c_ts_resume);

अटल पूर्णांक pixcir_i2c_ts_probe(काष्ठा i2c_client *client,
			       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा pixcir_i2c_ts_data *tsdata;
	काष्ठा input_dev *input;
	पूर्णांक error;

	tsdata = devm_kzalloc(dev, माप(*tsdata), GFP_KERNEL);
	अगर (!tsdata)
		वापस -ENOMEM;

	tsdata->chip = device_get_match_data(dev);
	अगर (!tsdata->chip && id)
		tsdata->chip = (स्थिर व्योम *)id->driver_data;
	अगर (!tsdata->chip) अणु
		dev_err(dev, "can't locate chip data\n");
		वापस -EINVAL;
	पूर्ण

	input = devm_input_allocate_device(dev);
	अगर (!input) अणु
		dev_err(dev, "Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	tsdata->client = client;
	tsdata->input = input;

	input->name = client->name;
	input->id.bustype = BUS_I2C;
	input->खोलो = pixcir_input_खोलो;
	input->बंद = pixcir_input_बंद;

	input_set_capability(input, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(input, EV_ABS, ABS_MT_POSITION_Y);
	touchscreen_parse_properties(input, true, &tsdata->prop);
	अगर (!input_असल_get_max(input, ABS_MT_POSITION_X) ||
	    !input_असल_get_max(input, ABS_MT_POSITION_Y)) अणु
		dev_err(dev, "Touchscreen size is not specified\n");
		वापस -EINVAL;
	पूर्ण

	error = input_mt_init_slots(input, tsdata->chip->max_fingers,
				    INPUT_MT_सूचीECT | INPUT_MT_DROP_UNUSED);
	अगर (error) अणु
		dev_err(dev, "Error initializing Multi-Touch slots\n");
		वापस error;
	पूर्ण

	input_set_drvdata(input, tsdata);

	tsdata->gpio_attb = devm_gpiod_get(dev, "attb", GPIOD_IN);
	अगर (IS_ERR(tsdata->gpio_attb)) अणु
		error = PTR_ERR(tsdata->gpio_attb);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "Failed to request ATTB gpio: %d\n",
				error);
		वापस error;
	पूर्ण

	tsdata->gpio_reset = devm_gpiod_get_optional(dev, "reset",
						     GPIOD_OUT_LOW);
	अगर (IS_ERR(tsdata->gpio_reset)) अणु
		error = PTR_ERR(tsdata->gpio_reset);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "Failed to request RESET gpio: %d\n",
				error);
		वापस error;
	पूर्ण

	tsdata->gpio_wake = devm_gpiod_get_optional(dev, "wake",
						    GPIOD_OUT_HIGH);
	अगर (IS_ERR(tsdata->gpio_wake)) अणु
		error = PTR_ERR(tsdata->gpio_wake);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "Failed to get wake gpio: %d\n", error);
		वापस error;
	पूर्ण

	tsdata->gpio_enable = devm_gpiod_get_optional(dev, "enable",
						      GPIOD_OUT_HIGH);
	अगर (IS_ERR(tsdata->gpio_enable)) अणु
		error = PTR_ERR(tsdata->gpio_enable);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "Failed to get enable gpio: %d\n", error);
		वापस error;
	पूर्ण

	अगर (tsdata->gpio_enable)
		msleep(100);

	error = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य, pixcir_ts_isr,
					  IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					  client->name, tsdata);
	अगर (error) अणु
		dev_err(dev, "failed to request irq %d\n", client->irq);
		वापस error;
	पूर्ण

	pixcir_reset(tsdata);

	/* Always be in IDLE mode to save घातer, device supports स्वतः wake */
	error = pixcir_set_घातer_mode(tsdata, PIXCIR_POWER_IDLE);
	अगर (error) अणु
		dev_err(dev, "Failed to set IDLE mode\n");
		वापस error;
	पूर्ण

	/* Stop device till खोलोed */
	error = pixcir_stop(tsdata);
	अगर (error)
		वापस error;

	error = input_रेजिस्टर_device(input);
	अगर (error)
		वापस error;

	i2c_set_clientdata(client, tsdata);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pixcir_i2c_chip_data pixcir_ts_data = अणु
	.max_fingers = 2,
	/* no hw id support */
पूर्ण;

अटल स्थिर काष्ठा pixcir_i2c_chip_data pixcir_tangoc_data = अणु
	.max_fingers = 5,
	.has_hw_ids = true,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id pixcir_i2c_ts_id[] = अणु
	अणु "pixcir_ts", (अचिन्हित दीर्घ) &pixcir_ts_data पूर्ण,
	अणु "pixcir_tangoc", (अचिन्हित दीर्घ) &pixcir_tangoc_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pixcir_i2c_ts_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pixcir_of_match[] = अणु
	अणु .compatible = "pixcir,pixcir_ts", .data = &pixcir_ts_data पूर्ण,
	अणु .compatible = "pixcir,pixcir_tangoc", .data = &pixcir_tangoc_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pixcir_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver pixcir_i2c_ts_driver = अणु
	.driver = अणु
		.name	= "pixcir_ts",
		.pm	= &pixcir_dev_pm_ops,
		.of_match_table = of_match_ptr(pixcir_of_match),
	पूर्ण,
	.probe		= pixcir_i2c_ts_probe,
	.id_table	= pixcir_i2c_ts_id,
पूर्ण;

module_i2c_driver(pixcir_i2c_ts_driver);

MODULE_AUTHOR("Jianchun Bian <jcbian@pixcir.com.cn>, Dequan Meng <dqmeng@pixcir.com.cn>");
MODULE_DESCRIPTION("Pixcir I2C Touchscreen Driver");
MODULE_LICENSE("GPL");
