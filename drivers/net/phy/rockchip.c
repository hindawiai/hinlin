<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/**
 * drivers/net/phy/rockchip.c
 *
 * Driver क्रम ROCKCHIP Ethernet PHYs
 *
 * Copyright (c) 2017, Fuzhou Rockchip Electronics Co., Ltd
 *
 * David Wu <david.wu@rock-chips.com>
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>

#घोषणा INTERNAL_EPHY_ID			0x1234d400

#घोषणा MII_INTERNAL_CTRL_STATUS		17
#घोषणा SMI_ADDR_TSTCNTL			20
#घोषणा SMI_ADDR_TSTREAD1			21
#घोषणा SMI_ADDR_TSTREAD2			22
#घोषणा SMI_ADDR_TSTWRITE			23
#घोषणा MII_SPECIAL_CONTROL_STATUS		31

#घोषणा MII_AUTO_MDIX_EN			BIT(7)
#घोषणा MII_MDIX_EN				BIT(6)

#घोषणा MII_SPEED_10				BIT(2)
#घोषणा MII_SPEED_100				BIT(3)

#घोषणा TSTCNTL_RD				(BIT(15) | BIT(10))
#घोषणा TSTCNTL_WR				(BIT(14) | BIT(10))

#घोषणा TSTMODE_ENABLE				0x400
#घोषणा TSTMODE_DISABLE				0x0

#घोषणा WR_ADDR_A7CFG				0x18

अटल पूर्णांक rockchip_init_tsपंचांगode(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Enable access to Analog and DSP रेजिस्टर banks */
	ret = phy_ग_लिखो(phydev, SMI_ADDR_TSTCNTL, TSTMODE_ENABLE);
	अगर (ret)
		वापस ret;

	ret = phy_ग_लिखो(phydev, SMI_ADDR_TSTCNTL, TSTMODE_DISABLE);
	अगर (ret)
		वापस ret;

	वापस phy_ग_लिखो(phydev, SMI_ADDR_TSTCNTL, TSTMODE_ENABLE);
पूर्ण

अटल पूर्णांक rockchip_बंद_tsपंचांगode(काष्ठा phy_device *phydev)
अणु
	/* Back to basic रेजिस्टर bank */
	वापस phy_ग_लिखो(phydev, SMI_ADDR_TSTCNTL, TSTMODE_DISABLE);
पूर्ण

अटल पूर्णांक rockchip_पूर्णांकegrated_phy_analog_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = rockchip_init_tsपंचांगode(phydev);
	अगर (ret)
		वापस ret;

	/*
	 * Adjust tx amplitude to make sginal better,
	 * the शेष value is 0x8.
	 */
	ret = phy_ग_लिखो(phydev, SMI_ADDR_TSTWRITE, 0xB);
	अगर (ret)
		वापस ret;
	ret = phy_ग_लिखो(phydev, SMI_ADDR_TSTCNTL, TSTCNTL_WR | WR_ADDR_A7CFG);
	अगर (ret)
		वापस ret;

	वापस rockchip_बंद_tsपंचांगode(phydev);
पूर्ण

अटल पूर्णांक rockchip_पूर्णांकegrated_phy_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val, ret;

	/*
	 * The स्वतः MIDX has linked problem on some board,
	 * workround to disable स्वतः MDIX.
	 */
	val = phy_पढ़ो(phydev, MII_INTERNAL_CTRL_STATUS);
	अगर (val < 0)
		वापस val;
	val &= ~MII_AUTO_MDIX_EN;
	ret = phy_ग_लिखो(phydev, MII_INTERNAL_CTRL_STATUS, val);
	अगर (ret)
		वापस ret;

	वापस rockchip_पूर्णांकegrated_phy_analog_init(phydev);
पूर्ण

अटल व्योम rockchip_link_change_notअगरy(काष्ठा phy_device *phydev)
अणु
	/*
	 * If mode चयन happens from 10BT to 100BT, all DSP/AFE
	 * रेजिस्टरs are set to शेष values. So any AFE/DSP
	 * रेजिस्टरs have to be re-initialized in this हाल.
	 */
	अगर (phydev->state == PHY_RUNNING && phydev->speed == SPEED_100) अणु
		पूर्णांक ret = rockchip_पूर्णांकegrated_phy_analog_init(phydev);

		अगर (ret)
			phydev_err(phydev, "rockchip_integrated_phy_analog_init err: %d.\n",
				   ret);
	पूर्ण
पूर्ण

अटल पूर्णांक rockchip_set_polarity(काष्ठा phy_device *phydev, पूर्णांक polarity)
अणु
	पूर्णांक reg, err, val;

	/* get the current settings */
	reg = phy_पढ़ो(phydev, MII_INTERNAL_CTRL_STATUS);
	अगर (reg < 0)
		वापस reg;

	reg &= ~MII_AUTO_MDIX_EN;
	val = reg;
	चयन (polarity) अणु
	हाल ETH_TP_MDI:
		val &= ~MII_MDIX_EN;
		अवरोध;
	हाल ETH_TP_MDI_X:
		val |= MII_MDIX_EN;
		अवरोध;
	हाल ETH_TP_MDI_AUTO:
	हाल ETH_TP_MDI_INVALID:
	शेष:
		वापस 0;
	पूर्ण

	अगर (val != reg) अणु
		/* Set the new polarity value in the रेजिस्टर */
		err = phy_ग_लिखो(phydev, MII_INTERNAL_CTRL_STATUS, val);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = rockchip_set_polarity(phydev, phydev->mdix);
	अगर (err < 0)
		वापस err;

	वापस genphy_config_aneg(phydev);
पूर्ण

अटल पूर्णांक rockchip_phy_resume(काष्ठा phy_device *phydev)
अणु
	genphy_resume(phydev);

	वापस rockchip_पूर्णांकegrated_phy_config_init(phydev);
पूर्ण

अटल काष्ठा phy_driver rockchip_phy_driver[] = अणु
अणु
	.phy_id			= INTERNAL_EPHY_ID,
	.phy_id_mask		= 0xfffffff0,
	.name			= "Rockchip integrated EPHY",
	/* PHY_BASIC_FEATURES */
	.flags			= 0,
	.link_change_notअगरy	= rockchip_link_change_notअगरy,
	.soft_reset		= genphy_soft_reset,
	.config_init		= rockchip_पूर्णांकegrated_phy_config_init,
	.config_aneg		= rockchip_config_aneg,
	.suspend		= genphy_suspend,
	.resume			= rockchip_phy_resume,
पूर्ण,
पूर्ण;

module_phy_driver(rockchip_phy_driver);

अटल काष्ठा mdio_device_id __maybe_unused rockchip_phy_tbl[] = अणु
	अणु INTERNAL_EPHY_ID, 0xfffffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, rockchip_phy_tbl);

MODULE_AUTHOR("David Wu <david.wu@rock-chips.com>");
MODULE_DESCRIPTION("Rockchip Ethernet PHY driver");
MODULE_LICENSE("GPL");
