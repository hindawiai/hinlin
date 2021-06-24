<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2005, 2006 Cisco Systems, Inc. All rights reserved.
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

#समावेश <linux/gfp.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/पन.स>

#समावेश <rdma/ib_pack.h>

#समावेश "mthca_dev.h"
#समावेश "mthca_cmd.h"
#समावेश "mthca_memfree.h"

क्रमागत अणु
	MTHCA_MAX_सूचीECT_CQ_SIZE = 4 * PAGE_SIZE
पूर्ण;

क्रमागत अणु
	MTHCA_CQ_ENTRY_SIZE = 0x20
पूर्ण;

क्रमागत अणु
	MTHCA_ATOMIC_BYTE_LEN = 8
पूर्ण;

/*
 * Must be packed because start is 64 bits but only aligned to 32 bits.
 */
काष्ठा mthca_cq_context अणु
	__be32 flags;
	__be64 start;
	__be32 logsize_usrpage;
	__be32 error_eqn;	/* Tavor only */
	__be32 comp_eqn;
	__be32 pd;
	__be32 lkey;
	__be32 last_notअगरied_index;
	__be32 solicit_producer_index;
	__be32 consumer_index;
	__be32 producer_index;
	__be32 cqn;
	__be32 ci_db;		/* Arbel only */
	__be32 state_db;	/* Arbel only */
	u32    reserved;
पूर्ण __packed;

#घोषणा MTHCA_CQ_STATUS_OK          ( 0 << 28)
#घोषणा MTHCA_CQ_STATUS_OVERFLOW    ( 9 << 28)
#घोषणा MTHCA_CQ_STATUS_WRITE_FAIL  (10 << 28)
#घोषणा MTHCA_CQ_FLAG_TR            ( 1 << 18)
#घोषणा MTHCA_CQ_FLAG_OI            ( 1 << 17)
#घोषणा MTHCA_CQ_STATE_DISARMED     ( 0 <<  8)
#घोषणा MTHCA_CQ_STATE_ARMED        ( 1 <<  8)
#घोषणा MTHCA_CQ_STATE_ARMED_SOL    ( 4 <<  8)
#घोषणा MTHCA_EQ_STATE_FIRED        (10 <<  8)

क्रमागत अणु
	MTHCA_ERROR_CQE_OPCODE_MASK = 0xfe
पूर्ण;

क्रमागत अणु
	SYNDROME_LOCAL_LENGTH_ERR 	 = 0x01,
	SYNDROME_LOCAL_QP_OP_ERR  	 = 0x02,
	SYNDROME_LOCAL_EEC_OP_ERR 	 = 0x03,
	SYNDROME_LOCAL_PROT_ERR   	 = 0x04,
	SYNDROME_WR_FLUSH_ERR     	 = 0x05,
	SYNDROME_MW_BIND_ERR      	 = 0x06,
	SYNDROME_BAD_RESP_ERR     	 = 0x10,
	SYNDROME_LOCAL_ACCESS_ERR 	 = 0x11,
	SYNDROME_REMOTE_INVAL_REQ_ERR 	 = 0x12,
	SYNDROME_REMOTE_ACCESS_ERR 	 = 0x13,
	SYNDROME_REMOTE_OP_ERR     	 = 0x14,
	SYNDROME_RETRY_EXC_ERR 		 = 0x15,
	SYNDROME_RNR_RETRY_EXC_ERR 	 = 0x16,
	SYNDROME_LOCAL_RDD_VIOL_ERR 	 = 0x20,
	SYNDROME_REMOTE_INVAL_RD_REQ_ERR = 0x21,
	SYNDROME_REMOTE_ABORTED_ERR 	 = 0x22,
	SYNDROME_INVAL_EECN_ERR 	 = 0x23,
	SYNDROME_INVAL_EEC_STATE_ERR 	 = 0x24
पूर्ण;

काष्ठा mthca_cqe अणु
	__be32 my_qpn;
	__be32 my_ee;
	__be32 rqpn;
	u8     sl_ipok;
	u8     g_mlpath;
	__be16 rlid;
	__be32 imm_etype_pkey_eec;
	__be32 byte_cnt;
	__be32 wqe;
	u8     opcode;
	u8     is_send;
	u8     reserved;
	u8     owner;
पूर्ण;

काष्ठा mthca_err_cqe अणु
	__be32 my_qpn;
	u32    reserved1[3];
	u8     syndrome;
	u8     venकरोr_err;
	__be16 db_cnt;
	u32    reserved2;
	__be32 wqe;
	u8     opcode;
	u8     reserved3[2];
	u8     owner;
पूर्ण;

#घोषणा MTHCA_CQ_ENTRY_OWNER_SW      (0 << 7)
#घोषणा MTHCA_CQ_ENTRY_OWNER_HW      (1 << 7)

#घोषणा MTHCA_TAVOR_CQ_DB_INC_CI       (1 << 24)
#घोषणा MTHCA_TAVOR_CQ_DB_REQ_NOT      (2 << 24)
#घोषणा MTHCA_TAVOR_CQ_DB_REQ_NOT_SOL  (3 << 24)
#घोषणा MTHCA_TAVOR_CQ_DB_SET_CI       (4 << 24)
#घोषणा MTHCA_TAVOR_CQ_DB_REQ_NOT_MULT (5 << 24)

