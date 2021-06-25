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

#समावेश "assert_support.h"		/* निश्चित */
#समावेश "ia_css_buffer.h"
#समावेश "sp.h"
#समावेश "ia_css_bufq.h"		/* Bufq API's */
#समावेश "ia_css_queue.h"		/* ia_css_queue_t */
#समावेश "sw_event_global.h"		/* Event IDs.*/
#समावेश "ia_css_eventq.h"		/* ia_css_eventq_recv()*/
#समावेश "ia_css_debug.h"		/* ia_css_debug_dtrace*/
#समावेश "sh_css_internal.h"		/* sh_css_queue_type */
#समावेश "sp_local.h"			/* sp_address_of */
#समावेश "sh_css_firmware.h"		/* sh_css_sp_fw*/

#घोषणा BUFQ_DUMP_खाता_NAME_PREFIX_SIZE 256

अटल अक्षर prefix[BUFQ_DUMP_खाता_NAME_PREFIX_SIZE] = अणु0पूर्ण;

/*********************************************************/
/* Global Queue objects used by CSS                      */
/*********************************************************/

काष्ठा sh_css_queues अणु
	/* Host2SP buffer queue */
	ia_css_queue_t host2sp_buffer_queue_handles
	[SH_CSS_MAX_SP_THREADS][SH_CSS_MAX_NUM_QUEUES];
	/* SP2Host buffer queue */
	ia_css_queue_t sp2host_buffer_queue_handles
	[SH_CSS_MAX_NUM_QUEUES];

	/* Host2SP event queue */
	ia_css_queue_t host2sp_psys_event_queue_handle;

	/* SP2Host event queue */
	ia_css_queue_t sp2host_psys_event_queue_handle;

	/* Host2SP ISYS event queue */
	ia_css_queue_t host2sp_isys_event_queue_handle;

	/* SP2Host ISYS event queue */
	ia_css_queue_t sp2host_isys_event_queue_handle;
	/* Tagger command queue */
	ia_css_queue_t host2sp_tag_cmd_queue_handle;
पूर्ण;

/*******************************************************
*** Static variables
********************************************************/
अटल काष्ठा sh_css_queues css_queues;

अटल पूर्णांक
buffer_type_to_queue_id_map[SH_CSS_MAX_SP_THREADS][IA_CSS_NUM_DYNAMIC_BUFFER_TYPE];
अटल bool queue_availability[SH_CSS_MAX_SP_THREADS][SH_CSS_MAX_NUM_QUEUES];

/*******************************************************
*** Static functions
********************************************************/
अटल व्योम map_buffer_type_to_queue_id(
    अचिन्हित पूर्णांक thपढ़ो_id,
    क्रमागत ia_css_buffer_type buf_type
);
अटल व्योम unmap_buffer_type_to_queue_id(
    अचिन्हित पूर्णांक thपढ़ो_id,
    क्रमागत ia_css_buffer_type buf_type
);

अटल ia_css_queue_t *bufq_get_qhandle(
    क्रमागत sh_css_queue_type type,
    क्रमागत sh_css_queue_id id,
    पूर्णांक thपढ़ो
);

/*******************************************************
*** Public functions
********************************************************/
व्योम ia_css_queue_map_init(व्योम)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < SH_CSS_MAX_SP_THREADS; i++) अणु
		क्रम (j = 0; j < SH_CSS_MAX_NUM_QUEUES; j++)
			queue_availability[i][j] = true;
	पूर्ण

	क्रम (i = 0; i < SH_CSS_MAX_SP_THREADS; i++) अणु
		क्रम (j = 0; j < IA_CSS_NUM_DYNAMIC_BUFFER_TYPE; j++)
			buffer_type_to_queue_id_map[i][j] = SH_CSS_INVALID_QUEUE_ID;
	पूर्ण
पूर्ण

व्योम ia_css_queue_map(
    अचिन्हित पूर्णांक thपढ़ो_id,
    क्रमागत ia_css_buffer_type buf_type,
    bool map)
अणु
	निश्चित(buf_type < IA_CSS_NUM_DYNAMIC_BUFFER_TYPE);
	निश्चित(thपढ़ो_id < SH_CSS_MAX_SP_THREADS);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_queue_map() enter: buf_type=%d, thread_id=%d\n", buf_type, thपढ़ो_id);

	अगर (map)
		map_buffer_type_to_queue_id(thपढ़ो_id, buf_type);
	अन्यथा
		unmap_buffer_type_to_queue_id(thपढ़ो_id, buf_type);
पूर्ण

/*
 * @brief Query the पूर्णांकernal queue ID.
 */
