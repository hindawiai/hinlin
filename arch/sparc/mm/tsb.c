<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* arch/sparc64/mm/tsb.c
 *
 * Copyright (C) 2006, 2008 David S. Miller <davem@davemloft.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/preempt.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/tsb.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/oplib.h>

बाह्य काष्ठा tsb swapper_tsb[KERNEL_TSB_NENTRIES];

अटल अंतरभूत अचिन्हित दीर्घ tsb_hash(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ hash_shअगरt, अचिन्हित दीर्घ nentries)
अणु
	vaddr >>= hash_shअगरt;
	वापस vaddr & (nentries - 1);
पूर्ण

अटल अंतरभूत पूर्णांक tag_compare(अचिन्हित दीर्घ tag, अचिन्हित दीर्घ vaddr)
अणु
	वापस (tag == (vaddr >> 22));
पूर्ण

अटल व्योम flush_tsb_kernel_range_scan(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ idx;

	क्रम (idx = 0; idx < KERNEL_TSB_NENTRIES; idx++) अणु
		काष्ठा tsb *ent = &swapper_tsb[idx];
		अचिन्हित दीर्घ match = idx << 13;

		match |= (ent->tag << 22);
		अगर (match >= start && match < end)
			ent->tag = (1UL << TSB_TAG_INVALID_BIT);
	पूर्ण
पूर्ण

/* TSB flushes need only occur on the processor initiating the address
 * space modअगरication, not on each cpu the address space has run on.
 * Only the TLB flush needs that treaपंचांगent.
 */

व्योम flush_tsb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ v;

	अगर ((end - start) >> PAGE_SHIFT >= 2 * KERNEL_TSB_NENTRIES)
		वापस flush_tsb_kernel_range_scan(start, end);

	क्रम (v = start; v < end; v += PAGE_SIZE) अणु
		अचिन्हित दीर्घ hash = tsb_hash(v, PAGE_SHIFT,
					      KERNEL_TSB_NENTRIES);
		काष्ठा tsb *ent = &swapper_tsb[hash];

		अगर (tag_compare(ent->tag, v))
			ent->tag = (1UL << TSB_TAG_INVALID_BIT);
	पूर्ण
पूर्ण

अटल व्योम __flush_tsb_one_entry(अचिन्हित दीर्घ tsb, अचिन्हित दीर्घ v,
				  अचिन्हित दीर्घ hash_shअगरt,
				  अचिन्हित दीर्घ nentries)
अणु
	अचिन्हित दीर्घ tag, ent, hash;

	v &= ~0x1UL;
	hash = tsb_hash(v, hash_shअगरt, nentries);
	ent = tsb + (hash * माप(काष्ठा tsb));
	tag = (v >> 22UL);

	tsb_flush(ent, tag);
पूर्ण

अटल व्योम __flush_tsb_one(काष्ठा tlb_batch *tb, अचिन्हित दीर्घ hash_shअगरt,
			    अचिन्हित दीर्घ tsb, अचिन्हित दीर्घ nentries)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < tb->tlb_nr; i++)
		__flush_tsb_one_entry(tsb, tb->vaddrs[i], hash_shअगरt, nentries);
पूर्ण

#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
अटल व्योम __flush_huge_tsb_one_entry(अचिन्हित दीर्घ tsb, अचिन्हित दीर्घ v,
				       अचिन्हित दीर्घ hash_shअगरt,
				       अचिन्हित दीर्घ nentries,
				       अचिन्हित पूर्णांक hugepage_shअगरt)
अणु
	अचिन्हित पूर्णांक hpage_entries;
	अचिन्हित पूर्णांक i;

	hpage_entries = 1 << (hugepage_shअगरt - hash_shअगरt);
	क्रम (i = 0; i < hpage_entries; i++)
		__flush_tsb_one_entry(tsb, v + (i << hash_shअगरt), hash_shअगरt,
				      nentries);
पूर्ण

अटल व्योम __flush_huge_tsb_one(काष्ठा tlb_batch *tb, अचिन्हित दीर्घ hash_shअगरt,
				 अचिन्हित दीर्घ tsb, अचिन्हित दीर्घ nentries,
				 अचिन्हित पूर्णांक hugepage_shअगरt)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < tb->tlb_nr; i++)
		__flush_huge_tsb_one_entry(tsb, tb->vaddrs[i], hash_shअगरt,
					   nentries, hugepage_shअगरt);
