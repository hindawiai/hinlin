<शैली गुरु>
// SPDX-License-Identअगरier:	GPL-2.0
/*
 * Copyright (C) 2017, Intel Corporation
 */
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>

#समावेश "stratix10-clk.h"
#समावेश "clk.h"

/* Clock Manager offsets */
#घोषणा CLK_MGR_PLL_CLK_SRC_SHIFT	16
#घोषणा CLK_MGR_PLL_CLK_SRC_MASK	0x3

/* PLL Clock enable bits */
#घोषणा SOCFPGA_PLL_POWER		0
#घोषणा SOCFPGA_PLL_RESET_MASK		0x2
#घोषणा SOCFPGA_PLL_REFDIV_MASK		0x00003F00
#घोषणा SOCFPGA_PLL_REFDIV_SHIFT	8
#घोषणा SOCFPGA_PLL_AREFDIV_MASK	0x00000F00
#घोषणा SOCFPGA_PLL_DREFDIV_MASK	0x00003000
#घोषणा SOCFPGA_PLL_DREFDIV_SHIFT	12
#घोषणा SOCFPGA_PLL_MDIV_MASK		0xFF000000
#घोषणा SOCFPGA_PLL_MDIV_SHIFT		24
#घोषणा SOCFPGA_AGILEX_PLL_MDIV_MASK	0x000003FF
#घोषणा SWCTRLBTCLKSEL_MASK		0x200
#घोषणा SWCTRLBTCLKSEL_SHIFT		9

#घोषणा SOCFPGA_N5X_PLLDIV_FDIV_MASK	GENMASK(16, 8)
#घोषणा SOCFPGA_N5X_PLLDIV_FDIV_SHIFT	8
#घोषणा SOCFPGA_N5X_PLLDIV_RDIV_MASK	GENMASK(5, 0)
#घोषणा SOCFPGA_N5X_PLLDIV_QDIV_MASK	GENMASK(26, 24)
#घोषणा SOCFPGA_N5X_PLLDIV_QDIV_SHIFT	24

#घोषणा SOCFPGA_BOOT_CLK		"boot_clk"

#घोषणा to_socfpga_clk(p) container_of(p, काष्ठा socfpga_pll, hw.hw)

