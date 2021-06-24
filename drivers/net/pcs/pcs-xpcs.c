<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020 Synopsys, Inc. and/or its affiliates.
 * Synopsys DesignWare XPCS helpers
 *
 * Author: Jose Abreu <Jose.Abreu@synopsys.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/pcs/pcs-xpcs.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/phylink.h>
#समावेश <linux/workqueue.h>

#घोषणा SYNOPSYS_XPCS_USXGMII_ID	0x7996ced0
#घोषणा SYNOPSYS_XPCS_10GKR_ID		0x7996ced0
#घोषणा SYNOPSYS_XPCS_XLGMII_ID		0x7996ced0
#घोषणा SYNOPSYS_XPCS_SGMII_ID		0x7996ced0
#घोषणा SYNOPSYS_XPCS_MASK		0xffffffff

/* Venकरोr regs access */
#घोषणा DW_VENDOR			BIT(15)

/* VR_XS_PCS */
#घोषणा DW_USXGMII_RST			BIT(10)
#घोषणा DW_USXGMII_EN			BIT(9)
#घोषणा DW_VR_XS_PCS_DIG_STS		0x0010
#घोषणा DW_RXFIFO_ERR			GENMASK(6, 5)

/* SR_MII */
#घोषणा DW_USXGMII_FULL			BIT(8)
#घोषणा DW_USXGMII_SS_MASK		(BIT(13) | BIT(6) | BIT(5))
#घोषणा DW_USXGMII_10000		(BIT(13) | BIT(6))
#घोषणा DW_USXGMII_5000			(BIT(13) | BIT(5))
#घोषणा DW_USXGMII_2500			(BIT(5))
#घोषणा DW_USXGMII_1000			(BIT(6))
#घोषणा DW_USXGMII_100			(BIT(13))
#घोषणा DW_USXGMII_10			(0)

/* SR_AN */
#घोषणा DW_SR_AN_ADV1			0x10
#घोषणा DW_SR_AN_ADV2			0x11
#घोषणा DW_SR_AN_ADV3			0x12
#घोषणा DW_SR_AN_LP_ABL1		0x13
#घोषणा DW_SR_AN_LP_ABL2		0x14
#घोषणा DW_SR_AN_LP_ABL3		0x15

/* Clause 73 Defines */
/* AN_LP_ABL1 */
#घोषणा DW_C73_PAUSE			BIT(10)
#घोषणा DW_C73_ASYM_PAUSE		BIT(11)
#घोषणा DW_C73_AN_ADV_SF		0x1
/* AN_LP_ABL2 */
#घोषणा DW_C73_1000KX			BIT(5)
#घोषणा DW_C73_10000KX4			BIT(6)
#घोषणा DW_C73_10000KR			BIT(7)
/* AN_LP_ABL3 */
#घोषणा DW_C73_2500KX			BIT(0)
#घोषणा DW_C73_5000KR			BIT(1)

/* Clause 37 Defines */
/* VR MII MMD रेजिस्टरs offsets */
#घोषणा DW_VR_MII_DIG_CTRL1		0x8000
#घोषणा DW_VR_MII_AN_CTRL		0x8001
#घोषणा DW_VR_MII_AN_INTR_STS		0x8002

/* VR_MII_DIG_CTRL1 */
#घोषणा DW_VR_MII_DIG_CTRL1_MAC_AUTO_SW		BIT(9)

/* VR_MII_AN_CTRL */
#घोषणा DW_VR_MII_AN_CTRL_TX_CONFIG_SHIFT	3
#घोषणा DW_VR_MII_TX_CONFIG_MASK		BIT(3)
#घोषणा DW_VR_MII_TX_CONFIG_PHY_SIDE_SGMII	0x1
#घोषणा DW_VR_MII_TX_CONFIG_MAC_SIDE_SGMII	0x0
#घोषणा DW_VR_MII_AN_CTRL_PCS_MODE_SHIFT	1
#घोषणा DW_VR_MII_PCS_MODE_MASK			GENMASK(2, 1)
#घोषणा DW_VR_MII_PCS_MODE_C37_1000BASEX	0x0
#घोषणा DW_VR_MII_PCS_MODE_C37_SGMII		0x2

