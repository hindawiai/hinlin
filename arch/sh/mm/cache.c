<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/sh/mm/cache.c
 *
 * Copyright (C) 1999, 2000, 2002  Niibe Yutaka
 * Copyright (C) 2002 - 2010  Paul Mundt
 */
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/fs.h>
#समावेश <linux/smp.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/module.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cacheflush.h>

व्योम (*local_flush_cache_all)(व्योम *args) = cache_noop;
व्योम (*local_flush_cache_mm)(व्योम *args) = cache_noop;
व्योम (*local_flush_cache_dup_mm)(व्योम *args) = cache_noop;
व्योम (*local_flush_cache_page)(व्योम *args) = cache_noop;
व्योम (*local_flush_cache_range)(व्योम *args) = cache_noop;
व्योम (*local_flush_dcache_page)(व्योम *args) = cache_noop;
व्योम (*local_flush_icache_range)(व्योम *args) = cache_noop;
व्योम (*local_flush_icache_page)(व्योम *args) = cache_noop;
व्योम (*local_flush_cache_sigtramp)(व्योम *args) = cache_noop;

व्योम (*__flush_wback_region)(व्योम *start, पूर्णांक size);
EXPORT_SYMBOL(__flush_wback_region);
व्योम (*__flush_purge_region)(व्योम *start, पूर्णांक size);
EXPORT_SYMBOL(__flush_purge_region);
व्योम (*__flush_invalidate_region)(व्योम *start, पूर्णांक size);
EXPORT_SYMBOL(__flush_invalidate_region);

अटल अंतरभूत व्योम noop__flush_region(व्योम *start, पूर्णांक size)
अणु
पूर्ण

अटल अंतरभूत व्योम cacheop_on_each_cpu(व्योम (*func) (व्योम *info), व्योम *info,
                                   पूर्णांक रुको)
अणु
	preempt_disable();

	/* Needing IPI क्रम cross-core flush is SHX3-specअगरic. */
#अगर_घोषित CONFIG_CPU_SHX3
	/*
	 * It's possible that this माला_लो called early on when IRQs are
	 * still disabled due to ioremapping by the boot CPU, so करोn't
	 * even attempt IPIs unless there are other CPUs online.
	 */
	अगर (num_online_cpus() > 1)
		smp_call_function(func, info, रुको);
#पूर्ण_अगर

	func(info);

	preempt_enable();
पूर्ण

व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
		       अचिन्हित दीर्घ vaddr, व्योम *dst, स्थिर व्योम *src,
		       अचिन्हित दीर्घ len)
अणु
	अगर (boot_cpu_data.dcache.n_aliases && page_mapcount(page) &&
	    test_bit(PG_dcache_clean, &page->flags)) अणु
		व्योम *vto = kmap_coherent(page, vaddr) + (vaddr & ~PAGE_MASK);
		स_नकल(vto, src, len);
		kunmap_coherent(vto);
	पूर्ण अन्यथा अणु
		स_नकल(dst, src, len);
		अगर (boot_cpu_data.dcache.n_aliases)
			clear_bit(PG_dcache_clean, &page->flags);
	पूर्ण

	अगर (vma->vm_flags & VM_EXEC)
		flush_cache_page(vma, vaddr, page_to_pfn(page));
पूर्ण

व्योम copy_from_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
			 अचिन्हित दीर्घ vaddr, व्योम *dst, स्थिर व्योम *src,
			 अचिन्हित दीर्घ len)
अणु
	अगर (boot_cpu_data.dcache.n_aliases && page_mapcount(page) &&
	    test_bit(PG_dcache_clean, &page->flags)) अणु
		व्योम *vfrom = kmap_coherent(page, vaddr) + (vaddr & ~PAGE_MASK);
		स_नकल(dst, vfrom, len);
		kunmap_coherent(vfrom);
	पूर्ण अन्यथा अणु
		स_नकल(dst, src, len);
		अगर (boot_cpu_data.dcache.n_aliases)
			clear_bit(PG_dcache_clean, &page->flags);
	पूर्ण
पूर्ण

व्योम copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
			अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	व्योम *vfrom, *vto;

	vto = kmap_atomic(to);

	अगर (boot_cpu_data.dcache.n_aliases && page_mapcount(from) &&
	    test_bit(PG_dcache_clean, &from->flags)) अणु
		vfrom = kmap_coherent(from, vaddr);
		copy_page(vto, vfrom);
		kunmap_coherent(vfrom);
	पूर्ण अन्यथा अणु
		vfrom = kmap_atomic(from);
		copy_page(vto, vfrom);
		kunmap_atomic(vfrom);
	पूर्ण

	अगर (pages_करो_alias((अचिन्हित दीर्घ)vto, vaddr & PAGE_MASK) ||
	    (vma->vm_flags & VM_EXEC))
		__flush_purge_region(vto, PAGE_SIZE);

	kunmap_atomic(vto);
	/* Make sure this page is cleared on other CPU's too beक्रमe using it */
	smp_wmb();
