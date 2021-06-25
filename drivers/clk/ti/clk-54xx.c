<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP5 Clock init
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 *
 * Tero Kristo (t-kristo@ti.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk/ti.h>
#समावेश <dt-bindings/घड़ी/omap5.h>

#समावेश "clock.h"

#घोषणा OMAP5_DPLL_ABE_DEFFREQ				98304000

/*
 * OMAP543x TRM, section "3.6.3.9.5 DPLL_USB Preferred Settings"
 * states it must be at 960MHz
 */
#घोषणा OMAP5_DPLL_USB_DEFFREQ				960000000

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_mpu_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_MPU_CLKCTRL, शून्य, 0, "dpll_mpu_m2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_dsp_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_MMU_DSP_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_NO_IDLEST, "dpll_iva_h11x2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_aess_fclk_parents[] __initस्थिर = अणु
	"abe_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data omap5_aess_fclk_data __initस्थिर = अणु
	.max_भाग = 2,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_aess_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_DIVIDER, omap5_aess_fclk_parents, &omap5_aess_fclk_data पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_dmic_gfclk_parents[] __initस्थिर = अणु
	"abe_cm:clk:0018:26",
	"pad_clks_ck",
	"slimbus_clk",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_dmic_sync_mux_ck_parents[] __initस्थिर = अणु
	"abe_24m_fclk",
	"dss_syc_gfclk_div",
	"func_24m_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_dmic_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_dmic_gfclk_parents, शून्य पूर्ण,
	अणु 26, TI_CLK_MUX, omap5_dmic_sync_mux_ck_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_mcbsp1_gfclk_parents[] __initस्थिर = अणु
	"abe_cm:clk:0028:26",
	"pad_clks_ck",
	"slimbus_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_mcbsp1_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_mcbsp1_gfclk_parents, शून्य पूर्ण,
	अणु 26, TI_CLK_MUX, omap5_dmic_sync_mux_ck_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_mcbsp2_gfclk_parents[] __initस्थिर = अणु
	"abe_cm:clk:0030:26",
	"pad_clks_ck",
	"slimbus_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_mcbsp2_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_mcbsp2_gfclk_parents, शून्य पूर्ण,
	अणु 26, TI_CLK_MUX, omap5_dmic_sync_mux_ck_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_mcbsp3_gfclk_parents[] __initस्थिर = अणु
	"abe_cm:clk:0038:26",
	"pad_clks_ck",
	"slimbus_clk",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_mcbsp3_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_mcbsp3_gfclk_parents, शून्य पूर्ण,
	अणु 26, TI_CLK_MUX, omap5_dmic_sync_mux_ck_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_समयr5_gfclk_mux_parents[] __initस्थिर = अणु
	"dss_syc_gfclk_div",
	"sys_32k_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_समयr5_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_समयr5_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_समयr6_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_समयr5_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_समयr7_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_समयr5_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_समयr8_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_समयr5_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_abe_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_L4_ABE_CLKCTRL, शून्य, 0, "abe_iclk" पूर्ण,
	अणु OMAP5_AESS_CLKCTRL, omap5_aess_bit_data, CLKF_SW_SUP, "abe_cm:clk:0008:24" पूर्ण,
	अणु OMAP5_MCPDM_CLKCTRL, शून्य, CLKF_SW_SUP, "pad_clks_ck" पूर्ण,
	अणु OMAP5_DMIC_CLKCTRL, omap5_dmic_bit_data, CLKF_SW_SUP, "abe_cm:clk:0018:24" पूर्ण,
	अणु OMAP5_MCBSP1_CLKCTRL, omap5_mcbsp1_bit_data, CLKF_SW_SUP, "abe_cm:clk:0028:24" पूर्ण,
	अणु OMAP5_MCBSP2_CLKCTRL, omap5_mcbsp2_bit_data, CLKF_SW_SUP, "abe_cm:clk:0030:24" पूर्ण,
	अणु OMAP5_MCBSP3_CLKCTRL, omap5_mcbsp3_bit_data, CLKF_SW_SUP, "abe_cm:clk:0038:24" पूर्ण,
	अणु OMAP5_TIMER5_CLKCTRL, omap5_समयr5_bit_data, CLKF_SW_SUP, "abe_cm:clk:0048:24" पूर्ण,
	अणु OMAP5_TIMER6_CLKCTRL, omap5_समयr6_bit_data, CLKF_SW_SUP, "abe_cm:clk:0050:24" पूर्ण,
	अणु OMAP5_TIMER7_CLKCTRL, omap5_समयr7_bit_data, CLKF_SW_SUP, "abe_cm:clk:0058:24" पूर्ण,
	अणु OMAP5_TIMER8_CLKCTRL, omap5_समयr8_bit_data, CLKF_SW_SUP, "abe_cm:clk:0060:24" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_l3मुख्य1_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_L3_MAIN_1_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_l3मुख्य2_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_L3_MAIN_2_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु OMAP5_L3_MAIN_2_GPMC_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु OMAP5_L3_MAIN_2_OCMC_RAM_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_ipu_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_MMU_IPU_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_NO_IDLEST, "dpll_core_h22x2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_dma_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_DMA_SYSTEM_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_emअगर_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_DMM_CLKCTRL, शून्य, 0, "l3_iclk_div" पूर्ण,
	अणु OMAP5_EMIF1_CLKCTRL, शून्य, CLKF_HW_SUP, "dpll_core_h11x2_ck" पूर्ण,
	अणु OMAP5_EMIF2_CLKCTRL, शून्य, CLKF_HW_SUP, "dpll_core_h11x2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_l4cfg_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_L4_CFG_CLKCTRL, शून्य, 0, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_SPINLOCK_CLKCTRL, शून्य, 0, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_MAILBOX_CLKCTRL, शून्य, 0, "l4_root_clk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_l3instr_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_L3_MAIN_3_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु OMAP5_L3_INSTR_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_समयr10_gfclk_mux_parents[] __initस्थिर = अणु
	"sys_clkin",
	"sys_32k_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_समयr10_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_समयr11_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_समयr2_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_समयr3_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_समयr4_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_समयr9_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_gpio2_dbclk_parents[] __initस्थिर = अणु
	"sys_32k_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_gpio2_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap5_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_gpio3_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap5_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_gpio4_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap5_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_gpio5_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap5_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_gpio6_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap5_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_gpio7_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap5_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_gpio8_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap5_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_l4per_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_TIMER10_CLKCTRL, omap5_समयr10_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0008:24" पूर्ण,
	अणु OMAP5_TIMER11_CLKCTRL, omap5_समयr11_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0010:24" पूर्ण,
	अणु OMAP5_TIMER2_CLKCTRL, omap5_समयr2_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0018:24" पूर्ण,
	अणु OMAP5_TIMER3_CLKCTRL, omap5_समयr3_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0020:24" पूर्ण,
	अणु OMAP5_TIMER4_CLKCTRL, omap5_समयr4_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0028:24" पूर्ण,
	अणु OMAP5_TIMER9_CLKCTRL, omap5_समयr9_bit_data, CLKF_SW_SUP, "l4per_cm:clk:0030:24" पूर्ण,
	अणु OMAP5_GPIO2_CLKCTRL, omap5_gpio2_bit_data, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_GPIO3_CLKCTRL, omap5_gpio3_bit_data, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_GPIO4_CLKCTRL, omap5_gpio4_bit_data, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_GPIO5_CLKCTRL, omap5_gpio5_bit_data, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_GPIO6_CLKCTRL, omap5_gpio6_bit_data, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_I2C1_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु OMAP5_I2C2_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु OMAP5_I2C3_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु OMAP5_I2C4_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु OMAP5_L4_PER_CLKCTRL, शून्य, 0, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_MCSPI1_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP5_MCSPI2_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP5_MCSPI3_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP5_MCSPI4_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP5_GPIO7_CLKCTRL, omap5_gpio7_bit_data, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_GPIO8_CLKCTRL, omap5_gpio8_bit_data, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_MMC3_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP5_MMC4_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP5_UART1_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP5_UART2_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP5_UART3_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP5_UART4_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP5_MMC5_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु OMAP5_I2C5_CLKCTRL, शून्य, CLKF_SW_SUP, "func_96m_fclk" पूर्ण,
	अणु OMAP5_UART5_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP5_UART6_CLKCTRL, शून्य, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा
omap_clkctrl_reg_data omap5_l4_secure_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_AES1_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु OMAP5_AES2_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु OMAP5_DES3DES_CLKCTRL, शून्य, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_FPKA_CLKCTRL, शून्य, CLKF_SW_SUP, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_RNG_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_SOC_NONSEC, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_SHA2MD5_CLKCTRL, शून्य, CLKF_HW_SUP, "l3_iclk_div" पूर्ण,
	अणु OMAP5_DMA_CRYPTO_CLKCTRL, शून्य, CLKF_HW_SUP | CLKF_SOC_NONSEC, "l3_iclk_div" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_iva_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_IVA_CLKCTRL, शून्य, CLKF_HW_SUP, "dpll_iva_h12x2_ck" पूर्ण,
	अणु OMAP5_SL2IF_CLKCTRL, शून्य, CLKF_HW_SUP, "dpll_iva_h12x2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_dss_dss_clk_parents[] __initस्थिर = अणु
	"dpll_per_h12x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_dss_48mhz_clk_parents[] __initस्थिर = अणु
	"func_48m_fclk",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_dss_sys_clk_parents[] __initस्थिर = अणु
	"dss_syc_gfclk_div",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_dss_core_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap5_dss_dss_clk_parents, शून्य पूर्ण,
	अणु 9, TI_CLK_GATE, omap5_dss_48mhz_clk_parents, शून्य पूर्ण,
	अणु 10, TI_CLK_GATE, omap5_dss_sys_clk_parents, शून्य पूर्ण,
	अणु 11, TI_CLK_GATE, omap5_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_dss_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_DSS_CORE_CLKCTRL, omap5_dss_core_bit_data, CLKF_SW_SUP, "dss_cm:clk:0000:8" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_gpu_core_mux_parents[] __initस्थिर = अणु
	"dpll_core_h14x2_ck",
	"dpll_per_h14x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_gpu_hyd_mux_parents[] __initस्थिर = अणु
	"dpll_core_h14x2_ck",
	"dpll_per_h14x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_gpu_sys_clk_parents[] __initस्थिर = अणु
	"sys_clkin",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data omap5_gpu_sys_clk_data __initस्थिर = अणु
	.max_भाग = 2,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_gpu_core_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_gpu_core_mux_parents, शून्य पूर्ण,
	अणु 25, TI_CLK_MUX, omap5_gpu_hyd_mux_parents, शून्य पूर्ण,
	अणु 26, TI_CLK_DIVIDER, omap5_gpu_sys_clk_parents, &omap5_gpu_sys_clk_data पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_gpu_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_GPU_CLKCTRL, omap5_gpu_core_bit_data, CLKF_SW_SUP, "gpu_cm:clk:0000:24" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_mmc1_fclk_mux_parents[] __initस्थिर = अणु
	"func_128m_clk",
	"dpll_per_m2x2_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_mmc1_fclk_parents[] __initस्थिर = अणु
	"l3init_cm:clk:0008:24",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data omap5_mmc1_fclk_data __initस्थिर = अणु
	.max_भाग = 2,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_mmc1_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap5_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, omap5_mmc1_fclk_mux_parents, शून्य पूर्ण,
	अणु 25, TI_CLK_DIVIDER, omap5_mmc1_fclk_parents, &omap5_mmc1_fclk_data पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_mmc2_fclk_parents[] __initस्थिर = अणु
	"l3init_cm:clk:0010:24",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_भाग_data omap5_mmc2_fclk_data __initस्थिर = अणु
	.max_भाग = 2,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_mmc2_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_mmc1_fclk_mux_parents, शून्य पूर्ण,
	अणु 25, TI_CLK_DIVIDER, omap5_mmc2_fclk_parents, &omap5_mmc2_fclk_data पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_usb_host_hs_hsic60m_p3_clk_parents[] __initस्थिर = अणु
	"l3init_60m_fclk",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_usb_host_hs_hsic480m_p3_clk_parents[] __initस्थिर = अणु
	"dpll_usb_m2_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_usb_host_hs_uपंचांगi_p1_clk_parents[] __initस्थिर = अणु
	"l3init_cm:clk:0038:24",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_usb_host_hs_uपंचांगi_p2_clk_parents[] __initस्थिर = अणु
	"l3init_cm:clk:0038:25",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_uपंचांगi_p1_gfclk_parents[] __initस्थिर = अणु
	"l3init_60m_fclk",
	"xclk60mhsp1_ck",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_uपंचांगi_p2_gfclk_parents[] __initस्थिर = अणु
	"l3init_60m_fclk",
	"xclk60mhsp2_ck",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_usb_host_hs_bit_data[] __initस्थिर = अणु
	अणु 6, TI_CLK_GATE, omap5_usb_host_hs_hsic60m_p3_clk_parents, शून्य पूर्ण,
	अणु 7, TI_CLK_GATE, omap5_usb_host_hs_hsic480m_p3_clk_parents, शून्य पूर्ण,
	अणु 8, TI_CLK_GATE, omap5_usb_host_hs_uपंचांगi_p1_clk_parents, शून्य पूर्ण,
	अणु 9, TI_CLK_GATE, omap5_usb_host_hs_uपंचांगi_p2_clk_parents, शून्य पूर्ण,
	अणु 10, TI_CLK_GATE, omap5_usb_host_hs_hsic60m_p3_clk_parents, शून्य पूर्ण,
	अणु 11, TI_CLK_GATE, omap5_usb_host_hs_hsic60m_p3_clk_parents, शून्य पूर्ण,
	अणु 12, TI_CLK_GATE, omap5_usb_host_hs_hsic60m_p3_clk_parents, शून्य पूर्ण,
	अणु 13, TI_CLK_GATE, omap5_usb_host_hs_hsic480m_p3_clk_parents, शून्य पूर्ण,
	अणु 14, TI_CLK_GATE, omap5_usb_host_hs_hsic480m_p3_clk_parents, शून्य पूर्ण,
	अणु 24, TI_CLK_MUX, omap5_uपंचांगi_p1_gfclk_parents, शून्य पूर्ण,
	अणु 25, TI_CLK_MUX, omap5_uपंचांगi_p2_gfclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_usb_tll_hs_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap5_usb_host_hs_hsic60m_p3_clk_parents, शून्य पूर्ण,
	अणु 9, TI_CLK_GATE, omap5_usb_host_hs_hsic60m_p3_clk_parents, शून्य पूर्ण,
	अणु 10, TI_CLK_GATE, omap5_usb_host_hs_hsic60m_p3_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_sata_ref_clk_parents[] __initस्थिर = अणु
	"sys_clkin",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_sata_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap5_sata_ref_clk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_usb_otg_ss_refclk960m_parents[] __initस्थिर = अणु
	"dpll_usb_clkdcoldo",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_usb_otg_ss_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap5_usb_otg_ss_refclk960m_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_l3init_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_MMC1_CLKCTRL, omap5_mmc1_bit_data, CLKF_SW_SUP, "l3init_cm:clk:0008:25" पूर्ण,
	अणु OMAP5_MMC2_CLKCTRL, omap5_mmc2_bit_data, CLKF_SW_SUP, "l3init_cm:clk:0010:25" पूर्ण,
	अणु OMAP5_USB_HOST_HS_CLKCTRL, omap5_usb_host_hs_bit_data, CLKF_SW_SUP, "l3init_60m_fclk" पूर्ण,
	अणु OMAP5_USB_TLL_HS_CLKCTRL, omap5_usb_tll_hs_bit_data, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_SATA_CLKCTRL, omap5_sata_bit_data, CLKF_SW_SUP, "func_48m_fclk" पूर्ण,
	अणु OMAP5_OCP2SCP1_CLKCTRL, शून्य, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_OCP2SCP3_CLKCTRL, शून्य, CLKF_HW_SUP, "l4_root_clk_div" पूर्ण,
	अणु OMAP5_USB_OTG_SS_CLKCTRL, omap5_usb_otg_ss_bit_data, CLKF_HW_SUP, "dpll_core_h13x2_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_gpio1_bit_data[] __initस्थिर = अणु
	अणु 8, TI_CLK_GATE, omap5_gpio2_dbclk_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_bit_data omap5_समयr1_bit_data[] __initस्थिर = अणु
	अणु 24, TI_CLK_MUX, omap5_समयr10_gfclk_mux_parents, शून्य पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_reg_data omap5_wkupaon_clkctrl_regs[] __initस्थिर = अणु
	अणु OMAP5_L4_WKUP_CLKCTRL, शून्य, 0, "wkupaon_iclk_mux" पूर्ण,
	अणु OMAP5_WD_TIMER2_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_32k_ck" पूर्ण,
	अणु OMAP5_GPIO1_CLKCTRL, omap5_gpio1_bit_data, CLKF_HW_SUP, "wkupaon_iclk_mux" पूर्ण,
	अणु OMAP5_TIMER1_CLKCTRL, omap5_समयr1_bit_data, CLKF_SW_SUP, "wkupaon_cm:clk:0020:24" पूर्ण,
	अणु OMAP5_COUNTER_32K_CLKCTRL, शून्य, 0, "wkupaon_iclk_mux" पूर्ण,
	अणु OMAP5_KBD_CLKCTRL, शून्य, CLKF_SW_SUP, "sys_32k_ck" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

स्थिर काष्ठा omap_clkctrl_data omap5_clkctrl_data[] __initस्थिर = अणु
	अणु 0x4a004320, omap5_mpu_clkctrl_regs पूर्ण,
	अणु 0x4a004420, omap5_dsp_clkctrl_regs पूर्ण,
	अणु 0x4a004520, omap5_abe_clkctrl_regs पूर्ण,
	अणु 0x4a008720, omap5_l3मुख्य1_clkctrl_regs पूर्ण,
	अणु 0x4a008820, omap5_l3मुख्य2_clkctrl_regs पूर्ण,
	अणु 0x4a008920, omap5_ipu_clkctrl_regs पूर्ण,
	अणु 0x4a008a20, omap5_dma_clkctrl_regs पूर्ण,
	अणु 0x4a008b20, omap5_emअगर_clkctrl_regs पूर्ण,
	अणु 0x4a008d20, omap5_l4cfg_clkctrl_regs पूर्ण,
	अणु 0x4a008e20, omap5_l3instr_clkctrl_regs पूर्ण,
	अणु 0x4a009020, omap5_l4per_clkctrl_regs पूर्ण,
	अणु 0x4a0091a0, omap5_l4_secure_clkctrl_regs पूर्ण,
	अणु 0x4a009220, omap5_iva_clkctrl_regs पूर्ण,
	अणु 0x4a009420, omap5_dss_clkctrl_regs पूर्ण,
	अणु 0x4a009520, omap5_gpu_clkctrl_regs पूर्ण,
	अणु 0x4a009620, omap5_l3init_clkctrl_regs पूर्ण,
	अणु 0x4ae07920, omap5_wkupaon_clkctrl_regs पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा ti_dt_clk omap54xx_clks[] = अणु
	DT_CLK(शून्य, "timer_32k_ck", "sys_32k_ck"),
	DT_CLK(शून्य, "sys_clkin_ck", "sys_clkin"),
	DT_CLK(शून्य, "dmic_gfclk", "abe_cm:0018:24"),
	DT_CLK(शून्य, "dmic_sync_mux_ck", "abe_cm:0018:26"),
	DT_CLK(शून्य, "dss_32khz_clk", "dss_cm:0000:11"),
	DT_CLK(शून्य, "dss_48mhz_clk", "dss_cm:0000:9"),
	DT_CLK(शून्य, "dss_dss_clk", "dss_cm:0000:8"),
	DT_CLK(शून्य, "dss_sys_clk", "dss_cm:0000:10"),
	DT_CLK(शून्य, "gpio1_dbclk", "wkupaon_cm:0018:8"),
	DT_CLK(शून्य, "gpio2_dbclk", "l4per_cm:0040:8"),
	DT_CLK(शून्य, "gpio3_dbclk", "l4per_cm:0048:8"),
	DT_CLK(शून्य, "gpio4_dbclk", "l4per_cm:0050:8"),
	DT_CLK(शून्य, "gpio5_dbclk", "l4per_cm:0058:8"),
	DT_CLK(शून्य, "gpio6_dbclk", "l4per_cm:0060:8"),
	DT_CLK(शून्य, "gpio7_dbclk", "l4per_cm:00f0:8"),
	DT_CLK(शून्य, "gpio8_dbclk", "l4per_cm:00f8:8"),
	DT_CLK(शून्य, "mcbsp1_gfclk", "abe_cm:0028:24"),
	DT_CLK(शून्य, "mcbsp1_sync_mux_ck", "abe_cm:0028:26"),
	DT_CLK(शून्य, "mcbsp2_gfclk", "abe_cm:0030:24"),
	DT_CLK(शून्य, "mcbsp2_sync_mux_ck", "abe_cm:0030:26"),
	DT_CLK(शून्य, "mcbsp3_gfclk", "abe_cm:0038:24"),
	DT_CLK(शून्य, "mcbsp3_sync_mux_ck", "abe_cm:0038:26"),
	DT_CLK(शून्य, "mmc1_32khz_clk", "l3init_cm:0008:8"),
	DT_CLK(शून्य, "mmc1_fclk", "l3init_cm:0008:25"),
	DT_CLK(शून्य, "mmc1_fclk_mux", "l3init_cm:0008:24"),
	DT_CLK(शून्य, "mmc2_fclk", "l3init_cm:0010:25"),
	DT_CLK(शून्य, "mmc2_fclk_mux", "l3init_cm:0010:24"),
	DT_CLK(शून्य, "sata_ref_clk", "l3init_cm:0068:8"),
	DT_CLK(शून्य, "timer10_gfclk_mux", "l4per_cm:0008:24"),
	DT_CLK(शून्य, "timer11_gfclk_mux", "l4per_cm:0010:24"),
	DT_CLK(शून्य, "timer1_gfclk_mux", "wkupaon_cm:0020:24"),
	DT_CLK(शून्य, "timer2_gfclk_mux", "l4per_cm:0018:24"),
	DT_CLK(शून्य, "timer3_gfclk_mux", "l4per_cm:0020:24"),
	DT_CLK(शून्य, "timer4_gfclk_mux", "l4per_cm:0028:24"),
	DT_CLK(शून्य, "timer5_gfclk_mux", "abe_cm:0048:24"),
	DT_CLK(शून्य, "timer6_gfclk_mux", "abe_cm:0050:24"),
	DT_CLK(शून्य, "timer7_gfclk_mux", "abe_cm:0058:24"),
	DT_CLK(शून्य, "timer8_gfclk_mux", "abe_cm:0060:24"),
	DT_CLK(शून्य, "timer9_gfclk_mux", "l4per_cm:0030:24"),
	DT_CLK(शून्य, "usb_host_hs_hsic480m_p1_clk", "l3init_cm:0038:13"),
	DT_CLK(शून्य, "usb_host_hs_hsic480m_p2_clk", "l3init_cm:0038:14"),
	DT_CLK(शून्य, "usb_host_hs_hsic480m_p3_clk", "l3init_cm:0038:7"),
	DT_CLK(शून्य, "usb_host_hs_hsic60m_p1_clk", "l3init_cm:0038:11"),
	DT_CLK(शून्य, "usb_host_hs_hsic60m_p2_clk", "l3init_cm:0038:12"),
	DT_CLK(शून्य, "usb_host_hs_hsic60m_p3_clk", "l3init_cm:0038:6"),
	DT_CLK(शून्य, "usb_host_hs_utmi_p1_clk", "l3init_cm:0038:8"),
	DT_CLK(शून्य, "usb_host_hs_utmi_p2_clk", "l3init_cm:0038:9"),
	DT_CLK(शून्य, "usb_host_hs_utmi_p3_clk", "l3init_cm:0038:10"),
	DT_CLK(शून्य, "usb_otg_ss_refclk960m", "l3init_cm:00d0:8"),
	DT_CLK(शून्य, "usb_tll_hs_usb_ch0_clk", "l3init_cm:0048:8"),
	DT_CLK(शून्य, "usb_tll_hs_usb_ch1_clk", "l3init_cm:0048:9"),
	DT_CLK(शून्य, "usb_tll_hs_usb_ch2_clk", "l3init_cm:0048:10"),
	DT_CLK(शून्य, "utmi_p1_gfclk", "l3init_cm:0038:24"),
	DT_CLK(शून्य, "utmi_p2_gfclk", "l3init_cm:0038:25"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

पूर्णांक __init omap5xxx_dt_clk_init(व्योम)
अणु
	पूर्णांक rc;
	काष्ठा clk *abe_dpll_ref, *abe_dpll, *abe_dpll_byp, *sys_32k_ck, *usb_dpll;

	ti_dt_घड़ीs_रेजिस्टर(omap54xx_clks);

	omap2_clk_disable_स्वतःidle_all();

	ti_clk_add_aliases();

	abe_dpll_ref = clk_get_sys(शून्य, "abe_dpll_clk_mux");
	sys_32k_ck = clk_get_sys(शून्य, "sys_32k_ck");
	rc = clk_set_parent(abe_dpll_ref, sys_32k_ck);

	/*
	 * This must also be set to sys_32k_ck to match or
	 * the ABE DPLL will not lock on a warm reboot when
	 * ABE समयrs are used.
	 */
	abe_dpll_byp = clk_get_sys(शून्य, "abe_dpll_bypass_clk_mux");
	अगर (!rc)
		rc = clk_set_parent(abe_dpll_byp, sys_32k_ck);

	abe_dpll = clk_get_sys(शून्य, "dpll_abe_ck");
	अगर (!rc)
		rc = clk_set_rate(abe_dpll, OMAP5_DPLL_ABE_DEFFREQ);
	अगर (rc)
		pr_err("%s: failed to configure ABE DPLL!\n", __func__);

	abe_dpll = clk_get_sys(शून्य, "dpll_abe_m2x2_ck");
	अगर (!rc)
		rc = clk_set_rate(abe_dpll, OMAP5_DPLL_ABE_DEFFREQ * 2);
	अगर (rc)
		pr_err("%s: failed to configure ABE m2x2 DPLL!\n", __func__);

	usb_dpll = clk_get_sys(शून्य, "dpll_usb_ck");
	rc = clk_set_rate(usb_dpll, OMAP5_DPLL_USB_DEFFREQ);
	अगर (rc)
		pr_err("%s: failed to configure USB DPLL!\n", __func__);

	usb_dpll = clk_get_sys(शून्य, "dpll_usb_m2_ck");
	rc = clk_set_rate(usb_dpll, OMAP5_DPLL_USB_DEFFREQ/2);
	अगर (rc)
		pr_err("%s: failed to set USB_DPLL M2 OUT\n", __func__);

	वापस 0;
पूर्ण
