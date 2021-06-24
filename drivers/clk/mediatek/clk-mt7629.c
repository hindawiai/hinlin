<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 MediaTek Inc.
 * Author: Wenzhen Yu <Wenzhen Yu@mediatek.com>
 *	   Ryder Lee <ryder.lee@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"
#समावेश "clk-cpumux.h"

#समावेश <dt-bindings/घड़ी/mt7629-clk.h>

#घोषणा MT7629_PLL_FMAX		(2500UL * MHZ)
#घोषणा CON0_MT7629_RST_BAR	BIT(24)

#घोषणा PLL_B(_id, _name, _reg, _pwr_reg, _en_mask, _flags, _pcwbits,	\
			_pd_reg, _pd_shअगरt, _tuner_reg, _pcw_reg,	\
			_pcw_shअगरt, _भाग_प्रकारable, _parent_name) अणु		\
		.id = _id,						\
		.name = _name,						\
		.reg = _reg,						\
		.pwr_reg = _pwr_reg,					\
		.en_mask = _en_mask,					\
		.flags = _flags,					\
		.rst_bar_mask = CON0_MT7629_RST_BAR,			\
		.fmax = MT7629_PLL_FMAX,				\
		.pcwbits = _pcwbits,					\
		.pd_reg = _pd_reg,					\
		.pd_shअगरt = _pd_shअगरt,					\
		.tuner_reg = _tuner_reg,				\
		.pcw_reg = _pcw_reg,					\
		.pcw_shअगरt = _pcw_shअगरt,				\
		.भाग_प्रकारable = _भाग_प्रकारable,				\
		.parent_name = _parent_name,				\
	पूर्ण

#घोषणा PLL(_id, _name, _reg, _pwr_reg, _en_mask, _flags, _pcwbits,	\
		_pd_reg, _pd_shअगरt, _tuner_reg, _pcw_reg,		\
		_pcw_shअगरt)						\
	PLL_B(_id, _name, _reg, _pwr_reg, _en_mask, _flags, _pcwbits,	\
		_pd_reg, _pd_shअगरt, _tuner_reg, _pcw_reg, _pcw_shअगरt,	\
		शून्य, "clk20m")

#घोषणा GATE_APMIXED(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &apmixed_cg_regs,		\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr_inv,	\
	पूर्ण

#घोषणा GATE_INFRA(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &infra_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	पूर्ण

#घोषणा GATE_PERI0(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &peri0_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	पूर्ण

#घोषणा GATE_PERI1(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &peri1_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	पूर्ण

अटल DEFINE_SPINLOCK(mt7629_clk_lock);

अटल स्थिर अक्षर * स्थिर axi_parents[] = अणु
	"clkxtal",
	"syspll1_d2",
	"syspll_d5",
	"syspll1_d4",
	"univpll_d5",
	"univpll2_d2",
	"univpll_d7",
	"dmpll_ck"
पूर्ण;

अटल स्थिर अक्षर * स्थिर mem_parents[] = अणु
	"clkxtal",
	"dmpll_ck"
पूर्ण;

अटल स्थिर अक्षर * स्थिर ddrphycfg_parents[] = अणु
	"clkxtal",
	"syspll1_d8"
पूर्ण;

अटल स्थिर अक्षर * स्थिर eth_parents[] = अणु
	"clkxtal",
	"syspll1_d2",
	"univpll1_d2",
	"syspll1_d4",
	"univpll_d5",
	"sgmiipll_d2",
	"univpll_d7",
	"dmpll_ck"
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_parents[] = अणु
	"clkxtal",
	"univpll2_d4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर f10m_ref_parents[] = अणु
	"clkxtal",
	"sgmiipll_d2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर nfi_infra_parents[] = अणु
	"clkxtal",
	"clkxtal",
	"clkxtal",
	"clkxtal",
	"clkxtal",
	"clkxtal",
	"univpll2_d8",
	"univpll3_d4",
	"syspll1_d8",
	"univpll1_d8",
	"syspll4_d2",
	"syspll2_d4",
	"univpll2_d4",
	"univpll3_d2",
	"syspll1_d4",
	"syspll_d7"
पूर्ण;