/* VR_MII_AN_INTR_STS */
#घोषणा DW_VR_MII_AN_STS_C37_ANSGM_FD		BIT(1)
#घोषणा DW_VR_MII_AN_STS_C37_ANSGM_SP_SHIFT	2
#घोषणा DW_VR_MII_AN_STS_C37_ANSGM_SP		GENMASK(3, 2)
#घोषणा DW_VR_MII_C37_ANSGM_SP_10		0x0
#घोषणा DW_VR_MII_C37_ANSGM_SP_100		0x1
#घोषणा DW_VR_MII_C37_ANSGM_SP_1000		0x2
#घोषणा DW_VR_MII_C37_ANSGM_SP_LNKSTS		BIT(4)

अटल स्थिर पूर्णांक xpcs_usxgmii_features[] = अणु
	ETHTOOL_LINK_MODE_Pause_BIT,
	ETHTOOL_LINK_MODE_Asym_Pause_BIT,
	ETHTOOL_LINK_MODE_Autoneg_BIT,
	ETHTOOL_LINK_MODE_1000baseKX_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
	ETHTOOL_LINK_MODE_2500baseX_Full_BIT,
	__ETHTOOL_LINK_MODE_MASK_NBITS,
पूर्ण;

अटल स्थिर पूर्णांक xpcs_10gkr_features[] = अणु
	ETHTOOL_LINK_MODE_Pause_BIT,
	ETHTOOL_LINK_MODE_Asym_Pause_BIT,
	ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
	__ETHTOOL_LINK_MODE_MASK_NBITS,
पूर्ण;

अटल स्थिर पूर्णांक xpcs_xlgmii_features[] = अणु
	ETHTOOL_LINK_MODE_Pause_BIT,
	ETHTOOL_LINK_MODE_Asym_Pause_BIT,
	ETHTOOL_LINK_MODE_25000baseCR_Full_BIT,
	ETHTOOL_LINK_MODE_25000baseKR_Full_BIT,
	ETHTOOL_LINK_MODE_25000baseSR_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseKR_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseSR_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseCR_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseLR_ER_FR_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseDR_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseKR2_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseSR2_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseCR2_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseLR2_ER2_FR2_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseDR2_Full_BIT,
	__ETHTOOL_LINK_MODE_MASK_NBITS,
पूर्ण;

अटल स्थिर पूर्णांक xpcs_sgmii_features[] = अणु
	ETHTOOL_LINK_MODE_10baseT_Half_BIT,
	ETHTOOL_LINK_MODE_10baseT_Full_BIT,
	ETHTOOL_LINK_MODE_100baseT_Half_BIT,
	ETHTOOL_LINK_MODE_100baseT_Full_BIT,
	ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
	ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
	__ETHTOOL_LINK_MODE_MASK_NBITS,
पूर्ण;

अटल स्थिर phy_पूर्णांकerface_t xpcs_usxgmii_पूर्णांकerfaces[] = अणु
	PHY_INTERFACE_MODE_USXGMII,
	PHY_INTERFACE_MODE_MAX,
पूर्ण;

अटल स्थिर phy_पूर्णांकerface_t xpcs_10gkr_पूर्णांकerfaces[] = अणु
	PHY_INTERFACE_MODE_10GKR,
	PHY_INTERFACE_MODE_MAX,
पूर्ण;

अटल स्थिर phy_पूर्णांकerface_t xpcs_xlgmii_पूर्णांकerfaces[] = अणु
	PHY_INTERFACE_MODE_XLGMII,
	PHY_INTERFACE_MODE_MAX,
पूर्ण;

अटल स्थिर phy_पूर्णांकerface_t xpcs_sgmii_पूर्णांकerfaces[] = अणु
	PHY_INTERFACE_MODE_SGMII,
	PHY_INTERFACE_MODE_MAX,
पूर्ण;

अटल काष्ठा xpcs_id अणु
	u32 id;
	u32 mask;
	स्थिर पूर्णांक *supported;
	स्थिर phy_पूर्णांकerface_t *पूर्णांकerface;
	पूर्णांक an_mode;
पूर्ण xpcs_id_list[] = अणु
	अणु
		.id = SYNOPSYS_XPCS_USXGMII_ID,
		.mask = SYNOPSYS_XPCS_MASK,
		.supported = xpcs_usxgmii_features,
		.पूर्णांकerface = xpcs_usxgmii_पूर्णांकerfaces,
		.an_mode = DW_AN_C73,
	पूर्ण, अणु
		.id = SYNOPSYS_XPCS_10GKR_ID,
		.mask = SYNOPSYS_XPCS_MASK,
		.supported = xpcs_10gkr_features,
		.पूर्णांकerface = xpcs_10gkr_पूर्णांकerfaces,
		.an_mode = DW_AN_C73,
	पूर्ण, अणु
		.id = SYNOPSYS_XPCS_XLGMII_ID,
		.mask = SYNOPSYS_XPCS_MASK,
		.supported = xpcs_xlgmii_features,
		.पूर्णांकerface = xpcs_xlgmii_पूर्णांकerfaces,
		.an_mode = DW_AN_C73,
	पूर्ण, अणु
		.id = SYNOPSYS_XPCS_SGMII_ID,
		.mask = SYNOPSYS_XPCS_MASK,
		.supported = xpcs_sgmii_features,
		.पूर्णांकerface = xpcs_sgmii_पूर्णांकerfaces,
		.an_mode = DW_AN_C37_SGMII,
	पूर्ण,
