<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2013-2020, Mellanox Technologies inc. All rights reserved.
 * Copyright (c) 2020, Intel Corporation. All rights reserved.
 */

#अगर_अघोषित MLX5_IB_H
#घोषणा MLX5_IB_H

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_smi.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/cq.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <linux/mlx5/qp.h>
#समावेश <linux/types.h>
#समावेश <linux/mlx5/transobj.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/mlx5-abi.h>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश <rdma/mlx5_user_ioctl_cmds.h>
#समावेश <rdma/mlx5_user_ioctl_verbs.h>

#समावेश "srq.h"

#घोषणा mlx5_ib_dbg(_dev, क्रमmat, arg...)                                      \
	dev_dbg(&(_dev)->ib_dev.dev, "%s:%d:(pid %d): " क्रमmat, __func__,      \
		__LINE__, current->pid, ##arg)

#घोषणा mlx5_ib_err(_dev, क्रमmat, arg...)                                      \
	dev_err(&(_dev)->ib_dev.dev, "%s:%d:(pid %d): " क्रमmat, __func__,      \
		__LINE__, current->pid, ##arg)

#घोषणा mlx5_ib_warn(_dev, क्रमmat, arg...)                                     \
	dev_warn(&(_dev)->ib_dev.dev, "%s:%d:(pid %d): " क्रमmat, __func__,     \
		 __LINE__, current->pid, ##arg)

#घोषणा MLX5_IB_DEFAULT_UIDX 0xffffff
#घोषणा MLX5_USER_ASSIGNED_UIDX_MASK __mlx5_mask(qpc, user_index)

अटल __always_अंतरभूत अचिन्हित दीर्घ
__mlx5_log_page_माप_प्रकारo_biपंचांगap(अचिन्हित पूर्णांक log_pgsz_bits,
			       अचिन्हित पूर्णांक pgsz_shअगरt)
अणु
	अचिन्हित पूर्णांक largest_pg_shअगरt =
		min_t(अचिन्हित दीर्घ, (1ULL << log_pgsz_bits) - 1 + pgsz_shअगरt,
		      BITS_PER_LONG - 1);

	/*
	 * Despite a command allowing it, the device करोes not support lower than
	 * 4k page size.
	 */
	pgsz_shअगरt = max_t(अचिन्हित पूर्णांक, MLX5_ADAPTER_PAGE_SHIFT, pgsz_shअगरt);
	वापस GENMASK(largest_pg_shअगरt, pgsz_shअगरt);
पूर्ण

/*
 * For mkc users, instead of a page_offset the command has a start_iova which
 * specअगरies both the page_offset and the on-the-wire IOVA
 */
#घोषणा mlx5_umem_find_best_pgsz(umem, typ, log_pgsz_fld, pgsz_shअगरt, iova)    \
	ib_umem_find_best_pgsz(umem,                                           \
			       __mlx5_log_page_माप_प्रकारo_biपंचांगap(                 \
				       __mlx5_bit_sz(typ, log_pgsz_fld),       \
				       pgsz_shअगरt),                            \
			       iova)

अटल __always_अंतरभूत अचिन्हित दीर्घ
__mlx5_page_offset_to_biपंचांगask(अचिन्हित पूर्णांक page_offset_bits,
			      अचिन्हित पूर्णांक offset_shअगरt)
अणु
	अचिन्हित पूर्णांक largest_offset_shअगरt =
		min_t(अचिन्हित दीर्घ, page_offset_bits - 1 + offset_shअगरt,
		      BITS_PER_LONG - 1);

	वापस GENMASK(largest_offset_shअगरt, offset_shअगरt);
पूर्ण

/*
 * QP/CQ/WQ/etc type commands take a page offset that satisअगरies:
 *   page_offset_quantized * (page_size/scale) = page_offset
 * Which restricts allowed page sizes to ones that satisअगरy the above.
 */
अचिन्हित दीर्घ __mlx5_umem_find_best_quantized_pgoff(
	काष्ठा ib_umem *umem, अचिन्हित दीर्घ pgsz_biपंचांगap,
	अचिन्हित पूर्णांक page_offset_bits, u64 pgoff_biपंचांगask, अचिन्हित पूर्णांक scale,
	अचिन्हित पूर्णांक *page_offset_quantized);
#घोषणा mlx5_umem_find_best_quantized_pgoff(umem, typ, log_pgsz_fld,           \
					    pgsz_shअगरt, page_offset_fld,       \
					    scale, page_offset_quantized)      \
	__mlx5_umem_find_best_quantized_pgoff(                                 \
		umem,                                                          \
		__mlx5_log_page_माप_प्रकारo_biपंचांगap(                                \
			__mlx5_bit_sz(typ, log_pgsz_fld), pgsz_shअगरt),         \
		__mlx5_bit_sz(typ, page_offset_fld),                           \
		GENMASK(31, order_base_2(scale)), scale,                       \
		page_offset_quantized)

#घोषणा mlx5_umem_find_best_cq_quantized_pgoff(umem, typ, log_pgsz_fld,        \
					       pgsz_shअगरt, page_offset_fld,    \
					       scale, page_offset_quantized)   \
	__mlx5_umem_find_best_quantized_pgoff(                                 \
		umem,                                                          \
		__mlx5_log_page_माप_प्रकारo_biपंचांगap(                                \
			__mlx5_bit_sz(typ, log_pgsz_fld), pgsz_shअगरt),         \
		__mlx5_bit_sz(typ, page_offset_fld), 0, scale,                 \
		page_offset_quantized)

क्रमागत अणु
	MLX5_IB_MMAP_OFFSET_START = 9,
	MLX5_IB_MMAP_OFFSET_END = 255,
पूर्ण;

क्रमागत अणु
	MLX5_IB_MMAP_CMD_SHIFT	= 8,
	MLX5_IB_MMAP_CMD_MASK	= 0xff,
पूर्ण;

क्रमागत अणु
	MLX5_RES_SCAT_DATA32_CQE	= 0x1,
	MLX5_RES_SCAT_DATA64_CQE	= 0x2,
	MLX5_REQ_SCAT_DATA32_CQE	= 0x11,
	MLX5_REQ_SCAT_DATA64_CQE	= 0x22,
पूर्ण;

क्रमागत mlx5_ib_mad_अगरc_flags अणु
	MLX5_MAD_IFC_IGNORE_MKEY	= 1,
	MLX5_MAD_IFC_IGNORE_BKEY	= 2,
	MLX5_MAD_IFC_NET_VIEW		= 4,
पूर्ण;

क्रमागत अणु
	MLX5_CROSS_CHANNEL_BFREG         = 0,
पूर्ण;

क्रमागत अणु
	MLX5_CQE_VERSION_V0,
	MLX5_CQE_VERSION_V1,
पूर्ण;

क्रमागत अणु
	MLX5_TM_MAX_RNDV_MSG_SIZE	= 64,
	MLX5_TM_MAX_SGE			= 1,
पूर्ण;

क्रमागत अणु
	MLX5_IB_INVALID_UAR_INDEX	= BIT(31),
	MLX5_IB_INVALID_BFREG		= BIT(31),
पूर्ण;

क्रमागत अणु
	MLX5_MAX_MEMIC_PAGES = 0x100,
	MLX5_MEMIC_ALLOC_SIZE_MASK = 0x3f,
पूर्ण;

क्रमागत अणु
	MLX5_MEMIC_BASE_ALIGN	= 6,
	MLX5_MEMIC_BASE_SIZE	= 1 << MLX5_MEMIC_BASE_ALIGN,
पूर्ण;

क्रमागत mlx5_ib_mmap_type अणु
	MLX5_IB_MMAP_TYPE_MEMIC = 1,
	MLX5_IB_MMAP_TYPE_VAR = 2,
	MLX5_IB_MMAP_TYPE_UAR_WC = 3,
	MLX5_IB_MMAP_TYPE_UAR_NC = 4,
	MLX5_IB_MMAP_TYPE_MEMIC_OP = 5,
पूर्ण;

काष्ठा mlx5_bfreg_info अणु
	u32 *sys_pages;
	पूर्णांक num_low_latency_bfregs;
	अचिन्हित पूर्णांक *count;

	/*
	 * protect bfreg allocation data काष्ठाs
	 */
	काष्ठा mutex lock;
	u32 ver;
	u8 lib_uar_4k : 1;
	u8 lib_uar_dyn : 1;
	u32 num_sys_pages;
	u32 num_अटल_sys_pages;
	u32 total_num_bfregs;
	u32 num_dyn_bfregs;
पूर्ण;

काष्ठा mlx5_ib_ucontext अणु
	काष्ठा ib_ucontext	ibucontext;
	काष्ठा list_head	db_page_list;

	/* protect करोorbell record alloc/मुक्त
	 */
	काष्ठा mutex		db_page_mutex;
	काष्ठा mlx5_bfreg_info	bfregi;
	u8			cqe_version;
	/* Transport Doमुख्य number */
	u32			tdn;

	u64			lib_caps;
	u16			devx_uid;
	/* For RoCE LAG TX affinity */
	atomic_t		tx_port_affinity;
पूर्ण;

अटल अंतरभूत काष्ठा mlx5_ib_ucontext *to_mucontext(काष्ठा ib_ucontext *ibucontext)
अणु
	वापस container_of(ibucontext, काष्ठा mlx5_ib_ucontext, ibucontext);
पूर्ण

काष्ठा mlx5_ib_pd अणु
	काष्ठा ib_pd		ibpd;
	u32			pdn;
	u16			uid;
पूर्ण;

क्रमागत अणु
	MLX5_IB_FLOW_ACTION_MODIFY_HEADER,
	MLX5_IB_FLOW_ACTION_PACKET_REFORMAT,
	MLX5_IB_FLOW_ACTION_DECAP,
पूर्ण;

#घोषणा MLX5_IB_FLOW_MCAST_PRIO		(MLX5_BY_PASS_NUM_PRIOS - 1)
#घोषणा MLX5_IB_FLOW_LAST_PRIO		(MLX5_BY_PASS_NUM_REGULAR_PRIOS - 1)
#अगर (MLX5_IB_FLOW_LAST_PRIO <= 0)
#त्रुटि "Invalid number of bypass priorities"
#पूर्ण_अगर
#घोषणा MLX5_IB_FLOW_LEFTOVERS_PRIO	(MLX5_IB_FLOW_MCAST_PRIO + 1)

#घोषणा MLX5_IB_NUM_FLOW_FT		(MLX5_IB_FLOW_LEFTOVERS_PRIO + 1)
#घोषणा MLX5_IB_NUM_SNIFFER_FTS		2
#घोषणा MLX5_IB_NUM_EGRESS_FTS		1
काष्ठा mlx5_ib_flow_prio अणु
	काष्ठा mlx5_flow_table		*flow_table;
	अचिन्हित पूर्णांक			refcount;
पूर्ण;

काष्ठा mlx5_ib_flow_handler अणु
	काष्ठा list_head		list;
	काष्ठा ib_flow			ibflow;
	काष्ठा mlx5_ib_flow_prio	*prio;
	काष्ठा mlx5_flow_handle		*rule;
	काष्ठा ib_counters		*ibcounters;
	काष्ठा mlx5_ib_dev		*dev;
	काष्ठा mlx5_ib_flow_matcher	*flow_matcher;
पूर्ण;

काष्ठा mlx5_ib_flow_matcher अणु
	काष्ठा mlx5_ib_match_params matcher_mask;
	पूर्णांक			mask_len;
	क्रमागत mlx5_ib_flow_type	flow_type;
	क्रमागत mlx5_flow_namespace_type ns_type;
	u16			priority;
	काष्ठा mlx5_core_dev	*mdev;
	atomic_t		usecnt;
	u8			match_criteria_enable;
पूर्ण;

काष्ठा mlx5_ib_pp अणु
	u16 index;
	काष्ठा mlx5_core_dev *mdev;
पूर्ण;

काष्ठा mlx5_ib_flow_db अणु
	काष्ठा mlx5_ib_flow_prio	prios[MLX5_IB_NUM_FLOW_FT];
	काष्ठा mlx5_ib_flow_prio	egress_prios[MLX5_IB_NUM_FLOW_FT];
	काष्ठा mlx5_ib_flow_prio	snअगरfer[MLX5_IB_NUM_SNIFFER_FTS];
	काष्ठा mlx5_ib_flow_prio	egress[MLX5_IB_NUM_EGRESS_FTS];
	काष्ठा mlx5_ib_flow_prio	fdb;
	काष्ठा mlx5_ib_flow_prio	rdma_rx[MLX5_IB_NUM_FLOW_FT];
	काष्ठा mlx5_ib_flow_prio	rdma_tx[MLX5_IB_NUM_FLOW_FT];
	काष्ठा mlx5_flow_table		*lag_demux_ft;
	/* Protect flow steering bypass flow tables
	 * when add/del flow rules.
	 * only single add/removal of flow steering rule could be करोne
	 * simultaneously.
	 */
	काष्ठा mutex			lock;
पूर्ण;

/* Use macros here so that करोn't have to duplicate
 * क्रमागत ib_send_flags and क्रमागत ib_qp_type क्रम low-level driver
 */

#घोषणा MLX5_IB_SEND_UMR_ENABLE_MR	       (IB_SEND_RESERVED_START << 0)
#घोषणा MLX5_IB_SEND_UMR_DISABLE_MR	       (IB_SEND_RESERVED_START << 1)
#घोषणा MLX5_IB_SEND_UMR_FAIL_IF_FREE	       (IB_SEND_RESERVED_START << 2)
#घोषणा MLX5_IB_SEND_UMR_UPDATE_XLT	       (IB_SEND_RESERVED_START << 3)
#घोषणा MLX5_IB_SEND_UMR_UPDATE_TRANSLATION    (IB_SEND_RESERVED_START << 4)
#घोषणा MLX5_IB_SEND_UMR_UPDATE_PD_ACCESS       IB_SEND_RESERVED_END

#घोषणा MLX5_IB_QPT_REG_UMR	IB_QPT_RESERVED1
/*
 * IB_QPT_GSI creates the software wrapper around GSI, and MLX5_IB_QPT_HW_GSI
 * creates the actual hardware QP.
 */
#घोषणा MLX5_IB_QPT_HW_GSI	IB_QPT_RESERVED2
#घोषणा MLX5_IB_QPT_DCI		IB_QPT_RESERVED3
#घोषणा MLX5_IB_QPT_DCT		IB_QPT_RESERVED4
#घोषणा MLX5_IB_WR_UMR		IB_WR_RESERVED1

#घोषणा MLX5_IB_UMR_OCTOWORD	       16
#घोषणा MLX5_IB_UMR_XLT_ALIGNMENT      64

#घोषणा MLX5_IB_UPD_XLT_ZAP	      BIT(0)
#घोषणा MLX5_IB_UPD_XLT_ENABLE	      BIT(1)
#घोषणा MLX5_IB_UPD_XLT_ATOMIC	      BIT(2)
#घोषणा MLX5_IB_UPD_XLT_ADDR	      BIT(3)
#घोषणा MLX5_IB_UPD_XLT_PD	      BIT(4)
#घोषणा MLX5_IB_UPD_XLT_ACCESS	      BIT(5)
#घोषणा MLX5_IB_UPD_XLT_INसूचीECT      BIT(6)

/* Private QP creation flags to be passed in ib_qp_init_attr.create_flags.
 *
 * These flags are पूर्णांकended क्रम पूर्णांकernal use by the mlx5_ib driver, and they
 * rely on the range reserved क्रम that use in the ib_qp_create_flags क्रमागत.
 */
#घोषणा MLX5_IB_QP_CREATE_SQPN_QP1	IB_QP_CREATE_RESERVED_START
#घोषणा MLX5_IB_QP_CREATE_WC_TEST	(IB_QP_CREATE_RESERVED_START << 1)

काष्ठा wr_list अणु
	u16	opcode;
	u16	next;
पूर्ण;

क्रमागत mlx5_ib_rq_flags अणु
	MLX5_IB_RQ_CVLAN_STRIPPING	= 1 << 0,
	MLX5_IB_RQ_PCI_WRITE_END_PADDING	= 1 << 1,
पूर्ण;

काष्ठा mlx5_ib_wq अणु
	काष्ठा mlx5_frag_buf_ctrl fbc;
	u64		       *wrid;
	u32		       *wr_data;
	काष्ठा wr_list	       *w_list;
	अचिन्हित	       *wqe_head;
	u16		        unsig_count;

	/* serialize post to the work queue
	 */
	spinlock_t		lock;
	पूर्णांक			wqe_cnt;
	पूर्णांक			max_post;
	पूर्णांक			max_gs;
	पूर्णांक			offset;
	पूर्णांक			wqe_shअगरt;
	अचिन्हित		head;
	अचिन्हित		tail;
	u16			cur_post;
	u16			last_poll;
	व्योम			*cur_edge;
पूर्ण;

क्रमागत mlx5_ib_wq_flags अणु
	MLX5_IB_WQ_FLAGS_DELAY_DROP = 0x1,
	MLX5_IB_WQ_FLAGS_STRIDING_RQ = 0x2,
पूर्ण;

#घोषणा MLX5_MIN_SINGLE_WQE_LOG_NUM_STRIDES 9
#घोषणा MLX5_MAX_SINGLE_WQE_LOG_NUM_STRIDES 16
#घोषणा MLX5_MIN_SINGLE_STRIDE_LOG_NUM_BYTES 6
#घोषणा MLX5_MAX_SINGLE_STRIDE_LOG_NUM_BYTES 13
#घोषणा MLX5_EXT_MIN_SINGLE_WQE_LOG_NUM_STRIDES 3

काष्ठा mlx5_ib_rwq अणु
	काष्ठा ib_wq		ibwq;
	काष्ठा mlx5_core_qp	core_qp;
	u32			rq_num_pas;
	u32			log_rq_stride;
	u32			log_rq_size;
	u32			rq_page_offset;
	u32			log_page_size;
	u32			log_num_strides;
	u32			two_byte_shअगरt_en;
	u32			single_stride_log_num_of_bytes;
	काष्ठा ib_umem		*umem;
	माप_प्रकार			buf_size;
	अचिन्हित पूर्णांक		page_shअगरt;
	काष्ठा mlx5_db		db;
	u32			user_index;
	u32			wqe_count;
	u32			wqe_shअगरt;
	पूर्णांक			wq_sig;
	u32			create_flags; /* Use क्रमागत mlx5_ib_wq_flags */
पूर्ण;

काष्ठा mlx5_ib_rwq_ind_table अणु
	काष्ठा ib_rwq_ind_table ib_rwq_ind_tbl;
	u32			rqtn;
	u16			uid;
पूर्ण;

काष्ठा mlx5_ib_ubuffer अणु
	काष्ठा ib_umem	       *umem;
	पूर्णांक			buf_size;
	u64			buf_addr;
पूर्ण;

काष्ठा mlx5_ib_qp_base अणु
	काष्ठा mlx5_ib_qp	*container_mibqp;
	काष्ठा mlx5_core_qp	mqp;
	काष्ठा mlx5_ib_ubuffer	ubuffer;
पूर्ण;

काष्ठा mlx5_ib_qp_trans अणु
	काष्ठा mlx5_ib_qp_base	base;
	u16			xrcdn;
	u32			alt_port;
	u8			atomic_rd_en;
	u8			resp_depth;
पूर्ण;

काष्ठा mlx5_ib_rss_qp अणु
	u32	tirn;
पूर्ण;

काष्ठा mlx5_ib_rq अणु
	काष्ठा mlx5_ib_qp_base base;
	काष्ठा mlx5_ib_wq	*rq;
	काष्ठा mlx5_ib_ubuffer	ubuffer;
	काष्ठा mlx5_db		*करोorbell;
	u32			tirn;
	u8			state;
	u32			flags;
पूर्ण;

काष्ठा mlx5_ib_sq अणु
	काष्ठा mlx5_ib_qp_base base;
	काष्ठा mlx5_ib_wq	*sq;
	काष्ठा mlx5_ib_ubuffer  ubuffer;
	काष्ठा mlx5_db		*करोorbell;
	काष्ठा mlx5_flow_handle	*flow_rule;
	u32			tisn;
	u8			state;
पूर्ण;

काष्ठा mlx5_ib_raw_packet_qp अणु
	काष्ठा mlx5_ib_sq sq;
	काष्ठा mlx5_ib_rq rq;
पूर्ण;

काष्ठा mlx5_bf अणु
	पूर्णांक			buf_size;
	अचिन्हित दीर्घ		offset;
	काष्ठा mlx5_sq_bfreg   *bfreg;
पूर्ण;

काष्ठा mlx5_ib_dct अणु
	काष्ठा mlx5_core_dct    mdct;
	u32                     *in;
पूर्ण;

काष्ठा mlx5_ib_gsi_qp अणु
	काष्ठा ib_qp *rx_qp;
	u32 port_num;
	काष्ठा ib_qp_cap cap;
	काष्ठा ib_cq *cq;
	काष्ठा mlx5_ib_gsi_wr *outstanding_wrs;
	u32 outstanding_pi, outstanding_ci;
	पूर्णांक num_qps;
	/* Protects access to the tx_qps. Post send operations synchronize
	 * with tx_qp creation in setup_qp(). Also protects the
	 * outstanding_wrs array and indices.
	 */
	spinlock_t lock;
	काष्ठा ib_qp **tx_qps;
पूर्ण;

काष्ठा mlx5_ib_qp अणु
	काष्ठा ib_qp		ibqp;
	जोड़ अणु
		काष्ठा mlx5_ib_qp_trans trans_qp;
		काष्ठा mlx5_ib_raw_packet_qp raw_packet_qp;
		काष्ठा mlx5_ib_rss_qp rss_qp;
		काष्ठा mlx5_ib_dct dct;
		काष्ठा mlx5_ib_gsi_qp gsi;
	पूर्ण;
	काष्ठा mlx5_frag_buf	buf;

	काष्ठा mlx5_db		db;
	काष्ठा mlx5_ib_wq	rq;

	u8			sq_संकेत_bits;
	u8			next_fence;
	काष्ठा mlx5_ib_wq	sq;

	/* serialize qp state modअगरications
	 */
	काष्ठा mutex		mutex;
	/* cached variant of create_flags from काष्ठा ib_qp_init_attr */
	u32			flags;
	u32			port;
	u8			state;
	पूर्णांक			max_अंतरभूत_data;
	काष्ठा mlx5_bf	        bf;
	u8			has_rq:1;
	u8			is_rss:1;

	/* only क्रम user space QPs. For kernel
	 * we have it from the bf object
	 */
	पूर्णांक			bfregn;

	काष्ठा list_head	qps_list;
	काष्ठा list_head	cq_recv_list;
	काष्ठा list_head	cq_send_list;
	काष्ठा mlx5_rate_limit	rl;
	u32                     underlay_qpn;
	u32			flags_en;
	/*
	 * IB/core करोesn't store low-level QP types, so
	 * store both MLX and IBTA types in the field below.
	 * IB_QPT_DRIVER will be अवरोध to DCI/DCT subtypes.
	 */
	क्रमागत ib_qp_type		type;
	/* A flag to indicate अगर there's a new counter is configured
	 * but not take effective
	 */
	u32                     counter_pending;
	u16			gsi_lag_port;
पूर्ण;

काष्ठा mlx5_ib_cq_buf अणु
	काष्ठा mlx5_frag_buf_ctrl fbc;
	काष्ठा mlx5_frag_buf    frag_buf;
	काष्ठा ib_umem		*umem;
	पूर्णांक			cqe_size;
	पूर्णांक			nent;
पूर्ण;

काष्ठा mlx5_umr_wr अणु
	काष्ठा ib_send_wr		wr;
	u64				virt_addr;
	u64				offset;
	काष्ठा ib_pd		       *pd;
	अचिन्हित पूर्णांक			page_shअगरt;
	अचिन्हित पूर्णांक			xlt_size;
	u64				length;
	पूर्णांक				access_flags;
	u32				mkey;
	u8				ignore_मुक्त_state:1;
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा mlx5_umr_wr *umr_wr(स्थिर काष्ठा ib_send_wr *wr)
अणु
	वापस container_of(wr, काष्ठा mlx5_umr_wr, wr);
पूर्ण

क्रमागत mlx5_ib_cq_pr_flags अणु
	MLX5_IB_CQ_PR_FLAGS_CQE_128_PAD	= 1 << 0,
पूर्ण;

काष्ठा mlx5_ib_cq अणु
	काष्ठा ib_cq		ibcq;
	काष्ठा mlx5_core_cq	mcq;
	काष्ठा mlx5_ib_cq_buf	buf;
	काष्ठा mlx5_db		db;

	/* serialize access to the CQ
	 */
	spinlock_t		lock;

	/* protect resize cq
	 */
	काष्ठा mutex		resize_mutex;
	काष्ठा mlx5_ib_cq_buf  *resize_buf;
	काष्ठा ib_umem	       *resize_umem;
	पूर्णांक			cqe_size;
	काष्ठा list_head	list_send_qp;
	काष्ठा list_head	list_recv_qp;
	u32			create_flags;
	काष्ठा list_head	wc_list;
	क्रमागत ib_cq_notअगरy_flags notअगरy_flags;
	काष्ठा work_काष्ठा	notअगरy_work;
	u16			निजी_flags; /* Use mlx5_ib_cq_pr_flags */
पूर्ण;

काष्ठा mlx5_ib_wc अणु
	काष्ठा ib_wc wc;
	काष्ठा list_head list;
पूर्ण;

काष्ठा mlx5_ib_srq अणु
	काष्ठा ib_srq		ibsrq;
	काष्ठा mlx5_core_srq	msrq;
	काष्ठा mlx5_frag_buf	buf;
	काष्ठा mlx5_db		db;
	काष्ठा mlx5_frag_buf_ctrl fbc;
	u64		       *wrid;
	/* protect SRQ hanlding
	 */
	spinlock_t		lock;
	पूर्णांक			head;
	पूर्णांक			tail;
	u16			wqe_ctr;
	काष्ठा ib_umem	       *umem;
	/* serialize arming a SRQ
	 */
	काष्ठा mutex		mutex;
	पूर्णांक			wq_sig;
पूर्ण;

काष्ठा mlx5_ib_xrcd अणु
	काष्ठा ib_xrcd		ibxrcd;
	u32			xrcdn;
पूर्ण;

क्रमागत mlx5_ib_mtt_access_flags अणु
	MLX5_IB_MTT_READ  = (1 << 0),
	MLX5_IB_MTT_WRITE = (1 << 1),
पूर्ण;

काष्ठा mlx5_user_mmap_entry अणु
	काष्ठा rdma_user_mmap_entry rdma_entry;
	u8 mmap_flag;
	u64 address;
	u32 page_idx;
पूर्ण;

#घोषणा MLX5_IB_MTT_PRESENT (MLX5_IB_MTT_READ | MLX5_IB_MTT_WRITE)

#घोषणा MLX5_IB_DM_MEMIC_ALLOWED_ACCESS (IB_ACCESS_LOCAL_WRITE   |\
					 IB_ACCESS_REMOTE_WRITE  |\
					 IB_ACCESS_REMOTE_READ   |\
					 IB_ACCESS_REMOTE_ATOMIC |\
					 IB_ZERO_BASED)

