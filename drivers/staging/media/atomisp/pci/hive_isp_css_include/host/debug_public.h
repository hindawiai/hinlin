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

#अगर_अघोषित __DEBUG_PUBLIC_H_INCLUDED__
#घोषणा __DEBUG_PUBLIC_H_INCLUDED__

#समावेश <type_support.h>
#समावेश <ia_css_types.h>
#समावेश "system_local.h"

/*! brief
 *
 * Simple queuing trace buffer क्रम debug data
 * instantiatable in SP DMEM
 *
 * The buffer has a remote and and a local store
 * which contain duplicate data (when in sync).
 * The buffers are स्वतःmatically synched when the
 * user dequeues, or manualy using the synch function
 *
 * An alternative (storage efficient) implementation
 * could manage the buffers to contain unique data
 *
 * The buffer empty status is computed from local
 * state which करोes not reflect the presence of data
 * in the remote buffer (unless the alternative
 * implementation is followed)
 */

प्रकार काष्ठा debug_data_s		debug_data_t;
प्रकार काष्ठा debug_data_ddr_s	debug_data_ddr_t;

बाह्य debug_data_t				*debug_data_ptr;
बाह्य hrt_address				debug_buffer_address;
बाह्य ia_css_ptr				debug_buffer_ddr_address;

/*! Check the empty state of the local debug data buffer

 \लeturn isEmpty(buffer)
 */
STORAGE_CLASS_DEBUG_H bool is_debug_buffer_empty(व्योम);

/*! Dequeue a token from the debug data buffer

 \लeturn isEmpty(buffer)?0:buffer[head]
 */
STORAGE_CLASS_DEBUG_H hrt_data debug_dequeue(व्योम);

/*! Synchronise the remote buffer to the local buffer

 \लeturn none
 */
STORAGE_CLASS_DEBUG_H व्योम debug_synch_queue(व्योम);

/*! Synchronise the remote buffer to the local buffer

 \लeturn none
 */
STORAGE_CLASS_DEBUG_H व्योम debug_synch_queue_isp(व्योम);

/*! Synchronise the remote buffer to the local buffer

 \लeturn none
 */
STORAGE_CLASS_DEBUG_H व्योम debug_synch_queue_ddr(व्योम);

/*! Set the offset/address of the (remote) debug buffer

 \लeturn none
 */
व्योम debug_buffer_init(
    स्थिर hrt_address		addr);

/*! Set the offset/address of the (remote) debug buffer

 \लeturn none
 */
व्योम debug_buffer_ddr_init(
    स्थिर ia_css_ptr		addr);

/*! Set the (remote) operating mode of the debug buffer

 \लeturn none
 */
व्योम debug_buffer_seपंचांगode(
    स्थिर debug_buf_mode_t	mode);

#पूर्ण_अगर /* __DEBUG_PUBLIC_H_INCLUDED__ */
