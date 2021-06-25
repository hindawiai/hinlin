<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2013 Boris BREZILLON <b.brezillon@overkiz.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "pmc.h"

DEFINE_SPINLOCK(pmc_pcr_lock);

#घोषणा PERIPHERAL_ID_MIN	2
#घोषणा PERIPHERAL_ID_MAX	31
#घोषणा PERIPHERAL_MASK(id)	(1 << ((id) & PERIPHERAL_ID_MAX))

#घोषणा PERIPHERAL_MAX_SHIFT	3

काष्ठा clk_peripheral अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u32 id;
पूर्ण;

#घोषणा to_clk_peripheral(hw) container_of(hw, काष्ठा clk_peripheral, hw)

काष्ठा clk_sam9x5_peripheral अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	काष्ठा clk_range range;
	spinlock_t *lock;
	u32 id;
	u32 भाग;
	स्थिर काष्ठा clk_pcr_layout *layout;
	bool स्वतः_भाग;
	पूर्णांक chg_pid;
पूर्ण;

#घोषणा to_clk_sam9x5_peripheral(hw) \
	container_of(hw, काष्ठा clk_sam9x5_peripheral, hw)

अटल पूर्णांक clk_peripheral_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_peripheral *periph = to_clk_peripheral(hw);
	पूर्णांक offset = AT91_PMC_PCER;
	u32 id = periph->id;

	अगर (id < PERIPHERAL_ID_MIN)
		वापस 0;
	अगर (id > PERIPHERAL_ID_MAX)
		offset = AT91_PMC_PCER1;
	regmap_ग_लिखो(periph->regmap, offset, PERIPHERAL_MASK(id));

	वापस 0;
पूर्ण

अटल व्योम clk_peripheral_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_peripheral *periph = to_clk_peripheral(hw);
	पूर्णांक offset = AT91_PMC_PCDR;
	u32 id = periph->id;

	अगर (id < PERIPHERAL_ID_MIN)
		वापस;
	अगर (id > PERIPHERAL_ID_MAX)
		offset = AT91_PMC_PCDR1;
	regmap_ग_लिखो(periph->regmap, offset, PERIPHERAL_MASK(id));
पूर्ण

अटल पूर्णांक clk_peripheral_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_peripheral *periph = to_clk_peripheral(hw);
	पूर्णांक offset = AT91_PMC_PCSR;
	अचिन्हित पूर्णांक status;
	u32 id = periph->id;

	अगर (id < PERIPHERAL_ID_MIN)
		वापस 1;
	अगर (id > PERIPHERAL_ID_MAX)
		offset = AT91_PMC_PCSR1;
	regmap_पढ़ो(periph->regmap, offset, &status);

	वापस status & PERIPHERAL_MASK(id) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops peripheral_ops = अणु
	.enable = clk_peripheral_enable,
	.disable = clk_peripheral_disable,
	.is_enabled = clk_peripheral_is_enabled,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_peripheral(काष्ठा regmap *regmap, स्थिर अक्षर *name,
			     स्थिर अक्षर *parent_name, u32 id)
अणु
	काष्ठा clk_peripheral *periph;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	अगर (!name || !parent_name || id > PERIPHERAL_ID_MAX)
		वापस ERR_PTR(-EINVAL);

	periph = kzalloc(माप(*periph), GFP_KERNEL);
	अगर (!periph)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &peripheral_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = 0;

	periph->id = id;
	periph->hw.init = &init;
	periph->regmap = regmap;

	hw = &periph->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &periph->hw);
	अगर (ret) अणु
		kमुक्त(periph);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

