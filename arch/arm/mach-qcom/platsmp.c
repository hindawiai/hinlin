<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *  Copyright (c) 2010, Code Aurora Forum. All rights reserved.
 *  Copyright (c) 2014 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/qcom_scm.h>

#समावेश <यंत्र/smp_plat.h>


#घोषणा VDD_SC1_ARRAY_CLAMP_GFS_CTL	0x35a0
#घोषणा SCSS_CPU1CORE_RESET		0x2d80
#घोषणा SCSS_DBG_STATUS_CORE_PWRDUP	0x2e64

#घोषणा APCS_CPU_PWR_CTL	0x04
#घोषणा PLL_CLAMP		BIT(8)
#घोषणा CORE_PWRD_UP		BIT(7)
#घोषणा COREPOR_RST		BIT(5)
#घोषणा CORE_RST		BIT(4)
#घोषणा L2DT_SLP		BIT(3)
#घोषणा CLAMP			BIT(0)

#घोषणा APC_PWR_GATE_CTL	0x14
#घोषणा BHS_CNT_SHIFT		24
#घोषणा LDO_PWR_DWN_SHIFT	16
#घोषणा LDO_BYP_SHIFT		8
#घोषणा BHS_SEG_SHIFT		1
#घोषणा BHS_EN			BIT(0)

#घोषणा APCS_SAW2_VCTL		0x14
#घोषणा APCS_SAW2_2_VCTL	0x1c

