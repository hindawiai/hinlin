<शैली गुरु>
/*
 * Synaptics touchpad with I2C पूर्णांकerface
 *
 * Copyright (C) 2009 Compulab, Ltd.
 * Mike Rapoport <mike@compulab.co.il>
 * Igor Grinberg <grinberg@compulab.co.il>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm.h>

#घोषणा DRIVER_NAME		"synaptics_i2c"
/* maximum product id is 15 अक्षरacters */
#घोषणा PRODUCT_ID_LENGTH	15
#घोषणा REGISTER_LENGTH		8

/*
 * after soft reset, we should रुको क्रम 1 ms
 * beक्रमe the device becomes operational
 */
#घोषणा SOFT_RESET_DELAY_US	3000
/* and after hard reset, we should रुको क्रम max 500ms */
#घोषणा HARD_RESET_DELAY_MS	500

/* Registers by SMBus address */
#घोषणा PAGE_SEL_REG		0xff
#घोषणा DEVICE_STATUS_REG	0x09

/* Registers by RMI address */
#घोषणा DEV_CONTROL_REG		0x0000
#घोषणा INTERRUPT_EN_REG	0x0001
#घोषणा ERR_STAT_REG		0x0002
#घोषणा INT_REQ_STAT_REG	0x0003
#घोषणा DEV_COMMAND_REG		0x0004

#घोषणा RMI_PROT_VER_REG	0x0200
#घोषणा MANUFACT_ID_REG		0x0201
#घोषणा PHYS_INT_VER_REG	0x0202
#घोषणा PROD_PROPERTY_REG	0x0203
#घोषणा INFO_QUERY_REG0		0x0204
#घोषणा INFO_QUERY_REG1		(INFO_QUERY_REG0 + 1)
#घोषणा INFO_QUERY_REG2		(INFO_QUERY_REG0 + 2)
#घोषणा INFO_QUERY_REG3		(INFO_QUERY_REG0 + 3)

#घोषणा PRODUCT_ID_REG0		0x0210
#घोषणा PRODUCT_ID_REG1		(PRODUCT_ID_REG0 + 1)
#घोषणा PRODUCT_ID_REG2		(PRODUCT_ID_REG0 + 2)
#घोषणा PRODUCT_ID_REG3		(PRODUCT_ID_REG0 + 3)
#घोषणा PRODUCT_ID_REG4		(PRODUCT_ID_REG0 + 4)
#घोषणा PRODUCT_ID_REG5		(PRODUCT_ID_REG0 + 5)
#घोषणा PRODUCT_ID_REG6		(PRODUCT_ID_REG0 + 6)
#घोषणा PRODUCT_ID_REG7		(PRODUCT_ID_REG0 + 7)
#घोषणा PRODUCT_ID_REG8		(PRODUCT_ID_REG0 + 8)
#घोषणा PRODUCT_ID_REG9		(PRODUCT_ID_REG0 + 9)
#घोषणा PRODUCT_ID_REG10	(PRODUCT_ID_REG0 + 10)
#घोषणा PRODUCT_ID_REG11	(PRODUCT_ID_REG0 + 11)
#घोषणा PRODUCT_ID_REG12	(PRODUCT_ID_REG0 + 12)
#घोषणा PRODUCT_ID_REG13	(PRODUCT_ID_REG0 + 13)
#घोषणा PRODUCT_ID_REG14	(PRODUCT_ID_REG0 + 14)
#घोषणा PRODUCT_ID_REG15	(PRODUCT_ID_REG0 + 15)

#घोषणा DATA_REG0		0x0400
#घोषणा ABS_PRESSURE_REG	0x0401
#घोषणा ABS_MSB_X_REG		0x0402
#घोषणा ABS_LSB_X_REG		(ABS_MSB_X_REG + 1)
#घोषणा ABS_MSB_Y_REG		0x0404
#घोषणा ABS_LSB_Y_REG		(ABS_MSB_Y_REG + 1)
#घोषणा REL_X_REG		0x0406
#घोषणा REL_Y_REG		0x0407

