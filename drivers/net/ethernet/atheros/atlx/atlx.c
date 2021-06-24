<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* atlx.c -- common functions क्रम Attansic network drivers
 *
 * Copyright(c) 2005 - 2006 Attansic Corporation. All rights reserved.
 * Copyright(c) 2006 - 2007 Chris Snook <csnook@redhat.com>
 * Copyright(c) 2006 - 2008 Jay Cliburn <jcliburn@gmail.com>
 * Copyright(c) 2007 Atheros Corporation. All rights reserved.
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 */

/* Including this file like a header is a temporary hack, I promise. -- CHS */
#अगर_अघोषित ATLX_C
#घोषणा ATLX_C

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश "atlx.h"

अटल s32 atlx_पढ़ो_phy_reg(काष्ठा atl1_hw *hw, u16 reg_addr, u16 *phy_data);
अटल u32 atlx_hash_mc_addr(काष्ठा atl1_hw *hw, u8 *mc_addr);
अटल व्योम atlx_set_mac_addr(काष्ठा atl1_hw *hw);

अटल काष्ठा atlx_spi_flash_dev flash_table[] = अणु
/*	MFR_NAME  WRSR  READ  PRGM  WREN  WRDI  RDSR  RDID  SEC_ERS CHIP_ERS */
	अणु"Atmel", 0x00, 0x03, 0x02, 0x06, 0x04, 0x05, 0x15, 0x52,   0x62पूर्ण,
	अणु"SST",   0x01, 0x03, 0x02, 0x06, 0x04, 0x05, 0x90, 0x20,   0x60पूर्ण,
	अणु"ST",    0x01, 0x03, 0x02, 0x06, 0x04, 0x05, 0xAB, 0xD8,   0xC7पूर्ण,
पूर्ण;

अटल पूर्णांक atlx_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
		वापस atlx_mii_ioctl(netdev, अगरr, cmd);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * atlx_set_mac - Change the Ethernet Address of the NIC
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @p: poपूर्णांकer to an address काष्ठाure
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक atlx_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा atlx_adapter *adapter = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;

	अगर (netअगर_running(netdev))
		वापस -EBUSY;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	स_नकल(adapter->hw.mac_addr, addr->sa_data, netdev->addr_len);

	atlx_set_mac_addr(&adapter->hw);
	वापस 0;
पूर्ण

अटल व्योम atlx_check_क्रम_link(काष्ठा atlx_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	u16 phy_data = 0;

	spin_lock(&adapter->lock);
	adapter->phy_समयr_pending = false;
	atlx_पढ़ो_phy_reg(&adapter->hw, MII_BMSR, &phy_data);
	atlx_पढ़ो_phy_reg(&adapter->hw, MII_BMSR, &phy_data);
	spin_unlock(&adapter->lock);

	/* notअगरy upper layer link करोwn ASAP */
	अगर (!(phy_data & BMSR_LSTATUS)) अणु
		/* Link Down */
		अगर (netअगर_carrier_ok(netdev)) अणु
			/* old link state: Up */
			dev_info(&adapter->pdev->dev, "%s link is down\n",
				netdev->name);
			adapter->link_speed = SPEED_0;
			netअगर_carrier_off(netdev);
		पूर्ण
	पूर्ण
	schedule_work(&adapter->link_chg_task);
पूर्ण

/**
 * atlx_set_multi - Multicast and Promiscuous mode set
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The set_multi entry poपूर्णांक is called whenever the multicast address
 * list or the network पूर्णांकerface flags are updated.  This routine is
 * responsible क्रम configuring the hardware क्रम proper multicast,
 * promiscuous mode, and all-multi behavior.
 */
अटल व्योम atlx_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा atlx_adapter *adapter = netdev_priv(netdev);
	काष्ठा atlx_hw *hw = &adapter->hw;
	काष्ठा netdev_hw_addr *ha;
	u32 rctl;
	u32 hash_value;

	/* Check क्रम Promiscuous and All Multicast modes */
	rctl = ioपढ़ो32(hw->hw_addr + REG_MAC_CTRL);
	अगर (netdev->flags & IFF_PROMISC)
		rctl |= MAC_CTRL_PROMIS_EN;
	अन्यथा अगर (netdev->flags & IFF_ALLMULTI) अणु
		rctl |= MAC_CTRL_MC_ALL_EN;
		rctl &= ~MAC_CTRL_PROMIS_EN;
	पूर्ण अन्यथा
		rctl &= ~(MAC_CTRL_PROMIS_EN | MAC_CTRL_MC_ALL_EN);

	ioग_लिखो32(rctl, hw->hw_addr + REG_MAC_CTRL);

	/* clear the old settings from the multicast hash table */
	ioग_लिखो32(0, hw->hw_addr + REG_RX_HASH_TABLE);
	ioग_लिखो32(0, (hw->hw_addr + REG_RX_HASH_TABLE) + (1 << 2));

	/* compute mc addresses' hash value ,and put it पूर्णांकo hash table */
	netdev_क्रम_each_mc_addr(ha, netdev) अणु
		hash_value = atlx_hash_mc_addr(hw, ha->addr);
		atlx_hash_set(hw, hash_value);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम atlx_imr_set(काष्ठा atlx_adapter *adapter,
				अचिन्हित पूर्णांक imr)
अणु
	ioग_लिखो32(imr, adapter->hw.hw_addr + REG_IMR);
	ioपढ़ो32(adapter->hw.hw_addr + REG_IMR);
पूर्ण

/**
 * atlx_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 * @adapter: board निजी काष्ठाure
 */
अटल व्योम atlx_irq_enable(काष्ठा atlx_adapter *adapter)
अणु
	atlx_imr_set(adapter, IMR_NORMAL_MASK);
	adapter->पूर्णांक_enabled = true;
पूर्ण

/**
 * atlx_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 * @adapter: board निजी काष्ठाure
 */
अटल व्योम atlx_irq_disable(काष्ठा atlx_adapter *adapter)
अणु
	adapter->पूर्णांक_enabled = false;
	atlx_imr_set(adapter, 0);
	synchronize_irq(adapter->pdev->irq);
पूर्ण

अटल व्योम atlx_clear_phy_पूर्णांक(काष्ठा atlx_adapter *adapter)
अणु
	u16 phy_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adapter->lock, flags);
	atlx_पढ़ो_phy_reg(&adapter->hw, 19, &phy_data);
	spin_unlock_irqrestore(&adapter->lock, flags);
