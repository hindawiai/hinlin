<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 * Copyright 2012 Linaro Ltd.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/err.h>
#समावेश "clk.h"

#घोषणा PLL_NUM_OFFSET		0x10
#घोषणा PLL_DENOM_OFFSET	0x20
#घोषणा PLL_IMX7_NUM_OFFSET	0x20
#घोषणा PLL_IMX7_DENOM_OFFSET	0x30

#घोषणा PLL_VF610_NUM_OFFSET	0x20
#घोषणा PLL_VF610_DENOM_OFFSET	0x30

#घोषणा BM_PLL_POWER		(0x1 << 12)
#घोषणा BM_PLL_LOCK		(0x1 << 31)
#घोषणा IMX7_ENET_PLL_POWER	(0x1 << 5)
#घोषणा IMX7_DDR_PLL_POWER	(0x1 << 20)

#घोषणा PLL_LOCK_TIMEOUT	10000

/**
 * काष्ठा clk_pllv3 - IMX PLL घड़ी version 3
 * @hw:		घड़ी source
 * @base:	 base address of PLL रेजिस्टरs
 * @घातer_bit:	 pll घातer bit mask
 * @घातerup_set: set घातer_bit to घातer up the PLL
 * @भाग_mask:	 mask of भागider bits
 * @भाग_shअगरt:	 shअगरt of भागider bits
 * @ref_घड़ी:	reference घड़ी rate
 * @num_offset:	num रेजिस्टर offset
 * @denom_offset: denom रेजिस्टर offset
 *
 * IMX PLL घड़ी version 3, found on i.MX6 series.  Divider क्रम pllv3
 * is actually a multiplier, and always sits at bit 0.
 */
काष्ठा clk_pllv3 अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*base;
	u32		घातer_bit;
	bool		घातerup_set;
	u32		भाग_mask;
	u32		भाग_shअगरt;
	अचिन्हित दीर्घ	ref_घड़ी;
	u32		num_offset;
	u32		denom_offset;
पूर्ण;

#घोषणा to_clk_pllv3(_hw) container_of(_hw, काष्ठा clk_pllv3, hw)

अटल पूर्णांक clk_pllv3_रुको_lock(काष्ठा clk_pllv3 *pll)
अणु
	u32 val = पढ़ोl_relaxed(pll->base) & pll->घातer_bit;

	/* No need to रुको क्रम lock when pll is not घातered up */
	अगर ((pll->घातerup_set && !val) || (!pll->घातerup_set && val))
		वापस 0;

	वापस पढ़ोl_relaxed_poll_समयout(pll->base, val, val & BM_PLL_LOCK,
					  500, PLL_LOCK_TIMEOUT);
पूर्ण

अटल पूर्णांक clk_pllv3_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pllv3 *pll = to_clk_pllv3(hw);
	u32 val;

	val = पढ़ोl_relaxed(pll->base);
	अगर (pll->घातerup_set)
		val |= pll->घातer_bit;
	अन्यथा
		val &= ~pll->घातer_bit;
	ग_लिखोl_relaxed(val, pll->base);

	वापस clk_pllv3_रुको_lock(pll);
पूर्ण

अटल व्योम clk_pllv3_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pllv3 *pll = to_clk_pllv3(hw);
	u32 val;

	val = पढ़ोl_relaxed(pll->base);
	अगर (pll->घातerup_set)
		val &= ~pll->घातer_bit;
	अन्यथा
		val |= pll->घातer_bit;
	ग_लिखोl_relaxed(val, pll->base);
पूर्ण

अटल पूर्णांक clk_pllv3_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pllv3 *pll = to_clk_pllv3(hw);

	अगर (पढ़ोl_relaxed(pll->base) & BM_PLL_LOCK)
		वापस 1;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ clk_pllv3_recalc_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pllv3 *pll = to_clk_pllv3(hw);
	u32 भाग = (पढ़ोl_relaxed(pll->base) >> pll->भाग_shअगरt)  & pll->भाग_mask;

	वापस (भाग == 1) ? parent_rate * 22 : parent_rate * 20;
पूर्ण

अटल दीर्घ clk_pllv3_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ *prate)
अणु
	अचिन्हित दीर्घ parent_rate = *prate;

	वापस (rate >= parent_rate * 22) ? parent_rate * 22 :
					    parent_rate * 20;
पूर्ण

अटल पूर्णांक clk_pllv3_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pllv3 *pll = to_clk_pllv3(hw);
	u32 val, भाग;

	अगर (rate == parent_rate * 22)
		भाग = 1;
	अन्यथा अगर (rate == parent_rate * 20)
		भाग = 0;
	अन्यथा
		वापस -EINVAL;

	val = पढ़ोl_relaxed(pll->base);
	val &= ~(pll->भाग_mask << pll->भाग_shअगरt);
	val |= (भाग << pll->भाग_shअगरt);
	ग_लिखोl_relaxed(val, pll->base);

	वापस clk_pllv3_रुको_lock(pll);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pllv3_ops = अणु
	.prepare	= clk_pllv3_prepare,
	.unprepare	= clk_pllv3_unprepare,
	.is_prepared	= clk_pllv3_is_prepared,
	.recalc_rate	= clk_pllv3_recalc_rate,
	.round_rate	= clk_pllv3_round_rate,
	.set_rate	= clk_pllv3_set_rate,
पूर्ण;

अटल अचिन्हित दीर्घ clk_pllv3_sys_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pllv3 *pll = to_clk_pllv3(hw);
	u32 भाग = पढ़ोl_relaxed(pll->base) & pll->भाग_mask;

	वापस parent_rate * भाग / 2;
पूर्ण

अटल दीर्घ clk_pllv3_sys_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ *prate)
अणु
	अचिन्हित दीर्घ parent_rate = *prate;
	अचिन्हित दीर्घ min_rate = parent_rate * 54 / 2;
	अचिन्हित दीर्घ max_rate = parent_rate * 108 / 2;
	u32 भाग;

	अगर (rate > max_rate)
		rate = max_rate;
	अन्यथा अगर (rate < min_rate)
		rate = min_rate;
	भाग = rate * 2 / parent_rate;

	वापस parent_rate * भाग / 2;
पूर्ण

अटल पूर्णांक clk_pllv3_sys_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pllv3 *pll = to_clk_pllv3(hw);
	अचिन्हित दीर्घ min_rate = parent_rate * 54 / 2;
	अचिन्हित दीर्घ max_rate = parent_rate * 108 / 2;
	u32 val, भाग;

	अगर (rate < min_rate || rate > max_rate)
		वापस -EINVAL;

	भाग = rate * 2 / parent_rate;
	val = पढ़ोl_relaxed(pll->base);
	val &= ~pll->भाग_mask;
	val |= भाग;
	ग_लिखोl_relaxed(val, pll->base);

	वापस clk_pllv3_रुको_lock(pll);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pllv3_sys_ops = अणु
	.prepare	= clk_pllv3_prepare,
	.unprepare	= clk_pllv3_unprepare,
	.is_prepared	= clk_pllv3_is_prepared,
	.recalc_rate	= clk_pllv3_sys_recalc_rate,
	.round_rate	= clk_pllv3_sys_round_rate,
	.set_rate	= clk_pllv3_sys_set_rate,
पूर्ण;

अटल अचिन्हित दीर्घ clk_pllv3_av_recalc_rate(काष्ठा clk_hw *hw,
					      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pllv3 *pll = to_clk_pllv3(hw);
	u32 mfn = पढ़ोl_relaxed(pll->base + pll->num_offset);
	u32 mfd = पढ़ोl_relaxed(pll->base + pll->denom_offset);
	u32 भाग = पढ़ोl_relaxed(pll->base) & pll->भाग_mask;
	u64 temp64 = (u64)parent_rate;

	temp64 *= mfn;
	करो_भाग(temp64, mfd);

	वापस parent_rate * भाग + (अचिन्हित दीर्घ)temp64;
पूर्ण

अटल दीर्घ clk_pllv3_av_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ *prate)
अणु
	अचिन्हित दीर्घ parent_rate = *prate;
	अचिन्हित दीर्घ min_rate = parent_rate * 27;
	अचिन्हित दीर्घ max_rate = parent_rate * 54;
	u32 भाग;
	u32 mfn, mfd = 1000000;
	u32 max_mfd = 0x3FFFFFFF;
	u64 temp64;

	अगर (rate > max_rate)
		rate = max_rate;
	अन्यथा अगर (rate < min_rate)
		rate = min_rate;

	अगर (parent_rate <= max_mfd)
		mfd = parent_rate;

	भाग = rate / parent_rate;
	temp64 = (u64) (rate - भाग * parent_rate);
	temp64 *= mfd;
	करो_भाग(temp64, parent_rate);
	mfn = temp64;

	temp64 = (u64)parent_rate;
	temp64 *= mfn;
	करो_भाग(temp64, mfd);

	वापस parent_rate * भाग + (अचिन्हित दीर्घ)temp64;
