<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PLL घड़ी driver क्रम TI Davinci SoCs
 *
 * Copyright (C) 2018 David Lechner <david@lechnology.com>
 *
 * Based on arch/arm/mach-davinci/घड़ी.c
 * Copyright (C) 2006-2007 Texas Instruments.
 * Copyright (C) 2008-2009 Deep Root Systems, LLC
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk/davinci.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/clk-davinci-pll.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "pll.h"

#घोषणा MAX_NAME_SIZE	20
#घोषणा OSCIN_CLK_NAME	"oscin"

#घोषणा REVID		0x000
#घोषणा PLLCTL		0x100
#घोषणा OCSEL		0x104
#घोषणा PLLSECCTL	0x108
#घोषणा PLLM		0x110
#घोषणा PREDIV		0x114
#घोषणा PLLDIV1		0x118
#घोषणा PLLDIV2		0x11c
#घोषणा PLLDIV3		0x120
#घोषणा OSCDIV		0x124
#घोषणा POSTDIV		0x128
#घोषणा BPDIV		0x12c
#घोषणा PLLCMD		0x138
#घोषणा PLLSTAT		0x13c
#घोषणा ALNCTL		0x140
#घोषणा DCHANGE		0x144
#घोषणा CKEN		0x148
#घोषणा CKSTAT		0x14c
#घोषणा SYSTAT		0x150
#घोषणा PLLDIV4		0x160
#घोषणा PLLDIV5		0x164
#घोषणा PLLDIV6		0x168
#घोषणा PLLDIV7		0x16c
#घोषणा PLLDIV8		0x170
#घोषणा PLLDIV9		0x174

#घोषणा PLLCTL_PLLEN		BIT(0)
#घोषणा PLLCTL_PLLPWRDN		BIT(1)
#घोषणा PLLCTL_PLLRST		BIT(3)
#घोषणा PLLCTL_PLLDIS		BIT(4)
#घोषणा PLLCTL_PLLENSRC		BIT(5)
#घोषणा PLLCTL_CLKMODE		BIT(8)

/* shared by most *DIV रेजिस्टरs */
#घोषणा DIV_RATIO_SHIFT		0
#घोषणा DIV_RATIO_WIDTH		5
#घोषणा DIV_ENABLE_SHIFT	15

#घोषणा PLLCMD_GOSET		BIT(0)
#घोषणा PLLSTAT_GOSTAT		BIT(0)

#घोषणा CKEN_OBSCLK_SHIFT	1
#घोषणा CKEN_AUXEN_SHIFT	0

/*
 * OMAP-L138 प्रणाली reference guide recommends a रुको क्रम 4 OSCIN/CLKIN
 * cycles to ensure that the PLLC has चयनed to bypass mode. Delay of 1us
 * ensures we are good क्रम all > 4MHz OSCIN/CLKIN inमाला_दो. Typically the input
 * is ~25MHz. Units are micro seconds.
 */
#घोषणा PLL_BYPASS_TIME		1

/* From OMAP-L138 datasheet table 6-4. Units are micro seconds */
#घोषणा PLL_RESET_TIME		1

/*
 * From OMAP-L138 datasheet table 6-4; assuming preभाग = 1, वर्ग_मूल(pllm) = 4
 * Units are micro seconds.
 */
#घोषणा PLL_LOCK_TIME		20

/**
 * काष्ठा davinci_pll_clk - Main PLL घड़ी (aka PLLOUT)
 * @hw: clk_hw क्रम the pll
 * @base: Base memory address
 * @pllm_min: The minimum allowable PLLM[PLLM] value
 * @pllm_max: The maxiumum allowable PLLM[PLLM] value
 * @pllm_mask: Biपंचांगask क्रम PLLM[PLLM] value
 */
काष्ठा davinci_pll_clk अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	u32 pllm_min;
	u32 pllm_max;
	u32 pllm_mask;
पूर्ण;

#घोषणा to_davinci_pll_clk(_hw) \
	container_of((_hw), काष्ठा davinci_pll_clk, hw)

अटल अचिन्हित दीर्घ davinci_pll_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा davinci_pll_clk *pll = to_davinci_pll_clk(hw);
	अचिन्हित दीर्घ rate = parent_rate;
	u32 mult;

	mult = पढ़ोl(pll->base + PLLM) & pll->pllm_mask;
	rate *= mult + 1;

	वापस rate;
पूर्ण

अटल पूर्णांक davinci_pll_determine_rate(काष्ठा clk_hw *hw,
				      काष्ठा clk_rate_request *req)
