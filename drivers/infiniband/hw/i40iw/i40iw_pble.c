<शैली गुरु>
/*******************************************************************************
*
* Copyright (c) 2015-2016 Intel Corporation.  All rights reserved.
*
* This software is available to you under a choice of one of two
* licenses.  You may choose to be licensed under the terms of the GNU
* General Public License (GPL) Version 2, available from the file
* COPYING in the मुख्य directory of this source tree, or the
* OpenFabrics.org BSD license below:
*
*   Redistribution and use in source and binary क्रमms, with or
*   without modअगरication, are permitted provided that the following
*   conditions are met:
*
*    - Redistributions of source code must retain the above
*	copyright notice, this list of conditions and the following
*	disclaimer.
*
*    - Redistributions in binary क्रमm must reproduce the above
*	copyright notice, this list of conditions and the following
*	disclaimer in the करोcumentation and/or other materials
*	provided with the distribution.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*******************************************************************************/

#समावेश "i40iw_status.h"
#समावेश "i40iw_osdep.h"
#समावेश "i40iw_register.h"
#समावेश "i40iw_hmc.h"

#समावेश "i40iw_d.h"
#समावेश "i40iw_type.h"
#समावेश "i40iw_p.h"

#समावेश <linux/pci.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "i40iw_pble.h"
#समावेश "i40iw.h"

काष्ठा i40iw_device;
अटल क्रमागत i40iw_status_code add_pble_pool(काष्ठा i40iw_sc_dev *dev,
					    काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc);
अटल व्योम i40iw_मुक्त_vदो_स्मृति_mem(काष्ठा i40iw_hw *hw, काष्ठा i40iw_chunk *chunk);

/**
 * i40iw_destroy_pble_pool - destroy pool during module unload
 * @dev: i40iw_sc_dev काष्ठा
 * @pble_rsrc:	pble resources
 */
व्योम i40iw_destroy_pble_pool(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc)
अणु
	काष्ठा list_head *clist;
	काष्ठा list_head *tlist;
	काष्ठा i40iw_chunk *chunk;
	काष्ठा i40iw_pble_pool *pinfo = &pble_rsrc->pinfo;

	अगर (pinfo->pool) अणु
		list_क्रम_each_safe(clist, tlist, &pinfo->clist) अणु
			chunk = list_entry(clist, काष्ठा i40iw_chunk, list);
			अगर (chunk->type == I40IW_VMALLOC)
				i40iw_मुक्त_vदो_स्मृति_mem(dev->hw, chunk);
			kमुक्त(chunk);
		पूर्ण
		gen_pool_destroy(pinfo->pool);
	पूर्ण
पूर्ण

/**
 * i40iw_hmc_init_pble - Initialize pble resources during module load
 * @dev: i40iw_sc_dev काष्ठा
 * @pble_rsrc:	pble resources
 */
क्रमागत i40iw_status_code i40iw_hmc_init_pble(काष्ठा i40iw_sc_dev *dev,
					   काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc)
अणु
	काष्ठा i40iw_hmc_info *hmc_info;
	u32 fpm_idx = 0;

	hmc_info = dev->hmc_info;
	pble_rsrc->fpm_base_addr = hmc_info->hmc_obj[I40IW_HMC_IW_PBLE].base;
	/* Now start the pble' on 4k boundary */
	अगर (pble_rsrc->fpm_base_addr & 0xfff)
		fpm_idx = (PAGE_SIZE - (pble_rsrc->fpm_base_addr & 0xfff)) >> 3;

	pble_rsrc->unallocated_pble =
	    hmc_info->hmc_obj[I40IW_HMC_IW_PBLE].cnt - fpm_idx;
	pble_rsrc->next_fpm_addr = pble_rsrc->fpm_base_addr + (fpm_idx << 3);

	pble_rsrc->pinfo.pool_shअगरt = POOL_SHIFT;
	pble_rsrc->pinfo.pool = gen_pool_create(pble_rsrc->pinfo.pool_shअगरt, -1);
	INIT_LIST_HEAD(&pble_rsrc->pinfo.clist);
	अगर (!pble_rsrc->pinfo.pool)
		जाओ error;

	अगर (add_pble_pool(dev, pble_rsrc))
		जाओ error;

	वापस 0;

 error:i40iw_destroy_pble_pool(dev, pble_rsrc);
	वापस I40IW_ERR_NO_MEMORY;
