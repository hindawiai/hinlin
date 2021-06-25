<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause */

/* Authors: Bernard Metzler <bmt@zurich.ibm.com> */
/* Copyright (c) 2008-2019, IBM Corporation */

#अगर_अघोषित _SIW_H
#घोषणा _SIW_H

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/restrack.h>
#समावेश <linux/socket.h>
#समावेश <linux/skbuff.h>
#समावेश <crypto/hash.h>
#समावेश <linux/crc32.h>
#समावेश <linux/crc32c.h>

#समावेश <rdma/siw-abi.h>
#समावेश "iwarp.h"

#घोषणा SIW_VENDOR_ID 0x626d74 /* ascii 'bmt' क्रम now */
#घोषणा SIW_VENDORT_PART_ID 0
#घोषणा SIW_MAX_QP (1024 * 100)
#घोषणा SIW_MAX_QP_WR (1024 * 32)
#घोषणा SIW_MAX_ORD_QP 128
#घोषणा SIW_MAX_IRD_QP 128
#घोषणा SIW_MAX_SGE_PBL 256 /* max num sge's क्रम PBL */
#घोषणा SIW_MAX_SGE_RD 1 /* iwarp limitation. we could relax */
#घोषणा SIW_MAX_CQ (1024 * 100)
#घोषणा SIW_MAX_CQE (SIW_MAX_QP_WR * 100)
#घोषणा SIW_MAX_MR (SIW_MAX_QP * 10)
#घोषणा SIW_MAX_PD SIW_MAX_QP
#घोषणा SIW_MAX_MW 0 /* to be set अगर MW's are supported */
#घोषणा SIW_MAX_SRQ SIW_MAX_QP
#घोषणा SIW_MAX_SRQ_WR (SIW_MAX_QP_WR * 10)
#घोषणा SIW_MAX_CONTEXT SIW_MAX_PD

/* Min number of bytes क्रम using zero copy transmit */
#घोषणा SENDPAGE_THRESH PAGE_SIZE

/* Maximum number of frames which can be send in one SQ processing */
#घोषणा SQ_USER_MAXBURST 100

/* Maximum number of consecutive IRQ elements which get served
 * अगर SQ has pending work. Prevents starving local SQ processing
 * by serving peer Read Requests.
 */
#घोषणा SIW_IRQ_MAXBURST_SQ_ACTIVE 4

काष्ठा siw_dev_cap अणु
	पूर्णांक max_qp;
	पूर्णांक max_qp_wr;
	पूर्णांक max_ord; /* max. outbound पढ़ो queue depth */
	पूर्णांक max_ird; /* max. inbound पढ़ो queue depth */
	पूर्णांक max_sge;
	पूर्णांक max_sge_rd;
	पूर्णांक max_cq;
	पूर्णांक max_cqe;
	पूर्णांक max_mr;
	पूर्णांक max_pd;
	पूर्णांक max_mw;
	पूर्णांक max_srq;
	पूर्णांक max_srq_wr;
	पूर्णांक max_srq_sge;
पूर्ण;

काष्ठा siw_pd अणु
	काष्ठा ib_pd base_pd;
पूर्ण;

काष्ठा siw_device अणु
	काष्ठा ib_device base_dev;
	काष्ठा net_device *netdev;
	काष्ठा siw_dev_cap attrs;

	u32 venकरोr_part_id;
	पूर्णांक numa_node;

	/* physical port state (only one port per device) */
	क्रमागत ib_port_state state;

	spinlock_t lock;

	काष्ठा xarray qp_xa;
	काष्ठा xarray mem_xa;

	काष्ठा list_head cep_list;
	काष्ठा list_head qp_list;

	/* active objects statistics to enक्रमce limits */
	atomic_t num_qp;
	atomic_t num_cq;
	atomic_t num_pd;
	atomic_t num_mr;
	atomic_t num_srq;
	atomic_t num_ctx;

	काष्ठा work_काष्ठा netdev_करोwn;
पूर्ण;

काष्ठा siw_ucontext अणु
	काष्ठा ib_ucontext base_ucontext;
	काष्ठा siw_device *sdev;