#घोषणा DEV_QUERY_REG0		0x1000
#घोषणा DEV_QUERY_REG1		(DEV_QUERY_REG0 + 1)
#घोषणा DEV_QUERY_REG2		(DEV_QUERY_REG0 + 2)
#घोषणा DEV_QUERY_REG3		(DEV_QUERY_REG0 + 3)
#घोषणा DEV_QUERY_REG4		(DEV_QUERY_REG0 + 4)
#घोषणा DEV_QUERY_REG5		(DEV_QUERY_REG0 + 5)
#घोषणा DEV_QUERY_REG6		(DEV_QUERY_REG0 + 6)
#घोषणा DEV_QUERY_REG7		(DEV_QUERY_REG0 + 7)
#घोषणा DEV_QUERY_REG8		(DEV_QUERY_REG0 + 8)

#घोषणा GENERAL_2D_CONTROL_REG	0x1041
#घोषणा SENSOR_SENSITIVITY_REG	0x1044
#घोषणा SENS_MAX_POS_MSB_REG	0x1046
#घोषणा SENS_MAX_POS_LSB_REG	(SENS_MAX_POS_UPPER_REG + 1)

/* Register bits */
/* Device Control Register Bits */
#घोषणा REPORT_RATE_1ST_BIT	6

/* Interrupt Enable Register Bits (INTERRUPT_EN_REG) */
#घोषणा F10_ABS_INT_ENA		0
#घोषणा F10_REL_INT_ENA		1
#घोषणा F20_INT_ENA		2

/* Interrupt Request Register Bits (INT_REQ_STAT_REG | DEVICE_STATUS_REG) */
#घोषणा F10_ABS_INT_REQ		0
#घोषणा F10_REL_INT_REQ		1
#घोषणा F20_INT_REQ		2
/* Device Status Register Bits (DEVICE_STATUS_REG) */
#घोषणा STAT_CONFIGURED		6
#घोषणा STAT_ERROR		7

/* Device Command Register Bits (DEV_COMMAND_REG) */
#घोषणा RESET_COMMAND		0x01
#घोषणा REZERO_COMMAND		0x02

/* Data Register 0 Bits (DATA_REG0) */
#घोषणा GESTURE			3

/* Device Query Registers Bits */
/* DEV_QUERY_REG3 */
#घोषणा HAS_PALM_DETECT		1
#घोषणा HAS_MULTI_FING		2
#घोषणा HAS_SCROLLER		4
#घोषणा HAS_2D_SCROLL		5

/* General 2D Control Register Bits (GENERAL_2D_CONTROL_REG) */
#घोषणा NO_DECELERATION		1
#घोषणा REDUCE_REPORTING	3
#घोषणा NO_FILTER		5

/* Function Masks */
/* Device Control Register Masks (DEV_CONTROL_REG) */
#घोषणा REPORT_RATE_MSK		0xc0
#घोषणा SLEEP_MODE_MSK		0x07

/* Device Sleep Modes */
#घोषणा FULL_AWAKE		0x0
#घोषणा NORMAL_OP		0x1
#घोषणा LOW_PWR_OP		0x2
#घोषणा VERY_LOW_PWR_OP		0x3
#घोषणा SENS_SLEEP		0x4
#घोषणा SLEEP_MOD		0x5
#घोषणा DEEP_SLEEP		0x6
#घोषणा HIBERNATE		0x7

/* Interrupt Register Mask */
/* (INT_REQ_STAT_REG | DEVICE_STATUS_REG | INTERRUPT_EN_REG) */
#घोषणा INT_ENA_REQ_MSK		0x07
#घोषणा INT_ENA_ABS_MSK		0x01
#घोषणा INT_ENA_REL_MSK		0x02
#घोषणा INT_ENA_F20_MSK		0x04

/* Device Status Register Masks (DEVICE_STATUS_REG) */
#घोषणा CONFIGURED_MSK		0x40
#घोषणा ERROR_MSK		0x80

/* Data Register 0 Masks */
#घोषणा FINGER_WIDTH_MSK	0xf0
#घोषणा GESTURE_MSK		0x08
#घोषणा SENSOR_STATUS_MSK	0x07

/*
 * MSB Position Register Masks
 * ABS_MSB_X_REG | ABS_MSB_Y_REG | SENS_MAX_POS_MSB_REG |
 * DEV_QUERY_REG3 | DEV_QUERY_REG5
 */
