<शैली गुरु>
/*
 * Copyright (c) 2004, 2005, Voltaire, Inc. All rights reserved.
 * Copyright (c) 2005 Intel Corporation. All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2009 HNR Consulting. All rights reserved.
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

#अगर_अघोषित __IB_MAD_PRIV_H__
#घोषणा __IB_MAD_PRIV_H__

#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <linux/workqueue.h>
#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_smi.h>
#समावेश <rdma/opa_smi.h>

#घोषणा IB_MAD_QPS_CORE		2 /* Always QP0 and QP1 as a minimum */

/* QP and CQ parameters */
#घोषणा IB_MAD_QP_SEND_SIZE	128
#घोषणा IB_MAD_QP_RECV_SIZE	512
#घोषणा IB_MAD_QP_MIN_SIZE	64
#घोषणा IB_MAD_QP_MAX_SIZE	8192
#घोषणा IB_MAD_SEND_REQ_MAX_SG	2
#घोषणा IB_MAD_RECV_REQ_MAX_SG	1

#घोषणा IB_MAD_SEND_Q_PSN	0

/* Registration table sizes */
#घोषणा MAX_MGMT_CLASS		80
#घोषणा MAX_MGMT_VERSION	0x83
#घोषणा MAX_MGMT_OUI		8
#घोषणा MAX_MGMT_VENDOR_RANGE2	(IB_MGMT_CLASS_VENDOR_RANGE2_END - \
				IB_MGMT_CLASS_VENDOR_RANGE2_START + 1)

काष्ठा ib_mad_list_head अणु
	काष्ठा list_head list;
	काष्ठा ib_cqe cqe;
	काष्ठा ib_mad_queue *mad_queue;
पूर्ण;

काष्ठा ib_mad_निजी_header अणु
	काष्ठा ib_mad_list_head mad_list;
	काष्ठा ib_mad_recv_wc recv_wc;
	काष्ठा ib_wc wc;
	u64 mapping;
पूर्ण __packed;

काष्ठा ib_mad_निजी अणु
	काष्ठा ib_mad_निजी_header header;
	माप_प्रकार mad_size;
	काष्ठा ib_grh grh;
	u8 mad[];
पूर्ण __packed;

काष्ठा ib_rmpp_segment अणु
	काष्ठा list_head list;
	u32 num;
	u8 data[];
पूर्ण;

काष्ठा ib_mad_agent_निजी अणु
	काष्ठा ib_mad_agent agent;
	काष्ठा ib_mad_reg_req *reg_req;
	काष्ठा ib_mad_qp_info *qp_info;

	spinlock_t lock;
	काष्ठा list_head send_list;
	काष्ठा list_head रुको_list;
	काष्ठा list_head करोne_list;
	काष्ठा delayed_work समयd_work;
	अचिन्हित दीर्घ समयout;
	काष्ठा list_head local_list;
	काष्ठा work_काष्ठा local_work;
	काष्ठा list_head rmpp_list;

	refcount_t refcount;
	जोड़ अणु
		काष्ठा completion comp;
		काष्ठा rcu_head rcu;
	पूर्ण;
पूर्ण;

काष्ठा ib_mad_snoop_निजी अणु
	काष्ठा ib_mad_agent agent;
	काष्ठा ib_mad_qp_info *qp_info;
	पूर्णांक snoop_index;
	पूर्णांक mad_snoop_flags;
	atomic_t refcount;
	काष्ठा completion comp;
पूर्ण;

काष्ठा ib_mad_send_wr_निजी अणु
	काष्ठा ib_mad_list_head mad_list;
	काष्ठा list_head agent_list;
	काष्ठा ib_mad_agent_निजी *mad_agent_priv;
	काष्ठा ib_mad_send_buf send_buf;
	u64 header_mapping;
	u64 payload_mapping;
	काष्ठा ib_ud_wr send_wr;
	काष्ठा ib_sge sg_list[IB_MAD_SEND_REQ_MAX_SG];
	__be64 tid;
	अचिन्हित दीर्घ समयout;
	पूर्णांक max_retries;
	पूर्णांक retries_left;
	पूर्णांक retry;
	पूर्णांक refcount;
	क्रमागत ib_wc_status status;

	/* RMPP control */
	काष्ठा list_head rmpp_list;
	काष्ठा ib_rmpp_segment *last_ack_seg;
	काष्ठा ib_rmpp_segment *cur_seg;
	पूर्णांक last_ack;
	पूर्णांक seg_num;
	पूर्णांक newwin;
	पूर्णांक pad;
