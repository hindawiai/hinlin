<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/ti.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <dt-bindings/घड़ी/dm814.h>

#समावेश "clock.h"

अटल स्थिर काष्ठा omap_clkctrl_reg_data dm814_शेष_clkctrl_regs[] __initस्थिर = अणु
	अणु DM814_USB_OTG_HS_CLKCTRL, शून्य, CLKF_SW_SUP, "pll260dcoclkldo" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dm814_alwon_clkctrl_regs[] __initस्थिर = अणु
	अणु DM814_UART1_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk10_ck" पूर्ण,
	अणु DM814_UART2_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk10_ck" पूर्ण,
	अणु DM814_UART3_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk10_ck" पूर्ण,
	अणु DM814_GPIO1_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk6_ck" पूर्ण,
	अणु DM814_GPIO2_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk6_ck" पूर्ण,
	अणु DM814_I2C1_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk10_ck" पूर्ण,
	अणु DM814_I2C2_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk10_ck" पूर्ण,
	अणु DM814_WD_TIMER_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_NO_IDLEST, "sysclk18_ck" पूर्ण,
	अणु DM814_MCSPI1_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk10_ck" पूर्ण,
	अणु DM814_GPMC_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk6_ck" पूर्ण,
	अणु DM814_MPU_CLKCTRL, शून्य, CLKF_SW_SUP, "mpu_ck" पूर्ण,
	अणु DM814_RTC_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_NO_IDLEST, "sysclk18_ck" पूर्ण,
	अणु DM814_TPCC_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk4_ck" पूर्ण,
	अणु DM814_TPTC0_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk4_ck" पूर्ण,
	अणु DM814_TPTC1_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk4_ck" पूर्ण,
	अणु DM814_TPTC2_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk4_ck" पूर्ण,
	अणु DM814_TPTC3_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk4_ck" पूर्ण,
	अणु DM814_MMC1_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk8_ck" पूर्ण,
	अणु DM814_MMC2_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk8_ck" पूर्ण,
	अणु DM814_MMC3_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk8_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा
omap_clkctrl_reg_data dm814_alwon_ethernet_clkctrl_regs[] __initस्थिर = अणु
	अणु 0, शून्य, CLKF_SW_SUP, "cpsw_125mhz_gclk" पूर्ण,
पूर्ण;

स्थिर काष्ठा omap_clkctrl_data dm814_clkctrl_data[] __initस्थिर = अणु
	अणु 0x48180500, dm814_शेष_clkctrl_regs पूर्ण,
	अणु 0x48181400, dm814_alwon_clkctrl_regs पूर्ण,
	अणु 0x481815d4, dm814_alwon_ethernet_clkctrl_regs पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा ti_dt_clk dm814_clks[] = अणु
	DT_CLK(शून्य, "timer_sys_ck", "devosc_ck"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

अटल bool समयr_घड़ीs_initialized;

अटल पूर्णांक __init dm814x_adpll_early_init(व्योम)
अणु
	काष्ठा device_node *np;

	अगर (!समयr_घड़ीs_initialized)
		वापस -ENODEV;

	np = of_find_node_by_name(शून्य, "pllss");
	अगर (!np) अणु
		pr_err("Could not find node for plls\n");
		वापस -ENODEV;
	पूर्ण

	of_platक्रमm_populate(np, शून्य, शून्य, शून्य);
	of_node_put(np);

	वापस 0;
पूर्ण
core_initcall(dm814x_adpll_early_init);

अटल स्थिर अक्षर * स्थिर init_घड़ीs[] = अणु
	"pll040clkout",		/* MPU 481c5040.adpll.clkout */
	"pll290clkout",		/* DDR 481c5290.adpll.clkout */
पूर्ण;

अटल पूर्णांक __init dm814x_adpll_enable_init_घड़ीs(व्योम)
अणु
	पूर्णांक i, err;

	अगर (!समयr_घड़ीs_initialized)
		वापस -ENODEV;

	क्रम (i = 0; i < ARRAY_SIZE(init_घड़ीs); i++) अणु
		काष्ठा clk *घड़ी;

		घड़ी = clk_get(शून्य, init_घड़ीs[i]);
		अगर (WARN(IS_ERR(घड़ी), "could not find init clock %s\n",
			 init_घड़ीs[i]))
			जारी;
		err = clk_prepare_enable(घड़ी);
		अगर (WARN(err, "could not enable init clock %s\n",
			 init_घड़ीs[i]))
			जारी;
	पूर्ण

	वापस 0;
पूर्ण
postcore_initcall(dm814x_adpll_enable_init_घड़ीs);

पूर्णांक __init dm814x_dt_clk_init(व्योम)
अणु
	ti_dt_घड़ीs_रेजिस्टर(dm814_clks);
	omap2_clk_disable_स्वतःidle_all();
	ti_clk_add_aliases();
	omap2_clk_enable_init_घड़ीs(शून्य, 0);
	समयr_घड़ीs_initialized = true;

	वापस 0;
पूर्ण