बाह्य व्योम secondary_startup_arm(व्योम);

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम qcom_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	wfi();
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक scss_release_secondary(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device_node *node;
	व्योम __iomem *base;

	node = of_find_compatible_node(शून्य, शून्य, "qcom,gcc-msm8660");
	अगर (!node) अणु
		pr_err("%s: can't find node\n", __func__);
		वापस -ENXIO;
	पूर्ण

	base = of_iomap(node, 0);
	of_node_put(node);
	अगर (!base)
		वापस -ENOMEM;

	ग_लिखोl_relaxed(0, base + VDD_SC1_ARRAY_CLAMP_GFS_CTL);
	ग_लिखोl_relaxed(0, base + SCSS_CPU1CORE_RESET);
	ग_लिखोl_relaxed(3, base + SCSS_DBG_STATUS_CORE_PWRDUP);
	mb();
	iounmap(base);

	वापस 0;
पूर्ण

अटल पूर्णांक kpssv1_release_secondary(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक ret = 0;
	व्योम __iomem *reg, *saw_reg;
	काष्ठा device_node *cpu_node, *acc_node, *saw_node;
	u32 val;

	cpu_node = of_get_cpu_node(cpu, शून्य);
	अगर (!cpu_node)
		वापस -ENODEV;

	acc_node = of_parse_phandle(cpu_node, "qcom,acc", 0);
	अगर (!acc_node) अणु
		ret = -ENODEV;
		जाओ out_acc;
	पूर्ण

	saw_node = of_parse_phandle(cpu_node, "qcom,saw", 0);
	अगर (!saw_node) अणु
		ret = -ENODEV;
		जाओ out_saw;
	पूर्ण

	reg = of_iomap(acc_node, 0);
	अगर (!reg) अणु
		ret = -ENOMEM;
		जाओ out_acc_map;
	पूर्ण

	saw_reg = of_iomap(saw_node, 0);
	अगर (!saw_reg) अणु
		ret = -ENOMEM;
		जाओ out_saw_map;
	पूर्ण

	/* Turn on CPU rail */
	ग_लिखोl_relaxed(0xA4, saw_reg + APCS_SAW2_VCTL);
	mb();
	udelay(512);

	/* Krait bring-up sequence */
	val = PLL_CLAMP | L2DT_SLP | CLAMP;
	ग_लिखोl_relaxed(val, reg + APCS_CPU_PWR_CTL);
	val &= ~L2DT_SLP;
	ग_लिखोl_relaxed(val, reg + APCS_CPU_PWR_CTL);
	mb();
	ndelay(300);

	val |= COREPOR_RST;
	ग_लिखोl_relaxed(val, reg + APCS_CPU_PWR_CTL);
	mb();
	udelay(2);

	val &= ~CLAMP;
	ग_लिखोl_relaxed(val, reg + APCS_CPU_PWR_CTL);
	mb();
	udelay(2);

	val &= ~COREPOR_RST;
	ग_लिखोl_relaxed(val, reg + APCS_CPU_PWR_CTL);
	mb();
	udelay(100);

	val |= CORE_PWRD_UP;
	ग_लिखोl_relaxed(val, reg + APCS_CPU_PWR_CTL);
	mb();

	iounmap(saw_reg);
out_saw_map:
	iounmap(reg);
out_acc_map:
	of_node_put(saw_node);
out_saw:
	of_node_put(acc_node);
out_acc:
	of_node_put(cpu_node);
	वापस ret;
पूर्ण

अटल पूर्णांक kpssv2_release_secondary(अचिन्हित पूर्णांक cpu)
अणु
	व्योम __iomem *reg;
	काष्ठा device_node *cpu_node, *l2_node, *acc_node, *saw_node;
	व्योम __iomem *l2_saw_base;
	अचिन्हित reg_val;
	पूर्णांक ret;

	cpu_node = of_get_cpu_node(cpu, शून्य);
	अगर (!cpu_node)
		वापस -ENODEV;

	acc_node = of_parse_phandle(cpu_node, "qcom,acc", 0);
	अगर (!acc_node) अणु
		ret = -ENODEV;
		जाओ out_acc;
	पूर्ण

	l2_node = of_parse_phandle(cpu_node, "next-level-cache", 0);
	अगर (!l2_node) अणु
		ret = -ENODEV;
		जाओ out_l2;
	पूर्ण

	saw_node = of_parse_phandle(l2_node, "qcom,saw", 0);
	अगर (!saw_node) अणु
		ret = -ENODEV;
		जाओ out_saw;
	पूर्ण

	reg = of_iomap(acc_node, 0);
	अगर (!reg) अणु
		ret = -ENOMEM;
		जाओ out_map;
	पूर्ण

	l2_saw_base = of_iomap(saw_node, 0);
	अगर (!l2_saw_base) अणु
		ret = -ENOMEM;
		जाओ out_saw_map;
	पूर्ण

	/* Turn on the BHS, turn off LDO Bypass and घातer करोwn LDO */
	reg_val = (64 << BHS_CNT_SHIFT) | (0x3f << LDO_PWR_DWN_SHIFT) | BHS_EN;
	ग_लिखोl_relaxed(reg_val, reg + APC_PWR_GATE_CTL);
	mb();
	/* रुको क्रम the BHS to settle */
	udelay(1);

	/* Turn on BHS segments */
	reg_val |= 0x3f << BHS_SEG_SHIFT;
	ग_लिखोl_relaxed(reg_val, reg + APC_PWR_GATE_CTL);
	mb();
	 /* रुको क्रम the BHS to settle */
	udelay(1);

	/* Finally turn on the bypass so that BHS supplies घातer */
	reg_val |= 0x3f << LDO_BYP_SHIFT;
	ग_लिखोl_relaxed(reg_val, reg + APC_PWR_GATE_CTL);

	/* enable max phases */
	ग_लिखोl_relaxed(0x10003, l2_saw_base + APCS_SAW2_2_VCTL);
	mb();
	udelay(50);

	reg_val = COREPOR_RST | CLAMP;
	ग_लिखोl_relaxed(reg_val, reg + APCS_CPU_PWR_CTL);
	mb();
	udelay(2);

	reg_val &= ~CLAMP;
	ग_लिखोl_relaxed(reg_val, reg + APCS_CPU_PWR_CTL);
	mb();
	udelay(2);

	reg_val &= ~COREPOR_RST;
	ग_लिखोl_relaxed(reg_val, reg + APCS_CPU_PWR_CTL);
	mb();

	reg_val |= CORE_PWRD_UP;
	ग_लिखोl_relaxed(reg_val, reg + APCS_CPU_PWR_CTL);
	mb();

	ret = 0;

	iounmap(l2_saw_base);
out_saw_map:
	iounmap(reg);
out_map:
	of_node_put(saw_node);
out_saw:
	of_node_put(l2_node);
out_l2:
	of_node_put(acc_node);
out_acc:
	of_node_put(cpu_node);

	वापस ret;
पूर्ण

अटल DEFINE_PER_CPU(पूर्णांक, cold_boot_करोne);

अटल पूर्णांक qcom_boot_secondary(अचिन्हित पूर्णांक cpu, पूर्णांक (*func)(अचिन्हित पूर्णांक))
अणु
	पूर्णांक ret = 0;

	अगर (!per_cpu(cold_boot_करोne, cpu)) अणु
		ret = func(cpu);
		अगर (!ret)
			per_cpu(cold_boot_करोne, cpu) = true;
	पूर्ण

	/*
	 * Send the secondary CPU a soft पूर्णांकerrupt, thereby causing
	 * the boot monitor to पढ़ो the प्रणाली wide flags रेजिस्टर,
	 * and branch to the address found there.
	 */
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	वापस ret;
पूर्ण

अटल पूर्णांक msm8660_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	वापस qcom_boot_secondary(cpu, scss_release_secondary);
पूर्ण

अटल पूर्णांक kpssv1_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	वापस qcom_boot_secondary(cpu, kpssv1_release_secondary);
पूर्ण

अटल पूर्णांक kpssv2_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	वापस qcom_boot_secondary(cpu, kpssv2_release_secondary);
पूर्ण

अटल व्योम __init qcom_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	पूर्णांक cpu;

	अगर (qcom_scm_set_cold_boot_addr(secondary_startup_arm,
					cpu_present_mask)) अणु
		क्रम_each_present_cpu(cpu) अणु
			अगर (cpu == smp_processor_id())
				जारी;
			set_cpu_present(cpu, false);
		पूर्ण
		pr_warn("Failed to set CPU boot address, disabling SMP\n");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा smp_operations smp_msm8660_ops __initस्थिर = अणु
	.smp_prepare_cpus	= qcom_smp_prepare_cpus,
	.smp_boot_secondary	= msm8660_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= qcom_cpu_die,
#पूर्ण_अगर
पूर्ण;
CPU_METHOD_OF_DECLARE(qcom_smp, "qcom,gcc-msm8660", &smp_msm8660_ops);

अटल स्थिर काष्ठा smp_operations qcom_smp_kpssv1_ops __initस्थिर = अणु
	.smp_prepare_cpus	= qcom_smp_prepare_cpus,
	.smp_boot_secondary	= kpssv1_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= qcom_cpu_die,
#पूर्ण_अगर
पूर्ण;
CPU_METHOD_OF_DECLARE(qcom_smp_kpssv1, "qcom,kpss-acc-v1", &qcom_smp_kpssv1_ops);

अटल स्थिर काष्ठा smp_operations qcom_smp_kpssv2_ops __initस्थिर = अणु
	.smp_prepare_cpus	= qcom_smp_prepare_cpus,
	.smp_boot_secondary	= kpssv2_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= qcom_cpu_die,
#पूर्ण_अगर
पूर्ण;
CPU_METHOD_OF_DECLARE(qcom_smp_kpssv2, "qcom,kpss-acc-v2", &qcom_smp_kpssv2_ops);