#घोषणा MSB_POSITION_MSK	0x1f

/* Device Query Registers Masks */

/* DEV_QUERY_REG2 */
#घोषणा NUM_EXTRA_POS_MSK	0x07

/* When in IRQ mode पढ़ो the device every THREAD_IRQ_SLEEP_SECS */
#घोषणा THREAD_IRQ_SLEEP_SECS	2
#घोषणा THREAD_IRQ_SLEEP_MSECS	(THREAD_IRQ_SLEEP_SECS * MSEC_PER_SEC)

/*
 * When in Polling mode and no data received क्रम NO_DATA_THRES msecs
 * reduce the polling rate to NO_DATA_SLEEP_MSECS
 */
#घोषणा NO_DATA_THRES		(MSEC_PER_SEC)
#घोषणा NO_DATA_SLEEP_MSECS	(MSEC_PER_SEC / 4)

/* Control touchpad's No Deceleration option */
अटल bool no_decel = true;
module_param(no_decel, bool, 0644);
MODULE_PARM_DESC(no_decel, "No Deceleration. Default = 1 (on)");

/* Control touchpad's Reduced Reporting option */
अटल bool reduce_report;
module_param(reduce_report, bool, 0644);
MODULE_PARM_DESC(reduce_report, "Reduced Reporting. Default = 0 (off)");

/* Control touchpad's No Filter option */
अटल bool no_filter;
module_param(no_filter, bool, 0644);
MODULE_PARM_DESC(no_filter, "No Filter. Default = 0 (off)");

/*
 * touchpad Attention line is Active Low and Open Drain,
 * thereक्रमe should be connected to pulled up line
 * and the irq configuration should be set to Falling Edge Trigger
 */
/* Control IRQ / Polling option */
अटल bool polling_req;
module_param(polling_req, bool, 0444);
MODULE_PARM_DESC(polling_req, "Request Polling. Default = 0 (use irq)");

/* Control Polling Rate */
अटल पूर्णांक scan_rate = 80;
module_param(scan_rate, पूर्णांक, 0644);
MODULE_PARM_DESC(scan_rate, "Polling rate in times/sec. Default = 80");

/* The मुख्य device काष्ठाure */
काष्ठा synaptics_i2c अणु
	काष्ठा i2c_client	*client;
	काष्ठा input_dev	*input;
	काष्ठा delayed_work	dwork;
	पूर्णांक			no_data_count;
	पूर्णांक			no_decel_param;
	पूर्णांक			reduce_report_param;
	पूर्णांक			no_filter_param;
	पूर्णांक			scan_rate_param;
	पूर्णांक			scan_ms;
पूर्ण;

अटल अंतरभूत व्योम set_scan_rate(काष्ठा synaptics_i2c *touch, पूर्णांक scan_rate)
अणु
	touch->scan_ms = MSEC_PER_SEC / scan_rate;
	touch->scan_rate_param = scan_rate;
पूर्ण

/*
 * Driver's initial design makes no race condition possible on i2c bus,
 * so there is no need in any locking.
 * Keep it in mind, जबतक playing with the code.
 */
अटल s32 synaptics_i2c_reg_get(काष्ठा i2c_client *client, u16 reg)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, PAGE_SEL_REG, reg >> 8);
	अगर (ret == 0)
		ret = i2c_smbus_पढ़ो_byte_data(client, reg & 0xff);

	वापस ret;
पूर्ण

अटल s32 synaptics_i2c_reg_set(काष्ठा i2c_client *client, u16 reg, u8 val)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, PAGE_SEL_REG, reg >> 8);
	अगर (ret == 0)
		ret = i2c_smbus_ग_लिखो_byte_data(client, reg & 0xff, val);

	वापस ret;
पूर्ण

अटल s32 synaptics_i2c_word_get(काष्ठा i2c_client *client, u16 reg)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, PAGE_SEL_REG, reg >> 8);
	अगर (ret == 0)
		ret = i2c_smbus_पढ़ो_word_data(client, reg & 0xff);

	वापस ret;
पूर्ण

