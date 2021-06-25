<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2005, Paul Mackerras, IBM Corporation.
 * Copyright 2009, Benjamin Herrenschmidt, IBM Corporation.
 * Copyright 2015-2016, Aneesh Kumar K.V, IBM Corporation.
 */

#समावेश <linux/sched.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/dma.h>

#समावेश <mm/mmu_decl.h>

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
/*
 * On Book3E CPUs, the vmemmap is currently mapped in the top half of
 * the vदो_स्मृति space using normal page tables, though the size of
 * pages encoded in the PTEs can be dअगरferent
 */
पूर्णांक __meminit vmemmap_create_mapping(अचिन्हित दीर्घ start,
				     अचिन्हित दीर्घ page_size,
				     अचिन्हित दीर्घ phys)
अणु
	/* Create a PTE encoding without page size */
	अचिन्हित दीर्घ i, flags = _PAGE_PRESENT | _PAGE_ACCESSED |
		_PAGE_KERNEL_RW;

	/* PTEs only contain page size encodings up to 32M */
	BUG_ON(mmu_psize_defs[mmu_vmemmap_psize].enc > 0xf);

	/* Encode the size in the PTE */
	flags |= mmu_psize_defs[mmu_vmemmap_psize].enc << 8;

	/* For each PTE क्रम that area, map things. Note that we करोn't
	 * increment phys because all PTEs are of the large size and
	 * thus must have the low bits clear
	 */
	क्रम (i = 0; i < page_size; i += PAGE_SIZE)
		BUG_ON(map_kernel_page(start + i, phys, __pgprot(flags)));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
व्योम vmemmap_हटाओ_mapping(अचिन्हित दीर्घ start,
			    अचिन्हित दीर्घ page_size)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_SPARSEMEM_VMEMMAP */

अटल व्योम __init *early_alloc_pgtable(अचिन्हित दीर्घ size)
अणु
	व्योम *ptr;

	ptr = memblock_alloc_try_nid(size, size, MEMBLOCK_LOW_LIMIT,
				     __pa(MAX_DMA_ADDRESS), NUMA_NO_NODE);

	अगर (!ptr)
		panic("%s: Failed to allocate %lu bytes align=0x%lx max_addr=%lx\n",
		      __func__, size, size, __pa(MAX_DMA_ADDRESS));

	वापस ptr;
पूर्ण

/*
 * map_kernel_page currently only called by __ioremap
 * map_kernel_page adds an entry to the ioremap page table
 * and adds an entry to the HPT, possibly bolting it
 */
पूर्णांक __ref map_kernel_page(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ pa, pgprot_t prot)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	BUILD_BUG_ON(TASK_SIZE_USER64 > PGTABLE_RANGE);
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
	पूर्ण अन्यथा अणु
		pgdp = pgd_offset_k(ea);
		p4dp = p4d_offset(pgdp, ea);
		अगर (p4d_none(*p4dp)) अणु
			pmdp = early_alloc_pgtable(PMD_TABLE_SIZE);
			p4d_populate(&init_mm, p4dp, pmdp);
		पूर्ण
		pudp = pud_offset(p4dp, ea);
		अगर (pud_none(*pudp)) अणु
			pmdp = early_alloc_pgtable(PMD_TABLE_SIZE);
			pud_populate(&init_mm, pudp, pmdp);
		पूर्ण
		pmdp = pmd_offset(pudp, ea);
		अगर (!pmd_present(*pmdp)) अणु
			ptep = early_alloc_pgtable(PAGE_SIZE);
			pmd_populate_kernel(&init_mm, pmdp, ptep);
		पूर्ण
		ptep = pte_offset_kernel(pmdp, ea);
	पूर्ण
	set_pte_at(&init_mm, ea, ptep, pfn_pte(pa >> PAGE_SHIFT, prot));

	smp_wmb();
	वापस 0;
पूर्ण
