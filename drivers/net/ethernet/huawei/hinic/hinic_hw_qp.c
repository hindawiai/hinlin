<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sizes.h>
#समावेश <linux/atomic.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "hinic_common.h"
#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_wqe.h"
#समावेश "hinic_hw_wq.h"
#समावेश "hinic_hw_qp_ctxt.h"
#समावेश "hinic_hw_qp.h"
#समावेश "hinic_hw_io.h"

#घोषणा SQ_DB_OFF               SZ_2K

/* The number of cache line to prefetch Until threshold state */
#घोषणा WQ_PREFETCH_MAX         2
/* The number of cache line to prefetch After threshold state */
#घोषणा WQ_PREFETCH_MIN         1
/* Threshold state */
#घोषणा WQ_PREFETCH_THRESHOLD   256

/* sizes of the SQ/RQ ctxt */
#घोषणा Q_CTXT_SIZE             48
#घोषणा CTXT_RSVD               240

#घोषणा SQ_CTXT_OFFSET(max_sqs, max_rqs, q_id)  \
		(((max_rqs) + (max_sqs)) * CTXT_RSVD + (q_id) * Q_CTXT_SIZE)

#घोषणा RQ_CTXT_OFFSET(max_sqs, max_rqs, q_id)  \
		(((max_rqs) + (max_sqs)) * CTXT_RSVD + \
		 (max_sqs + (q_id)) * Q_CTXT_SIZE)

#घोषणा SIZE_16BYTES(size)              (ALIGN(size, 16) >> 4)
#घोषणा SIZE_8BYTES(size)               (ALIGN(size, 8) >> 3)
#घोषणा SECT_SIZE_FROM_8BYTES(size)     ((size) << 3)

#घोषणा SQ_DB_PI_HI_SHIFT       8
#घोषणा SQ_DB_PI_HI(prod_idx)   ((prod_idx) >> SQ_DB_PI_HI_SHIFT)

#घोषणा SQ_DB_PI_LOW_MASK       0xFF
#घोषणा SQ_DB_PI_LOW(prod_idx)  ((prod_idx) & SQ_DB_PI_LOW_MASK)

#घोषणा SQ_DB_ADDR(sq, pi)      ((u64 *)((sq)->db_base) + SQ_DB_PI_LOW(pi))

#घोषणा SQ_MASKED_IDX(sq, idx)  ((idx) & (sq)->wq->mask)
#घोषणा RQ_MASKED_IDX(rq, idx)  ((idx) & (rq)->wq->mask)

क्रमागत sq_wqe_type अणु
	SQ_NORMAL_WQE = 0,
पूर्ण;

क्रमागत rq_completion_fmt अणु
	RQ_COMPLETE_SGE = 1
पूर्ण;

व्योम hinic_qp_prepare_header(काष्ठा hinic_qp_ctxt_header *qp_ctxt_hdr,
			     क्रमागत hinic_qp_ctxt_type ctxt_type,
			     u16 num_queues, u16 max_queues)
अणु
	u16 max_sqs = max_queues;
	u16 max_rqs = max_queues;

	qp_ctxt_hdr->num_queues = num_queues;
	qp_ctxt_hdr->queue_type = ctxt_type;

	अगर (ctxt_type == HINIC_QP_CTXT_TYPE_SQ)
		qp_ctxt_hdr->addr_offset = SQ_CTXT_OFFSET(max_sqs, max_rqs, 0);
	अन्यथा
		qp_ctxt_hdr->addr_offset = RQ_CTXT_OFFSET(max_sqs, max_rqs, 0);

	qp_ctxt_hdr->addr_offset = SIZE_16BYTES(qp_ctxt_hdr->addr_offset);

	hinic_cpu_to_be32(qp_ctxt_hdr, माप(*qp_ctxt_hdr));
पूर्ण

व्योम hinic_sq_prepare_ctxt(काष्ठा hinic_sq_ctxt *sq_ctxt,
			   काष्ठा hinic_sq *sq, u16 global_qid)
