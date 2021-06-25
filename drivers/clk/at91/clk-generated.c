<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2015 Aपंचांगel Corporation,
 *                     Nicolas Ferre <nicolas.ferre@aपंचांगel.com>
 *
 * Based on clk-programmable & clk-peripheral drivers by Boris BREZILLON.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "pmc.h"

#घोषणा GENERATED_MAX_DIV	255

काष्ठा clk_generated अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	काष्ठा clk_range range;
	spinlock_t *lock;
	u32 *mux_table;
	u32 id;
	u32 gckभाग;
	स्थिर काष्ठा clk_pcr_layout *layout;
	u8 parent_id;
	पूर्णांक chg_pid;
पूर्ण;

#घोषणा to_clk_generated(hw) \
	container_of(hw, काष्ठा clk_generated, hw)

अटल पूर्णांक clk_generated_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_generated *gck = to_clk_generated(hw);
	अचिन्हित दीर्घ flags;

	pr_debug("GCLK: %s, gckdiv = %d, parent id = %d\n",
		 __func__, gck->gckभाग, gck->parent_id);

	spin_lock_irqsave(gck->lock, flags);
	regmap_ग_लिखो(gck->regmap, gck->layout->offset,
		     (gck->id & gck->layout->pid_mask));
	regmap_update_bits(gck->regmap, gck->layout->offset,
			   AT91_PMC_PCR_GCKDIV_MASK | gck->layout->gckcss_mask |
			   gck->layout->cmd | AT91_PMC_PCR_GCKEN,
			   field_prep(gck->layout->gckcss_mask, gck->parent_id) |
			   gck->layout->cmd |
			   FIELD_PREP(AT91_PMC_PCR_GCKDIV_MASK, gck->gckभाग) |
			   AT91_PMC_PCR_GCKEN);
	spin_unlock_irqrestore(gck->lock, flags);
	वापस 0;
पूर्ण

