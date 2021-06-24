<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 2006 - 2007 Atheros Corporation. All rights reserved.
 * Copyright(c) 2007 - 2008 Chris Snook <csnook@redhat.com>
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 */

#समावेश <linux/atomic.h>
#समावेश <linux/crc32.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/in.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ip.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/mii.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/pm.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/tcp.h>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश "atl2.h"

अटल स्थिर अक्षर atl2_driver_name[] = "atl2";
अटल स्थिर काष्ठा ethtool_ops atl2_ethtool_ops;

MODULE_AUTHOR("Atheros Corporation <xiong.huang@atheros.com>, Chris Snook <csnook@redhat.com>");
MODULE_DESCRIPTION("Atheros Fast Ethernet Network Driver");
MODULE_LICENSE("GPL");

/*
 * atl2_pci_tbl - PCI Device ID Table
 */
अटल स्थिर काष्ठा pci_device_id atl2_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_ATTANSIC, PCI_DEVICE_ID_ATTANSIC_L2)पूर्ण,
	/* required last entry */
	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, atl2_pci_tbl);

अटल व्योम atl2_check_options(काष्ठा atl2_adapter *adapter);

/**
 * atl2_sw_init - Initialize general software काष्ठाures (काष्ठा atl2_adapter)
 * @adapter: board निजी काष्ठाure to initialize
 *
 * atl2_sw_init initializes the Adapter निजी data काष्ठाure.
 * Fields are initialized based on PCI device inक्रमmation and
 * OS network device settings (MTU size).
 */
अटल पूर्णांक atl2_sw_init(काष्ठा atl2_adapter *adapter)
अणु
	काष्ठा atl2_hw *hw = &adapter->hw;
	काष्ठा pci_dev *pdev = adapter->pdev;

	/* PCI config space info */
	hw->venकरोr_id = pdev->venकरोr;
	hw->device_id = pdev->device;
	hw->subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	hw->subप्रणाली_id = pdev->subप्रणाली_device;
	hw->revision_id  = pdev->revision;

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &hw->pci_cmd_word);

	adapter->wol = 0;
	adapter->ict = 50000;  /* ~100ms */
	adapter->link_speed = SPEED_0;   /* hardware init */
	adapter->link_duplex = FULL_DUPLEX;

	hw->phy_configured = false;
	hw->preamble_len = 7;
	hw->ipgt = 0x60;
	hw->min_अगरg = 0x50;
	hw->ipgr1 = 0x40;
	hw->ipgr2 = 0x60;
	hw->retry_buf = 2;
	hw->max_retry = 0xf;
	hw->lcol = 0x37;
	hw->jam_ipg = 7;
	hw->fc_rxd_hi = 0;
	hw->fc_rxd_lo = 0;
	hw->max_frame_size = adapter->netdev->mtu;

	spin_lock_init(&adapter->stats_lock);

	set_bit(__ATL2_DOWN, &adapter->flags);

	वापस 0;
पूर्ण

/**
 * atl2_set_multi - Multicast and Promiscuous mode set
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The set_multi entry poपूर्णांक is called whenever the multicast address
 * list or the network पूर्णांकerface flags are updated.  This routine is
 * responsible क्रम configuring the hardware क्रम proper multicast,
 * promiscuous mode, and all-multi behavior.
 */
अटल व्योम atl2_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl2_hw *hw = &adapter->hw;
	काष्ठा netdev_hw_addr *ha;
	u32 rctl;
	u32 hash_value;

	/* Check क्रम Promiscuous and All Multicast modes */
	rctl = ATL2_READ_REG(hw, REG_MAC_CTRL);

	अगर (netdev->flags & IFF_PROMISC) अणु
		rctl |= MAC_CTRL_PROMIS_EN;
	पूर्ण अन्यथा अगर (netdev->flags & IFF_ALLMULTI) अणु
		rctl |= MAC_CTRL_MC_ALL_EN;
		rctl &= ~MAC_CTRL_PROMIS_EN;
	पूर्ण अन्यथा
		rctl &= ~(MAC_CTRL_PROMIS_EN | MAC_CTRL_MC_ALL_EN);

	ATL2_WRITE_REG(hw, REG_MAC_CTRL, rctl);

	/* clear the old settings from the multicast hash table */
	ATL2_WRITE_REG(hw, REG_RX_HASH_TABLE, 0);
	ATL2_WRITE_REG_ARRAY(hw, REG_RX_HASH_TABLE, 1, 0);

	/* comoute mc addresses' hash value ,and put it पूर्णांकo hash table */
	netdev_क्रम_each_mc_addr(ha, netdev) अणु
		hash_value = atl2_hash_mc_addr(hw, ha->addr);
		atl2_hash_set(hw, hash_value);
	पूर्ण
पूर्ण

अटल व्योम init_ring_ptrs(काष्ठा atl2_adapter *adapter)
अणु
	/* Read / Write Ptr Initialize: */
	adapter->txd_ग_लिखो_ptr = 0;
	atomic_set(&adapter->txd_पढ़ो_ptr, 0);

	adapter->rxd_पढ़ो_ptr = 0;
	adapter->rxd_ग_लिखो_ptr = 0;

	atomic_set(&adapter->txs_ग_लिखो_ptr, 0);
	adapter->txs_next_clear = 0;
पूर्ण

/**
 * atl2_configure - Configure Transmit&Receive Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Tx /Rx unit of the MAC after a reset.
 */
अटल पूर्णांक atl2_configure(काष्ठा atl2_adapter *adapter)
अणु
	काष्ठा atl2_hw *hw = &adapter->hw;
	u32 value;

	/* clear पूर्णांकerrupt status */
	ATL2_WRITE_REG(&adapter->hw, REG_ISR, 0xffffffff);

	/* set MAC Address */
	value = (((u32)hw->mac_addr[2]) << 24) |
		(((u32)hw->mac_addr[3]) << 16) |
		(((u32)hw->mac_addr[4]) << 8) |
		(((u32)hw->mac_addr[5]));
	ATL2_WRITE_REG(hw, REG_MAC_STA_ADDR, value);
	value = (((u32)hw->mac_addr[0]) << 8) |
		(((u32)hw->mac_addr[1]));
	ATL2_WRITE_REG(hw, (REG_MAC_STA_ADDR+4), value);

	/* HI base address */
	ATL2_WRITE_REG(hw, REG_DESC_BASE_ADDR_HI,
		(u32)((adapter->ring_dma & 0xffffffff00000000ULL) >> 32));

	/* LO base address */
	ATL2_WRITE_REG(hw, REG_TXD_BASE_ADDR_LO,
		(u32)(adapter->txd_dma & 0x00000000ffffffffULL));
	ATL2_WRITE_REG(hw, REG_TXS_BASE_ADDR_LO,
		(u32)(adapter->txs_dma & 0x00000000ffffffffULL));
	ATL2_WRITE_REG(hw, REG_RXD_BASE_ADDR_LO,
		(u32)(adapter->rxd_dma & 0x00000000ffffffffULL));

	/* element count */
	ATL2_WRITE_REGW(hw, REG_TXD_MEM_SIZE, (u16)(adapter->txd_ring_size/4));
	ATL2_WRITE_REGW(hw, REG_TXS_MEM_SIZE, (u16)adapter->txs_ring_size);
	ATL2_WRITE_REGW(hw, REG_RXD_BUF_NUM,  (u16)adapter->rxd_ring_size);

	/* config Internal SRAM */
/*
    ATL2_WRITE_REGW(hw, REG_SRAM_TXRAM_END, sram_tx_end);
    ATL2_WRITE_REGW(hw, REG_SRAM_TXRAM_END, sram_rx_end);
*/

	/* config IPG/IFG */
	value = (((u32)hw->ipgt & MAC_IPG_IFG_IPGT_MASK) <<
		MAC_IPG_IFG_IPGT_SHIFT) |
		(((u32)hw->min_अगरg & MAC_IPG_IFG_MIFG_MASK) <<
		MAC_IPG_IFG_MIFG_SHIFT) |
		(((u32)hw->ipgr1 & MAC_IPG_IFG_IPGR1_MASK) <<
		MAC_IPG_IFG_IPGR1_SHIFT)|
		(((u32)hw->ipgr2 & MAC_IPG_IFG_IPGR2_MASK) <<
		MAC_IPG_IFG_IPGR2_SHIFT);
	ATL2_WRITE_REG(hw, REG_MAC_IPG_IFG, value);

	/* config  Half-Duplex Control */
	value = ((u32)hw->lcol & MAC_HALF_DUPLX_CTRL_LCOL_MASK) |
		(((u32)hw->max_retry & MAC_HALF_DUPLX_CTRL_RETRY_MASK) <<
		MAC_HALF_DUPLX_CTRL_RETRY_SHIFT) |
		MAC_HALF_DUPLX_CTRL_EXC_DEF_EN |
		(0xa << MAC_HALF_DUPLX_CTRL_ABEBT_SHIFT) |
		(((u32)hw->jam_ipg & MAC_HALF_DUPLX_CTRL_JAMIPG_MASK) <<
		MAC_HALF_DUPLX_CTRL_JAMIPG_SHIFT);
	ATL2_WRITE_REG(hw, REG_MAC_HALF_DUPLX_CTRL, value);

	/* set Interrupt Moderator Timer */
	ATL2_WRITE_REGW(hw, REG_IRQ_MODU_TIMER_INIT, adapter->imt);
	ATL2_WRITE_REG(hw, REG_MASTER_CTRL, MASTER_CTRL_ITIMER_EN);

	/* set Interrupt Clear Timer */
	ATL2_WRITE_REGW(hw, REG_CMBDISDMA_TIMER, adapter->ict);

	/* set MTU */
	ATL2_WRITE_REG(hw, REG_MTU, adapter->netdev->mtu +
		ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN);

	/* 1590 */
	ATL2_WRITE_REG(hw, REG_TX_CUT_THRESH, 0x177);

	/* flow control */
	ATL2_WRITE_REGW(hw, REG_PAUSE_ON_TH, hw->fc_rxd_hi);
	ATL2_WRITE_REGW(hw, REG_PAUSE_OFF_TH, hw->fc_rxd_lo);

	/* Init mailbox */
	ATL2_WRITE_REGW(hw, REG_MB_TXD_WR_IDX, (u16)adapter->txd_ग_लिखो_ptr);
	ATL2_WRITE_REGW(hw, REG_MB_RXD_RD_IDX, (u16)adapter->rxd_पढ़ो_ptr);

	/* enable DMA पढ़ो/ग_लिखो */
	ATL2_WRITE_REGB(hw, REG_DMAR, DMAR_EN);
	ATL2_WRITE_REGB(hw, REG_DMAW, DMAW_EN);

	value = ATL2_READ_REG(&adapter->hw, REG_ISR);
	अगर ((value & ISR_PHY_LINKDOWN) != 0)
		value = 1; /* config failed */
	अन्यथा
		value = 0;

	/* clear all पूर्णांकerrupt status */
	ATL2_WRITE_REG(&adapter->hw, REG_ISR, 0x3fffffff);
	ATL2_WRITE_REG(&adapter->hw, REG_ISR, 0);
	वापस value;
पूर्ण

/**
 * atl2_setup_ring_resources - allocate Tx / RX descriptor resources
 * @adapter: board निजी काष्ठाure
 *
 * Return 0 on success, negative on failure
 */
