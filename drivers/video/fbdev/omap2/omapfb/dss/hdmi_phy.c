<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HDMI PHY
 *
 * Copyright (C) 2013 Texas Instruments Incorporated
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "hdmi.h"

काष्ठा hdmi_phy_features अणु
	bool bist_ctrl;
	bool lकरो_voltage;
	अचिन्हित दीर्घ max_phy;
पूर्ण;

अटल स्थिर काष्ठा hdmi_phy_features *phy_feat;

व्योम hdmi_phy_dump(काष्ठा hdmi_phy_data *phy, काष्ठा seq_file *s)
अणु
#घोषणा DUMPPHY(r) seq_म_लिखो(s, "%-35s %08x\n", #r,\
		hdmi_पढ़ो_reg(phy->base, r))

	DUMPPHY(HDMI_TXPHY_TX_CTRL);
	DUMPPHY(HDMI_TXPHY_DIGITAL_CTRL);
	DUMPPHY(HDMI_TXPHY_POWER_CTRL);
	DUMPPHY(HDMI_TXPHY_PAD_CFG_CTRL);
	अगर (phy_feat->bist_ctrl)
		DUMPPHY(HDMI_TXPHY_BIST_CONTROL);
पूर्ण

पूर्णांक hdmi_phy_parse_lanes(काष्ठा hdmi_phy_data *phy, स्थिर u32 *lanes)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i += 2) अणु
		u8 lane, pol;
		पूर्णांक dx, dy;

		dx = lanes[i];
		dy = lanes[i + 1];

		अगर (dx < 0 || dx >= 8)
			वापस -EINVAL;

		अगर (dy < 0 || dy >= 8)
			वापस -EINVAL;

		अगर (dx & 1) अणु
			अगर (dy != dx - 1)
				वापस -EINVAL;
			pol = 1;
		पूर्ण अन्यथा अणु
			अगर (dy != dx + 1)
				वापस -EINVAL;
			pol = 0;
		पूर्ण

		lane = dx / 2;

		phy->lane_function[lane] = i / 2;
		phy->lane_polarity[lane] = pol;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hdmi_phy_configure_lanes(काष्ठा hdmi_phy_data *phy)
अणु
	अटल स्थिर u16 pad_cfg_list[] = अणु
		0x0123,
		0x0132,
		0x0312,
		0x0321,
		0x0231,
		0x0213,
		0x1023,
		0x1032,
		0x3012,
		0x3021,
		0x2031,
		0x2013,
		0x1203,
		0x1302,
		0x3102,
		0x3201,
		0x2301,
		0x2103,
		0x1230,
		0x1320,
		0x3120,
		0x3210,
		0x2310,
		0x2130,
	पूर्ण;

	u16 lane_cfg = 0;
	पूर्णांक i;
	अचिन्हित lane_cfg_val;
	u16 pol_val = 0;

	क्रम (i = 0; i < 4; ++i)
		lane_cfg |= phy->lane_function[i] << ((3 - i) * 4);

	pol_val |= phy->lane_polarity[0] << 0;
	pol_val |= phy->lane_polarity[1] << 3;
	pol_val |= phy->lane_polarity[2] << 2;
	pol_val |= phy->lane_polarity[3] << 1;

	क्रम (i = 0; i < ARRAY_SIZE(pad_cfg_list); ++i)
		अगर (pad_cfg_list[i] == lane_cfg)
			अवरोध;

	अगर (WARN_ON(i == ARRAY_SIZE(pad_cfg_list)))
		i = 0;

	lane_cfg_val = i;

	REG_FLD_MOD(phy->base, HDMI_TXPHY_PAD_CFG_CTRL, lane_cfg_val, 26, 22);
	REG_FLD_MOD(phy->base, HDMI_TXPHY_PAD_CFG_CTRL, pol_val, 30, 27);
पूर्ण

पूर्णांक hdmi_phy_configure(काष्ठा hdmi_phy_data *phy, अचिन्हित दीर्घ hfbitclk,
	अचिन्हित दीर्घ lfbitclk)
अणु
	u8 freqout;

	/*
	 * Read address 0 in order to get the SCP reset करोne completed
	 * Dummy access perक्रमmed to make sure reset is करोne
	 */
	hdmi_पढ़ो_reg(phy->base, HDMI_TXPHY_TX_CTRL);

	/*
	 * In OMAP5+, the HFBITCLK must be भागided by 2 beक्रमe issuing the
	 * HDMI_PHYPWRCMD_LDOON command.
	*/
	अगर (phy_feat->bist_ctrl)
		REG_FLD_MOD(phy->base, HDMI_TXPHY_BIST_CONTROL, 1, 11, 11);

	/*
	 * If the hfbitclk != lfbitclk, it means the lfbitclk was configured
	 * to be used क्रम TMDS.
	 */
	अगर (hfbitclk != lfbitclk)
		freqout = 0;
	अन्यथा अगर (hfbitclk / 10 < phy_feat->max_phy)
		freqout = 1;
	अन्यथा
		freqout = 2;

	/*
	 * Write to phy address 0 to configure the घड़ी
	 * use HFBITCLK ग_लिखो HDMI_TXPHY_TX_CONTROL_FREQOUT field
	 */
	REG_FLD_MOD(phy->base, HDMI_TXPHY_TX_CTRL, freqout, 31, 30);

	/* Write to phy address 1 to start HDMI line (TXVALID and TMDSCLKEN) */
	hdmi_ग_लिखो_reg(phy->base, HDMI_TXPHY_DIGITAL_CTRL, 0xF0000000);

	/* Setup max LDO voltage */
	अगर (phy_feat->lकरो_voltage)
		REG_FLD_MOD(phy->base, HDMI_TXPHY_POWER_CTRL, 0xB, 3, 0);

	hdmi_phy_configure_lanes(phy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hdmi_phy_features omap44xx_phy_feats = अणु
	.bist_ctrl	=	false,
	.lकरो_voltage	=	true,
	.max_phy	=	185675000,
पूर्ण;

अटल स्थिर काष्ठा hdmi_phy_features omap54xx_phy_feats = अणु
	.bist_ctrl	=	true,
	.lकरो_voltage	=	false,
	.max_phy	=	186000000,
पूर्ण;

अटल स्थिर काष्ठा hdmi_phy_features *hdmi_phy_get_features(व्योम)
अणु
	चयन (omapdss_get_version()) अणु
	हाल OMAPDSS_VER_OMAP4430_ES1:
	हाल OMAPDSS_VER_OMAP4430_ES2:
	हाल OMAPDSS_VER_OMAP4:
		वापस &omap44xx_phy_feats;

	हाल OMAPDSS_VER_OMAP5:
	हाल OMAPDSS_VER_DRA7xx:
		वापस &omap54xx_phy_feats;

	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

पूर्णांक hdmi_phy_init(काष्ठा platक्रमm_device *pdev, काष्ठा hdmi_phy_data *phy)
अणु
	phy_feat = hdmi_phy_get_features();
	अगर (!phy_feat)
		वापस -ENODEV;

	phy->base = devm_platक्रमm_ioremap_resource_byname(pdev, "phy");
	अगर (IS_ERR(phy->base)) अणु
		DSSERR("can't ioremap TX PHY\n");
		वापस PTR_ERR(phy->base);
	पूर्ण

	वापस 0;
पूर्ण
