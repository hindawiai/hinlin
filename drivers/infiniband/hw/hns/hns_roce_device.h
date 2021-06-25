<शैली गुरु>
/*
 * Copyright (c) 2016 Hisilicon Limited.
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

#अगर_अघोषित _HNS_ROCE_DEVICE_H
#घोषणा _HNS_ROCE_DEVICE_H

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/hns-abi.h>

#घोषणा DRV_NAME "hns_roce"

#घोषणा PCI_REVISION_ID_HIP08			0x21
#घोषणा PCI_REVISION_ID_HIP09			0x30

#घोषणा HNS_ROCE_HW_VER1	('h' << 24 | 'i' << 16 | '0' << 8 | '6')

#घोषणा HNS_ROCE_MAX_MSG_LEN			0x80000000

#घोषणा HNS_ROCE_IB_MIN_SQ_STRIDE		6

#घोषणा HNS_ROCE_BA_SIZE			(32 * 4096)

#घोषणा BA_BYTE_LEN				8

/* Hardware specअगरication only क्रम v1 engine */
#घोषणा HNS_ROCE_MIN_CQE_NUM			0x40
#घोषणा HNS_ROCE_MIN_WQE_NUM			0x20
#घोषणा HNS_ROCE_MIN_SRQ_WQE_NUM		1

/* Hardware specअगरication only क्रम v1 engine */
#घोषणा HNS_ROCE_MAX_INNER_MTPT_NUM		0x7
#घोषणा HNS_ROCE_MAX_MTPT_PBL_NUM		0x100000

#घोषणा HNS_ROCE_EACH_FREE_CQ_WAIT_MSECS	20
#घोषणा HNS_ROCE_MAX_FREE_CQ_WAIT_CNT	\
	(5000 / HNS_ROCE_EACH_FREE_CQ_WAIT_MSECS)
#घोषणा HNS_ROCE_CQE_WCMD_EMPTY_BIT		0x2
#घोषणा HNS_ROCE_MIN_CQE_CNT			16

#घोषणा HNS_ROCE_RESERVED_SGE			1

#घोषणा HNS_ROCE_MAX_IRQ_NUM			128

#घोषणा HNS_ROCE_SGE_IN_WQE			2
#घोषणा HNS_ROCE_SGE_SHIFT			4

#घोषणा EQ_ENABLE				1
#घोषणा EQ_DISABLE				0

#घोषणा HNS_ROCE_CEQ				0
#घोषणा HNS_ROCE_AEQ				1

#घोषणा HNS_ROCE_CEQE_SIZE 0x4
#घोषणा HNS_ROCE_AEQE_SIZE 0x10

#घोषणा HNS_ROCE_V3_EQE_SIZE 0x40

#घोषणा HNS_ROCE_V2_CQE_SIZE 32
#घोषणा HNS_ROCE_V3_CQE_SIZE 64

#घोषणा HNS_ROCE_V2_QPC_SZ 256
#घोषणा HNS_ROCE_V3_QPC_SZ 512

#घोषणा HNS_ROCE_MAX_PORTS			6
#घोषणा HNS_ROCE_GID_SIZE			16
#घोषणा HNS_ROCE_SGE_SIZE			16
#घोषणा HNS_ROCE_DWQE_SIZE			65536

#घोषणा HNS_ROCE_HOP_NUM_0			0xff

#घोषणा BITMAP_NO_RR				0
#घोषणा BITMAP_RR				1

#घोषणा MR_TYPE_MR				0x00
#घोषणा MR_TYPE_FRMR				0x01
#घोषणा MR_TYPE_DMA				0x03

#घोषणा HNS_ROCE_FRMR_MAX_PA			512

#घोषणा PKEY_ID					0xffff
#घोषणा GUID_LEN				8
#घोषणा NODE_DESC_SIZE				64
#घोषणा DB_REG_OFFSET				0x1000

/* Configure to HW क्रम PAGE_SIZE larger than 4KB */
#घोषणा PG_SHIFT_OFFSET				(PAGE_SHIFT - 12)

#घोषणा PAGES_SHIFT_8				8
#घोषणा PAGES_SHIFT_16				16
#घोषणा PAGES_SHIFT_24				24
#घोषणा PAGES_SHIFT_32				32

#घोषणा HNS_ROCE_IDX_QUE_ENTRY_SZ		4
#घोषणा SRQ_DB_REG				0x230

#घोषणा HNS_ROCE_QP_BANK_NUM 8
#घोषणा HNS_ROCE_CQ_BANK_NUM 4

#घोषणा CQ_BANKID_SHIFT 2

/* The chip implementation of the consumer index is calculated
 * according to twice the actual EQ depth
 */
#घोषणा EQ_DEPTH_COEFF				2

क्रमागत अणु
	SERV_TYPE_RC,
	SERV_TYPE_UC,
	SERV_TYPE_RD,
	SERV_TYPE_UD,
	SERV_TYPE_XRC = 5,
पूर्ण;

क्रमागत hns_roce_qp_state अणु
	HNS_ROCE_QP_STATE_RST,
	HNS_ROCE_QP_STATE_INIT,
	HNS_ROCE_QP_STATE_RTR,
	HNS_ROCE_QP_STATE_RTS,
	HNS_ROCE_QP_STATE_SQD,
	HNS_ROCE_QP_STATE_ERR,
	HNS_ROCE_QP_NUM_STATE,
पूर्ण;

क्रमागत hns_roce_event अणु
	HNS_ROCE_EVENT_TYPE_PATH_MIG                  = 0x01,
	HNS_ROCE_EVENT_TYPE_PATH_MIG_FAILED           = 0x02,
	HNS_ROCE_EVENT_TYPE_COMM_EST                  = 0x03,
	HNS_ROCE_EVENT_TYPE_SQ_DRAINED                = 0x04,
	HNS_ROCE_EVENT_TYPE_WQ_CATAS_ERROR            = 0x05,
	HNS_ROCE_EVENT_TYPE_INV_REQ_LOCAL_WQ_ERROR    = 0x06,
	HNS_ROCE_EVENT_TYPE_LOCAL_WQ_ACCESS_ERROR     = 0x07,
	HNS_ROCE_EVENT_TYPE_SRQ_LIMIT_REACH           = 0x08,
	HNS_ROCE_EVENT_TYPE_SRQ_LAST_WQE_REACH        = 0x09,
	HNS_ROCE_EVENT_TYPE_SRQ_CATAS_ERROR           = 0x0a,
	HNS_ROCE_EVENT_TYPE_CQ_ACCESS_ERROR           = 0x0b,
	HNS_ROCE_EVENT_TYPE_CQ_OVERFLOW               = 0x0c,
	HNS_ROCE_EVENT_TYPE_CQ_ID_INVALID             = 0x0d,
	HNS_ROCE_EVENT_TYPE_PORT_CHANGE               = 0x0f,
	/* 0x10 and 0x11 is unused in currently application हाल */
	HNS_ROCE_EVENT_TYPE_DB_OVERFLOW               = 0x12,
	HNS_ROCE_EVENT_TYPE_MB                        = 0x13,
	HNS_ROCE_EVENT_TYPE_FLR			      = 0x15,
	HNS_ROCE_EVENT_TYPE_XRCD_VIOLATION	      = 0x16,
	HNS_ROCE_EVENT_TYPE_INVALID_XRCETH	      = 0x17,
पूर्ण;

#घोषणा HNS_ROCE_CAP_FLAGS_EX_SHIFT 12

