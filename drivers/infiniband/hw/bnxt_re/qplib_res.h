<शैली गुरु>
/*
 * Broadcom NetXtreme-E RoCE driver.
 *
 * Copyright (c) 2016 - 2017, Broadcom. All rights reserved.  The term
 * Broadcom refers to Broadcom Limited and/or its subsidiaries.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
 * BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: QPLib resource manager (header)
 */

#अगर_अघोषित __BNXT_QPLIB_RES_H__
#घोषणा __BNXT_QPLIB_RES_H__

बाह्य स्थिर काष्ठा bnxt_qplib_gid bnxt_qplib_gid_zero;

#घोषणा CHIP_NUM_57508		0x1750
#घोषणा CHIP_NUM_57504		0x1751
#घोषणा CHIP_NUM_57502		0x1752

क्रमागत bnxt_qplib_wqe_mode अणु
	BNXT_QPLIB_WQE_MODE_STATIC	= 0x00,
	BNXT_QPLIB_WQE_MODE_VARIABLE	= 0x01,
	BNXT_QPLIB_WQE_MODE_INVALID	= 0x02
पूर्ण;

काष्ठा bnxt_qplib_drv_modes अणु
	u8	wqe_mode;
	/* Other modes to follow here */
पूर्ण;

काष्ठा bnxt_qplib_chip_ctx अणु
	u16	chip_num;
	u8	chip_rev;
	u8	chip_metal;
	काष्ठा bnxt_qplib_drv_modes modes;
पूर्ण;

#घोषणा PTR_CNT_PER_PG		(PAGE_SIZE / माप(व्योम *))
#घोषणा PTR_MAX_IDX_PER_PG	(PTR_CNT_PER_PG - 1)
#घोषणा PTR_PG(x)		(((x) & ~PTR_MAX_IDX_PER_PG) / PTR_CNT_PER_PG)
#घोषणा PTR_IDX(x)		((x) & PTR_MAX_IDX_PER_PG)

#घोषणा HWQ_CMP(idx, hwq)	((idx) & ((hwq)->max_elements - 1))

#घोषणा HWQ_FREE_SLOTS(hwq)	(hwq->max_elements - \
				((HWQ_CMP(hwq->prod, hwq)\
				- HWQ_CMP(hwq->cons, hwq))\
				& (hwq->max_elements - 1)))
क्रमागत bnxt_qplib_hwq_type अणु
	HWQ_TYPE_CTX,
	HWQ_TYPE_QUEUE,
	HWQ_TYPE_L2_CMPL,
	HWQ_TYPE_MR
पूर्ण;

#घोषणा MAX_PBL_LVL_0_PGS		1
#घोषणा MAX_PBL_LVL_1_PGS		512
#घोषणा MAX_PBL_LVL_1_PGS_SHIFT		9
#घोषणा MAX_PBL_LVL_1_PGS_FOR_LVL_2	256
#घोषणा MAX_PBL_LVL_2_PGS		(256 * 512)
#घोषणा MAX_PDL_LVL_SHIFT               9

क्रमागत bnxt_qplib_pbl_lvl अणु
	PBL_LVL_0,
	PBL_LVL_1,
	PBL_LVL_2,
	PBL_LVL_MAX
पूर्ण;

#घोषणा ROCE_PG_SIZE_4K		(4 * 1024)
#घोषणा ROCE_PG_SIZE_8K		(8 * 1024)
#घोषणा ROCE_PG_SIZE_64K	(64 * 1024)
#घोषणा ROCE_PG_SIZE_2M		(2 * 1024 * 1024)
#घोषणा ROCE_PG_SIZE_8M		(8 * 1024 * 1024)
#घोषणा ROCE_PG_SIZE_1G		(1024 * 1024 * 1024)

