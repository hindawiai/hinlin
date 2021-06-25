<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Cisco Systems. All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2004 Voltaire, Inc. All rights reserved.
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

#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/पन.स>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/ib_pack.h>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश "mthca_dev.h"
#समावेश "mthca_cmd.h"
#समावेश "mthca_memfree.h"
#समावेश "mthca_wqe.h"

क्रमागत अणु
	MTHCA_MAX_सूचीECT_QP_SIZE = 4 * PAGE_SIZE,
	MTHCA_ACK_REQ_FREQ       = 10,
	MTHCA_FLIGHT_LIMIT       = 9,
	MTHCA_UD_HEADER_SIZE     = 72, /* largest UD header possible */
	MTHCA_INLINE_HEADER_SIZE = 4,  /* data segment overhead क्रम अंतरभूत */
	MTHCA_INLINE_CHUNK_SIZE  = 16  /* अंतरभूत data segment chunk */
पूर्ण;

क्रमागत अणु
	MTHCA_QP_STATE_RST  = 0,
	MTHCA_QP_STATE_INIT = 1,
	MTHCA_QP_STATE_RTR  = 2,
	MTHCA_QP_STATE_RTS  = 3,
	MTHCA_QP_STATE_SQE  = 4,
	MTHCA_QP_STATE_SQD  = 5,
	MTHCA_QP_STATE_ERR  = 6,
	MTHCA_QP_STATE_DRAINING = 7
पूर्ण;

क्रमागत अणु
	MTHCA_QP_ST_RC 	= 0x0,
	MTHCA_QP_ST_UC 	= 0x1,
	MTHCA_QP_ST_RD 	= 0x2,
	MTHCA_QP_ST_UD 	= 0x3,
	MTHCA_QP_ST_MLX = 0x7
पूर्ण;

क्रमागत अणु
	MTHCA_QP_PM_MIGRATED = 0x3,
	MTHCA_QP_PM_ARMED    = 0x0,
	MTHCA_QP_PM_REARM    = 0x1
पूर्ण;

क्रमागत अणु
	/* qp_context flags */
	MTHCA_QP_BIT_DE  = 1 <<  8,
	/* params1 */
	MTHCA_QP_BIT_SRE = 1 << 15,
	MTHCA_QP_BIT_SWE = 1 << 14,
	MTHCA_QP_BIT_SAE = 1 << 13,
	MTHCA_QP_BIT_SIC = 1 <<  4,
	MTHCA_QP_BIT_SSC = 1 <<  3,
	/* params2 */
	MTHCA_QP_BIT_RRE = 1 << 15,
	MTHCA_QP_BIT_RWE = 1 << 14,
	MTHCA_QP_BIT_RAE = 1 << 13,
	MTHCA_QP_BIT_RIC = 1 <<  4,
	MTHCA_QP_BIT_RSC = 1 <<  3
पूर्ण;

क्रमागत अणु
	MTHCA_SEND_DOORBELL_FENCE = 1 << 5
पूर्ण;

काष्ठा mthca_qp_path अणु
	__be32 port_pkey;
	u8     rnr_retry;
	u8     g_mylmc;
	__be16 rlid;
	u8     ackto;
	u8     mgid_index;
	u8     अटल_rate;
	u8     hop_limit;
	__be32 sl_tclass_flowlabel;
	u8     rgid[16];
पूर्ण __packed;

काष्ठा mthca_qp_context अणु
	__be32 flags;
	__be32 tavor_sched_queue; /* Reserved on Arbel */
	u8     mtu_msgmax;
	u8     rq_size_stride;	/* Reserved on Tavor */
	u8     sq_size_stride;	/* Reserved on Tavor */
	u8     rlkey_arbel_sched_queue;	/* Reserved on Tavor */
	__be32 usr_page;
	__be32 local_qpn;
	__be32 remote_qpn;
	u32    reserved1[2];
	काष्ठा mthca_qp_path pri_path;
	काष्ठा mthca_qp_path alt_path;
	__be32 rdd;
	__be32 pd;
	__be32 wqe_base;
	__be32 wqe_lkey;
	__be32 params1;
	__be32 reserved2;
	__be32 next_send_psn;
	__be32 cqn_snd;
	__be32 snd_wqe_base_l;	/* Next send WQE on Tavor */
	__be32 snd_db_index;	/* (debugging only entries) */
	__be32 last_acked_psn;
	__be32 ssn;
	__be32 params2;
	__be32 rnr_nextrecvpsn;
	__be32 ra_buff_indx;
	__be32 cqn_rcv;
	__be32 rcv_wqe_base_l;	/* Next recv WQE on Tavor */
	__be32 rcv_db_index;	/* (debugging only entries) */
	__be32 qkey;
	__be32 srqn;
	__be32 rmsn;
	__be16 rq_wqe_counter;	/* reserved on Tavor */
	__be16 sq_wqe_counter;	/* reserved on Tavor */
	u32    reserved3[18];
पूर्ण __packed;

काष्ठा mthca_qp_param अणु
	__be32 opt_param_mask;
	u32    reserved1;
	काष्ठा mthca_qp_context context;
	u32    reserved2[62];
पूर्ण __packed;

क्रमागत अणु
	MTHCA_QP_OPTPAR_ALT_ADDR_PATH     = 1 << 0,
	MTHCA_QP_OPTPAR_RRE               = 1 << 1,
	MTHCA_QP_OPTPAR_RAE               = 1 << 2,
	MTHCA_QP_OPTPAR_RWE               = 1 << 3,
	MTHCA_QP_OPTPAR_PKEY_INDEX        = 1 << 4,
	MTHCA_QP_OPTPAR_Q_KEY             = 1 << 5,
	MTHCA_QP_OPTPAR_RNR_TIMEOUT       = 1 << 6,
	MTHCA_QP_OPTPAR_PRIMARY_ADDR_PATH = 1 << 7,
	MTHCA_QP_OPTPAR_SRA_MAX           = 1 << 8,
	MTHCA_QP_OPTPAR_RRA_MAX           = 1 << 9,
	MTHCA_QP_OPTPAR_PM_STATE          = 1 << 10,
	MTHCA_QP_OPTPAR_PORT_NUM          = 1 << 11,
	MTHCA_QP_OPTPAR_RETRY_COUNT       = 1 << 12,
	MTHCA_QP_OPTPAR_ALT_RNR_RETRY     = 1 << 13,
	MTHCA_QP_OPTPAR_ACK_TIMEOUT       = 1 << 14,
	MTHCA_QP_OPTPAR_RNR_RETRY         = 1 << 15,
	MTHCA_QP_OPTPAR_SCHED_QUEUE       = 1 << 16
पूर्ण;

अटल स्थिर u8 mthca_opcode[] = अणु
	[IB_WR_SEND]                 = MTHCA_OPCODE_SEND,
	[IB_WR_SEND_WITH_IMM]        = MTHCA_OPCODE_SEND_IMM,
	[IB_WR_RDMA_WRITE]           = MTHCA_OPCODE_RDMA_WRITE,
	[IB_WR_RDMA_WRITE_WITH_IMM]  = MTHCA_OPCODE_RDMA_WRITE_IMM,
	[IB_WR_RDMA_READ]            = MTHCA_OPCODE_RDMA_READ,
	[IB_WR_ATOMIC_CMP_AND_SWP]   = MTHCA_OPCODE_ATOMIC_CS,
	[IB_WR_ATOMIC_FETCH_AND_ADD] = MTHCA_OPCODE_ATOMIC_FA,
पूर्ण;

अटल पूर्णांक is_sqp(काष्ठा mthca_dev *dev, काष्ठा mthca_qp *qp)
अणु
	वापस qp->qpn >= dev->qp_table.sqp_start &&
		qp->qpn <= dev->qp_table.sqp_start + 3;
पूर्ण

अटल पूर्णांक is_qp0(काष्ठा mthca_dev *dev, काष्ठा mthca_qp *qp)
अणु
	वापस qp->qpn >= dev->qp_table.sqp_start &&
		qp->qpn <= dev->qp_table.sqp_start + 1;
पूर्ण

अटल व्योम *get_recv_wqe(काष्ठा mthca_qp *qp, पूर्णांक n)
अणु
	अगर (qp->is_direct)
		वापस qp->queue.direct.buf + (n << qp->rq.wqe_shअगरt);
	अन्यथा
		वापस qp->queue.page_list[(n << qp->rq.wqe_shअगरt) >> PAGE_SHIFT].buf +
			((n << qp->rq.wqe_shअगरt) & (PAGE_SIZE - 1));
पूर्ण

अटल व्योम *get_send_wqe(काष्ठा mthca_qp *qp, पूर्णांक n)
अणु
	अगर (qp->is_direct)
		वापस qp->queue.direct.buf + qp->send_wqe_offset +
			(n << qp->sq.wqe_shअगरt);
	अन्यथा
		वापस qp->queue.page_list[(qp->send_wqe_offset +
					    (n << qp->sq.wqe_shअगरt)) >>
					   PAGE_SHIFT].buf +
			((qp->send_wqe_offset + (n << qp->sq.wqe_shअगरt)) &
			 (PAGE_SIZE - 1));
पूर्ण

अटल व्योम mthca_wq_reset(काष्ठा mthca_wq *wq)
अणु
	wq->next_ind  = 0;
	wq->last_comp = wq->max - 1;
	wq->head      = 0;
	wq->tail      = 0;
पूर्ण

व्योम mthca_qp_event(काष्ठा mthca_dev *dev, u32 qpn,
		    क्रमागत ib_event_type event_type)
अणु
	काष्ठा mthca_qp *qp;
	काष्ठा ib_event event;

	spin_lock(&dev->qp_table.lock);
	qp = mthca_array_get(&dev->qp_table.qp, qpn & (dev->limits.num_qps - 1));
	अगर (qp)
		++qp->refcount;
	spin_unlock(&dev->qp_table.lock);

	अगर (!qp) अणु
		mthca_warn(dev, "Async event %d for bogus QP %08x\n",
			   event_type, qpn);
		वापस;
	पूर्ण

	अगर (event_type == IB_EVENT_PATH_MIG)
		qp->port = qp->alt_port;

	event.device      = &dev->ib_dev;
	event.event       = event_type;
	event.element.qp  = &qp->ibqp;
	अगर (qp->ibqp.event_handler)
		qp->ibqp.event_handler(&event, qp->ibqp.qp_context);

	spin_lock(&dev->qp_table.lock);
	अगर (!--qp->refcount)
		wake_up(&qp->रुको);
	spin_unlock(&dev->qp_table.lock);
पूर्ण

अटल पूर्णांक to_mthca_state(क्रमागत ib_qp_state ib_state)
अणु
	चयन (ib_state) अणु
	हाल IB_QPS_RESET: वापस MTHCA_QP_STATE_RST;
	हाल IB_QPS_INIT:  वापस MTHCA_QP_STATE_INIT;
	हाल IB_QPS_RTR:   वापस MTHCA_QP_STATE_RTR;
	हाल IB_QPS_RTS:   वापस MTHCA_QP_STATE_RTS;
	हाल IB_QPS_SQD:   वापस MTHCA_QP_STATE_SQD;
	हाल IB_QPS_SQE:   वापस MTHCA_QP_STATE_SQE;
	हाल IB_QPS_ERR:   वापस MTHCA_QP_STATE_ERR;
	शेष:                वापस -1;
	पूर्ण
पूर्ण

क्रमागत अणु RC, UC, UD, RD, RDEE, MLX, NUM_TRANS पूर्ण;

अटल पूर्णांक to_mthca_st(पूर्णांक transport)
अणु
	चयन (transport) अणु
	हाल RC:  वापस MTHCA_QP_ST_RC;
	हाल UC:  वापस MTHCA_QP_ST_UC;
	हाल UD:  वापस MTHCA_QP_ST_UD;
	हाल RD:  वापस MTHCA_QP_ST_RD;
	हाल MLX: वापस MTHCA_QP_ST_MLX;
	शेष:  वापस -1;
	पूर्ण
