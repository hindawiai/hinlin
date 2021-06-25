<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#समावेश "dsi_phy.h"
#समावेश "dsi.xml.h"

अटल व्योम dsi_20nm_dphy_set_timing(काष्ठा msm_dsi_phy *phy,
		काष्ठा msm_dsi_dphy_timing *timing)
अणु
	व्योम __iomem *base = phy->base;

	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_TIMING_CTRL_0,
		DSI_20nm_PHY_TIMING_CTRL_0_CLK_ZERO(timing->clk_zero));
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_TIMING_CTRL_1,
		DSI_20nm_PHY_TIMING_CTRL_1_CLK_TRAIL(timing->clk_trail));
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_TIMING_CTRL_2,
		DSI_20nm_PHY_TIMING_CTRL_2_CLK_PREPARE(timing->clk_prepare));
	अगर (timing->clk_zero & BIT(8))
		dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_TIMING_CTRL_3,
			DSI_20nm_PHY_TIMING_CTRL_3_CLK_ZERO_8);
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_TIMING_CTRL_4,
		DSI_20nm_PHY_TIMING_CTRL_4_HS_EXIT(timing->hs_निकास));
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_TIMING_CTRL_5,
		DSI_20nm_PHY_TIMING_CTRL_5_HS_ZERO(timing->hs_zero));
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_TIMING_CTRL_6,
		DSI_20nm_PHY_TIMING_CTRL_6_HS_PREPARE(timing->hs_prepare));
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_TIMING_CTRL_7,
		DSI_20nm_PHY_TIMING_CTRL_7_HS_TRAIL(timing->hs_trail));
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_TIMING_CTRL_8,
		DSI_20nm_PHY_TIMING_CTRL_8_HS_RQST(timing->hs_rqst));
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_TIMING_CTRL_9,
		DSI_20nm_PHY_TIMING_CTRL_9_TA_GO(timing->ta_go) |
		DSI_20nm_PHY_TIMING_CTRL_9_TA_SURE(timing->ta_sure));
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_TIMING_CTRL_10,
		DSI_20nm_PHY_TIMING_CTRL_10_TA_GET(timing->ta_get));
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_TIMING_CTRL_11,
		DSI_20nm_PHY_TIMING_CTRL_11_TRIG3_CMD(0));
पूर्ण

अटल व्योम dsi_20nm_phy_regulator_ctrl(काष्ठा msm_dsi_phy *phy, bool enable)
अणु
	व्योम __iomem *base = phy->reg_base;

	अगर (!enable) अणु
		dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_REGULATOR_CAL_PWR_CFG, 0);
		वापस;
	पूर्ण

	अगर (phy->regulator_lकरो_mode) अणु
		dsi_phy_ग_लिखो(phy->base + REG_DSI_20nm_PHY_LDO_CNTRL, 0x1d);
		वापस;
	पूर्ण

	/* non LDO mode */
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_REGULATOR_CTRL_1, 0x03);
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_REGULATOR_CTRL_2, 0x03);
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_REGULATOR_CTRL_3, 0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_REGULATOR_CTRL_4, 0x20);
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_REGULATOR_CAL_PWR_CFG, 0x01);
	dsi_phy_ग_लिखो(phy->base + REG_DSI_20nm_PHY_LDO_CNTRL, 0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_REGULATOR_CTRL_0, 0x03);
पूर्ण

अटल पूर्णांक dsi_20nm_phy_enable(काष्ठा msm_dsi_phy *phy,
				काष्ठा msm_dsi_phy_clk_request *clk_req)
अणु
	काष्ठा msm_dsi_dphy_timing *timing = &phy->timing;
	पूर्णांक i;
	व्योम __iomem *base = phy->base;
	u32 cfg_4[4] = अणु0x20, 0x40, 0x20, 0x00पूर्ण;
	u32 val;

	DBG("");

	अगर (msm_dsi_dphy_timing_calc(timing, clk_req)) अणु
		DRM_DEV_ERROR(&phy->pdev->dev,
			"%s: D-PHY timing calculation failed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dsi_20nm_phy_regulator_ctrl(phy, true);

	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_STRENGTH_0, 0xff);

	val = dsi_phy_पढ़ो(base + REG_DSI_20nm_PHY_GLBL_TEST_CTRL);
	अगर (phy->id == DSI_1 && phy->useहाल == MSM_DSI_PHY_STANDALONE)
		val |= DSI_20nm_PHY_GLBL_TEST_CTRL_BITCLK_HS_SEL;
	अन्यथा
		val &= ~DSI_20nm_PHY_GLBL_TEST_CTRL_BITCLK_HS_SEL;
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_GLBL_TEST_CTRL, val);

	क्रम (i = 0; i < 4; i++) अणु
		dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_LN_CFG_3(i),
							(i >> 1) * 0x40);
		dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_LN_TEST_STR_0(i), 0x01);
		dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_LN_TEST_STR_1(i), 0x46);
		dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_LN_CFG_0(i), 0x02);
		dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_LN_CFG_1(i), 0xa0);
		dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_LN_CFG_4(i), cfg_4[i]);
	पूर्ण

	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_LNCK_CFG_3, 0x80);
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_LNCK_TEST_STR0, 0x01);
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_LNCK_TEST_STR1, 0x46);
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_LNCK_CFG_0, 0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_LNCK_CFG_1, 0xa0);
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_LNCK_CFG_2, 0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_LNCK_CFG_4, 0x00);

	dsi_20nm_dphy_set_timing(phy, timing);

	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_CTRL_1, 0x00);

	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_STRENGTH_1, 0x06);

	/* make sure everything is written beक्रमe enable */
	wmb();
	dsi_phy_ग_लिखो(base + REG_DSI_20nm_PHY_CTRL_0, 0x7f);

	वापस 0;
पूर्ण

अटल व्योम dsi_20nm_phy_disable(काष्ठा msm_dsi_phy *phy)
अणु
	dsi_phy_ग_लिखो(phy->base + REG_DSI_20nm_PHY_CTRL_0, 0);
	dsi_20nm_phy_regulator_ctrl(phy, false);
पूर्ण

स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_20nm_cfgs = अणु
	.has_phy_regulator = true,
	.reg_cfg = अणु
		.num = 2,
		.regs = अणु
			अणु"vddio", 100000, 100पूर्ण,	/* 1.8 V */
			अणु"vcca", 10000, 100पूर्ण,	/* 1.0 V */
		पूर्ण,
	पूर्ण,
	.ops = अणु
		.enable = dsi_20nm_phy_enable,
		.disable = dsi_20nm_phy_disable,
	पूर्ण,
	.io_start = अणु 0xfd998500, 0xfd9a0500 पूर्ण,
	.num_dsi_phy = 2,
पूर्ण;

