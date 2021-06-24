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

#समावेश "ia_css_queue.h"
#समावेश <math_support.h>
#समावेश <ia_css_circbuf.h>
#समावेश <ia_css_circbuf_desc.h>
#समावेश "queue_access.h"

/*****************************************************************************
 * Queue Public APIs
 *****************************************************************************/
पूर्णांक ia_css_queue_local_init(ia_css_queue_t *qhandle, ia_css_queue_local_t *desc)
अणु
	अगर (शून्य == qhandle || शून्य == desc
	    || शून्य == desc->cb_elems || शून्य == desc->cb_desc) अणु
		/* Invalid parameters, वापस error*/
		वापस -EINVAL;
	पूर्ण

	/* Mark the queue as Local */
	qhandle->type = IA_CSS_QUEUE_TYPE_LOCAL;

	/* Create a local circular buffer queue*/
	ia_css_circbuf_create(&qhandle->desc.cb_local,
			      desc->cb_elems,
			      desc->cb_desc);

	वापस 0;
पूर्ण

पूर्णांक ia_css_queue_remote_init(ia_css_queue_t *qhandle, ia_css_queue_remote_t *desc)
अणु
	अगर (शून्य == qhandle || शून्य == desc) अणु
		/* Invalid parameters, वापस error*/
		वापस -EINVAL;
	पूर्ण

	/* Mark the queue as remote*/
	qhandle->type = IA_CSS_QUEUE_TYPE_REMOTE;

	/* Copy over the local queue descriptor*/
	qhandle->location = desc->location;
	qhandle->proc_id = desc->proc_id;
	qhandle->desc.remote.cb_desc_addr = desc->cb_desc_addr;
	qhandle->desc.remote.cb_elems_addr = desc->cb_elems_addr;

	/* If queue is remote, we let the local processor
	 * करो its init, beक्रमe using it. This is just to get us
	 * started, we can हटाओ this restriction as we go ahead
	 */

	वापस 0;
पूर्ण

पूर्णांक ia_css_queue_uninit(ia_css_queue_t *qhandle)
अणु
	अगर (!qhandle)
		वापस -EINVAL;

	/* Load the required queue object */
	अगर (qhandle->type == IA_CSS_QUEUE_TYPE_LOCAL) अणु
		/* Local queues are created. Destroy it*/
		ia_css_circbuf_destroy(&qhandle->desc.cb_local);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ia_css_queue_enqueue(ia_css_queue_t *qhandle, uपूर्णांक32_t item)
अणु
	पूर्णांक error = 0;

	अगर (!qhandle)
		वापस -EINVAL;

	/* 1. Load the required queue object */
	अगर (qhandle->type == IA_CSS_QUEUE_TYPE_LOCAL) अणु
		/* Directly de-ref the object and
		 * operate on the queue
		 */
		अगर (ia_css_circbuf_is_full(&qhandle->desc.cb_local)) अणु
			/* Cannot push the element. Return*/
			वापस -ENOBUFS;
		पूर्ण

		/* Push the element*/
		ia_css_circbuf_push(&qhandle->desc.cb_local, item);
	पूर्ण अन्यथा अगर (qhandle->type == IA_CSS_QUEUE_TYPE_REMOTE) अणु
		ia_css_circbuf_desc_t cb_desc;
		ia_css_circbuf_elem_t cb_elem;
		u32 ignore_desc_flags = QUEUE_IGNORE_STEP_FLAG;

		/* a. Load the queue cb_desc from remote */
		QUEUE_CB_DESC_INIT(&cb_desc);
		error = ia_css_queue_load(qhandle, &cb_desc, ignore_desc_flags);
		अगर (error != 0)
			वापस error;

		/* b. Operate on the queue */
		अगर (ia_css_circbuf_desc_is_full(&cb_desc))
			वापस -ENOBUFS;

		cb_elem.val = item;

		error = ia_css_queue_item_store(qhandle, cb_desc.end, &cb_elem);
		अगर (error != 0)
			वापस error;

		cb_desc.end = (cb_desc.end + 1) % cb_desc.size;

		/* c. Store the queue object */
		/* Set only fields requiring update with
		 * valid value. Aव्योमs uncessary calls
		 * to load/store functions
		 */
		ignore_desc_flags = QUEUE_IGNORE_SIZE_START_STEP_FLAGS;

		error = ia_css_queue_store(qhandle, &cb_desc, ignore_desc_flags);
		अगर (error != 0)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ia_css_queue_dequeue(ia_css_queue_t *qhandle, uपूर्णांक32_t *item)
