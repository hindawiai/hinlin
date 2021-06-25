<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, 2013, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/पन.स>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/clk/tegra.h>

#समावेश "clk.h"
#समावेश "clk-id.h"

#घोषणा PLLX_BASE 0xe0
#घोषणा PLLX_MISC 0xe4
#घोषणा PLLX_MISC2 0x514
#घोषणा PLLX_MISC3 0x518

#घोषणा CCLKG_BURST_POLICY 0x368
#घोषणा CCLKLP_BURST_POLICY 0x370
#घोषणा SCLK_BURST_POLICY 0x028
#घोषणा SYSTEM_CLK_RATE 0x030
#घोषणा SCLK_DIVIDER 0x2c

अटल DEFINE_SPINLOCK(sysrate_lock);

क्रमागत tegra_super_gen अणु
	gen4 = 4,
	gen5,
पूर्ण;

काष्ठा tegra_super_gen_info अणु
	क्रमागत tegra_super_gen gen;
	स्थिर अक्षर **sclk_parents;
	स्थिर अक्षर **cclk_g_parents;
	स्थिर अक्षर **cclk_lp_parents;
	पूर्णांक num_sclk_parents;
	पूर्णांक num_cclk_g_parents;
	पूर्णांक num_cclk_lp_parents;
पूर्ण;

अटल स्थिर अक्षर *sclk_parents[] = अणु "clk_m", "pll_c_out1", "pll_p_out4",
			       "pll_p", "pll_p_out2", "unused",
			       "clk_32k", "pll_m_out1" पूर्ण;

अटल स्थिर अक्षर *cclk_g_parents[] = अणु "clk_m", "pll_c", "clk_32k", "pll_m",
					"pll_p", "pll_p_out4", "unused",
					"unused", "pll_x", "unused", "unused",
					"unused", "unused", "unused", "unused",
					"dfllCPU_out" पूर्ण;

अटल स्थिर अक्षर *cclk_lp_parents[] = अणु "clk_m", "pll_c", "clk_32k", "pll_m",
					 "pll_p", "pll_p_out4", "unused",
					 "unused", "pll_x", "pll_x_out0" पूर्ण;

अटल स्थिर काष्ठा tegra_super_gen_info tegra_super_gen_info_gen4 = अणु
	.gen = gen4,
	.sclk_parents = sclk_parents,
	.cclk_g_parents = cclk_g_parents,
	.cclk_lp_parents = cclk_lp_parents,
	.num_sclk_parents = ARRAY_SIZE(sclk_parents),
	.num_cclk_g_parents = ARRAY_SIZE(cclk_g_parents),
	.num_cclk_lp_parents = ARRAY_SIZE(cclk_lp_parents),
पूर्ण;

अटल स्थिर अक्षर *sclk_parents_gen5[] = अणु "clk_m", "pll_c_out1", "pll_c4_out3",
			       "pll_p", "pll_p_out2", "pll_c4_out1",
			       "clk_32k", "pll_c4_out2" पूर्ण;

अटल स्थिर अक्षर *cclk_g_parents_gen5[] = अणु "clk_m", "unused", "clk_32k", "unused",
					"pll_p", "pll_p_out4", "unused",
					"unused", "pll_x", "unused", "unused",
					"unused", "unused", "unused", "unused",
					"dfllCPU_out" पूर्ण;

अटल स्थिर अक्षर *cclk_lp_parents_gen5[] = अणु "clk_m", "unused", "clk_32k", "unused",
					"pll_p", "pll_p_out4", "unused",
					"unused", "pll_x", "unused", "unused",
					"unused", "unused", "unused", "unused",
					"dfllCPU_out" पूर्ण;

अटल स्थिर काष्ठा tegra_super_gen_info tegra_super_gen_info_gen5 = अणु
	.gen = gen5,
	.sclk_parents = sclk_parents_gen5,
	.cclk_g_parents = cclk_g_parents_gen5,
	.cclk_lp_parents = cclk_lp_parents_gen5,
	.num_sclk_parents = ARRAY_SIZE(sclk_parents_gen5),
	.num_cclk_g_parents = ARRAY_SIZE(cclk_g_parents_gen5),
	.num_cclk_lp_parents = ARRAY_SIZE(cclk_lp_parents_gen5),
