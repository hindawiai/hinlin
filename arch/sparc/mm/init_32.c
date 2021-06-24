<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/sparc/mm/init.c
 *
 *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 *  Copyright (C) 1995 Eddie C. Dost (ecd@skynet.be)
 *  Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 *  Copyright (C) 2000 Anton Blanअक्षरd (anton@samba.org)
 */

#समावेश <linux/module.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/initrd.h>
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/memblock.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/poison.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/vaddrs.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/leon.h>

#समावेश "mm_32.h"

अचिन्हित दीर्घ *sparc_valid_addr_biपंचांगap;
EXPORT_SYMBOL(sparc_valid_addr_biपंचांगap);

अचिन्हित दीर्घ phys_base;
EXPORT_SYMBOL(phys_base);

अचिन्हित दीर्घ pfn_base;
EXPORT_SYMBOL(pfn_base);

काष्ठा sparc_phys_banks sp_banks[SPARC_PHYS_BANKS+1];

/* Initial ramdisk setup */
बाह्य अचिन्हित पूर्णांक sparc_ramdisk_image;
बाह्य अचिन्हित पूर्णांक sparc_ramdisk_size;

अचिन्हित दीर्घ highstart_pfn, highend_pfn;

अचिन्हित दीर्घ last_valid_pfn;

