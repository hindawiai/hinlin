<शैली गुरु>
/*
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/ti.h>
#समावेश <dt-bindings/घड़ी/dm816.h>

#समावेश "clock.h"

अटल स्थिर काष्ठा omap_clkctrl_reg_data dm816_शेष_clkctrl_regs[] __initस्थिर = अणु
	अणु DM816_USB_OTG_HS_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk6_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dm816_alwon_clkctrl_regs[] __initस्थिर = अणु
	अणु DM816_UART1_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk10_ck" पूर्ण,
	अणु DM816_UART2_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk10_ck" पूर्ण,
	अणु DM816_UART3_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk10_ck" पूर्ण,
	अणु DM816_GPIO1_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk6_ck" पूर्ण,
	अणु DM816_GPIO2_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk6_ck" पूर्ण,
	अणु DM816_I2C1_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk10_ck" पूर्ण,
	अणु DM816_I2C2_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk10_ck" पूर्ण,
	अणु DM816_TIMER1_CLKCTRL, शून्य, CLKF_SW_SUP, "timer1_fck" पूर्ण,
	अणु DM816_TIMER2_CLKCTRL, शून्य, CLKF_SW_SUP, "timer2_fck" पूर्ण,
	अणु DM816_TIMER3_CLKCTRL, शून्य, CLKF_SW_SUP, "timer3_fck" पूर्ण,
	अणु DM816_TIMER4_CLKCTRL, शून्य, CLKF_SW_SUP, "timer4_fck" पूर्ण,
	अणु DM816_TIMER5_CLKCTRL, शून्य, CLKF_SW_SUP, "timer5_fck" पूर्ण,
	अणु DM816_TIMER6_CLKCTRL, शून्य, CLKF_SW_SUP, "timer6_fck" पूर्ण,
	अणु DM816_TIMER7_CLKCTRL, शून्य, CLKF_SW_SUP, "timer7_fck" पूर्ण,
	अणु DM816_WD_TIMER_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_NO_IDLEST, "sysclk18_ck" पूर्ण,
	अणु DM816_MCSPI1_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk10_ck" पूर्ण,
	अणु DM816_MAILBOX_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk6_ck" पूर्ण,
	अणु DM816_SPINBOX_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk6_ck" पूर्ण,
	अणु DM816_MMC1_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk10_ck" पूर्ण,
	अणु DM816_GPMC_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk6_ck" पूर्ण,
	अणु DM816_DAVINCI_MDIO_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_NO_IDLEST, "sysclk24_ck" पूर्ण,
	अणु DM816_EMAC1_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_NO_IDLEST, "sysclk24_ck" पूर्ण,
	अणु DM816_MPU_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk2_ck" पूर्ण,
	अणु DM816_RTC_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_NO_IDLEST, "sysclk18_ck" पूर्ण,
	अणु DM816_TPCC_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk4_ck" पूर्ण,
	अणु DM816_TPTC0_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk4_ck" पूर्ण,
	अणु DM816_TPTC1_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk4_ck" पूर्ण,
	अणु DM816_TPTC2_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk4_ck" पूर्ण,
	अणु DM816_TPTC3_CLKCTRL, शून्य, CLKF_SW_SUP, "sysclk4_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

स्थिर काष्ठा omap_clkctrl_data dm816_clkctrl_data[] __initस्थिर = अणु
	अणु 0x48180500, dm816_शेष_clkctrl_regs पूर्ण,
	अणु 0x48181400, dm816_alwon_clkctrl_regs पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा ti_dt_clk dm816x_clks[] = अणु
	DT_CLK(शून्य, "sys_clkin", "sys_clkin_ck"),
	DT_CLK(शून्य, "timer_sys_ck", "sys_clkin_ck"),
	DT_CLK(शून्य, "timer_32k_ck", "sysclk18_ck"),
	DT_CLK(शून्य, "timer_ext_ck", "tclkin_ck"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *enable_init_clks[] = अणु
	"ddr_pll_clk1",
	"ddr_pll_clk2",
	"ddr_pll_clk3",
	"sysclk6_ck",
पूर्ण;

पूर्णांक __init dm816x_dt_clk_init(व्योम)
अणु
	ti_dt_घड़ीs_रेजिस्टर(dm816x_clks);
	omap2_clk_disable_स्वतःidle_all();
	ti_clk_add_aliases();
	omap2_clk_enable_init_घड़ीs(enable_init_clks,
				     ARRAY_SIZE(enable_init_clks));

	वापस 0;
पूर्ण