अणु
	काष्ठा davinci_pll_clk *pll = to_davinci_pll_clk(hw);
	काष्ठा clk_hw *parent = req->best_parent_hw;
	अचिन्हित दीर्घ parent_rate = req->best_parent_rate;
	अचिन्हित दीर्घ rate = req->rate;
	अचिन्हित दीर्घ best_rate, r;
	u32 mult;

	/* there is a limited range of valid outमाला_दो (see datasheet) */
	अगर (rate < req->min_rate)
		वापस -EINVAL;

	rate = min(rate, req->max_rate);
	mult = rate / parent_rate;
	best_rate = parent_rate * mult;

	/* easy हाल when there is no PREDIV */
	अगर (!(clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)) अणु
		अगर (best_rate < req->min_rate)
			वापस -EINVAL;

		अगर (mult < pll->pllm_min || mult > pll->pllm_max)
			वापस -EINVAL;

		req->rate = best_rate;

		वापस 0;
	पूर्ण

	/* see अगर the PREDIV घड़ी can help us */
	best_rate = 0;

	क्रम (mult = pll->pllm_min; mult <= pll->pllm_max; mult++) अणु
		parent_rate = clk_hw_round_rate(parent, rate / mult);
		r = parent_rate * mult;
		अगर (r < req->min_rate)
			जारी;
		अगर (r > rate || r > req->max_rate)
			अवरोध;
		अगर (r > best_rate) अणु
			best_rate = r;
			req->rate = best_rate;
			req->best_parent_rate = parent_rate;
			अगर (best_rate == rate)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा davinci_pll_clk *pll = to_davinci_pll_clk(hw);
	u32 mult;

	mult = rate / parent_rate;
	ग_लिखोl(mult - 1, pll->base + PLLM);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम davinci_pll_debug_init(काष्ठा clk_hw *hw, काष्ठा dentry *dentry);
#अन्यथा
#घोषणा davinci_pll_debug_init शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा clk_ops davinci_pll_ops = अणु
	.recalc_rate	= davinci_pll_recalc_rate,
	.determine_rate	= davinci_pll_determine_rate,
	.set_rate	= davinci_pll_set_rate,
	.debug_init	= davinci_pll_debug_init,
पूर्ण;

/* PLLM works dअगरferently on DM365 */
अटल अचिन्हित दीर्घ dm365_pll_recalc_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा davinci_pll_clk *pll = to_davinci_pll_clk(hw);
	अचिन्हित दीर्घ rate = parent_rate;
	u32 mult;

	mult = पढ़ोl(pll->base + PLLM) & pll->pllm_mask;
	rate *= mult * 2;

	वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops dm365_pll_ops = अणु
	.recalc_rate	= dm365_pll_recalc_rate,
	.debug_init	= davinci_pll_debug_init,
पूर्ण;

/**
 * davinci_pll_भाग_रेजिस्टर - common *DIV घड़ी implementation
 * @dev: The PLL platक्रमm device or शून्य
 * @name: the घड़ी name
 * @parent_name: the parent घड़ी name
 * @reg: the *DIV रेजिस्टर
 * @fixed: अगर true, the भागider is a fixed value
 * @flags: biपंचांगap of CLK_* flags from घड़ी-provider.h
 */
अटल काष्ठा clk *davinci_pll_भाग_रेजिस्टर(काष्ठा device *dev,
					    स्थिर अक्षर *name,
					    स्थिर अक्षर *parent_name,
					    व्योम __iomem *reg,
					    bool fixed, u32 flags)
अणु
	स्थिर अक्षर * स्थिर *parent_names = parent_name ? &parent_name : शून्य;
	पूर्णांक num_parents = parent_name ? 1 : 0;
	स्थिर काष्ठा clk_ops *भागider_ops = &clk_भागider_ops;
	काष्ठा clk_gate *gate;
	काष्ठा clk_भागider *भागider;
	काष्ठा clk *clk;
	पूर्णांक ret;

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		वापस ERR_PTR(-ENOMEM);

	gate->reg = reg;
	gate->bit_idx = DIV_ENABLE_SHIFT;

	भागider = kzalloc(माप(*भागider), GFP_KERNEL);
	अगर (!भागider) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_gate;
	पूर्ण

	भागider->reg = reg;
	भागider->shअगरt = DIV_RATIO_SHIFT;
	भागider->width = DIV_RATIO_WIDTH;

	अगर (fixed) अणु
		भागider->flags |= CLK_DIVIDER_READ_ONLY;
		भागider_ops = &clk_भागider_ro_ops;
	पूर्ण

	clk = clk_रेजिस्टर_composite(dev, name, parent_names, num_parents,
				     शून्य, शून्य, &भागider->hw, भागider_ops,
				     &gate->hw, &clk_gate_ops, flags);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ err_मुक्त_भागider;
	पूर्ण

	वापस clk;

