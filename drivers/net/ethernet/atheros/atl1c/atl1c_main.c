<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 2008 - 2009 Atheros Corporation. All rights reserved.
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 */

#समावेश "atl1c.h"

अक्षर atl1c_driver_name[] = "atl1c";

/*
 * atl1c_pci_tbl - PCI Device ID Table
 *
 * Wildcard entries (PCI_ANY_ID) should come last
 * Last entry must be all 0s
 *
 * अणु Venकरोr ID, Device ID, SubVenकरोr ID, SubDevice ID,
 *   Class, Class Mask, निजी data (not used) पूर्ण
 */
अटल स्थिर काष्ठा pci_device_id atl1c_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_ATTANSIC, PCI_DEVICE_ID_ATTANSIC_L1C)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ATTANSIC, PCI_DEVICE_ID_ATTANSIC_L2C)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ATTANSIC, PCI_DEVICE_ID_ATHEROS_L2C_B)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ATTANSIC, PCI_DEVICE_ID_ATHEROS_L2C_B2)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ATTANSIC, PCI_DEVICE_ID_ATHEROS_L1D)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ATTANSIC, PCI_DEVICE_ID_ATHEROS_L1D_2_0)पूर्ण,
	/* required last entry */
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, atl1c_pci_tbl);

MODULE_AUTHOR("Jie Yang");
MODULE_AUTHOR("Qualcomm Atheros Inc.");
MODULE_DESCRIPTION("Qualcomm Atheros 100/1000M Ethernet Network Driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक atl1c_stop_mac(काष्ठा atl1c_hw *hw);
अटल व्योम atl1c_disable_l0s_l1(काष्ठा atl1c_hw *hw);
अटल व्योम atl1c_set_aspm(काष्ठा atl1c_hw *hw, u16 link_speed);
अटल व्योम atl1c_start_mac(काष्ठा atl1c_adapter *adapter);
अटल व्योम atl1c_clean_rx_irq(काष्ठा atl1c_adapter *adapter,
		   पूर्णांक *work_करोne, पूर्णांक work_to_करो);
अटल पूर्णांक atl1c_up(काष्ठा atl1c_adapter *adapter);
अटल व्योम atl1c_करोwn(काष्ठा atl1c_adapter *adapter);
अटल पूर्णांक atl1c_reset_mac(काष्ठा atl1c_hw *hw);
अटल व्योम atl1c_reset_dma_ring(काष्ठा atl1c_adapter *adapter);
अटल पूर्णांक atl1c_configure(काष्ठा atl1c_adapter *adapter);
अटल पूर्णांक atl1c_alloc_rx_buffer(काष्ठा atl1c_adapter *adapter, bool napi_mode);


अटल स्थिर u32 atl1c_शेष_msg = NETIF_MSG_DRV | NETIF_MSG_PROBE |
	NETIF_MSG_LINK | NETIF_MSG_TIMER | NETIF_MSG_IFDOWN | NETIF_MSG_IFUP;
अटल व्योम atl1c_pcie_patch(काष्ठा atl1c_hw *hw)
अणु
	u32 mst_data, data;

	/* pclk sel could चयन to 25M */
	AT_READ_REG(hw, REG_MASTER_CTRL, &mst_data);
	mst_data &= ~MASTER_CTRL_CLK_SEL_DIS;
	AT_WRITE_REG(hw, REG_MASTER_CTRL, mst_data);

	/* WoL/PCIE related settings */
	अगर (hw->nic_type == athr_l1c || hw->nic_type == athr_l2c) अणु
		AT_READ_REG(hw, REG_PCIE_PHYMISC, &data);
		data |= PCIE_PHYMISC_FORCE_RCV_DET;
		AT_WRITE_REG(hw, REG_PCIE_PHYMISC, data);
	पूर्ण अन्यथा अणु /* new dev set bit5 of MASTER */
		अगर (!(mst_data & MASTER_CTRL_WAKEN_25M))
			AT_WRITE_REG(hw, REG_MASTER_CTRL,
				mst_data | MASTER_CTRL_WAKEN_25M);
	पूर्ण
	/* aspm/PCIE setting only क्रम l2cb 1.0 */
	अगर (hw->nic_type == athr_l2c_b && hw->revision_id == L2CB_V10) अणु
		AT_READ_REG(hw, REG_PCIE_PHYMISC2, &data);
		data = FIELD_SETX(data, PCIE_PHYMISC2_CDR_BW,
			L2CB1_PCIE_PHYMISC2_CDR_BW);
		data = FIELD_SETX(data, PCIE_PHYMISC2_L0S_TH,
			L2CB1_PCIE_PHYMISC2_L0S_TH);
		AT_WRITE_REG(hw, REG_PCIE_PHYMISC2, data);
		/* extend L1 sync समयr */
		AT_READ_REG(hw, REG_LINK_CTRL, &data);
		data |= LINK_CTRL_EXT_SYNC;
		AT_WRITE_REG(hw, REG_LINK_CTRL, data);
	पूर्ण
	/* l2cb 1.x & l1d 1.x */
	अगर (hw->nic_type == athr_l2c_b || hw->nic_type == athr_l1d) अणु
		AT_READ_REG(hw, REG_PM_CTRL, &data);
		data |= PM_CTRL_L0S_BUFSRX_EN;
		AT_WRITE_REG(hw, REG_PM_CTRL, data);
		/* clear venकरोr msg */
		AT_READ_REG(hw, REG_DMA_DBG, &data);
		AT_WRITE_REG(hw, REG_DMA_DBG, data & ~DMA_DBG_VENDOR_MSG);
	पूर्ण
पूर्ण

/* FIXME: no need any more ? */
/*
 * atl1c_init_pcie - init PCIE module
 */
अटल व्योम atl1c_reset_pcie(काष्ठा atl1c_hw *hw, u32 flag)
अणु
	u32 data;
	u32 pci_cmd;
	काष्ठा pci_dev *pdev = hw->adapter->pdev;
	पूर्णांक pos;

	AT_READ_REG(hw, PCI_COMMAND, &pci_cmd);
	pci_cmd &= ~PCI_COMMAND_INTX_DISABLE;
	pci_cmd |= (PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER |
		PCI_COMMAND_IO);
	AT_WRITE_REG(hw, PCI_COMMAND, pci_cmd);

	/*
	 * Clear any PowerSaveing Settings
	 */
	pci_enable_wake(pdev, PCI_D3hot, 0);
	pci_enable_wake(pdev, PCI_D3cold, 0);
	/* wol sts पढ़ो-clear */
	AT_READ_REG(hw, REG_WOL_CTRL, &data);
	AT_WRITE_REG(hw, REG_WOL_CTRL, 0);

	/*
	 * Mask some pcie error bits
	 */
	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_ERR);
	अगर (pos) अणु
		pci_पढ़ो_config_dword(pdev, pos + PCI_ERR_UNCOR_SEVER, &data);
		data &= ~(PCI_ERR_UNC_DLP | PCI_ERR_UNC_FCP);
		pci_ग_लिखो_config_dword(pdev, pos + PCI_ERR_UNCOR_SEVER, data);
	पूर्ण
	/* clear error status */
	pcie_capability_ग_लिखो_word(pdev, PCI_EXP_DEVSTA,
			PCI_EXP_DEVSTA_NFED |
			PCI_EXP_DEVSTA_FED |
			PCI_EXP_DEVSTA_CED |
			PCI_EXP_DEVSTA_URD);

	AT_READ_REG(hw, REG_LTSSM_ID_CTRL, &data);
	data &= ~LTSSM_ID_EN_WRO;
	AT_WRITE_REG(hw, REG_LTSSM_ID_CTRL, data);

	atl1c_pcie_patch(hw);
	अगर (flag & ATL1C_PCIE_L0S_L1_DISABLE)
		atl1c_disable_l0s_l1(hw);

	msleep(5);
पूर्ण

/**
 * atl1c_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 * @adapter: board निजी काष्ठाure
 */
अटल अंतरभूत व्योम atl1c_irq_enable(काष्ठा atl1c_adapter *adapter)
अणु
	अगर (likely(atomic_dec_and_test(&adapter->irq_sem))) अणु
		AT_WRITE_REG(&adapter->hw, REG_ISR, 0x7FFFFFFF);
		AT_WRITE_REG(&adapter->hw, REG_IMR, adapter->hw.पूर्णांकr_mask);
		AT_WRITE_FLUSH(&adapter->hw);
	पूर्ण
पूर्ण

/**
 * atl1c_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 * @adapter: board निजी काष्ठाure
 */
अटल अंतरभूत व्योम atl1c_irq_disable(काष्ठा atl1c_adapter *adapter)
अणु
	atomic_inc(&adapter->irq_sem);
	AT_WRITE_REG(&adapter->hw, REG_IMR, 0);
	AT_WRITE_REG(&adapter->hw, REG_ISR, ISR_DIS_INT);
	AT_WRITE_FLUSH(&adapter->hw);
	synchronize_irq(adapter->pdev->irq);
पूर्ण

/**
 * atl1c_irq_reset - reset पूर्णांकerrupt confiure on the NIC
 * @adapter: board निजी काष्ठाure
 */
अटल अंतरभूत व्योम atl1c_irq_reset(काष्ठा atl1c_adapter *adapter)
अणु
	atomic_set(&adapter->irq_sem, 1);
	atl1c_irq_enable(adapter);
पूर्ण

/*
 * atl1c_रुको_until_idle - रुको up to AT_HW_MAX_IDLE_DELAY पढ़ोs
 * of the idle status रेजिस्टर until the device is actually idle
 */
अटल u32 atl1c_रुको_until_idle(काष्ठा atl1c_hw *hw, u32 modu_ctrl)
अणु
	पूर्णांक समयout;
	u32 data;

	क्रम (समयout = 0; समयout < AT_HW_MAX_IDLE_DELAY; समयout++) अणु
		AT_READ_REG(hw, REG_IDLE_STATUS, &data);
		अगर ((data & modu_ctrl) == 0)
			वापस 0;
		msleep(1);
	पूर्ण
	वापस data;
पूर्ण

/**
 * atl1c_phy_config - Timer Call-back
 * @t: समयr list containing poपूर्णांकer to netdev cast पूर्णांकo an अचिन्हित दीर्घ
 */
अटल व्योम atl1c_phy_config(काष्ठा समयr_list *t)
अणु
	काष्ठा atl1c_adapter *adapter = from_समयr(adapter, t,
						   phy_config_समयr);
	काष्ठा atl1c_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adapter->mdio_lock, flags);
	atl1c_restart_स्वतःneg(hw);
	spin_unlock_irqrestore(&adapter->mdio_lock, flags);
पूर्ण

व्योम atl1c_reinit_locked(काष्ठा atl1c_adapter *adapter)
अणु
	atl1c_करोwn(adapter);
	atl1c_up(adapter);
	clear_bit(__AT_RESETTING, &adapter->flags);
पूर्ण

