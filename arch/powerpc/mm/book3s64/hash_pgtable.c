<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2005, Paul Mackerras, IBM Corporation.
 * Copyright 2009, Benjamin Herrenschmidt, IBM Corporation.
 * Copyright 2015-2016, Aneesh Kumar K.V, IBM Corporation.
 */

#समावेश <linux/sched.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/mm.h>
#समावेश <linux/stop_machine.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/tlb.h>

#समावेश <mm/mmu_decl.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/thp.h>

#अगर H_PGTABLE_RANGE > (USER_VSID_RANGE * (TASK_SIZE_USER64 / TASK_CONTEXT_SIZE))
#warning Limited user VSID range means pagetable space is wasted
#पूर्ण_अगर

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
/*
 * vmemmap is the starting address of the भव address space where
 * काष्ठा pages are allocated क्रम all possible PFNs present on the प्रणाली
 * including holes and bad memory (hence sparse). These भव काष्ठा
 * pages are stored in sequence in this भव address space irrespective
 * of the fact whether the corresponding PFN is valid or not. This achieves
 * स्थिरant relationship between address of काष्ठा page and its PFN.
 *
 * During boot or memory hotplug operation when a new memory section is
 * added, physical memory allocation (including hash table bolting) will
 * be perक्रमmed क्रम the set of काष्ठा pages which are part of the memory
 * section. This saves memory by not allocating काष्ठा pages क्रम PFNs
 * which are not valid.
 *
 *		----------------------------------------------
 *		| PHYSICAL ALLOCATION OF VIRTUAL STRUCT PAGES|
 *		----------------------------------------------
 *
 *	   f000000000000000                  c000000000000000
 * vmemmap +--------------+                  +--------------+
 *  +      |  page काष्ठा | +--------------> |  page काष्ठा |
 *  |      +--------------+                  +--------------+
 *  |      |  page काष्ठा | +--------------> |  page काष्ठा |
 *  |      +--------------+ |                +--------------+
 *  |      |  page काष्ठा | +       +------> |  page काष्ठा |
 *  |      +--------------+         |        +--------------+
 *  |      |  page काष्ठा |         |   +--> |  page काष्ठा |
 *  |      +--------------+         |   |    +--------------+
 *  |      |  page काष्ठा |         |   |
 *  |      +--------------+         |   |
 *  |      |  page काष्ठा |         |   |
 *  |      +--------------+         |   |
 *  |      |  page काष्ठा |         |   |
 *  |      +--------------+         |   |
 *  |      |  page काष्ठा |         |   |
 *  |      +--------------+         |   |
 *  |      |  page काष्ठा | +-------+   |
 *  |      +--------------+             |
 *  |      |  page काष्ठा | +-----------+
 *  |      +--------------+
 *  |      |  page काष्ठा | No mapping
 *  |      +--------------+
 *  |      |  page काष्ठा | No mapping
 *  v      +--------------+
 *
 *		-----------------------------------------
 *		| RELATION BETWEEN STRUCT PAGES AND PFNS|
 *		-----------------------------------------
 *
 * vmemmap +--------------+                 +---------------+
 *  +      |  page काष्ठा | +-------------> |      PFN      |
 *  |      +--------------+                 +---------------+
 *  |      |  page काष्ठा | +-------------> |      PFN      |
 *  |      +--------------+                 +---------------+
 *  |      |  page काष्ठा | +-------------> |      PFN      |
 *  |      +--------------+                 +---------------+
 *  |      |  page काष्ठा | +-------------> |      PFN      |
 *  |      +--------------+                 +---------------+
 *  |      |              |
 *  |      +--------------+
 *  |      |              |
 *  |      +--------------+
 *  |      |              |
 *  |      +--------------+                 +---------------+
 *  |      |  page काष्ठा | +-------------> |      PFN      |
 *  |      +--------------+                 +---------------+
 *  |      |              |
 *  |      +--------------+
 *  |      |              |
 *  |      +--------------+                 +---------------+
 *  |      |  page काष्ठा | +-------------> |      PFN      |
 *  |      +--------------+                 +---------------+
 *  |      |  page काष्ठा | +-------------> |      PFN      |
 *  v      +--------------+                 +---------------+
 */