पूर्ण;

अटल पूर्णांक xpcs_पढ़ो(काष्ठा mdio_xpcs_args *xpcs, पूर्णांक dev, u32 reg)
अणु
	u32 reg_addr = MII_ADDR_C45 | dev << 16 | reg;

	वापस mdiobus_पढ़ो(xpcs->bus, xpcs->addr, reg_addr);
पूर्ण

अटल पूर्णांक xpcs_ग_लिखो(काष्ठा mdio_xpcs_args *xpcs, पूर्णांक dev, u32 reg, u16 val)
अणु
	u32 reg_addr = MII_ADDR_C45 | dev << 16 | reg;

	वापस mdiobus_ग_लिखो(xpcs->bus, xpcs->addr, reg_addr, val);
पूर्ण

अटल पूर्णांक xpcs_पढ़ो_venकरोr(काष्ठा mdio_xpcs_args *xpcs, पूर्णांक dev, u32 reg)
अणु
	वापस xpcs_पढ़ो(xpcs, dev, DW_VENDOR | reg);
पूर्ण

अटल पूर्णांक xpcs_ग_लिखो_venकरोr(काष्ठा mdio_xpcs_args *xpcs, पूर्णांक dev, पूर्णांक reg,
			     u16 val)
अणु
	वापस xpcs_ग_लिखो(xpcs, dev, DW_VENDOR | reg, val);
पूर्ण

अटल पूर्णांक xpcs_पढ़ो_vpcs(काष्ठा mdio_xpcs_args *xpcs, पूर्णांक reg)
अणु
	वापस xpcs_पढ़ो_venकरोr(xpcs, MDIO_MMD_PCS, reg);
पूर्ण

अटल पूर्णांक xpcs_ग_लिखो_vpcs(काष्ठा mdio_xpcs_args *xpcs, पूर्णांक reg, u16 val)
अणु
	वापस xpcs_ग_लिखो_venकरोr(xpcs, MDIO_MMD_PCS, reg, val);
पूर्ण