#घोषणा MLX5_IB_DM_SW_ICM_ALLOWED_ACCESS (IB_ACCESS_LOCAL_WRITE   |\
					  IB_ACCESS_REMOTE_WRITE  |\
					  IB_ACCESS_REMOTE_READ   |\
					  IB_ZERO_BASED)

#घोषणा mlx5_update_odp_stats(mr, counter_name, value)		\
	atomic64_add(value, &((mr)->odp_stats.counter_name))

काष्ठा mlx5_ib_mr अणु
	काष्ठा ib_mr ibmr;
	काष्ठा mlx5_core_mkey mmkey;

	/* User MR data */
	काष्ठा mlx5_cache_ent *cache_ent;
	काष्ठा ib_umem *umem;

	/* This is zero'd when the MR is allocated */
	जोड़ अणु
		/* Used only जबतक the MR is in the cache */
		काष्ठा अणु
			u32 out[MLX5_ST_SZ_DW(create_mkey_out)];
			काष्ठा mlx5_async_work cb_work;
			/* Cache list element */
			काष्ठा list_head list;
		पूर्ण;

		/* Used only by kernel MRs (umem == शून्य) */
		काष्ठा अणु
			व्योम *descs;
			व्योम *descs_alloc;
			dma_addr_t desc_map;
			पूर्णांक max_descs;
			पूर्णांक ndescs;
			पूर्णांक desc_size;
			पूर्णांक access_mode;

			/* For Kernel IB_MR_TYPE_INTEGRITY */
			काष्ठा mlx5_core_sig_ctx *sig;
			काष्ठा mlx5_ib_mr *pi_mr;
			काष्ठा mlx5_ib_mr *klm_mr;
			काष्ठा mlx5_ib_mr *mtt_mr;
			u64 data_iova;
			u64 pi_iova;
			पूर्णांक meta_ndescs;
			पूर्णांक meta_length;
			पूर्णांक data_length;
		पूर्ण;

		/* Used only by User MRs (umem != शून्य) */
		काष्ठा अणु
			अचिन्हित पूर्णांक page_shअगरt;
			/* Current access_flags */
			पूर्णांक access_flags;

			/* For User ODP */
			काष्ठा mlx5_ib_mr *parent;
			काष्ठा xarray implicit_children;
			जोड़ अणु
				काष्ठा work_काष्ठा work;
			पूर्ण odp_destroy;
			काष्ठा ib_odp_counters odp_stats;
			bool is_odp_implicit;
		पूर्ण;
	पूर्ण;
