<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/parisc/mm/init.c
 *
 *  Copyright (C) 1995	Linus Torvalds
 *  Copyright 1999 SuSE GmbH
 *    changed by Philipp Rumpf
 *  Copyright 1999 Philipp Rumpf (prumpf@tux.org)
 *  Copyright 2004 Ranकरोlph Chung (tausq@debian.org)
 *  Copyright 2006-2007 Helge Deller (deller@gmx.de)
 *
 */


#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/gfp.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/initrd.h>
#समावेश <linux/swap.h>
#समावेश <linux/unistd.h>
#समावेश <linux/nodemask.h>	/* क्रम node_online_map */
#समावेश <linux/pagemap.h>	/* क्रम release_pages */
#समावेश <linux/compat.h>

#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/pdc_chassis.h>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/msgbuf.h>
#समावेश <यंत्र/sparseस्मृति.स>

बाह्य पूर्णांक  data_start;
बाह्य व्योम parisc_kernel_start(व्योम);	/* Kernel entry poपूर्णांक in head.S */

#अगर CONFIG_PGTABLE_LEVELS == 3
pmd_t pmd0[PTRS_PER_PMD] __section(".data..vm0.pmd") __attribute__ ((aligned(PAGE_SIZE)));
#पूर्ण_अगर

pgd_t swapper_pg_dir[PTRS_PER_PGD] __section(".data..vm0.pgd") __attribute__ ((aligned(PAGE_SIZE)));
pte_t pg0[PT_INITIAL * PTRS_PER_PTE] __section(".data..vm0.pte") __attribute__ ((aligned(PAGE_SIZE)));

अटल काष्ठा resource data_resource = अणु
	.name	= "Kernel data",
	.flags	= IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM,
पूर्ण;

अटल काष्ठा resource code_resource = अणु
	.name	= "Kernel code",
	.flags	= IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM,
पूर्ण;

अटल काष्ठा resource pdcdata_resource = अणु
	.name	= "PDC data (Page Zero)",
	.start	= 0,
	.end	= 0x9ff,
	.flags	= IORESOURCE_BUSY | IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource sysram_resources[MAX_PHYSMEM_RANGES] __ro_after_init;

/* The following array is initialized from the firmware specअगरic
 * inक्रमmation retrieved in kernel/inventory.c.
 */

physmem_range_t pmem_ranges[MAX_PHYSMEM_RANGES] __initdata;
पूर्णांक npmem_ranges __initdata;

#अगर_घोषित CONFIG_64BIT
#घोषणा MAX_MEM         (1UL << MAX_PHYSMEM_BITS)
#अन्यथा /* !CONFIG_64BIT */
#घोषणा MAX_MEM         (3584U*1024U*1024U)
#पूर्ण_अगर /* !CONFIG_64BIT */

अटल अचिन्हित दीर्घ mem_limit __पढ़ो_mostly = MAX_MEM;

अटल व्योम __init mem_limit_func(व्योम)
अणु
	अक्षर *cp, *end;
	अचिन्हित दीर्घ limit;

	/* We need this beक्रमe __setup() functions are called */

	limit = MAX_MEM;
	क्रम (cp = boot_command_line; *cp; ) अणु
		अगर (स_भेद(cp, "mem=", 4) == 0) अणु
			cp += 4;
			limit = memparse(cp, &end);
			अगर (end != cp)
				अवरोध;
			cp = end;
		पूर्ण अन्यथा अणु
			जबतक (*cp != ' ' && *cp)
				++cp;
			जबतक (*cp == ' ')
				++cp;
		पूर्ण
	पूर्ण

	अगर (limit < mem_limit)
		mem_limit = limit;
पूर्ण

#घोषणा MAX_GAP (0x40000000UL >> PAGE_SHIFT)

अटल व्योम __init setup_booपंचांगem(व्योम)
अणु
	अचिन्हित दीर्घ mem_max;
#अगर_अघोषित CONFIG_SPARSEMEM
	physmem_range_t pmem_holes[MAX_PHYSMEM_RANGES - 1];
	पूर्णांक npmem_holes;
