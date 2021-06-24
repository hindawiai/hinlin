<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * highस्मृति.स: भव kernel memory mappings क्रम high memory
 *
 * Used in CONFIG_HIGHMEM प्रणालीs क्रम memory pages which
 * are not addressable by direct kernel भव addresses.
 *
 * Copyright (C) 1999 Gerhard Wichert, Siemens AG
 *		      Gerhard.Wichert@pdb.siemens.de
 *
 *
 * Redeचिन्हित the x86 32-bit VM architecture to deal with
 * up to 16 Terabyte physical memory. With current x86 CPUs
 * we now support up to 64 Gigabytes physical RAM.
 *
 * Copyright (C) 1999 Ingo Molnar <mingo@redhat.com>
 */

#अगर_अघोषित _ASM_X86_HIGHMEM_H
#घोषणा _ASM_X86_HIGHMEM_H

#अगर_घोषित __KERNEL__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/fixmap.h>

/* declarations क्रम highmem.c */
बाह्य अचिन्हित दीर्घ highstart_pfn, highend_pfn;

/*
 * Right now we initialize only a single pte table. It can be extended
 * easily, subsequent pte tables have to be allocated in one physical
 * chunk of RAM.
 */
/*
 * Ordering is:
 *
 * high memory on:			              high_memory off:
 *    FIXADDR_TOP                                        FIXADDR_TOP
 *        fixed addresses                                    fixed addresses
 *    FIXADDR_START                                      FIXADDR_START
 *        temp fixed addresses/persistent kmap area      VMALLOC_END
 *    PKMAP_BASE                                             temp fixed addresses/vदो_स्मृति area
 *    VMALLOC_END                                        VMALLOC_START
 *        vदो_स्मृति area                                   high_memory
 *    VMALLOC_START
 *    high_memory
 *
 * The temp fixed area is only used during boot क्रम early_ioremap(), and
 * it is unused when the ioremap() is functional. vदो_स्मृति/pkmap area become
 * available after early boot so the temp fixed area is available क्रम re-use.
 */
#घोषणा LAST_PKMAP_MASK (LAST_PKMAP-1)
#घोषणा PKMAP_NR(virt)  ((virt-PKMAP_BASE) >> PAGE_SHIFT)
#घोषणा PKMAP_ADDR(nr)  (PKMAP_BASE + ((nr) << PAGE_SHIFT))

#घोषणा flush_cache_kmaps()	करो अणु पूर्ण जबतक (0)

#घोषणा	arch_kmap_local_post_map(vaddr, pteval)		\
	arch_flush_lazy_mmu_mode()

#घोषणा	arch_kmap_local_post_unmap(vaddr)		\
	करो अणु						\
		flush_tlb_one_kernel((vaddr));		\
		arch_flush_lazy_mmu_mode();		\
	पूर्ण जबतक (0)

बाह्य व्योम add_highpages_with_active_regions(पूर्णांक nid, अचिन्हित दीर्घ start_pfn,
					अचिन्हित दीर्घ end_pfn);

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_X86_HIGHMEM_H */