पूर्ण

अटल पूर्णांक clk_pllv3_av_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pllv3 *pll = to_clk_pllv3(hw);
	अचिन्हित दीर्घ min_rate = parent_rate * 27;
	अचिन्हित दीर्घ max_rate = parent_rate * 54;
	u32 val, भाग;
	u32 mfn, mfd = 1000000;
	u32 max_mfd = 0x3FFFFFFF;
	u64 temp64;

	अगर (rate < min_rate || rate > max_rate)
		वापस -EINVAL;

	अगर (parent_rate <= max_mfd)
		mfd = parent_rate;

	भाग = rate / parent_rate;
	temp64 = (u64) (rate - भाग * parent_rate);
	temp64 *= mfd;
	करो_भाग(temp64, parent_rate);
	mfn = temp64;

	val = पढ़ोl_relaxed(pll->base);
	val &= ~pll->भाग_mask;
	val |= भाग;
	ग_लिखोl_relaxed(val, pll->base);
	ग_लिखोl_relaxed(mfn, pll->base + pll->num_offset);
	ग_लिखोl_relaxed(mfd, pll->base + pll->denom_offset);

	वापस clk_pllv3_रुको_lock(pll);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pllv3_av_ops = अणु
	.prepare	= clk_pllv3_prepare,
	.unprepare	= clk_pllv3_unprepare,
	.is_prepared	= clk_pllv3_is_prepared,
	.recalc_rate	= clk_pllv3_av_recalc_rate,
	.round_rate	= clk_pllv3_av_round_rate,
	.set_rate	= clk_pllv3_av_set_rate,
पूर्ण;

काष्ठा clk_pllv3_vf610_mf अणु
	u32 mfi;	/* पूर्णांकeger part, can be 20 or 22 */
	u32 mfn;	/* numerator, 30-bit value */
	u32 mfd;	/* denominator, 30-bit value, must be less than mfn */
पूर्ण;

अटल अचिन्हित दीर्घ clk_pllv3_vf610_mf_to_rate(अचिन्हित दीर्घ parent_rate,
		काष्ठा clk_pllv3_vf610_mf mf)
अणु
	u64 temp64;

	temp64 = parent_rate;
	temp64 *= mf.mfn;
	करो_भाग(temp64, mf.mfd);

	वापस (parent_rate * mf.mfi) + temp64;
पूर्ण