पूर्ण

/**
 * get_sd_pd_idx -  Returns sd index, pd index and rel_pd_idx from fpm address
 * @pble_rsrc:	काष्ठाure containing fpm address
 * @idx: where to वापस indexes
 */
अटल अंतरभूत व्योम get_sd_pd_idx(काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc,
				 काष्ठा sd_pd_idx *idx)
अणु
	idx->sd_idx = (u32)(pble_rsrc->next_fpm_addr) / I40IW_HMC_सूचीECT_BP_SIZE;
	idx->pd_idx = (u32)(pble_rsrc->next_fpm_addr) / I40IW_HMC_PAGED_BP_SIZE;
	idx->rel_pd_idx = (idx->pd_idx % I40IW_HMC_PD_CNT_IN_SD);
पूर्ण

/**
 * add_sd_direct - add sd direct क्रम pble
 * @dev: hardware control device काष्ठाure
 * @pble_rsrc: pble resource ptr
 * @info: page info क्रम sd
 */
अटल क्रमागत i40iw_status_code add_sd_direct(काष्ठा i40iw_sc_dev *dev,
					    काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc,
					    काष्ठा i40iw_add_page_info *info)
अणु
	क्रमागत i40iw_status_code ret_code = 0;
	काष्ठा sd_pd_idx *idx = &info->idx;
	काष्ठा i40iw_chunk *chunk = info->chunk;
	काष्ठा i40iw_hmc_info *hmc_info = info->hmc_info;
	काष्ठा i40iw_hmc_sd_entry *sd_entry = info->sd_entry;
	u32 offset = 0;

	अगर (!sd_entry->valid) अणु
		अगर (dev->is_pf) अणु
			ret_code = i40iw_add_sd_table_entry(dev->hw, hmc_info,
							    info->idx.sd_idx,
							    I40IW_SD_TYPE_सूचीECT,
							    I40IW_HMC_सूचीECT_BP_SIZE);
			अगर (ret_code)
				वापस ret_code;
			chunk->type = I40IW_DMA_COHERENT;
		पूर्ण
	पूर्ण
	offset = idx->rel_pd_idx << I40IW_HMC_PAGED_BP_SHIFT;
	chunk->size = info->pages << I40IW_HMC_PAGED_BP_SHIFT;
	chunk->vaddr = ((u8 *)sd_entry->u.bp.addr.va + offset);
	chunk->fpm_addr = pble_rsrc->next_fpm_addr;
	i40iw_debug(dev, I40IW_DEBUG_PBLE, "chunk_size[%d] = 0x%x vaddr=%p fpm_addr = %llx\n",
		    chunk->size, chunk->size, chunk->vaddr, chunk->fpm_addr);
	वापस 0;
पूर्ण

/**
 * i40iw_मुक्त_vदो_स्मृति_mem - मुक्त vदो_स्मृति during बंद
 * @hw: hw काष्ठा
 * @chunk: chunk inक्रमmation क्रम vदो_स्मृति
 */
अटल व्योम i40iw_मुक्त_vदो_स्मृति_mem(काष्ठा i40iw_hw *hw, काष्ठा i40iw_chunk *chunk)
अणु
	काष्ठा pci_dev *pcidev = hw->pcidev;
	पूर्णांक i;

	अगर (!chunk->pg_cnt)
		जाओ करोne;
	क्रम (i = 0; i < chunk->pg_cnt; i++)
		dma_unmap_page(&pcidev->dev, chunk->dmaaddrs[i], PAGE_SIZE, DMA_BIसूचीECTIONAL);

 करोne:
	kमुक्त(chunk->dmaaddrs);
	chunk->dmaaddrs = शून्य;
	vमुक्त(chunk->vaddr);
	chunk->vaddr = शून्य;
	chunk->type = 0;
