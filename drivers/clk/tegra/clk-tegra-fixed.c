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

#घोषणा OSC_CTRL			0x50
#घोषणा OSC_CTRL_OSC_FREQ_SHIFT		28
#घोषणा OSC_CTRL_PLL_REF_DIV_SHIFT	26
#घोषणा OSC_CTRL_MASK			(0x3f2 |	\
					(0xf << OSC_CTRL_OSC_FREQ_SHIFT))

अटल u32 osc_ctrl_ctx;

पूर्णांक __init tegra_osc_clk_init(व्योम __iomem *clk_base, काष्ठा tegra_clk *clks,
			      अचिन्हित दीर्घ *input_freqs, अचिन्हित पूर्णांक num,
			      अचिन्हित पूर्णांक clk_m_भाग, अचिन्हित दीर्घ *osc_freq,
			      अचिन्हित दीर्घ *pll_ref_freq)
अणु
	काष्ठा clk *clk, *osc;
	काष्ठा clk **dt_clk;
	u32 val, pll_ref_भाग;
	अचिन्हित osc_idx;

	val = पढ़ोl_relaxed(clk_base + OSC_CTRL);
	osc_ctrl_ctx = val & OSC_CTRL_MASK;
	osc_idx = val >> OSC_CTRL_OSC_FREQ_SHIFT;

	अगर (osc_idx < num)
		*osc_freq = input_freqs[osc_idx];
	अन्यथा
		*osc_freq = 0;

	अगर (!*osc_freq) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	dt_clk = tegra_lookup_dt_id(tegra_clk_osc, clks);
	अगर (!dt_clk)
		वापस 0;

	osc = clk_रेजिस्टर_fixed_rate(शून्य, "osc", शून्य, 0, *osc_freq);
	*dt_clk = osc;

	/* osc_भाग2 */
	dt_clk = tegra_lookup_dt_id(tegra_clk_osc_भाग2, clks);
	अगर (dt_clk) अणु
		clk = clk_रेजिस्टर_fixed_factor(शून्य, "osc_div2", "osc",
						0, 1, 2);
		*dt_clk = clk;
	पूर्ण

	/* osc_भाग4 */
	dt_clk = tegra_lookup_dt_id(tegra_clk_osc_भाग4, clks);
	अगर (dt_clk) अणु
		clk = clk_रेजिस्टर_fixed_factor(शून्य, "osc_div4", "osc",
						0, 1, 4);
		*dt_clk = clk;
	पूर्ण

	dt_clk = tegra_lookup_dt_id(tegra_clk_clk_m, clks);
	अगर (!dt_clk)
		वापस 0;

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "clk_m", "osc",
					0, 1, clk_m_भाग);
	*dt_clk = clk;

	/* pll_ref */
	val = (val >> OSC_CTRL_PLL_REF_DIV_SHIFT) & 3;
	pll_ref_भाग = 1 << val;
	dt_clk = tegra_lookup_dt_id(tegra_clk_pll_ref, clks);
	अगर (!dt_clk)
		वापस 0;

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_ref", "osc",
					0, 1, pll_ref_भाग);
	*dt_clk = clk;

	अगर (pll_ref_freq)
		*pll_ref_freq = *osc_freq / pll_ref_भाग;

	वापस 0;
पूर्ण

व्योम __init tegra_fixed_clk_init(काष्ठा tegra_clk *tegra_clks)
अणु
	काष्ठा clk *clk;
	काष्ठा clk **dt_clk;

	/* clk_32k */
	dt_clk = tegra_lookup_dt_id(tegra_clk_clk_32k, tegra_clks);
	अगर (dt_clk) अणु
		clk = clk_रेजिस्टर_fixed_rate(शून्य, "clk_32k", शून्य, 0, 32768);
		*dt_clk = clk;
	पूर्ण
पूर्ण

व्योम tegra_clk_osc_resume(व्योम __iomem *clk_base)
अणु
	u32 val;

	val = पढ़ोl_relaxed(clk_base + OSC_CTRL) & ~OSC_CTRL_MASK;
	val |= osc_ctrl_ctx;
	ग_लिखोl_relaxed(val, clk_base + OSC_CTRL);
	fence_udelay(2, clk_base);
पूर्ण
