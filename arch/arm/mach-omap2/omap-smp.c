<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP4 SMP source file. It contains platक्रमm specअगरic functions
 * needed क्रम the linux smp kernel.
 *
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Author:
 *      Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * Platक्रमm file needed क्रम the OMAP4 SMP. This file is based on arm
 * realview smp platक्रमm.
 * * Copyright (c) 2002 ARM Limited.
 */
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip/arm-gic.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/virt.h>

#समावेश "omap-secure.h"
#समावेश "omap-wakeupgen.h"
#समावेश <यंत्र/cputype.h>

#समावेश "soc.h"
#समावेश "iomap.h"
#समावेश "common.h"
#समावेश "clockdomain.h"
#समावेश "pm.h"

#घोषणा CPU_MASK		0xff0ffff0
#घोषणा CPU_CORTEX_A9		0x410FC090
#घोषणा CPU_CORTEX_A15		0x410FC0F0

#घोषणा OMAP5_CORE_COUNT	0x2

#घोषणा AUX_CORE_BOOT0_GP_RELEASE	0x020
#घोषणा AUX_CORE_BOOT0_HS_RELEASE	0x200

काष्ठा omap_smp_config अणु
	अचिन्हित दीर्घ cpu1_rstctrl_pa;
	व्योम __iomem *cpu1_rstctrl_va;
	व्योम __iomem *scu_base;
	व्योम __iomem *wakeupgen_base;
	व्योम *startup_addr;
पूर्ण;

अटल काष्ठा omap_smp_config cfg;

अटल स्थिर काष्ठा omap_smp_config omap443x_cfg __initस्थिर = अणु
	.cpu1_rstctrl_pa = 0x4824380c,
	.startup_addr = omap4_secondary_startup,
पूर्ण;

अटल स्थिर काष्ठा omap_smp_config omap446x_cfg __initस्थिर = अणु
	.cpu1_rstctrl_pa = 0x4824380c,
	.startup_addr = omap4460_secondary_startup,
पूर्ण;

अटल स्थिर काष्ठा omap_smp_config omap5_cfg __initस्थिर = अणु
	.cpu1_rstctrl_pa = 0x48243810,
	.startup_addr = omap5_secondary_startup,
पूर्ण;

व्योम __iomem *omap4_get_scu_base(व्योम)
अणु
	वापस cfg.scu_base;
पूर्ण