पूर्ण

/**
 * i40iw_get_vदो_स्मृति_mem - get 2M page क्रम sd
 * @hw: hardware address
 * @chunk: chunk to adf
 * @pg_cnt: #of 4 K pages
 */
अटल क्रमागत i40iw_status_code i40iw_get_vदो_स्मृति_mem(काष्ठा i40iw_hw *hw,
						    काष्ठा i40iw_chunk *chunk,
						    पूर्णांक pg_cnt)
अणु
	काष्ठा pci_dev *pcidev = hw->pcidev;
	काष्ठा page *page;
	u8 *addr;
	u32 size;
	पूर्णांक i;

	chunk->dmaaddrs = kzalloc(pg_cnt << 3, GFP_KERNEL);
	अगर (!chunk->dmaaddrs)
		वापस I40IW_ERR_NO_MEMORY;
	size = PAGE_SIZE * pg_cnt;
	chunk->vaddr = vदो_स्मृति(size);
	अगर (!chunk->vaddr) अणु
		kमुक्त(chunk->dmaaddrs);
		chunk->dmaaddrs = शून्य;
		वापस I40IW_ERR_NO_MEMORY;
	पूर्ण
	chunk->size = size;
	addr = (u8 *)chunk->vaddr;
	क्रम (i = 0; i < pg_cnt; i++) अणु
		page = vदो_स्मृति_to_page((व्योम *)addr);
		अगर (!page)
			अवरोध;
		chunk->dmaaddrs[i] = dma_map_page(&pcidev->dev, page, 0,
						  PAGE_SIZE, DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(&pcidev->dev, chunk->dmaaddrs[i]))
			अवरोध;
		addr += PAGE_SIZE;
	पूर्ण

	chunk->pg_cnt = i;
	chunk->type = I40IW_VMALLOC;
	अगर (i == pg_cnt)
		वापस 0;

	i40iw_मुक्त_vदो_स्मृति_mem(hw, chunk);
	वापस I40IW_ERR_NO_MEMORY;
पूर्ण

/**
 * fpm_to_idx - given fpm address, get pble index
 * @pble_rsrc: pble resource management
 * @addr: fpm address क्रम index
 */
अटल अंतरभूत u32 fpm_to_idx(काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc, u64 addr)
अणु
	वापस (addr - (pble_rsrc->fpm_base_addr)) >> 3;
पूर्ण

/**
 * add_bp_pages - add backing pages क्रम sd
 * @dev: hardware control device काष्ठाure
 * @pble_rsrc: pble resource management
 * @info: page info क्रम sd
 */
अटल क्रमागत i40iw_status_code add_bp_pages(काष्ठा i40iw_sc_dev *dev,
					   काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc,
					   काष्ठा i40iw_add_page_info *info)
अणु
	u8 *addr;
	काष्ठा i40iw_dma_mem mem;
	काष्ठा i40iw_hmc_pd_entry *pd_entry;
	काष्ठा i40iw_hmc_sd_entry *sd_entry = info->sd_entry;
	काष्ठा i40iw_hmc_info *hmc_info = info->hmc_info;
	काष्ठा i40iw_chunk *chunk = info->chunk;
	काष्ठा i40iw_manage_vf_pble_info vf_pble_info;
	क्रमागत i40iw_status_code status = 0;
	u32 rel_pd_idx = info->idx.rel_pd_idx;
	u32 pd_idx = info->idx.pd_idx;
	u32 i;

	status = i40iw_get_vदो_स्मृति_mem(dev->hw, chunk, info->pages);
	अगर (status)
		वापस I40IW_ERR_NO_MEMORY;
	status = i40iw_add_sd_table_entry(dev->hw, hmc_info,
					  info->idx.sd_idx, I40IW_SD_TYPE_PAGED,
					  I40IW_HMC_सूचीECT_BP_SIZE);
	अगर (status)
		जाओ error;
	अगर (!dev->is_pf) अणु
		status = i40iw_vchnl_vf_add_hmc_objs(dev, I40IW_HMC_IW_PBLE,
						     fpm_to_idx(pble_rsrc,
								pble_rsrc->next_fpm_addr),
						     (info->pages << PBLE_512_SHIFT));
		अगर (status) अणु
			i40iw_pr_err("allocate PBLEs in the PF.  Error %i\n", status);
			जाओ error;
		पूर्ण
	पूर्ण
	addr = chunk->vaddr;
	क्रम (i = 0; i < info->pages; i++) अणु
		mem.pa = chunk->dmaaddrs[i];
		mem.size = PAGE_SIZE;
		mem.va = (व्योम *)(addr);
		pd_entry = &sd_entry->u.pd_table.pd_entry[rel_pd_idx++];
		अगर (!pd_entry->valid) अणु
			status = i40iw_add_pd_table_entry(dev->hw, hmc_info, pd_idx++, &mem);
			अगर (status)
				जाओ error;
			addr += PAGE_SIZE;
		पूर्ण अन्यथा अणु
			i40iw_pr_err("pd entry is valid expecting to be invalid\n");
		पूर्ण
	पूर्ण
	अगर (!dev->is_pf) अणु
		vf_pble_info.first_pd_index = info->idx.rel_pd_idx;
		vf_pble_info.inv_pd_ent = false;
		vf_pble_info.pd_entry_cnt = PBLE_PER_PAGE;
		vf_pble_info.pd_pl_pba = sd_entry->u.pd_table.pd_page_addr.pa;
		vf_pble_info.sd_index = info->idx.sd_idx;
		status = i40iw_hw_manage_vf_pble_bp(dev->back_dev,
						    &vf_pble_info, true);
		अगर (status) अणु
			i40iw_pr_err("CQP manage VF PBLE BP failed.  %i\n", status);
			जाओ error;
		पूर्ण
	पूर्ण
	chunk->fpm_addr = pble_rsrc->next_fpm_addr;
	वापस 0;
error:
	i40iw_मुक्त_vदो_स्मृति_mem(dev->hw, chunk);
	वापस status;
पूर्ण

/**
 * add_pble_pool - add a sd entry क्रम pble resoure
 * @dev: hardware control device काष्ठाure
 * @pble_rsrc: pble resource management
 */
अटल क्रमागत i40iw_status_code add_pble_pool(काष्ठा i40iw_sc_dev *dev,
					    काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc)
