<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश "hdmi.h"

अटल व्योम hdmi_phy_8960_घातerup(काष्ठा hdmi_phy *phy,
				  अचिन्हित दीर्घ पूर्णांक pixघड़ी)
अणु
	DBG("pixclock: %lu", pixघड़ी);

	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG2, 0x00);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG0, 0x1b);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG1, 0xf2);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG4, 0x00);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG5, 0x00);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG6, 0x00);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG7, 0x00);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG8, 0x00);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG9, 0x00);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG10, 0x00);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG11, 0x00);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG3, 0x20);
पूर्ण

अटल व्योम hdmi_phy_8960_घातerकरोwn(काष्ठा hdmi_phy *phy)
अणु
	DBG("");

	hdmi_phy_ग_लिखो(phy, REG_HDMI_8960_PHY_REG2, 0x7f);
पूर्ण

अटल स्थिर अक्षर * स्थिर hdmi_phy_8960_reg_names[] = अणु
	"core-vdda",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hdmi_phy_8960_clk_names[] = अणु
	"slave_iface",
पूर्ण;

स्थिर काष्ठा hdmi_phy_cfg msm_hdmi_phy_8960_cfg = अणु
	.type = MSM_HDMI_PHY_8960,
	.घातerup = hdmi_phy_8960_घातerup,
	.घातerकरोwn = hdmi_phy_8960_घातerकरोwn,
	.reg_names = hdmi_phy_8960_reg_names,
	.num_regs = ARRAY_SIZE(hdmi_phy_8960_reg_names),
	.clk_names = hdmi_phy_8960_clk_names,
	.num_clks = ARRAY_SIZE(hdmi_phy_8960_clk_names),
पूर्ण;
