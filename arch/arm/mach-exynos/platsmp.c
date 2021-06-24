<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
//
// Cloned from linux/arch/arm/mach-vexpress/platsmp.c
//
//  Copyright (C) 2002 ARM Ltd.
//  All Rights Reserved

#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/soc/samsung/exynos-regs-pmu.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/firmware.h>

#समावेश "common.h"

बाह्य व्योम exynos4_secondary_startup(व्योम);

/* XXX exynos_pen_release is cargo culted code - DO NOT COPY XXX */
अस्थिर पूर्णांक exynos_pen_release = -1;

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल अंतरभूत व्योम cpu_leave_lowघातer(u32 core_id)
अणु
	अचिन्हित पूर्णांक v;

	यंत्र अस्थिर(
	"mrc	p15, 0, %0, c1, c0, 0\n"
	"	orr	%0, %0, %1\n"
	"	mcr	p15, 0, %0, c1, c0, 0\n"
	"	mrc	p15, 0, %0, c1, c0, 1\n"
	"	orr	%0, %0, %2\n"
	"	mcr	p15, 0, %0, c1, c0, 1\n"
	  : "=&r" (v)
	  : "Ir" (CR_C), "Ir" (0x40)
	  : "cc");
पूर्ण

अटल अंतरभूत व्योम platक्रमm_करो_lowघातer(अचिन्हित पूर्णांक cpu, पूर्णांक *spurious)
अणु
	u32 mpidr = cpu_logical_map(cpu);
	u32 core_id = MPIDR_AFFINITY_LEVEL(mpidr, 0);

	क्रम (;;) अणु

		/* Turn the CPU off on next WFI inकाष्ठाion. */
		exynos_cpu_घातer_करोwn(core_id);

		wfi();

		अगर (exynos_pen_release == core_id) अणु
			/*
			 * OK, proper wakeup, we're करोne
			 */
			अवरोध;
		पूर्ण

		/*
		 * Getting here, means that we have come out of WFI without
		 * having been woken up - this shouldn't happen
		 *
		 * Just note it happening - when we're woken, we can report
		 * its occurrence.
		 */
		(*spurious)++;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

/**
 * exynos_cpu_घातer_करोwn() - घातer करोwn the specअगरied cpu
 * @cpu: the cpu to घातer करोwn
 *
 * Power करोwn the specअगरied cpu. The sequence must be finished by a
 * call to cpu_करो_idle()
 */
व्योम exynos_cpu_घातer_करोwn(पूर्णांक cpu)
अणु
	u32 core_conf;

	अगर (cpu == 0 && (soc_is_exynos5420() || soc_is_exynos5800())) अणु
		/*
		 * Bypass घातer करोwn क्रम CPU0 during suspend. Check क्रम
		 * the SYS_PWR_REG value to decide अगर we are suspending
		 * the प्रणाली.
		 */
		पूर्णांक val = pmu_raw_पढ़ोl(EXYNOS5_ARM_CORE0_SYS_PWR_REG);

		अगर (!(val & S5P_CORE_LOCAL_PWR_EN))
			वापस;
	पूर्ण

	core_conf = pmu_raw_पढ़ोl(EXYNOS_ARM_CORE_CONFIGURATION(cpu));
	core_conf &= ~S5P_CORE_LOCAL_PWR_EN;
	pmu_raw_ग_लिखोl(core_conf, EXYNOS_ARM_CORE_CONFIGURATION(cpu));
पूर्ण

/**
 * exynos_cpu_घातer_up() - घातer up the specअगरied cpu
 * @cpu: the cpu to घातer up
 *
 * Power up the specअगरied cpu
 */
व्योम exynos_cpu_घातer_up(पूर्णांक cpu)
अणु
	u32 core_conf = S5P_CORE_LOCAL_PWR_EN;

	अगर (soc_is_exynos3250())
		core_conf |= S5P_CORE_AUTOWAKEUP_EN;

	pmu_raw_ग_लिखोl(core_conf,
			EXYNOS_ARM_CORE_CONFIGURATION(cpu));
पूर्ण

/**
 * exynos_cpu_घातer_state() - वापसs the घातer state of the cpu
 * @cpu: the cpu to retrieve the घातer state from
 */
पूर्णांक exynos_cpu_घातer_state(पूर्णांक cpu)
अणु
	वापस (pmu_raw_पढ़ोl(EXYNOS_ARM_CORE_STATUS(cpu)) &
			S5P_CORE_LOCAL_PWR_EN);
पूर्ण

/**
 * exynos_cluster_घातer_करोwn() - घातer करोwn the specअगरied cluster
 * @cluster: the cluster to घातer करोwn
 */
व्योम exynos_cluster_घातer_करोwn(पूर्णांक cluster)
अणु
	pmu_raw_ग_लिखोl(0, EXYNOS_COMMON_CONFIGURATION(cluster));
पूर्ण

/**
 * exynos_cluster_घातer_up() - घातer up the specअगरied cluster
 * @cluster: the cluster to घातer up
 */
