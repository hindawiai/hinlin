<शैली गुरु>
/*
 * libcxgb_ppm.c: Chelsio common library क्रम T3/T4/T5 iSCSI PagePod Manager
 *
 * Copyright (c) 2016 Chelsio Communications, Inc. All rights reserved.
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
 *
 * Written by: Karen Xie (kxie@chelsio.com)
 */

#घोषणा DRV_NAME "libcxgb"
#घोषणा pr_fmt(fmt) DRV_NAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/export.h>
#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/pci.h>
#समावेश <linux/scatterlist.h>

#समावेश "libcxgb_ppm.h"

/* Direct Data Placement -
 * Directly place the iSCSI Data-In or Data-Out PDU's payload पूर्णांकo
 * pre-posted final destination host-memory buffers based on the
 * Initiator Task Tag (ITT) in Data-In or Target Task Tag (TTT)
 * in Data-Out PDUs. The host memory address is programmed पूर्णांकo
 * h/w in the क्रमmat of pagepod entries. The location of the
 * pagepod entry is encoded पूर्णांकo ddp tag which is used as the base
 * क्रम ITT/TTT.
 */

/* Direct-Data Placement page size adjusपंचांगent
 */
पूर्णांक cxgbi_ppm_find_page_index(काष्ठा cxgbi_ppm *ppm, अचिन्हित दीर्घ pgsz)
अणु
	काष्ठा cxgbi_tag_क्रमmat *tक्रमmat = &ppm->tक्रमmat;
	पूर्णांक i;

	क्रम (i = 0; i < DDP_PGIDX_MAX; i++) अणु
		अगर (pgsz == 1UL << (DDP_PGSZ_BASE_SHIFT +
					 tक्रमmat->pgsz_order[i])) अणु
			pr_debug("%s: %s ppm, pgsz %lu -> idx %d.\n",
				 __func__, ppm->ndev->name, pgsz, i);
			वापस i;
		पूर्ण
	पूर्ण
	pr_info("ippm: ddp page size %lu not supported.\n", pgsz);
	वापस DDP_PGIDX_MAX;
पूर्ण

/* DDP setup & tearकरोwn
 */
अटल पूर्णांक ppm_find_unused_entries(अचिन्हित दीर्घ *bmap,
				   अचिन्हित पूर्णांक max_ppods,
				   अचिन्हित पूर्णांक start,
				   अचिन्हित पूर्णांक nr,
				   अचिन्हित पूर्णांक align_mask)
अणु
	अचिन्हित दीर्घ i;

	i = biपंचांगap_find_next_zero_area(bmap, max_ppods, start, nr, align_mask);

	अगर (unlikely(i >= max_ppods) && (start > nr))
		i = biपंचांगap_find_next_zero_area(bmap, max_ppods, 0, start - 1,
					       align_mask);
	अगर (unlikely(i >= max_ppods))
		वापस -ENOSPC;

	biपंचांगap_set(bmap, i, nr);
	वापस (पूर्णांक)i;
पूर्ण

अटल व्योम ppm_mark_entries(काष्ठा cxgbi_ppm *ppm, पूर्णांक i, पूर्णांक count,
			     अचिन्हित दीर्घ caller_data)
अणु
	काष्ठा cxgbi_ppod_data *pdata = ppm->ppod_data + i;

	pdata->caller_data = caller_data;
	pdata->npods = count;

	अगर (pdata->color == ((1 << PPOD_IDX_SHIFT) - 1))
		pdata->color = 0;
	अन्यथा
		pdata->color++;
पूर्ण

अटल पूर्णांक ppm_get_cpu_entries(काष्ठा cxgbi_ppm *ppm, अचिन्हित पूर्णांक count,
			       अचिन्हित दीर्घ caller_data)
