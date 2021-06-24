<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SMP support क्रम PowerNV machines.
 *
 * Copyright 2011 IBM Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/vdso_datapage.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/runlatch.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/dbell.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/cpuidle.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/घातernv.h>

#समावेश "powernv.h"

#अगर_घोषित DEBUG
#समावेश <यंत्र/udbg.h>
#घोषणा DBG(fmt...) udbg_म_लिखो(fmt)
#अन्यथा
#घोषणा DBG(fmt...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल व्योम pnv_smp_setup_cpu(पूर्णांक cpu)
अणु
	/*
	 * P9 workaround क्रम CI vector load (see traps.c),
	 * enable the corresponding HMI पूर्णांकerrupt
	 */
	अगर (pvr_version_is(PVR_POWER9))
		mtspr(SPRN_HMEER, mfspr(SPRN_HMEER) | PPC_BIT(17));

	अगर (xive_enabled())
		xive_smp_setup_cpu();
	अन्यथा अगर (cpu != boot_cpuid)
		xics_setup_cpu();
पूर्ण

अटल पूर्णांक pnv_smp_kick_cpu(पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक pcpu;
	अचिन्हित दीर्घ start_here =
			__pa(ppc_function_entry(generic_secondary_smp_init));
	दीर्घ rc;
	uपूर्णांक8_t status;

	अगर (nr < 0 || nr >= nr_cpu_ids)
		वापस -EINVAL;

	pcpu = get_hard_smp_processor_id(nr);
	/*
	 * If we alपढ़ोy started or OPAL is not supported, we just
	 * kick the CPU via the PACA
	 */
	अगर (paca_ptrs[nr]->cpu_start || !firmware_has_feature(FW_FEATURE_OPAL))
		जाओ kick;

	/*
	 * At this poपूर्णांक, the CPU can either be spinning on the way in
	 * from kexec or be inside OPAL रुकोing to be started क्रम the
	 * first समय. OPAL v3 allows us to query OPAL to know अगर it
	 * has the CPUs, so we करो that
	 */
	rc = opal_query_cpu_status(pcpu, &status);
	अगर (rc != OPAL_SUCCESS) अणु
		pr_warn("OPAL Error %ld querying CPU %d state\n", rc, nr);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Alपढ़ोy started, just kick it, probably coming from
	 * kexec and spinning
	 */
	अगर (status == OPAL_THREAD_STARTED)
		जाओ kick;

	/*
	 * Available/inactive, let's kick it
	 */
	अगर (status == OPAL_THREAD_INACTIVE) अणु
		pr_devel("OPAL: Starting CPU %d (HW 0x%x)...\n", nr, pcpu);
		rc = opal_start_cpu(pcpu, start_here);
		अगर (rc != OPAL_SUCCESS) अणु
			pr_warn("OPAL Error %ld starting CPU %d\n", rc, nr);
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * An unavailable CPU (or any other unknown status)
		 * shouldn't be started. It should also
		 * not be in the possible map but currently it can
		 * happen
		 */
		pr_devel("OPAL: CPU %d (HW 0x%x) is unavailable"
			 " (status %d)...\n", nr, pcpu, status);
		वापस -ENODEV;
	पूर्ण

kick:
	वापस smp_generic_kick_cpu(nr);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

अटल पूर्णांक pnv_smp_cpu_disable(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	/* This is identical to pSeries... might consolidate by
	 * moving migrate_irqs_away to a ppc_md with शेष to
	 * the generic fixup_irqs. --BenH.
	 */
	set_cpu_online(cpu, false);
	vdso_data->processorCount--;
	अगर (cpu == boot_cpuid)
		boot_cpuid = cpumask_any(cpu_online_mask);
	अगर (xive_enabled())
		xive_smp_disable_cpu();
	अन्यथा
		xics_migrate_irqs_away();

	cleanup_cpu_mmu_context();

	वापस 0;
पूर्ण

अटल व्योम pnv_flush_पूर्णांकerrupts(व्योम)
अणु
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		अगर (xive_enabled())
			xive_flush_पूर्णांकerrupt();
		अन्यथा
			icp_opal_flush_पूर्णांकerrupt();
	पूर्ण अन्यथा अणु
		icp_native_flush_पूर्णांकerrupt();
	पूर्ण
पूर्ण

अटल व्योम pnv_cpu_offline_self(व्योम)
अणु
	अचिन्हित दीर्घ srr1, unexpected_mask, wmask;
	अचिन्हित पूर्णांक cpu;
	u64 lpcr_val;

	/* Standard hot unplug procedure */

	idle_task_निकास();
	cpu = smp_processor_id();
	DBG("CPU%d offline\n", cpu);
	generic_set_cpu_dead(cpu);
	smp_wmb();

	wmask = SRR1_WAKEMASK;
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S))
		wmask = SRR1_WAKEMASK_P8;

	/*
	 * This turns the irq soft-disabled state we're called with, पूर्णांकo a
	 * hard-disabled state with pending irq_happened पूर्णांकerrupts cleared.
	 *
	 * PACA_IRQ_DEC   - Decrementer should be ignored.
	 * PACA_IRQ_HMI   - Can be ignored, processing is करोne in real mode.
	 * PACA_IRQ_DBELL, EE, PMI - Unexpected.
	 */
	hard_irq_disable();
	अगर (generic_check_cpu_restart(cpu))
		जाओ out;

	unexpected_mask = ~(PACA_IRQ_DEC | PACA_IRQ_HMI | PACA_IRQ_HARD_DIS);
	अगर (local_paca->irq_happened & unexpected_mask) अणु
		अगर (local_paca->irq_happened & PACA_IRQ_EE)
			pnv_flush_पूर्णांकerrupts();
		DBG("CPU%d Unexpected exit while offline irq_happened=%lx!\n",
				cpu, local_paca->irq_happened);
	पूर्ण
	local_paca->irq_happened = PACA_IRQ_HARD_DIS;

	/*
	 * We करोn't want to take decrementer पूर्णांकerrupts जबतक we are
	 * offline, so clear LPCR:PECE1. We keep PECE2 (and
	 * LPCR_PECE_HVEE on P9) enabled so as to let IPIs in.
	 *
	 * If the CPU माला_लो woken up by a special wakeup, ensure that
	 * the SLW engine sets LPCR with decrementer bit cleared, अन्यथा
	 * the CPU will come back to the kernel due to a spurious
	 * wakeup.
	 */
	lpcr_val = mfspr(SPRN_LPCR) & ~(u64)LPCR_PECE1;
	pnv_program_cpu_hotplug_lpcr(cpu, lpcr_val);

	जबतक (!generic_check_cpu_restart(cpu)) अणु
		/*
		 * Clear IPI flag, since we करोn't handle IPIs जबतक
		 * offline, except क्रम those when changing micro-thपढ़ोing
		 * mode, which are handled explicitly below, and those
		 * क्रम coming online, which are handled via
		 * generic_check_cpu_restart() calls.
		 */
		kvmppc_clear_host_ipi(cpu);

		srr1 = pnv_cpu_offline(cpu);

		WARN_ON_ONCE(!irqs_disabled());
		WARN_ON(lazy_irq_pending());

		/*
		 * If the SRR1 value indicates that we woke up due to
		 * an बाह्यal पूर्णांकerrupt, then clear the पूर्णांकerrupt.
		 * We clear the पूर्णांकerrupt beक्रमe checking क्रम the
		 * reason, so as to aव्योम a race where we wake up क्रम
		 * some other reason, find nothing and clear the पूर्णांकerrupt
		 * just as some other cpu is sending us an पूर्णांकerrupt.
		 * If we वापसed from घातer7_nap as a result of
		 * having finished executing in a KVM guest, then srr1
		 * contains 0.
		 */
		अगर (((srr1 & wmask) == SRR1_WAKEEE) ||
		    ((srr1 & wmask) == SRR1_WAKEHVI)) अणु
			pnv_flush_पूर्णांकerrupts();
		पूर्ण अन्यथा अगर ((srr1 & wmask) == SRR1_WAKEHDBELL) अणु
			अचिन्हित दीर्घ msg = PPC_DBELL_TYPE(PPC_DBELL_SERVER);
			यंत्र अस्थिर(PPC_MSGCLR(%0) : : "r" (msg));
		पूर्ण अन्यथा अगर ((srr1 & wmask) == SRR1_WAKERESET) अणु
			irq_set_pending_from_srr1(srr1);
			/* Does not वापस */
		पूर्ण

		smp_mb();

		/*
		 * For kdump kernels, we process the ipi and jump to
		 * crash_ipi_callback
		 */
		अगर (kdump_in_progress()) अणु
			/*
			 * If we got to this poपूर्णांक, we've not used
			 * NMI's, otherwise we would have gone
			 * via the SRR1_WAKERESET path. We are
			 * using regular IPI's क्रम waking up offline
			 * thपढ़ोs.
			 */
			काष्ठा pt_regs regs;

			ppc_save_regs(&regs);
			crash_ipi_callback(&regs);
			/* Does not वापस */
		पूर्ण

		अगर (cpu_core_split_required())
			जारी;

		अगर (srr1 && !generic_check_cpu_restart(cpu))
			DBG("CPU%d Unexpected exit while offline srr1=%lx!\n",
					cpu, srr1);

	पूर्ण

	/*
	 * Re-enable decrementer पूर्णांकerrupts in LPCR.
	 *
	 * Further, we want stop states to be woken up by decrementer
	 * क्रम non-hotplug हालs. So program the LPCR via stop api as
	 * well.
	 */
	lpcr_val = mfspr(SPRN_LPCR) | (u64)LPCR_PECE1;
	pnv_program_cpu_hotplug_lpcr(cpu, lpcr_val);
out:
	DBG("CPU%d coming online...\n", cpu);
पूर्ण

#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

अटल पूर्णांक pnv_cpu_bootable(अचिन्हित पूर्णांक nr)
अणु
	/*
	 * Starting with POWER8, the subcore logic relies on all thपढ़ोs of a
	 * core being booted so that they can participate in split mode
	 * चयनes. So on those machines we ignore the smt_enabled_at_boot
	 * setting (smt-enabled on the kernel command line).
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस 1;

	वापस smp_generic_cpu_bootable(nr);
पूर्ण

अटल पूर्णांक pnv_smp_prepare_cpu(पूर्णांक cpu)
अणु
	अगर (xive_enabled())
		वापस xive_smp_prepare_cpu(cpu);
	वापस 0;
पूर्ण

/* Cause IPI as setup by the पूर्णांकerrupt controller (xics or xive) */
अटल व्योम (*ic_cause_ipi)(पूर्णांक cpu);

अटल व्योम pnv_cause_ipi(पूर्णांक cpu)
अणु
	अगर (करोorbell_try_core_ipi(cpu))
		वापस;

	ic_cause_ipi(cpu);
पूर्ण

अटल व्योम __init pnv_smp_probe(व्योम)
अणु
	अगर (xive_enabled())
		xive_smp_probe();
	अन्यथा
		xics_smp_probe();

	अगर (cpu_has_feature(CPU_FTR_DBELL)) अणु
		ic_cause_ipi = smp_ops->cause_ipi;
		WARN_ON(!ic_cause_ipi);

		अगर (cpu_has_feature(CPU_FTR_ARCH_300))
			smp_ops->cause_ipi = करोorbell_global_ipi;
		अन्यथा
			smp_ops->cause_ipi = pnv_cause_ipi;
	पूर्ण
