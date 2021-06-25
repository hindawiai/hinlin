<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>

#समावेश "hdmi.h"

काष्ठा hdmi_pll_8960 अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा clk_hw clk_hw;
	व्योम __iomem *mmio;

	अचिन्हित दीर्घ pixclk;
पूर्ण;

#घोषणा hw_clk_to_pll(x) container_of(x, काष्ठा hdmi_pll_8960, clk_hw)

/*
 * HDMI PLL:
 *
 * To get the parent घड़ी setup properly, we need to plug in hdmi pll
 * configuration पूर्णांकo common-घड़ी-framework.
 */

काष्ठा pll_rate अणु
	अचिन्हित दीर्घ rate;
	पूर्णांक num_reg;
	काष्ठा अणु
		u32 val;
		u32 reg;
	पूर्ण conf[32];
पूर्ण;

/* NOTE: keep sorted highest freq to lowest: */
अटल स्थिर काष्ठा pll_rate freqtbl[] = अणु
	अणु 154000000, 14, अणु
		अणु 0x08, REG_HDMI_8960_PHY_PLL_REFCLK_CFG    पूर्ण,
		अणु 0x20, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG0 पूर्ण,
		अणु 0xf9, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG1 पूर्ण,
		अणु 0x02, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG0   पूर्ण,
		अणु 0x03, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG1   पूर्ण,
		अणु 0x3b, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG2   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG3   पूर्ण,
		अणु 0x86, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG4   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG5   पूर्ण,
		अणु 0x0d, REG_HDMI_8960_PHY_PLL_SDM_CFG0      पूर्ण,
		अणु 0x4d, REG_HDMI_8960_PHY_PLL_SDM_CFG1      पूर्ण,
		अणु 0x5e, REG_HDMI_8960_PHY_PLL_SDM_CFG2      पूर्ण,
		अणु 0x42, REG_HDMI_8960_PHY_PLL_SDM_CFG3      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SDM_CFG4      पूर्ण,
			पूर्ण
	पूर्ण,
	/* 1080p60/1080p50 हाल */
	अणु 148500000, 27, अणु
		अणु 0x02, REG_HDMI_8960_PHY_PLL_REFCLK_CFG    पूर्ण,
		अणु 0x02, REG_HDMI_8960_PHY_PLL_CHRG_PUMP_CFG पूर्ण,
		अणु 0x01, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG0 पूर्ण,
		अणु 0x33, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG1 पूर्ण,
		अणु 0x2c, REG_HDMI_8960_PHY_PLL_IDAC_ADJ_CFG  पूर्ण,
		अणु 0x06, REG_HDMI_8960_PHY_PLL_I_VI_KVCO_CFG पूर्ण,
		अणु 0x0a, REG_HDMI_8960_PHY_PLL_PWRDN_B       पूर्ण,
		अणु 0x76, REG_HDMI_8960_PHY_PLL_SDM_CFG0      पूर्ण,
		अणु 0x01, REG_HDMI_8960_PHY_PLL_SDM_CFG1      पूर्ण,
		अणु 0x4c, REG_HDMI_8960_PHY_PLL_SDM_CFG2      पूर्ण,
		अणु 0xc0, REG_HDMI_8960_PHY_PLL_SDM_CFG3      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SDM_CFG4      पूर्ण,
		अणु 0x9a, REG_HDMI_8960_PHY_PLL_SSC_CFG0      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SSC_CFG1      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SSC_CFG2      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SSC_CFG3      पूर्ण,
		अणु 0x10, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG0  पूर्ण,
		अणु 0x1a, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG1  पूर्ण,
		अणु 0x0d, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG2  पूर्ण,
		अणु 0xe6, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG0   पूर्ण,
		अणु 0x02, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG1   पूर्ण,
		अणु 0x3b, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG2   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG3   पूर्ण,
		अणु 0x86, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG4   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG5   पूर्ण,
		अणु 0x33, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG6   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG7   पूर्ण,
			पूर्ण
	पूर्ण,
	अणु 108000000, 13, अणु
		अणु 0x08, REG_HDMI_8960_PHY_PLL_REFCLK_CFG    पूर्ण,
		अणु 0x21, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG0 पूर्ण,
		अणु 0xf9, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG1 पूर्ण,
		अणु 0x1c, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG0   पूर्ण,
		अणु 0x02, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG1   पूर्ण,
		अणु 0x3b, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG2   पूर्ण,
		अणु 0x86, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG4   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG5   पूर्ण,
		अणु 0x49, REG_HDMI_8960_PHY_PLL_SDM_CFG0      पूर्ण,
		अणु 0x49, REG_HDMI_8960_PHY_PLL_SDM_CFG1      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SDM_CFG2      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SDM_CFG3      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SDM_CFG4      पूर्ण,
			पूर्ण
	पूर्ण,
	/* 720p60/720p50/1080i60/1080i50/1080p24/1080p30/1080p25 */
	अणु 74250000, 8, अणु
		अणु 0x0a, REG_HDMI_8960_PHY_PLL_PWRDN_B       पूर्ण,
		अणु 0x12, REG_HDMI_8960_PHY_PLL_REFCLK_CFG    पूर्ण,
		अणु 0x01, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG0 पूर्ण,
		अणु 0x33, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG1 पूर्ण,
		अणु 0x76, REG_HDMI_8960_PHY_PLL_SDM_CFG0      पूर्ण,
		अणु 0xe6, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG0   पूर्ण,
		अणु 0x02, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG1   पूर्ण,
		अणु 0x3b, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG2   पूर्ण,
			पूर्ण
	पूर्ण,
	अणु 74176000, 14, अणु
		अणु 0x18, REG_HDMI_8960_PHY_PLL_REFCLK_CFG    पूर्ण,
		अणु 0x20, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG0 पूर्ण,
		अणु 0xf9, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG1 पूर्ण,
		अणु 0xe5, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG0   पूर्ण,
		अणु 0x02, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG1   पूर्ण,
		अणु 0x3b, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG2   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG3   पूर्ण,
		अणु 0x86, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG4   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG5   पूर्ण,
		अणु 0x0c, REG_HDMI_8960_PHY_PLL_SDM_CFG0      पूर्ण,
		अणु 0x4c, REG_HDMI_8960_PHY_PLL_SDM_CFG1      पूर्ण,
		अणु 0x7d, REG_HDMI_8960_PHY_PLL_SDM_CFG2      पूर्ण,
		अणु 0xbc, REG_HDMI_8960_PHY_PLL_SDM_CFG3      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SDM_CFG4      पूर्ण,
			पूर्ण
	पूर्ण,
	अणु 65000000, 14, अणु
		अणु 0x18, REG_HDMI_8960_PHY_PLL_REFCLK_CFG    पूर्ण,
		अणु 0x20, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG0 पूर्ण,
		अणु 0xf9, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG1 पूर्ण,
		अणु 0x8a, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG0   पूर्ण,
		अणु 0x02, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG1   पूर्ण,
		अणु 0x3b, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG2   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG3   पूर्ण,
		अणु 0x86, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG4   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG5   पूर्ण,
		अणु 0x0b, REG_HDMI_8960_PHY_PLL_SDM_CFG0      पूर्ण,
		अणु 0x4b, REG_HDMI_8960_PHY_PLL_SDM_CFG1      पूर्ण,
		अणु 0x7b, REG_HDMI_8960_PHY_PLL_SDM_CFG2      पूर्ण,
		अणु 0x09, REG_HDMI_8960_PHY_PLL_SDM_CFG3      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SDM_CFG4      पूर्ण,
			पूर्ण
	पूर्ण,
	/* 480p60/480i60 */
	अणु 27030000, 18, अणु
		अणु 0x0a, REG_HDMI_8960_PHY_PLL_PWRDN_B       पूर्ण,
		अणु 0x38, REG_HDMI_8960_PHY_PLL_REFCLK_CFG    पूर्ण,
		अणु 0x02, REG_HDMI_8960_PHY_PLL_CHRG_PUMP_CFG पूर्ण,
		अणु 0x20, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG0 पूर्ण,
		अणु 0xff, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG1 पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SDM_CFG0      पूर्ण,
		अणु 0x4e, REG_HDMI_8960_PHY_PLL_SDM_CFG1      पूर्ण,
		अणु 0xd7, REG_HDMI_8960_PHY_PLL_SDM_CFG2      पूर्ण,
		अणु 0x03, REG_HDMI_8960_PHY_PLL_SDM_CFG3      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SDM_CFG4      पूर्ण,
		अणु 0x2a, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG0   पूर्ण,
		अणु 0x03, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG1   पूर्ण,
		अणु 0x3b, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG2   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG3   पूर्ण,
		अणु 0x86, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG4   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG5   पूर्ण,
		अणु 0x33, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG6   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG7   पूर्ण,
			पूर्ण
	पूर्ण,
	/* 576p50/576i50 */
	अणु 27000000, 27, अणु
		अणु 0x32, REG_HDMI_8960_PHY_PLL_REFCLK_CFG    पूर्ण,
		अणु 0x02, REG_HDMI_8960_PHY_PLL_CHRG_PUMP_CFG पूर्ण,
		अणु 0x01, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG0 पूर्ण,
		अणु 0x33, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG1 पूर्ण,
		अणु 0x2c, REG_HDMI_8960_PHY_PLL_IDAC_ADJ_CFG  पूर्ण,
		अणु 0x06, REG_HDMI_8960_PHY_PLL_I_VI_KVCO_CFG पूर्ण,
		अणु 0x0a, REG_HDMI_8960_PHY_PLL_PWRDN_B       पूर्ण,
		अणु 0x7b, REG_HDMI_8960_PHY_PLL_SDM_CFG0      पूर्ण,
		अणु 0x01, REG_HDMI_8960_PHY_PLL_SDM_CFG1      पूर्ण,
		अणु 0x4c, REG_HDMI_8960_PHY_PLL_SDM_CFG2      पूर्ण,
		अणु 0xc0, REG_HDMI_8960_PHY_PLL_SDM_CFG3      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SDM_CFG4      पूर्ण,
		अणु 0x9a, REG_HDMI_8960_PHY_PLL_SSC_CFG0      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SSC_CFG1      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SSC_CFG2      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SSC_CFG3      पूर्ण,
		अणु 0x10, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG0  पूर्ण,
		अणु 0x1a, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG1  पूर्ण,
		अणु 0x0d, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG2  पूर्ण,
		अणु 0x2a, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG0   पूर्ण,
		अणु 0x03, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG1   पूर्ण,
		अणु 0x3b, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG2   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG3   पूर्ण,
		अणु 0x86, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG4   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG5   पूर्ण,
		अणु 0x33, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG6   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG7   पूर्ण,
			पूर्ण
	पूर्ण,
	/* 640x480p60 */
	अणु 25200000, 27, अणु
		अणु 0x32, REG_HDMI_8960_PHY_PLL_REFCLK_CFG    पूर्ण,
		अणु 0x02, REG_HDMI_8960_PHY_PLL_CHRG_PUMP_CFG पूर्ण,
		अणु 0x01, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG0 पूर्ण,
		अणु 0x33, REG_HDMI_8960_PHY_PLL_LOOP_FLT_CFG1 पूर्ण,
		अणु 0x2c, REG_HDMI_8960_PHY_PLL_IDAC_ADJ_CFG  पूर्ण,
		अणु 0x06, REG_HDMI_8960_PHY_PLL_I_VI_KVCO_CFG पूर्ण,
		अणु 0x0a, REG_HDMI_8960_PHY_PLL_PWRDN_B       पूर्ण,
		अणु 0x77, REG_HDMI_8960_PHY_PLL_SDM_CFG0      पूर्ण,
		अणु 0x4c, REG_HDMI_8960_PHY_PLL_SDM_CFG1      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SDM_CFG2      पूर्ण,
		अणु 0xc0, REG_HDMI_8960_PHY_PLL_SDM_CFG3      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SDM_CFG4      पूर्ण,
		अणु 0x9a, REG_HDMI_8960_PHY_PLL_SSC_CFG0      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SSC_CFG1      पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_SSC_CFG2      पूर्ण,
		अणु 0x20, REG_HDMI_8960_PHY_PLL_SSC_CFG3      पूर्ण,
		अणु 0x10, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG0  पूर्ण,
		अणु 0x1a, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG1  पूर्ण,
		अणु 0x0d, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG2  पूर्ण,
		अणु 0xf4, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG0   पूर्ण,
		अणु 0x02, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG1   पूर्ण,
		अणु 0x3b, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG2   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG3   पूर्ण,
		अणु 0x86, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG4   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG5   पूर्ण,
		अणु 0x33, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG6   पूर्ण,
		अणु 0x00, REG_HDMI_8960_PHY_PLL_VCOCAL_CFG7   पूर्ण,
			पूर्ण
	पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम pll_ग_लिखो(काष्ठा hdmi_pll_8960 *pll, u32 reg, u32 data)
