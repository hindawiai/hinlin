<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Google, Inc.
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>

#समावेश "clk.h"

#घोषणा PLL_STATUS			0x0
#घोषणा PLL_STATUS_LOCK			BIT(0)

#घोषणा PLL_CTRL1			0x4
#घोषणा PLL_CTRL1_REFDIV_SHIFT		0
#घोषणा PLL_CTRL1_REFDIV_MASK		0x3f
#घोषणा PLL_CTRL1_FBDIV_SHIFT		6
#घोषणा PLL_CTRL1_FBDIV_MASK		0xfff
#घोषणा PLL_INT_CTRL1_POSTDIV1_SHIFT	18
#घोषणा PLL_INT_CTRL1_POSTDIV1_MASK	0x7
#घोषणा PLL_INT_CTRL1_POSTDIV2_SHIFT	21
#घोषणा PLL_INT_CTRL1_POSTDIV2_MASK	0x7
#घोषणा PLL_INT_CTRL1_PD		BIT(24)
#घोषणा PLL_INT_CTRL1_DSMPD		BIT(25)
#घोषणा PLL_INT_CTRL1_FOUTPOSTDIVPD	BIT(26)
#घोषणा PLL_INT_CTRL1_FOUTVCOPD		BIT(27)

#घोषणा PLL_CTRL2			0x8
#घोषणा PLL_FRAC_CTRL2_FRAC_SHIFT	0
#घोषणा PLL_FRAC_CTRL2_FRAC_MASK	0xffffff
#घोषणा PLL_FRAC_CTRL2_POSTDIV1_SHIFT	24
#घोषणा PLL_FRAC_CTRL2_POSTDIV1_MASK	0x7
#घोषणा PLL_FRAC_CTRL2_POSTDIV2_SHIFT	27
#घोषणा PLL_FRAC_CTRL2_POSTDIV2_MASK	0x7
#घोषणा PLL_INT_CTRL2_BYPASS		BIT(28)

#घोषणा PLL_CTRL3			0xc
#घोषणा PLL_FRAC_CTRL3_PD		BIT(0)
#घोषणा PLL_FRAC_CTRL3_DACPD		BIT(1)
#घोषणा PLL_FRAC_CTRL3_DSMPD		BIT(2)
#घोषणा PLL_FRAC_CTRL3_FOUTPOSTDIVPD	BIT(3)
#घोषणा PLL_FRAC_CTRL3_FOUT4PHASEPD	BIT(4)
#घोषणा PLL_FRAC_CTRL3_FOUTVCOPD	BIT(5)

#घोषणा PLL_CTRL4			0x10
#घोषणा PLL_FRAC_CTRL4_BYPASS		BIT(28)

#घोषणा MIN_PFD				9600000UL
#घोषणा MIN_VCO_LA			400000000UL
#घोषणा MAX_VCO_LA			1600000000UL
#घोषणा MIN_VCO_FRAC_INT		600000000UL
#घोषणा MAX_VCO_FRAC_INT		1600000000UL
#घोषणा MIN_VCO_FRAC_FRAC		600000000UL
#घोषणा MAX_VCO_FRAC_FRAC		2400000000UL
#घोषणा MIN_OUTPUT_LA			8000000UL
#घोषणा MAX_OUTPUT_LA			1600000000UL
#घोषणा MIN_OUTPUT_FRAC			12000000UL
#घोषणा MAX_OUTPUT_FRAC			1600000000UL

/* Fractional PLL operating modes */
क्रमागत pll_mode अणु
	PLL_MODE_FRAC,
	PLL_MODE_INT,
पूर्ण;

काष्ठा pistachio_clk_pll अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	काष्ठा pistachio_pll_rate_table *rates;
	अचिन्हित पूर्णांक nr_rates;
पूर्ण;

अटल अंतरभूत u32 pll_पढ़ोl(काष्ठा pistachio_clk_pll *pll, u32 reg)
अणु
	वापस पढ़ोl(pll->base + reg);
पूर्ण

अटल अंतरभूत व्योम pll_ग_लिखोl(काष्ठा pistachio_clk_pll *pll, u32 val, u32 reg)
अणु
	ग_लिखोl(val, pll->base + reg);
पूर्ण

अटल अंतरभूत व्योम pll_lock(काष्ठा pistachio_clk_pll *pll)
अणु
	जबतक (!(pll_पढ़ोl(pll, PLL_STATUS) & PLL_STATUS_LOCK))
		cpu_relax();
पूर्ण

अटल अंतरभूत u64 करो_भाग_round_बंदst(u64 भागidend, u64 भागisor)
अणु
	भागidend += भागisor / 2;
	वापस भाग64_u64(भागidend, भागisor);
