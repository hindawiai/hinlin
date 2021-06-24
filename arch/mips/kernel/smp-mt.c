<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2004, 05, 06 MIPS Technologies, Inc.
 *    Elizabeth Clarke (beth@mips.com)
 *    Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2006 Ralf Baechle (ralf@linux-mips.org)
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/compiler.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/smp.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/hardirq.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mipsmtregs.h>
#समावेश <यंत्र/mips_mt.h>
#समावेश <यंत्र/mips-cps.h>

अटल व्योम __init smvp_copy_vpe_config(व्योम)
अणु
	ग_लिखो_vpe_c0_status(
		(पढ़ो_c0_status() & ~(ST0_IM | ST0_IE | ST0_KSU)) | ST0_CU0);

	/* set config to be the same as vpe0, particularly kseg0 coherency alg */
	ग_लिखो_vpe_c0_config( पढ़ो_c0_config());

	/* make sure there are no software पूर्णांकerrupts pending */
	ग_लिखो_vpe_c0_cause(0);

	/* Propagate Config7 */
	ग_लिखो_vpe_c0_config7(पढ़ो_c0_config7());

	ग_लिखो_vpe_c0_count(पढ़ो_c0_count());
पूर्ण

अटल अचिन्हित पूर्णांक __init smvp_vpe_init(अचिन्हित पूर्णांक tc, अचिन्हित पूर्णांक mvpconf0,
	अचिन्हित पूर्णांक ncpu)
अणु
	अगर (tc > ((mvpconf0 & MVPCONF0_PVPE) >> MVPCONF0_PVPE_SHIFT))
		वापस ncpu;

	/* Deactivate all but VPE 0 */
	अगर (tc != 0) अणु
		अचिन्हित दीर्घ पंचांगp = पढ़ो_vpe_c0_vpeconf0();

		पंचांगp &= ~VPECONF0_VPA;

		/* master VPE */
		पंचांगp |= VPECONF0_MVP;
		ग_लिखो_vpe_c0_vpeconf0(पंचांगp);

		/* Record this as available CPU */
		set_cpu_possible(tc, true);
		set_cpu_present(tc, true);
		__cpu_number_map[tc]	= ++ncpu;
		__cpu_logical_map[ncpu] = tc;
	पूर्ण

	/* Disable multi-thपढ़ोing with TC's */
	ग_लिखो_vpe_c0_vpecontrol(पढ़ो_vpe_c0_vpecontrol() & ~VPECONTROL_TE);

	अगर (tc != 0)
		smvp_copy_vpe_config();

	cpu_set_vpe_id(&cpu_data[ncpu], tc);

	वापस ncpu;
पूर्ण

अटल व्योम __init smvp_tc_init(अचिन्हित पूर्णांक tc, अचिन्हित पूर्णांक mvpconf0)
अणु
	अचिन्हित दीर्घ पंचांगp;

	अगर (!tc)
		वापस;

	/* bind a TC to each VPE, May as well put all excess TC's
	   on the last VPE */
	अगर (tc >= (((mvpconf0 & MVPCONF0_PVPE) >> MVPCONF0_PVPE_SHIFT)+1))
		ग_लिखो_tc_c0_tcbind(पढ़ो_tc_c0_tcbind() | ((mvpconf0 & MVPCONF0_PVPE) >> MVPCONF0_PVPE_SHIFT));
	अन्यथा अणु
		ग_लिखो_tc_c0_tcbind(पढ़ो_tc_c0_tcbind() | tc);

		/* and set XTC */
		ग_लिखो_vpe_c0_vpeconf0(पढ़ो_vpe_c0_vpeconf0() | (tc << VPECONF0_XTC_SHIFT));
	पूर्ण

	पंचांगp = पढ़ो_tc_c0_tcstatus();

	/* mark not allocated and not dynamically allocatable */
	पंचांगp &= ~(TCSTATUS_A | TCSTATUS_DA);
	पंचांगp |= TCSTATUS_IXMT;		/* पूर्णांकerrupt exempt */
	ग_लिखो_tc_c0_tcstatus(पंचांगp);

	ग_लिखो_tc_c0_tchalt(TCHALT_H);
पूर्ण

अटल व्योम vsmp_init_secondary(व्योम)
अणु
	/* This is Malta specअगरic: IPI,perक्रमmance and समयr पूर्णांकerrupts */
	अगर (mips_gic_present())
		change_c0_status(ST0_IM, STATUSF_IP2 | STATUSF_IP3 |
					 STATUSF_IP4 | STATUSF_IP5 |
					 STATUSF_IP6 | STATUSF_IP7);
	अन्यथा
		change_c0_status(ST0_IM, STATUSF_IP0 | STATUSF_IP1 |
					 STATUSF_IP6 | STATUSF_IP7);
पूर्ण

अटल व्योम vsmp_smp_finish(व्योम)
अणु
	/* CDFIXME: हटाओ this? */
	ग_लिखो_c0_compare(पढ़ो_c0_count() + (8* mips_hpt_frequency/HZ));

