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
 * Description: QPLib resource manager
 */

#घोषणा dev_fmt(fmt) "QPLIB: " fmt

#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_uस्मृति.स>

#समावेश "roce_hsi.h"
#समावेश "qplib_res.h"
#समावेश "qplib_sp.h"
#समावेश "qplib_rcfw.h"

अटल व्योम bnxt_qplib_मुक्त_stats_ctx(काष्ठा pci_dev *pdev,
				      काष्ठा bnxt_qplib_stats *stats);
अटल पूर्णांक bnxt_qplib_alloc_stats_ctx(काष्ठा pci_dev *pdev,
				      काष्ठा bnxt_qplib_stats *stats);

/* PBL */
अटल व्योम __मुक्त_pbl(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_pbl *pbl,
		       bool is_umem)
अणु
	काष्ठा pci_dev *pdev = res->pdev;
	पूर्णांक i;

	अगर (!is_umem) अणु
		क्रम (i = 0; i < pbl->pg_count; i++) अणु
			अगर (pbl->pg_arr[i])
				dma_मुक्त_coherent(&pdev->dev, pbl->pg_size,
						  (व्योम *)((अचिन्हित दीर्घ)
						   pbl->pg_arr[i] &
						  PAGE_MASK),
						  pbl->pg_map_arr[i]);
			अन्यथा
				dev_warn(&pdev->dev,
					 "PBL free pg_arr[%d] empty?!\n", i);
			pbl->pg_arr[i] = शून्य;
		पूर्ण
	पूर्ण
	vमुक्त(pbl->pg_arr);
	pbl->pg_arr = शून्य;
	vमुक्त(pbl->pg_map_arr);
	pbl->pg_map_arr = शून्य;
	pbl->pg_count = 0;
	pbl->pg_size = 0;
पूर्ण

अटल व्योम bnxt_qplib_fill_user_dma_pages(काष्ठा bnxt_qplib_pbl *pbl,
					   काष्ठा bnxt_qplib_sg_info *sginfo)
अणु
	काष्ठा ib_block_iter biter;
	पूर्णांक i = 0;

	rdma_umem_क्रम_each_dma_block(sginfo->umem, &biter, sginfo->pgsize) अणु
		pbl->pg_map_arr[i] = rdma_block_iter_dma_address(&biter);
		pbl->pg_arr[i] = शून्य;
		pbl->pg_count++;
		i++;
	पूर्ण
पूर्ण

अटल पूर्णांक __alloc_pbl(काष्ठा bnxt_qplib_res *res,
		       काष्ठा bnxt_qplib_pbl *pbl,
		       काष्ठा bnxt_qplib_sg_info *sginfo)
अणु
	काष्ठा pci_dev *pdev = res->pdev;
	bool is_umem = false;
	u32 pages;
	पूर्णांक i;

	अगर (sginfo->nopte)
		वापस 0;
	अगर (sginfo->umem)
		pages = ib_umem_num_dma_blocks(sginfo->umem, sginfo->pgsize);
	अन्यथा
		pages = sginfo->npages;
	/* page ptr arrays */
	pbl->pg_arr = vदो_स्मृति(pages * माप(व्योम *));
	अगर (!pbl->pg_arr)
		वापस -ENOMEM;

	pbl->pg_map_arr = vदो_स्मृति(pages * माप(dma_addr_t));
	अगर (!pbl->pg_map_arr) अणु
		vमुक्त(pbl->pg_arr);
		pbl->pg_arr = शून्य;
		वापस -ENOMEM;
	पूर्ण
	pbl->pg_count = 0;
	pbl->pg_size = sginfo->pgsize;

	अगर (!sginfo->umem) अणु
		क्रम (i = 0; i < pages; i++) अणु
			pbl->pg_arr[i] = dma_alloc_coherent(&pdev->dev,
							    pbl->pg_size,
							    &pbl->pg_map_arr[i],
							    GFP_KERNEL);
			अगर (!pbl->pg_arr[i])
				जाओ fail;
			pbl->pg_count++;
		पूर्ण
	पूर्ण अन्यथा अणु
		is_umem = true;
		bnxt_qplib_fill_user_dma_pages(pbl, sginfo);
	पूर्ण

	वापस 0;
fail:
	__मुक्त_pbl(res, pbl, is_umem);
	वापस -ENOMEM;
पूर्ण

/* HWQ */
व्योम bnxt_qplib_मुक्त_hwq(काष्ठा bnxt_qplib_res *res,
			 काष्ठा bnxt_qplib_hwq *hwq)
अणु
	पूर्णांक i;

	अगर (!hwq->max_elements)
		वापस;
	अगर (hwq->level >= PBL_LVL_MAX)
		वापस;

	क्रम (i = 0; i < hwq->level + 1; i++) अणु
		अगर (i == hwq->level)
			__मुक्त_pbl(res, &hwq->pbl[i], hwq->is_user);
		अन्यथा
			__मुक्त_pbl(res, &hwq->pbl[i], false);
	पूर्ण

	hwq->level = PBL_LVL_MAX;
	hwq->max_elements = 0;
	hwq->element_size = 0;
	hwq->prod = 0;
	hwq->cons = 0;
	hwq->cp_bit = 0;
