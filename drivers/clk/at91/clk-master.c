<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2013 Boris BREZILLON <b.brezillon@overkiz.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "pmc.h"

#घोषणा MASTER_PRES_MASK	0x7
#घोषणा MASTER_PRES_MAX		MASTER_PRES_MASK
#घोषणा MASTER_DIV_SHIFT	8
#घोषणा MASTER_DIV_MASK		0x7

#घोषणा PMC_MCR			0x30
#घोषणा PMC_MCR_ID_MSK		GENMASK(3, 0)
#घोषणा PMC_MCR_CMD		BIT(7)
#घोषणा PMC_MCR_DIV		GENMASK(10, 8)
#घोषणा PMC_MCR_CSS		GENMASK(20, 16)
#घोषणा PMC_MCR_CSS_SHIFT	(16)
#घोषणा PMC_MCR_EN		BIT(28)

#घोषणा PMC_MCR_ID(x)		((x) & PMC_MCR_ID_MSK)

#घोषणा MASTER_MAX_ID		4

#घोषणा to_clk_master(hw) container_of(hw, काष्ठा clk_master, hw)

काष्ठा clk_master अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	spinlock_t *lock;
	स्थिर काष्ठा clk_master_layout *layout;
	स्थिर काष्ठा clk_master_अक्षरacteristics *अक्षरacteristics;
	u32 *mux_table;
	u32 mckr;
	पूर्णांक chg_pid;
	u8 id;
	u8 parent;
	u8 भाग;
पूर्ण;

अटल अंतरभूत bool clk_master_पढ़ोy(काष्ठा clk_master *master)
अणु
	अचिन्हित पूर्णांक bit = master->id ? AT91_PMC_MCKXRDY : AT91_PMC_MCKRDY;
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(master->regmap, AT91_PMC_SR, &status);

	वापस !!(status & bit);
पूर्ण

