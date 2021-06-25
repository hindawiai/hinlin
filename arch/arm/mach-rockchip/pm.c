<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, Fuzhou Rockchip Electronics Co., Ltd
 * Author: Tony Xie <tony.xie@rock-chips.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>
#समावेश <linux/suspend.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regulator/machine.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/suspend.h>

#समावेश "pm.h"

/* These क्रमागत are option of low घातer mode */
क्रमागत अणु
	ROCKCHIP_ARM_OFF_LOGIC_NORMAL = 0,
	ROCKCHIP_ARM_OFF_LOGIC_DEEP = 1,
पूर्ण;

काष्ठा rockchip_pm_data अणु
	स्थिर काष्ठा platक्रमm_suspend_ops *ops;
	पूर्णांक (*init)(काष्ठा device_node *np);
पूर्ण;

अटल व्योम __iomem *rk3288_bootram_base;
अटल phys_addr_t rk3288_bootram_phy;

अटल काष्ठा regmap *pmu_regmap;
अटल काष्ठा regmap *sgrf_regmap;
अटल काष्ठा regmap *grf_regmap;

अटल u32 rk3288_pmu_pwr_mode_con;
अटल u32 rk3288_sgrf_soc_con0;
अटल u32 rk3288_sgrf_cpu_con0;

अटल अंतरभूत u32 rk3288_l2_config(व्योम)
अणु
	u32 l2ctlr;

	यंत्र("mrc p15, 1, %0, c9, c0, 2" : "=r" (l2ctlr));
	वापस l2ctlr;
पूर्ण

अटल व्योम __init rk3288_config_bootdata(व्योम)
अणु
	rkpm_bootdata_cpusp = rk3288_bootram_phy + (SZ_4K - 8);
	rkpm_bootdata_cpu_code = __pa_symbol(cpu_resume);

	rkpm_bootdata_l2ctlr_f  = 1;
	rkpm_bootdata_l2ctlr = rk3288_l2_config();
पूर्ण

#घोषणा GRF_UOC0_CON0			0x320
#घोषणा GRF_UOC1_CON0			0x334
#घोषणा GRF_UOC2_CON0			0x348
#घोषणा GRF_SIDDQ			BIT(13)

अटल bool rk3288_slp_disable_osc(व्योम)
अणु
	अटल स्थिर u32 reg_offset[] = अणु GRF_UOC0_CON0, GRF_UOC1_CON0,
					  GRF_UOC2_CON0 पूर्ण;
	u32 reg, i;

	/*
	 * अगर any usb phy is still on(GRF_SIDDQ==0), that means we need the
	 * function of usb wakeup, so करो not चयन to 32khz, since the usb phy
	 * clk करोes not connect to 32khz osc
	 */
	क्रम (i = 0; i < ARRAY_SIZE(reg_offset); i++) अणु
		regmap_पढ़ो(grf_regmap, reg_offset[i], &reg);
		अगर (!(reg & GRF_SIDDQ))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम rk3288_slp_mode_set(पूर्णांक level)
