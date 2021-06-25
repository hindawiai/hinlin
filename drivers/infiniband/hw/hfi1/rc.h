<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/*
 * Copyright(c) 2018 Intel Corporation.
 *
 */

#अगर_अघोषित HFI1_RC_H
#घोषणा HFI1_RC_H

/* cut करोwn ridiculously दीर्घ IB macro names */
#घोषणा OP(x) IB_OPCODE_RC_##x

अटल अंतरभूत व्योम update_ack_queue(काष्ठा rvt_qp *qp, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक next;

	next = n + 1;
	अगर (next > rvt_size_atomic(ib_to_rvt(qp->ibqp.device)))
		next = 0;
	qp->s_tail_ack_queue = next;
	qp->s_acked_ack_queue = next;
	qp->s_ack_state = OP(ACKNOWLEDGE);
पूर्ण

अटल अंतरभूत व्योम rc_defered_ack(काष्ठा hfi1_ctxtdata *rcd,
				  काष्ठा rvt_qp *qp)
अणु
	अगर (list_empty(&qp->rspरुको)) अणु
		qp->r_flags |= RVT_R_RSP_NAK;
		rvt_get_qp(qp);
		list_add_tail(&qp->rspरुको, &rcd->qp_रुको_list);
	पूर्ण
पूर्ण

अटल अंतरभूत u32 restart_sge(काष्ठा rvt_sge_state *ss, काष्ठा rvt_swqe *wqe,
			      u32 psn, u32 pmtu)
अणु
	u32 len;

	len = delta_psn(psn, wqe->psn) * pmtu;
	वापस rvt_restart_sge(ss, wqe, len);
पूर्ण

अटल अंतरभूत व्योम release_rdma_sge_mr(काष्ठा rvt_ack_entry *e)
अणु
	अगर (e->rdma_sge.mr) अणु
		rvt_put_mr(e->rdma_sge.mr);
		e->rdma_sge.mr = शून्य;
	पूर्ण
पूर्ण

काष्ठा rvt_ack_entry *find_prev_entry(काष्ठा rvt_qp *qp, u32 psn, u8 *prev,
				      u8 *prev_ack, bool *scheduled);
पूर्णांक करो_rc_ack(काष्ठा rvt_qp *qp, u32 aeth, u32 psn, पूर्णांक opcode, u64 val,
	      काष्ठा hfi1_ctxtdata *rcd);
काष्ठा rvt_swqe *करो_rc_completion(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
				  काष्ठा hfi1_ibport *ibp);

#पूर्ण_अगर /* HFI1_RC_H */
