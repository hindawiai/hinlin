<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * r8a7779 Core CPG Clocks
 *
 * Copyright (C) 2013, 2014 Horms Solutions Ltd.
 *
 * Contact: Simon Horman <horms@verge.net.au>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/renesas.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/soc/renesas/rcar-rst.h>

#समावेश <dt-bindings/घड़ी/r8a7779-घड़ी.h>

#घोषणा CPG_NUM_CLOCKS			(R8A7779_CLK_OUT + 1)

काष्ठा r8a7779_cpg अणु
	काष्ठा clk_onecell_data data;
	spinlock_t lock;
	व्योम __iomem *reg;
पूर्ण;

/* -----------------------------------------------------------------------------
 * CPG Clock Data
 */

/*
 *		MD1 = 1			MD1 = 0
 *		(PLLA = 1500)		(PLLA = 1600)
 *		(MHz)			(MHz)
 *------------------------------------------------+--------------------
 * clkz		1000   (2/3)		800   (1/2)
 * clkzs	 250   (1/6)		200   (1/8)
 * clki		 750   (1/2)		800   (1/2)
 * clks		 250   (1/6)		200   (1/8)
 * clks1	 125   (1/12)		100   (1/16)
 * clks3	 187.5 (1/8)		200   (1/8)
 * clks4	  93.7 (1/16)		100   (1/16)
 * clkp		  62.5 (1/24)		 50   (1/32)
 * clkg		  62.5 (1/24)		 66.6 (1/24)
 * clkb, CLKOUT
 * (MD2 = 0)	  62.5 (1/24)		 66.6 (1/24)
 * (MD2 = 1)	  41.6 (1/36)		 50   (1/32)
 */

#घोषणा CPG_CLK_CONFIG_INDEX(md)	(((md) & (BIT(2)|BIT(1))) >> 1)

काष्ठा cpg_clk_config अणु
	अचिन्हित पूर्णांक z_mult;
	अचिन्हित पूर्णांक z_भाग;
	अचिन्हित पूर्णांक zs_and_s_भाग;
	अचिन्हित पूर्णांक s1_भाग;
	अचिन्हित पूर्णांक p_भाग;
	अचिन्हित पूर्णांक b_and_out_भाग;
पूर्ण;

अटल स्थिर काष्ठा cpg_clk_config cpg_clk_configs[4] __initस्थिर = अणु
	अणु 1, 2, 8, 16, 32, 24 पूर्ण,
	अणु 2, 3, 6, 12, 24, 24 पूर्ण,
	अणु 1, 2, 8, 16, 32, 32 पूर्ण,
	अणु 2, 3, 6, 12, 24, 36 पूर्ण,
पूर्ण;

/*
 *   MD		PLLA Ratio
 * 12 11
 *------------------------
 * 0  0		x42
 * 0  1		x48
 * 1  0		x56
 * 1  1		x64
 */

#घोषणा CPG_PLLA_MULT_INDEX(md)	(((md) & (BIT(12)|BIT(11))) >> 11)

अटल स्थिर अचिन्हित पूर्णांक cpg_plla_mult[4] __initस्थिर = अणु 42, 48, 56, 64 पूर्ण;

/* -----------------------------------------------------------------------------
 * Initialization
 */

अटल काष्ठा clk * __init
r8a7779_cpg_रेजिस्टर_घड़ी(काष्ठा device_node *np, काष्ठा r8a7779_cpg *cpg,
			   स्थिर काष्ठा cpg_clk_config *config,
			   अचिन्हित पूर्णांक plla_mult, स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *parent_name = "plla";
	अचिन्हित पूर्णांक mult = 1;
	अचिन्हित पूर्णांक भाग = 1;

	अगर (!म_भेद(name, "plla")) अणु
		parent_name = of_clk_get_parent_name(np, 0);
		mult = plla_mult;
	पूर्ण अन्यथा अगर (!म_भेद(name, "z")) अणु
		भाग = config->z_भाग;
		mult = config->z_mult;
	पूर्ण अन्यथा अगर (!म_भेद(name, "zs") || !म_भेद(name, "s")) अणु
		भाग = config->zs_and_s_भाग;
	पूर्ण अन्यथा अगर (!म_भेद(name, "s1")) अणु
		भाग = config->s1_भाग;
	पूर्ण अन्यथा अगर (!म_भेद(name, "p")) अणु
		भाग = config->p_भाग;
	पूर्ण अन्यथा अगर (!म_भेद(name, "b") || !म_भेद(name, "out")) अणु
		भाग = config->b_and_out_भाग;
	पूर्ण अन्यथा अणु
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस clk_रेजिस्टर_fixed_factor(शून्य, name, parent_name, 0, mult, भाग);
पूर्ण

अटल व्योम __init r8a7779_cpg_घड़ीs_init(काष्ठा device_node *np)
अणु
	स्थिर काष्ठा cpg_clk_config *config;
	काष्ठा r8a7779_cpg *cpg;
	काष्ठा clk **clks;
	अचिन्हित पूर्णांक i, plla_mult;
	पूर्णांक num_clks;
	u32 mode;

	अगर (rcar_rst_पढ़ो_mode_pins(&mode))
		वापस;

	num_clks = of_property_count_strings(np, "clock-output-names");
	अगर (num_clks < 0) अणु
		pr_err("%s: failed to count clocks\n", __func__);
		वापस;
	पूर्ण

	cpg = kzalloc(माप(*cpg), GFP_KERNEL);
	clks = kसुस्मृति(CPG_NUM_CLOCKS, माप(*clks), GFP_KERNEL);
	अगर (cpg == शून्य || clks == शून्य) अणु
		/* We're leaking memory on purpose, there's no poपूर्णांक in cleaning
		 * up as the प्रणाली won't boot anyway.
		 */
		वापस;
	पूर्ण

	spin_lock_init(&cpg->lock);

	cpg->data.clks = clks;
	cpg->data.clk_num = num_clks;

	config = &cpg_clk_configs[CPG_CLK_CONFIG_INDEX(mode)];
	plla_mult = cpg_plla_mult[CPG_PLLA_MULT_INDEX(mode)];

	क्रम (i = 0; i < num_clks; ++i) अणु
		स्थिर अक्षर *name;
		काष्ठा clk *clk;

		of_property_पढ़ो_string_index(np, "clock-output-names", i,
					      &name);

		clk = r8a7779_cpg_रेजिस्टर_घड़ी(np, cpg, config,
						 plla_mult, name);
		अगर (IS_ERR(clk))
			pr_err("%s: failed to register %pOFn %s clock (%ld)\n",
			       __func__, np, name, PTR_ERR(clk));
		अन्यथा
			cpg->data.clks[i] = clk;
	पूर्ण

	of_clk_add_provider(np, of_clk_src_onecell_get, &cpg->data);

	cpg_mstp_add_clk_करोमुख्य(np);
पूर्ण
CLK_OF_DECLARE(r8a7779_cpg_clks, "renesas,r8a7779-cpg-clocks",
	       r8a7779_cpg_घड़ीs_init);
