<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/h8300/kernel/setup.c
 *
 *  Copyright (C) 2001-2014 Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 */

/*
 * This file handles the architecture-dependent parts of प्रणाली setup
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/console.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/memblock.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/घड़ीsource.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/page.h>

#अगर defined(CONFIG_CPU_H8300H)
#घोषणा CPU "H8/300H"
#या_अगर defined(CONFIG_CPU_H8S)
#घोषणा CPU "H8S"
#अन्यथा
#घोषणा CPU "Unknown"
#पूर्ण_अगर

अचिन्हित दीर्घ memory_start;
अचिन्हित दीर्घ memory_end;
EXPORT_SYMBOL(memory_end);
अटल अचिन्हित दीर्घ freq;
बाह्य अक्षर __dtb_start[];

#अगर_घोषित CONFIG_VT
काष्ठा screen_info screen_info;
#पूर्ण_अगर

अक्षर __initdata command_line[COMMAND_LINE_SIZE];

व्योम sim_console_रेजिस्टर(व्योम);

व्योम __init h8300_fdt_init(व्योम *fdt, अक्षर *bootargs)
अणु
	अगर (!fdt)
		fdt = __dtb_start;
	अन्यथा
		म_नकल(command_line, bootargs);

	early_init_dt_scan(fdt);
	memblock_allow_resize();
पूर्ण

अटल व्योम __init booपंचांगem_init(व्योम)
अणु
	काष्ठा memblock_region *region;

	memory_end = memory_start = 0;

	/* Find मुख्य memory where is the kernel */
	memory_start = memblock_start_of_DRAM();
	memory_end = memblock_end_of_DRAM();

	अगर (!memory_end)
		panic("No memory!");

	/* setup booपंचांगem globals (we use no_booपंचांगem, but mm still depends on this) */
	min_low_pfn = PFN_UP(memory_start);
	max_low_pfn = PFN_DOWN(memory_end);
	max_pfn = max_low_pfn;

	memblock_reserve(__pa(_stext), _end - _stext);

	early_init_fdt_reserve_self();
	early_init_fdt_scan_reserved_mem();

	memblock_dump_all();
पूर्ण

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	unflatten_and_copy_device_tree();

	init_mm.start_code = (अचिन्हित दीर्घ) _stext;
	init_mm.end_code = (अचिन्हित दीर्घ) _etext;
	init_mm.end_data = (अचिन्हित दीर्घ) _edata;
	init_mm.brk = (अचिन्हित दीर्घ) 0;

	pr_notice("\r\n\nuClinux " CPU "\n");
	pr_notice("Flat model support (C) 1998,1999 Kenneth Albanowski, D. Jeff Dionne\n");

	अगर (*command_line)
		म_नकल(boot_command_line, command_line);
	*cmdline_p = boot_command_line;

	parse_early_param();

	booपंचांगem_init();
	/*
	 * get kदो_स्मृति पूर्णांकo gear
	 */
	paging_init();
पूर्ण

/*
 *	Get CPU inक्रमmation क्रम use by the procfs.
 */

अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *v)
अणु
	अक्षर *cpu;

	cpu = CPU;

	seq_म_लिखो(m,  "CPU:\t\t%s\n"
		   "Clock:\t\t%lu.%1luMHz\n"
		   "BogoMips:\t%lu.%02lu\n"
		   "Calibration:\t%lu loops\n",
		   cpu,
		   freq/1000, freq%1000,
		   (loops_per_jअगरfy*HZ)/500000,
		   ((loops_per_jअगरfy*HZ)/5000)%100,
		   (loops_per_jअगरfy*HZ));

	वापस 0;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	वापस *pos < num_possible_cpus() ?
		((व्योम *) 0x12345678) : शून्य;
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

#अगर defined(CONFIG_CPU_H8300H)
#घोषणा get_रुको(base, addr) (अणु		\
	पूर्णांक baddr;			\
	baddr = ((addr) / 0x200000 * 2);			     \
	w *= (पढ़ोw((base) + 2) & (3 << baddr)) + 1;		     \
	पूर्ण)
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_H8S)
#घोषणा get_रुको(base, addr) (अणु		\
	पूर्णांक baddr;			\
	baddr = ((addr) / 0x200000 * 16);			     \
	w *= (पढ़ोl((base) + 2) & (7 << baddr)) + 1;	\
	पूर्ण)
#पूर्ण_अगर

अटल __init पूर्णांक access_timing(व्योम)
अणु
	काष्ठा device_node *bsc;
	व्योम __iomem *base;
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)&__delay;
	पूर्णांक bit = 1 << (addr / 0x200000);
	पूर्णांक w;

	bsc = of_find_compatible_node(शून्य, शून्य, "renesas,h8300-bsc");
	base = of_iomap(bsc, 0);
	w = (पढ़ोb(base + 0) & bit)?2:1;
	अगर (पढ़ोb(base + 1) & bit)
		w *= get_रुको(base, addr);
	अन्यथा
		w *= 2;
	वापस w * 3 / 2;
पूर्ण

व्योम __init calibrate_delay(व्योम)
अणु
	काष्ठा device_node *cpu;
	पूर्णांक freq;

	cpu = of_find_compatible_node(शून्य, शून्य, "renesas,h8300");
	of_property_पढ़ो_s32(cpu, "clock-frequency", &freq);
	loops_per_jअगरfy = freq / HZ / (access_timing() * 2);
	pr_cont("%lu.%02lu BogoMIPS (lpj=%lu)\n",
		loops_per_jअगरfy / (500000 / HZ),
		(loops_per_jअगरfy / (5000 / HZ)) % 100, loops_per_jअगरfy);
पूर्ण


व्योम __init समय_init(व्योम)
अणु
	of_clk_init(शून्य);
	समयr_probe();
पूर्ण
