<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
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

#अगर_अघोषित _IA_CSS_EVENTQ_H
#घोषणा _IA_CSS_EVENTQ_H

#समावेश "ia_css_queue.h"	/* queue APIs */

/**
 * @brief HOST receives event from SP.
 *
 * @param[in]	eventq_handle	eventq_handle.
 * @param[in]	payload		The event payload.
 * @वापस	0		- Successfully dequeue.
 * @वापस	-EINVAL		- Invalid argument.
 * @वापस	-ENODATA		- Queue is empty.
 */
पूर्णांक ia_css_eventq_recv(
    ia_css_queue_t *eventq_handle,
    uपूर्णांक8_t *payload);

/**
 * @brief The Host sends the event to SP.
 * The caller of this API will be blocked until the event
 * is sent.
 *
 * @param[in]	eventq_handle   eventq_handle.
 * @param[in]	evt_id		The event ID.
 * @param[in]	evt_payload_0	The event payload.
 * @param[in]	evt_payload_1	The event payload.
 * @param[in]	evt_payload_2	The event payload.
 * @वापस	0		- Successfully enqueue.
 * @वापस	-EINVAL		- Invalid argument.
 * @वापस	-ENOBUFS		- Queue is full.
 */
पूर्णांक ia_css_eventq_send(
    ia_css_queue_t *eventq_handle,
    u8 evt_id,
    u8 evt_payload_0,
    u8 evt_payload_1,
    uपूर्णांक8_t evt_payload_2);
#पूर्ण_अगर /* _IA_CSS_EVENTQ_H */