#पूर्ण_अगर
	पूर्णांक i, sysram_resource_count;

	disable_sr_hashing(); /* Turn off space रेजिस्टर hashing */

	/*
	 * Sort the ranges. Since the number of ranges is typically
	 * small, and perक्रमmance is not an issue here, just करो
	 * a simple insertion sort.
	 */

	क्रम (i = 1; i < npmem_ranges; i++) अणु
		पूर्णांक j;

		क्रम (j = i; j > 0; j--) अणु
			physmem_range_t पंचांगp;

			अगर (pmem_ranges[j-1].start_pfn <
			    pmem_ranges[j].start_pfn) अणु

				अवरोध;
			पूर्ण
			पंचांगp = pmem_ranges[j-1];
			pmem_ranges[j-1] = pmem_ranges[j];
			pmem_ranges[j] = पंचांगp;
		पूर्ण
	पूर्ण

#अगर_अघोषित CONFIG_SPARSEMEM
	/*
	 * Throw out ranges that are too far apart (controlled by
	 * MAX_GAP).
	 */

	क्रम (i = 1; i < npmem_ranges; i++) अणु
		अगर (pmem_ranges[i].start_pfn -
			(pmem_ranges[i-1].start_pfn +
			 pmem_ranges[i-1].pages) > MAX_GAP) अणु
			npmem_ranges = i;
			prपूर्णांकk("Large gap in memory detected (%ld pages). "
			       "Consider turning on CONFIG_SPARSEMEM\n",
			       pmem_ranges[i].start_pfn -
			       (pmem_ranges[i-1].start_pfn +
			        pmem_ranges[i-1].pages));
			अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Prपूर्णांक the memory ranges */
	pr_info("Memory Ranges:\n");

	क्रम (i = 0; i < npmem_ranges; i++) अणु
		काष्ठा resource *res = &sysram_resources[i];
		अचिन्हित दीर्घ start;
		अचिन्हित दीर्घ size;

		size = (pmem_ranges[i].pages << PAGE_SHIFT);
		start = (pmem_ranges[i].start_pfn << PAGE_SHIFT);
		pr_info("%2d) Start 0x%016lx End 0x%016lx Size %6ld MB\n",
			i, start, start + (size - 1), size >> 20);

		/* request memory resource */
		res->name = "System RAM";
		res->start = start;
		res->end = start + size - 1;
		res->flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;
		request_resource(&iomem_resource, res);
	पूर्ण

	sysram_resource_count = npmem_ranges;

	/*
	 * For 32 bit kernels we limit the amount of memory we can
	 * support, in order to preserve enough kernel address space
	 * क्रम other purposes. For 64 bit kernels we करोn't normally
	 * limit the memory, but this mechanism can be used to
	 * artअगरicially limit the amount of memory (and it is written
	 * to work with multiple memory ranges).
	 */

	mem_limit_func();       /* check क्रम "mem=" argument */

	mem_max = 0;
	क्रम (i = 0; i < npmem_ranges; i++) अणु
		अचिन्हित दीर्घ rsize;

		rsize = pmem_ranges[i].pages << PAGE_SHIFT;
		अगर ((mem_max + rsize) > mem_limit) अणु
			prपूर्णांकk(KERN_WARNING "Memory truncated to %ld MB\n", mem_limit >> 20);
			अगर (mem_max == mem_limit)
				npmem_ranges = i;
			अन्यथा अणु
				pmem_ranges[i].pages =   (mem_limit >> PAGE_SHIFT)
						       - (mem_max >> PAGE_SHIFT);
				npmem_ranges = i + 1;
				mem_max = mem_limit;
			पूर्ण
			अवरोध;
		पूर्ण
		mem_max += rsize;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Total Memory: %ld MB\n",mem_max >> 20);

#अगर_अघोषित CONFIG_SPARSEMEM
	/* Merge the ranges, keeping track of the holes */
	अणु
		अचिन्हित दीर्घ end_pfn;
		अचिन्हित दीर्घ hole_pages;

		npmem_holes = 0;
		end_pfn = pmem_ranges[0].start_pfn + pmem_ranges[0].pages;
		क्रम (i = 1; i < npmem_ranges; i++) अणु

			hole_pages = pmem_ranges[i].start_pfn - end_pfn;
			अगर (hole_pages) अणु
				pmem_holes[npmem_holes].start_pfn = end_pfn;
				pmem_holes[npmem_holes++].pages = hole_pages;
				end_pfn += hole_pages;
			पूर्ण
			end_pfn += pmem_ranges[i].pages;
		पूर्ण

		pmem_ranges[0].pages = end_pfn - pmem_ranges[0].start_pfn;
		npmem_ranges = 1;
	पूर्ण
