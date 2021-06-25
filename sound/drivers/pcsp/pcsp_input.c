<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PC Speaker beeper driver क्रम Linux
 *
 *  Copyright (c) 2002 Vojtech Pavlik
 *  Copyright (c) 1992 Orest Zborowski
 */


#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पन.स>
#समावेश "pcsp.h"
#समावेश "pcsp_input.h"

अटल व्योम pcspkr_करो_sound(अचिन्हित पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;

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
पूर्ण

व्योम pcspkr_stop_sound(व्योम)
अणु
	pcspkr_करो_sound(0);
पूर्ण

अटल पूर्णांक pcspkr_input_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
			      अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक count = 0;

	अगर (atomic_पढ़ो(&pcsp_chip.समयr_active) || !pcsp_chip.pcspkr)
		वापस 0;

	चयन (type) अणु
	हाल EV_SND:
		चयन (code) अणु
		हाल SND_BELL:
			अगर (value)
				value = 1000;
			अवरोध;
		हाल SND_TONE:
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण
		अवरोध;

	शेष:
		वापस -1;
	पूर्ण

	अगर (value > 20 && value < 32767)
		count = PIT_TICK_RATE / value;

	pcspkr_करो_sound(count);

	वापस 0;
पूर्ण

पूर्णांक pcspkr_input_init(काष्ठा input_dev **rdev, काष्ठा device *dev)
अणु
	पूर्णांक err;

	काष्ठा input_dev *input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	input_dev->name = "PC Speaker";
	input_dev->phys = "isa0061/input0";
	input_dev->id.bustype = BUS_ISA;
	input_dev->id.venकरोr = 0x001f;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = dev;

	input_dev->evbit[0] = BIT(EV_SND);
	input_dev->sndbit[0] = BIT(SND_BELL) | BIT(SND_TONE);
	input_dev->event = pcspkr_input_event;

	err = input_रेजिस्टर_device(input_dev);
	अगर (err) अणु
		input_मुक्त_device(input_dev);
		वापस err;
	पूर्ण

	*rdev = input_dev;
	वापस 0;
पूर्ण

पूर्णांक pcspkr_input_हटाओ(काष्ठा input_dev *dev)
अणु
	pcspkr_stop_sound();
	input_unरेजिस्टर_device(dev);	/* this also करोes kमुक्त() */

	वापस 0;
पूर्ण
