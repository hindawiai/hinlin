<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SN Platक्रमm GRU Driver
 *
 *              FAULT HANDLER FOR GRU DETECTED TLB MISSES
 *
 * This file contains code that handles TLB misses within the GRU.
 * These misses are reported either via पूर्णांकerrupts or user polling of
 * the user CB.
 *
 *  Copyright (c) 2008 Silicon Graphics, Inc.  All Rights Reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/security.h>
#समावेश <linux/sync_core.h>
#समावेश <linux/prefetch.h>
#समावेश "gru.h"
#समावेश "grutables.h"
#समावेश "grulib.h"
#समावेश "gru_instructions.h"
#समावेश <यंत्र/uv/uv_hub.h>

/* Return codes क्रम vtop functions */
#घोषणा VTOP_SUCCESS               0
#घोषणा VTOP_INVALID               -1
#घोषणा VTOP_RETRY                 -2


/*
 * Test अगर a physical address is a valid GRU GSEG address
 */
अटल अंतरभूत पूर्णांक is_gru_paddr(अचिन्हित दीर्घ paddr)
अणु
	वापस paddr >= gru_start_paddr && paddr < gru_end_paddr;
पूर्ण

/*
 * Find the vma of a GRU segment. Caller must hold mmap_lock.
 */
काष्ठा vm_area_काष्ठा *gru_find_vma(अचिन्हित दीर्घ vaddr)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	vma = find_vma(current->mm, vaddr);
	अगर (vma && vma->vm_start <= vaddr && vma->vm_ops == &gru_vm_ops)
		वापस vma;
	वापस शून्य;
पूर्ण

/*
 * Find and lock the gts that contains the specअगरied user vaddr.
 *
 * Returns:
 * 	- *gts with the mmap_lock locked क्रम पढ़ो and the GTS locked.
 *	- शून्य अगर vaddr invalid OR is not a valid GSEG vaddr.
 */

अटल काष्ठा gru_thपढ़ो_state *gru_find_lock_gts(अचिन्हित दीर्घ vaddr)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा gru_thपढ़ो_state *gts = शून्य;

	mmap_पढ़ो_lock(mm);
	vma = gru_find_vma(vaddr);
	अगर (vma)
		gts = gru_find_thपढ़ो_state(vma, TSID(vaddr, vma));
	अगर (gts)
		mutex_lock(&gts->ts_ctxlock);
	अन्यथा
		mmap_पढ़ो_unlock(mm);
	वापस gts;
पूर्ण

अटल काष्ठा gru_thपढ़ो_state *gru_alloc_locked_gts(अचिन्हित दीर्घ vaddr)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा gru_thपढ़ो_state *gts = ERR_PTR(-EINVAL);

	mmap_ग_लिखो_lock(mm);
	vma = gru_find_vma(vaddr);
	अगर (!vma)
		जाओ err;

	gts = gru_alloc_thपढ़ो_state(vma, TSID(vaddr, vma));
	अगर (IS_ERR(gts))
		जाओ err;
	mutex_lock(&gts->ts_ctxlock);
	mmap_ग_लिखो_करोwngrade(mm);
	वापस gts;

err:
	mmap_ग_लिखो_unlock(mm);
	वापस gts;
पूर्ण

/*
 * Unlock a GTS that was previously locked with gru_find_lock_gts().
 */
अटल व्योम gru_unlock_gts(काष्ठा gru_thपढ़ो_state *gts)
अणु
	mutex_unlock(&gts->ts_ctxlock);
	mmap_पढ़ो_unlock(current->mm);
पूर्ण

/*
 * Set a CB.istatus to active using a user भव address. This must be करोne
 * just prior to a TFH RESTART. The new cb.istatus is an in-cache status ONLY.
 * If the line is evicted, the status may be lost. The in-cache update
 * is necessary to prevent the user from seeing a stale cb.istatus that will
 * change as soon as the TFH restart is complete. Races may cause an
 * occasional failure to clear the cb.istatus, but that is ok.
 */
अटल व्योम gru_cb_set_istatus_active(काष्ठा gru_inकाष्ठाion_bits *cbk)
अणु
	अगर (cbk) अणु
		cbk->istatus = CBS_ACTIVE;
	पूर्ण
पूर्ण

/*
 * Read & clear a TFM
 *
 * The GRU has an array of fault maps. A map is निजी to a cpu
 * Only one cpu will be accessing a cpu's fault map.
 *
 * This function scans the cpu-निजी fault map & clears all bits that
 * are set. The function वापसs a biपंचांगap that indicates the bits that
 * were cleared. Note that sense the maps may be updated asynchronously by
 * the GRU, atomic operations must be used to clear bits.
 */
