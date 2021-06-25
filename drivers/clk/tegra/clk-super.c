<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>

#समावेश "clk.h"

#घोषणा SUPER_STATE_IDLE 0
#घोषणा SUPER_STATE_RUN 1
#घोषणा SUPER_STATE_IRQ 2
#घोषणा SUPER_STATE_FIQ 3

#घोषणा SUPER_STATE_SHIFT 28
#घोषणा SUPER_STATE_MASK ((BIT(SUPER_STATE_IDLE) | BIT(SUPER_STATE_RUN) | \
			   BIT(SUPER_STATE_IRQ) | BIT(SUPER_STATE_FIQ))	\
			  << SUPER_STATE_SHIFT)

#घोषणा SUPER_LP_DIV2_BYPASS (1 << 16)

#घोषणा super_state(s) (BIT(s) << SUPER_STATE_SHIFT)
#घोषणा super_state_to_src_shअगरt(m, s) ((m->width * s))
#घोषणा super_state_to_src_mask(m) (((1 << m->width) - 1))

#घोषणा CCLK_SRC_PLLP_OUT0 4
#घोषणा CCLK_SRC_PLLP_OUT4 5

अटल u8 clk_super_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_super_mux *mux = to_clk_super_mux(hw);
	u32 val, state;
	u8 source, shअगरt;

	val = पढ़ोl_relaxed(mux->reg);

	state = val & SUPER_STATE_MASK;

	BUG_ON((state != super_state(SUPER_STATE_RUN)) &&
	       (state != super_state(SUPER_STATE_IDLE)));
	shअगरt = (state == super_state(SUPER_STATE_IDLE)) ?
		super_state_to_src_shअगरt(mux, SUPER_STATE_IDLE) :
		super_state_to_src_shअगरt(mux, SUPER_STATE_RUN);

	source = (val >> shअगरt) & super_state_to_src_mask(mux);

	/*
	 * If LP_DIV2_BYPASS is not set and PLLX is current parent then
	 * PLLX/2 is the input source to CCLKLP.
	 */
	अगर ((mux->flags & TEGRA_DIVIDER_2) && !(val & SUPER_LP_DIV2_BYPASS) &&
	    (source == mux->pllx_index))
		source = mux->भाग2_index;

	वापस source;
पूर्ण

अटल पूर्णांक clk_super_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा tegra_clk_super_mux *mux = to_clk_super_mux(hw);
	u32 val, state;
	पूर्णांक err = 0;
	u8 parent_index, shअगरt;
	अचिन्हित दीर्घ flags = 0;

	अगर (mux->lock)
		spin_lock_irqsave(mux->lock, flags);

	val = पढ़ोl_relaxed(mux->reg);
	state = val & SUPER_STATE_MASK;
	BUG_ON((state != super_state(SUPER_STATE_RUN)) &&
	       (state != super_state(SUPER_STATE_IDLE)));
	shअगरt = (state == super_state(SUPER_STATE_IDLE)) ?
		super_state_to_src_shअगरt(mux, SUPER_STATE_IDLE) :
		super_state_to_src_shअगरt(mux, SUPER_STATE_RUN);

	/*
	 * For LP mode super-घड़ी चयन between PLLX direct
	 * and भागided-by-2 outमाला_दो is allowed only when other
	 * than PLLX घड़ी source is current parent.
	 */
	अगर ((mux->flags & TEGRA_DIVIDER_2) && ((index == mux->भाग2_index) ||
					       (index == mux->pllx_index))) अणु
		parent_index = clk_super_get_parent(hw);
		अगर ((parent_index == mux->भाग2_index) ||
		    (parent_index == mux->pllx_index)) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		val ^= SUPER_LP_DIV2_BYPASS;
		ग_लिखोl_relaxed(val, mux->reg);
		udelay(2);

		अगर (index == mux->भाग2_index)
			index = mux->pllx_index;
	पूर्ण

	/* enable PLLP branches to CPU beक्रमe selecting PLLP source */
	अगर ((mux->flags & TEGRA210_CPU_CLK) &&
	    (index == CCLK_SRC_PLLP_OUT0 || index == CCLK_SRC_PLLP_OUT4))
		tegra_clk_set_pllp_out_cpu(true);

	val &= ~((super_state_to_src_mask(mux)) << shअगरt);
	val |= (index & (super_state_to_src_mask(mux))) << shअगरt;

	ग_लिखोl_relaxed(val, mux->reg);
	udelay(2);

	/* disable PLLP branches to CPU अगर not used */
	अगर ((mux->flags & TEGRA210_CPU_CLK) &&
	    index != CCLK_SRC_PLLP_OUT0 && index != CCLK_SRC_PLLP_OUT4)
		tegra_clk_set_pllp_out_cpu(false);

