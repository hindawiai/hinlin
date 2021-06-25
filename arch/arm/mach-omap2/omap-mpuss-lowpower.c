<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP MPUSS low घातer code
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * OMAP4430 MPUSS मुख्यly consists of dual Cortex-A9 with per-CPU
 * Local समयr and Watchकरोg, GIC, SCU, PL310 L2 cache controller,
 * CPU0 and CPU1 LPRM modules.
 * CPU0, CPU1 and MPUSS each have there own घातer करोमुख्य and
 * hence multiple low घातer combinations of MPUSS are possible.
 *
 * The CPU0 and CPU1 can't support Closed चयन Retention (CSWR)
 * because the mode is not supported by hw स्थिरraपूर्णांकs of करोrmant
 * mode. While waking up from the करोrmant mode, a reset  संकेत
 * to the Cortex-A9 processor must be निश्चितed by the बाह्यal
 * घातer controller.
 *
 * With architectural inमाला_दो and hardware recommendations, only
 * below modes are supported from घातer gain vs latency poपूर्णांक of view.
 *
 *	CPU0		CPU1		MPUSS
 *	----------------------------------------------
 *	ON		ON		ON
 *	ON(Inactive)	OFF		ON(Inactive)
 *	OFF		OFF		CSWR
 *	OFF		OFF		OSWR
 *	OFF		OFF		OFF(Device OFF *TBD)
 *	----------------------------------------------
 *
 * Note: CPU0 is the master core and it is the last CPU to go करोwn
 * and first to wake-up when MPUSS low घातer states are excercised
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/linkage.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/virt.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>

#समावेश "soc.h"
#समावेश "common.h"
#समावेश "omap44xx.h"
#समावेश "omap4-sar-layout.h"
#समावेश "pm.h"
#समावेश "prcm_mpu44xx.h"
#समावेश "prcm_mpu54xx.h"
#समावेश "prminst44xx.h"
#समावेश "prcm44xx.h"
#समावेश "prm44xx.h"
#समावेश "prm-regbits-44xx.h"

अटल व्योम __iomem *sar_base;
अटल u32 old_cpu1_ns_pa_addr;

#अगर defined(CONFIG_PM) && defined(CONFIG_SMP)

काष्ठा omap4_cpu_pm_info अणु
	काष्ठा घातerकरोमुख्य *pwrdm;
	व्योम __iomem *scu_sar_addr;
	व्योम __iomem *wkup_sar_addr;
	व्योम __iomem *l2x0_sar_addr;
पूर्ण;

/**
 * काष्ठा cpu_pm_ops - CPU pm operations
 * @finish_suspend:	CPU suspend finisher function poपूर्णांकer
 * @resume:		CPU resume function poपूर्णांकer
 * @scu_prepare:	CPU Snoop Control program function poपूर्णांकer
 * @hotplug_restart:	CPU restart function poपूर्णांकer
 *
 * Structure holds functions poपूर्णांकer क्रम CPU low घातer operations like
 * suspend, resume and scu programming.
 */
काष्ठा cpu_pm_ops अणु
	पूर्णांक (*finish_suspend)(अचिन्हित दीर्घ cpu_state);
	व्योम (*resume)(व्योम);
	व्योम (*scu_prepare)(अचिन्हित पूर्णांक cpu_id, अचिन्हित पूर्णांक cpu_state);
	व्योम (*hotplug_restart)(व्योम);
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा omap4_cpu_pm_info, omap4_pm_info);
अटल काष्ठा घातerकरोमुख्य *mpuss_pd;
अटल u32 cpu_context_offset;

अटल पूर्णांक शेष_finish_suspend(अचिन्हित दीर्घ cpu_state)
अणु
	omap_करो_wfi();
	वापस 0;
पूर्ण

अटल व्योम dummy_cpu_resume(व्योम)
अणुपूर्ण

अटल व्योम dummy_scu_prepare(अचिन्हित पूर्णांक cpu_id, अचिन्हित पूर्णांक cpu_state)
अणुपूर्ण

अटल काष्ठा cpu_pm_ops omap_pm_ops = अणु
	.finish_suspend		= शेष_finish_suspend,
	.resume			= dummy_cpu_resume,
	.scu_prepare		= dummy_scu_prepare,
	.hotplug_restart	= dummy_cpu_resume,
पूर्ण;

/*
 * Program the wakeup routine address क्रम the CPU0 and CPU1
 * used क्रम OFF or DORMANT wakeup.
 */