व्योम exynos_cluster_घातer_up(पूर्णांक cluster)
अणु
	pmu_raw_ग_लिखोl(S5P_CORE_LOCAL_PWR_EN,
			EXYNOS_COMMON_CONFIGURATION(cluster));
पूर्ण

/**
 * exynos_cluster_घातer_state() - वापसs the घातer state of the cluster
 * @cluster: the cluster to retrieve the घातer state from
 *
 */
पूर्णांक exynos_cluster_घातer_state(पूर्णांक cluster)
अणु
	वापस (pmu_raw_पढ़ोl(EXYNOS_COMMON_STATUS(cluster)) &
		S5P_CORE_LOCAL_PWR_EN);
पूर्ण

/**
 * exynos_scu_enable() - enables SCU क्रम Cortex-A9 based प्रणाली
 */
व्योम exynos_scu_enable(व्योम)
अणु
	काष्ठा device_node *np;
	अटल व्योम __iomem *scu_base;

	अगर (!scu_base) अणु
		np = of_find_compatible_node(शून्य, शून्य, "arm,cortex-a9-scu");
		अगर (np) अणु
			scu_base = of_iomap(np, 0);
			of_node_put(np);
		पूर्ण अन्यथा अणु
			scu_base = ioremap(scu_a9_get_base(), SZ_4K);
		पूर्ण
	पूर्ण
	scu_enable(scu_base);
पूर्ण

अटल व्योम __iomem *cpu_boot_reg_base(व्योम)
अणु
	अगर (soc_is_exynos4210() && exynos_rev() == EXYNOS4210_REV_1_1)
		वापस pmu_base_addr + S5P_INFORM5;
	वापस sysram_base_addr;
पूर्ण

अटल अंतरभूत व्योम __iomem *cpu_boot_reg(पूर्णांक cpu)
अणु
	व्योम __iomem *boot_reg;

	boot_reg = cpu_boot_reg_base();
	अगर (!boot_reg)
		वापस IOMEM_ERR_PTR(-ENODEV);
	अगर (soc_is_exynos4412())
		boot_reg += 4*cpu;
	अन्यथा अगर (soc_is_exynos5420() || soc_is_exynos5800())
		boot_reg += 4;
	वापस boot_reg;
पूर्ण

/*
 * Set wake up by local घातer mode and execute software reset क्रम given core.
 *
 * Currently this is needed only when booting secondary CPU on Exynos3250.
 */
व्योम exynos_core_restart(u32 core_id)
अणु
	अचिन्हित पूर्णांक समयout = 16;
	u32 val;

	अगर (!soc_is_exynos3250())
		वापस;

	जबतक (समयout && !pmu_raw_पढ़ोl(S5P_PMU_SPARE2)) अणु
		समयout--;
		udelay(10);
	पूर्ण
	अगर (समयout == 0) अणु
		pr_err("cpu core %u restart failed\n", core_id);
		वापस;
	पूर्ण
	udelay(10);

	val = pmu_raw_पढ़ोl(EXYNOS_ARM_CORE_STATUS(core_id));
	val |= S5P_CORE_WAKEUP_FROM_LOCAL_CFG;
	pmu_raw_ग_लिखोl(val, EXYNOS_ARM_CORE_STATUS(core_id));

	pmu_raw_ग_लिखोl(EXYNOS_CORE_PO_RESET(core_id), EXYNOS_SWRESET);
पूर्ण

/*
 * XXX CARGO CULTED CODE - DO NOT COPY XXX
 *
 * Write exynos_pen_release in a way that is guaranteed to be visible to
 * all observers, irrespective of whether they're taking part in coherency
 * or not.  This is necessary क्रम the hotplug code to work reliably.
 */
अटल व्योम exynos_ग_लिखो_pen_release(पूर्णांक val)
अणु
	exynos_pen_release = val;
	smp_wmb();
	sync_cache_w(&exynos_pen_release);
पूर्ण

अटल DEFINE_SPINLOCK(boot_lock);

