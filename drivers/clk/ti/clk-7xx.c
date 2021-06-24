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
	अणु DRA7_MPU_MPU_CLKCTRL, शून्य, 0, "dpll_mpu_m2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_dsp1_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_DSP1_MMU0_DSP1_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_NO_IDLEST, "dpll_dsp_m2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_ipu1_gfclk_mux_parents[] __initस्थिर = अणु
	"dpll_abe_m2x2_ck",
	"dpll_core_h22x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_mmu_ipu1_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_ipu1_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_ipu1_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_IPU1_MMU_IPU1_CLKCTRL, dra7_mmu_ipu1_bit_data, CLKF_HW_SUP | CLKF_NO_IDLEST, "ipu1-clkctrl:0000:24" पूर्ण,
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
	अणु DRA7_IPU_MCASP1_CLKCTRL, dra7_mcasp1_bit_data, CLKF_SW_SUP, "ipu-clkctrl:0000:22" पूर्ण,
	अणु DRA7_IPU_TIMER5_CLKCTRL, dra7_समयr5_bit_data, CLKF_SW_SUP, "ipu-clkctrl:0008:24" पूर्ण,
	अणु DRA7_IPU_TIMER6_CLKCTRL, dra7_समयr6_bit_data, CLKF_SW_SUP, "ipu-clkctrl:0010:24" पूर्ण,
	अणु DRA7_IPU_TIMER7_CLKCTRL, dra7_समयr7_bit_data, CLKF_SW_SUP, "ipu-clkctrl:0018:24" पूर्ण,
	अणु DRA7_IPU_TIMER8_CLKCTRL, dra7_समयr8_bit_data, CLKF_SW_SUP, "ipu-clkctrl:0020:24" पूर्ण,
	अणु DRA7_IPU_I2C5_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु DRA7_IPU_UART6_CLKCTRL, dra7_uart6_bit_data, CLKF_SW_SUP, "ipu-clkctrl:0030:24" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_dsp2_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_DSP2_MMU0_DSP2_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_NO_IDLEST, "dpll_dsp_m2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_rtc_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_RTC_RTCSS_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_32k_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_cam_gfclk_mux_parents[] __initस्थिर = अणु
	"l3_iclk_div",
	"core_iss_main_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_cam_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_cam_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_cam_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_CAM_VIP1_CLKCTRL, dra7_cam_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_CAM_VIP2_CLKCTRL, dra7_cam_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_CAM_VIP3_CLKCTRL, dra7_cam_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_vpe_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_VPE_VPE_CLKCTRL, शून्य, CLKF_HW_SUP, "dpll_core_h23x2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_coreaon_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_COREAON_SMARTREFLEX_MPU_CLKCTRL, शून्य, CLKF_SW_SUP, "wkupaon_iclk_mux" पूर्ण,
	अणु DRA7_COREAON_SMARTREFLEX_CORE_CLKCTRL, शून्य, CLKF_SW_SUP, "wkupaon_iclk_mux" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_l3मुख्य1_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_L3MAIN1_L3_MAIN_1_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L3MAIN1_GPMC_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L3MAIN1_TPCC_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L3MAIN1_TPTC0_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L3MAIN1_TPTC1_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L3MAIN1_VCP1_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L3MAIN1_VCP2_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_ipu2_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_IPU2_MMU_IPU2_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_NO_IDLEST, "dpll_core_h22x2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_dma_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_DMA_DMA_SYSTEM_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_emअगर_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_EMIF_DMM_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
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
	"atl-clkctrl:0000:24",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_atl_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_atl_dpll_clk_mux_parents, शून्य पूर्ण,
	अणु 26, TI_CLK_MUX, dra7_atl_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_atl_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_ATL_ATL_CLKCTRL, dra7_atl_bit_data, CLKF_SW_SUP, "atl-clkctrl:0000:26" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_l4cfg_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_L4CFG_L4_CFG_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4CFG_SPINLOCK_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4CFG_MAILBOX1_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4CFG_MAILBOX2_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4CFG_MAILBOX3_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4CFG_MAILBOX4_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4CFG_MAILBOX5_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4CFG_MAILBOX6_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4CFG_MAILBOX7_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4CFG_MAILBOX8_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4CFG_MAILBOX9_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4CFG_MAILBOX10_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4CFG_MAILBOX11_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4CFG_MAILBOX12_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4CFG_MAILBOX13_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_l3instr_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_L3INSTR_L3_MAIN_2_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L3INSTR_L3_INSTR_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_iva_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_IVA_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_NO_IDLEST, "dpll_iva_h12x2_ck" पूर्ण,
	अणु DRA7_SL2IF_CLKCTRL, शून्य, CLKF_HW_SUP, "dpll_iva_h12x2_ck" पूर्ण,
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
	अणु DRA7_DSS_DSS_CORE_CLKCTRL, dra7_dss_core_bit_data, CLKF_SW_SUP, "dss-clkctrl:0000:8" पूर्ण,
	अणु DRA7_DSS_BB2D_CLKCTRL, शून्य, CLKF_SW_SUP, "dpll_core_h24x2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_gpu_core_mux_parents[] __initस्थिर = अणु
	"dpll_core_h14x2_ck",
	"dpll_per_h14x2_ck",
	"dpll_gpu_m2_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_gpu_hyd_mux_parents[] __initस्थिर = अणु
	"dpll_core_h14x2_ck",
	"dpll_per_h14x2_ck",
	"dpll_gpu_m2_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_gpu_core_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_gpu_core_mux_parents, शून्य, पूर्ण,
	अणु 26, TI_CLK_MUX, dra7_gpu_hyd_mux_parents, शून्य, पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_gpu_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_GPU_CLKCTRL, dra7_gpu_core_bit_data, CLKF_SW_SUP, "gpu-clkctrl:0000:24", पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_mmc1_fclk_mux_parents[] __initस्थिर = अणु
	"func_128m_clk",
	"dpll_per_m2x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_mmc1_fclk_भाग_parents[] __initस्थिर = अणु
	"l3init-clkctrl:0008:24",
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
	"l3init-clkctrl:0010:24",
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

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_usb_otg_ss1_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_usb_otg_ss2_refclk960m_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_l3init_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_L3INIT_MMC1_CLKCTRL, dra7_mmc1_bit_data, CLKF_SW_SUP, "l3init-clkctrl:0008:25" पूर्ण,
	अणु DRA7_L3INIT_MMC2_CLKCTRL, dra7_mmc2_bit_data, CLKF_SW_SUP, "l3init-clkctrl:0010:25" पूर्ण,
	अणु DRA7_L3INIT_USB_OTG_SS2_CLKCTRL, dra7_usb_otg_ss2_bit_data, CLKF_HW_SUP, "dpll_core_h13x2_ck" पूर्ण,
	अणु DRA7_L3INIT_USB_OTG_SS3_CLKCTRL, शून्य, CLKF_HW_SUP, "dpll_core_h13x2_ck" पूर्ण,
	अणु DRA7_L3INIT_USB_OTG_SS4_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_SOC_DRA74 | CLKF_SOC_DRA76, "dpll_core_h13x2_ck" पूर्ण,
	अणु DRA7_L3INIT_SATA_CLKCTRL, dra7_sata_bit_data, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु DRA7_L3INIT_OCP2SCP1_CLKCTRL, शून्य, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु DRA7_L3INIT_OCP2SCP3_CLKCTRL, शून्य, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु DRA7_L3INIT_USB_OTG_SS1_CLKCTRL, dra7_usb_otg_ss1_bit_data, CLKF_HW_SUP, "dpll_core_h13x2_ck" पूर्ण,
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

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_pcie_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_PCIE_PCIE1_CLKCTRL, dra7_pcie1_bit_data, CLKF_SW_SUP, "l4_root_clk_div" पूर्ण,
	अणु DRA7_PCIE_PCIE2_CLKCTRL, dra7_pcie2_bit_data, CLKF_SW_SUP, "l4_root_clk_div" पूर्ण,
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

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_gmac_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_GMAC_GMAC_CLKCTRL, dra7_gmac_bit_data, CLKF_SW_SUP, "gmac_main_clk" पूर्ण,
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

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_gpio7_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_gpio8_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, dra7_dss_32khz_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_mmc3_gfclk_भाग_parents[] __initस्थिर = अणु
	"l4per-clkctrl:00f8:24",
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
	"l4per-clkctrl:0100:24",
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

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_uart5_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_uart6_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_l4per_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_L4PER_TIMER10_CLKCTRL, dra7_समयr10_bit_data, CLKF_SW_SUP, "l4per-clkctrl:0000:24" पूर्ण,
	अणु DRA7_L4PER_TIMER11_CLKCTRL, dra7_समयr11_bit_data, CLKF_SW_SUP, "l4per-clkctrl:0008:24" पूर्ण,
	अणु DRA7_L4PER_TIMER2_CLKCTRL, dra7_समयr2_bit_data, CLKF_SW_SUP, "l4per-clkctrl:0010:24" पूर्ण,
	अणु DRA7_L4PER_TIMER3_CLKCTRL, dra7_समयr3_bit_data, CLKF_SW_SUP, "l4per-clkctrl:0018:24" पूर्ण,
	अणु DRA7_L4PER_TIMER4_CLKCTRL, dra7_समयr4_bit_data, CLKF_SW_SUP, "l4per-clkctrl:0020:24" पूर्ण,
	अणु DRA7_L4PER_TIMER9_CLKCTRL, dra7_समयr9_bit_data, CLKF_SW_SUP, "l4per-clkctrl:0028:24" पूर्ण,
	अणु DRA7_L4PER_ELM_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4PER_GPIO2_CLKCTRL, dra7_gpio2_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4PER_GPIO3_CLKCTRL, dra7_gpio3_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4PER_GPIO4_CLKCTRL, dra7_gpio4_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4PER_GPIO5_CLKCTRL, dra7_gpio5_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4PER_GPIO6_CLKCTRL, dra7_gpio6_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4PER_HDQ1W_CLKCTRL, शून्य, CLKF_SW_SUP, "func_12m_fclk" पूर्ण,
	अणु DRA7_L4PER_I2C1_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु DRA7_L4PER_I2C2_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु DRA7_L4PER_I2C3_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु DRA7_L4PER_I2C4_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु DRA7_L4PER_L4_PER1_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4PER_MCSPI1_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु DRA7_L4PER_MCSPI2_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु DRA7_L4PER_MCSPI3_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु DRA7_L4PER_MCSPI4_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु DRA7_L4PER_GPIO7_CLKCTRL, dra7_gpio7_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4PER_GPIO8_CLKCTRL, dra7_gpio8_bit_data, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4PER_MMC3_CLKCTRL, dra7_mmc3_bit_data, CLKF_SW_SUP, "l4per-clkctrl:00f8:25" पूर्ण,
	अणु DRA7_L4PER_MMC4_CLKCTRL, dra7_mmc4_bit_data, CLKF_SW_SUP, "l4per-clkctrl:0100:25" पूर्ण,
	अणु DRA7_L4PER_UART1_CLKCTRL, dra7_uart1_bit_data, CLKF_SW_SUP, "l4per-clkctrl:0118:24" पूर्ण,
	अणु DRA7_L4PER_UART2_CLKCTRL, dra7_uart2_bit_data, CLKF_SW_SUP, "l4per-clkctrl:0120:24" पूर्ण,
	अणु DRA7_L4PER_UART3_CLKCTRL, dra7_uart3_bit_data, CLKF_SW_SUP, "l4per-clkctrl:0128:24" पूर्ण,
	अणु DRA7_L4PER_UART4_CLKCTRL, dra7_uart4_bit_data, CLKF_SW_SUP, "l4per-clkctrl:0130:24" पूर्ण,
	अणु DRA7_L4PER_UART5_CLKCTRL, dra7_uart5_bit_data, CLKF_SW_SUP, "l4per-clkctrl:0148:24" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_l4sec_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_L4SEC_AES1_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4SEC_AES2_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4SEC_DES_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4SEC_RNG_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_SOC_NONSEC, "l4_root_clk_div" पूर्ण,
	अणु DRA7_L4SEC_SHAM_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4SEC_SHAM2_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_qspi_gfclk_mux_parents[] __initस्थिर = अणु
	"func_128m_clk",
	"dpll_per_h13x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_qspi_gfclk_भाग_parents[] __initस्थिर = अणु
	"l4per2-clkctrl:012c:24",
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

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_l4per2_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_L4PER2_L4_PER2_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4PER2_PRUSS1_CLKCTRL, शून्य, CLKF_SW_SUP, "" पूर्ण,
	अणु DRA7_L4PER2_PRUSS2_CLKCTRL, शून्य, CLKF_SW_SUP, "" पूर्ण,
	अणु DRA7_L4PER2_EPWMSS1_CLKCTRL, शून्य, CLKF_SW_SUP, "l4_root_clk_div" पूर्ण,
	अणु DRA7_L4PER2_EPWMSS2_CLKCTRL, शून्य, CLKF_SW_SUP, "l4_root_clk_div" पूर्ण,
	अणु DRA7_L4PER2_EPWMSS0_CLKCTRL, शून्य, CLKF_SW_SUP, "l4_root_clk_div" पूर्ण,
	अणु DRA7_L4PER2_QSPI_CLKCTRL, dra7_qspi_bit_data, CLKF_SW_SUP, "l4per2-clkctrl:012c:25" पूर्ण,
	अणु DRA7_L4PER2_MCASP2_CLKCTRL, dra7_mcasp2_bit_data, CLKF_SW_SUP, "l4per2-clkctrl:0154:22" पूर्ण,
	अणु DRA7_L4PER2_MCASP3_CLKCTRL, dra7_mcasp3_bit_data, CLKF_SW_SUP, "l4per2-clkctrl:015c:22" पूर्ण,
	अणु DRA7_L4PER2_MCASP5_CLKCTRL, dra7_mcasp5_bit_data, CLKF_SW_SUP, "l4per2-clkctrl:016c:22" पूर्ण,
	अणु DRA7_L4PER2_MCASP8_CLKCTRL, dra7_mcasp8_bit_data, CLKF_SW_SUP, "l4per2-clkctrl:0184:22" पूर्ण,
	अणु DRA7_L4PER2_MCASP4_CLKCTRL, dra7_mcasp4_bit_data, CLKF_SW_SUP, "l4per2-clkctrl:018c:22" पूर्ण,
	अणु DRA7_L4PER2_UART7_CLKCTRL, dra7_uart7_bit_data, CLKF_SW_SUP, "l4per2-clkctrl:01c4:24" पूर्ण,
	अणु DRA7_L4PER2_UART8_CLKCTRL, dra7_uart8_bit_data, CLKF_SW_SUP, "l4per2-clkctrl:01d4:24" पूर्ण,
	अणु DRA7_L4PER2_UART9_CLKCTRL, dra7_uart9_bit_data, CLKF_SW_SUP, "l4per2-clkctrl:01dc:24" पूर्ण,
	अणु DRA7_L4PER2_DCAN2_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_clkin1" पूर्ण,
	अणु DRA7_L4PER2_MCASP6_CLKCTRL, dra7_mcasp6_bit_data, CLKF_SW_SUP, "l4per2-clkctrl:01f8:22" पूर्ण,
	अणु DRA7_L4PER2_MCASP7_CLKCTRL, dra7_mcasp7_bit_data, CLKF_SW_SUP, "l4per2-clkctrl:01fc:22" पूर्ण,
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

