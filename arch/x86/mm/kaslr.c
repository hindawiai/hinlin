<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file implements KASLR memory अक्रमomization क्रम x86_64. It अक्रमomizes
 * the भव address space of kernel memory regions (physical memory
 * mapping, vदो_स्मृति & vmemmap) क्रम x86_64. This security feature mitigates
 * exploits relying on predictable kernel addresses.
 *
 * Entropy is generated using the KASLR early boot functions now shared in
 * the lib directory (originally written by Kees Cook). Ranकरोmization is
 * करोne on PGD & P4D/PUD page table levels to increase possible addresses.
 * The physical memory mapping code was adapted to support P4D/PUD level
 * भव addresses. This implementation on the best configuration provides
 * 30,000 possible भव addresses in average क्रम each memory region.
 * An additional low memory page is used to ensure each CPU can start with
 * a PGD aligned भव address (क्रम realmode).
 *
 * The order of each memory region is not changed. The feature looks at
 * the available space क्रम the regions based on dअगरferent configuration
 * options and अक्रमomizes the base and space between each. The size of the
 * physical memory mapping is the available physical memory.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/kaslr.h>

#समावेश "mm_internal.h"

#घोषणा TB_SHIFT 40

/*
 * The end address could depend on more configuration options to make the
 * highest amount of space क्रम अक्रमomization available, but that's too hard
 * to keep straight and caused issues alपढ़ोy.
 */
अटल स्थिर अचिन्हित दीर्घ vaddr_end = CPU_ENTRY_AREA_BASE;

/*
 * Memory regions अक्रमomized by KASLR (except modules that use a separate logic
 * earlier during boot). The list is ordered based on भव addresses. This
 * order is kept after अक्रमomization.
 */
अटल __initdata काष्ठा kaslr_memory_region अणु
	अचिन्हित दीर्घ *base;
	अचिन्हित दीर्घ माप_प्रकारb;
पूर्ण kaslr_regions[] = अणु
	अणु &page_offset_base, 0 पूर्ण,
	अणु &vदो_स्मृति_base, 0 पूर्ण,
	अणु &vmemmap_base, 0 पूर्ण,
पूर्ण;

/* Get size in bytes used by the memory region */
अटल अंतरभूत अचिन्हित दीर्घ get_padding(काष्ठा kaslr_memory_region *region)
अणु
	वापस (region->माप_प्रकारb << TB_SHIFT);
पूर्ण

