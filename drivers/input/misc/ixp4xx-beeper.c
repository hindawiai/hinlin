<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic IXP4xx beeper driver
 *
 * Copyright (C) 2005 Tower Technologies
 *
 * based on nslu2-io.c
 *  Copyright (C) 2004 Karen Spearel
 *
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 * Maपूर्णांकainers: http://www.nslu2-linux.org/
 */

#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpपन.स>
#समावेश <mach/hardware.h>

MODULE_AUTHOR("Alessandro Zummo <a.zummo@towertech.it>");
MODULE_DESCRIPTION("ixp4xx beeper driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ixp4xx-beeper");

अटल DEFINE_SPINLOCK(beep_lock);

अटल पूर्णांक ixp4xx_समयr2_irq;

अटल व्योम ixp4xx_spkr_control(अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&beep_lock, flags);

	अगर (count) अणु
		gpio_direction_output(pin, 0);
		*IXP4XX_OSRT2 = (count & ~IXP4XX_OST_RELOAD_MASK) | IXP4XX_OST_ENABLE;
	पूर्ण अन्यथा अणु
		gpio_direction_output(pin, 1);
		gpio_direction_input(pin);
		*IXP4XX_OSRT2 = 0;
	पूर्ण

	spin_unlock_irqrestore(&beep_lock, flags);
पूर्ण

अटल पूर्णांक ixp4xx_spkr_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक pin = (अचिन्हित पूर्णांक) input_get_drvdata(dev);
	अचिन्हित पूर्णांक count = 0;

	अगर (type != EV_SND)
		वापस -1;

	चयन (code) अणु
		हाल SND_BELL:
			अगर (value)
				value = 1000;
		हाल SND_TONE:
			अवरोध;
		शेष:
			वापस -1;
	पूर्ण

	अगर (value > 20 && value < 32767)
		count = (ixp4xx_समयr_freq / (value * 4)) - 1;

	ixp4xx_spkr_control(pin, count);

	वापस 0;
पूर्ण

अटल irqवापस_t ixp4xx_spkr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक pin = (अचिन्हित पूर्णांक) dev_id;

	/* clear पूर्णांकerrupt */
	*IXP4XX_OSST = IXP4XX_OSST_TIMER_2_PEND;

	/* flip the beeper output */
	gpio_set_value(pin, !gpio_get_value(pin));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ixp4xx_spkr_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा input_dev *input_dev;
	पूर्णांक irq;
	पूर्णांक err;

	input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	input_set_drvdata(input_dev, (व्योम *) dev->id);

	input_dev->name = "ixp4xx beeper";
	input_dev->phys = "ixp4xx/gpio";
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.venकरोr  = 0x001f;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &dev->dev;

	input_dev->evbit[0] = BIT_MASK(EV_SND);
	input_dev->sndbit[0] = BIT_MASK(SND_BELL) | BIT_MASK(SND_TONE);
	input_dev->event = ixp4xx_spkr_event;

	irq = platक्रमm_get_irq(dev, 0);
	अगर (irq < 0) अणु
		err = irq;
		जाओ err_मुक्त_device;
	पूर्ण

	err = gpio_request(dev->id, "ixp4-beeper");
	अगर (err)
		जाओ err_मुक्त_device;

	err = request_irq(irq, &ixp4xx_spkr_पूर्णांकerrupt,
			  IRQF_NO_SUSPEND, "ixp4xx-beeper",
			  (व्योम *) dev->id);
	अगर (err)
		जाओ err_मुक्त_gpio;
	ixp4xx_समयr2_irq = irq;

	err = input_रेजिस्टर_device(input_dev);
	अगर (err)
		जाओ err_मुक्त_irq;

	platक्रमm_set_drvdata(dev, input_dev);

	वापस 0;

 err_मुक्त_irq:
	मुक्त_irq(irq, (व्योम *)dev->id);
 err_मुक्त_gpio:
	gpio_मुक्त(dev->id);
 err_मुक्त_device:
	input_मुक्त_device(input_dev);

	वापस err;
पूर्ण

अटल पूर्णांक ixp4xx_spkr_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा input_dev *input_dev = platक्रमm_get_drvdata(dev);
	अचिन्हित पूर्णांक pin = (अचिन्हित पूर्णांक) input_get_drvdata(input_dev);

	input_unरेजिस्टर_device(input_dev);

	/* turn the speaker off */
	disable_irq(ixp4xx_समयr2_irq);
	ixp4xx_spkr_control(pin, 0);

	मुक्त_irq(ixp4xx_समयr2_irq, (व्योम *)dev->id);
	gpio_मुक्त(dev->id);

	वापस 0;
पूर्ण

अटल व्योम ixp4xx_spkr_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा input_dev *input_dev = platक्रमm_get_drvdata(dev);
	अचिन्हित पूर्णांक pin = (अचिन्हित पूर्णांक) input_get_drvdata(input_dev);

	/* turn off the speaker */
	disable_irq(ixp4xx_समयr2_irq);
	ixp4xx_spkr_control(pin, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver ixp4xx_spkr_platक्रमm_driver = अणु
	.driver		= अणु
		.name	= "ixp4xx-beeper",
	पूर्ण,
	.probe		= ixp4xx_spkr_probe,
	.हटाओ		= ixp4xx_spkr_हटाओ,
	.shutकरोwn	= ixp4xx_spkr_shutकरोwn,
पूर्ण;
module_platक्रमm_driver(ixp4xx_spkr_platक्रमm_driver);