पूर्ण;

काष्ठा ib_mad_local_निजी अणु
	काष्ठा list_head completion_list;
	काष्ठा ib_mad_निजी *mad_priv;
	काष्ठा ib_mad_agent_निजी *recv_mad_agent;
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;
	माप_प्रकार वापस_wc_byte_len;
पूर्ण;

काष्ठा ib_mad_mgmt_method_table अणु
	काष्ठा ib_mad_agent_निजी *agent[IB_MGMT_MAX_METHODS];
पूर्ण;

काष्ठा ib_mad_mgmt_class_table अणु
	काष्ठा ib_mad_mgmt_method_table *method_table[MAX_MGMT_CLASS];
पूर्ण;

काष्ठा ib_mad_mgmt_venकरोr_class अणु
	u8	oui[MAX_MGMT_OUI][3];
	काष्ठा ib_mad_mgmt_method_table *method_table[MAX_MGMT_OUI];
पूर्ण;

काष्ठा ib_mad_mgmt_venकरोr_class_table अणु
	काष्ठा ib_mad_mgmt_venकरोr_class *venकरोr_class[MAX_MGMT_VENDOR_RANGE2];
पूर्ण;

काष्ठा ib_mad_mgmt_version_table अणु
	काष्ठा ib_mad_mgmt_class_table *class;
	काष्ठा ib_mad_mgmt_venकरोr_class_table *venकरोr;
पूर्ण;

काष्ठा ib_mad_queue अणु
	spinlock_t lock;
	काष्ठा list_head list;
	पूर्णांक count;
	पूर्णांक max_active;
	काष्ठा ib_mad_qp_info *qp_info;
पूर्ण;

काष्ठा ib_mad_qp_info अणु
	काष्ठा ib_mad_port_निजी *port_priv;
	काष्ठा ib_qp *qp;
	काष्ठा ib_mad_queue send_queue;
	काष्ठा ib_mad_queue recv_queue;
	काष्ठा list_head overflow_list;
	spinlock_t snoop_lock;
	काष्ठा ib_mad_snoop_निजी **snoop_table;
	पूर्णांक snoop_table_size;
	atomic_t snoop_count;
पूर्ण;

काष्ठा ib_mad_port_निजी अणु
	काष्ठा list_head port_list;
	काष्ठा ib_device *device;
	पूर्णांक port_num;
	काष्ठा ib_cq *cq;
	काष्ठा ib_pd *pd;

	spinlock_t reg_lock;
	काष्ठा ib_mad_mgmt_version_table version[MAX_MGMT_VERSION];
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा ib_mad_qp_info qp_info[IB_MAD_QPS_CORE];
पूर्ण;

पूर्णांक ib_send_mad(काष्ठा ib_mad_send_wr_निजी *mad_send_wr);

काष्ठा ib_mad_send_wr_निजी *
ib_find_send_mad(स्थिर काष्ठा ib_mad_agent_निजी *mad_agent_priv,
		 स्थिर काष्ठा ib_mad_recv_wc *mad_recv_wc);

व्योम ib_mad_complete_send_wr(काष्ठा ib_mad_send_wr_निजी *mad_send_wr,
			     काष्ठा ib_mad_send_wc *mad_send_wc);

व्योम ib_mark_mad_करोne(काष्ठा ib_mad_send_wr_निजी *mad_send_wr);

व्योम ib_reset_mad_समयout(काष्ठा ib_mad_send_wr_निजी *mad_send_wr,
			  अचिन्हित दीर्घ समयout_ms);

#पूर्ण_अगर	/* __IB_MAD_PRIV_H__ */