#घोषणा MTHCA_ARBEL_CQ_DB_REQ_NOT_SOL  (1 << 24)
#घोषणा MTHCA_ARBEL_CQ_DB_REQ_NOT      (2 << 24)
#घोषणा MTHCA_ARBEL_CQ_DB_REQ_NOT_MULT (3 << 24)

अटल अंतरभूत काष्ठा mthca_cqe *get_cqe_from_buf(काष्ठा mthca_cq_buf *buf,
						 पूर्णांक entry)
अणु
	अगर (buf->is_direct)
		वापस buf->queue.direct.buf + (entry * MTHCA_CQ_ENTRY_SIZE);
	अन्यथा
		वापस buf->queue.page_list[entry * MTHCA_CQ_ENTRY_SIZE / PAGE_SIZE].buf
			+ (entry * MTHCA_CQ_ENTRY_SIZE) % PAGE_SIZE;
पूर्ण

अटल अंतरभूत काष्ठा mthca_cqe *get_cqe(काष्ठा mthca_cq *cq, पूर्णांक entry)
अणु
	वापस get_cqe_from_buf(&cq->buf, entry);
पूर्ण

अटल अंतरभूत काष्ठा mthca_cqe *cqe_sw(काष्ठा mthca_cqe *cqe)
अणु
	वापस MTHCA_CQ_ENTRY_OWNER_HW & cqe->owner ? शून्य : cqe;
पूर्ण

अटल अंतरभूत काष्ठा mthca_cqe *next_cqe_sw(काष्ठा mthca_cq *cq)
अणु
	वापस cqe_sw(get_cqe(cq, cq->cons_index & cq->ibcq.cqe));
पूर्ण

अटल अंतरभूत व्योम set_cqe_hw(काष्ठा mthca_cqe *cqe)
अणु
	cqe->owner = MTHCA_CQ_ENTRY_OWNER_HW;
पूर्ण

अटल व्योम dump_cqe(काष्ठा mthca_dev *dev, व्योम *cqe_ptr)
अणु
	__be32 *cqe = cqe_ptr;

	(व्योम) cqe;	/* aव्योम warning अगर mthca_dbg compiled away... */
	mthca_dbg(dev, "CQE contents %08x %08x %08x %08x %08x %08x %08x %08x\n",
		  be32_to_cpu(cqe[0]), be32_to_cpu(cqe[1]), be32_to_cpu(cqe[2]),
		  be32_to_cpu(cqe[3]), be32_to_cpu(cqe[4]), be32_to_cpu(cqe[5]),
		  be32_to_cpu(cqe[6]), be32_to_cpu(cqe[7]));
पूर्ण

/*
 * incr is ignored in native Arbel (mem-मुक्त) mode, so cq->cons_index
 * should be correct beक्रमe calling update_cons_index().
 */
अटल अंतरभूत व्योम update_cons_index(काष्ठा mthca_dev *dev, काष्ठा mthca_cq *cq,
				     पूर्णांक incr)
अणु
	अगर (mthca_is_memमुक्त(dev)) अणु
		*cq->set_ci_db = cpu_to_be32(cq->cons_index);
		wmb();
	पूर्ण अन्यथा अणु
		mthca_ग_लिखो64(MTHCA_TAVOR_CQ_DB_INC_CI | cq->cqn, incr - 1,
			      dev->kar + MTHCA_CQ_DOORBELL,
			      MTHCA_GET_DOORBELL_LOCK(&dev->करोorbell_lock));
	पूर्ण
पूर्ण

व्योम mthca_cq_completion(काष्ठा mthca_dev *dev, u32 cqn)
अणु
	काष्ठा mthca_cq *cq;

	cq = mthca_array_get(&dev->cq_table.cq, cqn & (dev->limits.num_cqs - 1));

	अगर (!cq) अणु
		mthca_warn(dev, "Completion event for bogus CQ %08x\n", cqn);
		वापस;
	पूर्ण

	++cq->arm_sn;

	cq->ibcq.comp_handler(&cq->ibcq, cq->ibcq.cq_context);
पूर्ण

व्योम mthca_cq_event(काष्ठा mthca_dev *dev, u32 cqn,
		    क्रमागत ib_event_type event_type)
अणु
	काष्ठा mthca_cq *cq;
	काष्ठा ib_event event;

	spin_lock(&dev->cq_table.lock);

	cq = mthca_array_get(&dev->cq_table.cq, cqn & (dev->limits.num_cqs - 1));
	अगर (cq)
		++cq->refcount;

	spin_unlock(&dev->cq_table.lock);

	अगर (!cq) अणु
		mthca_warn(dev, "Async event for bogus CQ %08x\n", cqn);
		वापस;
	पूर्ण

	event.device      = &dev->ib_dev;
	event.event       = event_type;
	event.element.cq  = &cq->ibcq;
	अगर (cq->ibcq.event_handler)
		cq->ibcq.event_handler(&event, cq->ibcq.cq_context);

	spin_lock(&dev->cq_table.lock);
	अगर (!--cq->refcount)
		wake_up(&cq->रुको);
	spin_unlock(&dev->cq_table.lock);
