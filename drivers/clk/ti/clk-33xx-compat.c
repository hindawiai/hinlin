<शैली गुरु>
/*
 * AM33XX Clock init
 *
 * Copyright (C) 2013 Texas Instruments, Inc
 *     Tero Kristo (t-kristo@ti.com)
 *
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
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/ti.h>
#समावेश <dt-bindings/घड़ी/am3.h>

#समावेश "clock.h"

अटल स्थिर अक्षर * स्थिर am3_gpio1_dbclk_parents[] __initस्थिर = अणु
	"l4_per_cm:clk:0138:0",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am3_gpio2_bit_data[] __initस्थिर = अणु
	अणु 18, TI_CLK_GATE, am3_gpio1_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am3_gpio3_bit_data[] __initस्थिर = अणु
	अणु 18, TI_CLK_GATE, am3_gpio1_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am3_gpio4_bit_data[] __initस्थिर = अणु
	अणु 18, TI_CLK_GATE, am3_gpio1_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_l4_per_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_CPGMAC0_CLKCTRL, शून्य, CLKF_SW_SUP, "cpsw_125mhz_gclk", "cpsw_125mhz_clkdm" पूर्ण,
	अणु AM3_LCDC_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_SET_RATE_PARENT, "lcd_gclk", "lcdc_clkdm" पूर्ण,
	अणु AM3_USB_OTG_HS_CLKCTRL, शून्य, CLKF_SW_SUP, "usbotg_fck", "l3s_clkdm" पूर्ण,
	अणु AM3_TPTC0_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM3_EMIF_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_ddr_m2_div2_ck", "l3_clkdm" पूर्ण,
	अणु AM3_OCMCRAM_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM3_GPMC_CLKCTRL, शून्य, CLKF_SW_SUP, "l3s_gclk", "l3s_clkdm" पूर्ण,
	अणु AM3_MCASP0_CLKCTRL, शून्य, CLKF_SW_SUP, "mcasp0_fck", "l3s_clkdm" पूर्ण,
	अणु AM3_UART6_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_MMC1_CLKCTRL, शून्य, CLKF_SW_SUP, "mmc_clk" पूर्ण,
	अणु AM3_ELM_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_I2C3_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_I2C2_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_SPI0_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_SPI1_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_L4_LS_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_MCASP1_CLKCTRL, शून्य, CLKF_SW_SUP, "mcasp1_fck", "l3s_clkdm" पूर्ण,
	अणु AM3_UART2_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_UART3_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_UART4_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_UART5_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_TIMER7_CLKCTRL, शून्य, CLKF_SW_SUP, "timer7_fck" पूर्ण,
	अणु AM3_TIMER2_CLKCTRL, शून्य, CLKF_SW_SUP, "timer2_fck" पूर्ण,
	अणु AM3_TIMER3_CLKCTRL, शून्य, CLKF_SW_SUP, "timer3_fck" पूर्ण,
	अणु AM3_TIMER4_CLKCTRL, शून्य, CLKF_SW_SUP, "timer4_fck" पूर्ण,
	अणु AM3_RNG_CLKCTRL, शून्य, CLKF_SW_SUP, "rng_fck" पूर्ण,
	अणु AM3_AES_CLKCTRL, शून्य, CLKF_SW_SUP, "aes0_fck", "l3_clkdm" पूर्ण,
	अणु AM3_SHAM_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM3_GPIO2_CLKCTRL, am3_gpio2_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_GPIO3_CLKCTRL, am3_gpio3_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_GPIO4_CLKCTRL, am3_gpio4_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_TPCC_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM3_D_CAN0_CLKCTRL, शून्य, CLKF_SW_SUP, "dcan0_fck" पूर्ण,
	अणु AM3_D_CAN1_CLKCTRL, शून्य, CLKF_SW_SUP, "dcan1_fck" पूर्ण,
	अणु AM3_EPWMSS1_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_EPWMSS0_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_EPWMSS2_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_L3_INSTR_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM3_L3_MAIN_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM3_PRUSS_CLKCTRL, शून्य, CLKF_SW_SUP, "pruss_ocp_gclk", "pruss_ocp_clkdm" पूर्ण,
	अणु AM3_TIMER5_CLKCTRL, शून्य, CLKF_SW_SUP, "timer5_fck" पूर्ण,
	अणु AM3_TIMER6_CLKCTRL, शून्य, CLKF_SW_SUP, "timer6_fck" पूर्ण,
	अणु AM3_MMC2_CLKCTRL, शून्य, CLKF_SW_SUP, "mmc_clk" पूर्ण,
	अणु AM3_MMC3_CLKCTRL, शून्य, CLKF_SW_SUP, "mmc_clk", "l3s_clkdm" पूर्ण,
	अणु AM3_TPTC1_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM3_TPTC2_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM3_SPINLOCK_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_MAILBOX_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_L4_HS_CLKCTRL, शून्य, CLKF_SW_SUP, "l4hs_gclk", "l4hs_clkdm" पूर्ण,
	अणु AM3_OCPWP_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_CLKDIV32K_CLKCTRL, शून्य, CLKF_SW_SUP, "clkdiv32k_ck", "clk_24mhz_clkdm" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर am3_gpio0_dbclk_parents[] __initस्थिर = अणु
	"gpio0_dbclk_mux_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am3_gpio1_bit_data[] __initस्थिर = अणु
	अणु 18, TI_CLK_GATE, am3_gpio0_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर am3_dbg_sysclk_ck_parents[] __initस्थिर = अणु
	"sys_clkin_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर am3_trace_pmd_clk_mux_ck_parents[] __initस्थिर = अणु
	"l4_wkup_cm:clk:0010:19",
	"l4_wkup_cm:clk:0010:30",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर am3_trace_clk_भाग_ck_parents[] __initस्थिर = अणु
	"l4_wkup_cm:clk:0010:20",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data am3_trace_clk_भाग_ck_data __initस्थिर = अणु
	.max_भाग = 64,
	.flags = CLK_DIVIDER_POWER_OF_TWO,
पूर्ण;

अटल स्थिर अक्षर * स्थिर am3_sपंचांग_clk_भाग_ck_parents[] __initस्थिर = अणु
	"l4_wkup_cm:clk:0010:22",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data am3_sपंचांग_clk_भाग_ck_data __initस्थिर = अणु
	.max_भाग = 64,
	.flags = CLK_DIVIDER_POWER_OF_TWO,
पूर्ण;

अटल स्थिर अक्षर * स्थिर am3_dbg_clka_ck_parents[] __initस्थिर = अणु
	"dpll_core_m4_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am3_debugss_bit_data[] __initस्थिर = अणु
	अणु 19, TI_CLK_GATE, am3_dbg_sysclk_ck_parents, शून्य पूर्ण,
	अणु 20, TI_CLK_MUX, am3_trace_pmd_clk_mux_ck_parents, शून्य पूर्ण,
	अणु 22, TI_CLK_MUX, am3_trace_pmd_clk_mux_ck_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_DIVIDER, am3_trace_clk_भाग_ck_parents, &am3_trace_clk_भाग_ck_data पूर्ण,
	अणु 27, TI_CLK_DIVIDER, am3_sपंचांग_clk_भाग_ck_parents, &am3_sपंचांग_clk_भाग_ck_data पूर्ण,
	अणु 30, TI_CLK_GATE, am3_dbg_clka_ck_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_l4_wkup_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_CONTROL_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_core_m4_div2_ck" पूर्ण,
	अणु AM3_GPIO1_CLKCTRL, am3_gpio1_bit_data, CLKF_SW_SUP, "dpll_core_m4_div2_ck" पूर्ण,
	अणु AM3_L4_WKUP_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_core_m4_div2_ck" पूर्ण,
	अणु AM3_DEBUGSS_CLKCTRL, am3_debugss_bit_data, CLKF_SW_SUP, "l4_wkup_cm:clk:0010:24", "l3_aon_clkdm" पूर्ण,
	अणु AM3_WKUP_M3_CLKCTRL, शून्य, CLKF_NO_IDLEST, "dpll_core_m4_div2_ck", "l4_wkup_aon_clkdm" पूर्ण,
	अणु AM3_UART1_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_wkupdm_ck" पूर्ण,
	अणु AM3_I2C1_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_wkupdm_ck" पूर्ण,
	अणु AM3_ADC_TSC_CLKCTRL, शून्य, CLKF_SW_SUP, "adc_tsc_fck" पूर्ण,
	अणु AM3_SMARTREFLEX0_CLKCTRL, शून्य, CLKF_SW_SUP, "smartreflex0_fck" पूर्ण,
	अणु AM3_TIMER1_CLKCTRL, शून्य, CLKF_SW_SUP, "timer1_fck" पूर्ण,
	अणु AM3_SMARTREFLEX1_CLKCTRL, शून्य, CLKF_SW_SUP, "smartreflex1_fck" पूर्ण,
	अणु AM3_WD_TIMER2_CLKCTRL, शून्य, CLKF_SW_SUP, "wdt1_fck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_mpu_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_MPU_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_mpu_m2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_l4_rtc_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_RTC_CLKCTRL, शून्य, CLKF_SW_SUP, "clk_32768_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_gfx_l3_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_GFX_CLKCTRL, शून्य, CLKF_SW_SUP, "gfx_fck_div_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_l4_cefuse_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_CEFUSE_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_clkin_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

स्थिर काष्ठा omap_clkctrl_data am3_clkctrl_compat_data[] __initस्थिर = अणु
	अणु 0x44e00014, am3_l4_per_clkctrl_regs पूर्ण,
	अणु 0x44e00404, am3_l4_wkup_clkctrl_regs पूर्ण,
	अणु 0x44e00604, am3_mpu_clkctrl_regs पूर्ण,
	अणु 0x44e00800, am3_l4_rtc_clkctrl_regs पूर्ण,
	अणु 0x44e00904, am3_gfx_l3_clkctrl_regs पूर्ण,
	अणु 0x44e00a20, am3_l4_cefuse_clkctrl_regs पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

काष्ठा ti_dt_clk am33xx_compat_clks[] = अणु
	DT_CLK(शून्य, "timer_32k_ck", "l4_per_cm:0138:0"),
	DT_CLK(शून्य, "timer_sys_ck", "sys_clkin_ck"),
	DT_CLK(शून्य, "clkdiv32k_ick", "l4_per_cm:0138:0"),
	DT_CLK(शून्य, "dbg_clka_ck", "l4_wkup_cm:0010:30"),
	DT_CLK(शून्य, "dbg_sysclk_ck", "l4_wkup_cm:0010:19"),
	DT_CLK(शून्य, "gpio0_dbclk", "l4_wkup_cm:0004:18"),
	DT_CLK(शून्य, "gpio1_dbclk", "l4_per_cm:0098:18"),
	DT_CLK(शून्य, "gpio2_dbclk", "l4_per_cm:009c:18"),
	DT_CLK(शून्य, "gpio3_dbclk", "l4_per_cm:00a0:18"),
	DT_CLK(शून्य, "stm_clk_div_ck", "l4_wkup_cm:0010:27"),
	DT_CLK(शून्य, "stm_pmd_clock_mux_ck", "l4_wkup_cm:0010:22"),
	DT_CLK(शून्य, "trace_clk_div_ck", "l4_wkup_cm:0010:24"),
	DT_CLK(शून्य, "trace_pmd_clk_mux_ck", "l4_wkup_cm:0010:20"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;
