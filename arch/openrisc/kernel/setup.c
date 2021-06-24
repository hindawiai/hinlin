<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC setup.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 *
 * This file handles the architecture-dependent parts of initialization
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/serial.h>
#समावेश <linux/initrd.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of.h>
#समावेश <linux/device.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/cpuinfo.h>
#समावेश <यंत्र/delay.h>

#समावेश "vmlinux.h"

अटल व्योम __init setup_memory(व्योम)
अणु
	अचिन्हित दीर्घ ram_start_pfn;
	अचिन्हित दीर्घ ram_end_pfn;
	phys_addr_t memory_start, memory_end;

	memory_end = memory_start = 0;

	/* Find मुख्य memory where is the kernel, we assume its the only one */
	memory_start = memblock_start_of_DRAM();
	memory_end = memblock_end_of_DRAM();

	अगर (!memory_end) अणु
		panic("No memory!");
	पूर्ण

	ram_start_pfn = PFN_UP(memory_start);
	ram_end_pfn = PFN_DOWN(memblock_end_of_DRAM());

	/* setup booपंचांगem globals (we use no_booपंचांगem, but mm still depends on this) */
	min_low_pfn = ram_start_pfn;
	max_low_pfn = ram_end_pfn;
	max_pfn = ram_end_pfn;

	/*
	 * initialize the boot-समय allocator (with low memory only).
	 *
	 * This makes the memory from the end of the kernel to the end of
	 * RAM usable.
	 */
	memblock_reserve(__pa(_stext), _end - _stext);

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	/* Then reserve the initrd, अगर any */
	अगर (initrd_start && (initrd_end > initrd_start)) अणु
		अचिन्हित दीर्घ aligned_start = ALIGN_DOWN(initrd_start, PAGE_SIZE);
		अचिन्हित दीर्घ aligned_end = ALIGN(initrd_end, PAGE_SIZE);

		memblock_reserve(__pa(aligned_start), aligned_end - aligned_start);
	पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_INITRD */

	early_init_fdt_reserve_self();
	early_init_fdt_scan_reserved_mem();

	memblock_dump_all();
पूर्ण

काष्ठा cpuinfo_or1k cpuinfo_or1k[NR_CPUS];

अटल व्योम prपूर्णांक_cpuinfo(व्योम)
अणु
	अचिन्हित दीर्घ upr = mfspr(SPR_UPR);
	अचिन्हित दीर्घ vr = mfspr(SPR_VR);
	अचिन्हित पूर्णांक version;
	अचिन्हित पूर्णांक revision;
	काष्ठा cpuinfo_or1k *cpuinfo = &cpuinfo_or1k[smp_processor_id()];

	version = (vr & SPR_VR_VER) >> 24;
	revision = (vr & SPR_VR_REV);

	prपूर्णांकk(KERN_INFO "CPU: OpenRISC-%x (revision %d) @%d MHz\n",
	       version, revision, cpuinfo->घड़ी_frequency / 1000000);

	अगर (!(upr & SPR_UPR_UP)) अणु
		prपूर्णांकk(KERN_INFO
		       "-- no UPR register... unable to detect configuration\n");
		वापस;
	पूर्ण

	अगर (upr & SPR_UPR_DCP)
		prपूर्णांकk(KERN_INFO
		       "-- dcache: %4d bytes total, %2d bytes/line, %d way(s)\n",
		       cpuinfo->dcache_size, cpuinfo->dcache_block_size,
		       cpuinfo->dcache_ways);
	अन्यथा
		prपूर्णांकk(KERN_INFO "-- dcache disabled\n");
	अगर (upr & SPR_UPR_ICP)
		prपूर्णांकk(KERN_INFO
		       "-- icache: %4d bytes total, %2d bytes/line, %d way(s)\n",
		       cpuinfo->icache_size, cpuinfo->icache_block_size,
		       cpuinfo->icache_ways);
	अन्यथा
		prपूर्णांकk(KERN_INFO "-- icache disabled\n");

	अगर (upr & SPR_UPR_DMP)
		prपूर्णांकk(KERN_INFO "-- dmmu: %4d entries, %lu way(s)\n",
		       1 << ((mfspr(SPR_DMMUCFGR) & SPR_DMMUCFGR_NTS) >> 2),
		       1 + (mfspr(SPR_DMMUCFGR) & SPR_DMMUCFGR_NTW));
	अगर (upr & SPR_UPR_IMP)
		prपूर्णांकk(KERN_INFO "-- immu: %4d entries, %lu way(s)\n",
		       1 << ((mfspr(SPR_IMMUCFGR) & SPR_IMMUCFGR_NTS) >> 2),
		       1 + (mfspr(SPR_IMMUCFGR) & SPR_IMMUCFGR_NTW));

	prपूर्णांकk(KERN_INFO "-- additional features:\n");
	अगर (upr & SPR_UPR_DUP)
		prपूर्णांकk(KERN_INFO "-- debug unit\n");
	अगर (upr & SPR_UPR_PCUP)
		prपूर्णांकk(KERN_INFO "-- performance counters\n");
	अगर (upr & SPR_UPR_PMP)
		prपूर्णांकk(KERN_INFO "-- power management\n");
	अगर (upr & SPR_UPR_PICP)
		prपूर्णांकk(KERN_INFO "-- PIC\n");
	अगर (upr & SPR_UPR_TTP)
		prपूर्णांकk(KERN_INFO "-- timer\n");
	अगर (upr & SPR_UPR_CUP)
		prपूर्णांकk(KERN_INFO "-- custom unit(s)\n");
