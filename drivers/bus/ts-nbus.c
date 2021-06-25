<शैली गुरु>
/*
 * NBUS driver क्रम TS-4600 based boards
 *
 * Copyright (c) 2016 - Savoir-faire Linux
 * Author: Sebastien Bourdelin <sebastien.bourdelin@savoirfairelinux.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * This driver implements a GPIOs bit-banged bus, called the NBUS by Technologic
 * Systems. It is used to communicate with the peripherals in the FPGA on the
 * TS-4600 SoM.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/ts-nbus.h>

#घोषणा TS_NBUS_सूचीECTION_IN  0
#घोषणा TS_NBUS_सूचीECTION_OUT 1
#घोषणा TS_NBUS_WRITE_ADR 0
#घोषणा TS_NBUS_WRITE_VAL 1

काष्ठा ts_nbus अणु
	काष्ठा pwm_device *pwm;
	काष्ठा gpio_descs *data;
	काष्ठा gpio_desc *csn;
	काष्ठा gpio_desc *txrx;
	काष्ठा gpio_desc *strobe;
	काष्ठा gpio_desc *ale;
	काष्ठा gpio_desc *rdy;
	काष्ठा mutex lock;
पूर्ण;

/*
 * request all gpios required by the bus.
 */
अटल पूर्णांक ts_nbus_init_pdata(काष्ठा platक्रमm_device *pdev, काष्ठा ts_nbus
		*ts_nbus)
अणु
	ts_nbus->data = devm_gpiod_get_array(&pdev->dev, "ts,data",
			GPIOD_OUT_HIGH);
	अगर (IS_ERR(ts_nbus->data)) अणु
		dev_err(&pdev->dev, "failed to retrieve ts,data-gpio from dts\n");
		वापस PTR_ERR(ts_nbus->data);
	पूर्ण

	ts_nbus->csn = devm_gpiod_get(&pdev->dev, "ts,csn", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ts_nbus->csn)) अणु
		dev_err(&pdev->dev, "failed to retrieve ts,csn-gpio from dts\n");
		वापस PTR_ERR(ts_nbus->csn);
	पूर्ण

	ts_nbus->txrx = devm_gpiod_get(&pdev->dev, "ts,txrx", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ts_nbus->txrx)) अणु
		dev_err(&pdev->dev, "failed to retrieve ts,txrx-gpio from dts\n");
		वापस PTR_ERR(ts_nbus->txrx);
	पूर्ण

	ts_nbus->strobe = devm_gpiod_get(&pdev->dev, "ts,strobe", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ts_nbus->strobe)) अणु
		dev_err(&pdev->dev, "failed to retrieve ts,strobe-gpio from dts\n");
		वापस PTR_ERR(ts_nbus->strobe);
	पूर्ण

	ts_nbus->ale = devm_gpiod_get(&pdev->dev, "ts,ale", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ts_nbus->ale)) अणु
		dev_err(&pdev->dev, "failed to retrieve ts,ale-gpio from dts\n");
		वापस PTR_ERR(ts_nbus->ale);
	पूर्ण

	ts_nbus->rdy = devm_gpiod_get(&pdev->dev, "ts,rdy", GPIOD_IN);
	अगर (IS_ERR(ts_nbus->rdy)) अणु
		dev_err(&pdev->dev, "failed to retrieve ts,rdy-gpio from dts\n");
		वापस PTR_ERR(ts_nbus->rdy);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * the data gpios are used क्रम पढ़ोing and writing values, their directions
 * should be adjusted accordingly.
 */
अटल व्योम ts_nbus_set_direction(काष्ठा ts_nbus *ts_nbus, पूर्णांक direction)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (direction == TS_NBUS_सूचीECTION_IN)
			gpiod_direction_input(ts_nbus->data->desc[i]);
		अन्यथा
			/* when used as output the शेष state of the data
			 * lines are set to high */
			gpiod_direction_output(ts_nbus->data->desc[i], 1);
	पूर्ण
पूर्ण

/*
 * reset the bus in its initial state.
 * The data, csn, strobe and ale lines must be zero'ed to let the FPGA knows a
 * new transaction can be process.
 */
