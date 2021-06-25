<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file contains the routines क्रम initializing the MMU
 * on the 8xx series of chips.
 *  -- christophe
 *
 *  Derived from arch/घातerpc/mm/40x_mmu.c:
 */

#समावेश <linux/memblock.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/hugetlb.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/inst.h>

#समावेश <mm/mmu_decl.h>

#घोषणा IMMR_SIZE (FIX_IMMR_SIZE << PAGE_SHIFT)

बाह्य पूर्णांक __map_without_ltlbs;

अटल अचिन्हित दीर्घ block_mapped_ram;

/*
 * Return PA क्रम this VA अगर it is in an area mapped with LTLBs or fixmap.
 * Otherwise, वापसs 0
 */
phys_addr_t v_block_mapped(अचिन्हित दीर्घ va)
अणु
	अचिन्हित दीर्घ p = PHYS_IMMR_BASE;

	अगर (va >= VIRT_IMMR_BASE && va < VIRT_IMMR_BASE + IMMR_SIZE)
		वापस p + va - VIRT_IMMR_BASE;
	अगर (__map_without_ltlbs)
		वापस 0;
	अगर (va >= PAGE_OFFSET && va < PAGE_OFFSET + block_mapped_ram)
		वापस __pa(va);
	वापस 0;
पूर्ण

/*
 * Return VA क्रम a given PA mapped with LTLBs or fixmap
 * Return 0 अगर not mapped
 */
अचिन्हित दीर्घ p_block_mapped(phys_addr_t pa)
अणु
	अचिन्हित दीर्घ p = PHYS_IMMR_BASE;

	अगर (pa >= p && pa < p + IMMR_SIZE)
		वापस VIRT_IMMR_BASE + pa - p;
	अगर (__map_without_ltlbs)
		वापस 0;
	अगर (pa < block_mapped_ram)
		वापस (अचिन्हित दीर्घ)__va(pa);
	वापस 0;
पूर्ण

अटल pte_t __init *early_hugepd_alloc_kernel(hugepd_t *pmdp, अचिन्हित दीर्घ va)
अणु
	अगर (hpd_val(*pmdp) == 0) अणु
		pte_t *ptep = memblock_alloc(माप(pte_basic_t), SZ_4K);

		अगर (!ptep)
			वापस शून्य;

		hugepd_populate_kernel((hugepd_t *)pmdp, ptep, PAGE_SHIFT_8M);
		hugepd_populate_kernel((hugepd_t *)pmdp + 1, ptep, PAGE_SHIFT_8M);
	पूर्ण
	वापस hugepte_offset(*(hugepd_t *)pmdp, va, PGसूची_SHIFT);
पूर्ण

अटल पूर्णांक __ref __early_map_kernel_hugepage(अचिन्हित दीर्घ va, phys_addr_t pa,
					     pgprot_t prot, पूर्णांक psize, bool new)
अणु
	pmd_t *pmdp = pmd_off_k(va);
	pte_t *ptep;

	अगर (WARN_ON(psize != MMU_PAGE_512K && psize != MMU_PAGE_8M))
		वापस -EINVAL;

	अगर (new) अणु
		अगर (WARN_ON(slab_is_available()))
			वापस -EINVAL;

		अगर (psize == MMU_PAGE_512K)
			ptep = early_pte_alloc_kernel(pmdp, va);
		अन्यथा
			ptep = early_hugepd_alloc_kernel((hugepd_t *)pmdp, va);
	पूर्ण अन्यथा अणु
		अगर (psize == MMU_PAGE_512K)
			ptep = pte_offset_kernel(pmdp, va);
		अन्यथा
			ptep = hugepte_offset(*(hugepd_t *)pmdp, va, PGसूची_SHIFT);
	पूर्ण

	अगर (WARN_ON(!ptep))
		वापस -ENOMEM;

	/* The PTE should never be alपढ़ोy present */
	अगर (new && WARN_ON(pte_present(*ptep) && pgprot_val(prot)))
		वापस -EINVAL;

	set_huge_pte_at(&init_mm, va, ptep, pte_mkhuge(pfn_pte(pa >> PAGE_SHIFT, prot)));

	वापस 0;
पूर्ण

/*
 * MMU_init_hw करोes the chip-specअगरic initialization of the MMU hardware.
 */
व्योम __init MMU_init_hw(व्योम)
अणु
पूर्ण

अटल bool immr_is_mapped __initdata;

व्योम __init mmu_mapin_immr(व्योम)
अणु
	अगर (immr_is_mapped)
		वापस;

	immr_is_mapped = true;

	__early_map_kernel_hugepage(VIRT_IMMR_BASE, PHYS_IMMR_BASE,
				    PAGE_KERNEL_NCG, MMU_PAGE_512K, true);
पूर्ण

अटल व्योम mmu_mapin_ram_chunk(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ top,
				pgprot_t prot, bool new)
अणु
	अचिन्हित दीर्घ v = PAGE_OFFSET + offset;
	अचिन्हित दीर्घ p = offset;

	WARN_ON(!IS_ALIGNED(offset, SZ_512K) || !IS_ALIGNED(top, SZ_512K));

	क्रम (; p < ALIGN(p, SZ_8M) && p < top; p += SZ_512K, v += SZ_512K)
		__early_map_kernel_hugepage(v, p, prot, MMU_PAGE_512K, new);
	क्रम (; p < ALIGN_DOWN(top, SZ_8M) && p < top; p += SZ_8M, v += SZ_8M)
		__early_map_kernel_hugepage(v, p, prot, MMU_PAGE_8M, new);
	क्रम (; p < ALIGN_DOWN(top, SZ_512K) && p < top; p += SZ_512K, v += SZ_512K)
		__early_map_kernel_hugepage(v, p, prot, MMU_PAGE_512K, new);

	अगर (!new)
		flush_tlb_kernel_range(PAGE_OFFSET + v, PAGE_OFFSET + top);