पूर्ण
EXPORT_SYMBOL(copy_user_highpage);

व्योम clear_user_highpage(काष्ठा page *page, अचिन्हित दीर्घ vaddr)
अणु
	व्योम *kaddr = kmap_atomic(page);

	clear_page(kaddr);

	अगर (pages_करो_alias((अचिन्हित दीर्घ)kaddr, vaddr & PAGE_MASK))
		__flush_purge_region(kaddr, PAGE_SIZE);

	kunmap_atomic(kaddr);
पूर्ण
EXPORT_SYMBOL(clear_user_highpage);

व्योम __update_cache(काष्ठा vm_area_काष्ठा *vma,
		    अचिन्हित दीर्घ address, pte_t pte)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ pfn = pte_pfn(pte);

	अगर (!boot_cpu_data.dcache.n_aliases)
		वापस;

	page = pfn_to_page(pfn);
	अगर (pfn_valid(pfn)) अणु
		पूर्णांक dirty = !test_and_set_bit(PG_dcache_clean, &page->flags);
		अगर (dirty)
			__flush_purge_region(page_address(page), PAGE_SIZE);
	पूर्ण
पूर्ण

व्योम __flush_anon_page(काष्ठा page *page, अचिन्हित दीर्घ vmaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) page_address(page);

	अगर (pages_करो_alias(addr, vmaddr)) अणु
		अगर (boot_cpu_data.dcache.n_aliases && page_mapcount(page) &&
		    test_bit(PG_dcache_clean, &page->flags)) अणु
			व्योम *kaddr;

			kaddr = kmap_coherent(page, vmaddr);
			/* XXX.. For now kunmap_coherent() करोes a purge */
			/* __flush_purge_region((व्योम *)kaddr, PAGE_SIZE); */
			kunmap_coherent(kaddr);
		पूर्ण अन्यथा
			__flush_purge_region((व्योम *)addr, PAGE_SIZE);
	पूर्ण
पूर्ण

व्योम flush_cache_all(व्योम)
अणु
	cacheop_on_each_cpu(local_flush_cache_all, शून्य, 1);
पूर्ण
EXPORT_SYMBOL(flush_cache_all);

व्योम flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (boot_cpu_data.dcache.n_aliases == 0)
		वापस;

	cacheop_on_each_cpu(local_flush_cache_mm, mm, 1);
पूर्ण

व्योम flush_cache_dup_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (boot_cpu_data.dcache.n_aliases == 0)
		वापस;

	cacheop_on_each_cpu(local_flush_cache_dup_mm, mm, 1);
पूर्ण

व्योम flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		      अचिन्हित दीर्घ pfn)
अणु
	काष्ठा flusher_data data;

	data.vma = vma;
	data.addr1 = addr;
	data.addr2 = pfn;

	cacheop_on_each_cpu(local_flush_cache_page, (व्योम *)&data, 1);
पूर्ण

व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		       अचिन्हित दीर्घ end)
अणु
	काष्ठा flusher_data data;

	data.vma = vma;
	data.addr1 = start;
	data.addr2 = end;

	cacheop_on_each_cpu(local_flush_cache_range, (व्योम *)&data, 1);
पूर्ण
EXPORT_SYMBOL(flush_cache_range);

व्योम flush_dcache_page(काष्ठा page *page)
अणु
	cacheop_on_each_cpu(local_flush_dcache_page, page, 1);
पूर्ण
EXPORT_SYMBOL(flush_dcache_page);

व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा flusher_data data;

	data.vma = शून्य;
	data.addr1 = start;
	data.addr2 = end;

	cacheop_on_each_cpu(local_flush_icache_range, (व्योम *)&data, 1);
पूर्ण
EXPORT_SYMBOL(flush_icache_range);

व्योम flush_icache_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page)
अणु
	/* Nothing uses the VMA, so just pass the काष्ठा page aदीर्घ */
	cacheop_on_each_cpu(local_flush_icache_page, page, 1);
पूर्ण

व्योम flush_cache_sigtramp(अचिन्हित दीर्घ address)
अणु
	cacheop_on_each_cpu(local_flush_cache_sigtramp, (व्योम *)address, 1);
पूर्ण

अटल व्योम compute_alias(काष्ठा cache_info *c)
अणु
#अगर_घोषित CONFIG_MMU
	c->alias_mask = ((c->sets - 1) << c->entry_shअगरt) & ~(PAGE_SIZE - 1);
#अन्यथा
	c->alias_mask = 0;