क्रमागत bnxt_qplib_hwrm_pg_size अणु
	BNXT_QPLIB_HWRM_PG_SIZE_4K	= 0,
	BNXT_QPLIB_HWRM_PG_SIZE_8K	= 1,
	BNXT_QPLIB_HWRM_PG_SIZE_64K	= 2,
	BNXT_QPLIB_HWRM_PG_SIZE_2M	= 3,
	BNXT_QPLIB_HWRM_PG_SIZE_8M	= 4,
	BNXT_QPLIB_HWRM_PG_SIZE_1G	= 5,
पूर्ण;

काष्ठा bnxt_qplib_reg_desc अणु
	u8		bar_id;
	resource_माप_प्रकार	bar_base;
	व्योम __iomem	*bar_reg;
	माप_प्रकार		len;
पूर्ण;

काष्ठा bnxt_qplib_pbl अणु
	u32				pg_count;
	u32				pg_size;
	व्योम				**pg_arr;
	dma_addr_t			*pg_map_arr;
पूर्ण;

काष्ठा bnxt_qplib_sg_info अणु
	काष्ठा ib_umem			*umem;
	u32				npages;
	u32				pgshft;
	u32				pgsize;
	bool				nopte;
पूर्ण;

काष्ठा bnxt_qplib_hwq_attr अणु
	काष्ठा bnxt_qplib_res		*res;
	काष्ठा bnxt_qplib_sg_info	*sginfo;
	क्रमागत bnxt_qplib_hwq_type	type;
	u32				depth;
	u32				stride;
	u32				aux_stride;
	u32				aux_depth;
पूर्ण;

काष्ठा bnxt_qplib_hwq अणु
	काष्ठा pci_dev			*pdev;
	/* lock to protect qplib_hwq */
	spinlock_t			lock;
	काष्ठा bnxt_qplib_pbl		pbl[PBL_LVL_MAX + 1];
	क्रमागत bnxt_qplib_pbl_lvl		level;		/* 0, 1, or 2 */
	/* ptr क्रम easy access to the PBL entries */
	व्योम				**pbl_ptr;
	/* ptr क्रम easy access to the dma_addr */
	dma_addr_t			*pbl_dma_ptr;
	u32				max_elements;
	u32				depth;
	u16				element_size;	/* Size of each entry */
	u16				qe_ppg;	/* queue entry per page */

	u32				prod;		/* raw */
	u32				cons;		/* raw */
	u8				cp_bit;
	u8				is_user;
	u64				*pad_pg;
	u32				pad_stride;
	u32				pad_pgofft;
पूर्ण;

काष्ठा bnxt_qplib_db_info अणु
	व्योम __iomem		*db;
	व्योम __iomem		*priv_db;
	काष्ठा bnxt_qplib_hwq	*hwq;
	u32			xid;
	u32			max_slot;
पूर्ण;

/* Tables */
काष्ठा bnxt_qplib_pd_tbl अणु
	अचिन्हित दीर्घ			*tbl;
	u32				max;
पूर्ण;

काष्ठा bnxt_qplib_sgid_tbl अणु
	काष्ठा bnxt_qplib_gid_info	*tbl;
	u16				*hw_id;
	u16				max;
	u16				active;
	व्योम				*ctx;
	u8				*vlan;
पूर्ण;

काष्ठा bnxt_qplib_pkey_tbl अणु
	u16				*tbl;
	u16				max;
	u16				active;
पूर्ण;

काष्ठा bnxt_qplib_dpi अणु
	u32				dpi;
	व्योम __iomem			*dbr;
	u64				umdbr;
पूर्ण;

काष्ठा bnxt_qplib_dpi_tbl अणु
	व्योम				**app_tbl;
	अचिन्हित दीर्घ			*tbl;
	u16				max;
	व्योम __iomem			*dbr_bar_reg_iomem;
	u64				unmapped_dbr;
पूर्ण;

काष्ठा bnxt_qplib_stats अणु
	dma_addr_t			dma_map;
	व्योम				*dma;
	u32				size;
	u32				fw_id;
पूर्ण;

काष्ठा bnxt_qplib_vf_res अणु
	u32 max_qp_per_vf;
	u32 max_mrw_per_vf;
	u32 max_srq_per_vf;
	u32 max_cq_per_vf;
	u32 max_gid_per_vf;
