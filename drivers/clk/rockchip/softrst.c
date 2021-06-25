<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014 MunकरोReader S.L.
 * Author: Heiko Stuebner <heiko@sntech.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/reset-controller.h>
#समावेश <linux/spinlock.h>
#समावेश "clk.h"

काष्ठा rockchip_softrst अणु
	काष्ठा reset_controller_dev	rcdev;
	व्योम __iomem			*reg_base;
	पूर्णांक				num_regs;
	पूर्णांक				num_per_reg;
	u8				flags;
	spinlock_t			lock;
पूर्ण;

अटल पूर्णांक rockchip_softrst_निश्चित(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा rockchip_softrst *softrst = container_of(rcdev,
						     काष्ठा rockchip_softrst,
						     rcdev);
	पूर्णांक bank = id / softrst->num_per_reg;
	पूर्णांक offset = id % softrst->num_per_reg;

	अगर (softrst->flags & ROCKCHIP_SOFTRST_HIWORD_MASK) अणु
		ग_लिखोl(BIT(offset) | (BIT(offset) << 16),
		       softrst->reg_base + (bank * 4));
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;
		u32 reg;

		spin_lock_irqsave(&softrst->lock, flags);

		reg = पढ़ोl(softrst->reg_base + (bank * 4));
		ग_लिखोl(reg | BIT(offset), softrst->reg_base + (bank * 4));

		spin_unlock_irqrestore(&softrst->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_softrst_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	काष्ठा rockchip_softrst *softrst = container_of(rcdev,
						     काष्ठा rockchip_softrst,
						     rcdev);
	पूर्णांक bank = id / softrst->num_per_reg;
	पूर्णांक offset = id % softrst->num_per_reg;

	अगर (softrst->flags & ROCKCHIP_SOFTRST_HIWORD_MASK) अणु
		ग_लिखोl((BIT(offset) << 16), softrst->reg_base + (bank * 4));
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;
		u32 reg;

		spin_lock_irqsave(&softrst->lock, flags);

		reg = पढ़ोl(softrst->reg_base + (bank * 4));
		ग_लिखोl(reg & ~BIT(offset), softrst->reg_base + (bank * 4));

		spin_unlock_irqrestore(&softrst->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops rockchip_softrst_ops = अणु
	.निश्चित		= rockchip_softrst_निश्चित,
	.deनिश्चित	= rockchip_softrst_deनिश्चित,
पूर्ण;

व्योम rockchip_रेजिस्टर_softrst(काष्ठा device_node *np,
			       अचिन्हित पूर्णांक num_regs,
			       व्योम __iomem *base, u8 flags)
अणु
	काष्ठा rockchip_softrst *softrst;
	पूर्णांक ret;

	softrst = kzalloc(माप(*softrst), GFP_KERNEL);
	अगर (!softrst)
		वापस;

	spin_lock_init(&softrst->lock);

	softrst->reg_base = base;
	softrst->flags = flags;
	softrst->num_regs = num_regs;
	softrst->num_per_reg = (flags & ROCKCHIP_SOFTRST_HIWORD_MASK) ? 16
								      : 32;

	softrst->rcdev.owner = THIS_MODULE;
	softrst->rcdev.nr_resets =  num_regs * softrst->num_per_reg;
	softrst->rcdev.ops = &rockchip_softrst_ops;
	softrst->rcdev.of_node = np;
	ret = reset_controller_रेजिस्टर(&softrst->rcdev);
	अगर (ret) अणु
		pr_err("%s: could not register reset controller, %d\n",
		       __func__, ret);
		kमुक्त(softrst);
	पूर्ण
पूर्ण;
EXPORT_SYMBOL_GPL(rockchip_रेजिस्टर_softrst);
