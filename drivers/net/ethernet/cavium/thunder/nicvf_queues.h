<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Cavium, Inc.
 */

#अगर_अघोषित NICVF_QUEUES_H
#घोषणा NICVF_QUEUES_H

#समावेश <linux/netdevice.h>
#समावेश <linux/iommu.h>
#समावेश <net/xdp.h>
#समावेश "q_struct.h"

#घोषणा MAX_QUEUE_SET			128
#घोषणा MAX_RCV_QUEUES_PER_QS		8
#घोषणा MAX_RCV_BUF_DESC_RINGS_PER_QS	2
#घोषणा MAX_SND_QUEUES_PER_QS		8
#घोषणा MAX_CMP_QUEUES_PER_QS		8

/* VF's queue पूर्णांकerrupt ranges */
#घोषणा	NICVF_INTR_ID_CQ		0
#घोषणा	NICVF_INTR_ID_SQ		8
#घोषणा	NICVF_INTR_ID_RBDR		16
#घोषणा	NICVF_INTR_ID_MISC		18
#घोषणा	NICVF_INTR_ID_QS_ERR		19

#घोषणा	क्रम_each_cq_irq(irq)	\
	क्रम (irq = NICVF_INTR_ID_CQ; irq < NICVF_INTR_ID_SQ; irq++)
#घोषणा	क्रम_each_sq_irq(irq)	\
	क्रम (irq = NICVF_INTR_ID_SQ; irq < NICVF_INTR_ID_RBDR; irq++)
#घोषणा	क्रम_each_rbdr_irq(irq)	\
	क्रम (irq = NICVF_INTR_ID_RBDR; irq < NICVF_INTR_ID_MISC; irq++)

#घोषणा RBDR_SIZE0		0ULL /* 8K entries */
#घोषणा RBDR_SIZE1		1ULL /* 16K entries */
#घोषणा RBDR_SIZE2		2ULL /* 32K entries */
#घोषणा RBDR_SIZE3		3ULL /* 64K entries */
#घोषणा RBDR_SIZE4		4ULL /* 126K entries */
#घोषणा RBDR_SIZE5		5ULL /* 256K entries */
#घोषणा RBDR_SIZE6		6ULL /* 512K entries */

#घोषणा SND_QUEUE_SIZE0		0ULL /* 1K entries */
#घोषणा SND_QUEUE_SIZE1		1ULL /* 2K entries */
#घोषणा SND_QUEUE_SIZE2		2ULL /* 4K entries */
#घोषणा SND_QUEUE_SIZE3		3ULL /* 8K entries */
#घोषणा SND_QUEUE_SIZE4		4ULL /* 16K entries */
#घोषणा SND_QUEUE_SIZE5		5ULL /* 32K entries */
#घोषणा SND_QUEUE_SIZE6		6ULL /* 64K entries */

#घोषणा CMP_QUEUE_SIZE0		0ULL /* 1K entries */
#घोषणा CMP_QUEUE_SIZE1		1ULL /* 2K entries */
#घोषणा CMP_QUEUE_SIZE2		2ULL /* 4K entries */
#घोषणा CMP_QUEUE_SIZE3		3ULL /* 8K entries */
#घोषणा CMP_QUEUE_SIZE4		4ULL /* 16K entries */
#घोषणा CMP_QUEUE_SIZE5		5ULL /* 32K entries */
#घोषणा CMP_QUEUE_SIZE6		6ULL /* 64K entries */

/* Default queue count per QS, its lengths and threshold values */
#घोषणा DEFAULT_RBDR_CNT	1

#घोषणा SND_QSIZE		SND_QUEUE_SIZE0
#घोषणा SND_QUEUE_LEN		(1ULL << (SND_QSIZE + 10))
#घोषणा MIN_SND_QUEUE_LEN	(1ULL << (SND_QUEUE_SIZE0 + 10))
#घोषणा MAX_SND_QUEUE_LEN	(1ULL << (SND_QUEUE_SIZE6 + 10))
#घोषणा SND_QUEUE_THRESH	2ULL
#घोषणा MIN_SQ_DESC_PER_PKT_XMIT	2
/* Since बारtamp not enabled, otherwise 2 */
#घोषणा MAX_CQE_PER_PKT_XMIT		1

