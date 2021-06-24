<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

अटल अंतरभूत u32 clk_mult_पढ़ोl(काष्ठा clk_multiplier *mult)
अणु
	अगर (mult->flags & CLK_MULTIPLIER_BIG_ENDIAN)
		वापस ioपढ़ो32be(mult->reg);

	वापस पढ़ोl(mult->reg);
पूर्ण

अटल अंतरभूत व्योम clk_mult_ग_लिखोl(काष्ठा clk_multiplier *mult, u32 val)
अणु
	अगर (mult->flags & CLK_MULTIPLIER_BIG_ENDIAN)
		ioग_लिखो32be(val, mult->reg);
	अन्यथा
		ग_लिखोl(val, mult->reg);
पूर्ण

अटल अचिन्हित दीर्घ __get_mult(काष्ठा clk_multiplier *mult,
				अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	अगर (mult->flags & CLK_MULTIPLIER_ROUND_CLOSEST)
		वापस DIV_ROUND_CLOSEST(rate, parent_rate);

	वापस rate / parent_rate;
पूर्ण

अटल अचिन्हित दीर्घ clk_multiplier_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_multiplier *mult = to_clk_multiplier(hw);
	अचिन्हित दीर्घ val;

	val = clk_mult_पढ़ोl(mult) >> mult->shअगरt;
	val &= GENMASK(mult->width - 1, 0);

	अगर (!val && mult->flags & CLK_MULTIPLIER_ZERO_BYPASS)
		val = 1;

	वापस parent_rate * val;
पूर्ण

अटल bool __is_best_rate(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ new,
			   अचिन्हित दीर्घ best, अचिन्हित दीर्घ flags)
अणु
	अगर (flags & CLK_MULTIPLIER_ROUND_CLOSEST)
		वापस असल(rate - new) < असल(rate - best);

	वापस new >= rate && new < best;
पूर्ण

अटल अचिन्हित दीर्घ __besपंचांगult(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *best_parent_rate,
				u8 width, अचिन्हित दीर्घ flags)
अणु
	काष्ठा clk_multiplier *mult = to_clk_multiplier(hw);
	अचिन्हित दीर्घ orig_parent_rate = *best_parent_rate;
	अचिन्हित दीर्घ parent_rate, current_rate, best_rate = ~0;
	अचिन्हित पूर्णांक i, besपंचांगult = 0;
	अचिन्हित पूर्णांक maxmult = (1 << width) - 1;

	अगर (!(clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)) अणु
		besपंचांगult = rate / orig_parent_rate;

		/* Make sure we करोn't end up with a 0 multiplier */
		अगर ((besपंचांगult == 0) &&
		    !(mult->flags & CLK_MULTIPLIER_ZERO_BYPASS))
			besपंचांगult = 1;

		/* Make sure we करोn't overflow the multiplier */
		अगर (besपंचांगult > maxmult)
			besपंचांगult = maxmult;

		वापस besपंचांगult;
	पूर्ण

	क्रम (i = 1; i < maxmult; i++) अणु
		अगर (rate == orig_parent_rate * i) अणु
			/*
			 * This is the best हाल क्रम us अगर we have a
			 * perfect match without changing the parent
			 * rate.
			 */
			*best_parent_rate = orig_parent_rate;
			वापस i;
		पूर्ण

		parent_rate = clk_hw_round_rate(clk_hw_get_parent(hw),
						rate / i);
		current_rate = parent_rate * i;

		अगर (__is_best_rate(rate, current_rate, best_rate, flags)) अणु
			besपंचांगult = i;
			best_rate = current_rate;
			*best_parent_rate = parent_rate;
		पूर्ण
	पूर्ण

	वापस besपंचांगult;
पूर्ण

अटल दीर्घ clk_multiplier_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_multiplier *mult = to_clk_multiplier(hw);
	अचिन्हित दीर्घ factor = __besपंचांगult(hw, rate, parent_rate,
					  mult->width, mult->flags);

	वापस *parent_rate * factor;
पूर्ण

अटल पूर्णांक clk_multiplier_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_multiplier *mult = to_clk_multiplier(hw);
	अचिन्हित दीर्घ factor = __get_mult(mult, rate, parent_rate);
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित दीर्घ val;

	अगर (mult->lock)
		spin_lock_irqsave(mult->lock, flags);
	अन्यथा
		__acquire(mult->lock);

	val = clk_mult_पढ़ोl(mult);
	val &= ~GENMASK(mult->width + mult->shअगरt - 1, mult->shअगरt);
	val |= factor << mult->shअगरt;
	clk_mult_ग_लिखोl(mult, val);

	अगर (mult->lock)
		spin_unlock_irqrestore(mult->lock, flags);
	अन्यथा
		__release(mult->lock);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops clk_multiplier_ops = अणु
	.recalc_rate	= clk_multiplier_recalc_rate,
	.round_rate	= clk_multiplier_round_rate,
	.set_rate	= clk_multiplier_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_multiplier_ops);
