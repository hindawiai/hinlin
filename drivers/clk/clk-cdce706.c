<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI CDCE706 programmable 3-PLL घड़ी synthesizer driver
 *
 * Copyright (c) 2014 Cadence Design Systems Inc.
 *
 * Reference: https://www.ti.com/lit/ds/symlink/cdce706.pdf
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/rational.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा CDCE706_CLKIN_CLOCK		10
#घोषणा CDCE706_CLKIN_SOURCE		11
#घोषणा CDCE706_PLL_M_LOW(pll)		(1 + 3 * (pll))
#घोषणा CDCE706_PLL_N_LOW(pll)		(2 + 3 * (pll))
#घोषणा CDCE706_PLL_HI(pll)		(3 + 3 * (pll))
#घोषणा CDCE706_PLL_MUX			3
#घोषणा CDCE706_PLL_FVCO		6
#घोषणा CDCE706_DIVIDER(भाग)		(13 + (भाग))
#घोषणा CDCE706_CLKOUT(out)		(19 + (out))

#घोषणा CDCE706_CLKIN_CLOCK_MASK	0x10
#घोषणा CDCE706_CLKIN_SOURCE_SHIFT	6
#घोषणा CDCE706_CLKIN_SOURCE_MASK	0xc0
#घोषणा CDCE706_CLKIN_SOURCE_LVCMOS	0x40

#घोषणा CDCE706_PLL_MUX_MASK(pll)	(0x80 >> (pll))
#घोषणा CDCE706_PLL_LOW_M_MASK		0xff
#घोषणा CDCE706_PLL_LOW_N_MASK		0xff
#घोषणा CDCE706_PLL_HI_M_MASK		0x1
#घोषणा CDCE706_PLL_HI_N_MASK		0x1e
#घोषणा CDCE706_PLL_HI_N_SHIFT		1
#घोषणा CDCE706_PLL_M_MAX		0x1ff
#घोषणा CDCE706_PLL_N_MAX		0xfff
#घोषणा CDCE706_PLL_FVCO_MASK(pll)	(0x80 >> (pll))
#घोषणा CDCE706_PLL_FREQ_MIN		 80000000
#घोषणा CDCE706_PLL_FREQ_MAX		300000000
#घोषणा CDCE706_PLL_FREQ_HI		180000000

#घोषणा CDCE706_DIVIDER_PLL(भाग)	(9 + (भाग) - ((भाग) > 2) - ((भाग) > 4))
#घोषणा CDCE706_DIVIDER_PLL_SHIFT(भाग)	((भाग) < 2 ? 5 : 3 * ((भाग) & 1))
#घोषणा CDCE706_DIVIDER_PLL_MASK(भाग)	(0x7 << CDCE706_DIVIDER_PLL_SHIFT(भाग))
#घोषणा CDCE706_DIVIDER_DIVIDER_MASK	0x7f
#घोषणा CDCE706_DIVIDER_DIVIDER_MAX	0x7f

#घोषणा CDCE706_CLKOUT_DIVIDER_MASK	0x7
#घोषणा CDCE706_CLKOUT_ENABLE_MASK	0x8

अटल स्थिर काष्ठा regmap_config cdce706_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.val_क्रमmat_endian = REGMAP_ENDIAN_NATIVE,
पूर्ण;

#घोषणा to_hw_data(phw) (container_of((phw), काष्ठा cdce706_hw_data, hw))

काष्ठा cdce706_hw_data अणु
	काष्ठा cdce706_dev_data *dev_data;
	अचिन्हित idx;
	अचिन्हित parent;
	काष्ठा clk_hw hw;
	अचिन्हित भाग;
	अचिन्हित mul;
	अचिन्हित mux;
पूर्ण;

काष्ठा cdce706_dev_data अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा clk *clkin_clk[2];
	स्थिर अक्षर *clkin_name[2];
	काष्ठा cdce706_hw_data clkin[1];
	काष्ठा cdce706_hw_data pll[3];
	काष्ठा cdce706_hw_data भागider[6];
	काष्ठा cdce706_hw_data clkout[6];
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdce706_source_name[] = अणु
	"clk_in0", "clk_in1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdce706_clkin_name[] = अणु
	"clk_in",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdce706_pll_name[] = अणु
	"pll1", "pll2", "pll3",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdce706_भागider_parent_name[] = अणु
	"clk_in", "pll1", "pll2", "pll2", "pll3",
पूर्ण;

