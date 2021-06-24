<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2000-2001 Vojtech Pavlik
 *
 *  Based on the work of:
 *	Alan Cox	Robin O'Leary
 */

/*
 * IBM PC110 touchpad driver क्रम Linux
 */

/*
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/input.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("IBM PC110 touchpad driver");
MODULE_LICENSE("GPL");

#घोषणा PC110PAD_OFF	0x30
#घोषणा PC110PAD_ON	0x38

अटल पूर्णांक pc110pad_irq = 10;
अटल पूर्णांक pc110pad_io = 0x15e0;

अटल काष्ठा input_dev *pc110pad_dev;
अटल पूर्णांक pc110pad_data[3];
अटल पूर्णांक pc110pad_count;

अटल irqवापस_t pc110pad_पूर्णांकerrupt(पूर्णांक irq, व्योम *ptr)
अणु
	पूर्णांक value     = inb_p(pc110pad_io);
	पूर्णांक handshake = inb_p(pc110pad_io + 2);

	outb(handshake |  1, pc110pad_io + 2);
	udelay(2);
	outb(handshake & ~1, pc110pad_io + 2);
	udelay(2);
	inb_p(0x64);

	pc110pad_data[pc110pad_count++] = value;

	अगर (pc110pad_count < 3)
		वापस IRQ_HANDLED;

	input_report_key(pc110pad_dev, BTN_TOUCH,
		pc110pad_data[0] & 0x01);
	input_report_असल(pc110pad_dev, ABS_X,
		pc110pad_data[1] | ((pc110pad_data[0] << 3) & 0x80) | ((pc110pad_data[0] << 1) & 0x100));
	input_report_असल(pc110pad_dev, ABS_Y,
		pc110pad_data[2] | ((pc110pad_data[0] << 4) & 0x80));
	input_sync(pc110pad_dev);

	pc110pad_count = 0;
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pc110pad_बंद(काष्ठा input_dev *dev)
अणु
	outb(PC110PAD_OFF, pc110pad_io + 2);
पूर्ण

अटल पूर्णांक pc110pad_खोलो(काष्ठा input_dev *dev)
अणु
	pc110pad_पूर्णांकerrupt(0, शून्य);
	pc110pad_पूर्णांकerrupt(0, शून्य);
	pc110pad_पूर्णांकerrupt(0, शून्य);
	outb(PC110PAD_ON, pc110pad_io + 2);
	pc110pad_count = 0;

	वापस 0;
पूर्ण

/*
 * We try to aव्योम enabling the hardware अगर it's not
 * there, but we करोn't know how to test. But we करो know
 * that the PC110 is not a PCI प्रणाली. So अगर we find any
 * PCI devices in the machine, we करोn't have a PC110.
 */
अटल पूर्णांक __init pc110pad_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!no_pci_devices())
		वापस -ENODEV;

	अगर (!request_region(pc110pad_io, 4, "pc110pad")) अणु
		prपूर्णांकk(KERN_ERR "pc110pad: I/O area %#x-%#x in use.\n",
				pc110pad_io, pc110pad_io + 4);
		वापस -EBUSY;
	पूर्ण

	outb(PC110PAD_OFF, pc110pad_io + 2);

	अगर (request_irq(pc110pad_irq, pc110pad_पूर्णांकerrupt, 0, "pc110pad", शून्य)) अणु
		prपूर्णांकk(KERN_ERR "pc110pad: Unable to get irq %d.\n", pc110pad_irq);
		err = -EBUSY;
		जाओ err_release_region;
	पूर्ण

	pc110pad_dev = input_allocate_device();
	अगर (!pc110pad_dev) अणु
		prपूर्णांकk(KERN_ERR "pc110pad: Not enough memory.\n");
		err = -ENOMEM;
		जाओ err_मुक्त_irq;
	पूर्ण

	pc110pad_dev->name = "IBM PC110 TouchPad";
	pc110pad_dev->phys = "isa15e0/input0";
	pc110pad_dev->id.bustype = BUS_ISA;
	pc110pad_dev->id.venकरोr = 0x0003;
	pc110pad_dev->id.product = 0x0001;
	pc110pad_dev->id.version = 0x0100;

	pc110pad_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	pc110pad_dev->असलbit[0] = BIT_MASK(ABS_X) | BIT_MASK(ABS_Y);
	pc110pad_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	input_असल_set_max(pc110pad_dev, ABS_X, 0x1ff);
	input_असल_set_max(pc110pad_dev, ABS_Y, 0x0ff);

	pc110pad_dev->खोलो = pc110pad_खोलो;
	pc110pad_dev->बंद = pc110pad_बंद;

	err = input_रेजिस्टर_device(pc110pad_dev);
	अगर (err)
		जाओ err_मुक्त_dev;

	वापस 0;

 err_मुक्त_dev:
	input_मुक्त_device(pc110pad_dev);
 err_मुक्त_irq:
	मुक्त_irq(pc110pad_irq, शून्य);
 err_release_region:
	release_region(pc110pad_io, 4);

	वापस err;
पूर्ण

अटल व्योम __निकास pc110pad_निकास(व्योम)
अणु
	outb(PC110PAD_OFF, pc110pad_io + 2);
	मुक्त_irq(pc110pad_irq, शून्य);
	input_unरेजिस्टर_device(pc110pad_dev);
	release_region(pc110pad_io, 4);
पूर्ण

module_init(pc110pad_init);
module_निकास(pc110pad_निकास);