अणु
	u32 wq_page_pfn_hi, wq_page_pfn_lo, wq_block_pfn_hi, wq_block_pfn_lo;
	u64 wq_page_addr, wq_page_pfn, wq_block_pfn;
	u16 pi_start, ci_start;
	काष्ठा hinic_wq *wq;

	wq = sq->wq;
	ci_start = atomic_पढ़ो(&wq->cons_idx);
	pi_start = atomic_पढ़ो(&wq->prod_idx);

	/* Read the first page paddr from the WQ page paddr ptrs */
	wq_page_addr = be64_to_cpu(*wq->block_vaddr);

	wq_page_pfn = HINIC_WQ_PAGE_PFN(wq_page_addr);
	wq_page_pfn_hi = upper_32_bits(wq_page_pfn);
	wq_page_pfn_lo = lower_32_bits(wq_page_pfn);

	/* If only one page, use 0-level CLA */
	अगर (wq->num_q_pages == 1)
		wq_block_pfn = HINIC_WQ_BLOCK_PFN(wq_page_addr);
	अन्यथा
		wq_block_pfn = HINIC_WQ_BLOCK_PFN(wq->block_paddr);

	wq_block_pfn_hi = upper_32_bits(wq_block_pfn);
	wq_block_pfn_lo = lower_32_bits(wq_block_pfn);

	sq_ctxt->ceq_attr = HINIC_SQ_CTXT_CEQ_ATTR_SET(global_qid,
						       GLOBAL_SQ_ID) |
			    HINIC_SQ_CTXT_CEQ_ATTR_SET(0, EN);

	sq_ctxt->ci_wrapped = HINIC_SQ_CTXT_CI_SET(ci_start, IDX) |
			      HINIC_SQ_CTXT_CI_SET(1, WRAPPED);

	sq_ctxt->wq_hi_pfn_pi =
			HINIC_SQ_CTXT_WQ_PAGE_SET(wq_page_pfn_hi, HI_PFN) |
			HINIC_SQ_CTXT_WQ_PAGE_SET(pi_start, PI);

	sq_ctxt->wq_lo_pfn = wq_page_pfn_lo;

	sq_ctxt->pref_cache =
		HINIC_SQ_CTXT_PREF_SET(WQ_PREFETCH_MIN, CACHE_MIN) |
		HINIC_SQ_CTXT_PREF_SET(WQ_PREFETCH_MAX, CACHE_MAX) |
		HINIC_SQ_CTXT_PREF_SET(WQ_PREFETCH_THRESHOLD, CACHE_THRESHOLD);

	sq_ctxt->pref_wrapped = 1;

	sq_ctxt->pref_wq_hi_pfn_ci =
		HINIC_SQ_CTXT_PREF_SET(ci_start, CI) |
		HINIC_SQ_CTXT_PREF_SET(wq_page_pfn_hi, WQ_HI_PFN);

	sq_ctxt->pref_wq_lo_pfn = wq_page_pfn_lo;

	sq_ctxt->wq_block_hi_pfn =
		HINIC_SQ_CTXT_WQ_BLOCK_SET(wq_block_pfn_hi, HI_PFN);

	sq_ctxt->wq_block_lo_pfn = wq_block_pfn_lo;

	hinic_cpu_to_be32(sq_ctxt, माप(*sq_ctxt));
पूर्ण

व्योम hinic_rq_prepare_ctxt(काष्ठा hinic_rq_ctxt *rq_ctxt,
			   काष्ठा hinic_rq *rq, u16 global_qid)
अणु
	u32 wq_page_pfn_hi, wq_page_pfn_lo, wq_block_pfn_hi, wq_block_pfn_lo;
	u64 wq_page_addr, wq_page_pfn, wq_block_pfn;
	u16 pi_start, ci_start;
	काष्ठा hinic_wq *wq;

	wq = rq->wq;
	ci_start = atomic_पढ़ो(&wq->cons_idx);
	pi_start = atomic_पढ़ो(&wq->prod_idx);

	/* Read the first page paddr from the WQ page paddr ptrs */
	wq_page_addr = be64_to_cpu(*wq->block_vaddr);

	wq_page_pfn = HINIC_WQ_PAGE_PFN(wq_page_addr);
	wq_page_pfn_hi = upper_32_bits(wq_page_pfn);
	wq_page_pfn_lo = lower_32_bits(wq_page_pfn);

	wq_block_pfn = HINIC_WQ_BLOCK_PFN(wq->block_paddr);
	wq_block_pfn_hi = upper_32_bits(wq_block_pfn);
	wq_block_pfn_lo = lower_32_bits(wq_block_pfn);

	rq_ctxt->ceq_attr = HINIC_RQ_CTXT_CEQ_ATTR_SET(0, EN) |
			    HINIC_RQ_CTXT_CEQ_ATTR_SET(1, WRAPPED);

	rq_ctxt->pi_पूर्णांकr_attr = HINIC_RQ_CTXT_PI_SET(pi_start, IDX) |
				HINIC_RQ_CTXT_PI_SET(rq->msix_entry, INTR);

	rq_ctxt->wq_hi_pfn_ci = HINIC_RQ_CTXT_WQ_PAGE_SET(wq_page_pfn_hi,
							  HI_PFN) |
				HINIC_RQ_CTXT_WQ_PAGE_SET(ci_start, CI);

	rq_ctxt->wq_lo_pfn = wq_page_pfn_lo;

	rq_ctxt->pref_cache =
		HINIC_RQ_CTXT_PREF_SET(WQ_PREFETCH_MIN, CACHE_MIN) |
		HINIC_RQ_CTXT_PREF_SET(WQ_PREFETCH_MAX, CACHE_MAX) |
		HINIC_RQ_CTXT_PREF_SET(WQ_PREFETCH_THRESHOLD, CACHE_THRESHOLD);

	rq_ctxt->pref_wrapped = 1;

	rq_ctxt->pref_wq_hi_pfn_ci =
		HINIC_RQ_CTXT_PREF_SET(wq_page_pfn_hi, WQ_HI_PFN) |
		HINIC_RQ_CTXT_PREF_SET(ci_start, CI);

	rq_ctxt->pref_wq_lo_pfn = wq_page_pfn_lo;

	rq_ctxt->pi_paddr_hi = upper_32_bits(rq->pi_dma_addr);
	rq_ctxt->pi_paddr_lo = lower_32_bits(rq->pi_dma_addr);

	rq_ctxt->wq_block_hi_pfn =
		HINIC_RQ_CTXT_WQ_BLOCK_SET(wq_block_pfn_hi, HI_PFN);

	rq_ctxt->wq_block_lo_pfn = wq_block_pfn_lo;

	hinic_cpu_to_be32(rq_ctxt, माप(*rq_ctxt));
