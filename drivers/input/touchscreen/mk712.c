<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ICS MK712 touchscreen controller driver
 *
 * Copyright (c) 1999-2002 Transmeta Corporation
 * Copyright (c) 2005 Rick Koch <n1gp@hoपंचांगail.com>
 * Copyright (c) 2005 Vojtech Pavlik <vojtech@suse.cz>
 */


/*
 * This driver supports the ICS MicroClock MK712 TouchScreen controller,
 * found in Gateway AOL Connected Touchpad computers.
 *
 * Documentation क्रम ICS MK712 can be found at:
 *	https://www.idt.com/general-parts/mk712-touch-screen-controller
 */

/*
 * 1999-12-18: original version, Daniel Quinlan
 * 1999-12-19: added anti-jitter code, report pen-up events, fixed mk712_poll
 *             to use queue_empty, Nathan Lareकरो
 * 1999-12-20: improved अक्रमom poपूर्णांक rejection, Nathan Lareकरो
 * 2000-01-05: checked in new anti-jitter code, changed mouse protocol, fixed
 *             queue code, added module options, other fixes, Daniel Quinlan
 * 2002-03-15: Clean up क्रम kernel merge <alan@redhat.com>
 *             Fixed multi खोलो race, fixed memory checks, fixed resource
 *             allocation, fixed बंद/घातerकरोwn bug, चयनed to new init
 * 2005-01-18: Ported to 2.6 from 2.4.28, Rick Koch
 * 2005-02-05: Rewritten क्रम the input layer, Vojtech Pavlik
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <यंत्र/पन.स>

MODULE_AUTHOR("Daniel Quinlan <quinlan@pathname.com>, Vojtech Pavlik <vojtech@suse.cz>");
MODULE_DESCRIPTION("ICS MicroClock MK712 TouchScreen driver");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक mk712_io = 0x260;	/* Also 0x200, 0x208, 0x300 */
module_param_hw_named(io, mk712_io, uपूर्णांक, ioport, 0);
MODULE_PARM_DESC(io, "I/O base address of MK712 touchscreen controller");

अटल अचिन्हित पूर्णांक mk712_irq = 10;	/* Also 12, 14, 15 */
module_param_hw_named(irq, mk712_irq, uपूर्णांक, irq, 0);
MODULE_PARM_DESC(irq, "IRQ of MK712 touchscreen controller");

/* eight 8-bit रेजिस्टरs */
#घोषणा MK712_STATUS		0
#घोषणा MK712_X			2
#घोषणा MK712_Y			4
#घोषणा MK712_CONTROL		6
#घोषणा MK712_RATE		7

/* status */
#घोषणा	MK712_STATUS_TOUCH			0x10
#घोषणा	MK712_CONVERSION_COMPLETE		0x80

/* control */
#घोषणा MK712_ENABLE_INT			0x01
#घोषणा MK712_INT_ON_CONVERSION_COMPLETE	0x02
#घोषणा MK712_INT_ON_CHANGE_IN_TOUCH_STATUS	0x04
#घोषणा MK712_ENABLE_PERIODIC_CONVERSIONS	0x10
#घोषणा MK712_READ_ONE_POINT			0x20
#घोषणा MK712_POWERUP				0x40

अटल काष्ठा input_dev *mk712_dev;
अटल DEFINE_SPINLOCK(mk712_lock);