क्रमागत अणु
	HNS_ROCE_CAP_FLAG_REREG_MR		= BIT(0),
	HNS_ROCE_CAP_FLAG_ROCE_V1_V2		= BIT(1),
	HNS_ROCE_CAP_FLAG_RQ_INLINE		= BIT(2),
	HNS_ROCE_CAP_FLAG_CQ_RECORD_DB		= BIT(3),
	HNS_ROCE_CAP_FLAG_QP_RECORD_DB		= BIT(4),
	HNS_ROCE_CAP_FLAG_SRQ			= BIT(5),
	HNS_ROCE_CAP_FLAG_XRC			= BIT(6),
	HNS_ROCE_CAP_FLAG_MW			= BIT(7),
	HNS_ROCE_CAP_FLAG_FRMR                  = BIT(8),
	HNS_ROCE_CAP_FLAG_QP_FLOW_CTRL		= BIT(9),
	HNS_ROCE_CAP_FLAG_ATOMIC		= BIT(10),
	HNS_ROCE_CAP_FLAG_SDI_MODE		= BIT(14),
	HNS_ROCE_CAP_FLAG_STASH			= BIT(17),
पूर्ण;

#घोषणा HNS_ROCE_DB_TYPE_COUNT			2
#घोषणा HNS_ROCE_DB_UNIT_SIZE			4

क्रमागत अणु
	HNS_ROCE_DB_PER_PAGE = PAGE_SIZE / 4
पूर्ण;

क्रमागत hns_roce_reset_stage अणु
	HNS_ROCE_STATE_NON_RST,
	HNS_ROCE_STATE_RST_BEF_DOWN,
	HNS_ROCE_STATE_RST_DOWN,
	HNS_ROCE_STATE_RST_UNINIT,
	HNS_ROCE_STATE_RST_INIT,
	HNS_ROCE_STATE_RST_INITED,
पूर्ण;

क्रमागत hns_roce_instance_state अणु
	HNS_ROCE_STATE_NON_INIT,
	HNS_ROCE_STATE_INIT,
	HNS_ROCE_STATE_INITED,
	HNS_ROCE_STATE_UNINIT,
पूर्ण;

क्रमागत अणु
	HNS_ROCE_RST_सूचीECT_RETURN		= 0,
पूर्ण;

#घोषणा HNS_ROCE_CMD_SUCCESS			1

/* The minimum page size is 4K क्रम hardware */
#घोषणा HNS_HW_PAGE_SHIFT			12
#घोषणा HNS_HW_PAGE_SIZE			(1 << HNS_HW_PAGE_SHIFT)

काष्ठा hns_roce_uar अणु
	u64		pfn;
	अचिन्हित दीर्घ	index;
	अचिन्हित दीर्घ	logic_idx;
पूर्ण;

काष्ठा hns_roce_ucontext अणु
	काष्ठा ib_ucontext	ibucontext;
	काष्ठा hns_roce_uar	uar;
	काष्ठा list_head	page_list;
	काष्ठा mutex		page_mutex;
पूर्ण;

काष्ठा hns_roce_pd अणु
	काष्ठा ib_pd		ibpd;
	अचिन्हित दीर्घ		pdn;
पूर्ण;

काष्ठा hns_roce_xrcd अणु
	काष्ठा ib_xrcd ibxrcd;
	u32 xrcdn;
पूर्ण;

काष्ठा hns_roce_biपंचांगap अणु
	/* Biपंचांगap Traversal last a bit which is 1 */
	अचिन्हित दीर्घ		last;
	अचिन्हित दीर्घ		top;
	अचिन्हित दीर्घ		max;
	अचिन्हित दीर्घ		reserved_top;
	अचिन्हित दीर्घ		mask;
	spinlock_t		lock;
	अचिन्हित दीर्घ		*table;
पूर्ण;

/* For Hardware Entry Memory */
काष्ठा hns_roce_hem_table अणु
	/* HEM type: 0 = qpc, 1 = mtt, 2 = cqc, 3 = srq, 4 = other */
	u32		type;
	/* HEM array elment num */
	अचिन्हित दीर्घ	num_hem;
	/* HEM entry record obj total num */
	अचिन्हित दीर्घ	num_obj;
	/* Single obj size */
	अचिन्हित दीर्घ	obj_size;
	अचिन्हित दीर्घ	table_chunk_size;
	पूर्णांक		lowmem;
	काष्ठा mutex	mutex;
	काष्ठा hns_roce_hem **hem;
	u64		**bt_l1;
	dma_addr_t	*bt_l1_dma_addr;
	u64		**bt_l0;
	dma_addr_t	*bt_l0_dma_addr;
पूर्ण;

काष्ठा hns_roce_buf_region अणु
	u32 offset; /* page offset */
	u32 count; /* page count */
	पूर्णांक hopnum; /* addressing hop num */
पूर्ण;

#घोषणा HNS_ROCE_MAX_BT_REGION	3
#घोषणा HNS_ROCE_MAX_BT_LEVEL	3
काष्ठा hns_roce_hem_list अणु
	काष्ठा list_head root_bt;
	/* link all bt dma mem by hop config */
	काष्ठा list_head mid_bt[HNS_ROCE_MAX_BT_REGION][HNS_ROCE_MAX_BT_LEVEL];
	काष्ठा list_head bपंचांग_bt; /* link all bottom bt in @mid_bt */
	dma_addr_t root_ba; /* poपूर्णांकer to the root ba table */
पूर्ण;

काष्ठा hns_roce_buf_attr अणु
	काष्ठा अणु
		माप_प्रकार	size;  /* region size */
		पूर्णांक	hopnum; /* multi-hop addressing hop num */
	पूर्ण region[HNS_ROCE_MAX_BT_REGION];
	अचिन्हित पूर्णांक region_count; /* valid region count */
	अचिन्हित पूर्णांक page_shअगरt;  /* buffer page shअगरt */
	अचिन्हित पूर्णांक user_access; /* umem access flag */
	bool mtt_only; /* only alloc buffer-required MTT memory */
पूर्ण;

काष्ठा hns_roce_hem_cfg अणु
	dma_addr_t	root_ba; /* root BA table's address */
	bool		is_direct; /* addressing without BA table */
	अचिन्हित पूर्णांक	ba_pg_shअगरt; /* BA table page shअगरt */
	अचिन्हित पूर्णांक	buf_pg_shअगरt; /* buffer page shअगरt */
	अचिन्हित पूर्णांक	buf_pg_count;  /* buffer page count */
	काष्ठा hns_roce_buf_region region[HNS_ROCE_MAX_BT_REGION];
	अचिन्हित पूर्णांक	region_count;
पूर्ण;

/* memory translate region */
काष्ठा hns_roce_mtr अणु
	काष्ठा hns_roce_hem_list hem_list; /* multi-hop addressing resource */
	काष्ठा ib_umem		*umem; /* user space buffer */
	काष्ठा hns_roce_buf	*kmem; /* kernel space buffer */
	काष्ठा hns_roce_hem_cfg  hem_cfg; /* config क्रम hardware addressing */
पूर्ण;

काष्ठा hns_roce_mw अणु
	काष्ठा ib_mw		ibmw;
	u32			pdn;
	u32			rkey;
	पूर्णांक			enabled; /* MW's active status */
	u32			pbl_hop_num;
	u32			pbl_ba_pg_sz;
	u32			pbl_buf_pg_sz;
पूर्ण;

/* Only support 4K page size क्रम mr रेजिस्टर */
#घोषणा MR_SIZE_4K 0

