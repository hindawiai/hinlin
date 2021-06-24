<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP4 Clock init
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 *
 * Tero Kristo (t-kristo@ti.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/ti.h>
#समावेश <dt-bindings/घड़ी/omap4.h>

#समावेश "clock.h"

/*
 * OMAP4 ABE DPLL शेष frequency. In OMAP4460 TRM version V, section
 * "3.6.3.2.3 CM1_ABE Clock Generator" states that the "DPLL_ABE_X2_CLK
 * must be set to 196.608 MHz" and hence, the DPLL locked frequency is
 * half of this value.
 */
#घोषणा OMAP4_DPLL_ABE_DEFFREQ				98304000

/*
 * OMAP4 USB DPLL शेष frequency. In OMAP4430 TRM version V, section
 * "3.6.3.9.5 DPLL_USB Preferred Settings" shows that the preferred
 * locked frequency क्रम the USB DPLL is 960MHz.
 */
#घोषणा OMAP4_DPLL_USB_DEFFREQ				960000000

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_mpuss_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_MPU_CLKCTRL, शून्य, 0, "dpll_mpu_m2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_tesla_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_DSP_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_NO_IDLEST, "dpll_iva_m4x2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_aess_fclk_parents[] __initस्थिर = अणु
	"abe_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data omap4_aess_fclk_data __initस्थिर = अणु
	.max_भाग = 2,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_aess_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_DIVIDER, omap4_aess_fclk_parents, &omap4_aess_fclk_data पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_func_dmic_abe_gfclk_parents[] __initस्थिर = अणु
	"abe_cm:clk:0018:26",
	"pad_clks_ck",
	"slimbus_clk",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_dmic_sync_mux_ck_parents[] __initस्थिर = अणु
	"abe_24m_fclk",
	"syc_clk_div_ck",
	"func_24m_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_dmic_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_func_dmic_abe_gfclk_parents, शून्य पूर्ण,
	अणु 26, TI_CLK_MUX, omap4_dmic_sync_mux_ck_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_func_mcasp_abe_gfclk_parents[] __initस्थिर = अणु
	"abe_cm:clk:0020:26",
	"pad_clks_ck",
	"slimbus_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_mcasp_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_func_mcasp_abe_gfclk_parents, शून्य पूर्ण,
	अणु 26, TI_CLK_MUX, omap4_dmic_sync_mux_ck_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_func_mcbsp1_gfclk_parents[] __initस्थिर = अणु
	"abe_cm:clk:0028:26",
	"pad_clks_ck",
	"slimbus_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_mcbsp1_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_func_mcbsp1_gfclk_parents, शून्य पूर्ण,
	अणु 26, TI_CLK_MUX, omap4_dmic_sync_mux_ck_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_func_mcbsp2_gfclk_parents[] __initस्थिर = अणु
	"abe_cm:clk:0030:26",
	"pad_clks_ck",
	"slimbus_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_mcbsp2_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_func_mcbsp2_gfclk_parents, शून्य पूर्ण,
	अणु 26, TI_CLK_MUX, omap4_dmic_sync_mux_ck_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_func_mcbsp3_gfclk_parents[] __initस्थिर = अणु
	"abe_cm:clk:0038:26",
	"pad_clks_ck",
	"slimbus_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_mcbsp3_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_func_mcbsp3_gfclk_parents, शून्य पूर्ण,
	अणु 26, TI_CLK_MUX, omap4_dmic_sync_mux_ck_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_slimbus1_fclk_0_parents[] __initस्थिर = अणु
	"abe_24m_fclk",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_slimbus1_fclk_1_parents[] __initस्थिर = अणु
	"func_24m_clk",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_slimbus1_fclk_2_parents[] __initस्थिर = अणु
	"pad_clks_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_slimbus1_slimbus_clk_parents[] __initस्थिर = अणु
	"slimbus_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_slimbus1_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap4_slimbus1_fclk_0_parents, शून्य पूर्ण,
	अणु 9, TI_CLK_GATE, omap4_slimbus1_fclk_1_parents, शून्य पूर्ण,
	अणु 10, TI_CLK_GATE, omap4_slimbus1_fclk_2_parents, शून्य पूर्ण,
	अणु 11, TI_CLK_GATE, omap4_slimbus1_slimbus_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_समयr5_sync_mux_parents[] __initस्थिर = अणु
	"syc_clk_div_ck",
	"sys_32k_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_समयr5_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_समयr5_sync_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_समयr6_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_समयr5_sync_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_समयr7_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_समयr5_sync_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_समयr8_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_समयr5_sync_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_abe_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_L4_ABE_CLKCTRL, शून्य, 0, "ocp_abe_iclk" पूर्ण,
	अणु OMAP4_AESS_CLKCTRL, omap4_aess_bit_data, CLKF_SW_SUP, "abe_cm:clk:0008:24" पूर्ण,
	अणु OMAP4_MCPDM_CLKCTRL, शून्य, CLKF_SW_SUP, "pad_clks_ck" पूर्ण,
	अणु OMAP4_DMIC_CLKCTRL, omap4_dmic_bit_data, CLKF_SW_SUP, "abe_cm:clk:0018:24" पूर्ण,
	अणु OMAP4_MCASP_CLKCTRL, omap4_mcasp_bit_data, CLKF_SW_SUP, "abe_cm:clk:0020:24" पूर्ण,
	अणु OMAP4_MCBSP1_CLKCTRL, omap4_mcbsp1_bit_data, CLKF_SW_SUP, "abe_cm:clk:0028:24" पूर्ण,
	अणु OMAP4_MCBSP2_CLKCTRL, omap4_mcbsp2_bit_data, CLKF_SW_SUP, "abe_cm:clk:0030:24" पूर्ण,
	अणु OMAP4_MCBSP3_CLKCTRL, omap4_mcbsp3_bit_data, CLKF_SW_SUP, "abe_cm:clk:0038:24" पूर्ण,
	अणु OMAP4_SLIMBUS1_CLKCTRL, omap4_slimbus1_bit_data, CLKF_SW_SUP, "abe_cm:clk:0040:8" पूर्ण,
	अणु OMAP4_TIMER5_CLKCTRL, omap4_समयr5_bit_data, CLKF_SW_SUP, "abe_cm:clk:0048:24" पूर्ण,
	अणु OMAP4_TIMER6_CLKCTRL, omap4_समयr6_bit_data, CLKF_SW_SUP, "abe_cm:clk:0050:24" पूर्ण,
	अणु OMAP4_TIMER7_CLKCTRL, omap4_समयr7_bit_data, CLKF_SW_SUP, "abe_cm:clk:0058:24" पूर्ण,
	अणु OMAP4_TIMER8_CLKCTRL, omap4_समयr8_bit_data, CLKF_SW_SUP, "abe_cm:clk:0060:24" पूर्ण,
	अणु OMAP4_WD_TIMER3_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_32k_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_l4_ao_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_SMARTREFLEX_MPU_CLKCTRL, शून्य, CLKF_SW_SUP, "l4_wkup_clk_mux_ck" पूर्ण,
	अणु OMAP4_SMARTREFLEX_IVA_CLKCTRL, शून्य, CLKF_SW_SUP, "l4_wkup_clk_mux_ck" पूर्ण,
	अणु OMAP4_SMARTREFLEX_CORE_CLKCTRL, शून्य, CLKF_SW_SUP, "l4_wkup_clk_mux_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_l3_1_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_L3_MAIN_1_CLKCTRL, शून्य, 0, "l3_div_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_l3_2_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_L3_MAIN_2_CLKCTRL, शून्य, 0, "l3_div_ck" पूर्ण,
	अणु OMAP4_GPMC_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_div_ck" पूर्ण,
	अणु OMAP4_OCMC_RAM_CLKCTRL, शून्य, 0, "l3_div_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_ducati_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_IPU_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_NO_IDLEST, "ducati_clk_mux_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_l3_dma_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_DMA_SYSTEM_CLKCTRL, शून्य, 0, "l3_div_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_l3_emअगर_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_DMM_CLKCTRL, शून्य, 0, "l3_div_ck" पूर्ण,
	अणु OMAP4_EMIF1_CLKCTRL, शून्य, CLKF_HW_SUP, "ddrphy_ck" पूर्ण,
	अणु OMAP4_EMIF2_CLKCTRL, शून्य, CLKF_HW_SUP, "ddrphy_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_d2d_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_C2C_CLKCTRL, शून्य, 0, "div_core_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_l4_cfg_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_L4_CFG_CLKCTRL, शून्य, 0, "l4_div_ck" पूर्ण,
	अणु OMAP4_SPINLOCK_CLKCTRL, शून्य, 0, "l4_div_ck" पूर्ण,
	अणु OMAP4_MAILBOX_CLKCTRL, शून्य, 0, "l4_div_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_l3_instr_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_L3_MAIN_3_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_div_ck" पूर्ण,
	अणु OMAP4_L3_INSTR_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_div_ck" पूर्ण,
	अणु OMAP4_OCP_WP_NOC_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_div_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_ivahd_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_IVA_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_NO_IDLEST, "dpll_iva_m5x2_ck" पूर्ण,
	अणु OMAP4_SL2IF_CLKCTRL, शून्य, CLKF_HW_SUP, "dpll_iva_m5x2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_iss_ctrlclk_parents[] __initस्थिर = अणु
	"func_96m_fclk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_iss_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap4_iss_ctrlclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_fdअगर_fck_parents[] __initस्थिर = अणु
	"dpll_per_m4x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data omap4_fdअगर_fck_data __initस्थिर = अणु
	.max_भाग = 4,
	.flags = CLK_DIVIDER_POWER_OF_TWO,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_fdअगर_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_DIVIDER, omap4_fdअगर_fck_parents, &omap4_fdअगर_fck_data पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_iss_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_ISS_CLKCTRL, omap4_iss_bit_data, CLKF_SW_SUP, "ducati_clk_mux_ck" पूर्ण,
	अणु OMAP4_FDIF_CLKCTRL, omap4_fdअगर_bit_data, CLKF_SW_SUP, "iss_cm:clk:0008:24" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_dss_dss_clk_parents[] __initस्थिर = अणु
	"dpll_per_m5x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_dss_48mhz_clk_parents[] __initस्थिर = अणु
	"func_48mc_fclk",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_dss_sys_clk_parents[] __initस्थिर = अणु
	"syc_clk_div_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_dss_tv_clk_parents[] __initस्थिर = अणु
	"extalt_clkin_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_dss_core_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap4_dss_dss_clk_parents, शून्य पूर्ण,
	अणु 9, TI_CLK_GATE, omap4_dss_48mhz_clk_parents, शून्य पूर्ण,
	अणु 10, TI_CLK_GATE, omap4_dss_sys_clk_parents, शून्य पूर्ण,
	अणु 11, TI_CLK_GATE, omap4_dss_tv_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_l3_dss_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_DSS_CORE_CLKCTRL, omap4_dss_core_bit_data, CLKF_SW_SUP, "l3_dss_cm:clk:0000:8" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_sgx_clk_mux_parents[] __initस्थिर = अणु
	"dpll_core_m7x2_ck",
	"dpll_per_m7x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_gpu_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_sgx_clk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_l3_gfx_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_GPU_CLKCTRL, omap4_gpu_bit_data, CLKF_SW_SUP, "l3_gfx_cm:clk:0000:24" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_hsmmc1_fclk_parents[] __initस्थिर = अणु
	"func_64m_fclk",
	"func_96m_fclk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_mmc1_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_hsmmc1_fclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_mmc2_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_hsmmc1_fclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_hsi_fck_parents[] __initस्थिर = अणु
	"dpll_per_m2x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data omap4_hsi_fck_data __initस्थिर = अणु
	.max_भाग = 4,
	.flags = CLK_DIVIDER_POWER_OF_TWO,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_hsi_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_DIVIDER, omap4_hsi_fck_parents, &omap4_hsi_fck_data पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_usb_host_hs_uपंचांगi_p1_clk_parents[] __initस्थिर = अणु
	"l3_init_cm:clk:0038:24",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_usb_host_hs_uपंचांगi_p2_clk_parents[] __initस्थिर = अणु
	"l3_init_cm:clk:0038:25",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_usb_host_hs_uपंचांगi_p3_clk_parents[] __initस्थिर = अणु
	"init_60m_fclk",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_usb_host_hs_hsic480m_p1_clk_parents[] __initस्थिर = अणु
	"dpll_usb_m2_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_uपंचांगi_p1_gfclk_parents[] __initस्थिर = अणु
	"init_60m_fclk",
	"xclk60mhsp1_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_uपंचांगi_p2_gfclk_parents[] __initस्थिर = अणु
	"init_60m_fclk",
	"xclk60mhsp2_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_usb_host_hs_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap4_usb_host_hs_uपंचांगi_p1_clk_parents, शून्य पूर्ण,
	अणु 9, TI_CLK_GATE, omap4_usb_host_hs_uपंचांगi_p2_clk_parents, शून्य पूर्ण,
	अणु 10, TI_CLK_GATE, omap4_usb_host_hs_uपंचांगi_p3_clk_parents, शून्य पूर्ण,
	अणु 11, TI_CLK_GATE, omap4_usb_host_hs_uपंचांगi_p3_clk_parents, शून्य पूर्ण,
	अणु 12, TI_CLK_GATE, omap4_usb_host_hs_uपंचांगi_p3_clk_parents, शून्य पूर्ण,
	अणु 13, TI_CLK_GATE, omap4_usb_host_hs_hsic480m_p1_clk_parents, शून्य पूर्ण,
	अणु 14, TI_CLK_GATE, omap4_usb_host_hs_hsic480m_p1_clk_parents, शून्य पूर्ण,
	अणु 15, TI_CLK_GATE, omap4_dss_48mhz_clk_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, omap4_uपंचांगi_p1_gfclk_parents, शून्य पूर्ण,
	अणु 25, TI_CLK_MUX, omap4_uपंचांगi_p2_gfclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_usb_otg_hs_xclk_parents[] __initस्थिर = अणु
	"l3_init_cm:clk:0040:24",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_otg_60m_gfclk_parents[] __initस्थिर = अणु
	"utmi_phy_clkout_ck",
	"xclk60motg_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_usb_otg_hs_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap4_usb_otg_hs_xclk_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, omap4_otg_60m_gfclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_usb_tll_hs_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap4_usb_host_hs_uपंचांगi_p3_clk_parents, शून्य पूर्ण,
	अणु 9, TI_CLK_GATE, omap4_usb_host_hs_uपंचांगi_p3_clk_parents, शून्य पूर्ण,
	अणु 10, TI_CLK_GATE, omap4_usb_host_hs_uपंचांगi_p3_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_ocp2scp_usb_phy_phy_48m_parents[] __initस्थिर = अणु
	"func_48m_fclk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_ocp2scp_usb_phy_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap4_ocp2scp_usb_phy_phy_48m_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_l3_init_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_MMC1_CLKCTRL, omap4_mmc1_bit_data, CLKF_SW_SUP, "l3_init_cm:clk:0008:24" पूर्ण,
	अणु OMAP4_MMC2_CLKCTRL, omap4_mmc2_bit_data, CLKF_SW_SUP, "l3_init_cm:clk:0010:24" पूर्ण,
	अणु OMAP4_HSI_CLKCTRL, omap4_hsi_bit_data, CLKF_HW_SUP, "l3_init_cm:clk:0018:24" पूर्ण,
	अणु OMAP4_USB_HOST_HS_CLKCTRL, omap4_usb_host_hs_bit_data, CLKF_SW_SUP, "init_60m_fclk" पूर्ण,
	अणु OMAP4_USB_OTG_HS_CLKCTRL, omap4_usb_otg_hs_bit_data, CLKF_HW_SUP, "l3_div_ck" पूर्ण,
	अणु OMAP4_USB_TLL_HS_CLKCTRL, omap4_usb_tll_hs_bit_data, CLKF_HW_SUP, "l4_div_ck" पूर्ण,
	अणु OMAP4_USB_HOST_FS_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48mc_fclk" पूर्ण,
	अणु OMAP4_OCP2SCP_USB_PHY_CLKCTRL, omap4_ocp2scp_usb_phy_bit_data, CLKF_HW_SUP, "l3_init_cm:clk:00c0:8" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_cm2_dm10_mux_parents[] __initस्थिर = अणु
	"sys_clkin_ck",
	"sys_32k_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_समयr10_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_cm2_dm10_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_समयr11_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_cm2_dm10_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_समयr2_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_cm2_dm10_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_समयr3_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_cm2_dm10_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_समयr4_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_cm2_dm10_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_समयr9_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_cm2_dm10_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_gpio2_dbclk_parents[] __initस्थिर = अणु
	"sys_32k_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_gpio2_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap4_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_gpio3_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap4_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_gpio4_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap4_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_gpio5_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap4_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_gpio6_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap4_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_per_mcbsp4_gfclk_parents[] __initस्थिर = अणु
	"l4_per_cm:clk:00c0:26",
	"pad_clks_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_mcbsp4_sync_mux_ck_parents[] __initस्थिर = अणु
	"func_96m_fclk",
	"per_abe_nc_fclk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_mcbsp4_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_per_mcbsp4_gfclk_parents, शून्य पूर्ण,
	अणु 26, TI_CLK_MUX, omap4_mcbsp4_sync_mux_ck_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_slimbus2_fclk_0_parents[] __initस्थिर = अणु
	"func_24mc_fclk",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_slimbus2_fclk_1_parents[] __initस्थिर = अणु
	"per_abe_24m_fclk",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_slimbus2_slimbus_clk_parents[] __initस्थिर = अणु
	"pad_slimbus_core_clks_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_slimbus2_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap4_slimbus2_fclk_0_parents, शून्य पूर्ण,
	अणु 9, TI_CLK_GATE, omap4_slimbus2_fclk_1_parents, शून्य पूर्ण,
	अणु 10, TI_CLK_GATE, omap4_slimbus2_slimbus_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_l4_per_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_TIMER10_CLKCTRL, omap4_समयr10_bit_data, CLKF_SW_SUP, "l4_per_cm:clk:0008:24" पूर्ण,
	अणु OMAP4_TIMER11_CLKCTRL, omap4_समयr11_bit_data, CLKF_SW_SUP, "l4_per_cm:clk:0010:24" पूर्ण,
	अणु OMAP4_TIMER2_CLKCTRL, omap4_समयr2_bit_data, CLKF_SW_SUP, "l4_per_cm:clk:0018:24" पूर्ण,
	अणु OMAP4_TIMER3_CLKCTRL, omap4_समयr3_bit_data, CLKF_SW_SUP, "l4_per_cm:clk:0020:24" पूर्ण,
	अणु OMAP4_TIMER4_CLKCTRL, omap4_समयr4_bit_data, CLKF_SW_SUP, "l4_per_cm:clk:0028:24" पूर्ण,
	अणु OMAP4_TIMER9_CLKCTRL, omap4_समयr9_bit_data, CLKF_SW_SUP, "l4_per_cm:clk:0030:24" पूर्ण,
	अणु OMAP4_ELM_CLKCTRL, शून्य, 0, "l4_div_ck" पूर्ण,
	अणु OMAP4_GPIO2_CLKCTRL, omap4_gpio2_bit_data, CLKF_HW_SUP, "l4_div_ck" पूर्ण,
	अणु OMAP4_GPIO3_CLKCTRL, omap4_gpio3_bit_data, CLKF_HW_SUP, "l4_div_ck" पूर्ण,
	अणु OMAP4_GPIO4_CLKCTRL, omap4_gpio4_bit_data, CLKF_HW_SUP, "l4_div_ck" पूर्ण,
	अणु OMAP4_GPIO5_CLKCTRL, omap4_gpio5_bit_data, CLKF_HW_SUP, "l4_div_ck" पूर्ण,
	अणु OMAP4_GPIO6_CLKCTRL, omap4_gpio6_bit_data, CLKF_HW_SUP, "l4_div_ck" पूर्ण,
	अणु OMAP4_HDQ1W_CLKCTRL, शून्य, CLKF_SW_SUP, "func_12m_fclk" पूर्ण,
	अणु OMAP4_I2C1_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु OMAP4_I2C2_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु OMAP4_I2C3_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु OMAP4_I2C4_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु OMAP4_L4_PER_CLKCTRL, शून्य, 0, "l4_div_ck" पूर्ण,
	अणु OMAP4_MCBSP4_CLKCTRL, omap4_mcbsp4_bit_data, CLKF_SW_SUP, "l4_per_cm:clk:00c0:24" पूर्ण,
	अणु OMAP4_MCSPI1_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP4_MCSPI2_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP4_MCSPI3_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP4_MCSPI4_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP4_MMC3_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP4_MMC4_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP4_SLIMBUS2_CLKCTRL, omap4_slimbus2_bit_data, CLKF_SW_SUP, "l4_per_cm:clk:0118:8" पूर्ण,
	अणु OMAP4_UART1_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP4_UART2_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP4_UART3_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP4_UART4_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP4_MMC5_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा
omap_clkctrl_reg_data omap4_l4_secure_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_AES1_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_div_ck" पूर्ण,
	अणु OMAP4_AES2_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_div_ck" पूर्ण,
	अणु OMAP4_DES3DES_CLKCTRL, शून्य, CLKF_SW_SUP, "l4_div_ck" पूर्ण,
	अणु OMAP4_PKA_CLKCTRL, शून्य, CLKF_SW_SUP, "l4_div_ck" पूर्ण,
	अणु OMAP4_RNG_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_SOC_NONSEC, "l4_div_ck" पूर्ण,
	अणु OMAP4_SHA2MD5_CLKCTRL, शून्य, CLKF_SW_SUP, "l3_div_ck" पूर्ण,
	अणु OMAP4_CRYPTODMA_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_SOC_NONSEC, "l3_div_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_gpio1_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap4_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_समयr1_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap4_cm2_dm10_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_l4_wkup_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_L4_WKUP_CLKCTRL, शून्य, 0, "l4_wkup_clk_mux_ck" पूर्ण,
	अणु OMAP4_WD_TIMER2_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_32k_ck" पूर्ण,
	अणु OMAP4_GPIO1_CLKCTRL, omap4_gpio1_bit_data, CLKF_HW_SUP, "l4_wkup_clk_mux_ck" पूर्ण,
	अणु OMAP4_TIMER1_CLKCTRL, omap4_समयr1_bit_data, CLKF_SW_SUP, "l4_wkup_cm:clk:0020:24" पूर्ण,
	अणु OMAP4_COUNTER_32K_CLKCTRL, शून्य, 0, "sys_32k_ck" पूर्ण,
	अणु OMAP4_KBD_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_32k_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_pmd_sपंचांग_घड़ी_mux_ck_parents[] __initस्थिर = अणु
	"sys_clkin_ck",
	"dpll_core_m6x2_ck",
	"tie_low_clock_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_trace_clk_भाग_भाग_ck_parents[] __initस्थिर = अणु
	"emu_sys_cm:clk:0000:22",
	शून्य,
पूर्ण;

अटल स्थिर पूर्णांक omap4_trace_clk_भाग_भाग_ck_भागs[] __initस्थिर = अणु
	0,
	1,
	2,
	0,
	4,
	-1,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data omap4_trace_clk_भाग_भाग_ck_data __initस्थिर = अणु
	.भागiders = omap4_trace_clk_भाग_भाग_ck_भागs,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_sपंचांग_clk_भाग_ck_parents[] __initस्थिर = अणु
	"emu_sys_cm:clk:0000:20",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data omap4_sपंचांग_clk_भाग_ck_data __initस्थिर = अणु
	.max_भाग = 64,
	.flags = CLK_DIVIDER_POWER_OF_TWO,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap4_debugss_bit_data[] __initस्थिर = अणु
	अणु 20, TI_CLK_MUX, omap4_pmd_sपंचांग_घड़ी_mux_ck_parents, शून्य पूर्ण,
	अणु 22, TI_CLK_MUX, omap4_pmd_sपंचांग_घड़ी_mux_ck_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_DIVIDER, omap4_trace_clk_भाग_भाग_ck_parents, &omap4_trace_clk_भाग_भाग_ck_data पूर्ण,
	अणु 27, TI_CLK_DIVIDER, omap4_sपंचांग_clk_भाग_ck_parents, &omap4_sपंचांग_clk_भाग_ck_data पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap4_emu_sys_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP4_DEBUGSS_CLKCTRL, omap4_debugss_bit_data, 0, "trace_clk_div_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

स्थिर काष्ठा omap_clkctrl_data omap4_clkctrl_data[] __initस्थिर = अणु
	अणु 0x4a004320, omap4_mpuss_clkctrl_regs पूर्ण,
	अणु 0x4a004420, omap4_tesla_clkctrl_regs पूर्ण,
	अणु 0x4a004520, omap4_abe_clkctrl_regs पूर्ण,
	अणु 0x4a008620, omap4_l4_ao_clkctrl_regs पूर्ण,
	अणु 0x4a008720, omap4_l3_1_clkctrl_regs पूर्ण,
	अणु 0x4a008820, omap4_l3_2_clkctrl_regs पूर्ण,
	अणु 0x4a008920, omap4_ducati_clkctrl_regs पूर्ण,
	अणु 0x4a008a20, omap4_l3_dma_clkctrl_regs पूर्ण,
	अणु 0x4a008b20, omap4_l3_emअगर_clkctrl_regs पूर्ण,
	अणु 0x4a008c20, omap4_d2d_clkctrl_regs पूर्ण,
	अणु 0x4a008d20, omap4_l4_cfg_clkctrl_regs पूर्ण,
	अणु 0x4a008e20, omap4_l3_instr_clkctrl_regs पूर्ण,
	अणु 0x4a008f20, omap4_ivahd_clkctrl_regs पूर्ण,
	अणु 0x4a009020, omap4_iss_clkctrl_regs पूर्ण,
	अणु 0x4a009120, omap4_l3_dss_clkctrl_regs पूर्ण,
	अणु 0x4a009220, omap4_l3_gfx_clkctrl_regs पूर्ण,
	अणु 0x4a009320, omap4_l3_init_clkctrl_regs पूर्ण,
	अणु 0x4a009420, omap4_l4_per_clkctrl_regs पूर्ण,
	अणु 0x4a0095a0, omap4_l4_secure_clkctrl_regs पूर्ण,
	अणु 0x4a307820, omap4_l4_wkup_clkctrl_regs पूर्ण,
	अणु 0x4a307a20, omap4_emu_sys_clkctrl_regs पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा ti_dt_clk omap44xx_clks[] = अणु
	DT_CLK(शून्य, "timer_32k_ck", "sys_32k_ck"),
	/*
	 * XXX: All the घड़ी aliases below are only needed क्रम legacy
	 * hwmod support. Once hwmod is हटाओd, these can be हटाओd
	 * also.
	 */
	DT_CLK(शून्य, "aess_fclk", "abe_cm:0008:24"),
	DT_CLK(शून्य, "cm2_dm10_mux", "l4_per_cm:0008:24"),
	DT_CLK(शून्य, "cm2_dm11_mux", "l4_per_cm:0010:24"),
	DT_CLK(शून्य, "cm2_dm2_mux", "l4_per_cm:0018:24"),
	DT_CLK(शून्य, "cm2_dm3_mux", "l4_per_cm:0020:24"),
	DT_CLK(शून्य, "cm2_dm4_mux", "l4_per_cm:0028:24"),
	DT_CLK(शून्य, "cm2_dm9_mux", "l4_per_cm:0030:24"),
	DT_CLK(शून्य, "dmic_sync_mux_ck", "abe_cm:0018:26"),
	DT_CLK(शून्य, "dmt1_clk_mux", "l4_wkup_cm:0020:24"),
	DT_CLK(शून्य, "dss_48mhz_clk", "l3_dss_cm:0000:9"),
	DT_CLK(शून्य, "dss_dss_clk", "l3_dss_cm:0000:8"),
	DT_CLK(शून्य, "dss_sys_clk", "l3_dss_cm:0000:10"),
	DT_CLK(शून्य, "dss_tv_clk", "l3_dss_cm:0000:11"),
	DT_CLK(शून्य, "fdif_fck", "iss_cm:0008:24"),
	DT_CLK(शून्य, "func_dmic_abe_gfclk", "abe_cm:0018:24"),
	DT_CLK(शून्य, "func_mcasp_abe_gfclk", "abe_cm:0020:24"),
	DT_CLK(शून्य, "func_mcbsp1_gfclk", "abe_cm:0028:24"),
	DT_CLK(शून्य, "func_mcbsp2_gfclk", "abe_cm:0030:24"),
	DT_CLK(शून्य, "func_mcbsp3_gfclk", "abe_cm:0038:24"),
	DT_CLK(शून्य, "gpio1_dbclk", "l4_wkup_cm:0018:8"),
	DT_CLK(शून्य, "gpio2_dbclk", "l4_per_cm:0040:8"),
	DT_CLK(शून्य, "gpio3_dbclk", "l4_per_cm:0048:8"),
	DT_CLK(शून्य, "gpio4_dbclk", "l4_per_cm:0050:8"),
	DT_CLK(शून्य, "gpio5_dbclk", "l4_per_cm:0058:8"),
	DT_CLK(शून्य, "gpio6_dbclk", "l4_per_cm:0060:8"),
	DT_CLK(शून्य, "hsi_fck", "l3_init_cm:0018:24"),
	DT_CLK(शून्य, "hsmmc1_fclk", "l3_init_cm:0008:24"),
	DT_CLK(शून्य, "hsmmc2_fclk", "l3_init_cm:0010:24"),
	DT_CLK(शून्य, "iss_ctrlclk", "iss_cm:0000:8"),
	DT_CLK(शून्य, "mcasp_sync_mux_ck", "abe_cm:0020:26"),
	DT_CLK(शून्य, "mcbsp1_sync_mux_ck", "abe_cm:0028:26"),
	DT_CLK(शून्य, "mcbsp2_sync_mux_ck", "abe_cm:0030:26"),
	DT_CLK(शून्य, "mcbsp3_sync_mux_ck", "abe_cm:0038:26"),
	DT_CLK(शून्य, "mcbsp4_sync_mux_ck", "l4_per_cm:00c0:26"),
	DT_CLK(शून्य, "ocp2scp_usb_phy_phy_48m", "l3_init_cm:00c0:8"),
	DT_CLK(शून्य, "otg_60m_gfclk", "l3_init_cm:0040:24"),
	DT_CLK(शून्य, "per_mcbsp4_gfclk", "l4_per_cm:00c0:24"),
	DT_CLK(शून्य, "pmd_stm_clock_mux_ck", "emu_sys_cm:0000:20"),
	DT_CLK(शून्य, "pmd_trace_clk_mux_ck", "emu_sys_cm:0000:22"),
	DT_CLK(शून्य, "sgx_clk_mux", "l3_gfx_cm:0000:24"),
	DT_CLK(शून्य, "slimbus1_fclk_0", "abe_cm:0040:8"),
	DT_CLK(शून्य, "slimbus1_fclk_1", "abe_cm:0040:9"),
	DT_CLK(शून्य, "slimbus1_fclk_2", "abe_cm:0040:10"),
	DT_CLK(शून्य, "slimbus1_slimbus_clk", "abe_cm:0040:11"),
	DT_CLK(शून्य, "slimbus2_fclk_0", "l4_per_cm:0118:8"),
	DT_CLK(शून्य, "slimbus2_fclk_1", "l4_per_cm:0118:9"),
	DT_CLK(शून्य, "slimbus2_slimbus_clk", "l4_per_cm:0118:10"),
	DT_CLK(शून्य, "stm_clk_div_ck", "emu_sys_cm:0000:27"),
	DT_CLK(शून्य, "timer5_sync_mux", "abe_cm:0048:24"),
	DT_CLK(शून्य, "timer6_sync_mux", "abe_cm:0050:24"),
	DT_CLK(शून्य, "timer7_sync_mux", "abe_cm:0058:24"),
	DT_CLK(शून्य, "timer8_sync_mux", "abe_cm:0060:24"),
	DT_CLK(शून्य, "trace_clk_div_div_ck", "emu_sys_cm:0000:24"),
	DT_CLK(शून्य, "usb_host_hs_func48mclk", "l3_init_cm:0038:15"),
	DT_CLK(शून्य, "usb_host_hs_hsic480m_p1_clk", "l3_init_cm:0038:13"),
	DT_CLK(शून्य, "usb_host_hs_hsic480m_p2_clk", "l3_init_cm:0038:14"),
	DT_CLK(शून्य, "usb_host_hs_hsic60m_p1_clk", "l3_init_cm:0038:11"),
	DT_CLK(शून्य, "usb_host_hs_hsic60m_p2_clk", "l3_init_cm:0038:12"),
	DT_CLK(शून्य, "usb_host_hs_utmi_p1_clk", "l3_init_cm:0038:8"),
	DT_CLK(शून्य, "usb_host_hs_utmi_p2_clk", "l3_init_cm:0038:9"),
	DT_CLK(शून्य, "usb_host_hs_utmi_p3_clk", "l3_init_cm:0038:10"),
	DT_CLK(शून्य, "usb_otg_hs_xclk", "l3_init_cm:0040:8"),
	DT_CLK(शून्य, "usb_tll_hs_usb_ch0_clk", "l3_init_cm:0048:8"),
	DT_CLK(शून्य, "usb_tll_hs_usb_ch1_clk", "l3_init_cm:0048:9"),
	DT_CLK(शून्य, "usb_tll_hs_usb_ch2_clk", "l3_init_cm:0048:10"),
	DT_CLK(शून्य, "utmi_p1_gfclk", "l3_init_cm:0038:24"),
	DT_CLK(शून्य, "utmi_p2_gfclk", "l3_init_cm:0038:25"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

पूर्णांक __init omap4xxx_dt_clk_init(व्योम)
अणु
	पूर्णांक rc;
	काष्ठा clk *abe_dpll_ref, *abe_dpll, *sys_32k_ck, *usb_dpll;

	ti_dt_घड़ीs_रेजिस्टर(omap44xx_clks);

	omap2_clk_disable_स्वतःidle_all();

	ti_clk_add_aliases();

	/*
	 * Lock USB DPLL on OMAP4 devices so that the L3INIT घातer
	 * करोमुख्य can transition to retention state when not in use.
	 */
	usb_dpll = clk_get_sys(शून्य, "dpll_usb_ck");
	rc = clk_set_rate(usb_dpll, OMAP4_DPLL_USB_DEFFREQ);
	अगर (rc)
		pr_err("%s: failed to configure USB DPLL!\n", __func__);

	/*
	 * On OMAP4460 the ABE DPLL fails to turn on अगर in idle low-घातer
	 * state when turning the ABE घड़ी करोमुख्य. Workaround this by
	 * locking the ABE DPLL on boot.
	 * Lock the ABE DPLL in any हाल to aव्योम issues with audio.
	 */
	abe_dpll_ref = clk_get_sys(शून्य, "abe_dpll_refclk_mux_ck");
	sys_32k_ck = clk_get_sys(शून्य, "sys_32k_ck");
	rc = clk_set_parent(abe_dpll_ref, sys_32k_ck);
	abe_dpll = clk_get_sys(शून्य, "dpll_abe_ck");
	अगर (!rc)
		rc = clk_set_rate(abe_dpll, OMAP4_DPLL_ABE_DEFFREQ);
	अगर (rc)
		pr_err("%s: failed to configure ABE DPLL!\n", __func__);

	वापस 0;
पूर्ण