अणु
	पूर्णांक error = 0;

	अगर (!qhandle || शून्य == item)
		वापस -EINVAL;

	/* 1. Load the required queue object */
	अगर (qhandle->type == IA_CSS_QUEUE_TYPE_LOCAL) अणु
		/* Directly de-ref the object and
		 * operate on the queue
		 */
		अगर (ia_css_circbuf_is_empty(&qhandle->desc.cb_local)) अणु
			/* Nothing to pop. Return empty queue*/
			वापस -ENODATA;
		पूर्ण

		*item = ia_css_circbuf_pop(&qhandle->desc.cb_local);
	पूर्ण अन्यथा अगर (qhandle->type == IA_CSS_QUEUE_TYPE_REMOTE) अणु
		/* a. Load the queue from remote */
		ia_css_circbuf_desc_t cb_desc;
		ia_css_circbuf_elem_t cb_elem;
		u32 ignore_desc_flags = QUEUE_IGNORE_STEP_FLAG;

		QUEUE_CB_DESC_INIT(&cb_desc);

		error = ia_css_queue_load(qhandle, &cb_desc, ignore_desc_flags);
		अगर (error != 0)
			वापस error;

		/* b. Operate on the queue */
		अगर (ia_css_circbuf_desc_is_empty(&cb_desc))
			वापस -ENODATA;

		error = ia_css_queue_item_load(qhandle, cb_desc.start, &cb_elem);
		अगर (error != 0)
			वापस error;

		*item = cb_elem.val;

		cb_desc.start = OP_std_modadd(cb_desc.start, 1, cb_desc.size);

		/* c. Store the queue object */
		/* Set only fields requiring update with
		 * valid value. Aव्योमs uncessary calls
		 * to load/store functions
		 */
		ignore_desc_flags = QUEUE_IGNORE_SIZE_END_STEP_FLAGS;
		error = ia_css_queue_store(qhandle, &cb_desc, ignore_desc_flags);
		अगर (error != 0)
			वापस error;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ia_css_queue_is_full(ia_css_queue_t *qhandle, bool *is_full)
अणु
	पूर्णांक error = 0;

	अगर ((!qhandle) || (!is_full))
		वापस -EINVAL;

	/* 1. Load the required queue object */
	अगर (qhandle->type == IA_CSS_QUEUE_TYPE_LOCAL) अणु
		/* Directly de-ref the object and
		 * operate on the queue
		 */
		*is_full = ia_css_circbuf_is_full(&qhandle->desc.cb_local);
		वापस 0;
	पूर्ण अन्यथा अगर (qhandle->type == IA_CSS_QUEUE_TYPE_REMOTE) अणु
		/* a. Load the queue from remote */
		ia_css_circbuf_desc_t cb_desc;
		u32 ignore_desc_flags = QUEUE_IGNORE_STEP_FLAG;

		QUEUE_CB_DESC_INIT(&cb_desc);
		error = ia_css_queue_load(qhandle, &cb_desc, ignore_desc_flags);
		अगर (error != 0)
			वापस error;

		/* b. Operate on the queue */
		*is_full = ia_css_circbuf_desc_is_full(&cb_desc);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक ia_css_queue_get_मुक्त_space(ia_css_queue_t *qhandle, uपूर्णांक32_t *size)
अणु
	पूर्णांक error = 0;

	अगर ((!qhandle) || (!size))
		वापस -EINVAL;

	/* 1. Load the required queue object */
	अगर (qhandle->type == IA_CSS_QUEUE_TYPE_LOCAL) अणु
		/* Directly de-ref the object and
		 * operate on the queue
		 */
		*size = ia_css_circbuf_get_मुक्त_elems(&qhandle->desc.cb_local);
		वापस 0;
	पूर्ण अन्यथा अगर (qhandle->type == IA_CSS_QUEUE_TYPE_REMOTE) अणु
		/* a. Load the queue from remote */
		ia_css_circbuf_desc_t cb_desc;
		u32 ignore_desc_flags = QUEUE_IGNORE_STEP_FLAG;

		QUEUE_CB_DESC_INIT(&cb_desc);
		error = ia_css_queue_load(qhandle, &cb_desc, ignore_desc_flags);
		अगर (error != 0)
			वापस error;

		/* b. Operate on the queue */
		*size = ia_css_circbuf_desc_get_मुक्त_elems(&cb_desc);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक ia_css_queue_get_used_space(ia_css_queue_t *qhandle, uपूर्णांक32_t *size)
