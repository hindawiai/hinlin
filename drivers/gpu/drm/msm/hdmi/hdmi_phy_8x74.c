<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश "hdmi.h"

अटल व्योम hdmi_phy_8x74_घातerup(काष्ठा hdmi_phy *phy,
		अचिन्हित दीर्घ पूर्णांक pixघड़ी)
अणु
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x74_ANA_CFG0,   0x1b);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x74_ANA_CFG1,   0xf2);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x74_BIST_CFG0,  0x0);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x74_BIST_PATN0, 0x0);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x74_BIST_PATN1, 0x0);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x74_BIST_PATN2, 0x0);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x74_BIST_PATN3, 0x0);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x74_PD_CTRL1,   0x20);
पूर्ण

अटल व्योम hdmi_phy_8x74_घातerकरोwn(काष्ठा hdmi_phy *phy)
अणु
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x74_PD_CTRL0, 0x7f);
पूर्ण

अटल स्थिर अक्षर * स्थिर hdmi_phy_8x74_reg_names[] = अणु
	"core-vdda",
	"vddio",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hdmi_phy_8x74_clk_names[] = अणु
	"iface", "alt_iface"
पूर्ण;

स्थिर काष्ठा hdmi_phy_cfg msm_hdmi_phy_8x74_cfg = अणु
	.type = MSM_HDMI_PHY_8x74,
	.घातerup = hdmi_phy_8x74_घातerup,
	.घातerकरोwn = hdmi_phy_8x74_घातerकरोwn,
	.reg_names = hdmi_phy_8x74_reg_names,
	.num_regs = ARRAY_SIZE(hdmi_phy_8x74_reg_names),
	.clk_names = hdmi_phy_8x74_clk_names,
	.num_clks = ARRAY_SIZE(hdmi_phy_8x74_clk_names),
पूर्ण;
