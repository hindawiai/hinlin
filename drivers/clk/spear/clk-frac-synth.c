<शैली गुरु>
/*
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * Fractional Synthesizer घड़ी implementation
 */

#घोषणा pr_fmt(fmt) "clk-frac-synth: " fmt

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश "clk.h"

#घोषणा DIV_FACTOR_MASK		0x1FFFF

/*
 * DOC: Fractional Synthesizer घड़ी
 *
 * Fout from synthesizer can be given from below equation:
 *
 * Fout= Fin/2*भाग (भागision factor)
 * भाग is 17 bits:-
 *	0-13 (fractional part)
 *	14-16 (पूर्णांकeger part)
 *	भाग is (16-14 bits).(13-0 bits) (in binary)
 *
 *	Fout = Fin/(2 * भाग)
 *	Fout = ((Fin / 10000)/(2 * भाग)) * 10000
 *	Fout = (2^14 * (Fin / 10000)/(2^14 * (2 * भाग))) * 10000
 *	Fout = (((Fin / 10000) << 14)/(2 * (भाग << 14))) * 10000
 *
 * भाग << 14 simply 17 bit value written at रेजिस्टर.
 * Max error due to scaling करोwn by 10000 is 10 KHz
 */

#घोषणा to_clk_frac(_hw) container_of(_hw, काष्ठा clk_frac, hw)

अटल अचिन्हित दीर्घ frac_calc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ prate,
		पूर्णांक index)
अणु
	काष्ठा clk_frac *frac = to_clk_frac(hw);
	काष्ठा frac_rate_tbl *rtbl = frac->rtbl;

	prate /= 10000;
	prate <<= 14;
	prate /= (2 * rtbl[index].भाग);
	prate *= 10000;

	वापस prate;
पूर्ण

अटल दीर्घ clk_frac_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
		अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_frac *frac = to_clk_frac(hw);
	पूर्णांक unused;

	वापस clk_round_rate_index(hw, drate, *prate, frac_calc_rate,
			frac->rtbl_cnt, &unused);
पूर्ण

अटल अचिन्हित दीर्घ clk_frac_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_frac *frac = to_clk_frac(hw);
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक भाग = 1, val;

	अगर (frac->lock)
		spin_lock_irqsave(frac->lock, flags);

	val = पढ़ोl_relaxed(frac->reg);

	अगर (frac->lock)
		spin_unlock_irqrestore(frac->lock, flags);

	भाग = val & DIV_FACTOR_MASK;

	अगर (!भाग)
		वापस 0;

	parent_rate = parent_rate / 10000;

	parent_rate = (parent_rate << 14) / (2 * भाग);
	वापस parent_rate * 10000;
पूर्ण

/* Configures new घड़ी rate of frac */
अटल पूर्णांक clk_frac_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
				अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_frac *frac = to_clk_frac(hw);
	काष्ठा frac_rate_tbl *rtbl = frac->rtbl;
	अचिन्हित दीर्घ flags = 0, val;
	पूर्णांक i;

	clk_round_rate_index(hw, drate, prate, frac_calc_rate, frac->rtbl_cnt,
			&i);

	अगर (frac->lock)
		spin_lock_irqsave(frac->lock, flags);

	val = पढ़ोl_relaxed(frac->reg) & ~DIV_FACTOR_MASK;
	val |= rtbl[i].भाग & DIV_FACTOR_MASK;
	ग_लिखोl_relaxed(val, frac->reg);

	अगर (frac->lock)
		spin_unlock_irqrestore(frac->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_frac_ops = अणु
	.recalc_rate = clk_frac_recalc_rate,
	.round_rate = clk_frac_round_rate,
	.set_rate = clk_frac_set_rate,
पूर्ण;

काष्ठा clk *clk_रेजिस्टर_frac(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg,
		काष्ठा frac_rate_tbl *rtbl, u8 rtbl_cnt, spinlock_t *lock)
अणु
	काष्ठा clk_init_data init;
	काष्ठा clk_frac *frac;
	काष्ठा clk *clk;

	अगर (!name || !parent_name || !reg || !rtbl || !rtbl_cnt) अणु
		pr_err("Invalid arguments passed\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	frac = kzalloc(माप(*frac), GFP_KERNEL);
	अगर (!frac)
		वापस ERR_PTR(-ENOMEM);

	/* काष्ठा clk_frac assignments */
	frac->reg = reg;
	frac->rtbl = rtbl;
	frac->rtbl_cnt = rtbl_cnt;
	frac->lock = lock;
	frac->hw.init = &init;

	init.name = name;
	init.ops = &clk_frac_ops;
	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	clk = clk_रेजिस्टर(शून्य, &frac->hw);
	अगर (!IS_ERR_OR_शून्य(clk))
		वापस clk;

	pr_err("clk register failed\n");
	kमुक्त(frac);

	वापस शून्य;
पूर्ण
