<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/mm/mmu.c
 *
 * Copyright (C) 1995-2005 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/cache.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kexec.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/mman.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/memblock.h>
#समावेश <linux/memory.h>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/kasan.h>
#समावेश <यंत्र/kernel-pgtable.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/ptdump.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/pgभाग.स>

#घोषणा NO_BLOCK_MAPPINGS	BIT(0)
#घोषणा NO_CONT_MAPPINGS	BIT(1)
#घोषणा NO_EXEC_MAPPINGS	BIT(2)	/* assumes FEAT_HPDS is not used */

u64 idmap_t0sz = TCR_T0SZ(VA_BITS_MIN);
u64 idmap_ptrs_per_pgd = PTRS_PER_PGD;

u64 __section(".mmuoff.data.write") vabits_actual;
EXPORT_SYMBOL(vabits_actual);

u64 kimage_voffset __ro_after_init;
EXPORT_SYMBOL(kimage_voffset);

/*
 * Empty_zero_page is a special page that is used क्रम zero-initialized data
 * and COW.
 */
अचिन्हित दीर्घ empty_zero_page[PAGE_SIZE / माप(अचिन्हित दीर्घ)] __page_aligned_bss;
EXPORT_SYMBOL(empty_zero_page);

अटल pte_t bm_pte[PTRS_PER_PTE] __page_aligned_bss;
अटल pmd_t bm_pmd[PTRS_PER_PMD] __page_aligned_bss __maybe_unused;
अटल pud_t bm_pud[PTRS_PER_PUD] __page_aligned_bss __maybe_unused;

अटल DEFINE_SPINLOCK(swapper_pgdir_lock);

व्योम set_swapper_pgd(pgd_t *pgdp, pgd_t pgd)
अणु
	pgd_t *fixmap_pgdp;

	spin_lock(&swapper_pgdir_lock);
	fixmap_pgdp = pgd_set_fixmap(__pa_symbol(pgdp));
	WRITE_ONCE(*fixmap_pgdp, pgd);
	/*
	 * We need dsb(ishst) here to ensure the page-table-walker sees
	 * our new entry beक्रमe set_p?d() वापसs. The fixmap's
	 * flush_tlb_kernel_range() via clear_fixmap() करोes this क्रम us.
	 */
	pgd_clear_fixmap();
	spin_unlock(&swapper_pgdir_lock);
पूर्ण

pgprot_t phys_mem_access_prot(काष्ठा file *file, अचिन्हित दीर्घ pfn,
			      अचिन्हित दीर्घ size, pgprot_t vma_prot)
अणु
	अगर (!pfn_valid(pfn))
		वापस pgprot_noncached(vma_prot);
	अन्यथा अगर (file->f_flags & O_SYNC)
		वापस pgprot_ग_लिखोcombine(vma_prot);
	वापस vma_prot;
पूर्ण
EXPORT_SYMBOL(phys_mem_access_prot);

अटल phys_addr_t __init early_pgtable_alloc(पूर्णांक shअगरt)
अणु
	phys_addr_t phys;
	व्योम *ptr;

	phys = memblock_phys_alloc(PAGE_SIZE, PAGE_SIZE);
	अगर (!phys)
		panic("Failed to allocate page table page\n");

	/*
	 * The FIX_अणुPGD,PUD,PMDपूर्ण slots may be in active use, but the FIX_PTE
	 * slot will be मुक्त, so we can (ab)use the FIX_PTE slot to initialise
	 * any level of table.
	 */
	ptr = pte_set_fixmap(phys);

	स_रखो(ptr, 0, PAGE_SIZE);

	/*
	 * Implicit barriers also ensure the zeroed page is visible to the page
	 * table walker
	 */
	pte_clear_fixmap();

	वापस phys;
पूर्ण

अटल bool pgattr_change_is_safe(u64 old, u64 new)
अणु
	/*
	 * The following mapping attributes may be updated in live
	 * kernel mappings without the need क्रम अवरोध-beक्रमe-make.
	 */
	pteval_t mask = PTE_PXN | PTE_RDONLY | PTE_WRITE | PTE_NG;

	/* creating or taking करोwn mappings is always safe */
	अगर (old == 0 || new == 0)
		वापस true;

	/* live contiguous mappings may not be manipulated at all */
	अगर ((old | new) & PTE_CONT)
		वापस false;

	/* Transitioning from Non-Global to Global is unsafe */
	अगर (old & ~new & PTE_NG)
		वापस false;

	/*
	 * Changing the memory type between Normal and Normal-Tagged is safe
	 * since Tagged is considered a permission attribute from the
	 * mismatched attribute aliases perspective.
	 */
	अगर (((old & PTE_ATTRINDX_MASK) == PTE_ATTRINDX(MT_NORMAL) ||
	     (old & PTE_ATTRINDX_MASK) == PTE_ATTRINDX(MT_NORMAL_TAGGED)) &&
	    ((new & PTE_ATTRINDX_MASK) == PTE_ATTRINDX(MT_NORMAL) ||
	     (new & PTE_ATTRINDX_MASK) == PTE_ATTRINDX(MT_NORMAL_TAGGED)))
		mask |= PTE_ATTRINDX_MASK;

	वापस ((old ^ new) & ~mask) == 0;
पूर्ण

अटल व्योम init_pte(pmd_t *pmdp, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		     phys_addr_t phys, pgprot_t prot)
अणु
	pte_t *ptep;

	ptep = pte_set_fixmap_offset(pmdp, addr);
	करो अणु
		pte_t old_pte = READ_ONCE(*ptep);

		set_pte(ptep, pfn_pte(__phys_to_pfn(phys), prot));

		/*
		 * After the PTE entry has been populated once, we
		 * only allow updates to the permission attributes.
		 */
		BUG_ON(!pgattr_change_is_safe(pte_val(old_pte),
					      READ_ONCE(pte_val(*ptep))));

		phys += PAGE_SIZE;
	पूर्ण जबतक (ptep++, addr += PAGE_SIZE, addr != end);

	pte_clear_fixmap();
पूर्ण

अटल व्योम alloc_init_cont_pte(pmd_t *pmdp, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ end, phys_addr_t phys,
				pgprot_t prot,
				phys_addr_t (*pgtable_alloc)(पूर्णांक),
				पूर्णांक flags)
अणु
	अचिन्हित दीर्घ next;
	pmd_t pmd = READ_ONCE(*pmdp);

	BUG_ON(pmd_sect(pmd));
	अगर (pmd_none(pmd)) अणु
		pmdval_t pmdval = PMD_TYPE_TABLE | PMD_TABLE_UXN;
		phys_addr_t pte_phys;

		अगर (flags & NO_EXEC_MAPPINGS)
			pmdval |= PMD_TABLE_PXN;
		BUG_ON(!pgtable_alloc);
		pte_phys = pgtable_alloc(PAGE_SHIFT);
		__pmd_populate(pmdp, pte_phys, pmdval);
		pmd = READ_ONCE(*pmdp);
	पूर्ण
	BUG_ON(pmd_bad(pmd));

	करो अणु
		pgprot_t __prot = prot;

		next = pte_cont_addr_end(addr, end);

		/* use a contiguous mapping अगर the range is suitably aligned */
		अगर ((((addr | next | phys) & ~CONT_PTE_MASK) == 0) &&
		    (flags & NO_CONT_MAPPINGS) == 0)
			__prot = __pgprot(pgprot_val(prot) | PTE_CONT);

		init_pte(pmdp, addr, next, phys, __prot);

		phys += next - addr;
	पूर्ण जबतक (addr = next, addr != end);
पूर्ण

अटल व्योम init_pmd(pud_t *pudp, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		     phys_addr_t phys, pgprot_t prot,
		     phys_addr_t (*pgtable_alloc)(पूर्णांक), पूर्णांक flags)