काष्ठा hns_roce_mr अणु
	काष्ठा ib_mr		ibmr;
	u64			iova; /* MR's भव orignal addr */
	u64			size; /* Address range of MR */
	u32			key; /* Key of MR */
	u32			pd;   /* PD num of MR */
	u32			access;	/* Access permission of MR */
	पूर्णांक			enabled; /* MR's active status */
	पूर्णांक			type;	/* MR's रेजिस्टर type */
	u32			pbl_hop_num;	/* multi-hop number */
	काष्ठा hns_roce_mtr	pbl_mtr;
	u32			npages;
	dma_addr_t		*page_list;
पूर्ण;

काष्ठा hns_roce_mr_table अणु
	काष्ठा hns_roce_biपंचांगap		mtpt_biपंचांगap;
	काष्ठा hns_roce_hem_table	mtpt_table;
पूर्ण;

काष्ठा hns_roce_wq अणु
	u64		*wrid;     /* Work request ID */
	spinlock_t	lock;
	u32		wqe_cnt;  /* WQE num */
	u32		max_gs;
	u32		rsv_sge;
	पूर्णांक		offset;
	पूर्णांक		wqe_shअगरt;	/* WQE size */
	u32		head;
	u32		tail;
	व्योम __iomem	*db_reg;
पूर्ण;

काष्ठा hns_roce_sge अणु
	अचिन्हित पूर्णांक	sge_cnt;	/* SGE num */
	पूर्णांक		offset;
	पूर्णांक		sge_shअगरt;	/* SGE size */
पूर्ण;

काष्ठा hns_roce_buf_list अणु
	व्योम		*buf;
	dma_addr_t	map;
पूर्ण;

/*
 * %HNS_ROCE_BUF_सूचीECT indicates that the all memory must be in a continuous
 * dma address range.
 *
 * %HNS_ROCE_BUF_NOSLEEP indicates that the caller cannot sleep.
 *
 * %HNS_ROCE_BUF_NOFAIL allocation only failed when allocated size is zero, even
 * the allocated size is smaller than the required size.
 */
क्रमागत अणु
	HNS_ROCE_BUF_सूचीECT = BIT(0),
	HNS_ROCE_BUF_NOSLEEP = BIT(1),
	HNS_ROCE_BUF_NOFAIL = BIT(2),
पूर्ण;

काष्ठा hns_roce_buf अणु
	काष्ठा hns_roce_buf_list	*trunk_list;
	u32				ntrunks;
	u32				npages;
	अचिन्हित पूर्णांक			trunk_shअगरt;
	अचिन्हित पूर्णांक			page_shअगरt;
पूर्ण;

काष्ठा hns_roce_db_pgdir अणु
	काष्ठा list_head	list;
	DECLARE_BITMAP(order0, HNS_ROCE_DB_PER_PAGE);
	DECLARE_BITMAP(order1, HNS_ROCE_DB_PER_PAGE / HNS_ROCE_DB_TYPE_COUNT);
	अचिन्हित दीर्घ		*bits[HNS_ROCE_DB_TYPE_COUNT];
	u32			*page;
	dma_addr_t		db_dma;
पूर्ण;

काष्ठा hns_roce_user_db_page अणु
	काष्ठा list_head	list;
	काष्ठा ib_umem		*umem;
	अचिन्हित दीर्घ		user_virt;
	refcount_t		refcount;
पूर्ण;

काष्ठा hns_roce_db अणु
	u32		*db_record;
	जोड़ अणु
		काष्ठा hns_roce_db_pgdir *pgdir;
		काष्ठा hns_roce_user_db_page *user_page;
	पूर्ण u;
	dma_addr_t	dma;
	व्योम		*virt_addr;
	अचिन्हित दीर्घ	index;
	अचिन्हित दीर्घ	order;
पूर्ण;

काष्ठा hns_roce_cq अणु
	काष्ठा ib_cq			ib_cq;
	काष्ठा hns_roce_mtr		mtr;
	काष्ठा hns_roce_db		db;
	u32				flags;
	spinlock_t			lock;
	u32				cq_depth;
	u32				cons_index;
	u32				*set_ci_db;
	व्योम __iomem			*db_reg;
	u16				*tptr_addr;
	पूर्णांक				arm_sn;
	पूर्णांक				cqe_size;
	अचिन्हित दीर्घ			cqn;
	u32				vector;
	atomic_t			refcount;
	काष्ठा completion		मुक्त;
	काष्ठा list_head		sq_list; /* all qps on this send cq */
	काष्ठा list_head		rq_list; /* all qps on this recv cq */
	पूर्णांक				is_armed; /* cq is armed */
	काष्ठा list_head		node; /* all armed cqs are on a list */
पूर्ण;

काष्ठा hns_roce_idx_que अणु
	काष्ठा hns_roce_mtr		mtr;
	पूर्णांक				entry_shअगरt;
	अचिन्हित दीर्घ			*biपंचांगap;
	u32				head;
	u32				tail;
पूर्ण;

काष्ठा hns_roce_srq अणु
	काष्ठा ib_srq		ibsrq;
	अचिन्हित दीर्घ		srqn;
	u32			wqe_cnt;
	पूर्णांक			max_gs;
	u32			rsv_sge;
	पूर्णांक			wqe_shअगरt;
	u32			cqn;
	u32			xrcdn;
	व्योम __iomem		*db_reg;

	atomic_t		refcount;
	काष्ठा completion	मुक्त;

	काष्ठा hns_roce_mtr	buf_mtr;

	u64		       *wrid;
	काष्ठा hns_roce_idx_que idx_que;
	spinlock_t		lock;
	काष्ठा mutex		mutex;
	व्योम (*event)(काष्ठा hns_roce_srq *srq, क्रमागत hns_roce_event event);
पूर्ण;

काष्ठा hns_roce_uar_table अणु
	काष्ठा hns_roce_biपंचांगap biपंचांगap;
पूर्ण;

काष्ठा hns_roce_bank अणु
	काष्ठा ida ida;
	u32 inuse; /* Number of IDs allocated */
	u32 min; /* Lowest ID to allocate.  */
	u32 max; /* Highest ID to allocate. */
	u32 next; /* Next ID to allocate. */
पूर्ण;

काष्ठा hns_roce_qp_table अणु
	काष्ठा hns_roce_hem_table	qp_table;
	काष्ठा hns_roce_hem_table	irrl_table;
	काष्ठा hns_roce_hem_table	trrl_table;
	काष्ठा hns_roce_hem_table	sccc_table;
	काष्ठा mutex			scc_mutex;
	काष्ठा hns_roce_bank bank[HNS_ROCE_QP_BANK_NUM];
	काष्ठा mutex bank_mutex;
पूर्ण;

काष्ठा hns_roce_cq_table अणु
	काष्ठा xarray			array;
	काष्ठा hns_roce_hem_table	table;
	काष्ठा hns_roce_bank bank[HNS_ROCE_CQ_BANK_NUM];
	काष्ठा mutex			bank_mutex;
पूर्ण;

काष्ठा hns_roce_srq_table अणु
	काष्ठा hns_roce_biपंचांगap		biपंचांगap;
	काष्ठा xarray			xa;
	काष्ठा hns_roce_hem_table	table;
पूर्ण;

काष्ठा hns_roce_raq_table अणु
	काष्ठा hns_roce_buf_list	*e_raq_buf;
पूर्ण;

