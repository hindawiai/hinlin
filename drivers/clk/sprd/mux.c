<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Spपढ़ोtrum multiplexer घड़ी driver
//
// Copyright (C) 2017 Spपढ़ोtrum, Inc.
// Author: Chunyan Zhang <chunyan.zhang@spपढ़ोtrum.com>

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>

#समावेश "mux.h"

u8 sprd_mux_helper_get_parent(स्थिर काष्ठा sprd_clk_common *common,
			      स्थिर काष्ठा sprd_mux_ssel *mux)
अणु
	अचिन्हित पूर्णांक reg;
	u8 parent;
	पूर्णांक num_parents;
	पूर्णांक i;

	regmap_पढ़ो(common->regmap, common->reg, &reg);
	parent = reg >> mux->shअगरt;
	parent &= (1 << mux->width) - 1;

	अगर (!mux->table)
		वापस parent;

	num_parents = clk_hw_get_num_parents(&common->hw);

	क्रम (i = 0; i < num_parents - 1; i++)
		अगर (parent >= mux->table[i] && parent < mux->table[i + 1])
			वापस i;

	वापस num_parents - 1;
पूर्ण
EXPORT_SYMBOL_GPL(sprd_mux_helper_get_parent);

अटल u8 sprd_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा sprd_mux *cm = hw_to_sprd_mux(hw);

	वापस sprd_mux_helper_get_parent(&cm->common, &cm->mux);
पूर्ण

पूर्णांक sprd_mux_helper_set_parent(स्थिर काष्ठा sprd_clk_common *common,
			       स्थिर काष्ठा sprd_mux_ssel *mux,
			       u8 index)
अणु
	अचिन्हित पूर्णांक reg;

	अगर (mux->table)
		index = mux->table[index];

	regmap_पढ़ो(common->regmap, common->reg, &reg);
	reg &= ~GENMASK(mux->width + mux->shअगरt - 1, mux->shअगरt);
	regmap_ग_लिखो(common->regmap, common->reg,
			  reg | (index << mux->shअगरt));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sprd_mux_helper_set_parent);

अटल पूर्णांक sprd_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा sprd_mux *cm = hw_to_sprd_mux(hw);

	वापस sprd_mux_helper_set_parent(&cm->common, &cm->mux, index);
पूर्ण

स्थिर काष्ठा clk_ops sprd_mux_ops = अणु
	.get_parent = sprd_mux_get_parent,
	.set_parent = sprd_mux_set_parent,
	.determine_rate = __clk_mux_determine_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(sprd_mux_ops);
