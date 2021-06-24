<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Phy provider क्रम USB 3.1 controller on HiSilicon Kirin970 platक्रमm
 *
 * Copyright (C) 2017-2020 Hilisicon Electronics Co., Ltd.
 *		http://www.huawei.com
 *
 * Authors: Yu Chen <chenyu56@huawei.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा SCTRL_SCDEEPSLEEPED		(0x0)
#घोषणा USB_CLK_SELECTED		BIT(20)

#घोषणा PERI_CRG_PEREN0			(0x00)
#घोषणा PERI_CRG_PERDIS0		(0x04)
#घोषणा PERI_CRG_PEREN4			(0x40)
#घोषणा PERI_CRG_PERDIS4		(0x44)
#घोषणा PERI_CRG_PERRSTEN4		(0x90)
#घोषणा PERI_CRG_PERRSTDIS4		(0x94)
#घोषणा PERI_CRG_ISODIS			(0x148)
#घोषणा PERI_CRG_PEREN6			(0x410)
#घोषणा PERI_CRG_PERDIS6		(0x414)

#घोषणा USB_REFCLK_ISO_EN		BIT(25)

#घोषणा GT_CLK_USB2PHY_REF		BIT(19)

#घोषणा PCTRL_PERI_CTRL3		(0x10)
#घोषणा PCTRL_PERI_CTRL3_MSK_START	(16)
#घोषणा USB_TCXO_EN			BIT(1)

#घोषणा PCTRL_PERI_CTRL24		(0x64)
#घोषणा SC_CLK_USB3PHY_3MUX1_SEL	BIT(25)

#घोषणा USB3OTG_CTRL0			(0x00)
#घोषणा USB3OTG_CTRL3			(0x0c)
#घोषणा USB3OTG_CTRL4			(0x10)
#घोषणा USB3OTG_CTRL5			(0x14)
#घोषणा USB3OTG_CTRL7			(0x1c)
#घोषणा USB_MISC_CFG50			(0x50)
#घोषणा USB_MISC_CFG54			(0x54)
#घोषणा USB_MISC_CFG58			(0x58)
#घोषणा USB_MISC_CFG5C			(0x5c)
#घोषणा USB_MISC_CFGA0			(0xa0)
#घोषणा TCA_CLK_RST			(0x200)
#घोषणा TCA_INTR_EN			(0x204)
#घोषणा TCA_INTR_STS			(0x208)
#घोषणा TCA_GCFG			(0x210)
#घोषणा TCA_TCPC			(0x214)
#घोषणा TCA_SYSMODE_CFG			(0x218)
#घोषणा TCA_VBUS_CTRL			(0x240)

#घोषणा CTRL0_USB3_VBUSVLD		BIT(7)
#घोषणा CTRL0_USB3_VBUSVLD_SEL		BIT(6)

#घोषणा CTRL3_USB2_VBUSVLDEXT0		BIT(6)
#घोषणा CTRL3_USB2_VBUSVLDEXTSEL0	BIT(5)

#घोषणा CTRL5_USB2_SIDDQ		BIT(0)

#घोषणा CTRL7_USB2_REFCLKSEL_MASK	GENMASK(4, 3)
#घोषणा CTRL7_USB2_REFCLKSEL_ABB	(BIT(4) | BIT(3))
#घोषणा CTRL7_USB2_REFCLKSEL_PAD	BIT(4)

#घोषणा CFG50_USB3_PHY_TEST_POWERDOWN	BIT(23)

#घोषणा CFG54_USB31PHY_CR_ADDR_MASK	GENMASK(31, 16)

#घोषणा CFG54_USB3PHY_REF_USE_PAD	BIT(12)
#घोषणा CFG54_PHY0_PMA_PWR_STABLE	BIT(11)
#घोषणा CFG54_PHY0_PCS_PWR_STABLE	BIT(9)
#घोषणा CFG54_USB31PHY_CR_ACK		BIT(7)
#घोषणा CFG54_USB31PHY_CR_WR_EN		BIT(5)
#घोषणा CFG54_USB31PHY_CR_SEL		BIT(4)
#घोषणा CFG54_USB31PHY_CR_RD_EN		BIT(3)
#घोषणा CFG54_USB31PHY_CR_CLK		BIT(2)
#घोषणा CFG54_USB3_PHY0_ANA_PWR_EN	BIT(1)

