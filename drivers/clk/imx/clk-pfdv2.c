<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017~2018 NXP
 *
 * Author: Dong Aisheng <aisheng.करोng@nxp.com>
 *
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/slab.h>

#समावेश "clk.h"

/**
 * काष्ठा clk_pfdv2 - IMX PFD घड़ी
 * @hw:		घड़ी source
 * @reg:	PFD रेजिस्टर address
 * @gate_bit:	Gate bit offset
 * @vld_bit:	Valid bit offset
 * @frac_off:	PLL Fractional Divider offset
 */

काष्ठा clk_pfdv2 अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	u8		gate_bit;
	u8		vld_bit;
	u8		frac_off;
पूर्ण;

#घोषणा to_clk_pfdv2(_hw) container_of(_hw, काष्ठा clk_pfdv2, hw)

#घोषणा CLK_PFDV2_FRAC_MASK 0x3f

#घोषणा LOCK_TIMEOUT_US		USEC_PER_MSEC

अटल DEFINE_SPINLOCK(pfd_lock);

अटल पूर्णांक clk_pfdv2_रुको(काष्ठा clk_pfdv2 *pfd)
अणु
	u32 val;

	वापस पढ़ोl_poll_समयout(pfd->reg, val, val & (1 << pfd->vld_bit),
				  0, LOCK_TIMEOUT_US);
पूर्ण

अटल पूर्णांक clk_pfdv2_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pfdv2 *pfd = to_clk_pfdv2(hw);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&pfd_lock, flags);
	val = पढ़ोl_relaxed(pfd->reg);
	val &= ~(1 << pfd->gate_bit);
	ग_लिखोl_relaxed(val, pfd->reg);
	spin_unlock_irqrestore(&pfd_lock, flags);

	वापस clk_pfdv2_रुको(pfd);
पूर्ण

अटल व्योम clk_pfdv2_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pfdv2 *pfd = to_clk_pfdv2(hw);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&pfd_lock, flags);
	val = पढ़ोl_relaxed(pfd->reg);
	val |= (1 << pfd->gate_bit);
	ग_लिखोl_relaxed(val, pfd->reg);
	spin_unlock_irqrestore(&pfd_lock, flags);
पूर्ण

अटल अचिन्हित दीर्घ clk_pfdv2_recalc_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pfdv2 *pfd = to_clk_pfdv2(hw);
	u64 पंचांगp = parent_rate;
	u8 frac;

	frac = (पढ़ोl_relaxed(pfd->reg) >> pfd->frac_off)
		& CLK_PFDV2_FRAC_MASK;

	अगर (!frac) अणु
		pr_debug("clk_pfdv2: %s invalid pfd frac value 0\n",
			 clk_hw_get_name(hw));
		वापस 0;
	पूर्ण

	पंचांगp *= 18;
	करो_भाग(पंचांगp, frac);

	वापस पंचांगp;
पूर्ण

अटल पूर्णांक clk_pfdv2_determine_rate(काष्ठा clk_hw *hw,
				    काष्ठा clk_rate_request *req)
अणु
	अचिन्हित दीर्घ parent_rates[] = अणु
					480000000,
					528000000,
					req->best_parent_rate
				       पूर्ण;
	अचिन्हित दीर्घ best_rate = -1UL, rate = req->rate;
	अचिन्हित दीर्घ best_parent_rate = req->best_parent_rate;
	u64 पंचांगp;
	u8 frac;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(parent_rates); i++) अणु
		पंचांगp = parent_rates[i];
		पंचांगp = पंचांगp * 18 + rate / 2;
		करो_भाग(पंचांगp, rate);
		frac = पंचांगp;

		अगर (frac < 12)
			frac = 12;
		अन्यथा अगर (frac > 35)
			frac = 35;

		पंचांगp = parent_rates[i];
		पंचांगp *= 18;
		करो_भाग(पंचांगp, frac);

		अगर (असल(पंचांगp - req->rate) < असल(best_rate - req->rate)) अणु
			best_rate = पंचांगp;
			best_parent_rate = parent_rates[i];
		पूर्ण
	पूर्ण

	req->best_parent_rate = best_parent_rate;
	req->rate = best_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक clk_pfdv2_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pfdv2 *pfd = to_clk_pfdv2(hw);

	अगर (पढ़ोl_relaxed(pfd->reg) & (1 << pfd->gate_bit))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक clk_pfdv2_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pfdv2 *pfd = to_clk_pfdv2(hw);
	अचिन्हित दीर्घ flags;
	u64 पंचांगp = parent_rate;
	u32 val;
	u8 frac;

	अगर (!rate)
		वापस -EINVAL;

	/* PFD can NOT change rate without gating */
	WARN_ON(clk_pfdv2_is_enabled(hw));

	पंचांगp = पंचांगp * 18 + rate / 2;
	करो_भाग(पंचांगp, rate);
	frac = पंचांगp;
	अगर (frac < 12)
		frac = 12;
	अन्यथा अगर (frac > 35)
		frac = 35;

	spin_lock_irqsave(&pfd_lock, flags);
	val = पढ़ोl_relaxed(pfd->reg);
	val &= ~(CLK_PFDV2_FRAC_MASK << pfd->frac_off);
	val |= frac << pfd->frac_off;
	ग_लिखोl_relaxed(val, pfd->reg);
	spin_unlock_irqrestore(&pfd_lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pfdv2_ops = अणु
	.enable		= clk_pfdv2_enable,
	.disable	= clk_pfdv2_disable,
	.recalc_rate	= clk_pfdv2_recalc_rate,
	.determine_rate	= clk_pfdv2_determine_rate,
	.set_rate	= clk_pfdv2_set_rate,
	.is_enabled     = clk_pfdv2_is_enabled,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_pfdv2(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			     व्योम __iomem *reg, u8 idx)
अणु
	काष्ठा clk_init_data init;
	काष्ठा clk_pfdv2 *pfd;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	WARN_ON(idx > 3);

	pfd = kzalloc(माप(*pfd), GFP_KERNEL);
	अगर (!pfd)
		वापस ERR_PTR(-ENOMEM);

	pfd->reg = reg;
	pfd->gate_bit = (idx + 1) * 8 - 1;
	pfd->vld_bit = pfd->gate_bit - 1;
	pfd->frac_off = idx * 8;

	init.name = name;
	init.ops = &clk_pfdv2_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = CLK_SET_RATE_GATE | CLK_SET_RATE_PARENT;

	pfd->hw.init = &init;

	hw = &pfd->hw;
	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(pfd);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
