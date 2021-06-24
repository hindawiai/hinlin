<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017~2018 NXP
 *
 * Author: Dong Aisheng <aisheng.करोng@nxp.com>
 *
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/slab.h>

#समावेश "clk.h"

/* PLL Control Status Register (xPLLCSR) */
#घोषणा PLL_CSR_OFFSET		0x0
#घोषणा PLL_VLD			BIT(24)
#घोषणा PLL_EN			BIT(0)

/* PLL Configuration Register (xPLLCFG) */
#घोषणा PLL_CFG_OFFSET		0x08
#घोषणा BP_PLL_MULT		16
#घोषणा BM_PLL_MULT		(0x7f << 16)

/* PLL Numerator Register (xPLLNUM) */
#घोषणा PLL_NUM_OFFSET		0x10

/* PLL Denominator Register (xPLLDENOM) */
#घोषणा PLL_DENOM_OFFSET	0x14

#घोषणा MAX_MFD			0x3fffffff
#घोषणा DEFAULT_MFD		1000000

काष्ठा clk_pllv4 अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*base;
पूर्ण;

/* Valid PLL MULT Table */
अटल स्थिर पूर्णांक pllv4_mult_table[] = अणु33, 27, 22, 20, 17, 16पूर्ण;

#घोषणा to_clk_pllv4(__hw) container_of(__hw, काष्ठा clk_pllv4, hw)

#घोषणा LOCK_TIMEOUT_US		USEC_PER_MSEC

अटल अंतरभूत पूर्णांक clk_pllv4_रुको_lock(काष्ठा clk_pllv4 *pll)
अणु
	u32 csr;

	वापस पढ़ोl_poll_समयout(pll->base  + PLL_CSR_OFFSET,
				  csr, csr & PLL_VLD, 0, LOCK_TIMEOUT_US);
पूर्ण

अटल पूर्णांक clk_pllv4_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pllv4 *pll = to_clk_pllv4(hw);

	अगर (पढ़ोl_relaxed(pll->base) & PLL_EN)
		वापस 1;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ clk_pllv4_recalc_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pllv4 *pll = to_clk_pllv4(hw);
	u32 mult, mfn, mfd;
	u64 temp64;

	mult = पढ़ोl_relaxed(pll->base + PLL_CFG_OFFSET);
	mult &= BM_PLL_MULT;
	mult >>= BP_PLL_MULT;

	mfn = पढ़ोl_relaxed(pll->base + PLL_NUM_OFFSET);
	mfd = पढ़ोl_relaxed(pll->base + PLL_DENOM_OFFSET);
	temp64 = parent_rate;
	temp64 *= mfn;
	करो_भाग(temp64, mfd);

	वापस (parent_rate * mult) + (u32)temp64;
पूर्ण

अटल दीर्घ clk_pllv4_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ *prate)
अणु
	अचिन्हित दीर्घ parent_rate = *prate;
	अचिन्हित दीर्घ round_rate, i;
	u32 mfn, mfd = DEFAULT_MFD;
	bool found = false;
	u64 temp64;

	क्रम (i = 0; i < ARRAY_SIZE(pllv4_mult_table); i++) अणु
		round_rate = parent_rate * pllv4_mult_table[i];
		अगर (rate >= round_rate) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		pr_warn("%s: unable to round rate %lu, parent rate %lu\n",
			clk_hw_get_name(hw), rate, parent_rate);
		वापस 0;
	पूर्ण

	अगर (parent_rate <= MAX_MFD)
		mfd = parent_rate;

	temp64 = (u64)(rate - round_rate);
	temp64 *= mfd;
	करो_भाग(temp64, parent_rate);
	mfn = temp64;

	/*
	 * NOTE: The value of numerator must always be configured to be
	 * less than the value of the denominator. If we can't get a proper
	 * pair of mfn/mfd, we simply वापस the round_rate without using
	 * the frac part.
	 */
	अगर (mfn >= mfd)
		वापस round_rate;

	temp64 = (u64)parent_rate;
	temp64 *= mfn;
	करो_भाग(temp64, mfd);

	वापस round_rate + (u32)temp64;
पूर्ण

अटल bool clk_pllv4_is_valid_mult(अचिन्हित पूर्णांक mult)
अणु
	पूर्णांक i;

	/* check अगर mult is in valid MULT table */
	क्रम (i = 0; i < ARRAY_SIZE(pllv4_mult_table); i++) अणु
		अगर (pllv4_mult_table[i] == mult)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक clk_pllv4_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pllv4 *pll = to_clk_pllv4(hw);
	u32 val, mult, mfn, mfd = DEFAULT_MFD;
	u64 temp64;

	mult = rate / parent_rate;

	अगर (!clk_pllv4_is_valid_mult(mult))
		वापस -EINVAL;

	अगर (parent_rate <= MAX_MFD)
		mfd = parent_rate;

	temp64 = (u64)(rate - mult * parent_rate);
	temp64 *= mfd;
	करो_भाग(temp64, parent_rate);
	mfn = temp64;

	val = पढ़ोl_relaxed(pll->base + PLL_CFG_OFFSET);
	val &= ~BM_PLL_MULT;
	val |= mult << BP_PLL_MULT;
	ग_लिखोl_relaxed(val, pll->base + PLL_CFG_OFFSET);

	ग_लिखोl_relaxed(mfn, pll->base + PLL_NUM_OFFSET);
	ग_लिखोl_relaxed(mfd, pll->base + PLL_DENOM_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_pllv4_prepare(काष्ठा clk_hw *hw)
अणु
	u32 val;
	काष्ठा clk_pllv4 *pll = to_clk_pllv4(hw);

	val = पढ़ोl_relaxed(pll->base);
	val |= PLL_EN;
	ग_लिखोl_relaxed(val, pll->base);

	वापस clk_pllv4_रुको_lock(pll);
पूर्ण

अटल व्योम clk_pllv4_unprepare(काष्ठा clk_hw *hw)
अणु
	u32 val;
	काष्ठा clk_pllv4 *pll = to_clk_pllv4(hw);

	val = पढ़ोl_relaxed(pll->base);
	val &= ~PLL_EN;
	ग_लिखोl_relaxed(val, pll->base);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pllv4_ops = अणु
	.recalc_rate	= clk_pllv4_recalc_rate,
	.round_rate	= clk_pllv4_round_rate,
	.set_rate	= clk_pllv4_set_rate,
	.prepare	= clk_pllv4_prepare,
	.unprepare	= clk_pllv4_unprepare,
	.is_prepared	= clk_pllv4_is_prepared,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_pllv4(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			  व्योम __iomem *base)
अणु
	काष्ठा clk_pllv4 *pll;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	pll->base = base;

	init.name = name;
	init.ops = &clk_pllv4_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = CLK_SET_RATE_GATE;

	pll->hw.init = &init;

	hw = &pll->hw;
	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(pll);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
