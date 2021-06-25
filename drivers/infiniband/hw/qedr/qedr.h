<शैली गुरु>
/* QLogic qedr NIC Driver
 * Copyright (c) 2015-2016  QLogic Corporation
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
 *        disclaimer in the करोcumentation and /or other materials
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
#अगर_अघोषित __QEDR_H__
#घोषणा __QEDR_H__

#समावेश <linux/pci.h>
#समावेश <linux/xarray.h>
#समावेश <rdma/ib_addr.h>
#समावेश <linux/qed/qed_अगर.h>
#समावेश <linux/qed/qed_chain.h>
#समावेश <linux/qed/qed_rdma_अगर.h>
#समावेश <linux/qed/qede_rdma.h>
#समावेश <linux/qed/roce_common.h>
#समावेश <linux/completion.h>
#समावेश "qedr_hsi_rdma.h"

#घोषणा QEDR_NODE_DESC "QLogic 579xx RoCE HCA"
#घोषणा DP_NAME(_dev) dev_name(&(_dev)->ibdev.dev)
#घोषणा IS_IWARP(_dev) ((_dev)->rdma_type == QED_RDMA_TYPE_IWARP)
#घोषणा IS_ROCE(_dev) ((_dev)->rdma_type == QED_RDMA_TYPE_ROCE)

#घोषणा DP_DEBUG(dev, module, fmt, ...)					\
	pr_debug("(%s) " module ": " fmt,				\
		 DP_NAME(dev) ? DP_NAME(dev) : "", ## __VA_ARGS__)

#घोषणा QEDR_MSG_INIT "INIT"
#घोषणा QEDR_MSG_MISC "MISC"
#घोषणा QEDR_MSG_CQ   "  CQ"
#घोषणा QEDR_MSG_MR   "  MR"
#घोषणा QEDR_MSG_RQ   "  RQ"
#घोषणा QEDR_MSG_SQ   "  SQ"
#घोषणा QEDR_MSG_QP   "  QP"
#घोषणा QEDR_MSG_SRQ  " SRQ"
#घोषणा QEDR_MSG_GSI  " GSI"
#घोषणा QEDR_MSG_IWARP  " IW"

#घोषणा QEDR_CQ_MAGIC_NUMBER	(0x11223344)

#घोषणा FW_PAGE_SIZE		(RDMA_RING_PAGE_SIZE)
#घोषणा FW_PAGE_SHIFT		(12)

काष्ठा qedr_dev;

काष्ठा qedr_cnq अणु
	काष्ठा qedr_dev		*dev;
	काष्ठा qed_chain	pbl;
	काष्ठा qed_sb_info	*sb;
	अक्षर			name[32];
	u64			n_comp;
	__le16			*hw_cons_ptr;
	u8			index;
पूर्ण;

#घोषणा QEDR_MAX_SGID 128

काष्ठा qedr_device_attr अणु
	u32	venकरोr_id;
	u32	venकरोr_part_id;
	u32	hw_ver;
	u64	fw_ver;
	u64	node_guid;
	u64	sys_image_guid;
	u8	max_cnq;
	u8	max_sge;
	u16	max_अंतरभूत;
	u32	max_sqe;
	u32	max_rqe;
	u8	max_qp_resp_rd_atomic_resc;
	u8	max_qp_req_rd_atomic_resc;
	u64	max_dev_resp_rd_atomic_resc;
	u32	max_cq;
	u32	max_qp;
	u32	max_mr;
	u64	max_mr_size;
	u32	max_cqe;
	u32	max_mw;
	u32	max_mr_mw_fmr_pbl;
	u64	max_mr_mw_fmr_size;
	u32	max_pd;
	u32	max_ah;
	u8	max_pkey;
	u32	max_srq;
	u32	max_srq_wr;
	u8	max_srq_sge;
	u8	max_stats_queues;
	u32	dev_caps;

	u64	page_size_caps;
	u8	dev_ack_delay;
	u32	reserved_lkey;
	u32	bad_pkey_counter;
	काष्ठा qed_rdma_events events;
पूर्ण;

#घोषणा QEDR_ENET_STATE_BIT	(0)

काष्ठा qedr_dev अणु
	काष्ठा ib_device	ibdev;
	काष्ठा qed_dev		*cdev;
	काष्ठा pci_dev		*pdev;
	काष्ठा net_device	*ndev;

	क्रमागत ib_atomic_cap	atomic_cap;

	व्योम *rdma_ctx;
	काष्ठा qedr_device_attr attr;

	स्थिर काष्ठा qed_rdma_ops *ops;
	काष्ठा qed_पूर्णांक_info	पूर्णांक_info;

	काष्ठा qed_sb_info	*sb_array;
	काष्ठा qedr_cnq		*cnq_array;
	पूर्णांक			num_cnq;
	पूर्णांक			sb_start;

	व्योम __iomem		*db_addr;
	u64			db_phys_addr;
	u32			db_size;
	u16			dpi;

	जोड़ ib_gid *sgid_tbl;

	/* Lock क्रम sgid table */
	spinlock_t sgid_lock;

	u64			guid;

	u32			dp_module;
	u8			dp_level;
	u8			num_hwfns;
