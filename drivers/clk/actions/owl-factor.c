<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// OWL factor घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "owl-factor.h"

अटल अचिन्हित पूर्णांक _get_table_maxval(स्थिर काष्ठा clk_factor_table *table)
अणु
	अचिन्हित पूर्णांक maxval = 0;
	स्थिर काष्ठा clk_factor_table *clkt;

	क्रम (clkt = table; clkt->भाग; clkt++)
		अगर (clkt->val > maxval)
			maxval = clkt->val;
	वापस maxval;
पूर्ण

अटल पूर्णांक _get_table_भाग_mul(स्थिर काष्ठा clk_factor_table *table,
			अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक *mul, अचिन्हित पूर्णांक *भाग)
अणु
	स्थिर काष्ठा clk_factor_table *clkt;

	क्रम (clkt = table; clkt->भाग; clkt++) अणु
		अगर (clkt->val == val) अणु
			*mul = clkt->mul;
			*भाग = clkt->भाग;
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक _get_table_val(स्थिर काष्ठा clk_factor_table *table,
			अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	स्थिर काष्ठा clk_factor_table *clkt;
	पूर्णांक val = -1;
	u64 calc_rate;

	क्रम (clkt = table; clkt->भाग; clkt++) अणु
		calc_rate = parent_rate * clkt->mul;
		करो_भाग(calc_rate, clkt->भाग);

		अगर ((अचिन्हित दीर्घ)calc_rate <= rate) अणु
			val = clkt->val;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (val == -1)
		val = _get_table_maxval(table);

	वापस val;
पूर्ण

अटल पूर्णांक owl_clk_val_best(स्थिर काष्ठा owl_factor_hw *factor_hw,
			काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ *best_parent_rate)
अणु
	स्थिर काष्ठा clk_factor_table *clkt = factor_hw->table;
	अचिन्हित दीर्घ parent_rate, try_parent_rate, best = 0, cur_rate;
	अचिन्हित दीर्घ parent_rate_saved = *best_parent_rate;
	पूर्णांक bestval = 0;

	अगर (!rate)
		rate = 1;

	अगर (!(clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)) अणु
		parent_rate = *best_parent_rate;
		bestval = _get_table_val(clkt, rate, parent_rate);
		वापस bestval;
	पूर्ण

	क्रम (clkt = factor_hw->table; clkt->भाग; clkt++) अणु
		try_parent_rate = rate * clkt->भाग / clkt->mul;

		अगर (try_parent_rate == parent_rate_saved) अणु
			pr_debug("%s: [%d %d %d] found try_parent_rate %ld\n",
				__func__, clkt->val, clkt->mul, clkt->भाग,
				try_parent_rate);
			/*
			 * It's the most ideal हाल अगर the requested rate can be
			 * भागided from parent घड़ी without any need to change
			 * parent rate, so वापस the भागider immediately.
			 */
			*best_parent_rate = parent_rate_saved;
			वापस clkt->val;
		पूर्ण

		parent_rate = clk_hw_round_rate(clk_hw_get_parent(hw),
				try_parent_rate);
		cur_rate = DIV_ROUND_UP(parent_rate, clkt->भाग) * clkt->mul;
		अगर (cur_rate <= rate && cur_rate > best) अणु
			bestval = clkt->val;
			best = cur_rate;
			*best_parent_rate = parent_rate;
		पूर्ण
	पूर्ण

	अगर (!bestval) अणु
		bestval = _get_table_maxval(clkt);
		*best_parent_rate = clk_hw_round_rate(
				clk_hw_get_parent(hw), 1);
	पूर्ण

	वापस bestval;
पूर्ण

दीर्घ owl_factor_helper_round_rate(काष्ठा owl_clk_common *common,
				स्थिर काष्ठा owl_factor_hw *factor_hw,
				अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	स्थिर काष्ठा clk_factor_table *clkt = factor_hw->table;
	अचिन्हित पूर्णांक val, mul = 0, भाग = 1;

	val = owl_clk_val_best(factor_hw, &common->hw, rate, parent_rate);
	_get_table_भाग_mul(clkt, val, &mul, &भाग);

	वापस *parent_rate * mul / भाग;
पूर्ण

अटल दीर्घ owl_factor_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा owl_factor *factor = hw_to_owl_factor(hw);
	काष्ठा owl_factor_hw *factor_hw = &factor->factor_hw;

	वापस owl_factor_helper_round_rate(&factor->common, factor_hw,
					rate, parent_rate);
पूर्ण

अचिन्हित दीर्घ owl_factor_helper_recalc_rate(काष्ठा owl_clk_common *common,
					 स्थिर काष्ठा owl_factor_hw *factor_hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	स्थिर काष्ठा clk_factor_table *clkt = factor_hw->table;
	अचिन्हित दीर्घ दीर्घ पूर्णांक rate;
	u32 reg, val, mul, भाग;

	भाग = 0;
	mul = 0;

	regmap_पढ़ो(common->regmap, factor_hw->reg, &reg);

	val = reg >> factor_hw->shअगरt;
	val &= भाग_mask(factor_hw);

	_get_table_भाग_mul(clkt, val, &mul, &भाग);
	अगर (!भाग) अणु
		WARN(!(factor_hw->fct_flags & CLK_DIVIDER_ALLOW_ZERO),
			"%s: Zero divisor and CLK_DIVIDER_ALLOW_ZERO not set\n",
			__clk_get_name(common->hw.clk));
		वापस parent_rate;
	पूर्ण

	rate = (अचिन्हित दीर्घ दीर्घ पूर्णांक)parent_rate * mul;
	करो_भाग(rate, भाग);

	वापस rate;
पूर्ण

अटल अचिन्हित दीर्घ owl_factor_recalc_rate(काष्ठा clk_hw *hw,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा owl_factor *factor = hw_to_owl_factor(hw);
	काष्ठा owl_factor_hw *factor_hw = &factor->factor_hw;
	काष्ठा owl_clk_common *common = &factor->common;

	वापस owl_factor_helper_recalc_rate(common, factor_hw, parent_rate);
पूर्ण

पूर्णांक owl_factor_helper_set_rate(स्थिर काष्ठा owl_clk_common *common,
				स्थिर काष्ठा owl_factor_hw *factor_hw,
				अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	u32 val, reg;

	val = _get_table_val(factor_hw->table, rate, parent_rate);

	अगर (val > भाग_mask(factor_hw))
		val = भाग_mask(factor_hw);

	regmap_पढ़ो(common->regmap, factor_hw->reg, &reg);

	reg &= ~(भाग_mask(factor_hw) << factor_hw->shअगरt);
	reg |= val << factor_hw->shअगरt;

	regmap_ग_लिखो(common->regmap, factor_hw->reg, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक owl_factor_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा owl_factor *factor = hw_to_owl_factor(hw);
	काष्ठा owl_factor_hw *factor_hw = &factor->factor_hw;
	काष्ठा owl_clk_common *common = &factor->common;

	वापस owl_factor_helper_set_rate(common, factor_hw,
					rate, parent_rate);
पूर्ण

स्थिर काष्ठा clk_ops owl_factor_ops = अणु
	.round_rate	= owl_factor_round_rate,
	.recalc_rate	= owl_factor_recalc_rate,
	.set_rate	= owl_factor_set_rate,
पूर्ण;