अणु
	काष्ठा i40iw_hmc_sd_entry *sd_entry;
	काष्ठा i40iw_hmc_info *hmc_info;
	काष्ठा i40iw_chunk *chunk;
	काष्ठा i40iw_add_page_info info;
	काष्ठा sd_pd_idx *idx = &info.idx;
	क्रमागत i40iw_status_code ret_code = 0;
	क्रमागत i40iw_sd_entry_type sd_entry_type;
	u64 sd_reg_val = 0;
	u32 pages;

	अगर (pble_rsrc->unallocated_pble < PBLE_PER_PAGE)
		वापस I40IW_ERR_NO_MEMORY;
	अगर (pble_rsrc->next_fpm_addr & 0xfff) अणु
		i40iw_pr_err("next fpm_addr %llx\n", pble_rsrc->next_fpm_addr);
		वापस I40IW_ERR_INVALID_PAGE_DESC_INDEX;
	पूर्ण
	chunk = kzalloc(माप(*chunk), GFP_KERNEL);
	अगर (!chunk)
		वापस I40IW_ERR_NO_MEMORY;
	hmc_info = dev->hmc_info;
	chunk->fpm_addr = pble_rsrc->next_fpm_addr;
	get_sd_pd_idx(pble_rsrc, idx);
	sd_entry = &hmc_info->sd_table.sd_entry[idx->sd_idx];
	pages = (idx->rel_pd_idx) ? (I40IW_HMC_PD_CNT_IN_SD -
			idx->rel_pd_idx) : I40IW_HMC_PD_CNT_IN_SD;
	pages = min(pages, pble_rsrc->unallocated_pble >> PBLE_512_SHIFT);
	info.chunk = chunk;
	info.hmc_info = hmc_info;
	info.pages = pages;
	info.sd_entry = sd_entry;
	अगर (!sd_entry->valid) अणु
		sd_entry_type = (!idx->rel_pd_idx &&
				 (pages == I40IW_HMC_PD_CNT_IN_SD) &&
				 dev->is_pf) ? I40IW_SD_TYPE_सूचीECT : I40IW_SD_TYPE_PAGED;
	पूर्ण अन्यथा अणु
		sd_entry_type = sd_entry->entry_type;
	पूर्ण
	i40iw_debug(dev, I40IW_DEBUG_PBLE,
		    "pages = %d, unallocated_pble[%u] current_fpm_addr = %llx\n",
		    pages, pble_rsrc->unallocated_pble, pble_rsrc->next_fpm_addr);
	i40iw_debug(dev, I40IW_DEBUG_PBLE, "sd_entry_type = %d sd_entry valid = %d\n",
		    sd_entry_type, sd_entry->valid);

	अगर (sd_entry_type == I40IW_SD_TYPE_सूचीECT)
		ret_code = add_sd_direct(dev, pble_rsrc, &info);
	अगर (ret_code)
		sd_entry_type = I40IW_SD_TYPE_PAGED;
	अन्यथा
		pble_rsrc->stats_direct_sds++;

	अगर (sd_entry_type == I40IW_SD_TYPE_PAGED) अणु
		ret_code = add_bp_pages(dev, pble_rsrc, &info);
		अगर (ret_code)
			जाओ error;
		अन्यथा
			pble_rsrc->stats_paged_sds++;
	पूर्ण

	अगर (gen_pool_add_virt(pble_rsrc->pinfo.pool, (अचिन्हित दीर्घ)chunk->vaddr,
			      (phys_addr_t)chunk->fpm_addr, chunk->size, -1)) अणु
		i40iw_pr_err("could not allocate memory by gen_pool_addr_virt()\n");
		ret_code = I40IW_ERR_NO_MEMORY;
		जाओ error;
	पूर्ण
	pble_rsrc->next_fpm_addr += chunk->size;
	i40iw_debug(dev, I40IW_DEBUG_PBLE, "next_fpm_addr = %llx chunk_size[%u] = 0x%x\n",
		    pble_rsrc->next_fpm_addr, chunk->size, chunk->size);
	pble_rsrc->unallocated_pble -= (chunk->size >> 3);
	sd_reg_val = (sd_entry_type == I40IW_SD_TYPE_PAGED) ?
			sd_entry->u.pd_table.pd_page_addr.pa : sd_entry->u.bp.addr.pa;
	अगर (dev->is_pf && !sd_entry->valid) अणु
		ret_code = i40iw_hmc_sd_one(dev, hmc_info->hmc_fn_id,
					    sd_reg_val, idx->sd_idx,
					    sd_entry->entry_type, true);
		अगर (ret_code) अणु
			i40iw_pr_err("cqp cmd failed for sd (pbles)\n");
			जाओ error;
		पूर्ण
	पूर्ण

	sd_entry->valid = true;
	list_add(&chunk->list, &pble_rsrc->pinfo.clist);
	वापस 0;
 error:
	kमुक्त(chunk);
	वापस ret_code;
पूर्ण

/**
 * मुक्त_lvl2 - fee level 2 pble
 * @pble_rsrc: pble resource management
 * @palloc: level 2 pble allocation
 */
अटल व्योम मुक्त_lvl2(काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc,
		      काष्ठा i40iw_pble_alloc *palloc)