पूर्ण

अटल अंतरभूत पूर्णांक is_recv_cqe(काष्ठा mthca_cqe *cqe)
अणु
	अगर ((cqe->opcode & MTHCA_ERROR_CQE_OPCODE_MASK) ==
	    MTHCA_ERROR_CQE_OPCODE_MASK)
		वापस !(cqe->opcode & 0x01);
	अन्यथा
		वापस !(cqe->is_send & 0x80);
पूर्ण

व्योम mthca_cq_clean(काष्ठा mthca_dev *dev, काष्ठा mthca_cq *cq, u32 qpn,
		    काष्ठा mthca_srq *srq)
अणु
	काष्ठा mthca_cqe *cqe;
	u32 prod_index;
	पूर्णांक i, nमुक्तd = 0;

	spin_lock_irq(&cq->lock);

	/*
	 * First we need to find the current producer index, so we
	 * know where to start cleaning from.  It करोesn't matter अगर HW
	 * adds new entries after this loop -- the QP we're worried
	 * about is alपढ़ोy in RESET, so the new entries won't come
	 * from our QP and thereक्रमe करोn't need to be checked.
	 */
	क्रम (prod_index = cq->cons_index;
	     cqe_sw(get_cqe(cq, prod_index & cq->ibcq.cqe));
	     ++prod_index)
		अगर (prod_index == cq->cons_index + cq->ibcq.cqe)
			अवरोध;

	अगर (0)
		mthca_dbg(dev, "Cleaning QPN %06x from CQN %06x; ci %d, pi %d\n",
			  qpn, cq->cqn, cq->cons_index, prod_index);

	/*
	 * Now sweep backwards through the CQ, removing CQ entries
	 * that match our QP by copying older entries on top of them.
	 */
	जबतक ((पूर्णांक) --prod_index - (पूर्णांक) cq->cons_index >= 0) अणु
		cqe = get_cqe(cq, prod_index & cq->ibcq.cqe);
		अगर (cqe->my_qpn == cpu_to_be32(qpn)) अणु
			अगर (srq && is_recv_cqe(cqe))
				mthca_मुक्त_srq_wqe(srq, be32_to_cpu(cqe->wqe));
			++nमुक्तd;
		पूर्ण अन्यथा अगर (nमुक्तd)
			स_नकल(get_cqe(cq, (prod_index + nमुक्तd) & cq->ibcq.cqe),
			       cqe, MTHCA_CQ_ENTRY_SIZE);
	पूर्ण

	अगर (nमुक्तd) अणु
		क्रम (i = 0; i < nमुक्तd; ++i)
			set_cqe_hw(get_cqe(cq, (cq->cons_index + i) & cq->ibcq.cqe));
		wmb();
		cq->cons_index += nमुक्तd;
		update_cons_index(dev, cq, nमुक्तd);
	पूर्ण

	spin_unlock_irq(&cq->lock);
पूर्ण

व्योम mthca_cq_resize_copy_cqes(काष्ठा mthca_cq *cq)
अणु
	पूर्णांक i;

	/*
	 * In Tavor mode, the hardware keeps the consumer and producer
	 * indices mod the CQ size.  Since we might be making the CQ
	 * bigger, we need to deal with the हाल where the producer
	 * index wrapped around beक्रमe the CQ was resized.
	 */
	अगर (!mthca_is_memमुक्त(to_mdev(cq->ibcq.device)) &&
	    cq->ibcq.cqe < cq->resize_buf->cqe) अणु
		cq->cons_index &= cq->ibcq.cqe;
		अगर (cqe_sw(get_cqe(cq, cq->ibcq.cqe)))
			cq->cons_index -= cq->ibcq.cqe + 1;
	पूर्ण

	क्रम (i = cq->cons_index; cqe_sw(get_cqe(cq, i & cq->ibcq.cqe)); ++i)
		स_नकल(get_cqe_from_buf(&cq->resize_buf->buf,
					i & cq->resize_buf->cqe),
		       get_cqe(cq, i & cq->ibcq.cqe), MTHCA_CQ_ENTRY_SIZE);
पूर्ण

पूर्णांक mthca_alloc_cq_buf(काष्ठा mthca_dev *dev, काष्ठा mthca_cq_buf *buf, पूर्णांक nent)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	ret = mthca_buf_alloc(dev, nent * MTHCA_CQ_ENTRY_SIZE,
			      MTHCA_MAX_सूचीECT_CQ_SIZE,
			      &buf->queue, &buf->is_direct,
			      &dev->driver_pd, 1, &buf->mr);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nent; ++i)
		set_cqe_hw(get_cqe_from_buf(buf, i));

	वापस 0;
पूर्ण

व्योम mthca_मुक्त_cq_buf(काष्ठा mthca_dev *dev, काष्ठा mthca_cq_buf *buf, पूर्णांक cqe)
अणु
	mthca_buf_मुक्त(dev, (cqe + 1) * MTHCA_CQ_ENTRY_SIZE, &buf->queue,
		       buf->is_direct, &buf->mr);
पूर्ण