पूर्ण

/* All HWQs are घातer of 2 in size */

पूर्णांक bnxt_qplib_alloc_init_hwq(काष्ठा bnxt_qplib_hwq *hwq,
			      काष्ठा bnxt_qplib_hwq_attr *hwq_attr)
अणु
	u32 npages, aux_slots, pg_size, aux_pages = 0, aux_size = 0;
	काष्ठा bnxt_qplib_sg_info sginfo = अणुपूर्ण;
	u32 depth, stride, npbl, npde;
	dma_addr_t *src_phys_ptr, **dst_virt_ptr;
	काष्ठा bnxt_qplib_res *res;
	काष्ठा pci_dev *pdev;
	पूर्णांक i, rc, lvl;

	res = hwq_attr->res;
	pdev = res->pdev;
	pg_size = hwq_attr->sginfo->pgsize;
	hwq->level = PBL_LVL_MAX;

	depth = roundup_घात_of_two(hwq_attr->depth);
	stride = roundup_घात_of_two(hwq_attr->stride);
	अगर (hwq_attr->aux_depth) अणु
		aux_slots = hwq_attr->aux_depth;
		aux_size = roundup_घात_of_two(hwq_attr->aux_stride);
		aux_pages = (aux_slots * aux_size) / pg_size;
		अगर ((aux_slots * aux_size) % pg_size)
			aux_pages++;
	पूर्ण

	अगर (!hwq_attr->sginfo->umem) अणु
		hwq->is_user = false;
		npages = (depth * stride) / pg_size + aux_pages;
		अगर ((depth * stride) % pg_size)
			npages++;
		अगर (!npages)
			वापस -EINVAL;
		hwq_attr->sginfo->npages = npages;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ sginfo_num_pages = ib_umem_num_dma_blocks(
			hwq_attr->sginfo->umem, hwq_attr->sginfo->pgsize);

		hwq->is_user = true;
		npages = sginfo_num_pages;
		npages = (npages * PAGE_SIZE) /
			  BIT_ULL(hwq_attr->sginfo->pgshft);
		अगर ((sginfo_num_pages * PAGE_SIZE) %
		     BIT_ULL(hwq_attr->sginfo->pgshft))
			अगर (!npages)
				npages++;
	पूर्ण

	अगर (npages == MAX_PBL_LVL_0_PGS) अणु
		/* This request is Level 0, map PTE */
		rc = __alloc_pbl(res, &hwq->pbl[PBL_LVL_0], hwq_attr->sginfo);
		अगर (rc)
			जाओ fail;
		hwq->level = PBL_LVL_0;
	पूर्ण

	अगर (npages > MAX_PBL_LVL_0_PGS) अणु
		अगर (npages > MAX_PBL_LVL_1_PGS) अणु
			u32 flag = (hwq_attr->type == HWQ_TYPE_L2_CMPL) ?
				    0 : PTU_PTE_VALID;
			/* 2 levels of indirection */
			npbl = npages >> MAX_PBL_LVL_1_PGS_SHIFT;
			अगर (npages % BIT(MAX_PBL_LVL_1_PGS_SHIFT))
				npbl++;
			npde = npbl >> MAX_PDL_LVL_SHIFT;
			अगर (npbl % BIT(MAX_PDL_LVL_SHIFT))
				npde++;
			/* Alloc PDE pages */
			sginfo.pgsize = npde * pg_size;
			sginfo.npages = 1;
			rc = __alloc_pbl(res, &hwq->pbl[PBL_LVL_0], &sginfo);

			/* Alloc PBL pages */
			sginfo.npages = npbl;
			sginfo.pgsize = PAGE_SIZE;
			rc = __alloc_pbl(res, &hwq->pbl[PBL_LVL_1], &sginfo);
			अगर (rc)
				जाओ fail;
			/* Fill PDL with PBL page poपूर्णांकers */
			dst_virt_ptr =
				(dma_addr_t **)hwq->pbl[PBL_LVL_0].pg_arr;
			src_phys_ptr = hwq->pbl[PBL_LVL_1].pg_map_arr;
			अगर (hwq_attr->type == HWQ_TYPE_MR) अणु
			/* For MR it is expected that we supply only 1 contigous
			 * page i.e only 1 entry in the PDL that will contain
			 * all the PBLs क्रम the user supplied memory region
			 */
				क्रम (i = 0; i < hwq->pbl[PBL_LVL_1].pg_count;
				     i++)
					dst_virt_ptr[0][i] = src_phys_ptr[i] |
						flag;
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < hwq->pbl[PBL_LVL_1].pg_count;
				     i++)
					dst_virt_ptr[PTR_PG(i)][PTR_IDX(i)] =
						src_phys_ptr[i] |
						PTU_PDE_VALID;
			पूर्ण
			/* Alloc or init PTEs */
			rc = __alloc_pbl(res, &hwq->pbl[PBL_LVL_2],
					 hwq_attr->sginfo);
			अगर (rc)
				जाओ fail;
			hwq->level = PBL_LVL_2;
			अगर (hwq_attr->sginfo->nopte)
				जाओ करोne;
			/* Fill PBLs with PTE poपूर्णांकers */
			dst_virt_ptr =
				(dma_addr_t **)hwq->pbl[PBL_LVL_1].pg_arr;
			src_phys_ptr = hwq->pbl[PBL_LVL_2].pg_map_arr;
			क्रम (i = 0; i < hwq->pbl[PBL_LVL_2].pg_count; i++) अणु
				dst_virt_ptr[PTR_PG(i)][PTR_IDX(i)] =
					src_phys_ptr[i] | PTU_PTE_VALID;
			पूर्ण
			अगर (hwq_attr->type == HWQ_TYPE_QUEUE) अणु
				/* Find the last pg of the size */
				i = hwq->pbl[PBL_LVL_2].pg_count;
				dst_virt_ptr[PTR_PG(i - 1)][PTR_IDX(i - 1)] |=
								  PTU_PTE_LAST;
				अगर (i > 1)
					dst_virt_ptr[PTR_PG(i - 2)]
						    [PTR_IDX(i - 2)] |=
						    PTU_PTE_NEXT_TO_LAST;
			पूर्ण
		पूर्ण अन्यथा अणु /* pages < 512 npbl = 1, npde = 0 */
			u32 flag = (hwq_attr->type == HWQ_TYPE_L2_CMPL) ?
				    0 : PTU_PTE_VALID;

			/* 1 level of indirection */
			npbl = npages >> MAX_PBL_LVL_1_PGS_SHIFT;
			अगर (npages % BIT(MAX_PBL_LVL_1_PGS_SHIFT))
				npbl++;
			sginfo.npages = npbl;
			sginfo.pgsize = PAGE_SIZE;
			/* Alloc PBL page */
			rc = __alloc_pbl(res, &hwq->pbl[PBL_LVL_0], &sginfo);
			अगर (rc)
				जाओ fail;
			/* Alloc or init  PTEs */
			rc = __alloc_pbl(res, &hwq->pbl[PBL_LVL_1],
					 hwq_attr->sginfo);
			अगर (rc)
				जाओ fail;
			hwq->level = PBL_LVL_1;
			अगर (hwq_attr->sginfo->nopte)
				जाओ करोne;
			/* Fill PBL with PTE poपूर्णांकers */
			dst_virt_ptr =
				(dma_addr_t **)hwq->pbl[PBL_LVL_0].pg_arr;
			src_phys_ptr = hwq->pbl[PBL_LVL_1].pg_map_arr;
			क्रम (i = 0; i < hwq->pbl[PBL_LVL_1].pg_count; i++)
				dst_virt_ptr[PTR_PG(i)][PTR_IDX(i)] =
					src_phys_ptr[i] | flag;
			अगर (hwq_attr->type == HWQ_TYPE_QUEUE) अणु
				/* Find the last pg of the size */
				i = hwq->pbl[PBL_LVL_1].pg_count;
				dst_virt_ptr[PTR_PG(i - 1)][PTR_IDX(i - 1)] |=
								  PTU_PTE_LAST;
				अगर (i > 1)
					dst_virt_ptr[PTR_PG(i - 2)]
						    [PTR_IDX(i - 2)] |=
						    PTU_PTE_NEXT_TO_LAST;
			पूर्ण
		पूर्ण
	पूर्ण