पूर्ण

अचिन्हित दीर्घ __init mmu_mapin_ram(अचिन्हित दीर्घ base, अचिन्हित दीर्घ top)
अणु
	अचिन्हित दीर्घ etext8 = ALIGN(__pa(_etext), SZ_8M);
	अचिन्हित दीर्घ sinittext = __pa(_sinittext);
	bool strict_boundary = strict_kernel_rwx_enabled() || debug_pagealloc_enabled_or_kfence();
	अचिन्हित दीर्घ boundary = strict_boundary ? sinittext : etext8;
	अचिन्हित दीर्घ einittext8 = ALIGN(__pa(_einittext), SZ_8M);

	WARN_ON(top < einittext8);

	mmu_mapin_immr();

	अगर (__map_without_ltlbs)
		वापस 0;

	mmu_mapin_ram_chunk(0, boundary, PAGE_KERNEL_TEXT, true);
	अगर (debug_pagealloc_enabled_or_kfence()) अणु
		top = boundary;
	पूर्ण अन्यथा अणु
		mmu_mapin_ram_chunk(boundary, einittext8, PAGE_KERNEL_TEXT, true);
		mmu_mapin_ram_chunk(einittext8, top, PAGE_KERNEL, true);
	पूर्ण

	अगर (top > SZ_32M)
		memblock_set_current_limit(top);

	block_mapped_ram = top;

	वापस top;
पूर्ण

व्योम mmu_mark_iniपंचांगem_nx(व्योम)
अणु
	अचिन्हित दीर्घ etext8 = ALIGN(__pa(_etext), SZ_8M);
	अचिन्हित दीर्घ sinittext = __pa(_sinittext);
	अचिन्हित दीर्घ boundary = strict_kernel_rwx_enabled() ? sinittext : etext8;
	अचिन्हित दीर्घ einittext8 = ALIGN(__pa(_einittext), SZ_8M);

	mmu_mapin_ram_chunk(0, boundary, PAGE_KERNEL_TEXT, false);
	mmu_mapin_ram_chunk(boundary, einittext8, PAGE_KERNEL, false);

	mmu_pin_tlb(block_mapped_ram, false);
पूर्ण

#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
व्योम mmu_mark_rodata_ro(व्योम)
अणु
	अचिन्हित दीर्घ sinittext = __pa(_sinittext);

	mmu_mapin_ram_chunk(0, sinittext, PAGE_KERNEL_ROX, false);
	अगर (IS_ENABLED(CONFIG_PIN_TLB_DATA))
		mmu_pin_tlb(block_mapped_ram, true);
पूर्ण
#पूर्ण_अगर

व्योम __init setup_initial_memory_limit(phys_addr_t first_memblock_base,
				       phys_addr_t first_memblock_size)
अणु
	/* We करोn't currently support the first MEMBLOCK not mapping 0
	 * physical on those processors
	 */
	BUG_ON(first_memblock_base != 0);

	/* 8xx can only access 32MB at the moment */
	memblock_set_current_limit(min_t(u64, first_memblock_size, SZ_32M));
पूर्ण

/*
 * Set up to use a given MMU context.
 * id is context number, pgd is PGD poपूर्णांकer.
 *
 * We place the physical address of the new task page directory loaded
 * पूर्णांकo the MMU base रेजिस्टर, and set the ASID compare रेजिस्टर with
 * the new "context."
 */
व्योम set_context(अचिन्हित दीर्घ id, pgd_t *pgd)
अणु
	s16 offset = (s16)(__pa(swapper_pg_dir));

	/* Context चयन the PTE poपूर्णांकer क्रम the Abatron BDI2000.
	 * The PGसूची is passed as second argument.
	 */
	अगर (IS_ENABLED(CONFIG_BDI_SWITCH))
		abatron_pteptrs[1] = pgd;

	/* Register M_TWB will contain base address of level 1 table minus the
	 * lower part of the kernel PGसूची base address, so that all accesses to
	 * level 1 table are करोne relative to lower part of kernel PGसूची base
	 * address.
	 */
	mtspr(SPRN_M_TWB, __pa(pgd) - offset);

	/* Update context */
	mtspr(SPRN_M_CASID, id - 1);
	/* sync */
	mb();
पूर्ण

#अगर_घोषित CONFIG_PPC_KUEP
व्योम __init setup_kuep(bool disabled)
अणु
	अगर (disabled)
		वापस;

	pr_info("Activating Kernel Userspace Execution Prevention\n");

	mtspr(SPRN_MI_AP, MI_APG_KUEP);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_KUAP
व्योम __init setup_kuap(bool disabled)
अणु
	pr_info("Activating Kernel Userspace Access Protection\n");

	अगर (disabled)
		pr_warn("KUAP cannot be disabled yet on 8xx when compiled in\n");

	mtspr(SPRN_MD_AP, MD_APG_KUAP);
पूर्ण
#पूर्ण_अगर