अटल अंतरभूत व्योम set_cpu_wakeup_addr(अचिन्हित पूर्णांक cpu_id, u32 addr)
अणु
	काष्ठा omap4_cpu_pm_info *pm_info = &per_cpu(omap4_pm_info, cpu_id);

	अगर (pm_info->wkup_sar_addr)
		ग_लिखोl_relaxed(addr, pm_info->wkup_sar_addr);
पूर्ण

/*
 * Store the SCU घातer status value to scratchpad memory
 */
अटल व्योम scu_pwrst_prepare(अचिन्हित पूर्णांक cpu_id, अचिन्हित पूर्णांक cpu_state)
अणु
	काष्ठा omap4_cpu_pm_info *pm_info = &per_cpu(omap4_pm_info, cpu_id);
	u32 scu_pwr_st;

	चयन (cpu_state) अणु
	हाल PWRDM_POWER_RET:
		scu_pwr_st = SCU_PM_DORMANT;
		अवरोध;
	हाल PWRDM_POWER_OFF:
		scu_pwr_st = SCU_PM_POWEROFF;
		अवरोध;
	हाल PWRDM_POWER_ON:
	हाल PWRDM_POWER_INACTIVE:
	शेष:
		scu_pwr_st = SCU_PM_NORMAL;
		अवरोध;
	पूर्ण

	अगर (pm_info->scu_sar_addr)
		ग_लिखोl_relaxed(scu_pwr_st, pm_info->scu_sar_addr);
पूर्ण

/* Helper functions क्रम MPUSS OSWR */
अटल अंतरभूत व्योम mpuss_clear_prev_logic_pwrst(व्योम)
अणु
	u32 reg;

	reg = omap4_prminst_पढ़ो_inst_reg(OMAP4430_PRM_PARTITION,
		OMAP4430_PRM_MPU_INST, OMAP4_RM_MPU_MPU_CONTEXT_OFFSET);
	omap4_prminst_ग_लिखो_inst_reg(reg, OMAP4430_PRM_PARTITION,
		OMAP4430_PRM_MPU_INST, OMAP4_RM_MPU_MPU_CONTEXT_OFFSET);
पूर्ण

अटल अंतरभूत व्योम cpu_clear_prev_logic_pwrst(अचिन्हित पूर्णांक cpu_id)
अणु
	u32 reg;

	अगर (cpu_id) अणु
		reg = omap4_prcm_mpu_पढ़ो_inst_reg(OMAP4430_PRCM_MPU_CPU1_INST,
					cpu_context_offset);
		omap4_prcm_mpu_ग_लिखो_inst_reg(reg, OMAP4430_PRCM_MPU_CPU1_INST,
					cpu_context_offset);
	पूर्ण अन्यथा अणु
		reg = omap4_prcm_mpu_पढ़ो_inst_reg(OMAP4430_PRCM_MPU_CPU0_INST,
					cpu_context_offset);
		omap4_prcm_mpu_ग_लिखो_inst_reg(reg, OMAP4430_PRCM_MPU_CPU0_INST,
					cpu_context_offset);
	पूर्ण
पूर्ण

/*
 * Store the CPU cluster state क्रम L2X0 low घातer operations.
 */
अटल व्योम l2x0_pwrst_prepare(अचिन्हित पूर्णांक cpu_id, अचिन्हित पूर्णांक save_state)
अणु
	काष्ठा omap4_cpu_pm_info *pm_info = &per_cpu(omap4_pm_info, cpu_id);

	अगर (pm_info->l2x0_sar_addr)
		ग_लिखोl_relaxed(save_state, pm_info->l2x0_sar_addr);
पूर्ण

/*
 * Save the L2X0 AUXCTRL and POR value to SAR memory. Its used to
 * in every restore MPUSS OFF path.
 */
#अगर_घोषित CONFIG_CACHE_L2X0
अटल व्योम __init save_l2x0_context(व्योम)
अणु
	व्योम __iomem *l2x0_base = omap4_get_l2cache_base();

	अगर (l2x0_base && sar_base) अणु
		ग_लिखोl_relaxed(l2x0_saved_regs.aux_ctrl,
			       sar_base + L2X0_AUXCTRL_OFFSET);
		ग_लिखोl_relaxed(l2x0_saved_regs.prefetch_ctrl,
			       sar_base + L2X0_PREFETCH_CTRL_OFFSET);
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम __init save_l2x0_context(व्योम)
अणुपूर्ण
#पूर्ण_अगर