अटल व्योम get_clear_fault_map(काष्ठा gru_state *gru,
				काष्ठा gru_tlb_fault_map *imap,
				काष्ठा gru_tlb_fault_map *dmap)
अणु
	अचिन्हित दीर्घ i, k;
	काष्ठा gru_tlb_fault_map *tfm;

	tfm = get_tfm_क्रम_cpu(gru, gru_cpu_fault_map_id());
	prefetchw(tfm);		/* Helps on hardware, required क्रम emulator */
	क्रम (i = 0; i < BITS_TO_LONGS(GRU_NUM_CBE); i++) अणु
		k = tfm->fault_bits[i];
		अगर (k)
			k = xchg(&tfm->fault_bits[i], 0UL);
		imap->fault_bits[i] = k;
		k = tfm->करोne_bits[i];
		अगर (k)
			k = xchg(&tfm->करोne_bits[i], 0UL);
		dmap->fault_bits[i] = k;
	पूर्ण

	/*
	 * Not functionally required but helps perक्रमmance. (Required
	 * on emulator)
	 */
	gru_flush_cache(tfm);
पूर्ण

/*
 * Atomic (पूर्णांकerrupt context) & non-atomic (user context) functions to
 * convert a vaddr पूर्णांकo a physical address. The size of the page
 * is वापसed in pageshअगरt.
 * 	वापसs:
 * 		  0 - successful
 * 		< 0 - error code
 * 		  1 - (atomic only) try again in non-atomic context
 */
अटल पूर्णांक non_atomic_pte_lookup(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ vaddr, पूर्णांक ग_लिखो,
				 अचिन्हित दीर्घ *paddr, पूर्णांक *pageshअगरt)
अणु
	काष्ठा page *page;

#अगर_घोषित CONFIG_HUGETLB_PAGE
	*pageshअगरt = is_vm_hugetlb_page(vma) ? HPAGE_SHIFT : PAGE_SHIFT;
#अन्यथा
	*pageshअगरt = PAGE_SHIFT;
#पूर्ण_अगर
	अगर (get_user_pages(vaddr, 1, ग_लिखो ? FOLL_WRITE : 0, &page, शून्य) <= 0)
		वापस -EFAULT;
	*paddr = page_to_phys(page);
	put_page(page);
	वापस 0;
पूर्ण

/*
 * atomic_pte_lookup
 *
 * Convert a user भव address to a physical address
 * Only supports Intel large pages (2MB only) on x86_64.
 *	ZZZ - hugepage support is incomplete
 *
 * NOTE: mmap_lock is alपढ़ोy held on entry to this function. This
 * guarantees existence of the page tables.
 */
अटल पूर्णांक atomic_pte_lookup(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vaddr,
	पूर्णांक ग_लिखो, अचिन्हित दीर्घ *paddr, पूर्णांक *pageshअगरt)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t pte;

	pgdp = pgd_offset(vma->vm_mm, vaddr);
	अगर (unlikely(pgd_none(*pgdp)))
		जाओ err;

	p4dp = p4d_offset(pgdp, vaddr);
	अगर (unlikely(p4d_none(*p4dp)))
		जाओ err;

	pudp = pud_offset(p4dp, vaddr);
	अगर (unlikely(pud_none(*pudp)))
		जाओ err;

	pmdp = pmd_offset(pudp, vaddr);
	अगर (unlikely(pmd_none(*pmdp)))
		जाओ err;
#अगर_घोषित CONFIG_X86_64
	अगर (unlikely(pmd_large(*pmdp)))
		pte = *(pte_t *) pmdp;
	अन्यथा
#पूर्ण_अगर
		pte = *pte_offset_kernel(pmdp, vaddr);

	अगर (unlikely(!pte_present(pte) ||
		     (ग_लिखो && (!pte_ग_लिखो(pte) || !pte_dirty(pte)))))
		वापस 1;

	*paddr = pte_pfn(pte) << PAGE_SHIFT;
#अगर_घोषित CONFIG_HUGETLB_PAGE
	*pageshअगरt = is_vm_hugetlb_page(vma) ? HPAGE_SHIFT : PAGE_SHIFT;
#अन्यथा
	*pageshअगरt = PAGE_SHIFT;
#पूर्ण_अगर
	वापस 0;

