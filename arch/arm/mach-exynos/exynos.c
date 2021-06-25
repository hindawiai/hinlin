<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Samsung Exynos Flattened Device Tree enabled machine
//
// Copyright (c) 2010-2014 Samsung Electronics Co., Ltd.
//		http://www.samsung.com

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/soc/samsung/exynos-regs-pmu.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "common.h"

#घोषणा S3C_ADDR_BASE	0xF6000000
#घोषणा S3C_ADDR(x)	((व्योम __iomem __क्रमce *)S3C_ADDR_BASE + (x))
#घोषणा S5P_VA_CHIPID	S3C_ADDR(0x02000000)

अटल काष्ठा platक्रमm_device exynos_cpuidle = अणु
	.name              = "exynos_cpuidle",
#अगर_घोषित CONFIG_ARM_EXYNOS_CPUIDLE
	.dev.platक्रमm_data = exynos_enter_aftr,
#पूर्ण_अगर
	.id                = -1,
पूर्ण;

व्योम __iomem *sysram_base_addr __ro_after_init;
phys_addr_t sysram_base_phys __ro_after_init;
व्योम __iomem *sysram_ns_base_addr __ro_after_init;

अचिन्हित दीर्घ exynos_cpu_id;
अटल अचिन्हित पूर्णांक exynos_cpu_rev;

अचिन्हित पूर्णांक exynos_rev(व्योम)
अणु
	वापस exynos_cpu_rev;
पूर्ण

