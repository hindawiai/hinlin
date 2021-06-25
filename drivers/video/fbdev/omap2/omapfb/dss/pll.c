<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Texas Instruments Incorporated
 */

#घोषणा DSS_SUBSYS_NAME "PLL"

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sched.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"

#घोषणा PLL_CONTROL			0x0000
#घोषणा PLL_STATUS			0x0004
#घोषणा PLL_GO				0x0008
#घोषणा PLL_CONFIGURATION1		0x000C
#घोषणा PLL_CONFIGURATION2		0x0010
#घोषणा PLL_CONFIGURATION3		0x0014
#घोषणा PLL_SSC_CONFIGURATION1		0x0018
#घोषणा PLL_SSC_CONFIGURATION2		0x001C
#घोषणा PLL_CONFIGURATION4		0x0020

अटल काष्ठा dss_pll *dss_plls[4];

पूर्णांक dss_pll_रेजिस्टर(काष्ठा dss_pll *pll)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dss_plls); ++i) अणु
		अगर (!dss_plls[i]) अणु
			dss_plls[i] = pll;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EBUSY;
पूर्ण

व्योम dss_pll_unरेजिस्टर(काष्ठा dss_pll *pll)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dss_plls); ++i) अणु
		अगर (dss_plls[i] == pll) अणु
			dss_plls[i] = शून्य;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा dss_pll *dss_pll_find(स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dss_plls); ++i) अणु
		अगर (dss_plls[i] && म_भेद(dss_plls[i]->name, name) == 0)
			वापस dss_plls[i];
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक dss_pll_enable(काष्ठा dss_pll *pll)
अणु
	पूर्णांक r;

	r = clk_prepare_enable(pll->clkin);
	अगर (r)
		वापस r;

	अगर (pll->regulator) अणु
		r = regulator_enable(pll->regulator);
		अगर (r)
			जाओ err_reg;
	पूर्ण

	r = pll->ops->enable(pll);
	अगर (r)
		जाओ err_enable;

	वापस 0;

err_enable:
	अगर (pll->regulator)
		regulator_disable(pll->regulator);
err_reg:
	clk_disable_unprepare(pll->clkin);
	वापस r;
पूर्ण

व्योम dss_pll_disable(काष्ठा dss_pll *pll)
अणु
	pll->ops->disable(pll);

	अगर (pll->regulator)
		regulator_disable(pll->regulator);

	clk_disable_unprepare(pll->clkin);

	स_रखो(&pll->cinfo, 0, माप(pll->cinfo));
पूर्ण

पूर्णांक dss_pll_set_config(काष्ठा dss_pll *pll, स्थिर काष्ठा dss_pll_घड़ी_info *cinfo)
अणु
	पूर्णांक r;

	r = pll->ops->set_config(pll, cinfo);
	अगर (r)
		वापस r;

	pll->cinfo = *cinfo;

	वापस 0;
पूर्ण

bool dss_pll_hsभाग_calc(स्थिर काष्ठा dss_pll *pll, अचिन्हित दीर्घ clkdco,
		अचिन्हित दीर्घ out_min, अचिन्हित दीर्घ out_max,
		dss_hsभाग_calc_func func, व्योम *data)
अणु
	स्थिर काष्ठा dss_pll_hw *hw = pll->hw;
	पूर्णांक m, m_start, m_stop;
	अचिन्हित दीर्घ out;

	out_min = out_min ? out_min : 1;
	out_max = out_max ? out_max : अच_दीर्घ_उच्च;

	m_start = max(DIV_ROUND_UP(clkdco, out_max), 1ul);

	m_stop = min((अचिन्हित)(clkdco / out_min), hw->mX_max);

	क्रम (m = m_start; m <= m_stop; ++m) अणु
		out = clkdco / m;

		अगर (func(m, out, data))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool dss_pll_calc(स्थिर काष्ठा dss_pll *pll, अचिन्हित दीर्घ clkin,
		अचिन्हित दीर्घ pll_min, अचिन्हित दीर्घ pll_max,
		dss_pll_calc_func func, व्योम *data)