अटल व्योम clk_generated_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_generated *gck = to_clk_generated(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(gck->lock, flags);
	regmap_ग_लिखो(gck->regmap, gck->layout->offset,
		     (gck->id & gck->layout->pid_mask));
	regmap_update_bits(gck->regmap, gck->layout->offset,
			   gck->layout->cmd | AT91_PMC_PCR_GCKEN,
			   gck->layout->cmd);
	spin_unlock_irqrestore(gck->lock, flags);
पूर्ण

अटल पूर्णांक clk_generated_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_generated *gck = to_clk_generated(hw);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक status;

	spin_lock_irqsave(gck->lock, flags);
	regmap_ग_लिखो(gck->regmap, gck->layout->offset,
		     (gck->id & gck->layout->pid_mask));
	regmap_पढ़ो(gck->regmap, gck->layout->offset, &status);
	spin_unlock_irqrestore(gck->lock, flags);

	वापस !!(status & AT91_PMC_PCR_GCKEN);
पूर्ण

अटल अचिन्हित दीर्घ
clk_generated_recalc_rate(काष्ठा clk_hw *hw,
			  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_generated *gck = to_clk_generated(hw);

	वापस DIV_ROUND_CLOSEST(parent_rate, gck->gckभाग + 1);
पूर्ण

अटल व्योम clk_generated_best_dअगरf(काष्ठा clk_rate_request *req,
				    काष्ठा clk_hw *parent,
				    अचिन्हित दीर्घ parent_rate, u32 भाग,
				    पूर्णांक *best_dअगरf, दीर्घ *best_rate)
अणु
	अचिन्हित दीर्घ पंचांगp_rate;
	पूर्णांक पंचांगp_dअगरf;

	अगर (!भाग)
		पंचांगp_rate = parent_rate;
	अन्यथा
		पंचांगp_rate = parent_rate / भाग;
	पंचांगp_dअगरf = असल(req->rate - पंचांगp_rate);

	अगर (*best_dअगरf < 0 || *best_dअगरf >= पंचांगp_dअगरf) अणु
		*best_rate = पंचांगp_rate;
		*best_dअगरf = पंचांगp_dअगरf;
		req->best_parent_rate = parent_rate;
		req->best_parent_hw = parent;
	पूर्ण
पूर्ण

अटल पूर्णांक clk_generated_determine_rate(काष्ठा clk_hw *hw,
					काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_generated *gck = to_clk_generated(hw);
	काष्ठा clk_hw *parent = शून्य;
	काष्ठा clk_rate_request req_parent = *req;
	दीर्घ best_rate = -EINVAL;
	अचिन्हित दीर्घ min_rate, parent_rate;
	पूर्णांक best_dअगरf = -1;
	पूर्णांक i;
	u32 भाग;

	क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++) अणु
		अगर (gck->chg_pid == i)
			जारी;

		parent = clk_hw_get_parent_by_index(hw, i);
		अगर (!parent)
			जारी;

		parent_rate = clk_hw_get_rate(parent);
		min_rate = DIV_ROUND_CLOSEST(parent_rate, GENERATED_MAX_DIV + 1);
		अगर (!parent_rate ||
		    (gck->range.max && min_rate > gck->range.max))
			जारी;

		भाग = DIV_ROUND_CLOSEST(parent_rate, req->rate);
		अगर (भाग > GENERATED_MAX_DIV + 1)
			भाग = GENERATED_MAX_DIV + 1;

		clk_generated_best_dअगरf(req, parent, parent_rate, भाग,
					&best_dअगरf, &best_rate);

		अगर (!best_dअगरf)
			अवरोध;
	पूर्ण

	/*
	 * The audio_pll rate can be modअगरied, unlike the five others घड़ीs
	 * that should never be altered.
	 * The audio_pll can technically be used by multiple consumers. However,
	 * with the rate locking, the first consumer to enable to घड़ी will be
	 * the one definitely setting the rate of the घड़ी.
	 * Since audio IPs are most likely to request the same rate, we enक्रमce
	 * that the only clks able to modअगरy gck rate are those of audio IPs.
	 */

	अगर (gck->chg_pid < 0)
		जाओ end;

	parent = clk_hw_get_parent_by_index(hw, gck->chg_pid);
	अगर (!parent)
		जाओ end;

	क्रम (भाग = 1; भाग < GENERATED_MAX_DIV + 2; भाग++) अणु
		req_parent.rate = req->rate * भाग;
		अगर (__clk_determine_rate(parent, &req_parent))
			जारी;
		clk_generated_best_dअगरf(req, parent, req_parent.rate, भाग,
					&best_dअगरf, &best_rate);

		अगर (!best_dअगरf)
			अवरोध;
	पूर्ण

end:
	pr_debug("GCLK: %s, best_rate = %ld, parent clk: %s @ %ld\n",
		 __func__, best_rate,
		 __clk_get_name((req->best_parent_hw)->clk),
		 req->best_parent_rate);

	अगर (best_rate < 0 || (gck->range.max && best_rate > gck->range.max))
		वापस -EINVAL;

	req->rate = best_rate;
	वापस 0;
पूर्ण

/* No modअगरication of hardware as we have the flag CLK_SET_PARENT_GATE set */
अटल पूर्णांक clk_generated_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_generated *gck = to_clk_generated(hw);

	अगर (index >= clk_hw_get_num_parents(hw))
		वापस -EINVAL;

	अगर (gck->mux_table)
		gck->parent_id = clk_mux_index_to_val(gck->mux_table, 0, index);
	अन्यथा
		gck->parent_id = index;

	वापस 0;
पूर्ण

अटल u8 clk_generated_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_generated *gck = to_clk_generated(hw);

	वापस gck->parent_id;
पूर्ण

/* No modअगरication of hardware as we have the flag CLK_SET_RATE_GATE set */
अटल पूर्णांक clk_generated_set_rate(काष्ठा clk_hw *hw,
				  अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_generated *gck = to_clk_generated(hw);
	u32 भाग;

	अगर (!rate)
		वापस -EINVAL;

	अगर (gck->range.max && rate > gck->range.max)
		वापस -EINVAL;

	भाग = DIV_ROUND_CLOSEST(parent_rate, rate);
	अगर (भाग > GENERATED_MAX_DIV + 1 || !भाग)
		वापस -EINVAL;

	gck->gckभाग = भाग - 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops generated_ops = अणु
	.enable = clk_generated_enable,
	.disable = clk_generated_disable,
	.is_enabled = clk_generated_is_enabled,
	.recalc_rate = clk_generated_recalc_rate,
	.determine_rate = clk_generated_determine_rate,
	.get_parent = clk_generated_get_parent,
	.set_parent = clk_generated_set_parent,
	.set_rate = clk_generated_set_rate,
पूर्ण;

/**
 * clk_generated_startup - Initialize a given घड़ी to its शेष parent and
 * भागisor parameter.
 *
 * @gck:	Generated घड़ी to set the startup parameters क्रम.
 *
 * Take parameters from the hardware and update local घड़ी configuration
 * accordingly.
 */
अटल व्योम clk_generated_startup(काष्ठा clk_generated *gck)
अणु
	u32 पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(gck->lock, flags);
	regmap_ग_लिखो(gck->regmap, gck->layout->offset,
		     (gck->id & gck->layout->pid_mask));
	regmap_पढ़ो(gck->regmap, gck->layout->offset, &पंचांगp);
	spin_unlock_irqrestore(gck->lock, flags);

	gck->parent_id = field_get(gck->layout->gckcss_mask, पंचांगp);
	gck->gckभाग = FIELD_GET(AT91_PMC_PCR_GCKDIV_MASK, पंचांगp);
पूर्ण

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_generated(काष्ठा regmap *regmap, spinlock_t *lock,
			    स्थिर काष्ठा clk_pcr_layout *layout,
			    स्थिर अक्षर *name, स्थिर अक्षर **parent_names,
			    u32 *mux_table, u8 num_parents, u8 id,
			    स्थिर काष्ठा clk_range *range,
			    पूर्णांक chg_pid)
अणु
	काष्ठा clk_generated *gck;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	gck = kzalloc(माप(*gck), GFP_KERNEL);
	अगर (!gck)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &generated_ops;
	init.parent_names = parent_names;
	init.num_parents = num_parents;
	init.flags = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE;
	अगर (chg_pid >= 0)
		init.flags |= CLK_SET_RATE_PARENT;

	gck->id = id;
	gck->hw.init = &init;
	gck->regmap = regmap;
	gck->lock = lock;
	gck->range = *range;
	gck->chg_pid = chg_pid;
	gck->layout = layout;
	gck->mux_table = mux_table;

	clk_generated_startup(gck);
	hw = &gck->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &gck->hw);
	अगर (ret) अणु
		kमुक्त(gck);
		hw = ERR_PTR(ret);
	पूर्ण अन्यथा अणु
		pmc_रेजिस्टर_id(id);
	पूर्ण

	वापस hw;
पूर्ण