अटल व्योम handle_error_cqe(काष्ठा mthca_dev *dev, काष्ठा mthca_cq *cq,
			     काष्ठा mthca_qp *qp, पूर्णांक wqe_index, पूर्णांक is_send,
			     काष्ठा mthca_err_cqe *cqe,
			     काष्ठा ib_wc *entry, पूर्णांक *मुक्त_cqe)
अणु
	पूर्णांक dbd;
	__be32 new_wqe;

	अगर (cqe->syndrome == SYNDROME_LOCAL_QP_OP_ERR) अणु
		mthca_dbg(dev, "local QP operation err "
			  "(QPN %06x, WQE @ %08x, CQN %06x, index %d)\n",
			  be32_to_cpu(cqe->my_qpn), be32_to_cpu(cqe->wqe),
			  cq->cqn, cq->cons_index);
		dump_cqe(dev, cqe);
	पूर्ण

	/*
	 * For completions in error, only work request ID, status, venकरोr error
	 * (and मुक्तd resource count क्रम RD) have to be set.
	 */
	चयन (cqe->syndrome) अणु
	हाल SYNDROME_LOCAL_LENGTH_ERR:
		entry->status = IB_WC_LOC_LEN_ERR;
		अवरोध;
	हाल SYNDROME_LOCAL_QP_OP_ERR:
		entry->status = IB_WC_LOC_QP_OP_ERR;
		अवरोध;
	हाल SYNDROME_LOCAL_EEC_OP_ERR:
		entry->status = IB_WC_LOC_EEC_OP_ERR;
		अवरोध;
	हाल SYNDROME_LOCAL_PROT_ERR:
		entry->status = IB_WC_LOC_PROT_ERR;
		अवरोध;
	हाल SYNDROME_WR_FLUSH_ERR:
		entry->status = IB_WC_WR_FLUSH_ERR;
		अवरोध;
	हाल SYNDROME_MW_BIND_ERR:
		entry->status = IB_WC_MW_BIND_ERR;
		अवरोध;
	हाल SYNDROME_BAD_RESP_ERR:
		entry->status = IB_WC_BAD_RESP_ERR;
		अवरोध;
	हाल SYNDROME_LOCAL_ACCESS_ERR:
		entry->status = IB_WC_LOC_ACCESS_ERR;
		अवरोध;
	हाल SYNDROME_REMOTE_INVAL_REQ_ERR:
		entry->status = IB_WC_REM_INV_REQ_ERR;
		अवरोध;
	हाल SYNDROME_REMOTE_ACCESS_ERR:
		entry->status = IB_WC_REM_ACCESS_ERR;
		अवरोध;
	हाल SYNDROME_REMOTE_OP_ERR:
		entry->status = IB_WC_REM_OP_ERR;
		अवरोध;
	हाल SYNDROME_RETRY_EXC_ERR:
		entry->status = IB_WC_RETRY_EXC_ERR;
		अवरोध;
	हाल SYNDROME_RNR_RETRY_EXC_ERR:
		entry->status = IB_WC_RNR_RETRY_EXC_ERR;
		अवरोध;
	हाल SYNDROME_LOCAL_RDD_VIOL_ERR:
		entry->status = IB_WC_LOC_RDD_VIOL_ERR;
		अवरोध;
	हाल SYNDROME_REMOTE_INVAL_RD_REQ_ERR:
		entry->status = IB_WC_REM_INV_RD_REQ_ERR;
		अवरोध;
	हाल SYNDROME_REMOTE_ABORTED_ERR:
		entry->status = IB_WC_REM_ABORT_ERR;
		अवरोध;
	हाल SYNDROME_INVAL_EECN_ERR:
		entry->status = IB_WC_INV_EECN_ERR;
		अवरोध;
	हाल SYNDROME_INVAL_EEC_STATE_ERR:
		entry->status = IB_WC_INV_EEC_STATE_ERR;
		अवरोध;
	शेष:
		entry->status = IB_WC_GENERAL_ERR;
		अवरोध;
	पूर्ण

	entry->venकरोr_err = cqe->venकरोr_err;

	/*
	 * Mem-मुक्त HCAs always generate one CQE per WQE, even in the
	 * error हाल, so we करोn't have to check the करोorbell count, etc.
	 */
	अगर (mthca_is_memमुक्त(dev))
		वापस;

	mthca_मुक्त_err_wqe(dev, qp, is_send, wqe_index, &dbd, &new_wqe);

	/*
	 * If we're at the end of the WQE chain, or we've used up our
	 * करोorbell count, मुक्त the CQE.  Otherwise just update it क्रम
	 * the next poll operation.
	 */
	अगर (!(new_wqe & cpu_to_be32(0x3f)) || (!cqe->db_cnt && dbd))
		वापस;

	be16_add_cpu(&cqe->db_cnt, -dbd);
	cqe->wqe      = new_wqe;
	cqe->syndrome = SYNDROME_WR_FLUSH_ERR;

	*मुक्त_cqe = 0;
पूर्ण

अटल अंतरभूत पूर्णांक mthca_poll_one(काष्ठा mthca_dev *dev,
				 काष्ठा mthca_cq *cq,
				 काष्ठा mthca_qp **cur_qp,
				 पूर्णांक *मुक्तd,
				 काष्ठा ib_wc *entry)
