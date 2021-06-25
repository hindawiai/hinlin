<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 RVU Physcial Function ethernet driver
 *
 * Copyright (C) 2020 Marvell.
 */

#समावेश "cn10k.h"
#समावेश "otx2_reg.h"
#समावेश "otx2_struct.h"

अटल काष्ठा dev_hw_ops	otx2_hw_ops = अणु
	.sq_aq_init = otx2_sq_aq_init,
	.sqe_flush = otx2_sqe_flush,
	.aura_मुक्तptr = otx2_aura_मुक्तptr,
	.refill_pool_ptrs = otx2_refill_pool_ptrs,
पूर्ण;

अटल काष्ठा dev_hw_ops cn10k_hw_ops = अणु
	.sq_aq_init = cn10k_sq_aq_init,
	.sqe_flush = cn10k_sqe_flush,
	.aura_मुक्तptr = cn10k_aura_मुक्तptr,
	.refill_pool_ptrs = cn10k_refill_pool_ptrs,
पूर्ण;

पूर्णांक cn10k_pf_lmtst_init(काष्ठा otx2_nic *pf)
अणु
	पूर्णांक size, num_lines;
	u64 base;

	अगर (!test_bit(CN10K_LMTST, &pf->hw.cap_flag)) अणु
		pf->hw_ops = &otx2_hw_ops;
		वापस 0;
	पूर्ण

	pf->hw_ops = &cn10k_hw_ops;
	base = pci_resource_start(pf->pdev, PCI_MBOX_BAR_NUM) +
		       (MBOX_SIZE * (pf->total_vfs + 1));

	size = pci_resource_len(pf->pdev, PCI_MBOX_BAR_NUM) -
	       (MBOX_SIZE * (pf->total_vfs + 1));

	pf->hw.lmt_base = ioremap(base, size);

	अगर (!pf->hw.lmt_base) अणु
		dev_err(pf->dev, "Unable to map PF LMTST region\n");
		वापस -ENOMEM;
	पूर्ण

	/* FIXME: Get the num of LMTST lines from LMT table */
	pf->tot_lmt_lines = size / LMT_LINE_SIZE;
	num_lines = (pf->tot_lmt_lines - NIX_LMTID_BASE) /
			    pf->hw.tx_queues;
	/* Number of LMT lines per SQ queues */
	pf->nix_lmt_lines = num_lines > 32 ? 32 : num_lines;

	pf->nix_lmt_size = pf->nix_lmt_lines * LMT_LINE_SIZE;
	वापस 0;
पूर्ण

पूर्णांक cn10k_vf_lmtst_init(काष्ठा otx2_nic *vf)
अणु
	पूर्णांक size, num_lines;

	अगर (!test_bit(CN10K_LMTST, &vf->hw.cap_flag)) अणु
		vf->hw_ops = &otx2_hw_ops;
		वापस 0;
	पूर्ण

	vf->hw_ops = &cn10k_hw_ops;
	size = pci_resource_len(vf->pdev, PCI_MBOX_BAR_NUM);
	vf->hw.lmt_base = ioremap_wc(pci_resource_start(vf->pdev,
							PCI_MBOX_BAR_NUM),
				     size);
	अगर (!vf->hw.lmt_base) अणु
		dev_err(vf->dev, "Unable to map VF LMTST region\n");
		वापस -ENOMEM;
	पूर्ण

	vf->tot_lmt_lines = size / LMT_LINE_SIZE;
	/* LMTST lines per SQ */
	num_lines = (vf->tot_lmt_lines - NIX_LMTID_BASE) /
			    vf->hw.tx_queues;
	vf->nix_lmt_lines = num_lines > 32 ? 32 : num_lines;
	vf->nix_lmt_size = vf->nix_lmt_lines * LMT_LINE_SIZE;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cn10k_vf_lmtst_init);