अटल अचिन्हित दीर्घ n5x_clk_pll_recalc_rate(काष्ठा clk_hw *hwclk,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_pll *socfpgaclk = to_socfpga_clk(hwclk);
	अचिन्हित दीर्घ fभाग, reg, rभाग, qभाग;
	u32 घातer = 1;

	/* पढ़ो VCO1 reg क्रम numerator and denominator */
	reg = पढ़ोl(socfpgaclk->hw.reg + 0x8);
	fभाग = (reg & SOCFPGA_N5X_PLLDIV_FDIV_MASK) >> SOCFPGA_N5X_PLLDIV_FDIV_SHIFT;
	rभाग = (reg & SOCFPGA_N5X_PLLDIV_RDIV_MASK);
	qभाग = (reg & SOCFPGA_N5X_PLLDIV_QDIV_MASK) >> SOCFPGA_N5X_PLLDIV_QDIV_SHIFT;

	जबतक (qभाग) अणु
		घातer *= 2;
		qभाग--;
	पूर्ण

	वापस ((parent_rate * 2 * (fभाग + 1)) / ((rभाग + 1) * घातer));
पूर्ण

अटल अचिन्हित दीर्घ agilex_clk_pll_recalc_rate(काष्ठा clk_hw *hwclk,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_pll *socfpgaclk = to_socfpga_clk(hwclk);
	अचिन्हित दीर्घ arefभाग, reg, mभाग;
	अचिन्हित दीर्घ दीर्घ vco_freq;

	/* पढ़ो VCO1 reg क्रम numerator and denominator */
	reg = पढ़ोl(socfpgaclk->hw.reg);
	arefभाग = (reg & SOCFPGA_PLL_AREFDIV_MASK) >> SOCFPGA_PLL_REFDIV_SHIFT;

	vco_freq = (अचिन्हित दीर्घ दीर्घ)parent_rate / arefभाग;

	/* Read mभाग and fभाग from the fdbck रेजिस्टर */
	reg = पढ़ोl(socfpgaclk->hw.reg + 0x24);
	mभाग = reg & SOCFPGA_AGILEX_PLL_MDIV_MASK;

	vco_freq = (अचिन्हित दीर्घ दीर्घ)vco_freq * mभाग;
	वापस (अचिन्हित दीर्घ)vco_freq;
पूर्ण

अटल अचिन्हित दीर्घ clk_pll_recalc_rate(काष्ठा clk_hw *hwclk,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_pll *socfpgaclk = to_socfpga_clk(hwclk);
	अचिन्हित दीर्घ mभाग;
	अचिन्हित दीर्घ refभाग;
	अचिन्हित दीर्घ reg;
	अचिन्हित दीर्घ दीर्घ vco_freq;

	/* पढ़ो VCO1 reg क्रम numerator and denominator */
	reg = पढ़ोl(socfpgaclk->hw.reg);
	refभाग = (reg & SOCFPGA_PLL_REFDIV_MASK) >> SOCFPGA_PLL_REFDIV_SHIFT;

	vco_freq = parent_rate;
	करो_भाग(vco_freq, refभाग);

	/* Read mभाग and fभाग from the fdbck रेजिस्टर */
	reg = पढ़ोl(socfpgaclk->hw.reg + 0x4);
	mभाग = (reg & SOCFPGA_PLL_MDIV_MASK) >> SOCFPGA_PLL_MDIV_SHIFT;
	vco_freq = (अचिन्हित दीर्घ दीर्घ)vco_freq * (mभाग + 6);

	वापस (अचिन्हित दीर्घ)vco_freq;
पूर्ण

अटल अचिन्हित दीर्घ clk_boot_clk_recalc_rate(काष्ठा clk_hw *hwclk,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_pll *socfpgaclk = to_socfpga_clk(hwclk);
	u32 भाग;

	भाग = ((पढ़ोl(socfpgaclk->hw.reg) &
		SWCTRLBTCLKSEL_MASK) >>
		SWCTRLBTCLKSEL_SHIFT);
	भाग += 1;
	वापस parent_rate /= भाग;
पूर्ण


अटल u8 clk_pll_get_parent(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा socfpga_pll *socfpgaclk = to_socfpga_clk(hwclk);
	u32 pll_src;

	pll_src = पढ़ोl(socfpgaclk->hw.reg);
	वापस (pll_src >> CLK_MGR_PLL_CLK_SRC_SHIFT) &
		CLK_MGR_PLL_CLK_SRC_MASK;
पूर्ण

अटल u8 clk_boot_get_parent(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा socfpga_pll *socfpgaclk = to_socfpga_clk(hwclk);
	u32 pll_src;

	pll_src = पढ़ोl(socfpgaclk->hw.reg);
	वापस (pll_src >> SWCTRLBTCLKSEL_SHIFT) &
		SWCTRLBTCLKSEL_MASK;
पूर्ण

अटल पूर्णांक clk_pll_prepare(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा socfpga_pll *socfpgaclk = to_socfpga_clk(hwclk);
	u32 reg;

	/* Bring PLL out of reset */
	reg = पढ़ोl(socfpgaclk->hw.reg);
	reg |= SOCFPGA_PLL_RESET_MASK;
	ग_लिखोl(reg, socfpgaclk->hw.reg);

	वापस 0;
पूर्ण

अटल पूर्णांक n5x_clk_pll_prepare(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा socfpga_pll *socfpgaclk = to_socfpga_clk(hwclk);
	u32 reg;

	/* Bring PLL out of reset */
	reg = पढ़ोl(socfpgaclk->hw.reg + 0x4);
	reg |= SOCFPGA_PLL_RESET_MASK;
	ग_लिखोl(reg, socfpgaclk->hw.reg + 0x4);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops n5x_clk_pll_ops = अणु
	.recalc_rate = n5x_clk_pll_recalc_rate,
	.get_parent = clk_pll_get_parent,
	.prepare = n5x_clk_pll_prepare,
पूर्ण;

अटल स्थिर काष्ठा clk_ops agilex_clk_pll_ops = अणु
	.recalc_rate = agilex_clk_pll_recalc_rate,
	.get_parent = clk_pll_get_parent,
	.prepare = clk_pll_prepare,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_pll_ops = अणु
	.recalc_rate = clk_pll_recalc_rate,
	.get_parent = clk_pll_get_parent,
	.prepare = clk_pll_prepare,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_boot_ops = अणु
	.recalc_rate = clk_boot_clk_recalc_rate,
	.get_parent = clk_boot_get_parent,
	.prepare = clk_pll_prepare,
पूर्ण;

काष्ठा clk_hw *s10_रेजिस्टर_pll(स्थिर काष्ठा stratix10_pll_घड़ी *clks,
			     व्योम __iomem *reg)
अणु
	काष्ठा clk_hw *hw_clk;
	काष्ठा socfpga_pll *pll_clk;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *name = clks->name;
	पूर्णांक ret;

	pll_clk = kzalloc(माप(*pll_clk), GFP_KERNEL);
	अगर (WARN_ON(!pll_clk))
		वापस शून्य;

	pll_clk->hw.reg = reg + clks->offset;

	अगर (streq(name, SOCFPGA_BOOT_CLK))
		init.ops = &clk_boot_ops;
	अन्यथा
		init.ops = &clk_pll_ops;

	init.name = name;
	init.flags = clks->flags;

	init.num_parents = clks->num_parents;
	init.parent_names = शून्य;
	init.parent_data = clks->parent_data;
	pll_clk->hw.hw.init = &init;

	pll_clk->hw.bit_idx = SOCFPGA_PLL_POWER;

	hw_clk = &pll_clk->hw.hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw_clk);
	अगर (ret) अणु
		kमुक्त(pll_clk);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस hw_clk;
पूर्ण

काष्ठा clk_hw *agilex_रेजिस्टर_pll(स्थिर काष्ठा stratix10_pll_घड़ी *clks,
				व्योम __iomem *reg)
अणु
	काष्ठा clk_hw *hw_clk;
	काष्ठा socfpga_pll *pll_clk;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *name = clks->name;
	पूर्णांक ret;

	pll_clk = kzalloc(माप(*pll_clk), GFP_KERNEL);
	अगर (WARN_ON(!pll_clk))
		वापस शून्य;

	pll_clk->hw.reg = reg + clks->offset;

	अगर (streq(name, SOCFPGA_BOOT_CLK))
		init.ops = &clk_boot_ops;
	अन्यथा
		init.ops = &agilex_clk_pll_ops;

	init.name = name;
	init.flags = clks->flags;

	init.num_parents = clks->num_parents;
	init.parent_names = शून्य;
	init.parent_data = clks->parent_data;
	pll_clk->hw.hw.init = &init;

	pll_clk->hw.bit_idx = SOCFPGA_PLL_POWER;
	hw_clk = &pll_clk->hw.hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw_clk);
	अगर (ret) अणु
		kमुक्त(pll_clk);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस hw_clk;
पूर्ण

काष्ठा clk_hw *n5x_रेजिस्टर_pll(स्थिर काष्ठा stratix10_pll_घड़ी *clks,
			     व्योम __iomem *reg)
अणु
	काष्ठा clk_hw *hw_clk;
	काष्ठा socfpga_pll *pll_clk;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *name = clks->name;
	पूर्णांक ret;

	pll_clk = kzalloc(माप(*pll_clk), GFP_KERNEL);
	अगर (WARN_ON(!pll_clk))
		वापस शून्य;

	pll_clk->hw.reg = reg + clks->offset;

	अगर (streq(name, SOCFPGA_BOOT_CLK))
		init.ops = &clk_boot_ops;
	अन्यथा
		init.ops = &n5x_clk_pll_ops;

	init.name = name;
	init.flags = clks->flags;

	init.num_parents = clks->num_parents;
	init.parent_names = शून्य;
	init.parent_data = clks->parent_data;
	pll_clk->hw.hw.init = &init;

	pll_clk->hw.bit_idx = SOCFPGA_PLL_POWER;
	hw_clk = &pll_clk->hw.hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw_clk);
	अगर (ret) अणु
		kमुक्त(pll_clk);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस hw_clk;
पूर्ण