अणु
	msm_ग_लिखोl(data, pll->mmio + reg);
पूर्ण

अटल अंतरभूत u32 pll_पढ़ो(काष्ठा hdmi_pll_8960 *pll, u32 reg)
अणु
	वापस msm_पढ़ोl(pll->mmio + reg);
पूर्ण

अटल अंतरभूत काष्ठा hdmi_phy *pll_get_phy(काष्ठा hdmi_pll_8960 *pll)
अणु
	वापस platक्रमm_get_drvdata(pll->pdev);
पूर्ण

अटल पूर्णांक hdmi_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा hdmi_pll_8960 *pll = hw_clk_to_pll(hw);
	काष्ठा hdmi_phy *phy = pll_get_phy(pll);
	पूर्णांक समयout_count, pll_lock_retry = 10;
	अचिन्हित पूर्णांक val;

	DBG("");

	/* Assert PLL S/W reset */
	pll_ग_लिखो(pll, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG2, 0x8d);
	pll_ग_लिखो(pll, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG0, 0x10);
	pll_ग_लिखो(pll, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG1, 0x1a);

	/* Wait क्रम a लघु समय beक्रमe de-निश्चितing
	 * to allow the hardware to complete its job.
	 * This much of delay should be fine क्रम hardware
	 * to निश्चित and de-निश्चित.
	 */
	udelay(10);

	/* De-निश्चित PLL S/W reset */
	pll_ग_लिखो(pll, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG2, 0x0d);

	val = hdmi_phy_पढ़ो(phy, REG_HDMI_8960_PHY_REG12);
	val |= HDMI_8960_PHY_REG12_SW_RESET;
	/* Assert PHY S/W reset */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG12, val);
	val &= ~HDMI_8960_PHY_REG12_SW_RESET;
	/*
	 * Wait क्रम a लघु समय beक्रमe de-निश्चितing to allow the hardware to
	 * complete its job. This much of delay should be fine क्रम hardware to
	 * निश्चित and de-निश्चित.
	 */
	udelay(10);
	/* De-निश्चित PHY S/W reset */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG12, val);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG2,  0x3f);

	val = hdmi_phy_पढ़ो(phy, REG_HDMI_8960_PHY_REG12);
	val |= HDMI_8960_PHY_REG12_PWRDN_B;
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG12, val);
	/* Wait 10 us क्रम enabling global घातer क्रम PHY */
	mb();
	udelay(10);

	val = pll_पढ़ो(pll, REG_HDMI_8960_PHY_PLL_PWRDN_B);
	val |= HDMI_8960_PHY_PLL_PWRDN_B_PLL_PWRDN_B;
	val &= ~HDMI_8960_PHY_PLL_PWRDN_B_PD_PLL;
	pll_ग_लिखो(pll, REG_HDMI_8960_PHY_PLL_PWRDN_B, val);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG2, 0x80);

	समयout_count = 1000;
	जबतक (--pll_lock_retry > 0) अणु
		/* are we there yet? */
		val = pll_पढ़ो(pll, REG_HDMI_8960_PHY_PLL_STATUS0);
		अगर (val & HDMI_8960_PHY_PLL_STATUS0_PLL_LOCK)
			अवरोध;

		udelay(1);

		अगर (--समयout_count > 0)
			जारी;

		/*
		 * PLL has still not locked.
		 * Do a software reset and try again
		 * Assert PLL S/W reset first
		 */
		pll_ग_लिखो(pll, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG2, 0x8d);
		udelay(10);
		pll_ग_लिखो(pll, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG2, 0x0d);

		/*
		 * Wait क्रम a लघु duration क्रम the PLL calibration
		 * beक्रमe checking अगर the PLL माला_लो locked
		 */
		udelay(350);

		समयout_count = 1000;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hdmi_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा hdmi_pll_8960 *pll = hw_clk_to_pll(hw);
	काष्ठा hdmi_phy *phy = pll_get_phy(pll);
	अचिन्हित पूर्णांक val;

	DBG("");

	val = hdmi_phy_पढ़ो(phy, REG_HDMI_8960_PHY_REG12);
	val &= ~HDMI_8960_PHY_REG12_PWRDN_B;
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG12, val);

	val = pll_पढ़ो(pll, REG_HDMI_8960_PHY_PLL_PWRDN_B);
	val |= HDMI_8960_PHY_REG12_SW_RESET;
	val &= ~HDMI_8960_PHY_REG12_PWRDN_B;
	pll_ग_लिखो(pll, REG_HDMI_8960_PHY_PLL_PWRDN_B, val);
	/* Make sure HDMI PHY/PLL are घातered करोwn */
	mb();