अटल स्थिर अक्षर * स्थिर flash_parents[] = अणु
	"clkxtal",
	"univpll_d80_d4",
	"syspll2_d8",
	"syspll3_d4",
	"univpll3_d4",
	"univpll1_d8",
	"syspll2_d4",
	"univpll2_d4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_parents[] = अणु
	"clkxtal",
	"univpll2_d8"
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi0_parents[] = अणु
	"clkxtal",
	"syspll3_d2",
	"clkxtal",
	"syspll2_d4",
	"syspll4_d2",
	"univpll2_d4",
	"univpll1_d8",
	"clkxtal"
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi1_parents[] = अणु
	"clkxtal",
	"syspll3_d2",
	"clkxtal",
	"syspll4_d4",
	"syspll4_d2",
	"univpll2_d4",
	"univpll1_d8",
	"clkxtal"
पूर्ण;

अटल स्थिर अक्षर * स्थिर msdc30_0_parents[] = अणु
	"clkxtal",
	"univpll2_d16",
	"univ48m"
पूर्ण;

अटल स्थिर अक्षर * स्थिर msdc30_1_parents[] = अणु
	"clkxtal",
	"univpll2_d16",
	"univ48m",
	"syspll2_d4",
	"univpll2_d4",
	"syspll_d7",
	"syspll2_d2",
	"univpll2_d2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर ap2wbmcu_parents[] = अणु
	"clkxtal",
	"syspll1_d2",
	"univ48m",
	"syspll1_d8",
	"univpll2_d4",
	"syspll_d7",
	"syspll2_d2",
	"univpll2_d2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर audio_parents[] = अणु
	"clkxtal",
	"syspll3_d4",
	"syspll4_d4",
	"syspll1_d16"
पूर्ण;

अटल स्थिर अक्षर * स्थिर aud_पूर्णांकbus_parents[] = अणु
	"clkxtal",
	"syspll1_d4",
	"syspll4_d2",
	"dmpll_d4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर pmicspi_parents[] = अणु
	"clkxtal",
	"syspll1_d8",
	"syspll3_d4",
	"syspll1_d16",
	"univpll3_d4",
	"clkxtal",
	"univpll2_d4",
	"dmpll_d8"
पूर्ण;

अटल स्थिर अक्षर * स्थिर scp_parents[] = अणु
	"clkxtal",
	"syspll1_d8",
	"univpll2_d2",
	"univpll2_d4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर atb_parents[] = अणु
	"clkxtal",
	"syspll1_d2",
	"syspll_d5"
पूर्ण;

अटल स्थिर अक्षर * स्थिर hअगर_parents[] = अणु
	"clkxtal",
	"syspll1_d2",
	"univpll1_d2",
	"syspll1_d4",
	"univpll_d5",
	"clk_null",
	"univpll_d7"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sata_parents[] = अणु
	"clkxtal",
	"univpll2_d4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb20_parents[] = अणु
	"clkxtal",
	"univpll3_d4",
	"syspll1_d8"
पूर्ण;

अटल स्थिर अक्षर * स्थिर aud1_parents[] = अणु
	"clkxtal"
पूर्ण;

अटल स्थिर अक्षर * स्थिर irrx_parents[] = अणु
	"clkxtal",
	"syspll4_d16"
पूर्ण;

अटल स्थिर अक्षर * स्थिर crypto_parents[] = अणु
	"clkxtal",
	"univpll_d3",
	"univpll1_d2",
	"syspll1_d2",
	"univpll_d5",
	"syspll_d5",
	"univpll2_d2",
	"syspll_d2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpt10m_parents[] = अणु
	"clkxtal",
	"clkxtal_d4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर peribus_ck_parents[] = अणु
	"syspll1_d8",
	"syspll1_d4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर infra_mux1_parents[] = अणु
	"clkxtal",
	"armpll",
	"main_core_en",
	"armpll"
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs apmixed_cg_regs = अणु
	.set_ofs = 0x8,
	.clr_ofs = 0x8,
	.sta_ofs = 0x8,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs infra_cg_regs = अणु
	.set_ofs = 0x40,
	.clr_ofs = 0x44,
	.sta_ofs = 0x48,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs peri0_cg_regs = अणु
	.set_ofs = 0x8,
	.clr_ofs = 0x10,
	.sta_ofs = 0x18,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs peri1_cg_regs = अणु
	.set_ofs = 0xC,
	.clr_ofs = 0x14,
	.sta_ofs = 0x1C,