अटल स्थिर अक्षर *cdce706_भागider_name[] = अणु
	"p0", "p1", "p2", "p3", "p4", "p5",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdce706_clkout_name[] = अणु
	"clk_out0", "clk_out1", "clk_out2", "clk_out3", "clk_out4", "clk_out5",
पूर्ण;

अटल पूर्णांक cdce706_reg_पढ़ो(काष्ठा cdce706_dev_data *dev_data, अचिन्हित reg,
			    अचिन्हित *val)
अणु
	पूर्णांक rc = regmap_पढ़ो(dev_data->regmap, reg | 0x80, val);

	अगर (rc < 0)
		dev_err(&dev_data->client->dev, "error reading reg %u", reg);
	वापस rc;
पूर्ण

अटल पूर्णांक cdce706_reg_ग_लिखो(काष्ठा cdce706_dev_data *dev_data, अचिन्हित reg,
			     अचिन्हित val)
अणु
	पूर्णांक rc = regmap_ग_लिखो(dev_data->regmap, reg | 0x80, val);

	अगर (rc < 0)
		dev_err(&dev_data->client->dev, "error writing reg %u", reg);
	वापस rc;
पूर्ण

अटल पूर्णांक cdce706_reg_update(काष्ठा cdce706_dev_data *dev_data, अचिन्हित reg,
			      अचिन्हित mask, अचिन्हित val)
अणु
	पूर्णांक rc = regmap_update_bits(dev_data->regmap, reg | 0x80, mask, val);

	अगर (rc < 0)
		dev_err(&dev_data->client->dev, "error updating reg %u", reg);
	वापस rc;
पूर्ण

अटल पूर्णांक cdce706_clkin_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा cdce706_hw_data *hwd = to_hw_data(hw);

	hwd->parent = index;
	वापस 0;
पूर्ण

अटल u8 cdce706_clkin_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा cdce706_hw_data *hwd = to_hw_data(hw);

	वापस hwd->parent;
पूर्ण

अटल स्थिर काष्ठा clk_ops cdce706_clkin_ops = अणु
	.set_parent = cdce706_clkin_set_parent,
	.get_parent = cdce706_clkin_get_parent,
पूर्ण;

अटल अचिन्हित दीर्घ cdce706_pll_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा cdce706_hw_data *hwd = to_hw_data(hw);

	dev_dbg(&hwd->dev_data->client->dev,
		"%s, pll: %d, mux: %d, mul: %u, div: %u\n",
		__func__, hwd->idx, hwd->mux, hwd->mul, hwd->भाग);

	अगर (!hwd->mux) अणु
		अगर (hwd->भाग && hwd->mul) अणु
			u64 res = (u64)parent_rate * hwd->mul;

			करो_भाग(res, hwd->भाग);
			वापस res;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hwd->भाग)
			वापस parent_rate / hwd->भाग;
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ cdce706_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा cdce706_hw_data *hwd = to_hw_data(hw);
	अचिन्हित दीर्घ mul, भाग;
	u64 res;

	dev_dbg(&hwd->dev_data->client->dev,
		"%s, rate: %lu, parent_rate: %lu\n",
		__func__, rate, *parent_rate);

	rational_best_approximation(rate, *parent_rate,
				    CDCE706_PLL_N_MAX, CDCE706_PLL_M_MAX,
				    &mul, &भाग);
	hwd->mul = mul;
	hwd->भाग = भाग;

	dev_dbg(&hwd->dev_data->client->dev,
		"%s, pll: %d, mul: %lu, div: %lu\n",
		__func__, hwd->idx, mul, भाग);

	res = (u64)*parent_rate * hwd->mul;
	करो_भाग(res, hwd->भाग);
	वापस res;
पूर्ण

