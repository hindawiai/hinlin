<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2013 Boris BREZILLON <b.brezillon@overkiz.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "pmc.h"

#घोषणा PLL_STATUS_MASK(id)	(1 << (1 + (id)))
#घोषणा PLL_REG(id)		(AT91_CKGR_PLLAR + ((id) * 4))
#घोषणा PLL_DIV_MASK		0xff
#घोषणा PLL_DIV_MAX		PLL_DIV_MASK
#घोषणा PLL_DIV(reg)		((reg) & PLL_DIV_MASK)
#घोषणा PLL_MUL(reg, layout)	(((reg) >> (layout)->mul_shअगरt) & \
				 (layout)->mul_mask)
#घोषणा PLL_MUL_MIN		2
#घोषणा PLL_MUL_MASK(layout)	((layout)->mul_mask)
#घोषणा PLL_MUL_MAX(layout)	(PLL_MUL_MASK(layout) + 1)
#घोषणा PLL_ICPR_SHIFT(id)	((id) * 16)
#घोषणा PLL_ICPR_MASK(id)	(0xffff << PLL_ICPR_SHIFT(id))
#घोषणा PLL_MAX_COUNT		0x3f
#घोषणा PLL_COUNT_SHIFT		8
#घोषणा PLL_OUT_SHIFT		14
#घोषणा PLL_MAX_ID		1

#घोषणा to_clk_pll(hw) container_of(hw, काष्ठा clk_pll, hw)

काष्ठा clk_pll अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u8 id;
	u8 भाग;
	u8 range;
	u16 mul;
	स्थिर काष्ठा clk_pll_layout *layout;
	स्थिर काष्ठा clk_pll_अक्षरacteristics *अक्षरacteristics;
पूर्ण;

अटल अंतरभूत bool clk_pll_पढ़ोy(काष्ठा regmap *regmap, पूर्णांक id)
अणु
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(regmap, AT91_PMC_SR, &status);

	वापस status & PLL_STATUS_MASK(id) ? 1 : 0;
पूर्ण

अटल पूर्णांक clk_pll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	काष्ठा regmap *regmap = pll->regmap;
	स्थिर काष्ठा clk_pll_layout *layout = pll->layout;
	स्थिर काष्ठा clk_pll_अक्षरacteristics *अक्षरacteristics =
							pll->अक्षरacteristics;
	u8 id = pll->id;
	u32 mask = PLL_STATUS_MASK(id);
	पूर्णांक offset = PLL_REG(id);
	u8 out = 0;
	अचिन्हित पूर्णांक pllr;
	अचिन्हित पूर्णांक status;
	u8 भाग;
	u16 mul;

	regmap_पढ़ो(regmap, offset, &pllr);
	भाग = PLL_DIV(pllr);
	mul = PLL_MUL(pllr, layout);

	regmap_पढ़ो(regmap, AT91_PMC_SR, &status);
	अगर ((status & mask) &&
	    (भाग == pll->भाग && mul == pll->mul))
		वापस 0;

	अगर (अक्षरacteristics->out)
		out = अक्षरacteristics->out[pll->range];

	अगर (अक्षरacteristics->icpll)
		regmap_update_bits(regmap, AT91_PMC_PLLICPR, PLL_ICPR_MASK(id),
			अक्षरacteristics->icpll[pll->range] << PLL_ICPR_SHIFT(id));

	regmap_update_bits(regmap, offset, layout->pllr_mask,
			pll->भाग | (PLL_MAX_COUNT << PLL_COUNT_SHIFT) |
			(out << PLL_OUT_SHIFT) |
			((pll->mul & layout->mul_mask) << layout->mul_shअगरt));

	जबतक (!clk_pll_पढ़ोy(regmap, pll->id))
		cpu_relax();

	वापस 0;
पूर्ण

अटल पूर्णांक clk_pll_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);

	वापस clk_pll_पढ़ोy(pll->regmap, pll->id);
पूर्ण

