<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2011-2012 Calxeda, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#घोषणा HB_PLL_LOCK_500		0x20000000
#घोषणा HB_PLL_LOCK		0x10000000
#घोषणा HB_PLL_DIVF_SHIFT	20
#घोषणा HB_PLL_DIVF_MASK	0x0ff00000
#घोषणा HB_PLL_DIVQ_SHIFT	16
#घोषणा HB_PLL_DIVQ_MASK	0x00070000
#घोषणा HB_PLL_DIVR_SHIFT	8
#घोषणा HB_PLL_DIVR_MASK	0x00001f00
#घोषणा HB_PLL_RANGE_SHIFT	4
#घोषणा HB_PLL_RANGE_MASK	0x00000070
#घोषणा HB_PLL_BYPASS		0x00000008
#घोषणा HB_PLL_RESET		0x00000004
#घोषणा HB_PLL_EXT_BYPASS	0x00000002
#घोषणा HB_PLL_EXT_ENA		0x00000001

#घोषणा HB_PLL_VCO_MIN_FREQ	2133000000
#घोषणा HB_PLL_MAX_FREQ		HB_PLL_VCO_MIN_FREQ
#घोषणा HB_PLL_MIN_FREQ		(HB_PLL_VCO_MIN_FREQ / 64)

#घोषणा HB_A9_BCLK_DIV_MASK	0x00000006
#घोषणा HB_A9_BCLK_DIV_SHIFT	1
#घोषणा HB_A9_PCLK_DIV		0x00000001

काष्ठा hb_clk अणु
        काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	अक्षर *parent_name;
पूर्ण;
#घोषणा to_hb_clk(p) container_of(p, काष्ठा hb_clk, hw)

अटल पूर्णांक clk_pll_prepare(काष्ठा clk_hw *hwclk)
	अणु
	काष्ठा hb_clk *hbclk = to_hb_clk(hwclk);
	u32 reg;

	reg = पढ़ोl(hbclk->reg);
	reg &= ~HB_PLL_RESET;
	ग_लिखोl(reg, hbclk->reg);

	जबतक ((पढ़ोl(hbclk->reg) & HB_PLL_LOCK) == 0)
		;
	जबतक ((पढ़ोl(hbclk->reg) & HB_PLL_LOCK_500) == 0)
		;

	वापस 0;
पूर्ण

