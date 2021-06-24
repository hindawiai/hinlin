<शैली गुरु>
/*
 * TI Divider Clock
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 *
 * Tero Kristo <t-kristo@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk/ti.h>
#समावेश "clock.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

अटल अचिन्हित पूर्णांक _get_table_भाग(स्थिर काष्ठा clk_भाग_प्रकारable *table,
				   अचिन्हित पूर्णांक val)
अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *clkt;

	क्रम (clkt = table; clkt->भाग; clkt++)
		अगर (clkt->val == val)
			वापस clkt->भाग;
	वापस 0;
पूर्ण

अटल व्योम _setup_mask(काष्ठा clk_omap_भागider *भागider)
अणु
	u16 mask;
	u32 max_val;
	स्थिर काष्ठा clk_भाग_प्रकारable *clkt;

	अगर (भागider->table) अणु
		max_val = 0;

		क्रम (clkt = भागider->table; clkt->भाग; clkt++)
			अगर (clkt->val > max_val)
				max_val = clkt->val;
	पूर्ण अन्यथा अणु
		max_val = भागider->max;

		अगर (!(भागider->flags & CLK_DIVIDER_ONE_BASED) &&
		    !(भागider->flags & CLK_DIVIDER_POWER_OF_TWO))
			max_val--;
	पूर्ण

	अगर (भागider->flags & CLK_DIVIDER_POWER_OF_TWO)
		mask = fls(max_val) - 1;
	अन्यथा
		mask = max_val;

	भागider->mask = (1 << fls(mask)) - 1;
पूर्ण

अटल अचिन्हित पूर्णांक _get_भाग(काष्ठा clk_omap_भागider *भागider, अचिन्हित पूर्णांक val)
अणु
	अगर (भागider->flags & CLK_DIVIDER_ONE_BASED)
		वापस val;
	अगर (भागider->flags & CLK_DIVIDER_POWER_OF_TWO)
		वापस 1 << val;
	अगर (भागider->table)
		वापस _get_table_भाग(भागider->table, val);
	वापस val + 1;
पूर्ण

अटल अचिन्हित पूर्णांक _get_table_val(स्थिर काष्ठा clk_भाग_प्रकारable *table,
				   अचिन्हित पूर्णांक भाग)
अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *clkt;

	क्रम (clkt = table; clkt->भाग; clkt++)
		अगर (clkt->भाग == भाग)
			वापस clkt->val;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक _get_val(काष्ठा clk_omap_भागider *भागider, u8 भाग)
अणु
	अगर (भागider->flags & CLK_DIVIDER_ONE_BASED)
		वापस भाग;
	अगर (भागider->flags & CLK_DIVIDER_POWER_OF_TWO)
		वापस __ffs(भाग);
	अगर (भागider->table)
		वापस  _get_table_val(भागider->table, भाग);
	वापस भाग - 1;
पूर्ण

अटल अचिन्हित दीर्घ ti_clk_भागider_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_omap_भागider *भागider = to_clk_omap_भागider(hw);
	अचिन्हित पूर्णांक भाग, val;

	val = ti_clk_ll_ops->clk_पढ़ोl(&भागider->reg) >> भागider->shअगरt;
	val &= भागider->mask;

	भाग = _get_भाग(भागider, val);
	अगर (!भाग) अणु
		WARN(!(भागider->flags & CLK_DIVIDER_ALLOW_ZERO),
		     "%s: Zero divisor and CLK_DIVIDER_ALLOW_ZERO not set\n",
		     clk_hw_get_name(hw));
		वापस parent_rate;
	पूर्ण

	वापस DIV_ROUND_UP(parent_rate, भाग);
पूर्ण

/*
 * The reverse of DIV_ROUND_UP: The maximum number which
 * भागided by m is r
 */
#घोषणा MULT_ROUND_UP(r, m) ((r) * (m) + (m) - 1)

अटल bool _is_valid_table_भाग(स्थिर काष्ठा clk_भाग_प्रकारable *table,
				अचिन्हित पूर्णांक भाग)
अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *clkt;

	क्रम (clkt = table; clkt->भाग; clkt++)
		अगर (clkt->भाग == भाग)
			वापस true;
	वापस false;
पूर्ण

अटल bool _is_valid_भाग(काष्ठा clk_omap_भागider *भागider, अचिन्हित पूर्णांक भाग)
अणु
	अगर (भागider->flags & CLK_DIVIDER_POWER_OF_TWO)
		वापस is_घातer_of_2(भाग);
	अगर (भागider->table)
		वापस _is_valid_table_भाग(भागider->table, भाग);
	वापस true;
पूर्ण