/*
 * On hash-based CPUs, the vmemmap is bolted in the hash table.
 *
 */
पूर्णांक __meminit hash__vmemmap_create_mapping(अचिन्हित दीर्घ start,
				       अचिन्हित दीर्घ page_size,
				       अचिन्हित दीर्घ phys)
अणु
	पूर्णांक rc;

	अगर ((start + page_size) >= H_VMEMMAP_END) अणु
		pr_warn("Outside the supported range\n");
		वापस -1;
	पूर्ण

	rc = htab_bolt_mapping(start, start + page_size, phys,
			       pgprot_val(PAGE_KERNEL),
			       mmu_vmemmap_psize, mmu_kernel_ssize);
	अगर (rc < 0) अणु
		पूर्णांक rc2 = htab_हटाओ_mapping(start, start + page_size,
					      mmu_vmemmap_psize,
					      mmu_kernel_ssize);
		BUG_ON(rc2 && (rc2 != -ENOENT));
	पूर्ण
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
व्योम hash__vmemmap_हटाओ_mapping(अचिन्हित दीर्घ start,
			      अचिन्हित दीर्घ page_size)
अणु
	पूर्णांक rc = htab_हटाओ_mapping(start, start + page_size,
				     mmu_vmemmap_psize,
				     mmu_kernel_ssize);
	BUG_ON((rc < 0) && (rc != -ENOENT));
	WARN_ON(rc == -ENOENT);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_SPARSEMEM_VMEMMAP */

/*
 * map_kernel_page currently only called by __ioremap
 * map_kernel_page adds an entry to the ioremap page table
 * and adds an entry to the HPT, possibly bolting it
 */
पूर्णांक hash__map_kernel_page(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ pa, pgprot_t prot)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	BUILD_BUG_ON(TASK_SIZE_USER64 > H_PGTABLE_RANGE);
	अगर (slab_is_available()) अणु
		pgdp = pgd_offset_k(ea);
		p4dp = p4d_offset(pgdp, ea);
		pudp = pud_alloc(&init_mm, p4dp, ea);
		अगर (!pudp)
			वापस -ENOMEM;
		pmdp = pmd_alloc(&init_mm, pudp, ea);
		अगर (!pmdp)
			वापस -ENOMEM;
		ptep = pte_alloc_kernel(pmdp, ea);
		अगर (!ptep)
			वापस -ENOMEM;
		set_pte_at(&init_mm, ea, ptep, pfn_pte(pa >> PAGE_SHIFT, prot));
	पूर्ण अन्यथा अणु
		/*
		 * If the mm subप्रणाली is not fully up, we cannot create a
		 * linux page table entry क्रम this mapping.  Simply bolt an
		 * entry in the hardware page table.
		 *
		 */
		अगर (htab_bolt_mapping(ea, ea + PAGE_SIZE, pa, pgprot_val(prot),
				      mmu_io_psize, mmu_kernel_ssize)) अणु
			prपूर्णांकk(KERN_ERR "Failed to do bolted mapping IO "
			       "memory at %016lx !\n", pa);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	smp_wmb();
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE

अचिन्हित दीर्घ hash__pmd_hugepage_update(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				    pmd_t *pmdp, अचिन्हित दीर्घ clr,
				    अचिन्हित दीर्घ set)
अणु
	__be64 old_be, पंचांगp;
	अचिन्हित दीर्घ old;

#अगर_घोषित CONFIG_DEBUG_VM
	WARN_ON(!hash__pmd_trans_huge(*pmdp) && !pmd_devmap(*pmdp));
	निश्चित_spin_locked(pmd_lockptr(mm, pmdp));
#पूर्ण_अगर

	__यंत्र__ __अस्थिर__(
	"1:	ldarx	%0,0,%3\न\
		and.	%1,%0,%6\न\
		bne-	1b \न\
		andc	%1,%0,%4 \न\
		or	%1,%1,%7\न\
		stdcx.	%1,0,%3 \न\
		bne-	1b"
	: "=&r" (old_be), "=&r" (पंचांगp), "=m" (*pmdp)
	: "r" (pmdp), "r" (cpu_to_be64(clr)), "m" (*pmdp),
	  "r" (cpu_to_be64(H_PAGE_BUSY)), "r" (cpu_to_be64(set))
	: "cc" );

	old = be64_to_cpu(old_be);

	trace_hugepage_update(addr, old, clr, set);
	अगर (old & H_PAGE_HASHPTE)
		hpte_करो_hugepage_flush(mm, addr, pmdp, old);
	वापस old;
