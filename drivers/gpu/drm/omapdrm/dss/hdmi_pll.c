<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HDMI PLL
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - https://www.ti.com/
 */

#घोषणा DSS_SUBSYS_NAME "HDMIPLL"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "omapdss.h"
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

अटल पूर्णांक hdmi_pll_enable(काष्ठा dss_pll *dsspll)
अणु
	काष्ठा hdmi_pll_data *pll = container_of(dsspll, काष्ठा hdmi_pll_data, pll);
	काष्ठा hdmi_wp_data *wp = pll->wp;
	पूर्णांक r;

	r = pm_runसमय_get_sync(&pll->pdev->dev);
	WARN_ON(r < 0);

	dss_ctrl_pll_enable(dsspll, true);

	r = hdmi_wp_set_pll_pwr(wp, HDMI_PLLPWRCMD_BOTHON_ALLCLKS);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल व्योम hdmi_pll_disable(काष्ठा dss_pll *dsspll)
अणु
	काष्ठा hdmi_pll_data *pll = container_of(dsspll, काष्ठा hdmi_pll_data, pll);
	काष्ठा hdmi_wp_data *wp = pll->wp;
	पूर्णांक r;

	hdmi_wp_set_pll_pwr(wp, HDMI_PLLPWRCMD_ALLOFF);

	dss_ctrl_pll_enable(dsspll, false);

	r = pm_runसमय_put_sync(&pll->pdev->dev);
	WARN_ON(r < 0 && r != -ENOSYS);
पूर्ण

अटल स्थिर काष्ठा dss_pll_ops hdmi_pll_ops = अणु
	.enable = hdmi_pll_enable,
	.disable = hdmi_pll_disable,
	.set_config = dss_pll_ग_लिखो_config_type_b,
पूर्ण;

अटल स्थिर काष्ठा dss_pll_hw dss_omap4_hdmi_pll_hw = अणु
	.type = DSS_PLL_TYPE_B,

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
	.type = DSS_PLL_TYPE_B,

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

अटल पूर्णांक hdmi_init_pll_data(काष्ठा dss_device *dss,
			      काष्ठा platक्रमm_device *pdev,
			      काष्ठा hdmi_pll_data *hpll)
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

	अगर (hpll->wp->version == 4)
		pll->hw = &dss_omap4_hdmi_pll_hw;
	अन्यथा
		pll->hw = &dss_omap5_hdmi_pll_hw;

	pll->ops = &hdmi_pll_ops;

	r = dss_pll_रेजिस्टर(dss, pll);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

पूर्णांक hdmi_pll_init(काष्ठा dss_device *dss, काष्ठा platक्रमm_device *pdev,
		  काष्ठा hdmi_pll_data *pll, काष्ठा hdmi_wp_data *wp)
अणु
	पूर्णांक r;
	काष्ठा resource *res;

	pll->pdev = pdev;
	pll->wp = wp;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "pll");
	pll->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(pll->base))
		वापस PTR_ERR(pll->base);

	r = hdmi_init_pll_data(dss, pdev, pll);
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
