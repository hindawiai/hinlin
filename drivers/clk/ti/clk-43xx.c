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

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_l3s_tsc_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_L3S_TSC_ADC_TSC_CLKCTRL, शून्य, CLKF_SW_SUP, "adc_tsc_fck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर am4_synस_समयr_32kclk_parents[] __initस्थिर = अणु
	"mux_synctimer32k_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data am4_counter_32k_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, am4_synस_समयr_32kclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_l4_wkup_aon_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_L4_WKUP_AON_WKUP_M3_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_NO_IDLEST, "sys_clkin_ck" पूर्ण,
	अणु AM4_L4_WKUP_AON_COUNTER_32K_CLKCTRL, am4_counter_32k_bit_data, CLKF_SW_SUP, "l4-wkup-aon-clkctrl:0008:8" पूर्ण,
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
	अणु AM4_L4_WKUP_L4_WKUP_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_clkin_ck" पूर्ण,
	अणु AM4_L4_WKUP_TIMER1_CLKCTRL, शून्य, CLKF_SW_SUP, "timer1_fck" पूर्ण,
	अणु AM4_L4_WKUP_WD_TIMER2_CLKCTRL, शून्य, CLKF_SW_SUP, "wdt1_fck" पूर्ण,
	अणु AM4_L4_WKUP_I2C1_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_wkupdm_ck" पूर्ण,
	अणु AM4_L4_WKUP_UART1_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_wkupdm_ck" पूर्ण,
	अणु AM4_L4_WKUP_SMARTREFLEX0_CLKCTRL, शून्य, CLKF_SW_SUP, "smartreflex0_fck" पूर्ण,
	अणु AM4_L4_WKUP_SMARTREFLEX1_CLKCTRL, शून्य, CLKF_SW_SUP, "smartreflex1_fck" पूर्ण,
	अणु AM4_L4_WKUP_CONTROL_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_clkin_ck" पूर्ण,
	अणु AM4_L4_WKUP_GPIO1_CLKCTRL, am4_gpio1_bit_data, CLKF_SW_SUP, "sys_clkin_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_mpu_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_MPU_MPU_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_mpu_m2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_gfx_l3_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_GFX_L3_GFX_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_NO_IDLEST, "gfx_fck_div_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_l4_rtc_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_L4_RTC_RTC_CLKCTRL, शून्य, CLKF_SW_SUP, "clkdiv32k_ick" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_l3_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_L3_L3_MAIN_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM4_L3_AES_CLKCTRL, शून्य, CLKF_SW_SUP, "aes0_fck" पूर्ण,
	अणु AM4_L3_DES_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM4_L3_L3_INSTR_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM4_L3_OCMCRAM_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM4_L3_SHAM_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM4_L3_TPCC_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM4_L3_TPTC0_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM4_L3_TPTC1_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM4_L3_TPTC2_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM4_L3_L4_HS_CLKCTRL, शून्य, CLKF_SW_SUP, "l4hs_gclk" पूर्ण,
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

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_l3s_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_L3S_VPFE0_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM4_L3S_VPFE1_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_gclk" पूर्ण,
	अणु AM4_L3S_GPMC_CLKCTRL, शून्य, CLKF_SW_SUP, "l3s_gclk" पूर्ण,
	अणु AM4_L3S_MCASP0_CLKCTRL, शून्य, CLKF_SW_SUP, "mcasp0_fck" पूर्ण,
	अणु AM4_L3S_MCASP1_CLKCTRL, शून्य, CLKF_SW_SUP, "mcasp1_fck" पूर्ण,
	अणु AM4_L3S_MMC3_CLKCTRL, शून्य, CLKF_SW_SUP, "mmc_clk" पूर्ण,
	अणु AM4_L3S_QSPI_CLKCTRL, शून्य, CLKF_SW_SUP, "l3s_gclk" पूर्ण,
	अणु AM4_L3S_USB_OTG_SS0_CLKCTRL, am4_usb_otg_ss0_bit_data, CLKF_SW_SUP, "l3s_gclk" पूर्ण,
	अणु AM4_L3S_USB_OTG_SS1_CLKCTRL, am4_usb_otg_ss1_bit_data, CLKF_SW_SUP, "l3s_gclk" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_pruss_ocp_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_PRUSS_OCP_PRUSS_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_NO_IDLEST, "pruss_ocp_gclk" पूर्ण,
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

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_l4ls_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_L4LS_L4_LS_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_D_CAN0_CLKCTRL, शून्य, CLKF_SW_SUP, "dcan0_fck" पूर्ण,
	अणु AM4_L4LS_D_CAN1_CLKCTRL, शून्य, CLKF_SW_SUP, "dcan1_fck" पूर्ण,
	अणु AM4_L4LS_EPWMSS0_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_EPWMSS1_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_EPWMSS2_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_EPWMSS3_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_EPWMSS4_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_EPWMSS5_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_ELM_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_GPIO2_CLKCTRL, am4_gpio2_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_GPIO3_CLKCTRL, am4_gpio3_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_GPIO4_CLKCTRL, am4_gpio4_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_GPIO5_CLKCTRL, am4_gpio5_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_GPIO6_CLKCTRL, am4_gpio6_bit_data, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_HDQ1W_CLKCTRL, शून्य, CLKF_SW_SUP, "func_12m_clk" पूर्ण,
	अणु AM4_L4LS_I2C2_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_L4LS_I2C3_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_L4LS_MAILBOX_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_MMC1_CLKCTRL, शून्य, CLKF_SW_SUP, "mmc_clk" पूर्ण,
	अणु AM4_L4LS_MMC2_CLKCTRL, शून्य, CLKF_SW_SUP, "mmc_clk" पूर्ण,
	अणु AM4_L4LS_RNG_CLKCTRL, शून्य, CLKF_SW_SUP, "rng_fck" पूर्ण,
	अणु AM4_L4LS_SPI0_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_L4LS_SPI1_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_L4LS_SPI2_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_L4LS_SPI3_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_L4LS_SPI4_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_L4LS_SPINLOCK_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_TIMER2_CLKCTRL, शून्य, CLKF_SW_SUP, "timer2_fck" पूर्ण,
	अणु AM4_L4LS_TIMER3_CLKCTRL, शून्य, CLKF_SW_SUP, "timer3_fck" पूर्ण,
	अणु AM4_L4LS_TIMER4_CLKCTRL, शून्य, CLKF_SW_SUP, "timer4_fck" पूर्ण,
	अणु AM4_L4LS_TIMER5_CLKCTRL, शून्य, CLKF_SW_SUP, "timer5_fck" पूर्ण,
	अणु AM4_L4LS_TIMER6_CLKCTRL, शून्य, CLKF_SW_SUP, "timer6_fck" पूर्ण,
	अणु AM4_L4LS_TIMER7_CLKCTRL, शून्य, CLKF_SW_SUP, "timer7_fck" पूर्ण,
	अणु AM4_L4LS_TIMER8_CLKCTRL, शून्य, CLKF_SW_SUP, "timer8_fck" पूर्ण,
	अणु AM4_L4LS_TIMER9_CLKCTRL, शून्य, CLKF_SW_SUP, "timer9_fck" पूर्ण,
	अणु AM4_L4LS_TIMER10_CLKCTRL, शून्य, CLKF_SW_SUP, "timer10_fck" पूर्ण,
	अणु AM4_L4LS_TIMER11_CLKCTRL, शून्य, CLKF_SW_SUP, "timer11_fck" पूर्ण,
	अणु AM4_L4LS_UART2_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_L4LS_UART3_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_L4LS_UART4_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_L4LS_UART5_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_L4LS_UART6_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_per_m2_div4_ck" पूर्ण,
	अणु AM4_L4LS_OCP2SCP0_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु AM4_L4LS_OCP2SCP1_CLKCTRL, शून्य, CLKF_SW_SUP, "l4ls_gclk" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_emअगर_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_EMIF_EMIF_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_ddr_m2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_dss_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_DSS_DSS_CORE_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_SET_RATE_PARENT, "disp_clk" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data am4_cpsw_125mhz_clkctrl_regs[] __initस्थिर = अणु
	अणु AM4_CPSW_125MHZ_CPGMAC0_CLKCTRL, शून्य, CLKF_SW_SUP, "cpsw_125mhz_gclk" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

