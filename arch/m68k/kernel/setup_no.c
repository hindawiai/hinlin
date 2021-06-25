<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/m68knommu/kernel/setup.c
 *
 *  Copyright (C) 1999-2007  Greg Ungerer (gerg@snapgear.com)
 *  Copyright (C) 1998,1999  D. Jeff Dionne <jeff@uClinux.org>
 *  Copyleft  ()) 2000       James D. Schettine अणुjames@telos-प्रणालीs.comपूर्ण
 *  Copyright (C) 1998       Kenneth Albanowski <kjahds@kjahds.com>
 *  Copyright (C) 1995       Hamish Macकरोnald
 *  Copyright (C) 2000       Lineo Inc. (www.lineo.com)
 *  Copyright (C) 2001 	     Lineo, Inc. <www.lineo.com>
 *
 *  68VZ328 Fixes/support    Evan Stawnyczy <e@lineo.ca>
 */

/*
 * This file handles the architecture-dependent parts of प्रणाली setup
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/console.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/memblock.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/initrd.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/rtc.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/sections.h>

अचिन्हित दीर्घ memory_start;
अचिन्हित दीर्घ memory_end;

EXPORT_SYMBOL(memory_start);
EXPORT_SYMBOL(memory_end);

अक्षर __initdata command_line[COMMAND_LINE_SIZE];

/* machine dependent समयr functions */
व्योम (*mach_sched_init)(व्योम) __initdata = शून्य;
पूर्णांक (*mach_hwclk) (पूर्णांक, काष्ठा rtc_समय*);

/* machine dependent reboot functions */
व्योम (*mach_reset)(व्योम);
व्योम (*mach_halt)(व्योम);
व्योम (*mach_घातer_off)(व्योम);

#अगर_घोषित CONFIG_M68000
#अगर defined(CONFIG_M68328)
#घोषणा CPU_NAME	"MC68328"
#या_अगर defined(CONFIG_M68EZ328)
#घोषणा CPU_NAME	"MC68EZ328"
#या_अगर defined(CONFIG_M68VZ328)
#घोषणा CPU_NAME	"MC68VZ328"
#अन्यथा
#घोषणा CPU_NAME	"MC68000"
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_M68000 */
#अगर_अघोषित CPU_NAME
#घोषणा	CPU_NAME	"UNKNOWN"
#पूर्ण_अगर

/*
 * Dअगरferent cores have dअगरferent inकाष्ठाion execution timings.
 * The old/traditional 68000 cores are basically all the same, at 16.
 * The ColdFire cores vary a little, their values are defined in their
 * headers. We शेष to the standard 68000 value here.
 */
#अगर_अघोषित CPU_INSTR_PER_JIFFY
#घोषणा	CPU_INSTR_PER_JIFFY	16
#पूर्ण_अगर

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	memory_start = PAGE_ALIGN(_ramstart);
	memory_end = _ramend;

	init_mm.start_code = (अचिन्हित दीर्घ) &_stext;
	init_mm.end_code = (अचिन्हित दीर्घ) &_etext;
	init_mm.end_data = (अचिन्हित दीर्घ) &_edata;
	init_mm.brk = (अचिन्हित दीर्घ) 0;

	config_BSP(&command_line[0], माप(command_line));

#अगर defined(CONFIG_BOOTPARAM)
	म_नकलन(&command_line[0], CONFIG_BOOTPARAM_STRING, माप(command_line));
	command_line[माप(command_line) - 1] = 0;
#पूर्ण_अगर /* CONFIG_BOOTPARAM */

	process_uboot_commandline(&command_line[0], माप(command_line));

	pr_info("uClinux with CPU " CPU_NAME "\n");

#अगर_घोषित CONFIG_UCDIMM
	pr_info("uCdimm by Lineo, Inc. <www.lineo.com>\n");
#पूर्ण_अगर
#अगर_घोषित CONFIG_M68328
	pr_info("68328 support D. Jeff Dionne <jeff@uclinux.org>\n");
	pr_info("68328 support Kenneth Albanowski <kjahds@kjshds.com>\n");
#पूर्ण_अगर
#अगर_घोषित CONFIG_M68EZ328
	pr_info("68EZ328 DragonBallEZ support (C) 1999 Rt-Control, Inc\n");
#पूर्ण_अगर
#अगर_घोषित CONFIG_M68VZ328
	pr_info("M68VZ328 support by Evan Stawnyczy <e@lineo.ca>\n");
	pr_info("68VZ328 DragonBallVZ support (c) 2001 Lineo, Inc.\n");