पूर्ण

/**
 * atlx_tx_समयout - Respond to a Tx Hang
 * @netdev: network पूर्णांकerface device काष्ठाure
 */
अटल व्योम atlx_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा atlx_adapter *adapter = netdev_priv(netdev);
	/* Do the reset outside of पूर्णांकerrupt context */
	schedule_work(&adapter->reset_dev_task);
पूर्ण

/*
 * atlx_link_chg_task - deal with link change event Out of पूर्णांकerrupt context
 */
अटल व्योम atlx_link_chg_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा atlx_adapter *adapter;
	अचिन्हित दीर्घ flags;

	adapter = container_of(work, काष्ठा atlx_adapter, link_chg_task);

	spin_lock_irqsave(&adapter->lock, flags);
	atlx_check_link(adapter);
	spin_unlock_irqrestore(&adapter->lock, flags);
पूर्ण

अटल व्योम __atlx_vlan_mode(netdev_features_t features, u32 *ctrl)
अणु
	अगर (features & NETIF_F_HW_VLAN_CTAG_RX) अणु
		/* enable VLAN tag insert/strip */
		*ctrl |= MAC_CTRL_RMV_VLAN;
	पूर्ण अन्यथा अणु
		/* disable VLAN tag insert/strip */
		*ctrl &= ~MAC_CTRL_RMV_VLAN;
	पूर्ण
पूर्ण

अटल व्योम atlx_vlan_mode(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	काष्ठा atlx_adapter *adapter = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	u32 ctrl;

	spin_lock_irqsave(&adapter->lock, flags);
	/* atlx_irq_disable(adapter); FIXME: confirm/हटाओ */
	ctrl = ioपढ़ो32(adapter->hw.hw_addr + REG_MAC_CTRL);
	__atlx_vlan_mode(features, &ctrl);
	ioग_लिखो32(ctrl, adapter->hw.hw_addr + REG_MAC_CTRL);
	/* atlx_irq_enable(adapter); FIXME */
	spin_unlock_irqrestore(&adapter->lock, flags);
पूर्ण

अटल व्योम atlx_restore_vlan(काष्ठा atlx_adapter *adapter)
अणु
	atlx_vlan_mode(adapter->netdev, adapter->netdev->features);
पूर्ण

अटल netdev_features_t atlx_fix_features(काष्ठा net_device *netdev,
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

अटल पूर्णांक atlx_set_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	netdev_features_t changed = netdev->features ^ features;

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX)
		atlx_vlan_mode(netdev, features);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* ATLX_C */
