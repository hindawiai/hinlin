<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  PowerPC version
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Modअगरications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *  PPC44x/36-bit changes by Matt Porter (mporter@mvista.com)
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 */

#समावेश <linux/memblock.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/suspend.h>
#समावेश <linux/dma-direct.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/kasan.h>
#समावेश <यंत्र/sparseस्मृति.स>
#समावेश <यंत्र/svm.h>

#समावेश <mm/mmu_decl.h>

अचिन्हित दीर्घ दीर्घ memory_limit;
bool init_mem_is_मुक्त;

pgprot_t phys_mem_access_prot(काष्ठा file *file, अचिन्हित दीर्घ pfn,
			      अचिन्हित दीर्घ size, pgprot_t vma_prot)
अणु
	अगर (ppc_md.phys_mem_access_prot)
		वापस ppc_md.phys_mem_access_prot(file, pfn, size, vma_prot);

	अगर (!page_is_ram(pfn))
		vma_prot = pgprot_noncached(vma_prot);

	वापस vma_prot;
पूर्ण
EXPORT_SYMBOL(phys_mem_access_prot);

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
अटल DEFINE_MUTEX(linear_mapping_mutex);

#अगर_घोषित CONFIG_NUMA
पूर्णांक memory_add_physaddr_to_nid(u64 start)
अणु
	वापस hot_add_scn_to_nid(start);
पूर्ण
#पूर्ण_अगर

पूर्णांक __weak create_section_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				  पूर्णांक nid, pgprot_t prot)
अणु
	वापस -ENODEV;
पूर्ण

पूर्णांक __weak हटाओ_section_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	वापस -ENODEV;
पूर्ण

पूर्णांक __ref arch_create_linear_mapping(पूर्णांक nid, u64 start, u64 size,
				     काष्ठा mhp_params *params)
अणु
	पूर्णांक rc;

	start = (अचिन्हित दीर्घ)__va(start);
	mutex_lock(&linear_mapping_mutex);
	rc = create_section_mapping(start, start + size, nid,
				    params->pgprot);
	mutex_unlock(&linear_mapping_mutex);
	अगर (rc) अणु
		pr_warn("Unable to create linear mapping for 0x%llx..0x%llx: %d\n",
			start, start + size, rc);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

व्योम __ref arch_हटाओ_linear_mapping(u64 start, u64 size)
अणु
	पूर्णांक ret;

	/* Remove htab bolted mappings क्रम this section of memory */
	start = (अचिन्हित दीर्घ)__va(start);

	mutex_lock(&linear_mapping_mutex);
	ret = हटाओ_section_mapping(start, start + size);
	mutex_unlock(&linear_mapping_mutex);
	अगर (ret)
		pr_warn("Unable to remove linear mapping for 0x%llx..0x%llx: %d\n",
			start, start + size, ret);

	/* Ensure all vदो_स्मृति mappings are flushed in हाल they also
	 * hit that section of memory
	 */
	vm_unmap_aliases();
पूर्ण

पूर्णांक __ref arch_add_memory(पूर्णांक nid, u64 start, u64 size,
			  काष्ठा mhp_params *params)
अणु
	अचिन्हित दीर्घ start_pfn = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;
	पूर्णांक rc;

	rc = arch_create_linear_mapping(nid, start, size, params);
	अगर (rc)
		वापस rc;
	rc = __add_pages(nid, start_pfn, nr_pages, params);
	अगर (rc)
		arch_हटाओ_linear_mapping(start, size);
	वापस rc;
पूर्ण

