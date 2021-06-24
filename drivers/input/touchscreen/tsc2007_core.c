<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/input/touchscreen/tsc2007.c
 *
 * Copyright (c) 2008 MtekVision Co., Ltd.
 *	Kwangwoo Lee <kwlee@mtekvision.com>
 *
 * Using code from:
 *  - ads7846.c
 *	Copyright (c) 2005 David Brownell
 *	Copyright (c) 2006 Nokia Corporation
 *  - corgi_ts.c
 *	Copyright (C) 2004-2005 Riअक्षरd Purdie
 *  - omap_ts.[hc], ads7846.h, ts_osk.c
 *	Copyright (C) 2002 MontaVista Software
 *	Copyright (C) 2004 Texas Instruments
 *	Copyright (C) 2005 Dirk Behme
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/property.h>
#समावेश <linux/platक्रमm_data/tsc2007.h>
#समावेश "tsc2007.h"

पूर्णांक tsc2007_xfer(काष्ठा tsc2007 *tsc, u8 cmd)
अणु
	s32 data;
	u16 val;

	data = i2c_smbus_पढ़ो_word_data(tsc->client, cmd);
	अगर (data < 0) अणु
		dev_err(&tsc->client->dev, "i2c io error: %d\n", data);
		वापस data;
	पूर्ण

	/* The protocol and raw data क्रमmat from i2c पूर्णांकerface:
	 * S Addr Wr [A] Comm [A] S Addr Rd [A] [DataLow] A [DataHigh] NA P
	 * Where DataLow has [D11-D4], DataHigh has [D3-D0 << 4 | Dummy 4bit].
	 */
	val = swab16(data) >> 4;

	dev_dbg(&tsc->client->dev, "data: 0x%x, val: 0x%x\n", data, val);

	वापस val;
पूर्ण

अटल व्योम tsc2007_पढ़ो_values(काष्ठा tsc2007 *tsc, काष्ठा ts_event *tc)
अणु
	/* y- still on; turn on only y+ (and ADC) */
	tc->y = tsc2007_xfer(tsc, READ_Y);

	/* turn y- off, x+ on, then leave in lowघातer */
	tc->x = tsc2007_xfer(tsc, READ_X);

	/* turn y+ off, x- on; we'll use क्रमmula #1 */
	tc->z1 = tsc2007_xfer(tsc, READ_Z1);
	tc->z2 = tsc2007_xfer(tsc, READ_Z2);

	/* Prepare क्रम next touch पढ़ोing - घातer करोwn ADC, enable PENIRQ */
	tsc2007_xfer(tsc, PWRDOWN);
पूर्ण

u32 tsc2007_calculate_resistance(काष्ठा tsc2007 *tsc, काष्ठा ts_event *tc)
अणु
	u32 rt = 0;

	/* range filtering */
	अगर (tc->x == MAX_12BIT)
		tc->x = 0;

	अगर (likely(tc->x && tc->z1)) अणु
		/* compute touch resistance using equation #1 */
		rt = tc->z2 - tc->z1;
		rt *= tc->x;
		rt *= tsc->x_plate_ohms;
		rt /= tc->z1;
		rt = (rt + 2047) >> 12;
	पूर्ण

	वापस rt;
पूर्ण

bool tsc2007_is_pen_करोwn(काष्ठा tsc2007 *ts)
अणु
	/*
	 * NOTE: We can't rely on the pressure to determine the pen करोwn
	 * state, even though this controller has a pressure sensor.
	 * The pressure value can fluctuate क्रम quite a जबतक after
	 * lअगरting the pen and in some हालs may not even settle at the
	 * expected value.
	 *
	 * The only safe way to check क्रम the pen up condition is in the
	 * work function by पढ़ोing the pen संकेत state (it's a GPIO
	 * and IRQ). Unक्रमtunately such callback is not always available,
	 * in that हाल we assume that the pen is करोwn and expect caller
	 * to fall back on the pressure पढ़ोing.
	 */

	अगर (!ts->get_penकरोwn_state)
		वापस true;

	वापस ts->get_penकरोwn_state(&ts->client->dev);
पूर्ण