/**
 * omap4_enter_lowघातer: OMAP4 MPUSS Low Power Entry Function
 * The purpose of this function is to manage low घातer programming
 * of OMAP4 MPUSS subप्रणाली
 * @cpu : CPU ID
 * @घातer_state: Low घातer state.
 *
 * MPUSS states क्रम the context save:
 * save_state =
 *	0 - Nothing lost and no need to save: MPUSS INACTIVE
 *	1 - CPUx L1 and logic lost: MPUSS CSWR
 *	2 - CPUx L1 and logic lost + GIC lost: MPUSS OSWR
 *	3 - CPUx L1 and logic lost + GIC + L2 lost: DEVICE OFF
 */
पूर्णांक omap4_enter_lowघातer(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक घातer_state)
अणु
	काष्ठा omap4_cpu_pm_info *pm_info = &per_cpu(omap4_pm_info, cpu);
	अचिन्हित पूर्णांक save_state = 0, cpu_logic_state = PWRDM_POWER_RET;

	अगर (omap_rev() == OMAP4430_REV_ES1_0)
		वापस -ENXIO;

	चयन (घातer_state) अणु
	हाल PWRDM_POWER_ON:
	हाल PWRDM_POWER_INACTIVE:
		save_state = 0;
		अवरोध;
	हाल PWRDM_POWER_OFF:
		cpu_logic_state = PWRDM_POWER_OFF;
		save_state = 1;
		अवरोध;
	हाल PWRDM_POWER_RET:
		अगर (IS_PM44XX_ERRATUM(PM_OMAP4_CPU_OSWR_DISABLE))
			save_state = 0;
		अवरोध;
	शेष:
		/*
		 * CPUx CSWR is invalid hardware state. Also CPUx OSWR
		 * करोesn't make much scense, since logic is lost and $L1
		 * needs to be cleaned because of coherency. This makes
		 * CPUx OSWR equivalent to CPUX OFF and hence not supported
		 */
		WARN_ON(1);
		वापस -ENXIO;
	पूर्ण

	pwrdm_pre_transition(शून्य);

	/*
	 * Check MPUSS next state and save पूर्णांकerrupt controller अगर needed.
	 * In MPUSS OSWR or device OFF, पूर्णांकerrupt controller  contest is lost.
	 */
	mpuss_clear_prev_logic_pwrst();
	अगर ((pwrdm_पढ़ो_next_pwrst(mpuss_pd) == PWRDM_POWER_RET) &&
		(pwrdm_पढ़ो_logic_retst(mpuss_pd) == PWRDM_POWER_OFF))
		save_state = 2;

	cpu_clear_prev_logic_pwrst(cpu);
	pwrdm_set_next_pwrst(pm_info->pwrdm, घातer_state);
	pwrdm_set_logic_retst(pm_info->pwrdm, cpu_logic_state);
	set_cpu_wakeup_addr(cpu, __pa_symbol(omap_pm_ops.resume));
	omap_pm_ops.scu_prepare(cpu, घातer_state);
	l2x0_pwrst_prepare(cpu, save_state);

	/*
	 * Call low level function  with targeted low घातer state.
	 */
	अगर (save_state)
		cpu_suspend(save_state, omap_pm_ops.finish_suspend);
	अन्यथा
		omap_pm_ops.finish_suspend(save_state);

	अगर (IS_PM44XX_ERRATUM(PM_OMAP4_ROM_SMP_BOOT_ERRATUM_GICD) && cpu)
		gic_dist_enable();

	/*
	 * Restore the CPUx घातer state to ON otherwise CPUx
	 * घातer करोमुख्य can transitions to programmed low घातer
	 * state जबतक करोing WFI outside the low घातe code. On
	 * secure devices, CPUx करोes WFI which can result in
	 * करोमुख्य transition
	 */
	pwrdm_set_next_pwrst(pm_info->pwrdm, PWRDM_POWER_ON);

	pwrdm_post_transition(शून्य);

	वापस 0;
पूर्ण

/**
 * omap4_hotplug_cpu: OMAP4 CPU hotplug entry
 * @cpu : CPU ID
 * @घातer_state: CPU low घातer state.
 */
