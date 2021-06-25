<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright(c) 2016 - 2020 Intel Corporation.
 */

#अगर_अघोषित DEF_RDMAVT_INCQP_H
#घोषणा DEF_RDMAVT_INCQP_H

#समावेश <rdma/rdma_vt.h>
#समावेश <rdma/ib_pack.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdmavt_cq.h>
#समावेश <rdma/rvt-abi.h>
/*
 * Atomic bit definitions क्रम r_aflags.
 */
#घोषणा RVT_R_WRID_VALID        0
#घोषणा RVT_R_REWIND_SGE        1

/*
 * Bit definitions क्रम r_flags.
 */
#घोषणा RVT_R_REUSE_SGE 0x01
#घोषणा RVT_R_RDMAR_SEQ 0x02
#घोषणा RVT_R_RSP_NAK   0x04
#घोषणा RVT_R_RSP_SEND  0x08
#घोषणा RVT_R_COMM_EST  0x10

/*
 * If a packet's QP[23:16] bits match this value, then it is
 * a PSM packet and the hardware will expect a KDETH header
 * following the BTH.
 */
#घोषणा RVT_KDETH_QP_PREFIX       0x80
#घोषणा RVT_KDETH_QP_SUFFIX       0xffff
#घोषणा RVT_KDETH_QP_PREFIX_MASK  0x00ff0000
#घोषणा RVT_KDETH_QP_PREFIX_SHIFT 16
#घोषणा RVT_KDETH_QP_BASE         (u32)(RVT_KDETH_QP_PREFIX << \
					RVT_KDETH_QP_PREFIX_SHIFT)
#घोषणा RVT_KDETH_QP_MAX          (u32)(RVT_KDETH_QP_BASE + RVT_KDETH_QP_SUFFIX)

/*
 * If a packet's LNH == BTH and DEST QPN[23:16] in the BTH match this
 * prefix value, then it is an AIP packet with a DETH containing the entropy
 * value in byte 4 following the BTH.
 */
#घोषणा RVT_AIP_QP_PREFIX       0x81
#घोषणा RVT_AIP_QP_SUFFIX       0xffff
#घोषणा RVT_AIP_QP_PREFIX_MASK  0x00ff0000
#घोषणा RVT_AIP_QP_PREFIX_SHIFT 16
#घोषणा RVT_AIP_QP_BASE         (u32)(RVT_AIP_QP_PREFIX << \
				      RVT_AIP_QP_PREFIX_SHIFT)
#घोषणा RVT_AIP_QPN_MAX         BIT(RVT_AIP_QP_PREFIX_SHIFT)
#घोषणा RVT_AIP_QP_MAX          (u32)(RVT_AIP_QP_BASE + RVT_AIP_QPN_MAX - 1)

/*
 * Bit definitions क्रम s_flags.
 *
 * RVT_S_SIGNAL_REQ_WR - set अगर QP send WRs contain completion संकेतed
 * RVT_S_BUSY - send tasklet is processing the QP
 * RVT_S_TIMER - the RC retry समयr is active
 * RVT_S_ACK_PENDING - an ACK is रुकोing to be sent after RDMA पढ़ो/atomics
 * RVT_S_WAIT_FENCE - रुकोing क्रम all prior RDMA पढ़ो or atomic SWQEs
 *                         beक्रमe processing the next SWQE
 * RVT_S_WAIT_RDMAR - रुकोing क्रम a RDMA पढ़ो or atomic SWQE to complete
 *                         beक्रमe processing the next SWQE
 * RVT_S_WAIT_RNR - रुकोing क्रम RNR समयout
 * RVT_S_WAIT_SSN_CREDIT - रुकोing क्रम RC credits to process next SWQE
 * RVT_S_WAIT_DMA - रुकोing क्रम send DMA queue to drain beक्रमe generating
 *                  next send completion entry not via send DMA
 * RVT_S_WAIT_PIO - रुकोing क्रम a send buffer to be available
 * RVT_S_WAIT_TX - रुकोing क्रम a काष्ठा verbs_txreq to be available
 * RVT_S_WAIT_DMA_DESC - रुकोing क्रम DMA descriptors to be available
 * RVT_S_WAIT_KMEM - रुकोing क्रम kernel memory to be available
 * RVT_S_WAIT_PSN - रुकोing क्रम a packet to निकास the send DMA queue
 * RVT_S_WAIT_ACK - रुकोing क्रम an ACK packet beक्रमe sending more requests
 * RVT_S_SEND_ONE - send one packet, request ACK, then रुको क्रम ACK
 * RVT_S_ECN - a BECN was queued to the send engine
 * RVT_S_MAX_BIT_MASK - The max bit that can be used by rdmavt
 */
#घोषणा RVT_S_SIGNAL_REQ_WR	0x0001
#घोषणा RVT_S_BUSY		0x0002
#घोषणा RVT_S_TIMER		0x0004
#घोषणा RVT_S_RESP_PENDING	0x0008
#घोषणा RVT_S_ACK_PENDING	0x0010
#घोषणा RVT_S_WAIT_FENCE	0x0020
#घोषणा RVT_S_WAIT_RDMAR	0x0040
#घोषणा RVT_S_WAIT_RNR		0x0080
#घोषणा RVT_S_WAIT_SSN_CREDIT	0x0100
#घोषणा RVT_S_WAIT_DMA		0x0200
#घोषणा RVT_S_WAIT_PIO		0x0400
#घोषणा RVT_S_WAIT_TX		0x0800
#घोषणा RVT_S_WAIT_DMA_DESC	0x1000
#घोषणा RVT_S_WAIT_KMEM		0x2000
#घोषणा RVT_S_WAIT_PSN		0x4000
#घोषणा RVT_S_WAIT_ACK		0x8000
#घोषणा RVT_S_SEND_ONE		0x10000
#घोषणा RVT_S_UNLIMITED_CREDIT	0x20000
#घोषणा RVT_S_ECN		0x40000
#घोषणा RVT_S_MAX_BIT_MASK	0x800000

