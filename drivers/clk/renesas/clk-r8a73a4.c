<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * r8a73a4 Core CPG Clocks
 *
 * Copyright (C) 2014  Ulrich Hecht
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/renesas.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/spinlock.h>

काष्ठा r8a73a4_cpg अणु
	काष्ठा clk_onecell_data data;
	spinlock_t lock;
	व्योम __iomem *reg;
पूर्ण;

#घोषणा CPG_CKSCR	0xc0
#घोषणा CPG_FRQCRA	0x00
#घोषणा CPG_FRQCRB	0x04
#घोषणा CPG_FRQCRC	0xe0
#घोषणा CPG_PLL0CR	0xd8
#घोषणा CPG_PLL1CR	0x28
#घोषणा CPG_PLL2CR	0x2c
#घोषणा CPG_PLL2HCR	0xe4
#घोषणा CPG_PLL2SCR	0xf4

#घोषणा CLK_ENABLE_ON_INIT BIT(0)

काष्ठा भाग4_clk अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक shअगरt;
पूर्ण;

अटल काष्ठा भाग4_clk भाग4_clks[] = अणु
	अणु "i",	CPG_FRQCRA, 20 पूर्ण,
	अणु "m3", CPG_FRQCRA, 12 पूर्ण,
	अणु "b",	CPG_FRQCRA,  8 पूर्ण,
	अणु "m1", CPG_FRQCRA,  4 पूर्ण,
	अणु "m2", CPG_FRQCRA,  0 पूर्ण,
	अणु "zx", CPG_FRQCRB, 12 पूर्ण,
	अणु "zs", CPG_FRQCRB,  8 पूर्ण,
	अणु "hp", CPG_FRQCRB,  4 पूर्ण,
	अणु शून्य, 0, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable भाग4_भाग_प्रकारable[] = अणु
	अणु 0, 2 पूर्ण, अणु 1, 3 पूर्ण, अणु 2, 4 पूर्ण, अणु 3, 6 पूर्ण, अणु 4, 8 पूर्ण, अणु 5, 12 पूर्ण,
	अणु 6, 16 पूर्ण, अणु 7, 18 पूर्ण, अणु 8, 24 पूर्ण, अणु 10, 36 पूर्ण, अणु 11, 48 पूर्ण,
	अणु 12, 10 पूर्ण, अणु 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा clk * __init
