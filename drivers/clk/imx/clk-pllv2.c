<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>

#समावेश <यंत्र/भाग64.h>

#समावेश "clk.h"

#घोषणा to_clk_pllv2(clk) (container_of(clk, काष्ठा clk_pllv2, clk))

/* PLL Register Offsets */
#घोषणा MXC_PLL_DP_CTL			0x00
#घोषणा MXC_PLL_DP_CONFIG		0x04
#घोषणा MXC_PLL_DP_OP			0x08
#घोषणा MXC_PLL_DP_MFD			0x0C
#घोषणा MXC_PLL_DP_MFN			0x10
#घोषणा MXC_PLL_DP_MFNMINUS		0x14
#घोषणा MXC_PLL_DP_MFNPLUS		0x18
#घोषणा MXC_PLL_DP_HFS_OP		0x1C
#घोषणा MXC_PLL_DP_HFS_MFD		0x20
#घोषणा MXC_PLL_DP_HFS_MFN		0x24
#घोषणा MXC_PLL_DP_MFN_TOGC		0x28
#घोषणा MXC_PLL_DP_DESTAT		0x2c

/* PLL Register Bit definitions */
#घोषणा MXC_PLL_DP_CTL_MUL_CTRL		0x2000
#घोषणा MXC_PLL_DP_CTL_DPDCK0_2_EN	0x1000
#घोषणा MXC_PLL_DP_CTL_DPDCK0_2_OFFSET	12
#घोषणा MXC_PLL_DP_CTL_ADE		0x800
#घोषणा MXC_PLL_DP_CTL_REF_CLK_DIV	0x400
#घोषणा MXC_PLL_DP_CTL_REF_CLK_SEL_MASK	(3 << 8)
#घोषणा MXC_PLL_DP_CTL_REF_CLK_SEL_OFFSET	8
#घोषणा MXC_PLL_DP_CTL_HFSM		0x80
#घोषणा MXC_PLL_DP_CTL_PRE		0x40
#घोषणा MXC_PLL_DP_CTL_UPEN		0x20
#घोषणा MXC_PLL_DP_CTL_RST		0x10
#घोषणा MXC_PLL_DP_CTL_RCP		0x8
#घोषणा MXC_PLL_DP_CTL_PLM		0x4
#घोषणा MXC_PLL_DP_CTL_BRM0		0x2
#घोषणा MXC_PLL_DP_CTL_LRF		0x1

#घोषणा MXC_PLL_DP_CONFIG_BIST		0x8
#घोषणा MXC_PLL_DP_CONFIG_SJC_CE	0x4
#घोषणा MXC_PLL_DP_CONFIG_AREN		0x2
#घोषणा MXC_PLL_DP_CONFIG_LDREQ		0x1

#घोषणा MXC_PLL_DP_OP_MFI_OFFSET	4
#घोषणा MXC_PLL_DP_OP_MFI_MASK		(0xF << 4)
#घोषणा MXC_PLL_DP_OP_PDF_OFFSET	0
#घोषणा MXC_PLL_DP_OP_PDF_MASK		0xF

#घोषणा MXC_PLL_DP_MFD_OFFSET		0
#घोषणा MXC_PLL_DP_MFD_MASK		0x07FFFFFF

#घोषणा MXC_PLL_DP_MFN_OFFSET		0x0
#घोषणा MXC_PLL_DP_MFN_MASK		0x07FFFFFF

#घोषणा MXC_PLL_DP_MFN_TOGC_TOG_DIS	(1 << 17)
#घोषणा MXC_PLL_DP_MFN_TOGC_TOG_EN	(1 << 16)
#घोषणा MXC_PLL_DP_MFN_TOGC_CNT_OFFSET	0x0
#घोषणा MXC_PLL_DP_MFN_TOGC_CNT_MASK	0xFFFF

#घोषणा MXC_PLL_DP_DESTAT_TOG_SEL	(1 << 31)
#घोषणा MXC_PLL_DP_DESTAT_MFN		0x07FFFFFF

#घोषणा MAX_DPLL_WAIT_TRIES	1000 /* 1000 * udelay(1) = 1ms */

काष्ठा clk_pllv2 अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*base;
पूर्ण;

अटल अचिन्हित दीर्घ __clk_pllv2_recalc_rate(अचिन्हित दीर्घ parent_rate,
		u32 dp_ctl, u32 dp_op, u32 dp_mfd, u32 dp_mfn)
अणु
	दीर्घ mfi, mfn, mfd, pdf, ref_clk;
	अचिन्हित दीर्घ dbl;
	u64 temp;

	dbl = dp_ctl & MXC_PLL_DP_CTL_DPDCK0_2_EN;

	pdf = dp_op & MXC_PLL_DP_OP_PDF_MASK;
	mfi = (dp_op & MXC_PLL_DP_OP_MFI_MASK) >> MXC_PLL_DP_OP_MFI_OFFSET;
	mfi = (mfi <= 5) ? 5 : mfi;
	mfd = dp_mfd & MXC_PLL_DP_MFD_MASK;
	mfn = dp_mfn & MXC_PLL_DP_MFN_MASK;
	mfn = sign_extend32(mfn, 26);

	ref_clk = 2 * parent_rate;
	अगर (dbl != 0)
		ref_clk *= 2;

	ref_clk /= (pdf + 1);
	temp = (u64) ref_clk * असल(mfn);
	करो_भाग(temp, mfd + 1);
	अगर (mfn < 0)
		temp = (ref_clk * mfi) - temp;
	अन्यथा
		temp = (ref_clk * mfi) + temp;

	वापस temp;
पूर्ण

अटल अचिन्हित दीर्घ clk_pllv2_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	u32 dp_op, dp_mfd, dp_mfn, dp_ctl;
	व्योम __iomem *pllbase;
	काष्ठा clk_pllv2 *pll = to_clk_pllv2(hw);

	pllbase = pll->base;

	dp_ctl = __raw_पढ़ोl(pllbase + MXC_PLL_DP_CTL);
	dp_op = __raw_पढ़ोl(pllbase + MXC_PLL_DP_OP);
	dp_mfd = __raw_पढ़ोl(pllbase + MXC_PLL_DP_MFD);
	dp_mfn = __raw_पढ़ोl(pllbase + MXC_PLL_DP_MFN);

	वापस __clk_pllv2_recalc_rate(parent_rate, dp_ctl, dp_op, dp_mfd, dp_mfn);
पूर्ण

अटल पूर्णांक __clk_pllv2_set_rate(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate,
		u32 *dp_op, u32 *dp_mfd, u32 *dp_mfn)
अणु
	u32 reg;
	दीर्घ mfi, pdf, mfn, mfd = 999999;
	u64 temp64;
	अचिन्हित दीर्घ quad_parent_rate;

	quad_parent_rate = 4 * parent_rate;
	pdf = mfi = -1;
	जबतक (++pdf < 16 && mfi < 5)
		mfi = rate * (pdf+1) / quad_parent_rate;
	अगर (mfi > 15)
		वापस -EINVAL;
	pdf--;

	temp64 = rate * (pdf + 1) - quad_parent_rate * mfi;
	करो_भाग(temp64, quad_parent_rate / 1000000);
	mfn = (दीर्घ)temp64;

	reg = mfi << 4 | pdf;

	*dp_op = reg;
	*dp_mfd = mfd;
	*dp_mfn = mfn;

	वापस 0;
पूर्ण

अटल पूर्णांक clk_pllv2_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pllv2 *pll = to_clk_pllv2(hw);
	व्योम __iomem *pllbase;
	u32 dp_ctl, dp_op, dp_mfd, dp_mfn;
	पूर्णांक ret;

	pllbase = pll->base;


	ret = __clk_pllv2_set_rate(rate, parent_rate, &dp_op, &dp_mfd, &dp_mfn);
	अगर (ret)
		वापस ret;

	dp_ctl = __raw_पढ़ोl(pllbase + MXC_PLL_DP_CTL);
	/* use dpdck0_2 */
	__raw_ग_लिखोl(dp_ctl | 0x1000L, pllbase + MXC_PLL_DP_CTL);

	__raw_ग_लिखोl(dp_op, pllbase + MXC_PLL_DP_OP);
	__raw_ग_लिखोl(dp_mfd, pllbase + MXC_PLL_DP_MFD);
	__raw_ग_लिखोl(dp_mfn, pllbase + MXC_PLL_DP_MFN);

	वापस 0;
पूर्ण

अटल दीर्घ clk_pllv2_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *prate)
अणु
	u32 dp_op, dp_mfd, dp_mfn;
	पूर्णांक ret;

	ret = __clk_pllv2_set_rate(rate, *prate, &dp_op, &dp_mfd, &dp_mfn);
	अगर (ret)
		वापस ret;

	वापस __clk_pllv2_recalc_rate(*prate, MXC_PLL_DP_CTL_DPDCK0_2_EN,
			dp_op, dp_mfd, dp_mfn);
पूर्ण

अटल पूर्णांक clk_pllv2_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pllv2 *pll = to_clk_pllv2(hw);
	u32 reg;
	व्योम __iomem *pllbase;
	पूर्णांक i = 0;

	pllbase = pll->base;
	reg = __raw_पढ़ोl(pllbase + MXC_PLL_DP_CTL) | MXC_PLL_DP_CTL_UPEN;
	__raw_ग_लिखोl(reg, pllbase + MXC_PLL_DP_CTL);

	/* Wait क्रम lock */
	करो अणु
		reg = __raw_पढ़ोl(pllbase + MXC_PLL_DP_CTL);
		अगर (reg & MXC_PLL_DP_CTL_LRF)
			अवरोध;

		udelay(1);
	पूर्ण जबतक (++i < MAX_DPLL_WAIT_TRIES);

	अगर (i == MAX_DPLL_WAIT_TRIES) अणु
		pr_err("MX5: pll locking failed\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम clk_pllv2_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pllv2 *pll = to_clk_pllv2(hw);
	u32 reg;
	व्योम __iomem *pllbase;

	pllbase = pll->base;
	reg = __raw_पढ़ोl(pllbase + MXC_PLL_DP_CTL) & ~MXC_PLL_DP_CTL_UPEN;
	__raw_ग_लिखोl(reg, pllbase + MXC_PLL_DP_CTL);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pllv2_ops = अणु
	.prepare = clk_pllv2_prepare,
	.unprepare = clk_pllv2_unprepare,
	.recalc_rate = clk_pllv2_recalc_rate,
	.round_rate = clk_pllv2_round_rate,
	.set_rate = clk_pllv2_set_rate,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_pllv2(स्थिर अक्षर *name, स्थिर अक्षर *parent,
		व्योम __iomem *base)
अणु
	काष्ठा clk_pllv2 *pll;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	pll->base = base;

	init.name = name;
	init.ops = &clk_pllv2_ops;
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
