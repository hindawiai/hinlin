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

#घोषणा UNIPHIER_CLK_CPUGEAR_STAT	0	/* status */
#घोषणा UNIPHIER_CLK_CPUGEAR_SET	4	/* set */
#घोषणा UNIPHIER_CLK_CPUGEAR_UPD	8	/* update */
#घोषणा   UNIPHIER_CLK_CPUGEAR_UPD_BIT	BIT(0)

काष्ठा uniphier_clk_cpugear अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक regbase;
	अचिन्हित पूर्णांक mask;
पूर्ण;

#घोषणा to_uniphier_clk_cpugear(_hw) \
			container_of(_hw, काष्ठा uniphier_clk_cpugear, hw)

अटल पूर्णांक uniphier_clk_cpugear_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा uniphier_clk_cpugear *gear = to_uniphier_clk_cpugear(hw);
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_ग_लिखो_bits(gear->regmap,
				gear->regbase + UNIPHIER_CLK_CPUGEAR_SET,
				gear->mask, index);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो_bits(gear->regmap,
				gear->regbase + UNIPHIER_CLK_CPUGEAR_UPD,
				UNIPHIER_CLK_CPUGEAR_UPD_BIT,
				UNIPHIER_CLK_CPUGEAR_UPD_BIT);
	अगर (ret)
		वापस ret;

	वापस regmap_पढ़ो_poll_समयout(gear->regmap,
				gear->regbase + UNIPHIER_CLK_CPUGEAR_UPD,
				val, !(val & UNIPHIER_CLK_CPUGEAR_UPD_BIT),
				0, 1);
पूर्ण

अटल u8 uniphier_clk_cpugear_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा uniphier_clk_cpugear *gear = to_uniphier_clk_cpugear(hw);
	पूर्णांक num_parents = clk_hw_get_num_parents(hw);
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(gear->regmap,
			  gear->regbase + UNIPHIER_CLK_CPUGEAR_STAT, &val);
	अगर (ret)
		वापस ret;

	val &= gear->mask;

	वापस val < num_parents ? val : -EINVAL;
पूर्ण

अटल स्थिर काष्ठा clk_ops uniphier_clk_cpugear_ops = अणु
	.determine_rate = __clk_mux_determine_rate,
	.set_parent = uniphier_clk_cpugear_set_parent,
	.get_parent = uniphier_clk_cpugear_get_parent,
पूर्ण;

काष्ठा clk_hw *uniphier_clk_रेजिस्टर_cpugear(काष्ठा device *dev,
					 काष्ठा regmap *regmap,
					 स्थिर अक्षर *name,
				स्थिर काष्ठा uniphier_clk_cpugear_data *data)
अणु
	काष्ठा uniphier_clk_cpugear *gear;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	gear = devm_kzalloc(dev, माप(*gear), GFP_KERNEL);
	अगर (!gear)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &uniphier_clk_cpugear_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = data->parent_names;
	init.num_parents = data->num_parents;

	gear->regmap = regmap;
	gear->regbase = data->regbase;
	gear->mask = data->mask;
	gear->hw.init = &init;

	ret = devm_clk_hw_रेजिस्टर(dev, &gear->hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस &gear->hw;
पूर्ण
