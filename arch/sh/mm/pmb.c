<शैली गुरु>
/*
 * arch/sh/mm/pmb.c
 *
 * Privileged Space Mapping Buffer (PMB) Support.
 *
 * Copyright (C) 2005 - 2011  Paul Mundt
 * Copyright (C) 2010  Matt Fleming
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/cpu.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/sizes.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/mmu_context.h>

काष्ठा pmb_entry;

काष्ठा pmb_entry अणु
	अचिन्हित दीर्घ vpn;
	अचिन्हित दीर्घ ppn;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ size;

	raw_spinlock_t lock;

	/*
	 * 0 .. NR_PMB_ENTRIES क्रम specअगरic entry selection, or
	 * PMB_NO_ENTRY to search क्रम a मुक्त one
	 */
	पूर्णांक entry;

	/* Adjacent entry link क्रम contiguous multi-entry mappings */
	काष्ठा pmb_entry *link;
पूर्ण;

अटल काष्ठा अणु
	अचिन्हित दीर्घ size;
	पूर्णांक flag;
पूर्ण pmb_sizes[] = अणु
	अणु .size	= SZ_512M, .flag = PMB_SZ_512M, पूर्ण,
	अणु .size = SZ_128M, .flag = PMB_SZ_128M, पूर्ण,
	अणु .size = SZ_64M,  .flag = PMB_SZ_64M,  पूर्ण,
	अणु .size = SZ_16M,  .flag = PMB_SZ_16M,  पूर्ण,
पूर्ण;

अटल व्योम pmb_unmap_entry(काष्ठा pmb_entry *, पूर्णांक depth);

अटल DEFINE_RWLOCK(pmb_rwlock);
अटल काष्ठा pmb_entry pmb_entry_list[NR_PMB_ENTRIES];
अटल DECLARE_BITMAP(pmb_map, NR_PMB_ENTRIES);

अटल अचिन्हित पूर्णांक pmb_iomapping_enabled;

अटल __always_अंतरभूत अचिन्हित दीर्घ mk_pmb_entry(अचिन्हित पूर्णांक entry)
अणु
	वापस (entry & PMB_E_MASK) << PMB_E_SHIFT;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ mk_pmb_addr(अचिन्हित पूर्णांक entry)
अणु
	वापस mk_pmb_entry(entry) | PMB_ADDR;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ mk_pmb_data(अचिन्हित पूर्णांक entry)
अणु
	वापस mk_pmb_entry(entry) | PMB_DATA;
पूर्ण

अटल __always_अंतरभूत अचिन्हित पूर्णांक pmb_ppn_in_range(अचिन्हित दीर्घ ppn)
अणु
	वापस ppn >= __pa(memory_start) && ppn < __pa(memory_end);
पूर्ण

/*
 * Ensure that the PMB entries match our cache configuration.
 *
 * When we are in 32-bit address extended mode, CCR.CB becomes
 * invalid, so care must be taken to manually adjust cacheable
 * translations.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ pmb_cache_flags(व्योम)
अणु
	अचिन्हित दीर्घ flags = 0;

#अगर defined(CONFIG_CACHE_OFF)
	flags |= PMB_WT | PMB_UB;
#या_अगर defined(CONFIG_CACHE_WRITETHROUGH)
	flags |= PMB_C | PMB_WT | PMB_UB;
#या_अगर defined(CONFIG_CACHE_WRITEBACK)
	flags |= PMB_C;
#पूर्ण_अगर

	वापस flags;
पूर्ण

/*
 * Convert typical pgprot value to the PMB equivalent
 */
अटल अंतरभूत अचिन्हित दीर्घ pgprot_to_pmb_flags(pgprot_t prot)
अणु
	अचिन्हित दीर्घ pmb_flags = 0;
	u64 flags = pgprot_val(prot);

	अगर (flags & _PAGE_CACHABLE)
		pmb_flags |= PMB_C;
	अगर (flags & _PAGE_WT)
		pmb_flags |= PMB_WT | PMB_UB;

	वापस pmb_flags;
पूर्ण