पूर्ण
#पूर्ण_अगर

व्योम flush_tsb_user(काष्ठा tlb_batch *tb)
अणु
	काष्ठा mm_काष्ठा *mm = tb->mm;
	अचिन्हित दीर्घ nentries, base, flags;

	spin_lock_irqsave(&mm->context.lock, flags);

	अगर (tb->hugepage_shअगरt < REAL_HPAGE_SHIFT) अणु
		base = (अचिन्हित दीर्घ) mm->context.tsb_block[MM_TSB_BASE].tsb;
		nentries = mm->context.tsb_block[MM_TSB_BASE].tsb_nentries;
		अगर (tlb_type == cheetah_plus || tlb_type == hypervisor)
			base = __pa(base);
		अगर (tb->hugepage_shअगरt == PAGE_SHIFT)
			__flush_tsb_one(tb, PAGE_SHIFT, base, nentries);
#अगर defined(CONFIG_HUGETLB_PAGE)
		अन्यथा
			__flush_huge_tsb_one(tb, PAGE_SHIFT, base, nentries,
					     tb->hugepage_shअगरt);
#पूर्ण_अगर
	पूर्ण
#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
	अन्यथा अगर (mm->context.tsb_block[MM_TSB_HUGE].tsb) अणु
		base = (अचिन्हित दीर्घ) mm->context.tsb_block[MM_TSB_HUGE].tsb;
		nentries = mm->context.tsb_block[MM_TSB_HUGE].tsb_nentries;
		अगर (tlb_type == cheetah_plus || tlb_type == hypervisor)
			base = __pa(base);
		__flush_huge_tsb_one(tb, REAL_HPAGE_SHIFT, base, nentries,
				     tb->hugepage_shअगरt);
	पूर्ण
#पूर्ण_अगर
	spin_unlock_irqrestore(&mm->context.lock, flags);
पूर्ण

व्योम flush_tsb_user_page(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr,
			 अचिन्हित पूर्णांक hugepage_shअगरt)
अणु
	अचिन्हित दीर्घ nentries, base, flags;

	spin_lock_irqsave(&mm->context.lock, flags);

	अगर (hugepage_shअगरt < REAL_HPAGE_SHIFT) अणु
		base = (अचिन्हित दीर्घ) mm->context.tsb_block[MM_TSB_BASE].tsb;
		nentries = mm->context.tsb_block[MM_TSB_BASE].tsb_nentries;
		अगर (tlb_type == cheetah_plus || tlb_type == hypervisor)
			base = __pa(base);
		अगर (hugepage_shअगरt == PAGE_SHIFT)
			__flush_tsb_one_entry(base, vaddr, PAGE_SHIFT,
					      nentries);
#अगर defined(CONFIG_HUGETLB_PAGE)
		अन्यथा
			__flush_huge_tsb_one_entry(base, vaddr, PAGE_SHIFT,
						   nentries, hugepage_shअगरt);
#पूर्ण_अगर
	पूर्ण
#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
	अन्यथा अगर (mm->context.tsb_block[MM_TSB_HUGE].tsb) अणु
		base = (अचिन्हित दीर्घ) mm->context.tsb_block[MM_TSB_HUGE].tsb;
		nentries = mm->context.tsb_block[MM_TSB_HUGE].tsb_nentries;
		अगर (tlb_type == cheetah_plus || tlb_type == hypervisor)
			base = __pa(base);
		__flush_huge_tsb_one_entry(base, vaddr, REAL_HPAGE_SHIFT,
					   nentries, hugepage_shअगरt);
	पूर्ण
#पूर्ण_अगर
	spin_unlock_irqrestore(&mm->context.lock, flags);
पूर्ण

#घोषणा HV_PGSZ_IDX_BASE	HV_PGSZ_IDX_8K
#घोषणा HV_PGSZ_MASK_BASE	HV_PGSZ_MASK_8K

#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
#घोषणा HV_PGSZ_IDX_HUGE	HV_PGSZ_IDX_4MB
#घोषणा HV_PGSZ_MASK_HUGE	HV_PGSZ_MASK_4MB
#पूर्ण_अगर

