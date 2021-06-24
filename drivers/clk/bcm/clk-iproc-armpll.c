<शैली गुरु>
/*
 * Copyright (C) 2014 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/of_address.h>

#समावेश "clk-iproc.h"

#घोषणा IPROC_CLK_MAX_FREQ_POLICY                    0x3
#घोषणा IPROC_CLK_POLICY_FREQ_OFFSET                 0x008
#घोषणा IPROC_CLK_POLICY_FREQ_POLICY_FREQ_SHIFT      8
#घोषणा IPROC_CLK_POLICY_FREQ_POLICY_FREQ_MASK       0x7

#घोषणा IPROC_CLK_PLLARMA_OFFSET                     0xc00
#घोषणा IPROC_CLK_PLLARMA_LOCK_SHIFT                 28
#घोषणा IPROC_CLK_PLLARMA_PDIV_SHIFT                 24
#घोषणा IPROC_CLK_PLLARMA_PDIV_MASK                  0xf
#घोषणा IPROC_CLK_PLLARMA_NDIV_INT_SHIFT             8
#घोषणा IPROC_CLK_PLLARMA_NDIV_INT_MASK              0x3ff

#घोषणा IPROC_CLK_PLLARMB_OFFSET                     0xc04
#घोषणा IPROC_CLK_PLLARMB_NDIV_FRAC_MASK             0xfffff

#घोषणा IPROC_CLK_PLLARMC_OFFSET                     0xc08
#घोषणा IPROC_CLK_PLLARMC_BYPCLK_EN_SHIFT            8
#घोषणा IPROC_CLK_PLLARMC_MDIV_MASK                  0xff

#घोषणा IPROC_CLK_PLLARMCTL5_OFFSET                  0xc20
#घोषणा IPROC_CLK_PLLARMCTL5_H_MDIV_MASK             0xff

#घोषणा IPROC_CLK_PLLARM_OFFSET_OFFSET               0xc24
#घोषणा IPROC_CLK_PLLARM_SW_CTL_SHIFT                29
#घोषणा IPROC_CLK_PLLARM_NDIV_INT_OFFSET_SHIFT       20
#घोषणा IPROC_CLK_PLLARM_NDIV_INT_OFFSET_MASK        0xff
#घोषणा IPROC_CLK_PLLARM_NDIV_FRAC_OFFSET_MASK       0xfffff

#घोषणा IPROC_CLK_ARM_DIV_OFFSET                     0xe00
#घोषणा IPROC_CLK_ARM_DIV_PLL_SELECT_OVERRIDE_SHIFT  4
#घोषणा IPROC_CLK_ARM_DIV_ARM_PLL_SELECT_MASK        0xf

#घोषणा IPROC_CLK_POLICY_DBG_OFFSET                  0xec0
#घोषणा IPROC_CLK_POLICY_DBG_ACT_FREQ_SHIFT          12
#घोषणा IPROC_CLK_POLICY_DBG_ACT_FREQ_MASK           0x7

क्रमागत iproc_arm_pll_fid अणु
	ARM_PLL_FID_CRYSTAL_CLK   = 0,
	ARM_PLL_FID_SYS_CLK       = 2,
	ARM_PLL_FID_CH0_SLOW_CLK  = 6,
	ARM_PLL_FID_CH1_FAST_CLK  = 7
पूर्ण;

काष्ठा iproc_arm_pll अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	अचिन्हित दीर्घ rate;
पूर्ण;

#घोषणा to_iproc_arm_pll(hw) container_of(hw, काष्ठा iproc_arm_pll, hw)

अटल अचिन्हित पूर्णांक __get_fid(काष्ठा iproc_arm_pll *pll)
अणु
	u32 val;
	अचिन्हित पूर्णांक policy, fid, active_fid;

	val = पढ़ोl(pll->base + IPROC_CLK_ARM_DIV_OFFSET);
	अगर (val & (1 << IPROC_CLK_ARM_DIV_PLL_SELECT_OVERRIDE_SHIFT))
		policy = val & IPROC_CLK_ARM_DIV_ARM_PLL_SELECT_MASK;
	अन्यथा
		policy = 0;

	/* something is seriously wrong */
	BUG_ON(policy > IPROC_CLK_MAX_FREQ_POLICY);

	val = पढ़ोl(pll->base + IPROC_CLK_POLICY_FREQ_OFFSET);
	fid = (val >> (IPROC_CLK_POLICY_FREQ_POLICY_FREQ_SHIFT * policy)) &
		IPROC_CLK_POLICY_FREQ_POLICY_FREQ_MASK;

	val = पढ़ोl(pll->base + IPROC_CLK_POLICY_DBG_OFFSET);
	active_fid = IPROC_CLK_POLICY_DBG_ACT_FREQ_MASK &
		(val >> IPROC_CLK_POLICY_DBG_ACT_FREQ_SHIFT);
	अगर (fid != active_fid) अणु
		pr_debug("%s: fid override %u->%u\n", __func__,	fid,
				active_fid);
		fid = active_fid;
	पूर्ण

	pr_debug("%s: active fid: %u\n", __func__, fid);

	वापस fid;