#घोषणा CFG58_USB31PHY_CR_DATA_MASK     GENMASK(31, 16)

#घोषणा CFG5C_USB3_PHY0_SS_MPLLA_SSC_EN	BIT(1)

#घोषणा CFGA0_VAUX_RESET		BIT(9)
#घोषणा CFGA0_USB31C_RESET		BIT(8)
#घोषणा CFGA0_USB2PHY_REFCLK_SELECT	BIT(4)
#घोषणा CFGA0_USB3PHY_RESET		BIT(1)
#घोषणा CFGA0_USB2PHY_POR		BIT(0)

#घोषणा INTR_EN_XA_TIMEOUT_EVT_EN	BIT(1)
#घोषणा INTR_EN_XA_ACK_EVT_EN		BIT(0)

#घोषणा CLK_RST_TCA_REF_CLK_EN		BIT(1)
#घोषणा CLK_RST_SUSPEND_CLK_EN		BIT(0)

#घोषणा GCFG_ROLE_HSTDEV		BIT(4)
#घोषणा GCFG_OP_MODE			GENMASK(1, 0)
#घोषणा GCFG_OP_MODE_CTRL_SYNC_MODE	BIT(0)

#घोषणा TCPC_VALID			BIT(4)
#घोषणा TCPC_LOW_POWER_EN		BIT(3)
#घोषणा TCPC_MUX_CONTROL_MASK		GENMASK(1, 0)
#घोषणा TCPC_MUX_CONTROL_USB31		BIT(0)

#घोषणा SYSMODE_CFG_TYPEC_DISABLE	BIT(3)

#घोषणा VBUS_CTRL_POWERPRESENT_OVERRD	GENMASK(3, 2)
#घोषणा VBUS_CTRL_VBUSVALID_OVERRD	GENMASK(1, 0)

#घोषणा KIRIN970_USB_DEFAULT_PHY_PARAM	(0xfdfee4)
#घोषणा KIRIN970_USB_DEFAULT_PHY_VBOOST	(0x5)

#घोषणा TX_VBOOST_LVL_REG		(0xf)
#घोषणा TX_VBOOST_LVL_START		(6)
#घोषणा TX_VBOOST_LVL_ENABLE		BIT(9)

काष्ठा hi3670_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *peri_crg;
	काष्ठा regmap *pctrl;
	काष्ठा regmap *sctrl;
	काष्ठा regmap *usb31misc;

	u32 eye_diagram_param;
	u32 tx_vboost_lvl;

	u32 peri_crg_offset;
	u32 pctrl_offset;
	u32 usb31misc_offset;
पूर्ण;