पूर्ण

अटल व्योम store_attrs(काष्ठा mthca_sqp *sqp, स्थिर काष्ठा ib_qp_attr *attr,
			पूर्णांक attr_mask)
अणु
	अगर (attr_mask & IB_QP_PKEY_INDEX)
		sqp->pkey_index = attr->pkey_index;
	अगर (attr_mask & IB_QP_QKEY)
		sqp->qkey = attr->qkey;
	अगर (attr_mask & IB_QP_SQ_PSN)
		sqp->send_psn = attr->sq_psn;
पूर्ण

अटल व्योम init_port(काष्ठा mthca_dev *dev, पूर्णांक port)
अणु
	पूर्णांक err;
	काष्ठा mthca_init_ib_param param;

	स_रखो(&param, 0, माप param);

	param.port_width = dev->limits.port_width_cap;
	param.vl_cap     = dev->limits.vl_cap;
	param.mtu_cap    = dev->limits.mtu_cap;
	param.gid_cap    = dev->limits.gid_table_len;
	param.pkey_cap   = dev->limits.pkey_table_len;

	err = mthca_INIT_IB(dev, &param, port);
	अगर (err)
		mthca_warn(dev, "INIT_IB failed, return code %d.\n", err);
पूर्ण

अटल __be32 get_hw_access_flags(काष्ठा mthca_qp *qp, स्थिर काष्ठा ib_qp_attr *attr,
				  पूर्णांक attr_mask)
अणु
	u8 dest_rd_atomic;
	u32 access_flags;
	u32 hw_access_flags = 0;

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC)
		dest_rd_atomic = attr->max_dest_rd_atomic;
	अन्यथा
		dest_rd_atomic = qp->resp_depth;

	अगर (attr_mask & IB_QP_ACCESS_FLAGS)
		access_flags = attr->qp_access_flags;
	अन्यथा
		access_flags = qp->atomic_rd_en;

	अगर (!dest_rd_atomic)
		access_flags &= IB_ACCESS_REMOTE_WRITE;

	अगर (access_flags & IB_ACCESS_REMOTE_READ)
		hw_access_flags |= MTHCA_QP_BIT_RRE;
	अगर (access_flags & IB_ACCESS_REMOTE_ATOMIC)
		hw_access_flags |= MTHCA_QP_BIT_RAE;
	अगर (access_flags & IB_ACCESS_REMOTE_WRITE)
		hw_access_flags |= MTHCA_QP_BIT_RWE;

	वापस cpu_to_be32(hw_access_flags);
पूर्ण

अटल अंतरभूत क्रमागत ib_qp_state to_ib_qp_state(पूर्णांक mthca_state)
अणु
	चयन (mthca_state) अणु
	हाल MTHCA_QP_STATE_RST:      वापस IB_QPS_RESET;
	हाल MTHCA_QP_STATE_INIT:     वापस IB_QPS_INIT;
	हाल MTHCA_QP_STATE_RTR:      वापस IB_QPS_RTR;
	हाल MTHCA_QP_STATE_RTS:      वापस IB_QPS_RTS;
	हाल MTHCA_QP_STATE_DRAINING:
	हाल MTHCA_QP_STATE_SQD:      वापस IB_QPS_SQD;
	हाल MTHCA_QP_STATE_SQE:      वापस IB_QPS_SQE;
	हाल MTHCA_QP_STATE_ERR:      वापस IB_QPS_ERR;
	शेष:                      वापस -1;
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत ib_mig_state to_ib_mig_state(पूर्णांक mthca_mig_state)
अणु
	चयन (mthca_mig_state) अणु
	हाल 0:  वापस IB_MIG_ARMED;
	हाल 1:  वापस IB_MIG_REARM;
	हाल 3:  वापस IB_MIG_MIGRATED;
	शेष: वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक to_ib_qp_access_flags(पूर्णांक mthca_flags)
अणु
	पूर्णांक ib_flags = 0;

	अगर (mthca_flags & MTHCA_QP_BIT_RRE)
		ib_flags |= IB_ACCESS_REMOTE_READ;
	अगर (mthca_flags & MTHCA_QP_BIT_RWE)
		ib_flags |= IB_ACCESS_REMOTE_WRITE;
	अगर (mthca_flags & MTHCA_QP_BIT_RAE)
		ib_flags |= IB_ACCESS_REMOTE_ATOMIC;

	वापस ib_flags;
पूर्ण

अटल व्योम to_rdma_ah_attr(काष्ठा mthca_dev *dev,
			    काष्ठा rdma_ah_attr *ah_attr,
			    काष्ठा mthca_qp_path *path)
अणु
	u8 port_num = (be32_to_cpu(path->port_pkey) >> 24) & 0x3;

	स_रखो(ah_attr, 0, माप(*ah_attr));

	अगर (port_num == 0 || port_num > dev->limits.num_ports)
		वापस;
	ah_attr->type = rdma_ah_find_type(&dev->ib_dev, port_num);
	rdma_ah_set_port_num(ah_attr, port_num);

	rdma_ah_set_dlid(ah_attr, be16_to_cpu(path->rlid));
	rdma_ah_set_sl(ah_attr, be32_to_cpu(path->sl_tclass_flowlabel) >> 28);
	rdma_ah_set_path_bits(ah_attr, path->g_mylmc & 0x7f);
	rdma_ah_set_अटल_rate(ah_attr,
				mthca_rate_to_ib(dev,
						 path->अटल_rate & 0xf,
						 port_num));
	अगर (path->g_mylmc & (1 << 7)) अणु
		u32 tc_fl = be32_to_cpu(path->sl_tclass_flowlabel);

		rdma_ah_set_grh(ah_attr, शून्य,
				tc_fl & 0xfffff,
				path->mgid_index &
				(dev->limits.gid_table_len - 1),
				path->hop_limit,
				(tc_fl >> 20) & 0xff);
		rdma_ah_set_dgid_raw(ah_attr, path->rgid);
	पूर्ण
पूर्ण

पूर्णांक mthca_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr, पूर्णांक qp_attr_mask,
		   काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibqp->device);
	काष्ठा mthca_qp *qp = to_mqp(ibqp);
	पूर्णांक err = 0;
	काष्ठा mthca_mailbox *mailbox = शून्य;
	काष्ठा mthca_qp_param *qp_param;
	काष्ठा mthca_qp_context *context;
	पूर्णांक mthca_state;

	mutex_lock(&qp->mutex);

	अगर (qp->state == IB_QPS_RESET) अणु
		qp_attr->qp_state = IB_QPS_RESET;
		जाओ करोne;
	पूर्ण

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox)) अणु
		err = PTR_ERR(mailbox);
		जाओ out;
	पूर्ण

	err = mthca_QUERY_QP(dev, qp->qpn, 0, mailbox);
	अगर (err) अणु
		mthca_warn(dev, "QUERY_QP failed (%d)\n", err);
		जाओ out_mailbox;
	पूर्ण

	qp_param    = mailbox->buf;
	context     = &qp_param->context;
	mthca_state = be32_to_cpu(context->flags) >> 28;

	qp->state		     = to_ib_qp_state(mthca_state);
	qp_attr->qp_state	     = qp->state;
	qp_attr->path_mtu 	     = context->mtu_msgmax >> 5;
	qp_attr->path_mig_state      =
		to_ib_mig_state((be32_to_cpu(context->flags) >> 11) & 0x3);
	qp_attr->qkey 		     = be32_to_cpu(context->qkey);
	qp_attr->rq_psn 	     = be32_to_cpu(context->rnr_nextrecvpsn) & 0xffffff;
	qp_attr->sq_psn 	     = be32_to_cpu(context->next_send_psn) & 0xffffff;
	qp_attr->dest_qp_num 	     = be32_to_cpu(context->remote_qpn) & 0xffffff;
	qp_attr->qp_access_flags     =
		to_ib_qp_access_flags(be32_to_cpu(context->params2));

	अगर (qp->transport == RC || qp->transport == UC) अणु
		to_rdma_ah_attr(dev, &qp_attr->ah_attr, &context->pri_path);
		to_rdma_ah_attr(dev, &qp_attr->alt_ah_attr, &context->alt_path);
		qp_attr->alt_pkey_index =
			be32_to_cpu(context->alt_path.port_pkey) & 0x7f;
		qp_attr->alt_port_num	=
			rdma_ah_get_port_num(&qp_attr->alt_ah_attr);
	पूर्ण

	qp_attr->pkey_index = be32_to_cpu(context->pri_path.port_pkey) & 0x7f;
	qp_attr->port_num   =
		(be32_to_cpu(context->pri_path.port_pkey) >> 24) & 0x3;

	/* qp_attr->en_sqd_async_notअगरy is only applicable in modअगरy qp */
	qp_attr->sq_draining = mthca_state == MTHCA_QP_STATE_DRAINING;

	qp_attr->max_rd_atomic = 1 << ((be32_to_cpu(context->params1) >> 21) & 0x7);

	qp_attr->max_dest_rd_atomic =
		1 << ((be32_to_cpu(context->params2) >> 21) & 0x7);
	qp_attr->min_rnr_समयr 	    =
		(be32_to_cpu(context->rnr_nextrecvpsn) >> 24) & 0x1f;
	qp_attr->समयout 	    = context->pri_path.ackto >> 3;
	qp_attr->retry_cnt 	    = (be32_to_cpu(context->params1) >> 16) & 0x7;
	qp_attr->rnr_retry 	    = context->pri_path.rnr_retry >> 5;
	qp_attr->alt_समयout 	    = context->alt_path.ackto >> 3;

करोne:
	qp_attr->cur_qp_state	     = qp_attr->qp_state;
	qp_attr->cap.max_send_wr     = qp->sq.max;
	qp_attr->cap.max_recv_wr     = qp->rq.max;
	qp_attr->cap.max_send_sge    = qp->sq.max_gs;
	qp_attr->cap.max_recv_sge    = qp->rq.max_gs;
	qp_attr->cap.max_अंतरभूत_data = qp->max_अंतरभूत_data;

	qp_init_attr->cap	     = qp_attr->cap;
	qp_init_attr->sq_sig_type    = qp->sq_policy;

out_mailbox:
	mthca_मुक्त_mailbox(dev, mailbox);