व्योम __ref arch_हटाओ_memory(पूर्णांक nid, u64 start, u64 size,
			      काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ start_pfn = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;

	__हटाओ_pages(start_pfn, nr_pages, alपंचांगap);
	arch_हटाओ_linear_mapping(start, size);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_NEED_MULTIPLE_NODES
व्योम __init mem_topology_setup(व्योम)
अणु
	max_low_pfn = max_pfn = memblock_end_of_DRAM() >> PAGE_SHIFT;
	min_low_pfn = MEMORY_START >> PAGE_SHIFT;
#अगर_घोषित CONFIG_HIGHMEM
	max_low_pfn = lowmem_end_addr >> PAGE_SHIFT;
#पूर्ण_अगर

	/* Place all memblock_regions in the same node and merge contiguous
	 * memblock_regions
	 */
	memblock_set_node(0, PHYS_ADDR_MAX, &memblock.memory, 0);
पूर्ण

व्योम __init iniपंचांगem_init(व्योम)
अणु
	sparse_init();
पूर्ण

/* mark pages that करोn't exist as nosave */
अटल पूर्णांक __init mark_nonram_nosave(व्योम)
अणु
	अचिन्हित दीर्घ spfn, epfn, prev = 0;
	पूर्णांक i;

	क्रम_each_mem_pfn_range(i, MAX_NUMNODES, &spfn, &epfn, शून्य) अणु
		अगर (prev && prev < spfn)
			रेजिस्टर_nosave_region(prev, spfn);

		prev = epfn;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा /* CONFIG_NEED_MULTIPLE_NODES */
अटल पूर्णांक __init mark_nonram_nosave(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Zones usage:
 *
 * We setup ZONE_DMA to be 31-bits on all platक्रमms and ZONE_NORMAL to be
 * everything अन्यथा. GFP_DMA32 page allocations स्वतःmatically fall back to
 * ZONE_DMA.
 *
 * By using 31-bit unconditionally, we can exploit zone_dma_bits to inक्रमm the
 * generic DMA mapping code.  32-bit only devices (अगर not handled by an IOMMU
 * anyway) will take a first dip पूर्णांकo ZONE_NORMAL and get otherwise served by
 * ZONE_DMA.
 */
अटल अचिन्हित दीर्घ max_zone_pfns[MAX_NR_ZONES];

/*
 * paging_init() sets up the page tables - in fact we've alपढ़ोy करोne this.
 */
व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ total_ram = memblock_phys_mem_size();
	phys_addr_t top_of_ram = memblock_end_of_DRAM();

#अगर_घोषित CONFIG_HIGHMEM
	अचिन्हित दीर्घ v = __fix_to_virt(FIX_KMAP_END);
	अचिन्हित दीर्घ end = __fix_to_virt(FIX_KMAP_BEGIN);

	क्रम (; v < end; v += PAGE_SIZE)
		map_kernel_page(v, 0, __pgprot(0)); /* XXX gross */

	map_kernel_page(PKMAP_BASE, 0, __pgprot(0));	/* XXX gross */
	pkmap_page_table = virt_to_kpte(PKMAP_BASE);
#पूर्ण_अगर /* CONFIG_HIGHMEM */

	prपूर्णांकk(KERN_DEBUG "Top of RAM: 0x%llx, Total RAM: 0x%llx\n",
	       (अचिन्हित दीर्घ दीर्घ)top_of_ram, total_ram);
	prपूर्णांकk(KERN_DEBUG "Memory hole size: %ldMB\n",
	       (दीर्घ पूर्णांक)((top_of_ram - total_ram) >> 20));

	/*
	 * Allow 30-bit DMA क्रम very limited Broadcom wअगरi chips on many
	 * घातerbooks.
	 */
	अगर (IS_ENABLED(CONFIG_PPC32))
		zone_dma_bits = 30;
	अन्यथा
		zone_dma_bits = 31;

#अगर_घोषित CONFIG_ZONE_DMA
	max_zone_pfns[ZONE_DMA]	= min(max_low_pfn,
				      1UL << (zone_dma_bits - PAGE_SHIFT));
#पूर्ण_अगर
	max_zone_pfns[ZONE_NORMAL] = max_low_pfn;
#अगर_घोषित CONFIG_HIGHMEM
	max_zone_pfns[ZONE_HIGHMEM] = max_pfn;
#पूर्ण_अगर

	मुक्त_area_init(max_zone_pfns);

	mark_nonram_nosave();
पूर्ण

व्योम __init mem_init(व्योम)
अणु
	/*
	 * book3s is limited to 16 page sizes due to encoding this in
	 * a 4-bit field क्रम slices.
	 */
	BUILD_BUG_ON(MMU_PAGE_COUNT > 16);

#अगर_घोषित CONFIG_SWIOTLB
	/*
	 * Some platक्रमms (e.g. 85xx) limit DMA-able memory way below
	 * 4G. We क्रमce memblock to bottom-up mode to ensure that the
	 * memory allocated in swiotlb_init() is DMA-able.
	 * As it's the last memblock allocation, no need to reset it
	 * back to to-करोwn.
	 */
	memblock_set_bottom_up(true);
	अगर (is_secure_guest())
		svm_swiotlb_init();
	अन्यथा
		swiotlb_init(0);
#पूर्ण_अगर

	high_memory = (व्योम *) __va(max_low_pfn * PAGE_SIZE);
	set_max_mapnr(max_pfn);

	kasan_late_init();

	memblock_मुक्त_all();

#अगर_घोषित CONFIG_HIGHMEM
	अणु
		अचिन्हित दीर्घ pfn, highmem_mapnr;

		highmem_mapnr = lowmem_end_addr >> PAGE_SHIFT;
		क्रम (pfn = highmem_mapnr; pfn < max_mapnr; ++pfn) अणु
			phys_addr_t paddr = (phys_addr_t)pfn << PAGE_SHIFT;
			काष्ठा page *page = pfn_to_page(pfn);
			अगर (!memblock_is_reserved(paddr))
				मुक्त_highmem_page(page);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_HIGHMEM */

#अगर defined(CONFIG_PPC_FSL_BOOK3E) && !defined(CONFIG_SMP)
	/*
	 * If smp is enabled, next_tlbcam_idx is initialized in the cpu up
	 * functions.... करो it here क्रम the non-smp हाल.
	 */
	per_cpu(next_tlbcam_idx, smp_processor_id()) =
		(mfspr(SPRN_TLB1CFG) & TLBnCFG_N_ENTRY) - 1;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC32
	pr_info("Kernel virtual memory layout:\n");
#अगर_घोषित CONFIG_KASAN
	pr_info("  * 0x%08lx..0x%08lx  : kasan shadow mem\n",
		KASAN_SHADOW_START, KASAN_SHADOW_END);
#पूर्ण_अगर
	pr_info("  * 0x%08lx..0x%08lx  : fixmap\n", FIXADDR_START, FIXADDR_TOP);
#अगर_घोषित CONFIG_HIGHMEM
	pr_info("  * 0x%08lx..0x%08lx  : highmem PTEs\n",
		PKMAP_BASE, PKMAP_ADDR(LAST_PKMAP));
#पूर्ण_अगर /* CONFIG_HIGHMEM */
	अगर (ioremap_bot != IOREMAP_TOP)
		pr_info("  * 0x%08lx..0x%08lx  : early ioremap\n",
			ioremap_bot, IOREMAP_TOP);
	pr_info("  * 0x%08lx..0x%08lx  : vmalloc & ioremap\n",
		VMALLOC_START, VMALLOC_END);
#पूर्ण_अगर /* CONFIG_PPC32 */
पूर्ण

व्योम मुक्त_iniपंचांगem(व्योम)
अणु
	ppc_md.progress = ppc_prपूर्णांकk_progress;
	mark_iniपंचांगem_nx();
	init_mem_is_मुक्त = true;
	मुक्त_iniपंचांगem_शेष(POISON_FREE_INITMEM);
पूर्ण

/*
 * System memory should not be in /proc/iomem but various tools expect it
 * (eg kdump).
 */
अटल पूर्णांक __init add_प्रणाली_ram_resources(व्योम)
अणु
	phys_addr_t start, end;
	u64 i;

	क्रम_each_mem_range(i, &start, &end) अणु
		काष्ठा resource *res;

		res = kzalloc(माप(काष्ठा resource), GFP_KERNEL);
		WARN_ON(!res);

		अगर (res) अणु
			res->name = "System RAM";
			res->start = start;
			/*
			 * In memblock, end poपूर्णांकs to the first byte after
			 * the range जबतक in resourses, end poपूर्णांकs to the
			 * last byte in the range.
			 */
			res->end = end - 1;
			res->flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;
			WARN_ON(request_resource(&iomem_resource, res) < 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(add_प्रणाली_ram_resources);

#अगर_घोषित CONFIG_STRICT_DEVMEM
/*
 * devmem_is_allowed(): check to see अगर /dev/mem access to a certain address
 * is valid. The argument is a physical page number.
 *
 * Access has to be given to non-kernel-ram areas as well, these contain the
 * PCI mmio resources as well as potential bios/acpi data regions.
 */
पूर्णांक devmem_is_allowed(अचिन्हित दीर्घ pfn)
अणु
	अगर (page_is_rtas_user_buf(pfn))
		वापस 1;
	अगर (iomem_is_exclusive(PFN_PHYS(pfn)))
		वापस 0;
	अगर (!page_is_ram(pfn))
		वापस 1;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_STRICT_DEVMEM */

/*
 * This is defined in kernel/resource.c but only घातerpc needs to export it, क्रम
 * the EHEA driver. Drop this when drivers/net/ethernet/ibm/ehea is हटाओd.
 */
EXPORT_SYMBOL_GPL(walk_प्रणाली_ram_range);
