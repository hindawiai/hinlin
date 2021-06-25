<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// OWL भागider घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>

#समावेश "owl-divider.h"

दीर्घ owl_भागider_helper_round_rate(काष्ठा owl_clk_common *common,
				स्थिर काष्ठा owl_भागider_hw *भाग_hw,
				अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	वापस भागider_round_rate(&common->hw, rate, parent_rate,
				  भाग_hw->table, भाग_hw->width,
				  भाग_hw->भाग_flags);
पूर्ण

अटल दीर्घ owl_भागider_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा owl_भागider *भाग = hw_to_owl_भागider(hw);

	वापस owl_भागider_helper_round_rate(&भाग->common, &भाग->भाग_hw,
					     rate, parent_rate);
पूर्ण

अचिन्हित दीर्घ owl_भागider_helper_recalc_rate(काष्ठा owl_clk_common *common,
					 स्थिर काष्ठा owl_भागider_hw *भाग_hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ val;
	अचिन्हित पूर्णांक reg;

	regmap_पढ़ो(common->regmap, भाग_hw->reg, &reg);
	val = reg >> भाग_hw->shअगरt;
	val &= (1 << भाग_hw->width) - 1;

	वापस भागider_recalc_rate(&common->hw, parent_rate,
				   val, भाग_hw->table,
				   भाग_hw->भाग_flags,
				   भाग_hw->width);
पूर्ण

अटल अचिन्हित दीर्घ owl_भागider_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा owl_भागider *भाग = hw_to_owl_भागider(hw);

	वापस owl_भागider_helper_recalc_rate(&भाग->common,
					      &भाग->भाग_hw, parent_rate);
पूर्ण

पूर्णांक owl_भागider_helper_set_rate(स्थिर काष्ठा owl_clk_common *common,
				स्थिर काष्ठा owl_भागider_hw *भाग_hw,
				अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ val;
	अचिन्हित पूर्णांक reg;

	val = भागider_get_val(rate, parent_rate, भाग_hw->table,
			      भाग_hw->width, 0);

	regmap_पढ़ो(common->regmap, भाग_hw->reg, &reg);
	reg &= ~GENMASK(भाग_hw->width + भाग_hw->shअगरt - 1, भाग_hw->shअगरt);

	regmap_ग_लिखो(common->regmap, भाग_hw->reg,
			  reg | (val << भाग_hw->shअगरt));

	वापस 0;
पूर्ण

अटल पूर्णांक owl_भागider_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा owl_भागider *भाग = hw_to_owl_भागider(hw);

	वापस owl_भागider_helper_set_rate(&भाग->common, &भाग->भाग_hw,
					rate, parent_rate);
पूर्ण

स्थिर काष्ठा clk_ops owl_भागider_ops = अणु
	.recalc_rate = owl_भागider_recalc_rate,
	.round_rate = owl_भागider_round_rate,
	.set_rate = owl_भागider_set_rate,
पूर्ण;
