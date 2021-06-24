<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2012-2014 Freescale Semiconductor, Inc.
 * Copyright (C) 2012 Marek Vasut <marex@denx.de>
 * on behalf of DENX Software Engineering GmbH
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/sपंचांगp_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/iopoll.h>

#घोषणा DRIVER_NAME "mxs_phy"

/* Register Macro */
#घोषणा HW_USBPHY_PWD				0x00
#घोषणा HW_USBPHY_TX				0x10
#घोषणा HW_USBPHY_CTRL				0x30
#घोषणा HW_USBPHY_CTRL_SET			0x34
#घोषणा HW_USBPHY_CTRL_CLR			0x38

#घोषणा HW_USBPHY_DEBUG_SET			0x54
#घोषणा HW_USBPHY_DEBUG_CLR			0x58

#घोषणा HW_USBPHY_IP				0x90
#घोषणा HW_USBPHY_IP_SET			0x94
#घोषणा HW_USBPHY_IP_CLR			0x98

#घोषणा GM_USBPHY_TX_TXCAL45DP(x)            (((x) & 0xf) << 16)
#घोषणा GM_USBPHY_TX_TXCAL45DN(x)            (((x) & 0xf) << 8)
#घोषणा GM_USBPHY_TX_D_CAL(x)                (((x) & 0xf) << 0)

/* imx7ulp */
#घोषणा HW_USBPHY_PLL_SIC			0xa0
#घोषणा HW_USBPHY_PLL_SIC_SET			0xa4
#घोषणा HW_USBPHY_PLL_SIC_CLR			0xa8

#घोषणा BM_USBPHY_CTRL_SFTRST			BIT(31)
#घोषणा BM_USBPHY_CTRL_CLKGATE			BIT(30)
#घोषणा BM_USBPHY_CTRL_OTG_ID_VALUE		BIT(27)
#घोषणा BM_USBPHY_CTRL_ENAUTOSET_USBCLKS	BIT(26)
#घोषणा BM_USBPHY_CTRL_ENAUTOCLR_USBCLKGATE	BIT(25)
#घोषणा BM_USBPHY_CTRL_ENVBUSCHG_WKUP		BIT(23)
#घोषणा BM_USBPHY_CTRL_ENIDCHG_WKUP		BIT(22)
#घोषणा BM_USBPHY_CTRL_ENDPDMCHG_WKUP		BIT(21)
#घोषणा BM_USBPHY_CTRL_ENAUTOCLR_PHY_PWD	BIT(20)
#घोषणा BM_USBPHY_CTRL_ENAUTOCLR_CLKGATE	BIT(19)
#घोषणा BM_USBPHY_CTRL_ENAUTO_PWRON_PLL		BIT(18)
#घोषणा BM_USBPHY_CTRL_ENUTMILEVEL3		BIT(15)
#घोषणा BM_USBPHY_CTRL_ENUTMILEVEL2		BIT(14)
#घोषणा BM_USBPHY_CTRL_ENHOSTDISCONDETECT	BIT(1)

#घोषणा BM_USBPHY_IP_FIX                       (BIT(17) | BIT(18))

#घोषणा BM_USBPHY_DEBUG_CLKGATE			BIT(30)
/* imx7ulp */
#घोषणा BM_USBPHY_PLL_LOCK			BIT(31)
#घोषणा BM_USBPHY_PLL_REG_ENABLE		BIT(21)
#घोषणा BM_USBPHY_PLL_BYPASS			BIT(16)
#घोषणा BM_USBPHY_PLL_POWER			BIT(12)
#घोषणा BM_USBPHY_PLL_EN_USB_CLKS		BIT(6)

/* Anatop Registers */
#घोषणा ANADIG_ANA_MISC0			0x150
#घोषणा ANADIG_ANA_MISC0_SET			0x154
#घोषणा ANADIG_ANA_MISC0_CLR			0x158

#घोषणा ANADIG_USB1_CHRG_DETECT_SET		0x1b4
#घोषणा ANADIG_USB1_CHRG_DETECT_CLR		0x1b8
#घोषणा ANADIG_USB2_CHRG_DETECT_SET		0x214
#घोषणा ANADIG_USB1_CHRG_DETECT_EN_B		BIT(20)
#घोषणा ANADIG_USB1_CHRG_DETECT_CHK_CHRG_B	BIT(19)
#घोषणा ANADIG_USB1_CHRG_DETECT_CHK_CONTACT	BIT(18)

#घोषणा ANADIG_USB1_VBUS_DET_STAT		0x1c0
#घोषणा ANADIG_USB1_VBUS_DET_STAT_VBUS_VALID	BIT(3)

#घोषणा ANADIG_USB1_CHRG_DET_STAT		0x1d0
#घोषणा ANADIG_USB1_CHRG_DET_STAT_DM_STATE	BIT(2)
#घोषणा ANADIG_USB1_CHRG_DET_STAT_CHRG_DETECTED	BIT(1)
#घोषणा ANADIG_USB1_CHRG_DET_STAT_PLUG_CONTACT	BIT(0)

#घोषणा ANADIG_USB2_VBUS_DET_STAT		0x220

