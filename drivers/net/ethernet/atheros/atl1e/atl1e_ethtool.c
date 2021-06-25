<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 2007 Atheros Corporation. All rights reserved.
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/slab.h>

#समावेश "atl1e.h"

अटल पूर्णांक atl1e_get_link_ksettings(काष्ठा net_device *netdev,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1e_hw *hw = &adapter->hw;
	u32 supported, advertising;

	supported = (SUPPORTED_10baseT_Half  |
			   SUPPORTED_10baseT_Full  |
			   SUPPORTED_100baseT_Half |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_Autoneg       |
			   SUPPORTED_TP);
	अगर (hw->nic_type == athr_l1e)
		supported |= SUPPORTED_1000baseT_Full;

	advertising = ADVERTISED_TP;

	advertising |= ADVERTISED_Autoneg;
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

अटल पूर्णांक atl1e_set_link_ksettings(काष्ठा net_device *netdev,
				    स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1e_hw *hw = &adapter->hw;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	जबतक (test_and_set_bit(__AT_RESETTING, &adapter->flags))
		msleep(1);

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		u16 adv4, adv9;

		अगर (advertising & ADVERTISE_1000_FULL) अणु
			अगर (hw->nic_type == athr_l1e) अणु
				hw->स्वतःneg_advertised =
					advertising & AT_ADV_MASK;
			पूर्ण अन्यथा अणु
				clear_bit(__AT_RESETTING, &adapter->flags);
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अगर (advertising & ADVERTISE_1000_HALF) अणु
			clear_bit(__AT_RESETTING, &adapter->flags);
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			hw->स्वतःneg_advertised =
				advertising & AT_ADV_MASK;
		पूर्ण
		advertising = hw->स्वतःneg_advertised |
				    ADVERTISED_TP | ADVERTISED_Autoneg;

		adv4 = hw->mii_स्वतःneg_adv_reg & ~ADVERTISE_ALL;
		adv9 = hw->mii_1000t_ctrl_reg & ~MII_AT001_CR_1000T_SPEED_MASK;
		अगर (hw->स्वतःneg_advertised & ADVERTISE_10_HALF)
			adv4 |= ADVERTISE_10HALF;
		अगर (hw->स्वतःneg_advertised & ADVERTISE_10_FULL)
			adv4 |= ADVERTISE_10FULL;
		अगर (hw->स्वतःneg_advertised & ADVERTISE_100_HALF)
			adv4 |= ADVERTISE_100HALF;
		अगर (hw->स्वतःneg_advertised & ADVERTISE_100_FULL)
			adv4 |= ADVERTISE_100FULL;
		अगर (hw->स्वतःneg_advertised & ADVERTISE_1000_FULL)
			adv9 |= ADVERTISE_1000FULL;

		अगर (adv4 != hw->mii_स्वतःneg_adv_reg ||
				adv9 != hw->mii_1000t_ctrl_reg) अणु
			hw->mii_स्वतःneg_adv_reg = adv4;
			hw->mii_1000t_ctrl_reg = adv9;
			hw->re_स्वतःneg = true;
		पूर्ण

	पूर्ण अन्यथा अणु
		clear_bit(__AT_RESETTING, &adapter->flags);
		वापस -EINVAL;
	पूर्ण

	/* reset the link */

	अगर (netअगर_running(adapter->netdev)) अणु
		atl1e_करोwn(adapter);
		atl1e_up(adapter);
	पूर्ण अन्यथा
		atl1e_reset_hw(&adapter->hw);

	clear_bit(__AT_RESETTING, &adapter->flags);
	वापस 0;
पूर्ण

अटल u32 atl1e_get_msglevel(काष्ठा net_device *netdev)
अणु
#अगर_घोषित DBG
	वापस 1;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक atl1e_get_regs_len(काष्ठा net_device *netdev)
अणु
	वापस AT_REGS_LEN * माप(u32);
पूर्ण

अटल व्योम atl1e_get_regs(काष्ठा net_device *netdev,
			   काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1e_hw *hw = &adapter->hw;
	u32 *regs_buff = p;
	u16 phy_data;

	स_रखो(p, 0, AT_REGS_LEN * माप(u32));

	regs->version = (1 << 24) | (hw->revision_id << 16) | hw->device_id;

	regs_buff[0]  = AT_READ_REG(hw, REG_VPD_CAP);
	regs_buff[1]  = AT_READ_REG(hw, REG_SPI_FLASH_CTRL);
	regs_buff[2]  = AT_READ_REG(hw, REG_SPI_FLASH_CONFIG);
	regs_buff[3]  = AT_READ_REG(hw, REG_TWSI_CTRL);
	regs_buff[4]  = AT_READ_REG(hw, REG_PCIE_DEV_MISC_CTRL);
	regs_buff[5]  = AT_READ_REG(hw, REG_MASTER_CTRL);
	regs_buff[6]  = AT_READ_REG(hw, REG_MANUAL_TIMER_INIT);
	regs_buff[7]  = AT_READ_REG(hw, REG_IRQ_MODU_TIMER_INIT);
	regs_buff[8]  = AT_READ_REG(hw, REG_GPHY_CTRL);
	regs_buff[9]  = AT_READ_REG(hw, REG_CMBDISDMA_TIMER);
	regs_buff[10] = AT_READ_REG(hw, REG_IDLE_STATUS);
	regs_buff[11] = AT_READ_REG(hw, REG_MDIO_CTRL);
	regs_buff[12] = AT_READ_REG(hw, REG_SERDES_LOCK);
	regs_buff[13] = AT_READ_REG(hw, REG_MAC_CTRL);
	regs_buff[14] = AT_READ_REG(hw, REG_MAC_IPG_IFG);
	regs_buff[15] = AT_READ_REG(hw, REG_MAC_STA_ADDR);
	regs_buff[16] = AT_READ_REG(hw, REG_MAC_STA_ADDR+4);
	regs_buff[17] = AT_READ_REG(hw, REG_RX_HASH_TABLE);
	regs_buff[18] = AT_READ_REG(hw, REG_RX_HASH_TABLE+4);
	regs_buff[19] = AT_READ_REG(hw, REG_MAC_HALF_DUPLX_CTRL);
	regs_buff[20] = AT_READ_REG(hw, REG_MTU);
	regs_buff[21] = AT_READ_REG(hw, REG_WOL_CTRL);
	regs_buff[22] = AT_READ_REG(hw, REG_SRAM_TRD_ADDR);
	regs_buff[23] = AT_READ_REG(hw, REG_SRAM_TRD_LEN);
	regs_buff[24] = AT_READ_REG(hw, REG_SRAM_RXF_ADDR);
	regs_buff[25] = AT_READ_REG(hw, REG_SRAM_RXF_LEN);
	regs_buff[26] = AT_READ_REG(hw, REG_SRAM_TXF_ADDR);
	regs_buff[27] = AT_READ_REG(hw, REG_SRAM_TXF_LEN);
	regs_buff[28] = AT_READ_REG(hw, REG_SRAM_TCPH_ADDR);
	regs_buff[29] = AT_READ_REG(hw, REG_SRAM_PKTH_ADDR);

	atl1e_पढ़ो_phy_reg(hw, MII_BMCR, &phy_data);
	regs_buff[73] = (u32)phy_data;
	atl1e_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
	regs_buff[74] = (u32)phy_data;
पूर्ण

अटल पूर्णांक atl1e_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);

	अगर (!atl1e_check_eeprom_exist(&adapter->hw))
		वापस AT_EEPROM_LEN;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक atl1e_get_eeprom(काष्ठा net_device *netdev,
		काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1e_hw *hw = &adapter->hw;
	u32 *eeprom_buff;
	पूर्णांक first_dword, last_dword;
	पूर्णांक ret_val = 0;
	पूर्णांक i;

	अगर (eeprom->len == 0)
		वापस -EINVAL;

	अगर (atl1e_check_eeprom_exist(hw)) /* not exist */
		वापस -EINVAL;

	eeprom->magic = hw->venकरोr_id | (hw->device_id << 16);

	first_dword = eeprom->offset >> 2;
	last_dword = (eeprom->offset + eeprom->len - 1) >> 2;

	eeprom_buff = kदो_स्मृति_array(last_dword - first_dword + 1, माप(u32),
				    GFP_KERNEL);
	अगर (eeprom_buff == शून्य)
		वापस -ENOMEM;

	क्रम (i = first_dword; i < last_dword; i++) अणु
		अगर (!atl1e_पढ़ो_eeprom(hw, i * 4, &(eeprom_buff[i-first_dword]))) अणु
			kमुक्त(eeprom_buff);
			वापस -EIO;
		पूर्ण
	पूर्ण

	स_नकल(bytes, (u8 *)eeprom_buff + (eeprom->offset & 3),
			eeprom->len);
	kमुक्त(eeprom_buff);

	वापस ret_val;
पूर्ण

अटल पूर्णांक atl1e_set_eeprom(काष्ठा net_device *netdev,
			    काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1e_hw *hw = &adapter->hw;
	u32 *eeprom_buff;
	u32 *ptr;
	पूर्णांक first_dword, last_dword;
	पूर्णांक ret_val = 0;
	पूर्णांक i;

	अगर (eeprom->len == 0)
		वापस -EOPNOTSUPP;

	अगर (eeprom->magic != (hw->venकरोr_id | (hw->device_id << 16)))
		वापस -EINVAL;

	first_dword = eeprom->offset >> 2;
	last_dword = (eeprom->offset + eeprom->len - 1) >> 2;
	eeprom_buff = kदो_स्मृति(AT_EEPROM_LEN, GFP_KERNEL);
	अगर (eeprom_buff == शून्य)
		वापस -ENOMEM;

	ptr = eeprom_buff;

	अगर (eeprom->offset & 3) अणु
		/* need पढ़ो/modअगरy/ग_लिखो of first changed EEPROM word */
		/* only the second byte of the word is being modअगरied */
		अगर (!atl1e_पढ़ो_eeprom(hw, first_dword * 4, &(eeprom_buff[0]))) अणु
			ret_val = -EIO;
			जाओ out;
		पूर्ण
		ptr++;
	पूर्ण
	अगर (((eeprom->offset + eeprom->len) & 3)) अणु
		/* need पढ़ो/modअगरy/ग_लिखो of last changed EEPROM word */
		/* only the first byte of the word is being modअगरied */

		अगर (!atl1e_पढ़ो_eeprom(hw, last_dword * 4,
				&(eeprom_buff[last_dword - first_dword]))) अणु
			ret_val = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Device's eeprom is always little-endian, word addressable */
	स_नकल(ptr, bytes, eeprom->len);

	क्रम (i = 0; i < last_dword - first_dword + 1; i++) अणु
		अगर (!atl1e_ग_लिखो_eeprom(hw, ((first_dword + i) * 4),
				  eeprom_buff[i])) अणु
			ret_val = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	kमुक्त(eeprom_buff);
	वापस ret_val;
पूर्ण

अटल व्योम atl1e_get_drvinfo(काष्ठा net_device *netdev,
		काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver,  atl1e_driver_name, माप(drvinfo->driver));
	strlcpy(drvinfo->fw_version, "L1e", माप(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल व्योम atl1e_get_wol(काष्ठा net_device *netdev,
			  काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);

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

अटल पूर्णांक atl1e_set_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);

	अगर (wol->wolopts & (WAKE_ARP | WAKE_MAGICSECURE |
			    WAKE_UCAST | WAKE_MCAST | WAKE_BCAST))
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

अटल पूर्णांक atl1e_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	अगर (netअगर_running(netdev))
		atl1e_reinit_locked(adapter);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops atl1e_ethtool_ops = अणु
	.get_drvinfo            = atl1e_get_drvinfo,
	.get_regs_len           = atl1e_get_regs_len,
	.get_regs               = atl1e_get_regs,
	.get_wol                = atl1e_get_wol,
	.set_wol                = atl1e_set_wol,
	.get_msglevel           = atl1e_get_msglevel,
	.nway_reset             = atl1e_nway_reset,
	.get_link               = ethtool_op_get_link,
	.get_eeprom_len         = atl1e_get_eeprom_len,
	.get_eeprom             = atl1e_get_eeprom,
	.set_eeprom             = atl1e_set_eeprom,
	.get_link_ksettings     = atl1e_get_link_ksettings,
	.set_link_ksettings     = atl1e_set_link_ksettings,
पूर्ण;

व्योम atl1e_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &atl1e_ethtool_ops;
पूर्ण