पूर्ण

pmd_t hash__pmdp_collapse_flush(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			    pmd_t *pmdp)
अणु
	pmd_t pmd;

	VM_BUG_ON(address & ~HPAGE_PMD_MASK);
	VM_BUG_ON(pmd_trans_huge(*pmdp));
	VM_BUG_ON(pmd_devmap(*pmdp));

	pmd = *pmdp;
	pmd_clear(pmdp);
	/*
	 * Wait क्रम all pending hash_page to finish. This is needed
	 * in हाल of subpage collapse. When we collapse normal pages
	 * to hugepage, we first clear the pmd, then invalidate all
	 * the PTE entries. The assumption here is that any low level
	 * page fault will see a none pmd and take the slow path that
	 * will रुको on mmap_lock. But we could very well be in a
	 * hash_page with local ptep poपूर्णांकer value. Such a hash page
	 * can result in adding new HPTE entries क्रम normal subpages.
	 * That means we could be modअगरying the page content as we
	 * copy them to a huge page. So रुको क्रम parallel hash_page
	 * to finish beक्रमe invalidating HPTE entries. We can करो this
	 * by sending an IPI to all the cpus and executing a dummy
	 * function there.
	 */
	serialize_against_pte_lookup(vma->vm_mm);
	/*
	 * Now invalidate the hpte entries in the range
	 * covered by pmd. This make sure we take a
	 * fault and will find the pmd as none, which will
	 * result in a major fault which takes mmap_lock and
	 * hence रुको क्रम collapse to complete. Without this
	 * the __collapse_huge_page_copy can result in copying
	 * the old content.
	 */
	flush_tlb_pmd_range(vma->vm_mm, &pmd, address);
	वापस pmd;
पूर्ण

/*
 * We want to put the pgtable in pmd and use pgtable क्रम tracking
 * the base page size hptes
 */
व्योम hash__pgtable_trans_huge_deposit(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				  pgtable_t pgtable)
अणु
	pgtable_t *pgtable_slot;

	निश्चित_spin_locked(pmd_lockptr(mm, pmdp));
	/*
	 * we store the pgtable in the second half of PMD
	 */
	pgtable_slot = (pgtable_t *)pmdp + PTRS_PER_PMD;
	*pgtable_slot = pgtable;
	/*
	 * expose the deposited pgtable to other cpus.
	 * beक्रमe we set the hugepage PTE at pmd level
	 * hash fault code looks at the deposted pgtable
	 * to store hash index values.
	 */
	smp_wmb();
पूर्ण

pgtable_t hash__pgtable_trans_huge_withdraw(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp)
अणु
	pgtable_t pgtable;
	pgtable_t *pgtable_slot;

	निश्चित_spin_locked(pmd_lockptr(mm, pmdp));

	pgtable_slot = (pgtable_t *)pmdp + PTRS_PER_PMD;
	pgtable = *pgtable_slot;
	/*
	 * Once we withdraw, mark the entry शून्य.
	 */
	*pgtable_slot = शून्य;
	/*
	 * We store HPTE inक्रमmation in the deposited PTE fragment.
	 * zero out the content on withdraw.
	 */
	स_रखो(pgtable, 0, PTE_FRAG_SIZE);
	वापस pgtable;
पूर्ण

/*
 * A linux hugepage PMD was changed and the corresponding hash table entries
 * neesd to be flushed.
 */
व्योम hpte_करो_hugepage_flush(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			    pmd_t *pmdp, अचिन्हित दीर्घ old_pmd)
अणु
	पूर्णांक ssize;
	अचिन्हित पूर्णांक psize;
	अचिन्हित दीर्घ vsid;
	अचिन्हित दीर्घ flags = 0;

	/* get the base page size,vsid and segment size */
#अगर_घोषित CONFIG_DEBUG_VM
	psize = get_slice_psize(mm, addr);
	BUG_ON(psize == MMU_PAGE_16M);
