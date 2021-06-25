<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Renesas Clock Pulse Generator / Module Standby and Software Reset
 *
 * Copyright (C) 2015 Glider bvba
 */

#अगर_अघोषित __CLK_RENESAS_CPG_MSSR_H__
#घोषणा __CLK_RENESAS_CPG_MSSR_H__

    /*
     * Definitions of CPG Core Clocks
     *
     * These include:
     *   - Clock outमाला_दो exported to DT
     *   - External input घड़ीs
     *   - Internal CPG घड़ीs
     */

काष्ठा cpg_core_clk अणु
	/* Common */
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक type;
	/* Depending on type */
	अचिन्हित पूर्णांक parent;	/* Core Clocks only */
	अचिन्हित पूर्णांक भाग;
	अचिन्हित पूर्णांक mult;
	अचिन्हित पूर्णांक offset;
पूर्ण;

क्रमागत clk_types अणु
	/* Generic */
	CLK_TYPE_IN,		/* External Clock Input */
	CLK_TYPE_FF,		/* Fixed Factor Clock */
	CLK_TYPE_DIV6P1,	/* DIV6 Clock with 1 parent घड़ी */
	CLK_TYPE_DIV6_RO,	/* DIV6 Clock पढ़ो only with extra भागisor */
	CLK_TYPE_FR,		/* Fixed Rate Clock */

	/* Custom definitions start here */
	CLK_TYPE_CUSTOM,
पूर्ण;

#घोषणा DEF_TYPE(_name, _id, _type...)	\
	अणु .name = _name, .id = _id, .type = _type पूर्ण
#घोषणा DEF_BASE(_name, _id, _type, _parent...)	\
	DEF_TYPE(_name, _id, _type, .parent = _parent)

#घोषणा DEF_INPUT(_name, _id) \
	DEF_TYPE(_name, _id, CLK_TYPE_IN)
#घोषणा DEF_FIXED(_name, _id, _parent, _भाग, _mult)	\
	DEF_BASE(_name, _id, CLK_TYPE_FF, _parent, .भाग = _भाग, .mult = _mult)
#घोषणा DEF_DIV6P1(_name, _id, _parent, _offset)	\
	DEF_BASE(_name, _id, CLK_TYPE_DIV6P1, _parent, .offset = _offset)
#घोषणा DEF_DIV6_RO(_name, _id, _parent, _offset, _भाग)	\
	DEF_BASE(_name, _id, CLK_TYPE_DIV6_RO, _parent, .offset = _offset, .भाग = _भाग, .mult = 1)
#घोषणा DEF_RATE(_name, _id, _rate)	\
	DEF_TYPE(_name, _id, CLK_TYPE_FR, .mult = _rate)

    /*
     * Definitions of Module Clocks
     */

काष्ठा mssr_mod_clk अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक parent;	/* Add MOD_CLK_BASE क्रम Module Clocks */
पूर्ण;

/* Convert from sparse base-100 to packed index space */
#घोषणा MOD_CLK_PACK(x)	((x) - ((x) / 100) * (100 - 32))

#घोषणा MOD_CLK_ID(x)	(MOD_CLK_BASE + MOD_CLK_PACK(x))

#घोषणा DEF_MOD(_name, _mod, _parent...)	\
	अणु .name = _name, .id = MOD_CLK_ID(_mod), .parent = _parent पूर्ण

/* Convert from sparse base-10 to packed index space */
#घोषणा MOD_CLK_PACK_10(x)	((x / 10) * 32 + (x % 10))

#घोषणा MOD_CLK_ID_10(x)	(MOD_CLK_BASE + MOD_CLK_PACK_10(x))

#घोषणा DEF_MOD_STB(_name, _mod, _parent...)	\
	अणु .name = _name, .id = MOD_CLK_ID_10(_mod), .parent = _parent पूर्ण

काष्ठा device_node;

क्रमागत clk_reg_layout अणु
	CLK_REG_LAYOUT_RCAR_GEN2_AND_GEN3 = 0,
	CLK_REG_LAYOUT_RZ_A,
	CLK_REG_LAYOUT_RCAR_V3U,
