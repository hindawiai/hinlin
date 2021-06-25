<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2011-2014 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
//
// Exynos - Suspend support
//
// Based on arch/arm/mach-s3c2410/pm.c
// Copyright (c) 2006 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>

#समावेश <linux/init.h>
#समावेश <linux/suspend.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_address.h>
#समावेश <linux/err.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/soc/samsung/exynos-pmu.h>
#समावेश <linux/soc/samsung/exynos-regs-pmu.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/mcpm.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/suspend.h>

#समावेश "common.h"
#समावेश "smc.h"

#घोषणा REG_TABLE_END (-1U)

#घोषणा EXYNOS5420_CPU_STATE	0x28

/**
 * काष्ठा exynos_wkup_irq - PMU IRQ to mask mapping
 * @hwirq: Hardware IRQ संकेत of the PMU
 * @mask: Mask in PMU wake-up mask रेजिस्टर
 */
काष्ठा exynos_wkup_irq अणु
	अचिन्हित पूर्णांक hwirq;
	u32 mask;
पूर्ण;

काष्ठा exynos_pm_data अणु
	स्थिर काष्ठा exynos_wkup_irq *wkup_irq;
	अचिन्हित पूर्णांक wake_disable_mask;

	व्योम (*pm_prepare)(व्योम);
	व्योम (*pm_resume_prepare)(व्योम);
	व्योम (*pm_resume)(व्योम);
	पूर्णांक (*pm_suspend)(व्योम);
	पूर्णांक (*cpu_suspend)(अचिन्हित दीर्घ);
पूर्ण;

/* Used only on Exynos542x/5800 */
काष्ठा exynos_pm_state अणु
	पूर्णांक cpu_state;
	अचिन्हित पूर्णांक pmu_spare3;
	व्योम __iomem *sysram_base;
	phys_addr_t sysram_phys;
	bool secure_firmware;
पूर्ण;

अटल स्थिर काष्ठा exynos_pm_data *pm_data __ro_after_init;
अटल काष्ठा exynos_pm_state pm_state;

/*
 * GIC wake-up support
 */

अटल u32 exynos_irqwake_पूर्णांकmask = 0xffffffff;

अटल स्थिर काष्ठा exynos_wkup_irq exynos3250_wkup_irq[] = अणु
	अणु 73, BIT(1) पूर्ण, /* RTC alarm */
	अणु 74, BIT(2) पूर्ण, /* RTC tick */
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा exynos_wkup_irq exynos4_wkup_irq[] = अणु
	अणु 44, BIT(1) पूर्ण, /* RTC alarm */
	अणु 45, BIT(2) पूर्ण, /* RTC tick */
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा exynos_wkup_irq exynos5250_wkup_irq[] = अणु
	अणु 43, BIT(1) पूर्ण, /* RTC alarm */
	अणु 44, BIT(2) पूर्ण, /* RTC tick */
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल u32 exynos_पढ़ो_eपूर्णांक_wakeup_mask(व्योम)
अणु
	वापस pmu_raw_पढ़ोl(EXYNOS_EINT_WAKEUP_MASK);
पूर्ण

अटल पूर्णांक exynos_irq_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक state)
अणु
	स्थिर काष्ठा exynos_wkup_irq *wkup_irq;

	अगर (!pm_data->wkup_irq)
		वापस -ENOENT;
	wkup_irq = pm_data->wkup_irq;

	जबतक (wkup_irq->mask) अणु
		अगर (wkup_irq->hwirq == data->hwirq) अणु
			अगर (!state)
				exynos_irqwake_पूर्णांकmask |= wkup_irq->mask;
			अन्यथा
				exynos_irqwake_पूर्णांकmask &= ~wkup_irq->mask;
			वापस 0;
		पूर्ण
		++wkup_irq;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल काष्ठा irq_chip exynos_pmu_chip = अणु
	.name			= "PMU",
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_set_wake		= exynos_irq_set_wake,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	= irq_chip_set_affinity_parent,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक exynos_pmu_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
				       काष्ठा irq_fwspec *fwspec,
				       अचिन्हित दीर्घ *hwirq,
				       अचिन्हित पूर्णांक *type)
