<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1993  Linus Torvalds
 *  Support of BIGMEM added by Gerhard Wichert, Siemens AG, July 1999
 *  SMP-safe vदो_स्मृति/vमुक्त/ioremap, Tigran Aivazian <tigran@veritas.com>, May 2000
 *  Major rework to support vmap/vunmap, Christoph Hellwig, SGI, August 2002
 *  Numa awareness, Christoph Lameter, SGI, June 2005
 *  Improving global KVA allocator, Uladzislau Rezki, Sony, May 2019
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/set_memory.h>
#समावेश <linux/debugobjects.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/list.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/xarray.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/pfn.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/atomic.h>
#समावेश <linux/compiler.h>
#समावेश <linux/llist.h>
#समावेश <linux/bitops.h>
#समावेश <linux/rbtree_augmented.h>
#समावेश <linux/overflow.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/shmparam.h>

#समावेश "internal.h"
#समावेश "pgalloc-track.h"

#अगर_घोषित CONFIG_HAVE_ARCH_HUGE_VMALLOC
अटल bool __ro_after_init vmap_allow_huge = true;

अटल पूर्णांक __init set_nohugevदो_स्मृति(अक्षर *str)
अणु
	vmap_allow_huge = false;
	वापस 0;
पूर्ण
early_param("nohugevmalloc", set_nohugevदो_स्मृति);
#अन्यथा /* CONFIG_HAVE_ARCH_HUGE_VMALLOC */
अटल स्थिर bool vmap_allow_huge = false;
#पूर्ण_अगर	/* CONFIG_HAVE_ARCH_HUGE_VMALLOC */

bool is_vदो_स्मृति_addr(स्थिर व्योम *x)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)x;

	वापस addr >= VMALLOC_START && addr < VMALLOC_END;
पूर्ण
EXPORT_SYMBOL(is_vदो_स्मृति_addr);

काष्ठा vमुक्त_deferred अणु
	काष्ठा llist_head list;
	काष्ठा work_काष्ठा wq;
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा vमुक्त_deferred, vमुक्त_deferred);

अटल व्योम __vunmap(स्थिर व्योम *, पूर्णांक);

अटल व्योम मुक्त_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा vमुक्त_deferred *p = container_of(w, काष्ठा vमुक्त_deferred, wq);
	काष्ठा llist_node *t, *llnode;

	llist_क्रम_each_safe(llnode, t, llist_del_all(&p->list))
		__vunmap((व्योम *)llnode, 1);
पूर्ण

/*** Page table manipulation functions ***/
अटल पूर्णांक vmap_pte_range(pmd_t *pmd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			phys_addr_t phys_addr, pgprot_t prot,
			pgtbl_mod_mask *mask)
अणु
	pte_t *pte;
	u64 pfn;

	pfn = phys_addr >> PAGE_SHIFT;
	pte = pte_alloc_kernel_track(pmd, addr, mask);
	अगर (!pte)
		वापस -ENOMEM;
	करो अणु
		BUG_ON(!pte_none(*pte));
		set_pte_at(&init_mm, addr, pte, pfn_pte(pfn, prot));
		pfn++;
	पूर्ण जबतक (pte++, addr += PAGE_SIZE, addr != end);
	*mask |= PGTBL_PTE_MODIFIED;
	वापस 0;
पूर्ण

अटल पूर्णांक vmap_try_huge_pmd(pmd_t *pmd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			phys_addr_t phys_addr, pgprot_t prot,
			अचिन्हित पूर्णांक max_page_shअगरt)
अणु
	अगर (max_page_shअगरt < PMD_SHIFT)
		वापस 0;

	अगर (!arch_vmap_pmd_supported(prot))
		वापस 0;

	अगर ((end - addr) != PMD_SIZE)
		वापस 0;

	अगर (!IS_ALIGNED(addr, PMD_SIZE))
		वापस 0;

	अगर (!IS_ALIGNED(phys_addr, PMD_SIZE))
		वापस 0;

	अगर (pmd_present(*pmd) && !pmd_मुक्त_pte_page(pmd, addr))
		वापस 0;

	वापस pmd_set_huge(pmd, phys_addr, prot);
पूर्ण

अटल पूर्णांक vmap_pmd_range(pud_t *pud, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			phys_addr_t phys_addr, pgprot_t prot,
			अचिन्हित पूर्णांक max_page_shअगरt, pgtbl_mod_mask *mask)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;

	pmd = pmd_alloc_track(&init_mm, pud, addr, mask);
	अगर (!pmd)
		वापस -ENOMEM;
	करो अणु
		next = pmd_addr_end(addr, end);

		अगर (vmap_try_huge_pmd(pmd, addr, next, phys_addr, prot,
					max_page_shअगरt)) अणु
			*mask |= PGTBL_PMD_MODIFIED;
			जारी;
		पूर्ण

		अगर (vmap_pte_range(pmd, addr, next, phys_addr, prot, mask))
			वापस -ENOMEM;
	पूर्ण जबतक (pmd++, phys_addr += (next - addr), addr = next, addr != end);
	वापस 0;
पूर्ण

अटल पूर्णांक vmap_try_huge_pud(pud_t *pud, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			phys_addr_t phys_addr, pgprot_t prot,
			अचिन्हित पूर्णांक max_page_shअगरt)
अणु
	अगर (max_page_shअगरt < PUD_SHIFT)
		वापस 0;

	अगर (!arch_vmap_pud_supported(prot))
		वापस 0;

	अगर ((end - addr) != PUD_SIZE)
		वापस 0;

	अगर (!IS_ALIGNED(addr, PUD_SIZE))
		वापस 0;

	अगर (!IS_ALIGNED(phys_addr, PUD_SIZE))
		वापस 0;

	अगर (pud_present(*pud) && !pud_मुक्त_pmd_page(pud, addr))
		वापस 0;

	वापस pud_set_huge(pud, phys_addr, prot);
पूर्ण

अटल पूर्णांक vmap_pud_range(p4d_t *p4d, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			phys_addr_t phys_addr, pgprot_t prot,
			अचिन्हित पूर्णांक max_page_shअगरt, pgtbl_mod_mask *mask)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ next;

	pud = pud_alloc_track(&init_mm, p4d, addr, mask);
	अगर (!pud)
		वापस -ENOMEM;
	करो अणु
		next = pud_addr_end(addr, end);

		अगर (vmap_try_huge_pud(pud, addr, next, phys_addr, prot,
					max_page_shअगरt)) अणु
			*mask |= PGTBL_PUD_MODIFIED;
			जारी;
		पूर्ण

		अगर (vmap_pmd_range(pud, addr, next, phys_addr, prot,
					max_page_shअगरt, mask))
			वापस -ENOMEM;
	पूर्ण जबतक (pud++, phys_addr += (next - addr), addr = next, addr != end);
	वापस 0;
पूर्ण

अटल पूर्णांक vmap_try_huge_p4d(p4d_t *p4d, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			phys_addr_t phys_addr, pgprot_t prot,
			अचिन्हित पूर्णांक max_page_shअगरt)
अणु
	अगर (max_page_shअगरt < P4D_SHIFT)
		वापस 0;

	अगर (!arch_vmap_p4d_supported(prot))
		वापस 0;

	अगर ((end - addr) != P4D_SIZE)
		वापस 0;

	अगर (!IS_ALIGNED(addr, P4D_SIZE))
		वापस 0;

	अगर (!IS_ALIGNED(phys_addr, P4D_SIZE))
		वापस 0;

	अगर (p4d_present(*p4d) && !p4d_मुक्त_pud_page(p4d, addr))
		वापस 0;

	वापस p4d_set_huge(p4d, phys_addr, prot);
पूर्ण

अटल पूर्णांक vmap_p4d_range(pgd_t *pgd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			phys_addr_t phys_addr, pgprot_t prot,
			अचिन्हित पूर्णांक max_page_shअगरt, pgtbl_mod_mask *mask)
अणु
	p4d_t *p4d;
	अचिन्हित दीर्घ next;

	p4d = p4d_alloc_track(&init_mm, pgd, addr, mask);
	अगर (!p4d)
		वापस -ENOMEM;
	करो अणु
		next = p4d_addr_end(addr, end);

		अगर (vmap_try_huge_p4d(p4d, addr, next, phys_addr, prot,
					max_page_shअगरt)) अणु
			*mask |= PGTBL_P4D_MODIFIED;
			जारी;
		पूर्ण

		अगर (vmap_pud_range(p4d, addr, next, phys_addr, prot,
					max_page_shअगरt, mask))
			वापस -ENOMEM;
	पूर्ण जबतक (p4d++, phys_addr += (next - addr), addr = next, addr != end);
	वापस 0;
पूर्ण

अटल पूर्णांक vmap_range_noflush(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			phys_addr_t phys_addr, pgprot_t prot,
			अचिन्हित पूर्णांक max_page_shअगरt)
अणु
	pgd_t *pgd;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ next;
	पूर्णांक err;
	pgtbl_mod_mask mask = 0;

	might_sleep();
	BUG_ON(addr >= end);

	start = addr;
	pgd = pgd_offset_k(addr);
	करो अणु
		next = pgd_addr_end(addr, end);
		err = vmap_p4d_range(pgd, addr, next, phys_addr, prot,
					max_page_shअगरt, &mask);
		अगर (err)
			अवरोध;
	पूर्ण जबतक (pgd++, phys_addr += (next - addr), addr = next, addr != end);

	अगर (mask & ARCH_PAGE_TABLE_SYNC_MASK)
		arch_sync_kernel_mappings(start, end);

	वापस err;
पूर्ण

पूर्णांक vmap_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			phys_addr_t phys_addr, pgprot_t prot,
			अचिन्हित पूर्णांक max_page_shअगरt)
अणु
	पूर्णांक err;

	err = vmap_range_noflush(addr, end, phys_addr, prot, max_page_shअगरt);
	flush_cache_vmap(addr, end);

	वापस err;
पूर्ण

अटल व्योम vunmap_pte_range(pmd_t *pmd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			     pgtbl_mod_mask *mask)
अणु
	pte_t *pte;

	pte = pte_offset_kernel(pmd, addr);
	करो अणु
		pte_t ptent = ptep_get_and_clear(&init_mm, addr, pte);
		WARN_ON(!pte_none(ptent) && !pte_present(ptent));
	पूर्ण जबतक (pte++, addr += PAGE_SIZE, addr != end);
	*mask |= PGTBL_PTE_MODIFIED;
पूर्ण

अटल व्योम vunmap_pmd_range(pud_t *pud, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			     pgtbl_mod_mask *mask)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;
	पूर्णांक cleared;

	pmd = pmd_offset(pud, addr);
	करो अणु
		next = pmd_addr_end(addr, end);

		cleared = pmd_clear_huge(pmd);
		अगर (cleared || pmd_bad(*pmd))
			*mask |= PGTBL_PMD_MODIFIED;

		अगर (cleared)
			जारी;
		अगर (pmd_none_or_clear_bad(pmd))
			जारी;
		vunmap_pte_range(pmd, addr, next, mask);

		cond_resched();
	पूर्ण जबतक (pmd++, addr = next, addr != end);
पूर्ण

अटल व्योम vunmap_pud_range(p4d_t *p4d, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			     pgtbl_mod_mask *mask)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ next;
	पूर्णांक cleared;

	pud = pud_offset(p4d, addr);
	करो अणु
		next = pud_addr_end(addr, end);

		cleared = pud_clear_huge(pud);
		अगर (cleared || pud_bad(*pud))
			*mask |= PGTBL_PUD_MODIFIED;

		अगर (cleared)
			जारी;
		अगर (pud_none_or_clear_bad(pud))
			जारी;
		vunmap_pmd_range(pud, addr, next, mask);
	पूर्ण जबतक (pud++, addr = next, addr != end);
पूर्ण

अटल व्योम vunmap_p4d_range(pgd_t *pgd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			     pgtbl_mod_mask *mask)
अणु
	p4d_t *p4d;
	अचिन्हित दीर्घ next;
	पूर्णांक cleared;

	p4d = p4d_offset(pgd, addr);
	करो अणु
		next = p4d_addr_end(addr, end);

		cleared = p4d_clear_huge(p4d);
		अगर (cleared || p4d_bad(*p4d))
			*mask |= PGTBL_P4D_MODIFIED;

		अगर (cleared)
			जारी;
		अगर (p4d_none_or_clear_bad(p4d))
			जारी;
		vunmap_pud_range(p4d, addr, next, mask);
	पूर्ण जबतक (p4d++, addr = next, addr != end);
पूर्ण

/*
 * vunmap_range_noflush is similar to vunmap_range, but करोes not
 * flush caches or TLBs.
 *
 * The caller is responsible क्रम calling flush_cache_vmap() beक्रमe calling
 * this function, and flush_tlb_kernel_range after it has वापसed
 * successfully (and beक्रमe the addresses are expected to cause a page fault
 * or be re-mapped क्रम something अन्यथा, अगर TLB flushes are being delayed or
 * coalesced).
 *
 * This is an पूर्णांकernal function only. Do not use outside mm/.
 */
व्योम vunmap_range_noflush(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;
	pgd_t *pgd;
	अचिन्हित दीर्घ addr = start;
	pgtbl_mod_mask mask = 0;

	BUG_ON(addr >= end);
	pgd = pgd_offset_k(addr);
	करो अणु
		next = pgd_addr_end(addr, end);
		अगर (pgd_bad(*pgd))
			mask |= PGTBL_PGD_MODIFIED;
		अगर (pgd_none_or_clear_bad(pgd))
			जारी;
		vunmap_p4d_range(pgd, addr, next, &mask);
	पूर्ण जबतक (pgd++, addr = next, addr != end);

	अगर (mask & ARCH_PAGE_TABLE_SYNC_MASK)
		arch_sync_kernel_mappings(start, end);
पूर्ण

/**
 * vunmap_range - unmap kernel भव addresses
 * @addr: start of the VM area to unmap
 * @end: end of the VM area to unmap (non-inclusive)
 *
 * Clears any present PTEs in the भव address range, flushes TLBs and
 * caches. Any subsequent access to the address beक्रमe it has been re-mapped
 * is a kernel bug.
 */
व्योम vunmap_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
	flush_cache_vunmap(addr, end);
	vunmap_range_noflush(addr, end);
	flush_tlb_kernel_range(addr, end);
पूर्ण

अटल पूर्णांक vmap_pages_pte_range(pmd_t *pmd, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ end, pgprot_t prot, काष्ठा page **pages, पूर्णांक *nr,
		pgtbl_mod_mask *mask)
अणु
	pte_t *pte;

	/*
	 * nr is a running index पूर्णांकo the array which helps higher level
	 * callers keep track of where we're up to.
	 */

	pte = pte_alloc_kernel_track(pmd, addr, mask);
	अगर (!pte)
		वापस -ENOMEM;
	करो अणु
		काष्ठा page *page = pages[*nr];

		अगर (WARN_ON(!pte_none(*pte)))
			वापस -EBUSY;
		अगर (WARN_ON(!page))
			वापस -ENOMEM;
		set_pte_at(&init_mm, addr, pte, mk_pte(page, prot));
		(*nr)++;
	पूर्ण जबतक (pte++, addr += PAGE_SIZE, addr != end);
	*mask |= PGTBL_PTE_MODIFIED;
	वापस 0;
पूर्ण

अटल पूर्णांक vmap_pages_pmd_range(pud_t *pud, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ end, pgprot_t prot, काष्ठा page **pages, पूर्णांक *nr,
		pgtbl_mod_mask *mask)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;

	pmd = pmd_alloc_track(&init_mm, pud, addr, mask);
	अगर (!pmd)
		वापस -ENOMEM;
	करो अणु
		next = pmd_addr_end(addr, end);
		अगर (vmap_pages_pte_range(pmd, addr, next, prot, pages, nr, mask))
			वापस -ENOMEM;
	पूर्ण जबतक (pmd++, addr = next, addr != end);
	वापस 0;
पूर्ण

अटल पूर्णांक vmap_pages_pud_range(p4d_t *p4d, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ end, pgprot_t prot, काष्ठा page **pages, पूर्णांक *nr,
		pgtbl_mod_mask *mask)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ next;

	pud = pud_alloc_track(&init_mm, p4d, addr, mask);
	अगर (!pud)
		वापस -ENOMEM;
	करो अणु
		next = pud_addr_end(addr, end);
		अगर (vmap_pages_pmd_range(pud, addr, next, prot, pages, nr, mask))
			वापस -ENOMEM;
	पूर्ण जबतक (pud++, addr = next, addr != end);
	वापस 0;
पूर्ण

अटल पूर्णांक vmap_pages_p4d_range(pgd_t *pgd, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ end, pgprot_t prot, काष्ठा page **pages, पूर्णांक *nr,
		pgtbl_mod_mask *mask)
अणु
	p4d_t *p4d;
	अचिन्हित दीर्घ next;

	p4d = p4d_alloc_track(&init_mm, pgd, addr, mask);
	अगर (!p4d)
		वापस -ENOMEM;
	करो अणु
		next = p4d_addr_end(addr, end);
		अगर (vmap_pages_pud_range(p4d, addr, next, prot, pages, nr, mask))
			वापस -ENOMEM;
	पूर्ण जबतक (p4d++, addr = next, addr != end);
	वापस 0;
पूर्ण

अटल पूर्णांक vmap_small_pages_range_noflush(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		pgprot_t prot, काष्ठा page **pages)
अणु
	अचिन्हित दीर्घ start = addr;
	pgd_t *pgd;
	अचिन्हित दीर्घ next;
	पूर्णांक err = 0;
	पूर्णांक nr = 0;
	pgtbl_mod_mask mask = 0;

	BUG_ON(addr >= end);
	pgd = pgd_offset_k(addr);
	करो अणु
		next = pgd_addr_end(addr, end);
		अगर (pgd_bad(*pgd))
			mask |= PGTBL_PGD_MODIFIED;
		err = vmap_pages_p4d_range(pgd, addr, next, prot, pages, &nr, &mask);
		अगर (err)
			वापस err;
	पूर्ण जबतक (pgd++, addr = next, addr != end);

	अगर (mask & ARCH_PAGE_TABLE_SYNC_MASK)
		arch_sync_kernel_mappings(start, end);

	वापस 0;
पूर्ण

/*
 * vmap_pages_range_noflush is similar to vmap_pages_range, but करोes not
 * flush caches.
 *
 * The caller is responsible क्रम calling flush_cache_vmap() after this
 * function वापसs successfully and beक्रमe the addresses are accessed.
 *
 * This is an पूर्णांकernal function only. Do not use outside mm/.
 */
पूर्णांक vmap_pages_range_noflush(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		pgprot_t prot, काष्ठा page **pages, अचिन्हित पूर्णांक page_shअगरt)
अणु
	अचिन्हित पूर्णांक i, nr = (end - addr) >> PAGE_SHIFT;

	WARN_ON(page_shअगरt < PAGE_SHIFT);

	अगर (!IS_ENABLED(CONFIG_HAVE_ARCH_HUGE_VMALLOC) ||
			page_shअगरt == PAGE_SHIFT)
		वापस vmap_small_pages_range_noflush(addr, end, prot, pages);

	क्रम (i = 0; i < nr; i += 1U << (page_shअगरt - PAGE_SHIFT)) अणु
		पूर्णांक err;

		err = vmap_range_noflush(addr, addr + (1UL << page_shअगरt),
					__pa(page_address(pages[i])), prot,
					page_shअगरt);
		अगर (err)
			वापस err;

		addr += 1UL << page_shअगरt;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmap_pages_range - map pages to a kernel भव address
 * @addr: start of the VM area to map
 * @end: end of the VM area to map (non-inclusive)
 * @prot: page protection flags to use
 * @pages: pages to map (always PAGE_SIZE pages)
 * @page_shअगरt: maximum shअगरt that the pages may be mapped with, @pages must
 * be aligned and contiguous up to at least this shअगरt.
 *
 * RETURNS:
 * 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक vmap_pages_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		pgprot_t prot, काष्ठा page **pages, अचिन्हित पूर्णांक page_shअगरt)