अटल व्योम ts_nbus_reset_bus(काष्ठा ts_nbus *ts_nbus)
अणु
	DECLARE_BITMAP(values, 8);

	values[0] = 0;

	gpiod_set_array_value_cansleep(8, ts_nbus->data->desc,
				       ts_nbus->data->info, values);
	gpiod_set_value_cansleep(ts_nbus->csn, 0);
	gpiod_set_value_cansleep(ts_nbus->strobe, 0);
	gpiod_set_value_cansleep(ts_nbus->ale, 0);
पूर्ण

/*
 * let the FPGA knows it can process.
 */
अटल व्योम ts_nbus_start_transaction(काष्ठा ts_nbus *ts_nbus)
अणु
	gpiod_set_value_cansleep(ts_nbus->strobe, 1);
पूर्ण

/*
 * पढ़ो a byte value from the data gpios.
 * वापस 0 on success or negative त्रुटि_सं on failure.
 */
अटल पूर्णांक ts_nbus_पढ़ो_byte(काष्ठा ts_nbus *ts_nbus, u8 *val)
अणु
	काष्ठा gpio_descs *gpios = ts_nbus->data;
	पूर्णांक ret, i;

	*val = 0;
	क्रम (i = 0; i < 8; i++) अणु
		ret = gpiod_get_value_cansleep(gpios->desc[i]);
		अगर (ret < 0)
			वापस ret;
		अगर (ret)
			*val |= BIT(i);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * set the data gpios accordingly to the byte value.
 */
अटल व्योम ts_nbus_ग_लिखो_byte(काष्ठा ts_nbus *ts_nbus, u8 byte)
अणु
	काष्ठा gpio_descs *gpios = ts_nbus->data;
	DECLARE_BITMAP(values, 8);

	values[0] = byte;

	gpiod_set_array_value_cansleep(8, gpios->desc, gpios->info, values);
पूर्ण

/*
 * पढ़ोing the bus consists of resetting the bus, then notअगरying the FPGA to
 * send the data in the data gpios and वापस the पढ़ो value.
 * वापस 0 on success or negative त्रुटि_सं on failure.
 */
अटल पूर्णांक ts_nbus_पढ़ो_bus(काष्ठा ts_nbus *ts_nbus, u8 *val)
अणु
	ts_nbus_reset_bus(ts_nbus);
	ts_nbus_start_transaction(ts_nbus);

	वापस ts_nbus_पढ़ो_byte(ts_nbus, val);
पूर्ण

/*
 * writing to the bus consists of resetting the bus, then define the type of
 * command (address/value), ग_लिखो the data and notअगरy the FPGA to retrieve the
 * value in the data gpios.
 */
अटल व्योम ts_nbus_ग_लिखो_bus(काष्ठा ts_nbus *ts_nbus, पूर्णांक cmd, u8 val)
अणु
	ts_nbus_reset_bus(ts_nbus);

	अगर (cmd == TS_NBUS_WRITE_ADR)
		gpiod_set_value_cansleep(ts_nbus->ale, 1);

	ts_nbus_ग_लिखो_byte(ts_nbus, val);
	ts_nbus_start_transaction(ts_nbus);
पूर्ण

/*
 * पढ़ो the value in the FPGA रेजिस्टर at the given address.
 * वापस 0 on success or negative त्रुटि_सं on failure.
 */
पूर्णांक ts_nbus_पढ़ो(काष्ठा ts_nbus *ts_nbus, u8 adr, u16 *val)
अणु
	पूर्णांक ret, i;
	u8 byte;

	/* bus access must be atomic */
	mutex_lock(&ts_nbus->lock);

	/* set the bus in पढ़ो mode */
	gpiod_set_value_cansleep(ts_nbus->txrx, 0);

	/* ग_लिखो address */
	ts_nbus_ग_लिखो_bus(ts_nbus, TS_NBUS_WRITE_ADR, adr);

	/* set the data gpios direction as input beक्रमe पढ़ोing */
	ts_nbus_set_direction(ts_nbus, TS_NBUS_सूचीECTION_IN);

	/* पढ़ोing value MSB first */
	करो अणु
		*val = 0;
		byte = 0;
		क्रम (i = 1; i >= 0; i--) अणु
			/* पढ़ो a byte from the bus, leave on error */
			ret = ts_nbus_पढ़ो_bus(ts_nbus, &byte);
			अगर (ret < 0)
				जाओ err;

			/* append the byte पढ़ो to the final value */
			*val |= byte << (i * 8);
		पूर्ण
		gpiod_set_value_cansleep(ts_nbus->csn, 1);
		ret = gpiod_get_value_cansleep(ts_nbus->rdy);
	पूर्ण जबतक (ret);