err_मुक्त_भागider:
	kमुक्त(भागider);
err_मुक्त_gate:
	kमुक्त(gate);

	वापस ERR_PTR(ret);
पूर्ण

काष्ठा davinci_pllen_clk अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
पूर्ण;

#घोषणा to_davinci_pllen_clk(_hw) \
	container_of((_hw), काष्ठा davinci_pllen_clk, hw)

अटल स्थिर काष्ठा clk_ops davinci_pllen_ops = अणु
	/* this घड़ीs just uses the घड़ी notअगरication feature */
पूर्ण;

/*
 * The PLL has to be चयनed पूर्णांकo bypass mode जबतक we are chaning the rate,
 * so we करो that on the PLLEN घड़ी since it is the end of the line. This will
 * चयन to bypass beक्रमe any of the parent घड़ीs (PREDIV, PLL, POSTDIV) are
 * changed and will चयन back to the PLL after the changes have been made.
 */
अटल पूर्णांक davinci_pllen_rate_change(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ flags, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *cnd = data;
	काष्ठा clk_hw *hw = __clk_get_hw(cnd->clk);
	काष्ठा davinci_pllen_clk *pll = to_davinci_pllen_clk(hw);
	u32 ctrl;

	ctrl = पढ़ोl(pll->base + PLLCTL);

	अगर (flags == PRE_RATE_CHANGE) अणु
		/* Switch the PLL to bypass mode */
		ctrl &= ~(PLLCTL_PLLENSRC | PLLCTL_PLLEN);
		ग_लिखोl(ctrl, pll->base + PLLCTL);

		udelay(PLL_BYPASS_TIME);

		/* Reset and enable PLL */
		ctrl &= ~(PLLCTL_PLLRST | PLLCTL_PLLDIS);
		ग_लिखोl(ctrl, pll->base + PLLCTL);
	पूर्ण अन्यथा अणु
		udelay(PLL_RESET_TIME);

		/* Bring PLL out of reset */
		ctrl |= PLLCTL_PLLRST;
		ग_लिखोl(ctrl, pll->base + PLLCTL);

		udelay(PLL_LOCK_TIME);

		/* Remove PLL from bypass mode */
		ctrl |= PLLCTL_PLLEN;
		ग_लिखोl(ctrl, pll->base + PLLCTL);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block davinci_pllen_notअगरier = अणु
	.notअगरier_call = davinci_pllen_rate_change,
पूर्ण;

/**
 * davinci_pll_clk_रेजिस्टर - Register a PLL घड़ी
 * @dev: The PLL platक्रमm device or शून्य
 * @info: The device-specअगरic घड़ी info
 * @parent_name: The parent घड़ी name
 * @base: The PLL's memory region
 * @cfgchip: CFGCHIP syscon regmap क्रम info->unlock_reg or शून्य
 *
 * This creates a series of घड़ीs that represent the PLL.
 *
 *     OSCIN > [PREDIV >] PLL > [POSTDIV >] PLLEN
 *
 * - OSCIN is the parent घड़ी (on secondary PLL, may come from primary PLL)
 * - PREDIV and POSTDIV are optional (depends on the PLL controller)
 * - PLL is the PLL output (aka PLLOUT)
 * - PLLEN is the bypass multiplexer
 *
 * Returns: The PLLOUT घड़ी or a negative error code.
 */
काष्ठा clk *davinci_pll_clk_रेजिस्टर(काष्ठा device *dev,
				     स्थिर काष्ठा davinci_pll_clk_info *info,
				     स्थिर अक्षर *parent_name,
				     व्योम __iomem *base,
				     काष्ठा regmap *cfgchip)
अणु
	अक्षर preभाग_name[MAX_NAME_SIZE];
	अक्षर pllout_name[MAX_NAME_SIZE];
	अक्षर postभाग_name[MAX_NAME_SIZE];
	अक्षर pllen_name[MAX_NAME_SIZE];
	काष्ठा clk_init_data init;
	काष्ठा davinci_pll_clk *pllout;
	काष्ठा davinci_pllen_clk *pllen;
	काष्ठा clk *oscin_clk = शून्य;
	काष्ठा clk *preभाग_clk = शून्य;
	काष्ठा clk *pllout_clk;
	काष्ठा clk *postभाग_clk = शून्य;
	काष्ठा clk *pllen_clk;
	पूर्णांक ret;

	अगर (info->flags & PLL_HAS_CLKMODE) अणु
		/*
		 * If a PLL has PLLCTL[CLKMODE], then it is the primary PLL.
		 * We रेजिस्टर a घड़ी named "oscin" that serves as the पूर्णांकernal
		 * "input clock" करोमुख्य shared by both PLLs (अगर there are 2)
		 * and will be the parent घड़ी to the AUXCLK, SYSCLKBP and
		 * OBSCLK करोमुख्यs. NB: The various TRMs use "OSCIN" to mean
		 * a number of dअगरferent things. In this driver we use it to
		 * mean the संकेत after the PLLCTL[CLKMODE] चयन.
		 */
		oscin_clk = clk_रेजिस्टर_fixed_factor(dev, OSCIN_CLK_NAME,
						      parent_name, 0, 1, 1);
		अगर (IS_ERR(oscin_clk))
			वापस oscin_clk;

		parent_name = OSCIN_CLK_NAME;
	पूर्ण

	अगर (info->flags & PLL_HAS_PREDIV) अणु
		bool fixed = info->flags & PLL_PREDIV_FIXED_DIV;
		u32 flags = 0;

		snम_लिखो(preभाग_name, MAX_NAME_SIZE, "%s_prediv", info->name);

		अगर (info->flags & PLL_PREDIV_ALWAYS_ENABLED)
			flags |= CLK_IS_CRITICAL;

		/* Some? DM355 chips करोn't correctly report the PREDIV value */
		अगर (info->flags & PLL_PREDIV_FIXED8)
			preभाग_clk = clk_रेजिस्टर_fixed_factor(dev, preभाग_name,
							parent_name, flags, 1, 8);
		अन्यथा
			preभाग_clk = davinci_pll_भाग_रेजिस्टर(dev, preभाग_name,
				parent_name, base + PREDIV, fixed, flags);
		अगर (IS_ERR(preभाग_clk)) अणु
			ret = PTR_ERR(preभाग_clk);
			जाओ err_unरेजिस्टर_oscin;
		पूर्ण

		parent_name = preभाग_name;
	पूर्ण

	/* Unlock writing to PLL रेजिस्टरs */
	अगर (info->unlock_reg) अणु
		अगर (IS_ERR_OR_शून्य(cfgchip))
			dev_warn(dev, "Failed to get CFGCHIP (%ld)\n",
				 PTR_ERR(cfgchip));
		अन्यथा
			regmap_ग_लिखो_bits(cfgchip, info->unlock_reg,
					  info->unlock_mask, 0);
	पूर्ण

	pllout = kzalloc(माप(*pllout), GFP_KERNEL);
	अगर (!pllout) अणु
		ret = -ENOMEM;
		जाओ err_unरेजिस्टर_preभाग;
	पूर्ण

	snम_लिखो(pllout_name, MAX_NAME_SIZE, "%s_pllout", info->name);

	init.name = pllout_name;
	अगर (info->flags & PLL_PLLM_2X)
		init.ops = &dm365_pll_ops;
	अन्यथा
		init.ops = &davinci_pll_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = 0;

	अगर (info->flags & PLL_HAS_PREDIV)
		init.flags |= CLK_SET_RATE_PARENT;

	pllout->hw.init = &init;
	pllout->base = base;
	pllout->pllm_mask = info->pllm_mask;
	pllout->pllm_min = info->pllm_min;
	pllout->pllm_max = info->pllm_max;

	pllout_clk = clk_रेजिस्टर(dev, &pllout->hw);
	अगर (IS_ERR(pllout_clk)) अणु
		ret = PTR_ERR(pllout_clk);
		जाओ err_मुक्त_pllout;
	पूर्ण

	clk_hw_set_rate_range(&pllout->hw, info->pllout_min_rate,
			      info->pllout_max_rate);

	parent_name = pllout_name;

	अगर (info->flags & PLL_HAS_POSTDIV) अणु
		bool fixed = info->flags & PLL_POSTDIV_FIXED_DIV;
		u32 flags = CLK_SET_RATE_PARENT;

		snम_लिखो(postभाग_name, MAX_NAME_SIZE, "%s_postdiv", info->name);

		अगर (info->flags & PLL_POSTDIV_ALWAYS_ENABLED)
			flags |= CLK_IS_CRITICAL;

		postभाग_clk = davinci_pll_भाग_रेजिस्टर(dev, postभाग_name,
				parent_name, base + POSTDIV, fixed, flags);
		अगर (IS_ERR(postभाग_clk)) अणु
			ret = PTR_ERR(postभाग_clk);
			जाओ err_unरेजिस्टर_pllout;
		पूर्ण

		parent_name = postभाग_name;
	पूर्ण

	pllen = kzalloc(माप(*pllen), GFP_KERNEL);
	अगर (!pllen) अणु
		ret = -ENOMEM;
		जाओ err_unरेजिस्टर_postभाग;
	पूर्ण

	snम_लिखो(pllen_name, MAX_NAME_SIZE, "%s_pllen", info->name);

	init.name = pllen_name;
	init.ops = &davinci_pllen_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = CLK_SET_RATE_PARENT;

	pllen->hw.init = &init;
	pllen->base = base;

	pllen_clk = clk_रेजिस्टर(dev, &pllen->hw);
	अगर (IS_ERR(pllen_clk)) अणु
		ret = PTR_ERR(pllen_clk);
		जाओ err_मुक्त_pllen;
	पूर्ण

	clk_notअगरier_रेजिस्टर(pllen_clk, &davinci_pllen_notअगरier);

	वापस pllout_clk;

err_मुक्त_pllen:
	kमुक्त(pllen);
err_unरेजिस्टर_postभाग:
	clk_unरेजिस्टर(postभाग_clk);
err_unरेजिस्टर_pllout:
	clk_unरेजिस्टर(pllout_clk);
err_मुक्त_pllout:
	kमुक्त(pllout);
err_unरेजिस्टर_preभाग:
	clk_unरेजिस्टर(preभाग_clk);
err_unरेजिस्टर_oscin:
	clk_unरेजिस्टर(oscin_clk);

	वापस ERR_PTR(ret);
पूर्ण

/**
 * davinci_pll_auxclk_रेजिस्टर - Register bypass घड़ी (AUXCLK)
 * @dev: The PLL platक्रमm device or शून्य
 * @name: The घड़ी name
 * @base: The PLL memory region
 */
काष्ठा clk *davinci_pll_auxclk_रेजिस्टर(काष्ठा device *dev,
					स्थिर अक्षर *name,
					व्योम __iomem *base)
अणु
	वापस clk_रेजिस्टर_gate(dev, name, OSCIN_CLK_NAME, 0, base + CKEN,
				 CKEN_AUXEN_SHIFT, 0, शून्य);
पूर्ण

/**
 * davinci_pll_sysclkbp_clk_रेजिस्टर - Register bypass भागider घड़ी (SYSCLKBP)
 * @dev: The PLL platक्रमm device or शून्य
 * @name: The घड़ी name
 * @base: The PLL memory region
 */
काष्ठा clk *davinci_pll_sysclkbp_clk_रेजिस्टर(काष्ठा device *dev,
					      स्थिर अक्षर *name,
					      व्योम __iomem *base)
अणु
	वापस clk_रेजिस्टर_भागider(dev, name, OSCIN_CLK_NAME, 0, base + BPDIV,
				    DIV_RATIO_SHIFT, DIV_RATIO_WIDTH,
				    CLK_DIVIDER_READ_ONLY, शून्य);
पूर्ण

/**
 * davinci_pll_obsclk_रेजिस्टर - Register oscillator भागider घड़ी (OBSCLK)
 * @dev: The PLL platक्रमm device or शून्य
 * @info: The घड़ी info
 * @base: The PLL memory region
 */
काष्ठा clk *
davinci_pll_obsclk_रेजिस्टर(काष्ठा device *dev,
			    स्थिर काष्ठा davinci_pll_obsclk_info *info,
			    व्योम __iomem *base)
अणु
	काष्ठा clk_mux *mux;
	काष्ठा clk_gate *gate;
	काष्ठा clk_भागider *भागider;
	काष्ठा clk *clk;
	u32 oscभाग;
	पूर्णांक ret;

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस ERR_PTR(-ENOMEM);

	mux->reg = base + OCSEL;
	mux->table = info->table;
	mux->mask = info->ocsrc_mask;

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_mux;
	पूर्ण

	gate->reg = base + CKEN;
	gate->bit_idx = CKEN_OBSCLK_SHIFT;

	भागider = kzalloc(माप(*भागider), GFP_KERNEL);
	अगर (!भागider) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_gate;
	पूर्ण

	भागider->reg = base + OSCDIV;
	भागider->shअगरt = DIV_RATIO_SHIFT;
	भागider->width = DIV_RATIO_WIDTH;

	/* make sure भागider is enabled just in हाल bootloader disabled it */
	oscभाग = पढ़ोl(base + OSCDIV);
	oscभाग |= BIT(DIV_ENABLE_SHIFT);
	ग_लिखोl(oscभाग, base + OSCDIV);

	clk = clk_रेजिस्टर_composite(dev, info->name, info->parent_names,
				     info->num_parents,
				     &mux->hw, &clk_mux_ops,
				     &भागider->hw, &clk_भागider_ops,
				     &gate->hw, &clk_gate_ops, 0);

	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ err_मुक्त_भागider;
	पूर्ण

	वापस clk;

err_मुक्त_भागider:
	kमुक्त(भागider);
err_मुक्त_gate:
	kमुक्त(gate);
err_मुक्त_mux:
	kमुक्त(mux);

	वापस ERR_PTR(ret);
पूर्ण

/* The PLL SYSCLKn घड़ीs have a mechanism क्रम synchronizing rate changes. */
अटल पूर्णांक davinci_pll_sysclk_rate_change(काष्ठा notअगरier_block *nb,
					  अचिन्हित दीर्घ flags, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *cnd = data;
	काष्ठा clk_hw *hw = __clk_get_hw(clk_get_parent(cnd->clk));
	काष्ठा davinci_pllen_clk *pll = to_davinci_pllen_clk(hw);
	u32 pllcmd, pllstat;

	चयन (flags) अणु
	हाल POST_RATE_CHANGE:
		/* apply the changes */
		pllcmd = पढ़ोl(pll->base + PLLCMD);
		pllcmd |= PLLCMD_GOSET;
		ग_लिखोl(pllcmd, pll->base + PLLCMD);
		fallthrough;
	हाल PRE_RATE_CHANGE:
		/* Wait until क्रम outstanding changes to take effect */
		करो अणु
			pllstat = पढ़ोl(pll->base + PLLSTAT);
		पूर्ण जबतक (pllstat & PLLSTAT_GOSTAT);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block davinci_pll_sysclk_notअगरier = अणु
	.notअगरier_call = davinci_pll_sysclk_rate_change,
पूर्ण;

/**
 * davinci_pll_sysclk_रेजिस्टर - Register भागider घड़ीs (SYSCLKn)
 * @dev: The PLL platक्रमm device or शून्य
 * @info: The घड़ी info
 * @base: The PLL memory region
 */
काष्ठा clk *
davinci_pll_sysclk_रेजिस्टर(काष्ठा device *dev,
			    स्थिर काष्ठा davinci_pll_sysclk_info *info,
			    व्योम __iomem *base)
अणु
	स्थिर काष्ठा clk_ops *भागider_ops = &clk_भागider_ops;
	काष्ठा clk_gate *gate;
	काष्ठा clk_भागider *भागider;
	काष्ठा clk *clk;
	u32 reg;
	u32 flags = 0;
	पूर्णांक ret;

	/* PLLDIVn रेजिस्टरs are not entirely consecutive */
	अगर (info->id < 4)
		reg = PLLDIV1 + 4 * (info->id - 1);
	अन्यथा
		reg = PLLDIV4 + 4 * (info->id - 4);

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		वापस ERR_PTR(-ENOMEM);

	gate->reg = base + reg;
	gate->bit_idx = DIV_ENABLE_SHIFT;

	भागider = kzalloc(माप(*भागider), GFP_KERNEL);
	अगर (!भागider) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_gate;
	पूर्ण

	भागider->reg = base + reg;
	भागider->shअगरt = DIV_RATIO_SHIFT;
	भागider->width = info->ratio_width;
	भागider->flags = 0;

	अगर (info->flags & SYSCLK_FIXED_DIV) अणु
		भागider->flags |= CLK_DIVIDER_READ_ONLY;
		भागider_ops = &clk_भागider_ro_ops;
	पूर्ण

	/* Only the ARM घड़ी can change the parent PLL rate */
	अगर (info->flags & SYSCLK_ARM_RATE)
		flags |= CLK_SET_RATE_PARENT;

	अगर (info->flags & SYSCLK_ALWAYS_ENABLED)
		flags |= CLK_IS_CRITICAL;

	clk = clk_रेजिस्टर_composite(dev, info->name, &info->parent_name, 1,
				     शून्य, शून्य, &भागider->hw, भागider_ops,
				     &gate->hw, &clk_gate_ops, flags);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ err_मुक्त_भागider;
	पूर्ण

	clk_notअगरier_रेजिस्टर(clk, &davinci_pll_sysclk_notअगरier);

	वापस clk;

err_मुक्त_भागider:
	kमुक्त(भागider);
err_मुक्त_gate:
	kमुक्त(gate);

	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक of_davinci_pll_init(काष्ठा device *dev, काष्ठा device_node *node,
			स्थिर काष्ठा davinci_pll_clk_info *info,
			स्थिर काष्ठा davinci_pll_obsclk_info *obsclk_info,
			स्थिर काष्ठा davinci_pll_sysclk_info **भाग_info,
			u8 max_sysclk_id,
			व्योम __iomem *base,
			काष्ठा regmap *cfgchip)
अणु
	काष्ठा device_node *child;
	स्थिर अक्षर *parent_name;
	काष्ठा clk *clk;

	अगर (info->flags & PLL_HAS_CLKMODE)
		parent_name = of_clk_get_parent_name(node, 0);
	अन्यथा
		parent_name = OSCIN_CLK_NAME;

	clk = davinci_pll_clk_रेजिस्टर(dev, info, parent_name, base, cfgchip);
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "failed to register %s\n", info->name);
		वापस PTR_ERR(clk);
	पूर्ण

	child = of_get_child_by_name(node, "pllout");
	अगर (of_device_is_available(child))
		of_clk_add_provider(child, of_clk_src_simple_get, clk);
	of_node_put(child);

	child = of_get_child_by_name(node, "sysclk");
	अगर (of_device_is_available(child)) अणु
		काष्ठा clk_onecell_data *clk_data;
		काष्ठा clk **clks;
		पूर्णांक n_clks =  max_sysclk_id + 1;
		पूर्णांक i;

		clk_data = kzalloc(माप(*clk_data), GFP_KERNEL);
		अगर (!clk_data) अणु
			of_node_put(child);
			वापस -ENOMEM;
		पूर्ण

		clks = kदो_स्मृति_array(n_clks, माप(*clks), GFP_KERNEL);
		अगर (!clks) अणु
			kमुक्त(clk_data);
			of_node_put(child);
			वापस -ENOMEM;
		पूर्ण

		clk_data->clks = clks;
		clk_data->clk_num = n_clks;

		क्रम (i = 0; i < n_clks; i++)
			clks[i] = ERR_PTR(-ENOENT);

		क्रम (; *भाग_info; भाग_info++) अणु
			clk = davinci_pll_sysclk_रेजिस्टर(dev, *भाग_info, base);
			अगर (IS_ERR(clk))
				dev_warn(dev, "failed to register %s (%ld)\n",
					 (*भाग_info)->name, PTR_ERR(clk));
			अन्यथा
				clks[(*भाग_info)->id] = clk;
		पूर्ण
		of_clk_add_provider(child, of_clk_src_onecell_get, clk_data);
	पूर्ण
	of_node_put(child);

	child = of_get_child_by_name(node, "auxclk");
	अगर (of_device_is_available(child)) अणु
		अक्षर child_name[MAX_NAME_SIZE];

		snम_लिखो(child_name, MAX_NAME_SIZE, "%s_auxclk", info->name);

		clk = davinci_pll_auxclk_रेजिस्टर(dev, child_name, base);
		अगर (IS_ERR(clk))
			dev_warn(dev, "failed to register %s (%ld)\n",
				 child_name, PTR_ERR(clk));
		अन्यथा
			of_clk_add_provider(child, of_clk_src_simple_get, clk);
	पूर्ण
	of_node_put(child);

	child = of_get_child_by_name(node, "obsclk");
	अगर (of_device_is_available(child)) अणु
		अगर (obsclk_info)
			clk = davinci_pll_obsclk_रेजिस्टर(dev, obsclk_info, base);
		अन्यथा
			clk = ERR_PTR(-EINVAL);

		अगर (IS_ERR(clk))
			dev_warn(dev, "failed to register obsclk (%ld)\n",
				 PTR_ERR(clk));
		अन्यथा
			of_clk_add_provider(child, of_clk_src_simple_get, clk);
	पूर्ण
	of_node_put(child);

	वापस 0;
पूर्ण

अटल काष्ठा davinci_pll_platक्रमm_data *davinci_pll_get_pdata(काष्ठा device *dev)
अणु
	काष्ठा davinci_pll_platक्रमm_data *pdata = dev_get_platdata(dev);

	/*
	 * Platक्रमm data is optional, so allocate a new काष्ठा अगर one was not
	 * provided. For device tree, this will always be the हाल.
	 */
	अगर (!pdata)
		pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	/* क्रम device tree, we need to fill in the काष्ठा */
	अगर (dev->of_node)
		pdata->cfgchip =
			syscon_regmap_lookup_by_compatible("ti,da830-cfgchip");

	वापस pdata;
पूर्ण

/* needed in early boot क्रम घड़ीsource/घड़ीevent */
#अगर_घोषित CONFIG_ARCH_DAVINCI_DA850
CLK_OF_DECLARE(da850_pll0, "ti,da850-pll0", of_da850_pll0_init);
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id davinci_pll_of_match[] = अणु
#अगर_घोषित CONFIG_ARCH_DAVINCI_DA850
	अणु .compatible = "ti,da850-pll1", .data = of_da850_pll1_init पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id davinci_pll_id_table[] = अणु
#अगर_घोषित CONFIG_ARCH_DAVINCI_DA830
	अणु .name = "da830-pll",   .driver_data = (kernel_uदीर्घ_t)da830_pll_init   पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DA850
	अणु .name = "da850-pll0",  .driver_data = (kernel_uदीर्घ_t)da850_pll0_init  पूर्ण,
	अणु .name = "da850-pll1",  .driver_data = (kernel_uदीर्घ_t)da850_pll1_init  पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM355
	अणु .name = "dm355-pll1",  .driver_data = (kernel_uदीर्घ_t)dm355_pll1_init  पूर्ण,
	अणु .name = "dm355-pll2",  .driver_data = (kernel_uदीर्घ_t)dm355_pll2_init  पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM365
	अणु .name = "dm365-pll1",  .driver_data = (kernel_uदीर्घ_t)dm365_pll1_init  पूर्ण,
	अणु .name = "dm365-pll2",  .driver_data = (kernel_uदीर्घ_t)dm365_pll2_init  पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM644x
	अणु .name = "dm644x-pll1", .driver_data = (kernel_uदीर्घ_t)dm644x_pll1_init पूर्ण,
	अणु .name = "dm644x-pll2", .driver_data = (kernel_uदीर्घ_t)dm644x_pll2_init पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM646x
	अणु .name = "dm646x-pll1", .driver_data = (kernel_uदीर्घ_t)dm646x_pll1_init पूर्ण,
	अणु .name = "dm646x-pll2", .driver_data = (kernel_uदीर्घ_t)dm646x_pll2_init पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

प्रकार पूर्णांक (*davinci_pll_init)(काष्ठा device *dev, व्योम __iomem *base,
				काष्ठा regmap *cfgchip);

अटल पूर्णांक davinci_pll_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा davinci_pll_platक्रमm_data *pdata;
	स्थिर काष्ठा of_device_id *of_id;
	davinci_pll_init pll_init = शून्य;
	व्योम __iomem *base;

	of_id = of_match_device(davinci_pll_of_match, dev);
	अगर (of_id)
		pll_init = of_id->data;
	अन्यथा अगर (pdev->id_entry)
		pll_init = (व्योम *)pdev->id_entry->driver_data;

	अगर (!pll_init) अणु
		dev_err(dev, "unable to find driver data\n");
		वापस -EINVAL;
	पूर्ण

	pdata = davinci_pll_get_pdata(dev);
	अगर (!pdata) अणु
		dev_err(dev, "missing platform data\n");
		वापस -EINVAL;
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	वापस pll_init(dev, base, pdata->cfgchip);
पूर्ण

अटल काष्ठा platक्रमm_driver davinci_pll_driver = अणु
	.probe		= davinci_pll_probe,
	.driver		= अणु
		.name		= "davinci-pll-clk",
		.of_match_table	= davinci_pll_of_match,
	पूर्ण,
	.id_table	= davinci_pll_id_table,
पूर्ण;

अटल पूर्णांक __init davinci_pll_driver_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&davinci_pll_driver);
पूर्ण