अणु
	u32 i;
	काष्ठा gen_pool *pool;
	काष्ठा i40iw_pble_level2 *lvl2 = &palloc->level2;
	काष्ठा i40iw_pble_info *root = &lvl2->root;
	काष्ठा i40iw_pble_info *leaf = lvl2->leaf;

	pool = pble_rsrc->pinfo.pool;

	क्रम (i = 0; i < lvl2->leaf_cnt; i++, leaf++) अणु
		अगर (leaf->addr)
			gen_pool_मुक्त(pool, leaf->addr, (leaf->cnt << 3));
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (root->addr)
		gen_pool_मुक्त(pool, root->addr, (root->cnt << 3));

	kमुक्त(lvl2->leaf);
	lvl2->leaf = शून्य;
पूर्ण

/**
 * get_lvl2_pble - get level 2 pble resource
 * @pble_rsrc: pble resource management
 * @palloc: level 2 pble allocation
 * @pool: pool poपूर्णांकer
 */
अटल क्रमागत i40iw_status_code get_lvl2_pble(काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc,
					    काष्ठा i40iw_pble_alloc *palloc,
					    काष्ठा gen_pool *pool)
अणु
	u32 lf4k, lflast, total, i;
	u32 pblcnt = PBLE_PER_PAGE;
	u64 *addr;
	काष्ठा i40iw_pble_level2 *lvl2 = &palloc->level2;
	काष्ठा i40iw_pble_info *root = &lvl2->root;
	काष्ठा i40iw_pble_info *leaf;

	/* number of full 512 (4K) leafs) */
	lf4k = palloc->total_cnt >> 9;
	lflast = palloc->total_cnt % PBLE_PER_PAGE;
	total = (lflast == 0) ? lf4k : lf4k + 1;
	lvl2->leaf_cnt = total;

	leaf = kzalloc((माप(*leaf) * total), GFP_ATOMIC);
	अगर (!leaf)
		वापस I40IW_ERR_NO_MEMORY;
	lvl2->leaf = leaf;
	/* allocate pbles क्रम the root */
	root->addr = gen_pool_alloc(pool, (total << 3));
	अगर (!root->addr) अणु
		kमुक्त(lvl2->leaf);
		lvl2->leaf = शून्य;
		वापस I40IW_ERR_NO_MEMORY;
	पूर्ण
	root->idx = fpm_to_idx(pble_rsrc,
			       (u64)gen_pool_virt_to_phys(pool, root->addr));
	root->cnt = total;
	addr = (u64 *)root->addr;
	क्रम (i = 0; i < total; i++, leaf++) अणु
		pblcnt = (lflast && ((i + 1) == total)) ? lflast : PBLE_PER_PAGE;
		leaf->addr = gen_pool_alloc(pool, (pblcnt << 3));
		अगर (!leaf->addr)
			जाओ error;
		leaf->idx = fpm_to_idx(pble_rsrc, (u64)gen_pool_virt_to_phys(pool, leaf->addr));

		leaf->cnt = pblcnt;
		*addr = (u64)leaf->idx;
		addr++;
	पूर्ण
	palloc->level = I40IW_LEVEL_2;
	pble_rsrc->stats_lvl2++;
	वापस 0;
 error:
	मुक्त_lvl2(pble_rsrc, palloc);
	वापस I40IW_ERR_NO_MEMORY;
पूर्ण

/**
 * get_lvl1_pble - get level 1 pble resource
 * @dev: hardware control device काष्ठाure
 * @pble_rsrc: pble resource management
 * @palloc: level 1 pble allocation
 */
अटल क्रमागत i40iw_status_code get_lvl1_pble(काष्ठा i40iw_sc_dev *dev,
					    काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc,
					    काष्ठा i40iw_pble_alloc *palloc)