करोne:
	hwq->prod = 0;
	hwq->cons = 0;
	hwq->pdev = pdev;
	hwq->depth = hwq_attr->depth;
	hwq->max_elements = depth;
	hwq->element_size = stride;
	hwq->qe_ppg = pg_size / stride;
	/* For direct access to the elements */
	lvl = hwq->level;
	अगर (hwq_attr->sginfo->nopte && hwq->level)
		lvl = hwq->level - 1;
	hwq->pbl_ptr = hwq->pbl[lvl].pg_arr;
	hwq->pbl_dma_ptr = hwq->pbl[lvl].pg_map_arr;
	spin_lock_init(&hwq->lock);

	वापस 0;
fail:
	bnxt_qplib_मुक्त_hwq(res, hwq);
	वापस -ENOMEM;
पूर्ण

/* Context Tables */
व्योम bnxt_qplib_मुक्त_ctx(काष्ठा bnxt_qplib_res *res,
			 काष्ठा bnxt_qplib_ctx *ctx)
अणु
	पूर्णांक i;

	bnxt_qplib_मुक्त_hwq(res, &ctx->qpc_tbl);
	bnxt_qplib_मुक्त_hwq(res, &ctx->mrw_tbl);
	bnxt_qplib_मुक्त_hwq(res, &ctx->srqc_tbl);
	bnxt_qplib_मुक्त_hwq(res, &ctx->cq_tbl);
	bnxt_qplib_मुक्त_hwq(res, &ctx->tim_tbl);
	क्रम (i = 0; i < MAX_TQM_ALLOC_REQ; i++)
		bnxt_qplib_मुक्त_hwq(res, &ctx->tqm_ctx.qtbl[i]);
	/* restore original pde level beक्रमe destroy */
	ctx->tqm_ctx.pde.level = ctx->tqm_ctx.pde_level;
	bnxt_qplib_मुक्त_hwq(res, &ctx->tqm_ctx.pde);
	bnxt_qplib_मुक्त_stats_ctx(res->pdev, &ctx->stats);
