<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SMP support क्रम pSeries machines.
 *
 * Dave Engebretsen, Peter Bergner, and
 * Mike Corrigan अणुengebret|bergner|mikecपूर्ण@us.ibm.com
 *
 * Plus various changes from other IBM teams...
 */


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
#समावेश <यंत्र/vdso_datapage.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/dbell.h>
#समावेश <यंत्र/plpar_wrappers.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/svm.h>
#समावेश <यंत्र/kvm_guest.h>

#समावेश "pseries.h"

/*
 * The Primary thपढ़ो of each non-boot processor was started from the OF client
 * पूर्णांकerface by prom_hold_cpus and is spinning on secondary_hold_spinloop.
 */
अटल cpumask_var_t of_spin_mask;

/* Query where a cpu is now.  Return codes #घोषणाd in plpar_wrappers.h */
पूर्णांक smp_query_cpu_stopped(अचिन्हित पूर्णांक pcpu)
अणु
	पूर्णांक cpu_status, status;
	पूर्णांक qcss_tok = rtas_token("query-cpu-stopped-state");

	अगर (qcss_tok == RTAS_UNKNOWN_SERVICE) अणु
		prपूर्णांकk_once(KERN_INFO
			"Firmware doesn't support query-cpu-stopped-state\n");
		वापस QCSS_HARDWARE_ERROR;
	पूर्ण

	status = rtas_call(qcss_tok, 1, 2, &cpu_status, pcpu);
	अगर (status != 0) अणु
		prपूर्णांकk(KERN_ERR
		       "RTAS query-cpu-stopped-state failed: %i\n", status);
		वापस status;
	पूर्ण

	वापस cpu_status;
पूर्ण

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

	अगर (cpumask_test_cpu(lcpu, of_spin_mask))
		/* Alपढ़ोy started by OF and sitting in spin loop */
		वापस 1;

	pcpu = get_hard_smp_processor_id(lcpu);

	/* Check to see अगर the CPU out of FW alपढ़ोy क्रम kexec */
	अगर (smp_query_cpu_stopped(pcpu) == QCSS_NOT_STOPPED)अणु
		cpumask_set_cpu(lcpu, of_spin_mask);
		वापस 1;
	पूर्ण

	/* Fixup atomic count: it निकासed inside IRQ handler. */
	task_thपढ़ो_info(paca_ptrs[lcpu]->__current)->preempt_count	= 0;

	/* 
	 * If the RTAS start-cpu token करोes not exist then presume the
	 * cpu is alपढ़ोy spinning.
	 */
	start_cpu = rtas_token("start-cpu");
	अगर (start_cpu == RTAS_UNKNOWN_SERVICE)
		वापस 1;

	status = rtas_call(start_cpu, 3, 1, शून्य, pcpu, start_here, pcpu);
	अगर (status != 0) अणु
		prपूर्णांकk(KERN_ERR "start-cpu failed: %i\n", status);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम smp_setup_cpu(पूर्णांक cpu)
अणु
	अगर (xive_enabled())
		xive_smp_setup_cpu();
	अन्यथा अगर (cpu != boot_cpuid)
		xics_setup_cpu();

	अगर (firmware_has_feature(FW_FEATURE_SPLPAR))
		vpa_init(cpu);

	cpumask_clear_cpu(cpu, of_spin_mask);
पूर्ण

अटल पूर्णांक smp_pSeries_kick_cpu(पूर्णांक nr)
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

अटल पूर्णांक pseries_smp_prepare_cpu(पूर्णांक cpu)
अणु
	अगर (xive_enabled())
		वापस xive_smp_prepare_cpu(cpu);
	वापस 0;
पूर्ण

/* Cause IPI as setup by the पूर्णांकerrupt controller (xics or xive) */
अटल व्योम (*ic_cause_ipi)(पूर्णांक cpu) __ro_after_init;

/* Use msgsndp करोorbells target is a sibling, अन्यथा use पूर्णांकerrupt controller */
अटल व्योम dbell_or_ic_cause_ipi(पूर्णांक cpu)
अणु
	अगर (करोorbell_try_core_ipi(cpu))
		वापस;

	ic_cause_ipi(cpu);
पूर्ण

