<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>

#समावेश "clk.h"

#घोषणा pll_out_override(p) (BIT((p->shअगरt - 6)))
#घोषणा भाग_mask(d) ((1 << (d->width)) - 1)
#घोषणा get_mul(d) (1 << d->frac_width)
#घोषणा get_max_भाग(d) भाग_mask(d)

#घोषणा PERIPH_CLK_UART_DIV_ENB BIT(24)

अटल पूर्णांक get_भाग(काष्ठा tegra_clk_frac_भाग *भागider, अचिन्हित दीर्घ rate,
		   अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक भाग;

	भाग = भाग_frac_get(rate, parent_rate, भागider->width,
			   भागider->frac_width, भागider->flags);

	अगर (भाग < 0)
		वापस 0;

	वापस भाग;
पूर्ण

अटल अचिन्हित दीर्घ clk_frac_भाग_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_frac_भाग *भागider = to_clk_frac_भाग(hw);
	u32 reg;
	पूर्णांक भाग, mul;
	u64 rate = parent_rate;

	reg = पढ़ोl_relaxed(भागider->reg);

	अगर ((भागider->flags & TEGRA_DIVIDER_UART) &&
	    !(reg & PERIPH_CLK_UART_DIV_ENB))
		वापस rate;

	भाग = (reg >> भागider->shअगरt) & भाग_mask(भागider);

	mul = get_mul(भागider);
	भाग += mul;

	rate *= mul;
	rate += भाग - 1;
	करो_भाग(rate, भाग);

	वापस rate;
पूर्ण

अटल दीर्घ clk_frac_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *prate)
अणु
	काष्ठा tegra_clk_frac_भाग *भागider = to_clk_frac_भाग(hw);
	पूर्णांक भाग, mul;
	अचिन्हित दीर्घ output_rate = *prate;

	अगर (!rate)
		वापस output_rate;

	भाग = get_भाग(भागider, rate, output_rate);
	अगर (भाग < 0)
		वापस *prate;

	mul = get_mul(भागider);

	वापस DIV_ROUND_UP(output_rate * mul, भाग + mul);
पूर्ण

अटल पूर्णांक clk_frac_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_frac_भाग *भागider = to_clk_frac_भाग(hw);
	पूर्णांक भाग;
	अचिन्हित दीर्घ flags = 0;
	u32 val;

	भाग = get_भाग(भागider, rate, parent_rate);
	अगर (भाग < 0)
		वापस भाग;

	अगर (भागider->lock)
		spin_lock_irqsave(भागider->lock, flags);

	val = पढ़ोl_relaxed(भागider->reg);
	val &= ~(भाग_mask(भागider) << भागider->shअगरt);
	val |= भाग << भागider->shअगरt;

	अगर (भागider->flags & TEGRA_DIVIDER_UART) अणु
		अगर (भाग)
			val |= PERIPH_CLK_UART_DIV_ENB;
		अन्यथा
			val &= ~PERIPH_CLK_UART_DIV_ENB;
	पूर्ण

	अगर (भागider->flags & TEGRA_DIVIDER_FIXED)
		val |= pll_out_override(भागider);

	ग_लिखोl_relaxed(val, भागider->reg);

	अगर (भागider->lock)
		spin_unlock_irqrestore(भागider->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम clk_भागider_restore_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw *parent = clk_hw_get_parent(hw);
	अचिन्हित दीर्घ parent_rate = clk_hw_get_rate(parent);
	अचिन्हित दीर्घ rate = clk_hw_get_rate(hw);

	अगर (clk_frac_भाग_set_rate(hw, rate, parent_rate) < 0)
		WARN_ON(1);
पूर्ण

स्थिर काष्ठा clk_ops tegra_clk_frac_भाग_ops = अणु
	.recalc_rate = clk_frac_भाग_recalc_rate,
	.set_rate = clk_frac_भाग_set_rate,
	.round_rate = clk_frac_भाग_round_rate,
	.restore_context = clk_भागider_restore_context,
पूर्ण;

काष्ठा clk *tegra_clk_रेजिस्टर_भागider(स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, व्योम __iomem *reg,
		अचिन्हित दीर्घ flags, u8 clk_भागider_flags, u8 shअगरt, u8 width,
		u8 frac_width, spinlock_t *lock)
अणु
	काष्ठा tegra_clk_frac_भाग *भागider;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	भागider = kzalloc(माप(*भागider), GFP_KERNEL);
	अगर (!भागider) अणु
		pr_err("%s: could not allocate fractional divider clk\n",
		       __func__);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	init.name = name;
	init.ops = &tegra_clk_frac_भाग_ops;
	init.flags = flags;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;

	भागider->reg = reg;
	भागider->shअगरt = shअगरt;
	भागider->width = width;
	भागider->frac_width = frac_width;
	भागider->lock = lock;
	भागider->flags = clk_भागider_flags;

	/* Data in .init is copied by clk_रेजिस्टर(), so stack variable OK */
	भागider->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &भागider->hw);
	अगर (IS_ERR(clk))
		kमुक्त(भागider);

	वापस clk;
पूर्ण

अटल स्थिर काष्ठा clk_भाग_प्रकारable mc_भाग_प्रकारable[] = अणु
	अणु .val = 0, .भाग = 2 पूर्ण,
	अणु .val = 1, .भाग = 1 पूर्ण,
	अणु .val = 0, .भाग = 0 पूर्ण,
पूर्ण;

काष्ठा clk *tegra_clk_रेजिस्टर_mc(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
				  व्योम __iomem *reg, spinlock_t *lock)
अणु
	वापस clk_रेजिस्टर_भागider_table(शून्य, name, parent_name,
					  CLK_IS_CRITICAL,
					  reg, 16, 1, CLK_DIVIDER_READ_ONLY,
					  mc_भाग_प्रकारable, lock);
पूर्ण
