<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/delay.h>

#समावेश "hdmi.h"

अटल व्योम hdmi_phy_8x60_घातerup(काष्ठा hdmi_phy *phy,
		अचिन्हित दीर्घ पूर्णांक pixघड़ी)
अणु
	/* De-serializer delay D/C क्रम non-lbk mode: */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG0,
		       HDMI_8x60_PHY_REG0_DESER_DEL_CTRL(3));

	अगर (pixघड़ी == 27000000) अणु
		/* video_क्रमmat == HDMI_VFRMT_720x480p60_16_9 */
		hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG1,
			       HDMI_8x60_PHY_REG1_DTEST_MUX_SEL(5) |
			       HDMI_8x60_PHY_REG1_OUTVOL_SWING_CTRL(3));
	पूर्ण अन्यथा अणु
		hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG1,
			       HDMI_8x60_PHY_REG1_DTEST_MUX_SEL(5) |
			       HDMI_8x60_PHY_REG1_OUTVOL_SWING_CTRL(4));
	पूर्ण

	/* No matter what, start from the घातer करोwn mode: */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG2,
		       HDMI_8x60_PHY_REG2_PD_PWRGEN |
		       HDMI_8x60_PHY_REG2_PD_PLL |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_4 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_3 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_2 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_1 |
		       HDMI_8x60_PHY_REG2_PD_DESER);

	/* Turn PowerGen on: */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG2,
		       HDMI_8x60_PHY_REG2_PD_PLL |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_4 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_3 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_2 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_1 |
		       HDMI_8x60_PHY_REG2_PD_DESER);

	/* Turn PLL घातer on: */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG2,
		       HDMI_8x60_PHY_REG2_PD_DRIVE_4 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_3 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_2 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_1 |
		       HDMI_8x60_PHY_REG2_PD_DESER);

	/* Write to HIGH after PLL घातer करोwn de-निश्चित: */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG3,
		       HDMI_8x60_PHY_REG3_PLL_ENABLE);

	/* ASIC घातer on; PHY REG9 = 0 */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG9, 0);

	/* Enable PLL lock detect, PLL lock det will go high after lock
	 * Enable the re-समय logic
	 */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG12,
		       HDMI_8x60_PHY_REG12_RETIMING_EN |
		       HDMI_8x60_PHY_REG12_PLL_LOCK_DETECT_EN);

	/* Drivers are on: */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG2,
		       HDMI_8x60_PHY_REG2_PD_DESER);

	/* If the RX detector is needed: */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG2,
		       HDMI_8x60_PHY_REG2_RCV_SENSE_EN |
		       HDMI_8x60_PHY_REG2_PD_DESER);

	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG4, 0);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG5, 0);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG6, 0);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG7, 0);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG8, 0);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG9, 0);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG10, 0);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG11, 0);

	/* If we want to use lock enable based on counting: */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG12,
		       HDMI_8x60_PHY_REG12_RETIMING_EN |
		       HDMI_8x60_PHY_REG12_PLL_LOCK_DETECT_EN |
		       HDMI_8x60_PHY_REG12_FORCE_LOCK);
पूर्ण

अटल व्योम hdmi_phy_8x60_घातerकरोwn(काष्ठा hdmi_phy *phy)
अणु
	/* Assert RESET PHY from controller */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_PHY_CTRL,
		       HDMI_PHY_CTRL_SW_RESET);
	udelay(10);
	/* De-निश्चित RESET PHY from controller */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_PHY_CTRL, 0);
	/* Turn off Driver */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG2,
		       HDMI_8x60_PHY_REG2_PD_DRIVE_4 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_3 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_2 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_1 |
		       HDMI_8x60_PHY_REG2_PD_DESER);
	udelay(10);
	/* Disable PLL */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG3, 0);
	/* Power करोwn PHY, but keep RX-sense: */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8x60_PHY_REG2,
		       HDMI_8x60_PHY_REG2_RCV_SENSE_EN |
		       HDMI_8x60_PHY_REG2_PD_PWRGEN |
		       HDMI_8x60_PHY_REG2_PD_PLL |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_4 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_3 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_2 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_1 |
		       HDMI_8x60_PHY_REG2_PD_DESER);
पूर्ण

स्थिर काष्ठा hdmi_phy_cfg msm_hdmi_phy_8x60_cfg = अणु
	.type = MSM_HDMI_PHY_8x60,
	.घातerup = hdmi_phy_8x60_घातerup,
	.घातerकरोwn = hdmi_phy_8x60_घातerकरोwn,
पूर्ण;
