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

#अगर_अघोषित _IA_CSS_BUFQ_H
#घोषणा _IA_CSS_BUFQ_H

#समावेश <type_support.h>
#समावेश "ia_css_bufq_comm.h"
#समावेश "ia_css_buffer.h"
#समावेश "ia_css_err.h"
#घोषणा BUFQ_EVENT_SIZE 4

/**
 * @brief Query the पूर्णांकernal frame ID.
 *
 * @param[in]	key	The query key.
 * @param[out]	val	The query value.
 *
 * @वापस
 *	true, अगर the query succeeds;
 *	false, अगर the query fails.
 */
bool ia_css_query_पूर्णांकernal_queue_id(
    क्रमागत ia_css_buffer_type buf_type,
    अचिन्हित पूर्णांक thपढ़ो_id,
    क्रमागत sh_css_queue_id *val
);

/**
 * @brief  Map buffer type to a पूर्णांकernal queue id.
 *
 * @param[in] thपढ़ो id		Thपढ़ो in which the buffer type has to be mapped or unmapped
 * @param[in] buf_type		buffer type.
 * @param[in] map		boolean flag to specअगरy map or unmap
 * @वापस none
 */
व्योम ia_css_queue_map(
    अचिन्हित पूर्णांक thपढ़ो_id,
    क्रमागत ia_css_buffer_type buf_type,
    bool map
);

/**
 * @brief  Initialize buffer type to a queue id mapping
 * @वापस none
 */
व्योम ia_css_queue_map_init(व्योम);

/**
 * @brief initializes bufq module
 * It create instances of
 * -host to SP buffer queue  which is a list with predefined size,
 *	MxN queues where M is the number thपढ़ोs and N is the number queues per thपढ़ो
 *-SP to host buffer queue , is a list with N queues
 *-host to SP event communication queue
 * -SP to host event communication queue
 * -queue क्रम tagger commands
 * @वापस none
 */
व्योम ia_css_bufq_init(व्योम);

/**
* @brief Enqueues an item पूर्णांकo host to SP buffer queue
 *
 * @param thपढ़ो_index[in]	Thपढ़ो in which the item to be enqueued
 *
 * @param queue_id[in]		Index of the queue in the specअगरied thपढ़ो
 * @param item[in]		Object to enqueue.
 * @वापस	0 or error code upon error.
 *
*/
पूर्णांक ia_css_bufq_enqueue_buffer(
    पूर्णांक thपढ़ो_index,
    पूर्णांक queue_id,
    uपूर्णांक32_t item);

/**
* @brief Dequeues an item from SP to host buffer queue.
 *
 * @param queue_id[in]		Specअगरies  the index of the queue in the list where
 *				the item has to be पढ़ो.
 * @paramitem [out]		Object to be dequeued पूर्णांकo this item.
 * @वापस	0 or error code upon error.
 *
*/
पूर्णांक ia_css_bufq_dequeue_buffer(
    पूर्णांक queue_id,
    uपूर्णांक32_t *item);

/**
* @brief  Enqueue an event item पूर्णांकo host to SP communication event queue.
 *
 * @param[in]	evt_id		      The event ID.
 * @param[in]	evt_payload_0	The event payload.
 * @param[in]	evt_payload_1	The event payload.
 * @param[in]	evt_payload_2	The event payload.
 * @वापस	0 or error code upon error.
 *
*/
पूर्णांक ia_css_bufq_enqueue_psys_event(
    u8 evt_id,
    u8 evt_payload_0,
    u8 evt_payload_1,
    uपूर्णांक8_t evt_payload_2
);

/**
 * @brief   Dequeue an item from  SP to host communication event queue.
 *
 * @param item	Object to be dequeued पूर्णांकo this item.
 * @वापस	0 or error code upon error.
 *
*/
पूर्णांक ia_css_bufq_dequeue_psys_event(
    u8 item[BUFQ_EVENT_SIZE]

);

/**
 * @brief  Enqueue an event item पूर्णांकo host to SP खातापूर्ण event queue.
 *
 * @param[in]	evt_id		      The event ID.
 * @वापस	0 or error code upon error.
 *
 */
पूर्णांक ia_css_bufq_enqueue_isys_event(
    uपूर्णांक8_t evt_id);

/**
* @brief   Dequeue an item from  SP to host communication खातापूर्ण event queue.

 *
 * @param item	Object to be dequeued पूर्णांकo this item.
 * @वापस	0 or error code upon error.
 *
 */
पूर्णांक ia_css_bufq_dequeue_isys_event(
    u8 item[BUFQ_EVENT_SIZE]);

/**
* @brief   Enqueue a tagger command item पूर्णांकo tagger command queue..
 *
 * @param item	Object to be enqueue.
 * @वापस	0 or error code upon error.
 *
*/
पूर्णांक ia_css_bufq_enqueue_tag_cmd(
    uपूर्णांक32_t item);

/**
* @brief  Uninitializes bufq module.
 *
 * @वापस	0 or error code upon error.
 *
*/
पूर्णांक ia_css_bufq_deinit(व्योम);

/**
* @brief  Dump queue states
 *
 * @वापस	None
 *
*/
व्योम ia_css_bufq_dump_queue_info(व्योम);

#पूर्ण_अगर	/* _IA_CSS_BUFQ_H */
