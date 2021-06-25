<शैली गुरु>
/*
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * Auxiliary Synthesizer घड़ी implementation
 */

#घोषणा pr_fmt(fmt) "clk-aux-synth: " fmt

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश "clk.h"

/*
 * DOC: Auxiliary Synthesizer घड़ी
 *
 * Aux synth gives rate क्रम dअगरferent values of eq, x and y
 *
 * Fout from synthesizer can be given from two equations:
 * Fout1 = (Fin * X/Y)/2		EQ1
 * Fout2 = Fin * X/Y			EQ2
 */

#घोषणा to_clk_aux(_hw) container_of(_hw, काष्ठा clk_aux, hw)

अटल स्थिर  काष्ठा aux_clk_masks शेष_aux_masks = अणु
	.eq_sel_mask = AUX_EQ_SEL_MASK,
	.eq_sel_shअगरt = AUX_EQ_SEL_SHIFT,
	.eq1_mask = AUX_EQ1_SEL,
	.eq2_mask = AUX_EQ2_SEL,
	.xscale_sel_mask = AUX_XSCALE_MASK,
	.xscale_sel_shअगरt = AUX_XSCALE_SHIFT,
	.yscale_sel_mask = AUX_YSCALE_MASK,
	.yscale_sel_shअगरt = AUX_YSCALE_SHIFT,
	.enable_bit = AUX_SYNT_ENB,
पूर्ण;

अटल अचिन्हित दीर्घ aux_calc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ prate,
		पूर्णांक index)
अणु
	काष्ठा clk_aux *aux = to_clk_aux(hw);
	काष्ठा aux_rate_tbl *rtbl = aux->rtbl;
	u8 eq = rtbl[index].eq ? 1 : 2;

	वापस (((prate / 10000) * rtbl[index].xscale) /
			(rtbl[index].yscale * eq)) * 10000;
पूर्ण

अटल दीर्घ clk_aux_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
		अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_aux *aux = to_clk_aux(hw);
	पूर्णांक unused;

	वापस clk_round_rate_index(hw, drate, *prate, aux_calc_rate,
			aux->rtbl_cnt, &unused);
पूर्ण

अटल अचिन्हित दीर्घ clk_aux_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_aux *aux = to_clk_aux(hw);
	अचिन्हित पूर्णांक num = 1, den = 1, val, eqn;
	अचिन्हित दीर्घ flags = 0;

	अगर (aux->lock)
		spin_lock_irqsave(aux->lock, flags);

	val = पढ़ोl_relaxed(aux->reg);

	अगर (aux->lock)
		spin_unlock_irqrestore(aux->lock, flags);

	eqn = (val >> aux->masks->eq_sel_shअगरt) & aux->masks->eq_sel_mask;
	अगर (eqn == aux->masks->eq1_mask)
		den = 2;

	/* calculate numerator */
	num = (val >> aux->masks->xscale_sel_shअगरt) &
		aux->masks->xscale_sel_mask;

	/* calculate denominator */
	den *= (val >> aux->masks->yscale_sel_shअगरt) &
		aux->masks->yscale_sel_mask;

	अगर (!den)
		वापस 0;

	वापस (((parent_rate / 10000) * num) / den) * 10000;
पूर्ण

/* Configures new घड़ी rate of aux */
अटल पूर्णांक clk_aux_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
				अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_aux *aux = to_clk_aux(hw);
	काष्ठा aux_rate_tbl *rtbl = aux->rtbl;
	अचिन्हित दीर्घ val, flags = 0;
	पूर्णांक i;

	clk_round_rate_index(hw, drate, prate, aux_calc_rate, aux->rtbl_cnt,
			&i);

	अगर (aux->lock)
		spin_lock_irqsave(aux->lock, flags);

	val = पढ़ोl_relaxed(aux->reg) &
		~(aux->masks->eq_sel_mask << aux->masks->eq_sel_shअगरt);
	val |= (rtbl[i].eq & aux->masks->eq_sel_mask) <<
		aux->masks->eq_sel_shअगरt;
	val &= ~(aux->masks->xscale_sel_mask << aux->masks->xscale_sel_shअगरt);
	val |= (rtbl[i].xscale & aux->masks->xscale_sel_mask) <<
		aux->masks->xscale_sel_shअगरt;
	val &= ~(aux->masks->yscale_sel_mask << aux->masks->yscale_sel_shअगरt);
	val |= (rtbl[i].yscale & aux->masks->yscale_sel_mask) <<
		aux->masks->yscale_sel_shअगरt;
	ग_लिखोl_relaxed(val, aux->reg);

	अगर (aux->lock)
		spin_unlock_irqrestore(aux->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_aux_ops = अणु
	.recalc_rate = clk_aux_recalc_rate,
	.round_rate = clk_aux_round_rate,
	.set_rate = clk_aux_set_rate,
पूर्ण;

काष्ठा clk *clk_रेजिस्टर_aux(स्थिर अक्षर *aux_name, स्थिर अक्षर *gate_name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags, व्योम __iomem *reg,
	        स्थिर काष्ठा aux_clk_masks *masks, काष्ठा aux_rate_tbl *rtbl,
		u8 rtbl_cnt, spinlock_t *lock, काष्ठा clk **gate_clk)
अणु
	काष्ठा clk_aux *aux;
	काष्ठा clk_init_data init;
	काष्ठा clk *clk;

	अगर (!aux_name || !parent_name || !reg || !rtbl || !rtbl_cnt) अणु
		pr_err("Invalid arguments passed");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	aux = kzalloc(माप(*aux), GFP_KERNEL);
	अगर (!aux)
		वापस ERR_PTR(-ENOMEM);

	/* काष्ठा clk_aux assignments */
	अगर (!masks)
		aux->masks = &शेष_aux_masks;
	अन्यथा
		aux->masks = masks;

	aux->reg = reg;
	aux->rtbl = rtbl;
	aux->rtbl_cnt = rtbl_cnt;
	aux->lock = lock;
	aux->hw.init = &init;

	init.name = aux_name;
	init.ops = &clk_aux_ops;
	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	clk = clk_रेजिस्टर(शून्य, &aux->hw);
	अगर (IS_ERR_OR_शून्य(clk))
		जाओ मुक्त_aux;

	अगर (gate_name) अणु
		काष्ठा clk *tgate_clk;

		tgate_clk = clk_रेजिस्टर_gate(शून्य, gate_name, aux_name,
				CLK_SET_RATE_PARENT, reg,
				aux->masks->enable_bit, 0, lock);
		अगर (IS_ERR_OR_शून्य(tgate_clk))
			जाओ मुक्त_aux;

		अगर (gate_clk)
			*gate_clk = tgate_clk;
	पूर्ण

	वापस clk;

मुक्त_aux:
	kमुक्त(aux);
	pr_err("clk register failed\n");

	वापस शून्य;
पूर्ण
