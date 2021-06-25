<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 Jernej Skrabec <jernej.skrabec@siol.net>
 */

#समावेश <linux/clk-provider.h>

#समावेश "sun8i_dw_hdmi.h"

काष्ठा sun8i_phy_clk अणु
	काष्ठा clk_hw		hw;
	काष्ठा sun8i_hdmi_phy	*phy;
पूर्ण;

अटल अंतरभूत काष्ठा sun8i_phy_clk *hw_to_phy_clk(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा sun8i_phy_clk, hw);
पूर्ण

अटल पूर्णांक sun8i_phy_clk_determine_rate(काष्ठा clk_hw *hw,
					काष्ठा clk_rate_request *req)
अणु
	अचिन्हित दीर्घ rate = req->rate;
	अचिन्हित दीर्घ best_rate = 0;
	काष्ठा clk_hw *best_parent = शून्य;
	काष्ठा clk_hw *parent;
	पूर्णांक best_भाग = 1;
	पूर्णांक i, p;

	क्रम (p = 0; p < clk_hw_get_num_parents(hw); p++) अणु
		parent = clk_hw_get_parent_by_index(hw, p);
		अगर (!parent)
			जारी;

		क्रम (i = 1; i <= 16; i++) अणु
			अचिन्हित दीर्घ ideal = rate * i;
			अचिन्हित दीर्घ rounded;

			rounded = clk_hw_round_rate(parent, ideal);

			अगर (rounded == ideal) अणु
				best_rate = rounded;
				best_भाग = i;
				best_parent = parent;
				अवरोध;
			पूर्ण

			अगर (!best_rate ||
			    असल(rate - rounded / i) <
			    असल(rate - best_rate / best_भाग)) अणु
				best_rate = rounded;
				best_भाग = i;
				best_parent = parent;
			पूर्ण
		पूर्ण

		अगर (best_rate / best_भाग == rate)
			अवरोध;
	पूर्ण

	req->rate = best_rate / best_भाग;
	req->best_parent_rate = best_rate;
	req->best_parent_hw = best_parent;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ sun8i_phy_clk_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sun8i_phy_clk *priv = hw_to_phy_clk(hw);
	u32 reg;

	regmap_पढ़ो(priv->phy->regs, SUN8I_HDMI_PHY_PLL_CFG2_REG, &reg);
	reg = ((reg >> SUN8I_HDMI_PHY_PLL_CFG2_PREDIV_SHIFT) &
		SUN8I_HDMI_PHY_PLL_CFG2_PREDIV_MSK) + 1;

	वापस parent_rate / reg;
पूर्ण

अटल पूर्णांक sun8i_phy_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sun8i_phy_clk *priv = hw_to_phy_clk(hw);
	अचिन्हित दीर्घ best_rate = 0;
	u8 best_m = 0, m;

	क्रम (m = 1; m <= 16; m++) अणु
		अचिन्हित दीर्घ पंचांगp_rate = parent_rate / m;

		अगर (पंचांगp_rate > rate)
			जारी;

		अगर (!best_rate ||
		    (rate - पंचांगp_rate) < (rate - best_rate)) अणु
			best_rate = पंचांगp_rate;
			best_m = m;
		पूर्ण
	पूर्ण

	regmap_update_bits(priv->phy->regs, SUN8I_HDMI_PHY_PLL_CFG2_REG,
			   SUN8I_HDMI_PHY_PLL_CFG2_PREDIV_MSK,
			   SUN8I_HDMI_PHY_PLL_CFG2_PREDIV(best_m));

	वापस 0;
पूर्ण

अटल u8 sun8i_phy_clk_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा sun8i_phy_clk *priv = hw_to_phy_clk(hw);
	u32 reg;

	regmap_पढ़ो(priv->phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG, &reg);
	reg = (reg & SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_MSK) >>
	      SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_SHIFT;

	वापस reg;
पूर्ण

अटल पूर्णांक sun8i_phy_clk_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा sun8i_phy_clk *priv = hw_to_phy_clk(hw);

	अगर (index > 1)
		वापस -EINVAL;

	regmap_update_bits(priv->phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG,
			   SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_MSK,
			   index << SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_SHIFT);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops sun8i_phy_clk_ops = अणु
	.determine_rate	= sun8i_phy_clk_determine_rate,
	.recalc_rate	= sun8i_phy_clk_recalc_rate,
	.set_rate	= sun8i_phy_clk_set_rate,

	.get_parent	= sun8i_phy_clk_get_parent,
	.set_parent	= sun8i_phy_clk_set_parent,
पूर्ण;

पूर्णांक sun8i_phy_clk_create(काष्ठा sun8i_hdmi_phy *phy, काष्ठा device *dev,
			 bool second_parent)
अणु
	काष्ठा clk_init_data init;
	काष्ठा sun8i_phy_clk *priv;
	स्थिर अक्षर *parents[2];

	parents[0] = __clk_get_name(phy->clk_pll0);
	अगर (!parents[0])
		वापस -ENODEV;

	अगर (second_parent) अणु
		parents[1] = __clk_get_name(phy->clk_pll1);
		अगर (!parents[1])
			वापस -ENODEV;
	पूर्ण

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	init.name = "hdmi-phy-clk";
	init.ops = &sun8i_phy_clk_ops;
	init.parent_names = parents;
	init.num_parents = second_parent ? 2 : 1;
	init.flags = CLK_SET_RATE_PARENT;

	priv->phy = phy;
	priv->hw.init = &init;

	phy->clk_phy = devm_clk_रेजिस्टर(dev, &priv->hw);
	अगर (IS_ERR(phy->clk_phy))
		वापस PTR_ERR(phy->clk_phy);

	वापस 0;
पूर्ण