out:
	mutex_unlock(&qp->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक mthca_path_set(काष्ठा mthca_dev *dev, स्थिर काष्ठा rdma_ah_attr *ah,
			  काष्ठा mthca_qp_path *path, u8 port)
अणु
	path->g_mylmc     = rdma_ah_get_path_bits(ah) & 0x7f;
	path->rlid        = cpu_to_be16(rdma_ah_get_dlid(ah));
	path->अटल_rate = mthca_get_rate(dev, rdma_ah_get_अटल_rate(ah),
					   port);

	अगर (rdma_ah_get_ah_flags(ah) & IB_AH_GRH) अणु
		स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(ah);

		अगर (grh->sgid_index >= dev->limits.gid_table_len) अणु
			mthca_dbg(dev, "sgid_index (%u) too large. max is %d\n",
				  grh->sgid_index,
				  dev->limits.gid_table_len - 1);
			वापस -1;
		पूर्ण

		path->g_mylmc   |= 1 << 7;
		path->mgid_index = grh->sgid_index;
		path->hop_limit  = grh->hop_limit;
		path->sl_tclass_flowlabel =
			cpu_to_be32((rdma_ah_get_sl(ah) << 28) |
				    (grh->traffic_class << 20) |
				    (grh->flow_label));
		स_नकल(path->rgid, grh->dgid.raw, 16);
	पूर्ण अन्यथा अणु
		path->sl_tclass_flowlabel = cpu_to_be32(rdma_ah_get_sl(ah) <<
							28);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __mthca_modअगरy_qp(काष्ठा ib_qp *ibqp,
			     स्थिर काष्ठा ib_qp_attr *attr, पूर्णांक attr_mask,
			     क्रमागत ib_qp_state cur_state,
			     क्रमागत ib_qp_state new_state,
			     काष्ठा ib_udata *udata)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibqp->device);
	काष्ठा mthca_qp *qp = to_mqp(ibqp);
	काष्ठा mthca_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा mthca_ucontext, ibucontext);
	काष्ठा mthca_mailbox *mailbox;
	काष्ठा mthca_qp_param *qp_param;
	काष्ठा mthca_qp_context *qp_context;
	u32 sqd_event = 0;
	पूर्णांक err = -EINVAL;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox)) अणु
		err = PTR_ERR(mailbox);
		जाओ out;
	पूर्ण
	qp_param = mailbox->buf;
	qp_context = &qp_param->context;
	स_रखो(qp_param, 0, माप *qp_param);

	qp_context->flags      = cpu_to_be32((to_mthca_state(new_state) << 28) |
					     (to_mthca_st(qp->transport) << 16));
	qp_context->flags     |= cpu_to_be32(MTHCA_QP_BIT_DE);
	अगर (!(attr_mask & IB_QP_PATH_MIG_STATE))
		qp_context->flags |= cpu_to_be32(MTHCA_QP_PM_MIGRATED << 11);
	अन्यथा अणु
		qp_param->opt_param_mask |= cpu_to_be32(MTHCA_QP_OPTPAR_PM_STATE);
		चयन (attr->path_mig_state) अणु
		हाल IB_MIG_MIGRATED:
			qp_context->flags |= cpu_to_be32(MTHCA_QP_PM_MIGRATED << 11);
			अवरोध;
		हाल IB_MIG_REARM:
			qp_context->flags |= cpu_to_be32(MTHCA_QP_PM_REARM << 11);
			अवरोध;
		हाल IB_MIG_ARMED:
			qp_context->flags |= cpu_to_be32(MTHCA_QP_PM_ARMED << 11);
			अवरोध;
		पूर्ण
	पूर्ण

	/* leave tavor_sched_queue as 0 */

	अगर (qp->transport == MLX || qp->transport == UD)
		qp_context->mtu_msgmax = (IB_MTU_2048 << 5) | 11;
	अन्यथा अगर (attr_mask & IB_QP_PATH_MTU) अणु
		अगर (attr->path_mtu < IB_MTU_256 || attr->path_mtu > IB_MTU_2048) अणु
			mthca_dbg(dev, "path MTU (%u) is invalid\n",
				  attr->path_mtu);
			जाओ out_mailbox;
		पूर्ण
		qp_context->mtu_msgmax = (attr->path_mtu << 5) | 31;
	पूर्ण

	अगर (mthca_is_memमुक्त(dev)) अणु
		अगर (qp->rq.max)
			qp_context->rq_size_stride = ilog2(qp->rq.max) << 3;
		qp_context->rq_size_stride |= qp->rq.wqe_shअगरt - 4;

		अगर (qp->sq.max)
			qp_context->sq_size_stride = ilog2(qp->sq.max) << 3;
		qp_context->sq_size_stride |= qp->sq.wqe_shअगरt - 4;
	पूर्ण

	/* leave arbel_sched_queue as 0 */

	अगर (qp->ibqp.uobject)
		qp_context->usr_page = cpu_to_be32(context->uar.index);
	अन्यथा
		qp_context->usr_page = cpu_to_be32(dev->driver_uar.index);
	qp_context->local_qpn  = cpu_to_be32(qp->qpn);
	अगर (attr_mask & IB_QP_DEST_QPN) अणु
		qp_context->remote_qpn = cpu_to_be32(attr->dest_qp_num);
	पूर्ण

	अगर (qp->transport == MLX)
		qp_context->pri_path.port_pkey |=
			cpu_to_be32(qp->port << 24);
	अन्यथा अणु
		अगर (attr_mask & IB_QP_PORT) अणु
			qp_context->pri_path.port_pkey |=
				cpu_to_be32(attr->port_num << 24);
			qp_param->opt_param_mask |= cpu_to_be32(MTHCA_QP_OPTPAR_PORT_NUM);
		पूर्ण
	पूर्ण

	अगर (attr_mask & IB_QP_PKEY_INDEX) अणु
		qp_context->pri_path.port_pkey |=
			cpu_to_be32(attr->pkey_index);
		qp_param->opt_param_mask |= cpu_to_be32(MTHCA_QP_OPTPAR_PKEY_INDEX);
	पूर्ण

	अगर (attr_mask & IB_QP_RNR_RETRY) अणु
		qp_context->alt_path.rnr_retry = qp_context->pri_path.rnr_retry =
			attr->rnr_retry << 5;
		qp_param->opt_param_mask |= cpu_to_be32(MTHCA_QP_OPTPAR_RNR_RETRY |
							MTHCA_QP_OPTPAR_ALT_RNR_RETRY);
	पूर्ण

	अगर (attr_mask & IB_QP_AV) अणु
		अगर (mthca_path_set(dev, &attr->ah_attr, &qp_context->pri_path,
				   attr_mask & IB_QP_PORT ? attr->port_num : qp->port))
			जाओ out_mailbox;

		qp_param->opt_param_mask |= cpu_to_be32(MTHCA_QP_OPTPAR_PRIMARY_ADDR_PATH);
	पूर्ण

	अगर (ibqp->qp_type == IB_QPT_RC &&
	    cur_state == IB_QPS_INIT && new_state == IB_QPS_RTR) अणु
		u8 sched_queue = ibqp->uobject ? 0x2 : 0x1;

		अगर (mthca_is_memमुक्त(dev))
			qp_context->rlkey_arbel_sched_queue |= sched_queue;
		अन्यथा
			qp_context->tavor_sched_queue |= cpu_to_be32(sched_queue);

		qp_param->opt_param_mask |=
			cpu_to_be32(MTHCA_QP_OPTPAR_SCHED_QUEUE);
	पूर्ण

	अगर (attr_mask & IB_QP_TIMEOUT) अणु
		qp_context->pri_path.ackto = attr->समयout << 3;
		qp_param->opt_param_mask |= cpu_to_be32(MTHCA_QP_OPTPAR_ACK_TIMEOUT);
	पूर्ण

	अगर (attr_mask & IB_QP_ALT_PATH) अणु
		अगर (attr->alt_pkey_index >= dev->limits.pkey_table_len) अणु
			mthca_dbg(dev, "Alternate P_Key index (%u) too large. max is %d\n",
				  attr->alt_pkey_index, dev->limits.pkey_table_len-1);
			जाओ out_mailbox;
		पूर्ण

		अगर (attr->alt_port_num == 0 || attr->alt_port_num > dev->limits.num_ports) अणु
			mthca_dbg(dev, "Alternate port number (%u) is invalid\n",
				attr->alt_port_num);
			जाओ out_mailbox;
		पूर्ण

		अगर (mthca_path_set(dev, &attr->alt_ah_attr, &qp_context->alt_path,
				   rdma_ah_get_port_num(&attr->alt_ah_attr)))
			जाओ out_mailbox;

		qp_context->alt_path.port_pkey |= cpu_to_be32(attr->alt_pkey_index |
							      attr->alt_port_num << 24);
		qp_context->alt_path.ackto = attr->alt_समयout << 3;
		qp_param->opt_param_mask |= cpu_to_be32(MTHCA_QP_OPTPAR_ALT_ADDR_PATH);
	पूर्ण

	/* leave rdd as 0 */
	qp_context->pd         = cpu_to_be32(to_mpd(ibqp->pd)->pd_num);
	/* leave wqe_base as 0 (we always create an MR based at 0 क्रम WQs) */
	qp_context->wqe_lkey   = cpu_to_be32(qp->mr.ibmr.lkey);
	qp_context->params1    = cpu_to_be32((MTHCA_ACK_REQ_FREQ << 28) |
					     (MTHCA_FLIGHT_LIMIT << 24) |
					     MTHCA_QP_BIT_SWE);
	अगर (qp->sq_policy == IB_SIGNAL_ALL_WR)
		qp_context->params1 |= cpu_to_be32(MTHCA_QP_BIT_SSC);
	अगर (attr_mask & IB_QP_RETRY_CNT) अणु
		qp_context->params1 |= cpu_to_be32(attr->retry_cnt << 16);
		qp_param->opt_param_mask |= cpu_to_be32(MTHCA_QP_OPTPAR_RETRY_COUNT);
	पूर्ण

	अगर (attr_mask & IB_QP_MAX_QP_RD_ATOMIC) अणु
		अगर (attr->max_rd_atomic) अणु
			qp_context->params1 |=
				cpu_to_be32(MTHCA_QP_BIT_SRE |
					    MTHCA_QP_BIT_SAE);
			qp_context->params1 |=
				cpu_to_be32(fls(attr->max_rd_atomic - 1) << 21);
		पूर्ण
		qp_param->opt_param_mask |= cpu_to_be32(MTHCA_QP_OPTPAR_SRA_MAX);
	पूर्ण

	अगर (attr_mask & IB_QP_SQ_PSN)
		qp_context->next_send_psn = cpu_to_be32(attr->sq_psn);
	qp_context->cqn_snd = cpu_to_be32(to_mcq(ibqp->send_cq)->cqn);

	अगर (mthca_is_memमुक्त(dev)) अणु
		qp_context->snd_wqe_base_l = cpu_to_be32(qp->send_wqe_offset);
		qp_context->snd_db_index   = cpu_to_be32(qp->sq.db_index);
	पूर्ण

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC) अणु
		अगर (attr->max_dest_rd_atomic)
			qp_context->params2 |=
				cpu_to_be32(fls(attr->max_dest_rd_atomic - 1) << 21);

		qp_param->opt_param_mask |= cpu_to_be32(MTHCA_QP_OPTPAR_RRA_MAX);
	पूर्ण

	अगर (attr_mask & (IB_QP_ACCESS_FLAGS | IB_QP_MAX_DEST_RD_ATOMIC)) अणु
		qp_context->params2      |= get_hw_access_flags(qp, attr, attr_mask);
		qp_param->opt_param_mask |= cpu_to_be32(MTHCA_QP_OPTPAR_RWE |
							MTHCA_QP_OPTPAR_RRE |
							MTHCA_QP_OPTPAR_RAE);
	पूर्ण

	qp_context->params2 |= cpu_to_be32(MTHCA_QP_BIT_RSC);

	अगर (ibqp->srq)
		qp_context->params2 |= cpu_to_be32(MTHCA_QP_BIT_RIC);

	अगर (attr_mask & IB_QP_MIN_RNR_TIMER) अणु
		qp_context->rnr_nextrecvpsn |= cpu_to_be32(attr->min_rnr_समयr << 24);
		qp_param->opt_param_mask |= cpu_to_be32(MTHCA_QP_OPTPAR_RNR_TIMEOUT);
	पूर्ण
	अगर (attr_mask & IB_QP_RQ_PSN)
		qp_context->rnr_nextrecvpsn |= cpu_to_be32(attr->rq_psn);

	qp_context->ra_buff_indx =
		cpu_to_be32(dev->qp_table.rdb_base +
			    ((qp->qpn & (dev->limits.num_qps - 1)) * MTHCA_RDB_ENTRY_SIZE <<
			     dev->qp_table.rdb_shअगरt));

	qp_context->cqn_rcv = cpu_to_be32(to_mcq(ibqp->recv_cq)->cqn);

	अगर (mthca_is_memमुक्त(dev))
		qp_context->rcv_db_index   = cpu_to_be32(qp->rq.db_index);

	अगर (attr_mask & IB_QP_QKEY) अणु
		qp_context->qkey = cpu_to_be32(attr->qkey);
		qp_param->opt_param_mask |= cpu_to_be32(MTHCA_QP_OPTPAR_Q_KEY);
	पूर्ण

	अगर (ibqp->srq)
		qp_context->srqn = cpu_to_be32(1 << 24 |
					       to_msrq(ibqp->srq)->srqn);

	अगर (cur_state == IB_QPS_RTS && new_state == IB_QPS_SQD	&&
	    attr_mask & IB_QP_EN_SQD_ASYNC_NOTIFY		&&
	    attr->en_sqd_async_notअगरy)
		sqd_event = 1 << 31;

	err = mthca_MODIFY_QP(dev, cur_state, new_state, qp->qpn, 0,
			      mailbox, sqd_event);
	अगर (err) अणु
		mthca_warn(dev, "modify QP %d->%d returned %d.\n",
			   cur_state, new_state, err);
		जाओ out_mailbox;
	पूर्ण

	qp->state = new_state;
	अगर (attr_mask & IB_QP_ACCESS_FLAGS)
		qp->atomic_rd_en = attr->qp_access_flags;
	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC)
		qp->resp_depth = attr->max_dest_rd_atomic;
	अगर (attr_mask & IB_QP_PORT)
		qp->port = attr->port_num;
	अगर (attr_mask & IB_QP_ALT_PATH)
		qp->alt_port = attr->alt_port_num;

	अगर (is_sqp(dev, qp))
		store_attrs(qp->sqp, attr, attr_mask);

	/*
	 * If we moved QP0 to RTR, bring the IB link up; अगर we moved
	 * QP0 to RESET or ERROR, bring the link back करोwn.
	 */
	अगर (is_qp0(dev, qp)) अणु
		अगर (cur_state != IB_QPS_RTR &&
		    new_state == IB_QPS_RTR)
			init_port(dev, qp->port);

		अगर (cur_state != IB_QPS_RESET &&
		    cur_state != IB_QPS_ERR &&
		    (new_state == IB_QPS_RESET ||
		     new_state == IB_QPS_ERR))
			mthca_CLOSE_IB(dev, qp->port);
	पूर्ण

	/*
	 * If we moved a kernel QP to RESET, clean up all old CQ
	 * entries and reinitialize the QP.
	 */
	अगर (new_state == IB_QPS_RESET && !qp->ibqp.uobject) अणु
		mthca_cq_clean(dev, to_mcq(qp->ibqp.recv_cq), qp->qpn,
			       qp->ibqp.srq ? to_msrq(qp->ibqp.srq) : शून्य);
		अगर (qp->ibqp.send_cq != qp->ibqp.recv_cq)
			mthca_cq_clean(dev, to_mcq(qp->ibqp.send_cq), qp->qpn, शून्य);

		mthca_wq_reset(&qp->sq);
		qp->sq.last = get_send_wqe(qp, qp->sq.max - 1);

		mthca_wq_reset(&qp->rq);
		qp->rq.last = get_recv_wqe(qp, qp->rq.max - 1);

		अगर (mthca_is_memमुक्त(dev)) अणु
			*qp->sq.db = 0;
			*qp->rq.db = 0;
		पूर्ण
	पूर्ण

