<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HDMI PLL
 *
 * Copyright (C) 2013 Texas Instruments Incorporated
 */

#घोषणा DSS_SUBSYS_NAME "HDMIPLL"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/seq_file.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "hdmi.h"

व्योम hdmi_pll_dump(काष्ठा hdmi_pll_data *pll, काष्ठा seq_file *s)
अणु
#घोषणा DUMPPLL(r) seq_म_लिखो(s, "%-35s %08x\n", #r,\
		hdmi_पढ़ो_reg(pll->base, r))

	DUMPPLL(PLLCTRL_PLL_CONTROL);
	DUMPPLL(PLLCTRL_PLL_STATUS);
	DUMPPLL(PLLCTRL_PLL_GO);
	DUMPPLL(PLLCTRL_CFG1);
	DUMPPLL(PLLCTRL_CFG2);
	DUMPPLL(PLLCTRL_CFG3);
	DUMPPLL(PLLCTRL_SSC_CFG1);
	DUMPPLL(PLLCTRL_SSC_CFG2);
	DUMPPLL(PLLCTRL_CFG4);
पूर्ण

व्योम hdmi_pll_compute(काष्ठा hdmi_pll_data *pll,
	अचिन्हित दीर्घ target_पंचांगds, काष्ठा dss_pll_घड़ी_info *pi)
अणु
	अचिन्हित दीर्घ fपूर्णांक, clkdco, clkout;
	अचिन्हित दीर्घ target_bitclk, target_clkdco;
	अचिन्हित दीर्घ min_dco;
	अचिन्हित n, m, mf, m2, sd;
	अचिन्हित दीर्घ clkin;
	स्थिर काष्ठा dss_pll_hw *hw = pll->pll.hw;

	clkin = clk_get_rate(pll->pll.clkin);

	DSSDBG("clkin %lu, target tmds %lu\n", clkin, target_पंचांगds);

	target_bitclk = target_पंचांगds * 10;

	/* Fपूर्णांक */
	n = DIV_ROUND_UP(clkin, hw->fपूर्णांक_max);
	fपूर्णांक = clkin / n;

	/* adjust m2 so that the clkdco will be high enough */
	min_dco = roundup(hw->clkdco_min, fपूर्णांक);
	m2 = DIV_ROUND_UP(min_dco, target_bitclk);
	अगर (m2 == 0)
		m2 = 1;

	target_clkdco = target_bitclk * m2;
	m = target_clkdco / fपूर्णांक;

	clkdco = fपूर्णांक * m;

	/* adjust clkdco with fractional mf */
	अगर (WARN_ON(target_clkdco - clkdco > fपूर्णांक))
		mf = 0;
	अन्यथा
		mf = (u32)भाग_u64(262144ull * (target_clkdco - clkdco), fपूर्णांक);

	अगर (mf > 0)
		clkdco += (u32)भाग_u64((u64)mf * fपूर्णांक, 262144);

	clkout = clkdco / m2;

	/* sigma-delta */
	sd = DIV_ROUND_UP(fपूर्णांक * m, 250000000);

	DSSDBG("N = %u, M = %u, M.f = %u, M2 = %u, SD = %u\n",
		n, m, mf, m2, sd);
	DSSDBG("Fint %lu, clkdco %lu, clkout %lu\n", fपूर्णांक, clkdco, clkout);

	pi->n = n;
	pi->m = m;
	pi->mf = mf;
	pi->mX[0] = m2;
	pi->sd = sd;

	pi->fपूर्णांक = fपूर्णांक;
	pi->clkdco = clkdco;
	pi->clkout[0] = clkout;
पूर्ण

अटल पूर्णांक hdmi_pll_enable(काष्ठा dss_pll *dsspll)
अणु
	काष्ठा hdmi_pll_data *pll = container_of(dsspll, काष्ठा hdmi_pll_data, pll);
	काष्ठा hdmi_wp_data *wp = pll->wp;

	dss_ctrl_pll_enable(DSS_PLL_HDMI, true);

	वापस hdmi_wp_set_pll_pwr(wp, HDMI_PLLPWRCMD_BOTHON_ALLCLKS);
पूर्ण

