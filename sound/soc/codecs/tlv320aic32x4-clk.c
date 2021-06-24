<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Clock Tree क्रम the Texas Instruments TLV320AIC32x4
 *
 * Copyright 2019 Annaliese McDermond
 *
 * Author: Annaliese McDermond <nh6z@nh6z.net>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/regmap.h>
#समावेश <linux/device.h>

#समावेश "tlv320aic32x4.h"

#घोषणा to_clk_aic32x4(_hw) container_of(_hw, काष्ठा clk_aic32x4, hw)
काष्ठा clk_aic32x4 अणु
	काष्ठा clk_hw hw;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक reg;
पूर्ण;

/*
 * काष्ठा clk_aic32x4_pll_muद_भाग - Multiplier/भागider settings
 * @p:		Divider
 * @r:		first multiplier
 * @j:		पूर्णांकeger part of second multiplier
 * @d:		decimal part of second multiplier
 */
काष्ठा clk_aic32x4_pll_muद_भाग अणु
	u8 p;
	u16 r;
	u8 j;
	u16 d;
पूर्ण;

काष्ठा aic32x4_clkdesc अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *parent_names;
	अचिन्हित पूर्णांक num_parents;
	स्थिर काष्ठा clk_ops *ops;
	अचिन्हित पूर्णांक reg;
पूर्ण;

अटल पूर्णांक clk_aic32x4_pll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_aic32x4 *pll = to_clk_aic32x4(hw);

	वापस regmap_update_bits(pll->regmap, AIC32X4_PLLPR,
				AIC32X4_PLLEN, AIC32X4_PLLEN);
पूर्ण

अटल व्योम clk_aic32x4_pll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_aic32x4 *pll = to_clk_aic32x4(hw);

	regmap_update_bits(pll->regmap, AIC32X4_PLLPR,
				AIC32X4_PLLEN, 0);
पूर्ण

अटल पूर्णांक clk_aic32x4_pll_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_aic32x4 *pll = to_clk_aic32x4(hw);

	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pll->regmap, AIC32X4_PLLPR, &val);
	अगर (ret < 0)
		वापस ret;

	वापस !!(val & AIC32X4_PLLEN);
पूर्ण

अटल पूर्णांक clk_aic32x4_pll_get_muद_भाग(काष्ठा clk_aic32x4 *pll,
			काष्ठा clk_aic32x4_pll_muद_भाग *settings)
अणु
	/*	Change to use regmap_bulk_पढ़ो? */
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pll->regmap, AIC32X4_PLLPR, &val);
	अगर (ret < 0)
		वापस ret;
	settings->r = val & AIC32X4_PLL_R_MASK;
	settings->p = (val & AIC32X4_PLL_P_MASK) >> AIC32X4_PLL_P_SHIFT;

	ret = regmap_पढ़ो(pll->regmap, AIC32X4_PLLJ, &val);
	अगर (ret < 0)
		वापस ret;
	settings->j = val;

	ret = regmap_पढ़ो(pll->regmap, AIC32X4_PLLDMSB, &val);
	अगर (ret < 0)
		वापस ret;
	settings->d = val << 8;

	ret = regmap_पढ़ो(pll->regmap, AIC32X4_PLLDLSB,	 &val);
	अगर (ret < 0)
		वापस ret;
	settings->d |= val;

	वापस 0;
पूर्ण

अटल पूर्णांक clk_aic32x4_pll_set_muद_भाग(काष्ठा clk_aic32x4 *pll,
			काष्ठा clk_aic32x4_pll_muद_भाग *settings)
अणु
	पूर्णांक ret;
	/*	Change to use regmap_bulk_ग_लिखो क्रम some अगर not all? */

	ret = regmap_update_bits(pll->regmap, AIC32X4_PLLPR,
				AIC32X4_PLL_R_MASK, settings->r);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(pll->regmap, AIC32X4_PLLPR,
				AIC32X4_PLL_P_MASK,
				settings->p << AIC32X4_PLL_P_SHIFT);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(pll->regmap, AIC32X4_PLLJ, settings->j);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(pll->regmap, AIC32X4_PLLDMSB, (settings->d >> 8));
	अगर (ret < 0)
		वापस ret;
	ret = regmap_ग_लिखो(pll->regmap, AIC32X4_PLLDLSB, (settings->d & 0xff));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ clk_aic32x4_pll_calc_rate(
			काष्ठा clk_aic32x4_pll_muद_भाग *settings,
			अचिन्हित दीर्घ parent_rate)
