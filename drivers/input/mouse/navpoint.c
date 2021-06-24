<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Synaptics NavPoपूर्णांक (PXA27x SSP/SPI) driver.
 *
 * Copyright (C) 2012 Paul Parsons <lost.distance@yahoo.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/input.h>
#समावेश <linux/input/navpoपूर्णांक.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pxa2xx_ssp.h>
#समावेश <linux/slab.h>

/*
 * Synaptics Modular Embedded Protocol: Module Packet Format.
 * Module header byte 2:0 = Length (# bytes that follow)
 * Module header byte 4:3 = Control
 * Module header byte 7:5 = Module Address
 */
#घोषणा HEADER_LENGTH(byte)	((byte) & 0x07)
#घोषणा HEADER_CONTROL(byte)	(((byte) >> 3) & 0x03)
#घोषणा HEADER_ADDRESS(byte)	((byte) >> 5)

काष्ठा navpoपूर्णांक अणु
	काष्ठा ssp_device	*ssp;
	काष्ठा input_dev	*input;
	काष्ठा device		*dev;
	पूर्णांक			gpio;
	पूर्णांक			index;
	u8			data[1 + HEADER_LENGTH(0xff)];
पूर्ण;

/*
 * Initialization values क्रम SSCR0_x, SSCR1_x, SSSR_x.
 */
अटल स्थिर u32 sscr0 = 0
	| SSCR0_TUM		/* TIM = 1; No TUR पूर्णांकerrupts */
	| SSCR0_RIM		/* RIM = 1; No ROR पूर्णांकerrupts */
	| SSCR0_SSE		/* SSE = 1; SSP enabled */
	| SSCR0_Motorola	/* FRF = 0; Motorola SPI */
	| SSCR0_DataSize(16)	/* DSS = 15; Data size = 16-bit */
	;
अटल स्थिर u32 sscr1 = 0
	| SSCR1_SCFR		/* SCFR = 1; SSPSCLK only during transfers */
	| SSCR1_SCLKसूची		/* SCLKसूची = 1; Slave mode */
	| SSCR1_SFRMसूची		/* SFRMसूची = 1; Slave mode */
	| SSCR1_RWOT		/* RWOT = 1; Receive without transmit mode */
	| SSCR1_RxTresh(1)	/* RFT = 0; Receive FIFO threshold = 1 */
	| SSCR1_SPH		/* SPH = 1; SSPSCLK inactive 0.5 + 1 cycles */
	| SSCR1_RIE		/* RIE = 1; Receive FIFO पूर्णांकerrupt enabled */
	;
अटल स्थिर u32 sssr = 0
	| SSSR_BCE		/* BCE = 1; Clear BCE */
	| SSSR_TUR		/* TUR = 1; Clear TUR */
	| SSSR_EOC		/* EOC = 1; Clear EOC */
	| SSSR_TINT		/* TINT = 1; Clear TINT */
	| SSSR_PINT		/* PINT = 1; Clear PINT */
	| SSSR_ROR		/* ROR = 1; Clear ROR */
	;

/*
 * MEP Query $22: Touchpad Coordinate Range Query is not supported by
 * the NavPoपूर्णांक module, so sampled values provide the शेष limits.
 */
#घोषणा NAVPOINT_X_MIN		1278
#घोषणा NAVPOINT_X_MAX		5340
#घोषणा NAVPOINT_Y_MIN		1572
#घोषणा NAVPOINT_Y_MAX		4396
#घोषणा NAVPOINT_PRESSURE_MIN	0
#घोषणा NAVPOINT_PRESSURE_MAX	255