अणु
	अगर (is_of_node(fwspec->fwnode)) अणु
		अगर (fwspec->param_count != 3)
			वापस -EINVAL;

		/* No PPI should poपूर्णांक to this करोमुख्य */
		अगर (fwspec->param[0] != 0)
			वापस -EINVAL;

		*hwirq = fwspec->param[1];
		*type = fwspec->param[2];
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक exynos_pmu_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				   अचिन्हित पूर्णांक virq,
				   अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा irq_fwspec *fwspec = data;
	काष्ठा irq_fwspec parent_fwspec;
	irq_hw_number_t hwirq;
	पूर्णांक i;

	अगर (fwspec->param_count != 3)
		वापस -EINVAL;	/* Not GIC compliant */
	अगर (fwspec->param[0] != 0)
		वापस -EINVAL;	/* No PPI should poपूर्णांक to this करोमुख्य */

	hwirq = fwspec->param[1];

	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, hwirq + i,
					      &exynos_pmu_chip, शून्य);

	parent_fwspec = *fwspec;
	parent_fwspec.fwnode = करोमुख्य->parent->fwnode;
	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs,
					    &parent_fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops exynos_pmu_करोमुख्य_ops = अणु
	.translate	= exynos_pmu_करोमुख्य_translate,
	.alloc		= exynos_pmu_करोमुख्य_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

अटल पूर्णांक __init exynos_pmu_irq_init(काष्ठा device_node *node,
				      काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *parent_करोमुख्य, *करोमुख्य;

	अगर (!parent) अणु
		pr_err("%pOF: no parent, giving up\n", node);
		वापस -ENODEV;
	पूर्ण

	parent_करोमुख्य = irq_find_host(parent);
	अगर (!parent_करोमुख्य) अणु
		pr_err("%pOF: unable to obtain parent domain\n", node);
		वापस -ENXIO;
	पूर्ण

	pmu_base_addr = of_iomap(node, 0);

	अगर (!pmu_base_addr) अणु
		pr_err("%pOF: failed to find exynos pmu register\n", node);
		वापस -ENOMEM;
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_hierarchy(parent_करोमुख्य, 0, 0,
					  node, &exynos_pmu_करोमुख्य_ops,
					  शून्य);
	अगर (!करोमुख्य) अणु
		iounmap(pmu_base_addr);
		pmu_base_addr = शून्य;
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Clear the OF_POPULATED flag set in of_irq_init so that
	 * later the Exynos PMU platक्रमm device won't be skipped.
	 */
	of_node_clear_flag(node, OF_POPULATED);

	वापस 0;
पूर्ण

#घोषणा EXYNOS_PMU_IRQ(symbol, name)	IRQCHIP_DECLARE(symbol, name, exynos_pmu_irq_init)

EXYNOS_PMU_IRQ(exynos3250_pmu_irq, "samsung,exynos3250-pmu");
EXYNOS_PMU_IRQ(exynos4210_pmu_irq, "samsung,exynos4210-pmu");
EXYNOS_PMU_IRQ(exynos4412_pmu_irq, "samsung,exynos4412-pmu");
EXYNOS_PMU_IRQ(exynos5250_pmu_irq, "samsung,exynos5250-pmu");
EXYNOS_PMU_IRQ(exynos5420_pmu_irq, "samsung,exynos5420-pmu");

अटल पूर्णांक exynos_cpu_करो_idle(व्योम)
अणु
	/* issue the standby संकेत पूर्णांकo the pm unit. */
	cpu_करो_idle();

	pr_info("Failed to suspend the system\n");
	वापस 1; /* Aborting suspend */
पूर्ण
अटल व्योम exynos_flush_cache_all(व्योम)
अणु
	flush_cache_all();
	outer_flush_all();
पूर्ण

अटल पूर्णांक exynos_cpu_suspend(अचिन्हित दीर्घ arg)
अणु
	exynos_flush_cache_all();
	वापस exynos_cpu_करो_idle();
पूर्ण

अटल पूर्णांक exynos3250_cpu_suspend(अचिन्हित दीर्घ arg)
अणु
	flush_cache_all();
	वापस exynos_cpu_करो_idle();
पूर्ण

अटल पूर्णांक exynos5420_cpu_suspend(अचिन्हित दीर्घ arg)
अणु
	/* MCPM works with HW CPU identअगरiers */
	अचिन्हित पूर्णांक mpidr = पढ़ो_cpuid_mpidr();
	अचिन्हित पूर्णांक cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	अचिन्हित पूर्णांक cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);

	अगर (IS_ENABLED(CONFIG_EXYNOS_MCPM)) अणु
		mcpm_set_entry_vector(cpu, cluster, exynos_cpu_resume);
		mcpm_cpu_suspend();
	पूर्ण

	pr_info("Failed to suspend the system\n");

	/* वापस value != 0 means failure */
	वापस 1;
