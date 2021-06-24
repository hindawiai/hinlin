<शैली गुरु>
/*
 * Nios2-specअगरic parts of प्रणाली setup
 *
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 * Copyright (C) 2001 Vic Phillips <vic@microtronix.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/console.h>
#समावेश <linux/memblock.h>
#समावेश <linux/initrd.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/screen_info.h>

#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/cpuinfo.h>

अचिन्हित दीर्घ memory_start;
EXPORT_SYMBOL(memory_start);

अचिन्हित दीर्घ memory_end;
EXPORT_SYMBOL(memory_end);

अटल काष्ठा pt_regs fake_regs = अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0,
					0पूर्ण;

#अगर_घोषित CONFIG_VT
काष्ठा screen_info screen_info;
#पूर्ण_अगर

/* Copy a लघु hook inकाष्ठाion sequence to the exception address */
अटल अंतरभूत व्योम copy_exception_handler(अचिन्हित पूर्णांक addr)
अणु
	अचिन्हित पूर्णांक start = (अचिन्हित पूर्णांक) exception_handler_hook;
	अस्थिर अचिन्हित पूर्णांक पंचांगp = 0;

	अगर (start == addr) अणु
		/* The CPU exception address alपढ़ोy poपूर्णांकs to the handler. */
		वापस;
	पूर्ण

	__यंत्र__ __अस्थिर__ (
		"ldw	%2,0(%0)\n"
		"stw	%2,0(%1)\n"
		"ldw	%2,4(%0)\n"
		"stw	%2,4(%1)\n"
		"ldw	%2,8(%0)\n"
		"stw	%2,8(%1)\n"
		"flushd	0(%1)\n"
		"flushd	4(%1)\n"
		"flushd	8(%1)\n"
		"flushi %1\n"
		"addi	%1,%1,4\n"
		"flushi %1\n"
		"addi	%1,%1,4\n"
		"flushi %1\n"
		"flushp\n"
		: /* no output रेजिस्टरs */
		: "r" (start), "r" (addr), "r" (पंचांगp)
		: "memory"
	);
पूर्ण

/* Copy the fast TLB miss handler */
अटल अंतरभूत व्योम copy_fast_tlb_miss_handler(अचिन्हित पूर्णांक addr)
अणु
	अचिन्हित पूर्णांक start = (अचिन्हित पूर्णांक) fast_handler;
	अचिन्हित पूर्णांक end = (अचिन्हित पूर्णांक) fast_handler_end;
	अस्थिर अचिन्हित पूर्णांक पंचांगp = 0;

	__यंत्र__ __अस्थिर__ (
		"1:\n"
		"	ldw	%3,0(%0)\n"
		"	stw	%3,0(%1)\n"
		"	flushd	0(%1)\n"
		"	flushi	%1\n"
		"	flushp\n"
		"	addi	%0,%0,4\n"
		"	addi	%1,%1,4\n"
		"	bne	%0,%2,1b\n"
		: /* no output रेजिस्टरs */
		: "r" (start), "r" (addr), "r" (end), "r" (पंचांगp)
		: "memory"
	);
पूर्ण

/*
 * save args passed from u-boot, called from head.S
 *
 * @r4: NIOS magic
 * @r5: initrd start
 * @r6: initrd end or fdt
 * @r7: kernel command line
 */
यंत्रlinkage व्योम __init nios2_boot_init(अचिन्हित r4, अचिन्हित r5, अचिन्हित r6,
				       अचिन्हित r7)
अणु
	अचिन्हित dtb_passed = 0;
	अक्षर cmdline_passed[COMMAND_LINE_SIZE] __maybe_unused = अणु 0, पूर्ण;

#अगर defined(CONFIG_NIOS2_PASS_CMDLINE)
	अगर (r4 == 0x534f494e) अणु /* r4 is magic NIOS */
#अगर defined(CONFIG_BLK_DEV_INITRD)
		अगर (r5) अणु /* initramfs */
			initrd_start = r5;
			initrd_end = r6;
		पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_INITRD */
		dtb_passed = r6;

		अगर (r7)
			strlcpy(cmdline_passed, (अक्षर *)r7, COMMAND_LINE_SIZE);
	पूर्ण
#पूर्ण_अगर

	early_init_devtree((व्योम *)dtb_passed);

#अगर_अघोषित CONFIG_CMDLINE_FORCE
	अगर (cmdline_passed[0])
		strlcpy(boot_command_line, cmdline_passed, COMMAND_LINE_SIZE);
#अगर_घोषित CONFIG_NIOS2_CMDLINE_IGNORE_DTB
	अन्यथा
		strlcpy(boot_command_line, CONFIG_CMDLINE, COMMAND_LINE_SIZE);
#पूर्ण_अगर
#पूर्ण_अगर

	parse_early_param();
पूर्ण

अटल व्योम __init find_limits(अचिन्हित दीर्घ *min, अचिन्हित दीर्घ *max_low,
			       अचिन्हित दीर्घ *max_high)
अणु
	*max_low = PFN_DOWN(memblock_get_current_limit());
	*min = PFN_UP(memblock_start_of_DRAM());
	*max_high = PFN_DOWN(memblock_end_of_DRAM());
पूर्ण

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	पूर्णांक dram_start;

	console_verbose();

	memory_start = memblock_start_of_DRAM();
	memory_end = memblock_end_of_DRAM();

	init_mm.start_code = (अचिन्हित दीर्घ) _stext;
	init_mm.end_code = (अचिन्हित दीर्घ) _etext;
	init_mm.end_data = (अचिन्हित दीर्घ) _edata;
	init_mm.brk = (अचिन्हित दीर्घ) _end;
	init_task.thपढ़ो.kregs = &fake_regs;

	/* Keep a copy of command line */
	*cmdline_p = boot_command_line;

	find_limits(&min_low_pfn, &max_low_pfn, &max_pfn);
	max_mapnr = max_low_pfn;

	memblock_reserve(__pa_symbol(_stext), _end - _stext);
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (initrd_start) अणु
		memblock_reserve(virt_to_phys((व्योम *)initrd_start),
				initrd_end - initrd_start);
	पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_INITRD */

	early_init_fdt_reserve_self();
	early_init_fdt_scan_reserved_mem();

	unflatten_and_copy_device_tree();

	setup_cpuinfo();

	copy_exception_handler(cpuinfo.exception_addr);

	mmu_init();

	copy_fast_tlb_miss_handler(cpuinfo.fast_tlb_miss_exc_addr);

	/*
	 * Initialize MMU context handling here because data from cpuinfo is
	 * needed क्रम this.
	 */
	mmu_context_init();

	/*
	 * get kदो_स्मृति पूर्णांकo gear
	 */
	paging_init();
पूर्ण
