<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#अगर_अघोषित RXE_LOC_H
#घोषणा RXE_LOC_H

/* rxe_av.c */
व्योम rxe_init_av(काष्ठा rdma_ah_attr *attr, काष्ठा rxe_av *av);

पूर्णांक rxe_av_chk_attr(काष्ठा rxe_dev *rxe, काष्ठा rdma_ah_attr *attr);

व्योम rxe_av_from_attr(u8 port_num, काष्ठा rxe_av *av,
		     काष्ठा rdma_ah_attr *attr);

व्योम rxe_av_to_attr(काष्ठा rxe_av *av, काष्ठा rdma_ah_attr *attr);

व्योम rxe_av_fill_ip_info(काष्ठा rxe_av *av, काष्ठा rdma_ah_attr *attr);

काष्ठा rxe_av *rxe_get_av(काष्ठा rxe_pkt_info *pkt);

/* rxe_cq.c */
पूर्णांक rxe_cq_chk_attr(काष्ठा rxe_dev *rxe, काष्ठा rxe_cq *cq,
		    पूर्णांक cqe, पूर्णांक comp_vector);

पूर्णांक rxe_cq_from_init(काष्ठा rxe_dev *rxe, काष्ठा rxe_cq *cq, पूर्णांक cqe,
		     पूर्णांक comp_vector, काष्ठा ib_udata *udata,
		     काष्ठा rxe_create_cq_resp __user *uresp);

पूर्णांक rxe_cq_resize_queue(काष्ठा rxe_cq *cq, पूर्णांक new_cqe,
			काष्ठा rxe_resize_cq_resp __user *uresp,
			काष्ठा ib_udata *udata);

पूर्णांक rxe_cq_post(काष्ठा rxe_cq *cq, काष्ठा rxe_cqe *cqe, पूर्णांक solicited);

व्योम rxe_cq_disable(काष्ठा rxe_cq *cq);

व्योम rxe_cq_cleanup(काष्ठा rxe_pool_entry *arg);

/* rxe_mcast.c */
पूर्णांक rxe_mcast_get_grp(काष्ठा rxe_dev *rxe, जोड़ ib_gid *mgid,
		      काष्ठा rxe_mc_grp **grp_p);

पूर्णांक rxe_mcast_add_grp_elem(काष्ठा rxe_dev *rxe, काष्ठा rxe_qp *qp,
			   काष्ठा rxe_mc_grp *grp);

पूर्णांक rxe_mcast_drop_grp_elem(काष्ठा rxe_dev *rxe, काष्ठा rxe_qp *qp,
			    जोड़ ib_gid *mgid);

व्योम rxe_drop_all_mcast_groups(काष्ठा rxe_qp *qp);

व्योम rxe_mc_cleanup(काष्ठा rxe_pool_entry *arg);

/* rxe_mmap.c */
काष्ठा rxe_mmap_info अणु
	काष्ठा list_head	pending_mmaps;
	काष्ठा ib_ucontext	*context;
	काष्ठा kref		ref;
	व्योम			*obj;

	काष्ठा mminfo info;
पूर्ण;

व्योम rxe_mmap_release(काष्ठा kref *ref);

काष्ठा rxe_mmap_info *rxe_create_mmap_info(काष्ठा rxe_dev *dev, u32 size,
					   काष्ठा ib_udata *udata, व्योम *obj);

पूर्णांक rxe_mmap(काष्ठा ib_ucontext *context, काष्ठा vm_area_काष्ठा *vma);

/* rxe_mr.c */
क्रमागत copy_direction अणु
	to_mr_obj,
	from_mr_obj,
पूर्ण;

व्योम rxe_mr_init_dma(काष्ठा rxe_pd *pd, पूर्णांक access, काष्ठा rxe_mr *mr);

पूर्णांक rxe_mr_init_user(काष्ठा rxe_pd *pd, u64 start, u64 length, u64 iova,
		     पूर्णांक access, काष्ठा ib_udata *udata, काष्ठा rxe_mr *mr);

पूर्णांक rxe_mr_init_fast(काष्ठा rxe_pd *pd, पूर्णांक max_pages, काष्ठा rxe_mr *mr);

पूर्णांक rxe_mr_copy(काष्ठा rxe_mr *mr, u64 iova, व्योम *addr, पूर्णांक length,
		क्रमागत copy_direction dir, u32 *crcp);

पूर्णांक copy_data(काष्ठा rxe_pd *pd, पूर्णांक access,
	      काष्ठा rxe_dma_info *dma, व्योम *addr, पूर्णांक length,
	      क्रमागत copy_direction dir, u32 *crcp);

व्योम *iova_to_vaddr(काष्ठा rxe_mr *mr, u64 iova, पूर्णांक length);

क्रमागत lookup_type अणु
	lookup_local,
	lookup_remote,
पूर्ण;

काष्ठा rxe_mr *lookup_mr(काष्ठा rxe_pd *pd, पूर्णांक access, u32 key,
			 क्रमागत lookup_type type);

पूर्णांक mr_check_range(काष्ठा rxe_mr *mr, u64 iova, माप_प्रकार length);

व्योम rxe_mr_cleanup(काष्ठा rxe_pool_entry *arg);

पूर्णांक advance_dma_data(काष्ठा rxe_dma_info *dma, अचिन्हित पूर्णांक length);

/* rxe_net.c */
व्योम rxe_loopback(काष्ठा sk_buff *skb);
पूर्णांक rxe_send(काष्ठा rxe_pkt_info *pkt, काष्ठा sk_buff *skb);
काष्ठा sk_buff *rxe_init_packet(काष्ठा rxe_dev *rxe, काष्ठा rxe_av *av,
				पूर्णांक paylen, काष्ठा rxe_pkt_info *pkt);
पूर्णांक rxe_prepare(काष्ठा rxe_pkt_info *pkt, काष्ठा sk_buff *skb, u32 *crc);
स्थिर अक्षर *rxe_parent_name(काष्ठा rxe_dev *rxe, अचिन्हित पूर्णांक port_num);
पूर्णांक rxe_mcast_add(काष्ठा rxe_dev *rxe, जोड़ ib_gid *mgid);
पूर्णांक rxe_mcast_delete(काष्ठा rxe_dev *rxe, जोड़ ib_gid *mgid);

/* rxe_qp.c */
पूर्णांक rxe_qp_chk_init(काष्ठा rxe_dev *rxe, काष्ठा ib_qp_init_attr *init);

पूर्णांक rxe_qp_from_init(काष्ठा rxe_dev *rxe, काष्ठा rxe_qp *qp, काष्ठा rxe_pd *pd,
		     काष्ठा ib_qp_init_attr *init,
		     काष्ठा rxe_create_qp_resp __user *uresp,
		     काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata);

पूर्णांक rxe_qp_to_init(काष्ठा rxe_qp *qp, काष्ठा ib_qp_init_attr *init);

पूर्णांक rxe_qp_chk_attr(काष्ठा rxe_dev *rxe, काष्ठा rxe_qp *qp,
		    काष्ठा ib_qp_attr *attr, पूर्णांक mask);

पूर्णांक rxe_qp_from_attr(काष्ठा rxe_qp *qp, काष्ठा ib_qp_attr *attr,
		     पूर्णांक mask, काष्ठा ib_udata *udata);

पूर्णांक rxe_qp_to_attr(काष्ठा rxe_qp *qp, काष्ठा ib_qp_attr *attr, पूर्णांक mask);

व्योम rxe_qp_error(काष्ठा rxe_qp *qp);

व्योम rxe_qp_destroy(काष्ठा rxe_qp *qp);

व्योम rxe_qp_cleanup(काष्ठा rxe_pool_entry *arg);

अटल अंतरभूत पूर्णांक qp_num(काष्ठा rxe_qp *qp)
अणु
	वापस qp->ibqp.qp_num;
पूर्ण

अटल अंतरभूत क्रमागत ib_qp_type qp_type(काष्ठा rxe_qp *qp)
अणु
	वापस qp->ibqp.qp_type;
पूर्ण

अटल अंतरभूत क्रमागत ib_qp_state qp_state(काष्ठा rxe_qp *qp)
अणु
	वापस qp->attr.qp_state;
पूर्ण

अटल अंतरभूत पूर्णांक qp_mtu(काष्ठा rxe_qp *qp)
अणु
	अगर (qp->ibqp.qp_type == IB_QPT_RC || qp->ibqp.qp_type == IB_QPT_UC)
		वापस qp->attr.path_mtu;
	अन्यथा
		वापस IB_MTU_4096;
पूर्ण