अणु
	अचिन्हित दीर्घ next;
	pmd_t *pmdp;

	pmdp = pmd_set_fixmap_offset(pudp, addr);
	करो अणु
		pmd_t old_pmd = READ_ONCE(*pmdp);

		next = pmd_addr_end(addr, end);

		/* try section mapping first */
		अगर (((addr | next | phys) & ~SECTION_MASK) == 0 &&
		    (flags & NO_BLOCK_MAPPINGS) == 0) अणु
			pmd_set_huge(pmdp, phys, prot);

			/*
			 * After the PMD entry has been populated once, we
			 * only allow updates to the permission attributes.
			 */
			BUG_ON(!pgattr_change_is_safe(pmd_val(old_pmd),
						      READ_ONCE(pmd_val(*pmdp))));
		पूर्ण अन्यथा अणु
			alloc_init_cont_pte(pmdp, addr, next, phys, prot,
					    pgtable_alloc, flags);

			BUG_ON(pmd_val(old_pmd) != 0 &&
			       pmd_val(old_pmd) != READ_ONCE(pmd_val(*pmdp)));
		पूर्ण
		phys += next - addr;
	पूर्ण जबतक (pmdp++, addr = next, addr != end);

	pmd_clear_fixmap();
पूर्ण

अटल व्योम alloc_init_cont_pmd(pud_t *pudp, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ end, phys_addr_t phys,
				pgprot_t prot,
				phys_addr_t (*pgtable_alloc)(पूर्णांक), पूर्णांक flags)
अणु
	अचिन्हित दीर्घ next;
	pud_t pud = READ_ONCE(*pudp);

	/*
	 * Check क्रम initial section mappings in the pgd/pud.
	 */
	BUG_ON(pud_sect(pud));
	अगर (pud_none(pud)) अणु
		pudval_t pudval = PUD_TYPE_TABLE | PUD_TABLE_UXN;
		phys_addr_t pmd_phys;

		अगर (flags & NO_EXEC_MAPPINGS)
			pudval |= PUD_TABLE_PXN;
		BUG_ON(!pgtable_alloc);
		pmd_phys = pgtable_alloc(PMD_SHIFT);
		__pud_populate(pudp, pmd_phys, pudval);
		pud = READ_ONCE(*pudp);
	पूर्ण
	BUG_ON(pud_bad(pud));

	करो अणु
		pgprot_t __prot = prot;

		next = pmd_cont_addr_end(addr, end);

		/* use a contiguous mapping अगर the range is suitably aligned */
		अगर ((((addr | next | phys) & ~CONT_PMD_MASK) == 0) &&
		    (flags & NO_CONT_MAPPINGS) == 0)
			__prot = __pgprot(pgprot_val(prot) | PTE_CONT);

		init_pmd(pudp, addr, next, phys, __prot, pgtable_alloc, flags);

		phys += next - addr;
	पूर्ण जबतक (addr = next, addr != end);
पूर्ण

अटल अंतरभूत bool use_1G_block(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ next,
			अचिन्हित दीर्घ phys)
अणु
	अगर (PAGE_SHIFT != 12)
		वापस false;

	अगर (((addr | next | phys) & ~PUD_MASK) != 0)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम alloc_init_pud(pgd_t *pgdp, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			   phys_addr_t phys, pgprot_t prot,
			   phys_addr_t (*pgtable_alloc)(पूर्णांक),
			   पूर्णांक flags)
अणु
	अचिन्हित दीर्घ next;
	pud_t *pudp;
	p4d_t *p4dp = p4d_offset(pgdp, addr);
	p4d_t p4d = READ_ONCE(*p4dp);

	अगर (p4d_none(p4d)) अणु
		p4dval_t p4dval = P4D_TYPE_TABLE | P4D_TABLE_UXN;
		phys_addr_t pud_phys;

		अगर (flags & NO_EXEC_MAPPINGS)
			p4dval |= P4D_TABLE_PXN;
		BUG_ON(!pgtable_alloc);
		pud_phys = pgtable_alloc(PUD_SHIFT);
		__p4d_populate(p4dp, pud_phys, p4dval);
		p4d = READ_ONCE(*p4dp);
	पूर्ण
	BUG_ON(p4d_bad(p4d));

	pudp = pud_set_fixmap_offset(p4dp, addr);
	करो अणु
		pud_t old_pud = READ_ONCE(*pudp);

		next = pud_addr_end(addr, end);

		/*
		 * For 4K granule only, attempt to put करोwn a 1GB block
		 */
		अगर (use_1G_block(addr, next, phys) &&
		    (flags & NO_BLOCK_MAPPINGS) == 0) अणु
			pud_set_huge(pudp, phys, prot);

			/*
			 * After the PUD entry has been populated once, we
			 * only allow updates to the permission attributes.
			 */
			BUG_ON(!pgattr_change_is_safe(pud_val(old_pud),
						      READ_ONCE(pud_val(*pudp))));
		पूर्ण अन्यथा अणु
			alloc_init_cont_pmd(pudp, addr, next, phys, prot,
					    pgtable_alloc, flags);

			BUG_ON(pud_val(old_pud) != 0 &&
			       pud_val(old_pud) != READ_ONCE(pud_val(*pudp)));
		पूर्ण
		phys += next - addr;
	पूर्ण जबतक (pudp++, addr = next, addr != end);

	pud_clear_fixmap();
पूर्ण

अटल व्योम __create_pgd_mapping(pgd_t *pgdir, phys_addr_t phys,
				 अचिन्हित दीर्घ virt, phys_addr_t size,
				 pgprot_t prot,
				 phys_addr_t (*pgtable_alloc)(पूर्णांक),
				 पूर्णांक flags)
अणु
	अचिन्हित दीर्घ addr, end, next;
	pgd_t *pgdp = pgd_offset_pgd(pgdir, virt);

	/*
	 * If the भव and physical address करोn't have the same offset
	 * within a page, we cannot map the region as the caller expects.
	 */
	अगर (WARN_ON((phys ^ virt) & ~PAGE_MASK))
		वापस;

	phys &= PAGE_MASK;
	addr = virt & PAGE_MASK;
	end = PAGE_ALIGN(virt + size);

	करो अणु
		next = pgd_addr_end(addr, end);
		alloc_init_pud(pgdp, addr, next, phys, prot, pgtable_alloc,
			       flags);
		phys += next - addr;
	पूर्ण जबतक (pgdp++, addr = next, addr != end);
पूर्ण

अटल phys_addr_t __pgd_pgtable_alloc(पूर्णांक shअगरt)
अणु
	व्योम *ptr = (व्योम *)__get_मुक्त_page(GFP_PGTABLE_KERNEL);
	BUG_ON(!ptr);

	/* Ensure the zeroed page is visible to the page table walker */
	dsb(ishst);
	वापस __pa(ptr);
पूर्ण

अटल phys_addr_t pgd_pgtable_alloc(पूर्णांक shअगरt)
अणु
	phys_addr_t pa = __pgd_pgtable_alloc(shअगरt);

	/*
	 * Call proper page table ctor in हाल later we need to
	 * call core mm functions like apply_to_page_range() on
	 * this pre-allocated page table.
	 *
	 * We करोn't select ARCH_ENABLE_SPLIT_PMD_PTLOCK अगर pmd is
	 * folded, and अगर so pgtable_pmd_page_ctor() becomes nop.
	 */
	अगर (shअगरt == PAGE_SHIFT)
		BUG_ON(!pgtable_pte_page_ctor(phys_to_page(pa)));
	अन्यथा अगर (shअगरt == PMD_SHIFT)
		BUG_ON(!pgtable_pmd_page_ctor(phys_to_page(pa)));

	वापस pa;
पूर्ण

/*
 * This function can only be used to modअगरy existing table entries,
 * without allocating new levels of table. Note that this permits the
 * creation of new section or page entries.
 */
अटल व्योम __init create_mapping_noalloc(phys_addr_t phys, अचिन्हित दीर्घ virt,
				  phys_addr_t size, pgprot_t prot)