काष्ठा hns_roce_av अणु
	u8 port;
	u8 gid_index;
	u8 stat_rate;
	u8 hop_limit;
	u32 flowlabel;
	u16 udp_sport;
	u8 sl;
	u8 tclass;
	u8 dgid[HNS_ROCE_GID_SIZE];
	u8 mac[ETH_ALEN];
	u16 vlan_id;
	u8 vlan_en;
पूर्ण;

काष्ठा hns_roce_ah अणु
	काष्ठा ib_ah		ibah;
	काष्ठा hns_roce_av	av;
पूर्ण;

काष्ठा hns_roce_cmd_context अणु
	काष्ठा completion	करोne;
	पूर्णांक			result;
	पूर्णांक			next;
	u64			out_param;
	u16			token;
	u16			busy;
पूर्ण;

काष्ठा hns_roce_cmdq अणु
	काष्ठा dma_pool		*pool;
	काष्ठा mutex		hcr_mutex;
	काष्ठा semaphore	poll_sem;
	/*
	 * Event mode: cmd रेजिस्टर mutex protection,
	 * ensure to not exceed max_cmds and user use limit region
	 */
	काष्ठा semaphore	event_sem;
	पूर्णांक			max_cmds;
	spinlock_t		context_lock;
	पूर्णांक			मुक्त_head;
	काष्ठा hns_roce_cmd_context *context;
	/*
	 * Process whether use event mode, init शेष non-zero
	 * After the event queue of cmd event पढ़ोy,
	 * can चयन पूर्णांकo event mode
	 * बंद device, चयन पूर्णांकo poll mode(non event mode)
	 */
	u8			use_events;
पूर्ण;

काष्ठा hns_roce_cmd_mailbox अणु
	व्योम		       *buf;
	dma_addr_t		dma;
पूर्ण;

काष्ठा hns_roce_dev;

काष्ठा hns_roce_rinl_sge अणु
	व्योम			*addr;
	u32			len;
पूर्ण;

काष्ठा hns_roce_rinl_wqe अणु
	काष्ठा hns_roce_rinl_sge *sg_list;
	u32			 sge_cnt;
पूर्ण;

काष्ठा hns_roce_rinl_buf अणु
	काष्ठा hns_roce_rinl_wqe *wqe_list;
	u32			 wqe_cnt;
पूर्ण;

क्रमागत अणु
	HNS_ROCE_FLUSH_FLAG = 0,
पूर्ण;

काष्ठा hns_roce_work अणु
	काष्ठा hns_roce_dev *hr_dev;
	काष्ठा work_काष्ठा work;
	पूर्णांक event_type;
	पूर्णांक sub_type;
	u32 queue_num;
पूर्ण;

क्रमागत अणु
	HNS_ROCE_QP_CAP_सूचीECT_WQE = BIT(5),
पूर्ण;

काष्ठा hns_roce_qp अणु
	काष्ठा ib_qp		ibqp;
	काष्ठा hns_roce_wq	rq;
	काष्ठा hns_roce_db	rdb;
	काष्ठा hns_roce_db	sdb;
	अचिन्हित दीर्घ		en_flags;
	u32			करोorbell_qpn;
	क्रमागत ib_sig_type	sq_संकेत_bits;
	काष्ठा hns_roce_wq	sq;

	काष्ठा hns_roce_mtr	mtr;

	u32			buff_size;
	काष्ठा mutex		mutex;
	u8			port;
	u8			phy_port;
	u8			sl;
	u8			resp_depth;
	u8			state;
	u32			access_flags;
	u32                     atomic_rd_en;
	u32			pkey_index;
	u32			qkey;
	व्योम			(*event)(काष्ठा hns_roce_qp *qp,
					 क्रमागत hns_roce_event event_type);
	अचिन्हित दीर्घ		qpn;

	u32			xrcdn;

	atomic_t		refcount;
	काष्ठा completion	मुक्त;

	काष्ठा hns_roce_sge	sge;
	u32			next_sge;
	क्रमागत ib_mtu		path_mtu;
	u32			max_अंतरभूत_data;

	/* 0: flush needed, 1: unneeded */
	अचिन्हित दीर्घ		flush_flag;
	काष्ठा hns_roce_work	flush_work;
	काष्ठा hns_roce_rinl_buf rq_inl_buf;
	काष्ठा list_head	node;		/* all qps are on a list */
	काष्ठा list_head	rq_node;	/* all recv qps are on a list */
	काष्ठा list_head	sq_node;	/* all send qps are on a list */
पूर्ण;

काष्ठा hns_roce_ib_iboe अणु
	spinlock_t		lock;
	काष्ठा net_device      *netdevs[HNS_ROCE_MAX_PORTS];
	काष्ठा notअगरier_block	nb;
	u8			phy_port[HNS_ROCE_MAX_PORTS];
पूर्ण;

क्रमागत अणु
	HNS_ROCE_EQ_STAT_INVALID  = 0,
	HNS_ROCE_EQ_STAT_VALID    = 2,
पूर्ण;

काष्ठा hns_roce_ceqe अणु
	__le32	comp;
	__le32	rsv[15];
पूर्ण;

काष्ठा hns_roce_aeqe अणु
	__le32 asyn;
	जोड़ अणु
		काष्ठा अणु
			__le32 num;
			u32 rsv0;
			u32 rsv1;
		पूर्ण queue_event;

		काष्ठा अणु
			__le64  out_param;
			__le16  token;
			u8	status;
			u8	rsv0;
		पूर्ण __packed cmd;
	 पूर्ण event;
	__le32 rsv[12];
पूर्ण;

काष्ठा hns_roce_eq अणु
	काष्ठा hns_roce_dev		*hr_dev;
	व्योम __iomem			*db_reg;

	पूर्णांक				type_flag; /* Aeq:1 ceq:0 */
	पूर्णांक				eqn;
	u32				entries;
	u32				log_entries;
	पूर्णांक				eqe_size;
	पूर्णांक				irq;
	पूर्णांक				log_page_size;
	u32				cons_index;
	काष्ठा hns_roce_buf_list	*buf_list;
	पूर्णांक				over_ignore;
	पूर्णांक				coalesce;
	पूर्णांक				arm_st;
	पूर्णांक				hop_num;
	काष्ठा hns_roce_mtr		mtr;
	u16				eq_max_cnt;
	u32				eq_period;
	पूर्णांक				shअगरt;
	पूर्णांक				event_type;
	पूर्णांक				sub_type;
पूर्ण;

काष्ठा hns_roce_eq_table अणु
	काष्ठा hns_roce_eq	*eq;
	व्योम __iomem		**eqc_base; /* only क्रम hw v1 */
पूर्ण;

क्रमागत cong_type अणु
	CONG_TYPE_DCQCN,
	CONG_TYPE_LDCP,
	CONG_TYPE_HC3,
	CONG_TYPE_DIP,
पूर्ण;

काष्ठा hns_roce_caps अणु
	u64		fw_ver;
	u8		num_ports;
	पूर्णांक		gid_table_len[HNS_ROCE_MAX_PORTS];
	पूर्णांक		pkey_table_len[HNS_ROCE_MAX_PORTS];
	पूर्णांक		local_ca_ack_delay;
	पूर्णांक		num_uars;
	u32		phy_num_uars;
	u32		max_sq_sg;
	u32		max_sq_अंतरभूत;
	u32		max_rq_sg;
	u32		max_extend_sg;
	u32		num_qps;
	u32		reserved_qps;
	पूर्णांक		num_qpc_समयr;
	पूर्णांक		num_cqc_समयr;
	पूर्णांक		num_srqs;
	u32		max_wqes;
	u32		max_srq_wrs;
	u32		max_srq_sges;
	u32		max_sq_desc_sz;
	u32		max_rq_desc_sz;
	u32		max_srq_desc_sz;
	पूर्णांक		max_qp_init_rdma;
	पूर्णांक		max_qp_dest_rdma;
	u32		num_cqs;
	u32		max_cqes;
	u32		min_cqes;
	u32		min_wqes;
	u32		reserved_cqs;
	पूर्णांक		reserved_srqs;
	पूर्णांक		num_aeq_vectors;
	पूर्णांक		num_comp_vectors;
	पूर्णांक		num_other_vectors;
	u32		num_mtpts;
	u32		num_mtt_segs;
	u32		num_srqwqe_segs;
	u32		num_idx_segs;
	पूर्णांक		reserved_mrws;
	पूर्णांक		reserved_uars;
	पूर्णांक		num_pds;
	पूर्णांक		reserved_pds;
	u32		num_xrcds;
	u32		reserved_xrcds;
	u32		mtt_entry_sz;
	u32		cqe_sz;
	u32		page_size_cap;
	u32		reserved_lkey;
	पूर्णांक		mtpt_entry_sz;
	पूर्णांक		qpc_sz;
	पूर्णांक		irrl_entry_sz;
	पूर्णांक		trrl_entry_sz;
	पूर्णांक		cqc_entry_sz;
	पूर्णांक		sccc_sz;
	पूर्णांक		qpc_समयr_entry_sz;
	पूर्णांक		cqc_समयr_entry_sz;
	पूर्णांक		srqc_entry_sz;
	पूर्णांक		idx_entry_sz;
	u32		pbl_ba_pg_sz;
	u32		pbl_buf_pg_sz;
	u32		pbl_hop_num;
	पूर्णांक		aeqe_depth;
	पूर्णांक		ceqe_depth;
	u32		aeqe_size;
	u32		ceqe_size;
	क्रमागत ib_mtu	max_mtu;
	u32		qpc_bt_num;
	u32		qpc_समयr_bt_num;
	u32		srqc_bt_num;
	u32		cqc_bt_num;
	u32		cqc_समयr_bt_num;
	u32		mpt_bt_num;
	u32		eqc_bt_num;
	u32		smac_bt_num;
	u32		sgid_bt_num;
	u32		sccc_bt_num;
	u32		gmv_bt_num;
	u32		qpc_ba_pg_sz;
	u32		qpc_buf_pg_sz;
	u32		qpc_hop_num;
	u32		srqc_ba_pg_sz;
	u32		srqc_buf_pg_sz;
	u32		srqc_hop_num;
	u32		cqc_ba_pg_sz;
	u32		cqc_buf_pg_sz;
	u32		cqc_hop_num;
	u32		mpt_ba_pg_sz;
	u32		mpt_buf_pg_sz;
	u32		mpt_hop_num;
	u32		mtt_ba_pg_sz;
	u32		mtt_buf_pg_sz;
	u32		mtt_hop_num;
	u32		wqe_sq_hop_num;
	u32		wqe_sge_hop_num;
	u32		wqe_rq_hop_num;
	u32		sccc_ba_pg_sz;
	u32		sccc_buf_pg_sz;
	u32		sccc_hop_num;
	u32		qpc_समयr_ba_pg_sz;
	u32		qpc_समयr_buf_pg_sz;
	u32		qpc_समयr_hop_num;
	u32		cqc_समयr_ba_pg_sz;
	u32		cqc_समयr_buf_pg_sz;
	u32		cqc_समयr_hop_num;
	u32             cqe_ba_pg_sz;	/* page_size = 4K*(2^cqe_ba_pg_sz) */
	u32		cqe_buf_pg_sz;
	u32		cqe_hop_num;
	u32		srqwqe_ba_pg_sz;
	u32		srqwqe_buf_pg_sz;
	u32		srqwqe_hop_num;
	u32		idx_ba_pg_sz;
	u32		idx_buf_pg_sz;
	u32		idx_hop_num;
	u32		eqe_ba_pg_sz;
	u32		eqe_buf_pg_sz;
	u32		eqe_hop_num;
	u32		gmv_entry_num;
	u32		gmv_entry_sz;
	u32		gmv_ba_pg_sz;
	u32		gmv_buf_pg_sz;
	u32		gmv_hop_num;
	u32		sl_num;
	u32		tsq_buf_pg_sz;
	u32		tpq_buf_pg_sz;
	u32		chunk_sz;	/* chunk size in non multihop mode */
	u64		flags;
	u16		शेष_ceq_max_cnt;
	u16		शेष_ceq_period;
	u16		शेष_aeq_max_cnt;
	u16		शेष_aeq_period;
	u16		शेष_aeq_arm_st;
	u16		शेष_ceq_arm_st;
	क्रमागत cong_type	cong_type;
पूर्ण;

काष्ठा hns_roce_dfx_hw अणु
	पूर्णांक (*query_cqc_info)(काष्ठा hns_roce_dev *hr_dev, u32 cqn,
			      पूर्णांक *buffer);
पूर्ण;

क्रमागत hns_roce_device_state अणु
	HNS_ROCE_DEVICE_STATE_INITED,
	HNS_ROCE_DEVICE_STATE_RST_DOWN,
	HNS_ROCE_DEVICE_STATE_UNINIT,
पूर्ण;

काष्ठा hns_roce_hw अणु
	पूर्णांक (*reset)(काष्ठा hns_roce_dev *hr_dev, bool enable);
	पूर्णांक (*cmq_init)(काष्ठा hns_roce_dev *hr_dev);
	व्योम (*cmq_निकास)(काष्ठा hns_roce_dev *hr_dev);
	पूर्णांक (*hw_profile)(काष्ठा hns_roce_dev *hr_dev);
	पूर्णांक (*hw_init)(काष्ठा hns_roce_dev *hr_dev);
	व्योम (*hw_निकास)(काष्ठा hns_roce_dev *hr_dev);
	पूर्णांक (*post_mbox)(काष्ठा hns_roce_dev *hr_dev, u64 in_param,
			 u64 out_param, u32 in_modअगरier, u8 op_modअगरier, u16 op,
			 u16 token, पूर्णांक event);
	पूर्णांक (*poll_mbox_करोne)(काष्ठा hns_roce_dev *hr_dev,
			      अचिन्हित पूर्णांक समयout);
	bool (*chk_mbox_avail)(काष्ठा hns_roce_dev *hr_dev, bool *is_busy);
	पूर्णांक (*set_gid)(काष्ठा hns_roce_dev *hr_dev, u32 port, पूर्णांक gid_index,
		       स्थिर जोड़ ib_gid *gid, स्थिर काष्ठा ib_gid_attr *attr);
	पूर्णांक (*set_mac)(काष्ठा hns_roce_dev *hr_dev, u8 phy_port, u8 *addr);
	व्योम (*set_mtu)(काष्ठा hns_roce_dev *hr_dev, u8 phy_port,
			क्रमागत ib_mtu mtu);
	पूर्णांक (*ग_लिखो_mtpt)(काष्ठा hns_roce_dev *hr_dev, व्योम *mb_buf,
			  काष्ठा hns_roce_mr *mr, अचिन्हित दीर्घ mtpt_idx);
	पूर्णांक (*rereg_ग_लिखो_mtpt)(काष्ठा hns_roce_dev *hr_dev,
				काष्ठा hns_roce_mr *mr, पूर्णांक flags,
				व्योम *mb_buf);
	पूर्णांक (*frmr_ग_लिखो_mtpt)(काष्ठा hns_roce_dev *hr_dev, व्योम *mb_buf,
			       काष्ठा hns_roce_mr *mr);
	पूर्णांक (*mw_ग_लिखो_mtpt)(व्योम *mb_buf, काष्ठा hns_roce_mw *mw);
	व्योम (*ग_लिखो_cqc)(काष्ठा hns_roce_dev *hr_dev,
			  काष्ठा hns_roce_cq *hr_cq, व्योम *mb_buf, u64 *mtts,
			  dma_addr_t dma_handle);
	पूर्णांक (*set_hem)(काष्ठा hns_roce_dev *hr_dev,
		       काष्ठा hns_roce_hem_table *table, पूर्णांक obj, पूर्णांक step_idx);
	पूर्णांक (*clear_hem)(काष्ठा hns_roce_dev *hr_dev,
			 काष्ठा hns_roce_hem_table *table, पूर्णांक obj,
			 पूर्णांक step_idx);
	पूर्णांक (*modअगरy_qp)(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_qp_attr *attr,
			 पूर्णांक attr_mask, क्रमागत ib_qp_state cur_state,
			 क्रमागत ib_qp_state new_state);
	पूर्णांक (*qp_flow_control_init)(काष्ठा hns_roce_dev *hr_dev,
			 काष्ठा hns_roce_qp *hr_qp);
	पूर्णांक (*dereg_mr)(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mr *mr,
			काष्ठा ib_udata *udata);
	पूर्णांक (*destroy_cq)(काष्ठा ib_cq *ibcq, काष्ठा ib_udata *udata);
	पूर्णांक (*init_eq)(काष्ठा hns_roce_dev *hr_dev);
	व्योम (*cleanup_eq)(काष्ठा hns_roce_dev *hr_dev);
	पूर्णांक (*ग_लिखो_srqc)(काष्ठा hns_roce_srq *srq, व्योम *mb_buf);
	स्थिर काष्ठा ib_device_ops *hns_roce_dev_ops;
	स्थिर काष्ठा ib_device_ops *hns_roce_dev_srq_ops;
