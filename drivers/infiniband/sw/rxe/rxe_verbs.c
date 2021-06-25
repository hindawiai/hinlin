<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <net/addrconf.h>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश "rxe.h"
#समावेश "rxe_loc.h"
#समावेश "rxe_queue.h"
#समावेश "rxe_hw_counters.h"

अटल पूर्णांक rxe_query_device(काष्ठा ib_device *dev,
			    काष्ठा ib_device_attr *attr,
			    काष्ठा ib_udata *uhw)
अणु
	काष्ठा rxe_dev *rxe = to_rdev(dev);

	अगर (uhw->inlen || uhw->outlen)
		वापस -EINVAL;

	*attr = rxe->attr;
	वापस 0;
पूर्ण

अटल पूर्णांक rxe_query_port(काष्ठा ib_device *dev,
			  u32 port_num, काष्ठा ib_port_attr *attr)
अणु
	काष्ठा rxe_dev *rxe = to_rdev(dev);
	काष्ठा rxe_port *port;
	पूर्णांक rc;

	port = &rxe->port;

	/* *attr being zeroed by the caller, aव्योम zeroing it here */
	*attr = port->attr;

	mutex_lock(&rxe->usdev_lock);
	rc = ib_get_eth_speed(dev, port_num, &attr->active_speed,
			      &attr->active_width);

	अगर (attr->state == IB_PORT_ACTIVE)
		attr->phys_state = IB_PORT_PHYS_STATE_LINK_UP;
	अन्यथा अगर (dev_get_flags(rxe->ndev) & IFF_UP)
		attr->phys_state = IB_PORT_PHYS_STATE_POLLING;
	अन्यथा
		attr->phys_state = IB_PORT_PHYS_STATE_DISABLED;

	mutex_unlock(&rxe->usdev_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक rxe_query_pkey(काष्ठा ib_device *device,
			  u32 port_num, u16 index, u16 *pkey)
अणु
	अगर (index > 0)
		वापस -EINVAL;

	*pkey = IB_DEFAULT_PKEY_FULL;
	वापस 0;
पूर्ण

अटल पूर्णांक rxe_modअगरy_device(काष्ठा ib_device *dev,
			     पूर्णांक mask, काष्ठा ib_device_modअगरy *attr)
अणु
	काष्ठा rxe_dev *rxe = to_rdev(dev);

	अगर (mask & ~(IB_DEVICE_MODIFY_SYS_IMAGE_GUID |
		     IB_DEVICE_MODIFY_NODE_DESC))
		वापस -EOPNOTSUPP;

	अगर (mask & IB_DEVICE_MODIFY_SYS_IMAGE_GUID)
		rxe->attr.sys_image_guid = cpu_to_be64(attr->sys_image_guid);

	अगर (mask & IB_DEVICE_MODIFY_NODE_DESC) अणु
		स_नकल(rxe->ib_dev.node_desc,
		       attr->node_desc, माप(rxe->ib_dev.node_desc));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rxe_modअगरy_port(काष्ठा ib_device *dev,
			   u32 port_num, पूर्णांक mask, काष्ठा ib_port_modअगरy *attr)
अणु
	काष्ठा rxe_dev *rxe = to_rdev(dev);
	काष्ठा rxe_port *port;

	port = &rxe->port;

	port->attr.port_cap_flags |= attr->set_port_cap_mask;
	port->attr.port_cap_flags &= ~attr->clr_port_cap_mask;

	अगर (mask & IB_PORT_RESET_QKEY_CNTR)
		port->attr.qkey_viol_cntr = 0;

	वापस 0;
पूर्ण

अटल क्रमागत rdma_link_layer rxe_get_link_layer(काष्ठा ib_device *dev,
					       u32 port_num)
अणु
	वापस IB_LINK_LAYER_ETHERNET;
पूर्ण

अटल पूर्णांक rxe_alloc_ucontext(काष्ठा ib_ucontext *ibuc, काष्ठा ib_udata *udata)
अणु
	काष्ठा rxe_dev *rxe = to_rdev(ibuc->device);
	काष्ठा rxe_ucontext *uc = to_ruc(ibuc);

	वापस rxe_add_to_pool(&rxe->uc_pool, uc);
पूर्ण

अटल व्योम rxe_dealloc_ucontext(काष्ठा ib_ucontext *ibuc)
अणु
	काष्ठा rxe_ucontext *uc = to_ruc(ibuc);

	rxe_drop_ref(uc);
पूर्ण

अटल पूर्णांक rxe_port_immutable(काष्ठा ib_device *dev, u32 port_num,
			      काष्ठा ib_port_immutable *immutable)
अणु
	पूर्णांक err;
	काष्ठा ib_port_attr attr;

	immutable->core_cap_flags = RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP;

	err = ib_query_port(dev, port_num, &attr);
	अगर (err)
		वापस err;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;
	immutable->max_mad_size = IB_MGMT_MAD_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक rxe_alloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा rxe_dev *rxe = to_rdev(ibpd->device);
	काष्ठा rxe_pd *pd = to_rpd(ibpd);

	वापस rxe_add_to_pool(&rxe->pd_pool, pd);
पूर्ण

अटल पूर्णांक rxe_dealloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा rxe_pd *pd = to_rpd(ibpd);

	rxe_drop_ref(pd);
	वापस 0;
पूर्ण

अटल पूर्णांक rxe_create_ah(काष्ठा ib_ah *ibah,
			 काष्ठा rdma_ah_init_attr *init_attr,
			 काष्ठा ib_udata *udata)

अणु
	पूर्णांक err;
	काष्ठा rxe_dev *rxe = to_rdev(ibah->device);
	काष्ठा rxe_ah *ah = to_rah(ibah);

	err = rxe_av_chk_attr(rxe, init_attr->ah_attr);
	अगर (err)
		वापस err;

	err = rxe_add_to_pool(&rxe->ah_pool, ah);
	अगर (err)
		वापस err;

	rxe_init_av(init_attr->ah_attr, &ah->av);
	वापस 0;
पूर्ण

अटल पूर्णांक rxe_modअगरy_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_attr *attr)
अणु
	पूर्णांक err;
	काष्ठा rxe_dev *rxe = to_rdev(ibah->device);
	काष्ठा rxe_ah *ah = to_rah(ibah);

	err = rxe_av_chk_attr(rxe, attr);
	अगर (err)
		वापस err;

	rxe_init_av(attr, &ah->av);
	वापस 0;