पूर्णांक omap4_hotplug_cpu(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक घातer_state)
अणु
	काष्ठा omap4_cpu_pm_info *pm_info = &per_cpu(omap4_pm_info, cpu);
	अचिन्हित पूर्णांक cpu_state = 0;

	अगर (omap_rev() == OMAP4430_REV_ES1_0)
		वापस -ENXIO;

	/* Use the achievable घातer state क्रम the करोमुख्य */
	घातer_state = pwrdm_get_valid_lp_state(pm_info->pwrdm,
					       false, घातer_state);

	अगर (घातer_state == PWRDM_POWER_OFF)
		cpu_state = 1;

	pwrdm_clear_all_prev_pwrst(pm_info->pwrdm);
	pwrdm_set_next_pwrst(pm_info->pwrdm, घातer_state);
	set_cpu_wakeup_addr(cpu, __pa_symbol(omap_pm_ops.hotplug_restart));
	omap_pm_ops.scu_prepare(cpu, घातer_state);

	/*
	 * CPU never retuns back अगर targeted घातer state is OFF mode.
	 * CPU ONLINE follows normal CPU ONLINE ptah via
	 * omap4_secondary_startup().
	 */
	omap_pm_ops.finish_suspend(cpu_state);

	pwrdm_set_next_pwrst(pm_info->pwrdm, PWRDM_POWER_ON);
	वापस 0;
पूर्ण


/*
 * Enable Mercury Fast HG retention mode by शेष.
 */
अटल व्योम enable_mercury_retention_mode(व्योम)
अणु
	u32 reg;

	reg = omap4_prcm_mpu_पढ़ो_inst_reg(OMAP54XX_PRCM_MPU_DEVICE_INST,
				  OMAP54XX_PRCM_MPU_PRM_PSCON_COUNT_OFFSET);
	/* Enable HG_EN, HG_RAMPUP = fast mode */
	reg |= BIT(24) | BIT(25);
	omap4_prcm_mpu_ग_लिखो_inst_reg(reg, OMAP54XX_PRCM_MPU_DEVICE_INST,
				      OMAP54XX_PRCM_MPU_PRM_PSCON_COUNT_OFFSET);
पूर्ण

/*
 * Initialise OMAP4 MPUSS
 */
पूर्णांक __init omap4_mpuss_init(व्योम)
अणु
	काष्ठा omap4_cpu_pm_info *pm_info;

	अगर (omap_rev() == OMAP4430_REV_ES1_0) अणु
		WARN(1, "Power Management not supported on OMAP4430 ES1.0\n");
		वापस -ENODEV;
	पूर्ण

	/* Initilaise per CPU PM inक्रमmation */
	pm_info = &per_cpu(omap4_pm_info, 0x0);
	अगर (sar_base) अणु
		pm_info->scu_sar_addr = sar_base + SCU_OFFSET0;
		अगर (cpu_is_omap44xx())
			pm_info->wkup_sar_addr = sar_base +
				CPU0_WAKEUP_NS_PA_ADDR_OFFSET;
		अन्यथा
			pm_info->wkup_sar_addr = sar_base +
				OMAP5_CPU0_WAKEUP_NS_PA_ADDR_OFFSET;
		pm_info->l2x0_sar_addr = sar_base + L2X0_SAVE_OFFSET0;
	पूर्ण
	pm_info->pwrdm = pwrdm_lookup("cpu0_pwrdm");
	अगर (!pm_info->pwrdm) अणु
		pr_err("Lookup failed for CPU0 pwrdm\n");
		वापस -ENODEV;
	पूर्ण

	/* Clear CPU previous घातer करोमुख्य state */
	pwrdm_clear_all_prev_pwrst(pm_info->pwrdm);
	cpu_clear_prev_logic_pwrst(0);

	/* Initialise CPU0 घातer करोमुख्य state to ON */
	pwrdm_set_next_pwrst(pm_info->pwrdm, PWRDM_POWER_ON);

	pm_info = &per_cpu(omap4_pm_info, 0x1);
	अगर (sar_base) अणु
		pm_info->scu_sar_addr = sar_base + SCU_OFFSET1;
		अगर (cpu_is_omap44xx())
			pm_info->wkup_sar_addr = sar_base +
				CPU1_WAKEUP_NS_PA_ADDR_OFFSET;
		अन्यथा
			pm_info->wkup_sar_addr = sar_base +
				OMAP5_CPU1_WAKEUP_NS_PA_ADDR_OFFSET;
		pm_info->l2x0_sar_addr = sar_base + L2X0_SAVE_OFFSET1;
	पूर्ण

	pm_info->pwrdm = pwrdm_lookup("cpu1_pwrdm");
	अगर (!pm_info->pwrdm) अणु
		pr_err("Lookup failed for CPU1 pwrdm\n");
		वापस -ENODEV;
	पूर्ण

	/* Clear CPU previous घातer करोमुख्य state */
	pwrdm_clear_all_prev_pwrst(pm_info->pwrdm);
	cpu_clear_prev_logic_pwrst(1);

	/* Initialise CPU1 घातer करोमुख्य state to ON */
	pwrdm_set_next_pwrst(pm_info->pwrdm, PWRDM_POWER_ON);

	mpuss_pd = pwrdm_lookup("mpu_pwrdm");
	अगर (!mpuss_pd) अणु
		pr_err("Failed to lookup MPUSS power domain\n");
		वापस -ENODEV;
	पूर्ण
	pwrdm_clear_all_prev_pwrst(mpuss_pd);
	mpuss_clear_prev_logic_pwrst();

	अगर (sar_base) अणु
		/* Save device type on scratchpad क्रम low level code to use */
		ग_लिखोl_relaxed((omap_type() != OMAP2_DEVICE_TYPE_GP) ? 1 : 0,
			       sar_base + OMAP_TYPE_OFFSET);
		save_l2x0_context();
	पूर्ण

	अगर (cpu_is_omap44xx()) अणु
		omap_pm_ops.finish_suspend = omap4_finish_suspend;
		omap_pm_ops.resume = omap4_cpu_resume;
		omap_pm_ops.scu_prepare = scu_pwrst_prepare;
		omap_pm_ops.hotplug_restart = omap4_secondary_startup;
		cpu_context_offset = OMAP4_RM_CPU0_CPU0_CONTEXT_OFFSET;
	पूर्ण अन्यथा अगर (soc_is_omap54xx() || soc_is_dra7xx()) अणु
		cpu_context_offset = OMAP54XX_RM_CPU0_CPU0_CONTEXT_OFFSET;
		enable_mercury_retention_mode();
	पूर्ण

	अगर (cpu_is_omap446x())
		omap_pm_ops.hotplug_restart = omap4460_secondary_startup;

	वापस 0;