पूर्ण;

काष्ठा hns_roce_dev अणु
	काष्ठा ib_device	ib_dev;
	काष्ठा platक्रमm_device  *pdev;
	काष्ठा pci_dev		*pci_dev;
	काष्ठा device		*dev;
	काष्ठा hns_roce_uar     priv_uar;
	स्थिर अक्षर		*irq_names[HNS_ROCE_MAX_IRQ_NUM];
	spinlock_t		sm_lock;
	spinlock_t		bt_cmd_lock;
	bool			active;
	bool			is_reset;
	bool			dis_db;
	अचिन्हित दीर्घ		reset_cnt;
	काष्ठा hns_roce_ib_iboe iboe;
	क्रमागत hns_roce_device_state state;
	काष्ठा list_head	qp_list; /* list of all qps on this dev */
	spinlock_t		qp_list_lock; /* protect qp_list */
	काष्ठा list_head	dip_list; /* list of all dest ips on this dev */
	spinlock_t		dip_list_lock; /* protect dip_list */

	काष्ठा list_head        pgdir_list;
	काष्ठा mutex            pgdir_mutex;
	पूर्णांक			irq[HNS_ROCE_MAX_IRQ_NUM];
	u8 __iomem		*reg_base;
	व्योम __iomem		*mem_base;
	काष्ठा hns_roce_caps	caps;
	काष्ठा xarray		qp_table_xa;

	अचिन्हित अक्षर	dev_addr[HNS_ROCE_MAX_PORTS][ETH_ALEN];
	u64			sys_image_guid;
	u32                     venकरोr_id;
	u32                     venकरोr_part_id;
	u32                     hw_rev;
	व्योम __iomem            *priv_addr;

	काष्ठा hns_roce_cmdq	cmd;
	काष्ठा hns_roce_biपंचांगap    pd_biपंचांगap;
	काष्ठा hns_roce_biपंचांगap xrcd_biपंचांगap;
	काष्ठा hns_roce_uar_table uar_table;
	काष्ठा hns_roce_mr_table  mr_table;
	काष्ठा hns_roce_cq_table  cq_table;
	काष्ठा hns_roce_srq_table srq_table;
	काष्ठा hns_roce_qp_table  qp_table;
	काष्ठा hns_roce_eq_table  eq_table;
	काष्ठा hns_roce_hem_table  qpc_समयr_table;
	काष्ठा hns_roce_hem_table  cqc_समयr_table;
	/* GMV is the memory area that the driver allocates क्रम the hardware
	 * to store SGID, SMAC and VLAN inक्रमmation.
	 */
	काष्ठा hns_roce_hem_table  gmv_table;

	पूर्णांक			cmd_mod;
	पूर्णांक			loop_idc;
	u32			sdb_offset;
	u32			odb_offset;
	dma_addr_t		tptr_dma_addr;	/* only क्रम hw v1 */
	u32			tptr_size;	/* only क्रम hw v1 */
	स्थिर काष्ठा hns_roce_hw *hw;
	व्योम			*priv;
	काष्ठा workqueue_काष्ठा *irq_workq;
	स्थिर काष्ठा hns_roce_dfx_hw *dfx;
	u32 func_num;
	u32 is_vf;
	u32 cong_algo_पंचांगpl_id;
पूर्ण;

अटल अंतरभूत काष्ठा hns_roce_dev *to_hr_dev(काष्ठा ib_device *ib_dev)
अणु
	वापस container_of(ib_dev, काष्ठा hns_roce_dev, ib_dev);
पूर्ण

अटल अंतरभूत काष्ठा hns_roce_ucontext
			*to_hr_ucontext(काष्ठा ib_ucontext *ibucontext)
अणु
	वापस container_of(ibucontext, काष्ठा hns_roce_ucontext, ibucontext);
पूर्ण

अटल अंतरभूत काष्ठा hns_roce_pd *to_hr_pd(काष्ठा ib_pd *ibpd)
अणु
	वापस container_of(ibpd, काष्ठा hns_roce_pd, ibpd);
पूर्ण

अटल अंतरभूत काष्ठा hns_roce_xrcd *to_hr_xrcd(काष्ठा ib_xrcd *ibxrcd)
अणु
	वापस container_of(ibxrcd, काष्ठा hns_roce_xrcd, ibxrcd);
पूर्ण

अटल अंतरभूत काष्ठा hns_roce_ah *to_hr_ah(काष्ठा ib_ah *ibah)
अणु
	वापस container_of(ibah, काष्ठा hns_roce_ah, ibah);
पूर्ण

अटल अंतरभूत काष्ठा hns_roce_mr *to_hr_mr(काष्ठा ib_mr *ibmr)
अणु
	वापस container_of(ibmr, काष्ठा hns_roce_mr, ibmr);
पूर्ण

अटल अंतरभूत काष्ठा hns_roce_mw *to_hr_mw(काष्ठा ib_mw *ibmw)
अणु
	वापस container_of(ibmw, काष्ठा hns_roce_mw, ibmw);
पूर्ण

अटल अंतरभूत काष्ठा hns_roce_qp *to_hr_qp(काष्ठा ib_qp *ibqp)
अणु
	वापस container_of(ibqp, काष्ठा hns_roce_qp, ibqp);
पूर्ण

अटल अंतरभूत काष्ठा hns_roce_cq *to_hr_cq(काष्ठा ib_cq *ib_cq)
अणु
	वापस container_of(ib_cq, काष्ठा hns_roce_cq, ib_cq);
पूर्ण