पूर्ण

अटल पूर्णांक rxe_query_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_attr *attr)
अणु
	काष्ठा rxe_ah *ah = to_rah(ibah);

	स_रखो(attr, 0, माप(*attr));
	attr->type = ibah->type;
	rxe_av_to_attr(&ah->av, attr);
	वापस 0;
पूर्ण

अटल पूर्णांक rxe_destroy_ah(काष्ठा ib_ah *ibah, u32 flags)
अणु
	काष्ठा rxe_ah *ah = to_rah(ibah);

	rxe_drop_ref(ah);
	वापस 0;
पूर्ण

अटल पूर्णांक post_one_recv(काष्ठा rxe_rq *rq, स्थिर काष्ठा ib_recv_wr *ibwr)
अणु
	पूर्णांक err;
	पूर्णांक i;
	u32 length;
	काष्ठा rxe_recv_wqe *recv_wqe;
	पूर्णांक num_sge = ibwr->num_sge;

	अगर (unlikely(queue_full(rq->queue))) अणु
		err = -ENOMEM;
		जाओ err1;
	पूर्ण

	अगर (unlikely(num_sge > rq->max_sge)) अणु
		err = -EINVAL;
		जाओ err1;
	पूर्ण

	length = 0;
	क्रम (i = 0; i < num_sge; i++)
		length += ibwr->sg_list[i].length;

	recv_wqe = producer_addr(rq->queue);
	recv_wqe->wr_id = ibwr->wr_id;
	recv_wqe->num_sge = num_sge;

	स_नकल(recv_wqe->dma.sge, ibwr->sg_list,
	       num_sge * माप(काष्ठा ib_sge));

	recv_wqe->dma.length		= length;
	recv_wqe->dma.resid		= length;
	recv_wqe->dma.num_sge		= num_sge;
	recv_wqe->dma.cur_sge		= 0;
	recv_wqe->dma.sge_offset	= 0;

	advance_producer(rq->queue);
	वापस 0;

err1:
	वापस err;
पूर्ण

अटल पूर्णांक rxe_create_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_init_attr *init,
			  काष्ठा ib_udata *udata)
अणु
	पूर्णांक err;
	काष्ठा rxe_dev *rxe = to_rdev(ibsrq->device);
	काष्ठा rxe_pd *pd = to_rpd(ibsrq->pd);
	काष्ठा rxe_srq *srq = to_rsrq(ibsrq);
	काष्ठा rxe_create_srq_resp __user *uresp = शून्य;

	अगर (init->srq_type != IB_SRQT_BASIC)
		वापस -EOPNOTSUPP;

	अगर (udata) अणु
		अगर (udata->outlen < माप(*uresp))
			वापस -EINVAL;
		uresp = udata->outbuf;
	पूर्ण

	err = rxe_srq_chk_attr(rxe, शून्य, &init->attr, IB_SRQ_INIT_MASK);
	अगर (err)
		जाओ err1;

	err = rxe_add_to_pool(&rxe->srq_pool, srq);
	अगर (err)
		जाओ err1;

	rxe_add_ref(pd);
	srq->pd = pd;

	err = rxe_srq_from_init(rxe, srq, init, udata, uresp);
	अगर (err)
		जाओ err2;

	वापस 0;

err2:
	rxe_drop_ref(pd);
	rxe_drop_ref(srq);
err1:
	वापस err;
पूर्ण

अटल पूर्णांक rxe_modअगरy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr,
			  क्रमागत ib_srq_attr_mask mask,
			  काष्ठा ib_udata *udata)
