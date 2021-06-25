<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 *
 * Copyright (C) 2000 - 2001 by Kanoj Sarcar (kanoj@sgi.com)
 * Copyright (C) 2000 - 2001 by Silicon Graphics, Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/cpumask.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/sn/agent.h>
#समावेश <यंत्र/sn/types.h>
#समावेश <यंत्र/sn/klconfig.h>
#समावेश <यंत्र/sn/ioc3.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/sn/gda.h>
#समावेश <यंत्र/sn/पूर्णांकr.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/sn/launch.h>
#समावेश <यंत्र/sn/mapped_kernel.h>

#समावेश "ip27-common.h"

#घोषणा CPU_NONE		(cpuid_t)-1

अटल DECLARE_BITMAP(hub_init_mask, MAX_NUMNODES);
nasid_t master_nasid = INVALID_NASID;

काष्ठा cpuinfo_ip27 sn_cpu_info[NR_CPUS];
EXPORT_SYMBOL_GPL(sn_cpu_info);

अटल व्योम per_hub_init(nasid_t nasid)
अणु
	काष्ठा hub_data *hub = hub_data(nasid);

	cpumask_set_cpu(smp_processor_id(), &hub->h_cpus);

	अगर (test_and_set_bit(nasid, hub_init_mask))
		वापस;
	/*
	 * Set CRB समयout at 5ms, (< PI समयout of 10ms)
	 */
	REMOTE_HUB_S(nasid, IIO_ICTP, 0x800);
	REMOTE_HUB_S(nasid, IIO_ICTO, 0xff);

	hub_rtc_init(nasid);

	अगर (nasid) अणु
		/* copy exception handlers from first node to current node */
		स_नकल((व्योम *)NODE_OFFSET_TO_K0(nasid, 0),
		       (व्योम *)CKSEG0, 0x200);
		__flush_cache_all();
		/* चयन to node local exception handlers */
		REMOTE_HUB_S(nasid, PI_CALIAS_SIZE, PI_CALIAS_SIZE_8K);
	पूर्ण
पूर्ण

व्योम per_cpu_init(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	nasid_t nasid = get_nasid();

	clear_c0_status(ST0_IM);

	per_hub_init(nasid);

	pr_info("CPU %d clock is %dMHz.\n", cpu, sn_cpu_info[cpu].p_speed);

	install_ipi();

	/* Install our NMI handler अगर symmon hasn't installed one. */
	install_cpu_nmi_handler(cputoslice(cpu));

	enable_percpu_irq(IP27_HUB_PEND0_IRQ, IRQ_TYPE_NONE);
	enable_percpu_irq(IP27_HUB_PEND1_IRQ, IRQ_TYPE_NONE);
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	u64 p, e, n_mode;
	nasid_t nid;

	रेजिस्टर_smp_ops(&ip27_smp_ops);

	ip27_reboot_setup();

	/*
	 * hub_rtc init and cpu घड़ी पूर्णांकr enabled क्रम later calibrate_delay.
	 */
	nid = get_nasid();
	prपूर्णांकk("IP27: Running on node %d.\n", nid);

	p = LOCAL_HUB_L(PI_CPU_PRESENT_A) & 1;
	e = LOCAL_HUB_L(PI_CPU_ENABLE_A) & 1;
	prपूर्णांकk("Node %d has %s primary CPU%s.\n", nid,
	       p ? "a" : "no",
	       e ? ", CPU is running" : "");

	p = LOCAL_HUB_L(PI_CPU_PRESENT_B) & 1;
	e = LOCAL_HUB_L(PI_CPU_ENABLE_B) & 1;
	prपूर्णांकk("Node %d has %s secondary CPU%s.\n", nid,
	       p ? "a" : "no",
	       e ? ", CPU is running" : "");

	/*
	 * Try to catch kernel missconfigurations and give user an
	 * indication what option to select.
	 */
	n_mode = LOCAL_HUB_L(NI_STATUS_REV_ID) & NSRI_MORENODES_MASK;
	prपूर्णांकk("Machine is in %c mode.\n", n_mode ? 'N' : 'M');
#अगर_घोषित CONFIG_SGI_SN_N_MODE
	अगर (!n_mode)
		panic("Kernel compiled for M mode.");
#अन्यथा
	अगर (n_mode)
		panic("Kernel compiled for N mode.");
#पूर्ण_अगर

	ioport_resource.start = 0;
	ioport_resource.end = ~0UL;
	set_io_port_base(IO_BASE);
पूर्ण

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस "SGI Origin";
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	prom_init_cmdline(fw_arg0, (LONG *)fw_arg1);
	prom_meminit();
पूर्ण

