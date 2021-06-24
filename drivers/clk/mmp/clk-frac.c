<शैली गुरु>
/*
 * mmp factor घड़ी operation source file
 *
 * Copyright (C) 2012 Marvell
 * Chao Xie <xiechao.mail@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>

#समावेश "clk.h"
/*
 * It is M/N घड़ी
 *
 * Fout from synthesizer can be given from two equations:
 * numerator/denominator = Fin / (Fout * factor)
 */

#घोषणा to_clk_factor(hw) container_of(hw, काष्ठा mmp_clk_factor, hw)

अटल दीर्घ clk_factor_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
		अचिन्हित दीर्घ *prate)
अणु
	काष्ठा mmp_clk_factor *factor = to_clk_factor(hw);
	u64 rate = 0, prev_rate;
	पूर्णांक i;

	क्रम (i = 0; i < factor->ftbl_cnt; i++) अणु
		prev_rate = rate;
		rate = *prate;
		rate *= factor->ftbl[i].den;
		करो_भाग(rate, factor->ftbl[i].num * factor->masks->factor);

		अगर (rate > drate)
			अवरोध;
	पूर्ण
	अगर ((i == 0) || (i == factor->ftbl_cnt)) अणु
		वापस rate;
	पूर्ण अन्यथा अणु
		अगर ((drate - prev_rate) > (rate - drate))
			वापस rate;
		अन्यथा
			वापस prev_rate;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ clk_factor_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mmp_clk_factor *factor = to_clk_factor(hw);
	काष्ठा mmp_clk_factor_masks *masks = factor->masks;
	अचिन्हित पूर्णांक val, num, den;
	u64 rate;

	val = पढ़ोl_relaxed(factor->base);

	/* calculate numerator */
	num = (val >> masks->num_shअगरt) & masks->num_mask;

	/* calculate denominator */
	den = (val >> masks->den_shअगरt) & masks->den_mask;

	अगर (!den)
		वापस 0;

	rate = parent_rate;
	rate *= den;
	करो_भाग(rate, num * factor->masks->factor);

	वापस rate;
पूर्ण

/* Configures new घड़ी rate*/
अटल पूर्णांक clk_factor_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
				अचिन्हित दीर्घ prate)
अणु
	काष्ठा mmp_clk_factor *factor = to_clk_factor(hw);
	काष्ठा mmp_clk_factor_masks *masks = factor->masks;
	पूर्णांक i;
	अचिन्हित दीर्घ val;
	अचिन्हित दीर्घ flags = 0;
	u64 rate = 0;

	क्रम (i = 0; i < factor->ftbl_cnt; i++) अणु
		rate = prate;
		rate *= factor->ftbl[i].den;
		करो_भाग(rate, factor->ftbl[i].num * factor->masks->factor);

		अगर (rate > drate)
			अवरोध;
	पूर्ण
	अगर (i > 0)
		i--;

	अगर (factor->lock)
		spin_lock_irqsave(factor->lock, flags);

	val = पढ़ोl_relaxed(factor->base);

	val &= ~(masks->num_mask << masks->num_shअगरt);
	val |= (factor->ftbl[i].num & masks->num_mask) << masks->num_shअगरt;

	val &= ~(masks->den_mask << masks->den_shअगरt);
	val |= (factor->ftbl[i].den & masks->den_mask) << masks->den_shअगरt;

	ग_लिखोl_relaxed(val, factor->base);

	अगर (factor->lock)
		spin_unlock_irqrestore(factor->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_factor_init(काष्ठा clk_hw *hw)
अणु
	काष्ठा mmp_clk_factor *factor = to_clk_factor(hw);
	काष्ठा mmp_clk_factor_masks *masks = factor->masks;
	u32 val, num, den;
	पूर्णांक i;
	अचिन्हित दीर्घ flags = 0;

	अगर (factor->lock)
		spin_lock_irqsave(factor->lock, flags);

	val = पढ़ोl(factor->base);

	/* calculate numerator */
	num = (val >> masks->num_shअगरt) & masks->num_mask;

	/* calculate denominator */
	den = (val >> masks->den_shअगरt) & masks->den_mask;

	क्रम (i = 0; i < factor->ftbl_cnt; i++)
		अगर (den == factor->ftbl[i].den && num == factor->ftbl[i].num)
			अवरोध;

	अगर (i >= factor->ftbl_cnt) अणु
		val &= ~(masks->num_mask << masks->num_shअगरt);
		val |= (factor->ftbl[0].num & masks->num_mask) <<
			masks->num_shअगरt;

		val &= ~(masks->den_mask << masks->den_shअगरt);
		val |= (factor->ftbl[0].den & masks->den_mask) <<
			masks->den_shअगरt;
	पूर्ण

	अगर (!(val & masks->enable_mask) || i >= factor->ftbl_cnt) अणु
		val |= masks->enable_mask;
		ग_लिखोl(val, factor->base);
	पूर्ण

	अगर (factor->lock)
		spin_unlock_irqrestore(factor->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_factor_ops = अणु
	.recalc_rate = clk_factor_recalc_rate,
	.round_rate = clk_factor_round_rate,
	.set_rate = clk_factor_set_rate,
	.init = clk_factor_init,
पूर्ण;

काष्ठा clk *mmp_clk_रेजिस्टर_factor(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		अचिन्हित दीर्घ flags, व्योम __iomem *base,
		काष्ठा mmp_clk_factor_masks *masks,
		काष्ठा mmp_clk_factor_tbl *ftbl,
		अचिन्हित पूर्णांक ftbl_cnt, spinlock_t *lock)
अणु
	काष्ठा mmp_clk_factor *factor;
	काष्ठा clk_init_data init;
	काष्ठा clk *clk;

	अगर (!masks) अणु
		pr_err("%s: must pass a clk_factor_mask\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	factor = kzalloc(माप(*factor), GFP_KERNEL);
	अगर (!factor)
		वापस ERR_PTR(-ENOMEM);

	/* काष्ठा clk_aux assignments */
	factor->base = base;
	factor->masks = masks;
	factor->ftbl = ftbl;
	factor->ftbl_cnt = ftbl_cnt;
	factor->hw.init = &init;
	factor->lock = lock;

	init.name = name;
	init.ops = &clk_factor_ops;
	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	clk = clk_रेजिस्टर(शून्य, &factor->hw);
	अगर (IS_ERR_OR_शून्य(clk))
		kमुक्त(factor);

	वापस clk;
पूर्ण