अटल पूर्णांक xpcs_poll_reset(काष्ठा mdio_xpcs_args *xpcs, पूर्णांक dev)
अणु
	/* Poll until the reset bit clears (50ms per retry == 0.6 sec) */
	अचिन्हित पूर्णांक retries = 12;
	पूर्णांक ret;

	करो अणु
		msleep(50);
		ret = xpcs_पढ़ो(xpcs, dev, MDIO_CTRL1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण जबतक (ret & MDIO_CTRL1_RESET && --retries);

	वापस (ret & MDIO_CTRL1_RESET) ? -ETIMEDOUT : 0;
पूर्ण

अटल पूर्णांक xpcs_soft_reset(काष्ठा mdio_xpcs_args *xpcs)
अणु
	पूर्णांक ret, dev;

	चयन (xpcs->an_mode) अणु
	हाल DW_AN_C73:
		dev = MDIO_MMD_PCS;
		अवरोध;
	हाल DW_AN_C37_SGMII:
		dev = MDIO_MMD_VEND2;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	ret = xpcs_ग_लिखो(xpcs, dev, MDIO_CTRL1, MDIO_CTRL1_RESET);
	अगर (ret < 0)
		वापस ret;

	वापस xpcs_poll_reset(xpcs, dev);
पूर्ण

#घोषणा xpcs_warn(__xpcs, __state, __args...) \
(अणु \
	अगर ((__state)->link) \
		dev_warn(&(__xpcs)->bus->dev, ##__args); \
पूर्ण)

अटल पूर्णांक xpcs_पढ़ो_fault_c73(काष्ठा mdio_xpcs_args *xpcs,
			       काष्ठा phylink_link_state *state)
अणु
	पूर्णांक ret;

	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_PCS, MDIO_STAT1);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & MDIO_STAT1_FAULT) अणु
		xpcs_warn(xpcs, state, "Link fault condition detected!\n");
		वापस -EFAULT;
	पूर्ण

	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_PCS, MDIO_STAT2);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & MDIO_STAT2_RXFAULT)
		xpcs_warn(xpcs, state, "Receiver fault detected!\n");
	अगर (ret & MDIO_STAT2_TXFAULT)
		xpcs_warn(xpcs, state, "Transmitter fault detected!\n");

	ret = xpcs_पढ़ो_venकरोr(xpcs, MDIO_MMD_PCS, DW_VR_XS_PCS_DIG_STS);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & DW_RXFIFO_ERR) अणु
		xpcs_warn(xpcs, state, "FIFO fault condition detected!\n");
		वापस -EFAULT;
	पूर्ण

	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_PCS, MDIO_PCS_10GBRT_STAT1);
	अगर (ret < 0)
		वापस ret;

	अगर (!(ret & MDIO_PCS_10GBRT_STAT1_BLKLK))
		xpcs_warn(xpcs, state, "Link is not locked!\n");

	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_PCS, MDIO_PCS_10GBRT_STAT2);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & MDIO_PCS_10GBRT_STAT2_ERR) अणु
		xpcs_warn(xpcs, state, "Link has errors!\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xpcs_पढ़ो_link_c73(काष्ठा mdio_xpcs_args *xpcs, bool an)
अणु
	bool link = true;
	पूर्णांक ret;

	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_PCS, MDIO_STAT1);
	अगर (ret < 0)
		वापस ret;

	अगर (!(ret & MDIO_STAT1_LSTATUS))
		link = false;

	अगर (an) अणु
		ret = xpcs_पढ़ो(xpcs, MDIO_MMD_AN, MDIO_STAT1);
		अगर (ret < 0)
			वापस ret;

		अगर (!(ret & MDIO_STAT1_LSTATUS))
			link = false;
	पूर्ण

	वापस link;
पूर्ण

अटल पूर्णांक xpcs_get_max_usxgmii_speed(स्थिर अचिन्हित दीर्घ *supported)
अणु
	पूर्णांक max = SPEED_UNKNOWN;

	अगर (phylink_test(supported, 1000baseKX_Full))
		max = SPEED_1000;
	अगर (phylink_test(supported, 2500baseX_Full))
		max = SPEED_2500;
	अगर (phylink_test(supported, 10000baseKX4_Full))
		max = SPEED_10000;
	अगर (phylink_test(supported, 10000baseKR_Full))
		max = SPEED_10000;

	वापस max;
पूर्ण

अटल पूर्णांक xpcs_config_usxgmii(काष्ठा mdio_xpcs_args *xpcs, पूर्णांक speed)
अणु
	पूर्णांक ret, speed_sel;

	चयन (speed) अणु
	हाल SPEED_10:
		speed_sel = DW_USXGMII_10;
		अवरोध;
	हाल SPEED_100:
		speed_sel = DW_USXGMII_100;
		अवरोध;
	हाल SPEED_1000:
		speed_sel = DW_USXGMII_1000;
		अवरोध;
	हाल SPEED_2500:
		speed_sel = DW_USXGMII_2500;
		अवरोध;
	हाल SPEED_5000:
		speed_sel = DW_USXGMII_5000;
		अवरोध;
	हाल SPEED_10000:
		speed_sel = DW_USXGMII_10000;
		अवरोध;
	शेष:
		/* Nothing to करो here */
		वापस -EINVAL;
	पूर्ण

	ret = xpcs_पढ़ो_vpcs(xpcs, MDIO_CTRL1);
	अगर (ret < 0)
		वापस ret;

	ret = xpcs_ग_लिखो_vpcs(xpcs, MDIO_CTRL1, ret | DW_USXGMII_EN);
	अगर (ret < 0)
		वापस ret;

	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_VEND2, MDIO_CTRL1);
	अगर (ret < 0)
		वापस ret;

	ret &= ~DW_USXGMII_SS_MASK;
	ret |= speed_sel | DW_USXGMII_FULL;

	ret = xpcs_ग_लिखो(xpcs, MDIO_MMD_VEND2, MDIO_CTRL1, ret);
	अगर (ret < 0)
		वापस ret;

	ret = xpcs_पढ़ो_vpcs(xpcs, MDIO_CTRL1);
	अगर (ret < 0)
		वापस ret;

	वापस xpcs_ग_लिखो_vpcs(xpcs, MDIO_CTRL1, ret | DW_USXGMII_RST);
