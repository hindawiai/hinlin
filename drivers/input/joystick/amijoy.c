<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1998-2001 Vojtech Pavlik
 */

/*
 * Driver क्रम Amiga joysticks क्रम Linux/m68k
 */

/*
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>

#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Driver for Amiga joysticks");
MODULE_LICENSE("GPL");

अटल पूर्णांक amijoy[2] = अणु 0, 1 पूर्ण;
module_param_array_named(map, amijoy, uपूर्णांक, शून्य, 0);
MODULE_PARM_DESC(map, "Map of attached joysticks in form of <a>,<b> (default is 0,1)");

अटल पूर्णांक amijoy_used;
अटल DEFINE_MUTEX(amijoy_mutex);
अटल काष्ठा input_dev *amijoy_dev[2];
अटल अक्षर *amijoy_phys[2] = अणु "amijoy/input0", "amijoy/input1" पूर्ण;

अटल irqवापस_t amijoy_पूर्णांकerrupt(पूर्णांक irq, व्योम *dummy)
अणु
	पूर्णांक i, data = 0, button = 0;

	क्रम (i = 0; i < 2; i++)
		अगर (amijoy[i]) अणु

			चयन (i) अणु
				हाल 0: data = ~amiga_custom.joy0dat; button = (~ciaa.pra >> 6) & 1; अवरोध;
				हाल 1: data = ~amiga_custom.joy1dat; button = (~ciaa.pra >> 7) & 1; अवरोध;
			पूर्ण

			input_report_key(amijoy_dev[i], BTN_TRIGGER, button);

			input_report_असल(amijoy_dev[i], ABS_X, ((data >> 1) & 1) - ((data >> 9) & 1));
			data = ~(data ^ (data << 1));
			input_report_असल(amijoy_dev[i], ABS_Y, ((data >> 1) & 1) - ((data >> 9) & 1));

			input_sync(amijoy_dev[i]);
		पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक amijoy_खोलो(काष्ठा input_dev *dev)
अणु
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&amijoy_mutex);
	अगर (err)
		वापस err;

	अगर (!amijoy_used && request_irq(IRQ_AMIGA_VERTB, amijoy_पूर्णांकerrupt, 0, "amijoy", amijoy_पूर्णांकerrupt)) अणु
		prपूर्णांकk(KERN_ERR "amijoy.c: Can't allocate irq %d\n", IRQ_AMIGA_VERTB);
		err = -EBUSY;
		जाओ out;
	पूर्ण

	amijoy_used++;
out:
	mutex_unlock(&amijoy_mutex);
	वापस err;
पूर्ण

अटल व्योम amijoy_बंद(काष्ठा input_dev *dev)
अणु
	mutex_lock(&amijoy_mutex);
	अगर (!--amijoy_used)
		मुक्त_irq(IRQ_AMIGA_VERTB, amijoy_पूर्णांकerrupt);
	mutex_unlock(&amijoy_mutex);
पूर्ण

अटल पूर्णांक __init amijoy_init(व्योम)
अणु
	पूर्णांक i, j;
	पूर्णांक err;

	अगर (!MACH_IS_AMIGA)
		वापस -ENODEV;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (!amijoy[i])
			जारी;

		amijoy_dev[i] = input_allocate_device();
		अगर (!amijoy_dev[i]) अणु
			err = -ENOMEM;
			जाओ fail;
		पूर्ण

		अगर (!request_mem_region(CUSTOM_PHYSADDR + 10 + i * 2, 2, "amijoy [Denise]")) अणु
			input_मुक्त_device(amijoy_dev[i]);
			err = -EBUSY;
			जाओ fail;
		पूर्ण

		amijoy_dev[i]->name = "Amiga joystick";
		amijoy_dev[i]->phys = amijoy_phys[i];
		amijoy_dev[i]->id.bustype = BUS_AMIGA;
		amijoy_dev[i]->id.venकरोr = 0x0001;
		amijoy_dev[i]->id.product = 0x0003;
		amijoy_dev[i]->id.version = 0x0100;

		amijoy_dev[i]->खोलो = amijoy_खोलो;
		amijoy_dev[i]->बंद = amijoy_बंद;

		amijoy_dev[i]->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		amijoy_dev[i]->असलbit[0] = BIT_MASK(ABS_X) | BIT_MASK(ABS_Y);
		amijoy_dev[i]->keybit[BIT_WORD(BTN_LEFT)] = BIT_MASK(BTN_LEFT) |
			BIT_MASK(BTN_MIDDLE) | BIT_MASK(BTN_RIGHT);
		क्रम (j = 0; j < 2; j++) अणु
			input_set_असल_params(amijoy_dev[i], ABS_X + j,
					     -1, 1, 0, 0);
		पूर्ण

		err = input_रेजिस्टर_device(amijoy_dev[i]);
		अगर (err) अणु
			input_मुक्त_device(amijoy_dev[i]);
			जाओ fail;
		पूर्ण
	पूर्ण
	वापस 0;

 fail:	जबतक (--i >= 0)
		अगर (amijoy[i]) अणु
			input_unरेजिस्टर_device(amijoy_dev[i]);
			release_mem_region(CUSTOM_PHYSADDR + 10 + i * 2, 2);
		पूर्ण
	वापस err;
पूर्ण

अटल व्योम __निकास amijoy_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++)
		अगर (amijoy[i]) अणु
			input_unरेजिस्टर_device(amijoy_dev[i]);
			release_mem_region(CUSTOM_PHYSADDR + 10 + i * 2, 2);
		पूर्ण
पूर्ण

module_init(amijoy_init);
module_निकास(amijoy_निकास);