अणु
	u32 mode_set, mode_set1;
	bool osc_disable = rk3288_slp_disable_osc();

	regmap_पढ़ो(sgrf_regmap, RK3288_SGRF_CPU_CON0, &rk3288_sgrf_cpu_con0);
	regmap_पढ़ो(sgrf_regmap, RK3288_SGRF_SOC_CON0, &rk3288_sgrf_soc_con0);

	regmap_पढ़ो(pmu_regmap, RK3288_PMU_PWRMODE_CON,
		    &rk3288_pmu_pwr_mode_con);

	/*
	 * SGRF_FAST_BOOT_EN - प्रणाली to boot from FAST_BOOT_ADDR
	 * PCLK_WDT_GATE - disable WDT during suspend.
	 */
	regmap_ग_लिखो(sgrf_regmap, RK3288_SGRF_SOC_CON0,
		     SGRF_PCLK_WDT_GATE | SGRF_FAST_BOOT_EN
		     | SGRF_PCLK_WDT_GATE_WRITE | SGRF_FAST_BOOT_EN_WRITE);

	/*
	 * The dapswjdp can not स्वतः reset beक्रमe resume, that cause it may
	 * access some illegal address during resume. Let's disable it beक्रमe
	 * suspend, and the MASKROM will enable it back.
	 */
	regmap_ग_लिखो(sgrf_regmap, RK3288_SGRF_CPU_CON0, SGRF_DAPDEVICEEN_WRITE);

	/* booting address of resuming प्रणाली is from this रेजिस्टर value */
	regmap_ग_लिखो(sgrf_regmap, RK3288_SGRF_FAST_BOOT_ADDR,
		     rk3288_bootram_phy);

	mode_set = BIT(PMU_GLOBAL_INT_DISABLE) | BIT(PMU_L2FLUSH_EN) |
		   BIT(PMU_SREF0_ENTER_EN) | BIT(PMU_SREF1_ENTER_EN) |
		   BIT(PMU_DDR0_GATING_EN) | BIT(PMU_DDR1_GATING_EN) |
		   BIT(PMU_PWR_MODE_EN) | BIT(PMU_CHIP_PD_EN) |
		   BIT(PMU_SCU_EN);

	mode_set1 = BIT(PMU_CLR_CORE) | BIT(PMU_CLR_CPUP);

	अगर (level == ROCKCHIP_ARM_OFF_LOGIC_DEEP) अणु
		/* arm off, logic deep sleep */
		mode_set |= BIT(PMU_BUS_PD_EN) | BIT(PMU_PMU_USE_LF) |
			    BIT(PMU_DDR1IO_RET_EN) | BIT(PMU_DDR0IO_RET_EN) |
			    BIT(PMU_ALIVE_USE_LF) | BIT(PMU_PLL_PD_EN);

		अगर (osc_disable)
			mode_set |= BIT(PMU_OSC_24M_DIS);

		mode_set1 |= BIT(PMU_CLR_ALIVE) | BIT(PMU_CLR_BUS) |
			     BIT(PMU_CLR_PERI) | BIT(PMU_CLR_DMA);

		regmap_ग_लिखो(pmu_regmap, RK3288_PMU_WAKEUP_CFG1,
			     PMU_ARMINT_WAKEUP_EN);

		/*
		 * In deep suspend we use PMU_PMU_USE_LF to let the rk3288
		 * चयन its मुख्य घड़ी supply to the alternative 32kHz
		 * source. Thereक्रमe set 30ms on a 32kHz घड़ी क्रम pmic
		 * stabilization. Similar 30ms on 24MHz क्रम the other
		 * mode below.
		 */
		regmap_ग_लिखो(pmu_regmap, RK3288_PMU_STABL_CNT, 32 * 30);

		/* only रुको क्रम stabilization, अगर we turned the osc off */
		regmap_ग_लिखो(pmu_regmap, RK3288_PMU_OSC_CNT,
					 osc_disable ? 32 * 30 : 0);
	पूर्ण अन्यथा अणु
		/*
		 * arm off, logic normal
		 * अगर pmu_clk_core_src_gate_en is not set,
		 * wakeup will be error
		 */
		mode_set |= BIT(PMU_CLK_CORE_SRC_GATE_EN);

		regmap_ग_लिखो(pmu_regmap, RK3288_PMU_WAKEUP_CFG1,
			     PMU_ARMINT_WAKEUP_EN | PMU_GPIOINT_WAKEUP_EN);

		/* 30ms on a 24MHz घड़ी क्रम pmic stabilization */
		regmap_ग_लिखो(pmu_regmap, RK3288_PMU_STABL_CNT, 24000 * 30);

		/* oscillator is still running, so no need to रुको */
		regmap_ग_लिखो(pmu_regmap, RK3288_PMU_OSC_CNT, 0);
	पूर्ण

	regmap_ग_लिखो(pmu_regmap, RK3288_PMU_PWRMODE_CON, mode_set);
	regmap_ग_लिखो(pmu_regmap, RK3288_PMU_PWRMODE_CON1, mode_set1);
पूर्ण

अटल व्योम rk3288_slp_mode_set_resume(व्योम)
अणु
	regmap_ग_लिखो(sgrf_regmap, RK3288_SGRF_CPU_CON0,
		     rk3288_sgrf_cpu_con0 | SGRF_DAPDEVICEEN_WRITE);

	regmap_ग_लिखो(pmu_regmap, RK3288_PMU_PWRMODE_CON,
		     rk3288_pmu_pwr_mode_con);

	regmap_ग_लिखो(sgrf_regmap, RK3288_SGRF_SOC_CON0,
		     rk3288_sgrf_soc_con0 | SGRF_PCLK_WDT_GATE_WRITE
		     | SGRF_FAST_BOOT_EN_WRITE);
पूर्ण