अणु
	काष्ठा cxgbi_ppm_pool *pool;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक i;

	अगर (!ppm->pool)
		वापस -EINVAL;

	cpu = get_cpu();
	pool = per_cpu_ptr(ppm->pool, cpu);
	spin_lock_bh(&pool->lock);
	put_cpu();

	i = ppm_find_unused_entries(pool->bmap, ppm->pool_index_max,
				    pool->next, count, 0);
	अगर (i < 0) अणु
		pool->next = 0;
		spin_unlock_bh(&pool->lock);
		वापस -ENOSPC;
	पूर्ण

	pool->next = i + count;
	अगर (pool->next >= ppm->pool_index_max)
		pool->next = 0;

	spin_unlock_bh(&pool->lock);

	pr_debug("%s: cpu %u, idx %d + %d (%d), next %u.\n",
		 __func__, cpu, i, count, i + cpu * ppm->pool_index_max,
		pool->next);

	i += cpu * ppm->pool_index_max;
	ppm_mark_entries(ppm, i, count, caller_data);

	वापस i;
पूर्ण

अटल पूर्णांक ppm_get_entries(काष्ठा cxgbi_ppm *ppm, अचिन्हित पूर्णांक count,
			   अचिन्हित दीर्घ caller_data)
अणु
	पूर्णांक i;

	spin_lock_bh(&ppm->map_lock);
	i = ppm_find_unused_entries(ppm->ppod_bmap, ppm->bmap_index_max,
				    ppm->next, count, 0);
	अगर (i < 0) अणु
		ppm->next = 0;
		spin_unlock_bh(&ppm->map_lock);
		pr_debug("ippm: NO suitable entries %u available.\n",
			 count);
		वापस -ENOSPC;
	पूर्ण

	ppm->next = i + count;
	अगर (ppm->max_index_in_edram && (ppm->next >= ppm->max_index_in_edram))
		ppm->next = 0;
	अन्यथा अगर (ppm->next >= ppm->bmap_index_max)
		ppm->next = 0;

	spin_unlock_bh(&ppm->map_lock);

	pr_debug("%s: idx %d + %d (%d), next %u, caller_data 0x%lx.\n",
		 __func__, i, count, i + ppm->pool_rsvd, ppm->next,
		 caller_data);

	i += ppm->pool_rsvd;
	ppm_mark_entries(ppm, i, count, caller_data);

	वापस i;
पूर्ण

अटल व्योम ppm_unmark_entries(काष्ठा cxgbi_ppm *ppm, पूर्णांक i, पूर्णांक count)
अणु
	pr_debug("%s: idx %d + %d.\n", __func__, i, count);

	अगर (i < ppm->pool_rsvd) अणु
		अचिन्हित पूर्णांक cpu;
		काष्ठा cxgbi_ppm_pool *pool;

		cpu = i / ppm->pool_index_max;
		i %= ppm->pool_index_max;

		pool = per_cpu_ptr(ppm->pool, cpu);
		spin_lock_bh(&pool->lock);
		biपंचांगap_clear(pool->bmap, i, count);

		अगर (i < pool->next)
			pool->next = i;
		spin_unlock_bh(&pool->lock);

		pr_debug("%s: cpu %u, idx %d, next %u.\n",
			 __func__, cpu, i, pool->next);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&ppm->map_lock);

		i -= ppm->pool_rsvd;
		biपंचांगap_clear(ppm->ppod_bmap, i, count);

		अगर (i < ppm->next)
			ppm->next = i;
		spin_unlock_bh(&ppm->map_lock);

		pr_debug("%s: idx %d, next %u.\n", __func__, i, ppm->next);
	पूर्ण
पूर्ण

व्योम cxgbi_ppm_ppod_release(काष्ठा cxgbi_ppm *ppm, u32 idx)
अणु
	काष्ठा cxgbi_ppod_data *pdata;

	अगर (idx >= ppm->ppmax) अणु
		pr_warn("ippm: idx too big %u > %u.\n", idx, ppm->ppmax);
		वापस;
	पूर्ण

	pdata = ppm->ppod_data + idx;
	अगर (!pdata->npods) अणु
		pr_warn("ippm: idx %u, npods 0.\n", idx);
		वापस;
	पूर्ण

	pr_debug("release idx %u, npods %u.\n", idx, pdata->npods);
	ppm_unmark_entries(ppm, idx, pdata->npods);
पूर्ण
EXPORT_SYMBOL(cxgbi_ppm_ppod_release);

पूर्णांक cxgbi_ppm_ppods_reserve(काष्ठा cxgbi_ppm *ppm, अचिन्हित लघु nr_pages,
			    u32 per_tag_pg_idx, u32 *ppod_idx,
			    u32 *ddp_tag, अचिन्हित दीर्घ caller_data)