पूर्ण

/**
 * alloc_sq_skb_arr - allocate sq array क्रम saved skb
 * @sq: HW Send Queue
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक alloc_sq_skb_arr(काष्ठा hinic_sq *sq)
अणु
	काष्ठा hinic_wq *wq = sq->wq;
	माप_प्रकार skb_arr_size;

	skb_arr_size = wq->q_depth * माप(*sq->saved_skb);
	sq->saved_skb = vzalloc(skb_arr_size);
	अगर (!sq->saved_skb)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * मुक्त_sq_skb_arr - मुक्त sq array क्रम saved skb
 * @sq: HW Send Queue
 **/
अटल व्योम मुक्त_sq_skb_arr(काष्ठा hinic_sq *sq)
अणु
	vमुक्त(sq->saved_skb);
पूर्ण

/**
 * alloc_rq_skb_arr - allocate rq array क्रम saved skb
 * @rq: HW Receive Queue
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक alloc_rq_skb_arr(काष्ठा hinic_rq *rq)
अणु
	काष्ठा hinic_wq *wq = rq->wq;
	माप_प्रकार skb_arr_size;

	skb_arr_size = wq->q_depth * माप(*rq->saved_skb);
	rq->saved_skb = vzalloc(skb_arr_size);
	अगर (!rq->saved_skb)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * मुक्त_rq_skb_arr - मुक्त rq array क्रम saved skb
 * @rq: HW Receive Queue
 **/
अटल व्योम मुक्त_rq_skb_arr(काष्ठा hinic_rq *rq)
अणु
	vमुक्त(rq->saved_skb);
पूर्ण

/**
 * hinic_init_sq - Initialize HW Send Queue
 * @sq: HW Send Queue
 * @hwअगर: HW Interface क्रम accessing HW
 * @wq: Work Queue क्रम the data of the SQ
 * @entry: msix entry क्रम sq
 * @ci_addr: address क्रम पढ़ोing the current HW consumer index
 * @ci_dma_addr: dma address क्रम पढ़ोing the current HW consumer index
 * @db_base: करोorbell base address
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_init_sq(काष्ठा hinic_sq *sq, काष्ठा hinic_hwअगर *hwअगर,
		  काष्ठा hinic_wq *wq, काष्ठा msix_entry *entry,
		  व्योम *ci_addr, dma_addr_t ci_dma_addr,
		  व्योम __iomem *db_base)
अणु
	sq->hwअगर = hwअगर;

	sq->wq = wq;

	sq->irq = entry->vector;
	sq->msix_entry = entry->entry;

	sq->hw_ci_addr = ci_addr;
	sq->hw_ci_dma_addr = ci_dma_addr;

	sq->db_base = db_base + SQ_DB_OFF;

	वापस alloc_sq_skb_arr(sq);
पूर्ण

/**
 * hinic_clean_sq - Clean HW Send Queue's Resources
 * @sq: Send Queue
 **/
व्योम hinic_clean_sq(काष्ठा hinic_sq *sq)
अणु
	मुक्त_sq_skb_arr(sq);
पूर्ण

/**
 * alloc_rq_cqe - allocate rq completion queue elements
 * @rq: HW Receive Queue
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक alloc_rq_cqe(काष्ठा hinic_rq *rq)
अणु
	काष्ठा hinic_hwअगर *hwअगर = rq->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	माप_प्रकार cqe_dma_size, cqe_size;
	काष्ठा hinic_wq *wq = rq->wq;
	पूर्णांक j, i;

	cqe_size = wq->q_depth * माप(*rq->cqe);
	rq->cqe = vzalloc(cqe_size);
	अगर (!rq->cqe)
		वापस -ENOMEM;

	cqe_dma_size = wq->q_depth * माप(*rq->cqe_dma);
	rq->cqe_dma = vzalloc(cqe_dma_size);
	अगर (!rq->cqe_dma)
		जाओ err_cqe_dma_arr_alloc;

	क्रम (i = 0; i < wq->q_depth; i++) अणु
		rq->cqe[i] = dma_alloc_coherent(&pdev->dev,
						माप(*rq->cqe[i]),
						&rq->cqe_dma[i], GFP_KERNEL);
		अगर (!rq->cqe[i])
			जाओ err_cqe_alloc;
	पूर्ण

	वापस 0;

err_cqe_alloc:
	क्रम (j = 0; j < i; j++)
		dma_मुक्त_coherent(&pdev->dev, माप(*rq->cqe[j]), rq->cqe[j],
				  rq->cqe_dma[j]);

	vमुक्त(rq->cqe_dma);

err_cqe_dma_arr_alloc:
	vमुक्त(rq->cqe);
	वापस -ENOMEM;
पूर्ण

/**
 * मुक्त_rq_cqe - मुक्त rq completion queue elements
 * @rq: HW Receive Queue
 **/
अटल व्योम मुक्त_rq_cqe(काष्ठा hinic_rq *rq)
अणु
	काष्ठा hinic_hwअगर *hwअगर = rq->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_wq *wq = rq->wq;
	पूर्णांक i;

	क्रम (i = 0; i < wq->q_depth; i++)
		dma_मुक्त_coherent(&pdev->dev, माप(*rq->cqe[i]), rq->cqe[i],
				  rq->cqe_dma[i]);

	vमुक्त(rq->cqe_dma);
	vमुक्त(rq->cqe);
