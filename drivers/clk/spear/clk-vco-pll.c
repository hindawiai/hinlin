<शैली गुरु>
/*
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * VCO-PLL घड़ी implementation
 */

#घोषणा pr_fmt(fmt) "clk-vco-pll: " fmt

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश "clk.h"

/*
 * DOC: VCO-PLL घड़ी
 *
 * VCO and PLL rate are derived from following equations:
 *
 * In normal mode
 * vco = (2 * M[15:8] * Fin)/N
 *
 * In Dithered mode
 * vco = (2 * M[15:0] * Fin)/(256 * N)
 *
 * pll_rate = pll/2^p
 *
 * vco and pll are very बंदly bound to each other, "vco needs to program:
 * mode, m & n" and "pll needs to program p", both share common enable/disable
 * logic.
 *
 * clk_रेजिस्टर_vco_pll() रेजिस्टरs instances of both vco & pll.
 * CLK_SET_RATE_PARENT flag is क्रमced क्रम pll, as it will always pass its
 * set_rate to vco. A single rate table exists क्रम both the घड़ीs, which
 * configures m, n and p.
 */

/* PLL_CTR रेजिस्टर masks */
#घोषणा PLL_MODE_NORMAL		0
#घोषणा PLL_MODE_FRACTION	1
#घोषणा PLL_MODE_DITH_DSM	2
#घोषणा PLL_MODE_DITH_SSM	3
#घोषणा PLL_MODE_MASK		3
#घोषणा PLL_MODE_SHIFT		3
#घोषणा PLL_ENABLE		2

#घोषणा PLL_LOCK_SHIFT		0
#घोषणा PLL_LOCK_MASK		1

/* PLL FRQ रेजिस्टर masks */
#घोषणा PLL_NORM_FDBK_M_MASK	0xFF
#घोषणा PLL_NORM_FDBK_M_SHIFT	24
#घोषणा PLL_DITH_FDBK_M_MASK	0xFFFF
#घोषणा PLL_DITH_FDBK_M_SHIFT	16
#घोषणा PLL_DIV_P_MASK		0x7
#घोषणा PLL_DIV_P_SHIFT		8
#घोषणा PLL_DIV_N_MASK		0xFF
#घोषणा PLL_DIV_N_SHIFT		0

#घोषणा to_clk_vco(_hw) container_of(_hw, काष्ठा clk_vco, hw)
#घोषणा to_clk_pll(_hw) container_of(_hw, काष्ठा clk_pll, hw)

/* Calculates pll clk rate क्रम specअगरic value of mode, m, n and p */
अटल अचिन्हित दीर्घ pll_calc_rate(काष्ठा pll_rate_tbl *rtbl,
		अचिन्हित दीर्घ prate, पूर्णांक index, अचिन्हित दीर्घ *pll_rate)
अणु
	अचिन्हित दीर्घ rate = prate;
	अचिन्हित पूर्णांक mode;

	mode = rtbl[index].mode ? 256 : 1;
	rate = (((2 * rate / 10000) * rtbl[index].m) / (mode * rtbl[index].n));

	अगर (pll_rate)
		*pll_rate = (rate / (1 << rtbl[index].p)) * 10000;

	वापस rate * 10000;
पूर्ण

अटल दीर्घ clk_pll_round_rate_index(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
				अचिन्हित दीर्घ *prate, पूर्णांक *index)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	अचिन्हित दीर्घ prev_rate, vco_prev_rate, rate = 0;
	अचिन्हित दीर्घ vco_parent_rate =
		clk_hw_get_rate(clk_hw_get_parent(clk_hw_get_parent(hw)));

	अगर (!prate) अणु
		pr_err("%s: prate is must for pll clk\n", __func__);
		वापस -EINVAL;
	पूर्ण

	क्रम (*index = 0; *index < pll->vco->rtbl_cnt; (*index)++) अणु
		prev_rate = rate;
		vco_prev_rate = *prate;
		*prate = pll_calc_rate(pll->vco->rtbl, vco_parent_rate, *index,
				&rate);
		अगर (drate < rate) अणु
			/* previous घड़ी was best */
			अगर (*index) अणु
				rate = prev_rate;
				*prate = vco_prev_rate;
				(*index)--;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rate;
पूर्ण

अटल दीर्घ clk_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
				अचिन्हित दीर्घ *prate)
अणु
	पूर्णांक unused;

	वापस clk_pll_round_rate_index(hw, drate, prate, &unused);