अटल पूर्णांक pseries_cause_nmi_ipi(पूर्णांक cpu)
अणु
	पूर्णांक hwcpu;

	अगर (cpu == NMI_IPI_ALL_OTHERS) अणु
		hwcpu = H_SIGNAL_SYS_RESET_ALL_OTHERS;
	पूर्ण अन्यथा अणु
		अगर (cpu < 0) अणु
			WARN_ONCE(true, "incorrect cpu parameter %d", cpu);
			वापस 0;
		पूर्ण

		hwcpu = get_hard_smp_processor_id(cpu);
	पूर्ण

	अगर (plpar_संकेत_sys_reset(hwcpu) == H_SUCCESS)
		वापस 1;

	वापस 0;
पूर्ण

अटल __init व्योम pSeries_smp_probe(व्योम)
अणु
	अगर (xive_enabled())
		xive_smp_probe();
	अन्यथा
		xics_smp_probe();

	/* No करोorbell facility, must use the पूर्णांकerrupt controller क्रम IPIs */
	अगर (!cpu_has_feature(CPU_FTR_DBELL))
		वापस;

	/* Doorbells can only be used क्रम IPIs between SMT siblings */
	अगर (!cpu_has_feature(CPU_FTR_SMT))
		वापस;

	अगर (check_kvm_guest()) अणु
		/*
		 * KVM emulates करोorbells by disabling FSCR[MSGP] so msgsndp
		 * faults to the hypervisor which then पढ़ोs the inकाष्ठाion
		 * from guest memory, which tends to be slower than using XIVE.
		 */
		अगर (xive_enabled())
			वापस;

		/*
		 * XICS hcalls aren't as fast, so we can use msgsndp (which
		 * also helps exercise KVM emulation), however KVM can't
		 * emulate secure guests because it can't पढ़ो the inकाष्ठाion
		 * out of their memory.
		 */
		अगर (is_secure_guest())
			वापस;
	पूर्ण

	/*
	 * Under PowerVM, FSCR[MSGP] is enabled as guest vCPU siblings are
	 * gang scheduled on the same physical core, so करोorbells are always
	 * faster than the पूर्णांकerrupt controller, and they can be used by
	 * secure guests.
	 */

	ic_cause_ipi = smp_ops->cause_ipi;
	smp_ops->cause_ipi = dbell_or_ic_cause_ipi;
पूर्ण

अटल काष्ठा smp_ops_t pseries_smp_ops = अणु
	.message_pass	= शून्य,	/* Use smp_muxed_ipi_message_pass */
	.cause_ipi	= शून्य,	/* Filled at runसमय by pSeries_smp_probe() */
	.cause_nmi_ipi	= pseries_cause_nmi_ipi,
	.probe		= pSeries_smp_probe,
	.prepare_cpu	= pseries_smp_prepare_cpu,
	.kick_cpu	= smp_pSeries_kick_cpu,
	.setup_cpu	= smp_setup_cpu,
	.cpu_bootable	= smp_generic_cpu_bootable,
पूर्ण;

/* This is called very early */
व्योम __init smp_init_pseries(व्योम)
अणु
	पूर्णांक i;

	pr_debug(" -> smp_init_pSeries()\n");
	smp_ops = &pseries_smp_ops;

	alloc_booपंचांगem_cpumask_var(&of_spin_mask);

	/*
	 * Mark thपढ़ोs which are still spinning in hold loops
	 *
	 * We know prom_init will not have started them अगर RTAS supports
	 * query-cpu-stopped-state.
	 */
	अगर (rtas_token("query-cpu-stopped-state") == RTAS_UNKNOWN_SERVICE) अणु
		अगर (cpu_has_feature(CPU_FTR_SMT)) अणु
			क्रम_each_present_cpu(i) अणु
				अगर (cpu_thपढ़ो_in_core(i) == 0)
					cpumask_set_cpu(i, of_spin_mask);
			पूर्ण
		पूर्ण अन्यथा
			cpumask_copy(of_spin_mask, cpu_present_mask);

		cpumask_clear_cpu(boot_cpuid, of_spin_mask);
	पूर्ण

	/* Non-lpar has additional take/give समयbase */
	अगर (rtas_token("freeze-time-base") != RTAS_UNKNOWN_SERVICE) अणु
		smp_ops->give_समयbase = rtas_give_समयbase;
		smp_ops->take_समयbase = rtas_take_समयbase;
	पूर्ण

	pr_debug(" <- smp_init_pSeries()\n");
पूर्ण