अटल s32 atl2_setup_ring_resources(काष्ठा atl2_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक size;
	u8 offset = 0;

	/* real ring DMA buffer */
	adapter->ring_size = size =
		adapter->txd_ring_size * 1 + 7 +	/* dword align */
		adapter->txs_ring_size * 4 + 7 +	/* dword align */
		adapter->rxd_ring_size * 1536 + 127;	/* 128bytes align */

	adapter->ring_vir_addr = dma_alloc_coherent(&pdev->dev, size,
						    &adapter->ring_dma, GFP_KERNEL);
	अगर (!adapter->ring_vir_addr)
		वापस -ENOMEM;

	/* Init TXD Ring */
	adapter->txd_dma = adapter->ring_dma ;
	offset = (adapter->txd_dma & 0x7) ? (8 - (adapter->txd_dma & 0x7)) : 0;
	adapter->txd_dma += offset;
	adapter->txd_ring = adapter->ring_vir_addr + offset;

	/* Init TXS Ring */
	adapter->txs_dma = adapter->txd_dma + adapter->txd_ring_size;
	offset = (adapter->txs_dma & 0x7) ? (8 - (adapter->txs_dma & 0x7)) : 0;
	adapter->txs_dma += offset;
	adapter->txs_ring = (काष्ठा tx_pkt_status *)
		(((u8 *)adapter->txd_ring) + (adapter->txd_ring_size + offset));

	/* Init RXD Ring */
	adapter->rxd_dma = adapter->txs_dma + adapter->txs_ring_size * 4;
	offset = (adapter->rxd_dma & 127) ?
		(128 - (adapter->rxd_dma & 127)) : 0;
	अगर (offset > 7)
		offset -= 8;
	अन्यथा
		offset += (128 - 8);

	adapter->rxd_dma += offset;
	adapter->rxd_ring = (काष्ठा rx_desc *) (((u8 *)adapter->txs_ring) +
		(adapter->txs_ring_size * 4 + offset));

/*
 * Read / Write Ptr Initialize:
 *      init_ring_ptrs(adapter);
 */
	वापस 0;
पूर्ण

/**
 * atl2_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 * @adapter: board निजी काष्ठाure
 */
अटल अंतरभूत व्योम atl2_irq_enable(काष्ठा atl2_adapter *adapter)
अणु
	ATL2_WRITE_REG(&adapter->hw, REG_IMR, IMR_NORMAL_MASK);
	ATL2_WRITE_FLUSH(&adapter->hw);
पूर्ण

/**
 * atl2_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 * @adapter: board निजी काष्ठाure
 */
अटल अंतरभूत व्योम atl2_irq_disable(काष्ठा atl2_adapter *adapter)
अणु
    ATL2_WRITE_REG(&adapter->hw, REG_IMR, 0);
    ATL2_WRITE_FLUSH(&adapter->hw);
    synchronize_irq(adapter->pdev->irq);
पूर्ण

अटल व्योम __atl2_vlan_mode(netdev_features_t features, u32 *ctrl)
अणु
	अगर (features & NETIF_F_HW_VLAN_CTAG_RX) अणु
		/* enable VLAN tag insert/strip */
		*ctrl |= MAC_CTRL_RMV_VLAN;
	पूर्ण अन्यथा अणु
		/* disable VLAN tag insert/strip */
		*ctrl &= ~MAC_CTRL_RMV_VLAN;
	पूर्ण
पूर्ण

अटल व्योम atl2_vlan_mode(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	u32 ctrl;

	atl2_irq_disable(adapter);

	ctrl = ATL2_READ_REG(&adapter->hw, REG_MAC_CTRL);
	__atl2_vlan_mode(features, &ctrl);
	ATL2_WRITE_REG(&adapter->hw, REG_MAC_CTRL, ctrl);

	atl2_irq_enable(adapter);
पूर्ण

अटल व्योम atl2_restore_vlan(काष्ठा atl2_adapter *adapter)
अणु
	atl2_vlan_mode(adapter->netdev, adapter->netdev->features);
पूर्ण

अटल netdev_features_t atl2_fix_features(काष्ठा net_device *netdev,
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

अटल पूर्णांक atl2_set_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	netdev_features_t changed = netdev->features ^ features;

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX)
		atl2_vlan_mode(netdev, features);

	वापस 0;
पूर्ण

अटल व्योम atl2_पूर्णांकr_rx(काष्ठा atl2_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा rx_desc *rxd;
	काष्ठा sk_buff *skb;

	करो अणु
		rxd = adapter->rxd_ring+adapter->rxd_ग_लिखो_ptr;
		अगर (!rxd->status.update)
			अवरोध; /* end of tx */

		/* clear this flag at once */
		rxd->status.update = 0;

		अगर (rxd->status.ok && rxd->status.pkt_size >= 60) अणु
			पूर्णांक rx_size = (पूर्णांक)(rxd->status.pkt_size - 4);
			/* alloc new buffer */
			skb = netdev_alloc_skb_ip_align(netdev, rx_size);
			अगर (शून्य == skb) अणु
				/*
				 * Check that some rx space is मुक्त. If not,
				 * मुक्त one and mark stats->rx_dropped++.
				 */
				netdev->stats.rx_dropped++;
				अवरोध;
			पूर्ण
			स_नकल(skb->data, rxd->packet, rx_size);
			skb_put(skb, rx_size);
			skb->protocol = eth_type_trans(skb, netdev);
			अगर (rxd->status.vlan) अणु
				u16 vlan_tag = (rxd->status.vtag>>4) |
					((rxd->status.vtag&7) << 13) |
					((rxd->status.vtag&8) << 9);

				__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tag);
			पूर्ण
			netअगर_rx(skb);
			netdev->stats.rx_bytes += rx_size;
			netdev->stats.rx_packets++;
		पूर्ण अन्यथा अणु
			netdev->stats.rx_errors++;

			अगर (rxd->status.ok && rxd->status.pkt_size <= 60)
				netdev->stats.rx_length_errors++;
			अगर (rxd->status.mcast)
				netdev->stats.multicast++;
			अगर (rxd->status.crc)
				netdev->stats.rx_crc_errors++;
			अगर (rxd->status.align)
				netdev->stats.rx_frame_errors++;
		पूर्ण

		/* advance ग_लिखो ptr */
		अगर (++adapter->rxd_ग_लिखो_ptr == adapter->rxd_ring_size)
			adapter->rxd_ग_लिखो_ptr = 0;
	पूर्ण जबतक (1);

	/* update mailbox? */
	adapter->rxd_पढ़ो_ptr = adapter->rxd_ग_लिखो_ptr;
	ATL2_WRITE_REGW(&adapter->hw, REG_MB_RXD_RD_IDX, adapter->rxd_पढ़ो_ptr);
पूर्ण

अटल व्योम atl2_पूर्णांकr_tx(काष्ठा atl2_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	u32 txd_पढ़ो_ptr;
	u32 txs_ग_लिखो_ptr;
	काष्ठा tx_pkt_status *txs;
	काष्ठा tx_pkt_header *txph;
	पूर्णांक मुक्त_hole = 0;

	करो अणु
		txs_ग_लिखो_ptr = (u32) atomic_पढ़ो(&adapter->txs_ग_लिखो_ptr);
		txs = adapter->txs_ring + txs_ग_लिखो_ptr;
		अगर (!txs->update)
			अवरोध; /* tx stop here */

		मुक्त_hole = 1;
		txs->update = 0;

		अगर (++txs_ग_लिखो_ptr == adapter->txs_ring_size)
			txs_ग_लिखो_ptr = 0;
		atomic_set(&adapter->txs_ग_लिखो_ptr, (पूर्णांक)txs_ग_लिखो_ptr);

		txd_पढ़ो_ptr = (u32) atomic_पढ़ो(&adapter->txd_पढ़ो_ptr);
		txph = (काष्ठा tx_pkt_header *)
			(((u8 *)adapter->txd_ring) + txd_पढ़ो_ptr);

		अगर (txph->pkt_size != txs->pkt_size) अणु
			काष्ठा tx_pkt_status *old_txs = txs;
			prपूर्णांकk(KERN_WARNING
				"%s: txs packet size not consistent with txd"
				" txd_:0x%08x, txs_:0x%08x!\n",
				adapter->netdev->name,
				*(u32 *)txph, *(u32 *)txs);
			prपूर्णांकk(KERN_WARNING
				"txd read ptr: 0x%x\n",
				txd_पढ़ो_ptr);
			txs = adapter->txs_ring + txs_ग_लिखो_ptr;
			prपूर्णांकk(KERN_WARNING
				"txs-behind:0x%08x\n",
				*(u32 *)txs);
			अगर (txs_ग_लिखो_ptr < 2) अणु
				txs = adapter->txs_ring +
					(adapter->txs_ring_size +
					txs_ग_लिखो_ptr - 2);
			पूर्ण अन्यथा अणु
				txs = adapter->txs_ring + (txs_ग_लिखो_ptr - 2);
			पूर्ण
			prपूर्णांकk(KERN_WARNING
				"txs-before:0x%08x\n",
				*(u32 *)txs);
			txs = old_txs;
		पूर्ण

		 /* 4क्रम TPH */
		txd_पढ़ो_ptr += (((u32)(txph->pkt_size) + 7) & ~3);
		अगर (txd_पढ़ो_ptr >= adapter->txd_ring_size)
			txd_पढ़ो_ptr -= adapter->txd_ring_size;

		atomic_set(&adapter->txd_पढ़ो_ptr, (पूर्णांक)txd_पढ़ो_ptr);

		/* tx statistics: */
		अगर (txs->ok) अणु
			netdev->stats.tx_bytes += txs->pkt_size;
			netdev->stats.tx_packets++;
		पूर्ण
		अन्यथा
			netdev->stats.tx_errors++;

		अगर (txs->defer)
			netdev->stats.collisions++;
		अगर (txs->पात_col)
			netdev->stats.tx_पातed_errors++;
		अगर (txs->late_col)
			netdev->stats.tx_winकरोw_errors++;
		अगर (txs->underrun)
			netdev->stats.tx_fअगरo_errors++;
	पूर्ण जबतक (1);

	अगर (मुक्त_hole) अणु
		अगर (netअगर_queue_stopped(adapter->netdev) &&
			netअगर_carrier_ok(adapter->netdev))
			netअगर_wake_queue(adapter->netdev);
	पूर्ण
पूर्ण

अटल व्योम atl2_check_क्रम_link(काष्ठा atl2_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	u16 phy_data = 0;

	spin_lock(&adapter->stats_lock);
	atl2_पढ़ो_phy_reg(&adapter->hw, MII_BMSR, &phy_data);
	atl2_पढ़ो_phy_reg(&adapter->hw, MII_BMSR, &phy_data);
	spin_unlock(&adapter->stats_lock);

	/* notअगरy upper layer link करोwn ASAP */
	अगर (!(phy_data & BMSR_LSTATUS)) अणु /* Link Down */
		अगर (netअगर_carrier_ok(netdev)) अणु /* old link state: Up */
		prपूर्णांकk(KERN_INFO "%s: %s NIC Link is Down\n",
			atl2_driver_name, netdev->name);
		adapter->link_speed = SPEED_0;
		netअगर_carrier_off(netdev);
		netअगर_stop_queue(netdev);
		पूर्ण
	पूर्ण
	schedule_work(&adapter->link_chg_task);
पूर्ण

अटल अंतरभूत व्योम atl2_clear_phy_पूर्णांक(काष्ठा atl2_adapter *adapter)
अणु
	u16 phy_data;
	spin_lock(&adapter->stats_lock);
	atl2_पढ़ो_phy_reg(&adapter->hw, 19, &phy_data);
	spin_unlock(&adapter->stats_lock);
पूर्ण

/**
 * atl2_पूर्णांकr - Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 */
अटल irqवापस_t atl2_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(data);
	काष्ठा atl2_hw *hw = &adapter->hw;
	u32 status;

	status = ATL2_READ_REG(hw, REG_ISR);
	अगर (0 == status)
		वापस IRQ_NONE;

	/* link event */
	अगर (status & ISR_PHY)
		atl2_clear_phy_पूर्णांक(adapter);

	/* clear ISR status, and Enable CMB DMA/Disable Interrupt */
	ATL2_WRITE_REG(hw, REG_ISR, status | ISR_DIS_INT);

	/* check अगर PCIE PHY Link करोwn */
	अगर (status & ISR_PHY_LINKDOWN) अणु
		अगर (netअगर_running(adapter->netdev)) अणु /* reset MAC */
			ATL2_WRITE_REG(hw, REG_ISR, 0);
			ATL2_WRITE_REG(hw, REG_IMR, 0);
			ATL2_WRITE_FLUSH(hw);
			schedule_work(&adapter->reset_task);
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण

	/* check अगर DMA पढ़ो/ग_लिखो error? */
	अगर (status & (ISR_DMAR_TO_RST | ISR_DMAW_TO_RST)) अणु
		ATL2_WRITE_REG(hw, REG_ISR, 0);
		ATL2_WRITE_REG(hw, REG_IMR, 0);
		ATL2_WRITE_FLUSH(hw);
		schedule_work(&adapter->reset_task);
		वापस IRQ_HANDLED;
	पूर्ण

	/* link event */
	अगर (status & (ISR_PHY | ISR_MANUAL)) अणु
		adapter->netdev->stats.tx_carrier_errors++;
		atl2_check_क्रम_link(adapter);
	पूर्ण

	/* transmit event */
	अगर (status & ISR_TX_EVENT)
		atl2_पूर्णांकr_tx(adapter);

	/* rx exception */
	अगर (status & ISR_RX_EVENT)
		atl2_पूर्णांकr_rx(adapter);

	/* re-enable Interrupt */
	ATL2_WRITE_REG(&adapter->hw, REG_ISR, 0);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक atl2_request_irq(काष्ठा atl2_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक flags, err = 0;

	flags = IRQF_SHARED;
	adapter->have_msi = true;
	err = pci_enable_msi(adapter->pdev);
	अगर (err)
		adapter->have_msi = false;

	अगर (adapter->have_msi)
		flags &= ~IRQF_SHARED;

	वापस request_irq(adapter->pdev->irq, atl2_पूर्णांकr, flags, netdev->name,
		netdev);
पूर्ण

/**
 * atl2_मुक्त_ring_resources - Free Tx / RX descriptor Resources
 * @adapter: board निजी काष्ठाure
 *
 * Free all transmit software resources
 */
अटल व्योम atl2_मुक्त_ring_resources(काष्ठा atl2_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	dma_मुक्त_coherent(&pdev->dev, adapter->ring_size,
			  adapter->ring_vir_addr, adapter->ring_dma);
पूर्ण

/**
 * atl2_खोलो - Called when a network पूर्णांकerface is made active
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
अटल पूर्णांक atl2_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err;
	u32 val;

	/* disallow खोलो during test */
	अगर (test_bit(__ATL2_TESTING, &adapter->flags))
		वापस -EBUSY;

	/* allocate transmit descriptors */
	err = atl2_setup_ring_resources(adapter);
	अगर (err)
		वापस err;

	err = atl2_init_hw(&adapter->hw);
	अगर (err) अणु
		err = -EIO;
		जाओ err_init_hw;
	पूर्ण

	/* hardware has been reset, we need to reload some things */
	atl2_set_multi(netdev);
	init_ring_ptrs(adapter);

	atl2_restore_vlan(adapter);

	अगर (atl2_configure(adapter)) अणु
		err = -EIO;
		जाओ err_config;
	पूर्ण

	err = atl2_request_irq(adapter);
	अगर (err)
		जाओ err_req_irq;

	clear_bit(__ATL2_DOWN, &adapter->flags);

	mod_समयr(&adapter->watchकरोg_समयr, round_jअगरfies(jअगरfies + 4*HZ));

	val = ATL2_READ_REG(&adapter->hw, REG_MASTER_CTRL);
	ATL2_WRITE_REG(&adapter->hw, REG_MASTER_CTRL,
		val | MASTER_CTRL_MANUAL_INT);

	atl2_irq_enable(adapter);

	वापस 0;

err_init_hw:
err_req_irq:
err_config:
	atl2_मुक्त_ring_resources(adapter);
	atl2_reset_hw(&adapter->hw);

	वापस err;
पूर्ण

अटल व्योम atl2_करोwn(काष्ठा atl2_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	/* संकेत that we're करोwn so the पूर्णांकerrupt handler करोes not
	 * reschedule our watchकरोg समयr */
	set_bit(__ATL2_DOWN, &adapter->flags);

	netअगर_tx_disable(netdev);

	/* reset MAC to disable all RX/TX */
	atl2_reset_hw(&adapter->hw);
	msleep(1);

	atl2_irq_disable(adapter);

	del_समयr_sync(&adapter->watchकरोg_समयr);
	del_समयr_sync(&adapter->phy_config_समयr);
	clear_bit(0, &adapter->cfg_phy);

	netअगर_carrier_off(netdev);
	adapter->link_speed = SPEED_0;
	adapter->link_duplex = -1;
पूर्ण

अटल व्योम atl2_मुक्त_irq(काष्ठा atl2_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	मुक्त_irq(adapter->pdev->irq, netdev);

#अगर_घोषित CONFIG_PCI_MSI
	अगर (adapter->have_msi)
		pci_disable_msi(adapter->pdev);
#पूर्ण_अगर
पूर्ण

/**
 * atl2_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are मुक्तd.
 */
अटल पूर्णांक atl2_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);

	WARN_ON(test_bit(__ATL2_RESETTING, &adapter->flags));

	atl2_करोwn(adapter);
	atl2_मुक्त_irq(adapter);
	atl2_मुक्त_ring_resources(adapter);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक TxsFreeUnit(काष्ठा atl2_adapter *adapter)
अणु
	u32 txs_ग_लिखो_ptr = (u32) atomic_पढ़ो(&adapter->txs_ग_लिखो_ptr);

	वापस (adapter->txs_next_clear >= txs_ग_लिखो_ptr) ?
		(पूर्णांक) (adapter->txs_ring_size - adapter->txs_next_clear +
		txs_ग_लिखो_ptr - 1) :
		(पूर्णांक) (txs_ग_लिखो_ptr - adapter->txs_next_clear - 1);
पूर्ण

अटल अंतरभूत पूर्णांक TxdFreeBytes(काष्ठा atl2_adapter *adapter)
अणु
	u32 txd_पढ़ो_ptr = (u32)atomic_पढ़ो(&adapter->txd_पढ़ो_ptr);

	वापस (adapter->txd_ग_लिखो_ptr >= txd_पढ़ो_ptr) ?
		(पूर्णांक) (adapter->txd_ring_size - adapter->txd_ग_लिखो_ptr +
		txd_पढ़ो_ptr - 1) :
		(पूर्णांक) (txd_पढ़ो_ptr - adapter->txd_ग_लिखो_ptr - 1);
पूर्ण

अटल netdev_tx_t atl2_xmit_frame(काष्ठा sk_buff *skb,
					 काष्ठा net_device *netdev)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	काष्ठा tx_pkt_header *txph;
	u32 offset, copy_len;
	पूर्णांक txs_unused;
	पूर्णांक txbuf_unused;

	अगर (test_bit(__ATL2_DOWN, &adapter->flags)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (unlikely(skb->len <= 0)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	txs_unused = TxsFreeUnit(adapter);
	txbuf_unused = TxdFreeBytes(adapter);

	अगर (skb->len + माप(काष्ठा tx_pkt_header) + 4  > txbuf_unused ||
		txs_unused < 1) अणु
		/* not enough resources */
		netअगर_stop_queue(netdev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	offset = adapter->txd_ग_लिखो_ptr;

	txph = (काष्ठा tx_pkt_header *) (((u8 *)adapter->txd_ring) + offset);

	*(u32 *)txph = 0;
	txph->pkt_size = skb->len;

	offset += 4;
	अगर (offset >= adapter->txd_ring_size)
		offset -= adapter->txd_ring_size;
	copy_len = adapter->txd_ring_size - offset;
	अगर (copy_len >= skb->len) अणु
		स_नकल(((u8 *)adapter->txd_ring) + offset, skb->data, skb->len);
		offset += ((u32)(skb->len + 3) & ~3);
	पूर्ण अन्यथा अणु
		स_नकल(((u8 *)adapter->txd_ring)+offset, skb->data, copy_len);
		स_नकल((u8 *)adapter->txd_ring, skb->data+copy_len,
			skb->len-copy_len);
		offset = ((u32)(skb->len-copy_len + 3) & ~3);
	पूर्ण
#अगर_घोषित NETIF_F_HW_VLAN_CTAG_TX
	अगर (skb_vlan_tag_present(skb)) अणु
		u16 vlan_tag = skb_vlan_tag_get(skb);
		vlan_tag = (vlan_tag << 4) |
			(vlan_tag >> 13) |
			((vlan_tag >> 9) & 0x8);
		txph->ins_vlan = 1;
		txph->vlan = vlan_tag;
	पूर्ण
#पूर्ण_अगर
	अगर (offset >= adapter->txd_ring_size)
		offset -= adapter->txd_ring_size;
	adapter->txd_ग_लिखो_ptr = offset;

	/* clear txs beक्रमe send */
	adapter->txs_ring[adapter->txs_next_clear].update = 0;
	अगर (++adapter->txs_next_clear == adapter->txs_ring_size)
		adapter->txs_next_clear = 0;

	ATL2_WRITE_REGW(&adapter->hw, REG_MB_TXD_WR_IDX,
		(adapter->txd_ग_लिखो_ptr >> 2));

	dev_consume_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/**
 * atl2_change_mtu - Change the Maximum Transfer Unit
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक atl2_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl2_hw *hw = &adapter->hw;

	/* set MTU */
	netdev->mtu = new_mtu;
	hw->max_frame_size = new_mtu;
	ATL2_WRITE_REG(hw, REG_MTU, new_mtu + ETH_HLEN +
		       VLAN_HLEN + ETH_FCS_LEN);

	वापस 0;
पूर्ण

/**
 * atl2_set_mac - Change the Ethernet Address of the NIC
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @p: poपूर्णांकer to an address काष्ठाure
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक atl2_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (netअगर_running(netdev))
		वापस -EBUSY;

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	स_नकल(adapter->hw.mac_addr, addr->sa_data, netdev->addr_len);

	atl2_set_mac_addr(&adapter->hw);

	वापस 0;
पूर्ण

अटल पूर्णांक atl2_mii_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);
	अचिन्हित दीर्घ flags;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		data->phy_id = 0;
		अवरोध;
	हाल SIOCGMIIREG:
		spin_lock_irqsave(&adapter->stats_lock, flags);
		अगर (atl2_पढ़ो_phy_reg(&adapter->hw,
			data->reg_num & 0x1F, &data->val_out)) अणु
			spin_unlock_irqrestore(&adapter->stats_lock, flags);
			वापस -EIO;
		पूर्ण
		spin_unlock_irqrestore(&adapter->stats_lock, flags);
		अवरोध;
	हाल SIOCSMIIREG:
		अगर (data->reg_num & ~(0x1F))
			वापस -EFAULT;
		spin_lock_irqsave(&adapter->stats_lock, flags);
		अगर (atl2_ग_लिखो_phy_reg(&adapter->hw, data->reg_num,
			data->val_in)) अणु
			spin_unlock_irqrestore(&adapter->stats_lock, flags);
			वापस -EIO;
		पूर्ण
		spin_unlock_irqrestore(&adapter->stats_lock, flags);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक atl2_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
		वापस atl2_mii_ioctl(netdev, अगरr, cmd);
#अगर_घोषित ETHTOOL_OPS_COMPAT
	हाल SIOCETHTOOL:
		वापस ethtool_ioctl(अगरr);
#पूर्ण_अगर
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * atl2_tx_समयout - Respond to a Tx Hang
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @txqueue: index of the hanging transmit queue
 */
अटल व्योम atl2_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);

	/* Do the reset outside of पूर्णांकerrupt context */
	schedule_work(&adapter->reset_task);
पूर्ण

/**
 * atl2_watchकरोg - Timer Call-back
 * @t: समयr list containing a poपूर्णांकer to netdev cast पूर्णांकo an अचिन्हित दीर्घ
 */
अटल व्योम atl2_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा atl2_adapter *adapter = from_समयr(adapter, t, watchकरोg_समयr);

	अगर (!test_bit(__ATL2_DOWN, &adapter->flags)) अणु
		u32 drop_rxd, drop_rxs;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&adapter->stats_lock, flags);
		drop_rxd = ATL2_READ_REG(&adapter->hw, REG_STS_RXD_OV);
		drop_rxs = ATL2_READ_REG(&adapter->hw, REG_STS_RXS_OV);
		spin_unlock_irqrestore(&adapter->stats_lock, flags);

		adapter->netdev->stats.rx_over_errors += drop_rxd + drop_rxs;

		/* Reset the समयr */
		mod_समयr(&adapter->watchकरोg_समयr,
			  round_jअगरfies(jअगरfies + 4 * HZ));
	पूर्ण
पूर्ण

/**
 * atl2_phy_config - Timer Call-back
 * @t: समयr list containing a poपूर्णांकer to netdev cast पूर्णांकo an अचिन्हित दीर्घ
 */
अटल व्योम atl2_phy_config(काष्ठा समयr_list *t)
अणु
	काष्ठा atl2_adapter *adapter = from_समयr(adapter, t,
						  phy_config_समयr);
	काष्ठा atl2_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adapter->stats_lock, flags);
	atl2_ग_लिखो_phy_reg(hw, MII_ADVERTISE, hw->mii_स्वतःneg_adv_reg);
	atl2_ग_लिखो_phy_reg(hw, MII_BMCR, MII_CR_RESET | MII_CR_AUTO_NEG_EN |
		MII_CR_RESTART_AUTO_NEG);
	spin_unlock_irqrestore(&adapter->stats_lock, flags);
	clear_bit(0, &adapter->cfg_phy);
पूर्ण

अटल पूर्णांक atl2_up(काष्ठा atl2_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err = 0;
	u32 val;

	/* hardware has been reset, we need to reload some things */

	err = atl2_init_hw(&adapter->hw);
	अगर (err) अणु
		err = -EIO;
		वापस err;
	पूर्ण

	atl2_set_multi(netdev);
	init_ring_ptrs(adapter);

	atl2_restore_vlan(adapter);

	अगर (atl2_configure(adapter)) अणु
		err = -EIO;
		जाओ err_up;
	पूर्ण

	clear_bit(__ATL2_DOWN, &adapter->flags);

	val = ATL2_READ_REG(&adapter->hw, REG_MASTER_CTRL);
	ATL2_WRITE_REG(&adapter->hw, REG_MASTER_CTRL, val |
		MASTER_CTRL_MANUAL_INT);

	atl2_irq_enable(adapter);

err_up:
	वापस err;
पूर्ण

अटल व्योम atl2_reinit_locked(काष्ठा atl2_adapter *adapter)
अणु
	जबतक (test_and_set_bit(__ATL2_RESETTING, &adapter->flags))
		msleep(1);
	atl2_करोwn(adapter);
	atl2_up(adapter);
	clear_bit(__ATL2_RESETTING, &adapter->flags);
पूर्ण

अटल व्योम atl2_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा atl2_adapter *adapter;
	adapter = container_of(work, काष्ठा atl2_adapter, reset_task);

	atl2_reinit_locked(adapter);
पूर्ण

अटल व्योम atl2_setup_mac_ctrl(काष्ठा atl2_adapter *adapter)
अणु
	u32 value;
	काष्ठा atl2_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;

	/* Config MAC CTRL Register */
	value = MAC_CTRL_TX_EN | MAC_CTRL_RX_EN | MAC_CTRL_MACLP_CLK_PHY;

	/* duplex */
	अगर (FULL_DUPLEX == adapter->link_duplex)
		value |= MAC_CTRL_DUPLX;

	/* flow control */
	value |= (MAC_CTRL_TX_FLOW | MAC_CTRL_RX_FLOW);

	/* PAD & CRC */
	value |= (MAC_CTRL_ADD_CRC | MAC_CTRL_PAD);

	/* preamble length */
	value |= (((u32)adapter->hw.preamble_len & MAC_CTRL_PRMLEN_MASK) <<
		MAC_CTRL_PRMLEN_SHIFT);

	/* vlan */
	__atl2_vlan_mode(netdev->features, &value);

	/* filter mode */
	value |= MAC_CTRL_BC_EN;
	अगर (netdev->flags & IFF_PROMISC)
		value |= MAC_CTRL_PROMIS_EN;
	अन्यथा अगर (netdev->flags & IFF_ALLMULTI)
		value |= MAC_CTRL_MC_ALL_EN;

	/* half retry buffer */
	value |= (((u32)(adapter->hw.retry_buf &
		MAC_CTRL_HALF_LEFT_BUF_MASK)) << MAC_CTRL_HALF_LEFT_BUF_SHIFT);

	ATL2_WRITE_REG(hw, REG_MAC_CTRL, value);
पूर्ण

अटल पूर्णांक atl2_check_link(काष्ठा atl2_adapter *adapter)
अणु
	काष्ठा atl2_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक ret_val;
	u16 speed, duplex, phy_data;
	पूर्णांक reconfig = 0;

	/* MII_BMSR must पढ़ो twise */
	atl2_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
	atl2_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
	अगर (!(phy_data&BMSR_LSTATUS)) अणु /* link करोwn */
		अगर (netअगर_carrier_ok(netdev)) अणु /* old link state: Up */
			u32 value;
			/* disable rx */
			value = ATL2_READ_REG(hw, REG_MAC_CTRL);
			value &= ~MAC_CTRL_RX_EN;
			ATL2_WRITE_REG(hw, REG_MAC_CTRL, value);
			adapter->link_speed = SPEED_0;
			netअगर_carrier_off(netdev);
			netअगर_stop_queue(netdev);
		पूर्ण
		वापस 0;
	पूर्ण

	/* Link Up */
	ret_val = atl2_get_speed_and_duplex(hw, &speed, &duplex);
	अगर (ret_val)
		वापस ret_val;
	चयन (hw->MediaType) अणु
	हाल MEDIA_TYPE_100M_FULL:
		अगर (speed  != SPEED_100 || duplex != FULL_DUPLEX)
			reconfig = 1;
		अवरोध;
	हाल MEDIA_TYPE_100M_HALF:
		अगर (speed  != SPEED_100 || duplex != HALF_DUPLEX)
			reconfig = 1;
		अवरोध;
	हाल MEDIA_TYPE_10M_FULL:
		अगर (speed != SPEED_10 || duplex != FULL_DUPLEX)
			reconfig = 1;
		अवरोध;
	हाल MEDIA_TYPE_10M_HALF:
		अगर (speed  != SPEED_10 || duplex != HALF_DUPLEX)
			reconfig = 1;
		अवरोध;
	पूर्ण
	/* link result is our setting */
	अगर (reconfig == 0) अणु
		अगर (adapter->link_speed != speed ||
			adapter->link_duplex != duplex) अणु
			adapter->link_speed = speed;
			adapter->link_duplex = duplex;
			atl2_setup_mac_ctrl(adapter);
			prपूर्णांकk(KERN_INFO "%s: %s NIC Link is Up<%d Mbps %s>\n",
				atl2_driver_name, netdev->name,
				adapter->link_speed,
				adapter->link_duplex == FULL_DUPLEX ?
					"Full Duplex" : "Half Duplex");
		पूर्ण

		अगर (!netअगर_carrier_ok(netdev)) अणु /* Link करोwn -> Up */
			netअगर_carrier_on(netdev);
			netअगर_wake_queue(netdev);
		पूर्ण
		वापस 0;
	पूर्ण

	/* change original link status */
	अगर (netअगर_carrier_ok(netdev)) अणु
		u32 value;
		/* disable rx */
		value = ATL2_READ_REG(hw, REG_MAC_CTRL);
		value &= ~MAC_CTRL_RX_EN;
		ATL2_WRITE_REG(hw, REG_MAC_CTRL, value);

		adapter->link_speed = SPEED_0;
		netअगर_carrier_off(netdev);
		netअगर_stop_queue(netdev);
	पूर्ण

	/* स्वतः-neg, insert समयr to re-config phy
	 * (अगर पूर्णांकerval smaller than 5 seconds, something strange) */
	अगर (!test_bit(__ATL2_DOWN, &adapter->flags)) अणु
		अगर (!test_and_set_bit(0, &adapter->cfg_phy))
			mod_समयr(&adapter->phy_config_समयr,
				  round_jअगरfies(jअगरfies + 5 * HZ));
	पूर्ण

	वापस 0;
पूर्ण

/**
 * atl2_link_chg_task - deal with link change event Out of पूर्णांकerrupt context
 * @work: poपूर्णांकer to work काष्ठा with निजी info
 */
अटल व्योम atl2_link_chg_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा atl2_adapter *adapter;
	अचिन्हित दीर्घ flags;

	adapter = container_of(work, काष्ठा atl2_adapter, link_chg_task);

	spin_lock_irqsave(&adapter->stats_lock, flags);
	atl2_check_link(adapter);
	spin_unlock_irqrestore(&adapter->stats_lock, flags);
पूर्ण

अटल व्योम atl2_setup_pcicmd(काष्ठा pci_dev *pdev)
अणु
	u16 cmd;

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);

	अगर (cmd & PCI_COMMAND_INTX_DISABLE)
		cmd &= ~PCI_COMMAND_INTX_DISABLE;
	अगर (cmd & PCI_COMMAND_IO)
		cmd &= ~PCI_COMMAND_IO;
	अगर (0 == (cmd & PCI_COMMAND_MEMORY))
		cmd |= PCI_COMMAND_MEMORY;
	अगर (0 == (cmd & PCI_COMMAND_MASTER))
		cmd |= PCI_COMMAND_MASTER;
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, cmd);

	/*
	 * some motherboards BIOS(PXE/EFI) driver may set PME
	 * जबतक they transfer control to OS (Winकरोws/Linux)
	 * so we should clear this bit beक्रमe NIC work normally
	 */
	pci_ग_लिखो_config_dword(pdev, REG_PM_CTRLSTAT, 0);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम atl2_poll_controller(काष्ठा net_device *netdev)
अणु
	disable_irq(netdev->irq);
	atl2_पूर्णांकr(netdev->irq, netdev);
	enable_irq(netdev->irq);
पूर्ण
#पूर्ण_अगर


अटल स्थिर काष्ठा net_device_ops atl2_netdev_ops = अणु
	.nकरो_खोलो		= atl2_खोलो,
	.nकरो_stop		= atl2_बंद,
	.nकरो_start_xmit		= atl2_xmit_frame,
	.nकरो_set_rx_mode	= atl2_set_multi,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= atl2_set_mac,
	.nकरो_change_mtu		= atl2_change_mtu,
	.nकरो_fix_features	= atl2_fix_features,
	.nकरो_set_features	= atl2_set_features,
	.nकरो_करो_ioctl		= atl2_ioctl,
	.nकरो_tx_समयout		= atl2_tx_समयout,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= atl2_poll_controller,
#पूर्ण_अगर
पूर्ण;

/**
 * atl2_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in atl2_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * atl2_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 */
अटल पूर्णांक atl2_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा atl2_adapter *adapter;
	अटल पूर्णांक cards_found = 0;
	अचिन्हित दीर्घ mmio_start;
	पूर्णांक mmio_len;
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	/*
	 * atl2 is a shared-high-32-bit device, so we're stuck with 32-bit DMA
	 * until the kernel has the proper infraकाष्ठाure to support 64-bit DMA
	 * on these devices.
	 */
	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32)) &&
	    dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		prपूर्णांकk(KERN_ERR "atl2: No usable DMA configuration, aborting\n");
		err = -EIO;
		जाओ err_dma;
	पूर्ण

	/* Mark all PCI regions associated with PCI device
	 * pdev as being reserved by owner atl2_driver_name */
	err = pci_request_regions(pdev, atl2_driver_name);
	अगर (err)
		जाओ err_pci_reg;

	/* Enables bus-mastering on the device and calls
	 * pcibios_set_master to करो the needed arch specअगरic settings */
	pci_set_master(pdev);

	netdev = alloc_etherdev(माप(काष्ठा atl2_adapter));
	अगर (!netdev) अणु
		err = -ENOMEM;
		जाओ err_alloc_etherdev;
	पूर्ण

	SET_NETDEV_DEV(netdev, &pdev->dev);

	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	adapter->hw.back = adapter;

	mmio_start = pci_resource_start(pdev, 0x0);
	mmio_len = pci_resource_len(pdev, 0x0);

	adapter->hw.mem_rang = (u32)mmio_len;
	adapter->hw.hw_addr = ioremap(mmio_start, mmio_len);
	अगर (!adapter->hw.hw_addr) अणु
		err = -EIO;
		जाओ err_ioremap;
	पूर्ण

	atl2_setup_pcicmd(pdev);

	netdev->netdev_ops = &atl2_netdev_ops;
	netdev->ethtool_ops = &atl2_ethtool_ops;
	netdev->watchकरोg_समयo = 5 * HZ;
	netdev->min_mtu = 40;
	netdev->max_mtu = ETH_DATA_LEN + VLAN_HLEN;
	म_नकलन(netdev->name, pci_name(pdev), माप(netdev->name) - 1);

	netdev->mem_start = mmio_start;
	netdev->mem_end = mmio_start + mmio_len;
	adapter->bd_number = cards_found;
	adapter->pci_using_64 = false;

	/* setup the निजी काष्ठाure */
	err = atl2_sw_init(adapter);
	अगर (err)
		जाओ err_sw_init;

	netdev->hw_features = NETIF_F_HW_VLAN_CTAG_RX;
	netdev->features |= (NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX);

	/* Init PHY as early as possible due to घातer saving issue  */
	atl2_phy_init(&adapter->hw);

	/* reset the controller to
	 * put the device in a known good starting state */

	अगर (atl2_reset_hw(&adapter->hw)) अणु
		err = -EIO;
		जाओ err_reset;
	पूर्ण

	/* copy the MAC address out of the EEPROM */
	atl2_पढ़ो_mac_addr(&adapter->hw);
	स_नकल(netdev->dev_addr, adapter->hw.mac_addr, netdev->addr_len);
	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		err = -EIO;
		जाओ err_eeprom;
	पूर्ण

	atl2_check_options(adapter);

	समयr_setup(&adapter->watchकरोg_समयr, atl2_watchकरोg, 0);

	समयr_setup(&adapter->phy_config_समयr, atl2_phy_config, 0);

	INIT_WORK(&adapter->reset_task, atl2_reset_task);
	INIT_WORK(&adapter->link_chg_task, atl2_link_chg_task);

	म_नकल(netdev->name, "eth%d"); /* ?? */
	err = रेजिस्टर_netdev(netdev);
	अगर (err)
		जाओ err_रेजिस्टर;

	/* assume we have no link क्रम now */
	netअगर_carrier_off(netdev);
	netअगर_stop_queue(netdev);

	cards_found++;

	वापस 0;

err_reset:
err_रेजिस्टर:
err_sw_init:
err_eeprom:
	iounmap(adapter->hw.hw_addr);
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
 * atl2_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * atl2_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.  The could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 */
/* FIXME: ग_लिखो the original MAC address back in हाल it was changed from a
 * BIOS-set value, as in atl1 -- CHS */
अटल व्योम atl2_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);

	/* flush_scheduled work may reschedule our watchकरोg task, so
	 * explicitly disable watchकरोg tasks from being rescheduled  */
	set_bit(__ATL2_DOWN, &adapter->flags);

	del_समयr_sync(&adapter->watchकरोg_समयr);
	del_समयr_sync(&adapter->phy_config_समयr);
	cancel_work_sync(&adapter->reset_task);
	cancel_work_sync(&adapter->link_chg_task);

	unरेजिस्टर_netdev(netdev);

	atl2_क्रमce_ps(&adapter->hw);

	iounmap(adapter->hw.hw_addr);
	pci_release_regions(pdev);

	मुक्त_netdev(netdev);

	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक atl2_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl2_hw *hw = &adapter->hw;
	u16 speed, duplex;
	u32 ctrl = 0;
	u32 wufc = adapter->wol;

#अगर_घोषित CONFIG_PM
	पूर्णांक retval = 0;
#पूर्ण_अगर

	netअगर_device_detach(netdev);

	अगर (netअगर_running(netdev)) अणु
		WARN_ON(test_bit(__ATL2_RESETTING, &adapter->flags));
		atl2_करोwn(adapter);
	पूर्ण

#अगर_घोषित CONFIG_PM
	retval = pci_save_state(pdev);
	अगर (retval)
		वापस retval;
#पूर्ण_अगर

	atl2_पढ़ो_phy_reg(hw, MII_BMSR, (u16 *)&ctrl);
	atl2_पढ़ो_phy_reg(hw, MII_BMSR, (u16 *)&ctrl);
	अगर (ctrl & BMSR_LSTATUS)
		wufc &= ~ATLX_WUFC_LNKC;

	अगर (0 != (ctrl & BMSR_LSTATUS) && 0 != wufc) अणु
		u32 ret_val;
		/* get current link speed & duplex */
		ret_val = atl2_get_speed_and_duplex(hw, &speed, &duplex);
		अगर (ret_val) अणु
			prपूर्णांकk(KERN_DEBUG
				"%s: get speed&duplex error while suspend\n",
				atl2_driver_name);
			जाओ wol_dis;
		पूर्ण

		ctrl = 0;

		/* turn on magic packet wol */
		अगर (wufc & ATLX_WUFC_MAG)
			ctrl |= (WOL_MAGIC_EN | WOL_MAGIC_PME_EN);

		/* ignore Link Chg event when Link is up */
		ATL2_WRITE_REG(hw, REG_WOL_CTRL, ctrl);

		/* Config MAC CTRL Register */
		ctrl = MAC_CTRL_RX_EN | MAC_CTRL_MACLP_CLK_PHY;
		अगर (FULL_DUPLEX == adapter->link_duplex)
			ctrl |= MAC_CTRL_DUPLX;
		ctrl |= (MAC_CTRL_ADD_CRC | MAC_CTRL_PAD);
		ctrl |= (((u32)adapter->hw.preamble_len &
			MAC_CTRL_PRMLEN_MASK) << MAC_CTRL_PRMLEN_SHIFT);
		ctrl |= (((u32)(adapter->hw.retry_buf &
			MAC_CTRL_HALF_LEFT_BUF_MASK)) <<
			MAC_CTRL_HALF_LEFT_BUF_SHIFT);
		अगर (wufc & ATLX_WUFC_MAG) अणु
			/* magic packet maybe Broadcast&multicast&Unicast */
			ctrl |= MAC_CTRL_BC_EN;
		पूर्ण

		ATL2_WRITE_REG(hw, REG_MAC_CTRL, ctrl);

		/* pcie patch */
		ctrl = ATL2_READ_REG(hw, REG_PCIE_PHYMISC);
		ctrl |= PCIE_PHYMISC_FORCE_RCV_DET;
		ATL2_WRITE_REG(hw, REG_PCIE_PHYMISC, ctrl);
		ctrl = ATL2_READ_REG(hw, REG_PCIE_DLL_TX_CTRL1);
		ctrl |= PCIE_DLL_TX_CTRL1_SEL_NOR_CLK;
		ATL2_WRITE_REG(hw, REG_PCIE_DLL_TX_CTRL1, ctrl);

		pci_enable_wake(pdev, pci_choose_state(pdev, state), 1);
		जाओ suspend_निकास;
	पूर्ण

	अगर (0 == (ctrl&BMSR_LSTATUS) && 0 != (wufc&ATLX_WUFC_LNKC)) अणु
		/* link is करोwn, so only LINK CHG WOL event enable */
		ctrl |= (WOL_LINK_CHG_EN | WOL_LINK_CHG_PME_EN);
		ATL2_WRITE_REG(hw, REG_WOL_CTRL, ctrl);
		ATL2_WRITE_REG(hw, REG_MAC_CTRL, 0);

		/* pcie patch */
		ctrl = ATL2_READ_REG(hw, REG_PCIE_PHYMISC);
		ctrl |= PCIE_PHYMISC_FORCE_RCV_DET;
		ATL2_WRITE_REG(hw, REG_PCIE_PHYMISC, ctrl);
		ctrl = ATL2_READ_REG(hw, REG_PCIE_DLL_TX_CTRL1);
		ctrl |= PCIE_DLL_TX_CTRL1_SEL_NOR_CLK;
		ATL2_WRITE_REG(hw, REG_PCIE_DLL_TX_CTRL1, ctrl);

		hw->phy_configured = false; /* re-init PHY when resume */

		pci_enable_wake(pdev, pci_choose_state(pdev, state), 1);

		जाओ suspend_निकास;
	पूर्ण

wol_dis:
	/* WOL disabled */
	ATL2_WRITE_REG(hw, REG_WOL_CTRL, 0);

	/* pcie patch */
	ctrl = ATL2_READ_REG(hw, REG_PCIE_PHYMISC);
	ctrl |= PCIE_PHYMISC_FORCE_RCV_DET;
	ATL2_WRITE_REG(hw, REG_PCIE_PHYMISC, ctrl);
	ctrl = ATL2_READ_REG(hw, REG_PCIE_DLL_TX_CTRL1);
	ctrl |= PCIE_DLL_TX_CTRL1_SEL_NOR_CLK;
	ATL2_WRITE_REG(hw, REG_PCIE_DLL_TX_CTRL1, ctrl);

	atl2_क्रमce_ps(hw);
	hw->phy_configured = false; /* re-init PHY when resume */

	pci_enable_wake(pdev, pci_choose_state(pdev, state), 0);

suspend_निकास:
	अगर (netअगर_running(netdev))
		atl2_मुक्त_irq(adapter);

	pci_disable_device(pdev);

	pci_set_घातer_state(pdev, pci_choose_state(pdev, state));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक atl2_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	u32 err;

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);

	err = pci_enable_device(pdev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR
			"atl2: Cannot enable PCI device from suspend\n");
		वापस err;
	पूर्ण

	pci_set_master(pdev);

	ATL2_READ_REG(&adapter->hw, REG_WOL_CTRL); /* clear WOL status */

	pci_enable_wake(pdev, PCI_D3hot, 0);
	pci_enable_wake(pdev, PCI_D3cold, 0);

	ATL2_WRITE_REG(&adapter->hw, REG_WOL_CTRL, 0);

	अगर (netअगर_running(netdev)) अणु
		err = atl2_request_irq(adapter);
		अगर (err)
			वापस err;
	पूर्ण

	atl2_reset_hw(&adapter->hw);

	अगर (netअगर_running(netdev))
		atl2_up(adapter);

	netअगर_device_attach(netdev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम atl2_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	atl2_suspend(pdev, PMSG_SUSPEND);
पूर्ण

अटल काष्ठा pci_driver atl2_driver = अणु
	.name     = atl2_driver_name,
	.id_table = atl2_pci_tbl,
	.probe    = atl2_probe,
	.हटाओ   = atl2_हटाओ,
	/* Power Management Hooks */
	.suspend  = atl2_suspend,
#अगर_घोषित CONFIG_PM
	.resume   = atl2_resume,
#पूर्ण_अगर
	.shutकरोwn = atl2_shutकरोwn,
पूर्ण;

module_pci_driver(atl2_driver);

अटल व्योम atl2_पढ़ो_pci_cfg(काष्ठा atl2_hw *hw, u32 reg, u16 *value)
अणु
	काष्ठा atl2_adapter *adapter = hw->back;
	pci_पढ़ो_config_word(adapter->pdev, reg, value);
पूर्ण

अटल व्योम atl2_ग_लिखो_pci_cfg(काष्ठा atl2_hw *hw, u32 reg, u16 *value)
अणु
	काष्ठा atl2_adapter *adapter = hw->back;
	pci_ग_लिखो_config_word(adapter->pdev, reg, *value);
पूर्ण

अटल पूर्णांक atl2_get_link_ksettings(काष्ठा net_device *netdev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl2_hw *hw = &adapter->hw;
	u32 supported, advertising;

	supported = (SUPPORTED_10baseT_Half |
		SUPPORTED_10baseT_Full |
		SUPPORTED_100baseT_Half |
		SUPPORTED_100baseT_Full |
		SUPPORTED_Autoneg |
		SUPPORTED_TP);
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

अटल पूर्णांक atl2_set_link_ksettings(काष्ठा net_device *netdev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl2_hw *hw = &adapter->hw;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	जबतक (test_and_set_bit(__ATL2_RESETTING, &adapter->flags))
		msleep(1);

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
#घोषणा MY_ADV_MASK	(ADVERTISE_10_HALF | \
			 ADVERTISE_10_FULL | \
			 ADVERTISE_100_HALF| \
			 ADVERTISE_100_FULL)

		अगर ((advertising & MY_ADV_MASK) == MY_ADV_MASK) अणु
			hw->MediaType = MEDIA_TYPE_AUTO_SENSOR;
			hw->स्वतःneg_advertised =  MY_ADV_MASK;
		पूर्ण अन्यथा अगर ((advertising & MY_ADV_MASK) == ADVERTISE_100_FULL) अणु
			hw->MediaType = MEDIA_TYPE_100M_FULL;
			hw->स्वतःneg_advertised = ADVERTISE_100_FULL;
		पूर्ण अन्यथा अगर ((advertising & MY_ADV_MASK) == ADVERTISE_100_HALF) अणु
			hw->MediaType = MEDIA_TYPE_100M_HALF;
			hw->स्वतःneg_advertised = ADVERTISE_100_HALF;
		पूर्ण अन्यथा अगर ((advertising & MY_ADV_MASK) == ADVERTISE_10_FULL) अणु
			hw->MediaType = MEDIA_TYPE_10M_FULL;
			hw->स्वतःneg_advertised = ADVERTISE_10_FULL;
		पूर्ण  अन्यथा अगर ((advertising & MY_ADV_MASK) == ADVERTISE_10_HALF) अणु
			hw->MediaType = MEDIA_TYPE_10M_HALF;
			hw->स्वतःneg_advertised = ADVERTISE_10_HALF;
		पूर्ण अन्यथा अणु
			clear_bit(__ATL2_RESETTING, &adapter->flags);
			वापस -EINVAL;
		पूर्ण
		advertising = hw->स्वतःneg_advertised |
			ADVERTISED_TP | ADVERTISED_Autoneg;
	पूर्ण अन्यथा अणु
		clear_bit(__ATL2_RESETTING, &adapter->flags);
		वापस -EINVAL;
	पूर्ण

	/* reset the link */
	अगर (netअगर_running(adapter->netdev)) अणु
		atl2_करोwn(adapter);
		atl2_up(adapter);
	पूर्ण अन्यथा
		atl2_reset_hw(&adapter->hw);

	clear_bit(__ATL2_RESETTING, &adapter->flags);
	वापस 0;
पूर्ण

अटल u32 atl2_get_msglevel(काष्ठा net_device *netdev)
अणु
	वापस 0;
पूर्ण

/*
 * It's sane क्रम this to be empty, but we might want to take advantage of this.
 */
अटल व्योम atl2_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
पूर्ण

अटल पूर्णांक atl2_get_regs_len(काष्ठा net_device *netdev)
अणु
#घोषणा ATL2_REGS_LEN 42
	वापस माप(u32) * ATL2_REGS_LEN;
पूर्ण

अटल व्योम atl2_get_regs(काष्ठा net_device *netdev,
	काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl2_hw *hw = &adapter->hw;
	u32 *regs_buff = p;
	u16 phy_data;

	स_रखो(p, 0, माप(u32) * ATL2_REGS_LEN);

	regs->version = (1 << 24) | (hw->revision_id << 16) | hw->device_id;

	regs_buff[0]  = ATL2_READ_REG(hw, REG_VPD_CAP);
	regs_buff[1]  = ATL2_READ_REG(hw, REG_SPI_FLASH_CTRL);
	regs_buff[2]  = ATL2_READ_REG(hw, REG_SPI_FLASH_CONFIG);
	regs_buff[3]  = ATL2_READ_REG(hw, REG_TWSI_CTRL);
	regs_buff[4]  = ATL2_READ_REG(hw, REG_PCIE_DEV_MISC_CTRL);
	regs_buff[5]  = ATL2_READ_REG(hw, REG_MASTER_CTRL);
	regs_buff[6]  = ATL2_READ_REG(hw, REG_MANUAL_TIMER_INIT);
	regs_buff[7]  = ATL2_READ_REG(hw, REG_IRQ_MODU_TIMER_INIT);
	regs_buff[8]  = ATL2_READ_REG(hw, REG_PHY_ENABLE);
	regs_buff[9]  = ATL2_READ_REG(hw, REG_CMBDISDMA_TIMER);
	regs_buff[10] = ATL2_READ_REG(hw, REG_IDLE_STATUS);
	regs_buff[11] = ATL2_READ_REG(hw, REG_MDIO_CTRL);
	regs_buff[12] = ATL2_READ_REG(hw, REG_SERDES_LOCK);
	regs_buff[13] = ATL2_READ_REG(hw, REG_MAC_CTRL);
	regs_buff[14] = ATL2_READ_REG(hw, REG_MAC_IPG_IFG);
	regs_buff[15] = ATL2_READ_REG(hw, REG_MAC_STA_ADDR);
	regs_buff[16] = ATL2_READ_REG(hw, REG_MAC_STA_ADDR+4);
	regs_buff[17] = ATL2_READ_REG(hw, REG_RX_HASH_TABLE);
	regs_buff[18] = ATL2_READ_REG(hw, REG_RX_HASH_TABLE+4);
	regs_buff[19] = ATL2_READ_REG(hw, REG_MAC_HALF_DUPLX_CTRL);
	regs_buff[20] = ATL2_READ_REG(hw, REG_MTU);
	regs_buff[21] = ATL2_READ_REG(hw, REG_WOL_CTRL);
	regs_buff[22] = ATL2_READ_REG(hw, REG_SRAM_TXRAM_END);
	regs_buff[23] = ATL2_READ_REG(hw, REG_DESC_BASE_ADDR_HI);
	regs_buff[24] = ATL2_READ_REG(hw, REG_TXD_BASE_ADDR_LO);
	regs_buff[25] = ATL2_READ_REG(hw, REG_TXD_MEM_SIZE);
	regs_buff[26] = ATL2_READ_REG(hw, REG_TXS_BASE_ADDR_LO);
	regs_buff[27] = ATL2_READ_REG(hw, REG_TXS_MEM_SIZE);
	regs_buff[28] = ATL2_READ_REG(hw, REG_RXD_BASE_ADDR_LO);
	regs_buff[29] = ATL2_READ_REG(hw, REG_RXD_BUF_NUM);
	regs_buff[30] = ATL2_READ_REG(hw, REG_DMAR);
	regs_buff[31] = ATL2_READ_REG(hw, REG_TX_CUT_THRESH);
	regs_buff[32] = ATL2_READ_REG(hw, REG_DMAW);
	regs_buff[33] = ATL2_READ_REG(hw, REG_PAUSE_ON_TH);
	regs_buff[34] = ATL2_READ_REG(hw, REG_PAUSE_OFF_TH);
	regs_buff[35] = ATL2_READ_REG(hw, REG_MB_TXD_WR_IDX);
	regs_buff[36] = ATL2_READ_REG(hw, REG_MB_RXD_RD_IDX);
	regs_buff[38] = ATL2_READ_REG(hw, REG_ISR);
	regs_buff[39] = ATL2_READ_REG(hw, REG_IMR);

	atl2_पढ़ो_phy_reg(hw, MII_BMCR, &phy_data);
	regs_buff[40] = (u32)phy_data;
	atl2_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
	regs_buff[41] = (u32)phy_data;
पूर्ण

अटल पूर्णांक atl2_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);

	अगर (!atl2_check_eeprom_exist(&adapter->hw))
		वापस 512;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक atl2_get_eeprom(काष्ठा net_device *netdev,
	काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl2_hw *hw = &adapter->hw;
	u32 *eeprom_buff;
	पूर्णांक first_dword, last_dword;
	पूर्णांक ret_val = 0;
	पूर्णांक i;

	अगर (eeprom->len == 0)
		वापस -EINVAL;

	अगर (atl2_check_eeprom_exist(hw))
		वापस -EINVAL;

	eeprom->magic = hw->venकरोr_id | (hw->device_id << 16);

	first_dword = eeprom->offset >> 2;
	last_dword = (eeprom->offset + eeprom->len - 1) >> 2;

	eeprom_buff = kदो_स्मृति_array(last_dword - first_dword + 1, माप(u32),
				    GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	क्रम (i = first_dword; i < last_dword; i++) अणु
		अगर (!atl2_पढ़ो_eeprom(hw, i*4, &(eeprom_buff[i-first_dword]))) अणु
			ret_val = -EIO;
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	स_नकल(bytes, (u8 *)eeprom_buff + (eeprom->offset & 3),
		eeprom->len);
मुक्त:
	kमुक्त(eeprom_buff);

	वापस ret_val;
पूर्ण

अटल पूर्णांक atl2_set_eeprom(काष्ठा net_device *netdev,
	काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl2_hw *hw = &adapter->hw;
	u32 *eeprom_buff;
	u32 *ptr;
	पूर्णांक max_len, first_dword, last_dword, ret_val = 0;
	पूर्णांक i;

	अगर (eeprom->len == 0)
		वापस -EOPNOTSUPP;

	अगर (eeprom->magic != (hw->venकरोr_id | (hw->device_id << 16)))
		वापस -EFAULT;

	max_len = 512;

	first_dword = eeprom->offset >> 2;
	last_dword = (eeprom->offset + eeprom->len - 1) >> 2;
	eeprom_buff = kदो_स्मृति(max_len, GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	ptr = eeprom_buff;

	अगर (eeprom->offset & 3) अणु
		/* need पढ़ो/modअगरy/ग_लिखो of first changed EEPROM word */
		/* only the second byte of the word is being modअगरied */
		अगर (!atl2_पढ़ो_eeprom(hw, first_dword*4, &(eeprom_buff[0]))) अणु
			ret_val = -EIO;
			जाओ out;
		पूर्ण
		ptr++;
	पूर्ण
	अगर (((eeprom->offset + eeprom->len) & 3)) अणु
		/*
		 * need पढ़ो/modअगरy/ग_लिखो of last changed EEPROM word
		 * only the first byte of the word is being modअगरied
		 */
		अगर (!atl2_पढ़ो_eeprom(hw, last_dword * 4,
					&(eeprom_buff[last_dword - first_dword]))) अणु
			ret_val = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Device's eeprom is always little-endian, word addressable */
	स_नकल(ptr, bytes, eeprom->len);

	क्रम (i = 0; i < last_dword - first_dword + 1; i++) अणु
		अगर (!atl2_ग_लिखो_eeprom(hw, ((first_dword+i)*4), eeprom_buff[i])) अणु
			ret_val = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण
 out:
	kमुक्त(eeprom_buff);
	वापस ret_val;
पूर्ण

अटल व्योम atl2_get_drvinfo(काष्ठा net_device *netdev,
	काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver,  atl2_driver_name, माप(drvinfo->driver));
	strlcpy(drvinfo->fw_version, "L2", माप(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल व्योम atl2_get_wol(काष्ठा net_device *netdev,
	काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);

	wol->supported = WAKE_MAGIC;
	wol->wolopts = 0;

	अगर (adapter->wol & ATLX_WUFC_EX)
		wol->wolopts |= WAKE_UCAST;
	अगर (adapter->wol & ATLX_WUFC_MC)
		wol->wolopts |= WAKE_MCAST;
	अगर (adapter->wol & ATLX_WUFC_BC)
		wol->wolopts |= WAKE_BCAST;
	अगर (adapter->wol & ATLX_WUFC_MAG)
		wol->wolopts |= WAKE_MAGIC;
	अगर (adapter->wol & ATLX_WUFC_LNKC)
		wol->wolopts |= WAKE_PHY;
पूर्ण

अटल पूर्णांक atl2_set_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);

	अगर (wol->wolopts & (WAKE_ARP | WAKE_MAGICSECURE))
		वापस -EOPNOTSUPP;

	अगर (wol->wolopts & (WAKE_UCAST | WAKE_BCAST | WAKE_MCAST))
		वापस -EOPNOTSUPP;

	/* these settings will always override what we currently have */
	adapter->wol = 0;

	अगर (wol->wolopts & WAKE_MAGIC)
		adapter->wol |= ATLX_WUFC_MAG;
	अगर (wol->wolopts & WAKE_PHY)
		adapter->wol |= ATLX_WUFC_LNKC;

	वापस 0;
पूर्ण

अटल पूर्णांक atl2_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा atl2_adapter *adapter = netdev_priv(netdev);
	अगर (netअगर_running(netdev))
		atl2_reinit_locked(adapter);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops atl2_ethtool_ops = अणु
	.get_drvinfo		= atl2_get_drvinfo,
	.get_regs_len		= atl2_get_regs_len,
	.get_regs		= atl2_get_regs,
	.get_wol		= atl2_get_wol,
	.set_wol		= atl2_set_wol,
	.get_msglevel		= atl2_get_msglevel,
	.set_msglevel		= atl2_set_msglevel,
	.nway_reset		= atl2_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_eeprom_len		= atl2_get_eeprom_len,
	.get_eeprom		= atl2_get_eeprom,
	.set_eeprom		= atl2_set_eeprom,
	.get_link_ksettings	= atl2_get_link_ksettings,
	.set_link_ksettings	= atl2_set_link_ksettings,
पूर्ण;

#घोषणा LBYTESWAP(a)  ((((a) & 0x00ff00ff) << 8) | \
	(((a) & 0xff00ff00) >> 8))
#घोषणा LONGSWAP(a)   ((LBYTESWAP(a) << 16) | (LBYTESWAP(a) >> 16))
#घोषणा SHORTSWAP(a)  (((a) << 8) | ((a) >> 8))

/*
 * Reset the transmit and receive units; mask and clear all पूर्णांकerrupts.
 *
 * hw - Struct containing variables accessed by shared code
 * वापस : 0  or  idle status (अगर error)
 */
अटल s32 atl2_reset_hw(काष्ठा atl2_hw *hw)
अणु
	u32 icr;
	u16 pci_cfg_cmd_word;
	पूर्णांक i;

	/* Workaround क्रम PCI problem when BIOS sets MMRBC incorrectly. */
	atl2_पढ़ो_pci_cfg(hw, PCI_REG_COMMAND, &pci_cfg_cmd_word);
	अगर ((pci_cfg_cmd_word &
		(CMD_IO_SPACE|CMD_MEMORY_SPACE|CMD_BUS_MASTER)) !=
		(CMD_IO_SPACE|CMD_MEMORY_SPACE|CMD_BUS_MASTER)) अणु
		pci_cfg_cmd_word |=
			(CMD_IO_SPACE|CMD_MEMORY_SPACE|CMD_BUS_MASTER);
		atl2_ग_लिखो_pci_cfg(hw, PCI_REG_COMMAND, &pci_cfg_cmd_word);
	पूर्ण

	/* Clear Interrupt mask to stop board from generating
	 * पूर्णांकerrupts & Clear any pending पूर्णांकerrupt events
	 */
	/* FIXME */
	/* ATL2_WRITE_REG(hw, REG_IMR, 0); */
	/* ATL2_WRITE_REG(hw, REG_ISR, 0xffffffff); */

	/* Issue Soft Reset to the MAC.  This will reset the chip's
	 * transmit, receive, DMA.  It will not effect
	 * the current PCI configuration.  The global reset bit is self-
	 * clearing, and should clear within a microsecond.
	 */
	ATL2_WRITE_REG(hw, REG_MASTER_CTRL, MASTER_CTRL_SOFT_RST);
	wmb();
	msleep(1); /* delay about 1ms */

	/* Wait at least 10ms क्रम All module to be Idle */
	क्रम (i = 0; i < 10; i++) अणु
		icr = ATL2_READ_REG(hw, REG_IDLE_STATUS);
		अगर (!icr)
			अवरोध;
		msleep(1); /* delay 1 ms */
		cpu_relax();
	पूर्ण

	अगर (icr)
		वापस icr;

	वापस 0;
पूर्ण

#घोषणा CUSTOM_SPI_CS_SETUP        2
#घोषणा CUSTOM_SPI_CLK_HI          2
#घोषणा CUSTOM_SPI_CLK_LO          2
#घोषणा CUSTOM_SPI_CS_HOLD         2
#घोषणा CUSTOM_SPI_CS_HI           3

अटल काष्ठा atl2_spi_flash_dev flash_table[] =
अणु
/* MFR    WRSR  READ  PROGRAM WREN  WRDI  RDSR  RDID  SECTOR_ERASE CHIP_ERASE */
अणु"Atmel", 0x0,  0x03, 0x02,   0x06, 0x04, 0x05, 0x15, 0x52,        0x62 पूर्ण,
अणु"SST",   0x01, 0x03, 0x02,   0x06, 0x04, 0x05, 0x90, 0x20,        0x60 पूर्ण,
अणु"ST",    0x01, 0x03, 0x02,   0x06, 0x04, 0x05, 0xAB, 0xD8,        0xC7 पूर्ण,
पूर्ण;

अटल bool atl2_spi_पढ़ो(काष्ठा atl2_hw *hw, u32 addr, u32 *buf)
अणु
	पूर्णांक i;
	u32 value;

	ATL2_WRITE_REG(hw, REG_SPI_DATA, 0);
	ATL2_WRITE_REG(hw, REG_SPI_ADDR, addr);

	value = SPI_FLASH_CTRL_WAIT_READY |
		(CUSTOM_SPI_CS_SETUP & SPI_FLASH_CTRL_CS_SETUP_MASK) <<
			SPI_FLASH_CTRL_CS_SETUP_SHIFT |
		(CUSTOM_SPI_CLK_HI & SPI_FLASH_CTRL_CLK_HI_MASK) <<
			SPI_FLASH_CTRL_CLK_HI_SHIFT |
		(CUSTOM_SPI_CLK_LO & SPI_FLASH_CTRL_CLK_LO_MASK) <<
			SPI_FLASH_CTRL_CLK_LO_SHIFT |
		(CUSTOM_SPI_CS_HOLD & SPI_FLASH_CTRL_CS_HOLD_MASK) <<
			SPI_FLASH_CTRL_CS_HOLD_SHIFT |
		(CUSTOM_SPI_CS_HI & SPI_FLASH_CTRL_CS_HI_MASK) <<
			SPI_FLASH_CTRL_CS_HI_SHIFT |
		(0x1 & SPI_FLASH_CTRL_INS_MASK) << SPI_FLASH_CTRL_INS_SHIFT;

	ATL2_WRITE_REG(hw, REG_SPI_FLASH_CTRL, value);

	value |= SPI_FLASH_CTRL_START;

	ATL2_WRITE_REG(hw, REG_SPI_FLASH_CTRL, value);

	क्रम (i = 0; i < 10; i++) अणु
		msleep(1);
		value = ATL2_READ_REG(hw, REG_SPI_FLASH_CTRL);
		अगर (!(value & SPI_FLASH_CTRL_START))
			अवरोध;
	पूर्ण

	अगर (value & SPI_FLASH_CTRL_START)
		वापस false;

	*buf = ATL2_READ_REG(hw, REG_SPI_DATA);

	वापस true;
पूर्ण

/*
 * get_permanent_address
 * वापस 0 अगर get valid mac address,
 */
अटल पूर्णांक get_permanent_address(काष्ठा atl2_hw *hw)
अणु
	u32 Addr[2];
	u32 i, Control;
	u16 Register;
	u8  EthAddr[ETH_ALEN];
	bool KeyValid;

	अगर (is_valid_ether_addr(hw->perm_mac_addr))
		वापस 0;

	Addr[0] = 0;
	Addr[1] = 0;

	अगर (!atl2_check_eeprom_exist(hw)) अणु /* eeprom exists */
		Register = 0;
		KeyValid = false;

		/* Read out all EEPROM content */
		i = 0;
		जबतक (1) अणु
			अगर (atl2_पढ़ो_eeprom(hw, i + 0x100, &Control)) अणु
				अगर (KeyValid) अणु
					अगर (Register == REG_MAC_STA_ADDR)
						Addr[0] = Control;
					अन्यथा अगर (Register ==
						(REG_MAC_STA_ADDR + 4))
						Addr[1] = Control;
					KeyValid = false;
				पूर्ण अन्यथा अगर ((Control & 0xff) == 0x5A) अणु
					KeyValid = true;
					Register = (u16) (Control >> 16);
				पूर्ण अन्यथा अणु
			/* assume data end जबतक encount an invalid KEYWORD */
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				अवरोध; /* पढ़ो error */
			पूर्ण
			i += 4;
		पूर्ण

		*(u32 *) &EthAddr[2] = LONGSWAP(Addr[0]);
		*(u16 *) &EthAddr[0] = SHORTSWAP(*(u16 *) &Addr[1]);

		अगर (is_valid_ether_addr(EthAddr)) अणु
			स_नकल(hw->perm_mac_addr, EthAddr, ETH_ALEN);
			वापस 0;
		पूर्ण
		वापस 1;
	पूर्ण

	/* see अगर SPI flash exists? */
	Addr[0] = 0;
	Addr[1] = 0;
	Register = 0;
	KeyValid = false;
	i = 0;
	जबतक (1) अणु
		अगर (atl2_spi_पढ़ो(hw, i + 0x1f000, &Control)) अणु
			अगर (KeyValid) अणु
				अगर (Register == REG_MAC_STA_ADDR)
					Addr[0] = Control;
				अन्यथा अगर (Register == (REG_MAC_STA_ADDR + 4))
					Addr[1] = Control;
				KeyValid = false;
			पूर्ण अन्यथा अगर ((Control & 0xff) == 0x5A) अणु
				KeyValid = true;
				Register = (u16) (Control >> 16);
			पूर्ण अन्यथा अणु
				अवरोध; /* data end */
			पूर्ण
		पूर्ण अन्यथा अणु
			अवरोध; /* पढ़ो error */
		पूर्ण
		i += 4;
	पूर्ण

	*(u32 *) &EthAddr[2] = LONGSWAP(Addr[0]);
	*(u16 *) &EthAddr[0] = SHORTSWAP(*(u16 *)&Addr[1]);
	अगर (is_valid_ether_addr(EthAddr)) अणु
		स_नकल(hw->perm_mac_addr, EthAddr, ETH_ALEN);
		वापस 0;
	पूर्ण
	/* maybe MAC-address is from BIOS */
	Addr[0] = ATL2_READ_REG(hw, REG_MAC_STA_ADDR);
	Addr[1] = ATL2_READ_REG(hw, REG_MAC_STA_ADDR + 4);
	*(u32 *) &EthAddr[2] = LONGSWAP(Addr[0]);
	*(u16 *) &EthAddr[0] = SHORTSWAP(*(u16 *) &Addr[1]);

	अगर (is_valid_ether_addr(EthAddr)) अणु
		स_नकल(hw->perm_mac_addr, EthAddr, ETH_ALEN);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Reads the adapter's MAC address from the EEPROM
 *
 * hw - Struct containing variables accessed by shared code
 */
अटल s32 atl2_पढ़ो_mac_addr(काष्ठा atl2_hw *hw)
अणु
	अगर (get_permanent_address(hw)) अणु
		/* क्रम test */
		/* FIXME: shouldn't we use eth_अक्रमom_addr() here? */
		hw->perm_mac_addr[0] = 0x00;
		hw->perm_mac_addr[1] = 0x13;
		hw->perm_mac_addr[2] = 0x74;
		hw->perm_mac_addr[3] = 0x00;
		hw->perm_mac_addr[4] = 0x5c;
		hw->perm_mac_addr[5] = 0x38;
	पूर्ण

	स_नकल(hw->mac_addr, hw->perm_mac_addr, ETH_ALEN);

	वापस 0;
पूर्ण

/*
 * Hashes an address to determine its location in the multicast table
 *
 * hw - Struct containing variables accessed by shared code
 * mc_addr - the multicast address to hash
 *
 * atl2_hash_mc_addr
 *  purpose
 *      set hash value क्रम a multicast address
 *      hash calcu processing :
 *          1. calcu 32bit CRC क्रम multicast address
 *          2. reverse crc with MSB to LSB
 */
अटल u32 atl2_hash_mc_addr(काष्ठा atl2_hw *hw, u8 *mc_addr)
अणु
	u32 crc32, value;
	पूर्णांक i;

	value = 0;
	crc32 = ether_crc_le(6, mc_addr);

	क्रम (i = 0; i < 32; i++)
		value |= (((crc32 >> i) & 1) << (31 - i));

	वापस value;
पूर्ण

/*
 * Sets the bit in the multicast table corresponding to the hash value.
 *
 * hw - Struct containing variables accessed by shared code
 * hash_value - Multicast address hash value
 */
अटल व्योम atl2_hash_set(काष्ठा atl2_hw *hw, u32 hash_value)
अणु
	u32 hash_bit, hash_reg;
	u32 mta;

	/* The HASH Table  is a रेजिस्टर array of 2 32-bit रेजिस्टरs.
	 * It is treated like an array of 64 bits.  We want to set
	 * bit BitArray[hash_value]. So we figure out what रेजिस्टर
	 * the bit is in, पढ़ो it, OR in the new bit, then ग_लिखो
	 * back the new value.  The रेजिस्टर is determined by the
	 * upper 7 bits of the hash value and the bit within that
	 * रेजिस्टर are determined by the lower 5 bits of the value.
	 */
	hash_reg = (hash_value >> 31) & 0x1;
	hash_bit = (hash_value >> 26) & 0x1F;

	mta = ATL2_READ_REG_ARRAY(hw, REG_RX_HASH_TABLE, hash_reg);

	mta |= (1 << hash_bit);

	ATL2_WRITE_REG_ARRAY(hw, REG_RX_HASH_TABLE, hash_reg, mta);
पूर्ण

/*
 * atl2_init_pcie - init PCIE module
 */
अटल व्योम atl2_init_pcie(काष्ठा atl2_hw *hw)
अणु
    u32 value;
    value = LTSSM_TEST_MODE_DEF;
    ATL2_WRITE_REG(hw, REG_LTSSM_TEST_MODE, value);

    value = PCIE_DLL_TX_CTRL1_DEF;
    ATL2_WRITE_REG(hw, REG_PCIE_DLL_TX_CTRL1, value);
पूर्ण

अटल व्योम atl2_init_flash_opcode(काष्ठा atl2_hw *hw)
अणु
	अगर (hw->flash_venकरोr >= ARRAY_SIZE(flash_table))
		hw->flash_venकरोr = 0; /* ATMEL */

	/* Init OP table */
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_PROGRAM,
		flash_table[hw->flash_venकरोr].cmdPROGRAM);
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_SC_ERASE,
		flash_table[hw->flash_venकरोr].cmdSECTOR_ERASE);
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_CHIP_ERASE,
		flash_table[hw->flash_venकरोr].cmdCHIP_ERASE);
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_RDID,
		flash_table[hw->flash_venकरोr].cmdRDID);
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_WREN,
		flash_table[hw->flash_venकरोr].cmdWREN);
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_RDSR,
		flash_table[hw->flash_venकरोr].cmdRDSR);
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_WRSR,
		flash_table[hw->flash_venकरोr].cmdWRSR);
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_READ,
		flash_table[hw->flash_venकरोr].cmdREAD);
