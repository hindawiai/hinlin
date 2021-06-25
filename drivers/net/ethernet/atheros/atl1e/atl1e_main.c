<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 2007 Atheros Corporation. All rights reserved.
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 */

#समावेश "atl1e.h"

अक्षर atl1e_driver_name[] = "ATL1E";
#घोषणा PCI_DEVICE_ID_ATTANSIC_L1E      0x1026
/*
 * atl1e_pci_tbl - PCI Device ID Table
 *
 * Wildcard entries (PCI_ANY_ID) should come last
 * Last entry must be all 0s
 *
 * अणु Venकरोr ID, Device ID, SubVenकरोr ID, SubDevice ID,
 *   Class, Class Mask, निजी data (not used) पूर्ण
 */
अटल स्थिर काष्ठा pci_device_id atl1e_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_ATTANSIC, PCI_DEVICE_ID_ATTANSIC_L1E)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ATTANSIC, 0x1066)पूर्ण,
	/* required last entry */
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, atl1e_pci_tbl);

MODULE_AUTHOR("Atheros Corporation, <xiong.huang@atheros.com>, Jie Yang <jie.yang@atheros.com>");
MODULE_DESCRIPTION("Atheros 1000M Ethernet Network Driver");
MODULE_LICENSE("GPL");

अटल व्योम atl1e_setup_mac_ctrl(काष्ठा atl1e_adapter *adapter);

अटल स्थिर u16
atl1e_rx_page_vld_regs[AT_MAX_RECEIVE_QUEUE][AT_PAGE_NUM_PER_QUEUE] =
अणु
	अणुREG_HOST_RXF0_PAGE0_VLD, REG_HOST_RXF0_PAGE1_VLDपूर्ण,
	अणुREG_HOST_RXF1_PAGE0_VLD, REG_HOST_RXF1_PAGE1_VLDपूर्ण,
	अणुREG_HOST_RXF2_PAGE0_VLD, REG_HOST_RXF2_PAGE1_VLDपूर्ण,
	अणुREG_HOST_RXF3_PAGE0_VLD, REG_HOST_RXF3_PAGE1_VLDपूर्ण
पूर्ण;

अटल स्थिर u16 atl1e_rx_page_hi_addr_regs[AT_MAX_RECEIVE_QUEUE] =
अणु
	REG_RXF0_BASE_ADDR_HI,
	REG_RXF1_BASE_ADDR_HI,
	REG_RXF2_BASE_ADDR_HI,
	REG_RXF3_BASE_ADDR_HI
पूर्ण;

अटल स्थिर u16
atl1e_rx_page_lo_addr_regs[AT_MAX_RECEIVE_QUEUE][AT_PAGE_NUM_PER_QUEUE] =
अणु
	अणुREG_HOST_RXF0_PAGE0_LO, REG_HOST_RXF0_PAGE1_LOपूर्ण,
	अणुREG_HOST_RXF1_PAGE0_LO, REG_HOST_RXF1_PAGE1_LOपूर्ण,
	अणुREG_HOST_RXF2_PAGE0_LO, REG_HOST_RXF2_PAGE1_LOपूर्ण,
	अणुREG_HOST_RXF3_PAGE0_LO, REG_HOST_RXF3_PAGE1_LOपूर्ण
पूर्ण;

अटल स्थिर u16
atl1e_rx_page_ग_लिखो_offset_regs[AT_MAX_RECEIVE_QUEUE][AT_PAGE_NUM_PER_QUEUE] =
अणु
	अणुREG_HOST_RXF0_MB0_LO,  REG_HOST_RXF0_MB1_LOपूर्ण,
	अणुREG_HOST_RXF1_MB0_LO,  REG_HOST_RXF1_MB1_LOपूर्ण,
	अणुREG_HOST_RXF2_MB0_LO,  REG_HOST_RXF2_MB1_LOपूर्ण,
	अणुREG_HOST_RXF3_MB0_LO,  REG_HOST_RXF3_MB1_LOपूर्ण
पूर्ण;

अटल स्थिर u16 atl1e_pay_load_size[] = अणु
	128, 256, 512, 1024, 2048, 4096,
पूर्ण;

/**
 * atl1e_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 * @adapter: board निजी काष्ठाure
 */
अटल अंतरभूत व्योम atl1e_irq_enable(काष्ठा atl1e_adapter *adapter)
अणु
	अगर (likely(atomic_dec_and_test(&adapter->irq_sem))) अणु
		AT_WRITE_REG(&adapter->hw, REG_ISR, 0);
		AT_WRITE_REG(&adapter->hw, REG_IMR, IMR_NORMAL_MASK);
		AT_WRITE_FLUSH(&adapter->hw);
	पूर्ण
पूर्ण

/**
 * atl1e_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 * @adapter: board निजी काष्ठाure
 */
अटल अंतरभूत व्योम atl1e_irq_disable(काष्ठा atl1e_adapter *adapter)
अणु
	atomic_inc(&adapter->irq_sem);
	AT_WRITE_REG(&adapter->hw, REG_IMR, 0);
	AT_WRITE_FLUSH(&adapter->hw);
	synchronize_irq(adapter->pdev->irq);
पूर्ण

/**
 * atl1e_irq_reset - reset पूर्णांकerrupt confiure on the NIC
 * @adapter: board निजी काष्ठाure
 */
अटल अंतरभूत व्योम atl1e_irq_reset(काष्ठा atl1e_adapter *adapter)
अणु
	atomic_set(&adapter->irq_sem, 0);
	AT_WRITE_REG(&adapter->hw, REG_ISR, 0);
	AT_WRITE_REG(&adapter->hw, REG_IMR, 0);
	AT_WRITE_FLUSH(&adapter->hw);
पूर्ण

/**
 * atl1e_phy_config - Timer Call-back
 * @t: समयr list containing poपूर्णांकer to netdev cast पूर्णांकo an अचिन्हित दीर्घ
 */
अटल व्योम atl1e_phy_config(काष्ठा समयr_list *t)
अणु
	काष्ठा atl1e_adapter *adapter = from_समयr(adapter, t,
						   phy_config_समयr);
	काष्ठा atl1e_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adapter->mdio_lock, flags);
	atl1e_restart_स्वतःneg(hw);
	spin_unlock_irqrestore(&adapter->mdio_lock, flags);
पूर्ण

व्योम atl1e_reinit_locked(काष्ठा atl1e_adapter *adapter)
अणु
	जबतक (test_and_set_bit(__AT_RESETTING, &adapter->flags))
		msleep(1);
	atl1e_करोwn(adapter);
	atl1e_up(adapter);
	clear_bit(__AT_RESETTING, &adapter->flags);
पूर्ण

अटल व्योम atl1e_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा atl1e_adapter *adapter;
	adapter = container_of(work, काष्ठा atl1e_adapter, reset_task);

	atl1e_reinit_locked(adapter);
पूर्ण

अटल पूर्णांक atl1e_check_link(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा atl1e_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err = 0;
	u16 speed, duplex, phy_data;

	/* MII_BMSR must पढ़ो twice */
	atl1e_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
	atl1e_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
	अगर ((phy_data & BMSR_LSTATUS) == 0) अणु
		/* link करोwn */
		अगर (netअगर_carrier_ok(netdev)) अणु /* old link state: Up */
			u32 value;
			/* disable rx */
			value = AT_READ_REG(hw, REG_MAC_CTRL);
			value &= ~MAC_CTRL_RX_EN;
			AT_WRITE_REG(hw, REG_MAC_CTRL, value);
			adapter->link_speed = SPEED_0;
			netअगर_carrier_off(netdev);
			netअगर_stop_queue(netdev);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Link Up */
		err = atl1e_get_speed_and_duplex(hw, &speed, &duplex);
		अगर (unlikely(err))
			वापस err;

		/* link result is our setting */
		अगर (adapter->link_speed != speed ||
		    adapter->link_duplex != duplex) अणु
			adapter->link_speed  = speed;
			adapter->link_duplex = duplex;
			atl1e_setup_mac_ctrl(adapter);
			netdev_info(netdev,
				    "NIC Link is Up <%d Mbps %s Duplex>\n",
				    adapter->link_speed,
				    adapter->link_duplex == FULL_DUPLEX ?
				    "Full" : "Half");
		पूर्ण

		अगर (!netअगर_carrier_ok(netdev)) अणु
			/* Link करोwn -> Up */
			netअगर_carrier_on(netdev);
			netअगर_wake_queue(netdev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * atl1e_link_chg_task - deal with link change event Out of पूर्णांकerrupt context
 * @work: work काष्ठा with driver info
 */
अटल व्योम atl1e_link_chg_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा atl1e_adapter *adapter;
	अचिन्हित दीर्घ flags;

	adapter = container_of(work, काष्ठा atl1e_adapter, link_chg_task);
	spin_lock_irqsave(&adapter->mdio_lock, flags);
	atl1e_check_link(adapter);
	spin_unlock_irqrestore(&adapter->mdio_lock, flags);
पूर्ण

अटल व्योम atl1e_link_chg_event(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	u16 phy_data = 0;
	u16 link_up = 0;

	spin_lock(&adapter->mdio_lock);
	atl1e_पढ़ो_phy_reg(&adapter->hw, MII_BMSR, &phy_data);
	atl1e_पढ़ो_phy_reg(&adapter->hw, MII_BMSR, &phy_data);
	spin_unlock(&adapter->mdio_lock);
	link_up = phy_data & BMSR_LSTATUS;
	/* notअगरy upper layer link करोwn ASAP */
	अगर (!link_up) अणु
		अगर (netअगर_carrier_ok(netdev)) अणु
			/* old link state: Up */
			netdev_info(netdev, "NIC Link is Down\n");
			adapter->link_speed = SPEED_0;
			netअगर_stop_queue(netdev);
		पूर्ण
	पूर्ण
	schedule_work(&adapter->link_chg_task);
पूर्ण

अटल व्योम atl1e_del_समयr(काष्ठा atl1e_adapter *adapter)
अणु
	del_समयr_sync(&adapter->phy_config_समयr);
पूर्ण

अटल व्योम atl1e_cancel_work(काष्ठा atl1e_adapter *adapter)
अणु
	cancel_work_sync(&adapter->reset_task);
	cancel_work_sync(&adapter->link_chg_task);
पूर्ण

/**
 * atl1e_tx_समयout - Respond to a Tx Hang
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @txqueue: the index of the hanging queue
 */
अटल व्योम atl1e_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);

	/* Do the reset outside of पूर्णांकerrupt context */
	schedule_work(&adapter->reset_task);
पूर्ण

/**
 * atl1e_set_multi - Multicast and Promiscuous mode set
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The set_multi entry poपूर्णांक is called whenever the multicast address
 * list or the network पूर्णांकerface flags are updated.  This routine is
 * responsible क्रम configuring the hardware क्रम proper multicast,
 * promiscuous mode, and all-multi behavior.
 */
अटल व्योम atl1e_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1e_hw *hw = &adapter->hw;
	काष्ठा netdev_hw_addr *ha;
	u32 mac_ctrl_data = 0;
	u32 hash_value;

	/* Check क्रम Promiscuous and All Multicast modes */
	mac_ctrl_data = AT_READ_REG(hw, REG_MAC_CTRL);

	अगर (netdev->flags & IFF_PROMISC) अणु
		mac_ctrl_data |= MAC_CTRL_PROMIS_EN;
	पूर्ण अन्यथा अगर (netdev->flags & IFF_ALLMULTI) अणु
		mac_ctrl_data |= MAC_CTRL_MC_ALL_EN;
		mac_ctrl_data &= ~MAC_CTRL_PROMIS_EN;
	पूर्ण अन्यथा अणु
		mac_ctrl_data &= ~(MAC_CTRL_PROMIS_EN | MAC_CTRL_MC_ALL_EN);
	पूर्ण

	AT_WRITE_REG(hw, REG_MAC_CTRL, mac_ctrl_data);

	/* clear the old settings from the multicast hash table */
	AT_WRITE_REG(hw, REG_RX_HASH_TABLE, 0);
	AT_WRITE_REG_ARRAY(hw, REG_RX_HASH_TABLE, 1, 0);

	/* comoute mc addresses' hash value ,and put it पूर्णांकo hash table */
	netdev_क्रम_each_mc_addr(ha, netdev) अणु
		hash_value = atl1e_hash_mc_addr(hw, ha->addr);
		atl1e_hash_set(hw, hash_value);
	पूर्ण
पूर्ण

अटल व्योम __atl1e_rx_mode(netdev_features_t features, u32 *mac_ctrl_data)
अणु

	अगर (features & NETIF_F_RXALL) अणु
		/* enable RX of ALL frames */
		*mac_ctrl_data |= MAC_CTRL_DBG;
	पूर्ण अन्यथा अणु
		/* disable RX of ALL frames */
		*mac_ctrl_data &= ~MAC_CTRL_DBG;
	पूर्ण
पूर्ण

अटल व्योम atl1e_rx_mode(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	u32 mac_ctrl_data = 0;

	netdev_dbg(adapter->netdev, "%s\n", __func__);

	atl1e_irq_disable(adapter);
	mac_ctrl_data = AT_READ_REG(&adapter->hw, REG_MAC_CTRL);
	__atl1e_rx_mode(features, &mac_ctrl_data);
	AT_WRITE_REG(&adapter->hw, REG_MAC_CTRL, mac_ctrl_data);
	atl1e_irq_enable(adapter);
पूर्ण


अटल व्योम __atl1e_vlan_mode(netdev_features_t features, u32 *mac_ctrl_data)
अणु
	अगर (features & NETIF_F_HW_VLAN_CTAG_RX) अणु
		/* enable VLAN tag insert/strip */
		*mac_ctrl_data |= MAC_CTRL_RMV_VLAN;
	पूर्ण अन्यथा अणु
		/* disable VLAN tag insert/strip */
		*mac_ctrl_data &= ~MAC_CTRL_RMV_VLAN;
	पूर्ण
पूर्ण

अटल व्योम atl1e_vlan_mode(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	u32 mac_ctrl_data = 0;

	netdev_dbg(adapter->netdev, "%s\n", __func__);

	atl1e_irq_disable(adapter);
	mac_ctrl_data = AT_READ_REG(&adapter->hw, REG_MAC_CTRL);
	__atl1e_vlan_mode(features, &mac_ctrl_data);
	AT_WRITE_REG(&adapter->hw, REG_MAC_CTRL, mac_ctrl_data);
	atl1e_irq_enable(adapter);
पूर्ण

अटल व्योम atl1e_restore_vlan(काष्ठा atl1e_adapter *adapter)
अणु
	netdev_dbg(adapter->netdev, "%s\n", __func__);
	atl1e_vlan_mode(adapter->netdev, adapter->netdev->features);
पूर्ण

/**
 * atl1e_set_mac - Change the Ethernet Address of the NIC
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @p: poपूर्णांकer to an address काष्ठाure
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक atl1e_set_mac_addr(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (netअगर_running(netdev))
		वापस -EBUSY;

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	स_नकल(adapter->hw.mac_addr, addr->sa_data, netdev->addr_len);

	atl1e_hw_set_mac_addr(&adapter->hw);

	वापस 0;
पूर्ण

अटल netdev_features_t atl1e_fix_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	/*
	 * Since there is no support क्रम separate rx/tx vlan accel
	 * enable/disable make sure tx flag is always in same state as rx.
	 */
	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		features |= NETIF_F_HW_VLAN_CTAG_TX;
	अन्यथा
		features &= ~NETIF_F_HW_VLAN_CTAG_TX;

	वापस features;
पूर्ण

अटल पूर्णांक atl1e_set_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	netdev_features_t changed = netdev->features ^ features;

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX)
		atl1e_vlan_mode(netdev, features);

	अगर (changed & NETIF_F_RXALL)
		atl1e_rx_mode(netdev, features);


	वापस 0;
पूर्ण

/**
 * atl1e_change_mtu - Change the Maximum Transfer Unit
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक atl1e_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	पूर्णांक max_frame = new_mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;

	/* set MTU */
	अगर (netअगर_running(netdev)) अणु
		जबतक (test_and_set_bit(__AT_RESETTING, &adapter->flags))
			msleep(1);
		netdev->mtu = new_mtu;
		adapter->hw.max_frame_size = new_mtu;
		adapter->hw.rx_jumbo_th = (max_frame + 7) >> 3;
		atl1e_करोwn(adapter);
		atl1e_up(adapter);
		clear_bit(__AT_RESETTING, &adapter->flags);
	पूर्ण
	वापस 0;
पूर्ण

/*
 *  caller should hold mdio_lock
 */
अटल पूर्णांक atl1e_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक reg_num)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	u16 result;

	atl1e_पढ़ो_phy_reg(&adapter->hw, reg_num & MDIO_REG_ADDR_MASK, &result);
	वापस result;
पूर्ण

अटल व्योम atl1e_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक phy_id,
			     पूर्णांक reg_num, पूर्णांक val)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);

	अगर (atl1e_ग_लिखो_phy_reg(&adapter->hw,
				reg_num & MDIO_REG_ADDR_MASK, val))
		netdev_err(netdev, "write phy register failed\n");