अटल काष्ठा clk_pllv3_vf610_mf clk_pllv3_vf610_rate_to_mf(
		अचिन्हित दीर्घ parent_rate, अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk_pllv3_vf610_mf mf;
	u64 temp64;

	mf.mfi = (rate >= 22 * parent_rate) ? 22 : 20;
	mf.mfd = 0x3fffffff;	/* use max supported value क्रम best accuracy */

	अगर (rate <= parent_rate * mf.mfi)
		mf.mfn = 0;
	अन्यथा अगर (rate >= parent_rate * (mf.mfi + 1))
		mf.mfn = mf.mfd - 1;
	अन्यथा अणु
		/* rate = parent_rate * (mfi + mfn/mfd) */
		temp64 = rate - parent_rate * mf.mfi;
		temp64 *= mf.mfd;
		करो_भाग(temp64, parent_rate);
		mf.mfn = temp64;
	पूर्ण

	वापस mf;
पूर्ण

अटल अचिन्हित दीर्घ clk_pllv3_vf610_recalc_rate(काष्ठा clk_hw *hw,
					      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pllv3 *pll = to_clk_pllv3(hw);
	काष्ठा clk_pllv3_vf610_mf mf;

	mf.mfn = पढ़ोl_relaxed(pll->base + pll->num_offset);
	mf.mfd = पढ़ोl_relaxed(pll->base + pll->denom_offset);
	mf.mfi = (पढ़ोl_relaxed(pll->base) & pll->भाग_mask) ? 22 : 20;

	वापस clk_pllv3_vf610_mf_to_rate(parent_rate, mf);
पूर्ण

अटल दीर्घ clk_pllv3_vf610_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_pllv3_vf610_mf mf = clk_pllv3_vf610_rate_to_mf(*prate, rate);

	वापस clk_pllv3_vf610_mf_to_rate(*prate, mf);
पूर्ण

अटल पूर्णांक clk_pllv3_vf610_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pllv3 *pll = to_clk_pllv3(hw);
	काष्ठा clk_pllv3_vf610_mf mf =
			clk_pllv3_vf610_rate_to_mf(parent_rate, rate);
	u32 val;

	val = पढ़ोl_relaxed(pll->base);
	अगर (mf.mfi == 20)
		val &= ~pll->भाग_mask;	/* clear bit क्रम mfi=20 */
	अन्यथा
		val |= pll->भाग_mask;	/* set bit क्रम mfi=22 */
	ग_लिखोl_relaxed(val, pll->base);

	ग_लिखोl_relaxed(mf.mfn, pll->base + pll->num_offset);
	ग_लिखोl_relaxed(mf.mfd, pll->base + pll->denom_offset);

	वापस clk_pllv3_रुको_lock(pll);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pllv3_vf610_ops = अणु
	.prepare	= clk_pllv3_prepare,
	.unprepare	= clk_pllv3_unprepare,
	.is_prepared	= clk_pllv3_is_prepared,
	.recalc_rate	= clk_pllv3_vf610_recalc_rate,
	.round_rate	= clk_pllv3_vf610_round_rate,
	.set_rate	= clk_pllv3_vf610_set_rate,
पूर्ण;

अटल अचिन्हित दीर्घ clk_pllv3_enet_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pllv3 *pll = to_clk_pllv3(hw);

	वापस pll->ref_घड़ी;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pllv3_enet_ops = अणु
	.prepare	= clk_pllv3_prepare,
	.unprepare	= clk_pllv3_unprepare,
	.is_prepared	= clk_pllv3_is_prepared,
	.recalc_rate	= clk_pllv3_enet_recalc_rate,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_pllv3(क्रमागत imx_pllv3_type type, स्थिर अक्षर *name,
			  स्थिर अक्षर *parent_name, व्योम __iomem *base,
			  u32 भाग_mask)
अणु
	काष्ठा clk_pllv3 *pll;
	स्थिर काष्ठा clk_ops *ops;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	pll->घातer_bit = BM_PLL_POWER;
	pll->num_offset = PLL_NUM_OFFSET;
	pll->denom_offset = PLL_DENOM_OFFSET;

	चयन (type) अणु
	हाल IMX_PLLV3_SYS:
		ops = &clk_pllv3_sys_ops;
		अवरोध;
	हाल IMX_PLLV3_SYS_VF610:
		ops = &clk_pllv3_vf610_ops;
		pll->num_offset = PLL_VF610_NUM_OFFSET;
		pll->denom_offset = PLL_VF610_DENOM_OFFSET;
		अवरोध;
	हाल IMX_PLLV3_USB_VF610:
		pll->भाग_shअगरt = 1;
		fallthrough;
	हाल IMX_PLLV3_USB:
		ops = &clk_pllv3_ops;
		pll->घातerup_set = true;
		अवरोध;
	हाल IMX_PLLV3_AV_IMX7:
		pll->num_offset = PLL_IMX7_NUM_OFFSET;
		pll->denom_offset = PLL_IMX7_DENOM_OFFSET;
		fallthrough;
	हाल IMX_PLLV3_AV:
		ops = &clk_pllv3_av_ops;
		अवरोध;
	हाल IMX_PLLV3_ENET_IMX7:
		pll->घातer_bit = IMX7_ENET_PLL_POWER;
		pll->ref_घड़ी = 1000000000;
		ops = &clk_pllv3_enet_ops;
		अवरोध;
	हाल IMX_PLLV3_ENET:
		pll->ref_घड़ी = 500000000;
		ops = &clk_pllv3_enet_ops;
		अवरोध;
	हाल IMX_PLLV3_DDR_IMX7:
		pll->घातer_bit = IMX7_DDR_PLL_POWER;
		pll->num_offset = PLL_IMX7_NUM_OFFSET;
		pll->denom_offset = PLL_IMX7_DENOM_OFFSET;
		ops = &clk_pllv3_av_ops;
		अवरोध;
	शेष:
		ops = &clk_pllv3_ops;
	पूर्ण
	pll->base = base;
	pll->भाग_mask = भाग_mask;

	init.name = name;
	init.ops = ops;
	init.flags = 0;
	init.parent_names = &parent_name;
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