err:
	वापस 1;
पूर्ण

अटल पूर्णांक gru_vtop(काष्ठा gru_thपढ़ो_state *gts, अचिन्हित दीर्घ vaddr,
		    पूर्णांक ग_लिखो, पूर्णांक atomic, अचिन्हित दीर्घ *gpa, पूर्णांक *pageshअगरt)
अणु
	काष्ठा mm_काष्ठा *mm = gts->ts_mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ paddr;
	पूर्णांक ret, ps;

	vma = find_vma(mm, vaddr);
	अगर (!vma)
		जाओ inval;

	/*
	 * Atomic lookup is faster & usually works even अगर called in non-atomic
	 * context.
	 */
	rmb();	/* Must/check ms_range_active beक्रमe loading PTEs */
	ret = atomic_pte_lookup(vma, vaddr, ग_लिखो, &paddr, &ps);
	अगर (ret) अणु
		अगर (atomic)
			जाओ upm;
		अगर (non_atomic_pte_lookup(vma, vaddr, ग_लिखो, &paddr, &ps))
			जाओ inval;
	पूर्ण
	अगर (is_gru_paddr(paddr))
		जाओ inval;
	paddr = paddr & ~((1UL << ps) - 1);
	*gpa = uv_soc_phys_ram_to_gpa(paddr);
	*pageshअगरt = ps;
	वापस VTOP_SUCCESS;

inval:
	वापस VTOP_INVALID;
upm:
	वापस VTOP_RETRY;
पूर्ण


/*
 * Flush a CBE from cache. The CBE is clean in the cache. Dirty the
 * CBE cacheline so that the line will be written back to home agent.
 * Otherwise the line may be silently dropped. This has no impact
 * except on perक्रमmance.
 */
अटल व्योम gru_flush_cache_cbe(काष्ठा gru_control_block_extended *cbe)
अणु
	अगर (unlikely(cbe)) अणु
		cbe->cbrexecstatus = 0;         /* make CL dirty */
		gru_flush_cache(cbe);
	पूर्ण
पूर्ण

/*
 * Preload the TLB with entries that may be required. Currently, preloading
 * is implemented only क्रम BCOPY. Preload  <tlb_preload_count> pages OR to
 * the end of the bcopy tranfer, whichever is smaller.
 */
अटल व्योम gru_preload_tlb(काष्ठा gru_state *gru,
			काष्ठा gru_thपढ़ो_state *gts, पूर्णांक atomic,
			अचिन्हित दीर्घ fault_vaddr, पूर्णांक asid, पूर्णांक ग_लिखो,
			अचिन्हित अक्षर tlb_preload_count,
			काष्ठा gru_tlb_fault_handle *tfh,
			काष्ठा gru_control_block_extended *cbe)
अणु
	अचिन्हित दीर्घ vaddr = 0, gpa;
	पूर्णांक ret, pageshअगरt;

	अगर (cbe->opccpy != OP_BCOPY)
		वापस;

	अगर (fault_vaddr == cbe->cbe_baddr0)
		vaddr = fault_vaddr + GRU_CACHE_LINE_BYTES * cbe->cbe_src_cl - 1;
	अन्यथा अगर (fault_vaddr == cbe->cbe_baddr1)
		vaddr = fault_vaddr + (1 << cbe->xtypecpy) * cbe->cbe_nelemcur - 1;

	fault_vaddr &= PAGE_MASK;
	vaddr &= PAGE_MASK;
	vaddr = min(vaddr, fault_vaddr + tlb_preload_count * PAGE_SIZE);

	जबतक (vaddr > fault_vaddr) अणु
		ret = gru_vtop(gts, vaddr, ग_लिखो, atomic, &gpa, &pageshअगरt);
		अगर (ret || tfh_ग_लिखो_only(tfh, gpa, GAA_RAM, vaddr, asid, ग_लिखो,
					  GRU_PAGESIZE(pageshअगरt)))
			वापस;
		gru_dbg(grudev,
			"%s: gid %d, gts 0x%p, tfh 0x%p, vaddr 0x%lx, asid 0x%x, rw %d, ps %d, gpa 0x%lx\n",
			atomic ? "atomic" : "non-atomic", gru->gs_gid, gts, tfh,
			vaddr, asid, ग_लिखो, pageshअगरt, gpa);
		vaddr -= PAGE_SIZE;
		STAT(tlb_preload_page);
	पूर्ण
पूर्ण

