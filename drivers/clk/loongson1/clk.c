<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2012-2016 Zhang, Keguang <keguang.zhang@gmail.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>

#समावेश "clk.h"

काष्ठा clk_hw *__init clk_hw_रेजिस्टर_pll(काष्ठा device *dev,
					  स्थिर अक्षर *name,
					  स्थिर अक्षर *parent_name,
					  स्थिर काष्ठा clk_ops *ops,
					  अचिन्हित दीर्घ flags)
अणु
	पूर्णांक ret;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;

	/* allocate the भागider */
	hw = kzalloc(माप(*hw), GFP_KERNEL);
	अगर (!hw)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = ops;
	init.flags = flags;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;
	hw->init = &init;

	/* रेजिस्टर the घड़ी */
	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret) अणु
		kमुक्त(hw);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