स्थिर काष्ठा omap_clkctrl_data am4_clkctrl_data[] __initस्थिर = अणु
	अणु 0x44df2920, am4_l3s_tsc_clkctrl_regs पूर्ण,
	अणु 0x44df2a28, am4_l4_wkup_aon_clkctrl_regs पूर्ण,
	अणु 0x44df2a20, am4_l4_wkup_clkctrl_regs पूर्ण,
	अणु 0x44df8320, am4_mpu_clkctrl_regs पूर्ण,
	अणु 0x44df8420, am4_gfx_l3_clkctrl_regs पूर्ण,
	अणु 0x44df8520, am4_l4_rtc_clkctrl_regs पूर्ण,
	अणु 0x44df8820, am4_l3_clkctrl_regs पूर्ण,
	अणु 0x44df8868, am4_l3s_clkctrl_regs पूर्ण,
	अणु 0x44df8b20, am4_pruss_ocp_clkctrl_regs पूर्ण,
	अणु 0x44df8c20, am4_l4ls_clkctrl_regs पूर्ण,
	अणु 0x44df8f20, am4_emअगर_clkctrl_regs पूर्ण,
	अणु 0x44df9220, am4_dss_clkctrl_regs पूर्ण,
	अणु 0x44df9320, am4_cpsw_125mhz_clkctrl_regs पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