अटल व्योम exynos_secondary_init(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * let the primary processor know we're out of the
	 * pen, then head off पूर्णांकo the C entry poपूर्णांक
	 */
	exynos_ग_लिखो_pen_release(-1);

	/*
	 * Synchronise with the boot thपढ़ो.
	 */
	spin_lock(&boot_lock);
	spin_unlock(&boot_lock);
पूर्ण

पूर्णांक exynos_set_boot_addr(u32 core_id, अचिन्हित दीर्घ boot_addr)
अणु
	पूर्णांक ret;

	/*
	 * Try to set boot address using firmware first
	 * and fall back to boot रेजिस्टर अगर it fails.
	 */
	ret = call_firmware_op(set_cpu_boot_addr, core_id, boot_addr);
	अगर (ret && ret != -ENOSYS)
		जाओ fail;
	अगर (ret == -ENOSYS) अणु
		व्योम __iomem *boot_reg = cpu_boot_reg(core_id);

		अगर (IS_ERR(boot_reg)) अणु
			ret = PTR_ERR(boot_reg);
			जाओ fail;
		पूर्ण
		ग_लिखोl_relaxed(boot_addr, boot_reg);
		ret = 0;
	पूर्ण
fail:
	वापस ret;
पूर्ण

पूर्णांक exynos_get_boot_addr(u32 core_id, अचिन्हित दीर्घ *boot_addr)
अणु
	पूर्णांक ret;

	/*
	 * Try to get boot address using firmware first
	 * and fall back to boot रेजिस्टर अगर it fails.
	 */
	ret = call_firmware_op(get_cpu_boot_addr, core_id, boot_addr);
	अगर (ret && ret != -ENOSYS)
		जाओ fail;
	अगर (ret == -ENOSYS) अणु
		व्योम __iomem *boot_reg = cpu_boot_reg(core_id);

		अगर (IS_ERR(boot_reg)) अणु
			ret = PTR_ERR(boot_reg);
			जाओ fail;
		पूर्ण
		*boot_addr = पढ़ोl_relaxed(boot_reg);
		ret = 0;
	पूर्ण
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक exynos_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित दीर्घ समयout;
	u32 mpidr = cpu_logical_map(cpu);
	u32 core_id = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	पूर्णांक ret = -ENOSYS;

	/*
	 * Set synchronisation state between this boot processor
	 * and the secondary one
	 */
	spin_lock(&boot_lock);

	/*
	 * The secondary processor is रुकोing to be released from
	 * the holding pen - release it, then रुको क्रम it to flag
	 * that it has been released by resetting exynos_pen_release.
	 *
	 * Note that "exynos_pen_release" is the hardware CPU core ID, whereas
	 * "cpu" is Linux's पूर्णांकernal ID.
	 */
	exynos_ग_लिखो_pen_release(core_id);

	अगर (!exynos_cpu_घातer_state(core_id)) अणु
		exynos_cpu_घातer_up(core_id);
		समयout = 10;

		/* रुको max 10 ms until cpu1 is on */
		जबतक (exynos_cpu_घातer_state(core_id)
		       != S5P_CORE_LOCAL_PWR_EN) अणु
			अगर (समयout == 0)
				अवरोध;
			समयout--;
			mdelay(1);
		पूर्ण

		अगर (समयout == 0) अणु
			prपूर्णांकk(KERN_ERR "cpu1 power enable failed");
			spin_unlock(&boot_lock);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	exynos_core_restart(core_id);

	/*
	 * Send the secondary CPU a soft पूर्णांकerrupt, thereby causing
	 * the boot monitor to पढ़ो the प्रणाली wide flags रेजिस्टर,
	 * and branch to the address found there.
	 */

	समयout = jअगरfies + (1 * HZ);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अचिन्हित दीर्घ boot_addr;

		smp_rmb();

		boot_addr = __pa_symbol(exynos4_secondary_startup);

		ret = exynos_set_boot_addr(core_id, boot_addr);
		अगर (ret)
			जाओ fail;

		call_firmware_op(cpu_boot, core_id);

		अगर (soc_is_exynos3250())
			dsb_sev();
		अन्यथा
			arch_send_wakeup_ipi_mask(cpumask_of(cpu));

		अगर (exynos_pen_release == -1)
			अवरोध;

		udelay(10);
	पूर्ण

	अगर (exynos_pen_release != -1)
		ret = -ETIMEDOUT;

	/*
	 * now the secondary core is starting up let it run its
	 * calibrations, then रुको क्रम it to finish
	 */
fail:
	spin_unlock(&boot_lock);

	वापस exynos_pen_release != -1 ? ret : 0;
पूर्ण

अटल व्योम __init exynos_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	exynos_sysram_init();

	exynos_set_delayed_reset_निश्चितion(true);

	अगर (पढ़ो_cpuid_part() == ARM_CPU_PART_CORTEX_A9)
		exynos_scu_enable();
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
/*
 * platक्रमm-specअगरic code to shutकरोwn a CPU
 *
 * Called with IRQs disabled
 */
अटल व्योम exynos_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक spurious = 0;
	u32 mpidr = cpu_logical_map(cpu);
	u32 core_id = MPIDR_AFFINITY_LEVEL(mpidr, 0);

	v7_निकास_coherency_flush(louis);

	platक्रमm_करो_lowघातer(cpu, &spurious);

	/*
	 * bring this CPU back पूर्णांकo the world of cache
	 * coherency, and then restore पूर्णांकerrupts
	 */
	cpu_leave_lowघातer(core_id);

	अगर (spurious)
		pr_warn("CPU%u: %u spurious wakeup calls\n", cpu, spurious);
पूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

स्थिर काष्ठा smp_operations exynos_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= exynos_smp_prepare_cpus,
	.smp_secondary_init	= exynos_secondary_init,
	.smp_boot_secondary	= exynos_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= exynos_cpu_die,
#पूर्ण_अगर
पूर्ण;