पूर्ण

अटल पूर्णांक _xpcs_config_aneg_c73(काष्ठा mdio_xpcs_args *xpcs)
अणु
	पूर्णांक ret, adv;

	/* By शेष, in USXGMII mode XPCS operates at 10G baud and
	 * replicates data to achieve lower speeds. Hereby, in this
	 * शेष configuration we need to advertise all supported
	 * modes and not only the ones we want to use.
	 */

	/* SR_AN_ADV3 */
	adv = 0;
	अगर (phylink_test(xpcs->supported, 2500baseX_Full))
		adv |= DW_C73_2500KX;

	/* TODO: 5000baseKR */

	ret = xpcs_ग_लिखो(xpcs, MDIO_MMD_AN, DW_SR_AN_ADV3, adv);
	अगर (ret < 0)
		वापस ret;

	/* SR_AN_ADV2 */
	adv = 0;
	अगर (phylink_test(xpcs->supported, 1000baseKX_Full))
		adv |= DW_C73_1000KX;
	अगर (phylink_test(xpcs->supported, 10000baseKX4_Full))
		adv |= DW_C73_10000KX4;
	अगर (phylink_test(xpcs->supported, 10000baseKR_Full))
		adv |= DW_C73_10000KR;

	ret = xpcs_ग_लिखो(xpcs, MDIO_MMD_AN, DW_SR_AN_ADV2, adv);
	अगर (ret < 0)
		वापस ret;

	/* SR_AN_ADV1 */
	adv = DW_C73_AN_ADV_SF;
	अगर (phylink_test(xpcs->supported, Pause))
		adv |= DW_C73_PAUSE;
	अगर (phylink_test(xpcs->supported, Asym_Pause))
		adv |= DW_C73_ASYM_PAUSE;

	वापस xpcs_ग_लिखो(xpcs, MDIO_MMD_AN, DW_SR_AN_ADV1, adv);
पूर्ण

अटल पूर्णांक xpcs_config_aneg_c73(काष्ठा mdio_xpcs_args *xpcs)
अणु
	पूर्णांक ret;

	ret = _xpcs_config_aneg_c73(xpcs);
	अगर (ret < 0)
		वापस ret;

	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_AN, MDIO_CTRL1);
	अगर (ret < 0)
		वापस ret;

	ret |= MDIO_AN_CTRL1_ENABLE | MDIO_AN_CTRL1_RESTART;

	वापस xpcs_ग_लिखो(xpcs, MDIO_MMD_AN, MDIO_CTRL1, ret);
पूर्ण

अटल पूर्णांक xpcs_aneg_करोne_c73(काष्ठा mdio_xpcs_args *xpcs,
			      काष्ठा phylink_link_state *state)
अणु
	पूर्णांक ret;

	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_AN, MDIO_STAT1);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & MDIO_AN_STAT1_COMPLETE) अणु
		ret = xpcs_पढ़ो(xpcs, MDIO_MMD_AN, DW_SR_AN_LP_ABL1);
		अगर (ret < 0)
			वापस ret;

		/* Check अगर Aneg outcome is valid */
		अगर (!(ret & DW_C73_AN_ADV_SF)) अणु
			xpcs_config_aneg_c73(xpcs);
			वापस 0;
		पूर्ण

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xpcs_पढ़ो_lpa_c73(काष्ठा mdio_xpcs_args *xpcs,
			     काष्ठा phylink_link_state *state)
अणु
	पूर्णांक ret;

	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_AN, MDIO_STAT1);
	अगर (ret < 0)
		वापस ret;

	अगर (!(ret & MDIO_AN_STAT1_LPABLE)) अणु
		phylink_clear(state->lp_advertising, Autoneg);
		वापस 0;
	पूर्ण

	phylink_set(state->lp_advertising, Autoneg);

	/* Clause 73 outcome */
	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_AN, DW_SR_AN_LP_ABL3);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & DW_C73_2500KX)
		phylink_set(state->lp_advertising, 2500baseX_Full);

	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_AN, DW_SR_AN_LP_ABL2);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & DW_C73_1000KX)
		phylink_set(state->lp_advertising, 1000baseKX_Full);
	अगर (ret & DW_C73_10000KX4)
		phylink_set(state->lp_advertising, 10000baseKX4_Full);
	अगर (ret & DW_C73_10000KR)
		phylink_set(state->lp_advertising, 10000baseKR_Full);

	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_AN, DW_SR_AN_LP_ABL1);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & DW_C73_PAUSE)
		phylink_set(state->lp_advertising, Pause);
	अगर (ret & DW_C73_ASYM_PAUSE)
		phylink_set(state->lp_advertising, Asym_Pause);

	linkmode_and(state->lp_advertising, state->lp_advertising,
		     state->advertising);
	वापस 0;