अटल अंतरभूत पूर्णांक rcv_wqe_size(पूर्णांक max_sge)
अणु
	वापस माप(काष्ठा rxe_recv_wqe) +
		max_sge * माप(काष्ठा ib_sge);
पूर्ण

व्योम मुक्त_rd_atomic_resource(काष्ठा rxe_qp *qp, काष्ठा resp_res *res);

अटल अंतरभूत व्योम rxe_advance_resp_resource(काष्ठा rxe_qp *qp)
अणु
	qp->resp.res_head++;
	अगर (unlikely(qp->resp.res_head == qp->attr.max_dest_rd_atomic))
		qp->resp.res_head = 0;
पूर्ण

व्योम retransmit_समयr(काष्ठा समयr_list *t);
व्योम rnr_nak_समयr(काष्ठा समयr_list *t);

/* rxe_srq.c */
#घोषणा IB_SRQ_INIT_MASK (~IB_SRQ_LIMIT)

पूर्णांक rxe_srq_chk_attr(काष्ठा rxe_dev *rxe, काष्ठा rxe_srq *srq,
		     काष्ठा ib_srq_attr *attr, क्रमागत ib_srq_attr_mask mask);

पूर्णांक rxe_srq_from_init(काष्ठा rxe_dev *rxe, काष्ठा rxe_srq *srq,
		      काष्ठा ib_srq_init_attr *init, काष्ठा ib_udata *udata,
		      काष्ठा rxe_create_srq_resp __user *uresp);

पूर्णांक rxe_srq_from_attr(काष्ठा rxe_dev *rxe, काष्ठा rxe_srq *srq,
		      काष्ठा ib_srq_attr *attr, क्रमागत ib_srq_attr_mask mask,
		      काष्ठा rxe_modअगरy_srq_cmd *ucmd, काष्ठा ib_udata *udata);

व्योम rxe_dealloc(काष्ठा ib_device *ib_dev);

पूर्णांक rxe_completer(व्योम *arg);
पूर्णांक rxe_requester(व्योम *arg);
पूर्णांक rxe_responder(व्योम *arg);

u32 rxe_icrc_hdr(काष्ठा rxe_pkt_info *pkt, काष्ठा sk_buff *skb);

व्योम rxe_resp_queue_pkt(काष्ठा rxe_qp *qp, काष्ठा sk_buff *skb);

व्योम rxe_comp_queue_pkt(काष्ठा rxe_qp *qp, काष्ठा sk_buff *skb);

अटल अंतरभूत अचिन्हित पूर्णांक wr_opcode_mask(पूर्णांक opcode, काष्ठा rxe_qp *qp)
अणु
	वापस rxe_wr_opcode_info[opcode].mask[qp->ibqp.qp_type];
पूर्ण

अटल अंतरभूत पूर्णांक rxe_xmit_packet(काष्ठा rxe_qp *qp, काष्ठा rxe_pkt_info *pkt,
				  काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;
	पूर्णांक is_request = pkt->mask & RXE_REQ_MASK;
	काष्ठा rxe_dev *rxe = to_rdev(qp->ibqp.device);

	अगर ((is_request && (qp->req.state != QP_STATE_READY)) ||
	    (!is_request && (qp->resp.state != QP_STATE_READY))) अणु
		pr_info("Packet dropped. QP is not in ready state\n");
		जाओ drop;
	पूर्ण

	अगर (pkt->mask & RXE_LOOPBACK_MASK) अणु
		स_नकल(SKB_TO_PKT(skb), pkt, माप(*pkt));
		rxe_loopback(skb);
		err = 0;
	पूर्ण अन्यथा अणु
		err = rxe_send(pkt, skb);
	पूर्ण

	अगर (err) अणु
		rxe->xmit_errors++;
		rxe_counter_inc(rxe, RXE_CNT_SEND_ERR);
		वापस err;
	पूर्ण

	अगर ((qp_type(qp) != IB_QPT_RC) &&
	    (pkt->mask & RXE_END_MASK)) अणु
		pkt->wqe->state = wqe_state_करोne;
		rxe_run_task(&qp->comp.task, 1);
	पूर्ण

	rxe_counter_inc(rxe, RXE_CNT_SENT_PKTS);
	जाओ करोne;

drop:
	kमुक्त_skb(skb);
	err = 0;
करोne:
	वापस err;
पूर्ण

#पूर्ण_अगर /* RXE_LOC_H */