अणु
	काष्ठा mthca_wq *wq;
	काष्ठा mthca_cqe *cqe;
	पूर्णांक wqe_index;
	पूर्णांक is_error;
	पूर्णांक is_send;
	पूर्णांक मुक्त_cqe = 1;
	पूर्णांक err = 0;
	u16 checksum;

	cqe = next_cqe_sw(cq);
	अगर (!cqe)
		वापस -EAGAIN;

	/*
	 * Make sure we पढ़ो CQ entry contents after we've checked the
	 * ownership bit.
	 */
	rmb();

	अगर (0) अणु
		mthca_dbg(dev, "%x/%d: CQE -> QPN %06x, WQE @ %08x\n",
			  cq->cqn, cq->cons_index, be32_to_cpu(cqe->my_qpn),
			  be32_to_cpu(cqe->wqe));
		dump_cqe(dev, cqe);
	पूर्ण

	is_error = (cqe->opcode & MTHCA_ERROR_CQE_OPCODE_MASK) ==
		MTHCA_ERROR_CQE_OPCODE_MASK;
	is_send  = is_error ? cqe->opcode & 0x01 : cqe->is_send & 0x80;

	अगर (!*cur_qp || be32_to_cpu(cqe->my_qpn) != (*cur_qp)->qpn) अणु
		/*
		 * We करो not have to take the QP table lock here,
		 * because CQs will be locked जबतक QPs are हटाओd
		 * from the table.
		 */
		*cur_qp = mthca_array_get(&dev->qp_table.qp,
					  be32_to_cpu(cqe->my_qpn) &
					  (dev->limits.num_qps - 1));
		अगर (!*cur_qp) अणु
			mthca_warn(dev, "CQ entry for unknown QP %06x\n",
				   be32_to_cpu(cqe->my_qpn) & 0xffffff);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	entry->qp = &(*cur_qp)->ibqp;

	अगर (is_send) अणु
		wq = &(*cur_qp)->sq;
		wqe_index = ((be32_to_cpu(cqe->wqe) - (*cur_qp)->send_wqe_offset)
			     >> wq->wqe_shअगरt);
		entry->wr_id = (*cur_qp)->wrid[wqe_index +
					       (*cur_qp)->rq.max];
	पूर्ण अन्यथा अगर ((*cur_qp)->ibqp.srq) अणु
		काष्ठा mthca_srq *srq = to_msrq((*cur_qp)->ibqp.srq);
		u32 wqe = be32_to_cpu(cqe->wqe);
		wq = शून्य;
		wqe_index = wqe >> srq->wqe_shअगरt;
		entry->wr_id = srq->wrid[wqe_index];
		mthca_मुक्त_srq_wqe(srq, wqe);
	पूर्ण अन्यथा अणु
		s32 wqe;
		wq = &(*cur_qp)->rq;
		wqe = be32_to_cpu(cqe->wqe);
		wqe_index = wqe >> wq->wqe_shअगरt;
		/*
		 * WQE addr == base - 1 might be reported in receive completion
		 * with error instead of (rq size - 1) by Sinai FW 1.0.800 and
		 * Arbel FW 5.1.400.  This bug should be fixed in later FW revs.
		 */
		अगर (unlikely(wqe_index < 0))
			wqe_index = wq->max - 1;
		entry->wr_id = (*cur_qp)->wrid[wqe_index];
	पूर्ण

	अगर (wq) अणु
		अगर (wq->last_comp < wqe_index)
			wq->tail += wqe_index - wq->last_comp;
		अन्यथा
			wq->tail += wqe_index + wq->max - wq->last_comp;

		wq->last_comp = wqe_index;
	पूर्ण

	अगर (is_error) अणु
		handle_error_cqe(dev, cq, *cur_qp, wqe_index, is_send,
				 (काष्ठा mthca_err_cqe *) cqe,
				 entry, &मुक्त_cqe);
		जाओ out;
	पूर्ण

	अगर (is_send) अणु
		entry->wc_flags = 0;
		चयन (cqe->opcode) अणु
		हाल MTHCA_OPCODE_RDMA_WRITE:
			entry->opcode    = IB_WC_RDMA_WRITE;
			अवरोध;
		हाल MTHCA_OPCODE_RDMA_WRITE_IMM:
			entry->opcode    = IB_WC_RDMA_WRITE;
			entry->wc_flags |= IB_WC_WITH_IMM;
			अवरोध;
		हाल MTHCA_OPCODE_SEND:
			entry->opcode    = IB_WC_SEND;
			अवरोध;
		हाल MTHCA_OPCODE_SEND_IMM:
			entry->opcode    = IB_WC_SEND;
			entry->wc_flags |= IB_WC_WITH_IMM;
			अवरोध;
		हाल MTHCA_OPCODE_RDMA_READ:
			entry->opcode    = IB_WC_RDMA_READ;
			entry->byte_len  = be32_to_cpu(cqe->byte_cnt);
			अवरोध;
		हाल MTHCA_OPCODE_ATOMIC_CS:
			entry->opcode    = IB_WC_COMP_SWAP;
			entry->byte_len  = MTHCA_ATOMIC_BYTE_LEN;
			अवरोध;
		हाल MTHCA_OPCODE_ATOMIC_FA:
			entry->opcode    = IB_WC_FETCH_ADD;
			entry->byte_len  = MTHCA_ATOMIC_BYTE_LEN;
			अवरोध;
		शेष:
			entry->opcode = 0xFF;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		entry->byte_len = be32_to_cpu(cqe->byte_cnt);
		चयन (cqe->opcode & 0x1f) अणु
		हाल IB_OPCODE_SEND_LAST_WITH_IMMEDIATE:
		हाल IB_OPCODE_SEND_ONLY_WITH_IMMEDIATE:
			entry->wc_flags = IB_WC_WITH_IMM;
			entry->ex.imm_data = cqe->imm_etype_pkey_eec;
			entry->opcode = IB_WC_RECV;
			अवरोध;
		हाल IB_OPCODE_RDMA_WRITE_LAST_WITH_IMMEDIATE:
		हाल IB_OPCODE_RDMA_WRITE_ONLY_WITH_IMMEDIATE:
			entry->wc_flags = IB_WC_WITH_IMM;
			entry->ex.imm_data = cqe->imm_etype_pkey_eec;
			entry->opcode = IB_WC_RECV_RDMA_WITH_IMM;
			अवरोध;
		शेष:
			entry->wc_flags = 0;
			entry->opcode = IB_WC_RECV;
			अवरोध;
		पूर्ण
		entry->slid 	   = be16_to_cpu(cqe->rlid);
		entry->sl   	   = cqe->sl_ipok >> 4;
		entry->src_qp 	   = be32_to_cpu(cqe->rqpn) & 0xffffff;
		entry->dlid_path_bits = cqe->g_mlpath & 0x7f;
		entry->pkey_index  = be32_to_cpu(cqe->imm_etype_pkey_eec) >> 16;
		entry->wc_flags   |= cqe->g_mlpath & 0x80 ? IB_WC_GRH : 0;
		checksum = (be32_to_cpu(cqe->rqpn) >> 24) |
				((be32_to_cpu(cqe->my_ee) >> 16) & 0xff00);
		entry->wc_flags	  |=  (cqe->sl_ipok & 1 && checksum == 0xffff) ?
							IB_WC_IP_CSUM_OK : 0;
	पूर्ण

	entry->status = IB_WC_SUCCESS;

 out:
	अगर (likely(मुक्त_cqe)) अणु
		set_cqe_hw(cqe);
		++(*मुक्तd);
		++cq->cons_index;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक mthca_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries,
		  काष्ठा ib_wc *entry)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibcq->device);
	काष्ठा mthca_cq *cq = to_mcq(ibcq);
	काष्ठा mthca_qp *qp = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	पूर्णांक मुक्तd = 0;
	पूर्णांक npolled;

	spin_lock_irqsave(&cq->lock, flags);

	npolled = 0;