पूर्ण;

#घोषणा BNXT_QPLIB_MAX_QP_CTX_ENTRY_SIZE	448
#घोषणा BNXT_QPLIB_MAX_SRQ_CTX_ENTRY_SIZE	64
#घोषणा BNXT_QPLIB_MAX_CQ_CTX_ENTRY_SIZE	64
#घोषणा BNXT_QPLIB_MAX_MRW_CTX_ENTRY_SIZE	128

#घोषणा MAX_TQM_ALLOC_REQ               48
#घोषणा MAX_TQM_ALLOC_BLK_SIZE          8
काष्ठा bnxt_qplib_tqm_ctx अणु
	काष्ठा bnxt_qplib_hwq           pde;
	u8                              pde_level; /* Original level */
	काष्ठा bnxt_qplib_hwq           qtbl[MAX_TQM_ALLOC_REQ];
	u8                              qcount[MAX_TQM_ALLOC_REQ];
पूर्ण;

काष्ठा bnxt_qplib_ctx अणु
	u32				qpc_count;
	काष्ठा bnxt_qplib_hwq		qpc_tbl;
	u32				mrw_count;
	काष्ठा bnxt_qplib_hwq		mrw_tbl;
	u32				srqc_count;
	काष्ठा bnxt_qplib_hwq		srqc_tbl;
	u32				cq_count;
	काष्ठा bnxt_qplib_hwq		cq_tbl;
	काष्ठा bnxt_qplib_hwq		tim_tbl;
	काष्ठा bnxt_qplib_tqm_ctx	tqm_ctx;
	काष्ठा bnxt_qplib_stats		stats;
	काष्ठा bnxt_qplib_vf_res	vf_res;
	u64				hwrm_पूर्णांकf_ver;
पूर्ण;

काष्ठा bnxt_qplib_res अणु
	काष्ठा pci_dev			*pdev;
	काष्ठा bnxt_qplib_chip_ctx	*cctx;
	काष्ठा net_device		*netdev;

	काष्ठा bnxt_qplib_rcfw		*rcfw;
	काष्ठा bnxt_qplib_pd_tbl	pd_tbl;
	काष्ठा bnxt_qplib_sgid_tbl	sgid_tbl;
	काष्ठा bnxt_qplib_pkey_tbl	pkey_tbl;
	काष्ठा bnxt_qplib_dpi_tbl	dpi_tbl;
	bool				prio;
पूर्ण;

अटल अंतरभूत bool bnxt_qplib_is_chip_gen_p5(काष्ठा bnxt_qplib_chip_ctx *cctx)
अणु
	वापस (cctx->chip_num == CHIP_NUM_57508 ||
		cctx->chip_num == CHIP_NUM_57504 ||
		cctx->chip_num == CHIP_NUM_57502);
पूर्ण

अटल अंतरभूत u8 bnxt_qplib_get_hwq_type(काष्ठा bnxt_qplib_res *res)
अणु
	वापस bnxt_qplib_is_chip_gen_p5(res->cctx) ?
					HWQ_TYPE_QUEUE : HWQ_TYPE_L2_CMPL;
पूर्ण

अटल अंतरभूत u8 bnxt_qplib_get_ring_type(काष्ठा bnxt_qplib_chip_ctx *cctx)
अणु
	वापस bnxt_qplib_is_chip_gen_p5(cctx) ?
	       RING_ALLOC_REQ_RING_TYPE_NQ :
	       RING_ALLOC_REQ_RING_TYPE_ROCE_CMPL;
पूर्ण