#पूर्ण_अगर
	अगर (old_pmd & H_PAGE_COMBO)
		psize = MMU_PAGE_4K;
	अन्यथा
		psize = MMU_PAGE_64K;

	अगर (!is_kernel_addr(addr)) अणु
		ssize = user_segment_size(addr);
		vsid = get_user_vsid(&mm->context, addr, ssize);
		WARN_ON(vsid == 0);
	पूर्ण अन्यथा अणु
		vsid = get_kernel_vsid(addr, mmu_kernel_ssize);
		ssize = mmu_kernel_ssize;
	पूर्ण

	अगर (mm_is_thपढ़ो_local(mm))
		flags |= HPTE_LOCAL_UPDATE;

	वापस flush_hash_hugepage(vsid, addr, pmdp, psize, ssize, flags);
पूर्ण

pmd_t hash__pmdp_huge_get_and_clear(काष्ठा mm_काष्ठा *mm,
				अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	pmd_t old_pmd;
	pgtable_t pgtable;
	अचिन्हित दीर्घ old;
	pgtable_t *pgtable_slot;

	old = pmd_hugepage_update(mm, addr, pmdp, ~0UL, 0);
	old_pmd = __pmd(old);
	/*
	 * We have pmd == none and we are holding page_table_lock.
	 * So we can safely go and clear the pgtable hash
	 * index info.
	 */
	pgtable_slot = (pgtable_t *)pmdp + PTRS_PER_PMD;
	pgtable = *pgtable_slot;
	/*
	 * Let's zero out old valid and hash index details
	 * hash fault look at them.
	 */
	स_रखो(pgtable, 0, PTE_FRAG_SIZE);
	वापस old_pmd;
पूर्ण

पूर्णांक hash__has_transparent_hugepage(व्योम)
अणु

	अगर (!mmu_has_feature(MMU_FTR_16M_PAGE))
		वापस 0;
	/*
	 * We support THP only अगर PMD_SIZE is 16MB.
	 */
	अगर (mmu_psize_defs[MMU_PAGE_16M].shअगरt != PMD_SHIFT)
		वापस 0;
	/*
	 * We need to make sure that we support 16MB hugepage in a segement
	 * with base page size 64K or 4K. We only enable THP with a PAGE_SIZE
	 * of 64K.
	 */
	/*
	 * If we have 64K HPTE, we will be using that by शेष
	 */
	अगर (mmu_psize_defs[MMU_PAGE_64K].shअगरt &&
	    (mmu_psize_defs[MMU_PAGE_64K].penc[MMU_PAGE_16M] == -1))
		वापस 0;
	/*
	 * Ok we only have 4K HPTE
	 */
	अगर (mmu_psize_defs[MMU_PAGE_4K].penc[MMU_PAGE_16M] == -1)
		वापस 0;

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(hash__has_transparent_hugepage);

#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

#अगर_घोषित CONFIG_STRICT_KERNEL_RWX

काष्ठा change_memory_parms अणु
	अचिन्हित दीर्घ start, end, newpp;
	अचिन्हित पूर्णांक step, nr_cpus, master_cpu;
	atomic_t cpu_counter;
पूर्ण;

// We'd rather this was on the stack but it has to be in the RMO
अटल काष्ठा change_memory_parms chmem_parms;

// And thereक्रमe we need a lock to protect it from concurrent use
अटल DEFINE_MUTEX(chmem_lock);

अटल व्योम change_memory_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				अचिन्हित पूर्णांक step, अचिन्हित दीर्घ newpp)
अणु
	अचिन्हित दीर्घ idx;

	pr_debug("Changing page protection on range 0x%lx-0x%lx, to 0x%lx, step 0x%x\n",
		 start, end, newpp, step);

	क्रम (idx = start; idx < end; idx += step)
		/* Not sure अगर we can करो much with the वापस value */
		mmu_hash_ops.hpte_updateboltedpp(newpp, idx, mmu_linear_psize,
							mmu_kernel_ssize);
पूर्ण