अणु
	u64 rate;
	/*
	 * We scale j by 10000 to account क्रम the decimal part of P and भागide
	 * it back out later.
	 */
	rate = (u64) parent_rate * settings->r *
				((settings->j * 10000) + settings->d);

	वापस (अचिन्हित दीर्घ) DIV_ROUND_UP_ULL(rate, settings->p * 10000);
पूर्ण

अटल पूर्णांक clk_aic32x4_pll_calc_muद_भाग(काष्ठा clk_aic32x4_pll_muद_भाग *settings,
			अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	u64 multiplier;

	settings->p = parent_rate / AIC32X4_MAX_PLL_CLKIN + 1;
	अगर (settings->p > 8)
		वापस -1;

	/*
	 * We scale this figure by 10000 so that we can get the decimal part
	 * of the multiplier.	This is because we can't करो भग्नing poपूर्णांक
	 * math in the kernel.
	 */
	multiplier = (u64) rate * settings->p * 10000;
	करो_भाग(multiplier, parent_rate);

	/*
	 * J can't be over 64, so R can scale this.
	 * R can't be greater than 4.
	 */
	settings->r = ((u32) multiplier / 640000) + 1;
	अगर (settings->r > 4)
		वापस -1;
	करो_भाग(multiplier, settings->r);

	/*
	 * J can't be < 1.
	 */
	अगर (multiplier < 10000)
		वापस -1;

	/* Figure out the पूर्णांकeger part, J, and the fractional part, D. */
	settings->j = (u32) multiplier / 10000;
	settings->d = (u32) multiplier % 10000;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ clk_aic32x4_pll_recalc_rate(काष्ठा clk_hw *hw,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_aic32x4 *pll = to_clk_aic32x4(hw);
	काष्ठा clk_aic32x4_pll_muद_भाग settings;
	पूर्णांक ret;

	ret =  clk_aic32x4_pll_get_muद_भाग(pll, &settings);
	अगर (ret < 0)
		वापस 0;

	वापस clk_aic32x4_pll_calc_rate(&settings, parent_rate);
पूर्ण

अटल दीर्घ clk_aic32x4_pll_round_rate(काष्ठा clk_hw *hw,
			अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_aic32x4_pll_muद_भाग settings;
	पूर्णांक ret;

	ret = clk_aic32x4_pll_calc_muद_भाग(&settings, rate, *parent_rate);
	अगर (ret < 0)
		वापस 0;

	वापस clk_aic32x4_pll_calc_rate(&settings, *parent_rate);
पूर्ण

अटल पूर्णांक clk_aic32x4_pll_set_rate(काष्ठा clk_hw *hw,
			अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_aic32x4 *pll = to_clk_aic32x4(hw);
	काष्ठा clk_aic32x4_pll_muद_भाग settings;
	पूर्णांक ret;

	ret = clk_aic32x4_pll_calc_muद_भाग(&settings, rate, parent_rate);
	अगर (ret < 0)
		वापस -EINVAL;

	ret = clk_aic32x4_pll_set_muद_भाग(pll, &settings);
	अगर (ret)
		वापस ret;

	/* 10ms is the delay to रुको beक्रमe the घड़ीs are stable */
	msleep(10);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_aic32x4_pll_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_aic32x4 *pll = to_clk_aic32x4(hw);

	वापस regmap_update_bits(pll->regmap,
				AIC32X4_CLKMUX,
				AIC32X4_PLL_CLKIN_MASK,
				index << AIC32X4_PLL_CLKIN_SHIFT);
पूर्ण

अटल u8 clk_aic32x4_pll_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_aic32x4 *pll = to_clk_aic32x4(hw);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(pll->regmap, AIC32X4_PLLPR, &val);

	वापस (val & AIC32X4_PLL_CLKIN_MASK) >> AIC32X4_PLL_CLKIN_SHIFT;
पूर्ण


अटल स्थिर काष्ठा clk_ops aic32x4_pll_ops = अणु
	.prepare = clk_aic32x4_pll_prepare,
	.unprepare = clk_aic32x4_pll_unprepare,
	.is_prepared = clk_aic32x4_pll_is_prepared,
	.recalc_rate = clk_aic32x4_pll_recalc_rate,
	.round_rate = clk_aic32x4_pll_round_rate,
	.set_rate = clk_aic32x4_pll_set_rate,
	.set_parent = clk_aic32x4_pll_set_parent,
	.get_parent = clk_aic32x4_pll_get_parent,
पूर्ण;

अटल पूर्णांक clk_aic32x4_codec_clkin_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_aic32x4 *mux = to_clk_aic32x4(hw);

	वापस regmap_update_bits(mux->regmap,
		AIC32X4_CLKMUX,
		AIC32X4_CODEC_CLKIN_MASK, index << AIC32X4_CODEC_CLKIN_SHIFT);
पूर्ण

अटल u8 clk_aic32x4_codec_clkin_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_aic32x4 *mux = to_clk_aic32x4(hw);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(mux->regmap, AIC32X4_CLKMUX, &val);

	वापस (val & AIC32X4_CODEC_CLKIN_MASK) >> AIC32X4_CODEC_CLKIN_SHIFT;
पूर्ण

अटल स्थिर काष्ठा clk_ops aic32x4_codec_clkin_ops = अणु
	.set_parent = clk_aic32x4_codec_clkin_set_parent,
	.get_parent = clk_aic32x4_codec_clkin_get_parent,
पूर्ण;

अटल पूर्णांक clk_aic32x4_भाग_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_aic32x4 *भाग = to_clk_aic32x4(hw);

	वापस regmap_update_bits(भाग->regmap, भाग->reg,
				AIC32X4_DIVEN, AIC32X4_DIVEN);
पूर्ण

अटल व्योम clk_aic32x4_भाग_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_aic32x4 *भाग = to_clk_aic32x4(hw);

	regmap_update_bits(भाग->regmap, भाग->reg,
			AIC32X4_DIVEN, 0);
पूर्ण

अटल पूर्णांक clk_aic32x4_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_aic32x4 *भाग = to_clk_aic32x4(hw);
	u8 भागisor;

	भागisor = DIV_ROUND_UP(parent_rate, rate);
	अगर (भागisor > 128)
		वापस -EINVAL;

	वापस regmap_update_bits(भाग->regmap, भाग->reg,
				AIC32X4_DIV_MASK, भागisor);
पूर्ण

अटल दीर्घ clk_aic32x4_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित दीर्घ भागisor;

	भागisor = DIV_ROUND_UP(*parent_rate, rate);
	अगर (भागisor > 128)
		वापस -EINVAL;

	वापस DIV_ROUND_UP(*parent_rate, भागisor);
पूर्ण

अटल अचिन्हित दीर्घ clk_aic32x4_भाग_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_aic32x4 *भाग = to_clk_aic32x4(hw);

	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(भाग->regmap, भाग->reg, &val);

	वापस DIV_ROUND_UP(parent_rate, val & AIC32X4_DIV_MASK);
पूर्ण

अटल स्थिर काष्ठा clk_ops aic32x4_भाग_ops = अणु
	.prepare = clk_aic32x4_भाग_prepare,
	.unprepare = clk_aic32x4_भाग_unprepare,
	.set_rate = clk_aic32x4_भाग_set_rate,
	.round_rate = clk_aic32x4_भाग_round_rate,
	.recalc_rate = clk_aic32x4_भाग_recalc_rate,
पूर्ण;

अटल पूर्णांक clk_aic32x4_bभाग_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_aic32x4 *mux = to_clk_aic32x4(hw);

	वापस regmap_update_bits(mux->regmap, AIC32X4_IFACE3,
				AIC32X4_BDIVCLK_MASK, index);
पूर्ण

अटल u8 clk_aic32x4_bभाग_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_aic32x4 *mux = to_clk_aic32x4(hw);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(mux->regmap, AIC32X4_IFACE3, &val);

	वापस val & AIC32X4_BDIVCLK_MASK;
पूर्ण

अटल स्थिर काष्ठा clk_ops aic32x4_bभाग_ops = अणु
	.prepare = clk_aic32x4_भाग_prepare,
	.unprepare = clk_aic32x4_भाग_unprepare,
	.set_parent = clk_aic32x4_bभाग_set_parent,
	.get_parent = clk_aic32x4_bभाग_get_parent,
	.set_rate = clk_aic32x4_भाग_set_rate,
	.round_rate = clk_aic32x4_भाग_round_rate,
	.recalc_rate = clk_aic32x4_भाग_recalc_rate,
पूर्ण;

अटल काष्ठा aic32x4_clkdesc aic32x4_clkdesc_array[] = अणु
	अणु
		.name = "pll",
		.parent_names =
			(स्थिर अक्षर* []) अणु "mclk", "bclk", "gpio", "din" पूर्ण,
		.num_parents = 4,
		.ops = &aic32x4_pll_ops,
		.reg = 0,
	पूर्ण,
	अणु
		.name = "codec_clkin",
		.parent_names =
			(स्थिर अक्षर *[]) अणु "mclk", "bclk", "gpio", "pll" पूर्ण,
		.num_parents = 4,
		.ops = &aic32x4_codec_clkin_ops,
		.reg = 0,
	पूर्ण,
	अणु
		.name = "ndac",
		.parent_names = (स्थिर अक्षर * []) अणु "codec_clkin" पूर्ण,
		.num_parents = 1,
		.ops = &aic32x4_भाग_ops,
		.reg = AIC32X4_NDAC,
	पूर्ण,
	अणु
		.name = "mdac",
		.parent_names = (स्थिर अक्षर * []) अणु "ndac" पूर्ण,
		.num_parents = 1,
		.ops = &aic32x4_भाग_ops,
		.reg = AIC32X4_MDAC,
	पूर्ण,
	अणु
		.name = "nadc",
		.parent_names = (स्थिर अक्षर * []) अणु "codec_clkin" पूर्ण,
		.num_parents = 1,
		.ops = &aic32x4_भाग_ops,
		.reg = AIC32X4_NADC,
	पूर्ण,
	अणु
		.name = "madc",
		.parent_names = (स्थिर अक्षर * []) अणु "nadc" पूर्ण,
		.num_parents = 1,
		.ops = &aic32x4_भाग_ops,
		.reg = AIC32X4_MADC,
	पूर्ण,
	अणु
		.name = "bdiv",
		.parent_names =
			(स्थिर अक्षर *[]) अणु "ndac", "mdac", "nadc", "madc" पूर्ण,
		.num_parents = 4,
		.ops = &aic32x4_bभाग_ops,
		.reg = AIC32X4_BCLKN,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk *aic32x4_रेजिस्टर_clk(काष्ठा device *dev,
			काष्ठा aic32x4_clkdesc *desc)
अणु
	काष्ठा clk_init_data init;
	काष्ठा clk_aic32x4 *priv;
	स्थिर अक्षर *devname = dev_name(dev);

	init.ops = desc->ops;
	init.name = desc->name;
	init.parent_names = desc->parent_names;
	init.num_parents = desc->num_parents;
	init.flags = 0;

	priv = devm_kzalloc(dev, माप(काष्ठा clk_aic32x4), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस (काष्ठा clk *) -ENOMEM;

	priv->dev = dev;
	priv->hw.init = &init;
	priv->regmap = dev_get_regmap(dev, शून्य);
	priv->reg = desc->reg;

	clk_hw_रेजिस्टर_clkdev(&priv->hw, desc->name, devname);
	वापस devm_clk_रेजिस्टर(dev, &priv->hw);
पूर्ण

पूर्णांक aic32x4_रेजिस्टर_घड़ीs(काष्ठा device *dev, स्थिर अक्षर *mclk_name)
अणु
	पूर्णांक i;

	/*
	 * These lines are here to preserve the current functionality of
	 * the driver with regard to the DT.  These should eventually be set
	 * by DT nodes so that the connections can be set up in configuration
	 * rather than code.
	 */
	aic32x4_clkdesc_array[0].parent_names =
			(स्थिर अक्षर* []) अणु mclk_name, "bclk", "gpio", "din" पूर्ण;
	aic32x4_clkdesc_array[1].parent_names =
			(स्थिर अक्षर *[]) अणु mclk_name, "bclk", "gpio", "pll" पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(aic32x4_clkdesc_array); ++i)
		aic32x4_रेजिस्टर_clk(dev, &aic32x4_clkdesc_array[i]);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(aic32x4_रेजिस्टर_घड़ीs);