पूर्ण

अटल अंतरभूत काष्ठा pistachio_clk_pll *to_pistachio_pll(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा pistachio_clk_pll, hw);
पूर्ण

अटल अंतरभूत क्रमागत pll_mode pll_frac_get_mode(काष्ठा clk_hw *hw)
अणु
	काष्ठा pistachio_clk_pll *pll = to_pistachio_pll(hw);
	u32 val;

	val = pll_पढ़ोl(pll, PLL_CTRL3) & PLL_FRAC_CTRL3_DSMPD;
	वापस val ? PLL_MODE_INT : PLL_MODE_FRAC;
पूर्ण

अटल अंतरभूत व्योम pll_frac_set_mode(काष्ठा clk_hw *hw, क्रमागत pll_mode mode)
अणु
	काष्ठा pistachio_clk_pll *pll = to_pistachio_pll(hw);
	u32 val;

	val = pll_पढ़ोl(pll, PLL_CTRL3);
	अगर (mode == PLL_MODE_INT)
		val |= PLL_FRAC_CTRL3_DSMPD | PLL_FRAC_CTRL3_DACPD;
	अन्यथा
		val &= ~(PLL_FRAC_CTRL3_DSMPD | PLL_FRAC_CTRL3_DACPD);

	pll_ग_लिखोl(pll, val, PLL_CTRL3);
पूर्ण

अटल काष्ठा pistachio_pll_rate_table *
pll_get_params(काष्ठा pistachio_clk_pll *pll, अचिन्हित दीर्घ fref,
	       अचिन्हित दीर्घ fout)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pll->nr_rates; i++) अणु
		अगर (pll->rates[i].fref == fref && pll->rates[i].fout == fout)
			वापस &pll->rates[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल दीर्घ pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा pistachio_clk_pll *pll = to_pistachio_pll(hw);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pll->nr_rates; i++) अणु
		अगर (i > 0 && pll->rates[i].fref == *parent_rate &&
		    pll->rates[i].fout <= rate)
			वापस pll->rates[i - 1].fout;
	पूर्ण

	वापस pll->rates[0].fout;
पूर्ण

अटल पूर्णांक pll_gf40lp_frac_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा pistachio_clk_pll *pll = to_pistachio_pll(hw);
	u32 val;

	val = pll_पढ़ोl(pll, PLL_CTRL3);
	val &= ~(PLL_FRAC_CTRL3_PD | PLL_FRAC_CTRL3_FOUTPOSTDIVPD |
		 PLL_FRAC_CTRL3_FOUT4PHASEPD | PLL_FRAC_CTRL3_FOUTVCOPD);
	pll_ग_लिखोl(pll, val, PLL_CTRL3);

	val = pll_पढ़ोl(pll, PLL_CTRL4);
	val &= ~PLL_FRAC_CTRL4_BYPASS;
	pll_ग_लिखोl(pll, val, PLL_CTRL4);

	pll_lock(pll);

	वापस 0;
पूर्ण

अटल व्योम pll_gf40lp_frac_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा pistachio_clk_pll *pll = to_pistachio_pll(hw);
	u32 val;

	val = pll_पढ़ोl(pll, PLL_CTRL3);
	val |= PLL_FRAC_CTRL3_PD;
	pll_ग_लिखोl(pll, val, PLL_CTRL3);
पूर्ण

अटल पूर्णांक pll_gf40lp_frac_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा pistachio_clk_pll *pll = to_pistachio_pll(hw);

	वापस !(pll_पढ़ोl(pll, PLL_CTRL3) & PLL_FRAC_CTRL3_PD);
पूर्ण

