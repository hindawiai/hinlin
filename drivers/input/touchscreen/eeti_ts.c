<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Touch Screen driver क्रम EETI's I2C connected touch screen panels
 *   Copyright (c) 2009,2018 Daniel Mack <daniel@zonque.org>
 *
 * See EETI's software guide क्रम the protocol specअगरication:
 *   http://home.eeti.com.tw/करोcumentation.hपंचांगl
 *
 * Based on migor_ts.c
 *   Copyright (c) 2008 Magnus Damm
 *   Copyright (c) 2007 Ujjwal Pande <ujjwal@kenati.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/input.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/समयr.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

काष्ठा eeti_ts अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा gpio_desc *attn_gpio;
	काष्ठा touchscreen_properties props;
	काष्ठा mutex mutex;
	bool running;
पूर्ण;

#घोषणा EETI_TS_BITDEPTH	(11)
#घोषणा EETI_MAXVAL		((1 << (EETI_TS_BITDEPTH + 1)) - 1)

#घोषणा REPORT_BIT_PRESSED	BIT(0)
#घोषणा REPORT_BIT_AD0		BIT(1)
#घोषणा REPORT_BIT_AD1		BIT(2)
#घोषणा REPORT_BIT_HAS_PRESSURE	BIT(6)
#घोषणा REPORT_RES_BITS(v)	(((v) >> 1) + EETI_TS_BITDEPTH)

अटल व्योम eeti_ts_report_event(काष्ठा eeti_ts *eeti, u8 *buf)
अणु
	अचिन्हित पूर्णांक res;
	u16 x, y;

	res = REPORT_RES_BITS(buf[0] & (REPORT_BIT_AD0 | REPORT_BIT_AD1));

	x = get_unaligned_be16(&buf[1]);
	y = get_unaligned_be16(&buf[3]);

	/* fix the range to 11 bits */
	x >>= res - EETI_TS_BITDEPTH;
	y >>= res - EETI_TS_BITDEPTH;

	अगर (buf[0] & REPORT_BIT_HAS_PRESSURE)
		input_report_असल(eeti->input, ABS_PRESSURE, buf[5]);

	touchscreen_report_pos(eeti->input, &eeti->props, x, y, false);
	input_report_key(eeti->input, BTN_TOUCH, buf[0] & REPORT_BIT_PRESSED);
	input_sync(eeti->input);
पूर्ण

अटल पूर्णांक eeti_ts_पढ़ो(काष्ठा eeti_ts *eeti)
अणु
	पूर्णांक len, error;
	अक्षर buf[6];

	len = i2c_master_recv(eeti->client, buf, माप(buf));
	अगर (len != माप(buf)) अणु
		error = len < 0 ? len : -EIO;
		dev_err(&eeti->client->dev,
			"failed to read touchscreen data: %d\n",
			error);
		वापस error;
	पूर्ण

	/* Motion packet */
	अगर (buf[0] & 0x80)
		eeti_ts_report_event(eeti, buf);

	वापस 0;
पूर्ण

अटल irqवापस_t eeti_ts_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा eeti_ts *eeti = dev_id;
	पूर्णांक error;

	mutex_lock(&eeti->mutex);

	करो अणु
		/*
		 * If we have attention GPIO, trust it. Otherwise we'll पढ़ो
		 * once and निकास. We assume that in this हाल we are using
		 * level triggered पूर्णांकerrupt and it will get उठाओd again
		 * अगर/when there is more data.
		 */
		अगर (eeti->attn_gpio &&
		    !gpiod_get_value_cansleep(eeti->attn_gpio)) अणु
			अवरोध;
		पूर्ण

		error = eeti_ts_पढ़ो(eeti);
		अगर (error)
			अवरोध;

	पूर्ण जबतक (eeti->running && eeti->attn_gpio);

	mutex_unlock(&eeti->mutex);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम eeti_ts_start(काष्ठा eeti_ts *eeti)
अणु
	mutex_lock(&eeti->mutex);

	eeti->running = true;
	enable_irq(eeti->client->irq);

	/*
	 * Kick the controller in हाल we are using edge पूर्णांकerrupt and
	 * we missed our edge जबतक पूर्णांकerrupt was disabled. We expect
	 * the attention GPIO to be wired in this हाल.
	 */
	अगर (eeti->attn_gpio && gpiod_get_value_cansleep(eeti->attn_gpio))
		eeti_ts_पढ़ो(eeti);

	mutex_unlock(&eeti->mutex);
पूर्ण

अटल व्योम eeti_ts_stop(काष्ठा eeti_ts *eeti)
अणु
	/*
	 * Not locking here, just setting a flag and expect that the
	 * पूर्णांकerrupt thपढ़ो will notice the flag eventually.
	 */
	eeti->running = false;
	wmb();
	disable_irq(eeti->client->irq);
