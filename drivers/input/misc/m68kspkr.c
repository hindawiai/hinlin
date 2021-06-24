<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  m68k beeper driver क्रम Linux
 *
 *  Copyright (c) 2002 Riअक्षरd Zidlicky
 *  Copyright (c) 2002 Vojtech Pavlik
 *  Copyright (c) 1992 Orest Zborowski
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>

MODULE_AUTHOR("Richard Zidlicky <rz@linux-m68k.org>");
MODULE_DESCRIPTION("m68k beeper driver");
MODULE_LICENSE("GPL");

अटल काष्ठा platक्रमm_device *m68kspkr_platक्रमm_device;

अटल पूर्णांक m68kspkr_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक count = 0;

	अगर (type != EV_SND)
		वापस -1;

	चयन (code) अणु
		हाल SND_BELL: अगर (value) value = 1000;
		हाल SND_TONE: अवरोध;
		शेष: वापस -1;
	पूर्ण

	अगर (value > 20 && value < 32767)
		count = 1193182 / value;

	mach_beep(count, -1);

	वापस 0;
पूर्ण

अटल पूर्णांक m68kspkr_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	input_dev->name = "m68k beeper";
	input_dev->phys = "m68k/generic";
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.venकरोr  = 0x001f;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &dev->dev;

	input_dev->evbit[0] = BIT_MASK(EV_SND);
	input_dev->sndbit[0] = BIT_MASK(SND_BELL) | BIT_MASK(SND_TONE);
	input_dev->event = m68kspkr_event;

	err = input_रेजिस्टर_device(input_dev);
	अगर (err) अणु
		input_मुक्त_device(input_dev);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(dev, input_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक m68kspkr_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा input_dev *input_dev = platक्रमm_get_drvdata(dev);

	input_unरेजिस्टर_device(input_dev);
	/* turn off the speaker */
	m68kspkr_event(शून्य, EV_SND, SND_BELL, 0);

	वापस 0;
पूर्ण

अटल व्योम m68kspkr_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	/* turn off the speaker */
	m68kspkr_event(शून्य, EV_SND, SND_BELL, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver m68kspkr_platक्रमm_driver = अणु
	.driver		= अणु
		.name	= "m68kspkr",
	पूर्ण,
	.probe		= m68kspkr_probe,
	.हटाओ		= m68kspkr_हटाओ,
	.shutकरोwn	= m68kspkr_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init m68kspkr_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!mach_beep) अणु
		prपूर्णांकk(KERN_INFO "m68kspkr: no lowlevel beep support\n");
		वापस -ENODEV;
        पूर्ण

	err = platक्रमm_driver_रेजिस्टर(&m68kspkr_platक्रमm_driver);
	अगर (err)
		वापस err;

	m68kspkr_platक्रमm_device = platक्रमm_device_alloc("m68kspkr", -1);
	अगर (!m68kspkr_platक्रमm_device) अणु
		err = -ENOMEM;
		जाओ err_unरेजिस्टर_driver;
	पूर्ण

	err = platक्रमm_device_add(m68kspkr_platक्रमm_device);
	अगर (err)
		जाओ err_मुक्त_device;

	वापस 0;

 err_मुक्त_device:
	platक्रमm_device_put(m68kspkr_platक्रमm_device);
 err_unरेजिस्टर_driver:
	platक्रमm_driver_unरेजिस्टर(&m68kspkr_platक्रमm_driver);

	वापस err;
पूर्ण

अटल व्योम __निकास m68kspkr_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(m68kspkr_platक्रमm_device);
	platक्रमm_driver_unरेजिस्टर(&m68kspkr_platक्रमm_driver);
पूर्ण

module_init(m68kspkr_init);
module_निकास(m68kspkr_निकास);