अटल पूर्णांक pll_gf40lp_frac_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pistachio_clk_pll *pll = to_pistachio_pll(hw);
	काष्ठा pistachio_pll_rate_table *params;
	पूर्णांक enabled = pll_gf40lp_frac_is_enabled(hw);
	u64 val, vco, old_postभाग1, old_postभाग2;
	स्थिर अक्षर *name = clk_hw_get_name(hw);

	अगर (rate < MIN_OUTPUT_FRAC || rate > MAX_OUTPUT_FRAC)
		वापस -EINVAL;

	params = pll_get_params(pll, parent_rate, rate);
	अगर (!params || !params->refभाग)
		वापस -EINVAL;

	/* calculate vco */
	vco = params->fref;
	vco *= (params->fbभाग << 24) + params->frac;
	vco = भाग64_u64(vco, params->refभाग << 24);

	अगर (vco < MIN_VCO_FRAC_FRAC || vco > MAX_VCO_FRAC_FRAC)
		pr_warn("%s: VCO %llu is out of range %lu..%lu\n", name, vco,
			MIN_VCO_FRAC_FRAC, MAX_VCO_FRAC_FRAC);

	val = भाग64_u64(params->fref, params->refभाग);
	अगर (val < MIN_PFD)
		pr_warn("%s: PFD %llu is too low (min %lu)\n",
			name, val, MIN_PFD);
	अगर (val > vco / 16)
		pr_warn("%s: PFD %llu is too high (max %llu)\n",
			name, val, vco / 16);

	val = pll_पढ़ोl(pll, PLL_CTRL1);
	val &= ~((PLL_CTRL1_REFDIV_MASK << PLL_CTRL1_REFDIV_SHIFT) |
		 (PLL_CTRL1_FBDIV_MASK << PLL_CTRL1_FBDIV_SHIFT));
	val |= (params->refभाग << PLL_CTRL1_REFDIV_SHIFT) |
		(params->fbभाग << PLL_CTRL1_FBDIV_SHIFT);
	pll_ग_लिखोl(pll, val, PLL_CTRL1);

	val = pll_पढ़ोl(pll, PLL_CTRL2);

	old_postभाग1 = (val >> PLL_FRAC_CTRL2_POSTDIV1_SHIFT) &
		       PLL_FRAC_CTRL2_POSTDIV1_MASK;
	old_postभाग2 = (val >> PLL_FRAC_CTRL2_POSTDIV2_SHIFT) &
		       PLL_FRAC_CTRL2_POSTDIV2_MASK;
	अगर (enabled &&
	    (params->postभाग1 != old_postभाग1 ||
	     params->postभाग2 != old_postभाग2))
		pr_warn("%s: changing postdiv while PLL is enabled\n", name);

	अगर (params->postभाग2 > params->postभाग1)
		pr_warn("%s: postdiv2 should not exceed postdiv1\n", name);

	val &= ~((PLL_FRAC_CTRL2_FRAC_MASK << PLL_FRAC_CTRL2_FRAC_SHIFT) |
		 (PLL_FRAC_CTRL2_POSTDIV1_MASK <<
		  PLL_FRAC_CTRL2_POSTDIV1_SHIFT) |
		 (PLL_FRAC_CTRL2_POSTDIV2_MASK <<
		  PLL_FRAC_CTRL2_POSTDIV2_SHIFT));
	val |= (params->frac << PLL_FRAC_CTRL2_FRAC_SHIFT) |
		(params->postभाग1 << PLL_FRAC_CTRL2_POSTDIV1_SHIFT) |
		(params->postभाग2 << PLL_FRAC_CTRL2_POSTDIV2_SHIFT);
	pll_ग_लिखोl(pll, val, PLL_CTRL2);

	/* set operating mode */
	अगर (params->frac)
		pll_frac_set_mode(hw, PLL_MODE_FRAC);
	अन्यथा
		pll_frac_set_mode(hw, PLL_MODE_INT);

	अगर (enabled)
		pll_lock(pll);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ pll_gf40lp_frac_recalc_rate(काष्ठा clk_hw *hw,
						 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pistachio_clk_pll *pll = to_pistachio_pll(hw);
	u64 val, preभाग, fbभाग, frac, postभाग1, postभाग2, rate;

	val = pll_पढ़ोl(pll, PLL_CTRL1);
	preभाग = (val >> PLL_CTRL1_REFDIV_SHIFT) & PLL_CTRL1_REFDIV_MASK;
	fbभाग = (val >> PLL_CTRL1_FBDIV_SHIFT) & PLL_CTRL1_FBDIV_MASK;

	val = pll_पढ़ोl(pll, PLL_CTRL2);
	postभाग1 = (val >> PLL_FRAC_CTRL2_POSTDIV1_SHIFT) &
		PLL_FRAC_CTRL2_POSTDIV1_MASK;
	postभाग2 = (val >> PLL_FRAC_CTRL2_POSTDIV2_SHIFT) &
		PLL_FRAC_CTRL2_POSTDIV2_MASK;
	frac = (val >> PLL_FRAC_CTRL2_FRAC_SHIFT) & PLL_FRAC_CTRL2_FRAC_MASK;

	/* get operating mode (पूर्णांक/frac) and calculate rate accordingly */
	rate = parent_rate;
	अगर (pll_frac_get_mode(hw) == PLL_MODE_FRAC)
		rate *= (fbभाग << 24) + frac;
	अन्यथा
		rate *= (fbभाग << 24);

	rate = करो_भाग_round_बंदst(rate, (preभाग * postभाग1 * postभाग2) << 24);

	वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops pll_gf40lp_frac_ops = अणु
	.enable = pll_gf40lp_frac_enable,
	.disable = pll_gf40lp_frac_disable,
	.is_enabled = pll_gf40lp_frac_is_enabled,
	.recalc_rate = pll_gf40lp_frac_recalc_rate,
	.round_rate = pll_round_rate,
	.set_rate = pll_gf40lp_frac_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops pll_gf40lp_frac_fixed_ops = अणु
	.enable = pll_gf40lp_frac_enable,
	.disable = pll_gf40lp_frac_disable,
	.is_enabled = pll_gf40lp_frac_is_enabled,
	.recalc_rate = pll_gf40lp_frac_recalc_rate,
पूर्ण;

अटल पूर्णांक pll_gf40lp_laपूर्णांक_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा pistachio_clk_pll *pll = to_pistachio_pll(hw);
	u32 val;

	val = pll_पढ़ोl(pll, PLL_CTRL1);
	val &= ~(PLL_INT_CTRL1_PD |
		 PLL_INT_CTRL1_FOUTPOSTDIVPD | PLL_INT_CTRL1_FOUTVCOPD);
	pll_ग_लिखोl(pll, val, PLL_CTRL1);

	val = pll_पढ़ोl(pll, PLL_CTRL2);
	val &= ~PLL_INT_CTRL2_BYPASS;
	pll_ग_लिखोl(pll, val, PLL_CTRL2);

	pll_lock(pll);

	वापस 0;
पूर्ण

अटल व्योम pll_gf40lp_laपूर्णांक_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा pistachio_clk_pll *pll = to_pistachio_pll(hw);
	u32 val;

	val = pll_पढ़ोl(pll, PLL_CTRL1);
	val |= PLL_INT_CTRL1_PD;
	pll_ग_लिखोl(pll, val, PLL_CTRL1);
पूर्ण

अटल पूर्णांक pll_gf40lp_laपूर्णांक_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा pistachio_clk_pll *pll = to_pistachio_pll(hw);

	वापस !(pll_पढ़ोl(pll, PLL_CTRL1) & PLL_INT_CTRL1_PD);
पूर्ण

अटल पूर्णांक pll_gf40lp_laपूर्णांक_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pistachio_clk_pll *pll = to_pistachio_pll(hw);
	काष्ठा pistachio_pll_rate_table *params;
	पूर्णांक enabled = pll_gf40lp_laपूर्णांक_is_enabled(hw);
	u32 val, vco, old_postभाग1, old_postभाग2;
	स्थिर अक्षर *name = clk_hw_get_name(hw);

	अगर (rate < MIN_OUTPUT_LA || rate > MAX_OUTPUT_LA)
		वापस -EINVAL;

	params = pll_get_params(pll, parent_rate, rate);
	अगर (!params || !params->refभाग)
		वापस -EINVAL;

	vco = भाग_u64(params->fref * params->fbभाग, params->refभाग);
	अगर (vco < MIN_VCO_LA || vco > MAX_VCO_LA)
		pr_warn("%s: VCO %u is out of range %lu..%lu\n", name, vco,
			MIN_VCO_LA, MAX_VCO_LA);

	val = भाग_u64(params->fref, params->refभाग);
	अगर (val < MIN_PFD)
		pr_warn("%s: PFD %u is too low (min %lu)\n",
			name, val, MIN_PFD);
	अगर (val > vco / 16)
		pr_warn("%s: PFD %u is too high (max %u)\n",
			name, val, vco / 16);

	val = pll_पढ़ोl(pll, PLL_CTRL1);

	old_postभाग1 = (val >> PLL_INT_CTRL1_POSTDIV1_SHIFT) &
		       PLL_INT_CTRL1_POSTDIV1_MASK;
	old_postभाग2 = (val >> PLL_INT_CTRL1_POSTDIV2_SHIFT) &
		       PLL_INT_CTRL1_POSTDIV2_MASK;
	अगर (enabled &&
	    (params->postभाग1 != old_postभाग1 ||
	     params->postभाग2 != old_postभाग2))
		pr_warn("%s: changing postdiv while PLL is enabled\n", name);

	अगर (params->postभाग2 > params->postभाग1)
		pr_warn("%s: postdiv2 should not exceed postdiv1\n", name);

	val &= ~((PLL_CTRL1_REFDIV_MASK << PLL_CTRL1_REFDIV_SHIFT) |
		 (PLL_CTRL1_FBDIV_MASK << PLL_CTRL1_FBDIV_SHIFT) |
		 (PLL_INT_CTRL1_POSTDIV1_MASK << PLL_INT_CTRL1_POSTDIV1_SHIFT) |
		 (PLL_INT_CTRL1_POSTDIV2_MASK << PLL_INT_CTRL1_POSTDIV2_SHIFT));
	val |= (params->refभाग << PLL_CTRL1_REFDIV_SHIFT) |
		(params->fbभाग << PLL_CTRL1_FBDIV_SHIFT) |
		(params->postभाग1 << PLL_INT_CTRL1_POSTDIV1_SHIFT) |
		(params->postभाग2 << PLL_INT_CTRL1_POSTDIV2_SHIFT);
	pll_ग_लिखोl(pll, val, PLL_CTRL1);

	अगर (enabled)
		pll_lock(pll);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ pll_gf40lp_laपूर्णांक_recalc_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pistachio_clk_pll *pll = to_pistachio_pll(hw);
	u32 val, preभाग, fbभाग, postभाग1, postभाग2;
	u64 rate = parent_rate;

	val = pll_पढ़ोl(pll, PLL_CTRL1);
	preभाग = (val >> PLL_CTRL1_REFDIV_SHIFT) & PLL_CTRL1_REFDIV_MASK;
	fbभाग = (val >> PLL_CTRL1_FBDIV_SHIFT) & PLL_CTRL1_FBDIV_MASK;
	postभाग1 = (val >> PLL_INT_CTRL1_POSTDIV1_SHIFT) &
		PLL_INT_CTRL1_POSTDIV1_MASK;
	postभाग2 = (val >> PLL_INT_CTRL1_POSTDIV2_SHIFT) &
		PLL_INT_CTRL1_POSTDIV2_MASK;

	rate *= fbभाग;
	rate = करो_भाग_round_बंदst(rate, preभाग * postभाग1 * postभाग2);

	वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops pll_gf40lp_laपूर्णांक_ops = अणु
	.enable = pll_gf40lp_laपूर्णांक_enable,
	.disable = pll_gf40lp_laपूर्णांक_disable,
	.is_enabled = pll_gf40lp_laपूर्णांक_is_enabled,
	.recalc_rate = pll_gf40lp_laपूर्णांक_recalc_rate,
	.round_rate = pll_round_rate,
	.set_rate = pll_gf40lp_laपूर्णांक_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops pll_gf40lp_laपूर्णांक_fixed_ops = अणु
	.enable = pll_gf40lp_laपूर्णांक_enable,
	.disable = pll_gf40lp_laपूर्णांक_disable,
	.is_enabled = pll_gf40lp_laपूर्णांक_is_enabled,
	.recalc_rate = pll_gf40lp_laपूर्णांक_recalc_rate,
पूर्ण;

अटल काष्ठा clk *pll_रेजिस्टर(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
				अचिन्हित दीर्घ flags, व्योम __iomem *base,
				क्रमागत pistachio_pll_type type,
				काष्ठा pistachio_pll_rate_table *rates,
				अचिन्हित पूर्णांक nr_rates)
अणु
	काष्ठा pistachio_clk_pll *pll;
	काष्ठा clk_init_data init;
	काष्ठा clk *clk;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.flags = flags | CLK_GET_RATE_NOCACHE;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	चयन (type) अणु
	हाल PLL_GF40LP_FRAC:
		अगर (rates)
			init.ops = &pll_gf40lp_frac_ops;
		अन्यथा
			init.ops = &pll_gf40lp_frac_fixed_ops;
		अवरोध;
	हाल PLL_GF40LP_LAINT:
		अगर (rates)
			init.ops = &pll_gf40lp_laपूर्णांक_ops;
		अन्यथा
			init.ops = &pll_gf40lp_laपूर्णांक_fixed_ops;
		अवरोध;
	शेष:
		pr_err("Unrecognized PLL type %u\n", type);
		kमुक्त(pll);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pll->hw.init = &init;
	pll->base = base;
	pll->rates = rates;
	pll->nr_rates = nr_rates;

	clk = clk_रेजिस्टर(शून्य, &pll->hw);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

व्योम pistachio_clk_रेजिस्टर_pll(काष्ठा pistachio_clk_provider *p,
				काष्ठा pistachio_pll *pll,
				अचिन्हित पूर्णांक num)
अणु
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		clk = pll_रेजिस्टर(pll[i].name, pll[i].parent,
				   0, p->base + pll[i].reg_base,
				   pll[i].type, pll[i].rates,
				   pll[i].nr_rates);
		p->clk_data.clks[pll[i].id] = clk;
	पूर्ण
पूर्ण