#घोषणा QEDR_IS_CMT(dev)        ((dev)->num_hwfns > 1)
	u8			affin_hwfn_idx;
	u8			gsi_ll2_handle;

	uपूर्णांक			wq_multiplier;
	u8			gsi_ll2_mac_address[ETH_ALEN];
	पूर्णांक			gsi_qp_created;
	काष्ठा qedr_cq		*gsi_sqcq;
	काष्ठा qedr_cq		*gsi_rqcq;
	काष्ठा qedr_qp		*gsi_qp;
	क्रमागत qed_rdma_type	rdma_type;
	काष्ठा xarray		qps;
	काष्ठा xarray		srqs;
	काष्ठा workqueue_काष्ठा *iwarp_wq;
	u16			iwarp_max_mtu;

	अचिन्हित दीर्घ enet_state;

	u8 user_dpm_enabled;
पूर्ण;

#घोषणा QEDR_MAX_SQ_PBL			(0x8000)
#घोषणा QEDR_MAX_SQ_PBL_ENTRIES		(0x10000 / माप(व्योम *))
#घोषणा QEDR_SQE_ELEMENT_SIZE		(माप(काष्ठा rdma_sq_sge))
#घोषणा QEDR_MAX_SQE_ELEMENTS_PER_SQE	(ROCE_REQ_MAX_SINGLE_SQ_WQE_SIZE / \
					 QEDR_SQE_ELEMENT_SIZE)
#घोषणा QEDR_MAX_SQE_ELEMENTS_PER_PAGE	((RDMA_RING_PAGE_SIZE) / \
					 QEDR_SQE_ELEMENT_SIZE)
#घोषणा QEDR_MAX_SQE			((QEDR_MAX_SQ_PBL_ENTRIES) *\
					 (RDMA_RING_PAGE_SIZE) / \
					 (QEDR_SQE_ELEMENT_SIZE) /\
					 (QEDR_MAX_SQE_ELEMENTS_PER_SQE))
/* RQ */
#घोषणा QEDR_MAX_RQ_PBL			(0x2000)
#घोषणा QEDR_MAX_RQ_PBL_ENTRIES		(0x10000 / माप(व्योम *))
#घोषणा QEDR_RQE_ELEMENT_SIZE		(माप(काष्ठा rdma_rq_sge))
#घोषणा QEDR_MAX_RQE_ELEMENTS_PER_RQE	(RDMA_MAX_SGE_PER_RQ_WQE)
#घोषणा QEDR_MAX_RQE_ELEMENTS_PER_PAGE	((RDMA_RING_PAGE_SIZE) / \
					 QEDR_RQE_ELEMENT_SIZE)
#घोषणा QEDR_MAX_RQE			((QEDR_MAX_RQ_PBL_ENTRIES) *\
					 (RDMA_RING_PAGE_SIZE) / \
					 (QEDR_RQE_ELEMENT_SIZE) /\
					 (QEDR_MAX_RQE_ELEMENTS_PER_RQE))