अणु
	काष्ठा cxgbi_ppod_data *pdata;
	अचिन्हित पूर्णांक npods;
	पूर्णांक idx = -1;
	अचिन्हित पूर्णांक hwidx;
	u32 tag;

	npods = (nr_pages + PPOD_PAGES_MAX - 1) >> PPOD_PAGES_SHIFT;
	अगर (!npods) अणु
		pr_warn("%s: pages %u -> npods %u, full.\n",
			__func__, nr_pages, npods);
		वापस -EINVAL;
	पूर्ण

	/* grab from cpu pool first */
	idx = ppm_get_cpu_entries(ppm, npods, caller_data);
	/* try the general pool */
	अगर (idx < 0)
		idx = ppm_get_entries(ppm, npods, caller_data);
	अगर (idx < 0) अणु
		pr_debug("ippm: pages %u, nospc %u, nxt %u, 0x%lx.\n",
			 nr_pages, npods, ppm->next, caller_data);
		वापस idx;
	पूर्ण

	pdata = ppm->ppod_data + idx;
	hwidx = ppm->base_idx + idx;

	tag = cxgbi_ppm_make_ddp_tag(hwidx, pdata->color);

	अगर (per_tag_pg_idx)
		tag |= (per_tag_pg_idx << 30) & 0xC0000000;

	*ppod_idx = idx;
	*ddp_tag = tag;

	pr_debug("ippm: sg %u, tag 0x%x(%u,%u), data 0x%lx.\n",
		 nr_pages, tag, idx, npods, caller_data);

	वापस npods;
पूर्ण
EXPORT_SYMBOL(cxgbi_ppm_ppods_reserve);

व्योम cxgbi_ppm_make_ppod_hdr(काष्ठा cxgbi_ppm *ppm, u32 tag,
			     अचिन्हित पूर्णांक tid, अचिन्हित पूर्णांक offset,
			     अचिन्हित पूर्णांक length,
			     काष्ठा cxgbi_pagepod_hdr *hdr)
अणु
	/* The ddp tag in pagepod should be with bit 31:30 set to 0.
	 * The ddp Tag on the wire should be with non-zero 31:30 to the peer
	 */
	tag &= 0x3FFFFFFF;

	hdr->vld_tid = htonl(PPOD_VALID_FLAG | PPOD_TID(tid));

	hdr->rsvd = 0;
	hdr->pgsz_tag_clr = htonl(tag & ppm->tक्रमmat.idx_clr_mask);
	hdr->max_offset = htonl(length);
	hdr->page_offset = htonl(offset);

	pr_debug("ippm: tag 0x%x, tid 0x%x, xfer %u, off %u.\n",
		 tag, tid, length, offset);
पूर्ण
EXPORT_SYMBOL(cxgbi_ppm_make_ppod_hdr);

अटल व्योम ppm_मुक्त(काष्ठा cxgbi_ppm *ppm)
अणु
	vमुक्त(ppm);
पूर्ण

अटल व्योम ppm_destroy(काष्ठा kref *kref)
अणु
	काष्ठा cxgbi_ppm *ppm = container_of(kref,
					     काष्ठा cxgbi_ppm,
					     refcnt);
	pr_info("ippm: kref 0, destroy %s ppm 0x%p.\n",
		ppm->ndev->name, ppm);

	*ppm->ppm_pp = शून्य;

	मुक्त_percpu(ppm->pool);
	ppm_मुक्त(ppm);
पूर्ण

पूर्णांक cxgbi_ppm_release(काष्ठा cxgbi_ppm *ppm)
अणु
	अगर (ppm) अणु
		पूर्णांक rv;

		rv = kref_put(&ppm->refcnt, ppm_destroy);
		वापस rv;
	पूर्ण
	वापस 1;
पूर्ण
EXPORT_SYMBOL(cxgbi_ppm_release);

अटल काष्ठा cxgbi_ppm_pool *ppm_alloc_cpu_pool(अचिन्हित पूर्णांक *total,
						 अचिन्हित पूर्णांक *pcpu_ppmax)
