<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>
 * Copyright (C) 2011 Riअक्षरd Zhao, Linaro <riअक्षरd.zhao@linaro.org>
 * Copyright (C) 2011-2012 Mike Turquette, Linaro Ltd <mturquette@linaro.org>
 *
 * Simple multiplexer घड़ी implementation
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>

/*
 * DOC: basic adjustable multiplexer घड़ी that cannot gate
 *
 * Traits of this घड़ी:
 * prepare - clk_prepare only ensures that parents are prepared
 * enable - clk_enable only ensures that parents are enabled
 * rate - rate is only affected by parent चयनing.  No clk_set_rate support
 * parent - parent is adjustable through clk_set_parent
 */

अटल अंतरभूत u32 clk_mux_पढ़ोl(काष्ठा clk_mux *mux)
अणु
	अगर (mux->flags & CLK_MUX_BIG_ENDIAN)
		वापस ioपढ़ो32be(mux->reg);

	वापस पढ़ोl(mux->reg);
पूर्ण

अटल अंतरभूत व्योम clk_mux_ग_लिखोl(काष्ठा clk_mux *mux, u32 val)
अणु
	अगर (mux->flags & CLK_MUX_BIG_ENDIAN)
		ioग_लिखो32be(val, mux->reg);
	अन्यथा
		ग_लिखोl(val, mux->reg);
पूर्ण

पूर्णांक clk_mux_val_to_index(काष्ठा clk_hw *hw, u32 *table, अचिन्हित पूर्णांक flags,
			 अचिन्हित पूर्णांक val)
अणु
	पूर्णांक num_parents = clk_hw_get_num_parents(hw);

	अगर (table) अणु
		पूर्णांक i;

		क्रम (i = 0; i < num_parents; i++)
			अगर (table[i] == val)
				वापस i;
		वापस -EINVAL;
	पूर्ण

	अगर (val && (flags & CLK_MUX_INDEX_BIT))
		val = ffs(val) - 1;

	अगर (val && (flags & CLK_MUX_INDEX_ONE))
		val--;

	अगर (val >= num_parents)
		वापस -EINVAL;

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(clk_mux_val_to_index);

अचिन्हित पूर्णांक clk_mux_index_to_val(u32 *table, अचिन्हित पूर्णांक flags, u8 index)
अणु
	अचिन्हित पूर्णांक val = index;

	अगर (table) अणु
		val = table[index];
	पूर्ण अन्यथा अणु
		अगर (flags & CLK_MUX_INDEX_BIT)
			val = 1 << index;

		अगर (flags & CLK_MUX_INDEX_ONE)
			val++;
	पूर्ण

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(clk_mux_index_to_val);

अटल u8 clk_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_mux *mux = to_clk_mux(hw);
	u32 val;

	val = clk_mux_पढ़ोl(mux) >> mux->shअगरt;
	val &= mux->mask;

	वापस clk_mux_val_to_index(hw, mux->table, mux->flags, val);
पूर्ण

अटल पूर्णांक clk_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_mux *mux = to_clk_mux(hw);
	u32 val = clk_mux_index_to_val(mux->table, mux->flags, index);
	अचिन्हित दीर्घ flags = 0;
	u32 reg;

	अगर (mux->lock)
		spin_lock_irqsave(mux->lock, flags);
	अन्यथा
		__acquire(mux->lock);

	अगर (mux->flags & CLK_MUX_HIWORD_MASK) अणु
		reg = mux->mask << (mux->shअगरt + 16);
	पूर्ण अन्यथा अणु
		reg = clk_mux_पढ़ोl(mux);
		reg &= ~(mux->mask << mux->shअगरt);
	पूर्ण
	val = val << mux->shअगरt;
	reg |= val;
	clk_mux_ग_लिखोl(mux, reg);

	अगर (mux->lock)
		spin_unlock_irqrestore(mux->lock, flags);
	अन्यथा
		__release(mux->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_mux_determine_rate(काष्ठा clk_hw *hw,
				  काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_mux *mux = to_clk_mux(hw);

	वापस clk_mux_determine_rate_flags(hw, req, mux->flags);
पूर्ण

स्थिर काष्ठा clk_ops clk_mux_ops = अणु
	.get_parent = clk_mux_get_parent,
	.set_parent = clk_mux_set_parent,
	.determine_rate = clk_mux_determine_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_mux_ops);

स्थिर काष्ठा clk_ops clk_mux_ro_ops = अणु
	.get_parent = clk_mux_get_parent,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_mux_ro_ops);

