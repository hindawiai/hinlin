<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Marvell OcteonTx2 RVU Ethernet driver
 *
 * Copyright (C) 2020 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित OTX2_TXRX_H
#घोषणा OTX2_TXRX_H

#समावेश <linux/etherdevice.h>
#समावेश <linux/iommu.h>
#समावेश <linux/अगर_vlan.h>

#घोषणा LBK_CHAN_BASE	0x000
#घोषणा SDP_CHAN_BASE	0x700
#घोषणा CGX_CHAN_BASE	0x800

#घोषणा OTX2_DATA_ALIGN(X)	ALIGN(X, OTX2_ALIGN)
#घोषणा OTX2_HEAD_ROOM		OTX2_ALIGN

#घोषणा	OTX2_ETH_HLEN		(VLAN_ETH_HLEN + VLAN_HLEN)
#घोषणा	OTX2_MIN_MTU		64

#घोषणा OTX2_MAX_GSO_SEGS	255
#घोषणा OTX2_MAX_FRAGS_IN_SQE	9

/* Rx buffer size should be in multiples of 128bytes */
#घोषणा RCV_FRAG_LEN1(x)				\
		((OTX2_HEAD_ROOM + OTX2_DATA_ALIGN(x)) + \
		OTX2_DATA_ALIGN(माप(काष्ठा skb_shared_info)))

/* Prefer 2048 byte buffers क्रम better last level cache
 * utilization or data distribution across regions.
 */
#घोषणा RCV_FRAG_LEN(x)	\
		((RCV_FRAG_LEN1(x) < 2048) ? 2048 : RCV_FRAG_LEN1(x))

#घोषणा DMA_BUFFER_LEN(x)		\
		((x) - OTX2_HEAD_ROOM - \
		OTX2_DATA_ALIGN(माप(काष्ठा skb_shared_info)))

/* IRQ triggered when NIX_LF_CINTX_CNT[ECOUNT]
 * is equal to this value.
 */
#घोषणा CQ_CQE_THRESH_DEFAULT	10

/* IRQ triggered when NIX_LF_CINTX_CNT[ECOUNT]
 * is nonzero and this much समय elapses after that.
 */
#घोषणा CQ_TIMER_THRESH_DEFAULT	1  /* 1 usec */
#घोषणा CQ_TIMER_THRESH_MAX     25 /* 25 usec */

/* Min number of CQs (of the ones mapped to this CINT)
 * with valid CQEs.
 */
#घोषणा CQ_QCOUNT_DEFAULT	1

काष्ठा queue_stats अणु
	u64	bytes;
	u64	pkts;
पूर्ण;

काष्ठा otx2_rcv_queue अणु
	काष्ठा queue_stats	stats;
पूर्ण;

काष्ठा sg_list अणु
	u16	num_segs;
	u64	skb;
	u64	size[OTX2_MAX_FRAGS_IN_SQE];
	u64	dma_addr[OTX2_MAX_FRAGS_IN_SQE];
पूर्ण;

काष्ठा otx2_snd_queue अणु
	u8			aura_id;
	u16			head;
	u16			sqe_size;
	u32			sqe_cnt;
	u16			num_sqbs;
	u16			sqe_thresh;
	u8			sqe_per_sqb;
	u64			 io_addr;
	u64			*aura_fc_addr;
	u64			*lmt_addr;
	व्योम			*sqe_base;
	काष्ठा qmem		*sqe;
	काष्ठा qmem		*tso_hdrs;
	काष्ठा sg_list		*sg;
	काष्ठा qmem		*बारtamps;
	काष्ठा queue_stats	stats;
	u16			sqb_count;
	u64			*sqb_ptrs;
पूर्ण ____cacheline_aligned_in_smp;

क्रमागत cq_type अणु
	CQ_RX,
	CQ_TX,
	CQS_PER_CINT = 2, /* RQ + SQ */
पूर्ण;

काष्ठा otx2_cq_poll अणु
	व्योम			*dev;
#घोषणा CINT_INVALID_CQ		255
	u8			cपूर्णांक_idx;
	u8			cq_ids[CQS_PER_CINT];
	काष्ठा napi_काष्ठा	napi;
पूर्ण;

काष्ठा otx2_pool अणु
	काष्ठा qmem		*stack;
	काष्ठा qmem		*fc_addr;
	u64			*lmt_addr;
	u16			rbsize;
पूर्ण;

काष्ठा otx2_cq_queue अणु
	u8			cq_idx;
	u8			cq_type;
	u8			cपूर्णांक_idx; /* CQ पूर्णांकerrupt id */
	u8			refill_task_sched;
	u16			cqe_size;
	u16			pool_ptrs;
	u32			cqe_cnt;
	u32			cq_head;
	व्योम			*cqe_base;
	काष्ठा qmem		*cqe;
	काष्ठा otx2_pool	*rbpool;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा otx2_qset अणु
	u32			rqe_cnt;
	u32			sqe_cnt; /* Keep these two at top */
#घोषणा OTX2_MAX_CQ_CNT		64
	u16			cq_cnt;
	u16			xqe_size;
	काष्ठा otx2_pool	*pool;
	काष्ठा otx2_cq_poll	*napi;
	काष्ठा otx2_cq_queue	*cq;
	काष्ठा otx2_snd_queue	*sq;
	काष्ठा otx2_rcv_queue	*rq;
पूर्ण;

/* Translate IOVA to physical address */
अटल अंतरभूत u64 otx2_iova_to_phys(व्योम *iommu_करोमुख्य, dma_addr_t dma_addr)
अणु
	/* Translation is installed only when IOMMU is present */
	अगर (likely(iommu_करोमुख्य))
		वापस iommu_iova_to_phys(iommu_करोमुख्य, dma_addr);
	वापस dma_addr;
पूर्ण

पूर्णांक otx2_napi_handler(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
bool otx2_sq_append_skb(काष्ठा net_device *netdev, काष्ठा otx2_snd_queue *sq,
			काष्ठा sk_buff *skb, u16 qidx);
व्योम cn10k_sqe_flush(व्योम *dev, काष्ठा otx2_snd_queue *sq,
		     पूर्णांक size, पूर्णांक qidx);
व्योम otx2_sqe_flush(व्योम *dev, काष्ठा otx2_snd_queue *sq,
		    पूर्णांक size, पूर्णांक qidx);
व्योम otx2_refill_pool_ptrs(व्योम *dev, काष्ठा otx2_cq_queue *cq);
व्योम cn10k_refill_pool_ptrs(व्योम *dev, काष्ठा otx2_cq_queue *cq);
#पूर्ण_अगर /* OTX2_TXRX_H */