अटल पूर्णांक clk_master_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(master->lock, flags);

	जबतक (!clk_master_पढ़ोy(master))
		cpu_relax();

	spin_unlock_irqrestore(master->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_master_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	अचिन्हित दीर्घ flags;
	bool status;

	spin_lock_irqsave(master->lock, flags);
	status = clk_master_पढ़ोy(master);
	spin_unlock_irqrestore(master->lock, flags);

	वापस status;
पूर्ण

अटल अचिन्हित दीर्घ clk_master_भाग_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	u8 भाग;
	अचिन्हित दीर्घ flags, rate = parent_rate;
	काष्ठा clk_master *master = to_clk_master(hw);
	स्थिर काष्ठा clk_master_layout *layout = master->layout;
	स्थिर काष्ठा clk_master_अक्षरacteristics *अक्षरacteristics =
						master->अक्षरacteristics;
	अचिन्हित पूर्णांक mckr;

	spin_lock_irqsave(master->lock, flags);
	regmap_पढ़ो(master->regmap, master->layout->offset, &mckr);
	spin_unlock_irqrestore(master->lock, flags);

	mckr &= layout->mask;

	भाग = (mckr >> MASTER_DIV_SHIFT) & MASTER_DIV_MASK;

	rate /= अक्षरacteristics->भागisors[भाग];

	अगर (rate < अक्षरacteristics->output.min)
		pr_warn("master clk div is underclocked");
	अन्यथा अगर (rate > अक्षरacteristics->output.max)
		pr_warn("master clk div is overclocked");

	वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops master_भाग_ops = अणु
	.prepare = clk_master_prepare,
	.is_prepared = clk_master_is_prepared,
	.recalc_rate = clk_master_भाग_recalc_rate,
पूर्ण;

अटल पूर्णांक clk_master_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	स्थिर काष्ठा clk_master_अक्षरacteristics *अक्षरacteristics =
						master->अक्षरacteristics;
	अचिन्हित दीर्घ flags;
	पूर्णांक भाग, i;

	भाग = DIV_ROUND_CLOSEST(parent_rate, rate);
	अगर (भाग > ARRAY_SIZE(अक्षरacteristics->भागisors))
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(अक्षरacteristics->भागisors); i++) अणु
		अगर (!अक्षरacteristics->भागisors[i])
			अवरोध;

		अगर (भाग == अक्षरacteristics->भागisors[i]) अणु
			भाग = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(अक्षरacteristics->भागisors))
		वापस -EINVAL;

	spin_lock_irqsave(master->lock, flags);
	regmap_update_bits(master->regmap, master->layout->offset,
			   (MASTER_DIV_MASK << MASTER_DIV_SHIFT),
			   (भाग << MASTER_DIV_SHIFT));
	जबतक (!clk_master_पढ़ोy(master))
		cpu_relax();
	spin_unlock_irqrestore(master->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_master_भाग_determine_rate(काष्ठा clk_hw *hw,
					 काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	स्थिर काष्ठा clk_master_अक्षरacteristics *अक्षरacteristics =
						master->अक्षरacteristics;
	काष्ठा clk_hw *parent;
	अचिन्हित दीर्घ parent_rate, पंचांगp_rate, best_rate = 0;
	पूर्णांक i, best_dअगरf = पूर्णांक_न्यून, पंचांगp_dअगरf;

	parent = clk_hw_get_parent(hw);
	अगर (!parent)
		वापस -EINVAL;

	parent_rate = clk_hw_get_rate(parent);
	अगर (!parent_rate)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(अक्षरacteristics->भागisors); i++) अणु
		अगर (!अक्षरacteristics->भागisors[i])
			अवरोध;

		पंचांगp_rate = DIV_ROUND_CLOSEST_ULL(parent_rate,
						 अक्षरacteristics->भागisors[i]);
		पंचांगp_dअगरf = असल(पंचांगp_rate - req->rate);

		अगर (!best_rate || best_dअगरf > पंचांगp_dअगरf) अणु
			best_dअगरf = पंचांगp_dअगरf;
			best_rate = पंचांगp_rate;
		पूर्ण

		अगर (!best_dअगरf)
			अवरोध;
	पूर्ण

	req->best_parent_rate = best_rate;
	req->best_parent_hw = parent;
	req->rate = best_rate;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops master_भाग_ops_chg = अणु
	.prepare = clk_master_prepare,
	.is_prepared = clk_master_is_prepared,
	.recalc_rate = clk_master_भाग_recalc_rate,
	.determine_rate = clk_master_भाग_determine_rate,
	.set_rate = clk_master_भाग_set_rate,
पूर्ण;

अटल व्योम clk_sama7g5_master_best_dअगरf(काष्ठा clk_rate_request *req,
					 काष्ठा clk_hw *parent,
					 अचिन्हित दीर्घ parent_rate,
					 दीर्घ *best_rate,
					 दीर्घ *best_dअगरf,
					 u32 भाग)
अणु
	अचिन्हित दीर्घ पंचांगp_rate, पंचांगp_dअगरf;

	अगर (भाग == MASTER_PRES_MAX)
		पंचांगp_rate = parent_rate / 3;
	अन्यथा
		पंचांगp_rate = parent_rate >> भाग;

	पंचांगp_dअगरf = असल(req->rate - पंचांगp_rate);

	अगर (*best_dअगरf < 0 || *best_dअगरf >= पंचांगp_dअगरf) अणु
		*best_rate = पंचांगp_rate;
		*best_dअगरf = पंचांगp_dअगरf;
		req->best_parent_rate = parent_rate;
		req->best_parent_hw = parent;
	पूर्ण
पूर्ण

अटल पूर्णांक clk_master_pres_determine_rate(काष्ठा clk_hw *hw,
					  काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	काष्ठा clk_rate_request req_parent = *req;
	स्थिर काष्ठा clk_master_अक्षरacteristics *अक्षरacteristics =
							master->अक्षरacteristics;
	काष्ठा clk_hw *parent;
	दीर्घ best_rate = दीर्घ_न्यून, best_dअगरf = दीर्घ_न्यून;
	u32 pres;
	पूर्णांक i;

	अगर (master->chg_pid < 0)
		वापस -EOPNOTSUPP;

	parent = clk_hw_get_parent_by_index(hw, master->chg_pid);
	अगर (!parent)
		वापस -EOPNOTSUPP;

	क्रम (i = 0; i <= MASTER_PRES_MAX; i++) अणु
		अगर (अक्षरacteristics->have_भाग3_pres && i == MASTER_PRES_MAX)
			pres = 3;
		अन्यथा
			pres = 1 << i;

		req_parent.rate = req->rate * pres;
		अगर (__clk_determine_rate(parent, &req_parent))
			जारी;

		clk_sama7g5_master_best_dअगरf(req, parent, req_parent.rate,
					     &best_dअगरf, &best_rate, pres);
		अगर (!best_dअगरf)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक clk_master_pres_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक pres;

	pres = DIV_ROUND_CLOSEST(parent_rate, rate);
	अगर (pres > MASTER_PRES_MAX)
		वापस -EINVAL;

	अन्यथा अगर (pres == 3)
		pres = MASTER_PRES_MAX;
	अन्यथा
		pres = ffs(pres) - 1;

	spin_lock_irqsave(master->lock, flags);
	regmap_update_bits(master->regmap, master->layout->offset,
			   (MASTER_PRES_MASK << master->layout->pres_shअगरt),
			   (pres << master->layout->pres_shअगरt));

	जबतक (!clk_master_पढ़ोy(master))
		cpu_relax();
	spin_unlock_irqrestore(master->lock, flags);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ clk_master_pres_recalc_rate(काष्ठा clk_hw *hw,
						 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	स्थिर काष्ठा clk_master_अक्षरacteristics *अक्षरacteristics =
						master->अक्षरacteristics;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val, pres;

	spin_lock_irqsave(master->lock, flags);
	regmap_पढ़ो(master->regmap, master->layout->offset, &val);
	spin_unlock_irqrestore(master->lock, flags);

	pres = (val >> master->layout->pres_shअगरt) & MASTER_PRES_MASK;
	अगर (pres == 3 && अक्षरacteristics->have_भाग3_pres)
		pres = 3;
	अन्यथा
		pres = (1 << pres);

	वापस DIV_ROUND_CLOSEST_ULL(parent_rate, pres);
पूर्ण

अटल u8 clk_master_pres_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mckr;

	spin_lock_irqsave(master->lock, flags);
	regmap_पढ़ो(master->regmap, master->layout->offset, &mckr);
	spin_unlock_irqrestore(master->lock, flags);

	वापस mckr & AT91_PMC_CSS;
पूर्ण

अटल स्थिर काष्ठा clk_ops master_pres_ops = अणु
	.prepare = clk_master_prepare,
	.is_prepared = clk_master_is_prepared,
	.recalc_rate = clk_master_pres_recalc_rate,
	.get_parent = clk_master_pres_get_parent,
पूर्ण;

अटल स्थिर काष्ठा clk_ops master_pres_ops_chg = अणु
	.prepare = clk_master_prepare,
	.is_prepared = clk_master_is_prepared,
	.determine_rate = clk_master_pres_determine_rate,
	.recalc_rate = clk_master_pres_recalc_rate,
	.get_parent = clk_master_pres_get_parent,
	.set_rate = clk_master_pres_set_rate,
पूर्ण;

अटल काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_master_पूर्णांकernal(काष्ठा regmap *regmap,
		स्थिर अक्षर *name, पूर्णांक num_parents,
		स्थिर अक्षर **parent_names,
		स्थिर काष्ठा clk_master_layout *layout,
		स्थिर काष्ठा clk_master_अक्षरacteristics *अक्षरacteristics,
		स्थिर काष्ठा clk_ops *ops, spinlock_t *lock, u32 flags,
		पूर्णांक chg_pid)
अणु
	काष्ठा clk_master *master;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	अगर (!name || !num_parents || !parent_names || !lock)
		वापस ERR_PTR(-EINVAL);

	master = kzalloc(माप(*master), GFP_KERNEL);
	अगर (!master)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = ops;
	init.parent_names = parent_names;
	init.num_parents = num_parents;
	init.flags = flags;

	master->hw.init = &init;
	master->layout = layout;
	master->अक्षरacteristics = अक्षरacteristics;
	master->regmap = regmap;
	master->chg_pid = chg_pid;
	master->lock = lock;

	hw = &master->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &master->hw);
	अगर (ret) अणु
		kमुक्त(master);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_master_pres(काष्ठा regmap *regmap,
		स्थिर अक्षर *name, पूर्णांक num_parents,
		स्थिर अक्षर **parent_names,
		स्थिर काष्ठा clk_master_layout *layout,
		स्थिर काष्ठा clk_master_अक्षरacteristics *अक्षरacteristics,
		spinlock_t *lock, u32 flags, पूर्णांक chg_pid)
अणु
	स्थिर काष्ठा clk_ops *ops;

	अगर (flags & CLK_SET_RATE_GATE)
		ops = &master_pres_ops;
	अन्यथा
		ops = &master_pres_ops_chg;

	वापस at91_clk_रेजिस्टर_master_पूर्णांकernal(regmap, name, num_parents,
						 parent_names, layout,
						 अक्षरacteristics, ops,
						 lock, flags, chg_pid);
पूर्ण

काष्ठा clk_hw * __init
at91_clk_रेजिस्टर_master_भाग(काष्ठा regmap *regmap,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		स्थिर काष्ठा clk_master_layout *layout,
		स्थिर काष्ठा clk_master_अक्षरacteristics *अक्षरacteristics,
		spinlock_t *lock, u32 flags)
अणु
	स्थिर काष्ठा clk_ops *ops;

	अगर (flags & CLK_SET_RATE_GATE)
		ops = &master_भाग_ops;
	अन्यथा
		ops = &master_भाग_ops_chg;

	वापस at91_clk_रेजिस्टर_master_पूर्णांकernal(regmap, name, 1,
						 &parent_name, layout,
						 अक्षरacteristics, ops,
						 lock, flags, -EINVAL);
पूर्ण

अटल अचिन्हित दीर्घ
clk_sama7g5_master_recalc_rate(काष्ठा clk_hw *hw,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);

	वापस DIV_ROUND_CLOSEST_ULL(parent_rate, (1 << master->भाग));
पूर्ण

अटल पूर्णांक clk_sama7g5_master_determine_rate(काष्ठा clk_hw *hw,
					     काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	काष्ठा clk_rate_request req_parent = *req;
	काष्ठा clk_hw *parent;
	दीर्घ best_rate = दीर्घ_न्यून, best_dअगरf = दीर्घ_न्यून;
	अचिन्हित दीर्घ parent_rate;
	अचिन्हित पूर्णांक भाग, i;

	/* First: check the भागiders of MCR. */
	क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++) अणु
		parent = clk_hw_get_parent_by_index(hw, i);
		अगर (!parent)
			जारी;

		parent_rate = clk_hw_get_rate(parent);
		अगर (!parent_rate)
			जारी;

		क्रम (भाग = 0; भाग < MASTER_PRES_MAX + 1; भाग++) अणु
			clk_sama7g5_master_best_dअगरf(req, parent, parent_rate,
						     &best_rate, &best_dअगरf,
						     भाग);
			अगर (!best_dअगरf)
				अवरोध;
		पूर्ण

		अगर (!best_dअगरf)
			अवरोध;
	पूर्ण

	/* Second: try to request rate क्रमm changeable parent. */
	अगर (master->chg_pid < 0)
		जाओ end;

	parent = clk_hw_get_parent_by_index(hw, master->chg_pid);
	अगर (!parent)
		जाओ end;

	क्रम (भाग = 0; भाग < MASTER_PRES_MAX + 1; भाग++) अणु
		अगर (भाग == MASTER_PRES_MAX)
			req_parent.rate = req->rate * 3;
		अन्यथा
			req_parent.rate = req->rate << भाग;

		अगर (__clk_determine_rate(parent, &req_parent))
			जारी;

		clk_sama7g5_master_best_dअगरf(req, parent, req_parent.rate,
					     &best_rate, &best_dअगरf, भाग);

		अगर (!best_dअगरf)
			अवरोध;
	पूर्ण

end:
	pr_debug("MCK: %s, best_rate = %ld, parent clk: %s @ %ld\n",
		 __func__, best_rate,
		 __clk_get_name((req->best_parent_hw)->clk),
		req->best_parent_rate);

	अगर (best_rate < 0)
		वापस -EINVAL;

	req->rate = best_rate;

	वापस 0;
पूर्ण

अटल u8 clk_sama7g5_master_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	अचिन्हित दीर्घ flags;
	u8 index;

	spin_lock_irqsave(master->lock, flags);
	index = clk_mux_val_to_index(&master->hw, master->mux_table, 0,
				     master->parent);
	spin_unlock_irqrestore(master->lock, flags);

	वापस index;
पूर्ण

अटल पूर्णांक clk_sama7g5_master_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	अचिन्हित दीर्घ flags;

	अगर (index >= clk_hw_get_num_parents(hw))
		वापस -EINVAL;

	spin_lock_irqsave(master->lock, flags);
	master->parent = clk_mux_index_to_val(master->mux_table, 0, index);
	spin_unlock_irqrestore(master->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_sama7g5_master_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val, cparent;

	spin_lock_irqsave(master->lock, flags);

	regmap_ग_लिखो(master->regmap, PMC_MCR, PMC_MCR_ID(master->id));
	regmap_पढ़ो(master->regmap, PMC_MCR, &val);
	regmap_update_bits(master->regmap, PMC_MCR,
			   PMC_MCR_EN | PMC_MCR_CSS | PMC_MCR_DIV |
			   PMC_MCR_CMD | PMC_MCR_ID_MSK,
			   PMC_MCR_EN | (master->parent << PMC_MCR_CSS_SHIFT) |
			   (master->भाग << MASTER_DIV_SHIFT) |
			   PMC_MCR_CMD | PMC_MCR_ID(master->id));

	cparent = (val & PMC_MCR_CSS) >> PMC_MCR_CSS_SHIFT;

	/* Wait here only अगर parent is being changed. */
	जबतक ((cparent != master->parent) && !clk_master_पढ़ोy(master))
		cpu_relax();

	spin_unlock_irqrestore(master->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम clk_sama7g5_master_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(master->lock, flags);

	regmap_ग_लिखो(master->regmap, PMC_MCR, master->id);
	regmap_update_bits(master->regmap, PMC_MCR,
			   PMC_MCR_EN | PMC_MCR_CMD | PMC_MCR_ID_MSK,
			   PMC_MCR_CMD | PMC_MCR_ID(master->id));

	spin_unlock_irqrestore(master->lock, flags);
पूर्ण

अटल पूर्णांक clk_sama7g5_master_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(master->lock, flags);

	regmap_ग_लिखो(master->regmap, PMC_MCR, master->id);
	regmap_पढ़ो(master->regmap, PMC_MCR, &val);

	spin_unlock_irqrestore(master->lock, flags);

	वापस !!(val & PMC_MCR_EN);
पूर्ण

अटल पूर्णांक clk_sama7g5_master_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_master *master = to_clk_master(hw);
	अचिन्हित दीर्घ भाग, flags;

	भाग = DIV_ROUND_CLOSEST(parent_rate, rate);
	अगर ((भाग > (1 << (MASTER_PRES_MAX - 1))) || (भाग & (भाग - 1)))
		वापस -EINVAL;

	अगर (भाग == 3)
		भाग = MASTER_PRES_MAX;
	अन्यथा
		भाग = ffs(भाग) - 1;

	spin_lock_irqsave(master->lock, flags);
	master->भाग = भाग;
	spin_unlock_irqrestore(master->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops sama7g5_master_ops = अणु
	.enable = clk_sama7g5_master_enable,
	.disable = clk_sama7g5_master_disable,
	.is_enabled = clk_sama7g5_master_is_enabled,
	.recalc_rate = clk_sama7g5_master_recalc_rate,
	.determine_rate = clk_sama7g5_master_determine_rate,
	.set_rate = clk_sama7g5_master_set_rate,
	.get_parent = clk_sama7g5_master_get_parent,
	.set_parent = clk_sama7g5_master_set_parent,
पूर्ण;

काष्ठा clk_hw * __init
at91_clk_sama7g5_रेजिस्टर_master(काष्ठा regmap *regmap,
				 स्थिर अक्षर *name, पूर्णांक num_parents,
				 स्थिर अक्षर **parent_names,
				 u32 *mux_table,
				 spinlock_t *lock, u8 id,
				 bool critical, पूर्णांक chg_pid)
अणु
	काष्ठा clk_master *master;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (!name || !num_parents || !parent_names || !mux_table ||
	    !lock || id > MASTER_MAX_ID)
		वापस ERR_PTR(-EINVAL);

	master = kzalloc(माप(*master), GFP_KERNEL);
	अगर (!master)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &sama7g5_master_ops;
	init.parent_names = parent_names;
	init.num_parents = num_parents;
	init.flags = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE;
	अगर (chg_pid >= 0)
		init.flags |= CLK_SET_RATE_PARENT;
	अगर (critical)
		init.flags |= CLK_IS_CRITICAL;

	master->hw.init = &init;
	master->regmap = regmap;
	master->id = id;
	master->chg_pid = chg_pid;
	master->lock = lock;
	master->mux_table = mux_table;

	spin_lock_irqsave(master->lock, flags);
	regmap_ग_लिखो(master->regmap, PMC_MCR, master->id);
	regmap_पढ़ो(master->regmap, PMC_MCR, &val);
	master->parent = (val & PMC_MCR_CSS) >> PMC_MCR_CSS_SHIFT;
	master->भाग = (val & PMC_MCR_DIV) >> MASTER_DIV_SHIFT;
	spin_unlock_irqrestore(master->lock, flags);

	hw = &master->hw;
	ret = clk_hw_रेजिस्टर(शून्य, &master->hw);
	अगर (ret) अणु
		kमुक्त(master);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

स्थिर काष्ठा clk_master_layout at91rm9200_master_layout = अणु
	.mask = 0x31F,
	.pres_shअगरt = 2,
	.offset = AT91_PMC_MCKR,
पूर्ण;

स्थिर काष्ठा clk_master_layout at91sam9x5_master_layout = अणु
	.mask = 0x373,
	.pres_shअगरt = 4,
	.offset = AT91_PMC_MCKR,
पूर्ण;