पूर्ण;

/* Zero the fields in the mr that are variant depending on usage */
अटल अंतरभूत व्योम mlx5_clear_mr(काष्ठा mlx5_ib_mr *mr)
अणु
	स_रखो(mr->out, 0, माप(*mr) - दुरत्व(काष्ठा mlx5_ib_mr, out));
पूर्ण

अटल अंतरभूत bool is_odp_mr(काष्ठा mlx5_ib_mr *mr)
अणु
	वापस IS_ENABLED(CONFIG_INFINIBAND_ON_DEMAND_PAGING) && mr->umem &&
	       mr->umem->is_odp;
पूर्ण

अटल अंतरभूत bool is_dmabuf_mr(काष्ठा mlx5_ib_mr *mr)
अणु
	वापस IS_ENABLED(CONFIG_INFINIBAND_ON_DEMAND_PAGING) && mr->umem &&
	       mr->umem->is_dmabuf;
पूर्ण

काष्ठा mlx5_ib_mw अणु
	काष्ठा ib_mw		ibmw;
	काष्ठा mlx5_core_mkey	mmkey;
	पूर्णांक			ndescs;
पूर्ण;

काष्ठा mlx5_ib_devx_mr अणु
	काष्ठा mlx5_core_mkey	mmkey;
	पूर्णांक			ndescs;
