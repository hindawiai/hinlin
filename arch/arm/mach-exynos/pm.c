<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2011-2014 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
//
// Exynos - Power Management support
//
// Based on arch/arm/mach-s3c2410/pm.c
// Copyright (c) 2006 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>

#समावेश <linux/init.h>
#समावेश <linux/suspend.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/soc/samsung/exynos-regs-pmu.h>
#समावेश <linux/soc/samsung/exynos-pmu.h>

#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "common.h"

अटल अंतरभूत व्योम __iomem *exynos_boot_vector_addr(व्योम)
अणु
	अगर (exynos_rev() == EXYNOS4210_REV_1_1)
		वापस pmu_base_addr + S5P_INFORM7;
	अन्यथा अगर (exynos_rev() == EXYNOS4210_REV_1_0)
		वापस sysram_base_addr + 0x24;
	वापस pmu_base_addr + S5P_INFORM0;
पूर्ण

अटल अंतरभूत व्योम __iomem *exynos_boot_vector_flag(व्योम)
अणु
	अगर (exynos_rev() == EXYNOS4210_REV_1_1)
		वापस pmu_base_addr + S5P_INFORM6;
	अन्यथा अगर (exynos_rev() == EXYNOS4210_REV_1_0)
		वापस sysram_base_addr + 0x20;
	वापस pmu_base_addr + S5P_INFORM1;
पूर्ण

#घोषणा S5P_CHECK_AFTR  0xFCBA0D10

/* For Cortex-A9 Diagnostic and Power control रेजिस्टर */
अटल अचिन्हित पूर्णांक save_arm_रेजिस्टर[2];