अटल अंतरभूत bool pmb_can_merge(काष्ठा pmb_entry *a, काष्ठा pmb_entry *b)
अणु
	वापस (b->vpn == (a->vpn + a->size)) &&
	       (b->ppn == (a->ppn + a->size)) &&
	       (b->flags == a->flags);
पूर्ण

अटल bool pmb_mapping_exists(अचिन्हित दीर्घ vaddr, phys_addr_t phys,
			       अचिन्हित दीर्घ size)
अणु
	पूर्णांक i;

	पढ़ो_lock(&pmb_rwlock);

	क्रम (i = 0; i < ARRAY_SIZE(pmb_entry_list); i++) अणु
		काष्ठा pmb_entry *pmbe, *iter;
		अचिन्हित दीर्घ span;

		अगर (!test_bit(i, pmb_map))
			जारी;

		pmbe = &pmb_entry_list[i];

		/*
		 * See अगर VPN and PPN are bounded by an existing mapping.
		 */
		अगर ((vaddr < pmbe->vpn) || (vaddr >= (pmbe->vpn + pmbe->size)))
			जारी;
		अगर ((phys < pmbe->ppn) || (phys >= (pmbe->ppn + pmbe->size)))
			जारी;

		/*
		 * Now see अगर we're in range of a simple mapping.
		 */
		अगर (size <= pmbe->size) अणु
			पढ़ो_unlock(&pmb_rwlock);
			वापस true;
		पूर्ण

		span = pmbe->size;

		/*
		 * Finally क्रम sizes that involve compound mappings, walk
		 * the chain.
		 */
		क्रम (iter = pmbe->link; iter; iter = iter->link)
			span += iter->size;

		/*
		 * Nothing अन्यथा to करो अगर the range requirements are met.
		 */
		अगर (size <= span) अणु
			पढ़ो_unlock(&pmb_rwlock);
			वापस true;
		पूर्ण
	पूर्ण

	पढ़ो_unlock(&pmb_rwlock);
	वापस false;
पूर्ण

अटल bool pmb_size_valid(अचिन्हित दीर्घ size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pmb_sizes); i++)
		अगर (pmb_sizes[i].size == size)
			वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool pmb_addr_valid(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	वापस (addr >= P1SEG && (addr + size - 1) < P3SEG);
पूर्ण

अटल अंतरभूत bool pmb_prot_valid(pgprot_t prot)
अणु
	वापस (pgprot_val(prot) & _PAGE_USER) == 0;
पूर्ण

अटल पूर्णांक pmb_माप_प्रकारo_flags(अचिन्हित दीर्घ size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pmb_sizes); i++)
		अगर (pmb_sizes[i].size == size)
			वापस pmb_sizes[i].flag;

	वापस 0;
पूर्ण

अटल पूर्णांक pmb_alloc_entry(व्योम)
अणु
	पूर्णांक pos;

	pos = find_first_zero_bit(pmb_map, NR_PMB_ENTRIES);
	अगर (pos >= 0 && pos < NR_PMB_ENTRIES)
		__set_bit(pos, pmb_map);
	अन्यथा
		pos = -ENOSPC;

	वापस pos;
पूर्ण

अटल काष्ठा pmb_entry *pmb_alloc(अचिन्हित दीर्घ vpn, अचिन्हित दीर्घ ppn,
				   अचिन्हित दीर्घ flags, पूर्णांक entry)
अणु
	काष्ठा pmb_entry *pmbe;
	अचिन्हित दीर्घ irqflags;
	व्योम *ret = शून्य;
	पूर्णांक pos;

	ग_लिखो_lock_irqsave(&pmb_rwlock, irqflags);

	अगर (entry == PMB_NO_ENTRY) अणु
		pos = pmb_alloc_entry();
		अगर (unlikely(pos < 0)) अणु
			ret = ERR_PTR(pos);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (__test_and_set_bit(entry, pmb_map)) अणु
			ret = ERR_PTR(-ENOSPC);
			जाओ out;
		पूर्ण

		pos = entry;
	पूर्ण

	ग_लिखो_unlock_irqrestore(&pmb_rwlock, irqflags);

	pmbe = &pmb_entry_list[pos];

	स_रखो(pmbe, 0, माप(काष्ठा pmb_entry));

	raw_spin_lock_init(&pmbe->lock);

	pmbe->vpn	= vpn;
	pmbe->ppn	= ppn;
	pmbe->flags	= flags;
	pmbe->entry	= pos;

	वापस pmbe;

