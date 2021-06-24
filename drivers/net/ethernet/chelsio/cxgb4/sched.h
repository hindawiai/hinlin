<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2016 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __CXGB4_SCHED_H
#घोषणा __CXGB4_SCHED_H

#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>

#घोषणा SCHED_CLS_NONE 0xff

#घोषणा FW_SCHED_CLS_NONE 0xffffffff

/* Max rate that can be set to a scheduling class is 100 Gbps */
#घोषणा SCHED_MAX_RATE_KBPS 100000000U

क्रमागत अणु
	SCHED_STATE_ACTIVE,
	SCHED_STATE_UNUSED,
पूर्ण;

क्रमागत sched_fw_ops अणु
	SCHED_FW_OP_ADD,
	SCHED_FW_OP_DEL,
पूर्ण;

क्रमागत sched_bind_type अणु
	SCHED_QUEUE,
	SCHED_FLOWC,
पूर्ण;

काष्ठा sched_queue_entry अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक cntxt_id;
	काष्ठा ch_sched_queue param;
पूर्ण;

काष्ठा sched_flowc_entry अणु
	काष्ठा list_head list;
	काष्ठा ch_sched_flowc param;
पूर्ण;

काष्ठा sched_class अणु
	u8 state;
	u8 idx;
	काष्ठा ch_sched_params info;
	क्रमागत sched_bind_type bind_type;
	काष्ठा list_head entry_list;
	atomic_t refcnt;
पूर्ण;

काष्ठा sched_table अणु      /* per port scheduling table */
	u8 sched_size;
	काष्ठा sched_class tab[];
पूर्ण;

अटल अंतरभूत bool can_sched(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);

	वापस !pi->sched_tbl ? false : true;
पूर्ण

अटल अंतरभूत bool valid_class_id(काष्ठा net_device *dev, u8 class_id)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);

	अगर ((class_id > pi->sched_tbl->sched_size - 1) &&
	    (class_id != SCHED_CLS_NONE))
		वापस false;

	वापस true;
पूर्ण

काष्ठा sched_class *cxgb4_sched_queue_lookup(काष्ठा net_device *dev,
					     काष्ठा ch_sched_queue *p);
पूर्णांक cxgb4_sched_class_bind(काष्ठा net_device *dev, व्योम *arg,
			   क्रमागत sched_bind_type type);
पूर्णांक cxgb4_sched_class_unbind(काष्ठा net_device *dev, व्योम *arg,
			     क्रमागत sched_bind_type type);

काष्ठा sched_class *cxgb4_sched_class_alloc(काष्ठा net_device *dev,
					    काष्ठा ch_sched_params *p);
व्योम cxgb4_sched_class_मुक्त(काष्ठा net_device *dev, u8 classid);

काष्ठा sched_table *t4_init_sched(अचिन्हित पूर्णांक size);
व्योम t4_cleanup_sched(काष्ठा adapter *adap);
#पूर्ण_अगर  /* __CXGB4_SCHED_H */