/* has to be postcore_initcall because PSC devices depend on PLL parent घड़ीs */
postcore_initcall(davinci_pll_driver_init);

#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>

#घोषणा DEBUG_REG(n)	\
अणु			\
	.name	= #n,	\
	.offset	= n,	\
पूर्ण

अटल स्थिर काष्ठा debugfs_reg32 davinci_pll_regs[] = अणु
	DEBUG_REG(REVID),
	DEBUG_REG(PLLCTL),
	DEBUG_REG(OCSEL),
	DEBUG_REG(PLLSECCTL),
	DEBUG_REG(PLLM),
	DEBUG_REG(PREDIV),
	DEBUG_REG(PLLDIV1),
	DEBUG_REG(PLLDIV2),
	DEBUG_REG(PLLDIV3),
	DEBUG_REG(OSCDIV),
	DEBUG_REG(POSTDIV),
	DEBUG_REG(BPDIV),
	DEBUG_REG(PLLCMD),
	DEBUG_REG(PLLSTAT),
	DEBUG_REG(ALNCTL),
	DEBUG_REG(DCHANGE),
	DEBUG_REG(CKEN),
	DEBUG_REG(CKSTAT),
	DEBUG_REG(SYSTAT),
	DEBUG_REG(PLLDIV4),
	DEBUG_REG(PLLDIV5),
	DEBUG_REG(PLLDIV6),
	DEBUG_REG(PLLDIV7),
	DEBUG_REG(PLLDIV8),
	DEBUG_REG(PLLDIV9),
पूर्ण;

अटल व्योम davinci_pll_debug_init(काष्ठा clk_hw *hw, काष्ठा dentry *dentry)
अणु
	काष्ठा davinci_pll_clk *pll = to_davinci_pll_clk(hw);
	काष्ठा debugfs_regset32 *regset;

	regset = kzalloc(माप(*regset), GFP_KERNEL);
	अगर (!regset)
		वापस;

	regset->regs = davinci_pll_regs;
	regset->nregs = ARRAY_SIZE(davinci_pll_regs);
	regset->base = pll->base;

	debugfs_create_regset32("registers", 0400, dentry, regset);
पूर्ण
#पूर्ण_अगर