#घोषणा ANADIG_USB1_LOOPBACK_SET		0x1e4
#घोषणा ANADIG_USB1_LOOPBACK_CLR		0x1e8
#घोषणा ANADIG_USB1_LOOPBACK_UTMI_TESTSTART	BIT(0)

#घोषणा ANADIG_USB2_LOOPBACK_SET		0x244
#घोषणा ANADIG_USB2_LOOPBACK_CLR		0x248

#घोषणा ANADIG_USB1_MISC			0x1f0
#घोषणा ANADIG_USB2_MISC			0x250

#घोषणा BM_ANADIG_ANA_MISC0_STOP_MODE_CONFIG	BIT(12)
#घोषणा BM_ANADIG_ANA_MISC0_STOP_MODE_CONFIG_SL BIT(11)

#घोषणा BM_ANADIG_USB1_VBUS_DET_STAT_VBUS_VALID	BIT(3)
#घोषणा BM_ANADIG_USB2_VBUS_DET_STAT_VBUS_VALID	BIT(3)

#घोषणा BM_ANADIG_USB1_LOOPBACK_UTMI_DIG_TST1	BIT(2)
#घोषणा BM_ANADIG_USB1_LOOPBACK_TSTI_TX_EN	BIT(5)
#घोषणा BM_ANADIG_USB2_LOOPBACK_UTMI_DIG_TST1	BIT(2)
#घोषणा BM_ANADIG_USB2_LOOPBACK_TSTI_TX_EN	BIT(5)

#घोषणा BM_ANADIG_USB1_MISC_RX_VPIN_FS		BIT(29)
#घोषणा BM_ANADIG_USB1_MISC_RX_VMIN_FS		BIT(28)
#घोषणा BM_ANADIG_USB2_MISC_RX_VPIN_FS		BIT(29)
#घोषणा BM_ANADIG_USB2_MISC_RX_VMIN_FS		BIT(28)

#घोषणा to_mxs_phy(p) container_of((p), काष्ठा mxs_phy, phy)

/* Do disconnection between PHY and controller without vbus */
#घोषणा MXS_PHY_DISCONNECT_LINE_WITHOUT_VBUS	BIT(0)

/*
 * The PHY will be in messy अगर there is a wakeup after putting
 * bus to suspend (set portsc.suspendM) but beक्रमe setting PHY to low
 * घातer mode (set portsc.phcd).
 */
#घोषणा MXS_PHY_ABNORMAL_IN_SUSPEND		BIT(1)

/*
 * The SOF sends too fast after resuming, it will cause disconnection
 * between host and high speed device.
 */
#घोषणा MXS_PHY_SENDING_SOF_TOO_FAST		BIT(2)

/*
 * IC has bug fixes logic, they include
 * MXS_PHY_ABNORMAL_IN_SUSPEND and MXS_PHY_SENDING_SOF_TOO_FAST
 * which are described at above flags, the RTL will handle it
 * according to dअगरferent versions.
 */
#घोषणा MXS_PHY_NEED_IP_FIX			BIT(3)

/* Minimum and maximum values क्रम device tree entries */
#घोषणा MXS_PHY_TX_CAL45_MIN			30
#घोषणा MXS_PHY_TX_CAL45_MAX			55
#घोषणा MXS_PHY_TX_D_CAL_MIN			79
#घोषणा MXS_PHY_TX_D_CAL_MAX			119

काष्ठा mxs_phy_data अणु
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल स्थिर काष्ठा mxs_phy_data imx23_phy_data = अणु
	.flags = MXS_PHY_ABNORMAL_IN_SUSPEND | MXS_PHY_SENDING_SOF_TOO_FAST,
पूर्ण;

अटल स्थिर काष्ठा mxs_phy_data imx6q_phy_data = अणु
	.flags = MXS_PHY_SENDING_SOF_TOO_FAST |
		MXS_PHY_DISCONNECT_LINE_WITHOUT_VBUS |
		MXS_PHY_NEED_IP_FIX,
पूर्ण;

अटल स्थिर काष्ठा mxs_phy_data imx6sl_phy_data = अणु
	.flags = MXS_PHY_DISCONNECT_LINE_WITHOUT_VBUS |
		MXS_PHY_NEED_IP_FIX,
पूर्ण;

अटल स्थिर काष्ठा mxs_phy_data vf610_phy_data = अणु
	.flags = MXS_PHY_DISCONNECT_LINE_WITHOUT_VBUS |
		MXS_PHY_NEED_IP_FIX,
पूर्ण;

अटल स्थिर काष्ठा mxs_phy_data imx6sx_phy_data = अणु
	.flags = MXS_PHY_DISCONNECT_LINE_WITHOUT_VBUS,
पूर्ण;

अटल स्थिर काष्ठा mxs_phy_data imx6ul_phy_data = अणु
	.flags = MXS_PHY_DISCONNECT_LINE_WITHOUT_VBUS,
पूर्ण;

अटल स्थिर काष्ठा mxs_phy_data imx7ulp_phy_data = अणु
पूर्ण;