#पूर्ण_अगर

	/*
	 * Initialize and मुक्त the full range of memory in each range.
	 */

	max_pfn = 0;
	क्रम (i = 0; i < npmem_ranges; i++) अणु
		अचिन्हित दीर्घ start_pfn;
		अचिन्हित दीर्घ npages;
		अचिन्हित दीर्घ start;
		अचिन्हित दीर्घ size;

		start_pfn = pmem_ranges[i].start_pfn;
		npages = pmem_ranges[i].pages;

		start = start_pfn << PAGE_SHIFT;
		size = npages << PAGE_SHIFT;

		/* add प्रणाली RAM memblock */
		memblock_add(start, size);

		अगर ((start_pfn + npages) > max_pfn)
			max_pfn = start_pfn + npages;
	पूर्ण

	/*
	 * We can't use memblock top-करोwn allocations because we only
	 * created the initial mapping up to KERNEL_INITIAL_SIZE in
	 * the assembly bootup code.
	 */
	memblock_set_bottom_up(true);

	/* IOMMU is always used to access "high mem" on those boxes
	 * that can support enough mem that a PCI device couldn't
	 * directly DMA to any physical addresses.
	 * ISA DMA support will need to revisit this.
	 */
	max_low_pfn = max_pfn;

	/* reserve PAGE0 pdc memory, kernel text/data/bss & booपंचांगap */

#घोषणा PDC_CONSOLE_IO_IODC_SIZE 32768

	memblock_reserve(0UL, (अचिन्हित दीर्घ)(PAGE0->mem_मुक्त +
				PDC_CONSOLE_IO_IODC_SIZE));
	memblock_reserve(__pa(KERNEL_BINARY_TEXT_START),
			(अचिन्हित दीर्घ)(_end - KERNEL_BINARY_TEXT_START));

#अगर_अघोषित CONFIG_SPARSEMEM

	/* reserve the holes */

	क्रम (i = 0; i < npmem_holes; i++) अणु
		memblock_reserve((pmem_holes[i].start_pfn << PAGE_SHIFT),
				(pmem_holes[i].pages << PAGE_SHIFT));
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (initrd_start) अणु
		prपूर्णांकk(KERN_INFO "initrd: %08lx-%08lx\n", initrd_start, initrd_end);
		अगर (__pa(initrd_start) < mem_max) अणु
			अचिन्हित दीर्घ initrd_reserve;

			अगर (__pa(initrd_end) > mem_max) अणु
				initrd_reserve = mem_max - __pa(initrd_start);
			पूर्ण अन्यथा अणु
				initrd_reserve = initrd_end - initrd_start;
			पूर्ण
			initrd_below_start_ok = 1;
			prपूर्णांकk(KERN_INFO "initrd: reserving %08lx-%08lx (mem_max %08lx)\n", __pa(initrd_start), __pa(initrd_start) + initrd_reserve, mem_max);

			memblock_reserve(__pa(initrd_start), initrd_reserve);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	data_resource.start =  virt_to_phys(&data_start);
	data_resource.end = virt_to_phys(_end) - 1;
	code_resource.start = virt_to_phys(_text);
	code_resource.end = virt_to_phys(&data_start)-1;

	/* We करोn't know which region the kernel will be in, so try
	 * all of them.
	 */
	क्रम (i = 0; i < sysram_resource_count; i++) अणु
		काष्ठा resource *res = &sysram_resources[i];
		request_resource(res, &code_resource);
		request_resource(res, &data_resource);
	पूर्ण
	request_resource(&sysram_resources[0], &pdcdata_resource);

	/* Initialize Page Deallocation Table (PDT) and check क्रम bad memory. */
	pdc_pdt_init();

	memblock_allow_resize();
	memblock_dump_all();
पूर्ण

अटल bool kernel_set_to_पढ़ोonly;

अटल व्योम __init map_pages(अचिन्हित दीर्घ start_vaddr,
			     अचिन्हित दीर्घ start_paddr, अचिन्हित दीर्घ size,
			     pgprot_t pgprot, पूर्णांक क्रमce)
