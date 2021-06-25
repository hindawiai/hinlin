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

#घोषणा SMD_DIV_SHIFT		8
#घोषणा SMD_MAX_DIV		0xf

काष्ठा at91sam9x5_clk_smd अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
पूर्ण;

#घोषणा to_at91sam9x5_clk_smd(hw) \
	container_of(hw, काष्ठा at91sam9x5_clk_smd, hw)

अटल अचिन्हित दीर्घ at91sam9x5_clk_smd_recalc_rate(काष्ठा clk_hw *hw,
						    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा at91sam9x5_clk_smd *smd = to_at91sam9x5_clk_smd(hw);
	अचिन्हित पूर्णांक smdr;
	u8 smdभाग;

	regmap_पढ़ो(smd->regmap, AT91_PMC_SMD, &smdr);
	smdभाग = (smdr & AT91_PMC_SMD_DIV) >> SMD_DIV_SHIFT;

	वापस parent_rate / (smdभाग + 1);
पूर्ण

अटल दीर्घ at91sam9x5_clk_smd_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					  अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित दीर्घ भाग;
	अचिन्हित दीर्घ bestrate;
	अचिन्हित दीर्घ पंचांगp;

	अगर (rate >= *parent_rate)
		वापस *parent_rate;

	भाग = *parent_rate / rate;
	अगर (भाग > SMD_MAX_DIV)
		वापस *parent_rate / (SMD_MAX_DIV + 1);

	bestrate = *parent_rate / भाग;
	पंचांगp = *parent_rate / (भाग + 1);
	अगर (bestrate - rate > rate - पंचांगp)
		bestrate = पंचांगp;

	वापस bestrate;
पूर्ण

अटल पूर्णांक at91sam9x5_clk_smd_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा at91sam9x5_clk_smd *smd = to_at91sam9x5_clk_smd(hw);

	अगर (index > 1)
		वापस -EINVAL;

	regmap_update_bits(smd->regmap, AT91_PMC_SMD, AT91_PMC_SMDS,
			   index ? AT91_PMC_SMDS : 0);

	वापस 0;
पूर्ण

अटल u8 at91sam9x5_clk_smd_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा at91sam9x5_clk_smd *smd = to_at91sam9x5_clk_smd(hw);
	अचिन्हित पूर्णांक smdr;

	regmap_पढ़ो(smd->regmap, AT91_PMC_SMD, &smdr);

	वापस smdr & AT91_PMC_SMDS;
पूर्ण

अटल पूर्णांक at91sam9x5_clk_smd_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा at91sam9x5_clk_smd *smd = to_at91sam9x5_clk_smd(hw);
	अचिन्हित दीर्घ भाग = parent_rate / rate;

	अगर (parent_rate % rate || भाग < 1 || भाग > (SMD_MAX_DIV + 1))
		वापस -EINVAL;

	regmap_update_bits(smd->regmap, AT91_PMC_SMD, AT91_PMC_SMD_DIV,
			   (भाग - 1) << SMD_DIV_SHIFT);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops at91sam9x5_smd_ops = अणु
	.recalc_rate = at91sam9x5_clk_smd_recalc_rate,
	.round_rate = at91sam9x5_clk_smd_round_rate,
	.get_parent = at91sam9x5_clk_smd_get_parent,
	.set_parent = at91sam9x5_clk_smd_set_parent,
	.set_rate = at91sam9x5_clk_smd_set_rate,
पूर्ण;

काष्ठा clk_hw * __init
at91sam9x5_clk_रेजिस्टर_smd(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			    स्थिर अक्षर **parent_names, u8 num_parents)
अणु
	काष्ठा at91sam9x5_clk_smd *smd;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	smd = kzalloc(माप(*smd), GFP_KERNEL);
	अगर (!smd)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &at91sam9x5_smd_ops;
	init.parent_names = parent_names;
	init.num_parents = num_parents;
	init.flags = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE;

	smd->hw.init = &init;
	smd->regmap = regmap;

	hw = &smd->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &smd->hw);
	अगर (ret) अणु
		kमुक्त(smd);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