out:
	ग_लिखो_unlock_irqrestore(&pmb_rwlock, irqflags);
	वापस ret;
पूर्ण

अटल व्योम pmb_मुक्त(काष्ठा pmb_entry *pmbe)
अणु
	__clear_bit(pmbe->entry, pmb_map);

	pmbe->entry	= PMB_NO_ENTRY;
	pmbe->link	= शून्य;
पूर्ण

/*
 * Must be run uncached.
 */
अटल व्योम __set_pmb_entry(काष्ठा pmb_entry *pmbe)
अणु
	अचिन्हित दीर्घ addr, data;

	addr = mk_pmb_addr(pmbe->entry);
	data = mk_pmb_data(pmbe->entry);

	jump_to_uncached();

	/* Set V-bit */
	__raw_ग_लिखोl(pmbe->vpn | PMB_V, addr);
	__raw_ग_लिखोl(pmbe->ppn | pmbe->flags | PMB_V, data);

	back_to_cached();
पूर्ण

अटल व्योम __clear_pmb_entry(काष्ठा pmb_entry *pmbe)
अणु
	अचिन्हित दीर्घ addr, data;
	अचिन्हित दीर्घ addr_val, data_val;

	addr = mk_pmb_addr(pmbe->entry);
	data = mk_pmb_data(pmbe->entry);

	addr_val = __raw_पढ़ोl(addr);
	data_val = __raw_पढ़ोl(data);

	/* Clear V-bit */
	ग_लिखोl_uncached(addr_val & ~PMB_V, addr);
	ग_लिखोl_uncached(data_val & ~PMB_V, data);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम set_pmb_entry(काष्ठा pmb_entry *pmbe)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pmbe->lock, flags);
	__set_pmb_entry(pmbe);
	raw_spin_unlock_irqrestore(&pmbe->lock, flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

पूर्णांक pmb_bolt_mapping(अचिन्हित दीर्घ vaddr, phys_addr_t phys,
		     अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	काष्ठा pmb_entry *pmbp, *pmbe;
	अचिन्हित दीर्घ orig_addr, orig_size;
	अचिन्हित दीर्घ flags, pmb_flags;
	पूर्णांक i, mapped;

	अगर (size < SZ_16M)
		वापस -EINVAL;
	अगर (!pmb_addr_valid(vaddr, size))
		वापस -EFAULT;
	अगर (pmb_mapping_exists(vaddr, phys, size))
		वापस 0;

	orig_addr = vaddr;
	orig_size = size;

	flush_tlb_kernel_range(vaddr, vaddr + size);

	pmb_flags = pgprot_to_pmb_flags(prot);
	pmbp = शून्य;

	करो अणु
		क्रम (i = mapped = 0; i < ARRAY_SIZE(pmb_sizes); i++) अणु
			अगर (size < pmb_sizes[i].size)
				जारी;

			pmbe = pmb_alloc(vaddr, phys, pmb_flags |
					 pmb_sizes[i].flag, PMB_NO_ENTRY);
			अगर (IS_ERR(pmbe)) अणु
				pmb_unmap_entry(pmbp, mapped);
				वापस PTR_ERR(pmbe);
			पूर्ण

			raw_spin_lock_irqsave(&pmbe->lock, flags);

			pmbe->size = pmb_sizes[i].size;

			__set_pmb_entry(pmbe);

			phys	+= pmbe->size;
			vaddr	+= pmbe->size;
			size	-= pmbe->size;

			/*
			 * Link adjacent entries that span multiple PMB
			 * entries क्रम easier tear-करोwn.
			 */
			अगर (likely(pmbp)) अणु
				raw_spin_lock_nested(&pmbp->lock,
						     SINGLE_DEPTH_NESTING);
				pmbp->link = pmbe;
				raw_spin_unlock(&pmbp->lock);
			पूर्ण

			pmbp = pmbe;

			/*
			 * Instead of trying smaller sizes on every
			 * iteration (even अगर we succeed in allocating
			 * space), try using pmb_sizes[i].size again.
			 */
			i--;
			mapped++;

			raw_spin_unlock_irqrestore(&pmbe->lock, flags);
		पूर्ण
	पूर्ण जबतक (size >= SZ_16M);

	flush_cache_vmap(orig_addr, orig_addr + orig_size);

	वापस 0;
पूर्ण

व्योम __iomem *pmb_remap_caller(phys_addr_t phys, अचिन्हित दीर्घ size,
			       pgprot_t prot, व्योम *caller)
अणु
	अचिन्हित दीर्घ vaddr;
	phys_addr_t offset, last_addr;
	phys_addr_t align_mask;
	अचिन्हित दीर्घ aligned;
	काष्ठा vm_काष्ठा *area;
	पूर्णांक i, ret;

	अगर (!pmb_iomapping_enabled)
		वापस शून्य;

	/*
	 * Small mappings need to go through the TLB.
	 */
	अगर (size < SZ_16M)
		वापस ERR_PTR(-EINVAL);
	अगर (!pmb_prot_valid(prot))
		वापस ERR_PTR(-EINVAL);

	क्रम (i = 0; i < ARRAY_SIZE(pmb_sizes); i++)
		अगर (size >= pmb_sizes[i].size)
			अवरोध;

	last_addr = phys + size;
	align_mask = ~(pmb_sizes[i].size - 1);
	offset = phys & ~align_mask;
	phys &= align_mask;
	aligned = ALIGN(last_addr, pmb_sizes[i].size) - phys;

	/*
	 * XXX: This should really start from uncached_end, but this
	 * causes the MMU to reset, so क्रम now we restrict it to the
	 * 0xb000...0xc000 range.
	 */
	area = __get_vm_area_caller(aligned, VM_IOREMAP, 0xb0000000,
				    P3SEG, caller);
	अगर (!area)
		वापस शून्य;

	area->phys_addr = phys;
	vaddr = (अचिन्हित दीर्घ)area->addr;

	ret = pmb_bolt_mapping(vaddr, phys, size, prot);
	अगर (unlikely(ret != 0))
		वापस ERR_PTR(ret);

	वापस (व्योम __iomem *)(offset + (अक्षर *)vaddr);
पूर्ण

पूर्णांक pmb_unmap(व्योम __iomem *addr)
अणु
	काष्ठा pmb_entry *pmbe = शून्य;
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ __क्रमce)addr;
	पूर्णांक i, found = 0;

	पढ़ो_lock(&pmb_rwlock);

	क्रम (i = 0; i < ARRAY_SIZE(pmb_entry_list); i++) अणु
		अगर (test_bit(i, pmb_map)) अणु
			pmbe = &pmb_entry_list[i];
			अगर (pmbe->vpn == vaddr) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	पढ़ो_unlock(&pmb_rwlock);

	अगर (found) अणु
		pmb_unmap_entry(pmbe, NR_PMB_ENTRIES);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम __pmb_unmap_entry(काष्ठा pmb_entry *pmbe, पूर्णांक depth)
अणु
	करो अणु
		काष्ठा pmb_entry *pmblink = pmbe;

		/*
		 * We may be called beक्रमe this pmb_entry has been
		 * entered पूर्णांकo the PMB table via set_pmb_entry(), but
		 * that's OK because we've allocated a unique slot क्रम
		 * this entry in pmb_alloc() (even अगर we haven't filled
		 * it yet).
		 *
		 * Thereक्रमe, calling __clear_pmb_entry() is safe as no
		 * other mapping can be using that slot.
		 */
		__clear_pmb_entry(pmbe);

		flush_cache_vunmap(pmbe->vpn, pmbe->vpn + pmbe->size);

		pmbe = pmblink->link;

		pmb_मुक्त(pmblink);
	पूर्ण जबतक (pmbe && --depth);
पूर्ण

अटल व्योम pmb_unmap_entry(काष्ठा pmb_entry *pmbe, पूर्णांक depth)
अणु
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!pmbe))
		वापस;

	ग_लिखो_lock_irqsave(&pmb_rwlock, flags);
	__pmb_unmap_entry(pmbe, depth);
	ग_लिखो_unlock_irqrestore(&pmb_rwlock, flags);