पूर्ण

अटल व्योम xpcs_resolve_lpa_c73(काष्ठा mdio_xpcs_args *xpcs,
				 काष्ठा phylink_link_state *state)
अणु
	पूर्णांक max_speed = xpcs_get_max_usxgmii_speed(state->lp_advertising);

	state->छोड़ो = MLO_PAUSE_TX | MLO_PAUSE_RX;
	state->speed = max_speed;
	state->duplex = DUPLEX_FULL;
पूर्ण

अटल पूर्णांक xpcs_get_max_xlgmii_speed(काष्ठा mdio_xpcs_args *xpcs,
				     काष्ठा phylink_link_state *state)
अणु
	अचिन्हित दीर्घ *adv = state->advertising;
	पूर्णांक speed = SPEED_UNKNOWN;
	पूर्णांक bit;

	क्रम_each_set_bit(bit, adv, __ETHTOOL_LINK_MODE_MASK_NBITS) अणु
		पूर्णांक new_speed = SPEED_UNKNOWN;

		चयन (bit) अणु
		हाल ETHTOOL_LINK_MODE_25000baseCR_Full_BIT:
		हाल ETHTOOL_LINK_MODE_25000baseKR_Full_BIT:
		हाल ETHTOOL_LINK_MODE_25000baseSR_Full_BIT:
			new_speed = SPEED_25000;
			अवरोध;
		हाल ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT:
		हाल ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT:
		हाल ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT:
		हाल ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT:
			new_speed = SPEED_40000;
			अवरोध;
		हाल ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT:
		हाल ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT:
		हाल ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT:
		हाल ETHTOOL_LINK_MODE_50000baseKR_Full_BIT:
		हाल ETHTOOL_LINK_MODE_50000baseSR_Full_BIT:
		हाल ETHTOOL_LINK_MODE_50000baseCR_Full_BIT:
		हाल ETHTOOL_LINK_MODE_50000baseLR_ER_FR_Full_BIT:
		हाल ETHTOOL_LINK_MODE_50000baseDR_Full_BIT:
			new_speed = SPEED_50000;
			अवरोध;
		हाल ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT:
		हाल ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT:
		हाल ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT:
		हाल ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT:
		हाल ETHTOOL_LINK_MODE_100000baseKR2_Full_BIT:
		हाल ETHTOOL_LINK_MODE_100000baseSR2_Full_BIT:
		हाल ETHTOOL_LINK_MODE_100000baseCR2_Full_BIT:
		हाल ETHTOOL_LINK_MODE_100000baseLR2_ER2_FR2_Full_BIT:
		हाल ETHTOOL_LINK_MODE_100000baseDR2_Full_BIT:
			new_speed = SPEED_100000;
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		अगर (new_speed > speed)
			speed = new_speed;
	पूर्ण

	वापस speed;
पूर्ण

अटल व्योम xpcs_resolve_pma(काष्ठा mdio_xpcs_args *xpcs,
			     काष्ठा phylink_link_state *state)
अणु
	state->छोड़ो = MLO_PAUSE_TX | MLO_PAUSE_RX;
	state->duplex = DUPLEX_FULL;

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_10GKR:
		state->speed = SPEED_10000;
		अवरोध;
	हाल PHY_INTERFACE_MODE_XLGMII:
		state->speed = xpcs_get_max_xlgmii_speed(xpcs, state);
		अवरोध;
	शेष:
		state->speed = SPEED_UNKNOWN;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक xpcs_validate(काष्ठा mdio_xpcs_args *xpcs,
			 अचिन्हित दीर्घ *supported,
			 काष्ठा phylink_link_state *state)
अणु
	linkmode_and(supported, supported, xpcs->supported);
	linkmode_and(state->advertising, state->advertising, xpcs->supported);
	वापस 0;
पूर्ण