पूर्ण

/**
 * hinic_init_rq - Initialize HW Receive Queue
 * @rq: HW Receive Queue
 * @hwअगर: HW Interface क्रम accessing HW
 * @wq: Work Queue क्रम the data of the RQ
 * @entry: msix entry क्रम rq
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_init_rq(काष्ठा hinic_rq *rq, काष्ठा hinic_hwअगर *hwअगर,
		  काष्ठा hinic_wq *wq, काष्ठा msix_entry *entry)
अणु
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	माप_प्रकार pi_size;
	पूर्णांक err;

	rq->hwअगर = hwअगर;

	rq->wq = wq;

	rq->irq = entry->vector;
	rq->msix_entry = entry->entry;

	rq->buf_sz = HINIC_RX_BUF_SZ;

	err = alloc_rq_skb_arr(rq);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate rq priv data\n");
		वापस err;
	पूर्ण

	err = alloc_rq_cqe(rq);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate rq cqe\n");
		जाओ err_alloc_rq_cqe;
	पूर्ण

	/* HW requirements: Must be at least 32 bit */
	pi_size = ALIGN(माप(*rq->pi_virt_addr), माप(u32));
	rq->pi_virt_addr = dma_alloc_coherent(&pdev->dev, pi_size,
					      &rq->pi_dma_addr, GFP_KERNEL);
	अगर (!rq->pi_virt_addr) अणु
		err = -ENOMEM;
		जाओ err_pi_virt;
	पूर्ण

	वापस 0;

err_pi_virt:
	मुक्त_rq_cqe(rq);

err_alloc_rq_cqe:
	मुक्त_rq_skb_arr(rq);
	वापस err;
पूर्ण

/**
 * hinic_clean_rq - Clean HW Receive Queue's Resources
 * @rq: HW Receive Queue
 **/
व्योम hinic_clean_rq(काष्ठा hinic_rq *rq)
अणु
	काष्ठा hinic_hwअगर *hwअगर = rq->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	माप_प्रकार pi_size;

	pi_size = ALIGN(माप(*rq->pi_virt_addr), माप(u32));
	dma_मुक्त_coherent(&pdev->dev, pi_size, rq->pi_virt_addr,
			  rq->pi_dma_addr);

	मुक्त_rq_cqe(rq);
	मुक्त_rq_skb_arr(rq);
पूर्ण

/**
 * hinic_get_sq_मुक्त_wqebbs - वापस number of मुक्त wqebbs क्रम use
 * @sq: send queue
 *
 * Return number of मुक्त wqebbs
 **/
पूर्णांक hinic_get_sq_मुक्त_wqebbs(काष्ठा hinic_sq *sq)
अणु
	काष्ठा hinic_wq *wq = sq->wq;

	वापस atomic_पढ़ो(&wq->delta) - 1;
पूर्ण

/**
 * hinic_get_rq_मुक्त_wqebbs - वापस number of मुक्त wqebbs क्रम use
 * @rq: recv queue
 *
 * Return number of मुक्त wqebbs
 **/
पूर्णांक hinic_get_rq_मुक्त_wqebbs(काष्ठा hinic_rq *rq)
अणु
	काष्ठा hinic_wq *wq = rq->wq;

	वापस atomic_पढ़ो(&wq->delta) - 1;
पूर्ण

अटल व्योम sq_prepare_ctrl(काष्ठा hinic_sq_ctrl *ctrl, u16 prod_idx,
			    पूर्णांक nr_descs)
अणु
	u32 ctrl_size, task_size, bufdesc_size;

	ctrl_size = SIZE_8BYTES(माप(काष्ठा hinic_sq_ctrl));
	task_size = SIZE_8BYTES(माप(काष्ठा hinic_sq_task));
	bufdesc_size = nr_descs * माप(काष्ठा hinic_sq_bufdesc);
	bufdesc_size = SIZE_8BYTES(bufdesc_size);

	ctrl->ctrl_info = HINIC_SQ_CTRL_SET(bufdesc_size, BUFDESC_SECT_LEN) |
			  HINIC_SQ_CTRL_SET(task_size, TASKSECT_LEN)        |
			  HINIC_SQ_CTRL_SET(SQ_NORMAL_WQE, DATA_FORMAT)     |
			  HINIC_SQ_CTRL_SET(ctrl_size, LEN);

	ctrl->queue_info = HINIC_SQ_CTRL_SET(HINIC_MSS_DEFAULT,
					     QUEUE_INFO_MSS) |
			   HINIC_SQ_CTRL_SET(1, QUEUE_INFO_UC);
पूर्ण

अटल व्योम sq_prepare_task(काष्ठा hinic_sq_task *task)
अणु
	task->pkt_info0 = 0;
	task->pkt_info1 = 0;
	task->pkt_info2 = 0;

	task->ufo_v6_identअगरy = 0;

	task->pkt_info4 = HINIC_SQ_TASK_INFO4_SET(HINIC_L2TYPE_ETH, L2TYPE);

	task->zero_pad = 0;
पूर्ण

व्योम hinic_task_set_l2hdr(काष्ठा hinic_sq_task *task, u32 len)
अणु
	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(len, L2HDR_LEN);
पूर्ण

