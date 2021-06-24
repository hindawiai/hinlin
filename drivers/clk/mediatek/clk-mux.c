<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 MediaTek Inc.
 * Author: Owen Chen <owen.chen@mediatek.com>
 */

#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/syscon.h>

#समावेश "clk-mtk.h"
#समावेश "clk-mux.h"

अटल अंतरभूत काष्ठा mtk_clk_mux *to_mtk_clk_mux(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा mtk_clk_mux, hw);
पूर्ण

अटल पूर्णांक mtk_clk_mux_enable_setclr(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_clk_mux *mux = to_mtk_clk_mux(hw);
	अचिन्हित दीर्घ flags = 0;

	अगर (mux->lock)
		spin_lock_irqsave(mux->lock, flags);
	अन्यथा
		__acquire(mux->lock);

	regmap_ग_लिखो(mux->regmap, mux->data->clr_ofs,
		     BIT(mux->data->gate_shअगरt));

	/*
	 * If the parent has been changed when the घड़ी was disabled, it will
	 * not be effective yet. Set the update bit to ensure the mux माला_लो
	 * updated.
	 */
	अगर (mux->reparent && mux->data->upd_shअगरt >= 0) अणु
		regmap_ग_लिखो(mux->regmap, mux->data->upd_ofs,
			     BIT(mux->data->upd_shअगरt));
		mux->reparent = false;
	पूर्ण

	अगर (mux->lock)
		spin_unlock_irqrestore(mux->lock, flags);
	अन्यथा
		__release(mux->lock);

	वापस 0;
पूर्ण

अटल व्योम mtk_clk_mux_disable_setclr(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_clk_mux *mux = to_mtk_clk_mux(hw);

	regmap_ग_लिखो(mux->regmap, mux->data->set_ofs,
			BIT(mux->data->gate_shअगरt));
पूर्ण

अटल पूर्णांक mtk_clk_mux_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_clk_mux *mux = to_mtk_clk_mux(hw);
	u32 val;

	regmap_पढ़ो(mux->regmap, mux->data->mux_ofs, &val);

	वापस (val & BIT(mux->data->gate_shअगरt)) == 0;
पूर्ण

अटल u8 mtk_clk_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_clk_mux *mux = to_mtk_clk_mux(hw);
	u32 mask = GENMASK(mux->data->mux_width - 1, 0);
	u32 val;

	regmap_पढ़ो(mux->regmap, mux->data->mux_ofs, &val);
	val = (val >> mux->data->mux_shअगरt) & mask;

	वापस val;
पूर्ण

अटल पूर्णांक mtk_clk_mux_set_parent_setclr_lock(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा mtk_clk_mux *mux = to_mtk_clk_mux(hw);
	u32 mask = GENMASK(mux->data->mux_width - 1, 0);
	u32 val, orig;
	अचिन्हित दीर्घ flags = 0;

	अगर (mux->lock)
		spin_lock_irqsave(mux->lock, flags);
	अन्यथा
		__acquire(mux->lock);

	regmap_पढ़ो(mux->regmap, mux->data->mux_ofs, &orig);
	val = (orig & ~(mask << mux->data->mux_shअगरt))
			| (index << mux->data->mux_shअगरt);

	अगर (val != orig) अणु
		regmap_ग_लिखो(mux->regmap, mux->data->clr_ofs,
				mask << mux->data->mux_shअगरt);
		regmap_ग_लिखो(mux->regmap, mux->data->set_ofs,
				index << mux->data->mux_shअगरt);

		अगर (mux->data->upd_shअगरt >= 0) अणु
			regmap_ग_लिखो(mux->regmap, mux->data->upd_ofs,
					BIT(mux->data->upd_shअगरt));
			mux->reparent = true;
		पूर्ण
	पूर्ण

	अगर (mux->lock)
		spin_unlock_irqrestore(mux->lock, flags);
	अन्यथा
		__release(mux->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops mtk_mux_ops = अणु
	.enable = mtk_clk_mux_enable_setclr,
	.disable = mtk_clk_mux_disable_setclr,
	.is_enabled = mtk_clk_mux_is_enabled,
	.get_parent = mtk_clk_mux_get_parent,
	.set_parent = mtk_clk_mux_set_parent_setclr_lock,
पूर्ण;

अटल काष्ठा clk *mtk_clk_रेजिस्टर_mux(स्थिर काष्ठा mtk_mux *mux,
				 काष्ठा regmap *regmap,
				 spinlock_t *lock)
अणु
	काष्ठा mtk_clk_mux *clk_mux;
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा clk *clk;

	clk_mux = kzalloc(माप(*clk_mux), GFP_KERNEL);
	अगर (!clk_mux)
		वापस ERR_PTR(-ENOMEM);

	init.name = mux->name;
	init.flags = mux->flags | CLK_SET_RATE_PARENT;
	init.parent_names = mux->parent_names;
	init.num_parents = mux->num_parents;
	init.ops = &mtk_mux_ops;

	clk_mux->regmap = regmap;
	clk_mux->data = mux;
	clk_mux->lock = lock;
	clk_mux->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &clk_mux->hw);
	अगर (IS_ERR(clk)) अणु
		kमुक्त(clk_mux);
		वापस clk;
	पूर्ण

	वापस clk;
पूर्ण

पूर्णांक mtk_clk_रेजिस्टर_muxes(स्थिर काष्ठा mtk_mux *muxes,
			   पूर्णांक num, काष्ठा device_node *node,
			   spinlock_t *lock,
			   काष्ठा clk_onecell_data *clk_data)
अणु
	काष्ठा regmap *regmap;
	काष्ठा clk *clk;
	पूर्णांक i;

	regmap = syscon_node_to_regmap(node);
	अगर (IS_ERR(regmap)) अणु
		pr_err("Cannot find regmap for %pOF: %ld\n", node,
		       PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		स्थिर काष्ठा mtk_mux *mux = &muxes[i];

		अगर (IS_ERR_OR_शून्य(clk_data->clks[mux->id])) अणु
			clk = mtk_clk_रेजिस्टर_mux(mux, regmap, lock);

			अगर (IS_ERR(clk)) अणु
				pr_err("Failed to register clk %s: %ld\n",
				       mux->name, PTR_ERR(clk));
				जारी;
			पूर्ण

			clk_data->clks[mux->id] = clk;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
