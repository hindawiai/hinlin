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
 * up to 16 Terrabyte physical memory. With current x86 CPUs
 * we now support up to 64 Gigabytes physical RAM.
 *
 * Copyright (C) 1999 Ingo Molnar <mingo@redhat.com>
 */

#अगर_अघोषित _ASM_HIGHMEM_H
#घोषणा _ASM_HIGHMEM_H

#अगर_घोषित __KERNEL__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/vaddrs.h>
#समावेश <यंत्र/pgtsrmmu.h>

/* declarations क्रम highmem.c */
बाह्य अचिन्हित दीर्घ highstart_pfn, highend_pfn;

#घोषणा kmap_prot __pgprot(SRMMU_ET_PTE | SRMMU_PRIV | SRMMU_CACHE)
बाह्य pte_t *pkmap_page_table;

/*
 * Right now we initialize only a single pte table. It can be extended
 * easily, subsequent pte tables have to be allocated in one physical
 * chunk of RAM.  Currently the simplest way to करो this is to align the
 * pkmap region on a pagetable boundary (4MB).
 */
#घोषणा LAST_PKMAP 1024
#घोषणा PKMAP_SIZE (LAST_PKMAP << PAGE_SHIFT)
#घोषणा PKMAP_BASE PMD_ALIGN(SRMMU_NOCACHE_VADDR + (SRMMU_MAX_NOCACHE_PAGES << PAGE_SHIFT))

#घोषणा LAST_PKMAP_MASK (LAST_PKMAP - 1)
#घोषणा PKMAP_NR(virt)  ((virt - PKMAP_BASE) >> PAGE_SHIFT)
#घोषणा PKMAP_ADDR(nr)  (PKMAP_BASE + ((nr) << PAGE_SHIFT))

#घोषणा PKMAP_END (PKMAP_ADDR(LAST_PKMAP))

#घोषणा flush_cache_kmaps()	flush_cache_all()

/* FIXME: Use __flush_*_one(vaddr) instead of flush_*_all() -- Anton */
#घोषणा arch_kmap_local_pre_map(vaddr, pteval)	flush_cache_all()
#घोषणा arch_kmap_local_pre_unmap(vaddr)	flush_cache_all()
#घोषणा arch_kmap_local_post_map(vaddr, pteval)	flush_tlb_all()
#घोषणा arch_kmap_local_post_unmap(vaddr)	flush_tlb_all()

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_HIGHMEM_H */