अणु
	अगर ((virt >= PAGE_END) && (virt < VMALLOC_START)) अणु
		pr_warn("BUG: not creating mapping for %pa at 0x%016lx - outside kernel range\n",
			&phys, virt);
		वापस;
	पूर्ण
	__create_pgd_mapping(init_mm.pgd, phys, virt, size, prot, शून्य,
			     NO_CONT_MAPPINGS);
पूर्ण

व्योम __init create_pgd_mapping(काष्ठा mm_काष्ठा *mm, phys_addr_t phys,
			       अचिन्हित दीर्घ virt, phys_addr_t size,
			       pgprot_t prot, bool page_mappings_only)
अणु
	पूर्णांक flags = 0;

	BUG_ON(mm == &init_mm);

	अगर (page_mappings_only)
		flags = NO_BLOCK_MAPPINGS | NO_CONT_MAPPINGS;

	__create_pgd_mapping(mm->pgd, phys, virt, size, prot,
			     pgd_pgtable_alloc, flags);
पूर्ण

अटल व्योम update_mapping_prot(phys_addr_t phys, अचिन्हित दीर्घ virt,
				phys_addr_t size, pgprot_t prot)
अणु
	अगर ((virt >= PAGE_END) && (virt < VMALLOC_START)) अणु
		pr_warn("BUG: not updating mapping for %pa at 0x%016lx - outside kernel range\n",
			&phys, virt);
		वापस;
	पूर्ण

	__create_pgd_mapping(init_mm.pgd, phys, virt, size, prot, शून्य,
			     NO_CONT_MAPPINGS);

	/* flush the TLBs after updating live kernel mappings */
	flush_tlb_kernel_range(virt, virt + size);
पूर्ण

अटल व्योम __init __map_memblock(pgd_t *pgdp, phys_addr_t start,
				  phys_addr_t end, pgprot_t prot, पूर्णांक flags)
अणु
	__create_pgd_mapping(pgdp, start, __phys_to_virt(start), end - start,
			     prot, early_pgtable_alloc, flags);
पूर्ण

व्योम __init mark_linear_text_alias_ro(व्योम)
अणु
	/*
	 * Remove the ग_लिखो permissions from the linear alias of .text/.rodata
	 */
	update_mapping_prot(__pa_symbol(_stext), (अचिन्हित दीर्घ)lm_alias(_stext),
			    (अचिन्हित दीर्घ)__init_begin - (अचिन्हित दीर्घ)_stext,
			    PAGE_KERNEL_RO);
पूर्ण

अटल bool crash_mem_map __initdata;

अटल पूर्णांक __init enable_crash_mem_map(अक्षर *arg)
अणु
	/*
	 * Proper parameter parsing is करोne by reserve_crashkernel(). We only
	 * need to know अगर the linear map has to aव्योम block mappings so that
	 * the crashkernel reservations can be unmapped later.
	 */
	crash_mem_map = true;

	वापस 0;
पूर्ण
early_param("crashkernel", enable_crash_mem_map);

अटल व्योम __init map_mem(pgd_t *pgdp)
अणु
	अटल स्थिर u64 direct_map_end = _PAGE_END(VA_BITS_MIN);
	phys_addr_t kernel_start = __pa_symbol(_stext);
	phys_addr_t kernel_end = __pa_symbol(__init_begin);
	phys_addr_t start, end;
	पूर्णांक flags = NO_EXEC_MAPPINGS;
	u64 i;

	/*
	 * Setting hierarchical PXNTable attributes on table entries covering
	 * the linear region is only possible अगर it is guaranteed that no table
	 * entries at any level are being shared between the linear region and
	 * the vदो_स्मृति region. Check whether this is true क्रम the PGD level, in
	 * which हाल it is guaranteed to be true क्रम all other levels as well.
	 */
	BUILD_BUG_ON(pgd_index(direct_map_end - 1) == pgd_index(direct_map_end));

	अगर (rodata_full || crash_mem_map || debug_pagealloc_enabled() ||
	    IS_ENABLED(CONFIG_KFENCE))
		flags |= NO_BLOCK_MAPPINGS | NO_CONT_MAPPINGS;

	/*
	 * Take care not to create a writable alias क्रम the
	 * पढ़ो-only text and rodata sections of the kernel image.
	 * So temporarily mark them as NOMAP to skip mappings in
	 * the following क्रम-loop
	 */
	memblock_mark_nomap(kernel_start, kernel_end - kernel_start);

	/* map all the memory banks */
	क्रम_each_mem_range(i, &start, &end) अणु
		अगर (start >= end)
			अवरोध;
		/*
		 * The linear map must allow allocation tags पढ़ोing/writing
		 * अगर MTE is present. Otherwise, it has the same attributes as
		 * PAGE_KERNEL.
		 */
		__map_memblock(pgdp, start, end, pgprot_tagged(PAGE_KERNEL),
			       flags);
	पूर्ण

	/*
	 * Map the linear alias of the [_stext, __init_begin) पूर्णांकerval
	 * as non-executable now, and हटाओ the ग_लिखो permission in
	 * mark_linear_text_alias_ro() below (which will be called after
	 * alternative patching has completed). This makes the contents
	 * of the region accessible to subप्रणालीs such as hibernate,
	 * but protects it from inadvertent modअगरication or execution.
	 * Note that contiguous mappings cannot be remapped in this way,
	 * so we should aव्योम them here.
	 */
	__map_memblock(pgdp, kernel_start, kernel_end,
		       PAGE_KERNEL, NO_CONT_MAPPINGS);
	memblock_clear_nomap(kernel_start, kernel_end - kernel_start);
पूर्ण

व्योम mark_rodata_ro(व्योम)
अणु
	अचिन्हित दीर्घ section_size;

	/*
	 * mark .rodata as पढ़ो only. Use __init_begin rather than __end_rodata
	 * to cover NOTES and EXCEPTION_TABLE.
	 */
	section_size = (अचिन्हित दीर्घ)__init_begin - (अचिन्हित दीर्घ)__start_rodata;
	update_mapping_prot(__pa_symbol(__start_rodata), (अचिन्हित दीर्घ)__start_rodata,
			    section_size, PAGE_KERNEL_RO);

	debug_checkwx();
पूर्ण

अटल व्योम __init map_kernel_segment(pgd_t *pgdp, व्योम *बहु_शुरू, व्योम *बहु_पूर्ण,
				      pgprot_t prot, काष्ठा vm_काष्ठा *vma,
				      पूर्णांक flags, अचिन्हित दीर्घ vm_flags)
अणु
	phys_addr_t pa_start = __pa_symbol(बहु_शुरू);
	अचिन्हित दीर्घ size = बहु_पूर्ण - बहु_शुरू;

	BUG_ON(!PAGE_ALIGNED(pa_start));
	BUG_ON(!PAGE_ALIGNED(size));

	__create_pgd_mapping(pgdp, pa_start, (अचिन्हित दीर्घ)बहु_शुरू, size, prot,
			     early_pgtable_alloc, flags);

	अगर (!(vm_flags & VM_NO_GUARD))
		size += PAGE_SIZE;

	vma->addr	= बहु_शुरू;
	vma->phys_addr	= pa_start;
	vma->size	= size;
	vma->flags	= VM_MAP | vm_flags;
	vma->caller	= __builtin_वापस_address(0);

	vm_area_add_early(vma);
पूर्ण

अटल पूर्णांक __init parse_rodata(अक्षर *arg)
अणु
	पूर्णांक ret = strtobool(arg, &rodata_enabled);
	अगर (!ret) अणु
		rodata_full = false;
		वापस 0;
	पूर्ण

	/* permit 'full' in addition to boolean options */
	अगर (म_भेद(arg, "full"))
		वापस -EINVAL;

	rodata_enabled = true;
	rodata_full = true;
	वापस 0;
पूर्ण
early_param("rodata", parse_rodata);

