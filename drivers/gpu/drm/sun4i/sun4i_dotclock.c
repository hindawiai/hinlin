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

#समावेश "sun4i_tcon.h"
#समावेश "sun4i_dotclock.h"

काष्ठा sun4i_dclk अणु
	काष्ठा clk_hw		hw;
	काष्ठा regmap		*regmap;
	काष्ठा sun4i_tcon	*tcon;
पूर्ण;

अटल अंतरभूत काष्ठा sun4i_dclk *hw_to_dclk(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा sun4i_dclk, hw);
पूर्ण

अटल व्योम sun4i_dclk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sun4i_dclk *dclk = hw_to_dclk(hw);

	regmap_update_bits(dclk->regmap, SUN4I_TCON0_DCLK_REG,
			   BIT(SUN4I_TCON0_DCLK_GATE_BIT), 0);
पूर्ण

अटल पूर्णांक sun4i_dclk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा sun4i_dclk *dclk = hw_to_dclk(hw);

	वापस regmap_update_bits(dclk->regmap, SUN4I_TCON0_DCLK_REG,
				  BIT(SUN4I_TCON0_DCLK_GATE_BIT),
				  BIT(SUN4I_TCON0_DCLK_GATE_BIT));
पूर्ण

अटल पूर्णांक sun4i_dclk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा sun4i_dclk *dclk = hw_to_dclk(hw);
	u32 val;

	regmap_पढ़ो(dclk->regmap, SUN4I_TCON0_DCLK_REG, &val);

	वापस val & BIT(SUN4I_TCON0_DCLK_GATE_BIT);
पूर्ण

अटल अचिन्हित दीर्घ sun4i_dclk_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sun4i_dclk *dclk = hw_to_dclk(hw);
	u32 val;

	regmap_पढ़ो(dclk->regmap, SUN4I_TCON0_DCLK_REG, &val);

	val >>= SUN4I_TCON0_DCLK_DIV_SHIFT;
	val &= (1 << SUN4I_TCON0_DCLK_DIV_WIDTH) - 1;

	अगर (!val)
		val = 1;

	वापस parent_rate / val;
पूर्ण

अटल दीर्घ sun4i_dclk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा sun4i_dclk *dclk = hw_to_dclk(hw);
	काष्ठा sun4i_tcon *tcon = dclk->tcon;
	अचिन्हित दीर्घ best_parent = 0;
	u8 best_भाग = 1;
	पूर्णांक i;

	क्रम (i = tcon->dclk_min_भाग; i <= tcon->dclk_max_भाग; i++) अणु
		u64 ideal = (u64)rate * i;
		अचिन्हित दीर्घ rounded;

		/*
		 * ideal has overflowed the max value that can be stored in an
		 * अचिन्हित दीर्घ, and every clk operation we might करो on a
		 * truncated u64 value will give us incorrect results.
		 * Let's just stop there since bigger भागiders will result in
		 * the same overflow issue.
		 */
		अगर (ideal > अच_दीर्घ_उच्च)
			जाओ out;

		rounded = clk_hw_round_rate(clk_hw_get_parent(hw),
					    ideal);

		अगर (rounded == ideal) अणु
			best_parent = rounded;
			best_भाग = i;
			जाओ out;
		पूर्ण

		अगर (असल(rate - rounded / i) <
		    असल(rate - best_parent / best_भाग)) अणु
			best_parent = rounded;
			best_भाग = i;
		पूर्ण
	पूर्ण

out:
	*parent_rate = best_parent;

	वापस best_parent / best_भाग;
पूर्ण

अटल पूर्णांक sun4i_dclk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sun4i_dclk *dclk = hw_to_dclk(hw);
	u8 भाग = parent_rate / rate;

	वापस regmap_update_bits(dclk->regmap, SUN4I_TCON0_DCLK_REG,
				  GENMASK(6, 0), भाग);
पूर्ण

अटल पूर्णांक sun4i_dclk_get_phase(काष्ठा clk_hw *hw)
अणु
	काष्ठा sun4i_dclk *dclk = hw_to_dclk(hw);
	u32 val;

	regmap_पढ़ो(dclk->regmap, SUN4I_TCON0_IO_POL_REG, &val);

	val >>= 28;
	val &= 3;

	वापस val * 120;
पूर्ण

अटल पूर्णांक sun4i_dclk_set_phase(काष्ठा clk_hw *hw, पूर्णांक degrees)
अणु
	काष्ठा sun4i_dclk *dclk = hw_to_dclk(hw);
	u32 val = degrees / 120;

	val <<= 28;

	regmap_update_bits(dclk->regmap, SUN4I_TCON0_IO_POL_REG,
			   GENMASK(29, 28),
			   val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops sun4i_dclk_ops = अणु
	.disable	= sun4i_dclk_disable,
	.enable		= sun4i_dclk_enable,
	.is_enabled	= sun4i_dclk_is_enabled,

	.recalc_rate	= sun4i_dclk_recalc_rate,
	.round_rate	= sun4i_dclk_round_rate,
	.set_rate	= sun4i_dclk_set_rate,

	.get_phase	= sun4i_dclk_get_phase,
	.set_phase	= sun4i_dclk_set_phase,
पूर्ण;

पूर्णांक sun4i_dclk_create(काष्ठा device *dev, काष्ठा sun4i_tcon *tcon)
अणु
	स्थिर अक्षर *clk_name, *parent_name;
	काष्ठा clk_init_data init;
	काष्ठा sun4i_dclk *dclk;
	पूर्णांक ret;

	parent_name = __clk_get_name(tcon->sclk0);
	ret = of_property_पढ़ो_string_index(dev->of_node,
					    "clock-output-names", 0,
					    &clk_name);
	अगर (ret)
		वापस ret;

	dclk = devm_kzalloc(dev, माप(*dclk), GFP_KERNEL);
	अगर (!dclk)
		वापस -ENOMEM;
	dclk->tcon = tcon;

	init.name = clk_name;
	init.ops = &sun4i_dclk_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = CLK_SET_RATE_PARENT;

	dclk->regmap = tcon->regs;
	dclk->hw.init = &init;

	tcon->dclk = clk_रेजिस्टर(dev, &dclk->hw);
	अगर (IS_ERR(tcon->dclk))
		वापस PTR_ERR(tcon->dclk);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sun4i_dclk_create);

पूर्णांक sun4i_dclk_मुक्त(काष्ठा sun4i_tcon *tcon)
अणु
	clk_unरेजिस्टर(tcon->dclk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(sun4i_dclk_मुक्त);