#पूर्ण_अगर
#अगर_घोषित CONFIG_COLDFIRE
	pr_info("COLDFIRE port done by Greg Ungerer, gerg@snapgear.com\n");
#अगर_घोषित CONFIG_M5307
	pr_info("Modified for M5307 by Dave Miller, dmiller@intellistor.com\n");
#पूर्ण_अगर
#अगर_घोषित CONFIG_ELITE
	pr_info("Modified for M5206eLITE by Rob Scott, rscott@mtrob.fdns.net\n");
#पूर्ण_अगर
#पूर्ण_अगर
	pr_info("Flat model support (C) 1998,1999 Kenneth Albanowski, D. Jeff Dionne\n");

#अगर defined( CONFIG_PILOT ) && defined( CONFIG_M68328 )
	pr_info("68328/Pilot support Bernhard Kuhn <kuhn@lpr.e-technik.tu-muenchen.de>\n");
	pr_info("TRG SuperPilot FLASH card support <info@trgnet.com>\n");
#पूर्ण_अगर
#अगर defined( CONFIG_PILOT ) && defined( CONFIG_M68EZ328 )
	pr_info("PalmV support by Lineo Inc. <jeff@uclinux.com>\n");
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRAGEN2
	pr_info("DragonEngine II board support by Georges Menie\n");
#पूर्ण_अगर
#अगर_घोषित CONFIG_M5235EVB
	pr_info("Motorola M5235EVB support (C)2005 Syn-tech Systems, Inc. (Jate Sujjavanich)\n");
#पूर्ण_अगर

	pr_debug("KERNEL -> TEXT=0x%p-0x%p DATA=0x%p-0x%p BSS=0x%p-0x%p\n",
		 _stext, _etext, _sdata, _edata, __bss_start, __bss_stop);
	pr_debug("MEMORY -> ROMFS=0x%p-0x%06lx MEM=0x%06lx-0x%06lx\n ",
		 __bss_stop, memory_start, memory_start, memory_end);

	memblock_add(_rambase, memory_end - _rambase);
	memblock_reserve(_rambase, memory_start - _rambase);

	/* Keep a copy of command line */
	*cmdline_p = &command_line[0];
	स_नकल(boot_command_line, command_line, COMMAND_LINE_SIZE);
	boot_command_line[COMMAND_LINE_SIZE-1] = 0;

	/*
	 * Give all the memory to the booपंचांगap allocator, tell it to put the
	 * boot mem_map at the start of memory.
	 */
	min_low_pfn = PFN_DOWN(memory_start);
	max_pfn = max_low_pfn = PFN_DOWN(memory_end);

#अगर defined(CONFIG_UBOOT) && defined(CONFIG_BLK_DEV_INITRD)
	अगर ((initrd_start > 0) && (initrd_start < initrd_end) &&
			(initrd_end < memory_end))
		memblock_reserve(initrd_start, initrd_end - initrd_start);
#पूर्ण_अगर /* अगर defined(CONFIG_BLK_DEV_INITRD) */

	/*
	 * Get kदो_स्मृति पूर्णांकo gear.
	 */
	paging_init();
पूर्ण

/*
 *	Get CPU inक्रमmation क्रम use by the procfs.
 */
अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *v)
अणु
	अक्षर *cpu, *mmu, *fpu;
	u_दीर्घ घड़ीfreq;

	cpu = CPU_NAME;
	mmu = "none";
	fpu = "none";
	घड़ीfreq = (loops_per_jअगरfy * HZ) * CPU_INSTR_PER_JIFFY;

	seq_म_लिखो(m, "CPU:\t\t%s\n"
		      "MMU:\t\t%s\n"
		      "FPU:\t\t%s\n"
		      "Clocking:\t%lu.%1luMHz\n"
		      "BogoMips:\t%lu.%02lu\n"
		      "Calibration:\t%lu loops\n",
		      cpu, mmu, fpu,
		      घड़ीfreq / 1000000,
		      (घड़ीfreq / 100000) % 10,
		      (loops_per_jअगरfy * HZ) / 500000,
		      ((loops_per_jअगरfy * HZ) / 5000) % 100,
		      (loops_per_jअगरfy * HZ));

	वापस 0;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	वापस *pos < NR_CPUS ? ((व्योम *) 0x12345678) : शून्य;
पूर्ण

अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस c_start(m, pos);
पूर्ण

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
पूर्ण;