पूर्ण;

काष्ठा mlx5_ib_umr_context अणु
	काष्ठा ib_cqe		cqe;
	क्रमागत ib_wc_status	status;
	काष्ठा completion	करोne;
पूर्ण;

काष्ठा umr_common अणु
	काष्ठा ib_pd	*pd;
	काष्ठा ib_cq	*cq;
	काष्ठा ib_qp	*qp;
	/* control access to UMR QP
	 */
	काष्ठा semaphore	sem;
पूर्ण;

काष्ठा mlx5_cache_ent अणु
	काष्ठा list_head	head;
	/* sync access to the cahce entry
	 */
	spinlock_t		lock;


	अक्षर                    name[4];
	u32                     order;
	u32			xlt;
	u32			access_mode;
	u32			page;

	u8 disabled:1;
	u8 fill_to_high_water:1;

	/*
	 * - available_mrs is the length of list head, ie the number of MRs
	 *   available क्रम immediate allocation.
	 * - total_mrs is available_mrs plus all in use MRs that could be
	 *   वापसed to the cache.
	 * - limit is the low water mark क्रम available_mrs, 2* limit is the
	 *   upper water mark.
	 * - pending is the number of MRs currently being created
	 */
	u32 total_mrs;
	u32 available_mrs;
	u32 limit;
	u32 pending;

	/* Statistics */
	u32                     miss;

	काष्ठा mlx5_ib_dev     *dev;
	काष्ठा work_काष्ठा	work;
	काष्ठा delayed_work	dwork;
पूर्ण;

काष्ठा mlx5_mr_cache अणु
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा mlx5_cache_ent	ent[MAX_MR_CACHE_ENTRIES];
	काष्ठा dentry		*root;
	अचिन्हित दीर्घ		last_add;
पूर्ण;

काष्ठा mlx5_ib_port_resources अणु
	काष्ठा mlx5_ib_gsi_qp *gsi;
	काष्ठा work_काष्ठा pkey_change_work;
पूर्ण;

काष्ठा mlx5_ib_resources अणु
	काष्ठा ib_cq	*c0;
	u32 xrcdn0;
	u32 xrcdn1;
	काष्ठा ib_pd	*p0;
	काष्ठा ib_srq	*s0;
	काष्ठा ib_srq	*s1;
	काष्ठा mlx5_ib_port_resources ports[2];
	/* Protects changes to the port resources */
	काष्ठा mutex	mutex;
पूर्ण;

काष्ठा mlx5_ib_counters अणु
	स्थिर अक्षर **names;
	माप_प्रकार *offsets;
	u32 num_q_counters;
	u32 num_cong_counters;
	u32 num_ext_ppcnt_counters;
	u16 set_id;
पूर्ण;

काष्ठा mlx5_ib_multiport_info;

काष्ठा mlx5_ib_multiport अणु
	काष्ठा mlx5_ib_multiport_info *mpi;
	/* To be held when accessing the multiport info */
	spinlock_t mpi_lock;
पूर्ण;

काष्ठा mlx5_roce अणु
	/* Protect mlx5_ib_get_netdev from invoking dev_hold() with a शून्य
	 * netdev poपूर्णांकer
	 */
	rwlock_t		netdev_lock;
	काष्ठा net_device	*netdev;
	काष्ठा notअगरier_block	nb;
	atomic_t		tx_port_affinity;
	क्रमागत ib_port_state last_port_state;
	काष्ठा mlx5_ib_dev	*dev;
	u32			native_port_num;
पूर्ण;

काष्ठा mlx5_ib_port अणु
	काष्ठा mlx5_ib_counters cnts;
	काष्ठा mlx5_ib_multiport mp;
	काष्ठा mlx5_ib_dbg_cc_params *dbg_cc_params;
	काष्ठा mlx5_roce roce;
	काष्ठा mlx5_eचयन_rep		*rep;
पूर्ण;

काष्ठा mlx5_ib_dbg_param अणु
	पूर्णांक			offset;
	काष्ठा mlx5_ib_dev	*dev;
	काष्ठा dentry		*dentry;
	u32			port_num;
पूर्ण;

क्रमागत mlx5_ib_dbg_cc_types अणु
	MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE,
	MLX5_IB_DBG_CC_RP_CLAMP_TGT_RATE_ATI,
	MLX5_IB_DBG_CC_RP_TIME_RESET,
	MLX5_IB_DBG_CC_RP_BYTE_RESET,
	MLX5_IB_DBG_CC_RP_THRESHOLD,
	MLX5_IB_DBG_CC_RP_AI_RATE,
	MLX5_IB_DBG_CC_RP_MAX_RATE,
	MLX5_IB_DBG_CC_RP_HAI_RATE,
	MLX5_IB_DBG_CC_RP_MIN_DEC_FAC,
	MLX5_IB_DBG_CC_RP_MIN_RATE,
	MLX5_IB_DBG_CC_RP_RATE_TO_SET_ON_FIRST_CNP,
	MLX5_IB_DBG_CC_RP_DCE_TCP_G,
	MLX5_IB_DBG_CC_RP_DCE_TCP_RTT,
	MLX5_IB_DBG_CC_RP_RATE_REDUCE_MONITOR_PERIOD,
	MLX5_IB_DBG_CC_RP_INITIAL_ALPHA_VALUE,
	MLX5_IB_DBG_CC_RP_GD,
	MLX5_IB_DBG_CC_NP_MIN_TIME_BETWEEN_CNPS,
	MLX5_IB_DBG_CC_NP_CNP_DSCP,
	MLX5_IB_DBG_CC_NP_CNP_PRIO_MODE,
	MLX5_IB_DBG_CC_NP_CNP_PRIO,
	MLX5_IB_DBG_CC_MAX,
पूर्ण;

काष्ठा mlx5_ib_dbg_cc_params अणु
	काष्ठा dentry			*root;
	काष्ठा mlx5_ib_dbg_param	params[MLX5_IB_DBG_CC_MAX];
पूर्ण;

क्रमागत अणु
	MLX5_MAX_DELAY_DROP_TIMEOUT_MS = 100,
पूर्ण;

काष्ठा mlx5_ib_delay_drop अणु
	काष्ठा mlx5_ib_dev     *dev;
	काष्ठा work_काष्ठा	delay_drop_work;
	/* serialize setting of delay drop */
	काष्ठा mutex		lock;
	u32			समयout;
	bool			activate;
	atomic_t		events_cnt;
	atomic_t		rqs_cnt;
	काष्ठा dentry		*dir_debugfs;
पूर्ण;

