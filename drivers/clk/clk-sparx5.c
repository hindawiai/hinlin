<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Microchip Sparx5 SoC Clock driver.
 *
 * Copyright (c) 2019 Microchip Inc.
 *
 * Author: Lars Povlsen <lars.povlsen@microchip.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <dt-bindings/घड़ी/microchip,sparx5.h>

#घोषणा PLL_DIV		GENMASK(7, 0)
#घोषणा PLL_PRE_DIV	GENMASK(10, 8)
#घोषणा PLL_ROT_सूची	BIT(11)
#घोषणा PLL_ROT_SEL	GENMASK(13, 12)
#घोषणा PLL_ROT_ENA	BIT(14)
#घोषणा PLL_CLK_ENA	BIT(15)

#घोषणा MAX_SEL 4
#घोषणा MAX_PRE BIT(3)

अटल स्थिर u8 sel_rates[MAX_SEL] = अणु 0, 2*8, 2*4, 2*2 पूर्ण;

अटल स्थिर अक्षर *clk_names[N_CLOCKS] = अणु
	"core", "ddr", "cpu2", "arm2",
	"aux1", "aux2", "aux3", "aux4",
	"synce",
पूर्ण;

काष्ठा s5_hw_clk अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg;
पूर्ण;

काष्ठा s5_clk_data अणु
	व्योम __iomem *base;
	काष्ठा s5_hw_clk s5_hw[N_CLOCKS];
पूर्ण;

काष्ठा s5_pll_conf अणु
	अचिन्हित दीर्घ freq;
	u8 भाग;
	bool rot_ena;
	u8 rot_sel;
	u8 rot_dir;
	u8 pre_भाग;
पूर्ण;

#घोषणा to_s5_pll(hw) container_of(hw, काष्ठा s5_hw_clk, hw)

अटल अचिन्हित दीर्घ s5_calc_freq(अचिन्हित दीर्घ parent_rate,
				  स्थिर काष्ठा s5_pll_conf *conf)
अणु
	अचिन्हित दीर्घ rate = parent_rate / conf->भाग;

	अगर (conf->rot_ena) अणु
		पूर्णांक sign = conf->rot_dir ? -1 : 1;
		पूर्णांक भागt = sel_rates[conf->rot_sel] * (1 + conf->pre_भाग);
		पूर्णांक भागb = भागt + sign;

		rate = mult_frac(rate, भागt, भागb);
		rate = roundup(rate, 1000);
	पूर्ण

	वापस rate;
पूर्ण

अटल व्योम s5_search_fractional(अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ parent_rate,
				 पूर्णांक भाग,
				 काष्ठा s5_pll_conf *conf)
अणु
	काष्ठा s5_pll_conf best;
	uदीर्घ cur_offset, best_offset = rate;
	पूर्णांक d, i, j;

	स_रखो(conf, 0, माप(*conf));
	conf->भाग = भाग;
	conf->rot_ena = 1;	/* Fractional rate */

	क्रम (d = 0; best_offset > 0 && d <= 1 ; d++) अणु
		conf->rot_dir = !!d;
		क्रम (i = 0; best_offset > 0 && i < MAX_PRE; i++) अणु
			conf->pre_भाग = i;
			क्रम (j = 1; best_offset > 0 && j < MAX_SEL; j++) अणु
				conf->rot_sel = j;
				conf->freq = s5_calc_freq(parent_rate, conf);
				cur_offset = असल(rate - conf->freq);
				अगर (cur_offset < best_offset) अणु
					best_offset = cur_offset;
					best = *conf;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Best match */
	*conf = best;
पूर्ण

अटल अचिन्हित दीर्घ s5_calc_params(अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate,
				    काष्ठा s5_pll_conf *conf)
अणु
	अगर (parent_rate % rate) अणु
		काष्ठा s5_pll_conf alt1, alt2;
		पूर्णांक भाग;

		भाग = DIV_ROUND_CLOSEST_ULL(parent_rate, rate);
		s5_search_fractional(rate, parent_rate, भाग, &alt1);

		/* Straight match? */
		अगर (alt1.freq == rate) अणु
			*conf = alt1;
		पूर्ण अन्यथा अणु
			/* Try without rounding भागider */
			भाग = parent_rate / rate;
			अगर (भाग != alt1.भाग) अणु
				s5_search_fractional(rate, parent_rate, भाग,
						     &alt2);
				/* Select the better match */
				अगर (असल(rate - alt1.freq) <
				    असल(rate - alt2.freq))
					*conf = alt1;
				अन्यथा
					*conf = alt2;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Straight fit */
		स_रखो(conf, 0, माप(*conf));
		conf->भाग = parent_rate / rate;
	पूर्ण

	वापस conf->freq;
पूर्ण