repoll:
	जबतक (npolled < num_entries) अणु
		err = mthca_poll_one(dev, cq, &qp,
				     &मुक्तd, entry + npolled);
		अगर (err)
			अवरोध;
		++npolled;
	पूर्ण

	अगर (मुक्तd) अणु
		wmb();
		update_cons_index(dev, cq, मुक्तd);
	पूर्ण

	/*
	 * If a CQ resize is in progress and we discovered that the
	 * old buffer is empty, then peek in the new buffer, and अगर
	 * it's not empty, चयन to the new buffer and जारी
	 * polling there.
	 */
	अगर (unlikely(err == -EAGAIN && cq->resize_buf &&
		     cq->resize_buf->state == CQ_RESIZE_READY)) अणु
		/*
		 * In Tavor mode, the hardware keeps the producer
		 * index modulo the CQ size.  Since we might be making
		 * the CQ bigger, we need to mask our consumer index
		 * using the size of the old CQ buffer beक्रमe looking
		 * in the new CQ buffer.
		 */
		अगर (!mthca_is_memमुक्त(dev))
			cq->cons_index &= cq->ibcq.cqe;

		अगर (cqe_sw(get_cqe_from_buf(&cq->resize_buf->buf,
					    cq->cons_index & cq->resize_buf->cqe))) अणु
			काष्ठा mthca_cq_buf tbuf;
			पूर्णांक tcqe;

			tbuf         = cq->buf;
			tcqe         = cq->ibcq.cqe;
			cq->buf      = cq->resize_buf->buf;
			cq->ibcq.cqe = cq->resize_buf->cqe;

			cq->resize_buf->buf   = tbuf;
			cq->resize_buf->cqe   = tcqe;
			cq->resize_buf->state = CQ_RESIZE_SWAPPED;

			जाओ repoll;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&cq->lock, flags);

	वापस err == 0 || err == -EAGAIN ? npolled : err;
पूर्ण

पूर्णांक mthca_tavor_arm_cq(काष्ठा ib_cq *cq, क्रमागत ib_cq_notअगरy_flags flags)
अणु
	u32 dbhi = ((flags & IB_CQ_SOLICITED_MASK) == IB_CQ_SOLICITED ?
		    MTHCA_TAVOR_CQ_DB_REQ_NOT_SOL :
		    MTHCA_TAVOR_CQ_DB_REQ_NOT) |
		to_mcq(cq)->cqn;

	mthca_ग_लिखो64(dbhi, 0xffffffff, to_mdev(cq->device)->kar + MTHCA_CQ_DOORBELL,
		      MTHCA_GET_DOORBELL_LOCK(&to_mdev(cq->device)->करोorbell_lock));

	वापस 0;