अटल पूर्णांक _भाग_round_up(स्थिर काष्ठा clk_भाग_प्रकारable *table,
			 अचिन्हित दीर्घ parent_rate, अचिन्हित दीर्घ rate)
अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *clkt;
	पूर्णांक up = पूर्णांक_उच्च;
	पूर्णांक भाग = DIV_ROUND_UP_ULL((u64)parent_rate, rate);

	क्रम (clkt = table; clkt->भाग; clkt++) अणु
		अगर (clkt->भाग == भाग)
			वापस clkt->भाग;
		अन्यथा अगर (clkt->भाग < भाग)
			जारी;

		अगर ((clkt->भाग - भाग) < (up - भाग))
			up = clkt->भाग;
	पूर्ण

	वापस up;
पूर्ण

अटल पूर्णांक _भाग_round(स्थिर काष्ठा clk_भाग_प्रकारable *table,
		      अचिन्हित दीर्घ parent_rate, अचिन्हित दीर्घ rate)
अणु
	अगर (!table)
		वापस DIV_ROUND_UP(parent_rate, rate);

	वापस _भाग_round_up(table, parent_rate, rate);
पूर्ण

अटल पूर्णांक ti_clk_भागider_bestभाग(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *best_parent_rate)
अणु
	काष्ठा clk_omap_भागider *भागider = to_clk_omap_भागider(hw);
	पूर्णांक i, bestभाग = 0;
	अचिन्हित दीर्घ parent_rate, best = 0, now, maxभाग;
	अचिन्हित दीर्घ parent_rate_saved = *best_parent_rate;

	अगर (!rate)
		rate = 1;

	maxभाग = भागider->max;

	अगर (!(clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)) अणु
		parent_rate = *best_parent_rate;
		bestभाग = _भाग_round(भागider->table, parent_rate, rate);
		bestभाग = bestभाग == 0 ? 1 : bestभाग;
		bestभाग = bestभाग > maxभाग ? maxभाग : bestभाग;
		वापस bestभाग;
	पूर्ण

	/*
	 * The maximum भागider we can use without overflowing
	 * अचिन्हित दीर्घ in rate * i below
	 */
	maxभाग = min(अच_दीर्घ_उच्च / rate, maxभाग);

	क्रम (i = 1; i <= maxभाग; i++) अणु
		अगर (!_is_valid_भाग(भागider, i))
			जारी;
		अगर (rate * i == parent_rate_saved) अणु
			/*
			 * It's the most ideal हाल अगर the requested rate can be
			 * भागided from parent घड़ी without needing to change
			 * parent rate, so वापस the भागider immediately.
			 */
			*best_parent_rate = parent_rate_saved;
			वापस i;
		पूर्ण
		parent_rate = clk_hw_round_rate(clk_hw_get_parent(hw),
				MULT_ROUND_UP(rate, i));
		now = DIV_ROUND_UP(parent_rate, i);
		अगर (now <= rate && now > best) अणु
			bestभाग = i;
			best = now;
			*best_parent_rate = parent_rate;
		पूर्ण
	पूर्ण

	अगर (!bestभाग) अणु
		bestभाग = भागider->max;
		*best_parent_rate =
			clk_hw_round_rate(clk_hw_get_parent(hw), 1);
	पूर्ण

	वापस bestभाग;
पूर्ण

अटल दीर्घ ti_clk_भागider_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ *prate)
अणु
	पूर्णांक भाग;
	भाग = ti_clk_भागider_bestभाग(hw, rate, prate);

	वापस DIV_ROUND_UP(*prate, भाग);
पूर्ण

अटल पूर्णांक ti_clk_भागider_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_omap_भागider *भागider;
	अचिन्हित पूर्णांक भाग, value;
	u32 val;

	अगर (!hw || !rate)
		वापस -EINVAL;

	भागider = to_clk_omap_भागider(hw);

	भाग = DIV_ROUND_UP(parent_rate, rate);

	अगर (भाग > भागider->max)
		भाग = भागider->max;
	अगर (भाग < भागider->min)
		भाग = भागider->min;

	value = _get_val(भागider, भाग);

	val = ti_clk_ll_ops->clk_पढ़ोl(&भागider->reg);
	val &= ~(भागider->mask << भागider->shअगरt);
	val |= value << भागider->shअगरt;
	ti_clk_ll_ops->clk_ग_लिखोl(val, &भागider->reg);

	ti_clk_latch(&भागider->reg, भागider->latch);

	वापस 0;
पूर्ण

/**
 * clk_भागider_save_context - Save the भागider value
 * @hw: poपूर्णांकer  काष्ठा clk_hw
 *
 * Save the भागider value
 */