अणु
	काष्ठा cxgbi_ppm_pool *pools;
	अचिन्हित पूर्णांक ppmax = (*total) / num_possible_cpus();
	अचिन्हित पूर्णांक max = (PCPU_MIN_UNIT_SIZE - माप(*pools)) << 3;
	अचिन्हित पूर्णांक bmap;
	अचिन्हित पूर्णांक alloc_sz;
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित पूर्णांक cpu;

	/* make sure per cpu pool fits पूर्णांकo PCPU_MIN_UNIT_SIZE */
	अगर (ppmax > max)
		ppmax = max;

	/* pool size must be multiple of अचिन्हित दीर्घ */
	bmap = ppmax / BITS_PER_TYPE(अचिन्हित दीर्घ);
	अगर (!bmap)
		वापस शून्य;

	ppmax = (bmap * माप(अचिन्हित दीर्घ)) << 3;

	alloc_sz = माप(*pools) + माप(अचिन्हित दीर्घ) * bmap;
	pools = __alloc_percpu(alloc_sz, __alignof__(काष्ठा cxgbi_ppm_pool));

	अगर (!pools)
		वापस शून्य;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा cxgbi_ppm_pool *ppool = per_cpu_ptr(pools, cpu);

		स_रखो(ppool, 0, alloc_sz);
		spin_lock_init(&ppool->lock);
		count += ppmax;
	पूर्ण

	*total = count;
	*pcpu_ppmax = ppmax;

	वापस pools;
पूर्ण

पूर्णांक cxgbi_ppm_init(व्योम **ppm_pp, काष्ठा net_device *ndev,
		   काष्ठा pci_dev *pdev, व्योम *lldev,
		   काष्ठा cxgbi_tag_क्रमmat *tक्रमmat, अचिन्हित पूर्णांक iscsi_size,
		   अचिन्हित पूर्णांक llimit, अचिन्हित पूर्णांक start,
		   अचिन्हित पूर्णांक reserve_factor, अचिन्हित पूर्णांक iscsi_edram_start,
		   अचिन्हित पूर्णांक iscsi_edram_size)