पूर्ण;

/*
 * The RDMA core करोes not define LOCAL_READ access, which is always
 * enabled implictely.
 */
#घोषणा IWARP_ACCESS_MASK					\
	(IB_ACCESS_LOCAL_WRITE | IB_ACCESS_REMOTE_WRITE	|	\
	 IB_ACCESS_REMOTE_READ)

/*
 * siw presentation of user memory रेजिस्टरed as source
 * or target of RDMA operations.
 */

काष्ठा siw_page_chunk अणु
	काष्ठा page **plist;
पूर्ण;

काष्ठा siw_umem अणु
	काष्ठा siw_page_chunk *page_chunk;
	पूर्णांक num_pages;
	bool writable;
	u64 fp_addr; /* First page base address */
	काष्ठा mm_काष्ठा *owning_mm;
पूर्ण;

काष्ठा siw_pble अणु
	dma_addr_t addr; /* Address of asचिन्हित buffer */
	अचिन्हित पूर्णांक size; /* Size of this entry */
	अचिन्हित दीर्घ pbl_off; /* Total offset from start of PBL */
पूर्ण;

काष्ठा siw_pbl अणु
	अचिन्हित पूर्णांक num_buf;
	अचिन्हित पूर्णांक max_buf;
	काष्ठा siw_pble pbe[];
पूर्ण;

/*
 * Generic memory representation क्रम रेजिस्टरed siw memory.
 * Memory lookup always via higher 24 bit of STag (STag index).
 */
काष्ठा siw_mem अणु
	काष्ठा siw_device *sdev;
	काष्ठा kref ref;
	u64 va; /* VA of memory */
	u64 len; /* length of the memory buffer in bytes */
	u32 stag; /* iWarp memory access steering tag */
	u8 stag_valid; /* VALID or INVALID */
	u8 is_pbl; /* PBL or user space mem */
	u8 is_mw; /* Memory Region or Memory Winकरोw */
	क्रमागत ib_access_flags perms; /* local/remote READ & WRITE */
	जोड़ अणु
		काष्ठा siw_umem *umem;
		काष्ठा siw_pbl *pbl;
		व्योम *mem_obj;
	पूर्ण;
	काष्ठा ib_pd *pd;
पूर्ण;

काष्ठा siw_mr अणु
	काष्ठा ib_mr base_mr;
	काष्ठा siw_mem *mem;
	काष्ठा rcu_head rcu;
पूर्ण;

/*
 * Error codes क्रम local or remote
 * access to रेजिस्टरed memory
 */
क्रमागत siw_access_state अणु
	E_ACCESS_OK,
	E_STAG_INVALID,
	E_BASE_BOUNDS,
	E_ACCESS_PERM,
	E_PD_MISMATCH
पूर्ण;

क्रमागत siw_wr_state अणु
	SIW_WR_IDLE,
	SIW_WR_QUEUED, /* processing has not started yet */
	SIW_WR_INPROGRESS /* initiated processing of the WR */
पूर्ण;

/* The WQE currently being processed (RX or TX) */
काष्ठा siw_wqe अणु
	/* Copy of applications SQE or RQE */
	जोड़ अणु
		काष्ठा siw_sqe sqe;
		काष्ठा siw_rqe rqe;
	पूर्ण;
	काष्ठा siw_mem *mem[SIW_MAX_SGE]; /* per sge's resolved mem */
	क्रमागत siw_wr_state wr_status;
	क्रमागत siw_wc_status wc_status;
	u32 bytes; /* total bytes to process */
	u32 processed; /* bytes processed */
पूर्ण;

काष्ठा siw_cq अणु
	काष्ठा ib_cq base_cq;
	spinlock_t lock;
	काष्ठा siw_cq_ctrl *notअगरy;
	काष्ठा siw_cqe *queue;
	u32 cq_put;
	u32 cq_get;
	u32 num_cqe;
	काष्ठा rdma_user_mmap_entry *cq_entry; /* mmap info क्रम CQE array */
	u32 id; /* For debugging only */
पूर्ण;

