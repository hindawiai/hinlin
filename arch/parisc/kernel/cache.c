<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1999-2006 Helge Deller <deller@gmx.de> (07-13-1999)
 * Copyright (C) 1999 SuSE GmbH Nuernberg
 * Copyright (C) 2000 Philipp Rumpf (prumpf@tux.org)
 *
 * Cache and TLB management
 *
 */
 
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/shmparam.h>

पूर्णांक split_tlb __ro_after_init;
पूर्णांक dcache_stride __ro_after_init;
पूर्णांक icache_stride __ro_after_init;
EXPORT_SYMBOL(dcache_stride);

व्योम flush_dcache_page_यंत्र(अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ vaddr);
EXPORT_SYMBOL(flush_dcache_page_यंत्र);
व्योम purge_dcache_page_यंत्र(अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ vaddr);
व्योम flush_icache_page_यंत्र(अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ vaddr);


/* On some machines (i.e., ones with the Merced bus), there can be
 * only a single PxTLB broadcast at a समय; this must be guaranteed
 * by software. We need a spinlock around all TLB flushes to ensure
 * this.
 */
DEFINE_SPINLOCK(pa_tlb_flush_lock);

/* Swapper page setup lock. */
DEFINE_SPINLOCK(pa_swapper_pg_lock);

#अगर defined(CONFIG_64BIT) && defined(CONFIG_SMP)
पूर्णांक pa_serialize_tlb_flushes __ro_after_init;
#पूर्ण_अगर

काष्ठा pdc_cache_info cache_info __ro_after_init;
#अगर_अघोषित CONFIG_PA20
अटल काष्ठा pdc_btlb_info btlb_info __ro_after_init;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
व्योम
flush_data_cache(व्योम)
अणु
	on_each_cpu(flush_data_cache_local, शून्य, 1);
पूर्ण
व्योम 
flush_inकाष्ठाion_cache(व्योम)
अणु
	on_each_cpu(flush_inकाष्ठाion_cache_local, शून्य, 1);
पूर्ण
#पूर्ण_अगर

व्योम
flush_cache_all_local(व्योम)
अणु
	flush_inकाष्ठाion_cache_local(शून्य);
	flush_data_cache_local(शून्य);
पूर्ण
EXPORT_SYMBOL(flush_cache_all_local);

/* Virtual address of pfn.  */
#घोषणा pfn_va(pfn)	__va(PFN_PHYS(pfn))

व्योम
update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	अचिन्हित दीर्घ pfn = pte_pfn(*ptep);
	काष्ठा page *page;

	/* We करोn't have pte special.  As a result, we can be called with
	   an invalid pfn and we करोn't need to flush the kernel dcache page.
	   This occurs with FireGL card in C8000.  */
	अगर (!pfn_valid(pfn))
		वापस;

	page = pfn_to_page(pfn);
	अगर (page_mapping_file(page) &&
	    test_bit(PG_dcache_dirty, &page->flags)) अणु
		flush_kernel_dcache_page_addr(pfn_va(pfn));
		clear_bit(PG_dcache_dirty, &page->flags);
	पूर्ण अन्यथा अगर (parisc_requires_coherency())
		flush_kernel_dcache_page_addr(pfn_va(pfn));
पूर्ण

व्योम
show_cache_info(काष्ठा seq_file *m)
अणु
	अक्षर buf[32];

	seq_म_लिखो(m, "I-cache\t\t: %ld KB\n", 
		cache_info.ic_size/1024 );
	अगर (cache_info.dc_loop != 1)
		snम_लिखो(buf, 32, "%lu-way associative", cache_info.dc_loop);
	seq_म_लिखो(m, "D-cache\t\t: %ld KB (%s%s, %s)\n",
		cache_info.dc_size/1024,
		(cache_info.dc_conf.cc_wt ? "WT":"WB"),
		(cache_info.dc_conf.cc_sh ? ", shared I/D":""),
		((cache_info.dc_loop == 1) ? "direct mapped" : buf));
	seq_म_लिखो(m, "ITLB entries\t: %ld\n" "DTLB entries\t: %ld%s\n",
		cache_info.it_size,
		cache_info.dt_size,
		cache_info.dt_conf.tc_sh ? " - shared with ITLB":""
	);
		
