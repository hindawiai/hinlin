<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HTC Shअगरt touchscreen driver
 *
 * Copyright (C) 2008 Pau Oliva Fora <pof@eslack.org>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/isa.h>
#समावेश <linux/ioport.h>
#समावेश <linux/dmi.h>

MODULE_AUTHOR("Pau Oliva Fora <pau@eslack.org>");
MODULE_DESCRIPTION("HTC Shift touchscreen driver");
MODULE_LICENSE("GPL");

#घोषणा HTCPEN_PORT_IRQ_CLEAR	0x068
#घोषणा HTCPEN_PORT_INIT	0x06c
#घोषणा HTCPEN_PORT_INDEX	0x0250
#घोषणा HTCPEN_PORT_DATA	0x0251
#घोषणा HTCPEN_IRQ		3

#घोषणा DEVICE_ENABLE		0xa2
#घोषणा DEVICE_DISABLE		0xa3

#घोषणा X_INDEX			3
#घोषणा Y_INDEX			5
#घोषणा TOUCH_INDEX		0xb
#घोषणा LSB_XY_INDEX		0xc
#घोषणा X_AXIS_MAX		2040
#घोषणा Y_AXIS_MAX		2040

अटल bool invert_x;
module_param(invert_x, bool, 0644);
MODULE_PARM_DESC(invert_x, "If set, X axis is inverted");
अटल bool invert_y;
module_param(invert_y, bool, 0644);
MODULE_PARM_DESC(invert_y, "If set, Y axis is inverted");