पूर्ण

अटल पूर्णांक pnv_प्रणाली_reset_exception(काष्ठा pt_regs *regs)
अणु
	अगर (smp_handle_nmi_ipi(regs))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक pnv_cause_nmi_ipi(पूर्णांक cpu)
अणु
	पूर्णांक64_t rc;

	अगर (cpu >= 0) अणु
		पूर्णांक h = get_hard_smp_processor_id(cpu);

		अगर (opal_check_token(OPAL_QUIESCE))
			opal_quiesce(QUIESCE_HOLD, h);

		rc = opal_संकेत_प्रणाली_reset(h);

		अगर (opal_check_token(OPAL_QUIESCE))
			opal_quiesce(QUIESCE_RESUME, h);

		अगर (rc != OPAL_SUCCESS)
			वापस 0;
		वापस 1;

	पूर्ण अन्यथा अगर (cpu == NMI_IPI_ALL_OTHERS) अणु
		bool success = true;
		पूर्णांक c;

		अगर (opal_check_token(OPAL_QUIESCE))
			opal_quiesce(QUIESCE_HOLD, -1);

		/*
		 * We करो not use broadcasts (yet), because it's not clear
		 * exactly what semantics Linux wants or the firmware should
		 * provide.
		 */
		क्रम_each_online_cpu(c) अणु
			अगर (c == smp_processor_id())
				जारी;

			rc = opal_संकेत_प्रणाली_reset(
						get_hard_smp_processor_id(c));
			अगर (rc != OPAL_SUCCESS)
				success = false;
		पूर्ण

		अगर (opal_check_token(OPAL_QUIESCE))
			opal_quiesce(QUIESCE_RESUME, -1);

		अगर (success)
			वापस 1;

		/*
		 * Caller will fall back to करोorbells, which may pick
		 * up the reमुख्यders.
		 */
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा smp_ops_t pnv_smp_ops = अणु
	.message_pass	= शून्य, /* Use smp_muxed_ipi_message_pass */
	.cause_ipi	= शून्य,	/* Filled at runसमय by pnv_smp_probe() */
	.cause_nmi_ipi	= शून्य,
	.probe		= pnv_smp_probe,
	.prepare_cpu	= pnv_smp_prepare_cpu,
	.kick_cpu	= pnv_smp_kick_cpu,
	.setup_cpu	= pnv_smp_setup_cpu,
	.cpu_bootable	= pnv_cpu_bootable,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_disable	= pnv_smp_cpu_disable,
	.cpu_die	= generic_cpu_die,
	.cpu_offline_self = pnv_cpu_offline_self,
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */
पूर्ण;

/* This is called very early during platक्रमm setup_arch */
व्योम __init pnv_smp_init(व्योम)
अणु
	अगर (opal_check_token(OPAL_SIGNAL_SYSTEM_RESET)) अणु
		ppc_md.प्रणाली_reset_exception = pnv_प्रणाली_reset_exception;
		pnv_smp_ops.cause_nmi_ipi = pnv_cause_nmi_ipi;
	पूर्ण
	smp_ops = &pnv_smp_ops;

#अगर_घोषित CONFIG_HOTPLUG_CPU
#अगर_घोषित CONFIG_KEXEC_CORE
	crash_wake_offline = 1;
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण
