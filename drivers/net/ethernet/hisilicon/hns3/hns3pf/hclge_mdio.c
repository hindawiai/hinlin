<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2016-2017 Hisilicon Limited.

#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/marvell_phy.h>

#समावेश "hclge_cmd.h"
#समावेश "hclge_main.h"
#समावेश "hclge_mdio.h"

क्रमागत hclge_mdio_c22_op_seq अणु
	HCLGE_MDIO_C22_WRITE = 1,
	HCLGE_MDIO_C22_READ = 2
पूर्ण;

#घोषणा HCLGE_MDIO_CTRL_START_B		0
#घोषणा HCLGE_MDIO_CTRL_ST_S		1
#घोषणा HCLGE_MDIO_CTRL_ST_M		(0x3 << HCLGE_MDIO_CTRL_ST_S)
#घोषणा HCLGE_MDIO_CTRL_OP_S		3
#घोषणा HCLGE_MDIO_CTRL_OP_M		(0x3 << HCLGE_MDIO_CTRL_OP_S)

#घोषणा HCLGE_MDIO_PHYID_S		0
#घोषणा HCLGE_MDIO_PHYID_M		(0x1f << HCLGE_MDIO_PHYID_S)

#घोषणा HCLGE_MDIO_PHYREG_S		0
#घोषणा HCLGE_MDIO_PHYREG_M		(0x1f << HCLGE_MDIO_PHYREG_S)

#घोषणा HCLGE_MDIO_STA_B		0

काष्ठा hclge_mdio_cfg_cmd अणु
	u8 ctrl_bit;
	u8 phyid;
	u8 phyad;
	u8 rsvd;
	__le16 reserve;
	__le16 data_wr;
	__le16 data_rd;
	__le16 sta;
पूर्ण;

अटल पूर्णांक hclge_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phyid, पूर्णांक regnum,
			    u16 data)
अणु
	काष्ठा hclge_mdio_cfg_cmd *mdio_cmd;
	काष्ठा hclge_dev *hdev = bus->priv;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	अगर (test_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state))
		वापस 0;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MDIO_CONFIG, false);

	mdio_cmd = (काष्ठा hclge_mdio_cfg_cmd *)desc.data;

	hnae3_set_field(mdio_cmd->phyid, HCLGE_MDIO_PHYID_M,
			HCLGE_MDIO_PHYID_S, (u32)phyid);
	hnae3_set_field(mdio_cmd->phyad, HCLGE_MDIO_PHYREG_M,
			HCLGE_MDIO_PHYREG_S, (u32)regnum);

	hnae3_set_bit(mdio_cmd->ctrl_bit, HCLGE_MDIO_CTRL_START_B, 1);
	hnae3_set_field(mdio_cmd->ctrl_bit, HCLGE_MDIO_CTRL_ST_M,
			HCLGE_MDIO_CTRL_ST_S, 1);
	hnae3_set_field(mdio_cmd->ctrl_bit, HCLGE_MDIO_CTRL_OP_M,
			HCLGE_MDIO_CTRL_OP_S, HCLGE_MDIO_C22_WRITE);

	mdio_cmd->data_wr = cpu_to_le16(data);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"mdio write fail when sending cmd, status is %d.\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phyid, पूर्णांक regnum)
अणु
	काष्ठा hclge_mdio_cfg_cmd *mdio_cmd;
	काष्ठा hclge_dev *hdev = bus->priv;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	अगर (test_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state))
		वापस 0;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MDIO_CONFIG, true);

	mdio_cmd = (काष्ठा hclge_mdio_cfg_cmd *)desc.data;

	hnae3_set_field(mdio_cmd->phyid, HCLGE_MDIO_PHYID_M,
			HCLGE_MDIO_PHYID_S, (u32)phyid);
	hnae3_set_field(mdio_cmd->phyad, HCLGE_MDIO_PHYREG_M,
			HCLGE_MDIO_PHYREG_S, (u32)regnum);

	hnae3_set_bit(mdio_cmd->ctrl_bit, HCLGE_MDIO_CTRL_START_B, 1);
	hnae3_set_field(mdio_cmd->ctrl_bit, HCLGE_MDIO_CTRL_ST_M,
			HCLGE_MDIO_CTRL_ST_S, 1);
	hnae3_set_field(mdio_cmd->ctrl_bit, HCLGE_MDIO_CTRL_OP_M,
			HCLGE_MDIO_CTRL_OP_S, HCLGE_MDIO_C22_READ);

	/* Read out phy data */
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"mdio read fail when get data, status is %d.\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (hnae3_get_bit(le16_to_cpu(mdio_cmd->sta), HCLGE_MDIO_STA_B)) अणु
		dev_err(&hdev->pdev->dev, "mdio read data error\n");
		वापस -EIO;
	पूर्ण

	वापस le16_to_cpu(mdio_cmd->data_rd);
पूर्ण

