<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश "clk.h"

/**
 * काष्ठा clk_भाग - mxs पूर्णांकeger भागider घड़ी
 * @भागider: the parent class
 * @ops: poपूर्णांकer to clk_ops of parent class
 * @reg: रेजिस्टर address
 * @busy: busy bit shअगरt
 *
 * The mxs भागider घड़ी is a subclass of basic clk_भागider with an
 * addtional busy bit.
 */
काष्ठा clk_भाग अणु
	काष्ठा clk_भागider भागider;
	स्थिर काष्ठा clk_ops *ops;
	व्योम __iomem *reg;
	u8 busy;
पूर्ण;

अटल अंतरभूत काष्ठा clk_भाग *to_clk_भाग(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_भागider *भागider = to_clk_भागider(hw);

	वापस container_of(भागider, काष्ठा clk_भाग, भागider);
पूर्ण

अटल अचिन्हित दीर्घ clk_भाग_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_भाग *भाग = to_clk_भाग(hw);

	वापस भाग->ops->recalc_rate(&भाग->भागider.hw, parent_rate);
पूर्ण

अटल दीर्घ clk_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_भाग *भाग = to_clk_भाग(hw);

	वापस भाग->ops->round_rate(&भाग->भागider.hw, rate, prate);
पूर्ण

अटल पूर्णांक clk_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_भाग *भाग = to_clk_भाग(hw);
	पूर्णांक ret;

	ret = भाग->ops->set_rate(&भाग->भागider.hw, rate, parent_rate);
	अगर (!ret)
		ret = mxs_clk_रुको(भाग->reg, भाग->busy);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_भाग_ops = अणु
	.recalc_rate = clk_भाग_recalc_rate,
	.round_rate = clk_भाग_round_rate,
	.set_rate = clk_भाग_set_rate,
पूर्ण;

काष्ठा clk *mxs_clk_भाग(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			व्योम __iomem *reg, u8 shअगरt, u8 width, u8 busy)
अणु
	काष्ठा clk_भाग *भाग;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_भाग_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = (parent_name ? &parent_name: शून्य);
	init.num_parents = (parent_name ? 1 : 0);

	भाग->reg = reg;
	भाग->busy = busy;

	भाग->भागider.reg = reg;
	भाग->भागider.shअगरt = shअगरt;
	भाग->भागider.width = width;
	भाग->भागider.flags = CLK_DIVIDER_ONE_BASED;
	भाग->भागider.lock = &mxs_lock;
	भाग->भागider.hw.init = &init;
	भाग->ops = &clk_भागider_ops;

	clk = clk_रेजिस्टर(शून्य, &भाग->भागider.hw);
	अगर (IS_ERR(clk))
		kमुक्त(भाग);

	वापस clk;
पूर्ण