अटल अंतरभूत u8 bnxt_qplib_base_pg_size(काष्ठा bnxt_qplib_hwq *hwq)
अणु
	u8 pg_size = BNXT_QPLIB_HWRM_PG_SIZE_4K;
	काष्ठा bnxt_qplib_pbl *pbl;

	pbl = &hwq->pbl[PBL_LVL_0];
	चयन (pbl->pg_size) अणु
	हाल ROCE_PG_SIZE_4K:
		pg_size = BNXT_QPLIB_HWRM_PG_SIZE_4K;
		अवरोध;
	हाल ROCE_PG_SIZE_8K:
		pg_size = BNXT_QPLIB_HWRM_PG_SIZE_8K;
		अवरोध;
	हाल ROCE_PG_SIZE_64K:
		pg_size = BNXT_QPLIB_HWRM_PG_SIZE_64K;
		अवरोध;
	हाल ROCE_PG_SIZE_2M:
		pg_size = BNXT_QPLIB_HWRM_PG_SIZE_2M;
		अवरोध;
	हाल ROCE_PG_SIZE_8M:
		pg_size = BNXT_QPLIB_HWRM_PG_SIZE_8M;
		अवरोध;
	हाल ROCE_PG_SIZE_1G:
		pg_size = BNXT_QPLIB_HWRM_PG_SIZE_1G;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस pg_size;
पूर्ण

अटल अंतरभूत व्योम *bnxt_qplib_get_qe(काष्ठा bnxt_qplib_hwq *hwq,
				      u32 indx, u64 *pg)
अणु
	u32 pg_num, pg_idx;

	pg_num = (indx / hwq->qe_ppg);
	pg_idx = (indx % hwq->qe_ppg);
	अगर (pg)
		*pg = (u64)&hwq->pbl_ptr[pg_num];
	वापस (व्योम *)(hwq->pbl_ptr[pg_num] + hwq->element_size * pg_idx);
पूर्ण

अटल अंतरभूत व्योम *bnxt_qplib_get_prod_qe(काष्ठा bnxt_qplib_hwq *hwq, u32 idx)
अणु
	idx += hwq->prod;
	अगर (idx >= hwq->depth)
		idx -= hwq->depth;
	वापस bnxt_qplib_get_qe(hwq, idx, शून्य);
पूर्ण

#घोषणा to_bnxt_qplib(ptr, type, member)	\
	container_of(ptr, type, member)

काष्ठा bnxt_qplib_pd;
काष्ठा bnxt_qplib_dev_attr;

व्योम bnxt_qplib_मुक्त_hwq(काष्ठा bnxt_qplib_res *res,
			 काष्ठा bnxt_qplib_hwq *hwq);
पूर्णांक bnxt_qplib_alloc_init_hwq(काष्ठा bnxt_qplib_hwq *hwq,
			      काष्ठा bnxt_qplib_hwq_attr *hwq_attr);
व्योम bnxt_qplib_get_guid(u8 *dev_addr, u8 *guid);
पूर्णांक bnxt_qplib_alloc_pd(काष्ठा bnxt_qplib_pd_tbl *pd_tbl,
			काष्ठा bnxt_qplib_pd *pd);
पूर्णांक bnxt_qplib_dealloc_pd(काष्ठा bnxt_qplib_res *res,
			  काष्ठा bnxt_qplib_pd_tbl *pd_tbl,
			  काष्ठा bnxt_qplib_pd *pd);
पूर्णांक bnxt_qplib_alloc_dpi(काष्ठा bnxt_qplib_dpi_tbl *dpit,
			 काष्ठा bnxt_qplib_dpi     *dpi,
			 व्योम                      *app);
पूर्णांक bnxt_qplib_dealloc_dpi(काष्ठा bnxt_qplib_res *res,
			   काष्ठा bnxt_qplib_dpi_tbl *dpi_tbl,
			   काष्ठा bnxt_qplib_dpi *dpi);
व्योम bnxt_qplib_cleanup_res(काष्ठा bnxt_qplib_res *res);
पूर्णांक bnxt_qplib_init_res(काष्ठा bnxt_qplib_res *res);
व्योम bnxt_qplib_मुक्त_res(काष्ठा bnxt_qplib_res *res);
पूर्णांक bnxt_qplib_alloc_res(काष्ठा bnxt_qplib_res *res, काष्ठा pci_dev *pdev,
			 काष्ठा net_device *netdev,
			 काष्ठा bnxt_qplib_dev_attr *dev_attr);