/* Keep CQ and SQ sizes same, अगर बारtamping
 * is enabled this equation will change.
 */
#घोषणा CMP_QSIZE		CMP_QUEUE_SIZE0
#घोषणा CMP_QUEUE_LEN		(1ULL << (CMP_QSIZE + 10))
#घोषणा MIN_CMP_QUEUE_LEN	(1ULL << (CMP_QUEUE_SIZE0 + 10))
#घोषणा MAX_CMP_QUEUE_LEN	(1ULL << (CMP_QUEUE_SIZE6 + 10))
#घोषणा CMP_QUEUE_CQE_THRESH	(NAPI_POLL_WEIGHT / 2)
#घोषणा CMP_QUEUE_TIMER_THRESH	80 /* ~2usec */

/* No of CQEs that might anyway माला_लो used by HW due to pipelining
 * effects irrespective of PASS/DROP/LEVELS being configured
 */
#घोषणा CMP_QUEUE_PIPELINE_RSVD 544

#घोषणा RBDR_SIZE		RBDR_SIZE0
#घोषणा RCV_BUF_COUNT		(1ULL << (RBDR_SIZE + 13))
#घोषणा MAX_RCV_BUF_COUNT	(1ULL << (RBDR_SIZE6 + 13))
#घोषणा RBDR_THRESH		(RCV_BUF_COUNT / 2)
#घोषणा DMA_BUFFER_LEN		1536 /* In multiples of 128bytes */
#घोषणा RCV_FRAG_LEN	 (SKB_DATA_ALIGN(DMA_BUFFER_LEN + NET_SKB_PAD) + \
			 SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))

#घोषणा MAX_CQES_FOR_TX		((SND_QUEUE_LEN / MIN_SQ_DESC_PER_PKT_XMIT) * \
				 MAX_CQE_PER_PKT_XMIT)

/* RED and Backpressure levels of CQ क्रम pkt reception
 * For CQ, level is a measure of emptiness i.e 0x0 means full
 * eg: For CQ of size 4K, and क्रम pass/drop levels of 160/144
 * HW accepts pkt अगर unused CQE >= 2560
 * RED accepts pkt अगर unused CQE < 2304 & >= 2560
 * DROPs pkts अगर unused CQE < 2304
 */
#घोषणा RQ_PASS_CQ_LVL         224ULL
#घोषणा RQ_DROP_CQ_LVL         216ULL

/* RED and Backpressure levels of RBDR क्रम pkt reception
 * For RBDR, level is a measure of fullness i.e 0x0 means empty
 * eg: For RBDR of size 8K, and क्रम pass/drop levels of 4/0
 * HW accepts pkt अगर unused RBs >= 256
 * RED accepts pkt अगर unused RBs < 256 & >= 0
 * DROPs pkts अगर unused RBs < 0
 */
#घोषणा RQ_PASS_RBDR_LVL	8ULL
#घोषणा RQ_DROP_RBDR_LVL	0ULL

/* Descriptor size in bytes */
#घोषणा SND_QUEUE_DESC_SIZE	16
#घोषणा CMP_QUEUE_DESC_SIZE	512

/* Buffer / descriptor alignments */
#घोषणा NICVF_RCV_BUF_ALIGN		7
#घोषणा NICVF_RCV_BUF_ALIGN_BYTES	(1ULL << NICVF_RCV_BUF_ALIGN)
#घोषणा NICVF_CQ_BASE_ALIGN_BYTES	512  /* 9 bits */
#घोषणा NICVF_SQ_BASE_ALIGN_BYTES	128  /* 7 bits */

#घोषणा NICVF_ALIGNED_ADDR(ADDR, ALIGN_BYTES)	ALIGN(ADDR, ALIGN_BYTES)

/* Queue enable/disable */
#घोषणा NICVF_SQ_EN		BIT_ULL(19)

/* Queue reset */
#घोषणा NICVF_CQ_RESET		BIT_ULL(41)
#घोषणा NICVF_SQ_RESET		BIT_ULL(17)
#घोषणा NICVF_RBDR_RESET	BIT_ULL(43)

क्रमागत CQ_RX_ERRLVL_E अणु
	CQ_ERRLVL_MAC,
	CQ_ERRLVL_L2,
	CQ_ERRLVL_L3,
	CQ_ERRLVL_L4,
पूर्ण;

