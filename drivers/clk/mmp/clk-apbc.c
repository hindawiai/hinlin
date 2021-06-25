<शैली गुरु>
/*
 * mmp APB घड़ी operation source file
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

/* Common APB घड़ी रेजिस्टर bit definitions */
#घोषणा APBC_APBCLK	(1 << 0)  /* APB Bus Clock Enable */
#घोषणा APBC_FNCLK	(1 << 1)  /* Functional Clock Enable */
#घोषणा APBC_RST	(1 << 2)  /* Reset Generation */
#घोषणा APBC_POWER	(1 << 7)  /* Reset Generation */

#घोषणा to_clk_apbc(hw) container_of(hw, काष्ठा clk_apbc, hw)
काष्ठा clk_apbc अणु
	काष्ठा clk_hw		hw;
	व्योम __iomem		*base;
	अचिन्हित पूर्णांक		delay;
	अचिन्हित पूर्णांक		flags;
	spinlock_t		*lock;
पूर्ण;

अटल पूर्णांक clk_apbc_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_apbc *apbc = to_clk_apbc(hw);
	अचिन्हित पूर्णांक data;
	अचिन्हित दीर्घ flags = 0;

	/*
	 * It may share same रेजिस्टर as MUX घड़ी,
	 * and it will impact FNCLK enable. Spinlock is needed
	 */
	अगर (apbc->lock)
		spin_lock_irqsave(apbc->lock, flags);

	data = पढ़ोl_relaxed(apbc->base);
	अगर (apbc->flags & APBC_POWER_CTRL)
		data |= APBC_POWER;
	data |= APBC_FNCLK;
	ग_लिखोl_relaxed(data, apbc->base);

	अगर (apbc->lock)
		spin_unlock_irqrestore(apbc->lock, flags);

	udelay(apbc->delay);

	अगर (apbc->lock)
		spin_lock_irqsave(apbc->lock, flags);

	data = पढ़ोl_relaxed(apbc->base);
	data |= APBC_APBCLK;
	ग_लिखोl_relaxed(data, apbc->base);

	अगर (apbc->lock)
		spin_unlock_irqrestore(apbc->lock, flags);

	udelay(apbc->delay);

	अगर (!(apbc->flags & APBC_NO_BUS_CTRL)) अणु
		अगर (apbc->lock)
			spin_lock_irqsave(apbc->lock, flags);

		data = पढ़ोl_relaxed(apbc->base);
		data &= ~APBC_RST;
		ग_लिखोl_relaxed(data, apbc->base);

		अगर (apbc->lock)
			spin_unlock_irqrestore(apbc->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम clk_apbc_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_apbc *apbc = to_clk_apbc(hw);
	अचिन्हित दीर्घ data;
	अचिन्हित दीर्घ flags = 0;

	अगर (apbc->lock)
		spin_lock_irqsave(apbc->lock, flags);

	data = पढ़ोl_relaxed(apbc->base);
	अगर (apbc->flags & APBC_POWER_CTRL)
		data &= ~APBC_POWER;
	data &= ~APBC_FNCLK;
	ग_लिखोl_relaxed(data, apbc->base);

	अगर (apbc->lock)
		spin_unlock_irqrestore(apbc->lock, flags);

	udelay(10);

	अगर (apbc->lock)
		spin_lock_irqsave(apbc->lock, flags);

	data = पढ़ोl_relaxed(apbc->base);
	data &= ~APBC_APBCLK;
	ग_लिखोl_relaxed(data, apbc->base);

	अगर (apbc->lock)
		spin_unlock_irqrestore(apbc->lock, flags);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_apbc_ops = अणु
	.prepare = clk_apbc_prepare,
	.unprepare = clk_apbc_unprepare,
पूर्ण;

काष्ठा clk *mmp_clk_रेजिस्टर_apbc(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		व्योम __iomem *base, अचिन्हित पूर्णांक delay,
		अचिन्हित पूर्णांक apbc_flags, spinlock_t *lock)
अणु
	काष्ठा clk_apbc *apbc;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	apbc = kzalloc(माप(*apbc), GFP_KERNEL);
	अगर (!apbc)
		वापस शून्य;

	init.name = name;
	init.ops = &clk_apbc_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);

	apbc->base = base;
	apbc->delay = delay;
	apbc->flags = apbc_flags;
	apbc->lock = lock;
	apbc->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &apbc->hw);
	अगर (IS_ERR(clk))
		kमुक्त(apbc);

	वापस clk;
पूर्ण