अटल पूर्णांक hi3670_phy_cr_clk(काष्ठा regmap *usb31misc)
अणु
	पूर्णांक ret;

	/* Clock up */
	ret = regmap_update_bits(usb31misc, USB_MISC_CFG54,
				 CFG54_USB31PHY_CR_CLK, CFG54_USB31PHY_CR_CLK);
	अगर (ret)
		वापस ret;

	/* Clock करोwn */
	ret = regmap_update_bits(usb31misc, USB_MISC_CFG54,
				 CFG54_USB31PHY_CR_CLK, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक hi3670_phy_cr_set_sel(काष्ठा regmap *usb31misc)
अणु
	वापस regmap_update_bits(usb31misc, USB_MISC_CFG54,
				  CFG54_USB31PHY_CR_SEL, CFG54_USB31PHY_CR_SEL);
पूर्ण

अटल पूर्णांक hi3670_phy_cr_start(काष्ठा regmap *usb31misc, पूर्णांक direction)
अणु
	पूर्णांक ret, reg;

	अगर (direction)
		reg = CFG54_USB31PHY_CR_WR_EN;
	अन्यथा
		reg = CFG54_USB31PHY_CR_RD_EN;

	ret = regmap_update_bits(usb31misc, USB_MISC_CFG54, reg, reg);

	अगर (ret)
		वापस ret;

	ret = hi3670_phy_cr_clk(usb31misc);
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(usb31misc, USB_MISC_CFG54,
				  CFG54_USB31PHY_CR_RD_EN | CFG54_USB31PHY_CR_WR_EN, 0);
पूर्ण

अटल पूर्णांक hi3670_phy_cr_रुको_ack(काष्ठा regmap *usb31misc)
अणु
	u32 reg;
	पूर्णांक retry = 10;
	पूर्णांक ret;

	जबतक (retry-- > 0) अणु
		ret = regmap_पढ़ो(usb31misc, USB_MISC_CFG54, &reg);
		अगर (ret)
			वापस ret;
		अगर ((reg & CFG54_USB31PHY_CR_ACK) == CFG54_USB31PHY_CR_ACK)
			वापस 0;

		ret = hi3670_phy_cr_clk(usb31misc);
		अगर (ret)
			वापस ret;

		usleep_range(10, 20);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक hi3670_phy_cr_set_addr(काष्ठा regmap *usb31misc, u32 addr)
अणु
	u32 reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(usb31misc, USB_MISC_CFG54, &reg);
	अगर (ret)
		वापस ret;

	reg = FIELD_PREP(CFG54_USB31PHY_CR_ADDR_MASK, addr);
	ret = regmap_update_bits(usb31misc, USB_MISC_CFG54,
				 CFG54_USB31PHY_CR_ADDR_MASK, reg);

	वापस ret;
पूर्ण

अटल पूर्णांक hi3670_phy_cr_पढ़ो(काष्ठा regmap *usb31misc, u32 addr, u32 *val)
अणु
	पूर्णांक reg;
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < 100; i++) अणु
		ret = hi3670_phy_cr_clk(usb31misc);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = hi3670_phy_cr_set_sel(usb31misc);
	अगर (ret)
		वापस ret;

	ret = hi3670_phy_cr_set_addr(usb31misc, addr);
	अगर (ret)
		वापस ret;

	ret = hi3670_phy_cr_start(usb31misc, 0);
	अगर (ret)
		वापस ret;

	ret = hi3670_phy_cr_रुको_ack(usb31misc);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(usb31misc, USB_MISC_CFG58, &reg);
	अगर (ret)
		वापस ret;

	*val = FIELD_GET(CFG58_USB31PHY_CR_DATA_MASK, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक hi3670_phy_cr_ग_लिखो(काष्ठा regmap *usb31misc, u32 addr, u32 val)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < 100; i++) अणु
		ret = hi3670_phy_cr_clk(usb31misc);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = hi3670_phy_cr_set_sel(usb31misc);
	अगर (ret)
		वापस ret;

	ret = hi3670_phy_cr_set_addr(usb31misc, addr);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(usb31misc, USB_MISC_CFG58,
			   FIELD_PREP(CFG58_USB31PHY_CR_DATA_MASK, val));
	अगर (ret)
		वापस ret;

	ret = hi3670_phy_cr_start(usb31misc, 1);
	अगर (ret)
		वापस ret;

	ret = hi3670_phy_cr_रुको_ack(usb31misc);

	वापस ret;
पूर्ण

अटल पूर्णांक hi3670_phy_set_params(काष्ठा hi3670_priv *priv)
अणु
	u32 reg;
	पूर्णांक ret;
	पूर्णांक retry = 3;

	ret = regmap_ग_लिखो(priv->usb31misc, USB3OTG_CTRL4,
			   priv->eye_diagram_param);
	अगर (ret) अणु
		dev_err(priv->dev, "set USB3OTG_CTRL4 failed\n");
		वापस ret;
	पूर्ण

	जबतक (retry-- > 0) अणु
		ret = hi3670_phy_cr_पढ़ो(priv->usb31misc,
					 TX_VBOOST_LVL_REG, &reg);
		अगर (!ret)
			अवरोध;

		अगर (ret != -ETIMEDOUT) अणु
			dev_err(priv->dev, "read TX_VBOOST_LVL_REG failed\n");
			वापस ret;
		पूर्ण
	पूर्ण
	अगर (ret)
		वापस ret;

	reg |= (TX_VBOOST_LVL_ENABLE | (priv->tx_vboost_lvl << TX_VBOOST_LVL_START));
	ret = hi3670_phy_cr_ग_लिखो(priv->usb31misc, TX_VBOOST_LVL_REG, reg);
	अगर (ret)
		dev_err(priv->dev, "write TX_VBOOST_LVL_REG failed\n");

	वापस ret;