पूर्ण

अटल पूर्णांक bnxt_qplib_alloc_tqm_rings(काष्ठा bnxt_qplib_res *res,
				      काष्ठा bnxt_qplib_ctx *ctx)
अणु
	काष्ठा bnxt_qplib_hwq_attr hwq_attr = अणुपूर्ण;
	काष्ठा bnxt_qplib_sg_info sginfo = अणुपूर्ण;
	काष्ठा bnxt_qplib_tqm_ctx *tqmctx;
	पूर्णांक rc = 0;
	पूर्णांक i;

	tqmctx = &ctx->tqm_ctx;

	sginfo.pgsize = PAGE_SIZE;
	sginfo.pgshft = PAGE_SHIFT;
	hwq_attr.sginfo = &sginfo;
	hwq_attr.res = res;
	hwq_attr.type = HWQ_TYPE_CTX;
	hwq_attr.depth = 512;
	hwq_attr.stride = माप(u64);
	/* Alloc pdl buffer */
	rc = bnxt_qplib_alloc_init_hwq(&tqmctx->pde, &hwq_attr);
	अगर (rc)
		जाओ out;
	/* Save original pdl level */
	tqmctx->pde_level = tqmctx->pde.level;

	hwq_attr.stride = 1;
	क्रम (i = 0; i < MAX_TQM_ALLOC_REQ; i++) अणु
		अगर (!tqmctx->qcount[i])
			जारी;
		hwq_attr.depth = ctx->qpc_count * tqmctx->qcount[i];
		rc = bnxt_qplib_alloc_init_hwq(&tqmctx->qtbl[i], &hwq_attr);
		अगर (rc)
			जाओ out;
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल व्योम bnxt_qplib_map_tqm_pgtbl(काष्ठा bnxt_qplib_tqm_ctx *ctx)
अणु
	काष्ठा bnxt_qplib_hwq *tbl;
	dma_addr_t *dma_ptr;
	__le64 **pbl_ptr, *ptr;
	पूर्णांक i, j, k;
	पूर्णांक fnz_idx = -1;
	पूर्णांक pg_count;

	pbl_ptr = (__le64 **)ctx->pde.pbl_ptr;

	क्रम (i = 0, j = 0; i < MAX_TQM_ALLOC_REQ;
	     i++, j += MAX_TQM_ALLOC_BLK_SIZE) अणु
		tbl = &ctx->qtbl[i];
		अगर (!tbl->max_elements)
			जारी;
		अगर (fnz_idx == -1)
			fnz_idx = i; /* first non-zero index */
		चयन (tbl->level) अणु
		हाल PBL_LVL_2:
			pg_count = tbl->pbl[PBL_LVL_1].pg_count;
			क्रम (k = 0; k < pg_count; k++) अणु
				ptr = &pbl_ptr[PTR_PG(j + k)][PTR_IDX(j + k)];
				dma_ptr = &tbl->pbl[PBL_LVL_1].pg_map_arr[k];
				*ptr = cpu_to_le64(*dma_ptr | PTU_PTE_VALID);
			पूर्ण
			अवरोध;
		हाल PBL_LVL_1:
		हाल PBL_LVL_0:
		शेष:
			ptr = &pbl_ptr[PTR_PG(j)][PTR_IDX(j)];
			*ptr = cpu_to_le64(tbl->pbl[PBL_LVL_0].pg_map_arr[0] |
					   PTU_PTE_VALID);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (fnz_idx == -1)
		fnz_idx = 0;
	/* update pde level as per page table programming */
	ctx->pde.level = (ctx->qtbl[fnz_idx].level == PBL_LVL_2) ? PBL_LVL_2 :
			  ctx->qtbl[fnz_idx].level + 1;
पूर्ण

अटल पूर्णांक bnxt_qplib_setup_tqm_rings(काष्ठा bnxt_qplib_res *res,
				      काष्ठा bnxt_qplib_ctx *ctx)
अणु
	पूर्णांक rc = 0;

	rc = bnxt_qplib_alloc_tqm_rings(res, ctx);
	अगर (rc)
		जाओ fail;

	bnxt_qplib_map_tqm_pgtbl(&ctx->tqm_ctx);
fail:
	वापस rc;
पूर्ण