अणु
	पूर्णांक err;
	काष्ठा rxe_srq *srq = to_rsrq(ibsrq);
	काष्ठा rxe_dev *rxe = to_rdev(ibsrq->device);
	काष्ठा rxe_modअगरy_srq_cmd ucmd = अणुपूर्ण;

	अगर (udata) अणु
		अगर (udata->inlen < माप(ucmd))
			वापस -EINVAL;

		err = ib_copy_from_udata(&ucmd, udata, माप(ucmd));
		अगर (err)
			वापस err;
	पूर्ण

	err = rxe_srq_chk_attr(rxe, srq, attr, mask);
	अगर (err)
		जाओ err1;

	err = rxe_srq_from_attr(rxe, srq, attr, mask, &ucmd, udata);
	अगर (err)
		जाओ err1;

	वापस 0;

err1:
	वापस err;
पूर्ण

अटल पूर्णांक rxe_query_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr)
अणु
	काष्ठा rxe_srq *srq = to_rsrq(ibsrq);

	अगर (srq->error)
		वापस -EINVAL;

	attr->max_wr = srq->rq.queue->buf->index_mask;
	attr->max_sge = srq->rq.max_sge;
	attr->srq_limit = srq->limit;
	वापस 0;
पूर्ण

अटल पूर्णांक rxe_destroy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_udata *udata)
अणु
	काष्ठा rxe_srq *srq = to_rsrq(ibsrq);

	अगर (srq->rq.queue)
		rxe_queue_cleanup(srq->rq.queue);

	rxe_drop_ref(srq->pd);
	rxe_drop_ref(srq);
	वापस 0;
पूर्ण

अटल पूर्णांक rxe_post_srq_recv(काष्ठा ib_srq *ibsrq, स्थिर काष्ठा ib_recv_wr *wr,
			     स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	पूर्णांक err = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा rxe_srq *srq = to_rsrq(ibsrq);

	spin_lock_irqsave(&srq->rq.producer_lock, flags);

	जबतक (wr) अणु
		err = post_one_recv(&srq->rq, wr);
		अगर (unlikely(err))
			अवरोध;
		wr = wr->next;
	पूर्ण

	spin_unlock_irqrestore(&srq->rq.producer_lock, flags);

	अगर (err)
		*bad_wr = wr;

	वापस err;
पूर्ण

अटल काष्ठा ib_qp *rxe_create_qp(काष्ठा ib_pd *ibpd,
				   काष्ठा ib_qp_init_attr *init,
				   काष्ठा ib_udata *udata)
अणु
	पूर्णांक err;
	काष्ठा rxe_dev *rxe = to_rdev(ibpd->device);
	काष्ठा rxe_pd *pd = to_rpd(ibpd);
	काष्ठा rxe_qp *qp;
	काष्ठा rxe_create_qp_resp __user *uresp = शून्य;

	अगर (udata) अणु
		अगर (udata->outlen < माप(*uresp))
			वापस ERR_PTR(-EINVAL);
		uresp = udata->outbuf;
	पूर्ण

	अगर (init->create_flags)
		वापस ERR_PTR(-EOPNOTSUPP);

	err = rxe_qp_chk_init(rxe, init);
	अगर (err)
		जाओ err1;

	qp = rxe_alloc(&rxe->qp_pool);
	अगर (!qp) अणु
		err = -ENOMEM;
		जाओ err1;
	पूर्ण

	अगर (udata) अणु
		अगर (udata->inlen) अणु
			err = -EINVAL;
			जाओ err2;
		पूर्ण
		qp->is_user = 1;
	पूर्ण

	rxe_add_index(qp);

	err = rxe_qp_from_init(rxe, qp, pd, init, uresp, ibpd, udata);
	अगर (err)
		जाओ err3;

	वापस &qp->ibqp;

err3:
	rxe_drop_index(qp);
err2:
	rxe_drop_ref(qp);
err1:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक rxe_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
			 पूर्णांक mask, काष्ठा ib_udata *udata)
अणु
	पूर्णांक err;
	काष्ठा rxe_dev *rxe = to_rdev(ibqp->device);
	काष्ठा rxe_qp *qp = to_rqp(ibqp);

	अगर (mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	err = rxe_qp_chk_attr(rxe, qp, attr, mask);
	अगर (err)
		जाओ err1;

	err = rxe_qp_from_attr(qp, attr, mask, udata);
	अगर (err)
		जाओ err1;

	वापस 0;

err1:
	वापस err;
पूर्ण

अटल पूर्णांक rxe_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
			पूर्णांक mask, काष्ठा ib_qp_init_attr *init)
अणु
	काष्ठा rxe_qp *qp = to_rqp(ibqp);

	rxe_qp_to_init(qp, init);
	rxe_qp_to_attr(qp, attr, mask);

	वापस 0;
पूर्ण

अटल पूर्णांक rxe_destroy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_udata *udata)
अणु
	काष्ठा rxe_qp *qp = to_rqp(ibqp);

	rxe_qp_destroy(qp);
	rxe_drop_index(qp);
	rxe_drop_ref(qp);
	वापस 0;
पूर्ण

अटल पूर्णांक validate_send_wr(काष्ठा rxe_qp *qp, स्थिर काष्ठा ib_send_wr *ibwr,
			    अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक length)