अणु
	पूर्णांक error = 0;

	अगर ((!qhandle) || (!size))
		वापस -EINVAL;

	/* 1. Load the required queue object */
	अगर (qhandle->type == IA_CSS_QUEUE_TYPE_LOCAL) अणु
		/* Directly de-ref the object and
		 * operate on the queue
		 */
		*size = ia_css_circbuf_get_num_elems(&qhandle->desc.cb_local);
		वापस 0;
	पूर्ण अन्यथा अगर (qhandle->type == IA_CSS_QUEUE_TYPE_REMOTE) अणु
		/* a. Load the queue from remote */
		ia_css_circbuf_desc_t cb_desc;
		u32 ignore_desc_flags = QUEUE_IGNORE_STEP_FLAG;

		QUEUE_CB_DESC_INIT(&cb_desc);
		error = ia_css_queue_load(qhandle, &cb_desc, ignore_desc_flags);
		अगर (error != 0)
			वापस error;

		/* b. Operate on the queue */
		*size = ia_css_circbuf_desc_get_num_elems(&cb_desc);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक ia_css_queue_peek(ia_css_queue_t *qhandle, u32 offset, uपूर्णांक32_t *element)
अणु
	u32 num_elems = 0;
	पूर्णांक error = 0;

	अगर ((!qhandle) || (!element))
		वापस -EINVAL;

	/* 1. Load the required queue object */
	अगर (qhandle->type == IA_CSS_QUEUE_TYPE_LOCAL) अणु
		/* Directly de-ref the object and
		 * operate on the queue
		 */
		/* Check अगर offset is valid */
		num_elems = ia_css_circbuf_get_num_elems(&qhandle->desc.cb_local);
		अगर (offset > num_elems)
			वापस -EINVAL;

		*element = ia_css_circbuf_peek_from_start(&qhandle->desc.cb_local, (पूर्णांक)offset);
		वापस 0;
	पूर्ण अन्यथा अगर (qhandle->type == IA_CSS_QUEUE_TYPE_REMOTE) अणु
		/* a. Load the queue from remote */
		ia_css_circbuf_desc_t cb_desc;
		ia_css_circbuf_elem_t cb_elem;
		u32 ignore_desc_flags = QUEUE_IGNORE_STEP_FLAG;

		QUEUE_CB_DESC_INIT(&cb_desc);

		error =  ia_css_queue_load(qhandle, &cb_desc, ignore_desc_flags);
		अगर (error != 0)
			वापस error;

		/* Check अगर offset is valid */
		num_elems = ia_css_circbuf_desc_get_num_elems(&cb_desc);
		अगर (offset > num_elems)
			वापस -EINVAL;

		offset = OP_std_modadd(cb_desc.start, offset, cb_desc.size);
		error = ia_css_queue_item_load(qhandle, (uपूर्णांक8_t)offset, &cb_elem);
		अगर (error != 0)
			वापस error;

		*element = cb_elem.val;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक ia_css_queue_is_empty(ia_css_queue_t *qhandle, bool *is_empty)
अणु
	पूर्णांक error = 0;

	अगर ((!qhandle) || (!is_empty))
		वापस -EINVAL;

	/* 1. Load the required queue object */
	अगर (qhandle->type == IA_CSS_QUEUE_TYPE_LOCAL) अणु
		/* Directly de-ref the object and
		 * operate on the queue
		 */
		*is_empty = ia_css_circbuf_is_empty(&qhandle->desc.cb_local);
		वापस 0;
	पूर्ण अन्यथा अगर (qhandle->type == IA_CSS_QUEUE_TYPE_REMOTE) अणु
		/* a. Load the queue from remote */
		ia_css_circbuf_desc_t cb_desc;
		u32 ignore_desc_flags = QUEUE_IGNORE_STEP_FLAG;

		QUEUE_CB_DESC_INIT(&cb_desc);
		error = ia_css_queue_load(qhandle, &cb_desc, ignore_desc_flags);
		अगर (error != 0)
			वापस error;

		/* b. Operate on the queue */
		*is_empty = ia_css_circbuf_desc_is_empty(&cb_desc);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक ia_css_queue_get_size(ia_css_queue_t *qhandle, uपूर्णांक32_t *size)
अणु
	पूर्णांक error = 0;

	अगर ((!qhandle) || (!size))
		वापस -EINVAL;

	/* 1. Load the required queue object */
	अगर (qhandle->type == IA_CSS_QUEUE_TYPE_LOCAL) अणु
		/* Directly de-ref the object and
		 * operate on the queue
		 */
		/* Return maximum usable capacity */
		*size = ia_css_circbuf_get_size(&qhandle->desc.cb_local);
	पूर्ण अन्यथा अगर (qhandle->type == IA_CSS_QUEUE_TYPE_REMOTE) अणु
		/* a. Load the queue from remote */
		ia_css_circbuf_desc_t cb_desc;
		u32 ignore_desc_flags = QUEUE_IGNORE_START_END_STEP_FLAGS;

		QUEUE_CB_DESC_INIT(&cb_desc);

		error = ia_css_queue_load(qhandle, &cb_desc, ignore_desc_flags);
		अगर (error != 0)
			वापस error;

		/* Return maximum usable capacity */
		*size = cb_desc.size;
	पूर्ण

	वापस 0;
पूर्ण