अटल व्योम navpoपूर्णांक_packet(काष्ठा navpoपूर्णांक *navpoपूर्णांक)
अणु
	पूर्णांक finger;
	पूर्णांक gesture;
	पूर्णांक x, y, z;

	चयन (navpoपूर्णांक->data[0]) अणु
	हाल 0xff:	/* Garbage (packet?) between reset and Hello packet */
	हाल 0x00:	/* Module 0, शून्य packet */
		अवरोध;

	हाल 0x0e:	/* Module 0, Absolute packet */
		finger = (navpoपूर्णांक->data[1] & 0x01);
		gesture = (navpoपूर्णांक->data[1] & 0x02);
		x = ((navpoपूर्णांक->data[2] & 0x1f) << 8) | navpoपूर्णांक->data[3];
		y = ((navpoपूर्णांक->data[4] & 0x1f) << 8) | navpoपूर्णांक->data[5];
		z = navpoपूर्णांक->data[6];
		input_report_key(navpoपूर्णांक->input, BTN_TOUCH, finger);
		input_report_असल(navpoपूर्णांक->input, ABS_X, x);
		input_report_असल(navpoपूर्णांक->input, ABS_Y, y);
		input_report_असल(navpoपूर्णांक->input, ABS_PRESSURE, z);
		input_report_key(navpoपूर्णांक->input, BTN_TOOL_FINGER, finger);
		input_report_key(navpoपूर्णांक->input, BTN_LEFT, gesture);
		input_sync(navpoपूर्णांक->input);
		अवरोध;

	हाल 0x19:	/* Module 0, Hello packet */
		अगर ((navpoपूर्णांक->data[1] & 0xf0) == 0x10)
			अवरोध;
		fallthrough;
	शेष:
		dev_warn(navpoपूर्णांक->dev,
			 "spurious packet: data=0x%02x,0x%02x,...\n",
			 navpoपूर्णांक->data[0], navpoपूर्णांक->data[1]);
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t navpoपूर्णांक_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा navpoपूर्णांक *navpoपूर्णांक = dev_id;
	काष्ठा ssp_device *ssp = navpoपूर्णांक->ssp;
	irqवापस_t ret = IRQ_NONE;
	u32 status;

	status = pxa_ssp_पढ़ो_reg(ssp, SSSR);
	अगर (status & sssr) अणु
		dev_warn(navpoपूर्णांक->dev,
			 "unexpected interrupt: status=0x%08x\n", status);
		pxa_ssp_ग_लिखो_reg(ssp, SSSR, (status & sssr));
		ret = IRQ_HANDLED;
	पूर्ण

	जबतक (status & SSSR_RNE) अणु
		u32 data;

		data = pxa_ssp_पढ़ो_reg(ssp, SSDR);
		navpoपूर्णांक->data[navpoपूर्णांक->index + 0] = (data >> 8);
		navpoपूर्णांक->data[navpoपूर्णांक->index + 1] = data;
		navpoपूर्णांक->index += 2;
		अगर (HEADER_LENGTH(navpoपूर्णांक->data[0]) < navpoपूर्णांक->index) अणु
			navpoपूर्णांक_packet(navpoपूर्णांक);
			navpoपूर्णांक->index = 0;
		पूर्ण
		status = pxa_ssp_पढ़ो_reg(ssp, SSSR);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम navpoपूर्णांक_up(काष्ठा navpoपूर्णांक *navpoपूर्णांक)
अणु
	काष्ठा ssp_device *ssp = navpoपूर्णांक->ssp;
	पूर्णांक समयout;

	clk_prepare_enable(ssp->clk);

	pxa_ssp_ग_लिखो_reg(ssp, SSCR1, sscr1);
	pxa_ssp_ग_लिखो_reg(ssp, SSSR, sssr);
	pxa_ssp_ग_लिखो_reg(ssp, SSTO, 0);
	pxa_ssp_ग_लिखो_reg(ssp, SSCR0, sscr0);	/* SSCR0_SSE written last */

	/* Wait until SSP port is पढ़ोy क्रम slave घड़ी operations */
	क्रम (समयout = 100; समयout != 0; --समयout) अणु
		अगर (!(pxa_ssp_पढ़ो_reg(ssp, SSSR) & SSSR_CSS))
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (समयout == 0)
		dev_err(navpoपूर्णांक->dev,
			"timeout waiting for SSSR[CSS] to clear\n");

	अगर (gpio_is_valid(navpoपूर्णांक->gpio))
		gpio_set_value(navpoपूर्णांक->gpio, 1);
पूर्ण

अटल व्योम navpoपूर्णांक_करोwn(काष्ठा navpoपूर्णांक *navpoपूर्णांक)
अणु
	काष्ठा ssp_device *ssp = navpoपूर्णांक->ssp;

	अगर (gpio_is_valid(navpoपूर्णांक->gpio))
		gpio_set_value(navpoपूर्णांक->gpio, 0);

	pxa_ssp_ग_लिखो_reg(ssp, SSCR0, 0);

	clk_disable_unprepare(ssp->clk);
पूर्ण

अटल पूर्णांक navpoपूर्णांक_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा navpoपूर्णांक *navpoपूर्णांक = input_get_drvdata(input);

	navpoपूर्णांक_up(navpoपूर्णांक);

	वापस 0;
पूर्ण

अटल व्योम navpoपूर्णांक_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा navpoपूर्णांक *navpoपूर्णांक = input_get_drvdata(input);

	navpoपूर्णांक_करोwn(navpoपूर्णांक);
पूर्ण