/*
 * Drivers should use s_flags starting with bit 31 करोwn to the bit next to
 * RVT_S_MAX_BIT_MASK
 */

/*
 * Wait flags that would prevent any packet type from being sent.
 */
#घोषणा RVT_S_ANY_WAIT_IO \
	(RVT_S_WAIT_PIO | RVT_S_WAIT_TX | \
	 RVT_S_WAIT_DMA_DESC | RVT_S_WAIT_KMEM)

/*
 * Wait flags that would prevent send work requests from making progress.
 */
#घोषणा RVT_S_ANY_WAIT_SEND (RVT_S_WAIT_FENCE | RVT_S_WAIT_RDMAR | \
	RVT_S_WAIT_RNR | RVT_S_WAIT_SSN_CREDIT | RVT_S_WAIT_DMA | \
	RVT_S_WAIT_PSN | RVT_S_WAIT_ACK)

#घोषणा RVT_S_ANY_WAIT (RVT_S_ANY_WAIT_IO | RVT_S_ANY_WAIT_SEND)

/* Number of bits to pay attention to in the opcode क्रम checking qp type */
#घोषणा RVT_OPCODE_QP_MASK 0xE0

/* Flags क्रम checking QP state (see ib_rvt_state_ops[]) */
#घोषणा RVT_POST_SEND_OK                0x01
#घोषणा RVT_POST_RECV_OK                0x02
#घोषणा RVT_PROCESS_RECV_OK             0x04
#घोषणा RVT_PROCESS_SEND_OK             0x08
#घोषणा RVT_PROCESS_NEXT_SEND_OK        0x10
#घोषणा RVT_FLUSH_SEND			0x20
#घोषणा RVT_FLUSH_RECV			0x40
#घोषणा RVT_PROCESS_OR_FLUSH_SEND \
	(RVT_PROCESS_SEND_OK | RVT_FLUSH_SEND)
#घोषणा RVT_SEND_OR_FLUSH_OR_RECV_OK \
	(RVT_PROCESS_SEND_OK | RVT_FLUSH_SEND | RVT_PROCESS_RECV_OK)

/*
 * Internal send flags
 */
#घोषणा RVT_SEND_RESERVE_USED           IB_SEND_RESERVED_START
#घोषणा RVT_SEND_COMPLETION_ONLY	(IB_SEND_RESERVED_START << 1)

/**
 * rvt_ud_wr - IB UD work plus AH cache
 * @wr: valid IB work request
 * @attr: poपूर्णांकer to an allocated AH attribute
 *
 * Special हाल the UD WR so we can keep track of the AH attributes.
 *
 * NOTE: This data काष्ठाure is stricly ordered wr then attr. I.e the attr
 * MUST come after wr.  The ib_ud_wr is sized and copied in rvt_post_one_wr.
 * The copy assumes that wr is first.
 */
काष्ठा rvt_ud_wr अणु
	काष्ठा ib_ud_wr wr;
	काष्ठा rdma_ah_attr *attr;
पूर्ण;

/*
 * Send work request queue entry.
 * The size of the sg_list is determined when the QP is created and stored
 * in qp->s_max_sge.
 */
काष्ठा rvt_swqe अणु
	जोड़ अणु
		काष्ठा ib_send_wr wr;   /* करोn't use wr.sg_list */
		काष्ठा rvt_ud_wr ud_wr;
		काष्ठा ib_reg_wr reg_wr;
		काष्ठा ib_rdma_wr rdma_wr;
		काष्ठा ib_atomic_wr atomic_wr;
	पूर्ण;
	u32 psn;                /* first packet sequence number */
	u32 lpsn;               /* last packet sequence number */
	u32 ssn;                /* send sequence number */
	u32 length;             /* total length of data in sg_list */
	व्योम *priv;             /* driver dependent field */
	काष्ठा rvt_sge sg_list[];
पूर्ण;

/**
 * काष्ठा rvt_krwq - kernel काष्ठा receive work request
 * @p_lock: lock to protect producer of the kernel buffer
 * @head: index of next entry to fill
 * @c_lock:lock to protect consumer of the kernel buffer
 * @tail: index of next entry to pull
 * @count: count is aproximate of total receive enteries posted
 * @rvt_rwqe: काष्ठा of receive work request queue entry
 *
 * This काष्ठाure is used to contain the head poपूर्णांकer,
 * tail poपूर्णांकer and receive work queue entries क्रम kernel
 * mode user.
 */
काष्ठा rvt_krwq अणु
	spinlock_t p_lock;	/* protect producer */
	u32 head;               /* new work requests posted to the head */

	/* protect consumer */
	spinlock_t c_lock ____cacheline_aligned_in_smp;
	u32 tail;               /* receives pull requests from here. */
	u32 count;		/* approx count of receive entries posted */
	काष्ठा rvt_rwqe *curr_wq;
	काष्ठा rvt_rwqe wq[];
पूर्ण;