व्योम hinic_task_set_outter_l3(काष्ठा hinic_sq_task *task,
			      क्रमागत hinic_l3_offload_type l3_type,
			      u32 network_len)
अणु
	task->pkt_info2 |= HINIC_SQ_TASK_INFO2_SET(l3_type, OUTER_L3TYPE) |
			   HINIC_SQ_TASK_INFO2_SET(network_len, OUTER_L3LEN);
पूर्ण

व्योम hinic_task_set_inner_l3(काष्ठा hinic_sq_task *task,
			     क्रमागत hinic_l3_offload_type l3_type,
			     u32 network_len)
अणु
	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(l3_type, INNER_L3TYPE);
	task->pkt_info1 |= HINIC_SQ_TASK_INFO1_SET(network_len, INNER_L3LEN);
पूर्ण

व्योम hinic_task_set_tunnel_l4(काष्ठा hinic_sq_task *task,
			      क्रमागत hinic_l4_tunnel_type l4_type,
			      u32 tunnel_len)
अणु
	task->pkt_info2 |= HINIC_SQ_TASK_INFO2_SET(l4_type, TUNNEL_L4TYPE) |
			   HINIC_SQ_TASK_INFO2_SET(tunnel_len, TUNNEL_L4LEN);
पूर्ण

व्योम hinic_set_cs_inner_l4(काष्ठा hinic_sq_task *task, u32 *queue_info,
			   क्रमागत hinic_l4_offload_type l4_offload,
			   u32 l4_len, u32 offset)
अणु
	u32 tcp_udp_cs = 0, sctp = 0;
	u32 mss = HINIC_MSS_DEFAULT;

	अगर (l4_offload == TCP_OFFLOAD_ENABLE ||
	    l4_offload == UDP_OFFLOAD_ENABLE)
		tcp_udp_cs = 1;
	अन्यथा अगर (l4_offload == SCTP_OFFLOAD_ENABLE)
		sctp = 1;

	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(l4_offload, L4_OFFLOAD);
	task->pkt_info1 |= HINIC_SQ_TASK_INFO1_SET(l4_len, INNER_L4LEN);

	*queue_info |= HINIC_SQ_CTRL_SET(offset, QUEUE_INFO_PLDOFF) |
		       HINIC_SQ_CTRL_SET(tcp_udp_cs, QUEUE_INFO_TCPUDP_CS) |
		       HINIC_SQ_CTRL_SET(sctp, QUEUE_INFO_SCTP);

	*queue_info = HINIC_SQ_CTRL_CLEAR(*queue_info, QUEUE_INFO_MSS);
	*queue_info |= HINIC_SQ_CTRL_SET(mss, QUEUE_INFO_MSS);
पूर्ण

व्योम hinic_set_tso_inner_l4(काष्ठा hinic_sq_task *task, u32 *queue_info,
			    क्रमागत hinic_l4_offload_type l4_offload,
			    u32 l4_len, u32 offset, u32 ip_ident, u32 mss)
अणु
	u32 tso = 0, ufo = 0;

	अगर (l4_offload == TCP_OFFLOAD_ENABLE)
		tso = 1;
	अन्यथा अगर (l4_offload == UDP_OFFLOAD_ENABLE)
		ufo = 1;

	task->ufo_v6_identअगरy = ip_ident;

	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(l4_offload, L4_OFFLOAD);
	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(tso || ufo, TSO_FLAG);
	task->pkt_info1 |= HINIC_SQ_TASK_INFO1_SET(l4_len, INNER_L4LEN);

	*queue_info |= HINIC_SQ_CTRL_SET(offset, QUEUE_INFO_PLDOFF) |
		       HINIC_SQ_CTRL_SET(tso, QUEUE_INFO_TSO) |
		       HINIC_SQ_CTRL_SET(ufo, QUEUE_INFO_UFO) |
		       HINIC_SQ_CTRL_SET(!!l4_offload, QUEUE_INFO_TCPUDP_CS);

	/* set MSS value */
	*queue_info = HINIC_SQ_CTRL_CLEAR(*queue_info, QUEUE_INFO_MSS);
	*queue_info |= HINIC_SQ_CTRL_SET(mss, QUEUE_INFO_MSS);
पूर्ण

/**
 * hinic_sq_prepare_wqe - prepare wqe beक्रमe insert to the queue
 * @sq: send queue
 * @prod_idx: pi value
 * @sq_wqe: wqe to prepare
 * @sges: sges क्रम use by the wqe क्रम send क्रम buf addresses
 * @nr_sges: number of sges
 **/
व्योम hinic_sq_prepare_wqe(काष्ठा hinic_sq *sq, u16 prod_idx,
			  काष्ठा hinic_sq_wqe *sq_wqe, काष्ठा hinic_sge *sges,
			  पूर्णांक nr_sges)
अणु
	पूर्णांक i;

	sq_prepare_ctrl(&sq_wqe->ctrl, prod_idx, nr_sges);

	sq_prepare_task(&sq_wqe->task);

	क्रम (i = 0; i < nr_sges; i++)
		sq_wqe->buf_descs[i].sge = sges[i];
पूर्ण

/**
 * sq_prepare_db - prepare करोorbell to ग_लिखो
 * @sq: send queue
 * @prod_idx: pi value क्रम the करोorbell
 * @cos: cos of the करोorbell
 *
 * Return db value
 **/
