<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// OWL gate घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>

#समावेश "owl-gate.h"

व्योम owl_gate_set(स्थिर काष्ठा owl_clk_common *common,
		 स्थिर काष्ठा owl_gate_hw *gate_hw, bool enable)
अणु
	पूर्णांक set = gate_hw->gate_flags & CLK_GATE_SET_TO_DISABLE ? 1 : 0;
	u32 reg;

	set ^= enable;

	regmap_पढ़ो(common->regmap, gate_hw->reg, &reg);

	अगर (set)
		reg |= BIT(gate_hw->bit_idx);
	अन्यथा
		reg &= ~BIT(gate_hw->bit_idx);

	regmap_ग_लिखो(common->regmap, gate_hw->reg, reg);
पूर्ण

अटल व्योम owl_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_gate *gate = hw_to_owl_gate(hw);
	काष्ठा owl_clk_common *common = &gate->common;

	owl_gate_set(common, &gate->gate_hw, false);
पूर्ण

अटल पूर्णांक owl_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_gate *gate = hw_to_owl_gate(hw);
	काष्ठा owl_clk_common *common = &gate->common;

	owl_gate_set(common, &gate->gate_hw, true);

	वापस 0;
पूर्ण

पूर्णांक owl_gate_clk_is_enabled(स्थिर काष्ठा owl_clk_common *common,
		   स्थिर काष्ठा owl_gate_hw *gate_hw)
अणु
	u32 reg;

	regmap_पढ़ो(common->regmap, gate_hw->reg, &reg);

	अगर (gate_hw->gate_flags & CLK_GATE_SET_TO_DISABLE)
		reg ^= BIT(gate_hw->bit_idx);

	वापस !!(reg & BIT(gate_hw->bit_idx));
पूर्ण

अटल पूर्णांक owl_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_gate *gate = hw_to_owl_gate(hw);
	काष्ठा owl_clk_common *common = &gate->common;

	वापस owl_gate_clk_is_enabled(common, &gate->gate_hw);
पूर्ण

स्थिर काष्ठा clk_ops owl_gate_ops = अणु
	.disable	= owl_gate_disable,
	.enable		= owl_gate_enable,
	.is_enabled	= owl_gate_is_enabled,
पूर्ण;