पूर्ण

अटल व्योम exynos_pm_set_wakeup_mask(व्योम)
अणु
	/*
	 * Set wake-up mask रेजिस्टरs
	 * EXYNOS_EINT_WAKEUP_MASK is set by pinctrl driver in late suspend.
	 */
	pmu_raw_ग_लिखोl(exynos_irqwake_पूर्णांकmask & ~BIT(31), S5P_WAKEUP_MASK);
पूर्ण

अटल व्योम exynos_pm_enter_sleep_mode(व्योम)
अणु
	/* Set value of घातer करोwn रेजिस्टर क्रम sleep mode */
	exynos_sys_घातerकरोwn_conf(SYS_SLEEP);
	pmu_raw_ग_लिखोl(EXYNOS_SLEEP_MAGIC, S5P_INFORM1);
पूर्ण

अटल व्योम exynos_pm_prepare(व्योम)
अणु
	exynos_set_delayed_reset_निश्चितion(false);

	/* Set wake-up mask रेजिस्टरs */
	exynos_pm_set_wakeup_mask();

	exynos_pm_enter_sleep_mode();

	/* ensure at least INFORM0 has the resume address */
	pmu_raw_ग_लिखोl(__pa_symbol(exynos_cpu_resume), S5P_INFORM0);
पूर्ण

अटल व्योम exynos3250_pm_prepare(व्योम)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	/* Set wake-up mask रेजिस्टरs */
	exynos_pm_set_wakeup_mask();

	पंचांगp = pmu_raw_पढ़ोl(EXYNOS3_ARM_L2_OPTION);
	पंचांगp &= ~EXYNOS5_OPTION_USE_RETENTION;
	pmu_raw_ग_लिखोl(पंचांगp, EXYNOS3_ARM_L2_OPTION);

	exynos_pm_enter_sleep_mode();

	/* ensure at least INFORM0 has the resume address */
	pmu_raw_ग_लिखोl(__pa_symbol(exynos_cpu_resume), S5P_INFORM0);
पूर्ण