व्योम bnxt_qplib_मुक्त_ctx(काष्ठा bnxt_qplib_res *res,
			 काष्ठा bnxt_qplib_ctx *ctx);
पूर्णांक bnxt_qplib_alloc_ctx(काष्ठा bnxt_qplib_res *res,
			 काष्ठा bnxt_qplib_ctx *ctx,
			 bool virt_fn, bool is_p5);

अटल अंतरभूत व्योम bnxt_qplib_hwq_incr_prod(काष्ठा bnxt_qplib_hwq *hwq, u32 cnt)
अणु
	hwq->prod = (hwq->prod + cnt) % hwq->depth;
पूर्ण

अटल अंतरभूत व्योम bnxt_qplib_hwq_incr_cons(काष्ठा bnxt_qplib_hwq *hwq,
					    u32 cnt)
अणु
	hwq->cons = (hwq->cons + cnt) % hwq->depth;
पूर्ण

अटल अंतरभूत व्योम bnxt_qplib_ring_db32(काष्ठा bnxt_qplib_db_info *info,
					bool arm)
अणु
	u32 key;

	key = info->hwq->cons & (info->hwq->max_elements - 1);
	key |= (CMPL_DOORBELL_IDX_VALID |
		(CMPL_DOORBELL_KEY_CMPL & CMPL_DOORBELL_KEY_MASK));
	अगर (!arm)
		key |= CMPL_DOORBELL_MASK;
	ग_लिखोl(key, info->db);
पूर्ण

अटल अंतरभूत व्योम bnxt_qplib_ring_db(काष्ठा bnxt_qplib_db_info *info,
				      u32 type)
अणु
	u64 key = 0;

	key = (info->xid & DBC_DBC_XID_MASK) | DBC_DBC_PATH_ROCE | type;
	key <<= 32;
	key |= (info->hwq->cons & (info->hwq->max_elements - 1)) &
		DBC_DBC_INDEX_MASK;
	ग_लिखोq(key, info->db);
पूर्ण

अटल अंतरभूत व्योम bnxt_qplib_ring_prod_db(काष्ठा bnxt_qplib_db_info *info,
					   u32 type)
अणु
	u64 key = 0;

	key = (info->xid & DBC_DBC_XID_MASK) | DBC_DBC_PATH_ROCE | type;
	key <<= 32;
	key |= ((info->hwq->prod / info->max_slot)) & DBC_DBC_INDEX_MASK;
	ग_लिखोq(key, info->db);
पूर्ण

अटल अंतरभूत व्योम bnxt_qplib_armen_db(काष्ठा bnxt_qplib_db_info *info,
				       u32 type)
अणु
	u64 key = 0;

	key = (info->xid & DBC_DBC_XID_MASK) | DBC_DBC_PATH_ROCE | type;
	key <<= 32;
	ग_लिखोq(key, info->priv_db);
पूर्ण

अटल अंतरभूत व्योम bnxt_qplib_srq_arm_db(काष्ठा bnxt_qplib_db_info *info,
					 u32 th)
अणु
	u64 key = 0;

	key = (info->xid & DBC_DBC_XID_MASK) | DBC_DBC_PATH_ROCE | th;
	key <<= 32;
	key |=  th & DBC_DBC_INDEX_MASK;
	ग_लिखोq(key, info->priv_db);
पूर्ण

अटल अंतरभूत व्योम bnxt_qplib_ring_nq_db(काष्ठा bnxt_qplib_db_info *info,
					 काष्ठा bnxt_qplib_chip_ctx *cctx,
					 bool arm)
अणु
	u32 type;

	type = arm ? DBC_DBC_TYPE_NQ_ARM : DBC_DBC_TYPE_NQ;
	अगर (bnxt_qplib_is_chip_gen_p5(cctx))
		bnxt_qplib_ring_db(info, type);
	अन्यथा
		bnxt_qplib_ring_db32(info, arm);
पूर्ण
#पूर्ण_अगर /* __BNXT_QPLIB_RES_H__ */
