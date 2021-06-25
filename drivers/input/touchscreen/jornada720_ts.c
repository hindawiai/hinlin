<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/input/touchscreen/jornada720_ts.c
 *
 * Copyright (C) 2007 Kristoffer Ericson <Kristoffer.Ericson@gmail.com>
 *
 *  Copyright (C) 2006 Filip Zyzniewski <filip.zyzniewski@tefnet.pl>
 *  based on HP Jornada 56x touchscreen driver by Alex Lange <chicken@handhelds.org>
 *
 * HP Jornada 710/720/729 Touchscreen Driver
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश <mach/jornada720.h>

MODULE_AUTHOR("Kristoffer Ericson <kristoffer.ericson@gmail.com>");
MODULE_DESCRIPTION("HP Jornada 710/720/728 touchscreen driver");
MODULE_LICENSE("GPL v2");

काष्ठा jornada_ts अणु
	काष्ठा input_dev *dev;
	काष्ठा gpio_desc *gpio;
	पूर्णांक x_data[4];		/* X sample values */
	पूर्णांक y_data[4];		/* Y sample values */
पूर्ण;

अटल व्योम jornada720_ts_collect_data(काष्ठा jornada_ts *jornada_ts)
अणु
	/* 3 low word X samples */
	jornada_ts->x_data[0] = jornada_ssp_byte(TXDUMMY);
	jornada_ts->x_data[1] = jornada_ssp_byte(TXDUMMY);
	jornada_ts->x_data[2] = jornada_ssp_byte(TXDUMMY);

	/* 3 low word Y samples */
	jornada_ts->y_data[0] = jornada_ssp_byte(TXDUMMY);
	jornada_ts->y_data[1] = jornada_ssp_byte(TXDUMMY);
	jornada_ts->y_data[2] = jornada_ssp_byte(TXDUMMY);

	/* combined x samples bits */
	jornada_ts->x_data[3] = jornada_ssp_byte(TXDUMMY);

	/* combined y samples bits */
	jornada_ts->y_data[3] = jornada_ssp_byte(TXDUMMY);
पूर्ण

अटल पूर्णांक jornada720_ts_average(पूर्णांक coords[4])
अणु
	पूर्णांक coord, high_bits = coords[3];

	coord  = coords[0] | ((high_bits & 0x03) << 8);
	coord += coords[1] | ((high_bits & 0x0c) << 6);
	coord += coords[2] | ((high_bits & 0x30) << 4);

	वापस coord / 3;
पूर्ण

अटल irqवापस_t jornada720_ts_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *pdev = dev_id;
	काष्ठा jornada_ts *jornada_ts = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input = jornada_ts->dev;
	पूर्णांक x, y;

	/* If gpio is high then report pen up */
	अगर (gpiod_get_value(jornada_ts->gpio)) अणु
		input_report_key(input, BTN_TOUCH, 0);
		input_sync(input);
	पूर्ण अन्यथा अणु
		jornada_ssp_start();

		/* proper reply to request is always TXDUMMY */
		अगर (jornada_ssp_inout(GETTOUCHSAMPLES) == TXDUMMY) अणु
			jornada720_ts_collect_data(jornada_ts);

			x = jornada720_ts_average(jornada_ts->x_data);
			y = jornada720_ts_average(jornada_ts->y_data);

			input_report_key(input, BTN_TOUCH, 1);
			input_report_असल(input, ABS_X, x);
			input_report_असल(input, ABS_Y, y);
			input_sync(input);
		पूर्ण

		jornada_ssp_end();
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक jornada720_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा jornada_ts *jornada_ts;
	काष्ठा input_dev *input_dev;
	पूर्णांक error, irq;

	jornada_ts = devm_kzalloc(&pdev->dev, माप(*jornada_ts), GFP_KERNEL);
	अगर (!jornada_ts)
		वापस -ENOMEM;

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, jornada_ts);

	jornada_ts->gpio = devm_gpiod_get(&pdev->dev, "penup", GPIOD_IN);
	अगर (IS_ERR(jornada_ts->gpio))
		वापस PTR_ERR(jornada_ts->gpio);

	irq = gpiod_to_irq(jornada_ts->gpio);
	अगर (irq <= 0)
		वापस irq < 0 ? irq : -EINVAL;

	jornada_ts->dev = input_dev;

	input_dev->name = "HP Jornada 7xx Touchscreen";
	input_dev->phys = "jornadats/input0";
	input_dev->id.bustype = BUS_HOST;
	input_dev->dev.parent = &pdev->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(input_dev, ABS_X, 270, 3900, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 180, 3700, 0, 0);

	error = devm_request_irq(&pdev->dev, irq, jornada720_ts_पूर्णांकerrupt,
				 IRQF_TRIGGER_RISING,
				 "HP7XX Touchscreen driver", pdev);
	अगर (error) अणु
		dev_err(&pdev->dev, "HP7XX TS : Unable to acquire irq!\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(jornada_ts->dev);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:jornada_ts");

अटल काष्ठा platक्रमm_driver jornada720_ts_driver = अणु
	.probe		= jornada720_ts_probe,
	.driver		= अणु
		.name	= "jornada_ts",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(jornada720_ts_driver);