पूर्ण;

    /**
     * SoC-specअगरic CPG/MSSR Description
     *
     * @early_core_clks: Array of Early Core Clock definitions
     * @num_early_core_clks: Number of entries in early_core_clks[]
     * @early_mod_clks: Array of Early Module Clock definitions
     * @num_early_mod_clks: Number of entries in early_mod_clks[]
     *
     * @core_clks: Array of Core Clock definitions
     * @num_core_clks: Number of entries in core_clks[]
     * @last_dt_core_clk: ID of the last Core Clock exported to DT
     * @num_total_core_clks: Total number of Core Clocks (exported + पूर्णांकernal)
     *
     * @mod_clks: Array of Module Clock definitions
     * @num_mod_clks: Number of entries in mod_clks[]
     * @num_hw_mod_clks: Number of Module Clocks supported by the hardware
     *
     * @crit_mod_clks: Array with Module Clock IDs of critical घड़ीs that
     *                 should not be disabled without a knowledgeable driver
     * @num_crit_mod_clks: Number of entries in crit_mod_clks[]
     * @reg_layout: CPG/MSSR रेजिस्टर layout from क्रमागत clk_reg_layout
     *
     * @core_pm_clks: Array with IDs of Core Clocks that are suitable क्रम Power
     *                Management, in addition to Module Clocks
     * @num_core_pm_clks: Number of entries in core_pm_clks[]
     *
     * @init: Optional callback to perक्रमm SoC-specअगरic initialization
     * @cpg_clk_रेजिस्टर: Optional callback to handle special Core Clock types
     */

काष्ठा cpg_mssr_info अणु
	/* Early Clocks */
	स्थिर काष्ठा cpg_core_clk *early_core_clks;
	अचिन्हित पूर्णांक num_early_core_clks;
	स्थिर काष्ठा mssr_mod_clk *early_mod_clks;
	अचिन्हित पूर्णांक num_early_mod_clks;

	/* Core Clocks */
	स्थिर काष्ठा cpg_core_clk *core_clks;
	अचिन्हित पूर्णांक num_core_clks;
	अचिन्हित पूर्णांक last_dt_core_clk;
	अचिन्हित पूर्णांक num_total_core_clks;
	क्रमागत clk_reg_layout reg_layout;

	/* Module Clocks */
	स्थिर काष्ठा mssr_mod_clk *mod_clks;
	अचिन्हित पूर्णांक num_mod_clks;
	अचिन्हित पूर्णांक num_hw_mod_clks;

	/* Critical Module Clocks that should not be disabled */
	स्थिर अचिन्हित पूर्णांक *crit_mod_clks;
	अचिन्हित पूर्णांक num_crit_mod_clks;

	/* Core Clocks suitable क्रम PM, in addition to the Module Clocks */
	स्थिर अचिन्हित पूर्णांक *core_pm_clks;
	अचिन्हित पूर्णांक num_core_pm_clks;

	/* Callbacks */
	पूर्णांक (*init)(काष्ठा device *dev);
	काष्ठा clk *(*cpg_clk_रेजिस्टर)(काष्ठा device *dev,
					स्थिर काष्ठा cpg_core_clk *core,
					स्थिर काष्ठा cpg_mssr_info *info,
					काष्ठा clk **clks, व्योम __iomem *base,
					काष्ठा raw_notअगरier_head *notअगरiers);
पूर्ण;

बाह्य स्थिर काष्ठा cpg_mssr_info r7s9210_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a7742_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a7743_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a7745_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a77470_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a774a1_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a774b1_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a774c0_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a774e1_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a7790_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a7791_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a7792_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a7794_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a7795_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a7796_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a77965_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a77970_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a77980_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a77990_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a77995_cpg_mssr_info;
बाह्य स्थिर काष्ठा cpg_mssr_info r8a779a0_cpg_mssr_info;

व्योम __init cpg_mssr_early_init(काष्ठा device_node *np,
				स्थिर काष्ठा cpg_mssr_info *info);

    /*
     * Helpers क्रम fixing up घड़ी tables depending on SoC revision
     */

काष्ठा mssr_mod_reparent अणु
	अचिन्हित पूर्णांक clk, parent;
पूर्ण;


बाह्य व्योम cpg_core_nullअगरy_range(काष्ठा cpg_core_clk *core_clks,
				   अचिन्हित पूर्णांक num_core_clks,
				   अचिन्हित पूर्णांक first_clk,
				   अचिन्हित पूर्णांक last_clk);
बाह्य व्योम mssr_mod_nullअगरy(काष्ठा mssr_mod_clk *mod_clks,
			     अचिन्हित पूर्णांक num_mod_clks,
			     स्थिर अचिन्हित पूर्णांक *clks, अचिन्हित पूर्णांक n);
बाह्य व्योम mssr_mod_reparent(काष्ठा mssr_mod_clk *mod_clks,
			      अचिन्हित पूर्णांक num_mod_clks,
			      स्थिर काष्ठा mssr_mod_reparent *clks,
			      अचिन्हित पूर्णांक n);
#पूर्ण_अगर