पूर्ण

अटल काष्ठा device_node *setup_find_cpu_node(पूर्णांक cpu)
अणु
	u32 hwid;
	काष्ठा device_node *cpun;

	क्रम_each_of_cpu_node(cpun) अणु
		अगर (of_property_पढ़ो_u32(cpun, "reg", &hwid))
			जारी;
		अगर (hwid == cpu)
			वापस cpun;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम __init setup_cpuinfo(व्योम)
अणु
	काष्ठा device_node *cpu;
	अचिन्हित दीर्घ iccfgr, dccfgr;
	अचिन्हित दीर्घ cache_set_size;
	पूर्णांक cpu_id = smp_processor_id();
	काष्ठा cpuinfo_or1k *cpuinfo = &cpuinfo_or1k[cpu_id];

	cpu = setup_find_cpu_node(cpu_id);
	अगर (!cpu)
		panic("Couldn't find CPU%d in device tree...\n", cpu_id);

	iccfgr = mfspr(SPR_ICCFGR);
	cpuinfo->icache_ways = 1 << (iccfgr & SPR_ICCFGR_NCW);
	cache_set_size = 1 << ((iccfgr & SPR_ICCFGR_NCS) >> 3);
	cpuinfo->icache_block_size = 16 << ((iccfgr & SPR_ICCFGR_CBS) >> 7);
	cpuinfo->icache_size =
	    cache_set_size * cpuinfo->icache_ways * cpuinfo->icache_block_size;

	dccfgr = mfspr(SPR_DCCFGR);
	cpuinfo->dcache_ways = 1 << (dccfgr & SPR_DCCFGR_NCW);
	cache_set_size = 1 << ((dccfgr & SPR_DCCFGR_NCS) >> 3);
	cpuinfo->dcache_block_size = 16 << ((dccfgr & SPR_DCCFGR_CBS) >> 7);
	cpuinfo->dcache_size =
	    cache_set_size * cpuinfo->dcache_ways * cpuinfo->dcache_block_size;

	अगर (of_property_पढ़ो_u32(cpu, "clock-frequency",
				 &cpuinfo->घड़ी_frequency)) अणु
		prपूर्णांकk(KERN_WARNING
		       "Device tree missing CPU 'clock-frequency' parameter."
		       "Assuming frequency 25MHZ"
		       "This is probably not what you want.");
	पूर्ण

	cpuinfo->coreid = mfspr(SPR_COREID);

	of_node_put(cpu);

	prपूर्णांक_cpuinfo();
पूर्ण