अटल व्योम hdmi_pll_disable(काष्ठा dss_pll *dsspll)
अणु
	काष्ठा hdmi_pll_data *pll = container_of(dsspll, काष्ठा hdmi_pll_data, pll);
	काष्ठा hdmi_wp_data *wp = pll->wp;

	hdmi_wp_set_pll_pwr(wp, HDMI_PLLPWRCMD_ALLOFF);

	dss_ctrl_pll_enable(DSS_PLL_HDMI, false);
पूर्ण

अटल स्थिर काष्ठा dss_pll_ops dsi_pll_ops = अणु
	.enable = hdmi_pll_enable,
	.disable = hdmi_pll_disable,
	.set_config = dss_pll_ग_लिखो_config_type_b,
पूर्ण;

अटल स्थिर काष्ठा dss_pll_hw dss_omap4_hdmi_pll_hw = अणु
	.n_max = 255,
	.m_min = 20,
	.m_max = 4095,
	.mX_max = 127,
	.fपूर्णांक_min = 500000,
	.fपूर्णांक_max = 2500000,

	.clkdco_min = 500000000,
	.clkdco_low = 1000000000,
	.clkdco_max = 2000000000,

	.n_msb = 8,
	.n_lsb = 1,
	.m_msb = 20,
	.m_lsb = 9,

	.mX_msb[0] = 24,
	.mX_lsb[0] = 18,

	.has_selfreqdco = true,
पूर्ण;

अटल स्थिर काष्ठा dss_pll_hw dss_omap5_hdmi_pll_hw = अणु
	.n_max = 255,
	.m_min = 20,
	.m_max = 2045,
	.mX_max = 127,
	.fपूर्णांक_min = 620000,
	.fपूर्णांक_max = 2500000,

	.clkdco_min = 750000000,
	.clkdco_low = 1500000000,
	.clkdco_max = 2500000000UL,

	.n_msb = 8,
	.n_lsb = 1,
	.m_msb = 20,
	.m_lsb = 9,

	.mX_msb[0] = 24,
	.mX_lsb[0] = 18,

	.has_selfreqdco = true,
	.has_refsel = true,
पूर्ण;

अटल पूर्णांक dsi_init_pll_data(काष्ठा platक्रमm_device *pdev, काष्ठा hdmi_pll_data *hpll)
अणु
	काष्ठा dss_pll *pll = &hpll->pll;
	काष्ठा clk *clk;
	पूर्णांक r;

	clk = devm_clk_get(&pdev->dev, "sys_clk");
	अगर (IS_ERR(clk)) अणु
		DSSERR("can't get sys_clk\n");
		वापस PTR_ERR(clk);
	पूर्ण

	pll->name = "hdmi";
	pll->id = DSS_PLL_HDMI;
	pll->base = hpll->base;
	pll->clkin = clk;

	चयन (omapdss_get_version()) अणु
	हाल OMAPDSS_VER_OMAP4430_ES1:
	हाल OMAPDSS_VER_OMAP4430_ES2:
	हाल OMAPDSS_VER_OMAP4:
		pll->hw = &dss_omap4_hdmi_pll_hw;
		अवरोध;

	हाल OMAPDSS_VER_OMAP5:
	हाल OMAPDSS_VER_DRA7xx:
		pll->hw = &dss_omap5_hdmi_pll_hw;
		अवरोध;

	शेष:
		वापस -ENODEV;
	पूर्ण

	pll->ops = &dsi_pll_ops;

	r = dss_pll_रेजिस्टर(pll);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

पूर्णांक hdmi_pll_init(काष्ठा platक्रमm_device *pdev, काष्ठा hdmi_pll_data *pll,
	काष्ठा hdmi_wp_data *wp)
अणु
	पूर्णांक r;

	pll->wp = wp;

	pll->base = devm_platक्रमm_ioremap_resource_byname(pdev, "pll");
	अगर (IS_ERR(pll->base)) अणु
		DSSERR("can't ioremap PLLCTRL\n");
		वापस PTR_ERR(pll->base);
	पूर्ण

	r = dsi_init_pll_data(pdev, pll);
	अगर (r) अणु
		DSSERR("failed to init HDMI PLL\n");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

व्योम hdmi_pll_uninit(काष्ठा hdmi_pll_data *hpll)
अणु
	काष्ठा dss_pll *pll = &hpll->pll;

	dss_pll_unरेजिस्टर(pll);
पूर्ण