पूर्ण;

अटल स्थिर काष्ठा mtk_pll_data plls[] = अणु
	PLL(CLK_APMIXED_ARMPLL, "armpll", 0x0200, 0x020C, 0x00000001,
	    0, 21, 0x0204, 24, 0, 0x0204, 0),
	PLL(CLK_APMIXED_MAINPLL, "mainpll", 0x0210, 0x021C, 0x00000001,
	    HAVE_RST_BAR, 21, 0x0214, 24, 0, 0x0214, 0),
	PLL(CLK_APMIXED_UNIV2PLL, "univ2pll", 0x0220, 0x022C, 0x00000001,
	    HAVE_RST_BAR, 7, 0x0224, 24, 0, 0x0224, 14),
	PLL(CLK_APMIXED_ETH1PLL, "eth1pll", 0x0300, 0x0310, 0x00000001,
	    0, 21, 0x0300, 1, 0, 0x0304, 0),
	PLL(CLK_APMIXED_ETH2PLL, "eth2pll", 0x0314, 0x0320, 0x00000001,
	    0, 21, 0x0314, 1, 0, 0x0318, 0),
	PLL(CLK_APMIXED_SGMIPLL, "sgmipll", 0x0358, 0x0368, 0x00000001,
	    0, 21, 0x0358, 1, 0, 0x035C, 0),
पूर्ण;

अटल स्थिर काष्ठा mtk_gate apmixed_clks[] = अणु
	GATE_APMIXED(CLK_APMIXED_MAIN_CORE_EN, "main_core_en", "mainpll", 5),
पूर्ण;

अटल स्थिर काष्ठा mtk_gate infra_clks[] = अणु
	GATE_INFRA(CLK_INFRA_DBGCLK_PD, "infra_dbgclk_pd", "hd_faxi", 0),
	GATE_INFRA(CLK_INFRA_TRNG_PD, "infra_trng_pd", "hd_faxi", 2),
	GATE_INFRA(CLK_INFRA_DEVAPC_PD, "infra_devapc_pd", "hd_faxi", 4),
	GATE_INFRA(CLK_INFRA_APXGPT_PD, "infra_apxgpt_pd", "infrao_10m", 18),
	GATE_INFRA(CLK_INFRA_SEJ_PD, "infra_sej_pd", "infrao_10m", 19),
पूर्ण;

अटल स्थिर काष्ठा mtk_fixed_clk top_fixed_clks[] = अणु
	FIXED_CLK(CLK_TOP_TO_U2_PHY, "to_u2_phy", "clkxtal",
		  31250000),
	FIXED_CLK(CLK_TOP_TO_U2_PHY_1P, "to_u2_phy_1p", "clkxtal",
		  31250000),
	FIXED_CLK(CLK_TOP_PCIE0_PIPE_EN, "pcie0_pipe_en", "clkxtal",
		  125000000),
	FIXED_CLK(CLK_TOP_PCIE1_PIPE_EN, "pcie1_pipe_en", "clkxtal",
		  125000000),
	FIXED_CLK(CLK_TOP_SSUSB_TX250M, "ssusb_tx250m", "clkxtal",
		  250000000),
	FIXED_CLK(CLK_TOP_SSUSB_EQ_RX250M, "ssusb_eq_rx250m", "clkxtal",
		  250000000),
	FIXED_CLK(CLK_TOP_SSUSB_CDR_REF, "ssusb_cdr_ref", "clkxtal",
		  33333333),
	FIXED_CLK(CLK_TOP_SSUSB_CDR_FB, "ssusb_cdr_fb", "clkxtal",
		  50000000),
	FIXED_CLK(CLK_TOP_SATA_ASIC, "sata_asic", "clkxtal",
		  50000000),
	FIXED_CLK(CLK_TOP_SATA_RBC, "sata_rbc", "clkxtal",
		  50000000),
पूर्ण;

