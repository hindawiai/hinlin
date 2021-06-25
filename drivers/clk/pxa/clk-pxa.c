<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell PXA family घड़ीs
 *
 * Copyright (C) 2014 Robert Jarzmik
 *
 * Common घड़ी code क्रम PXA घड़ीs ("CKEN" type घड़ीs + DT)
 */
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#समावेश <dt-bindings/घड़ी/pxa-घड़ी.h>
#समावेश "clk-pxa.h"

#घोषणा KHz 1000
#घोषणा MHz (1000 * 1000)

#घोषणा MDREFR_K0DB4	(1 << 29)	/* SDCLK0 Divide by 4 Control/Status */
#घोषणा MDREFR_K2FREE	(1 << 25)	/* SDRAM Free-Running Control */
#घोषणा MDREFR_K1FREE	(1 << 24)	/* SDRAM Free-Running Control */
#घोषणा MDREFR_K0FREE	(1 << 23)	/* SDRAM Free-Running Control */
#घोषणा MDREFR_SLFRSH	(1 << 22)	/* SDRAM Self-Refresh Control/Status */
#घोषणा MDREFR_APD	(1 << 20)	/* SDRAM/SSRAM Auto-Power-Down Enable */
#घोषणा MDREFR_K2DB2	(1 << 19)	/* SDCLK2 Divide by 2 Control/Status */
#घोषणा MDREFR_K2RUN	(1 << 18)	/* SDCLK2 Run Control/Status */
#घोषणा MDREFR_K1DB2	(1 << 17)	/* SDCLK1 Divide by 2 Control/Status */
#घोषणा MDREFR_K1RUN	(1 << 16)	/* SDCLK1 Run Control/Status */
#घोषणा MDREFR_E1PIN	(1 << 15)	/* SDCKE1 Level Control/Status */
#घोषणा MDREFR_K0DB2	(1 << 14)	/* SDCLK0 Divide by 2 Control/Status */
#घोषणा MDREFR_K0RUN	(1 << 13)	/* SDCLK0 Run Control/Status */
#घोषणा MDREFR_E0PIN	(1 << 12)	/* SDCKE0 Level Control/Status */
#घोषणा MDREFR_DB2_MASK	(MDREFR_K2DB2 | MDREFR_K1DB2)
#घोषणा MDREFR_DRI_MASK	0xFFF

अटल DEFINE_SPINLOCK(pxa_clk_lock);

अटल काष्ठा clk *pxa_घड़ीs[CLK_MAX];
अटल काष्ठा clk_onecell_data onecell_data = अणु
	.clks = pxa_घड़ीs,
	.clk_num = CLK_MAX,
पूर्ण;

काष्ठा pxa_clk अणु
	काष्ठा clk_hw hw;
	काष्ठा clk_fixed_factor lp;
	काष्ठा clk_fixed_factor hp;
	काष्ठा clk_gate gate;
	bool (*is_in_low_घातer)(व्योम);
पूर्ण;

#घोषणा to_pxa_clk(_hw) container_of(_hw, काष्ठा pxa_clk, hw)