अटल व्योम setup_tsb_params(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ tsb_idx, अचिन्हित दीर्घ tsb_bytes)
अणु
	अचिन्हित दीर्घ tsb_reg, base, tsb_paddr;
	अचिन्हित दीर्घ page_sz, tte;

	mm->context.tsb_block[tsb_idx].tsb_nentries =
		tsb_bytes / माप(काष्ठा tsb);

	चयन (tsb_idx) अणु
	हाल MM_TSB_BASE:
		base = TSBMAP_8K_BASE;
		अवरोध;
#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
	हाल MM_TSB_HUGE:
		base = TSBMAP_4M_BASE;
		अवरोध;
#पूर्ण_अगर
	शेष:
		BUG();
	पूर्ण

	tte = pgprot_val(PAGE_KERNEL_LOCKED);
	tsb_paddr = __pa(mm->context.tsb_block[tsb_idx].tsb);
	BUG_ON(tsb_paddr & (tsb_bytes - 1UL));

	/* Use the smallest page size that can map the whole TSB
	 * in one TLB entry.
	 */
	चयन (tsb_bytes) अणु
	हाल 8192 << 0:
		tsb_reg = 0x0UL;
#अगर_घोषित DCACHE_ALIASING_POSSIBLE
		base += (tsb_paddr & 8192);
#पूर्ण_अगर
		page_sz = 8192;
		अवरोध;

	हाल 8192 << 1:
		tsb_reg = 0x1UL;
		page_sz = 64 * 1024;
		अवरोध;

	हाल 8192 << 2:
		tsb_reg = 0x2UL;
		page_sz = 64 * 1024;
		अवरोध;

	हाल 8192 << 3:
		tsb_reg = 0x3UL;
		page_sz = 64 * 1024;
		अवरोध;

	हाल 8192 << 4:
		tsb_reg = 0x4UL;
		page_sz = 512 * 1024;
		अवरोध;

	हाल 8192 << 5:
		tsb_reg = 0x5UL;
		page_sz = 512 * 1024;
		अवरोध;

	हाल 8192 << 6:
		tsb_reg = 0x6UL;
		page_sz = 512 * 1024;
		अवरोध;

	हाल 8192 << 7:
		tsb_reg = 0x7UL;
		page_sz = 4 * 1024 * 1024;
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "TSB[%s:%d]: Impossible TSB size %lu, killing process.\n",
		       current->comm, current->pid, tsb_bytes);
		करो_निकास(संक_अंश);
	पूर्ण
	tte |= pte_sz_bits(page_sz);

	अगर (tlb_type == cheetah_plus || tlb_type == hypervisor) अणु
		/* Physical mapping, no locked TLB entry क्रम TSB.  */
		tsb_reg |= tsb_paddr;

		mm->context.tsb_block[tsb_idx].tsb_reg_val = tsb_reg;
		mm->context.tsb_block[tsb_idx].tsb_map_vaddr = 0;
		mm->context.tsb_block[tsb_idx].tsb_map_pte = 0;
	पूर्ण अन्यथा अणु
		tsb_reg |= base;
		tsb_reg |= (tsb_paddr & (page_sz - 1UL));
		tte |= (tsb_paddr & ~(page_sz - 1UL));

		mm->context.tsb_block[tsb_idx].tsb_reg_val = tsb_reg;
		mm->context.tsb_block[tsb_idx].tsb_map_vaddr = base;
		mm->context.tsb_block[tsb_idx].tsb_map_pte = tte;
	पूर्ण

	/* Setup the Hypervisor TSB descriptor.  */
	अगर (tlb_type == hypervisor) अणु
		काष्ठा hv_tsb_descr *hp = &mm->context.tsb_descr[tsb_idx];

		चयन (tsb_idx) अणु
		हाल MM_TSB_BASE:
			hp->pgsz_idx = HV_PGSZ_IDX_BASE;
			अवरोध;
#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
		हाल MM_TSB_HUGE:
			hp->pgsz_idx = HV_PGSZ_IDX_HUGE;
			अवरोध;
#पूर्ण_अगर
		शेष:
			BUG();
		पूर्ण
		hp->assoc = 1;
		hp->num_ttes = tsb_bytes / 16;
		hp->ctx_idx = 0;
		चयन (tsb_idx) अणु
		हाल MM_TSB_BASE:
			hp->pgsz_mask = HV_PGSZ_MASK_BASE;
			अवरोध;