अटल स्थिर काष्ठा mtk_fixed_factor top_भागs[] = अणु
	FACTOR(CLK_TOP_TO_USB3_SYS, "to_usb3_sys", "eth1pll", 1, 4),
	FACTOR(CLK_TOP_P1_1MHZ, "p1_1mhz", "eth1pll", 1, 500),
	FACTOR(CLK_TOP_4MHZ, "free_run_4mhz", "eth1pll", 1, 125),
	FACTOR(CLK_TOP_P0_1MHZ, "p0_1mhz", "eth1pll", 1, 500),
	FACTOR(CLK_TOP_ETH_500M, "eth_500m", "eth1pll", 1, 1),
	FACTOR(CLK_TOP_TXCLK_SRC_PRE, "txclk_src_pre", "sgmiipll_d2", 1, 1),
	FACTOR(CLK_TOP_RTC, "rtc", "clkxtal", 1, 1024),
	FACTOR(CLK_TOP_PWM_QTR_26M, "pwm_qtr_26m", "clkxtal", 1, 1),
	FACTOR(CLK_TOP_CPUM_TCK_IN, "cpum_tck_in", "cpum_tck", 1, 1),
	FACTOR(CLK_TOP_TO_USB3_DA_TOP, "to_usb3_da_top", "clkxtal", 1, 1),
	FACTOR(CLK_TOP_MEMPLL, "mempll", "clkxtal", 32, 1),
	FACTOR(CLK_TOP_DMPLL, "dmpll_ck", "mempll", 1, 1),
	FACTOR(CLK_TOP_DMPLL_D4, "dmpll_d4", "mempll", 1, 4),
	FACTOR(CLK_TOP_DMPLL_D8, "dmpll_d8", "mempll", 1, 8),
	FACTOR(CLK_TOP_SYSPLL_D2, "syspll_d2", "mainpll", 1, 2),
	FACTOR(CLK_TOP_SYSPLL1_D2, "syspll1_d2", "mainpll", 1, 4),
	FACTOR(CLK_TOP_SYSPLL1_D4, "syspll1_d4", "mainpll", 1, 8),
	FACTOR(CLK_TOP_SYSPLL1_D8, "syspll1_d8", "mainpll", 1, 16),
	FACTOR(CLK_TOP_SYSPLL1_D16, "syspll1_d16", "mainpll", 1, 32),
	FACTOR(CLK_TOP_SYSPLL2_D2, "syspll2_d2", "mainpll", 1, 6),
	FACTOR(CLK_TOP_SYSPLL2_D4, "syspll2_d4", "mainpll", 1, 12),
	FACTOR(CLK_TOP_SYSPLL2_D8, "syspll2_d8", "mainpll", 1, 24),
	FACTOR(CLK_TOP_SYSPLL_D5, "syspll_d5", "mainpll", 1, 5),
	FACTOR(CLK_TOP_SYSPLL3_D2, "syspll3_d2", "mainpll", 1, 10),
	FACTOR(CLK_TOP_SYSPLL3_D4, "syspll3_d4", "mainpll", 1, 20),
	FACTOR(CLK_TOP_SYSPLL_D7, "syspll_d7", "mainpll", 1, 7),
	FACTOR(CLK_TOP_SYSPLL4_D2, "syspll4_d2", "mainpll", 1, 14),
	FACTOR(CLK_TOP_SYSPLL4_D4, "syspll4_d4", "mainpll", 1, 28),
	FACTOR(CLK_TOP_SYSPLL4_D16, "syspll4_d16", "mainpll", 1, 112),
	FACTOR(CLK_TOP_UNIVPLL, "univpll", "univ2pll", 1, 2),
	FACTOR(CLK_TOP_UNIVPLL1_D2, "univpll1_d2", "univpll", 1, 4),
	FACTOR(CLK_TOP_UNIVPLL1_D4, "univpll1_d4", "univpll", 1, 8),
	FACTOR(CLK_TOP_UNIVPLL1_D8, "univpll1_d8", "univpll", 1, 16),
	FACTOR(CLK_TOP_UNIVPLL_D3, "univpll_d3", "univpll", 1, 3),
	FACTOR(CLK_TOP_UNIVPLL2_D2, "univpll2_d2", "univpll", 1, 6),
	FACTOR(CLK_TOP_UNIVPLL2_D4, "univpll2_d4", "univpll", 1, 12),
	FACTOR(CLK_TOP_UNIVPLL2_D8, "univpll2_d8", "univpll", 1, 24),
	FACTOR(CLK_TOP_UNIVPLL2_D16, "univpll2_d16", "univpll", 1, 48),
	FACTOR(CLK_TOP_UNIVPLL_D5, "univpll_d5", "univpll", 1, 5),
	FACTOR(CLK_TOP_UNIVPLL3_D2, "univpll3_d2", "univpll", 1, 10),
	FACTOR(CLK_TOP_UNIVPLL3_D4, "univpll3_d4", "univpll", 1, 20),
	FACTOR(CLK_TOP_UNIVPLL3_D16, "univpll3_d16", "univpll", 1, 80),
	FACTOR(CLK_TOP_UNIVPLL_D7, "univpll_d7", "univpll", 1, 7),
	FACTOR(CLK_TOP_UNIVPLL_D80_D4, "univpll_d80_d4", "univpll", 1, 320),
	FACTOR(CLK_TOP_UNIV48M, "univ48m", "univpll", 1, 25),
	FACTOR(CLK_TOP_SGMIIPLL_D2, "sgmiipll_d2", "sgmipll", 1, 2),
	FACTOR(CLK_TOP_CLKXTAL_D4, "clkxtal_d4", "clkxtal", 1, 4),
	FACTOR(CLK_TOP_HD_FAXI, "hd_faxi", "axi_sel", 1, 1),
	FACTOR(CLK_TOP_FAXI, "faxi", "axi_sel", 1, 1),
	FACTOR(CLK_TOP_F_FAUD_INTBUS, "f_faud_intbus", "aud_intbus_sel", 1, 1),
	FACTOR(CLK_TOP_AP2WBHIF_HCLK, "ap2wbhif_hclk", "syspll1_d8", 1, 1),
	FACTOR(CLK_TOP_10M_INFRAO, "infrao_10m", "gpt10m_sel", 1, 1),
	FACTOR(CLK_TOP_MSDC30_1, "msdc30_1", "msdc30_1_sel", 1, 1),
	FACTOR(CLK_TOP_SPI, "spi", "spi0_sel", 1, 1),
	FACTOR(CLK_TOP_SF, "sf", "nfi_infra_sel", 1, 1),
	FACTOR(CLK_TOP_FLASH, "flash", "flash_sel", 1, 1),
	FACTOR(CLK_TOP_TO_USB3_REF, "to_usb3_ref", "sata_sel", 1, 4),
	FACTOR(CLK_TOP_TO_USB3_MCU, "to_usb3_mcu", "axi_sel", 1, 1),
	FACTOR(CLK_TOP_TO_USB3_DMA, "to_usb3_dma", "hif_sel", 1, 1),
	FACTOR(CLK_TOP_FROM_TOP_AHB, "from_top_ahb", "axi_sel", 1, 1),
	FACTOR(CLK_TOP_FROM_TOP_AXI, "from_top_axi", "hif_sel", 1, 1),
	FACTOR(CLK_TOP_PCIE1_MAC_EN, "pcie1_mac_en", "sata_sel", 1, 1),
	FACTOR(CLK_TOP_PCIE0_MAC_EN, "pcie0_mac_en", "sata_sel", 1, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_gate peri_clks[] = अणु
	/* PERI0 */
	GATE_PERI0(CLK_PERI_PWM1_PD, "peri_pwm1_pd", "pwm_qtr_26m", 2),
	GATE_PERI0(CLK_PERI_PWM2_PD, "peri_pwm2_pd", "pwm_qtr_26m", 3),
	GATE_PERI0(CLK_PERI_PWM3_PD, "peri_pwm3_pd", "pwm_qtr_26m", 4),
	GATE_PERI0(CLK_PERI_PWM4_PD, "peri_pwm4_pd", "pwm_qtr_26m", 5),
	GATE_PERI0(CLK_PERI_PWM5_PD, "peri_pwm5_pd", "pwm_qtr_26m", 6),
	GATE_PERI0(CLK_PERI_PWM6_PD, "peri_pwm6_pd", "pwm_qtr_26m", 7),
	GATE_PERI0(CLK_PERI_PWM7_PD, "peri_pwm7_pd", "pwm_qtr_26m", 8),
	GATE_PERI0(CLK_PERI_PWM_PD, "peri_pwm_pd", "pwm_qtr_26m", 9),
	GATE_PERI0(CLK_PERI_AP_DMA_PD, "peri_ap_dma_pd", "faxi", 12),
	GATE_PERI0(CLK_PERI_MSDC30_1_PD, "peri_msdc30_1", "msdc30_1", 14),
	GATE_PERI0(CLK_PERI_UART0_PD, "peri_uart0_pd", "faxi", 17),
	GATE_PERI0(CLK_PERI_UART1_PD, "peri_uart1_pd", "faxi", 18),
	GATE_PERI0(CLK_PERI_UART2_PD, "peri_uart2_pd", "faxi", 19),
	GATE_PERI0(CLK_PERI_UART3_PD, "peri_uart3_pd", "faxi", 20),
	GATE_PERI0(CLK_PERI_BTIF_PD, "peri_btif_pd", "faxi", 22),
	GATE_PERI0(CLK_PERI_I2C0_PD, "peri_i2c0_pd", "faxi", 23),
	GATE_PERI0(CLK_PERI_SPI0_PD, "peri_spi0_pd", "spi", 28),
	GATE_PERI0(CLK_PERI_SNFI_PD, "peri_snfi_pd", "sf", 29),
	GATE_PERI0(CLK_PERI_NFI_PD, "peri_nfi_pd", "faxi", 30),
	GATE_PERI0(CLK_PERI_NFIECC_PD, "peri_nfiecc_pd", "faxi", 31),
	/* PERI1 */
	GATE_PERI1(CLK_PERI_FLASH_PD, "peri_flash_pd", "flash", 1),
पूर्ण;

अटल काष्ठा mtk_composite infra_muxes[] = अणु
	/* INFRA_TOPCKGEN_CKMUXSEL */
	MUX(CLK_INFRA_MUX1_SEL, "infra_mux1_sel", infra_mux1_parents, 0x000,
	    2, 2),
पूर्ण;

अटल काष्ठा mtk_composite top_muxes[] = अणु
	/* CLK_CFG_0 */
	MUX_GATE(CLK_TOP_AXI_SEL, "axi_sel", axi_parents,
		 0x040, 0, 3, 7),
	MUX_GATE(CLK_TOP_MEM_SEL, "mem_sel", mem_parents,
		 0x040, 8, 1, 15),
	MUX_GATE(CLK_TOP_DDRPHYCFG_SEL, "ddrphycfg_sel", ddrphycfg_parents,
		 0x040, 16, 1, 23),
	MUX_GATE(CLK_TOP_ETH_SEL, "eth_sel", eth_parents,
		 0x040, 24, 3, 31),
	/* CLK_CFG_1 */
	MUX_GATE(CLK_TOP_PWM_SEL, "pwm_sel", pwm_parents,
		 0x050, 0, 2, 7),
	MUX_GATE(CLK_TOP_F10M_REF_SEL, "f10m_ref_sel", f10m_ref_parents,
		 0x050, 8, 1, 15),
	MUX_GATE(CLK_TOP_NFI_INFRA_SEL, "nfi_infra_sel", nfi_infra_parents,
		 0x050, 16, 4, 23),
	MUX_GATE(CLK_TOP_FLASH_SEL, "flash_sel", flash_parents,
		 0x050, 24, 3, 31),
	/* CLK_CFG_2 */
	MUX_GATE(CLK_TOP_UART_SEL, "uart_sel", uart_parents,
		 0x060, 0, 1, 7),
	MUX_GATE(CLK_TOP_SPI0_SEL, "spi0_sel", spi0_parents,
		 0x060, 8, 3, 15),
	MUX_GATE(CLK_TOP_SPI1_SEL, "spi1_sel", spi1_parents,
		 0x060, 16, 3, 23),
	MUX_GATE(CLK_TOP_MSDC50_0_SEL, "msdc50_0_sel", uart_parents,
		 0x060, 24, 3, 31),
	/* CLK_CFG_3 */
	MUX_GATE(CLK_TOP_MSDC30_0_SEL, "msdc30_0_sel", msdc30_0_parents,
		 0x070, 0, 3, 7),
	MUX_GATE(CLK_TOP_MSDC30_1_SEL, "msdc30_1_sel", msdc30_1_parents,
		 0x070, 8, 3, 15),
	MUX_GATE(CLK_TOP_AP2WBMCU_SEL, "ap2wbmcu_sel", ap2wbmcu_parents,
		 0x070, 16, 3, 23),
	MUX_GATE(CLK_TOP_AP2WBHIF_SEL, "ap2wbhif_sel", ap2wbmcu_parents,
		 0x070, 24, 3, 31),
	/* CLK_CFG_4 */
	MUX_GATE(CLK_TOP_AUDIO_SEL, "audio_sel", audio_parents,
		 0x080, 0, 2, 7),
	MUX_GATE(CLK_TOP_AUD_INTBUS_SEL, "aud_intbus_sel", aud_पूर्णांकbus_parents,
		 0x080, 8, 2, 15),
	MUX_GATE(CLK_TOP_PMICSPI_SEL, "pmicspi_sel", pmicspi_parents,
		 0x080, 16, 3, 23),
	MUX_GATE(CLK_TOP_SCP_SEL, "scp_sel", scp_parents,
		 0x080, 24, 2, 31),
	/* CLK_CFG_5 */
	MUX_GATE(CLK_TOP_ATB_SEL, "atb_sel", atb_parents,
		 0x090, 0, 2, 7),
	MUX_GATE(CLK_TOP_HIF_SEL, "hif_sel", hअगर_parents,
		 0x090, 8, 3, 15),
	MUX_GATE(CLK_TOP_SATA_SEL, "sata_sel", sata_parents,
		 0x090, 16, 1, 23),
	MUX_GATE(CLK_TOP_U2_SEL, "usb20_sel", usb20_parents,
		 0x090, 24, 2, 31),
	/* CLK_CFG_6 */
	MUX_GATE(CLK_TOP_AUD1_SEL, "aud1_sel", aud1_parents,
		 0x0A0, 0, 1, 7),
	MUX_GATE(CLK_TOP_AUD2_SEL, "aud2_sel", aud1_parents,
		 0x0A0, 8, 1, 15),
	MUX_GATE(CLK_TOP_IRRX_SEL, "irrx_sel", irrx_parents,
		 0x0A0, 16, 1, 23),
	MUX_GATE(CLK_TOP_IRTX_SEL, "irtx_sel", irrx_parents,
		 0x0A0, 24, 1, 31),
	/* CLK_CFG_7 */
	MUX_GATE(CLK_TOP_SATA_MCU_SEL, "sata_mcu_sel", scp_parents,
		 0x0B0, 0, 2, 7),
	MUX_GATE(CLK_TOP_PCIE0_MCU_SEL, "pcie0_mcu_sel", scp_parents,
		 0x0B0, 8, 2, 15),
	MUX_GATE(CLK_TOP_PCIE1_MCU_SEL, "pcie1_mcu_sel", scp_parents,
		 0x0B0, 16, 2, 23),
	MUX_GATE(CLK_TOP_SSUSB_MCU_SEL, "ssusb_mcu_sel", scp_parents,
		 0x0B0, 24, 2, 31),
	/* CLK_CFG_8 */
	MUX_GATE(CLK_TOP_CRYPTO_SEL, "crypto_sel", crypto_parents,
		 0x0C0, 0, 3, 7),
	MUX_GATE(CLK_TOP_SGMII_REF_1_SEL, "sgmii_ref_1_sel", f10m_ref_parents,
		 0x0C0, 8, 1, 15),
	MUX_GATE(CLK_TOP_10M_SEL, "gpt10m_sel", gpt10m_parents,
		 0x0C0, 16, 1, 23),
पूर्ण;

अटल काष्ठा mtk_composite peri_muxes[] = अणु
	/* PERI_GLOBALCON_CKSEL */
	MUX(CLK_PERIBUS_SEL, "peribus_ck_sel", peribus_ck_parents, 0x05C, 0, 1),
पूर्ण;

अटल पूर्णांक mtk_topckgen_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	व्योम __iomem *base;
	काष्ठा device_node *node = pdev->dev.of_node;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	clk_data = mtk_alloc_clk_data(CLK_TOP_NR_CLK);

	mtk_clk_रेजिस्टर_fixed_clks(top_fixed_clks, ARRAY_SIZE(top_fixed_clks),
				    clk_data);

	mtk_clk_रेजिस्टर_factors(top_भागs, ARRAY_SIZE(top_भागs),
				 clk_data);

	mtk_clk_रेजिस्टर_composites(top_muxes, ARRAY_SIZE(top_muxes),
				    base, &mt7629_clk_lock, clk_data);

	clk_prepare_enable(clk_data->clks[CLK_TOP_AXI_SEL]);
	clk_prepare_enable(clk_data->clks[CLK_TOP_MEM_SEL]);
	clk_prepare_enable(clk_data->clks[CLK_TOP_DDRPHYCFG_SEL]);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल पूर्णांक mtk_infrasys_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा clk_onecell_data *clk_data;

	clk_data = mtk_alloc_clk_data(CLK_INFRA_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, infra_clks, ARRAY_SIZE(infra_clks),
			       clk_data);

	mtk_clk_रेजिस्टर_cpumuxes(node, infra_muxes, ARRAY_SIZE(infra_muxes),
				  clk_data);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get,
				   clk_data);
