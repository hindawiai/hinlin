<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Acorn RiscPC mouse driver क्रम Linux/ARM
 *
 *  Copyright (c) 2000-2002 Vojtech Pavlik
 *  Copyright (C) 1996-2002 Russell King
 */

/*
 *
 * This handles the Acorn RiscPCs mouse.  We basically have a couple of
 * hardware रेजिस्टरs that track the sensor count क्रम the X-Y movement and
 * another रेजिस्टर holding the button state.  On every VSYNC पूर्णांकerrupt we पढ़ो
 * the complete state and then work out अगर something has changed.
 */

#समावेश <linux/module.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पन.स>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hardware/iomd.h>

MODULE_AUTHOR("Vojtech Pavlik, Russell King");
MODULE_DESCRIPTION("Acorn RiscPC mouse driver");
MODULE_LICENSE("GPL");

अटल लघु rpcmouse_lastx, rpcmouse_lasty;
अटल काष्ठा input_dev *rpcmouse_dev;

अटल irqवापस_t rpcmouse_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा input_dev *dev = dev_id;
	लघु x, y, dx, dy, b;

	x = (लघु) iomd_पढ़ोl(IOMD_MOUSEX);
	y = (लघु) iomd_पढ़ोl(IOMD_MOUSEY);
	b = (लघु) (__raw_पढ़ोl(IOMEM(0xe0310000)) ^ 0x70);

	dx = x - rpcmouse_lastx;
	dy = y - rpcmouse_lasty;

	rpcmouse_lastx = x;
	rpcmouse_lasty = y;

	input_report_rel(dev, REL_X, dx);
	input_report_rel(dev, REL_Y, -dy);

	input_report_key(dev, BTN_LEFT,   b & 0x40);
	input_report_key(dev, BTN_MIDDLE, b & 0x20);
	input_report_key(dev, BTN_RIGHT,  b & 0x10);

	input_sync(dev);

	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक __init rpcmouse_init(व्योम)
अणु
	पूर्णांक err;

	rpcmouse_dev = input_allocate_device();
	अगर (!rpcmouse_dev)
		वापस -ENOMEM;

	rpcmouse_dev->name = "Acorn RiscPC Mouse";
	rpcmouse_dev->phys = "rpcmouse/input0";
	rpcmouse_dev->id.bustype = BUS_HOST;
	rpcmouse_dev->id.venकरोr  = 0x0005;
	rpcmouse_dev->id.product = 0x0001;
	rpcmouse_dev->id.version = 0x0100;

	rpcmouse_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
	rpcmouse_dev->keybit[BIT_WORD(BTN_LEFT)] = BIT_MASK(BTN_LEFT) |
		BIT_MASK(BTN_MIDDLE) | BIT_MASK(BTN_RIGHT);
	rpcmouse_dev->relbit[0]	= BIT_MASK(REL_X) | BIT_MASK(REL_Y);

	rpcmouse_lastx = (लघु) iomd_पढ़ोl(IOMD_MOUSEX);
	rpcmouse_lasty = (लघु) iomd_पढ़ोl(IOMD_MOUSEY);

	अगर (request_irq(IRQ_VSYNCPULSE, rpcmouse_irq, IRQF_SHARED, "rpcmouse", rpcmouse_dev)) अणु
		prपूर्णांकk(KERN_ERR "rpcmouse: unable to allocate VSYNC interrupt\n");
		err = -EBUSY;
		जाओ err_मुक्त_dev;
	पूर्ण

	err = input_रेजिस्टर_device(rpcmouse_dev);
	अगर (err)
		जाओ err_मुक्त_irq;

	वापस 0;

 err_मुक्त_irq:
	मुक्त_irq(IRQ_VSYNCPULSE, rpcmouse_dev);
 err_मुक्त_dev:
	input_मुक्त_device(rpcmouse_dev);

	वापस err;
पूर्ण

अटल व्योम __निकास rpcmouse_निकास(व्योम)
अणु
	मुक्त_irq(IRQ_VSYNCPULSE, rpcmouse_dev);
	input_unरेजिस्टर_device(rpcmouse_dev);
पूर्ण

module_init(rpcmouse_init);
module_निकास(rpcmouse_निकास);
