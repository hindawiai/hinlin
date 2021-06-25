<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Carlo Caione <carlo@endlessm.com>
 * Copyright (C) 2017 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/smp.h>
#समावेश <linux/mfd/syscon.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/smp_plat.h>

#घोषणा MESON_SMP_SRAM_CPU_CTRL_REG		(0x00)
#घोषणा MESON_SMP_SRAM_CPU_CTRL_ADDR_REG(c)	(0x04 + ((c - 1) << 2))

#घोषणा MESON_CPU_AO_RTI_PWR_A9_CNTL0		(0x00)
#घोषणा MESON_CPU_AO_RTI_PWR_A9_CNTL1		(0x04)
#घोषणा MESON_CPU_AO_RTI_PWR_A9_MEM_PD0		(0x14)

#घोषणा MESON_CPU_PWR_A9_CNTL0_M(c)		(0x03 << ((c * 2) + 16))
#घोषणा MESON_CPU_PWR_A9_CNTL1_M(c)		(0x03 << ((c + 1) << 1))
#घोषणा MESON_CPU_PWR_A9_MEM_PD0_M(c)		(0x0f << (32 - (c * 4)))
#घोषणा MESON_CPU_PWR_A9_CNTL1_ST(c)		(0x01 << (c + 16))

अटल व्योम __iomem *sram_base;
अटल व्योम __iomem *scu_base;
अटल काष्ठा regmap *pmu;

अटल काष्ठा reset_control *meson_smp_get_core_reset(पूर्णांक cpu)
अणु
	काष्ठा device_node *np = of_get_cpu_node(cpu, 0);

	वापस of_reset_control_get_exclusive(np, शून्य);
पूर्ण

अटल व्योम meson_smp_set_cpu_ctrl(पूर्णांक cpu, bool on_off)
अणु
	u32 val = पढ़ोl(sram_base + MESON_SMP_SRAM_CPU_CTRL_REG);

	अगर (on_off)
		val |= BIT(cpu);
	अन्यथा
		val &= ~BIT(cpu);

	/* keep bit 0 always enabled */
	val |= BIT(0);

	ग_लिखोl(val, sram_base + MESON_SMP_SRAM_CPU_CTRL_REG);
पूर्ण

अटल व्योम __init meson_smp_prepare_cpus(स्थिर अक्षर *scu_compatible,
					  स्थिर अक्षर *pmu_compatible,
					  स्थिर अक्षर *sram_compatible)
अणु
	अटल काष्ठा device_node *node;

	/* SMP SRAM */
	node = of_find_compatible_node(शून्य, शून्य, sram_compatible);
	अगर (!node) अणु
		pr_err("Missing SRAM node\n");
		वापस;
	पूर्ण

	sram_base = of_iomap(node, 0);
	अगर (!sram_base) अणु
		pr_err("Couldn't map SRAM registers\n");
		वापस;
	पूर्ण

	/* PMU */
	pmu = syscon_regmap_lookup_by_compatible(pmu_compatible);
	अगर (IS_ERR(pmu)) अणु
		pr_err("Couldn't map PMU registers\n");
		वापस;
	पूर्ण

	/* SCU */
	node = of_find_compatible_node(शून्य, शून्य, scu_compatible);
	अगर (!node) अणु
		pr_err("Missing SCU node\n");
		वापस;
	पूर्ण

	scu_base = of_iomap(node, 0);
	अगर (!scu_base) अणु
		pr_err("Couldn't map SCU registers\n");
		वापस;
	पूर्ण

	scu_enable(scu_base);
पूर्ण

अटल व्योम __init meson8b_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	meson_smp_prepare_cpus("arm,cortex-a5-scu", "amlogic,meson8b-pmu",
			       "amlogic,meson8b-smp-sram");
पूर्ण

अटल व्योम __init meson8_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	meson_smp_prepare_cpus("arm,cortex-a9-scu", "amlogic,meson8-pmu",
			       "amlogic,meson8-smp-sram");
पूर्ण