/*
 * Routine: bnxt_qplib_alloc_ctx
 * Description:
 *     Context tables are memories which are used by the chip fw.
 *     The 6 tables defined are:
 *             QPC ctx - holds QP states
 *             MRW ctx - holds memory region and winकरोw
 *             SRQ ctx - holds shared RQ states
 *             CQ ctx - holds completion queue states
 *             TQM ctx - holds Tx Queue Manager context
 *             TIM ctx - holds समयr context
 *     Depending on the size of the tbl requested, either a 1 Page Buffer List
 *     or a 1-to-2-stage indirection Page Directory List + 1 PBL is used
 *     instead.
 *     Table might be employed as follows:
 *             For 0      < ctx size <= 1 PAGE, 0 level of ind is used
 *             For 1 PAGE < ctx size <= 512 entries size, 1 level of ind is used
 *             For 512    < ctx size <= MAX, 2 levels of ind is used
 * Returns:
 *     0 अगर success, अन्यथा -ERRORS
 */
पूर्णांक bnxt_qplib_alloc_ctx(काष्ठा bnxt_qplib_res *res,
			 काष्ठा bnxt_qplib_ctx *ctx,
			 bool virt_fn, bool is_p5)
अणु
	काष्ठा bnxt_qplib_hwq_attr hwq_attr = अणुपूर्ण;
	काष्ठा bnxt_qplib_sg_info sginfo = अणुपूर्ण;
	पूर्णांक rc = 0;

	अगर (virt_fn || is_p5)
		जाओ stats_alloc;

	/* QPC Tables */
	sginfo.pgsize = PAGE_SIZE;
	sginfo.pgshft = PAGE_SHIFT;
	hwq_attr.sginfo = &sginfo;

	hwq_attr.res = res;
	hwq_attr.depth = ctx->qpc_count;
	hwq_attr.stride = BNXT_QPLIB_MAX_QP_CTX_ENTRY_SIZE;
	hwq_attr.type = HWQ_TYPE_CTX;
	rc = bnxt_qplib_alloc_init_hwq(&ctx->qpc_tbl, &hwq_attr);
	अगर (rc)
		जाओ fail;

	/* MRW Tables */
	hwq_attr.depth = ctx->mrw_count;
	hwq_attr.stride = BNXT_QPLIB_MAX_MRW_CTX_ENTRY_SIZE;
	rc = bnxt_qplib_alloc_init_hwq(&ctx->mrw_tbl, &hwq_attr);
	अगर (rc)
		जाओ fail;

	/* SRQ Tables */
	hwq_attr.depth = ctx->srqc_count;
	hwq_attr.stride = BNXT_QPLIB_MAX_SRQ_CTX_ENTRY_SIZE;
	rc = bnxt_qplib_alloc_init_hwq(&ctx->srqc_tbl, &hwq_attr);
	अगर (rc)
		जाओ fail;

	/* CQ Tables */
	hwq_attr.depth = ctx->cq_count;
	hwq_attr.stride = BNXT_QPLIB_MAX_CQ_CTX_ENTRY_SIZE;
	rc = bnxt_qplib_alloc_init_hwq(&ctx->cq_tbl, &hwq_attr);
	अगर (rc)
		जाओ fail;

	/* TQM Buffer */
	rc = bnxt_qplib_setup_tqm_rings(res, ctx);
	अगर (rc)
		जाओ fail;
	/* TIM Buffer */
	ctx->tim_tbl.max_elements = ctx->qpc_count * 16;
	hwq_attr.depth = ctx->qpc_count * 16;
	hwq_attr.stride = 1;
	rc = bnxt_qplib_alloc_init_hwq(&ctx->tim_tbl, &hwq_attr);
	अगर (rc)
		जाओ fail;
stats_alloc:
	/* Stats */
	rc = bnxt_qplib_alloc_stats_ctx(res->pdev, &ctx->stats);
	अगर (rc)
		जाओ fail;

	वापस 0;

fail:
	bnxt_qplib_मुक्त_ctx(res, ctx);
	वापस rc;
पूर्ण

/* GUID */
व्योम bnxt_qplib_get_guid(u8 *dev_addr, u8 *guid)
अणु
	u8 mac[ETH_ALEN];

	/* MAC-48 to EUI-64 mapping */
	स_नकल(mac, dev_addr, ETH_ALEN);
	guid[0] = mac[0] ^ 2;
	guid[1] = mac[1];
	guid[2] = mac[2];
	guid[3] = 0xff;
	guid[4] = 0xfe;
	guid[5] = mac[3];
	guid[6] = mac[4];
	guid[7] = mac[5];
पूर्ण

अटल व्योम bnxt_qplib_मुक्त_sgid_tbl(काष्ठा bnxt_qplib_res *res,
				     काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl)
अणु
	kमुक्त(sgid_tbl->tbl);
	kमुक्त(sgid_tbl->hw_id);
	kमुक्त(sgid_tbl->ctx);
	kमुक्त(sgid_tbl->vlan);
	sgid_tbl->tbl = शून्य;
	sgid_tbl->hw_id = शून्य;
	sgid_tbl->ctx = शून्य;
	sgid_tbl->vlan = शून्य;
	sgid_tbl->max = 0;
	sgid_tbl->active = 0;
पूर्ण