err:
	/* restore the data gpios direction as output after पढ़ोing */
	ts_nbus_set_direction(ts_nbus, TS_NBUS_सूचीECTION_OUT);

	mutex_unlock(&ts_nbus->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ts_nbus_पढ़ो);

/*
 * ग_लिखो the desired value in the FPGA रेजिस्टर at the given address.
 */
पूर्णांक ts_nbus_ग_लिखो(काष्ठा ts_nbus *ts_nbus, u8 adr, u16 val)
अणु
	पूर्णांक i;

	/* bus access must be atomic */
	mutex_lock(&ts_nbus->lock);

	/* set the bus in ग_लिखो mode */
	gpiod_set_value_cansleep(ts_nbus->txrx, 1);

	/* ग_लिखो address */
	ts_nbus_ग_लिखो_bus(ts_nbus, TS_NBUS_WRITE_ADR, adr);

	/* writing value MSB first */
	क्रम (i = 1; i >= 0; i--)
		ts_nbus_ग_लिखो_bus(ts_nbus, TS_NBUS_WRITE_VAL, (u8)(val >> (i * 8)));

	/* रुको क्रम completion */
	gpiod_set_value_cansleep(ts_nbus->csn, 1);
	जबतक (gpiod_get_value_cansleep(ts_nbus->rdy) != 0) अणु
		gpiod_set_value_cansleep(ts_nbus->csn, 0);
		gpiod_set_value_cansleep(ts_nbus->csn, 1);
	पूर्ण

	mutex_unlock(&ts_nbus->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ts_nbus_ग_लिखो);

अटल पूर्णांक ts_nbus_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pwm_device *pwm;
	काष्ठा pwm_args pargs;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ts_nbus *ts_nbus;
	पूर्णांक ret;

	ts_nbus = devm_kzalloc(dev, माप(*ts_nbus), GFP_KERNEL);
	अगर (!ts_nbus)
		वापस -ENOMEM;

	mutex_init(&ts_nbus->lock);

	ret = ts_nbus_init_pdata(pdev, ts_nbus);
	अगर (ret < 0)
		वापस ret;

	pwm = devm_pwm_get(dev, शून्य);
	अगर (IS_ERR(pwm)) अणु
		ret = PTR_ERR(pwm);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "unable to request PWM\n");
		वापस ret;
	पूर्ण

	pwm_get_args(pwm, &pargs);
	अगर (!pargs.period) अणु
		dev_err(&pdev->dev, "invalid PWM period\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * FIXME: pwm_apply_args() should be हटाओd when चयनing to
	 * the atomic PWM API.
	 */
	pwm_apply_args(pwm);
	ret = pwm_config(pwm, pargs.period, pargs.period);
	अगर (ret < 0)
		वापस ret;

	/*
	 * we can now start the FPGA and populate the peripherals.
	 */
	pwm_enable(pwm);
	ts_nbus->pwm = pwm;

	/*
	 * let the child nodes retrieve this instance of the ts-nbus.
	 */
	dev_set_drvdata(dev, ts_nbus);

	ret = of_platक्रमm_populate(dev->of_node, शून्य, शून्य, dev);
	अगर (ret < 0)
		वापस ret;

	dev_info(dev, "initialized\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ts_nbus_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ts_nbus *ts_nbus = dev_get_drvdata(&pdev->dev);

	/* shutकरोwn the FPGA */
	mutex_lock(&ts_nbus->lock);
	pwm_disable(ts_nbus->pwm);
	mutex_unlock(&ts_nbus->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ts_nbus_of_match[] = अणु
	अणु .compatible = "technologic,ts-nbus", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ts_nbus_of_match);

अटल काष्ठा platक्रमm_driver ts_nbus_driver = अणु
	.probe		= ts_nbus_probe,
	.हटाओ		= ts_nbus_हटाओ,
	.driver		= अणु
		.name	= "ts_nbus",
		.of_match_table = ts_nbus_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ts_nbus_driver);

MODULE_ALIAS("platform:ts_nbus");
MODULE_AUTHOR("Sebastien Bourdelin <sebastien.bourdelin@savoirfairelinux.com>");
MODULE_DESCRIPTION("Technologic Systems NBUS");
MODULE_LICENSE("GPL v2");
