<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018-2019 SiFive, Inc.
 * Copyright (C) 2018-2019 Wesley Terpstra
 * Copyright (C) 2018-2019 Paul Walmsley
 * Copyright (C) 2020 Zong Li
 *
 * The FU540 PRCI implements घड़ी and reset control क्रम the SiFive
 * FU540-C000 chip.  This driver assumes that it has sole control
 * over all PRCI resources.
 *
 * This driver is based on the PRCI driver written by Wesley Terpstra:
 * https://github.com/riscv/riscv-linux/commit/999529edf517ed75b56659d456d221b2ee56bb60
 *
 * References:
 * - SiFive FU540-C000 manual v1p0, Chapter 7 "Clocking and Reset"
 */

#समावेश <linux/module.h>

#समावेश <dt-bindings/घड़ी/sअगरive-fu540-prci.h>

#समावेश "fu540-prci.h"
#समावेश "sifive-prci.h"

/* PRCI पूर्णांकegration data क्रम each WRPLL instance */

अटल काष्ठा __prci_wrpll_data __prci_corepll_data = अणु
	.cfg0_offs = PRCI_COREPLLCFG0_OFFSET,
	.cfg1_offs = PRCI_COREPLLCFG1_OFFSET,
	.enable_bypass = sअगरive_prci_coreclksel_use_hfclk,
	.disable_bypass = sअगरive_prci_coreclksel_use_corepll,
पूर्ण;

अटल काष्ठा __prci_wrpll_data __prci_ddrpll_data = अणु
	.cfg0_offs = PRCI_DDRPLLCFG0_OFFSET,
	.cfg1_offs = PRCI_DDRPLLCFG1_OFFSET,
पूर्ण;

अटल काष्ठा __prci_wrpll_data __prci_gemgxlpll_data = अणु
	.cfg0_offs = PRCI_GEMGXLPLLCFG0_OFFSET,
	.cfg1_offs = PRCI_GEMGXLPLLCFG1_OFFSET,
पूर्ण;

/* Linux घड़ी framework पूर्णांकegration */

अटल स्थिर काष्ठा clk_ops sअगरive_fu540_prci_wrpll_clk_ops = अणु
	.set_rate = sअगरive_prci_wrpll_set_rate,
	.round_rate = sअगरive_prci_wrpll_round_rate,
	.recalc_rate = sअगरive_prci_wrpll_recalc_rate,
	.enable = sअगरive_prci_घड़ी_enable,
	.disable = sअगरive_prci_घड़ी_disable,
	.is_enabled = sअगरive_clk_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा clk_ops sअगरive_fu540_prci_wrpll_ro_clk_ops = अणु
	.recalc_rate = sअगरive_prci_wrpll_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops sअगरive_fu540_prci_tlclksel_clk_ops = अणु
	.recalc_rate = sअगरive_prci_tlclksel_recalc_rate,
पूर्ण;

/* List of घड़ी controls provided by the PRCI */
काष्ठा __prci_घड़ी __prci_init_घड़ीs_fu540[] = अणु
	[PRCI_CLK_COREPLL] = अणु
		.name = "corepll",
		.parent_name = "hfclk",
		.ops = &sअगरive_fu540_prci_wrpll_clk_ops,
		.pwd = &__prci_corepll_data,
	पूर्ण,
	[PRCI_CLK_DDRPLL] = अणु
		.name = "ddrpll",
		.parent_name = "hfclk",
		.ops = &sअगरive_fu540_prci_wrpll_ro_clk_ops,
		.pwd = &__prci_ddrpll_data,
	पूर्ण,
	[PRCI_CLK_GEMGXLPLL] = अणु
		.name = "gemgxlpll",
		.parent_name = "hfclk",
		.ops = &sअगरive_fu540_prci_wrpll_clk_ops,
		.pwd = &__prci_gemgxlpll_data,
	पूर्ण,
	[PRCI_CLK_TLCLK] = अणु
		.name = "tlclk",
		.parent_name = "corepll",
		.ops = &sअगरive_fu540_prci_tlclksel_clk_ops,
	पूर्ण,
पूर्ण;