bool ia_css_query_पूर्णांकernal_queue_id(
    क्रमागत ia_css_buffer_type buf_type,
    अचिन्हित पूर्णांक thपढ़ो_id,
    क्रमागत sh_css_queue_id *val)
अणु
	IA_CSS_ENTER("buf_type=%d, thread_id=%d, val = %p", buf_type, thपढ़ो_id, val);

	अगर ((!val) || (thपढ़ो_id >= SH_CSS_MAX_SP_THREADS) ||
	    (buf_type >= IA_CSS_NUM_DYNAMIC_BUFFER_TYPE)) अणु
		IA_CSS_LEAVE("return_val = false");
		वापस false;
	पूर्ण

	*val = buffer_type_to_queue_id_map[thपढ़ो_id][buf_type];
	अगर ((*val == SH_CSS_INVALID_QUEUE_ID) || (*val >= SH_CSS_MAX_NUM_QUEUES)) अणु
		IA_CSS_LOG("INVALID queue ID MAP = %d\n", *val);
		IA_CSS_LEAVE("return_val = false");
		वापस false;
	पूर्ण
	IA_CSS_LEAVE("return_val = true");
	वापस true;
पूर्ण

/*******************************************************
*** Static functions
********************************************************/
अटल व्योम map_buffer_type_to_queue_id(
    अचिन्हित पूर्णांक thपढ़ो_id,
    क्रमागत ia_css_buffer_type buf_type)
अणु
	अचिन्हित पूर्णांक i;

	निश्चित(thपढ़ो_id < SH_CSS_MAX_SP_THREADS);
	निश्चित(buf_type < IA_CSS_NUM_DYNAMIC_BUFFER_TYPE);
	निश्चित(buffer_type_to_queue_id_map[thपढ़ो_id][buf_type] ==
	       SH_CSS_INVALID_QUEUE_ID);

	/* queue 0 is reserved क्रम parameters because it करोesn't depend on events */
	अगर (buf_type == IA_CSS_BUFFER_TYPE_PARAMETER_SET) अणु
		निश्चित(queue_availability[thपढ़ो_id][IA_CSS_PARAMETER_SET_QUEUE_ID]);
		queue_availability[thपढ़ो_id][IA_CSS_PARAMETER_SET_QUEUE_ID] = false;
		buffer_type_to_queue_id_map[thपढ़ो_id][buf_type] =
		    IA_CSS_PARAMETER_SET_QUEUE_ID;
		वापस;
	पूर्ण

	/* queue 1 is reserved क्रम per frame parameters because it करोesn't depend on events */
	अगर (buf_type == IA_CSS_BUFFER_TYPE_PER_FRAME_PARAMETER_SET) अणु
		निश्चित(queue_availability[thपढ़ो_id][IA_CSS_PER_FRAME_PARAMETER_SET_QUEUE_ID]);
		queue_availability[thपढ़ो_id][IA_CSS_PER_FRAME_PARAMETER_SET_QUEUE_ID] = false;
		buffer_type_to_queue_id_map[thपढ़ो_id][buf_type] =
		    IA_CSS_PER_FRAME_PARAMETER_SET_QUEUE_ID;
		वापस;
	पूर्ण

	क्रम (i = SH_CSS_QUEUE_C_ID; i < SH_CSS_MAX_NUM_QUEUES; i++) अणु
		अगर (queue_availability[thपढ़ो_id][i]) अणु
			queue_availability[thपढ़ो_id][i] = false;
			buffer_type_to_queue_id_map[thपढ़ो_id][buf_type] = i;
			अवरोध;
		पूर्ण
	पूर्ण

	निश्चित(i != SH_CSS_MAX_NUM_QUEUES);
	वापस;
पूर्ण

अटल व्योम unmap_buffer_type_to_queue_id(
    अचिन्हित पूर्णांक thपढ़ो_id,
    क्रमागत ia_css_buffer_type buf_type)
अणु
	पूर्णांक queue_id;

	निश्चित(thपढ़ो_id < SH_CSS_MAX_SP_THREADS);
	निश्चित(buf_type < IA_CSS_NUM_DYNAMIC_BUFFER_TYPE);
	निश्चित(buffer_type_to_queue_id_map[thपढ़ो_id][buf_type] !=
	       SH_CSS_INVALID_QUEUE_ID);

	queue_id = buffer_type_to_queue_id_map[thपढ़ो_id][buf_type];
	buffer_type_to_queue_id_map[thपढ़ो_id][buf_type] = SH_CSS_INVALID_QUEUE_ID;
	queue_availability[thपढ़ो_id][queue_id] = true;
पूर्ण