अणु
	पूर्णांक err;

	err = vmap_pages_range_noflush(addr, end, prot, pages, page_shअगरt);
	flush_cache_vmap(addr, end);
	वापस err;
पूर्ण

पूर्णांक is_vदो_स्मृति_or_module_addr(स्थिर व्योम *x)
अणु
	/*
	 * ARM, x86-64 and sparc64 put modules in a special place,
	 * and fall back on vदो_स्मृति() अगर that fails. Others
	 * just put it in the vदो_स्मृति space.
	 */
#अगर defined(CONFIG_MODULES) && defined(MODULES_VADDR)
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)x;
	अगर (addr >= MODULES_VADDR && addr < MODULES_END)
		वापस 1;
#पूर्ण_अगर
	वापस is_vदो_स्मृति_addr(x);
पूर्ण

/*
 * Walk a vmap address to the काष्ठा page it maps. Huge vmap mappings will
 * वापस the tail page that corresponds to the base page address, which
 * matches small vmap mappings.
 */
काष्ठा page *vदो_स्मृति_to_page(स्थिर व्योम *vदो_स्मृति_addr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) vदो_स्मृति_addr;
	काष्ठा page *page = शून्य;
	pgd_t *pgd = pgd_offset_k(addr);
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *ptep, pte;

	/*
	 * XXX we might need to change this अगर we add VIRTUAL_BUG_ON क्रम
	 * architectures that करो not vदो_स्मृति module space
	 */
	VIRTUAL_BUG_ON(!is_vदो_स्मृति_or_module_addr(vदो_स्मृति_addr));

	अगर (pgd_none(*pgd))
		वापस शून्य;
	अगर (WARN_ON_ONCE(pgd_leaf(*pgd)))
		वापस शून्य; /* XXX: no allowance क्रम huge pgd */
	अगर (WARN_ON_ONCE(pgd_bad(*pgd)))
		वापस शून्य;

	p4d = p4d_offset(pgd, addr);
	अगर (p4d_none(*p4d))
		वापस शून्य;
	अगर (p4d_leaf(*p4d))
		वापस p4d_page(*p4d) + ((addr & ~P4D_MASK) >> PAGE_SHIFT);
	अगर (WARN_ON_ONCE(p4d_bad(*p4d)))
		वापस शून्य;

	pud = pud_offset(p4d, addr);
	अगर (pud_none(*pud))
		वापस शून्य;
	अगर (pud_leaf(*pud))
		वापस pud_page(*pud) + ((addr & ~PUD_MASK) >> PAGE_SHIFT);
	अगर (WARN_ON_ONCE(pud_bad(*pud)))
		वापस शून्य;

	pmd = pmd_offset(pud, addr);
	अगर (pmd_none(*pmd))
		वापस शून्य;
	अगर (pmd_leaf(*pmd))
		वापस pmd_page(*pmd) + ((addr & ~PMD_MASK) >> PAGE_SHIFT);
	अगर (WARN_ON_ONCE(pmd_bad(*pmd)))
		वापस शून्य;

	ptep = pte_offset_map(pmd, addr);
	pte = *ptep;
	अगर (pte_present(pte))
		page = pte_page(pte);
	pte_unmap(ptep);

	वापस page;
पूर्ण
EXPORT_SYMBOL(vदो_स्मृति_to_page);

/*
 * Map a vदो_स्मृति()-space भव address to the physical page frame number.
 */
अचिन्हित दीर्घ vदो_स्मृति_to_pfn(स्थिर व्योम *vदो_स्मृति_addr)
अणु
	वापस page_to_pfn(vदो_स्मृति_to_page(vदो_स्मृति_addr));
पूर्ण
EXPORT_SYMBOL(vदो_स्मृति_to_pfn);


/*** Global kva allocator ***/

#घोषणा DEBUG_AUGMENT_PROPAGATE_CHECK 0
#घोषणा DEBUG_AUGMENT_LOWEST_MATCH_CHECK 0


अटल DEFINE_SPINLOCK(vmap_area_lock);
अटल DEFINE_SPINLOCK(मुक्त_vmap_area_lock);
/* Export क्रम kexec only */
LIST_HEAD(vmap_area_list);
अटल काष्ठा rb_root vmap_area_root = RB_ROOT;
अटल bool vmap_initialized __पढ़ो_mostly;

अटल काष्ठा rb_root purge_vmap_area_root = RB_ROOT;
अटल LIST_HEAD(purge_vmap_area_list);
अटल DEFINE_SPINLOCK(purge_vmap_area_lock);

/*
 * This kmem_cache is used क्रम vmap_area objects. Instead of
 * allocating from slab we reuse an object from this cache to
 * make things faster. Especially in "no edge" splitting of
 * मुक्त block.
 */
अटल काष्ठा kmem_cache *vmap_area_cachep;

/*
 * This linked list is used in pair with मुक्त_vmap_area_root.
 * It gives O(1) access to prev/next to perक्रमm fast coalescing.
 */
अटल LIST_HEAD(मुक्त_vmap_area_list);

/*
 * This augment red-black tree represents the मुक्त vmap space.
 * All vmap_area objects in this tree are sorted by va->बहु_शुरू
 * address. It is used क्रम allocation and merging when a vmap
 * object is released.
 *
 * Each vmap_area node contains a maximum available मुक्त block
 * of its sub-tree, right or left. Thereक्रमe it is possible to
 * find a lowest match of मुक्त area.
 */
अटल काष्ठा rb_root मुक्त_vmap_area_root = RB_ROOT;

/*
 * Preload a CPU with one object क्रम "no edge" split हाल. The
 * aim is to get rid of allocations from the atomic context, thus
 * to use more permissive allocation masks.
 */
अटल DEFINE_PER_CPU(काष्ठा vmap_area *, ne_fit_preload_node);

अटल __always_अंतरभूत अचिन्हित दीर्घ
va_size(काष्ठा vmap_area *va)
अणु
	वापस (va->बहु_पूर्ण - va->बहु_शुरू);
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
get_subtree_max_size(काष्ठा rb_node *node)
अणु
	काष्ठा vmap_area *va;

	va = rb_entry_safe(node, काष्ठा vmap_area, rb_node);
	वापस va ? va->subtree_max_size : 0;
पूर्ण

/*
 * Gets called when हटाओ the node and rotate.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ
compute_subtree_max_size(काष्ठा vmap_area *va)
अणु
	वापस max3(va_size(va),
		get_subtree_max_size(va->rb_node.rb_left),
		get_subtree_max_size(va->rb_node.rb_right));
पूर्ण

RB_DECLARE_CALLBACKS_MAX(अटल, मुक्त_vmap_area_rb_augment_cb,
	काष्ठा vmap_area, rb_node, अचिन्हित दीर्घ, subtree_max_size, va_size)

अटल व्योम purge_vmap_area_lazy(व्योम);
अटल BLOCKING_NOTIFIER_HEAD(vmap_notअगरy_list);
अटल अचिन्हित दीर्घ lazy_max_pages(व्योम);

अटल atomic_दीर्घ_t nr_vदो_स्मृति_pages;

अचिन्हित दीर्घ vदो_स्मृति_nr_pages(व्योम)
अणु
	वापस atomic_दीर्घ_पढ़ो(&nr_vदो_स्मृति_pages);
पूर्ण

अटल काष्ठा vmap_area *__find_vmap_area(अचिन्हित दीर्घ addr)
अणु
	काष्ठा rb_node *n = vmap_area_root.rb_node;

	जबतक (n) अणु
		काष्ठा vmap_area *va;

		va = rb_entry(n, काष्ठा vmap_area, rb_node);
		अगर (addr < va->बहु_शुरू)
			n = n->rb_left;
		अन्यथा अगर (addr >= va->बहु_पूर्ण)
			n = n->rb_right;
		अन्यथा
			वापस va;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * This function वापसs back addresses of parent node
 * and its left or right link क्रम further processing.
 *
 * Otherwise शून्य is वापसed. In that हाल all further
 * steps regarding inserting of conflicting overlap range
 * have to be declined and actually considered as a bug.
 */
अटल __always_अंतरभूत काष्ठा rb_node **
find_va_links(काष्ठा vmap_area *va,
	काष्ठा rb_root *root, काष्ठा rb_node *from,
	काष्ठा rb_node **parent)
अणु
	काष्ठा vmap_area *पंचांगp_va;
	काष्ठा rb_node **link;

	अगर (root) अणु
		link = &root->rb_node;
		अगर (unlikely(!*link)) अणु
			*parent = शून्य;
			वापस link;
		पूर्ण
	पूर्ण अन्यथा अणु
		link = &from;
	पूर्ण

	/*
	 * Go to the bottom of the tree. When we hit the last poपूर्णांक
	 * we end up with parent rb_node and correct direction, i name
	 * it link, where the new va->rb_node will be attached to.
	 */
	करो अणु
		पंचांगp_va = rb_entry(*link, काष्ठा vmap_area, rb_node);

		/*
		 * During the traversal we also करो some sanity check.
		 * Trigger the BUG() अगर there are sides(left/right)
		 * or full overlaps.
		 */
		अगर (va->बहु_शुरू < पंचांगp_va->बहु_पूर्ण &&
				va->बहु_पूर्ण <= पंचांगp_va->बहु_शुरू)
			link = &(*link)->rb_left;
		अन्यथा अगर (va->बहु_पूर्ण > पंचांगp_va->बहु_शुरू &&
				va->बहु_शुरू >= पंचांगp_va->बहु_पूर्ण)
			link = &(*link)->rb_right;
		अन्यथा अणु
			WARN(1, "vmalloc bug: 0x%lx-0x%lx overlaps with 0x%lx-0x%lx\n",
				va->बहु_शुरू, va->बहु_पूर्ण, पंचांगp_va->बहु_शुरू, पंचांगp_va->बहु_पूर्ण);

			वापस शून्य;
		पूर्ण
	पूर्ण जबतक (*link);

	*parent = &पंचांगp_va->rb_node;
	वापस link;
पूर्ण

अटल __always_अंतरभूत काष्ठा list_head *
get_va_next_sibling(काष्ठा rb_node *parent, काष्ठा rb_node **link)
अणु
	काष्ठा list_head *list;

	अगर (unlikely(!parent))
		/*
		 * The red-black tree where we try to find VA neighbors
		 * beक्रमe merging or inserting is empty, i.e. it means
		 * there is no मुक्त vmap space. Normally it करोes not
		 * happen but we handle this हाल anyway.
		 */
		वापस शून्य;

	list = &rb_entry(parent, काष्ठा vmap_area, rb_node)->list;
	वापस (&parent->rb_right == link ? list->next : list);
पूर्ण

अटल __always_अंतरभूत व्योम
link_va(काष्ठा vmap_area *va, काष्ठा rb_root *root,
	काष्ठा rb_node *parent, काष्ठा rb_node **link, काष्ठा list_head *head)
अणु
	/*
	 * VA is still not in the list, but we can
	 * identअगरy its future previous list_head node.
	 */
	अगर (likely(parent)) अणु
		head = &rb_entry(parent, काष्ठा vmap_area, rb_node)->list;
		अगर (&parent->rb_right != link)
			head = head->prev;
	पूर्ण

	/* Insert to the rb-tree */
	rb_link_node(&va->rb_node, parent, link);
	अगर (root == &मुक्त_vmap_area_root) अणु
		/*
		 * Some explanation here. Just perक्रमm simple insertion
		 * to the tree. We करो not set va->subtree_max_size to
		 * its current size beक्रमe calling rb_insert_augmented().
		 * It is because of we populate the tree from the bottom
		 * to parent levels when the node _is_ in the tree.
		 *
		 * Thereक्रमe we set subtree_max_size to zero after insertion,
		 * to let __augment_tree_propagate_from() माला_दो everything to
		 * the correct order later on.
		 */
		rb_insert_augmented(&va->rb_node,
			root, &मुक्त_vmap_area_rb_augment_cb);
		va->subtree_max_size = 0;
	पूर्ण अन्यथा अणु
		rb_insert_color(&va->rb_node, root);
	पूर्ण

	/* Address-sort this list */
	list_add(&va->list, head);
पूर्ण

अटल __always_अंतरभूत व्योम
unlink_va(काष्ठा vmap_area *va, काष्ठा rb_root *root)
अणु
	अगर (WARN_ON(RB_EMPTY_NODE(&va->rb_node)))
		वापस;

	अगर (root == &मुक्त_vmap_area_root)
		rb_erase_augmented(&va->rb_node,
			root, &मुक्त_vmap_area_rb_augment_cb);
	अन्यथा
		rb_erase(&va->rb_node, root);

	list_del(&va->list);
	RB_CLEAR_NODE(&va->rb_node);
पूर्ण

#अगर DEBUG_AUGMENT_PROPAGATE_CHECK
अटल व्योम
augment_tree_propagate_check(व्योम)
अणु
	काष्ठा vmap_area *va;
	अचिन्हित दीर्घ computed_size;

	list_क्रम_each_entry(va, &मुक्त_vmap_area_list, list) अणु
		computed_size = compute_subtree_max_size(va);
		अगर (computed_size != va->subtree_max_size)
			pr_emerg("tree is corrupted: %lu, %lu\n",
				va_size(va), va->subtree_max_size);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * This function populates subtree_max_size from bottom to upper
 * levels starting from VA poपूर्णांक. The propagation must be करोne
 * when VA size is modअगरied by changing its बहु_शुरू/बहु_पूर्ण. Or
 * in हाल of newly inserting of VA to the tree.
 *
 * It means that __augment_tree_propagate_from() must be called:
 * - After VA has been inserted to the tree(मुक्त path);
 * - After VA has been shrunk(allocation path);
 * - After VA has been increased(merging path).
 *
 * Please note that, it करोes not mean that upper parent nodes
 * and their subtree_max_size are recalculated all the समय up
 * to the root node.
 *
 *       4--8
 *        /\
 *       /  \
 *      /    \
 *    2--2  8--8
 *
 * For example अगर we modअगरy the node 4, shrinking it to 2, then
 * no any modअगरication is required. If we shrink the node 2 to 1
 * its subtree_max_size is updated only, and set to 1. If we shrink
 * the node 8 to 6, then its subtree_max_size is set to 6 and parent
 * node becomes 4--6.
 */
अटल __always_अंतरभूत व्योम
augment_tree_propagate_from(काष्ठा vmap_area *va)
अणु
	/*
	 * Populate the tree from bottom towards the root until
	 * the calculated maximum available size of checked node
	 * is equal to its current one.
	 */
	मुक्त_vmap_area_rb_augment_cb_propagate(&va->rb_node, शून्य);

#अगर DEBUG_AUGMENT_PROPAGATE_CHECK
	augment_tree_propagate_check();
#पूर्ण_अगर
पूर्ण

अटल व्योम
insert_vmap_area(काष्ठा vmap_area *va,
	काष्ठा rb_root *root, काष्ठा list_head *head)
अणु
	काष्ठा rb_node **link;
	काष्ठा rb_node *parent;

	link = find_va_links(va, root, शून्य, &parent);
	अगर (link)
		link_va(va, root, parent, link, head);
पूर्ण

अटल व्योम
insert_vmap_area_augment(काष्ठा vmap_area *va,
	काष्ठा rb_node *from, काष्ठा rb_root *root,
	काष्ठा list_head *head)