अणु
	pmd_t *pmd;
	pte_t *pg_table;
	अचिन्हित दीर्घ end_paddr;
	अचिन्हित दीर्घ start_pmd;
	अचिन्हित दीर्घ start_pte;
	अचिन्हित दीर्घ पंचांगp1;
	अचिन्हित दीर्घ पंचांगp2;
	अचिन्हित दीर्घ address;
	अचिन्हित दीर्घ vaddr;
	अचिन्हित दीर्घ ro_start;
	अचिन्हित दीर्घ ro_end;
	अचिन्हित दीर्घ kernel_start, kernel_end;

	ro_start = __pa((अचिन्हित दीर्घ)_text);
	ro_end   = __pa((अचिन्हित दीर्घ)&data_start);
	kernel_start = __pa((अचिन्हित दीर्घ)&__init_begin);
	kernel_end  = __pa((अचिन्हित दीर्घ)&_end);

	end_paddr = start_paddr + size;

	/* क्रम 2-level configuration PTRS_PER_PMD is 0 so start_pmd will be 0 */
	start_pmd = ((start_vaddr >> PMD_SHIFT) & (PTRS_PER_PMD - 1));
	start_pte = ((start_vaddr >> PAGE_SHIFT) & (PTRS_PER_PTE - 1));

	address = start_paddr;
	vaddr = start_vaddr;
	जबतक (address < end_paddr) अणु
		pgd_t *pgd = pgd_offset_k(vaddr);
		p4d_t *p4d = p4d_offset(pgd, vaddr);
		pud_t *pud = pud_offset(p4d, vaddr);

#अगर CONFIG_PGTABLE_LEVELS == 3
		अगर (pud_none(*pud)) अणु
			pmd = memblock_alloc(PAGE_SIZE << PMD_ORDER,
					     PAGE_SIZE << PMD_ORDER);
			अगर (!pmd)
				panic("pmd allocation failed.\n");
			pud_populate(शून्य, pud, pmd);
		पूर्ण
#पूर्ण_अगर

		pmd = pmd_offset(pud, vaddr);
		क्रम (पंचांगp1 = start_pmd; पंचांगp1 < PTRS_PER_PMD; पंचांगp1++, pmd++) अणु
			अगर (pmd_none(*pmd)) अणु
				pg_table = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
				अगर (!pg_table)
					panic("page table allocation failed\n");
				pmd_populate_kernel(शून्य, pmd, pg_table);
			पूर्ण

			pg_table = pte_offset_kernel(pmd, vaddr);
			क्रम (पंचांगp2 = start_pte; पंचांगp2 < PTRS_PER_PTE; पंचांगp2++, pg_table++) अणु
				pte_t pte;
				pgprot_t prot;
				bool huge = false;

				अगर (क्रमce) अणु
					prot = pgprot;
				पूर्ण अन्यथा अगर (address < kernel_start || address >= kernel_end) अणु
					/* outside kernel memory */
					prot = PAGE_KERNEL;
				पूर्ण अन्यथा अगर (!kernel_set_to_पढ़ोonly) अणु
					/* still initializing, allow writing to RO memory */
					prot = PAGE_KERNEL_RWX;
					huge = true;
				पूर्ण अन्यथा अगर (address >= ro_start) अणु
					/* Code (ro) and Data areas */
					prot = (address < ro_end) ?
						PAGE_KERNEL_EXEC : PAGE_KERNEL;
					huge = true;
				पूर्ण अन्यथा अणु
					prot = PAGE_KERNEL;
				पूर्ण

				pte = __mk_pte(address, prot);
				अगर (huge)
					pte = pte_mkhuge(pte);

				अगर (address >= end_paddr)
					अवरोध;

				set_pte(pg_table, pte);

				address += PAGE_SIZE;
				vaddr += PAGE_SIZE;
			पूर्ण
			start_pte = 0;

			अगर (address >= end_paddr)
			    अवरोध;
		पूर्ण
		start_pmd = 0;
	पूर्ण
पूर्ण

व्योम __init set_kernel_text_rw(पूर्णांक enable_पढ़ो_ग_लिखो)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ) __init_begin;
	अचिन्हित दीर्घ end   = (अचिन्हित दीर्घ) &data_start;

	map_pages(start, __pa(start), end-start,
		PAGE_KERNEL_RWX, enable_पढ़ो_ग_लिखो ? 1:0);

	/* क्रमce the kernel to see the new page table entries */
	flush_cache_all();
	flush_tlb_all();
पूर्ण