क्रमागत siw_qp_state अणु
	SIW_QP_STATE_IDLE,
	SIW_QP_STATE_RTR,
	SIW_QP_STATE_RTS,
	SIW_QP_STATE_CLOSING,
	SIW_QP_STATE_TERMINATE,
	SIW_QP_STATE_ERROR,
	SIW_QP_STATE_COUNT
पूर्ण;

क्रमागत siw_qp_flags अणु
	SIW_RDMA_BIND_ENABLED = (1 << 0),
	SIW_RDMA_WRITE_ENABLED = (1 << 1),
	SIW_RDMA_READ_ENABLED = (1 << 2),
	SIW_SIGNAL_ALL_WR = (1 << 3),
	SIW_MPA_CRC = (1 << 4),
	SIW_QP_IN_DESTROY = (1 << 5)
पूर्ण;

क्रमागत siw_qp_attr_mask अणु
	SIW_QP_ATTR_STATE = (1 << 0),
	SIW_QP_ATTR_ACCESS_FLAGS = (1 << 1),
	SIW_QP_ATTR_LLP_HANDLE = (1 << 2),
	SIW_QP_ATTR_ORD = (1 << 3),
	SIW_QP_ATTR_IRD = (1 << 4),
	SIW_QP_ATTR_SQ_SIZE = (1 << 5),
	SIW_QP_ATTR_RQ_SIZE = (1 << 6),
	SIW_QP_ATTR_MPA = (1 << 7)
पूर्ण;

काष्ठा siw_srq अणु
	काष्ठा ib_srq base_srq;
	spinlock_t lock;
	u32 max_sge;
	u32 limit; /* low watermark क्रम async event */
	काष्ठा siw_rqe *recvq;
	u32 rq_put;
	u32 rq_get;
	u32 num_rqe; /* max # of wqe's allowed */
	काष्ठा rdma_user_mmap_entry *srq_entry; /* mmap info क्रम SRQ array */
	bool armed:1; /* inक्रमm user अगर limit hit */
	bool is_kernel_res:1; /* true अगर kernel client */
पूर्ण;

काष्ठा siw_qp_attrs अणु
	क्रमागत siw_qp_state state;
	u32 sq_size;
	u32 rq_size;
	u32 orq_size;
	u32 irq_size;
	u32 sq_max_sges;
	u32 rq_max_sges;
	क्रमागत siw_qp_flags flags;

	काष्ठा socket *sk;
पूर्ण;

क्रमागत siw_tx_ctx अणु
	SIW_SEND_HDR, /* start or जारी sending HDR */
	SIW_SEND_DATA, /* start or जारी sending DDP payload */
	SIW_SEND_TRAILER, /* start or जारी sending TRAILER */
	SIW_SEND_SHORT_FPDU/* send whole FPDU hdr|data|trailer at once */
पूर्ण;

क्रमागत siw_rx_state अणु
	SIW_GET_HDR, /* aरुको new hdr or within hdr */
	SIW_GET_DATA_START, /* start of inbound DDP payload */
	SIW_GET_DATA_MORE, /* continuation of (misaligned) DDP payload */
	SIW_GET_TRAILER/* aरुको new trailer or within trailer */
पूर्ण;

काष्ठा siw_rx_stream अणु
	काष्ठा sk_buff *skb;
	पूर्णांक skb_new; /* pending unपढ़ो bytes in skb */
	पूर्णांक skb_offset; /* offset in skb */
	पूर्णांक skb_copied; /* processed bytes in skb */

	जोड़ iwarp_hdr hdr;
	काष्ठा mpa_trailer trailer;

	क्रमागत siw_rx_state state;

	/*
	 * For each FPDU, मुख्य RX loop runs through 3 stages:
	 * Receiving protocol headers, placing DDP payload and receiving
	 * trailer inक्रमmation (CRC + possibly padding).
	 * Next two variables keep state on receive status of the
	 * current FPDU part (hdr, data, trailer).
	 */
	पूर्णांक fpdu_part_rcvd; /* bytes in pkt part copied */
	पूर्णांक fpdu_part_rem; /* bytes in pkt part not seen */

	/*
	 * Next expected DDP MSN क्रम each QN +
	 * expected steering tag +
	 * expected DDP tagget offset (all HBO)
	 */
	u32 ddp_msn[RDMAP_UNTAGGED_QN_COUNT];
	u32 ddp_stag;
	u64 ddp_to;
	u32 inval_stag; /* Stag to be invalidated */

	काष्ठा shash_desc *mpa_crc_hd;
	u8 rx_suspend : 1;
	u8 pad : 2; /* # of pad bytes expected */
	u8 rdmap_op : 4; /* opcode of current frame */
