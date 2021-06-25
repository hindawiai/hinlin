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

#घोषणा PROG_ID_MAX		7

#घोषणा PROG_STATUS_MASK(id)	(1 << ((id) + 8))
#घोषणा PROG_PRES(layout, pckr)	((pckr >> layout->pres_shअगरt) & layout->pres_mask)
#घोषणा PROG_MAX_RM9200_CSS	3

काष्ठा clk_programmable अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u32 *mux_table;
	u8 id;
	स्थिर काष्ठा clk_programmable_layout *layout;
पूर्ण;

#घोषणा to_clk_programmable(hw) container_of(hw, काष्ठा clk_programmable, hw)

अटल अचिन्हित दीर्घ clk_programmable_recalc_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_programmable *prog = to_clk_programmable(hw);
	स्थिर काष्ठा clk_programmable_layout *layout = prog->layout;
	अचिन्हित पूर्णांक pckr;
	अचिन्हित दीर्घ rate;

	regmap_पढ़ो(prog->regmap, AT91_PMC_PCKR(prog->id), &pckr);

	अगर (layout->is_pres_direct)
		rate = parent_rate / (PROG_PRES(layout, pckr) + 1);
	अन्यथा
		rate = parent_rate >> PROG_PRES(layout, pckr);

	वापस rate;
पूर्ण

अटल पूर्णांक clk_programmable_determine_rate(काष्ठा clk_hw *hw,
					   काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_programmable *prog = to_clk_programmable(hw);
	स्थिर काष्ठा clk_programmable_layout *layout = prog->layout;
	काष्ठा clk_hw *parent;
	दीर्घ best_rate = -EINVAL;
	अचिन्हित दीर्घ parent_rate;
	अचिन्हित दीर्घ पंचांगp_rate = 0;
	पूर्णांक shअगरt;
	पूर्णांक i;

	क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++) अणु
		parent = clk_hw_get_parent_by_index(hw, i);
		अगर (!parent)
			जारी;

		parent_rate = clk_hw_get_rate(parent);
		अगर (layout->is_pres_direct) अणु
			क्रम (shअगरt = 0; shअगरt <= layout->pres_mask; shअगरt++) अणु
				पंचांगp_rate = parent_rate / (shअगरt + 1);
				अगर (पंचांगp_rate <= req->rate)
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (shअगरt = 0; shअगरt < layout->pres_mask; shअगरt++) अणु
				पंचांगp_rate = parent_rate >> shअगरt;
				अगर (पंचांगp_rate <= req->rate)
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (पंचांगp_rate > req->rate)
			जारी;

		अगर (best_rate < 0 ||
		    (req->rate - पंचांगp_rate) < (req->rate - best_rate)) अणु
			best_rate = पंचांगp_rate;
			req->best_parent_rate = parent_rate;
			req->best_parent_hw = parent;
		पूर्ण

		अगर (!best_rate)
			अवरोध;
	पूर्ण

	अगर (best_rate < 0)
		वापस best_rate;

	req->rate = best_rate;
	वापस 0;
पूर्ण

अटल पूर्णांक clk_programmable_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_programmable *prog = to_clk_programmable(hw);
	स्थिर काष्ठा clk_programmable_layout *layout = prog->layout;
	अचिन्हित पूर्णांक mask = layout->css_mask;
	अचिन्हित पूर्णांक pckr = index;

	अगर (layout->have_slck_mck)
		mask |= AT91_PMC_CSSMCK_MCK;

	अगर (prog->mux_table)
		pckr = clk_mux_index_to_val(prog->mux_table, 0, index);

	अगर (index > layout->css_mask) अणु
		अगर (index > PROG_MAX_RM9200_CSS && !layout->have_slck_mck)
			वापस -EINVAL;

		pckr |= AT91_PMC_CSSMCK_MCK;
	पूर्ण

	regmap_update_bits(prog->regmap, AT91_PMC_PCKR(prog->id), mask, pckr);

	वापस 0;