पूर्ण

/********************************************************************
* Perक्रमms basic configuration of the adapter.
*
* hw - Struct containing variables accessed by shared code
* Assumes that the controller has previously been reset and is in a
* post-reset uninitialized state. Initializes multicast table,
* and  Calls routines to setup link
* Leaves the transmit and receive units disabled and uninitialized.
********************************************************************/
अटल s32 atl2_init_hw(काष्ठा atl2_hw *hw)
अणु
	u32 ret_val = 0;

	atl2_init_pcie(hw);

	/* Zero out the Multicast HASH table */
	/* clear the old settings from the multicast hash table */
	ATL2_WRITE_REG(hw, REG_RX_HASH_TABLE, 0);
	ATL2_WRITE_REG_ARRAY(hw, REG_RX_HASH_TABLE, 1, 0);

	atl2_init_flash_opcode(hw);

	ret_val = atl2_phy_init(hw);

	वापस ret_val;
पूर्ण

/*
 * Detects the current speed and duplex settings of the hardware.
 *
 * hw - Struct containing variables accessed by shared code
 * speed - Speed of the connection
 * duplex - Duplex setting of the connection
 */
अटल s32 atl2_get_speed_and_duplex(काष्ठा atl2_hw *hw, u16 *speed,
	u16 *duplex)