अटल पूर्णांक clk_भागider_save_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_omap_भागider *भागider = to_clk_omap_भागider(hw);
	u32 val;

	val = ti_clk_ll_ops->clk_पढ़ोl(&भागider->reg) >> भागider->shअगरt;
	भागider->context = val & भागider->mask;

	वापस 0;
पूर्ण

/**
 * clk_भागider_restore_context - restore the saved the भागider value
 * @hw: poपूर्णांकer  काष्ठा clk_hw
 *
 * Restore the saved the भागider value
 */
अटल व्योम clk_भागider_restore_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_omap_भागider *भागider = to_clk_omap_भागider(hw);
	u32 val;

	val = ti_clk_ll_ops->clk_पढ़ोl(&भागider->reg);
	val &= ~(भागider->mask << भागider->shअगरt);
	val |= भागider->context << भागider->shअगरt;
	ti_clk_ll_ops->clk_ग_लिखोl(val, &भागider->reg);
पूर्ण

स्थिर काष्ठा clk_ops ti_clk_भागider_ops = अणु
	.recalc_rate = ti_clk_भागider_recalc_rate,
	.round_rate = ti_clk_भागider_round_rate,
	.set_rate = ti_clk_भागider_set_rate,
	.save_context = clk_भागider_save_context,
	.restore_context = clk_भागider_restore_context,
पूर्ण;

अटल काष्ठा clk *_रेजिस्टर_भागider(काष्ठा device_node *node,
				     u32 flags,
				     काष्ठा clk_omap_भागider *भाग)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *parent_name;

	parent_name = of_clk_get_parent_name(node, 0);

	init.name = node->name;
	init.ops = &ti_clk_भागider_ops;
	init.flags = flags;
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);

	भाग->hw.init = &init;

	/* रेजिस्टर the घड़ी */
	clk = ti_clk_रेजिस्टर(शून्य, &भाग->hw, node->name);

	अगर (IS_ERR(clk))
		kमुक्त(भाग);

	वापस clk;
पूर्ण

पूर्णांक ti_clk_parse_भागider_data(पूर्णांक *भाग_प्रकारable, पूर्णांक num_भागiders, पूर्णांक max_भाग,
			      u8 flags, काष्ठा clk_omap_भागider *भागider)
