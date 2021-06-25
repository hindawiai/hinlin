<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017, Linaro Limited
 * Author: Georgi Djakov <georgi.djakov@linaro.org>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/regmap.h>

#समावेश "clk-regmap-mux-div.h"

#घोषणा CMD_RCGR			0x0
#घोषणा CMD_RCGR_UPDATE			BIT(0)
#घोषणा CMD_RCGR_सूचीTY_CFG		BIT(4)
#घोषणा CMD_RCGR_ROOT_OFF		BIT(31)
#घोषणा CFG_RCGR			0x4

#घोषणा to_clk_regmap_mux_भाग(_hw) \
	container_of(to_clk_regmap(_hw), काष्ठा clk_regmap_mux_भाग, clkr)

पूर्णांक mux_भाग_set_src_भाग(काष्ठा clk_regmap_mux_भाग *md, u32 src, u32 भाग)
अणु
	पूर्णांक ret, count;
	u32 val, mask;
	स्थिर अक्षर *name = clk_hw_get_name(&md->clkr.hw);

	val = (भाग << md->hid_shअगरt) | (src << md->src_shअगरt);
	mask = ((BIT(md->hid_width) - 1) << md->hid_shअगरt) |
	       ((BIT(md->src_width) - 1) << md->src_shअगरt);

	ret = regmap_update_bits(md->clkr.regmap, CFG_RCGR + md->reg_offset,
				 mask, val);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(md->clkr.regmap, CMD_RCGR + md->reg_offset,
				 CMD_RCGR_UPDATE, CMD_RCGR_UPDATE);
	अगर (ret)
		वापस ret;

	/* Wait क्रम update to take effect */
	क्रम (count = 500; count > 0; count--) अणु
		ret = regmap_पढ़ो(md->clkr.regmap, CMD_RCGR + md->reg_offset,
				  &val);
		अगर (ret)
			वापस ret;
		अगर (!(val & CMD_RCGR_UPDATE))
			वापस 0;
		udelay(1);
	पूर्ण

	pr_err("%s: RCG did not update its configuration", name);
	वापस -EBUSY;
पूर्ण
EXPORT_SYMBOL_GPL(mux_भाग_set_src_भाग);

अटल व्योम mux_भाग_get_src_भाग(काष्ठा clk_regmap_mux_भाग *md, u32 *src,
				u32 *भाग)
अणु
	u32 val, d, s;
	स्थिर अक्षर *name = clk_hw_get_name(&md->clkr.hw);

	regmap_पढ़ो(md->clkr.regmap, CMD_RCGR + md->reg_offset, &val);

	अगर (val & CMD_RCGR_सूचीTY_CFG) अणु
		pr_err("%s: RCG configuration is pending\n", name);
		वापस;
	पूर्ण

	regmap_पढ़ो(md->clkr.regmap, CFG_RCGR + md->reg_offset, &val);
	s = (val >> md->src_shअगरt);
	s &= BIT(md->src_width) - 1;
	*src = s;

	d = (val >> md->hid_shअगरt);
	d &= BIT(md->hid_width) - 1;
	*भाग = d;
पूर्ण

अटल अंतरभूत bool is_better_rate(अचिन्हित दीर्घ req, अचिन्हित दीर्घ best,
				  अचिन्हित दीर्घ new)
अणु
	वापस (req <= new && new < best) || (best < req && best < new);
पूर्ण

अटल पूर्णांक mux_भाग_determine_rate(काष्ठा clk_hw *hw,
				  काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_regmap_mux_भाग *md = to_clk_regmap_mux_भाग(hw);
	अचिन्हित पूर्णांक i, भाग, max_भाग;
	अचिन्हित दीर्घ actual_rate, best_rate = 0;
	अचिन्हित दीर्घ req_rate = req->rate;

	क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++) अणु
		काष्ठा clk_hw *parent = clk_hw_get_parent_by_index(hw, i);
		अचिन्हित दीर्घ parent_rate = clk_hw_get_rate(parent);

		max_भाग = BIT(md->hid_width) - 1;
		क्रम (भाग = 1; भाग < max_भाग; भाग++) अणु
			parent_rate = mult_frac(req_rate, भाग, 2);
			parent_rate = clk_hw_round_rate(parent, parent_rate);
			actual_rate = mult_frac(parent_rate, 2, भाग);

			अगर (is_better_rate(req_rate, best_rate, actual_rate)) अणु
				best_rate = actual_rate;
				req->rate = best_rate;
				req->best_parent_rate = parent_rate;
				req->best_parent_hw = parent;
			पूर्ण

			अगर (actual_rate < req_rate || best_rate <= req_rate)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (!best_rate)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __mux_भाग_set_rate_and_parent(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					 अचिन्हित दीर्घ prate, u32 src)