/*
 * Drop a TLB entry पूर्णांकo the GRU. The fault is described by info in an TFH.
 *	Input:
 *		cb    Address of user CBR. Null अगर not running in user context
 * 	Return:
 * 		  0 = dropin, exception, or चयन to UPM successful
 * 		  1 = range invalidate active
 * 		< 0 = error code
 *
 */
अटल पूर्णांक gru_try_dropin(काष्ठा gru_state *gru,
			  काष्ठा gru_thपढ़ो_state *gts,
			  काष्ठा gru_tlb_fault_handle *tfh,
			  काष्ठा gru_inकाष्ठाion_bits *cbk)
अणु
	काष्ठा gru_control_block_extended *cbe = शून्य;
	अचिन्हित अक्षर tlb_preload_count = gts->ts_tlb_preload_count;
	पूर्णांक pageshअगरt = 0, asid, ग_लिखो, ret, atomic = !cbk, indexway;
	अचिन्हित दीर्घ gpa = 0, vaddr = 0;

	/*
	 * NOTE: The GRU contains magic hardware that eliminates races between
	 * TLB invalidates and TLB dropins. If an invalidate occurs
	 * in the winकरोw between पढ़ोing the TFH and the subsequent TLB dropin,
	 * the dropin is ignored. This eliminates the need क्रम additional locks.
	 */

	/*
	 * Prefetch the CBE अगर करोing TLB preloading
	 */
	अगर (unlikely(tlb_preload_count)) अणु
		cbe = gru_tfh_to_cbe(tfh);
		prefetchw(cbe);
	पूर्ण

	/*
	 * Error अगर TFH state is IDLE or FMM mode & the user issuing a UPM call.
	 * Might be a hardware race OR a stupid user. Ignore FMM because FMM
	 * is a transient state.
	 */
	अगर (tfh->status != TFHSTATUS_EXCEPTION) अणु
		gru_flush_cache(tfh);
		sync_core();
		अगर (tfh->status != TFHSTATUS_EXCEPTION)
			जाओ failnoexception;
		STAT(tfh_stale_on_fault);
	पूर्ण
	अगर (tfh->state == TFHSTATE_IDLE)
		जाओ failidle;
	अगर (tfh->state == TFHSTATE_MISS_FMM && cbk)
		जाओ failfmm;

	ग_लिखो = (tfh->cause & TFHCAUSE_TLB_MOD) != 0;
	vaddr = tfh->missvaddr;
	asid = tfh->missasid;
	indexway = tfh->indexway;
	अगर (asid == 0)
		जाओ failnoasid;

	rmb();	/* TFH must be cache resident beक्रमe पढ़ोing ms_range_active */

	/*
	 * TFH is cache resident - at least briefly. Fail the dropin
	 * अगर a range invalidate is active.
	 */
	अगर (atomic_पढ़ो(&gts->ts_gms->ms_range_active))
		जाओ failactive;

	ret = gru_vtop(gts, vaddr, ग_लिखो, atomic, &gpa, &pageshअगरt);
	अगर (ret == VTOP_INVALID)
		जाओ failinval;
	अगर (ret == VTOP_RETRY)
		जाओ failupm;

	अगर (!(gts->ts_sizeavail & GRU_SIZEAVAIL(pageshअगरt))) अणु
		gts->ts_sizeavail |= GRU_SIZEAVAIL(pageshअगरt);
		अगर (atomic || !gru_update_cch(gts)) अणु
			gts->ts_क्रमce_cch_reload = 1;
			जाओ failupm;
		पूर्ण
	पूर्ण

	अगर (unlikely(cbe) && pageshअगरt == PAGE_SHIFT) अणु
		gru_preload_tlb(gru, gts, atomic, vaddr, asid, ग_लिखो, tlb_preload_count, tfh, cbe);
		gru_flush_cache_cbe(cbe);
	पूर्ण

	gru_cb_set_istatus_active(cbk);
	gts->ustats.tlbdropin++;
	tfh_ग_लिखो_restart(tfh, gpa, GAA_RAM, vaddr, asid, ग_लिखो,
			  GRU_PAGESIZE(pageshअगरt));
	gru_dbg(grudev,
		"%s: gid %d, gts 0x%p, tfh 0x%p, vaddr 0x%lx, asid 0x%x, indexway 0x%x,"
		" rw %d, ps %d, gpa 0x%lx\n",
		atomic ? "atomic" : "non-atomic", gru->gs_gid, gts, tfh, vaddr, asid,
		indexway, ग_लिखो, pageshअगरt, gpa);
	STAT(tlb_dropin);
	वापस 0;

