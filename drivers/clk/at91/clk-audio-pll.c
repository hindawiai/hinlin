<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2016 Aपंचांगel Corporation,
 *		       Songjun Wu <songjun.wu@aपंचांगel.com>,
 *                     Nicolas Ferre <nicolas.ferre@aपंचांगel.com>
 *  Copyright (C) 2017 Free Electrons,
 *		       Quentin Schulz <quentin.schulz@मुक्त-electrons.com>
 *
 * The Sama5d2 SoC has two audio PLLs (PMC and PAD) that shares the same parent
 * (FRAC). FRAC can output between 620 and 700MHz and only multiply the rate of
 * its own parent. PMC and PAD can then भागide the FRAC rate to best match the
 * asked rate.
 *
 * Traits of FRAC घड़ी:
 * enable - clk_enable ग_लिखोs nd, fracr parameters and enables PLL
 * rate - rate is adjustable.
 *        clk->rate = parent->rate * ((nd + 1) + (fracr / 2^22))
 * parent - fixed parent.  No clk_set_parent support
 *
 * Traits of PMC घड़ी:
 * enable - clk_enable ग_लिखोs qdpmc, and enables PMC output
 * rate - rate is adjustable.
 *        clk->rate = parent->rate / (qdpmc + 1)
 * parent - fixed parent.  No clk_set_parent support
 *
 * Traits of PAD घड़ी:
 * enable - clk_enable ग_लिखोs भागisors and enables PAD output
 * rate - rate is adjustable.
 *        clk->rate = parent->rate / (qdaudio * भाग))
 * parent - fixed parent.  No clk_set_parent support
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "pmc.h"

#घोषणा AUDIO_PLL_DIV_FRAC	BIT(22)
#घोषणा AUDIO_PLL_ND_MAX	(AT91_PMC_AUDIO_PLL_ND_MASK >> \
					AT91_PMC_AUDIO_PLL_ND_OFFSET)

#घोषणा AUDIO_PLL_QDPAD(qd, भाग)	((AT91_PMC_AUDIO_PLL_QDPAD_EXTDIV(qd) & \
					  AT91_PMC_AUDIO_PLL_QDPAD_EXTDIV_MASK) | \
					 (AT91_PMC_AUDIO_PLL_QDPAD_DIV(भाग) & \
					  AT91_PMC_AUDIO_PLL_QDPAD_DIV_MASK))

#घोषणा AUDIO_PLL_QDPMC_MAX		(AT91_PMC_AUDIO_PLL_QDPMC_MASK >> \
						AT91_PMC_AUDIO_PLL_QDPMC_OFFSET)

#घोषणा AUDIO_PLL_FOUT_MIN	620000000UL
#घोषणा AUDIO_PLL_FOUT_MAX	700000000UL

काष्ठा clk_audio_frac अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u32 fracr;
	u8 nd;
पूर्ण;

काष्ठा clk_audio_pad अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u8 qdaudio;
	u8 भाग;
पूर्ण;

काष्ठा clk_audio_pmc अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u8 qdpmc;
पूर्ण;

#घोषणा to_clk_audio_frac(hw) container_of(hw, काष्ठा clk_audio_frac, hw)
#घोषणा to_clk_audio_pad(hw) container_of(hw, काष्ठा clk_audio_pad, hw)
#घोषणा to_clk_audio_pmc(hw) container_of(hw, काष्ठा clk_audio_pmc, hw)

अटल पूर्णांक clk_audio_pll_frac_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_audio_frac *frac = to_clk_audio_frac(hw);

	regmap_update_bits(frac->regmap, AT91_PMC_AUDIO_PLL0,
			   AT91_PMC_AUDIO_PLL_RESETN, 0);
	regmap_update_bits(frac->regmap, AT91_PMC_AUDIO_PLL0,
			   AT91_PMC_AUDIO_PLL_RESETN,
			   AT91_PMC_AUDIO_PLL_RESETN);
	regmap_update_bits(frac->regmap, AT91_PMC_AUDIO_PLL1,
			   AT91_PMC_AUDIO_PLL_FRACR_MASK, frac->fracr);

	/*
	 * reset and enable have to be करोne in 2 separated ग_लिखोs
	 * क्रम AT91_PMC_AUDIO_PLL0
	 */
	regmap_update_bits(frac->regmap, AT91_PMC_AUDIO_PLL0,
			   AT91_PMC_AUDIO_PLL_PLLEN |
			   AT91_PMC_AUDIO_PLL_ND_MASK,
			   AT91_PMC_AUDIO_PLL_PLLEN |
			   AT91_PMC_AUDIO_PLL_ND(frac->nd));

	वापस 0;