अटल u32 sq_prepare_db(काष्ठा hinic_sq *sq, u16 prod_idx, अचिन्हित पूर्णांक cos)
अणु
	काष्ठा hinic_qp *qp = container_of(sq, काष्ठा hinic_qp, sq);
	u8 hi_prod_idx = SQ_DB_PI_HI(SQ_MASKED_IDX(sq, prod_idx));

	/* Data should be written to HW in Big Endian Format */
	वापस cpu_to_be32(HINIC_SQ_DB_INFO_SET(hi_prod_idx, PI_HI)     |
			   HINIC_SQ_DB_INFO_SET(HINIC_DB_SQ_TYPE, TYPE) |
			   HINIC_SQ_DB_INFO_SET(HINIC_DATA_PATH, PATH)  |
			   HINIC_SQ_DB_INFO_SET(cos, COS)               |
			   HINIC_SQ_DB_INFO_SET(qp->q_id, QID));
पूर्ण

/**
 * hinic_sq_ग_लिखो_db- ग_लिखो करोorbell
 * @sq: send queue
 * @prod_idx: pi value क्रम the करोorbell
 * @wqe_size: wqe size
 * @cos: cos of the wqe
 **/
व्योम hinic_sq_ग_लिखो_db(काष्ठा hinic_sq *sq, u16 prod_idx, अचिन्हित पूर्णांक wqe_size,
		       अचिन्हित पूर्णांक cos)
अणु
	काष्ठा hinic_wq *wq = sq->wq;

	/* increment prod_idx to the next */
	prod_idx += ALIGN(wqe_size, wq->wqebb_size) / wq->wqebb_size;
	prod_idx = SQ_MASKED_IDX(sq, prod_idx);

	wmb();  /* Write all beक्रमe the करोorbell */

	ग_लिखोl(sq_prepare_db(sq, prod_idx, cos), SQ_DB_ADDR(sq, prod_idx));
पूर्ण

/**
 * hinic_sq_get_wqe - get wqe ptr in the current pi and update the pi
 * @sq: sq to get wqe from
 * @wqe_size: wqe size
 * @prod_idx: वापसed pi
 *
 * Return wqe poपूर्णांकer
 **/
काष्ठा hinic_sq_wqe *hinic_sq_get_wqe(काष्ठा hinic_sq *sq,
				      अचिन्हित पूर्णांक wqe_size, u16 *prod_idx)
अणु
	काष्ठा hinic_hw_wqe *hw_wqe = hinic_get_wqe(sq->wq, wqe_size,
						    prod_idx);

	अगर (IS_ERR(hw_wqe))
		वापस शून्य;

	वापस &hw_wqe->sq_wqe;
पूर्ण

/**
 * hinic_sq_वापस_wqe - वापस the wqe to the sq
 * @sq: send queue
 * @wqe_size: the size of the wqe
 **/
व्योम hinic_sq_वापस_wqe(काष्ठा hinic_sq *sq, अचिन्हित पूर्णांक wqe_size)
अणु
	hinic_वापस_wqe(sq->wq, wqe_size);
पूर्ण

/**
 * hinic_sq_ग_लिखो_wqe - ग_लिखो the wqe to the sq
 * @sq: send queue
 * @prod_idx: pi of the wqe
 * @sq_wqe: the wqe to ग_लिखो
 * @skb: skb to save
 * @wqe_size: the size of the wqe
 **/
व्योम hinic_sq_ग_लिखो_wqe(काष्ठा hinic_sq *sq, u16 prod_idx,
			काष्ठा hinic_sq_wqe *sq_wqe,
			काष्ठा sk_buff *skb, अचिन्हित पूर्णांक wqe_size)
अणु
	काष्ठा hinic_hw_wqe *hw_wqe = (काष्ठा hinic_hw_wqe *)sq_wqe;

	sq->saved_skb[prod_idx] = skb;

	/* The data in the HW should be in Big Endian Format */
	hinic_cpu_to_be32(sq_wqe, wqe_size);

	hinic_ग_लिखो_wqe(sq->wq, hw_wqe, wqe_size);
पूर्ण

/**
 * hinic_sq_पढ़ो_wqebb - पढ़ो wqe ptr in the current ci and update the ci, the
 * wqe only have one wqebb
 * @sq: send queue
 * @skb: वापस skb that was saved
 * @wqe_size: the wqe size ptr
 * @cons_idx: consumer index of the wqe
 *
 * Return wqe in ci position
 **/
काष्ठा hinic_sq_wqe *hinic_sq_पढ़ो_wqebb(काष्ठा hinic_sq *sq,
					 काष्ठा sk_buff **skb,
					 अचिन्हित पूर्णांक *wqe_size, u16 *cons_idx)
अणु
	काष्ठा hinic_hw_wqe *hw_wqe;
	काष्ठा hinic_sq_wqe *sq_wqe;
	काष्ठा hinic_sq_ctrl *ctrl;
	अचिन्हित पूर्णांक buf_sect_len;
	u32 ctrl_info;

	/* पढ़ो the ctrl section क्रम getting wqe size */
	hw_wqe = hinic_पढ़ो_wqe(sq->wq, माप(*ctrl), cons_idx);
	अगर (IS_ERR(hw_wqe))
		वापस शून्य;

	*skb = sq->saved_skb[*cons_idx];

	sq_wqe = &hw_wqe->sq_wqe;
	ctrl = &sq_wqe->ctrl;
	ctrl_info = be32_to_cpu(ctrl->ctrl_info);
	buf_sect_len = HINIC_SQ_CTRL_GET(ctrl_info, BUFDESC_SECT_LEN);

	*wqe_size = माप(*ctrl) + माप(sq_wqe->task);
	*wqe_size += SECT_SIZE_FROM_8BYTES(buf_sect_len);
	*wqe_size = ALIGN(*wqe_size, sq->wq->wqebb_size);

	वापस &hw_wqe->sq_wqe;
