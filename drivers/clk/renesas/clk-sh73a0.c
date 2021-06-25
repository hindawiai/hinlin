<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sh73a0 Core CPG Clocks
 *
 * Copyright (C) 2014  Ulrich Hecht
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/renesas.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

काष्ठा sh73a0_cpg अणु
	काष्ठा clk_onecell_data data;
	spinlock_t lock;
	व्योम __iomem *reg;
पूर्ण;

#घोषणा CPG_FRQCRA	0x00
#घोषणा CPG_FRQCRB	0x04
#घोषणा CPG_SD0CKCR	0x74
#घोषणा CPG_SD1CKCR	0x78
#घोषणा CPG_SD2CKCR	0x7c
#घोषणा CPG_PLLECR	0xd0
#घोषणा CPG_PLL0CR	0xd8
#घोषणा CPG_PLL1CR	0x28
#घोषणा CPG_PLL2CR	0x2c
#घोषणा CPG_PLL3CR	0xdc
#घोषणा CPG_CKSCR	0xc0
#घोषणा CPG_DSI0PHYCR	0x6c
#घोषणा CPG_DSI1PHYCR	0x70

#घोषणा CLK_ENABLE_ON_INIT BIT(0)

काष्ठा भाग4_clk अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक shअगरt;
पूर्ण;

अटल स्थिर काष्ठा भाग4_clk भाग4_clks[] = अणु
	अणु "zg", "pll0", CPG_FRQCRA, 16 पूर्ण,
	अणु "m3", "pll1", CPG_FRQCRA, 12 पूर्ण,
	अणु "b",  "pll1", CPG_FRQCRA,  8 पूर्ण,
	अणु "m1", "pll1", CPG_FRQCRA,  4 पूर्ण,
	अणु "m2", "pll1", CPG_FRQCRA,  0 पूर्ण,
	अणु "zx", "pll1", CPG_FRQCRB, 12 पूर्ण,
	अणु "hp", "pll1", CPG_FRQCRB,  4 पूर्ण,
	अणु शून्य, शून्य, 0, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable भाग4_भाग_प्रकारable[] = अणु
	अणु 0, 2 पूर्ण, अणु 1, 3 पूर्ण, अणु 2, 4 पूर्ण, अणु 3, 6 पूर्ण, अणु 4, 8 पूर्ण, अणु 5, 12 पूर्ण,
	अणु 6, 16 पूर्ण, अणु 7, 18 पूर्ण, अणु 8, 24 पूर्ण, अणु 10, 36 पूर्ण, अणु 11, 48 पूर्ण,
	अणु 12, 7 पूर्ण, अणु 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable z_भाग_प्रकारable[] = अणु
	/* ZSEL == 0 */
	अणु 0, 1 पूर्ण, अणु 1, 1 पूर्ण, अणु 2, 1 पूर्ण, अणु 3, 1 पूर्ण, अणु 4, 1 पूर्ण, अणु 5, 1 पूर्ण,
	अणु 6, 1 पूर्ण, अणु 7, 1 पूर्ण, अणु 8, 1 पूर्ण, अणु 9, 1 पूर्ण, अणु 10, 1 पूर्ण, अणु 11, 1 पूर्ण,
	अणु 12, 1 पूर्ण, अणु 13, 1 पूर्ण, अणु 14, 1 पूर्ण, अणु 15, 1 पूर्ण,
	/* ZSEL == 1 */
	अणु 16, 2 पूर्ण, अणु 17, 3 पूर्ण, अणु 18, 4 पूर्ण, अणु 19, 6 पूर्ण, अणु 20, 8 पूर्ण, अणु 21, 12 पूर्ण,
	अणु 22, 16 पूर्ण, अणु 24, 24 पूर्ण, अणु 27, 48 पूर्ण, अणु 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा clk * __init
