<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// OWL mux घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>

#समावेश "owl-mux.h"

u8 owl_mux_helper_get_parent(स्थिर काष्ठा owl_clk_common *common,
			     स्थिर काष्ठा owl_mux_hw *mux_hw)
अणु
	u32 reg;
	u8 parent;

	regmap_पढ़ो(common->regmap, mux_hw->reg, &reg);
	parent = reg >> mux_hw->shअगरt;
	parent &= BIT(mux_hw->width) - 1;

	वापस parent;
पूर्ण

अटल u8 owl_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_mux *mux = hw_to_owl_mux(hw);

	वापस owl_mux_helper_get_parent(&mux->common, &mux->mux_hw);
पूर्ण

पूर्णांक owl_mux_helper_set_parent(स्थिर काष्ठा owl_clk_common *common,
			      काष्ठा owl_mux_hw *mux_hw, u8 index)
अणु
	u32 reg;

	regmap_पढ़ो(common->regmap, mux_hw->reg, &reg);
	reg &= ~GENMASK(mux_hw->width + mux_hw->shअगरt - 1, mux_hw->shअगरt);
	regmap_ग_लिखो(common->regmap, mux_hw->reg,
			reg | (index << mux_hw->shअगरt));

	वापस 0;
पूर्ण

अटल पूर्णांक owl_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा owl_mux *mux = hw_to_owl_mux(hw);

	वापस owl_mux_helper_set_parent(&mux->common, &mux->mux_hw, index);
पूर्ण

स्थिर काष्ठा clk_ops owl_mux_ops = अणु
	.get_parent = owl_mux_get_parent,
	.set_parent = owl_mux_set_parent,
	.determine_rate = __clk_mux_determine_rate,
पूर्ण;