पूर्ण

/**
 * hinic_sq_पढ़ो_wqe - पढ़ो wqe ptr in the current ci and update the ci
 * @sq: send queue
 * @skb: वापस skb that was saved
 * @wqe_size: the size of the wqe
 * @cons_idx: consumer index of the wqe
 *
 * Return wqe in ci position
 **/
काष्ठा hinic_sq_wqe *hinic_sq_पढ़ो_wqe(काष्ठा hinic_sq *sq,
				       काष्ठा sk_buff **skb,
				       अचिन्हित पूर्णांक wqe_size, u16 *cons_idx)
अणु
	काष्ठा hinic_hw_wqe *hw_wqe;

	hw_wqe = hinic_पढ़ो_wqe(sq->wq, wqe_size, cons_idx);
	*skb = sq->saved_skb[*cons_idx];

	वापस &hw_wqe->sq_wqe;
पूर्ण

/**
 * hinic_sq_put_wqe - release the ci क्रम new wqes
 * @sq: send queue
 * @wqe_size: the size of the wqe
 **/
व्योम hinic_sq_put_wqe(काष्ठा hinic_sq *sq, अचिन्हित पूर्णांक wqe_size)
अणु
	hinic_put_wqe(sq->wq, wqe_size);
पूर्ण

/**
 * hinic_sq_get_sges - get sges from the wqe
 * @sq_wqe: wqe to get the sges from its buffer addresses
 * @sges: वापसed sges
 * @nr_sges: number sges to वापस
 **/
व्योम hinic_sq_get_sges(काष्ठा hinic_sq_wqe *sq_wqe, काष्ठा hinic_sge *sges,
		       पूर्णांक nr_sges)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_sges && i < HINIC_MAX_SQ_BUFDESCS; i++) अणु
		sges[i] = sq_wqe->buf_descs[i].sge;
		hinic_be32_to_cpu(&sges[i], माप(sges[i]));
	पूर्ण
पूर्ण

/**
 * hinic_rq_get_wqe - get wqe ptr in the current pi and update the pi
 * @rq: rq to get wqe from
 * @wqe_size: wqe size
 * @prod_idx: वापसed pi
 *
 * Return wqe poपूर्णांकer
 **/
काष्ठा hinic_rq_wqe *hinic_rq_get_wqe(काष्ठा hinic_rq *rq,
				      अचिन्हित पूर्णांक wqe_size, u16 *prod_idx)
अणु
	काष्ठा hinic_hw_wqe *hw_wqe = hinic_get_wqe(rq->wq, wqe_size,
						    prod_idx);

	अगर (IS_ERR(hw_wqe))
		वापस शून्य;

	वापस &hw_wqe->rq_wqe;
पूर्ण

/**
 * hinic_rq_ग_लिखो_wqe - ग_लिखो the wqe to the rq
 * @rq: recv queue
 * @prod_idx: pi of the wqe
 * @rq_wqe: the wqe to ग_लिखो
 * @skb: skb to save
 **/
व्योम hinic_rq_ग_लिखो_wqe(काष्ठा hinic_rq *rq, u16 prod_idx,
			काष्ठा hinic_rq_wqe *rq_wqe, काष्ठा sk_buff *skb)
अणु
	काष्ठा hinic_hw_wqe *hw_wqe = (काष्ठा hinic_hw_wqe *)rq_wqe;

	rq->saved_skb[prod_idx] = skb;

	/* The data in the HW should be in Big Endian Format */
	hinic_cpu_to_be32(rq_wqe, माप(*rq_wqe));

	hinic_ग_लिखो_wqe(rq->wq, hw_wqe, माप(*rq_wqe));
पूर्ण

/**
 * hinic_rq_पढ़ो_wqe - पढ़ो wqe ptr in the current ci and update the ci
 * @rq: recv queue
 * @wqe_size: the size of the wqe
 * @skb: वापस saved skb
 * @cons_idx: consumer index of the wqe
 *
 * Return wqe in ci position
 **/
काष्ठा hinic_rq_wqe *hinic_rq_पढ़ो_wqe(काष्ठा hinic_rq *rq,
				       अचिन्हित पूर्णांक wqe_size,
				       काष्ठा sk_buff **skb, u16 *cons_idx)
अणु
	काष्ठा hinic_hw_wqe *hw_wqe;
	काष्ठा hinic_rq_cqe *cqe;
	पूर्णांक rx_करोne;
	u32 status;

	hw_wqe = hinic_पढ़ो_wqe(rq->wq, wqe_size, cons_idx);
	अगर (IS_ERR(hw_wqe))
		वापस शून्य;

	cqe = rq->cqe[*cons_idx];

	status = be32_to_cpu(cqe->status);

	rx_करोne = HINIC_RQ_CQE_STATUS_GET(status, RXDONE);
	अगर (!rx_करोne)
		वापस शून्य;

	*skb = rq->saved_skb[*cons_idx];

	वापस &hw_wqe->rq_wqe;
