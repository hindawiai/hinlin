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

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/initrd.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/memblock.h>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/hugetlb.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/btext.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/hugetlb.h>
#समावेश <यंत्र/kup.h>
#समावेश <यंत्र/kasan.h>

#समावेश <mm/mmu_decl.h>

#अगर defined(CONFIG_KERNEL_START_BOOL) || defined(CONFIG_LOWMEM_SIZE_BOOL)
/* The amount of lowmem must be within 0xF0000000 - KERNELBASE. */
#अगर (CONFIG_LOWMEM_SIZE > (0xF0000000 - PAGE_OFFSET))
#त्रुटि "You must adjust CONFIG_LOWMEM_SIZE or CONFIG_KERNEL_START"
#पूर्ण_अगर
#पूर्ण_अगर
#घोषणा MAX_LOW_MEM	CONFIG_LOWMEM_SIZE

phys_addr_t total_memory;
phys_addr_t total_lowmem;

#अगर_घोषित CONFIG_RELOCATABLE
/* Used in __va()/__pa() */
दीर्घ दीर्घ virt_phys_offset;
EXPORT_SYMBOL(virt_phys_offset);
#पूर्ण_अगर

phys_addr_t lowmem_end_addr;

पूर्णांक boot_mapsize;
#अगर_घोषित CONFIG_PPC_PMAC
अचिन्हित दीर्घ agp_special_page;
EXPORT_SYMBOL(agp_special_page);
#पूर्ण_अगर

व्योम MMU_init(व्योम);

/*
 * this tells the प्रणाली to map all of ram with the segregs
 * (i.e. page tables) instead of the bats.
 * -- Cort
 */
पूर्णांक __map_without_bats;
पूर्णांक __map_without_ltlbs;

/* max amount of low RAM to map in */
अचिन्हित दीर्घ __max_low_memory = MAX_LOW_MEM;

/*
 * Check क्रम command-line options that affect what MMU_init will करो.
 */
अटल व्योम __init MMU_setup(व्योम)
अणु
	/* Check क्रम nobats option (used in mapin_ram). */
	अगर (म_माला(boot_command_line, "nobats")) अणु
		__map_without_bats = 1;
	पूर्ण

	अगर (म_माला(boot_command_line, "noltlbs")) अणु
		__map_without_ltlbs = 1;
	पूर्ण
	अगर (IS_ENABLED(CONFIG_PPC_8xx))
		वापस;

	अगर (IS_ENABLED(CONFIG_KFENCE))
		__map_without_ltlbs = 1;

	अगर (debug_pagealloc_enabled())
		__map_without_ltlbs = 1;

	अगर (strict_kernel_rwx_enabled())
		__map_without_ltlbs = 1;
पूर्ण

/*
 * MMU_init sets up the basic memory mappings क्रम the kernel,
 * including both RAM and possibly some I/O regions,
 * and sets up the page tables and the MMU hardware पढ़ोy to go.
 */
व्योम __init MMU_init(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("MMU:enter", 0x111);

	/* parse args from command line */
	MMU_setup();

	/*
	 * Reserve gigantic pages क्रम hugetlb.  This MUST occur beक्रमe
	 * lowmem_end_addr is initialized below.
	 */
	अगर (memblock.memory.cnt > 1) अणु
#अगर_अघोषित CONFIG_WII
		memblock_enक्रमce_memory_limit(memblock.memory.regions[0].size);
		pr_warn("Only using first contiguous memory region\n");
#अन्यथा
		wii_memory_fixups();
#पूर्ण_अगर
	पूर्ण

	total_lowmem = total_memory = memblock_end_of_DRAM() - memstart_addr;
	lowmem_end_addr = memstart_addr + total_lowmem;

#अगर_घोषित CONFIG_FSL_BOOKE
	/* Freescale Book-E parts expect lowmem to be mapped by fixed TLB
	 * entries, so we need to adjust lowmem to match the amount we can map
	 * in the fixed entries */
	adjust_total_lowmem();
#पूर्ण_अगर /* CONFIG_FSL_BOOKE */

	अगर (total_lowmem > __max_low_memory) अणु
		total_lowmem = __max_low_memory;
		lowmem_end_addr = memstart_addr + total_lowmem;
#अगर_अघोषित CONFIG_HIGHMEM
		total_memory = total_lowmem;
		memblock_enक्रमce_memory_limit(total_lowmem);
#पूर्ण_अगर /* CONFIG_HIGHMEM */
	पूर्ण

	/* Initialize the MMU hardware */
	अगर (ppc_md.progress)
		ppc_md.progress("MMU:hw init", 0x300);
	MMU_init_hw();

	/* Map in all of RAM starting at KERNELBASE */
	अगर (ppc_md.progress)
		ppc_md.progress("MMU:mapin", 0x301);
	mapin_ram();

	/* Initialize early top-करोwn ioremap allocator */
	ioremap_bot = IOREMAP_TOP;

	अगर (ppc_md.progress)
		ppc_md.progress("MMU:exit", 0x211);

	/* From now on, btext is no दीर्घer BAT mapped अगर it was at all */
#अगर_घोषित CONFIG_BOOTX_TEXT
	btext_unmap();
#पूर्ण_अगर

	kasan_mmu_init();

	setup_kup();

	/* Shortly after that, the entire linear mapping will be available */
	memblock_set_current_limit(lowmem_end_addr);
पूर्ण
