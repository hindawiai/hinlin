<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* Copyright (C) 2014 Texas Instruments Ltd
*/

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "dss_features.h"

काष्ठा dss_video_pll अणु
	काष्ठा dss_pll pll;

	काष्ठा device *dev;

	व्योम __iomem *clkctrl_base;
पूर्ण;

#घोषणा REG_MOD(reg, val, start, end) \
	ग_लिखोl_relaxed(FLD_MOD(पढ़ोl_relaxed(reg), val, start, end), reg)

अटल व्योम dss_dpll_enable_scp_clk(काष्ठा dss_video_pll *vpll)
अणु
	REG_MOD(vpll->clkctrl_base, 1, 14, 14); /* CIO_CLK_ICG */
पूर्ण

अटल व्योम dss_dpll_disable_scp_clk(काष्ठा dss_video_pll *vpll)
अणु
	REG_MOD(vpll->clkctrl_base, 0, 14, 14); /* CIO_CLK_ICG */
पूर्ण

अटल व्योम dss_dpll_घातer_enable(काष्ठा dss_video_pll *vpll)
अणु
	REG_MOD(vpll->clkctrl_base, 2, 31, 30); /* PLL_POWER_ON_ALL */

	/*
	 * DRA7x PLL CTRL's PLL_PWR_STATUS seems to always वापस 0,
	 * so we have to use fixed delay here.
	 */
	msleep(1);
पूर्ण

अटल व्योम dss_dpll_घातer_disable(काष्ठा dss_video_pll *vpll)
अणु
	REG_MOD(vpll->clkctrl_base, 0, 31, 30);	/* PLL_POWER_OFF */
पूर्ण

अटल पूर्णांक dss_video_pll_enable(काष्ठा dss_pll *pll)
अणु
	काष्ठा dss_video_pll *vpll = container_of(pll, काष्ठा dss_video_pll, pll);
	पूर्णांक r;

	r = dss_runसमय_get();
	अगर (r)
		वापस r;

	dss_ctrl_pll_enable(pll->id, true);

	dss_dpll_enable_scp_clk(vpll);

	r = dss_pll_रुको_reset_करोne(pll);
	अगर (r)
		जाओ err_reset;

	dss_dpll_घातer_enable(vpll);

	वापस 0;

err_reset:
	dss_dpll_disable_scp_clk(vpll);
	dss_ctrl_pll_enable(pll->id, false);
	dss_runसमय_put();

	वापस r;
पूर्ण

अटल व्योम dss_video_pll_disable(काष्ठा dss_pll *pll)
अणु
	काष्ठा dss_video_pll *vpll = container_of(pll, काष्ठा dss_video_pll, pll);

	dss_dpll_घातer_disable(vpll);

	dss_dpll_disable_scp_clk(vpll);

	dss_ctrl_pll_enable(pll->id, false);

	dss_runसमय_put();
पूर्ण

अटल स्थिर काष्ठा dss_pll_ops dss_pll_ops = अणु
	.enable = dss_video_pll_enable,
	.disable = dss_video_pll_disable,
	.set_config = dss_pll_ग_लिखो_config_type_a,
पूर्ण;

अटल स्थिर काष्ठा dss_pll_hw dss_dra7_video_pll_hw = अणु
	.n_max = (1 << 8) - 1,
	.m_max = (1 << 12) - 1,
	.mX_max = (1 << 5) - 1,
	.fपूर्णांक_min = 500000,
	.fपूर्णांक_max = 2500000,
	.clkdco_max = 1800000000,

	.n_msb = 8,
	.n_lsb = 1,
	.m_msb = 20,
	.m_lsb = 9,

	.mX_msb[0] = 25,
	.mX_lsb[0] = 21,
	.mX_msb[1] = 30,
	.mX_lsb[1] = 26,

	.has_refsel = true,
पूर्ण;

काष्ठा dss_pll *dss_video_pll_init(काष्ठा platक्रमm_device *pdev, पूर्णांक id,
	काष्ठा regulator *regulator)
अणु
	स्थिर अक्षर * स्थिर reg_name[] = अणु "pll1", "pll2" पूर्ण;
	स्थिर अक्षर * स्थिर clkctrl_name[] = अणु "pll1_clkctrl", "pll2_clkctrl" पूर्ण;
	स्थिर अक्षर * स्थिर clkin_name[] = अणु "video1_clk", "video2_clk" पूर्ण;

	काष्ठा dss_video_pll *vpll;
	व्योम __iomem *pll_base, *clkctrl_base;
	काष्ठा clk *clk;
	काष्ठा dss_pll *pll;
	पूर्णांक r;

	/* PLL CONTROL */

	pll_base = devm_platक्रमm_ioremap_resource_byname(pdev, reg_name[id]);
	अगर (IS_ERR(pll_base)) अणु
		dev_err(&pdev->dev, "failed to ioremap pll%d reg_name\n", id);
		वापस ERR_CAST(pll_base);
	पूर्ण

	/* CLOCK CONTROL */

	clkctrl_base = devm_platक्रमm_ioremap_resource_byname(pdev, clkctrl_name[id]);
	अगर (IS_ERR(clkctrl_base)) अणु
		dev_err(&pdev->dev, "failed to ioremap pll%d clkctrl\n", id);
		वापस ERR_CAST(clkctrl_base);
	पूर्ण

	/* CLKIN */

	clk = devm_clk_get(&pdev->dev, clkin_name[id]);
	अगर (IS_ERR(clk)) अणु
		DSSERR("can't get video pll clkin\n");
		वापस ERR_CAST(clk);
	पूर्ण

	vpll = devm_kzalloc(&pdev->dev, माप(*vpll), GFP_KERNEL);
	अगर (!vpll)
		वापस ERR_PTR(-ENOMEM);

	vpll->dev = &pdev->dev;
	vpll->clkctrl_base = clkctrl_base;

	pll = &vpll->pll;

	pll->name = id == 0 ? "video0" : "video1";
	pll->id = id == 0 ? DSS_PLL_VIDEO1 : DSS_PLL_VIDEO2;
	pll->clkin = clk;
	pll->regulator = regulator;
	pll->base = pll_base;
	pll->hw = &dss_dra7_video_pll_hw;
	pll->ops = &dss_pll_ops;

	r = dss_pll_रेजिस्टर(pll);
	अगर (r)
		वापस ERR_PTR(r);

	वापस pll;
पूर्ण

व्योम dss_video_pll_uninit(काष्ठा dss_pll *pll)
अणु
	dss_pll_unरेजिस्टर(pll);
पूर्ण