#अगर_अघोषित CONFIG_PA20
	/* BTLB - Block TLB */
	अगर (btlb_info.max_size==0) अणु
		seq_म_लिखो(m, "BTLB\t\t: not supported\n" );
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, 
		"BTLB fixed\t: max. %d pages, pagesize=%d (%dMB)\n"
		"BTLB fix-entr.\t: %d instruction, %d data (%d combined)\n"
		"BTLB var-entr.\t: %d instruction, %d data (%d combined)\n",
		btlb_info.max_size, (पूर्णांक)4096,
		btlb_info.max_size>>8,
		btlb_info.fixed_range_info.num_i,
		btlb_info.fixed_range_info.num_d,
		btlb_info.fixed_range_info.num_comb, 
		btlb_info.variable_range_info.num_i,
		btlb_info.variable_range_info.num_d,
		btlb_info.variable_range_info.num_comb
		);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम __init 
parisc_cache_init(व्योम)
अणु
	अगर (pdc_cache_info(&cache_info) < 0)
		panic("parisc_cache_init: pdc_cache_info failed");

#अगर 0
	prपूर्णांकk("ic_size %lx dc_size %lx it_size %lx\n",
		cache_info.ic_size,
		cache_info.dc_size,
		cache_info.it_size);

	prपूर्णांकk("DC  base 0x%lx stride 0x%lx count 0x%lx loop 0x%lx\n",
		cache_info.dc_base,
		cache_info.dc_stride,
		cache_info.dc_count,
		cache_info.dc_loop);

	prपूर्णांकk("dc_conf = 0x%lx  alias %d blk %d line %d shift %d\n",
		*(अचिन्हित दीर्घ *) (&cache_info.dc_conf),
		cache_info.dc_conf.cc_alias,
		cache_info.dc_conf.cc_block,
		cache_info.dc_conf.cc_line,
		cache_info.dc_conf.cc_shअगरt);
	prपूर्णांकk("	wt %d sh %d cst %d hv %d\n",
		cache_info.dc_conf.cc_wt,
		cache_info.dc_conf.cc_sh,
		cache_info.dc_conf.cc_cst,
		cache_info.dc_conf.cc_hv);

	prपूर्णांकk("IC  base 0x%lx stride 0x%lx count 0x%lx loop 0x%lx\n",
		cache_info.ic_base,
		cache_info.ic_stride,
		cache_info.ic_count,
		cache_info.ic_loop);

	prपूर्णांकk("IT  base 0x%lx stride 0x%lx count 0x%lx loop 0x%lx off_base 0x%lx off_stride 0x%lx off_count 0x%lx\n",
		cache_info.it_sp_base,
		cache_info.it_sp_stride,
		cache_info.it_sp_count,
		cache_info.it_loop,
		cache_info.it_off_base,
		cache_info.it_off_stride,
		cache_info.it_off_count);

	prपूर्णांकk("DT  base 0x%lx stride 0x%lx count 0x%lx loop 0x%lx off_base 0x%lx off_stride 0x%lx off_count 0x%lx\n",
		cache_info.dt_sp_base,
		cache_info.dt_sp_stride,
		cache_info.dt_sp_count,
		cache_info.dt_loop,
		cache_info.dt_off_base,
		cache_info.dt_off_stride,
		cache_info.dt_off_count);

	prपूर्णांकk("ic_conf = 0x%lx  alias %d blk %d line %d shift %d\n",
		*(अचिन्हित दीर्घ *) (&cache_info.ic_conf),
		cache_info.ic_conf.cc_alias,
		cache_info.ic_conf.cc_block,
		cache_info.ic_conf.cc_line,
		cache_info.ic_conf.cc_shअगरt);
	prपूर्णांकk("	wt %d sh %d cst %d hv %d\n",
		cache_info.ic_conf.cc_wt,
		cache_info.ic_conf.cc_sh,
		cache_info.ic_conf.cc_cst,
		cache_info.ic_conf.cc_hv);

	prपूर्णांकk("D-TLB conf: sh %d page %d cst %d aid %d sr %d\n",
		cache_info.dt_conf.tc_sh,
		cache_info.dt_conf.tc_page,
		cache_info.dt_conf.tc_cst,
		cache_info.dt_conf.tc_aid,
		cache_info.dt_conf.tc_sr);

	prपूर्णांकk("I-TLB conf: sh %d page %d cst %d aid %d sr %d\n",
		cache_info.it_conf.tc_sh,
		cache_info.it_conf.tc_page,
		cache_info.it_conf.tc_cst,
		cache_info.it_conf.tc_aid,
		cache_info.it_conf.tc_sr);