failnoasid:
	/* No asid (delayed unload). */
	STAT(tlb_dropin_fail_no_asid);
	gru_dbg(grudev, "FAILED no_asid tfh: 0x%p, vaddr 0x%lx\n", tfh, vaddr);
	अगर (!cbk)
		tfh_user_polling_mode(tfh);
	अन्यथा
		gru_flush_cache(tfh);
	gru_flush_cache_cbe(cbe);
	वापस -EAGAIN;

failupm:
	/* Atomic failure चयन CBR to UPM */
	tfh_user_polling_mode(tfh);
	gru_flush_cache_cbe(cbe);
	STAT(tlb_dropin_fail_upm);
	gru_dbg(grudev, "FAILED upm tfh: 0x%p, vaddr 0x%lx\n", tfh, vaddr);
	वापस 1;

failfmm:
	/* FMM state on UPM call */
	gru_flush_cache(tfh);
	gru_flush_cache_cbe(cbe);
	STAT(tlb_dropin_fail_fmm);
	gru_dbg(grudev, "FAILED fmm tfh: 0x%p, state %d\n", tfh, tfh->state);
	वापस 0;

failnoexception:
	/* TFH status did not show exception pending */
	gru_flush_cache(tfh);
	gru_flush_cache_cbe(cbe);
	अगर (cbk)
		gru_flush_cache(cbk);
	STAT(tlb_dropin_fail_no_exception);
	gru_dbg(grudev, "FAILED non-exception tfh: 0x%p, status %d, state %d\n",
		tfh, tfh->status, tfh->state);
	वापस 0;

failidle:
	/* TFH state was idle  - no miss pending */
	gru_flush_cache(tfh);
	gru_flush_cache_cbe(cbe);
	अगर (cbk)
		gru_flush_cache(cbk);
	STAT(tlb_dropin_fail_idle);
	gru_dbg(grudev, "FAILED idle tfh: 0x%p, state %d\n", tfh, tfh->state);
	वापस 0;

failinval:
	/* All errors (atomic & non-atomic) चयन CBR to EXCEPTION state */
	tfh_exception(tfh);
	gru_flush_cache_cbe(cbe);
	STAT(tlb_dropin_fail_invalid);
	gru_dbg(grudev, "FAILED inval tfh: 0x%p, vaddr 0x%lx\n", tfh, vaddr);
	वापस -EFAULT;

failactive:
	/* Range invalidate active. Switch to UPM अगरf atomic */
	अगर (!cbk)
		tfh_user_polling_mode(tfh);
	अन्यथा
		gru_flush_cache(tfh);
	gru_flush_cache_cbe(cbe);
	STAT(tlb_dropin_fail_range_active);
	gru_dbg(grudev, "FAILED range active: tfh 0x%p, vaddr 0x%lx\n",
		tfh, vaddr);
	वापस 1;
पूर्ण

/*
 * Process an बाह्यal पूर्णांकerrupt from the GRU. This पूर्णांकerrupt is
 * caused by a TLB miss.
 * Note that this is the पूर्णांकerrupt handler that is रेजिस्टरed with linux
 * पूर्णांकerrupt handlers.
 */