क्रमागत CQ_RX_ERROP_E अणु
	CQ_RX_ERROP_RE_NONE = 0x0,
	CQ_RX_ERROP_RE_PARTIAL = 0x1,
	CQ_RX_ERROP_RE_JABBER = 0x2,
	CQ_RX_ERROP_RE_FCS = 0x7,
	CQ_RX_ERROP_RE_TERMINATE = 0x9,
	CQ_RX_ERROP_RE_RX_CTL = 0xb,
	CQ_RX_ERROP_PREL2_ERR = 0x1f,
	CQ_RX_ERROP_L2_FRAGMENT = 0x20,
	CQ_RX_ERROP_L2_OVERRUN = 0x21,
	CQ_RX_ERROP_L2_PFCS = 0x22,
	CQ_RX_ERROP_L2_PUNY = 0x23,
	CQ_RX_ERROP_L2_MAL = 0x24,
	CQ_RX_ERROP_L2_OVERSIZE = 0x25,
	CQ_RX_ERROP_L2_UNDERSIZE = 0x26,
	CQ_RX_ERROP_L2_LENMISM = 0x27,
	CQ_RX_ERROP_L2_PCLP = 0x28,
	CQ_RX_ERROP_IP_NOT = 0x41,
	CQ_RX_ERROP_IP_CSUM_ERR = 0x42,
	CQ_RX_ERROP_IP_MAL = 0x43,
	CQ_RX_ERROP_IP_MALD = 0x44,
	CQ_RX_ERROP_IP_HOP = 0x45,
	CQ_RX_ERROP_L3_ICRC = 0x46,
	CQ_RX_ERROP_L3_PCLP = 0x47,
	CQ_RX_ERROP_L4_MAL = 0x61,
	CQ_RX_ERROP_L4_CHK = 0x62,
	CQ_RX_ERROP_UDP_LEN = 0x63,
	CQ_RX_ERROP_L4_PORT = 0x64,
	CQ_RX_ERROP_TCP_FLAG = 0x65,
	CQ_RX_ERROP_TCP_OFFSET = 0x66,
	CQ_RX_ERROP_L4_PCLP = 0x67,
	CQ_RX_ERROP_RBDR_TRUNC = 0x70,
पूर्ण;

क्रमागत CQ_TX_ERROP_E अणु
	CQ_TX_ERROP_GOOD = 0x0,
	CQ_TX_ERROP_DESC_FAULT = 0x10,
	CQ_TX_ERROP_HDR_CONS_ERR = 0x11,
	CQ_TX_ERROP_SUBDC_ERR = 0x12,
	CQ_TX_ERROP_MAX_SIZE_VIOL = 0x13,
	CQ_TX_ERROP_IMM_SIZE_OFLOW = 0x80,
	CQ_TX_ERROP_DATA_SEQUENCE_ERR = 0x81,
	CQ_TX_ERROP_MEM_SEQUENCE_ERR = 0x82,
	CQ_TX_ERROP_LOCK_VIOL = 0x83,
	CQ_TX_ERROP_DATA_FAULT = 0x84,
	CQ_TX_ERROP_TSTMP_CONFLICT = 0x85,
	CQ_TX_ERROP_TSTMP_TIMEOUT = 0x86,
	CQ_TX_ERROP_MEM_FAULT = 0x87,
	CQ_TX_ERROP_CK_OVERLAP = 0x88,
	CQ_TX_ERROP_CK_OFLOW = 0x89,
	CQ_TX_ERROP_ENUM_LAST = 0x8a,
पूर्ण;

क्रमागत RQ_SQ_STATS अणु
	RQ_SQ_STATS_OCTS,
	RQ_SQ_STATS_PKTS,
पूर्ण;

काष्ठा rx_tx_queue_stats अणु
	u64	bytes;
	u64	pkts;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा q_desc_mem अणु
	dma_addr_t	dma;
	u64		size;
	u32		q_len;
	dma_addr_t	phys_base;
	व्योम		*base;
	व्योम		*unalign_base;
पूर्ण;

काष्ठा pgcache अणु
	काष्ठा page	*page;
	पूर्णांक		ref_count;
	u64		dma_addr;
पूर्ण;