/**
 * or32_early_setup
 *
 * Handles the poपूर्णांकer to the device tree that this kernel is to use
 * क्रम establishing the available platक्रमm devices.
 *
 * Falls back on built-in device tree in हाल null poपूर्णांकer is passed.
 */

व्योम __init or32_early_setup(व्योम *fdt)
अणु
	अगर (fdt)
		pr_info("FDT at %p\n", fdt);
	अन्यथा अणु
		fdt = __dtb_start;
		pr_info("Compiled-in FDT at %p\n", fdt);
	पूर्ण
	early_init_devtree(fdt);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ extract_value_bits(अचिन्हित दीर्घ reg,
					       लघु bit_nr, लघु width)
अणु
	वापस (reg >> bit_nr) & (0 << width);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ extract_value(अचिन्हित दीर्घ reg, अचिन्हित दीर्घ mask)
अणु
	जबतक (!(mask & 0x1)) अणु
		reg = reg >> 1;
		mask = mask >> 1;
	पूर्ण
	वापस mask & reg;
पूर्ण

व्योम __init detect_unit_config(अचिन्हित दीर्घ upr, अचिन्हित दीर्घ mask,
			       अक्षर *text, व्योम (*func) (व्योम))
अणु
	अगर (text != शून्य)
		prपूर्णांकk("%s", text);

	अगर (upr & mask) अणु
		अगर (func != शून्य)
			func();
		अन्यथा
			prपूर्णांकk("present\n");
	पूर्ण अन्यथा
		prपूर्णांकk("not present\n");
पूर्ण

/*
 * calibrate_delay
 *
 * Lightweight calibrate_delay implementation that calculates loops_per_jअगरfy
 * from the घड़ी frequency passed in via the device tree
 *
 */

व्योम calibrate_delay(व्योम)
अणु
	स्थिर पूर्णांक *val;
	काष्ठा device_node *cpu = setup_find_cpu_node(smp_processor_id());

	val = of_get_property(cpu, "clock-frequency", शून्य);
	अगर (!val)
		panic("no cpu 'clock-frequency' parameter in device tree");
	loops_per_jअगरfy = *val / HZ;
	pr_cont("%lu.%02lu BogoMIPS (lpj=%lu)\n",
		loops_per_jअगरfy / (500000 / HZ),
		(loops_per_jअगरfy / (5000 / HZ)) % 100, loops_per_jअगरfy);

	of_node_put(cpu);
पूर्ण

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	unflatten_and_copy_device_tree();

	setup_cpuinfo();

#अगर_घोषित CONFIG_SMP
	smp_init_cpus();
#पूर्ण_अगर

	/* process 1's initial memory region is the kernel code/data */
	init_mm.start_code = (अचिन्हित दीर्घ)_stext;
	init_mm.end_code = (अचिन्हित दीर्घ)_etext;
	init_mm.end_data = (अचिन्हित दीर्घ)_edata;
	init_mm.brk = (अचिन्हित दीर्घ)_end;

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (initrd_start == initrd_end) अणु
		prपूर्णांकk(KERN_INFO "Initial ramdisk not found\n");
		initrd_start = 0;
		initrd_end = 0;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "Initial ramdisk at: 0x%p (%lu bytes)\n",
		       (व्योम *)(initrd_start), initrd_end - initrd_start);
		initrd_below_start_ok = 1;
	पूर्ण
#पूर्ण_अगर

	/* setup memblock allocator */
	setup_memory();

	/* paging_init() sets up the MMU and marks all pages as reserved */
	paging_init();

	*cmdline_p = boot_command_line;

	prपूर्णांकk(KERN_INFO "OpenRISC Linux -- http://openrisc.io\n");
पूर्ण

अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित पूर्णांक vr, cpucfgr;
	अचिन्हित पूर्णांक avr;
	अचिन्हित पूर्णांक version;
	काष्ठा cpuinfo_or1k *cpuinfo = v;

	vr = mfspr(SPR_VR);
	cpucfgr = mfspr(SPR_CPUCFGR);