अटल irqवापस_t gru_पूर्णांकr(पूर्णांक chiplet, पूर्णांक blade)
अणु
	काष्ठा gru_state *gru;
	काष्ठा gru_tlb_fault_map imap, dmap;
	काष्ठा gru_thपढ़ो_state *gts;
	काष्ठा gru_tlb_fault_handle *tfh = शून्य;
	काष्ठा completion *cmp;
	पूर्णांक cbrnum, ctxnum;

	STAT(पूर्णांकr);

	gru = &gru_base[blade]->bs_grus[chiplet];
	अगर (!gru) अणु
		dev_err(grudev, "GRU: invalid interrupt: cpu %d, chiplet %d\n",
			raw_smp_processor_id(), chiplet);
		वापस IRQ_NONE;
	पूर्ण
	get_clear_fault_map(gru, &imap, &dmap);
	gru_dbg(grudev,
		"cpu %d, chiplet %d, gid %d, imap %016lx %016lx, dmap %016lx %016lx\n",
		smp_processor_id(), chiplet, gru->gs_gid,
		imap.fault_bits[0], imap.fault_bits[1],
		dmap.fault_bits[0], dmap.fault_bits[1]);

	क्रम_each_cbr_in_tfm(cbrnum, dmap.fault_bits) अणु
		STAT(पूर्णांकr_cbr);
		cmp = gru->gs_blade->bs_async_wq;
		अगर (cmp)
			complete(cmp);
		gru_dbg(grudev, "gid %d, cbr_done %d, done %d\n",
			gru->gs_gid, cbrnum, cmp ? cmp->करोne : -1);
	पूर्ण

	क्रम_each_cbr_in_tfm(cbrnum, imap.fault_bits) अणु
		STAT(पूर्णांकr_tfh);
		tfh = get_tfh_by_index(gru, cbrnum);
		prefetchw(tfh);	/* Helps on hdw, required क्रम emulator */

		/*
		 * When hardware sets a bit in the faulपंचांगap, it implicitly
		 * locks the GRU context so that it cannot be unloaded.
		 * The gts cannot change until a TFH start/ग_लिखोstart command
		 * is issued.
		 */
		ctxnum = tfh->ctxnum;
		gts = gru->gs_gts[ctxnum];

		/* Spurious पूर्णांकerrupts can cause this. Ignore. */
		अगर (!gts) अणु
			STAT(पूर्णांकr_spurious);
			जारी;
		पूर्ण

		/*
		 * This is running in पूर्णांकerrupt context. Trylock the mmap_lock.
		 * If it fails, retry the fault in user context.
		 */
		gts->ustats.fmm_tlbmiss++;
		अगर (!gts->ts_क्रमce_cch_reload &&
					mmap_पढ़ो_trylock(gts->ts_mm)) अणु
			gru_try_dropin(gru, gts, tfh, शून्य);
			mmap_पढ़ो_unlock(gts->ts_mm);
		पूर्ण अन्यथा अणु
			tfh_user_polling_mode(tfh);
			STAT(पूर्णांकr_mm_lock_failed);
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t gru0_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस gru_पूर्णांकr(0, uv_numa_blade_id());
पूर्ण

irqवापस_t gru1_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस gru_पूर्णांकr(1, uv_numa_blade_id());
पूर्ण

