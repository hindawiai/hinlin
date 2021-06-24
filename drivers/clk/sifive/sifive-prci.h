<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018-2019 SiFive, Inc.
 * Wesley Terpstra
 * Paul Walmsley
 * Zong Li
 */

#अगर_अघोषित __SIFIVE_CLK_SIFIVE_PRCI_H
#घोषणा __SIFIVE_CLK_SIFIVE_PRCI_H

#समावेश <linux/clk/analogbits-wrpll-cln28hpc.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/reset/reset-simple.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * EXPECTED_CLK_PARENT_COUNT: how many parent घड़ीs this driver expects:
 *     hfclk and rtcclk
 */
#घोषणा EXPECTED_CLK_PARENT_COUNT 2

/*
 * Register offsets and biपंचांगasks
 */

/* COREPLLCFG0 */
#घोषणा PRCI_COREPLLCFG0_OFFSET		0x4
#घोषणा PRCI_COREPLLCFG0_DIVR_SHIFT	0
#घोषणा PRCI_COREPLLCFG0_DIVR_MASK	(0x3f << PRCI_COREPLLCFG0_DIVR_SHIFT)
#घोषणा PRCI_COREPLLCFG0_DIVF_SHIFT	6
#घोषणा PRCI_COREPLLCFG0_DIVF_MASK	(0x1ff << PRCI_COREPLLCFG0_DIVF_SHIFT)
#घोषणा PRCI_COREPLLCFG0_DIVQ_SHIFT	15
#घोषणा PRCI_COREPLLCFG0_DIVQ_MASK	(0x7 << PRCI_COREPLLCFG0_DIVQ_SHIFT)
#घोषणा PRCI_COREPLLCFG0_RANGE_SHIFT	18
#घोषणा PRCI_COREPLLCFG0_RANGE_MASK	(0x7 << PRCI_COREPLLCFG0_RANGE_SHIFT)
#घोषणा PRCI_COREPLLCFG0_BYPASS_SHIFT	24
#घोषणा PRCI_COREPLLCFG0_BYPASS_MASK	(0x1 << PRCI_COREPLLCFG0_BYPASS_SHIFT)
#घोषणा PRCI_COREPLLCFG0_FSE_SHIFT	25
#घोषणा PRCI_COREPLLCFG0_FSE_MASK	(0x1 << PRCI_COREPLLCFG0_FSE_SHIFT)
#घोषणा PRCI_COREPLLCFG0_LOCK_SHIFT	31
#घोषणा PRCI_COREPLLCFG0_LOCK_MASK	(0x1 << PRCI_COREPLLCFG0_LOCK_SHIFT)

/* COREPLLCFG1 */
#घोषणा PRCI_COREPLLCFG1_OFFSET		0x8
#घोषणा PRCI_COREPLLCFG1_CKE_SHIFT	31
#घोषणा PRCI_COREPLLCFG1_CKE_MASK	(0x1 << PRCI_COREPLLCFG1_CKE_SHIFT)

/* DDRPLLCFG0 */
#घोषणा PRCI_DDRPLLCFG0_OFFSET		0xc
#घोषणा PRCI_DDRPLLCFG0_DIVR_SHIFT	0
#घोषणा PRCI_DDRPLLCFG0_DIVR_MASK	(0x3f << PRCI_DDRPLLCFG0_DIVR_SHIFT)
#घोषणा PRCI_DDRPLLCFG0_DIVF_SHIFT	6
#घोषणा PRCI_DDRPLLCFG0_DIVF_MASK	(0x1ff << PRCI_DDRPLLCFG0_DIVF_SHIFT)
#घोषणा PRCI_DDRPLLCFG0_DIVQ_SHIFT	15
#घोषणा PRCI_DDRPLLCFG0_DIVQ_MASK	(0x7 << PRCI_DDRPLLCFG0_DIVQ_SHIFT)
#घोषणा PRCI_DDRPLLCFG0_RANGE_SHIFT	18
#घोषणा PRCI_DDRPLLCFG0_RANGE_MASK	(0x7 << PRCI_DDRPLLCFG0_RANGE_SHIFT)
#घोषणा PRCI_DDRPLLCFG0_BYPASS_SHIFT	24
#घोषणा PRCI_DDRPLLCFG0_BYPASS_MASK	(0x1 << PRCI_DDRPLLCFG0_BYPASS_SHIFT)
#घोषणा PRCI_DDRPLLCFG0_FSE_SHIFT	25
#घोषणा PRCI_DDRPLLCFG0_FSE_MASK	(0x1 << PRCI_DDRPLLCFG0_FSE_SHIFT)
#घोषणा PRCI_DDRPLLCFG0_LOCK_SHIFT	31
#घोषणा PRCI_DDRPLLCFG0_LOCK_MASK	(0x1 << PRCI_DDRPLLCFG0_LOCK_SHIFT)

