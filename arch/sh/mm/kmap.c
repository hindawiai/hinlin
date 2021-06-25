<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/sh/mm/kmap.c
 *
 * Copyright (C) 1999, 2000, 2002  Niibe Yutaka
 * Copyright (C) 2002 - 2009  Paul Mundt
 */
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/fs.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/module.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cacheflush.h>

अटल pte_t *kmap_coherent_pte;

व्योम __init kmap_coherent_init(व्योम)
अणु
	अचिन्हित दीर्घ vaddr;

	/* cache the first coherent kmap pte */
	vaddr = __fix_to_virt(FIX_CMAP_BEGIN);
	kmap_coherent_pte = virt_to_kpte(vaddr);
पूर्ण

व्योम *kmap_coherent(काष्ठा page *page, अचिन्हित दीर्घ addr)
अणु
	क्रमागत fixed_addresses idx;
	अचिन्हित दीर्घ vaddr;

	BUG_ON(!test_bit(PG_dcache_clean, &page->flags));

	preempt_disable();
	pagefault_disable();

	idx = FIX_CMAP_END -
		(((addr >> PAGE_SHIFT) & (FIX_N_COLOURS - 1)) +
		 (FIX_N_COLOURS * smp_processor_id()));

	vaddr = __fix_to_virt(idx);

	BUG_ON(!pte_none(*(kmap_coherent_pte - idx)));
	set_pte(kmap_coherent_pte - idx, mk_pte(page, PAGE_KERNEL));

	वापस (व्योम *)vaddr;
पूर्ण

व्योम kunmap_coherent(व्योम *kvaddr)
अणु
	अगर (kvaddr >= (व्योम *)FIXADDR_START) अणु
		अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)kvaddr & PAGE_MASK;
		क्रमागत fixed_addresses idx = __virt_to_fix(vaddr);

		/* XXX.. Kill this later, here क्रम sanity at the moment.. */
		__flush_purge_region((व्योम *)vaddr, PAGE_SIZE);

		pte_clear(&init_mm, vaddr, kmap_coherent_pte - idx);
		local_flush_tlb_one(get_asid(), vaddr);
	पूर्ण

	pagefault_enable();
	preempt_enable();
पूर्ण