अटल पूर्णांक notrace chmem_secondary_loop(काष्ठा change_memory_parms *parms)
अणु
	अचिन्हित दीर्घ msr, पंचांगp, flags;
	पूर्णांक *p;

	p = &parms->cpu_counter.counter;

	local_irq_save(flags);
	hard_irq_disable();

	यंत्र अस्थिर (
	// Switch to real mode and leave पूर्णांकerrupts off
	"mfmsr	%[msr]			;"
	"li	%[tmp], %[MSR_IR_DR]	;"
	"andc	%[tmp], %[msr], %[tmp]	;"
	"mtmsrd %[tmp]			;"

	// Tell the master we are in real mode
	"1:				"
	"lwarx	%[tmp], 0, %[p]		;"
	"addic	%[tmp], %[tmp], -1	;"
	"stwcx.	%[tmp], 0, %[p]		;"
	"bne-	1b			;"

	// Spin until the counter goes to zero
	"2:				;"
	"lwz	%[tmp], 0(%[p])		;"
	"cmpwi	%[tmp], 0		;"
	"bne-	2b			;"

	// Switch back to भव mode
	"mtmsrd %[msr]			;"

	: // outमाला_दो
	  [msr] "=&r" (msr), [पंचांगp] "=&b" (पंचांगp), "+m" (*p)
	: // inमाला_दो
	  [p] "b" (p), [MSR_IR_DR] "i" (MSR_IR | MSR_DR)
	: // clobbers
	  "cc", "xer"
	);

	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल पूर्णांक change_memory_range_fn(व्योम *data)
अणु
	काष्ठा change_memory_parms *parms = data;

	अगर (parms->master_cpu != smp_processor_id())
		वापस chmem_secondary_loop(parms);

	// Wait क्रम all but one CPU (this one) to call-in
	जबतक (atomic_पढ़ो(&parms->cpu_counter) > 1)
		barrier();

	change_memory_range(parms->start, parms->end, parms->step, parms->newpp);

	mb();

	// Signal the other CPUs that we're करोne
	atomic_dec(&parms->cpu_counter);

	वापस 0;
पूर्ण

अटल bool hash__change_memory_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				      अचिन्हित दीर्घ newpp)
अणु
	अचिन्हित पूर्णांक step, shअगरt;

	shअगरt = mmu_psize_defs[mmu_linear_psize].shअगरt;
	step = 1 << shअगरt;

	start = ALIGN_DOWN(start, step);
	end = ALIGN(end, step); // aligns up

	अगर (start >= end)
		वापस false;

	अगर (firmware_has_feature(FW_FEATURE_LPAR)) अणु
		mutex_lock(&chmem_lock);

		chmem_parms.start = start;
		chmem_parms.end = end;
		chmem_parms.step = step;
		chmem_parms.newpp = newpp;
		chmem_parms.master_cpu = smp_processor_id();

		cpus_पढ़ो_lock();

		atomic_set(&chmem_parms.cpu_counter, num_online_cpus());

		// Ensure state is consistent beक्रमe we call the other CPUs
		mb();

		stop_machine_cpuslocked(change_memory_range_fn, &chmem_parms,
					cpu_online_mask);

		cpus_पढ़ो_unlock();
		mutex_unlock(&chmem_lock);
	पूर्ण अन्यथा
		change_memory_range(start, end, step, newpp);

	वापस true;
पूर्ण

व्योम hash__mark_rodata_ro(व्योम)
अणु
	अचिन्हित दीर्घ start, end, pp;

	start = (अचिन्हित दीर्घ)_stext;
	end = (अचिन्हित दीर्घ)__init_begin;

	pp = htab_convert_pte_flags(pgprot_val(PAGE_KERNEL_ROX), HPTE_USE_KERNEL_KEY);

	WARN_ON(!hash__change_memory_range(start, end, pp));
पूर्ण

व्योम hash__mark_iniपंचांगem_nx(व्योम)
अणु
	अचिन्हित दीर्घ start, end, pp;

	start = (अचिन्हित दीर्घ)__init_begin;
	end = (अचिन्हित दीर्घ)__init_end;

	pp = htab_convert_pte_flags(pgprot_val(PAGE_KERNEL), HPTE_USE_KERNEL_KEY);

	WARN_ON(!hash__change_memory_range(start, end, pp));
पूर्ण
#पूर्ण_अगर