अटल ia_css_queue_t *bufq_get_qhandle(
    क्रमागत sh_css_queue_type type,
    क्रमागत sh_css_queue_id id,
    पूर्णांक thपढ़ो)
अणु
	ia_css_queue_t *q = शून्य;

	चयन (type) अणु
	हाल sh_css_host2sp_buffer_queue:
		अगर ((thपढ़ो >= SH_CSS_MAX_SP_THREADS) || (thपढ़ो < 0) ||
		    (id == SH_CSS_INVALID_QUEUE_ID))
			अवरोध;
		q = &css_queues.host2sp_buffer_queue_handles[thपढ़ो][id];
		अवरोध;
	हाल sh_css_sp2host_buffer_queue:
		अगर (id == SH_CSS_INVALID_QUEUE_ID)
			अवरोध;
		q = &css_queues.sp2host_buffer_queue_handles[id];
		अवरोध;
	हाल sh_css_host2sp_psys_event_queue:
		q = &css_queues.host2sp_psys_event_queue_handle;
		अवरोध;
	हाल sh_css_sp2host_psys_event_queue:
		q = &css_queues.sp2host_psys_event_queue_handle;
		अवरोध;
	हाल sh_css_host2sp_isys_event_queue:
		q = &css_queues.host2sp_isys_event_queue_handle;
		अवरोध;
	हाल sh_css_sp2host_isys_event_queue:
		q = &css_queues.sp2host_isys_event_queue_handle;
		अवरोध;
	हाल sh_css_host2sp_tag_cmd_queue:
		q = &css_queues.host2sp_tag_cmd_queue_handle;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस q;
पूर्ण

/* Local function to initialize a buffer queue. This reduces
 * the chances of copy-paste errors or typos.
 */
अटल अंतरभूत व्योम
init_bufq(अचिन्हित पूर्णांक desc_offset,
	  अचिन्हित पूर्णांक elems_offset,
	  ia_css_queue_t *handle)
अणु
	स्थिर काष्ठा ia_css_fw_info *fw;
	अचिन्हित पूर्णांक q_base_addr;
	ia_css_queue_remote_t remoteq;

	fw = &sh_css_sp_fw;
	q_base_addr = fw->info.sp.host_sp_queue;

	/* Setup queue location as SP and proc id as SP0_ID */
	remoteq.location = IA_CSS_QUEUE_LOC_SP;
	remoteq.proc_id = SP0_ID;
	remoteq.cb_desc_addr = q_base_addr + desc_offset;
	remoteq.cb_elems_addr = q_base_addr + elems_offset;
	/* Initialize the queue instance and obtain handle */
	ia_css_queue_remote_init(handle, &remoteq);
पूर्ण

व्योम ia_css_bufq_init(व्योम)
अणु
	पूर्णांक i, j;

	IA_CSS_ENTER_PRIVATE("");

	/* Setup all the local queue descriptors क्रम Host2SP Buffer Queues */
	क्रम (i = 0; i < SH_CSS_MAX_SP_THREADS; i++)
		क्रम (j = 0; j < SH_CSS_MAX_NUM_QUEUES; j++) अणु
			init_bufq((uपूर्णांक32_t)दुरत्व(काष्ठा host_sp_queues,
						     host2sp_buffer_queues_desc[i][j]),
				  (uपूर्णांक32_t)दुरत्व(काष्ठा host_sp_queues, host2sp_buffer_queues_elems[i][j]),
				  &css_queues.host2sp_buffer_queue_handles[i][j]);
		पूर्ण

	/* Setup all the local queue descriptors क्रम SP2Host Buffer Queues */
	क्रम (i = 0; i < SH_CSS_MAX_NUM_QUEUES; i++) अणु
		init_bufq(दुरत्व(काष्ठा host_sp_queues, sp2host_buffer_queues_desc[i]),
			  दुरत्व(काष्ठा host_sp_queues, sp2host_buffer_queues_elems[i]),
			  &css_queues.sp2host_buffer_queue_handles[i]);
	पूर्ण

	/* Host2SP event queue*/
	init_bufq((uपूर्णांक32_t)दुरत्व(काष्ठा host_sp_queues,
				     host2sp_psys_event_queue_desc),
		  (uपूर्णांक32_t)दुरत्व(काष्ठा host_sp_queues, host2sp_psys_event_queue_elems),
		  &css_queues.host2sp_psys_event_queue_handle);

	/* SP2Host event queue */
	init_bufq((uपूर्णांक32_t)दुरत्व(काष्ठा host_sp_queues,
				     sp2host_psys_event_queue_desc),
		  (uपूर्णांक32_t)दुरत्व(काष्ठा host_sp_queues, sp2host_psys_event_queue_elems),
		  &css_queues.sp2host_psys_event_queue_handle);

	/* Host2SP ISYS event queue */
	init_bufq((uपूर्णांक32_t)दुरत्व(काष्ठा host_sp_queues,
				     host2sp_isys_event_queue_desc),
		  (uपूर्णांक32_t)दुरत्व(काष्ठा host_sp_queues, host2sp_isys_event_queue_elems),
		  &css_queues.host2sp_isys_event_queue_handle);

	/* SP2Host ISYS event queue*/
	init_bufq((uपूर्णांक32_t)दुरत्व(काष्ठा host_sp_queues,
				     sp2host_isys_event_queue_desc),
		  (uपूर्णांक32_t)दुरत्व(काष्ठा host_sp_queues, sp2host_isys_event_queue_elems),
		  &css_queues.sp2host_isys_event_queue_handle);

	/* Host2SP tagger command queue */
	init_bufq((uपूर्णांक32_t)दुरत्व(काष्ठा host_sp_queues, host2sp_tag_cmd_queue_desc),
		  (uपूर्णांक32_t)दुरत्व(काष्ठा host_sp_queues, host2sp_tag_cmd_queue_elems),
		  &css_queues.host2sp_tag_cmd_queue_handle);

	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