अणु
	काष्ठा cxgbi_ppm *ppm = (काष्ठा cxgbi_ppm *)(*ppm_pp);
	काष्ठा cxgbi_ppm_pool *pool = शून्य;
	अचिन्हित पूर्णांक pool_index_max = 0;
	अचिन्हित पूर्णांक ppmax_pool = 0;
	अचिन्हित पूर्णांक ppod_bmap_size;
	अचिन्हित पूर्णांक alloc_sz;
	अचिन्हित पूर्णांक ppmax;

	अगर (!iscsi_edram_start)
		iscsi_edram_size = 0;

	अगर (iscsi_edram_size &&
	    ((iscsi_edram_start + iscsi_edram_size) != start)) अणु
		pr_err("iscsi ppod region not contiguous: EDRAM start 0x%x "
			"size 0x%x DDR start 0x%x\n",
			iscsi_edram_start, iscsi_edram_size, start);
		वापस -EINVAL;
	पूर्ण

	अगर (iscsi_edram_size) अणु
		reserve_factor = 0;
		start = iscsi_edram_start;
	पूर्ण

	ppmax = (iscsi_edram_size + iscsi_size) >> PPOD_SIZE_SHIFT;

	अगर (ppm) अणु
		pr_info("ippm: %s, ppm 0x%p,0x%p already initialized, %u/%u.\n",
			ndev->name, ppm_pp, ppm, ppm->ppmax, ppmax);
		kref_get(&ppm->refcnt);
		वापस 1;
	पूर्ण

	अगर (reserve_factor) अणु
		ppmax_pool = ppmax / reserve_factor;
		pool = ppm_alloc_cpu_pool(&ppmax_pool, &pool_index_max);
		अगर (!pool) अणु
			ppmax_pool = 0;
			reserve_factor = 0;
		पूर्ण

		pr_debug("%s: ppmax %u, cpu total %u, per cpu %u.\n",
			 ndev->name, ppmax, ppmax_pool, pool_index_max);
	पूर्ण

	ppod_bmap_size = BITS_TO_LONGS(ppmax - ppmax_pool);
	alloc_sz = माप(काष्ठा cxgbi_ppm) +
			ppmax * (माप(काष्ठा cxgbi_ppod_data)) +
			ppod_bmap_size * माप(अचिन्हित दीर्घ);

	ppm = vzalloc(alloc_sz);
	अगर (!ppm)
		जाओ release_ppm_pool;

	ppm->ppod_bmap = (अचिन्हित दीर्घ *)(&ppm->ppod_data[ppmax]);

	अगर ((ppod_bmap_size >> 3) > (ppmax - ppmax_pool)) अणु
		अचिन्हित पूर्णांक start = ppmax - ppmax_pool;
		अचिन्हित पूर्णांक end = ppod_bmap_size >> 3;

		biपंचांगap_set(ppm->ppod_bmap, ppmax, end - start);
		pr_info("%s: %u - %u < %u * 8, mask extra bits %u, %u.\n",
			__func__, ppmax, ppmax_pool, ppod_bmap_size, start,
			end);
	पूर्ण
	अगर (iscsi_edram_size) अणु
		अचिन्हित पूर्णांक first_ddr_idx =
				iscsi_edram_size >> PPOD_SIZE_SHIFT;

		ppm->max_index_in_edram = first_ddr_idx - 1;
		biपंचांगap_set(ppm->ppod_bmap, first_ddr_idx, 1);
		pr_debug("reserved %u ppod in bitmap\n", first_ddr_idx);
	पूर्ण

	spin_lock_init(&ppm->map_lock);
	kref_init(&ppm->refcnt);

	स_नकल(&ppm->tक्रमmat, tक्रमmat, माप(काष्ठा cxgbi_tag_क्रमmat));

	ppm->ppm_pp = ppm_pp;
	ppm->ndev = ndev;
	ppm->pdev = pdev;
	ppm->lldev = lldev;
	ppm->ppmax = ppmax;
	ppm->next = 0;
	ppm->llimit = llimit;
	ppm->base_idx = start > llimit ?
			(start - llimit + 1) >> PPOD_SIZE_SHIFT : 0;
	ppm->bmap_index_max = ppmax - ppmax_pool;

	ppm->pool = pool;
	ppm->pool_rsvd = ppmax_pool;
	ppm->pool_index_max = pool_index_max;

	/* check one more समय */
	अगर (*ppm_pp) अणु
		ppm_मुक्त(ppm);
		ppm = (काष्ठा cxgbi_ppm *)(*ppm_pp);

		pr_info("ippm: %s, ppm 0x%p,0x%p already initialized, %u/%u.\n",
			ndev->name, ppm_pp, *ppm_pp, ppm->ppmax, ppmax);

		kref_get(&ppm->refcnt);
		वापस 1;
	पूर्ण
	*ppm_pp = ppm;

	ppm->tक्रमmat.pgsz_idx_dflt = cxgbi_ppm_find_page_index(ppm, PAGE_SIZE);

	pr_info("ippm %s: ppm 0x%p, 0x%p, base %u/%u, pg %lu,%u, rsvd %u,%u.\n",
		ndev->name, ppm_pp, ppm, ppm->base_idx, ppm->ppmax, PAGE_SIZE,
		ppm->tक्रमmat.pgsz_idx_dflt, ppm->pool_rsvd,
		ppm->pool_index_max);

	वापस 0;

release_ppm_pool:
	मुक्त_percpu(pool);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(cxgbi_ppm_init);

अचिन्हित पूर्णांक cxgbi_tagmask_set(अचिन्हित पूर्णांक ppmax)
अणु
	अचिन्हित पूर्णांक bits = fls(ppmax);

	अगर (bits > PPOD_IDX_MAX_SIZE)
		bits = PPOD_IDX_MAX_SIZE;

	pr_info("ippm: ppmax %u/0x%x -> bits %u, tagmask 0x%x.\n",
		ppmax, ppmax, bits, 1 << (bits + PPOD_IDX_SHIFT));

	वापस 1 << (bits + PPOD_IDX_SHIFT);
पूर्ण
EXPORT_SYMBOL(cxgbi_tagmask_set);

MODULE_AUTHOR("Chelsio Communications");
MODULE_DESCRIPTION("Chelsio common library");
MODULE_LICENSE("Dual BSD/GPL");
