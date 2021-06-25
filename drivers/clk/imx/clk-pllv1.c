<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bits.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>

#समावेश "clk.h"

/**
 * pll v1
 *
 * @clk_hw	घड़ी source
 * @parent	the parent घड़ी name
 * @base	base address of pll रेजिस्टरs
 *
 * PLL घड़ी version 1, found on i.MX1/21/25/27/31/35
 */

#घोषणा MFN_BITS	(10)
#घोषणा MFN_SIGN	(BIT(MFN_BITS - 1))
#घोषणा MFN_MASK	(MFN_SIGN - 1)

काष्ठा clk_pllv1 अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*base;
	क्रमागत imx_pllv1_type type;
पूर्ण;

#घोषणा to_clk_pllv1(clk) (container_of(clk, काष्ठा clk_pllv1, clk))

अटल अंतरभूत bool is_imx1_pllv1(काष्ठा clk_pllv1 *pll)
अणु
	वापस pll->type == IMX_PLLV1_IMX1;
पूर्ण

अटल अंतरभूत bool is_imx21_pllv1(काष्ठा clk_pllv1 *pll)
अणु
	वापस pll->type == IMX_PLLV1_IMX21;
पूर्ण

अटल अंतरभूत bool is_imx27_pllv1(काष्ठा clk_pllv1 *pll)
अणु
	वापस pll->type == IMX_PLLV1_IMX27;
पूर्ण

अटल अंतरभूत bool mfn_is_negative(काष्ठा clk_pllv1 *pll, अचिन्हित पूर्णांक mfn)
अणु
	वापस !is_imx1_pllv1(pll) && !is_imx21_pllv1(pll) && (mfn & MFN_SIGN);
पूर्ण

अटल अचिन्हित दीर्घ clk_pllv1_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pllv1 *pll = to_clk_pllv1(hw);
	अचिन्हित दीर्घ दीर्घ ull;
	पूर्णांक mfn_असल;
	अचिन्हित पूर्णांक mfi, mfn, mfd, pd;
	u32 reg;
	अचिन्हित दीर्घ rate;

	reg = पढ़ोl(pll->base);

	/*
	 * Get the resulting घड़ी rate from a PLL रेजिस्टर value and the input
	 * frequency. PLLs with this रेजिस्टर layout can be found on i.MX1,
	 * i.MX21, i.MX27 and i,MX31
	 *
	 *                  mfi + mfn / (mfd + 1)
	 *  f = 2 * f_ref * --------------------
	 *                        pd + 1
	 */

	mfi = (reg >> 10) & 0xf;
	mfn = reg & 0x3ff;
	mfd = (reg >> 16) & 0x3ff;
	pd =  (reg >> 26) & 0xf;

	mfi = mfi <= 5 ? 5 : mfi;

	mfn_असल = mfn;

	/*
	 * On all i.MXs except i.MX1 and i.MX21 mfn is a 10bit
	 * 2's complements number.
	 * On i.MX27 the bit 9 is the sign bit.
	 */
	अगर (mfn_is_negative(pll, mfn)) अणु
		अगर (is_imx27_pllv1(pll))
			mfn_असल = mfn & MFN_MASK;
		अन्यथा
			mfn_असल = BIT(MFN_BITS) - mfn;
	पूर्ण

	rate = parent_rate * 2;
	rate /= pd + 1;

	ull = (अचिन्हित दीर्घ दीर्घ)rate * mfn_असल;

	करो_भाग(ull, mfd + 1);

	अगर (mfn_is_negative(pll, mfn))
		ull = (rate * mfi) - ull;
	अन्यथा
		ull = (rate * mfi) + ull;

	वापस ull;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pllv1_ops = अणु
	.recalc_rate = clk_pllv1_recalc_rate,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_pllv1(क्रमागत imx_pllv1_type type, स्थिर अक्षर *name,
		स्थिर अक्षर *parent, व्योम __iomem *base)
अणु
	काष्ठा clk_pllv1 *pll;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	pll = kदो_स्मृति(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	pll->base = base;
	pll->type = type;

	init.name = name;
	init.ops = &clk_pllv1_ops;
	init.flags = 0;
	init.parent_names = &parent;
	init.num_parents = 1;

	pll->hw.init = &init;
	hw = &pll->hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(pll);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
