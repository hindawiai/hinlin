<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>
 * Copyright (C) 2011 Riअक्षरd Zhao, Linaro <riअक्षरd.zhao@linaro.org>
 * Copyright (C) 2011-2012 Mike Turquette, Linaro Ltd <mturquette@linaro.org>
 *
 * Adjustable भागider घड़ी implementation
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/log2.h>

/*
 * DOC: basic adjustable भागider घड़ी that cannot gate
 *
 * Traits of this घड़ी:
 * prepare - clk_prepare only ensures that parents are prepared
 * enable - clk_enable only ensures that parents are enabled
 * rate - rate is adjustable.  clk->rate = उच्चमानing(parent->rate / भागisor)
 * parent - fixed parent.  No clk_set_parent support
 */

अटल अंतरभूत u32 clk_भाग_पढ़ोl(काष्ठा clk_भागider *भागider)
अणु
	अगर (भागider->flags & CLK_DIVIDER_BIG_ENDIAN)
		वापस ioपढ़ो32be(भागider->reg);

	वापस पढ़ोl(भागider->reg);
पूर्ण

अटल अंतरभूत व्योम clk_भाग_ग_लिखोl(काष्ठा clk_भागider *भागider, u32 val)
अणु
	अगर (भागider->flags & CLK_DIVIDER_BIG_ENDIAN)
		ioग_लिखो32be(val, भागider->reg);
	अन्यथा
		ग_लिखोl(val, भागider->reg);
पूर्ण

अटल अचिन्हित पूर्णांक _get_table_maxभाग(स्थिर काष्ठा clk_भाग_प्रकारable *table,
				      u8 width)
अणु
	अचिन्हित पूर्णांक maxभाग = 0, mask = clk_भाग_mask(width);
	स्थिर काष्ठा clk_भाग_प्रकारable *clkt;

	क्रम (clkt = table; clkt->भाग; clkt++)
		अगर (clkt->भाग > maxभाग && clkt->val <= mask)
			maxभाग = clkt->भाग;
	वापस maxभाग;
पूर्ण

अटल अचिन्हित पूर्णांक _get_table_minभाग(स्थिर काष्ठा clk_भाग_प्रकारable *table)
अणु
	अचिन्हित पूर्णांक minभाग = अच_पूर्णांक_उच्च;
	स्थिर काष्ठा clk_भाग_प्रकारable *clkt;

	क्रम (clkt = table; clkt->भाग; clkt++)
		अगर (clkt->भाग < minभाग)
			minभाग = clkt->भाग;
	वापस minभाग;
पूर्ण

अटल अचिन्हित पूर्णांक _get_maxभाग(स्थिर काष्ठा clk_भाग_प्रकारable *table, u8 width,
				अचिन्हित दीर्घ flags)
अणु
	अगर (flags & CLK_DIVIDER_ONE_BASED)
		वापस clk_भाग_mask(width);
	अगर (flags & CLK_DIVIDER_POWER_OF_TWO)
		वापस 1 << clk_भाग_mask(width);
	अगर (table)
		वापस _get_table_maxभाग(table, width);
	वापस clk_भाग_mask(width) + 1;
पूर्ण

अटल अचिन्हित पूर्णांक _get_table_भाग(स्थिर काष्ठा clk_भाग_प्रकारable *table,
							अचिन्हित पूर्णांक val)
अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *clkt;

	क्रम (clkt = table; clkt->भाग; clkt++)
		अगर (clkt->val == val)
			वापस clkt->भाग;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक _get_भाग(स्थिर काष्ठा clk_भाग_प्रकारable *table,
			     अचिन्हित पूर्णांक val, अचिन्हित दीर्घ flags, u8 width)
अणु
	अगर (flags & CLK_DIVIDER_ONE_BASED)
		वापस val;
	अगर (flags & CLK_DIVIDER_POWER_OF_TWO)
		वापस 1 << val;
	अगर (flags & CLK_DIVIDER_MAX_AT_ZERO)
		वापस val ? val : clk_भाग_mask(width) + 1;
	अगर (table)
		वापस _get_table_भाग(table, val);
	वापस val + 1;
पूर्ण

अटल अचिन्हित पूर्णांक _get_table_val(स्थिर काष्ठा clk_भाग_प्रकारable *table,
							अचिन्हित पूर्णांक भाग)
अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *clkt;

	क्रम (clkt = table; clkt->भाग; clkt++)
		अगर (clkt->भाग == भाग)
			वापस clkt->val;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक _get_val(स्थिर काष्ठा clk_भाग_प्रकारable *table,
			     अचिन्हित पूर्णांक भाग, अचिन्हित दीर्घ flags, u8 width)
अणु
	अगर (flags & CLK_DIVIDER_ONE_BASED)
		वापस भाग;
	अगर (flags & CLK_DIVIDER_POWER_OF_TWO)
		वापस __ffs(भाग);
	अगर (flags & CLK_DIVIDER_MAX_AT_ZERO)
		वापस (भाग == clk_भाग_mask(width) + 1) ? 0 : भाग;
	अगर (table)
		वापस  _get_table_val(table, भाग);
	वापस भाग - 1;
पूर्ण

अचिन्हित दीर्घ भागider_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate,
				  अचिन्हित पूर्णांक val,
				  स्थिर काष्ठा clk_भाग_प्रकारable *table,
				  अचिन्हित दीर्घ flags, अचिन्हित दीर्घ width)
अणु
	अचिन्हित पूर्णांक भाग;

	भाग = _get_भाग(table, val, flags, width);
	अगर (!भाग) अणु
		WARN(!(flags & CLK_DIVIDER_ALLOW_ZERO),
			"%s: Zero divisor and CLK_DIVIDER_ALLOW_ZERO not set\n",
			clk_hw_get_name(hw));
		वापस parent_rate;
	पूर्ण

	वापस DIV_ROUND_UP_ULL((u64)parent_rate, भाग);
पूर्ण
EXPORT_SYMBOL_GPL(भागider_recalc_rate);

अटल अचिन्हित दीर्घ clk_भागider_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_भागider *भागider = to_clk_भागider(hw);
	अचिन्हित पूर्णांक val;

	val = clk_भाग_पढ़ोl(भागider) >> भागider->shअगरt;
	val &= clk_भाग_mask(भागider->width);

	वापस भागider_recalc_rate(hw, parent_rate, val, भागider->table,
				   भागider->flags, भागider->width);
पूर्ण

अटल bool _is_valid_table_भाग(स्थिर काष्ठा clk_भाग_प्रकारable *table,
							 अचिन्हित पूर्णांक भाग)
अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *clkt;

	क्रम (clkt = table; clkt->भाग; clkt++)
		अगर (clkt->भाग == भाग)
			वापस true;
	वापस false;
पूर्ण

अटल bool _is_valid_भाग(स्थिर काष्ठा clk_भाग_प्रकारable *table, अचिन्हित पूर्णांक भाग,
			  अचिन्हित दीर्घ flags)
अणु
	अगर (flags & CLK_DIVIDER_POWER_OF_TWO)
		वापस is_घातer_of_2(भाग);
	अगर (table)
		वापस _is_valid_table_भाग(table, भाग);
	वापस true;
पूर्ण

अटल पूर्णांक _round_up_table(स्थिर काष्ठा clk_भाग_प्रकारable *table, पूर्णांक भाग)
अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *clkt;
	पूर्णांक up = पूर्णांक_उच्च;

	क्रम (clkt = table; clkt->भाग; clkt++) अणु
		अगर (clkt->भाग == भाग)
			वापस clkt->भाग;
		अन्यथा अगर (clkt->भाग < भाग)
			जारी;

		अगर ((clkt->भाग - भाग) < (up - भाग))
			up = clkt->भाग;
	पूर्ण

	वापस up;
पूर्ण

अटल पूर्णांक _round_करोwn_table(स्थिर काष्ठा clk_भाग_प्रकारable *table, पूर्णांक भाग)
अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *clkt;
	पूर्णांक करोwn = _get_table_minभाग(table);

	क्रम (clkt = table; clkt->भाग; clkt++) अणु
		अगर (clkt->भाग == भाग)
			वापस clkt->भाग;
		अन्यथा अगर (clkt->भाग > भाग)
			जारी;

		अगर ((भाग - clkt->भाग) < (भाग - करोwn))
			करोwn = clkt->भाग;
	पूर्ण

	वापस करोwn;
पूर्ण

अटल पूर्णांक _भाग_round_up(स्थिर काष्ठा clk_भाग_प्रकारable *table,
			 अचिन्हित दीर्घ parent_rate, अचिन्हित दीर्घ rate,
			 अचिन्हित दीर्घ flags)
अणु
	पूर्णांक भाग = DIV_ROUND_UP_ULL((u64)parent_rate, rate);

	अगर (flags & CLK_DIVIDER_POWER_OF_TWO)
		भाग = __roundup_घात_of_two(भाग);
	अगर (table)
		भाग = _round_up_table(table, भाग);

	वापस भाग;
पूर्ण

अटल पूर्णांक _भाग_round_बंदst(स्थिर काष्ठा clk_भाग_प्रकारable *table,
			      अचिन्हित दीर्घ parent_rate, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ flags)
अणु
	पूर्णांक up, करोwn;
	अचिन्हित दीर्घ up_rate, करोwn_rate;

	up = DIV_ROUND_UP_ULL((u64)parent_rate, rate);
	करोwn = parent_rate / rate;

	अगर (flags & CLK_DIVIDER_POWER_OF_TWO) अणु
		up = __roundup_घात_of_two(up);
		करोwn = __roundकरोwn_घात_of_two(करोwn);
	पूर्ण अन्यथा अगर (table) अणु
		up = _round_up_table(table, up);
		करोwn = _round_करोwn_table(table, करोwn);
	पूर्ण

	up_rate = DIV_ROUND_UP_ULL((u64)parent_rate, up);
	करोwn_rate = DIV_ROUND_UP_ULL((u64)parent_rate, करोwn);

	वापस (rate - up_rate) <= (करोwn_rate - rate) ? up : करोwn;
पूर्ण

अटल पूर्णांक _भाग_round(स्थिर काष्ठा clk_भाग_प्रकारable *table,
		      अचिन्हित दीर्घ parent_rate, अचिन्हित दीर्घ rate,
		      अचिन्हित दीर्घ flags)
अणु
	अगर (flags & CLK_DIVIDER_ROUND_CLOSEST)
		वापस _भाग_round_बंदst(table, parent_rate, rate, flags);

	वापस _भाग_round_up(table, parent_rate, rate, flags);
पूर्ण

अटल bool _is_best_भाग(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ now,
			 अचिन्हित दीर्घ best, अचिन्हित दीर्घ flags)
अणु
	अगर (flags & CLK_DIVIDER_ROUND_CLOSEST)
		वापस असल(rate - now) < असल(rate - best);

	वापस now <= rate && now > best;
पूर्ण

अटल पूर्णांक _next_भाग(स्थिर काष्ठा clk_भाग_प्रकारable *table, पूर्णांक भाग,
		     अचिन्हित दीर्घ flags)
अणु
	भाग++;

	अगर (flags & CLK_DIVIDER_POWER_OF_TWO)
		वापस __roundup_घात_of_two(भाग);
	अगर (table)
		वापस _round_up_table(table, भाग);

	वापस भाग;
पूर्ण

अटल पूर्णांक clk_भागider_bestभाग(काष्ठा clk_hw *hw, काष्ठा clk_hw *parent,
			       अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *best_parent_rate,
			       स्थिर काष्ठा clk_भाग_प्रकारable *table, u8 width,
			       अचिन्हित दीर्घ flags)
अणु
	पूर्णांक i, bestभाग = 0;
	अचिन्हित दीर्घ parent_rate, best = 0, now, maxभाग;
	अचिन्हित दीर्घ parent_rate_saved = *best_parent_rate;

	अगर (!rate)
		rate = 1;

	maxभाग = _get_maxभाग(table, width, flags);

	अगर (!(clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)) अणु
		parent_rate = *best_parent_rate;
		bestभाग = _भाग_round(table, parent_rate, rate, flags);
		bestभाग = bestभाग == 0 ? 1 : bestभाग;
		bestभाग = bestभाग > maxभाग ? maxभाग : bestभाग;
		वापस bestभाग;
	पूर्ण

	/*
	 * The maximum भागider we can use without overflowing
	 * अचिन्हित दीर्घ in rate * i below
	 */
	maxभाग = min(अच_दीर्घ_उच्च / rate, maxभाग);

	क्रम (i = _next_भाग(table, 0, flags); i <= maxभाग;
					     i = _next_भाग(table, i, flags)) अणु
		अगर (rate * i == parent_rate_saved) अणु
			/*
			 * It's the most ideal हाल अगर the requested rate can be
			 * भागided from parent घड़ी without needing to change
			 * parent rate, so वापस the भागider immediately.
			 */
			*best_parent_rate = parent_rate_saved;
			वापस i;
		पूर्ण
		parent_rate = clk_hw_round_rate(parent, rate * i);
		now = DIV_ROUND_UP_ULL((u64)parent_rate, i);
		अगर (_is_best_भाग(rate, now, best, flags)) अणु
			bestभाग = i;
			best = now;
			*best_parent_rate = parent_rate;
		पूर्ण
	पूर्ण

	अगर (!bestभाग) अणु
		bestभाग = _get_maxभाग(table, width, flags);
		*best_parent_rate = clk_hw_round_rate(parent, 1);
	पूर्ण

	वापस bestभाग;
पूर्ण

दीर्घ भागider_round_rate_parent(काष्ठा clk_hw *hw, काष्ठा clk_hw *parent,
			       अचिन्हित दीर्घ rate, अचिन्हित दीर्घ *prate,
			       स्थिर काष्ठा clk_भाग_प्रकारable *table,
			       u8 width, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक भाग;

	भाग = clk_भागider_bestभाग(hw, parent, rate, prate, table, width, flags);

	वापस DIV_ROUND_UP_ULL((u64)*prate, भाग);
पूर्ण
EXPORT_SYMBOL_GPL(भागider_round_rate_parent);

दीर्घ भागider_ro_round_rate_parent(काष्ठा clk_hw *hw, काष्ठा clk_hw *parent,
				  अचिन्हित दीर्घ rate, अचिन्हित दीर्घ *prate,
				  स्थिर काष्ठा clk_भाग_प्रकारable *table, u8 width,
				  अचिन्हित दीर्घ flags, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक भाग;

	भाग = _get_भाग(table, val, flags, width);

	/* Even a पढ़ो-only घड़ी can propagate a rate change */
	अगर (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT) अणु
		अगर (!parent)
			वापस -EINVAL;

		*prate = clk_hw_round_rate(parent, rate * भाग);
	पूर्ण

	वापस DIV_ROUND_UP_ULL((u64)*prate, भाग);
पूर्ण
EXPORT_SYMBOL_GPL(भागider_ro_round_rate_parent);


अटल दीर्घ clk_भागider_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_भागider *भागider = to_clk_भागider(hw);

	/* अगर पढ़ो only, just वापस current value */
	अगर (भागider->flags & CLK_DIVIDER_READ_ONLY) अणु
		u32 val;

		val = clk_भाग_पढ़ोl(भागider) >> भागider->shअगरt;
		val &= clk_भाग_mask(भागider->width);

		वापस भागider_ro_round_rate(hw, rate, prate, भागider->table,
					     भागider->width, भागider->flags,
					     val);
	पूर्ण

	वापस भागider_round_rate(hw, rate, prate, भागider->table,
				  भागider->width, भागider->flags);
पूर्ण

पूर्णांक भागider_get_val(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate,
		    स्थिर काष्ठा clk_भाग_प्रकारable *table, u8 width,
		    अचिन्हित दीर्घ flags)
अणु
	अचिन्हित पूर्णांक भाग, value;

	भाग = DIV_ROUND_UP_ULL((u64)parent_rate, rate);

	अगर (!_is_valid_भाग(table, भाग, flags))
		वापस -EINVAL;

	value = _get_val(table, भाग, flags, width);

	वापस min_t(अचिन्हित पूर्णांक, value, clk_भाग_mask(width));
पूर्ण
EXPORT_SYMBOL_GPL(भागider_get_val);

अटल पूर्णांक clk_भागider_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_भागider *भागider = to_clk_भागider(hw);
	पूर्णांक value;
	अचिन्हित दीर्घ flags = 0;
	u32 val;

	value = भागider_get_val(rate, parent_rate, भागider->table,
				भागider->width, भागider->flags);
	अगर (value < 0)
		वापस value;

	अगर (भागider->lock)
		spin_lock_irqsave(भागider->lock, flags);
	अन्यथा
		__acquire(भागider->lock);

	अगर (भागider->flags & CLK_DIVIDER_HIWORD_MASK) अणु
		val = clk_भाग_mask(भागider->width) << (भागider->shअगरt + 16);
	पूर्ण अन्यथा अणु
		val = clk_भाग_पढ़ोl(भागider);
		val &= ~(clk_भाग_mask(भागider->width) << भागider->shअगरt);
	पूर्ण
	val |= (u32)value << भागider->shअगरt;
	clk_भाग_ग_लिखोl(भागider, val);

	अगर (भागider->lock)
		spin_unlock_irqrestore(भागider->lock, flags);
	अन्यथा
		__release(भागider->lock);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops clk_भागider_ops = अणु
	.recalc_rate = clk_भागider_recalc_rate,
	.round_rate = clk_भागider_round_rate,
	.set_rate = clk_भागider_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_भागider_ops);

स्थिर काष्ठा clk_ops clk_भागider_ro_ops = अणु
	.recalc_rate = clk_भागider_recalc_rate,
	.round_rate = clk_भागider_round_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_भागider_ro_ops);

काष्ठा clk_hw *__clk_hw_रेजिस्टर_भागider(काष्ठा device *dev,
		काष्ठा device_node *np, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, स्थिर काष्ठा clk_hw *parent_hw,
		स्थिर काष्ठा clk_parent_data *parent_data, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 shअगरt, u8 width, u8 clk_भागider_flags,
		स्थिर काष्ठा clk_भाग_प्रकारable *table, spinlock_t *lock)
अणु
	काष्ठा clk_भागider *भाग;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init = अणुपूर्ण;
	पूर्णांक ret;

	अगर (clk_भागider_flags & CLK_DIVIDER_HIWORD_MASK) अणु
		अगर (width + shअगरt > 16) अणु
			pr_warn("divider value exceeds LOWORD field\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	/* allocate the भागider */
	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	अगर (clk_भागider_flags & CLK_DIVIDER_READ_ONLY)
		init.ops = &clk_भागider_ro_ops;
	अन्यथा
		init.ops = &clk_भागider_ops;
	init.flags = flags;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.parent_hws = parent_hw ? &parent_hw : शून्य;
	init.parent_data = parent_data;
	अगर (parent_name || parent_hw || parent_data)
		init.num_parents = 1;
	अन्यथा
		init.num_parents = 0;

	/* काष्ठा clk_भागider assignments */
	भाग->reg = reg;
	भाग->shअगरt = shअगरt;
	भाग->width = width;
	भाग->flags = clk_भागider_flags;
	भाग->lock = lock;
	भाग->hw.init = &init;
	भाग->table = table;

	/* रेजिस्टर the घड़ी */
	hw = &भाग->hw;
	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret) अणु
		kमुक्त(भाग);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
