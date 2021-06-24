<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 *
 *  Based on the work of:
 *	James Banks		Matthew Dillon
 *	David Giller		Nathan Lareकरो
 *	Linus Torvalds		Johan Myreen
 *	Clअगरf Matthews		Philip Blundell
 *	Russell King
 */

/*
 * Logitech Bus Mouse Driver क्रम Linux
 */

/*
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Logitech busmouse driver");
MODULE_LICENSE("GPL");

#घोषणा	LOGIBM_BASE		0x23c
#घोषणा	LOGIBM_EXTENT		4

#घोषणा	LOGIBM_DATA_PORT	LOGIBM_BASE + 0
#घोषणा	LOGIBM_SIGNATURE_PORT	LOGIBM_BASE + 1
#घोषणा	LOGIBM_CONTROL_PORT	LOGIBM_BASE + 2
#घोषणा	LOGIBM_CONFIG_PORT	LOGIBM_BASE + 3

#घोषणा	LOGIBM_ENABLE_IRQ	0x00
#घोषणा	LOGIBM_DISABLE_IRQ	0x10
#घोषणा	LOGIBM_READ_X_LOW	0x80
#घोषणा	LOGIBM_READ_X_HIGH	0xa0
#घोषणा	LOGIBM_READ_Y_LOW	0xc0
#घोषणा	LOGIBM_READ_Y_HIGH	0xe0

#घोषणा LOGIBM_DEFAULT_MODE	0x90
#घोषणा LOGIBM_CONFIG_BYTE	0x91
#घोषणा LOGIBM_SIGNATURE_BYTE	0xa5

#घोषणा LOGIBM_IRQ		5

अटल पूर्णांक logibm_irq = LOGIBM_IRQ;
module_param_hw_named(irq, logibm_irq, uपूर्णांक, irq, 0);
MODULE_PARM_DESC(irq, "IRQ number (5=default)");

अटल काष्ठा input_dev *logibm_dev;

अटल irqवापस_t logibm_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अक्षर dx, dy;
	अचिन्हित अक्षर buttons;

	outb(LOGIBM_READ_X_LOW, LOGIBM_CONTROL_PORT);
	dx = (inb(LOGIBM_DATA_PORT) & 0xf);
	outb(LOGIBM_READ_X_HIGH, LOGIBM_CONTROL_PORT);
	dx |= (inb(LOGIBM_DATA_PORT) & 0xf) << 4;
	outb(LOGIBM_READ_Y_LOW, LOGIBM_CONTROL_PORT);
	dy = (inb(LOGIBM_DATA_PORT) & 0xf);
	outb(LOGIBM_READ_Y_HIGH, LOGIBM_CONTROL_PORT);
	buttons = inb(LOGIBM_DATA_PORT);
	dy |= (buttons & 0xf) << 4;
	buttons = ~buttons >> 5;

	input_report_rel(logibm_dev, REL_X, dx);
	input_report_rel(logibm_dev, REL_Y, dy);
	input_report_key(logibm_dev, BTN_RIGHT,  buttons & 1);
	input_report_key(logibm_dev, BTN_MIDDLE, buttons & 2);
	input_report_key(logibm_dev, BTN_LEFT,   buttons & 4);
	input_sync(logibm_dev);

	outb(LOGIBM_ENABLE_IRQ, LOGIBM_CONTROL_PORT);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक logibm_खोलो(काष्ठा input_dev *dev)
अणु
	अगर (request_irq(logibm_irq, logibm_पूर्णांकerrupt, 0, "logibm", शून्य)) अणु
		prपूर्णांकk(KERN_ERR "logibm.c: Can't allocate irq %d\n", logibm_irq);
		वापस -EBUSY;
	पूर्ण
	outb(LOGIBM_ENABLE_IRQ, LOGIBM_CONTROL_PORT);
	वापस 0;
पूर्ण

अटल व्योम logibm_बंद(काष्ठा input_dev *dev)
अणु
	outb(LOGIBM_DISABLE_IRQ, LOGIBM_CONTROL_PORT);
	मुक्त_irq(logibm_irq, शून्य);
पूर्ण

अटल पूर्णांक __init logibm_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!request_region(LOGIBM_BASE, LOGIBM_EXTENT, "logibm")) अणु
		prपूर्णांकk(KERN_ERR "logibm.c: Can't allocate ports at %#x\n", LOGIBM_BASE);
		वापस -EBUSY;
	पूर्ण

	outb(LOGIBM_CONFIG_BYTE, LOGIBM_CONFIG_PORT);
	outb(LOGIBM_SIGNATURE_BYTE, LOGIBM_SIGNATURE_PORT);
	udelay(100);

	अगर (inb(LOGIBM_SIGNATURE_PORT) != LOGIBM_SIGNATURE_BYTE) अणु
		prपूर्णांकk(KERN_INFO "logibm.c: Didn't find Logitech busmouse at %#x\n", LOGIBM_BASE);
		err = -ENODEV;
		जाओ err_release_region;
	पूर्ण

	outb(LOGIBM_DEFAULT_MODE, LOGIBM_CONFIG_PORT);
	outb(LOGIBM_DISABLE_IRQ, LOGIBM_CONTROL_PORT);

	logibm_dev = input_allocate_device();
	अगर (!logibm_dev) अणु
		prपूर्णांकk(KERN_ERR "logibm.c: Not enough memory for input device\n");
		err = -ENOMEM;
		जाओ err_release_region;
	पूर्ण

	logibm_dev->name = "Logitech bus mouse";
	logibm_dev->phys = "isa023c/input0";
	logibm_dev->id.bustype = BUS_ISA;
	logibm_dev->id.venकरोr  = 0x0003;
	logibm_dev->id.product = 0x0001;
	logibm_dev->id.version = 0x0100;

	logibm_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
	logibm_dev->keybit[BIT_WORD(BTN_LEFT)] = BIT_MASK(BTN_LEFT) |
		BIT_MASK(BTN_MIDDLE) | BIT_MASK(BTN_RIGHT);
	logibm_dev->relbit[0] = BIT_MASK(REL_X) | BIT_MASK(REL_Y);

	logibm_dev->खोलो  = logibm_खोलो;
	logibm_dev->बंद = logibm_बंद;

	err = input_रेजिस्टर_device(logibm_dev);
	अगर (err)
		जाओ err_मुक्त_dev;

	वापस 0;

 err_मुक्त_dev:
	input_मुक्त_device(logibm_dev);
 err_release_region:
	release_region(LOGIBM_BASE, LOGIBM_EXTENT);

	वापस err;
पूर्ण

अटल व्योम __निकास logibm_निकास(व्योम)
अणु
	input_unरेजिस्टर_device(logibm_dev);
	release_region(LOGIBM_BASE, LOGIBM_EXTENT);
पूर्ण

module_init(logibm_init);
module_निकास(logibm_निकास);