irqवापस_t gru_पूर्णांकr_mblade(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक blade;

	क्रम_each_possible_blade(blade) अणु
		अगर (uv_blade_nr_possible_cpus(blade))
			जारी;
		gru_पूर्णांकr(0, blade);
		gru_पूर्णांकr(1, blade);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक gru_user_dropin(काष्ठा gru_thपढ़ो_state *gts,
			   काष्ठा gru_tlb_fault_handle *tfh,
			   व्योम *cb)
अणु
	काष्ठा gru_mm_काष्ठा *gms = gts->ts_gms;
	पूर्णांक ret;

	gts->ustats.upm_tlbmiss++;
	जबतक (1) अणु
		रुको_event(gms->ms_रुको_queue,
			   atomic_पढ़ो(&gms->ms_range_active) == 0);
		prefetchw(tfh);	/* Helps on hdw, required क्रम emulator */
		ret = gru_try_dropin(gts->ts_gru, gts, tfh, cb);
		अगर (ret <= 0)
			वापस ret;
		STAT(call_os_रुको_queue);
	पूर्ण
पूर्ण

/*
 * This पूर्णांकerface is called as a result of a user detecting a "call OS" bit
 * in a user CB. Normally means that a TLB fault has occurred.
 * 	cb - user भव address of the CB
 */
पूर्णांक gru_handle_user_call_os(अचिन्हित दीर्घ cb)
अणु
	काष्ठा gru_tlb_fault_handle *tfh;
	काष्ठा gru_thपढ़ो_state *gts;
	व्योम *cbk;
	पूर्णांक ucbnum, cbrnum, ret = -EINVAL;

	STAT(call_os);

	/* sanity check the cb poपूर्णांकer */
	ucbnum = get_cb_number((व्योम *)cb);
	अगर ((cb & (GRU_HANDLE_STRIDE - 1)) || ucbnum >= GRU_NUM_CB)
		वापस -EINVAL;

	gts = gru_find_lock_gts(cb);
	अगर (!gts)
		वापस -EINVAL;
	gru_dbg(grudev, "address 0x%lx, gid %d, gts 0x%p\n", cb, gts->ts_gru ? gts->ts_gru->gs_gid : -1, gts);

	अगर (ucbnum >= gts->ts_cbr_au_count * GRU_CBR_AU_SIZE)
		जाओ निकास;

	gru_check_context_placement(gts);

	/*
	 * CCH may contain stale data अगर ts_क्रमce_cch_reload is set.
	 */
	अगर (gts->ts_gru && gts->ts_क्रमce_cch_reload) अणु
		gts->ts_क्रमce_cch_reload = 0;
		gru_update_cch(gts);
	पूर्ण

	ret = -EAGAIN;
	cbrnum = thपढ़ो_cbr_number(gts, ucbnum);
	अगर (gts->ts_gru) अणु
		tfh = get_tfh_by_index(gts->ts_gru, cbrnum);
		cbk = get_gseg_base_address_cb(gts->ts_gru->gs_gru_base_vaddr,
				gts->ts_ctxnum, ucbnum);
		ret = gru_user_dropin(gts, tfh, cbk);
	पूर्ण
निकास:
	gru_unlock_gts(gts);
	वापस ret;
पूर्ण

/*
 * Fetch the exception detail inक्रमmation क्रम a CB that terminated with
 * an exception.
 */
पूर्णांक gru_get_exception_detail(अचिन्हित दीर्घ arg)
अणु
	काष्ठा control_block_extended_exc_detail excdet;
	काष्ठा gru_control_block_extended *cbe;
	काष्ठा gru_thपढ़ो_state *gts;
	पूर्णांक ucbnum, cbrnum, ret;

	STAT(user_exception);
	अगर (copy_from_user(&excdet, (व्योम __user *)arg, माप(excdet)))
		वापस -EFAULT;

	gts = gru_find_lock_gts(excdet.cb);
	अगर (!gts)
		वापस -EINVAL;

	gru_dbg(grudev, "address 0x%lx, gid %d, gts 0x%p\n", excdet.cb, gts->ts_gru ? gts->ts_gru->gs_gid : -1, gts);
	ucbnum = get_cb_number((व्योम *)excdet.cb);
	अगर (ucbnum >= gts->ts_cbr_au_count * GRU_CBR_AU_SIZE) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अगर (gts->ts_gru) अणु
		cbrnum = thपढ़ो_cbr_number(gts, ucbnum);
		cbe = get_cbe_by_index(gts->ts_gru, cbrnum);
		gru_flush_cache(cbe);	/* CBE not coherent */
		sync_core();		/* make sure we are have current data */
		excdet.opc = cbe->opccpy;
		excdet.exopc = cbe->exopccpy;
		excdet.ecause = cbe->ecause;
		excdet.exceptdet0 = cbe->idef1upd;
		excdet.exceptdet1 = cbe->idef3upd;
		excdet.cbrstate = cbe->cbrstate;
		excdet.cbrexecstatus = cbe->cbrexecstatus;
		gru_flush_cache_cbe(cbe);
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EAGAIN;
	पूर्ण
	gru_unlock_gts(gts);

	gru_dbg(grudev,
		"cb 0x%lx, op %d, exopc %d, cbrstate %d, cbrexecstatus 0x%x, ecause 0x%x, "
		"exdet0 0x%lx, exdet1 0x%x\n",
		excdet.cb, excdet.opc, excdet.exopc, excdet.cbrstate, excdet.cbrexecstatus,
		excdet.ecause, excdet.exceptdet0, excdet.exceptdet1);
	अगर (!ret && copy_to_user((व्योम __user *)arg, &excdet, माप(excdet)))
		ret = -EFAULT;
	वापस ret;
पूर्ण

/*
 * User request to unload a context. Content is saved क्रम possible reload.
 */
अटल पूर्णांक gru_unload_all_contexts(व्योम)
अणु
	काष्ठा gru_thपढ़ो_state *gts;
	काष्ठा gru_state *gru;
	पूर्णांक gid, ctxnum;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	क्रमeach_gid(gid) अणु
		gru = GID_TO_GRU(gid);
		spin_lock(&gru->gs_lock);
		क्रम (ctxnum = 0; ctxnum < GRU_NUM_CCH; ctxnum++) अणु
			gts = gru->gs_gts[ctxnum];
			अगर (gts && mutex_trylock(&gts->ts_ctxlock)) अणु
				spin_unlock(&gru->gs_lock);
				gru_unload_context(gts, 1);
				mutex_unlock(&gts->ts_ctxlock);
				spin_lock(&gru->gs_lock);
			पूर्ण
		पूर्ण
		spin_unlock(&gru->gs_lock);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक gru_user_unload_context(अचिन्हित दीर्घ arg)
अणु
	काष्ठा gru_thपढ़ो_state *gts;
	काष्ठा gru_unload_context_req req;

	STAT(user_unload_context);
	अगर (copy_from_user(&req, (व्योम __user *)arg, माप(req)))
		वापस -EFAULT;

	gru_dbg(grudev, "gseg 0x%lx\n", req.gseg);

	अगर (!req.gseg)
		वापस gru_unload_all_contexts();

	gts = gru_find_lock_gts(req.gseg);
	अगर (!gts)
		वापस -EINVAL;

	अगर (gts->ts_gru)
		gru_unload_context(gts, 1);
	gru_unlock_gts(gts);

	वापस 0;
पूर्ण

/*
 * User request to flush a range of भव addresses from the GRU TLB
 * (Mainly क्रम testing).
 */
पूर्णांक gru_user_flush_tlb(अचिन्हित दीर्घ arg)
अणु
	काष्ठा gru_thपढ़ो_state *gts;
	काष्ठा gru_flush_tlb_req req;
	काष्ठा gru_mm_काष्ठा *gms;

	STAT(user_flush_tlb);
	अगर (copy_from_user(&req, (व्योम __user *)arg, माप(req)))
		वापस -EFAULT;

	gru_dbg(grudev, "gseg 0x%lx, vaddr 0x%lx, len 0x%lx\n", req.gseg,
		req.vaddr, req.len);

	gts = gru_find_lock_gts(req.gseg);
	अगर (!gts)
		वापस -EINVAL;

	gms = gts->ts_gms;
	gru_unlock_gts(gts);
	gru_flush_tlb_range(gms, req.vaddr, req.len);

	वापस 0;
पूर्ण

/*
 * Fetch GSEG statisticss
 */
दीर्घ gru_get_gseg_statistics(अचिन्हित दीर्घ arg)
अणु
	काष्ठा gru_thपढ़ो_state *gts;
	काष्ठा gru_get_gseg_statistics_req req;

	अगर (copy_from_user(&req, (व्योम __user *)arg, माप(req)))
		वापस -EFAULT;

	/*
	 * The library creates arrays of contexts क्रम thपढ़ोed programs.
	 * If no gts exists in the array, the context has never been used & all
	 * statistics are implicitly 0.
	 */
	gts = gru_find_lock_gts(req.gseg);
	अगर (gts) अणु
		स_नकल(&req.stats, &gts->ustats, माप(gts->ustats));
		gru_unlock_gts(gts);
	पूर्ण अन्यथा अणु
		स_रखो(&req.stats, 0, माप(gts->ustats));
	पूर्ण

	अगर (copy_to_user((व्योम __user *)arg, &req, माप(req)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * Register the current task as the user of the GSEG slice.
 * Needed क्रम TLB fault पूर्णांकerrupt targeting.
 */
पूर्णांक gru_set_context_option(अचिन्हित दीर्घ arg)
अणु
	काष्ठा gru_thपढ़ो_state *gts;
	काष्ठा gru_set_context_option_req req;
	पूर्णांक ret = 0;

	STAT(set_context_option);
	अगर (copy_from_user(&req, (व्योम __user *)arg, माप(req)))
		वापस -EFAULT;
	gru_dbg(grudev, "op %d, gseg 0x%lx, value1 0x%lx\n", req.op, req.gseg, req.val1);

	gts = gru_find_lock_gts(req.gseg);
	अगर (!gts) अणु
		gts = gru_alloc_locked_gts(req.gseg);
		अगर (IS_ERR(gts))
			वापस PTR_ERR(gts);
	पूर्ण

	चयन (req.op) अणु
	हाल sco_blade_chiplet:
		/* Select blade/chiplet क्रम GRU context */
		अगर (req.val0 < -1 || req.val0 >= GRU_CHIPLETS_PER_HUB ||
		    req.val1 < -1 || req.val1 >= GRU_MAX_BLADES ||
		    (req.val1 >= 0 && !gru_base[req.val1])) अणु
			ret = -EINVAL;
		पूर्ण अन्यथा अणु
			gts->ts_user_blade_id = req.val1;
			gts->ts_user_chiplet_id = req.val0;
			gru_check_context_placement(gts);
		पूर्ण
		अवरोध;
	हाल sco_gseg_owner:
 		/* Register the current task as the GSEG owner */
		gts->ts_tgid_owner = current->tgid;
		अवरोध;
	हाल sco_cch_req_slice:
 		/* Set the CCH slice option */
		gts->ts_cch_req_slice = req.val1 & 3;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	gru_unlock_gts(gts);

	वापस ret;
पूर्ण
