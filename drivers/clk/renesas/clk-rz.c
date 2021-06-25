<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RZ/A1 Core CPG Clocks
 *
 * Copyright (C) 2013 Ideas On Board SPRL
 * Copyright (C) 2014 Wolfram Sang, Sang Engineering <wsa@sang-engineering.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/renesas.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

काष्ठा rz_cpg अणु
	काष्ठा clk_onecell_data data;
	व्योम __iomem *reg;
पूर्ण;

#घोषणा CPG_FRQCR	0x10
#घोषणा CPG_FRQCR2	0x14

#घोषणा PPR0		0xFCFE3200
#घोषणा PIBC0		0xFCFE7000

#घोषणा MD_CLK(x)	((x >> 2) & 1)	/* P0_2 */

/* -----------------------------------------------------------------------------
 * Initialization
 */

अटल u16 __init rz_cpg_पढ़ो_mode_pins(व्योम)
अणु
	व्योम __iomem *ppr0, *pibc0;
	u16 modes;

	ppr0 = ioremap(PPR0, 2);
	pibc0 = ioremap(PIBC0, 2);
	BUG_ON(!ppr0 || !pibc0);
	ioग_लिखो16(4, pibc0);	/* enable input buffer */
	modes = ioपढ़ो16(ppr0);
	iounmap(ppr0);
	iounmap(pibc0);

	वापस modes;
पूर्ण

अटल काष्ठा clk * __init
rz_cpg_रेजिस्टर_घड़ी(काष्ठा device_node *np, काष्ठा rz_cpg *cpg, स्थिर अक्षर *name)
अणु
	u32 val;
	अचिन्हित mult;
	अटल स्थिर अचिन्हित frqcr_tab[4] = अणु 3, 2, 0, 1 पूर्ण;

	अगर (म_भेद(name, "pll") == 0) अणु
		अचिन्हित पूर्णांक cpg_mode = MD_CLK(rz_cpg_पढ़ो_mode_pins());
		स्थिर अक्षर *parent_name = of_clk_get_parent_name(np, cpg_mode);

		mult = cpg_mode ? (32 / 4) : 30;

		वापस clk_रेजिस्टर_fixed_factor(शून्य, name, parent_name, 0, mult, 1);
	पूर्ण

	/* If mapping regs failed, skip non-pll घड़ीs. System will boot anyhow */
	अगर (!cpg->reg)
		वापस ERR_PTR(-ENXIO);

	/* FIXME:"i" and "g" are variable घड़ीs with non-पूर्णांकeger भागiders (e.g. 2/3)
	 * and the स्थिरraपूर्णांक that always g <= i. To get the rz platक्रमm started,
	 * let them run at fixed current speed and implement the details later.
	 */
	अगर (म_भेद(name, "i") == 0)
		val = (पढ़ोl(cpg->reg + CPG_FRQCR) >> 8) & 3;
	अन्यथा अगर (म_भेद(name, "g") == 0)
		val = पढ़ोl(cpg->reg + CPG_FRQCR2) & 3;
	अन्यथा
		वापस ERR_PTR(-EINVAL);

	mult = frqcr_tab[val];
	वापस clk_रेजिस्टर_fixed_factor(शून्य, name, "pll", 0, mult, 3);
पूर्ण

अटल व्योम __init rz_cpg_घड़ीs_init(काष्ठा device_node *np)
अणु
	काष्ठा rz_cpg *cpg;
	काष्ठा clk **clks;
	अचिन्हित i;
	पूर्णांक num_clks;

	num_clks = of_property_count_strings(np, "clock-output-names");
	अगर (WARN(num_clks <= 0, "can't count CPG clocks\n"))
		वापस;

	cpg = kzalloc(माप(*cpg), GFP_KERNEL);
	clks = kसुस्मृति(num_clks, माप(*clks), GFP_KERNEL);
	BUG_ON(!cpg || !clks);

	cpg->data.clks = clks;
	cpg->data.clk_num = num_clks;

	cpg->reg = of_iomap(np, 0);

	क्रम (i = 0; i < num_clks; ++i) अणु
		स्थिर अक्षर *name;
		काष्ठा clk *clk;

		of_property_पढ़ो_string_index(np, "clock-output-names", i, &name);

		clk = rz_cpg_रेजिस्टर_घड़ी(np, cpg, name);
		अगर (IS_ERR(clk))
			pr_err("%s: failed to register %pOFn %s clock (%ld)\n",
			       __func__, np, name, PTR_ERR(clk));
		अन्यथा
			cpg->data.clks[i] = clk;
	पूर्ण

	of_clk_add_provider(np, of_clk_src_onecell_get, &cpg->data);

	cpg_mstp_add_clk_करोमुख्य(np);
पूर्ण
CLK_OF_DECLARE(rz_cpg_clks, "renesas,rz-cpg-clocks", rz_cpg_घड़ीs_init);