पूर्ण

अटल पूर्णांक clk_audio_pll_pad_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_audio_pad *apad_ck = to_clk_audio_pad(hw);

	regmap_update_bits(apad_ck->regmap, AT91_PMC_AUDIO_PLL1,
			   AT91_PMC_AUDIO_PLL_QDPAD_MASK,
			   AUDIO_PLL_QDPAD(apad_ck->qdaudio, apad_ck->भाग));
	regmap_update_bits(apad_ck->regmap, AT91_PMC_AUDIO_PLL0,
			   AT91_PMC_AUDIO_PLL_PADEN, AT91_PMC_AUDIO_PLL_PADEN);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_audio_pll_pmc_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_audio_pmc *apmc_ck = to_clk_audio_pmc(hw);

	regmap_update_bits(apmc_ck->regmap, AT91_PMC_AUDIO_PLL0,
			   AT91_PMC_AUDIO_PLL_PMCEN |
			   AT91_PMC_AUDIO_PLL_QDPMC_MASK,
			   AT91_PMC_AUDIO_PLL_PMCEN |
			   AT91_PMC_AUDIO_PLL_QDPMC(apmc_ck->qdpmc));
	वापस 0;
पूर्ण

अटल व्योम clk_audio_pll_frac_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_audio_frac *frac = to_clk_audio_frac(hw);

	regmap_update_bits(frac->regmap, AT91_PMC_AUDIO_PLL0,
			   AT91_PMC_AUDIO_PLL_PLLEN, 0);
	/* करो it in 2 separated ग_लिखोs */
	regmap_update_bits(frac->regmap, AT91_PMC_AUDIO_PLL0,
			   AT91_PMC_AUDIO_PLL_RESETN, 0);
पूर्ण

अटल व्योम clk_audio_pll_pad_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_audio_pad *apad_ck = to_clk_audio_pad(hw);

	regmap_update_bits(apad_ck->regmap, AT91_PMC_AUDIO_PLL0,
			   AT91_PMC_AUDIO_PLL_PADEN, 0);
पूर्ण

अटल व्योम clk_audio_pll_pmc_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_audio_pmc *apmc_ck = to_clk_audio_pmc(hw);

	regmap_update_bits(apmc_ck->regmap, AT91_PMC_AUDIO_PLL0,
			   AT91_PMC_AUDIO_PLL_PMCEN, 0);
पूर्ण

अटल अचिन्हित दीर्घ clk_audio_pll_fout(अचिन्हित दीर्घ parent_rate,
					अचिन्हित दीर्घ nd, अचिन्हित दीर्घ fracr)
अणु
	अचिन्हित दीर्घ दीर्घ fr = (अचिन्हित दीर्घ दीर्घ)parent_rate * fracr;

	pr_debug("A PLL: %s, fr = %llu\n", __func__, fr);

	fr = DIV_ROUND_CLOSEST_ULL(fr, AUDIO_PLL_DIV_FRAC);

	pr_debug("A PLL: %s, fr = %llu\n", __func__, fr);

	वापस parent_rate * (nd + 1) + fr;
पूर्ण

