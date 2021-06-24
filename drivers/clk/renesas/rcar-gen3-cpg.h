<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * R-Car Gen3 Clock Pulse Generator
 *
 * Copyright (C) 2015-2018 Glider bvba
 * Copyright (C) 2018 Renesas Electronics Corp.
 *
 */

#अगर_अघोषित __CLK_RENESAS_RCAR_GEN3_CPG_H__
#घोषणा __CLK_RENESAS_RCAR_GEN3_CPG_H__

क्रमागत rcar_gen3_clk_types अणु
	CLK_TYPE_GEN3_MAIN = CLK_TYPE_CUSTOM,
	CLK_TYPE_GEN3_PLL0,
	CLK_TYPE_GEN3_PLL1,
	CLK_TYPE_GEN3_PLL2,
	CLK_TYPE_GEN3_PLL3,
	CLK_TYPE_GEN3_PLL4,
	CLK_TYPE_GEN3_SD,
	CLK_TYPE_GEN3_R,
	CLK_TYPE_GEN3_MDSEL,	/* Select parent/भागider using mode pin */
	CLK_TYPE_GEN3_Z,
	CLK_TYPE_GEN3_OSC,	/* OSC EXTAL preभागider and fixed भागider */
	CLK_TYPE_GEN3_RCKSEL,	/* Select parent/भागider using RCKCR.CKSEL */
	CLK_TYPE_GEN3_RPCSRC,
	CLK_TYPE_GEN3_E3_RPCSRC,
	CLK_TYPE_GEN3_RPC,
	CLK_TYPE_GEN3_RPCD2,

	/* SoC specअगरic definitions start here */
	CLK_TYPE_GEN3_SOC_BASE,
पूर्ण;

#घोषणा DEF_GEN3_SD(_name, _id, _parent, _offset)	\
	DEF_BASE(_name, _id, CLK_TYPE_GEN3_SD, _parent, .offset = _offset)

#घोषणा DEF_GEN3_MDSEL(_name, _id, _md, _parent0, _भाग0, _parent1, _भाग1) \
	DEF_BASE(_name, _id, CLK_TYPE_GEN3_MDSEL,	\
		 (_parent0) << 16 | (_parent1),		\
		 .भाग = (_भाग0) << 16 | (_भाग1), .offset = _md)

#घोषणा DEF_GEN3_PE(_name, _id, _parent_sscg, _भाग_sscg, _parent_clean, \
		    _भाग_clean) \
	DEF_GEN3_MDSEL(_name, _id, 12, _parent_sscg, _भाग_sscg,	\
		       _parent_clean, _भाग_clean)

#घोषणा DEF_GEN3_OSC(_name, _id, _parent, _भाग)		\
	DEF_BASE(_name, _id, CLK_TYPE_GEN3_OSC, _parent, .भाग = _भाग)

#घोषणा DEF_GEN3_RCKSEL(_name, _id, _parent0, _भाग0, _parent1, _भाग1) \
	DEF_BASE(_name, _id, CLK_TYPE_GEN3_RCKSEL,	\
		 (_parent0) << 16 | (_parent1),	.भाग = (_भाग0) << 16 | (_भाग1))

#घोषणा DEF_GEN3_Z(_name, _id, _type, _parent, _भाग, _offset)	\
	DEF_BASE(_name, _id, _type, _parent, .भाग = _भाग, .offset = _offset)

#घोषणा DEF_FIXED_RPCSRC_E3(_name, _id, _parent0, _parent1)	\
	DEF_BASE(_name, _id, CLK_TYPE_GEN3_E3_RPCSRC,	\
		 (_parent0) << 16 | (_parent1), .भाग = 8)

काष्ठा rcar_gen3_cpg_pll_config अणु
	u8 extal_भाग;
	u8 pll1_mult;
	u8 pll1_भाग;
	u8 pll3_mult;
	u8 pll3_भाग;
	u8 osc_preभाग;
पूर्ण;

#घोषणा CPG_RPCCKCR	0x238
#घोषणा CPG_RCKCR	0x240

काष्ठा clk *rcar_gen3_cpg_clk_रेजिस्टर(काष्ठा device *dev,
	स्थिर काष्ठा cpg_core_clk *core, स्थिर काष्ठा cpg_mssr_info *info,
	काष्ठा clk **clks, व्योम __iomem *base,
	काष्ठा raw_notअगरier_head *notअगरiers);
पूर्णांक rcar_gen3_cpg_init(स्थिर काष्ठा rcar_gen3_cpg_pll_config *config,
		       अचिन्हित पूर्णांक clk_extalr, u32 mode);

#पूर्ण_अगर