अटल पूर्णांक bnxt_qplib_alloc_sgid_tbl(काष्ठा bnxt_qplib_res *res,
				     काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl,
				     u16 max)
अणु
	sgid_tbl->tbl = kसुस्मृति(max, माप(*sgid_tbl->tbl), GFP_KERNEL);
	अगर (!sgid_tbl->tbl)
		वापस -ENOMEM;

	sgid_tbl->hw_id = kसुस्मृति(max, माप(u16), GFP_KERNEL);
	अगर (!sgid_tbl->hw_id)
		जाओ out_मुक्त1;

	sgid_tbl->ctx = kसुस्मृति(max, माप(व्योम *), GFP_KERNEL);
	अगर (!sgid_tbl->ctx)
		जाओ out_मुक्त2;

	sgid_tbl->vlan = kसुस्मृति(max, माप(u8), GFP_KERNEL);
	अगर (!sgid_tbl->vlan)
		जाओ out_मुक्त3;

	sgid_tbl->max = max;
	वापस 0;
out_मुक्त3:
	kमुक्त(sgid_tbl->ctx);
	sgid_tbl->ctx = शून्य;
out_मुक्त2:
	kमुक्त(sgid_tbl->hw_id);
	sgid_tbl->hw_id = शून्य;
out_मुक्त1:
	kमुक्त(sgid_tbl->tbl);
	sgid_tbl->tbl = शून्य;
	वापस -ENOMEM;
पूर्ण;

अटल व्योम bnxt_qplib_cleanup_sgid_tbl(काष्ठा bnxt_qplib_res *res,
					काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sgid_tbl->max; i++) अणु
		अगर (स_भेद(&sgid_tbl->tbl[i], &bnxt_qplib_gid_zero,
			   माप(bnxt_qplib_gid_zero)))
			bnxt_qplib_del_sgid(sgid_tbl, &sgid_tbl->tbl[i].gid,
					    sgid_tbl->tbl[i].vlan_id, true);
	पूर्ण
	स_रखो(sgid_tbl->tbl, 0, माप(*sgid_tbl->tbl) * sgid_tbl->max);
	स_रखो(sgid_tbl->hw_id, -1, माप(u16) * sgid_tbl->max);
	स_रखो(sgid_tbl->vlan, 0, माप(u8) * sgid_tbl->max);
	sgid_tbl->active = 0;
पूर्ण

अटल व्योम bnxt_qplib_init_sgid_tbl(काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl,
				     काष्ठा net_device *netdev)
अणु
	u32 i;

	क्रम (i = 0; i < sgid_tbl->max; i++)
		sgid_tbl->tbl[i].vlan_id = 0xffff;

	स_रखो(sgid_tbl->hw_id, -1, माप(u16) * sgid_tbl->max);
पूर्ण

अटल व्योम bnxt_qplib_मुक्त_pkey_tbl(काष्ठा bnxt_qplib_res *res,
				     काष्ठा bnxt_qplib_pkey_tbl *pkey_tbl)
अणु
	अगर (!pkey_tbl->tbl)
		dev_dbg(&res->pdev->dev, "PKEY tbl not present\n");
	अन्यथा
		kमुक्त(pkey_tbl->tbl);

	pkey_tbl->tbl = शून्य;
	pkey_tbl->max = 0;
	pkey_tbl->active = 0;
पूर्ण

अटल पूर्णांक bnxt_qplib_alloc_pkey_tbl(काष्ठा bnxt_qplib_res *res,
				     काष्ठा bnxt_qplib_pkey_tbl *pkey_tbl,
				     u16 max)
अणु
	pkey_tbl->tbl = kसुस्मृति(max, माप(u16), GFP_KERNEL);
	अगर (!pkey_tbl->tbl)
		वापस -ENOMEM;

	pkey_tbl->max = max;
	वापस 0;
पूर्ण;

/* PDs */
पूर्णांक bnxt_qplib_alloc_pd(काष्ठा bnxt_qplib_pd_tbl *pdt, काष्ठा bnxt_qplib_pd *pd)
अणु
	u32 bit_num;

	bit_num = find_first_bit(pdt->tbl, pdt->max);
	अगर (bit_num == pdt->max)
		वापस -ENOMEM;

	/* Found unused PD */
	clear_bit(bit_num, pdt->tbl);
	pd->id = bit_num;
	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_dealloc_pd(काष्ठा bnxt_qplib_res *res,
			  काष्ठा bnxt_qplib_pd_tbl *pdt,
			  काष्ठा bnxt_qplib_pd *pd)
अणु
	अगर (test_and_set_bit(pd->id, pdt->tbl)) अणु
		dev_warn(&res->pdev->dev, "Freeing an unused PD? pdn = %d\n",
			 pd->id);
		वापस -EINVAL;
	पूर्ण
	pd->id = 0;
	वापस 0;
पूर्ण

अटल व्योम bnxt_qplib_मुक्त_pd_tbl(काष्ठा bnxt_qplib_pd_tbl *pdt)
अणु
	kमुक्त(pdt->tbl);
	pdt->tbl = शून्य;
	pdt->max = 0;
