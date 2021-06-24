<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Spपढ़ोtrum भागider घड़ी driver
//
// Copyright (C) 2017 Spपढ़ोtrum, Inc.
// Author: Chunyan Zhang <chunyan.zhang@spपढ़ोtrum.com>

#समावेश <linux/clk-provider.h>

#समावेश "div.h"

दीर्घ sprd_भाग_helper_round_rate(काष्ठा sprd_clk_common *common,
				स्थिर काष्ठा sprd_भाग_पूर्णांकernal *भाग,
				अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	वापस भागider_round_rate(&common->hw, rate, parent_rate,
				  शून्य, भाग->width, 0);
पूर्ण
EXPORT_SYMBOL_GPL(sprd_भाग_helper_round_rate);

अटल दीर्घ sprd_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा sprd_भाग *cd = hw_to_sprd_भाग(hw);

	वापस sprd_भाग_helper_round_rate(&cd->common, &cd->भाग,
					  rate, parent_rate);
पूर्ण

अचिन्हित दीर्घ sprd_भाग_helper_recalc_rate(काष्ठा sprd_clk_common *common,
					  स्थिर काष्ठा sprd_भाग_पूर्णांकernal *भाग,
					  अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ val;
	अचिन्हित पूर्णांक reg;

	regmap_पढ़ो(common->regmap, common->reg, &reg);
	val = reg >> भाग->shअगरt;
	val &= (1 << भाग->width) - 1;

	वापस भागider_recalc_rate(&common->hw, parent_rate, val, शून्य, 0,
				   भाग->width);
पूर्ण
EXPORT_SYMBOL_GPL(sprd_भाग_helper_recalc_rate);

अटल अचिन्हित दीर्घ sprd_भाग_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sprd_भाग *cd = hw_to_sprd_भाग(hw);

	वापस sprd_भाग_helper_recalc_rate(&cd->common, &cd->भाग, parent_rate);
पूर्ण

पूर्णांक sprd_भाग_helper_set_rate(स्थिर काष्ठा sprd_clk_common *common,
			     स्थिर काष्ठा sprd_भाग_पूर्णांकernal *भाग,
			     अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ val;
	अचिन्हित पूर्णांक reg;

	val = भागider_get_val(rate, parent_rate, शून्य,
			      भाग->width, 0);

	regmap_पढ़ो(common->regmap, common->reg, &reg);
	reg &= ~GENMASK(भाग->width + भाग->shअगरt - 1, भाग->shअगरt);

	regmap_ग_लिखो(common->regmap, common->reg,
			  reg | (val << भाग->shअगरt));

	वापस 0;

पूर्ण
EXPORT_SYMBOL_GPL(sprd_भाग_helper_set_rate);

अटल पूर्णांक sprd_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sprd_भाग *cd = hw_to_sprd_भाग(hw);

	वापस sprd_भाग_helper_set_rate(&cd->common, &cd->भाग,
					rate, parent_rate);
पूर्ण

स्थिर काष्ठा clk_ops sprd_भाग_ops = अणु
	.recalc_rate = sprd_भाग_recalc_rate,
	.round_rate = sprd_भाग_round_rate,
	.set_rate = sprd_भाग_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(sprd_भाग_ops);