अणु
	काष्ठा rb_node **link;
	काष्ठा rb_node *parent;

	अगर (from)
		link = find_va_links(va, शून्य, from, &parent);
	अन्यथा
		link = find_va_links(va, root, शून्य, &parent);

	अगर (link) अणु
		link_va(va, root, parent, link, head);
		augment_tree_propagate_from(va);
	पूर्ण
पूर्ण

/*
 * Merge de-allocated chunk of VA memory with previous
 * and next मुक्त blocks. If coalesce is not करोne a new
 * मुक्त area is inserted. If VA has been merged, it is
 * मुक्तd.
 *
 * Please note, it can वापस शून्य in हाल of overlap
 * ranges, followed by WARN() report. Despite it is a
 * buggy behaviour, a प्रणाली can be alive and keep
 * ongoing.
 */
अटल __always_अंतरभूत काष्ठा vmap_area *
merge_or_add_vmap_area(काष्ठा vmap_area *va,
	काष्ठा rb_root *root, काष्ठा list_head *head)
अणु
	काष्ठा vmap_area *sibling;
	काष्ठा list_head *next;
	काष्ठा rb_node **link;
	काष्ठा rb_node *parent;
	bool merged = false;

	/*
	 * Find a place in the tree where VA potentially will be
	 * inserted, unless it is merged with its sibling/siblings.
	 */
	link = find_va_links(va, root, शून्य, &parent);
	अगर (!link)
		वापस शून्य;

	/*
	 * Get next node of VA to check अगर merging can be करोne.
	 */
	next = get_va_next_sibling(parent, link);
	अगर (unlikely(next == शून्य))
		जाओ insert;

	/*
	 * start            end
	 * |                |
	 * |<------VA------>|<-----Next----->|
	 *                  |                |
	 *                  start            end
	 */
	अगर (next != head) अणु
		sibling = list_entry(next, काष्ठा vmap_area, list);
		अगर (sibling->बहु_शुरू == va->बहु_पूर्ण) अणु
			sibling->बहु_शुरू = va->बहु_शुरू;

			/* Free vmap_area object. */
			kmem_cache_मुक्त(vmap_area_cachep, va);

			/* Poपूर्णांक to the new merged area. */
			va = sibling;
			merged = true;
		पूर्ण
	पूर्ण

	/*
	 * start            end
	 * |                |
	 * |<-----Prev----->|<------VA------>|
	 *                  |                |
	 *                  start            end
	 */
	अगर (next->prev != head) अणु
		sibling = list_entry(next->prev, काष्ठा vmap_area, list);
		अगर (sibling->बहु_पूर्ण == va->बहु_शुरू) अणु
			/*
			 * If both neighbors are coalesced, it is important
			 * to unlink the "next" node first, followed by merging
			 * with "previous" one. Otherwise the tree might not be
			 * fully populated अगर a sibling's augmented value is
			 * "normalized" because of rotation operations.
			 */
			अगर (merged)
				unlink_va(va, root);

			sibling->बहु_पूर्ण = va->बहु_पूर्ण;

			/* Free vmap_area object. */
			kmem_cache_मुक्त(vmap_area_cachep, va);

			/* Poपूर्णांक to the new merged area. */
			va = sibling;
			merged = true;
		पूर्ण
	पूर्ण

insert:
	अगर (!merged)
		link_va(va, root, parent, link, head);

	वापस va;
पूर्ण

अटल __always_अंतरभूत काष्ठा vmap_area *
merge_or_add_vmap_area_augment(काष्ठा vmap_area *va,
	काष्ठा rb_root *root, काष्ठा list_head *head)
अणु
	va = merge_or_add_vmap_area(va, root, head);
	अगर (va)
		augment_tree_propagate_from(va);

	वापस va;
पूर्ण

अटल __always_अंतरभूत bool
is_within_this_va(काष्ठा vmap_area *va, अचिन्हित दीर्घ size,
	अचिन्हित दीर्घ align, अचिन्हित दीर्घ vstart)
अणु
	अचिन्हित दीर्घ nबहु_शुरू_addr;

	अगर (va->बहु_शुरू > vstart)
		nबहु_शुरू_addr = ALIGN(va->बहु_शुरू, align);
	अन्यथा
		nबहु_शुरू_addr = ALIGN(vstart, align);

	/* Can be overflowed due to big size or alignment. */
	अगर (nबहु_शुरू_addr + size < nबहु_शुरू_addr ||
			nबहु_शुरू_addr < vstart)
		वापस false;

	वापस (nबहु_शुरू_addr + size <= va->बहु_पूर्ण);
पूर्ण

/*
 * Find the first मुक्त block(lowest start address) in the tree,
 * that will accomplish the request corresponding to passing
 * parameters.
 */
अटल __always_अंतरभूत काष्ठा vmap_area *
find_vmap_lowest_match(अचिन्हित दीर्घ size,
	अचिन्हित दीर्घ align, अचिन्हित दीर्घ vstart)
अणु
	काष्ठा vmap_area *va;
	काष्ठा rb_node *node;
	अचिन्हित दीर्घ length;

	/* Start from the root. */
	node = मुक्त_vmap_area_root.rb_node;

	/* Adjust the search size क्रम alignment overhead. */
	length = size + align - 1;

	जबतक (node) अणु
		va = rb_entry(node, काष्ठा vmap_area, rb_node);

		अगर (get_subtree_max_size(node->rb_left) >= length &&
				vstart < va->बहु_शुरू) अणु
			node = node->rb_left;
		पूर्ण अन्यथा अणु
			अगर (is_within_this_va(va, size, align, vstart))
				वापस va;

			/*
			 * Does not make sense to go deeper towards the right
			 * sub-tree अगर it करोes not have a मुक्त block that is
			 * equal or bigger to the requested search length.
			 */
			अगर (get_subtree_max_size(node->rb_right) >= length) अणु
				node = node->rb_right;
				जारी;
			पूर्ण

			/*
			 * OK. We roll back and find the first right sub-tree,
			 * that will satisfy the search criteria. It can happen
			 * only once due to "vstart" restriction.
			 */
			जबतक ((node = rb_parent(node))) अणु
				va = rb_entry(node, काष्ठा vmap_area, rb_node);
				अगर (is_within_this_va(va, size, align, vstart))
					वापस va;

				अगर (get_subtree_max_size(node->rb_right) >= length &&
						vstart <= va->बहु_शुरू) अणु
					node = node->rb_right;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

#अगर DEBUG_AUGMENT_LOWEST_MATCH_CHECK
#समावेश <linux/अक्रमom.h>

अटल काष्ठा vmap_area *
find_vmap_lowest_linear_match(अचिन्हित दीर्घ size,
	अचिन्हित दीर्घ align, अचिन्हित दीर्घ vstart)
अणु
	काष्ठा vmap_area *va;

	list_क्रम_each_entry(va, &मुक्त_vmap_area_list, list) अणु
		अगर (!is_within_this_va(va, size, align, vstart))
			जारी;

		वापस va;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
find_vmap_lowest_match_check(अचिन्हित दीर्घ size)
अणु
	काष्ठा vmap_area *va_1, *va_2;
	अचिन्हित दीर्घ vstart;
	अचिन्हित पूर्णांक rnd;

	get_अक्रमom_bytes(&rnd, माप(rnd));
	vstart = VMALLOC_START + rnd;

	va_1 = find_vmap_lowest_match(size, 1, vstart);
	va_2 = find_vmap_lowest_linear_match(size, 1, vstart);

	अगर (va_1 != va_2)
		pr_emerg("not lowest: t: 0x%p, l: 0x%p, v: 0x%lx\n",
			va_1, va_2, vstart);
पूर्ण
#पूर्ण_अगर

क्रमागत fit_type अणु
	NOTHING_FIT = 0,
	FL_FIT_TYPE = 1,	/* full fit */
	LE_FIT_TYPE = 2,	/* left edge fit */
	RE_FIT_TYPE = 3,	/* right edge fit */
	NE_FIT_TYPE = 4		/* no edge fit */
पूर्ण;

अटल __always_अंतरभूत क्रमागत fit_type
classअगरy_va_fit_type(काष्ठा vmap_area *va,
	अचिन्हित दीर्घ nबहु_शुरू_addr, अचिन्हित दीर्घ size)
अणु
	क्रमागत fit_type type;

	/* Check अगर it is within VA. */
	अगर (nबहु_शुरू_addr < va->बहु_शुरू ||
			nबहु_शुरू_addr + size > va->बहु_पूर्ण)
		वापस NOTHING_FIT;

	/* Now classअगरy. */
	अगर (va->बहु_शुरू == nबहु_शुरू_addr) अणु
		अगर (va->बहु_पूर्ण == nबहु_शुरू_addr + size)
			type = FL_FIT_TYPE;
		अन्यथा
			type = LE_FIT_TYPE;
	पूर्ण अन्यथा अगर (va->बहु_पूर्ण == nबहु_शुरू_addr + size) अणु
		type = RE_FIT_TYPE;
	पूर्ण अन्यथा अणु
		type = NE_FIT_TYPE;
	पूर्ण

	वापस type;
पूर्ण

अटल __always_अंतरभूत पूर्णांक
adjust_va_to_fit_type(काष्ठा vmap_area *va,
	अचिन्हित दीर्घ nबहु_शुरू_addr, अचिन्हित दीर्घ size,
	क्रमागत fit_type type)
अणु
	काष्ठा vmap_area *lva = शून्य;

	अगर (type == FL_FIT_TYPE) अणु
		/*
		 * No need to split VA, it fully fits.
		 *
		 * |               |
		 * V      NVA      V
		 * |---------------|
		 */
		unlink_va(va, &मुक्त_vmap_area_root);
		kmem_cache_मुक्त(vmap_area_cachep, va);
	पूर्ण अन्यथा अगर (type == LE_FIT_TYPE) अणु
		/*
		 * Split left edge of fit VA.
		 *
		 * |       |
		 * V  NVA  V   R
		 * |-------|-------|
		 */
		va->बहु_शुरू += size;
	पूर्ण अन्यथा अगर (type == RE_FIT_TYPE) अणु
		/*
		 * Split right edge of fit VA.
		 *
		 *         |       |
		 *     L   V  NVA  V
		 * |-------|-------|
		 */
		va->बहु_पूर्ण = nबहु_शुरू_addr;
	पूर्ण अन्यथा अगर (type == NE_FIT_TYPE) अणु
		/*
		 * Split no edge of fit VA.
		 *
		 *     |       |
		 *   L V  NVA  V R
		 * |---|-------|---|
		 */
		lva = __this_cpu_xchg(ne_fit_preload_node, शून्य);
		अगर (unlikely(!lva)) अणु
			/*
			 * For percpu allocator we करो not करो any pre-allocation
			 * and leave it as it is. The reason is it most likely
			 * never ends up with NE_FIT_TYPE splitting. In हाल of
			 * percpu allocations offsets and sizes are aligned to
			 * fixed align request, i.e. RE_FIT_TYPE and FL_FIT_TYPE
			 * are its मुख्य fitting हालs.
			 *
			 * There are a few exceptions though, as an example it is
			 * a first allocation (early boot up) when we have "one"
			 * big मुक्त space that has to be split.
			 *
			 * Also we can hit this path in हाल of regular "vmap"
			 * allocations, अगर "this" current CPU was not preloaded.
			 * See the comment in alloc_vmap_area() why. If so, then
			 * GFP_NOWAIT is used instead to get an extra object क्रम
			 * split purpose. That is rare and most समय करोes not
			 * occur.
			 *
			 * What happens अगर an allocation माला_लो failed. Basically,
			 * an "overflow" path is triggered to purge lazily मुक्तd
			 * areas to मुक्त some memory, then, the "retry" path is
			 * triggered to repeat one more समय. See more details
			 * in alloc_vmap_area() function.
			 */
			lva = kmem_cache_alloc(vmap_area_cachep, GFP_NOWAIT);
			अगर (!lva)
				वापस -1;
		पूर्ण

		/*
		 * Build the reमुख्यder.
		 */
		lva->बहु_शुरू = va->बहु_शुरू;
		lva->बहु_पूर्ण = nबहु_शुरू_addr;

		/*
		 * Shrink this VA to reमुख्यing size.
		 */
		va->बहु_शुरू = nबहु_शुरू_addr + size;
	पूर्ण अन्यथा अणु
		वापस -1;
	पूर्ण

	अगर (type != FL_FIT_TYPE) अणु
		augment_tree_propagate_from(va);

		अगर (lva)	/* type == NE_FIT_TYPE */
			insert_vmap_area_augment(lva, &va->rb_node,
				&मुक्त_vmap_area_root, &मुक्त_vmap_area_list);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Returns a start address of the newly allocated area, अगर success.
 * Otherwise a vend is वापसed that indicates failure.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ
__alloc_vmap_area(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align,
	अचिन्हित दीर्घ vstart, अचिन्हित दीर्घ vend)
अणु
	अचिन्हित दीर्घ nबहु_शुरू_addr;
	काष्ठा vmap_area *va;
	क्रमागत fit_type type;
	पूर्णांक ret;

	va = find_vmap_lowest_match(size, align, vstart);
	अगर (unlikely(!va))
		वापस vend;

	अगर (va->बहु_शुरू > vstart)
		nबहु_शुरू_addr = ALIGN(va->बहु_शुरू, align);
	अन्यथा
		nबहु_शुरू_addr = ALIGN(vstart, align);

	/* Check the "vend" restriction. */
	अगर (nबहु_शुरू_addr + size > vend)
		वापस vend;

	/* Classअगरy what we have found. */
	type = classअगरy_va_fit_type(va, nबहु_शुरू_addr, size);
	अगर (WARN_ON_ONCE(type == NOTHING_FIT))
		वापस vend;

	/* Update the मुक्त vmap_area. */
	ret = adjust_va_to_fit_type(va, nबहु_शुरू_addr, size, type);
	अगर (ret)
		वापस vend;

#अगर DEBUG_AUGMENT_LOWEST_MATCH_CHECK
	find_vmap_lowest_match_check(size);
#पूर्ण_अगर

	वापस nबहु_शुरू_addr;
पूर्ण

/*
 * Free a region of KVA allocated by alloc_vmap_area
 */
अटल व्योम मुक्त_vmap_area(काष्ठा vmap_area *va)
अणु
	/*
	 * Remove from the busy tree/list.
	 */
	spin_lock(&vmap_area_lock);
	unlink_va(va, &vmap_area_root);
	spin_unlock(&vmap_area_lock);

	/*
	 * Insert/Merge it back to the मुक्त tree/list.
	 */
	spin_lock(&मुक्त_vmap_area_lock);
	merge_or_add_vmap_area_augment(va, &मुक्त_vmap_area_root, &मुक्त_vmap_area_list);
	spin_unlock(&मुक्त_vmap_area_lock);
पूर्ण

अटल अंतरभूत व्योम
preload_this_cpu_lock(spinlock_t *lock, gfp_t gfp_mask, पूर्णांक node)
अणु
	काष्ठा vmap_area *va = शून्य;

	/*
	 * Preload this CPU with one extra vmap_area object. It is used
	 * when fit type of मुक्त area is NE_FIT_TYPE. It guarantees that
	 * a CPU that करोes an allocation is preloaded.
	 *
	 * We करो it in non-atomic context, thus it allows us to use more
	 * permissive allocation masks to be more stable under low memory
	 * condition and high memory pressure.
	 */
	अगर (!this_cpu_पढ़ो(ne_fit_preload_node))
		va = kmem_cache_alloc_node(vmap_area_cachep, gfp_mask, node);

	spin_lock(lock);

	अगर (va && __this_cpu_cmpxchg(ne_fit_preload_node, शून्य, va))
		kmem_cache_मुक्त(vmap_area_cachep, va);
पूर्ण

/*
 * Allocate a region of KVA of the specअगरied size and alignment, within the
 * vstart and vend.
 */
अटल काष्ठा vmap_area *alloc_vmap_area(अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ align,
				अचिन्हित दीर्घ vstart, अचिन्हित दीर्घ vend,
				पूर्णांक node, gfp_t gfp_mask)
अणु
	काष्ठा vmap_area *va;
	अचिन्हित दीर्घ addr;
	पूर्णांक purged = 0;
	पूर्णांक ret;

	BUG_ON(!size);
	BUG_ON(offset_in_page(size));
	BUG_ON(!is_घातer_of_2(align));

	अगर (unlikely(!vmap_initialized))
		वापस ERR_PTR(-EBUSY);

	might_sleep();
	gfp_mask = gfp_mask & GFP_RECLAIM_MASK;

	va = kmem_cache_alloc_node(vmap_area_cachep, gfp_mask, node);
	अगर (unlikely(!va))
		वापस ERR_PTR(-ENOMEM);

	/*
	 * Only scan the relevant parts containing poपूर्णांकers to other objects
	 * to aव्योम false negatives.
	 */
	kmemleak_scan_area(&va->rb_node, SIZE_MAX, gfp_mask);

retry:
	preload_this_cpu_lock(&मुक्त_vmap_area_lock, gfp_mask, node);
	addr = __alloc_vmap_area(size, align, vstart, vend);
	spin_unlock(&मुक्त_vmap_area_lock);

	/*
	 * If an allocation fails, the "vend" address is
	 * वापसed. Thereक्रमe trigger the overflow path.
	 */
	अगर (unlikely(addr == vend))
		जाओ overflow;

	va->बहु_शुरू = addr;
	va->बहु_पूर्ण = addr + size;
	va->vm = शून्य;

	spin_lock(&vmap_area_lock);
	insert_vmap_area(va, &vmap_area_root, &vmap_area_list);
	spin_unlock(&vmap_area_lock);

	BUG_ON(!IS_ALIGNED(va->बहु_शुरू, align));
	BUG_ON(va->बहु_शुरू < vstart);
	BUG_ON(va->बहु_पूर्ण > vend);

	ret = kasan_populate_vदो_स्मृति(addr, size);
	अगर (ret) अणु
		मुक्त_vmap_area(va);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस va;