अचिन्हित दीर्घ calc_highpages(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक nr = 0;

	क्रम (i = 0; sp_banks[i].num_bytes != 0; i++) अणु
		अचिन्हित दीर्घ start_pfn = sp_banks[i].base_addr >> PAGE_SHIFT;
		अचिन्हित दीर्घ end_pfn = (sp_banks[i].base_addr + sp_banks[i].num_bytes) >> PAGE_SHIFT;

		अगर (end_pfn <= max_low_pfn)
			जारी;

		अगर (start_pfn < max_low_pfn)
			start_pfn = max_low_pfn;

		nr += end_pfn - start_pfn;
	पूर्ण

	वापस nr;
पूर्ण

अटल अचिन्हित दीर्घ calc_max_low_pfn(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ पंचांगp = pfn_base + (SRMMU_MAXMEM >> PAGE_SHIFT);
	अचिन्हित दीर्घ curr_pfn, last_pfn;

	last_pfn = (sp_banks[0].base_addr + sp_banks[0].num_bytes) >> PAGE_SHIFT;
	क्रम (i = 1; sp_banks[i].num_bytes != 0; i++) अणु
		curr_pfn = sp_banks[i].base_addr >> PAGE_SHIFT;

		अगर (curr_pfn >= पंचांगp) अणु
			अगर (last_pfn < पंचांगp)
				पंचांगp = last_pfn;
			अवरोध;
		पूर्ण

		last_pfn = (sp_banks[i].base_addr + sp_banks[i].num_bytes) >> PAGE_SHIFT;
	पूर्ण

	वापस पंचांगp;
पूर्ण

अटल व्योम __init find_ramdisk(अचिन्हित दीर्घ end_of_phys_memory)
अणु
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अचिन्हित दीर्घ size;

	/* Now have to check initial ramdisk, so that it won't pass
	 * the end of memory
	 */
	अगर (sparc_ramdisk_image) अणु
		अगर (sparc_ramdisk_image >= (अचिन्हित दीर्घ)&_end - 2 * PAGE_SIZE)
			sparc_ramdisk_image -= KERNBASE;
		initrd_start = sparc_ramdisk_image + phys_base;
		initrd_end = initrd_start + sparc_ramdisk_size;
		अगर (initrd_end > end_of_phys_memory) अणु
			prपूर्णांकk(KERN_CRIT "initrd extends beyond end of memory "
			       "(0x%016lx > 0x%016lx)\ndisabling initrd\n",
			       initrd_end, end_of_phys_memory);
			initrd_start = 0;
		पूर्ण अन्यथा अणु
			/* Reserve the initrd image area. */
			size = initrd_end - initrd_start;
			memblock_reserve(initrd_start, size);

			initrd_start = (initrd_start - phys_base) + PAGE_OFFSET;
			initrd_end = (initrd_end - phys_base) + PAGE_OFFSET;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अचिन्हित दीर्घ __init booपंचांगem_init(अचिन्हित दीर्घ *pages_avail)
अणु
	अचिन्हित दीर्घ start_pfn, bytes_avail, size;
	अचिन्हित दीर्घ end_of_phys_memory = 0;
	अचिन्हित दीर्घ high_pages = 0;
	पूर्णांक i;

	memblock_set_bottom_up(true);
	memblock_allow_resize();

	bytes_avail = 0UL;
	क्रम (i = 0; sp_banks[i].num_bytes != 0; i++) अणु
		end_of_phys_memory = sp_banks[i].base_addr +
			sp_banks[i].num_bytes;
		bytes_avail += sp_banks[i].num_bytes;
		अगर (cmdline_memory_size) अणु
			अगर (bytes_avail > cmdline_memory_size) अणु
				अचिन्हित दीर्घ slack = bytes_avail - cmdline_memory_size;

				bytes_avail -= slack;
				end_of_phys_memory -= slack;

				sp_banks[i].num_bytes -= slack;
				अगर (sp_banks[i].num_bytes == 0) अणु
					sp_banks[i].base_addr = 0xdeadbeef;
				पूर्ण अन्यथा अणु
					memblock_add(sp_banks[i].base_addr,
						     sp_banks[i].num_bytes);
					sp_banks[i+1].num_bytes = 0;
					sp_banks[i+1].base_addr = 0xdeadbeef;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		memblock_add(sp_banks[i].base_addr, sp_banks[i].num_bytes);
	पूर्ण

	/* Start with page aligned address of last symbol in kernel
	 * image.
	 */
	start_pfn  = (अचिन्हित दीर्घ)__pa(PAGE_ALIGN((अचिन्हित दीर्घ) &_end));

	/* Now shअगरt करोwn to get the real physical page frame number. */
	start_pfn >>= PAGE_SHIFT;

	max_pfn = end_of_phys_memory >> PAGE_SHIFT;

	max_low_pfn = max_pfn;
	highstart_pfn = highend_pfn = max_pfn;

	अगर (max_low_pfn > pfn_base + (SRMMU_MAXMEM >> PAGE_SHIFT)) अणु
		highstart_pfn = pfn_base + (SRMMU_MAXMEM >> PAGE_SHIFT);
		max_low_pfn = calc_max_low_pfn();
		high_pages = calc_highpages();
		prपूर्णांकk(KERN_NOTICE "%ldMB HIGHMEM available.\n",
		    high_pages >> (20 - PAGE_SHIFT));
	पूर्ण

	find_ramdisk(end_of_phys_memory);

	/* Reserve the kernel text/data/bss. */
	size = (start_pfn << PAGE_SHIFT) - phys_base;
	memblock_reserve(phys_base, size);
	memblock_add(phys_base, size);

	size = memblock_phys_mem_size() - memblock_reserved_size();
	*pages_avail = (size >> PAGE_SHIFT) - high_pages;

	/* Only allow low memory to be allocated via memblock allocation */
	memblock_set_current_limit(max_low_pfn << PAGE_SHIFT);

	वापस max_pfn;
पूर्ण

/*
 * paging_init() sets up the page tables: We call the MMU specअगरic
 * init routine based upon the Sun model type on the Sparc.
 *
 */
व्योम __init paging_init(व्योम)
अणु
	srmmu_paging_init();
	prom_build_devicetree();
	of_fill_in_cpu_data();
	device_scan();
पूर्ण

अटल व्योम __init taपूर्णांक_real_pages(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; sp_banks[i].num_bytes; i++) अणु
		अचिन्हित दीर्घ start, end;

		start = sp_banks[i].base_addr;
		end = start + sp_banks[i].num_bytes;

		जबतक (start < end) अणु
			set_bit(start >> 20, sparc_valid_addr_biपंचांगap);
			start += PAGE_SIZE;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम map_high_region(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ पंचांगp;

#अगर_घोषित CONFIG_DEBUG_HIGHMEM
	prपूर्णांकk("mapping high region %08lx - %08lx\n", start_pfn, end_pfn);
#पूर्ण_अगर

	क्रम (पंचांगp = start_pfn; पंचांगp < end_pfn; पंचांगp++)
		मुक्त_highmem_page(pfn_to_page(पंचांगp));
पूर्ण

व्योम __init mem_init(व्योम)
अणु
	पूर्णांक i;

	अगर (PKMAP_BASE+LAST_PKMAP*PAGE_SIZE >= FIXADDR_START) अणु
		prom_म_लिखो("BUG: fixmap and pkmap areas overlap\n");
		prom_म_लिखो("pkbase: 0x%lx pkend: 0x%lx fixstart 0x%lx\n",
		       PKMAP_BASE,
		       (अचिन्हित दीर्घ)PKMAP_BASE+LAST_PKMAP*PAGE_SIZE,
		       FIXADDR_START);
		prom_म_लिखो("Please mail sparclinux@vger.kernel.org.\n");
		prom_halt();
	पूर्ण


	/* Saves us work later. */
	स_रखो((व्योम *)empty_zero_page, 0, PAGE_SIZE);

	i = last_valid_pfn >> ((20 - PAGE_SHIFT) + 5);
	i += 1;
	sparc_valid_addr_biपंचांगap = (अचिन्हित दीर्घ *)
		memblock_alloc(i << 2, SMP_CACHE_BYTES);

	अगर (sparc_valid_addr_biपंचांगap == शून्य) अणु
		prom_म_लिखो("mem_init: Cannot alloc valid_addr_bitmap.\n");
		prom_halt();
	पूर्ण
	स_रखो(sparc_valid_addr_biपंचांगap, 0, i << 2);

	taपूर्णांक_real_pages();

	max_mapnr = last_valid_pfn - pfn_base;
	high_memory = __va(max_low_pfn << PAGE_SHIFT);
	memblock_मुक्त_all();

	क्रम (i = 0; sp_banks[i].num_bytes != 0; i++) अणु
		अचिन्हित दीर्घ start_pfn = sp_banks[i].base_addr >> PAGE_SHIFT;
		अचिन्हित दीर्घ end_pfn = (sp_banks[i].base_addr + sp_banks[i].num_bytes) >> PAGE_SHIFT;

		अगर (end_pfn <= highstart_pfn)
			जारी;

		अगर (start_pfn < highstart_pfn)
			start_pfn = highstart_pfn;

		map_high_region(start_pfn, end_pfn);
	पूर्ण
पूर्ण

व्योम sparc_flush_page_to_ram(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)page_address(page);

	अगर (vaddr)
		__flush_page_to_ram(vaddr);
पूर्ण
EXPORT_SYMBOL(sparc_flush_page_to_ram);