अणु
	पूर्णांक num_sge = ibwr->num_sge;
	काष्ठा rxe_sq *sq = &qp->sq;

	अगर (unlikely(num_sge > sq->max_sge))
		जाओ err1;

	अगर (unlikely(mask & WR_ATOMIC_MASK)) अणु
		अगर (length < 8)
			जाओ err1;

		अगर (atomic_wr(ibwr)->remote_addr & 0x7)
			जाओ err1;
	पूर्ण

	अगर (unlikely((ibwr->send_flags & IB_SEND_INLINE) &&
		     (length > sq->max_अंतरभूत)))
		जाओ err1;

	वापस 0;

err1:
	वापस -EINVAL;
पूर्ण

अटल व्योम init_send_wr(काष्ठा rxe_qp *qp, काष्ठा rxe_send_wr *wr,
			 स्थिर काष्ठा ib_send_wr *ibwr)
अणु
	wr->wr_id = ibwr->wr_id;
	wr->num_sge = ibwr->num_sge;
	wr->opcode = ibwr->opcode;
	wr->send_flags = ibwr->send_flags;

	अगर (qp_type(qp) == IB_QPT_UD ||
	    qp_type(qp) == IB_QPT_SMI ||
	    qp_type(qp) == IB_QPT_GSI) अणु
		wr->wr.ud.remote_qpn = ud_wr(ibwr)->remote_qpn;
		wr->wr.ud.remote_qkey = ud_wr(ibwr)->remote_qkey;
		अगर (qp_type(qp) == IB_QPT_GSI)
			wr->wr.ud.pkey_index = ud_wr(ibwr)->pkey_index;
		अगर (wr->opcode == IB_WR_SEND_WITH_IMM)
			wr->ex.imm_data = ibwr->ex.imm_data;
	पूर्ण अन्यथा अणु
		चयन (wr->opcode) अणु
		हाल IB_WR_RDMA_WRITE_WITH_IMM:
			wr->ex.imm_data = ibwr->ex.imm_data;
			fallthrough;
		हाल IB_WR_RDMA_READ:
		हाल IB_WR_RDMA_WRITE:
			wr->wr.rdma.remote_addr = rdma_wr(ibwr)->remote_addr;
			wr->wr.rdma.rkey	= rdma_wr(ibwr)->rkey;
			अवरोध;
		हाल IB_WR_SEND_WITH_IMM:
			wr->ex.imm_data = ibwr->ex.imm_data;
			अवरोध;
		हाल IB_WR_SEND_WITH_INV:
			wr->ex.invalidate_rkey = ibwr->ex.invalidate_rkey;
			अवरोध;
		हाल IB_WR_ATOMIC_CMP_AND_SWP:
		हाल IB_WR_ATOMIC_FETCH_AND_ADD:
			wr->wr.atomic.remote_addr =
				atomic_wr(ibwr)->remote_addr;
			wr->wr.atomic.compare_add =
				atomic_wr(ibwr)->compare_add;
			wr->wr.atomic.swap = atomic_wr(ibwr)->swap;
			wr->wr.atomic.rkey = atomic_wr(ibwr)->rkey;
			अवरोध;
		हाल IB_WR_LOCAL_INV:
			wr->ex.invalidate_rkey = ibwr->ex.invalidate_rkey;
		अवरोध;
		हाल IB_WR_REG_MR:
			wr->wr.reg.mr = reg_wr(ibwr)->mr;
			wr->wr.reg.key = reg_wr(ibwr)->key;
			wr->wr.reg.access = reg_wr(ibwr)->access;
		अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम copy_अंतरभूत_data_to_wqe(काष्ठा rxe_send_wqe *wqe,
				    स्थिर काष्ठा ib_send_wr *ibwr)
अणु
	काष्ठा ib_sge *sge = ibwr->sg_list;
	u8 *p = wqe->dma.अंतरभूत_data;
	पूर्णांक i;

	क्रम (i = 0; i < ibwr->num_sge; i++, sge++) अणु
		स_नकल(p, (व्योम *)(uपूर्णांकptr_t)sge->addr, sge->length);
		p += sge->length;
	पूर्ण
पूर्ण

अटल व्योम init_send_wqe(काष्ठा rxe_qp *qp, स्थिर काष्ठा ib_send_wr *ibwr,
			 अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक length,
			 काष्ठा rxe_send_wqe *wqe)