#पूर्ण_अगर

	split_tlb = 0;
	अगर (cache_info.dt_conf.tc_sh == 0 || cache_info.dt_conf.tc_sh == 2) अणु
		अगर (cache_info.dt_conf.tc_sh == 2)
			prपूर्णांकk(KERN_WARNING "Unexpected TLB configuration. "
			"Will flush I/D separately (could be optimized).\n");

		split_tlb = 1;
	पूर्ण

	/* "New and Improved" version from Jim Hull 
	 *	(1 << (cc_block-1)) * (cc_line << (4 + cnf.cc_shअगरt))
	 * The following CAFL_STRIDE is an optimized version, see
	 * http://lists.parisc-linux.org/pipermail/parisc-linux/2004-June/023625.hपंचांगl
	 * http://lists.parisc-linux.org/pipermail/parisc-linux/2004-June/023671.hपंचांगl
	 */
#घोषणा CAFL_STRIDE(cnf) (cnf.cc_line << (3 + cnf.cc_block + cnf.cc_shअगरt))
	dcache_stride = CAFL_STRIDE(cache_info.dc_conf);
	icache_stride = CAFL_STRIDE(cache_info.ic_conf);
#अघोषित CAFL_STRIDE

#अगर_अघोषित CONFIG_PA20
	अगर (pdc_btlb_info(&btlb_info) < 0) अणु
		स_रखो(&btlb_info, 0, माप btlb_info);
	पूर्ण
#पूर्ण_अगर

	अगर ((boot_cpu_data.pdc.capabilities & PDC_MODEL_NVA_MASK) ==
						PDC_MODEL_NVA_UNSUPPORTED) अणु
		prपूर्णांकk(KERN_WARNING "parisc_cache_init: Only equivalent aliasing supported!\n");
#अगर 0
		panic("SMP kernel required to avoid non-equivalent aliasing");
#पूर्ण_अगर
	पूर्ण
पूर्ण

व्योम __init disable_sr_hashing(व्योम)
अणु
	पूर्णांक srhash_type, retval;
	अचिन्हित दीर्घ space_bits;

	चयन (boot_cpu_data.cpu_type) अणु
	हाल pcx: /* We shouldn't get this far.  setup.c should prevent it. */
		BUG();
		वापस;

	हाल pcxs:
	हाल pcxt:
	हाल pcxt_:
		srhash_type = SRHASH_PCXST;
		अवरोध;

	हाल pcxl:
		srhash_type = SRHASH_PCXL;
		अवरोध;

	हाल pcxl2: /* pcxl2 करोesn't support space रेजिस्टर hashing */
		वापस;

	शेष: /* Currently all PA2.0 machines use the same ins. sequence */
		srhash_type = SRHASH_PA20;
		अवरोध;
	पूर्ण

	disable_sr_hashing_यंत्र(srhash_type);

	retval = pdc_spaceid_bits(&space_bits);
	/* If this procedure isn't implemented, don't panic. */
	अगर (retval < 0 && retval != PDC_BAD_OPTION)
		panic("pdc_spaceid_bits call failed.\n");
	अगर (space_bits != 0)
		panic("SpaceID hashing is still on!\n");
पूर्ण

अटल अंतरभूत व्योम
__flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr,
		   अचिन्हित दीर्घ physaddr)
अणु
	preempt_disable();
	flush_dcache_page_यंत्र(physaddr, vmaddr);
	अगर (vma->vm_flags & VM_EXEC)
		flush_icache_page_यंत्र(physaddr, vmaddr);
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम
__purge_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr,
		   अचिन्हित दीर्घ physaddr)
अणु
	preempt_disable();
	purge_dcache_page_यंत्र(physaddr, vmaddr);
	अगर (vma->vm_flags & VM_EXEC)
		flush_icache_page_यंत्र(physaddr, vmaddr);
	preempt_enable();
पूर्ण