अटल पूर्णांक cdce706_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा cdce706_hw_data *hwd = to_hw_data(hw);
	अचिन्हित दीर्घ mul = hwd->mul, भाग = hwd->भाग;
	पूर्णांक err;

	dev_dbg(&hwd->dev_data->client->dev,
		"%s, pll: %d, mul: %lu, div: %lu\n",
		__func__, hwd->idx, mul, भाग);

	err = cdce706_reg_update(hwd->dev_data,
				 CDCE706_PLL_HI(hwd->idx),
				 CDCE706_PLL_HI_M_MASK | CDCE706_PLL_HI_N_MASK,
				 ((भाग >> 8) & CDCE706_PLL_HI_M_MASK) |
				 ((mul >> (8 - CDCE706_PLL_HI_N_SHIFT)) &
				  CDCE706_PLL_HI_N_MASK));
	अगर (err < 0)
		वापस err;

	err = cdce706_reg_ग_लिखो(hwd->dev_data,
				CDCE706_PLL_M_LOW(hwd->idx),
				भाग & CDCE706_PLL_LOW_M_MASK);
	अगर (err < 0)
		वापस err;

	err = cdce706_reg_ग_लिखो(hwd->dev_data,
				CDCE706_PLL_N_LOW(hwd->idx),
				mul & CDCE706_PLL_LOW_N_MASK);
	अगर (err < 0)
		वापस err;

	err = cdce706_reg_update(hwd->dev_data,
				 CDCE706_PLL_FVCO,
				 CDCE706_PLL_FVCO_MASK(hwd->idx),
				 rate > CDCE706_PLL_FREQ_HI ?
				 CDCE706_PLL_FVCO_MASK(hwd->idx) : 0);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा clk_ops cdce706_pll_ops = अणु
	.recalc_rate = cdce706_pll_recalc_rate,
	.round_rate = cdce706_pll_round_rate,
	.set_rate = cdce706_pll_set_rate,
पूर्ण;

अटल पूर्णांक cdce706_भागider_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा cdce706_hw_data *hwd = to_hw_data(hw);

	अगर (hwd->parent == index)
		वापस 0;
	hwd->parent = index;
	वापस cdce706_reg_update(hwd->dev_data,
				  CDCE706_DIVIDER_PLL(hwd->idx),
				  CDCE706_DIVIDER_PLL_MASK(hwd->idx),
				  index << CDCE706_DIVIDER_PLL_SHIFT(hwd->idx));
पूर्ण

अटल u8 cdce706_भागider_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा cdce706_hw_data *hwd = to_hw_data(hw);

	वापस hwd->parent;
पूर्ण