अटल व्योम clk_pll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	अचिन्हित पूर्णांक mask = pll->layout->pllr_mask;

	regmap_update_bits(pll->regmap, PLL_REG(pll->id), mask, ~mask);
पूर्ण

अटल अचिन्हित दीर्घ clk_pll_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);

	अगर (!pll->भाग || !pll->mul)
		वापस 0;

	वापस (parent_rate / pll->भाग) * (pll->mul + 1);
पूर्ण

अटल दीर्घ clk_pll_get_best_भाग_mul(काष्ठा clk_pll *pll, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ parent_rate,
				     u32 *भाग, u32 *mul,
				     u32 *index) अणु
	स्थिर काष्ठा clk_pll_layout *layout = pll->layout;
	स्थिर काष्ठा clk_pll_अक्षरacteristics *अक्षरacteristics =
							pll->अक्षरacteristics;
	अचिन्हित दीर्घ bestreमुख्यder = अच_दीर्घ_उच्च;
	अचिन्हित दीर्घ maxभाग, minभाग, पंचांगpभाग;
	दीर्घ bestrate = -दुस्फल;
	अचिन्हित दीर्घ bestभाग;
	अचिन्हित दीर्घ besपंचांगul;
	पूर्णांक i = 0;

	/* Check अगर parent_rate is a valid input rate */
	अगर (parent_rate < अक्षरacteristics->input.min)
		वापस -दुस्फल;

	/*
	 * Calculate minimum भागider based on the minimum multiplier, the
	 * parent_rate and the requested rate.
	 * Should always be 2 according to the input and output अक्षरacteristics
	 * of the PLL blocks.
	 */
	minभाग = (parent_rate * PLL_MUL_MIN) / rate;
	अगर (!minभाग)
		minभाग = 1;

	अगर (parent_rate > अक्षरacteristics->input.max) अणु
		पंचांगpभाग = DIV_ROUND_UP(parent_rate, अक्षरacteristics->input.max);
		अगर (पंचांगpभाग > PLL_DIV_MAX)
			वापस -दुस्फल;

		अगर (पंचांगpभाग > minभाग)
			minभाग = पंचांगpभाग;
	पूर्ण

	/*
	 * Calculate the maximum भागider which is limited by PLL रेजिस्टर
	 * layout (limited by the MUL or DIV field size).
	 */
	maxभाग = DIV_ROUND_UP(parent_rate * PLL_MUL_MAX(layout), rate);
	अगर (maxभाग > PLL_DIV_MAX)
		maxभाग = PLL_DIV_MAX;

	/*
	 * Iterate over the acceptable भागider values to find the best
	 * भागider/multiplier pair (the one that generates the बंदst
	 * rate to the requested one).
	 */
	क्रम (पंचांगpभाग = minभाग; पंचांगpभाग <= maxभाग; पंचांगpभाग++) अणु
		अचिन्हित दीर्घ reमुख्यder;
		अचिन्हित दीर्घ पंचांगprate;
		अचिन्हित दीर्घ पंचांगpmul;

		/*
		 * Calculate the multiplier associated with the current
		 * भागider that provide the बंदst rate to the requested one.
		 */
		पंचांगpmul = DIV_ROUND_CLOSEST(rate, parent_rate / पंचांगpभाग);
		पंचांगprate = (parent_rate / पंचांगpभाग) * पंचांगpmul;
		अगर (पंचांगprate > rate)
			reमुख्यder = पंचांगprate - rate;
		अन्यथा
			reमुख्यder = rate - पंचांगprate;

		/*
		 * Compare the reमुख्यder with the best reमुख्यder found until
		 * now and elect a new best multiplier/भागider pair अगर the
		 * current reमुख्यder is smaller than the best one.
		 */
		अगर (reमुख्यder < bestreमुख्यder) अणु
			bestreमुख्यder = reमुख्यder;
			bestभाग = पंचांगpभाग;
			besपंचांगul = पंचांगpmul;
			bestrate = पंचांगprate;
		पूर्ण

		/*
		 * We've found a perfect match!
		 * Stop searching now and use this multiplier/भागider pair.
		 */
		अगर (!reमुख्यder)
			अवरोध;
	पूर्ण

	/* We haven't found any multiplier/भागider pair => वापस -दुस्फल */
	अगर (bestrate < 0)
		वापस bestrate;

	/* Check अगर bestrate is a valid output rate  */
	क्रम (i = 0; i < अक्षरacteristics->num_output; i++) अणु
		अगर (bestrate >= अक्षरacteristics->output[i].min &&
		    bestrate <= अक्षरacteristics->output[i].max)
			अवरोध;
	पूर्ण

	अगर (i >= अक्षरacteristics->num_output)
		वापस -दुस्फल;

	अगर (भाग)
		*भाग = bestभाग;
	अगर (mul)
		*mul = besपंचांगul - 1;
	अगर (index)
		*index = i;

	वापस bestrate;
