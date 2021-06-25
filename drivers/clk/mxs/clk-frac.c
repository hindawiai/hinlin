<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश "clk.h"

/**
 * काष्ठा clk_frac - mxs fractional भागider घड़ी
 * @hw: clk_hw क्रम the fractional भागider घड़ी
 * @reg: रेजिस्टर address
 * @shअगरt: the भागider bit shअगरt
 * @width: the भागider bit width
 * @busy: busy bit shअगरt
 *
 * The घड़ी is an adjustable fractional भागider with a busy bit to रुको
 * when the भागider is adjusted.
 */
काष्ठा clk_frac अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg;
	u8 shअगरt;
	u8 width;
	u8 busy;
पूर्ण;

#घोषणा to_clk_frac(_hw) container_of(_hw, काष्ठा clk_frac, hw)

अटल अचिन्हित दीर्घ clk_frac_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_frac *frac = to_clk_frac(hw);
	u32 भाग;
	u64 पंचांगp_rate;

	भाग = पढ़ोl_relaxed(frac->reg) >> frac->shअगरt;
	भाग &= (1 << frac->width) - 1;

	पंचांगp_rate = (u64)parent_rate * भाग;
	वापस पंचांगp_rate >> frac->width;
पूर्ण

अटल दीर्घ clk_frac_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_frac *frac = to_clk_frac(hw);
	अचिन्हित दीर्घ parent_rate = *prate;
	u32 भाग;
	u64 पंचांगp, पंचांगp_rate, result;

	अगर (rate > parent_rate)
		वापस -EINVAL;

	पंचांगp = rate;
	पंचांगp <<= frac->width;
	करो_भाग(पंचांगp, parent_rate);
	भाग = पंचांगp;

	अगर (!भाग)
		वापस -EINVAL;

	पंचांगp_rate = (u64)parent_rate * भाग;
	result = पंचांगp_rate >> frac->width;
	अगर ((result << frac->width) < पंचांगp_rate)
		result += 1;
	वापस result;
पूर्ण

अटल पूर्णांक clk_frac_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_frac *frac = to_clk_frac(hw);
	अचिन्हित दीर्घ flags;
	u32 भाग, val;
	u64 पंचांगp;

	अगर (rate > parent_rate)
		वापस -EINVAL;

	पंचांगp = rate;
	पंचांगp <<= frac->width;
	करो_भाग(पंचांगp, parent_rate);
	भाग = पंचांगp;

	अगर (!भाग)
		वापस -EINVAL;

	spin_lock_irqsave(&mxs_lock, flags);

	val = पढ़ोl_relaxed(frac->reg);
	val &= ~(((1 << frac->width) - 1) << frac->shअगरt);
	val |= भाग << frac->shअगरt;
	ग_लिखोl_relaxed(val, frac->reg);

	spin_unlock_irqrestore(&mxs_lock, flags);

	वापस mxs_clk_रुको(frac->reg, frac->busy);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_frac_ops = अणु
	.recalc_rate = clk_frac_recalc_rate,
	.round_rate = clk_frac_round_rate,
	.set_rate = clk_frac_set_rate,
पूर्ण;

काष्ठा clk *mxs_clk_frac(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			 व्योम __iomem *reg, u8 shअगरt, u8 width, u8 busy)
अणु
	काष्ठा clk_frac *frac;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	frac = kzalloc(माप(*frac), GFP_KERNEL);
	अगर (!frac)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_frac_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = (parent_name ? &parent_name: शून्य);
	init.num_parents = (parent_name ? 1 : 0);

	frac->reg = reg;
	frac->shअगरt = shअगरt;
	frac->width = width;
	frac->busy = busy;
	frac->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &frac->hw);
	अगर (IS_ERR(clk))
		kमुक्त(frac);

	वापस clk;
पूर्ण
