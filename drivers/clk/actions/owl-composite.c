<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// OWL composite घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>

#समावेश "owl-composite.h"

अटल u8 owl_comp_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_composite *comp = hw_to_owl_comp(hw);

	वापस owl_mux_helper_get_parent(&comp->common, &comp->mux_hw);
पूर्ण

अटल पूर्णांक owl_comp_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा owl_composite *comp = hw_to_owl_comp(hw);

	वापस owl_mux_helper_set_parent(&comp->common, &comp->mux_hw, index);
पूर्ण

अटल व्योम owl_comp_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_composite *comp = hw_to_owl_comp(hw);
	काष्ठा owl_clk_common *common = &comp->common;

	owl_gate_set(common, &comp->gate_hw, false);
पूर्ण

अटल पूर्णांक owl_comp_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_composite *comp = hw_to_owl_comp(hw);
	काष्ठा owl_clk_common *common = &comp->common;

	owl_gate_set(common, &comp->gate_hw, true);

	वापस 0;
पूर्ण

अटल पूर्णांक owl_comp_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_composite *comp = hw_to_owl_comp(hw);
	काष्ठा owl_clk_common *common = &comp->common;

	वापस owl_gate_clk_is_enabled(common, &comp->gate_hw);
पूर्ण

अटल दीर्घ owl_comp_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा owl_composite *comp = hw_to_owl_comp(hw);

	वापस owl_भागider_helper_round_rate(&comp->common, &comp->rate.भाग_hw,
					rate, parent_rate);
पूर्ण

अटल अचिन्हित दीर्घ owl_comp_भाग_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा owl_composite *comp = hw_to_owl_comp(hw);

	वापस owl_भागider_helper_recalc_rate(&comp->common, &comp->rate.भाग_hw,
					parent_rate);
पूर्ण

अटल पूर्णांक owl_comp_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा owl_composite *comp = hw_to_owl_comp(hw);

	वापस owl_भागider_helper_set_rate(&comp->common, &comp->rate.भाग_hw,
					rate, parent_rate);
पूर्ण

अटल दीर्घ owl_comp_fact_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा owl_composite *comp = hw_to_owl_comp(hw);

	वापस owl_factor_helper_round_rate(&comp->common,
					&comp->rate.factor_hw,
					rate, parent_rate);
पूर्ण

अटल अचिन्हित दीर्घ owl_comp_fact_recalc_rate(काष्ठा clk_hw *hw,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा owl_composite *comp = hw_to_owl_comp(hw);

	वापस owl_factor_helper_recalc_rate(&comp->common,
					&comp->rate.factor_hw,
					parent_rate);
पूर्ण

अटल पूर्णांक owl_comp_fact_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा owl_composite *comp = hw_to_owl_comp(hw);

	वापस owl_factor_helper_set_rate(&comp->common,
					&comp->rate.factor_hw,
					rate, parent_rate);
पूर्ण

अटल दीर्घ owl_comp_fix_fact_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा owl_composite *comp = hw_to_owl_comp(hw);
	काष्ठा clk_fixed_factor *fix_fact_hw = &comp->rate.fix_fact_hw;

	वापस comp->fix_fact_ops->round_rate(&fix_fact_hw->hw, rate, parent_rate);
पूर्ण

अटल अचिन्हित दीर्घ owl_comp_fix_fact_recalc_rate(काष्ठा clk_hw *hw,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा owl_composite *comp = hw_to_owl_comp(hw);
	काष्ठा clk_fixed_factor *fix_fact_hw = &comp->rate.fix_fact_hw;

	वापस comp->fix_fact_ops->recalc_rate(&fix_fact_hw->hw, parent_rate);

पूर्ण

अटल पूर्णांक owl_comp_fix_fact_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ parent_rate)
अणु
	/*
	 * We must report success but we can करो so unconditionally because
	 * owl_comp_fix_fact_round_rate वापसs values that ensure this call is
	 * a nop.
	 */

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops owl_comp_भाग_ops = अणु
	/* mux_ops */
	.get_parent	= owl_comp_get_parent,
	.set_parent	= owl_comp_set_parent,

	/* gate_ops */
	.disable	= owl_comp_disable,
	.enable		= owl_comp_enable,
	.is_enabled	= owl_comp_is_enabled,

	/* भाग_ops */
	.round_rate	= owl_comp_भाग_round_rate,
	.recalc_rate	= owl_comp_भाग_recalc_rate,
	.set_rate	= owl_comp_भाग_set_rate,
पूर्ण;


स्थिर काष्ठा clk_ops owl_comp_fact_ops = अणु
	/* mux_ops */
	.get_parent	= owl_comp_get_parent,
	.set_parent	= owl_comp_set_parent,

	/* gate_ops */
	.disable	= owl_comp_disable,
	.enable		= owl_comp_enable,
	.is_enabled	= owl_comp_is_enabled,

	/* fact_ops */
	.round_rate	= owl_comp_fact_round_rate,
	.recalc_rate	= owl_comp_fact_recalc_rate,
	.set_rate	= owl_comp_fact_set_rate,
पूर्ण;

स्थिर काष्ठा clk_ops owl_comp_fix_fact_ops = अणु
	/* gate_ops */
	.disable	= owl_comp_disable,
	.enable		= owl_comp_enable,
	.is_enabled	= owl_comp_is_enabled,

	/* fix_fact_ops */
	.round_rate	= owl_comp_fix_fact_round_rate,
	.recalc_rate	= owl_comp_fix_fact_recalc_rate,
	.set_rate	= owl_comp_fix_fact_set_rate,
पूर्ण;


स्थिर काष्ठा clk_ops owl_comp_pass_ops = अणु
	/* mux_ops */
	.get_parent	= owl_comp_get_parent,
	.set_parent	= owl_comp_set_parent,

	/* gate_ops */
	.disable	= owl_comp_disable,
	.enable		= owl_comp_enable,
	.is_enabled	= owl_comp_is_enabled,
पूर्ण;
