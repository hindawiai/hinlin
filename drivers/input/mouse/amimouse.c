<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Amiga mouse driver क्रम Linux/m68k
 *
 *  Copyright (c) 2000-2002 Vojtech Pavlik
 *
 *  Based on the work of:
 *	Michael Rausch		James Banks
 *	Matther Dillon		David Giller
 *	Nathan Lareकरो		Linus Torvalds
 *	Johan Myreen		Jes Sorensen
 *	Russell King
 */


#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/setup.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Amiga mouse driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक amimouse_lastx, amimouse_lasty;

अटल irqवापस_t amimouse_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा input_dev *dev = data;
	अचिन्हित लघु joy0dat, potgor;
	पूर्णांक nx, ny, dx, dy;

	joy0dat = amiga_custom.joy0dat;

	nx = joy0dat & 0xff;
	ny = joy0dat >> 8;

	dx = nx - amimouse_lastx;
	dy = ny - amimouse_lasty;

	अगर (dx < -127) dx = (256 + nx) - amimouse_lastx;
	अगर (dx >  127) dx = (nx - 256) - amimouse_lastx;
	अगर (dy < -127) dy = (256 + ny) - amimouse_lasty;
	अगर (dy >  127) dy = (ny - 256) - amimouse_lasty;

	amimouse_lastx = nx;
	amimouse_lasty = ny;

	potgor = amiga_custom.potgor;

	input_report_rel(dev, REL_X, dx);
	input_report_rel(dev, REL_Y, dy);

	input_report_key(dev, BTN_LEFT,   ciaa.pra & 0x40);
	input_report_key(dev, BTN_MIDDLE, potgor & 0x0100);
	input_report_key(dev, BTN_RIGHT,  potgor & 0x0400);

	input_sync(dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक amimouse_खोलो(काष्ठा input_dev *dev)
अणु
	अचिन्हित लघु joy0dat;
	पूर्णांक error;

	joy0dat = amiga_custom.joy0dat;

	amimouse_lastx = joy0dat & 0xff;
	amimouse_lasty = joy0dat >> 8;

	error = request_irq(IRQ_AMIGA_VERTB, amimouse_पूर्णांकerrupt, 0, "amimouse",
			    dev);
	अगर (error)
		dev_err(&dev->dev, "Can't allocate irq %d\n", IRQ_AMIGA_VERTB);

	वापस error;
पूर्ण

अटल व्योम amimouse_बंद(काष्ठा input_dev *dev)
अणु
	मुक्त_irq(IRQ_AMIGA_VERTB, dev);
पूर्ण

अटल पूर्णांक __init amimouse_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	काष्ठा input_dev *dev;

	dev = input_allocate_device();
	अगर (!dev)
		वापस -ENOMEM;

	dev->name = pdev->name;
	dev->phys = "amimouse/input0";
	dev->id.bustype = BUS_AMIGA;
	dev->id.venकरोr = 0x0001;
	dev->id.product = 0x0002;
	dev->id.version = 0x0100;

	dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
	dev->relbit[0] = BIT_MASK(REL_X) | BIT_MASK(REL_Y);
	dev->keybit[BIT_WORD(BTN_LEFT)] = BIT_MASK(BTN_LEFT) |
		BIT_MASK(BTN_MIDDLE) | BIT_MASK(BTN_RIGHT);
	dev->खोलो = amimouse_खोलो;
	dev->बंद = amimouse_बंद;
	dev->dev.parent = &pdev->dev;

	err = input_रेजिस्टर_device(dev);
	अगर (err) अणु
		input_मुक्त_device(dev);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __निकास amimouse_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *dev = platक्रमm_get_drvdata(pdev);

	input_unरेजिस्टर_device(dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver amimouse_driver = अणु
	.हटाओ = __निकास_p(amimouse_हटाओ),
	.driver   = अणु
		.name	= "amiga-mouse",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(amimouse_driver, amimouse_probe);

MODULE_ALIAS("platform:amiga-mouse");