क्रमागत mlx5_ib_stages अणु
	MLX5_IB_STAGE_INIT,
	MLX5_IB_STAGE_FS,
	MLX5_IB_STAGE_CAPS,
	MLX5_IB_STAGE_NON_DEFAULT_CB,
	MLX5_IB_STAGE_ROCE,
	MLX5_IB_STAGE_QP,
	MLX5_IB_STAGE_SRQ,
	MLX5_IB_STAGE_DEVICE_RESOURCES,
	MLX5_IB_STAGE_DEVICE_NOTIFIER,
	MLX5_IB_STAGE_ODP,
	MLX5_IB_STAGE_COUNTERS,
	MLX5_IB_STAGE_CONG_DEBUGFS,
	MLX5_IB_STAGE_UAR,
	MLX5_IB_STAGE_BFREG,
	MLX5_IB_STAGE_PRE_IB_REG_UMR,
	MLX5_IB_STAGE_WHITELIST_UID,
	MLX5_IB_STAGE_IB_REG,
	MLX5_IB_STAGE_POST_IB_REG_UMR,
	MLX5_IB_STAGE_DELAY_DROP,
	MLX5_IB_STAGE_RESTRACK,
	MLX5_IB_STAGE_MAX,
पूर्ण;

काष्ठा mlx5_ib_stage अणु
	पूर्णांक (*init)(काष्ठा mlx5_ib_dev *dev);
	व्योम (*cleanup)(काष्ठा mlx5_ib_dev *dev);
पूर्ण;

#घोषणा STAGE_CREATE(_stage, _init, _cleanup) \
	.stage[_stage] = अणु.init = _init, .cleanup = _cleanupपूर्ण

काष्ठा mlx5_ib_profile अणु
	काष्ठा mlx5_ib_stage stage[MLX5_IB_STAGE_MAX];
पूर्ण;

काष्ठा mlx5_ib_multiport_info अणु
	काष्ठा list_head list;
	काष्ठा mlx5_ib_dev *ibdev;
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा notअगरier_block mdev_events;
	काष्ठा completion unref_comp;
	u64 sys_image_guid;
	u32 mdev_refcnt;
	bool is_master;
	bool unaffiliate;
पूर्ण;

काष्ठा mlx5_ib_flow_action अणु
	काष्ठा ib_flow_action		ib_action;
	जोड़ अणु
		काष्ठा अणु
			u64			    ib_flags;
			काष्ठा mlx5_accel_esp_xfrm *ctx;
		पूर्ण esp_aes_gcm;
		काष्ठा अणु
			काष्ठा mlx5_ib_dev *dev;
			u32 sub_type;
			जोड़ अणु
				काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr;
				काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat;
			पूर्ण;
		पूर्ण flow_action_raw;
	पूर्ण;
पूर्ण;

काष्ठा mlx5_dm अणु
	काष्ठा mlx5_core_dev *dev;
	/* This lock is used to protect the access to the shared
	 * allocation map when concurrent requests by dअगरferent
	 * processes are handled.
	 */
	spinlock_t lock;
	DECLARE_BITMAP(memic_alloc_pages, MLX5_MAX_MEMIC_PAGES);
पूर्ण;

काष्ठा mlx5_पढ़ो_counters_attr अणु
	काष्ठा mlx5_fc *hw_cntrs_hndl;
	u64 *out;
	u32 flags;
पूर्ण;

क्रमागत mlx5_ib_counters_type अणु
	MLX5_IB_COUNTERS_FLOW,
पूर्ण;

काष्ठा mlx5_ib_mcounters अणु
	काष्ठा ib_counters ibcntrs;
	क्रमागत mlx5_ib_counters_type type;
	/* number of counters supported क्रम this counters type */
	u32 counters_num;
	काष्ठा mlx5_fc *hw_cntrs_hndl;
	/* पढ़ो function क्रम this counters type */
	पूर्णांक (*पढ़ो_counters)(काष्ठा ib_device *ibdev,
			     काष्ठा mlx5_पढ़ो_counters_attr *पढ़ो_attr);
	/* max index set as part of create_flow */
	u32 cntrs_max_index;
	/* number of counters data entries (<description,index> pair) */
	u32 ncounters;
	/* counters data array क्रम descriptions and indexes */
	काष्ठा mlx5_ib_flow_counters_desc *counters_data;
	/* protects access to mcounters पूर्णांकernal data */
	काष्ठा mutex mcntrs_mutex;
पूर्ण;

अटल अंतरभूत काष्ठा mlx5_ib_mcounters *
to_mcounters(काष्ठा ib_counters *ibcntrs)
अणु
	वापस container_of(ibcntrs, काष्ठा mlx5_ib_mcounters, ibcntrs);
पूर्ण

पूर्णांक parse_flow_flow_action(काष्ठा mlx5_ib_flow_action *maction,
			   bool is_egress,
			   काष्ठा mlx5_flow_act *action);
काष्ठा mlx5_ib_lb_state अणु
	/* protect the user_td */
	काष्ठा mutex		mutex;
	u32			user_td;
	पूर्णांक			qps;
	bool			enabled;
पूर्ण;

काष्ठा mlx5_ib_pf_eq अणु
	काष्ठा notअगरier_block irq_nb;
	काष्ठा mlx5_ib_dev *dev;
	काष्ठा mlx5_eq *core;
	काष्ठा work_काष्ठा work;
	spinlock_t lock; /* Pagefaults spinlock */
	काष्ठा workqueue_काष्ठा *wq;
	mempool_t *pool;
पूर्ण;

काष्ठा mlx5_devx_event_table अणु
	काष्ठा mlx5_nb devx_nb;
	/* serialize updating the event_xa */
	काष्ठा mutex event_xa_lock;
	काष्ठा xarray event_xa;
पूर्ण;

काष्ठा mlx5_var_table अणु
	/* serialize updating the biपंचांगap */
	काष्ठा mutex biपंचांगap_lock;
	अचिन्हित दीर्घ *biपंचांगap;
	u64 hw_start_addr;
	u32 stride_size;
	u64 num_var_hw_entries;
पूर्ण;

काष्ठा mlx5_port_caps अणु
	bool has_smi;
	u8 ext_port_cap;
पूर्ण;

काष्ठा mlx5_ib_dev अणु
	काष्ठा ib_device		ib_dev;
	काष्ठा mlx5_core_dev		*mdev;
	काष्ठा notअगरier_block		mdev_events;
	पूर्णांक				num_ports;
	/* serialize update of capability mask
	 */
	काष्ठा mutex			cap_mask_mutex;
	u8				ib_active:1;
	u8				is_rep:1;
	u8				lag_active:1;
	u8				wc_support:1;
	u8				fill_delay;
	काष्ठा umr_common		umrc;
	/* sync used page count stats
	 */
	काष्ठा mlx5_ib_resources	devr;

	atomic_t			mkey_var;
	काष्ठा mlx5_mr_cache		cache;
	काष्ठा समयr_list		delay_समयr;
	/* Prevents soft lock on massive reg MRs */
	काष्ठा mutex			slow_path_mutex;
	काष्ठा ib_odp_caps	odp_caps;
	u64			odp_max_size;
	काष्ठा mutex		odp_eq_mutex;
	काष्ठा mlx5_ib_pf_eq	odp_pf_eq;

	काष्ठा xarray		odp_mkeys;

	u32			null_mkey;
	काष्ठा mlx5_ib_flow_db	*flow_db;
	/* protect resources needed as part of reset flow */
	spinlock_t		reset_flow_resource_lock;
	काष्ठा list_head	qp_list;
	/* Array with num_ports elements */
	काष्ठा mlx5_ib_port	*port;
	काष्ठा mlx5_sq_bfreg	bfreg;
	काष्ठा mlx5_sq_bfreg	wc_bfreg;
	काष्ठा mlx5_sq_bfreg	fp_bfreg;
	काष्ठा mlx5_ib_delay_drop	delay_drop;
	स्थिर काष्ठा mlx5_ib_profile	*profile;

	काष्ठा mlx5_ib_lb_state		lb;
	u8			umr_fence;
	काष्ठा list_head	ib_dev_list;
	u64			sys_image_guid;
	काष्ठा mlx5_dm		dm;
	u16			devx_whitelist_uid;
	काष्ठा mlx5_srq_table   srq_table;
	काष्ठा mlx5_qp_table    qp_table;
	काष्ठा mlx5_async_ctx   async_ctx;
	काष्ठा mlx5_devx_event_table devx_event_table;
	काष्ठा mlx5_var_table var_table;

	काष्ठा xarray sig_mrs;
	काष्ठा mlx5_port_caps port_caps[MLX5_MAX_PORTS];
	u16 pkey_table_len;
पूर्ण;

अटल अंतरभूत काष्ठा mlx5_ib_cq *to_mibcq(काष्ठा mlx5_core_cq *mcq)
अणु
	वापस container_of(mcq, काष्ठा mlx5_ib_cq, mcq);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_xrcd *to_mxrcd(काष्ठा ib_xrcd *ibxrcd)
अणु
	वापस container_of(ibxrcd, काष्ठा mlx5_ib_xrcd, ibxrcd);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_dev *to_mdev(काष्ठा ib_device *ibdev)
अणु
	वापस container_of(ibdev, काष्ठा mlx5_ib_dev, ib_dev);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_dev *mr_to_mdev(काष्ठा mlx5_ib_mr *mr)
अणु
	वापस to_mdev(mr->ibmr.device);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_dev *mlx5_udata_to_mdev(काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा mlx5_ib_ucontext, ibucontext);

	वापस to_mdev(context->ibucontext.device);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_cq *to_mcq(काष्ठा ib_cq *ibcq)
अणु
	वापस container_of(ibcq, काष्ठा mlx5_ib_cq, ibcq);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_qp *to_mibqp(काष्ठा mlx5_core_qp *mqp)