अटल पूर्णांक synaptics_i2c_config(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret, control;
	u8 पूर्णांक_en;

	/* set Report Rate to Device Highest (>=80) and Sleep to normal */
	ret = synaptics_i2c_reg_set(client, DEV_CONTROL_REG, 0xc1);
	अगर (ret)
		वापस ret;

	/* set Interrupt Disable to Func20 / Enable to Func10) */
	पूर्णांक_en = (polling_req) ? 0 : INT_ENA_ABS_MSK | INT_ENA_REL_MSK;
	ret = synaptics_i2c_reg_set(client, INTERRUPT_EN_REG, पूर्णांक_en);
	अगर (ret)
		वापस ret;

	control = synaptics_i2c_reg_get(client, GENERAL_2D_CONTROL_REG);
	/* No Deceleration */
	control |= no_decel ? 1 << NO_DECELERATION : 0;
	/* Reduced Reporting */
	control |= reduce_report ? 1 << REDUCE_REPORTING : 0;
	/* No Filter */
	control |= no_filter ? 1 << NO_FILTER : 0;
	ret = synaptics_i2c_reg_set(client, GENERAL_2D_CONTROL_REG, control);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक synaptics_i2c_reset_config(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	/* Reset the Touchpad */
	ret = synaptics_i2c_reg_set(client, DEV_COMMAND_REG, RESET_COMMAND);
	अगर (ret) अणु
		dev_err(&client->dev, "Unable to reset device\n");
	पूर्ण अन्यथा अणु
		usleep_range(SOFT_RESET_DELAY_US, SOFT_RESET_DELAY_US + 100);
		ret = synaptics_i2c_config(client);
		अगर (ret)
			dev_err(&client->dev, "Unable to config device\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक synaptics_i2c_check_error(काष्ठा i2c_client *client)
अणु
	पूर्णांक status, ret = 0;

	status = i2c_smbus_पढ़ो_byte_data(client, DEVICE_STATUS_REG) &
		(CONFIGURED_MSK | ERROR_MSK);

	अगर (status != CONFIGURED_MSK)
		ret = synaptics_i2c_reset_config(client);

	वापस ret;
पूर्ण

अटल bool synaptics_i2c_get_input(काष्ठा synaptics_i2c *touch)
अणु
	काष्ठा input_dev *input = touch->input;
	पूर्णांक xy_delta, gesture;
	s32 data;
	s8 x_delta, y_delta;

	/* Deal with spontaneous resets and errors */
	अगर (synaptics_i2c_check_error(touch->client))
		वापस false;

	/* Get Gesture Bit */
	data = synaptics_i2c_reg_get(touch->client, DATA_REG0);
	gesture = (data >> GESTURE) & 0x1;

	/*
	 * Get Relative axes. we have to get them in one shot,
	 * so we get 2 bytes starting from REL_X_REG.
	 */
	xy_delta = synaptics_i2c_word_get(touch->client, REL_X_REG) & 0xffff;

	/* Separate X from Y */
	x_delta = xy_delta & 0xff;
	y_delta = (xy_delta >> REGISTER_LENGTH) & 0xff;

	/* Report the button event */
	input_report_key(input, BTN_LEFT, gesture);

	/* Report the deltas */
	input_report_rel(input, REL_X, x_delta);
	input_report_rel(input, REL_Y, -y_delta);
	input_sync(input);

	वापस xy_delta || gesture;
पूर्ण

अटल irqवापस_t synaptics_i2c_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा synaptics_i2c *touch = dev_id;

	mod_delayed_work(प्रणाली_wq, &touch->dwork, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम synaptics_i2c_check_params(काष्ठा synaptics_i2c *touch)
अणु
	bool reset = false;

	अगर (scan_rate != touch->scan_rate_param)
		set_scan_rate(touch, scan_rate);

	अगर (no_decel != touch->no_decel_param) अणु
		touch->no_decel_param = no_decel;
		reset = true;
	पूर्ण

	अगर (no_filter != touch->no_filter_param) अणु
		touch->no_filter_param = no_filter;
		reset = true;
	पूर्ण

	अगर (reduce_report != touch->reduce_report_param) अणु
		touch->reduce_report_param = reduce_report;
		reset = true;
	पूर्ण

	अगर (reset)
		synaptics_i2c_reset_config(touch->client);
पूर्ण

/* Control the Device polling rate / Work Handler sleep समय */
अटल अचिन्हित दीर्घ synaptics_i2c_adjust_delay(काष्ठा synaptics_i2c *touch,
						bool have_data)
अणु
	अचिन्हित दीर्घ delay, nodata_count_thres;

	अगर (polling_req) अणु
		delay = touch->scan_ms;
		अगर (have_data) अणु
			touch->no_data_count = 0;
		पूर्ण अन्यथा अणु
			nodata_count_thres = NO_DATA_THRES / touch->scan_ms;
			अगर (touch->no_data_count < nodata_count_thres)
				touch->no_data_count++;
			अन्यथा
				delay = NO_DATA_SLEEP_MSECS;
		पूर्ण
		वापस msecs_to_jअगरfies(delay);
	पूर्ण अन्यथा अणु
		delay = msecs_to_jअगरfies(THREAD_IRQ_SLEEP_MSECS);
		वापस round_jअगरfies_relative(delay);
	पूर्ण
पूर्ण

/* Work Handler */
अटल व्योम synaptics_i2c_work_handler(काष्ठा work_काष्ठा *work)
अणु
	bool have_data;
	काष्ठा synaptics_i2c *touch =
			container_of(work, काष्ठा synaptics_i2c, dwork.work);
	अचिन्हित दीर्घ delay;

	synaptics_i2c_check_params(touch);

	have_data = synaptics_i2c_get_input(touch);
	delay = synaptics_i2c_adjust_delay(touch, have_data);

	/*
	 * While पूर्णांकerrupt driven, there is no real need to poll the device.
	 * But touchpads are very sensitive, so there could be errors
	 * related to physical environment and the attention line isn't
	 * necessarily निश्चितed. In such हाल we can lose the touchpad.
	 * We poll the device once in THREAD_IRQ_SLEEP_SECS and
	 * अगर error is detected, we try to reset and reconfigure the touchpad.
	 */
	mod_delayed_work(प्रणाली_wq, &touch->dwork, delay);
पूर्ण

अटल पूर्णांक synaptics_i2c_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा synaptics_i2c *touch = input_get_drvdata(input);
	पूर्णांक ret;

	ret = synaptics_i2c_reset_config(touch->client);
	अगर (ret)
		वापस ret;

	अगर (polling_req)
		mod_delayed_work(प्रणाली_wq, &touch->dwork,
				msecs_to_jअगरfies(NO_DATA_SLEEP_MSECS));

	वापस 0;
पूर्ण

अटल व्योम synaptics_i2c_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा synaptics_i2c *touch = input_get_drvdata(input);

	अगर (!polling_req)
		synaptics_i2c_reg_set(touch->client, INTERRUPT_EN_REG, 0);

	cancel_delayed_work_sync(&touch->dwork);

	/* Save some घातer */
	synaptics_i2c_reg_set(touch->client, DEV_CONTROL_REG, DEEP_SLEEP);
पूर्ण

अटल व्योम synaptics_i2c_set_input_params(काष्ठा synaptics_i2c *touch)
अणु
	काष्ठा input_dev *input = touch->input;

	input->name = touch->client->name;
	input->phys = touch->client->adapter->name;
	input->id.bustype = BUS_I2C;
	input->id.version = synaptics_i2c_word_get(touch->client,
						   INFO_QUERY_REG0);
	input->dev.parent = &touch->client->dev;
	input->खोलो = synaptics_i2c_खोलो;
	input->बंद = synaptics_i2c_बंद;
	input_set_drvdata(input, touch);

	/* Register the device as mouse */
	__set_bit(EV_REL, input->evbit);
	__set_bit(REL_X, input->relbit);
	__set_bit(REL_Y, input->relbit);

	/* Register device's buttons and keys */
	__set_bit(EV_KEY, input->evbit);
	__set_bit(BTN_LEFT, input->keybit);
पूर्ण

अटल काष्ठा synaptics_i2c *synaptics_i2c_touch_create(काष्ठा i2c_client *client)
अणु
	काष्ठा synaptics_i2c *touch;

	touch = kzalloc(माप(काष्ठा synaptics_i2c), GFP_KERNEL);
	अगर (!touch)
		वापस शून्य;

	touch->client = client;
	touch->no_decel_param = no_decel;
	touch->scan_rate_param = scan_rate;
	set_scan_rate(touch, scan_rate);
	INIT_DELAYED_WORK(&touch->dwork, synaptics_i2c_work_handler);

	वापस touch;
पूर्ण

अटल पूर्णांक synaptics_i2c_probe(काष्ठा i2c_client *client,
			       स्थिर काष्ठा i2c_device_id *dev_id)
अणु
	पूर्णांक ret;
	काष्ठा synaptics_i2c *touch;

	touch = synaptics_i2c_touch_create(client);
	अगर (!touch)
		वापस -ENOMEM;

	ret = synaptics_i2c_reset_config(client);
	अगर (ret)
		जाओ err_mem_मुक्त;

	अगर (client->irq < 1)
		polling_req = true;

	touch->input = input_allocate_device();
	अगर (!touch->input) अणु
		ret = -ENOMEM;
		जाओ err_mem_मुक्त;
	पूर्ण

	synaptics_i2c_set_input_params(touch);

	अगर (!polling_req) अणु
		dev_dbg(&touch->client->dev,
			 "Requesting IRQ: %d\n", touch->client->irq);

		ret = request_irq(touch->client->irq, synaptics_i2c_irq,
				  IRQ_TYPE_EDGE_FALLING,
				  DRIVER_NAME, touch);
		अगर (ret) अणु
			dev_warn(&touch->client->dev,
				  "IRQ request failed: %d, "
				  "falling back to polling\n", ret);
			polling_req = true;
			synaptics_i2c_reg_set(touch->client,
					      INTERRUPT_EN_REG, 0);
		पूर्ण
	पूर्ण

	अगर (polling_req)
		dev_dbg(&touch->client->dev,
			 "Using polling at rate: %d times/sec\n", scan_rate);

	/* Register the device in input subप्रणाली */
	ret = input_रेजिस्टर_device(touch->input);
	अगर (ret) अणु
		dev_err(&client->dev,
			 "Input device register failed: %d\n", ret);
		जाओ err_input_मुक्त;
	पूर्ण

	i2c_set_clientdata(client, touch);

	वापस 0;

err_input_मुक्त:
	input_मुक्त_device(touch->input);
err_mem_मुक्त:
	kमुक्त(touch);

	वापस ret;
पूर्ण

अटल पूर्णांक synaptics_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा synaptics_i2c *touch = i2c_get_clientdata(client);

	अगर (!polling_req)
		मुक्त_irq(client->irq, touch);

	input_unरेजिस्टर_device(touch->input);
	kमुक्त(touch);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused synaptics_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा synaptics_i2c *touch = i2c_get_clientdata(client);

	cancel_delayed_work_sync(&touch->dwork);

	/* Save some घातer */
	synaptics_i2c_reg_set(touch->client, DEV_CONTROL_REG, DEEP_SLEEP);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused synaptics_i2c_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा synaptics_i2c *touch = i2c_get_clientdata(client);

	ret = synaptics_i2c_reset_config(client);
	अगर (ret)
		वापस ret;

	mod_delayed_work(प्रणाली_wq, &touch->dwork,
				msecs_to_jअगरfies(NO_DATA_SLEEP_MSECS));

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(synaptics_i2c_pm, synaptics_i2c_suspend,
			 synaptics_i2c_resume);

अटल स्थिर काष्ठा i2c_device_id synaptics_i2c_id_table[] = अणु
	अणु "synaptics_i2c", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, synaptics_i2c_id_table);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id synaptics_i2c_of_match[] = अणु
	अणु .compatible = "synaptics,synaptics_i2c", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, synaptics_i2c_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver synaptics_i2c_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
		.of_match_table = of_match_ptr(synaptics_i2c_of_match),
		.pm	= &synaptics_i2c_pm,
	पूर्ण,

	.probe		= synaptics_i2c_probe,
	.हटाओ		= synaptics_i2c_हटाओ,

	.id_table	= synaptics_i2c_id_table,
पूर्ण;

module_i2c_driver(synaptics_i2c_driver);

MODULE_DESCRIPTION("Synaptics I2C touchpad driver");
MODULE_AUTHOR("Mike Rapoport, Igor Grinberg, Compulab");
MODULE_LICENSE("GPL");

