<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/regmap.h>
#समावेश <linux/export.h>

#समावेश "clk-regmap-mux.h"

अटल अंतरभूत काष्ठा clk_regmap_mux *to_clk_regmap_mux(काष्ठा clk_hw *hw)
अणु
	वापस container_of(to_clk_regmap(hw), काष्ठा clk_regmap_mux, clkr);
पूर्ण

अटल u8 mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap_mux *mux = to_clk_regmap_mux(hw);
	काष्ठा clk_regmap *clkr = to_clk_regmap(hw);
	अचिन्हित पूर्णांक mask = GENMASK(mux->width - 1, 0);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(clkr->regmap, mux->reg, &val);

	val >>= mux->shअगरt;
	val &= mask;

	अगर (mux->parent_map)
		वापस qcom_find_src_index(hw, mux->parent_map, val);

	वापस val;
पूर्ण

अटल पूर्णांक mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_regmap_mux *mux = to_clk_regmap_mux(hw);
	काष्ठा clk_regmap *clkr = to_clk_regmap(hw);
	अचिन्हित पूर्णांक mask = GENMASK(mux->width + mux->shअगरt - 1, mux->shअगरt);
	अचिन्हित पूर्णांक val;

	अगर (mux->parent_map)
		index = mux->parent_map[index].cfg;

	val = index;
	val <<= mux->shअगरt;

	वापस regmap_update_bits(clkr->regmap, mux->reg, mask, val);
पूर्ण

स्थिर काष्ठा clk_ops clk_regmap_mux_बंदst_ops = अणु
	.get_parent = mux_get_parent,
	.set_parent = mux_set_parent,
	.determine_rate = __clk_mux_determine_rate_बंदst,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_regmap_mux_बंदst_ops);