अटल स्थिर काष्ठा of_device_id mxs_phy_dt_ids[] = अणु
	अणु .compatible = "fsl,imx6sx-usbphy", .data = &imx6sx_phy_data, पूर्ण,
	अणु .compatible = "fsl,imx6sl-usbphy", .data = &imx6sl_phy_data, पूर्ण,
	अणु .compatible = "fsl,imx6q-usbphy", .data = &imx6q_phy_data, पूर्ण,
	अणु .compatible = "fsl,imx23-usbphy", .data = &imx23_phy_data, पूर्ण,
	अणु .compatible = "fsl,vf610-usbphy", .data = &vf610_phy_data, पूर्ण,
	अणु .compatible = "fsl,imx6ul-usbphy", .data = &imx6ul_phy_data, पूर्ण,
	अणु .compatible = "fsl,imx7ulp-usbphy", .data = &imx7ulp_phy_data, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxs_phy_dt_ids);

काष्ठा mxs_phy अणु
	काष्ठा usb_phy phy;
	काष्ठा clk *clk;
	स्थिर काष्ठा mxs_phy_data *data;
	काष्ठा regmap *regmap_anatop;
	पूर्णांक port_id;
	u32 tx_reg_set;
	u32 tx_reg_mask;
पूर्ण;

अटल अंतरभूत bool is_imx6q_phy(काष्ठा mxs_phy *mxs_phy)
अणु
	वापस mxs_phy->data == &imx6q_phy_data;
पूर्ण

अटल अंतरभूत bool is_imx6sl_phy(काष्ठा mxs_phy *mxs_phy)
अणु
	वापस mxs_phy->data == &imx6sl_phy_data;
पूर्ण

अटल अंतरभूत bool is_imx7ulp_phy(काष्ठा mxs_phy *mxs_phy)
अणु
	वापस mxs_phy->data == &imx7ulp_phy_data;
पूर्ण

/*
 * PHY needs some 32K cycles to चयन from 32K घड़ी to
 * bus (such as AHB/AXI, etc) घड़ी.
 */
अटल व्योम mxs_phy_घड़ी_चयन_delay(व्योम)
अणु
	usleep_range(300, 400);
पूर्ण

अटल व्योम mxs_phy_tx_init(काष्ठा mxs_phy *mxs_phy)
अणु
	व्योम __iomem *base = mxs_phy->phy.io_priv;
	u32 phytx;

	/* Update TX रेजिस्टर अगर there is anything to ग_लिखो */
	अगर (mxs_phy->tx_reg_mask) अणु
		phytx = पढ़ोl(base + HW_USBPHY_TX);
		phytx &= ~mxs_phy->tx_reg_mask;
		phytx |= mxs_phy->tx_reg_set;
		ग_लिखोl(phytx, base + HW_USBPHY_TX);
	पूर्ण
पूर्ण