अणु
	वापस container_of(mqp, काष्ठा mlx5_ib_qp_base, mqp)->container_mibqp;
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_rwq *to_mibrwq(काष्ठा mlx5_core_qp *core_qp)
अणु
	वापस container_of(core_qp, काष्ठा mlx5_ib_rwq, core_qp);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_pd *to_mpd(काष्ठा ib_pd *ibpd)
अणु
	वापस container_of(ibpd, काष्ठा mlx5_ib_pd, ibpd);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_srq *to_msrq(काष्ठा ib_srq *ibsrq)
अणु
	वापस container_of(ibsrq, काष्ठा mlx5_ib_srq, ibsrq);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_qp *to_mqp(काष्ठा ib_qp *ibqp)
अणु
	वापस container_of(ibqp, काष्ठा mlx5_ib_qp, ibqp);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_rwq *to_mrwq(काष्ठा ib_wq *ibwq)
अणु
	वापस container_of(ibwq, काष्ठा mlx5_ib_rwq, ibwq);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_rwq_ind_table *to_mrwq_ind_table(काष्ठा ib_rwq_ind_table *ib_rwq_ind_tbl)
अणु
	वापस container_of(ib_rwq_ind_tbl, काष्ठा mlx5_ib_rwq_ind_table, ib_rwq_ind_tbl);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_srq *to_mibsrq(काष्ठा mlx5_core_srq *msrq)
अणु
	वापस container_of(msrq, काष्ठा mlx5_ib_srq, msrq);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_mr *to_mmr(काष्ठा ib_mr *ibmr)
अणु
	वापस container_of(ibmr, काष्ठा mlx5_ib_mr, ibmr);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_mw *to_mmw(काष्ठा ib_mw *ibmw)
अणु
	वापस container_of(ibmw, काष्ठा mlx5_ib_mw, ibmw);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_flow_action *
to_mflow_act(काष्ठा ib_flow_action *ibact)
अणु
	वापस container_of(ibact, काष्ठा mlx5_ib_flow_action, ib_action);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_user_mmap_entry *
to_mmmap(काष्ठा rdma_user_mmap_entry *rdma_entry)
अणु
	वापस container_of(rdma_entry,
		काष्ठा mlx5_user_mmap_entry, rdma_entry);
पूर्ण

पूर्णांक mlx5_ib_db_map_user(काष्ठा mlx5_ib_ucontext *context,
			काष्ठा ib_udata *udata, अचिन्हित दीर्घ virt,
			काष्ठा mlx5_db *db);
व्योम mlx5_ib_db_unmap_user(काष्ठा mlx5_ib_ucontext *context, काष्ठा mlx5_db *db);
व्योम __mlx5_ib_cq_clean(काष्ठा mlx5_ib_cq *cq, u32 qpn, काष्ठा mlx5_ib_srq *srq);
व्योम mlx5_ib_cq_clean(काष्ठा mlx5_ib_cq *cq, u32 qpn, काष्ठा mlx5_ib_srq *srq);
व्योम mlx5_ib_मुक्त_srq_wqe(काष्ठा mlx5_ib_srq *srq, पूर्णांक wqe_index);
पूर्णांक mlx5_ib_create_ah(काष्ठा ib_ah *ah, काष्ठा rdma_ah_init_attr *init_attr,
		      काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_query_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_attr *ah_attr);
अटल अंतरभूत पूर्णांक mlx5_ib_destroy_ah(काष्ठा ib_ah *ah, u32 flags)
अणु
	वापस 0;
पूर्ण
पूर्णांक mlx5_ib_create_srq(काष्ठा ib_srq *srq, काष्ठा ib_srq_init_attr *init_attr,
		       काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_modअगरy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr,
		       क्रमागत ib_srq_attr_mask attr_mask, काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_query_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *srq_attr);
पूर्णांक mlx5_ib_destroy_srq(काष्ठा ib_srq *srq, काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_post_srq_recv(काष्ठा ib_srq *ibsrq, स्थिर काष्ठा ib_recv_wr *wr,
			  स्थिर काष्ठा ib_recv_wr **bad_wr);
पूर्णांक mlx5_ib_enable_lb(काष्ठा mlx5_ib_dev *dev, bool td, bool qp);
व्योम mlx5_ib_disable_lb(काष्ठा mlx5_ib_dev *dev, bool td, bool qp);
काष्ठा ib_qp *mlx5_ib_create_qp(काष्ठा ib_pd *pd,
				काष्ठा ib_qp_init_attr *init_attr,
				काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		      पूर्णांक attr_mask, काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr, पूर्णांक qp_attr_mask,
		     काष्ठा ib_qp_init_attr *qp_init_attr);
पूर्णांक mlx5_ib_destroy_qp(काष्ठा ib_qp *qp, काष्ठा ib_udata *udata);
व्योम mlx5_ib_drain_sq(काष्ठा ib_qp *qp);
व्योम mlx5_ib_drain_rq(काष्ठा ib_qp *qp);
पूर्णांक mlx5_ib_पढ़ो_wqe_sq(काष्ठा mlx5_ib_qp *qp, पूर्णांक wqe_index, व्योम *buffer,
			माप_प्रकार buflen, माप_प्रकार *bc);
पूर्णांक mlx5_ib_पढ़ो_wqe_rq(काष्ठा mlx5_ib_qp *qp, पूर्णांक wqe_index, व्योम *buffer,
			माप_प्रकार buflen, माप_प्रकार *bc);
पूर्णांक mlx5_ib_पढ़ो_wqe_srq(काष्ठा mlx5_ib_srq *srq, पूर्णांक wqe_index, व्योम *buffer,
			 माप_प्रकार buflen, माप_प्रकार *bc);
पूर्णांक mlx5_ib_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		      काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_destroy_cq(काष्ठा ib_cq *cq, काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc);
पूर्णांक mlx5_ib_arm_cq(काष्ठा ib_cq *ibcq, क्रमागत ib_cq_notअगरy_flags flags);
पूर्णांक mlx5_ib_modअगरy_cq(काष्ठा ib_cq *cq, u16 cq_count, u16 cq_period);
पूर्णांक mlx5_ib_resize_cq(काष्ठा ib_cq *ibcq, पूर्णांक entries, काष्ठा ib_udata *udata);
काष्ठा ib_mr *mlx5_ib_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक acc);
काष्ठा ib_mr *mlx5_ib_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
				  u64 virt_addr, पूर्णांक access_flags,
				  काष्ठा ib_udata *udata);
काष्ठा ib_mr *mlx5_ib_reg_user_mr_dmabuf(काष्ठा ib_pd *pd, u64 start,
					 u64 length, u64 virt_addr,
					 पूर्णांक fd, पूर्णांक access_flags,
					 काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_advise_mr(काष्ठा ib_pd *pd,
		      क्रमागत ib_uverbs_advise_mr_advice advice,
		      u32 flags,
		      काष्ठा ib_sge *sg_list,
		      u32 num_sge,
		      काष्ठा uverbs_attr_bundle *attrs);
पूर्णांक mlx5_ib_alloc_mw(काष्ठा ib_mw *mw, काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_dealloc_mw(काष्ठा ib_mw *mw);
पूर्णांक mlx5_ib_update_xlt(काष्ठा mlx5_ib_mr *mr, u64 idx, पूर्णांक npages,
		       पूर्णांक page_shअगरt, पूर्णांक flags);
पूर्णांक mlx5_ib_update_mr_pas(काष्ठा mlx5_ib_mr *mr, अचिन्हित पूर्णांक flags);
काष्ठा mlx5_ib_mr *mlx5_ib_alloc_implicit_mr(काष्ठा mlx5_ib_pd *pd,
					     काष्ठा ib_udata *udata,
					     पूर्णांक access_flags);
व्योम mlx5_ib_मुक्त_implicit_mr(काष्ठा mlx5_ib_mr *mr);
व्योम mlx5_ib_मुक्त_odp_mr(काष्ठा mlx5_ib_mr *mr);
काष्ठा ib_mr *mlx5_ib_rereg_user_mr(काष्ठा ib_mr *ib_mr, पूर्णांक flags, u64 start,
				    u64 length, u64 virt_addr, पूर्णांक access_flags,
				    काष्ठा ib_pd *pd, काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_dereg_mr(काष्ठा ib_mr *ibmr, काष्ठा ib_udata *udata);
काष्ठा ib_mr *mlx5_ib_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			       u32 max_num_sg);
काष्ठा ib_mr *mlx5_ib_alloc_mr_पूर्णांकegrity(काष्ठा ib_pd *pd,
					 u32 max_num_sg,
					 u32 max_num_meta_sg);
पूर्णांक mlx5_ib_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		      अचिन्हित पूर्णांक *sg_offset);
पूर्णांक mlx5_ib_map_mr_sg_pi(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *data_sg,
			 पूर्णांक data_sg_nents, अचिन्हित पूर्णांक *data_sg_offset,
			 काष्ठा scatterlist *meta_sg, पूर्णांक meta_sg_nents,
			 अचिन्हित पूर्णांक *meta_sg_offset);
पूर्णांक mlx5_ib_process_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags, u32 port_num,
			स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
			स्थिर काष्ठा ib_mad *in, काष्ठा ib_mad *out,
			माप_प्रकार *out_mad_size, u16 *out_mad_pkey_index);
