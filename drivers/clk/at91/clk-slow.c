<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/clk/at91/clk-slow.c
 *
 *  Copyright (C) 2013 Boris BREZILLON <b.brezillon@overkiz.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "pmc.h"

काष्ठा clk_sam9260_slow अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
पूर्ण;

#घोषणा to_clk_sam9260_slow(hw) container_of(hw, काष्ठा clk_sam9260_slow, hw)

अटल u8 clk_sam9260_slow_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sam9260_slow *slowck = to_clk_sam9260_slow(hw);
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(slowck->regmap, AT91_PMC_SR, &status);

	वापस status & AT91_PMC_OSCSEL ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops sam9260_slow_ops = अणु
	.get_parent = clk_sam9260_slow_get_parent,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_sam9260_slow(काष्ठा regmap *regmap,
			       स्थिर अक्षर *name,
			       स्थिर अक्षर **parent_names,
			       पूर्णांक num_parents)
अणु
	काष्ठा clk_sam9260_slow *slowck;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	अगर (!name)
		वापस ERR_PTR(-EINVAL);

	अगर (!parent_names || !num_parents)
		वापस ERR_PTR(-EINVAL);

	slowck = kzalloc(माप(*slowck), GFP_KERNEL);
	अगर (!slowck)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &sam9260_slow_ops;
	init.parent_names = parent_names;
	init.num_parents = num_parents;
	init.flags = 0;

	slowck->hw.init = &init;
	slowck->regmap = regmap;

	hw = &slowck->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &slowck->hw);
	अगर (ret) अणु
		kमुक्त(slowck);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
