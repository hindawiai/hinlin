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
#अगर_अघोषित _ASM_HIGHMEM_H
#घोषणा _ASM_HIGHMEM_H

#अगर_घोषित __KERNEL__

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/fixmap.h>

बाह्य pte_t *pkmap_page_table;

/*
 * Right now we initialize only a single pte table. It can be extended
 * easily, subsequent pte tables have to be allocated in one physical
 * chunk of RAM.
 */
/*
 * We use one full pte table with 4K pages. And with 16K/64K/256K pages pte
 * table covers enough memory (32MB/512MB/2GB resp.), so that both FIXMAP
 * and PKMAP can be placed in a single pte table. We use 512 pages क्रम PKMAP
 * in हाल of 16K/64K/256K page sizes.
 */

#घोषणा PKMAP_ORDER	PTE_SHIFT
#घोषणा LAST_PKMAP	(1 << PKMAP_ORDER)

#घोषणा PKMAP_BASE	((FIXADDR_START - PAGE_SIZE * (LAST_PKMAP + 1)) \
								& PMD_MASK)

#घोषणा LAST_PKMAP_MASK	(LAST_PKMAP - 1)
#घोषणा PKMAP_NR(virt)  ((virt - PKMAP_BASE) >> PAGE_SHIFT)
#घोषणा PKMAP_ADDR(nr)  (PKMAP_BASE + ((nr) << PAGE_SHIFT))

#घोषणा flush_cache_kmaps()	अणु flush_icache(); flush_dcache(); पूर्ण

#घोषणा arch_kmap_local_post_map(vaddr, pteval)	\
	local_flush_tlb_page(शून्य, vaddr);
#घोषणा arch_kmap_local_post_unmap(vaddr)	\
	local_flush_tlb_page(शून्य, vaddr);

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_HIGHMEM_H */