पूर्ण;

अटल व्योम __init tegra_sclk_init(व्योम __iomem *clk_base,
				काष्ठा tegra_clk *tegra_clks,
				स्थिर काष्ठा tegra_super_gen_info *gen_info)
अणु
	काष्ठा clk *clk;
	काष्ठा clk **dt_clk;

	/* SCLK_MUX */
	dt_clk = tegra_lookup_dt_id(tegra_clk_sclk_mux, tegra_clks);
	अगर (dt_clk) अणु
		clk = tegra_clk_रेजिस्टर_super_mux("sclk_mux",
						gen_info->sclk_parents,
						gen_info->num_sclk_parents,
						CLK_SET_RATE_PARENT,
						clk_base + SCLK_BURST_POLICY,
						0, 4, 0, 0, शून्य);
		*dt_clk = clk;


		/* SCLK */
		dt_clk = tegra_lookup_dt_id(tegra_clk_sclk, tegra_clks);
		अगर (dt_clk) अणु
			clk = clk_रेजिस्टर_भागider(शून्य, "sclk", "sclk_mux",
						CLK_IS_CRITICAL,
						clk_base + SCLK_DIVIDER, 0, 8,
						0, &sysrate_lock);
			*dt_clk = clk;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* SCLK */
		dt_clk = tegra_lookup_dt_id(tegra_clk_sclk, tegra_clks);
		अगर (dt_clk) अणु
			clk = tegra_clk_रेजिस्टर_super_mux("sclk",
						gen_info->sclk_parents,
						gen_info->num_sclk_parents,
						CLK_SET_RATE_PARENT |
						CLK_IS_CRITICAL,
						clk_base + SCLK_BURST_POLICY,
						0, 4, 0, 0, शून्य);
			*dt_clk = clk;
		पूर्ण
	पूर्ण

	/* HCLK */
	dt_clk = tegra_lookup_dt_id(tegra_clk_hclk, tegra_clks);
	अगर (dt_clk) अणु
		clk = clk_रेजिस्टर_भागider(शून्य, "hclk_div", "sclk", 0,
				   clk_base + SYSTEM_CLK_RATE, 4, 2, 0,
				   &sysrate_lock);
		clk = clk_रेजिस्टर_gate(शून्य, "hclk", "hclk_div",
				CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
				clk_base + SYSTEM_CLK_RATE,
				7, CLK_GATE_SET_TO_DISABLE, &sysrate_lock);
		*dt_clk = clk;
	पूर्ण

	/* PCLK */
	dt_clk = tegra_lookup_dt_id(tegra_clk_pclk, tegra_clks);
	अगर (!dt_clk)
		वापस;

	clk = clk_रेजिस्टर_भागider(शून्य, "pclk_div", "hclk", 0,
				   clk_base + SYSTEM_CLK_RATE, 0, 2, 0,
				   &sysrate_lock);
	clk = clk_रेजिस्टर_gate(शून्य, "pclk", "pclk_div", CLK_SET_RATE_PARENT |
				CLK_IS_CRITICAL, clk_base + SYSTEM_CLK_RATE,
				3, CLK_GATE_SET_TO_DISABLE, &sysrate_lock);
	*dt_clk = clk;
पूर्ण

अटल व्योम __init tegra_super_clk_init(व्योम __iomem *clk_base,
				व्योम __iomem *pmc_base,
				काष्ठा tegra_clk *tegra_clks,
				काष्ठा tegra_clk_pll_params *params,
				स्थिर काष्ठा tegra_super_gen_info *gen_info)
