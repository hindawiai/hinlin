<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Page table allocation functions
 *
 *    Copyright IBM Corp. 2016
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/sysctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/gmap.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>

#अगर_घोषित CONFIG_PGSTE

पूर्णांक page_table_allocate_pgste = 0;
EXPORT_SYMBOL(page_table_allocate_pgste);

अटल काष्ठा ctl_table page_table_sysctl[] = अणु
	अणु
		.procname	= "allocate_pgste",
		.data		= &page_table_allocate_pgste,
		.maxlen		= माप(पूर्णांक),
		.mode		= S_IRUGO | S_IWUSR,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table page_table_sysctl_dir[] = अणु
	अणु
		.procname	= "vm",
		.maxlen		= 0,
		.mode		= 0555,
		.child		= page_table_sysctl,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init page_table_रेजिस्टर_sysctl(व्योम)
अणु
	वापस रेजिस्टर_sysctl_table(page_table_sysctl_dir) ? 0 : -ENOMEM;
पूर्ण
__initcall(page_table_रेजिस्टर_sysctl);

#पूर्ण_अगर /* CONFIG_PGSTE */

अचिन्हित दीर्घ *crst_table_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा page *page = alloc_pages(GFP_KERNEL, 2);

	अगर (!page)
		वापस शून्य;
	arch_set_page_dat(page, 2);
	वापस (अचिन्हित दीर्घ *) page_to_virt(page);
पूर्ण

व्योम crst_table_मुक्त(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ *table)
अणु
	मुक्त_pages((अचिन्हित दीर्घ) table, 2);
पूर्ण

अटल व्योम __crst_table_upgrade(व्योम *arg)
अणु
	काष्ठा mm_काष्ठा *mm = arg;

	/* change all active ASCEs to aव्योम the creation of new TLBs */
	अगर (current->active_mm == mm) अणु
		S390_lowcore.user_asce = mm->context.asce;
		__ctl_load(S390_lowcore.user_asce, 7, 7);
	पूर्ण
	__tlb_flush_local();
पूर्ण