अटल अचिन्हित दीर्घ cdce706_भागider_recalc_rate(काष्ठा clk_hw *hw,
						 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा cdce706_hw_data *hwd = to_hw_data(hw);

	dev_dbg(&hwd->dev_data->client->dev,
		"%s, divider: %d, div: %u\n",
		__func__, hwd->idx, hwd->भाग);
	अगर (hwd->भाग)
		वापस parent_rate / hwd->भाग;
	वापस 0;
पूर्ण

अटल दीर्घ cdce706_भागider_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा cdce706_hw_data *hwd = to_hw_data(hw);
	काष्ठा cdce706_dev_data *cdce = hwd->dev_data;
	अचिन्हित दीर्घ mul, भाग;

	dev_dbg(&hwd->dev_data->client->dev,
		"%s, rate: %lu, parent_rate: %lu\n",
		__func__, rate, *parent_rate);

	rational_best_approximation(rate, *parent_rate,
				    1, CDCE706_DIVIDER_DIVIDER_MAX,
				    &mul, &भाग);
	अगर (!mul)
		भाग = CDCE706_DIVIDER_DIVIDER_MAX;

	अगर (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT) अणु
		अचिन्हित दीर्घ best_dअगरf = rate;
		अचिन्हित दीर्घ best_भाग = 0;
		काष्ठा clk *gp_clk = cdce->clkin_clk[cdce->clkin[0].parent];
		अचिन्हित दीर्घ gp_rate = gp_clk ? clk_get_rate(gp_clk) : 0;

		क्रम (भाग = CDCE706_PLL_FREQ_MIN / rate; best_dअगरf &&
		     भाग <= CDCE706_PLL_FREQ_MAX / rate; ++भाग) अणु
			अचिन्हित दीर्घ n, m;
			अचिन्हित दीर्घ dअगरf;
			अचिन्हित दीर्घ भाग_rate;
			u64 भाग_rate64;

			अगर (rate * भाग < CDCE706_PLL_FREQ_MIN)
				जारी;

			rational_best_approximation(rate * भाग, gp_rate,
						    CDCE706_PLL_N_MAX,
						    CDCE706_PLL_M_MAX,
						    &n, &m);
			भाग_rate64 = (u64)gp_rate * n;
			करो_भाग(भाग_rate64, m);
			करो_भाग(भाग_rate64, भाग);
			भाग_rate = भाग_rate64;
			dअगरf = max(भाग_rate, rate) - min(भाग_rate, rate);

			अगर (dअगरf < best_dअगरf) अणु
				best_dअगरf = dअगरf;
				best_भाग = भाग;
				dev_dbg(&hwd->dev_data->client->dev,
					"%s, %lu * %lu / %lu / %lu = %lu\n",
					__func__, gp_rate, n, m, भाग, भाग_rate);
			पूर्ण
		पूर्ण

		भाग = best_भाग;

		dev_dbg(&hwd->dev_data->client->dev,
			"%s, altering parent rate: %lu -> %lu\n",
			__func__, *parent_rate, rate * भाग);
		*parent_rate = rate * भाग;
	पूर्ण
	hwd->भाग = भाग;

	dev_dbg(&hwd->dev_data->client->dev,
		"%s, divider: %d, div: %lu\n",
		__func__, hwd->idx, भाग);

	वापस *parent_rate / भाग;
पूर्ण

अटल पूर्णांक cdce706_भागider_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा cdce706_hw_data *hwd = to_hw_data(hw);

	dev_dbg(&hwd->dev_data->client->dev,
		"%s, divider: %d, div: %u\n",
		__func__, hwd->idx, hwd->भाग);

	वापस cdce706_reg_update(hwd->dev_data,
				  CDCE706_DIVIDER(hwd->idx),
				  CDCE706_DIVIDER_DIVIDER_MASK,
				  hwd->भाग);
पूर्ण

अटल स्थिर काष्ठा clk_ops cdce706_भागider_ops = अणु
	.set_parent = cdce706_भागider_set_parent,
	.get_parent = cdce706_भागider_get_parent,
	.recalc_rate = cdce706_भागider_recalc_rate,
	.round_rate = cdce706_भागider_round_rate,
	.set_rate = cdce706_भागider_set_rate,
पूर्ण;

अटल पूर्णांक cdce706_clkout_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा cdce706_hw_data *hwd = to_hw_data(hw);

	वापस cdce706_reg_update(hwd->dev_data, CDCE706_CLKOUT(hwd->idx),
				  CDCE706_CLKOUT_ENABLE_MASK,
				  CDCE706_CLKOUT_ENABLE_MASK);
पूर्ण

अटल व्योम cdce706_clkout_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा cdce706_hw_data *hwd = to_hw_data(hw);

	cdce706_reg_update(hwd->dev_data, CDCE706_CLKOUT(hwd->idx),
			   CDCE706_CLKOUT_ENABLE_MASK, 0);
पूर्ण

अटल पूर्णांक cdce706_clkout_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा cdce706_hw_data *hwd = to_hw_data(hw);

	अगर (hwd->parent == index)
		वापस 0;
	hwd->parent = index;
	वापस cdce706_reg_update(hwd->dev_data,
				  CDCE706_CLKOUT(hwd->idx),
				  CDCE706_CLKOUT_ENABLE_MASK, index);
पूर्ण

अटल u8 cdce706_clkout_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा cdce706_hw_data *hwd = to_hw_data(hw);

	वापस hwd->parent;
पूर्ण

अटल अचिन्हित दीर्घ cdce706_clkout_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	वापस parent_rate;
पूर्ण

अटल दीर्घ cdce706_clkout_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ *parent_rate)
अणु
	*parent_rate = rate;
	वापस rate;
पूर्ण

अटल पूर्णांक cdce706_clkout_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops cdce706_clkout_ops = अणु
	.prepare = cdce706_clkout_prepare,
	.unprepare = cdce706_clkout_unprepare,
	.set_parent = cdce706_clkout_set_parent,
	.get_parent = cdce706_clkout_get_parent,
	.recalc_rate = cdce706_clkout_recalc_rate,
	.round_rate = cdce706_clkout_round_rate,
	.set_rate = cdce706_clkout_set_rate,
पूर्ण;

अटल पूर्णांक cdce706_रेजिस्टर_hw(काष्ठा cdce706_dev_data *cdce,
			       काष्ठा cdce706_hw_data *hw, अचिन्हित num_hw,
			       स्थिर अक्षर * स्थिर *clk_names,
			       काष्ठा clk_init_data *init)
अणु
	अचिन्हित i;
	पूर्णांक ret;

	क्रम (i = 0; i < num_hw; ++i, ++hw) अणु
		init->name = clk_names[i];
		hw->dev_data = cdce;
		hw->idx = i;
		hw->hw.init = init;
		ret = devm_clk_hw_रेजिस्टर(&cdce->client->dev,
					    &hw->hw);
		अगर (ret) अणु
			dev_err(&cdce->client->dev, "Failed to register %s\n",
				clk_names[i]);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cdce706_रेजिस्टर_clkin(काष्ठा cdce706_dev_data *cdce)
