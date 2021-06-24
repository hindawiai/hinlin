<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_HIGHMEM_H
#घोषणा __ASM_CSKY_HIGHMEM_H

#अगर_घोषित __KERNEL__

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/kmap_size.h>
#समावेश <यंत्र/cache.h>

/* undef क्रम production */
#घोषणा HIGHMEM_DEBUG 1

/* declarations क्रम highmem.c */
बाह्य अचिन्हित दीर्घ highstart_pfn, highend_pfn;

बाह्य pte_t *pkmap_page_table;

/*
 * Right now we initialize only a single pte table. It can be extended
 * easily, subsequent pte tables have to be allocated in one physical
 * chunk of RAM.
 */
#घोषणा LAST_PKMAP 1024
#घोषणा LAST_PKMAP_MASK (LAST_PKMAP-1)
#घोषणा PKMAP_NR(virt)  ((virt-PKMAP_BASE) >> PAGE_SHIFT)
#घोषणा PKMAP_ADDR(nr)  (PKMAP_BASE + ((nr) << PAGE_SHIFT))

#घोषणा ARCH_HAS_KMAP_FLUSH_TLB
बाह्य व्योम kmap_flush_tlb(अचिन्हित दीर्घ addr);

#घोषणा flush_cache_kmaps() करो अणुपूर्ण जबतक (0)

#घोषणा arch_kmap_local_post_map(vaddr, pteval)	kmap_flush_tlb(vaddr)
#घोषणा arch_kmap_local_post_unmap(vaddr)	kmap_flush_tlb(vaddr)

बाह्य व्योम kmap_init(व्योम);

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ASM_CSKY_HIGHMEM_H */