/*
 * rvt_get_swqe_ah - Return the poपूर्णांकer to the काष्ठा rvt_ah
 * @swqe: valid Send WQE
 *
 */
अटल अंतरभूत काष्ठा rvt_ah *rvt_get_swqe_ah(काष्ठा rvt_swqe *swqe)
अणु
	वापस ibah_to_rvtah(swqe->ud_wr.wr.ah);
पूर्ण

/**
 * rvt_get_swqe_ah_attr - Return the cached ah attribute inक्रमmation
 * @swqe: valid Send WQE
 *
 */
अटल अंतरभूत काष्ठा rdma_ah_attr *rvt_get_swqe_ah_attr(काष्ठा rvt_swqe *swqe)
अणु
	वापस swqe->ud_wr.attr;
पूर्ण

/**
 * rvt_get_swqe_remote_qpn - Access the remote QPN value
 * @swqe: valid Send WQE
 *
 */
अटल अंतरभूत u32 rvt_get_swqe_remote_qpn(काष्ठा rvt_swqe *swqe)
अणु
	वापस swqe->ud_wr.wr.remote_qpn;
पूर्ण

/**
 * rvt_get_swqe_remote_qkey - Acces the remote qkey value
 * @swqe: valid Send WQE
 *
 */
अटल अंतरभूत u32 rvt_get_swqe_remote_qkey(काष्ठा rvt_swqe *swqe)
अणु
	वापस swqe->ud_wr.wr.remote_qkey;
पूर्ण

/**
 * rvt_get_swqe_pkey_index - Access the pkey index
 * @swqe: valid Send WQE
 *
 */
अटल अंतरभूत u16 rvt_get_swqe_pkey_index(काष्ठा rvt_swqe *swqe)
अणु
	वापस swqe->ud_wr.wr.pkey_index;
पूर्ण

काष्ठा rvt_rq अणु
	काष्ठा rvt_rwq *wq;
	काष्ठा rvt_krwq *kwq;
	u32 size;               /* size of RWQE array */
	u8 max_sge;
	/* protect changes in this काष्ठा */
	spinlock_t lock ____cacheline_aligned_in_smp;
पूर्ण;

/**
 * rvt_get_rq_count - count numbers of request work queue entries
 * in circular buffer
 * @rq: data काष्ठाure क्रम request queue entry
 * @head: head indices of the circular buffer
 * @tail: tail indices of the circular buffer
 *
 * Return - total number of entries in the Receive Queue
 */

अटल अंतरभूत u32 rvt_get_rq_count(काष्ठा rvt_rq *rq, u32 head, u32 tail)
अणु
	u32 count = head - tail;

	अगर ((s32)count < 0)
		count += rq->size;
	वापस count;
पूर्ण

/*
 * This काष्ठाure holds the inक्रमmation that the send tasklet needs
 * to send a RDMA पढ़ो response or atomic operation.
 */
काष्ठा rvt_ack_entry अणु
	काष्ठा rvt_sge rdma_sge;
	u64 atomic_data;
	u32 psn;
	u32 lpsn;
	u8 opcode;
	u8 sent;
	व्योम *priv;
पूर्ण;

#घोषणा	RC_QP_SCALING_INTERVAL	5

#घोषणा RVT_OPERATION_PRIV        0x00000001
#घोषणा RVT_OPERATION_ATOMIC      0x00000002
#घोषणा RVT_OPERATION_ATOMIC_SGE  0x00000004
#घोषणा RVT_OPERATION_LOCAL       0x00000008
#घोषणा RVT_OPERATION_USE_RESERVE 0x00000010
#घोषणा RVT_OPERATION_IGN_RNR_CNT 0x00000020

#घोषणा RVT_OPERATION_MAX (IB_WR_RESERVED10 + 1)

/**
 * rvt_operation_params - op table entry
 * @length - the length to copy पूर्णांकo the swqe entry
 * @qpt_support - a bit mask indicating QP type support
 * @flags - RVT_OPERATION flags (see above)
 *
 * This supports table driven post send so that
 * the driver can have dअगरfering an potentially
 * dअगरferent sets of operations.
 *
 **/

काष्ठा rvt_operation_params अणु
	माप_प्रकार length;
	u32 qpt_support;
	u32 flags;
पूर्ण;

/*
 * Common variables are रक्षित by both r_rq.lock and s_lock in that order
 * which only happens in modअगरy_qp() or changing the QP 'state'.
 */
