<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SMP support क्रम BPA machines.
 *
 * Dave Engebretsen, Peter Bergner, and
 * Mike Corrigan अणुengebret|bergner|mikecपूर्ण@us.ibm.com
 *
 * Plus various changes from other IBM teams...
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/cache.h>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/cpu.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/code-patching.h>

#समावेश "interrupt.h"
#समावेश <यंत्र/udbg.h>

#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) udbg_म_लिखो(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

/*
 * The Primary thपढ़ो of each non-boot processor was started from the OF client
 * पूर्णांकerface by prom_hold_cpus and is spinning on secondary_hold_spinloop.
 */
अटल cpumask_t of_spin_map;

/**
 * smp_startup_cpu() - start the given cpu
 *
 * At boot समय, there is nothing to करो क्रम primary thपढ़ोs which were
 * started from Open Firmware.  For anything अन्यथा, call RTAS with the
 * appropriate start location.
 *
 * Returns:
 *	0	- failure
 *	1	- success
 */
अटल अंतरभूत पूर्णांक smp_startup_cpu(अचिन्हित पूर्णांक lcpu)
अणु
	पूर्णांक status;
	अचिन्हित दीर्घ start_here =
			__pa(ppc_function_entry(generic_secondary_smp_init));
	अचिन्हित पूर्णांक pcpu;
	पूर्णांक start_cpu;

	अगर (cpumask_test_cpu(lcpu, &of_spin_map))
		/* Alपढ़ोy started by OF and sitting in spin loop */
		वापस 1;

	pcpu = get_hard_smp_processor_id(lcpu);

	/* Fixup atomic count: it निकासed inside IRQ handler. */
	task_thपढ़ो_info(paca_ptrs[lcpu]->__current)->preempt_count	= 0;

	/*
	 * If the RTAS start-cpu token करोes not exist then presume the
	 * cpu is alपढ़ोy spinning.
	 */
	start_cpu = rtas_token("start-cpu");
	अगर (start_cpu == RTAS_UNKNOWN_SERVICE)
		वापस 1;

	status = rtas_call(start_cpu, 3, 1, शून्य, pcpu, start_here, lcpu);
	अगर (status != 0) अणु
		prपूर्णांकk(KERN_ERR "start-cpu failed: %i\n", status);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम smp_cell_setup_cpu(पूर्णांक cpu)
अणु
	अगर (cpu != boot_cpuid)
		iic_setup_cpu();

	/*
	 * change शेष DABRX to allow user watchpoपूर्णांकs
	 */
	mtspr(SPRN_DABRX, DABRX_KERNEL | DABRX_USER);
पूर्ण

अटल पूर्णांक smp_cell_kick_cpu(पूर्णांक nr)
अणु
	अगर (nr < 0 || nr >= nr_cpu_ids)
		वापस -EINVAL;

	अगर (!smp_startup_cpu(nr))
		वापस -ENOENT;

	/*
	 * The processor is currently spinning, रुकोing क्रम the
	 * cpu_start field to become non-zero After we set cpu_start,
	 * the processor will जारी on to secondary_start
	 */
	paca_ptrs[nr]->cpu_start = 1;

	वापस 0;
पूर्ण

अटल काष्ठा smp_ops_t bpa_iic_smp_ops = अणु
	.message_pass	= iic_message_pass,
	.probe		= iic_request_IPIs,
	.kick_cpu	= smp_cell_kick_cpu,
	.setup_cpu	= smp_cell_setup_cpu,
	.cpu_bootable	= smp_generic_cpu_bootable,
पूर्ण;

/* This is called very early */
व्योम __init smp_init_cell(व्योम)
अणु
	पूर्णांक i;

	DBG(" -> smp_init_cell()\n");

	smp_ops = &bpa_iic_smp_ops;

	/* Mark thपढ़ोs which are still spinning in hold loops. */
	अगर (cpu_has_feature(CPU_FTR_SMT)) अणु
		क्रम_each_present_cpu(i) अणु
			अगर (cpu_thपढ़ो_in_core(i) == 0)
				cpumask_set_cpu(i, &of_spin_map);
		पूर्ण
	पूर्ण अन्यथा
		cpumask_copy(&of_spin_map, cpu_present_mask);

	cpumask_clear_cpu(boot_cpuid, &of_spin_map);

	/* Non-lpar has additional take/give समयbase */
	अगर (rtas_token("freeze-time-base") != RTAS_UNKNOWN_SERVICE) अणु
		smp_ops->give_समयbase = rtas_give_समयbase;
		smp_ops->take_समयbase = rtas_take_समयbase;
	पूर्ण

	DBG(" <- smp_init_cell()\n");
पूर्ण
