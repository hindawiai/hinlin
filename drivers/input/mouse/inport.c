<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 *
 *  Based on the work of:
 *	Teemu Rantanen		Derrick Cole
 *	Peter Cervasio		Christoph Niemann
 *	Philip Blundell		Russell King
 *	Bob Harris
 */

/*
 * Inport (ATI XL and Microsoft) busmouse driver क्रम Linux
 */

/*
 */

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Inport (ATI XL and Microsoft) busmouse driver");
MODULE_LICENSE("GPL");

#घोषणा INPORT_BASE		0x23c
#घोषणा INPORT_EXTENT		4

#घोषणा INPORT_CONTROL_PORT	INPORT_BASE + 0
#घोषणा INPORT_DATA_PORT	INPORT_BASE + 1
#घोषणा INPORT_SIGNATURE_PORT	INPORT_BASE + 2

#घोषणा INPORT_REG_BTNS	0x00
#घोषणा INPORT_REG_X		0x01
#घोषणा INPORT_REG_Y		0x02
#घोषणा INPORT_REG_MODE		0x07
#घोषणा INPORT_RESET		0x80

#अगर_घोषित CONFIG_MOUSE_ATIXL
#घोषणा INPORT_NAME		"ATI XL Mouse"
#घोषणा INPORT_VENDOR		0x0002
#घोषणा INPORT_SPEED_30HZ	0x01
#घोषणा INPORT_SPEED_50HZ	0x02
#घोषणा INPORT_SPEED_100HZ	0x03
#घोषणा INPORT_SPEED_200HZ	0x04
#घोषणा INPORT_MODE_BASE	INPORT_SPEED_100HZ
#घोषणा INPORT_MODE_IRQ		0x08
#अन्यथा
#घोषणा INPORT_NAME		"Microsoft InPort Mouse"
#घोषणा INPORT_VENDOR		0x0001
#घोषणा INPORT_MODE_BASE	0x10
#घोषणा INPORT_MODE_IRQ		0x01
#पूर्ण_अगर
#घोषणा INPORT_MODE_HOLD	0x20

#घोषणा INPORT_IRQ		5

अटल पूर्णांक inport_irq = INPORT_IRQ;
module_param_hw_named(irq, inport_irq, uपूर्णांक, irq, 0);
MODULE_PARM_DESC(irq, "IRQ number (5=default)");

अटल काष्ठा input_dev *inport_dev;

अटल irqवापस_t inport_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित अक्षर buttons;

	outb(INPORT_REG_MODE, INPORT_CONTROL_PORT);
	outb(INPORT_MODE_HOLD | INPORT_MODE_IRQ | INPORT_MODE_BASE, INPORT_DATA_PORT);

	outb(INPORT_REG_X, INPORT_CONTROL_PORT);
	input_report_rel(inport_dev, REL_X, inb(INPORT_DATA_PORT));

	outb(INPORT_REG_Y, INPORT_CONTROL_PORT);
	input_report_rel(inport_dev, REL_Y, inb(INPORT_DATA_PORT));

	outb(INPORT_REG_BTNS, INPORT_CONTROL_PORT);
	buttons = inb(INPORT_DATA_PORT);

	input_report_key(inport_dev, BTN_MIDDLE, buttons & 1);
	input_report_key(inport_dev, BTN_LEFT,   buttons & 2);
	input_report_key(inport_dev, BTN_RIGHT,  buttons & 4);

	outb(INPORT_REG_MODE, INPORT_CONTROL_PORT);
	outb(INPORT_MODE_IRQ | INPORT_MODE_BASE, INPORT_DATA_PORT);

	input_sync(inport_dev);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक inport_खोलो(काष्ठा input_dev *dev)
अणु
	अगर (request_irq(inport_irq, inport_पूर्णांकerrupt, 0, "inport", शून्य))
		वापस -EBUSY;
	outb(INPORT_REG_MODE, INPORT_CONTROL_PORT);
	outb(INPORT_MODE_IRQ | INPORT_MODE_BASE, INPORT_DATA_PORT);

	वापस 0;
पूर्ण

अटल व्योम inport_बंद(काष्ठा input_dev *dev)
अणु
	outb(INPORT_REG_MODE, INPORT_CONTROL_PORT);
	outb(INPORT_MODE_BASE, INPORT_DATA_PORT);
	मुक्त_irq(inport_irq, शून्य);
पूर्ण

अटल पूर्णांक __init inport_init(व्योम)
अणु
	अचिन्हित अक्षर a, b, c;
	पूर्णांक err;

	अगर (!request_region(INPORT_BASE, INPORT_EXTENT, "inport")) अणु
		prपूर्णांकk(KERN_ERR "inport.c: Can't allocate ports at %#x\n", INPORT_BASE);
		वापस -EBUSY;
	पूर्ण

	a = inb(INPORT_SIGNATURE_PORT);
	b = inb(INPORT_SIGNATURE_PORT);
	c = inb(INPORT_SIGNATURE_PORT);
	अगर (a == b || a != c) अणु
		prपूर्णांकk(KERN_INFO "inport.c: Didn't find InPort mouse at %#x\n", INPORT_BASE);
		err = -ENODEV;
		जाओ err_release_region;
	पूर्ण

	inport_dev = input_allocate_device();
	अगर (!inport_dev) अणु
		prपूर्णांकk(KERN_ERR "inport.c: Not enough memory for input device\n");
		err = -ENOMEM;
		जाओ err_release_region;
	पूर्ण

	inport_dev->name = INPORT_NAME;
	inport_dev->phys = "isa023c/input0";
	inport_dev->id.bustype = BUS_ISA;
	inport_dev->id.venकरोr  = INPORT_VENDOR;
	inport_dev->id.product = 0x0001;
	inport_dev->id.version = 0x0100;

	inport_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
	inport_dev->keybit[BIT_WORD(BTN_LEFT)] = BIT_MASK(BTN_LEFT) |
		BIT_MASK(BTN_MIDDLE) | BIT_MASK(BTN_RIGHT);
	inport_dev->relbit[0] = BIT_MASK(REL_X) | BIT_MASK(REL_Y);

	inport_dev->खोलो  = inport_खोलो;
	inport_dev->बंद = inport_बंद;

	outb(INPORT_RESET, INPORT_CONTROL_PORT);
	outb(INPORT_REG_MODE, INPORT_CONTROL_PORT);
	outb(INPORT_MODE_BASE, INPORT_DATA_PORT);

	err = input_रेजिस्टर_device(inport_dev);
	अगर (err)
		जाओ err_मुक्त_dev;

	वापस 0;

 err_मुक्त_dev:
	input_मुक्त_device(inport_dev);
 err_release_region:
	release_region(INPORT_BASE, INPORT_EXTENT);

	वापस err;
पूर्ण

अटल व्योम __निकास inport_निकास(व्योम)
अणु
	input_unरेजिस्टर_device(inport_dev);
	release_region(INPORT_BASE, INPORT_EXTENT);
पूर्ण

module_init(inport_init);
module_निकास(inport_निकास);