#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
		हाल MM_TSB_HUGE:
			hp->pgsz_mask = HV_PGSZ_MASK_HUGE;
			अवरोध;
#पूर्ण_अगर
		शेष:
			BUG();
		पूर्ण
		hp->tsb_base = tsb_paddr;
		hp->resv = 0;
	पूर्ण
पूर्ण

काष्ठा kmem_cache *pgtable_cache __पढ़ो_mostly;

अटल काष्ठा kmem_cache *tsb_caches[8] __पढ़ो_mostly;

अटल स्थिर अक्षर *tsb_cache_names[8] = अणु
	"tsb_8KB",
	"tsb_16KB",
	"tsb_32KB",
	"tsb_64KB",
	"tsb_128KB",
	"tsb_256KB",
	"tsb_512KB",
	"tsb_1MB",
पूर्ण;

व्योम __init pgtable_cache_init(व्योम)
अणु
	अचिन्हित दीर्घ i;

	pgtable_cache = kmem_cache_create("pgtable_cache",
					  PAGE_SIZE, PAGE_SIZE,
					  0,
					  _clear_page);
	अगर (!pgtable_cache) अणु
		prom_म_लिखो("pgtable_cache_init(): Could not create!\n");
		prom_halt();
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tsb_cache_names); i++) अणु
		अचिन्हित दीर्घ size = 8192 << i;
		स्थिर अक्षर *name = tsb_cache_names[i];

		tsb_caches[i] = kmem_cache_create(name,
						  size, size,
						  0, शून्य);
		अगर (!tsb_caches[i]) अणु
			prom_म_लिखो("Could not create %s cache\n", name);
			prom_halt();
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक sysctl_tsb_ratio = -2;

अटल अचिन्हित दीर्घ tsb_माप_प्रकारo_rss_limit(अचिन्हित दीर्घ new_size)
अणु
	अचिन्हित दीर्घ num_ents = (new_size / माप(काष्ठा tsb));

	अगर (sysctl_tsb_ratio < 0)
		वापस num_ents - (num_ents >> -sysctl_tsb_ratio);
	अन्यथा
		वापस num_ents + (num_ents >> sysctl_tsb_ratio);
पूर्ण

/* When the RSS of an address space exceeds tsb_rss_limit क्रम a TSB,
 * करो_sparc64_fault() invokes this routine to try and grow it.
 *
 * When we reach the maximum TSB size supported, we stick ~0UL पूर्णांकo
 * tsb_rss_limit क्रम that TSB so the grow checks in करो_sparc64_fault()
 * will not trigger any दीर्घer.
 *
 * The TSB can be anywhere from 8K to 1MB in size, in increasing घातers
 * of two.  The TSB must be aligned to it's size, so f.e. a 512K TSB
 * must be 512K aligned.  It also must be physically contiguous, so we
 * cannot use vदो_स्मृति().
 *
 * The idea here is to grow the TSB when the RSS of the process approaches
 * the number of entries that the current TSB can hold at once.  Currently,
 * we trigger when the RSS hits 3/4 of the TSB capacity.
 */
व्योम tsb_grow(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ tsb_index, अचिन्हित दीर्घ rss)
अणु
	अचिन्हित दीर्घ max_tsb_size = 1 * 1024 * 1024;
	अचिन्हित दीर्घ new_size, old_size, flags;
	काष्ठा tsb *old_tsb, *new_tsb;
	अचिन्हित दीर्घ new_cache_index, old_cache_index;
	अचिन्हित दीर्घ new_rss_limit;
	gfp_t gfp_flags;

	अगर (max_tsb_size > (PAGE_SIZE << MAX_ORDER))
		max_tsb_size = (PAGE_SIZE << MAX_ORDER);

	new_cache_index = 0;
	क्रम (new_size = 8192; new_size < max_tsb_size; new_size <<= 1UL) अणु
		new_rss_limit = tsb_माप_प्रकारo_rss_limit(new_size);
		अगर (new_rss_limit > rss)
			अवरोध;
		new_cache_index++;
	पूर्ण

	अगर (new_size == max_tsb_size)
		new_rss_limit = ~0UL;