काष्ठा clk_hw *__clk_hw_रेजिस्टर_mux(काष्ठा device *dev, काष्ठा device_node *np,
		स्थिर अक्षर *name, u8 num_parents,
		स्थिर अक्षर * स्थिर *parent_names,
		स्थिर काष्ठा clk_hw **parent_hws,
		स्थिर काष्ठा clk_parent_data *parent_data,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg, u8 shअगरt, u32 mask,
		u8 clk_mux_flags, u32 *table, spinlock_t *lock)
अणु
	काष्ठा clk_mux *mux;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init = अणुपूर्ण;
	u8 width = 0;
	पूर्णांक ret = -EINVAL;

	अगर (clk_mux_flags & CLK_MUX_HIWORD_MASK) अणु
		width = fls(mask) - ffs(mask) + 1;
		अगर (width + shअगरt > 16) अणु
			pr_err("mux value exceeds LOWORD field\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	/* allocate the mux */
	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	अगर (clk_mux_flags & CLK_MUX_READ_ONLY)
		init.ops = &clk_mux_ro_ops;
	अन्यथा
		init.ops = &clk_mux_ops;
	init.flags = flags;
	init.parent_names = parent_names;
	init.parent_data = parent_data;
	init.parent_hws = parent_hws;
	init.num_parents = num_parents;

	/* काष्ठा clk_mux assignments */
	mux->reg = reg;
	mux->shअगरt = shअगरt;
	mux->mask = mask;
	mux->flags = clk_mux_flags;
	mux->lock = lock;
	mux->table = table;
	mux->hw.init = &init;

	hw = &mux->hw;
	अगर (dev || !np)
		ret = clk_hw_रेजिस्टर(dev, hw);
	अन्यथा अगर (np)
		ret = of_clk_hw_रेजिस्टर(np, hw);
	अगर (ret) अणु
		kमुक्त(mux);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
EXPORT_SYMBOL_GPL(__clk_hw_रेजिस्टर_mux);

अटल व्योम devm_clk_hw_release_mux(काष्ठा device *dev, व्योम *res)
अणु
	clk_hw_unरेजिस्टर_mux(*(काष्ठा clk_hw **)res);
पूर्ण

काष्ठा clk_hw *__devm_clk_hw_रेजिस्टर_mux(काष्ठा device *dev, काष्ठा device_node *np,
		स्थिर अक्षर *name, u8 num_parents,
		स्थिर अक्षर * स्थिर *parent_names,
		स्थिर काष्ठा clk_hw **parent_hws,
		स्थिर काष्ठा clk_parent_data *parent_data,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg, u8 shअगरt, u32 mask,
		u8 clk_mux_flags, u32 *table, spinlock_t *lock)
अणु
	काष्ठा clk_hw **ptr, *hw;

	ptr = devres_alloc(devm_clk_hw_release_mux, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	hw = __clk_hw_रेजिस्टर_mux(dev, np, name, num_parents, parent_names, parent_hws,
				       parent_data, flags, reg, shअगरt, mask,
				       clk_mux_flags, table, lock);

	अगर (!IS_ERR(hw)) अणु
		*ptr = hw;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस hw;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_clk_hw_रेजिस्टर_mux);

काष्ठा clk *clk_रेजिस्टर_mux_table(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर * स्थिर *parent_names, u8 num_parents,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg, u8 shअगरt, u32 mask,
		u8 clk_mux_flags, u32 *table, spinlock_t *lock)
अणु
	काष्ठा clk_hw *hw;

	hw = clk_hw_रेजिस्टर_mux_table(dev, name, parent_names,
				       num_parents, flags, reg, shअगरt, mask,
				       clk_mux_flags, table, lock);
	अगर (IS_ERR(hw))
		वापस ERR_CAST(hw);
	वापस hw->clk;
पूर्ण
EXPORT_SYMBOL_GPL(clk_रेजिस्टर_mux_table);

व्योम clk_unरेजिस्टर_mux(काष्ठा clk *clk)
अणु
	काष्ठा clk_mux *mux;
	काष्ठा clk_hw *hw;

	hw = __clk_get_hw(clk);
	अगर (!hw)
		वापस;

	mux = to_clk_mux(hw);

	clk_unरेजिस्टर(clk);
	kमुक्त(mux);
पूर्ण
EXPORT_SYMBOL_GPL(clk_unरेजिस्टर_mux);

व्योम clk_hw_unरेजिस्टर_mux(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_mux *mux;

	mux = to_clk_mux(hw);

	clk_hw_unरेजिस्टर(hw);
	kमुक्त(mux);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_unरेजिस्टर_mux);