/* DDRPLLCFG1 */
#घोषणा PRCI_DDRPLLCFG1_OFFSET		0x10
#घोषणा PRCI_DDRPLLCFG1_CKE_SHIFT	31
#घोषणा PRCI_DDRPLLCFG1_CKE_MASK	(0x1 << PRCI_DDRPLLCFG1_CKE_SHIFT)

/* PCIEAUX */
#घोषणा PRCI_PCIE_AUX_OFFSET		0x14
#घोषणा PRCI_PCIE_AUX_EN_SHIFT		0
#घोषणा PRCI_PCIE_AUX_EN_MASK		(0x1 << PRCI_PCIE_AUX_EN_SHIFT)

/* GEMGXLPLLCFG0 */
#घोषणा PRCI_GEMGXLPLLCFG0_OFFSET	0x1c
#घोषणा PRCI_GEMGXLPLLCFG0_DIVR_SHIFT	0
#घोषणा PRCI_GEMGXLPLLCFG0_DIVR_MASK	(0x3f << PRCI_GEMGXLPLLCFG0_DIVR_SHIFT)
#घोषणा PRCI_GEMGXLPLLCFG0_DIVF_SHIFT	6
#घोषणा PRCI_GEMGXLPLLCFG0_DIVF_MASK	(0x1ff << PRCI_GEMGXLPLLCFG0_DIVF_SHIFT)
#घोषणा PRCI_GEMGXLPLLCFG0_DIVQ_SHIFT	15
#घोषणा PRCI_GEMGXLPLLCFG0_DIVQ_MASK	(0x7 << PRCI_GEMGXLPLLCFG0_DIVQ_SHIFT)
#घोषणा PRCI_GEMGXLPLLCFG0_RANGE_SHIFT	18
#घोषणा PRCI_GEMGXLPLLCFG0_RANGE_MASK	(0x7 << PRCI_GEMGXLPLLCFG0_RANGE_SHIFT)
#घोषणा PRCI_GEMGXLPLLCFG0_BYPASS_SHIFT	24
#घोषणा PRCI_GEMGXLPLLCFG0_BYPASS_MASK	(0x1 << PRCI_GEMGXLPLLCFG0_BYPASS_SHIFT)
#घोषणा PRCI_GEMGXLPLLCFG0_FSE_SHIFT	25
#घोषणा PRCI_GEMGXLPLLCFG0_FSE_MASK	(0x1 << PRCI_GEMGXLPLLCFG0_FSE_SHIFT)
#घोषणा PRCI_GEMGXLPLLCFG0_LOCK_SHIFT	31
#घोषणा PRCI_GEMGXLPLLCFG0_LOCK_MASK	(0x1 << PRCI_GEMGXLPLLCFG0_LOCK_SHIFT)

/* GEMGXLPLLCFG1 */
#घोषणा PRCI_GEMGXLPLLCFG1_OFFSET	0x20
#घोषणा PRCI_GEMGXLPLLCFG1_CKE_SHIFT	31
#घोषणा PRCI_GEMGXLPLLCFG1_CKE_MASK	(0x1 << PRCI_GEMGXLPLLCFG1_CKE_SHIFT)

/* CORECLKSEL */
#घोषणा PRCI_CORECLKSEL_OFFSET			0x24
#घोषणा PRCI_CORECLKSEL_CORECLKSEL_SHIFT	0
#घोषणा PRCI_CORECLKSEL_CORECLKSEL_MASK					\
		(0x1 << PRCI_CORECLKSEL_CORECLKSEL_SHIFT)

/* DEVICESRESETREG */
#घोषणा PRCI_DEVICESRESETREG_OFFSET				0x28
#घोषणा PRCI_DEVICESRESETREG_DDR_CTRL_RST_N_SHIFT		0
#घोषणा PRCI_DEVICESRESETREG_DDR_CTRL_RST_N_MASK			\
		(0x1 << PRCI_DEVICESRESETREG_DDR_CTRL_RST_N_SHIFT)
#घोषणा PRCI_DEVICESRESETREG_DDR_AXI_RST_N_SHIFT		1
#घोषणा PRCI_DEVICESRESETREG_DDR_AXI_RST_N_MASK				\
		(0x1 << PRCI_DEVICESRESETREG_DDR_AXI_RST_N_SHIFT)
