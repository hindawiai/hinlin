<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MMP PLL घड़ी rate calculation
 *
 * Copyright (C) 2020 Lubomir Rपूर्णांकel <lkundrak@v3.sk>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश "clk.h"

#घोषणा to_clk_mmp_pll(hw)	container_of(hw, काष्ठा mmp_clk_pll, hw)

काष्ठा mmp_clk_pll अणु
	काष्ठा clk_hw hw;
	अचिन्हित दीर्घ शेष_rate;
	व्योम __iomem *enable_reg;
	u32 enable;
	व्योम __iomem *reg;
	u8 shअगरt;

	अचिन्हित दीर्घ input_rate;
	व्योम __iomem *postभाग_reg;
	u8 postभाग_shअगरt;
पूर्ण;

अटल पूर्णांक mmp_clk_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा mmp_clk_pll *pll = to_clk_mmp_pll(hw);
	u32 val;

	val = पढ़ोl_relaxed(pll->enable_reg);
	अगर ((val & pll->enable) == pll->enable)
		वापस 1;

	/* Some PLLs, अगर not software controlled, output शेष घड़ी. */
	अगर (pll->शेष_rate > 0)
		वापस 1;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ mmp_clk_pll_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mmp_clk_pll *pll = to_clk_mmp_pll(hw);
	u32 fbभाग, refभाग, postभाग;
	u64 rate;
	u32 val;

	val = पढ़ोl_relaxed(pll->enable_reg);
	अगर ((val & pll->enable) != pll->enable)
		वापस pll->शेष_rate;

	अगर (pll->reg) अणु
		val = पढ़ोl_relaxed(pll->reg);
		fbभाग = (val >> pll->shअगरt) & 0x1ff;
		refभाग = (val >> (pll->shअगरt + 9)) & 0x1f;
	पूर्ण अन्यथा अणु
		fbभाग = 2;
		refभाग = 1;
	पूर्ण

	अगर (pll->postभाग_reg) अणु
		/* MMP3 घड़ी rate calculation */
		अटल स्थिर u8 postभागs[] = अणु2, 3, 4, 5, 6, 8, 10, 12, 16पूर्ण;

		val = पढ़ोl_relaxed(pll->postभाग_reg);
		postभाग = (val >> pll->postभाग_shअगरt) & 0x7;

		rate = pll->input_rate;
		rate *= 2 * fbभाग;
		करो_भाग(rate, refभाग);
		करो_भाग(rate, postभागs[postभाग]);
	पूर्ण अन्यथा अणु
		/* MMP2 घड़ी rate calculation */
		अगर (refभाग == 3) अणु
			rate = 19200000;
		पूर्ण अन्यथा अगर (refभाग == 4) अणु
			rate = 26000000;
		पूर्ण अन्यथा अणु
			pr_err("bad refdiv: %d (0x%08x)\n", refभाग, val);
			वापस 0;
		पूर्ण

		rate *= fbभाग + 2;
		करो_भाग(rate, refभाग + 2);
	पूर्ण

	वापस (अचिन्हित दीर्घ)rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops mmp_clk_pll_ops = अणु
	.is_enabled = mmp_clk_pll_is_enabled,
	.recalc_rate = mmp_clk_pll_recalc_rate,
पूर्ण;

अटल काष्ठा clk *mmp_clk_रेजिस्टर_pll(अक्षर *name,
			अचिन्हित दीर्घ शेष_rate,
			व्योम __iomem *enable_reg, u32 enable,
			व्योम __iomem *reg, u8 shअगरt,
			अचिन्हित दीर्घ input_rate,
			व्योम __iomem *postभाग_reg, u8 postभाग_shअगरt)
अणु
	काष्ठा mmp_clk_pll *pll;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &mmp_clk_pll_ops;
	init.flags = 0;
	init.parent_names = शून्य;
	init.num_parents = 0;

	pll->शेष_rate = शेष_rate;
	pll->enable_reg = enable_reg;
	pll->enable = enable;
	pll->reg = reg;
	pll->shअगरt = shअगरt;

	pll->input_rate = input_rate;
	pll->postभाग_reg = postभाग_reg;
	pll->postभाग_shअगरt = postभाग_shअगरt;

	pll->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &pll->hw);

	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

व्योम mmp_रेजिस्टर_pll_clks(काष्ठा mmp_clk_unit *unit,
			काष्ठा mmp_param_pll_clk *clks,
			व्योम __iomem *base, पूर्णांक size)
अणु
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		व्योम __iomem *reg = शून्य;

		अगर (clks[i].offset)
			reg = base + clks[i].offset;

		clk = mmp_clk_रेजिस्टर_pll(clks[i].name,
					clks[i].शेष_rate,
					base + clks[i].enable_offset,
					clks[i].enable,
					reg, clks[i].shअगरt,
					clks[i].input_rate,
					base + clks[i].postभाग_offset,
					clks[i].postभाग_shअगरt);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जारी;
		पूर्ण
		अगर (clks[i].id)
			unit->clk_table[clks[i].id] = clk;
	पूर्ण
पूर्ण