#अगर_घोषित CONFIG_SMP
	seq_म_लिखो(m, "processor\t\t: %d\n", cpuinfo->coreid);
#पूर्ण_अगर
	अगर (vr & SPR_VR_UVRP) अणु
		vr = mfspr(SPR_VR2);
		version = vr & SPR_VR2_VER;
		avr = mfspr(SPR_AVR);
		seq_म_लिखो(m, "cpu architecture\t: "
			   "OpenRISC 1000 (%d.%d-rev%d)\n",
			   (avr >> 24) & 0xff,
			   (avr >> 16) & 0xff,
			   (avr >> 8) & 0xff);
		seq_म_लिखो(m, "cpu implementation id\t: 0x%x\n",
			   (vr & SPR_VR2_CPUID) >> 24);
		seq_म_लिखो(m, "cpu version\t\t: 0x%x\n", version);
	पूर्ण अन्यथा अणु
		version = (vr & SPR_VR_VER) >> 24;
		seq_म_लिखो(m, "cpu\t\t\t: OpenRISC-%x\n", version);
		seq_म_लिखो(m, "revision\t\t: %d\n", vr & SPR_VR_REV);
	पूर्ण
	seq_म_लिखो(m, "frequency\t\t: %ld\n", loops_per_jअगरfy * HZ);
	seq_म_लिखो(m, "dcache size\t\t: %d bytes\n", cpuinfo->dcache_size);
	seq_म_लिखो(m, "dcache block size\t: %d bytes\n",
		   cpuinfo->dcache_block_size);
	seq_म_लिखो(m, "dcache ways\t\t: %d\n", cpuinfo->dcache_ways);
	seq_म_लिखो(m, "icache size\t\t: %d bytes\n", cpuinfo->icache_size);
	seq_म_लिखो(m, "icache block size\t: %d bytes\n",
		   cpuinfo->icache_block_size);
	seq_म_लिखो(m, "icache ways\t\t: %d\n", cpuinfo->icache_ways);
	seq_म_लिखो(m, "immu\t\t\t: %d entries, %lu ways\n",
		   1 << ((mfspr(SPR_DMMUCFGR) & SPR_DMMUCFGR_NTS) >> 2),
		   1 + (mfspr(SPR_DMMUCFGR) & SPR_DMMUCFGR_NTW));
	seq_म_लिखो(m, "dmmu\t\t\t: %d entries, %lu ways\n",
		   1 << ((mfspr(SPR_IMMUCFGR) & SPR_IMMUCFGR_NTS) >> 2),
		   1 + (mfspr(SPR_IMMUCFGR) & SPR_IMMUCFGR_NTW));
	seq_म_लिखो(m, "bogomips\t\t: %lu.%02lu\n",
		   (loops_per_jअगरfy * HZ) / 500000,
		   ((loops_per_jअगरfy * HZ) / 5000) % 100);

	seq_माला_दो(m, "features\t\t: ");
	seq_म_लिखो(m, "%s ", cpucfgr & SPR_CPUCFGR_OB32S ? "orbis32" : "");
	seq_म_लिखो(m, "%s ", cpucfgr & SPR_CPUCFGR_OB64S ? "orbis64" : "");
	seq_म_लिखो(m, "%s ", cpucfgr & SPR_CPUCFGR_OF32S ? "orfpx32" : "");
	seq_म_लिखो(m, "%s ", cpucfgr & SPR_CPUCFGR_OF64S ? "orfpx64" : "");
	seq_म_लिखो(m, "%s ", cpucfgr & SPR_CPUCFGR_OV64S ? "orvdx64" : "");
	seq_माला_दो(m, "\n");

	seq_माला_दो(m, "\n");

	वापस 0;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	*pos = cpumask_next(*pos - 1, cpu_online_mask);
	अगर ((*pos) < nr_cpu_ids)
		वापस &cpuinfo_or1k[*pos];
	वापस शून्य;
पूर्ण

अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस c_start(m, pos);
पूर्ण

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start = c_start,
	.next = c_next,
	.stop = c_stop,
	.show = show_cpuinfo,
पूर्ण;
