<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Arch related setup क्रम Hexagon
 *
 * Copyright (c) 2010-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/mm.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/console.h>
#समावेश <linux/of_fdt.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/hexagon_vm.h>
#समावेश <यंत्र/vm_mmu.h>
#समावेश <यंत्र/समय.स>

अक्षर cmd_line[COMMAND_LINE_SIZE];
अटल अक्षर शेष_command_line[COMMAND_LINE_SIZE] __initdata = CONFIG_CMDLINE;

पूर्णांक on_simulator;

व्योम calibrate_delay(व्योम)
अणु
	loops_per_jअगरfy = thपढ़ो_freq_mhz * 1000000 / HZ;
पूर्ण

/*
 * setup_arch -  high level architectural setup routine
 * @cmdline_p: poपूर्णांकer to poपूर्णांकer to command-line arguments
 */

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	अक्षर *p = &बाह्यal_cmdline_buffer;

	/*
	 * These will eventually be pulled in via either some hypervisor
	 * or devicetree description.  Hardwiring क्रम now.
	 */
	pcycle_freq_mhz = 600;
	thपढ़ो_freq_mhz = 100;
	sleep_clk_freq = 32000;

	/*
	 * Set up event bindings to handle exceptions and पूर्णांकerrupts.
	 */
	__vmsetvec(_K_VM_event_vector);

	prपूर्णांकk(KERN_INFO "PHYS_OFFSET=0x%08lx\n", PHYS_OFFSET);

	/*
	 * Simulator has a few dअगरferences from the hardware.
	 * For now, check uninitialized-but-mapped memory
	 * prior to invoking setup_arch_memory().
	 */
	अगर (*(पूर्णांक *)((अचिन्हित दीर्घ)_end + 8) == 0x1f1f1f1f)
		on_simulator = 1;
	अन्यथा
		on_simulator = 0;

	अगर (p[0] != '\0')
		strlcpy(boot_command_line, p, COMMAND_LINE_SIZE);
	अन्यथा
		strlcpy(boot_command_line, शेष_command_line,
			COMMAND_LINE_SIZE);

	/*
	 * boot_command_line and the value set up by setup_arch
	 * are both picked up by the init code. If no reason to
	 * make them dअगरferent, pass the same poपूर्णांकer back.
	 */
	strlcpy(cmd_line, boot_command_line, COMMAND_LINE_SIZE);
	*cmdline_p = cmd_line;

	parse_early_param();

	setup_arch_memory();

#अगर_घोषित CONFIG_SMP
	smp_start_cpus();
#पूर्ण_अगर
पूर्ण

/*
 * Functions क्रम dumping CPU info via /proc
 * Probably should move to kernel/proc.c or something.
 */
अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	वापस *pos < nr_cpu_ids ? (व्योम *)((अचिन्हित दीर्घ) *pos + 1) : शून्य;
पूर्ण

अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस c_start(m, pos);
पूर्ण

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

/*
 * Eventually this will dump inक्रमmation about
 * CPU properties like ISA level, TLB size, etc.
 */
अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक cpu = (अचिन्हित दीर्घ) v - 1;

#अगर_घोषित CONFIG_SMP
	अगर (!cpu_online(cpu))
		वापस 0;
#पूर्ण_अगर

	seq_म_लिखो(m, "processor\t: %d\n", cpu);
	seq_म_लिखो(m, "model name\t: Hexagon Virtual Machine\n");
	seq_म_लिखो(m, "BogoMips\t: %lu.%02lu\n",
		(loops_per_jअगरfy * HZ) / 500000,
		((loops_per_jअगरfy * HZ) / 5000) % 100);
	seq_म_लिखो(m, "\n");
	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start  = &c_start,
	.next   = &c_next,
	.stop   = &c_stop,
	.show   = &show_cpuinfo,
पूर्ण;
