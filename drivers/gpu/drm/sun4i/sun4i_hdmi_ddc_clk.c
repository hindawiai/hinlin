<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Free Electrons
 * Copyright (C) 2016 NextThing Co
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>

#समावेश "sun4i_hdmi.h"

काष्ठा sun4i_ddc अणु
	काष्ठा clk_hw		hw;
	काष्ठा sun4i_hdmi	*hdmi;
	काष्ठा regmap_field	*reg;
	u8			pre_भाग;
	u8			m_offset;
पूर्ण;

अटल अंतरभूत काष्ठा sun4i_ddc *hw_to_ddc(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा sun4i_ddc, hw);
पूर्ण

अटल अचिन्हित दीर्घ sun4i_ddc_calc_भागider(अचिन्हित दीर्घ rate,
					    अचिन्हित दीर्घ parent_rate,
					    स्थिर u8 pre_भाग,
					    स्थिर u8 m_offset,
					    u8 *m, u8 *n)
अणु
	अचिन्हित दीर्घ best_rate = 0;
	u8 best_m = 0, best_n = 0, _m, _n;

	क्रम (_m = 0; _m < 16; _m++) अणु
		क्रम (_n = 0; _n < 8; _n++) अणु
			अचिन्हित दीर्घ पंचांगp_rate;

			पंचांगp_rate = (((parent_rate / pre_भाग) / 10) >> _n) /
				(_m + m_offset);

			अगर (पंचांगp_rate > rate)
				जारी;

			अगर (असल(rate - पंचांगp_rate) < असल(rate - best_rate)) अणु
				best_rate = पंचांगp_rate;
				best_m = _m;
				best_n = _n;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (m && n) अणु
		*m = best_m;
		*n = best_n;
	पूर्ण

	वापस best_rate;
पूर्ण

अटल दीर्घ sun4i_ddc_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ *prate)
अणु
	काष्ठा sun4i_ddc *ddc = hw_to_ddc(hw);

	वापस sun4i_ddc_calc_भागider(rate, *prate, ddc->pre_भाग,
				      ddc->m_offset, शून्य, शून्य);
पूर्ण

अटल अचिन्हित दीर्घ sun4i_ddc_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sun4i_ddc *ddc = hw_to_ddc(hw);
	अचिन्हित पूर्णांक reg;
	u8 m, n;

	regmap_field_पढ़ो(ddc->reg, &reg);
	m = (reg >> 3) & 0xf;
	n = reg & 0x7;

	वापस (((parent_rate / ddc->pre_भाग) / 10) >> n) /
	       (m + ddc->m_offset);
पूर्ण

अटल पूर्णांक sun4i_ddc_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sun4i_ddc *ddc = hw_to_ddc(hw);
	u8 भाग_m, भाग_n;

	sun4i_ddc_calc_भागider(rate, parent_rate, ddc->pre_भाग,
			       ddc->m_offset, &भाग_m, &भाग_n);

	regmap_field_ग_लिखो(ddc->reg,
			   SUN4I_HDMI_DDC_CLK_M(भाग_m) |
			   SUN4I_HDMI_DDC_CLK_N(भाग_n));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops sun4i_ddc_ops = अणु
	.recalc_rate	= sun4i_ddc_recalc_rate,
	.round_rate	= sun4i_ddc_round_rate,
	.set_rate	= sun4i_ddc_set_rate,
पूर्ण;

पूर्णांक sun4i_ddc_create(काष्ठा sun4i_hdmi *hdmi, काष्ठा clk *parent)
अणु
	काष्ठा clk_init_data init;
	काष्ठा sun4i_ddc *ddc;
	स्थिर अक्षर *parent_name;

	parent_name = __clk_get_name(parent);
	अगर (!parent_name)
		वापस -ENODEV;

	ddc = devm_kzalloc(hdmi->dev, माप(*ddc), GFP_KERNEL);
	अगर (!ddc)
		वापस -ENOMEM;

	ddc->reg = devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					   hdmi->variant->ddc_clk_reg);
	अगर (IS_ERR(ddc->reg))
		वापस PTR_ERR(ddc->reg);

	init.name = "hdmi-ddc";
	init.ops = &sun4i_ddc_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	ddc->hdmi = hdmi;
	ddc->hw.init = &init;
	ddc->pre_भाग = hdmi->variant->ddc_clk_pre_भागider;
	ddc->m_offset = hdmi->variant->ddc_clk_m_offset;

	hdmi->ddc_clk = devm_clk_रेजिस्टर(hdmi->dev, &ddc->hw);
	अगर (IS_ERR(hdmi->ddc_clk))
		वापस PTR_ERR(hdmi->ddc_clk);

	वापस 0;
पूर्ण
