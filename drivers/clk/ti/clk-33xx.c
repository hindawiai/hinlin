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
	"clk-24mhz-clkctrl:0000:0",
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

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_l4ls_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_L4LS_UART6_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_L4LS_MMC1_CLKCTRL, शून्य, CLKF_SW_SUP, "mmc_clk" पूर्ण,
	अणु AM3_L4LS_ELM_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_L4LS_I2C3_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_L4LS_I2C2_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_L4LS_SPI0_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_L4LS_SPI1_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_L4LS_L4_LS_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_L4LS_UART2_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_L4LS_UART3_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_L4LS_UART4_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_L4LS_UART5_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM3_L4LS_TIMER7_CLKCTRL, शून्य, CLKF_SW_SUP, "timer7_fck" पूर्ण,
	अणु AM3_L4LS_TIMER2_CLKCTRL, शून्य, CLKF_SW_SUP, "timer2_fck" पूर्ण,
	अणु AM3_L4LS_TIMER3_CLKCTRL, शून्य, CLKF_SW_SUP, "timer3_fck" पूर्ण,
	अणु AM3_L4LS_TIMER4_CLKCTRL, शून्य, CLKF_SW_SUP, "timer4_fck" पूर्ण,
	अणु AM3_L4LS_RNG_CLKCTRL, शून्य, CLKF_SW_SUP, "rng_fck" पूर्ण,
	अणु AM3_L4LS_GPIO2_CLKCTRL, am3_gpio2_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_L4LS_GPIO3_CLKCTRL, am3_gpio3_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_L4LS_GPIO4_CLKCTRL, am3_gpio4_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_L4LS_D_CAN0_CLKCTRL, शून्य, CLKF_SW_SUP, "dcan0_fck" पूर्ण,
	अणु AM3_L4LS_D_CAN1_CLKCTRL, शून्य, CLKF_SW_SUP, "dcan1_fck" पूर्ण,
	अणु AM3_L4LS_EPWMSS1_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_L4LS_EPWMSS0_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_L4LS_EPWMSS2_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_L4LS_TIMER5_CLKCTRL, शून्य, CLKF_SW_SUP, "timer5_fck" पूर्ण,
	अणु AM3_L4LS_TIMER6_CLKCTRL, शून्य, CLKF_SW_SUP, "timer6_fck" पूर्ण,
	अणु AM3_L4LS_MMC2_CLKCTRL, शून्य, CLKF_SW_SUP, "mmc_clk" पूर्ण,
	अणु AM3_L4LS_SPINLOCK_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_L4LS_MAILBOX_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM3_L4LS_OCPWP_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_l3s_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_L3S_USB_OTG_HS_CLKCTRL, शून्य, CLKF_SW_SUP, "usbotg_fck" पूर्ण,
	अणु AM3_L3S_GPMC_CLKCTRL, शून्य, CLKF_SW_SUP, "l3s_gclk" पूर्ण,
	अणु AM3_L3S_MCASP0_CLKCTRL, शून्य, CLKF_SW_SUP, "mcasp0_fck" पूर्ण,
	अणु AM3_L3S_MCASP1_CLKCTRL, शून्य, CLKF_SW_SUP, "mcasp1_fck" पूर्ण,
	अणु AM3_L3S_MMC3_CLKCTRL, शून्य, CLKF_SW_SUP, "mmc_clk" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_l3_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_L3_TPTC0_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM3_L3_EMIF_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_ddr_m2_div2_ck" पूर्ण,
	अणु AM3_L3_OCMCRAM_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM3_L3_AES_CLKCTRL, शून्य, CLKF_SW_SUP, "aes0_fck" पूर्ण,
	अणु AM3_L3_SHAM_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM3_L3_TPCC_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM3_L3_L3_INSTR_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM3_L3_L3_MAIN_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM3_L3_TPTC1_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM3_L3_TPTC2_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_l4hs_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_L4HS_L4_HS_CLKCTRL, शून्य, CLKF_SW_SUP, "l4hs_gclk" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_pruss_ocp_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_PRUSS_OCP_PRUSS_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_NO_IDLEST, "pruss_ocp_gclk" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_cpsw_125mhz_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_CPSW_125MHZ_CPGMAC0_CLKCTRL, शून्य, CLKF_SW_SUP, "cpsw_125mhz_gclk" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_lcdc_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_LCDC_LCDC_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_SET_RATE_PARENT, "lcd_gclk" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_clk_24mhz_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_CLK_24MHZ_CLKDIV32K_CLKCTRL, शून्य, CLKF_SW_SUP, "clkdiv32k_ck" पूर्ण,
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

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_l4_wkup_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_L4_WKUP_CONTROL_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_core_m4_div2_ck" पूर्ण,
	अणु AM3_L4_WKUP_GPIO1_CLKCTRL, am3_gpio1_bit_data, CLKF_SW_SUP, "dpll_core_m4_div2_ck" पूर्ण,
	अणु AM3_L4_WKUP_L4_WKUP_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_core_m4_div2_ck" पूर्ण,
	अणु AM3_L4_WKUP_UART1_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_wkupdm_ck" पूर्ण,
	अणु AM3_L4_WKUP_I2C1_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_wkupdm_ck" पूर्ण,
	अणु AM3_L4_WKUP_ADC_TSC_CLKCTRL, शून्य, CLKF_SW_SUP, "adc_tsc_fck" पूर्ण,
	अणु AM3_L4_WKUP_SMARTREFLEX0_CLKCTRL, शून्य, CLKF_SW_SUP, "smartreflex0_fck" पूर्ण,
	अणु AM3_L4_WKUP_TIMER1_CLKCTRL, शून्य, CLKF_SW_SUP, "timer1_fck" पूर्ण,
	अणु AM3_L4_WKUP_SMARTREFLEX1_CLKCTRL, शून्य, CLKF_SW_SUP, "smartreflex1_fck" पूर्ण,
	अणु AM3_L4_WKUP_WD_TIMER2_CLKCTRL, शून्य, CLKF_SW_SUP, "wdt1_fck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर am3_dbg_sysclk_ck_parents[] __initस्थिर = अणु
	"sys_clkin_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर am3_trace_pmd_clk_mux_ck_parents[] __initस्थिर = अणु
	"l3-aon-clkctrl:0000:19",
	"l3-aon-clkctrl:0000:30",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर am3_trace_clk_भाग_ck_parents[] __initस्थिर = अणु
	"l3-aon-clkctrl:0000:20",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data am3_trace_clk_भाग_ck_data __initस्थिर = अणु
	.max_भाग = 64,
	.flags = CLK_DIVIDER_POWER_OF_TWO,