पूर्ण;

काष्ठा siw_rx_fpdu अणु
	/*
	 * Local destination memory of inbound RDMA operation.
	 * Valid, according to wqe->wr_status
	 */
	काष्ठा siw_wqe wqe_active;

	अचिन्हित पूर्णांक pbl_idx; /* Index पूर्णांकo current PBL */
	अचिन्हित पूर्णांक sge_idx; /* current sge in rx */
	अचिन्हित पूर्णांक sge_off; /* alपढ़ोy rcvd in curr. sge */

	अक्षर first_ddp_seg; /* this is the first DDP seg */
	अक्षर more_ddp_segs; /* more DDP segs expected */
	u8 prev_rdmap_op : 4; /* opcode of prev frame */
पूर्ण;

/*
 * Shorthands क्रम लघु packets w/o payload
 * to be transmitted more efficient.
 */
काष्ठा siw_send_pkt अणु
	काष्ठा iwarp_send send;
	__be32 crc;
पूर्ण;

काष्ठा siw_ग_लिखो_pkt अणु
	काष्ठा iwarp_rdma_ग_लिखो ग_लिखो;
	__be32 crc;
पूर्ण;

काष्ठा siw_rreq_pkt अणु
	काष्ठा iwarp_rdma_rreq rreq;
	__be32 crc;
पूर्ण;

काष्ठा siw_rresp_pkt अणु
	काष्ठा iwarp_rdma_rresp rresp;
	__be32 crc;
पूर्ण;

काष्ठा siw_iwarp_tx अणु
	जोड़ अणु
		जोड़ iwarp_hdr hdr;

		/* Generic part of FPDU header */
		काष्ठा iwarp_ctrl ctrl;
		काष्ठा iwarp_ctrl_untagged c_untagged;
		काष्ठा iwarp_ctrl_tagged c_tagged;

		/* FPDU headers */
		काष्ठा iwarp_rdma_ग_लिखो rग_लिखो;
		काष्ठा iwarp_rdma_rreq rreq;
		काष्ठा iwarp_rdma_rresp rresp;
		काष्ठा iwarp_terminate terminate;
		काष्ठा iwarp_send send;
		काष्ठा iwarp_send_inv send_inv;

		/* complete लघु FPDUs */
		काष्ठा siw_send_pkt send_pkt;
		काष्ठा siw_ग_लिखो_pkt ग_लिखो_pkt;
		काष्ठा siw_rreq_pkt rreq_pkt;
		काष्ठा siw_rresp_pkt rresp_pkt;
	पूर्ण pkt;

	काष्ठा mpa_trailer trailer;
	/* DDP MSN क्रम untagged messages */
	u32 ddp_msn[RDMAP_UNTAGGED_QN_COUNT];

	क्रमागत siw_tx_ctx state;
	u16 ctrl_len; /* ddp+rdmap hdr */
	u16 ctrl_sent;
	पूर्णांक burst;
	पूर्णांक bytes_unsent; /* ddp payload bytes */

	काष्ठा shash_desc *mpa_crc_hd;

	u8 करो_crc : 1; /* करो crc क्रम segment */
	u8 use_sendpage : 1; /* send w/o copy */
	u8 tx_suspend : 1; /* stop sending DDP segs. */
	u8 pad : 2; /* # pad in current fpdu */
	u8 orq_fence : 1; /* ORQ full or Send fenced */
	u8 in_syscall : 1; /* TX out of user context */
	u8 zcopy_tx : 1; /* Use TCP_SENDPAGE अगर possible */
	u8 gso_seg_limit; /* Maximum segments क्रम GSO, 0 = unbound */

	u16 fpdu_len; /* len of FPDU to tx */
	अचिन्हित पूर्णांक tcp_seglen; /* reमुख्यing tcp seg space */

	काष्ठा siw_wqe wqe_active;

	पूर्णांक pbl_idx; /* Index पूर्णांकo current PBL */
	पूर्णांक sge_idx; /* current sge in tx */
	u32 sge_off; /* alपढ़ोy sent in curr. sge */