अटल व्योम clk_pll_unprepare(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा hb_clk *hbclk = to_hb_clk(hwclk);
	u32 reg;

	reg = पढ़ोl(hbclk->reg);
	reg |= HB_PLL_RESET;
	ग_लिखोl(reg, hbclk->reg);
पूर्ण

अटल पूर्णांक clk_pll_enable(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा hb_clk *hbclk = to_hb_clk(hwclk);
	u32 reg;

	reg = पढ़ोl(hbclk->reg);
	reg |= HB_PLL_EXT_ENA;
	ग_लिखोl(reg, hbclk->reg);

	वापस 0;
पूर्ण

अटल व्योम clk_pll_disable(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा hb_clk *hbclk = to_hb_clk(hwclk);
	u32 reg;

	reg = पढ़ोl(hbclk->reg);
	reg &= ~HB_PLL_EXT_ENA;
	ग_लिखोl(reg, hbclk->reg);
पूर्ण

अटल अचिन्हित दीर्घ clk_pll_recalc_rate(काष्ठा clk_hw *hwclk,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hb_clk *hbclk = to_hb_clk(hwclk);
	अचिन्हित दीर्घ भागf, भागq, vco_freq, reg;

	reg = पढ़ोl(hbclk->reg);
	अगर (reg & HB_PLL_EXT_BYPASS)
		वापस parent_rate;

	भागf = (reg & HB_PLL_DIVF_MASK) >> HB_PLL_DIVF_SHIFT;
	भागq = (reg & HB_PLL_DIVQ_MASK) >> HB_PLL_DIVQ_SHIFT;
	vco_freq = parent_rate * (भागf + 1);

	वापस vco_freq / (1 << भागq);
पूर्ण

अटल व्योम clk_pll_calc(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ ref_freq,
			u32 *pभागq, u32 *pभागf)
अणु
	u32 भागq, भागf;
	अचिन्हित दीर्घ vco_freq;

	अगर (rate < HB_PLL_MIN_FREQ)
		rate = HB_PLL_MIN_FREQ;
	अगर (rate > HB_PLL_MAX_FREQ)
		rate = HB_PLL_MAX_FREQ;

	क्रम (भागq = 1; भागq <= 6; भागq++) अणु
		अगर ((rate * (1 << भागq)) >= HB_PLL_VCO_MIN_FREQ)
			अवरोध;
	पूर्ण

	vco_freq = rate * (1 << भागq);
	भागf = (vco_freq + (ref_freq / 2)) / ref_freq;
	भागf--;

	*pभागq = भागq;
	*pभागf = भागf;
पूर्ण

अटल दीर्घ clk_pll_round_rate(काष्ठा clk_hw *hwclk, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *parent_rate)
अणु
	u32 भागq, भागf;
	अचिन्हित दीर्घ ref_freq = *parent_rate;

	clk_pll_calc(rate, ref_freq, &भागq, &भागf);

	वापस (ref_freq * (भागf + 1)) / (1 << भागq);
पूर्ण

अटल पूर्णांक clk_pll_set_rate(काष्ठा clk_hw *hwclk, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hb_clk *hbclk = to_hb_clk(hwclk);
	u32 भागq, भागf;
	u32 reg;

	clk_pll_calc(rate, parent_rate, &भागq, &भागf);

	reg = पढ़ोl(hbclk->reg);
	अगर (भागf != ((reg & HB_PLL_DIVF_MASK) >> HB_PLL_DIVF_SHIFT)) अणु
		/* Need to re-lock PLL, so put it पूर्णांकo bypass mode */
		reg |= HB_PLL_EXT_BYPASS;
		ग_लिखोl(reg | HB_PLL_EXT_BYPASS, hbclk->reg);

		ग_लिखोl(reg | HB_PLL_RESET, hbclk->reg);
		reg &= ~(HB_PLL_DIVF_MASK | HB_PLL_DIVQ_MASK);
		reg |= (भागf << HB_PLL_DIVF_SHIFT) | (भागq << HB_PLL_DIVQ_SHIFT);
		ग_लिखोl(reg | HB_PLL_RESET, hbclk->reg);
		ग_लिखोl(reg, hbclk->reg);

		जबतक ((पढ़ोl(hbclk->reg) & HB_PLL_LOCK) == 0)
			;
		जबतक ((पढ़ोl(hbclk->reg) & HB_PLL_LOCK_500) == 0)
			;
		reg |= HB_PLL_EXT_ENA;
		reg &= ~HB_PLL_EXT_BYPASS;
	पूर्ण अन्यथा अणु
		ग_लिखोl(reg | HB_PLL_EXT_BYPASS, hbclk->reg);
		reg &= ~HB_PLL_DIVQ_MASK;
		reg |= भागq << HB_PLL_DIVQ_SHIFT;
		ग_लिखोl(reg | HB_PLL_EXT_BYPASS, hbclk->reg);
	पूर्ण
	ग_लिखोl(reg, hbclk->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pll_ops = अणु
	.prepare = clk_pll_prepare,
	.unprepare = clk_pll_unprepare,
	.enable = clk_pll_enable,
	.disable = clk_pll_disable,
	.recalc_rate = clk_pll_recalc_rate,
	.round_rate = clk_pll_round_rate,
	.set_rate = clk_pll_set_rate,
पूर्ण;

अटल अचिन्हित दीर्घ clk_cpu_periphclk_recalc_rate(काष्ठा clk_hw *hwclk,
						   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hb_clk *hbclk = to_hb_clk(hwclk);
	u32 भाग = (पढ़ोl(hbclk->reg) & HB_A9_PCLK_DIV) ? 8 : 4;
	वापस parent_rate / भाग;
पूर्ण

अटल स्थिर काष्ठा clk_ops a9periphclk_ops = अणु
	.recalc_rate = clk_cpu_periphclk_recalc_rate,
पूर्ण;

अटल अचिन्हित दीर्घ clk_cpu_a9bclk_recalc_rate(काष्ठा clk_hw *hwclk,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hb_clk *hbclk = to_hb_clk(hwclk);
	u32 भाग = (पढ़ोl(hbclk->reg) & HB_A9_BCLK_DIV_MASK) >> HB_A9_BCLK_DIV_SHIFT;

	वापस parent_rate / (भाग + 2);
पूर्ण

अटल स्थिर काष्ठा clk_ops a9bclk_ops = अणु
	.recalc_rate = clk_cpu_a9bclk_recalc_rate,
पूर्ण;

अटल अचिन्हित दीर्घ clk_periclk_recalc_rate(काष्ठा clk_hw *hwclk,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hb_clk *hbclk = to_hb_clk(hwclk);
	u32 भाग;

	भाग = पढ़ोl(hbclk->reg) & 0x1f;
	भाग++;
	भाग *= 2;

	वापस parent_rate / भाग;
पूर्ण

अटल दीर्घ clk_periclk_round_rate(काष्ठा clk_hw *hwclk, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *parent_rate)
अणु
	u32 भाग;

	भाग = *parent_rate / rate;
	भाग++;
	भाग &= ~0x1;

	वापस *parent_rate / भाग;
पूर्ण

अटल पूर्णांक clk_periclk_set_rate(काष्ठा clk_hw *hwclk, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hb_clk *hbclk = to_hb_clk(hwclk);
	u32 भाग;

	भाग = parent_rate / rate;
	अगर (भाग & 0x1)
		वापस -EINVAL;

	ग_लिखोl(भाग >> 1, hbclk->reg);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops periclk_ops = अणु
	.recalc_rate = clk_periclk_recalc_rate,
	.round_rate = clk_periclk_round_rate,
	.set_rate = clk_periclk_set_rate,
पूर्ण;

अटल व्योम __init hb_clk_init(काष्ठा device_node *node, स्थिर काष्ठा clk_ops *ops, अचिन्हित दीर्घ clkflags)
अणु
	u32 reg;
	काष्ठा hb_clk *hb_clk;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parent_name;
	काष्ठा clk_init_data init;
	काष्ठा device_node *srnp;
	पूर्णांक rc;

	rc = of_property_पढ़ो_u32(node, "reg", &reg);
	अगर (WARN_ON(rc))
		वापस;

	hb_clk = kzalloc(माप(*hb_clk), GFP_KERNEL);
	अगर (WARN_ON(!hb_clk))
		वापस;

	/* Map प्रणाली रेजिस्टरs */
	srnp = of_find_compatible_node(शून्य, शून्य, "calxeda,hb-sregs");
	hb_clk->reg = of_iomap(srnp, 0);
	of_node_put(srnp);
	BUG_ON(!hb_clk->reg);
	hb_clk->reg += reg;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	init.name = clk_name;
	init.ops = ops;
	init.flags = clkflags;
	parent_name = of_clk_get_parent_name(node, 0);
	init.parent_names = &parent_name;
	init.num_parents = 1;

	hb_clk->hw.init = &init;

	rc = clk_hw_रेजिस्टर(शून्य, &hb_clk->hw);
	अगर (WARN_ON(rc)) अणु
		kमुक्त(hb_clk);
		वापस;
	पूर्ण
	of_clk_add_hw_provider(node, of_clk_hw_simple_get, &hb_clk->hw);
पूर्ण

अटल व्योम __init hb_pll_init(काष्ठा device_node *node)
अणु
	hb_clk_init(node, &clk_pll_ops, 0);
पूर्ण
CLK_OF_DECLARE(hb_pll, "calxeda,hb-pll-clock", hb_pll_init);

अटल व्योम __init hb_a9periph_init(काष्ठा device_node *node)
अणु
	hb_clk_init(node, &a9periphclk_ops, 0);
पूर्ण
CLK_OF_DECLARE(hb_a9periph, "calxeda,hb-a9periph-clock", hb_a9periph_init);

अटल व्योम __init hb_a9bus_init(काष्ठा device_node *node)
अणु
	hb_clk_init(node, &a9bclk_ops, CLK_IS_CRITICAL);
पूर्ण
CLK_OF_DECLARE(hb_a9bus, "calxeda,hb-a9bus-clock", hb_a9bus_init);

अटल व्योम __init hb_emmc_init(काष्ठा device_node *node)
अणु
	hb_clk_init(node, &periclk_ops, 0);
पूर्ण
CLK_OF_DECLARE(hb_emmc, "calxeda,hb-emmc-clock", hb_emmc_init);