काष्ठा rbdr अणु
	bool		enable;
	u32		dma_size;
	u32		frag_len;
	u32		thresh;		/* Threshold level क्रम पूर्णांकerrupt */
	व्योम		*desc;
	u32		head;
	u32		tail;
	काष्ठा q_desc_mem   dmem;
	bool		is_xdp;

	/* For page recycling */
	पूर्णांक		pgidx;
	पूर्णांक		pgcnt;
	पूर्णांक		pgalloc;
	काष्ठा pgcache	*pgcache;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा rcv_queue अणु
	bool		enable;
	काष्ठा	rbdr	*rbdr_start;
	काष्ठा	rbdr	*rbdr_cont;
	bool		en_tcp_reassembly;
	u8		cq_qs;  /* CQ's QS to which this RQ is asचिन्हित */
	u8		cq_idx; /* CQ index (0 to 7) in the QS */
	u8		cont_rbdr_qs;      /* Continue buffer ptrs - QS num */
	u8		cont_qs_rbdr_idx;  /* RBDR idx in the cont QS */
	u8		start_rbdr_qs;     /* First buffer ptrs - QS num */
	u8		start_qs_rbdr_idx; /* RBDR idx in the above QS */
	u8		caching;
	काष्ठा		rx_tx_queue_stats stats;
	काष्ठा xdp_rxq_info xdp_rxq;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा cmp_queue अणु
	bool		enable;
	u16		thresh;
	spinlock_t	lock;  /* lock to serialize processing CQEs */
	व्योम		*desc;
	काष्ठा q_desc_mem   dmem;
	पूर्णांक		irq;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा snd_queue अणु
	bool		enable;
	u8		cq_qs;  /* CQ's QS to which this SQ is poपूर्णांकing */
	u8		cq_idx; /* CQ index (0 to 7) in the above QS */
	u16		thresh;
	atomic_t	मुक्त_cnt;
	u32		head;
	u32		tail;
	u64		*skbuff;
	व्योम		*desc;
	u64		*xdp_page;
	u16		xdp_desc_cnt;
	u16		xdp_मुक्त_cnt;
	bool		is_xdp;

	/* For TSO segment's header */
	अक्षर		*tso_hdrs;
	dma_addr_t	tso_hdrs_phys;

	cpumask_t	affinity_mask;
	काष्ठा q_desc_mem   dmem;
	काष्ठा rx_tx_queue_stats stats;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा queue_set अणु
	bool		enable;
	bool		be_en;
	u8		vnic_id;
	u8		rq_cnt;
	u8		cq_cnt;
	u64		cq_len;
	u8		sq_cnt;
	u64		sq_len;
	u8		rbdr_cnt;
	u64		rbdr_len;
	काष्ठा	rcv_queue	rq[MAX_RCV_QUEUES_PER_QS];
	काष्ठा	cmp_queue	cq[MAX_CMP_QUEUES_PER_QS];
	काष्ठा	snd_queue	sq[MAX_SND_QUEUES_PER_QS];
	काष्ठा	rbdr		rbdr[MAX_RCV_BUF_DESC_RINGS_PER_QS];
पूर्ण ____cacheline_aligned_in_smp;

#घोषणा GET_RBDR_DESC(RING, idx)\
		(&(((काष्ठा rbdr_entry_t *)((RING)->desc))[idx]))
#घोषणा GET_SQ_DESC(RING, idx)\
		(&(((काष्ठा sq_hdr_subdesc *)((RING)->desc))[idx]))
#घोषणा GET_CQ_DESC(RING, idx)\
		(&(((जोड़ cq_desc_t *)((RING)->desc))[idx]))

/* CQ status bits */
#घोषणा	CQ_WR_FULL	BIT(26)
#घोषणा	CQ_WR_DISABLE	BIT(25)
#घोषणा	CQ_WR_FAULT	BIT(24)
#घोषणा	CQ_CQE_COUNT	(0xFFFF << 0)

#घोषणा	CQ_ERR_MASK	(CQ_WR_FULL | CQ_WR_DISABLE | CQ_WR_FAULT)

अटल अंतरभूत u64 nicvf_iova_to_phys(काष्ठा nicvf *nic, dma_addr_t dma_addr)
अणु
	/* Translation is installed only when IOMMU is present */
	अगर (nic->iommu_करोमुख्य)
		वापस iommu_iova_to_phys(nic->iommu_करोमुख्य, dma_addr);
	वापस dma_addr;
