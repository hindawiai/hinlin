<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TSI driver क्रम Dialog DA9052
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/mfd/da9052/reg.h>
#समावेश <linux/mfd/da9052/da9052.h>

#घोषणा TSI_PEN_DOWN_STATUS 0x40

काष्ठा da9052_tsi अणु
	काष्ठा da9052 *da9052;
	काष्ठा input_dev *dev;
	काष्ठा delayed_work ts_pen_work;
	bool stopped;
	bool adc_on;
पूर्ण;

अटल व्योम da9052_ts_adc_toggle(काष्ठा da9052_tsi *tsi, bool on)
अणु
	da9052_reg_update(tsi->da9052, DA9052_TSI_CONT_A_REG, 1 << 0, on);
	tsi->adc_on = on;
पूर्ण

अटल irqवापस_t da9052_ts_pendwn_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9052_tsi *tsi = data;

	अगर (!tsi->stopped) अणु
		/* Mask PEN_DOWN event and unmask TSI_READY event */
		da9052_disable_irq_nosync(tsi->da9052, DA9052_IRQ_PENDOWN);
		da9052_enable_irq(tsi->da9052, DA9052_IRQ_TSIREADY);

		da9052_ts_adc_toggle(tsi, true);

		schedule_delayed_work(&tsi->ts_pen_work, HZ / 50);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम da9052_ts_पढ़ो(काष्ठा da9052_tsi *tsi)
अणु
	काष्ठा input_dev *input = tsi->dev;
	पूर्णांक ret;
	u16 x, y, z;
	u8 v;

	ret = da9052_reg_पढ़ो(tsi->da9052, DA9052_TSI_X_MSB_REG);
	अगर (ret < 0)
		वापस;

	x = (u16) ret;

	ret = da9052_reg_पढ़ो(tsi->da9052, DA9052_TSI_Y_MSB_REG);
	अगर (ret < 0)
		वापस;

	y = (u16) ret;

	ret = da9052_reg_पढ़ो(tsi->da9052, DA9052_TSI_Z_MSB_REG);
	अगर (ret < 0)
		वापस;

	z = (u16) ret;

	ret = da9052_reg_पढ़ो(tsi->da9052, DA9052_TSI_LSB_REG);
	अगर (ret < 0)
		वापस;

	v = (u8) ret;

	x = ((x << 2) & 0x3fc) | (v & 0x3);
	y = ((y << 2) & 0x3fc) | ((v & 0xc) >> 2);
	z = ((z << 2) & 0x3fc) | ((v & 0x30) >> 4);

	input_report_key(input, BTN_TOUCH, 1);
	input_report_असल(input, ABS_X, x);
	input_report_असल(input, ABS_Y, y);
	input_report_असल(input, ABS_PRESSURE, z);
	input_sync(input);
पूर्ण

अटल irqवापस_t da9052_ts_datardy_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9052_tsi *tsi = data;

	da9052_ts_पढ़ो(tsi);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम da9052_ts_pen_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा da9052_tsi *tsi = container_of(work, काष्ठा da9052_tsi,
					      ts_pen_work.work);
	अगर (!tsi->stopped) अणु
		पूर्णांक ret = da9052_reg_पढ़ो(tsi->da9052, DA9052_TSI_LSB_REG);
		अगर (ret < 0 || (ret & TSI_PEN_DOWN_STATUS)) अणु
			/* Pen is still DOWN (or पढ़ो error) */
			schedule_delayed_work(&tsi->ts_pen_work, HZ / 50);
		पूर्ण अन्यथा अणु
			काष्ठा input_dev *input = tsi->dev;

			/* Pen UP */
			da9052_ts_adc_toggle(tsi, false);

			/* Report Pen UP */
			input_report_key(input, BTN_TOUCH, 0);
			input_report_असल(input, ABS_PRESSURE, 0);
			input_sync(input);

			/*
			 * FIXME: Fixes the unhandled irq issue when quick
			 * pen करोwn and pen up events occurs
			 */
			ret = da9052_reg_update(tsi->da9052,
						DA9052_EVENT_B_REG, 0xC0, 0xC0);
			अगर (ret < 0)
				वापस;

			/* Mask TSI_READY event and unmask PEN_DOWN event */
			da9052_disable_irq(tsi->da9052, DA9052_IRQ_TSIREADY);
			da9052_enable_irq(tsi->da9052, DA9052_IRQ_PENDOWN);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक da9052_ts_configure_gpio(काष्ठा da9052 *da9052)