पूर्ण

अटल bool hi3670_is_abbclk_selected(काष्ठा hi3670_priv *priv)
अणु
	u32 reg;

	अगर (!priv->sctrl) अणु
		dev_err(priv->dev, "priv->sctrl is null!\n");
		वापस false;
	पूर्ण

	अगर (regmap_पढ़ो(priv->sctrl, SCTRL_SCDEEPSLEEPED, &reg)) अणु
		dev_err(priv->dev, "SCTRL_SCDEEPSLEEPED read failed!\n");
		वापस false;
	पूर्ण

	अगर ((reg & USB_CLK_SELECTED) == 0)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक hi3670_config_phy_घड़ी(काष्ठा hi3670_priv *priv)
अणु
	u32 val, mask;
	पूर्णांक ret;

	अगर (!hi3670_is_abbclk_selected(priv)) अणु
		/* usb refclk iso disable */
		ret = regmap_ग_लिखो(priv->peri_crg, PERI_CRG_ISODIS,
				   USB_REFCLK_ISO_EN);
		अगर (ret)
			जाओ out;

		/* enable usb_tcxo_en */
		ret = regmap_ग_लिखो(priv->pctrl, PCTRL_PERI_CTRL3,
				   USB_TCXO_EN |
				   (USB_TCXO_EN << PCTRL_PERI_CTRL3_MSK_START));

		/* select usbphy clk from abb */
		mask = SC_CLK_USB3PHY_3MUX1_SEL;
		ret = regmap_update_bits(priv->pctrl,
					 PCTRL_PERI_CTRL24, mask, 0);
		अगर (ret)
			जाओ out;

		ret = regmap_update_bits(priv->usb31misc, USB_MISC_CFGA0,
					 CFGA0_USB2PHY_REFCLK_SELECT, 0);
		अगर (ret)
			जाओ out;

		ret = regmap_पढ़ो(priv->usb31misc, USB3OTG_CTRL7, &val);
		अगर (ret)
			जाओ out;
		val &= ~CTRL7_USB2_REFCLKSEL_MASK;
		val |= CTRL7_USB2_REFCLKSEL_ABB;
		ret = regmap_ग_लिखो(priv->usb31misc, USB3OTG_CTRL7, val);
		अगर (ret)
			जाओ out;

		वापस 0;
	पूर्ण

	ret = regmap_update_bits(priv->usb31misc, USB_MISC_CFG54,
				 CFG54_USB3PHY_REF_USE_PAD,
				 CFG54_USB3PHY_REF_USE_PAD);
	अगर (ret)
		जाओ out;

	ret = regmap_update_bits(priv->usb31misc, USB_MISC_CFGA0,
				 CFGA0_USB2PHY_REFCLK_SELECT,
				 CFGA0_USB2PHY_REFCLK_SELECT);
	अगर (ret)
		जाओ out;

	ret = regmap_पढ़ो(priv->usb31misc, USB3OTG_CTRL7, &val);
	अगर (ret)
		जाओ out;
	val &= ~CTRL7_USB2_REFCLKSEL_MASK;
	val |= CTRL7_USB2_REFCLKSEL_PAD;
	ret = regmap_ग_लिखो(priv->usb31misc, USB3OTG_CTRL7, val);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(priv->peri_crg,
			   PERI_CRG_PEREN6, GT_CLK_USB2PHY_REF);
	अगर (ret)
		जाओ out;

	वापस 0;
