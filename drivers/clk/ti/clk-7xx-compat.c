<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DRA7 Clock init
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
#समावेश <dt-bindings/घड़ी/dra7.h>

#समावेश "clock.h"

#घोषणा DRA7_DPLL_GMAC_DEFFREQ				1000000000
#घोषणा DRA7_DPLL_USB_DEFFREQ				960000000

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_mpu_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_MPU_CLKCTRL, शून्य, 0, "dpll_mpu_m2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_mcasp1_aux_gfclk_mux_parents[] __initस्थिर = अणु
	"per_abe_x1_gfclk2_div",
	"video1_clk2_div",
	"video2_clk2_div",
	"hdmi_clk2_div",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_mcasp1_ahclkx_mux_parents[] __initस्थिर = अणु
	"abe_24m_fclk",
	"abe_sys_clk_div",
	"func_24m_clk",
	"atl_clkin3_ck",
	"atl_clkin2_ck",
	"atl_clkin1_ck",
	"atl_clkin0_ck",
	"sys_clkin2",
	"ref_clkin0_ck",
	"ref_clkin1_ck",
	"ref_clkin2_ck",
	"ref_clkin3_ck",
	"mlb_clk",
	"mlbp_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_mcasp1_bit_data[] __initस्थिर = अणु
	अणु 22, TI_CLK_MUX, dra7_mcasp1_aux_gfclk_mux_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, dra7_mcasp1_ahclkx_mux_parents, शून्य पूर्ण,
	अणु 28, TI_CLK_MUX, dra7_mcasp1_ahclkx_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_समयr5_gfclk_mux_parents[] __initस्थिर = अणु
	"timer_sys_clk_div",
	"sys_32k_ck",
	"sys_clkin2",
	"ref_clkin0_ck",
	"ref_clkin1_ck",
	"ref_clkin2_ck",
	"ref_clkin3_ck",
	"abe_giclk_div",
	"video1_div_clk",
	"video2_div_clk",
	"hdmi_div_clk",
	"clkoutmux0_clk_mux",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr5_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr5_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr6_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr5_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr7_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr5_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr8_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr5_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_uart6_gfclk_mux_parents[] __initस्थिर = अणु
	"func_48m_fclk",
	"dpll_per_m2x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_uart6_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_uart6_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_ipu_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_MCASP1_CLKCTRL, dra7_mcasp1_bit_data, CLKF_SW_SUP, "ipu_cm:clk:0010:22" पूर्ण,
	अणु DRA7_TIMER5_CLKCTRL, dra7_समयr5_bit_data, CLKF_SW_SUP, "ipu_cm:clk:0018:24" पूर्ण,
	अणु DRA7_TIMER6_CLKCTRL, dra7_समयr6_bit_data, CLKF_SW_SUP, "ipu_cm:clk:0020:24" पूर्ण,
	अणु DRA7_TIMER7_CLKCTRL, dra7_समयr7_bit_data, CLKF_SW_SUP, "ipu_cm:clk:0028:24" पूर्ण,
	अणु DRA7_TIMER8_CLKCTRL, dra7_समयr8_bit_data, CLKF_SW_SUP, "ipu_cm:clk:0030:24" पूर्ण,
	अणु DRA7_I2C5_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु DRA7_UART6_CLKCTRL, dra7_uart6_bit_data, CLKF_SW_SUP, "ipu_cm:clk:0040:24" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_rtc_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_RTCSS_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_32k_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_coreaon_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_SMARTREFLEX_MPU_CLKCTRL, शून्य, CLKF_SW_SUP, "wkupaon_iclk_mux" पूर्ण,
	अणु DRA7_SMARTREFLEX_CORE_CLKCTRL, शून्य, CLKF_SW_SUP, "wkupaon_iclk_mux" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_l3मुख्य1_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_L3_MAIN_1_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_GPMC_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_TPCC_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_TPTC0_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_TPTC1_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_VCP1_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_VCP2_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_dma_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_DMA_SYSTEM_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_emअगर_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_DMM_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_atl_dpll_clk_mux_parents[] __initस्थिर = अणु
	"sys_32k_ck",
	"video1_clkin_ck",
	"video2_clkin_ck",
	"hdmi_clkin_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_atl_gfclk_mux_parents[] __initस्थिर = अणु
	"l3_iclk_div",
	"dpll_abe_m2_ck",
	"atl_cm:clk:0000:24",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_atl_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_atl_dpll_clk_mux_parents, शून्य पूर्ण,
	अणु 26, TI_CLK_MUX, dra7_atl_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_atl_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_ATL_CLKCTRL, dra7_atl_bit_data, CLKF_SW_SUP, "atl_cm:clk:0000:26" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_l4cfg_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_L4_CFG_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_SPINLOCK_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_MAILBOX1_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_MAILBOX2_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_MAILBOX3_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_MAILBOX4_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_MAILBOX5_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_MAILBOX6_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_MAILBOX7_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_MAILBOX8_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_MAILBOX9_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_MAILBOX10_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_MAILBOX11_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_MAILBOX12_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_MAILBOX13_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_l3instr_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_L3_MAIN_2_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L3_INSTR_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_dss_dss_clk_parents[] __initस्थिर = अणु
	"dpll_per_h12x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_dss_48mhz_clk_parents[] __initस्थिर = अणु
	"func_48m_fclk",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_dss_hdmi_clk_parents[] __initस्थिर = अणु
	"hdmi_dpll_clk_mux",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_dss_32khz_clk_parents[] __initस्थिर = अणु
	"sys_32k_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_dss_video1_clk_parents[] __initस्थिर = अणु
	"video1_dpll_clk_mux",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_dss_video2_clk_parents[] __initस्थिर = अणु
	"video2_dpll_clk_mux",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_dss_core_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_dss_clk_parents, शून्य पूर्ण,
	अणु 9, TI_CLK_GATE, dra7_dss_48mhz_clk_parents, शून्य पूर्ण,
	अणु 10, TI_CLK_GATE, dra7_dss_hdmi_clk_parents, शून्य पूर्ण,
	अणु 11, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 12, TI_CLK_GATE, dra7_dss_video1_clk_parents, शून्य पूर्ण,
	अणु 13, TI_CLK_GATE, dra7_dss_video2_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_dss_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_DSS_CORE_CLKCTRL, dra7_dss_core_bit_data, CLKF_SW_SUP, "dss_cm:clk:0000:8" पूर्ण,
	अणु DRA7_BB2D_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_core_h24x2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_mmc1_fclk_mux_parents[] __initस्थिर = अणु
	"func_128m_clk",
	"dpll_per_m2x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_mmc1_fclk_भाग_parents[] __initस्थिर = अणु
	"l3init_cm:clk:0008:24",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data dra7_mmc1_fclk_भाग_data __initस्थिर = अणु
	.max_भाग = 4,
	.flags = CLK_DIVIDER_POWER_OF_TWO,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_mmc1_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, dra7_mmc1_fclk_mux_parents, शून्य पूर्ण,
	अणु 25, TI_CLK_DIVIDER, dra7_mmc1_fclk_भाग_parents, &dra7_mmc1_fclk_भाग_data पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_mmc2_fclk_भाग_parents[] __initस्थिर = अणु
	"l3init_cm:clk:0010:24",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data dra7_mmc2_fclk_भाग_data __initस्थिर = अणु
	.max_भाग = 4,
	.flags = CLK_DIVIDER_POWER_OF_TWO,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_mmc2_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, dra7_mmc1_fclk_mux_parents, शून्य पूर्ण,
	अणु 25, TI_CLK_DIVIDER, dra7_mmc2_fclk_भाग_parents, &dra7_mmc2_fclk_भाग_data पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_usb_otg_ss2_refclk960m_parents[] __initस्थिर = अणु
	"l3init_960m_gfclk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_usb_otg_ss2_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_usb_otg_ss2_refclk960m_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_sata_ref_clk_parents[] __initस्थिर = अणु
	"sys_clkin1",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_sata_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_sata_ref_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_optfclk_pciephy1_clk_parents[] __initस्थिर = अणु
	"apll_pcie_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_optfclk_pciephy1_भाग_clk_parents[] __initस्थिर = अणु
	"optfclk_pciephy_div",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_pcie1_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 9, TI_CLK_GATE, dra7_optfclk_pciephy1_clk_parents, शून्य पूर्ण,
	अणु 10, TI_CLK_GATE, dra7_optfclk_pciephy1_भाग_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_pcie2_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 9, TI_CLK_GATE, dra7_optfclk_pciephy1_clk_parents, शून्य पूर्ण,
	अणु 10, TI_CLK_GATE, dra7_optfclk_pciephy1_भाग_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_rmii_50mhz_clk_mux_parents[] __initस्थिर = अणु
	"dpll_gmac_h11x2_ck",
	"rmii_clk_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_gmac_rft_clk_mux_parents[] __initस्थिर = अणु
	"video1_clkin_ck",
	"video2_clkin_ck",
	"dpll_abe_m2_ck",
	"hdmi_clkin_ck",
	"l3_iclk_div",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_gmac_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_rmii_50mhz_clk_mux_parents, शून्य पूर्ण,
	अणु 25, TI_CLK_MUX, dra7_gmac_rft_clk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_usb_otg_ss1_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_usb_otg_ss2_refclk960m_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_l3init_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_MMC1_CLKCTRL, dra7_mmc1_bit_data, CLKF_SW_SUP, "l3init_cm:clk:0008:25" पूर्ण,
	अणु DRA7_MMC2_CLKCTRL, dra7_mmc2_bit_data, CLKF_SW_SUP, "l3init_cm:clk:0010:25" पूर्ण,
	अणु DRA7_USB_OTG_SS2_CLKCTRL, dra7_usb_otg_ss2_bit_data, CLKF_HW_SUP, "dpll_core_h13x2_ck" पूर्ण,
	अणु DRA7_USB_OTG_SS3_CLKCTRL, शून्य, CLKF_HW_SUP, "dpll_core_h13x2_ck" पूर्ण,
	अणु DRA7_USB_OTG_SS4_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_SOC_DRA74 | CLKF_SOC_DRA76, "dpll_core_h13x2_ck" पूर्ण,
	अणु DRA7_SATA_CLKCTRL, dra7_sata_bit_data, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु DRA7_PCIE1_CLKCTRL, dra7_pcie1_bit_data, CLKF_SW_SUP, "l4_root_clk_div", "pcie_clkdm" पूर्ण,
	अणु DRA7_PCIE2_CLKCTRL, dra7_pcie2_bit_data, CLKF_SW_SUP, "l4_root_clk_div", "pcie_clkdm" पूर्ण,
	अणु DRA7_GMAC_CLKCTRL, dra7_gmac_bit_data, CLKF_SW_SUP, "dpll_gmac_ck", "gmac_clkdm" पूर्ण,
	अणु DRA7_OCP2SCP1_CLKCTRL, शून्य, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु DRA7_OCP2SCP3_CLKCTRL, शून्य, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु DRA7_USB_OTG_SS1_CLKCTRL, dra7_usb_otg_ss1_bit_data, CLKF_HW_SUP, "dpll_core_h13x2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_समयr10_gfclk_mux_parents[] __initस्थिर = अणु
	"timer_sys_clk_div",
	"sys_32k_ck",
	"sys_clkin2",
	"ref_clkin0_ck",
	"ref_clkin1_ck",
	"ref_clkin2_ck",
	"ref_clkin3_ck",
	"abe_giclk_div",
	"video1_div_clk",
	"video2_div_clk",
	"hdmi_div_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr10_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr11_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr2_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr3_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr4_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr9_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_gpio2_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_gpio3_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_gpio4_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_gpio5_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_gpio6_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr13_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr14_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr15_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_gpio7_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_gpio8_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_mmc3_gfclk_भाग_parents[] __initस्थिर = अणु
	"l4per_cm:clk:0120:24",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data dra7_mmc3_gfclk_भाग_data __initस्थिर = अणु
	.max_भाग = 4,
	.flags = CLK_DIVIDER_POWER_OF_TWO,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_mmc3_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, dra7_uart6_gfclk_mux_parents, शून्य पूर्ण,
	अणु 25, TI_CLK_DIVIDER, dra7_mmc3_gfclk_भाग_parents, &dra7_mmc3_gfclk_भाग_data पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_mmc4_gfclk_भाग_parents[] __initस्थिर = अणु
	"l4per_cm:clk:0128:24",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data dra7_mmc4_gfclk_भाग_data __initस्थिर = अणु
	.max_भाग = 4,
	.flags = CLK_DIVIDER_POWER_OF_TWO,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_mmc4_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, dra7_uart6_gfclk_mux_parents, शून्य पूर्ण,
	अणु 25, TI_CLK_DIVIDER, dra7_mmc4_gfclk_भाग_parents, &dra7_mmc4_gfclk_भाग_data पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr16_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_qspi_gfclk_mux_parents[] __initस्थिर = अणु
	"func_128m_clk",
	"dpll_per_h13x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_qspi_gfclk_भाग_parents[] __initस्थिर = अणु
	"l4per_cm:clk:0138:24",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data dra7_qspi_gfclk_भाग_data __initस्थिर = अणु
	.max_भाग = 4,
	.flags = CLK_DIVIDER_POWER_OF_TWO,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_qspi_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_qspi_gfclk_mux_parents, शून्य पूर्ण,
	अणु 25, TI_CLK_DIVIDER, dra7_qspi_gfclk_भाग_parents, &dra7_qspi_gfclk_भाग_data पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_uart1_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_uart6_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_uart2_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_uart6_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_uart3_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_uart6_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_uart4_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_uart6_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_mcasp2_bit_data[] __initस्थिर = अणु
	अणु 22, TI_CLK_MUX, dra7_mcasp1_aux_gfclk_mux_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, dra7_mcasp1_ahclkx_mux_parents, शून्य पूर्ण,
	अणु 28, TI_CLK_MUX, dra7_mcasp1_ahclkx_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_mcasp3_bit_data[] __initस्थिर = अणु
	अणु 22, TI_CLK_MUX, dra7_mcasp1_aux_gfclk_mux_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, dra7_mcasp1_ahclkx_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_uart5_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_uart6_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_mcasp5_bit_data[] __initस्थिर = अणु
	अणु 22, TI_CLK_MUX, dra7_mcasp1_aux_gfclk_mux_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, dra7_mcasp1_ahclkx_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_mcasp8_bit_data[] __initस्थिर = अणु
	अणु 22, TI_CLK_MUX, dra7_mcasp1_aux_gfclk_mux_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, dra7_mcasp1_ahclkx_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_mcasp4_bit_data[] __initस्थिर = अणु
	अणु 22, TI_CLK_MUX, dra7_mcasp1_aux_gfclk_mux_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, dra7_mcasp1_ahclkx_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_uart7_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_uart6_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_uart8_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_uart6_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_uart9_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_uart6_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_mcasp6_bit_data[] __initस्थिर = अणु
	अणु 22, TI_CLK_MUX, dra7_mcasp1_aux_gfclk_mux_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, dra7_mcasp1_ahclkx_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_mcasp7_bit_data[] __initस्थिर = अणु
	अणु 22, TI_CLK_MUX, dra7_mcasp1_aux_gfclk_mux_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, dra7_mcasp1_ahclkx_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_l4per_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_L4_PER2_CLKCTRL, शून्य, 0, "l3_iclk_div", "l4per2_clkdm" पूर्ण,
	अणु DRA7_L4_PER3_CLKCTRL, शून्य, 0, "l3_iclk_div", "l4per3_clkdm" पूर्ण,
	अणु DRA7_TIMER10_CLKCTRL, dra7_समयr10_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0028:24" पूर्ण,
	अणु DRA7_TIMER11_CLKCTRL, dra7_समयr11_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0030:24" पूर्ण,
	अणु DRA7_TIMER2_CLKCTRL, dra7_समयr2_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0038:24" पूर्ण,
	अणु DRA7_TIMER3_CLKCTRL, dra7_समयr3_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0040:24" पूर्ण,
	अणु DRA7_TIMER4_CLKCTRL, dra7_समयr4_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0048:24" पूर्ण,
	अणु DRA7_TIMER9_CLKCTRL, dra7_समयr9_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0050:24" पूर्ण,
	अणु DRA7_ELM_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_GPIO2_CLKCTRL, dra7_gpio2_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_GPIO3_CLKCTRL, dra7_gpio3_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_GPIO4_CLKCTRL, dra7_gpio4_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_GPIO5_CLKCTRL, dra7_gpio5_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_GPIO6_CLKCTRL, dra7_gpio6_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_HDQ1W_CLKCTRL, शून्य, CLKF_SW_SUP, "func_12m_fclk" पूर्ण,
	अणु DRA7_EPWMSS1_CLKCTRL, शून्य, CLKF_SW_SUP, "l4_root_clk_div", "l4per2_clkdm" पूर्ण,
	अणु DRA7_EPWMSS2_CLKCTRL, शून्य, CLKF_SW_SUP, "l4_root_clk_div", "l4per2_clkdm" पूर्ण,
	अणु DRA7_I2C1_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु DRA7_I2C2_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु DRA7_I2C3_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु DRA7_I2C4_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु DRA7_L4_PER1_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_EPWMSS0_CLKCTRL, शून्य, CLKF_SW_SUP, "l4_root_clk_div", "l4per2_clkdm" पूर्ण,
	अणु DRA7_TIMER13_CLKCTRL, dra7_समयr13_bit_data, CLKF_SW_SUP, "l4per_cm:clk:00c8:24", "l4per3_clkdm" पूर्ण,
	अणु DRA7_TIMER14_CLKCTRL, dra7_समयr14_bit_data, CLKF_SW_SUP, "l4per_cm:clk:00d0:24", "l4per3_clkdm" पूर्ण,
	अणु DRA7_TIMER15_CLKCTRL, dra7_समयr15_bit_data, CLKF_SW_SUP, "l4per_cm:clk:00d8:24", "l4per3_clkdm" पूर्ण,
	अणु DRA7_MCSPI1_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु DRA7_MCSPI2_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु DRA7_MCSPI3_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु DRA7_MCSPI4_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु DRA7_GPIO7_CLKCTRL, dra7_gpio7_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_GPIO8_CLKCTRL, dra7_gpio8_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_MMC3_CLKCTRL, dra7_mmc3_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0120:25" पूर्ण,
	अणु DRA7_MMC4_CLKCTRL, dra7_mmc4_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0128:25" पूर्ण,
	अणु DRA7_TIMER16_CLKCTRL, dra7_समयr16_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0130:24", "l4per3_clkdm" पूर्ण,
	अणु DRA7_QSPI_CLKCTRL, dra7_qspi_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0138:25", "l4per2_clkdm" पूर्ण,
	अणु DRA7_UART1_CLKCTRL, dra7_uart1_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0140:24" पूर्ण,
	अणु DRA7_UART2_CLKCTRL, dra7_uart2_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0148:24" पूर्ण,
	अणु DRA7_UART3_CLKCTRL, dra7_uart3_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0150:24" पूर्ण,
	अणु DRA7_UART4_CLKCTRL, dra7_uart4_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0158:24" पूर्ण,
	अणु DRA7_MCASP2_CLKCTRL, dra7_mcasp2_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0160:22", "l4per2_clkdm" पूर्ण,
	अणु DRA7_MCASP3_CLKCTRL, dra7_mcasp3_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0168:22", "l4per2_clkdm" पूर्ण,
	अणु DRA7_UART5_CLKCTRL, dra7_uart5_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0170:24" पूर्ण,
	अणु DRA7_MCASP5_CLKCTRL, dra7_mcasp5_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0178:22", "l4per2_clkdm" पूर्ण,
	अणु DRA7_MCASP8_CLKCTRL, dra7_mcasp8_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0190:24", "l4per2_clkdm" पूर्ण,
	अणु DRA7_MCASP4_CLKCTRL, dra7_mcasp4_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0198:22", "l4per2_clkdm" पूर्ण,
	अणु DRA7_AES1_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div", "l4sec_clkdm" पूर्ण,
	अणु DRA7_AES2_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div", "l4sec_clkdm" पूर्ण,
	अणु DRA7_DES_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div", "l4sec_clkdm" पूर्ण,
	अणु DRA7_RNG_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_SOC_NONSEC, "l3_iclk_div", "l4sec_clkdm" पूर्ण,
	अणु DRA7_SHAM_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div", "l4sec_clkdm" पूर्ण,
	अणु DRA7_UART7_CLKCTRL, dra7_uart7_bit_data, CLKF_SW_SUP, "l4per_cm:clk:01d0:24", "l4per2_clkdm" पूर्ण,
	अणु DRA7_UART8_CLKCTRL, dra7_uart8_bit_data, CLKF_SW_SUP, "l4per_cm:clk:01e0:24", "l4per2_clkdm" पूर्ण,
	अणु DRA7_UART9_CLKCTRL, dra7_uart9_bit_data, CLKF_SW_SUP, "l4per_cm:clk:01e8:24", "l4per2_clkdm" पूर्ण,
	अणु DRA7_DCAN2_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_clkin1", "l4per2_clkdm" पूर्ण,
	अणु DRA7_MCASP6_CLKCTRL, dra7_mcasp6_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0204:22", "l4per2_clkdm" पूर्ण,
	अणु DRA7_MCASP7_CLKCTRL, dra7_mcasp7_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0208:22", "l4per2_clkdm" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_gpio1_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr1_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_uart10_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_uart6_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_dcan1_sys_clk_mux_parents[] __initस्थिर = अणु
	"sys_clkin1",
	"sys_clkin2",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_dcan1_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_dcan1_sys_clk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_wkupaon_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_L4_WKUP_CLKCTRL, शून्य, 0, "wkupaon_iclk_mux" पूर्ण,
	अणु DRA7_WD_TIMER2_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_32k_ck" पूर्ण,
	अणु DRA7_GPIO1_CLKCTRL, dra7_gpio1_bit_data, CLKF_HW_SUP, "wkupaon_iclk_mux" पूर्ण,
	अणु DRA7_TIMER1_CLKCTRL, dra7_समयr1_bit_data, CLKF_SW_SUP, "wkupaon_cm:clk:0020:24" पूर्ण,
	अणु DRA7_TIMER12_CLKCTRL, शून्य, CLKF_SOC_NONSEC, "secure_32k_clk_src_ck" पूर्ण,
	अणु DRA7_COUNTER_32K_CLKCTRL, शून्य, 0, "wkupaon_iclk_mux" पूर्ण,
	अणु DRA7_UART10_CLKCTRL, dra7_uart10_bit_data, CLKF_SW_SUP, "wkupaon_cm:clk:0060:24" पूर्ण,
	अणु DRA7_DCAN1_CLKCTRL, dra7_dcan1_bit_data, CLKF_SW_SUP, "wkupaon_cm:clk:0068:24" पूर्ण,
	अणु DRA7_ADC_CLKCTRL, शून्य, CLKF_SW_SUP, "mcan_clk"पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

