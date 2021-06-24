<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2013 Altera Corporation
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 *
 * Based on cpuinfo.c from microblaze
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/माला.स>
#समावेश <linux/of.h>
#समावेश <यंत्र/cpuinfo.h>

काष्ठा cpuinfo cpuinfo;

#घोषणा err_cpu(x) \
	pr_err("ERROR: Nios II " x " different for kernel and DTS\n")

अटल अंतरभूत u32 fcpu(काष्ठा device_node *cpu, स्थिर अक्षर *n)
अणु
	u32 val = 0;

	of_property_पढ़ो_u32(cpu, n, &val);

	वापस val;
पूर्ण

व्योम __init setup_cpuinfo(व्योम)
अणु
	काष्ठा device_node *cpu;
	स्थिर अक्षर *str;
	पूर्णांक len;

	cpu = of_get_cpu_node(0, शून्य);
	अगर (!cpu)
		panic("%s: No CPU found in devicetree!\n", __func__);

	अगर (!of_property_पढ़ो_bool(cpu, "altr,has-initda"))
		panic("initda instruction is unimplemented. Please update your "
			"hardware system to have more than 4-byte line data "
			"cache\n");

	cpuinfo.cpu_घड़ी_freq = fcpu(cpu, "clock-frequency");

	str = of_get_property(cpu, "altr,implementation", &len);
	अगर (str)
		strlcpy(cpuinfo.cpu_impl, str, माप(cpuinfo.cpu_impl));
	अन्यथा
		म_नकल(cpuinfo.cpu_impl, "<unknown>");

	cpuinfo.has_भाग = of_property_पढ़ो_bool(cpu, "altr,has-div");
	cpuinfo.has_mul = of_property_पढ़ो_bool(cpu, "altr,has-mul");
	cpuinfo.has_mulx = of_property_पढ़ो_bool(cpu, "altr,has-mulx");
	cpuinfo.has_bmx = of_property_पढ़ो_bool(cpu, "altr,has-bmx");
	cpuinfo.has_cdx = of_property_पढ़ो_bool(cpu, "altr,has-cdx");
	cpuinfo.mmu = of_property_पढ़ो_bool(cpu, "altr,has-mmu");

	अगर (IS_ENABLED(CONFIG_NIOS2_HW_DIV_SUPPORT) && !cpuinfo.has_भाग)
		err_cpu("DIV");

	अगर (IS_ENABLED(CONFIG_NIOS2_HW_MUL_SUPPORT) && !cpuinfo.has_mul)
		err_cpu("MUL");

	अगर (IS_ENABLED(CONFIG_NIOS2_HW_MULX_SUPPORT) && !cpuinfo.has_mulx)
		err_cpu("MULX");

	अगर (IS_ENABLED(CONFIG_NIOS2_BMX_SUPPORT) && !cpuinfo.has_bmx)
		err_cpu("BMX");

	अगर (IS_ENABLED(CONFIG_NIOS2_CDX_SUPPORT) && !cpuinfo.has_cdx)
		err_cpu("CDX");

	cpuinfo.tlb_num_ways = fcpu(cpu, "altr,tlb-num-ways");
	अगर (!cpuinfo.tlb_num_ways)
		panic("altr,tlb-num-ways can't be 0. Please check your hardware "
			"system\n");
	cpuinfo.icache_line_size = fcpu(cpu, "icache-line-size");
	cpuinfo.icache_size = fcpu(cpu, "icache-size");
	अगर (CONFIG_NIOS2_ICACHE_SIZE != cpuinfo.icache_size)
		pr_warn("Warning: icache size configuration mismatch "
		"(0x%x vs 0x%x) of CONFIG_NIOS2_ICACHE_SIZE vs "
		"device tree icache-size\n",
		CONFIG_NIOS2_ICACHE_SIZE, cpuinfo.icache_size);

	cpuinfo.dcache_line_size = fcpu(cpu, "dcache-line-size");
	अगर (CONFIG_NIOS2_DCACHE_LINE_SIZE != cpuinfo.dcache_line_size)
		pr_warn("Warning: dcache line size configuration mismatch "
		"(0x%x vs 0x%x) of CONFIG_NIOS2_DCACHE_LINE_SIZE vs "
		"device tree dcache-line-size\n",
		CONFIG_NIOS2_DCACHE_LINE_SIZE, cpuinfo.dcache_line_size);
	cpuinfo.dcache_size = fcpu(cpu, "dcache-size");
	अगर (CONFIG_NIOS2_DCACHE_SIZE != cpuinfo.dcache_size)
		pr_warn("Warning: dcache size configuration mismatch "
			"(0x%x vs 0x%x) of CONFIG_NIOS2_DCACHE_SIZE vs "
			"device tree dcache-size\n",
			CONFIG_NIOS2_DCACHE_SIZE, cpuinfo.dcache_size);

	cpuinfo.tlb_pid_num_bits = fcpu(cpu, "altr,pid-num-bits");
	cpuinfo.tlb_num_ways_log2 = ilog2(cpuinfo.tlb_num_ways);
	cpuinfo.tlb_num_entries = fcpu(cpu, "altr,tlb-num-entries");
	cpuinfo.tlb_num_lines = cpuinfo.tlb_num_entries / cpuinfo.tlb_num_ways;
	cpuinfo.tlb_ptr_sz = fcpu(cpu, "altr,tlb-ptr-sz");

	cpuinfo.reset_addr = fcpu(cpu, "altr,reset-addr");
	cpuinfo.exception_addr = fcpu(cpu, "altr,exception-addr");
	cpuinfo.fast_tlb_miss_exc_addr = fcpu(cpu, "altr,fast-tlb-miss-addr");

	of_node_put(cpu);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

/*
 * Get CPU inक्रमmation क्रम use by the procfs.
 */
अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *v)
अणु
	स्थिर u32 घड़ीfreq = cpuinfo.cpu_घड़ी_freq;

	seq_म_लिखो(m,
		   "CPU:\t\tNios II/%s\n"
		   "REV:\t\t%i\n"
		   "MMU:\t\t%s\n"
		   "FPU:\t\tnone\n"
		   "Clocking:\t%u.%02u MHz\n"
		   "BogoMips:\t%lu.%02lu\n"
		   "Calibration:\t%lu loops\n",
		   cpuinfo.cpu_impl,
		   CONFIG_NIOS2_ARCH_REVISION,
		   cpuinfo.mmu ? "present" : "none",
		   घड़ीfreq / 1000000, (घड़ीfreq / 100000) % 10,
		   (loops_per_jअगरfy * HZ) / 500000,
		   ((loops_per_jअगरfy * HZ) / 5000) % 100,
		   (loops_per_jअगरfy * HZ));

	seq_म_लिखो(m,
		   "HW:\n"
		   " MUL:\t\t%s\n"
		   " MULX:\t\t%s\n"
		   " DIV:\t\t%s\n"
		   " BMX:\t\t%s\n"
		   " CDX:\t\t%s\n",
		   cpuinfo.has_mul ? "yes" : "no",
		   cpuinfo.has_mulx ? "yes" : "no",
		   cpuinfo.has_भाग ? "yes" : "no",
		   cpuinfo.has_bmx ? "yes" : "no",
		   cpuinfo.has_cdx ? "yes" : "no");

	seq_म_लिखो(m,
		   "Icache:\t\t%ukB, line length: %u\n",
		   cpuinfo.icache_size >> 10,
		   cpuinfo.icache_line_size);

	seq_म_लिखो(m,
		   "Dcache:\t\t%ukB, line length: %u\n",
		   cpuinfo.dcache_size >> 10,
		   cpuinfo.dcache_line_size);

	seq_म_लिखो(m,
		   "TLB:\t\t%u ways, %u entries, %u PID bits\n",
		   cpuinfo.tlb_num_ways,
		   cpuinfo.tlb_num_entries,
		   cpuinfo.tlb_pid_num_bits);

	वापस 0;
पूर्ण

अटल व्योम *cpuinfo_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	अचिन्हित दीर्घ i = *pos;

	वापस i < num_possible_cpus() ? (व्योम *) (i + 1) : शून्य;
पूर्ण

अटल व्योम *cpuinfo_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस cpuinfo_start(m, pos);
पूर्ण

अटल व्योम cpuinfo_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start	= cpuinfo_start,
	.next	= cpuinfo_next,
	.stop	= cpuinfo_stop,
	.show	= show_cpuinfo
पूर्ण;

#पूर्ण_अगर /* CONFIG_PROC_FS */