पूर्णांक ia_css_bufq_enqueue_buffer(
    पूर्णांक thपढ़ो_index,
    पूर्णांक queue_id,
    uपूर्णांक32_t item)
अणु
	ia_css_queue_t *q;
	पूर्णांक error;

	IA_CSS_ENTER_PRIVATE("queue_id=%d", queue_id);
	अगर ((thपढ़ो_index >= SH_CSS_MAX_SP_THREADS) || (thपढ़ो_index < 0) ||
	    (queue_id == SH_CSS_INVALID_QUEUE_ID))
		वापस -EINVAL;

	/* Get the queue क्रम communication */
	q = bufq_get_qhandle(sh_css_host2sp_buffer_queue,
			     queue_id,
			     thपढ़ो_index);
	अगर (q) अणु
		error = ia_css_queue_enqueue(q, item);
	पूर्ण अन्यथा अणु
		IA_CSS_ERROR("queue is not initialized");
		error = -EBUSY;
	पूर्ण

	IA_CSS_LEAVE_ERR_PRIVATE(error);
	वापस error;
पूर्ण

पूर्णांक ia_css_bufq_dequeue_buffer(
    पूर्णांक queue_id,
    uपूर्णांक32_t *item)
अणु
	पूर्णांक error;
	ia_css_queue_t *q;

	IA_CSS_ENTER_PRIVATE("queue_id=%d", queue_id);
	अगर ((!item) ||
	    (queue_id <= SH_CSS_INVALID_QUEUE_ID) ||
	    (queue_id >= SH_CSS_MAX_NUM_QUEUES)
	   )
		वापस -EINVAL;

	q = bufq_get_qhandle(sh_css_sp2host_buffer_queue,
			     queue_id,
			     -1);
	अगर (q) अणु
		error = ia_css_queue_dequeue(q, item);
	पूर्ण अन्यथा अणु
		IA_CSS_ERROR("queue is not initialized");
		error = -EBUSY;
	पूर्ण

	IA_CSS_LEAVE_ERR_PRIVATE(error);
	वापस error;
पूर्ण

पूर्णांक ia_css_bufq_enqueue_psys_event(
    u8 evt_id,
    u8 evt_payload_0,
    u8 evt_payload_1,
    uपूर्णांक8_t evt_payload_2)
अणु
	पूर्णांक error = 0;
	ia_css_queue_t *q;

	IA_CSS_ENTER_PRIVATE("evt_id=%d", evt_id);
	q = bufq_get_qhandle(sh_css_host2sp_psys_event_queue, -1, -1);
	अगर (!q) अणु
		IA_CSS_ERROR("queue is not initialized");
		वापस -EBUSY;
	पूर्ण

	error = ia_css_eventq_send(q,
				   evt_id, evt_payload_0, evt_payload_1, evt_payload_2);

	IA_CSS_LEAVE_ERR_PRIVATE(error);
	वापस error;
पूर्ण

पूर्णांक ia_css_bufq_dequeue_psys_event(
    u8 item[BUFQ_EVENT_SIZE])
