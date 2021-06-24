<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenCores Keyboard Controller Driver
 * http://www.खोलोcores.org/project,keyboardcontroller
 *
 * Copyright 2007-2009 HV Sistemas S.L.
 */

#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

काष्ठा खोलोcores_kbd अणु
	काष्ठा input_dev *input;
	व्योम __iomem *addr;
	पूर्णांक irq;
	अचिन्हित लघु keycodes[128];
पूर्ण;

अटल irqवापस_t खोलोcores_kbd_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा खोलोcores_kbd *खोलोcores_kbd = dev_id;
	काष्ठा input_dev *input = खोलोcores_kbd->input;
	अचिन्हित अक्षर c;

	c = पढ़ोb(खोलोcores_kbd->addr);
	input_report_key(input, c & 0x7f, c & 0x80 ? 0 : 1);
	input_sync(input);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक खोलोcores_kbd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *input;
	काष्ठा खोलोcores_kbd *खोलोcores_kbd;
	काष्ठा resource *res;
	पूर्णांक irq, i, error;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "missing board memory resource\n");
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	खोलोcores_kbd = devm_kzalloc(&pdev->dev, माप(*खोलोcores_kbd),
				     GFP_KERNEL);
	अगर (!खोलोcores_kbd)
		वापस -ENOMEM;

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input) अणु
		dev_err(&pdev->dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	खोलोcores_kbd->input = input;

	खोलोcores_kbd->addr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(खोलोcores_kbd->addr))
		वापस PTR_ERR(खोलोcores_kbd->addr);

	input->name = pdev->name;
	input->phys = "opencores-kbd/input0";

	input->id.bustype = BUS_HOST;
	input->id.venकरोr = 0x0001;
	input->id.product = 0x0001;
	input->id.version = 0x0100;

	input->keycode = खोलोcores_kbd->keycodes;
	input->keycodesize = माप(खोलोcores_kbd->keycodes[0]);
	input->keycodemax = ARRAY_SIZE(खोलोcores_kbd->keycodes);

	__set_bit(EV_KEY, input->evbit);

	क्रम (i = 0; i < ARRAY_SIZE(खोलोcores_kbd->keycodes); i++) अणु
		/*
		 * OpenCores controller happens to have scancodes match
		 * our KEY_* definitions.
		 */
		खोलोcores_kbd->keycodes[i] = i;
		__set_bit(खोलोcores_kbd->keycodes[i], input->keybit);
	पूर्ण
	__clear_bit(KEY_RESERVED, input->keybit);

	error = devm_request_irq(&pdev->dev, irq, &खोलोcores_kbd_isr,
				 IRQF_TRIGGER_RISING,
				 pdev->name, खोलोcores_kbd);
	अगर (error) अणु
		dev_err(&pdev->dev, "unable to claim irq %d\n", irq);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&pdev->dev, "unable to register input device\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver खोलोcores_kbd_device_driver = अणु
	.probe    = खोलोcores_kbd_probe,
	.driver   = अणु
		.name = "opencores-kbd",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(खोलोcores_kbd_device_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Javier Herrero <jherrero@hvsistemas.es>");
MODULE_DESCRIPTION("Keyboard driver for OpenCores Keyboard Controller");