अटल पूर्णांक mxs_phy_pll_enable(व्योम __iomem *base, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (enable) अणु
		u32 value;

		ग_लिखोl(BM_USBPHY_PLL_REG_ENABLE, base + HW_USBPHY_PLL_SIC_SET);
		ग_लिखोl(BM_USBPHY_PLL_BYPASS, base + HW_USBPHY_PLL_SIC_CLR);
		ग_लिखोl(BM_USBPHY_PLL_POWER, base + HW_USBPHY_PLL_SIC_SET);
		ret = पढ़ोl_poll_समयout(base + HW_USBPHY_PLL_SIC,
			value, (value & BM_USBPHY_PLL_LOCK) != 0,
			100, 10000);
		अगर (ret)
			वापस ret;

		ग_लिखोl(BM_USBPHY_PLL_EN_USB_CLKS, base +
				HW_USBPHY_PLL_SIC_SET);
	पूर्ण अन्यथा अणु
		ग_लिखोl(BM_USBPHY_PLL_EN_USB_CLKS, base +
				HW_USBPHY_PLL_SIC_CLR);
		ग_लिखोl(BM_USBPHY_PLL_POWER, base + HW_USBPHY_PLL_SIC_CLR);
		ग_लिखोl(BM_USBPHY_PLL_BYPASS, base + HW_USBPHY_PLL_SIC_SET);
		ग_लिखोl(BM_USBPHY_PLL_REG_ENABLE, base + HW_USBPHY_PLL_SIC_CLR);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mxs_phy_hw_init(काष्ठा mxs_phy *mxs_phy)
अणु
	पूर्णांक ret;
	व्योम __iomem *base = mxs_phy->phy.io_priv;

	अगर (is_imx7ulp_phy(mxs_phy)) अणु
		ret = mxs_phy_pll_enable(base, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = sपंचांगp_reset_block(base + HW_USBPHY_CTRL);
	अगर (ret)
		जाओ disable_pll;

	/* Power up the PHY */
	ग_लिखोl(0, base + HW_USBPHY_PWD);

	/*
	 * USB PHY Ctrl Setting
	 * - Auto घड़ी/घातer on
	 * - Enable full/low speed support
	 */
	ग_लिखोl(BM_USBPHY_CTRL_ENAUTOSET_USBCLKS |
		BM_USBPHY_CTRL_ENAUTOCLR_USBCLKGATE |
		BM_USBPHY_CTRL_ENAUTOCLR_PHY_PWD |
		BM_USBPHY_CTRL_ENAUTOCLR_CLKGATE |
		BM_USBPHY_CTRL_ENAUTO_PWRON_PLL |
		BM_USBPHY_CTRL_ENUTMILEVEL2 |
		BM_USBPHY_CTRL_ENUTMILEVEL3,
	       base + HW_USBPHY_CTRL_SET);

	अगर (mxs_phy->data->flags & MXS_PHY_NEED_IP_FIX)
		ग_लिखोl(BM_USBPHY_IP_FIX, base + HW_USBPHY_IP_SET);

	अगर (mxs_phy->regmap_anatop) अणु
		अचिन्हित पूर्णांक reg = mxs_phy->port_id ?
			ANADIG_USB1_CHRG_DETECT_SET :
			ANADIG_USB2_CHRG_DETECT_SET;
		/*
		 * The बाह्यal अक्षरger detector needs to be disabled,
		 * or the संकेत at DP will be poor
		 */
		regmap_ग_लिखो(mxs_phy->regmap_anatop, reg,
			     ANADIG_USB1_CHRG_DETECT_EN_B |
			     ANADIG_USB1_CHRG_DETECT_CHK_CHRG_B);
	पूर्ण

	mxs_phy_tx_init(mxs_phy);

	वापस 0;

disable_pll:
	अगर (is_imx7ulp_phy(mxs_phy))
		mxs_phy_pll_enable(base, false);
	वापस ret;
पूर्ण

/* Return true अगर the vbus is there */
अटल bool mxs_phy_get_vbus_status(काष्ठा mxs_phy *mxs_phy)
अणु
	अचिन्हित पूर्णांक vbus_value = 0;

	अगर (!mxs_phy->regmap_anatop)
		वापस false;

	अगर (mxs_phy->port_id == 0)
		regmap_पढ़ो(mxs_phy->regmap_anatop,
			ANADIG_USB1_VBUS_DET_STAT,
			&vbus_value);
	अन्यथा अगर (mxs_phy->port_id == 1)
		regmap_पढ़ो(mxs_phy->regmap_anatop,
			ANADIG_USB2_VBUS_DET_STAT,
			&vbus_value);

	अगर (vbus_value & BM_ANADIG_USB1_VBUS_DET_STAT_VBUS_VALID)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम __mxs_phy_disconnect_line(काष्ठा mxs_phy *mxs_phy, bool disconnect)
अणु
	व्योम __iomem *base = mxs_phy->phy.io_priv;
	u32 reg;

	अगर (disconnect)
		ग_लिखोl_relaxed(BM_USBPHY_DEBUG_CLKGATE,
			base + HW_USBPHY_DEBUG_CLR);

	अगर (mxs_phy->port_id == 0) अणु
		reg = disconnect ? ANADIG_USB1_LOOPBACK_SET
			: ANADIG_USB1_LOOPBACK_CLR;
		regmap_ग_लिखो(mxs_phy->regmap_anatop, reg,
			BM_ANADIG_USB1_LOOPBACK_UTMI_DIG_TST1 |
			BM_ANADIG_USB1_LOOPBACK_TSTI_TX_EN);
	पूर्ण अन्यथा अगर (mxs_phy->port_id == 1) अणु
		reg = disconnect ? ANADIG_USB2_LOOPBACK_SET
			: ANADIG_USB2_LOOPBACK_CLR;
		regmap_ग_लिखो(mxs_phy->regmap_anatop, reg,
			BM_ANADIG_USB2_LOOPBACK_UTMI_DIG_TST1 |
			BM_ANADIG_USB2_LOOPBACK_TSTI_TX_EN);
	पूर्ण

	अगर (!disconnect)
		ग_लिखोl_relaxed(BM_USBPHY_DEBUG_CLKGATE,
			base + HW_USBPHY_DEBUG_SET);

	/* Delay some समय, and let Linestate be SE0 क्रम controller */
	अगर (disconnect)
		usleep_range(500, 1000);
पूर्ण

अटल bool mxs_phy_is_otg_host(काष्ठा mxs_phy *mxs_phy)
अणु
	व्योम __iomem *base = mxs_phy->phy.io_priv;
	u32 phyctrl = पढ़ोl(base + HW_USBPHY_CTRL);

	अगर (IS_ENABLED(CONFIG_USB_OTG) &&
			!(phyctrl & BM_USBPHY_CTRL_OTG_ID_VALUE))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम mxs_phy_disconnect_line(काष्ठा mxs_phy *mxs_phy, bool on)
अणु
	bool vbus_is_on = false;

	/* If the SoCs करोn't need to disconnect line without vbus, quit */
	अगर (!(mxs_phy->data->flags & MXS_PHY_DISCONNECT_LINE_WITHOUT_VBUS))
		वापस;

	/* If the SoCs करोn't have anatop, quit */
	अगर (!mxs_phy->regmap_anatop)
		वापस;

	vbus_is_on = mxs_phy_get_vbus_status(mxs_phy);

	अगर (on && !vbus_is_on && !mxs_phy_is_otg_host(mxs_phy))
		__mxs_phy_disconnect_line(mxs_phy, true);
	अन्यथा
		__mxs_phy_disconnect_line(mxs_phy, false);

पूर्ण

अटल पूर्णांक mxs_phy_init(काष्ठा usb_phy *phy)
अणु
	पूर्णांक ret;
	काष्ठा mxs_phy *mxs_phy = to_mxs_phy(phy);

	mxs_phy_घड़ी_चयन_delay();
	ret = clk_prepare_enable(mxs_phy->clk);
	अगर (ret)
		वापस ret;

	वापस mxs_phy_hw_init(mxs_phy);
पूर्ण

अटल व्योम mxs_phy_shutकरोwn(काष्ठा usb_phy *phy)
अणु
	काष्ठा mxs_phy *mxs_phy = to_mxs_phy(phy);
	u32 value = BM_USBPHY_CTRL_ENVBUSCHG_WKUP |
			BM_USBPHY_CTRL_ENDPDMCHG_WKUP |
			BM_USBPHY_CTRL_ENIDCHG_WKUP |
			BM_USBPHY_CTRL_ENAUTOSET_USBCLKS |
			BM_USBPHY_CTRL_ENAUTOCLR_USBCLKGATE |
			BM_USBPHY_CTRL_ENAUTOCLR_PHY_PWD |
			BM_USBPHY_CTRL_ENAUTOCLR_CLKGATE |
			BM_USBPHY_CTRL_ENAUTO_PWRON_PLL;

	ग_लिखोl(value, phy->io_priv + HW_USBPHY_CTRL_CLR);
	ग_लिखोl(0xffffffff, phy->io_priv + HW_USBPHY_PWD);

	ग_लिखोl(BM_USBPHY_CTRL_CLKGATE,
	       phy->io_priv + HW_USBPHY_CTRL_SET);

	अगर (is_imx7ulp_phy(mxs_phy))
		mxs_phy_pll_enable(phy->io_priv, false);

	clk_disable_unprepare(mxs_phy->clk);
पूर्ण

अटल bool mxs_phy_is_low_speed_connection(काष्ठा mxs_phy *mxs_phy)
अणु
	अचिन्हित पूर्णांक line_state;
	/* bit definition is the same क्रम all controllers */
	अचिन्हित पूर्णांक dp_bit = BM_ANADIG_USB1_MISC_RX_VPIN_FS,
		     dm_bit = BM_ANADIG_USB1_MISC_RX_VMIN_FS;
	अचिन्हित पूर्णांक reg = ANADIG_USB1_MISC;

	/* If the SoCs करोn't have anatop, quit */
	अगर (!mxs_phy->regmap_anatop)
		वापस false;

	अगर (mxs_phy->port_id == 0)
		reg = ANADIG_USB1_MISC;
	अन्यथा अगर (mxs_phy->port_id == 1)
		reg = ANADIG_USB2_MISC;

	regmap_पढ़ो(mxs_phy->regmap_anatop, reg, &line_state);

	अगर ((line_state & (dp_bit | dm_bit)) ==  dm_bit)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक mxs_phy_suspend(काष्ठा usb_phy *x, पूर्णांक suspend)
अणु
	पूर्णांक ret;
	काष्ठा mxs_phy *mxs_phy = to_mxs_phy(x);
	bool low_speed_connection, vbus_is_on;

	low_speed_connection = mxs_phy_is_low_speed_connection(mxs_phy);
	vbus_is_on = mxs_phy_get_vbus_status(mxs_phy);

	अगर (suspend) अणु
		/*
		 * FIXME: Do not घातer करोwn RXPWD1PT1 bit क्रम low speed
		 * connect. The low speed connection will have problem at
		 * very rare हालs during usb suspend and resume process.
		 */
		अगर (low_speed_connection & vbus_is_on) अणु
			/*
			 * If value to be set as pwd value is not 0xffffffff,
			 * several 32Khz cycles are needed.
			 */
			mxs_phy_घड़ी_चयन_delay();
			ग_लिखोl(0xffbfffff, x->io_priv + HW_USBPHY_PWD);
		पूर्ण अन्यथा अणु
			ग_लिखोl(0xffffffff, x->io_priv + HW_USBPHY_PWD);
		पूर्ण
		ग_लिखोl(BM_USBPHY_CTRL_CLKGATE,
		       x->io_priv + HW_USBPHY_CTRL_SET);
		clk_disable_unprepare(mxs_phy->clk);
	पूर्ण अन्यथा अणु
		mxs_phy_घड़ी_चयन_delay();
		ret = clk_prepare_enable(mxs_phy->clk);
		अगर (ret)
			वापस ret;
		ग_लिखोl(BM_USBPHY_CTRL_CLKGATE,
		       x->io_priv + HW_USBPHY_CTRL_CLR);
		ग_लिखोl(0, x->io_priv + HW_USBPHY_PWD);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_phy_set_wakeup(काष्ठा usb_phy *x, bool enabled)
अणु
	काष्ठा mxs_phy *mxs_phy = to_mxs_phy(x);
	u32 value = BM_USBPHY_CTRL_ENVBUSCHG_WKUP |
			BM_USBPHY_CTRL_ENDPDMCHG_WKUP |
				BM_USBPHY_CTRL_ENIDCHG_WKUP;
	अगर (enabled) अणु
		mxs_phy_disconnect_line(mxs_phy, true);
		ग_लिखोl_relaxed(value, x->io_priv + HW_USBPHY_CTRL_SET);
	पूर्ण अन्यथा अणु
		ग_लिखोl_relaxed(value, x->io_priv + HW_USBPHY_CTRL_CLR);
		mxs_phy_disconnect_line(mxs_phy, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_phy_on_connect(काष्ठा usb_phy *phy,
		क्रमागत usb_device_speed speed)
अणु
	dev_dbg(phy->dev, "%s device has connected\n",
		(speed == USB_SPEED_HIGH) ? "HS" : "FS/LS");

	अगर (speed == USB_SPEED_HIGH)
		ग_लिखोl(BM_USBPHY_CTRL_ENHOSTDISCONDETECT,
		       phy->io_priv + HW_USBPHY_CTRL_SET);

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_phy_on_disconnect(काष्ठा usb_phy *phy,
		क्रमागत usb_device_speed speed)
अणु
	dev_dbg(phy->dev, "%s device has disconnected\n",
		(speed == USB_SPEED_HIGH) ? "HS" : "FS/LS");

	/* Someबार, the speed is not high speed when the error occurs */
	अगर (पढ़ोl(phy->io_priv + HW_USBPHY_CTRL) &
			BM_USBPHY_CTRL_ENHOSTDISCONDETECT)
		ग_लिखोl(BM_USBPHY_CTRL_ENHOSTDISCONDETECT,
		       phy->io_priv + HW_USBPHY_CTRL_CLR);

	वापस 0;
पूर्ण

#घोषणा MXS_USB_CHARGER_DATA_CONTACT_TIMEOUT	100
अटल पूर्णांक mxs_अक्षरger_data_contact_detect(काष्ठा mxs_phy *x)
अणु
	काष्ठा regmap *regmap = x->regmap_anatop;
	पूर्णांक i, stable_contact_count = 0;
	u32 val;

	/* Check अगर vbus is valid */
	regmap_पढ़ो(regmap, ANADIG_USB1_VBUS_DET_STAT, &val);
	अगर (!(val & ANADIG_USB1_VBUS_DET_STAT_VBUS_VALID)) अणु
		dev_err(x->phy.dev, "vbus is not valid\n");
		वापस -EINVAL;
	पूर्ण

	/* Enable अक्षरger detector */
	regmap_ग_लिखो(regmap, ANADIG_USB1_CHRG_DETECT_CLR,
				ANADIG_USB1_CHRG_DETECT_EN_B);
	/*
	 * - Do not check whether a अक्षरger is connected to the USB port
	 * - Check whether the USB plug has been in contact with each other
	 */
	regmap_ग_लिखो(regmap, ANADIG_USB1_CHRG_DETECT_SET,
			ANADIG_USB1_CHRG_DETECT_CHK_CONTACT |
			ANADIG_USB1_CHRG_DETECT_CHK_CHRG_B);

	/* Check अगर plug is connected */
	क्रम (i = 0; i < MXS_USB_CHARGER_DATA_CONTACT_TIMEOUT; i++) अणु
		regmap_पढ़ो(regmap, ANADIG_USB1_CHRG_DET_STAT, &val);
		अगर (val & ANADIG_USB1_CHRG_DET_STAT_PLUG_CONTACT) अणु
			stable_contact_count++;
			अगर (stable_contact_count > 5)
				/* Data pin makes contact */
				अवरोध;
			अन्यथा
				usleep_range(5000, 10000);
		पूर्ण अन्यथा अणु
			stable_contact_count = 0;
			usleep_range(5000, 6000);
		पूर्ण
	पूर्ण

	अगर (i == MXS_USB_CHARGER_DATA_CONTACT_TIMEOUT) अणु
		dev_err(x->phy.dev,
			"Data pin can't make good contact.\n");
		/* Disable अक्षरger detector */
		regmap_ग_लिखो(regmap, ANADIG_USB1_CHRG_DETECT_SET,
				ANADIG_USB1_CHRG_DETECT_EN_B |
				ANADIG_USB1_CHRG_DETECT_CHK_CHRG_B);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत usb_अक्षरger_type mxs_अक्षरger_primary_detection(काष्ठा mxs_phy *x)
अणु
	काष्ठा regmap *regmap = x->regmap_anatop;
	क्रमागत usb_अक्षरger_type chgr_type = UNKNOWN_TYPE;
	u32 val;

	/*
	 * - Do check whether a अक्षरger is connected to the USB port
	 * - Do not Check whether the USB plug has been in contact with
	 *   each other
	 */
	regmap_ग_लिखो(regmap, ANADIG_USB1_CHRG_DETECT_CLR,
			ANADIG_USB1_CHRG_DETECT_CHK_CONTACT |
			ANADIG_USB1_CHRG_DETECT_CHK_CHRG_B);

	msleep(100);

	/* Check अगर it is a अक्षरger */
	regmap_पढ़ो(regmap, ANADIG_USB1_CHRG_DET_STAT, &val);
	अगर (!(val & ANADIG_USB1_CHRG_DET_STAT_CHRG_DETECTED)) अणु
		chgr_type = SDP_TYPE;
		dev_dbg(x->phy.dev, "It is a standard downstream port\n");
	पूर्ण

	/* Disable अक्षरger detector */
	regmap_ग_लिखो(regmap, ANADIG_USB1_CHRG_DETECT_SET,
			ANADIG_USB1_CHRG_DETECT_EN_B |
			ANADIG_USB1_CHRG_DETECT_CHK_CHRG_B);

	वापस chgr_type;
पूर्ण

/*
 * It must be called after DP is pulled up, which is used to
 * dअगरferentiate DCP and CDP.
 */
अटल क्रमागत usb_अक्षरger_type mxs_अक्षरger_secondary_detection(काष्ठा mxs_phy *x)
अणु
	काष्ठा regmap *regmap = x->regmap_anatop;
	पूर्णांक val;

	msleep(80);

	regmap_पढ़ो(regmap, ANADIG_USB1_CHRG_DET_STAT, &val);
	अगर (val & ANADIG_USB1_CHRG_DET_STAT_DM_STATE) अणु
		dev_dbg(x->phy.dev, "It is a dedicate charging port\n");
		वापस DCP_TYPE;
	पूर्ण अन्यथा अणु
		dev_dbg(x->phy.dev, "It is a charging downstream port\n");
		वापस CDP_TYPE;
	पूर्ण
पूर्ण

अटल क्रमागत usb_अक्षरger_type mxs_phy_अक्षरger_detect(काष्ठा usb_phy *phy)
अणु
	काष्ठा mxs_phy *mxs_phy = to_mxs_phy(phy);
	काष्ठा regmap *regmap = mxs_phy->regmap_anatop;
	व्योम __iomem *base = phy->io_priv;
	क्रमागत usb_अक्षरger_type chgr_type = UNKNOWN_TYPE;

	अगर (!regmap)
		वापस UNKNOWN_TYPE;

	अगर (mxs_अक्षरger_data_contact_detect(mxs_phy))
		वापस chgr_type;

	chgr_type = mxs_अक्षरger_primary_detection(mxs_phy);

	अगर (chgr_type != SDP_TYPE) अणु
		/* Pull up DP via test */
		ग_लिखोl_relaxed(BM_USBPHY_DEBUG_CLKGATE,
				base + HW_USBPHY_DEBUG_CLR);
		regmap_ग_लिखो(regmap, ANADIG_USB1_LOOPBACK_SET,
				ANADIG_USB1_LOOPBACK_UTMI_TESTSTART);

		chgr_type = mxs_अक्षरger_secondary_detection(mxs_phy);

		/* Stop the test */
		regmap_ग_लिखो(regmap, ANADIG_USB1_LOOPBACK_CLR,
				ANADIG_USB1_LOOPBACK_UTMI_TESTSTART);
		ग_लिखोl_relaxed(BM_USBPHY_DEBUG_CLKGATE,
				base + HW_USBPHY_DEBUG_SET);
	पूर्ण

	वापस chgr_type;
पूर्ण

अटल पूर्णांक mxs_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा mxs_phy *mxs_phy;
	पूर्णांक ret;
	काष्ठा device_node *np = pdev->dev.of_node;
	u32 val;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev,
			"can't get the clock, err=%ld", PTR_ERR(clk));
		वापस PTR_ERR(clk);
	पूर्ण

	mxs_phy = devm_kzalloc(&pdev->dev, माप(*mxs_phy), GFP_KERNEL);
	अगर (!mxs_phy)
		वापस -ENOMEM;

	/* Some SoCs करोn't have anatop रेजिस्टरs */
	अगर (of_get_property(np, "fsl,anatop", शून्य)) अणु
		mxs_phy->regmap_anatop = syscon_regmap_lookup_by_phandle
			(np, "fsl,anatop");
		अगर (IS_ERR(mxs_phy->regmap_anatop)) अणु
			dev_dbg(&pdev->dev,
				"failed to find regmap for anatop\n");
			वापस PTR_ERR(mxs_phy->regmap_anatop);
		पूर्ण
	पूर्ण

	/* Precompute which bits of the TX रेजिस्टर are to be updated, अगर any */
	अगर (!of_property_पढ़ो_u32(np, "fsl,tx-cal-45-dn-ohms", &val) &&
	    val >= MXS_PHY_TX_CAL45_MIN && val <= MXS_PHY_TX_CAL45_MAX) अणु
		/* Scale to a 4-bit value */
		val = (MXS_PHY_TX_CAL45_MAX - val) * 0xF
			/ (MXS_PHY_TX_CAL45_MAX - MXS_PHY_TX_CAL45_MIN);
		mxs_phy->tx_reg_mask |= GM_USBPHY_TX_TXCAL45DN(~0);
		mxs_phy->tx_reg_set  |= GM_USBPHY_TX_TXCAL45DN(val);
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "fsl,tx-cal-45-dp-ohms", &val) &&
	    val >= MXS_PHY_TX_CAL45_MIN && val <= MXS_PHY_TX_CAL45_MAX) अणु
		/* Scale to a 4-bit value. */
		val = (MXS_PHY_TX_CAL45_MAX - val) * 0xF
			/ (MXS_PHY_TX_CAL45_MAX - MXS_PHY_TX_CAL45_MIN);
		mxs_phy->tx_reg_mask |= GM_USBPHY_TX_TXCAL45DP(~0);
		mxs_phy->tx_reg_set  |= GM_USBPHY_TX_TXCAL45DP(val);
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "fsl,tx-d-cal", &val) &&
	    val >= MXS_PHY_TX_D_CAL_MIN && val <= MXS_PHY_TX_D_CAL_MAX) अणु
		/* Scale to a 4-bit value.  Round up the values and heavily
		 * weight the rounding by adding 2/3 of the denominator.
		 */
		val = ((MXS_PHY_TX_D_CAL_MAX - val) * 0xF
			+ (MXS_PHY_TX_D_CAL_MAX - MXS_PHY_TX_D_CAL_MIN) * 2/3)
			/ (MXS_PHY_TX_D_CAL_MAX - MXS_PHY_TX_D_CAL_MIN);
		mxs_phy->tx_reg_mask |= GM_USBPHY_TX_D_CAL(~0);
		mxs_phy->tx_reg_set  |= GM_USBPHY_TX_D_CAL(val);
	पूर्ण

	ret = of_alias_get_id(np, "usbphy");
	अगर (ret < 0)
		dev_dbg(&pdev->dev, "failed to get alias id, errno %d\n", ret);
	mxs_phy->port_id = ret;

	mxs_phy->phy.io_priv		= base;
	mxs_phy->phy.dev		= &pdev->dev;
	mxs_phy->phy.label		= DRIVER_NAME;
	mxs_phy->phy.init		= mxs_phy_init;
	mxs_phy->phy.shutकरोwn		= mxs_phy_shutकरोwn;
	mxs_phy->phy.set_suspend	= mxs_phy_suspend;
	mxs_phy->phy.notअगरy_connect	= mxs_phy_on_connect;
	mxs_phy->phy.notअगरy_disconnect	= mxs_phy_on_disconnect;
	mxs_phy->phy.type		= USB_PHY_TYPE_USB2;
	mxs_phy->phy.set_wakeup		= mxs_phy_set_wakeup;
	mxs_phy->phy.अक्षरger_detect	= mxs_phy_अक्षरger_detect;

	mxs_phy->clk = clk;
	mxs_phy->data = of_device_get_match_data(&pdev->dev);

	platक्रमm_set_drvdata(pdev, mxs_phy);

	device_set_wakeup_capable(&pdev->dev, true);

	वापस usb_add_phy_dev(&mxs_phy->phy);