out_mailbox:
	mthca_मुक्त_mailbox(dev, mailbox);
out:
	वापस err;
पूर्ण

पूर्णांक mthca_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr, पूर्णांक attr_mask,
		    काष्ठा ib_udata *udata)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibqp->device);
	काष्ठा mthca_qp *qp = to_mqp(ibqp);
	क्रमागत ib_qp_state cur_state, new_state;
	पूर्णांक err = -EINVAL;

	अगर (attr_mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	mutex_lock(&qp->mutex);
	अगर (attr_mask & IB_QP_CUR_STATE) अणु
		cur_state = attr->cur_qp_state;
	पूर्ण अन्यथा अणु
		spin_lock_irq(&qp->sq.lock);
		spin_lock(&qp->rq.lock);
		cur_state = qp->state;
		spin_unlock(&qp->rq.lock);
		spin_unlock_irq(&qp->sq.lock);
	पूर्ण

	new_state = attr_mask & IB_QP_STATE ? attr->qp_state : cur_state;

	अगर (!ib_modअगरy_qp_is_ok(cur_state, new_state, ibqp->qp_type,
				attr_mask)) अणु
		mthca_dbg(dev, "Bad QP transition (transport %d) "
			  "%d->%d with attr 0x%08x\n",
			  qp->transport, cur_state, new_state,
			  attr_mask);
		जाओ out;
	पूर्ण

	अगर ((attr_mask & IB_QP_PKEY_INDEX) &&
	     attr->pkey_index >= dev->limits.pkey_table_len) अणु
		mthca_dbg(dev, "P_Key index (%u) too large. max is %d\n",
			  attr->pkey_index, dev->limits.pkey_table_len-1);
		जाओ out;
	पूर्ण

	अगर ((attr_mask & IB_QP_PORT) &&
	    (attr->port_num == 0 || attr->port_num > dev->limits.num_ports)) अणु
		mthca_dbg(dev, "Port number (%u) is invalid\n", attr->port_num);
		जाओ out;
	पूर्ण

	अगर (attr_mask & IB_QP_MAX_QP_RD_ATOMIC &&
	    attr->max_rd_atomic > dev->limits.max_qp_init_rdma) अणु
		mthca_dbg(dev, "Max rdma_atomic as initiator %u too large (max is %d)\n",
			  attr->max_rd_atomic, dev->limits.max_qp_init_rdma);
		जाओ out;
	पूर्ण

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC &&
	    attr->max_dest_rd_atomic > 1 << dev->qp_table.rdb_shअगरt) अणु
		mthca_dbg(dev, "Max rdma_atomic as responder %u too large (max %d)\n",
			  attr->max_dest_rd_atomic, 1 << dev->qp_table.rdb_shअगरt);
		जाओ out;
	पूर्ण

	अगर (cur_state == new_state && cur_state == IB_QPS_RESET) अणु
		err = 0;
		जाओ out;
	पूर्ण

	err = __mthca_modअगरy_qp(ibqp, attr, attr_mask, cur_state, new_state,
				udata);