अणु
	काष्ठा clk_regmap_mux_भाग *md = to_clk_regmap_mux_भाग(hw);
	पूर्णांक ret;
	u32 भाग, max_भाग, best_src = 0, best_भाग = 0;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ actual_rate, best_rate = 0;

	क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++) अणु
		काष्ठा clk_hw *parent = clk_hw_get_parent_by_index(hw, i);
		अचिन्हित दीर्घ parent_rate = clk_hw_get_rate(parent);

		max_भाग = BIT(md->hid_width) - 1;
		क्रम (भाग = 1; भाग < max_भाग; भाग++) अणु
			parent_rate = mult_frac(rate, भाग, 2);
			parent_rate = clk_hw_round_rate(parent, parent_rate);
			actual_rate = mult_frac(parent_rate, 2, भाग);

			अगर (is_better_rate(rate, best_rate, actual_rate)) अणु
				best_rate = actual_rate;
				best_src = md->parent_map[i];
				best_भाग = भाग - 1;
			पूर्ण

			अगर (actual_rate < rate || best_rate <= rate)
				अवरोध;
		पूर्ण
	पूर्ण

	ret = mux_भाग_set_src_भाग(md, best_src, best_भाग);
	अगर (!ret) अणु
		md->भाग = best_भाग;
		md->src = best_src;
	पूर्ण

	वापस ret;
पूर्ण

अटल u8 mux_भाग_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap_mux_भाग *md = to_clk_regmap_mux_भाग(hw);
	स्थिर अक्षर *name = clk_hw_get_name(hw);
	u32 i, भाग, src = 0;

	mux_भाग_get_src_भाग(md, &src, &भाग);

	क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++)
		अगर (src == md->parent_map[i])
			वापस i;

	pr_err("%s: Can't find parent with src %d\n", name, src);
	वापस 0;
पूर्ण

अटल पूर्णांक mux_भाग_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_regmap_mux_भाग *md = to_clk_regmap_mux_भाग(hw);

	वापस mux_भाग_set_src_भाग(md, md->parent_map[index], md->भाग);
पूर्ण

अटल पूर्णांक mux_भाग_set_rate(काष्ठा clk_hw *hw,
			    अचिन्हित दीर्घ rate, अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_regmap_mux_भाग *md = to_clk_regmap_mux_भाग(hw);

	वापस __mux_भाग_set_rate_and_parent(hw, rate, prate, md->src);
पूर्ण

अटल पूर्णांक mux_भाग_set_rate_and_parent(काष्ठा clk_hw *hw,  अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ prate, u8 index)
अणु
	काष्ठा clk_regmap_mux_भाग *md = to_clk_regmap_mux_भाग(hw);

	वापस __mux_भाग_set_rate_and_parent(hw, rate, prate,
					     md->parent_map[index]);
पूर्ण

अटल अचिन्हित दीर्घ mux_भाग_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_regmap_mux_भाग *md = to_clk_regmap_mux_भाग(hw);
	u32 भाग, src;
	पूर्णांक i, num_parents = clk_hw_get_num_parents(hw);
	स्थिर अक्षर *name = clk_hw_get_name(hw);

	mux_भाग_get_src_भाग(md, &src, &भाग);
	क्रम (i = 0; i < num_parents; i++)
		अगर (src == md->parent_map[i]) अणु
			काष्ठा clk_hw *p = clk_hw_get_parent_by_index(hw, i);
			अचिन्हित दीर्घ parent_rate = clk_hw_get_rate(p);

			वापस mult_frac(parent_rate, 2, भाग + 1);
		पूर्ण

	pr_err("%s: Can't find parent %d\n", name, src);
	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops clk_regmap_mux_भाग_ops = अणु
	.get_parent = mux_भाग_get_parent,
	.set_parent = mux_भाग_set_parent,
	.set_rate = mux_भाग_set_rate,
	.set_rate_and_parent = mux_भाग_set_rate_and_parent,
	.determine_rate = mux_भाग_determine_rate,
	.recalc_rate = mux_भाग_recalc_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_regmap_mux_भाग_ops);