अटल पूर्णांक navpoपूर्णांक_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा navpoपूर्णांक_platक्रमm_data *pdata =
					dev_get_platdata(&pdev->dev);
	काष्ठा ssp_device *ssp;
	काष्ठा input_dev *input;
	काष्ठा navpoपूर्णांक *navpoपूर्णांक;
	पूर्णांक error;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "no platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (gpio_is_valid(pdata->gpio)) अणु
		error = gpio_request_one(pdata->gpio, GPIOF_OUT_INIT_LOW,
					 "SYNAPTICS_ON");
		अगर (error)
			वापस error;
	पूर्ण

	ssp = pxa_ssp_request(pdata->port, pdev->name);
	अगर (!ssp) अणु
		error = -ENODEV;
		जाओ err_मुक्त_gpio;
	पूर्ण

	/* HaRET करोes not disable devices beक्रमe jumping पूर्णांकo Linux */
	अगर (pxa_ssp_पढ़ो_reg(ssp, SSCR0) & SSCR0_SSE) अणु
		pxa_ssp_ग_लिखो_reg(ssp, SSCR0, 0);
		dev_warn(&pdev->dev, "ssp%d already enabled\n", pdata->port);
	पूर्ण

	navpoपूर्णांक = kzalloc(माप(*navpoपूर्णांक), GFP_KERNEL);
	input = input_allocate_device();
	अगर (!navpoपूर्णांक || !input) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	navpoपूर्णांक->ssp = ssp;
	navpoपूर्णांक->input = input;
	navpoपूर्णांक->dev = &pdev->dev;
	navpoपूर्णांक->gpio = pdata->gpio;

	input->name = pdev->name;
	input->dev.parent = &pdev->dev;

	__set_bit(EV_KEY, input->evbit);
	__set_bit(EV_ABS, input->evbit);
	__set_bit(BTN_LEFT, input->keybit);
	__set_bit(BTN_TOUCH, input->keybit);
	__set_bit(BTN_TOOL_FINGER, input->keybit);

	input_set_असल_params(input, ABS_X,
			     NAVPOINT_X_MIN, NAVPOINT_X_MAX, 0, 0);
	input_set_असल_params(input, ABS_Y,
			     NAVPOINT_Y_MIN, NAVPOINT_Y_MAX, 0, 0);
	input_set_असल_params(input, ABS_PRESSURE,
			     NAVPOINT_PRESSURE_MIN, NAVPOINT_PRESSURE_MAX,
			     0, 0);

	input->खोलो = navpoपूर्णांक_खोलो;
	input->बंद = navpoपूर्णांक_बंद;

	input_set_drvdata(input, navpoपूर्णांक);

	error = request_irq(ssp->irq, navpoपूर्णांक_irq, 0, pdev->name, navpoपूर्णांक);
	अगर (error)
		जाओ err_मुक्त_mem;

	error = input_रेजिस्टर_device(input);
	अगर (error)
		जाओ err_मुक्त_irq;

	platक्रमm_set_drvdata(pdev, navpoपूर्णांक);
	dev_dbg(&pdev->dev, "ssp%d, irq %d\n", pdata->port, ssp->irq);

	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(ssp->irq, navpoपूर्णांक);
err_मुक्त_mem:
	input_मुक्त_device(input);
	kमुक्त(navpoपूर्णांक);
	pxa_ssp_मुक्त(ssp);
err_मुक्त_gpio:
	अगर (gpio_is_valid(pdata->gpio))
		gpio_मुक्त(pdata->gpio);

	वापस error;
पूर्ण

अटल पूर्णांक navpoपूर्णांक_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा navpoपूर्णांक_platक्रमm_data *pdata =
					dev_get_platdata(&pdev->dev);
	काष्ठा navpoपूर्णांक *navpoपूर्णांक = platक्रमm_get_drvdata(pdev);
	काष्ठा ssp_device *ssp = navpoपूर्णांक->ssp;

	मुक्त_irq(ssp->irq, navpoपूर्णांक);

	input_unरेजिस्टर_device(navpoपूर्णांक->input);
	kमुक्त(navpoपूर्णांक);

	pxa_ssp_मुक्त(ssp);

	अगर (gpio_is_valid(pdata->gpio))
		gpio_मुक्त(pdata->gpio);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused navpoपूर्णांक_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा navpoपूर्णांक *navpoपूर्णांक = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input = navpoपूर्णांक->input;

	mutex_lock(&input->mutex);
	अगर (input_device_enabled(input))
		navpoपूर्णांक_करोwn(navpoपूर्णांक);
	mutex_unlock(&input->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused navpoपूर्णांक_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा navpoपूर्णांक *navpoपूर्णांक = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input = navpoपूर्णांक->input;

	mutex_lock(&input->mutex);
	अगर (input_device_enabled(input))
		navpoपूर्णांक_up(navpoपूर्णांक);
	mutex_unlock(&input->mutex);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(navpoपूर्णांक_pm_ops, navpoपूर्णांक_suspend, navpoपूर्णांक_resume);

अटल काष्ठा platक्रमm_driver navpoपूर्णांक_driver = अणु
	.probe		= navpoपूर्णांक_probe,
	.हटाओ		= navpoपूर्णांक_हटाओ,
	.driver = अणु
		.name	= "navpoint",
		.pm	= &navpoपूर्णांक_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(navpoपूर्णांक_driver);

MODULE_AUTHOR("Paul Parsons <lost.distance@yahoo.com>");
MODULE_DESCRIPTION("Synaptics NavPoint (PXA27x SSP/SPI) driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:navpoint");
