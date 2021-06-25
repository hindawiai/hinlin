<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * clk-h32mx.c
 *
 *  Copyright (C) 2014 Aपंचांगel
 *
 * Alexandre Belloni <alexandre.belloni@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#समावेश "pmc.h"

#घोषणा H32MX_MAX_FREQ	90000000

काष्ठा clk_sama5d4_h32mx अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
पूर्ण;

#घोषणा to_clk_sama5d4_h32mx(hw) container_of(hw, काष्ठा clk_sama5d4_h32mx, hw)

अटल अचिन्हित दीर्घ clk_sama5d4_h32mx_recalc_rate(काष्ठा clk_hw *hw,
						 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_sama5d4_h32mx *h32mxclk = to_clk_sama5d4_h32mx(hw);
	अचिन्हित पूर्णांक mckr;

	regmap_पढ़ो(h32mxclk->regmap, AT91_PMC_MCKR, &mckr);
	अगर (mckr & AT91_PMC_H32MXDIV)
		वापस parent_rate / 2;

	अगर (parent_rate > H32MX_MAX_FREQ)
		pr_warn("H32MX clock is too fast\n");
	वापस parent_rate;
पूर्ण

अटल दीर्घ clk_sama5d4_h32mx_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
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

अटल पूर्णांक clk_sama5d4_h32mx_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_sama5d4_h32mx *h32mxclk = to_clk_sama5d4_h32mx(hw);
	u32 mckr = 0;

	अगर (parent_rate != rate && (parent_rate / 2) != rate)
		वापस -EINVAL;

	अगर ((parent_rate / 2) == rate)
		mckr = AT91_PMC_H32MXDIV;

	regmap_update_bits(h32mxclk->regmap, AT91_PMC_MCKR,
			   AT91_PMC_H32MXDIV, mckr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops h32mx_ops = अणु
	.recalc_rate = clk_sama5d4_h32mx_recalc_rate,
	.round_rate = clk_sama5d4_h32mx_round_rate,
	.set_rate = clk_sama5d4_h32mx_set_rate,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_h32mx(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			स्थिर अक्षर *parent_name)
अणु
	काष्ठा clk_sama5d4_h32mx *h32mxclk;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	h32mxclk = kzalloc(माप(*h32mxclk), GFP_KERNEL);
	अगर (!h32mxclk)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &h32mx_ops;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;
	init.flags = CLK_SET_RATE_GATE;

	h32mxclk->hw.init = &init;
	h32mxclk->regmap = regmap;

	ret = clk_hw_रेजिस्टर(शून्य, &h32mxclk->hw);
	अगर (ret) अणु
		kमुक्त(h32mxclk);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस &h32mxclk->hw;
पूर्ण