#घोषणा PRCI_DEVICESRESETREG_DDR_AHB_RST_N_SHIFT		2
#घोषणा PRCI_DEVICESRESETREG_DDR_AHB_RST_N_MASK				\
		(0x1 << PRCI_DEVICESRESETREG_DDR_AHB_RST_N_SHIFT)
#घोषणा PRCI_DEVICESRESETREG_DDR_PHY_RST_N_SHIFT		3
#घोषणा PRCI_DEVICESRESETREG_DDR_PHY_RST_N_MASK				\
		(0x1 << PRCI_DEVICESRESETREG_DDR_PHY_RST_N_SHIFT)
#घोषणा PRCI_DEVICESRESETREG_GEMGXL_RST_N_SHIFT			5
#घोषणा PRCI_DEVICESRESETREG_GEMGXL_RST_N_MASK				\
		(0x1 << PRCI_DEVICESRESETREG_GEMGXL_RST_N_SHIFT)
#घोषणा PRCI_DEVICESRESETREG_CHIPLINK_RST_N_SHIFT		6
#घोषणा PRCI_DEVICESRESETREG_CHIPLINK_RST_N_MASK			\
		(0x1 << PRCI_DEVICESRESETREG_CHIPLINK_RST_N_SHIFT)

#घोषणा PRCI_RST_NR						7

/* CLKMUXSTATUSREG */
#घोषणा PRCI_CLKMUXSTATUSREG_OFFSET				0x2c
#घोषणा PRCI_CLKMUXSTATUSREG_TLCLKSEL_STATUS_SHIFT		1
#घोषणा PRCI_CLKMUXSTATUSREG_TLCLKSEL_STATUS_MASK			\
		(0x1 << PRCI_CLKMUXSTATUSREG_TLCLKSEL_STATUS_SHIFT)

/* CLTXPLLCFG0 */
#घोषणा PRCI_CLTXPLLCFG0_OFFSET		0x30
#घोषणा PRCI_CLTXPLLCFG0_DIVR_SHIFT	0
#घोषणा PRCI_CLTXPLLCFG0_DIVR_MASK	(0x3f << PRCI_CLTXPLLCFG0_DIVR_SHIFT)
#घोषणा PRCI_CLTXPLLCFG0_DIVF_SHIFT	6
#घोषणा PRCI_CLTXPLLCFG0_DIVF_MASK	(0x1ff << PRCI_CLTXPLLCFG0_DIVF_SHIFT)
#घोषणा PRCI_CLTXPLLCFG0_DIVQ_SHIFT	15
#घोषणा PRCI_CLTXPLLCFG0_DIVQ_MASK	(0x7 << PRCI_CLTXPLLCFG0_DIVQ_SHIFT)
#घोषणा PRCI_CLTXPLLCFG0_RANGE_SHIFT	18
#घोषणा PRCI_CLTXPLLCFG0_RANGE_MASK	(0x7 << PRCI_CLTXPLLCFG0_RANGE_SHIFT)
#घोषणा PRCI_CLTXPLLCFG0_BYPASS_SHIFT	24
#घोषणा PRCI_CLTXPLLCFG0_BYPASS_MASK	(0x1 << PRCI_CLTXPLLCFG0_BYPASS_SHIFT)
#घोषणा PRCI_CLTXPLLCFG0_FSE_SHIFT	25
#घोषणा PRCI_CLTXPLLCFG0_FSE_MASK	(0x1 << PRCI_CLTXPLLCFG0_FSE_SHIFT)
#घोषणा PRCI_CLTXPLLCFG0_LOCK_SHIFT	31
#घोषणा PRCI_CLTXPLLCFG0_LOCK_MASK	(0x1 << PRCI_CLTXPLLCFG0_LOCK_SHIFT)

/* CLTXPLLCFG1 */
#घोषणा PRCI_CLTXPLLCFG1_OFFSET		0x34
#घोषणा PRCI_CLTXPLLCFG1_CKE_SHIFT	31
#घोषणा PRCI_CLTXPLLCFG1_CKE_MASK	(0x1 << PRCI_CLTXPLLCFG1_CKE_SHIFT)

/* DVFSCOREPLLCFG0 */
#घोषणा PRCI_DVFSCOREPLLCFG0_OFFSET	0x38

/* DVFSCOREPLLCFG1 */
#घोषणा PRCI_DVFSCOREPLLCFG1_OFFSET	0x3c
#घोषणा PRCI_DVFSCOREPLLCFG1_CKE_SHIFT	31
#घोषणा PRCI_DVFSCOREPLLCFG1_CKE_MASK	(0x1 << PRCI_DVFSCOREPLLCFG1_CKE_SHIFT)

