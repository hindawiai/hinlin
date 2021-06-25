<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/regmap.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश "clk.h"

काष्ठा rockchip_muxgrf_घड़ी अणु
	काष्ठा clk_hw		hw;
	काष्ठा regmap		*regmap;
	u32			reg;
	u32			shअगरt;
	u32			width;
	पूर्णांक			flags;
पूर्ण;

#घोषणा to_muxgrf_घड़ी(_hw) container_of(_hw, काष्ठा rockchip_muxgrf_घड़ी, hw)

अटल u8 rockchip_muxgrf_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_muxgrf_घड़ी *mux = to_muxgrf_घड़ी(hw);
	अचिन्हित पूर्णांक mask = GENMASK(mux->width - 1, 0);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(mux->regmap, mux->reg, &val);

	val >>= mux->shअगरt;
	val &= mask;

	वापस val;
पूर्ण

अटल पूर्णांक rockchip_muxgrf_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा rockchip_muxgrf_घड़ी *mux = to_muxgrf_घड़ी(hw);
	अचिन्हित पूर्णांक mask = GENMASK(mux->width + mux->shअगरt - 1, mux->shअगरt);
	अचिन्हित पूर्णांक val;

	val = index;
	val <<= mux->shअगरt;

	अगर (mux->flags & CLK_MUX_HIWORD_MASK)
		वापस regmap_ग_लिखो(mux->regmap, mux->reg, val | (mask << 16));
	अन्यथा
		वापस regmap_update_bits(mux->regmap, mux->reg, mask, val);
पूर्ण

अटल स्थिर काष्ठा clk_ops rockchip_muxgrf_clk_ops = अणु
	.get_parent = rockchip_muxgrf_get_parent,
	.set_parent = rockchip_muxgrf_set_parent,
	.determine_rate = __clk_mux_determine_rate,
पूर्ण;

काष्ठा clk *rockchip_clk_रेजिस्टर_muxgrf(स्थिर अक्षर *name,
				स्थिर अक्षर *स्थिर *parent_names, u8 num_parents,
				पूर्णांक flags, काष्ठा regmap *regmap, पूर्णांक reg,
				पूर्णांक shअगरt, पूर्णांक width, पूर्णांक mux_flags)
अणु
	काष्ठा rockchip_muxgrf_घड़ी *muxgrf_घड़ी;
	काष्ठा clk_init_data init;
	काष्ठा clk *clk;

	अगर (IS_ERR(regmap)) अणु
		pr_err("%s: regmap not available\n", __func__);
		वापस ERR_PTR(-ENOTSUPP);
	पूर्ण

	muxgrf_घड़ी = kदो_स्मृति(माप(*muxgrf_घड़ी), GFP_KERNEL);
	अगर (!muxgrf_घड़ी)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.flags = flags;
	init.num_parents = num_parents;
	init.parent_names = parent_names;
	init.ops = &rockchip_muxgrf_clk_ops;

	muxgrf_घड़ी->hw.init = &init;
	muxgrf_घड़ी->regmap = regmap;
	muxgrf_घड़ी->reg = reg;
	muxgrf_घड़ी->shअगरt = shअगरt;
	muxgrf_घड़ी->width = width;
	muxgrf_घड़ी->flags = mux_flags;

	clk = clk_रेजिस्टर(शून्य, &muxgrf_घड़ी->hw);
	अगर (IS_ERR(clk))
		kमुक्त(muxgrf_घड़ी);

	वापस clk;
पूर्ण