अटल व्योम exynos5420_pm_prepare(व्योम)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	/* Set wake-up mask रेजिस्टरs */
	exynos_pm_set_wakeup_mask();

	pm_state.pmu_spare3 = pmu_raw_पढ़ोl(S5P_PMU_SPARE3);
	/*
	 * The cpu state needs to be saved and restored so that the
	 * secondary CPUs will enter low घातer start. Though the U-Boot
	 * is setting the cpu state with low घातer flag, the kernel
	 * needs to restore it back in हाल, the primary cpu fails to
	 * suspend क्रम any reason.
	 */
	pm_state.cpu_state = पढ़ोl_relaxed(pm_state.sysram_base +
					   EXYNOS5420_CPU_STATE);
	ग_लिखोl_relaxed(0x0, pm_state.sysram_base + EXYNOS5420_CPU_STATE);
	अगर (pm_state.secure_firmware)
		exynos_smc(SMC_CMD_REG, SMC_REG_ID_SFR_W(pm_state.sysram_phys +
							 EXYNOS5420_CPU_STATE),
			   0, 0);

	exynos_pm_enter_sleep_mode();

	/* ensure at least INFORM0 has the resume address */
	अगर (IS_ENABLED(CONFIG_EXYNOS_MCPM))
		pmu_raw_ग_लिखोl(__pa_symbol(mcpm_entry_poपूर्णांक), S5P_INFORM0);

	पंचांगp = pmu_raw_पढ़ोl(EXYNOS_L2_OPTION(0));
	पंचांगp &= ~EXYNOS_L2_USE_RETENTION;
	pmu_raw_ग_लिखोl(पंचांगp, EXYNOS_L2_OPTION(0));

	पंचांगp = pmu_raw_पढ़ोl(EXYNOS5420_SFR_AXI_CGDIS1);
	पंचांगp |= EXYNOS5420_UFS;
	pmu_raw_ग_लिखोl(पंचांगp, EXYNOS5420_SFR_AXI_CGDIS1);

	पंचांगp = pmu_raw_पढ़ोl(EXYNOS5420_ARM_COMMON_OPTION);
	पंचांगp &= ~EXYNOS5420_L2RSTDISABLE_VALUE;
	pmu_raw_ग_लिखोl(पंचांगp, EXYNOS5420_ARM_COMMON_OPTION);

	पंचांगp = pmu_raw_पढ़ोl(EXYNOS5420_FSYS2_OPTION);
	पंचांगp |= EXYNOS5420_EMULATION;
	pmu_raw_ग_लिखोl(पंचांगp, EXYNOS5420_FSYS2_OPTION);

	पंचांगp = pmu_raw_पढ़ोl(EXYNOS5420_PSGEN_OPTION);
	पंचांगp |= EXYNOS5420_EMULATION;
	pmu_raw_ग_लिखोl(पंचांगp, EXYNOS5420_PSGEN_OPTION);
पूर्ण


अटल पूर्णांक exynos_pm_suspend(व्योम)
अणु
	exynos_pm_central_suspend();

	/* Setting SEQ_OPTION रेजिस्टर */
	pmu_raw_ग_लिखोl(S5P_USE_STANDBY_WFI0 | S5P_USE_STANDBY_WFE0,
		       S5P_CENTRAL_SEQ_OPTION);

	अगर (पढ़ो_cpuid_part() == ARM_CPU_PART_CORTEX_A9)
		exynos_cpu_save_रेजिस्टर();

	वापस 0;
पूर्ण

अटल पूर्णांक exynos5420_pm_suspend(व्योम)
अणु
	u32 this_cluster;

	exynos_pm_central_suspend();

	/* Setting SEQ_OPTION रेजिस्टर */

	this_cluster = MPIDR_AFFINITY_LEVEL(पढ़ो_cpuid_mpidr(), 1);
	अगर (!this_cluster)
		pmu_raw_ग_लिखोl(EXYNOS5420_ARM_USE_STANDBY_WFI0,
				S5P_CENTRAL_SEQ_OPTION);
	अन्यथा
		pmu_raw_ग_लिखोl(EXYNOS5420_KFC_USE_STANDBY_WFI0,
				S5P_CENTRAL_SEQ_OPTION);
	वापस 0;
पूर्ण

