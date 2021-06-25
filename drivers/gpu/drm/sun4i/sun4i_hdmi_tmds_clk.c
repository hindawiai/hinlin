<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Free Electrons
 * Copyright (C) 2016 NextThing Co
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>

#समावेश "sun4i_hdmi.h"

काष्ठा sun4i_पंचांगds अणु
	काष्ठा clk_hw		hw;
	काष्ठा sun4i_hdmi	*hdmi;

	u8			भाग_offset;
पूर्ण;

अटल अंतरभूत काष्ठा sun4i_पंचांगds *hw_to_पंचांगds(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा sun4i_पंचांगds, hw);
पूर्ण


अटल अचिन्हित दीर्घ sun4i_पंचांगds_calc_भागider(अचिन्हित दीर्घ rate,
					     अचिन्हित दीर्घ parent_rate,
					     u8 भाग_offset,
					     u8 *भाग,
					     bool *half)
अणु
	अचिन्हित दीर्घ best_rate = 0;
	u8 best_m = 0, m;
	bool is_द्विगुन = false;

	क्रम (m = भाग_offset ?: 1; m < (16 + भाग_offset); m++) अणु
		u8 d;

		क्रम (d = 1; d < 3; d++) अणु
			अचिन्हित दीर्घ पंचांगp_rate;

			पंचांगp_rate = parent_rate / m / d;

			अगर (पंचांगp_rate > rate)
				जारी;

			अगर (!best_rate ||
			    (rate - पंचांगp_rate) < (rate - best_rate)) अणु
				best_rate = पंचांगp_rate;
				best_m = m;
				is_द्विगुन = (d == 2) ? true : false;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (भाग && half) अणु
		*भाग = best_m;
		*half = is_द्विगुन;
	पूर्ण

	वापस best_rate;
पूर्ण


अटल पूर्णांक sun4i_पंचांगds_determine_rate(काष्ठा clk_hw *hw,
				     काष्ठा clk_rate_request *req)
अणु
	काष्ठा sun4i_पंचांगds *पंचांगds = hw_to_पंचांगds(hw);
	काष्ठा clk_hw *parent = शून्य;
	अचिन्हित दीर्घ best_parent = 0;
	अचिन्हित दीर्घ rate = req->rate;
	पूर्णांक best_भाग = 1, best_half = 1;
	पूर्णांक i, j, p;

	/*
	 * We only consider PLL3, since the TCON is very likely to be
	 * घड़ीed from it, and to have the same rate than our HDMI
	 * घड़ी, so we should not need to करो anything.
	 */

	क्रम (p = 0; p < clk_hw_get_num_parents(hw); p++) अणु
		parent = clk_hw_get_parent_by_index(hw, p);
		अगर (!parent)
			जारी;

		क्रम (i = 1; i < 3; i++) अणु
			क्रम (j = पंचांगds->भाग_offset ?: 1;
			     j < (16 + पंचांगds->भाग_offset); j++) अणु
				अचिन्हित दीर्घ ideal = rate * i * j;
				अचिन्हित दीर्घ rounded;

				rounded = clk_hw_round_rate(parent, ideal);

				अगर (rounded == ideal) अणु
					best_parent = rounded;
					best_half = i;
					best_भाग = j;
					जाओ out;
				पूर्ण

				अगर (!best_parent ||
				    असल(rate - rounded / i / j) <
				    असल(rate - best_parent / best_half /
					best_भाग)) अणु
					best_parent = rounded;
					best_half = i;
					best_भाग = j;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!parent)
		वापस -EINVAL;

out:
	req->rate = best_parent / best_half / best_भाग;
	req->best_parent_rate = best_parent;
	req->best_parent_hw = parent;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ sun4i_पंचांगds_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sun4i_पंचांगds *पंचांगds = hw_to_पंचांगds(hw);
	u32 reg;

	reg = पढ़ोl(पंचांगds->hdmi->base + SUN4I_HDMI_PAD_CTRL1_REG);
	अगर (reg & SUN4I_HDMI_PAD_CTRL1_HALVE_CLK)
		parent_rate /= 2;

	reg = पढ़ोl(पंचांगds->hdmi->base + SUN4I_HDMI_PLL_CTRL_REG);
	reg = ((reg >> 4) & 0xf) + पंचांगds->भाग_offset;
	अगर (!reg)
		reg = 1;

	वापस parent_rate / reg;