out:
	dev_err(priv->dev, "failed to config phy clock ret: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hi3670_config_tca(काष्ठा hi3670_priv *priv)
अणु
	u32 val, mask;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(priv->usb31misc, TCA_INTR_STS, 0xffff);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(priv->usb31misc, TCA_INTR_EN,
			   INTR_EN_XA_TIMEOUT_EVT_EN | INTR_EN_XA_ACK_EVT_EN);
	अगर (ret)
		जाओ out;

	mask = CLK_RST_TCA_REF_CLK_EN | CLK_RST_SUSPEND_CLK_EN;
	ret = regmap_update_bits(priv->usb31misc, TCA_CLK_RST, mask, 0);
	अगर (ret)
		जाओ out;

	ret = regmap_update_bits(priv->usb31misc, TCA_GCFG,
				 GCFG_ROLE_HSTDEV | GCFG_OP_MODE,
				 GCFG_ROLE_HSTDEV | GCFG_OP_MODE_CTRL_SYNC_MODE);
	अगर (ret)
		जाओ out;

	ret = regmap_update_bits(priv->usb31misc, TCA_SYSMODE_CFG,
				 SYSMODE_CFG_TYPEC_DISABLE, 0);
	अगर (ret)
		जाओ out;

	ret = regmap_पढ़ो(priv->usb31misc, TCA_TCPC, &val);
	अगर (ret)
		जाओ out;
	val &= ~(TCPC_VALID | TCPC_LOW_POWER_EN | TCPC_MUX_CONTROL_MASK);
	val |= (TCPC_VALID | TCPC_MUX_CONTROL_USB31);
	ret = regmap_ग_लिखो(priv->usb31misc, TCA_TCPC, val);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(priv->usb31misc, TCA_VBUS_CTRL,
			   VBUS_CTRL_POWERPRESENT_OVERRD | VBUS_CTRL_VBUSVALID_OVERRD);
	अगर (ret)
		जाओ out;

	वापस 0;
out:
	dev_err(priv->dev, "failed to config phy clock ret: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hi3670_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा hi3670_priv *priv = phy_get_drvdata(phy);
	u32 val;
	पूर्णांक ret;

	/* निश्चित controller */
	val = CFGA0_VAUX_RESET | CFGA0_USB31C_RESET |
	      CFGA0_USB3PHY_RESET | CFGA0_USB2PHY_POR;
	ret = regmap_update_bits(priv->usb31misc, USB_MISC_CFGA0, val, 0);
	अगर (ret)
		जाओ out;

	ret = hi3670_config_phy_घड़ी(priv);
	अगर (ret)
		जाओ out;

	/* Exit from IDDQ mode */
	ret = regmap_update_bits(priv->usb31misc, USB3OTG_CTRL5,
				 CTRL5_USB2_SIDDQ, 0);
	अगर (ret)
		जाओ out;

	/* Release USB31 PHY out of TestPowerDown mode */
	ret = regmap_update_bits(priv->usb31misc, USB_MISC_CFG50,
				 CFG50_USB3_PHY_TEST_POWERDOWN, 0);
	अगर (ret)
		जाओ out;

	/* Deनिश्चित phy */
	val = CFGA0_USB3PHY_RESET | CFGA0_USB2PHY_POR;
	ret = regmap_update_bits(priv->usb31misc, USB_MISC_CFGA0, val, val);
	अगर (ret)
		जाओ out;

	usleep_range(100, 120);

	/* Tell the PHY घातer is stable */
	val = CFG54_USB3_PHY0_ANA_PWR_EN | CFG54_PHY0_PCS_PWR_STABLE |
	      CFG54_PHY0_PMA_PWR_STABLE;
	ret = regmap_update_bits(priv->usb31misc, USB_MISC_CFG54,
				 val, val);
	अगर (ret)
		जाओ out;

	ret = hi3670_config_tca(priv);
	अगर (ret)
		जाओ out;

	/* Enable SSC */
	ret = regmap_update_bits(priv->usb31misc, USB_MISC_CFG5C,
				 CFG5C_USB3_PHY0_SS_MPLLA_SSC_EN,
				 CFG5C_USB3_PHY0_SS_MPLLA_SSC_EN);
	अगर (ret)
		जाओ out;

	/* Deनिश्चित controller */
	val = CFGA0_VAUX_RESET | CFGA0_USB31C_RESET;
	ret = regmap_update_bits(priv->usb31misc, USB_MISC_CFGA0, val, val);
	अगर (ret)
		जाओ out;

	usleep_range(100, 120);

	/* Set fake vbus valid संकेत */
	val = CTRL0_USB3_VBUSVLD | CTRL0_USB3_VBUSVLD_SEL;
	ret = regmap_update_bits(priv->usb31misc, USB3OTG_CTRL0, val, val);
	अगर (ret)
		जाओ out;

	val = CTRL3_USB2_VBUSVLDEXT0 | CTRL3_USB2_VBUSVLDEXTSEL0;
	ret = regmap_update_bits(priv->usb31misc, USB3OTG_CTRL3, val, val);
	अगर (ret)
		जाओ out;

	usleep_range(100, 120);

	ret = hi3670_phy_set_params(priv);
	अगर (ret)
		जाओ out;

	वापस 0;
out:
	dev_err(priv->dev, "failed to init phy ret: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hi3670_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा hi3670_priv *priv = phy_get_drvdata(phy);
	u32 mask;
	पूर्णांक ret;

	/* Assert phy */
	mask = CFGA0_USB3PHY_RESET | CFGA0_USB2PHY_POR;
	ret = regmap_update_bits(priv->usb31misc, USB_MISC_CFGA0, mask, 0);
	अगर (ret)
		जाओ out;

	अगर (!hi3670_is_abbclk_selected(priv)) अणु
		/* disable usb_tcxo_en */
		ret = regmap_ग_लिखो(priv->pctrl, PCTRL_PERI_CTRL3,
				   USB_TCXO_EN << PCTRL_PERI_CTRL3_MSK_START);
	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(priv->peri_crg, PERI_CRG_PERDIS6,
				   GT_CLK_USB2PHY_REF);
		अगर (ret)
			जाओ out;
	पूर्ण

	वापस 0;
out:
	dev_err(priv->dev, "failed to exit phy ret: %d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा phy_ops hi3670_phy_ops = अणु
	.init		= hi3670_phy_init,
	.निकास		= hi3670_phy_निकास,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक hi3670_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy *phy;
	काष्ठा hi3670_priv *priv;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->peri_crg = syscon_regmap_lookup_by_phandle(dev->of_node,
							 "hisilicon,pericrg-syscon");
	अगर (IS_ERR(priv->peri_crg)) अणु
		dev_err(dev, "no hisilicon,pericrg-syscon\n");
		वापस PTR_ERR(priv->peri_crg);
	पूर्ण

	priv->pctrl = syscon_regmap_lookup_by_phandle(dev->of_node,
						      "hisilicon,pctrl-syscon");
	अगर (IS_ERR(priv->pctrl)) अणु
		dev_err(dev, "no hisilicon,pctrl-syscon\n");
		वापस PTR_ERR(priv->pctrl);
	पूर्ण

	priv->sctrl = syscon_regmap_lookup_by_phandle(dev->of_node,
						      "hisilicon,sctrl-syscon");
	अगर (IS_ERR(priv->sctrl)) अणु
		dev_err(dev, "no hisilicon,sctrl-syscon\n");
		वापस PTR_ERR(priv->sctrl);
	पूर्ण

	/* node of hi3670 phy is a sub-node of usb3_otg_bc */
	priv->usb31misc = syscon_node_to_regmap(dev->parent->of_node);
	अगर (IS_ERR(priv->usb31misc)) अणु
		dev_err(dev, "no hisilicon,usb3-otg-bc-syscon\n");
		वापस PTR_ERR(priv->usb31misc);
	पूर्ण

	अगर (of_property_पढ़ो_u32(dev->of_node, "hisilicon,eye-diagram-param",
				 &priv->eye_diagram_param))
		priv->eye_diagram_param = KIRIN970_USB_DEFAULT_PHY_PARAM;

	अगर (of_property_पढ़ो_u32(dev->of_node, "hisilicon,tx-vboost-lvl",
				 &priv->tx_vboost_lvl))
		priv->tx_vboost_lvl = KIRIN970_USB_DEFAULT_PHY_VBOOST;

	phy = devm_phy_create(dev, शून्य, &hi3670_phy_ops);
	अगर (IS_ERR(phy))
		वापस PTR_ERR(phy);

	phy_set_drvdata(phy, priv);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id hi3670_phy_of_match[] = अणु
	अणु .compatible = "hisilicon,hi3670-usb-phy" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hi3670_phy_of_match);

अटल काष्ठा platक्रमm_driver hi3670_phy_driver = अणु
	.probe	= hi3670_phy_probe,
	.driver = अणु
		.name	= "hi3670-usb-phy",
		.of_match_table	= hi3670_phy_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(hi3670_phy_driver);

MODULE_AUTHOR("Yu Chen <chenyu56@huawei.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Hilisicon Kirin970 USB31 PHY Driver");