पूर्ण

अटल स्थिर काष्ठा pll_rate *find_rate(अचिन्हित दीर्घ rate)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < ARRAY_SIZE(freqtbl); i++)
		अगर (rate > freqtbl[i].rate)
			वापस &freqtbl[i - 1];

	वापस &freqtbl[i - 1];
पूर्ण

अटल अचिन्हित दीर्घ hdmi_pll_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hdmi_pll_8960 *pll = hw_clk_to_pll(hw);

	वापस pll->pixclk;
पूर्ण

अटल दीर्घ hdmi_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	स्थिर काष्ठा pll_rate *pll_rate = find_rate(rate);

	वापस pll_rate->rate;
पूर्ण

अटल पूर्णांक hdmi_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hdmi_pll_8960 *pll = hw_clk_to_pll(hw);
	स्थिर काष्ठा pll_rate *pll_rate = find_rate(rate);
	पूर्णांक i;

	DBG("rate=%lu", rate);

	क्रम (i = 0; i < pll_rate->num_reg; i++)
		pll_ग_लिखो(pll, pll_rate->conf[i].reg, pll_rate->conf[i].val);

	pll->pixclk = rate;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops hdmi_pll_ops = अणु
	.enable = hdmi_pll_enable,
	.disable = hdmi_pll_disable,
	.recalc_rate = hdmi_pll_recalc_rate,
	.round_rate = hdmi_pll_round_rate,
	.set_rate = hdmi_pll_set_rate,