अणु
	u64 *addr;
	काष्ठा gen_pool *pool;
	काष्ठा i40iw_pble_info *lvl1 = &palloc->level1;

	pool = pble_rsrc->pinfo.pool;
	addr = (u64 *)gen_pool_alloc(pool, (palloc->total_cnt << 3));

	अगर (!addr)
		वापस I40IW_ERR_NO_MEMORY;

	palloc->level = I40IW_LEVEL_1;
	lvl1->addr = (अचिन्हित दीर्घ)addr;
	lvl1->idx = fpm_to_idx(pble_rsrc, (u64)gen_pool_virt_to_phys(pool,
			       (अचिन्हित दीर्घ)addr));
	lvl1->cnt = palloc->total_cnt;
	pble_rsrc->stats_lvl1++;
	वापस 0;
पूर्ण

/**
 * get_lvl1_lvl2_pble - calls get_lvl1 and get_lvl2 pble routine
 * @dev: i40iw_sc_dev काष्ठा
 * @pble_rsrc:	pble resources
 * @palloc: contains all inक्रमamtion regarding pble (idx + pble addr)
 * @pool: poपूर्णांकer to general purpose special memory pool descriptor
 */
अटल अंतरभूत क्रमागत i40iw_status_code get_lvl1_lvl2_pble(काष्ठा i40iw_sc_dev *dev,
							काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc,
							काष्ठा i40iw_pble_alloc *palloc,
							काष्ठा gen_pool *pool)
अणु
	क्रमागत i40iw_status_code status = 0;

	status = get_lvl1_pble(dev, pble_rsrc, palloc);
	अगर (status && (palloc->total_cnt > PBLE_PER_PAGE))
		status = get_lvl2_pble(pble_rsrc, palloc, pool);
	वापस status;
पूर्ण

/**
 * i40iw_get_pble - allocate pbles from the pool
 * @dev: i40iw_sc_dev काष्ठा
 * @pble_rsrc:	pble resources
 * @palloc: contains all inक्रमamtion regarding pble (idx + pble addr)
 * @pble_cnt: #of pbles requested
 */
क्रमागत i40iw_status_code i40iw_get_pble(काष्ठा i40iw_sc_dev *dev,
				      काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc,
				      काष्ठा i40iw_pble_alloc *palloc,
				      u32 pble_cnt)
अणु
	काष्ठा gen_pool *pool;
	क्रमागत i40iw_status_code status = 0;
	u32 max_sds = 0;
	पूर्णांक i;

	pool = pble_rsrc->pinfo.pool;
	palloc->total_cnt = pble_cnt;
	palloc->level = I40IW_LEVEL_0;
	/*check first to see अगर we can get pble's without acquiring additional sd's */
	status = get_lvl1_lvl2_pble(dev, pble_rsrc, palloc, pool);
	अगर (!status)
		जाओ निकास;
	max_sds = (palloc->total_cnt >> 18) + 1;
	क्रम (i = 0; i < max_sds; i++) अणु
		status = add_pble_pool(dev, pble_rsrc);
		अगर (status)
			अवरोध;
		status = get_lvl1_lvl2_pble(dev, pble_rsrc, palloc, pool);
		अगर (!status)
			अवरोध;
	पूर्ण
निकास:
	अगर (!status)
		pble_rsrc->stats_alloc_ok++;
	अन्यथा
		pble_rsrc->stats_alloc_fail++;

	वापस status;
पूर्ण

/**
 * i40iw_मुक्त_pble - put pbles back पूर्णांकo pool
 * @pble_rsrc:	pble resources
 * @palloc: contains all inक्रमamtion regarding pble resource being मुक्तd
 */
व्योम i40iw_मुक्त_pble(काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc,
		     काष्ठा i40iw_pble_alloc *palloc)
अणु
	काष्ठा gen_pool *pool;

	pool = pble_rsrc->pinfo.pool;
	अगर (palloc->level == I40IW_LEVEL_2)
		मुक्त_lvl2(pble_rsrc, palloc);
	अन्यथा
		gen_pool_मुक्त(pool, palloc->level1.addr,
			      (palloc->level1.cnt << 3));
	pble_rsrc->stats_alloc_मुक्तd++;
पूर्ण