पूर्ण

/*
 * Determine the mभाग (post भागider) based on the frequency ID being used.
 * There are 4 sources that can be used to derive the output घड़ी rate:
 *    - 25 MHz Crystal
 *    - System घड़ी
 *    - PLL channel 0 (slow घड़ी)
 *    - PLL channel 1 (fast घड़ी)
 */
अटल पूर्णांक __get_mभाग(काष्ठा iproc_arm_pll *pll)
अणु
	अचिन्हित पूर्णांक fid;
	पूर्णांक mभाग;
	u32 val;

	fid = __get_fid(pll);

	चयन (fid) अणु
	हाल ARM_PLL_FID_CRYSTAL_CLK:
	हाल ARM_PLL_FID_SYS_CLK:
		mभाग = 1;
		अवरोध;

	हाल ARM_PLL_FID_CH0_SLOW_CLK:
		val = पढ़ोl(pll->base + IPROC_CLK_PLLARMC_OFFSET);
		mभाग = val & IPROC_CLK_PLLARMC_MDIV_MASK;
		अगर (mभाग == 0)
			mभाग = 256;
		अवरोध;

	हाल ARM_PLL_FID_CH1_FAST_CLK:
		val = पढ़ोl(pll->base +	IPROC_CLK_PLLARMCTL5_OFFSET);
		mभाग = val & IPROC_CLK_PLLARMCTL5_H_MDIV_MASK;
		अगर (mभाग == 0)
			mभाग = 256;
		अवरोध;

	शेष:
		mभाग = -EFAULT;
	पूर्ण

	वापस mभाग;
पूर्ण

अटल अचिन्हित पूर्णांक __get_nभाग(काष्ठा iproc_arm_pll *pll)
अणु
	u32 val;
	अचिन्हित पूर्णांक nभाग_पूर्णांक, nभाग_frac, nभाग;

	val = पढ़ोl(pll->base + IPROC_CLK_PLLARM_OFFSET_OFFSET);
	अगर (val & (1 << IPROC_CLK_PLLARM_SW_CTL_SHIFT)) अणु
		/*
		 * offset mode is active. Read the nभाग from the PLLARM OFFSET
		 * रेजिस्टर
		 */
		nभाग_पूर्णांक = (val >> IPROC_CLK_PLLARM_NDIV_INT_OFFSET_SHIFT) &
			IPROC_CLK_PLLARM_NDIV_INT_OFFSET_MASK;
		अगर (nभाग_पूर्णांक == 0)
			nभाग_पूर्णांक = 256;

		nभाग_frac = val & IPROC_CLK_PLLARM_NDIV_FRAC_OFFSET_MASK;
	पूर्ण अन्यथा अणु
		/* offset mode not active */
		val = पढ़ोl(pll->base + IPROC_CLK_PLLARMA_OFFSET);
		nभाग_पूर्णांक = (val >> IPROC_CLK_PLLARMA_NDIV_INT_SHIFT) &
			IPROC_CLK_PLLARMA_NDIV_INT_MASK;
		अगर (nभाग_पूर्णांक == 0)
			nभाग_पूर्णांक = 1024;

		val = पढ़ोl(pll->base + IPROC_CLK_PLLARMB_OFFSET);
		nभाग_frac = val & IPROC_CLK_PLLARMB_NDIV_FRAC_MASK;
	पूर्ण

	nभाग = (nभाग_पूर्णांक << 20) | nभाग_frac;

	वापस nभाग;