अटल व्योम exynos_pm_resume(व्योम)
अणु
	u32 cpuid = पढ़ो_cpuid_part();

	अगर (exynos_pm_central_resume())
		जाओ early_wakeup;

	अगर (cpuid == ARM_CPU_PART_CORTEX_A9)
		exynos_scu_enable();

	अगर (call_firmware_op(resume) == -ENOSYS
	    && cpuid == ARM_CPU_PART_CORTEX_A9)
		exynos_cpu_restore_रेजिस्टर();

early_wakeup:

	/* Clear SLEEP mode set in INFORM1 */
	pmu_raw_ग_लिखोl(0x0, S5P_INFORM1);
	exynos_set_delayed_reset_निश्चितion(true);
पूर्ण

अटल व्योम exynos3250_pm_resume(व्योम)
अणु
	u32 cpuid = पढ़ो_cpuid_part();

	अगर (exynos_pm_central_resume())
		जाओ early_wakeup;

	pmu_raw_ग_लिखोl(S5P_USE_STANDBY_WFI_ALL, S5P_CENTRAL_SEQ_OPTION);

	अगर (call_firmware_op(resume) == -ENOSYS
	    && cpuid == ARM_CPU_PART_CORTEX_A9)
		exynos_cpu_restore_रेजिस्टर();

early_wakeup:

	/* Clear SLEEP mode set in INFORM1 */
	pmu_raw_ग_लिखोl(0x0, S5P_INFORM1);
पूर्ण

अटल व्योम exynos5420_prepare_pm_resume(व्योम)
अणु
	अचिन्हित पूर्णांक mpidr, cluster;

	mpidr = पढ़ो_cpuid_mpidr();
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);

	अगर (IS_ENABLED(CONFIG_EXYNOS_MCPM))
		WARN_ON(mcpm_cpu_घातered_up());

	अगर (IS_ENABLED(CONFIG_HW_PERF_EVENTS) && cluster != 0) अणु
		/*
		 * When प्रणाली is resumed on the LITTLE/KFC core (cluster 1),
		 * the DSCR is not properly updated until the घातer is turned
		 * on also क्रम the cluster 0. Enable it क्रम a जबतक to
		 * propagate the SPNIDEN and SPIDEN संकेतs from Secure JTAG
		 * block and aव्योम undefined inकाष्ठाion issue on CP14 reset.
		 */
		pmu_raw_ग_लिखोl(S5P_CORE_LOCAL_PWR_EN,
				EXYNOS_COMMON_CONFIGURATION(0));
		pmu_raw_ग_लिखोl(0,
				EXYNOS_COMMON_CONFIGURATION(0));
	पूर्ण
पूर्ण

