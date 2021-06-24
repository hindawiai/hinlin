<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hisilicon घड़ी separated gate driver
 *
 * Copyright (c) 2012-2013 Hisilicon Limited.
 * Copyright (c) 2012-2013 Linaro Limited.
 *
 * Author: Haojian Zhuang <haojian.zhuang@linaro.org>
 *	   Xin Li <li.xin@linaro.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश "clk.h"

/* घड़ी separated gate रेजिस्टर offset */
#घोषणा CLKGATE_SEPERATED_ENABLE		0x0
#घोषणा CLKGATE_SEPERATED_DISABLE		0x4
#घोषणा CLKGATE_SEPERATED_STATUS		0x8

काष्ठा clkgate_separated अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*enable;	/* enable रेजिस्टर */
	u8		bit_idx;	/* bits in enable/disable रेजिस्टर */
	u8		flags;
	spinlock_t	*lock;
पूर्ण;

अटल पूर्णांक clkgate_separated_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clkgate_separated *sclk;
	अचिन्हित दीर्घ flags = 0;
	u32 reg;

	sclk = container_of(hw, काष्ठा clkgate_separated, hw);
	अगर (sclk->lock)
		spin_lock_irqsave(sclk->lock, flags);
	reg = BIT(sclk->bit_idx);
	ग_लिखोl_relaxed(reg, sclk->enable);
	पढ़ोl_relaxed(sclk->enable + CLKGATE_SEPERATED_STATUS);
	अगर (sclk->lock)
		spin_unlock_irqrestore(sclk->lock, flags);
	वापस 0;
पूर्ण

अटल व्योम clkgate_separated_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clkgate_separated *sclk;
	अचिन्हित दीर्घ flags = 0;
	u32 reg;

	sclk = container_of(hw, काष्ठा clkgate_separated, hw);
	अगर (sclk->lock)
		spin_lock_irqsave(sclk->lock, flags);
	reg = BIT(sclk->bit_idx);
	ग_लिखोl_relaxed(reg, sclk->enable + CLKGATE_SEPERATED_DISABLE);
	पढ़ोl_relaxed(sclk->enable + CLKGATE_SEPERATED_STATUS);
	अगर (sclk->lock)
		spin_unlock_irqrestore(sclk->lock, flags);
पूर्ण

अटल पूर्णांक clkgate_separated_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clkgate_separated *sclk;
	u32 reg;

	sclk = container_of(hw, काष्ठा clkgate_separated, hw);
	reg = पढ़ोl_relaxed(sclk->enable + CLKGATE_SEPERATED_STATUS);
	reg &= BIT(sclk->bit_idx);

	वापस reg ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clkgate_separated_ops = अणु
	.enable		= clkgate_separated_enable,
	.disable	= clkgate_separated_disable,
	.is_enabled	= clkgate_separated_is_enabled,
पूर्ण;

काष्ठा clk *hisi_रेजिस्टर_clkgate_sep(काष्ठा device *dev, स्थिर अक्षर *name,
				      स्थिर अक्षर *parent_name,
				      अचिन्हित दीर्घ flags,
				      व्योम __iomem *reg, u8 bit_idx,
				      u8 clk_gate_flags, spinlock_t *lock)
अणु
	काष्ठा clkgate_separated *sclk;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	sclk = kzalloc(माप(*sclk), GFP_KERNEL);
	अगर (!sclk)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clkgate_separated_ops;
	init.flags = flags;
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);

	sclk->enable = reg + CLKGATE_SEPERATED_ENABLE;
	sclk->bit_idx = bit_idx;
	sclk->flags = clk_gate_flags;
	sclk->hw.init = &init;
	sclk->lock = lock;

	clk = clk_रेजिस्टर(dev, &sclk->hw);
	अगर (IS_ERR(clk))
		kमुक्त(sclk);
	वापस clk;
पूर्ण