#घोषणा QEDR_CQE_SIZE	(माप(जोड़ rdma_cqe))
#घोषणा QEDR_MAX_CQE_PBL_SIZE (512 * 1024)
#घोषणा QEDR_MAX_CQE_PBL_ENTRIES (((QEDR_MAX_CQE_PBL_SIZE) / \
				  माप(u64)) - 1)
#घोषणा QEDR_MAX_CQES ((u32)((QEDR_MAX_CQE_PBL_ENTRIES) * \
			     (QED_CHAIN_PAGE_SIZE) / QEDR_CQE_SIZE))

#घोषणा QEDR_ROCE_MAX_CNQ_SIZE		(0x4000)

#घोषणा QEDR_MAX_PORT			(1)
#घोषणा QEDR_PORT			(1)

#घोषणा QEDR_UVERBS(CMD_NAME) (1ull << IB_USER_VERBS_CMD_##CMD_NAME)

#घोषणा QEDR_ROCE_PKEY_MAX 1
#घोषणा QEDR_ROCE_PKEY_TABLE_LEN 1
#घोषणा QEDR_ROCE_PKEY_DEFAULT 0xffff

काष्ठा qedr_pbl अणु
	काष्ठा list_head list_entry;
	व्योम *va;
	dma_addr_t pa;
पूर्ण;

काष्ठा qedr_ucontext अणु
	काष्ठा ib_ucontext ibucontext;
	काष्ठा qedr_dev *dev;
	काष्ठा qedr_pd *pd;
	व्योम __iomem *dpi_addr;
	काष्ठा rdma_user_mmap_entry *db_mmap_entry;
	u64 dpi_phys_addr;
	u32 dpi_size;
	u16 dpi;
	bool db_rec;
	u8 edpm_mode;
पूर्ण;

जोड़ db_prod32 अणु
	काष्ठा rdma_pwm_val16_data data;
	u32 raw;
पूर्ण;

जोड़ db_prod64 अणु
	काष्ठा rdma_pwm_val32_data data;
	u64 raw;
पूर्ण;

क्रमागत qedr_cq_type अणु
	QEDR_CQ_TYPE_GSI,
	QEDR_CQ_TYPE_KERNEL,
	QEDR_CQ_TYPE_USER,
पूर्ण;

काष्ठा qedr_pbl_info अणु
	u32 num_pbls;
	u32 num_pbes;
	u32 pbl_size;
	u32 pbe_size;
	bool two_layered;
पूर्ण;

काष्ठा qedr_userq अणु
	काष्ठा ib_umem *umem;
	काष्ठा qedr_pbl_info pbl_info;
	काष्ठा qedr_pbl *pbl_tbl;
	u64 buf_addr;
	माप_प्रकार buf_len;

	/* करोorbell recovery */
	व्योम __iomem *db_addr;
	काष्ठा qedr_user_db_rec *db_rec_data;
	काष्ठा rdma_user_mmap_entry *db_mmap_entry;
	व्योम __iomem *db_rec_db2_addr;
	जोड़ db_prod32 db_rec_db2_data;
पूर्ण;

काष्ठा qedr_cq अणु
	काष्ठा ib_cq ibcq;

	क्रमागत qedr_cq_type cq_type;
	u32 sig;

	u16 icid;

	/* Lock to protect multiplem CQ's */
	spinlock_t cq_lock;
	u8 arm_flags;
	काष्ठा qed_chain pbl;

	व्योम __iomem *db_addr;
	जोड़ db_prod64 db;

	u8 pbl_toggle;
	जोड़ rdma_cqe *latest_cqe;
	जोड़ rdma_cqe *toggle_cqe;

	u32 cq_cons;

	काष्ठा qedr_userq q;
	u8 destroyed;
	u16 cnq_notअगर;
पूर्ण;

काष्ठा qedr_pd अणु
	काष्ठा ib_pd ibpd;
	u32 pd_id;
	काष्ठा qedr_ucontext *uctx;
पूर्ण;

काष्ठा qedr_xrcd अणु
	काष्ठा ib_xrcd ibxrcd;
	u16 xrcd_id;
पूर्ण;