अटल irqवापस_t tsc2007_soft_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा tsc2007 *ts = handle;
	काष्ठा input_dev *input = ts->input;
	काष्ठा ts_event tc;
	u32 rt;

	जबतक (!ts->stopped && tsc2007_is_pen_करोwn(ts)) अणु

		/* pen is करोwn, जारी with the measurement */

		mutex_lock(&ts->mlock);
		tsc2007_पढ़ो_values(ts, &tc);
		mutex_unlock(&ts->mlock);

		rt = tsc2007_calculate_resistance(ts, &tc);

		अगर (!rt && !ts->get_penकरोwn_state) अणु
			/*
			 * If pressure reported is 0 and we करोn't have
			 * callback to check penकरोwn state, we have to
			 * assume that pen was lअगरted up.
			 */
			अवरोध;
		पूर्ण

		अगर (rt <= ts->max_rt) अणु
			dev_dbg(&ts->client->dev,
				"DOWN point(%4d,%4d), resistance (%4u)\n",
				tc.x, tc.y, rt);

			rt = ts->max_rt - rt;

			input_report_key(input, BTN_TOUCH, 1);
			input_report_असल(input, ABS_X, tc.x);
			input_report_असल(input, ABS_Y, tc.y);
			input_report_असल(input, ABS_PRESSURE, rt);

			input_sync(input);

		पूर्ण अन्यथा अणु
			/*
			 * Sample found inconsistent by debouncing or pressure is
			 * beyond the maximum. Don't report it to user space,
			 * repeat at least once more the measurement.
			 */
			dev_dbg(&ts->client->dev, "ignored pressure %d\n", rt);
		पूर्ण

		रुको_event_समयout(ts->रुको, ts->stopped, ts->poll_period);
	पूर्ण

	dev_dbg(&ts->client->dev, "UP\n");

	input_report_key(input, BTN_TOUCH, 0);
	input_report_असल(input, ABS_PRESSURE, 0);
	input_sync(input);

	अगर (ts->clear_penirq)
		ts->clear_penirq();

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t tsc2007_hard_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा tsc2007 *ts = handle;

	अगर (tsc2007_is_pen_करोwn(ts))
		वापस IRQ_WAKE_THREAD;

	अगर (ts->clear_penirq)
		ts->clear_penirq();

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tsc2007_stop(काष्ठा tsc2007 *ts)
अणु
	ts->stopped = true;
	mb();
	wake_up(&ts->रुको);

	disable_irq(ts->irq);
पूर्ण

अटल पूर्णांक tsc2007_खोलो(काष्ठा input_dev *input_dev)
अणु
	काष्ठा tsc2007 *ts = input_get_drvdata(input_dev);
	पूर्णांक err;

	ts->stopped = false;
	mb();

	enable_irq(ts->irq);

	/* Prepare क्रम touch पढ़ोings - घातer करोwn ADC and enable PENIRQ */
	err = tsc2007_xfer(ts, PWRDOWN);
	अगर (err < 0) अणु
		tsc2007_stop(ts);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tsc2007_बंद(काष्ठा input_dev *input_dev)
अणु
	काष्ठा tsc2007 *ts = input_get_drvdata(input_dev);

	tsc2007_stop(ts);
पूर्ण

