<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 * IBM ASM Service Processor Device Driver
 *
 * Copyright (C) IBM Corporation, 2004
 *
 * Author: Max Asbथघck <amax@us.ibm.com>
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश "ibmasm.h"
#समावेश "lowlevel.h"

/*
 * ASM service processor event handling routines.
 *
 * Events are संकेतled to the device drivers through पूर्णांकerrupts.
 * They have the क्रमmat of करोt commands, with the type field set to
 * sp_event.
 * The driver करोes not पूर्णांकerpret the events, it simply stores them in a
 * circular buffer.
 */

अटल व्योम wake_up_event_पढ़ोers(काष्ठा service_processor *sp)
अणु
	काष्ठा event_पढ़ोer *पढ़ोer;

	list_क्रम_each_entry(पढ़ोer, &sp->event_buffer->पढ़ोers, node)
                wake_up_पूर्णांकerruptible(&पढ़ोer->रुको);
पूर्ण

/*
 * receive_event
 * Called by the पूर्णांकerrupt handler when a करोt command of type sp_event is
 * received.
 * Store the event in the circular event buffer, wake up any sleeping
 * event पढ़ोers.
 * There is no पढ़ोer marker in the buffer, thereक्रमe पढ़ोers are
 * responsible क्रम keeping up with the ग_लिखोr, or they will lose events.
 */
व्योम ibmयंत्र_receive_event(काष्ठा service_processor *sp, व्योम *data, अचिन्हित पूर्णांक data_size)
अणु
	काष्ठा event_buffer *buffer = sp->event_buffer;
	काष्ठा ibmयंत्र_event *event;
	अचिन्हित दीर्घ flags;

	data_size = min(data_size, IBMASM_EVENT_MAX_SIZE);

	spin_lock_irqsave(&sp->lock, flags);
	/* copy the event पूर्णांकo the next slot in the circular buffer */
	event = &buffer->events[buffer->next_index];
	स_नकल_fromio(event->data, data, data_size);
	event->data_size = data_size;
	event->serial_number = buffer->next_serial_number;

	/* advance indices in the buffer */
	buffer->next_index = (buffer->next_index + 1) % IBMASM_NUM_EVENTS;
	buffer->next_serial_number++;
	spin_unlock_irqrestore(&sp->lock, flags);

	wake_up_event_पढ़ोers(sp);
पूर्ण

अटल अंतरभूत पूर्णांक event_available(काष्ठा event_buffer *b, काष्ठा event_पढ़ोer *r)
अणु
	वापस (r->next_serial_number < b->next_serial_number);
पूर्ण

/*
 * get_next_event
 * Called by event पढ़ोers (initiated from user space through the file
 * प्रणाली).
 * Sleeps until a new event is available.
 */
पूर्णांक ibmयंत्र_get_next_event(काष्ठा service_processor *sp, काष्ठा event_पढ़ोer *पढ़ोer)
अणु
	काष्ठा event_buffer *buffer = sp->event_buffer;
	काष्ठा ibmयंत्र_event *event;
	अचिन्हित पूर्णांक index;
	अचिन्हित दीर्घ flags;

	पढ़ोer->cancelled = 0;

	अगर (रुको_event_पूर्णांकerruptible(पढ़ोer->रुको,
			event_available(buffer, पढ़ोer) || पढ़ोer->cancelled))
		वापस -ERESTARTSYS;

	अगर (!event_available(buffer, पढ़ोer))
		वापस 0;

	spin_lock_irqsave(&sp->lock, flags);

	index = buffer->next_index;
	event = &buffer->events[index];
	जबतक (event->serial_number < पढ़ोer->next_serial_number) अणु
		index = (index + 1) % IBMASM_NUM_EVENTS;
		event = &buffer->events[index];
	पूर्ण
	स_नकल(पढ़ोer->data, event->data, event->data_size);
	पढ़ोer->data_size = event->data_size;
	पढ़ोer->next_serial_number = event->serial_number + 1;

	spin_unlock_irqrestore(&sp->lock, flags);

	वापस event->data_size;
पूर्ण

व्योम ibmयंत्र_cancel_next_event(काष्ठा event_पढ़ोer *पढ़ोer)
अणु
        पढ़ोer->cancelled = 1;
        wake_up_पूर्णांकerruptible(&पढ़ोer->रुको);
पूर्ण

व्योम ibmयंत्र_event_पढ़ोer_रेजिस्टर(काष्ठा service_processor *sp, काष्ठा event_पढ़ोer *पढ़ोer)
अणु
	अचिन्हित दीर्घ flags;

	पढ़ोer->next_serial_number = sp->event_buffer->next_serial_number;
	init_रुकोqueue_head(&पढ़ोer->रुको);
	spin_lock_irqsave(&sp->lock, flags);
	list_add(&पढ़ोer->node, &sp->event_buffer->पढ़ोers);
	spin_unlock_irqrestore(&sp->lock, flags);
पूर्ण

व्योम ibmयंत्र_event_पढ़ोer_unरेजिस्टर(काष्ठा service_processor *sp, काष्ठा event_पढ़ोer *पढ़ोer)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sp->lock, flags);
	list_del(&पढ़ोer->node);
	spin_unlock_irqrestore(&sp->lock, flags);
पूर्ण

पूर्णांक ibmयंत्र_event_buffer_init(काष्ठा service_processor *sp)
अणु
	काष्ठा event_buffer *buffer;
	काष्ठा ibmयंत्र_event *event;
	पूर्णांक i;

	buffer = kदो_स्मृति(माप(काष्ठा event_buffer), GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	buffer->next_index = 0;
	buffer->next_serial_number = 1;

	event = buffer->events;
	क्रम (i=0; i<IBMASM_NUM_EVENTS; i++, event++)
		event->serial_number = 0;

	INIT_LIST_HEAD(&buffer->पढ़ोers);

	sp->event_buffer = buffer;

	वापस 0;
पूर्ण

व्योम ibmयंत्र_event_buffer_निकास(काष्ठा service_processor *sp)
अणु
	kमुक्त(sp->event_buffer);
पूर्ण