r8a73a4_cpg_रेजिस्टर_घड़ी(काष्ठा device_node *np, काष्ठा r8a73a4_cpg *cpg,
			     स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *table = शून्य;
	स्थिर अक्षर *parent_name;
	अचिन्हित पूर्णांक shअगरt, reg;
	अचिन्हित पूर्णांक mult = 1;
	अचिन्हित पूर्णांक भाग = 1;


	अगर (!म_भेद(name, "main")) अणु
		u32 ckscr = पढ़ोl(cpg->reg + CPG_CKSCR);

		चयन ((ckscr >> 28) & 3) अणु
		हाल 0:	/* extal1 */
			parent_name = of_clk_get_parent_name(np, 0);
			अवरोध;
		हाल 1:	/* extal1 / 2 */
			parent_name = of_clk_get_parent_name(np, 0);
			भाग = 2;
			अवरोध;
		हाल 2: /* extal2 */
			parent_name = of_clk_get_parent_name(np, 1);
			अवरोध;
		हाल 3: /* extal2 / 2 */
			parent_name = of_clk_get_parent_name(np, 1);
			भाग = 2;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेद(name, "pll0")) अणु
		/* PLL0/1 are configurable multiplier घड़ीs. Register them as
		 * fixed factor घड़ीs क्रम now as there's no generic multiplier
		 * घड़ी implementation and we currently have no need to change
		 * the multiplier value.
		 */
		u32 value = पढ़ोl(cpg->reg + CPG_PLL0CR);

		parent_name = "main";
		mult = ((value >> 24) & 0x7f) + 1;
		अगर (value & BIT(20))
			भाग = 2;
	पूर्ण अन्यथा अगर (!म_भेद(name, "pll1")) अणु
		u32 value = पढ़ोl(cpg->reg + CPG_PLL1CR);

		parent_name = "main";
		/* XXX: enable bit? */
		mult = ((value >> 24) & 0x7f) + 1;
		अगर (value & BIT(7))
			भाग = 2;
	पूर्ण अन्यथा अगर (!म_भेदन(name, "pll2", 4)) अणु
		u32 value, cr;

		चयन (name[4]) अणु
		हाल 0:
			cr = CPG_PLL2CR;
			अवरोध;
		हाल 's':
			cr = CPG_PLL2SCR;
			अवरोध;
		हाल 'h':
			cr = CPG_PLL2HCR;
			अवरोध;
		शेष:
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		value = पढ़ोl(cpg->reg + cr);
		चयन ((value >> 5) & 7) अणु
		हाल 0:
			parent_name = "main";
			भाग = 2;
			अवरोध;
		हाल 1:
			parent_name = "extal2";
			भाग = 2;
			अवरोध;
		हाल 3:
			parent_name = "extal2";
			भाग = 4;
			अवरोध;
		हाल 4:
			parent_name = "main";
			अवरोध;
		हाल 5:
			parent_name = "extal2";
			अवरोध;
		शेष:
			pr_warn("%s: unexpected parent of %s\n", __func__,
				name);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		/* XXX: enable bit? */
		mult = ((value >> 24) & 0x7f) + 1;
	पूर्ण अन्यथा अगर (!म_भेद(name, "z") || !म_भेद(name, "z2")) अणु
		u32 shअगरt = 8;

		parent_name = "pll0";
		अगर (name[1] == '2') अणु
			भाग = 2;
			shअगरt = 0;
		पूर्ण
		भाग *= 32;
		mult = 0x20 - ((पढ़ोl(cpg->reg + CPG_FRQCRC) >> shअगरt) & 0x1f);
	पूर्ण अन्यथा अणु
		काष्ठा भाग4_clk *c;

		क्रम (c = भाग4_clks; c->name; c++) अणु
			अगर (!म_भेद(name, c->name))
				अवरोध;
		पूर्ण
		अगर (!c->name)
			वापस ERR_PTR(-EINVAL);

		parent_name = "pll1";
		table = भाग4_भाग_प्रकारable;
		reg = c->reg;
		shअगरt = c->shअगरt;
	पूर्ण

	अगर (!table) अणु
		वापस clk_रेजिस्टर_fixed_factor(शून्य, name, parent_name, 0,
						 mult, भाग);
	पूर्ण अन्यथा अणु
		वापस clk_रेजिस्टर_भागider_table(शून्य, name, parent_name, 0,
						  cpg->reg + reg, shअगरt, 4, 0,
						  table, &cpg->lock);
	पूर्ण
पूर्ण

अटल व्योम __init r8a73a4_cpg_घड़ीs_init(काष्ठा device_node *np)
अणु
	काष्ठा r8a73a4_cpg *cpg;
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

	क्रम (i = 0; i < num_clks; ++i) अणु
		स्थिर अक्षर *name;
		काष्ठा clk *clk;

		of_property_पढ़ो_string_index(np, "clock-output-names", i,
					      &name);

		clk = r8a73a4_cpg_रेजिस्टर_घड़ी(np, cpg, name);
		अगर (IS_ERR(clk))
			pr_err("%s: failed to register %pOFn %s clock (%ld)\n",
			       __func__, np, name, PTR_ERR(clk));
		अन्यथा
			cpg->data.clks[i] = clk;
	पूर्ण

	of_clk_add_provider(np, of_clk_src_onecell_get, &cpg->data);
पूर्ण
CLK_OF_DECLARE(r8a73a4_cpg_clks, "renesas,r8a73a4-cpg-clocks",
	       r8a73a4_cpg_घड़ीs_init);
