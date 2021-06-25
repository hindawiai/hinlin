<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Socionext Inc.
 *   Author: Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>

#समावेश "clk-uniphier.h"

काष्ठा clk_hw *uniphier_clk_रेजिस्टर_fixed_rate(काष्ठा device *dev,
						स्थिर अक्षर *name,
				स्थिर काष्ठा uniphier_clk_fixed_rate_data *data)
अणु
	काष्ठा clk_fixed_rate *fixed;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	/* allocate fixed-rate घड़ी */
	fixed = devm_kzalloc(dev, माप(*fixed), GFP_KERNEL);
	अगर (!fixed)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_fixed_rate_ops;
	init.parent_names = शून्य;
	init.num_parents = 0;

	fixed->fixed_rate = data->fixed_rate;
	fixed->hw.init = &init;

	ret = devm_clk_hw_रेजिस्टर(dev, &fixed->hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस &fixed->hw;
पूर्ण