काष्ठा qedr_qp_hwq_info अणु
	/* WQE Elements */
	काष्ठा qed_chain pbl;
	u64 p_phys_addr_tbl;
	u32 max_sges;

	/* WQE */
	u16 prod;
	u16 cons;
	u16 wqe_cons;
	u16 gsi_cons;
	u16 max_wr;

	/* DB */
	व्योम __iomem *db;
	जोड़ db_prod32 db_data;

	व्योम __iomem *iwarp_db2;
	जोड़ db_prod32 iwarp_db2_data;
पूर्ण;

#घोषणा QEDR_INC_SW_IDX(p_info, index)					\
	करो अणु								\
		p_info->index = (p_info->index + 1) &			\
				qed_chain_get_capacity(p_info->pbl)	\
	पूर्ण जबतक (0)

काष्ठा qedr_srq_hwq_info अणु
	u32 max_sges;
	u32 max_wr;
	काष्ठा qed_chain pbl;
	u64 p_phys_addr_tbl;
	u32 wqe_prod;
	u32 sge_prod;
	u32 wr_prod_cnt;
	atomic_t wr_cons_cnt;
	u32 num_elems;

	काष्ठा rdma_srq_producers *virt_prod_pair_addr;
	dma_addr_t phy_prod_pair_addr;
पूर्ण;

काष्ठा qedr_srq अणु
	काष्ठा ib_srq ibsrq;
	काष्ठा qedr_dev *dev;

	काष्ठा qedr_userq	usrq;
	काष्ठा qedr_srq_hwq_info hw_srq;
	काष्ठा ib_umem *prod_umem;
	u16 srq_id;
	u32 srq_limit;
	bool is_xrc;
	/* lock to protect srq recv post */
	spinlock_t lock;
पूर्ण;

क्रमागत qedr_qp_err_biपंचांगap अणु
	QEDR_QP_ERR_SQ_FULL = 1,
	QEDR_QP_ERR_RQ_FULL = 2,
	QEDR_QP_ERR_BAD_SR = 4,
	QEDR_QP_ERR_BAD_RR = 8,
	QEDR_QP_ERR_SQ_PBL_FULL = 16,
	QEDR_QP_ERR_RQ_PBL_FULL = 32,
पूर्ण;

क्रमागत qedr_qp_create_type अणु
	QEDR_QP_CREATE_NONE,
	QEDR_QP_CREATE_USER,
	QEDR_QP_CREATE_KERNEL,
पूर्ण;

क्रमागत qedr_iwarp_cm_flags अणु
	QEDR_IWARP_CM_WAIT_FOR_CONNECT    = BIT(0),
	QEDR_IWARP_CM_WAIT_FOR_DISCONNECT = BIT(1),
पूर्ण;

काष्ठा qedr_qp अणु
	काष्ठा ib_qp ibqp;	/* must be first */
	काष्ठा qedr_dev *dev;
	काष्ठा qedr_qp_hwq_info sq;
	काष्ठा qedr_qp_hwq_info rq;

	u32 max_अंतरभूत_data;

	/* Lock क्रम QP's */
	spinlock_t q_lock;
	काष्ठा qedr_cq *sq_cq;
	काष्ठा qedr_cq *rq_cq;
	काष्ठा qedr_srq *srq;
	क्रमागत qed_roce_qp_state state;
	u32 id;
	काष्ठा qedr_pd *pd;
	क्रमागत ib_qp_type qp_type;
	क्रमागत qedr_qp_create_type create_type;
	काष्ठा qed_rdma_qp *qed_qp;
	u32 qp_id;
	u16 icid;
	u16 mtu;
	पूर्णांक sgid_idx;
	u32 rq_psn;
	u32 sq_psn;
	u32 qkey;
	u32 dest_qp_num;

	/* Relevant to qps created from kernel space only (ULPs) */
	u8 prev_wqe_size;
	u16 wqe_cons;
	u32 err_biपंचांगap;
	bool संकेतed;

	/* SQ shaकरोw */
	काष्ठा अणु
		u64 wr_id;
		क्रमागत ib_wc_opcode opcode;
		u32 bytes_len;
		u8 wqe_size;
		bool संकेतed;
		dma_addr_t icrc_mapping;
		u32 *icrc;
		काष्ठा qedr_mr *mr;
	पूर्ण *wqe_wr_id;

	/* RQ shaकरोw */
	काष्ठा अणु
		u64 wr_id;
		काष्ठा ib_sge sg_list[RDMA_MAX_SGE_PER_RQ_WQE];
		u8 wqe_size;

		u8 smac[ETH_ALEN];
		u16 vlan;
		पूर्णांक rc;
	पूर्ण *rqe_wr_id;

	/* Relevant to qps created from user space only (applications) */
	काष्ठा qedr_userq usq;
	काष्ठा qedr_userq urq;

	/* synchronization objects used with iwarp ep */
	काष्ठा kref refcnt;
	काष्ठा completion iwarp_cm_comp;
	अचिन्हित दीर्घ iwarp_cm_flags; /* क्रमागत iwarp_cm_flags */
