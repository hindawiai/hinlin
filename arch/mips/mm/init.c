<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994 - 2000 Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.
 */
#समावेश <linux/bug.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/swap.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/pfn.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kcore.h>
#समावेश <linux/initrd.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cachectl.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/maar.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/fixmap.h>

/*
 * We have up to 8 empty zeroed pages so we can map one of the right colour
 * when needed.	 This is necessary only on R4000 / R4400 SC and MC versions
 * where we have to aव्योम VCED / VECI exceptions क्रम good perक्रमmance at
 * any price.  Since page is never written to after the initialization we
 * करोn't have to care about aliases on other CPUs.
 */
अचिन्हित दीर्घ empty_zero_page, zero_page_mask;
EXPORT_SYMBOL_GPL(empty_zero_page);
EXPORT_SYMBOL(zero_page_mask);

/*
 * Not अटल अंतरभूत because used by IP27 special magic initialization code
 */
व्योम setup_zero_pages(व्योम)
अणु
	अचिन्हित पूर्णांक order, i;
	काष्ठा page *page;

	अगर (cpu_has_vce)
		order = 3;
	अन्यथा
		order = 0;

	empty_zero_page = __get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, order);
	अगर (!empty_zero_page)
		panic("Oh boy, that early out of memory?");

	page = virt_to_page((व्योम *)empty_zero_page);
	split_page(page, order);
	क्रम (i = 0; i < (1 << order); i++, page++)
		mark_page_reserved(page);

	zero_page_mask = ((PAGE_SIZE << order) - 1) & PAGE_MASK;
पूर्ण

अटल व्योम *__kmap_pgprot(काष्ठा page *page, अचिन्हित दीर्घ addr, pgprot_t prot)
अणु
	क्रमागत fixed_addresses idx;
	अचिन्हित पूर्णांक old_mmid;
	अचिन्हित दीर्घ vaddr, flags, entrylo;
	अचिन्हित दीर्घ old_ctx;
	pte_t pte;
	पूर्णांक tlbidx;

	BUG_ON(Page_dcache_dirty(page));

	preempt_disable();
	pagefault_disable();
	idx = (addr >> PAGE_SHIFT) & (FIX_N_COLOURS - 1);
	idx += in_पूर्णांकerrupt() ? FIX_N_COLOURS : 0;
	vaddr = __fix_to_virt(FIX_CMAP_END - idx);
	pte = mk_pte(page, prot);
#अगर defined(CONFIG_XPA)
	entrylo = pte_to_entrylo(pte.pte_high);
#या_अगर defined(CONFIG_PHYS_ADDR_T_64BIT) && defined(CONFIG_CPU_MIPS32)
	entrylo = pte.pte_high;
#अन्यथा
	entrylo = pte_to_entrylo(pte_val(pte));
#पूर्ण_अगर

	local_irq_save(flags);
	old_ctx = पढ़ो_c0_entryhi();
	ग_लिखो_c0_entryhi(vaddr & (PAGE_MASK << 1));
	ग_लिखो_c0_entrylo0(entrylo);
	ग_लिखो_c0_entrylo1(entrylo);
	अगर (cpu_has_mmid) अणु
		old_mmid = पढ़ो_c0_memorymapid();
		ग_लिखो_c0_memorymapid(MMID_KERNEL_WIRED);
	पूर्ण
#अगर_घोषित CONFIG_XPA
	अगर (cpu_has_xpa) अणु
		entrylo = (pte.pte_low & _PFNX_MASK);
		ग_लिखोx_c0_entrylo0(entrylo);
		ग_लिखोx_c0_entrylo1(entrylo);
	पूर्ण
#पूर्ण_अगर
	tlbidx = num_wired_entries();
	ग_लिखो_c0_wired(tlbidx + 1);
	ग_लिखो_c0_index(tlbidx);
	mtc0_tlbw_hazard();
	tlb_ग_लिखो_indexed();
	tlbw_use_hazard();
	ग_लिखो_c0_entryhi(old_ctx);
	अगर (cpu_has_mmid)
		ग_लिखो_c0_memorymapid(old_mmid);
	local_irq_restore(flags);

	वापस (व्योम*) vaddr;
पूर्ण

व्योम *kmap_coherent(काष्ठा page *page, अचिन्हित दीर्घ addr)
अणु
	वापस __kmap_pgprot(page, addr, PAGE_KERNEL);
पूर्ण

