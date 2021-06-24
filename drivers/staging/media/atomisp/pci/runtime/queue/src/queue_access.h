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

#अगर_अघोषित __QUEUE_ACCESS_H
#घोषणा __QUEUE_ACCESS_H

#समावेश <linux/त्रुटिसं.स>

#समावेश <type_support.h>
#समावेश <ia_css_queue_comm.h>
#समावेश <ia_css_circbuf.h>

#घोषणा QUEUE_IGNORE_START_FLAG	0x0001
#घोषणा QUEUE_IGNORE_END_FLAG	0x0002
#घोषणा QUEUE_IGNORE_SIZE_FLAG	0x0004
#घोषणा QUEUE_IGNORE_STEP_FLAG	0x0008
#घोषणा QUEUE_IGNORE_DESC_FLAGS_MAX 0x000f

#घोषणा QUEUE_IGNORE_SIZE_START_STEP_FLAGS \
	(QUEUE_IGNORE_SIZE_FLAG | \
	QUEUE_IGNORE_START_FLAG | \
	QUEUE_IGNORE_STEP_FLAG)

#घोषणा QUEUE_IGNORE_SIZE_END_STEP_FLAGS \
	(QUEUE_IGNORE_SIZE_FLAG | \
	QUEUE_IGNORE_END_FLAG   | \
	QUEUE_IGNORE_STEP_FLAG)

#घोषणा QUEUE_IGNORE_START_END_STEP_FLAGS \
	(QUEUE_IGNORE_START_FLAG | \
	QUEUE_IGNORE_END_FLAG	  | \
	QUEUE_IGNORE_STEP_FLAG)

#घोषणा QUEUE_CB_DESC_INIT(cb_desc)	\
	करो अणु				\
		(cb_desc)->size  = 0;	\
		(cb_desc)->step  = 0;	\
		(cb_desc)->start = 0;	\
		(cb_desc)->end   = 0;	\
	पूर्ण जबतक (0)

काष्ठा ia_css_queue अणु
	u8 type;        /* Specअगरy remote/local type of access */
	u8 location;    /* Cell location क्रम queue */
	u8 proc_id;     /* Processor id क्रम queue access */
	जोड़ अणु
		ia_css_circbuf_t cb_local;
		काष्ठा अणु
			u32 cb_desc_addr; /*Circbuf desc address क्रम remote queues*/
			u32 cb_elems_addr; /*Circbuf elements addr क्रम remote queue*/
		पूर्ण	remote;
	पूर्ण desc;
पूर्ण;

पूर्णांक ia_css_queue_load(
    काष्ठा ia_css_queue *rdesc,
    ia_css_circbuf_desc_t *cb_desc,
    uपूर्णांक32_t ignore_desc_flags);

पूर्णांक ia_css_queue_store(
    काष्ठा ia_css_queue *rdesc,
    ia_css_circbuf_desc_t *cb_desc,
    uपूर्णांक32_t ignore_desc_flags);

पूर्णांक ia_css_queue_item_load(
    काष्ठा ia_css_queue *rdesc,
    u8 position,
    ia_css_circbuf_elem_t *item);

पूर्णांक ia_css_queue_item_store(
    काष्ठा ia_css_queue *rdesc,
    u8 position,
    ia_css_circbuf_elem_t *item);

#पूर्ण_अगर /* __QUEUE_ACCESS_H */