स्थिर काष्ठा omap_clkctrl_data dra7_clkctrl_compat_data[] __initस्थिर = अणु
	अणु 0x4a005320, dra7_mpu_clkctrl_regs पूर्ण,
	अणु 0x4a005540, dra7_ipu_clkctrl_regs पूर्ण,
	अणु 0x4a005740, dra7_rtc_clkctrl_regs पूर्ण,
	अणु 0x4a008620, dra7_coreaon_clkctrl_regs पूर्ण,
	अणु 0x4a008720, dra7_l3मुख्य1_clkctrl_regs पूर्ण,
	अणु 0x4a008a20, dra7_dma_clkctrl_regs पूर्ण,
	अणु 0x4a008b20, dra7_emअगर_clkctrl_regs पूर्ण,
	अणु 0x4a008c00, dra7_atl_clkctrl_regs पूर्ण,
	अणु 0x4a008d20, dra7_l4cfg_clkctrl_regs पूर्ण,
	अणु 0x4a008e20, dra7_l3instr_clkctrl_regs पूर्ण,
	अणु 0x4a009120, dra7_dss_clkctrl_regs पूर्ण,
	अणु 0x4a009320, dra7_l3init_clkctrl_regs पूर्ण,
	अणु 0x4a009700, dra7_l4per_clkctrl_regs पूर्ण,
	अणु 0x4ae07820, dra7_wkupaon_clkctrl_regs पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

