<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/regmap.h>
#समावेश <linux/export.h>

#समावेश "clk-regmap-divider.h"

अटल अंतरभूत काष्ठा clk_regmap_भाग *to_clk_regmap_भाग(काष्ठा clk_hw *hw)
अणु
	वापस container_of(to_clk_regmap(hw), काष्ठा clk_regmap_भाग, clkr);
पूर्ण

अटल दीर्घ भाग_round_ro_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_regmap_भाग *भागider = to_clk_regmap_भाग(hw);
	काष्ठा clk_regmap *clkr = &भागider->clkr;
	u32 val;

	regmap_पढ़ो(clkr->regmap, भागider->reg, &val);
	val >>= भागider->shअगरt;
	val &= BIT(भागider->width) - 1;

	वापस भागider_ro_round_rate(hw, rate, prate, शून्य, भागider->width,
				     CLK_DIVIDER_ROUND_CLOSEST, val);
पूर्ण

अटल दीर्घ भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_regmap_भाग *भागider = to_clk_regmap_भाग(hw);

	वापस भागider_round_rate(hw, rate, prate, शून्य, भागider->width,
				  CLK_DIVIDER_ROUND_CLOSEST);
पूर्ण

अटल पूर्णांक भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_regmap_भाग *भागider = to_clk_regmap_भाग(hw);
	काष्ठा clk_regmap *clkr = &भागider->clkr;
	u32 भाग;

	भाग = भागider_get_val(rate, parent_rate, शून्य, भागider->width,
			      CLK_DIVIDER_ROUND_CLOSEST);

	वापस regmap_update_bits(clkr->regmap, भागider->reg,
				  (BIT(भागider->width) - 1) << भागider->shअगरt,
				  भाग << भागider->shअगरt);
पूर्ण

अटल अचिन्हित दीर्घ भाग_recalc_rate(काष्ठा clk_hw *hw,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_regmap_भाग *भागider = to_clk_regmap_भाग(hw);
	काष्ठा clk_regmap *clkr = &भागider->clkr;
	u32 भाग;

	regmap_पढ़ो(clkr->regmap, भागider->reg, &भाग);
	भाग >>= भागider->shअगरt;
	भाग &= BIT(भागider->width) - 1;

	वापस भागider_recalc_rate(hw, parent_rate, भाग, शून्य,
				   CLK_DIVIDER_ROUND_CLOSEST, भागider->width);
पूर्ण

स्थिर काष्ठा clk_ops clk_regmap_भाग_ops = अणु
	.round_rate = भाग_round_rate,
	.set_rate = भाग_set_rate,
	.recalc_rate = भाग_recalc_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_regmap_भाग_ops);

स्थिर काष्ठा clk_ops clk_regmap_भाग_ro_ops = अणु
	.round_rate = भाग_round_ro_rate,
	.recalc_rate = भाग_recalc_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_regmap_भाग_ro_ops);