अटल पूर्णांक tsc2007_get_penकरोwn_state_gpio(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा tsc2007 *ts = i2c_get_clientdata(client);

	वापस gpiod_get_value(ts->gpiod);
पूर्ण

अटल पूर्णांक tsc2007_probe_properties(काष्ठा device *dev, काष्ठा tsc2007 *ts)
अणु
	u32 val32;
	u64 val64;

	अगर (!device_property_पढ़ो_u32(dev, "ti,max-rt", &val32))
		ts->max_rt = val32;
	अन्यथा
		ts->max_rt = MAX_12BIT;

	अगर (!device_property_पढ़ो_u32(dev, "ti,fuzzx", &val32))
		ts->fuzzx = val32;

	अगर (!device_property_पढ़ो_u32(dev, "ti,fuzzy", &val32))
		ts->fuzzy = val32;

	अगर (!device_property_पढ़ो_u32(dev, "ti,fuzzz", &val32))
		ts->fuzzz = val32;

	अगर (!device_property_पढ़ो_u64(dev, "ti,poll-period", &val64))
		ts->poll_period = msecs_to_jअगरfies(val64);
	अन्यथा
		ts->poll_period = msecs_to_jअगरfies(1);

	अगर (!device_property_पढ़ो_u32(dev, "ti,x-plate-ohms", &val32)) अणु
		ts->x_plate_ohms = val32;
	पूर्ण अन्यथा अणु
		dev_err(dev, "Missing ti,x-plate-ohms device property\n");
		वापस -EINVAL;
	पूर्ण

	ts->gpiod = devm_gpiod_get_optional(dev, शून्य, GPIOD_IN);
	अगर (IS_ERR(ts->gpiod))
		वापस PTR_ERR(ts->gpiod);

	अगर (ts->gpiod)
		ts->get_penकरोwn_state = tsc2007_get_penकरोwn_state_gpio;
	अन्यथा
		dev_warn(dev, "Pen down GPIO is not specified in properties\n");

	वापस 0;
पूर्ण

अटल पूर्णांक tsc2007_probe_pdev(काष्ठा device *dev, काष्ठा tsc2007 *ts,
			      स्थिर काष्ठा tsc2007_platक्रमm_data *pdata,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	ts->model             = pdata->model;
	ts->x_plate_ohms      = pdata->x_plate_ohms;
	ts->max_rt            = pdata->max_rt ? : MAX_12BIT;
	ts->poll_period       = msecs_to_jअगरfies(pdata->poll_period ? : 1);
	ts->get_penकरोwn_state = pdata->get_penकरोwn_state;
	ts->clear_penirq      = pdata->clear_penirq;
	ts->fuzzx             = pdata->fuzzx;
	ts->fuzzy             = pdata->fuzzy;
	ts->fuzzz             = pdata->fuzzz;

	अगर (pdata->x_plate_ohms == 0) अणु
		dev_err(dev, "x_plate_ohms is not set up in platform data\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tsc2007_call_निकास_platक्रमm_hw(व्योम *data)
अणु
	काष्ठा device *dev = data;
	स्थिर काष्ठा tsc2007_platक्रमm_data *pdata = dev_get_platdata(dev);

	pdata->निकास_platक्रमm_hw();
पूर्ण

अटल पूर्णांक tsc2007_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा tsc2007_platक्रमm_data *pdata =
		dev_get_platdata(&client->dev);
	काष्ठा tsc2007 *ts;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_WORD_DATA))
		वापस -EIO;

	ts = devm_kzalloc(&client->dev, माप(काष्ठा tsc2007), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	अगर (pdata)
		err = tsc2007_probe_pdev(&client->dev, ts, pdata, id);
	अन्यथा
		err = tsc2007_probe_properties(&client->dev, ts);
	अगर (err)
		वापस err;

	input_dev = devm_input_allocate_device(&client->dev);
	अगर (!input_dev)
		वापस -ENOMEM;

	i2c_set_clientdata(client, ts);

	ts->client = client;
	ts->irq = client->irq;
	ts->input = input_dev;

	init_रुकोqueue_head(&ts->रुको);
	mutex_init(&ts->mlock);

	snम_लिखो(ts->phys, माप(ts->phys),
		 "%s/input0", dev_name(&client->dev));

	input_dev->name = "TSC2007 Touchscreen";
	input_dev->phys = ts->phys;
	input_dev->id.bustype = BUS_I2C;

	input_dev->खोलो = tsc2007_खोलो;
	input_dev->बंद = tsc2007_बंद;

	input_set_drvdata(input_dev, ts);

	input_set_capability(input_dev, EV_KEY, BTN_TOUCH);

	input_set_असल_params(input_dev, ABS_X, 0, MAX_12BIT, ts->fuzzx, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, MAX_12BIT, ts->fuzzy, 0);
	input_set_असल_params(input_dev, ABS_PRESSURE, 0, MAX_12BIT,
			     ts->fuzzz, 0);

	अगर (pdata) अणु
		अगर (pdata->निकास_platक्रमm_hw) अणु
			err = devm_add_action(&client->dev,
					      tsc2007_call_निकास_platक्रमm_hw,
					      &client->dev);
			अगर (err) अणु
				dev_err(&client->dev,
					"Failed to register exit_platform_hw action, %d\n",
					err);
				वापस err;
			पूर्ण
		पूर्ण

		अगर (pdata->init_platक्रमm_hw)
			pdata->init_platक्रमm_hw();
	पूर्ण

	err = devm_request_thपढ़ोed_irq(&client->dev, ts->irq,
					tsc2007_hard_irq, tsc2007_soft_irq,
					IRQF_ONESHOT,
					client->dev.driver->name, ts);
	अगर (err) अणु
		dev_err(&client->dev, "Failed to request irq %d: %d\n",
			ts->irq, err);
		वापस err;
	पूर्ण

	tsc2007_stop(ts);

	/* घातer करोwn the chip (TSC2007_SETUP करोes not ACK on I2C) */
	err = tsc2007_xfer(ts, PWRDOWN);
	अगर (err < 0) अणु
		dev_err(&client->dev,
			"Failed to setup chip: %d\n", err);
		वापस err;	/* chip करोes not respond */
	पूर्ण

	err = input_रेजिस्टर_device(input_dev);
	अगर (err) अणु
		dev_err(&client->dev,
			"Failed to register input device: %d\n", err);
		वापस err;
	पूर्ण

	err =  tsc2007_iio_configure(ts);
	अगर (err) अणु
		dev_err(&client->dev,
			"Failed to register with IIO: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tsc2007_idtable[] = अणु
	अणु "tsc2007", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, tsc2007_idtable);

अटल स्थिर काष्ठा of_device_id tsc2007_of_match[] = अणु
	अणु .compatible = "ti,tsc2007" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tsc2007_of_match);

अटल काष्ठा i2c_driver tsc2007_driver = अणु
	.driver = अणु
		.name	= "tsc2007",
		.of_match_table = tsc2007_of_match,
	पूर्ण,
	.id_table	= tsc2007_idtable,
	.probe		= tsc2007_probe,
पूर्ण;

module_i2c_driver(tsc2007_driver);

MODULE_AUTHOR("Kwangwoo Lee <kwlee@mtekvision.com>");
MODULE_DESCRIPTION("TSC2007 TouchScreen Driver");
MODULE_LICENSE("GPL");
