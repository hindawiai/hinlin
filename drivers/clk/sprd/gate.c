<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Spपढ़ोtrum gate घड़ी driver
//
// Copyright (C) 2017 Spपढ़ोtrum, Inc.
// Author: Chunyan Zhang <chunyan.zhang@spपढ़ोtrum.com>

#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>

#समावेश "gate.h"

अटल व्योम clk_gate_toggle(स्थिर काष्ठा sprd_gate *sg, bool en)
अणु
	स्थिर काष्ठा sprd_clk_common *common = &sg->common;
	अचिन्हित पूर्णांक reg;
	bool set = sg->flags & CLK_GATE_SET_TO_DISABLE ? true : false;

	set ^= en;

	regmap_पढ़ो(common->regmap, common->reg, &reg);

	अगर (set)
		reg |= sg->enable_mask;
	अन्यथा
		reg &= ~sg->enable_mask;

	regmap_ग_लिखो(common->regmap, common->reg, reg);
पूर्ण

अटल व्योम clk_sc_gate_toggle(स्थिर काष्ठा sprd_gate *sg, bool en)
अणु
	स्थिर काष्ठा sprd_clk_common *common = &sg->common;
	bool set = sg->flags & CLK_GATE_SET_TO_DISABLE ? 1 : 0;
	अचिन्हित पूर्णांक offset;

	set ^= en;

	/*
	 * Each set/clear gate घड़ी has three रेजिस्टरs:
	 * common->reg			- base रेजिस्टर
	 * common->reg + offset		- set रेजिस्टर
	 * common->reg + 2 * offset	- clear रेजिस्टर
	 */
	offset = set ? sg->sc_offset : sg->sc_offset * 2;

	regmap_ग_लिखो(common->regmap, common->reg + offset,
			  sg->enable_mask);
पूर्ण

अटल व्योम sprd_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sprd_gate *sg = hw_to_sprd_gate(hw);

	clk_gate_toggle(sg, false);
पूर्ण

अटल पूर्णांक sprd_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sprd_gate *sg = hw_to_sprd_gate(hw);

	clk_gate_toggle(sg, true);

	वापस 0;
पूर्ण

अटल व्योम sprd_sc_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sprd_gate *sg = hw_to_sprd_gate(hw);

	clk_sc_gate_toggle(sg, false);
पूर्ण

अटल पूर्णांक sprd_sc_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sprd_gate *sg = hw_to_sprd_gate(hw);

	clk_sc_gate_toggle(sg, true);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_pll_sc_gate_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा sprd_gate *sg = hw_to_sprd_gate(hw);

	clk_sc_gate_toggle(sg, true);
	udelay(sg->udelay);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा sprd_gate *sg = hw_to_sprd_gate(hw);
	काष्ठा sprd_clk_common *common = &sg->common;
	काष्ठा clk_hw *parent;
	अचिन्हित पूर्णांक reg;

	अगर (sg->flags & SPRD_GATE_NON_AON) अणु
		parent = clk_hw_get_parent(hw);
		अगर (!parent || !clk_hw_is_enabled(parent))
			वापस 0;
	पूर्ण

	regmap_पढ़ो(common->regmap, common->reg, &reg);

	अगर (sg->flags & CLK_GATE_SET_TO_DISABLE)
		reg ^= sg->enable_mask;

	reg &= sg->enable_mask;

	वापस reg ? 1 : 0;
पूर्ण

स्थिर काष्ठा clk_ops sprd_gate_ops = अणु
	.disable	= sprd_gate_disable,
	.enable		= sprd_gate_enable,
	.is_enabled	= sprd_gate_is_enabled,
पूर्ण;
EXPORT_SYMBOL_GPL(sprd_gate_ops);

स्थिर काष्ठा clk_ops sprd_sc_gate_ops = अणु
	.disable	= sprd_sc_gate_disable,
	.enable		= sprd_sc_gate_enable,
	.is_enabled	= sprd_gate_is_enabled,
पूर्ण;
EXPORT_SYMBOL_GPL(sprd_sc_gate_ops);

स्थिर काष्ठा clk_ops sprd_pll_sc_gate_ops = अणु
	.unprepare	= sprd_sc_gate_disable,
	.prepare	= sprd_pll_sc_gate_prepare,
	.is_enabled	= sprd_gate_is_enabled,
पूर्ण;
EXPORT_SYMBOL_GPL(sprd_pll_sc_gate_ops);
