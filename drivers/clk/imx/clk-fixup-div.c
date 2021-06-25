<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश "clk.h"

#घोषणा भाग_mask(d)	((1 << (d->width)) - 1)

/**
 * काष्ठा clk_fixup_भाग - imx पूर्णांकeger fixup भागider घड़ी
 * @भागider: the parent class
 * @ops: poपूर्णांकer to clk_ops of parent class
 * @fixup: a hook to fixup the ग_लिखो value
 *
 * The imx fixup भागider घड़ी is a subclass of basic clk_भागider
 * with an addtional fixup hook.
 */
काष्ठा clk_fixup_भाग अणु
	काष्ठा clk_भागider भागider;
	स्थिर काष्ठा clk_ops *ops;
	व्योम (*fixup)(u32 *val);
पूर्ण;

अटल अंतरभूत काष्ठा clk_fixup_भाग *to_clk_fixup_भाग(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_भागider *भागider = to_clk_भागider(hw);

	वापस container_of(भागider, काष्ठा clk_fixup_भाग, भागider);
पूर्ण

अटल अचिन्हित दीर्घ clk_fixup_भाग_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_fixup_भाग *fixup_भाग = to_clk_fixup_भाग(hw);

	वापस fixup_भाग->ops->recalc_rate(&fixup_भाग->भागider.hw, parent_rate);
पूर्ण

अटल दीर्घ clk_fixup_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_fixup_भाग *fixup_भाग = to_clk_fixup_भाग(hw);

	वापस fixup_भाग->ops->round_rate(&fixup_भाग->भागider.hw, rate, prate);
पूर्ण

अटल पूर्णांक clk_fixup_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_fixup_भाग *fixup_भाग = to_clk_fixup_भाग(hw);
	काष्ठा clk_भागider *भाग = to_clk_भागider(hw);
	अचिन्हित पूर्णांक भागider, value;
	अचिन्हित दीर्घ flags;
	u32 val;

	भागider = parent_rate / rate;

	/* Zero based भागider */
	value = भागider - 1;

	अगर (value > भाग_mask(भाग))
		value = भाग_mask(भाग);

	spin_lock_irqsave(भाग->lock, flags);

	val = पढ़ोl(भाग->reg);
	val &= ~(भाग_mask(भाग) << भाग->shअगरt);
	val |= value << भाग->shअगरt;
	fixup_भाग->fixup(&val);
	ग_लिखोl(val, भाग->reg);

	spin_unlock_irqrestore(भाग->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_fixup_भाग_ops = अणु
	.recalc_rate = clk_fixup_भाग_recalc_rate,
	.round_rate = clk_fixup_भाग_round_rate,
	.set_rate = clk_fixup_भाग_set_rate,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_fixup_भागider(स्थिर अक्षर *name, स्थिर अक्षर *parent,
				  व्योम __iomem *reg, u8 shअगरt, u8 width,
				  व्योम (*fixup)(u32 *val))
अणु
	काष्ठा clk_fixup_भाग *fixup_भाग;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	अगर (!fixup)
		वापस ERR_PTR(-EINVAL);

	fixup_भाग = kzalloc(माप(*fixup_भाग), GFP_KERNEL);
	अगर (!fixup_भाग)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_fixup_भाग_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = parent ? &parent : शून्य;
	init.num_parents = parent ? 1 : 0;

	fixup_भाग->भागider.reg = reg;
	fixup_भाग->भागider.shअगरt = shअगरt;
	fixup_भाग->भागider.width = width;
	fixup_भाग->भागider.lock = &imx_ccm_lock;
	fixup_भाग->भागider.hw.init = &init;
	fixup_भाग->ops = &clk_भागider_ops;
	fixup_भाग->fixup = fixup;

	hw = &fixup_भाग->भागider.hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(fixup_भाग);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