पूर्णांक hclge_mac_mdio_config(काष्ठा hclge_dev *hdev)
अणु
#घोषणा PHY_INEXISTENT	255

	काष्ठा hclge_mac *mac = &hdev->hw.mac;
	काष्ठा phy_device *phydev;
	काष्ठा mii_bus *mdio_bus;
	पूर्णांक ret;

	अगर (hdev->hw.mac.phy_addr == PHY_INEXISTENT) अणु
		dev_info(&hdev->pdev->dev,
			 "no phy device is connected to mdio bus\n");
		वापस 0;
	पूर्ण अन्यथा अगर (hdev->hw.mac.phy_addr >= PHY_MAX_ADDR) अणु
		dev_err(&hdev->pdev->dev, "phy_addr(%u) is too large.\n",
			hdev->hw.mac.phy_addr);
		वापस -EINVAL;
	पूर्ण

	mdio_bus = devm_mdiobus_alloc(&hdev->pdev->dev);
	अगर (!mdio_bus)
		वापस -ENOMEM;

	mdio_bus->name = "hisilicon MII bus";
	mdio_bus->पढ़ो = hclge_mdio_पढ़ो;
	mdio_bus->ग_लिखो = hclge_mdio_ग_लिखो;
	snम_लिखो(mdio_bus->id, MII_BUS_ID_SIZE, "%s-%s", "mii",
		 dev_name(&hdev->pdev->dev));

	mdio_bus->parent = &hdev->pdev->dev;
	mdio_bus->priv = hdev;
	mdio_bus->phy_mask = ~(1 << mac->phy_addr);
	ret = mdiobus_रेजिस्टर(mdio_bus);
	अगर (ret) अणु
		dev_err(mdio_bus->parent,
			"failed to register MDIO bus, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	phydev = mdiobus_get_phy(mdio_bus, mac->phy_addr);
	अगर (!phydev) अणु
		dev_err(mdio_bus->parent, "Failed to get phy device\n");
		mdiobus_unरेजिस्टर(mdio_bus);
		वापस -EIO;
	पूर्ण

	mac->phydev = phydev;
	mac->mdio_bus = mdio_bus;

	वापस 0;
पूर्ण

अटल व्योम hclge_mac_adjust_link(काष्ठा net_device *netdev)
अणु
	काष्ठा hnae3_handle *h = *((व्योम **)netdev_priv(netdev));
	काष्ठा hclge_vport *vport = hclge_get_vport(h);
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक duplex, speed;
	पूर्णांक ret;

	/* When phy link करोwn, करो nothing */
	अगर (netdev->phydev->link == 0)
		वापस;

	speed = netdev->phydev->speed;
	duplex = netdev->phydev->duplex;

	ret = hclge_cfg_mac_speed_dup(hdev, speed, duplex);
	अगर (ret)
		netdev_err(netdev, "failed to adjust link.\n");

	ret = hclge_cfg_flowctrl(hdev);
	अगर (ret)
		netdev_err(netdev, "failed to configure flow control.\n");
पूर्ण

पूर्णांक hclge_mac_connect_phy(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा net_device *netdev = hdev->vport[0].nic.netdev;
	काष्ठा phy_device *phydev = hdev->hw.mac.phydev;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;
	पूर्णांक ret;

	अगर (!phydev)
		वापस 0;

	linkmode_clear_bit(ETHTOOL_LINK_MODE_FIBRE_BIT, phydev->supported);

	phydev->dev_flags |= MARVELL_PHY_LED0_LINK_LED1_ACTIVE;

	ret = phy_connect_direct(netdev, phydev,
				 hclge_mac_adjust_link,
				 PHY_INTERFACE_MODE_SGMII);
	अगर (ret) अणु
		netdev_err(netdev, "phy_connect_direct err.\n");
		वापस ret;
	पूर्ण

	linkmode_copy(mask, hdev->hw.mac.supported);
	linkmode_and(phydev->supported, phydev->supported, mask);
	linkmode_copy(phydev->advertising, phydev->supported);

	/* supported flag is Pause and Asym Pause, but शेष advertising
	 * should be rx on, tx on, so need clear Asym Pause in advertising
	 * flag
	 */
	linkmode_clear_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
			   phydev->advertising);

	phy_attached_info(phydev);

	वापस 0;
पूर्ण

व्योम hclge_mac_disconnect_phy(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclge_vport *vport = hclge_get_vport(handle);
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा phy_device *phydev = hdev->hw.mac.phydev;

	अगर (!phydev)
		वापस;

	phy_disconnect(phydev);
पूर्ण

व्योम hclge_mac_start_phy(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा phy_device *phydev = hdev->hw.mac.phydev;

	अगर (!phydev)
		वापस;

	phy_loopback(phydev, false);

	phy_start(phydev);
पूर्ण

व्योम hclge_mac_stop_phy(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा net_device *netdev = hdev->vport[0].nic.netdev;
	काष्ठा phy_device *phydev = netdev->phydev;

	अगर (!phydev)
		वापस;

	phy_stop(phydev);
पूर्ण

u16 hclge_पढ़ो_phy_reg(काष्ठा hclge_dev *hdev, u16 reg_addr)
अणु
	काष्ठा hclge_phy_reg_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_PHY_REG, true);

	req = (काष्ठा hclge_phy_reg_cmd *)desc.data;
	req->reg_addr = cpu_to_le16(reg_addr);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"failed to read phy reg, ret = %d.\n", ret);

	वापस le16_to_cpu(req->reg_val);
पूर्ण

पूर्णांक hclge_ग_लिखो_phy_reg(काष्ठा hclge_dev *hdev, u16 reg_addr, u16 val)
अणु
	काष्ठा hclge_phy_reg_cmd *req;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_PHY_REG, false);

	req = (काष्ठा hclge_phy_reg_cmd *)desc.data;
	req->reg_addr = cpu_to_le16(reg_addr);
	req->reg_val = cpu_to_le16(val);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"failed to write phy reg, ret = %d.\n", ret);

	वापस ret;
पूर्ण
