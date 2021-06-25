<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2018 Microchip Technology Inc,
 *                     Codrin Ciubotariu <codrin.ciubotariu@microchip.com>
 *
 *
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <soc/at91/aपंचांगel-sfr.h>

#समावेश "pmc.h"

काष्ठा clk_i2s_mux अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u8 bus_id;
पूर्ण;

#घोषणा to_clk_i2s_mux(hw) container_of(hw, काष्ठा clk_i2s_mux, hw)

अटल u8 clk_i2s_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_i2s_mux *mux = to_clk_i2s_mux(hw);
	u32 val;

	regmap_पढ़ो(mux->regmap, AT91_SFR_I2SCLKSEL, &val);

	वापस (val & BIT(mux->bus_id)) >> mux->bus_id;
पूर्ण

अटल पूर्णांक clk_i2s_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_i2s_mux *mux = to_clk_i2s_mux(hw);

	वापस regmap_update_bits(mux->regmap, AT91_SFR_I2SCLKSEL,
				  BIT(mux->bus_id), index << mux->bus_id);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_i2s_mux_ops = अणु
	.get_parent = clk_i2s_mux_get_parent,
	.set_parent = clk_i2s_mux_set_parent,
	.determine_rate = __clk_mux_determine_rate,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_i2s_mux_रेजिस्टर(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			  स्थिर अक्षर * स्थिर *parent_names,
			  अचिन्हित पूर्णांक num_parents, u8 bus_id)
अणु
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा clk_i2s_mux *i2s_ck;
	पूर्णांक ret;

	i2s_ck = kzalloc(माप(*i2s_ck), GFP_KERNEL);
	अगर (!i2s_ck)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_i2s_mux_ops;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	i2s_ck->hw.init = &init;
	i2s_ck->bus_id = bus_id;
	i2s_ck->regmap = regmap;

	ret = clk_hw_रेजिस्टर(शून्य, &i2s_ck->hw);
	अगर (ret) अणु
		kमुक्त(i2s_ck);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस &i2s_ck->hw;
पूर्ण
