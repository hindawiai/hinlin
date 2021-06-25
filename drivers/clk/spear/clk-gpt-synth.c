<शैली गुरु>
/*
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * General Purpose Timer Synthesizer घड़ी implementation
 */

#घोषणा pr_fmt(fmt) "clk-gpt-synth: " fmt

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश "clk.h"

#घोषणा GPT_MSCALE_MASK		0xFFF
#घोषणा GPT_NSCALE_SHIFT	12
#घोषणा GPT_NSCALE_MASK		0xF

/*
 * DOC: General Purpose Timer Synthesizer घड़ी
 *
 * Calculates gpt synth clk rate क्रम dअगरferent values of mscale and nscale
 *
 * Fout= Fin/((2 ^ (N+1)) * (M+1))
 */

#घोषणा to_clk_gpt(_hw) container_of(_hw, काष्ठा clk_gpt, hw)

अटल अचिन्हित दीर्घ gpt_calc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ prate,
		पूर्णांक index)
अणु
	काष्ठा clk_gpt *gpt = to_clk_gpt(hw);
	काष्ठा gpt_rate_tbl *rtbl = gpt->rtbl;

	prate /= ((1 << (rtbl[index].nscale + 1)) * (rtbl[index].mscale + 1));

	वापस prate;
पूर्ण

अटल दीर्घ clk_gpt_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
		अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_gpt *gpt = to_clk_gpt(hw);
	पूर्णांक unused;

	वापस clk_round_rate_index(hw, drate, *prate, gpt_calc_rate,
			gpt->rtbl_cnt, &unused);
पूर्ण

अटल अचिन्हित दीर्घ clk_gpt_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_gpt *gpt = to_clk_gpt(hw);
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक भाग = 1, val;

	अगर (gpt->lock)
		spin_lock_irqsave(gpt->lock, flags);

	val = पढ़ोl_relaxed(gpt->reg);

	अगर (gpt->lock)
		spin_unlock_irqrestore(gpt->lock, flags);

	भाग += val & GPT_MSCALE_MASK;
	भाग *= 1 << (((val >> GPT_NSCALE_SHIFT) & GPT_NSCALE_MASK) + 1);

	अगर (!भाग)
		वापस 0;

	वापस parent_rate / भाग;
पूर्ण

/* Configures new घड़ी rate of gpt */
अटल पूर्णांक clk_gpt_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
				अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_gpt *gpt = to_clk_gpt(hw);
	काष्ठा gpt_rate_tbl *rtbl = gpt->rtbl;
	अचिन्हित दीर्घ flags = 0, val;
	पूर्णांक i;

	clk_round_rate_index(hw, drate, prate, gpt_calc_rate, gpt->rtbl_cnt,
			&i);

	अगर (gpt->lock)
		spin_lock_irqsave(gpt->lock, flags);

	val = पढ़ोl(gpt->reg) & ~GPT_MSCALE_MASK;
	val &= ~(GPT_NSCALE_MASK << GPT_NSCALE_SHIFT);

	val |= rtbl[i].mscale & GPT_MSCALE_MASK;
	val |= (rtbl[i].nscale & GPT_NSCALE_MASK) << GPT_NSCALE_SHIFT;

	ग_लिखोl_relaxed(val, gpt->reg);

	अगर (gpt->lock)
		spin_unlock_irqrestore(gpt->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_gpt_ops = अणु
	.recalc_rate = clk_gpt_recalc_rate,
	.round_rate = clk_gpt_round_rate,
	.set_rate = clk_gpt_set_rate,
पूर्ण;

काष्ठा clk *clk_रेजिस्टर_gpt(स्थिर अक्षर *name, स्थिर अक्षर *parent_name, अचिन्हित
		दीर्घ flags, व्योम __iomem *reg, काष्ठा gpt_rate_tbl *rtbl, u8
		rtbl_cnt, spinlock_t *lock)
अणु
	काष्ठा clk_init_data init;
	काष्ठा clk_gpt *gpt;
	काष्ठा clk *clk;

	अगर (!name || !parent_name || !reg || !rtbl || !rtbl_cnt) अणु
		pr_err("Invalid arguments passed\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	gpt = kzalloc(माप(*gpt), GFP_KERNEL);
	अगर (!gpt)
		वापस ERR_PTR(-ENOMEM);

	/* काष्ठा clk_gpt assignments */
	gpt->reg = reg;
	gpt->rtbl = rtbl;
	gpt->rtbl_cnt = rtbl_cnt;
	gpt->lock = lock;
	gpt->hw.init = &init;

	init.name = name;
	init.ops = &clk_gpt_ops;
	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	clk = clk_रेजिस्टर(शून्य, &gpt->hw);
	अगर (!IS_ERR_OR_शून्य(clk))
		वापस clk;

	pr_err("clk register failed\n");
	kमुक्त(gpt);

	वापस शून्य;
पूर्ण