पूर्ण

पूर्णांक mthca_arbel_arm_cq(काष्ठा ib_cq *ibcq, क्रमागत ib_cq_notअगरy_flags flags)
अणु
	काष्ठा mthca_cq *cq = to_mcq(ibcq);
	__be32 db_rec[2];
	u32 dbhi;
	u32 sn = cq->arm_sn & 3;

	db_rec[0] = cpu_to_be32(cq->cons_index);
	db_rec[1] = cpu_to_be32((cq->cqn << 8) | (2 << 5) | (sn << 3) |
				((flags & IB_CQ_SOLICITED_MASK) ==
				 IB_CQ_SOLICITED ? 1 : 2));

	mthca_ग_लिखो_db_rec(db_rec, cq->arm_db);

	/*
	 * Make sure that the करोorbell record in host memory is
	 * written beक्रमe ringing the करोorbell via PCI MMIO.
	 */
	wmb();

	dbhi = (sn << 28) |
		((flags & IB_CQ_SOLICITED_MASK) == IB_CQ_SOLICITED ?
		 MTHCA_ARBEL_CQ_DB_REQ_NOT_SOL :
		 MTHCA_ARBEL_CQ_DB_REQ_NOT) | cq->cqn;

	mthca_ग_लिखो64(dbhi, cq->cons_index,
		      to_mdev(ibcq->device)->kar + MTHCA_CQ_DOORBELL,
		      MTHCA_GET_DOORBELL_LOCK(&to_mdev(ibcq->device)->करोorbell_lock));

	वापस 0;
पूर्ण

पूर्णांक mthca_init_cq(काष्ठा mthca_dev *dev, पूर्णांक nent,
		  काष्ठा mthca_ucontext *ctx, u32 pdn,
		  काष्ठा mthca_cq *cq)
अणु
	काष्ठा mthca_mailbox *mailbox;
	काष्ठा mthca_cq_context *cq_context;
	पूर्णांक err = -ENOMEM;

	cq->ibcq.cqe  = nent - 1;
	cq->is_kernel = !ctx;

	cq->cqn = mthca_alloc(&dev->cq_table.alloc);
	अगर (cq->cqn == -1)
		वापस -ENOMEM;

	अगर (mthca_is_memमुक्त(dev)) अणु
		err = mthca_table_get(dev, dev->cq_table.table, cq->cqn);
		अगर (err)
			जाओ err_out;

		अगर (cq->is_kernel) अणु
			cq->arm_sn = 1;

			err = -ENOMEM;

			cq->set_ci_db_index = mthca_alloc_db(dev, MTHCA_DB_TYPE_CQ_SET_CI,
							     cq->cqn, &cq->set_ci_db);
			अगर (cq->set_ci_db_index < 0)
				जाओ err_out_icm;

			cq->arm_db_index = mthca_alloc_db(dev, MTHCA_DB_TYPE_CQ_ARM,
							  cq->cqn, &cq->arm_db);
			अगर (cq->arm_db_index < 0)
				जाओ err_out_ci;
		पूर्ण
	पूर्ण

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox)) अणु
		err = PTR_ERR(mailbox);
		जाओ err_out_arm;
	पूर्ण

	cq_context = mailbox->buf;

	अगर (cq->is_kernel) अणु
		err = mthca_alloc_cq_buf(dev, &cq->buf, nent);
		अगर (err)
			जाओ err_out_mailbox;
	पूर्ण

	spin_lock_init(&cq->lock);
	cq->refcount = 1;
	init_रुकोqueue_head(&cq->रुको);
	mutex_init(&cq->mutex);

	स_रखो(cq_context, 0, माप *cq_context);
	cq_context->flags           = cpu_to_be32(MTHCA_CQ_STATUS_OK      |
						  MTHCA_CQ_STATE_DISARMED |
						  MTHCA_CQ_FLAG_TR);
	cq_context->logsize_usrpage = cpu_to_be32((ffs(nent) - 1) << 24);
	अगर (ctx)
		cq_context->logsize_usrpage |= cpu_to_be32(ctx->uar.index);
	अन्यथा
		cq_context->logsize_usrpage |= cpu_to_be32(dev->driver_uar.index);
	cq_context->error_eqn       = cpu_to_be32(dev->eq_table.eq[MTHCA_EQ_ASYNC].eqn);
	cq_context->comp_eqn        = cpu_to_be32(dev->eq_table.eq[MTHCA_EQ_COMP].eqn);
	cq_context->pd              = cpu_to_be32(pdn);
	cq_context->lkey            = cpu_to_be32(cq->buf.mr.ibmr.lkey);
	cq_context->cqn             = cpu_to_be32(cq->cqn);

	अगर (mthca_is_memमुक्त(dev)) अणु
		cq_context->ci_db    = cpu_to_be32(cq->set_ci_db_index);
		cq_context->state_db = cpu_to_be32(cq->arm_db_index);
	पूर्ण

	err = mthca_SW2HW_CQ(dev, mailbox, cq->cqn);
	अगर (err) अणु
		mthca_warn(dev, "SW2HW_CQ failed (%d)\n", err);
		जाओ err_out_मुक्त_mr;
	पूर्ण

	spin_lock_irq(&dev->cq_table.lock);
	err = mthca_array_set(&dev->cq_table.cq,
			      cq->cqn & (dev->limits.num_cqs - 1), cq);
	अगर (err) अणु
		spin_unlock_irq(&dev->cq_table.lock);
		जाओ err_out_मुक्त_mr;
	पूर्ण
	spin_unlock_irq(&dev->cq_table.lock);

	cq->cons_index = 0;

	mthca_मुक्त_mailbox(dev, mailbox);

	वापस 0;

