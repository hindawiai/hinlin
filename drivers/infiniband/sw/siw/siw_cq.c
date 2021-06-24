<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause

/* Authors: Bernard Metzler <bmt@zurich.ibm.com> */
/* Copyright (c) 2008-2019, IBM Corporation */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>

#समावेश <rdma/ib_verbs.h>

#समावेश "siw.h"

अटल पूर्णांक map_wc_opcode[SIW_NUM_OPCODES] = अणु
	[SIW_OP_WRITE] = IB_WC_RDMA_WRITE,
	[SIW_OP_SEND] = IB_WC_SEND,
	[SIW_OP_SEND_WITH_IMM] = IB_WC_SEND,
	[SIW_OP_READ] = IB_WC_RDMA_READ,
	[SIW_OP_READ_LOCAL_INV] = IB_WC_RDMA_READ,
	[SIW_OP_COMP_AND_SWAP] = IB_WC_COMP_SWAP,
	[SIW_OP_FETCH_AND_ADD] = IB_WC_FETCH_ADD,
	[SIW_OP_INVAL_STAG] = IB_WC_LOCAL_INV,
	[SIW_OP_REG_MR] = IB_WC_REG_MR,
	[SIW_OP_RECEIVE] = IB_WC_RECV,
	[SIW_OP_READ_RESPONSE] = -1 /* not used */
पूर्ण;

अटल काष्ठा अणु
	क्रमागत siw_wc_status siw;
	क्रमागत ib_wc_status ib;
पूर्ण map_cqe_status[SIW_NUM_WC_STATUS] = अणु
	अणु SIW_WC_SUCCESS, IB_WC_SUCCESS पूर्ण,
	अणु SIW_WC_LOC_LEN_ERR, IB_WC_LOC_LEN_ERR पूर्ण,
	अणु SIW_WC_LOC_PROT_ERR, IB_WC_LOC_PROT_ERR पूर्ण,
	अणु SIW_WC_LOC_QP_OP_ERR, IB_WC_LOC_QP_OP_ERR पूर्ण,
	अणु SIW_WC_WR_FLUSH_ERR, IB_WC_WR_FLUSH_ERR पूर्ण,
	अणु SIW_WC_BAD_RESP_ERR, IB_WC_BAD_RESP_ERR पूर्ण,
	अणु SIW_WC_LOC_ACCESS_ERR, IB_WC_LOC_ACCESS_ERR पूर्ण,
	अणु SIW_WC_REM_ACCESS_ERR, IB_WC_REM_ACCESS_ERR पूर्ण,
	अणु SIW_WC_REM_INV_REQ_ERR, IB_WC_REM_INV_REQ_ERR पूर्ण,
	अणु SIW_WC_GENERAL_ERR, IB_WC_GENERAL_ERR पूर्ण
पूर्ण;

/*
 * Reap one CQE from the CQ. Only used by kernel clients
 * during CQ normal operation. Might be called during CQ
 * flush क्रम user mapped CQE array as well.
 */
पूर्णांक siw_reap_cqe(काष्ठा siw_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा siw_cqe *cqe;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cq->lock, flags);

	cqe = &cq->queue[cq->cq_get % cq->num_cqe];
	अगर (READ_ONCE(cqe->flags) & SIW_WQE_VALID) अणु
		स_रखो(wc, 0, माप(*wc));
		wc->wr_id = cqe->id;
		wc->status = map_cqe_status[cqe->status].ib;
		wc->opcode = map_wc_opcode[cqe->opcode];
		wc->byte_len = cqe->bytes;

		/*
		 * During CQ flush, also user land CQE's may get
		 * reaped here, which करो not hold a QP reference
		 * and करो not qualअगरy क्रम memory extension verbs.
		 */
		अगर (likely(rdma_is_kernel_res(&cq->base_cq.res))) अणु
			अगर (cqe->flags & SIW_WQE_REM_INVAL) अणु
				wc->ex.invalidate_rkey = cqe->inval_stag;
				wc->wc_flags = IB_WC_WITH_INVALIDATE;
			पूर्ण
			wc->qp = cqe->base_qp;
			siw_dbg_cq(cq,
				   "idx %u, type %d, flags %2x, id 0x%pK\n",
				   cq->cq_get % cq->num_cqe, cqe->opcode,
				   cqe->flags, (व्योम *)(uपूर्णांकptr_t)cqe->id);
		पूर्ण
		WRITE_ONCE(cqe->flags, 0);
		cq->cq_get++;

		spin_unlock_irqrestore(&cq->lock, flags);

		वापस 1;
	पूर्ण
	spin_unlock_irqrestore(&cq->lock, flags);

	वापस 0;
पूर्ण

/*
 * siw_cq_flush()
 *
 * Flush all CQ elements.
 */
व्योम siw_cq_flush(काष्ठा siw_cq *cq)
अणु
	काष्ठा ib_wc wc;

	जबतक (siw_reap_cqe(cq, &wc))
		;
पूर्ण