#पूर्ण_अगर
	c->n_aliases = c->alias_mask ? (c->alias_mask >> PAGE_SHIFT) + 1 : 0;
पूर्ण

अटल व्योम __init emit_cache_params(व्योम)
अणु
	prपूर्णांकk(KERN_NOTICE "I-cache : n_ways=%d n_sets=%d way_incr=%d\n",
		boot_cpu_data.icache.ways,
		boot_cpu_data.icache.sets,
		boot_cpu_data.icache.way_incr);
	prपूर्णांकk(KERN_NOTICE "I-cache : entry_mask=0x%08x alias_mask=0x%08x n_aliases=%d\n",
		boot_cpu_data.icache.entry_mask,
		boot_cpu_data.icache.alias_mask,
		boot_cpu_data.icache.n_aliases);
	prपूर्णांकk(KERN_NOTICE "D-cache : n_ways=%d n_sets=%d way_incr=%d\n",
		boot_cpu_data.dcache.ways,
		boot_cpu_data.dcache.sets,
		boot_cpu_data.dcache.way_incr);
	prपूर्णांकk(KERN_NOTICE "D-cache : entry_mask=0x%08x alias_mask=0x%08x n_aliases=%d\n",
		boot_cpu_data.dcache.entry_mask,
		boot_cpu_data.dcache.alias_mask,
		boot_cpu_data.dcache.n_aliases);

	/*
	 * Emit Secondary Cache parameters अगर the CPU has a probed L2.
	 */
	अगर (boot_cpu_data.flags & CPU_HAS_L2_CACHE) अणु
		prपूर्णांकk(KERN_NOTICE "S-cache : n_ways=%d n_sets=%d way_incr=%d\n",
			boot_cpu_data.scache.ways,
			boot_cpu_data.scache.sets,
			boot_cpu_data.scache.way_incr);
		prपूर्णांकk(KERN_NOTICE "S-cache : entry_mask=0x%08x alias_mask=0x%08x n_aliases=%d\n",
			boot_cpu_data.scache.entry_mask,
			boot_cpu_data.scache.alias_mask,
			boot_cpu_data.scache.n_aliases);
	पूर्ण
पूर्ण

व्योम __init cpu_cache_init(व्योम)
अणु
	अचिन्हित पूर्णांक cache_disabled = 0;

#अगर_घोषित SH_CCR
	cache_disabled = !(__raw_पढ़ोl(SH_CCR) & CCR_CACHE_ENABLE);
#पूर्ण_अगर

	compute_alias(&boot_cpu_data.icache);
	compute_alias(&boot_cpu_data.dcache);
	compute_alias(&boot_cpu_data.scache);

	__flush_wback_region		= noop__flush_region;
	__flush_purge_region		= noop__flush_region;
	__flush_invalidate_region	= noop__flush_region;

	/*
	 * No flushing is necessary in the disabled cache हाल so we can
	 * just keep the noop functions in local_flush_..() and __flush_..()
	 */
	अगर (unlikely(cache_disabled))
		जाओ skip;

	अगर (boot_cpu_data.type == CPU_J2) अणु
		बाह्य व्योम __weak j2_cache_init(व्योम);

		j2_cache_init();
	पूर्ण अन्यथा अगर (boot_cpu_data.family == CPU_FAMILY_SH2) अणु
		बाह्य व्योम __weak sh2_cache_init(व्योम);

		sh2_cache_init();
	पूर्ण

	अगर (boot_cpu_data.family == CPU_FAMILY_SH2A) अणु
		बाह्य व्योम __weak sh2a_cache_init(व्योम);

		sh2a_cache_init();
	पूर्ण

	अगर (boot_cpu_data.family == CPU_FAMILY_SH3) अणु
		बाह्य व्योम __weak sh3_cache_init(व्योम);

		sh3_cache_init();

		अगर ((boot_cpu_data.type == CPU_SH7705) &&
		    (boot_cpu_data.dcache.sets == 512)) अणु
			बाह्य व्योम __weak sh7705_cache_init(व्योम);

			sh7705_cache_init();
		पूर्ण
	पूर्ण

	अगर ((boot_cpu_data.family == CPU_FAMILY_SH4) ||
	    (boot_cpu_data.family == CPU_FAMILY_SH4A) ||
	    (boot_cpu_data.family == CPU_FAMILY_SH4AL_DSP)) अणु
		बाह्य व्योम __weak sh4_cache_init(व्योम);

		sh4_cache_init();

		अगर ((boot_cpu_data.type == CPU_SH7786) ||
		    (boot_cpu_data.type == CPU_SHX3)) अणु
			बाह्य व्योम __weak shx3_cache_init(व्योम);

			shx3_cache_init();
		पूर्ण
	पूर्ण

skip:
	emit_cache_params();
पूर्ण