काष्ठा ti_dt_clk dra7xx_compat_clks[] = अणु
	DT_CLK(शून्य, "timer_32k_ck", "sys_32k_ck"),
	DT_CLK(शून्य, "sys_clkin_ck", "timer_sys_clk_div"),
	DT_CLK(शून्य, "sys_clkin", "sys_clkin1"),
	DT_CLK(शून्य, "atl_dpll_clk_mux", "atl_cm:0000:24"),
	DT_CLK(शून्य, "atl_gfclk_mux", "atl_cm:0000:26"),
	DT_CLK(शून्य, "dcan1_sys_clk_mux", "wkupaon_cm:0068:24"),
	DT_CLK(शून्य, "dss_32khz_clk", "dss_cm:0000:11"),
	DT_CLK(शून्य, "dss_48mhz_clk", "dss_cm:0000:9"),
	DT_CLK(शून्य, "dss_dss_clk", "dss_cm:0000:8"),
	DT_CLK(शून्य, "dss_hdmi_clk", "dss_cm:0000:10"),
	DT_CLK(शून्य, "dss_video1_clk", "dss_cm:0000:12"),
	DT_CLK(शून्य, "dss_video2_clk", "dss_cm:0000:13"),
	DT_CLK(शून्य, "gmac_rft_clk_mux", "l3init_cm:00b0:25"),
	DT_CLK(शून्य, "gpio1_dbclk", "wkupaon_cm:0018:8"),
	DT_CLK(शून्य, "gpio2_dbclk", "l4per_cm:0060:8"),
	DT_CLK(शून्य, "gpio3_dbclk", "l4per_cm:0068:8"),
	DT_CLK(शून्य, "gpio4_dbclk", "l4per_cm:0070:8"),
	DT_CLK(शून्य, "gpio5_dbclk", "l4per_cm:0078:8"),
	DT_CLK(शून्य, "gpio6_dbclk", "l4per_cm:0080:8"),
	DT_CLK(शून्य, "gpio7_dbclk", "l4per_cm:0110:8"),
	DT_CLK(शून्य, "gpio8_dbclk", "l4per_cm:0118:8"),
	DT_CLK(शून्य, "mcasp1_ahclkr_mux", "ipu_cm:0010:28"),
	DT_CLK(शून्य, "mcasp1_ahclkx_mux", "ipu_cm:0010:24"),
	DT_CLK(शून्य, "mcasp1_aux_gfclk_mux", "ipu_cm:0010:22"),
	DT_CLK(शून्य, "mcasp2_ahclkr_mux", "l4per_cm:0160:28"),
	DT_CLK(शून्य, "mcasp2_ahclkx_mux", "l4per_cm:0160:24"),
	DT_CLK(शून्य, "mcasp2_aux_gfclk_mux", "l4per_cm:0160:22"),
	DT_CLK(शून्य, "mcasp3_ahclkx_mux", "l4per_cm:0168:24"),
	DT_CLK(शून्य, "mcasp3_aux_gfclk_mux", "l4per_cm:0168:22"),
	DT_CLK(शून्य, "mcasp4_ahclkx_mux", "l4per_cm:0198:24"),
	DT_CLK(शून्य, "mcasp4_aux_gfclk_mux", "l4per_cm:0198:22"),
	DT_CLK(शून्य, "mcasp5_ahclkx_mux", "l4per_cm:0178:24"),
	DT_CLK(शून्य, "mcasp5_aux_gfclk_mux", "l4per_cm:0178:22"),
	DT_CLK(शून्य, "mcasp6_ahclkx_mux", "l4per_cm:0204:24"),
	DT_CLK(शून्य, "mcasp6_aux_gfclk_mux", "l4per_cm:0204:22"),
	DT_CLK(शून्य, "mcasp7_ahclkx_mux", "l4per_cm:0208:24"),
	DT_CLK(शून्य, "mcasp7_aux_gfclk_mux", "l4per_cm:0208:22"),
	DT_CLK(शून्य, "mcasp8_ahclkx_mux", "l4per_cm:0190:22"),
	DT_CLK(शून्य, "mcasp8_aux_gfclk_mux", "l4per_cm:0190:24"),
	DT_CLK(शून्य, "mmc1_clk32k", "l3init_cm:0008:8"),
	DT_CLK(शून्य, "mmc1_fclk_div", "l3init_cm:0008:25"),
	DT_CLK(शून्य, "mmc1_fclk_mux", "l3init_cm:0008:24"),
	DT_CLK(शून्य, "mmc2_clk32k", "l3init_cm:0010:8"),
	DT_CLK(शून्य, "mmc2_fclk_div", "l3init_cm:0010:25"),
	DT_CLK(शून्य, "mmc2_fclk_mux", "l3init_cm:0010:24"),
	DT_CLK(शून्य, "mmc3_clk32k", "l4per_cm:0120:8"),
	DT_CLK(शून्य, "mmc3_gfclk_div", "l4per_cm:0120:25"),
	DT_CLK(शून्य, "mmc3_gfclk_mux", "l4per_cm:0120:24"),
	DT_CLK(शून्य, "mmc4_clk32k", "l4per_cm:0128:8"),
	DT_CLK(शून्य, "mmc4_gfclk_div", "l4per_cm:0128:25"),
	DT_CLK(शून्य, "mmc4_gfclk_mux", "l4per_cm:0128:24"),
	DT_CLK(शून्य, "optfclk_pciephy1_32khz", "l3init_cm:0090:8"),
	DT_CLK(शून्य, "optfclk_pciephy1_clk", "l3init_cm:0090:9"),
	DT_CLK(शून्य, "optfclk_pciephy1_div_clk", "l3init_cm:0090:10"),
	DT_CLK(शून्य, "optfclk_pciephy2_32khz", "l3init_cm:0098:8"),
	DT_CLK(शून्य, "optfclk_pciephy2_clk", "l3init_cm:0098:9"),
	DT_CLK(शून्य, "optfclk_pciephy2_div_clk", "l3init_cm:0098:10"),
	DT_CLK(शून्य, "qspi_gfclk_div", "l4per_cm:0138:25"),
	DT_CLK(शून्य, "qspi_gfclk_mux", "l4per_cm:0138:24"),
	DT_CLK(शून्य, "rmii_50mhz_clk_mux", "l3init_cm:00b0:24"),
	DT_CLK(शून्य, "sata_ref_clk", "l3init_cm:0068:8"),
	DT_CLK(शून्य, "timer10_gfclk_mux", "l4per_cm:0028:24"),
	DT_CLK(शून्य, "timer11_gfclk_mux", "l4per_cm:0030:24"),
	DT_CLK(शून्य, "timer13_gfclk_mux", "l4per_cm:00c8:24"),
	DT_CLK(शून्य, "timer14_gfclk_mux", "l4per_cm:00d0:24"),
	DT_CLK(शून्य, "timer15_gfclk_mux", "l4per_cm:00d8:24"),
	DT_CLK(शून्य, "timer16_gfclk_mux", "l4per_cm:0130:24"),
	DT_CLK(शून्य, "timer1_gfclk_mux", "wkupaon_cm:0020:24"),
	DT_CLK(शून्य, "timer2_gfclk_mux", "l4per_cm:0038:24"),
	DT_CLK(शून्य, "timer3_gfclk_mux", "l4per_cm:0040:24"),
	DT_CLK(शून्य, "timer4_gfclk_mux", "l4per_cm:0048:24"),
	DT_CLK(शून्य, "timer5_gfclk_mux", "ipu_cm:0018:24"),
	DT_CLK(शून्य, "timer6_gfclk_mux", "ipu_cm:0020:24"),
	DT_CLK(शून्य, "timer7_gfclk_mux", "ipu_cm:0028:24"),
	DT_CLK(शून्य, "timer8_gfclk_mux", "ipu_cm:0030:24"),
	DT_CLK(शून्य, "timer9_gfclk_mux", "l4per_cm:0050:24"),
	DT_CLK(शून्य, "uart10_gfclk_mux", "wkupaon_cm:0060:24"),
	DT_CLK(शून्य, "uart1_gfclk_mux", "l4per_cm:0140:24"),
	DT_CLK(शून्य, "uart2_gfclk_mux", "l4per_cm:0148:24"),
	DT_CLK(शून्य, "uart3_gfclk_mux", "l4per_cm:0150:24"),
	DT_CLK(शून्य, "uart4_gfclk_mux", "l4per_cm:0158:24"),
	DT_CLK(शून्य, "uart5_gfclk_mux", "l4per_cm:0170:24"),
	DT_CLK(शून्य, "uart6_gfclk_mux", "ipu_cm:0040:24"),
	DT_CLK(शून्य, "uart7_gfclk_mux", "l4per_cm:01d0:24"),
	DT_CLK(शून्य, "uart8_gfclk_mux", "l4per_cm:01e0:24"),
	DT_CLK(शून्य, "uart9_gfclk_mux", "l4per_cm:01e8:24"),
	DT_CLK(शून्य, "usb_otg_ss1_refclk960m", "l3init_cm:00d0:8"),
	DT_CLK(शून्य, "usb_otg_ss2_refclk960m", "l3init_cm:0020:8"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;