पूर्ण

/*
 * The output frequency of the ARM PLL is calculated based on the ARM PLL
 * भागider values:
 *   pभाग = ARM PLL pre-भागider
 *   nभाग = ARM PLL multiplier
 *   mभाग = ARM PLL post भागider
 *
 * The frequency is calculated by:
 *   ((nभाग * parent घड़ी rate) / pभाग) / mभाग
 */
अटल अचिन्हित दीर्घ iproc_arm_pll_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा iproc_arm_pll *pll = to_iproc_arm_pll(hw);
	u32 val;
	पूर्णांक mभाग;
	u64 nभाग;
	अचिन्हित पूर्णांक pभाग;

	/* in bypass mode, use parent rate */
	val = पढ़ोl(pll->base + IPROC_CLK_PLLARMC_OFFSET);
	अगर (val & (1 << IPROC_CLK_PLLARMC_BYPCLK_EN_SHIFT)) अणु
		pll->rate = parent_rate;
		वापस pll->rate;
	पूर्ण

	/* PLL needs to be locked */
	val = पढ़ोl(pll->base + IPROC_CLK_PLLARMA_OFFSET);
	अगर (!(val & (1 << IPROC_CLK_PLLARMA_LOCK_SHIFT))) अणु
		pll->rate = 0;
		वापस 0;
	पूर्ण

	pभाग = (val >> IPROC_CLK_PLLARMA_PDIV_SHIFT) &
		IPROC_CLK_PLLARMA_PDIV_MASK;
	अगर (pभाग == 0)
		pभाग = 16;

	nभाग = __get_nभाग(pll);
	mभाग = __get_mभाग(pll);
	अगर (mभाग <= 0) अणु
		pll->rate = 0;
		वापस 0;
	पूर्ण
	pll->rate = (nभाग * parent_rate) >> 20;
	pll->rate = (pll->rate / pभाग) / mभाग;

	pr_debug("%s: ARM PLL rate: %lu. parent rate: %lu\n", __func__,
		 pll->rate, parent_rate);
	pr_debug("%s: ndiv_int: %u, pdiv: %u, mdiv: %d\n", __func__,
		 (अचिन्हित पूर्णांक)(nभाग >> 20), pभाग, mभाग);

	वापस pll->rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops iproc_arm_pll_ops = अणु
	.recalc_rate = iproc_arm_pll_recalc_rate,
पूर्ण;

व्योम __init iproc_armpll_setup(काष्ठा device_node *node)
अणु
	पूर्णांक ret;
	काष्ठा iproc_arm_pll *pll;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *parent_name;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (WARN_ON(!pll))
		वापस;

	pll->base = of_iomap(node, 0);
	अगर (WARN_ON(!pll->base))
		जाओ err_मुक्त_pll;

	init.name = node->name;
	init.ops = &iproc_arm_pll_ops;
	init.flags = 0;
	parent_name = of_clk_get_parent_name(node, 0);
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);
	pll->hw.init = &init;

	ret = clk_hw_रेजिस्टर(शून्य, &pll->hw);
	अगर (WARN_ON(ret))
		जाओ err_iounmap;

	ret = of_clk_add_hw_provider(node, of_clk_hw_simple_get, &pll->hw);
	अगर (WARN_ON(ret))
		जाओ err_clk_unरेजिस्टर;

	वापस;

err_clk_unरेजिस्टर:
	clk_hw_unरेजिस्टर(&pll->hw);
err_iounmap:
	iounmap(pll->base);
err_मुक्त_pll:
	kमुक्त(pll);
पूर्ण