पूर्ण;

काष्ठा siw_qp अणु
	काष्ठा ib_qp base_qp;
	काष्ठा siw_device *sdev;
	काष्ठा kref ref;
	काष्ठा list_head devq;
	पूर्णांक tx_cpu;
	काष्ठा siw_qp_attrs attrs;

	काष्ठा siw_cep *cep;
	काष्ठा rw_semaphore state_lock;

	काष्ठा ib_pd *pd;
	काष्ठा siw_cq *scq;
	काष्ठा siw_cq *rcq;
	काष्ठा siw_srq *srq;

	काष्ठा siw_iwarp_tx tx_ctx; /* Transmit context */
	spinlock_t sq_lock;
	काष्ठा siw_sqe *sendq; /* send queue element array */
	uपूर्णांक32_t sq_get; /* consumer index पूर्णांकo sq array */
	uपूर्णांक32_t sq_put; /* kernel prod. index पूर्णांकo sq array */
	काष्ठा llist_node tx_list;

	काष्ठा siw_sqe *orq; /* outbound पढ़ो queue element array */
	spinlock_t orq_lock;
	uपूर्णांक32_t orq_get; /* consumer index पूर्णांकo orq array */
	uपूर्णांक32_t orq_put; /* shared producer index क्रम ORQ */

	काष्ठा siw_rx_stream rx_stream;
	काष्ठा siw_rx_fpdu *rx_fpdu;
	काष्ठा siw_rx_fpdu rx_tagged;
	काष्ठा siw_rx_fpdu rx_untagged;
	spinlock_t rq_lock;
	काष्ठा siw_rqe *recvq; /* recv queue element array */
	uपूर्णांक32_t rq_get; /* consumer index पूर्णांकo rq array */
	uपूर्णांक32_t rq_put; /* kernel prod. index पूर्णांकo rq array */

	काष्ठा siw_sqe *irq; /* inbound पढ़ो queue element array */
	uपूर्णांक32_t irq_get; /* consumer index पूर्णांकo irq array */
	uपूर्णांक32_t irq_put; /* producer index पूर्णांकo irq array */
	पूर्णांक irq_burst;

	काष्ठा अणु /* inक्रमmation to be carried in TERMINATE pkt, अगर valid */
		u8 valid;
		u8 in_tx;
		u8 layer : 4, etype : 4;
		u8 ecode;
	पूर्ण term_info;
	काष्ठा rdma_user_mmap_entry *sq_entry; /* mmap info क्रम SQE array */
	काष्ठा rdma_user_mmap_entry *rq_entry; /* mmap info क्रम RQE array */
	काष्ठा rcu_head rcu;
पूर्ण;

/* helper macros */
#घोषणा rx_qp(rx) container_of(rx, काष्ठा siw_qp, rx_stream)
#घोषणा tx_qp(tx) container_of(tx, काष्ठा siw_qp, tx_ctx)
#घोषणा tx_wqe(qp) (&(qp)->tx_ctx.wqe_active)
#घोषणा rx_wqe(rctx) (&(rctx)->wqe_active)
#घोषणा rx_mem(rctx) ((rctx)->wqe_active.mem[0])
#घोषणा tx_type(wqe) ((wqe)->sqe.opcode)
#घोषणा rx_type(wqe) ((wqe)->rqe.opcode)
#घोषणा tx_flags(wqe) ((wqe)->sqe.flags)