पूर्ण

अटल व्योम __init pmb_notअगरy(व्योम)
अणु
	पूर्णांक i;

	pr_info("PMB: boot mappings:\n");

	पढ़ो_lock(&pmb_rwlock);

	क्रम (i = 0; i < ARRAY_SIZE(pmb_entry_list); i++) अणु
		काष्ठा pmb_entry *pmbe;

		अगर (!test_bit(i, pmb_map))
			जारी;

		pmbe = &pmb_entry_list[i];

		pr_info("       0x%08lx -> 0x%08lx [ %4ldMB %2scached ]\n",
			pmbe->vpn >> PAGE_SHIFT, pmbe->ppn >> PAGE_SHIFT,
			pmbe->size >> 20, (pmbe->flags & PMB_C) ? "" : "un");
	पूर्ण

	पढ़ो_unlock(&pmb_rwlock);
पूर्ण

/*
 * Sync our software copy of the PMB mappings with those in hardware. The
 * mappings in the hardware PMB were either set up by the bootloader or
 * very early on by the kernel.
 */
अटल व्योम __init pmb_synchronize(व्योम)
अणु
	काष्ठा pmb_entry *pmbp = शून्य;
	पूर्णांक i, j;

	/*
	 * Run through the initial boot mappings, log the established
	 * ones, and blow away anything that falls outside of the valid
	 * PPN range. Specअगरically, we only care about existing mappings
	 * that impact the cached/uncached sections.
	 *
	 * Note that touching these can be a bit of a minefield; the boot
	 * loader can establish multi-page mappings with the same caching
	 * attributes, so we need to ensure that we aren't modअगरying a
	 * mapping that we're presently executing from, or may execute
	 * from in the हाल of straddling page boundaries.
	 *
	 * In the future we will have to tidy up after the boot loader by
	 * jumping between the cached and uncached mappings and tearing
	 * करोwn alternating mappings जबतक executing from the other.
	 */
	क्रम (i = 0; i < NR_PMB_ENTRIES; i++) अणु
		अचिन्हित दीर्घ addr, data;
		अचिन्हित दीर्घ addr_val, data_val;
		अचिन्हित दीर्घ ppn, vpn, flags;
		अचिन्हित दीर्घ irqflags;
		अचिन्हित पूर्णांक size;
		काष्ठा pmb_entry *pmbe;

		addr = mk_pmb_addr(i);
		data = mk_pmb_data(i);

		addr_val = __raw_पढ़ोl(addr);
		data_val = __raw_पढ़ोl(data);

		/*
		 * Skip over any bogus entries
		 */
		अगर (!(data_val & PMB_V) || !(addr_val & PMB_V))
			जारी;

		ppn = data_val & PMB_PFN_MASK;
		vpn = addr_val & PMB_PFN_MASK;

		/*
		 * Only preserve in-range mappings.
		 */
		अगर (!pmb_ppn_in_range(ppn)) अणु
			/*
			 * Invalidate anything out of bounds.
			 */
			ग_लिखोl_uncached(addr_val & ~PMB_V, addr);
			ग_लिखोl_uncached(data_val & ~PMB_V, data);
			जारी;
		पूर्ण

		/*
		 * Update the caching attributes अगर necessary
		 */
		अगर (data_val & PMB_C) अणु
			data_val &= ~PMB_CACHE_MASK;
			data_val |= pmb_cache_flags();

			ग_लिखोl_uncached(data_val, data);
		पूर्ण

		size = data_val & PMB_SZ_MASK;
		flags = size | (data_val & PMB_CACHE_MASK);

		pmbe = pmb_alloc(vpn, ppn, flags, i);
		अगर (IS_ERR(pmbe)) अणु
			WARN_ON_ONCE(1);
			जारी;
		पूर्ण

		raw_spin_lock_irqsave(&pmbe->lock, irqflags);

		क्रम (j = 0; j < ARRAY_SIZE(pmb_sizes); j++)
			अगर (pmb_sizes[j].flag == size)
				pmbe->size = pmb_sizes[j].size;

		अगर (pmbp) अणु
			raw_spin_lock_nested(&pmbp->lock, SINGLE_DEPTH_NESTING);
			/*
			 * Compare the previous entry against the current one to
			 * see अगर the entries span a contiguous mapping. If so,
			 * setup the entry links accordingly. Compound mappings
			 * are later coalesced.
			 */
			अगर (pmb_can_merge(pmbp, pmbe))
				pmbp->link = pmbe;
			raw_spin_unlock(&pmbp->lock);
		पूर्ण

		pmbp = pmbe;

		raw_spin_unlock_irqrestore(&pmbe->lock, irqflags);
	पूर्ण
