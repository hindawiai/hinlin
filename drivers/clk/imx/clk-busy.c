<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 * Copyright 2012 Linaro Ltd.
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/err.h>
#समावेश "clk.h"

अटल पूर्णांक clk_busy_रुको(व्योम __iomem *reg, u8 shअगरt)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(10);

	जबतक (पढ़ोl_relaxed(reg) & (1 << shअगरt))
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

काष्ठा clk_busy_भागider अणु
	काष्ठा clk_भागider भाग;
	स्थिर काष्ठा clk_ops *भाग_ops;
	व्योम __iomem *reg;
	u8 shअगरt;
पूर्ण;

अटल अंतरभूत काष्ठा clk_busy_भागider *to_clk_busy_भागider(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_भागider *भाग = to_clk_भागider(hw);

	वापस container_of(भाग, काष्ठा clk_busy_भागider, भाग);
पूर्ण

अटल अचिन्हित दीर्घ clk_busy_भागider_recalc_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_busy_भागider *busy = to_clk_busy_भागider(hw);

	वापस busy->भाग_ops->recalc_rate(&busy->भाग.hw, parent_rate);
पूर्ण

अटल दीर्घ clk_busy_भागider_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_busy_भागider *busy = to_clk_busy_भागider(hw);

	वापस busy->भाग_ops->round_rate(&busy->भाग.hw, rate, prate);
पूर्ण

अटल पूर्णांक clk_busy_भागider_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_busy_भागider *busy = to_clk_busy_भागider(hw);
	पूर्णांक ret;

	ret = busy->भाग_ops->set_rate(&busy->भाग.hw, rate, parent_rate);
	अगर (!ret)
		ret = clk_busy_रुको(busy->reg, busy->shअगरt);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_busy_भागider_ops = अणु
	.recalc_rate = clk_busy_भागider_recalc_rate,
	.round_rate = clk_busy_भागider_round_rate,
	.set_rate = clk_busy_भागider_set_rate,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_busy_भागider(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
				 व्योम __iomem *reg, u8 shअगरt, u8 width,
				 व्योम __iomem *busy_reg, u8 busy_shअगरt)
अणु
	काष्ठा clk_busy_भागider *busy;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	busy = kzalloc(माप(*busy), GFP_KERNEL);
	अगर (!busy)
		वापस ERR_PTR(-ENOMEM);

	busy->reg = busy_reg;
	busy->shअगरt = busy_shअगरt;

	busy->भाग.reg = reg;
	busy->भाग.shअगरt = shअगरt;
	busy->भाग.width = width;
	busy->भाग.lock = &imx_ccm_lock;
	busy->भाग_ops = &clk_भागider_ops;

	init.name = name;
	init.ops = &clk_busy_भागider_ops;
	init.flags = CLK_SET_RATE_PARENT | CLK_IS_CRITICAL;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	busy->भाग.hw.init = &init;

	hw = &busy->भाग.hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(busy);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

काष्ठा clk_busy_mux अणु
	काष्ठा clk_mux mux;
	स्थिर काष्ठा clk_ops *mux_ops;
	व्योम __iomem *reg;
	u8 shअगरt;
पूर्ण;

अटल अंतरभूत काष्ठा clk_busy_mux *to_clk_busy_mux(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_mux *mux = to_clk_mux(hw);

	वापस container_of(mux, काष्ठा clk_busy_mux, mux);
पूर्ण

अटल u8 clk_busy_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_busy_mux *busy = to_clk_busy_mux(hw);

	वापस busy->mux_ops->get_parent(&busy->mux.hw);
पूर्ण

अटल पूर्णांक clk_busy_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_busy_mux *busy = to_clk_busy_mux(hw);
	पूर्णांक ret;

	ret = busy->mux_ops->set_parent(&busy->mux.hw, index);
	अगर (!ret)
		ret = clk_busy_रुको(busy->reg, busy->shअगरt);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_busy_mux_ops = अणु
	.get_parent = clk_busy_mux_get_parent,
	.set_parent = clk_busy_mux_set_parent,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_busy_mux(स्थिर अक्षर *name, व्योम __iomem *reg, u8 shअगरt,
			     u8 width, व्योम __iomem *busy_reg, u8 busy_shअगरt,
			     स्थिर अक्षर * स्थिर *parent_names, पूर्णांक num_parents)
अणु
	काष्ठा clk_busy_mux *busy;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	busy = kzalloc(माप(*busy), GFP_KERNEL);
	अगर (!busy)
		वापस ERR_PTR(-ENOMEM);

	busy->reg = busy_reg;
	busy->shअगरt = busy_shअगरt;

	busy->mux.reg = reg;
	busy->mux.shअगरt = shअगरt;
	busy->mux.mask = BIT(width) - 1;
	busy->mux.lock = &imx_ccm_lock;
	busy->mux_ops = &clk_mux_ops;

	init.name = name;
	init.ops = &clk_busy_mux_ops;
	init.flags = CLK_IS_CRITICAL;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	busy->mux.hw.init = &init;

	hw = &busy->mux.hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(busy);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