overflow:
	अगर (!purged) अणु
		purge_vmap_area_lazy();
		purged = 1;
		जाओ retry;
	पूर्ण

	अगर (gfpflags_allow_blocking(gfp_mask)) अणु
		अचिन्हित दीर्घ मुक्तd = 0;
		blocking_notअगरier_call_chain(&vmap_notअगरy_list, 0, &मुक्तd);
		अगर (मुक्तd > 0) अणु
			purged = 0;
			जाओ retry;
		पूर्ण
	पूर्ण

	अगर (!(gfp_mask & __GFP_NOWARN) && prपूर्णांकk_ratelimit())
		pr_warn("vmap allocation for size %lu failed: use vmalloc=<size> to increase size\n",
			size);

	kmem_cache_मुक्त(vmap_area_cachep, va);
	वापस ERR_PTR(-EBUSY);
पूर्ण

पूर्णांक रेजिस्टर_vmap_purge_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&vmap_notअगरy_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_vmap_purge_notअगरier);

पूर्णांक unरेजिस्टर_vmap_purge_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&vmap_notअगरy_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_vmap_purge_notअगरier);

/*
 * lazy_max_pages is the maximum amount of भव address space we gather up
 * beक्रमe attempting to purge with a TLB flush.
 *
 * There is a tradeoff here: a larger number will cover more kernel page tables
 * and take slightly दीर्घer to purge, but it will linearly reduce the number of
 * global TLB flushes that must be perक्रमmed. It would seem natural to scale
 * this number up linearly with the number of CPUs (because vmapping activity
 * could also scale linearly with the number of CPUs), however it is likely
 * that in practice, workloads might be स्थिरrained in other ways that mean
 * vmap activity will not scale linearly with CPUs. Also, I want to be
 * conservative and not पूर्णांकroduce a big latency on huge प्रणालीs, so go with
 * a less aggressive log scale. It will still be an improvement over the old
 * code, and it will be simple to change the scale factor अगर we find that it
 * becomes a problem on bigger प्रणालीs.
 */
अटल अचिन्हित दीर्घ lazy_max_pages(व्योम)
अणु
	अचिन्हित पूर्णांक log;

	log = fls(num_online_cpus());

	वापस log * (32UL * 1024 * 1024 / PAGE_SIZE);
पूर्ण

अटल atomic_दीर्घ_t vmap_lazy_nr = ATOMIC_LONG_INIT(0);

/*
 * Serialize vmap purging.  There is no actual critical section रक्षित
 * by this look, but we want to aव्योम concurrent calls क्रम perक्रमmance
 * reasons and to make the pcpu_get_vm_areas more deterministic.
 */
अटल DEFINE_MUTEX(vmap_purge_lock);

/* क्रम per-CPU blocks */
अटल व्योम purge_fragmented_blocks_allcpus(व्योम);

/*
 * called beक्रमe a call to iounmap() अगर the caller wants vm_area_काष्ठा's
 * immediately मुक्तd.
 */
व्योम set_iounmap_nonlazy(व्योम)
अणु
	atomic_दीर्घ_set(&vmap_lazy_nr, lazy_max_pages()+1);
पूर्ण

/*
 * Purges all lazily-मुक्तd vmap areas.
 */
