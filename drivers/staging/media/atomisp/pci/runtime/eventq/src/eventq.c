<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश "ia_css_types.h"
#समावेश "assert_support.h"
#समावेश "ia_css_queue.h" /* sp2host_dequeue_irq_event() */
#समावेश "ia_css_eventq.h"
#समावेश "ia_css_event.h"	/* ia_css_event_encode()
				ia_css_event_decode()
				*/
पूर्णांक ia_css_eventq_recv(
    ia_css_queue_t *eventq_handle,
    uपूर्णांक8_t *payload)
अणु
	u32 sp_event;
	पूर्णांक error;

	/* dequeue the IRQ event */
	error = ia_css_queue_dequeue(eventq_handle, &sp_event);

	/* check whether the IRQ event is available or not */
	अगर (!error)
		ia_css_event_decode(sp_event, payload);
	वापस error;
पूर्ण

/*
 * @brief The Host sends the event to the SP.
 * Refer to "sh_css_sp.h" क्रम details.
 */
पूर्णांक ia_css_eventq_send(
    ia_css_queue_t *eventq_handle,
    u8 evt_id,
    u8 evt_payload_0,
    u8 evt_payload_1,
    uपूर्णांक8_t evt_payload_2)
अणु
	u8 पंचांगp[4];
	u32 sw_event;
	पूर्णांक error = -ENOSYS;

	/*
	 * Encode the queue type, the thपढ़ो ID and
	 * the queue ID पूर्णांकo the event.
	 */
	पंचांगp[0] = evt_id;
	पंचांगp[1] = evt_payload_0;
	पंचांगp[2] = evt_payload_1;
	पंचांगp[3] = evt_payload_2;
	ia_css_event_encode(पंचांगp, 4, &sw_event);

	/* queue the software event (busy-रुकोing) */
	क्रम ( ; ; ) अणु
		error = ia_css_queue_enqueue(eventq_handle, sw_event);
		अगर (error != -ENOBUFS) अणु
			/* We were able to successfully send the event
			   or had a real failure. वापस the status*/
			अवरोध;
		पूर्ण
		/* Wait क्रम the queue to be not full and try again*/
		udelay(1);
	पूर्ण
	वापस error;
पूर्ण