अटल पूर्णांक rockchip_lpmode_enter(अचिन्हित दीर्घ arg)
अणु
	flush_cache_all();

	cpu_करो_idle();

	pr_err("%s: Failed to suspend\n", __func__);

	वापस 1;
पूर्ण

अटल पूर्णांक rk3288_suspend_enter(suspend_state_t state)
अणु
	local_fiq_disable();

	rk3288_slp_mode_set(ROCKCHIP_ARM_OFF_LOGIC_NORMAL);

	cpu_suspend(0, rockchip_lpmode_enter);

	rk3288_slp_mode_set_resume();

	local_fiq_enable();

	वापस 0;
पूर्ण

अटल पूर्णांक rk3288_suspend_prepare(व्योम)
अणु
	वापस regulator_suspend_prepare(PM_SUSPEND_MEM);
पूर्ण

अटल व्योम rk3288_suspend_finish(व्योम)
अणु
	अगर (regulator_suspend_finish())
		pr_err("%s: Suspend finish failed\n", __func__);
पूर्ण

अटल पूर्णांक __init rk3288_suspend_init(काष्ठा device_node *np)
अणु
	काष्ठा device_node *sram_np;
	काष्ठा resource res;
	पूर्णांक ret;

	pmu_regmap = syscon_node_to_regmap(np);
	अगर (IS_ERR(pmu_regmap)) अणु
		pr_err("%s: could not find pmu regmap\n", __func__);
		वापस PTR_ERR(pmu_regmap);
	पूर्ण

	sgrf_regmap = syscon_regmap_lookup_by_compatible(
				"rockchip,rk3288-sgrf");
	अगर (IS_ERR(sgrf_regmap)) अणु
		pr_err("%s: could not find sgrf regmap\n", __func__);
		वापस PTR_ERR(sgrf_regmap);
	पूर्ण

	grf_regmap = syscon_regmap_lookup_by_compatible(
				"rockchip,rk3288-grf");
	अगर (IS_ERR(grf_regmap)) अणु
		pr_err("%s: could not find grf regmap\n", __func__);
		वापस PTR_ERR(grf_regmap);
	पूर्ण

	sram_np = of_find_compatible_node(शून्य, शून्य,
					  "rockchip,rk3288-pmu-sram");
	अगर (!sram_np) अणु
		pr_err("%s: could not find bootram dt node\n", __func__);
		वापस -ENODEV;
	पूर्ण

	rk3288_bootram_base = of_iomap(sram_np, 0);
	अगर (!rk3288_bootram_base) अणु
		pr_err("%s: could not map bootram base\n", __func__);
		of_node_put(sram_np);
		वापस -ENOMEM;
	पूर्ण

	ret = of_address_to_resource(sram_np, 0, &res);
	अगर (ret) अणु
		pr_err("%s: could not get bootram phy addr\n", __func__);
		of_node_put(sram_np);
		वापस ret;
	पूर्ण
	rk3288_bootram_phy = res.start;

	of_node_put(sram_np);

	rk3288_config_bootdata();

	/* copy resume code and data to bootsram */
	स_नकल(rk3288_bootram_base, rockchip_slp_cpu_resume,
	       rk3288_bootram_sz);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops rk3288_suspend_ops = अणु
	.enter   = rk3288_suspend_enter,
	.valid   = suspend_valid_only_mem,
	.prepare = rk3288_suspend_prepare,
	.finish  = rk3288_suspend_finish,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pm_data rk3288_pm_data __initस्थिर = अणु
	.ops = &rk3288_suspend_ops,
	.init = rk3288_suspend_init,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_pmu_of_device_ids[] __initस्थिर = अणु
	अणु
		.compatible = "rockchip,rk3288-pmu",
		.data = &rk3288_pm_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

व्योम __init rockchip_suspend_init(व्योम)
अणु
	स्थिर काष्ठा rockchip_pm_data *pm_data;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np;
	पूर्णांक ret;

	np = of_find_matching_node_and_match(शून्य, rockchip_pmu_of_device_ids,
					     &match);
	अगर (!match) अणु
		pr_err("Failed to find PMU node\n");
		वापस;
	पूर्ण
	pm_data = (काष्ठा rockchip_pm_data *) match->data;

	अगर (pm_data->init) अणु
		ret = pm_data->init(np);

		अगर (ret) अणु
			pr_err("%s: matches init error %d\n", __func__, ret);
			वापस;
		पूर्ण
	पूर्ण

	suspend_set_ops(pm_data->ops);
पूर्ण
