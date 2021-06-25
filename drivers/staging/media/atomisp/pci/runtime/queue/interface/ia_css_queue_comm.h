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

#अगर_अघोषित __IA_CSS_QUEUE_COMM_H
#घोषणा __IA_CSS_QUEUE_COMM_H

#समावेश "type_support.h"
#समावेश "ia_css_circbuf.h"
/*****************************************************************************
 * Queue Public Data Structures
 *****************************************************************************/

/* Queue location specअगरier */
/* Aव्योमing क्रमागतs to save space */
#घोषणा IA_CSS_QUEUE_LOC_HOST 0
#घोषणा IA_CSS_QUEUE_LOC_SP   1
#घोषणा IA_CSS_QUEUE_LOC_ISP  2

/* Queue type specअगरier */
/* Aव्योमing क्रमागतs to save space */
#घोषणा IA_CSS_QUEUE_TYPE_LOCAL  0
#घोषणा IA_CSS_QUEUE_TYPE_REMOTE 1

/* क्रम DDR Allocated queues,
allocate minimum these many elements.
DDR->SP' DMEM DMA transfer needs 32byte aligned address.
Since each element size is 4 bytes, 8 elements need to be
DMAed to access single element.*/
#घोषणा IA_CSS_MIN_ELEM_COUNT    8
#घोषणा IA_CSS_DMA_XFER_MASK (IA_CSS_MIN_ELEM_COUNT - 1)

/* Remote Queue object descriptor */
काष्ठा ia_css_queue_remote अणु
	u32 cb_desc_addr; /*Circbuf desc address क्रम remote queues*/
	u32 cb_elems_addr; /*Circbuf elements addr क्रम remote queue*/
	u8 location;    /* Cell location क्रम queue */
	u8 proc_id;     /* Processor id क्रम queue access */
पूर्ण;

प्रकार काष्ठा ia_css_queue_remote ia_css_queue_remote_t;

#पूर्ण_अगर /* __IA_CSS_QUEUE_COMM_H */