अटल अंतरभूत काष्ठा hns_roce_srq *to_hr_srq(काष्ठा ib_srq *ibsrq)
अणु
	वापस container_of(ibsrq, काष्ठा hns_roce_srq, ibsrq);
पूर्ण

अटल अंतरभूत व्योम hns_roce_ग_लिखो64_k(__le32 val[2], व्योम __iomem *dest)
अणु
	ग_लिखोq(*(u64 *)val, dest);
पूर्ण

अटल अंतरभूत काष्ठा hns_roce_qp
	*__hns_roce_qp_lookup(काष्ठा hns_roce_dev *hr_dev, u32 qpn)
अणु
	वापस xa_load(&hr_dev->qp_table_xa, qpn & (hr_dev->caps.num_qps - 1));
पूर्ण

अटल अंतरभूत व्योम *hns_roce_buf_offset(काष्ठा hns_roce_buf *buf,
					अचिन्हित पूर्णांक offset)
अणु
	वापस (अक्षर *)(buf->trunk_list[offset >> buf->trunk_shअगरt].buf) +
			(offset & ((1 << buf->trunk_shअगरt) - 1));
पूर्ण

अटल अंतरभूत dma_addr_t hns_roce_buf_page(काष्ठा hns_roce_buf *buf, u32 idx)
अणु
	अचिन्हित पूर्णांक offset = idx << buf->page_shअगरt;

	वापस buf->trunk_list[offset >> buf->trunk_shअगरt].map +
			(offset & ((1 << buf->trunk_shअगरt) - 1));
पूर्ण

#घोषणा hr_hw_page_align(x)		ALIGN(x, 1 << HNS_HW_PAGE_SHIFT)

अटल अंतरभूत u64 to_hr_hw_page_addr(u64 addr)
अणु
	वापस addr >> HNS_HW_PAGE_SHIFT;
पूर्ण

अटल अंतरभूत u32 to_hr_hw_page_shअगरt(u32 page_shअगरt)
अणु
	वापस page_shअगरt - HNS_HW_PAGE_SHIFT;
पूर्ण

अटल अंतरभूत u32 to_hr_hem_hopnum(u32 hopnum, u32 count)
अणु
	अगर (count > 0)
		वापस hopnum == HNS_ROCE_HOP_NUM_0 ? 0 : hopnum;

	वापस 0;
पूर्ण

अटल अंतरभूत u32 to_hr_hem_entries_size(u32 count, u32 buf_shअगरt)
अणु
	वापस hr_hw_page_align(count << buf_shअगरt);
पूर्ण

अटल अंतरभूत u32 to_hr_hem_entries_count(u32 count, u32 buf_shअगरt)
अणु
	वापस hr_hw_page_align(count << buf_shअगरt) >> buf_shअगरt;
पूर्ण

अटल अंतरभूत u32 to_hr_hem_entries_shअगरt(u32 count, u32 buf_shअगरt)
अणु
	अगर (!count)
		वापस 0;

	वापस ilog2(to_hr_hem_entries_count(count, buf_shअगरt));
पूर्ण

#घोषणा DSCP_SHIFT 2

अटल अंतरभूत u8 get_tclass(स्थिर काष्ठा ib_global_route *grh)
अणु
	वापस grh->sgid_attr->gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP ?
	       grh->traffic_class >> DSCP_SHIFT : grh->traffic_class;
पूर्ण

पूर्णांक hns_roce_init_uar_table(काष्ठा hns_roce_dev *dev);
पूर्णांक hns_roce_uar_alloc(काष्ठा hns_roce_dev *dev, काष्ठा hns_roce_uar *uar);
व्योम hns_roce_uar_मुक्त(काष्ठा hns_roce_dev *dev, काष्ठा hns_roce_uar *uar);
व्योम hns_roce_cleanup_uar_table(काष्ठा hns_roce_dev *dev);

पूर्णांक hns_roce_cmd_init(काष्ठा hns_roce_dev *hr_dev);
व्योम hns_roce_cmd_cleanup(काष्ठा hns_roce_dev *hr_dev);
व्योम hns_roce_cmd_event(काष्ठा hns_roce_dev *hr_dev, u16 token, u8 status,
			u64 out_param);
पूर्णांक hns_roce_cmd_use_events(काष्ठा hns_roce_dev *hr_dev);
व्योम hns_roce_cmd_use_polling(काष्ठा hns_roce_dev *hr_dev);

/* hns roce hw need current block and next block addr from mtt */
#घोषणा MTT_MIN_COUNT	 2
पूर्णांक hns_roce_mtr_find(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mtr *mtr,
		      पूर्णांक offset, u64 *mtt_buf, पूर्णांक mtt_max, u64 *base_addr);
पूर्णांक hns_roce_mtr_create(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mtr *mtr,
			काष्ठा hns_roce_buf_attr *buf_attr,
			अचिन्हित पूर्णांक page_shअगरt, काष्ठा ib_udata *udata,
			अचिन्हित दीर्घ user_addr);
व्योम hns_roce_mtr_destroy(काष्ठा hns_roce_dev *hr_dev,
			  काष्ठा hns_roce_mtr *mtr);
पूर्णांक hns_roce_mtr_map(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mtr *mtr,
		     dma_addr_t *pages, अचिन्हित पूर्णांक page_cnt);

पूर्णांक hns_roce_init_pd_table(काष्ठा hns_roce_dev *hr_dev);
पूर्णांक hns_roce_init_mr_table(काष्ठा hns_roce_dev *hr_dev);
व्योम hns_roce_init_cq_table(काष्ठा hns_roce_dev *hr_dev);
पूर्णांक hns_roce_init_qp_table(काष्ठा hns_roce_dev *hr_dev);
पूर्णांक hns_roce_init_srq_table(काष्ठा hns_roce_dev *hr_dev);
पूर्णांक hns_roce_init_xrcd_table(काष्ठा hns_roce_dev *hr_dev);

व्योम hns_roce_cleanup_pd_table(काष्ठा hns_roce_dev *hr_dev);
व्योम hns_roce_cleanup_mr_table(काष्ठा hns_roce_dev *hr_dev);
व्योम hns_roce_cleanup_eq_table(काष्ठा hns_roce_dev *hr_dev);
व्योम hns_roce_cleanup_cq_table(काष्ठा hns_roce_dev *hr_dev);
व्योम hns_roce_cleanup_qp_table(काष्ठा hns_roce_dev *hr_dev);
व्योम hns_roce_cleanup_srq_table(काष्ठा hns_roce_dev *hr_dev);
व्योम hns_roce_cleanup_xrcd_table(काष्ठा hns_roce_dev *hr_dev);

पूर्णांक hns_roce_biपंचांगap_alloc(काष्ठा hns_roce_biपंचांगap *biपंचांगap, अचिन्हित दीर्घ *obj);
व्योम hns_roce_biपंचांगap_मुक्त(काष्ठा hns_roce_biपंचांगap *biपंचांगap, अचिन्हित दीर्घ obj,
			 पूर्णांक rr);
पूर्णांक hns_roce_biपंचांगap_init(काष्ठा hns_roce_biपंचांगap *biपंचांगap, u32 num, u32 mask,
			 u32 reserved_bot, u32 resetrved_top);
व्योम hns_roce_biपंचांगap_cleanup(काष्ठा hns_roce_biपंचांगap *biपंचांगap);
व्योम hns_roce_cleanup_biपंचांगap(काष्ठा hns_roce_dev *hr_dev);
पूर्णांक hns_roce_biपंचांगap_alloc_range(काष्ठा hns_roce_biपंचांगap *biपंचांगap, पूर्णांक cnt,
				पूर्णांक align, अचिन्हित दीर्घ *obj);