अटल bool __purge_vmap_area_lazy(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ resched_threshold;
	काष्ठा list_head local_pure_list;
	काष्ठा vmap_area *va, *n_va;

	lockdep_निश्चित_held(&vmap_purge_lock);

	spin_lock(&purge_vmap_area_lock);
	purge_vmap_area_root = RB_ROOT;
	list_replace_init(&purge_vmap_area_list, &local_pure_list);
	spin_unlock(&purge_vmap_area_lock);

	अगर (unlikely(list_empty(&local_pure_list)))
		वापस false;

	start = min(start,
		list_first_entry(&local_pure_list,
			काष्ठा vmap_area, list)->बहु_शुरू);

	end = max(end,
		list_last_entry(&local_pure_list,
			काष्ठा vmap_area, list)->बहु_पूर्ण);

	flush_tlb_kernel_range(start, end);
	resched_threshold = lazy_max_pages() << 1;

	spin_lock(&मुक्त_vmap_area_lock);
	list_क्रम_each_entry_safe(va, n_va, &local_pure_list, list) अणु
		अचिन्हित दीर्घ nr = (va->बहु_पूर्ण - va->बहु_शुरू) >> PAGE_SHIFT;
		अचिन्हित दीर्घ orig_start = va->बहु_शुरू;
		अचिन्हित दीर्घ orig_end = va->बहु_पूर्ण;

		/*
		 * Finally insert or merge lazily-मुक्तd area. It is
		 * detached and there is no need to "unlink" it from
		 * anything.
		 */
		va = merge_or_add_vmap_area_augment(va, &मुक्त_vmap_area_root,
				&मुक्त_vmap_area_list);

		अगर (!va)
			जारी;

		अगर (is_vदो_स्मृति_or_module_addr((व्योम *)orig_start))
			kasan_release_vदो_स्मृति(orig_start, orig_end,
					      va->बहु_शुरू, va->बहु_पूर्ण);

		atomic_दीर्घ_sub(nr, &vmap_lazy_nr);

		अगर (atomic_दीर्घ_पढ़ो(&vmap_lazy_nr) < resched_threshold)
			cond_resched_lock(&मुक्त_vmap_area_lock);
	पूर्ण
	spin_unlock(&मुक्त_vmap_area_lock);
	वापस true;
पूर्ण

/*
 * Kick off a purge of the outstanding lazy areas. Don't bother अगर somebody
 * is alपढ़ोy purging.
 */
अटल व्योम try_purge_vmap_area_lazy(व्योम)
अणु
	अगर (mutex_trylock(&vmap_purge_lock)) अणु
		__purge_vmap_area_lazy(अच_दीर्घ_उच्च, 0);
		mutex_unlock(&vmap_purge_lock);
	पूर्ण
पूर्ण

/*
 * Kick off a purge of the outstanding lazy areas.
 */
अटल व्योम purge_vmap_area_lazy(व्योम)
अणु
	mutex_lock(&vmap_purge_lock);
	purge_fragmented_blocks_allcpus();
	__purge_vmap_area_lazy(अच_दीर्घ_उच्च, 0);
	mutex_unlock(&vmap_purge_lock);
पूर्ण

/*
 * Free a vmap area, caller ensuring that the area has been unmapped
 * and flush_cache_vunmap had been called क्रम the correct range
 * previously.
 */
अटल व्योम मुक्त_vmap_area_noflush(काष्ठा vmap_area *va)
अणु
	अचिन्हित दीर्घ nr_lazy;

	spin_lock(&vmap_area_lock);
	unlink_va(va, &vmap_area_root);
	spin_unlock(&vmap_area_lock);

	nr_lazy = atomic_दीर्घ_add_वापस((va->बहु_पूर्ण - va->बहु_शुरू) >>
				PAGE_SHIFT, &vmap_lazy_nr);

	/*
	 * Merge or place it to the purge tree/list.
	 */
	spin_lock(&purge_vmap_area_lock);
	merge_or_add_vmap_area(va,
		&purge_vmap_area_root, &purge_vmap_area_list);
	spin_unlock(&purge_vmap_area_lock);

	/* After this poपूर्णांक, we may मुक्त va at any समय */
	अगर (unlikely(nr_lazy > lazy_max_pages()))
		try_purge_vmap_area_lazy();
पूर्ण

/*
 * Free and unmap a vmap area
 */
अटल व्योम मुक्त_unmap_vmap_area(काष्ठा vmap_area *va)
अणु
	flush_cache_vunmap(va->बहु_शुरू, va->बहु_पूर्ण);
	vunmap_range_noflush(va->बहु_शुरू, va->बहु_पूर्ण);
	अगर (debug_pagealloc_enabled_अटल())
		flush_tlb_kernel_range(va->बहु_शुरू, va->बहु_पूर्ण);

	मुक्त_vmap_area_noflush(va);
पूर्ण

अटल काष्ठा vmap_area *find_vmap_area(अचिन्हित दीर्घ addr)
अणु
	काष्ठा vmap_area *va;

	spin_lock(&vmap_area_lock);
	va = __find_vmap_area(addr);
	spin_unlock(&vmap_area_lock);

	वापस va;
पूर्ण

/*** Per cpu kva allocator ***/

/*
 * vmap space is limited especially on 32 bit architectures. Ensure there is
 * room क्रम at least 16 percpu vmap blocks per CPU.
 */
/*
 * If we had a स्थिरant VMALLOC_START and VMALLOC_END, we'd like to be able
 * to #घोषणा VMALLOC_SPACE		(VMALLOC_END-VMALLOC_START). Guess
 * instead (we just need a rough idea)
 */
#अगर BITS_PER_LONG == 32
#घोषणा VMALLOC_SPACE		(128UL*1024*1024)
#अन्यथा
#घोषणा VMALLOC_SPACE		(128UL*1024*1024*1024)
#पूर्ण_अगर

#घोषणा VMALLOC_PAGES		(VMALLOC_SPACE / PAGE_SIZE)
#घोषणा VMAP_MAX_ALLOC		BITS_PER_LONG	/* 256K with 4K pages */
#घोषणा VMAP_BBMAP_BITS_MAX	1024	/* 4MB with 4K pages */
#घोषणा VMAP_BBMAP_BITS_MIN	(VMAP_MAX_ALLOC*2)
#घोषणा VMAP_MIN(x, y)		((x) < (y) ? (x) : (y)) /* can't use min() */
#घोषणा VMAP_MAX(x, y)		((x) > (y) ? (x) : (y)) /* can't use max() */
#घोषणा VMAP_BBMAP_BITS		\
		VMAP_MIN(VMAP_BBMAP_BITS_MAX,	\
		VMAP_MAX(VMAP_BBMAP_BITS_MIN,	\
			VMALLOC_PAGES / roundup_घात_of_two(NR_CPUS) / 16))

#घोषणा VMAP_BLOCK_SIZE		(VMAP_BBMAP_BITS * PAGE_SIZE)

काष्ठा vmap_block_queue अणु
	spinlock_t lock;
	काष्ठा list_head मुक्त;
पूर्ण;

काष्ठा vmap_block अणु
	spinlock_t lock;
	काष्ठा vmap_area *va;
	अचिन्हित दीर्घ मुक्त, dirty;
	अचिन्हित दीर्घ dirty_min, dirty_max; /*< dirty range */
	काष्ठा list_head मुक्त_list;
	काष्ठा rcu_head rcu_head;
	काष्ठा list_head purge;
पूर्ण;

/* Queue of मुक्त and dirty vmap blocks, क्रम allocation and flushing purposes */
अटल DEFINE_PER_CPU(काष्ठा vmap_block_queue, vmap_block_queue);

/*
 * XArray of vmap blocks, indexed by address, to quickly find a vmap block
 * in the मुक्त path. Could get rid of this अगर we change the API to वापस a
 * "cookie" from alloc, to be passed to मुक्त. But no big deal yet.
 */
अटल DEFINE_XARRAY(vmap_blocks);

/*
 * We should probably have a fallback mechanism to allocate भव memory
 * out of partially filled vmap blocks. However vmap block sizing should be
 * fairly reasonable according to the vदो_स्मृति size, so it shouldn't be a
 * big problem.
 */

अटल अचिन्हित दीर्घ addr_to_vb_idx(अचिन्हित दीर्घ addr)
अणु
	addr -= VMALLOC_START & ~(VMAP_BLOCK_SIZE-1);
	addr /= VMAP_BLOCK_SIZE;
	वापस addr;
पूर्ण

अटल व्योम *vmap_block_vaddr(अचिन्हित दीर्घ बहु_शुरू, अचिन्हित दीर्घ pages_off)
अणु
	अचिन्हित दीर्घ addr;

	addr = बहु_शुरू + (pages_off << PAGE_SHIFT);
	BUG_ON(addr_to_vb_idx(addr) != addr_to_vb_idx(बहु_शुरू));
	वापस (व्योम *)addr;
पूर्ण

/**
 * new_vmap_block - allocates new vmap_block and occupies 2^order pages in this
 *                  block. Of course pages number can't exceed VMAP_BBMAP_BITS
 * @order:    how many 2^order pages should be occupied in newly allocated block
 * @gfp_mask: flags क्रम the page level allocator
 *
 * Return: भव address in a newly allocated block or ERR_PTR(-त्रुटि_सं)
 */
अटल व्योम *new_vmap_block(अचिन्हित पूर्णांक order, gfp_t gfp_mask)
अणु
	काष्ठा vmap_block_queue *vbq;
	काष्ठा vmap_block *vb;
	काष्ठा vmap_area *va;
	अचिन्हित दीर्घ vb_idx;
	पूर्णांक node, err;
	व्योम *vaddr;

	node = numa_node_id();

	vb = kदो_स्मृति_node(माप(काष्ठा vmap_block),
			gfp_mask & GFP_RECLAIM_MASK, node);
	अगर (unlikely(!vb))
		वापस ERR_PTR(-ENOMEM);

	va = alloc_vmap_area(VMAP_BLOCK_SIZE, VMAP_BLOCK_SIZE,
					VMALLOC_START, VMALLOC_END,
					node, gfp_mask);
	अगर (IS_ERR(va)) अणु
		kमुक्त(vb);
		वापस ERR_CAST(va);
	पूर्ण

	vaddr = vmap_block_vaddr(va->बहु_शुरू, 0);
	spin_lock_init(&vb->lock);
	vb->va = va;
	/* At least something should be left मुक्त */
	BUG_ON(VMAP_BBMAP_BITS <= (1UL << order));
	vb->मुक्त = VMAP_BBMAP_BITS - (1UL << order);
	vb->dirty = 0;
	vb->dirty_min = VMAP_BBMAP_BITS;
	vb->dirty_max = 0;
	INIT_LIST_HEAD(&vb->मुक्त_list);

	vb_idx = addr_to_vb_idx(va->बहु_शुरू);
	err = xa_insert(&vmap_blocks, vb_idx, vb, gfp_mask);
	अगर (err) अणु
		kमुक्त(vb);
		मुक्त_vmap_area(va);
		वापस ERR_PTR(err);
	पूर्ण

	vbq = &get_cpu_var(vmap_block_queue);
	spin_lock(&vbq->lock);
	list_add_tail_rcu(&vb->मुक्त_list, &vbq->मुक्त);
	spin_unlock(&vbq->lock);
	put_cpu_var(vmap_block_queue);

	वापस vaddr;
पूर्ण

अटल व्योम मुक्त_vmap_block(काष्ठा vmap_block *vb)
अणु
	काष्ठा vmap_block *पंचांगp;

	पंचांगp = xa_erase(&vmap_blocks, addr_to_vb_idx(vb->va->बहु_शुरू));
	BUG_ON(पंचांगp != vb);

	मुक्त_vmap_area_noflush(vb->va);
	kमुक्त_rcu(vb, rcu_head);
पूर्ण

अटल व्योम purge_fragmented_blocks(पूर्णांक cpu)
अणु
	LIST_HEAD(purge);
	काष्ठा vmap_block *vb;
	काष्ठा vmap_block *n_vb;
	काष्ठा vmap_block_queue *vbq = &per_cpu(vmap_block_queue, cpu);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(vb, &vbq->मुक्त, मुक्त_list) अणु

		अगर (!(vb->मुक्त + vb->dirty == VMAP_BBMAP_BITS && vb->dirty != VMAP_BBMAP_BITS))
			जारी;

		spin_lock(&vb->lock);
		अगर (vb->मुक्त + vb->dirty == VMAP_BBMAP_BITS && vb->dirty != VMAP_BBMAP_BITS) अणु
			vb->मुक्त = 0; /* prevent further allocs after releasing lock */
			vb->dirty = VMAP_BBMAP_BITS; /* prevent purging it again */
			vb->dirty_min = 0;
			vb->dirty_max = VMAP_BBMAP_BITS;
			spin_lock(&vbq->lock);
			list_del_rcu(&vb->मुक्त_list);
			spin_unlock(&vbq->lock);
			spin_unlock(&vb->lock);
			list_add_tail(&vb->purge, &purge);
		पूर्ण अन्यथा
			spin_unlock(&vb->lock);
	पूर्ण
	rcu_पढ़ो_unlock();

	list_क्रम_each_entry_safe(vb, n_vb, &purge, purge) अणु
		list_del(&vb->purge);
		मुक्त_vmap_block(vb);
	पूर्ण
पूर्ण

अटल व्योम purge_fragmented_blocks_allcpus(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		purge_fragmented_blocks(cpu);
पूर्ण

अटल व्योम *vb_alloc(अचिन्हित दीर्घ size, gfp_t gfp_mask)
अणु
	काष्ठा vmap_block_queue *vbq;
	काष्ठा vmap_block *vb;
	व्योम *vaddr = शून्य;
	अचिन्हित पूर्णांक order;

	BUG_ON(offset_in_page(size));
	BUG_ON(size > PAGE_SIZE*VMAP_MAX_ALLOC);
	अगर (WARN_ON(size == 0)) अणु
		/*
		 * Allocating 0 bytes isn't what caller wants since
		 * get_order(0) वापसs funny result. Just warn and terminate
		 * early.
		 */
		वापस शून्य;
	पूर्ण
	order = get_order(size);

	rcu_पढ़ो_lock();
	vbq = &get_cpu_var(vmap_block_queue);
	list_क्रम_each_entry_rcu(vb, &vbq->मुक्त, मुक्त_list) अणु
		अचिन्हित दीर्घ pages_off;

		spin_lock(&vb->lock);
		अगर (vb->मुक्त < (1UL << order)) अणु
			spin_unlock(&vb->lock);
			जारी;
		पूर्ण

		pages_off = VMAP_BBMAP_BITS - vb->मुक्त;
		vaddr = vmap_block_vaddr(vb->va->बहु_शुरू, pages_off);
		vb->मुक्त -= 1UL << order;
		अगर (vb->मुक्त == 0) अणु
			spin_lock(&vbq->lock);
			list_del_rcu(&vb->मुक्त_list);
			spin_unlock(&vbq->lock);
		पूर्ण

		spin_unlock(&vb->lock);
		अवरोध;
	पूर्ण

	put_cpu_var(vmap_block_queue);
	rcu_पढ़ो_unlock();

	/* Allocate new block अगर nothing was found */
	अगर (!vaddr)
		vaddr = new_vmap_block(order, gfp_mask);

	वापस vaddr;
पूर्ण

अटल व्योम vb_मुक्त(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ offset;
	अचिन्हित पूर्णांक order;
	काष्ठा vmap_block *vb;

	BUG_ON(offset_in_page(size));
	BUG_ON(size > PAGE_SIZE*VMAP_MAX_ALLOC);

	flush_cache_vunmap(addr, addr + size);

	order = get_order(size);
	offset = (addr & (VMAP_BLOCK_SIZE - 1)) >> PAGE_SHIFT;
	vb = xa_load(&vmap_blocks, addr_to_vb_idx(addr));

	vunmap_range_noflush(addr, addr + size);

	अगर (debug_pagealloc_enabled_अटल())
		flush_tlb_kernel_range(addr, addr + size);

	spin_lock(&vb->lock);

	/* Expand dirty range */
	vb->dirty_min = min(vb->dirty_min, offset);
	vb->dirty_max = max(vb->dirty_max, offset + (1UL << order));

	vb->dirty += 1UL << order;
	अगर (vb->dirty == VMAP_BBMAP_BITS) अणु
		BUG_ON(vb->मुक्त);
		spin_unlock(&vb->lock);
		मुक्त_vmap_block(vb);
	पूर्ण अन्यथा
		spin_unlock(&vb->lock);
पूर्ण

अटल व्योम _vm_unmap_aliases(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक flush)
अणु
	पूर्णांक cpu;

	अगर (unlikely(!vmap_initialized))
		वापस;

	might_sleep();

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा vmap_block_queue *vbq = &per_cpu(vmap_block_queue, cpu);
		काष्ठा vmap_block *vb;

		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(vb, &vbq->मुक्त, मुक्त_list) अणु
			spin_lock(&vb->lock);
			अगर (vb->dirty && vb->dirty != VMAP_BBMAP_BITS) अणु
				अचिन्हित दीर्घ बहु_शुरू = vb->va->बहु_शुरू;
				अचिन्हित दीर्घ s, e;

				s = बहु_शुरू + (vb->dirty_min << PAGE_SHIFT);
				e = बहु_शुरू + (vb->dirty_max << PAGE_SHIFT);

				start = min(s, start);
				end   = max(e, end);

				flush = 1;
			पूर्ण
			spin_unlock(&vb->lock);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	mutex_lock(&vmap_purge_lock);
	purge_fragmented_blocks_allcpus();
	अगर (!__purge_vmap_area_lazy(start, end) && flush)
		flush_tlb_kernel_range(start, end);
	mutex_unlock(&vmap_purge_lock);
पूर्ण

/**
 * vm_unmap_aliases - unmap outstanding lazy aliases in the vmap layer
 *
 * The vmap/vदो_स्मृति layer lazily flushes kernel भव mappings primarily
 * to amortize TLB flushing overheads. What this means is that any page you
 * have now, may, in a क्रमmer lअगरe, have been mapped पूर्णांकo kernel भव
 * address by the vmap layer and so there might be some CPUs with TLB entries
 * still referencing that page (additional to the regular 1:1 kernel mapping).
 *
 * vm_unmap_aliases flushes all such lazy mappings. After it वापसs, we can
 * be sure that none of the pages we have control over will have any aliases
 * from the vmap layer.
 */
व्योम vm_unmap_aliases(व्योम)
अणु
	अचिन्हित दीर्घ start = अच_दीर्घ_उच्च, end = 0;
	पूर्णांक flush = 0;

	_vm_unmap_aliases(start, end, flush);
पूर्ण
EXPORT_SYMBOL_GPL(vm_unmap_aliases);

/**
 * vm_unmap_ram - unmap linear kernel address space set up by vm_map_ram
 * @mem: the poपूर्णांकer वापसed by vm_map_ram
 * @count: the count passed to that vm_map_ram call (cannot unmap partial)
 */
व्योम vm_unmap_ram(स्थिर व्योम *mem, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित दीर्घ size = (अचिन्हित दीर्घ)count << PAGE_SHIFT;
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)mem;
	काष्ठा vmap_area *va;

	might_sleep();
	BUG_ON(!addr);
	BUG_ON(addr < VMALLOC_START);
	BUG_ON(addr > VMALLOC_END);
	BUG_ON(!PAGE_ALIGNED(addr));

	kasan_poison_vदो_स्मृति(mem, size);

	अगर (likely(count <= VMAP_MAX_ALLOC)) अणु
		debug_check_no_locks_मुक्तd(mem, size);
		vb_मुक्त(addr, size);
		वापस;
	पूर्ण

	va = find_vmap_area(addr);
	BUG_ON(!va);
	debug_check_no_locks_मुक्तd((व्योम *)va->बहु_शुरू,
				    (va->बहु_पूर्ण - va->बहु_शुरू));
	मुक्त_unmap_vmap_area(va);
पूर्ण
EXPORT_SYMBOL(vm_unmap_ram);

/**
 * vm_map_ram - map pages linearly पूर्णांकo kernel भव address (vदो_स्मृति space)
 * @pages: an array of poपूर्णांकers to the pages to be mapped
 * @count: number of pages
 * @node: prefer to allocate data काष्ठाures on this node
 *
 * If you use this function क्रम less than VMAP_MAX_ALLOC pages, it could be
 * faster than vmap so it's good.  But अगर you mix दीर्घ-lअगरe and लघु-lअगरe
 * objects with vm_map_ram(), it could consume lots of address space through
 * fragmentation (especially on a 32bit machine).  You could see failures in
 * the end.  Please use this function क्रम लघु-lived objects.
 *
 * Returns: a poपूर्णांकer to the address that has been mapped, or %शून्य on failure
 */
व्योम *vm_map_ram(काष्ठा page **pages, अचिन्हित पूर्णांक count, पूर्णांक node)
अणु
	अचिन्हित दीर्घ size = (अचिन्हित दीर्घ)count << PAGE_SHIFT;
	अचिन्हित दीर्घ addr;
	व्योम *mem;

	अगर (likely(count <= VMAP_MAX_ALLOC)) अणु
		mem = vb_alloc(size, GFP_KERNEL);
		अगर (IS_ERR(mem))
			वापस शून्य;
		addr = (अचिन्हित दीर्घ)mem;
	पूर्ण अन्यथा अणु
		काष्ठा vmap_area *va;
		va = alloc_vmap_area(size, PAGE_SIZE,
				VMALLOC_START, VMALLOC_END, node, GFP_KERNEL);
		अगर (IS_ERR(va))
			वापस शून्य;

		addr = va->बहु_शुरू;
		mem = (व्योम *)addr;
	पूर्ण

	kasan_unpoison_vदो_स्मृति(mem, size);

	अगर (vmap_pages_range(addr, addr + size, PAGE_KERNEL,
				pages, PAGE_SHIFT) < 0) अणु
		vm_unmap_ram(mem, count);
		वापस शून्य;
	पूर्ण

	वापस mem;
पूर्ण
EXPORT_SYMBOL(vm_map_ram);

अटल काष्ठा vm_काष्ठा *vmlist __initdata;

अटल अंतरभूत अचिन्हित पूर्णांक vm_area_page_order(काष्ठा vm_काष्ठा *vm)
अणु
#अगर_घोषित CONFIG_HAVE_ARCH_HUGE_VMALLOC
	वापस vm->page_order;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम set_vm_area_page_order(काष्ठा vm_काष्ठा *vm, अचिन्हित पूर्णांक order)
अणु
#अगर_घोषित CONFIG_HAVE_ARCH_HUGE_VMALLOC
	vm->page_order = order;
#अन्यथा
	BUG_ON(order != 0);
#पूर्ण_अगर
पूर्ण

/**
 * vm_area_add_early - add vmap area early during boot
 * @vm: vm_काष्ठा to add
 *
 * This function is used to add fixed kernel vm area to vmlist beक्रमe
 * vदो_स्मृति_init() is called.  @vm->addr, @vm->size, and @vm->flags
 * should contain proper values and the other fields should be zero.
 *
 * DO NOT USE THIS FUNCTION UNLESS YOU KNOW WHAT YOU'RE DOING.
 */
व्योम __init vm_area_add_early(काष्ठा vm_काष्ठा *vm)
अणु
	काष्ठा vm_काष्ठा *पंचांगp, **p;

	BUG_ON(vmap_initialized);
	क्रम (p = &vmlist; (पंचांगp = *p) != शून्य; p = &पंचांगp->next) अणु
		अगर (पंचांगp->addr >= vm->addr) अणु
			BUG_ON(पंचांगp->addr < vm->addr + vm->size);
			अवरोध;
		पूर्ण अन्यथा
			BUG_ON(पंचांगp->addr + पंचांगp->size > vm->addr);
	पूर्ण
	vm->next = *p;
	*p = vm;
पूर्ण

/**
 * vm_area_रेजिस्टर_early - रेजिस्टर vmap area early during boot
 * @vm: vm_काष्ठा to रेजिस्टर
 * @align: requested alignment
 *
 * This function is used to रेजिस्टर kernel vm area beक्रमe
 * vदो_स्मृति_init() is called.  @vm->size and @vm->flags should contain
 * proper values on entry and other fields should be zero.  On वापस,
 * vm->addr contains the allocated address.
 *
 * DO NOT USE THIS FUNCTION UNLESS YOU KNOW WHAT YOU'RE DOING.
 */
व्योम __init vm_area_रेजिस्टर_early(काष्ठा vm_काष्ठा *vm, माप_प्रकार align)
अणु
	अटल माप_प्रकार vm_init_off __initdata;
	अचिन्हित दीर्घ addr;

	addr = ALIGN(VMALLOC_START + vm_init_off, align);
	vm_init_off = PFN_ALIGN(addr + vm->size) - VMALLOC_START;

	vm->addr = (व्योम *)addr;

	vm_area_add_early(vm);
पूर्ण

अटल व्योम vmap_init_मुक्त_space(व्योम)
अणु
	अचिन्हित दीर्घ vmap_start = 1;
	स्थिर अचिन्हित दीर्घ vmap_end = अच_दीर्घ_उच्च;
	काष्ठा vmap_area *busy, *मुक्त;

	/*
	 *     B     F     B     B     B     F
	 * -|-----|.....|-----|-----|-----|.....|-
	 *  |           The KVA space           |
	 *  |<--------------------------------->|
	 */
	list_क्रम_each_entry(busy, &vmap_area_list, list) अणु
		अगर (busy->बहु_शुरू - vmap_start > 0) अणु
			मुक्त = kmem_cache_zalloc(vmap_area_cachep, GFP_NOWAIT);
			अगर (!WARN_ON_ONCE(!मुक्त)) अणु
				मुक्त->बहु_शुरू = vmap_start;
				मुक्त->बहु_पूर्ण = busy->बहु_शुरू;

				insert_vmap_area_augment(मुक्त, शून्य,
					&मुक्त_vmap_area_root,
						&मुक्त_vmap_area_list);
			पूर्ण
		पूर्ण

		vmap_start = busy->बहु_पूर्ण;
	पूर्ण

	अगर (vmap_end - vmap_start > 0) अणु
		मुक्त = kmem_cache_zalloc(vmap_area_cachep, GFP_NOWAIT);
		अगर (!WARN_ON_ONCE(!मुक्त)) अणु
			मुक्त->बहु_शुरू = vmap_start;
			मुक्त->बहु_पूर्ण = vmap_end;

			insert_vmap_area_augment(मुक्त, शून्य,
				&मुक्त_vmap_area_root,
					&मुक्त_vmap_area_list);
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init vदो_स्मृति_init(व्योम)
अणु
	काष्ठा vmap_area *va;
	काष्ठा vm_काष्ठा *पंचांगp;
	पूर्णांक i;

	/*
	 * Create the cache क्रम vmap_area objects.
	 */
	vmap_area_cachep = KMEM_CACHE(vmap_area, SLAB_PANIC);

	क्रम_each_possible_cpu(i) अणु
		काष्ठा vmap_block_queue *vbq;
		काष्ठा vमुक्त_deferred *p;

		vbq = &per_cpu(vmap_block_queue, i);
		spin_lock_init(&vbq->lock);
		INIT_LIST_HEAD(&vbq->मुक्त);
		p = &per_cpu(vमुक्त_deferred, i);
		init_llist_head(&p->list);
		INIT_WORK(&p->wq, मुक्त_work);
	पूर्ण

	/* Import existing vmlist entries. */
	क्रम (पंचांगp = vmlist; पंचांगp; पंचांगp = पंचांगp->next) अणु
		va = kmem_cache_zalloc(vmap_area_cachep, GFP_NOWAIT);
		अगर (WARN_ON_ONCE(!va))
			जारी;

		va->बहु_शुरू = (अचिन्हित दीर्घ)पंचांगp->addr;
		va->बहु_पूर्ण = va->बहु_शुरू + पंचांगp->size;
		va->vm = पंचांगp;
		insert_vmap_area(va, &vmap_area_root, &vmap_area_list);
	पूर्ण

	/*
	 * Now we can initialize a मुक्त vmap space.
	 */
	vmap_init_मुक्त_space();
	vmap_initialized = true;
पूर्ण

अटल अंतरभूत व्योम setup_vदो_स्मृति_vm_locked(काष्ठा vm_काष्ठा *vm,
	काष्ठा vmap_area *va, अचिन्हित दीर्घ flags, स्थिर व्योम *caller)
अणु
	vm->flags = flags;
	vm->addr = (व्योम *)va->बहु_शुरू;
	vm->size = va->बहु_पूर्ण - va->बहु_शुरू;
	vm->caller = caller;
	va->vm = vm;
पूर्ण

अटल व्योम setup_vदो_स्मृति_vm(काष्ठा vm_काष्ठा *vm, काष्ठा vmap_area *va,
			      अचिन्हित दीर्घ flags, स्थिर व्योम *caller)
अणु
	spin_lock(&vmap_area_lock);
	setup_vदो_स्मृति_vm_locked(vm, va, flags, caller);
	spin_unlock(&vmap_area_lock);
पूर्ण

अटल व्योम clear_vm_uninitialized_flag(काष्ठा vm_काष्ठा *vm)
अणु
	/*
	 * Beक्रमe removing VM_UNINITIALIZED,
	 * we should make sure that vm has proper values.
	 * Pair with smp_rmb() in show_numa_info().
	 */
	smp_wmb();
	vm->flags &= ~VM_UNINITIALIZED;
पूर्ण

अटल काष्ठा vm_काष्ठा *__get_vm_area_node(अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ align, अचिन्हित दीर्घ flags, अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ end, पूर्णांक node, gfp_t gfp_mask, स्थिर व्योम *caller)
अणु
	काष्ठा vmap_area *va;
	काष्ठा vm_काष्ठा *area;
	अचिन्हित दीर्घ requested_size = size;

	BUG_ON(in_पूर्णांकerrupt());
	size = PAGE_ALIGN(size);
	अगर (unlikely(!size))
		वापस शून्य;

	अगर (flags & VM_IOREMAP)
		align = 1ul << clamp_t(पूर्णांक, get_count_order_दीर्घ(size),
				       PAGE_SHIFT, IOREMAP_MAX_ORDER);

	area = kzalloc_node(माप(*area), gfp_mask & GFP_RECLAIM_MASK, node);
	अगर (unlikely(!area))
		वापस शून्य;

	अगर (!(flags & VM_NO_GUARD))
		size += PAGE_SIZE;

	va = alloc_vmap_area(size, align, start, end, node, gfp_mask);
	अगर (IS_ERR(va)) अणु
		kमुक्त(area);
		वापस शून्य;
	पूर्ण

	kasan_unpoison_vदो_स्मृति((व्योम *)va->बहु_शुरू, requested_size);

	setup_vदो_स्मृति_vm(area, va, flags, caller);

	वापस area;
पूर्ण

काष्ठा vm_काष्ठा *__get_vm_area_caller(अचिन्हित दीर्घ size, अचिन्हित दीर्घ flags,
				       अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				       स्थिर व्योम *caller)
अणु
	वापस __get_vm_area_node(size, 1, flags, start, end, NUMA_NO_NODE,
				  GFP_KERNEL, caller);
पूर्ण

/**
 * get_vm_area - reserve a contiguous kernel भव area
 * @size:	 size of the area
 * @flags:	 %VM_IOREMAP क्रम I/O mappings or VM_ALLOC
 *
 * Search an area of @size in the kernel भव mapping area,
 * and reserved it क्रम out purposes.  Returns the area descriptor
 * on success or %शून्य on failure.
 *
 * Return: the area descriptor on success or %शून्य on failure.
 */
काष्ठा vm_काष्ठा *get_vm_area(अचिन्हित दीर्घ size, अचिन्हित दीर्घ flags)
अणु
	वापस __get_vm_area_node(size, 1, flags, VMALLOC_START, VMALLOC_END,
				  NUMA_NO_NODE, GFP_KERNEL,
				  __builtin_वापस_address(0));
पूर्ण

काष्ठा vm_काष्ठा *get_vm_area_caller(अचिन्हित दीर्घ size, अचिन्हित दीर्घ flags,
				स्थिर व्योम *caller)
अणु
	वापस __get_vm_area_node(size, 1, flags, VMALLOC_START, VMALLOC_END,
				  NUMA_NO_NODE, GFP_KERNEL, caller);
पूर्ण

/**
 * find_vm_area - find a continuous kernel भव area
 * @addr:	  base address
 *
 * Search क्रम the kernel VM area starting at @addr, and वापस it.
 * It is up to the caller to करो all required locking to keep the वापसed
 * poपूर्णांकer valid.
 *
 * Return: the area descriptor on success or %शून्य on failure.
 */
काष्ठा vm_काष्ठा *find_vm_area(स्थिर व्योम *addr)
अणु
	काष्ठा vmap_area *va;

	va = find_vmap_area((अचिन्हित दीर्घ)addr);
	अगर (!va)
		वापस शून्य;

	वापस va->vm;
पूर्ण

/**
 * हटाओ_vm_area - find and हटाओ a continuous kernel भव area
 * @addr:	    base address
 *
 * Search क्रम the kernel VM area starting at @addr, and हटाओ it.
 * This function वापसs the found VM area, but using it is NOT safe
 * on SMP machines, except क्रम its size or flags.
 *
 * Return: the area descriptor on success or %शून्य on failure.
 */
काष्ठा vm_काष्ठा *हटाओ_vm_area(स्थिर व्योम *addr)
अणु
	काष्ठा vmap_area *va;

	might_sleep();

	spin_lock(&vmap_area_lock);
	va = __find_vmap_area((अचिन्हित दीर्घ)addr);
	अगर (va && va->vm) अणु
		काष्ठा vm_काष्ठा *vm = va->vm;

		va->vm = शून्य;
		spin_unlock(&vmap_area_lock);

		kasan_मुक्त_shaकरोw(vm);
		मुक्त_unmap_vmap_area(va);

		वापस vm;
	पूर्ण

	spin_unlock(&vmap_area_lock);
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम set_area_direct_map(स्थिर काष्ठा vm_काष्ठा *area,
				       पूर्णांक (*set_direct_map)(काष्ठा page *page))
अणु
	पूर्णांक i;

	/* HUGE_VMALLOC passes small pages to set_direct_map */
	क्रम (i = 0; i < area->nr_pages; i++)
		अगर (page_address(area->pages[i]))
			set_direct_map(area->pages[i]);
पूर्ण

/* Handle removing and resetting vm mappings related to the vm_काष्ठा. */
अटल व्योम vm_हटाओ_mappings(काष्ठा vm_काष्ठा *area, पूर्णांक deallocate_pages)
अणु
	अचिन्हित दीर्घ start = अच_दीर्घ_उच्च, end = 0;
	अचिन्हित पूर्णांक page_order = vm_area_page_order(area);
	पूर्णांक flush_reset = area->flags & VM_FLUSH_RESET_PERMS;
	पूर्णांक flush_dmap = 0;
	पूर्णांक i;

	हटाओ_vm_area(area->addr);

	/* If this is not VM_FLUSH_RESET_PERMS memory, no need क्रम the below. */
	अगर (!flush_reset)
		वापस;

	/*
	 * If not deallocating pages, just करो the flush of the VM area and
	 * वापस.
	 */
	अगर (!deallocate_pages) अणु
		vm_unmap_aliases();
		वापस;
	पूर्ण

	/*
	 * If execution माला_लो here, flush the vm mapping and reset the direct
	 * map. Find the start and end range of the direct mappings to make sure
	 * the vm_unmap_aliases() flush includes the direct map.
	 */
	क्रम (i = 0; i < area->nr_pages; i += 1U << page_order) अणु
		अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)page_address(area->pages[i]);
		अगर (addr) अणु
			अचिन्हित दीर्घ page_size;

			page_size = PAGE_SIZE << page_order;
			start = min(addr, start);
			end = max(addr + page_size, end);
			flush_dmap = 1;
		पूर्ण
	पूर्ण

	/*
	 * Set direct map to something invalid so that it won't be cached अगर
	 * there are any accesses after the TLB flush, then flush the TLB and
	 * reset the direct map permissions to the शेष.
	 */
	set_area_direct_map(area, set_direct_map_invalid_noflush);
	_vm_unmap_aliases(start, end, flush_dmap);
	set_area_direct_map(area, set_direct_map_शेष_noflush);
पूर्ण

अटल व्योम __vunmap(स्थिर व्योम *addr, पूर्णांक deallocate_pages)
अणु
	काष्ठा vm_काष्ठा *area;

	अगर (!addr)
		वापस;

	अगर (WARN(!PAGE_ALIGNED(addr), "Trying to vfree() bad address (%p)\n",
			addr))
		वापस;

	area = find_vm_area(addr);
	अगर (unlikely(!area)) अणु
		WARN(1, KERN_ERR "Trying to vfree() nonexistent vm area (%p)\n",
				addr);
		वापस;
	पूर्ण

	debug_check_no_locks_मुक्तd(area->addr, get_vm_area_size(area));
	debug_check_no_obj_मुक्तd(area->addr, get_vm_area_size(area));

	kasan_poison_vदो_स्मृति(area->addr, get_vm_area_size(area));

	vm_हटाओ_mappings(area, deallocate_pages);

	अगर (deallocate_pages) अणु
		अचिन्हित पूर्णांक page_order = vm_area_page_order(area);
		पूर्णांक i;

		क्रम (i = 0; i < area->nr_pages; i += 1U << page_order) अणु
			काष्ठा page *page = area->pages[i];

			BUG_ON(!page);
			__मुक्त_pages(page, page_order);
		पूर्ण
		atomic_दीर्घ_sub(area->nr_pages, &nr_vदो_स्मृति_pages);

		kvमुक्त(area->pages);
	पूर्ण

	kमुक्त(area);
पूर्ण

अटल अंतरभूत व्योम __vमुक्त_deferred(स्थिर व्योम *addr)
अणु
	/*
	 * Use raw_cpu_ptr() because this can be called from preemptible
	 * context. Preemption is असलolutely fine here, because the llist_add()
	 * implementation is lockless, so it works even अगर we are adding to
	 * another cpu's list. schedule_work() should be fine with this too.
	 */
	काष्ठा vमुक्त_deferred *p = raw_cpu_ptr(&vमुक्त_deferred);

	अगर (llist_add((काष्ठा llist_node *)addr, &p->list))
		schedule_work(&p->wq);
पूर्ण

/**
 * vमुक्त_atomic - release memory allocated by vदो_स्मृति()
 * @addr:	  memory base address
 *
 * This one is just like vमुक्त() but can be called in any atomic context
 * except NMIs.
 */
व्योम vमुक्त_atomic(स्थिर व्योम *addr)
अणु
	BUG_ON(in_nmi());

	kmemleak_मुक्त(addr);

	अगर (!addr)
		वापस;
	__vमुक्त_deferred(addr);
पूर्ण

अटल व्योम __vमुक्त(स्थिर व्योम *addr)
अणु
	अगर (unlikely(in_पूर्णांकerrupt()))
		__vमुक्त_deferred(addr);
	अन्यथा
		__vunmap(addr, 1);
पूर्ण

/**
 * vमुक्त - Release memory allocated by vदो_स्मृति()
 * @addr:  Memory base address
 *
 * Free the भवly continuous memory area starting at @addr, as obtained
 * from one of the vदो_स्मृति() family of APIs.  This will usually also मुक्त the
 * physical memory underlying the भव allocation, but that memory is
 * reference counted, so it will not be मुक्तd until the last user goes away.
 *
 * If @addr is शून्य, no operation is perक्रमmed.
 *
 * Context:
 * May sleep अगर called *not* from पूर्णांकerrupt context.
 * Must not be called in NMI context (strictly speaking, it could be
 * अगर we have CONFIG_ARCH_HAVE_NMI_SAFE_CMPXCHG, but making the calling
 * conventions क्रम vमुक्त() arch-dependent would be a really bad idea).
 */
व्योम vमुक्त(स्थिर व्योम *addr)
अणु
	BUG_ON(in_nmi());

	kmemleak_मुक्त(addr);

	might_sleep_अगर(!in_पूर्णांकerrupt());

	अगर (!addr)
		वापस;

	__vमुक्त(addr);
पूर्ण
EXPORT_SYMBOL(vमुक्त);

/**
 * vunmap - release भव mapping obtained by vmap()
 * @addr:   memory base address
 *
 * Free the भवly contiguous memory area starting at @addr,
 * which was created from the page array passed to vmap().
 *
 * Must not be called in पूर्णांकerrupt context.
 */
व्योम vunmap(स्थिर व्योम *addr)
अणु
	BUG_ON(in_पूर्णांकerrupt());
	might_sleep();
	अगर (addr)
		__vunmap(addr, 0);
पूर्ण
EXPORT_SYMBOL(vunmap);

/**
 * vmap - map an array of pages पूर्णांकo भवly contiguous space
 * @pages: array of page poपूर्णांकers
 * @count: number of pages to map
 * @flags: vm_area->flags
 * @prot: page protection क्रम the mapping
 *
 * Maps @count pages from @pages पूर्णांकo contiguous kernel भव space.
 * If @flags contains %VM_MAP_PUT_PAGES the ownership of the pages array itself
 * (which must be kदो_स्मृति or vदो_स्मृति memory) and one reference per pages in it
 * are transferred from the caller to vmap(), and will be मुक्तd / dropped when
 * vमुक्त() is called on the वापस value.
 *
 * Return: the address of the area or %शून्य on failure
 */
व्योम *vmap(काष्ठा page **pages, अचिन्हित पूर्णांक count,
	   अचिन्हित दीर्घ flags, pgprot_t prot)
अणु
	काष्ठा vm_काष्ठा *area;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ size;		/* In bytes */

	might_sleep();

	अगर (count > totalram_pages())
		वापस शून्य;

	size = (अचिन्हित दीर्घ)count << PAGE_SHIFT;
	area = get_vm_area_caller(size, flags, __builtin_वापस_address(0));
	अगर (!area)
		वापस शून्य;

	addr = (अचिन्हित दीर्घ)area->addr;
	अगर (vmap_pages_range(addr, addr + size, pgprot_nx(prot),
				pages, PAGE_SHIFT) < 0) अणु
		vunmap(area->addr);
		वापस शून्य;
	पूर्ण

	अगर (flags & VM_MAP_PUT_PAGES) अणु
		area->pages = pages;
		area->nr_pages = count;
	पूर्ण
	वापस area->addr;
पूर्ण
EXPORT_SYMBOL(vmap);

#अगर_घोषित CONFIG_VMAP_PFN
काष्ठा vmap_pfn_data अणु
	अचिन्हित दीर्घ	*pfns;
	pgprot_t	prot;
	अचिन्हित पूर्णांक	idx;
पूर्ण;

अटल पूर्णांक vmap_pfn_apply(pte_t *pte, अचिन्हित दीर्घ addr, व्योम *निजी)
अणु
	काष्ठा vmap_pfn_data *data = निजी;

	अगर (WARN_ON_ONCE(pfn_valid(data->pfns[data->idx])))
		वापस -EINVAL;
	*pte = pte_mkspecial(pfn_pte(data->pfns[data->idx++], data->prot));
	वापस 0;
पूर्ण

/**
 * vmap_pfn - map an array of PFNs पूर्णांकo भवly contiguous space
 * @pfns: array of PFNs
 * @count: number of pages to map
 * @prot: page protection क्रम the mapping
 *
 * Maps @count PFNs from @pfns पूर्णांकo contiguous kernel भव space and वापसs
 * the start address of the mapping.
 */
व्योम *vmap_pfn(अचिन्हित दीर्घ *pfns, अचिन्हित पूर्णांक count, pgprot_t prot)
अणु
	काष्ठा vmap_pfn_data data = अणु .pfns = pfns, .prot = pgprot_nx(prot) पूर्ण;
	काष्ठा vm_काष्ठा *area;

	area = get_vm_area_caller(count * PAGE_SIZE, VM_IOREMAP,
			__builtin_वापस_address(0));
	अगर (!area)
		वापस शून्य;
	अगर (apply_to_page_range(&init_mm, (अचिन्हित दीर्घ)area->addr,
			count * PAGE_SIZE, vmap_pfn_apply, &data)) अणु
		मुक्त_vm_area(area);
		वापस शून्य;
	पूर्ण
	वापस area->addr;
पूर्ण
EXPORT_SYMBOL_GPL(vmap_pfn);
#पूर्ण_अगर /* CONFIG_VMAP_PFN */

अटल व्योम *__vदो_स्मृति_area_node(काष्ठा vm_काष्ठा *area, gfp_t gfp_mask,
				 pgprot_t prot, अचिन्हित पूर्णांक page_shअगरt,
				 पूर्णांक node)
अणु
	स्थिर gfp_t nested_gfp = (gfp_mask & GFP_RECLAIM_MASK) | __GFP_ZERO;
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)area->addr;
	अचिन्हित दीर्घ size = get_vm_area_size(area);
	अचिन्हित दीर्घ array_size;
	अचिन्हित पूर्णांक nr_small_pages = size >> PAGE_SHIFT;
	अचिन्हित पूर्णांक page_order;
	काष्ठा page **pages;
	अचिन्हित पूर्णांक i;

	array_size = (अचिन्हित दीर्घ)nr_small_pages * माप(काष्ठा page *);
	gfp_mask |= __GFP_NOWARN;
	अगर (!(gfp_mask & (GFP_DMA | GFP_DMA32)))
		gfp_mask |= __GFP_HIGHMEM;

	/* Please note that the recursion is strictly bounded. */
	अगर (array_size > PAGE_SIZE) अणु
		pages = __vदो_स्मृति_node(array_size, 1, nested_gfp, node,
					area->caller);
	पूर्ण अन्यथा अणु
		pages = kदो_स्मृति_node(array_size, nested_gfp, node);
	पूर्ण

	अगर (!pages) अणु
		मुक्त_vm_area(area);
		warn_alloc(gfp_mask, शून्य,
			   "vmalloc size %lu allocation failure: "
			   "page array size %lu allocation failed",
			   nr_small_pages * PAGE_SIZE, array_size);
		वापस शून्य;
	पूर्ण

	area->pages = pages;
	area->nr_pages = nr_small_pages;
	set_vm_area_page_order(area, page_shअगरt - PAGE_SHIFT);

	page_order = vm_area_page_order(area);

	/*
	 * Careful, we allocate and map page_order pages, but tracking is करोne
	 * per PAGE_SIZE page so as to keep the vm_काष्ठा APIs independent of
	 * the physical/mapped size.
	 */
	क्रम (i = 0; i < area->nr_pages; i += 1U << page_order) अणु
		काष्ठा page *page;
		पूर्णांक p;

		/* Compound pages required क्रम remap_vदो_स्मृति_page */
		page = alloc_pages_node(node, gfp_mask | __GFP_COMP, page_order);
		अगर (unlikely(!page)) अणु
			/* Successfully allocated i pages, मुक्त them in __vमुक्त() */
			area->nr_pages = i;
			atomic_दीर्घ_add(area->nr_pages, &nr_vदो_स्मृति_pages);
			warn_alloc(gfp_mask, शून्य,
				   "vmalloc size %lu allocation failure: "
				   "page order %u allocation failed",
				   area->nr_pages * PAGE_SIZE, page_order);
			जाओ fail;
		पूर्ण

		क्रम (p = 0; p < (1U << page_order); p++)
			area->pages[i + p] = page + p;

		अगर (gfpflags_allow_blocking(gfp_mask))
			cond_resched();
	पूर्ण
	atomic_दीर्घ_add(area->nr_pages, &nr_vदो_स्मृति_pages);

	अगर (vmap_pages_range(addr, addr + size, prot, pages, page_shअगरt) < 0) अणु
		warn_alloc(gfp_mask, शून्य,
			   "vmalloc size %lu allocation failure: "
			   "failed to map pages",
			   area->nr_pages * PAGE_SIZE);
		जाओ fail;
	पूर्ण

	वापस area->addr;

fail:
	__vमुक्त(area->addr);
	वापस शून्य;
पूर्ण

/**
 * __vदो_स्मृति_node_range - allocate भवly contiguous memory
 * @size:		  allocation size
 * @align:		  desired alignment
 * @start:		  vm area range start
 * @end:		  vm area range end
 * @gfp_mask:		  flags क्रम the page level allocator
 * @prot:		  protection mask क्रम the allocated pages
 * @vm_flags:		  additional vm area flags (e.g. %VM_NO_GUARD)
 * @node:		  node to use क्रम allocation or NUMA_NO_NODE
 * @caller:		  caller's वापस address
 *
 * Allocate enough pages to cover @size from the page level
 * allocator with @gfp_mask flags.  Map them पूर्णांकo contiguous
 * kernel भव space, using a pagetable protection of @prot.
 *
 * Return: the address of the area or %शून्य on failure
 */
व्योम *__vदो_स्मृति_node_range(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, gfp_t gfp_mask,
			pgprot_t prot, अचिन्हित दीर्घ vm_flags, पूर्णांक node,
			स्थिर व्योम *caller)
अणु
	काष्ठा vm_काष्ठा *area;
	व्योम *addr;
	अचिन्हित दीर्घ real_size = size;
	अचिन्हित दीर्घ real_align = align;
	अचिन्हित पूर्णांक shअगरt = PAGE_SHIFT;

	अगर (WARN_ON_ONCE(!size))
		वापस शून्य;

	अगर ((size >> PAGE_SHIFT) > totalram_pages()) अणु
		warn_alloc(gfp_mask, शून्य,
			   "vmalloc size %lu allocation failure: "
			   "exceeds total pages", real_size);
		वापस शून्य;
	पूर्ण

	अगर (vmap_allow_huge && !(vm_flags & VM_NO_HUGE_VMAP) &&
			arch_vmap_pmd_supported(prot)) अणु
		अचिन्हित दीर्घ size_per_node;

		/*
		 * Try huge pages. Only try क्रम PAGE_KERNEL allocations,
		 * others like modules करोn't yet expect huge pages in
		 * their allocations due to apply_to_page_range not
		 * supporting them.
		 */

		size_per_node = size;
		अगर (node == NUMA_NO_NODE)
			size_per_node /= num_online_nodes();
		अगर (size_per_node >= PMD_SIZE) अणु
			shअगरt = PMD_SHIFT;
			align = max(real_align, 1UL << shअगरt);
			size = ALIGN(real_size, 1UL << shअगरt);
		पूर्ण
	पूर्ण

again:
	size = PAGE_ALIGN(size);
	area = __get_vm_area_node(size, align, VM_ALLOC | VM_UNINITIALIZED |
				vm_flags, start, end, node, gfp_mask, caller);
	अगर (!area) अणु
		warn_alloc(gfp_mask, शून्य,
			   "vmalloc size %lu allocation failure: "
			   "vm_struct allocation failed", real_size);
		जाओ fail;
	पूर्ण

	addr = __vदो_स्मृति_area_node(area, gfp_mask, prot, shअगरt, node);
	अगर (!addr)
		जाओ fail;

	/*
	 * In this function, newly allocated vm_काष्ठा has VM_UNINITIALIZED
	 * flag. It means that vm_काष्ठा is not fully initialized.
	 * Now, it is fully initialized, so हटाओ this flag here.
	 */
	clear_vm_uninitialized_flag(area);

	kmemleak_vदो_स्मृति(area, size, gfp_mask);

	वापस addr;

fail:
	अगर (shअगरt > PAGE_SHIFT) अणु
		shअगरt = PAGE_SHIFT;
		align = real_align;
		size = real_size;
		जाओ again;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * __vदो_स्मृति_node - allocate भवly contiguous memory
 * @size:	    allocation size
 * @align:	    desired alignment
 * @gfp_mask:	    flags क्रम the page level allocator
 * @node:	    node to use क्रम allocation or NUMA_NO_NODE
 * @caller:	    caller's वापस address
 *
 * Allocate enough pages to cover @size from the page level allocator with
 * @gfp_mask flags.  Map them पूर्णांकo contiguous kernel भव space.
 *
 * Reclaim modअगरiers in @gfp_mask - __GFP_NORETRY, __GFP_RETRY_MAYFAIL
 * and __GFP_NOFAIL are not supported
 *
 * Any use of gfp flags outside of GFP_KERNEL should be consulted
 * with mm people.
 *
 * Return: poपूर्णांकer to the allocated memory or %शून्य on error
 */
व्योम *__vदो_स्मृति_node(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align,
			    gfp_t gfp_mask, पूर्णांक node, स्थिर व्योम *caller)
अणु
	वापस __vदो_स्मृति_node_range(size, align, VMALLOC_START, VMALLOC_END,
				gfp_mask, PAGE_KERNEL, 0, node, caller);
पूर्ण
/*
 * This is only क्रम perक्रमmance analysis of vदो_स्मृति and stress purpose.
 * It is required by vदो_स्मृति test module, thereक्रमe करो not use it other
 * than that.
 */
#अगर_घोषित CONFIG_TEST_VMALLOC_MODULE
EXPORT_SYMBOL_GPL(__vदो_स्मृति_node);
#पूर्ण_अगर

व्योम *__vदो_स्मृति(अचिन्हित दीर्घ size, gfp_t gfp_mask)
अणु
	वापस __vदो_स्मृति_node(size, 1, gfp_mask, NUMA_NO_NODE,
				__builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(__vदो_स्मृति);

/**
 * vदो_स्मृति - allocate भवly contiguous memory
 * @size:    allocation size
 *
 * Allocate enough pages to cover @size from the page level
 * allocator and map them पूर्णांकo contiguous kernel भव space.
 *
 * For tight control over page level allocator and protection flags
 * use __vदो_स्मृति() instead.
 *
 * Return: poपूर्णांकer to the allocated memory or %शून्य on error
 */
व्योम *vदो_स्मृति(अचिन्हित दीर्घ size)
अणु
	वापस __vदो_स्मृति_node(size, 1, GFP_KERNEL, NUMA_NO_NODE,
				__builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(vदो_स्मृति);

/**
 * vzalloc - allocate भवly contiguous memory with zero fill
 * @size:    allocation size
 *
 * Allocate enough pages to cover @size from the page level
 * allocator and map them पूर्णांकo contiguous kernel भव space.
 * The memory allocated is set to zero.
 *
 * For tight control over page level allocator and protection flags
 * use __vदो_स्मृति() instead.
 *
 * Return: poपूर्णांकer to the allocated memory or %शून्य on error
 */
व्योम *vzalloc(अचिन्हित दीर्घ size)
अणु
	वापस __vदो_स्मृति_node(size, 1, GFP_KERNEL | __GFP_ZERO, NUMA_NO_NODE,
				__builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(vzalloc);

/**
 * vदो_स्मृति_user - allocate zeroed भवly contiguous memory क्रम userspace
 * @size: allocation size
 *
 * The resulting memory area is zeroed so it can be mapped to userspace
 * without leaking data.
 *
 * Return: poपूर्णांकer to the allocated memory or %शून्य on error
 */
व्योम *vदो_स्मृति_user(अचिन्हित दीर्घ size)
अणु
	वापस __vदो_स्मृति_node_range(size, SHMLBA,  VMALLOC_START, VMALLOC_END,
				    GFP_KERNEL | __GFP_ZERO, PAGE_KERNEL,
				    VM_USERMAP, NUMA_NO_NODE,
				    __builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(vदो_स्मृति_user);

/**
 * vदो_स्मृति_node - allocate memory on a specअगरic node
 * @size:	  allocation size
 * @node:	  numa node
 *
 * Allocate enough pages to cover @size from the page level
 * allocator and map them पूर्णांकo contiguous kernel भव space.
 *
 * For tight control over page level allocator and protection flags
 * use __vदो_स्मृति() instead.
 *
 * Return: poपूर्णांकer to the allocated memory or %शून्य on error
 */
व्योम *vदो_स्मृति_node(अचिन्हित दीर्घ size, पूर्णांक node)
अणु
	वापस __vदो_स्मृति_node(size, 1, GFP_KERNEL, node,
			__builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(vदो_स्मृति_node);

/**
 * vzalloc_node - allocate memory on a specअगरic node with zero fill
 * @size:	allocation size
 * @node:	numa node
 *
 * Allocate enough pages to cover @size from the page level
 * allocator and map them पूर्णांकo contiguous kernel भव space.
 * The memory allocated is set to zero.
 *
 * Return: poपूर्णांकer to the allocated memory or %शून्य on error
 */
व्योम *vzalloc_node(अचिन्हित दीर्घ size, पूर्णांक node)
अणु
	वापस __vदो_स्मृति_node(size, 1, GFP_KERNEL | __GFP_ZERO, node,
				__builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(vzalloc_node);

#अगर defined(CONFIG_64BIT) && defined(CONFIG_ZONE_DMA32)
#घोषणा GFP_VMALLOC32 (GFP_DMA32 | GFP_KERNEL)
#या_अगर defined(CONFIG_64BIT) && defined(CONFIG_ZONE_DMA)
#घोषणा GFP_VMALLOC32 (GFP_DMA | GFP_KERNEL)
#अन्यथा
/*
 * 64b प्रणालीs should always have either DMA or DMA32 zones. For others
 * GFP_DMA32 should करो the right thing and use the normal zone.
 */
#घोषणा GFP_VMALLOC32 (GFP_DMA32 | GFP_KERNEL)
#पूर्ण_अगर

/**
 * vदो_स्मृति_32 - allocate भवly contiguous memory (32bit addressable)
 * @size:	allocation size
 *
 * Allocate enough 32bit PA addressable pages to cover @size from the
 * page level allocator and map them पूर्णांकo contiguous kernel भव space.
 *
 * Return: poपूर्णांकer to the allocated memory or %शून्य on error
 */
व्योम *vदो_स्मृति_32(अचिन्हित दीर्घ size)
अणु
	वापस __vदो_स्मृति_node(size, 1, GFP_VMALLOC32, NUMA_NO_NODE,
			__builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(vदो_स्मृति_32);

/**
 * vदो_स्मृति_32_user - allocate zeroed भवly contiguous 32bit memory
 * @size:	     allocation size
 *
 * The resulting memory area is 32bit addressable and zeroed so it can be
 * mapped to userspace without leaking data.
 *
 * Return: poपूर्णांकer to the allocated memory or %शून्य on error
 */
व्योम *vदो_स्मृति_32_user(अचिन्हित दीर्घ size)
अणु
	वापस __vदो_स्मृति_node_range(size, SHMLBA,  VMALLOC_START, VMALLOC_END,
				    GFP_VMALLOC32 | __GFP_ZERO, PAGE_KERNEL,
				    VM_USERMAP, NUMA_NO_NODE,
				    __builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(vदो_स्मृति_32_user);

/*
 * small helper routine , copy contents to buf from addr.
 * If the page is not present, fill zero.
 */

अटल पूर्णांक aligned_vपढ़ो(अक्षर *buf, अक्षर *addr, अचिन्हित दीर्घ count)
अणु
	काष्ठा page *p;
	पूर्णांक copied = 0;

	जबतक (count) अणु
		अचिन्हित दीर्घ offset, length;

		offset = offset_in_page(addr);
		length = PAGE_SIZE - offset;
		अगर (length > count)
			length = count;
		p = vदो_स्मृति_to_page(addr);
		/*
		 * To करो safe access to this _mapped_ area, we need
		 * lock. But adding lock here means that we need to add
		 * overhead of vदो_स्मृति()/vमुक्त() calls क्रम this _debug_
		 * पूर्णांकerface, rarely used. Instead of that, we'll use
		 * kmap() and get small overhead in this access function.
		 */
		अगर (p) अणु
			/* We can expect USER0 is not used -- see vपढ़ो() */
			व्योम *map = kmap_atomic(p);
			स_नकल(buf, map + offset, length);
			kunmap_atomic(map);
		पूर्ण अन्यथा
			स_रखो(buf, 0, length);

		addr += length;
		buf += length;
		copied += length;
		count -= length;
	पूर्ण
	वापस copied;
पूर्ण

/**
 * vपढ़ो() - पढ़ो vदो_स्मृति area in a safe way.
 * @buf:     buffer क्रम पढ़ोing data
 * @addr:    vm address.
 * @count:   number of bytes to be पढ़ो.
 *
 * This function checks that addr is a valid vदो_स्मृति'ed area, and
 * copy data from that area to a given buffer. If the given memory range
 * of [addr...addr+count) includes some valid address, data is copied to
 * proper area of @buf. If there are memory holes, they'll be zero-filled.
 * IOREMAP area is treated as memory hole and no copy is करोne.
 *
 * If [addr...addr+count) करोesn't includes any पूर्णांकersects with alive
 * vm_काष्ठा area, वापसs 0. @buf should be kernel's buffer.
 *
 * Note: In usual ops, vपढ़ो() is never necessary because the caller
 * should know vदो_स्मृति() area is valid and can use स_नकल().
 * This is क्रम routines which have to access vदो_स्मृति area without
 * any inक्रमmation, as /proc/kcore.
 *
 * Return: number of bytes क्रम which addr and buf should be increased
 * (same number as @count) or %0 अगर [addr...addr+count) करोesn't
 * include any पूर्णांकersection with valid vदो_स्मृति area
 */
दीर्घ vपढ़ो(अक्षर *buf, अक्षर *addr, अचिन्हित दीर्घ count)
अणु
	काष्ठा vmap_area *va;
	काष्ठा vm_काष्ठा *vm;
	अक्षर *vaddr, *buf_start = buf;
	अचिन्हित दीर्घ buflen = count;
	अचिन्हित दीर्घ n;

	/* Don't allow overflow */
	अगर ((अचिन्हित दीर्घ) addr + count < count)
		count = -(अचिन्हित दीर्घ) addr;

	spin_lock(&vmap_area_lock);
	va = __find_vmap_area((अचिन्हित दीर्घ)addr);
	अगर (!va)
		जाओ finished;
	list_क्रम_each_entry_from(va, &vmap_area_list, list) अणु
		अगर (!count)
			अवरोध;

		अगर (!va->vm)
			जारी;

		vm = va->vm;
		vaddr = (अक्षर *) vm->addr;
		अगर (addr >= vaddr + get_vm_area_size(vm))
			जारी;
		जबतक (addr < vaddr) अणु
			अगर (count == 0)
				जाओ finished;
			*buf = '\0';
			buf++;
			addr++;
			count--;
		पूर्ण
		n = vaddr + get_vm_area_size(vm) - addr;
		अगर (n > count)
			n = count;
		अगर (!(vm->flags & VM_IOREMAP))
			aligned_vपढ़ो(buf, addr, n);
		अन्यथा /* IOREMAP area is treated as memory hole */
			स_रखो(buf, 0, n);
		buf += n;
		addr += n;
		count -= n;
	पूर्ण
finished:
	spin_unlock(&vmap_area_lock);

	अगर (buf == buf_start)
		वापस 0;
	/* zero-fill memory holes */
	अगर (buf != buf_start + buflen)
		स_रखो(buf, 0, buflen - (buf - buf_start));

	वापस buflen;
पूर्ण

/**
 * remap_vदो_स्मृति_range_partial - map vदो_स्मृति pages to userspace
 * @vma:		vma to cover
 * @uaddr:		target user address to start at
 * @kaddr:		भव address of vदो_स्मृति kernel memory
 * @pgoff:		offset from @kaddr to start at
 * @size:		size of map area
 *
 * Returns:	0 क्रम success, -Exxx on failure
 *
 * This function checks that @kaddr is a valid vदो_स्मृति'ed area,
 * and that it is big enough to cover the range starting at
 * @uaddr in @vma. Will वापस failure अगर that criteria isn't
 * met.
 *
 * Similar to remap_pfn_range() (see mm/memory.c)
 */
पूर्णांक remap_vदो_स्मृति_range_partial(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ uaddr,
				व्योम *kaddr, अचिन्हित दीर्घ pgoff,
				अचिन्हित दीर्घ size)
अणु
	काष्ठा vm_काष्ठा *area;
	अचिन्हित दीर्घ off;
	अचिन्हित दीर्घ end_index;

	अगर (check_shl_overflow(pgoff, PAGE_SHIFT, &off))
		वापस -EINVAL;

	size = PAGE_ALIGN(size);

	अगर (!PAGE_ALIGNED(uaddr) || !PAGE_ALIGNED(kaddr))
		वापस -EINVAL;

	area = find_vm_area(kaddr);
	अगर (!area)
		वापस -EINVAL;

	अगर (!(area->flags & (VM_USERMAP | VM_DMA_COHERENT)))
		वापस -EINVAL;

	अगर (check_add_overflow(size, off, &end_index) ||
	    end_index > get_vm_area_size(area))
		वापस -EINVAL;
	kaddr += off;

	करो अणु
		काष्ठा page *page = vदो_स्मृति_to_page(kaddr);
		पूर्णांक ret;

		ret = vm_insert_page(vma, uaddr, page);
		अगर (ret)
			वापस ret;

		uaddr += PAGE_SIZE;
		kaddr += PAGE_SIZE;
		size -= PAGE_SIZE;
	पूर्ण जबतक (size > 0);

	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;

	वापस 0;
पूर्ण

/**
 * remap_vदो_स्मृति_range - map vदो_स्मृति pages to userspace
 * @vma:		vma to cover (map full range of vma)
 * @addr:		vदो_स्मृति memory
 * @pgoff:		number of pages पूर्णांकo addr beक्रमe first page to map
 *
 * Returns:	0 क्रम success, -Exxx on failure
 *
 * This function checks that addr is a valid vदो_स्मृति'ed area, and
 * that it is big enough to cover the vma. Will वापस failure अगर
 * that criteria isn't met.
 *
 * Similar to remap_pfn_range() (see mm/memory.c)
 */
पूर्णांक remap_vदो_स्मृति_range(काष्ठा vm_area_काष्ठा *vma, व्योम *addr,
						अचिन्हित दीर्घ pgoff)
अणु
	वापस remap_vदो_स्मृति_range_partial(vma, vma->vm_start,
					   addr, pgoff,
					   vma->vm_end - vma->vm_start);
पूर्ण
EXPORT_SYMBOL(remap_vदो_स्मृति_range);

व्योम मुक्त_vm_area(काष्ठा vm_काष्ठा *area)
अणु
	काष्ठा vm_काष्ठा *ret;
	ret = हटाओ_vm_area(area->addr);
	BUG_ON(ret != area);
	kमुक्त(area);
पूर्ण
EXPORT_SYMBOL_GPL(मुक्त_vm_area);

#अगर_घोषित CONFIG_SMP
अटल काष्ठा vmap_area *node_to_va(काष्ठा rb_node *n)
अणु
	वापस rb_entry_safe(n, काष्ठा vmap_area, rb_node);
पूर्ण

/**
 * pvm_find_va_enबंद_addr - find the vmap_area @addr beदीर्घs to
 * @addr: target address
 *
 * Returns: vmap_area अगर it is found. If there is no such area
 *   the first highest(reverse order) vmap_area is वापसed
 *   i.e. va->बहु_शुरू < addr && va->बहु_पूर्ण < addr or शून्य
 *   अगर there are no any areas beक्रमe @addr.
 */
अटल काष्ठा vmap_area *
pvm_find_va_enबंद_addr(अचिन्हित दीर्घ addr)
अणु
	काष्ठा vmap_area *va, *पंचांगp;
	काष्ठा rb_node *n;

	n = मुक्त_vmap_area_root.rb_node;
	va = शून्य;

	जबतक (n) अणु
		पंचांगp = rb_entry(n, काष्ठा vmap_area, rb_node);
		अगर (पंचांगp->बहु_शुरू <= addr) अणु
			va = पंचांगp;
			अगर (पंचांगp->बहु_पूर्ण >= addr)
				अवरोध;

			n = n->rb_right;
		पूर्ण अन्यथा अणु
			n = n->rb_left;
		पूर्ण
	पूर्ण

	वापस va;
पूर्ण

/**
 * pvm_determine_end_from_reverse - find the highest aligned address
 * of मुक्त block below VMALLOC_END
 * @va:
 *   in - the VA we start the search(reverse order);
 *   out - the VA with the highest aligned end address.
 * @align: alignment क्रम required highest address
 *
 * Returns: determined end address within vmap_area
 */
अटल अचिन्हित दीर्घ
pvm_determine_end_from_reverse(काष्ठा vmap_area **va, अचिन्हित दीर्घ align)
अणु
	अचिन्हित दीर्घ vदो_स्मृति_end = VMALLOC_END & ~(align - 1);
	अचिन्हित दीर्घ addr;

	अगर (likely(*va)) अणु
		list_क्रम_each_entry_from_reverse((*va),
				&मुक्त_vmap_area_list, list) अणु
			addr = min((*va)->बहु_पूर्ण & ~(align - 1), vदो_स्मृति_end);
			अगर ((*va)->बहु_शुरू < addr)
				वापस addr;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pcpu_get_vm_areas - allocate vदो_स्मृति areas क्रम percpu allocator
 * @offsets: array containing offset of each area
 * @sizes: array containing size of each area
 * @nr_vms: the number of areas to allocate
 * @align: alignment, all entries in @offsets and @sizes must be aligned to this
 *
 * Returns: kदो_स्मृति'd vm_काष्ठा poपूर्णांकer array poपूर्णांकing to allocated
 *	    vm_काष्ठाs on success, %शून्य on failure
 *
 * Percpu allocator wants to use congruent vm areas so that it can
 * मुख्यtain the offsets among percpu areas.  This function allocates
 * congruent vदो_स्मृति areas क्रम it with GFP_KERNEL.  These areas tend to
 * be scattered pretty far, distance between two areas easily going up
 * to gigabytes.  To aव्योम पूर्णांकeracting with regular vदो_स्मृतिs, these
 * areas are allocated from top.
 *
 * Despite its complicated look, this allocator is rather simple. It
 * करोes everything top-करोwn and scans मुक्त blocks from the end looking
 * क्रम matching base. While scanning, अगर any of the areas करो not fit the
 * base address is pulled करोwn to fit the area. Scanning is repeated till
 * all the areas fit and then all necessary data काष्ठाures are inserted
 * and the result is वापसed.
 */
काष्ठा vm_काष्ठा **pcpu_get_vm_areas(स्थिर अचिन्हित दीर्घ *offsets,
				     स्थिर माप_प्रकार *sizes, पूर्णांक nr_vms,
				     माप_प्रकार align)
अणु
	स्थिर अचिन्हित दीर्घ vदो_स्मृति_start = ALIGN(VMALLOC_START, align);
	स्थिर अचिन्हित दीर्घ vदो_स्मृति_end = VMALLOC_END & ~(align - 1);
	काष्ठा vmap_area **vas, *va;
	काष्ठा vm_काष्ठा **vms;
	पूर्णांक area, area2, last_area, term_area;
	अचिन्हित दीर्घ base, start, size, end, last_end, orig_start, orig_end;
	bool purged = false;
	क्रमागत fit_type type;

	/* verअगरy parameters and allocate data काष्ठाures */
	BUG_ON(offset_in_page(align) || !is_घातer_of_2(align));
	क्रम (last_area = 0, area = 0; area < nr_vms; area++) अणु
		start = offsets[area];
		end = start + sizes[area];

		/* is everything aligned properly? */
		BUG_ON(!IS_ALIGNED(offsets[area], align));
		BUG_ON(!IS_ALIGNED(sizes[area], align));

		/* detect the area with the highest address */
		अगर (start > offsets[last_area])
			last_area = area;

		क्रम (area2 = area + 1; area2 < nr_vms; area2++) अणु
			अचिन्हित दीर्घ start2 = offsets[area2];
			अचिन्हित दीर्घ end2 = start2 + sizes[area2];

			BUG_ON(start2 < end && start < end2);
		पूर्ण
	पूर्ण
	last_end = offsets[last_area] + sizes[last_area];

	अगर (vदो_स्मृति_end - vदो_स्मृति_start < last_end) अणु
		WARN_ON(true);
		वापस शून्य;
	पूर्ण

	vms = kसुस्मृति(nr_vms, माप(vms[0]), GFP_KERNEL);
	vas = kसुस्मृति(nr_vms, माप(vas[0]), GFP_KERNEL);
	अगर (!vas || !vms)
		जाओ err_मुक्त2;

	क्रम (area = 0; area < nr_vms; area++) अणु
		vas[area] = kmem_cache_zalloc(vmap_area_cachep, GFP_KERNEL);
		vms[area] = kzalloc(माप(काष्ठा vm_काष्ठा), GFP_KERNEL);
		अगर (!vas[area] || !vms[area])
			जाओ err_मुक्त;
	पूर्ण
retry:
	spin_lock(&मुक्त_vmap_area_lock);

	/* start scanning - we scan from the top, begin with the last area */
	area = term_area = last_area;
	start = offsets[area];
	end = start + sizes[area];

	va = pvm_find_va_enबंद_addr(vदो_स्मृति_end);
	base = pvm_determine_end_from_reverse(&va, align) - end;

	जबतक (true) अणु
		/*
		 * base might have underflowed, add last_end beक्रमe
		 * comparing.
		 */
		अगर (base + last_end < vदो_स्मृति_start + last_end)
			जाओ overflow;

		/*
		 * Fitting base has not been found.
		 */
		अगर (va == शून्य)
			जाओ overflow;

		/*
		 * If required width exceeds current VA block, move
		 * base करोwnwards and then recheck.
		 */
		अगर (base + end > va->बहु_पूर्ण) अणु
			base = pvm_determine_end_from_reverse(&va, align) - end;
			term_area = area;
			जारी;
		पूर्ण

		/*
		 * If this VA करोes not fit, move base करोwnwards and recheck.
		 */
		अगर (base + start < va->बहु_शुरू) अणु
			va = node_to_va(rb_prev(&va->rb_node));
			base = pvm_determine_end_from_reverse(&va, align) - end;
			term_area = area;
			जारी;
		पूर्ण

		/*
		 * This area fits, move on to the previous one.  If
		 * the previous one is the terminal one, we're करोne.
		 */
		area = (area + nr_vms - 1) % nr_vms;
		अगर (area == term_area)
			अवरोध;

		start = offsets[area];
		end = start + sizes[area];
		va = pvm_find_va_enबंद_addr(base + end);
	पूर्ण

	/* we've found a fitting base, insert all va's */
	क्रम (area = 0; area < nr_vms; area++) अणु
		पूर्णांक ret;

		start = base + offsets[area];
		size = sizes[area];

		va = pvm_find_va_enबंद_addr(start);
		अगर (WARN_ON_ONCE(va == शून्य))
			/* It is a BUG(), but trigger recovery instead. */
			जाओ recovery;

		type = classअगरy_va_fit_type(va, start, size);
		अगर (WARN_ON_ONCE(type == NOTHING_FIT))
			/* It is a BUG(), but trigger recovery instead. */
			जाओ recovery;

		ret = adjust_va_to_fit_type(va, start, size, type);
		अगर (unlikely(ret))
			जाओ recovery;

		/* Allocated area. */
		va = vas[area];
		va->बहु_शुरू = start;
		va->बहु_पूर्ण = start + size;
	पूर्ण

	spin_unlock(&मुक्त_vmap_area_lock);

	/* populate the kasan shaकरोw space */
	क्रम (area = 0; area < nr_vms; area++) अणु
		अगर (kasan_populate_vदो_स्मृति(vas[area]->बहु_शुरू, sizes[area]))
			जाओ err_मुक्त_shaकरोw;

		kasan_unpoison_vदो_स्मृति((व्योम *)vas[area]->बहु_शुरू,
				       sizes[area]);
	पूर्ण

	/* insert all vm's */
	spin_lock(&vmap_area_lock);
	क्रम (area = 0; area < nr_vms; area++) अणु
		insert_vmap_area(vas[area], &vmap_area_root, &vmap_area_list);

		setup_vदो_स्मृति_vm_locked(vms[area], vas[area], VM_ALLOC,
				 pcpu_get_vm_areas);
	पूर्ण
	spin_unlock(&vmap_area_lock);

	kमुक्त(vas);
	वापस vms;

recovery:
	/*
	 * Remove previously allocated areas. There is no
	 * need in removing these areas from the busy tree,
	 * because they are inserted only on the final step
	 * and when pcpu_get_vm_areas() is success.
	 */
	जबतक (area--) अणु
		orig_start = vas[area]->बहु_शुरू;
		orig_end = vas[area]->बहु_पूर्ण;
		va = merge_or_add_vmap_area_augment(vas[area], &मुक्त_vmap_area_root,
				&मुक्त_vmap_area_list);
		अगर (va)
			kasan_release_vदो_स्मृति(orig_start, orig_end,
				va->बहु_शुरू, va->बहु_पूर्ण);
		vas[area] = शून्य;
	पूर्ण

overflow:
	spin_unlock(&मुक्त_vmap_area_lock);
	अगर (!purged) अणु
		purge_vmap_area_lazy();
		purged = true;

		/* Beक्रमe "retry", check अगर we recover. */
		क्रम (area = 0; area < nr_vms; area++) अणु
			अगर (vas[area])
				जारी;

			vas[area] = kmem_cache_zalloc(
				vmap_area_cachep, GFP_KERNEL);
			अगर (!vas[area])
				जाओ err_मुक्त;
		पूर्ण

		जाओ retry;
	पूर्ण

err_मुक्त:
	क्रम (area = 0; area < nr_vms; area++) अणु
		अगर (vas[area])
			kmem_cache_मुक्त(vmap_area_cachep, vas[area]);

		kमुक्त(vms[area]);
	पूर्ण
err_मुक्त2:
	kमुक्त(vas);
	kमुक्त(vms);
	वापस शून्य;

err_मुक्त_shaकरोw:
	spin_lock(&मुक्त_vmap_area_lock);
	/*
	 * We release all the vदो_स्मृति shaकरोws, even the ones क्रम regions that
	 * hadn't been successfully added. This relies on kasan_release_vदो_स्मृति
	 * being able to tolerate this हाल.
	 */
	क्रम (area = 0; area < nr_vms; area++) अणु
		orig_start = vas[area]->बहु_शुरू;
		orig_end = vas[area]->बहु_पूर्ण;
		va = merge_or_add_vmap_area_augment(vas[area], &मुक्त_vmap_area_root,
				&मुक्त_vmap_area_list);
		अगर (va)
			kasan_release_vदो_स्मृति(orig_start, orig_end,
				va->बहु_शुरू, va->बहु_पूर्ण);
		vas[area] = शून्य;
		kमुक्त(vms[area]);
	पूर्ण
	spin_unlock(&मुक्त_vmap_area_lock);
	kमुक्त(vas);
	kमुक्त(vms);
	वापस शून्य;
पूर्ण

/**
 * pcpu_मुक्त_vm_areas - मुक्त vदो_स्मृति areas क्रम percpu allocator
 * @vms: vm_काष्ठा poपूर्णांकer array वापसed by pcpu_get_vm_areas()
 * @nr_vms: the number of allocated areas
 *
 * Free vm_काष्ठाs and the array allocated by pcpu_get_vm_areas().
 */
व्योम pcpu_मुक्त_vm_areas(काष्ठा vm_काष्ठा **vms, पूर्णांक nr_vms)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_vms; i++)
		मुक्त_vm_area(vms[i]);
	kमुक्त(vms);
पूर्ण
#पूर्ण_अगर	/* CONFIG_SMP */

#अगर_घोषित CONFIG_PRINTK
bool vदो_स्मृति_dump_obj(व्योम *object)
अणु
	काष्ठा vm_काष्ठा *vm;
	व्योम *objp = (व्योम *)PAGE_ALIGN((अचिन्हित दीर्घ)object);

	vm = find_vm_area(objp);
	अगर (!vm)
		वापस false;
	pr_cont(" %u-page vmalloc region starting at %#lx allocated at %pS\n",
		vm->nr_pages, (अचिन्हित दीर्घ)vm->addr, vm->caller);
	वापस true;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम *s_start(काष्ठा seq_file *m, loff_t *pos)
	__acquires(&vmap_purge_lock)
	__acquires(&vmap_area_lock)
अणु
	mutex_lock(&vmap_purge_lock);
	spin_lock(&vmap_area_lock);

	वापस seq_list_start(&vmap_area_list, *pos);
पूर्ण

अटल व्योम *s_next(काष्ठा seq_file *m, व्योम *p, loff_t *pos)
अणु
	वापस seq_list_next(p, &vmap_area_list, pos);
पूर्ण

अटल व्योम s_stop(काष्ठा seq_file *m, व्योम *p)
	__releases(&vmap_area_lock)
	__releases(&vmap_purge_lock)
अणु
	spin_unlock(&vmap_area_lock);
	mutex_unlock(&vmap_purge_lock);
पूर्ण

अटल व्योम show_numa_info(काष्ठा seq_file *m, काष्ठा vm_काष्ठा *v)
अणु
	अगर (IS_ENABLED(CONFIG_NUMA)) अणु
		अचिन्हित पूर्णांक nr, *counters = m->निजी;

		अगर (!counters)
			वापस;

		अगर (v->flags & VM_UNINITIALIZED)
			वापस;
		/* Pair with smp_wmb() in clear_vm_uninitialized_flag() */
		smp_rmb();

		स_रखो(counters, 0, nr_node_ids * माप(अचिन्हित पूर्णांक));

		क्रम (nr = 0; nr < v->nr_pages; nr++)
			counters[page_to_nid(v->pages[nr])]++;

		क्रम_each_node_state(nr, N_HIGH_MEMORY)
			अगर (counters[nr])
				seq_म_लिखो(m, " N%u=%u", nr, counters[nr]);
	पूर्ण
पूर्ण

अटल व्योम show_purge_info(काष्ठा seq_file *m)
अणु
	काष्ठा vmap_area *va;

	spin_lock(&purge_vmap_area_lock);
	list_क्रम_each_entry(va, &purge_vmap_area_list, list) अणु
		seq_म_लिखो(m, "0x%pK-0x%pK %7ld unpurged vm_area\n",
			(व्योम *)va->बहु_शुरू, (व्योम *)va->बहु_पूर्ण,
			va->बहु_पूर्ण - va->बहु_शुरू);
	पूर्ण
	spin_unlock(&purge_vmap_area_lock);
पूर्ण

अटल पूर्णांक s_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा vmap_area *va;
	काष्ठा vm_काष्ठा *v;

	va = list_entry(p, काष्ठा vmap_area, list);

	/*
	 * s_show can encounter race with हटाओ_vm_area, !vm on behalf
	 * of vmap area is being tear करोwn or vm_map_ram allocation.
	 */
	अगर (!va->vm) अणु
		seq_म_लिखो(m, "0x%pK-0x%pK %7ld vm_map_ram\n",
			(व्योम *)va->बहु_शुरू, (व्योम *)va->बहु_पूर्ण,
			va->बहु_पूर्ण - va->बहु_शुरू);

		वापस 0;
	पूर्ण

	v = va->vm;

	seq_म_लिखो(m, "0x%pK-0x%pK %7ld",
		v->addr, v->addr + v->size, v->size);

	अगर (v->caller)
		seq_म_लिखो(m, " %pS", v->caller);

	अगर (v->nr_pages)
		seq_म_लिखो(m, " pages=%d", v->nr_pages);

	अगर (v->phys_addr)
		seq_म_लिखो(m, " phys=%pa", &v->phys_addr);

	अगर (v->flags & VM_IOREMAP)
		seq_माला_दो(m, " ioremap");

	अगर (v->flags & VM_ALLOC)
		seq_माला_दो(m, " vmalloc");

	अगर (v->flags & VM_MAP)
		seq_माला_दो(m, " vmap");

	अगर (v->flags & VM_USERMAP)
		seq_माला_दो(m, " user");

	अगर (v->flags & VM_DMA_COHERENT)
		seq_माला_दो(m, " dma-coherent");

	अगर (is_vदो_स्मृति_addr(v->pages))
		seq_माला_दो(m, " vpages");

	show_numa_info(m, v);
	seq_अ_दो(m, '\n');

	/*
	 * As a final step, dump "unpurged" areas.
	 */
	अगर (list_is_last(&va->list, &vmap_area_list))
		show_purge_info(m);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations vदो_स्मृति_op = अणु
	.start = s_start,
	.next = s_next,
	.stop = s_stop,
	.show = s_show,
पूर्ण;

अटल पूर्णांक __init proc_vदो_स्मृति_init(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_NUMA))
		proc_create_seq_निजी("vmallocinfo", 0400, शून्य,
				&vदो_स्मृति_op,
				nr_node_ids * माप(अचिन्हित पूर्णांक), शून्य);
	अन्यथा
		proc_create_seq("vmallocinfo", 0400, शून्य, &vदो_स्मृति_op);
	वापस 0;
पूर्ण
module_init(proc_vदो_स्मृति_init);

#पूर्ण_अगर