अणु
	काष्ठा clk_init_data init = अणु
		.ops = &cdce706_clkin_ops,
		.parent_names = cdce->clkin_name,
		.num_parents = ARRAY_SIZE(cdce->clkin_name),
	पूर्ण;
	अचिन्हित i;
	पूर्णांक ret;
	अचिन्हित घड़ी, source;

	क्रम (i = 0; i < ARRAY_SIZE(cdce->clkin_name); ++i) अणु
		काष्ठा clk *parent = devm_clk_get(&cdce->client->dev,
						  cdce706_source_name[i]);

		अगर (IS_ERR(parent)) अणु
			cdce->clkin_name[i] = cdce706_source_name[i];
		पूर्ण अन्यथा अणु
			cdce->clkin_name[i] = __clk_get_name(parent);
			cdce->clkin_clk[i] = parent;
		पूर्ण
	पूर्ण

	ret = cdce706_reg_पढ़ो(cdce, CDCE706_CLKIN_SOURCE, &source);
	अगर (ret < 0)
		वापस ret;
	अगर ((source & CDCE706_CLKIN_SOURCE_MASK) ==
	    CDCE706_CLKIN_SOURCE_LVCMOS) अणु
		ret = cdce706_reg_पढ़ो(cdce, CDCE706_CLKIN_CLOCK, &घड़ी);
		अगर (ret < 0)
			वापस ret;
		cdce->clkin[0].parent = !!(घड़ी & CDCE706_CLKIN_CLOCK_MASK);
	पूर्ण

	ret = cdce706_रेजिस्टर_hw(cdce, cdce->clkin,
				  ARRAY_SIZE(cdce->clkin),
				  cdce706_clkin_name, &init);
	वापस ret;
पूर्ण

अटल पूर्णांक cdce706_रेजिस्टर_plls(काष्ठा cdce706_dev_data *cdce)
अणु
	काष्ठा clk_init_data init = अणु
		.ops = &cdce706_pll_ops,
		.parent_names = cdce706_clkin_name,
		.num_parents = ARRAY_SIZE(cdce706_clkin_name),
	पूर्ण;
	अचिन्हित i;
	पूर्णांक ret;
	अचिन्हित mux;

	ret = cdce706_reg_पढ़ो(cdce, CDCE706_PLL_MUX, &mux);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(cdce->pll); ++i) अणु
		अचिन्हित m, n, v;

		ret = cdce706_reg_पढ़ो(cdce, CDCE706_PLL_M_LOW(i), &m);
		अगर (ret < 0)
			वापस ret;
		ret = cdce706_reg_पढ़ो(cdce, CDCE706_PLL_N_LOW(i), &n);
		अगर (ret < 0)
			वापस ret;
		ret = cdce706_reg_पढ़ो(cdce, CDCE706_PLL_HI(i), &v);
		अगर (ret < 0)
			वापस ret;
		cdce->pll[i].भाग = m | ((v & CDCE706_PLL_HI_M_MASK) << 8);
		cdce->pll[i].mul = n | ((v & CDCE706_PLL_HI_N_MASK) <<
					(8 - CDCE706_PLL_HI_N_SHIFT));
		cdce->pll[i].mux = mux & CDCE706_PLL_MUX_MASK(i);
		dev_dbg(&cdce->client->dev,
			"%s: i: %u, div: %u, mul: %u, mux: %d\n", __func__, i,
			cdce->pll[i].भाग, cdce->pll[i].mul, cdce->pll[i].mux);
	पूर्ण

	ret = cdce706_रेजिस्टर_hw(cdce, cdce->pll,
				  ARRAY_SIZE(cdce->pll),
				  cdce706_pll_name, &init);
	वापस ret;
पूर्ण