retry_tsb_alloc:
	gfp_flags = GFP_KERNEL;
	अगर (new_size > (PAGE_SIZE * 2))
		gfp_flags |= __GFP_NOWARN | __GFP_NORETRY;

	new_tsb = kmem_cache_alloc_node(tsb_caches[new_cache_index],
					gfp_flags, numa_node_id());
	अगर (unlikely(!new_tsb)) अणु
		/* Not being able to विभाजन due to a high-order TSB
		 * allocation failure is very bad behavior.  Just back
		 * करोwn to a 0-order allocation and क्रमce no TSB
		 * growing क्रम this address space.
		 */
		अगर (mm->context.tsb_block[tsb_index].tsb == शून्य &&
		    new_cache_index > 0) अणु
			new_cache_index = 0;
			new_size = 8192;
			new_rss_limit = ~0UL;
			जाओ retry_tsb_alloc;
		पूर्ण

		/* If we failed on a TSB grow, we are under serious
		 * memory pressure so करोn't try to grow any more.
		 */
		अगर (mm->context.tsb_block[tsb_index].tsb != शून्य)
			mm->context.tsb_block[tsb_index].tsb_rss_limit = ~0UL;
		वापस;
	पूर्ण

	/* Mark all tags as invalid.  */
	tsb_init(new_tsb, new_size);

	/* Ok, we are about to commit the changes.  If we are
	 * growing an existing TSB the locking is very tricky,
	 * so WATCH OUT!
	 *
	 * We have to hold mm->context.lock जबतक committing to the
	 * new TSB, this synchronizes us with processors in
	 * flush_tsb_user() and चयन_mm() क्रम this address space.
	 *
	 * But even with that lock held, processors run asynchronously
	 * accessing the old TSB via TLB miss handling.  This is OK
	 * because those actions are just propagating state from the
	 * Linux page tables पूर्णांकo the TSB, page table mappings are not
	 * being changed.  If a real fault occurs, the processor will
	 * synchronize with us when it hits flush_tsb_user(), this is
	 * also true क्रम the हाल where vmscan is modअगरying the page
	 * tables.  The only thing we need to be careful with is to
	 * skip any locked TSB entries during copy_tsb().
	 *
	 * When we finish committing to the new TSB, we have to drop
	 * the lock and ask all other cpus running this address space
	 * to run tsb_context_चयन() to see the new TSB table.
	 */
	spin_lock_irqsave(&mm->context.lock, flags);

	old_tsb = mm->context.tsb_block[tsb_index].tsb;
	old_cache_index =
		(mm->context.tsb_block[tsb_index].tsb_reg_val & 0x7UL);
	old_size = (mm->context.tsb_block[tsb_index].tsb_nentries *
		    माप(काष्ठा tsb));


	/* Handle multiple thपढ़ोs trying to grow the TSB at the same समय.
	 * One will get in here first, and bump the size and the RSS limit.
	 * The others will get in here next and hit this check.
	 */
	अगर (unlikely(old_tsb &&
		     (rss < mm->context.tsb_block[tsb_index].tsb_rss_limit))) अणु
		spin_unlock_irqrestore(&mm->context.lock, flags);

		kmem_cache_मुक्त(tsb_caches[new_cache_index], new_tsb);
		वापस;
	पूर्ण

	mm->context.tsb_block[tsb_index].tsb_rss_limit = new_rss_limit;

	अगर (old_tsb) अणु
		बाह्य व्योम copy_tsb(अचिन्हित दीर्घ old_tsb_base,
				     अचिन्हित दीर्घ old_tsb_size,
				     अचिन्हित दीर्घ new_tsb_base,
				     अचिन्हित दीर्घ new_tsb_size,
				     अचिन्हित दीर्घ page_size_shअगरt);
		अचिन्हित दीर्घ old_tsb_base = (अचिन्हित दीर्घ) old_tsb;
		अचिन्हित दीर्घ new_tsb_base = (अचिन्हित दीर्घ) new_tsb;

		अगर (tlb_type == cheetah_plus || tlb_type == hypervisor) अणु
			old_tsb_base = __pa(old_tsb_base);
			new_tsb_base = __pa(new_tsb_base);
		पूर्ण
		copy_tsb(old_tsb_base, old_size, new_tsb_base, new_size,
			tsb_index == MM_TSB_BASE ?
			PAGE_SHIFT : REAL_HPAGE_SHIFT);
	पूर्ण

	mm->context.tsb_block[tsb_index].tsb = new_tsb;
	setup_tsb_params(mm, tsb_index, new_size);

	spin_unlock_irqrestore(&mm->context.lock, flags);

	/* If old_tsb is शून्य, we're being invoked क्रम the first समय
	 * from init_new_context().
	 */
	अगर (old_tsb) अणु
		/* Reload it on the local cpu.  */
		tsb_context_चयन(mm);

		/* Now क्रमce other processors to करो the same.  */
		preempt_disable();
		smp_tsb_sync(mm);
		preempt_enable();

		/* Now it is safe to मुक्त the old tsb.  */
		kmem_cache_मुक्त(tsb_caches[old_cache_index], old_tsb);
	पूर्ण
