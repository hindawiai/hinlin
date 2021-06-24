<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015-2016, Aneesh Kumar K.V, IBM Corporation.
 */

#समावेश <linux/sched.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/memblock.h>
#समावेश <misc/cxl-base.h>

#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/trace.h>
#समावेश <यंत्र/घातernv.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/ultravisor.h>
#समावेश <यंत्र/kexec.h>

#समावेश <mm/mmu_decl.h>
#समावेश <trace/events/thp.h>

#समावेश "internal.h"

अचिन्हित दीर्घ __pmd_frag_nr;
EXPORT_SYMBOL(__pmd_frag_nr);
अचिन्हित दीर्घ __pmd_frag_size_shअगरt;
EXPORT_SYMBOL(__pmd_frag_size_shअगरt);

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
/*
 * This is called when relaxing access to a hugepage. It's also called in the page
 * fault path when we करोn't hit any of the major fault हालs, ie, a minor
 * update of _PAGE_ACCESSED, _PAGE_सूचीTY, etc... The generic code will have
 * handled those two क्रम us, we additionally deal with missing execute
 * permission here on some processors
 */
पूर्णांक pmdp_set_access_flags(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			  pmd_t *pmdp, pmd_t entry, पूर्णांक dirty)
अणु
	पूर्णांक changed;
#अगर_घोषित CONFIG_DEBUG_VM
	WARN_ON(!pmd_trans_huge(*pmdp) && !pmd_devmap(*pmdp));
	निश्चित_spin_locked(pmd_lockptr(vma->vm_mm, pmdp));
#पूर्ण_अगर
	changed = !pmd_same(*(pmdp), entry);
	अगर (changed) अणु
		/*
		 * We can use MMU_PAGE_2M here, because only radix
		 * path look at the psize.
		 */
		__ptep_set_access_flags(vma, pmdp_ptep(pmdp),
					pmd_pte(entry), address, MMU_PAGE_2M);
	पूर्ण
	वापस changed;
पूर्ण

पूर्णांक pmdp_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
			      अचिन्हित दीर्घ address, pmd_t *pmdp)
अणु
	वापस __pmdp_test_and_clear_young(vma->vm_mm, address, pmdp);
पूर्ण
/*
 * set a new huge pmd. We should not be called क्रम updating
 * an existing pmd entry. That should go via pmd_hugepage_update.
 */
व्योम set_pmd_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		pmd_t *pmdp, pmd_t pmd)
अणु
#अगर_घोषित CONFIG_DEBUG_VM
	/*
	 * Make sure hardware valid bit is not set. We करोn't करो
	 * tlb flush क्रम this update.
	 */

	WARN_ON(pte_hw_valid(pmd_pte(*pmdp)) && !pte_protnone(pmd_pte(*pmdp)));
	निश्चित_spin_locked(pmd_lockptr(mm, pmdp));
	WARN_ON(!(pmd_large(pmd)));
#पूर्ण_अगर
	trace_hugepage_set_pmd(addr, pmd_val(pmd));
	वापस set_pte_at(mm, addr, pmdp_ptep(pmdp), pmd_pte(pmd));
पूर्ण

अटल व्योम करो_serialize(व्योम *arg)
अणु
	/* We've taken the IPI, so try to trim the mask जबतक here */
	अगर (radix_enabled()) अणु
		काष्ठा mm_काष्ठा *mm = arg;
		निकास_lazy_flush_tlb(mm, false);
	पूर्ण
पूर्ण

/*
 * Serialize against find_current_mm_pte which करोes lock-less
 * lookup in page tables with local पूर्णांकerrupts disabled. For huge pages
 * it casts pmd_t to pte_t. Since क्रमmat of pte_t is dअगरferent from
 * pmd_t we want to prevent transit from pmd poपूर्णांकing to page table
 * to pmd poपूर्णांकing to huge page (and back) जबतक पूर्णांकerrupts are disabled.
 * We clear pmd to possibly replace it with page table poपूर्णांकer in
 * dअगरferent code paths. So make sure we रुको क्रम the parallel
 * find_current_mm_pte to finish.
 */
व्योम serialize_against_pte_lookup(काष्ठा mm_काष्ठा *mm)
अणु
	smp_mb();
	smp_call_function_many(mm_cpumask(mm), करो_serialize, mm, 1);
पूर्ण

/*
 * We use this to invalidate a pmdp entry beक्रमe चयनing from a
 * hugepte to regular pmd entry.
 */
pmd_t pmdp_invalidate(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		     pmd_t *pmdp)
अणु
	अचिन्हित दीर्घ old_pmd;

	old_pmd = pmd_hugepage_update(vma->vm_mm, address, pmdp, _PAGE_PRESENT, _PAGE_INVALID);
	flush_pmd_tlb_range(vma, address, address + HPAGE_PMD_SIZE);
	वापस __pmd(old_pmd);
पूर्ण

pmd_t pmdp_huge_get_and_clear_full(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ addr, pmd_t *pmdp, पूर्णांक full)
अणु
	pmd_t pmd;
	VM_BUG_ON(addr & ~HPAGE_PMD_MASK);
	VM_BUG_ON((pmd_present(*pmdp) && !pmd_trans_huge(*pmdp) &&
		   !pmd_devmap(*pmdp)) || !pmd_present(*pmdp));
	pmd = pmdp_huge_get_and_clear(vma->vm_mm, addr, pmdp);
	/*
	 * अगर it not a fullmm flush, then we can possibly end up converting
	 * this PMD pte entry to a regular level 0 PTE by a parallel page fault.
	 * Make sure we flush the tlb in this हाल.
	 */
	अगर (!full)
		flush_pmd_tlb_range(vma, addr, addr + HPAGE_PMD_SIZE);
	वापस pmd;
पूर्ण

अटल pmd_t pmd_set_protbits(pmd_t pmd, pgprot_t pgprot)
अणु
	वापस __pmd(pmd_val(pmd) | pgprot_val(pgprot));
पूर्ण

/*
 * At some poपूर्णांक we should be able to get rid of
 * pmd_mkhuge() and mk_huge_pmd() when we update all the
 * other archs to mark the pmd huge in pfn_pmd()
 */
pmd_t pfn_pmd(अचिन्हित दीर्घ pfn, pgprot_t pgprot)
अणु
	अचिन्हित दीर्घ pmdv;

	pmdv = (pfn << PAGE_SHIFT) & PTE_RPN_MASK;

	वापस __pmd_mkhuge(pmd_set_protbits(__pmd(pmdv), pgprot));
पूर्ण

pmd_t mk_pmd(काष्ठा page *page, pgprot_t pgprot)
अणु
	वापस pfn_pmd(page_to_pfn(page), pgprot);
पूर्ण

pmd_t pmd_modअगरy(pmd_t pmd, pgprot_t newprot)
अणु
	अचिन्हित दीर्घ pmdv;

	pmdv = pmd_val(pmd);
	pmdv &= _HPAGE_CHG_MASK;
	वापस pmd_set_protbits(__pmd(pmdv), newprot);
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

/* For use by kexec */
व्योम mmu_cleanup_all(व्योम)
अणु
	अगर (radix_enabled())
		radix__mmu_cleanup_all();
	अन्यथा अगर (mmu_hash_ops.hpte_clear_all)
		mmu_hash_ops.hpte_clear_all();

	reset_sprs();
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
पूर्णांक __meminit create_section_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				     पूर्णांक nid, pgprot_t prot)
अणु
	अगर (radix_enabled())
		वापस radix__create_section_mapping(start, end, nid, prot);

	वापस hash__create_section_mapping(start, end, nid, prot);
पूर्ण

पूर्णांक __meminit हटाओ_section_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (radix_enabled())
		वापस radix__हटाओ_section_mapping(start, end);

	वापस hash__हटाओ_section_mapping(start, end);
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG */

व्योम __init mmu_partition_table_init(व्योम)
अणु
	अचिन्हित दीर्घ patb_size = 1UL << PATB_SIZE_SHIFT;
	अचिन्हित दीर्घ ptcr;

	BUILD_BUG_ON_MSG((PATB_SIZE_SHIFT > 36), "Partition table size too large.");
	/* Initialize the Partition Table with no entries */
	partition_tb = memblock_alloc(patb_size, patb_size);
	अगर (!partition_tb)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, patb_size, patb_size);

	/*
	 * update partition table control रेजिस्टर,
	 * 64 K size.
	 */
	ptcr = __pa(partition_tb) | (PATB_SIZE_SHIFT - 12);
	set_ptcr_when_no_uv(ptcr);
	घातernv_set_nmmu_ptcr(ptcr);
पूर्ण

अटल व्योम flush_partition(अचिन्हित पूर्णांक lpid, bool radix)
अणु
	अगर (radix) अणु
		radix__flush_all_lpid(lpid);
		radix__flush_all_lpid_guest(lpid);
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर("ptesync" : : : "memory");
		यंत्र अस्थिर(PPC_TLBIE_5(%0,%1,2,0,0) : :
			     "r" (TLBIEL_INVAL_SET_LPID), "r" (lpid));
		/* करो we need fixup here ?*/
		यंत्र अस्थिर("eieio; tlbsync; ptesync" : : : "memory");
		trace_tlbie(lpid, 0, TLBIEL_INVAL_SET_LPID, lpid, 2, 0, 0);
	पूर्ण
पूर्ण

व्योम mmu_partition_table_set_entry(अचिन्हित पूर्णांक lpid, अचिन्हित दीर्घ dw0,
				  अचिन्हित दीर्घ dw1, bool flush)
अणु
	अचिन्हित दीर्घ old = be64_to_cpu(partition_tb[lpid].patb0);

	/*
	 * When ultravisor is enabled, the partition table is stored in secure
	 * memory and can only be accessed करोing an ultravisor call. However, we
	 * मुख्यtain a copy of the partition table in normal memory to allow Nest
	 * MMU translations to occur (क्रम normal VMs).
	 *
	 * Thereक्रमe, here we always update partition_tb, regardless of whether
	 * we are running under an ultravisor or not.
	 */
	partition_tb[lpid].patb0 = cpu_to_be64(dw0);
	partition_tb[lpid].patb1 = cpu_to_be64(dw1);

	/*
	 * If ultravisor is enabled, we करो an ultravisor call to रेजिस्टर the
	 * partition table entry (PATE), which also करो a global flush of TLBs
	 * and partition table caches क्रम the lpid. Otherwise, just करो the
	 * flush. The type of flush (hash or radix) depends on what the previous
	 * use of the partition ID was, not the new use.
	 */
	अगर (firmware_has_feature(FW_FEATURE_ULTRAVISOR)) अणु
		uv_रेजिस्टर_pate(lpid, dw0, dw1);
		pr_info("PATE registered by ultravisor: dw0 = 0x%lx, dw1 = 0x%lx\n",
			dw0, dw1);
	पूर्ण अन्यथा अगर (flush) अणु
		/*
		 * Boot करोes not need to flush, because MMU is off and each
		 * CPU करोes a tlbiel_all() beक्रमe चयनing them on, which
		 * flushes everything.
		 */
		flush_partition(lpid, (old & PATB_HR));
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mmu_partition_table_set_entry);

अटल pmd_t *get_pmd_from_cache(काष्ठा mm_काष्ठा *mm)
अणु
	व्योम *pmd_frag, *ret;

	अगर (PMD_FRAG_NR == 1)
		वापस शून्य;

	spin_lock(&mm->page_table_lock);
	ret = mm->context.pmd_frag;
	अगर (ret) अणु
		pmd_frag = ret + PMD_FRAG_SIZE;
		/*
		 * If we have taken up all the fragments mark PTE page शून्य
		 */
		अगर (((अचिन्हित दीर्घ)pmd_frag & ~PAGE_MASK) == 0)
			pmd_frag = शून्य;
		mm->context.pmd_frag = pmd_frag;
	पूर्ण
	spin_unlock(&mm->page_table_lock);
	वापस (pmd_t *)ret;
पूर्ण

अटल pmd_t *__alloc_क्रम_pmdcache(काष्ठा mm_काष्ठा *mm)
अणु
	व्योम *ret = शून्य;
	काष्ठा page *page;
	gfp_t gfp = GFP_KERNEL_ACCOUNT | __GFP_ZERO;

	अगर (mm == &init_mm)
		gfp &= ~__GFP_ACCOUNT;
	page = alloc_page(gfp);
	अगर (!page)
		वापस शून्य;
	अगर (!pgtable_pmd_page_ctor(page)) अणु
		__मुक्त_pages(page, 0);
		वापस शून्य;
	पूर्ण

	atomic_set(&page->pt_frag_refcount, 1);

	ret = page_address(page);
	/*
	 * अगर we support only one fragment just वापस the
	 * allocated page.
	 */
	अगर (PMD_FRAG_NR == 1)
		वापस ret;

	spin_lock(&mm->page_table_lock);
	/*
	 * If we find pgtable_page set, we वापस
	 * the allocated page with single fragement
	 * count.
	 */
	अगर (likely(!mm->context.pmd_frag)) अणु
		atomic_set(&page->pt_frag_refcount, PMD_FRAG_NR);
		mm->context.pmd_frag = ret + PMD_FRAG_SIZE;
	पूर्ण
	spin_unlock(&mm->page_table_lock);

	वापस (pmd_t *)ret;
पूर्ण

pmd_t *pmd_fragment_alloc(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr)
अणु
	pmd_t *pmd;

	pmd = get_pmd_from_cache(mm);
	अगर (pmd)
		वापस pmd;

	वापस __alloc_क्रम_pmdcache(mm);
पूर्ण

व्योम pmd_fragment_मुक्त(अचिन्हित दीर्घ *pmd)
अणु
	काष्ठा page *page = virt_to_page(pmd);

	अगर (PageReserved(page))
		वापस मुक्त_reserved_page(page);

	BUG_ON(atomic_पढ़ो(&page->pt_frag_refcount) <= 0);
	अगर (atomic_dec_and_test(&page->pt_frag_refcount)) अणु
		pgtable_pmd_page_dtor(page);
		__मुक्त_page(page);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pgtable_मुक्त(व्योम *table, पूर्णांक index)
अणु
	चयन (index) अणु
	हाल PTE_INDEX:
		pte_fragment_मुक्त(table, 0);
		अवरोध;
	हाल PMD_INDEX:
		pmd_fragment_मुक्त(table);
		अवरोध;
	हाल PUD_INDEX:
		__pud_मुक्त(table);
		अवरोध;
#अगर defined(CONFIG_PPC_4K_PAGES) && defined(CONFIG_HUGETLB_PAGE)
		/* 16M hugepd directory at pud level */
	हाल HTLB_16M_INDEX:
		BUILD_BUG_ON(H_16M_CACHE_INDEX <= 0);
		kmem_cache_मुक्त(PGT_CACHE(H_16M_CACHE_INDEX), table);
		अवरोध;
		/* 16G hugepd directory at the pgd level */
	हाल HTLB_16G_INDEX:
		BUILD_BUG_ON(H_16G_CACHE_INDEX <= 0);
		kmem_cache_मुक्त(PGT_CACHE(H_16G_CACHE_INDEX), table);
		अवरोध;
#पूर्ण_अगर
		/* We करोn't मुक्त pgd table via RCU callback */
	शेष:
		BUG();
	पूर्ण
पूर्ण

व्योम pgtable_मुक्त_tlb(काष्ठा mmu_gather *tlb, व्योम *table, पूर्णांक index)
अणु
	अचिन्हित दीर्घ pgf = (अचिन्हित दीर्घ)table;

	BUG_ON(index > MAX_PGTABLE_INDEX_SIZE);
	pgf |= index;
	tlb_हटाओ_table(tlb, (व्योम *)pgf);
पूर्ण

व्योम __tlb_हटाओ_table(व्योम *_table)
अणु
	व्योम *table = (व्योम *)((अचिन्हित दीर्घ)_table & ~MAX_PGTABLE_INDEX_SIZE);
	अचिन्हित पूर्णांक index = (अचिन्हित दीर्घ)_table & MAX_PGTABLE_INDEX_SIZE;

	वापस pgtable_मुक्त(table, index);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
atomic_दीर्घ_t direct_pages_count[MMU_PAGE_COUNT];

व्योम arch_report_meminfo(काष्ठा seq_file *m)
अणु
	/*
	 * Hash maps the memory with one size mmu_linear_psize.
	 * So करोn't bother to prपूर्णांक these on hash
	 */
	अगर (!radix_enabled())
		वापस;
	seq_म_लिखो(m, "DirectMap4k:    %8lu kB\n",
		   atomic_दीर्घ_पढ़ो(&direct_pages_count[MMU_PAGE_4K]) << 2);
	seq_म_लिखो(m, "DirectMap64k:    %8lu kB\n",
		   atomic_दीर्घ_पढ़ो(&direct_pages_count[MMU_PAGE_64K]) << 6);
	seq_म_लिखो(m, "DirectMap2M:    %8lu kB\n",
		   atomic_दीर्घ_पढ़ो(&direct_pages_count[MMU_PAGE_2M]) << 11);
	seq_म_लिखो(m, "DirectMap1G:    %8lu kB\n",
		   atomic_दीर्घ_पढ़ो(&direct_pages_count[MMU_PAGE_1G]) << 20);
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

pte_t ptep_modअगरy_prot_start(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			     pte_t *ptep)
अणु
	अचिन्हित दीर्घ pte_val;

	/*
	 * Clear the _PAGE_PRESENT so that no hardware parallel update is
	 * possible. Also keep the pte_present true so that we करोn't take
	 * wrong fault.
	 */
	pte_val = pte_update(vma->vm_mm, addr, ptep, _PAGE_PRESENT, _PAGE_INVALID, 0);

	वापस __pte(pte_val);

पूर्ण

व्योम ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			     pte_t *ptep, pte_t old_pte, pte_t pte)
अणु
	अगर (radix_enabled())
		वापस radix__ptep_modअगरy_prot_commit(vma, addr,
						      ptep, old_pte, pte);
	set_pte_at(vma->vm_mm, addr, ptep, pte);
पूर्ण

/*
 * For hash translation mode, we use the deposited table to store hash slot
 * inक्रमmation and they are stored at PTRS_PER_PMD offset from related pmd
 * location. Hence a pmd move requires deposit and withdraw.
 *
 * For radix translation with split pmd ptl, we store the deposited table in the
 * pmd page. Hence अगर we have dअगरferent pmd page we need to withdraw during pmd
 * move.
 *
 * With hash we use deposited table always irrespective of anon or not.
 * With radix we use deposited table only क्रम anonymous mapping.
 */
पूर्णांक pmd_move_must_withdraw(काष्ठा spinlock *new_pmd_ptl,
			   काष्ठा spinlock *old_pmd_ptl,
			   काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (radix_enabled())
		वापस (new_pmd_ptl != old_pmd_ptl) && vma_is_anonymous(vma);

	वापस true;
पूर्ण

/*
 * Does the CPU support tlbie?
 */
bool tlbie_capable __पढ़ो_mostly = true;
EXPORT_SYMBOL(tlbie_capable);

/*
 * Should tlbie be used क्रम management of CPU TLBs, क्रम kernel and process
 * address spaces? tlbie may still be used क्रम nMMU accelerators, and क्रम KVM
 * guest address spaces.
 */
bool tlbie_enabled __पढ़ो_mostly = true;

अटल पूर्णांक __init setup_disable_tlbie(अक्षर *str)
अणु
	अगर (!radix_enabled()) अणु
		pr_err("disable_tlbie: Unable to disable TLBIE with Hash MMU.\n");
		वापस 1;
	पूर्ण

	tlbie_capable = false;
	tlbie_enabled = false;

        वापस 1;
पूर्ण
__setup("disable_tlbie", setup_disable_tlbie);

अटल पूर्णांक __init pgtable_debugfs_setup(व्योम)
अणु
	अगर (!tlbie_capable)
		वापस 0;

	/*
	 * There is no locking vs tlb flushing when changing this value.
	 * The tlb flushers will see one value or another, and use either
	 * tlbie or tlbiel with IPIs. In both हालs the TLBs will be
	 * invalidated as expected.
	 */
	debugfs_create_bool("tlbie_enabled", 0600,
			घातerpc_debugfs_root,
			&tlbie_enabled);

	वापस 0;
पूर्ण
arch_initcall(pgtable_debugfs_setup);