व्योम flush_dcache_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page_mapping_file(page);
	काष्ठा vm_area_काष्ठा *mpnt;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ addr, old_addr = 0;
	pgoff_t pgoff;

	अगर (mapping && !mapping_mapped(mapping)) अणु
		set_bit(PG_dcache_dirty, &page->flags);
		वापस;
	पूर्ण

	flush_kernel_dcache_page(page);

	अगर (!mapping)
		वापस;

	pgoff = page->index;

	/* We have carefully arranged in arch_get_unmapped_area() that
	 * *any* mappings of a file are always congruently mapped (whether
	 * declared as MAP_PRIVATE or MAP_SHARED), so we only need
	 * to flush one address here क्रम them all to become coherent */

	flush_dcache_mmap_lock(mapping);
	vma_पूर्णांकerval_tree_क्रमeach(mpnt, &mapping->i_mmap, pgoff, pgoff) अणु
		offset = (pgoff - mpnt->vm_pgoff) << PAGE_SHIFT;
		addr = mpnt->vm_start + offset;

		/* The TLB is the engine of coherence on parisc: The
		 * CPU is entitled to speculate any page with a TLB
		 * mapping, so here we समाप्त the mapping then flush the
		 * page aदीर्घ a special flush only alias mapping.
		 * This guarantees that the page is no-दीर्घer in the
		 * cache क्रम any process and nor may it be
		 * speculatively पढ़ो in (until the user or kernel
		 * specअगरically accesses it, of course) */

		flush_tlb_page(mpnt, addr);
		अगर (old_addr == 0 || (old_addr & (SHM_COLOUR - 1))
				      != (addr & (SHM_COLOUR - 1))) अणु
			__flush_cache_page(mpnt, addr, page_to_phys(page));
			अगर (parisc_requires_coherency() && old_addr)
				prपूर्णांकk(KERN_ERR "INEQUIVALENT ALIASES 0x%lx and 0x%lx in file %pD\n", old_addr, addr, mpnt->vm_file);
			old_addr = addr;
		पूर्ण
	पूर्ण
	flush_dcache_mmap_unlock(mapping);
पूर्ण
EXPORT_SYMBOL(flush_dcache_page);

/* Defined in arch/parisc/kernel/pacache.S */
EXPORT_SYMBOL(flush_kernel_dcache_range_यंत्र);
EXPORT_SYMBOL(flush_kernel_dcache_page_यंत्र);
EXPORT_SYMBOL(flush_data_cache_local);
EXPORT_SYMBOL(flush_kernel_icache_range_यंत्र);

#घोषणा FLUSH_THRESHOLD 0x80000 /* 0.5MB */
अटल अचिन्हित दीर्घ parisc_cache_flush_threshold __ro_after_init = FLUSH_THRESHOLD;

#घोषणा FLUSH_TLB_THRESHOLD (16*1024) /* 16 KiB minimum TLB threshold */
अटल अचिन्हित दीर्घ parisc_tlb_flush_threshold __ro_after_init = ~0UL;

व्योम __init parisc_setup_cache_timing(व्योम)
अणु
	अचिन्हित दीर्घ rangeसमय, allसमय;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ threshold;

	allसमय = mfctl(16);
	flush_data_cache();
	allसमय = mfctl(16) - allसमय;

	size = (अचिन्हित दीर्घ)(_end - _text);
	rangeसमय = mfctl(16);
	flush_kernel_dcache_range((अचिन्हित दीर्घ)_text, size);
	rangeसमय = mfctl(16) - rangeसमय;

	prपूर्णांकk(KERN_DEBUG "Whole cache flush %lu cycles, flushing %lu bytes %lu cycles\n",
		allसमय, size, rangeसमय);

	threshold = L1_CACHE_ALIGN(size * allसमय / rangeसमय);
	अगर (threshold > cache_info.dc_size)
		threshold = cache_info.dc_size;
	अगर (threshold)
		parisc_cache_flush_threshold = threshold;
	prपूर्णांकk(KERN_INFO "Cache flush threshold set to %lu KiB\n",
		parisc_cache_flush_threshold/1024);

	/* calculate TLB flush threshold */

	/* On SMP machines, skip the TLB measure of kernel text which
	 * has been mapped as huge pages. */
	अगर (num_online_cpus() > 1 && !parisc_requires_coherency()) अणु
		threshold = max(cache_info.it_size, cache_info.dt_size);
		threshold *= PAGE_SIZE;
		threshold /= num_online_cpus();
		जाओ set_tlb_threshold;
	पूर्ण

	size = (अचिन्हित दीर्घ)_end - (अचिन्हित दीर्घ)_text;
	rangeसमय = mfctl(16);
	flush_tlb_kernel_range((अचिन्हित दीर्घ)_text, (अचिन्हित दीर्घ)_end);
	rangeसमय = mfctl(16) - rangeसमय;

	allसमय = mfctl(16);
	flush_tlb_all();
	allसमय = mfctl(16) - allसमय;

	prपूर्णांकk(KERN_INFO "Whole TLB flush %lu cycles, Range flush %lu bytes %lu cycles\n",
		allसमय, size, rangeसमय);

	threshold = PAGE_ALIGN((num_online_cpus() * size * allसमय) / rangeसमय);
	prपूर्णांकk(KERN_INFO "Calculated TLB flush threshold %lu KiB\n",
		threshold/1024);