अणु
	पूर्णांक error = 0;
	ia_css_queue_t *q;

	/* No ENTER/LEAVE in this function since this is polled
	 * by some test apps. Enablign logging here floods the log
	 * files which may cause समयouts. */
	अगर (!item)
		वापस -EINVAL;

	q = bufq_get_qhandle(sh_css_sp2host_psys_event_queue, -1, -1);
	अगर (!q) अणु
		IA_CSS_ERROR("queue is not initialized");
		वापस -EBUSY;
	पूर्ण
	error = ia_css_eventq_recv(q, item);

	वापस error;
पूर्ण

पूर्णांक ia_css_bufq_dequeue_isys_event(
    u8 item[BUFQ_EVENT_SIZE])
अणु
	पूर्णांक error = 0;
	ia_css_queue_t *q;

	/* No ENTER/LEAVE in this function since this is polled
	 * by some test apps. Enablign logging here floods the log
	 * files which may cause समयouts. */
	अगर (!item)
		वापस -EINVAL;

	q = bufq_get_qhandle(sh_css_sp2host_isys_event_queue, -1, -1);
	अगर (!q) अणु
		IA_CSS_ERROR("queue is not initialized");
		वापस -EBUSY;
	पूर्ण
	error = ia_css_eventq_recv(q, item);
	वापस error;
पूर्ण

पूर्णांक ia_css_bufq_enqueue_isys_event(uपूर्णांक8_t evt_id)
अणु
	पूर्णांक error = 0;
	ia_css_queue_t *q;

	IA_CSS_ENTER_PRIVATE("event_id=%d", evt_id);
	q = bufq_get_qhandle(sh_css_host2sp_isys_event_queue, -1, -1);
	अगर (!q) अणु
		IA_CSS_ERROR("queue is not initialized");
		वापस -EBUSY;
	पूर्ण

	error = ia_css_eventq_send(q, evt_id, 0, 0, 0);

	IA_CSS_LEAVE_ERR_PRIVATE(error);
	वापस error;
पूर्ण

पूर्णांक ia_css_bufq_enqueue_tag_cmd(
    uपूर्णांक32_t item)
अणु
	पूर्णांक error;
	ia_css_queue_t *q;

	IA_CSS_ENTER_PRIVATE("item=%d", item);
	q = bufq_get_qhandle(sh_css_host2sp_tag_cmd_queue, -1, -1);
	अगर (!q) अणु
		IA_CSS_ERROR("queue is not initialized");
		वापस -EBUSY;
	पूर्ण
	error = ia_css_queue_enqueue(q, item);

	IA_CSS_LEAVE_ERR_PRIVATE(error);
	वापस error;
पूर्ण

पूर्णांक ia_css_bufq_deinit(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम bufq_dump_queue_info(स्थिर अक्षर *prefix, ia_css_queue_t *qhandle)
अणु
	u32 मुक्त = 0, used = 0;

	निश्चित(prefix && qhandle);
	ia_css_queue_get_used_space(qhandle, &used);
	ia_css_queue_get_मुक्त_space(qhandle, &मुक्त);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "%s: used=%u free=%u\n",
			    prefix, used, मुक्त);
पूर्ण

व्योम ia_css_bufq_dump_queue_info(व्योम)
अणु
	पूर्णांक i, j;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "Queue Information:\n");

	क्रम (i = 0; i < SH_CSS_MAX_SP_THREADS; i++) अणु
		क्रम (j = 0; j < SH_CSS_MAX_NUM_QUEUES; j++) अणु
			snम_लिखो(prefix, BUFQ_DUMP_खाता_NAME_PREFIX_SIZE,
				 "host2sp_buffer_queue[%u][%u]", i, j);
			bufq_dump_queue_info(prefix,
					     &css_queues.host2sp_buffer_queue_handles[i][j]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < SH_CSS_MAX_NUM_QUEUES; i++) अणु
		snम_लिखो(prefix, BUFQ_DUMP_खाता_NAME_PREFIX_SIZE,
			 "sp2host_buffer_queue[%u]", i);
		bufq_dump_queue_info(prefix,
				     &css_queues.sp2host_buffer_queue_handles[i]);
	पूर्ण
	bufq_dump_queue_info("host2sp_psys_event",
			     &css_queues.host2sp_psys_event_queue_handle);
	bufq_dump_queue_info("sp2host_psys_event",
			     &css_queues.sp2host_psys_event_queue_handle);

	bufq_dump_queue_info("host2sp_isys_event",
			     &css_queues.host2sp_isys_event_queue_handle);
	bufq_dump_queue_info("sp2host_isys_event",
			     &css_queues.sp2host_isys_event_queue_handle);
	bufq_dump_queue_info("host2sp_tag_cmd",
			     &css_queues.host2sp_tag_cmd_queue_handle);
पूर्ण
