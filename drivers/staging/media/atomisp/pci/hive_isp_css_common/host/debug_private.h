<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010-2015, Intel Corporation.
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

#अगर_अघोषित __DEBUG_PRIVATE_H_INCLUDED__
#घोषणा __DEBUG_PRIVATE_H_INCLUDED__

#समावेश "debug_public.h"

#समावेश "sp.h"

#घोषणा __INLINE_ISP__
#समावेश "isp.h"

#समावेश "assert_support.h"

STORAGE_CLASS_DEBUG_C bool is_debug_buffer_empty(व्योम)
अणु
	वापस (debug_data_ptr->head == debug_data_ptr->tail);
पूर्ण

STORAGE_CLASS_DEBUG_C hrt_data debug_dequeue(व्योम)
अणु
	hrt_data value = 0;

	निश्चित(debug_buffer_address != ((hrt_address) - 1));

	debug_synch_queue();

	अगर (!is_debug_buffer_empty()) अणु
		value = debug_data_ptr->buf[debug_data_ptr->head];
		debug_data_ptr->head = (debug_data_ptr->head + 1) & DEBUG_BUF_MASK;
		sp_dmem_store_uपूर्णांक32(SP0_ID, debug_buffer_address + DEBUG_DATA_HEAD_ADDR,
				     debug_data_ptr->head);
	पूर्ण

	वापस value;
पूर्ण

STORAGE_CLASS_DEBUG_C व्योम debug_synch_queue(व्योम)
अणु
	u32 remote_tail = sp_dmem_load_uपूर्णांक32(SP0_ID,
					      debug_buffer_address + DEBUG_DATA_TAIL_ADDR);
	/* We could move the remote head after the upload, but we would have to limit the upload w.r.t. the local head. This is easier */
	अगर (remote_tail > debug_data_ptr->tail) अणु
		माप_प्रकार	delta = remote_tail - debug_data_ptr->tail;

		sp_dmem_load(SP0_ID, debug_buffer_address + DEBUG_DATA_BUF_ADDR +
			     debug_data_ptr->tail * माप(uपूर्णांक32_t),
			     (व्योम *)&debug_data_ptr->buf[debug_data_ptr->tail], delta * माप(uपूर्णांक32_t));
	पूर्ण अन्यथा अगर (remote_tail < debug_data_ptr->tail) अणु
		माप_प्रकार	delta = DEBUG_BUF_SIZE - debug_data_ptr->tail;

		sp_dmem_load(SP0_ID, debug_buffer_address + DEBUG_DATA_BUF_ADDR +
			     debug_data_ptr->tail * माप(uपूर्णांक32_t),
			     (व्योम *)&debug_data_ptr->buf[debug_data_ptr->tail], delta * माप(uपूर्णांक32_t));
		sp_dmem_load(SP0_ID, debug_buffer_address + DEBUG_DATA_BUF_ADDR,
			     (व्योम *)&debug_data_ptr->buf[0],
			     remote_tail * माप(uपूर्णांक32_t));
	पूर्ण /* अन्यथा we are up to date */
	debug_data_ptr->tail = remote_tail;
पूर्ण

STORAGE_CLASS_DEBUG_C व्योम debug_synch_queue_isp(व्योम)
अणु
	u32 remote_tail = isp_dmem_load_uपूर्णांक32(ISP0_ID,
					       DEBUG_BUFFER_ISP_DMEM_ADDR + DEBUG_DATA_TAIL_ADDR);
	/* We could move the remote head after the upload, but we would have to limit the upload w.r.t. the local head. This is easier */
	अगर (remote_tail > debug_data_ptr->tail) अणु
		माप_प्रकार	delta = remote_tail - debug_data_ptr->tail;

		isp_dmem_load(ISP0_ID, DEBUG_BUFFER_ISP_DMEM_ADDR + DEBUG_DATA_BUF_ADDR +
			      debug_data_ptr->tail * माप(uपूर्णांक32_t),
			      (व्योम *)&debug_data_ptr->buf[debug_data_ptr->tail], delta * माप(uपूर्णांक32_t));
	पूर्ण अन्यथा अगर (remote_tail < debug_data_ptr->tail) अणु
		माप_प्रकार	delta = DEBUG_BUF_SIZE - debug_data_ptr->tail;

		isp_dmem_load(ISP0_ID, DEBUG_BUFFER_ISP_DMEM_ADDR + DEBUG_DATA_BUF_ADDR +
			      debug_data_ptr->tail * माप(uपूर्णांक32_t),
			      (व्योम *)&debug_data_ptr->buf[debug_data_ptr->tail], delta * माप(uपूर्णांक32_t));
		isp_dmem_load(ISP0_ID, DEBUG_BUFFER_ISP_DMEM_ADDR + DEBUG_DATA_BUF_ADDR,
			      (व्योम *)&debug_data_ptr->buf[0],
			      remote_tail * माप(uपूर्णांक32_t));
	पूर्ण /* अन्यथा we are up to date */
	debug_data_ptr->tail = remote_tail;
पूर्ण

STORAGE_CLASS_DEBUG_C व्योम debug_synch_queue_ddr(व्योम)
अणु
	u32	remote_tail;

	hmm_load(debug_buffer_ddr_address + DEBUG_DATA_TAIL_DDR_ADDR, &remote_tail,
		  माप(uपूर्णांक32_t));
	/* We could move the remote head after the upload, but we would have to limit the upload w.r.t. the local head. This is easier */
	अगर (remote_tail > debug_data_ptr->tail) अणु
		माप_प्रकार	delta = remote_tail - debug_data_ptr->tail;

		hmm_load(debug_buffer_ddr_address + DEBUG_DATA_BUF_DDR_ADDR +
			  debug_data_ptr->tail * माप(uपूर्णांक32_t),
			  (व्योम *)&debug_data_ptr->buf[debug_data_ptr->tail], delta * माप(uपूर्णांक32_t));
	पूर्ण अन्यथा अगर (remote_tail < debug_data_ptr->tail) अणु
		माप_प्रकार	delta = DEBUG_BUF_SIZE - debug_data_ptr->tail;

		hmm_load(debug_buffer_ddr_address + DEBUG_DATA_BUF_DDR_ADDR +
			  debug_data_ptr->tail * माप(uपूर्णांक32_t),
			  (व्योम *)&debug_data_ptr->buf[debug_data_ptr->tail], delta * माप(uपूर्णांक32_t));
		hmm_load(debug_buffer_ddr_address + DEBUG_DATA_BUF_DDR_ADDR,
			  (व्योम *)&debug_data_ptr->buf[0],
			  remote_tail * माप(uपूर्णांक32_t));
	पूर्ण /* अन्यथा we are up to date */
	debug_data_ptr->tail = remote_tail;
पूर्ण

#पूर्ण_अगर /* __DEBUG_PRIVATE_H_INCLUDED__ */
