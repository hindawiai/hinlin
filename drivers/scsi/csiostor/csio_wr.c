<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2008-2012 Chelsio Communications, Inc. All rights reserved.
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

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/compiler.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/cache.h>

#समावेश "t4_values.h"
#समावेश "csio_hw.h"
#समावेश "csio_wr.h"
#समावेश "csio_mb.h"
#समावेश "csio_defs.h"

पूर्णांक csio_पूर्णांकr_coalesce_cnt;		/* value:SGE_INGRESS_RX_THRESHOLD[0] */
अटल पूर्णांक csio_sge_thresh_reg;		/* SGE_INGRESS_RX_THRESHOLD[0] */

पूर्णांक csio_पूर्णांकr_coalesce_समय = 10;	/* value:SGE_TIMER_VALUE_1 */
अटल पूर्णांक csio_sge_समयr_reg = 1;

#घोषणा CSIO_SET_FLBUF_SIZE(_hw, _reg, _val)				\
	csio_wr_reg32((_hw), (_val), SGE_FL_BUFFER_SIZE##_reg##_A)

अटल व्योम
csio_get_flbuf_size(काष्ठा csio_hw *hw, काष्ठा csio_sge *sge, uपूर्णांक32_t reg)
अणु
	sge->sge_fl_buf_size[reg] = csio_rd_reg32(hw, SGE_FL_BUFFER_SIZE0_A +
							reg * माप(uपूर्णांक32_t));
पूर्ण

/* Free list buffer size */
अटल अंतरभूत uपूर्णांक32_t
csio_wr_fl_bufsz(काष्ठा csio_sge *sge, काष्ठा csio_dma_buf *buf)
अणु
	वापस sge->sge_fl_buf_size[buf->paddr & 0xF];
पूर्ण

/* Size of the egress queue status page */
अटल अंतरभूत uपूर्णांक32_t
csio_wr_qstat_pgsz(काष्ठा csio_hw *hw)
अणु
	वापस (hw->wrm.sge.sge_control & EGRSTATUSPAGESIZE_F) ?  128 : 64;
पूर्ण

/* Ring मुक्तlist करोorbell */
अटल अंतरभूत व्योम
csio_wr_ring_fldb(काष्ठा csio_hw *hw, काष्ठा csio_q *flq)
अणु
	/*
	 * Ring the करोorbell only when we have atleast CSIO_QCREDIT_SZ
	 * number of bytes in the मुक्तlist queue. This translates to atleast
	 * 8 मुक्तlist buffer poपूर्णांकers (since each poपूर्णांकer is 8 bytes).
	 */
	अगर (flq->inc_idx >= 8) अणु
		csio_wr_reg32(hw, DBPRIO_F | QID_V(flq->un.fl.flid) |
				  PIDX_T5_V(flq->inc_idx / 8) | DBTYPE_F,
				  MYPF_REG(SGE_PF_KDOORBELL_A));
		flq->inc_idx &= 7;
	पूर्ण
पूर्ण

/* Write a 0 cidx increment value to enable SGE पूर्णांकerrupts क्रम this queue */
अटल व्योम
csio_wr_sge_पूर्णांकr_enable(काष्ठा csio_hw *hw, uपूर्णांक16_t iqid)
अणु
	csio_wr_reg32(hw, CIDXINC_V(0)		|
			  INGRESSQID_V(iqid)	|
			  TIMERREG_V(X_TIMERREG_RESTART_COUNTER),
			  MYPF_REG(SGE_PF_GTS_A));
पूर्ण

/*
 * csio_wr_fill_fl - Populate the FL buffers of a FL queue.
 * @hw: HW module.
 * @flq: Freelist queue.
 *
 * Fill up मुक्तlist buffer entries with buffers of size specअगरied
 * in the size रेजिस्टर.
 *
 */
अटल पूर्णांक
csio_wr_fill_fl(काष्ठा csio_hw *hw, काष्ठा csio_q *flq)
अणु
	काष्ठा csio_wrm *wrm = csio_hw_to_wrm(hw);
	काष्ठा csio_sge *sge = &wrm->sge;
	__be64 *d = (__be64 *)(flq->vstart);
	काष्ठा csio_dma_buf *buf = &flq->un.fl.bufs[0];
	uपूर्णांक64_t paddr;
	पूर्णांक sreg = flq->un.fl.sreg;
	पूर्णांक n = flq->credits;

	जबतक (n--) अणु
		buf->len = sge->sge_fl_buf_size[sreg];
		buf->vaddr = dma_alloc_coherent(&hw->pdev->dev, buf->len,
						&buf->paddr, GFP_KERNEL);
		अगर (!buf->vaddr) अणु
			csio_err(hw, "Could only fill %d buffers!\n", n + 1);
			वापस -ENOMEM;
		पूर्ण

		paddr = buf->paddr | (sreg & 0xF);

		*d++ = cpu_to_be64(paddr);
		buf++;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csio_wr_update_fl -
 * @hw: HW module.
 * @flq: Freelist queue.
 *
 *
 */
अटल अंतरभूत व्योम
csio_wr_update_fl(काष्ठा csio_hw *hw, काष्ठा csio_q *flq, uपूर्णांक16_t n)
अणु

	flq->inc_idx += n;
	flq->pidx += n;
	अगर (unlikely(flq->pidx >= flq->credits))
		flq->pidx -= (uपूर्णांक16_t)flq->credits;

	CSIO_INC_STATS(flq, n_flq_refill);
पूर्ण

/*
 * csio_wr_alloc_q - Allocate a WR queue and initialize it.
 * @hw: HW module
 * @qsize: Size of the queue in bytes
 * @wrsize: Since of WR in this queue, अगर fixed.
 * @type: Type of queue (Ingress/Egress/Freelist)
 * @owner: Module that owns this queue.
 * @nflb: Number of मुक्तlist buffers क्रम FL.
 * @sreg: What is the FL buffer size रेजिस्टर?
 * @iq_पूर्णांक_handler: Ingress queue handler in INTx mode.
 *
 * This function allocates and sets up a queue क्रम the caller
 * of size qsize, aligned at the required boundary. This is subject to
 * be मुक्त entries being available in the queue array. If one is found,
 * it is initialized with the allocated queue, marked as being used (owner),
 * and a handle वापसed to the caller in क्रमm of the queue's index
 * पूर्णांकo the q_arr array.
 * If user has indicated a मुक्तlist (by specअगरying nflb > 0), create
 * another queue (with its own index पूर्णांकo q_arr) क्रम the मुक्तlist. Allocate
 * memory क्रम DMA buffer metadata (vaddr, len etc). Save off the मुक्तlist
 * idx in the ingress queue's flq.idx. This is how a Freelist is associated
 * with its owning ingress queue.
 */
पूर्णांक
csio_wr_alloc_q(काष्ठा csio_hw *hw, uपूर्णांक32_t qsize, uपूर्णांक32_t wrsize,
		uपूर्णांक16_t type, व्योम *owner, uपूर्णांक32_t nflb, पूर्णांक sreg,
		iq_handler_t iq_पूर्णांकx_handler)
अणु
	काष्ठा csio_wrm *wrm = csio_hw_to_wrm(hw);
	काष्ठा csio_q	*q, *flq;
	पूर्णांक		मुक्त_idx = wrm->मुक्त_qidx;
	पूर्णांक		ret_idx = मुक्त_idx;
	uपूर्णांक32_t	qsz;
	पूर्णांक flq_idx;

	अगर (मुक्त_idx >= wrm->num_q) अणु
		csio_err(hw, "No more free queues.\n");
		वापस -1;
	पूर्ण

	चयन (type) अणु
	हाल CSIO_EGRESS:
		qsz = ALIGN(qsize, CSIO_QCREDIT_SZ) + csio_wr_qstat_pgsz(hw);
		अवरोध;
	हाल CSIO_INGRESS:
		चयन (wrsize) अणु
		हाल 16:
		हाल 32:
		हाल 64:
		हाल 128:
			अवरोध;
		शेष:
			csio_err(hw, "Invalid Ingress queue WR size:%d\n",
				    wrsize);
			वापस -1;
		पूर्ण

		/*
		 * Number of elements must be a multiple of 16
		 * So this includes status page size
		 */
		qsz = ALIGN(qsize/wrsize, 16) * wrsize;

		अवरोध;
	हाल CSIO_FREELIST:
		qsz = ALIGN(qsize/wrsize, 8) * wrsize + csio_wr_qstat_pgsz(hw);
		अवरोध;
	शेष:
		csio_err(hw, "Invalid queue type: 0x%x\n", type);
		वापस -1;
	पूर्ण

	q = wrm->q_arr[मुक्त_idx];

	q->vstart = dma_alloc_coherent(&hw->pdev->dev, qsz, &q->pstart,
				       GFP_KERNEL);
	अगर (!q->vstart) अणु
		csio_err(hw,
			 "Failed to allocate DMA memory for "
			 "queue at id: %d size: %d\n", मुक्त_idx, qsize);
		वापस -1;
	पूर्ण

	q->type		= type;
	q->owner	= owner;
	q->pidx		= q->cidx = q->inc_idx = 0;
	q->size		= qsz;
	q->wr_sz	= wrsize;	/* If using fixed size WRs */

	wrm->मुक्त_qidx++;

	अगर (type == CSIO_INGRESS) अणु
		/* Since queue area is set to zero */
		q->un.iq.genbit	= 1;

		/*
		 * Ingress queue status page size is always the size of
		 * the ingress queue entry.
		 */
		q->credits	= (qsz - q->wr_sz) / q->wr_sz;
		q->vwrap	= (व्योम *)((uपूर्णांकptr_t)(q->vstart) + qsz
							- q->wr_sz);

		/* Allocate memory क्रम FL अगर requested */
		अगर (nflb > 0) अणु
			flq_idx = csio_wr_alloc_q(hw, nflb * माप(__be64),
						  माप(__be64), CSIO_FREELIST,
						  owner, 0, sreg, शून्य);
			अगर (flq_idx == -1) अणु
				csio_err(hw,
					 "Failed to allocate FL queue"
					 " for IQ idx:%d\n", मुक्त_idx);
				वापस -1;
			पूर्ण

			/* Associate the new FL with the Ingress quue */
			q->un.iq.flq_idx = flq_idx;

			flq = wrm->q_arr[q->un.iq.flq_idx];
			flq->un.fl.bufs = kसुस्मृति(flq->credits,
						  माप(काष्ठा csio_dma_buf),
						  GFP_KERNEL);
			अगर (!flq->un.fl.bufs) अणु
				csio_err(hw,
					 "Failed to allocate FL queue bufs"
					 " for IQ idx:%d\n", मुक्त_idx);
				वापस -1;
			पूर्ण

			flq->un.fl.packen = 0;
			flq->un.fl.offset = 0;
			flq->un.fl.sreg = sreg;

			/* Fill up the मुक्त list buffers */
			अगर (csio_wr_fill_fl(hw, flq))
				वापस -1;

			/*
			 * Make sure in a FLQ, atleast 1 credit (8 FL buffers)
			 * reमुख्यs unpopulated,otherwise HW thinks
			 * FLQ is empty.
			 */
			flq->pidx = flq->inc_idx = flq->credits - 8;
		पूर्ण अन्यथा अणु
			q->un.iq.flq_idx = -1;
		पूर्ण

		/* Associate the IQ INTx handler. */
		q->un.iq.iq_पूर्णांकx_handler = iq_पूर्णांकx_handler;

		csio_q_iqid(hw, ret_idx) = CSIO_MAX_QID;

	पूर्ण अन्यथा अगर (type == CSIO_EGRESS) अणु
		q->credits = (qsz - csio_wr_qstat_pgsz(hw)) / CSIO_QCREDIT_SZ;
		q->vwrap   = (व्योम *)((uपूर्णांकptr_t)(q->vstart) + qsz
						- csio_wr_qstat_pgsz(hw));
		csio_q_eqid(hw, ret_idx) = CSIO_MAX_QID;
	पूर्ण अन्यथा अणु /* Freelist */
		q->credits = (qsz - csio_wr_qstat_pgsz(hw)) / माप(__be64);
		q->vwrap   = (व्योम *)((uपूर्णांकptr_t)(q->vstart) + qsz
						- csio_wr_qstat_pgsz(hw));
		csio_q_flid(hw, ret_idx) = CSIO_MAX_QID;
	पूर्ण

	वापस ret_idx;
पूर्ण

/*
 * csio_wr_iq_create_rsp - Response handler क्रम IQ creation.
 * @hw: The HW module.
 * @mbp: Mailbox.
 * @iq_idx: Ingress queue that got created.
 *
 * Handle FW_IQ_CMD mailbox completion. Save off the asचिन्हित IQ/FL ids.
 */
अटल पूर्णांक
csio_wr_iq_create_rsp(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, पूर्णांक iq_idx)
अणु
	काष्ठा csio_iq_params iqp;
	क्रमागत fw_retval retval;
	uपूर्णांक32_t iq_id;
	पूर्णांक flq_idx;

	स_रखो(&iqp, 0, माप(काष्ठा csio_iq_params));

	csio_mb_iq_alloc_ग_लिखो_rsp(hw, mbp, &retval, &iqp);

	अगर (retval != FW_SUCCESS) अणु
		csio_err(hw, "IQ cmd returned 0x%x!\n", retval);
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	csio_q_iqid(hw, iq_idx)		= iqp.iqid;
	csio_q_physiqid(hw, iq_idx)	= iqp.physiqid;
	csio_q_pidx(hw, iq_idx)		= csio_q_cidx(hw, iq_idx) = 0;
	csio_q_inc_idx(hw, iq_idx)	= 0;

	/* Actual iq-id. */
	iq_id = iqp.iqid - hw->wrm.fw_iq_start;

	/* Set the iq-id to iq map table. */
	अगर (iq_id >= CSIO_MAX_IQ) अणु
		csio_err(hw,
			 "Exceeding MAX_IQ(%d) supported!"
			 " iqid:%d rel_iqid:%d FW iq_start:%d\n",
			 CSIO_MAX_IQ, iq_id, iqp.iqid, hw->wrm.fw_iq_start);
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण
	csio_q_set_पूर्णांकr_map(hw, iq_idx, iq_id);

	/*
	 * During FW_IQ_CMD, FW sets पूर्णांकerrupt_sent bit to 1 in the SGE
	 * ingress context of this queue. This will block पूर्णांकerrupts to
	 * this queue until the next GTS ग_लिखो. Thereक्रमe, we करो a
	 * 0-cidx increment GTS ग_लिखो क्रम this queue just to clear the
	 * पूर्णांकerrupt_sent bit. This will re-enable पूर्णांकerrupts to this
	 * queue.
	 */
	csio_wr_sge_पूर्णांकr_enable(hw, iqp.physiqid);

	flq_idx = csio_q_iq_flq_idx(hw, iq_idx);
	अगर (flq_idx != -1) अणु
		काष्ठा csio_q *flq = hw->wrm.q_arr[flq_idx];

		csio_q_flid(hw, flq_idx) = iqp.fl0id;
		csio_q_cidx(hw, flq_idx) = 0;
		csio_q_pidx(hw, flq_idx)    = csio_q_credits(hw, flq_idx) - 8;
		csio_q_inc_idx(hw, flq_idx) = csio_q_credits(hw, flq_idx) - 8;

		/* Now update SGE about the buffers allocated during init */
		csio_wr_ring_fldb(hw, flq);
	पूर्ण

	mempool_मुक्त(mbp, hw->mb_mempool);

	वापस 0;
पूर्ण

/*
 * csio_wr_iq_create - Configure an Ingress queue with FW.
 * @hw: The HW module.
 * @priv: Private data object.
 * @iq_idx: Ingress queue index in the WR module.
 * @vec: MSIX vector.
 * @portid: PCIE Channel to be associated with this queue.
 * @async: Is this a FW asynchronous message handling queue?
 * @cbfn: Completion callback.
 *
 * This API configures an ingress queue with FW by issuing a FW_IQ_CMD mailbox
 * with alloc/ग_लिखो bits set.
 */
पूर्णांक
csio_wr_iq_create(काष्ठा csio_hw *hw, व्योम *priv, पूर्णांक iq_idx,
		  uपूर्णांक32_t vec, uपूर्णांक8_t portid, bool async,
		  व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा csio_mb  *mbp;
	काष्ठा csio_iq_params iqp;
	पूर्णांक flq_idx;

	स_रखो(&iqp, 0, माप(काष्ठा csio_iq_params));
	csio_q_portid(hw, iq_idx) = portid;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		csio_err(hw, "IQ command out of memory!\n");
		वापस -ENOMEM;
	पूर्ण

	चयन (hw->पूर्णांकr_mode) अणु
	हाल CSIO_IM_INTX:
	हाल CSIO_IM_MSI:
		/* For पूर्णांकerrupt क्रमwarding queue only */
		अगर (hw->पूर्णांकr_iq_idx == iq_idx)
			iqp.iqandst	= X_INTERRUPTDESTINATION_PCIE;
		अन्यथा
			iqp.iqandst	= X_INTERRUPTDESTINATION_IQ;
		iqp.iqandstindex	=
			csio_q_physiqid(hw, hw->पूर्णांकr_iq_idx);
		अवरोध;
	हाल CSIO_IM_MSIX:
		iqp.iqandst		= X_INTERRUPTDESTINATION_PCIE;
		iqp.iqandstindex	= (uपूर्णांक16_t)vec;
		अवरोध;
	हाल CSIO_IM_NONE:
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	/* Pass in the ingress queue cmd parameters */
	iqp.pfn			= hw->pfn;
	iqp.vfn			= 0;
	iqp.iq_start		= 1;
	iqp.viid		= 0;
	iqp.type		= FW_IQ_TYPE_FL_INT_CAP;
	iqp.iqasynch		= async;
	अगर (csio_पूर्णांकr_coalesce_cnt)
		iqp.iqanus	= X_UPDATESCHEDULING_COUNTER_OPTTIMER;
	अन्यथा
		iqp.iqanus	= X_UPDATESCHEDULING_TIMER;
	iqp.iqanud		= X_UPDATEDELIVERY_INTERRUPT;
	iqp.iqpciech		= portid;
	iqp.iqपूर्णांकcntthresh	= (uपूर्णांक8_t)csio_sge_thresh_reg;

	चयन (csio_q_wr_sz(hw, iq_idx)) अणु
	हाल 16:
		iqp.iqesize = 0; अवरोध;
	हाल 32:
		iqp.iqesize = 1; अवरोध;
	हाल 64:
		iqp.iqesize = 2; अवरोध;
	हाल 128:
		iqp.iqesize = 3; अवरोध;
	पूर्ण

	iqp.iqsize		= csio_q_size(hw, iq_idx) /
						csio_q_wr_sz(hw, iq_idx);
	iqp.iqaddr		= csio_q_pstart(hw, iq_idx);

	flq_idx = csio_q_iq_flq_idx(hw, iq_idx);
	अगर (flq_idx != -1) अणु
		क्रमागत chip_type chip = CHELSIO_CHIP_VERSION(hw->chip_id);
		काष्ठा csio_q *flq = hw->wrm.q_arr[flq_idx];

		iqp.fl0paden	= 1;
		iqp.fl0packen	= flq->un.fl.packen ? 1 : 0;
		iqp.fl0fbmin	= X_FETCHBURSTMIN_64B;
		iqp.fl0fbmax	= ((chip == CHELSIO_T5) ?
				  X_FETCHBURSTMAX_512B : X_FETCHBURSTMAX_256B);
		iqp.fl0size	= csio_q_size(hw, flq_idx) / CSIO_QCREDIT_SZ;
		iqp.fl0addr	= csio_q_pstart(hw, flq_idx);
	पूर्ण

	csio_mb_iq_alloc_ग_लिखो(hw, mbp, priv, CSIO_MB_DEFAULT_TMO, &iqp, cbfn);

	अगर (csio_mb_issue(hw, mbp)) अणु
		csio_err(hw, "Issue of IQ cmd failed!\n");
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	अगर (cbfn != शून्य)
		वापस 0;

	वापस csio_wr_iq_create_rsp(hw, mbp, iq_idx);
पूर्ण

/*
 * csio_wr_eq_create_rsp - Response handler क्रम EQ creation.
 * @hw: The HW module.
 * @mbp: Mailbox.
 * @eq_idx: Egress queue that got created.
 *
 * Handle FW_EQ_OFLD_CMD mailbox completion. Save off the asचिन्हित EQ ids.
 */
अटल पूर्णांक
csio_wr_eq_cfg_rsp(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, पूर्णांक eq_idx)
अणु
	काष्ठा csio_eq_params eqp;
	क्रमागत fw_retval retval;

	स_रखो(&eqp, 0, माप(काष्ठा csio_eq_params));

	csio_mb_eq_ofld_alloc_ग_लिखो_rsp(hw, mbp, &retval, &eqp);

	अगर (retval != FW_SUCCESS) अणु
		csio_err(hw, "EQ OFLD cmd returned 0x%x!\n", retval);
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	csio_q_eqid(hw, eq_idx)	= (uपूर्णांक16_t)eqp.eqid;
	csio_q_physeqid(hw, eq_idx) = (uपूर्णांक16_t)eqp.physeqid;
	csio_q_pidx(hw, eq_idx)	= csio_q_cidx(hw, eq_idx) = 0;
	csio_q_inc_idx(hw, eq_idx) = 0;

	mempool_मुक्त(mbp, hw->mb_mempool);

	वापस 0;
पूर्ण

/*
 * csio_wr_eq_create - Configure an Egress queue with FW.
 * @hw: HW module.
 * @priv: Private data.
 * @eq_idx: Egress queue index in the WR module.
 * @iq_idx: Associated ingress queue index.
 * @cbfn: Completion callback.
 *
 * This API configures a offload egress queue with FW by issuing a
 * FW_EQ_OFLD_CMD  (with alloc + ग_लिखो ) mailbox.
 */
पूर्णांक
csio_wr_eq_create(काष्ठा csio_hw *hw, व्योम *priv, पूर्णांक eq_idx,
		  पूर्णांक iq_idx, uपूर्णांक8_t portid,
		  व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	काष्ठा csio_mb  *mbp;
	काष्ठा csio_eq_params eqp;

	स_रखो(&eqp, 0, माप(काष्ठा csio_eq_params));

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		csio_err(hw, "EQ command out of memory!\n");
		वापस -ENOMEM;
	पूर्ण

	eqp.pfn			= hw->pfn;
	eqp.vfn			= 0;
	eqp.eqstart		= 1;
	eqp.hostfcmode		= X_HOSTFCMODE_STATUS_PAGE;
	eqp.iqid		= csio_q_iqid(hw, iq_idx);
	eqp.fbmin		= X_FETCHBURSTMIN_64B;
	eqp.fbmax		= X_FETCHBURSTMAX_512B;
	eqp.cidxfthresh		= 0;
	eqp.pciechn		= portid;
	eqp.eqsize		= csio_q_size(hw, eq_idx) / CSIO_QCREDIT_SZ;
	eqp.eqaddr		= csio_q_pstart(hw, eq_idx);

	csio_mb_eq_ofld_alloc_ग_लिखो(hw, mbp, priv, CSIO_MB_DEFAULT_TMO,
				    &eqp, cbfn);

	अगर (csio_mb_issue(hw, mbp)) अणु
		csio_err(hw, "Issue of EQ OFLD cmd failed!\n");
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	अगर (cbfn != शून्य)
		वापस 0;

	वापस csio_wr_eq_cfg_rsp(hw, mbp, eq_idx);
पूर्ण

/*
 * csio_wr_iq_destroy_rsp - Response handler क्रम IQ removal.
 * @hw: The HW module.
 * @mbp: Mailbox.
 * @iq_idx: Ingress queue that was मुक्तd.
 *
 * Handle FW_IQ_CMD (मुक्त) mailbox completion.
 */
अटल पूर्णांक
csio_wr_iq_destroy_rsp(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, पूर्णांक iq_idx)
अणु
	क्रमागत fw_retval retval = csio_mb_fw_retval(mbp);
	पूर्णांक rv = 0;

	अगर (retval != FW_SUCCESS)
		rv = -EINVAL;

	mempool_मुक्त(mbp, hw->mb_mempool);

	वापस rv;
पूर्ण

/*
 * csio_wr_iq_destroy - Free an ingress queue.
 * @hw: The HW module.
 * @priv: Private data object.
 * @iq_idx: Ingress queue index to destroy
 * @cbfn: Completion callback.
 *
 * This API मुक्तs an ingress queue by issuing the FW_IQ_CMD
 * with the मुक्त bit set.
 */
अटल पूर्णांक
csio_wr_iq_destroy(काष्ठा csio_hw *hw, व्योम *priv, पूर्णांक iq_idx,
		   व्योम (*cbfn)(काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	पूर्णांक rv = 0;
	काष्ठा csio_mb  *mbp;
	काष्ठा csio_iq_params iqp;
	पूर्णांक flq_idx;

	स_रखो(&iqp, 0, माप(काष्ठा csio_iq_params));

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp)
		वापस -ENOMEM;

	iqp.pfn		= hw->pfn;
	iqp.vfn		= 0;
	iqp.iqid	= csio_q_iqid(hw, iq_idx);
	iqp.type	= FW_IQ_TYPE_FL_INT_CAP;

	flq_idx = csio_q_iq_flq_idx(hw, iq_idx);
	अगर (flq_idx != -1)
		iqp.fl0id = csio_q_flid(hw, flq_idx);
	अन्यथा
		iqp.fl0id = 0xFFFF;

	iqp.fl1id = 0xFFFF;

	csio_mb_iq_मुक्त(hw, mbp, priv, CSIO_MB_DEFAULT_TMO, &iqp, cbfn);

	rv = csio_mb_issue(hw, mbp);
	अगर (rv != 0) अणु
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस rv;
	पूर्ण

	अगर (cbfn != शून्य)
		वापस 0;

	वापस csio_wr_iq_destroy_rsp(hw, mbp, iq_idx);
पूर्ण

/*
 * csio_wr_eq_destroy_rsp - Response handler क्रम OFLD EQ creation.
 * @hw: The HW module.
 * @mbp: Mailbox.
 * @eq_idx: Egress queue that was मुक्तd.
 *
 * Handle FW_OFLD_EQ_CMD (मुक्त) mailbox completion.
 */
अटल पूर्णांक
csio_wr_eq_destroy_rsp(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, पूर्णांक eq_idx)
अणु
	क्रमागत fw_retval retval = csio_mb_fw_retval(mbp);
	पूर्णांक rv = 0;

	अगर (retval != FW_SUCCESS)
		rv = -EINVAL;

	mempool_मुक्त(mbp, hw->mb_mempool);

	वापस rv;
पूर्ण

/*
 * csio_wr_eq_destroy - Free an Egress queue.
 * @hw: The HW module.
 * @priv: Private data object.
 * @eq_idx: Egress queue index to destroy
 * @cbfn: Completion callback.
 *
 * This API मुक्तs an Egress queue by issuing the FW_EQ_OFLD_CMD
 * with the मुक्त bit set.
 */
अटल पूर्णांक
csio_wr_eq_destroy(काष्ठा csio_hw *hw, व्योम *priv, पूर्णांक eq_idx,
		   व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *))
अणु
	पूर्णांक rv = 0;
	काष्ठा csio_mb  *mbp;
	काष्ठा csio_eq_params eqp;

	स_रखो(&eqp, 0, माप(काष्ठा csio_eq_params));

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp)
		वापस -ENOMEM;

	eqp.pfn		= hw->pfn;
	eqp.vfn		= 0;
	eqp.eqid	= csio_q_eqid(hw, eq_idx);

	csio_mb_eq_ofld_मुक्त(hw, mbp, priv, CSIO_MB_DEFAULT_TMO, &eqp, cbfn);

	rv = csio_mb_issue(hw, mbp);
	अगर (rv != 0) अणु
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस rv;
	पूर्ण

	अगर (cbfn != शून्य)
		वापस 0;

	वापस csio_wr_eq_destroy_rsp(hw, mbp, eq_idx);
पूर्ण

/*
 * csio_wr_cleanup_eq_stpg - Cleanup Egress queue status page
 * @hw: HW module
 * @qidx: Egress queue index
 *
 * Cleanup the Egress queue status page.
 */
अटल व्योम
csio_wr_cleanup_eq_stpg(काष्ठा csio_hw *hw, पूर्णांक qidx)
अणु
	काष्ठा csio_q	*q = csio_hw_to_wrm(hw)->q_arr[qidx];
	काष्ठा csio_qstatus_page *stp = (काष्ठा csio_qstatus_page *)q->vwrap;

	स_रखो(stp, 0, माप(*stp));
पूर्ण

/*
 * csio_wr_cleanup_iq_ftr - Cleanup Footer entries in IQ
 * @hw: HW module
 * @qidx: Ingress queue index
 *
 * Cleanup the footer entries in the given ingress queue,
 * set to 1 the पूर्णांकernal copy of genbit.
 */
अटल व्योम
csio_wr_cleanup_iq_ftr(काष्ठा csio_hw *hw, पूर्णांक qidx)
अणु
	काष्ठा csio_wrm *wrm	= csio_hw_to_wrm(hw);
	काष्ठा csio_q	*q	= wrm->q_arr[qidx];
	व्योम *wr;
	काष्ठा csio_iqwr_footer *ftr;
	uपूर्णांक32_t i = 0;

	/* set to 1 since we are just about zero out genbit */
	q->un.iq.genbit = 1;

	क्रम (i = 0; i < q->credits; i++) अणु
		/* Get the WR */
		wr = (व्योम *)((uपूर्णांकptr_t)q->vstart +
					   (i * q->wr_sz));
		/* Get the footer */
		ftr = (काष्ठा csio_iqwr_footer *)((uपूर्णांकptr_t)wr +
					  (q->wr_sz - माप(*ftr)));
		/* Zero out footer */
		स_रखो(ftr, 0, माप(*ftr));
	पूर्ण
पूर्ण

पूर्णांक
csio_wr_destroy_queues(काष्ठा csio_hw *hw, bool cmd)
अणु
	पूर्णांक i, flq_idx;
	काष्ठा csio_q *q;
	काष्ठा csio_wrm *wrm = csio_hw_to_wrm(hw);
	पूर्णांक rv;

	क्रम (i = 0; i < wrm->मुक्त_qidx; i++) अणु
		q = wrm->q_arr[i];

		चयन (q->type) अणु
		हाल CSIO_EGRESS:
			अगर (csio_q_eqid(hw, i) != CSIO_MAX_QID) अणु
				csio_wr_cleanup_eq_stpg(hw, i);
				अगर (!cmd) अणु
					csio_q_eqid(hw, i) = CSIO_MAX_QID;
					जारी;
				पूर्ण

				rv = csio_wr_eq_destroy(hw, शून्य, i, शून्य);
				अगर ((rv == -EBUSY) || (rv == -ETIMEDOUT))
					cmd = false;

				csio_q_eqid(hw, i) = CSIO_MAX_QID;
			पूर्ण
			fallthrough;
		हाल CSIO_INGRESS:
			अगर (csio_q_iqid(hw, i) != CSIO_MAX_QID) अणु
				csio_wr_cleanup_iq_ftr(hw, i);
				अगर (!cmd) अणु
					csio_q_iqid(hw, i) = CSIO_MAX_QID;
					flq_idx = csio_q_iq_flq_idx(hw, i);
					अगर (flq_idx != -1)
						csio_q_flid(hw, flq_idx) =
								CSIO_MAX_QID;
					जारी;
				पूर्ण

				rv = csio_wr_iq_destroy(hw, शून्य, i, शून्य);
				अगर ((rv == -EBUSY) || (rv == -ETIMEDOUT))
					cmd = false;

				csio_q_iqid(hw, i) = CSIO_MAX_QID;
				flq_idx = csio_q_iq_flq_idx(hw, i);
				अगर (flq_idx != -1)
					csio_q_flid(hw, flq_idx) = CSIO_MAX_QID;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	hw->flags &= ~CSIO_HWF_Q_FW_ALLOCED;

	वापस 0;
पूर्ण

/*
 * csio_wr_get - Get requested size of WR entry/entries from queue.
 * @hw: HW module.
 * @qidx: Index of queue.
 * @size: Cumulative size of Work request(s).
 * @wrp: Work request pair.
 *
 * If requested credits are available, वापस the start address of the
 * work request in the work request pair. Set pidx accordingly and
 * वापस.
 *
 * NOTE about WR pair:
 * ==================
 * A WR can start towards the end of a queue, and then जारी at the
 * beginning, since the queue is considered to be circular. This will
 * require a pair of address/size to be passed back to the caller -
 * hence Work request pair क्रमmat.
 */
पूर्णांक
csio_wr_get(काष्ठा csio_hw *hw, पूर्णांक qidx, uपूर्णांक32_t size,
	    काष्ठा csio_wr_pair *wrp)
अणु
	काष्ठा csio_wrm *wrm = csio_hw_to_wrm(hw);
	काष्ठा csio_q *q = wrm->q_arr[qidx];
	व्योम *cwr = (व्योम *)((uपूर्णांकptr_t)(q->vstart) +
						(q->pidx * CSIO_QCREDIT_SZ));
	काष्ठा csio_qstatus_page *stp = (काष्ठा csio_qstatus_page *)q->vwrap;
	uपूर्णांक16_t cidx = q->cidx = ntohs(stp->cidx);
	uपूर्णांक16_t pidx = q->pidx;
	uपूर्णांक32_t req_sz	= ALIGN(size, CSIO_QCREDIT_SZ);
	पूर्णांक req_credits	= req_sz / CSIO_QCREDIT_SZ;
	पूर्णांक credits;

	CSIO_DB_ASSERT(q->owner != शून्य);
	CSIO_DB_ASSERT((qidx >= 0) && (qidx < wrm->मुक्त_qidx));
	CSIO_DB_ASSERT(cidx <= q->credits);

	/* Calculate credits */
	अगर (pidx > cidx) अणु
		credits = q->credits - (pidx - cidx) - 1;
	पूर्ण अन्यथा अगर (cidx > pidx) अणु
		credits = cidx - pidx - 1;
	पूर्ण अन्यथा अणु
		/* cidx == pidx, empty queue */
		credits = q->credits;
		CSIO_INC_STATS(q, n_qempty);
	पूर्ण

	/*
	 * Check अगर we have enough credits.
	 * credits = 1 implies queue is full.
	 */
	अगर (!credits || (req_credits > credits)) अणु
		CSIO_INC_STATS(q, n_qfull);
		वापस -EBUSY;
	पूर्ण

	/*
	 * If we are here, we have enough credits to satisfy the
	 * request. Check अगर we are near the end of q, and अगर WR spills over.
	 * If it करोes, use the first addr/size to cover the queue until
	 * the end. Fit the reमुख्यder portion of the request at the top
	 * of queue and वापस it in the second addr/len. Set pidx
	 * accordingly.
	 */
	अगर (unlikely(((uपूर्णांकptr_t)cwr + req_sz) > (uपूर्णांकptr_t)(q->vwrap))) अणु
		wrp->addr1 = cwr;
		wrp->size1 = (uपूर्णांक32_t)((uपूर्णांकptr_t)q->vwrap - (uपूर्णांकptr_t)cwr);
		wrp->addr2 = q->vstart;
		wrp->size2 = req_sz - wrp->size1;
		q->pidx	= (uपूर्णांक16_t)(ALIGN(wrp->size2, CSIO_QCREDIT_SZ) /
							CSIO_QCREDIT_SZ);
		CSIO_INC_STATS(q, n_qwrap);
		CSIO_INC_STATS(q, n_eq_wr_split);
	पूर्ण अन्यथा अणु
		wrp->addr1 = cwr;
		wrp->size1 = req_sz;
		wrp->addr2 = शून्य;
		wrp->size2 = 0;
		q->pidx	+= (uपूर्णांक16_t)req_credits;

		/* We are the end of queue, roll back pidx to top of queue */
		अगर (unlikely(q->pidx == q->credits)) अणु
			q->pidx = 0;
			CSIO_INC_STATS(q, n_qwrap);
		पूर्ण
	पूर्ण

	q->inc_idx = (uपूर्णांक16_t)req_credits;

	CSIO_INC_STATS(q, n_tot_reqs);

	वापस 0;
पूर्ण

/*
 * csio_wr_copy_to_wrp - Copies given data पूर्णांकo WR.
 * @data_buf - Data buffer
 * @wrp - Work request pair.
 * @wr_off - Work request offset.
 * @data_len - Data length.
 *
 * Copies the given data in Work Request. Work request pair(wrp) specअगरies
 * address inक्रमmation of Work request.
 * Returns: none
 */
व्योम
csio_wr_copy_to_wrp(व्योम *data_buf, काष्ठा csio_wr_pair *wrp,
		   uपूर्णांक32_t wr_off, uपूर्णांक32_t data_len)
अणु
	uपूर्णांक32_t nbytes;

	/* Number of space available in buffer addr1 of WRP */
	nbytes = ((wrp->size1 - wr_off) >= data_len) ?
					data_len : (wrp->size1 - wr_off);

	स_नकल((uपूर्णांक8_t *) wrp->addr1 + wr_off, data_buf, nbytes);
	data_len -= nbytes;

	/* Write the reमुख्यing data from the begining of circular buffer */
	अगर (data_len) अणु
		CSIO_DB_ASSERT(data_len <= wrp->size2);
		CSIO_DB_ASSERT(wrp->addr2 != शून्य);
		स_नकल(wrp->addr2, (uपूर्णांक8_t *) data_buf + nbytes, data_len);
	पूर्ण
पूर्ण

/*
 * csio_wr_issue - Notअगरy chip of Work request.
 * @hw: HW module.
 * @qidx: Index of queue.
 * @prio: 0: Low priority, 1: High priority
 *
 * Rings the SGE Doorbell by writing the current producer index of the passed
 * in queue पूर्णांकo the रेजिस्टर.
 *
 */
पूर्णांक
csio_wr_issue(काष्ठा csio_hw *hw, पूर्णांक qidx, bool prio)
अणु
	काष्ठा csio_wrm *wrm = csio_hw_to_wrm(hw);
	काष्ठा csio_q *q = wrm->q_arr[qidx];

	CSIO_DB_ASSERT((qidx >= 0) && (qidx < wrm->मुक्त_qidx));

	wmb();
	/* Ring SGE Doorbell writing q->pidx पूर्णांकo it */
	csio_wr_reg32(hw, DBPRIO_V(prio) | QID_V(q->un.eq.physeqid) |
			  PIDX_T5_V(q->inc_idx) | DBTYPE_F,
			  MYPF_REG(SGE_PF_KDOORBELL_A));
	q->inc_idx = 0;

	वापस 0;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t
csio_wr_avail_qcredits(काष्ठा csio_q *q)
अणु
	अगर (q->pidx > q->cidx)
		वापस q->pidx - q->cidx;
	अन्यथा अगर (q->cidx > q->pidx)
		वापस q->credits - (q->cidx - q->pidx);
	अन्यथा
		वापस 0;	/* cidx == pidx, empty queue */
पूर्ण

/*
 * csio_wr_inval_flq_buf - Invalidate a मुक्त list buffer entry.
 * @hw: HW module.
 * @flq: The मुक्तlist queue.
 *
 * Invalidate the driver's version of a मुक्तlist buffer entry,
 * without मुक्तing the associated the DMA memory. The entry
 * to be invalidated is picked up from the current Free list
 * queue cidx.
 *
 */
अटल अंतरभूत व्योम
csio_wr_inval_flq_buf(काष्ठा csio_hw *hw, काष्ठा csio_q *flq)
अणु
	flq->cidx++;
	अगर (flq->cidx == flq->credits) अणु
		flq->cidx = 0;
		CSIO_INC_STATS(flq, n_qwrap);
	पूर्ण
पूर्ण

/*
 * csio_wr_process_fl - Process a मुक्तlist completion.
 * @hw: HW module.
 * @q: The ingress queue attached to the Freelist.
 * @wr: The मुक्तlist completion WR in the ingress queue.
 * @len_to_qid: The lower 32-bits of the first flit of the RSP footer
 * @iq_handler: Caller's handler क्रम this completion.
 * @priv: Private poपूर्णांकer of caller
 *
 */
अटल अंतरभूत व्योम
csio_wr_process_fl(काष्ठा csio_hw *hw, काष्ठा csio_q *q,
		   व्योम *wr, uपूर्णांक32_t len_to_qid,
		   व्योम (*iq_handler)(काष्ठा csio_hw *, व्योम *,
				      uपूर्णांक32_t, काष्ठा csio_fl_dma_buf *,
				      व्योम *),
		   व्योम *priv)
अणु
	काष्ठा csio_wrm *wrm = csio_hw_to_wrm(hw);
	काष्ठा csio_sge *sge = &wrm->sge;
	काष्ठा csio_fl_dma_buf flb;
	काष्ठा csio_dma_buf *buf, *fbuf;
	uपूर्णांक32_t bufsz, len, lastlen = 0;
	पूर्णांक n;
	काष्ठा csio_q *flq = hw->wrm.q_arr[q->un.iq.flq_idx];

	CSIO_DB_ASSERT(flq != शून्य);

	len = len_to_qid;

	अगर (len & IQWRF_NEWBUF) अणु
		अगर (flq->un.fl.offset > 0) अणु
			csio_wr_inval_flq_buf(hw, flq);
			flq->un.fl.offset = 0;
		पूर्ण
		len = IQWRF_LEN_GET(len);
	पूर्ण

	CSIO_DB_ASSERT(len != 0);

	flb.totlen = len;

	/* Consume all मुक्तlist buffers used क्रम len bytes */
	क्रम (n = 0, fbuf = flb.flbufs; ; n++, fbuf++) अणु
		buf = &flq->un.fl.bufs[flq->cidx];
		bufsz = csio_wr_fl_bufsz(sge, buf);

		fbuf->paddr	= buf->paddr;
		fbuf->vaddr	= buf->vaddr;

		flb.offset	= flq->un.fl.offset;
		lastlen		= min(bufsz, len);
		fbuf->len	= lastlen;

		len -= lastlen;
		अगर (!len)
			अवरोध;
		csio_wr_inval_flq_buf(hw, flq);
	पूर्ण

	flb.defer_मुक्त = flq->un.fl.packen ? 0 : 1;

	iq_handler(hw, wr, q->wr_sz - माप(काष्ठा csio_iqwr_footer),
		   &flb, priv);

	अगर (flq->un.fl.packen)
		flq->un.fl.offset += ALIGN(lastlen, sge->csio_fl_align);
	अन्यथा
		csio_wr_inval_flq_buf(hw, flq);

पूर्ण

/*
 * csio_is_new_iqwr - Is this a new Ingress queue entry ?
 * @q: Ingress quueue.
 * @ftr: Ingress queue WR SGE footer.
 *
 * The entry is new अगर our generation bit matches the corresponding
 * bit in the footer of the current WR.
 */
अटल अंतरभूत bool
csio_is_new_iqwr(काष्ठा csio_q *q, काष्ठा csio_iqwr_footer *ftr)
अणु
	वापस (q->un.iq.genbit == (ftr->u.type_gen >> IQWRF_GEN_SHIFT));
पूर्ण

/*
 * csio_wr_process_iq - Process elements in Ingress queue.
 * @hw:  HW poपूर्णांकer
 * @qidx: Index of queue
 * @iq_handler: Handler क्रम this queue
 * @priv: Caller's निजी poपूर्णांकer
 *
 * This routine walks through every entry of the ingress queue, calling
 * the provided iq_handler with the entry, until the generation bit
 * flips.
 */
पूर्णांक
csio_wr_process_iq(काष्ठा csio_hw *hw, काष्ठा csio_q *q,
		   व्योम (*iq_handler)(काष्ठा csio_hw *, व्योम *,
				      uपूर्णांक32_t, काष्ठा csio_fl_dma_buf *,
				      व्योम *),
		   व्योम *priv)
अणु
	काष्ठा csio_wrm *wrm = csio_hw_to_wrm(hw);
	व्योम *wr = (व्योम *)((uपूर्णांकptr_t)q->vstart + (q->cidx * q->wr_sz));
	काष्ठा csio_iqwr_footer *ftr;
	uपूर्णांक32_t wr_type, fw_qid, qid;
	काष्ठा csio_q *q_completed;
	काष्ठा csio_q *flq = csio_iq_has_fl(q) ?
					wrm->q_arr[q->un.iq.flq_idx] : शून्य;
	पूर्णांक rv = 0;

	/* Get the footer */
	ftr = (काष्ठा csio_iqwr_footer *)((uपूर्णांकptr_t)wr +
					  (q->wr_sz - माप(*ftr)));

	/*
	 * When q wrapped around last समय, driver should have inverted
	 * ic.genbit as well.
	 */
	जबतक (csio_is_new_iqwr(q, ftr)) अणु

		CSIO_DB_ASSERT(((uपूर्णांकptr_t)wr + q->wr_sz) <=
						(uपूर्णांकptr_t)q->vwrap);
		rmb();
		wr_type = IQWRF_TYPE_GET(ftr->u.type_gen);

		चयन (wr_type) अणु
		हाल X_RSPD_TYPE_CPL:
			/* Subtract footer from WR len */
			iq_handler(hw, wr, q->wr_sz - माप(*ftr), शून्य, priv);
			अवरोध;
		हाल X_RSPD_TYPE_FLBUF:
			csio_wr_process_fl(hw, q, wr,
					   ntohl(ftr->pldbuflen_qid),
					   iq_handler, priv);
			अवरोध;
		हाल X_RSPD_TYPE_INTR:
			fw_qid = ntohl(ftr->pldbuflen_qid);
			qid = fw_qid - wrm->fw_iq_start;
			q_completed = hw->wrm.पूर्णांकr_map[qid];

			अगर (unlikely(qid ==
					csio_q_physiqid(hw, hw->पूर्णांकr_iq_idx))) अणु
				/*
				 * We are alपढ़ोy in the Forward Interrupt
				 * Interrupt Queue Service! Do-not service
				 * again!
				 *
				 */
			पूर्ण अन्यथा अणु
				CSIO_DB_ASSERT(q_completed);
				CSIO_DB_ASSERT(
					q_completed->un.iq.iq_पूर्णांकx_handler);

				/* Call the queue handler. */
				q_completed->un.iq.iq_पूर्णांकx_handler(hw, शून्य,
						0, शून्य, (व्योम *)q_completed);
			पूर्ण
			अवरोध;
		शेष:
			csio_warn(hw, "Unknown resp type 0x%x received\n",
				 wr_type);
			CSIO_INC_STATS(q, n_rsp_unknown);
			अवरोध;
		पूर्ण

		/*
		 * Ingress *always* has fixed size WR entries. Thereक्रमe,
		 * there should always be complete WRs towards the end of
		 * queue.
		 */
		अगर (((uपूर्णांकptr_t)wr + q->wr_sz) == (uपूर्णांकptr_t)q->vwrap) अणु

			/* Roll over to start of queue */
			q->cidx = 0;
			wr	= q->vstart;

			/* Toggle genbit */
			q->un.iq.genbit ^= 0x1;

			CSIO_INC_STATS(q, n_qwrap);
		पूर्ण अन्यथा अणु
			q->cidx++;
			wr	= (व्योम *)((uपूर्णांकptr_t)(q->vstart) +
					   (q->cidx * q->wr_sz));
		पूर्ण

		ftr = (काष्ठा csio_iqwr_footer *)((uपूर्णांकptr_t)wr +
						  (q->wr_sz - माप(*ftr)));
		q->inc_idx++;

	पूर्ण /* जबतक (q->un.iq.genbit == hdr->genbit) */

	/*
	 * We need to re-arm SGE पूर्णांकerrupts in हाल we got a stray पूर्णांकerrupt,
	 * especially in msix mode. With INTx, this may be a common occurence.
	 */
	अगर (unlikely(!q->inc_idx)) अणु
		CSIO_INC_STATS(q, n_stray_comp);
		rv = -EINVAL;
		जाओ restart;
	पूर्ण

	/* Replenish मुक्त list buffers अगर pending falls below low water mark */
	अगर (flq) अणु
		uपूर्णांक32_t avail  = csio_wr_avail_qcredits(flq);
		अगर (avail <= 16) अणु
			/* Make sure in FLQ, atleast 1 credit (8 FL buffers)
			 * reमुख्यs unpopulated otherwise HW thinks
			 * FLQ is empty.
			 */
			csio_wr_update_fl(hw, flq, (flq->credits - 8) - avail);
			csio_wr_ring_fldb(hw, flq);
		पूर्ण
	पूर्ण

restart:
	/* Now inक्रमm SGE about our incremental index value */
	csio_wr_reg32(hw, CIDXINC_V(q->inc_idx)		|
			  INGRESSQID_V(q->un.iq.physiqid)	|
			  TIMERREG_V(csio_sge_समयr_reg),
			  MYPF_REG(SGE_PF_GTS_A));
	q->stats.n_tot_rsps += q->inc_idx;

	q->inc_idx = 0;

	वापस rv;
पूर्ण

पूर्णांक
csio_wr_process_iq_idx(काष्ठा csio_hw *hw, पूर्णांक qidx,
		   व्योम (*iq_handler)(काष्ठा csio_hw *, व्योम *,
				      uपूर्णांक32_t, काष्ठा csio_fl_dma_buf *,
				      व्योम *),
		   व्योम *priv)
अणु
	काष्ठा csio_wrm *wrm	= csio_hw_to_wrm(hw);
	काष्ठा csio_q	*iq	= wrm->q_arr[qidx];

	वापस csio_wr_process_iq(hw, iq, iq_handler, priv);
पूर्ण

अटल पूर्णांक
csio_बंदst_समयr(काष्ठा csio_sge *s, पूर्णांक समय)
अणु
	पूर्णांक i, delta, match = 0, min_delta = पूर्णांक_उच्च;

	क्रम (i = 0; i < ARRAY_SIZE(s->समयr_val); i++) अणु
		delta = समय - s->समयr_val[i];
		अगर (delta < 0)
			delta = -delta;
		अगर (delta < min_delta) अणु
			min_delta = delta;
			match = i;
		पूर्ण
	पूर्ण
	वापस match;
पूर्ण

अटल पूर्णांक
csio_बंदst_thresh(काष्ठा csio_sge *s, पूर्णांक cnt)
अणु
	पूर्णांक i, delta, match = 0, min_delta = पूर्णांक_उच्च;

	क्रम (i = 0; i < ARRAY_SIZE(s->counter_val); i++) अणु
		delta = cnt - s->counter_val[i];
		अगर (delta < 0)
			delta = -delta;
		अगर (delta < min_delta) अणु
			min_delta = delta;
			match = i;
		पूर्ण
	पूर्ण
	वापस match;
पूर्ण

अटल व्योम
csio_wr_fixup_host_params(काष्ठा csio_hw *hw)
अणु
	काष्ठा csio_wrm *wrm = csio_hw_to_wrm(hw);
	काष्ठा csio_sge *sge = &wrm->sge;
	uपूर्णांक32_t clsz = L1_CACHE_BYTES;
	uपूर्णांक32_t s_hps = PAGE_SHIFT - 10;
	uपूर्णांक32_t stat_len = clsz > 64 ? 128 : 64;
	u32 fl_align = clsz < 32 ? 32 : clsz;
	u32 pack_align;
	u32 ingpad, ingpack;

	csio_wr_reg32(hw, HOSTPAGESIZEPF0_V(s_hps) | HOSTPAGESIZEPF1_V(s_hps) |
		      HOSTPAGESIZEPF2_V(s_hps) | HOSTPAGESIZEPF3_V(s_hps) |
		      HOSTPAGESIZEPF4_V(s_hps) | HOSTPAGESIZEPF5_V(s_hps) |
		      HOSTPAGESIZEPF6_V(s_hps) | HOSTPAGESIZEPF7_V(s_hps),
		      SGE_HOST_PAGE_SIZE_A);

	/* T5 पूर्णांकroduced the separation of the Free List Padding and
	 * Packing Boundaries.  Thus, we can select a smaller Padding
	 * Boundary to aव्योम uselessly chewing up PCIe Link and Memory
	 * Bandwidth, and use a Packing Boundary which is large enough
	 * to aव्योम false sharing between CPUs, etc.
	 *
	 * For the PCI Link, the smaller the Padding Boundary the
	 * better.  For the Memory Controller, a smaller Padding
	 * Boundary is better until we cross under the Memory Line
	 * Size (the minimum unit of transfer to/from Memory).  If we
	 * have a Padding Boundary which is smaller than the Memory
	 * Line Size, that'll involve a Read-Modअगरy-Write cycle on the
	 * Memory Controller which is never good.
	 */

	/* We want the Packing Boundary to be based on the Cache Line
	 * Size in order to help aव्योम False Sharing perक्रमmance
	 * issues between CPUs, etc.  We also want the Packing
	 * Boundary to incorporate the PCI-E Maximum Payload Size.  We
	 * get best perक्रमmance when the Packing Boundary is a
	 * multiple of the Maximum Payload Size.
	 */
	pack_align = fl_align;
	अगर (pci_is_pcie(hw->pdev)) अणु
		u32 mps, mps_log;
		u16 devctl;

		/* The PCIe Device Control Maximum Payload Size field
		 * [bits 7:5] encodes sizes as घातers of 2 starting at
		 * 128 bytes.
		 */
		pcie_capability_पढ़ो_word(hw->pdev, PCI_EXP_DEVCTL, &devctl);
		mps_log = ((devctl & PCI_EXP_DEVCTL_PAYLOAD) >> 5) + 7;
		mps = 1 << mps_log;
		अगर (mps > pack_align)
			pack_align = mps;
	पूर्ण

	/* T5/T6 have a special पूर्णांकerpretation of the "0"
	 * value क्रम the Packing Boundary.  This corresponds to 16
	 * bytes instead of the expected 32 bytes.
	 */
	अगर (pack_align <= 16) अणु
		ingpack = INGPACKBOUNDARY_16B_X;
		fl_align = 16;
	पूर्ण अन्यथा अगर (pack_align == 32) अणु
		ingpack = INGPACKBOUNDARY_64B_X;
		fl_align = 64;
	पूर्ण अन्यथा अणु
		u32 pack_align_log = fls(pack_align) - 1;

		ingpack = pack_align_log - INGPACKBOUNDARY_SHIFT_X;
		fl_align = pack_align;
	पूर्ण

	/* Use the smallest Ingress Padding which isn't smaller than
	 * the Memory Controller Read/Write Size.  We'll take that as
	 * being 8 bytes since we करोn't know of any प्रणाली with a
	 * wider Memory Controller Bus Width.
	 */
	अगर (csio_is_t5(hw->pdev->device & CSIO_HW_CHIP_MASK))
		ingpad = INGPADBOUNDARY_32B_X;
	अन्यथा
		ingpad = T6_INGPADBOUNDARY_8B_X;

	csio_set_reg_field(hw, SGE_CONTROL_A,
			   INGPADBOUNDARY_V(INGPADBOUNDARY_M) |
			   EGRSTATUSPAGESIZE_F,
			   INGPADBOUNDARY_V(ingpad) |
			   EGRSTATUSPAGESIZE_V(stat_len != 64));
	csio_set_reg_field(hw, SGE_CONTROL2_A,
			   INGPACKBOUNDARY_V(INGPACKBOUNDARY_M),
			   INGPACKBOUNDARY_V(ingpack));

	/* FL BUFFER SIZE#0 is Page size i,e alपढ़ोy aligned to cache line */
	csio_wr_reg32(hw, PAGE_SIZE, SGE_FL_BUFFER_SIZE0_A);

	/*
	 * If using hard params, the following will get set correctly
	 * in csio_wr_set_sge().
	 */
	अगर (hw->flags & CSIO_HWF_USING_SOFT_PARAMS) अणु
		csio_wr_reg32(hw,
			(csio_rd_reg32(hw, SGE_FL_BUFFER_SIZE2_A) +
			fl_align - 1) & ~(fl_align - 1),
			SGE_FL_BUFFER_SIZE2_A);
		csio_wr_reg32(hw,
			(csio_rd_reg32(hw, SGE_FL_BUFFER_SIZE3_A) +
			fl_align - 1) & ~(fl_align - 1),
			SGE_FL_BUFFER_SIZE3_A);
	पूर्ण

	sge->csio_fl_align = fl_align;

	csio_wr_reg32(hw, HPZ0_V(PAGE_SHIFT - 12), ULP_RX_TDDP_PSZ_A);

	/* शेष value of rx_dma_offset of the NIC driver */
	csio_set_reg_field(hw, SGE_CONTROL_A,
			   PKTSHIFT_V(PKTSHIFT_M),
			   PKTSHIFT_V(CSIO_SGE_RX_DMA_OFFSET));

	csio_hw_tp_wr_bits_indirect(hw, TP_INGRESS_CONFIG_A,
				    CSUM_HAS_PSEUDO_HDR_F, 0);
पूर्ण

अटल व्योम
csio_init_पूर्णांकr_coalesce_parms(काष्ठा csio_hw *hw)
अणु
	काष्ठा csio_wrm *wrm = csio_hw_to_wrm(hw);
	काष्ठा csio_sge *sge = &wrm->sge;

	csio_sge_thresh_reg = csio_बंदst_thresh(sge, csio_पूर्णांकr_coalesce_cnt);
	अगर (csio_पूर्णांकr_coalesce_cnt) अणु
		csio_sge_thresh_reg = 0;
		csio_sge_समयr_reg = X_TIMERREG_RESTART_COUNTER;
		वापस;
	पूर्ण

	csio_sge_समयr_reg = csio_बंदst_समयr(sge, csio_पूर्णांकr_coalesce_समय);
पूर्ण

/*
 * csio_wr_get_sge - Get SGE रेजिस्टर values.
 * @hw: HW module.
 *
 * Used by non-master functions and by master-functions relying on config file.
 */
अटल व्योम
csio_wr_get_sge(काष्ठा csio_hw *hw)
अणु
	काष्ठा csio_wrm *wrm = csio_hw_to_wrm(hw);
	काष्ठा csio_sge *sge = &wrm->sge;
	uपूर्णांक32_t ingpad;
	पूर्णांक i;
	u32 समयr_value_0_and_1, समयr_value_2_and_3, समयr_value_4_and_5;
	u32 ingress_rx_threshold;

	sge->sge_control = csio_rd_reg32(hw, SGE_CONTROL_A);

	ingpad = INGPADBOUNDARY_G(sge->sge_control);

	चयन (ingpad) अणु
	हाल X_INGPCIEBOUNDARY_32B:
		sge->csio_fl_align = 32; अवरोध;
	हाल X_INGPCIEBOUNDARY_64B:
		sge->csio_fl_align = 64; अवरोध;
	हाल X_INGPCIEBOUNDARY_128B:
		sge->csio_fl_align = 128; अवरोध;
	हाल X_INGPCIEBOUNDARY_256B:
		sge->csio_fl_align = 256; अवरोध;
	हाल X_INGPCIEBOUNDARY_512B:
		sge->csio_fl_align = 512; अवरोध;
	हाल X_INGPCIEBOUNDARY_1024B:
		sge->csio_fl_align = 1024; अवरोध;
	हाल X_INGPCIEBOUNDARY_2048B:
		sge->csio_fl_align = 2048; अवरोध;
	हाल X_INGPCIEBOUNDARY_4096B:
		sge->csio_fl_align = 4096; अवरोध;
	पूर्ण

	क्रम (i = 0; i < CSIO_SGE_FL_SIZE_REGS; i++)
		csio_get_flbuf_size(hw, sge, i);

	समयr_value_0_and_1 = csio_rd_reg32(hw, SGE_TIMER_VALUE_0_AND_1_A);
	समयr_value_2_and_3 = csio_rd_reg32(hw, SGE_TIMER_VALUE_2_AND_3_A);
	समयr_value_4_and_5 = csio_rd_reg32(hw, SGE_TIMER_VALUE_4_AND_5_A);

	sge->समयr_val[0] = (uपूर्णांक16_t)csio_core_ticks_to_us(hw,
					TIMERVALUE0_G(समयr_value_0_and_1));
	sge->समयr_val[1] = (uपूर्णांक16_t)csio_core_ticks_to_us(hw,
					TIMERVALUE1_G(समयr_value_0_and_1));
	sge->समयr_val[2] = (uपूर्णांक16_t)csio_core_ticks_to_us(hw,
					TIMERVALUE2_G(समयr_value_2_and_3));
	sge->समयr_val[3] = (uपूर्णांक16_t)csio_core_ticks_to_us(hw,
					TIMERVALUE3_G(समयr_value_2_and_3));
	sge->समयr_val[4] = (uपूर्णांक16_t)csio_core_ticks_to_us(hw,
					TIMERVALUE4_G(समयr_value_4_and_5));
	sge->समयr_val[5] = (uपूर्णांक16_t)csio_core_ticks_to_us(hw,
					TIMERVALUE5_G(समयr_value_4_and_5));

	ingress_rx_threshold = csio_rd_reg32(hw, SGE_INGRESS_RX_THRESHOLD_A);
	sge->counter_val[0] = THRESHOLD_0_G(ingress_rx_threshold);
	sge->counter_val[1] = THRESHOLD_1_G(ingress_rx_threshold);
	sge->counter_val[2] = THRESHOLD_2_G(ingress_rx_threshold);
	sge->counter_val[3] = THRESHOLD_3_G(ingress_rx_threshold);

	csio_init_पूर्णांकr_coalesce_parms(hw);
पूर्ण

/*
 * csio_wr_set_sge - Initialize SGE रेजिस्टरs
 * @hw: HW module.
 *
 * Used by Master function to initialize SGE रेजिस्टरs in the असलence
 * of a config file.
 */
अटल व्योम
csio_wr_set_sge(काष्ठा csio_hw *hw)
अणु
	काष्ठा csio_wrm *wrm = csio_hw_to_wrm(hw);
	काष्ठा csio_sge *sge = &wrm->sge;
	पूर्णांक i;

	/*
	 * Set up our basic SGE mode to deliver CPL messages to our Ingress
	 * Queue and Packet Date to the Free List.
	 */
	csio_set_reg_field(hw, SGE_CONTROL_A, RXPKTCPLMODE_F, RXPKTCPLMODE_F);

	sge->sge_control = csio_rd_reg32(hw, SGE_CONTROL_A);

	/* sge->csio_fl_align is set up by csio_wr_fixup_host_params(). */

	/*
	 * Set up to drop DOORBELL ग_लिखोs when the DOORBELL FIFO overflows
	 * and generate an पूर्णांकerrupt when this occurs so we can recover.
	 */
	csio_set_reg_field(hw, SGE_DBFIFO_STATUS_A,
			   LP_INT_THRESH_T5_V(LP_INT_THRESH_T5_M),
			   LP_INT_THRESH_T5_V(CSIO_SGE_DBFIFO_INT_THRESH));
	csio_set_reg_field(hw, SGE_DBFIFO_STATUS2_A,
			   HP_INT_THRESH_T5_V(LP_INT_THRESH_T5_M),
			   HP_INT_THRESH_T5_V(CSIO_SGE_DBFIFO_INT_THRESH));

	csio_set_reg_field(hw, SGE_DOORBELL_CONTROL_A, ENABLE_DROP_F,
			   ENABLE_DROP_F);

	/* SGE_FL_BUFFER_SIZE0 is set up by csio_wr_fixup_host_params(). */

	CSIO_SET_FLBUF_SIZE(hw, 1, CSIO_SGE_FLBUF_SIZE1);
	csio_wr_reg32(hw, (CSIO_SGE_FLBUF_SIZE2 + sge->csio_fl_align - 1)
		      & ~(sge->csio_fl_align - 1), SGE_FL_BUFFER_SIZE2_A);
	csio_wr_reg32(hw, (CSIO_SGE_FLBUF_SIZE3 + sge->csio_fl_align - 1)
		      & ~(sge->csio_fl_align - 1), SGE_FL_BUFFER_SIZE3_A);
	CSIO_SET_FLBUF_SIZE(hw, 4, CSIO_SGE_FLBUF_SIZE4);
	CSIO_SET_FLBUF_SIZE(hw, 5, CSIO_SGE_FLBUF_SIZE5);
	CSIO_SET_FLBUF_SIZE(hw, 6, CSIO_SGE_FLBUF_SIZE6);
	CSIO_SET_FLBUF_SIZE(hw, 7, CSIO_SGE_FLBUF_SIZE7);
	CSIO_SET_FLBUF_SIZE(hw, 8, CSIO_SGE_FLBUF_SIZE8);

	क्रम (i = 0; i < CSIO_SGE_FL_SIZE_REGS; i++)
		csio_get_flbuf_size(hw, sge, i);

	/* Initialize पूर्णांकerrupt coalescing attributes */
	sge->समयr_val[0] = CSIO_SGE_TIMER_VAL_0;
	sge->समयr_val[1] = CSIO_SGE_TIMER_VAL_1;
	sge->समयr_val[2] = CSIO_SGE_TIMER_VAL_2;
	sge->समयr_val[3] = CSIO_SGE_TIMER_VAL_3;
	sge->समयr_val[4] = CSIO_SGE_TIMER_VAL_4;
	sge->समयr_val[5] = CSIO_SGE_TIMER_VAL_5;

	sge->counter_val[0] = CSIO_SGE_INT_CNT_VAL_0;
	sge->counter_val[1] = CSIO_SGE_INT_CNT_VAL_1;
	sge->counter_val[2] = CSIO_SGE_INT_CNT_VAL_2;
	sge->counter_val[3] = CSIO_SGE_INT_CNT_VAL_3;

	csio_wr_reg32(hw, THRESHOLD_0_V(sge->counter_val[0]) |
		      THRESHOLD_1_V(sge->counter_val[1]) |
		      THRESHOLD_2_V(sge->counter_val[2]) |
		      THRESHOLD_3_V(sge->counter_val[3]),
		      SGE_INGRESS_RX_THRESHOLD_A);

	csio_wr_reg32(hw,
		   TIMERVALUE0_V(csio_us_to_core_ticks(hw, sge->समयr_val[0])) |
		   TIMERVALUE1_V(csio_us_to_core_ticks(hw, sge->समयr_val[1])),
		   SGE_TIMER_VALUE_0_AND_1_A);

	csio_wr_reg32(hw,
		   TIMERVALUE2_V(csio_us_to_core_ticks(hw, sge->समयr_val[2])) |
		   TIMERVALUE3_V(csio_us_to_core_ticks(hw, sge->समयr_val[3])),
		   SGE_TIMER_VALUE_2_AND_3_A);

	csio_wr_reg32(hw,
		   TIMERVALUE4_V(csio_us_to_core_ticks(hw, sge->समयr_val[4])) |
		   TIMERVALUE5_V(csio_us_to_core_ticks(hw, sge->समयr_val[5])),
		   SGE_TIMER_VALUE_4_AND_5_A);

	csio_init_पूर्णांकr_coalesce_parms(hw);
पूर्ण

व्योम
csio_wr_sge_init(काष्ठा csio_hw *hw)
अणु
	/*
	 * If we are master and chip is not initialized:
	 *    - If we plan to use the config file, we need to fixup some
	 *      host specअगरic रेजिस्टरs, and पढ़ो the rest of the SGE
	 *      configuration.
	 *    - If we करोnt plan to use the config file, we need to initialize
	 *      SGE entirely, including fixing the host specअगरic रेजिस्टरs.
	 * If we are master and chip is initialized, just पढ़ो and work off of
	 *	the alपढ़ोy initialized SGE values.
	 * If we arent the master, we are only allowed to पढ़ो and work off of
	 *      the alपढ़ोy initialized SGE values.
	 *
	 * Thereक्रमe, beक्रमe calling this function, we assume that the master-
	 * ship of the card, state and whether to use config file or not, have
	 * alपढ़ोy been decided.
	 */
	अगर (csio_is_hw_master(hw)) अणु
		अगर (hw->fw_state != CSIO_DEV_STATE_INIT)
			csio_wr_fixup_host_params(hw);

		अगर (hw->flags & CSIO_HWF_USING_SOFT_PARAMS)
			csio_wr_get_sge(hw);
		अन्यथा
			csio_wr_set_sge(hw);
	पूर्ण अन्यथा
		csio_wr_get_sge(hw);
पूर्ण

/*
 * csio_wrm_init - Initialize Work request module.
 * @wrm: WR module
 * @hw: HW poपूर्णांकer
 *
 * Allocates memory क्रम an array of queue poपूर्णांकers starting at q_arr.
 */
पूर्णांक
csio_wrm_init(काष्ठा csio_wrm *wrm, काष्ठा csio_hw *hw)
अणु
	पूर्णांक i;

	अगर (!wrm->num_q) अणु
		csio_err(hw, "Num queues is not set\n");
		वापस -EINVAL;
	पूर्ण

	wrm->q_arr = kसुस्मृति(wrm->num_q, माप(काष्ठा csio_q *), GFP_KERNEL);
	अगर (!wrm->q_arr)
		जाओ err;

	क्रम (i = 0; i < wrm->num_q; i++) अणु
		wrm->q_arr[i] = kzalloc(माप(काष्ठा csio_q), GFP_KERNEL);
		अगर (!wrm->q_arr[i]) अणु
			जबतक (--i >= 0)
				kमुक्त(wrm->q_arr[i]);
			जाओ err_मुक्त_arr;
		पूर्ण
	पूर्ण
	wrm->मुक्त_qidx	= 0;

	वापस 0;

err_मुक्त_arr:
	kमुक्त(wrm->q_arr);
err:
	वापस -ENOMEM;
पूर्ण

/*
 * csio_wrm_निकास - Initialize Work request module.
 * @wrm: WR module
 * @hw: HW module
 *
 * Uninitialize WR module. Free q_arr and poपूर्णांकers in it.
 * We have the additional job of मुक्तing the DMA memory associated
 * with the queues.
 */
व्योम
csio_wrm_निकास(काष्ठा csio_wrm *wrm, काष्ठा csio_hw *hw)
अणु
	पूर्णांक i;
	uपूर्णांक32_t j;
	काष्ठा csio_q *q;
	काष्ठा csio_dma_buf *buf;

	क्रम (i = 0; i < wrm->num_q; i++) अणु
		q = wrm->q_arr[i];

		अगर (wrm->मुक्त_qidx && (i < wrm->मुक्त_qidx)) अणु
			अगर (q->type == CSIO_FREELIST) अणु
				अगर (!q->un.fl.bufs)
					जारी;
				क्रम (j = 0; j < q->credits; j++) अणु
					buf = &q->un.fl.bufs[j];
					अगर (!buf->vaddr)
						जारी;
					dma_मुक्त_coherent(&hw->pdev->dev,
							buf->len, buf->vaddr,
							buf->paddr);
				पूर्ण
				kमुक्त(q->un.fl.bufs);
			पूर्ण
			dma_मुक्त_coherent(&hw->pdev->dev, q->size,
					q->vstart, q->pstart);
		पूर्ण
		kमुक्त(q);
	पूर्ण

	hw->flags &= ~CSIO_HWF_Q_MEM_ALLOCED;

	kमुक्त(wrm->q_arr);
पूर्ण