पूर्ण;

काष्ठा qedr_ah अणु
	काष्ठा ib_ah ibah;
	काष्ठा rdma_ah_attr attr;
पूर्ण;

क्रमागत qedr_mr_type अणु
	QEDR_MR_USER,
	QEDR_MR_KERNEL,
	QEDR_MR_DMA,
	QEDR_MR_FRMR,
पूर्ण;

काष्ठा mr_info अणु
	काष्ठा qedr_pbl *pbl_table;
	काष्ठा qedr_pbl_info pbl_info;
	काष्ठा list_head मुक्त_pbl_list;
	काष्ठा list_head inuse_pbl_list;
	u32 completed;
	u32 completed_handled;
पूर्ण;

काष्ठा qedr_mr अणु
	काष्ठा ib_mr ibmr;
	काष्ठा ib_umem *umem;

	काष्ठा qed_rdma_रेजिस्टर_tid_in_params hw_mr;
	क्रमागत qedr_mr_type type;

	काष्ठा qedr_dev *dev;
	काष्ठा mr_info info;

	u64 *pages;
	u32 npages;
पूर्ण;

काष्ठा qedr_user_mmap_entry अणु
	काष्ठा rdma_user_mmap_entry rdma_entry;
	काष्ठा qedr_dev *dev;
	जोड़ अणु
		u64 io_address;
		व्योम *address;
	पूर्ण;
	माप_प्रकार length;
	u16 dpi;
	u8 mmap_flag;
पूर्ण;

#घोषणा SET_FIELD2(value, name, flag) ((value) |= ((flag) << (name ## _SHIFT)))

#घोषणा QEDR_RESP_IMM	(RDMA_CQE_RESPONDER_IMM_FLG_MASK << \
			 RDMA_CQE_RESPONDER_IMM_FLG_SHIFT)
#घोषणा QEDR_RESP_RDMA	(RDMA_CQE_RESPONDER_RDMA_FLG_MASK << \
			 RDMA_CQE_RESPONDER_RDMA_FLG_SHIFT)
#घोषणा QEDR_RESP_INV	(RDMA_CQE_RESPONDER_INV_FLG_MASK << \
			 RDMA_CQE_RESPONDER_INV_FLG_SHIFT)

अटल अंतरभूत व्योम qedr_inc_sw_cons(काष्ठा qedr_qp_hwq_info *info)
अणु
	info->cons = (info->cons + 1) % info->max_wr;
	info->wqe_cons++;
पूर्ण

अटल अंतरभूत व्योम qedr_inc_sw_prod(काष्ठा qedr_qp_hwq_info *info)
अणु
	info->prod = (info->prod + 1) % info->max_wr;
पूर्ण

अटल अंतरभूत पूर्णांक qedr_get_dmac(काष्ठा qedr_dev *dev,
				काष्ठा rdma_ah_attr *ah_attr, u8 *mac_addr)
