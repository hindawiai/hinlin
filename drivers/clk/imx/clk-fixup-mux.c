<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश "clk.h"

/**
 * काष्ठा clk_fixup_mux - imx पूर्णांकeger fixup multiplexer घड़ी
 * @mux: the parent class
 * @ops: poपूर्णांकer to clk_ops of parent class
 * @fixup: a hook to fixup the ग_लिखो value
 *
 * The imx fixup multiplexer घड़ी is a subclass of basic clk_mux
 * with an addtional fixup hook.
 */
काष्ठा clk_fixup_mux अणु
	काष्ठा clk_mux mux;
	स्थिर काष्ठा clk_ops *ops;
	व्योम (*fixup)(u32 *val);
पूर्ण;

अटल अंतरभूत काष्ठा clk_fixup_mux *to_clk_fixup_mux(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_mux *mux = to_clk_mux(hw);

	वापस container_of(mux, काष्ठा clk_fixup_mux, mux);
पूर्ण

अटल u8 clk_fixup_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_fixup_mux *fixup_mux = to_clk_fixup_mux(hw);

	वापस fixup_mux->ops->get_parent(&fixup_mux->mux.hw);
पूर्ण

अटल पूर्णांक clk_fixup_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_fixup_mux *fixup_mux = to_clk_fixup_mux(hw);
	काष्ठा clk_mux *mux = to_clk_mux(hw);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(mux->lock, flags);

	val = पढ़ोl(mux->reg);
	val &= ~(mux->mask << mux->shअगरt);
	val |= index << mux->shअगरt;
	fixup_mux->fixup(&val);
	ग_लिखोl(val, mux->reg);

	spin_unlock_irqrestore(mux->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_fixup_mux_ops = अणु
	.get_parent = clk_fixup_mux_get_parent,
	.set_parent = clk_fixup_mux_set_parent,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_fixup_mux(स्थिर अक्षर *name, व्योम __iomem *reg,
			      u8 shअगरt, u8 width, स्थिर अक्षर * स्थिर *parents,
			      पूर्णांक num_parents, व्योम (*fixup)(u32 *val))
अणु
	काष्ठा clk_fixup_mux *fixup_mux;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	अगर (!fixup)
		वापस ERR_PTR(-EINVAL);

	fixup_mux = kzalloc(माप(*fixup_mux), GFP_KERNEL);
	अगर (!fixup_mux)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_fixup_mux_ops;
	init.parent_names = parents;
	init.num_parents = num_parents;
	init.flags = 0;

	fixup_mux->mux.reg = reg;
	fixup_mux->mux.shअगरt = shअगरt;
	fixup_mux->mux.mask = BIT(width) - 1;
	fixup_mux->mux.lock = &imx_ccm_lock;
	fixup_mux->mux.hw.init = &init;
	fixup_mux->ops = &clk_mux_ops;
	fixup_mux->fixup = fixup;

	hw = &fixup_mux->mux.hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(fixup_mux);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
