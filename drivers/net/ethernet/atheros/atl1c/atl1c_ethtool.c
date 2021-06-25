<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 2009 - 2009 Atheros Corporation. All rights reserved.
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/slab.h>

#समावेश "atl1c.h"

अटल पूर्णांक atl1c_get_link_ksettings(काष्ठा net_device *netdev,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1c_hw *hw = &adapter->hw;
	u32 supported, advertising;

	supported = (SUPPORTED_10baseT_Half  |
			   SUPPORTED_10baseT_Full  |
			   SUPPORTED_100baseT_Half |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_Autoneg       |
			   SUPPORTED_TP);
	अगर (hw->link_cap_flags & ATL1C_LINK_CAP_1000M)
		supported |= SUPPORTED_1000baseT_Full;

	advertising = ADVERTISED_TP;

	advertising |= hw->स्वतःneg_advertised;

	cmd->base.port = PORT_TP;
	cmd->base.phy_address = 0;

	अगर (adapter->link_speed != SPEED_0) अणु
		cmd->base.speed = adapter->link_speed;
		अगर (adapter->link_duplex == FULL_DUPLEX)
			cmd->base.duplex = DUPLEX_FULL;
		अन्यथा
			cmd->base.duplex = DUPLEX_HALF;
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	cmd->base.स्वतःneg = AUTONEG_ENABLE;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक atl1c_set_link_ksettings(काष्ठा net_device *netdev,
				    स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1c_hw *hw = &adapter->hw;
	u16  स्वतःneg_advertised;

	जबतक (test_and_set_bit(__AT_RESETTING, &adapter->flags))
		msleep(1);

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		स्वतःneg_advertised = ADVERTISED_Autoneg;
	पूर्ण अन्यथा अणु
		u32 speed = cmd->base.speed;
		अगर (speed == SPEED_1000) अणु
			अगर (cmd->base.duplex != DUPLEX_FULL) अणु
				अगर (netअगर_msg_link(adapter))
					dev_warn(&adapter->pdev->dev,
						"1000M half is invalid\n");
				clear_bit(__AT_RESETTING, &adapter->flags);
				वापस -EINVAL;
			पूर्ण
			स्वतःneg_advertised = ADVERTISED_1000baseT_Full;
		पूर्ण अन्यथा अगर (speed == SPEED_100) अणु
			अगर (cmd->base.duplex == DUPLEX_FULL)
				स्वतःneg_advertised = ADVERTISED_100baseT_Full;
			अन्यथा
				स्वतःneg_advertised = ADVERTISED_100baseT_Half;
		पूर्ण अन्यथा अणु
			अगर (cmd->base.duplex == DUPLEX_FULL)
				स्वतःneg_advertised = ADVERTISED_10baseT_Full;
			अन्यथा
				स्वतःneg_advertised = ADVERTISED_10baseT_Half;
		पूर्ण
	पूर्ण

	अगर (hw->स्वतःneg_advertised != स्वतःneg_advertised) अणु
		hw->स्वतःneg_advertised = स्वतःneg_advertised;
		अगर (atl1c_restart_स्वतःneg(hw) != 0) अणु
			अगर (netअगर_msg_link(adapter))
				dev_warn(&adapter->pdev->dev,
					"ethtool speed/duplex setting failed\n");
			clear_bit(__AT_RESETTING, &adapter->flags);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	clear_bit(__AT_RESETTING, &adapter->flags);
	वापस 0;
पूर्ण

अटल u32 atl1c_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	वापस adapter->msg_enable;
पूर्ण

अटल व्योम atl1c_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	adapter->msg_enable = data;
पूर्ण

अटल पूर्णांक atl1c_get_regs_len(काष्ठा net_device *netdev)
अणु
	वापस AT_REGS_LEN;
पूर्ण

अटल व्योम atl1c_get_regs(काष्ठा net_device *netdev,
			   काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1c_hw *hw = &adapter->hw;
	u32 *regs_buff = p;
	u16 phy_data;

	स_रखो(p, 0, AT_REGS_LEN);

	regs->version = 1;
	AT_READ_REG(hw, REG_PM_CTRL, 		  p++);
	AT_READ_REG(hw, REG_MAC_HALF_DUPLX_CTRL,  p++);
	AT_READ_REG(hw, REG_TWSI_CTRL, 		  p++);
	AT_READ_REG(hw, REG_PCIE_DEV_MISC_CTRL,   p++);
	AT_READ_REG(hw, REG_MASTER_CTRL, 	  p++);
	AT_READ_REG(hw, REG_MANUAL_TIMER_INIT,    p++);
	AT_READ_REG(hw, REG_IRQ_MODRT_TIMER_INIT, p++);
	AT_READ_REG(hw, REG_GPHY_CTRL, 		  p++);
	AT_READ_REG(hw, REG_LINK_CTRL, 		  p++);
	AT_READ_REG(hw, REG_IDLE_STATUS, 	  p++);
	AT_READ_REG(hw, REG_MDIO_CTRL, 		  p++);
	AT_READ_REG(hw, REG_SERDES,		  p++);
	AT_READ_REG(hw, REG_MAC_CTRL, 		  p++);
	AT_READ_REG(hw, REG_MAC_IPG_IFG, 	  p++);
	AT_READ_REG(hw, REG_MAC_STA_ADDR, 	  p++);
	AT_READ_REG(hw, REG_MAC_STA_ADDR+4, 	  p++);
	AT_READ_REG(hw, REG_RX_HASH_TABLE, 	  p++);
	AT_READ_REG(hw, REG_RX_HASH_TABLE+4, 	  p++);
	AT_READ_REG(hw, REG_RXQ_CTRL, 		  p++);
	AT_READ_REG(hw, REG_TXQ_CTRL, 		  p++);
	AT_READ_REG(hw, REG_MTU, 		  p++);
	AT_READ_REG(hw, REG_WOL_CTRL, 		  p++);

	atl1c_पढ़ो_phy_reg(hw, MII_BMCR, &phy_data);
	regs_buff[AT_REGS_LEN/माप(u32) - 2] = (u32) phy_data;
	atl1c_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
	regs_buff[AT_REGS_LEN/माप(u32) - 1] = (u32) phy_data;
पूर्ण

अटल पूर्णांक atl1c_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	अगर (atl1c_check_eeprom_exist(&adapter->hw))
		वापस AT_EEPROM_LEN;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक atl1c_get_eeprom(काष्ठा net_device *netdev,
		काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1c_hw *hw = &adapter->hw;
	u32 *eeprom_buff;
	पूर्णांक first_dword, last_dword;
	पूर्णांक ret_val = 0;
	पूर्णांक i;

	अगर (eeprom->len == 0)
		वापस -EINVAL;

	अगर (!atl1c_check_eeprom_exist(hw)) /* not exist */
		वापस -EINVAL;

	eeprom->magic = adapter->pdev->venकरोr |
			(adapter->pdev->device << 16);

	first_dword = eeprom->offset >> 2;
	last_dword = (eeprom->offset + eeprom->len - 1) >> 2;

	eeprom_buff = kदो_स्मृति_array(last_dword - first_dword + 1, माप(u32),
				    GFP_KERNEL);
	अगर (eeprom_buff == शून्य)
		वापस -ENOMEM;

	क्रम (i = first_dword; i < last_dword; i++) अणु
		अगर (!atl1c_पढ़ो_eeprom(hw, i * 4, &(eeprom_buff[i-first_dword]))) अणु
			kमुक्त(eeprom_buff);
			वापस -EIO;
		पूर्ण
	पूर्ण

	स_नकल(bytes, (u8 *)eeprom_buff + (eeprom->offset & 3),
			eeprom->len);
	kमुक्त(eeprom_buff);

	वापस ret_val;
	वापस 0;
पूर्ण

अटल व्योम atl1c_get_drvinfo(काष्ठा net_device *netdev,
		काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver,  atl1c_driver_name, माप(drvinfo->driver));
	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल व्योम atl1c_get_wol(काष्ठा net_device *netdev,
			  काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	wol->supported = WAKE_MAGIC | WAKE_PHY;
	wol->wolopts = 0;

	अगर (adapter->wol & AT_WUFC_EX)
		wol->wolopts |= WAKE_UCAST;
	अगर (adapter->wol & AT_WUFC_MC)
		wol->wolopts |= WAKE_MCAST;
	अगर (adapter->wol & AT_WUFC_BC)
		wol->wolopts |= WAKE_BCAST;
	अगर (adapter->wol & AT_WUFC_MAG)
		wol->wolopts |= WAKE_MAGIC;
	अगर (adapter->wol & AT_WUFC_LNKC)
		wol->wolopts |= WAKE_PHY;
पूर्ण

अटल पूर्णांक atl1c_set_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	अगर (wol->wolopts & (WAKE_ARP | WAKE_MAGICSECURE |
			    WAKE_UCAST | WAKE_BCAST | WAKE_MCAST))
		वापस -EOPNOTSUPP;
	/* these settings will always override what we currently have */
	adapter->wol = 0;

	अगर (wol->wolopts & WAKE_MAGIC)
		adapter->wol |= AT_WUFC_MAG;
	अगर (wol->wolopts & WAKE_PHY)
		adapter->wol |= AT_WUFC_LNKC;

	device_set_wakeup_enable(&adapter->pdev->dev, adapter->wol);

	वापस 0;
पूर्ण

अटल पूर्णांक atl1c_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	अगर (netअगर_running(netdev))
		atl1c_reinit_locked(adapter);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops atl1c_ethtool_ops = अणु
	.get_drvinfo            = atl1c_get_drvinfo,
	.get_regs_len           = atl1c_get_regs_len,
	.get_regs               = atl1c_get_regs,
	.get_wol                = atl1c_get_wol,
	.set_wol                = atl1c_set_wol,
	.get_msglevel           = atl1c_get_msglevel,
	.set_msglevel           = atl1c_set_msglevel,
	.nway_reset             = atl1c_nway_reset,
	.get_link               = ethtool_op_get_link,
	.get_eeprom_len         = atl1c_get_eeprom_len,
	.get_eeprom             = atl1c_get_eeprom,
	.get_link_ksettings     = atl1c_get_link_ksettings,
	.set_link_ksettings     = atl1c_set_link_ksettings,
पूर्ण;

व्योम atl1c_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &atl1c_ethtool_ops;
पूर्ण