अणु
	जोड़ ib_gid zero_sgid = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा in6_addr in6;
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(ah_attr);
	u8 *dmac;

	अगर (!स_भेद(&grh->dgid, &zero_sgid, माप(जोड़ ib_gid))) अणु
		DP_ERR(dev, "Local port GID not supported\n");
		eth_zero_addr(mac_addr);
		वापस -EINVAL;
	पूर्ण

	स_नकल(&in6, grh->dgid.raw, माप(in6));
	dmac = rdma_ah_retrieve_dmac(ah_attr);
	अगर (!dmac)
		वापस -EINVAL;
	ether_addr_copy(mac_addr, dmac);

	वापस 0;
पूर्ण

काष्ठा qedr_iw_listener अणु
	काष्ठा qedr_dev *dev;
	काष्ठा iw_cm_id *cm_id;
	पूर्णांक		backlog;
	व्योम		*qed_handle;
पूर्ण;

काष्ठा qedr_iw_ep अणु
	काष्ठा qedr_dev	*dev;
	काष्ठा iw_cm_id	*cm_id;
	काष्ठा qedr_qp	*qp;
	व्योम		*qed_context;
	काष्ठा kref	refcnt;
पूर्ण;

अटल अंतरभूत
काष्ठा qedr_ucontext *get_qedr_ucontext(काष्ठा ib_ucontext *ibucontext)
अणु
	वापस container_of(ibucontext, काष्ठा qedr_ucontext, ibucontext);
पूर्ण

अटल अंतरभूत काष्ठा qedr_dev *get_qedr_dev(काष्ठा ib_device *ibdev)
अणु
	वापस container_of(ibdev, काष्ठा qedr_dev, ibdev);
पूर्ण

अटल अंतरभूत काष्ठा qedr_pd *get_qedr_pd(काष्ठा ib_pd *ibpd)
अणु
	वापस container_of(ibpd, काष्ठा qedr_pd, ibpd);
पूर्ण

अटल अंतरभूत काष्ठा qedr_xrcd *get_qedr_xrcd(काष्ठा ib_xrcd *ibxrcd)
अणु
	वापस container_of(ibxrcd, काष्ठा qedr_xrcd, ibxrcd);
पूर्ण

अटल अंतरभूत काष्ठा qedr_cq *get_qedr_cq(काष्ठा ib_cq *ibcq)
अणु
	वापस container_of(ibcq, काष्ठा qedr_cq, ibcq);
पूर्ण

अटल अंतरभूत काष्ठा qedr_qp *get_qedr_qp(काष्ठा ib_qp *ibqp)
अणु
	वापस container_of(ibqp, काष्ठा qedr_qp, ibqp);
पूर्ण

अटल अंतरभूत काष्ठा qedr_ah *get_qedr_ah(काष्ठा ib_ah *ibah)
अणु
	वापस container_of(ibah, काष्ठा qedr_ah, ibah);
पूर्ण

अटल अंतरभूत काष्ठा qedr_mr *get_qedr_mr(काष्ठा ib_mr *ibmr)
अणु
	वापस container_of(ibmr, काष्ठा qedr_mr, ibmr);
पूर्ण

अटल अंतरभूत काष्ठा qedr_srq *get_qedr_srq(काष्ठा ib_srq *ibsrq)
अणु
	वापस container_of(ibsrq, काष्ठा qedr_srq, ibsrq);
पूर्ण

अटल अंतरभूत bool qedr_qp_has_srq(काष्ठा qedr_qp *qp)
अणु
	वापस qp->srq;
पूर्ण

अटल अंतरभूत bool qedr_qp_has_sq(काष्ठा qedr_qp *qp)
अणु
	अगर (qp->qp_type == IB_QPT_GSI || qp->qp_type == IB_QPT_XRC_TGT)
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत bool qedr_qp_has_rq(काष्ठा qedr_qp *qp)
अणु
	अगर (qp->qp_type == IB_QPT_GSI || qp->qp_type == IB_QPT_XRC_INI ||
	    qp->qp_type == IB_QPT_XRC_TGT || qedr_qp_has_srq(qp))
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत काष्ठा qedr_user_mmap_entry *
get_qedr_mmap_entry(काष्ठा rdma_user_mmap_entry *rdma_entry)
अणु
	वापस container_of(rdma_entry, काष्ठा qedr_user_mmap_entry,
			    rdma_entry);
पूर्ण
#पूर्ण_अगर