out:
	अगर (mux->lock)
		spin_unlock_irqrestore(mux->lock, flags);

	वापस err;
पूर्ण

अटल व्योम clk_super_mux_restore_context(काष्ठा clk_hw *hw)
अणु
	पूर्णांक parent_id;

	parent_id = clk_hw_get_parent_index(hw);
	अगर (WARN_ON(parent_id < 0))
		वापस;

	clk_super_set_parent(hw, parent_id);
पूर्ण

अटल स्थिर काष्ठा clk_ops tegra_clk_super_mux_ops = अणु
	.get_parent = clk_super_get_parent,
	.set_parent = clk_super_set_parent,
	.restore_context = clk_super_mux_restore_context,
पूर्ण;

अटल दीर्घ clk_super_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा tegra_clk_super_mux *super = to_clk_super_mux(hw);
	काष्ठा clk_hw *भाग_hw = &super->frac_भाग.hw;

	__clk_hw_set_clk(भाग_hw, hw);

	वापस super->भाग_ops->round_rate(भाग_hw, rate, parent_rate);
पूर्ण

अटल अचिन्हित दीर्घ clk_super_recalc_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_super_mux *super = to_clk_super_mux(hw);
	काष्ठा clk_hw *भाग_hw = &super->frac_भाग.hw;

	__clk_hw_set_clk(भाग_hw, hw);

	वापस super->भाग_ops->recalc_rate(भाग_hw, parent_rate);
पूर्ण

अटल पूर्णांक clk_super_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_super_mux *super = to_clk_super_mux(hw);
	काष्ठा clk_hw *भाग_hw = &super->frac_भाग.hw;

	__clk_hw_set_clk(भाग_hw, hw);

	वापस super->भाग_ops->set_rate(भाग_hw, rate, parent_rate);
पूर्ण

अटल व्योम clk_super_restore_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_super_mux *super = to_clk_super_mux(hw);
	काष्ठा clk_hw *भाग_hw = &super->frac_भाग.hw;
	पूर्णांक parent_id;

	parent_id = clk_hw_get_parent_index(hw);
	अगर (WARN_ON(parent_id < 0))
		वापस;

	super->भाग_ops->restore_context(भाग_hw);
	clk_super_set_parent(hw, parent_id);
पूर्ण

स्थिर काष्ठा clk_ops tegra_clk_super_ops = अणु
	.get_parent = clk_super_get_parent,
	.set_parent = clk_super_set_parent,
	.set_rate = clk_super_set_rate,
	.round_rate = clk_super_round_rate,
	.recalc_rate = clk_super_recalc_rate,
	.restore_context = clk_super_restore_context,
पूर्ण;

काष्ठा clk *tegra_clk_रेजिस्टर_super_mux(स्थिर अक्षर *name,
		स्थिर अक्षर **parent_names, u8 num_parents,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg, u8 clk_super_flags,
		u8 width, u8 pllx_index, u8 भाग2_index, spinlock_t *lock)
अणु
	काष्ठा tegra_clk_super_mux *super;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	super = kzalloc(माप(*super), GFP_KERNEL);
	अगर (!super)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &tegra_clk_super_mux_ops;
	init.flags = flags;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	super->reg = reg;
	super->pllx_index = pllx_index;
	super->भाग2_index = भाग2_index;
	super->lock = lock;
	super->width = width;
	super->flags = clk_super_flags;

	/* Data in .init is copied by clk_रेजिस्टर(), so stack variable OK */
	super->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &super->hw);
	अगर (IS_ERR(clk))
		kमुक्त(super);

	वापस clk;
पूर्ण

काष्ठा clk *tegra_clk_रेजिस्टर_super_clk(स्थिर अक्षर *name,
		स्थिर अक्षर * स्थिर *parent_names, u8 num_parents,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg, u8 clk_super_flags,
		spinlock_t *lock)
अणु
	काष्ठा tegra_clk_super_mux *super;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	super = kzalloc(माप(*super), GFP_KERNEL);
	अगर (!super)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &tegra_clk_super_ops;
	init.flags = flags;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	super->reg = reg;
	super->lock = lock;
	super->width = 4;
	super->flags = clk_super_flags;
	super->frac_भाग.reg = reg + 4;
	super->frac_भाग.shअगरt = 16;
	super->frac_भाग.width = 8;
	super->frac_भाग.frac_width = 1;
	super->frac_भाग.lock = lock;
	super->भाग_ops = &tegra_clk_frac_भाग_ops;

	/* Data in .init is copied by clk_रेजिस्टर(), so stack variable OK */
	super->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &super->hw);
	अगर (IS_ERR(clk))
		kमुक्त(super);

	वापस clk;
पूर्ण
