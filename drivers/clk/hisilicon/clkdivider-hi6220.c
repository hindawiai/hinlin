<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hisilicon hi6220 SoC भागider घड़ी driver
 *
 * Copyright (c) 2015 Hisilicon Limited.
 *
 * Author: Bपूर्णांकian Wang <bपूर्णांकian.wang@huawei.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/spinlock.h>

#समावेश "clk.h"

#घोषणा भाग_mask(width)	((1 << (width)) - 1)

/**
 * काष्ठा hi6220_clk_भागider - भागider घड़ी क्रम hi6220
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @reg:	रेजिस्टर containing भागider
 * @shअगरt:	shअगरt to the भागider bit field
 * @width:	width of the भागider bit field
 * @mask:	mask क्रम setting भागider rate
 * @table:	the भाग table that the भागider supports
 * @lock:	रेजिस्टर lock
 */
काष्ठा hi6220_clk_भागider अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	u8		shअगरt;
	u8		width;
	u32		mask;
	स्थिर काष्ठा clk_भाग_प्रकारable *table;
	spinlock_t	*lock;
पूर्ण;

#घोषणा to_hi6220_clk_भागider(_hw)	\
	container_of(_hw, काष्ठा hi6220_clk_भागider, hw)

अटल अचिन्हित दीर्घ hi6220_clkभाग_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा hi6220_clk_भागider *dclk = to_hi6220_clk_भागider(hw);

	val = पढ़ोl_relaxed(dclk->reg) >> dclk->shअगरt;
	val &= भाग_mask(dclk->width);

	वापस भागider_recalc_rate(hw, parent_rate, val, dclk->table,
				   CLK_DIVIDER_ROUND_CLOSEST, dclk->width);
पूर्ण

अटल दीर्घ hi6220_clkभाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ *prate)
अणु
	काष्ठा hi6220_clk_भागider *dclk = to_hi6220_clk_भागider(hw);

	वापस भागider_round_rate(hw, rate, prate, dclk->table,
				  dclk->width, CLK_DIVIDER_ROUND_CLOSEST);
पूर्ण

अटल पूर्णांक hi6220_clkभाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक value;
	अचिन्हित दीर्घ flags = 0;
	u32 data;
	काष्ठा hi6220_clk_भागider *dclk = to_hi6220_clk_भागider(hw);

	value = भागider_get_val(rate, parent_rate, dclk->table,
				dclk->width, CLK_DIVIDER_ROUND_CLOSEST);

	अगर (dclk->lock)
		spin_lock_irqsave(dclk->lock, flags);

	data = पढ़ोl_relaxed(dclk->reg);
	data &= ~(भाग_mask(dclk->width) << dclk->shअगरt);
	data |= value << dclk->shअगरt;
	data |= dclk->mask;

	ग_लिखोl_relaxed(data, dclk->reg);

	अगर (dclk->lock)
		spin_unlock_irqrestore(dclk->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops hi6220_clkभाग_ops = अणु
	.recalc_rate = hi6220_clkभाग_recalc_rate,
	.round_rate = hi6220_clkभाग_round_rate,
	.set_rate = hi6220_clkभाग_set_rate,
पूर्ण;

काष्ठा clk *hi6220_रेजिस्टर_clkभाग(काष्ठा device *dev, स्थिर अक्षर *name,
	स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags, व्योम __iomem *reg,
	u8 shअगरt, u8 width, u32 mask_bit, spinlock_t *lock)
अणु
	काष्ठा hi6220_clk_भागider *भाग;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;
	काष्ठा clk_भाग_प्रकारable *table;
	u32 max_भाग, min_भाग;
	पूर्णांक i;

	/* allocate the भागider */
	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस ERR_PTR(-ENOMEM);

	/* Init the भागider table */
	max_भाग = भाग_mask(width) + 1;
	min_भाग = 1;

	table = kसुस्मृति(max_भाग + 1, माप(*table), GFP_KERNEL);
	अगर (!table) अणु
		kमुक्त(भाग);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	क्रम (i = 0; i < max_भाग; i++) अणु
		table[i].भाग = min_भाग + i;
		table[i].val = table[i].भाग - 1;
	पूर्ण

	init.name = name;
	init.ops = &hi6220_clkभाग_ops;
	init.flags = flags;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;

	/* काष्ठा hi6220_clk_भागider assignments */
	भाग->reg = reg;
	भाग->shअगरt = shअगरt;
	भाग->width = width;
	भाग->mask = mask_bit ? BIT(mask_bit) : 0;
	भाग->lock = lock;
	भाग->hw.init = &init;
	भाग->table = table;

	/* रेजिस्टर the घड़ी */
	clk = clk_रेजिस्टर(dev, &भाग->hw);
	अगर (IS_ERR(clk)) अणु
		kमुक्त(table);
		kमुक्त(भाग);
	पूर्ण

	वापस clk;
पूर्ण