पूर्ण

अटल पूर्णांक bnxt_qplib_alloc_pd_tbl(काष्ठा bnxt_qplib_res *res,
				   काष्ठा bnxt_qplib_pd_tbl *pdt,
				   u32 max)
अणु
	u32 bytes;

	bytes = max >> 3;
	अगर (!bytes)
		bytes = 1;
	pdt->tbl = kदो_स्मृति(bytes, GFP_KERNEL);
	अगर (!pdt->tbl)
		वापस -ENOMEM;

	pdt->max = max;
	स_रखो((u8 *)pdt->tbl, 0xFF, bytes);

	वापस 0;
पूर्ण

/* DPIs */
पूर्णांक bnxt_qplib_alloc_dpi(काष्ठा bnxt_qplib_dpi_tbl *dpit,
			 काष्ठा bnxt_qplib_dpi     *dpi,
			 व्योम                      *app)
अणु
	u32 bit_num;

	bit_num = find_first_bit(dpit->tbl, dpit->max);
	अगर (bit_num == dpit->max)
		वापस -ENOMEM;

	/* Found unused DPI */
	clear_bit(bit_num, dpit->tbl);
	dpit->app_tbl[bit_num] = app;

	dpi->dpi = bit_num;
	dpi->dbr = dpit->dbr_bar_reg_iomem + (bit_num * PAGE_SIZE);
	dpi->umdbr = dpit->unmapped_dbr + (bit_num * PAGE_SIZE);

	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_dealloc_dpi(काष्ठा bnxt_qplib_res *res,
			   काष्ठा bnxt_qplib_dpi_tbl *dpit,
			   काष्ठा bnxt_qplib_dpi     *dpi)
अणु
	अगर (dpi->dpi >= dpit->max) अणु
		dev_warn(&res->pdev->dev, "Invalid DPI? dpi = %d\n", dpi->dpi);
		वापस -EINVAL;
	पूर्ण
	अगर (test_and_set_bit(dpi->dpi, dpit->tbl)) अणु
		dev_warn(&res->pdev->dev, "Freeing an unused DPI? dpi = %d\n",
			 dpi->dpi);
		वापस -EINVAL;
	पूर्ण
	अगर (dpit->app_tbl)
		dpit->app_tbl[dpi->dpi] = शून्य;
	स_रखो(dpi, 0, माप(*dpi));

	वापस 0;
पूर्ण

अटल व्योम bnxt_qplib_मुक्त_dpi_tbl(काष्ठा bnxt_qplib_res     *res,
				    काष्ठा bnxt_qplib_dpi_tbl *dpit)
अणु
	kमुक्त(dpit->tbl);
	kमुक्त(dpit->app_tbl);
	अगर (dpit->dbr_bar_reg_iomem)
		pci_iounmap(res->pdev, dpit->dbr_bar_reg_iomem);
	स_रखो(dpit, 0, माप(*dpit));
पूर्ण

अटल पूर्णांक bnxt_qplib_alloc_dpi_tbl(काष्ठा bnxt_qplib_res     *res,
				    काष्ठा bnxt_qplib_dpi_tbl *dpit,
				    u32                       dbr_offset)
अणु
	u32 dbr_bar_reg = RCFW_DBR_PCI_BAR_REGION;
	resource_माप_प्रकार bar_reg_base;
	u32 dbr_len, bytes;

	अगर (dpit->dbr_bar_reg_iomem) अणु
		dev_err(&res->pdev->dev, "DBR BAR region %d already mapped\n",
			dbr_bar_reg);
		वापस -EALREADY;
	पूर्ण

	bar_reg_base = pci_resource_start(res->pdev, dbr_bar_reg);
	अगर (!bar_reg_base) अणु
		dev_err(&res->pdev->dev, "BAR region %d resc start failed\n",
			dbr_bar_reg);
		वापस -ENOMEM;
	पूर्ण

	dbr_len = pci_resource_len(res->pdev, dbr_bar_reg) - dbr_offset;
	अगर (!dbr_len || ((dbr_len & (PAGE_SIZE - 1)) != 0)) अणु
		dev_err(&res->pdev->dev, "Invalid DBR length %d\n", dbr_len);
		वापस -ENOMEM;
	पूर्ण

	dpit->dbr_bar_reg_iomem = ioremap(bar_reg_base + dbr_offset,
						  dbr_len);
	अगर (!dpit->dbr_bar_reg_iomem) अणु
		dev_err(&res->pdev->dev,
			"FP: DBR BAR region %d mapping failed\n", dbr_bar_reg);
		वापस -ENOMEM;
	पूर्ण

	dpit->unmapped_dbr = bar_reg_base + dbr_offset;
	dpit->max = dbr_len / PAGE_SIZE;

	dpit->app_tbl = kसुस्मृति(dpit->max, माप(व्योम *), GFP_KERNEL);
	अगर (!dpit->app_tbl)
		जाओ unmap_io;

	bytes = dpit->max >> 3;
	अगर (!bytes)
		bytes = 1;

	dpit->tbl = kदो_स्मृति(bytes, GFP_KERNEL);
	अगर (!dpit->tbl) अणु
		kमुक्त(dpit->app_tbl);
		dpit->app_tbl = शून्य;
		जाओ unmap_io;
	पूर्ण

	स_रखो((u8 *)dpit->tbl, 0xFF, bytes);

	वापस 0;

