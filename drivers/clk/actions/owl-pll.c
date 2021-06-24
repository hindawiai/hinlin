<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// OWL pll घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>

#समावेश "owl-pll.h"

अटल u32 owl_pll_calculate_mul(काष्ठा owl_pll_hw *pll_hw, अचिन्हित दीर्घ rate)
अणु
	u32 mul;

	mul = DIV_ROUND_CLOSEST(rate, pll_hw->bfreq);
	अगर (mul < pll_hw->min_mul)
		mul = pll_hw->min_mul;
	अन्यथा अगर (mul > pll_hw->max_mul)
		mul = pll_hw->max_mul;

	वापस mul &= mul_mask(pll_hw);
पूर्ण

अटल अचिन्हित दीर्घ _get_table_rate(स्थिर काष्ठा clk_pll_table *table,
		अचिन्हित पूर्णांक val)
अणु
	स्थिर काष्ठा clk_pll_table *clkt;

	क्रम (clkt = table; clkt->rate; clkt++)
		अगर (clkt->val == val)
			वापस clkt->rate;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_pll_table *_get_pll_table(
		स्थिर काष्ठा clk_pll_table *table, अचिन्हित दीर्घ rate)
अणु
	स्थिर काष्ठा clk_pll_table *clkt;

	क्रम (clkt = table; clkt->rate; clkt++) अणु
		अगर (clkt->rate == rate) अणु
			table = clkt;
			अवरोध;
		पूर्ण अन्यथा अगर (clkt->rate < rate)
			table = clkt;
	पूर्ण

	वापस table;
पूर्ण

अटल दीर्घ owl_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा owl_pll *pll = hw_to_owl_pll(hw);
	काष्ठा owl_pll_hw *pll_hw = &pll->pll_hw;
	स्थिर काष्ठा clk_pll_table *clkt;
	u32 mul;

	अगर (pll_hw->table) अणु
		clkt = _get_pll_table(pll_hw->table, rate);
		वापस clkt->rate;
	पूर्ण

	/* fixed frequency */
	अगर (pll_hw->width == 0)
		वापस pll_hw->bfreq;

	mul = owl_pll_calculate_mul(pll_hw, rate);

	वापस pll_hw->bfreq * mul;
पूर्ण

अटल अचिन्हित दीर्घ owl_pll_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा owl_pll *pll = hw_to_owl_pll(hw);
	काष्ठा owl_pll_hw *pll_hw = &pll->pll_hw;
	स्थिर काष्ठा owl_clk_common *common = &pll->common;
	u32 val;

	अगर (pll_hw->table) अणु
		regmap_पढ़ो(common->regmap, pll_hw->reg, &val);

		val = val >> pll_hw->shअगरt;
		val &= mul_mask(pll_hw);

		वापस _get_table_rate(pll_hw->table, val);
	पूर्ण

	/* fixed frequency */
	अगर (pll_hw->width == 0)
		वापस pll_hw->bfreq;

	regmap_पढ़ो(common->regmap, pll_hw->reg, &val);

	val = val >> pll_hw->shअगरt;
	val &= mul_mask(pll_hw);

	वापस pll_hw->bfreq * val;
पूर्ण

अटल पूर्णांक owl_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_pll *pll = hw_to_owl_pll(hw);
	काष्ठा owl_pll_hw *pll_hw = &pll->pll_hw;
	स्थिर काष्ठा owl_clk_common *common = &pll->common;
	u32 reg;

	regmap_पढ़ो(common->regmap, pll_hw->reg, &reg);

	वापस !!(reg & BIT(pll_hw->bit_idx));
पूर्ण

अटल व्योम owl_pll_set(स्थिर काष्ठा owl_clk_common *common,
		       स्थिर काष्ठा owl_pll_hw *pll_hw, bool enable)
अणु
	u32 reg;

	regmap_पढ़ो(common->regmap, pll_hw->reg, &reg);

	अगर (enable)
		reg |= BIT(pll_hw->bit_idx);
	अन्यथा
		reg &= ~BIT(pll_hw->bit_idx);

	regmap_ग_लिखो(common->regmap, pll_hw->reg, reg);
पूर्ण

अटल पूर्णांक owl_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_pll *pll = hw_to_owl_pll(hw);
	स्थिर काष्ठा owl_clk_common *common = &pll->common;

	owl_pll_set(common, &pll->pll_hw, true);

	वापस 0;
पूर्ण

अटल व्योम owl_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_pll *pll = hw_to_owl_pll(hw);
	स्थिर काष्ठा owl_clk_common *common = &pll->common;

	owl_pll_set(common, &pll->pll_hw, false);
पूर्ण

अटल पूर्णांक owl_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा owl_pll *pll = hw_to_owl_pll(hw);
	काष्ठा owl_pll_hw *pll_hw = &pll->pll_hw;
	स्थिर काष्ठा owl_clk_common *common = &pll->common;
	स्थिर काष्ठा clk_pll_table *clkt;
	u32 val, reg;

	/* fixed frequency */
	अगर (pll_hw->width == 0)
		वापस 0;

	अगर (pll_hw->table) अणु
		clkt = _get_pll_table(pll_hw->table, rate);
		val = clkt->val;
	पूर्ण अन्यथा अणु
		val = owl_pll_calculate_mul(pll_hw, rate);
	पूर्ण

	regmap_पढ़ो(common->regmap, pll_hw->reg, &reg);

	reg &= ~mul_mask(pll_hw);
	reg |= val << pll_hw->shअगरt;

	regmap_ग_लिखो(common->regmap, pll_hw->reg, reg);

	udelay(pll_hw->delay);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops owl_pll_ops = अणु
	.enable = owl_pll_enable,
	.disable = owl_pll_disable,
	.is_enabled = owl_pll_is_enabled,
	.round_rate = owl_pll_round_rate,
	.recalc_rate = owl_pll_recalc_rate,
	.set_rate = owl_pll_set_rate,
पूर्ण;