व्योम *kmap_noncoherent(काष्ठा page *page, अचिन्हित दीर्घ addr)
अणु
	वापस __kmap_pgprot(page, addr, PAGE_KERNEL_NC);
पूर्ण

व्योम kunmap_coherent(व्योम)
अणु
	अचिन्हित पूर्णांक wired;
	अचिन्हित दीर्घ flags, old_ctx;

	local_irq_save(flags);
	old_ctx = पढ़ो_c0_entryhi();
	wired = num_wired_entries() - 1;
	ग_लिखो_c0_wired(wired);
	ग_लिखो_c0_index(wired);
	ग_लिखो_c0_entryhi(UNIQUE_ENTRYHI(wired));
	ग_लिखो_c0_entrylo0(0);
	ग_लिखो_c0_entrylo1(0);
	mtc0_tlbw_hazard();
	tlb_ग_लिखो_indexed();
	tlbw_use_hazard();
	ग_लिखो_c0_entryhi(old_ctx);
	local_irq_restore(flags);
	pagefault_enable();
	preempt_enable();
पूर्ण

व्योम copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
	अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	व्योम *vfrom, *vto;

	vto = kmap_atomic(to);
	अगर (cpu_has_dc_aliases &&
	    page_mapcount(from) && !Page_dcache_dirty(from)) अणु
		vfrom = kmap_coherent(from, vaddr);
		copy_page(vto, vfrom);
		kunmap_coherent();
	पूर्ण अन्यथा अणु
		vfrom = kmap_atomic(from);
		copy_page(vto, vfrom);
		kunmap_atomic(vfrom);
	पूर्ण
	अगर ((!cpu_has_ic_fills_f_dc) ||
	    pages_करो_alias((अचिन्हित दीर्घ)vto, vaddr & PAGE_MASK))
		flush_data_cache_page((अचिन्हित दीर्घ)vto);
	kunmap_atomic(vto);
	/* Make sure this page is cleared on other CPU's too beक्रमe using it */
	smp_wmb();
पूर्ण

व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma,
	काष्ठा page *page, अचिन्हित दीर्घ vaddr, व्योम *dst, स्थिर व्योम *src,
	अचिन्हित दीर्घ len)
अणु
	अगर (cpu_has_dc_aliases &&
	    page_mapcount(page) && !Page_dcache_dirty(page)) अणु
		व्योम *vto = kmap_coherent(page, vaddr) + (vaddr & ~PAGE_MASK);
		स_नकल(vto, src, len);
		kunmap_coherent();
	पूर्ण अन्यथा अणु
		स_नकल(dst, src, len);
		अगर (cpu_has_dc_aliases)
			SetPageDcacheDirty(page);
	पूर्ण
	अगर (vma->vm_flags & VM_EXEC)
		flush_cache_page(vma, vaddr, page_to_pfn(page));
पूर्ण

व्योम copy_from_user_page(काष्ठा vm_area_काष्ठा *vma,
	काष्ठा page *page, अचिन्हित दीर्घ vaddr, व्योम *dst, स्थिर व्योम *src,
	अचिन्हित दीर्घ len)
अणु
	अगर (cpu_has_dc_aliases &&
	    page_mapcount(page) && !Page_dcache_dirty(page)) अणु
		व्योम *vfrom = kmap_coherent(page, vaddr) + (vaddr & ~PAGE_MASK);
		स_नकल(dst, vfrom, len);
		kunmap_coherent();
	पूर्ण अन्यथा अणु
		स_नकल(dst, src, len);
		अगर (cpu_has_dc_aliases)
			SetPageDcacheDirty(page);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(copy_from_user_page);

व्योम __init fixrange_init(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
	pgd_t *pgd_base)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	पूर्णांक i, j, k;
	अचिन्हित दीर्घ vaddr;

	vaddr = start;
	i = pgd_index(vaddr);
	j = pud_index(vaddr);
	k = pmd_index(vaddr);
	pgd = pgd_base + i;

	क्रम ( ; (i < PTRS_PER_PGD) && (vaddr < end); pgd++, i++) अणु
		pud = (pud_t *)pgd;
		क्रम ( ; (j < PTRS_PER_PUD) && (vaddr < end); pud++, j++) अणु
			pmd = (pmd_t *)pud;
			क्रम (; (k < PTRS_PER_PMD) && (vaddr < end); pmd++, k++) अणु
				अगर (pmd_none(*pmd)) अणु
					pte = (pte_t *) memblock_alloc_low(PAGE_SIZE,
									   PAGE_SIZE);
					अगर (!pte)
						panic("%s: Failed to allocate %lu bytes align=%lx\n",
						      __func__, PAGE_SIZE,
						      PAGE_SIZE);

					set_pmd(pmd, __pmd((अचिन्हित दीर्घ)pte));
					BUG_ON(pte != pte_offset_kernel(pmd, 0));
				पूर्ण
				vaddr += PMD_SIZE;
			पूर्ण
			k = 0;
		पूर्ण
		j = 0;
	पूर्ण
