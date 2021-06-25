<शैली गुरु>
/*
 * AM43XX Clock init
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
#समावेश <dt-bindings/घड़ी/am4.h>

#समावेश "clock.h"

अटल स्थिर अक्षर * स्थिर am4_synस_समयr_32kclk_parents[] __initस्थिर = अणु
	"mux_synctimer32k_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am4_counter_32k_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, am4_synस_समयr_32kclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर am4_gpio0_dbclk_parents[] __initस्थिर = अणु
	"gpio0_dbclk_mux_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am4_gpio1_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, am4_gpio0_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_l4_wkup_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_ADC_TSC_CLKCTRL, शून्य, CLKF_SW_SUP, "adc_tsc_fck", "l3s_tsc_clkdm" पूर्ण,
	अणु AM4_L4_WKUP_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_clkin_ck", "l4_wkup_clkdm" पूर्ण,
	अणु AM4_WKUP_M3_CLKCTRL, शून्य, CLKF_NO_IDLEST, "sys_clkin_ck" पूर्ण,
	अणु AM4_COUNTER_32K_CLKCTRL, am4_counter_32k_bit_data, CLKF_SW_SUP, "l4_wkup_cm:clk:0210:8" पूर्ण,
	अणु AM4_TIMER1_CLKCTRL, शून्य, CLKF_SW_SUP, "timer1_fck", "l4_wkup_clkdm" पूर्ण,
	अणु AM4_WD_TIMER2_CLKCTRL, शून्य, CLKF_SW_SUP, "wdt1_fck", "l4_wkup_clkdm" पूर्ण,
	अणु AM4_I2C1_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_wkupdm_ck", "l4_wkup_clkdm" पूर्ण,
	अणु AM4_UART1_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_wkupdm_ck", "l4_wkup_clkdm" पूर्ण,
	अणु AM4_SMARTREFLEX0_CLKCTRL, शून्य, CLKF_SW_SUP, "smartreflex0_fck", "l4_wkup_clkdm" पूर्ण,
	अणु AM4_SMARTREFLEX1_CLKCTRL, शून्य, CLKF_SW_SUP, "smartreflex1_fck", "l4_wkup_clkdm" पूर्ण,
	अणु AM4_CONTROL_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_clkin_ck", "l4_wkup_clkdm" पूर्ण,
	अणु AM4_GPIO1_CLKCTRL, am4_gpio1_bit_data, CLKF_SW_SUP, "sys_clkin_ck", "l4_wkup_clkdm" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_mpu_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_MPU_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_mpu_m2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_gfx_l3_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_GFX_CLKCTRL, शून्य, CLKF_SW_SUP, "gfx_fck_div_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_l4_rtc_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_RTC_CLKCTRL, शून्य, CLKF_SW_SUP, "clk_32768_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर am4_usb_otg_ss0_refclk960m_parents[] __initस्थिर = अणु
	"dpll_per_clkdcoldo",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am4_usb_otg_ss0_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, am4_usb_otg_ss0_refclk960m_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am4_usb_otg_ss1_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, am4_usb_otg_ss0_refclk960m_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर am4_gpio1_dbclk_parents[] __initस्थिर = अणु
	"clkdiv32k_ick",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am4_gpio2_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, am4_gpio1_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am4_gpio3_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, am4_gpio1_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am4_gpio4_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, am4_gpio1_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am4_gpio5_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, am4_gpio1_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am4_gpio6_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, am4_gpio1_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_l4_per_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_L3_MAIN_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM4_AES_CLKCTRL, शून्य, CLKF_SW_SUP, "aes0_fck", "l3_clkdm" पूर्ण,
	अणु AM4_DES_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM4_L3_INSTR_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM4_OCMCRAM_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM4_SHAM_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM4_VPFE0_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3s_clkdm" पूर्ण,
	अणु AM4_VPFE1_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3s_clkdm" पूर्ण,
	अणु AM4_TPCC_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM4_TPTC0_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM4_TPTC1_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM4_TPTC2_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk", "l3_clkdm" पूर्ण,
	अणु AM4_L4_HS_CLKCTRL, शून्य, CLKF_SW_SUP, "l4hs_gclk", "l3_clkdm" पूर्ण,
	अणु AM4_GPMC_CLKCTRL, शून्य, CLKF_SW_SUP, "l3s_gclk", "l3s_clkdm" पूर्ण,
	अणु AM4_MCASP0_CLKCTRL, शून्य, CLKF_SW_SUP, "mcasp0_fck", "l3s_clkdm" पूर्ण,
	अणु AM4_MCASP1_CLKCTRL, शून्य, CLKF_SW_SUP, "mcasp1_fck", "l3s_clkdm" पूर्ण,
	अणु AM4_MMC3_CLKCTRL, शून्य, CLKF_SW_SUP, "mmc_clk", "l3s_clkdm" पूर्ण,
	अणु AM4_QSPI_CLKCTRL, शून्य, CLKF_SW_SUP, "l3s_gclk", "l3s_clkdm" पूर्ण,
	अणु AM4_USB_OTG_SS0_CLKCTRL, am4_usb_otg_ss0_bit_data, CLKF_SW_SUP, "l3s_gclk", "l3s_clkdm" पूर्ण,
	अणु AM4_USB_OTG_SS1_CLKCTRL, am4_usb_otg_ss1_bit_data, CLKF_SW_SUP, "l3s_gclk", "l3s_clkdm" पूर्ण,
	अणु AM4_PRUSS_CLKCTRL, शून्य, CLKF_SW_SUP, "pruss_ocp_gclk", "pruss_ocp_clkdm" पूर्ण,
	अणु AM4_L4_LS_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_D_CAN0_CLKCTRL, शून्य, CLKF_SW_SUP, "dcan0_fck" पूर्ण,
	अणु AM4_D_CAN1_CLKCTRL, शून्य, CLKF_SW_SUP, "dcan1_fck" पूर्ण,
	अणु AM4_EPWMSS0_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_EPWMSS1_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_EPWMSS2_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_EPWMSS3_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_EPWMSS4_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_EPWMSS5_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_ELM_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_GPIO2_CLKCTRL, am4_gpio2_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_GPIO3_CLKCTRL, am4_gpio3_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_GPIO4_CLKCTRL, am4_gpio4_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_GPIO5_CLKCTRL, am4_gpio5_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_GPIO6_CLKCTRL, am4_gpio6_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_HDQ1W_CLKCTRL, शून्य, CLKF_SW_SUP, "func_12m_clk" पूर्ण,
	अणु AM4_I2C2_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_I2C3_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_MAILBOX_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_MMC1_CLKCTRL, शून्य, CLKF_SW_SUP, "mmc_clk" पूर्ण,
	अणु AM4_MMC2_CLKCTRL, शून्य, CLKF_SW_SUP, "mmc_clk" पूर्ण,
	अणु AM4_RNG_CLKCTRL, शून्य, CLKF_SW_SUP, "rng_fck" पूर्ण,
	अणु AM4_SPI0_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_SPI1_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_SPI2_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_SPI3_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_SPI4_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_SPINLOCK_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_TIMER2_CLKCTRL, शून्य, CLKF_SW_SUP, "timer2_fck" पूर्ण,
	अणु AM4_TIMER3_CLKCTRL, शून्य, CLKF_SW_SUP, "timer3_fck" पूर्ण,
	अणु AM4_TIMER4_CLKCTRL, शून्य, CLKF_SW_SUP, "timer4_fck" पूर्ण,
	अणु AM4_TIMER5_CLKCTRL, शून्य, CLKF_SW_SUP, "timer5_fck" पूर्ण,
	अणु AM4_TIMER6_CLKCTRL, शून्य, CLKF_SW_SUP, "timer6_fck" पूर्ण,
	अणु AM4_TIMER7_CLKCTRL, शून्य, CLKF_SW_SUP, "timer7_fck" पूर्ण,
	अणु AM4_TIMER8_CLKCTRL, शून्य, CLKF_SW_SUP, "timer8_fck" पूर्ण,
	अणु AM4_TIMER9_CLKCTRL, शून्य, CLKF_SW_SUP, "timer9_fck" पूर्ण,
	अणु AM4_TIMER10_CLKCTRL, शून्य, CLKF_SW_SUP, "timer10_fck" पूर्ण,
	अणु AM4_TIMER11_CLKCTRL, शून्य, CLKF_SW_SUP, "timer11_fck" पूर्ण,
	अणु AM4_UART2_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_UART3_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_UART4_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_UART5_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_UART6_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_OCP2SCP0_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_OCP2SCP1_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_EMIF_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_ddr_m2_ck", "emif_clkdm" पूर्ण,
	अणु AM4_DSS_CORE_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_SET_RATE_PARENT, "disp_clk", "dss_clkdm" पूर्ण,
	अणु AM4_CPGMAC0_CLKCTRL, शून्य, CLKF_SW_SUP, "cpsw_125mhz_gclk", "cpsw_125mhz_clkdm" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

स्थिर काष्ठा omap_clkctrl_data am4_clkctrl_compat_data[] __initस्थिर = अणु
	अणु 0x44df2820, am4_l4_wkup_clkctrl_regs पूर्ण,
	अणु 0x44df8320, am4_mpu_clkctrl_regs पूर्ण,
	अणु 0x44df8420, am4_gfx_l3_clkctrl_regs पूर्ण,
	अणु 0x44df8520, am4_l4_rtc_clkctrl_regs पूर्ण,
	अणु 0x44df8820, am4_l4_per_clkctrl_regs पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

स्थिर काष्ठा omap_clkctrl_data am438x_clkctrl_compat_data[] __initस्थिर = अणु
	अणु 0x44df2820, am4_l4_wkup_clkctrl_regs पूर्ण,
	अणु 0x44df8320, am4_mpu_clkctrl_regs पूर्ण,
	अणु 0x44df8420, am4_gfx_l3_clkctrl_regs पूर्ण,
	अणु 0x44df8820, am4_l4_per_clkctrl_regs पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

काष्ठा ti_dt_clk am43xx_compat_clks[] = अणु
	DT_CLK(शून्य, "timer_32k_ck", "clkdiv32k_ick"),
	DT_CLK(शून्य, "timer_sys_ck", "sys_clkin_ck"),
	DT_CLK(शून्य, "gpio0_dbclk", "l4_wkup_cm:0348:8"),
	DT_CLK(शून्य, "gpio1_dbclk", "l4_per_cm:0458:8"),
	DT_CLK(शून्य, "gpio2_dbclk", "l4_per_cm:0460:8"),
	DT_CLK(शून्य, "gpio3_dbclk", "l4_per_cm:0468:8"),
	DT_CLK(शून्य, "gpio4_dbclk", "l4_per_cm:0470:8"),
	DT_CLK(शून्य, "gpio5_dbclk", "l4_per_cm:0478:8"),
	DT_CLK(शून्य, "synctimer_32kclk", "l4_wkup_cm:0210:8"),
	DT_CLK(शून्य, "usb_otg_ss0_refclk960m", "l4_per_cm:0240:8"),
	DT_CLK(शून्य, "usb_otg_ss1_refclk960m", "l4_per_cm:0248:8"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;