पूर्ण

अटल पूर्णांक mxs_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mxs_phy *mxs_phy = platक्रमm_get_drvdata(pdev);

	usb_हटाओ_phy(&mxs_phy->phy);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम mxs_phy_enable_lकरो_in_suspend(काष्ठा mxs_phy *mxs_phy, bool on)
अणु
	अचिन्हित पूर्णांक reg = on ? ANADIG_ANA_MISC0_SET : ANADIG_ANA_MISC0_CLR;

	/* If the SoCs करोn't have anatop, quit */
	अगर (!mxs_phy->regmap_anatop)
		वापस;

	अगर (is_imx6q_phy(mxs_phy))
		regmap_ग_लिखो(mxs_phy->regmap_anatop, reg,
			BM_ANADIG_ANA_MISC0_STOP_MODE_CONFIG);
	अन्यथा अगर (is_imx6sl_phy(mxs_phy))
		regmap_ग_लिखो(mxs_phy->regmap_anatop,
			reg, BM_ANADIG_ANA_MISC0_STOP_MODE_CONFIG_SL);
पूर्ण

अटल पूर्णांक mxs_phy_प्रणाली_suspend(काष्ठा device *dev)
अणु
	काष्ठा mxs_phy *mxs_phy = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		mxs_phy_enable_lकरो_in_suspend(mxs_phy, true);

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_phy_प्रणाली_resume(काष्ठा device *dev)
अणु
	काष्ठा mxs_phy *mxs_phy = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		mxs_phy_enable_lकरो_in_suspend(mxs_phy, false);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(mxs_phy_pm, mxs_phy_प्रणाली_suspend,
		mxs_phy_प्रणाली_resume);

अटल काष्ठा platक्रमm_driver mxs_phy_driver = अणु
	.probe = mxs_phy_probe,
	.हटाओ = mxs_phy_हटाओ,
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = mxs_phy_dt_ids,
		.pm = &mxs_phy_pm,
	 पूर्ण,
पूर्ण;

अटल पूर्णांक __init mxs_phy_module_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mxs_phy_driver);
पूर्ण
postcore_initcall(mxs_phy_module_init);

अटल व्योम __निकास mxs_phy_module_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mxs_phy_driver);
पूर्ण
module_निकास(mxs_phy_module_निकास);

MODULE_ALIAS("platform:mxs-usb-phy");
MODULE_AUTHOR("Marek Vasut <marex@denx.de>");
MODULE_AUTHOR("Richard Zhao <richard.zhao@freescale.com>");
MODULE_DESCRIPTION("Freescale MXS USB PHY driver");
MODULE_LICENSE("GPL");