अटल स्थिर काष्ठा omap_clkctrl_bit_data dra7_समयr16_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, dra7_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data dra7_l4per3_clkctrl_regs[] __initस्थिर = अणु
	अणु DRA7_L4PER3_L4_PER3_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु DRA7_L4PER3_TIMER13_CLKCTRL, dra7_समयr13_bit_data, CLKF_SW_SUP, "l4per3-clkctrl:00b4:24" पूर्ण,
	अणु DRA7_L4PER3_TIMER14_CLKCTRL, dra7_समयr14_bit_data, CLKF_SW_SUP, "l4per3-clkctrl:00bc:24" पूर्ण,
	अणु DRA7_L4PER3_TIMER15_CLKCTRL, dra7_समयr15_bit_data, CLKF_SW_SUP, "l4per3-clkctrl:00c4:24" पूर्ण,
	अणु DRA7_L4PER3_TIMER16_CLKCTRL, dra7_समयr16_bit_data, CLKF_SW_SUP, "l4per3-clkctrl:011c:24" पूर्ण,
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
	अणु DRA7_WKUPAON_L4_WKUP_CLKCTRL, शून्य, 0, "wkupaon_iclk_mux" पूर्ण,
	अणु DRA7_WKUPAON_WD_TIMER2_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_32k_ck" पूर्ण,
	अणु DRA7_WKUPAON_GPIO1_CLKCTRL, dra7_gpio1_bit_data, CLKF_HW_SUP, "wkupaon_iclk_mux" पूर्ण,
	अणु DRA7_WKUPAON_TIMER1_CLKCTRL, dra7_समयr1_bit_data, CLKF_SW_SUP, "wkupaon-clkctrl:0020:24" पूर्ण,
	अणु DRA7_WKUPAON_TIMER12_CLKCTRL, शून्य, CLKF_SOC_NONSEC, "secure_32k_clk_src_ck" पूर्ण,
	अणु DRA7_WKUPAON_COUNTER_32K_CLKCTRL, शून्य, 0, "wkupaon_iclk_mux" पूर्ण,
	अणु DRA7_WKUPAON_UART10_CLKCTRL, dra7_uart10_bit_data, CLKF_SW_SUP, "wkupaon-clkctrl:0060:24" पूर्ण,
	अणु DRA7_WKUPAON_DCAN1_CLKCTRL, dra7_dcan1_bit_data, CLKF_SW_SUP, "wkupaon-clkctrl:0068:24" पूर्ण,
	अणु DRA7_WKUPAON_ADC_CLKCTRL, शून्य, CLKF_SW_SUP | CLKF_SOC_DRA76, "mcan_clk" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