स्थिर काष्ठा omap_clkctrl_data am438x_clkctrl_data[] __initस्थिर = अणु
	अणु 0x44df2920, am4_l3s_tsc_clkctrl_regs पूर्ण,
	अणु 0x44df2a28, am4_l4_wkup_aon_clkctrl_regs पूर्ण,
	अणु 0x44df2a20, am4_l4_wkup_clkctrl_regs पूर्ण,
	अणु 0x44df8320, am4_mpu_clkctrl_regs पूर्ण,
	अणु 0x44df8420, am4_gfx_l3_clkctrl_regs पूर्ण,
	अणु 0x44df8820, am4_l3_clkctrl_regs पूर्ण,
	अणु 0x44df8868, am4_l3s_clkctrl_regs पूर्ण,
	अणु 0x44df8b20, am4_pruss_ocp_clkctrl_regs पूर्ण,
	अणु 0x44df8c20, am4_l4ls_clkctrl_regs पूर्ण,
	अणु 0x44df8f20, am4_emअगर_clkctrl_regs पूर्ण,
	अणु 0x44df9220, am4_dss_clkctrl_regs पूर्ण,
	अणु 0x44df9320, am4_cpsw_125mhz_clkctrl_regs पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा ti_dt_clk am43xx_clks[] = अणु
	DT_CLK(शून्य, "timer_32k_ck", "clkdiv32k_ick"),
	DT_CLK(शून्य, "timer_sys_ck", "sys_clkin_ck"),
	DT_CLK(शून्य, "gpio0_dbclk", "l4-wkup-clkctrl:0148:8"),
	DT_CLK(शून्य, "gpio1_dbclk", "l4ls-clkctrl:0058:8"),
	DT_CLK(शून्य, "gpio2_dbclk", "l4ls-clkctrl:0060:8"),
	DT_CLK(शून्य, "gpio3_dbclk", "l4ls-clkctrl:0068:8"),
	DT_CLK(शून्य, "gpio4_dbclk", "l4ls-clkctrl:0070:8"),
	DT_CLK(शून्य, "gpio5_dbclk", "l4ls-clkctrl:0078:8"),
	DT_CLK(शून्य, "synctimer_32kclk", "l4-wkup-aon-clkctrl:0008:8"),
	DT_CLK(शून्य, "usb_otg_ss0_refclk960m", "l3s-clkctrl:01f8:8"),
	DT_CLK(शून्य, "usb_otg_ss1_refclk960m", "l3s-clkctrl:0200:8"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *enable_init_clks[] = अणु
	/* AM4_L3_L3_MAIN_CLKCTRL, needed during suspend */
	"l3-clkctrl:0000:0",
पूर्ण;

पूर्णांक __init am43xx_dt_clk_init(व्योम)
अणु
	काष्ठा clk *clk1, *clk2;

	अगर (ti_clk_get_features()->flags & TI_CLK_CLKCTRL_COMPAT)
		ti_dt_घड़ीs_रेजिस्टर(am43xx_compat_clks);
	अन्यथा
		ti_dt_घड़ीs_रेजिस्टर(am43xx_clks);

	omap2_clk_disable_स्वतःidle_all();

	omap2_clk_enable_init_घड़ीs(enable_init_clks,
				     ARRAY_SIZE(enable_init_clks));

	ti_clk_add_aliases();

	/*
	 * cpsw_cpts_rft_clk  has got the choice of 3 घड़ीsources
	 * dpll_core_m4_ck, dpll_core_m5_ck and dpll_disp_m2_ck.
	 * By शेष dpll_core_m4_ck is selected, witn this as घड़ी
	 * source the CPTS करोesnot work properly. It gives घड़ीcheck errors
	 * जबतक running PTP.
	 * घड़ीcheck: घड़ी jumped backward or running slower than expected!
	 * By selecting dpll_core_m5_ck as the घड़ीsource fixes this issue.
	 * In AM335x dpll_core_m5_ck is the शेष घड़ीsource.
	 */
	clk1 = clk_get_sys(शून्य, "cpsw_cpts_rft_clk");
	clk2 = clk_get_sys(शून्य, "dpll_core_m5_ck");
	clk_set_parent(clk1, clk2);

	वापस 0;
पूर्ण