out:
	mutex_unlock(&qp->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक mthca_max_data_size(काष्ठा mthca_dev *dev, काष्ठा mthca_qp *qp, पूर्णांक desc_sz)
अणु
	/*
	 * Calculate the maximum size of WQE s/g segments, excluding
	 * the next segment and other non-data segments.
	 */
	पूर्णांक max_data_size = desc_sz - माप (काष्ठा mthca_next_seg);

	चयन (qp->transport) अणु
	हाल MLX:
		max_data_size -= 2 * माप (काष्ठा mthca_data_seg);
		अवरोध;

	हाल UD:
		अगर (mthca_is_memमुक्त(dev))
			max_data_size -= माप (काष्ठा mthca_arbel_ud_seg);
		अन्यथा
			max_data_size -= माप (काष्ठा mthca_tavor_ud_seg);
		अवरोध;

	शेष:
		max_data_size -= माप (काष्ठा mthca_raddr_seg);
		अवरोध;
	पूर्ण

	वापस max_data_size;
पूर्ण

अटल अंतरभूत पूर्णांक mthca_max_अंतरभूत_data(काष्ठा mthca_pd *pd, पूर्णांक max_data_size)
अणु
	/* We करोn't support अंतरभूत data क्रम kernel QPs (yet). */
	वापस pd->ibpd.uobject ? max_data_size - MTHCA_INLINE_HEADER_SIZE : 0;
पूर्ण

अटल व्योम mthca_adjust_qp_caps(काष्ठा mthca_dev *dev,
				 काष्ठा mthca_pd *pd,
				 काष्ठा mthca_qp *qp)
अणु
	पूर्णांक max_data_size = mthca_max_data_size(dev, qp,
						min(dev->limits.max_desc_sz,
						    1 << qp->sq.wqe_shअगरt));

	qp->max_अंतरभूत_data = mthca_max_अंतरभूत_data(pd, max_data_size);

	qp->sq.max_gs = min_t(पूर्णांक, dev->limits.max_sg,
			      max_data_size / माप (काष्ठा mthca_data_seg));
	qp->rq.max_gs = min_t(पूर्णांक, dev->limits.max_sg,
			       (min(dev->limits.max_desc_sz, 1 << qp->rq.wqe_shअगरt) -
				माप (काष्ठा mthca_next_seg)) /
			       माप (काष्ठा mthca_data_seg));
पूर्ण

/*
 * Allocate and रेजिस्टर buffer क्रम WQEs.  qp->rq.max, sq.max,
 * rq.max_gs and sq.max_gs must all be asचिन्हित.
 * mthca_alloc_wqe_buf will calculate rq.wqe_shअगरt and
 * sq.wqe_shअगरt (as well as send_wqe_offset, is_direct, and
 * queue)
 */
अटल पूर्णांक mthca_alloc_wqe_buf(काष्ठा mthca_dev *dev,
			       काष्ठा mthca_pd *pd,
			       काष्ठा mthca_qp *qp,
			       काष्ठा ib_udata *udata)
अणु
	पूर्णांक size;
	पूर्णांक err = -ENOMEM;

	size = माप (काष्ठा mthca_next_seg) +
		qp->rq.max_gs * माप (काष्ठा mthca_data_seg);

	अगर (size > dev->limits.max_desc_sz)
		वापस -EINVAL;

	क्रम (qp->rq.wqe_shअगरt = 6; 1 << qp->rq.wqe_shअगरt < size;
	     qp->rq.wqe_shअगरt++)
		; /* nothing */

	size = qp->sq.max_gs * माप (काष्ठा mthca_data_seg);
	चयन (qp->transport) अणु
	हाल MLX:
		size += 2 * माप (काष्ठा mthca_data_seg);
		अवरोध;

	हाल UD:
		size += mthca_is_memमुक्त(dev) ?
			माप (काष्ठा mthca_arbel_ud_seg) :
			माप (काष्ठा mthca_tavor_ud_seg);
		अवरोध;

	हाल UC:
		size += माप (काष्ठा mthca_raddr_seg);
		अवरोध;

	हाल RC:
		size += माप (काष्ठा mthca_raddr_seg);
		/*
		 * An atomic op will require an atomic segment, a
		 * remote address segment and one scatter entry.
		 */
		size = max_t(पूर्णांक, size,
			     माप (काष्ठा mthca_atomic_seg) +
			     माप (काष्ठा mthca_raddr_seg) +
			     माप (काष्ठा mthca_data_seg));
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/* Make sure that we have enough space क्रम a bind request */
	size = max_t(पूर्णांक, size, माप (काष्ठा mthca_bind_seg));

	size += माप (काष्ठा mthca_next_seg);

	अगर (size > dev->limits.max_desc_sz)
		वापस -EINVAL;

	क्रम (qp->sq.wqe_shअगरt = 6; 1 << qp->sq.wqe_shअगरt < size;
	     qp->sq.wqe_shअगरt++)
		; /* nothing */

	qp->send_wqe_offset = ALIGN(qp->rq.max << qp->rq.wqe_shअगरt,
				    1 << qp->sq.wqe_shअगरt);

	/*
	 * If this is a userspace QP, we करोn't actually have to
	 * allocate anything.  All we need is to calculate the WQE
	 * sizes and the send_wqe_offset, so we're करोne now.
	 */
	अगर (udata)
		वापस 0;

	size = PAGE_ALIGN(qp->send_wqe_offset +
			  (qp->sq.max << qp->sq.wqe_shअगरt));

	qp->wrid = kदो_स्मृति_array(qp->rq.max + qp->sq.max, माप(u64),
				 GFP_KERNEL);
	अगर (!qp->wrid)
		जाओ err_out;

	err = mthca_buf_alloc(dev, size, MTHCA_MAX_सूचीECT_QP_SIZE,
			      &qp->queue, &qp->is_direct, pd, 0, &qp->mr);
	अगर (err)
		जाओ err_out;

	वापस 0;

err_out:
	kमुक्त(qp->wrid);
	वापस err;
पूर्ण

अटल व्योम mthca_मुक्त_wqe_buf(काष्ठा mthca_dev *dev,
			       काष्ठा mthca_qp *qp)
अणु
	mthca_buf_मुक्त(dev, PAGE_ALIGN(qp->send_wqe_offset +
				       (qp->sq.max << qp->sq.wqe_shअगरt)),
		       &qp->queue, qp->is_direct, &qp->mr);
	kमुक्त(qp->wrid);
पूर्ण

अटल पूर्णांक mthca_map_memमुक्त(काष्ठा mthca_dev *dev,
			     काष्ठा mthca_qp *qp)
अणु
	पूर्णांक ret;

	अगर (mthca_is_memमुक्त(dev)) अणु
		ret = mthca_table_get(dev, dev->qp_table.qp_table, qp->qpn);
		अगर (ret)
			वापस ret;

		ret = mthca_table_get(dev, dev->qp_table.eqp_table, qp->qpn);
		अगर (ret)
			जाओ err_qpc;

		ret = mthca_table_get(dev, dev->qp_table.rdb_table,
				      qp->qpn << dev->qp_table.rdb_shअगरt);
		अगर (ret)
			जाओ err_eqpc;

	पूर्ण

	वापस 0;

err_eqpc:
	mthca_table_put(dev, dev->qp_table.eqp_table, qp->qpn);

err_qpc:
	mthca_table_put(dev, dev->qp_table.qp_table, qp->qpn);

	वापस ret;
पूर्ण

अटल व्योम mthca_unmap_memमुक्त(काष्ठा mthca_dev *dev,
				काष्ठा mthca_qp *qp)
अणु
	mthca_table_put(dev, dev->qp_table.rdb_table,
			qp->qpn << dev->qp_table.rdb_shअगरt);
	mthca_table_put(dev, dev->qp_table.eqp_table, qp->qpn);
	mthca_table_put(dev, dev->qp_table.qp_table, qp->qpn);
पूर्ण

अटल पूर्णांक mthca_alloc_memमुक्त(काष्ठा mthca_dev *dev,
			       काष्ठा mthca_qp *qp)
अणु
	अगर (mthca_is_memमुक्त(dev)) अणु
		qp->rq.db_index = mthca_alloc_db(dev, MTHCA_DB_TYPE_RQ,
						 qp->qpn, &qp->rq.db);
		अगर (qp->rq.db_index < 0)
			वापस -ENOMEM;

		qp->sq.db_index = mthca_alloc_db(dev, MTHCA_DB_TYPE_SQ,
						 qp->qpn, &qp->sq.db);
		अगर (qp->sq.db_index < 0) अणु
			mthca_मुक्त_db(dev, MTHCA_DB_TYPE_RQ, qp->rq.db_index);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mthca_मुक्त_memमुक्त(काष्ठा mthca_dev *dev,
			       काष्ठा mthca_qp *qp)
अणु
	अगर (mthca_is_memमुक्त(dev)) अणु
		mthca_मुक्त_db(dev, MTHCA_DB_TYPE_SQ, qp->sq.db_index);
		mthca_मुक्त_db(dev, MTHCA_DB_TYPE_RQ, qp->rq.db_index);
	पूर्ण
पूर्ण

अटल पूर्णांक mthca_alloc_qp_common(काष्ठा mthca_dev *dev,
				 काष्ठा mthca_pd *pd,
				 काष्ठा mthca_cq *send_cq,
				 काष्ठा mthca_cq *recv_cq,
				 क्रमागत ib_sig_type send_policy,
				 काष्ठा mthca_qp *qp,
				 काष्ठा ib_udata *udata)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा mthca_next_seg *next;

	qp->refcount = 1;
	init_रुकोqueue_head(&qp->रुको);
	mutex_init(&qp->mutex);
	qp->state    	 = IB_QPS_RESET;
	qp->atomic_rd_en = 0;
	qp->resp_depth   = 0;
	qp->sq_policy    = send_policy;
	mthca_wq_reset(&qp->sq);
	mthca_wq_reset(&qp->rq);

	spin_lock_init(&qp->sq.lock);
	spin_lock_init(&qp->rq.lock);

	ret = mthca_map_memमुक्त(dev, qp);
	अगर (ret)
		वापस ret;

	ret = mthca_alloc_wqe_buf(dev, pd, qp, udata);
	अगर (ret) अणु
		mthca_unmap_memमुक्त(dev, qp);
		वापस ret;
	पूर्ण

	mthca_adjust_qp_caps(dev, pd, qp);

	/*
	 * If this is a userspace QP, we're करोne now.  The करोorbells
	 * will be allocated and buffers will be initialized in
	 * userspace.
	 */
	अगर (udata)
		वापस 0;

	ret = mthca_alloc_memमुक्त(dev, qp);
	अगर (ret) अणु
		mthca_मुक्त_wqe_buf(dev, qp);
		mthca_unmap_memमुक्त(dev, qp);
		वापस ret;
	पूर्ण

	अगर (mthca_is_memमुक्त(dev)) अणु
		काष्ठा mthca_data_seg *scatter;
		पूर्णांक size = (माप (काष्ठा mthca_next_seg) +
			    qp->rq.max_gs * माप (काष्ठा mthca_data_seg)) / 16;

		क्रम (i = 0; i < qp->rq.max; ++i) अणु
			next = get_recv_wqe(qp, i);
			next->nda_op = cpu_to_be32(((i + 1) & (qp->rq.max - 1)) <<
						   qp->rq.wqe_shअगरt);
			next->ee_nds = cpu_to_be32(size);

			क्रम (scatter = (व्योम *) (next + 1);
			     (व्योम *) scatter < (व्योम *) next + (1 << qp->rq.wqe_shअगरt);
			     ++scatter)
				scatter->lkey = cpu_to_be32(MTHCA_INVAL_LKEY);
		पूर्ण

		क्रम (i = 0; i < qp->sq.max; ++i) अणु
			next = get_send_wqe(qp, i);
			next->nda_op = cpu_to_be32((((i + 1) & (qp->sq.max - 1)) <<
						    qp->sq.wqe_shअगरt) +
						   qp->send_wqe_offset);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < qp->rq.max; ++i) अणु
			next = get_recv_wqe(qp, i);
			next->nda_op = htonl((((i + 1) % qp->rq.max) <<
					      qp->rq.wqe_shअगरt) | 1);
		पूर्ण

	पूर्ण

	qp->sq.last = get_send_wqe(qp, qp->sq.max - 1);
	qp->rq.last = get_recv_wqe(qp, qp->rq.max - 1);

	वापस 0;
पूर्ण

अटल पूर्णांक mthca_set_qp_size(काष्ठा mthca_dev *dev, काष्ठा ib_qp_cap *cap,
			     काष्ठा mthca_pd *pd, काष्ठा mthca_qp *qp)
अणु
	पूर्णांक max_data_size = mthca_max_data_size(dev, qp, dev->limits.max_desc_sz);

	/* Sanity check QP size beक्रमe proceeding */
	अगर (cap->max_send_wr  	 > dev->limits.max_wqes ||
	    cap->max_recv_wr  	 > dev->limits.max_wqes ||
	    cap->max_send_sge 	 > dev->limits.max_sg   ||
	    cap->max_recv_sge 	 > dev->limits.max_sg   ||
	    cap->max_अंतरभूत_data > mthca_max_अंतरभूत_data(pd, max_data_size))
		वापस -EINVAL;

	/*
	 * For MLX transport we need 2 extra send gather entries:
	 * one क्रम the header and one क्रम the checksum at the end
	 */
	अगर (qp->transport == MLX && cap->max_send_sge + 2 > dev->limits.max_sg)
		वापस -EINVAL;

	अगर (mthca_is_memमुक्त(dev)) अणु
		qp->rq.max = cap->max_recv_wr ?
			roundup_घात_of_two(cap->max_recv_wr) : 0;
		qp->sq.max = cap->max_send_wr ?
			roundup_घात_of_two(cap->max_send_wr) : 0;
	पूर्ण अन्यथा अणु
		qp->rq.max = cap->max_recv_wr;
		qp->sq.max = cap->max_send_wr;
	पूर्ण

	qp->rq.max_gs = cap->max_recv_sge;
	qp->sq.max_gs = max_t(पूर्णांक, cap->max_send_sge,
			      ALIGN(cap->max_अंतरभूत_data + MTHCA_INLINE_HEADER_SIZE,
				    MTHCA_INLINE_CHUNK_SIZE) /
			      माप (काष्ठा mthca_data_seg));

	वापस 0;
पूर्ण

पूर्णांक mthca_alloc_qp(काष्ठा mthca_dev *dev,
		   काष्ठा mthca_pd *pd,
		   काष्ठा mthca_cq *send_cq,
		   काष्ठा mthca_cq *recv_cq,
		   क्रमागत ib_qp_type type,
		   क्रमागत ib_sig_type send_policy,
		   काष्ठा ib_qp_cap *cap,
		   काष्ठा mthca_qp *qp,
		   काष्ठा ib_udata *udata)
अणु
	पूर्णांक err;

	चयन (type) अणु
	हाल IB_QPT_RC: qp->transport = RC; अवरोध;
	हाल IB_QPT_UC: qp->transport = UC; अवरोध;
	हाल IB_QPT_UD: qp->transport = UD; अवरोध;
	शेष: वापस -EINVAL;
	पूर्ण

	err = mthca_set_qp_size(dev, cap, pd, qp);
	अगर (err)
		वापस err;

	qp->qpn = mthca_alloc(&dev->qp_table.alloc);
	अगर (qp->qpn == -1)
		वापस -ENOMEM;

	/* initialize port to zero क्रम error-catching. */
	qp->port = 0;

	err = mthca_alloc_qp_common(dev, pd, send_cq, recv_cq,
				    send_policy, qp, udata);
	अगर (err) अणु
		mthca_मुक्त(&dev->qp_table.alloc, qp->qpn);
		वापस err;
	पूर्ण

	spin_lock_irq(&dev->qp_table.lock);
	mthca_array_set(&dev->qp_table.qp,
			qp->qpn & (dev->limits.num_qps - 1), qp);
	spin_unlock_irq(&dev->qp_table.lock);

	वापस 0;
पूर्ण

अटल व्योम mthca_lock_cqs(काष्ठा mthca_cq *send_cq, काष्ठा mthca_cq *recv_cq)
	__acquires(&send_cq->lock) __acquires(&recv_cq->lock)
अणु
	अगर (send_cq == recv_cq) अणु
		spin_lock_irq(&send_cq->lock);
		__acquire(&recv_cq->lock);
	पूर्ण अन्यथा अगर (send_cq->cqn < recv_cq->cqn) अणु
		spin_lock_irq(&send_cq->lock);
		spin_lock_nested(&recv_cq->lock, SINGLE_DEPTH_NESTING);
	पूर्ण अन्यथा अणु
		spin_lock_irq(&recv_cq->lock);
		spin_lock_nested(&send_cq->lock, SINGLE_DEPTH_NESTING);
	पूर्ण
पूर्ण

अटल व्योम mthca_unlock_cqs(काष्ठा mthca_cq *send_cq, काष्ठा mthca_cq *recv_cq)
	__releases(&send_cq->lock) __releases(&recv_cq->lock)
अणु
	अगर (send_cq == recv_cq) अणु
		__release(&recv_cq->lock);
		spin_unlock_irq(&send_cq->lock);
	पूर्ण अन्यथा अगर (send_cq->cqn < recv_cq->cqn) अणु
		spin_unlock(&recv_cq->lock);
		spin_unlock_irq(&send_cq->lock);
	पूर्ण अन्यथा अणु
		spin_unlock(&send_cq->lock);
		spin_unlock_irq(&recv_cq->lock);
	पूर्ण
पूर्ण

पूर्णांक mthca_alloc_sqp(काष्ठा mthca_dev *dev,
		    काष्ठा mthca_pd *pd,
		    काष्ठा mthca_cq *send_cq,
		    काष्ठा mthca_cq *recv_cq,
		    क्रमागत ib_sig_type send_policy,
		    काष्ठा ib_qp_cap *cap,
		    पूर्णांक qpn,
		    u32 port,
		    काष्ठा mthca_qp *qp,
		    काष्ठा ib_udata *udata)