अटल व्योम meson_smp_begin_secondary_boot(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * Set the entry poपूर्णांक beक्रमe घातering on the CPU through the SCU. This
	 * is needed अगर the CPU is in "warm" state (= after rebooting the
	 * प्रणाली without घातer-cycling, or when taking the CPU offline and
	 * then taking it online again.
	 */
	ग_लिखोl(__pa_symbol(secondary_startup),
	       sram_base + MESON_SMP_SRAM_CPU_CTRL_ADDR_REG(cpu));

	/*
	 * SCU Power on CPU (needs to be करोne beक्रमe starting the CPU,
	 * otherwise the secondary CPU will not start).
	 */
	scu_cpu_घातer_enable(scu_base, cpu);
पूर्ण

अटल पूर्णांक meson_smp_finalize_secondary_boot(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + (10 * HZ);
	जबतक (पढ़ोl(sram_base + MESON_SMP_SRAM_CPU_CTRL_ADDR_REG(cpu))) अणु
		अगर (!समय_beक्रमe(jअगरfies, समयout)) अणु
			pr_err("Timeout while waiting for CPU%d status\n",
			       cpu);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	ग_लिखोl(__pa_symbol(secondary_startup),
	       sram_base + MESON_SMP_SRAM_CPU_CTRL_ADDR_REG(cpu));

	meson_smp_set_cpu_ctrl(cpu, true);

	वापस 0;
पूर्ण

अटल पूर्णांक meson8_smp_boot_secondary(अचिन्हित पूर्णांक cpu,
				     काष्ठा task_काष्ठा *idle)
अणु
	काष्ठा reset_control *rstc;
	पूर्णांक ret;

	rstc = meson_smp_get_core_reset(cpu);
	अगर (IS_ERR(rstc)) अणु
		pr_err("Couldn't get the reset controller for CPU%d\n", cpu);
		वापस PTR_ERR(rstc);
	पूर्ण

	meson_smp_begin_secondary_boot(cpu);

	/* Reset enable */
	ret = reset_control_निश्चित(rstc);
	अगर (ret) अणु
		pr_err("Failed to assert CPU%d reset\n", cpu);
		जाओ out;
	पूर्ण

	/* CPU घातer ON */
	ret = regmap_update_bits(pmu, MESON_CPU_AO_RTI_PWR_A9_CNTL1,
				 MESON_CPU_PWR_A9_CNTL1_M(cpu), 0);
	अगर (ret < 0) अणु
		pr_err("Couldn't wake up CPU%d\n", cpu);
		जाओ out;
	पूर्ण

	udelay(10);

	/* Isolation disable */
	ret = regmap_update_bits(pmu, MESON_CPU_AO_RTI_PWR_A9_CNTL0, BIT(cpu),
				 0);
	अगर (ret < 0) अणु
		pr_err("Error when disabling isolation of CPU%d\n", cpu);
		जाओ out;
	पूर्ण

	/* Reset disable */
	ret = reset_control_deनिश्चित(rstc);
	अगर (ret) अणु
		pr_err("Failed to de-assert CPU%d reset\n", cpu);
		जाओ out;
	पूर्ण

	ret = meson_smp_finalize_secondary_boot(cpu);
	अगर (ret)
		जाओ out;

out:
	reset_control_put(rstc);

	वापस 0;
पूर्ण

अटल पूर्णांक meson8b_smp_boot_secondary(अचिन्हित पूर्णांक cpu,
				     काष्ठा task_काष्ठा *idle)
अणु
	काष्ठा reset_control *rstc;
	पूर्णांक ret;
	u32 val;

	rstc = meson_smp_get_core_reset(cpu);
	अगर (IS_ERR(rstc)) अणु
		pr_err("Couldn't get the reset controller for CPU%d\n", cpu);
		वापस PTR_ERR(rstc);
	पूर्ण

	meson_smp_begin_secondary_boot(cpu);

	/* CPU घातer UP */
	ret = regmap_update_bits(pmu, MESON_CPU_AO_RTI_PWR_A9_CNTL0,
				 MESON_CPU_PWR_A9_CNTL0_M(cpu), 0);
	अगर (ret < 0) अणु
		pr_err("Couldn't power up CPU%d\n", cpu);
		जाओ out;
	पूर्ण

	udelay(5);

	/* Reset enable */
	ret = reset_control_निश्चित(rstc);
	अगर (ret) अणु
		pr_err("Failed to assert CPU%d reset\n", cpu);
		जाओ out;
	पूर्ण

	/* Memory घातer UP */
	ret = regmap_update_bits(pmu, MESON_CPU_AO_RTI_PWR_A9_MEM_PD0,
				 MESON_CPU_PWR_A9_MEM_PD0_M(cpu), 0);
	अगर (ret < 0) अणु
		pr_err("Couldn't power up the memory for CPU%d\n", cpu);
		जाओ out;
	पूर्ण

	/* Wake up CPU */
	ret = regmap_update_bits(pmu, MESON_CPU_AO_RTI_PWR_A9_CNTL1,
				 MESON_CPU_PWR_A9_CNTL1_M(cpu), 0);
	अगर (ret < 0) अणु
		pr_err("Couldn't wake up CPU%d\n", cpu);
		जाओ out;
	पूर्ण

	udelay(10);

	ret = regmap_पढ़ो_poll_समयout(pmu, MESON_CPU_AO_RTI_PWR_A9_CNTL1, val,
				       val & MESON_CPU_PWR_A9_CNTL1_ST(cpu),
				       10, 10000);
	अगर (ret) अणु
		pr_err("Timeout while polling PMU for CPU%d status\n", cpu);
		जाओ out;
	पूर्ण

	/* Isolation disable */
	ret = regmap_update_bits(pmu, MESON_CPU_AO_RTI_PWR_A9_CNTL0, BIT(cpu),
				 0);
	अगर (ret < 0) अणु
		pr_err("Error when disabling isolation of CPU%d\n", cpu);
		जाओ out;
	पूर्ण

	/* Reset disable */
	ret = reset_control_deनिश्चित(rstc);
	अगर (ret) अणु
		pr_err("Failed to de-assert CPU%d reset\n", cpu);
		जाओ out;
	पूर्ण

	ret = meson_smp_finalize_secondary_boot(cpu);
	अगर (ret)
		जाओ out;

out:
	reset_control_put(rstc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम meson8_smp_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	meson_smp_set_cpu_ctrl(cpu, false);

	v7_निकास_coherency_flush(louis);

	scu_घातer_mode(scu_base, SCU_PM_POWEROFF);

	dsb();
	wfi();

	/* we should never get here */
	WARN_ON(1);
पूर्ण

अटल पूर्णांक meson8_smp_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक ret, घातer_mode;
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + (50 * HZ);
	करो अणु
		घातer_mode = scu_get_cpu_घातer_mode(scu_base, cpu);

		अगर (घातer_mode == SCU_PM_POWEROFF)
			अवरोध;

		usleep_range(10000, 15000);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	अगर (घातer_mode != SCU_PM_POWEROFF) अणु
		pr_err("Error while waiting for SCU power-off on CPU%d\n",
		       cpu);
		वापस -ETIMEDOUT;
	पूर्ण

	msleep(30);

	/* Isolation enable */
	ret = regmap_update_bits(pmu, MESON_CPU_AO_RTI_PWR_A9_CNTL0, BIT(cpu),
				 0x3);
	अगर (ret < 0) अणु
		pr_err("Error when enabling isolation for CPU%d\n", cpu);
		वापस ret;
	पूर्ण

	udelay(10);

	/* CPU घातer OFF */
	ret = regmap_update_bits(pmu, MESON_CPU_AO_RTI_PWR_A9_CNTL1,
				 MESON_CPU_PWR_A9_CNTL1_M(cpu), 0x3);
	अगर (ret < 0) अणु
		pr_err("Couldn't change sleep status of CPU%d\n", cpu);
		वापस ret;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक meson8b_smp_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक ret, घातer_mode, count = 5000;

	करो अणु
		घातer_mode = scu_get_cpu_घातer_mode(scu_base, cpu);

		अगर (घातer_mode == SCU_PM_POWEROFF)
			अवरोध;

		udelay(10);
	पूर्ण जबतक (++count);

	अगर (घातer_mode != SCU_PM_POWEROFF) अणु
		pr_err("Error while waiting for SCU power-off on CPU%d\n",
		       cpu);
		वापस -ETIMEDOUT;
	पूर्ण

	udelay(10);

	/* CPU घातer DOWN */
	ret = regmap_update_bits(pmu, MESON_CPU_AO_RTI_PWR_A9_CNTL0,
				 MESON_CPU_PWR_A9_CNTL0_M(cpu), 0x3);
	अगर (ret < 0) अणु
		pr_err("Couldn't power down CPU%d\n", cpu);
		वापस ret;
	पूर्ण

	/* Isolation enable */
	ret = regmap_update_bits(pmu, MESON_CPU_AO_RTI_PWR_A9_CNTL0, BIT(cpu),
				 0x3);
	अगर (ret < 0) अणु
		pr_err("Error when enabling isolation for CPU%d\n", cpu);
		वापस ret;
	पूर्ण

	udelay(10);

	/* Sleep status */
	ret = regmap_update_bits(pmu, MESON_CPU_AO_RTI_PWR_A9_CNTL1,
				 MESON_CPU_PWR_A9_CNTL1_M(cpu), 0x3);
	अगर (ret < 0) अणु
		pr_err("Couldn't change sleep status of CPU%d\n", cpu);
		वापस ret;
	पूर्ण

	/* Memory घातer DOWN */
	ret = regmap_update_bits(pmu, MESON_CPU_AO_RTI_PWR_A9_MEM_PD0,
				 MESON_CPU_PWR_A9_MEM_PD0_M(cpu), 0xf);
	अगर (ret < 0) अणु
		pr_err("Couldn't power down the memory of CPU%d\n", cpu);
		वापस ret;
	पूर्ण

	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा smp_operations meson8_smp_ops __initdata = अणु
	.smp_prepare_cpus	= meson8_smp_prepare_cpus,
	.smp_boot_secondary	= meson8_smp_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= meson8_smp_cpu_die,
	.cpu_समाप्त		= meson8_smp_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा smp_operations meson8b_smp_ops __initdata = अणु
	.smp_prepare_cpus	= meson8b_smp_prepare_cpus,
	.smp_boot_secondary	= meson8b_smp_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= meson8_smp_cpu_die,
	.cpu_समाप्त		= meson8b_smp_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;

CPU_METHOD_OF_DECLARE(meson8_smp, "amlogic,meson8-smp", &meson8_smp_ops);
CPU_METHOD_OF_DECLARE(meson8b_smp, "amlogic,meson8b-smp", &meson8b_smp_ops);