अटल अचिन्हित दीर्घ clk_audio_pll_frac_recalc_rate(काष्ठा clk_hw *hw,
						    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_audio_frac *frac = to_clk_audio_frac(hw);
	अचिन्हित दीर्घ fout;

	fout = clk_audio_pll_fout(parent_rate, frac->nd, frac->fracr);

	pr_debug("A PLL: %s, fout = %lu (nd = %u, fracr = %lu)\n", __func__,
		 fout, frac->nd, (अचिन्हित दीर्घ)frac->fracr);

	वापस fout;
पूर्ण

अटल अचिन्हित दीर्घ clk_audio_pll_pad_recalc_rate(काष्ठा clk_hw *hw,
						   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_audio_pad *apad_ck = to_clk_audio_pad(hw);
	अचिन्हित दीर्घ apad_rate = 0;

	अगर (apad_ck->qdaudio && apad_ck->भाग)
		apad_rate = parent_rate / (apad_ck->qdaudio * apad_ck->भाग);

	pr_debug("A PLL/PAD: %s, apad_rate = %lu (div = %u, qdaudio = %u)\n",
		 __func__, apad_rate, apad_ck->भाग, apad_ck->qdaudio);

	वापस apad_rate;
पूर्ण

अटल अचिन्हित दीर्घ clk_audio_pll_pmc_recalc_rate(काष्ठा clk_hw *hw,
						   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_audio_pmc *apmc_ck = to_clk_audio_pmc(hw);
	अचिन्हित दीर्घ apmc_rate = 0;

	apmc_rate = parent_rate / (apmc_ck->qdpmc + 1);

	pr_debug("A PLL/PMC: %s, apmc_rate = %lu (qdpmc = %u)\n", __func__,
		 apmc_rate, apmc_ck->qdpmc);

	वापस apmc_rate;
पूर्ण

अटल पूर्णांक clk_audio_pll_frac_compute_frac(अचिन्हित दीर्घ rate,
					   अचिन्हित दीर्घ parent_rate,
					   अचिन्हित दीर्घ *nd,
					   अचिन्हित दीर्घ *fracr)
अणु
	अचिन्हित दीर्घ दीर्घ पंचांगp, rem;

	अगर (!rate)
		वापस -EINVAL;

	पंचांगp = rate;
	rem = करो_भाग(पंचांगp, parent_rate);
	अगर (!पंचांगp || पंचांगp >= AUDIO_PLL_ND_MAX)
		वापस -EINVAL;

	*nd = पंचांगp - 1;

	पंचांगp = rem * AUDIO_PLL_DIV_FRAC;
	पंचांगp = DIV_ROUND_CLOSEST_ULL(पंचांगp, parent_rate);
	अगर (पंचांगp > AT91_PMC_AUDIO_PLL_FRACR_MASK)
		वापस -EINVAL;

	/* we can cast here as we verअगरied the bounds just above */
	*fracr = (अचिन्हित दीर्घ)पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक clk_audio_pll_frac_determine_rate(काष्ठा clk_hw *hw,
					     काष्ठा clk_rate_request *req)
अणु
	अचिन्हित दीर्घ fracr, nd;
	पूर्णांक ret;

	pr_debug("A PLL: %s, rate = %lu (parent_rate = %lu)\n", __func__,
		 req->rate, req->best_parent_rate);

	req->rate = clamp(req->rate, AUDIO_PLL_FOUT_MIN, AUDIO_PLL_FOUT_MAX);

	req->min_rate = max(req->min_rate, AUDIO_PLL_FOUT_MIN);
	req->max_rate = min(req->max_rate, AUDIO_PLL_FOUT_MAX);

	ret = clk_audio_pll_frac_compute_frac(req->rate, req->best_parent_rate,
					      &nd, &fracr);
	अगर (ret)
		वापस ret;

	req->rate = clk_audio_pll_fout(req->best_parent_rate, nd, fracr);

	req->best_parent_hw = clk_hw_get_parent(hw);

	pr_debug("A PLL: %s, best_rate = %lu (nd = %lu, fracr = %lu)\n",
		 __func__, req->rate, nd, fracr);

	वापस 0;
पूर्ण

अटल दीर्घ clk_audio_pll_pad_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					 अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_hw *pclk = clk_hw_get_parent(hw);
	दीर्घ best_rate = -EINVAL;
	अचिन्हित दीर्घ best_parent_rate;
	अचिन्हित दीर्घ पंचांगp_qd;
	u32 भाग;
	दीर्घ पंचांगp_rate;
	पूर्णांक पंचांगp_dअगरf;
	पूर्णांक best_dअगरf = -1;

	pr_debug("A PLL/PAD: %s, rate = %lu (parent_rate = %lu)\n", __func__,
		 rate, *parent_rate);

	/*
	 * Rate भागisor is actually made of two dअगरferent भागisors, multiplied
	 * between themselves beक्रमe भागiding the rate.
	 * पंचांगp_qd goes from 1 to 31 and भाग is either 2 or 3.
	 * In order to aव्योम testing twice the rate भागisor (e.g. भागisor 12 can
	 * be found with (पंचांगp_qd, भाग) = (2, 6) or (3, 4)), we हटाओ any loop
	 * क्रम a rate भागisor when भाग is 2 and पंचांगp_qd is a multiple of 3.
	 * We cannot inverse it (condition भाग is 3 and पंचांगp_qd is even) or we
	 * would miss some rate भागisor that aren't reachable with भाग being 2
	 * (e.g. rate भागisor 90 is made with भाग = 3 and पंचांगp_qd = 30, thus
	 * पंचांगp_qd is even so we skip it because we think भाग 2 could make this
	 * rate भागisor which isn't possible since पंचांगp_qd has to be <= 31).
	 */
	क्रम (पंचांगp_qd = 1; पंचांगp_qd < AT91_PMC_AUDIO_PLL_QDPAD_EXTDIV_MAX; पंचांगp_qd++)
		क्रम (भाग = 2; भाग <= 3; भाग++) अणु
			अगर (भाग == 2 && पंचांगp_qd % 3 == 0)
				जारी;

			best_parent_rate = clk_hw_round_rate(pclk,
							rate * पंचांगp_qd * भाग);
			पंचांगp_rate = best_parent_rate / (भाग * पंचांगp_qd);
			पंचांगp_dअगरf = असल(rate - पंचांगp_rate);

			अगर (best_dअगरf < 0 || best_dअगरf > पंचांगp_dअगरf) अणु
				*parent_rate = best_parent_rate;
				best_rate = पंचांगp_rate;
				best_dअगरf = पंचांगp_dअगरf;
			पूर्ण
		पूर्ण

	pr_debug("A PLL/PAD: %s, best_rate = %ld, best_parent_rate = %lu\n",
		 __func__, best_rate, best_parent_rate);

	वापस best_rate;
पूर्ण

अटल दीर्घ clk_audio_pll_pmc_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					 अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_hw *pclk = clk_hw_get_parent(hw);
	दीर्घ best_rate = -EINVAL;
	अचिन्हित दीर्घ best_parent_rate = 0;
	u32 पंचांगp_qd = 0, भाग;
	दीर्घ पंचांगp_rate;
	पूर्णांक पंचांगp_dअगरf;
	पूर्णांक best_dअगरf = -1;

	pr_debug("A PLL/PMC: %s, rate = %lu (parent_rate = %lu)\n", __func__,
		 rate, *parent_rate);

	अगर (!rate)
		वापस 0;

	best_parent_rate = clk_round_rate(pclk->clk, 1);
	भाग = max(best_parent_rate / rate, 1UL);
	क्रम (; भाग <= AUDIO_PLL_QDPMC_MAX; भाग++) अणु
		best_parent_rate = clk_round_rate(pclk->clk, rate * भाग);
		पंचांगp_rate = best_parent_rate / भाग;
		पंचांगp_dअगरf = असल(rate - पंचांगp_rate);

		अगर (best_dअगरf < 0 || best_dअगरf > पंचांगp_dअगरf) अणु
			*parent_rate = best_parent_rate;
			best_rate = पंचांगp_rate;
			best_dअगरf = पंचांगp_dअगरf;
			पंचांगp_qd = भाग;
			अगर (!best_dअगरf)
				अवरोध;	/* got exact match */
		पूर्ण
	पूर्ण

	pr_debug("A PLL/PMC: %s, best_rate = %ld, best_parent_rate = %lu (qd = %d)\n",
		 __func__, best_rate, *parent_rate, पंचांगp_qd - 1);

	वापस best_rate;
पूर्ण

अटल पूर्णांक clk_audio_pll_frac_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_audio_frac *frac = to_clk_audio_frac(hw);
	अचिन्हित दीर्घ fracr, nd;
	पूर्णांक ret;

	pr_debug("A PLL: %s, rate = %lu (parent_rate = %lu)\n", __func__, rate,
		 parent_rate);

	अगर (rate < AUDIO_PLL_FOUT_MIN || rate > AUDIO_PLL_FOUT_MAX)
		वापस -EINVAL;

	ret = clk_audio_pll_frac_compute_frac(rate, parent_rate, &nd, &fracr);
	अगर (ret)
		वापस ret;

	frac->nd = nd;
	frac->fracr = fracr;

	वापस 0;
पूर्ण

अटल पूर्णांक clk_audio_pll_pad_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_audio_pad *apad_ck = to_clk_audio_pad(hw);
	u8 पंचांगp_भाग;

	pr_debug("A PLL/PAD: %s, rate = %lu (parent_rate = %lu)\n", __func__,
		 rate, parent_rate);

	अगर (!rate)
		वापस -EINVAL;

	पंचांगp_भाग = parent_rate / rate;
	अगर (पंचांगp_भाग % 3 == 0) अणु
		apad_ck->qdaudio = पंचांगp_भाग / 3;
		apad_ck->भाग = 3;
	पूर्ण अन्यथा अणु
		apad_ck->qdaudio = पंचांगp_भाग / 2;
		apad_ck->भाग = 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक clk_audio_pll_pmc_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_audio_pmc *apmc_ck = to_clk_audio_pmc(hw);

	अगर (!rate)
		वापस -EINVAL;

	pr_debug("A PLL/PMC: %s, rate = %lu (parent_rate = %lu)\n", __func__,
		 rate, parent_rate);

	apmc_ck->qdpmc = parent_rate / rate - 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops audio_pll_frac_ops = अणु
	.enable = clk_audio_pll_frac_enable,
	.disable = clk_audio_pll_frac_disable,
	.recalc_rate = clk_audio_pll_frac_recalc_rate,
	.determine_rate = clk_audio_pll_frac_determine_rate,
	.set_rate = clk_audio_pll_frac_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops audio_pll_pad_ops = अणु
	.enable = clk_audio_pll_pad_enable,
	.disable = clk_audio_pll_pad_disable,
	.recalc_rate = clk_audio_pll_pad_recalc_rate,
	.round_rate = clk_audio_pll_pad_round_rate,
	.set_rate = clk_audio_pll_pad_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops audio_pll_pmc_ops = अणु
	.enable = clk_audio_pll_pmc_enable,
	.disable = clk_audio_pll_pmc_disable,
	.recalc_rate = clk_audio_pll_pmc_recalc_rate,
	.round_rate = clk_audio_pll_pmc_round_rate,
	.set_rate = clk_audio_pll_pmc_set_rate,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_audio_pll_frac(काष्ठा regmap *regmap, स्थिर अक्षर *name,
				 स्थिर अक्षर *parent_name)
अणु
	काष्ठा clk_audio_frac *frac_ck;
	काष्ठा clk_init_data init = अणुपूर्ण;
	पूर्णांक ret;

	frac_ck = kzalloc(माप(*frac_ck), GFP_KERNEL);
	अगर (!frac_ck)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &audio_pll_frac_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = CLK_SET_RATE_GATE;

	frac_ck->hw.init = &init;
	frac_ck->regmap = regmap;

	ret = clk_hw_रेजिस्टर(शून्य, &frac_ck->hw);
	अगर (ret) अणु
		kमुक्त(frac_ck);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस &frac_ck->hw;
पूर्ण

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_audio_pll_pad(काष्ठा regmap *regmap, स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name)
अणु
	काष्ठा clk_audio_pad *apad_ck;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	apad_ck = kzalloc(माप(*apad_ck), GFP_KERNEL);
	अगर (!apad_ck)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &audio_pll_pad_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE |
		CLK_SET_RATE_PARENT;

	apad_ck->hw.init = &init;
	apad_ck->regmap = regmap;

	ret = clk_hw_रेजिस्टर(शून्य, &apad_ck->hw);
	अगर (ret) अणु
		kमुक्त(apad_ck);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस &apad_ck->hw;
पूर्ण

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_audio_pll_pmc(काष्ठा regmap *regmap, स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name)
अणु
	काष्ठा clk_audio_pmc *apmc_ck;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	apmc_ck = kzalloc(माप(*apmc_ck), GFP_KERNEL);
	अगर (!apmc_ck)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &audio_pll_pmc_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE |
		CLK_SET_RATE_PARENT;

	apmc_ck->hw.init = &init;
	apmc_ck->regmap = regmap;

	ret = clk_hw_रेजिस्टर(शून्य, &apmc_ck->hw);
	अगर (ret) अणु
		kमुक्त(apmc_ck);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस &apmc_ck->hw;
पूर्ण
