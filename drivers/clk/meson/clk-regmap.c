<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#समावेश <linux/module.h>
#समावेश "clk-regmap.h"

अटल पूर्णांक clk_regmap_gate_endisable(काष्ठा clk_hw *hw, पूर्णांक enable)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा clk_regmap_gate_data *gate = clk_get_regmap_gate_data(clk);
	पूर्णांक set = gate->flags & CLK_GATE_SET_TO_DISABLE ? 1 : 0;

	set ^= enable;

	वापस regmap_update_bits(clk->map, gate->offset, BIT(gate->bit_idx),
				  set ? BIT(gate->bit_idx) : 0);
पूर्ण

अटल पूर्णांक clk_regmap_gate_enable(काष्ठा clk_hw *hw)
अणु
	वापस clk_regmap_gate_endisable(hw, 1);
पूर्ण

अटल व्योम clk_regmap_gate_disable(काष्ठा clk_hw *hw)
अणु
	clk_regmap_gate_endisable(hw, 0);
पूर्ण

अटल पूर्णांक clk_regmap_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा clk_regmap_gate_data *gate = clk_get_regmap_gate_data(clk);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(clk->map, gate->offset, &val);
	अगर (gate->flags & CLK_GATE_SET_TO_DISABLE)
		val ^= BIT(gate->bit_idx);

	val &= BIT(gate->bit_idx);

	वापस val ? 1 : 0;
पूर्ण

स्थिर काष्ठा clk_ops clk_regmap_gate_ops = अणु
	.enable = clk_regmap_gate_enable,
	.disable = clk_regmap_gate_disable,
	.is_enabled = clk_regmap_gate_is_enabled,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_regmap_gate_ops);

स्थिर काष्ठा clk_ops clk_regmap_gate_ro_ops = अणु
	.is_enabled = clk_regmap_gate_is_enabled,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_regmap_gate_ro_ops);

अटल अचिन्हित दीर्घ clk_regmap_भाग_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा clk_regmap_भाग_data *भाग = clk_get_regmap_भाग_data(clk);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(clk->map, भाग->offset, &val);
	अगर (ret)
		/* Gives a hपूर्णांक that something is wrong */
		वापस 0;

	val >>= भाग->shअगरt;
	val &= clk_भाग_mask(भाग->width);
	वापस भागider_recalc_rate(hw, prate, val, भाग->table, भाग->flags,
				   भाग->width);
पूर्ण

अटल दीर्घ clk_regmap_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा clk_regmap_भाग_data *भाग = clk_get_regmap_भाग_data(clk);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* अगर पढ़ो only, just वापस current value */
	अगर (भाग->flags & CLK_DIVIDER_READ_ONLY) अणु
		ret = regmap_पढ़ो(clk->map, भाग->offset, &val);
		अगर (ret)
			/* Gives a hपूर्णांक that something is wrong */
			वापस 0;

		val >>= भाग->shअगरt;
		val &= clk_भाग_mask(भाग->width);

		वापस भागider_ro_round_rate(hw, rate, prate, भाग->table,
					     भाग->width, भाग->flags, val);
	पूर्ण

	वापस भागider_round_rate(hw, rate, prate, भाग->table, भाग->width,
				  भाग->flags);
पूर्ण

अटल पूर्णांक clk_regmap_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा clk_regmap_भाग_data *भाग = clk_get_regmap_भाग_data(clk);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = भागider_get_val(rate, parent_rate, भाग->table, भाग->width,
			      भाग->flags);
	अगर (ret < 0)
		वापस ret;

	val = (अचिन्हित पूर्णांक)ret << भाग->shअगरt;
	वापस regmap_update_bits(clk->map, भाग->offset,
				  clk_भाग_mask(भाग->width) << भाग->shअगरt, val);
पूर्ण;

/* Would prefer clk_regmap_भाग_ro_ops but clashes with qcom */

स्थिर काष्ठा clk_ops clk_regmap_भागider_ops = अणु
	.recalc_rate = clk_regmap_भाग_recalc_rate,
	.round_rate = clk_regmap_भाग_round_rate,
	.set_rate = clk_regmap_भाग_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_regmap_भागider_ops);

स्थिर काष्ठा clk_ops clk_regmap_भागider_ro_ops = अणु
	.recalc_rate = clk_regmap_भाग_recalc_rate,
	.round_rate = clk_regmap_भाग_round_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_regmap_भागider_ro_ops);

अटल u8 clk_regmap_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा clk_regmap_mux_data *mux = clk_get_regmap_mux_data(clk);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(clk->map, mux->offset, &val);
	अगर (ret)
		वापस ret;

	val >>= mux->shअगरt;
	val &= mux->mask;
	वापस clk_mux_val_to_index(hw, mux->table, mux->flags, val);
पूर्ण

अटल पूर्णांक clk_regmap_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा clk_regmap_mux_data *mux = clk_get_regmap_mux_data(clk);
	अचिन्हित पूर्णांक val = clk_mux_index_to_val(mux->table, mux->flags, index);

	वापस regmap_update_bits(clk->map, mux->offset,
				  mux->mask << mux->shअगरt,
				  val << mux->shअगरt);
पूर्ण

अटल पूर्णांक clk_regmap_mux_determine_rate(काष्ठा clk_hw *hw,
					 काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा clk_regmap_mux_data *mux = clk_get_regmap_mux_data(clk);

	वापस clk_mux_determine_rate_flags(hw, req, mux->flags);
पूर्ण

स्थिर काष्ठा clk_ops clk_regmap_mux_ops = अणु
	.get_parent = clk_regmap_mux_get_parent,
	.set_parent = clk_regmap_mux_set_parent,
	.determine_rate = clk_regmap_mux_determine_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_regmap_mux_ops);

स्थिर काष्ठा clk_ops clk_regmap_mux_ro_ops = अणु
	.get_parent = clk_regmap_mux_get_parent,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_regmap_mux_ro_ops);

MODULE_DESCRIPTION("Amlogic regmap backed clock driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