अटल पूर्णांक s5_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा s5_hw_clk *pll = to_s5_pll(hw);
	u32 val = पढ़ोl(pll->reg);

	val |= PLL_CLK_ENA;
	ग_लिखोl(val, pll->reg);

	वापस 0;
पूर्ण

अटल व्योम s5_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा s5_hw_clk *pll = to_s5_pll(hw);
	u32 val = पढ़ोl(pll->reg);

	val &= ~PLL_CLK_ENA;
	ग_लिखोl(val, pll->reg);
पूर्ण

अटल पूर्णांक s5_pll_set_rate(काष्ठा clk_hw *hw,
			   अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा s5_hw_clk *pll = to_s5_pll(hw);
	काष्ठा s5_pll_conf conf;
	अचिन्हित दीर्घ eff_rate;
	u32 val;

	eff_rate = s5_calc_params(rate, parent_rate, &conf);
	अगर (eff_rate != rate)
		वापस -EOPNOTSUPP;

	val = पढ़ोl(pll->reg) & PLL_CLK_ENA;
	val |= FIELD_PREP(PLL_DIV, conf.भाग);
	अगर (conf.rot_ena) अणु
		val |= PLL_ROT_ENA;
		val |= FIELD_PREP(PLL_ROT_SEL, conf.rot_sel);
		val |= FIELD_PREP(PLL_PRE_DIV, conf.pre_भाग);
		अगर (conf.rot_dir)
			val |= PLL_ROT_सूची;
	पूर्ण
	ग_लिखोl(val, pll->reg);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ s5_pll_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा s5_hw_clk *pll = to_s5_pll(hw);
	काष्ठा s5_pll_conf conf;
	u32 val;

	val = पढ़ोl(pll->reg);

	अगर (val & PLL_CLK_ENA) अणु
		conf.भाग     = FIELD_GET(PLL_DIV, val);
		conf.pre_भाग = FIELD_GET(PLL_PRE_DIV, val);
		conf.rot_ena = FIELD_GET(PLL_ROT_ENA, val);
		conf.rot_dir = FIELD_GET(PLL_ROT_सूची, val);
		conf.rot_sel = FIELD_GET(PLL_ROT_SEL, val);

		conf.freq = s5_calc_freq(parent_rate, &conf);
	पूर्ण अन्यथा अणु
		conf.freq = 0;
	पूर्ण

	वापस conf.freq;
पूर्ण

अटल दीर्घ s5_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा s5_pll_conf conf;

	वापस s5_calc_params(rate, *parent_rate, &conf);
पूर्ण

अटल स्थिर काष्ठा clk_ops s5_pll_ops = अणु
	.enable		= s5_pll_enable,
	.disable	= s5_pll_disable,
	.set_rate	= s5_pll_set_rate,
	.round_rate	= s5_pll_round_rate,
	.recalc_rate	= s5_pll_recalc_rate,
पूर्ण;

अटल काष्ठा clk_hw *s5_clk_hw_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा s5_clk_data *s5_clk = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= N_CLOCKS) अणु
		pr_err("%s: invalid index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस &s5_clk->s5_hw[idx].hw;
पूर्ण

अटल पूर्णांक s5_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i, ret;
	काष्ठा s5_clk_data *s5_clk;
	काष्ठा clk_parent_data pdata = अणु .index = 0 पूर्ण;
	काष्ठा clk_init_data init = अणु
		.ops = &s5_pll_ops,
		.num_parents = 1,
		.parent_data = &pdata,
	पूर्ण;

	s5_clk = devm_kzalloc(dev, माप(*s5_clk), GFP_KERNEL);
	अगर (!s5_clk)
		वापस -ENOMEM;

	s5_clk->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(s5_clk->base))
		वापस PTR_ERR(s5_clk->base);

	क्रम (i = 0; i < N_CLOCKS; i++) अणु
		काष्ठा s5_hw_clk *s5_hw = &s5_clk->s5_hw[i];

		init.name = clk_names[i];
		s5_hw->reg = s5_clk->base + (i * 4);
		s5_hw->hw.init = &init;
		ret = devm_clk_hw_रेजिस्टर(dev, &s5_hw->hw);
		अगर (ret) अणु
			dev_err(dev, "failed to register %s clock\n",
				init.name);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस devm_of_clk_add_hw_provider(dev, s5_clk_hw_get, s5_clk);
पूर्ण

अटल स्थिर काष्ठा of_device_id s5_clk_dt_ids[] = अणु
	अणु .compatible = "microchip,sparx5-dpll", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, s5_clk_dt_ids);

अटल काष्ठा platक्रमm_driver s5_clk_driver = अणु
	.probe  = s5_clk_probe,
	.driver = अणु
		.name = "sparx5-clk",
		.of_match_table = s5_clk_dt_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(s5_clk_driver);
