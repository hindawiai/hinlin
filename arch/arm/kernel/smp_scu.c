<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/smp_scu.c
 *
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 */
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cputype.h>

#घोषणा SCU_CTRL		0x00
#घोषणा SCU_ENABLE		(1 << 0)
#घोषणा SCU_STANDBY_ENABLE	(1 << 5)
#घोषणा SCU_CONFIG		0x04
#घोषणा SCU_CPU_STATUS		0x08
#घोषणा SCU_CPU_STATUS_MASK	GENMASK(1, 0)
#घोषणा SCU_INVALIDATE		0x0c
#घोषणा SCU_FPGA_REVISION	0x10

#अगर_घोषित CONFIG_SMP
/*
 * Get the number of CPU cores from the SCU configuration
 */
अचिन्हित पूर्णांक __init scu_get_core_count(व्योम __iomem *scu_base)
अणु
	अचिन्हित पूर्णांक ncores = पढ़ोl_relaxed(scu_base + SCU_CONFIG);
	वापस (ncores & 0x03) + 1;
पूर्ण

/*
 * Enable the SCU
 */
व्योम scu_enable(व्योम __iomem *scu_base)
अणु
	u32 scu_ctrl;

#अगर_घोषित CONFIG_ARM_ERRATA_764369
	/* Cortex-A9 only */
	अगर ((पढ़ो_cpuid_id() & 0xff0ffff0) == 0x410fc090) अणु
		scu_ctrl = पढ़ोl_relaxed(scu_base + 0x30);
		अगर (!(scu_ctrl & 1))
			ग_लिखोl_relaxed(scu_ctrl | 0x1, scu_base + 0x30);
	पूर्ण
#पूर्ण_अगर

	scu_ctrl = पढ़ोl_relaxed(scu_base + SCU_CTRL);
	/* alपढ़ोy enabled? */
	अगर (scu_ctrl & SCU_ENABLE)
		वापस;

	scu_ctrl |= SCU_ENABLE;

	/* Cortex-A9 earlier than r2p0 has no standby bit in SCU */
	अगर ((पढ़ो_cpuid_id() & 0xff0ffff0) == 0x410fc090 &&
	    (पढ़ो_cpuid_id() & 0x00f0000f) >= 0x00200000)
		scu_ctrl |= SCU_STANDBY_ENABLE;

	ग_लिखोl_relaxed(scu_ctrl, scu_base + SCU_CTRL);

	/*
	 * Ensure that the data accessed by CPU0 beक्रमe the SCU was
	 * initialised is visible to the other CPUs.
	 */
	flush_cache_all();
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक scu_set_घातer_mode_पूर्णांकernal(व्योम __iomem *scu_base,
				       अचिन्हित पूर्णांक logical_cpu,
				       अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक cpu = MPIDR_AFFINITY_LEVEL(cpu_logical_map(logical_cpu), 0);

	अगर (mode > 3 || mode == 1 || cpu > 3)
		वापस -EINVAL;

	val = पढ़ोb_relaxed(scu_base + SCU_CPU_STATUS + cpu);
	val &= ~SCU_CPU_STATUS_MASK;
	val |= mode;
	ग_लिखोb_relaxed(val, scu_base + SCU_CPU_STATUS + cpu);

	वापस 0;
पूर्ण

/*
 * Set the executing CPUs घातer mode as defined.  This will be in
 * preparation क्रम it executing a WFI inकाष्ठाion.
 *
 * This function must be called with preemption disabled, and as it
 * has the side effect of disabling coherency, caches must have been
 * flushed.  Interrupts must also have been disabled.
 */
पूर्णांक scu_घातer_mode(व्योम __iomem *scu_base, अचिन्हित पूर्णांक mode)
अणु
	वापस scu_set_घातer_mode_पूर्णांकernal(scu_base, smp_processor_id(), mode);
पूर्ण

/*
 * Set the given (logical) CPU's घातer mode to SCU_PM_NORMAL.
 */
पूर्णांक scu_cpu_घातer_enable(व्योम __iomem *scu_base, अचिन्हित पूर्णांक cpu)
अणु
	वापस scu_set_घातer_mode_पूर्णांकernal(scu_base, cpu, SCU_PM_NORMAL);
पूर्ण

पूर्णांक scu_get_cpu_घातer_mode(व्योम __iomem *scu_base, अचिन्हित पूर्णांक logical_cpu)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक cpu = MPIDR_AFFINITY_LEVEL(cpu_logical_map(logical_cpu), 0);

	अगर (cpu > 3)
		वापस -EINVAL;

	val = पढ़ोb_relaxed(scu_base + SCU_CPU_STATUS + cpu);
	val &= SCU_CPU_STATUS_MASK;

	वापस val;
पूर्ण
