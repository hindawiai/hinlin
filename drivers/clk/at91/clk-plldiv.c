<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2013 Boris BREZILLON <b.brezillon@overkiz.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "pmc.h"

#घोषणा to_clk_plद_भाग(hw) container_of(hw, काष्ठा clk_plद_भाग, hw)

काष्ठा clk_plद_भाग अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
पूर्ण;

अटल अचिन्हित दीर्घ clk_plद_भाग_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_plद_भाग *plद_भाग = to_clk_plद_भाग(hw);
	अचिन्हित पूर्णांक mckr;

	regmap_पढ़ो(plद_भाग->regmap, AT91_PMC_MCKR, &mckr);

	अगर (mckr & AT91_PMC_PLLADIV2)
		वापस parent_rate / 2;

	वापस parent_rate;
पूर्ण

अटल दीर्घ clk_plद_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित दीर्घ भाग;

	अगर (rate > *parent_rate)
		वापस *parent_rate;
	भाग = *parent_rate / 2;
	अगर (rate < भाग)
		वापस भाग;

	अगर (rate - भाग < *parent_rate - rate)
		वापस भाग;

	वापस *parent_rate;
पूर्ण

अटल पूर्णांक clk_plद_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_plद_भाग *plद_भाग = to_clk_plद_भाग(hw);

	अगर ((parent_rate != rate) && (parent_rate / 2 != rate))
		वापस -EINVAL;

	regmap_update_bits(plद_भाग->regmap, AT91_PMC_MCKR, AT91_PMC_PLLADIV2,
			   parent_rate != rate ? AT91_PMC_PLLADIV2 : 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops plद_भाग_ops = अणु
	.recalc_rate = clk_plद_भाग_recalc_rate,
	.round_rate = clk_plद_भाग_round_rate,
	.set_rate = clk_plद_भाग_set_rate,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_plद_भाग(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			 स्थिर अक्षर *parent_name)
अणु
	काष्ठा clk_plद_भाग *plद_भाग;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	plद_भाग = kzalloc(माप(*plद_भाग), GFP_KERNEL);
	अगर (!plद_भाग)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &plद_भाग_ops;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;
	init.flags = CLK_SET_RATE_GATE;

	plद_भाग->hw.init = &init;
	plद_भाग->regmap = regmap;

	hw = &plद_भाग->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &plद_भाग->hw);
	अगर (ret) अणु
		kमुक्त(plद_भाग);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