#अगर_घोषित CONFIG_UNMAP_KERNEL_AT_EL0
अटल पूर्णांक __init map_entry_trampoline(व्योम)
अणु
	pgprot_t prot = rodata_enabled ? PAGE_KERNEL_ROX : PAGE_KERNEL_EXEC;
	phys_addr_t pa_start = __pa_symbol(__entry_tramp_text_start);

	/* The trampoline is always mapped and can thereक्रमe be global */
	pgprot_val(prot) &= ~PTE_NG;

	/* Map only the text पूर्णांकo the trampoline page table */
	स_रखो(tramp_pg_dir, 0, PGD_SIZE);
	__create_pgd_mapping(tramp_pg_dir, pa_start, TRAMP_VALIAS, PAGE_SIZE,
			     prot, __pgd_pgtable_alloc, 0);

	/* Map both the text and data पूर्णांकo the kernel page table */
	__set_fixmap(FIX_ENTRY_TRAMP_TEXT, pa_start, prot);
	अगर (IS_ENABLED(CONFIG_RANDOMIZE_BASE)) अणु
		बाह्य अक्षर __entry_tramp_data_start[];

		__set_fixmap(FIX_ENTRY_TRAMP_DATA,
			     __pa_symbol(__entry_tramp_data_start),
			     PAGE_KERNEL_RO);
	पूर्ण

	वापस 0;
पूर्ण
core_initcall(map_entry_trampoline);
#पूर्ण_अगर

/*
 * Open coded check क्रम BTI, only क्रम use to determine configuration
 * क्रम early mappings क्रम beक्रमe the cpufeature code has run.
 */
अटल bool arm64_early_this_cpu_has_bti(व्योम)
अणु
	u64 pfr1;

	अगर (!IS_ENABLED(CONFIG_ARM64_BTI_KERNEL))
		वापस false;

	pfr1 = __पढ़ो_sysreg_by_encoding(SYS_ID_AA64PFR1_EL1);
	वापस cpuid_feature_extract_अचिन्हित_field(pfr1,
						    ID_AA64PFR1_BT_SHIFT);
पूर्ण

/*
 * Create fine-grained mappings क्रम the kernel.
 */
अटल व्योम __init map_kernel(pgd_t *pgdp)
अणु
	अटल काष्ठा vm_काष्ठा vmlinux_text, vmlinux_rodata, vmlinux_inittext,
				vmlinux_initdata, vmlinux_data;

	/*
	 * External debuggers may need to ग_लिखो directly to the text
	 * mapping to install SW अवरोधpoपूर्णांकs. Allow this (only) when
	 * explicitly requested with rodata=off.
	 */
	pgprot_t text_prot = rodata_enabled ? PAGE_KERNEL_ROX : PAGE_KERNEL_EXEC;

	/*
	 * If we have a CPU that supports BTI and a kernel built क्रम
	 * BTI then mark the kernel executable text as guarded pages
	 * now so we करोn't have to reग_लिखो the page tables later.
	 */
	अगर (arm64_early_this_cpu_has_bti())
		text_prot = __pgprot_modअगरy(text_prot, PTE_GP, PTE_GP);

	/*
	 * Only rodata will be remapped with dअगरferent permissions later on,
	 * all other segments are allowed to use contiguous mappings.
	 */
	map_kernel_segment(pgdp, _stext, _etext, text_prot, &vmlinux_text, 0,
			   VM_NO_GUARD);
	map_kernel_segment(pgdp, __start_rodata, __inittext_begin, PAGE_KERNEL,
			   &vmlinux_rodata, NO_CONT_MAPPINGS, VM_NO_GUARD);
	map_kernel_segment(pgdp, __inittext_begin, __inittext_end, text_prot,
			   &vmlinux_inittext, 0, VM_NO_GUARD);
	map_kernel_segment(pgdp, __initdata_begin, __initdata_end, PAGE_KERNEL,
			   &vmlinux_initdata, 0, VM_NO_GUARD);
	map_kernel_segment(pgdp, _data, _end, PAGE_KERNEL, &vmlinux_data, 0, 0);

	अगर (!READ_ONCE(pgd_val(*pgd_offset_pgd(pgdp, FIXADDR_START)))) अणु
		/*
		 * The fixmap falls in a separate pgd to the kernel, and करोesn't
		 * live in the carveout क्रम the swapper_pg_dir. We can simply
		 * re-use the existing dir क्रम the fixmap.
		 */
		set_pgd(pgd_offset_pgd(pgdp, FIXADDR_START),
			READ_ONCE(*pgd_offset_k(FIXADDR_START)));
	पूर्ण अन्यथा अगर (CONFIG_PGTABLE_LEVELS > 3) अणु
		pgd_t *bm_pgdp;
		p4d_t *bm_p4dp;
		pud_t *bm_pudp;
		/*
		 * The fixmap shares its top level pgd entry with the kernel
		 * mapping. This can really only occur when we are running
		 * with 16k/4 levels, so we can simply reuse the pud level
		 * entry instead.
		 */
		BUG_ON(!IS_ENABLED(CONFIG_ARM64_16K_PAGES));
		bm_pgdp = pgd_offset_pgd(pgdp, FIXADDR_START);
		bm_p4dp = p4d_offset(bm_pgdp, FIXADDR_START);
		bm_pudp = pud_set_fixmap_offset(bm_p4dp, FIXADDR_START);
		pud_populate(&init_mm, bm_pudp, lm_alias(bm_pmd));
		pud_clear_fixmap();
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	kasan_copy_shaकरोw(pgdp);
पूर्ण

व्योम __init paging_init(व्योम)
अणु
	pgd_t *pgdp = pgd_set_fixmap(__pa_symbol(swapper_pg_dir));

	map_kernel(pgdp);
	map_mem(pgdp);

	pgd_clear_fixmap();

	cpu_replace_ttbr1(lm_alias(swapper_pg_dir));
	init_mm.pgd = swapper_pg_dir;

	memblock_मुक्त(__pa_symbol(init_pg_dir),
		      __pa_symbol(init_pg_end) - __pa_symbol(init_pg_dir));

	memblock_allow_resize();
पूर्ण

/*
 * Check whether a kernel address is valid (derived from arch/x86/).
 */