पूर्ण

अटल पूर्णांक atl1e_mii_ioctl(काष्ठा net_device *netdev,
			   काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	अगर (!netअगर_running(netdev))
		वापस -EINVAL;

	spin_lock_irqsave(&adapter->mdio_lock, flags);
	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		data->phy_id = 0;
		अवरोध;

	हाल SIOCGMIIREG:
		अगर (atl1e_पढ़ो_phy_reg(&adapter->hw, data->reg_num & 0x1F,
				    &data->val_out)) अणु
			retval = -EIO;
			जाओ out;
		पूर्ण
		अवरोध;

	हाल SIOCSMIIREG:
		अगर (data->reg_num & ~(0x1F)) अणु
			retval = -EFAULT;
			जाओ out;
		पूर्ण

		netdev_dbg(adapter->netdev, "<atl1e_mii_ioctl> write %x %x\n",
			   data->reg_num, data->val_in);
		अगर (atl1e_ग_लिखो_phy_reg(&adapter->hw,
				     data->reg_num, data->val_in)) अणु
			retval = -EIO;
			जाओ out;
		पूर्ण
		अवरोध;

	शेष:
		retval = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
out:
	spin_unlock_irqrestore(&adapter->mdio_lock, flags);
	वापस retval;

पूर्ण

अटल पूर्णांक atl1e_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
		वापस atl1e_mii_ioctl(netdev, अगरr, cmd);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम atl1e_setup_pcicmd(काष्ठा pci_dev *pdev)
अणु
	u16 cmd;

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);
	cmd &= ~(PCI_COMMAND_INTX_DISABLE | PCI_COMMAND_IO);
	cmd |=  (PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, cmd);

	/*
	 * some motherboards BIOS(PXE/EFI) driver may set PME
	 * जबतक they transfer control to OS (Winकरोws/Linux)
	 * so we should clear this bit beक्रमe NIC work normally
	 */
	pci_ग_लिखो_config_dword(pdev, REG_PM_CTRLSTAT, 0);
	msleep(1);
पूर्ण

/**
 * atl1e_alloc_queues - Allocate memory क्रम all rings
 * @adapter: board निजी काष्ठाure to initialize
 *
 */
अटल पूर्णांक atl1e_alloc_queues(काष्ठा atl1e_adapter *adapter)
अणु
	वापस 0;
पूर्ण

/**
 * atl1e_sw_init - Initialize general software काष्ठाures (काष्ठा atl1e_adapter)
 * @adapter: board निजी काष्ठाure to initialize
 *
 * atl1e_sw_init initializes the Adapter निजी data काष्ठाure.
 * Fields are initialized based on PCI device inक्रमmation and
 * OS network device settings (MTU size).
 */
अटल पूर्णांक atl1e_sw_init(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा atl1e_hw *hw   = &adapter->hw;
	काष्ठा pci_dev	*pdev = adapter->pdev;
	u32 phy_status_data = 0;

	adapter->wol = 0;
	adapter->link_speed = SPEED_0;   /* hardware init */
	adapter->link_duplex = FULL_DUPLEX;
	adapter->num_rx_queues = 1;

	/* PCI config space info */
	hw->venकरोr_id = pdev->venकरोr;
	hw->device_id = pdev->device;
	hw->subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	hw->subप्रणाली_id = pdev->subप्रणाली_device;
	hw->revision_id  = pdev->revision;

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &hw->pci_cmd_word);

	phy_status_data = AT_READ_REG(hw, REG_PHY_STATUS);
	/* nic type */
	अगर (hw->revision_id >= 0xF0) अणु
		hw->nic_type = athr_l2e_revB;
	पूर्ण अन्यथा अणु
		अगर (phy_status_data & PHY_STATUS_100M)
			hw->nic_type = athr_l1e;
		अन्यथा
			hw->nic_type = athr_l2e_revA;
	पूर्ण

	phy_status_data = AT_READ_REG(hw, REG_PHY_STATUS);

	अगर (phy_status_data & PHY_STATUS_EMI_CA)
		hw->emi_ca = true;
	अन्यथा
		hw->emi_ca = false;

	hw->phy_configured = false;
	hw->preamble_len = 7;
	hw->max_frame_size = adapter->netdev->mtu;
	hw->rx_jumbo_th = (hw->max_frame_size + ETH_HLEN +
				VLAN_HLEN + ETH_FCS_LEN + 7) >> 3;

	hw->rrs_type = atl1e_rrs_disable;
	hw->indirect_tab = 0;
	hw->base_cpu = 0;

	/* need confirm */

	hw->ict = 50000;                 /* 100ms */
	hw->smb_समयr = 200000;          /* 200ms  */
	hw->tpd_burst = 5;
	hw->rrd_thresh = 1;
	hw->tpd_thresh = adapter->tx_ring.count / 2;
	hw->rx_count_करोwn = 4;  /* 2us resolution */
	hw->tx_count_करोwn = hw->imt * 4 / 3;
	hw->dmar_block = atl1e_dma_req_1024;
	hw->dmaw_block = atl1e_dma_req_1024;
	hw->dmar_dly_cnt = 15;
	hw->dmaw_dly_cnt = 4;

	अगर (atl1e_alloc_queues(adapter)) अणु
		netdev_err(adapter->netdev, "Unable to allocate memory for queues\n");
		वापस -ENOMEM;
	पूर्ण

	atomic_set(&adapter->irq_sem, 1);
	spin_lock_init(&adapter->mdio_lock);

	set_bit(__AT_DOWN, &adapter->flags);

	वापस 0;
पूर्ण

/**
 * atl1e_clean_tx_ring - Free Tx-skb
 * @adapter: board निजी काष्ठाure
 */