unmap_io:
	pci_iounmap(res->pdev, dpit->dbr_bar_reg_iomem);
	dpit->dbr_bar_reg_iomem = शून्य;
	वापस -ENOMEM;
पूर्ण

/* PKEYs */
अटल व्योम bnxt_qplib_cleanup_pkey_tbl(काष्ठा bnxt_qplib_pkey_tbl *pkey_tbl)
अणु
	स_रखो(pkey_tbl->tbl, 0, माप(u16) * pkey_tbl->max);
	pkey_tbl->active = 0;
पूर्ण

अटल व्योम bnxt_qplib_init_pkey_tbl(काष्ठा bnxt_qplib_res *res,
				     काष्ठा bnxt_qplib_pkey_tbl *pkey_tbl)
अणु
	u16 pkey = 0xFFFF;

	स_रखो(pkey_tbl->tbl, 0, माप(u16) * pkey_tbl->max);

	/* pkey शेष = 0xFFFF */
	bnxt_qplib_add_pkey(res, pkey_tbl, &pkey, false);
पूर्ण

/* Stats */
अटल व्योम bnxt_qplib_मुक्त_stats_ctx(काष्ठा pci_dev *pdev,
				      काष्ठा bnxt_qplib_stats *stats)
अणु
	अगर (stats->dma) अणु
		dma_मुक्त_coherent(&pdev->dev, stats->size,
				  stats->dma, stats->dma_map);
	पूर्ण
	स_रखो(stats, 0, माप(*stats));
	stats->fw_id = -1;
पूर्ण

अटल पूर्णांक bnxt_qplib_alloc_stats_ctx(काष्ठा pci_dev *pdev,
				      काष्ठा bnxt_qplib_stats *stats)
अणु
	स_रखो(stats, 0, माप(*stats));
	stats->fw_id = -1;
	/* 128 byte aligned context memory is required only क्रम 57500.
	 * However making this unconditional, it करोes not harm previous
	 * generation.
	 */
	stats->size = ALIGN(माप(काष्ठा ctx_hw_stats), 128);
	stats->dma = dma_alloc_coherent(&pdev->dev, stats->size,
					&stats->dma_map, GFP_KERNEL);
	अगर (!stats->dma) अणु
		dev_err(&pdev->dev, "Stats DMA allocation failed\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम bnxt_qplib_cleanup_res(काष्ठा bnxt_qplib_res *res)
अणु
	bnxt_qplib_cleanup_pkey_tbl(&res->pkey_tbl);
	bnxt_qplib_cleanup_sgid_tbl(res, &res->sgid_tbl);
पूर्ण

पूर्णांक bnxt_qplib_init_res(काष्ठा bnxt_qplib_res *res)
अणु
	bnxt_qplib_init_sgid_tbl(&res->sgid_tbl, res->netdev);
	bnxt_qplib_init_pkey_tbl(res, &res->pkey_tbl);

	वापस 0;
पूर्ण

व्योम bnxt_qplib_मुक्त_res(काष्ठा bnxt_qplib_res *res)
अणु
	bnxt_qplib_मुक्त_pkey_tbl(res, &res->pkey_tbl);
	bnxt_qplib_मुक्त_sgid_tbl(res, &res->sgid_tbl);
	bnxt_qplib_मुक्त_pd_tbl(&res->pd_tbl);
	bnxt_qplib_मुक्त_dpi_tbl(res, &res->dpi_tbl);
पूर्ण

पूर्णांक bnxt_qplib_alloc_res(काष्ठा bnxt_qplib_res *res, काष्ठा pci_dev *pdev,
			 काष्ठा net_device *netdev,
			 काष्ठा bnxt_qplib_dev_attr *dev_attr)
अणु
	पूर्णांक rc = 0;

	res->pdev = pdev;
	res->netdev = netdev;

	rc = bnxt_qplib_alloc_sgid_tbl(res, &res->sgid_tbl, dev_attr->max_sgid);
	अगर (rc)
		जाओ fail;

	rc = bnxt_qplib_alloc_pkey_tbl(res, &res->pkey_tbl, dev_attr->max_pkey);
	अगर (rc)
		जाओ fail;

	rc = bnxt_qplib_alloc_pd_tbl(res, &res->pd_tbl, dev_attr->max_pd);
	अगर (rc)
		जाओ fail;

	rc = bnxt_qplib_alloc_dpi_tbl(res, &res->dpi_tbl, dev_attr->l2_db_size);
	अगर (rc)
		जाओ fail;

	वापस 0;
fail:
	bnxt_qplib_मुक्त_res(res);
	वापस rc;
पूर्ण