पूर्णांक mlx5_ib_alloc_xrcd(काष्ठा ib_xrcd *xrcd, काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_dealloc_xrcd(काष्ठा ib_xrcd *xrcd, काष्ठा ib_udata *udata);
पूर्णांक mlx5_query_ext_port_caps(काष्ठा mlx5_ib_dev *dev, अचिन्हित पूर्णांक port);
पूर्णांक mlx5_query_mad_अगरc_प्रणाली_image_guid(काष्ठा ib_device *ibdev,
					 __be64 *sys_image_guid);
पूर्णांक mlx5_query_mad_अगरc_max_pkeys(काष्ठा ib_device *ibdev,
				 u16 *max_pkeys);
पूर्णांक mlx5_query_mad_अगरc_venकरोr_id(काष्ठा ib_device *ibdev,
				 u32 *venकरोr_id);
पूर्णांक mlx5_query_mad_अगरc_node_desc(काष्ठा mlx5_ib_dev *dev, अक्षर *node_desc);
पूर्णांक mlx5_query_mad_अगरc_node_guid(काष्ठा mlx5_ib_dev *dev, __be64 *node_guid);
पूर्णांक mlx5_query_mad_अगरc_pkey(काष्ठा ib_device *ibdev, u32 port, u16 index,
			    u16 *pkey);
पूर्णांक mlx5_query_mad_अगरc_gids(काष्ठा ib_device *ibdev, u32 port, पूर्णांक index,
			    जोड़ ib_gid *gid);
पूर्णांक mlx5_query_mad_अगरc_port(काष्ठा ib_device *ibdev, u32 port,
			    काष्ठा ib_port_attr *props);
पूर्णांक mlx5_ib_query_port(काष्ठा ib_device *ibdev, u32 port,
		       काष्ठा ib_port_attr *props);
व्योम mlx5_ib_populate_pas(काष्ठा ib_umem *umem, माप_प्रकार page_size, __be64 *pas,
			  u64 access_flags);
व्योम mlx5_ib_copy_pas(u64 *old, u64 *new, पूर्णांक step, पूर्णांक num);
पूर्णांक mlx5_ib_get_cqe_size(काष्ठा ib_cq *ibcq);
पूर्णांक mlx5_mr_cache_init(काष्ठा mlx5_ib_dev *dev);
पूर्णांक mlx5_mr_cache_cleanup(काष्ठा mlx5_ib_dev *dev);

काष्ठा mlx5_ib_mr *mlx5_mr_cache_alloc(काष्ठा mlx5_ib_dev *dev,
				       अचिन्हित पूर्णांक entry, पूर्णांक access_flags);

पूर्णांक mlx5_ib_check_mr_status(काष्ठा ib_mr *ibmr, u32 check_mask,
			    काष्ठा ib_mr_status *mr_status);
काष्ठा ib_wq *mlx5_ib_create_wq(काष्ठा ib_pd *pd,
				काष्ठा ib_wq_init_attr *init_attr,
				काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_destroy_wq(काष्ठा ib_wq *wq, काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_modअगरy_wq(काष्ठा ib_wq *wq, काष्ठा ib_wq_attr *wq_attr,
		      u32 wq_attr_mask, काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_create_rwq_ind_table(काष्ठा ib_rwq_ind_table *ib_rwq_ind_table,
				 काष्ठा ib_rwq_ind_table_init_attr *init_attr,
				 काष्ठा ib_udata *udata);
पूर्णांक mlx5_ib_destroy_rwq_ind_table(काष्ठा ib_rwq_ind_table *wq_ind_table);
काष्ठा ib_mr *mlx5_ib_reg_dm_mr(काष्ठा ib_pd *pd, काष्ठा ib_dm *dm,
				काष्ठा ib_dm_mr_attr *attr,
				काष्ठा uverbs_attr_bundle *attrs);

#अगर_घोषित CONFIG_INFINIBAND_ON_DEMAND_PAGING
पूर्णांक mlx5_ib_odp_init_one(काष्ठा mlx5_ib_dev *ibdev);
पूर्णांक mlx5r_odp_create_eq(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_pf_eq *eq);
व्योम mlx5_ib_odp_cleanup_one(काष्ठा mlx5_ib_dev *ibdev);
पूर्णांक __init mlx5_ib_odp_init(व्योम);
व्योम mlx5_ib_odp_cleanup(व्योम);
व्योम mlx5_odp_init_mr_cache_entry(काष्ठा mlx5_cache_ent *ent);
व्योम mlx5_odp_populate_xlt(व्योम *xlt, माप_प्रकार idx, माप_प्रकार nentries,
			   काष्ठा mlx5_ib_mr *mr, पूर्णांक flags);

पूर्णांक mlx5_ib_advise_mr_prefetch(काष्ठा ib_pd *pd,
			       क्रमागत ib_uverbs_advise_mr_advice advice,
			       u32 flags, काष्ठा ib_sge *sg_list, u32 num_sge);
पूर्णांक mlx5_ib_init_odp_mr(काष्ठा mlx5_ib_mr *mr);
पूर्णांक mlx5_ib_init_dmabuf_mr(काष्ठा mlx5_ib_mr *mr);
#अन्यथा /* CONFIG_INFINIBAND_ON_DEMAND_PAGING */
अटल अंतरभूत पूर्णांक mlx5_ib_odp_init_one(काष्ठा mlx5_ib_dev *ibdev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक mlx5r_odp_create_eq(काष्ठा mlx5_ib_dev *dev,
				      काष्ठा mlx5_ib_pf_eq *eq)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम mlx5_ib_odp_cleanup_one(काष्ठा mlx5_ib_dev *ibdev) अणुपूर्ण
अटल अंतरभूत पूर्णांक mlx5_ib_odp_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mlx5_ib_odp_cleanup(व्योम)				    अणुपूर्ण
अटल अंतरभूत व्योम mlx5_odp_init_mr_cache_entry(काष्ठा mlx5_cache_ent *ent) अणुपूर्ण
अटल अंतरभूत व्योम mlx5_odp_populate_xlt(व्योम *xlt, माप_प्रकार idx, माप_प्रकार nentries,
					 काष्ठा mlx5_ib_mr *mr, पूर्णांक flags) अणुपूर्ण

अटल अंतरभूत पूर्णांक
mlx5_ib_advise_mr_prefetch(काष्ठा ib_pd *pd,
			   क्रमागत ib_uverbs_advise_mr_advice advice, u32 flags,
			   काष्ठा ib_sge *sg_list, u32 num_sge)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक mlx5_ib_init_odp_mr(काष्ठा mlx5_ib_mr *mr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक mlx5_ib_init_dmabuf_mr(काष्ठा mlx5_ib_mr *mr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर /* CONFIG_INFINIBAND_ON_DEMAND_PAGING */

बाह्य स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops mlx5_mn_ops;

/* Needed क्रम rep profile */
व्योम __mlx5_ib_हटाओ(काष्ठा mlx5_ib_dev *dev,
		      स्थिर काष्ठा mlx5_ib_profile *profile,
		      पूर्णांक stage);
पूर्णांक __mlx5_ib_add(काष्ठा mlx5_ib_dev *dev,
		  स्थिर काष्ठा mlx5_ib_profile *profile);

पूर्णांक mlx5_ib_get_vf_config(काष्ठा ib_device *device, पूर्णांक vf,
			  u32 port, काष्ठा अगरla_vf_info *info);
पूर्णांक mlx5_ib_set_vf_link_state(काष्ठा ib_device *device, पूर्णांक vf,
			      u32 port, पूर्णांक state);
पूर्णांक mlx5_ib_get_vf_stats(काष्ठा ib_device *device, पूर्णांक vf,
			 u32 port, काष्ठा अगरla_vf_stats *stats);
पूर्णांक mlx5_ib_get_vf_guid(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
			काष्ठा अगरla_vf_guid *node_guid,
			काष्ठा अगरla_vf_guid *port_guid);
पूर्णांक mlx5_ib_set_vf_guid(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
			u64 guid, पूर्णांक type);

__be16 mlx5_get_roce_udp_sport_min(स्थिर काष्ठा mlx5_ib_dev *dev,
				   स्थिर काष्ठा ib_gid_attr *attr);

व्योम mlx5_ib_cleanup_cong_debugfs(काष्ठा mlx5_ib_dev *dev, u32 port_num);
व्योम mlx5_ib_init_cong_debugfs(काष्ठा mlx5_ib_dev *dev, u32 port_num);

/* GSI QP helper functions */
पूर्णांक mlx5_ib_create_gsi(काष्ठा ib_pd *pd, काष्ठा mlx5_ib_qp *mqp,
		       काष्ठा ib_qp_init_attr *attr);
पूर्णांक mlx5_ib_destroy_gsi(काष्ठा mlx5_ib_qp *mqp);
पूर्णांक mlx5_ib_gsi_modअगरy_qp(काष्ठा ib_qp *qp, काष्ठा ib_qp_attr *attr,
			  पूर्णांक attr_mask);
पूर्णांक mlx5_ib_gsi_query_qp(काष्ठा ib_qp *qp, काष्ठा ib_qp_attr *qp_attr,
			 पूर्णांक qp_attr_mask,
			 काष्ठा ib_qp_init_attr *qp_init_attr);
पूर्णांक mlx5_ib_gsi_post_send(काष्ठा ib_qp *qp, स्थिर काष्ठा ib_send_wr *wr,
			  स्थिर काष्ठा ib_send_wr **bad_wr);
पूर्णांक mlx5_ib_gsi_post_recv(काष्ठा ib_qp *qp, स्थिर काष्ठा ib_recv_wr *wr,
			  स्थिर काष्ठा ib_recv_wr **bad_wr);
व्योम mlx5_ib_gsi_pkey_change(काष्ठा mlx5_ib_gsi_qp *gsi);

पूर्णांक mlx5_ib_generate_wc(काष्ठा ib_cq *ibcq, काष्ठा ib_wc *wc);

व्योम mlx5_ib_मुक्त_bfreg(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_bfreg_info *bfregi,
			पूर्णांक bfregn);
काष्ठा mlx5_ib_dev *mlx5_ib_get_ibdev_from_mpi(काष्ठा mlx5_ib_multiport_info *mpi);
काष्ठा mlx5_core_dev *mlx5_ib_get_native_port_mdev(काष्ठा mlx5_ib_dev *dev,
						   u32 ib_port_num,
						   u32 *native_port_num);
व्योम mlx5_ib_put_native_port_mdev(काष्ठा mlx5_ib_dev *dev,
				  u32 port_num);

बाह्य स्थिर काष्ठा uapi_definition mlx5_ib_devx_defs[];
बाह्य स्थिर काष्ठा uapi_definition mlx5_ib_flow_defs[];
बाह्य स्थिर काष्ठा uapi_definition mlx5_ib_qos_defs[];
बाह्य स्थिर काष्ठा uapi_definition mlx5_ib_std_types_defs[];

अटल अंतरभूत व्योम init_query_mad(काष्ठा ib_smp *mad)
अणु
	mad->base_version  = 1;
	mad->mgmt_class    = IB_MGMT_CLASS_SUBN_LID_ROUTED;
	mad->class_version = 1;
	mad->method	   = IB_MGMT_METHOD_GET;
पूर्ण

अटल अंतरभूत पूर्णांक is_qp1(क्रमागत ib_qp_type qp_type)
अणु
	वापस qp_type == MLX5_IB_QPT_HW_GSI || qp_type == IB_QPT_GSI;
पूर्ण

#घोषणा MLX5_MAX_UMR_SHIFT 16
#घोषणा MLX5_MAX_UMR_PAGES (1 << MLX5_MAX_UMR_SHIFT)

अटल अंतरभूत u32 check_cq_create_flags(u32 flags)
अणु
	/*
	 * It वापसs non-zero value क्रम unsupported CQ
	 * create flags, otherwise it वापसs zero.
	 */
	वापस (flags & ~(IB_UVERBS_CQ_FLAGS_IGNORE_OVERRUN |
			  IB_UVERBS_CQ_FLAGS_TIMESTAMP_COMPLETION));
पूर्ण

अटल अंतरभूत पूर्णांक verअगरy_assign_uidx(u8 cqe_version, u32 cmd_uidx,
				     u32 *user_index)
अणु
	अगर (cqe_version) अणु
		अगर ((cmd_uidx == MLX5_IB_DEFAULT_UIDX) ||
		    (cmd_uidx & ~MLX5_USER_ASSIGNED_UIDX_MASK))
			वापस -EINVAL;
		*user_index = cmd_uidx;
	पूर्ण अन्यथा अणु
		*user_index = MLX5_IB_DEFAULT_UIDX;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक get_qp_user_index(काष्ठा mlx5_ib_ucontext *ucontext,
				    काष्ठा mlx5_ib_create_qp *ucmd,
				    पूर्णांक inlen,
				    u32 *user_index)
अणु
	u8 cqe_version = ucontext->cqe_version;

	अगर ((दुरत्वend(typeof(*ucmd), uidx) <= inlen) && !cqe_version &&
	    (ucmd->uidx == MLX5_IB_DEFAULT_UIDX))
		वापस 0;

	अगर ((दुरत्वend(typeof(*ucmd), uidx) <= inlen) != !!cqe_version)
		वापस -EINVAL;

	वापस verअगरy_assign_uidx(cqe_version, ucmd->uidx, user_index);
पूर्ण

अटल अंतरभूत पूर्णांक get_srq_user_index(काष्ठा mlx5_ib_ucontext *ucontext,
				     काष्ठा mlx5_ib_create_srq *ucmd,
				     पूर्णांक inlen,
				     u32 *user_index)
अणु
	u8 cqe_version = ucontext->cqe_version;

	अगर ((दुरत्वend(typeof(*ucmd), uidx) <= inlen) && !cqe_version &&
	    (ucmd->uidx == MLX5_IB_DEFAULT_UIDX))
		वापस 0;

	अगर ((दुरत्वend(typeof(*ucmd), uidx) <= inlen) != !!cqe_version)
		वापस -EINVAL;

	वापस verअगरy_assign_uidx(cqe_version, ucmd->uidx, user_index);
पूर्ण

अटल अंतरभूत पूर्णांक get_uars_per_sys_page(काष्ठा mlx5_ib_dev *dev, bool lib_support)
अणु
	वापस lib_support && MLX5_CAP_GEN(dev->mdev, uar_4k) ?
				MLX5_UARS_IN_PAGE : 1;
पूर्ण

अटल अंतरभूत पूर्णांक get_num_अटल_uars(काष्ठा mlx5_ib_dev *dev,
				      काष्ठा mlx5_bfreg_info *bfregi)
अणु
	वापस get_uars_per_sys_page(dev, bfregi->lib_uar_4k) * bfregi->num_अटल_sys_pages;
पूर्ण

बाह्य व्योम *xlt_emergency_page;

पूर्णांक bfregn_to_uar_index(काष्ठा mlx5_ib_dev *dev,
			काष्ठा mlx5_bfreg_info *bfregi, u32 bfregn,
			bool dyn_bfreg);

अटल अंतरभूत bool mlx5_ib_can_load_pas_with_umr(काष्ठा mlx5_ib_dev *dev,
						 माप_प्रकार length)
अणु
	/*
	 * umr_check_mkey_mask() rejects MLX5_MKEY_MASK_PAGE_SIZE which is
	 * always set अगर MLX5_IB_SEND_UMR_UPDATE_TRANSLATION (aka
	 * MLX5_IB_UPD_XLT_ADDR and MLX5_IB_UPD_XLT_ENABLE) is set. Thus, a mkey
	 * can never be enabled without this capability. Simplअगरy this weird
	 * quirky hardware by just saying it can't use PAS lists with UMR at
	 * all.
	 */
	अगर (MLX5_CAP_GEN(dev->mdev, umr_modअगरy_entity_size_disabled))
		वापस false;

	/*
	 * length is the size of the MR in bytes when mlx5_ib_update_xlt() is
	 * used.
	 */
	अगर (!MLX5_CAP_GEN(dev->mdev, umr_extended_translation_offset) &&
	    length >= MLX5_MAX_UMR_PAGES * PAGE_SIZE)
		वापस false;
	वापस true;
पूर्ण

/*
 * true अगर an existing MR can be reconfigured to new access_flags using UMR.
 * Older HW cannot use UMR to update certain elements of the MKC. See
 * umr_check_mkey_mask(), get_umr_update_access_mask() and umr_check_mkey_mask()
 */
अटल अंतरभूत bool mlx5_ib_can_reconfig_with_umr(काष्ठा mlx5_ib_dev *dev,
						 अचिन्हित पूर्णांक current_access_flags,
						 अचिन्हित पूर्णांक target_access_flags)
अणु
	अचिन्हित पूर्णांक dअगरfs = current_access_flags ^ target_access_flags;

	अगर ((dअगरfs & IB_ACCESS_REMOTE_ATOMIC) &&
	    MLX5_CAP_GEN(dev->mdev, atomic) &&
	    MLX5_CAP_GEN(dev->mdev, umr_modअगरy_atomic_disabled))
		वापस false;

	अगर ((dअगरfs & IB_ACCESS_RELAXED_ORDERING) &&
	    MLX5_CAP_GEN(dev->mdev, relaxed_ordering_ग_लिखो) &&
	    !MLX5_CAP_GEN(dev->mdev, relaxed_ordering_ग_लिखो_umr))
		वापस false;

	अगर ((dअगरfs & IB_ACCESS_RELAXED_ORDERING) &&
	    MLX5_CAP_GEN(dev->mdev, relaxed_ordering_पढ़ो) &&
	    !MLX5_CAP_GEN(dev->mdev, relaxed_ordering_पढ़ो_umr))
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक mlx5r_store_odp_mkey(काष्ठा mlx5_ib_dev *dev,
				       काष्ठा mlx5_core_mkey *mmkey)
अणु
	refcount_set(&mmkey->usecount, 1);

	वापस xa_err(xa_store(&dev->odp_mkeys, mlx5_base_mkey(mmkey->key),
			       mmkey, GFP_KERNEL));
पूर्ण

/* deref an mkey that can participate in ODP flow */
अटल अंतरभूत व्योम mlx5r_deref_odp_mkey(काष्ठा mlx5_core_mkey *mmkey)
अणु
	अगर (refcount_dec_and_test(&mmkey->usecount))
		wake_up(&mmkey->रुको);
पूर्ण

/* deref an mkey that can participate in ODP flow and रुको क्रम relese */
अटल अंतरभूत व्योम mlx5r_deref_रुको_odp_mkey(काष्ठा mlx5_core_mkey *mmkey)
अणु
	mlx5r_deref_odp_mkey(mmkey);
	रुको_event(mmkey->रुको, refcount_पढ़ो(&mmkey->usecount) == 0);
पूर्ण

पूर्णांक mlx5_ib_test_wc(काष्ठा mlx5_ib_dev *dev);

अटल अंतरभूत bool mlx5_ib_lag_should_assign_affinity(काष्ठा mlx5_ib_dev *dev)
अणु
	वापस dev->lag_active ||
		(MLX5_CAP_GEN(dev->mdev, num_lag_ports) > 1 &&
		 MLX5_CAP_GEN(dev->mdev, lag_tx_port_affinity));
पूर्ण
#पूर्ण_अगर /* MLX5_IB_H */