sh73a0_cpg_रेजिस्टर_घड़ी(काष्ठा device_node *np, काष्ठा sh73a0_cpg *cpg,
			     स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *table = शून्य;
	अचिन्हित पूर्णांक shअगरt, reg, width;
	स्थिर अक्षर *parent_name = शून्य;
	अचिन्हित पूर्णांक mult = 1;
	अचिन्हित पूर्णांक भाग = 1;

	अगर (!म_भेद(name, "main")) अणु
		/* extal1, extal1_भाग2, extal2, extal2_भाग2 */
		u32 parent_idx = (पढ़ोl(cpg->reg + CPG_CKSCR) >> 28) & 3;

		parent_name = of_clk_get_parent_name(np, parent_idx >> 1);
		भाग = (parent_idx & 1) + 1;
	पूर्ण अन्यथा अगर (!म_भेदन(name, "pll", 3)) अणु
		व्योम __iomem *enable_reg = cpg->reg;
		u32 enable_bit = name[3] - '0';

		parent_name = "main";
		चयन (enable_bit) अणु
		हाल 0:
			enable_reg += CPG_PLL0CR;
			अवरोध;
		हाल 1:
			enable_reg += CPG_PLL1CR;
			अवरोध;
		हाल 2:
			enable_reg += CPG_PLL2CR;
			अवरोध;
		हाल 3:
			enable_reg += CPG_PLL3CR;
			अवरोध;
		शेष:
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		अगर (पढ़ोl(cpg->reg + CPG_PLLECR) & BIT(enable_bit)) अणु
			mult = ((पढ़ोl(enable_reg) >> 24) & 0x3f) + 1;
			/* handle CFG bit क्रम PLL1 and PLL2 */
			अगर (enable_bit == 1 || enable_bit == 2)
				अगर (पढ़ोl(enable_reg) & BIT(20))
					mult *= 2;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेद(name, "dsi0phy") || !म_भेद(name, "dsi1phy")) अणु
		u32 phy_no = name[3] - '0';
		व्योम __iomem *dsi_reg = cpg->reg +
			(phy_no ? CPG_DSI1PHYCR : CPG_DSI0PHYCR);

		parent_name = phy_no ? "dsi1pck" : "dsi0pck";
		mult = पढ़ोl(dsi_reg);
		अगर (!(mult & 0x8000))
			mult = 1;
		अन्यथा
			mult = (mult & 0x3f) + 1;
	पूर्ण अन्यथा अगर (!म_भेद(name, "z")) अणु
		parent_name = "pll0";
		table = z_भाग_प्रकारable;
		reg = CPG_FRQCRB;
		shअगरt = 24;
		width = 5;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा भाग4_clk *c;

		क्रम (c = भाग4_clks; c->name; c++) अणु
			अगर (!म_भेद(name, c->name)) अणु
				parent_name = c->parent;
				table = भाग4_भाग_प्रकारable;
				reg = c->reg;
				shअगरt = c->shअगरt;
				width = 4;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!c->name)
			वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!table) अणु
		वापस clk_रेजिस्टर_fixed_factor(शून्य, name, parent_name, 0,
						 mult, भाग);
	पूर्ण अन्यथा अणु
		वापस clk_रेजिस्टर_भागider_table(शून्य, name, parent_name, 0,
						  cpg->reg + reg, shअगरt, width, 0,
						  table, &cpg->lock);
	पूर्ण
पूर्ण

अटल व्योम __init sh73a0_cpg_घड़ीs_init(काष्ठा device_node *np)
अणु
	काष्ठा sh73a0_cpg *cpg;
	काष्ठा clk **clks;
	अचिन्हित पूर्णांक i;
	पूर्णांक num_clks;

	num_clks = of_property_count_strings(np, "clock-output-names");
	अगर (num_clks < 0) अणु
		pr_err("%s: failed to count clocks\n", __func__);
		वापस;
	पूर्ण

	cpg = kzalloc(माप(*cpg), GFP_KERNEL);
	clks = kसुस्मृति(num_clks, माप(*clks), GFP_KERNEL);
	अगर (cpg == शून्य || clks == शून्य) अणु
		/* We're leaking memory on purpose, there's no poपूर्णांक in cleaning
		 * up as the प्रणाली won't boot anyway.
		 */
		वापस;
	पूर्ण

	spin_lock_init(&cpg->lock);

	cpg->data.clks = clks;
	cpg->data.clk_num = num_clks;

	cpg->reg = of_iomap(np, 0);
	अगर (WARN_ON(cpg->reg == शून्य))
		वापस;

	/* Set SDHI घड़ीs to a known state */
	ग_लिखोl(0x108, cpg->reg + CPG_SD0CKCR);
	ग_लिखोl(0x108, cpg->reg + CPG_SD1CKCR);
	ग_लिखोl(0x108, cpg->reg + CPG_SD2CKCR);

	क्रम (i = 0; i < num_clks; ++i) अणु
		स्थिर अक्षर *name;
		काष्ठा clk *clk;

		of_property_पढ़ो_string_index(np, "clock-output-names", i,
					      &name);

		clk = sh73a0_cpg_रेजिस्टर_घड़ी(np, cpg, name);
		अगर (IS_ERR(clk))
			pr_err("%s: failed to register %pOFn %s clock (%ld)\n",
			       __func__, np, name, PTR_ERR(clk));
		अन्यथा
			cpg->data.clks[i] = clk;
	पूर्ण

	of_clk_add_provider(np, of_clk_src_onecell_get, &cpg->data);
पूर्ण
CLK_OF_DECLARE(sh73a0_cpg_clks, "renesas,sh73a0-cpg-clocks",
	       sh73a0_cpg_घड़ीs_init);
