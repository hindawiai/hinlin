<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PC Speaker beeper driver क्रम Linux
 *
 *  Copyright (c) 2002 Vojtech Pavlik
 *  Copyright (c) 1992 Orest Zborowski
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i8253.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/समयx.h>
#समावेश <linux/पन.स>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("PC Speaker beeper driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pcspkr");

अटल पूर्णांक pcspkr_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
			अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित दीर्घ flags;

	अगर (type != EV_SND)
		वापस -EINVAL;

	चयन (code) अणु
	हाल SND_BELL:
		अगर (value)
			value = 1000;
		अवरोध;
	हाल SND_TONE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (value > 20 && value < 32767)
		count = PIT_TICK_RATE / value;

	raw_spin_lock_irqsave(&i8253_lock, flags);

	अगर (count) अणु
		/* set command क्रम counter 2, 2 byte ग_लिखो */
		outb_p(0xB6, 0x43);
		/* select desired HZ */
		outb_p(count & 0xff, 0x42);
		outb((count >> 8) & 0xff, 0x42);
		/* enable counter 2 */
		outb_p(inb_p(0x61) | 3, 0x61);
	पूर्ण अन्यथा अणु
		/* disable counter 2 */
		outb(inb_p(0x61) & 0xFC, 0x61);
	पूर्ण

	raw_spin_unlock_irqrestore(&i8253_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pcspkr_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा input_dev *pcspkr_dev;
	पूर्णांक err;

	pcspkr_dev = input_allocate_device();
	अगर (!pcspkr_dev)
		वापस -ENOMEM;

	pcspkr_dev->name = "PC Speaker";
	pcspkr_dev->phys = "isa0061/input0";
	pcspkr_dev->id.bustype = BUS_ISA;
	pcspkr_dev->id.venकरोr = 0x001f;
	pcspkr_dev->id.product = 0x0001;
	pcspkr_dev->id.version = 0x0100;
	pcspkr_dev->dev.parent = &dev->dev;

	pcspkr_dev->evbit[0] = BIT_MASK(EV_SND);
	pcspkr_dev->sndbit[0] = BIT_MASK(SND_BELL) | BIT_MASK(SND_TONE);
	pcspkr_dev->event = pcspkr_event;

	err = input_रेजिस्टर_device(pcspkr_dev);
	अगर (err) अणु
		input_मुक्त_device(pcspkr_dev);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(dev, pcspkr_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pcspkr_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा input_dev *pcspkr_dev = platक्रमm_get_drvdata(dev);

	input_unरेजिस्टर_device(pcspkr_dev);
	/* turn off the speaker */
	pcspkr_event(शून्य, EV_SND, SND_BELL, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक pcspkr_suspend(काष्ठा device *dev)
अणु
	pcspkr_event(शून्य, EV_SND, SND_BELL, 0);

	वापस 0;
पूर्ण

अटल व्योम pcspkr_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	/* turn off the speaker */
	pcspkr_event(शून्य, EV_SND, SND_BELL, 0);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pcspkr_pm_ops = अणु
	.suspend = pcspkr_suspend,
पूर्ण;

अटल काष्ठा platक्रमm_driver pcspkr_platक्रमm_driver = अणु
	.driver		= अणु
		.name	= "pcspkr",
		.pm	= &pcspkr_pm_ops,
	पूर्ण,
	.probe		= pcspkr_probe,
	.हटाओ		= pcspkr_हटाओ,
	.shutकरोwn	= pcspkr_shutकरोwn,
पूर्ण;
module_platक्रमm_driver(pcspkr_platक्रमm_driver);

