<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* fakekey.c
 * Functions क्रम simulating keypresses.
 *
 * Copyright (C) 2010 the Speakup Team
 */
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/preempt.h>
#समावेश <linux/percpu.h>
#समावेश <linux/input.h>

#समावेश "speakup.h"

#घोषणा PRESSED 1
#घोषणा RELEASED 0

अटल DEFINE_PER_CPU(पूर्णांक, reporting_keystroke);

अटल काष्ठा input_dev *virt_keyboard;

पूर्णांक speakup_add_भव_keyboard(व्योम)
अणु
	पूर्णांक err;

	virt_keyboard = input_allocate_device();

	अगर (!virt_keyboard)
		वापस -ENOMEM;

	virt_keyboard->name = "Speakup";
	virt_keyboard->id.bustype = BUS_VIRTUAL;
	virt_keyboard->phys = "speakup/input0";
	virt_keyboard->dev.parent = शून्य;

	__set_bit(EV_KEY, virt_keyboard->evbit);
	__set_bit(KEY_DOWN, virt_keyboard->keybit);

	err = input_रेजिस्टर_device(virt_keyboard);
	अगर (err) अणु
		input_मुक्त_device(virt_keyboard);
		virt_keyboard = शून्य;
	पूर्ण

	वापस err;
पूर्ण

व्योम speakup_हटाओ_भव_keyboard(व्योम)
अणु
	अगर (virt_keyboard) अणु
		input_unरेजिस्टर_device(virt_keyboard);
		virt_keyboard = शून्य;
	पूर्ण
पूर्ण

/*
 * Send a simulated करोwn-arrow to the application.
 */
व्योम speakup_fake_करोwn_arrow(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	/* disable keyboard पूर्णांकerrupts */
	local_irq_save(flags);
	/* करोn't change CPU */
	preempt_disable();

	__this_cpu_ग_लिखो(reporting_keystroke, true);
	input_report_key(virt_keyboard, KEY_DOWN, PRESSED);
	input_report_key(virt_keyboard, KEY_DOWN, RELEASED);
	input_sync(virt_keyboard);
	__this_cpu_ग_लिखो(reporting_keystroke, false);

	/* reenable preemption */
	preempt_enable();
	/* reenable keyboard पूर्णांकerrupts */
	local_irq_restore(flags);
पूर्ण

/*
 * Are we handling a simulated keypress on the current CPU?
 * Returns a boolean.
 */
bool speakup_fake_key_pressed(व्योम)
अणु
	वापस this_cpu_पढ़ो(reporting_keystroke);
पूर्ण
