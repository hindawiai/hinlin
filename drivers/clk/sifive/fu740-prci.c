<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 SiFive, Inc.
 * Copyright (C) 2020 Zong Li
 */

#समावेश <linux/module.h>

#समावेश <dt-bindings/घड़ी/sअगरive-fu740-prci.h>

#समावेश "fu540-prci.h"
#समावेश "sifive-prci.h"

/* PRCI पूर्णांकegration data क्रम each WRPLL instance */

अटल काष्ठा __prci_wrpll_data __prci_corepll_data = अणु
	.cfg0_offs = PRCI_COREPLLCFG0_OFFSET,
	.cfg1_offs = PRCI_COREPLLCFG1_OFFSET,
	.enable_bypass = sअगरive_prci_coreclksel_use_hfclk,
	.disable_bypass = sअगरive_prci_coreclksel_use_final_corepll,
पूर्ण;

अटल काष्ठा __prci_wrpll_data __prci_ddrpll_data = अणु
	.cfg0_offs = PRCI_DDRPLLCFG0_OFFSET,
	.cfg1_offs = PRCI_DDRPLLCFG1_OFFSET,
पूर्ण;

अटल काष्ठा __prci_wrpll_data __prci_gemgxlpll_data = अणु
	.cfg0_offs = PRCI_GEMGXLPLLCFG0_OFFSET,
	.cfg1_offs = PRCI_GEMGXLPLLCFG1_OFFSET,
पूर्ण;

अटल काष्ठा __prci_wrpll_data __prci_dvfscorepll_data = अणु
	.cfg0_offs = PRCI_DVFSCOREPLLCFG0_OFFSET,
	.cfg1_offs = PRCI_DVFSCOREPLLCFG1_OFFSET,
	.enable_bypass = sअगरive_prci_corepllsel_use_corepll,
	.disable_bypass = sअगरive_prci_corepllsel_use_dvfscorepll,
पूर्ण;

अटल काष्ठा __prci_wrpll_data __prci_hfpclkpll_data = अणु
	.cfg0_offs = PRCI_HFPCLKPLLCFG0_OFFSET,
	.cfg1_offs = PRCI_HFPCLKPLLCFG1_OFFSET,
	.enable_bypass = sअगरive_prci_hfpclkpllsel_use_hfclk,
	.disable_bypass = sअगरive_prci_hfpclkpllsel_use_hfpclkpll,
पूर्ण;

अटल काष्ठा __prci_wrpll_data __prci_cltxpll_data = अणु
	.cfg0_offs = PRCI_CLTXPLLCFG0_OFFSET,
	.cfg1_offs = PRCI_CLTXPLLCFG1_OFFSET,
पूर्ण;

/* Linux घड़ी framework पूर्णांकegration */

अटल स्थिर काष्ठा clk_ops sअगरive_fu740_prci_wrpll_clk_ops = अणु
	.set_rate = sअगरive_prci_wrpll_set_rate,
	.round_rate = sअगरive_prci_wrpll_round_rate,
	.recalc_rate = sअगरive_prci_wrpll_recalc_rate,
	.enable = sअगरive_prci_घड़ी_enable,
	.disable = sअगरive_prci_घड़ी_disable,
	.is_enabled = sअगरive_clk_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा clk_ops sअगरive_fu740_prci_wrpll_ro_clk_ops = अणु
	.recalc_rate = sअगरive_prci_wrpll_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops sअगरive_fu740_prci_tlclksel_clk_ops = अणु
	.recalc_rate = sअगरive_prci_tlclksel_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops sअगरive_fu740_prci_hfpclkplद_भाग_clk_ops = अणु
	.recalc_rate = sअगरive_prci_hfpclkplद_भाग_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops sअगरive_fu740_prci_pcie_aux_clk_ops = अणु
	.enable = sअगरive_prci_pcie_aux_घड़ी_enable,
	.disable = sअगरive_prci_pcie_aux_घड़ी_disable,
	.is_enabled = sअगरive_prci_pcie_aux_घड़ी_is_enabled,
पूर्ण;

/* List of घड़ी controls provided by the PRCI */
काष्ठा __prci_घड़ी __prci_init_घड़ीs_fu740[] = अणु
	[PRCI_CLK_COREPLL] = अणु
		.name = "corepll",
		.parent_name = "hfclk",
		.ops = &sअगरive_fu740_prci_wrpll_clk_ops,
		.pwd = &__prci_corepll_data,
	पूर्ण,
	[PRCI_CLK_DDRPLL] = अणु
		.name = "ddrpll",
		.parent_name = "hfclk",
		.ops = &sअगरive_fu740_prci_wrpll_ro_clk_ops,
		.pwd = &__prci_ddrpll_data,
	पूर्ण,
	[PRCI_CLK_GEMGXLPLL] = अणु
		.name = "gemgxlpll",
		.parent_name = "hfclk",
		.ops = &sअगरive_fu740_prci_wrpll_clk_ops,
		.pwd = &__prci_gemgxlpll_data,
	पूर्ण,
	[PRCI_CLK_DVFSCOREPLL] = अणु
		.name = "dvfscorepll",
		.parent_name = "hfclk",
		.ops = &sअगरive_fu740_prci_wrpll_clk_ops,
		.pwd = &__prci_dvfscorepll_data,
	पूर्ण,
	[PRCI_CLK_HFPCLKPLL] = अणु
		.name = "hfpclkpll",
		.parent_name = "hfclk",
		.ops = &sअगरive_fu740_prci_wrpll_clk_ops,
		.pwd = &__prci_hfpclkpll_data,
	पूर्ण,
	[PRCI_CLK_CLTXPLL] = अणु
		.name = "cltxpll",
		.parent_name = "hfclk",
		.ops = &sअगरive_fu740_prci_wrpll_clk_ops,
		.pwd = &__prci_cltxpll_data,
	पूर्ण,
	[PRCI_CLK_TLCLK] = अणु
		.name = "tlclk",
		.parent_name = "corepll",
		.ops = &sअगरive_fu740_prci_tlclksel_clk_ops,
	पूर्ण,
	[PRCI_CLK_PCLK] = अणु
		.name = "pclk",
		.parent_name = "hfpclkpll",
		.ops = &sअगरive_fu740_prci_hfpclkplद_भाग_clk_ops,
	पूर्ण,
	[PRCI_CLK_PCIE_AUX] = अणु
		.name = "pcie_aux",
		.parent_name = "hfclk",
		.ops = &sअगरive_fu740_prci_pcie_aux_clk_ops,
	पूर्ण,
पूर्ण;