अटल अचिन्हित दीर्घ cken_recalc_rate(काष्ठा clk_hw *hw,
				      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pxa_clk *pclk = to_pxa_clk(hw);
	काष्ठा clk_fixed_factor *fix;

	अगर (!pclk->is_in_low_घातer || pclk->is_in_low_घातer())
		fix = &pclk->lp;
	अन्यथा
		fix = &pclk->hp;
	__clk_hw_set_clk(&fix->hw, hw);
	वापस clk_fixed_factor_ops.recalc_rate(&fix->hw, parent_rate);
पूर्ण

अटल स्थिर काष्ठा clk_ops cken_rate_ops = अणु
	.recalc_rate = cken_recalc_rate,
पूर्ण;

अटल u8 cken_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा pxa_clk *pclk = to_pxa_clk(hw);

	अगर (!pclk->is_in_low_घातer)
		वापस 0;
	वापस pclk->is_in_low_घातer() ? 0 : 1;
पूर्ण

अटल स्थिर काष्ठा clk_ops cken_mux_ops = अणु
	.get_parent = cken_get_parent,
	.set_parent = dummy_clk_set_parent,
पूर्ण;

व्योम __init clkdev_pxa_रेजिस्टर(पूर्णांक ckid, स्थिर अक्षर *con_id,
				स्थिर अक्षर *dev_id, काष्ठा clk *clk)
अणु
	अगर (!IS_ERR(clk) && (ckid != CLK_NONE))
		pxa_घड़ीs[ckid] = clk;
	अगर (!IS_ERR(clk))
		clk_रेजिस्टर_clkdev(clk, con_id, dev_id);
पूर्ण

पूर्णांक __init clk_pxa_cken_init(स्थिर काष्ठा desc_clk_cken *clks, पूर्णांक nb_clks)
अणु
	पूर्णांक i;
	काष्ठा pxa_clk *pxa_clk;
	काष्ठा clk *clk;

	क्रम (i = 0; i < nb_clks; i++) अणु
		pxa_clk = kzalloc(माप(*pxa_clk), GFP_KERNEL);
		pxa_clk->is_in_low_घातer = clks[i].is_in_low_घातer;
		pxa_clk->lp = clks[i].lp;
		pxa_clk->hp = clks[i].hp;
		pxa_clk->gate = clks[i].gate;
		pxa_clk->gate.lock = &pxa_clk_lock;
		clk = clk_रेजिस्टर_composite(शून्य, clks[i].name,
					     clks[i].parent_names, 2,
					     &pxa_clk->hw, &cken_mux_ops,
					     &pxa_clk->hw, &cken_rate_ops,
					     &pxa_clk->gate.hw, &clk_gate_ops,
					     clks[i].flags);
		clkdev_pxa_रेजिस्टर(clks[i].ckid, clks[i].con_id,
				    clks[i].dev_id, clk);
	पूर्ण
	वापस 0;
पूर्ण

व्योम __init clk_pxa_dt_common_init(काष्ठा device_node *np)
अणु
	of_clk_add_provider(np, of_clk_src_onecell_get, &onecell_data);
पूर्ण

व्योम pxa2xx_core_turbo_चयन(bool on)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक unused, clkcfg;

	local_irq_save(flags);

	यंत्र("mrc p14, 0, %0, c6, c0, 0" : "=r" (clkcfg));
	clkcfg &= ~CLKCFG_TURBO & ~CLKCFG_HALFTURBO;
	अगर (on)
		clkcfg |= CLKCFG_TURBO;
	clkcfg |= CLKCFG_FCS;

	यंत्र अस्थिर(
	"	b	2f\n"
	"	.align	5\n"
	"1:	mcr	p14, 0, %1, c6, c0, 0\n"
	"	b	3f\n"
	"2:	b	1b\n"
	"3:	nop\n"
		: "=&r" (unused) : "r" (clkcfg));

	local_irq_restore(flags);
पूर्ण

व्योम pxa2xx_cpll_change(काष्ठा pxa2xx_freq *freq,
			u32 (*mdrefr_dri)(अचिन्हित पूर्णांक), व्योम __iomem *mdrefr,
			व्योम __iomem *cccr)
अणु
	अचिन्हित पूर्णांक clkcfg = freq->clkcfg;
	अचिन्हित पूर्णांक unused, preset_mdrefr, postset_mdrefr;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/* Calculate the next MDREFR.  If we're slowing करोwn the SDRAM घड़ी
	 * we need to preset the smaller DRI beक्रमe the change.	 If we're
	 * speeding up we need to set the larger DRI value after the change.
	 */
	preset_mdrefr = postset_mdrefr = पढ़ोl(mdrefr);
	अगर ((preset_mdrefr & MDREFR_DRI_MASK) > mdrefr_dri(freq->membus_khz)) अणु
		preset_mdrefr = (preset_mdrefr & ~MDREFR_DRI_MASK);
		preset_mdrefr |= mdrefr_dri(freq->membus_khz);
	पूर्ण
	postset_mdrefr =
		(postset_mdrefr & ~MDREFR_DRI_MASK) |
		mdrefr_dri(freq->membus_khz);

	/* If we're भागiding the memory घड़ी by two क्रम the SDRAM घड़ी, this
	 * must be set prior to the change.  Clearing the भागide must be करोne
	 * after the change.
	 */
	अगर (freq->भाग2) अणु
		preset_mdrefr  |= MDREFR_DB2_MASK;
		postset_mdrefr |= MDREFR_DB2_MASK;
	पूर्ण अन्यथा अणु
		postset_mdrefr &= ~MDREFR_DB2_MASK;
	पूर्ण

	/* Set new the CCCR and prepare CLKCFG */
	ग_लिखोl(freq->cccr, cccr);

	यंत्र अस्थिर(
	"	ldr	r4, [%1]\n"
	"	b	2f\n"
	"	.align	5\n"
	"1:	str	%3, [%1]		/* preset the MDREFR */\n"
	"	mcr	p14, 0, %2, c6, c0, 0	/* set CLKCFG[FCS] */\n"
	"	str	%4, [%1]		/* postset the MDREFR */\n"
	"	b	3f\n"
	"2:	b	1b\n"
	"3:	nop\n"
	     : "=&r" (unused)
	     : "r" (mdrefr), "r" (clkcfg), "r" (preset_mdrefr),
	       "r" (postset_mdrefr)
	     : "r4", "r5");

	local_irq_restore(flags);
पूर्ण

पूर्णांक pxa2xx_determine_rate(काष्ठा clk_rate_request *req,
			  काष्ठा pxa2xx_freq *freqs, पूर्णांक nb_freqs)
अणु
	पूर्णांक i, बंदst_below = -1, बंदst_above = -1;
	अचिन्हित दीर्घ rate;

	क्रम (i = 0; i < nb_freqs; i++) अणु
		rate = freqs[i].cpll;
		अगर (rate == req->rate)
			अवरोध;
		अगर (rate < req->min_rate)
			जारी;
		अगर (rate > req->max_rate)
			जारी;
		अगर (rate <= req->rate)
			बंदst_below = i;
		अगर ((rate >= req->rate) && (बंदst_above == -1))
			बंदst_above = i;
	पूर्ण

	req->best_parent_hw = शून्य;

	अगर (i < nb_freqs) अणु
		rate = req->rate;
	पूर्ण अन्यथा अगर (बंदst_below >= 0) अणु
		rate = freqs[बंदst_below].cpll;
	पूर्ण अन्यथा अगर (बंदst_above >= 0) अणु
		rate = freqs[बंदst_above].cpll;
	पूर्ण अन्यथा अणु
		pr_debug("%s(rate=%lu) no match\n", __func__, req->rate);
		वापस -EINVAL;
	पूर्ण

	pr_debug("%s(rate=%lu) rate=%lu\n", __func__, req->rate, rate);
	req->rate = rate;

	वापस 0;
पूर्ण
