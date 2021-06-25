<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/memblock.h>
#समावेश <linux/export.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlbflush.h>

/*
 * HIGHMEM API:
 *
 * kmap() API provides sleep semantics hence referred to as "permanent maps"
 * It allows mapping LAST_PKMAP pages, using @last_pkmap_nr as the cursor
 * क्रम book-keeping
 *
 * kmap_atomic() can't sleep (calls pagefault_disable()), thus it provides
 * लघुlived ala "temporary mappings" which historically were implemented as
 * fixmaps (compile समय addr etc). Their book-keeping is करोne per cpu.
 *
 *	Both these facts combined (preemption disabled and per-cpu allocation)
 *	means the total number of concurrent fixmaps will be limited to max
 *	such allocations in a single control path. Thus KM_TYPE_NR (another
 *	historic relic) is a small'ish number which caps max percpu fixmaps
 *
 * ARC HIGHMEM Details
 *
 * - the kernel vaddr space from 0x7z to 0x8z (currently used by vदो_स्मृति/module)
 *   is now shared between vदो_स्मृति and kmap (non overlapping though)
 *
 * - Both fixmap/pkmap use a dedicated page table each, hooked up to swapper PGD
 *   This means each only has 1 PGसूची_SIZE worth of kvaddr mappings, which means
 *   2M of kvaddr space क्रम typical config (8K page and 11:8:13 traversal split)
 *
 * - The fixed KMAP slots क्रम kmap_local/atomic() require KM_MAX_IDX slots per
 *   CPU. So the number of CPUs sharing a single PTE page is limited.
 *
 * - pkmap being preemptible, in theory could करो with more than 256 concurrent
 *   mappings. However, generic pkmap code: map_new_भव(), करोesn't traverse
 *   the PGD and only works with a single page table @pkmap_page_table, hence
 *   sets the limit
 */

बाह्य pte_t * pkmap_page_table;

अटल noअंतरभूत pte_t * __init alloc_kmap_pgtable(अचिन्हित दीर्घ kvaddr)
अणु
	pmd_t *pmd_k = pmd_off_k(kvaddr);
	pte_t *pte_k;

	pte_k = (pte_t *)memblock_alloc_low(PAGE_SIZE, PAGE_SIZE);
	अगर (!pte_k)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);

	pmd_populate_kernel(&init_mm, pmd_k, pte_k);
	वापस pte_k;
पूर्ण

व्योम __init kmap_init(व्योम)
अणु
	/* Due to recursive include hell, we can't करो this in processor.h */
	BUILD_BUG_ON(PAGE_OFFSET < (VMALLOC_END + FIXMAP_SIZE + PKMAP_SIZE));
	BUILD_BUG_ON(LAST_PKMAP > PTRS_PER_PTE);
	BUILD_BUG_ON(FIX_KMAP_SLOTS > PTRS_PER_PTE);

	pkmap_page_table = alloc_kmap_pgtable(PKMAP_BASE);
	alloc_kmap_pgtable(FIXMAP_BASE);
पूर्ण