पूर्ण

/**
 * hinic_rq_पढ़ो_next_wqe - increment ci and पढ़ो the wqe in ci position
 * @rq: recv queue
 * @wqe_size: the size of the wqe
 * @skb: वापस saved skb
 * @cons_idx: consumer index in the wq
 *
 * Return wqe in incremented ci position
 **/
काष्ठा hinic_rq_wqe *hinic_rq_पढ़ो_next_wqe(काष्ठा hinic_rq *rq,
					    अचिन्हित पूर्णांक wqe_size,
					    काष्ठा sk_buff **skb,
					    u16 *cons_idx)
अणु
	काष्ठा hinic_wq *wq = rq->wq;
	काष्ठा hinic_hw_wqe *hw_wqe;
	अचिन्हित पूर्णांक num_wqebbs;

	wqe_size = ALIGN(wqe_size, wq->wqebb_size);
	num_wqebbs = wqe_size / wq->wqebb_size;

	*cons_idx = RQ_MASKED_IDX(rq, *cons_idx + num_wqebbs);

	*skb = rq->saved_skb[*cons_idx];

	hw_wqe = hinic_पढ़ो_wqe_direct(wq, *cons_idx);

	वापस &hw_wqe->rq_wqe;
पूर्ण

/**
 * hinic_put_wqe - release the ci क्रम new wqes
 * @rq: recv queue
 * @cons_idx: consumer index of the wqe
 * @wqe_size: the size of the wqe
 **/
व्योम hinic_rq_put_wqe(काष्ठा hinic_rq *rq, u16 cons_idx,
		      अचिन्हित पूर्णांक wqe_size)
अणु
	काष्ठा hinic_rq_cqe *cqe = rq->cqe[cons_idx];
	u32 status = be32_to_cpu(cqe->status);

	status = HINIC_RQ_CQE_STATUS_CLEAR(status, RXDONE);

	/* Rx WQE size is 1 WQEBB, no wq shaकरोw*/
	cqe->status = cpu_to_be32(status);

	wmb();          /* clear करोne flag */

	hinic_put_wqe(rq->wq, wqe_size);
पूर्ण

/**
 * hinic_rq_get_sge - get sge from the wqe
 * @rq: recv queue
 * @rq_wqe: wqe to get the sge from its buf address
 * @cons_idx: consumer index
 * @sge: वापसed sge
 **/
व्योम hinic_rq_get_sge(काष्ठा hinic_rq *rq, काष्ठा hinic_rq_wqe *rq_wqe,
		      u16 cons_idx, काष्ठा hinic_sge *sge)
अणु
	काष्ठा hinic_rq_cqe *cqe = rq->cqe[cons_idx];
	u32 len = be32_to_cpu(cqe->len);

	sge->hi_addr = be32_to_cpu(rq_wqe->buf_desc.hi_addr);
	sge->lo_addr = be32_to_cpu(rq_wqe->buf_desc.lo_addr);
	sge->len = HINIC_RQ_CQE_SGE_GET(len, LEN);
पूर्ण

/**
 * hinic_rq_prepare_wqe - prepare wqe beक्रमe insert to the queue
 * @rq: recv queue
 * @prod_idx: pi value
 * @rq_wqe: the wqe
 * @sge: sge क्रम use by the wqe क्रम recv buf address
 **/
व्योम hinic_rq_prepare_wqe(काष्ठा hinic_rq *rq, u16 prod_idx,
			  काष्ठा hinic_rq_wqe *rq_wqe, काष्ठा hinic_sge *sge)
अणु
	काष्ठा hinic_rq_cqe_sect *cqe_sect = &rq_wqe->cqe_sect;
	काष्ठा hinic_rq_bufdesc *buf_desc = &rq_wqe->buf_desc;
	काष्ठा hinic_rq_cqe *cqe = rq->cqe[prod_idx];
	काष्ठा hinic_rq_ctrl *ctrl = &rq_wqe->ctrl;
	dma_addr_t cqe_dma = rq->cqe_dma[prod_idx];

	ctrl->ctrl_info =
		HINIC_RQ_CTRL_SET(SIZE_8BYTES(माप(*ctrl)), LEN) |
		HINIC_RQ_CTRL_SET(SIZE_8BYTES(माप(*cqe_sect)),
				  COMPLETE_LEN)                    |
		HINIC_RQ_CTRL_SET(SIZE_8BYTES(माप(*buf_desc)),
				  BUFDESC_SECT_LEN)                |
		HINIC_RQ_CTRL_SET(RQ_COMPLETE_SGE, COMPLETE_FORMAT);

	hinic_set_sge(&cqe_sect->sge, cqe_dma, माप(*cqe));

	buf_desc->hi_addr = sge->hi_addr;
	buf_desc->lo_addr = sge->lo_addr;
पूर्ण

/**
 * hinic_rq_update - update pi of the rq
 * @rq: recv queue
 * @prod_idx: pi value
 **/
व्योम hinic_rq_update(काष्ठा hinic_rq *rq, u16 prod_idx)
अणु
	*rq->pi_virt_addr = cpu_to_be16(RQ_MASKED_IDX(rq, prod_idx + 1));
पूर्ण