पूर्ण

अटल दीर्घ clk_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);

	वापस clk_pll_get_best_भाग_mul(pll, rate, *parent_rate,
					शून्य, शून्य, शून्य);
पूर्ण

अटल पूर्णांक clk_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	दीर्घ ret;
	u32 भाग;
	u32 mul;
	u32 index;

	ret = clk_pll_get_best_भाग_mul(pll, rate, parent_rate,
				       &भाग, &mul, &index);
	अगर (ret < 0)
		वापस ret;

	pll->range = index;
	pll->भाग = भाग;
	pll->mul = mul;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops pll_ops = अणु
	.prepare = clk_pll_prepare,
	.unprepare = clk_pll_unprepare,
	.is_prepared = clk_pll_is_prepared,
	.recalc_rate = clk_pll_recalc_rate,
	.round_rate = clk_pll_round_rate,
	.set_rate = clk_pll_set_rate,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_pll(काष्ठा regmap *regmap, स्थिर अक्षर *name,
		      स्थिर अक्षर *parent_name, u8 id,
		      स्थिर काष्ठा clk_pll_layout *layout,
		      स्थिर काष्ठा clk_pll_अक्षरacteristics *अक्षरacteristics)
अणु
	काष्ठा clk_pll *pll;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक offset = PLL_REG(id);
	अचिन्हित पूर्णांक pllr;
	पूर्णांक ret;

	अगर (id > PLL_MAX_ID)
		वापस ERR_PTR(-EINVAL);

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &pll_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = CLK_SET_RATE_GATE;

	pll->id = id;
	pll->hw.init = &init;
	pll->layout = layout;
	pll->अक्षरacteristics = अक्षरacteristics;
	pll->regmap = regmap;
	regmap_पढ़ो(regmap, offset, &pllr);
	pll->भाग = PLL_DIV(pllr);
	pll->mul = PLL_MUL(pllr, layout);

	hw = &pll->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &pll->hw);
	अगर (ret) अणु
		kमुक्त(pll);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण


स्थिर काष्ठा clk_pll_layout at91rm9200_pll_layout = अणु
	.pllr_mask = 0x7FFFFFF,
	.mul_shअगरt = 16,
	.mul_mask = 0x7FF,
पूर्ण;

स्थिर काष्ठा clk_pll_layout at91sam9g45_pll_layout = अणु
	.pllr_mask = 0xFFFFFF,
	.mul_shअगरt = 16,
	.mul_mask = 0xFF,
पूर्ण;

स्थिर काष्ठा clk_pll_layout at91sam9g20_pllb_layout = अणु
	.pllr_mask = 0x3FFFFF,
	.mul_shअगरt = 16,
	.mul_mask = 0x3F,
पूर्ण;

स्थिर काष्ठा clk_pll_layout sama5d3_pll_layout = अणु
	.pllr_mask = 0x1FFFFFF,
	.mul_shअगरt = 18,
	.mul_mask = 0x7F,
पूर्ण;