पूर्णांक kern_addr_valid(अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp, pud;
	pmd_t *pmdp, pmd;
	pte_t *ptep, pte;

	addr = arch_kasan_reset_tag(addr);
	अगर ((((दीर्घ)addr) >> VA_BITS) != -1UL)
		वापस 0;

	pgdp = pgd_offset_k(addr);
	अगर (pgd_none(READ_ONCE(*pgdp)))
		वापस 0;

	p4dp = p4d_offset(pgdp, addr);
	अगर (p4d_none(READ_ONCE(*p4dp)))
		वापस 0;

	pudp = pud_offset(p4dp, addr);
	pud = READ_ONCE(*pudp);
	अगर (pud_none(pud))
		वापस 0;

	अगर (pud_sect(pud))
		वापस pfn_valid(pud_pfn(pud));

	pmdp = pmd_offset(pudp, addr);
	pmd = READ_ONCE(*pmdp);
	अगर (pmd_none(pmd))
		वापस 0;

	अगर (pmd_sect(pmd))
		वापस pfn_valid(pmd_pfn(pmd));

	ptep = pte_offset_kernel(pmdp, addr);
	pte = READ_ONCE(*ptep);
	अगर (pte_none(pte))
		वापस 0;

	वापस pfn_valid(pte_pfn(pte));
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
अटल व्योम मुक्त_hotplug_page_range(काष्ठा page *page, माप_प्रकार size,
				    काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अगर (alपंचांगap) अणु
		vmem_alपंचांगap_मुक्त(alपंचांगap, size >> PAGE_SHIFT);
	पूर्ण अन्यथा अणु
		WARN_ON(PageReserved(page));
		मुक्त_pages((अचिन्हित दीर्घ)page_address(page), get_order(size));
	पूर्ण
पूर्ण

अटल व्योम मुक्त_hotplug_pgtable_page(काष्ठा page *page)
अणु
	मुक्त_hotplug_page_range(page, PAGE_SIZE, शून्य);
पूर्ण

अटल bool pgtable_range_aligned(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				  अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing,
				  अचिन्हित दीर्घ mask)
अणु
	start &= mask;
	अगर (start < न्यूनमान)
		वापस false;

	अगर (उच्चमानing) अणु
		उच्चमानing &= mask;
		अगर (!उच्चमानing)
			वापस false;
	पूर्ण

	अगर (end - 1 > उच्चमानing - 1)
		वापस false;
	वापस true;
पूर्ण

अटल व्योम unmap_hotplug_pte_range(pmd_t *pmdp, अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ end, bool मुक्त_mapped,
				    काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	pte_t *ptep, pte;

	करो अणु
		ptep = pte_offset_kernel(pmdp, addr);
		pte = READ_ONCE(*ptep);
		अगर (pte_none(pte))
			जारी;

		WARN_ON(!pte_present(pte));
		pte_clear(&init_mm, addr, ptep);
		flush_tlb_kernel_range(addr, addr + PAGE_SIZE);
		अगर (मुक्त_mapped)
			मुक्त_hotplug_page_range(pte_page(pte),
						PAGE_SIZE, alपंचांगap);
	पूर्ण जबतक (addr += PAGE_SIZE, addr < end);
पूर्ण

अटल व्योम unmap_hotplug_pmd_range(pud_t *pudp, अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ end, bool मुक्त_mapped,
				    काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ next;
	pmd_t *pmdp, pmd;

	करो अणु
		next = pmd_addr_end(addr, end);
		pmdp = pmd_offset(pudp, addr);
		pmd = READ_ONCE(*pmdp);
		अगर (pmd_none(pmd))
			जारी;

		WARN_ON(!pmd_present(pmd));
		अगर (pmd_sect(pmd)) अणु
			pmd_clear(pmdp);

			/*
			 * One TLBI should be sufficient here as the PMD_SIZE
			 * range is mapped with a single block entry.
			 */
			flush_tlb_kernel_range(addr, addr + PAGE_SIZE);
			अगर (मुक्त_mapped)
				मुक्त_hotplug_page_range(pmd_page(pmd),
							PMD_SIZE, alपंचांगap);
			जारी;
		पूर्ण
		WARN_ON(!pmd_table(pmd));
		unmap_hotplug_pte_range(pmdp, addr, next, मुक्त_mapped, alपंचांगap);
	पूर्ण जबतक (addr = next, addr < end);
पूर्ण

अटल व्योम unmap_hotplug_pud_range(p4d_t *p4dp, अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ end, bool मुक्त_mapped,
				    काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ next;
	pud_t *pudp, pud;

	करो अणु
		next = pud_addr_end(addr, end);
		pudp = pud_offset(p4dp, addr);
		pud = READ_ONCE(*pudp);
		अगर (pud_none(pud))
			जारी;

		WARN_ON(!pud_present(pud));
		अगर (pud_sect(pud)) अणु
			pud_clear(pudp);

			/*
			 * One TLBI should be sufficient here as the PUD_SIZE
			 * range is mapped with a single block entry.
			 */
			flush_tlb_kernel_range(addr, addr + PAGE_SIZE);
			अगर (मुक्त_mapped)
				मुक्त_hotplug_page_range(pud_page(pud),
							PUD_SIZE, alपंचांगap);
			जारी;
		पूर्ण
		WARN_ON(!pud_table(pud));
		unmap_hotplug_pmd_range(pudp, addr, next, मुक्त_mapped, alपंचांगap);
	पूर्ण जबतक (addr = next, addr < end);
पूर्ण

अटल व्योम unmap_hotplug_p4d_range(pgd_t *pgdp, अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ end, bool मुक्त_mapped,
				    काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ next;
	p4d_t *p4dp, p4d;

	करो अणु
		next = p4d_addr_end(addr, end);
		p4dp = p4d_offset(pgdp, addr);
		p4d = READ_ONCE(*p4dp);
		अगर (p4d_none(p4d))
			जारी;

		WARN_ON(!p4d_present(p4d));
		unmap_hotplug_pud_range(p4dp, addr, next, मुक्त_mapped, alपंचांगap);
	पूर्ण जबतक (addr = next, addr < end);
पूर्ण

अटल व्योम unmap_hotplug_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				bool मुक्त_mapped, काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ next;
	pgd_t *pgdp, pgd;

	/*
	 * alपंचांगap can only be used as vmemmap mapping backing memory.
	 * In हाल the backing memory itself is not being मुक्तd, then
	 * alपंचांगap is irrelevant. Warn about this inconsistency when
	 * encountered.
	 */
	WARN_ON(!मुक्त_mapped && alपंचांगap);

	करो अणु
		next = pgd_addr_end(addr, end);
		pgdp = pgd_offset_k(addr);
		pgd = READ_ONCE(*pgdp);
		अगर (pgd_none(pgd))
			जारी;

		WARN_ON(!pgd_present(pgd));
		unmap_hotplug_p4d_range(pgdp, addr, next, मुक्त_mapped, alपंचांगap);
	पूर्ण जबतक (addr = next, addr < end);
पूर्ण

अटल व्योम मुक्त_empty_pte_table(pmd_t *pmdp, अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ end, अचिन्हित दीर्घ न्यूनमान,
				 अचिन्हित दीर्घ उच्चमानing)
अणु
	pte_t *ptep, pte;
	अचिन्हित दीर्घ i, start = addr;

	करो अणु
		ptep = pte_offset_kernel(pmdp, addr);
		pte = READ_ONCE(*ptep);

		/*
		 * This is just a sanity check here which verअगरies that
		 * pte clearing has been करोne by earlier unmap loops.
		 */
		WARN_ON(!pte_none(pte));
	पूर्ण जबतक (addr += PAGE_SIZE, addr < end);

	अगर (!pgtable_range_aligned(start, end, न्यूनमान, उच्चमानing, PMD_MASK))
		वापस;

	/*
	 * Check whether we can मुक्त the pte page अगर the rest of the
	 * entries are empty. Overlap with other regions have been
	 * handled by the न्यूनमान/उच्चमानing check.
	 */
	ptep = pte_offset_kernel(pmdp, 0UL);
	क्रम (i = 0; i < PTRS_PER_PTE; i++) अणु
		अगर (!pte_none(READ_ONCE(ptep[i])))
			वापस;
	पूर्ण

	pmd_clear(pmdp);
	__flush_tlb_kernel_pgtable(start);
	मुक्त_hotplug_pgtable_page(virt_to_page(ptep));
पूर्ण

अटल व्योम मुक्त_empty_pmd_table(pud_t *pudp, अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ end, अचिन्हित दीर्घ न्यूनमान,
				 अचिन्हित दीर्घ उच्चमानing)
अणु
	pmd_t *pmdp, pmd;
	अचिन्हित दीर्घ i, next, start = addr;

	करो अणु
		next = pmd_addr_end(addr, end);
		pmdp = pmd_offset(pudp, addr);
		pmd = READ_ONCE(*pmdp);
		अगर (pmd_none(pmd))
			जारी;

		WARN_ON(!pmd_present(pmd) || !pmd_table(pmd) || pmd_sect(pmd));
		मुक्त_empty_pte_table(pmdp, addr, next, न्यूनमान, उच्चमानing);
	पूर्ण जबतक (addr = next, addr < end);

	अगर (CONFIG_PGTABLE_LEVELS <= 2)
		वापस;

	अगर (!pgtable_range_aligned(start, end, न्यूनमान, उच्चमानing, PUD_MASK))
		वापस;

	/*
	 * Check whether we can मुक्त the pmd page अगर the rest of the
	 * entries are empty. Overlap with other regions have been
	 * handled by the न्यूनमान/उच्चमानing check.
	 */
	pmdp = pmd_offset(pudp, 0UL);
	क्रम (i = 0; i < PTRS_PER_PMD; i++) अणु
		अगर (!pmd_none(READ_ONCE(pmdp[i])))
			वापस;
	पूर्ण

	pud_clear(pudp);
	__flush_tlb_kernel_pgtable(start);
	मुक्त_hotplug_pgtable_page(virt_to_page(pmdp));
पूर्ण

अटल व्योम मुक्त_empty_pud_table(p4d_t *p4dp, अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ end, अचिन्हित दीर्घ न्यूनमान,
				 अचिन्हित दीर्घ उच्चमानing)
अणु
	pud_t *pudp, pud;
	अचिन्हित दीर्घ i, next, start = addr;

	करो अणु
		next = pud_addr_end(addr, end);
		pudp = pud_offset(p4dp, addr);
		pud = READ_ONCE(*pudp);
		अगर (pud_none(pud))
			जारी;

		WARN_ON(!pud_present(pud) || !pud_table(pud) || pud_sect(pud));
		मुक्त_empty_pmd_table(pudp, addr, next, न्यूनमान, उच्चमानing);
	पूर्ण जबतक (addr = next, addr < end);

	अगर (CONFIG_PGTABLE_LEVELS <= 3)
		वापस;

	अगर (!pgtable_range_aligned(start, end, न्यूनमान, उच्चमानing, PGसूची_MASK))
		वापस;

	/*
	 * Check whether we can मुक्त the pud page अगर the rest of the
	 * entries are empty. Overlap with other regions have been
	 * handled by the न्यूनमान/उच्चमानing check.
	 */
	pudp = pud_offset(p4dp, 0UL);
	क्रम (i = 0; i < PTRS_PER_PUD; i++) अणु
		अगर (!pud_none(READ_ONCE(pudp[i])))
			वापस;
	पूर्ण

	p4d_clear(p4dp);
	__flush_tlb_kernel_pgtable(start);
	मुक्त_hotplug_pgtable_page(virt_to_page(pudp));
पूर्ण

अटल व्योम मुक्त_empty_p4d_table(pgd_t *pgdp, अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ end, अचिन्हित दीर्घ न्यूनमान,
				 अचिन्हित दीर्घ उच्चमानing)
अणु
	अचिन्हित दीर्घ next;
	p4d_t *p4dp, p4d;

	करो अणु
		next = p4d_addr_end(addr, end);
		p4dp = p4d_offset(pgdp, addr);
		p4d = READ_ONCE(*p4dp);
		अगर (p4d_none(p4d))
			जारी;

		WARN_ON(!p4d_present(p4d));
		मुक्त_empty_pud_table(p4dp, addr, next, न्यूनमान, उच्चमानing);
	पूर्ण जबतक (addr = next, addr < end);
पूर्ण

अटल व्योम मुक्त_empty_tables(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			      अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	अचिन्हित दीर्घ next;
	pgd_t *pgdp, pgd;

	करो अणु
		next = pgd_addr_end(addr, end);
		pgdp = pgd_offset_k(addr);
		pgd = READ_ONCE(*pgdp);
		अगर (pgd_none(pgd))
			जारी;

		WARN_ON(!pgd_present(pgd));
		मुक्त_empty_p4d_table(pgdp, addr, next, न्यूनमान, उच्चमानing);
	पूर्ण जबतक (addr = next, addr < end);
पूर्ण
#पूर्ण_अगर

#अगर !ARM64_SWAPPER_USES_SECTION_MAPS
पूर्णांक __meminit vmemmap_populate(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक node,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	WARN_ON((start < VMEMMAP_START) || (end > VMEMMAP_END));
	वापस vmemmap_populate_basepages(start, end, node, alपंचांगap);
पूर्ण
#अन्यथा	/* !ARM64_SWAPPER_USES_SECTION_MAPS */
पूर्णांक __meminit vmemmap_populate(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक node,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ addr = start;
	अचिन्हित दीर्घ next;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;

	WARN_ON((start < VMEMMAP_START) || (end > VMEMMAP_END));
	करो अणु
		next = pmd_addr_end(addr, end);

		pgdp = vmemmap_pgd_populate(addr, node);
		अगर (!pgdp)
			वापस -ENOMEM;

		p4dp = vmemmap_p4d_populate(pgdp, addr, node);
		अगर (!p4dp)
			वापस -ENOMEM;

		pudp = vmemmap_pud_populate(p4dp, addr, node);
		अगर (!pudp)
			वापस -ENOMEM;

		pmdp = pmd_offset(pudp, addr);
		अगर (pmd_none(READ_ONCE(*pmdp))) अणु
			व्योम *p = शून्य;

			p = vmemmap_alloc_block_buf(PMD_SIZE, node, alपंचांगap);
			अगर (!p) अणु
				अगर (vmemmap_populate_basepages(addr, next, node, alपंचांगap))
					वापस -ENOMEM;
				जारी;
			पूर्ण

			pmd_set_huge(pmdp, __pa(p), __pgprot(PROT_SECT_NORMAL));
		पूर्ण अन्यथा
			vmemmap_verअगरy((pte_t *)pmdp, node, addr, next);
	पूर्ण जबतक (addr = next, addr != end);

	वापस 0;
पूर्ण
#पूर्ण_अगर	/* !ARM64_SWAPPER_USES_SECTION_MAPS */
व्योम vmemmap_मुक्त(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
#अगर_घोषित CONFIG_MEMORY_HOTPLUG
	WARN_ON((start < VMEMMAP_START) || (end > VMEMMAP_END));

	unmap_hotplug_range(start, end, true, alपंचांगap);
	मुक्त_empty_tables(start, end, VMEMMAP_START, VMEMMAP_END);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत pud_t *fixmap_pud(अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgdp = pgd_offset_k(addr);
	p4d_t *p4dp = p4d_offset(pgdp, addr);
	p4d_t p4d = READ_ONCE(*p4dp);

	BUG_ON(p4d_none(p4d) || p4d_bad(p4d));

	वापस pud_offset_kimg(p4dp, addr);
पूर्ण

अटल अंतरभूत pmd_t *fixmap_pmd(अचिन्हित दीर्घ addr)
अणु
	pud_t *pudp = fixmap_pud(addr);
	pud_t pud = READ_ONCE(*pudp);

	BUG_ON(pud_none(pud) || pud_bad(pud));

	वापस pmd_offset_kimg(pudp, addr);
पूर्ण

अटल अंतरभूत pte_t *fixmap_pte(अचिन्हित दीर्घ addr)
अणु
	वापस &bm_pte[pte_index(addr)];
पूर्ण

/*
 * The p*d_populate functions call virt_to_phys implicitly so they can't be used
 * directly on kernel symbols (bm_p*d). This function is called too early to use
 * lm_alias so __p*d_populate functions must be used to populate with the
 * physical address from __pa_symbol.
 */
व्योम __init early_fixmap_init(व्योम)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp, p4d;
	pud_t *pudp;
	pmd_t *pmdp;
	अचिन्हित दीर्घ addr = FIXADDR_START;

	pgdp = pgd_offset_k(addr);
	p4dp = p4d_offset(pgdp, addr);
	p4d = READ_ONCE(*p4dp);
	अगर (CONFIG_PGTABLE_LEVELS > 3 &&
	    !(p4d_none(p4d) || p4d_page_paddr(p4d) == __pa_symbol(bm_pud))) अणु
		/*
		 * We only end up here अगर the kernel mapping and the fixmap
		 * share the top level pgd entry, which should only happen on
		 * 16k/4 levels configurations.
		 */
		BUG_ON(!IS_ENABLED(CONFIG_ARM64_16K_PAGES));
		pudp = pud_offset_kimg(p4dp, addr);
	पूर्ण अन्यथा अणु
		अगर (p4d_none(p4d))
			__p4d_populate(p4dp, __pa_symbol(bm_pud), P4D_TYPE_TABLE);
		pudp = fixmap_pud(addr);
	पूर्ण
	अगर (pud_none(READ_ONCE(*pudp)))
		__pud_populate(pudp, __pa_symbol(bm_pmd), PUD_TYPE_TABLE);
	pmdp = fixmap_pmd(addr);
	__pmd_populate(pmdp, __pa_symbol(bm_pte), PMD_TYPE_TABLE);

	/*
	 * The boot-ioremap range spans multiple pmds, क्रम which
	 * we are not prepared:
	 */
	BUILD_BUG_ON((__fix_to_virt(FIX_BTMAP_BEGIN) >> PMD_SHIFT)
		     != (__fix_to_virt(FIX_BTMAP_END) >> PMD_SHIFT));

	अगर ((pmdp != fixmap_pmd(fix_to_virt(FIX_BTMAP_BEGIN)))
	     || pmdp != fixmap_pmd(fix_to_virt(FIX_BTMAP_END))) अणु
		WARN_ON(1);
		pr_warn("pmdp %p != %p, %p\n",
			pmdp, fixmap_pmd(fix_to_virt(FIX_BTMAP_BEGIN)),
			fixmap_pmd(fix_to_virt(FIX_BTMAP_END)));
		pr_warn("fix_to_virt(FIX_BTMAP_BEGIN): %08lx\n",
			fix_to_virt(FIX_BTMAP_BEGIN));
		pr_warn("fix_to_virt(FIX_BTMAP_END):   %08lx\n",
			fix_to_virt(FIX_BTMAP_END));

		pr_warn("FIX_BTMAP_END:       %d\n", FIX_BTMAP_END);
		pr_warn("FIX_BTMAP_BEGIN:     %d\n", FIX_BTMAP_BEGIN);
	पूर्ण
पूर्ण

/*
 * Unusually, this is also called in IRQ context (ghes_iounmap_irq) so अगर we
 * ever need to use IPIs क्रम TLB broadcasting, then we're in trouble here.
 */
व्योम __set_fixmap(क्रमागत fixed_addresses idx,
			       phys_addr_t phys, pgprot_t flags)
अणु
	अचिन्हित दीर्घ addr = __fix_to_virt(idx);
	pte_t *ptep;

	BUG_ON(idx <= FIX_HOLE || idx >= __end_of_fixed_addresses);

	ptep = fixmap_pte(addr);

	अगर (pgprot_val(flags)) अणु
		set_pte(ptep, pfn_pte(phys >> PAGE_SHIFT, flags));
	पूर्ण अन्यथा अणु
		pte_clear(&init_mm, addr, ptep);
		flush_tlb_kernel_range(addr, addr+PAGE_SIZE);
	पूर्ण
पूर्ण

व्योम *__init fixmap_remap_fdt(phys_addr_t dt_phys, पूर्णांक *size, pgprot_t prot)
अणु
	स्थिर u64 dt_virt_base = __fix_to_virt(FIX_FDT);
	पूर्णांक offset;
	व्योम *dt_virt;

	/*
	 * Check whether the physical FDT address is set and meets the minimum
	 * alignment requirement. Since we are relying on MIN_FDT_ALIGN to be
	 * at least 8 bytes so that we can always access the magic and size
	 * fields of the FDT header after mapping the first chunk, द्विगुन check
	 * here अगर that is indeed the हाल.
	 */
	BUILD_BUG_ON(MIN_FDT_ALIGN < 8);
	अगर (!dt_phys || dt_phys % MIN_FDT_ALIGN)
		वापस शून्य;

	/*
	 * Make sure that the FDT region can be mapped without the need to
	 * allocate additional translation table pages, so that it is safe
	 * to call create_mapping_noalloc() this early.
	 *
	 * On 64k pages, the FDT will be mapped using PTEs, so we need to
	 * be in the same PMD as the rest of the fixmap.
	 * On 4k pages, we'll use section mappings क्रम the FDT so we only
	 * have to be in the same PUD.
	 */
	BUILD_BUG_ON(dt_virt_base % SZ_2M);

	BUILD_BUG_ON(__fix_to_virt(FIX_FDT_END) >> SWAPPER_TABLE_SHIFT !=
		     __fix_to_virt(FIX_BTMAP_BEGIN) >> SWAPPER_TABLE_SHIFT);

	offset = dt_phys % SWAPPER_BLOCK_SIZE;
	dt_virt = (व्योम *)dt_virt_base + offset;

	/* map the first chunk so we can पढ़ो the size from the header */
	create_mapping_noalloc(round_करोwn(dt_phys, SWAPPER_BLOCK_SIZE),
			dt_virt_base, SWAPPER_BLOCK_SIZE, prot);

	अगर (fdt_magic(dt_virt) != FDT_MAGIC)
		वापस शून्य;

	*size = fdt_totalsize(dt_virt);
	अगर (*size > MAX_FDT_SIZE)
		वापस शून्य;

	अगर (offset + *size > SWAPPER_BLOCK_SIZE)
		create_mapping_noalloc(round_करोwn(dt_phys, SWAPPER_BLOCK_SIZE), dt_virt_base,
			       round_up(offset + *size, SWAPPER_BLOCK_SIZE), prot);

	वापस dt_virt;
पूर्ण

पूर्णांक pud_set_huge(pud_t *pudp, phys_addr_t phys, pgprot_t prot)
अणु
	pud_t new_pud = pfn_pud(__phys_to_pfn(phys), mk_pud_sect_prot(prot));

	/* Only allow permission changes क्रम now */
	अगर (!pgattr_change_is_safe(READ_ONCE(pud_val(*pudp)),
				   pud_val(new_pud)))
		वापस 0;

	VM_BUG_ON(phys & ~PUD_MASK);
	set_pud(pudp, new_pud);
	वापस 1;
पूर्ण

पूर्णांक pmd_set_huge(pmd_t *pmdp, phys_addr_t phys, pgprot_t prot)
अणु
	pmd_t new_pmd = pfn_pmd(__phys_to_pfn(phys), mk_pmd_sect_prot(prot));

	/* Only allow permission changes क्रम now */
	अगर (!pgattr_change_is_safe(READ_ONCE(pmd_val(*pmdp)),
				   pmd_val(new_pmd)))
		वापस 0;

	VM_BUG_ON(phys & ~PMD_MASK);
	set_pmd(pmdp, new_pmd);
	वापस 1;
पूर्ण

पूर्णांक pud_clear_huge(pud_t *pudp)
अणु
	अगर (!pud_sect(READ_ONCE(*pudp)))
		वापस 0;
	pud_clear(pudp);
	वापस 1;
पूर्ण

पूर्णांक pmd_clear_huge(pmd_t *pmdp)
अणु
	अगर (!pmd_sect(READ_ONCE(*pmdp)))
		वापस 0;
	pmd_clear(pmdp);
	वापस 1;
पूर्ण

पूर्णांक pmd_मुक्त_pte_page(pmd_t *pmdp, अचिन्हित दीर्घ addr)
अणु
	pte_t *table;
	pmd_t pmd;

	pmd = READ_ONCE(*pmdp);

	अगर (!pmd_table(pmd)) अणु
		VM_WARN_ON(1);
		वापस 1;
	पूर्ण

	table = pte_offset_kernel(pmdp, addr);
	pmd_clear(pmdp);
	__flush_tlb_kernel_pgtable(addr);
	pte_मुक्त_kernel(शून्य, table);
	वापस 1;
पूर्ण

पूर्णांक pud_मुक्त_pmd_page(pud_t *pudp, अचिन्हित दीर्घ addr)
अणु
	pmd_t *table;
	pmd_t *pmdp;
	pud_t pud;
	अचिन्हित दीर्घ next, end;

	pud = READ_ONCE(*pudp);

	अगर (!pud_table(pud)) अणु
		VM_WARN_ON(1);
		वापस 1;
	पूर्ण

	table = pmd_offset(pudp, addr);
	pmdp = table;
	next = addr;
	end = addr + PUD_SIZE;
	करो अणु
		pmd_मुक्त_pte_page(pmdp, next);
	पूर्ण जबतक (pmdp++, next += PMD_SIZE, next != end);

	pud_clear(pudp);
	__flush_tlb_kernel_pgtable(addr);
	pmd_मुक्त(शून्य, table);
	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
अटल व्योम __हटाओ_pgd_mapping(pgd_t *pgdir, अचिन्हित दीर्घ start, u64 size)
अणु
	अचिन्हित दीर्घ end = start + size;

	WARN_ON(pgdir != init_mm.pgd);
	WARN_ON((start < PAGE_OFFSET) || (end > PAGE_END));

	unmap_hotplug_range(start, end, false, शून्य);
	मुक्त_empty_tables(start, end, PAGE_OFFSET, PAGE_END);
पूर्ण

काष्ठा range arch_get_mappable_range(व्योम)
अणु
	काष्ठा range mhp_range;
	u64 start_linear_pa = __pa(_PAGE_OFFSET(vabits_actual));
	u64 end_linear_pa = __pa(PAGE_END - 1);

	अगर (IS_ENABLED(CONFIG_RANDOMIZE_BASE)) अणु
		/*
		 * Check क्रम a wrap, it is possible because of अक्रमomized linear
		 * mapping the start physical address is actually bigger than
		 * the end physical address. In this हाल set start to zero
		 * because [0, end_linear_pa] range must still be able to cover
		 * all addressable physical addresses.
		 */
		अगर (start_linear_pa > end_linear_pa)
			start_linear_pa = 0;
	पूर्ण

	WARN_ON(start_linear_pa > end_linear_pa);

	/*
	 * Linear mapping region is the range [PAGE_OFFSET..(PAGE_END - 1)]
	 * accommodating both its ends but excluding PAGE_END. Max physical
	 * range which can be mapped inside this linear mapping range, must
	 * also be derived from its end poपूर्णांकs.
	 */
	mhp_range.start = start_linear_pa;
	mhp_range.end =  end_linear_pa;

	वापस mhp_range;
पूर्ण

पूर्णांक arch_add_memory(पूर्णांक nid, u64 start, u64 size,
		    काष्ठा mhp_params *params)
अणु
	पूर्णांक ret, flags = NO_EXEC_MAPPINGS;

	VM_BUG_ON(!mhp_range_allowed(start, size, true));

	/*
	 * KFENCE requires linear map to be mapped at page granularity, so that
	 * it is possible to protect/unprotect single pages in the KFENCE pool.
	 */
	अगर (rodata_full || debug_pagealloc_enabled() ||
	    IS_ENABLED(CONFIG_KFENCE))
		flags |= NO_BLOCK_MAPPINGS | NO_CONT_MAPPINGS;

	__create_pgd_mapping(swapper_pg_dir, start, __phys_to_virt(start),
			     size, params->pgprot, __pgd_pgtable_alloc,
			     flags);

	memblock_clear_nomap(start, size);

	ret = __add_pages(nid, start >> PAGE_SHIFT, size >> PAGE_SHIFT,
			   params);
	अगर (ret)
		__हटाओ_pgd_mapping(swapper_pg_dir,
				     __phys_to_virt(start), size);
	वापस ret;
पूर्ण

व्योम arch_हटाओ_memory(पूर्णांक nid, u64 start, u64 size,
			काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ start_pfn = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;

	__हटाओ_pages(start_pfn, nr_pages, alपंचांगap);
	__हटाओ_pgd_mapping(swapper_pg_dir, __phys_to_virt(start), size);
पूर्ण

/*
 * This memory hotplug notअगरier helps prevent boot memory from being
 * inadvertently हटाओd as it blocks pfn range offlining process in
 * __offline_pages(). Hence this prevents both offlining as well as
 * removal process क्रम boot memory which is initially always online.
 * In future अगर and when boot memory could be हटाओd, this notअगरier
 * should be dropped and मुक्त_hotplug_page_range() should handle any
 * reserved pages allocated during boot.
 */
अटल पूर्णांक prevent_booपंचांगem_हटाओ_notअगरier(काष्ठा notअगरier_block *nb,
					   अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा mem_section *ms;
	काष्ठा memory_notअगरy *arg = data;
	अचिन्हित दीर्घ end_pfn = arg->start_pfn + arg->nr_pages;
	अचिन्हित दीर्घ pfn = arg->start_pfn;

	अगर ((action != MEM_GOING_OFFLINE) && (action != MEM_OFFLINE))
		वापस NOTIFY_OK;

	क्रम (; pfn < end_pfn; pfn += PAGES_PER_SECTION) अणु
		अचिन्हित दीर्घ start = PFN_PHYS(pfn);
		अचिन्हित दीर्घ end = start + (1UL << PA_SECTION_SHIFT);

		ms = __pfn_to_section(pfn);
		अगर (!early_section(ms))
			जारी;

		अगर (action == MEM_GOING_OFFLINE) अणु
			/*
			 * Boot memory removal is not supported. Prevent
			 * it via blocking any attempted offline request
			 * क्रम the boot memory and just report it.
			 */
			pr_warn("Boot memory [%lx %lx] offlining attempted\n", start, end);
			वापस NOTIFY_BAD;
		पूर्ण अन्यथा अगर (action == MEM_OFFLINE) अणु
			/*
			 * This should have never happened. Boot memory
			 * offlining should have been prevented by this
			 * very notअगरier. Probably some memory removal
			 * procedure might have changed which would then
			 * require further debug.
			 */
			pr_err("Boot memory [%lx %lx] offlined\n", start, end);

			/*
			 * Core memory hotplug करोes not process a वापस
			 * code from the notअगरier क्रम MEM_OFFLINE events.
			 * The error condition has been reported. Return
			 * from here as अगर ignored.
			 */
			वापस NOTIFY_DONE;
		पूर्ण
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block prevent_booपंचांगem_हटाओ_nb = अणु
	.notअगरier_call = prevent_booपंचांगem_हटाओ_notअगरier,
पूर्ण;

/*
 * This ensures that boot memory sections on the platक्रमm are online
 * from early boot. Memory sections could not be prevented from being
 * offlined, unless क्रम some reason they are not online to begin with.
 * This helps validate the basic assumption on which the above memory
 * event notअगरier works to prevent boot memory section offlining and
 * its possible removal.
 */
अटल व्योम validate_booपंचांगem_online(व्योम)
अणु
	phys_addr_t start, end, addr;
	काष्ठा mem_section *ms;
	u64 i;

	/*
	 * Scanning across all memblock might be expensive
	 * on some big memory प्रणालीs. Hence enable this
	 * validation only with DEBUG_VM.
	 */
	अगर (!IS_ENABLED(CONFIG_DEBUG_VM))
		वापस;

	क्रम_each_mem_range(i, &start, &end) अणु
		क्रम (addr = start; addr < end; addr += (1UL << PA_SECTION_SHIFT)) अणु
			ms = __pfn_to_section(PHYS_PFN(addr));

			/*
			 * All memory ranges in the प्रणाली at this poपूर्णांक
			 * should have been marked as early sections.
			 */
			WARN_ON(!early_section(ms));

			/*
			 * Memory notअगरier mechanism here to prevent boot
			 * memory offlining depends on the fact that each
			 * early section memory on the प्रणाली is initially
			 * online. Otherwise a given memory section which
			 * is alपढ़ोy offline will be overlooked and can
			 * be हटाओd completely. Call out such sections.
			 */
			अगर (!online_section(ms))
				pr_err("Boot memory [%llx %llx] is offline, can be removed\n",
					addr, addr + (1UL << PA_SECTION_SHIFT));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init prevent_booपंचांगem_हटाओ_init(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (!IS_ENABLED(CONFIG_MEMORY_HOTREMOVE))
		वापस ret;

	validate_booपंचांगem_online();
	ret = रेजिस्टर_memory_notअगरier(&prevent_booपंचांगem_हटाओ_nb);
	अगर (ret)
		pr_err("%s: Notifier registration failed %d\n", __func__, ret);

	वापस ret;
पूर्ण
early_initcall(prevent_booपंचांगem_हटाओ_init);
#पूर्ण_अगर