अणु
	u32 mqpn = qpn * 2 + dev->qp_table.sqp_start + port - 1;
	पूर्णांक err;

	qp->transport = MLX;
	err = mthca_set_qp_size(dev, cap, pd, qp);
	अगर (err)
		वापस err;

	qp->sqp->header_buf_size = qp->sq.max * MTHCA_UD_HEADER_SIZE;
	qp->sqp->header_buf =
		dma_alloc_coherent(&dev->pdev->dev, qp->sqp->header_buf_size,
				   &qp->sqp->header_dma, GFP_KERNEL);
	अगर (!qp->sqp->header_buf)
		वापस -ENOMEM;

	spin_lock_irq(&dev->qp_table.lock);
	अगर (mthca_array_get(&dev->qp_table.qp, mqpn))
		err = -EBUSY;
	अन्यथा
		mthca_array_set(&dev->qp_table.qp, mqpn, qp->sqp);
	spin_unlock_irq(&dev->qp_table.lock);

	अगर (err)
		जाओ err_out;

	qp->port      = port;
	qp->qpn       = mqpn;
	qp->transport = MLX;

	err = mthca_alloc_qp_common(dev, pd, send_cq, recv_cq,
				    send_policy, qp, udata);
	अगर (err)
		जाओ err_out_मुक्त;

	atomic_inc(&pd->sqp_count);

	वापस 0;

 err_out_मुक्त:
	/*
	 * Lock CQs here, so that CQ polling code can करो QP lookup
	 * without taking a lock.
	 */
	mthca_lock_cqs(send_cq, recv_cq);

	spin_lock(&dev->qp_table.lock);
	mthca_array_clear(&dev->qp_table.qp, mqpn);
	spin_unlock(&dev->qp_table.lock);

	mthca_unlock_cqs(send_cq, recv_cq);

err_out:
	dma_मुक्त_coherent(&dev->pdev->dev, qp->sqp->header_buf_size,
			  qp->sqp->header_buf, qp->sqp->header_dma);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक get_qp_refcount(काष्ठा mthca_dev *dev, काष्ठा mthca_qp *qp)
अणु
	पूर्णांक c;

	spin_lock_irq(&dev->qp_table.lock);
	c = qp->refcount;
	spin_unlock_irq(&dev->qp_table.lock);

	वापस c;
पूर्ण

व्योम mthca_मुक्त_qp(काष्ठा mthca_dev *dev,
		   काष्ठा mthca_qp *qp)
अणु
	काष्ठा mthca_cq *send_cq;
	काष्ठा mthca_cq *recv_cq;

	send_cq = to_mcq(qp->ibqp.send_cq);
	recv_cq = to_mcq(qp->ibqp.recv_cq);

	/*
	 * Lock CQs here, so that CQ polling code can करो QP lookup
	 * without taking a lock.
	 */
	mthca_lock_cqs(send_cq, recv_cq);

	spin_lock(&dev->qp_table.lock);
	mthca_array_clear(&dev->qp_table.qp,
			  qp->qpn & (dev->limits.num_qps - 1));
	--qp->refcount;
	spin_unlock(&dev->qp_table.lock);

	mthca_unlock_cqs(send_cq, recv_cq);

	रुको_event(qp->रुको, !get_qp_refcount(dev, qp));

	अगर (qp->state != IB_QPS_RESET)
		mthca_MODIFY_QP(dev, qp->state, IB_QPS_RESET, qp->qpn, 0,
				शून्य, 0);

	/*
	 * If this is a userspace QP, the buffers, MR, CQs and so on
	 * will be cleaned up in userspace, so all we have to करो is
	 * unref the mem-मुक्त tables and मुक्त the QPN in our table.
	 */
	अगर (!qp->ibqp.uobject) अणु
		mthca_cq_clean(dev, recv_cq, qp->qpn,
			       qp->ibqp.srq ? to_msrq(qp->ibqp.srq) : शून्य);
		अगर (send_cq != recv_cq)
			mthca_cq_clean(dev, send_cq, qp->qpn, शून्य);

		mthca_मुक्त_memमुक्त(dev, qp);
		mthca_मुक्त_wqe_buf(dev, qp);
	पूर्ण

	mthca_unmap_memमुक्त(dev, qp);

	अगर (is_sqp(dev, qp)) अणु
		atomic_dec(&(to_mpd(qp->ibqp.pd)->sqp_count));
		dma_मुक्त_coherent(&dev->pdev->dev, qp->sqp->header_buf_size,
				  qp->sqp->header_buf, qp->sqp->header_dma);
	पूर्ण अन्यथा
		mthca_मुक्त(&dev->qp_table.alloc, qp->qpn);
पूर्ण

/* Create UD header क्रम an MLX send and build a data segment क्रम it */
अटल पूर्णांक build_mlx_header(काष्ठा mthca_dev *dev, काष्ठा mthca_qp *qp, पूर्णांक ind,
			    स्थिर काष्ठा ib_ud_wr *wr,
			    काष्ठा mthca_mlx_seg *mlx,
			    काष्ठा mthca_data_seg *data)
अणु
	काष्ठा mthca_sqp *sqp = qp->sqp;
	पूर्णांक header_size;
	पूर्णांक err;
	u16 pkey;

	ib_ud_header_init(256, /* assume a MAD */ 1, 0, 0,
			  mthca_ah_grh_present(to_mah(wr->ah)), 0, 0, 0,
			  &sqp->ud_header);

	err = mthca_पढ़ो_ah(dev, to_mah(wr->ah), &sqp->ud_header);
	अगर (err)
		वापस err;
	mlx->flags &= ~cpu_to_be32(MTHCA_NEXT_SOLICIT | 1);
	mlx->flags |= cpu_to_be32((!qp->ibqp.qp_num ? MTHCA_MLX_VL15 : 0) |
				  (sqp->ud_header.lrh.destination_lid ==
				   IB_LID_PERMISSIVE ? MTHCA_MLX_SLR : 0) |
				  (sqp->ud_header.lrh.service_level << 8));
	mlx->rlid = sqp->ud_header.lrh.destination_lid;
	mlx->vcrc = 0;

	चयन (wr->wr.opcode) अणु
	हाल IB_WR_SEND:
		sqp->ud_header.bth.opcode = IB_OPCODE_UD_SEND_ONLY;
		sqp->ud_header.immediate_present = 0;
		अवरोध;
	हाल IB_WR_SEND_WITH_IMM:
		sqp->ud_header.bth.opcode = IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE;
		sqp->ud_header.immediate_present = 1;
		sqp->ud_header.immediate_data = wr->wr.ex.imm_data;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	sqp->ud_header.lrh.भव_lane    = !qp->ibqp.qp_num ? 15 : 0;
	अगर (sqp->ud_header.lrh.destination_lid == IB_LID_PERMISSIVE)
		sqp->ud_header.lrh.source_lid = IB_LID_PERMISSIVE;
	sqp->ud_header.bth.solicited_event = !!(wr->wr.send_flags & IB_SEND_SOLICITED);
	अगर (!qp->ibqp.qp_num)
		ib_get_cached_pkey(&dev->ib_dev, qp->port, sqp->pkey_index,
				   &pkey);
	अन्यथा
		ib_get_cached_pkey(&dev->ib_dev, qp->port, wr->pkey_index,
				   &pkey);
	sqp->ud_header.bth.pkey = cpu_to_be16(pkey);
	sqp->ud_header.bth.destination_qpn = cpu_to_be32(wr->remote_qpn);
	sqp->ud_header.bth.psn = cpu_to_be32((sqp->send_psn++) & ((1 << 24) - 1));
	sqp->ud_header.deth.qkey = cpu_to_be32(wr->remote_qkey & 0x80000000 ?
					       sqp->qkey : wr->remote_qkey);
	sqp->ud_header.deth.source_qpn = cpu_to_be32(qp->ibqp.qp_num);

	header_size = ib_ud_header_pack(&sqp->ud_header,
					sqp->header_buf +
					ind * MTHCA_UD_HEADER_SIZE);

	data->byte_count = cpu_to_be32(header_size);
	data->lkey       = cpu_to_be32(to_mpd(qp->ibqp.pd)->nपंचांगr.ibmr.lkey);
	data->addr       = cpu_to_be64(sqp->header_dma +
				       ind * MTHCA_UD_HEADER_SIZE);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mthca_wq_overflow(काष्ठा mthca_wq *wq, पूर्णांक nreq,
				    काष्ठा ib_cq *ib_cq)
अणु
	अचिन्हित cur;
	काष्ठा mthca_cq *cq;

	cur = wq->head - wq->tail;
	अगर (likely(cur + nreq < wq->max))
		वापस 0;

	cq = to_mcq(ib_cq);
	spin_lock(&cq->lock);
	cur = wq->head - wq->tail;
	spin_unlock(&cq->lock);

	वापस cur + nreq >= wq->max;
पूर्ण

अटल __always_अंतरभूत व्योम set_raddr_seg(काष्ठा mthca_raddr_seg *rseg,
					  u64 remote_addr, u32 rkey)
अणु
	rseg->raddr    = cpu_to_be64(remote_addr);
	rseg->rkey     = cpu_to_be32(rkey);
	rseg->reserved = 0;
पूर्ण

अटल __always_अंतरभूत व्योम set_atomic_seg(काष्ठा mthca_atomic_seg *aseg,
					   स्थिर काष्ठा ib_atomic_wr *wr)
अणु
	अगर (wr->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP) अणु
		aseg->swap_add = cpu_to_be64(wr->swap);
		aseg->compare  = cpu_to_be64(wr->compare_add);
	पूर्ण अन्यथा अणु
		aseg->swap_add = cpu_to_be64(wr->compare_add);
		aseg->compare  = 0;
	पूर्ण

पूर्ण

अटल व्योम set_tavor_ud_seg(काष्ठा mthca_tavor_ud_seg *useg,
			     स्थिर काष्ठा ib_ud_wr *wr)
अणु
	useg->lkey    = cpu_to_be32(to_mah(wr->ah)->key);
	useg->av_addr =	cpu_to_be64(to_mah(wr->ah)->avdma);
	useg->dqpn    =	cpu_to_be32(wr->remote_qpn);
	useg->qkey    =	cpu_to_be32(wr->remote_qkey);

पूर्ण

अटल व्योम set_arbel_ud_seg(काष्ठा mthca_arbel_ud_seg *useg,
			     स्थिर काष्ठा ib_ud_wr *wr)
अणु
	स_नकल(useg->av, to_mah(wr->ah)->av, MTHCA_AV_SIZE);
	useg->dqpn = cpu_to_be32(wr->remote_qpn);
	useg->qkey = cpu_to_be32(wr->remote_qkey);
पूर्ण