अणु
	पूर्णांक valid_भाग = 0;
	पूर्णांक i;
	काष्ठा clk_भाग_प्रकारable *पंचांगp;
	u16 min_भाग = 0;

	अगर (!भाग_प्रकारable) अणु
		भागider->min = 1;
		भागider->max = max_भाग;
		_setup_mask(भागider);
		वापस 0;
	पूर्ण

	i = 0;

	जबतक (!num_भागiders || i < num_भागiders) अणु
		अगर (भाग_प्रकारable[i] == -1)
			अवरोध;
		अगर (भाग_प्रकारable[i])
			valid_भाग++;
		i++;
	पूर्ण

	num_भागiders = i;

	पंचांगp = kसुस्मृति(valid_भाग + 1, माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	valid_भाग = 0;

	क्रम (i = 0; i < num_भागiders; i++)
		अगर (भाग_प्रकारable[i] > 0) अणु
			पंचांगp[valid_भाग].भाग = भाग_प्रकारable[i];
			पंचांगp[valid_भाग].val = i;
			valid_भाग++;
			अगर (भाग_प्रकारable[i] > max_भाग)
				max_भाग = भाग_प्रकारable[i];
			अगर (!min_भाग || भाग_प्रकारable[i] < min_भाग)
				min_भाग = भाग_प्रकारable[i];
		पूर्ण

	भागider->min = min_भाग;
	भागider->max = max_भाग;
	भागider->table = पंचांगp;
	_setup_mask(भागider);

	वापस 0;
पूर्ण

अटल पूर्णांक __init ti_clk_get_भाग_प्रकारable(काष्ठा device_node *node,
				       काष्ठा clk_omap_भागider *भाग)
अणु
	काष्ठा clk_भाग_प्रकारable *table;
	स्थिर __be32 *भागspec;
	u32 val;
	u32 num_भाग;
	u32 valid_भाग;
	पूर्णांक i;

	भागspec = of_get_property(node, "ti,dividers", &num_भाग);

	अगर (!भागspec)
		वापस 0;

	num_भाग /= 4;

	valid_भाग = 0;

	/* Determine required size क्रम भागider table */
	क्रम (i = 0; i < num_भाग; i++) अणु
		of_property_पढ़ो_u32_index(node, "ti,dividers", i, &val);
		अगर (val)
			valid_भाग++;
	पूर्ण

	अगर (!valid_भाग) अणु
		pr_err("no valid dividers for %pOFn table\n", node);
		वापस -EINVAL;
	पूर्ण

	table = kसुस्मृति(valid_भाग + 1, माप(*table), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	valid_भाग = 0;

	क्रम (i = 0; i < num_भाग; i++) अणु
		of_property_पढ़ो_u32_index(node, "ti,dividers", i, &val);
		अगर (val) अणु
			table[valid_भाग].भाग = val;
			table[valid_भाग].val = i;
			valid_भाग++;
		पूर्ण
	पूर्ण

	भाग->table = table;

	वापस 0;
पूर्ण

अटल पूर्णांक _populate_भागider_min_max(काष्ठा device_node *node,
				     काष्ठा clk_omap_भागider *भागider)
अणु
	u32 min_भाग = 0;
	u32 max_भाग = 0;
	u32 val;
	स्थिर काष्ठा clk_भाग_प्रकारable *clkt;

	अगर (!भागider->table) अणु
		/* Clk भागider table not provided, determine min/max भागs */
		अगर (of_property_पढ़ो_u32(node, "ti,min-div", &min_भाग))
			min_भाग = 1;

		अगर (of_property_पढ़ो_u32(node, "ti,max-div", &max_भाग)) अणु
			pr_err("no max-div for %pOFn!\n", node);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु

		क्रम (clkt = भागider->table; clkt->भाग; clkt++) अणु
			val = clkt->भाग;
			अगर (val > max_भाग)
				max_भाग = val;
			अगर (!min_भाग || val < min_भाग)
				min_भाग = val;
		पूर्ण
	पूर्ण

	भागider->min = min_भाग;
	भागider->max = max_भाग;
	_setup_mask(भागider);

	वापस 0;
पूर्ण

अटल पूर्णांक __init ti_clk_भागider_populate(काष्ठा device_node *node,
					  काष्ठा clk_omap_भागider *भाग,
					  u32 *flags)
अणु
	u32 val;
	पूर्णांक ret;

	ret = ti_clk_get_reg_addr(node, 0, &भाग->reg);
	अगर (ret)
		वापस ret;

	अगर (!of_property_पढ़ो_u32(node, "ti,bit-shift", &val))
		भाग->shअगरt = val;
	अन्यथा
		भाग->shअगरt = 0;

	अगर (!of_property_पढ़ो_u32(node, "ti,latch-bit", &val))
		भाग->latch = val;
	अन्यथा
		भाग->latch = -EINVAL;

	*flags = 0;
	भाग->flags = 0;

	अगर (of_property_पढ़ो_bool(node, "ti,index-starts-at-one"))
		भाग->flags |= CLK_DIVIDER_ONE_BASED;

	अगर (of_property_पढ़ो_bool(node, "ti,index-power-of-two"))
		भाग->flags |= CLK_DIVIDER_POWER_OF_TWO;

	अगर (of_property_पढ़ो_bool(node, "ti,set-rate-parent"))
		*flags |= CLK_SET_RATE_PARENT;

	ret = ti_clk_get_भाग_प्रकारable(node, भाग);
	अगर (ret)
		वापस ret;

	वापस _populate_भागider_min_max(node, भाग);
पूर्ण

/**
 * of_ti_भागider_clk_setup - Setup function क्रम simple भाग rate घड़ी
 * @node: device node क्रम this घड़ी
 *
 * Sets up a basic भागider घड़ी.
 */
अटल व्योम __init of_ti_भागider_clk_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk *clk;
	u32 flags = 0;
	काष्ठा clk_omap_भागider *भाग;

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस;

	अगर (ti_clk_भागider_populate(node, भाग, &flags))
		जाओ cleanup;

	clk = _रेजिस्टर_भागider(node, flags, भाग);
	अगर (!IS_ERR(clk)) अणु
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
		of_ti_clk_स्वतःidle_setup(node);
		वापस;
	पूर्ण

cleanup:
	kमुक्त(भाग->table);
	kमुक्त(भाग);
पूर्ण
CLK_OF_DECLARE(भागider_clk, "ti,divider-clock", of_ti_भागider_clk_setup);

अटल व्योम __init of_ti_composite_भागider_clk_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk_omap_भागider *भाग;
	u32 पंचांगp;

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस;

	अगर (ti_clk_भागider_populate(node, भाग, &पंचांगp))
		जाओ cleanup;

	अगर (!ti_clk_add_component(node, &भाग->hw, CLK_COMPONENT_TYPE_DIVIDER))
		वापस;

cleanup:
	kमुक्त(भाग->table);
	kमुक्त(भाग);
पूर्ण
CLK_OF_DECLARE(ti_composite_भागider_clk, "ti,composite-divider-clock",
	       of_ti_composite_भागider_clk_setup);
