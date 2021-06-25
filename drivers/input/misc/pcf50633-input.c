<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* NXP PCF50633 Input Driver
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * Author: Balaji Rao <balajirrao@खोलोmoko.org>
 * All rights reserved.
 *
 * Broken करोwn from monstrous PCF50633 driver मुख्यly by
 * Harald Welte, Andy Green and Werner Almesberger
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/pcf50633/core.h>

#घोषणा PCF50633_OOCSTAT_ONKEY	0x01
#घोषणा PCF50633_REG_OOCSTAT	0x12
#घोषणा PCF50633_REG_OOCMODE	0x10

काष्ठा pcf50633_input अणु
	काष्ठा pcf50633 *pcf;
	काष्ठा input_dev *input_dev;
पूर्ण;

अटल व्योम
pcf50633_input_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pcf50633_input *input;
	पूर्णांक onkey_released;

	input = data;

	/* We report only one event depending on the key press status */
	onkey_released = pcf50633_reg_पढ़ो(input->pcf, PCF50633_REG_OOCSTAT)
						& PCF50633_OOCSTAT_ONKEY;

	अगर (irq == PCF50633_IRQ_ONKEYF && !onkey_released)
		input_report_key(input->input_dev, KEY_POWER, 1);
	अन्यथा अगर (irq == PCF50633_IRQ_ONKEYR && onkey_released)
		input_report_key(input->input_dev, KEY_POWER, 0);

	input_sync(input->input_dev);
पूर्ण

अटल पूर्णांक pcf50633_input_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pcf50633_input *input;
	काष्ठा input_dev *input_dev;
	पूर्णांक ret;


	input = kzalloc(माप(*input), GFP_KERNEL);
	अगर (!input)
		वापस -ENOMEM;

	input_dev = input_allocate_device();
	अगर (!input_dev) अणु
		kमुक्त(input);
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pdev, input);
	input->pcf = dev_to_pcf50633(pdev->dev.parent);
	input->input_dev = input_dev;

	input_dev->name = "PCF50633 PMU events";
	input_dev->id.bustype = BUS_I2C;
	input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_PWR);
	set_bit(KEY_POWER, input_dev->keybit);

	ret = input_रेजिस्टर_device(input_dev);
	अगर (ret) अणु
		input_मुक्त_device(input_dev);
		kमुक्त(input);
		वापस ret;
	पूर्ण
	pcf50633_रेजिस्टर_irq(input->pcf, PCF50633_IRQ_ONKEYR,
				pcf50633_input_irq, input);
	pcf50633_रेजिस्टर_irq(input->pcf, PCF50633_IRQ_ONKEYF,
				pcf50633_input_irq, input);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf50633_input_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pcf50633_input *input  = platक्रमm_get_drvdata(pdev);

	pcf50633_मुक्त_irq(input->pcf, PCF50633_IRQ_ONKEYR);
	pcf50633_मुक्त_irq(input->pcf, PCF50633_IRQ_ONKEYF);

	input_unरेजिस्टर_device(input->input_dev);
	kमुक्त(input);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pcf50633_input_driver = अणु
	.driver = अणु
		.name = "pcf50633-input",
	पूर्ण,
	.probe = pcf50633_input_probe,
	.हटाओ = pcf50633_input_हटाओ,
पूर्ण;
module_platक्रमm_driver(pcf50633_input_driver);

MODULE_AUTHOR("Balaji Rao <balajirrao@openmoko.org>");
MODULE_DESCRIPTION("PCF50633 input driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pcf50633-input");