पूर्ण

पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ mm_rss = get_mm_rss(mm);
#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
	अचिन्हित दीर्घ saved_hugetlb_pte_count;
	अचिन्हित दीर्घ saved_thp_pte_count;
#पूर्ण_अगर
	अचिन्हित पूर्णांक i;

	spin_lock_init(&mm->context.lock);

	mm->context.sparc64_ctx_val = 0UL;

	mm->context.tag_store = शून्य;
	spin_lock_init(&mm->context.tag_lock);

#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
	/* We reset them to zero because the विभाजन() page copying
	 * will re-increment the counters as the parent PTEs are
	 * copied पूर्णांकo the child address space.
	 */
	saved_hugetlb_pte_count = mm->context.hugetlb_pte_count;
	saved_thp_pte_count = mm->context.thp_pte_count;
	mm->context.hugetlb_pte_count = 0;
	mm->context.thp_pte_count = 0;

	mm_rss -= saved_thp_pte_count * (HPAGE_SIZE / PAGE_SIZE);
#पूर्ण_अगर

	/* copy_mm() copies over the parent's mm_काष्ठा beक्रमe calling
	 * us, so we need to zero out the TSB poपूर्णांकer or अन्यथा tsb_grow()
	 * will be confused and think there is an older TSB to मुक्त up.
	 */
	क्रम (i = 0; i < MM_NUM_TSBS; i++)
		mm->context.tsb_block[i].tsb = शून्य;

	/* If this is विभाजन, inherit the parent's TSB size.  We would
	 * grow it to that size on the first page fault anyways.
	 */
	tsb_grow(mm, MM_TSB_BASE, mm_rss);

#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
	अगर (unlikely(saved_hugetlb_pte_count + saved_thp_pte_count))
		tsb_grow(mm, MM_TSB_HUGE,
			 (saved_hugetlb_pte_count + saved_thp_pte_count) *
			 REAL_HPAGE_PER_HPAGE);
#पूर्ण_अगर

	अगर (unlikely(!mm->context.tsb_block[MM_TSB_BASE].tsb))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम tsb_destroy_one(काष्ठा tsb_config *tp)
अणु
	अचिन्हित दीर्घ cache_index;

	अगर (!tp->tsb)
		वापस;
	cache_index = tp->tsb_reg_val & 0x7UL;
	kmem_cache_मुक्त(tsb_caches[cache_index], tp->tsb);
	tp->tsb = शून्य;
	tp->tsb_reg_val = 0UL;
पूर्ण

व्योम destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ flags, i;

	क्रम (i = 0; i < MM_NUM_TSBS; i++)
		tsb_destroy_one(&mm->context.tsb_block[i]);

	spin_lock_irqsave(&ctx_alloc_lock, flags);

	अगर (CTX_VALID(mm->context)) अणु
		अचिन्हित दीर्घ nr = CTX_NRBITS(mm->context);
		mmu_context_bmap[nr>>6] &= ~(1UL << (nr & 63));
	पूर्ण

	spin_unlock_irqrestore(&ctx_alloc_lock, flags);

	/* If ADI tag storage was allocated क्रम this task, मुक्त it */
	अगर (mm->context.tag_store) अणु
		tag_storage_desc_t *tag_desc;
		अचिन्हित दीर्घ max_desc;
		अचिन्हित अक्षर *tags;

		tag_desc = mm->context.tag_store;
		max_desc = PAGE_SIZE/माप(tag_storage_desc_t);
		क्रम (i = 0; i < max_desc; i++) अणु
			tags = tag_desc->tags;
			tag_desc->tags = शून्य;
			kमुक्त(tags);
			tag_desc++;
		पूर्ण
		kमुक्त(mm->context.tag_store);
		mm->context.tag_store = शून्य;
	पूर्ण
पूर्ण
