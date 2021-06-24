<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __EVENT_FIFO_PUBLIC_H
#घोषणा __EVENT_FIFO_PUBLIC_H

#समावेश <type_support.h>
#समावेश "system_local.h"

/*! Blocking पढ़ो from an event source EVENT[ID]

 \param	ID[in]				EVENT identअगरier

 \लeturn none, dequeue(event_queue[ID])
 */
STORAGE_CLASS_EVENT_H व्योम event_रुको_क्रम(
    स्थिर event_ID_t		ID);

/*! Conditional blocking रुको क्रम an event source EVENT[ID]

 \param	ID[in]				EVENT identअगरier
 \param	cnd[in]				predicate

 \लeturn none, अगर(cnd) dequeue(event_queue[ID])
 */
STORAGE_CLASS_EVENT_H व्योम cnd_event_रुको_क्रम(
    स्थिर event_ID_t		ID,
    स्थिर bool				cnd);

/*! Blocking पढ़ो from an event source EVENT[ID]

 \param	ID[in]				EVENT identअगरier

 \लeturn dequeue(event_queue[ID])
 */
STORAGE_CLASS_EVENT_H hrt_data event_receive_token(
    स्थिर event_ID_t		ID);

/*! Blocking ग_लिखो to an event sink EVENT[ID]

 \param	ID[in]				EVENT identअगरier
 \param	token[in]			token to be written on the event

 \लeturn none, enqueue(event_queue[ID])
 */
STORAGE_CLASS_EVENT_H व्योम event_send_token(
    स्थिर event_ID_t		ID,
    स्थिर hrt_data			token);

/*! Query an event source EVENT[ID]

 \param	ID[in]				EVENT identअगरier

 \लeturn !isempty(event_queue[ID])
 */
STORAGE_CLASS_EVENT_H bool is_event_pending(
    स्थिर event_ID_t		ID);

/*! Query an event sink EVENT[ID]

 \param	ID[in]				EVENT identअगरier

 \लeturn !isfull(event_queue[ID])
 */
STORAGE_CLASS_EVENT_H bool can_event_send_token(
    स्थिर event_ID_t		ID);

#पूर्ण_अगर /* __EVENT_FIFO_PUBLIC_H */