काष्ठा rvt_qp अणु
	काष्ठा ib_qp ibqp;
	व्योम *priv; /* Driver निजी data */
	/* पढ़ो mostly fields above and below */
	काष्ठा rdma_ah_attr remote_ah_attr;
	काष्ठा rdma_ah_attr alt_ah_attr;
	काष्ठा rvt_qp __rcu *next;           /* link list क्रम QPN hash table */
	काष्ठा rvt_swqe *s_wq;  /* send work queue */
	काष्ठा rvt_mmap_info *ip;

	अचिन्हित दीर्घ समयout_jअगरfies;  /* computed from समयout */

	पूर्णांक srate_mbps;		/* s_srate (below) converted to Mbit/s */
	pid_t pid;		/* pid क्रम user mode QPs */
	u32 remote_qpn;
	u32 qkey;               /* QKEY क्रम this QP (क्रम UD or RD) */
	u32 s_size;             /* send work queue size */

	u16 pmtu;		/* decoded from path_mtu */
	u8 log_pmtu;		/* shअगरt क्रम pmtu */
	u8 state;               /* QP state */
	u8 allowed_ops;		/* high order bits of allowed opcodes */
	u8 qp_access_flags;
	u8 alt_समयout;         /* Alternate path समयout क्रम this QP */
	u8 समयout;             /* Timeout क्रम this QP */
	u8 s_srate;
	u8 s_mig_state;
	u8 port_num;
	u8 s_pkey_index;        /* PKEY index to use */
	u8 s_alt_pkey_index;    /* Alternate path PKEY index to use */
	u8 r_max_rd_atomic;     /* max number of RDMA पढ़ो/atomic to receive */
	u8 s_max_rd_atomic;     /* max number of RDMA पढ़ो/atomic to send */
	u8 s_retry_cnt;         /* number of बार to retry */
	u8 s_rnr_retry_cnt;
	u8 r_min_rnr_समयr;     /* retry समयout value क्रम RNR NAKs */
	u8 s_max_sge;           /* size of s_wq->sg_list */
	u8 s_draining;

	/* start of पढ़ो/ग_लिखो fields */
	atomic_t refcount ____cacheline_aligned_in_smp;
	रुको_queue_head_t रुको;

	काष्ठा rvt_ack_entry *s_ack_queue;
	काष्ठा rvt_sge_state s_rdma_पढ़ो_sge;

	spinlock_t r_lock ____cacheline_aligned_in_smp;      /* used क्रम APM */
	u32 r_psn;              /* expected rcv packet sequence number */
	अचिन्हित दीर्घ r_aflags;
	u64 r_wr_id;            /* ID क्रम current receive WQE */
	u32 r_ack_psn;          /* PSN क्रम next ACK or atomic ACK */
	u32 r_len;              /* total length of r_sge */
	u32 r_rcv_len;          /* receive data len processed */
	u32 r_msn;              /* message sequence number */

	u8 r_state;             /* opcode of last packet received */
	u8 r_flags;
	u8 r_head_ack_queue;    /* index पूर्णांकo s_ack_queue[] */
	u8 r_adefered;          /* defered ack count */

	काष्ठा list_head rspरुको;       /* link क्रम रुकोing to respond */

	काष्ठा rvt_sge_state r_sge;     /* current receive data */
	काष्ठा rvt_rq r_rq;             /* receive work queue */

	/* post send line */
	spinlock_t s_hlock ____cacheline_aligned_in_smp;
	u32 s_head;             /* new entries added here */
	u32 s_next_psn;         /* PSN क्रम next request */
	u32 s_avail;            /* number of entries avail */
	u32 s_ssn;              /* SSN of tail entry */
	atomic_t s_reserved_used; /* reserved entries in use */

	spinlock_t s_lock ____cacheline_aligned_in_smp;
	u32 s_flags;
	काष्ठा rvt_sge_state *s_cur_sge;
	काष्ठा rvt_swqe *s_wqe;
	काष्ठा rvt_sge_state s_sge;     /* current send request data */
	काष्ठा rvt_mregion *s_rdma_mr;
	u32 s_len;              /* total length of s_sge */
	u32 s_rdma_पढ़ो_len;    /* total length of s_rdma_पढ़ो_sge */
	u32 s_last_psn;         /* last response PSN processed */
	u32 s_sending_psn;      /* lowest PSN that is being sent */
	u32 s_sending_hpsn;     /* highest PSN that is being sent */
	u32 s_psn;              /* current packet sequence number */
	u32 s_ack_rdma_psn;     /* PSN क्रम sending RDMA पढ़ो responses */
	u32 s_ack_psn;          /* PSN क्रम acking sends and RDMA ग_लिखोs */
	u32 s_tail;             /* next entry to process */
	u32 s_cur;              /* current work queue entry */
	u32 s_acked;            /* last un-ACK'ed entry */
	u32 s_last;             /* last completed entry */
	u32 s_lsn;              /* limit sequence number (credit) */
	u32 s_ahgpsn;           /* set to the psn in the copy of the header */
	u16 s_cur_size;         /* size of send packet in bytes */
	u16 s_rdma_ack_cnt;
	u8 s_hdrwords;         /* size of s_hdr in 32 bit words */
	s8 s_ahgidx;
	u8 s_state;             /* opcode of last packet sent */
	u8 s_ack_state;         /* opcode of packet to ACK */
	u8 s_nak_state;         /* non-zero अगर NAK is pending */
	u8 r_nak_state;         /* non-zero अगर NAK is pending */
	u8 s_retry;             /* requester retry counter */
	u8 s_rnr_retry;         /* requester RNR retry counter */
	u8 s_num_rd_atomic;     /* number of RDMA पढ़ो/atomic pending */
	u8 s_tail_ack_queue;    /* index पूर्णांकo s_ack_queue[] */
	u8 s_acked_ack_queue;   /* index पूर्णांकo s_ack_queue[] */

	काष्ठा rvt_sge_state s_ack_rdma_sge;
	काष्ठा समयr_list s_समयr;
	काष्ठा hrसमयr s_rnr_समयr;

	atomic_t local_ops_pending; /* number of fast_reg/local_inv reqs */

	/*
	 * This sge list MUST be last. Do not add anything below here.
	 */
	काष्ठा rvt_sge r_sg_list[] /* verअगरied SGEs */
		____cacheline_aligned_in_smp;
पूर्ण;

काष्ठा rvt_srq अणु
	काष्ठा ib_srq ibsrq;
	काष्ठा rvt_rq rq;
	काष्ठा rvt_mmap_info *ip;
	/* send संकेत when number of RWQEs < limit */
	u32 limit;
पूर्ण;

