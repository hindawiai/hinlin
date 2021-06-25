<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * r8a7778 Core CPG Clocks
 *
 * Copyright (C) 2014  Ulrich Hecht
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/renesas.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/renesas/rcar-rst.h>

काष्ठा r8a7778_cpg अणु
	काष्ठा clk_onecell_data data;
	spinlock_t lock;
	व्योम __iomem *reg;
पूर्ण;

/* PLL multipliers per bits 11, 12, and 18 of MODEMR */
अटल स्थिर काष्ठा अणु
	अचिन्हित दीर्घ plla_mult;
	अचिन्हित दीर्घ pllb_mult;
पूर्ण r8a7778_rates[] __initस्थिर = अणु
	[0] = अणु 21, 21 पूर्ण,
	[1] = अणु 24, 24 पूर्ण,
	[2] = अणु 28, 28 पूर्ण,
	[3] = अणु 32, 32 पूर्ण,
	[5] = अणु 24, 21 पूर्ण,
	[6] = अणु 28, 21 पूर्ण,
	[7] = अणु 32, 24 पूर्ण,
पूर्ण;

/* Clock भागiders per bits 1 and 2 of MODEMR */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक भाग[4];
पूर्ण r8a7778_भागs[6] __initस्थिर = अणु
	अणु "b",   अणु 12, 12, 16, 18 पूर्ण पूर्ण,
	अणु "out", अणु 12, 12, 16, 18 पूर्ण पूर्ण,
	अणु "p",   अणु 16, 12, 16, 12 पूर्ण पूर्ण,
	अणु "s",   अणु 4,  3,  4,  3  पूर्ण पूर्ण,
	अणु "s1",  अणु 8,  6,  8,  6  पूर्ण पूर्ण,
पूर्ण;

अटल u32 cpg_mode_rates __initdata;
अटल u32 cpg_mode_भागs __initdata;

अटल काष्ठा clk * __init
r8a7778_cpg_रेजिस्टर_घड़ी(काष्ठा device_node *np, काष्ठा r8a7778_cpg *cpg,
			     स्थिर अक्षर *name)
अणु
	अगर (!म_भेद(name, "plla")) अणु
		वापस clk_रेजिस्टर_fixed_factor(शून्य, "plla",
			of_clk_get_parent_name(np, 0), 0,
			r8a7778_rates[cpg_mode_rates].plla_mult, 1);
	पूर्ण अन्यथा अगर (!म_भेद(name, "pllb")) अणु
		वापस clk_रेजिस्टर_fixed_factor(शून्य, "pllb",
			of_clk_get_parent_name(np, 0), 0,
			r8a7778_rates[cpg_mode_rates].pllb_mult, 1);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(r8a7778_भागs); i++) अणु
			अगर (!म_भेद(name, r8a7778_भागs[i].name)) अणु
				वापस clk_रेजिस्टर_fixed_factor(शून्य,
					r8a7778_भागs[i].name,
					"plla", 0, 1,
					r8a7778_भागs[i].भाग[cpg_mode_भागs]);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण


अटल व्योम __init r8a7778_cpg_घड़ीs_init(काष्ठा device_node *np)
अणु
	काष्ठा r8a7778_cpg *cpg;
	काष्ठा clk **clks;
	अचिन्हित पूर्णांक i;
	पूर्णांक num_clks;
	u32 mode;

	अगर (rcar_rst_पढ़ो_mode_pins(&mode))
		वापस;

	BUG_ON(!(mode & BIT(19)));

	cpg_mode_rates = (!!(mode & BIT(18)) << 2) |
			 (!!(mode & BIT(12)) << 1) |
			 (!!(mode & BIT(11)));
	cpg_mode_भागs = (!!(mode & BIT(2)) << 1) |
			(!!(mode & BIT(1)));

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

		clk = r8a7778_cpg_रेजिस्टर_घड़ी(np, cpg, name);
		अगर (IS_ERR(clk))
			pr_err("%s: failed to register %pOFn %s clock (%ld)\n",
			       __func__, np, name, PTR_ERR(clk));
		अन्यथा
			cpg->data.clks[i] = clk;
	पूर्ण

	of_clk_add_provider(np, of_clk_src_onecell_get, &cpg->data);

	cpg_mstp_add_clk_करोमुख्य(np);
पूर्ण

CLK_OF_DECLARE(r8a7778_cpg_clks, "renesas,r8a7778-cpg-clocks",
	       r8a7778_cpg_घड़ीs_init);
