<शैली गुरु>
/*
 * mmp AXI peripharal घड़ी operation source file
 *
 * Copyright (C) 2012 Marvell
 * Chao Xie <xiechao.mail@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश "clk.h"

#घोषणा to_clk_apmu(clk) (container_of(clk, काष्ठा clk_apmu, clk))
काष्ठा clk_apmu अणु
	काष्ठा clk_hw   hw;
	व्योम __iomem    *base;
	u32		rst_mask;
	u32		enable_mask;
	spinlock_t	*lock;
पूर्ण;

अटल पूर्णांक clk_apmu_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_apmu *apmu = to_clk_apmu(hw);
	अचिन्हित दीर्घ data;
	अचिन्हित दीर्घ flags = 0;

	अगर (apmu->lock)
		spin_lock_irqsave(apmu->lock, flags);

	data = पढ़ोl_relaxed(apmu->base) | apmu->enable_mask;
	ग_लिखोl_relaxed(data, apmu->base);

	अगर (apmu->lock)
		spin_unlock_irqrestore(apmu->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम clk_apmu_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_apmu *apmu = to_clk_apmu(hw);
	अचिन्हित दीर्घ data;
	अचिन्हित दीर्घ flags = 0;

	अगर (apmu->lock)
		spin_lock_irqsave(apmu->lock, flags);

	data = पढ़ोl_relaxed(apmu->base) & ~apmu->enable_mask;
	ग_लिखोl_relaxed(data, apmu->base);

	अगर (apmu->lock)
		spin_unlock_irqrestore(apmu->lock, flags);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_apmu_ops = अणु
	.enable = clk_apmu_enable,
	.disable = clk_apmu_disable,
पूर्ण;

काष्ठा clk *mmp_clk_रेजिस्टर_apmu(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		व्योम __iomem *base, u32 enable_mask, spinlock_t *lock)
अणु
	काष्ठा clk_apmu *apmu;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	apmu = kzalloc(माप(*apmu), GFP_KERNEL);
	अगर (!apmu)
		वापस शून्य;

	init.name = name;
	init.ops = &clk_apmu_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);

	apmu->base = base;
	apmu->enable_mask = enable_mask;
	apmu->lock = lock;
	apmu->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &apmu->hw);

	अगर (IS_ERR(clk))
		kमुक्त(apmu);

	वापस clk;
पूर्ण