पूर्ण

अटल u8 clk_programmable_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_programmable *prog = to_clk_programmable(hw);
	स्थिर काष्ठा clk_programmable_layout *layout = prog->layout;
	अचिन्हित पूर्णांक pckr;
	u8 ret;

	regmap_पढ़ो(prog->regmap, AT91_PMC_PCKR(prog->id), &pckr);

	ret = pckr & layout->css_mask;

	अगर (layout->have_slck_mck && (pckr & AT91_PMC_CSSMCK_MCK) && !ret)
		ret = PROG_MAX_RM9200_CSS + 1;

	अगर (prog->mux_table)
		ret = clk_mux_val_to_index(&prog->hw, prog->mux_table, 0, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक clk_programmable_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_programmable *prog = to_clk_programmable(hw);
	स्थिर काष्ठा clk_programmable_layout *layout = prog->layout;
	अचिन्हित दीर्घ भाग = parent_rate / rate;
	पूर्णांक shअगरt = 0;

	अगर (!भाग)
		वापस -EINVAL;

	अगर (layout->is_pres_direct) अणु
		shअगरt = भाग - 1;

		अगर (shअगरt > layout->pres_mask)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		shअगरt = fls(भाग) - 1;

		अगर (भाग != (1 << shअगरt))
			वापस -EINVAL;

		अगर (shअगरt >= layout->pres_mask)
			वापस -EINVAL;
	पूर्ण

	regmap_update_bits(prog->regmap, AT91_PMC_PCKR(prog->id),
			   layout->pres_mask << layout->pres_shअगरt,
			   shअगरt << layout->pres_shअगरt);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops programmable_ops = अणु
	.recalc_rate = clk_programmable_recalc_rate,
	.determine_rate = clk_programmable_determine_rate,
	.get_parent = clk_programmable_get_parent,
	.set_parent = clk_programmable_set_parent,
	.set_rate = clk_programmable_set_rate,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_programmable(काष्ठा regmap *regmap,
			       स्थिर अक्षर *name, स्थिर अक्षर **parent_names,
			       u8 num_parents, u8 id,
			       स्थिर काष्ठा clk_programmable_layout *layout,
			       u32 *mux_table)
अणु
	काष्ठा clk_programmable *prog;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	अगर (id > PROG_ID_MAX)
		वापस ERR_PTR(-EINVAL);

	prog = kzalloc(माप(*prog), GFP_KERNEL);
	अगर (!prog)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &programmable_ops;
	init.parent_names = parent_names;
	init.num_parents = num_parents;
	init.flags = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE;

	prog->id = id;
	prog->layout = layout;
	prog->hw.init = &init;
	prog->regmap = regmap;
	prog->mux_table = mux_table;

	hw = &prog->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &prog->hw);
	अगर (ret) अणु
		kमुक्त(prog);
		hw = ERR_PTR(ret);
	पूर्ण अन्यथा अणु
		pmc_रेजिस्टर_pck(id);
	पूर्ण

	वापस hw;
पूर्ण

स्थिर काष्ठा clk_programmable_layout at91rm9200_programmable_layout = अणु
	.pres_mask = 0x7,
	.pres_shअगरt = 2,
	.css_mask = 0x3,
	.have_slck_mck = 0,
	.is_pres_direct = 0,
पूर्ण;

स्थिर काष्ठा clk_programmable_layout at91sam9g45_programmable_layout = अणु
	.pres_mask = 0x7,
	.pres_shअगरt = 2,
	.css_mask = 0x3,
	.have_slck_mck = 1,
	.is_pres_direct = 0,
पूर्ण;

स्थिर काष्ठा clk_programmable_layout at91sam9x5_programmable_layout = अणु
	.pres_mask = 0x7,
	.pres_shअगरt = 4,
	.css_mask = 0x7,
	.have_slck_mck = 0,
	.is_pres_direct = 0,
पूर्ण;