/* COREPLLSEL */
#घोषणा PRCI_COREPLLSEL_OFFSET			0x40
#घोषणा PRCI_COREPLLSEL_COREPLLSEL_SHIFT	0
#घोषणा PRCI_COREPLLSEL_COREPLLSEL_MASK					\
		(0x1 << PRCI_COREPLLSEL_COREPLLSEL_SHIFT)

/* HFPCLKPLLCFG0 */
#घोषणा PRCI_HFPCLKPLLCFG0_OFFSET		0x50
#घोषणा PRCI_HFPCLKPLL_CFG0_DIVR_SHIFT		0
#घोषणा PRCI_HFPCLKPLL_CFG0_DIVR_MASK					\
		(0x3f << PRCI_HFPCLKPLLCFG0_DIVR_SHIFT)
#घोषणा PRCI_HFPCLKPLL_CFG0_DIVF_SHIFT		6
#घोषणा PRCI_HFPCLKPLL_CFG0_DIVF_MASK					\
		(0x1ff << PRCI_HFPCLKPLLCFG0_DIVF_SHIFT)
#घोषणा PRCI_HFPCLKPLL_CFG0_DIVQ_SHIFT		15
#घोषणा PRCI_HFPCLKPLL_CFG0_DIVQ_MASK					\
		(0x7 << PRCI_HFPCLKPLLCFG0_DIVQ_SHIFT)
#घोषणा PRCI_HFPCLKPLL_CFG0_RANGE_SHIFT		18
#घोषणा PRCI_HFPCLKPLL_CFG0_RANGE_MASK					\
		(0x7 << PRCI_HFPCLKPLLCFG0_RANGE_SHIFT)
#घोषणा PRCI_HFPCLKPLL_CFG0_BYPASS_SHIFT	24
#घोषणा PRCI_HFPCLKPLL_CFG0_BYPASS_MASK					\
		(0x1 << PRCI_HFPCLKPLLCFG0_BYPASS_SHIFT)
#घोषणा PRCI_HFPCLKPLL_CFG0_FSE_SHIFT		25
#घोषणा PRCI_HFPCLKPLL_CFG0_FSE_MASK					\
		(0x1 << PRCI_HFPCLKPLLCFG0_FSE_SHIFT)
#घोषणा PRCI_HFPCLKPLL_CFG0_LOCK_SHIFT		31
#घोषणा PRCI_HFPCLKPLL_CFG0_LOCK_MASK					\
		(0x1 << PRCI_HFPCLKPLLCFG0_LOCK_SHIFT)

/* HFPCLKPLLCFG1 */
#घोषणा PRCI_HFPCLKPLLCFG1_OFFSET		0x54
#घोषणा PRCI_HFPCLKPLLCFG1_CKE_SHIFT		31
#घोषणा PRCI_HFPCLKPLLCFG1_CKE_MASK					\
		(0x1 << PRCI_HFPCLKPLLCFG1_CKE_SHIFT)

/* HFPCLKPLLSEL */
#घोषणा PRCI_HFPCLKPLLSEL_OFFSET		0x58
#घोषणा PRCI_HFPCLKPLLSEL_HFPCLKPLLSEL_SHIFT	0
#घोषणा PRCI_HFPCLKPLLSEL_HFPCLKPLLSEL_MASK				\
		(0x1 << PRCI_HFPCLKPLLSEL_HFPCLKPLLSEL_SHIFT)

/* HFPCLKPLLDIV */
#घोषणा PRCI_HFPCLKPLLDIV_OFFSET		0x5c

/* PRCIPLL */
#घोषणा PRCI_PRCIPLL_OFFSET			0xe0

/* PROCMONCFG */
#घोषणा PRCI_PROCMONCFG_OFFSET			0xf0

/*
 * Private काष्ठाures
 */

/**
 * काष्ठा __prci_data - per-device-instance data
 * @va: base भव address of the PRCI IP block
 * @hw_clks: encapsulates काष्ठा clk_hw records
 *
 * PRCI per-device instance data
 */
काष्ठा __prci_data अणु
	व्योम __iomem *va;
	काष्ठा reset_simple_data reset;
	काष्ठा clk_hw_onecell_data hw_clks;
पूर्ण;