err_out_मुक्त_mr:
	अगर (cq->is_kernel)
		mthca_मुक्त_cq_buf(dev, &cq->buf, cq->ibcq.cqe);

err_out_mailbox:
	mthca_मुक्त_mailbox(dev, mailbox);

err_out_arm:
	अगर (cq->is_kernel && mthca_is_memमुक्त(dev))
		mthca_मुक्त_db(dev, MTHCA_DB_TYPE_CQ_ARM, cq->arm_db_index);

err_out_ci:
	अगर (cq->is_kernel && mthca_is_memमुक्त(dev))
		mthca_मुक्त_db(dev, MTHCA_DB_TYPE_CQ_SET_CI, cq->set_ci_db_index);

err_out_icm:
	mthca_table_put(dev, dev->cq_table.table, cq->cqn);

err_out:
	mthca_मुक्त(&dev->cq_table.alloc, cq->cqn);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक get_cq_refcount(काष्ठा mthca_dev *dev, काष्ठा mthca_cq *cq)
अणु
	पूर्णांक c;

	spin_lock_irq(&dev->cq_table.lock);
	c = cq->refcount;
	spin_unlock_irq(&dev->cq_table.lock);

	वापस c;
पूर्ण

व्योम mthca_मुक्त_cq(काष्ठा mthca_dev *dev,
		   काष्ठा mthca_cq *cq)
अणु
	काष्ठा mthca_mailbox *mailbox;
	पूर्णांक err;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox)) अणु
		mthca_warn(dev, "No memory for mailbox to free CQ.\n");
		वापस;
	पूर्ण

	err = mthca_HW2SW_CQ(dev, mailbox, cq->cqn);
	अगर (err)
		mthca_warn(dev, "HW2SW_CQ failed (%d)\n", err);

	अगर (0) अणु
		__be32 *ctx = mailbox->buf;
		पूर्णांक j;

		prपूर्णांकk(KERN_ERR "context for CQN %x (cons index %x, next sw %d)\n",
		       cq->cqn, cq->cons_index,
		       cq->is_kernel ? !!next_cqe_sw(cq) : 0);
		क्रम (j = 0; j < 16; ++j)
			prपूर्णांकk(KERN_ERR "[%2x] %08x\n", j * 4, be32_to_cpu(ctx[j]));
	पूर्ण

	spin_lock_irq(&dev->cq_table.lock);
	mthca_array_clear(&dev->cq_table.cq,
			  cq->cqn & (dev->limits.num_cqs - 1));
	--cq->refcount;
	spin_unlock_irq(&dev->cq_table.lock);

	अगर (dev->mthca_flags & MTHCA_FLAG_MSI_X)
		synchronize_irq(dev->eq_table.eq[MTHCA_EQ_COMP].msi_x_vector);
	अन्यथा
		synchronize_irq(dev->pdev->irq);

	रुको_event(cq->रुको, !get_cq_refcount(dev, cq));

	अगर (cq->is_kernel) अणु
		mthca_मुक्त_cq_buf(dev, &cq->buf, cq->ibcq.cqe);
		अगर (mthca_is_memमुक्त(dev)) अणु
			mthca_मुक्त_db(dev, MTHCA_DB_TYPE_CQ_ARM,    cq->arm_db_index);
			mthca_मुक्त_db(dev, MTHCA_DB_TYPE_CQ_SET_CI, cq->set_ci_db_index);
		पूर्ण
	पूर्ण

	mthca_table_put(dev, dev->cq_table.table, cq->cqn);
	mthca_मुक्त(&dev->cq_table.alloc, cq->cqn);
	mthca_मुक्त_mailbox(dev, mailbox);
पूर्ण

पूर्णांक mthca_init_cq_table(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक err;

	spin_lock_init(&dev->cq_table.lock);

	err = mthca_alloc_init(&dev->cq_table.alloc,
			       dev->limits.num_cqs,
			       (1 << 24) - 1,
			       dev->limits.reserved_cqs);
	अगर (err)
		वापस err;

	err = mthca_array_init(&dev->cq_table.cq,
			       dev->limits.num_cqs);
	अगर (err)
		mthca_alloc_cleanup(&dev->cq_table.alloc);

	वापस err;
पूर्ण

व्योम mthca_cleanup_cq_table(काष्ठा mthca_dev *dev)
अणु
	mthca_array_cleanup(&dev->cq_table.cq, dev->limits.num_cqs);
	mthca_alloc_cleanup(&dev->cq_table.alloc);
पूर्ण
