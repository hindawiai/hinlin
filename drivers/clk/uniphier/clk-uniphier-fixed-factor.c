<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Socionext Inc.
 *   Author: Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>

#समावेश "clk-uniphier.h"

काष्ठा clk_hw *uniphier_clk_रेजिस्टर_fixed_factor(काष्ठा device *dev,
						  स्थिर अक्षर *name,
			स्थिर काष्ठा uniphier_clk_fixed_factor_data *data)
अणु
	काष्ठा clk_fixed_factor *fix;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	fix = devm_kzalloc(dev, माप(*fix), GFP_KERNEL);
	अगर (!fix)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_fixed_factor_ops;
	init.flags = data->parent_name ? CLK_SET_RATE_PARENT : 0;
	init.parent_names = data->parent_name ? &data->parent_name : शून्य;
	init.num_parents = data->parent_name ? 1 : 0;

	fix->mult = data->mult;
	fix->भाग = data->भाग;
	fix->hw.init = &init;

	ret = devm_clk_hw_रेजिस्टर(dev, &fix->hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस &fix->hw;
पूर्ण