अटल अंतरभूत काष्ठा rvt_srq *ibsrq_to_rvtsrq(काष्ठा ib_srq *ibsrq)
अणु
	वापस container_of(ibsrq, काष्ठा rvt_srq, ibsrq);
पूर्ण

अटल अंतरभूत काष्ठा rvt_qp *ibqp_to_rvtqp(काष्ठा ib_qp *ibqp)
अणु
	वापस container_of(ibqp, काष्ठा rvt_qp, ibqp);
पूर्ण

#घोषणा RVT_QPN_MAX                 BIT(24)
#घोषणा RVT_QPNMAP_ENTRIES          (RVT_QPN_MAX / PAGE_SIZE / BITS_PER_BYTE)
#घोषणा RVT_BITS_PER_PAGE           (PAGE_SIZE * BITS_PER_BYTE)
#घोषणा RVT_BITS_PER_PAGE_MASK      (RVT_BITS_PER_PAGE - 1)
#घोषणा RVT_QPN_MASK		    IB_QPN_MASK

/*
 * QPN-map pages start out as शून्य, they get allocated upon
 * first use and are never deallocated. This way,
 * large biपंचांगaps are not allocated unless large numbers of QPs are used.
 */
काष्ठा rvt_qpn_map अणु
	व्योम *page;
पूर्ण;

काष्ठा rvt_qpn_table अणु
	spinlock_t lock; /* protect changes to the qp table */
	अचिन्हित flags;         /* flags क्रम QP0/1 allocated क्रम each port */
	u32 last;               /* last QP number allocated */
	u32 nmaps;              /* size of the map table */
	u16 limit;
	u8  incr;
	/* bit map of मुक्त QP numbers other than 0/1 */
	काष्ठा rvt_qpn_map map[RVT_QPNMAP_ENTRIES];
पूर्ण;

काष्ठा rvt_qp_ibdev अणु
	u32 qp_table_size;
	u32 qp_table_bits;
	काष्ठा rvt_qp __rcu **qp_table;
	spinlock_t qpt_lock; /* qptable lock */
	काष्ठा rvt_qpn_table qpn_table;
पूर्ण;

/*
 * There is one काष्ठा rvt_mcast क्रम each multicast GID.
 * All attached QPs are then stored as a list of
 * काष्ठा rvt_mcast_qp.
 */
काष्ठा rvt_mcast_qp अणु
	काष्ठा list_head list;
	काष्ठा rvt_qp *qp;
पूर्ण;

काष्ठा rvt_mcast_addr अणु
	जोड़ ib_gid mgid;
	u16 lid;
पूर्ण;

काष्ठा rvt_mcast अणु
	काष्ठा rb_node rb_node;
	काष्ठा rvt_mcast_addr mcast_addr;
	काष्ठा list_head qp_list;
	रुको_queue_head_t रुको;
	atomic_t refcount;
	पूर्णांक n_attached;
पूर्ण;

/*
 * Since काष्ठा rvt_swqe is not a fixed size, we can't simply index पूर्णांकo
 * काष्ठा rvt_qp.s_wq.  This function करोes the array index computation.
 */
अटल अंतरभूत काष्ठा rvt_swqe *rvt_get_swqe_ptr(काष्ठा rvt_qp *qp,
						अचिन्हित n)
अणु
	वापस (काष्ठा rvt_swqe *)((अक्षर *)qp->s_wq +
				     (माप(काष्ठा rvt_swqe) +
				      qp->s_max_sge *
				      माप(काष्ठा rvt_sge)) * n);
पूर्ण

/*
 * Since काष्ठा rvt_rwqe is not a fixed size, we can't simply index पूर्णांकo
 * काष्ठा rvt_rwq.wq.  This function करोes the array index computation.
 */
अटल अंतरभूत काष्ठा rvt_rwqe *rvt_get_rwqe_ptr(काष्ठा rvt_rq *rq, अचिन्हित n)
अणु
	वापस (काष्ठा rvt_rwqe *)
		((अक्षर *)rq->kwq->curr_wq +
		 (माप(काष्ठा rvt_rwqe) +
		  rq->max_sge * माप(काष्ठा ib_sge)) * n);
पूर्ण

/**
 * rvt_is_user_qp - वापस अगर this is user mode QP
 * @qp - the target QP
 */
अटल अंतरभूत bool rvt_is_user_qp(काष्ठा rvt_qp *qp)
अणु
	वापस !!qp->pid;
पूर्ण

/**
 * rvt_get_qp - get a QP reference
 * @qp - the QP to hold
 */
अटल अंतरभूत व्योम rvt_get_qp(काष्ठा rvt_qp *qp)
अणु
	atomic_inc(&qp->refcount);
पूर्ण

/**
 * rvt_put_qp - release a QP reference
 * @qp - the QP to release
 */
अटल अंतरभूत व्योम rvt_put_qp(काष्ठा rvt_qp *qp)
अणु
	अगर (qp && atomic_dec_and_test(&qp->refcount))
		wake_up(&qp->रुको);
पूर्ण

/**
 * rvt_put_swqe - drop mr refs held by swqe
 * @wqe - the send wqe
 *
 * This drops any mr references held by the swqe
 */
अटल अंतरभूत व्योम rvt_put_swqe(काष्ठा rvt_swqe *wqe)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < wqe->wr.num_sge; i++) अणु
		काष्ठा rvt_sge *sge = &wqe->sg_list[i];

		rvt_put_mr(sge->mr);
	पूर्ण
पूर्ण