पूर्ण;

अटल स्थिर अक्षर * स्थिर hdmi_pll_parents[] = अणु
	"pxo",
पूर्ण;

अटल काष्ठा clk_init_data pll_init = अणु
	.name = "hdmi_pll",
	.ops = &hdmi_pll_ops,
	.parent_names = hdmi_pll_parents,
	.num_parents = ARRAY_SIZE(hdmi_pll_parents),
	.flags = CLK_IGNORE_UNUSED,
पूर्ण;

पूर्णांक msm_hdmi_pll_8960_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hdmi_pll_8960 *pll;
	काष्ठा clk *clk;
	पूर्णांक i;

	/* sanity check: */
	क्रम (i = 0; i < (ARRAY_SIZE(freqtbl) - 1); i++)
		अगर (WARN_ON(freqtbl[i].rate < freqtbl[i + 1].rate))
			वापस -EINVAL;

	pll = devm_kzalloc(dev, माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस -ENOMEM;

	pll->mmio = msm_ioremap(pdev, "hdmi_pll", "HDMI_PLL");
	अगर (IS_ERR(pll->mmio)) अणु
		DRM_DEV_ERROR(dev, "failed to map pll base\n");
		वापस -ENOMEM;
	पूर्ण

	pll->pdev = pdev;
	pll->clk_hw.init = &pll_init;

	clk = devm_clk_रेजिस्टर(dev, &pll->clk_hw);
	अगर (IS_ERR(clk)) अणु
		DRM_DEV_ERROR(dev, "failed to register pll clock\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