#अगर_घोषित CONFIG_MIPS_MT_FPAFF
	/* If we have an FPU, enroll ourselves in the FPU-full mask */
	अगर (cpu_has_fpu)
		cpumask_set_cpu(smp_processor_id(), &mt_fpu_cpumask);
#पूर्ण_अगर /* CONFIG_MIPS_MT_FPAFF */

	local_irq_enable();
पूर्ण

/*
 * Setup the PC, SP, and GP of a secondary processor and start it
 * running!
 * smp_bootstrap is the place to resume from
 * __KSTK_TOS(idle) is apparently the stack poपूर्णांकer
 * (अचिन्हित दीर्घ)idle->thपढ़ो_info the gp
 * assumes a 1:1 mapping of TC => VPE
 */
अटल पूर्णांक vsmp_boot_secondary(पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	काष्ठा thपढ़ो_info *gp = task_thपढ़ो_info(idle);
	dvpe();
	set_c0_mvpcontrol(MVPCONTROL_VPC);

	settc(cpu);

	/* restart */
	ग_लिखो_tc_c0_tcrestart((अचिन्हित दीर्घ)&smp_bootstrap);

	/* enable the tc this vpe/cpu will be running */
	ग_लिखो_tc_c0_tcstatus((पढ़ो_tc_c0_tcstatus() & ~TCSTATUS_IXMT) | TCSTATUS_A);

	ग_लिखो_tc_c0_tchalt(0);

	/* enable the VPE */
	ग_लिखो_vpe_c0_vpeconf0(पढ़ो_vpe_c0_vpeconf0() | VPECONF0_VPA);

	/* stack poपूर्णांकer */
	ग_लिखो_tc_gpr_sp( __KSTK_TOS(idle));

	/* global poपूर्णांकer */
	ग_लिखो_tc_gpr_gp((अचिन्हित दीर्घ)gp);

	flush_icache_range((अचिन्हित दीर्घ)gp,
			   (अचिन्हित दीर्घ)(gp + माप(काष्ठा thपढ़ो_info)));

	/* finally out of configuration and पूर्णांकo chaos */
	clear_c0_mvpcontrol(MVPCONTROL_VPC);

	evpe(EVPE_ENABLE);

	वापस 0;
पूर्ण

/*
 * Common setup beक्रमe any secondaries are started
 * Make sure all CPU's are in a sensible state beक्रमe we boot any of the
 * secondaries
 */
अटल व्योम __init vsmp_smp_setup(व्योम)
अणु
	अचिन्हित पूर्णांक mvpconf0, ntc, tc, ncpu = 0;
	अचिन्हित पूर्णांक nvpe;

#अगर_घोषित CONFIG_MIPS_MT_FPAFF
	/* If we have an FPU, enroll ourselves in the FPU-full mask */
	अगर (cpu_has_fpu)
		cpumask_set_cpu(0, &mt_fpu_cpumask);
#पूर्ण_अगर /* CONFIG_MIPS_MT_FPAFF */
	अगर (!cpu_has_mipsmt)
		वापस;

	/* disable MT so we can configure */
	dvpe();
	dmt();

	/* Put MVPE's into 'configuration state' */
	set_c0_mvpcontrol(MVPCONTROL_VPC);

	mvpconf0 = पढ़ो_c0_mvpconf0();
	ntc = (mvpconf0 & MVPCONF0_PTC) >> MVPCONF0_PTC_SHIFT;

	nvpe = ((mvpconf0 & MVPCONF0_PVPE) >> MVPCONF0_PVPE_SHIFT) + 1;
	smp_num_siblings = nvpe;

	/* we'll always have more TC's than VPE's, so loop setting everything
	   to a sensible state */
	क्रम (tc = 0; tc <= ntc; tc++) अणु
		settc(tc);

		smvp_tc_init(tc, mvpconf0);
		ncpu = smvp_vpe_init(tc, mvpconf0, ncpu);
	पूर्ण

	/* Release config state */
	clear_c0_mvpcontrol(MVPCONTROL_VPC);

	/* We'll रुको until starting the secondaries beक्रमe starting MVPE */

	prपूर्णांकk(KERN_INFO "Detected %i available secondary CPU(s)\n", ncpu);
पूर्ण

अटल व्योम __init vsmp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	mips_mt_set_cpuoptions();
पूर्ण

स्थिर काष्ठा plat_smp_ops vsmp_smp_ops = अणु
	.send_ipi_single	= mips_smp_send_ipi_single,
	.send_ipi_mask		= mips_smp_send_ipi_mask,
	.init_secondary		= vsmp_init_secondary,
	.smp_finish		= vsmp_smp_finish,
	.boot_secondary		= vsmp_boot_secondary,
	.smp_setup		= vsmp_smp_setup,
	.prepare_cpus		= vsmp_prepare_cpus,
पूर्ण;