अणु
	पूर्णांक error;

	error = da9052_reg_update(da9052, DA9052_GPIO_2_3_REG, 0x30, 0);
	अगर (error < 0)
		वापस error;

	error = da9052_reg_update(da9052, DA9052_GPIO_4_5_REG, 0x33, 0);
	अगर (error < 0)
		वापस error;

	error = da9052_reg_update(da9052, DA9052_GPIO_6_7_REG, 0x33, 0);
	अगर (error < 0)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक da9052_configure_tsi(काष्ठा da9052_tsi *tsi)
अणु
	पूर्णांक error;

	error = da9052_ts_configure_gpio(tsi->da9052);
	अगर (error)
		वापस error;

	/* Measure TSI sample every 1ms */
	error = da9052_reg_update(tsi->da9052, DA9052_ADC_CONT_REG,
				  1 << 6, 1 << 6);
	अगर (error < 0)
		वापस error;

	/* TSI_DELAY: 3 slots, TSI_SKIP: 0 slots, TSI_MODE: XYZP */
	error = da9052_reg_update(tsi->da9052, DA9052_TSI_CONT_A_REG, 0xFC, 0xC0);
	अगर (error < 0)
		वापस error;

	/* Supply TSIRef through LD09 */
	error = da9052_reg_ग_लिखो(tsi->da9052, DA9052_LDO9_REG, 0x59);
	अगर (error < 0)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक da9052_ts_input_खोलो(काष्ठा input_dev *input_dev)
अणु
	काष्ठा da9052_tsi *tsi = input_get_drvdata(input_dev);

	tsi->stopped = false;
	mb();

	/* Unmask PEN_DOWN event */
	da9052_enable_irq(tsi->da9052, DA9052_IRQ_PENDOWN);

	/* Enable Pen Detect Circuit */
	वापस da9052_reg_update(tsi->da9052, DA9052_TSI_CONT_A_REG,
				 1 << 1, 1 << 1);
पूर्ण

अटल व्योम da9052_ts_input_बंद(काष्ठा input_dev *input_dev)
अणु
	काष्ठा da9052_tsi *tsi = input_get_drvdata(input_dev);

	tsi->stopped = true;
	mb();
	da9052_disable_irq(tsi->da9052, DA9052_IRQ_PENDOWN);
	cancel_delayed_work_sync(&tsi->ts_pen_work);

	अगर (tsi->adc_on) अणु
		da9052_disable_irq(tsi->da9052, DA9052_IRQ_TSIREADY);
		da9052_ts_adc_toggle(tsi, false);

		/*
		 * If ADC was on that means that pendwn IRQ was disabled
		 * twice and we need to enable it to keep enable/disable
		 * counter balanced. IRQ is still off though.
		 */
		da9052_enable_irq(tsi->da9052, DA9052_IRQ_PENDOWN);
	पूर्ण

	/* Disable Pen Detect Circuit */
	da9052_reg_update(tsi->da9052, DA9052_TSI_CONT_A_REG, 1 << 1, 0);
पूर्ण

अटल पूर्णांक da9052_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9052 *da9052;
	काष्ठा da9052_tsi *tsi;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	da9052 = dev_get_drvdata(pdev->dev.parent);
	अगर (!da9052)
		वापस -EINVAL;

	tsi = kzalloc(माप(काष्ठा da9052_tsi), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!tsi || !input_dev) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	tsi->da9052 = da9052;
	tsi->dev = input_dev;
	tsi->stopped = true;
	INIT_DELAYED_WORK(&tsi->ts_pen_work, da9052_ts_pen_work);

	input_dev->id.version = 0x0101;
	input_dev->id.venकरोr = 0x15B6;
	input_dev->id.product = 0x9052;
	input_dev->name = "Dialog DA9052 TouchScreen Driver";
	input_dev->dev.parent = &pdev->dev;
	input_dev->खोलो = da9052_ts_input_खोलो;
	input_dev->बंद = da9052_ts_input_बंद;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);

	input_set_असल_params(input_dev, ABS_X, 0, 1023, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, 1023, 0, 0);
	input_set_असल_params(input_dev, ABS_PRESSURE, 0, 1023, 0, 0);

	input_set_drvdata(input_dev, tsi);

	/* Disable Pen Detect Circuit */
	da9052_reg_update(tsi->da9052, DA9052_TSI_CONT_A_REG, 1 << 1, 0);

	/* Disable ADC */
	da9052_ts_adc_toggle(tsi, false);

	error = da9052_request_irq(tsi->da9052, DA9052_IRQ_PENDOWN,
				"pendown-irq", da9052_ts_pendwn_irq, tsi);
	अगर (error) अणु
		dev_err(tsi->da9052->dev,
			"Failed to register PENDWN IRQ: %d\n", error);
		जाओ err_मुक्त_mem;
	पूर्ण

	error = da9052_request_irq(tsi->da9052, DA9052_IRQ_TSIREADY,
				"tsiready-irq", da9052_ts_datardy_irq, tsi);
	अगर (error) अणु
		dev_err(tsi->da9052->dev,
			"Failed to register TSIRDY IRQ :%d\n", error);
		जाओ err_मुक्त_pendwn_irq;
	पूर्ण

	/* Mask PEN_DOWN and TSI_READY events */
	da9052_disable_irq(tsi->da9052, DA9052_IRQ_PENDOWN);
	da9052_disable_irq(tsi->da9052, DA9052_IRQ_TSIREADY);

	error = da9052_configure_tsi(tsi);
	अगर (error)
		जाओ err_मुक्त_datardy_irq;

	error = input_रेजिस्टर_device(tsi->dev);
	अगर (error)
		जाओ err_मुक्त_datardy_irq;

	platक्रमm_set_drvdata(pdev, tsi);

	वापस 0;

err_मुक्त_datardy_irq:
	da9052_मुक्त_irq(tsi->da9052, DA9052_IRQ_TSIREADY, tsi);
err_मुक्त_pendwn_irq:
	da9052_मुक्त_irq(tsi->da9052, DA9052_IRQ_PENDOWN, tsi);
err_मुक्त_mem:
	kमुक्त(tsi);
	input_मुक्त_device(input_dev);

	वापस error;
पूर्ण

अटल पूर्णांक  da9052_ts_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9052_tsi *tsi = platक्रमm_get_drvdata(pdev);

	da9052_reg_ग_लिखो(tsi->da9052, DA9052_LDO9_REG, 0x19);

	da9052_मुक्त_irq(tsi->da9052, DA9052_IRQ_TSIREADY, tsi);
	da9052_मुक्त_irq(tsi->da9052, DA9052_IRQ_PENDOWN, tsi);

	input_unरेजिस्टर_device(tsi->dev);
	kमुक्त(tsi);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9052_tsi_driver = अणु
	.probe	= da9052_ts_probe,
	.हटाओ	= da9052_ts_हटाओ,
	.driver	= अणु
		.name	= "da9052-tsi",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(da9052_tsi_driver);

MODULE_DESCRIPTION("Touchscreen driver for Dialog Semiconductor DA9052");
MODULE_AUTHOR("Anthony Olech <Anthony.Olech@diasemi.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9052-tsi");