#पूर्ण_अगर
पूर्ण

काष्ठा maar_walk_info अणु
	काष्ठा maar_config cfg[16];
	अचिन्हित पूर्णांक num_cfg;
पूर्ण;

अटल पूर्णांक maar_res_walk(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages,
			 व्योम *data)
अणु
	काष्ठा maar_walk_info *wi = data;
	काष्ठा maar_config *cfg = &wi->cfg[wi->num_cfg];
	अचिन्हित पूर्णांक maar_align;

	/* MAAR रेजिस्टरs hold physical addresses right shअगरted by 4 bits */
	maar_align = BIT(MIPS_MAAR_ADDR_SHIFT + 4);

	/* Fill in the MAAR config entry */
	cfg->lower = ALIGN(PFN_PHYS(start_pfn), maar_align);
	cfg->upper = ALIGN_DOWN(PFN_PHYS(start_pfn + nr_pages), maar_align) - 1;
	cfg->attrs = MIPS_MAAR_S;

	/* Ensure we करोn't overflow the cfg array */
	अगर (!WARN_ON(wi->num_cfg >= ARRAY_SIZE(wi->cfg)))
		wi->num_cfg++;

	वापस 0;
पूर्ण


अचिन्हित __weak platक्रमm_maar_init(अचिन्हित num_pairs)
अणु
	अचिन्हित पूर्णांक num_configured;
	काष्ठा maar_walk_info wi;

	wi.num_cfg = 0;
	walk_प्रणाली_ram_range(0, max_pfn, &wi, maar_res_walk);

	num_configured = maar_config(wi.cfg, wi.num_cfg, num_pairs);
	अगर (num_configured < wi.num_cfg)
		pr_warn("Not enough MAAR pairs (%u) for all memory regions (%u)\n",
			num_pairs, wi.num_cfg);

	वापस num_configured;
पूर्ण

व्योम maar_init(व्योम)
अणु
	अचिन्हित num_maars, used, i;
	phys_addr_t lower, upper, attr;
	अटल काष्ठा अणु
		काष्ठा maar_config cfgs[3];
		अचिन्हित used;
	पूर्ण recorded = अणु अणु अणु 0 पूर्ण पूर्ण, 0 पूर्ण;

	अगर (!cpu_has_maar)
		वापस;

	/* Detect the number of MAARs */
	ग_लिखो_c0_maari(~0);
	back_to_back_c0_hazard();
	num_maars = पढ़ो_c0_maari() + 1;

	/* MAARs should be in pairs */
	WARN_ON(num_maars % 2);

	/* Set MAARs using values we recorded alपढ़ोy */
	अगर (recorded.used) अणु
		used = maar_config(recorded.cfgs, recorded.used, num_maars / 2);
		BUG_ON(used != recorded.used);
	पूर्ण अन्यथा अणु
		/* Configure the required MAARs */
		used = platक्रमm_maar_init(num_maars / 2);
	पूर्ण

	/* Disable any further MAARs */
	क्रम (i = (used * 2); i < num_maars; i++) अणु
		ग_लिखो_c0_maari(i);
		back_to_back_c0_hazard();
		ग_लिखो_c0_maar(0);
		back_to_back_c0_hazard();
	पूर्ण

	अगर (recorded.used)
		वापस;

	pr_info("MAAR configuration:\n");
	क्रम (i = 0; i < num_maars; i += 2) अणु
		ग_लिखो_c0_maari(i);
		back_to_back_c0_hazard();
		upper = पढ़ो_c0_maar();
#अगर_घोषित CONFIG_XPA
		upper |= (phys_addr_t)पढ़ोx_c0_maar() << MIPS_MAARX_ADDR_SHIFT;
#पूर्ण_अगर

		ग_लिखो_c0_maari(i + 1);
		back_to_back_c0_hazard();
		lower = पढ़ो_c0_maar();
#अगर_घोषित CONFIG_XPA
		lower |= (phys_addr_t)पढ़ोx_c0_maar() << MIPS_MAARX_ADDR_SHIFT;