पूर्ण

अटल व्योम __init pmb_merge(काष्ठा pmb_entry *head)
अणु
	अचिन्हित दीर्घ span, newsize;
	काष्ठा pmb_entry *tail;
	पूर्णांक i = 1, depth = 0;

	span = newsize = head->size;

	tail = head->link;
	जबतक (tail) अणु
		span += tail->size;

		अगर (pmb_size_valid(span)) अणु
			newsize = span;
			depth = i;
		पूर्ण

		/* This is the end of the line.. */
		अगर (!tail->link)
			अवरोध;

		tail = tail->link;
		i++;
	पूर्ण

	/*
	 * The merged page size must be valid.
	 */
	अगर (!depth || !pmb_size_valid(newsize))
		वापस;

	head->flags &= ~PMB_SZ_MASK;
	head->flags |= pmb_माप_प्रकारo_flags(newsize);

	head->size = newsize;

	__pmb_unmap_entry(head->link, depth);
	__set_pmb_entry(head);
पूर्ण

अटल व्योम __init pmb_coalesce(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	ग_लिखो_lock_irqsave(&pmb_rwlock, flags);

	क्रम (i = 0; i < ARRAY_SIZE(pmb_entry_list); i++) अणु
		काष्ठा pmb_entry *pmbe;

		अगर (!test_bit(i, pmb_map))
			जारी;

		pmbe = &pmb_entry_list[i];

		/*
		 * We're only पूर्णांकerested in compound mappings
		 */
		अगर (!pmbe->link)
			जारी;

		/*
		 * Nothing to करो अगर it alपढ़ोy uses the largest possible
		 * page size.
		 */
		अगर (pmbe->size == SZ_512M)
			जारी;

		pmb_merge(pmbe);
	पूर्ण

	ग_लिखो_unlock_irqrestore(&pmb_rwlock, flags);
पूर्ण

#अगर_घोषित CONFIG_UNCACHED_MAPPING
अटल व्योम __init pmb_resize(व्योम)
अणु
	पूर्णांक i;

	/*
	 * If the uncached mapping was स्थिरructed by the kernel, it will
	 * alपढ़ोy be a reasonable size.
	 */
	अगर (uncached_size == SZ_16M)
		वापस;

	पढ़ो_lock(&pmb_rwlock);

	क्रम (i = 0; i < ARRAY_SIZE(pmb_entry_list); i++) अणु
		काष्ठा pmb_entry *pmbe;
		अचिन्हित दीर्घ flags;

		अगर (!test_bit(i, pmb_map))
			जारी;

		pmbe = &pmb_entry_list[i];

		अगर (pmbe->vpn != uncached_start)
			जारी;

		/*
		 * Found it, now resize it.
		 */
		raw_spin_lock_irqsave(&pmbe->lock, flags);

		pmbe->size = SZ_16M;
		pmbe->flags &= ~PMB_SZ_MASK;
		pmbe->flags |= pmb_माप_प्रकारo_flags(pmbe->size);

		uncached_resize(pmbe->size);

		__set_pmb_entry(pmbe);

		raw_spin_unlock_irqrestore(&pmbe->lock, flags);
	पूर्ण

	पढ़ो_unlock(&pmb_rwlock);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init early_pmb(अक्षर *p)
अणु
	अगर (!p)
		वापस 0;

	अगर (म_माला(p, "iomap"))
		pmb_iomapping_enabled = 1;

	वापस 0;
पूर्ण
early_param("pmb", early_pmb);

व्योम __init pmb_init(व्योम)
अणु
	/* Synchronize software state */
	pmb_synchronize();

	/* Attempt to combine compound mappings */
	pmb_coalesce();

#अगर_घोषित CONFIG_UNCACHED_MAPPING
	/* Resize initial mappings, अगर necessary */
	pmb_resize();
#पूर्ण_अगर

	/* Log them */
	pmb_notअगरy();

	ग_लिखोl_uncached(0, PMB_IRMCR);

	/* Flush out the TLB */
	local_flush_tlb_all();
	ctrl_barrier();
पूर्ण

bool __in_29bit_mode(व्योम)
अणु
        वापस (__raw_पढ़ोl(PMB_PASCR) & PASCR_SE) == 0;
पूर्ण

अटल पूर्णांक pmb_debugfs_show(काष्ठा seq_file *file, व्योम *iter)
अणु
	पूर्णांक i;

	seq_म_लिखो(file, "V: Valid, C: Cacheable, WT: Write-Through\n"
			 "CB: Copy-Back, B: Buffered, UB: Unbuffered\n");
	seq_म_लिखो(file, "ety   vpn  ppn  size   flags\n");

	क्रम (i = 0; i < NR_PMB_ENTRIES; i++) अणु
		अचिन्हित दीर्घ addr, data;
		अचिन्हित पूर्णांक size;
		अक्षर *sz_str = शून्य;

		addr = __raw_पढ़ोl(mk_pmb_addr(i));
		data = __raw_पढ़ोl(mk_pmb_data(i));

		size = data & PMB_SZ_MASK;
		sz_str = (size == PMB_SZ_16M)  ? " 16MB":
			 (size == PMB_SZ_64M)  ? " 64MB":
			 (size == PMB_SZ_128M) ? "128MB":
					         "512MB";

		/* 02: V 0x88 0x08 128MB C CB  B */
		seq_म_लिखो(file, "%02d: %c 0x%02lx 0x%02lx %s %c %s %s\n",
			   i, ((addr & PMB_V) && (data & PMB_V)) ? 'V' : ' ',
			   (addr >> 24) & 0xff, (data >> 24) & 0xff,
			   sz_str, (data & PMB_C) ? 'C' : ' ',
			   (data & PMB_WT) ? "WT" : "CB",
			   (data & PMB_UB) ? "UB" : " B");
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(pmb_debugfs);

अटल पूर्णांक __init pmb_debugfs_init(व्योम)
अणु
	debugfs_create_file("pmb", S_IFREG | S_IRUGO, arch_debugfs_dir, शून्य,
			    &pmb_debugfs_fops);
	वापस 0;
पूर्ण
subsys_initcall(pmb_debugfs_init);

#अगर_घोषित CONFIG_PM
अटल व्योम pmb_syscore_resume(व्योम)
अणु
	काष्ठा pmb_entry *pmbe;
	पूर्णांक i;

	पढ़ो_lock(&pmb_rwlock);

	क्रम (i = 0; i < ARRAY_SIZE(pmb_entry_list); i++) अणु
		अगर (test_bit(i, pmb_map)) अणु
			pmbe = &pmb_entry_list[i];
			set_pmb_entry(pmbe);
		पूर्ण
	पूर्ण

	पढ़ो_unlock(&pmb_rwlock);
पूर्ण

अटल काष्ठा syscore_ops pmb_syscore_ops = अणु
	.resume = pmb_syscore_resume,
पूर्ण;

अटल पूर्णांक __init pmb_sysdev_init(व्योम)
अणु
	रेजिस्टर_syscore_ops(&pmb_syscore_ops);
	वापस 0;
पूर्ण
subsys_initcall(pmb_sysdev_init);
#पूर्ण_अगर