set_tlb_threshold:
	अगर (threshold > FLUSH_TLB_THRESHOLD)
		parisc_tlb_flush_threshold = threshold;
	अन्यथा
		parisc_tlb_flush_threshold = FLUSH_TLB_THRESHOLD;

	prपूर्णांकk(KERN_INFO "TLB flush threshold set to %lu KiB\n",
		parisc_tlb_flush_threshold/1024);
पूर्ण

बाह्य व्योम purge_kernel_dcache_page_यंत्र(अचिन्हित दीर्घ);
बाह्य व्योम clear_user_page_यंत्र(व्योम *, अचिन्हित दीर्घ);
बाह्य व्योम copy_user_page_यंत्र(व्योम *, व्योम *, अचिन्हित दीर्घ);

व्योम flush_kernel_dcache_page_addr(व्योम *addr)
अणु
	अचिन्हित दीर्घ flags;

	flush_kernel_dcache_page_यंत्र(addr);
	purge_tlb_start(flags);
	pdtlb_kernel(addr);
	purge_tlb_end(flags);
पूर्ण
EXPORT_SYMBOL(flush_kernel_dcache_page_addr);

व्योम copy_user_page(व्योम *vto, व्योम *vfrom, अचिन्हित दीर्घ vaddr,
	काष्ठा page *pg)
अणु
       /* Copy using kernel mapping.  No coherency is needed (all in
	  kunmap) क्रम the `to' page.  However, the `from' page needs to
	  be flushed through a mapping equivalent to the user mapping
	  beक्रमe it can be accessed through the kernel mapping. */
	preempt_disable();
	flush_dcache_page_यंत्र(__pa(vfrom), vaddr);
	copy_page_यंत्र(vto, vfrom);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(copy_user_page);

/* __flush_tlb_range()
 *
 * वापसs 1 अगर all TLBs were flushed.
 */