अटल व्योम atl1c_check_link_status(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा atl1c_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev    *pdev   = adapter->pdev;
	पूर्णांक err;
	अचिन्हित दीर्घ flags;
	u16 speed, duplex, phy_data;

	spin_lock_irqsave(&adapter->mdio_lock, flags);
	/* MII_BMSR must पढ़ो twise */
	atl1c_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
	atl1c_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
	spin_unlock_irqrestore(&adapter->mdio_lock, flags);

	अगर ((phy_data & BMSR_LSTATUS) == 0) अणु
		/* link करोwn */
		netअगर_carrier_off(netdev);
		hw->hibernate = true;
		अगर (atl1c_reset_mac(hw) != 0)
			अगर (netअगर_msg_hw(adapter))
				dev_warn(&pdev->dev, "reset mac failed\n");
		atl1c_set_aspm(hw, SPEED_0);
		atl1c_post_phy_linkchg(hw, SPEED_0);
		atl1c_reset_dma_ring(adapter);
		atl1c_configure(adapter);
	पूर्ण अन्यथा अणु
		/* Link Up */
		hw->hibernate = false;
		spin_lock_irqsave(&adapter->mdio_lock, flags);
		err = atl1c_get_speed_and_duplex(hw, &speed, &duplex);
		spin_unlock_irqrestore(&adapter->mdio_lock, flags);
		अगर (unlikely(err))
			वापस;
		/* link result is our setting */
		अगर (adapter->link_speed != speed ||
		    adapter->link_duplex != duplex) अणु
			adapter->link_speed  = speed;
			adapter->link_duplex = duplex;
			atl1c_set_aspm(hw, speed);
			atl1c_post_phy_linkchg(hw, speed);
			atl1c_start_mac(adapter);
			अगर (netअगर_msg_link(adapter))
				dev_info(&pdev->dev,
					"%s: %s NIC Link is Up<%d Mbps %s>\n",
					atl1c_driver_name, netdev->name,
					adapter->link_speed,
					adapter->link_duplex == FULL_DUPLEX ?
					"Full Duplex" : "Half Duplex");
		पूर्ण
		अगर (!netअगर_carrier_ok(netdev))
			netअगर_carrier_on(netdev);
	पूर्ण
पूर्ण

अटल व्योम atl1c_link_chg_event(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev    *pdev   = adapter->pdev;
	u16 phy_data;
	u16 link_up;

	spin_lock(&adapter->mdio_lock);
	atl1c_पढ़ो_phy_reg(&adapter->hw, MII_BMSR, &phy_data);
	atl1c_पढ़ो_phy_reg(&adapter->hw, MII_BMSR, &phy_data);
	spin_unlock(&adapter->mdio_lock);
	link_up = phy_data & BMSR_LSTATUS;
	/* notअगरy upper layer link करोwn ASAP */
	अगर (!link_up) अणु
		अगर (netअगर_carrier_ok(netdev)) अणु
			/* old link state: Up */
			netअगर_carrier_off(netdev);
			अगर (netअगर_msg_link(adapter))
				dev_info(&pdev->dev,
					"%s: %s NIC Link is Down\n",
					atl1c_driver_name, netdev->name);
			adapter->link_speed = SPEED_0;
		पूर्ण
	पूर्ण

	set_bit(ATL1C_WORK_EVENT_LINK_CHANGE, &adapter->work_event);
	schedule_work(&adapter->common_task);
पूर्ण

अटल व्योम atl1c_common_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा atl1c_adapter *adapter;
	काष्ठा net_device *netdev;

	adapter = container_of(work, काष्ठा atl1c_adapter, common_task);
	netdev = adapter->netdev;

	अगर (test_bit(__AT_DOWN, &adapter->flags))
		वापस;

	अगर (test_and_clear_bit(ATL1C_WORK_EVENT_RESET, &adapter->work_event)) अणु
		netअगर_device_detach(netdev);
		atl1c_करोwn(adapter);
		atl1c_up(adapter);
		netअगर_device_attach(netdev);
	पूर्ण

	अगर (test_and_clear_bit(ATL1C_WORK_EVENT_LINK_CHANGE,
		&adapter->work_event)) अणु
		atl1c_irq_disable(adapter);
		atl1c_check_link_status(adapter);
		atl1c_irq_enable(adapter);
	पूर्ण
पूर्ण


अटल व्योम atl1c_del_समयr(काष्ठा atl1c_adapter *adapter)
अणु
	del_समयr_sync(&adapter->phy_config_समयr);
पूर्ण


/**
 * atl1c_tx_समयout - Respond to a Tx Hang
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @txqueue: index of hanging tx queue
 */
अटल व्योम atl1c_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	/* Do the reset outside of पूर्णांकerrupt context */
	set_bit(ATL1C_WORK_EVENT_RESET, &adapter->work_event);
	schedule_work(&adapter->common_task);
पूर्ण

/**
 * atl1c_set_multi - Multicast and Promiscuous mode set
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The set_multi entry poपूर्णांक is called whenever the multicast address
 * list or the network पूर्णांकerface flags are updated.  This routine is
 * responsible क्रम configuring the hardware क्रम proper multicast,
 * promiscuous mode, and all-multi behavior.
 */
अटल व्योम atl1c_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1c_hw *hw = &adapter->hw;
	काष्ठा netdev_hw_addr *ha;
	u32 mac_ctrl_data;
	u32 hash_value;

	/* Check क्रम Promiscuous and All Multicast modes */
	AT_READ_REG(hw, REG_MAC_CTRL, &mac_ctrl_data);

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
		hash_value = atl1c_hash_mc_addr(hw, ha->addr);
		atl1c_hash_set(hw, hash_value);
	पूर्ण
पूर्ण

अटल व्योम __atl1c_vlan_mode(netdev_features_t features, u32 *mac_ctrl_data)
अणु
	अगर (features & NETIF_F_HW_VLAN_CTAG_RX) अणु
		/* enable VLAN tag insert/strip */
		*mac_ctrl_data |= MAC_CTRL_RMV_VLAN;
	पूर्ण अन्यथा अणु
		/* disable VLAN tag insert/strip */
		*mac_ctrl_data &= ~MAC_CTRL_RMV_VLAN;
	पूर्ण
पूर्ण

अटल व्योम atl1c_vlan_mode(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = adapter->pdev;
	u32 mac_ctrl_data = 0;

	अगर (netअगर_msg_pktdata(adapter))
		dev_dbg(&pdev->dev, "atl1c_vlan_mode\n");

	atl1c_irq_disable(adapter);
	AT_READ_REG(&adapter->hw, REG_MAC_CTRL, &mac_ctrl_data);
	__atl1c_vlan_mode(features, &mac_ctrl_data);
	AT_WRITE_REG(&adapter->hw, REG_MAC_CTRL, mac_ctrl_data);
	atl1c_irq_enable(adapter);
पूर्ण

अटल व्योम atl1c_restore_vlan(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;

	अगर (netअगर_msg_pktdata(adapter))
		dev_dbg(&pdev->dev, "atl1c_restore_vlan\n");
	atl1c_vlan_mode(adapter->netdev, adapter->netdev->features);
पूर्ण

/**
 * atl1c_set_mac - Change the Ethernet Address of the NIC
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @p: poपूर्णांकer to an address काष्ठाure
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक atl1c_set_mac_addr(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (netअगर_running(netdev))
		वापस -EBUSY;

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	स_नकल(adapter->hw.mac_addr, addr->sa_data, netdev->addr_len);

	atl1c_hw_set_mac_addr(&adapter->hw, adapter->hw.mac_addr);

	वापस 0;
पूर्ण

अटल व्योम atl1c_set_rxbufsize(काष्ठा atl1c_adapter *adapter,
				काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक head_size;
	पूर्णांक mtu = dev->mtu;

	adapter->rx_buffer_len = mtu > AT_RX_BUF_SIZE ?
		roundup(mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN, 8) : AT_RX_BUF_SIZE;

	head_size = SKB_DATA_ALIGN(adapter->rx_buffer_len + NET_SKB_PAD + NET_IP_ALIGN) +
		    SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	adapter->rx_frag_size = roundup_घात_of_two(head_size);
पूर्ण

अटल netdev_features_t atl1c_fix_features(काष्ठा net_device *netdev,
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

	अगर (netdev->mtu > MAX_TSO_FRAME_SIZE)
		features &= ~(NETIF_F_TSO | NETIF_F_TSO6);

	वापस features;
पूर्ण

अटल पूर्णांक atl1c_set_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	netdev_features_t changed = netdev->features ^ features;

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX)
		atl1c_vlan_mode(netdev, features);

	वापस 0;
पूर्ण

अटल व्योम atl1c_set_max_mtu(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1c_hw *hw = &adapter->hw;

	चयन (hw->nic_type) अणु
	/* These (GbE) devices support jumbo packets, max_mtu 6122 */
	हाल athr_l1c:
	हाल athr_l1d:
	हाल athr_l1d_2:
		netdev->max_mtu = MAX_JUMBO_FRAME_SIZE -
				  (ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN);
		अवरोध;
	/* The 10/100 devices करोn't support jumbo packets, max_mtu 1500 */
	शेष:
		netdev->max_mtu = ETH_DATA_LEN;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * atl1c_change_mtu - Change the Maximum Transfer Unit
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक atl1c_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	/* set MTU */
	अगर (netअगर_running(netdev)) अणु
		जबतक (test_and_set_bit(__AT_RESETTING, &adapter->flags))
			msleep(1);
		netdev->mtu = new_mtu;
		adapter->hw.max_frame_size = new_mtu;
		atl1c_set_rxbufsize(adapter, netdev);
		atl1c_करोwn(adapter);
		netdev_update_features(netdev);
		atl1c_up(adapter);
		clear_bit(__AT_RESETTING, &adapter->flags);
	पूर्ण
	वापस 0;
पूर्ण

/*
 *  caller should hold mdio_lock
 */
अटल पूर्णांक atl1c_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक reg_num)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	u16 result;

	atl1c_पढ़ो_phy_reg(&adapter->hw, reg_num, &result);
	वापस result;
पूर्ण

अटल व्योम atl1c_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक phy_id,
			     पूर्णांक reg_num, पूर्णांक val)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	atl1c_ग_लिखो_phy_reg(&adapter->hw, reg_num, val);
पूर्ण

अटल पूर्णांक atl1c_mii_ioctl(काष्ठा net_device *netdev,
			   काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = adapter->pdev;
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
		अगर (atl1c_पढ़ो_phy_reg(&adapter->hw, data->reg_num & 0x1F,
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

		dev_dbg(&pdev->dev, "<atl1c_mii_ioctl> write %x %x",
				data->reg_num, data->val_in);
		अगर (atl1c_ग_लिखो_phy_reg(&adapter->hw,
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

अटल पूर्णांक atl1c_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
		वापस atl1c_mii_ioctl(netdev, अगरr, cmd);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * atl1c_alloc_queues - Allocate memory क्रम all rings
 * @adapter: board निजी काष्ठाure to initialize
 *
 */
अटल पूर्णांक atl1c_alloc_queues(काष्ठा atl1c_adapter *adapter)
अणु
	वापस 0;
पूर्ण

अटल व्योम atl1c_set_mac_type(काष्ठा atl1c_hw *hw)
अणु
	चयन (hw->device_id) अणु
	हाल PCI_DEVICE_ID_ATTANSIC_L2C:
		hw->nic_type = athr_l2c;
		अवरोध;
	हाल PCI_DEVICE_ID_ATTANSIC_L1C:
		hw->nic_type = athr_l1c;
		अवरोध;
	हाल PCI_DEVICE_ID_ATHEROS_L2C_B:
		hw->nic_type = athr_l2c_b;
		अवरोध;
	हाल PCI_DEVICE_ID_ATHEROS_L2C_B2:
		hw->nic_type = athr_l2c_b2;
		अवरोध;
	हाल PCI_DEVICE_ID_ATHEROS_L1D:
		hw->nic_type = athr_l1d;
		अवरोध;
	हाल PCI_DEVICE_ID_ATHEROS_L1D_2_0:
		hw->nic_type = athr_l1d_2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक atl1c_setup_mac_funcs(काष्ठा atl1c_hw *hw)
अणु
	u32 link_ctrl_data;

	atl1c_set_mac_type(hw);
	AT_READ_REG(hw, REG_LINK_CTRL, &link_ctrl_data);

	hw->ctrl_flags = ATL1C_INTR_MODRT_ENABLE  |
			 ATL1C_TXQ_MODE_ENHANCE;
	hw->ctrl_flags |= ATL1C_ASPM_L0S_SUPPORT |
			  ATL1C_ASPM_L1_SUPPORT;
	hw->ctrl_flags |= ATL1C_ASPM_CTRL_MON;

	अगर (hw->nic_type == athr_l1c ||
	    hw->nic_type == athr_l1d ||
	    hw->nic_type == athr_l1d_2)
		hw->link_cap_flags |= ATL1C_LINK_CAP_1000M;
	वापस 0;
पूर्ण

काष्ठा atl1c_platक्रमm_patch अणु
	u16 pci_did;
	u8  pci_revid;
	u16 subप्रणाली_vid;
	u16 subप्रणाली_did;
	u32 patch_flag;
#घोषणा ATL1C_LINK_PATCH	0x1
पूर्ण;
अटल स्थिर काष्ठा atl1c_platक्रमm_patch plats[] = अणु
अणु0x2060, 0xC1, 0x1019, 0x8152, 0x1पूर्ण,
अणु0x2060, 0xC1, 0x1019, 0x2060, 0x1पूर्ण,
अणु0x2060, 0xC1, 0x1019, 0xE000, 0x1पूर्ण,
अणु0x2062, 0xC0, 0x1019, 0x8152, 0x1पूर्ण,
अणु0x2062, 0xC0, 0x1019, 0x2062, 0x1पूर्ण,
अणु0x2062, 0xC0, 0x1458, 0xE000, 0x1पूर्ण,
अणु0x2062, 0xC1, 0x1019, 0x8152, 0x1पूर्ण,
अणु0x2062, 0xC1, 0x1019, 0x2062, 0x1पूर्ण,
अणु0x2062, 0xC1, 0x1458, 0xE000, 0x1पूर्ण,
अणु0x2062, 0xC1, 0x1565, 0x2802, 0x1पूर्ण,
अणु0x2062, 0xC1, 0x1565, 0x2801, 0x1पूर्ण,
अणु0x1073, 0xC0, 0x1019, 0x8151, 0x1पूर्ण,
अणु0x1073, 0xC0, 0x1019, 0x1073, 0x1पूर्ण,
अणु0x1073, 0xC0, 0x1458, 0xE000, 0x1पूर्ण,
अणु0x1083, 0xC0, 0x1458, 0xE000, 0x1पूर्ण,
अणु0x1083, 0xC0, 0x1019, 0x8151, 0x1पूर्ण,
अणु0x1083, 0xC0, 0x1019, 0x1083, 0x1पूर्ण,
अणु0x1083, 0xC0, 0x1462, 0x7680, 0x1पूर्ण,
अणु0x1083, 0xC0, 0x1565, 0x2803, 0x1पूर्ण,
अणु0पूर्ण,
पूर्ण;

अटल व्योम atl1c_patch_assign(काष्ठा atl1c_hw *hw)
अणु
	काष्ठा pci_dev	*pdev = hw->adapter->pdev;
	u32 misc_ctrl;
	पूर्णांक i = 0;

	hw->msi_lnkpatch = false;

	जबतक (plats[i].pci_did != 0) अणु
		अगर (plats[i].pci_did == hw->device_id &&
		    plats[i].pci_revid == hw->revision_id &&
		    plats[i].subप्रणाली_vid == hw->subप्रणाली_venकरोr_id &&
		    plats[i].subप्रणाली_did == hw->subप्रणाली_id) अणु
			अगर (plats[i].patch_flag & ATL1C_LINK_PATCH)
				hw->msi_lnkpatch = true;
		पूर्ण
		i++;
	पूर्ण

	अगर (hw->device_id == PCI_DEVICE_ID_ATHEROS_L2C_B2 &&
	    hw->revision_id == L2CB_V21) अणु
		/* config access mode */
		pci_ग_लिखो_config_dword(pdev, REG_PCIE_IND_ACC_ADDR,
				       REG_PCIE_DEV_MISC_CTRL);
		pci_पढ़ो_config_dword(pdev, REG_PCIE_IND_ACC_DATA, &misc_ctrl);
		misc_ctrl &= ~0x100;
		pci_ग_लिखो_config_dword(pdev, REG_PCIE_IND_ACC_ADDR,
				       REG_PCIE_DEV_MISC_CTRL);
		pci_ग_लिखो_config_dword(pdev, REG_PCIE_IND_ACC_DATA, misc_ctrl);
	पूर्ण
पूर्ण
/**
 * atl1c_sw_init - Initialize general software काष्ठाures (काष्ठा atl1c_adapter)
 * @adapter: board निजी काष्ठाure to initialize
 *
 * atl1c_sw_init initializes the Adapter निजी data काष्ठाure.
 * Fields are initialized based on PCI device inक्रमmation and
 * OS network device settings (MTU size).
 */
अटल पूर्णांक atl1c_sw_init(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा atl1c_hw *hw   = &adapter->hw;
	काष्ठा pci_dev	*pdev = adapter->pdev;
	u32 revision;


	adapter->wol = 0;
	device_set_wakeup_enable(&pdev->dev, false);
	adapter->link_speed = SPEED_0;
	adapter->link_duplex = FULL_DUPLEX;
	adapter->tpd_ring[0].count = 1024;
	adapter->rfd_ring.count = 512;

	hw->venकरोr_id = pdev->venकरोr;
	hw->device_id = pdev->device;
	hw->subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	hw->subप्रणाली_id = pdev->subप्रणाली_device;
	pci_पढ़ो_config_dword(pdev, PCI_CLASS_REVISION, &revision);
	hw->revision_id = revision & 0xFF;
	/* beक्रमe link up, we assume hibernate is true */
	hw->hibernate = true;
	hw->media_type = MEDIA_TYPE_AUTO_SENSOR;
	अगर (atl1c_setup_mac_funcs(hw) != 0) अणु
		dev_err(&pdev->dev, "set mac function pointers failed\n");
		वापस -1;
	पूर्ण
	atl1c_patch_assign(hw);

	hw->पूर्णांकr_mask = IMR_NORMAL_MASK;
	hw->phy_configured = false;
	hw->preamble_len = 7;
	hw->max_frame_size = adapter->netdev->mtu;
	hw->स्वतःneg_advertised = ADVERTISED_Autoneg;
	hw->indirect_tab = 0xE4E4E4E4;
	hw->base_cpu = 0;

	hw->ict = 50000;		/* 100ms */
	hw->smb_समयr = 200000;	  	/* 400ms */
	hw->rx_imt = 200;
	hw->tx_imt = 1000;

	hw->tpd_burst = 5;
	hw->rfd_burst = 8;
	hw->dma_order = atl1c_dma_ord_out;
	hw->dmar_block = atl1c_dma_req_1024;

	अगर (atl1c_alloc_queues(adapter)) अणु
		dev_err(&pdev->dev, "Unable to allocate memory for queues\n");
		वापस -ENOMEM;
	पूर्ण
	/* TODO */
	atl1c_set_rxbufsize(adapter, adapter->netdev);
	atomic_set(&adapter->irq_sem, 1);
	spin_lock_init(&adapter->mdio_lock);
	spin_lock_init(&adapter->hw.पूर्णांकr_mask_lock);
	set_bit(__AT_DOWN, &adapter->flags);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम atl1c_clean_buffer(काष्ठा pci_dev *pdev,
				काष्ठा atl1c_buffer *buffer_info)
अणु
	u16 pci_driection;
	अगर (buffer_info->flags & ATL1C_BUFFER_FREE)
		वापस;
	अगर (buffer_info->dma) अणु
		अगर (buffer_info->flags & ATL1C_PCIMAP_FROMDEVICE)
			pci_driection = DMA_FROM_DEVICE;
		अन्यथा
			pci_driection = DMA_TO_DEVICE;

		अगर (buffer_info->flags & ATL1C_PCIMAP_SINGLE)
			dma_unmap_single(&pdev->dev, buffer_info->dma,
					 buffer_info->length, pci_driection);
		अन्यथा अगर (buffer_info->flags & ATL1C_PCIMAP_PAGE)
			dma_unmap_page(&pdev->dev, buffer_info->dma,
				       buffer_info->length, pci_driection);
	पूर्ण
	अगर (buffer_info->skb)
		dev_consume_skb_any(buffer_info->skb);
	buffer_info->dma = 0;
	buffer_info->skb = शून्य;
	ATL1C_SET_BUFFER_STATE(buffer_info, ATL1C_BUFFER_FREE);
पूर्ण
/**
 * atl1c_clean_tx_ring - Free Tx-skb
 * @adapter: board निजी काष्ठाure
 * @type: type of transmit queue
 */
अटल व्योम atl1c_clean_tx_ring(काष्ठा atl1c_adapter *adapter,
				क्रमागत atl1c_trans_queue type)
अणु
	काष्ठा atl1c_tpd_ring *tpd_ring = &adapter->tpd_ring[type];
	काष्ठा atl1c_buffer *buffer_info;
	काष्ठा pci_dev *pdev = adapter->pdev;
	u16 index, ring_count;

	ring_count = tpd_ring->count;
	क्रम (index = 0; index < ring_count; index++) अणु
		buffer_info = &tpd_ring->buffer_info[index];
		atl1c_clean_buffer(pdev, buffer_info);
	पूर्ण

	netdev_reset_queue(adapter->netdev);

	/* Zero out Tx-buffers */
	स_रखो(tpd_ring->desc, 0, माप(काष्ठा atl1c_tpd_desc) *
		ring_count);
	atomic_set(&tpd_ring->next_to_clean, 0);
	tpd_ring->next_to_use = 0;
पूर्ण

/**
 * atl1c_clean_rx_ring - Free rx-reservation skbs
 * @adapter: board निजी काष्ठाure
 */
अटल व्योम atl1c_clean_rx_ring(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा atl1c_rfd_ring *rfd_ring = &adapter->rfd_ring;
	काष्ठा atl1c_rrd_ring *rrd_ring = &adapter->rrd_ring;
	काष्ठा atl1c_buffer *buffer_info;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक j;

	क्रम (j = 0; j < rfd_ring->count; j++) अणु
		buffer_info = &rfd_ring->buffer_info[j];
		atl1c_clean_buffer(pdev, buffer_info);
	पूर्ण
	/* zero out the descriptor ring */
	स_रखो(rfd_ring->desc, 0, rfd_ring->size);
	rfd_ring->next_to_clean = 0;
	rfd_ring->next_to_use = 0;
	rrd_ring->next_to_use = 0;
	rrd_ring->next_to_clean = 0;
पूर्ण

/*
 * Read / Write Ptr Initialize:
 */
अटल व्योम atl1c_init_ring_ptrs(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा atl1c_tpd_ring *tpd_ring = adapter->tpd_ring;
	काष्ठा atl1c_rfd_ring *rfd_ring = &adapter->rfd_ring;
	काष्ठा atl1c_rrd_ring *rrd_ring = &adapter->rrd_ring;
	काष्ठा atl1c_buffer *buffer_info;
	पूर्णांक i, j;

	क्रम (i = 0; i < AT_MAX_TRANSMIT_QUEUE; i++) अणु
		tpd_ring[i].next_to_use = 0;
		atomic_set(&tpd_ring[i].next_to_clean, 0);
		buffer_info = tpd_ring[i].buffer_info;
		क्रम (j = 0; j < tpd_ring->count; j++)
			ATL1C_SET_BUFFER_STATE(&buffer_info[i],
					ATL1C_BUFFER_FREE);
	पूर्ण
	rfd_ring->next_to_use = 0;
	rfd_ring->next_to_clean = 0;
	rrd_ring->next_to_use = 0;
	rrd_ring->next_to_clean = 0;
	क्रम (j = 0; j < rfd_ring->count; j++) अणु
		buffer_info = &rfd_ring->buffer_info[j];
		ATL1C_SET_BUFFER_STATE(buffer_info, ATL1C_BUFFER_FREE);
	पूर्ण
पूर्ण

/**
 * atl1c_मुक्त_ring_resources - Free Tx / RX descriptor Resources
 * @adapter: board निजी काष्ठाure
 *
 * Free all transmit software resources
 */
अटल व्योम atl1c_मुक्त_ring_resources(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;

	dma_मुक्त_coherent(&pdev->dev, adapter->ring_header.size,
			  adapter->ring_header.desc, adapter->ring_header.dma);
	adapter->ring_header.desc = शून्य;

	/* Note: just मुक्त tdp_ring.buffer_info,
	*  it contain rfd_ring.buffer_info, करो not द्विगुन मुक्त */
	अगर (adapter->tpd_ring[0].buffer_info) अणु
		kमुक्त(adapter->tpd_ring[0].buffer_info);
		adapter->tpd_ring[0].buffer_info = शून्य;
	पूर्ण
	अगर (adapter->rx_page) अणु
		put_page(adapter->rx_page);
		adapter->rx_page = शून्य;
	पूर्ण
पूर्ण

/**
 * atl1c_setup_mem_resources - allocate Tx / RX descriptor resources
 * @adapter: board निजी काष्ठाure
 *
 * Return 0 on success, negative on failure
 */
अटल पूर्णांक atl1c_setup_ring_resources(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा atl1c_tpd_ring *tpd_ring = adapter->tpd_ring;
	काष्ठा atl1c_rfd_ring *rfd_ring = &adapter->rfd_ring;
	काष्ठा atl1c_rrd_ring *rrd_ring = &adapter->rrd_ring;
	काष्ठा atl1c_ring_header *ring_header = &adapter->ring_header;
	पूर्णांक size;
	पूर्णांक i;
	पूर्णांक count = 0;
	पूर्णांक rx_desc_count = 0;
	u32 offset = 0;

	rrd_ring->count = rfd_ring->count;
	क्रम (i = 1; i < AT_MAX_TRANSMIT_QUEUE; i++)
		tpd_ring[i].count = tpd_ring[0].count;

	/* 2 tpd queue, one high priority queue,
	 * another normal priority queue */
	size = माप(काष्ठा atl1c_buffer) * (tpd_ring->count * 2 +
		rfd_ring->count);
	tpd_ring->buffer_info = kzalloc(size, GFP_KERNEL);
	अगर (unlikely(!tpd_ring->buffer_info))
		जाओ err_nomem;

	क्रम (i = 0; i < AT_MAX_TRANSMIT_QUEUE; i++) अणु
		tpd_ring[i].buffer_info =
			(tpd_ring->buffer_info + count);
		count += tpd_ring[i].count;
	पूर्ण

	rfd_ring->buffer_info =
		(tpd_ring->buffer_info + count);
	count += rfd_ring->count;
	rx_desc_count += rfd_ring->count;

	/*
	 * real ring DMA buffer
	 * each ring/block may need up to 8 bytes क्रम alignment, hence the
	 * additional bytes tacked onto the end.
	 */
	ring_header->size = size =
		माप(काष्ठा atl1c_tpd_desc) * tpd_ring->count * 2 +
		माप(काष्ठा atl1c_rx_मुक्त_desc) * rx_desc_count +
		माप(काष्ठा atl1c_recv_ret_status) * rx_desc_count +
		8 * 4;

	ring_header->desc = dma_alloc_coherent(&pdev->dev, ring_header->size,
					       &ring_header->dma, GFP_KERNEL);
	अगर (unlikely(!ring_header->desc)) अणु
		dev_err(&pdev->dev, "could not get memory for DMA buffer\n");
		जाओ err_nomem;
	पूर्ण
	/* init TPD ring */

	tpd_ring[0].dma = roundup(ring_header->dma, 8);
	offset = tpd_ring[0].dma - ring_header->dma;
	क्रम (i = 0; i < AT_MAX_TRANSMIT_QUEUE; i++) अणु
		tpd_ring[i].dma = ring_header->dma + offset;
		tpd_ring[i].desc = (u8 *) ring_header->desc + offset;
		tpd_ring[i].size =
			माप(काष्ठा atl1c_tpd_desc) * tpd_ring[i].count;
		offset += roundup(tpd_ring[i].size, 8);
	पूर्ण
	/* init RFD ring */
	rfd_ring->dma = ring_header->dma + offset;
	rfd_ring->desc = (u8 *) ring_header->desc + offset;
	rfd_ring->size = माप(काष्ठा atl1c_rx_मुक्त_desc) * rfd_ring->count;
	offset += roundup(rfd_ring->size, 8);

	/* init RRD ring */
	rrd_ring->dma = ring_header->dma + offset;
	rrd_ring->desc = (u8 *) ring_header->desc + offset;
	rrd_ring->size = माप(काष्ठा atl1c_recv_ret_status) *
		rrd_ring->count;
	offset += roundup(rrd_ring->size, 8);

	वापस 0;

err_nomem:
	kमुक्त(tpd_ring->buffer_info);
	वापस -ENOMEM;
पूर्ण

अटल व्योम atl1c_configure_des_ring(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा atl1c_hw *hw = &adapter->hw;
	काष्ठा atl1c_rfd_ring *rfd_ring = &adapter->rfd_ring;
	काष्ठा atl1c_rrd_ring *rrd_ring = &adapter->rrd_ring;
	काष्ठा atl1c_tpd_ring *tpd_ring = (काष्ठा atl1c_tpd_ring *)
				adapter->tpd_ring;

	/* TPD */
	AT_WRITE_REG(hw, REG_TX_BASE_ADDR_HI,
			(u32)((tpd_ring[atl1c_trans_normal].dma &
				AT_DMA_HI_ADDR_MASK) >> 32));
	/* just enable normal priority TX queue */
	AT_WRITE_REG(hw, REG_TPD_PRI0_ADDR_LO,
			(u32)(tpd_ring[atl1c_trans_normal].dma &
				AT_DMA_LO_ADDR_MASK));
	AT_WRITE_REG(hw, REG_TPD_PRI1_ADDR_LO,
			(u32)(tpd_ring[atl1c_trans_high].dma &
				AT_DMA_LO_ADDR_MASK));
	AT_WRITE_REG(hw, REG_TPD_RING_SIZE,
			(u32)(tpd_ring[0].count & TPD_RING_SIZE_MASK));


	/* RFD */
	AT_WRITE_REG(hw, REG_RX_BASE_ADDR_HI,
			(u32)((rfd_ring->dma & AT_DMA_HI_ADDR_MASK) >> 32));
	AT_WRITE_REG(hw, REG_RFD0_HEAD_ADDR_LO,
			(u32)(rfd_ring->dma & AT_DMA_LO_ADDR_MASK));

	AT_WRITE_REG(hw, REG_RFD_RING_SIZE,
			rfd_ring->count & RFD_RING_SIZE_MASK);
	AT_WRITE_REG(hw, REG_RX_BUF_SIZE,
			adapter->rx_buffer_len & RX_BUF_SIZE_MASK);

	/* RRD */
	AT_WRITE_REG(hw, REG_RRD0_HEAD_ADDR_LO,
			(u32)(rrd_ring->dma & AT_DMA_LO_ADDR_MASK));
	AT_WRITE_REG(hw, REG_RRD_RING_SIZE,
			(rrd_ring->count & RRD_RING_SIZE_MASK));

	अगर (hw->nic_type == athr_l2c_b) अणु
		AT_WRITE_REG(hw, REG_SRAM_RXF_LEN, 0x02a0L);
		AT_WRITE_REG(hw, REG_SRAM_TXF_LEN, 0x0100L);
		AT_WRITE_REG(hw, REG_SRAM_RXF_ADDR, 0x029f0000L);
		AT_WRITE_REG(hw, REG_SRAM_RFD0_INFO, 0x02bf02a0L);
		AT_WRITE_REG(hw, REG_SRAM_TXF_ADDR, 0x03bf02c0L);
		AT_WRITE_REG(hw, REG_SRAM_TRD_ADDR, 0x03df03c0L);
		AT_WRITE_REG(hw, REG_TXF_WATER_MARK, 0);	/* TX watermark, to enter l1 state.*/
		AT_WRITE_REG(hw, REG_RXD_DMA_CTRL, 0);		/* RXD threshold.*/
	पूर्ण
	/* Load all of base address above */
	AT_WRITE_REG(hw, REG_LOAD_PTR, 1);
पूर्ण

अटल व्योम atl1c_configure_tx(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा atl1c_hw *hw = &adapter->hw;
	पूर्णांक max_pay_load;
	u16 tx_offload_thresh;
	u32 txq_ctrl_data;

	tx_offload_thresh = MAX_TSO_FRAME_SIZE;
	AT_WRITE_REG(hw, REG_TX_TSO_OFFLOAD_THRESH,
		(tx_offload_thresh >> 3) & TX_TSO_OFFLOAD_THRESH_MASK);
	max_pay_load = pcie_get_पढ़ोrq(adapter->pdev) >> 8;
	hw->dmar_block = min_t(u32, max_pay_load, hw->dmar_block);
	/*
	 * अगर BIOS had changed the dam-पढ़ो-max-length to an invalid value,
	 * restore it to शेष value
	 */
	अगर (hw->dmar_block < DEVICE_CTRL_MAXRRS_MIN) अणु
		pcie_set_पढ़ोrq(adapter->pdev, 128 << DEVICE_CTRL_MAXRRS_MIN);
		hw->dmar_block = DEVICE_CTRL_MAXRRS_MIN;
	पूर्ण
	txq_ctrl_data =
		hw->nic_type == athr_l2c_b || hw->nic_type == athr_l2c_b2 ?
		L2CB_TXQ_CFGV : L1C_TXQ_CFGV;

	AT_WRITE_REG(hw, REG_TXQ_CTRL, txq_ctrl_data);
पूर्ण

अटल व्योम atl1c_configure_rx(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा atl1c_hw *hw = &adapter->hw;
	u32 rxq_ctrl_data;

	rxq_ctrl_data = (hw->rfd_burst & RXQ_RFD_BURST_NUM_MASK) <<
			RXQ_RFD_BURST_NUM_SHIFT;

	अगर (hw->ctrl_flags & ATL1C_RX_IPV6_CHKSUM)
		rxq_ctrl_data |= IPV6_CHKSUM_CTRL_EN;

	/* aspm क्रम gigabit */
	अगर (hw->nic_type != athr_l1d_2 && (hw->device_id & 1) != 0)
		rxq_ctrl_data = FIELD_SETX(rxq_ctrl_data, ASPM_THRUPUT_LIMIT,
			ASPM_THRUPUT_LIMIT_100M);

	AT_WRITE_REG(hw, REG_RXQ_CTRL, rxq_ctrl_data);
पूर्ण

अटल व्योम atl1c_configure_dma(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा atl1c_hw *hw = &adapter->hw;
	u32 dma_ctrl_data;

	dma_ctrl_data = FIELDX(DMA_CTRL_RORDER_MODE, DMA_CTRL_RORDER_MODE_OUT) |
		DMA_CTRL_RREQ_PRI_DATA |
		FIELDX(DMA_CTRL_RREQ_BLEN, hw->dmar_block) |
		FIELDX(DMA_CTRL_WDLY_CNT, DMA_CTRL_WDLY_CNT_DEF) |
		FIELDX(DMA_CTRL_RDLY_CNT, DMA_CTRL_RDLY_CNT_DEF);

	AT_WRITE_REG(hw, REG_DMA_CTRL, dma_ctrl_data);
पूर्ण

/*
 * Stop the mac, transmit and receive units
 * hw - Struct containing variables accessed by shared code
 * वापस : 0  or  idle status (अगर error)
 */
अटल पूर्णांक atl1c_stop_mac(काष्ठा atl1c_hw *hw)
अणु
	u32 data;

	AT_READ_REG(hw, REG_RXQ_CTRL, &data);
	data &= ~RXQ_CTRL_EN;
	AT_WRITE_REG(hw, REG_RXQ_CTRL, data);

	AT_READ_REG(hw, REG_TXQ_CTRL, &data);
	data &= ~TXQ_CTRL_EN;
	AT_WRITE_REG(hw, REG_TXQ_CTRL, data);

	atl1c_रुको_until_idle(hw, IDLE_STATUS_RXQ_BUSY | IDLE_STATUS_TXQ_BUSY);

	AT_READ_REG(hw, REG_MAC_CTRL, &data);
	data &= ~(MAC_CTRL_TX_EN | MAC_CTRL_RX_EN);
	AT_WRITE_REG(hw, REG_MAC_CTRL, data);

	वापस (पूर्णांक)atl1c_रुको_until_idle(hw,
		IDLE_STATUS_TXMAC_BUSY | IDLE_STATUS_RXMAC_BUSY);
पूर्ण

अटल व्योम atl1c_start_mac(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा atl1c_hw *hw = &adapter->hw;
	u32 mac, txq, rxq;

	hw->mac_duplex = adapter->link_duplex == FULL_DUPLEX;
	hw->mac_speed = adapter->link_speed == SPEED_1000 ?
		atl1c_mac_speed_1000 : atl1c_mac_speed_10_100;

	AT_READ_REG(hw, REG_TXQ_CTRL, &txq);
	AT_READ_REG(hw, REG_RXQ_CTRL, &rxq);
	AT_READ_REG(hw, REG_MAC_CTRL, &mac);

	txq |= TXQ_CTRL_EN;
	rxq |= RXQ_CTRL_EN;
	mac |= MAC_CTRL_TX_EN | MAC_CTRL_TX_FLOW |
	       MAC_CTRL_RX_EN | MAC_CTRL_RX_FLOW |
	       MAC_CTRL_ADD_CRC | MAC_CTRL_PAD |
	       MAC_CTRL_BC_EN | MAC_CTRL_SINGLE_PAUSE_EN |
	       MAC_CTRL_HASH_ALG_CRC32;
	अगर (hw->mac_duplex)
		mac |= MAC_CTRL_DUPLX;
	अन्यथा
		mac &= ~MAC_CTRL_DUPLX;
	mac = FIELD_SETX(mac, MAC_CTRL_SPEED, hw->mac_speed);
	mac = FIELD_SETX(mac, MAC_CTRL_PRMLEN, hw->preamble_len);

	AT_WRITE_REG(hw, REG_TXQ_CTRL, txq);
	AT_WRITE_REG(hw, REG_RXQ_CTRL, rxq);
	AT_WRITE_REG(hw, REG_MAC_CTRL, mac);
पूर्ण

/*
 * Reset the transmit and receive units; mask and clear all पूर्णांकerrupts.
 * hw - Struct containing variables accessed by shared code
 * वापस : 0  or  idle status (अगर error)
 */
अटल पूर्णांक atl1c_reset_mac(काष्ठा atl1c_hw *hw)
अणु
	काष्ठा atl1c_adapter *adapter = hw->adapter;
	काष्ठा pci_dev *pdev = adapter->pdev;
	u32 ctrl_data = 0;

	atl1c_stop_mac(hw);
	/*
	 * Issue Soft Reset to the MAC.  This will reset the chip's
	 * transmit, receive, DMA.  It will not effect
	 * the current PCI configuration.  The global reset bit is self-
	 * clearing, and should clear within a microsecond.
	 */
	AT_READ_REG(hw, REG_MASTER_CTRL, &ctrl_data);
	ctrl_data |= MASTER_CTRL_OOB_DIS;
	AT_WRITE_REG(hw, REG_MASTER_CTRL, ctrl_data | MASTER_CTRL_SOFT_RST);

	AT_WRITE_FLUSH(hw);
	msleep(10);
	/* Wait at least 10ms क्रम All module to be Idle */

	अगर (atl1c_रुको_until_idle(hw, IDLE_STATUS_MASK)) अणु
		dev_err(&pdev->dev,
			"MAC state machine can't be idle since"
			" disabled for 10ms second\n");
		वापस -1;
	पूर्ण
	AT_WRITE_REG(hw, REG_MASTER_CTRL, ctrl_data);

	/* driver control speed/duplex */
	AT_READ_REG(hw, REG_MAC_CTRL, &ctrl_data);
	AT_WRITE_REG(hw, REG_MAC_CTRL, ctrl_data | MAC_CTRL_SPEED_MODE_SW);

	/* clk चयन setting */
	AT_READ_REG(hw, REG_SERDES, &ctrl_data);
	चयन (hw->nic_type) अणु
	हाल athr_l2c_b:
		ctrl_data &= ~(SERDES_PHY_CLK_SLOWDOWN |
				SERDES_MAC_CLK_SLOWDOWN);
		AT_WRITE_REG(hw, REG_SERDES, ctrl_data);
		अवरोध;
	हाल athr_l2c_b2:
	हाल athr_l1d_2:
		ctrl_data |= SERDES_PHY_CLK_SLOWDOWN | SERDES_MAC_CLK_SLOWDOWN;
		AT_WRITE_REG(hw, REG_SERDES, ctrl_data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम atl1c_disable_l0s_l1(काष्ठा atl1c_hw *hw)
अणु
	u16 ctrl_flags = hw->ctrl_flags;

	hw->ctrl_flags &= ~(ATL1C_ASPM_L0S_SUPPORT | ATL1C_ASPM_L1_SUPPORT);
	atl1c_set_aspm(hw, SPEED_0);
	hw->ctrl_flags = ctrl_flags;
पूर्ण

/*
 * Set ASPM state.
 * Enable/disable L0s/L1 depend on link state.
 */
अटल व्योम atl1c_set_aspm(काष्ठा atl1c_hw *hw, u16 link_speed)
अणु
	u32 pm_ctrl_data;
	u32 link_l1_समयr;

	AT_READ_REG(hw, REG_PM_CTRL, &pm_ctrl_data);
	pm_ctrl_data &= ~(PM_CTRL_ASPM_L1_EN |
			  PM_CTRL_ASPM_L0S_EN |
			  PM_CTRL_MAC_ASPM_CHK);
	/* L1 समयr */
	अगर (hw->nic_type == athr_l2c_b2 || hw->nic_type == athr_l1d_2) अणु
		pm_ctrl_data &= ~PMCTRL_TXL1_AFTER_L0S;
		link_l1_समयr =
			link_speed == SPEED_1000 || link_speed == SPEED_100 ?
			L1D_PMCTRL_L1_ENTRY_TM_16US : 1;
		pm_ctrl_data = FIELD_SETX(pm_ctrl_data,
			L1D_PMCTRL_L1_ENTRY_TM, link_l1_समयr);
	पूर्ण अन्यथा अणु
		link_l1_समयr = hw->nic_type == athr_l2c_b ?
			L2CB1_PM_CTRL_L1_ENTRY_TM : L1C_PM_CTRL_L1_ENTRY_TM;
		अगर (link_speed != SPEED_1000 && link_speed != SPEED_100)
			link_l1_समयr = 1;
		pm_ctrl_data = FIELD_SETX(pm_ctrl_data,
			PM_CTRL_L1_ENTRY_TIMER, link_l1_समयr);
	पूर्ण

	/* L0S/L1 enable */
	अगर ((hw->ctrl_flags & ATL1C_ASPM_L0S_SUPPORT) && link_speed != SPEED_0)
		pm_ctrl_data |= PM_CTRL_ASPM_L0S_EN | PM_CTRL_MAC_ASPM_CHK;
	अगर (hw->ctrl_flags & ATL1C_ASPM_L1_SUPPORT)
		pm_ctrl_data |= PM_CTRL_ASPM_L1_EN | PM_CTRL_MAC_ASPM_CHK;

	/* l2cb & l1d & l2cb2 & l1d2 */
	अगर (hw->nic_type == athr_l2c_b || hw->nic_type == athr_l1d ||
	    hw->nic_type == athr_l2c_b2 || hw->nic_type == athr_l1d_2) अणु
		pm_ctrl_data = FIELD_SETX(pm_ctrl_data,
			PM_CTRL_PM_REQ_TIMER, PM_CTRL_PM_REQ_TO_DEF);
		pm_ctrl_data |= PM_CTRL_RCVR_WT_TIMER |
				PM_CTRL_SERDES_PD_EX_L1 |
				PM_CTRL_CLK_SWH_L1;
		pm_ctrl_data &= ~(PM_CTRL_SERDES_L1_EN |
				  PM_CTRL_SERDES_PLL_L1_EN |
				  PM_CTRL_SERDES_BUFS_RX_L1_EN |
				  PM_CTRL_SA_DLY_EN |
				  PM_CTRL_HOTRST);
		/* disable l0s अगर link करोwn or l2cb */
		अगर (link_speed == SPEED_0 || hw->nic_type == athr_l2c_b)
			pm_ctrl_data &= ~PM_CTRL_ASPM_L0S_EN;
	पूर्ण अन्यथा अणु /* l1c */
		pm_ctrl_data =
			FIELD_SETX(pm_ctrl_data, PM_CTRL_L1_ENTRY_TIMER, 0);
		अगर (link_speed != SPEED_0) अणु
			pm_ctrl_data |= PM_CTRL_SERDES_L1_EN |
					PM_CTRL_SERDES_PLL_L1_EN |
					PM_CTRL_SERDES_BUFS_RX_L1_EN;
			pm_ctrl_data &= ~(PM_CTRL_SERDES_PD_EX_L1 |
					  PM_CTRL_CLK_SWH_L1 |
					  PM_CTRL_ASPM_L0S_EN |
					  PM_CTRL_ASPM_L1_EN);
		पूर्ण अन्यथा अणु /* link करोwn */
			pm_ctrl_data |= PM_CTRL_CLK_SWH_L1;
			pm_ctrl_data &= ~(PM_CTRL_SERDES_L1_EN |
					  PM_CTRL_SERDES_PLL_L1_EN |
					  PM_CTRL_SERDES_BUFS_RX_L1_EN |
					  PM_CTRL_ASPM_L0S_EN);
		पूर्ण
	पूर्ण
	AT_WRITE_REG(hw, REG_PM_CTRL, pm_ctrl_data);

	वापस;
पूर्ण

/**
 * atl1c_configure - Configure Transmit&Receive Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Tx /Rx unit of the MAC after a reset.
 */
अटल पूर्णांक atl1c_configure_mac(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा atl1c_hw *hw = &adapter->hw;
	u32 master_ctrl_data = 0;
	u32 पूर्णांकr_modrt_data;
	u32 data;

	AT_READ_REG(hw, REG_MASTER_CTRL, &master_ctrl_data);
	master_ctrl_data &= ~(MASTER_CTRL_TX_ITIMER_EN |
			      MASTER_CTRL_RX_ITIMER_EN |
			      MASTER_CTRL_INT_RDCLR);
	/* clear पूर्णांकerrupt status */
	AT_WRITE_REG(hw, REG_ISR, 0xFFFFFFFF);
	/*  Clear any WOL status */
	AT_WRITE_REG(hw, REG_WOL_CTRL, 0);
	/* set Interrupt Clear Timer
	 * HW will enable self to निश्चित पूर्णांकerrupt event to प्रणाली after
	 * रुकोing x-समय क्रम software to notअगरy it accept पूर्णांकerrupt.
	 */

	data = CLK_GATING_EN_ALL;
	अगर (hw->ctrl_flags & ATL1C_CLK_GATING_EN) अणु
		अगर (hw->nic_type == athr_l2c_b)
			data &= ~CLK_GATING_RXMAC_EN;
	पूर्ण अन्यथा
		data = 0;
	AT_WRITE_REG(hw, REG_CLK_GATING_CTRL, data);

	AT_WRITE_REG(hw, REG_INT_RETRIG_TIMER,
		hw->ict & INT_RETRIG_TIMER_MASK);

	atl1c_configure_des_ring(adapter);

	अगर (hw->ctrl_flags & ATL1C_INTR_MODRT_ENABLE) अणु
		पूर्णांकr_modrt_data = (hw->tx_imt & IRQ_MODRT_TIMER_MASK) <<
					IRQ_MODRT_TX_TIMER_SHIFT;
		पूर्णांकr_modrt_data |= (hw->rx_imt & IRQ_MODRT_TIMER_MASK) <<
					IRQ_MODRT_RX_TIMER_SHIFT;
		AT_WRITE_REG(hw, REG_IRQ_MODRT_TIMER_INIT, पूर्णांकr_modrt_data);
		master_ctrl_data |=
			MASTER_CTRL_TX_ITIMER_EN | MASTER_CTRL_RX_ITIMER_EN;
	पूर्ण

	अगर (hw->ctrl_flags & ATL1C_INTR_CLEAR_ON_READ)
		master_ctrl_data |= MASTER_CTRL_INT_RDCLR;

	master_ctrl_data |= MASTER_CTRL_SA_TIMER_EN;
	AT_WRITE_REG(hw, REG_MASTER_CTRL, master_ctrl_data);

	AT_WRITE_REG(hw, REG_SMB_STAT_TIMER,
		hw->smb_समयr & SMB_STAT_TIMER_MASK);

	/* set MTU */
	AT_WRITE_REG(hw, REG_MTU, hw->max_frame_size + ETH_HLEN +
			VLAN_HLEN + ETH_FCS_LEN);

	atl1c_configure_tx(adapter);
	atl1c_configure_rx(adapter);
	atl1c_configure_dma(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक atl1c_configure(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक num;

	atl1c_init_ring_ptrs(adapter);
	atl1c_set_multi(netdev);
	atl1c_restore_vlan(adapter);

	num = atl1c_alloc_rx_buffer(adapter, false);
	अगर (unlikely(num == 0))
		वापस -ENOMEM;

	अगर (atl1c_configure_mac(adapter))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम atl1c_update_hw_stats(काष्ठा atl1c_adapter *adapter)
अणु
	u16 hw_reg_addr = 0;
	अचिन्हित दीर्घ *stats_item = शून्य;
	u32 data;

	/* update rx status */
	hw_reg_addr = REG_MAC_RX_STATUS_BIN;
	stats_item  = &adapter->hw_stats.rx_ok;
	जबतक (hw_reg_addr <= REG_MAC_RX_STATUS_END) अणु
		AT_READ_REG(&adapter->hw, hw_reg_addr, &data);
		*stats_item += data;
		stats_item++;
		hw_reg_addr += 4;
	पूर्ण
/* update tx status */
	hw_reg_addr = REG_MAC_TX_STATUS_BIN;
	stats_item  = &adapter->hw_stats.tx_ok;
	जबतक (hw_reg_addr <= REG_MAC_TX_STATUS_END) अणु
		AT_READ_REG(&adapter->hw, hw_reg_addr, &data);
		*stats_item += data;
		stats_item++;
		hw_reg_addr += 4;
	पूर्ण
पूर्ण

/**
 * atl1c_get_stats - Get System Network Statistics
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns the address of the device statistics काष्ठाure.
 * The statistics are actually updated from the समयr callback.
 */
अटल काष्ठा net_device_stats *atl1c_get_stats(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1c_hw_stats  *hw_stats = &adapter->hw_stats;
	काष्ठा net_device_stats *net_stats = &netdev->stats;

	atl1c_update_hw_stats(adapter);
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

अटल अंतरभूत व्योम atl1c_clear_phy_पूर्णांक(काष्ठा atl1c_adapter *adapter)
अणु
	u16 phy_data;

	spin_lock(&adapter->mdio_lock);
	atl1c_पढ़ो_phy_reg(&adapter->hw, MII_ISR, &phy_data);
	spin_unlock(&adapter->mdio_lock);
पूर्ण

अटल पूर्णांक atl1c_clean_tx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा atl1c_adapter *adapter =
		container_of(napi, काष्ठा atl1c_adapter, tx_napi);
	काष्ठा atl1c_tpd_ring *tpd_ring = &adapter->tpd_ring[atl1c_trans_normal];
	काष्ठा atl1c_buffer *buffer_info;
	काष्ठा pci_dev *pdev = adapter->pdev;
	u16 next_to_clean = atomic_पढ़ो(&tpd_ring->next_to_clean);
	u16 hw_next_to_clean;
	अचिन्हित पूर्णांक total_bytes = 0, total_packets = 0;
	अचिन्हित दीर्घ flags;

	AT_READ_REGW(&adapter->hw, REG_TPD_PRI0_CIDX, &hw_next_to_clean);

	जबतक (next_to_clean != hw_next_to_clean) अणु
		buffer_info = &tpd_ring->buffer_info[next_to_clean];
		अगर (buffer_info->skb) अणु
			total_bytes += buffer_info->skb->len;
			total_packets++;
		पूर्ण
		atl1c_clean_buffer(pdev, buffer_info);
		अगर (++next_to_clean == tpd_ring->count)
			next_to_clean = 0;
		atomic_set(&tpd_ring->next_to_clean, next_to_clean);
	पूर्ण

	netdev_completed_queue(adapter->netdev, total_packets, total_bytes);

	अगर (netअगर_queue_stopped(adapter->netdev) &&
			netअगर_carrier_ok(adapter->netdev)) अणु
		netअगर_wake_queue(adapter->netdev);
	पूर्ण

	अगर (total_packets < budget) अणु
		napi_complete_करोne(napi, total_packets);
		spin_lock_irqsave(&adapter->hw.पूर्णांकr_mask_lock, flags);
		adapter->hw.पूर्णांकr_mask |= ISR_TX_PKT;
		AT_WRITE_REG(&adapter->hw, REG_IMR, adapter->hw.पूर्णांकr_mask);
		spin_unlock_irqrestore(&adapter->hw.पूर्णांकr_mask_lock, flags);
		वापस total_packets;
	पूर्ण
	वापस budget;
पूर्ण

/**
 * atl1c_पूर्णांकr - Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 */
अटल irqवापस_t atl1c_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा net_device *netdev  = data;
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा atl1c_hw *hw = &adapter->hw;
	पूर्णांक max_पूर्णांकs = AT_MAX_INT_WORK;
	पूर्णांक handled = IRQ_NONE;
	u32 status;
	u32 reg_data;

	करो अणु
		AT_READ_REG(hw, REG_ISR, &reg_data);
		status = reg_data & hw->पूर्णांकr_mask;

		अगर (status == 0 || (status & ISR_DIS_INT) != 0) अणु
			अगर (max_पूर्णांकs != AT_MAX_INT_WORK)
				handled = IRQ_HANDLED;
			अवरोध;
		पूर्ण
		/* link event */
		अगर (status & ISR_GPHY)
			atl1c_clear_phy_पूर्णांक(adapter);
		/* Ack ISR */
		AT_WRITE_REG(hw, REG_ISR, status | ISR_DIS_INT);
		अगर (status & ISR_RX_PKT) अणु
			अगर (likely(napi_schedule_prep(&adapter->napi))) अणु
				spin_lock(&hw->पूर्णांकr_mask_lock);
				hw->पूर्णांकr_mask &= ~ISR_RX_PKT;
				AT_WRITE_REG(hw, REG_IMR, hw->पूर्णांकr_mask);
				spin_unlock(&hw->पूर्णांकr_mask_lock);
				__napi_schedule(&adapter->napi);
			पूर्ण
		पूर्ण
		अगर (status & ISR_TX_PKT) अणु
			अगर (napi_schedule_prep(&adapter->tx_napi)) अणु
				spin_lock(&hw->पूर्णांकr_mask_lock);
				hw->पूर्णांकr_mask &= ~ISR_TX_PKT;
				AT_WRITE_REG(hw, REG_IMR, hw->पूर्णांकr_mask);
				spin_unlock(&hw->पूर्णांकr_mask_lock);
				__napi_schedule(&adapter->tx_napi);
			पूर्ण
		पूर्ण

		handled = IRQ_HANDLED;
		/* check अगर PCIE PHY Link करोwn */
		अगर (status & ISR_ERROR) अणु
			अगर (netअगर_msg_hw(adapter))
				dev_err(&pdev->dev,
					"atl1c hardware error (status = 0x%x)\n",
					status & ISR_ERROR);
			/* reset MAC */
			set_bit(ATL1C_WORK_EVENT_RESET, &adapter->work_event);
			schedule_work(&adapter->common_task);
			वापस IRQ_HANDLED;
		पूर्ण

		अगर (status & ISR_OVER)
			अगर (netअगर_msg_पूर्णांकr(adapter))
				dev_warn(&pdev->dev,
					"TX/RX overflow (status = 0x%x)\n",
					status & ISR_OVER);

		/* link event */
		अगर (status & (ISR_GPHY | ISR_MANUAL)) अणु
			netdev->stats.tx_carrier_errors++;
			atl1c_link_chg_event(adapter);
			अवरोध;
		पूर्ण

	पूर्ण जबतक (--max_पूर्णांकs > 0);
	/* re-enable Interrupt*/
	AT_WRITE_REG(&adapter->hw, REG_ISR, 0);
	वापस handled;
पूर्ण

अटल अंतरभूत व्योम atl1c_rx_checksum(काष्ठा atl1c_adapter *adapter,
		  काष्ठा sk_buff *skb, काष्ठा atl1c_recv_ret_status *prrs)
अणु
	/*
	 * The pid field in RRS in not correct someबार, so we
	 * cannot figure out अगर the packet is fragmented or not,
	 * so we tell the KERNEL CHECKSUM_NONE
	 */
	skb_checksum_none_निश्चित(skb);
पूर्ण

अटल काष्ठा sk_buff *atl1c_alloc_skb(काष्ठा atl1c_adapter *adapter,
				       bool napi_mode)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा page *page;

	अगर (adapter->rx_frag_size > PAGE_SIZE) अणु
		अगर (likely(napi_mode))
			वापस napi_alloc_skb(&adapter->napi,
					      adapter->rx_buffer_len);
		अन्यथा
			वापस netdev_alloc_skb_ip_align(adapter->netdev,
							 adapter->rx_buffer_len);
	पूर्ण

	page = adapter->rx_page;
	अगर (!page) अणु
		adapter->rx_page = page = alloc_page(GFP_ATOMIC);
		अगर (unlikely(!page))
			वापस शून्य;
		adapter->rx_page_offset = 0;
	पूर्ण

	skb = build_skb(page_address(page) + adapter->rx_page_offset,
			adapter->rx_frag_size);
	अगर (likely(skb)) अणु
		skb_reserve(skb, NET_SKB_PAD + NET_IP_ALIGN);
		adapter->rx_page_offset += adapter->rx_frag_size;
		अगर (adapter->rx_page_offset >= PAGE_SIZE)
			adapter->rx_page = शून्य;
		अन्यथा
			get_page(page);
	पूर्ण
	वापस skb;
पूर्ण

अटल पूर्णांक atl1c_alloc_rx_buffer(काष्ठा atl1c_adapter *adapter, bool napi_mode)
अणु
	काष्ठा atl1c_rfd_ring *rfd_ring = &adapter->rfd_ring;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा atl1c_buffer *buffer_info, *next_info;
	काष्ठा sk_buff *skb;
	व्योम *vir_addr = शून्य;
	u16 num_alloc = 0;
	u16 rfd_next_to_use, next_next;
	काष्ठा atl1c_rx_मुक्त_desc *rfd_desc;
	dma_addr_t mapping;

	next_next = rfd_next_to_use = rfd_ring->next_to_use;
	अगर (++next_next == rfd_ring->count)
		next_next = 0;
	buffer_info = &rfd_ring->buffer_info[rfd_next_to_use];
	next_info = &rfd_ring->buffer_info[next_next];

	जबतक (next_info->flags & ATL1C_BUFFER_FREE) अणु
		rfd_desc = ATL1C_RFD_DESC(rfd_ring, rfd_next_to_use);

		skb = atl1c_alloc_skb(adapter, napi_mode);
		अगर (unlikely(!skb)) अणु
			अगर (netअगर_msg_rx_err(adapter))
				dev_warn(&pdev->dev, "alloc rx buffer failed\n");
			अवरोध;
		पूर्ण

		/*
		 * Make buffer alignment 2 beyond a 16 byte boundary
		 * this will result in a 16 byte aligned IP header after
		 * the 14 byte MAC header is हटाओd
		 */
		vir_addr = skb->data;
		ATL1C_SET_BUFFER_STATE(buffer_info, ATL1C_BUFFER_BUSY);
		buffer_info->skb = skb;
		buffer_info->length = adapter->rx_buffer_len;
		mapping = dma_map_single(&pdev->dev, vir_addr,
					 buffer_info->length, DMA_FROM_DEVICE);
		अगर (unlikely(dma_mapping_error(&pdev->dev, mapping))) अणु
			dev_kमुक्त_skb(skb);
			buffer_info->skb = शून्य;
			buffer_info->length = 0;
			ATL1C_SET_BUFFER_STATE(buffer_info, ATL1C_BUFFER_FREE);
			netअगर_warn(adapter, rx_err, adapter->netdev, "RX pci_map_single failed");
			अवरोध;
		पूर्ण
		buffer_info->dma = mapping;
		ATL1C_SET_PCIMAP_TYPE(buffer_info, ATL1C_PCIMAP_SINGLE,
			ATL1C_PCIMAP_FROMDEVICE);
		rfd_desc->buffer_addr = cpu_to_le64(buffer_info->dma);
		rfd_next_to_use = next_next;
		अगर (++next_next == rfd_ring->count)
			next_next = 0;
		buffer_info = &rfd_ring->buffer_info[rfd_next_to_use];
		next_info = &rfd_ring->buffer_info[next_next];
		num_alloc++;
	पूर्ण

	अगर (num_alloc) अणु
		/* TODO: update mailbox here */
		wmb();
		rfd_ring->next_to_use = rfd_next_to_use;
		AT_WRITE_REG(&adapter->hw, REG_MB_RFD0_PROD_IDX,
			rfd_ring->next_to_use & MB_RFDX_PROD_IDX_MASK);
	पूर्ण

	वापस num_alloc;
पूर्ण

अटल व्योम atl1c_clean_rrd(काष्ठा atl1c_rrd_ring *rrd_ring,
			काष्ठा	atl1c_recv_ret_status *rrs, u16 num)
अणु
	u16 i;
	/* the relationship between rrd and rfd is one map one */
	क्रम (i = 0; i < num; i++, rrs = ATL1C_RRD_DESC(rrd_ring,
					rrd_ring->next_to_clean)) अणु
		rrs->word3 &= ~RRS_RXD_UPDATED;
		अगर (++rrd_ring->next_to_clean == rrd_ring->count)
			rrd_ring->next_to_clean = 0;
	पूर्ण
पूर्ण

अटल व्योम atl1c_clean_rfd(काष्ठा atl1c_rfd_ring *rfd_ring,
	काष्ठा atl1c_recv_ret_status *rrs, u16 num)
अणु
	u16 i;
	u16 rfd_index;
	काष्ठा atl1c_buffer *buffer_info = rfd_ring->buffer_info;

	rfd_index = (rrs->word0 >> RRS_RX_RFD_INDEX_SHIFT) &
			RRS_RX_RFD_INDEX_MASK;
	क्रम (i = 0; i < num; i++) अणु
		buffer_info[rfd_index].skb = शून्य;
		ATL1C_SET_BUFFER_STATE(&buffer_info[rfd_index],
					ATL1C_BUFFER_FREE);
		अगर (++rfd_index == rfd_ring->count)
			rfd_index = 0;
	पूर्ण
	rfd_ring->next_to_clean = rfd_index;
पूर्ण

अटल व्योम atl1c_clean_rx_irq(काष्ठा atl1c_adapter *adapter,
		   पूर्णांक *work_करोne, पूर्णांक work_to_करो)
अणु
	u16 rfd_num, rfd_index;
	u16 count = 0;
	u16 length;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा net_device *netdev  = adapter->netdev;
	काष्ठा atl1c_rfd_ring *rfd_ring = &adapter->rfd_ring;
	काष्ठा atl1c_rrd_ring *rrd_ring = &adapter->rrd_ring;
	काष्ठा sk_buff *skb;
	काष्ठा atl1c_recv_ret_status *rrs;
	काष्ठा atl1c_buffer *buffer_info;

	जबतक (1) अणु
		अगर (*work_करोne >= work_to_करो)
			अवरोध;
		rrs = ATL1C_RRD_DESC(rrd_ring, rrd_ring->next_to_clean);
		अगर (likely(RRS_RXD_IS_VALID(rrs->word3))) अणु
			rfd_num = (rrs->word0 >> RRS_RX_RFD_CNT_SHIFT) &
				RRS_RX_RFD_CNT_MASK;
			अगर (unlikely(rfd_num != 1))
				/* TODO support mul rfd*/
				अगर (netअगर_msg_rx_err(adapter))
					dev_warn(&pdev->dev,
						"Multi rfd not support yet!\n");
			जाओ rrs_checked;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
rrs_checked:
		atl1c_clean_rrd(rrd_ring, rrs, rfd_num);
		अगर (rrs->word3 & (RRS_RX_ERR_SUM | RRS_802_3_LEN_ERR)) अणु
			atl1c_clean_rfd(rfd_ring, rrs, rfd_num);
			अगर (netअगर_msg_rx_err(adapter))
				dev_warn(&pdev->dev,
					 "wrong packet! rrs word3 is %x\n",
					 rrs->word3);
			जारी;
		पूर्ण

		length = le16_to_cpu((rrs->word3 >> RRS_PKT_SIZE_SHIFT) &
				RRS_PKT_SIZE_MASK);
		/* Good Receive */
		अगर (likely(rfd_num == 1)) अणु
			rfd_index = (rrs->word0 >> RRS_RX_RFD_INDEX_SHIFT) &
					RRS_RX_RFD_INDEX_MASK;
			buffer_info = &rfd_ring->buffer_info[rfd_index];
			dma_unmap_single(&pdev->dev, buffer_info->dma,
					 buffer_info->length, DMA_FROM_DEVICE);
			skb = buffer_info->skb;
		पूर्ण अन्यथा अणु
			/* TODO */
			अगर (netअगर_msg_rx_err(adapter))
				dev_warn(&pdev->dev,
					"Multi rfd not support yet!\n");
			अवरोध;
		पूर्ण
		atl1c_clean_rfd(rfd_ring, rrs, rfd_num);
		skb_put(skb, length - ETH_FCS_LEN);
		skb->protocol = eth_type_trans(skb, netdev);
		atl1c_rx_checksum(adapter, skb, rrs);
		अगर (rrs->word3 & RRS_VLAN_INS) अणु
			u16 vlan;

			AT_TAG_TO_VLAN(rrs->vlan_tag, vlan);
			vlan = le16_to_cpu(vlan);
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan);
		पूर्ण
		napi_gro_receive(&adapter->napi, skb);

		(*work_करोne)++;
		count++;
	पूर्ण
	अगर (count)
		atl1c_alloc_rx_buffer(adapter, true);
पूर्ण

/**
 * atl1c_clean - NAPI Rx polling callback
 * @napi: napi info
 * @budget: limit of packets to clean
 */
अटल पूर्णांक atl1c_clean(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा atl1c_adapter *adapter =
			container_of(napi, काष्ठा atl1c_adapter, napi);
	पूर्णांक work_करोne = 0;
	अचिन्हित दीर्घ flags;

	/* Keep link state inक्रमmation with original netdev */
	अगर (!netअगर_carrier_ok(adapter->netdev))
		जाओ quit_polling;
	/* just enable one RXQ */
	atl1c_clean_rx_irq(adapter, &work_करोne, budget);

	अगर (work_करोne < budget) अणु
quit_polling:
		napi_complete_करोne(napi, work_करोne);
		spin_lock_irqsave(&adapter->hw.पूर्णांकr_mask_lock, flags);
		adapter->hw.पूर्णांकr_mask |= ISR_RX_PKT;
		AT_WRITE_REG(&adapter->hw, REG_IMR, adapter->hw.पूर्णांकr_mask);
		spin_unlock_irqrestore(&adapter->hw.पूर्णांकr_mask_lock, flags);
	पूर्ण
	वापस work_करोne;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER

/*
 * Polling 'interrupt' - used by things like netconsole to send skbs
 * without having to re-enable पूर्णांकerrupts. It's not called जबतक
 * the पूर्णांकerrupt routine is executing.
 */
अटल व्योम atl1c_netpoll(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	disable_irq(adapter->pdev->irq);
	atl1c_पूर्णांकr(adapter->pdev->irq, netdev);
	enable_irq(adapter->pdev->irq);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत u16 atl1c_tpd_avail(काष्ठा atl1c_adapter *adapter, क्रमागत atl1c_trans_queue type)
अणु
	काष्ठा atl1c_tpd_ring *tpd_ring = &adapter->tpd_ring[type];
	u16 next_to_use = 0;
	u16 next_to_clean = 0;

	next_to_clean = atomic_पढ़ो(&tpd_ring->next_to_clean);
	next_to_use   = tpd_ring->next_to_use;

	वापस (u16)(next_to_clean > next_to_use) ?
		(next_to_clean - next_to_use - 1) :
		(tpd_ring->count + next_to_clean - next_to_use - 1);
पूर्ण

/*
 * get next usable tpd
 * Note: should call atl1c_tdp_avail to make sure
 * there is enough tpd to use
 */
अटल काष्ठा atl1c_tpd_desc *atl1c_get_tpd(काष्ठा atl1c_adapter *adapter,
	क्रमागत atl1c_trans_queue type)
अणु
	काष्ठा atl1c_tpd_ring *tpd_ring = &adapter->tpd_ring[type];
	काष्ठा atl1c_tpd_desc *tpd_desc;
	u16 next_to_use = 0;

	next_to_use = tpd_ring->next_to_use;
	अगर (++tpd_ring->next_to_use == tpd_ring->count)
		tpd_ring->next_to_use = 0;
	tpd_desc = ATL1C_TPD_DESC(tpd_ring, next_to_use);
	स_रखो(tpd_desc, 0, माप(काष्ठा atl1c_tpd_desc));
	वापस	tpd_desc;
पूर्ण

अटल काष्ठा atl1c_buffer *
atl1c_get_tx_buffer(काष्ठा atl1c_adapter *adapter, काष्ठा atl1c_tpd_desc *tpd)
अणु
	काष्ठा atl1c_tpd_ring *tpd_ring = adapter->tpd_ring;

	वापस &tpd_ring->buffer_info[tpd -
			(काष्ठा atl1c_tpd_desc *)tpd_ring->desc];
पूर्ण

/* Calculate the transmit packet descript needed*/
अटल u16 atl1c_cal_tpd_req(स्थिर काष्ठा sk_buff *skb)
अणु
	u16 tpd_req;
	u16 proto_hdr_len = 0;

	tpd_req = skb_shinfo(skb)->nr_frags + 1;

	अगर (skb_is_gso(skb)) अणु
		proto_hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		अगर (proto_hdr_len < skb_headlen(skb))
			tpd_req++;
		अगर (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6)
			tpd_req++;
	पूर्ण
	वापस tpd_req;
पूर्ण

अटल पूर्णांक atl1c_tso_csum(काष्ठा atl1c_adapter *adapter,
			  काष्ठा sk_buff *skb,
			  काष्ठा atl1c_tpd_desc **tpd,
			  क्रमागत atl1c_trans_queue type)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
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
				अगर (netअगर_msg_tx_queued(adapter))
					dev_warn(&pdev->dev,
						"IPV4 tso with zero data??\n");
				जाओ check_sum;
			पूर्ण अन्यथा अणु
				ip_hdr(skb)->check = 0;
				tcp_hdr(skb)->check = ~csum_tcpudp_magic(
							ip_hdr(skb)->saddr,
							ip_hdr(skb)->daddr,
							0, IPPROTO_TCP, 0);
				(*tpd)->word1 |= 1 << TPD_IPV4_PACKET_SHIFT;
			पूर्ण
		पूर्ण

		अगर (offload_type & SKB_GSO_TCPV6) अणु
			काष्ठा atl1c_tpd_ext_desc *etpd =
				*(काष्ठा atl1c_tpd_ext_desc **)(tpd);

			स_रखो(etpd, 0, माप(काष्ठा atl1c_tpd_ext_desc));
			*tpd = atl1c_get_tpd(adapter, type);
			ipv6_hdr(skb)->payload_len = 0;
			/* check payload == 0 byte ? */
			hdr_len = (skb_transport_offset(skb) + tcp_hdrlen(skb));
			अगर (unlikely(skb->len == hdr_len)) अणु
				/* only xsum need */
				अगर (netअगर_msg_tx_queued(adapter))
					dev_warn(&pdev->dev,
						"IPV6 tso with zero data??\n");
				जाओ check_sum;
			पूर्ण अन्यथा
				tcp_v6_gso_csum_prep(skb);

			etpd->word1 |= 1 << TPD_LSO_EN_SHIFT;
			etpd->word1 |= 1 << TPD_LSO_VER_SHIFT;
			etpd->pkt_len = cpu_to_le32(skb->len);
			(*tpd)->word1 |= 1 << TPD_LSO_VER_SHIFT;
		पूर्ण

		(*tpd)->word1 |= 1 << TPD_LSO_EN_SHIFT;
		(*tpd)->word1 |= (skb_transport_offset(skb) & TPD_TCPHDR_OFFSET_MASK) <<
				TPD_TCPHDR_OFFSET_SHIFT;
		(*tpd)->word1 |= (skb_shinfo(skb)->gso_size & TPD_MSS_MASK) <<
				TPD_MSS_SHIFT;
		वापस 0;
	पूर्ण

check_sum:
	अगर (likely(skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		u8 css, cso;
		cso = skb_checksum_start_offset(skb);

		अगर (unlikely(cso & 0x1)) अणु
			अगर (netअगर_msg_tx_err(adapter))
				dev_err(&adapter->pdev->dev,
					"payload offset should not an event number\n");
			वापस -1;
		पूर्ण अन्यथा अणु
			css = cso + skb->csum_offset;

			(*tpd)->word1 |= ((cso >> 1) & TPD_PLOADOFFSET_MASK) <<
					TPD_PLOADOFFSET_SHIFT;
			(*tpd)->word1 |= ((css >> 1) & TPD_CCSUM_OFFSET_MASK) <<
					TPD_CCSUM_OFFSET_SHIFT;
			(*tpd)->word1 |= 1 << TPD_CCSUM_EN_SHIFT;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम atl1c_tx_rollback(काष्ठा atl1c_adapter *adpt,
			      काष्ठा atl1c_tpd_desc *first_tpd,
			      क्रमागत atl1c_trans_queue type)
अणु
	काष्ठा atl1c_tpd_ring *tpd_ring = &adpt->tpd_ring[type];
	काष्ठा atl1c_buffer *buffer_info;
	काष्ठा atl1c_tpd_desc *tpd;
	u16 first_index, index;

	first_index = first_tpd - (काष्ठा atl1c_tpd_desc *)tpd_ring->desc;
	index = first_index;
	जबतक (index != tpd_ring->next_to_use) अणु
		tpd = ATL1C_TPD_DESC(tpd_ring, index);
		buffer_info = &tpd_ring->buffer_info[index];
		atl1c_clean_buffer(adpt->pdev, buffer_info);
		स_रखो(tpd, 0, माप(काष्ठा atl1c_tpd_desc));
		अगर (++index == tpd_ring->count)
			index = 0;
	पूर्ण
	tpd_ring->next_to_use = first_index;
पूर्ण

अटल पूर्णांक atl1c_tx_map(काष्ठा atl1c_adapter *adapter,
		      काष्ठा sk_buff *skb, काष्ठा atl1c_tpd_desc *tpd,
			क्रमागत atl1c_trans_queue type)
अणु
	काष्ठा atl1c_tpd_desc *use_tpd = शून्य;
	काष्ठा atl1c_buffer *buffer_info = शून्य;
	u16 buf_len = skb_headlen(skb);
	u16 map_len = 0;
	u16 mapped_len = 0;
	u16 hdr_len = 0;
	u16 nr_frags;
	u16 f;
	पूर्णांक tso;

	nr_frags = skb_shinfo(skb)->nr_frags;
	tso = (tpd->word1 >> TPD_LSO_EN_SHIFT) & TPD_LSO_EN_MASK;
	अगर (tso) अणु
		/* TSO */
		map_len = hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		use_tpd = tpd;

		buffer_info = atl1c_get_tx_buffer(adapter, use_tpd);
		buffer_info->length = map_len;
		buffer_info->dma = dma_map_single(&adapter->pdev->dev,
						  skb->data, hdr_len,
						  DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(&adapter->pdev->dev, buffer_info->dma)))
			जाओ err_dma;
		ATL1C_SET_BUFFER_STATE(buffer_info, ATL1C_BUFFER_BUSY);
		ATL1C_SET_PCIMAP_TYPE(buffer_info, ATL1C_PCIMAP_SINGLE,
			ATL1C_PCIMAP_TODEVICE);
		mapped_len += map_len;
		use_tpd->buffer_addr = cpu_to_le64(buffer_info->dma);
		use_tpd->buffer_len = cpu_to_le16(buffer_info->length);
	पूर्ण

	अगर (mapped_len < buf_len) अणु
		/* mapped_len == 0, means we should use the first tpd,
		   which is given by caller  */
		अगर (mapped_len == 0)
			use_tpd = tpd;
		अन्यथा अणु
			use_tpd = atl1c_get_tpd(adapter, type);
			स_नकल(use_tpd, tpd, माप(काष्ठा atl1c_tpd_desc));
		पूर्ण
		buffer_info = atl1c_get_tx_buffer(adapter, use_tpd);
		buffer_info->length = buf_len - mapped_len;
		buffer_info->dma =
			dma_map_single(&adapter->pdev->dev,
				       skb->data + mapped_len,
				       buffer_info->length, DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(&adapter->pdev->dev, buffer_info->dma)))
			जाओ err_dma;

		ATL1C_SET_BUFFER_STATE(buffer_info, ATL1C_BUFFER_BUSY);
		ATL1C_SET_PCIMAP_TYPE(buffer_info, ATL1C_PCIMAP_SINGLE,
			ATL1C_PCIMAP_TODEVICE);
		use_tpd->buffer_addr = cpu_to_le64(buffer_info->dma);
		use_tpd->buffer_len  = cpu_to_le16(buffer_info->length);
	पूर्ण

	क्रम (f = 0; f < nr_frags; f++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[f];

		use_tpd = atl1c_get_tpd(adapter, type);
		स_नकल(use_tpd, tpd, माप(काष्ठा atl1c_tpd_desc));

		buffer_info = atl1c_get_tx_buffer(adapter, use_tpd);
		buffer_info->length = skb_frag_size(frag);
		buffer_info->dma = skb_frag_dma_map(&adapter->pdev->dev,
						    frag, 0,
						    buffer_info->length,
						    DMA_TO_DEVICE);
		अगर (dma_mapping_error(&adapter->pdev->dev, buffer_info->dma))
			जाओ err_dma;

		ATL1C_SET_BUFFER_STATE(buffer_info, ATL1C_BUFFER_BUSY);
		ATL1C_SET_PCIMAP_TYPE(buffer_info, ATL1C_PCIMAP_PAGE,
			ATL1C_PCIMAP_TODEVICE);
		use_tpd->buffer_addr = cpu_to_le64(buffer_info->dma);
		use_tpd->buffer_len  = cpu_to_le16(buffer_info->length);
	पूर्ण

	/* The last tpd */
	use_tpd->word1 |= 1 << TPD_EOP_SHIFT;
	/* The last buffer info contain the skb address,
	   so it will be मुक्त after unmap */
	buffer_info->skb = skb;

	वापस 0;

err_dma:
	buffer_info->dma = 0;
	buffer_info->length = 0;
	वापस -1;
पूर्ण

अटल व्योम atl1c_tx_queue(काष्ठा atl1c_adapter *adapter, काष्ठा sk_buff *skb,
			   काष्ठा atl1c_tpd_desc *tpd, क्रमागत atl1c_trans_queue type)
अणु
	काष्ठा atl1c_tpd_ring *tpd_ring = &adapter->tpd_ring[type];
	u16 reg;

	reg = type == atl1c_trans_high ? REG_TPD_PRI1_PIDX : REG_TPD_PRI0_PIDX;
	AT_WRITE_REGW(&adapter->hw, reg, tpd_ring->next_to_use);
पूर्ण

अटल netdev_tx_t atl1c_xmit_frame(काष्ठा sk_buff *skb,
					  काष्ठा net_device *netdev)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	u16 tpd_req;
	काष्ठा atl1c_tpd_desc *tpd;
	क्रमागत atl1c_trans_queue type = atl1c_trans_normal;

	अगर (test_bit(__AT_DOWN, &adapter->flags)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	tpd_req = atl1c_cal_tpd_req(skb);

	अगर (atl1c_tpd_avail(adapter, type) < tpd_req) अणु
		/* no enough descriptor, just stop queue */
		netअगर_stop_queue(netdev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	tpd = atl1c_get_tpd(adapter, type);

	/* करो TSO and check sum */
	अगर (atl1c_tso_csum(adapter, skb, &tpd, type) != 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (unlikely(skb_vlan_tag_present(skb))) अणु
		u16 vlan = skb_vlan_tag_get(skb);
		__le16 tag;

		vlan = cpu_to_le16(vlan);
		AT_VLAN_TO_TAG(vlan, tag);
		tpd->word1 |= 1 << TPD_INS_VTAG_SHIFT;
		tpd->vlan_tag = tag;
	पूर्ण

	अगर (skb_network_offset(skb) != ETH_HLEN)
		tpd->word1 |= 1 << TPD_ETH_TYPE_SHIFT; /* Ethernet frame */

	अगर (atl1c_tx_map(adapter, skb, tpd, type) < 0) अणु
		netअगर_info(adapter, tx_करोne, adapter->netdev,
			   "tx-skb dropped due to dma error\n");
		/* roll back tpd/buffer */
		atl1c_tx_rollback(adapter, tpd, type);
		dev_kमुक्त_skb_any(skb);
	पूर्ण अन्यथा अणु
		netdev_sent_queue(adapter->netdev, skb->len);
		atl1c_tx_queue(adapter, skb, tpd, type);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम atl1c_मुक्त_irq(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	मुक्त_irq(adapter->pdev->irq, netdev);

	अगर (adapter->have_msi)
		pci_disable_msi(adapter->pdev);
पूर्ण

अटल पूर्णांक atl1c_request_irq(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा pci_dev    *pdev   = adapter->pdev;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक flags = 0;
	पूर्णांक err = 0;

	adapter->have_msi = true;
	err = pci_enable_msi(adapter->pdev);
	अगर (err) अणु
		अगर (netअगर_msg_अगरup(adapter))
			dev_err(&pdev->dev,
				"Unable to allocate MSI interrupt Error: %d\n",
				err);
		adapter->have_msi = false;
	पूर्ण

	अगर (!adapter->have_msi)
		flags |= IRQF_SHARED;
	err = request_irq(adapter->pdev->irq, atl1c_पूर्णांकr, flags,
			netdev->name, netdev);
	अगर (err) अणु
		अगर (netअगर_msg_अगरup(adapter))
			dev_err(&pdev->dev,
				"Unable to allocate interrupt Error: %d\n",
				err);
		अगर (adapter->have_msi)
			pci_disable_msi(adapter->pdev);
		वापस err;
	पूर्ण
	अगर (netअगर_msg_अगरup(adapter))
		dev_dbg(&pdev->dev, "atl1c_request_irq OK\n");
	वापस err;
पूर्ण


अटल व्योम atl1c_reset_dma_ring(काष्ठा atl1c_adapter *adapter)
अणु
	/* release tx-pending skbs and reset tx/rx ring index */
	atl1c_clean_tx_ring(adapter, atl1c_trans_normal);
	atl1c_clean_tx_ring(adapter, atl1c_trans_high);
	atl1c_clean_rx_ring(adapter);
पूर्ण

अटल पूर्णांक atl1c_up(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err;

	netअगर_carrier_off(netdev);

	err = atl1c_configure(adapter);
	अगर (unlikely(err))
		जाओ err_up;

	err = atl1c_request_irq(adapter);
	अगर (unlikely(err))
		जाओ err_up;

	atl1c_check_link_status(adapter);
	clear_bit(__AT_DOWN, &adapter->flags);
	napi_enable(&adapter->napi);
	napi_enable(&adapter->tx_napi);
	atl1c_irq_enable(adapter);
	netअगर_start_queue(netdev);
	वापस err;

err_up:
	atl1c_clean_rx_ring(adapter);
	वापस err;
पूर्ण

अटल व्योम atl1c_करोwn(काष्ठा atl1c_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	atl1c_del_समयr(adapter);
	adapter->work_event = 0; /* clear all event */
	/* संकेत that we're करोwn so the पूर्णांकerrupt handler करोes not
	 * reschedule our watchकरोg समयr */
	set_bit(__AT_DOWN, &adapter->flags);
	netअगर_carrier_off(netdev);
	napi_disable(&adapter->napi);
	napi_disable(&adapter->tx_napi);
	atl1c_irq_disable(adapter);
	atl1c_मुक्त_irq(adapter);
	/* disable ASPM अगर device inactive */
	atl1c_disable_l0s_l1(&adapter->hw);
	/* reset MAC to disable all RX/TX */
	atl1c_reset_mac(&adapter->hw);
	msleep(1);

	adapter->link_speed = SPEED_0;
	adapter->link_duplex = -1;
	atl1c_reset_dma_ring(adapter);
पूर्ण

/**
 * atl1c_खोलो - Called when a network पूर्णांकerface is made active
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
अटल पूर्णांक atl1c_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err;

	/* disallow खोलो during test */
	अगर (test_bit(__AT_TESTING, &adapter->flags))
		वापस -EBUSY;

	/* allocate rx/tx dma buffer & descriptors */
	err = atl1c_setup_ring_resources(adapter);
	अगर (unlikely(err))
		वापस err;

	err = atl1c_up(adapter);
	अगर (unlikely(err))
		जाओ err_up;

	वापस 0;

err_up:
	atl1c_मुक्त_irq(adapter);
	atl1c_मुक्त_ring_resources(adapter);
	atl1c_reset_mac(&adapter->hw);
	वापस err;
पूर्ण

/**
 * atl1c_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are मुक्तd.
 */
अटल पूर्णांक atl1c_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	WARN_ON(test_bit(__AT_RESETTING, &adapter->flags));
	set_bit(__AT_DOWN, &adapter->flags);
	cancel_work_sync(&adapter->common_task);
	atl1c_करोwn(adapter);
	atl1c_मुक्त_ring_resources(adapter);
	वापस 0;
पूर्ण

अटल पूर्णांक atl1c_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1c_hw *hw = &adapter->hw;
	u32 wufc = adapter->wol;

	atl1c_disable_l0s_l1(hw);
	अगर (netअगर_running(netdev)) अणु
		WARN_ON(test_bit(__AT_RESETTING, &adapter->flags));
		atl1c_करोwn(adapter);
	पूर्ण
	netअगर_device_detach(netdev);

	अगर (wufc)
		अगर (atl1c_phy_to_ps_link(hw) != 0)
			dev_dbg(dev, "phy power saving failed");

	atl1c_घातer_saving(hw, wufc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक atl1c_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	AT_WRITE_REG(&adapter->hw, REG_WOL_CTRL, 0);
	atl1c_reset_pcie(&adapter->hw, ATL1C_PCIE_L0S_L1_DISABLE);

	atl1c_phy_reset(&adapter->hw);
	atl1c_reset_mac(&adapter->hw);
	atl1c_phy_init(&adapter->hw);

	netअगर_device_attach(netdev);
	अगर (netअगर_running(netdev))
		atl1c_up(adapter);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम atl1c_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	atl1c_suspend(&pdev->dev);
	pci_wake_from_d3(pdev, adapter->wol);
	pci_set_घातer_state(pdev, PCI_D3hot);
पूर्ण

अटल स्थिर काष्ठा net_device_ops atl1c_netdev_ops = अणु
	.nकरो_खोलो		= atl1c_खोलो,
	.nकरो_stop		= atl1c_बंद,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_start_xmit		= atl1c_xmit_frame,
	.nकरो_set_mac_address	= atl1c_set_mac_addr,
	.nकरो_set_rx_mode	= atl1c_set_multi,
	.nकरो_change_mtu		= atl1c_change_mtu,
	.nकरो_fix_features	= atl1c_fix_features,
	.nकरो_set_features	= atl1c_set_features,
	.nकरो_करो_ioctl		= atl1c_ioctl,
	.nकरो_tx_समयout		= atl1c_tx_समयout,
	.nकरो_get_stats		= atl1c_get_stats,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= atl1c_netpoll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक atl1c_init_netdev(काष्ठा net_device *netdev, काष्ठा pci_dev *pdev)
अणु
	SET_NETDEV_DEV(netdev, &pdev->dev);
	pci_set_drvdata(pdev, netdev);

	netdev->netdev_ops = &atl1c_netdev_ops;
	netdev->watchकरोg_समयo = AT_TX_WATCHDOG;
	netdev->min_mtu = ETH_ZLEN - (ETH_HLEN + VLAN_HLEN);
	atl1c_set_ethtool_ops(netdev);

	/* TODO: add when पढ़ोy */
	netdev->hw_features =	NETIF_F_SG		|
				NETIF_F_HW_CSUM		|
				NETIF_F_HW_VLAN_CTAG_RX	|
				NETIF_F_TSO		|
				NETIF_F_TSO6;
	netdev->features =	netdev->hw_features	|
				NETIF_F_HW_VLAN_CTAG_TX;
	वापस 0;
पूर्ण

/**
 * atl1c_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in atl1c_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * atl1c_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 */
अटल पूर्णांक atl1c_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा atl1c_adapter *adapter;
	अटल पूर्णांक cards_found;

	पूर्णांक err = 0;

	/* enable device (incl. PCI PM wakeup and hotplug setup) */
	err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot enable PCI device\n");
		वापस err;
	पूर्ण

	/*
	 * The atl1c chip can DMA to 64-bit addresses, but it uses a single
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

	err = pci_request_regions(pdev, atl1c_driver_name);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot obtain PCI resources\n");
		जाओ err_pci_reg;
	पूर्ण

	pci_set_master(pdev);

	netdev = alloc_etherdev(माप(काष्ठा atl1c_adapter));
	अगर (netdev == शून्य) अणु
		err = -ENOMEM;
		जाओ err_alloc_etherdev;
	पूर्ण

	err = atl1c_init_netdev(netdev, pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "init netdevice failed\n");
		जाओ err_init_netdev;
	पूर्ण
	adapter = netdev_priv(netdev);
	adapter->bd_number = cards_found;
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	adapter->hw.adapter = adapter;
	adapter->msg_enable = netअगर_msg_init(-1, atl1c_शेष_msg);
	adapter->hw.hw_addr = ioremap(pci_resource_start(pdev, 0), pci_resource_len(pdev, 0));
	अगर (!adapter->hw.hw_addr) अणु
		err = -EIO;
		dev_err(&pdev->dev, "cannot map device registers\n");
		जाओ err_ioremap;
	पूर्ण

	/* init mii data */
	adapter->mii.dev = netdev;
	adapter->mii.mdio_पढ़ो  = atl1c_mdio_पढ़ो;
	adapter->mii.mdio_ग_लिखो = atl1c_mdio_ग_लिखो;
	adapter->mii.phy_id_mask = 0x1f;
	adapter->mii.reg_num_mask = MDIO_CTRL_REG_MASK;
	dev_set_thपढ़ोed(netdev, true);
	netअगर_napi_add(netdev, &adapter->napi, atl1c_clean, 64);
	netअगर_napi_add(netdev, &adapter->tx_napi, atl1c_clean_tx, 64);
	समयr_setup(&adapter->phy_config_समयr, atl1c_phy_config, 0);
	/* setup the निजी काष्ठाure */
	err = atl1c_sw_init(adapter);
	अगर (err) अणु
		dev_err(&pdev->dev, "net device private data init failed\n");
		जाओ err_sw_init;
	पूर्ण
	/* set max MTU */
	atl1c_set_max_mtu(netdev);

	atl1c_reset_pcie(&adapter->hw, ATL1C_PCIE_L0S_L1_DISABLE);

	/* Init GPHY as early as possible due to घातer saving issue  */
	atl1c_phy_reset(&adapter->hw);

	err = atl1c_reset_mac(&adapter->hw);
	अगर (err) अणु
		err = -EIO;
		जाओ err_reset;
	पूर्ण

	/* reset the controller to
	 * put the device in a known good starting state */
	err = atl1c_phy_init(&adapter->hw);
	अगर (err) अणु
		err = -EIO;
		जाओ err_reset;
	पूर्ण
	अगर (atl1c_पढ़ो_mac_addr(&adapter->hw)) अणु
		/* got a अक्रमom MAC address, set NET_ADDR_RANDOM to netdev */
		netdev->addr_assign_type = NET_ADDR_RANDOM;
	पूर्ण
	स_नकल(netdev->dev_addr, adapter->hw.mac_addr, netdev->addr_len);
	अगर (netअगर_msg_probe(adapter))
		dev_dbg(&pdev->dev, "mac address : %pM\n",
			adapter->hw.mac_addr);

	atl1c_hw_set_mac_addr(&adapter->hw, adapter->hw.mac_addr);
	INIT_WORK(&adapter->common_task, atl1c_common_task);
	adapter->work_event = 0;
	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "register netdevice failed\n");
		जाओ err_रेजिस्टर;
	पूर्ण

	cards_found++;
	वापस 0;

err_reset:
err_रेजिस्टर:
err_sw_init:
	iounmap(adapter->hw.hw_addr);
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
 * atl1c_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * atl1c_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.  The could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 */
अटल व्योम atl1c_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	unरेजिस्टर_netdev(netdev);
	/* restore permanent address */
	atl1c_hw_set_mac_addr(&adapter->hw, adapter->hw.perm_mac_addr);
	atl1c_phy_disable(&adapter->hw);

	iounmap(adapter->hw.hw_addr);

	pci_release_regions(pdev);
	pci_disable_device(pdev);
	मुक्त_netdev(netdev);
पूर्ण

/**
 * atl1c_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t atl1c_io_error_detected(काष्ठा pci_dev *pdev,
						pci_channel_state_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	netअगर_device_detach(netdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (netअगर_running(netdev))
		atl1c_करोwn(adapter);

	pci_disable_device(pdev);

	/* Request a slot slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * atl1c_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot. Implementation
 * resembles the first-half of the e1000_resume routine.
 */
अटल pci_ers_result_t atl1c_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	अगर (pci_enable_device(pdev)) अणु
		अगर (netअगर_msg_hw(adapter))
			dev_err(&pdev->dev,
				"Cannot re-enable PCI device after reset\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
	pci_set_master(pdev);

	pci_enable_wake(pdev, PCI_D3hot, 0);
	pci_enable_wake(pdev, PCI_D3cold, 0);

	atl1c_reset_mac(&adapter->hw);

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * atl1c_io_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells us that
 * its OK to resume normal operation. Implementation resembles the
 * second-half of the atl1c_resume routine.
 */
अटल व्योम atl1c_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl1c_adapter *adapter = netdev_priv(netdev);

	अगर (netअगर_running(netdev)) अणु
		अगर (atl1c_up(adapter)) अणु
			अगर (netअगर_msg_hw(adapter))
				dev_err(&pdev->dev,
					"Cannot bring device back up after reset\n");
			वापस;
		पूर्ण
	पूर्ण

	netअगर_device_attach(netdev);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers atl1c_err_handler = अणु
	.error_detected = atl1c_io_error_detected,
	.slot_reset = atl1c_io_slot_reset,
	.resume = atl1c_io_resume,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(atl1c_pm_ops, atl1c_suspend, atl1c_resume);

अटल काष्ठा pci_driver atl1c_driver = अणु
	.name     = atl1c_driver_name,
	.id_table = atl1c_pci_tbl,
	.probe    = atl1c_probe,
	.हटाओ   = atl1c_हटाओ,
	.shutकरोwn = atl1c_shutकरोwn,
	.err_handler = &atl1c_err_handler,
	.driver.pm = &atl1c_pm_ops,
पूर्ण;

module_pci_driver(atl1c_driver);