अटल व्योम exynos5420_pm_resume(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;

	/* Restore the CPU0 low घातer state रेजिस्टर */
	पंचांगp = pmu_raw_पढ़ोl(EXYNOS5_ARM_CORE0_SYS_PWR_REG);
	pmu_raw_ग_लिखोl(पंचांगp | S5P_CORE_LOCAL_PWR_EN,
		       EXYNOS5_ARM_CORE0_SYS_PWR_REG);

	/* Restore the sysram cpu state रेजिस्टर */
	ग_लिखोl_relaxed(pm_state.cpu_state,
		       pm_state.sysram_base + EXYNOS5420_CPU_STATE);
	अगर (pm_state.secure_firmware)
		exynos_smc(SMC_CMD_REG,
			   SMC_REG_ID_SFR_W(pm_state.sysram_phys +
					    EXYNOS5420_CPU_STATE),
			   EXYNOS_AFTR_MAGIC, 0);

	pmu_raw_ग_लिखोl(EXYNOS5420_USE_STANDBY_WFI_ALL,
			S5P_CENTRAL_SEQ_OPTION);

	अगर (exynos_pm_central_resume())
		जाओ early_wakeup;

	pmu_raw_ग_लिखोl(pm_state.pmu_spare3, S5P_PMU_SPARE3);

early_wakeup:

	पंचांगp = pmu_raw_पढ़ोl(EXYNOS5420_SFR_AXI_CGDIS1);
	पंचांगp &= ~EXYNOS5420_UFS;
	pmu_raw_ग_लिखोl(पंचांगp, EXYNOS5420_SFR_AXI_CGDIS1);

	पंचांगp = pmu_raw_पढ़ोl(EXYNOS5420_FSYS2_OPTION);
	पंचांगp &= ~EXYNOS5420_EMULATION;
	pmu_raw_ग_लिखोl(पंचांगp, EXYNOS5420_FSYS2_OPTION);

	पंचांगp = pmu_raw_पढ़ोl(EXYNOS5420_PSGEN_OPTION);
	पंचांगp &= ~EXYNOS5420_EMULATION;
	pmu_raw_ग_लिखोl(पंचांगp, EXYNOS5420_PSGEN_OPTION);

	/* Clear SLEEP mode set in INFORM1 */
	pmu_raw_ग_लिखोl(0x0, S5P_INFORM1);
पूर्ण

/*
 * Suspend Ops
 */

अटल पूर्णांक exynos_suspend_enter(suspend_state_t state)
अणु
	u32 eपूर्णांक_wakeup_mask = exynos_पढ़ो_eपूर्णांक_wakeup_mask();
	पूर्णांक ret;

	pr_debug("%s: suspending the system...\n", __func__);

	pr_debug("%s: wakeup masks: %08x,%08x\n", __func__,
		  exynos_irqwake_पूर्णांकmask, eपूर्णांक_wakeup_mask);

	अगर (exynos_irqwake_पूर्णांकmask == -1U
	    && eपूर्णांक_wakeup_mask == EXYNOS_EINT_WAKEUP_MASK_DISABLED) अणु
		pr_err("%s: No wake-up sources!\n", __func__);
		pr_err("%s: Aborting sleep\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (pm_data->pm_prepare)
		pm_data->pm_prepare();
	flush_cache_all();

	ret = call_firmware_op(suspend);
	अगर (ret == -ENOSYS)
		ret = cpu_suspend(0, pm_data->cpu_suspend);
	अगर (ret)
		वापस ret;

	अगर (pm_data->pm_resume_prepare)
		pm_data->pm_resume_prepare();

	pr_debug("%s: wakeup stat: %08x\n", __func__,
			pmu_raw_पढ़ोl(S5P_WAKEUP_STAT));

	pr_debug("%s: resuming the system...\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_suspend_prepare(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * REVISIT: It would be better अगर काष्ठा platक्रमm_suspend_ops
	 * .prepare handler get the suspend_state_t as a parameter to
	 * aव्योम hard-coding the suspend to mem state. It's safe to करो
	 * it now only because the suspend_valid_only_mem function is
	 * used as the .valid callback used to check अगर a given state
	 * is supported by the platक्रमm anyways.
	 */
	ret = regulator_suspend_prepare(PM_SUSPEND_MEM);
	अगर (ret) अणु
		pr_err("Failed to prepare regulators for suspend (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम exynos_suspend_finish(व्योम)
अणु
	पूर्णांक ret;

	ret = regulator_suspend_finish();
	अगर (ret)
		pr_warn("Failed to resume regulators from suspend (%d)\n", ret);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops exynos_suspend_ops = अणु
	.enter		= exynos_suspend_enter,
	.prepare	= exynos_suspend_prepare,
	.finish		= exynos_suspend_finish,
	.valid		= suspend_valid_only_mem,
पूर्ण;

अटल स्थिर काष्ठा exynos_pm_data exynos3250_pm_data = अणु
	.wkup_irq	= exynos3250_wkup_irq,
	.wake_disable_mask = ((0xFF << 8) | (0x1F << 1)),
	.pm_suspend	= exynos_pm_suspend,
	.pm_resume	= exynos3250_pm_resume,
	.pm_prepare	= exynos3250_pm_prepare,
	.cpu_suspend	= exynos3250_cpu_suspend,
पूर्ण;

अटल स्थिर काष्ठा exynos_pm_data exynos4_pm_data = अणु
	.wkup_irq	= exynos4_wkup_irq,
	.wake_disable_mask = ((0xFF << 8) | (0x1F << 1)),
	.pm_suspend	= exynos_pm_suspend,
	.pm_resume	= exynos_pm_resume,
	.pm_prepare	= exynos_pm_prepare,
	.cpu_suspend	= exynos_cpu_suspend,
पूर्ण;

अटल स्थिर काष्ठा exynos_pm_data exynos5250_pm_data = अणु
	.wkup_irq	= exynos5250_wkup_irq,
	.wake_disable_mask = ((0xFF << 8) | (0x1F << 1)),
	.pm_suspend	= exynos_pm_suspend,
	.pm_resume	= exynos_pm_resume,
	.pm_prepare	= exynos_pm_prepare,
	.cpu_suspend	= exynos_cpu_suspend,
पूर्ण;

अटल स्थिर काष्ठा exynos_pm_data exynos5420_pm_data = अणु
	.wkup_irq	= exynos5250_wkup_irq,
	.wake_disable_mask = (0x7F << 7) | (0x1F << 1),
	.pm_resume_prepare = exynos5420_prepare_pm_resume,
	.pm_resume	= exynos5420_pm_resume,
	.pm_suspend	= exynos5420_pm_suspend,
	.pm_prepare	= exynos5420_pm_prepare,
	.cpu_suspend	= exynos5420_cpu_suspend,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_pmu_of_device_ids[] __initस्थिर = अणु
	अणु
		.compatible = "samsung,exynos3250-pmu",
		.data = &exynos3250_pm_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos4210-pmu",
		.data = &exynos4_pm_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos4412-pmu",
		.data = &exynos4_pm_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos5250-pmu",
		.data = &exynos5250_pm_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos5420-pmu",
		.data = &exynos5420_pm_data,
	पूर्ण,
	अणु /*sentinel*/ पूर्ण,
पूर्ण;

अटल काष्ठा syscore_ops exynos_pm_syscore_ops;

व्योम __init exynos_pm_init(व्योम)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np;
	u32 पंचांगp;

	np = of_find_matching_node_and_match(शून्य, exynos_pmu_of_device_ids, &match);
	अगर (!np) अणु
		pr_err("Failed to find PMU node\n");
		वापस;
	पूर्ण

	अगर (WARN_ON(!of_find_property(np, "interrupt-controller", शून्य))) अणु
		pr_warn("Outdated DT detected, suspend/resume will NOT work\n");
		of_node_put(np);
		वापस;
	पूर्ण
	of_node_put(np);

	pm_data = (स्थिर काष्ठा exynos_pm_data *) match->data;

	/* All wakeup disable */
	पंचांगp = pmu_raw_पढ़ोl(S5P_WAKEUP_MASK);
	पंचांगp |= pm_data->wake_disable_mask;
	pmu_raw_ग_लिखोl(पंचांगp, S5P_WAKEUP_MASK);

	exynos_pm_syscore_ops.suspend	= pm_data->pm_suspend;
	exynos_pm_syscore_ops.resume	= pm_data->pm_resume;

	रेजिस्टर_syscore_ops(&exynos_pm_syscore_ops);
	suspend_set_ops(&exynos_suspend_ops);

	/*
	 * Applicable as of now only to Exynos542x. If booted under secure
	 * firmware, the non-secure region of sysram should be used.
	 */
	अगर (exynos_secure_firmware_available()) अणु
		pm_state.sysram_phys = sysram_base_phys;
		pm_state.sysram_base = sysram_ns_base_addr;
		pm_state.secure_firmware = true;
	पूर्ण अन्यथा अणु
		pm_state.sysram_base = sysram_base_addr;
	पूर्ण
पूर्ण