पूर्ण

#पूर्ण_अगर

u32 omap4_get_cpu1_ns_pa_addr(व्योम)
अणु
	वापस old_cpu1_ns_pa_addr;
पूर्ण

/*
 * For kexec, we must set CPU1_WAKEUP_NS_PA_ADDR to poपूर्णांक to
 * current kernel's secondary_startup() early beक्रमe
 * घड़ीकरोमुख्यs_init(). Otherwise घड़ीकरोमुख्य_init() can
 * wake CPU1 and cause a hang.
 */
व्योम __init omap4_mpuss_early_init(व्योम)
अणु
	अचिन्हित दीर्घ startup_pa;
	व्योम __iomem *ns_pa_addr;

	अगर (!(soc_is_omap44xx() || soc_is_omap54xx()))
		वापस;

	sar_base = omap4_get_sar_ram_base();

	/* Save old NS_PA_ADDR क्रम validity checks later on */
	अगर (soc_is_omap44xx())
		ns_pa_addr = sar_base + CPU1_WAKEUP_NS_PA_ADDR_OFFSET;
	अन्यथा
		ns_pa_addr = sar_base + OMAP5_CPU1_WAKEUP_NS_PA_ADDR_OFFSET;
	old_cpu1_ns_pa_addr = पढ़ोl_relaxed(ns_pa_addr);

	अगर (soc_is_omap443x())
		startup_pa = __pa_symbol(omap4_secondary_startup);
	अन्यथा अगर (soc_is_omap446x())
		startup_pa = __pa_symbol(omap4460_secondary_startup);
	अन्यथा अगर ((__boot_cpu_mode & MODE_MASK) == HYP_MODE)
		startup_pa = __pa_symbol(omap5_secondary_hyp_startup);
	अन्यथा
		startup_pa = __pa_symbol(omap5_secondary_startup);

	अगर (soc_is_omap44xx())
		ग_लिखोl_relaxed(startup_pa, sar_base +
			       CPU1_WAKEUP_NS_PA_ADDR_OFFSET);
	अन्यथा
		ग_लिखोl_relaxed(startup_pa, sar_base +
			       OMAP5_CPU1_WAKEUP_NS_PA_ADDR_OFFSET);
पूर्ण