व्योम __ref मुक्त_iniपंचांगem(व्योम)
अणु
	अचिन्हित दीर्घ init_begin = (अचिन्हित दीर्घ)__init_begin;
	अचिन्हित दीर्घ init_end = (अचिन्हित दीर्घ)__init_end;
	अचिन्हित दीर्घ kernel_end  = (अचिन्हित दीर्घ)&_end;

	/* Remap kernel text and data, but करो not touch init section yet. */
	kernel_set_to_पढ़ोonly = true;
	map_pages(init_end, __pa(init_end), kernel_end - init_end,
		  PAGE_KERNEL, 0);

	/* The init text pages are marked R-X.  We have to
	 * flush the icache and mark them RW-
	 *
	 * This is tricky, because map_pages is in the init section.
	 * Do a dummy remap of the data section first (the data
	 * section is alपढ़ोy PAGE_KERNEL) to pull in the TLB entries
	 * क्रम map_kernel */
	map_pages(init_begin, __pa(init_begin), init_end - init_begin,
		  PAGE_KERNEL_RWX, 1);
	/* now remap at PAGE_KERNEL since the TLB is pre-primed to execute
	 * map_pages */
	map_pages(init_begin, __pa(init_begin), init_end - init_begin,
		  PAGE_KERNEL, 1);

	/* क्रमce the kernel to see the new TLB entries */
	__flush_tlb_range(0, init_begin, kernel_end);

	/* finally dump all the inकाष्ठाions which were cached, since the
	 * pages are no-दीर्घer executable */
	flush_icache_range(init_begin, init_end);
	
	मुक्त_iniपंचांगem_शेष(POISON_FREE_INITMEM);

	/* set up a new led state on प्रणालीs shipped LED State panel */
	pdc_chassis_send_status(PDC_CHASSIS_सूचीECT_BCOMPLETE);
पूर्ण


#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
व्योम mark_rodata_ro(व्योम)
अणु
	/* rodata memory was alपढ़ोy mapped with KERNEL_RO access rights by
           pagetable_init() and map_pages(). No need to करो additional stuff here */
	अचिन्हित दीर्घ roai_size = __end_ro_after_init - __start_ro_after_init;

	pr_info("Write protected read-only-after-init data: %luk\n", roai_size >> 10);
पूर्ण
#पूर्ण_अगर


/*
 * Just an arbitrary offset to serve as a "hole" between mapping areas
 * (between top of physical memory and a potential pcxl dma mapping
 * area, and below the vदो_स्मृति mapping area).
 *
 * The current 32K value just means that there will be a 32K "hole"
 * between mapping areas. That means that  any out-of-bounds memory
 * accesses will hopefully be caught. The vदो_स्मृति() routines leaves
 * a hole of 4kB between each vदो_स्मृतिed area क्रम the same reason.
 */

 /* Leave room क्रम gateway page expansion */
#अगर KERNEL_MAP_START < GATEWAY_PAGE_SIZE
#त्रुटि KERNEL_MAP_START is in gateway reserved region
#पूर्ण_अगर
#घोषणा MAP_START (KERNEL_MAP_START)

#घोषणा VM_MAP_OFFSET  (32*1024)
#घोषणा SET_MAP_OFFSET(x) ((व्योम *)(((अचिन्हित दीर्घ)(x) + VM_MAP_OFFSET) \
				     & ~(VM_MAP_OFFSET-1)))

व्योम *parisc_vदो_स्मृति_start __ro_after_init;
EXPORT_SYMBOL(parisc_vदो_स्मृति_start);

#अगर_घोषित CONFIG_PA11
अचिन्हित दीर्घ pcxl_dma_start __ro_after_init;
#पूर्ण_अगर

व्योम __init mem_init(व्योम)
अणु
	/* Do sanity checks on IPC (compat) काष्ठाures */
	BUILD_BUG_ON(माप(काष्ठा ipc64_perm) != 48);
#अगर_अघोषित CONFIG_64BIT
	BUILD_BUG_ON(माप(काष्ठा semid64_ds) != 80);
	BUILD_BUG_ON(माप(काष्ठा msqid64_ds) != 104);
	BUILD_BUG_ON(माप(काष्ठा shmid64_ds) != 104);
#पूर्ण_अगर
#अगर_घोषित CONFIG_COMPAT
	BUILD_BUG_ON(माप(काष्ठा compat_ipc64_perm) != माप(काष्ठा ipc64_perm));
	BUILD_BUG_ON(माप(काष्ठा compat_semid64_ds) != 80);
	BUILD_BUG_ON(माप(काष्ठा compat_msqid64_ds) != 104);
	BUILD_BUG_ON(माप(काष्ठा compat_shmid64_ds) != 104);
#पूर्ण_अगर

	/* Do sanity checks on page table स्थिरants */
	BUILD_BUG_ON(PTE_ENTRY_SIZE != माप(pte_t));
	BUILD_BUG_ON(PMD_ENTRY_SIZE != माप(pmd_t));
	BUILD_BUG_ON(PGD_ENTRY_SIZE != माप(pgd_t));
	BUILD_BUG_ON(PAGE_SHIFT + BITS_PER_PTE + BITS_PER_PMD + BITS_PER_PGD
			> BITS_PER_LONG);
#अगर CONFIG_PGTABLE_LEVELS == 3
	BUILD_BUG_ON(PT_INITIAL > PTRS_PER_PMD);
#अन्यथा
	BUILD_BUG_ON(PT_INITIAL > PTRS_PER_PGD);
#पूर्ण_अगर

	high_memory = __va((max_pfn << PAGE_SHIFT));
	set_max_mapnr(max_low_pfn);
	memblock_मुक्त_all();

#अगर_घोषित CONFIG_PA11
	अगर (boot_cpu_data.cpu_type == pcxl2 || boot_cpu_data.cpu_type == pcxl) अणु
		pcxl_dma_start = (अचिन्हित दीर्घ)SET_MAP_OFFSET(MAP_START);
		parisc_vदो_स्मृति_start = SET_MAP_OFFSET(pcxl_dma_start
						+ PCXL_DMA_MAP_SIZE);
	पूर्ण अन्यथा
#पूर्ण_अगर
		parisc_vदो_स्मृति_start = SET_MAP_OFFSET(MAP_START);

#अगर 0
	/*
	 * Do not expose the भव kernel memory layout to userspace.
	 * But keep code क्रम debugging purposes.
	 */
	prपूर्णांकk("virtual kernel memory layout:\n"
	       "     vmalloc : 0x%px - 0x%px   (%4ld MB)\n"
	       "     fixmap  : 0x%px - 0x%px   (%4ld kB)\n"
	       "     memory  : 0x%px - 0x%px   (%4ld MB)\n"
	       "       .init : 0x%px - 0x%px   (%4ld kB)\n"
	       "       .data : 0x%px - 0x%px   (%4ld kB)\n"
	       "       .text : 0x%px - 0x%px   (%4ld kB)\n",

	       (व्योम*)VMALLOC_START, (व्योम*)VMALLOC_END,
	       (VMALLOC_END - VMALLOC_START) >> 20,

	       (व्योम *)FIXMAP_START, (व्योम *)(FIXMAP_START + FIXMAP_SIZE),
	       (अचिन्हित दीर्घ)(FIXMAP_SIZE / 1024),

	       __va(0), high_memory,
	       ((अचिन्हित दीर्घ)high_memory - (अचिन्हित दीर्घ)__va(0)) >> 20,

	       __init_begin, __init_end,
	       ((अचिन्हित दीर्घ)__init_end - (अचिन्हित दीर्घ)__init_begin) >> 10,

	       _etext, _edata,
	       ((अचिन्हित दीर्घ)_edata - (अचिन्हित दीर्घ)_etext) >> 10,

	       _text, _etext,
	       ((अचिन्हित दीर्घ)_etext - (अचिन्हित दीर्घ)_text) >> 10);
#पूर्ण_अगर
पूर्ण

अचिन्हित दीर्घ *empty_zero_page __ro_after_init;
EXPORT_SYMBOL(empty_zero_page);

/*
 * pagetable_init() sets up the page tables
 *
 * Note that gateway_init() places the Linux gateway page at page 0.
 * Since gateway pages cannot be dereferenced this has the desirable
 * side effect of trapping those pesky शून्य-reference errors in the
 * kernel.
 */
अटल व्योम __init pagetable_init(व्योम)
अणु
	पूर्णांक range;

	/* Map each physical memory range to its kernel vaddr */

	क्रम (range = 0; range < npmem_ranges; range++) अणु
		अचिन्हित दीर्घ start_paddr;
		अचिन्हित दीर्घ end_paddr;
		अचिन्हित दीर्घ size;

		start_paddr = pmem_ranges[range].start_pfn << PAGE_SHIFT;
		size = pmem_ranges[range].pages << PAGE_SHIFT;
		end_paddr = start_paddr + size;

		map_pages((अचिन्हित दीर्घ)__va(start_paddr), start_paddr,
			  size, PAGE_KERNEL, 0);
	पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (initrd_end && initrd_end > mem_limit) अणु
		prपूर्णांकk(KERN_INFO "initrd: mapping %08lx-%08lx\n", initrd_start, initrd_end);
		map_pages(initrd_start, __pa(initrd_start),
			  initrd_end - initrd_start, PAGE_KERNEL, 0);
	पूर्ण
#पूर्ण_अगर

	empty_zero_page = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
	अगर (!empty_zero_page)
		panic("zero page allocation failed.\n");

पूर्ण

अटल व्योम __init gateway_init(व्योम)
अणु
	अचिन्हित दीर्घ linux_gateway_page_addr;
	/* FIXME: This is 'const' in order to trick the compiler
	   पूर्णांकo not treating it as DP-relative data. */
	बाह्य व्योम * स्थिर linux_gateway_page;

	linux_gateway_page_addr = LINUX_GATEWAY_ADDR & PAGE_MASK;

	/*
	 * Setup Linux Gateway page.
	 *
	 * The Linux gateway page will reside in kernel space (on भव
	 * page 0), so it करोesn't need to be aliased पूर्णांकo user space.
	 */

	map_pages(linux_gateway_page_addr, __pa(&linux_gateway_page),
		  PAGE_SIZE, PAGE_GATEWAY, 1);
पूर्ण

अटल व्योम __init parisc_booपंचांगem_मुक्त(व्योम)
अणु
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु 0, पूर्ण;

	max_zone_pfn[0] = memblock_end_of_DRAM();

	मुक्त_area_init(max_zone_pfn);
पूर्ण

व्योम __init paging_init(व्योम)
अणु
	setup_booपंचांगem();
	pagetable_init();
	gateway_init();
	flush_cache_all_local(); /* start with known state */
	flush_tlb_all_local(शून्य);

	sparse_init();
	parisc_booपंचांगem_मुक्त();
पूर्ण

#अगर_घोषित CONFIG_PA20

/*
 * Currently, all PA20 chips have 18 bit protection IDs, which is the
 * limiting factor (space ids are 32 bits).
 */

#घोषणा NR_SPACE_IDS 262144

#अन्यथा

/*
 * Currently we have a one-to-one relationship between space IDs and
 * protection IDs. Older parisc chips (PCXS, PCXT, PCXL, PCXL2) only
 * support 15 bit protection IDs, so that is the limiting factor.
 * PCXT' has 18 bit protection IDs, but only 16 bit spaceids, so it's
 * probably not worth the efक्रमt क्रम a special हाल here.
 */

#घोषणा NR_SPACE_IDS 32768

#पूर्ण_अगर  /* !CONFIG_PA20 */

#घोषणा RECYCLE_THRESHOLD (NR_SPACE_IDS / 2)
#घोषणा SID_ARRAY_SIZE  (NR_SPACE_IDS / (8 * माप(दीर्घ)))

अटल अचिन्हित दीर्घ space_id[SID_ARRAY_SIZE] = अणु 1 पूर्ण; /* disallow space 0 */
अटल अचिन्हित दीर्घ dirty_space_id[SID_ARRAY_SIZE];
अटल अचिन्हित दीर्घ space_id_index;
अटल अचिन्हित दीर्घ मुक्त_space_ids = NR_SPACE_IDS - 1;
अटल अचिन्हित दीर्घ dirty_space_ids = 0;

अटल DEFINE_SPINLOCK(sid_lock);

अचिन्हित दीर्घ alloc_sid(व्योम)
अणु
	अचिन्हित दीर्घ index;

	spin_lock(&sid_lock);

	अगर (मुक्त_space_ids == 0) अणु
		अगर (dirty_space_ids != 0) अणु
			spin_unlock(&sid_lock);
			flush_tlb_all(); /* flush_tlb_all() calls recycle_sids() */
			spin_lock(&sid_lock);
		पूर्ण
		BUG_ON(मुक्त_space_ids == 0);
	पूर्ण

	मुक्त_space_ids--;

	index = find_next_zero_bit(space_id, NR_SPACE_IDS, space_id_index);
	space_id[BIT_WORD(index)] |= BIT_MASK(index);
	space_id_index = index;

	spin_unlock(&sid_lock);

	वापस index << SPACEID_SHIFT;