काष्ठा iwarp_msg_info अणु
	पूर्णांक hdr_len;
	काष्ठा iwarp_ctrl ctrl;
	पूर्णांक (*rx_data)(काष्ठा siw_qp *qp);
पूर्ण;

काष्ठा siw_user_mmap_entry अणु
	काष्ठा rdma_user_mmap_entry rdma_entry;
	व्योम *address;
पूर्ण;

/* Global siw parameters. Currently set in siw_मुख्य.c */
बाह्य स्थिर bool zcopy_tx;
बाह्य स्थिर bool try_gso;
बाह्य स्थिर bool loopback_enabled;
बाह्य स्थिर bool mpa_crc_required;
बाह्य स्थिर bool mpa_crc_strict;
बाह्य स्थिर bool siw_tcp_nagle;
बाह्य u_अक्षर mpa_version;
बाह्य स्थिर bool peer_to_peer;
बाह्य काष्ठा task_काष्ठा *siw_tx_thपढ़ो[];

बाह्य काष्ठा crypto_shash *siw_crypto_shash;
बाह्य काष्ठा iwarp_msg_info iwarp_pktinfo[RDMAP_TERMINATE + 1];

/* QP general functions */
पूर्णांक siw_qp_modअगरy(काष्ठा siw_qp *qp, काष्ठा siw_qp_attrs *attr,
		  क्रमागत siw_qp_attr_mask mask);
पूर्णांक siw_qp_mpa_rts(काष्ठा siw_qp *qp, क्रमागत mpa_v2_ctrl ctrl);
व्योम siw_qp_llp_बंद(काष्ठा siw_qp *qp);
व्योम siw_qp_cm_drop(काष्ठा siw_qp *qp, पूर्णांक schedule);
व्योम siw_send_terminate(काष्ठा siw_qp *qp);

व्योम siw_qp_get_ref(काष्ठा ib_qp *qp);
व्योम siw_qp_put_ref(काष्ठा ib_qp *qp);
पूर्णांक siw_qp_add(काष्ठा siw_device *sdev, काष्ठा siw_qp *qp);
व्योम siw_मुक्त_qp(काष्ठा kref *ref);

व्योम siw_init_terminate(काष्ठा siw_qp *qp, क्रमागत term_elayer layer,
			u8 etype, u8 ecode, पूर्णांक in_tx);
क्रमागत ddp_ecode siw_tagged_error(क्रमागत siw_access_state state);
क्रमागत rdmap_ecode siw_rdmap_error(क्रमागत siw_access_state state);

व्योम siw_पढ़ो_to_orq(काष्ठा siw_sqe *rreq, काष्ठा siw_sqe *sqe);
पूर्णांक siw_sqe_complete(काष्ठा siw_qp *qp, काष्ठा siw_sqe *sqe, u32 bytes,
		     क्रमागत siw_wc_status status);
पूर्णांक siw_rqe_complete(काष्ठा siw_qp *qp, काष्ठा siw_rqe *rqe, u32 bytes,
		     u32 inval_stag, क्रमागत siw_wc_status status);
व्योम siw_qp_llp_data_पढ़ोy(काष्ठा sock *sk);
व्योम siw_qp_llp_ग_लिखो_space(काष्ठा sock *sk);

/* QP TX path functions */
पूर्णांक siw_run_sq(व्योम *arg);
पूर्णांक siw_qp_sq_process(काष्ठा siw_qp *qp);
पूर्णांक siw_sq_start(काष्ठा siw_qp *qp);
पूर्णांक siw_activate_tx(काष्ठा siw_qp *qp);
व्योम siw_stop_tx_thपढ़ो(पूर्णांक nr_cpu);
पूर्णांक siw_get_tx_cpu(काष्ठा siw_device *sdev);
व्योम siw_put_tx_cpu(पूर्णांक cpu);

/* QP RX path functions */
पूर्णांक siw_proc_send(काष्ठा siw_qp *qp);
पूर्णांक siw_proc_rreq(काष्ठा siw_qp *qp);
पूर्णांक siw_proc_rresp(काष्ठा siw_qp *qp);
पूर्णांक siw_proc_ग_लिखो(काष्ठा siw_qp *qp);
पूर्णांक siw_proc_terminate(काष्ठा siw_qp *qp);