अटल पूर्णांक xpcs_config_aneg_c37_sgmii(काष्ठा mdio_xpcs_args *xpcs)
अणु
	पूर्णांक ret;

	/* For AN क्रम C37 SGMII mode, the settings are :-
	 * 1) VR_MII_AN_CTRL Bit(2:1)[PCS_MODE] = 10b (SGMII AN)
	 * 2) VR_MII_AN_CTRL Bit(3) [TX_CONFIG] = 0b (MAC side SGMII)
	 *    DW xPCS used with DW EQoS MAC is always MAC side SGMII.
	 * 3) VR_MII_DIG_CTRL1 Bit(9) [MAC_AUTO_SW] = 1b (Automatic
	 *    speed/duplex mode change by HW after SGMII AN complete)
	 *
	 * Note: Since it is MAC side SGMII, there is no need to set
	 *	 SR_MII_AN_ADV. MAC side SGMII receives AN Tx Config from
	 *	 PHY about the link state change after C28 AN is completed
	 *	 between PHY and Link Partner. There is also no need to
	 *	 trigger AN restart क्रम MAC-side SGMII.
	 */
	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_VEND2, DW_VR_MII_AN_CTRL);
	अगर (ret < 0)
		वापस ret;

	ret &= ~(DW_VR_MII_PCS_MODE_MASK | DW_VR_MII_TX_CONFIG_MASK);
	ret |= (DW_VR_MII_PCS_MODE_C37_SGMII <<
		DW_VR_MII_AN_CTRL_PCS_MODE_SHIFT &
		DW_VR_MII_PCS_MODE_MASK);
	ret |= (DW_VR_MII_TX_CONFIG_MAC_SIDE_SGMII <<
		DW_VR_MII_AN_CTRL_TX_CONFIG_SHIFT &
		DW_VR_MII_TX_CONFIG_MASK);
	ret = xpcs_ग_लिखो(xpcs, MDIO_MMD_VEND2, DW_VR_MII_AN_CTRL, ret);
	अगर (ret < 0)
		वापस ret;

	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_VEND2, DW_VR_MII_DIG_CTRL1);
	अगर (ret < 0)
		वापस ret;

	ret |= DW_VR_MII_DIG_CTRL1_MAC_AUTO_SW;

	वापस xpcs_ग_लिखो(xpcs, MDIO_MMD_VEND2, DW_VR_MII_DIG_CTRL1, ret);
पूर्ण

अटल पूर्णांक xpcs_config(काष्ठा mdio_xpcs_args *xpcs,
		       स्थिर काष्ठा phylink_link_state *state)
अणु
	पूर्णांक ret;

	चयन (xpcs->an_mode) अणु
	हाल DW_AN_C73:
		अगर (state->an_enabled) अणु
			ret = xpcs_config_aneg_c73(xpcs);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;
	हाल DW_AN_C37_SGMII:
		ret = xpcs_config_aneg_c37_sgmii(xpcs);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xpcs_get_state_c73(काष्ठा mdio_xpcs_args *xpcs,
			      काष्ठा phylink_link_state *state)
अणु
	पूर्णांक ret;

	/* Link needs to be पढ़ो first ... */
	state->link = xpcs_पढ़ो_link_c73(xpcs, state->an_enabled) > 0 ? 1 : 0;

	/* ... and then we check the faults. */
	ret = xpcs_पढ़ो_fault_c73(xpcs, state);
	अगर (ret) अणु
		ret = xpcs_soft_reset(xpcs);
		अगर (ret)
			वापस ret;

		state->link = 0;

		वापस xpcs_config(xpcs, state);
	पूर्ण

	अगर (state->an_enabled && xpcs_aneg_करोne_c73(xpcs, state)) अणु
		state->an_complete = true;
		xpcs_पढ़ो_lpa_c73(xpcs, state);
		xpcs_resolve_lpa_c73(xpcs, state);
	पूर्ण अन्यथा अगर (state->an_enabled) अणु
		state->link = 0;
	पूर्ण अन्यथा अगर (state->link) अणु
		xpcs_resolve_pma(xpcs, state);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xpcs_get_state_c37_sgmii(काष्ठा mdio_xpcs_args *xpcs,
				    काष्ठा phylink_link_state *state)