अटल पूर्णांक cdce706_रेजिस्टर_भागiders(काष्ठा cdce706_dev_data *cdce)
अणु
	काष्ठा clk_init_data init = अणु
		.ops = &cdce706_भागider_ops,
		.parent_names = cdce706_भागider_parent_name,
		.num_parents = ARRAY_SIZE(cdce706_भागider_parent_name),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण;
	अचिन्हित i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(cdce->भागider); ++i) अणु
		अचिन्हित val;

		ret = cdce706_reg_पढ़ो(cdce, CDCE706_DIVIDER_PLL(i), &val);
		अगर (ret < 0)
			वापस ret;
		cdce->भागider[i].parent =
			(val & CDCE706_DIVIDER_PLL_MASK(i)) >>
			CDCE706_DIVIDER_PLL_SHIFT(i);

		ret = cdce706_reg_पढ़ो(cdce, CDCE706_DIVIDER(i), &val);
		अगर (ret < 0)
			वापस ret;
		cdce->भागider[i].भाग = val & CDCE706_DIVIDER_DIVIDER_MASK;
		dev_dbg(&cdce->client->dev,
			"%s: i: %u, parent: %u, div: %u\n", __func__, i,
			cdce->भागider[i].parent, cdce->भागider[i].भाग);
	पूर्ण

	ret = cdce706_रेजिस्टर_hw(cdce, cdce->भागider,
				  ARRAY_SIZE(cdce->भागider),
				  cdce706_भागider_name, &init);
	वापस ret;
पूर्ण

अटल पूर्णांक cdce706_रेजिस्टर_clkouts(काष्ठा cdce706_dev_data *cdce)
अणु
	काष्ठा clk_init_data init = अणु
		.ops = &cdce706_clkout_ops,
		.parent_names = cdce706_भागider_name,
		.num_parents = ARRAY_SIZE(cdce706_भागider_name),
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण;
	अचिन्हित i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(cdce->clkout); ++i) अणु
		अचिन्हित val;

		ret = cdce706_reg_पढ़ो(cdce, CDCE706_CLKOUT(i), &val);
		अगर (ret < 0)
			वापस ret;
		cdce->clkout[i].parent = val & CDCE706_CLKOUT_DIVIDER_MASK;
		dev_dbg(&cdce->client->dev,
			"%s: i: %u, parent: %u\n", __func__, i,
			cdce->clkout[i].parent);
	पूर्ण

	वापस cdce706_रेजिस्टर_hw(cdce, cdce->clkout,
				   ARRAY_SIZE(cdce->clkout),
				   cdce706_clkout_name, &init);
पूर्ण

अटल काष्ठा clk_hw *
of_clk_cdce_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा cdce706_dev_data *cdce = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= ARRAY_SIZE(cdce->clkout)) अणु
		pr_err("%s: invalid index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस &cdce->clkout[idx].hw;
पूर्ण

अटल पूर्णांक cdce706_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा cdce706_dev_data *cdce;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	cdce = devm_kzalloc(&client->dev, माप(*cdce), GFP_KERNEL);
	अगर (!cdce)
		वापस -ENOMEM;

	cdce->client = client;
	cdce->regmap = devm_regmap_init_i2c(client, &cdce706_regmap_config);
	अगर (IS_ERR(cdce->regmap)) अणु
		dev_err(&client->dev, "Failed to initialize regmap\n");
		वापस -EINVAL;
	पूर्ण

	i2c_set_clientdata(client, cdce);

	ret = cdce706_रेजिस्टर_clkin(cdce);
	अगर (ret < 0)
		वापस ret;
	ret = cdce706_रेजिस्टर_plls(cdce);
	अगर (ret < 0)
		वापस ret;
	ret = cdce706_रेजिस्टर_भागiders(cdce);
	अगर (ret < 0)
		वापस ret;
	ret = cdce706_रेजिस्टर_clkouts(cdce);
	अगर (ret < 0)
		वापस ret;
	वापस of_clk_add_hw_provider(client->dev.of_node, of_clk_cdce_get,
				      cdce);
पूर्ण

अटल पूर्णांक cdce706_हटाओ(काष्ठा i2c_client *client)
अणु
	of_clk_del_provider(client->dev.of_node);
	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id cdce706_dt_match[] = अणु
	अणु .compatible = "ti,cdce706" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cdce706_dt_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id cdce706_id[] = अणु
	अणु "cdce706", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cdce706_id);

अटल काष्ठा i2c_driver cdce706_i2c_driver = अणु
	.driver	= अणु
		.name	= "cdce706",
		.of_match_table = of_match_ptr(cdce706_dt_match),
	पूर्ण,
	.probe		= cdce706_probe,
	.हटाओ		= cdce706_हटाओ,
	.id_table	= cdce706_id,
पूर्ण;
module_i2c_driver(cdce706_i2c_driver);

MODULE_AUTHOR("Max Filippov <jcmvbkbc@gmail.com>");
MODULE_DESCRIPTION("TI CDCE 706 clock synthesizer driver");
MODULE_LICENSE("GPL");