/**
 * rvt_qp_wqe_reserve - reserve operation
 * @qp - the rvt qp
 * @wqe - the send wqe
 *
 * This routine used in post send to record
 * a wqe relative reserved operation use.
 */
अटल अंतरभूत व्योम rvt_qp_wqe_reserve(
	काष्ठा rvt_qp *qp,
	काष्ठा rvt_swqe *wqe)
अणु
	atomic_inc(&qp->s_reserved_used);
पूर्ण

/**
 * rvt_qp_wqe_unreserve - clean reserved operation
 * @qp - the rvt qp
 * @flags - send wqe flags
 *
 * This decrements the reserve use count.
 *
 * This call MUST precede the change to
 * s_last to insure that post send sees a stable
 * s_avail.
 *
 * An smp_mp__after_atomic() is used to insure
 * the compiler करोes not juggle the order of the s_last
 * ring index and the decrementing of s_reserved_used.
 */
अटल अंतरभूत व्योम rvt_qp_wqe_unreserve(काष्ठा rvt_qp *qp, पूर्णांक flags)
अणु
	अगर (unlikely(flags & RVT_SEND_RESERVE_USED)) अणु
		atomic_dec(&qp->s_reserved_used);
		/* insure no compiler re-order up to s_last change */
		smp_mb__after_atomic();
	पूर्ण
पूर्ण

बाह्य स्थिर क्रमागत ib_wc_opcode ib_rvt_wc_opcode[];

/*
 * Compare the lower 24 bits of the msn values.
 * Returns an पूर्णांकeger <, ==, or > than zero.
 */
अटल अंतरभूत पूर्णांक rvt_cmp_msn(u32 a, u32 b)
अणु
	वापस (((पूर्णांक)a) - ((पूर्णांक)b)) << 8;
पूर्ण

__be32 rvt_compute_aeth(काष्ठा rvt_qp *qp);

व्योम rvt_get_credit(काष्ठा rvt_qp *qp, u32 aeth);

u32 rvt_restart_sge(काष्ठा rvt_sge_state *ss, काष्ठा rvt_swqe *wqe, u32 len);

/**
 * rvt_भाग_round_up_mtu - round up भागide
 * @qp - the qp pair
 * @len - the length
 *
 * Perक्रमm a shअगरt based mtu round up भागide
 */
अटल अंतरभूत u32 rvt_भाग_round_up_mtu(काष्ठा rvt_qp *qp, u32 len)
अणु
	वापस (len + qp->pmtu - 1) >> qp->log_pmtu;
पूर्ण

/**
 * @qp - the qp pair
 * @len - the length
 *
 * Perक्रमm a shअगरt based mtu भागide
 */
अटल अंतरभूत u32 rvt_भाग_mtu(काष्ठा rvt_qp *qp, u32 len)
अणु
	वापस len >> qp->log_pmtu;
पूर्ण

/**
 * rvt_समयout_to_jअगरfies - Convert a ULP समयout input पूर्णांकo jअगरfies
 * @समयout - समयout input(0 - 31).
 *
 * Return a समयout value in jअगरfies.
 */
अटल अंतरभूत अचिन्हित दीर्घ rvt_समयout_to_jअगरfies(u8 समयout)
अणु
	अगर (समयout > 31)
		समयout = 31;

	वापस usecs_to_jअगरfies(1U << समयout) * 4096UL / 1000UL;
पूर्ण

/**
 * rvt_lookup_qpn - वापस the QP with the given QPN
 * @ibp: the ibport
 * @qpn: the QP number to look up
 *
 * The caller must hold the rcu_पढ़ो_lock(), and keep the lock until
 * the वापसed qp is no दीर्घer in use.
 */
अटल अंतरभूत काष्ठा rvt_qp *rvt_lookup_qpn(काष्ठा rvt_dev_info *rdi,
					    काष्ठा rvt_ibport *rvp,
					    u32 qpn) __must_hold(RCU)
अणु
	काष्ठा rvt_qp *qp = शून्य;

	अगर (unlikely(qpn <= 1)) अणु
		qp = rcu_dereference(rvp->qp[qpn]);
	पूर्ण अन्यथा अणु
		u32 n = hash_32(qpn, rdi->qp_dev->qp_table_bits);

		क्रम (qp = rcu_dereference(rdi->qp_dev->qp_table[n]); qp;
			qp = rcu_dereference(qp->next))
			अगर (qp->ibqp.qp_num == qpn)
				अवरोध;
	पूर्ण
	वापस qp;
पूर्ण

/**
 * rvt_mod_retry_समयr - mod a retry समयr
 * @qp - the QP
 * @shअगरt - समयout shअगरt to रुको क्रम multiple packets
 * Modअगरy a potentially alपढ़ोy running retry समयr
 */
अटल अंतरभूत व्योम rvt_mod_retry_समयr_ext(काष्ठा rvt_qp *qp, u8 shअगरt)
अणु
	काष्ठा ib_qp *ibqp = &qp->ibqp;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibqp->device);

	lockdep_निश्चित_held(&qp->s_lock);
	qp->s_flags |= RVT_S_TIMER;
	/* 4.096 usec. * (1 << qp->समयout) */
	mod_समयr(&qp->s_समयr, jअगरfies + rdi->busy_jअगरfies +
		  (qp->समयout_jअगरfies << shअगरt));
पूर्ण

अटल अंतरभूत व्योम rvt_mod_retry_समयr(काष्ठा rvt_qp *qp)
अणु
	वापस rvt_mod_retry_समयr_ext(qp, 0);