पूर्णांक cn10k_sq_aq_init(व्योम *dev, u16 qidx, u16 sqb_aura)
अणु
	काष्ठा nix_cn10k_aq_enq_req *aq;
	काष्ठा otx2_nic *pfvf = dev;
	काष्ठा otx2_snd_queue *sq;

	sq = &pfvf->qset.sq[qidx];
	sq->lmt_addr = (__क्रमce u64 *)((u64)pfvf->hw.nix_lmt_base +
			       (qidx * pfvf->nix_lmt_size));

	/* Get memory to put this msg */
	aq = otx2_mbox_alloc_msg_nix_cn10k_aq_enq(&pfvf->mbox);
	अगर (!aq)
		वापस -ENOMEM;

	aq->sq.cq = pfvf->hw.rx_queues + qidx;
	aq->sq.max_sqe_size = NIX_MAXSQESZ_W16; /* 128 byte */
	aq->sq.cq_ena = 1;
	aq->sq.ena = 1;
	/* Only one SMQ is allocated, map all SQ's to that SMQ  */
	aq->sq.smq = pfvf->hw.txschq_list[NIX_TXSCH_LVL_SMQ][0];
	/* FIXME: set based on NIX_AF_DWRR_RPM_MTU*/
	aq->sq.smq_rr_weight = pfvf->netdev->mtu;
	aq->sq.शेष_chan = pfvf->hw.tx_chan_base;
	aq->sq.sqe_stype = NIX_STYPE_STF; /* Cache SQB */
	aq->sq.sqb_aura = sqb_aura;
	aq->sq.sq_पूर्णांक_ena = NIX_SQINT_BITS;
	aq->sq.qपूर्णांक_idx = 0;
	/* Due pipelining impact minimum 2000 unused SQ CQE's
	 * need to मुख्यtain to aव्योम CQ overflow.
	 */
	aq->sq.cq_limit = ((SEND_CQ_SKID * 256) / (pfvf->qset.sqe_cnt));

	/* Fill AQ info */
	aq->qidx = qidx;
	aq->ctype = NIX_AQ_CTYPE_SQ;
	aq->op = NIX_AQ_INSTOP_INIT;

	वापस otx2_sync_mbox_msg(&pfvf->mbox);
पूर्ण

#घोषणा NPA_MAX_BURST 16
व्योम cn10k_refill_pool_ptrs(व्योम *dev, काष्ठा otx2_cq_queue *cq)
अणु
	काष्ठा otx2_nic *pfvf = dev;
	u64 ptrs[NPA_MAX_BURST];
	पूर्णांक num_ptrs = 1;
	dma_addr_t bufptr;

	/* Refill pool with new buffers */
	जबतक (cq->pool_ptrs) अणु
		अगर (otx2_alloc_buffer(pfvf, cq, &bufptr)) अणु
			अगर (num_ptrs--)
				__cn10k_aura_मुक्तptr(pfvf, cq->cq_idx, ptrs,
						     num_ptrs,
						     cq->rbpool->lmt_addr);
			अवरोध;
		पूर्ण
		cq->pool_ptrs--;
		ptrs[num_ptrs] = (u64)bufptr + OTX2_HEAD_ROOM;
		num_ptrs++;
		अगर (num_ptrs == NPA_MAX_BURST || cq->pool_ptrs == 0) अणु
			__cn10k_aura_मुक्तptr(pfvf, cq->cq_idx, ptrs,
					     num_ptrs,
					     cq->rbpool->lmt_addr);
			num_ptrs = 1;
		पूर्ण
	पूर्ण
पूर्ण

व्योम cn10k_sqe_flush(व्योम *dev, काष्ठा otx2_snd_queue *sq, पूर्णांक size, पूर्णांक qidx)
अणु
	काष्ठा otx2_nic *pfvf = dev;
	पूर्णांक lmt_id = NIX_LMTID_BASE + (qidx * pfvf->nix_lmt_lines);
	u64 val = 0, tar_addr = 0;

	/* FIXME: val[0:10] LMT_ID.
	 * [12:15] no of LMTST - 1 in the burst.
	 * [19:63] data size of each LMTST in the burst except first.
	 */
	val = (lmt_id & 0x7FF);
	/* Target address क्रम LMTST flush tells HW how many 128bit
	 * words are present.
	 * tar_addr[6:4] size of first LMTST - 1 in units of 128b.
	 */
	tar_addr |= sq->io_addr | (((size / 16) - 1) & 0x7) << 4;
	dma_wmb();
	स_नकल(sq->lmt_addr, sq->sqe_base, size);
	cn10k_lmt_flush(val, tar_addr);

	sq->head++;
	sq->head &= (sq->sqe_cnt - 1);
पूर्ण