पूर्ण;

अटल स्थिर अक्षर * स्थिर am3_sपंचांग_clk_भाग_ck_parents[] __initस्थिर = अणु
	"l3-aon-clkctrl:0000:22",
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

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_l3_aon_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_L3_AON_DEBUGSS_CLKCTRL, am3_debugss_bit_data, CLKF_SW_SUP, "l3-aon-clkctrl:0000:24" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_l4_wkup_aon_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_L4_WKUP_AON_WKUP_M3_CLKCTRL, शून्य, CLKF_NO_IDLEST, "dpll_core_m4_div2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_mpu_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_MPU_MPU_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_mpu_m2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_l4_rtc_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_L4_RTC_RTC_CLKCTRL, शून्य, CLKF_SW_SUP, "clk-24mhz-clkctrl:0000:0" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_gfx_l3_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_GFX_L3_GFX_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_NO_IDLEST, "gfx_fck_div_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am3_l4_cefuse_clkctrl_regs[] __initस्थिर = अणु
	अणु AM3_L4_CEFUSE_CEFUSE_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_clkin_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

स्थिर काष्ठा omap_clkctrl_data am3_clkctrl_data[] __initस्थिर = अणु
	अणु 0x44e00038, am3_l4ls_clkctrl_regs पूर्ण,
	अणु 0x44e0001c, am3_l3s_clkctrl_regs पूर्ण,
	अणु 0x44e00024, am3_l3_clkctrl_regs पूर्ण,
	अणु 0x44e00120, am3_l4hs_clkctrl_regs पूर्ण,
	अणु 0x44e000e8, am3_pruss_ocp_clkctrl_regs पूर्ण,
	अणु 0x44e00000, am3_cpsw_125mhz_clkctrl_regs पूर्ण,
	अणु 0x44e00018, am3_lcdc_clkctrl_regs पूर्ण,
	अणु 0x44e0014c, am3_clk_24mhz_clkctrl_regs पूर्ण,
	अणु 0x44e00400, am3_l4_wkup_clkctrl_regs पूर्ण,
	अणु 0x44e00414, am3_l3_aon_clkctrl_regs पूर्ण,
	अणु 0x44e004b0, am3_l4_wkup_aon_clkctrl_regs पूर्ण,
	अणु 0x44e00600, am3_mpu_clkctrl_regs पूर्ण,
	अणु 0x44e00800, am3_l4_rtc_clkctrl_regs पूर्ण,
	अणु 0x44e00900, am3_gfx_l3_clkctrl_regs पूर्ण,
	अणु 0x44e00a00, am3_l4_cefuse_clkctrl_regs पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा ti_dt_clk am33xx_clks[] = अणु
	DT_CLK(शून्य, "timer_32k_ck", "clk-24mhz-clkctrl:0000:0"),
	DT_CLK(शून्य, "timer_sys_ck", "sys_clkin_ck"),
	DT_CLK(शून्य, "clkdiv32k_ick", "clk-24mhz-clkctrl:0000:0"),
	DT_CLK(शून्य, "dbg_clka_ck", "l3-aon-clkctrl:0000:30"),
	DT_CLK(शून्य, "dbg_sysclk_ck", "l3-aon-clkctrl:0000:19"),
	DT_CLK(शून्य, "gpio0_dbclk", "l4-wkup-clkctrl:0008:18"),
	DT_CLK(शून्य, "gpio1_dbclk", "l4ls-clkctrl:0074:18"),
	DT_CLK(शून्य, "gpio2_dbclk", "l4ls-clkctrl:0078:18"),
	DT_CLK(शून्य, "gpio3_dbclk", "l4ls-clkctrl:007c:18"),
	DT_CLK(शून्य, "stm_clk_div_ck", "l3-aon-clkctrl:0000:27"),
	DT_CLK(शून्य, "stm_pmd_clock_mux_ck", "l3-aon-clkctrl:0000:22"),
	DT_CLK(शून्य, "trace_clk_div_ck", "l3-aon-clkctrl:0000:24"),
	DT_CLK(शून्य, "trace_pmd_clk_mux_ck", "l3-aon-clkctrl:0000:20"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *enable_init_clks[] = अणु
	"dpll_ddr_m2_ck",
	"dpll_mpu_m2_ck",
	"l3_gclk",
	/* AM3_L3_L3_MAIN_CLKCTRL, needed during suspend */
	"l3-clkctrl:00bc:0",
	"l4hs_gclk",
	"l4fw_gclk",
	"l4ls_gclk",
	/* Required क्रम बाह्यal peripherals like, Audio codecs */
	"clkout2_ck",
पूर्ण;

पूर्णांक __init am33xx_dt_clk_init(व्योम)
अणु
	काष्ठा clk *clk1, *clk2;

	अगर (ti_clk_get_features()->flags & TI_CLK_CLKCTRL_COMPAT)
		ti_dt_घड़ीs_रेजिस्टर(am33xx_compat_clks);
	अन्यथा
		ti_dt_घड़ीs_रेजिस्टर(am33xx_clks);

	omap2_clk_disable_स्वतःidle_all();

	ti_clk_add_aliases();

	omap2_clk_enable_init_घड़ीs(enable_init_clks,
				     ARRAY_SIZE(enable_init_clks));

	/* TRM ERRATA: Timer 3 & 6 शेष parent (TCLKIN) may not be always
	 *    physically present, in such a हाल HWMOD enabling of
	 *    घड़ी would be failure with शेष parent. And समयr
	 *    probe thinks घड़ी is alपढ़ोy enabled, this leads to
	 *    crash upon accessing समयr 3 & 6 रेजिस्टरs in probe.
	 *    Fix by setting parent of both these समयrs to master
	 *    oscillator घड़ी.
	 */

	clk1 = clk_get_sys(शून्य, "sys_clkin_ck");
	clk2 = clk_get_sys(शून्य, "timer3_fck");
	clk_set_parent(clk2, clk1);

	clk2 = clk_get_sys(शून्य, "timer6_fck");
	clk_set_parent(clk2, clk1);
	/*
	 * The On-Chip 32K RC Osc घड़ी is not an accurate घड़ी-source as per
	 * the design/spec, so as a result, क्रम example, समयr which supposed
	 * to get expired @60Sec, but will expire somewhere ~@40Sec, which is
	 * not expected by any use-हाल, so change WDT1 घड़ी source to PRCM
	 * 32KHz घड़ी.
	 */
	clk1 = clk_get_sys(शून्य, "wdt1_fck");
	clk2 = clk_get_sys(शून्य, "clkdiv32k_ick");
	clk_set_parent(clk1, clk2);

	वापस 0;
पूर्ण