पूर्णांक mthca_tavor_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
			  स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibqp->device);
	काष्ठा mthca_qp *qp = to_mqp(ibqp);
	व्योम *wqe;
	व्योम *prev_wqe;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	पूर्णांक nreq;
	पूर्णांक i;
	पूर्णांक size;
	/*
	 * f0 and size0 are only used अगर nreq != 0, and they will
	 * always be initialized the first समय through the मुख्य loop
	 * beक्रमe nreq is incremented.  So nreq cannot become non-zero
	 * without initializing f0 and size0, and they are in fact
	 * never used uninitialized.
	 */
	पूर्णांक size0;
	u32 f0;
	पूर्णांक ind;
	u8 op0 = 0;

	spin_lock_irqsave(&qp->sq.lock, flags);

	/* XXX check that state is OK to post send */

	ind = qp->sq.next_ind;

	क्रम (nreq = 0; wr; ++nreq, wr = wr->next) अणु
		अगर (mthca_wq_overflow(&qp->sq, nreq, qp->ibqp.send_cq)) अणु
			mthca_err(dev, "SQ %06x full (%u head, %u tail,"
					" %d max, %d nreq)\n", qp->qpn,
					qp->sq.head, qp->sq.tail,
					qp->sq.max, nreq);
			err = -ENOMEM;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		wqe = get_send_wqe(qp, ind);
		prev_wqe = qp->sq.last;
		qp->sq.last = wqe;

		((काष्ठा mthca_next_seg *) wqe)->nda_op = 0;
		((काष्ठा mthca_next_seg *) wqe)->ee_nds = 0;
		((काष्ठा mthca_next_seg *) wqe)->flags =
			((wr->send_flags & IB_SEND_SIGNALED) ?
			 cpu_to_be32(MTHCA_NEXT_CQ_UPDATE) : 0) |
			((wr->send_flags & IB_SEND_SOLICITED) ?
			 cpu_to_be32(MTHCA_NEXT_SOLICIT) : 0)   |
			cpu_to_be32(1);
		अगर (wr->opcode == IB_WR_SEND_WITH_IMM ||
		    wr->opcode == IB_WR_RDMA_WRITE_WITH_IMM)
			((काष्ठा mthca_next_seg *) wqe)->imm = wr->ex.imm_data;

		wqe += माप (काष्ठा mthca_next_seg);
		size = माप (काष्ठा mthca_next_seg) / 16;

		चयन (qp->transport) अणु
		हाल RC:
			चयन (wr->opcode) अणु
			हाल IB_WR_ATOMIC_CMP_AND_SWP:
			हाल IB_WR_ATOMIC_FETCH_AND_ADD:
				set_raddr_seg(wqe, atomic_wr(wr)->remote_addr,
					      atomic_wr(wr)->rkey);
				wqe += माप (काष्ठा mthca_raddr_seg);

				set_atomic_seg(wqe, atomic_wr(wr));
				wqe += माप (काष्ठा mthca_atomic_seg);
				size += (माप (काष्ठा mthca_raddr_seg) +
					 माप (काष्ठा mthca_atomic_seg)) / 16;
				अवरोध;

			हाल IB_WR_RDMA_WRITE:
			हाल IB_WR_RDMA_WRITE_WITH_IMM:
			हाल IB_WR_RDMA_READ:
				set_raddr_seg(wqe, rdma_wr(wr)->remote_addr,
					      rdma_wr(wr)->rkey);
				wqe  += माप (काष्ठा mthca_raddr_seg);
				size += माप (काष्ठा mthca_raddr_seg) / 16;
				अवरोध;

			शेष:
				/* No extra segments required क्रम sends */
				अवरोध;
			पूर्ण

			अवरोध;

		हाल UC:
			चयन (wr->opcode) अणु
			हाल IB_WR_RDMA_WRITE:
			हाल IB_WR_RDMA_WRITE_WITH_IMM:
				set_raddr_seg(wqe, rdma_wr(wr)->remote_addr,
					      rdma_wr(wr)->rkey);
				wqe  += माप (काष्ठा mthca_raddr_seg);
				size += माप (काष्ठा mthca_raddr_seg) / 16;
				अवरोध;

			शेष:
				/* No extra segments required क्रम sends */
				अवरोध;
			पूर्ण

			अवरोध;

		हाल UD:
			set_tavor_ud_seg(wqe, ud_wr(wr));
			wqe  += माप (काष्ठा mthca_tavor_ud_seg);
			size += माप (काष्ठा mthca_tavor_ud_seg) / 16;
			अवरोध;

		हाल MLX:
			err = build_mlx_header(
				dev, qp, ind, ud_wr(wr),
				wqe - माप(काष्ठा mthca_next_seg), wqe);
			अगर (err) अणु
				*bad_wr = wr;
				जाओ out;
			पूर्ण
			wqe += माप (काष्ठा mthca_data_seg);
			size += माप (काष्ठा mthca_data_seg) / 16;
			अवरोध;
		पूर्ण

		अगर (wr->num_sge > qp->sq.max_gs) अणु
			mthca_err(dev, "too many gathers\n");
			err = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < wr->num_sge; ++i) अणु
			mthca_set_data_seg(wqe, wr->sg_list + i);
			wqe  += माप (काष्ठा mthca_data_seg);
			size += माप (काष्ठा mthca_data_seg) / 16;
		पूर्ण

		/* Add one more अंतरभूत data segment क्रम ICRC */
		अगर (qp->transport == MLX) अणु
			((काष्ठा mthca_data_seg *) wqe)->byte_count =
				cpu_to_be32((1 << 31) | 4);
			((u32 *) wqe)[1] = 0;
			wqe += माप (काष्ठा mthca_data_seg);
			size += माप (काष्ठा mthca_data_seg) / 16;
		पूर्ण

		qp->wrid[ind + qp->rq.max] = wr->wr_id;

		अगर (wr->opcode >= ARRAY_SIZE(mthca_opcode)) अणु
			mthca_err(dev, "opcode invalid\n");
			err = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		((काष्ठा mthca_next_seg *) prev_wqe)->nda_op =
			cpu_to_be32(((ind << qp->sq.wqe_shअगरt) +
				     qp->send_wqe_offset) |
				    mthca_opcode[wr->opcode]);
		wmb();
		((काष्ठा mthca_next_seg *) prev_wqe)->ee_nds =
			cpu_to_be32((nreq ? 0 : MTHCA_NEXT_DBD) | size |
				    ((wr->send_flags & IB_SEND_FENCE) ?
				    MTHCA_NEXT_FENCE : 0));

		अगर (!nreq) अणु
			size0 = size;
			op0   = mthca_opcode[wr->opcode];
			f0    = wr->send_flags & IB_SEND_FENCE ?
				MTHCA_SEND_DOORBELL_FENCE : 0;
		पूर्ण

		++ind;
		अगर (unlikely(ind >= qp->sq.max))
			ind -= qp->sq.max;
	पूर्ण

out:
	अगर (likely(nreq)) अणु
		wmb();

		mthca_ग_लिखो64(((qp->sq.next_ind << qp->sq.wqe_shअगरt) +
			       qp->send_wqe_offset) | f0 | op0,
			      (qp->qpn << 8) | size0,
			      dev->kar + MTHCA_SEND_DOORBELL,
			      MTHCA_GET_DOORBELL_LOCK(&dev->करोorbell_lock));
	पूर्ण

	qp->sq.next_ind = ind;
	qp->sq.head    += nreq;

	spin_unlock_irqrestore(&qp->sq.lock, flags);
	वापस err;
पूर्ण

पूर्णांक mthca_tavor_post_receive(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
			     स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibqp->device);
	काष्ठा mthca_qp *qp = to_mqp(ibqp);
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	पूर्णांक nreq;
	पूर्णांक i;
	पूर्णांक size;
	/*
	 * size0 is only used अगर nreq != 0, and it will always be
	 * initialized the first समय through the मुख्य loop beक्रमe
	 * nreq is incremented.  So nreq cannot become non-zero
	 * without initializing size0, and it is in fact never used
	 * uninitialized.
	 */
	पूर्णांक size0;
	पूर्णांक ind;
	व्योम *wqe;
	व्योम *prev_wqe;

	spin_lock_irqsave(&qp->rq.lock, flags);

	/* XXX check that state is OK to post receive */

	ind = qp->rq.next_ind;

	क्रम (nreq = 0; wr; wr = wr->next) अणु
		अगर (mthca_wq_overflow(&qp->rq, nreq, qp->ibqp.recv_cq)) अणु
			mthca_err(dev, "RQ %06x full (%u head, %u tail,"
					" %d max, %d nreq)\n", qp->qpn,
					qp->rq.head, qp->rq.tail,
					qp->rq.max, nreq);
			err = -ENOMEM;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		wqe = get_recv_wqe(qp, ind);
		prev_wqe = qp->rq.last;
		qp->rq.last = wqe;

		((काष्ठा mthca_next_seg *) wqe)->ee_nds =
			cpu_to_be32(MTHCA_NEXT_DBD);
		((काष्ठा mthca_next_seg *) wqe)->flags = 0;

		wqe += माप (काष्ठा mthca_next_seg);
		size = माप (काष्ठा mthca_next_seg) / 16;

		अगर (unlikely(wr->num_sge > qp->rq.max_gs)) अणु
			err = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < wr->num_sge; ++i) अणु
			mthca_set_data_seg(wqe, wr->sg_list + i);
			wqe  += माप (काष्ठा mthca_data_seg);
			size += माप (काष्ठा mthca_data_seg) / 16;
		पूर्ण

		qp->wrid[ind] = wr->wr_id;

		((काष्ठा mthca_next_seg *) prev_wqe)->ee_nds =
			cpu_to_be32(MTHCA_NEXT_DBD | size);

		अगर (!nreq)
			size0 = size;

		++ind;
		अगर (unlikely(ind >= qp->rq.max))
			ind -= qp->rq.max;

		++nreq;
		अगर (unlikely(nreq == MTHCA_TAVOR_MAX_WQES_PER_RECV_DB)) अणु
			nreq = 0;

			wmb();

			mthca_ग_लिखो64((qp->rq.next_ind << qp->rq.wqe_shअगरt) | size0,
				      qp->qpn << 8, dev->kar + MTHCA_RECEIVE_DOORBELL,
				      MTHCA_GET_DOORBELL_LOCK(&dev->करोorbell_lock));

			qp->rq.next_ind = ind;
			qp->rq.head += MTHCA_TAVOR_MAX_WQES_PER_RECV_DB;
		पूर्ण
	पूर्ण

out:
	अगर (likely(nreq)) अणु
		wmb();

		mthca_ग_लिखो64((qp->rq.next_ind << qp->rq.wqe_shअगरt) | size0,
			      qp->qpn << 8 | nreq, dev->kar + MTHCA_RECEIVE_DOORBELL,
			      MTHCA_GET_DOORBELL_LOCK(&dev->करोorbell_lock));
	पूर्ण

	qp->rq.next_ind = ind;
	qp->rq.head    += nreq;

	spin_unlock_irqrestore(&qp->rq.lock, flags);
	वापस err;
पूर्ण