पूर्णांक siw_tcp_rx_data(पढ़ो_descriptor_t *rd_desc, काष्ठा sk_buff *skb,
		    अचिन्हित पूर्णांक off, माप_प्रकार len);

अटल अंतरभूत व्योम set_rx_fpdu_context(काष्ठा siw_qp *qp, u8 opcode)
अणु
	अगर (opcode == RDMAP_RDMA_WRITE || opcode == RDMAP_RDMA_READ_RESP)
		qp->rx_fpdu = &qp->rx_tagged;
	अन्यथा
		qp->rx_fpdu = &qp->rx_untagged;

	qp->rx_stream.rdmap_op = opcode;
पूर्ण

अटल अंतरभूत काष्ठा siw_ucontext *to_siw_ctx(काष्ठा ib_ucontext *base_ctx)
अणु
	वापस container_of(base_ctx, काष्ठा siw_ucontext, base_ucontext);
पूर्ण

अटल अंतरभूत काष्ठा siw_qp *to_siw_qp(काष्ठा ib_qp *base_qp)
अणु
	वापस container_of(base_qp, काष्ठा siw_qp, base_qp);
पूर्ण

अटल अंतरभूत काष्ठा siw_cq *to_siw_cq(काष्ठा ib_cq *base_cq)
अणु
	वापस container_of(base_cq, काष्ठा siw_cq, base_cq);
पूर्ण

अटल अंतरभूत काष्ठा siw_srq *to_siw_srq(काष्ठा ib_srq *base_srq)
अणु
	वापस container_of(base_srq, काष्ठा siw_srq, base_srq);
पूर्ण

अटल अंतरभूत काष्ठा siw_device *to_siw_dev(काष्ठा ib_device *base_dev)
अणु
	वापस container_of(base_dev, काष्ठा siw_device, base_dev);
पूर्ण

अटल अंतरभूत काष्ठा siw_mr *to_siw_mr(काष्ठा ib_mr *base_mr)
अणु
	वापस container_of(base_mr, काष्ठा siw_mr, base_mr);
पूर्ण

अटल अंतरभूत काष्ठा siw_user_mmap_entry *
to_siw_mmap_entry(काष्ठा rdma_user_mmap_entry *rdma_mmap)
अणु
	वापस container_of(rdma_mmap, काष्ठा siw_user_mmap_entry, rdma_entry);
पूर्ण

अटल अंतरभूत काष्ठा siw_qp *siw_qp_id2obj(काष्ठा siw_device *sdev, पूर्णांक id)
अणु
	काष्ठा siw_qp *qp;

	rcu_पढ़ो_lock();
	qp = xa_load(&sdev->qp_xa, id);
	अगर (likely(qp && kref_get_unless_zero(&qp->ref))) अणु
		rcu_पढ़ो_unlock();
		वापस qp;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण

अटल अंतरभूत u32 qp_id(काष्ठा siw_qp *qp)
अणु
	वापस qp->base_qp.qp_num;
पूर्ण

अटल अंतरभूत व्योम siw_qp_get(काष्ठा siw_qp *qp)
अणु
	kref_get(&qp->ref);
पूर्ण

अटल अंतरभूत व्योम siw_qp_put(काष्ठा siw_qp *qp)
अणु
	kref_put(&qp->ref, siw_मुक्त_qp);
पूर्ण

