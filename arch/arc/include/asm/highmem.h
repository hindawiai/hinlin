<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ASM_HIGHMEM_H
#घोषणा _ASM_HIGHMEM_H

#अगर_घोषित CONFIG_HIGHMEM

#समावेश <uapi/यंत्र/page.h>
#समावेश <यंत्र/kmap_size.h>

#घोषणा FIXMAP_SIZE		PGसूची_SIZE
#घोषणा PKMAP_SIZE		PGसूची_SIZE

/* start after vदो_स्मृति area */
#घोषणा FIXMAP_BASE		(PAGE_OFFSET - FIXMAP_SIZE - PKMAP_SIZE)

#घोषणा FIX_KMAP_SLOTS		(KM_MAX_IDX * NR_CPUS)
#घोषणा FIX_KMAP_BEGIN		(0UL)
#घोषणा FIX_KMAP_END		((FIX_KMAP_BEGIN + FIX_KMAP_SLOTS) - 1)

#घोषणा FIXADDR_TOP		(FIXMAP_BASE + (FIX_KMAP_END << PAGE_SHIFT))

/*
 * This should be converted to the यंत्र-generic version, but of course this
 * is needlessly dअगरferent from all other architectures. Sigh - tglx
 */
#घोषणा __fix_to_virt(x)	(FIXADDR_TOP - ((x) << PAGE_SHIFT))
#घोषणा __virt_to_fix(x)	(((FIXADDR_TOP - ((x) & PAGE_MASK))) >> PAGE_SHIFT)

/* start after fixmap area */
#घोषणा PKMAP_BASE		(FIXMAP_BASE + FIXMAP_SIZE)
#घोषणा LAST_PKMAP		(PKMAP_SIZE >> PAGE_SHIFT)
#घोषणा LAST_PKMAP_MASK		(LAST_PKMAP - 1)
#घोषणा PKMAP_ADDR(nr)		(PKMAP_BASE + ((nr) << PAGE_SHIFT))
#घोषणा PKMAP_NR(virt)		(((virt) - PKMAP_BASE) >> PAGE_SHIFT)

#समावेश <यंत्र/cacheflush.h>

बाह्य व्योम kmap_init(व्योम);

#घोषणा arch_kmap_local_post_unmap(vaddr)			\
	local_flush_tlb_kernel_range(vaddr, vaddr + PAGE_SIZE)

अटल अंतरभूत व्योम flush_cache_kmaps(व्योम)
अणु
	flush_cache_all();
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