स्थिर काष्ठा omap_clkctrl_data dra7_clkctrl_data[] __initस्थिर = अणु
	अणु 0x4a005320, dra7_mpu_clkctrl_regs पूर्ण,
	अणु 0x4a005420, dra7_dsp1_clkctrl_regs पूर्ण,
	अणु 0x4a005520, dra7_ipu1_clkctrl_regs पूर्ण,
	अणु 0x4a005550, dra7_ipu_clkctrl_regs पूर्ण,
	अणु 0x4a005620, dra7_dsp2_clkctrl_regs पूर्ण,
	अणु 0x4a005720, dra7_rtc_clkctrl_regs पूर्ण,
	अणु 0x4a005760, dra7_vpe_clkctrl_regs पूर्ण,
	अणु 0x4a008620, dra7_coreaon_clkctrl_regs पूर्ण,
	अणु 0x4a008720, dra7_l3मुख्य1_clkctrl_regs पूर्ण,
	अणु 0x4a008920, dra7_ipu2_clkctrl_regs पूर्ण,
	अणु 0x4a008a20, dra7_dma_clkctrl_regs पूर्ण,
	अणु 0x4a008b20, dra7_emअगर_clkctrl_regs पूर्ण,
	अणु 0x4a008c00, dra7_atl_clkctrl_regs पूर्ण,
	अणु 0x4a008d20, dra7_l4cfg_clkctrl_regs पूर्ण,
	अणु 0x4a008e20, dra7_l3instr_clkctrl_regs पूर्ण,
	अणु 0x4a008f20, dra7_iva_clkctrl_regs पूर्ण,
	अणु 0x4a009020, dra7_cam_clkctrl_regs पूर्ण,
	अणु 0x4a009120, dra7_dss_clkctrl_regs पूर्ण,
	अणु 0x4a009220, dra7_gpu_clkctrl_regs पूर्ण,
	अणु 0x4a009320, dra7_l3init_clkctrl_regs पूर्ण,
	अणु 0x4a0093b0, dra7_pcie_clkctrl_regs पूर्ण,
	अणु 0x4a0093d0, dra7_gmac_clkctrl_regs पूर्ण,
	अणु 0x4a009728, dra7_l4per_clkctrl_regs पूर्ण,
	अणु 0x4a0098a0, dra7_l4sec_clkctrl_regs पूर्ण,
	अणु 0x4a00970c, dra7_l4per2_clkctrl_regs पूर्ण,
	अणु 0x4a009714, dra7_l4per3_clkctrl_regs पूर्ण,
	अणु 0x4ae07820, dra7_wkupaon_clkctrl_regs पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा ti_dt_clk dra7xx_clks[] = अणु
	DT_CLK(शून्य, "timer_32k_ck", "sys_32k_ck"),
	DT_CLK(शून्य, "sys_clkin_ck", "timer_sys_clk_div"),
	DT_CLK(शून्य, "sys_clkin", "sys_clkin1"),
	DT_CLK(शून्य, "atl_dpll_clk_mux", "atl-clkctrl:0000:24"),
	DT_CLK(शून्य, "atl_gfclk_mux", "atl-clkctrl:0000:26"),
	DT_CLK(शून्य, "dcan1_sys_clk_mux", "wkupaon-clkctrl:0068:24"),
	DT_CLK(शून्य, "dss_32khz_clk", "dss-clkctrl:0000:11"),
	DT_CLK(शून्य, "dss_48mhz_clk", "dss-clkctrl:0000:9"),
	DT_CLK(शून्य, "dss_dss_clk", "dss-clkctrl:0000:8"),
	DT_CLK(शून्य, "dss_hdmi_clk", "dss-clkctrl:0000:10"),
	DT_CLK(शून्य, "dss_video1_clk", "dss-clkctrl:0000:12"),
	DT_CLK(शून्य, "dss_video2_clk", "dss-clkctrl:0000:13"),
	DT_CLK(शून्य, "gmac_rft_clk_mux", "gmac-clkctrl:0000:25"),
	DT_CLK(शून्य, "gpio1_dbclk", "wkupaon-clkctrl:0018:8"),
	DT_CLK(शून्य, "gpio2_dbclk", "l4per-clkctrl:0038:8"),
	DT_CLK(शून्य, "gpio3_dbclk", "l4per-clkctrl:0040:8"),
	DT_CLK(शून्य, "gpio4_dbclk", "l4per-clkctrl:0048:8"),
	DT_CLK(शून्य, "gpio5_dbclk", "l4per-clkctrl:0050:8"),
	DT_CLK(शून्य, "gpio6_dbclk", "l4per-clkctrl:0058:8"),
	DT_CLK(शून्य, "gpio7_dbclk", "l4per-clkctrl:00e8:8"),
	DT_CLK(शून्य, "gpio8_dbclk", "l4per-clkctrl:00f0:8"),
	DT_CLK(शून्य, "ipu1_gfclk_mux", "ipu1-clkctrl:0000:24"),
	DT_CLK(शून्य, "mcasp1_ahclkr_mux", "ipu-clkctrl:0000:28"),
	DT_CLK(शून्य, "mcasp1_ahclkx_mux", "ipu-clkctrl:0000:24"),
	DT_CLK(शून्य, "mcasp1_aux_gfclk_mux", "ipu-clkctrl:0000:22"),
	DT_CLK(शून्य, "mcasp2_ahclkr_mux", "l4per2-clkctrl:0154:28"),
	DT_CLK(शून्य, "mcasp2_ahclkx_mux", "l4per2-clkctrl:0154:24"),
	DT_CLK(शून्य, "mcasp2_aux_gfclk_mux", "l4per2-clkctrl:0154:22"),
	DT_CLK(शून्य, "mcasp3_ahclkx_mux", "l4per2-clkctrl:015c:24"),
	DT_CLK(शून्य, "mcasp3_aux_gfclk_mux", "l4per2-clkctrl:015c:22"),
	DT_CLK(शून्य, "mcasp4_ahclkx_mux", "l4per2-clkctrl:018c:24"),
	DT_CLK(शून्य, "mcasp4_aux_gfclk_mux", "l4per2-clkctrl:018c:22"),
	DT_CLK(शून्य, "mcasp5_ahclkx_mux", "l4per2-clkctrl:016c:24"),
	DT_CLK(शून्य, "mcasp5_aux_gfclk_mux", "l4per2-clkctrl:016c:22"),
	DT_CLK(शून्य, "mcasp6_ahclkx_mux", "l4per2-clkctrl:01f8:24"),
	DT_CLK(शून्य, "mcasp6_aux_gfclk_mux", "l4per2-clkctrl:01f8:22"),
	DT_CLK(शून्य, "mcasp7_ahclkx_mux", "l4per2-clkctrl:01fc:24"),
	DT_CLK(शून्य, "mcasp7_aux_gfclk_mux", "l4per2-clkctrl:01fc:22"),
	DT_CLK(शून्य, "mcasp8_ahclkx_mux", "l4per2-clkctrl:0184:24"),
	DT_CLK(शून्य, "mcasp8_aux_gfclk_mux", "l4per2-clkctrl:0184:22"),
	DT_CLK(शून्य, "mmc1_clk32k", "l3init-clkctrl:0008:8"),
	DT_CLK(शून्य, "mmc1_fclk_div", "l3init-clkctrl:0008:25"),
	DT_CLK(शून्य, "mmc1_fclk_mux", "l3init-clkctrl:0008:24"),
	DT_CLK(शून्य, "mmc2_clk32k", "l3init-clkctrl:0010:8"),
	DT_CLK(शून्य, "mmc2_fclk_div", "l3init-clkctrl:0010:25"),
	DT_CLK(शून्य, "mmc2_fclk_mux", "l3init-clkctrl:0010:24"),
	DT_CLK(शून्य, "mmc3_clk32k", "l4per-clkctrl:00f8:8"),
	DT_CLK(शून्य, "mmc3_gfclk_div", "l4per-clkctrl:00f8:25"),
	DT_CLK(शून्य, "mmc3_gfclk_mux", "l4per-clkctrl:00f8:24"),
	DT_CLK(शून्य, "mmc4_clk32k", "l4per-clkctrl:0100:8"),
	DT_CLK(शून्य, "mmc4_gfclk_div", "l4per-clkctrl:0100:25"),
	DT_CLK(शून्य, "mmc4_gfclk_mux", "l4per-clkctrl:0100:24"),
	DT_CLK(शून्य, "optfclk_pciephy1_32khz", "pcie-clkctrl:0000:8"),
	DT_CLK(शून्य, "optfclk_pciephy1_clk", "pcie-clkctrl:0000:9"),
	DT_CLK(शून्य, "optfclk_pciephy1_div_clk", "pcie-clkctrl:0000:10"),
	DT_CLK(शून्य, "optfclk_pciephy2_32khz", "pcie-clkctrl:0008:8"),
	DT_CLK(शून्य, "optfclk_pciephy2_clk", "pcie-clkctrl:0008:9"),
	DT_CLK(शून्य, "optfclk_pciephy2_div_clk", "pcie-clkctrl:0008:10"),
	DT_CLK(शून्य, "qspi_gfclk_div", "l4per2-clkctrl:012c:25"),
	DT_CLK(शून्य, "qspi_gfclk_mux", "l4per2-clkctrl:012c:24"),
	DT_CLK(शून्य, "rmii_50mhz_clk_mux", "gmac-clkctrl:0000:24"),
	DT_CLK(शून्य, "sata_ref_clk", "l3init-clkctrl:0068:8"),
	DT_CLK(शून्य, "timer10_gfclk_mux", "l4per-clkctrl:0000:24"),
	DT_CLK(शून्य, "timer11_gfclk_mux", "l4per-clkctrl:0008:24"),
	DT_CLK(शून्य, "timer13_gfclk_mux", "l4per3-clkctrl:00b4:24"),
	DT_CLK(शून्य, "timer14_gfclk_mux", "l4per3-clkctrl:00bc:24"),
	DT_CLK(शून्य, "timer15_gfclk_mux", "l4per3-clkctrl:00c4:24"),
	DT_CLK(शून्य, "timer16_gfclk_mux", "l4per3-clkctrl:011c:24"),
	DT_CLK(शून्य, "timer1_gfclk_mux", "wkupaon-clkctrl:0020:24"),
	DT_CLK(शून्य, "timer2_gfclk_mux", "l4per-clkctrl:0010:24"),
	DT_CLK(शून्य, "timer3_gfclk_mux", "l4per-clkctrl:0018:24"),
	DT_CLK(शून्य, "timer4_gfclk_mux", "l4per-clkctrl:0020:24"),
	DT_CLK(शून्य, "timer5_gfclk_mux", "ipu-clkctrl:0008:24"),
	DT_CLK(शून्य, "timer6_gfclk_mux", "ipu-clkctrl:0010:24"),
	DT_CLK(शून्य, "timer7_gfclk_mux", "ipu-clkctrl:0018:24"),
	DT_CLK(शून्य, "timer8_gfclk_mux", "ipu-clkctrl:0020:24"),
	DT_CLK(शून्य, "timer9_gfclk_mux", "l4per-clkctrl:0028:24"),
	DT_CLK(शून्य, "uart10_gfclk_mux", "wkupaon-clkctrl:0060:24"),
	DT_CLK(शून्य, "uart1_gfclk_mux", "l4per-clkctrl:0118:24"),
	DT_CLK(शून्य, "uart2_gfclk_mux", "l4per-clkctrl:0120:24"),
	DT_CLK(शून्य, "uart3_gfclk_mux", "l4per-clkctrl:0128:24"),
	DT_CLK(शून्य, "uart4_gfclk_mux", "l4per-clkctrl:0130:24"),
	DT_CLK(शून्य, "uart5_gfclk_mux", "l4per-clkctrl:0148:24"),
	DT_CLK(शून्य, "uart6_gfclk_mux", "ipu-clkctrl:0030:24"),
	DT_CLK(शून्य, "uart7_gfclk_mux", "l4per2-clkctrl:01c4:24"),
	DT_CLK(शून्य, "uart8_gfclk_mux", "l4per2-clkctrl:01d4:24"),
	DT_CLK(शून्य, "uart9_gfclk_mux", "l4per2-clkctrl:01dc:24"),
	DT_CLK(शून्य, "usb_otg_ss1_refclk960m", "l3init-clkctrl:00d0:8"),
	DT_CLK(शून्य, "usb_otg_ss2_refclk960m", "l3init-clkctrl:0020:8"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

पूर्णांक __init dra7xx_dt_clk_init(व्योम)
अणु
	पूर्णांक rc;
	काष्ठा clk *dpll_ck, *hdcp_ck;

	अगर (ti_clk_get_features()->flags & TI_CLK_CLKCTRL_COMPAT)
		ti_dt_घड़ीs_रेजिस्टर(dra7xx_compat_clks);
	अन्यथा
		ti_dt_घड़ीs_रेजिस्टर(dra7xx_clks);

	omap2_clk_disable_स्वतःidle_all();

	ti_clk_add_aliases();

	dpll_ck = clk_get_sys(शून्य, "dpll_gmac_ck");
	rc = clk_set_rate(dpll_ck, DRA7_DPLL_GMAC_DEFFREQ);
	अगर (rc)
		pr_err("%s: failed to configure GMAC DPLL!\n", __func__);

	dpll_ck = clk_get_sys(शून्य, "dpll_usb_ck");
	rc = clk_set_rate(dpll_ck, DRA7_DPLL_USB_DEFFREQ);
	अगर (rc)
		pr_err("%s: failed to configure USB DPLL!\n", __func__);

	dpll_ck = clk_get_sys(शून्य, "dpll_usb_m2_ck");
	rc = clk_set_rate(dpll_ck, DRA7_DPLL_USB_DEFFREQ/2);
	अगर (rc)
		pr_err("%s: failed to set USB_DPLL M2 OUT\n", __func__);

	hdcp_ck = clk_get_sys(शून्य, "dss_deshdcp_clk");
	rc = clk_prepare_enable(hdcp_ck);
	अगर (rc)
		pr_err("%s: failed to set dss_deshdcp_clk\n", __func__);

	वापस rc;
पूर्ण