अटल अंतरभूत पूर्णांक siw_sq_empty(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_sqe *sqe = &qp->sendq[qp->sq_get % qp->attrs.sq_size];

	वापस READ_ONCE(sqe->flags) == 0;
पूर्ण

अटल अंतरभूत काष्ठा siw_sqe *sq_get_next(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_sqe *sqe = &qp->sendq[qp->sq_get % qp->attrs.sq_size];

	अगर (READ_ONCE(sqe->flags) & SIW_WQE_VALID)
		वापस sqe;

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा siw_sqe *orq_get_current(काष्ठा siw_qp *qp)
अणु
	वापस &qp->orq[qp->orq_get % qp->attrs.orq_size];
पूर्ण

अटल अंतरभूत काष्ठा siw_sqe *orq_get_tail(काष्ठा siw_qp *qp)
अणु
	वापस &qp->orq[qp->orq_put % qp->attrs.orq_size];
पूर्ण

अटल अंतरभूत काष्ठा siw_sqe *orq_get_मुक्त(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_sqe *orq_e = orq_get_tail(qp);

	अगर (READ_ONCE(orq_e->flags) == 0)
		वापस orq_e;

	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक siw_orq_empty(काष्ठा siw_qp *qp)
अणु
	वापस qp->orq[qp->orq_get % qp->attrs.orq_size].flags == 0 ? 1 : 0;
पूर्ण

अटल अंतरभूत काष्ठा siw_sqe *irq_alloc_मुक्त(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_sqe *irq_e = &qp->irq[qp->irq_put % qp->attrs.irq_size];

	अगर (READ_ONCE(irq_e->flags) == 0) अणु
		qp->irq_put++;
		वापस irq_e;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत __wsum siw_csum_update(स्थिर व्योम *buff, पूर्णांक len, __wsum sum)
अणु
	वापस (__क्रमce __wsum)crc32c((__क्रमce __u32)sum, buff, len);
पूर्ण

अटल अंतरभूत __wsum siw_csum_combine(__wsum csum, __wsum csum2, पूर्णांक offset,
				      पूर्णांक len)
अणु
	वापस (__क्रमce __wsum)__crc32c_le_combine((__क्रमce __u32)csum,
						   (__क्रमce __u32)csum2, len);
पूर्ण

अटल अंतरभूत व्योम siw_crc_skb(काष्ठा siw_rx_stream *srx, अचिन्हित पूर्णांक len)
अणु
	स्थिर काष्ठा skb_checksum_ops siw_cs_ops = अणु
		.update = siw_csum_update,
		.combine = siw_csum_combine,
	पूर्ण;
	__wsum crc = *(u32 *)shash_desc_ctx(srx->mpa_crc_hd);

	crc = __skb_checksum(srx->skb, srx->skb_offset, len, crc,
			     &siw_cs_ops);
	*(u32 *)shash_desc_ctx(srx->mpa_crc_hd) = crc;
पूर्ण

#घोषणा siw_dbg(ibdev, fmt, ...)                                               \
	ibdev_dbg(ibdev, "%s: " fmt, __func__, ##__VA_ARGS__)

#घोषणा siw_dbg_qp(qp, fmt, ...)                                               \
	ibdev_dbg(&qp->sdev->base_dev, "QP[%u] %s: " fmt, qp_id(qp), __func__, \
		  ##__VA_ARGS__)

#घोषणा siw_dbg_cq(cq, fmt, ...)                                               \
	ibdev_dbg(cq->base_cq.device, "CQ[%u] %s: " fmt, cq->id, __func__,     \
		  ##__VA_ARGS__)

#घोषणा siw_dbg_pd(pd, fmt, ...)                                               \
	ibdev_dbg(pd->device, "PD[%u] %s: " fmt, pd->res.id, __func__,         \
		  ##__VA_ARGS__)

#घोषणा siw_dbg_mem(mem, fmt, ...)                                             \
	ibdev_dbg(&mem->sdev->base_dev,                                        \
		  "MEM[0x%08x] %s: " fmt, mem->stag, __func__, ##__VA_ARGS__)

#घोषणा siw_dbg_cep(cep, fmt, ...)                                             \
	ibdev_dbg(&cep->sdev->base_dev, "CEP[0x%pK] %s: " fmt,                 \
		  cep, __func__, ##__VA_ARGS__)

व्योम siw_cq_flush(काष्ठा siw_cq *cq);
व्योम siw_sq_flush(काष्ठा siw_qp *qp);
व्योम siw_rq_flush(काष्ठा siw_qp *qp);
पूर्णांक siw_reap_cqe(काष्ठा siw_cq *cq, काष्ठा ib_wc *wc);

#पूर्ण_अगर
