<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * r8a7740 Core CPG Clocks
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

काष्ठा r8a7740_cpg अणु
	काष्ठा clk_onecell_data data;
	spinlock_t lock;
	व्योम __iomem *reg;
पूर्ण;

#घोषणा CPG_FRQCRA	0x00
#घोषणा CPG_FRQCRB	0x04
#घोषणा CPG_PLLC2CR	0x2c
#घोषणा CPG_USBCKCR	0x8c
#घोषणा CPG_FRQCRC	0xe0

#घोषणा CLK_ENABLE_ON_INIT BIT(0)

काष्ठा भाग4_clk अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक shअगरt;
	पूर्णांक flags;
पूर्ण;

अटल काष्ठा भाग4_clk भाग4_clks[] = अणु
	अणु "i", CPG_FRQCRA, 20, CLK_ENABLE_ON_INIT पूर्ण,
	अणु "zg", CPG_FRQCRA, 16, CLK_ENABLE_ON_INIT पूर्ण,
	अणु "b", CPG_FRQCRA,  8, CLK_ENABLE_ON_INIT पूर्ण,
	अणु "m1", CPG_FRQCRA,  4, CLK_ENABLE_ON_INIT पूर्ण,
	अणु "hp", CPG_FRQCRB,  4, 0 पूर्ण,
	अणु "hpp", CPG_FRQCRC, 20, 0 पूर्ण,
	अणु "usbp", CPG_FRQCRC, 16, 0 पूर्ण,
	अणु "s", CPG_FRQCRC, 12, 0 पूर्ण,
	अणु "zb", CPG_FRQCRC,  8, 0 पूर्ण,
	अणु "m3", CPG_FRQCRC,  4, 0 पूर्ण,
	अणु "cp", CPG_FRQCRC,  0, 0 पूर्ण,
	अणु शून्य, 0, 0, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable भाग4_भाग_प्रकारable[] = अणु
	अणु 0, 2 पूर्ण, अणु 1, 3 पूर्ण, अणु 2, 4 पूर्ण, अणु 3, 6 पूर्ण, अणु 4, 8 पूर्ण, अणु 5, 12 पूर्ण,
	अणु 6, 16 पूर्ण, अणु 7, 18 पूर्ण, अणु 8, 24 पूर्ण, अणु 9, 32 पूर्ण, अणु 10, 36 पूर्ण, अणु 11, 48 पूर्ण,
	अणु 13, 72 पूर्ण, अणु 14, 96 पूर्ण, अणु 0, 0 पूर्ण
पूर्ण;

अटल u32 cpg_mode __initdata;

अटल काष्ठा clk * __init
r8a7740_cpg_रेजिस्टर_घड़ी(काष्ठा device_node *np, काष्ठा r8a7740_cpg *cpg,
			     स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *table = शून्य;
	स्थिर अक्षर *parent_name;
	अचिन्हित पूर्णांक shअगरt, reg;
	अचिन्हित पूर्णांक mult = 1;
	अचिन्हित पूर्णांक भाग = 1;

	अगर (!म_भेद(name, "r")) अणु
		चयन (cpg_mode & (BIT(2) | BIT(1))) अणु
		हाल BIT(1) | BIT(2):
			/* extal1 */
			parent_name = of_clk_get_parent_name(np, 0);
			भाग = 2048;
			अवरोध;
		हाल BIT(2):
			/* extal1 */
			parent_name = of_clk_get_parent_name(np, 0);
			भाग = 1024;
			अवरोध;
		शेष:
			/* extalr */
			parent_name = of_clk_get_parent_name(np, 2);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेद(name, "system")) अणु
		parent_name = of_clk_get_parent_name(np, 0);
		अगर (cpg_mode & BIT(1))
			भाग = 2;
	पूर्ण अन्यथा अगर (!म_भेद(name, "pllc0")) अणु
		/* PLLC0/1 are configurable multiplier घड़ीs. Register them as
		 * fixed factor घड़ीs क्रम now as there's no generic multiplier
		 * घड़ी implementation and we currently have no need to change
		 * the multiplier value.
		 */
		u32 value = पढ़ोl(cpg->reg + CPG_FRQCRC);
		parent_name = "system";
		mult = ((value >> 24) & 0x7f) + 1;
	पूर्ण अन्यथा अगर (!म_भेद(name, "pllc1")) अणु
		u32 value = पढ़ोl(cpg->reg + CPG_FRQCRA);
		parent_name = "system";
		mult = ((value >> 24) & 0x7f) + 1;
		भाग = 2;
	पूर्ण अन्यथा अगर (!म_भेद(name, "pllc2")) अणु
		u32 value = पढ़ोl(cpg->reg + CPG_PLLC2CR);
		parent_name = "system";
		mult = ((value >> 24) & 0x3f) + 1;
	पूर्ण अन्यथा अगर (!म_भेद(name, "usb24s")) अणु
		u32 value = पढ़ोl(cpg->reg + CPG_USBCKCR);
		अगर (value & BIT(7))
			/* extal2 */
			parent_name = of_clk_get_parent_name(np, 1);
		अन्यथा
			parent_name = "system";
		अगर (!(value & BIT(6)))
			भाग = 2;
	पूर्ण अन्यथा अणु
		काष्ठा भाग4_clk *c;
		क्रम (c = भाग4_clks; c->name; c++) अणु
			अगर (!म_भेद(name, c->name)) अणु
				parent_name = "pllc1";
				table = भाग4_भाग_प्रकारable;
				reg = c->reg;
				shअगरt = c->shअगरt;
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
						  cpg->reg + reg, shअगरt, 4, 0,
						  table, &cpg->lock);
	पूर्ण
पूर्ण

अटल व्योम __init r8a7740_cpg_घड़ीs_init(काष्ठा device_node *np)
अणु
	काष्ठा r8a7740_cpg *cpg;
	काष्ठा clk **clks;
	अचिन्हित पूर्णांक i;
	पूर्णांक num_clks;

	अगर (of_property_पढ़ो_u32(np, "renesas,mode", &cpg_mode))
		pr_warn("%s: missing renesas,mode property\n", __func__);

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

		clk = r8a7740_cpg_रेजिस्टर_घड़ी(np, cpg, name);
		अगर (IS_ERR(clk))
			pr_err("%s: failed to register %pOFn %s clock (%ld)\n",
			       __func__, np, name, PTR_ERR(clk));
		अन्यथा
			cpg->data.clks[i] = clk;
	पूर्ण

	of_clk_add_provider(np, of_clk_src_onecell_get, &cpg->data);
पूर्ण
CLK_OF_DECLARE(r8a7740_cpg_clks, "renesas,r8a7740-cpg-clocks",
	       r8a7740_cpg_घड़ीs_init);