#अगर_घोषित CONFIG_OMAP5_ERRATA_801819
अटल व्योम omap5_erratum_workaround_801819(व्योम)
अणु
	u32 acr, revidr;
	u32 acr_mask;

	/* REVIDR[3] indicates erratum fix available on silicon */
	यंत्र अस्थिर ("mrc p15, 0, %0, c0, c0, 6" : "=r" (revidr));
	अगर (revidr & (0x1 << 3))
		वापस;

	यंत्र अस्थिर ("mrc p15, 0, %0, c1, c0, 1" : "=r" (acr));
	/*
	 * BIT(27) - Disables streaming. All ग_लिखो-allocate lines allocate in
	 * the L1 or L2 cache.
	 * BIT(25) - Disables streaming. All ग_लिखो-allocate lines allocate in
	 * the L1 cache.
	 */
	acr_mask = (0x3 << 25) | (0x3 << 27);
	/* करो we alपढ़ोy have it करोne.. अगर yes, skip expensive smc */
	अगर ((acr & acr_mask) == acr_mask)
		वापस;

	acr |= acr_mask;
	omap_smc1(OMAP5_DRA7_MON_SET_ACR_INDEX, acr);

	pr_debug("%s: ARM erratum workaround 801819 applied on CPU%d\n",
		 __func__, smp_processor_id());
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम omap5_erratum_workaround_801819(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HARDEN_BRANCH_PREDICTOR
/*
 * Configure ACR and enable ACTLR[0] (Enable invalidates of BTB with
 * ICIALLU) to activate the workaround क्रम secondary Core.
 * NOTE: it is assumed that the primary core's configuration is करोne
 * by the boot loader (kernel will detect a misconfiguration and complain
 * अगर this is not करोne).
 *
 * In General Purpose(GP) devices, ACR bit settings can only be करोne
 * by ROM code in "secure world" using the smc call and there is no
 * option to update the "firmware" on such devices. This also works क्रम
 * High security(HS) devices, as a backup option in हाल the
 * "update" is not करोne in the "security firmware".
 */
अटल व्योम omap5_secondary_harden_predictor(व्योम)
अणु
	u32 acr, acr_mask;

	यंत्र अस्थिर ("mrc p15, 0, %0, c1, c0, 1" : "=r" (acr));

	/*
	 * ACTLR[0] (Enable invalidates of BTB with ICIALLU)
	 */
	acr_mask = BIT(0);

	/* Do we alपढ़ोy have it करोne.. अगर yes, skip expensive smc */
	अगर ((acr & acr_mask) == acr_mask)
		वापस;

	acr |= acr_mask;
	omap_smc1(OMAP5_DRA7_MON_SET_ACR_INDEX, acr);

	pr_debug("%s: ARM ACR setup for CVE_2017_5715 applied on CPU%d\n",
		 __func__, smp_processor_id());
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम omap5_secondary_harden_predictor(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम omap4_secondary_init(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * Configure ACTRL and enable NS SMP bit access on CPU1 on HS device.
	 * OMAP44XX EMU/HS devices - CPU0 SMP bit access is enabled in PPA
	 * init and क्रम CPU1, a secure PPA API provided. CPU0 must be ON
	 * जबतक executing NS_SMP API on CPU1 and PPA version must be 1.4.0+.
	 * OMAP443X GP devices- SMP bit isn't accessible.
	 * OMAP446X GP devices - SMP bit access is enabled on both CPUs.
	 */
	अगर (soc_is_omap443x() && (omap_type() != OMAP2_DEVICE_TYPE_GP))
		omap_secure_dispatcher(OMAP4_PPA_CPU_ACTRL_SMP_INDEX,
							4, 0, 0, 0, 0, 0);

	अगर (soc_is_omap54xx() || soc_is_dra7xx()) अणु
		/*
		 * Configure the CNTFRQ रेजिस्टर क्रम the secondary cpu's which
		 * indicates the frequency of the cpu local समयrs.
		 */
		set_cntfreq();
		/* Configure ACR to disable streaming WA क्रम 801819 */
		omap5_erratum_workaround_801819();
		/* Enable ACR to allow क्रम ICUALLU workaround */
		omap5_secondary_harden_predictor();
	पूर्ण
पूर्ण

अटल पूर्णांक omap4_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अटल काष्ठा घड़ीकरोमुख्य *cpu1_clkdm;
	अटल bool booted;
	अटल काष्ठा घातerकरोमुख्य *cpu1_pwrdm;

	/*
	 * Update the AuxCoreBoot0 with boot state क्रम secondary core.
	 * omap4_secondary_startup() routine will hold the secondary core till
	 * the AuxCoreBoot1 रेजिस्टर is updated with cpu state
	 * A barrier is added to ensure that ग_लिखो buffer is drained
	 */
	अगर (omap_secure_apis_support())
		omap_modअगरy_auxcoreboot0(AUX_CORE_BOOT0_HS_RELEASE,
					 0xfffffdff);
	अन्यथा
		ग_लिखोl_relaxed(AUX_CORE_BOOT0_GP_RELEASE,
			       cfg.wakeupgen_base + OMAP_AUX_CORE_BOOT_0);

	अगर (!cpu1_clkdm && !cpu1_pwrdm) अणु
		cpu1_clkdm = clkdm_lookup("mpu1_clkdm");
		cpu1_pwrdm = pwrdm_lookup("cpu1_pwrdm");
	पूर्ण

	/*
	 * The SGI(Software Generated Interrupts) are not wakeup capable
	 * from low घातer states. This is known limitation on OMAP4 and
	 * needs to be worked around by using software क्रमced घड़ीकरोमुख्य
	 * wake-up. To wakeup CPU1, CPU0 क्रमces the CPU1 घड़ीकरोमुख्य to
	 * software क्रमce wakeup. The घड़ीकरोमुख्य is then put back to
	 * hardware supervised mode.
	 * More details can be found in OMAP4430 TRM - Version J
	 * Section :
	 *	4.3.4.2 Power States of CPU0 and CPU1
	 */
	अगर (booted && cpu1_pwrdm && cpu1_clkdm) अणु
		/*
		 * GIC distributor control रेजिस्टर has changed between
		 * CortexA9 r1pX and r2pX. The Control Register secure
		 * banked version is now composed of 2 bits:
		 * bit 0 == Secure Enable
		 * bit 1 == Non-Secure Enable
		 * The Non-Secure banked रेजिस्टर has not changed
		 * Because the ROM Code is based on the r1pX GIC, the CPU1
		 * GIC restoration will cause a problem to CPU0 Non-Secure SW.
		 * The workaround must be:
		 * 1) Beक्रमe करोing the CPU1 wakeup, CPU0 must disable
		 * the GIC distributor
		 * 2) CPU1 must re-enable the GIC distributor on
		 * it's wakeup path.
		 */
		अगर (IS_PM44XX_ERRATUM(PM_OMAP4_ROM_SMP_BOOT_ERRATUM_GICD)) अणु
			local_irq_disable();
			gic_dist_disable();
		पूर्ण

		/*
		 * Ensure that CPU घातer state is set to ON to aव्योम CPU
		 * घातerकरोमुख्य transition on wfi
		 */
		clkdm_deny_idle_nolock(cpu1_clkdm);
		pwrdm_set_next_pwrst(cpu1_pwrdm, PWRDM_POWER_ON);
		clkdm_allow_idle_nolock(cpu1_clkdm);

		अगर (IS_PM44XX_ERRATUM(PM_OMAP4_ROM_SMP_BOOT_ERRATUM_GICD)) अणु
			जबतक (gic_dist_disabled()) अणु
				udelay(1);
				cpu_relax();
			पूर्ण
			gic_समयr_retrigger();
			local_irq_enable();
		पूर्ण
	पूर्ण अन्यथा अणु
		dsb_sev();
		booted = true;
	पूर्ण

	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	वापस 0;
पूर्ण

/*
 * Initialise the CPU possible map early - this describes the CPUs
 * which may be present or become present in the प्रणाली.
 */
अटल व्योम __init omap4_smp_init_cpus(व्योम)
अणु
	अचिन्हित पूर्णांक i = 0, ncores = 1, cpu_id;

	/* Use ARM cpuid check here, as SoC detection will not work so early */
	cpu_id = पढ़ो_cpuid_id() & CPU_MASK;
	अगर (cpu_id == CPU_CORTEX_A9) अणु
		/*
		 * Currently we can't call ioremap here because
		 * SoC detection won't work until after init_early.
		 */
		cfg.scu_base =  OMAP2_L4_IO_ADDRESS(scu_a9_get_base());
		BUG_ON(!cfg.scu_base);
		ncores = scu_get_core_count(cfg.scu_base);
	पूर्ण अन्यथा अगर (cpu_id == CPU_CORTEX_A15) अणु
		ncores = OMAP5_CORE_COUNT;
	पूर्ण

	/* sanity check */
	अगर (ncores > nr_cpu_ids) अणु
		pr_warn("SMP: %u cores greater than maximum (%u), clipping\n",
			ncores, nr_cpu_ids);
		ncores = nr_cpu_ids;
	पूर्ण

	क्रम (i = 0; i < ncores; i++)
		set_cpu_possible(i, true);
पूर्ण

/*
 * For now, just make sure the start-up address is not within the booting
 * kernel space as that means we just overwrote whatever secondary_startup()
 * code there was.
 */
अटल bool __init omap4_smp_cpu1_startup_valid(अचिन्हित दीर्घ addr)
अणु
	अगर ((addr >= __pa(PAGE_OFFSET)) && (addr <= __pa(__bss_start)))
		वापस false;

	वापस true;
पूर्ण

/*
 * We may need to reset CPU1 beक्रमe configuring, otherwise kexec boot can end
 * up trying to use old kernel startup address or suspend-resume will
 * occasionally fail to bring up CPU1 on 4430 अगर CPU1 fails to enter deeper
 * idle states.
 */
अटल व्योम __init omap4_smp_maybe_reset_cpu1(काष्ठा omap_smp_config *c)
अणु
	अचिन्हित दीर्घ cpu1_startup_pa, cpu1_ns_pa_addr;
	bool needs_reset = false;
	u32 released;

	अगर (omap_secure_apis_support())
		released = omap_पढ़ो_auxcoreboot0() & AUX_CORE_BOOT0_HS_RELEASE;
	अन्यथा
		released = पढ़ोl_relaxed(cfg.wakeupgen_base +
					 OMAP_AUX_CORE_BOOT_0) &
						AUX_CORE_BOOT0_GP_RELEASE;
	अगर (released) अणु
		pr_warn("smp: CPU1 not parked?\n");

		वापस;
	पूर्ण

	cpu1_startup_pa = पढ़ोl_relaxed(cfg.wakeupgen_base +
					OMAP_AUX_CORE_BOOT_1);

	/* Did the configured secondary_startup() get overwritten? */
	अगर (!omap4_smp_cpu1_startup_valid(cpu1_startup_pa))
		needs_reset = true;

	/*
	 * If omap4 or 5 has NS_PA_ADDR configured, CPU1 may be in a
	 * deeper idle state in WFI and will wake to an invalid address.
	 */
	अगर ((soc_is_omap44xx() || soc_is_omap54xx())) अणु
		cpu1_ns_pa_addr = omap4_get_cpu1_ns_pa_addr();
		अगर (!omap4_smp_cpu1_startup_valid(cpu1_ns_pa_addr))
			needs_reset = true;
	पूर्ण अन्यथा अणु
		cpu1_ns_pa_addr = 0;
	पूर्ण

	अगर (!needs_reset || !c->cpu1_rstctrl_va)
		वापस;

	pr_info("smp: CPU1 parked within kernel, needs reset (0x%lx 0x%lx)\n",
		cpu1_startup_pa, cpu1_ns_pa_addr);

	ग_लिखोl_relaxed(1, c->cpu1_rstctrl_va);
	पढ़ोl_relaxed(c->cpu1_rstctrl_va);
	ग_लिखोl_relaxed(0, c->cpu1_rstctrl_va);
पूर्ण

अटल व्योम __init omap4_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	स्थिर काष्ठा omap_smp_config *c = शून्य;

	अगर (soc_is_omap443x())
		c = &omap443x_cfg;
	अन्यथा अगर (soc_is_omap446x())
		c = &omap446x_cfg;
	अन्यथा अगर (soc_is_dra74x() || soc_is_omap54xx() || soc_is_dra76x())
		c = &omap5_cfg;

	अगर (!c) अणु
		pr_err("%s Unknown SMP SoC?\n", __func__);
		वापस;
	पूर्ण

	/* Must preserve cfg.scu_base set earlier */
	cfg.cpu1_rstctrl_pa = c->cpu1_rstctrl_pa;
	cfg.startup_addr = c->startup_addr;
	cfg.wakeupgen_base = omap_get_wakeupgen_base();

	अगर (soc_is_dra74x() || soc_is_omap54xx() || soc_is_dra76x()) अणु
		अगर ((__boot_cpu_mode & MODE_MASK) == HYP_MODE)
			cfg.startup_addr = omap5_secondary_hyp_startup;
		omap5_erratum_workaround_801819();
	पूर्ण

	cfg.cpu1_rstctrl_va = ioremap(cfg.cpu1_rstctrl_pa, 4);
	अगर (!cfg.cpu1_rstctrl_va)
		वापस;

	/*
	 * Initialise the SCU and wake up the secondary core using
	 * wakeup_secondary().
	 */
	अगर (cfg.scu_base)
		scu_enable(cfg.scu_base);

	omap4_smp_maybe_reset_cpu1(&cfg);

	/*
	 * Write the address of secondary startup routine पूर्णांकo the
	 * AuxCoreBoot1 where ROM code will jump and start executing
	 * on secondary core once out of WFE
	 * A barrier is added to ensure that ग_लिखो buffer is drained
	 */
	अगर (omap_secure_apis_support())
		omap_auxcoreboot_addr(__pa_symbol(cfg.startup_addr));
	अन्यथा
		ग_लिखोl_relaxed(__pa_symbol(cfg.startup_addr),
			       cfg.wakeupgen_base + OMAP_AUX_CORE_BOOT_1);
पूर्ण

स्थिर काष्ठा smp_operations omap4_smp_ops __initस्थिर = अणु
	.smp_init_cpus		= omap4_smp_init_cpus,
	.smp_prepare_cpus	= omap4_smp_prepare_cpus,
	.smp_secondary_init	= omap4_secondary_init,
	.smp_boot_secondary	= omap4_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= omap4_cpu_die,
	.cpu_समाप्त		= omap4_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;