EXPORT_SYMBOL_GPL(__clk_hw_रेजिस्टर_भागider);

/**
 * clk_रेजिस्टर_भागider_table - रेजिस्टर a table based भागider घड़ी with
 * the घड़ी framework
 * @dev: device रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_name: name of घड़ी's parent
 * @flags: framework-specअगरic flags
 * @reg: रेजिस्टर address to adjust भागider
 * @shअगरt: number of bits to shअगरt the bitfield
 * @width: width of the bitfield
 * @clk_भागider_flags: भागider-specअगरic flags क्रम this घड़ी
 * @table: array of भागider/value pairs ending with a भाग set to 0
 * @lock: shared रेजिस्टर lock क्रम this घड़ी
 */
काष्ठा clk *clk_रेजिस्टर_भागider_table(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 shअगरt, u8 width,
		u8 clk_भागider_flags, स्थिर काष्ठा clk_भाग_प्रकारable *table,
		spinlock_t *lock)
अणु
	काष्ठा clk_hw *hw;

	hw =  __clk_hw_रेजिस्टर_भागider(dev, शून्य, name, parent_name, शून्य,
			शून्य, flags, reg, shअगरt, width, clk_भागider_flags,
			table, lock);
	अगर (IS_ERR(hw))
		वापस ERR_CAST(hw);
	वापस hw->clk;
पूर्ण
EXPORT_SYMBOL_GPL(clk_रेजिस्टर_भागider_table);

व्योम clk_unरेजिस्टर_भागider(काष्ठा clk *clk)
अणु
	काष्ठा clk_भागider *भाग;
	काष्ठा clk_hw *hw;

	hw = __clk_get_hw(clk);
	अगर (!hw)
		वापस;

	भाग = to_clk_भागider(hw);

	clk_unरेजिस्टर(clk);
	kमुक्त(भाग);
पूर्ण
EXPORT_SYMBOL_GPL(clk_unरेजिस्टर_भागider);

/**
 * clk_hw_unरेजिस्टर_भागider - unरेजिस्टर a clk भागider
 * @hw: hardware-specअगरic घड़ी data to unरेजिस्टर
 */
व्योम clk_hw_unरेजिस्टर_भागider(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_भागider *भाग;

	भाग = to_clk_भागider(hw);

	clk_hw_unरेजिस्टर(hw);
	kमुक्त(भाग);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_unरेजिस्टर_भागider);

अटल व्योम devm_clk_hw_release_भागider(काष्ठा device *dev, व्योम *res)
अणु
	clk_hw_unरेजिस्टर_भागider(*(काष्ठा clk_hw **)res);
पूर्ण

काष्ठा clk_hw *__devm_clk_hw_रेजिस्टर_भागider(काष्ठा device *dev,
		काष्ठा device_node *np, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, स्थिर काष्ठा clk_hw *parent_hw,
		स्थिर काष्ठा clk_parent_data *parent_data, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 shअगरt, u8 width, u8 clk_भागider_flags,
		स्थिर काष्ठा clk_भाग_प्रकारable *table, spinlock_t *lock)
अणु
	काष्ठा clk_hw **ptr, *hw;

	ptr = devres_alloc(devm_clk_hw_release_भागider, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	hw = __clk_hw_रेजिस्टर_भागider(dev, np, name, parent_name, parent_hw,
				       parent_data, flags, reg, shअगरt, width,
				       clk_भागider_flags, table, lock);

	अगर (!IS_ERR(hw)) अणु
		*ptr = hw;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस hw;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_clk_hw_रेजिस्टर_भागider);
