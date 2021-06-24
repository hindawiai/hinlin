<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 Heiko Stuebner <heiko@sntech.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश "clk.h"

काष्ठा rockchip_inv_घड़ी अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	पूर्णांक		shअगरt;
	पूर्णांक		flags;
	spinlock_t	*lock;
पूर्ण;

#घोषणा to_inv_घड़ी(_hw) container_of(_hw, काष्ठा rockchip_inv_घड़ी, hw)

#घोषणा INVERTER_MASK 0x1

अटल पूर्णांक rockchip_inv_get_phase(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_inv_घड़ी *inv_घड़ी = to_inv_घड़ी(hw);
	u32 val;

	val = पढ़ोl(inv_घड़ी->reg) >> inv_घड़ी->shअगरt;
	val &= INVERTER_MASK;
	वापस val ? 180 : 0;
पूर्ण

अटल पूर्णांक rockchip_inv_set_phase(काष्ठा clk_hw *hw, पूर्णांक degrees)
अणु
	काष्ठा rockchip_inv_घड़ी *inv_घड़ी = to_inv_घड़ी(hw);
	u32 val;

	अगर (degrees % 180 == 0) अणु
		val = !!degrees;
	पूर्ण अन्यथा अणु
		pr_err("%s: unsupported phase %d for %s\n",
		       __func__, degrees, clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	अगर (inv_घड़ी->flags & ROCKCHIP_INVERTER_HIWORD_MASK) अणु
		ग_लिखोl(HIWORD_UPDATE(val, INVERTER_MASK, inv_घड़ी->shअगरt),
		       inv_घड़ी->reg);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;
		u32 reg;

		spin_lock_irqsave(inv_घड़ी->lock, flags);

		reg = पढ़ोl(inv_घड़ी->reg);
		reg &= ~BIT(inv_घड़ी->shअगरt);
		reg |= val;
		ग_लिखोl(reg, inv_घड़ी->reg);

		spin_unlock_irqrestore(inv_घड़ी->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops rockchip_inv_clk_ops = अणु
	.get_phase	= rockchip_inv_get_phase,
	.set_phase	= rockchip_inv_set_phase,
पूर्ण;

काष्ठा clk *rockchip_clk_रेजिस्टर_inverter(स्थिर अक्षर *name,
				स्थिर अक्षर *स्थिर *parent_names, u8 num_parents,
				व्योम __iomem *reg, पूर्णांक shअगरt, पूर्णांक flags,
				spinlock_t *lock)
अणु
	काष्ठा clk_init_data init;
	काष्ठा rockchip_inv_घड़ी *inv_घड़ी;
	काष्ठा clk *clk;

	inv_घड़ी = kदो_स्मृति(माप(*inv_घड़ी), GFP_KERNEL);
	अगर (!inv_घड़ी)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.num_parents = num_parents;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = parent_names;
	init.ops = &rockchip_inv_clk_ops;

	inv_घड़ी->hw.init = &init;
	inv_घड़ी->reg = reg;
	inv_घड़ी->shअगरt = shअगरt;
	inv_घड़ी->flags = flags;
	inv_घड़ी->lock = lock;

	clk = clk_रेजिस्टर(शून्य, &inv_घड़ी->hw);
	अगर (IS_ERR(clk))
		kमुक्त(inv_घड़ी);

	वापस clk;
पूर्ण
