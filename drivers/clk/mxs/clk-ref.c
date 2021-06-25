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
 * काष्ठा clk_ref - mxs reference घड़ी
 * @hw: clk_hw क्रम the reference घड़ी
 * @reg: रेजिस्टर address
 * @idx: the index of the reference घड़ी within the same रेजिस्टर
 *
 * The mxs reference घड़ी sources from pll.  Every 4 reference घड़ीs share
 * one रेजिस्टर space, and @idx is used to identअगरy them.  Each reference
 * घड़ी has a gate control and a fractional * भागider.  The rate is calculated
 * as pll rate  * (18 / FRAC), where FRAC = 18 ~ 35.
 */
काष्ठा clk_ref अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg;
	u8 idx;
पूर्ण;

#घोषणा to_clk_ref(_hw) container_of(_hw, काष्ठा clk_ref, hw)

अटल पूर्णांक clk_ref_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_ref *ref = to_clk_ref(hw);

	ग_लिखोl_relaxed(1 << ((ref->idx + 1) * 8 - 1), ref->reg + CLR);

	वापस 0;
पूर्ण

अटल व्योम clk_ref_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_ref *ref = to_clk_ref(hw);

	ग_लिखोl_relaxed(1 << ((ref->idx + 1) * 8 - 1), ref->reg + SET);
पूर्ण

अटल अचिन्हित दीर्घ clk_ref_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_ref *ref = to_clk_ref(hw);
	u64 पंचांगp = parent_rate;
	u8 frac = (पढ़ोl_relaxed(ref->reg) >> (ref->idx * 8)) & 0x3f;

	पंचांगp *= 18;
	करो_भाग(पंचांगp, frac);

	वापस पंचांगp;
पूर्ण

अटल दीर्घ clk_ref_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *prate)
अणु
	अचिन्हित दीर्घ parent_rate = *prate;
	u64 पंचांगp = parent_rate;
	u8 frac;

	पंचांगp = पंचांगp * 18 + rate / 2;
	करो_भाग(पंचांगp, rate);
	frac = पंचांगp;

	अगर (frac < 18)
		frac = 18;
	अन्यथा अगर (frac > 35)
		frac = 35;

	पंचांगp = parent_rate;
	पंचांगp *= 18;
	करो_भाग(पंचांगp, frac);

	वापस पंचांगp;
पूर्ण

अटल पूर्णांक clk_ref_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_ref *ref = to_clk_ref(hw);
	अचिन्हित दीर्घ flags;
	u64 पंचांगp = parent_rate;
	u32 val;
	u8 frac, shअगरt = ref->idx * 8;

	पंचांगp = पंचांगp * 18 + rate / 2;
	करो_भाग(पंचांगp, rate);
	frac = पंचांगp;

	अगर (frac < 18)
		frac = 18;
	अन्यथा अगर (frac > 35)
		frac = 35;

	spin_lock_irqsave(&mxs_lock, flags);

	val = पढ़ोl_relaxed(ref->reg);
	val &= ~(0x3f << shअगरt);
	val |= frac << shअगरt;
	ग_लिखोl_relaxed(val, ref->reg);

	spin_unlock_irqrestore(&mxs_lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_ref_ops = अणु
	.enable		= clk_ref_enable,
	.disable	= clk_ref_disable,
	.recalc_rate	= clk_ref_recalc_rate,
	.round_rate	= clk_ref_round_rate,
	.set_rate	= clk_ref_set_rate,
पूर्ण;

काष्ठा clk *mxs_clk_ref(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			व्योम __iomem *reg, u8 idx)
अणु
	काष्ठा clk_ref *ref;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	ref = kzalloc(माप(*ref), GFP_KERNEL);
	अगर (!ref)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_ref_ops;
	init.flags = 0;
	init.parent_names = (parent_name ? &parent_name: शून्य);
	init.num_parents = (parent_name ? 1 : 0);

	ref->reg = reg;
	ref->idx = idx;
	ref->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &ref->hw);
	अगर (IS_ERR(clk))
		kमुक्त(ref);

	वापस clk;
पूर्ण