पूर्णांक __flush_tlb_range(अचिन्हित दीर्घ sid, अचिन्हित दीर्घ start,
		      अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ flags;

	अगर ((!IS_ENABLED(CONFIG_SMP) || !arch_irqs_disabled()) &&
	    end - start >= parisc_tlb_flush_threshold) अणु
		flush_tlb_all();
		वापस 1;
	पूर्ण

	/* Purge TLB entries क्रम small ranges using the pdtlb and
	   pitlb inकाष्ठाions.  These inकाष्ठाions execute locally
	   but cause a purge request to be broadcast to other TLBs.  */
	जबतक (start < end) अणु
		purge_tlb_start(flags);
		mtsp(sid, 1);
		pdtlb(start);
		pitlb(start);
		purge_tlb_end(flags);
		start += PAGE_SIZE;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cacheflush_h_पंचांगp_function(व्योम *dummy)
अणु
	flush_cache_all_local();
पूर्ण

व्योम flush_cache_all(व्योम)
अणु
	on_each_cpu(cacheflush_h_पंचांगp_function, शून्य, 1);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mm_total_size(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ usize = 0;

	क्रम (vma = mm->mmap; vma; vma = vma->vm_next)
		usize += vma->vm_end - vma->vm_start;
	वापस usize;
पूर्ण

अटल अंतरभूत pte_t *get_ptep(pgd_t *pgd, अचिन्हित दीर्घ addr)
अणु
	pte_t *ptep = शून्य;

	अगर (!pgd_none(*pgd)) अणु
		p4d_t *p4d = p4d_offset(pgd, addr);
		अगर (!p4d_none(*p4d)) अणु
			pud_t *pud = pud_offset(p4d, addr);
			अगर (!pud_none(*pud)) अणु
				pmd_t *pmd = pmd_offset(pud, addr);
				अगर (!pmd_none(*pmd))
					ptep = pte_offset_map(pmd, addr);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ptep;
पूर्ण

व्योम flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	pgd_t *pgd;

	/* Flushing the whole cache on each cpu takes क्रमever on
	   rp3440, etc.  So, aव्योम it अगर the mm isn't too big.  */
	अगर ((!IS_ENABLED(CONFIG_SMP) || !arch_irqs_disabled()) &&
	    mm_total_size(mm) >= parisc_cache_flush_threshold) अणु
		अगर (mm->context)
			flush_tlb_all();
		flush_cache_all();
		वापस;
	पूर्ण

	अगर (mm->context == mfsp(3)) अणु
		क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
			flush_user_dcache_range_यंत्र(vma->vm_start, vma->vm_end);
			अगर (vma->vm_flags & VM_EXEC)
				flush_user_icache_range_यंत्र(vma->vm_start, vma->vm_end);
			flush_tlb_range(vma, vma->vm_start, vma->vm_end);
		पूर्ण
		वापस;
	पूर्ण

	pgd = mm->pgd;
	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		अचिन्हित दीर्घ addr;

		क्रम (addr = vma->vm_start; addr < vma->vm_end;
		     addr += PAGE_SIZE) अणु
			अचिन्हित दीर्घ pfn;
			pte_t *ptep = get_ptep(pgd, addr);
			अगर (!ptep)
				जारी;
			pfn = pte_pfn(*ptep);
			अगर (!pfn_valid(pfn))
				जारी;
			अगर (unlikely(mm->context)) अणु
				flush_tlb_page(vma, addr);
				__flush_cache_page(vma, addr, PFN_PHYS(pfn));
			पूर्ण अन्यथा अणु
				__purge_cache_page(vma, addr, PFN_PHYS(pfn));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	pgd_t *pgd;
	अचिन्हित दीर्घ addr;

	अगर ((!IS_ENABLED(CONFIG_SMP) || !arch_irqs_disabled()) &&
	    end - start >= parisc_cache_flush_threshold) अणु
		अगर (vma->vm_mm->context)
			flush_tlb_range(vma, start, end);
		flush_cache_all();
		वापस;
	पूर्ण

	अगर (vma->vm_mm->context == mfsp(3)) अणु
		flush_user_dcache_range_यंत्र(start, end);
		अगर (vma->vm_flags & VM_EXEC)
			flush_user_icache_range_यंत्र(start, end);
		flush_tlb_range(vma, start, end);
		वापस;
	पूर्ण

	pgd = vma->vm_mm->pgd;
	क्रम (addr = vma->vm_start; addr < vma->vm_end; addr += PAGE_SIZE) अणु
		अचिन्हित दीर्घ pfn;
		pte_t *ptep = get_ptep(pgd, addr);
		अगर (!ptep)
			जारी;
		pfn = pte_pfn(*ptep);
		अगर (pfn_valid(pfn)) अणु
			अगर (unlikely(vma->vm_mm->context)) अणु
				flush_tlb_page(vma, addr);
				__flush_cache_page(vma, addr, PFN_PHYS(pfn));
			पूर्ण अन्यथा अणु
				__purge_cache_page(vma, addr, PFN_PHYS(pfn));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम
flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr, अचिन्हित दीर्घ pfn)
अणु
	अगर (pfn_valid(pfn)) अणु
		अगर (likely(vma->vm_mm->context)) अणु
			flush_tlb_page(vma, vmaddr);
			__flush_cache_page(vma, vmaddr, PFN_PHYS(pfn));
		पूर्ण अन्यथा अणु
			__purge_cache_page(vma, vmaddr, PFN_PHYS(pfn));
		पूर्ण
	पूर्ण
पूर्ण

व्योम flush_kernel_vmap_range(व्योम *vaddr, पूर्णांक size)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)vaddr;
	अचिन्हित दीर्घ end = start + size;

	अगर ((!IS_ENABLED(CONFIG_SMP) || !arch_irqs_disabled()) &&
	    (अचिन्हित दीर्घ)size >= parisc_cache_flush_threshold) अणु
		flush_tlb_kernel_range(start, end);
		flush_data_cache();
		वापस;
	पूर्ण

	flush_kernel_dcache_range_यंत्र(start, end);
	flush_tlb_kernel_range(start, end);
पूर्ण
EXPORT_SYMBOL(flush_kernel_vmap_range);

व्योम invalidate_kernel_vmap_range(व्योम *vaddr, पूर्णांक size)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)vaddr;
	अचिन्हित दीर्घ end = start + size;

	अगर ((!IS_ENABLED(CONFIG_SMP) || !arch_irqs_disabled()) &&
	    (अचिन्हित दीर्घ)size >= parisc_cache_flush_threshold) अणु
		flush_tlb_kernel_range(start, end);
		flush_data_cache();
		वापस;
	पूर्ण

	purge_kernel_dcache_range_यंत्र(start, end);
	flush_tlb_kernel_range(start, end);
पूर्ण
EXPORT_SYMBOL(invalidate_kernel_vmap_range);