अटल व्योम atl1e_clean_tx_ring(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा atl1e_tx_ring *tx_ring = &adapter->tx_ring;
	काष्ठा atl1e_tx_buffer *tx_buffer = शून्य;
	काष्ठा pci_dev *pdev = adapter->pdev;
	u16 index, ring_count;

	अगर (tx_ring->desc == शून्य || tx_ring->tx_buffer == शून्य)
		वापस;

	ring_count = tx_ring->count;
	/* first unmmap dma */
	क्रम (index = 0; index < ring_count; index++) अणु
		tx_buffer = &tx_ring->tx_buffer[index];
		अगर (tx_buffer->dma) अणु
			अगर (tx_buffer->flags & ATL1E_TX_PCIMAP_SINGLE)
				dma_unmap_single(&pdev->dev, tx_buffer->dma,
						 tx_buffer->length,
						 DMA_TO_DEVICE);
			अन्यथा अगर (tx_buffer->flags & ATL1E_TX_PCIMAP_PAGE)
				dma_unmap_page(&pdev->dev, tx_buffer->dma,
					       tx_buffer->length,
					       DMA_TO_DEVICE);
			tx_buffer->dma = 0;
		पूर्ण
	पूर्ण
	/* second मुक्त skb */
	क्रम (index = 0; index < ring_count; index++) अणु
		tx_buffer = &tx_ring->tx_buffer[index];
		अगर (tx_buffer->skb) अणु
			dev_kमुक्त_skb_any(tx_buffer->skb);
			tx_buffer->skb = शून्य;
		पूर्ण
	पूर्ण
	/* Zero out Tx-buffers */
	स_रखो(tx_ring->desc, 0, माप(काष्ठा atl1e_tpd_desc) *
				ring_count);
	स_रखो(tx_ring->tx_buffer, 0, माप(काष्ठा atl1e_tx_buffer) *
				ring_count);
पूर्ण

/**
 * atl1e_clean_rx_ring - Free rx-reservation skbs
 * @adapter: board निजी काष्ठाure
 */
अटल व्योम atl1e_clean_rx_ring(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा atl1e_rx_ring *rx_ring =
		&adapter->rx_ring;
	काष्ठा atl1e_rx_page_desc *rx_page_desc = rx_ring->rx_page_desc;
	u16 i, j;


	अगर (adapter->ring_vir_addr == शून्य)
		वापस;
	/* Zero out the descriptor ring */
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		क्रम (j = 0; j < AT_PAGE_NUM_PER_QUEUE; j++) अणु
			अगर (rx_page_desc[i].rx_page[j].addr != शून्य) अणु
				स_रखो(rx_page_desc[i].rx_page[j].addr, 0,
						rx_ring->real_page_size);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम atl1e_cal_ring_size(काष्ठा atl1e_adapter *adapter, u32 *ring_size)
अणु
	*ring_size = ((u32)(adapter->tx_ring.count *
		     माप(काष्ठा atl1e_tpd_desc) + 7
			/* tx ring, qword align */
		     + adapter->rx_ring.real_page_size * AT_PAGE_NUM_PER_QUEUE *
			adapter->num_rx_queues + 31
			/* rx ring,  32 bytes align */
		     + (1 + AT_PAGE_NUM_PER_QUEUE * adapter->num_rx_queues) *
			माप(u32) + 3));
			/* tx, rx cmd, dword align   */
पूर्ण

अटल व्योम atl1e_init_ring_resources(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा atl1e_rx_ring *rx_ring = शून्य;

	rx_ring = &adapter->rx_ring;

	rx_ring->real_page_size = adapter->rx_ring.page_size
				 + adapter->hw.max_frame_size
				 + ETH_HLEN + VLAN_HLEN
				 + ETH_FCS_LEN;
	rx_ring->real_page_size = roundup(rx_ring->real_page_size, 32);
	atl1e_cal_ring_size(adapter, &adapter->ring_size);

	adapter->ring_vir_addr = शून्य;
	adapter->rx_ring.desc = शून्य;
	rwlock_init(&adapter->tx_ring.tx_lock);
पूर्ण

/*
 * Read / Write Ptr Initialize:
 */
अटल व्योम atl1e_init_ring_ptrs(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा atl1e_tx_ring *tx_ring = शून्य;
	काष्ठा atl1e_rx_ring *rx_ring = शून्य;
	काष्ठा atl1e_rx_page_desc *rx_page_desc = शून्य;
	पूर्णांक i, j;

	tx_ring = &adapter->tx_ring;
	rx_ring = &adapter->rx_ring;
	rx_page_desc = rx_ring->rx_page_desc;

	tx_ring->next_to_use = 0;
	atomic_set(&tx_ring->next_to_clean, 0);

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		rx_page_desc[i].rx_using  = 0;
		rx_page_desc[i].rx_nxseq = 0;
		क्रम (j = 0; j < AT_PAGE_NUM_PER_QUEUE; j++) अणु
			*rx_page_desc[i].rx_page[j].ग_लिखो_offset_addr = 0;
			rx_page_desc[i].rx_page[j].पढ़ो_offset = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * atl1e_मुक्त_ring_resources - Free Tx / RX descriptor Resources
 * @adapter: board निजी काष्ठाure
 *
 * Free all transmit software resources
 */
अटल व्योम atl1e_मुक्त_ring_resources(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;

	atl1e_clean_tx_ring(adapter);
	atl1e_clean_rx_ring(adapter);

	अगर (adapter->ring_vir_addr) अणु
		dma_मुक्त_coherent(&pdev->dev, adapter->ring_size,
				  adapter->ring_vir_addr, adapter->ring_dma);
		adapter->ring_vir_addr = शून्य;
	पूर्ण

	अगर (adapter->tx_ring.tx_buffer) अणु
		kमुक्त(adapter->tx_ring.tx_buffer);
		adapter->tx_ring.tx_buffer = शून्य;
	पूर्ण
पूर्ण

/**
 * atl1e_setup_mem_resources - allocate Tx / RX descriptor resources
 * @adapter: board निजी काष्ठाure
 *
 * Return 0 on success, negative on failure
 */
अटल पूर्णांक atl1e_setup_ring_resources(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा atl1e_tx_ring *tx_ring;
	काष्ठा atl1e_rx_ring *rx_ring;
	काष्ठा atl1e_rx_page_desc  *rx_page_desc;
	पूर्णांक size, i, j;
	u32 offset = 0;
	पूर्णांक err = 0;

	अगर (adapter->ring_vir_addr != शून्य)
		वापस 0; /* alloced alपढ़ोy */

	tx_ring = &adapter->tx_ring;
	rx_ring = &adapter->rx_ring;

	/* real ring DMA buffer */

	size = adapter->ring_size;
	adapter->ring_vir_addr = dma_alloc_coherent(&pdev->dev,
						    adapter->ring_size,
						    &adapter->ring_dma, GFP_KERNEL);
	अगर (adapter->ring_vir_addr == शून्य) अणु
		netdev_err(adapter->netdev,
			   "dma_alloc_coherent failed, size = D%d\n", size);
		वापस -ENOMEM;
	पूर्ण

	rx_page_desc = rx_ring->rx_page_desc;

	/* Init TPD Ring */
	tx_ring->dma = roundup(adapter->ring_dma, 8);
	offset = tx_ring->dma - adapter->ring_dma;
	tx_ring->desc = adapter->ring_vir_addr + offset;
	size = माप(काष्ठा atl1e_tx_buffer) * (tx_ring->count);
	tx_ring->tx_buffer = kzalloc(size, GFP_KERNEL);
	अगर (tx_ring->tx_buffer == शून्य) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	/* Init RXF-Pages */
	offset += (माप(काष्ठा atl1e_tpd_desc) * tx_ring->count);
	offset = roundup(offset, 32);

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		क्रम (j = 0; j < AT_PAGE_NUM_PER_QUEUE; j++) अणु
			rx_page_desc[i].rx_page[j].dma =
				adapter->ring_dma + offset;
			rx_page_desc[i].rx_page[j].addr =
				adapter->ring_vir_addr + offset;
			offset += rx_ring->real_page_size;
		पूर्ण
	पूर्ण

	/* Init CMB dma address */
	tx_ring->cmb_dma = adapter->ring_dma + offset;
	tx_ring->cmb = adapter->ring_vir_addr + offset;
	offset += माप(u32);

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		क्रम (j = 0; j < AT_PAGE_NUM_PER_QUEUE; j++) अणु
			rx_page_desc[i].rx_page[j].ग_लिखो_offset_dma =
				adapter->ring_dma + offset;
			rx_page_desc[i].rx_page[j].ग_लिखो_offset_addr =
				adapter->ring_vir_addr + offset;
			offset += माप(u32);
		पूर्ण
	पूर्ण

	अगर (unlikely(offset > adapter->ring_size)) अणु
		netdev_err(adapter->netdev, "offset(%d) > ring size(%d) !!\n",
			   offset, adapter->ring_size);
		err = -1;
		जाओ failed;
	पूर्ण

	वापस 0;
failed:
	अगर (adapter->ring_vir_addr != शून्य) अणु
		dma_मुक्त_coherent(&pdev->dev, adapter->ring_size,
				  adapter->ring_vir_addr, adapter->ring_dma);
		adapter->ring_vir_addr = शून्य;
	पूर्ण
	वापस err;
पूर्ण

अटल अंतरभूत व्योम atl1e_configure_des_ring(काष्ठा atl1e_adapter *adapter)
अणु

	काष्ठा atl1e_hw *hw = &adapter->hw;
	काष्ठा atl1e_rx_ring *rx_ring = &adapter->rx_ring;
	काष्ठा atl1e_tx_ring *tx_ring = &adapter->tx_ring;
	काष्ठा atl1e_rx_page_desc *rx_page_desc = शून्य;
	पूर्णांक i, j;

	AT_WRITE_REG(hw, REG_DESC_BASE_ADDR_HI,
			(u32)((adapter->ring_dma & AT_DMA_HI_ADDR_MASK) >> 32));
	AT_WRITE_REG(hw, REG_TPD_BASE_ADDR_LO,
			(u32)((tx_ring->dma) & AT_DMA_LO_ADDR_MASK));
	AT_WRITE_REG(hw, REG_TPD_RING_SIZE, (u16)(tx_ring->count));
	AT_WRITE_REG(hw, REG_HOST_TX_CMB_LO,
			(u32)((tx_ring->cmb_dma) & AT_DMA_LO_ADDR_MASK));

	rx_page_desc = rx_ring->rx_page_desc;
	/* RXF Page Physical address / Page Length */
	क्रम (i = 0; i < AT_MAX_RECEIVE_QUEUE; i++) अणु
		AT_WRITE_REG(hw, atl1e_rx_page_hi_addr_regs[i],
				 (u32)((adapter->ring_dma &
				 AT_DMA_HI_ADDR_MASK) >> 32));
		क्रम (j = 0; j < AT_PAGE_NUM_PER_QUEUE; j++) अणु
			u32 page_phy_addr;
			u32 offset_phy_addr;

			page_phy_addr = rx_page_desc[i].rx_page[j].dma;
			offset_phy_addr =
				   rx_page_desc[i].rx_page[j].ग_लिखो_offset_dma;

			AT_WRITE_REG(hw, atl1e_rx_page_lo_addr_regs[i][j],
					page_phy_addr & AT_DMA_LO_ADDR_MASK);
			AT_WRITE_REG(hw, atl1e_rx_page_ग_लिखो_offset_regs[i][j],
					offset_phy_addr & AT_DMA_LO_ADDR_MASK);
			AT_WRITE_REGB(hw, atl1e_rx_page_vld_regs[i][j], 1);
		पूर्ण
	पूर्ण
	/* Page Length */
	AT_WRITE_REG(hw, REG_HOST_RXFPAGE_SIZE, rx_ring->page_size);
	/* Load all of base address above */
	AT_WRITE_REG(hw, REG_LOAD_PTR, 1);
पूर्ण

अटल अंतरभूत व्योम atl1e_configure_tx(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा atl1e_hw *hw = &adapter->hw;
	u32 dev_ctrl_data = 0;
	u32 max_pay_load = 0;
	u32 jumbo_thresh = 0;
	u32 extra_size = 0;     /* Jumbo frame threshold in QWORD unit */

	/* configure TXQ param */
	अगर (hw->nic_type != athr_l2e_revB) अणु
		extra_size = ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN;
		अगर (hw->max_frame_size <= 1500) अणु
			jumbo_thresh = hw->max_frame_size + extra_size;
		पूर्ण अन्यथा अगर (hw->max_frame_size < 6*1024) अणु
			jumbo_thresh =
				(hw->max_frame_size + extra_size) * 2 / 3;
		पूर्ण अन्यथा अणु
			jumbo_thresh = (hw->max_frame_size + extra_size) / 2;
		पूर्ण
		AT_WRITE_REG(hw, REG_TX_EARLY_TH, (jumbo_thresh + 7) >> 3);
	पूर्ण

	dev_ctrl_data = AT_READ_REG(hw, REG_DEVICE_CTRL);

	max_pay_load  = ((dev_ctrl_data >> DEVICE_CTRL_MAX_PAYLOAD_SHIFT)) &
			DEVICE_CTRL_MAX_PAYLOAD_MASK;

	hw->dmaw_block = min_t(u32, max_pay_load, hw->dmaw_block);

	max_pay_load  = ((dev_ctrl_data >> DEVICE_CTRL_MAX_RREQ_SZ_SHIFT)) &
			DEVICE_CTRL_MAX_RREQ_SZ_MASK;
	hw->dmar_block = min_t(u32, max_pay_load, hw->dmar_block);

	अगर (hw->nic_type != athr_l2e_revB)
		AT_WRITE_REGW(hw, REG_TXQ_CTRL + 2,
			      atl1e_pay_load_size[hw->dmar_block]);
	/* enable TXQ */
	AT_WRITE_REGW(hw, REG_TXQ_CTRL,
			(((u16)hw->tpd_burst & TXQ_CTRL_NUM_TPD_BURST_MASK)
			 << TXQ_CTRL_NUM_TPD_BURST_SHIFT)
			| TXQ_CTRL_ENH_MODE | TXQ_CTRL_EN);
पूर्ण

अटल अंतरभूत व्योम atl1e_configure_rx(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा atl1e_hw *hw = &adapter->hw;
	u32 rxf_len  = 0;
	u32 rxf_low  = 0;
	u32 rxf_high = 0;
	u32 rxf_thresh_data = 0;
	u32 rxq_ctrl_data = 0;

	अगर (hw->nic_type != athr_l2e_revB) अणु
		AT_WRITE_REGW(hw, REG_RXQ_JMBOSZ_RRDTIM,
			      (u16)((hw->rx_jumbo_th & RXQ_JMBOSZ_TH_MASK) <<
			      RXQ_JMBOSZ_TH_SHIFT |
			      (1 & RXQ_JMBO_LKAH_MASK) <<
			      RXQ_JMBO_LKAH_SHIFT));

		rxf_len  = AT_READ_REG(hw, REG_SRAM_RXF_LEN);
		rxf_high = rxf_len * 4 / 5;
		rxf_low  = rxf_len / 5;
		rxf_thresh_data = ((rxf_high  & RXQ_RXF_PAUSE_TH_HI_MASK)
				  << RXQ_RXF_PAUSE_TH_HI_SHIFT) |
				  ((rxf_low & RXQ_RXF_PAUSE_TH_LO_MASK)
				  << RXQ_RXF_PAUSE_TH_LO_SHIFT);

		AT_WRITE_REG(hw, REG_RXQ_RXF_PAUSE_THRESH, rxf_thresh_data);
	पूर्ण

	/* RRS */
	AT_WRITE_REG(hw, REG_IDT_TABLE, hw->indirect_tab);
	AT_WRITE_REG(hw, REG_BASE_CPU_NUMBER, hw->base_cpu);

	अगर (hw->rrs_type & atl1e_rrs_ipv4)
		rxq_ctrl_data |= RXQ_CTRL_HASH_TYPE_IPV4;

	अगर (hw->rrs_type & atl1e_rrs_ipv4_tcp)
		rxq_ctrl_data |= RXQ_CTRL_HASH_TYPE_IPV4_TCP;

	अगर (hw->rrs_type & atl1e_rrs_ipv6)
		rxq_ctrl_data |= RXQ_CTRL_HASH_TYPE_IPV6;

	अगर (hw->rrs_type & atl1e_rrs_ipv6_tcp)
		rxq_ctrl_data |= RXQ_CTRL_HASH_TYPE_IPV6_TCP;

	अगर (hw->rrs_type != atl1e_rrs_disable)
		rxq_ctrl_data |=
			(RXQ_CTRL_HASH_ENABLE | RXQ_CTRL_RSS_MODE_MQUESINT);

	rxq_ctrl_data |= RXQ_CTRL_IPV6_XSUM_VERIFY_EN | RXQ_CTRL_PBA_ALIGN_32 |
			 RXQ_CTRL_CUT_THRU_EN | RXQ_CTRL_EN;

	AT_WRITE_REG(hw, REG_RXQ_CTRL, rxq_ctrl_data);
पूर्ण

अटल अंतरभूत व्योम atl1e_configure_dma(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा atl1e_hw *hw = &adapter->hw;
	u32 dma_ctrl_data = 0;

	dma_ctrl_data = DMA_CTRL_RXCMB_EN;
	dma_ctrl_data |= (((u32)hw->dmar_block) & DMA_CTRL_DMAR_BURST_LEN_MASK)
		<< DMA_CTRL_DMAR_BURST_LEN_SHIFT;
	dma_ctrl_data |= (((u32)hw->dmaw_block) & DMA_CTRL_DMAW_BURST_LEN_MASK)
		<< DMA_CTRL_DMAW_BURST_LEN_SHIFT;
	dma_ctrl_data |= DMA_CTRL_DMAR_REQ_PRI | DMA_CTRL_DMAR_OUT_ORDER;
	dma_ctrl_data |= (((u32)hw->dmar_dly_cnt) & DMA_CTRL_DMAR_DLY_CNT_MASK)
		<< DMA_CTRL_DMAR_DLY_CNT_SHIFT;
	dma_ctrl_data |= (((u32)hw->dmaw_dly_cnt) & DMA_CTRL_DMAW_DLY_CNT_MASK)
		<< DMA_CTRL_DMAW_DLY_CNT_SHIFT;

	AT_WRITE_REG(hw, REG_DMA_CTRL, dma_ctrl_data);
पूर्ण

अटल व्योम atl1e_setup_mac_ctrl(काष्ठा atl1e_adapter *adapter)
अणु
	u32 value;
	काष्ठा atl1e_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;

	/* Config MAC CTRL Register */
	value = MAC_CTRL_TX_EN |
		MAC_CTRL_RX_EN ;

	अगर (FULL_DUPLEX == adapter->link_duplex)
		value |= MAC_CTRL_DUPLX;

	value |= ((u32)((SPEED_1000 == adapter->link_speed) ?
			  MAC_CTRL_SPEED_1000 : MAC_CTRL_SPEED_10_100) <<
			  MAC_CTRL_SPEED_SHIFT);
	value |= (MAC_CTRL_TX_FLOW | MAC_CTRL_RX_FLOW);

	value |= (MAC_CTRL_ADD_CRC | MAC_CTRL_PAD);
	value |= (((u32)adapter->hw.preamble_len &
		  MAC_CTRL_PRMLEN_MASK) << MAC_CTRL_PRMLEN_SHIFT);

	__atl1e_vlan_mode(netdev->features, &value);

	value |= MAC_CTRL_BC_EN;
	अगर (netdev->flags & IFF_PROMISC)
		value |= MAC_CTRL_PROMIS_EN;
	अगर (netdev->flags & IFF_ALLMULTI)
		value |= MAC_CTRL_MC_ALL_EN;
	अगर (netdev->features & NETIF_F_RXALL)
		value |= MAC_CTRL_DBG;
	AT_WRITE_REG(hw, REG_MAC_CTRL, value);
पूर्ण

/**
 * atl1e_configure - Configure Transmit&Receive Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Tx /Rx unit of the MAC after a reset.
 */
अटल पूर्णांक atl1e_configure(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा atl1e_hw *hw = &adapter->hw;

	u32 पूर्णांकr_status_data = 0;

	/* clear पूर्णांकerrupt status */
	AT_WRITE_REG(hw, REG_ISR, ~0);

	/* 1. set MAC Address */
	atl1e_hw_set_mac_addr(hw);

	/* 2. Init the Multicast HASH table करोne by set_muti */

	/* 3. Clear any WOL status */
	AT_WRITE_REG(hw, REG_WOL_CTRL, 0);

	/* 4. Descripter Ring BaseMem/Length/Read ptr/Write ptr
	 *    TPD Ring/SMB/RXF0 Page CMBs, they use the same
	 *    High 32bits memory */
	atl1e_configure_des_ring(adapter);

	/* 5. set Interrupt Moderator Timer */
	AT_WRITE_REGW(hw, REG_IRQ_MODU_TIMER_INIT, hw->imt);
	AT_WRITE_REGW(hw, REG_IRQ_MODU_TIMER2_INIT, hw->imt);
	AT_WRITE_REG(hw, REG_MASTER_CTRL, MASTER_CTRL_LED_MODE |
			MASTER_CTRL_ITIMER_EN | MASTER_CTRL_ITIMER2_EN);

	/* 6. rx/tx threshold to trig पूर्णांकerrupt */
	AT_WRITE_REGW(hw, REG_TRIG_RRD_THRESH, hw->rrd_thresh);
	AT_WRITE_REGW(hw, REG_TRIG_TPD_THRESH, hw->tpd_thresh);
	AT_WRITE_REGW(hw, REG_TRIG_RXTIMER, hw->rx_count_करोwn);
	AT_WRITE_REGW(hw, REG_TRIG_TXTIMER, hw->tx_count_करोwn);

	/* 7. set Interrupt Clear Timer */
	AT_WRITE_REGW(hw, REG_CMBDISDMA_TIMER, hw->ict);

	/* 8. set MTU */
	AT_WRITE_REG(hw, REG_MTU, hw->max_frame_size + ETH_HLEN +
			VLAN_HLEN + ETH_FCS_LEN);

	/* 9. config TXQ early tx threshold */
	atl1e_configure_tx(adapter);

	/* 10. config RXQ */
	atl1e_configure_rx(adapter);

	/* 11. config  DMA Engine */
	atl1e_configure_dma(adapter);

	/* 12. smb समयr to trig पूर्णांकerrupt */
	AT_WRITE_REG(hw, REG_SMB_STAT_TIMER, hw->smb_समयr);

	पूर्णांकr_status_data = AT_READ_REG(hw, REG_ISR);
	अगर (unlikely((पूर्णांकr_status_data & ISR_PHY_LINKDOWN) != 0)) अणु
		netdev_err(adapter->netdev,
			   "atl1e_configure failed, PCIE phy link down\n");
		वापस -1;
	पूर्ण

	AT_WRITE_REG(hw, REG_ISR, 0x7fffffff);
	वापस 0;
पूर्ण

/**
 * atl1e_get_stats - Get System Network Statistics
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns the address of the device statistics काष्ठाure.
 * The statistics are actually updated from the समयr callback.
 */
अटल काष्ठा net_device_stats *atl1e_get_stats(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1e_hw_stats  *hw_stats = &adapter->hw_stats;
	काष्ठा net_device_stats *net_stats = &netdev->stats;

	net_stats->rx_bytes   = hw_stats->rx_byte_cnt;
	net_stats->tx_bytes   = hw_stats->tx_byte_cnt;
	net_stats->multicast  = hw_stats->rx_mcast;
	net_stats->collisions = hw_stats->tx_1_col +
				hw_stats->tx_2_col +
				hw_stats->tx_late_col +
				hw_stats->tx_पात_col;

	net_stats->rx_errors  = hw_stats->rx_frag +
				hw_stats->rx_fcs_err +
				hw_stats->rx_len_err +
				hw_stats->rx_sz_ov +
				hw_stats->rx_rrd_ov +
				hw_stats->rx_align_err +
				hw_stats->rx_rxf_ov;

	net_stats->rx_fअगरo_errors   = hw_stats->rx_rxf_ov;
	net_stats->rx_length_errors = hw_stats->rx_len_err;
	net_stats->rx_crc_errors    = hw_stats->rx_fcs_err;
	net_stats->rx_frame_errors  = hw_stats->rx_align_err;
	net_stats->rx_dropped       = hw_stats->rx_rrd_ov;

	net_stats->tx_errors = hw_stats->tx_late_col +
			       hw_stats->tx_पात_col +
			       hw_stats->tx_underrun +
			       hw_stats->tx_trunc;

	net_stats->tx_fअगरo_errors    = hw_stats->tx_underrun;
	net_stats->tx_पातed_errors = hw_stats->tx_पात_col;
	net_stats->tx_winकरोw_errors  = hw_stats->tx_late_col;

	net_stats->rx_packets = hw_stats->rx_ok + net_stats->rx_errors;
	net_stats->tx_packets = hw_stats->tx_ok + net_stats->tx_errors;

	वापस net_stats;
पूर्ण

अटल व्योम atl1e_update_hw_stats(काष्ठा atl1e_adapter *adapter)
अणु
	u16 hw_reg_addr = 0;
	अचिन्हित दीर्घ *stats_item = शून्य;

	/* update rx status */
	hw_reg_addr = REG_MAC_RX_STATUS_BIN;
	stats_item  = &adapter->hw_stats.rx_ok;
	जबतक (hw_reg_addr <= REG_MAC_RX_STATUS_END) अणु
		*stats_item += AT_READ_REG(&adapter->hw, hw_reg_addr);
		stats_item++;
		hw_reg_addr += 4;
	पूर्ण
	/* update tx status */
	hw_reg_addr = REG_MAC_TX_STATUS_BIN;
	stats_item  = &adapter->hw_stats.tx_ok;
	जबतक (hw_reg_addr <= REG_MAC_TX_STATUS_END) अणु
		*stats_item += AT_READ_REG(&adapter->hw, hw_reg_addr);
		stats_item++;
		hw_reg_addr += 4;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम atl1e_clear_phy_पूर्णांक(काष्ठा atl1e_adapter *adapter)
अणु
	u16 phy_data;

	spin_lock(&adapter->mdio_lock);
	atl1e_पढ़ो_phy_reg(&adapter->hw, MII_INT_STATUS, &phy_data);
	spin_unlock(&adapter->mdio_lock);
पूर्ण

अटल bool atl1e_clean_tx_irq(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा atl1e_tx_ring *tx_ring = &adapter->tx_ring;
	काष्ठा atl1e_tx_buffer *tx_buffer = शून्य;
	u16 hw_next_to_clean = AT_READ_REGW(&adapter->hw, REG_TPD_CONS_IDX);
	u16 next_to_clean = atomic_पढ़ो(&tx_ring->next_to_clean);

	जबतक (next_to_clean != hw_next_to_clean) अणु
		tx_buffer = &tx_ring->tx_buffer[next_to_clean];
		अगर (tx_buffer->dma) अणु
			अगर (tx_buffer->flags & ATL1E_TX_PCIMAP_SINGLE)
				dma_unmap_single(&adapter->pdev->dev,
						 tx_buffer->dma,
						 tx_buffer->length,
						 DMA_TO_DEVICE);
			अन्यथा अगर (tx_buffer->flags & ATL1E_TX_PCIMAP_PAGE)
				dma_unmap_page(&adapter->pdev->dev,
					       tx_buffer->dma,
					       tx_buffer->length,
					       DMA_TO_DEVICE);
			tx_buffer->dma = 0;
		पूर्ण

		अगर (tx_buffer->skb) अणु
			dev_consume_skb_irq(tx_buffer->skb);
			tx_buffer->skb = शून्य;
		पूर्ण

		अगर (++next_to_clean == tx_ring->count)
			next_to_clean = 0;
	पूर्ण

	atomic_set(&tx_ring->next_to_clean, next_to_clean);

	अगर (netअगर_queue_stopped(adapter->netdev) &&
			netअगर_carrier_ok(adapter->netdev)) अणु
		netअगर_wake_queue(adapter->netdev);
	पूर्ण

	वापस true;
पूर्ण

/**
 * atl1e_पूर्णांकr - Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 */
अटल irqवापस_t atl1e_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा net_device *netdev  = data;
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1e_hw *hw = &adapter->hw;
	पूर्णांक max_पूर्णांकs = AT_MAX_INT_WORK;
	पूर्णांक handled = IRQ_NONE;
	u32 status;

	करो अणु
		status = AT_READ_REG(hw, REG_ISR);
		अगर ((status & IMR_NORMAL_MASK) == 0 ||
				(status & ISR_DIS_INT) != 0) अणु
			अगर (max_पूर्णांकs != AT_MAX_INT_WORK)
				handled = IRQ_HANDLED;
			अवरोध;
		पूर्ण
		/* link event */
		अगर (status & ISR_GPHY)
			atl1e_clear_phy_पूर्णांक(adapter);
		/* Ack ISR */
		AT_WRITE_REG(hw, REG_ISR, status | ISR_DIS_INT);

		handled = IRQ_HANDLED;
		/* check अगर PCIE PHY Link करोwn */
		अगर (status & ISR_PHY_LINKDOWN) अणु
			netdev_err(adapter->netdev,
				   "pcie phy linkdown %x\n", status);
			अगर (netअगर_running(adapter->netdev)) अणु
				/* reset MAC */
				atl1e_irq_reset(adapter);
				schedule_work(&adapter->reset_task);
				अवरोध;
			पूर्ण
		पूर्ण

		/* check अगर DMA पढ़ो/ग_लिखो error */
		अगर (status & (ISR_DMAR_TO_RST | ISR_DMAW_TO_RST)) अणु
			netdev_err(adapter->netdev,
				   "PCIE DMA RW error (status = 0x%x)\n",
				   status);
			atl1e_irq_reset(adapter);
			schedule_work(&adapter->reset_task);
			अवरोध;
		पूर्ण

		अगर (status & ISR_SMB)
			atl1e_update_hw_stats(adapter);

		/* link event */
		अगर (status & (ISR_GPHY | ISR_MANUAL)) अणु
			netdev->stats.tx_carrier_errors++;
			atl1e_link_chg_event(adapter);
			अवरोध;
		पूर्ण

		/* transmit event */
		अगर (status & ISR_TX_EVENT)
			atl1e_clean_tx_irq(adapter);

		अगर (status & ISR_RX_EVENT) अणु
			/*
			 * disable rx पूर्णांकerrupts, without
			 * the synchronize_irq bit
			 */
			AT_WRITE_REG(hw, REG_IMR,
				     IMR_NORMAL_MASK & ~ISR_RX_EVENT);
			AT_WRITE_FLUSH(hw);
			अगर (likely(napi_schedule_prep(
				   &adapter->napi)))
				__napi_schedule(&adapter->napi);
		पूर्ण
	पूर्ण जबतक (--max_पूर्णांकs > 0);
	/* re-enable Interrupt*/
	AT_WRITE_REG(&adapter->hw, REG_ISR, 0);

	वापस handled;
पूर्ण

अटल अंतरभूत व्योम atl1e_rx_checksum(काष्ठा atl1e_adapter *adapter,
		  काष्ठा sk_buff *skb, काष्ठा atl1e_recv_ret_status *prrs)
अणु
	u8 *packet = (u8 *)(prrs + 1);
	काष्ठा iphdr *iph;
	u16 head_len = ETH_HLEN;
	u16 pkt_flags;
	u16 err_flags;

	skb_checksum_none_निश्चित(skb);
	pkt_flags = prrs->pkt_flag;
	err_flags = prrs->err_flag;
	अगर (((pkt_flags & RRS_IS_IPV4) || (pkt_flags & RRS_IS_IPV6)) &&
		((pkt_flags & RRS_IS_TCP) || (pkt_flags & RRS_IS_UDP))) अणु
		अगर (pkt_flags & RRS_IS_IPV4) अणु
			अगर (pkt_flags & RRS_IS_802_3)
				head_len += 8;
			iph = (काष्ठा iphdr *) (packet + head_len);
			अगर (iph->frag_off != 0 && !(pkt_flags & RRS_IS_IP_DF))
				जाओ hw_xsum;
		पूर्ण
		अगर (!(err_flags & (RRS_ERR_IP_CSUM | RRS_ERR_L4_CSUM))) अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			वापस;
		पूर्ण
	पूर्ण

hw_xsum :
	वापस;
पूर्ण

अटल काष्ठा atl1e_rx_page *atl1e_get_rx_page(काष्ठा atl1e_adapter *adapter,
					       u8 que)
अणु
	काष्ठा atl1e_rx_page_desc *rx_page_desc =
		(काष्ठा atl1e_rx_page_desc *) adapter->rx_ring.rx_page_desc;
	u8 rx_using = rx_page_desc[que].rx_using;

	वापस &(rx_page_desc[que].rx_page[rx_using]);
पूर्ण

अटल व्योम atl1e_clean_rx_irq(काष्ठा atl1e_adapter *adapter, u8 que,
		   पूर्णांक *work_करोne, पूर्णांक work_to_करो)
अणु
	काष्ठा net_device *netdev  = adapter->netdev;
	काष्ठा atl1e_rx_ring *rx_ring = &adapter->rx_ring;
	काष्ठा atl1e_rx_page_desc *rx_page_desc =
		(काष्ठा atl1e_rx_page_desc *) rx_ring->rx_page_desc;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा atl1e_rx_page *rx_page = atl1e_get_rx_page(adapter, que);
	u32 packet_size, ग_लिखो_offset;
	काष्ठा atl1e_recv_ret_status *prrs;

	ग_लिखो_offset = *(rx_page->ग_लिखो_offset_addr);
	अगर (likely(rx_page->पढ़ो_offset < ग_लिखो_offset)) अणु
		करो अणु
			अगर (*work_करोne >= work_to_करो)
				अवरोध;
			(*work_करोne)++;
			/* get new packet's  rrs */
			prrs = (काष्ठा atl1e_recv_ret_status *) (rx_page->addr +
						 rx_page->पढ़ो_offset);
			/* check sequence number */
			अगर (prrs->seq_num != rx_page_desc[que].rx_nxseq) अणु
				netdev_err(netdev,
					   "rx sequence number error (rx=%d) (expect=%d)\n",
					   prrs->seq_num,
					   rx_page_desc[que].rx_nxseq);
				rx_page_desc[que].rx_nxseq++;
				/* just क्रम debug use */
				AT_WRITE_REG(&adapter->hw, REG_DEBUG_DATA0,
					     (((u32)prrs->seq_num) << 16) |
					     rx_page_desc[que].rx_nxseq);
				जाओ fatal_err;
			पूर्ण
			rx_page_desc[que].rx_nxseq++;

			/* error packet */
			अगर ((prrs->pkt_flag & RRS_IS_ERR_FRAME) &&
			    !(netdev->features & NETIF_F_RXALL)) अणु
				अगर (prrs->err_flag & (RRS_ERR_BAD_CRC |
					RRS_ERR_DRIBBLE | RRS_ERR_CODE |
					RRS_ERR_TRUNC)) अणु
				/* hardware error, discard this packet*/
					netdev_err(netdev,
						   "rx packet desc error %x\n",
						   *((u32 *)prrs + 1));
					जाओ skip_pkt;
				पूर्ण
			पूर्ण

			packet_size = ((prrs->word1 >> RRS_PKT_SIZE_SHIFT) &
					RRS_PKT_SIZE_MASK);
			अगर (likely(!(netdev->features & NETIF_F_RXFCS)))
				packet_size -= 4; /* CRC */

			skb = netdev_alloc_skb_ip_align(netdev, packet_size);
			अगर (skb == शून्य)
				जाओ skip_pkt;

			स_नकल(skb->data, (u8 *)(prrs + 1), packet_size);
			skb_put(skb, packet_size);
			skb->protocol = eth_type_trans(skb, netdev);
			atl1e_rx_checksum(adapter, skb, prrs);

			अगर (prrs->pkt_flag & RRS_IS_VLAN_TAG) अणु
				u16 vlan_tag = (prrs->vtag >> 4) |
					       ((prrs->vtag & 7) << 13) |
					       ((prrs->vtag & 8) << 9);
				netdev_dbg(netdev,
					   "RXD VLAN TAG<RRD>=0x%04x\n",
					   prrs->vtag);
				__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tag);
			पूर्ण
			napi_gro_receive(&adapter->napi, skb);

skip_pkt:
	/* skip current packet whether it's ok or not. */
			rx_page->पढ़ो_offset +=
				(((u32)((prrs->word1 >> RRS_PKT_SIZE_SHIFT) &
				RRS_PKT_SIZE_MASK) +
				माप(काष्ठा atl1e_recv_ret_status) + 31) &
						0xFFFFFFE0);

			अगर (rx_page->पढ़ो_offset >= rx_ring->page_size) अणु
				/* mark this page clean */
				u16 reg_addr;
				u8  rx_using;

				rx_page->पढ़ो_offset =
					*(rx_page->ग_लिखो_offset_addr) = 0;
				rx_using = rx_page_desc[que].rx_using;
				reg_addr =
					atl1e_rx_page_vld_regs[que][rx_using];
				AT_WRITE_REGB(&adapter->hw, reg_addr, 1);
				rx_page_desc[que].rx_using ^= 1;
				rx_page = atl1e_get_rx_page(adapter, que);
			पूर्ण
			ग_लिखो_offset = *(rx_page->ग_लिखो_offset_addr);
		पूर्ण जबतक (rx_page->पढ़ो_offset < ग_लिखो_offset);
	पूर्ण

	वापस;

fatal_err:
	अगर (!test_bit(__AT_DOWN, &adapter->flags))
		schedule_work(&adapter->reset_task);
पूर्ण

/**
 * atl1e_clean - NAPI Rx polling callback
 * @napi: napi info
 * @budget: number of packets to clean
 */
अटल पूर्णांक atl1e_clean(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा atl1e_adapter *adapter =
			container_of(napi, काष्ठा atl1e_adapter, napi);
	u32 imr_data;
	पूर्णांक work_करोne = 0;

	/* Keep link state inक्रमmation with original netdev */
	अगर (!netअगर_carrier_ok(adapter->netdev))
		जाओ quit_polling;

	atl1e_clean_rx_irq(adapter, 0, &work_करोne, budget);

	/* If no Tx and not enough Rx work करोne, निकास the polling mode */
	अगर (work_करोne < budget) अणु
quit_polling:
		napi_complete_करोne(napi, work_करोne);
		imr_data = AT_READ_REG(&adapter->hw, REG_IMR);
		AT_WRITE_REG(&adapter->hw, REG_IMR, imr_data | ISR_RX_EVENT);
		/* test debug */
		अगर (test_bit(__AT_DOWN, &adapter->flags)) अणु
			atomic_dec(&adapter->irq_sem);
			netdev_err(adapter->netdev,
				   "atl1e_clean is called when AT_DOWN\n");
		पूर्ण
		/* reenable RX पूर्णांकr */
		/*atl1e_irq_enable(adapter); */

	पूर्ण
	वापस work_करोne;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER

/*
 * Polling 'interrupt' - used by things like netconsole to send skbs
 * without having to re-enable पूर्णांकerrupts. It's not called जबतक
 * the पूर्णांकerrupt routine is executing.
 */
अटल व्योम atl1e_netpoll(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);

	disable_irq(adapter->pdev->irq);
	atl1e_पूर्णांकr(adapter->pdev->irq, netdev);
	enable_irq(adapter->pdev->irq);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत u16 atl1e_tpd_avail(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा atl1e_tx_ring *tx_ring = &adapter->tx_ring;
	u16 next_to_use = 0;
	u16 next_to_clean = 0;

	next_to_clean = atomic_पढ़ो(&tx_ring->next_to_clean);
	next_to_use   = tx_ring->next_to_use;

	वापस (u16)(next_to_clean > next_to_use) ?
		(next_to_clean - next_to_use - 1) :
		(tx_ring->count + next_to_clean - next_to_use - 1);
पूर्ण

/*
 * get next usable tpd
 * Note: should call atl1e_tdp_avail to make sure
 * there is enough tpd to use
 */
अटल काष्ठा atl1e_tpd_desc *atl1e_get_tpd(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा atl1e_tx_ring *tx_ring = &adapter->tx_ring;
	u16 next_to_use = 0;

	next_to_use = tx_ring->next_to_use;
	अगर (++tx_ring->next_to_use == tx_ring->count)
		tx_ring->next_to_use = 0;

	स_रखो(&tx_ring->desc[next_to_use], 0, माप(काष्ठा atl1e_tpd_desc));
	वापस &tx_ring->desc[next_to_use];
पूर्ण

अटल काष्ठा atl1e_tx_buffer *
atl1e_get_tx_buffer(काष्ठा atl1e_adapter *adapter, काष्ठा atl1e_tpd_desc *tpd)
अणु
	काष्ठा atl1e_tx_ring *tx_ring = &adapter->tx_ring;

	वापस &tx_ring->tx_buffer[tpd - tx_ring->desc];
पूर्ण

/* Calculate the transmit packet descript needed*/
अटल u16 atl1e_cal_tdp_req(स्थिर काष्ठा sk_buff *skb)
अणु
	पूर्णांक i = 0;
	u16 tpd_req = 1;
	u16 fg_size = 0;
	u16 proto_hdr_len = 0;

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		fg_size = skb_frag_size(&skb_shinfo(skb)->frags[i]);
		tpd_req += ((fg_size + MAX_TX_BUF_LEN - 1) >> MAX_TX_BUF_SHIFT);
	पूर्ण

	अगर (skb_is_gso(skb)) अणु
		अगर (skb->protocol == htons(ETH_P_IP) ||
		   (skb_shinfo(skb)->gso_type == SKB_GSO_TCPV6)) अणु
			proto_hdr_len = skb_transport_offset(skb) +
					tcp_hdrlen(skb);
			अगर (proto_hdr_len < skb_headlen(skb)) अणु
				tpd_req += ((skb_headlen(skb) - proto_hdr_len +
					   MAX_TX_BUF_LEN - 1) >>
					   MAX_TX_BUF_SHIFT);
			पूर्ण
		पूर्ण

	पूर्ण
	वापस tpd_req;
पूर्ण

अटल पूर्णांक atl1e_tso_csum(काष्ठा atl1e_adapter *adapter,
		       काष्ठा sk_buff *skb, काष्ठा atl1e_tpd_desc *tpd)
अणु
	अचिन्हित लघु offload_type;
	u8 hdr_len;
	u32 real_len;

	अगर (skb_is_gso(skb)) अणु
		पूर्णांक err;

		err = skb_cow_head(skb, 0);
		अगर (err < 0)
			वापस err;

		offload_type = skb_shinfo(skb)->gso_type;

		अगर (offload_type & SKB_GSO_TCPV4) अणु
			real_len = (((अचिन्हित अक्षर *)ip_hdr(skb) - skb->data)
					+ ntohs(ip_hdr(skb)->tot_len));

			अगर (real_len < skb->len)
				pskb_trim(skb, real_len);

			hdr_len = (skb_transport_offset(skb) + tcp_hdrlen(skb));
			अगर (unlikely(skb->len == hdr_len)) अणु
				/* only xsum need */
				netdev_warn(adapter->netdev,
					    "IPV4 tso with zero data??\n");
				जाओ check_sum;
			पूर्ण अन्यथा अणु
				ip_hdr(skb)->check = 0;
				ip_hdr(skb)->tot_len = 0;
				tcp_hdr(skb)->check = ~csum_tcpudp_magic(
							ip_hdr(skb)->saddr,
							ip_hdr(skb)->daddr,
							0, IPPROTO_TCP, 0);
				tpd->word3 |= (ip_hdr(skb)->ihl &
					TDP_V4_IPHL_MASK) <<
					TPD_V4_IPHL_SHIFT;
				tpd->word3 |= ((tcp_hdrlen(skb) >> 2) &
					TPD_TCPHDRLEN_MASK) <<
					TPD_TCPHDRLEN_SHIFT;
				tpd->word3 |= ((skb_shinfo(skb)->gso_size) &
					TPD_MSS_MASK) << TPD_MSS_SHIFT;
				tpd->word3 |= 1 << TPD_SEGMENT_EN_SHIFT;
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण

check_sum:
	अगर (likely(skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		u8 css, cso;

		cso = skb_checksum_start_offset(skb);
		अगर (unlikely(cso & 0x1)) अणु
			netdev_err(adapter->netdev,
				   "payload offset should not ant event number\n");
			वापस -1;
		पूर्ण अन्यथा अणु
			css = cso + skb->csum_offset;
			tpd->word3 |= (cso & TPD_PLOADOFFSET_MASK) <<
					TPD_PLOADOFFSET_SHIFT;
			tpd->word3 |= (css & TPD_CCSUMOFFSET_MASK) <<
					TPD_CCSUMOFFSET_SHIFT;
			tpd->word3 |= 1 << TPD_CC_SEGMENT_EN_SHIFT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक atl1e_tx_map(काष्ठा atl1e_adapter *adapter,
			काष्ठा sk_buff *skb, काष्ठा atl1e_tpd_desc *tpd)
अणु
	काष्ठा atl1e_tpd_desc *use_tpd = शून्य;
	काष्ठा atl1e_tx_buffer *tx_buffer = शून्य;
	u16 buf_len = skb_headlen(skb);
	u16 map_len = 0;
	u16 mapped_len = 0;
	u16 hdr_len = 0;
	u16 nr_frags;
	u16 f;
	पूर्णांक segment;
	पूर्णांक ring_start = adapter->tx_ring.next_to_use;
	पूर्णांक ring_end;

	nr_frags = skb_shinfo(skb)->nr_frags;
	segment = (tpd->word3 >> TPD_SEGMENT_EN_SHIFT) & TPD_SEGMENT_EN_MASK;
	अगर (segment) अणु
		/* TSO */
		map_len = hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		use_tpd = tpd;

		tx_buffer = atl1e_get_tx_buffer(adapter, use_tpd);
		tx_buffer->length = map_len;
		tx_buffer->dma = dma_map_single(&adapter->pdev->dev,
						skb->data, hdr_len,
						DMA_TO_DEVICE);
		अगर (dma_mapping_error(&adapter->pdev->dev, tx_buffer->dma))
			वापस -ENOSPC;

		ATL1E_SET_PCIMAP_TYPE(tx_buffer, ATL1E_TX_PCIMAP_SINGLE);
		mapped_len += map_len;
		use_tpd->buffer_addr = cpu_to_le64(tx_buffer->dma);
		use_tpd->word2 = (use_tpd->word2 & (~TPD_BUFLEN_MASK)) |
			((cpu_to_le32(tx_buffer->length) &
			TPD_BUFLEN_MASK) << TPD_BUFLEN_SHIFT);
	पूर्ण

	जबतक (mapped_len < buf_len) अणु
		/* mapped_len == 0, means we should use the first tpd,
		   which is given by caller  */
		अगर (mapped_len == 0) अणु
			use_tpd = tpd;
		पूर्ण अन्यथा अणु
			use_tpd = atl1e_get_tpd(adapter);
			स_नकल(use_tpd, tpd, माप(काष्ठा atl1e_tpd_desc));
		पूर्ण
		tx_buffer = atl1e_get_tx_buffer(adapter, use_tpd);
		tx_buffer->skb = शून्य;

		tx_buffer->length = map_len =
			((buf_len - mapped_len) >= MAX_TX_BUF_LEN) ?
			MAX_TX_BUF_LEN : (buf_len - mapped_len);
		tx_buffer->dma =
			dma_map_single(&adapter->pdev->dev,
				       skb->data + mapped_len, map_len,
				       DMA_TO_DEVICE);

		अगर (dma_mapping_error(&adapter->pdev->dev, tx_buffer->dma)) अणु
			/* We need to unwind the mappings we've करोne */
			ring_end = adapter->tx_ring.next_to_use;
			adapter->tx_ring.next_to_use = ring_start;
			जबतक (adapter->tx_ring.next_to_use != ring_end) अणु
				tpd = atl1e_get_tpd(adapter);
				tx_buffer = atl1e_get_tx_buffer(adapter, tpd);
				dma_unmap_single(&adapter->pdev->dev,
						 tx_buffer->dma,
						 tx_buffer->length,
						 DMA_TO_DEVICE);
			पूर्ण
			/* Reset the tx rings next poपूर्णांकer */
			adapter->tx_ring.next_to_use = ring_start;
			वापस -ENOSPC;
		पूर्ण

		ATL1E_SET_PCIMAP_TYPE(tx_buffer, ATL1E_TX_PCIMAP_SINGLE);
		mapped_len  += map_len;
		use_tpd->buffer_addr = cpu_to_le64(tx_buffer->dma);
		use_tpd->word2 = (use_tpd->word2 & (~TPD_BUFLEN_MASK)) |
			((cpu_to_le32(tx_buffer->length) &
			TPD_BUFLEN_MASK) << TPD_BUFLEN_SHIFT);
	पूर्ण

	क्रम (f = 0; f < nr_frags; f++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[f];
		u16 i;
		u16 seg_num;

		buf_len = skb_frag_size(frag);

		seg_num = (buf_len + MAX_TX_BUF_LEN - 1) / MAX_TX_BUF_LEN;
		क्रम (i = 0; i < seg_num; i++) अणु
			use_tpd = atl1e_get_tpd(adapter);
			स_नकल(use_tpd, tpd, माप(काष्ठा atl1e_tpd_desc));

			tx_buffer = atl1e_get_tx_buffer(adapter, use_tpd);
			BUG_ON(tx_buffer->skb);

			tx_buffer->skb = शून्य;
			tx_buffer->length =
				(buf_len > MAX_TX_BUF_LEN) ?
				MAX_TX_BUF_LEN : buf_len;
			buf_len -= tx_buffer->length;

			tx_buffer->dma = skb_frag_dma_map(&adapter->pdev->dev,
							  frag,
							  (i * MAX_TX_BUF_LEN),
							  tx_buffer->length,
							  DMA_TO_DEVICE);

			अगर (dma_mapping_error(&adapter->pdev->dev, tx_buffer->dma)) अणु
				/* We need to unwind the mappings we've करोne */
				ring_end = adapter->tx_ring.next_to_use;
				adapter->tx_ring.next_to_use = ring_start;
				जबतक (adapter->tx_ring.next_to_use != ring_end) अणु
					tpd = atl1e_get_tpd(adapter);
					tx_buffer = atl1e_get_tx_buffer(adapter, tpd);
					dma_unmap_page(&adapter->pdev->dev, tx_buffer->dma,
						       tx_buffer->length, DMA_TO_DEVICE);
				पूर्ण

				/* Reset the ring next to use poपूर्णांकer */
				adapter->tx_ring.next_to_use = ring_start;
				वापस -ENOSPC;
			पूर्ण

			ATL1E_SET_PCIMAP_TYPE(tx_buffer, ATL1E_TX_PCIMAP_PAGE);
			use_tpd->buffer_addr = cpu_to_le64(tx_buffer->dma);
			use_tpd->word2 = (use_tpd->word2 & (~TPD_BUFLEN_MASK)) |
					((cpu_to_le32(tx_buffer->length) &
					TPD_BUFLEN_MASK) << TPD_BUFLEN_SHIFT);
		पूर्ण
	पूर्ण

	अगर ((tpd->word3 >> TPD_SEGMENT_EN_SHIFT) & TPD_SEGMENT_EN_MASK)
		/* note this one is a tcp header */
		tpd->word3 |= 1 << TPD_HDRFLAG_SHIFT;
	/* The last tpd */

	use_tpd->word3 |= 1 << TPD_EOP_SHIFT;
	/* The last buffer info contain the skb address,
	   so it will be मुक्त after unmap */
	tx_buffer->skb = skb;
	वापस 0;
पूर्ण

अटल व्योम atl1e_tx_queue(काष्ठा atl1e_adapter *adapter, u16 count,
			   काष्ठा atl1e_tpd_desc *tpd)
अणु
	काष्ठा atl1e_tx_ring *tx_ring = &adapter->tx_ring;
	/* Force memory ग_लिखोs to complete beक्रमe letting h/w
	 * know there are new descriptors to fetch.  (Only
	 * applicable क्रम weak-ordered memory model archs,
	 * such as IA-64). */
	wmb();
	AT_WRITE_REG(&adapter->hw, REG_MB_TPD_PROD_IDX, tx_ring->next_to_use);
पूर्ण

अटल netdev_tx_t atl1e_xmit_frame(काष्ठा sk_buff *skb,
					  काष्ठा net_device *netdev)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	u16 tpd_req = 1;
	काष्ठा atl1e_tpd_desc *tpd;

	अगर (test_bit(__AT_DOWN, &adapter->flags)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (unlikely(skb->len <= 0)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	tpd_req = atl1e_cal_tdp_req(skb);

	अगर (atl1e_tpd_avail(adapter) < tpd_req) अणु
		/* no enough descriptor, just stop queue */
		netअगर_stop_queue(netdev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	tpd = atl1e_get_tpd(adapter);

	अगर (skb_vlan_tag_present(skb)) अणु
		u16 vlan_tag = skb_vlan_tag_get(skb);
		u16 atl1e_vlan_tag;

		tpd->word3 |= 1 << TPD_INS_VL_TAG_SHIFT;
		AT_VLAN_TAG_TO_TPD_TAG(vlan_tag, atl1e_vlan_tag);
		tpd->word2 |= (atl1e_vlan_tag & TPD_VLANTAG_MASK) <<
				TPD_VLAN_SHIFT;
	पूर्ण

	अगर (skb->protocol == htons(ETH_P_8021Q))
		tpd->word3 |= 1 << TPD_VL_TAGGED_SHIFT;

	अगर (skb_network_offset(skb) != ETH_HLEN)
		tpd->word3 |= 1 << TPD_ETHTYPE_SHIFT; /* 802.3 frame */

	/* करो TSO and check sum */
	अगर (atl1e_tso_csum(adapter, skb, tpd) != 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (atl1e_tx_map(adapter, skb, tpd)) अणु
		dev_kमुक्त_skb_any(skb);
		जाओ out;
	पूर्ण

	atl1e_tx_queue(adapter, tpd_req, tpd);
out:
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम atl1e_मुक्त_irq(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	मुक्त_irq(adapter->pdev->irq, netdev);
पूर्ण

अटल पूर्णांक atl1e_request_irq(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा pci_dev    *pdev   = adapter->pdev;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err = 0;

	err = request_irq(pdev->irq, atl1e_पूर्णांकr, IRQF_SHARED, netdev->name,
			  netdev);
	अगर (err) अणु
		netdev_dbg(adapter->netdev,
			   "Unable to allocate interrupt Error: %d\n", err);
		वापस err;
	पूर्ण
	netdev_dbg(netdev, "atl1e_request_irq OK\n");
	वापस err;
पूर्ण

पूर्णांक atl1e_up(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err = 0;
	u32 val;

	/* hardware has been reset, we need to reload some things */
	err = atl1e_init_hw(&adapter->hw);
	अगर (err) अणु
		err = -EIO;
		वापस err;
	पूर्ण
	atl1e_init_ring_ptrs(adapter);
	atl1e_set_multi(netdev);
	atl1e_restore_vlan(adapter);

	अगर (atl1e_configure(adapter)) अणु
		err = -EIO;
		जाओ err_up;
	पूर्ण

	clear_bit(__AT_DOWN, &adapter->flags);
	napi_enable(&adapter->napi);
	atl1e_irq_enable(adapter);
	val = AT_READ_REG(&adapter->hw, REG_MASTER_CTRL);
	AT_WRITE_REG(&adapter->hw, REG_MASTER_CTRL,
		      val | MASTER_CTRL_MANUAL_INT);

err_up:
	वापस err;
पूर्ण

व्योम atl1e_करोwn(काष्ठा atl1e_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	/* संकेत that we're करोwn so the पूर्णांकerrupt handler करोes not
	 * reschedule our watchकरोg समयr */
	set_bit(__AT_DOWN, &adapter->flags);

	netअगर_stop_queue(netdev);

	/* reset MAC to disable all RX/TX */
	atl1e_reset_hw(&adapter->hw);
	msleep(1);

	napi_disable(&adapter->napi);
	atl1e_del_समयr(adapter);
	atl1e_irq_disable(adapter);

	netअगर_carrier_off(netdev);
	adapter->link_speed = SPEED_0;
	adapter->link_duplex = -1;
	atl1e_clean_tx_ring(adapter);
	atl1e_clean_rx_ring(adapter);
पूर्ण

/**
 * atl1e_खोलो - Called when a network पूर्णांकerface is made active
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0 on success, negative value on failure
 *
 * The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 * active by the प्रणाली (IFF_UP).  At this poपूर्णांक all resources needed
 * क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 * handler is रेजिस्टरed with the OS, the watchकरोg समयr is started,
 * and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 */
अटल पूर्णांक atl1e_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err;

	/* disallow खोलो during test */
	अगर (test_bit(__AT_TESTING, &adapter->flags))
		वापस -EBUSY;

	/* allocate rx/tx dma buffer & descriptors */
	atl1e_init_ring_resources(adapter);
	err = atl1e_setup_ring_resources(adapter);
	अगर (unlikely(err))
		वापस err;

	err = atl1e_request_irq(adapter);
	अगर (unlikely(err))
		जाओ err_req_irq;

	err = atl1e_up(adapter);
	अगर (unlikely(err))
		जाओ err_up;

	वापस 0;

err_up:
	atl1e_मुक्त_irq(adapter);
err_req_irq:
	atl1e_मुक्त_ring_resources(adapter);
	atl1e_reset_hw(&adapter->hw);

	वापस err;
पूर्ण

/**
 * atl1e_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are मुक्तd.
 */
अटल पूर्णांक atl1e_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);

	WARN_ON(test_bit(__AT_RESETTING, &adapter->flags));
	atl1e_करोwn(adapter);
	atl1e_मुक्त_irq(adapter);
	atl1e_मुक्त_ring_resources(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक atl1e_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1e_hw *hw = &adapter->hw;
	u32 ctrl = 0;
	u32 mac_ctrl_data = 0;
	u32 wol_ctrl_data = 0;
	u16 mii_advertise_data = 0;
	u16 mii_bmsr_data = 0;
	u16 mii_पूर्णांकr_status_data = 0;
	u32 wufc = adapter->wol;
	u32 i;
#अगर_घोषित CONFIG_PM
	पूर्णांक retval = 0;
#पूर्ण_अगर

	अगर (netअगर_running(netdev)) अणु
		WARN_ON(test_bit(__AT_RESETTING, &adapter->flags));
		atl1e_करोwn(adapter);
	पूर्ण
	netअगर_device_detach(netdev);

#अगर_घोषित CONFIG_PM
	retval = pci_save_state(pdev);
	अगर (retval)
		वापस retval;
#पूर्ण_अगर

	अगर (wufc) अणु
		/* get link status */
		atl1e_पढ़ो_phy_reg(hw, MII_BMSR, &mii_bmsr_data);
		atl1e_पढ़ो_phy_reg(hw, MII_BMSR, &mii_bmsr_data);

		mii_advertise_data = ADVERTISE_10HALF;

		अगर ((atl1e_ग_लिखो_phy_reg(hw, MII_CTRL1000, 0) != 0) ||
		    (atl1e_ग_लिखो_phy_reg(hw,
			   MII_ADVERTISE, mii_advertise_data) != 0) ||
		    (atl1e_phy_commit(hw)) != 0) अणु
			netdev_dbg(adapter->netdev, "set phy register failed\n");
			जाओ wol_dis;
		पूर्ण

		hw->phy_configured = false; /* re-init PHY when resume */

		/* turn on magic packet wol */
		अगर (wufc & AT_WUFC_MAG)
			wol_ctrl_data |= WOL_MAGIC_EN | WOL_MAGIC_PME_EN;

		अगर (wufc & AT_WUFC_LNKC) अणु
		/* अगर orignal link status is link, just रुको क्रम retrive link */
			अगर (mii_bmsr_data & BMSR_LSTATUS) अणु
				क्रम (i = 0; i < AT_SUSPEND_LINK_TIMEOUT; i++) अणु
					msleep(100);
					atl1e_पढ़ो_phy_reg(hw, MII_BMSR,
							&mii_bmsr_data);
					अगर (mii_bmsr_data & BMSR_LSTATUS)
						अवरोध;
				पूर्ण

				अगर ((mii_bmsr_data & BMSR_LSTATUS) == 0)
					netdev_dbg(adapter->netdev,
						   "Link may change when suspend\n");
			पूर्ण
			wol_ctrl_data |=  WOL_LINK_CHG_EN | WOL_LINK_CHG_PME_EN;
			/* only link up can wake up */
			अगर (atl1e_ग_लिखो_phy_reg(hw, MII_INT_CTRL, 0x400) != 0) अणु
				netdev_dbg(adapter->netdev,
					   "read write phy register failed\n");
				जाओ wol_dis;
			पूर्ण
		पूर्ण
		/* clear phy पूर्णांकerrupt */
		atl1e_पढ़ो_phy_reg(hw, MII_INT_STATUS, &mii_पूर्णांकr_status_data);
		/* Config MAC Ctrl रेजिस्टर */
		mac_ctrl_data = MAC_CTRL_RX_EN;
		/* set to 10/100M halt duplex */
		mac_ctrl_data |= MAC_CTRL_SPEED_10_100 << MAC_CTRL_SPEED_SHIFT;
		mac_ctrl_data |= (((u32)adapter->hw.preamble_len &
				 MAC_CTRL_PRMLEN_MASK) <<
				 MAC_CTRL_PRMLEN_SHIFT);

		__atl1e_vlan_mode(netdev->features, &mac_ctrl_data);

		/* magic packet maybe Broadcast&multicast&Unicast frame */
		अगर (wufc & AT_WUFC_MAG)
			mac_ctrl_data |= MAC_CTRL_BC_EN;

		netdev_dbg(adapter->netdev, "suspend MAC=0x%x\n",
			   mac_ctrl_data);

		AT_WRITE_REG(hw, REG_WOL_CTRL, wol_ctrl_data);
		AT_WRITE_REG(hw, REG_MAC_CTRL, mac_ctrl_data);
		/* pcie patch */
		ctrl = AT_READ_REG(hw, REG_PCIE_PHYMISC);
		ctrl |= PCIE_PHYMISC_FORCE_RCV_DET;
		AT_WRITE_REG(hw, REG_PCIE_PHYMISC, ctrl);
		pci_enable_wake(pdev, pci_choose_state(pdev, state), 1);
		जाओ suspend_निकास;
	पूर्ण
wol_dis:

	/* WOL disabled */
	AT_WRITE_REG(hw, REG_WOL_CTRL, 0);

	/* pcie patch */
	ctrl = AT_READ_REG(hw, REG_PCIE_PHYMISC);
	ctrl |= PCIE_PHYMISC_FORCE_RCV_DET;
	AT_WRITE_REG(hw, REG_PCIE_PHYMISC, ctrl);

	atl1e_क्रमce_ps(hw);
	hw->phy_configured = false; /* re-init PHY when resume */

	pci_enable_wake(pdev, pci_choose_state(pdev, state), 0);

suspend_निकास:

	अगर (netअगर_running(netdev))
		atl1e_मुक्त_irq(adapter);

	pci_disable_device(pdev);

	pci_set_घातer_state(pdev, pci_choose_state(pdev, state));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक atl1e_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);
	u32 err;

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);

	err = pci_enable_device(pdev);
	अगर (err) अणु
		netdev_err(adapter->netdev,
			   "Cannot enable PCI device from suspend\n");
		वापस err;
	पूर्ण

	pci_set_master(pdev);

	AT_READ_REG(&adapter->hw, REG_WOL_CTRL); /* clear WOL status */

	pci_enable_wake(pdev, PCI_D3hot, 0);
	pci_enable_wake(pdev, PCI_D3cold, 0);

	AT_WRITE_REG(&adapter->hw, REG_WOL_CTRL, 0);

	अगर (netअगर_running(netdev)) अणु
		err = atl1e_request_irq(adapter);
		अगर (err)
			वापस err;
	पूर्ण

	atl1e_reset_hw(&adapter->hw);

	अगर (netअगर_running(netdev))
		atl1e_up(adapter);

	netअगर_device_attach(netdev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम atl1e_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	atl1e_suspend(pdev, PMSG_SUSPEND);
पूर्ण

अटल स्थिर काष्ठा net_device_ops atl1e_netdev_ops = अणु
	.nकरो_खोलो		= atl1e_खोलो,
	.nकरो_stop		= atl1e_बंद,
	.nकरो_start_xmit		= atl1e_xmit_frame,
	.nकरो_get_stats		= atl1e_get_stats,
	.nकरो_set_rx_mode	= atl1e_set_multi,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= atl1e_set_mac_addr,
	.nकरो_fix_features	= atl1e_fix_features,
	.nकरो_set_features	= atl1e_set_features,
	.nकरो_change_mtu		= atl1e_change_mtu,
	.nकरो_करो_ioctl		= atl1e_ioctl,
	.nकरो_tx_समयout		= atl1e_tx_समयout,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= atl1e_netpoll,
#पूर्ण_अगर

पूर्ण;

अटल पूर्णांक atl1e_init_netdev(काष्ठा net_device *netdev, काष्ठा pci_dev *pdev)
अणु
	SET_NETDEV_DEV(netdev, &pdev->dev);
	pci_set_drvdata(pdev, netdev);

	netdev->netdev_ops = &atl1e_netdev_ops;

	netdev->watchकरोg_समयo = AT_TX_WATCHDOG;
	/* MTU range: 42 - 8170 */
	netdev->min_mtu = ETH_ZLEN - (ETH_HLEN + VLAN_HLEN);
	netdev->max_mtu = MAX_JUMBO_FRAME_SIZE -
			  (ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN);
	atl1e_set_ethtool_ops(netdev);

	netdev->hw_features = NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_TSO |
			      NETIF_F_HW_VLAN_CTAG_RX;
	netdev->features = netdev->hw_features | NETIF_F_HW_VLAN_CTAG_TX;
	/* not enabled by शेष */
	netdev->hw_features |= NETIF_F_RXALL | NETIF_F_RXFCS;
	वापस 0;
पूर्ण

/**
 * atl1e_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in atl1e_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * atl1e_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 */
अटल पूर्णांक atl1e_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा atl1e_adapter *adapter = शून्य;
	अटल पूर्णांक cards_found;

	पूर्णांक err = 0;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot enable PCI device\n");
		वापस err;
	पूर्ण

	/*
	 * The atl1e chip can DMA to 64-bit addresses, but it uses a single
	 * shared रेजिस्टर क्रम the high 32 bits, so only a single, aligned,
	 * 4 GB physical address range can be used at a समय.
	 *
	 * Supporting 64-bit DMA on this hardware is more trouble than it's
	 * worth.  It is far easier to limit to 32-bit DMA than update
	 * various kernel subप्रणालीs to support the mechanics required by a
	 * fixed-high-32-bit प्रणाली.
	 */
	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_err(&pdev->dev, "No usable DMA configuration,aborting\n");
		जाओ err_dma;
	पूर्ण

	err = pci_request_regions(pdev, atl1e_driver_name);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot obtain PCI resources\n");
		जाओ err_pci_reg;
	पूर्ण

	pci_set_master(pdev);

	netdev = alloc_etherdev(माप(काष्ठा atl1e_adapter));
	अगर (netdev == शून्य) अणु
		err = -ENOMEM;
		जाओ err_alloc_etherdev;
	पूर्ण

	err = atl1e_init_netdev(netdev, pdev);
	अगर (err) अणु
		netdev_err(netdev, "init netdevice failed\n");
		जाओ err_init_netdev;
	पूर्ण
	adapter = netdev_priv(netdev);
	adapter->bd_number = cards_found;
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	adapter->hw.adapter = adapter;
	adapter->hw.hw_addr = pci_iomap(pdev, BAR_0, 0);
	अगर (!adapter->hw.hw_addr) अणु
		err = -EIO;
		netdev_err(netdev, "cannot map device registers\n");
		जाओ err_ioremap;
	पूर्ण

	/* init mii data */
	adapter->mii.dev = netdev;
	adapter->mii.mdio_पढ़ो  = atl1e_mdio_पढ़ो;
	adapter->mii.mdio_ग_लिखो = atl1e_mdio_ग_लिखो;
	adapter->mii.phy_id_mask = 0x1f;
	adapter->mii.reg_num_mask = MDIO_REG_ADDR_MASK;

	netअगर_napi_add(netdev, &adapter->napi, atl1e_clean, 64);

	समयr_setup(&adapter->phy_config_समयr, atl1e_phy_config, 0);

	/* get user settings */
	atl1e_check_options(adapter);
	/*
	 * Mark all PCI regions associated with PCI device
	 * pdev as being reserved by owner atl1e_driver_name
	 * Enables bus-mastering on the device and calls
	 * pcibios_set_master to करो the needed arch specअगरic settings
	 */
	atl1e_setup_pcicmd(pdev);
	/* setup the निजी काष्ठाure */
	err = atl1e_sw_init(adapter);
	अगर (err) अणु
		netdev_err(netdev, "net device private data init failed\n");
		जाओ err_sw_init;
	पूर्ण

	/* Init GPHY as early as possible due to घातer saving issue  */
	atl1e_phy_init(&adapter->hw);
	/* reset the controller to
	 * put the device in a known good starting state */
	err = atl1e_reset_hw(&adapter->hw);
	अगर (err) अणु
		err = -EIO;
		जाओ err_reset;
	पूर्ण

	अगर (atl1e_पढ़ो_mac_addr(&adapter->hw) != 0) अणु
		err = -EIO;
		netdev_err(netdev, "get mac address failed\n");
		जाओ err_eeprom;
	पूर्ण

	स_नकल(netdev->dev_addr, adapter->hw.mac_addr, netdev->addr_len);
	netdev_dbg(netdev, "mac address : %pM\n", adapter->hw.mac_addr);

	INIT_WORK(&adapter->reset_task, atl1e_reset_task);
	INIT_WORK(&adapter->link_chg_task, atl1e_link_chg_task);
	netअगर_set_gso_max_size(netdev, MAX_TSO_SEG_SIZE);
	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		netdev_err(netdev, "register netdevice failed\n");
		जाओ err_रेजिस्टर;
	पूर्ण

	/* assume we have no link क्रम now */
	netअगर_stop_queue(netdev);
	netअगर_carrier_off(netdev);

	cards_found++;

	वापस 0;

err_reset:
err_रेजिस्टर:
err_sw_init:
err_eeprom:
	pci_iounmap(pdev, adapter->hw.hw_addr);
err_init_netdev:
err_ioremap:
	मुक्त_netdev(netdev);
err_alloc_etherdev:
	pci_release_regions(pdev);
err_pci_reg:
err_dma:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

/**
 * atl1e_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * atl1e_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.  The could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 */
अटल व्योम atl1e_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);

	/*
	 * flush_scheduled work may reschedule our watchकरोg task, so
	 * explicitly disable watchकरोg tasks from being rescheduled
	 */
	set_bit(__AT_DOWN, &adapter->flags);

	atl1e_del_समयr(adapter);
	atl1e_cancel_work(adapter);

	unरेजिस्टर_netdev(netdev);
	atl1e_मुक्त_ring_resources(adapter);
	atl1e_क्रमce_ps(&adapter->hw);
	pci_iounmap(pdev, adapter->hw.hw_addr);
	pci_release_regions(pdev);
	मुक्त_netdev(netdev);
	pci_disable_device(pdev);
पूर्ण

/**
 * atl1e_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t
atl1e_io_error_detected(काष्ठा pci_dev *pdev, pci_channel_state_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);

	netअगर_device_detach(netdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (netअगर_running(netdev))
		atl1e_करोwn(adapter);

	pci_disable_device(pdev);

	/* Request a slot slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * atl1e_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot. Implementation
 * resembles the first-half of the e1000_resume routine.
 */
अटल pci_ers_result_t atl1e_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);

	अगर (pci_enable_device(pdev)) अणु
		netdev_err(adapter->netdev,
			   "Cannot re-enable PCI device after reset\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
	pci_set_master(pdev);

	pci_enable_wake(pdev, PCI_D3hot, 0);
	pci_enable_wake(pdev, PCI_D3cold, 0);

	atl1e_reset_hw(&adapter->hw);

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * atl1e_io_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells us that
 * its OK to resume normal operation. Implementation resembles the
 * second-half of the atl1e_resume routine.
 */
अटल व्योम atl1e_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl1e_adapter *adapter = netdev_priv(netdev);

	अगर (netअगर_running(netdev)) अणु
		अगर (atl1e_up(adapter)) अणु
			netdev_err(adapter->netdev,
				   "can't bring device back up after reset\n");
			वापस;
		पूर्ण
	पूर्ण

	netअगर_device_attach(netdev);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers atl1e_err_handler = अणु
	.error_detected = atl1e_io_error_detected,
	.slot_reset = atl1e_io_slot_reset,
	.resume = atl1e_io_resume,
पूर्ण;

अटल काष्ठा pci_driver atl1e_driver = अणु
	.name     = atl1e_driver_name,
	.id_table = atl1e_pci_tbl,
	.probe    = atl1e_probe,
	.हटाओ   = atl1e_हटाओ,
	/* Power Management Hooks */
#अगर_घोषित CONFIG_PM
	.suspend  = atl1e_suspend,
	.resume   = atl1e_resume,
#पूर्ण_अगर
	.shutकरोwn = atl1e_shutकरोwn,
	.err_handler = &atl1e_err_handler
पूर्ण;

module_pci_driver(atl1e_driver);