पूर्णांक crst_table_upgrade(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ *pgd = शून्य, *p4d = शून्य, *__pgd;
	अचिन्हित दीर्घ asce_limit = mm->context.asce_limit;

	/* upgrade should only happen from 3 to 4, 3 to 5, or 4 to 5 levels */
	VM_BUG_ON(asce_limit < _REGION2_SIZE);

	अगर (end <= asce_limit)
		वापस 0;

	अगर (asce_limit == _REGION2_SIZE) अणु
		p4d = crst_table_alloc(mm);
		अगर (unlikely(!p4d))
			जाओ err_p4d;
		crst_table_init(p4d, _REGION2_ENTRY_EMPTY);
	पूर्ण
	अगर (end > _REGION1_SIZE) अणु
		pgd = crst_table_alloc(mm);
		अगर (unlikely(!pgd))
			जाओ err_pgd;
		crst_table_init(pgd, _REGION1_ENTRY_EMPTY);
	पूर्ण

	spin_lock_bh(&mm->page_table_lock);

	/*
	 * This routine माला_लो called with mmap_lock lock held and there is
	 * no reason to optimize क्रम the हाल of otherwise. However, अगर
	 * that would ever change, the below check will let us know.
	 */
	VM_BUG_ON(asce_limit != mm->context.asce_limit);

	अगर (p4d) अणु
		__pgd = (अचिन्हित दीर्घ *) mm->pgd;
		p4d_populate(mm, (p4d_t *) p4d, (pud_t *) __pgd);
		mm->pgd = (pgd_t *) p4d;
		mm->context.asce_limit = _REGION1_SIZE;
		mm->context.asce = __pa(mm->pgd) | _ASCE_TABLE_LENGTH |
			_ASCE_USER_BITS | _ASCE_TYPE_REGION2;
		mm_inc_nr_puds(mm);
	पूर्ण
	अगर (pgd) अणु
		__pgd = (अचिन्हित दीर्घ *) mm->pgd;
		pgd_populate(mm, (pgd_t *) pgd, (p4d_t *) __pgd);
		mm->pgd = (pgd_t *) pgd;
		mm->context.asce_limit = TASK_SIZE_MAX;
		mm->context.asce = __pa(mm->pgd) | _ASCE_TABLE_LENGTH |
			_ASCE_USER_BITS | _ASCE_TYPE_REGION1;
	पूर्ण

	spin_unlock_bh(&mm->page_table_lock);

	on_each_cpu(__crst_table_upgrade, mm, 0);

	वापस 0;

err_pgd:
	crst_table_मुक्त(mm, p4d);
err_p4d:
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक atomic_xor_bits(atomic_t *v, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक old, new;

	करो अणु
		old = atomic_पढ़ो(v);
		new = old ^ bits;
	पूर्ण जबतक (atomic_cmpxchg(v, old, new) != old);
	वापस new;
पूर्ण

#अगर_घोषित CONFIG_PGSTE

काष्ठा page *page_table_alloc_pgste(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा page *page;
	u64 *table;

	page = alloc_page(GFP_KERNEL);
	अगर (page) अणु
		table = (u64 *)page_to_virt(page);
		स_रखो64(table, _PAGE_INVALID, PTRS_PER_PTE);
		स_रखो64(table + PTRS_PER_PTE, 0, PTRS_PER_PTE);
	पूर्ण
	वापस page;
पूर्ण

व्योम page_table_मुक्त_pgste(काष्ठा page *page)
अणु
	__मुक्त_page(page);
पूर्ण

#पूर्ण_अगर /* CONFIG_PGSTE */

/*
 * page table entry allocation/मुक्त routines.
 */
अचिन्हित दीर्घ *page_table_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ *table;
	काष्ठा page *page;
	अचिन्हित पूर्णांक mask, bit;

	/* Try to get a fragment of a 4K page as a 2K page table */
	अगर (!mm_alloc_pgste(mm)) अणु
		table = शून्य;
		spin_lock_bh(&mm->context.lock);
		अगर (!list_empty(&mm->context.pgtable_list)) अणु
			page = list_first_entry(&mm->context.pgtable_list,
						काष्ठा page, lru);
			mask = atomic_पढ़ो(&page->_refcount) >> 24;
			mask = (mask | (mask >> 4)) & 3;
			अगर (mask != 3) अणु
				table = (अचिन्हित दीर्घ *) page_to_virt(page);
				bit = mask & 1;		/* =1 -> second 2K */
				अगर (bit)
					table += PTRS_PER_PTE;
				atomic_xor_bits(&page->_refcount,
							1U << (bit + 24));
				list_del(&page->lru);
			पूर्ण
		पूर्ण
		spin_unlock_bh(&mm->context.lock);
		अगर (table)
			वापस table;
	पूर्ण
	/* Allocate a fresh page */
	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस शून्य;
	अगर (!pgtable_pte_page_ctor(page)) अणु
		__मुक्त_page(page);
		वापस शून्य;
	पूर्ण
	arch_set_page_dat(page, 0);
	/* Initialize page table */
	table = (अचिन्हित दीर्घ *) page_to_virt(page);
	अगर (mm_alloc_pgste(mm)) अणु
		/* Return 4K page table with PGSTEs */
		atomic_xor_bits(&page->_refcount, 3 << 24);
		स_रखो64((u64 *)table, _PAGE_INVALID, PTRS_PER_PTE);
		स_रखो64((u64 *)table + PTRS_PER_PTE, 0, PTRS_PER_PTE);
	पूर्ण अन्यथा अणु
		/* Return the first 2K fragment of the page */
		atomic_xor_bits(&page->_refcount, 1 << 24);
		स_रखो64((u64 *)table, _PAGE_INVALID, 2 * PTRS_PER_PTE);
		spin_lock_bh(&mm->context.lock);
		list_add(&page->lru, &mm->context.pgtable_list);
		spin_unlock_bh(&mm->context.lock);
	पूर्ण
	वापस table;
पूर्ण

व्योम page_table_मुक्त(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ *table)
अणु
	काष्ठा page *page;
	अचिन्हित पूर्णांक bit, mask;

	page = virt_to_page(table);
	अगर (!mm_alloc_pgste(mm)) अणु
		/* Free 2K page table fragment of a 4K page */
		bit = ((अचिन्हित दीर्घ) table & ~PAGE_MASK)/(PTRS_PER_PTE*माप(pte_t));
		spin_lock_bh(&mm->context.lock);
		mask = atomic_xor_bits(&page->_refcount, 1U << (bit + 24));
		mask >>= 24;
		अगर (mask & 3)
			list_add(&page->lru, &mm->context.pgtable_list);
		अन्यथा
			list_del(&page->lru);
		spin_unlock_bh(&mm->context.lock);
		अगर (mask != 0)
			वापस;
	पूर्ण अन्यथा अणु
		atomic_xor_bits(&page->_refcount, 3U << 24);
	पूर्ण

	pgtable_pte_page_dtor(page);
	__मुक्त_page(page);
पूर्ण

व्योम page_table_मुक्त_rcu(काष्ठा mmu_gather *tlb, अचिन्हित दीर्घ *table,
			 अचिन्हित दीर्घ vmaddr)
अणु
	काष्ठा mm_काष्ठा *mm;
	काष्ठा page *page;
	अचिन्हित पूर्णांक bit, mask;

	mm = tlb->mm;
	page = virt_to_page(table);
	अगर (mm_alloc_pgste(mm)) अणु
		gmap_unlink(mm, table, vmaddr);
		table = (अचिन्हित दीर्घ *) ((अचिन्हित दीर्घ)table | 3);
		tlb_हटाओ_table(tlb, table);
		वापस;
	पूर्ण
	bit = ((अचिन्हित दीर्घ) table & ~PAGE_MASK) / (PTRS_PER_PTE*माप(pte_t));
	spin_lock_bh(&mm->context.lock);
	mask = atomic_xor_bits(&page->_refcount, 0x11U << (bit + 24));
	mask >>= 24;
	अगर (mask & 3)
		list_add_tail(&page->lru, &mm->context.pgtable_list);
	अन्यथा
		list_del(&page->lru);
	spin_unlock_bh(&mm->context.lock);
	table = (अचिन्हित दीर्घ *) ((अचिन्हित दीर्घ) table | (1U << bit));
	tlb_हटाओ_table(tlb, table);
पूर्ण

व्योम __tlb_हटाओ_table(व्योम *_table)
अणु
	अचिन्हित पूर्णांक mask = (अचिन्हित दीर्घ) _table & 3;
	व्योम *table = (व्योम *)((अचिन्हित दीर्घ) _table ^ mask);
	काष्ठा page *page = virt_to_page(table);

	चयन (mask) अणु
	हाल 0:		/* pmd, pud, or p4d */
		मुक्त_pages((अचिन्हित दीर्घ) table, 2);
		अवरोध;
	हाल 1:		/* lower 2K of a 4K page table */
	हाल 2:		/* higher 2K of a 4K page table */
		mask = atomic_xor_bits(&page->_refcount, mask << (4 + 24));
		mask >>= 24;
		अगर (mask != 0)
			अवरोध;
		fallthrough;
	हाल 3:		/* 4K page table with pgstes */
		अगर (mask & 3)
			atomic_xor_bits(&page->_refcount, 3 << 24);
		pgtable_pte_page_dtor(page);
		__मुक्त_page(page);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Base infraकाष्ठाure required to generate basic asces, region, segment,
 * and page tables that करो not make use of enhanced features like EDAT1.
 */

अटल काष्ठा kmem_cache *base_pgt_cache;

अटल अचिन्हित दीर्घ base_pgt_alloc(व्योम)
अणु
	u64 *table;

	table = kmem_cache_alloc(base_pgt_cache, GFP_KERNEL);
	अगर (table)
		स_रखो64(table, _PAGE_INVALID, PTRS_PER_PTE);
	वापस (अचिन्हित दीर्घ) table;
पूर्ण

अटल व्योम base_pgt_मुक्त(अचिन्हित दीर्घ table)
अणु
	kmem_cache_मुक्त(base_pgt_cache, (व्योम *) table);
पूर्ण

अटल अचिन्हित दीर्घ base_crst_alloc(अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ table;

	table =	 __get_मुक्त_pages(GFP_KERNEL, CRST_ALLOC_ORDER);
	अगर (table)
		crst_table_init((अचिन्हित दीर्घ *)table, val);
	वापस table;
पूर्ण

अटल व्योम base_crst_मुक्त(अचिन्हित दीर्घ table)
अणु
	मुक्त_pages(table, CRST_ALLOC_ORDER);
पूर्ण

#घोषणा BASE_ADDR_END_FUNC(NAME, SIZE)					\
अटल अंतरभूत अचिन्हित दीर्घ base_##NAME##_addr_end(अचिन्हित दीर्घ addr,	\
						   अचिन्हित दीर्घ end)	\
अणु									\
	अचिन्हित दीर्घ next = (addr + (SIZE)) & ~((SIZE) - 1);		\
									\
	वापस (next - 1) < (end - 1) ? next : end;			\
पूर्ण

BASE_ADDR_END_FUNC(page,    _PAGE_SIZE)
BASE_ADDR_END_FUNC(segment, _SEGMENT_SIZE)
BASE_ADDR_END_FUNC(region3, _REGION3_SIZE)
BASE_ADDR_END_FUNC(region2, _REGION2_SIZE)
BASE_ADDR_END_FUNC(region1, _REGION1_SIZE)

अटल अंतरभूत अचिन्हित दीर्घ base_lra(अचिन्हित दीर्घ address)
अणु
	अचिन्हित दीर्घ real;

	यंत्र अस्थिर(
		"	lra	%0,0(%1)\n"
		: "=d" (real) : "a" (address) : "cc");
	वापस real;
पूर्ण

अटल पूर्णांक base_page_walk(अचिन्हित दीर्घ origin, अचिन्हित दीर्घ addr,
			  अचिन्हित दीर्घ end, पूर्णांक alloc)
अणु
	अचिन्हित दीर्घ *pte, next;

	अगर (!alloc)
		वापस 0;
	pte = (अचिन्हित दीर्घ *) origin;
	pte += (addr & _PAGE_INDEX) >> _PAGE_SHIFT;
	करो अणु
		next = base_page_addr_end(addr, end);
		*pte = base_lra(addr);
	पूर्ण जबतक (pte++, addr = next, addr < end);
	वापस 0;
पूर्ण

अटल पूर्णांक base_segment_walk(अचिन्हित दीर्घ origin, अचिन्हित दीर्घ addr,
			     अचिन्हित दीर्घ end, पूर्णांक alloc)
अणु
	अचिन्हित दीर्घ *ste, next, table;
	पूर्णांक rc;

	ste = (अचिन्हित दीर्घ *) origin;
	ste += (addr & _SEGMENT_INDEX) >> _SEGMENT_SHIFT;
	करो अणु
		next = base_segment_addr_end(addr, end);
		अगर (*ste & _SEGMENT_ENTRY_INVALID) अणु
			अगर (!alloc)
				जारी;
			table = base_pgt_alloc();
			अगर (!table)
				वापस -ENOMEM;
			*ste = table | _SEGMENT_ENTRY;
		पूर्ण
		table = *ste & _SEGMENT_ENTRY_ORIGIN;
		rc = base_page_walk(table, addr, next, alloc);
		अगर (rc)
			वापस rc;
		अगर (!alloc)
			base_pgt_मुक्त(table);
		cond_resched();
	पूर्ण जबतक (ste++, addr = next, addr < end);
	वापस 0;
पूर्ण

अटल पूर्णांक base_region3_walk(अचिन्हित दीर्घ origin, अचिन्हित दीर्घ addr,
			     अचिन्हित दीर्घ end, पूर्णांक alloc)
अणु
	अचिन्हित दीर्घ *rtte, next, table;
	पूर्णांक rc;

	rtte = (अचिन्हित दीर्घ *) origin;
	rtte += (addr & _REGION3_INDEX) >> _REGION3_SHIFT;
	करो अणु
		next = base_region3_addr_end(addr, end);
		अगर (*rtte & _REGION_ENTRY_INVALID) अणु
			अगर (!alloc)
				जारी;
			table = base_crst_alloc(_SEGMENT_ENTRY_EMPTY);
			अगर (!table)
				वापस -ENOMEM;
			*rtte = table | _REGION3_ENTRY;
		पूर्ण
		table = *rtte & _REGION_ENTRY_ORIGIN;
		rc = base_segment_walk(table, addr, next, alloc);
		अगर (rc)
			वापस rc;
		अगर (!alloc)
			base_crst_मुक्त(table);
	पूर्ण जबतक (rtte++, addr = next, addr < end);
	वापस 0;
पूर्ण

अटल पूर्णांक base_region2_walk(अचिन्हित दीर्घ origin, अचिन्हित दीर्घ addr,
			     अचिन्हित दीर्घ end, पूर्णांक alloc)
अणु
	अचिन्हित दीर्घ *rste, next, table;
	पूर्णांक rc;

	rste = (अचिन्हित दीर्घ *) origin;
	rste += (addr & _REGION2_INDEX) >> _REGION2_SHIFT;
	करो अणु
		next = base_region2_addr_end(addr, end);
		अगर (*rste & _REGION_ENTRY_INVALID) अणु
			अगर (!alloc)
				जारी;
			table = base_crst_alloc(_REGION3_ENTRY_EMPTY);
			अगर (!table)
				वापस -ENOMEM;
			*rste = table | _REGION2_ENTRY;
		पूर्ण
		table = *rste & _REGION_ENTRY_ORIGIN;
		rc = base_region3_walk(table, addr, next, alloc);
		अगर (rc)
			वापस rc;
		अगर (!alloc)
			base_crst_मुक्त(table);
	पूर्ण जबतक (rste++, addr = next, addr < end);
	वापस 0;
पूर्ण

अटल पूर्णांक base_region1_walk(अचिन्हित दीर्घ origin, अचिन्हित दीर्घ addr,
			     अचिन्हित दीर्घ end, पूर्णांक alloc)
अणु
	अचिन्हित दीर्घ *rfte, next, table;
	पूर्णांक rc;

	rfte = (अचिन्हित दीर्घ *) origin;
	rfte += (addr & _REGION1_INDEX) >> _REGION1_SHIFT;
	करो अणु
		next = base_region1_addr_end(addr, end);
		अगर (*rfte & _REGION_ENTRY_INVALID) अणु
			अगर (!alloc)
				जारी;
			table = base_crst_alloc(_REGION2_ENTRY_EMPTY);
			अगर (!table)
				वापस -ENOMEM;
			*rfte = table | _REGION1_ENTRY;
		पूर्ण
		table = *rfte & _REGION_ENTRY_ORIGIN;
		rc = base_region2_walk(table, addr, next, alloc);
		अगर (rc)
			वापस rc;
		अगर (!alloc)
			base_crst_मुक्त(table);
	पूर्ण जबतक (rfte++, addr = next, addr < end);
	वापस 0;
पूर्ण

/**
 * base_asce_मुक्त - मुक्त asce and tables वापसed from base_asce_alloc()
 * @asce: asce to be मुक्तd
 *
 * Frees all region, segment, and page tables that were allocated with a
 * corresponding base_asce_alloc() call.
 */
व्योम base_asce_मुक्त(अचिन्हित दीर्घ asce)
अणु
	अचिन्हित दीर्घ table = asce & _ASCE_ORIGIN;

	अगर (!asce)
		वापस;
	चयन (asce & _ASCE_TYPE_MASK) अणु
	हाल _ASCE_TYPE_SEGMENT:
		base_segment_walk(table, 0, _REGION3_SIZE, 0);
		अवरोध;
	हाल _ASCE_TYPE_REGION3:
		base_region3_walk(table, 0, _REGION2_SIZE, 0);
		अवरोध;
	हाल _ASCE_TYPE_REGION2:
		base_region2_walk(table, 0, _REGION1_SIZE, 0);
		अवरोध;
	हाल _ASCE_TYPE_REGION1:
		base_region1_walk(table, 0, TASK_SIZE_MAX, 0);
		अवरोध;
	पूर्ण
	base_crst_मुक्त(table);
पूर्ण

अटल पूर्णांक base_pgt_cache_init(व्योम)
अणु
	अटल DEFINE_MUTEX(base_pgt_cache_mutex);
	अचिन्हित दीर्घ sz = _PAGE_TABLE_SIZE;

	अगर (base_pgt_cache)
		वापस 0;
	mutex_lock(&base_pgt_cache_mutex);
	अगर (!base_pgt_cache)
		base_pgt_cache = kmem_cache_create("base_pgt", sz, sz, 0, शून्य);
	mutex_unlock(&base_pgt_cache_mutex);
	वापस base_pgt_cache ? 0 : -ENOMEM;
पूर्ण

/**
 * base_asce_alloc - create kernel mapping without enhanced DAT features
 * @addr: भव start address of kernel mapping
 * @num_pages: number of consecutive pages
 *
 * Generate an asce, including all required region, segment and page tables,
 * that can be used to access the भव kernel mapping. The dअगरference is
 * that the वापसed asce करोes not make use of any enhanced DAT features like
 * e.g. large pages. This is required क्रम some I/O functions that pass an
 * asce, like e.g. some service call requests.
 *
 * Note: the वापसed asce may NEVER be attached to any cpu. It may only be
 *	 used क्रम I/O requests. tlb entries that might result because the
 *	 asce was attached to a cpu won't be cleared.
 */
अचिन्हित दीर्घ base_asce_alloc(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ num_pages)
अणु
	अचिन्हित दीर्घ asce, table, end;
	पूर्णांक rc;

	अगर (base_pgt_cache_init())
		वापस 0;
	end = addr + num_pages * PAGE_SIZE;
	अगर (end <= _REGION3_SIZE) अणु
		table = base_crst_alloc(_SEGMENT_ENTRY_EMPTY);
		अगर (!table)
			वापस 0;
		rc = base_segment_walk(table, addr, end, 1);
		asce = table | _ASCE_TYPE_SEGMENT | _ASCE_TABLE_LENGTH;
	पूर्ण अन्यथा अगर (end <= _REGION2_SIZE) अणु
		table = base_crst_alloc(_REGION3_ENTRY_EMPTY);
		अगर (!table)
			वापस 0;
		rc = base_region3_walk(table, addr, end, 1);
		asce = table | _ASCE_TYPE_REGION3 | _ASCE_TABLE_LENGTH;
	पूर्ण अन्यथा अगर (end <= _REGION1_SIZE) अणु
		table = base_crst_alloc(_REGION2_ENTRY_EMPTY);
		अगर (!table)
			वापस 0;
		rc = base_region2_walk(table, addr, end, 1);
		asce = table | _ASCE_TYPE_REGION2 | _ASCE_TABLE_LENGTH;
	पूर्ण अन्यथा अणु
		table = base_crst_alloc(_REGION1_ENTRY_EMPTY);
		अगर (!table)
			वापस 0;
		rc = base_region1_walk(table, addr, end, 1);
		asce = table | _ASCE_TYPE_REGION1 | _ASCE_TABLE_LENGTH;
	पूर्ण
	अगर (rc) अणु
		base_asce_मुक्त(asce);
		asce = 0;
	पूर्ण
	वापस asce;
पूर्ण