पूर्ण

अटल पूर्णांक eeti_ts_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा eeti_ts *eeti = input_get_drvdata(dev);

	eeti_ts_start(eeti);

	वापस 0;
पूर्ण

अटल व्योम eeti_ts_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा eeti_ts *eeti = input_get_drvdata(dev);

	eeti_ts_stop(eeti);
पूर्ण

अटल पूर्णांक eeti_ts_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *idp)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा eeti_ts *eeti;
	काष्ठा input_dev *input;
	पूर्णांक error;

	/*
	 * In contrast to what's described in the datasheet, there seems
	 * to be no way of probing the presence of that device using I2C
	 * commands. So we need to blindly believe it is there, and रुको
	 * क्रम पूर्णांकerrupts to occur.
	 */

	eeti = devm_kzalloc(dev, माप(*eeti), GFP_KERNEL);
	अगर (!eeti) अणु
		dev_err(dev, "failed to allocate driver data\n");
		वापस -ENOMEM;
	पूर्ण

	mutex_init(&eeti->mutex);

	input = devm_input_allocate_device(dev);
	अगर (!input) अणु
		dev_err(dev, "Failed to allocate input device.\n");
		वापस -ENOMEM;
	पूर्ण

	input_set_capability(input, EV_KEY, BTN_TOUCH);

	input_set_असल_params(input, ABS_X, 0, EETI_MAXVAL, 0, 0);
	input_set_असल_params(input, ABS_Y, 0, EETI_MAXVAL, 0, 0);
	input_set_असल_params(input, ABS_PRESSURE, 0, 0xff, 0, 0);

	touchscreen_parse_properties(input, false, &eeti->props);

	input->name = client->name;
	input->id.bustype = BUS_I2C;
	input->खोलो = eeti_ts_खोलो;
	input->बंद = eeti_ts_बंद;

	eeti->client = client;
	eeti->input = input;

	eeti->attn_gpio = devm_gpiod_get_optional(dev, "attn", GPIOD_IN);
	अगर (IS_ERR(eeti->attn_gpio))
		वापस PTR_ERR(eeti->attn_gpio);

	i2c_set_clientdata(client, eeti);
	input_set_drvdata(input, eeti);

	error = devm_request_thपढ़ोed_irq(dev, client->irq,
					  शून्य, eeti_ts_isr,
					  IRQF_ONESHOT,
					  client->name, eeti);
	अगर (error) अणु
		dev_err(dev, "Unable to request touchscreen IRQ: %d\n",
			error);
		वापस error;
	पूर्ण

	/*
	 * Disable the device क्रम now. It will be enabled once the
	 * input device is खोलोed.
	 */
	eeti_ts_stop(eeti);

	error = input_रेजिस्टर_device(input);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused eeti_ts_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा eeti_ts *eeti = i2c_get_clientdata(client);
	काष्ठा input_dev *input_dev = eeti->input;

	mutex_lock(&input_dev->mutex);

	अगर (input_device_enabled(input_dev))
		eeti_ts_stop(eeti);

	mutex_unlock(&input_dev->mutex);

	अगर (device_may_wakeup(&client->dev))
		enable_irq_wake(client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused eeti_ts_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा eeti_ts *eeti = i2c_get_clientdata(client);
	काष्ठा input_dev *input_dev = eeti->input;

	अगर (device_may_wakeup(&client->dev))
		disable_irq_wake(client->irq);

	mutex_lock(&input_dev->mutex);

	अगर (input_device_enabled(input_dev))
		eeti_ts_start(eeti);

	mutex_unlock(&input_dev->mutex);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(eeti_ts_pm, eeti_ts_suspend, eeti_ts_resume);

अटल स्थिर काष्ठा i2c_device_id eeti_ts_id[] = अणु
	अणु "eeti_ts", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, eeti_ts_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id of_eeti_ts_match[] = अणु
	अणु .compatible = "eeti,exc3000-i2c", पूर्ण,
	अणु पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा i2c_driver eeti_ts_driver = अणु
	.driver = अणु
		.name = "eeti_ts",
		.pm = &eeti_ts_pm,
		.of_match_table = of_match_ptr(of_eeti_ts_match),
	पूर्ण,
	.probe = eeti_ts_probe,
	.id_table = eeti_ts_id,
पूर्ण;

module_i2c_driver(eeti_ts_driver);

MODULE_DESCRIPTION("EETI Touchscreen driver");
MODULE_AUTHOR("Daniel Mack <daniel@zonque.org>");
MODULE_LICENSE("GPL");