अटल irqवापस_t mk712_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित अक्षर status;
	अटल पूर्णांक debounce = 1;
	अटल अचिन्हित लघु last_x;
	अटल अचिन्हित लघु last_y;

	spin_lock(&mk712_lock);

	status = inb(mk712_io + MK712_STATUS);

	अगर (~status & MK712_CONVERSION_COMPLETE) अणु
		debounce = 1;
		जाओ end;
	पूर्ण

	अगर (~status & MK712_STATUS_TOUCH) अणु
		debounce = 1;
		input_report_key(mk712_dev, BTN_TOUCH, 0);
		जाओ end;
	पूर्ण

	अगर (debounce) अणु
		debounce = 0;
		जाओ end;
	पूर्ण

	input_report_key(mk712_dev, BTN_TOUCH, 1);
	input_report_असल(mk712_dev, ABS_X, last_x);
	input_report_असल(mk712_dev, ABS_Y, last_y);

 end:
	last_x = inw(mk712_io + MK712_X) & 0x0fff;
	last_y = inw(mk712_io + MK712_Y) & 0x0fff;
	input_sync(mk712_dev);
	spin_unlock(&mk712_lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mk712_खोलो(काष्ठा input_dev *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mk712_lock, flags);

	outb(0, mk712_io + MK712_CONTROL); /* Reset */

	outb(MK712_ENABLE_INT | MK712_INT_ON_CONVERSION_COMPLETE |
		MK712_INT_ON_CHANGE_IN_TOUCH_STATUS |
		MK712_ENABLE_PERIODIC_CONVERSIONS |
		MK712_POWERUP, mk712_io + MK712_CONTROL);

	outb(10, mk712_io + MK712_RATE); /* 187 poपूर्णांकs per second */

	spin_unlock_irqrestore(&mk712_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम mk712_बंद(काष्ठा input_dev *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mk712_lock, flags);

	outb(0, mk712_io + MK712_CONTROL);

	spin_unlock_irqrestore(&mk712_lock, flags);
पूर्ण

अटल पूर्णांक __init mk712_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!request_region(mk712_io, 8, "mk712")) अणु
		prपूर्णांकk(KERN_WARNING "mk712: unable to get IO region\n");
		वापस -ENODEV;
	पूर्ण

	outb(0, mk712_io + MK712_CONTROL);

	अगर ((inw(mk712_io + MK712_X) & 0xf000) ||	/* Sanity check */
	    (inw(mk712_io + MK712_Y) & 0xf000) ||
	    (inw(mk712_io + MK712_STATUS) & 0xf333)) अणु
		prपूर्णांकk(KERN_WARNING "mk712: device not present\n");
		err = -ENODEV;
		जाओ fail1;
	पूर्ण

	mk712_dev = input_allocate_device();
	अगर (!mk712_dev) अणु
		prपूर्णांकk(KERN_ERR "mk712: not enough memory\n");
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	mk712_dev->name = "ICS MicroClock MK712 TouchScreen";
	mk712_dev->phys = "isa0260/input0";
	mk712_dev->id.bustype = BUS_ISA;
	mk712_dev->id.venकरोr  = 0x0005;
	mk712_dev->id.product = 0x0001;
	mk712_dev->id.version = 0x0100;

	mk712_dev->खोलो    = mk712_खोलो;
	mk712_dev->बंद   = mk712_बंद;

	mk712_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	mk712_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(mk712_dev, ABS_X, 0, 0xfff, 88, 0);
	input_set_असल_params(mk712_dev, ABS_Y, 0, 0xfff, 88, 0);

	अगर (request_irq(mk712_irq, mk712_पूर्णांकerrupt, 0, "mk712", mk712_dev)) अणु
		prपूर्णांकk(KERN_WARNING "mk712: unable to get IRQ\n");
		err = -EBUSY;
		जाओ fail1;
	पूर्ण

	err = input_रेजिस्टर_device(mk712_dev);
	अगर (err)
		जाओ fail2;

	वापस 0;

 fail2:	मुक्त_irq(mk712_irq, mk712_dev);
 fail1:	input_मुक्त_device(mk712_dev);
	release_region(mk712_io, 8);
	वापस err;
पूर्ण

अटल व्योम __निकास mk712_निकास(व्योम)
अणु
	input_unरेजिस्टर_device(mk712_dev);
	मुक्त_irq(mk712_irq, mk712_dev);
	release_region(mk712_io, 8);
पूर्ण

module_init(mk712_init);
module_निकास(mk712_निकास);
