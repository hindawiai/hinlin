<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Applied Micro X-Gene SoC Ethernet v2 Driver
 *
 * Copyright (c) 2017, Applied Micro Circuits Corporation
 * Author(s): Iyappan Subramanian <isubramanian@apm.com>
 *	      Keyur Chudgar <kchudgar@apm.com>
 */

#समावेश "main.h"

अटल पूर्णांक xge_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg, u16 data)
अणु
	काष्ठा xge_pdata *pdata = bus->priv;
	u32 करोne, val = 0;
	u8 रुको = 10;

	SET_REG_BITS(&val, PHY_ADDR, phy_id);
	SET_REG_BITS(&val, REG_ADDR, reg);
	xge_wr_csr(pdata, MII_MGMT_ADDRESS, val);

	xge_wr_csr(pdata, MII_MGMT_CONTROL, data);
	करो अणु
		usleep_range(5, 10);
		करोne = xge_rd_csr(pdata, MII_MGMT_INDICATORS);
	पूर्ण जबतक ((करोne & MII_MGMT_BUSY) && रुको--);

	अगर (करोne & MII_MGMT_BUSY) अणु
		dev_err(&bus->dev, "MII_MGMT write failed\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xge_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg)
अणु
	काष्ठा xge_pdata *pdata = bus->priv;
	u32 data, करोne, val = 0;
	u8 रुको = 10;

	SET_REG_BITS(&val, PHY_ADDR, phy_id);
	SET_REG_BITS(&val, REG_ADDR, reg);
	xge_wr_csr(pdata, MII_MGMT_ADDRESS, val);

	xge_wr_csr(pdata, MII_MGMT_COMMAND, MII_READ_CYCLE);
	करो अणु
		usleep_range(5, 10);
		करोne = xge_rd_csr(pdata, MII_MGMT_INDICATORS);
	पूर्ण जबतक ((करोne & MII_MGMT_BUSY) && रुको--);

	अगर (करोne & MII_MGMT_BUSY) अणु
		dev_err(&bus->dev, "MII_MGMT read failed\n");
		वापस -ETIMEDOUT;
	पूर्ण

	data = xge_rd_csr(pdata, MII_MGMT_STATUS);
	xge_wr_csr(pdata, MII_MGMT_COMMAND, 0);

	वापस data;
पूर्ण

अटल व्योम xge_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	काष्ठा phy_device *phydev = ndev->phydev;

	अगर (phydev->link) अणु
		अगर (pdata->phy_speed != phydev->speed) अणु
			pdata->phy_speed = phydev->speed;
			xge_mac_set_speed(pdata);
			xge_mac_enable(pdata);
			phy_prपूर्णांक_status(phydev);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pdata->phy_speed != SPEED_UNKNOWN) अणु
			pdata->phy_speed = SPEED_UNKNOWN;
			xge_mac_disable(pdata);
			phy_prपूर्णांक_status(phydev);
		पूर्ण
	पूर्ण
पूर्ण

व्योम xge_mdio_हटाओ(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	काष्ठा mii_bus *mdio_bus = pdata->mdio_bus;

	अगर (ndev->phydev)
		phy_disconnect(ndev->phydev);

	अगर (mdio_bus->state == MDIOBUS_REGISTERED)
		mdiobus_unरेजिस्टर(mdio_bus);

	mdiobus_मुक्त(mdio_bus);
पूर्ण

पूर्णांक xge_mdio_config(काष्ठा net_device *ndev)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	काष्ठा device *dev = &pdata->pdev->dev;
	काष्ठा mii_bus *mdio_bus;
	काष्ठा phy_device *phydev;
	पूर्णांक ret;

	mdio_bus = mdiobus_alloc();
	अगर (!mdio_bus)
		वापस -ENOMEM;

	mdio_bus->name = "APM X-Gene Ethernet (v2) MDIO Bus";
	mdio_bus->पढ़ो = xge_mdio_पढ़ो;
	mdio_bus->ग_लिखो = xge_mdio_ग_लिखो;
	mdio_bus->priv = pdata;
	mdio_bus->parent = dev;
	snम_लिखो(mdio_bus->id, MII_BUS_ID_SIZE, "%s-mii", dev_name(dev));
	pdata->mdio_bus = mdio_bus;

	mdio_bus->phy_mask = 0x1;
	ret = mdiobus_रेजिस्टर(mdio_bus);
	अगर (ret)
		जाओ err;

	phydev = phy_find_first(mdio_bus);
	अगर (!phydev) अणु
		dev_err(dev, "no PHY found\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण
	phydev = phy_connect(ndev, phydev_name(phydev),
			     &xge_adjust_link,
			     pdata->resources.phy_mode);

	अगर (IS_ERR(phydev)) अणु
		netdev_err(ndev, "Could not attach to PHY\n");
		ret = PTR_ERR(phydev);
		जाओ err;
	पूर्ण

	linkmode_set_bit_array(phy_10_100_features_array,
			       ARRAY_SIZE(phy_10_100_features_array),
			       mask);
	linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT, mask);
	linkmode_set_bit(ETHTOOL_LINK_MODE_AUI_BIT, mask);
	linkmode_set_bit(ETHTOOL_LINK_MODE_MII_BIT, mask);
	linkmode_set_bit(ETHTOOL_LINK_MODE_FIBRE_BIT, mask);
	linkmode_set_bit(ETHTOOL_LINK_MODE_BNC_BIT, mask);

	linkmode_andnot(phydev->supported, phydev->supported, mask);
	linkmode_copy(phydev->advertising, phydev->supported);
	pdata->phy_speed = SPEED_UNKNOWN;

	वापस 0;
err:
	xge_mdio_हटाओ(ndev);

	वापस ret;
पूर्ण
