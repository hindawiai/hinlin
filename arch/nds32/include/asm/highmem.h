<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित _ASM_HIGHMEM_H
#घोषणा _ASM_HIGHMEM_H

#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/fixmap.h>

/*
 * Right now we initialize only a single pte table. It can be extended
 * easily, subsequent pte tables have to be allocated in one physical
 * chunk of RAM.
 */
/*
 * Ordering is (from lower to higher memory addresses):
 *
 * high_memory
 *			Persistent kmap area
 * PKMAP_BASE
 *			fixed_addresses
 * FIXADDR_START
 * FIXADDR_TOP
 *			Vदो_स्मृति area
 * VMALLOC_START
 * VMALLOC_END
 */
#घोषणा PKMAP_BASE		((FIXADDR_START - PGसूची_SIZE) & (PGसूची_MASK))
#घोषणा LAST_PKMAP		PTRS_PER_PTE
#घोषणा LAST_PKMAP_MASK		(LAST_PKMAP - 1)
#घोषणा PKMAP_NR(virt)		(((virt) - (PKMAP_BASE)) >> PAGE_SHIFT)
#घोषणा PKMAP_ADDR(nr)		(PKMAP_BASE + ((nr) << PAGE_SHIFT))

अटल अंतरभूत व्योम flush_cache_kmaps(व्योम)
अणु
	cpu_dcache_wbinval_all();
पूर्ण

/* declarations क्रम highmem.c */
बाह्य अचिन्हित दीर्घ highstart_pfn, highend_pfn;

बाह्य pte_t *pkmap_page_table;

बाह्य व्योम kmap_init(व्योम);

/*
 * FIXME: The below looks broken vs. a kmap_atomic() in task context which
 * is पूर्णांकerupted and another kmap_atomic() happens in पूर्णांकerrupt context.
 * But what करो I know about nds32. -- tglx
 */
#घोषणा arch_kmap_local_post_map(vaddr, pteval)			\
	करो अणु							\
		__nds32__tlbop_inv(vaddr);			\
		__nds32__mtsr_dsb(vaddr, NDS32_SR_TLB_VPN);	\
		__nds32__tlbop_rwr(pteval);			\
		__nds32__isb();					\
	पूर्ण जबतक (0)

#घोषणा arch_kmap_local_pre_unmap(vaddr)			\
	करो अणु							\
		__nds32__tlbop_inv(vaddr);			\
		__nds32__isb();					\
	पूर्ण जबतक (0)

#पूर्ण_अगर