अटल व्योम clk_sam9x5_peripheral_स्वतःभाग(काष्ठा clk_sam9x5_peripheral *periph)
अणु
	काष्ठा clk_hw *parent;
	अचिन्हित दीर्घ parent_rate;
	पूर्णांक shअगरt = 0;

	अगर (!periph->स्वतः_भाग)
		वापस;

	अगर (periph->range.max) अणु
		parent = clk_hw_get_parent_by_index(&periph->hw, 0);
		parent_rate = clk_hw_get_rate(parent);
		अगर (!parent_rate)
			वापस;

		क्रम (; shअगरt < PERIPHERAL_MAX_SHIFT; shअगरt++) अणु
			अगर (parent_rate >> shअगरt <= periph->range.max)
				अवरोध;
		पूर्ण
	पूर्ण

	periph->स्वतः_भाग = false;
	periph->भाग = shअगरt;
पूर्ण

अटल पूर्णांक clk_sam9x5_peripheral_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sam9x5_peripheral *periph = to_clk_sam9x5_peripheral(hw);
	अचिन्हित दीर्घ flags;

	अगर (periph->id < PERIPHERAL_ID_MIN)
		वापस 0;

	spin_lock_irqsave(periph->lock, flags);
	regmap_ग_लिखो(periph->regmap, periph->layout->offset,
		     (periph->id & periph->layout->pid_mask));
	regmap_update_bits(periph->regmap, periph->layout->offset,
			   periph->layout->भाग_mask | periph->layout->cmd |
			   AT91_PMC_PCR_EN,
			   field_prep(periph->layout->भाग_mask, periph->भाग) |
			   periph->layout->cmd |
			   AT91_PMC_PCR_EN);
	spin_unlock_irqrestore(periph->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम clk_sam9x5_peripheral_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sam9x5_peripheral *periph = to_clk_sam9x5_peripheral(hw);
	अचिन्हित दीर्घ flags;

	अगर (periph->id < PERIPHERAL_ID_MIN)
		वापस;

	spin_lock_irqsave(periph->lock, flags);
	regmap_ग_लिखो(periph->regmap, periph->layout->offset,
		     (periph->id & periph->layout->pid_mask));
	regmap_update_bits(periph->regmap, periph->layout->offset,
			   AT91_PMC_PCR_EN | periph->layout->cmd,
			   periph->layout->cmd);
	spin_unlock_irqrestore(periph->lock, flags);
पूर्ण

अटल पूर्णांक clk_sam9x5_peripheral_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sam9x5_peripheral *periph = to_clk_sam9x5_peripheral(hw);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक status;

	अगर (periph->id < PERIPHERAL_ID_MIN)
		वापस 1;

	spin_lock_irqsave(periph->lock, flags);
	regmap_ग_लिखो(periph->regmap, periph->layout->offset,
		     (periph->id & periph->layout->pid_mask));
	regmap_पढ़ो(periph->regmap, periph->layout->offset, &status);
	spin_unlock_irqrestore(periph->lock, flags);

	वापस !!(status & AT91_PMC_PCR_EN);
पूर्ण

अटल अचिन्हित दीर्घ
clk_sam9x5_peripheral_recalc_rate(काष्ठा clk_hw *hw,
				  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_sam9x5_peripheral *periph = to_clk_sam9x5_peripheral(hw);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक status;

	अगर (periph->id < PERIPHERAL_ID_MIN)
		वापस parent_rate;

	spin_lock_irqsave(periph->lock, flags);
	regmap_ग_लिखो(periph->regmap, periph->layout->offset,
		     (periph->id & periph->layout->pid_mask));
	regmap_पढ़ो(periph->regmap, periph->layout->offset, &status);
	spin_unlock_irqrestore(periph->lock, flags);

	अगर (status & AT91_PMC_PCR_EN) अणु
		periph->भाग = field_get(periph->layout->भाग_mask, status);
		periph->स्वतः_भाग = false;
	पूर्ण अन्यथा अणु
		clk_sam9x5_peripheral_स्वतःभाग(periph);
	पूर्ण

	वापस parent_rate >> periph->भाग;
पूर्ण

अटल व्योम clk_sam9x5_peripheral_best_dअगरf(काष्ठा clk_rate_request *req,
					    काष्ठा clk_hw *parent,
					    अचिन्हित दीर्घ parent_rate,
					    u32 shअगरt, दीर्घ *best_dअगरf,
					    दीर्घ *best_rate)
अणु
	अचिन्हित दीर्घ पंचांगp_rate = parent_rate >> shअगरt;
	अचिन्हित दीर्घ पंचांगp_dअगरf = असल(req->rate - पंचांगp_rate);

	अगर (*best_dअगरf < 0 || *best_dअगरf >= पंचांगp_dअगरf) अणु
		*best_rate = पंचांगp_rate;
		*best_dअगरf = पंचांगp_dअगरf;
		req->best_parent_rate = parent_rate;
		req->best_parent_hw = parent;
	पूर्ण
पूर्ण

अटल पूर्णांक clk_sam9x5_peripheral_determine_rate(काष्ठा clk_hw *hw,
						काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_sam9x5_peripheral *periph = to_clk_sam9x5_peripheral(hw);
	काष्ठा clk_hw *parent = clk_hw_get_parent(hw);
	काष्ठा clk_rate_request req_parent = *req;
	अचिन्हित दीर्घ parent_rate = clk_hw_get_rate(parent);
	अचिन्हित दीर्घ पंचांगp_rate;
	दीर्घ best_rate = दीर्घ_न्यून;
	दीर्घ best_dअगरf = दीर्घ_न्यून;
	u32 shअगरt;

	अगर (periph->id < PERIPHERAL_ID_MIN || !periph->range.max)
		वापस parent_rate;

	/* Fist step: check the available भागiders. */
	क्रम (shअगरt = 0; shअगरt <= PERIPHERAL_MAX_SHIFT; shअगरt++) अणु
		पंचांगp_rate = parent_rate >> shअगरt;

		अगर (periph->range.max && पंचांगp_rate > periph->range.max)
			जारी;

		clk_sam9x5_peripheral_best_dअगरf(req, parent, parent_rate,
						shअगरt, &best_dअगरf, &best_rate);

		अगर (!best_dअगरf || best_rate <= req->rate)
			अवरोध;
	पूर्ण

	अगर (periph->chg_pid < 0)
		जाओ end;

	/* Step two: try to request rate from parent. */
	parent = clk_hw_get_parent_by_index(hw, periph->chg_pid);
	अगर (!parent)
		जाओ end;

	क्रम (shअगरt = 0; shअगरt <= PERIPHERAL_MAX_SHIFT; shअगरt++) अणु
		req_parent.rate = req->rate << shअगरt;

		अगर (__clk_determine_rate(parent, &req_parent))
			जारी;

		clk_sam9x5_peripheral_best_dअगरf(req, parent, req_parent.rate,
						shअगरt, &best_dअगरf, &best_rate);

		अगर (!best_dअगरf)
			अवरोध;
	पूर्ण
end:
	अगर (best_rate < 0 ||
	    (periph->range.max && best_rate > periph->range.max))
		वापस -EINVAL;

	pr_debug("PCK: %s, best_rate = %ld, parent clk: %s @ %ld\n",
		 __func__, best_rate,
		 __clk_get_name((req->best_parent_hw)->clk),
		 req->best_parent_rate);

	req->rate = best_rate;

	वापस 0;
पूर्ण

अटल दीर्घ clk_sam9x5_peripheral_round_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ rate,
					     अचिन्हित दीर्घ *parent_rate)
अणु
	पूर्णांक shअगरt = 0;
	अचिन्हित दीर्घ best_rate;
	अचिन्हित दीर्घ best_dअगरf;
	अचिन्हित दीर्घ cur_rate = *parent_rate;
	अचिन्हित दीर्घ cur_dअगरf;
	काष्ठा clk_sam9x5_peripheral *periph = to_clk_sam9x5_peripheral(hw);

	अगर (periph->id < PERIPHERAL_ID_MIN || !periph->range.max)
		वापस *parent_rate;

	अगर (periph->range.max) अणु
		क्रम (; shअगरt <= PERIPHERAL_MAX_SHIFT; shअगरt++) अणु
			cur_rate = *parent_rate >> shअगरt;
			अगर (cur_rate <= periph->range.max)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (rate >= cur_rate)
		वापस cur_rate;

	best_dअगरf = cur_rate - rate;
	best_rate = cur_rate;
	क्रम (; shअगरt <= PERIPHERAL_MAX_SHIFT; shअगरt++) अणु
		cur_rate = *parent_rate >> shअगरt;
		अगर (cur_rate < rate)
			cur_dअगरf = rate - cur_rate;
		अन्यथा
			cur_dअगरf = cur_rate - rate;

		अगर (cur_dअगरf < best_dअगरf) अणु
			best_dअगरf = cur_dअगरf;
			best_rate = cur_rate;
		पूर्ण

		अगर (!best_dअगरf || cur_rate < rate)
			अवरोध;
	पूर्ण

	वापस best_rate;
पूर्ण

अटल पूर्णांक clk_sam9x5_peripheral_set_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ rate,
					  अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक shअगरt;
	काष्ठा clk_sam9x5_peripheral *periph = to_clk_sam9x5_peripheral(hw);
	अगर (periph->id < PERIPHERAL_ID_MIN || !periph->range.max) अणु
		अगर (parent_rate == rate)
			वापस 0;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (periph->range.max && rate > periph->range.max)
		वापस -EINVAL;

	क्रम (shअगरt = 0; shअगरt <= PERIPHERAL_MAX_SHIFT; shअगरt++) अणु
		अगर (parent_rate >> shअगरt == rate) अणु
			periph->स्वतः_भाग = false;
			periph->भाग = shअगरt;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा clk_ops sam9x5_peripheral_ops = अणु
	.enable = clk_sam9x5_peripheral_enable,
	.disable = clk_sam9x5_peripheral_disable,
	.is_enabled = clk_sam9x5_peripheral_is_enabled,
	.recalc_rate = clk_sam9x5_peripheral_recalc_rate,
	.round_rate = clk_sam9x5_peripheral_round_rate,
	.set_rate = clk_sam9x5_peripheral_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops sam9x5_peripheral_chg_ops = अणु
	.enable = clk_sam9x5_peripheral_enable,
	.disable = clk_sam9x5_peripheral_disable,
	.is_enabled = clk_sam9x5_peripheral_is_enabled,
	.recalc_rate = clk_sam9x5_peripheral_recalc_rate,
	.determine_rate = clk_sam9x5_peripheral_determine_rate,
	.set_rate = clk_sam9x5_peripheral_set_rate,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_sam9x5_peripheral(काष्ठा regmap *regmap, spinlock_t *lock,
				    स्थिर काष्ठा clk_pcr_layout *layout,
				    स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
				    u32 id, स्थिर काष्ठा clk_range *range,
				    पूर्णांक chg_pid)
अणु
	काष्ठा clk_sam9x5_peripheral *periph;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	अगर (!name || !parent_name)
		वापस ERR_PTR(-EINVAL);

	periph = kzalloc(माप(*periph), GFP_KERNEL);
	अगर (!periph)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	अगर (chg_pid < 0) अणु
		init.flags = 0;
		init.ops = &sam9x5_peripheral_ops;
	पूर्ण अन्यथा अणु
		init.flags = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE |
			     CLK_SET_RATE_PARENT;
		init.ops = &sam9x5_peripheral_chg_ops;
	पूर्ण

	periph->id = id;
	periph->hw.init = &init;
	periph->भाग = 0;
	periph->regmap = regmap;
	periph->lock = lock;
	अगर (layout->भाग_mask)
		periph->स्वतः_भाग = true;
	periph->layout = layout;
	periph->range = *range;
	periph->chg_pid = chg_pid;

	hw = &periph->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &periph->hw);
	अगर (ret) अणु
		kमुक्त(periph);
		hw = ERR_PTR(ret);
	पूर्ण अन्यथा अणु
		clk_sam9x5_peripheral_स्वतःभाग(periph);
		pmc_रेजिस्टर_id(id);
	पूर्ण

	वापस hw;
पूर्ण