पूर्णांक mthca_arbel_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
			  स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibqp->device);
	काष्ठा mthca_qp *qp = to_mqp(ibqp);
	u32 dbhi;
	व्योम *wqe;
	व्योम *prev_wqe;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	पूर्णांक nreq;
	पूर्णांक i;
	पूर्णांक size;
	/*
	 * f0 and size0 are only used अगर nreq != 0, and they will
	 * always be initialized the first समय through the मुख्य loop
	 * beक्रमe nreq is incremented.  So nreq cannot become non-zero
	 * without initializing f0 and size0, and they are in fact
	 * never used uninitialized.
	 */
	पूर्णांक size0;
	u32 f0;
	पूर्णांक ind;
	u8 op0 = 0;

	spin_lock_irqsave(&qp->sq.lock, flags);

	/* XXX check that state is OK to post send */

	ind = qp->sq.head & (qp->sq.max - 1);

	क्रम (nreq = 0; wr; ++nreq, wr = wr->next) अणु
		अगर (unlikely(nreq == MTHCA_ARBEL_MAX_WQES_PER_SEND_DB)) अणु
			nreq = 0;

			dbhi = (MTHCA_ARBEL_MAX_WQES_PER_SEND_DB << 24) |
				((qp->sq.head & 0xffff) << 8) | f0 | op0;

			qp->sq.head += MTHCA_ARBEL_MAX_WQES_PER_SEND_DB;

			/*
			 * Make sure that descriptors are written beक्रमe
			 * करोorbell record.
			 */
			wmb();
			*qp->sq.db = cpu_to_be32(qp->sq.head & 0xffff);

			/*
			 * Make sure करोorbell record is written beक्रमe we
			 * ग_लिखो MMIO send करोorbell.
			 */
			wmb();

			mthca_ग_लिखो64(dbhi, (qp->qpn << 8) | size0,
				      dev->kar + MTHCA_SEND_DOORBELL,
				      MTHCA_GET_DOORBELL_LOCK(&dev->करोorbell_lock));
		पूर्ण

		अगर (mthca_wq_overflow(&qp->sq, nreq, qp->ibqp.send_cq)) अणु
			mthca_err(dev, "SQ %06x full (%u head, %u tail,"
					" %d max, %d nreq)\n", qp->qpn,
					qp->sq.head, qp->sq.tail,
					qp->sq.max, nreq);
			err = -ENOMEM;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		wqe = get_send_wqe(qp, ind);
		prev_wqe = qp->sq.last;
		qp->sq.last = wqe;

		((काष्ठा mthca_next_seg *) wqe)->flags =
			((wr->send_flags & IB_SEND_SIGNALED) ?
			 cpu_to_be32(MTHCA_NEXT_CQ_UPDATE) : 0) |
			((wr->send_flags & IB_SEND_SOLICITED) ?
			 cpu_to_be32(MTHCA_NEXT_SOLICIT) : 0)   |
			((wr->send_flags & IB_SEND_IP_CSUM) ?
			 cpu_to_be32(MTHCA_NEXT_IP_CSUM | MTHCA_NEXT_TCP_UDP_CSUM) : 0) |
			cpu_to_be32(1);
		अगर (wr->opcode == IB_WR_SEND_WITH_IMM ||
		    wr->opcode == IB_WR_RDMA_WRITE_WITH_IMM)
			((काष्ठा mthca_next_seg *) wqe)->imm = wr->ex.imm_data;

		wqe += माप (काष्ठा mthca_next_seg);
		size = माप (काष्ठा mthca_next_seg) / 16;

		चयन (qp->transport) अणु
		हाल RC:
			चयन (wr->opcode) अणु
			हाल IB_WR_ATOMIC_CMP_AND_SWP:
			हाल IB_WR_ATOMIC_FETCH_AND_ADD:
				set_raddr_seg(wqe, atomic_wr(wr)->remote_addr,
					      atomic_wr(wr)->rkey);
				wqe += माप (काष्ठा mthca_raddr_seg);

				set_atomic_seg(wqe, atomic_wr(wr));
				wqe  += माप (काष्ठा mthca_atomic_seg);
				size += (माप (काष्ठा mthca_raddr_seg) +
					 माप (काष्ठा mthca_atomic_seg)) / 16;
				अवरोध;

			हाल IB_WR_RDMA_READ:
			हाल IB_WR_RDMA_WRITE:
			हाल IB_WR_RDMA_WRITE_WITH_IMM:
				set_raddr_seg(wqe, rdma_wr(wr)->remote_addr,
					      rdma_wr(wr)->rkey);
				wqe  += माप (काष्ठा mthca_raddr_seg);
				size += माप (काष्ठा mthca_raddr_seg) / 16;
				अवरोध;

			शेष:
				/* No extra segments required क्रम sends */
				अवरोध;
			पूर्ण

			अवरोध;

		हाल UC:
			चयन (wr->opcode) अणु
			हाल IB_WR_RDMA_WRITE:
			हाल IB_WR_RDMA_WRITE_WITH_IMM:
				set_raddr_seg(wqe, rdma_wr(wr)->remote_addr,
					      rdma_wr(wr)->rkey);
				wqe  += माप (काष्ठा mthca_raddr_seg);
				size += माप (काष्ठा mthca_raddr_seg) / 16;
				अवरोध;

			शेष:
				/* No extra segments required क्रम sends */
				अवरोध;
			पूर्ण

			अवरोध;

		हाल UD:
			set_arbel_ud_seg(wqe, ud_wr(wr));
			wqe  += माप (काष्ठा mthca_arbel_ud_seg);
			size += माप (काष्ठा mthca_arbel_ud_seg) / 16;
			अवरोध;

		हाल MLX:
			err = build_mlx_header(
				dev, qp, ind, ud_wr(wr),
				wqe - माप(काष्ठा mthca_next_seg), wqe);
			अगर (err) अणु
				*bad_wr = wr;
				जाओ out;
			पूर्ण
			wqe += माप (काष्ठा mthca_data_seg);
			size += माप (काष्ठा mthca_data_seg) / 16;
			अवरोध;
		पूर्ण

		अगर (wr->num_sge > qp->sq.max_gs) अणु
			mthca_err(dev, "too many gathers\n");
			err = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < wr->num_sge; ++i) अणु
			mthca_set_data_seg(wqe, wr->sg_list + i);
			wqe  += माप (काष्ठा mthca_data_seg);
			size += माप (काष्ठा mthca_data_seg) / 16;
		पूर्ण

		/* Add one more अंतरभूत data segment क्रम ICRC */
		अगर (qp->transport == MLX) अणु
			((काष्ठा mthca_data_seg *) wqe)->byte_count =
				cpu_to_be32((1 << 31) | 4);
			((u32 *) wqe)[1] = 0;
			wqe += माप (काष्ठा mthca_data_seg);
			size += माप (काष्ठा mthca_data_seg) / 16;
		पूर्ण

		qp->wrid[ind + qp->rq.max] = wr->wr_id;

		अगर (wr->opcode >= ARRAY_SIZE(mthca_opcode)) अणु
			mthca_err(dev, "opcode invalid\n");
			err = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		((काष्ठा mthca_next_seg *) prev_wqe)->nda_op =
			cpu_to_be32(((ind << qp->sq.wqe_shअगरt) +
				     qp->send_wqe_offset) |
				    mthca_opcode[wr->opcode]);
		wmb();
		((काष्ठा mthca_next_seg *) prev_wqe)->ee_nds =
			cpu_to_be32(MTHCA_NEXT_DBD | size |
				    ((wr->send_flags & IB_SEND_FENCE) ?
				     MTHCA_NEXT_FENCE : 0));

		अगर (!nreq) अणु
			size0 = size;
			op0   = mthca_opcode[wr->opcode];
			f0    = wr->send_flags & IB_SEND_FENCE ?
				MTHCA_SEND_DOORBELL_FENCE : 0;
		पूर्ण

		++ind;
		अगर (unlikely(ind >= qp->sq.max))
			ind -= qp->sq.max;
	पूर्ण

out:
	अगर (likely(nreq)) अणु
		dbhi = (nreq << 24) | ((qp->sq.head & 0xffff) << 8) | f0 | op0;

		qp->sq.head += nreq;

		/*
		 * Make sure that descriptors are written beक्रमe
		 * करोorbell record.
		 */
		wmb();
		*qp->sq.db = cpu_to_be32(qp->sq.head & 0xffff);

		/*
		 * Make sure करोorbell record is written beक्रमe we
		 * ग_लिखो MMIO send करोorbell.
		 */
		wmb();

		mthca_ग_लिखो64(dbhi, (qp->qpn << 8) | size0, dev->kar + MTHCA_SEND_DOORBELL,
			      MTHCA_GET_DOORBELL_LOCK(&dev->करोorbell_lock));
	पूर्ण

	spin_unlock_irqrestore(&qp->sq.lock, flags);
	वापस err;
पूर्ण

पूर्णांक mthca_arbel_post_receive(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
			     स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibqp->device);
	काष्ठा mthca_qp *qp = to_mqp(ibqp);
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	पूर्णांक nreq;
	पूर्णांक ind;
	पूर्णांक i;
	व्योम *wqe;

	spin_lock_irqsave(&qp->rq.lock, flags);

	/* XXX check that state is OK to post receive */

	ind = qp->rq.head & (qp->rq.max - 1);

	क्रम (nreq = 0; wr; ++nreq, wr = wr->next) अणु
		अगर (mthca_wq_overflow(&qp->rq, nreq, qp->ibqp.recv_cq)) अणु
			mthca_err(dev, "RQ %06x full (%u head, %u tail,"
					" %d max, %d nreq)\n", qp->qpn,
					qp->rq.head, qp->rq.tail,
					qp->rq.max, nreq);
			err = -ENOMEM;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		wqe = get_recv_wqe(qp, ind);

		((काष्ठा mthca_next_seg *) wqe)->flags = 0;

		wqe += माप (काष्ठा mthca_next_seg);

		अगर (unlikely(wr->num_sge > qp->rq.max_gs)) अणु
			err = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < wr->num_sge; ++i) अणु
			mthca_set_data_seg(wqe, wr->sg_list + i);
			wqe += माप (काष्ठा mthca_data_seg);
		पूर्ण

		अगर (i < qp->rq.max_gs)
			mthca_set_data_seg_inval(wqe);

		qp->wrid[ind] = wr->wr_id;

		++ind;
		अगर (unlikely(ind >= qp->rq.max))
			ind -= qp->rq.max;
	पूर्ण
out:
	अगर (likely(nreq)) अणु
		qp->rq.head += nreq;

		/*
		 * Make sure that descriptors are written beक्रमe
		 * करोorbell record.
		 */
		wmb();
		*qp->rq.db = cpu_to_be32(qp->rq.head & 0xffff);
	पूर्ण

	spin_unlock_irqrestore(&qp->rq.lock, flags);
	वापस err;
पूर्ण

व्योम mthca_मुक्त_err_wqe(काष्ठा mthca_dev *dev, काष्ठा mthca_qp *qp, पूर्णांक is_send,
			पूर्णांक index, पूर्णांक *dbd, __be32 *new_wqe)
अणु
	काष्ठा mthca_next_seg *next;

	/*
	 * For SRQs, all receive WQEs generate a CQE, so we're always
	 * at the end of the करोorbell chain.
	 */
	अगर (qp->ibqp.srq && !is_send) अणु
		*new_wqe = 0;
		वापस;
	पूर्ण

	अगर (is_send)
		next = get_send_wqe(qp, index);
	अन्यथा
		next = get_recv_wqe(qp, index);

	*dbd = !!(next->ee_nds & cpu_to_be32(MTHCA_NEXT_DBD));
	अगर (next->ee_nds & cpu_to_be32(0x3f))
		*new_wqe = (next->nda_op & cpu_to_be32(~0x3f)) |
			(next->ee_nds & cpu_to_be32(0x3f));
	अन्यथा
		*new_wqe = 0;
पूर्ण

पूर्णांक mthca_init_qp_table(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक err;
	पूर्णांक i;

	spin_lock_init(&dev->qp_table.lock);

	/*
	 * We reserve 2 extra QPs per port क्रम the special QPs.  The
	 * special QP क्रम port 1 has to be even, so round up.
	 */
	dev->qp_table.sqp_start = (dev->limits.reserved_qps + 1) & ~1UL;
	err = mthca_alloc_init(&dev->qp_table.alloc,
			       dev->limits.num_qps,
			       (1 << 24) - 1,
			       dev->qp_table.sqp_start +
			       MTHCA_MAX_PORTS * 2);
	अगर (err)
		वापस err;

	err = mthca_array_init(&dev->qp_table.qp,
			       dev->limits.num_qps);
	अगर (err) अणु
		mthca_alloc_cleanup(&dev->qp_table.alloc);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < 2; ++i) अणु
		err = mthca_CONF_SPECIAL_QP(dev, i ? IB_QPT_GSI : IB_QPT_SMI,
				    dev->qp_table.sqp_start + i * 2);
		अगर (err) अणु
			mthca_warn(dev, "CONF_SPECIAL_QP returned "
				   "%d, aborting.\n", err);
			जाओ err_out;
		पूर्ण
	पूर्ण
	वापस 0;

 err_out:
	क्रम (i = 0; i < 2; ++i)
		mthca_CONF_SPECIAL_QP(dev, i, 0);

	mthca_array_cleanup(&dev->qp_table.qp, dev->limits.num_qps);
	mthca_alloc_cleanup(&dev->qp_table.alloc);

	वापस err;
पूर्ण

व्योम mthca_cleanup_qp_table(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; ++i)
		mthca_CONF_SPECIAL_QP(dev, i, 0);

	mthca_array_cleanup(&dev->qp_table.qp, dev->limits.num_qps);
	mthca_alloc_cleanup(&dev->qp_table.alloc);
पूर्ण