#पूर्ण_अगर

		attr = lower & upper;
		lower = (lower & MIPS_MAAR_ADDR) << 4;
		upper = ((upper & MIPS_MAAR_ADDR) << 4) | 0xffff;

		pr_info("  [%d]: ", i / 2);
		अगर ((attr & MIPS_MAAR_V) != MIPS_MAAR_V) अणु
			pr_cont("disabled\n");
			जारी;
		पूर्ण

		pr_cont("%pa-%pa", &lower, &upper);

		अगर (attr & MIPS_MAAR_S)
			pr_cont(" speculate");

		pr_cont("\n");

		/* Record the setup क्रम use on secondary CPUs */
		अगर (used <= ARRAY_SIZE(recorded.cfgs)) अणु
			recorded.cfgs[recorded.used].lower = lower;
			recorded.cfgs[recorded.used].upper = upper;
			recorded.cfgs[recorded.used].attrs = attr;
			recorded.used++;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_अघोषित CONFIG_NEED_MULTIPLE_NODES
व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ max_zone_pfns[MAX_NR_ZONES];

	pagetable_init();

#अगर_घोषित CONFIG_ZONE_DMA
	max_zone_pfns[ZONE_DMA] = MAX_DMA_PFN;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ZONE_DMA32
	max_zone_pfns[ZONE_DMA32] = MAX_DMA32_PFN;
#पूर्ण_अगर
	max_zone_pfns[ZONE_NORMAL] = max_low_pfn;
#अगर_घोषित CONFIG_HIGHMEM
	max_zone_pfns[ZONE_HIGHMEM] = highend_pfn;

	अगर (cpu_has_dc_aliases && max_low_pfn != highend_pfn) अणु
		prपूर्णांकk(KERN_WARNING "This processor doesn't support highmem."
		       " %ldk highmem ignored\n",
		       (highend_pfn - max_low_pfn) << (PAGE_SHIFT - 10));
		max_zone_pfns[ZONE_HIGHMEM] = max_low_pfn;
	पूर्ण
#पूर्ण_अगर

	मुक्त_area_init(max_zone_pfns);
पूर्ण

#अगर_घोषित CONFIG_64BIT
अटल काष्ठा kcore_list kcore_kseg0;
#पूर्ण_अगर

अटल अंतरभूत व्योम __init mem_init_मुक्त_highmem(व्योम)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	अचिन्हित दीर्घ पंचांगp;

	अगर (cpu_has_dc_aliases)
		वापस;

	क्रम (पंचांगp = highstart_pfn; पंचांगp < highend_pfn; पंचांगp++) अणु
		काष्ठा page *page = pfn_to_page(पंचांगp);

		अगर (!memblock_is_memory(PFN_PHYS(पंचांगp)))
			SetPageReserved(page);
		अन्यथा
			मुक्त_highmem_page(page);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम __init mem_init(व्योम)
अणु
	/*
	 * When _PFN_SHIFT is greater than PAGE_SHIFT we won't have enough PTE
	 * bits to hold a full 32b physical address on MIPS32 प्रणालीs.
	 */
	BUILD_BUG_ON(IS_ENABLED(CONFIG_32BIT) && (_PFN_SHIFT > PAGE_SHIFT));

#अगर_घोषित CONFIG_HIGHMEM
#अगर_घोषित CONFIG_DISCONTIGMEM
#त्रुटि "CONFIG_HIGHMEM and CONFIG_DISCONTIGMEM dont work together yet"
#पूर्ण_अगर
	max_mapnr = highend_pfn ? highend_pfn : max_low_pfn;
#अन्यथा
	max_mapnr = max_low_pfn;
#पूर्ण_अगर
	high_memory = (व्योम *) __va(max_low_pfn << PAGE_SHIFT);

	maar_init();
	memblock_मुक्त_all();
	setup_zero_pages();	/* Setup zeroed pages.  */
	mem_init_मुक्त_highmem();

#अगर_घोषित CONFIG_64BIT
	अगर ((अचिन्हित दीर्घ) &_text > (अचिन्हित दीर्घ) CKSEG0)
		/* The -4 is a hack so that user tools करोn't have to handle
		   the overflow.  */
		kclist_add(&kcore_kseg0, (व्योम *) CKSEG0,
				0x80000000 - 4, KCORE_TEXT);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर /* !CONFIG_NEED_MULTIPLE_NODES */

