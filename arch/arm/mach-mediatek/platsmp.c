<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-mediatek/platsmp.c
 *
 * Copyright (c) 2014 Mediatek Inc.
 * Author: Shunli Wang <shunli.wang@mediatek.com>
 *         Yingjoe Chen <yingjoe.chen@mediatek.com>
 */
#समावेश <linux/पन.स>
#समावेश <linux/memblock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/माला.स>
#समावेश <linux/thपढ़ोs.h>

#घोषणा MTK_MAX_CPU		8
#घोषणा MTK_SMP_REG_SIZE	0x1000

काष्ठा mtk_smp_boot_info अणु
	अचिन्हित दीर्घ smp_base;
	अचिन्हित पूर्णांक jump_reg;
	अचिन्हित पूर्णांक core_keys[MTK_MAX_CPU - 1];
	अचिन्हित पूर्णांक core_regs[MTK_MAX_CPU - 1];
पूर्ण;

अटल स्थिर काष्ठा mtk_smp_boot_info mtk_mt8135_tz_boot = अणु
	0x80002000, 0x3fc,
	अणु 0x534c4131, 0x4c415332, 0x41534c33 पूर्ण,
	अणु 0x3f8, 0x3f8, 0x3f8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_smp_boot_info mtk_mt6589_boot = अणु
	0x10002000, 0x34,
	अणु 0x534c4131, 0x4c415332, 0x41534c33 पूर्ण,
	अणु 0x38, 0x3c, 0x40 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_smp_boot_info mtk_mt7623_boot = अणु
	0x10202000, 0x34,
	अणु 0x534c4131, 0x4c415332, 0x41534c33 पूर्ण,
	अणु 0x38, 0x3c, 0x40 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_tz_smp_boot_infos[] __initस्थिर = अणु
	अणु .compatible   = "mediatek,mt8135", .data = &mtk_mt8135_tz_boot पूर्ण,
	अणु .compatible   = "mediatek,mt8127", .data = &mtk_mt8135_tz_boot पूर्ण,
	अणु .compatible   = "mediatek,mt2701", .data = &mtk_mt8135_tz_boot पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_smp_boot_infos[] __initस्थिर = अणु
	अणु .compatible   = "mediatek,mt6589", .data = &mtk_mt6589_boot पूर्ण,
	अणु .compatible   = "mediatek,mt7623", .data = &mtk_mt7623_boot पूर्ण,
	अणु .compatible   = "mediatek,mt7629", .data = &mtk_mt7623_boot पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम __iomem *mtk_smp_base;
अटल स्थिर काष्ठा mtk_smp_boot_info *mtk_smp_info;

अटल पूर्णांक mtk_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अगर (!mtk_smp_base)
		वापस -EINVAL;

	अगर (!mtk_smp_info->core_keys[cpu-1])
		वापस -EINVAL;

	ग_लिखोl_relaxed(mtk_smp_info->core_keys[cpu-1],
		mtk_smp_base + mtk_smp_info->core_regs[cpu-1]);

	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	वापस 0;
पूर्ण

अटल व्योम __init __mtk_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus, पूर्णांक trustzone)
अणु
	पूर्णांक i, num;
	स्थिर काष्ठा of_device_id *infos;

	अगर (trustzone) अणु
		num = ARRAY_SIZE(mtk_tz_smp_boot_infos);
		infos = mtk_tz_smp_boot_infos;
	पूर्ण अन्यथा अणु
		num = ARRAY_SIZE(mtk_smp_boot_infos);
		infos = mtk_smp_boot_infos;
	पूर्ण

	/* Find smp boot info क्रम this SoC */
	क्रम (i = 0; i < num; i++) अणु
		अगर (of_machine_is_compatible(infos[i].compatible)) अणु
			mtk_smp_info = infos[i].data;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!mtk_smp_info) अणु
		pr_err("%s: Device is not supported\n", __func__);
		वापस;
	पूर्ण

	अगर (trustzone) अणु
		/* smp_base(trustzone-bootinfo) is reserved by device tree */
		mtk_smp_base = phys_to_virt(mtk_smp_info->smp_base);
	पूर्ण अन्यथा अणु
		mtk_smp_base = ioremap(mtk_smp_info->smp_base, MTK_SMP_REG_SIZE);
		अगर (!mtk_smp_base) अणु
			pr_err("%s: Can't remap %lx\n", __func__,
				mtk_smp_info->smp_base);
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * ग_लिखो the address of slave startup address पूर्णांकo the प्रणाली-wide
	 * jump रेजिस्टर
	 */
	ग_लिखोl_relaxed(__pa_symbol(secondary_startup_arm),
			mtk_smp_base + mtk_smp_info->jump_reg);
पूर्ण

अटल व्योम __init mtk_tz_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	__mtk_smp_prepare_cpus(max_cpus, 1);
पूर्ण

अटल व्योम __init mtk_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	__mtk_smp_prepare_cpus(max_cpus, 0);
पूर्ण

अटल स्थिर काष्ठा smp_operations mt81xx_tz_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus = mtk_tz_smp_prepare_cpus,
	.smp_boot_secondary = mtk_boot_secondary,
पूर्ण;
CPU_METHOD_OF_DECLARE(mt81xx_tz_smp, "mediatek,mt81xx-tz-smp", &mt81xx_tz_smp_ops);

अटल स्थिर काष्ठा smp_operations mt6589_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus = mtk_smp_prepare_cpus,
	.smp_boot_secondary = mtk_boot_secondary,
पूर्ण;
CPU_METHOD_OF_DECLARE(mt6589_smp, "mediatek,mt6589-smp", &mt6589_smp_ops);