अणु
	पूर्णांक num_sge = ibwr->num_sge;

	init_send_wr(qp, &wqe->wr, ibwr);

	/* local operation */
	अगर (unlikely(mask & WR_REG_MASK)) अणु
		wqe->mask = mask;
		wqe->state = wqe_state_posted;
		वापस;
	पूर्ण

	अगर (qp_type(qp) == IB_QPT_UD ||
	    qp_type(qp) == IB_QPT_SMI ||
	    qp_type(qp) == IB_QPT_GSI)
		स_नकल(&wqe->av, &to_rah(ud_wr(ibwr)->ah)->av, माप(wqe->av));

	अगर (unlikely(ibwr->send_flags & IB_SEND_INLINE))
		copy_अंतरभूत_data_to_wqe(wqe, ibwr);
	अन्यथा
		स_नकल(wqe->dma.sge, ibwr->sg_list,
		       num_sge * माप(काष्ठा ib_sge));

	wqe->iova = mask & WR_ATOMIC_MASK ? atomic_wr(ibwr)->remote_addr :
		mask & WR_READ_OR_WRITE_MASK ? rdma_wr(ibwr)->remote_addr : 0;
	wqe->mask		= mask;
	wqe->dma.length		= length;
	wqe->dma.resid		= length;
	wqe->dma.num_sge	= num_sge;
	wqe->dma.cur_sge	= 0;
	wqe->dma.sge_offset	= 0;
	wqe->state		= wqe_state_posted;
	wqe->ssn		= atomic_add_वापस(1, &qp->ssn);
पूर्ण

अटल पूर्णांक post_one_send(काष्ठा rxe_qp *qp, स्थिर काष्ठा ib_send_wr *ibwr,
			 अचिन्हित पूर्णांक mask, u32 length)
अणु
	पूर्णांक err;
	काष्ठा rxe_sq *sq = &qp->sq;
	काष्ठा rxe_send_wqe *send_wqe;
	अचिन्हित दीर्घ flags;

	err = validate_send_wr(qp, ibwr, mask, length);
	अगर (err)
		वापस err;

	spin_lock_irqsave(&qp->sq.sq_lock, flags);

	अगर (unlikely(queue_full(sq->queue))) अणु
		err = -ENOMEM;
		जाओ err1;
	पूर्ण

	send_wqe = producer_addr(sq->queue);
	init_send_wqe(qp, ibwr, mask, length, send_wqe);

	advance_producer(sq->queue);
	spin_unlock_irqrestore(&qp->sq.sq_lock, flags);

	वापस 0;

err1:
	spin_unlock_irqrestore(&qp->sq.sq_lock, flags);
	वापस err;
पूर्ण

अटल पूर्णांक rxe_post_send_kernel(काष्ठा rxe_qp *qp, स्थिर काष्ठा ib_send_wr *wr,
				स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक length = 0;
	पूर्णांक i;
	काष्ठा ib_send_wr *next;

	जबतक (wr) अणु
		mask = wr_opcode_mask(wr->opcode, qp);
		अगर (unlikely(!mask)) अणु
			err = -EINVAL;
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		अगर (unlikely((wr->send_flags & IB_SEND_INLINE) &&
			     !(mask & WR_INLINE_MASK))) अणु
			err = -EINVAL;
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		next = wr->next;

		length = 0;
		क्रम (i = 0; i < wr->num_sge; i++)
			length += wr->sg_list[i].length;

		err = post_one_send(qp, wr, mask, length);

		अगर (err) अणु
			*bad_wr = wr;
			अवरोध;
		पूर्ण
		wr = next;
	पूर्ण

	rxe_run_task(&qp->req.task, 1);
	अगर (unlikely(qp->req.state == QP_STATE_ERROR))
		rxe_run_task(&qp->comp.task, 1);

	वापस err;
पूर्ण

अटल पूर्णांक rxe_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
			 स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	काष्ठा rxe_qp *qp = to_rqp(ibqp);

	अगर (unlikely(!qp->valid)) अणु
		*bad_wr = wr;
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(qp->req.state < QP_STATE_READY)) अणु
		*bad_wr = wr;
		वापस -EINVAL;
	पूर्ण

	अगर (qp->is_user) अणु
		/* Utilize process context to करो protocol processing */
		rxe_run_task(&qp->req.task, 0);
		वापस 0;
	पूर्ण अन्यथा
		वापस rxe_post_send_kernel(qp, wr, bad_wr);
पूर्ण

अटल पूर्णांक rxe_post_recv(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
			 स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	पूर्णांक err = 0;
	काष्ठा rxe_qp *qp = to_rqp(ibqp);
	काष्ठा rxe_rq *rq = &qp->rq;
	अचिन्हित दीर्घ flags;

	अगर (unlikely((qp_state(qp) < IB_QPS_INIT) || !qp->valid)) अणु
		*bad_wr = wr;
		err = -EINVAL;
		जाओ err1;
	पूर्ण

	अगर (unlikely(qp->srq)) अणु
		*bad_wr = wr;
		err = -EINVAL;
		जाओ err1;
	पूर्ण

	spin_lock_irqsave(&rq->producer_lock, flags);

	जबतक (wr) अणु
		err = post_one_recv(rq, wr);
		अगर (unlikely(err)) अणु
			*bad_wr = wr;
			अवरोध;
		पूर्ण
		wr = wr->next;
	पूर्ण

	spin_unlock_irqrestore(&rq->producer_lock, flags);

	अगर (qp->resp.state == QP_STATE_ERROR)
		rxe_run_task(&qp->resp.task, 1);

err1:
	वापस err;
पूर्ण

अटल पूर्णांक rxe_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
			 काष्ठा ib_udata *udata)