अटल irqवापस_t htcpen_पूर्णांकerrupt(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा input_dev *htcpen_dev = handle;
	अचिन्हित लघु x, y, xy;

	/* 0 = press; 1 = release */
	outb_p(TOUCH_INDEX, HTCPEN_PORT_INDEX);

	अगर (inb_p(HTCPEN_PORT_DATA)) अणु
		input_report_key(htcpen_dev, BTN_TOUCH, 0);
	पूर्ण अन्यथा अणु
		outb_p(X_INDEX, HTCPEN_PORT_INDEX);
		x = inb_p(HTCPEN_PORT_DATA);

		outb_p(Y_INDEX, HTCPEN_PORT_INDEX);
		y = inb_p(HTCPEN_PORT_DATA);

		outb_p(LSB_XY_INDEX, HTCPEN_PORT_INDEX);
		xy = inb_p(HTCPEN_PORT_DATA);

		/* get high resolution value of X and Y using LSB */
		x = X_AXIS_MAX - ((x * 8) + ((xy >> 4) & 0xf));
		y = (y * 8) + (xy & 0xf);
		अगर (invert_x)
			x = X_AXIS_MAX - x;
		अगर (invert_y)
			y = Y_AXIS_MAX - y;

		अगर (x != X_AXIS_MAX && x != 0) अणु
			input_report_key(htcpen_dev, BTN_TOUCH, 1);
			input_report_असल(htcpen_dev, ABS_X, x);
			input_report_असल(htcpen_dev, ABS_Y, y);
		पूर्ण
	पूर्ण

	input_sync(htcpen_dev);

	inb_p(HTCPEN_PORT_IRQ_CLEAR);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक htcpen_खोलो(काष्ठा input_dev *dev)
अणु
	outb_p(DEVICE_ENABLE, HTCPEN_PORT_INIT);

	वापस 0;
पूर्ण

अटल व्योम htcpen_बंद(काष्ठा input_dev *dev)
अणु
	outb_p(DEVICE_DISABLE, HTCPEN_PORT_INIT);
	synchronize_irq(HTCPEN_IRQ);
पूर्ण

अटल पूर्णांक htcpen_isa_probe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	काष्ठा input_dev *htcpen_dev;
	पूर्णांक err = -EBUSY;

	अगर (!request_region(HTCPEN_PORT_IRQ_CLEAR, 1, "htcpen")) अणु
		prपूर्णांकk(KERN_ERR "htcpen: unable to get IO region 0x%x\n",
			HTCPEN_PORT_IRQ_CLEAR);
		जाओ request_region1_failed;
	पूर्ण

	अगर (!request_region(HTCPEN_PORT_INIT, 1, "htcpen")) अणु
		prपूर्णांकk(KERN_ERR "htcpen: unable to get IO region 0x%x\n",
			HTCPEN_PORT_INIT);
		जाओ request_region2_failed;
	पूर्ण

	अगर (!request_region(HTCPEN_PORT_INDEX, 2, "htcpen")) अणु
		prपूर्णांकk(KERN_ERR "htcpen: unable to get IO region 0x%x\n",
			HTCPEN_PORT_INDEX);
		जाओ request_region3_failed;
	पूर्ण

	htcpen_dev = input_allocate_device();
	अगर (!htcpen_dev) अणु
		prपूर्णांकk(KERN_ERR "htcpen: can't allocate device\n");
		err = -ENOMEM;
		जाओ input_alloc_failed;
	पूर्ण

	htcpen_dev->name = "HTC Shift EC TouchScreen";
	htcpen_dev->id.bustype = BUS_ISA;

	htcpen_dev->evbit[0] = BIT_MASK(EV_ABS) | BIT_MASK(EV_KEY);
	htcpen_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(htcpen_dev, ABS_X, 0, X_AXIS_MAX, 0, 0);
	input_set_असल_params(htcpen_dev, ABS_Y, 0, Y_AXIS_MAX, 0, 0);

	htcpen_dev->खोलो = htcpen_खोलो;
	htcpen_dev->बंद = htcpen_बंद;

	err = request_irq(HTCPEN_IRQ, htcpen_पूर्णांकerrupt, 0, "htcpen",
			htcpen_dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "htcpen: irq busy\n");
		जाओ request_irq_failed;
	पूर्ण

	inb_p(HTCPEN_PORT_IRQ_CLEAR);

	err = input_रेजिस्टर_device(htcpen_dev);
	अगर (err)
		जाओ input_रेजिस्टर_failed;

	dev_set_drvdata(dev, htcpen_dev);

	वापस 0;

 input_रेजिस्टर_failed:
	मुक्त_irq(HTCPEN_IRQ, htcpen_dev);
 request_irq_failed:
	input_मुक्त_device(htcpen_dev);
 input_alloc_failed:
	release_region(HTCPEN_PORT_INDEX, 2);
 request_region3_failed:
	release_region(HTCPEN_PORT_INIT, 1);
 request_region2_failed:
	release_region(HTCPEN_PORT_IRQ_CLEAR, 1);
 request_region1_failed:
	वापस err;
पूर्ण

अटल व्योम htcpen_isa_हटाओ(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	काष्ठा input_dev *htcpen_dev = dev_get_drvdata(dev);

	input_unरेजिस्टर_device(htcpen_dev);

	मुक्त_irq(HTCPEN_IRQ, htcpen_dev);

	release_region(HTCPEN_PORT_INDEX, 2);
	release_region(HTCPEN_PORT_INIT, 1);
	release_region(HTCPEN_PORT_IRQ_CLEAR, 1);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक htcpen_isa_suspend(काष्ठा device *dev, अचिन्हित पूर्णांक n,
				pm_message_t state)
अणु
	outb_p(DEVICE_DISABLE, HTCPEN_PORT_INIT);

	वापस 0;
पूर्ण

अटल पूर्णांक htcpen_isa_resume(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	outb_p(DEVICE_ENABLE, HTCPEN_PORT_INIT);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा isa_driver htcpen_isa_driver = अणु
	.probe		= htcpen_isa_probe,
	.हटाओ		= htcpen_isa_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= htcpen_isa_suspend,
	.resume		= htcpen_isa_resume,
#पूर्ण_अगर
	.driver = अणु
		.owner	= THIS_MODULE,
		.name	= "htcpen",
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id htcshअगरt_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "Shift",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "High Tech Computer Corp"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Shift"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, htcshअगरt_dmi_table);

अटल पूर्णांक __init htcpen_isa_init(व्योम)
अणु
	अगर (!dmi_check_प्रणाली(htcshअगरt_dmi_table))
		वापस -ENODEV;

	वापस isa_रेजिस्टर_driver(&htcpen_isa_driver, 1);
पूर्ण

अटल व्योम __निकास htcpen_isa_निकास(व्योम)
अणु
	isa_unरेजिस्टर_driver(&htcpen_isa_driver);
पूर्ण

module_init(htcpen_isa_init);
module_निकास(htcpen_isa_निकास);