/* Initialize base and padding क्रम each memory region अक्रमomized with KASLR */
व्योम __init kernel_अक्रमomize_memory(व्योम)
अणु
	माप_प्रकार i;
	अचिन्हित दीर्घ vaddr_start, vaddr;
	अचिन्हित दीर्घ अक्रम, memory_tb;
	काष्ठा rnd_state अक्रम_state;
	अचिन्हित दीर्घ reमुख्य_entropy;
	अचिन्हित दीर्घ vmemmap_size;

	vaddr_start = pgtable_l5_enabled() ? __PAGE_OFFSET_BASE_L5 : __PAGE_OFFSET_BASE_L4;
	vaddr = vaddr_start;

	/*
	 * These BUILD_BUG_ON checks ensure the memory layout is consistent
	 * with the vaddr_start/vaddr_end variables. These checks are very
	 * limited....
	 */
	BUILD_BUG_ON(vaddr_start >= vaddr_end);
	BUILD_BUG_ON(vaddr_end != CPU_ENTRY_AREA_BASE);
	BUILD_BUG_ON(vaddr_end > __START_KERNEL_map);

	अगर (!kaslr_memory_enabled())
		वापस;

	kaslr_regions[0].माप_प्रकारb = 1 << (MAX_PHYSMEM_BITS - TB_SHIFT);
	kaslr_regions[1].माप_प्रकारb = VMALLOC_SIZE_TB;

	/*
	 * Update Physical memory mapping to available and
	 * add padding अगर needed (especially क्रम memory hotplug support).
	 */
	BUG_ON(kaslr_regions[0].base != &page_offset_base);
	memory_tb = DIV_ROUND_UP(max_pfn << PAGE_SHIFT, 1UL << TB_SHIFT) +
		CONFIG_RANDOMIZE_MEMORY_PHYSICAL_PADDING;

	/* Adapt physical memory region size based on available memory */
	अगर (memory_tb < kaslr_regions[0].माप_प्रकारb)
		kaslr_regions[0].माप_प्रकारb = memory_tb;

	/*
	 * Calculate the vmemmap region size in TBs, aligned to a TB
	 * boundary.
	 */
	vmemmap_size = (kaslr_regions[0].माप_प्रकारb << (TB_SHIFT - PAGE_SHIFT)) *
			माप(काष्ठा page);
	kaslr_regions[2].माप_प्रकारb = DIV_ROUND_UP(vmemmap_size, 1UL << TB_SHIFT);

	/* Calculate entropy available between regions */
	reमुख्य_entropy = vaddr_end - vaddr_start;
	क्रम (i = 0; i < ARRAY_SIZE(kaslr_regions); i++)
		reमुख्य_entropy -= get_padding(&kaslr_regions[i]);

	pअक्रमom_seed_state(&अक्रम_state, kaslr_get_अक्रमom_दीर्घ("Memory"));

	क्रम (i = 0; i < ARRAY_SIZE(kaslr_regions); i++) अणु
		अचिन्हित दीर्घ entropy;

		/*
		 * Select a अक्रमom भव address using the extra entropy
		 * available.
		 */
		entropy = reमुख्य_entropy / (ARRAY_SIZE(kaslr_regions) - i);
		pअक्रमom_bytes_state(&अक्रम_state, &अक्रम, माप(अक्रम));
		entropy = (अक्रम % (entropy + 1)) & PUD_MASK;
		vaddr += entropy;
		*kaslr_regions[i].base = vaddr;

		/*
		 * Jump the region and add a minimum padding based on
		 * अक्रमomization alignment.
		 */
		vaddr += get_padding(&kaslr_regions[i]);
		vaddr = round_up(vaddr + 1, PUD_SIZE);
		reमुख्य_entropy -= entropy;
	पूर्ण
पूर्ण

व्योम __meminit init_trampoline_kaslr(व्योम)
अणु
	pud_t *pud_page_tramp, *pud, *pud_tramp;
	p4d_t *p4d_page_tramp, *p4d, *p4d_tramp;
	अचिन्हित दीर्घ paddr, vaddr;
	pgd_t *pgd;

	pud_page_tramp = alloc_low_page();

	/*
	 * There are two mappings क्रम the low 1MB area, the direct mapping
	 * and the 1:1 mapping क्रम the real mode trampoline:
	 *
	 * Direct mapping: virt_addr = phys_addr + PAGE_OFFSET
	 * 1:1 mapping:    virt_addr = phys_addr
	 */
	paddr = 0;
	vaddr = (अचिन्हित दीर्घ)__va(paddr);
	pgd = pgd_offset_k(vaddr);

	p4d = p4d_offset(pgd, vaddr);
	pud = pud_offset(p4d, vaddr);

	pud_tramp = pud_page_tramp + pud_index(paddr);
	*pud_tramp = *pud;

	अगर (pgtable_l5_enabled()) अणु
		p4d_page_tramp = alloc_low_page();

		p4d_tramp = p4d_page_tramp + p4d_index(paddr);

		set_p4d(p4d_tramp,
			__p4d(_KERNPG_TABLE | __pa(pud_page_tramp)));

		set_pgd(&trampoline_pgd_entry,
			__pgd(_KERNPG_TABLE | __pa(p4d_page_tramp)));
	पूर्ण अन्यथा अणु
		set_pgd(&trampoline_pgd_entry,
			__pgd(_KERNPG_TABLE | __pa(pud_page_tramp)));
	पूर्ण
पूर्ण