अणु
	s32 ret_val;
	u16 phy_data;

	/* Read PHY Specअगरic Status Register (17) */
	ret_val = atl2_पढ़ो_phy_reg(hw, MII_ATLX_PSSR, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	अगर (!(phy_data & MII_ATLX_PSSR_SPD_DPLX_RESOLVED))
		वापस ATLX_ERR_PHY_RES;

	चयन (phy_data & MII_ATLX_PSSR_SPEED) अणु
	हाल MII_ATLX_PSSR_100MBS:
		*speed = SPEED_100;
		अवरोध;
	हाल MII_ATLX_PSSR_10MBS:
		*speed = SPEED_10;
		अवरोध;
	शेष:
		वापस ATLX_ERR_PHY_SPEED;
	पूर्ण

	अगर (phy_data & MII_ATLX_PSSR_DPLX)
		*duplex = FULL_DUPLEX;
	अन्यथा
		*duplex = HALF_DUPLEX;

	वापस 0;
पूर्ण

/*
 * Reads the value from a PHY रेजिस्टर
 * hw - Struct containing variables accessed by shared code
 * reg_addr - address of the PHY रेजिस्टर to पढ़ो
 */
अटल s32 atl2_पढ़ो_phy_reg(काष्ठा atl2_hw *hw, u16 reg_addr, u16 *phy_data)
अणु
	u32 val;
	पूर्णांक i;

	val = ((u32)(reg_addr & MDIO_REG_ADDR_MASK)) << MDIO_REG_ADDR_SHIFT |
		MDIO_START |
		MDIO_SUP_PREAMBLE |
		MDIO_RW |
		MDIO_CLK_25_4 << MDIO_CLK_SEL_SHIFT;
	ATL2_WRITE_REG(hw, REG_MDIO_CTRL, val);

	wmb();

	क्रम (i = 0; i < MDIO_WAIT_TIMES; i++) अणु
		udelay(2);
		val = ATL2_READ_REG(hw, REG_MDIO_CTRL);
		अगर (!(val & (MDIO_START | MDIO_BUSY)))
			अवरोध;
		wmb();
	पूर्ण
	अगर (!(val & (MDIO_START | MDIO_BUSY))) अणु
		*phy_data = (u16)val;
		वापस 0;
	पूर्ण

	वापस ATLX_ERR_PHY;
पूर्ण

/*
 * Writes a value to a PHY रेजिस्टर
 * hw - Struct containing variables accessed by shared code
 * reg_addr - address of the PHY रेजिस्टर to ग_लिखो
 * data - data to ग_लिखो to the PHY
 */
अटल s32 atl2_ग_लिखो_phy_reg(काष्ठा atl2_hw *hw, u32 reg_addr, u16 phy_data)
अणु
	पूर्णांक i;
	u32 val;

	val = ((u32)(phy_data & MDIO_DATA_MASK)) << MDIO_DATA_SHIFT |
		(reg_addr & MDIO_REG_ADDR_MASK) << MDIO_REG_ADDR_SHIFT |
		MDIO_SUP_PREAMBLE |
		MDIO_START |
		MDIO_CLK_25_4 << MDIO_CLK_SEL_SHIFT;
	ATL2_WRITE_REG(hw, REG_MDIO_CTRL, val);

	wmb();

	क्रम (i = 0; i < MDIO_WAIT_TIMES; i++) अणु
		udelay(2);
		val = ATL2_READ_REG(hw, REG_MDIO_CTRL);
		अगर (!(val & (MDIO_START | MDIO_BUSY)))
			अवरोध;

		wmb();
	पूर्ण

	अगर (!(val & (MDIO_START | MDIO_BUSY)))
		वापस 0;

	वापस ATLX_ERR_PHY;
पूर्ण

/*
 * Configures PHY स्वतःneg and flow control advertisement settings
 *
 * hw - Struct containing variables accessed by shared code
 */
अटल s32 atl2_phy_setup_स्वतःneg_adv(काष्ठा atl2_hw *hw)
अणु
	s16 mii_स्वतःneg_adv_reg;

	/* Read the MII Auto-Neg Advertisement Register (Address 4). */
	mii_स्वतःneg_adv_reg = MII_AR_DEFAULT_CAP_MASK;

	/* Need to parse स्वतःneg_advertised  and set up
	 * the appropriate PHY रेजिस्टरs.  First we will parse क्रम
	 * स्वतःneg_advertised software override.  Since we can advertise
	 * a plethora of combinations, we need to check each bit
	 * inभागidually.
	 */

	/* First we clear all the 10/100 mb speed bits in the Auto-Neg
	 * Advertisement Register (Address 4) and the 1000 mb speed bits in
	 * the  1000Base-T Control Register (Address 9). */
	mii_स्वतःneg_adv_reg &= ~MII_AR_SPEED_MASK;

	/* Need to parse MediaType and setup the
	 * appropriate PHY रेजिस्टरs. */
	चयन (hw->MediaType) अणु
	हाल MEDIA_TYPE_AUTO_SENSOR:
		mii_स्वतःneg_adv_reg |=
			(MII_AR_10T_HD_CAPS |
			MII_AR_10T_FD_CAPS  |
			MII_AR_100TX_HD_CAPS|
			MII_AR_100TX_FD_CAPS);
		hw->स्वतःneg_advertised =
			ADVERTISE_10_HALF |
			ADVERTISE_10_FULL |
			ADVERTISE_100_HALF|
			ADVERTISE_100_FULL;
		अवरोध;
	हाल MEDIA_TYPE_100M_FULL:
		mii_स्वतःneg_adv_reg |= MII_AR_100TX_FD_CAPS;
		hw->स्वतःneg_advertised = ADVERTISE_100_FULL;
		अवरोध;
	हाल MEDIA_TYPE_100M_HALF:
		mii_स्वतःneg_adv_reg |= MII_AR_100TX_HD_CAPS;
		hw->स्वतःneg_advertised = ADVERTISE_100_HALF;
		अवरोध;
	हाल MEDIA_TYPE_10M_FULL:
		mii_स्वतःneg_adv_reg |= MII_AR_10T_FD_CAPS;
		hw->स्वतःneg_advertised = ADVERTISE_10_FULL;
		अवरोध;
	शेष:
		mii_स्वतःneg_adv_reg |= MII_AR_10T_HD_CAPS;
		hw->स्वतःneg_advertised = ADVERTISE_10_HALF;
		अवरोध;
	पूर्ण

	/* flow control fixed to enable all */
	mii_स्वतःneg_adv_reg |= (MII_AR_ASM_सूची | MII_AR_PAUSE);

	hw->mii_स्वतःneg_adv_reg = mii_स्वतःneg_adv_reg;

	वापस atl2_ग_लिखो_phy_reg(hw, MII_ADVERTISE, mii_स्वतःneg_adv_reg);
पूर्ण

/*
 * Resets the PHY and make all config validate
 *
 * hw - Struct containing variables accessed by shared code
 *
 * Sets bit 15 and 12 of the MII Control regiser (क्रम F001 bug)
 */
अटल s32 atl2_phy_commit(काष्ठा atl2_hw *hw)
अणु
	s32 ret_val;
	u16 phy_data;

	phy_data = MII_CR_RESET | MII_CR_AUTO_NEG_EN | MII_CR_RESTART_AUTO_NEG;
	ret_val = atl2_ग_लिखो_phy_reg(hw, MII_BMCR, phy_data);
	अगर (ret_val) अणु
		u32 val;
		पूर्णांक i;
		/* pcie serdes link may be करोwn ! */
		क्रम (i = 0; i < 25; i++) अणु
			msleep(1);
			val = ATL2_READ_REG(hw, REG_MDIO_CTRL);
			अगर (!(val & (MDIO_START | MDIO_BUSY)))
				अवरोध;
		पूर्ण

		अगर (0 != (val & (MDIO_START | MDIO_BUSY))) अणु
			prपूर्णांकk(KERN_ERR "atl2: PCIe link down for at least 25ms !\n");
			वापस ret_val;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल s32 atl2_phy_init(काष्ठा atl2_hw *hw)
अणु
	s32 ret_val;
	u16 phy_val;

	अगर (hw->phy_configured)
		वापस 0;

	/* Enable PHY */
	ATL2_WRITE_REGW(hw, REG_PHY_ENABLE, 1);
	ATL2_WRITE_FLUSH(hw);
	msleep(1);

	/* check अगर the PHY is in घातersaving mode */
	atl2_ग_लिखो_phy_reg(hw, MII_DBG_ADDR, 0);
	atl2_पढ़ो_phy_reg(hw, MII_DBG_DATA, &phy_val);

	/* 024E / 124E 0r 0274 / 1274 ? */
	अगर (phy_val & 0x1000) अणु
		phy_val &= ~0x1000;
		atl2_ग_लिखो_phy_reg(hw, MII_DBG_DATA, phy_val);
	पूर्ण

	msleep(1);

	/*Enable PHY LinkChange Interrupt */
	ret_val = atl2_ग_लिखो_phy_reg(hw, 18, 0xC00);
	अगर (ret_val)
		वापस ret_val;

	/* setup AutoNeg parameters */
	ret_val = atl2_phy_setup_स्वतःneg_adv(hw);
	अगर (ret_val)
		वापस ret_val;

	/* SW.Reset & En-Auto-Neg to restart Auto-Neg */
	ret_val = atl2_phy_commit(hw);
	अगर (ret_val)
		वापस ret_val;

	hw->phy_configured = true;

	वापस ret_val;
पूर्ण

अटल व्योम atl2_set_mac_addr(काष्ठा atl2_hw *hw)
अणु
	u32 value;
	/* 00-0B-6A-F6-00-DC
	 * 0:  6AF600DC   1: 000B
	 * low dword */
	value = (((u32)hw->mac_addr[2]) << 24) |
		(((u32)hw->mac_addr[3]) << 16) |
		(((u32)hw->mac_addr[4]) << 8)  |
		(((u32)hw->mac_addr[5]));
	ATL2_WRITE_REG_ARRAY(hw, REG_MAC_STA_ADDR, 0, value);
	/* hight dword */
	value = (((u32)hw->mac_addr[0]) << 8) |
		(((u32)hw->mac_addr[1]));
	ATL2_WRITE_REG_ARRAY(hw, REG_MAC_STA_ADDR, 1, value);
पूर्ण

/*
 * check_eeprom_exist
 * वापस 0 अगर eeprom exist
 */
अटल पूर्णांक atl2_check_eeprom_exist(काष्ठा atl2_hw *hw)
अणु
	u32 value;

	value = ATL2_READ_REG(hw, REG_SPI_FLASH_CTRL);
	अगर (value & SPI_FLASH_CTRL_EN_VPD) अणु
		value &= ~SPI_FLASH_CTRL_EN_VPD;
		ATL2_WRITE_REG(hw, REG_SPI_FLASH_CTRL, value);
	पूर्ण
	value = ATL2_READ_REGW(hw, REG_PCIE_CAP_LIST);
	वापस ((value & 0xFF00) == 0x6C00) ? 0 : 1;
पूर्ण

/* FIXME: This करोesn't look right. -- CHS */
अटल bool atl2_ग_लिखो_eeprom(काष्ठा atl2_hw *hw, u32 offset, u32 value)
अणु
	वापस true;
पूर्ण

अटल bool atl2_पढ़ो_eeprom(काष्ठा atl2_hw *hw, u32 Offset, u32 *pValue)
अणु
	पूर्णांक i;
	u32    Control;

	अगर (Offset & 0x3)
		वापस false; /* address करो not align */

	ATL2_WRITE_REG(hw, REG_VPD_DATA, 0);
	Control = (Offset & VPD_CAP_VPD_ADDR_MASK) << VPD_CAP_VPD_ADDR_SHIFT;
	ATL2_WRITE_REG(hw, REG_VPD_CAP, Control);

	क्रम (i = 0; i < 10; i++) अणु
		msleep(2);
		Control = ATL2_READ_REG(hw, REG_VPD_CAP);
		अगर (Control & VPD_CAP_VPD_FLAG)
			अवरोध;
	पूर्ण

	अगर (Control & VPD_CAP_VPD_FLAG) अणु
		*pValue = ATL2_READ_REG(hw, REG_VPD_DATA);
		वापस true;
	पूर्ण
	वापस false; /* समयout */
पूर्ण

अटल व्योम atl2_क्रमce_ps(काष्ठा atl2_hw *hw)
अणु
	u16 phy_val;

	atl2_ग_लिखो_phy_reg(hw, MII_DBG_ADDR, 0);
	atl2_पढ़ो_phy_reg(hw, MII_DBG_DATA, &phy_val);
	atl2_ग_लिखो_phy_reg(hw, MII_DBG_DATA, phy_val | 0x1000);

	atl2_ग_लिखो_phy_reg(hw, MII_DBG_ADDR, 2);
	atl2_ग_लिखो_phy_reg(hw, MII_DBG_DATA, 0x3000);
	atl2_ग_लिखो_phy_reg(hw, MII_DBG_ADDR, 3);
	atl2_ग_लिखो_phy_reg(hw, MII_DBG_DATA, 0);
पूर्ण

/* This is the only thing that needs to be changed to adjust the
 * maximum number of ports that the driver can manage.
 */
#घोषणा ATL2_MAX_NIC 4

#घोषणा OPTION_UNSET    -1
#घोषणा OPTION_DISABLED 0
#घोषणा OPTION_ENABLED  1

/* All parameters are treated the same, as an पूर्णांकeger array of values.
 * This macro just reduces the need to repeat the same declaration code
 * over and over (plus this helps to aव्योम typo bugs).
 */
#घोषणा ATL2_PARAM_INIT अणु[0 ... ATL2_MAX_NIC] = OPTION_UNSETपूर्ण
#अगर_अघोषित module_param_array
/* Module Parameters are always initialized to -1, so that the driver
 * can tell the dअगरference between no user specअगरied value or the
 * user asking क्रम the शेष value.
 * The true शेष values are loaded in when atl2_check_options is called.
 *
 * This is a GCC extension to ANSI C.
 * See the item "Labeled Elements in Initializers" in the section
 * "Extensions to the C Language Family" of the GCC करोcumentation.
 */

#घोषणा ATL2_PARAM(X, desc) \
    अटल स्थिर पूर्णांक X[ATL2_MAX_NIC + 1] = ATL2_PARAM_INIT; \
    MODULE_PARM(X, "1-" __MODULE_STRING(ATL2_MAX_NIC) "i"); \
    MODULE_PARM_DESC(X, desc);
#अन्यथा
#घोषणा ATL2_PARAM(X, desc) \
    अटल पूर्णांक X[ATL2_MAX_NIC+1] = ATL2_PARAM_INIT; \
    अटल अचिन्हित पूर्णांक num_##X; \
    module_param_array_named(X, X, पूर्णांक, &num_##X, 0); \
    MODULE_PARM_DESC(X, desc);
#पूर्ण_अगर

/*
 * Transmit Memory Size
 * Valid Range: 64-2048
 * Default Value: 128
 */
#घोषणा ATL2_MIN_TX_MEMSIZE		4	/* 4KB */
#घोषणा ATL2_MAX_TX_MEMSIZE		64	/* 64KB */
#घोषणा ATL2_DEFAULT_TX_MEMSIZE		8	/* 8KB */
ATL2_PARAM(TxMemSize, "Bytes of Transmit Memory");

/*
 * Receive Memory Block Count
 * Valid Range: 16-512
 * Default Value: 128
 */
#घोषणा ATL2_MIN_RXD_COUNT		16
#घोषणा ATL2_MAX_RXD_COUNT		512
#घोषणा ATL2_DEFAULT_RXD_COUNT		64
ATL2_PARAM(RxMemBlock, "Number of receive memory block");

/*
 * User Specअगरied MediaType Override
 *
 * Valid Range: 0-5
 *  - 0    - स्वतः-negotiate at all supported speeds
 *  - 1    - only link at 1000Mbps Full Duplex
 *  - 2    - only link at 100Mbps Full Duplex
 *  - 3    - only link at 100Mbps Half Duplex
 *  - 4    - only link at 10Mbps Full Duplex
 *  - 5    - only link at 10Mbps Half Duplex
 * Default Value: 0
 */
ATL2_PARAM(MediaType, "MediaType Select");

/*
 * Interrupt Moderate Timer in units of 2048 ns (~2 us)
 * Valid Range: 10-65535
 * Default Value: 45000(90ms)
 */
#घोषणा INT_MOD_DEFAULT_CNT	100 /* 200us */
#घोषणा INT_MOD_MAX_CNT		65000
#घोषणा INT_MOD_MIN_CNT		50
ATL2_PARAM(IntModTimer, "Interrupt Moderator Timer");

/*
 * FlashVenकरोr
 * Valid Range: 0-2
 * 0 - Aपंचांगel
 * 1 - SST
 * 2 - ST
 */
ATL2_PARAM(FlashVenकरोr, "SPI Flash Vendor");

#घोषणा AUTONEG_ADV_DEFAULT	0x2F
#घोषणा AUTONEG_ADV_MASK	0x2F
#घोषणा FLOW_CONTROL_DEFAULT	FLOW_CONTROL_FULL

#घोषणा FLASH_VENDOR_DEFAULT	0
#घोषणा FLASH_VENDOR_MIN	0
#घोषणा FLASH_VENDOR_MAX	2

काष्ठा atl2_option अणु
	क्रमागत अणु enable_option, range_option, list_option पूर्ण type;
	अक्षर *name;
	अक्षर *err;
	पूर्णांक  def;
	जोड़ अणु
		काष्ठा अणु /* range_option info */
			पूर्णांक min;
			पूर्णांक max;
		पूर्ण r;
		काष्ठा अणु /* list_option info */
			पूर्णांक nr;
			काष्ठा atl2_opt_list अणु पूर्णांक i; अक्षर *str; पूर्ण *p;
		पूर्ण l;
	पूर्ण arg;
पूर्ण;

अटल पूर्णांक atl2_validate_option(पूर्णांक *value, काष्ठा atl2_option *opt)
अणु
	पूर्णांक i;
	काष्ठा atl2_opt_list *ent;

	अगर (*value == OPTION_UNSET) अणु
		*value = opt->def;
		वापस 0;
	पूर्ण

	चयन (opt->type) अणु
	हाल enable_option:
		चयन (*value) अणु
		हाल OPTION_ENABLED:
			prपूर्णांकk(KERN_INFO "%s Enabled\n", opt->name);
			वापस 0;
		हाल OPTION_DISABLED:
			prपूर्णांकk(KERN_INFO "%s Disabled\n", opt->name);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल range_option:
		अगर (*value >= opt->arg.r.min && *value <= opt->arg.r.max) अणु
			prपूर्णांकk(KERN_INFO "%s set to %i\n", opt->name, *value);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल list_option:
		क्रम (i = 0; i < opt->arg.l.nr; i++) अणु
			ent = &opt->arg.l.p[i];
			अगर (*value == ent->i) अणु
				अगर (ent->str[0] != '\0')
					prपूर्णांकk(KERN_INFO "%s\n", ent->str);
				वापस 0;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	prपूर्णांकk(KERN_INFO "Invalid %s specified (%i) %s\n",
		opt->name, *value, opt->err);
	*value = opt->def;
	वापस -1;
पूर्ण

/**
 * atl2_check_options - Range Checking क्रम Command Line Parameters
 * @adapter: board निजी काष्ठाure
 *
 * This routine checks all command line parameters क्रम valid user
 * input.  If an invalid value is given, or अगर no user specअगरied
 * value exists, a शेष value is used.  The final value is stored
 * in a variable in the adapter काष्ठाure.
 */
अटल व्योम atl2_check_options(काष्ठा atl2_adapter *adapter)
अणु
	पूर्णांक val;
	काष्ठा atl2_option opt;
	पूर्णांक bd = adapter->bd_number;
	अगर (bd >= ATL2_MAX_NIC) अणु
		prपूर्णांकk(KERN_NOTICE "Warning: no configuration for board #%i\n",
			bd);
		prपूर्णांकk(KERN_NOTICE "Using defaults for all values\n");
#अगर_अघोषित module_param_array
		bd = ATL2_MAX_NIC;
#पूर्ण_अगर
	पूर्ण

	/* Bytes of Transmit Memory */
	opt.type = range_option;
	opt.name = "Bytes of Transmit Memory";
	opt.err = "using default of " __MODULE_STRING(ATL2_DEFAULT_TX_MEMSIZE);
	opt.def = ATL2_DEFAULT_TX_MEMSIZE;
	opt.arg.r.min = ATL2_MIN_TX_MEMSIZE;
	opt.arg.r.max = ATL2_MAX_TX_MEMSIZE;
#अगर_घोषित module_param_array
	अगर (num_TxMemSize > bd) अणु
#पूर्ण_अगर
		val = TxMemSize[bd];
		atl2_validate_option(&val, &opt);
		adapter->txd_ring_size = ((u32) val) * 1024;
#अगर_घोषित module_param_array
	पूर्ण अन्यथा
		adapter->txd_ring_size = ((u32)opt.def) * 1024;
#पूर्ण_अगर
	/* txs ring size: */
	adapter->txs_ring_size = adapter->txd_ring_size / 128;
	अगर (adapter->txs_ring_size > 160)
		adapter->txs_ring_size = 160;

	/* Receive Memory Block Count */
	opt.type = range_option;
	opt.name = "Number of receive memory block";
	opt.err = "using default of " __MODULE_STRING(ATL2_DEFAULT_RXD_COUNT);
	opt.def = ATL2_DEFAULT_RXD_COUNT;
	opt.arg.r.min = ATL2_MIN_RXD_COUNT;
	opt.arg.r.max = ATL2_MAX_RXD_COUNT;
#अगर_घोषित module_param_array
	अगर (num_RxMemBlock > bd) अणु
#पूर्ण_अगर
		val = RxMemBlock[bd];
		atl2_validate_option(&val, &opt);
		adapter->rxd_ring_size = (u32)val;
		/* FIXME */
		/* ((u16)val)&~1; */	/* even number */
#अगर_घोषित module_param_array
	पूर्ण अन्यथा
		adapter->rxd_ring_size = (u32)opt.def;
#पूर्ण_अगर
	/* init RXD Flow control value */
	adapter->hw.fc_rxd_hi = (adapter->rxd_ring_size / 8) * 7;
	adapter->hw.fc_rxd_lo = (ATL2_MIN_RXD_COUNT / 8) >
		(adapter->rxd_ring_size / 12) ? (ATL2_MIN_RXD_COUNT / 8) :
		(adapter->rxd_ring_size / 12);

	/* Interrupt Moderate Timer */
	opt.type = range_option;
	opt.name = "Interrupt Moderate Timer";
	opt.err = "using default of " __MODULE_STRING(INT_MOD_DEFAULT_CNT);
	opt.def = INT_MOD_DEFAULT_CNT;
	opt.arg.r.min = INT_MOD_MIN_CNT;
	opt.arg.r.max = INT_MOD_MAX_CNT;
#अगर_घोषित module_param_array
	अगर (num_IntModTimer > bd) अणु
#पूर्ण_अगर
		val = IntModTimer[bd];
		atl2_validate_option(&val, &opt);
		adapter->imt = (u16) val;
#अगर_घोषित module_param_array
	पूर्ण अन्यथा
		adapter->imt = (u16)(opt.def);
#पूर्ण_अगर
	/* Flash Venकरोr */
	opt.type = range_option;
	opt.name = "SPI Flash Vendor";
	opt.err = "using default of " __MODULE_STRING(FLASH_VENDOR_DEFAULT);
	opt.def = FLASH_VENDOR_DEFAULT;
	opt.arg.r.min = FLASH_VENDOR_MIN;
	opt.arg.r.max = FLASH_VENDOR_MAX;
#अगर_घोषित module_param_array
	अगर (num_FlashVenकरोr > bd) अणु
#पूर्ण_अगर
		val = FlashVenकरोr[bd];
		atl2_validate_option(&val, &opt);
		adapter->hw.flash_venकरोr = (u8) val;
#अगर_घोषित module_param_array
	पूर्ण अन्यथा
		adapter->hw.flash_venकरोr = (u8)(opt.def);
#पूर्ण_अगर
	/* MediaType */
	opt.type = range_option;
	opt.name = "Speed/Duplex Selection";
	opt.err = "using default of " __MODULE_STRING(MEDIA_TYPE_AUTO_SENSOR);
	opt.def = MEDIA_TYPE_AUTO_SENSOR;
	opt.arg.r.min = MEDIA_TYPE_AUTO_SENSOR;
	opt.arg.r.max = MEDIA_TYPE_10M_HALF;
#अगर_घोषित module_param_array
	अगर (num_MediaType > bd) अणु
#पूर्ण_अगर
		val = MediaType[bd];
		atl2_validate_option(&val, &opt);
		adapter->hw.MediaType = (u16) val;
#अगर_घोषित module_param_array
	पूर्ण अन्यथा
		adapter->hw.MediaType = (u16)(opt.def);
#पूर्ण_अगर
पूर्ण