पूर्ण

/**
 * rvt_put_qp_swqe - drop refs held by swqe
 * @qp: the send qp
 * @wqe: the send wqe
 *
 * This drops any references held by the swqe
 */
अटल अंतरभूत व्योम rvt_put_qp_swqe(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe)
अणु
	rvt_put_swqe(wqe);
	अगर (qp->allowed_ops == IB_OPCODE_UD)
		rdma_destroy_ah_attr(wqe->ud_wr.attr);
पूर्ण

/**
 * rvt_qp_sqwe_incr - increment ring index
 * @qp: the qp
 * @val: the starting value
 *
 * Return: the new value wrapping as appropriate
 */
अटल अंतरभूत u32
rvt_qp_swqe_incr(काष्ठा rvt_qp *qp, u32 val)
अणु
	अगर (++val >= qp->s_size)
		val = 0;
	वापस val;
पूर्ण

पूर्णांक rvt_error_qp(काष्ठा rvt_qp *qp, क्रमागत ib_wc_status err);

/**
 * rvt_recv_cq - add a new entry to completion queue
 *			by receive queue
 * @qp: receive queue
 * @wc: work completion entry to add
 * @solicited: true अगर @entry is solicited
 *
 * This is wrapper function क्रम rvt_enter_cq function call by
 * receive queue. If rvt_cq_enter वापस false, it means cq is
 * full and the qp is put पूर्णांकo error state.
 */
अटल अंतरभूत व्योम rvt_recv_cq(काष्ठा rvt_qp *qp, काष्ठा ib_wc *wc,
			       bool solicited)
अणु
	काष्ठा rvt_cq *cq = ibcq_to_rvtcq(qp->ibqp.recv_cq);

	अगर (unlikely(!rvt_cq_enter(cq, wc, solicited)))
		rvt_error_qp(qp, IB_WC_LOC_QP_OP_ERR);
पूर्ण

/**
 * rvt_send_cq - add a new entry to completion queue
 *                        by send queue
 * @qp: send queue
 * @wc: work completion entry to add
 * @solicited: true अगर @entry is solicited
 *
 * This is wrapper function क्रम rvt_enter_cq function call by
 * send queue. If rvt_cq_enter वापस false, it means cq is
 * full and the qp is put पूर्णांकo error state.
 */
अटल अंतरभूत व्योम rvt_send_cq(काष्ठा rvt_qp *qp, काष्ठा ib_wc *wc,
			       bool solicited)
अणु
	काष्ठा rvt_cq *cq = ibcq_to_rvtcq(qp->ibqp.send_cq);

	अगर (unlikely(!rvt_cq_enter(cq, wc, solicited)))
		rvt_error_qp(qp, IB_WC_LOC_QP_OP_ERR);
पूर्ण

/**
 * rvt_qp_complete_swqe - insert send completion
 * @qp - the qp
 * @wqe - the send wqe
 * @opcode - wc operation (driver dependent)
 * @status - completion status
 *
 * Update the s_last inक्रमmation, and then insert a send
 * completion पूर्णांकo the completion
 * queue अगर the qp indicates it should be करोne.
 *
 * See IBTA 10.7.3.1 क्रम info on completion
 * control.
 *
 * Return: new last
 */
अटल अंतरभूत u32
rvt_qp_complete_swqe(काष्ठा rvt_qp *qp,
		     काष्ठा rvt_swqe *wqe,
		     क्रमागत ib_wc_opcode opcode,
		     क्रमागत ib_wc_status status)
अणु
	bool need_completion;
	u64 wr_id;
	u32 byte_len, last;
	पूर्णांक flags = wqe->wr.send_flags;

	rvt_qp_wqe_unreserve(qp, flags);
	rvt_put_qp_swqe(qp, wqe);

	need_completion =
		!(flags & RVT_SEND_RESERVE_USED) &&
		(!(qp->s_flags & RVT_S_SIGNAL_REQ_WR) ||
		(flags & IB_SEND_SIGNALED) ||
		status != IB_WC_SUCCESS);
	अगर (need_completion) अणु
		wr_id = wqe->wr.wr_id;
		byte_len = wqe->length;
		/* above fields required beक्रमe writing s_last */
	पूर्ण
	last = rvt_qp_swqe_incr(qp, qp->s_last);
	/* see rvt_qp_is_avail() */
	smp_store_release(&qp->s_last, last);
	अगर (need_completion) अणु
		काष्ठा ib_wc w = अणु
			.wr_id = wr_id,
			.status = status,
			.opcode = opcode,
			.qp = &qp->ibqp,
			.byte_len = byte_len,
		पूर्ण;
		rvt_send_cq(qp, &w, status != IB_WC_SUCCESS);
	पूर्ण
	वापस last;
पूर्ण

बाह्य स्थिर पूर्णांक  ib_rvt_state_ops[];

काष्ठा rvt_dev_info;
पूर्णांक rvt_get_rwqe(काष्ठा rvt_qp *qp, bool wr_id_only);
व्योम rvt_comm_est(काष्ठा rvt_qp *qp);
व्योम rvt_rc_error(काष्ठा rvt_qp *qp, क्रमागत ib_wc_status err);
अचिन्हित दीर्घ rvt_rnr_tbl_to_usec(u32 index);
क्रमागत hrसमयr_restart rvt_rc_rnr_retry(काष्ठा hrसमयr *t);
व्योम rvt_add_rnr_समयr(काष्ठा rvt_qp *qp, u32 aeth);
व्योम rvt_del_समयrs_sync(काष्ठा rvt_qp *qp);
व्योम rvt_stop_rc_समयrs(काष्ठा rvt_qp *qp);
व्योम rvt_add_retry_समयr_ext(काष्ठा rvt_qp *qp, u8 shअगरt);
अटल अंतरभूत व्योम rvt_add_retry_समयr(काष्ठा rvt_qp *qp)
अणु
	rvt_add_retry_समयr_ext(qp, 0);