अणु
	स्थिर काष्ठा dss_pll_hw *hw = pll->hw;
	पूर्णांक n, n_start, n_stop;
	पूर्णांक m, m_start, m_stop;
	अचिन्हित दीर्घ fपूर्णांक, clkdco;
	अचिन्हित दीर्घ pll_hw_max;
	अचिन्हित दीर्घ fपूर्णांक_hw_min, fपूर्णांक_hw_max;

	pll_hw_max = hw->clkdco_max;

	fपूर्णांक_hw_min = hw->fपूर्णांक_min;
	fपूर्णांक_hw_max = hw->fपूर्णांक_max;

	n_start = max(DIV_ROUND_UP(clkin, fपूर्णांक_hw_max), 1ul);
	n_stop = min((अचिन्हित)(clkin / fपूर्णांक_hw_min), hw->n_max);

	pll_max = pll_max ? pll_max : अच_दीर्घ_उच्च;

	क्रम (n = n_start; n <= n_stop; ++n) अणु
		fपूर्णांक = clkin / n;

		m_start = max(DIV_ROUND_UP(DIV_ROUND_UP(pll_min, fपूर्णांक), 2),
				1ul);
		m_stop = min3((अचिन्हित)(pll_max / fपूर्णांक / 2),
				(अचिन्हित)(pll_hw_max / fपूर्णांक / 2),
				hw->m_max);

		क्रम (m = m_start; m <= m_stop; ++m) अणु
			clkdco = 2 * m * fपूर्णांक;

			अगर (func(n, m, fपूर्णांक, clkdco, data))
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक रुको_क्रम_bit_change(व्योम __iomem *reg, पूर्णांक bitnum, पूर्णांक value)
अणु
	अचिन्हित दीर्घ समयout;
	kसमय_प्रकार रुको;
	पूर्णांक t;

	/* first busyloop to see अगर the bit changes right away */
	t = 100;
	जबतक (t-- > 0) अणु
		अगर (FLD_GET(पढ़ोl_relaxed(reg), bitnum, bitnum) == value)
			वापस value;
	पूर्ण

	/* then loop क्रम 500ms, sleeping क्रम 1ms in between */
	समयout = jअगरfies + msecs_to_jअगरfies(500);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (FLD_GET(पढ़ोl_relaxed(reg), bitnum, bitnum) == value)
			वापस value;

		रुको = ns_to_kसमय(1000 * 1000);
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_hrसमयout(&रुको, HRTIMER_MODE_REL);
	पूर्ण

	वापस !value;
पूर्ण

पूर्णांक dss_pll_रुको_reset_करोne(काष्ठा dss_pll *pll)
अणु
	व्योम __iomem *base = pll->base;

	अगर (रुको_क्रम_bit_change(base + PLL_STATUS, 0, 1) != 1)
		वापस -ETIMEDOUT;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक dss_रुको_hsभाग_ack(काष्ठा dss_pll *pll, u32 hsभाग_ack_mask)
अणु
	पूर्णांक t = 100;

	जबतक (t-- > 0) अणु
		u32 v = पढ़ोl_relaxed(pll->base + PLL_STATUS);
		v &= hsभाग_ack_mask;
		अगर (v == hsभाग_ack_mask)
			वापस 0;
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

पूर्णांक dss_pll_ग_लिखो_config_type_a(काष्ठा dss_pll *pll,
		स्थिर काष्ठा dss_pll_घड़ी_info *cinfo)
अणु
	स्थिर काष्ठा dss_pll_hw *hw = pll->hw;
	व्योम __iomem *base = pll->base;
	पूर्णांक r = 0;
	u32 l;

	l = 0;
	अगर (hw->has_stopmode)
		l = FLD_MOD(l, 1, 0, 0);		/* PLL_STOPMODE */
	l = FLD_MOD(l, cinfo->n - 1, hw->n_msb, hw->n_lsb);	/* PLL_REGN */
	l = FLD_MOD(l, cinfo->m, hw->m_msb, hw->m_lsb);		/* PLL_REGM */
	/* M4 */
	l = FLD_MOD(l, cinfo->mX[0] ? cinfo->mX[0] - 1 : 0,
			hw->mX_msb[0], hw->mX_lsb[0]);
	/* M5 */
	l = FLD_MOD(l, cinfo->mX[1] ? cinfo->mX[1] - 1 : 0,
			hw->mX_msb[1], hw->mX_lsb[1]);
	ग_लिखोl_relaxed(l, base + PLL_CONFIGURATION1);

	l = 0;
	/* M6 */
	l = FLD_MOD(l, cinfo->mX[2] ? cinfo->mX[2] - 1 : 0,
			hw->mX_msb[2], hw->mX_lsb[2]);
	/* M7 */
	l = FLD_MOD(l, cinfo->mX[3] ? cinfo->mX[3] - 1 : 0,
			hw->mX_msb[3], hw->mX_lsb[3]);
	ग_लिखोl_relaxed(l, base + PLL_CONFIGURATION3);

	l = पढ़ोl_relaxed(base + PLL_CONFIGURATION2);
	अगर (hw->has_freqsel) अणु
		u32 f = cinfo->fपूर्णांक < 1000000 ? 0x3 :
			cinfo->fपूर्णांक < 1250000 ? 0x4 :
			cinfo->fपूर्णांक < 1500000 ? 0x5 :
			cinfo->fपूर्णांक < 1750000 ? 0x6 :
			0x7;

		l = FLD_MOD(l, f, 4, 1);	/* PLL_FREQSEL */
	पूर्ण अन्यथा अगर (hw->has_selfreqdco) अणु
		u32 f = cinfo->clkdco < hw->clkdco_low ? 0x2 : 0x4;

		l = FLD_MOD(l, f, 3, 1);	/* PLL_SELFREQDCO */
	पूर्ण
	l = FLD_MOD(l, 1, 13, 13);		/* PLL_REFEN */
	l = FLD_MOD(l, 0, 14, 14);		/* PHY_CLKINEN */
	l = FLD_MOD(l, 0, 16, 16);		/* M4_CLOCK_EN */
	l = FLD_MOD(l, 0, 18, 18);		/* M5_CLOCK_EN */
	l = FLD_MOD(l, 1, 20, 20);		/* HSDIVBYPASS */
	अगर (hw->has_refsel)
		l = FLD_MOD(l, 3, 22, 21);	/* REFSEL = sysclk */
	l = FLD_MOD(l, 0, 23, 23);		/* M6_CLOCK_EN */
	l = FLD_MOD(l, 0, 25, 25);		/* M7_CLOCK_EN */
	ग_लिखोl_relaxed(l, base + PLL_CONFIGURATION2);

	ग_लिखोl_relaxed(1, base + PLL_GO);	/* PLL_GO */

	अगर (रुको_क्रम_bit_change(base + PLL_GO, 0, 0) != 0) अणु
		DSSERR("DSS DPLL GO bit not going down.\n");
		r = -EIO;
		जाओ err;
	पूर्ण

	अगर (रुको_क्रम_bit_change(base + PLL_STATUS, 1, 1) != 1) अणु
		DSSERR("cannot lock DSS DPLL\n");
		r = -EIO;
		जाओ err;
	पूर्ण

	l = पढ़ोl_relaxed(base + PLL_CONFIGURATION2);
	l = FLD_MOD(l, 1, 14, 14);			/* PHY_CLKINEN */
	l = FLD_MOD(l, cinfo->mX[0] ? 1 : 0, 16, 16);	/* M4_CLOCK_EN */
	l = FLD_MOD(l, cinfo->mX[1] ? 1 : 0, 18, 18);	/* M5_CLOCK_EN */
	l = FLD_MOD(l, 0, 20, 20);			/* HSDIVBYPASS */
	l = FLD_MOD(l, cinfo->mX[2] ? 1 : 0, 23, 23);	/* M6_CLOCK_EN */
	l = FLD_MOD(l, cinfo->mX[3] ? 1 : 0, 25, 25);	/* M7_CLOCK_EN */
	ग_लिखोl_relaxed(l, base + PLL_CONFIGURATION2);

	r = dss_रुको_hsभाग_ack(pll,
		(cinfo->mX[0] ? BIT(7) : 0) |
		(cinfo->mX[1] ? BIT(8) : 0) |
		(cinfo->mX[2] ? BIT(10) : 0) |
		(cinfo->mX[3] ? BIT(11) : 0));
	अगर (r) अणु
		DSSERR("failed to enable HSDIV clocks\n");
		जाओ err;
	पूर्ण