व्योम exynos_cpu_save_रेजिस्टर(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;

	/* Save Power control रेजिस्टर */
	यंत्र ("mrc p15, 0, %0, c15, c0, 0"
	     : "=r" (पंचांगp) : : "cc");

	save_arm_रेजिस्टर[0] = पंचांगp;

	/* Save Diagnostic रेजिस्टर */
	यंत्र ("mrc p15, 0, %0, c15, c0, 1"
	     : "=r" (पंचांगp) : : "cc");

	save_arm_रेजिस्टर[1] = पंचांगp;
पूर्ण

व्योम exynos_cpu_restore_रेजिस्टर(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;

	/* Restore Power control रेजिस्टर */
	पंचांगp = save_arm_रेजिस्टर[0];

	यंत्र अस्थिर ("mcr p15, 0, %0, c15, c0, 0"
		      : : "r" (पंचांगp)
		      : "cc");

	/* Restore Diagnostic रेजिस्टर */
	पंचांगp = save_arm_रेजिस्टर[1];

	यंत्र अस्थिर ("mcr p15, 0, %0, c15, c0, 1"
		      : : "r" (पंचांगp)
		      : "cc");
पूर्ण

व्योम exynos_pm_central_suspend(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;

	/* Setting Central Sequence Register क्रम घातer करोwn mode */
	पंचांगp = pmu_raw_पढ़ोl(S5P_CENTRAL_SEQ_CONFIGURATION);
	पंचांगp &= ~S5P_CENTRAL_LOWPWR_CFG;
	pmu_raw_ग_लिखोl(पंचांगp, S5P_CENTRAL_SEQ_CONFIGURATION);
पूर्ण

पूर्णांक exynos_pm_central_resume(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;

	/*
	 * If PMU failed जबतक entering sleep mode, WFI will be
	 * ignored by PMU and then निकासing cpu_करो_idle().
	 * S5P_CENTRAL_LOWPWR_CFG bit will not be set स्वतःmatically
	 * in this situation.
	 */
	पंचांगp = pmu_raw_पढ़ोl(S5P_CENTRAL_SEQ_CONFIGURATION);
	अगर (!(पंचांगp & S5P_CENTRAL_LOWPWR_CFG)) अणु
		पंचांगp |= S5P_CENTRAL_LOWPWR_CFG;
		pmu_raw_ग_लिखोl(पंचांगp, S5P_CENTRAL_SEQ_CONFIGURATION);
		/* clear the wakeup state रेजिस्टर */
		pmu_raw_ग_लिखोl(0x0, S5P_WAKEUP_STAT);
		/* No need to perक्रमm below restore code */
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/* Ext-GIC nIRQ/nFIQ is the only wakeup source in AFTR */
अटल व्योम exynos_set_wakeupmask(दीर्घ mask)
अणु
	pmu_raw_ग_लिखोl(mask, S5P_WAKEUP_MASK);
	अगर (soc_is_exynos3250())
		pmu_raw_ग_लिखोl(0x0, S5P_WAKEUP_MASK2);
पूर्ण

अटल व्योम exynos_cpu_set_boot_vector(दीर्घ flags)
अणु
	ग_लिखोl_relaxed(__pa_symbol(exynos_cpu_resume),
		       exynos_boot_vector_addr());
	ग_लिखोl_relaxed(flags, exynos_boot_vector_flag());
पूर्ण

अटल पूर्णांक exynos_aftr_finisher(अचिन्हित दीर्घ flags)
अणु
	पूर्णांक ret;

	exynos_set_wakeupmask(soc_is_exynos3250() ? 0x40003ffe : 0x0000ff3e);
	/* Set value of घातer करोwn रेजिस्टर क्रम aftr mode */
	exynos_sys_घातerकरोwn_conf(SYS_AFTR);

	ret = call_firmware_op(करो_idle, FW_DO_IDLE_AFTR);
	अगर (ret == -ENOSYS) अणु
		अगर (पढ़ो_cpuid_part() == ARM_CPU_PART_CORTEX_A9)
			exynos_cpu_save_रेजिस्टर();
		exynos_cpu_set_boot_vector(S5P_CHECK_AFTR);
		cpu_करो_idle();
	पूर्ण

	वापस 1;
पूर्ण

व्योम exynos_enter_aftr(व्योम)
अणु
	अचिन्हित पूर्णांक cpuid = smp_processor_id();

	cpu_pm_enter();

	अगर (soc_is_exynos3250())
		exynos_set_boot_flag(cpuid, C2_STATE);

	exynos_pm_central_suspend();

	अगर (soc_is_exynos4412()) अणु
		/* Setting SEQ_OPTION रेजिस्टर */
		pmu_raw_ग_लिखोl(S5P_USE_STANDBY_WFI0 | S5P_USE_STANDBY_WFE0,
			       S5P_CENTRAL_SEQ_OPTION);
	पूर्ण

	cpu_suspend(0, exynos_aftr_finisher);

	अगर (पढ़ो_cpuid_part() == ARM_CPU_PART_CORTEX_A9) अणु
		exynos_scu_enable();
		अगर (call_firmware_op(resume) == -ENOSYS)
			exynos_cpu_restore_रेजिस्टर();
	पूर्ण

	exynos_pm_central_resume();

	अगर (soc_is_exynos3250())
		exynos_clear_boot_flag(cpuid, C2_STATE);

	cpu_pm_निकास();
पूर्ण

#अगर defined(CONFIG_SMP) && defined(CONFIG_ARM_EXYNOS_CPUIDLE)
अटल atomic_t cpu1_wakeup = ATOMIC_INIT(0);

अटल पूर्णांक exynos_cpu0_enter_aftr(व्योम)
अणु
	पूर्णांक ret = -1;

	/*
	 * If the other cpu is घातered on, we have to घातer it off, because
	 * the AFTR state won't work otherwise
	 */
	अगर (cpu_online(1)) अणु
		/*
		 * We reach a sync poपूर्णांक with the coupled idle state, we know
		 * the other cpu will घातer करोwn itself or will पात the
		 * sequence, let's रुको क्रम one of these to happen
		 */
		जबतक (exynos_cpu_घातer_state(1)) अणु
			अचिन्हित दीर्घ boot_addr;

			/*
			 * The other cpu may skip idle and boot back
			 * up again
			 */
			अगर (atomic_पढ़ो(&cpu1_wakeup))
				जाओ पात;

			/*
			 * The other cpu may bounce through idle and
			 * boot back up again, getting stuck in the
			 * boot rom code
			 */
			ret = exynos_get_boot_addr(1, &boot_addr);
			अगर (ret)
				जाओ fail;
			ret = -1;
			अगर (boot_addr == 0)
				जाओ पात;

			cpu_relax();
		पूर्ण
	पूर्ण

	exynos_enter_aftr();
	ret = 0;

पात:
	अगर (cpu_online(1)) अणु
		अचिन्हित दीर्घ boot_addr = __pa_symbol(exynos_cpu_resume);

		/*
		 * Set the boot vector to something non-zero
		 */
		ret = exynos_set_boot_addr(1, boot_addr);
		अगर (ret)
			जाओ fail;
		dsb();

		/*
		 * Turn on cpu1 and रुको क्रम it to be on
		 */
		exynos_cpu_घातer_up(1);
		जबतक (exynos_cpu_घातer_state(1) != S5P_CORE_LOCAL_PWR_EN)
			cpu_relax();

		अगर (soc_is_exynos3250()) अणु
			जबतक (!pmu_raw_पढ़ोl(S5P_PMU_SPARE2) &&
			       !atomic_पढ़ो(&cpu1_wakeup))
				cpu_relax();

			अगर (!atomic_पढ़ो(&cpu1_wakeup))
				exynos_core_restart(1);
		पूर्ण

		जबतक (!atomic_पढ़ो(&cpu1_wakeup)) अणु
			smp_rmb();

			/*
			 * Poke cpu1 out of the boot rom
			 */

			ret = exynos_set_boot_addr(1, boot_addr);
			अगर (ret)
				जाओ fail;

			call_firmware_op(cpu_boot, 1);
			dsb_sev();
		पूर्ण
	पूर्ण
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक exynos_wfi_finisher(अचिन्हित दीर्घ flags)
अणु
	अगर (soc_is_exynos3250())
		flush_cache_all();
	cpu_करो_idle();

	वापस -1;
पूर्ण

अटल पूर्णांक exynos_cpu1_घातerकरोwn(व्योम)
अणु
	पूर्णांक ret = -1;

	/*
	 * Idle sequence क्रम cpu1
	 */
	अगर (cpu_pm_enter())
		जाओ cpu1_पातed;

	/*
	 * Turn off cpu 1
	 */
	exynos_cpu_घातer_करोwn(1);

	अगर (soc_is_exynos3250())
		pmu_raw_ग_लिखोl(0, S5P_PMU_SPARE2);

	ret = cpu_suspend(0, exynos_wfi_finisher);

	cpu_pm_निकास();

cpu1_पातed:
	dsb();
	/*
	 * Notअगरy cpu 0 that cpu 1 is awake
	 */
	atomic_set(&cpu1_wakeup, 1);

	वापस ret;
पूर्ण

अटल व्योम exynos_pre_enter_aftr(व्योम)
अणु
	अचिन्हित दीर्घ boot_addr = __pa_symbol(exynos_cpu_resume);

	(व्योम)exynos_set_boot_addr(1, boot_addr);
पूर्ण

अटल व्योम exynos_post_enter_aftr(व्योम)
अणु
	atomic_set(&cpu1_wakeup, 0);
पूर्ण

काष्ठा cpuidle_exynos_data cpuidle_coupled_exynos_data = अणु
	.cpu0_enter_aftr		= exynos_cpu0_enter_aftr,
	.cpu1_घातerकरोwn		= exynos_cpu1_घातerकरोwn,
	.pre_enter_aftr		= exynos_pre_enter_aftr,
	.post_enter_aftr		= exynos_post_enter_aftr,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SMP && CONFIG_ARM_EXYNOS_CPUIDLE */