अणु
	पूर्णांक err;
	काष्ठा ib_device *dev = ibcq->device;
	काष्ठा rxe_dev *rxe = to_rdev(dev);
	काष्ठा rxe_cq *cq = to_rcq(ibcq);
	काष्ठा rxe_create_cq_resp __user *uresp = शून्य;

	अगर (udata) अणु
		अगर (udata->outlen < माप(*uresp))
			वापस -EINVAL;
		uresp = udata->outbuf;
	पूर्ण

	अगर (attr->flags)
		वापस -EOPNOTSUPP;

	err = rxe_cq_chk_attr(rxe, शून्य, attr->cqe, attr->comp_vector);
	अगर (err)
		वापस err;

	err = rxe_cq_from_init(rxe, cq, attr->cqe, attr->comp_vector, udata,
			       uresp);
	अगर (err)
		वापस err;

	वापस rxe_add_to_pool(&rxe->cq_pool, cq);
पूर्ण

अटल पूर्णांक rxe_destroy_cq(काष्ठा ib_cq *ibcq, काष्ठा ib_udata *udata)
अणु
	काष्ठा rxe_cq *cq = to_rcq(ibcq);

	rxe_cq_disable(cq);

	rxe_drop_ref(cq);
	वापस 0;
पूर्ण

अटल पूर्णांक rxe_resize_cq(काष्ठा ib_cq *ibcq, पूर्णांक cqe, काष्ठा ib_udata *udata)
अणु
	पूर्णांक err;
	काष्ठा rxe_cq *cq = to_rcq(ibcq);
	काष्ठा rxe_dev *rxe = to_rdev(ibcq->device);
	काष्ठा rxe_resize_cq_resp __user *uresp = शून्य;

	अगर (udata) अणु
		अगर (udata->outlen < माप(*uresp))
			वापस -EINVAL;
		uresp = udata->outbuf;
	पूर्ण

	err = rxe_cq_chk_attr(rxe, cq, cqe, 0);
	अगर (err)
		जाओ err1;

	err = rxe_cq_resize_queue(cq, cqe, uresp, udata);
	अगर (err)
		जाओ err1;

	वापस 0;

err1:
	वापस err;
पूर्ण

अटल पूर्णांक rxe_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc)
अणु
	पूर्णांक i;
	काष्ठा rxe_cq *cq = to_rcq(ibcq);
	काष्ठा rxe_cqe *cqe;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cq->cq_lock, flags);
	क्रम (i = 0; i < num_entries; i++) अणु
		cqe = queue_head(cq->queue);
		अगर (!cqe)
			अवरोध;

		स_नकल(wc++, &cqe->ibwc, माप(*wc));
		advance_consumer(cq->queue);
	पूर्ण
	spin_unlock_irqrestore(&cq->cq_lock, flags);

	वापस i;
पूर्ण

अटल पूर्णांक rxe_peek_cq(काष्ठा ib_cq *ibcq, पूर्णांक wc_cnt)
अणु
	काष्ठा rxe_cq *cq = to_rcq(ibcq);
	पूर्णांक count = queue_count(cq->queue);

	वापस (count > wc_cnt) ? wc_cnt : count;
पूर्ण

अटल पूर्णांक rxe_req_notअगरy_cq(काष्ठा ib_cq *ibcq, क्रमागत ib_cq_notअगरy_flags flags)
अणु
	काष्ठा rxe_cq *cq = to_rcq(ibcq);
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&cq->cq_lock, irq_flags);
	अगर (cq->notअगरy != IB_CQ_NEXT_COMP)
		cq->notअगरy = flags & IB_CQ_SOLICITED_MASK;

	अगर ((flags & IB_CQ_REPORT_MISSED_EVENTS) && !queue_empty(cq->queue))
		ret = 1;

	spin_unlock_irqrestore(&cq->cq_lock, irq_flags);

	वापस ret;
पूर्ण

अटल काष्ठा ib_mr *rxe_get_dma_mr(काष्ठा ib_pd *ibpd, पूर्णांक access)
अणु
	काष्ठा rxe_dev *rxe = to_rdev(ibpd->device);
	काष्ठा rxe_pd *pd = to_rpd(ibpd);
	काष्ठा rxe_mr *mr;

	mr = rxe_alloc(&rxe->mr_pool);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	rxe_add_index(mr);
	rxe_add_ref(pd);
	rxe_mr_init_dma(pd, access, mr);

	वापस &mr->ibmr;
पूर्ण

अटल काष्ठा ib_mr *rxe_reg_user_mr(काष्ठा ib_pd *ibpd,
				     u64 start,
				     u64 length,
				     u64 iova,
				     पूर्णांक access, काष्ठा ib_udata *udata)
अणु
	पूर्णांक err;
	काष्ठा rxe_dev *rxe = to_rdev(ibpd->device);
	काष्ठा rxe_pd *pd = to_rpd(ibpd);
	काष्ठा rxe_mr *mr;

	mr = rxe_alloc(&rxe->mr_pool);
	अगर (!mr) अणु
		err = -ENOMEM;
		जाओ err2;
	पूर्ण

	rxe_add_index(mr);

	rxe_add_ref(pd);

	err = rxe_mr_init_user(pd, start, length, iova, access, udata, mr);
	अगर (err)
		जाओ err3;

	वापस &mr->ibmr;

err3:
	rxe_drop_ref(pd);
	rxe_drop_index(mr);
	rxe_drop_ref(mr);
err2:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक rxe_dereg_mr(काष्ठा ib_mr *ibmr, काष्ठा ib_udata *udata)
अणु
	काष्ठा rxe_mr *mr = to_rmr(ibmr);

	mr->state = RXE_MR_STATE_ZOMBIE;
	rxe_drop_ref(mr_pd(mr));
	rxe_drop_index(mr);
	rxe_drop_ref(mr);
	वापस 0;
पूर्ण

अटल काष्ठा ib_mr *rxe_alloc_mr(काष्ठा ib_pd *ibpd, क्रमागत ib_mr_type mr_type,
				  u32 max_num_sg)
अणु
	काष्ठा rxe_dev *rxe = to_rdev(ibpd->device);
	काष्ठा rxe_pd *pd = to_rpd(ibpd);
	काष्ठा rxe_mr *mr;
	पूर्णांक err;

	अगर (mr_type != IB_MR_TYPE_MEM_REG)
		वापस ERR_PTR(-EINVAL);

	mr = rxe_alloc(&rxe->mr_pool);
	अगर (!mr) अणु
		err = -ENOMEM;
		जाओ err1;
	पूर्ण

	rxe_add_index(mr);

	rxe_add_ref(pd);

	err = rxe_mr_init_fast(pd, max_num_sg, mr);
	अगर (err)
		जाओ err2;

	वापस &mr->ibmr;

err2:
	rxe_drop_ref(pd);
	rxe_drop_index(mr);
	rxe_drop_ref(mr);
err1:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक rxe_set_page(काष्ठा ib_mr *ibmr, u64 addr)
अणु
	काष्ठा rxe_mr *mr = to_rmr(ibmr);
	काष्ठा rxe_map *map;
	काष्ठा rxe_phys_buf *buf;

	अगर (unlikely(mr->nbuf == mr->num_buf))
		वापस -ENOMEM;

	map = mr->map[mr->nbuf / RXE_BUF_PER_MAP];
	buf = &map->buf[mr->nbuf % RXE_BUF_PER_MAP];

	buf->addr = addr;
	buf->size = ibmr->page_size;
	mr->nbuf++;

	वापस 0;
पूर्ण

अटल पूर्णांक rxe_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg,
			 पूर्णांक sg_nents, अचिन्हित पूर्णांक *sg_offset)
अणु
	काष्ठा rxe_mr *mr = to_rmr(ibmr);
	पूर्णांक n;

	mr->nbuf = 0;

	n = ib_sg_to_pages(ibmr, sg, sg_nents, sg_offset, rxe_set_page);

	mr->va = ibmr->iova;
	mr->iova = ibmr->iova;
	mr->length = ibmr->length;
	mr->page_shअगरt = ilog2(ibmr->page_size);
	mr->page_mask = ibmr->page_size - 1;
	mr->offset = mr->iova & mr->page_mask;

	वापस n;
पूर्ण

अटल पूर्णांक rxe_attach_mcast(काष्ठा ib_qp *ibqp, जोड़ ib_gid *mgid, u16 mlid)
अणु
	पूर्णांक err;
	काष्ठा rxe_dev *rxe = to_rdev(ibqp->device);
	काष्ठा rxe_qp *qp = to_rqp(ibqp);
	काष्ठा rxe_mc_grp *grp;

	/* takes a ref on grp अगर successful */
	err = rxe_mcast_get_grp(rxe, mgid, &grp);
	अगर (err)
		वापस err;

	err = rxe_mcast_add_grp_elem(rxe, qp, grp);

	rxe_drop_ref(grp);
	वापस err;
पूर्ण

अटल पूर्णांक rxe_detach_mcast(काष्ठा ib_qp *ibqp, जोड़ ib_gid *mgid, u16 mlid)
अणु
	काष्ठा rxe_dev *rxe = to_rdev(ibqp->device);
	काष्ठा rxe_qp *qp = to_rqp(ibqp);

	वापस rxe_mcast_drop_grp_elem(rxe, qp, mgid);
पूर्ण

अटल sमाप_प्रकार parent_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rxe_dev *rxe =
		rdma_device_to_drv_device(device, काष्ठा rxe_dev, ib_dev);

	वापस sysfs_emit(buf, "%s\n", rxe_parent_name(rxe, 1));
पूर्ण

अटल DEVICE_ATTR_RO(parent);

अटल काष्ठा attribute *rxe_dev_attributes[] = अणु
	&dev_attr_parent.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group rxe_attr_group = अणु
	.attrs = rxe_dev_attributes,
पूर्ण;

अटल पूर्णांक rxe_enable_driver(काष्ठा ib_device *ib_dev)
अणु
	काष्ठा rxe_dev *rxe = container_of(ib_dev, काष्ठा rxe_dev, ib_dev);

	rxe_set_port_state(rxe);
	dev_info(&rxe->ib_dev.dev, "added %s\n", netdev_name(rxe->ndev));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ib_device_ops rxe_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_RXE,
	.uverbs_abi_ver = RXE_UVERBS_ABI_VERSION,

	.alloc_hw_stats = rxe_ib_alloc_hw_stats,
	.alloc_mr = rxe_alloc_mr,
	.alloc_pd = rxe_alloc_pd,
	.alloc_ucontext = rxe_alloc_ucontext,
	.attach_mcast = rxe_attach_mcast,
	.create_ah = rxe_create_ah,
	.create_cq = rxe_create_cq,
	.create_qp = rxe_create_qp,
	.create_srq = rxe_create_srq,
	.create_user_ah = rxe_create_ah,
	.dealloc_driver = rxe_dealloc,
	.dealloc_pd = rxe_dealloc_pd,
	.dealloc_ucontext = rxe_dealloc_ucontext,
	.dereg_mr = rxe_dereg_mr,
	.destroy_ah = rxe_destroy_ah,
	.destroy_cq = rxe_destroy_cq,
	.destroy_qp = rxe_destroy_qp,
	.destroy_srq = rxe_destroy_srq,
	.detach_mcast = rxe_detach_mcast,
	.enable_driver = rxe_enable_driver,
	.get_dma_mr = rxe_get_dma_mr,
	.get_hw_stats = rxe_ib_get_hw_stats,
	.get_link_layer = rxe_get_link_layer,
	.get_port_immutable = rxe_port_immutable,
	.map_mr_sg = rxe_map_mr_sg,
	.mmap = rxe_mmap,
	.modअगरy_ah = rxe_modअगरy_ah,
	.modअगरy_device = rxe_modअगरy_device,
	.modअगरy_port = rxe_modअगरy_port,
	.modअगरy_qp = rxe_modअगरy_qp,
	.modअगरy_srq = rxe_modअगरy_srq,
	.peek_cq = rxe_peek_cq,
	.poll_cq = rxe_poll_cq,
	.post_recv = rxe_post_recv,
	.post_send = rxe_post_send,
	.post_srq_recv = rxe_post_srq_recv,
	.query_ah = rxe_query_ah,
	.query_device = rxe_query_device,
	.query_pkey = rxe_query_pkey,
	.query_port = rxe_query_port,
	.query_qp = rxe_query_qp,
	.query_srq = rxe_query_srq,
	.reg_user_mr = rxe_reg_user_mr,
	.req_notअगरy_cq = rxe_req_notअगरy_cq,
	.resize_cq = rxe_resize_cq,

	INIT_RDMA_OBJ_SIZE(ib_ah, rxe_ah, ibah),
	INIT_RDMA_OBJ_SIZE(ib_cq, rxe_cq, ibcq),
	INIT_RDMA_OBJ_SIZE(ib_pd, rxe_pd, ibpd),
	INIT_RDMA_OBJ_SIZE(ib_srq, rxe_srq, ibsrq),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, rxe_ucontext, ibuc),
	INIT_RDMA_OBJ_SIZE(ib_mw, rxe_mw, ibmw),
पूर्ण;

पूर्णांक rxe_रेजिस्टर_device(काष्ठा rxe_dev *rxe, स्थिर अक्षर *ibdev_name)
अणु
	पूर्णांक err;
	काष्ठा ib_device *dev = &rxe->ib_dev;
	काष्ठा crypto_shash *tfm;

	strscpy(dev->node_desc, "rxe", माप(dev->node_desc));

	dev->node_type = RDMA_NODE_IB_CA;
	dev->phys_port_cnt = 1;
	dev->num_comp_vectors = num_possible_cpus();
	dev->local_dma_lkey = 0;
	addrconf_addr_eui48((अचिन्हित अक्षर *)&dev->node_guid,
			    rxe->ndev->dev_addr);

	dev->uverbs_cmd_mask |= BIT_ULL(IB_USER_VERBS_CMD_POST_SEND) |
				BIT_ULL(IB_USER_VERBS_CMD_REQ_NOTIFY_CQ);

	ib_set_device_ops(dev, &rxe_dev_ops);
	err = ib_device_set_netdev(&rxe->ib_dev, rxe->ndev, 1);
	अगर (err)
		वापस err;

	tfm = crypto_alloc_shash("crc32", 0, 0);
	अगर (IS_ERR(tfm)) अणु
		pr_err("failed to allocate crc algorithm err:%ld\n",
		       PTR_ERR(tfm));
		वापस PTR_ERR(tfm);
	पूर्ण
	rxe->tfm = tfm;

	rdma_set_device_sysfs_group(dev, &rxe_attr_group);
	err = ib_रेजिस्टर_device(dev, ibdev_name, शून्य);
	अगर (err)
		pr_warn("%s failed with error %d\n", __func__, err);

	/*
	 * Note that rxe may be invalid at this poपूर्णांक अगर another thपढ़ो
	 * unरेजिस्टरed it.
	 */
	वापस err;
पूर्ण