व्योम __init exynos_sysram_init(व्योम)
अणु
	काष्ठा device_node *node;

	क्रम_each_compatible_node(node, शून्य, "samsung,exynos4210-sysram") अणु
		अगर (!of_device_is_available(node))
			जारी;
		sysram_base_addr = of_iomap(node, 0);
		sysram_base_phys = of_translate_address(node,
					   of_get_address(node, 0, शून्य, शून्य));
		अवरोध;
	पूर्ण

	क्रम_each_compatible_node(node, शून्य, "samsung,exynos4210-sysram-ns") अणु
		अगर (!of_device_is_available(node))
			जारी;
		sysram_ns_base_addr = of_iomap(node, 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __init exynos_fdt_map_chipid(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
					पूर्णांक depth, व्योम *data)
अणु
	काष्ठा map_desc iodesc;
	स्थिर __be32 *reg;
	पूर्णांक len;

	अगर (!of_flat_dt_is_compatible(node, "samsung,exynos4210-chipid"))
		वापस 0;

	reg = of_get_flat_dt_prop(node, "reg", &len);
	अगर (reg == शून्य || len != (माप(अचिन्हित दीर्घ) * 2))
		वापस 0;

	iodesc.pfn = __phys_to_pfn(be32_to_cpu(reg[0]));
	iodesc.length = be32_to_cpu(reg[1]) - 1;
	iodesc.भव = (अचिन्हित दीर्घ)S5P_VA_CHIPID;
	iodesc.type = MT_DEVICE;
	iotable_init(&iodesc, 1);
	वापस 1;
पूर्ण

अटल व्योम __init exynos_init_io(व्योम)
अणु
	debug_ll_io_init();

	of_scan_flat_dt(exynos_fdt_map_chipid, शून्य);

	/* detect cpu id and rev. */
	exynos_cpu_id = पढ़ोl_relaxed(S5P_VA_CHIPID);
	exynos_cpu_rev = exynos_cpu_id & 0xFF;

	pr_info("Samsung CPU ID: 0x%08lx\n", exynos_cpu_id);

पूर्ण

/*
 * Set or clear the USE_DELAYED_RESET_ASSERTION option. Used by smp code
 * and suspend.
 *
 * This is necessary only on Exynos4 SoCs. When प्रणाली is running
 * USE_DELAYED_RESET_ASSERTION should be set so the ARM CLK घड़ी करोwn
 * feature could properly detect global idle state when secondary CPU is
 * घातered करोwn.
 *
 * However this should not be set when such प्रणाली is going पूर्णांकo suspend.
 */
व्योम exynos_set_delayed_reset_निश्चितion(bool enable)
अणु
	अगर (of_machine_is_compatible("samsung,exynos4")) अणु
		अचिन्हित पूर्णांक पंचांगp, core_id;

		क्रम (core_id = 0; core_id < num_possible_cpus(); core_id++) अणु
			पंचांगp = pmu_raw_पढ़ोl(EXYNOS_ARM_CORE_OPTION(core_id));
			अगर (enable)
				पंचांगp |= S5P_USE_DELAYED_RESET_ASSERTION;
			अन्यथा
				पंचांगp &= ~(S5P_USE_DELAYED_RESET_ASSERTION);
			pmu_raw_ग_लिखोl(पंचांगp, EXYNOS_ARM_CORE_OPTION(core_id));
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Apparently, these SoCs are not able to wake-up from suspend using
 * the PMU. Too bad. Should they suddenly become capable of such a
 * feat, the matches below should be moved to suspend.c.
 */
अटल स्थिर काष्ठा of_device_id exynos_dt_pmu_match[] = अणु
	अणु .compatible = "samsung,exynos5260-pmu" पूर्ण,
	अणु .compatible = "samsung,exynos5410-pmu" पूर्ण,
	अणु /*sentinel*/ पूर्ण,
पूर्ण;

अटल व्योम exynos_map_pmu(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_matching_node(शून्य, exynos_dt_pmu_match);
	अगर (np)
		pmu_base_addr = of_iomap(np, 0);
पूर्ण

अटल व्योम __init exynos_init_irq(व्योम)
अणु
	irqchip_init();
	/*
	 * Since platsmp.c needs pmu base address by the समय
	 * DT is not unflatten so we can't use DT APIs beक्रमe
	 * init_irq
	 */
	exynos_map_pmu();
पूर्ण

अटल व्योम __init exynos_dt_machine_init(व्योम)
अणु
	/*
	 * This is called from smp_prepare_cpus अगर we've built क्रम SMP, but
	 * we still need to set it up क्रम PM and firmware ops अगर not.
	 */
	अगर (!IS_ENABLED(CONFIG_SMP))
		exynos_sysram_init();

#अगर defined(CONFIG_SMP) && defined(CONFIG_ARM_EXYNOS_CPUIDLE)
	अगर (of_machine_is_compatible("samsung,exynos4210") ||
	    of_machine_is_compatible("samsung,exynos3250"))
		exynos_cpuidle.dev.platक्रमm_data = &cpuidle_coupled_exynos_data;
#पूर्ण_अगर
	अगर (of_machine_is_compatible("samsung,exynos4210") ||
	    (of_machine_is_compatible("samsung,exynos4412") &&
	     (of_machine_is_compatible("samsung,trats2") ||
		  of_machine_is_compatible("samsung,midas") ||
		  of_machine_is_compatible("samsung,p4note"))) ||
	    of_machine_is_compatible("samsung,exynos3250") ||
	    of_machine_is_compatible("samsung,exynos5250"))
		platक्रमm_device_रेजिस्टर(&exynos_cpuidle);
पूर्ण

अटल अक्षर स्थिर *स्थिर exynos_dt_compat[] __initस्थिर = अणु
	"samsung,exynos3",
	"samsung,exynos3250",
	"samsung,exynos4",
	"samsung,exynos4210",
	"samsung,exynos4412",
	"samsung,exynos5",
	"samsung,exynos5250",
	"samsung,exynos5260",
	"samsung,exynos5420",
	शून्य
पूर्ण;

अटल व्योम __init exynos_dt_fixup(व्योम)
अणु
	/*
	 * Some versions of uboot pass garbage entries in the memory node,
	 * use the old CONFIG_ARM_NR_BANKS
	 */
	of_fdt_limit_memory(8);
पूर्ण

DT_MACHINE_START(EXYNOS_DT, "Samsung Exynos (Flattened Device Tree)")
	.l2c_aux_val	= 0x08400000,
	.l2c_aux_mask	= 0xf60fffff,
	.smp		= smp_ops(exynos_smp_ops),
	.map_io		= exynos_init_io,
	.init_early	= exynos_firmware_init,
	.init_irq	= exynos_init_irq,
	.init_machine	= exynos_dt_machine_init,
	.init_late	= exynos_pm_init,
	.dt_compat	= exynos_dt_compat,
	.dt_fixup	= exynos_dt_fixup,
MACHINE_END
