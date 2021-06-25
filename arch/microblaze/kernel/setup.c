<शैली गुरु>
/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/माला.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/cpu.h>
#समावेश <linux/initrd.h>
#समावेश <linux/console.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/पन.स>
#समावेश <linux/bug.h>
#समावेश <linux/param.h>
#समावेश <linux/pci.h>
#समावेश <linux/cache.h>
#समावेश <linux/of.h>
#समावेश <linux/dma-mapping.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/entry.h>
#समावेश <यंत्र/cpuinfo.h>


DEFINE_PER_CPU(अचिन्हित पूर्णांक, KSP);	/* Saved kernel stack poपूर्णांकer */
DEFINE_PER_CPU(अचिन्हित पूर्णांक, KM);	/* Kernel/user mode */
DEFINE_PER_CPU(अचिन्हित पूर्णांक, ENTRY_SP);	/* Saved SP on kernel entry */
DEFINE_PER_CPU(अचिन्हित पूर्णांक, R11_SAVE);	/* Temp variable क्रम entry */
DEFINE_PER_CPU(अचिन्हित पूर्णांक, CURRENT_SAVE);	/* Saved current poपूर्णांकer */

/*
 * Placed cmd_line to .data section because can be initialized from
 * ASM code. Default position is BSS section which is cleared
 * in machine_early_init().
 */
अक्षर cmd_line[COMMAND_LINE_SIZE] __section(".data");

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	*cmdline_p = boot_command_line;

	setup_memory();

	console_verbose();

	unflatten_device_tree();

	setup_cpuinfo();

	microblaze_cache_init();

	xilinx_pci_init();
पूर्ण

#अगर_घोषित CONFIG_MTD_UCLINUX
/* Handle both romfs and cramfs types, without generating unnecessary
 code (ie no poपूर्णांक checking क्रम CRAMFS अगर it's not even enabled) */
अंतरभूत अचिन्हित get_romfs_len(अचिन्हित *addr)
अणु
#अगर_घोषित CONFIG_ROMFS_FS
	अगर (स_भेद(&addr[0], "-rom1fs-", 8) == 0) /* romfs */
		वापस be32_to_cpu(addr[2]);
#पूर्ण_अगर

#अगर_घोषित CONFIG_CRAMFS
	अगर (addr[0] == le32_to_cpu(0x28cd3d45)) /* cramfs */
		वापस le32_to_cpu(addr[1]);
#पूर्ण_अगर
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_MTD_UCLINUX_EBSS */

अचिन्हित दीर्घ kernel_tlb;

व्योम __init machine_early_init(स्थिर अक्षर *cmdline, अचिन्हित पूर्णांक ram,
		अचिन्हित पूर्णांक fdt, अचिन्हित पूर्णांक msr, अचिन्हित पूर्णांक tlb0,
		अचिन्हित पूर्णांक tlb1)
अणु
	अचिन्हित दीर्घ *src, *dst;
	अचिन्हित पूर्णांक offset = 0;

	/* If CONFIG_MTD_UCLINUX is defined, assume ROMFS is at the
	 * end of kernel. There are two position which we want to check.
	 * The first is __init_end and the second __bss_start.
	 */
#अगर_घोषित CONFIG_MTD_UCLINUX
	पूर्णांक romfs_size;
	अचिन्हित पूर्णांक romfs_base;
	अक्षर *old_klimit = klimit;

	romfs_base = (ram ? ram : (अचिन्हित पूर्णांक)&__init_end);
	romfs_size = PAGE_ALIGN(get_romfs_len((अचिन्हित *)romfs_base));
	अगर (!romfs_size) अणु
		romfs_base = (अचिन्हित पूर्णांक)&__bss_start;
		romfs_size = PAGE_ALIGN(get_romfs_len((अचिन्हित *)romfs_base));
	पूर्ण

	/* Move ROMFS out of BSS beक्रमe clearing it */
	अगर (romfs_size > 0) अणु
		स_हटाओ(&__bss_stop, (पूर्णांक *)romfs_base, romfs_size);
		klimit += romfs_size;
	पूर्ण
#पूर्ण_अगर

/* clearing bss section */
	स_रखो(__bss_start, 0, __bss_stop-__bss_start);
	स_रखो(_ssbss, 0, _esbss-_ssbss);

/* initialize device tree क्रम usage in early_prपूर्णांकk */
	early_init_devtree(_fdt_start);

	/* setup kernel_tlb after BSS cleaning
	 * Maybe worth to move to यंत्र code */
	kernel_tlb = tlb0 + tlb1;
	/* prपूर्णांकk("TLB1 0x%08x, TLB0 0x%08x, tlb 0x%x\n", tlb0,
							tlb1, kernel_tlb); */

	pr_info("Ramdisk addr 0x%08x, ", ram);
	अगर (fdt)
		pr_info("FDT at 0x%08x\n", fdt);
	अन्यथा
		pr_info("Compiled-in FDT at %p\n", _fdt_start);

#अगर_घोषित CONFIG_MTD_UCLINUX
	pr_info("Found romfs @ 0x%08x (0x%08x)\n",
			romfs_base, romfs_size);
	pr_info("#### klimit %p ####\n", old_klimit);
	BUG_ON(romfs_size < 0); /* What अन्यथा can we करो? */

	pr_info("Moved 0x%08x bytes from 0x%08x to 0x%08x\n",
			romfs_size, romfs_base, (अचिन्हित)&__bss_stop);

	pr_info("New klimit: 0x%08x\n", (अचिन्हित)klimit);
#पूर्ण_अगर

#अगर CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR
	अगर (msr) अणु
		pr_info("!!!Your kernel has setup MSR instruction but ");
		pr_cont("CPU don't have it %x\n", msr);
	पूर्ण
#अन्यथा
	अगर (!msr) अणु
		pr_info("!!!Your kernel not setup MSR instruction but ");
		pr_cont("CPU have it %x\n", msr);
	पूर्ण
#पूर्ण_अगर

	/* Do not copy reset vectors. offset = 0x2 means skip the first
	 * two inकाष्ठाions. dst is poपूर्णांकer to MB vectors which are placed
	 * in block ram. If you want to copy reset vector setup offset to 0x0 */
#अगर !CONFIG_MANUAL_RESET_VECTOR
	offset = 0x2;
#पूर्ण_अगर
	dst = (अचिन्हित दीर्घ *) (offset * माप(u32));
	क्रम (src = __ivt_start + offset; src < __ivt_end; src++, dst++)
		*dst = *src;

	/* Initialize global data */
	per_cpu(KM, 0) = 0x1;	/* We start in kernel mode */
	per_cpu(CURRENT_SAVE, 0) = (अचिन्हित दीर्घ)current;
पूर्ण

व्योम __init समय_init(व्योम)
अणु
	of_clk_init(शून्य);
	setup_cpuinfo_clk();
	समयr_probe();
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
काष्ठा dentry *of_debugfs_root;

अटल पूर्णांक microblaze_debugfs_init(व्योम)
अणु
	of_debugfs_root = debugfs_create_dir("microblaze", शून्य);
	वापस 0;
पूर्ण
arch_initcall(microblaze_debugfs_init);

अटल पूर्णांक __init debugfs_tlb(व्योम)
अणु
	debugfs_create_u32("tlb_skip", S_IRUGO, of_debugfs_root, &tlb_skip);
	वापस 0;
पूर्ण
device_initcall(debugfs_tlb);
#पूर्ण_अगर