अणु
	पूर्णांक ret;

	/* Reset link_state */
	state->link = false;
	state->speed = SPEED_UNKNOWN;
	state->duplex = DUPLEX_UNKNOWN;
	state->छोड़ो = 0;

	/* For C37 SGMII mode, we check DW_VR_MII_AN_INTR_STS क्रम link
	 * status, speed and duplex.
	 */
	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_VEND2, DW_VR_MII_AN_INTR_STS);
	अगर (ret < 0)
		वापस false;

	अगर (ret & DW_VR_MII_C37_ANSGM_SP_LNKSTS) अणु
		पूर्णांक speed_value;

		state->link = true;

		speed_value = (ret & DW_VR_MII_AN_STS_C37_ANSGM_SP) >>
			      DW_VR_MII_AN_STS_C37_ANSGM_SP_SHIFT;
		अगर (speed_value == DW_VR_MII_C37_ANSGM_SP_1000)
			state->speed = SPEED_1000;
		अन्यथा अगर (speed_value == DW_VR_MII_C37_ANSGM_SP_100)
			state->speed = SPEED_100;
		अन्यथा
			state->speed = SPEED_10;

		अगर (ret & DW_VR_MII_AN_STS_C37_ANSGM_FD)
			state->duplex = DUPLEX_FULL;
		अन्यथा
			state->duplex = DUPLEX_HALF;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xpcs_get_state(काष्ठा mdio_xpcs_args *xpcs,
			  काष्ठा phylink_link_state *state)
अणु
	पूर्णांक ret;

	चयन (xpcs->an_mode) अणु
	हाल DW_AN_C73:
		ret = xpcs_get_state_c73(xpcs, state);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल DW_AN_C37_SGMII:
		ret = xpcs_get_state_c37_sgmii(xpcs, state);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xpcs_link_up(काष्ठा mdio_xpcs_args *xpcs, पूर्णांक speed,
			phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	अगर (पूर्णांकerface == PHY_INTERFACE_MODE_USXGMII)
		वापस xpcs_config_usxgmii(xpcs, speed);

	वापस 0;
पूर्ण

अटल u32 xpcs_get_id(काष्ठा mdio_xpcs_args *xpcs)
अणु
	पूर्णांक ret;
	u32 id;

	/* First, search C73 PCS using PCS MMD */
	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_PCS, MII_PHYSID1);
	अगर (ret < 0)
		वापस 0xffffffff;

	id = ret << 16;

	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_PCS, MII_PHYSID2);
	अगर (ret < 0)
		वापस 0xffffffff;

	/* If Device IDs are not all zeros, we found C73 AN-type device */
	अगर (id | ret)
		वापस id | ret;

	/* Next, search C37 PCS using Venकरोr-Specअगरic MII MMD */
	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_VEND2, MII_PHYSID1);
	अगर (ret < 0)
		वापस 0xffffffff;

	id = ret << 16;

	ret = xpcs_पढ़ो(xpcs, MDIO_MMD_VEND2, MII_PHYSID2);
	अगर (ret < 0)
		वापस 0xffffffff;

	/* If Device IDs are not all zeros, we found C37 AN-type device */
	अगर (id | ret)
		वापस id | ret;

	वापस 0xffffffff;
पूर्ण

अटल bool xpcs_check_features(काष्ठा mdio_xpcs_args *xpcs,
				काष्ठा xpcs_id *match,
				phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	पूर्णांक i;

	क्रम (i = 0; match->पूर्णांकerface[i] != PHY_INTERFACE_MODE_MAX; i++) अणु
		अगर (match->पूर्णांकerface[i] == पूर्णांकerface)
			अवरोध;
	पूर्ण

	अगर (match->पूर्णांकerface[i] == PHY_INTERFACE_MODE_MAX)
		वापस false;

	क्रम (i = 0; match->supported[i] != __ETHTOOL_LINK_MODE_MASK_NBITS; i++)
		set_bit(match->supported[i], xpcs->supported);

	xpcs->an_mode = match->an_mode;

	वापस true;
पूर्ण

अटल पूर्णांक xpcs_probe(काष्ठा mdio_xpcs_args *xpcs, phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	u32 xpcs_id = xpcs_get_id(xpcs);
	काष्ठा xpcs_id *match = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(xpcs_id_list); i++) अणु
		काष्ठा xpcs_id *entry = &xpcs_id_list[i];

		अगर ((xpcs_id & entry->mask) == entry->id) अणु
			match = entry;

			अगर (xpcs_check_features(xpcs, match, पूर्णांकerface))
				वापस xpcs_soft_reset(xpcs);
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल काष्ठा mdio_xpcs_ops xpcs_ops = अणु
	.validate = xpcs_validate,
	.config = xpcs_config,
	.get_state = xpcs_get_state,
	.link_up = xpcs_link_up,
	.probe = xpcs_probe,
पूर्ण;

काष्ठा mdio_xpcs_ops *mdio_xpcs_get_ops(व्योम)
अणु
	वापस &xpcs_ops;
पूर्ण
EXPORT_SYMBOL_GPL(mdio_xpcs_get_ops);

MODULE_LICENSE("GPL v2");
