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

काष्ठा uniphier_clk_mux अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक reg;
	स्थिर अचिन्हित पूर्णांक *masks;
	स्थिर अचिन्हित पूर्णांक *vals;
पूर्ण;

#घोषणा to_uniphier_clk_mux(_hw) container_of(_hw, काष्ठा uniphier_clk_mux, hw)

अटल पूर्णांक uniphier_clk_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा uniphier_clk_mux *mux = to_uniphier_clk_mux(hw);

	वापस regmap_ग_लिखो_bits(mux->regmap, mux->reg, mux->masks[index],
				 mux->vals[index]);
पूर्ण

अटल u8 uniphier_clk_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा uniphier_clk_mux *mux = to_uniphier_clk_mux(hw);
	अचिन्हित पूर्णांक num_parents = clk_hw_get_num_parents(hw);
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक i;

	ret = regmap_पढ़ो(mux->regmap, mux->reg, &val);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < num_parents; i++)
		अगर ((mux->masks[i] & val) == mux->vals[i])
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा clk_ops uniphier_clk_mux_ops = अणु
	.determine_rate = __clk_mux_determine_rate,
	.set_parent = uniphier_clk_mux_set_parent,
	.get_parent = uniphier_clk_mux_get_parent,
पूर्ण;

काष्ठा clk_hw *uniphier_clk_रेजिस्टर_mux(काष्ठा device *dev,
					 काष्ठा regmap *regmap,
					 स्थिर अक्षर *name,
				स्थिर काष्ठा uniphier_clk_mux_data *data)
अणु
	काष्ठा uniphier_clk_mux *mux;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	mux = devm_kzalloc(dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &uniphier_clk_mux_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = data->parent_names;
	init.num_parents = data->num_parents;

	mux->regmap = regmap;
	mux->reg = data->reg;
	mux->masks = data->masks;
	mux->vals = data->vals;
	mux->hw.init = &init;

	ret = devm_clk_hw_रेजिस्टर(dev, &mux->hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस &mux->hw;
पूर्ण