पूर्ण

व्योम मुक्त_sid(अचिन्हित दीर्घ spaceid)
अणु
	अचिन्हित दीर्घ index = spaceid >> SPACEID_SHIFT;
	अचिन्हित दीर्घ *dirty_space_offset, mask;

	dirty_space_offset = &dirty_space_id[BIT_WORD(index)];
	mask = BIT_MASK(index);

	spin_lock(&sid_lock);

	BUG_ON(*dirty_space_offset & mask); /* attempt to मुक्त space id twice */

	*dirty_space_offset |= mask;
	dirty_space_ids++;

	spin_unlock(&sid_lock);
पूर्ण


#अगर_घोषित CONFIG_SMP
अटल व्योम get_dirty_sids(अचिन्हित दीर्घ *ndirtyptr,अचिन्हित दीर्घ *dirty_array)
अणु
	पूर्णांक i;

	/* NOTE: sid_lock must be held upon entry */

	*ndirtyptr = dirty_space_ids;
	अगर (dirty_space_ids != 0) अणु
	    क्रम (i = 0; i < SID_ARRAY_SIZE; i++) अणु
		dirty_array[i] = dirty_space_id[i];
		dirty_space_id[i] = 0;
	    पूर्ण
	    dirty_space_ids = 0;
	पूर्ण

	वापस;
पूर्ण

अटल व्योम recycle_sids(अचिन्हित दीर्घ ndirty,अचिन्हित दीर्घ *dirty_array)
अणु
	पूर्णांक i;

	/* NOTE: sid_lock must be held upon entry */

	अगर (ndirty != 0) अणु
		क्रम (i = 0; i < SID_ARRAY_SIZE; i++) अणु
			space_id[i] ^= dirty_array[i];
		पूर्ण

		मुक्त_space_ids += ndirty;
		space_id_index = 0;
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_SMP */

अटल व्योम recycle_sids(व्योम)
अणु
	पूर्णांक i;

	/* NOTE: sid_lock must be held upon entry */

	अगर (dirty_space_ids != 0) अणु
		क्रम (i = 0; i < SID_ARRAY_SIZE; i++) अणु
			space_id[i] ^= dirty_space_id[i];
			dirty_space_id[i] = 0;
		पूर्ण

		मुक्त_space_ids += dirty_space_ids;
		dirty_space_ids = 0;
		space_id_index = 0;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * flush_tlb_all() calls recycle_sids(), since whenever the entire tlb is
 * purged, we can safely reuse the space ids that were released but
 * not flushed from the tlb.
 */

#अगर_घोषित CONFIG_SMP

अटल अचिन्हित दीर्घ recycle_ndirty;
अटल अचिन्हित दीर्घ recycle_dirty_array[SID_ARRAY_SIZE];
अटल अचिन्हित पूर्णांक recycle_inuse;

व्योम flush_tlb_all(व्योम)
अणु
	पूर्णांक करो_recycle;

	__inc_irq_stat(irq_tlb_count);
	करो_recycle = 0;
	spin_lock(&sid_lock);
	अगर (dirty_space_ids > RECYCLE_THRESHOLD) अणु
	    BUG_ON(recycle_inuse);  /* FIXME: Use a semaphore/रुको queue here */
	    get_dirty_sids(&recycle_ndirty,recycle_dirty_array);
	    recycle_inuse++;
	    करो_recycle++;
	पूर्ण
	spin_unlock(&sid_lock);
	on_each_cpu(flush_tlb_all_local, शून्य, 1);
	अगर (करो_recycle) अणु
	    spin_lock(&sid_lock);
	    recycle_sids(recycle_ndirty,recycle_dirty_array);
	    recycle_inuse = 0;
	    spin_unlock(&sid_lock);
	पूर्ण
पूर्ण
#अन्यथा
व्योम flush_tlb_all(व्योम)
अणु
	__inc_irq_stat(irq_tlb_count);
	spin_lock(&sid_lock);
	flush_tlb_all_local(शून्य);
	recycle_sids();
	spin_unlock(&sid_lock);
पूर्ण
#पूर्ण_अगर