व्योम hns_roce_biपंचांगap_मुक्त_range(काष्ठा hns_roce_biपंचांगap *biपंचांगap,
				अचिन्हित दीर्घ obj, पूर्णांक cnt,
				पूर्णांक rr);

पूर्णांक hns_roce_create_ah(काष्ठा ib_ah *ah, काष्ठा rdma_ah_init_attr *init_attr,
		       काष्ठा ib_udata *udata);
पूर्णांक hns_roce_query_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_attr *ah_attr);
अटल अंतरभूत पूर्णांक hns_roce_destroy_ah(काष्ठा ib_ah *ah, u32 flags)
अणु
	वापस 0;
पूर्ण

पूर्णांक hns_roce_alloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata);
पूर्णांक hns_roce_dealloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata);

काष्ठा ib_mr *hns_roce_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक acc);
काष्ठा ib_mr *hns_roce_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
				   u64 virt_addr, पूर्णांक access_flags,
				   काष्ठा ib_udata *udata);
काष्ठा ib_mr *hns_roce_rereg_user_mr(काष्ठा ib_mr *mr, पूर्णांक flags, u64 start,
				     u64 length, u64 virt_addr,
				     पूर्णांक mr_access_flags, काष्ठा ib_pd *pd,
				     काष्ठा ib_udata *udata);
काष्ठा ib_mr *hns_roce_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
				u32 max_num_sg);
पूर्णांक hns_roce_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		       अचिन्हित पूर्णांक *sg_offset);
पूर्णांक hns_roce_dereg_mr(काष्ठा ib_mr *ibmr, काष्ठा ib_udata *udata);
पूर्णांक hns_roce_hw_destroy_mpt(काष्ठा hns_roce_dev *hr_dev,
			    काष्ठा hns_roce_cmd_mailbox *mailbox,
			    अचिन्हित दीर्घ mpt_index);
अचिन्हित दीर्घ key_to_hw_index(u32 key);

पूर्णांक hns_roce_alloc_mw(काष्ठा ib_mw *mw, काष्ठा ib_udata *udata);
पूर्णांक hns_roce_dealloc_mw(काष्ठा ib_mw *ibmw);

व्योम hns_roce_buf_मुक्त(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_buf *buf);
काष्ठा hns_roce_buf *hns_roce_buf_alloc(काष्ठा hns_roce_dev *hr_dev, u32 size,
					u32 page_shअगरt, u32 flags);

पूर्णांक hns_roce_get_kmem_bufs(काष्ठा hns_roce_dev *hr_dev, dma_addr_t *bufs,
			   पूर्णांक buf_cnt, पूर्णांक start, काष्ठा hns_roce_buf *buf);
पूर्णांक hns_roce_get_umem_bufs(काष्ठा hns_roce_dev *hr_dev, dma_addr_t *bufs,
			   पूर्णांक buf_cnt, पूर्णांक start, काष्ठा ib_umem *umem,
			   अचिन्हित पूर्णांक page_shअगरt);

पूर्णांक hns_roce_create_srq(काष्ठा ib_srq *srq,
			काष्ठा ib_srq_init_attr *srq_init_attr,
			काष्ठा ib_udata *udata);
पूर्णांक hns_roce_modअगरy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *srq_attr,
			क्रमागत ib_srq_attr_mask srq_attr_mask,
			काष्ठा ib_udata *udata);
पूर्णांक hns_roce_destroy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_udata *udata);

पूर्णांक hns_roce_alloc_xrcd(काष्ठा ib_xrcd *ib_xrcd, काष्ठा ib_udata *udata);
पूर्णांक hns_roce_dealloc_xrcd(काष्ठा ib_xrcd *ib_xrcd, काष्ठा ib_udata *udata);

काष्ठा ib_qp *hns_roce_create_qp(काष्ठा ib_pd *ib_pd,
				 काष्ठा ib_qp_init_attr *init_attr,
				 काष्ठा ib_udata *udata);
पूर्णांक hns_roce_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		       पूर्णांक attr_mask, काष्ठा ib_udata *udata);
व्योम init_flush_work(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp);
व्योम *hns_roce_get_recv_wqe(काष्ठा hns_roce_qp *hr_qp, अचिन्हित पूर्णांक n);
व्योम *hns_roce_get_send_wqe(काष्ठा hns_roce_qp *hr_qp, अचिन्हित पूर्णांक n);
व्योम *hns_roce_get_extend_sge(काष्ठा hns_roce_qp *hr_qp, अचिन्हित पूर्णांक n);
bool hns_roce_wq_overflow(काष्ठा hns_roce_wq *hr_wq, u32 nreq,
			  काष्ठा ib_cq *ib_cq);
क्रमागत hns_roce_qp_state to_hns_roce_state(क्रमागत ib_qp_state state);
व्योम hns_roce_lock_cqs(काष्ठा hns_roce_cq *send_cq,
		       काष्ठा hns_roce_cq *recv_cq);
व्योम hns_roce_unlock_cqs(काष्ठा hns_roce_cq *send_cq,
			 काष्ठा hns_roce_cq *recv_cq);
व्योम hns_roce_qp_हटाओ(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp);
व्योम hns_roce_qp_destroy(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp,
			 काष्ठा ib_udata *udata);
__be32 send_ieth(स्थिर काष्ठा ib_send_wr *wr);
पूर्णांक to_hr_qp_type(पूर्णांक qp_type);

पूर्णांक hns_roce_create_cq(काष्ठा ib_cq *ib_cq, स्थिर काष्ठा ib_cq_init_attr *attr,
		       काष्ठा ib_udata *udata);

पूर्णांक hns_roce_destroy_cq(काष्ठा ib_cq *ib_cq, काष्ठा ib_udata *udata);
पूर्णांक hns_roce_db_map_user(काष्ठा hns_roce_ucontext *context,
			 काष्ठा ib_udata *udata, अचिन्हित दीर्घ virt,
			 काष्ठा hns_roce_db *db);
व्योम hns_roce_db_unmap_user(काष्ठा hns_roce_ucontext *context,
			    काष्ठा hns_roce_db *db);
पूर्णांक hns_roce_alloc_db(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_db *db,
		      पूर्णांक order);
व्योम hns_roce_मुक्त_db(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_db *db);

व्योम hns_roce_cq_completion(काष्ठा hns_roce_dev *hr_dev, u32 cqn);
व्योम hns_roce_cq_event(काष्ठा hns_roce_dev *hr_dev, u32 cqn, पूर्णांक event_type);
व्योम hns_roce_qp_event(काष्ठा hns_roce_dev *hr_dev, u32 qpn, पूर्णांक event_type);
व्योम hns_roce_srq_event(काष्ठा hns_roce_dev *hr_dev, u32 srqn, पूर्णांक event_type);
u8 hns_get_gid_index(काष्ठा hns_roce_dev *hr_dev, u32 port, पूर्णांक gid_index);
व्योम hns_roce_handle_device_err(काष्ठा hns_roce_dev *hr_dev);
पूर्णांक hns_roce_init(काष्ठा hns_roce_dev *hr_dev);
व्योम hns_roce_निकास(काष्ठा hns_roce_dev *hr_dev);
पूर्णांक hns_roce_fill_res_cq_entry(काष्ठा sk_buff *msg,
			       काष्ठा ib_cq *ib_cq);
#पूर्ण_अगर /* _HNS_ROCE_DEVICE_H */