/**
 * काष्ठा __prci_wrpll_data - WRPLL configuration and पूर्णांकegration data
 * @c: WRPLL current configuration record
 * @enable_bypass: fn ptr to code to bypass the WRPLL (अगर applicable; अन्यथा शून्य)
 * @disable_bypass: fn ptr to code to not bypass the WRPLL (or शून्य)
 * @cfg0_offs: WRPLL CFG0 रेजिस्टर offset (in bytes) from the PRCI base address
 * @cfg1_offs: WRPLL CFG1 रेजिस्टर offset (in bytes) from the PRCI base address
 *
 * @enable_bypass and @disable_bypass are used क्रम WRPLL instances
 * that contain a separate बाह्यal glitchless घड़ी mux करोwnstream
 * from the PLL.  The WRPLL पूर्णांकernal bypass mux is not glitchless.
 */
काष्ठा __prci_wrpll_data अणु
	काष्ठा wrpll_cfg c;
	व्योम (*enable_bypass)(काष्ठा __prci_data *pd);
	व्योम (*disable_bypass)(काष्ठा __prci_data *pd);
	u8 cfg0_offs;
	u8 cfg1_offs;
पूर्ण;

/**
 * काष्ठा __prci_घड़ी - describes a घड़ी device managed by PRCI
 * @name: user-पढ़ोable घड़ी name string - should match the manual
 * @parent_name: parent name क्रम this घड़ी
 * @ops: काष्ठा clk_ops क्रम the Linux घड़ी framework to use क्रम control
 * @hw: Linux-निजी घड़ी data
 * @pwd: WRPLL-specअगरic data, associated with this घड़ी (अगर not शून्य)
 * @pd: PRCI-specअगरic data associated with this घड़ी (अगर not शून्य)
 *
 * PRCI घड़ी data.  Used by the PRCI driver to रेजिस्टर PRCI-provided
 * घड़ीs to the Linux घड़ी infraकाष्ठाure.
 */
काष्ठा __prci_घड़ी अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	स्थिर काष्ठा clk_ops *ops;
	काष्ठा clk_hw hw;
	काष्ठा __prci_wrpll_data *pwd;
	काष्ठा __prci_data *pd;
पूर्ण;

#घोषणा clk_hw_to_prci_घड़ी(pwd) container_of(pwd, काष्ठा __prci_घड़ी, hw)

/*
 * काष्ठा prci_clk_desc - describes the inक्रमmation of घड़ीs of each SoCs
 * @clks: poपूर्णांक to a array of __prci_घड़ी
 * @num_clks: the number of element of clks
 */
काष्ठा prci_clk_desc अणु
	काष्ठा __prci_घड़ी *clks;
	माप_प्रकार num_clks;
पूर्ण;

/* Core घड़ी mux control */
व्योम sअगरive_prci_coreclksel_use_hfclk(काष्ठा __prci_data *pd);
व्योम sअगरive_prci_coreclksel_use_corepll(काष्ठा __prci_data *pd);
व्योम sअगरive_prci_coreclksel_use_final_corepll(काष्ठा __prci_data *pd);
व्योम sअगरive_prci_corepllsel_use_dvfscorepll(काष्ठा __prci_data *pd);
व्योम sअगरive_prci_corepllsel_use_corepll(काष्ठा __prci_data *pd);
व्योम sअगरive_prci_hfpclkpllsel_use_hfclk(काष्ठा __prci_data *pd);
व्योम sअगरive_prci_hfpclkpllsel_use_hfpclkpll(काष्ठा __prci_data *pd);

/* Linux घड़ी framework पूर्णांकegration */
दीर्घ sअगरive_prci_wrpll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *parent_rate);
पूर्णांक sअगरive_prci_wrpll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate);
पूर्णांक sअगरive_clk_is_enabled(काष्ठा clk_hw *hw);
पूर्णांक sअगरive_prci_घड़ी_enable(काष्ठा clk_hw *hw);
व्योम sअगरive_prci_घड़ी_disable(काष्ठा clk_hw *hw);
अचिन्हित दीर्घ sअगरive_prci_wrpll_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate);
अचिन्हित दीर्घ sअगरive_prci_tlclksel_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate);
अचिन्हित दीर्घ sअगरive_prci_hfpclkplद_भाग_recalc_rate(काष्ठा clk_hw *hw,
						   अचिन्हित दीर्घ parent_rate);

पूर्णांक sअगरive_prci_pcie_aux_घड़ी_is_enabled(काष्ठा clk_hw *hw);
पूर्णांक sअगरive_prci_pcie_aux_घड़ी_enable(काष्ठा clk_hw *hw);
व्योम sअगरive_prci_pcie_aux_घड़ी_disable(काष्ठा clk_hw *hw);

#पूर्ण_अगर /* __SIFIVE_CLK_SIFIVE_PRCI_H */