पूर्ण

अटल पूर्णांक mtk_pericfg_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	व्योम __iomem *base;
	पूर्णांक r;
	काष्ठा device_node *node = pdev->dev.of_node;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	clk_data = mtk_alloc_clk_data(CLK_PERI_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, peri_clks, ARRAY_SIZE(peri_clks),
			       clk_data);

	mtk_clk_रेजिस्टर_composites(peri_muxes, ARRAY_SIZE(peri_muxes), base,
				    &mt7629_clk_lock, clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
	अगर (r)
		वापस r;

	clk_prepare_enable(clk_data->clks[CLK_PERI_UART0_PD]);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_apmixedsys_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_APMIXED_NR_CLK);
	अगर (!clk_data)
		वापस -ENOMEM;

	mtk_clk_रेजिस्टर_plls(node, plls, ARRAY_SIZE(plls),
			      clk_data);

	mtk_clk_रेजिस्टर_gates(node, apmixed_clks,
			       ARRAY_SIZE(apmixed_clks), clk_data);

	clk_prepare_enable(clk_data->clks[CLK_APMIXED_ARMPLL]);
	clk_prepare_enable(clk_data->clks[CLK_APMIXED_MAIN_CORE_EN]);

	वापस of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
पूर्ण


अटल स्थिर काष्ठा of_device_id of_match_clk_mt7629[] = अणु
	अणु
		.compatible = "mediatek,mt7629-apmixedsys",
		.data = mtk_apmixedsys_init,
	पूर्ण, अणु
		.compatible = "mediatek,mt7629-infracfg",
		.data = mtk_infrasys_init,
	पूर्ण, अणु
		.compatible = "mediatek,mt7629-topckgen",
		.data = mtk_topckgen_init,
	पूर्ण, अणु
		.compatible = "mediatek,mt7629-pericfg",
		.data = mtk_pericfg_init,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

अटल पूर्णांक clk_mt7629_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक (*clk_init)(काष्ठा platक्रमm_device *);
	पूर्णांक r;

	clk_init = of_device_get_match_data(&pdev->dev);
	अगर (!clk_init)
		वापस -EINVAL;

	r = clk_init(pdev);
	अगर (r)
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);

	वापस r;
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt7629_drv = अणु
	.probe = clk_mt7629_probe,
	.driver = अणु
		.name = "clk-mt7629",
		.of_match_table = of_match_clk_mt7629,
	पूर्ण,
पूर्ण;

अटल पूर्णांक clk_mt7629_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&clk_mt7629_drv);
पूर्ण

arch_initcall(clk_mt7629_init);