व्योम मुक्त_init_pages(स्थिर अक्षर *what, अचिन्हित दीर्घ begin, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ pfn;

	क्रम (pfn = PFN_UP(begin); pfn < PFN_DOWN(end); pfn++) अणु
		काष्ठा page *page = pfn_to_page(pfn);
		व्योम *addr = phys_to_virt(PFN_PHYS(pfn));

		स_रखो(addr, POISON_FREE_INITMEM, PAGE_SIZE);
		मुक्त_reserved_page(page);
	पूर्ण
	prपूर्णांकk(KERN_INFO "Freeing %s: %ldk freed\n", what, (end - begin) >> 10);
पूर्ण

व्योम (*मुक्त_init_pages_eva)(व्योम *begin, व्योम *end) = शून्य;

व्योम __weak __init prom_मुक्त_prom_memory(व्योम)
अणु
	/* nothing to करो */
पूर्ण

व्योम __ref मुक्त_iniपंचांगem(व्योम)
अणु
	prom_मुक्त_prom_memory();
	/*
	 * Let the platक्रमm define a specअगरic function to मुक्त the
	 * init section since EVA may have used any possible mapping
	 * between भव and physical addresses.
	 */
	अगर (मुक्त_init_pages_eva)
		मुक्त_init_pages_eva((व्योम *)&__init_begin, (व्योम *)&__init_end);
	अन्यथा
		मुक्त_iniपंचांगem_शेष(POISON_FREE_INITMEM);
पूर्ण

#अगर_घोषित CONFIG_HAVE_SETUP_PER_CPU_AREA
अचिन्हित दीर्घ __per_cpu_offset[NR_CPUS] __पढ़ो_mostly;
EXPORT_SYMBOL(__per_cpu_offset);

अटल पूर्णांक __init pcpu_cpu_distance(अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to)
अणु
	वापस node_distance(cpu_to_node(from), cpu_to_node(to));
पूर्ण

अटल व्योम * __init pcpu_fc_alloc(अचिन्हित पूर्णांक cpu, माप_प्रकार size,
				       माप_प्रकार align)
अणु
	वापस memblock_alloc_try_nid(size, align, __pa(MAX_DMA_ADDRESS),
				      MEMBLOCK_ALLOC_ACCESSIBLE,
				      cpu_to_node(cpu));
पूर्ण

अटल व्योम __init pcpu_fc_मुक्त(व्योम *ptr, माप_प्रकार size)
अणु
	memblock_मुक्त_early(__pa(ptr), size);
पूर्ण

व्योम __init setup_per_cpu_areas(व्योम)
अणु
	अचिन्हित दीर्घ delta;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक rc;

	/*
	 * Always reserve area क्रम module percpu variables.  That's
	 * what the legacy allocator did.
	 */
	rc = pcpu_embed_first_chunk(PERCPU_MODULE_RESERVE,
				    PERCPU_DYNAMIC_RESERVE, PAGE_SIZE,
				    pcpu_cpu_distance,
				    pcpu_fc_alloc, pcpu_fc_मुक्त);
	अगर (rc < 0)
		panic("Failed to initialize percpu areas.");

	delta = (अचिन्हित दीर्घ)pcpu_base_addr - (अचिन्हित दीर्घ)__per_cpu_start;
	क्रम_each_possible_cpu(cpu)
		__per_cpu_offset[cpu] = delta + pcpu_unit_offsets[cpu];
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_MIPS_PGD_C0_CONTEXT
अचिन्हित दीर्घ pgd_current[NR_CPUS];
#पूर्ण_अगर

/*
 * Align swapper_pg_dir in to 64K, allows its address to be loaded
 * with a single LUI inकाष्ठाion in the TLB handlers.  If we used
 * __aligned(64K), its size would get rounded up to the alignment
 * size, and waste space.  So we place it in its own section and align
 * it in the linker script.
 */
pgd_t swapper_pg_dir[PTRS_PER_PGD] __section(".bss..swapper_pg_dir");
#अगर_अघोषित __PAGETABLE_PUD_FOLDED
pud_t invalid_pud_table[PTRS_PER_PUD] __page_aligned_bss;
#पूर्ण_अगर
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
pmd_t invalid_pmd_table[PTRS_PER_PMD] __page_aligned_bss;
EXPORT_SYMBOL_GPL(invalid_pmd_table);
#पूर्ण_अगर
pte_t invalid_pte_table[PTRS_PER_PTE] __page_aligned_bss;
EXPORT_SYMBOL(invalid_pte_table);