पूर्ण

अटल अचिन्हित दीर्घ clk_pll_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ
		parent_rate)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक p;

	अगर (pll->vco->lock)
		spin_lock_irqsave(pll->vco->lock, flags);

	p = पढ़ोl_relaxed(pll->vco->cfg_reg);

	अगर (pll->vco->lock)
		spin_unlock_irqrestore(pll->vco->lock, flags);

	p = (p >> PLL_DIV_P_SHIFT) & PLL_DIV_P_MASK;

	वापस parent_rate / (1 << p);
पूर्ण

अटल पूर्णांक clk_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
				अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	काष्ठा pll_rate_tbl *rtbl = pll->vco->rtbl;
	अचिन्हित दीर्घ flags = 0, val;
	पूर्णांक i = 0;

	clk_pll_round_rate_index(hw, drate, शून्य, &i);

	अगर (pll->vco->lock)
		spin_lock_irqsave(pll->vco->lock, flags);

	val = पढ़ोl_relaxed(pll->vco->cfg_reg);
	val &= ~(PLL_DIV_P_MASK << PLL_DIV_P_SHIFT);
	val |= (rtbl[i].p & PLL_DIV_P_MASK) << PLL_DIV_P_SHIFT;
	ग_लिखोl_relaxed(val, pll->vco->cfg_reg);

	अगर (pll->vco->lock)
		spin_unlock_irqrestore(pll->vco->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pll_ops = अणु
	.recalc_rate = clk_pll_recalc_rate,
	.round_rate = clk_pll_round_rate,
	.set_rate = clk_pll_set_rate,
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ vco_calc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ prate, पूर्णांक index)
अणु
	काष्ठा clk_vco *vco = to_clk_vco(hw);

	वापस pll_calc_rate(vco->rtbl, prate, index, शून्य);
पूर्ण

अटल दीर्घ clk_vco_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
		अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_vco *vco = to_clk_vco(hw);
	पूर्णांक unused;

	वापस clk_round_rate_index(hw, drate, *prate, vco_calc_rate,
			vco->rtbl_cnt, &unused);
पूर्ण

अटल अचिन्हित दीर्घ clk_vco_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_vco *vco = to_clk_vco(hw);
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक num = 2, den = 0, val, mode = 0;

	अगर (vco->lock)
		spin_lock_irqsave(vco->lock, flags);

	mode = (पढ़ोl_relaxed(vco->mode_reg) >> PLL_MODE_SHIFT) & PLL_MODE_MASK;

	val = पढ़ोl_relaxed(vco->cfg_reg);

	अगर (vco->lock)
		spin_unlock_irqrestore(vco->lock, flags);

	den = (val >> PLL_DIV_N_SHIFT) & PLL_DIV_N_MASK;

	/* calculate numerator & denominator */
	अगर (!mode) अणु
		/* Normal mode */
		num *= (val >> PLL_NORM_FDBK_M_SHIFT) & PLL_NORM_FDBK_M_MASK;
	पूर्ण अन्यथा अणु
		/* Dithered mode */
		num *= (val >> PLL_DITH_FDBK_M_SHIFT) & PLL_DITH_FDBK_M_MASK;
		den *= 256;
	पूर्ण

	अगर (!den) अणु
		WARN(1, "%s: denominator can't be zero\n", __func__);
		वापस 0;
	पूर्ण

	वापस (((parent_rate / 10000) * num) / den) * 10000;
पूर्ण

/* Configures new घड़ी rate of vco */
अटल पूर्णांक clk_vco_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
				अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_vco *vco = to_clk_vco(hw);
	काष्ठा pll_rate_tbl *rtbl = vco->rtbl;
	अचिन्हित दीर्घ flags = 0, val;
	पूर्णांक i;

	clk_round_rate_index(hw, drate, prate, vco_calc_rate, vco->rtbl_cnt,
			&i);

	अगर (vco->lock)
		spin_lock_irqsave(vco->lock, flags);

	val = पढ़ोl_relaxed(vco->mode_reg);
	val &= ~(PLL_MODE_MASK << PLL_MODE_SHIFT);
	val |= (rtbl[i].mode & PLL_MODE_MASK) << PLL_MODE_SHIFT;
	ग_लिखोl_relaxed(val, vco->mode_reg);

	val = पढ़ोl_relaxed(vco->cfg_reg);
	val &= ~(PLL_DIV_N_MASK << PLL_DIV_N_SHIFT);
	val |= (rtbl[i].n & PLL_DIV_N_MASK) << PLL_DIV_N_SHIFT;

	val &= ~(PLL_DITH_FDBK_M_MASK << PLL_DITH_FDBK_M_SHIFT);
	अगर (rtbl[i].mode)
		val |= (rtbl[i].m & PLL_DITH_FDBK_M_MASK) <<
			PLL_DITH_FDBK_M_SHIFT;
	अन्यथा
		val |= (rtbl[i].m & PLL_NORM_FDBK_M_MASK) <<
			PLL_NORM_FDBK_M_SHIFT;

	ग_लिखोl_relaxed(val, vco->cfg_reg);

	अगर (vco->lock)
		spin_unlock_irqrestore(vco->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_vco_ops = अणु
	.recalc_rate = clk_vco_recalc_rate,
	.round_rate = clk_vco_round_rate,
	.set_rate = clk_vco_set_rate,
पूर्ण;

काष्ठा clk *clk_रेजिस्टर_vco_pll(स्थिर अक्षर *vco_name, स्थिर अक्षर *pll_name,
		स्थिर अक्षर *vco_gate_name, स्थिर अक्षर *parent_name,
		अचिन्हित दीर्घ flags, व्योम __iomem *mode_reg, व्योम __iomem
		*cfg_reg, काष्ठा pll_rate_tbl *rtbl, u8 rtbl_cnt,
		spinlock_t *lock, काष्ठा clk **pll_clk,
		काष्ठा clk **vco_gate_clk)
अणु
	काष्ठा clk_vco *vco;
	काष्ठा clk_pll *pll;
	काष्ठा clk *vco_clk, *tpll_clk, *tvco_gate_clk;
	काष्ठा clk_init_data vco_init, pll_init;
	स्थिर अक्षर **vco_parent_name;

	अगर (!vco_name || !pll_name || !parent_name || !mode_reg || !cfg_reg ||
			!rtbl || !rtbl_cnt) अणु
		pr_err("Invalid arguments passed");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	vco = kzalloc(माप(*vco), GFP_KERNEL);
	अगर (!vco)
		वापस ERR_PTR(-ENOMEM);

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		जाओ मुक्त_vco;

	/* काष्ठा clk_vco assignments */
	vco->mode_reg = mode_reg;
	vco->cfg_reg = cfg_reg;
	vco->rtbl = rtbl;
	vco->rtbl_cnt = rtbl_cnt;
	vco->lock = lock;
	vco->hw.init = &vco_init;

	pll->vco = vco;
	pll->hw.init = &pll_init;

	अगर (vco_gate_name) अणु
		tvco_gate_clk = clk_रेजिस्टर_gate(शून्य, vco_gate_name,
				parent_name, 0, mode_reg, PLL_ENABLE, 0, lock);
		अगर (IS_ERR_OR_शून्य(tvco_gate_clk))
			जाओ मुक्त_pll;

		अगर (vco_gate_clk)
			*vco_gate_clk = tvco_gate_clk;
		vco_parent_name = &vco_gate_name;
	पूर्ण अन्यथा अणु
		vco_parent_name = &parent_name;
	पूर्ण

	vco_init.name = vco_name;
	vco_init.ops = &clk_vco_ops;
	vco_init.flags = flags;
	vco_init.parent_names = vco_parent_name;
	vco_init.num_parents = 1;

	pll_init.name = pll_name;
	pll_init.ops = &clk_pll_ops;
	pll_init.flags = CLK_SET_RATE_PARENT;
	pll_init.parent_names = &vco_name;
	pll_init.num_parents = 1;

	vco_clk = clk_रेजिस्टर(शून्य, &vco->hw);
	अगर (IS_ERR_OR_शून्य(vco_clk))
		जाओ मुक्त_pll;

	tpll_clk = clk_रेजिस्टर(शून्य, &pll->hw);
	अगर (IS_ERR_OR_शून्य(tpll_clk))
		जाओ मुक्त_pll;

	अगर (pll_clk)
		*pll_clk = tpll_clk;

	वापस vco_clk;

मुक्त_pll:
	kमुक्त(pll);
मुक्त_vco:
	kमुक्त(vco);

	pr_err("Failed to register vco pll clock\n");

	वापस ERR_PTR(-ENOMEM);
पूर्ण