अणु
	काष्ठा clk *clk;
	काष्ठा clk **dt_clk;

	/* CCLKG */
	dt_clk = tegra_lookup_dt_id(tegra_clk_cclk_g, tegra_clks);
	अगर (dt_clk) अणु
		अगर (gen_info->gen == gen5) अणु
			clk = tegra_clk_रेजिस्टर_super_mux("cclk_g",
					gen_info->cclk_g_parents,
					gen_info->num_cclk_g_parents,
					CLK_SET_RATE_PARENT,
					clk_base + CCLKG_BURST_POLICY,
					TEGRA210_CPU_CLK, 4, 8, 0, शून्य);
		पूर्ण अन्यथा अणु
			clk = tegra_clk_रेजिस्टर_super_mux("cclk_g",
					gen_info->cclk_g_parents,
					gen_info->num_cclk_g_parents,
					CLK_SET_RATE_PARENT,
					clk_base + CCLKG_BURST_POLICY,
					0, 4, 0, 0, शून्य);
		पूर्ण
		*dt_clk = clk;
	पूर्ण

	/* CCLKLP */
	dt_clk = tegra_lookup_dt_id(tegra_clk_cclk_lp, tegra_clks);
	अगर (dt_clk) अणु
		अगर (gen_info->gen == gen5) अणु
			/*
			 * TEGRA210_CPU_CLK flag is not needed क्रम cclk_lp as
			 * cluster चयनing is not currently supported on
			 * Tegra210 and also cpu_lp is not used.
			 */
			clk = tegra_clk_रेजिस्टर_super_mux("cclk_lp",
					gen_info->cclk_lp_parents,
					gen_info->num_cclk_lp_parents,
					CLK_SET_RATE_PARENT,
					clk_base + CCLKLP_BURST_POLICY,
					0, 4, 8, 0, शून्य);
		पूर्ण अन्यथा अणु
			clk = tegra_clk_रेजिस्टर_super_mux("cclk_lp",
					gen_info->cclk_lp_parents,
					gen_info->num_cclk_lp_parents,
					CLK_SET_RATE_PARENT,
					clk_base + CCLKLP_BURST_POLICY,
					TEGRA_DIVIDER_2, 4, 8, 9, शून्य);
		पूर्ण
		*dt_clk = clk;
	पूर्ण

	tegra_sclk_init(clk_base, tegra_clks, gen_info);

#अगर defined(CONFIG_ARCH_TEGRA_114_SOC) || \
    defined(CONFIG_ARCH_TEGRA_124_SOC) || \
    defined(CONFIG_ARCH_TEGRA_210_SOC)
	/* PLLX */
	dt_clk = tegra_lookup_dt_id(tegra_clk_pll_x, tegra_clks);
	अगर (!dt_clk)
		वापस;

#अगर defined(CONFIG_ARCH_TEGRA_210_SOC)
	अगर (gen_info->gen == gen5)
		clk = tegra_clk_रेजिस्टर_pllc_tegra210("pll_x", "pll_ref",
			clk_base, pmc_base, CLK_IGNORE_UNUSED, params, शून्य);
	अन्यथा
#पूर्ण_अगर
		clk = tegra_clk_रेजिस्टर_pllxc("pll_x", "pll_ref", clk_base,
				pmc_base, CLK_IGNORE_UNUSED, params, शून्य);

	*dt_clk = clk;

	/* PLLX_OUT0 */

	dt_clk = tegra_lookup_dt_id(tegra_clk_pll_x_out0, tegra_clks);
	अगर (!dt_clk)
		वापस;
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_x_out0", "pll_x",
					CLK_SET_RATE_PARENT, 1, 2);
	*dt_clk = clk;
#पूर्ण_अगर
पूर्ण

व्योम __init tegra_super_clk_gen4_init(व्योम __iomem *clk_base,
				व्योम __iomem *pmc_base,
				काष्ठा tegra_clk *tegra_clks,
				काष्ठा tegra_clk_pll_params *params)
अणु
	tegra_super_clk_init(clk_base, pmc_base, tegra_clks, params,
			     &tegra_super_gen_info_gen4);
पूर्ण

व्योम __init tegra_super_clk_gen5_init(व्योम __iomem *clk_base,
				व्योम __iomem *pmc_base,
				काष्ठा tegra_clk *tegra_clks,
				काष्ठा tegra_clk_pll_params *params)
अणु
	tegra_super_clk_init(clk_base, pmc_base, tegra_clks, params,
			     &tegra_super_gen_info_gen5);
पूर्ण