पूर्ण

व्योम rvt_copy_sge(काष्ठा rvt_qp *qp, काष्ठा rvt_sge_state *ss,
		  व्योम *data, u32 length,
		  bool release, bool copy_last);
व्योम rvt_send_complete(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
		       क्रमागत ib_wc_status status);
व्योम rvt_ruc_loopback(काष्ठा rvt_qp *qp);

/**
 * काष्ठा rvt_qp_iter - the iterator क्रम QPs
 * @qp - the current QP
 *
 * This काष्ठाure defines the current iterator
 * state क्रम sequenced access to all QPs relative
 * to an rvt_dev_info.
 */
काष्ठा rvt_qp_iter अणु
	काष्ठा rvt_qp *qp;
	/* निजी: backpoपूर्णांकer */
	काष्ठा rvt_dev_info *rdi;
	/* निजी: callback routine */
	व्योम (*cb)(काष्ठा rvt_qp *qp, u64 v);
	/* निजी: क्रम arg to callback routine */
	u64 v;
	/* निजी: number of SMI,GSI QPs क्रम device */
	पूर्णांक specials;
	/* निजी: current iterator index */
	पूर्णांक n;
पूर्ण;

/**
 * ib_cq_tail - Return tail index of cq buffer
 * @send_cq - The cq क्रम send
 *
 * This is called in qp_iter_prपूर्णांक to get tail
 * of cq buffer.
 */
अटल अंतरभूत u32 ib_cq_tail(काष्ठा ib_cq *send_cq)
अणु
	काष्ठा rvt_cq *cq = ibcq_to_rvtcq(send_cq);

	वापस ibcq_to_rvtcq(send_cq)->ip ?
	       RDMA_READ_UAPI_ATOMIC(cq->queue->tail) :
	       ibcq_to_rvtcq(send_cq)->kqueue->tail;
पूर्ण

/**
 * ib_cq_head - Return head index of cq buffer
 * @send_cq - The cq क्रम send
 *
 * This is called in qp_iter_prपूर्णांक to get head
 * of cq buffer.
 */
अटल अंतरभूत u32 ib_cq_head(काष्ठा ib_cq *send_cq)
अणु
	काष्ठा rvt_cq *cq = ibcq_to_rvtcq(send_cq);

	वापस ibcq_to_rvtcq(send_cq)->ip ?
	       RDMA_READ_UAPI_ATOMIC(cq->queue->head) :
	       ibcq_to_rvtcq(send_cq)->kqueue->head;
पूर्ण

/**
 * rvt_मुक्त_rq - मुक्त memory allocated क्रम rvt_rq काष्ठा
 * @rvt_rq: request queue data काष्ठाure
 *
 * This function should only be called अगर the rvt_mmap_info()
 * has not succeeded.
 */
अटल अंतरभूत व्योम rvt_मुक्त_rq(काष्ठा rvt_rq *rq)
अणु
	kvमुक्त(rq->kwq);
	rq->kwq = शून्य;
	vमुक्त(rq->wq);
	rq->wq = शून्य;
पूर्ण

/**
 * rvt_to_iport - Get the ibport poपूर्णांकer
 * @qp: the qp poपूर्णांकer
 *
 * This function वापसs the ibport poपूर्णांकer from the qp poपूर्णांकer.
 */
अटल अंतरभूत काष्ठा rvt_ibport *rvt_to_iport(काष्ठा rvt_qp *qp)
अणु
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(qp->ibqp.device);

	वापस rdi->ports[qp->port_num - 1];
पूर्ण

/**
 * rvt_rc_credit_avail - Check अगर there are enough RC credits क्रम the request
 * @qp: the qp
 * @wqe: the request
 *
 * This function वापसs false when there are not enough credits क्रम the given
 * request and true otherwise.
 */
अटल अंतरभूत bool rvt_rc_credit_avail(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe)
अणु
	lockdep_निश्चित_held(&qp->s_lock);
	अगर (!(qp->s_flags & RVT_S_UNLIMITED_CREDIT) &&
	    rvt_cmp_msn(wqe->ssn, qp->s_lsn + 1) > 0) अणु
		काष्ठा rvt_ibport *rvp = rvt_to_iport(qp);

		qp->s_flags |= RVT_S_WAIT_SSN_CREDIT;
		rvp->n_rc_crरुकोs++;
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

काष्ठा rvt_qp_iter *rvt_qp_iter_init(काष्ठा rvt_dev_info *rdi,
				     u64 v,
				     व्योम (*cb)(काष्ठा rvt_qp *qp, u64 v));
पूर्णांक rvt_qp_iter_next(काष्ठा rvt_qp_iter *iter);
व्योम rvt_qp_iter(काष्ठा rvt_dev_info *rdi,
		 u64 v,
		 व्योम (*cb)(काष्ठा rvt_qp *qp, u64 v));
व्योम rvt_qp_mr_clean(काष्ठा rvt_qp *qp, u32 lkey);
#पूर्ण_अगर          /* DEF_RDMAVT_INCQP_H */