err:
	वापस r;
पूर्ण

पूर्णांक dss_pll_ग_लिखो_config_type_b(काष्ठा dss_pll *pll,
		स्थिर काष्ठा dss_pll_घड़ी_info *cinfo)
अणु
	स्थिर काष्ठा dss_pll_hw *hw = pll->hw;
	व्योम __iomem *base = pll->base;
	u32 l;

	l = 0;
	l = FLD_MOD(l, cinfo->m, 20, 9);	/* PLL_REGM */
	l = FLD_MOD(l, cinfo->n - 1, 8, 1);	/* PLL_REGN */
	ग_लिखोl_relaxed(l, base + PLL_CONFIGURATION1);

	l = पढ़ोl_relaxed(base + PLL_CONFIGURATION2);
	l = FLD_MOD(l, 0x0, 12, 12);	/* PLL_HIGHFREQ भागide by 2 */
	l = FLD_MOD(l, 0x1, 13, 13);	/* PLL_REFEN */
	l = FLD_MOD(l, 0x0, 14, 14);	/* PHY_CLKINEN */
	अगर (hw->has_refsel)
		l = FLD_MOD(l, 0x3, 22, 21);	/* REFSEL = SYSCLK */

	/* PLL_SELFREQDCO */
	अगर (cinfo->clkdco > hw->clkdco_low)
		l = FLD_MOD(l, 0x4, 3, 1);
	अन्यथा
		l = FLD_MOD(l, 0x2, 3, 1);
	ग_लिखोl_relaxed(l, base + PLL_CONFIGURATION2);

	l = पढ़ोl_relaxed(base + PLL_CONFIGURATION3);
	l = FLD_MOD(l, cinfo->sd, 17, 10);	/* PLL_REGSD */
	ग_लिखोl_relaxed(l, base + PLL_CONFIGURATION3);

	l = पढ़ोl_relaxed(base + PLL_CONFIGURATION4);
	l = FLD_MOD(l, cinfo->mX[0], 24, 18);	/* PLL_REGM2 */
	l = FLD_MOD(l, cinfo->mf, 17, 0);	/* PLL_REGM_F */
	ग_लिखोl_relaxed(l, base + PLL_CONFIGURATION4);

	ग_लिखोl_relaxed(1, base + PLL_GO);	/* PLL_GO */

	अगर (रुको_क्रम_bit_change(base + PLL_GO, 0, 0) != 0) अणु
		DSSERR("DSS DPLL GO bit not going down.\n");
		वापस -EIO;
	पूर्ण

	अगर (रुको_क्रम_bit_change(base + PLL_STATUS, 1, 1) != 1) अणु
		DSSERR("cannot lock DSS DPLL\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण
