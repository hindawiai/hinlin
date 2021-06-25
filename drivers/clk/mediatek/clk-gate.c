<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: James Liao <jamesjj.liao@mediatek.com>
 */

#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/clkdev.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

अटल पूर्णांक mtk_cg_bit_is_cleared(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_clk_gate *cg = to_mtk_clk_gate(hw);
	u32 val;

	regmap_पढ़ो(cg->regmap, cg->sta_ofs, &val);

	val &= BIT(cg->bit);

	वापस val == 0;
पूर्ण

अटल पूर्णांक mtk_cg_bit_is_set(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_clk_gate *cg = to_mtk_clk_gate(hw);
	u32 val;

	regmap_पढ़ो(cg->regmap, cg->sta_ofs, &val);

	val &= BIT(cg->bit);

	वापस val != 0;
पूर्ण

अटल व्योम mtk_cg_set_bit(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_clk_gate *cg = to_mtk_clk_gate(hw);

	regmap_ग_लिखो(cg->regmap, cg->set_ofs, BIT(cg->bit));
पूर्ण

अटल व्योम mtk_cg_clr_bit(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_clk_gate *cg = to_mtk_clk_gate(hw);

	regmap_ग_लिखो(cg->regmap, cg->clr_ofs, BIT(cg->bit));
पूर्ण

अटल व्योम mtk_cg_set_bit_no_setclr(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_clk_gate *cg = to_mtk_clk_gate(hw);
	u32 cgbit = BIT(cg->bit);

	regmap_update_bits(cg->regmap, cg->sta_ofs, cgbit, cgbit);
पूर्ण

अटल व्योम mtk_cg_clr_bit_no_setclr(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_clk_gate *cg = to_mtk_clk_gate(hw);
	u32 cgbit = BIT(cg->bit);

	regmap_update_bits(cg->regmap, cg->sta_ofs, cgbit, 0);
पूर्ण

अटल पूर्णांक mtk_cg_enable(काष्ठा clk_hw *hw)
अणु
	mtk_cg_clr_bit(hw);

	वापस 0;
पूर्ण

अटल व्योम mtk_cg_disable(काष्ठा clk_hw *hw)
अणु
	mtk_cg_set_bit(hw);
पूर्ण

अटल पूर्णांक mtk_cg_enable_inv(काष्ठा clk_hw *hw)
अणु
	mtk_cg_set_bit(hw);

	वापस 0;
पूर्ण

अटल व्योम mtk_cg_disable_inv(काष्ठा clk_hw *hw)
अणु
	mtk_cg_clr_bit(hw);
पूर्ण

अटल पूर्णांक mtk_cg_enable_no_setclr(काष्ठा clk_hw *hw)
अणु
	mtk_cg_clr_bit_no_setclr(hw);

	वापस 0;
पूर्ण

अटल व्योम mtk_cg_disable_no_setclr(काष्ठा clk_hw *hw)
अणु
	mtk_cg_set_bit_no_setclr(hw);
पूर्ण

अटल पूर्णांक mtk_cg_enable_inv_no_setclr(काष्ठा clk_hw *hw)
अणु
	mtk_cg_set_bit_no_setclr(hw);

	वापस 0;
पूर्ण

अटल व्योम mtk_cg_disable_inv_no_setclr(काष्ठा clk_hw *hw)
अणु
	mtk_cg_clr_bit_no_setclr(hw);
पूर्ण

स्थिर काष्ठा clk_ops mtk_clk_gate_ops_setclr = अणु
	.is_enabled	= mtk_cg_bit_is_cleared,
	.enable		= mtk_cg_enable,
	.disable	= mtk_cg_disable,
पूर्ण;

स्थिर काष्ठा clk_ops mtk_clk_gate_ops_setclr_inv = अणु
	.is_enabled	= mtk_cg_bit_is_set,
	.enable		= mtk_cg_enable_inv,
	.disable	= mtk_cg_disable_inv,
पूर्ण;

स्थिर काष्ठा clk_ops mtk_clk_gate_ops_no_setclr = अणु
	.is_enabled	= mtk_cg_bit_is_cleared,
	.enable		= mtk_cg_enable_no_setclr,
	.disable	= mtk_cg_disable_no_setclr,
पूर्ण;

स्थिर काष्ठा clk_ops mtk_clk_gate_ops_no_setclr_inv = अणु
	.is_enabled	= mtk_cg_bit_is_set,
	.enable		= mtk_cg_enable_inv_no_setclr,
	.disable	= mtk_cg_disable_inv_no_setclr,
पूर्ण;

काष्ठा clk *mtk_clk_रेजिस्टर_gate(
		स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name,
		काष्ठा regmap *regmap,
		पूर्णांक set_ofs,
		पूर्णांक clr_ofs,
		पूर्णांक sta_ofs,
		u8 bit,
		स्थिर काष्ठा clk_ops *ops,
		अचिन्हित दीर्घ flags,
		काष्ठा device *dev)
अणु
	काष्ठा mtk_clk_gate *cg;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init = अणुपूर्ण;

	cg = kzalloc(माप(*cg), GFP_KERNEL);
	अगर (!cg)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.flags = flags | CLK_SET_RATE_PARENT;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;
	init.ops = ops;

	cg->regmap = regmap;
	cg->set_ofs = set_ofs;
	cg->clr_ofs = clr_ofs;
	cg->sta_ofs = sta_ofs;
	cg->bit = bit;

	cg->hw.init = &init;

	clk = clk_रेजिस्टर(dev, &cg->hw);
	अगर (IS_ERR(clk))
		kमुक्त(cg);

	वापस clk;
पूर्ण