पूर्ण

व्योम nicvf_unmap_sndq_buffers(काष्ठा nicvf *nic, काष्ठा snd_queue *sq,
			      पूर्णांक hdr_sqe, u8 subdesc_cnt);
व्योम nicvf_config_vlan_stripping(काष्ठा nicvf *nic,
				 netdev_features_t features);
पूर्णांक nicvf_set_qset_resources(काष्ठा nicvf *nic);
पूर्णांक nicvf_config_data_transfer(काष्ठा nicvf *nic, bool enable);
व्योम nicvf_qset_config(काष्ठा nicvf *nic, bool enable);
व्योम nicvf_cmp_queue_config(काष्ठा nicvf *nic, काष्ठा queue_set *qs,
			    पूर्णांक qidx, bool enable);

व्योम nicvf_sq_enable(काष्ठा nicvf *nic, काष्ठा snd_queue *sq, पूर्णांक qidx);
व्योम nicvf_sq_disable(काष्ठा nicvf *nic, पूर्णांक qidx);
व्योम nicvf_put_sq_desc(काष्ठा snd_queue *sq, पूर्णांक desc_cnt);
व्योम nicvf_sq_मुक्त_used_descs(काष्ठा net_device *netdev,
			      काष्ठा snd_queue *sq, पूर्णांक qidx);
पूर्णांक nicvf_sq_append_skb(काष्ठा nicvf *nic, काष्ठा snd_queue *sq,
			काष्ठा sk_buff *skb, u8 sq_num);
पूर्णांक nicvf_xdp_sq_append_pkt(काष्ठा nicvf *nic, काष्ठा snd_queue *sq,
			    u64 bufaddr, u64 dma_addr, u16 len);
व्योम nicvf_xdp_sq_करोorbell(काष्ठा nicvf *nic, काष्ठा snd_queue *sq, पूर्णांक sq_num);

काष्ठा sk_buff *nicvf_get_rcv_skb(काष्ठा nicvf *nic,
				  काष्ठा cqe_rx_t *cqe_rx, bool xdp);
व्योम nicvf_rbdr_task(काष्ठा tasklet_काष्ठा *t);
व्योम nicvf_rbdr_work(काष्ठा work_काष्ठा *work);

व्योम nicvf_enable_पूर्णांकr(काष्ठा nicvf *nic, पूर्णांक पूर्णांक_type, पूर्णांक q_idx);
व्योम nicvf_disable_पूर्णांकr(काष्ठा nicvf *nic, पूर्णांक पूर्णांक_type, पूर्णांक q_idx);
व्योम nicvf_clear_पूर्णांकr(काष्ठा nicvf *nic, पूर्णांक पूर्णांक_type, पूर्णांक q_idx);
पूर्णांक nicvf_is_पूर्णांकr_enabled(काष्ठा nicvf *nic, पूर्णांक पूर्णांक_type, पूर्णांक q_idx);

/* Register access APIs */
व्योम nicvf_reg_ग_लिखो(काष्ठा nicvf *nic, u64 offset, u64 val);
u64  nicvf_reg_पढ़ो(काष्ठा nicvf *nic, u64 offset);
व्योम nicvf_qset_reg_ग_लिखो(काष्ठा nicvf *nic, u64 offset, u64 val);
u64 nicvf_qset_reg_पढ़ो(काष्ठा nicvf *nic, u64 offset);
व्योम nicvf_queue_reg_ग_लिखो(काष्ठा nicvf *nic, u64 offset,
			   u64 qidx, u64 val);
u64  nicvf_queue_reg_पढ़ो(काष्ठा nicvf *nic,
			  u64 offset, u64 qidx);

/* Stats */
व्योम nicvf_update_rq_stats(काष्ठा nicvf *nic, पूर्णांक rq_idx);
व्योम nicvf_update_sq_stats(काष्ठा nicvf *nic, पूर्णांक sq_idx);
पूर्णांक nicvf_check_cqe_rx_errs(काष्ठा nicvf *nic, काष्ठा cqe_rx_t *cqe_rx);
पूर्णांक nicvf_check_cqe_tx_errs(काष्ठा nicvf *nic, काष्ठा cqe_send_t *cqe_tx);
#पूर्ण_अगर /* NICVF_QUEUES_H */
