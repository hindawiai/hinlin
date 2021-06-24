<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * R-Car Gen2 Clock Pulse Generator
 *
 * Copyright (C) 2016 Cogent Embedded Inc.
 */

#अगर_अघोषित __CLK_RENESAS_RCAR_GEN2_CPG_H__
#घोषणा __CLK_RENESAS_RCAR_GEN2_CPG_H__

क्रमागत rcar_gen2_clk_types अणु
	CLK_TYPE_GEN2_MAIN = CLK_TYPE_CUSTOM,
	CLK_TYPE_GEN2_PLL0,
	CLK_TYPE_GEN2_PLL1,
	CLK_TYPE_GEN2_PLL3,
	CLK_TYPE_GEN2_Z,
	CLK_TYPE_GEN2_LB,
	CLK_TYPE_GEN2_ADSP,
	CLK_TYPE_GEN2_SDH,
	CLK_TYPE_GEN2_SD0,
	CLK_TYPE_GEN2_SD1,
	CLK_TYPE_GEN2_QSPI,
	CLK_TYPE_GEN2_RCAN,
पूर्ण;

काष्ठा rcar_gen2_cpg_pll_config अणु
	u8 extal_भाग;
	u8 pll1_mult;
	u8 pll3_mult;
	u8 pll0_mult;		/* leave as zero अगर PLL0CR exists */
पूर्ण;

काष्ठा clk *rcar_gen2_cpg_clk_रेजिस्टर(काष्ठा device *dev,
	स्थिर काष्ठा cpg_core_clk *core, स्थिर काष्ठा cpg_mssr_info *info,
	काष्ठा clk **clks, व्योम __iomem *base,
	काष्ठा raw_notअगरier_head *notअगरiers);
पूर्णांक rcar_gen2_cpg_init(स्थिर काष्ठा rcar_gen2_cpg_pll_config *config,
		       अचिन्हित पूर्णांक pll0_भाग, u32 mode);

#पूर्ण_अगर
