<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Socionext Inc.
 *   Author: Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>

#समावेश "clk-uniphier.h"

काष्ठा uniphier_clk_gate अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक bit;
पूर्ण;

#घोषणा to_uniphier_clk_gate(_hw) \
				container_of(_hw, काष्ठा uniphier_clk_gate, hw)

अटल पूर्णांक uniphier_clk_gate_endisable(काष्ठा clk_hw *hw, पूर्णांक enable)
अणु
	काष्ठा uniphier_clk_gate *gate = to_uniphier_clk_gate(hw);

	वापस regmap_ग_लिखो_bits(gate->regmap, gate->reg, BIT(gate->bit),
				 enable ? BIT(gate->bit) : 0);
पूर्ण

अटल पूर्णांक uniphier_clk_gate_enable(काष्ठा clk_hw *hw)
अणु
	वापस uniphier_clk_gate_endisable(hw, 1);
पूर्ण

अटल व्योम uniphier_clk_gate_disable(काष्ठा clk_hw *hw)
अणु
	अगर (uniphier_clk_gate_endisable(hw, 0) < 0)
		pr_warn("failed to disable clk\n");
पूर्ण

अटल पूर्णांक uniphier_clk_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा uniphier_clk_gate *gate = to_uniphier_clk_gate(hw);
	अचिन्हित पूर्णांक val;

	अगर (regmap_पढ़ो(gate->regmap, gate->reg, &val) < 0)
		pr_warn("is_enabled() may return wrong result\n");

	वापस !!(val & BIT(gate->bit));
पूर्ण

अटल स्थिर काष्ठा clk_ops uniphier_clk_gate_ops = अणु
	.enable = uniphier_clk_gate_enable,
	.disable = uniphier_clk_gate_disable,
	.is_enabled = uniphier_clk_gate_is_enabled,
पूर्ण;

काष्ठा clk_hw *uniphier_clk_रेजिस्टर_gate(काष्ठा device *dev,
					  काष्ठा regmap *regmap,
					  स्थिर अक्षर *name,
				स्थिर काष्ठा uniphier_clk_gate_data *data)
अणु
	काष्ठा uniphier_clk_gate *gate;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	gate = devm_kzalloc(dev, माप(*gate), GFP_KERNEL);
	अगर (!gate)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &uniphier_clk_gate_ops;
	init.flags = data->parent_name ? CLK_SET_RATE_PARENT : 0;
	init.parent_names = data->parent_name ? &data->parent_name : शून्य;
	init.num_parents = data->parent_name ? 1 : 0;

	gate->regmap = regmap;
	gate->reg = data->reg;
	gate->bit = data->bit;
	gate->hw.init = &init;

	ret = devm_clk_hw_रेजिस्टर(dev, &gate->hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस &gate->hw;
पूर्ण