पूर्ण

अटल पूर्णांक sun4i_पंचांगds_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sun4i_पंचांगds *पंचांगds = hw_to_पंचांगds(hw);
	bool half;
	u32 reg;
	u8 भाग;

	sun4i_पंचांगds_calc_भागider(rate, parent_rate, पंचांगds->भाग_offset,
				&भाग, &half);

	reg = पढ़ोl(पंचांगds->hdmi->base + SUN4I_HDMI_PAD_CTRL1_REG);
	reg &= ~SUN4I_HDMI_PAD_CTRL1_HALVE_CLK;
	अगर (half)
		reg |= SUN4I_HDMI_PAD_CTRL1_HALVE_CLK;
	ग_लिखोl(reg, पंचांगds->hdmi->base + SUN4I_HDMI_PAD_CTRL1_REG);

	reg = पढ़ोl(पंचांगds->hdmi->base + SUN4I_HDMI_PLL_CTRL_REG);
	reg &= ~SUN4I_HDMI_PLL_CTRL_DIV_MASK;
	ग_लिखोl(reg | SUN4I_HDMI_PLL_CTRL_DIV(भाग - पंचांगds->भाग_offset),
	       पंचांगds->hdmi->base + SUN4I_HDMI_PLL_CTRL_REG);

	वापस 0;
पूर्ण

अटल u8 sun4i_पंचांगds_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा sun4i_पंचांगds *पंचांगds = hw_to_पंचांगds(hw);
	u32 reg;

	reg = पढ़ोl(पंचांगds->hdmi->base + SUN4I_HDMI_PLL_DBG0_REG);
	वापस ((reg & SUN4I_HDMI_PLL_DBG0_TMDS_PARENT_MASK) >>
		SUN4I_HDMI_PLL_DBG0_TMDS_PARENT_SHIFT);
पूर्ण

अटल पूर्णांक sun4i_पंचांगds_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा sun4i_पंचांगds *पंचांगds = hw_to_पंचांगds(hw);
	u32 reg;

	अगर (index > 1)
		वापस -EINVAL;

	reg = पढ़ोl(पंचांगds->hdmi->base + SUN4I_HDMI_PLL_DBG0_REG);
	reg &= ~SUN4I_HDMI_PLL_DBG0_TMDS_PARENT_MASK;
	ग_लिखोl(reg | SUN4I_HDMI_PLL_DBG0_TMDS_PARENT(index),
	       पंचांगds->hdmi->base + SUN4I_HDMI_PLL_DBG0_REG);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops sun4i_पंचांगds_ops = अणु
	.determine_rate	= sun4i_पंचांगds_determine_rate,
	.recalc_rate	= sun4i_पंचांगds_recalc_rate,
	.set_rate	= sun4i_पंचांगds_set_rate,

	.get_parent	= sun4i_पंचांगds_get_parent,
	.set_parent	= sun4i_पंचांगds_set_parent,
पूर्ण;

पूर्णांक sun4i_पंचांगds_create(काष्ठा sun4i_hdmi *hdmi)
अणु
	काष्ठा clk_init_data init;
	काष्ठा sun4i_पंचांगds *पंचांगds;
	स्थिर अक्षर *parents[2];

	parents[0] = __clk_get_name(hdmi->pll0_clk);
	अगर (!parents[0])
		वापस -ENODEV;

	parents[1] = __clk_get_name(hdmi->pll1_clk);
	अगर (!parents[1])
		वापस -ENODEV;

	पंचांगds = devm_kzalloc(hdmi->dev, माप(*पंचांगds), GFP_KERNEL);
	अगर (!पंचांगds)
		वापस -ENOMEM;

	init.name = "hdmi-tmds";
	init.ops = &sun4i_पंचांगds_ops;
	init.parent_names = parents;
	init.num_parents = 2;
	init.flags = CLK_SET_RATE_PARENT;

	पंचांगds->hdmi = hdmi;
	पंचांगds->hw.init = &init;
	पंचांगds->भाग_offset = hdmi->variant->पंचांगds_clk_भाग_offset;

	hdmi->पंचांगds_clk = devm_clk_रेजिस्टर(hdmi->dev, &पंचांगds->hw);
	अगर (IS_ERR(hdmi->पंचांगds_clk))
		वापस PTR_ERR(hdmi->पंचांगds_clk);

	वापस 0;
पूर्ण
