<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1999 - 2010 Intel Corporation.
 * Copyright (C) 2010 - 2012 LAPIS SEMICONDUCTOR CO., LTD.
 *
 * This code was derived from the Intel e1000e Linux driver.
 */

#समावेश "pch_gbe.h"
#समावेश "pch_gbe_phy.h"
#समावेश <linux/module.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/ptp_pch.h>
#समावेश <linux/gpपन.स>

#घोषणा DRV_VERSION     "1.01"
स्थिर अक्षर pch_driver_version[] = DRV_VERSION;

#घोषणा PCH_GBE_MAR_ENTRIES		16
#घोषणा PCH_GBE_SHORT_PKT		64
#घोषणा DSC_INIT16			0xC000
#घोषणा PCH_GBE_DMA_ALIGN		0
#घोषणा PCH_GBE_DMA_PADDING		2
#घोषणा PCH_GBE_WATCHDOG_PERIOD		(5 * HZ)	/* watchकरोg समय */
#घोषणा PCH_GBE_PCI_BAR			1
#घोषणा PCH_GBE_RESERVE_MEMORY		0x200000	/* 2MB */

#घोषणा PCI_DEVICE_ID_INTEL_IOH1_GBE		0x8802

#घोषणा PCI_DEVICE_ID_ROHM_ML7223_GBE		0x8013
#घोषणा PCI_DEVICE_ID_ROHM_ML7831_GBE		0x8802

#घोषणा PCH_GBE_TX_WEIGHT         64
#घोषणा PCH_GBE_RX_WEIGHT         64
#घोषणा PCH_GBE_RX_BUFFER_WRITE   16

/* Initialize the wake-on-LAN settings */
#घोषणा PCH_GBE_WL_INIT_SETTING    (PCH_GBE_WLC_MP)

#घोषणा PCH_GBE_MAC_RGMII_CTRL_SETTING ( \
	PCH_GBE_CHIP_TYPE_INTERNAL | \
	PCH_GBE_RGMII_MODE_RGMII     \
	)

/* Ethertype field values */
#घोषणा PCH_GBE_MAX_RX_BUFFER_SIZE      0x2880
#घोषणा PCH_GBE_MAX_JUMBO_FRAME_SIZE    10318
#घोषणा PCH_GBE_FRAME_SIZE_2048         2048
#घोषणा PCH_GBE_FRAME_SIZE_4096         4096
#घोषणा PCH_GBE_FRAME_SIZE_8192         8192

#घोषणा PCH_GBE_GET_DESC(R, i, type)    (&(((काष्ठा type *)((R).desc))[i]))
#घोषणा PCH_GBE_RX_DESC(R, i)           PCH_GBE_GET_DESC(R, i, pch_gbe_rx_desc)
#घोषणा PCH_GBE_TX_DESC(R, i)           PCH_GBE_GET_DESC(R, i, pch_gbe_tx_desc)
#घोषणा PCH_GBE_DESC_UNUSED(R) \
	((((R)->next_to_clean > (R)->next_to_use) ? 0 : (R)->count) + \
	(R)->next_to_clean - (R)->next_to_use - 1)

/* Pause packet value */
#घोषणा	PCH_GBE_PAUSE_PKT1_VALUE    0x00C28001
#घोषणा	PCH_GBE_PAUSE_PKT2_VALUE    0x00000100
#घोषणा	PCH_GBE_PAUSE_PKT4_VALUE    0x01000888
#घोषणा	PCH_GBE_PAUSE_PKT5_VALUE    0x0000FFFF


/* This defines the bits that are set in the Interrupt Mask
 * Set/Read Register.  Each bit is करोcumented below:
 *   o RXT0   = Receiver Timer Interrupt (ring 0)
 *   o TXDW   = Transmit Descriptor Written Back
 *   o RXDMT0 = Receive Descriptor Minimum Threshold hit (ring 0)
 *   o RXSEQ  = Receive Sequence Error
 *   o LSC    = Link Status Change
 */
#घोषणा PCH_GBE_INT_ENABLE_MASK ( \
	PCH_GBE_INT_RX_DMA_CMPLT |    \
	PCH_GBE_INT_RX_DSC_EMP   |    \
	PCH_GBE_INT_RX_FIFO_ERR  |    \
	PCH_GBE_INT_WOL_DET      |    \
	PCH_GBE_INT_TX_CMPLT          \
	)

#घोषणा PCH_GBE_INT_DISABLE_ALL		0

/* Macros क्रम ieee1588 */
/* 0x40 Time Synchronization Channel Control Register Bits */
#घोषणा MASTER_MODE   (1<<0)
#घोषणा SLAVE_MODE    (0)
#घोषणा V2_MODE       (1<<31)
#घोषणा CAP_MODE0     (0)
#घोषणा CAP_MODE2     (1<<17)

/* 0x44 Time Synchronization Channel Event Register Bits */
#घोषणा TX_SNAPSHOT_LOCKED (1<<0)
#घोषणा RX_SNAPSHOT_LOCKED (1<<1)

#घोषणा PTP_L4_MULTICAST_SA "01:00:5e:00:01:81"
#घोषणा PTP_L2_MULTICAST_SA "01:1b:19:00:00:00"

#घोषणा MINNOW_PHY_RESET_GPIO		13

अटल पूर्णांक pch_gbe_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक addr, पूर्णांक reg);
अटल व्योम pch_gbe_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक addr, पूर्णांक reg,
			       पूर्णांक data);
अटल व्योम pch_gbe_set_multi(काष्ठा net_device *netdev);

अटल पूर्णांक pch_ptp_match(काष्ठा sk_buff *skb, u16 uid_hi, u32 uid_lo, u16 seqid)
अणु
	u8 *data = skb->data;
	अचिन्हित पूर्णांक offset;
	u16 *hi, *id;
	u32 lo;

	अगर (ptp_classअगरy_raw(skb) == PTP_CLASS_NONE)
		वापस 0;

	offset = ETH_HLEN + IPV4_HLEN(data) + UDP_HLEN;

	अगर (skb->len < offset + OFF_PTP_SEQUENCE_ID + माप(seqid))
		वापस 0;

	hi = (u16 *)(data + offset + OFF_PTP_SOURCE_UUID);
	id = (u16 *)(data + offset + OFF_PTP_SEQUENCE_ID);

	स_नकल(&lo, &hi[1], माप(lo));

	वापस (uid_hi == *hi &&
		uid_lo == lo &&
		seqid  == *id);
पूर्ण

अटल व्योम
pch_rx_बारtamp(काष्ठा pch_gbe_adapter *adapter, काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_shared_hwtstamps *shhwtstamps;
	काष्ठा pci_dev *pdev;
	u64 ns;
	u32 hi, lo, val;
	u16 uid, seq;

	अगर (!adapter->hwts_rx_en)
		वापस;

	/* Get ieee1588's dev inक्रमmation */
	pdev = adapter->ptp_pdev;

	val = pch_ch_event_पढ़ो(pdev);

	अगर (!(val & RX_SNAPSHOT_LOCKED))
		वापस;

	lo = pch_src_uuid_lo_पढ़ो(pdev);
	hi = pch_src_uuid_hi_पढ़ो(pdev);

	uid = hi & 0xffff;
	seq = (hi >> 16) & 0xffff;

	अगर (!pch_ptp_match(skb, htons(uid), htonl(lo), htons(seq)))
		जाओ out;

	ns = pch_rx_snap_पढ़ो(pdev);

	shhwtstamps = skb_hwtstamps(skb);
	स_रखो(shhwtstamps, 0, माप(*shhwtstamps));
	shhwtstamps->hwtstamp = ns_to_kसमय(ns);
out:
	pch_ch_event_ग_लिखो(pdev, RX_SNAPSHOT_LOCKED);
पूर्ण

अटल व्योम
pch_tx_बारtamp(काष्ठा pch_gbe_adapter *adapter, काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	काष्ठा pci_dev *pdev;
	काष्ठा skb_shared_info *shtx;
	u64 ns;
	u32 cnt, val;

	shtx = skb_shinfo(skb);
	अगर (likely(!(shtx->tx_flags & SKBTX_HW_TSTAMP && adapter->hwts_tx_en)))
		वापस;

	shtx->tx_flags |= SKBTX_IN_PROGRESS;

	/* Get ieee1588's dev inक्रमmation */
	pdev = adapter->ptp_pdev;

	/*
	 * This really stinks, but we have to poll क्रम the Tx समय stamp.
	 */
	क्रम (cnt = 0; cnt < 100; cnt++) अणु
		val = pch_ch_event_पढ़ो(pdev);
		अगर (val & TX_SNAPSHOT_LOCKED)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (!(val & TX_SNAPSHOT_LOCKED)) अणु
		shtx->tx_flags &= ~SKBTX_IN_PROGRESS;
		वापस;
	पूर्ण

	ns = pch_tx_snap_पढ़ो(pdev);

	स_रखो(&shhwtstamps, 0, माप(shhwtstamps));
	shhwtstamps.hwtstamp = ns_to_kसमय(ns);
	skb_tstamp_tx(skb, &shhwtstamps);

	pch_ch_event_ग_लिखो(pdev, TX_SNAPSHOT_LOCKED);
पूर्ण

अटल पूर्णांक hwtstamp_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा hwtstamp_config cfg;
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pci_dev *pdev;
	u8 station[20];

	अगर (copy_from_user(&cfg, अगरr->अगरr_data, माप(cfg)))
		वापस -EFAULT;

	अगर (cfg.flags) /* reserved क्रम future extensions */
		वापस -EINVAL;

	/* Get ieee1588's dev inक्रमmation */
	pdev = adapter->ptp_pdev;

	अगर (cfg.tx_type != HWTSTAMP_TX_OFF && cfg.tx_type != HWTSTAMP_TX_ON)
		वापस -दुस्फल;

	चयन (cfg.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		adapter->hwts_rx_en = 0;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
		adapter->hwts_rx_en = 0;
		pch_ch_control_ग_लिखो(pdev, SLAVE_MODE | CAP_MODE0);
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		adapter->hwts_rx_en = 1;
		pch_ch_control_ग_लिखो(pdev, MASTER_MODE | CAP_MODE0);
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
		adapter->hwts_rx_en = 1;
		pch_ch_control_ग_लिखो(pdev, V2_MODE | CAP_MODE2);
		म_नकल(station, PTP_L4_MULTICAST_SA);
		pch_set_station_address(station, pdev);
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
		adapter->hwts_rx_en = 1;
		pch_ch_control_ग_लिखो(pdev, V2_MODE | CAP_MODE2);
		म_नकल(station, PTP_L2_MULTICAST_SA);
		pch_set_station_address(station, pdev);
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	adapter->hwts_tx_en = cfg.tx_type == HWTSTAMP_TX_ON;

	/* Clear out any old समय stamps. */
	pch_ch_event_ग_लिखो(pdev, TX_SNAPSHOT_LOCKED | RX_SNAPSHOT_LOCKED);

	वापस copy_to_user(अगरr->अगरr_data, &cfg, माप(cfg)) ? -EFAULT : 0;
पूर्ण

अटल अंतरभूत व्योम pch_gbe_mac_load_mac_addr(काष्ठा pch_gbe_hw *hw)
अणु
	ioग_लिखो32(0x01, &hw->reg->MAC_ADDR_LOAD);
पूर्ण

/**
 * pch_gbe_mac_पढ़ो_mac_addr - Read MAC address
 * @hw:	            Poपूर्णांकer to the HW काष्ठाure
 * Returns:
 *	0:			Successful.
 */
अटल s32 pch_gbe_mac_पढ़ो_mac_addr(काष्ठा pch_gbe_hw *hw)
अणु
	काष्ठा pch_gbe_adapter *adapter = pch_gbe_hw_to_adapter(hw);
	u32  adr1a, adr1b;

	adr1a = ioपढ़ो32(&hw->reg->mac_adr[0].high);
	adr1b = ioपढ़ो32(&hw->reg->mac_adr[0].low);

	hw->mac.addr[0] = (u8)(adr1a & 0xFF);
	hw->mac.addr[1] = (u8)((adr1a >> 8) & 0xFF);
	hw->mac.addr[2] = (u8)((adr1a >> 16) & 0xFF);
	hw->mac.addr[3] = (u8)((adr1a >> 24) & 0xFF);
	hw->mac.addr[4] = (u8)(adr1b & 0xFF);
	hw->mac.addr[5] = (u8)((adr1b >> 8) & 0xFF);

	netdev_dbg(adapter->netdev, "hw->mac.addr : %pM\n", hw->mac.addr);
	वापस 0;
पूर्ण

/**
 * pch_gbe_रुको_clr_bit - Wait to clear a bit
 * @reg:	Poपूर्णांकer of रेजिस्टर
 * @bit:	Busy bit
 */
अटल व्योम pch_gbe_रुको_clr_bit(व्योम *reg, u32 bit)
अणु
	u32 पंचांगp;

	/* रुको busy */
	पंचांगp = 1000;
	जबतक ((ioपढ़ो32(reg) & bit) && --पंचांगp)
		cpu_relax();
	अगर (!पंचांगp)
		pr_err("Error: busy bit is not cleared\n");
पूर्ण

/**
 * pch_gbe_mac_mar_set - Set MAC address रेजिस्टर
 * @hw:	    Poपूर्णांकer to the HW काष्ठाure
 * @addr:   Poपूर्णांकer to the MAC address
 * @index:  MAC address array रेजिस्टर
 */
अटल व्योम pch_gbe_mac_mar_set(काष्ठा pch_gbe_hw *hw, u8 * addr, u32 index)
अणु
	काष्ठा pch_gbe_adapter *adapter = pch_gbe_hw_to_adapter(hw);
	u32 mar_low, mar_high, adrmask;

	netdev_dbg(adapter->netdev, "index : 0x%x\n", index);

	/*
	 * HW expects these in little endian so we reverse the byte order
	 * from network order (big endian) to little endian
	 */
	mar_high = ((u32) addr[0] | ((u32) addr[1] << 8) |
		   ((u32) addr[2] << 16) | ((u32) addr[3] << 24));
	mar_low = ((u32) addr[4] | ((u32) addr[5] << 8));
	/* Stop the MAC Address of index. */
	adrmask = ioपढ़ो32(&hw->reg->ADDR_MASK);
	ioग_लिखो32((adrmask | (0x0001 << index)), &hw->reg->ADDR_MASK);
	/* रुको busy */
	pch_gbe_रुको_clr_bit(&hw->reg->ADDR_MASK, PCH_GBE_BUSY);
	/* Set the MAC address to the MAC address 1A/1B रेजिस्टर */
	ioग_लिखो32(mar_high, &hw->reg->mac_adr[index].high);
	ioग_लिखो32(mar_low, &hw->reg->mac_adr[index].low);
	/* Start the MAC address of index */
	ioग_लिखो32((adrmask & ~(0x0001 << index)), &hw->reg->ADDR_MASK);
	/* रुको busy */
	pch_gbe_रुको_clr_bit(&hw->reg->ADDR_MASK, PCH_GBE_BUSY);
पूर्ण

/**
 * pch_gbe_mac_reset_hw - Reset hardware
 * @hw:	Poपूर्णांकer to the HW काष्ठाure
 */
अटल व्योम pch_gbe_mac_reset_hw(काष्ठा pch_gbe_hw *hw)
अणु
	/* Read the MAC address. and store to the निजी data */
	pch_gbe_mac_पढ़ो_mac_addr(hw);
	ioग_लिखो32(PCH_GBE_ALL_RST, &hw->reg->RESET);
	ioग_लिखो32(PCH_GBE_MODE_GMII_ETHER, &hw->reg->MODE);
	pch_gbe_रुको_clr_bit(&hw->reg->RESET, PCH_GBE_ALL_RST);
	/* Setup the receive addresses */
	pch_gbe_mac_mar_set(hw, hw->mac.addr, 0);
	वापस;
पूर्ण

अटल व्योम pch_gbe_disable_mac_rx(काष्ठा pch_gbe_hw *hw)
अणु
	u32 rctl;
	/* Disables Receive MAC */
	rctl = ioपढ़ो32(&hw->reg->MAC_RX_EN);
	ioग_लिखो32((rctl & ~PCH_GBE_MRE_MAC_RX_EN), &hw->reg->MAC_RX_EN);
पूर्ण

अटल व्योम pch_gbe_enable_mac_rx(काष्ठा pch_gbe_hw *hw)
अणु
	u32 rctl;
	/* Enables Receive MAC */
	rctl = ioपढ़ो32(&hw->reg->MAC_RX_EN);
	ioग_लिखो32((rctl | PCH_GBE_MRE_MAC_RX_EN), &hw->reg->MAC_RX_EN);
पूर्ण

/**
 * pch_gbe_mac_init_rx_addrs - Initialize receive address's
 * @hw:	Poपूर्णांकer to the HW काष्ठाure
 * @mar_count: Receive address रेजिस्टरs
 */
अटल व्योम pch_gbe_mac_init_rx_addrs(काष्ठा pch_gbe_hw *hw, u16 mar_count)
अणु
	u32 i;

	/* Setup the receive address */
	pch_gbe_mac_mar_set(hw, hw->mac.addr, 0);

	/* Zero out the other receive addresses */
	क्रम (i = 1; i < mar_count; i++) अणु
		ioग_लिखो32(0, &hw->reg->mac_adr[i].high);
		ioग_लिखो32(0, &hw->reg->mac_adr[i].low);
	पूर्ण
	ioग_लिखो32(0xFFFE, &hw->reg->ADDR_MASK);
	/* रुको busy */
	pch_gbe_रुको_clr_bit(&hw->reg->ADDR_MASK, PCH_GBE_BUSY);
पूर्ण

/**
 * pch_gbe_mac_क्रमce_mac_fc - Force the MAC's flow control settings
 * @hw:	            Poपूर्णांकer to the HW काष्ठाure
 * Returns:
 *	0:			Successful.
 *	Negative value:		Failed.
 */
s32 pch_gbe_mac_क्रमce_mac_fc(काष्ठा pch_gbe_hw *hw)
अणु
	काष्ठा pch_gbe_adapter *adapter = pch_gbe_hw_to_adapter(hw);
	काष्ठा pch_gbe_mac_info *mac = &hw->mac;
	u32 rx_fctrl;

	netdev_dbg(adapter->netdev, "mac->fc = %u\n", mac->fc);

	rx_fctrl = ioपढ़ो32(&hw->reg->RX_FCTRL);

	चयन (mac->fc) अणु
	हाल PCH_GBE_FC_NONE:
		rx_fctrl &= ~PCH_GBE_FL_CTRL_EN;
		mac->tx_fc_enable = false;
		अवरोध;
	हाल PCH_GBE_FC_RX_PAUSE:
		rx_fctrl |= PCH_GBE_FL_CTRL_EN;
		mac->tx_fc_enable = false;
		अवरोध;
	हाल PCH_GBE_FC_TX_PAUSE:
		rx_fctrl &= ~PCH_GBE_FL_CTRL_EN;
		mac->tx_fc_enable = true;
		अवरोध;
	हाल PCH_GBE_FC_FULL:
		rx_fctrl |= PCH_GBE_FL_CTRL_EN;
		mac->tx_fc_enable = true;
		अवरोध;
	शेष:
		netdev_err(adapter->netdev,
			   "Flow control param set incorrectly\n");
		वापस -EINVAL;
	पूर्ण
	अगर (mac->link_duplex == DUPLEX_HALF)
		rx_fctrl &= ~PCH_GBE_FL_CTRL_EN;
	ioग_लिखो32(rx_fctrl, &hw->reg->RX_FCTRL);
	netdev_dbg(adapter->netdev,
		   "RX_FCTRL reg : 0x%08x  mac->tx_fc_enable : %d\n",
		   ioपढ़ो32(&hw->reg->RX_FCTRL), mac->tx_fc_enable);
	वापस 0;
पूर्ण

/**
 * pch_gbe_mac_set_wol_event - Set wake-on-lan event
 * @hw:     Poपूर्णांकer to the HW काष्ठाure
 * @wu_evt: Wake up event
 */
अटल व्योम pch_gbe_mac_set_wol_event(काष्ठा pch_gbe_hw *hw, u32 wu_evt)
अणु
	काष्ठा pch_gbe_adapter *adapter = pch_gbe_hw_to_adapter(hw);
	u32 addr_mask;

	netdev_dbg(adapter->netdev, "wu_evt : 0x%08x  ADDR_MASK reg : 0x%08x\n",
		   wu_evt, ioपढ़ो32(&hw->reg->ADDR_MASK));

	अगर (wu_evt) अणु
		/* Set Wake-On-Lan address mask */
		addr_mask = ioपढ़ो32(&hw->reg->ADDR_MASK);
		ioग_लिखो32(addr_mask, &hw->reg->WOL_ADDR_MASK);
		/* रुको busy */
		pch_gbe_रुको_clr_bit(&hw->reg->WOL_ADDR_MASK, PCH_GBE_WLA_BUSY);
		ioग_लिखो32(0, &hw->reg->WOL_ST);
		ioग_लिखो32((wu_evt | PCH_GBE_WLC_WOL_MODE), &hw->reg->WOL_CTRL);
		ioग_लिखो32(0x02, &hw->reg->TCPIP_ACC);
		ioग_लिखो32(PCH_GBE_INT_ENABLE_MASK, &hw->reg->INT_EN);
	पूर्ण अन्यथा अणु
		ioग_लिखो32(0, &hw->reg->WOL_CTRL);
		ioग_लिखो32(0, &hw->reg->WOL_ST);
	पूर्ण
	वापस;
पूर्ण

/**
 * pch_gbe_mac_ctrl_miim - Control MIIM पूर्णांकerface
 * @hw:   Poपूर्णांकer to the HW काष्ठाure
 * @addr: Address of PHY
 * @dir:  Operetion. (Write or Read)
 * @reg:  Access रेजिस्टर of PHY
 * @data: Write data.
 *
 * Returns: Read date.
 */
u16 pch_gbe_mac_ctrl_miim(काष्ठा pch_gbe_hw *hw, u32 addr, u32 dir, u32 reg,
			u16 data)
अणु
	काष्ठा pch_gbe_adapter *adapter = pch_gbe_hw_to_adapter(hw);
	u32 data_out = 0;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->miim_lock, flags);

	क्रम (i = 100; i; --i) अणु
		अगर ((ioपढ़ो32(&hw->reg->MIIM) & PCH_GBE_MIIM_OPER_READY))
			अवरोध;
		udelay(20);
	पूर्ण
	अगर (i == 0) अणु
		netdev_err(adapter->netdev, "pch-gbe.miim won't go Ready\n");
		spin_unlock_irqrestore(&hw->miim_lock, flags);
		वापस 0;	/* No way to indicate समयout error */
	पूर्ण
	ioग_लिखो32(((reg << PCH_GBE_MIIM_REG_ADDR_SHIFT) |
		  (addr << PCH_GBE_MIIM_PHY_ADDR_SHIFT) |
		  dir | data), &hw->reg->MIIM);
	क्रम (i = 0; i < 100; i++) अणु
		udelay(20);
		data_out = ioपढ़ो32(&hw->reg->MIIM);
		अगर ((data_out & PCH_GBE_MIIM_OPER_READY))
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&hw->miim_lock, flags);

	netdev_dbg(adapter->netdev, "PHY %s: reg=%d, data=0x%04X\n",
		   dir == PCH_GBE_MIIM_OPER_READ ? "READ" : "WRITE", reg,
		   dir == PCH_GBE_MIIM_OPER_READ ? data_out : data);
	वापस (u16) data_out;
पूर्ण

/**
 * pch_gbe_mac_set_छोड़ो_packet - Set छोड़ो packet
 * @hw:   Poपूर्णांकer to the HW काष्ठाure
 */
अटल व्योम pch_gbe_mac_set_छोड़ो_packet(काष्ठा pch_gbe_hw *hw)
अणु
	काष्ठा pch_gbe_adapter *adapter = pch_gbe_hw_to_adapter(hw);
	अचिन्हित दीर्घ पंचांगp2, पंचांगp3;

	/* Set Pause packet */
	पंचांगp2 = hw->mac.addr[1];
	पंचांगp2 = (पंचांगp2 << 8) | hw->mac.addr[0];
	पंचांगp2 = PCH_GBE_PAUSE_PKT2_VALUE | (पंचांगp2 << 16);

	पंचांगp3 = hw->mac.addr[5];
	पंचांगp3 = (पंचांगp3 << 8) | hw->mac.addr[4];
	पंचांगp3 = (पंचांगp3 << 8) | hw->mac.addr[3];
	पंचांगp3 = (पंचांगp3 << 8) | hw->mac.addr[2];

	ioग_लिखो32(PCH_GBE_PAUSE_PKT1_VALUE, &hw->reg->PAUSE_PKT1);
	ioग_लिखो32(पंचांगp2, &hw->reg->PAUSE_PKT2);
	ioग_लिखो32(पंचांगp3, &hw->reg->PAUSE_PKT3);
	ioग_लिखो32(PCH_GBE_PAUSE_PKT4_VALUE, &hw->reg->PAUSE_PKT4);
	ioग_लिखो32(PCH_GBE_PAUSE_PKT5_VALUE, &hw->reg->PAUSE_PKT5);

	/* Transmit Pause Packet */
	ioग_लिखो32(PCH_GBE_PS_PKT_RQ, &hw->reg->PAUSE_REQ);

	netdev_dbg(adapter->netdev,
		   "PAUSE_PKT1-5 reg : 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   ioपढ़ो32(&hw->reg->PAUSE_PKT1),
		   ioपढ़ो32(&hw->reg->PAUSE_PKT2),
		   ioपढ़ो32(&hw->reg->PAUSE_PKT3),
		   ioपढ़ो32(&hw->reg->PAUSE_PKT4),
		   ioपढ़ो32(&hw->reg->PAUSE_PKT5));

	वापस;
पूर्ण


/**
 * pch_gbe_alloc_queues - Allocate memory क्रम all rings
 * @adapter:  Board निजी काष्ठाure to initialize
 * Returns:
 *	0:	Successfully
 *	Negative value:	Failed
 */
अटल पूर्णांक pch_gbe_alloc_queues(काष्ठा pch_gbe_adapter *adapter)
अणु
	adapter->tx_ring = devm_kzalloc(&adapter->pdev->dev,
					माप(*adapter->tx_ring), GFP_KERNEL);
	अगर (!adapter->tx_ring)
		वापस -ENOMEM;

	adapter->rx_ring = devm_kzalloc(&adapter->pdev->dev,
					माप(*adapter->rx_ring), GFP_KERNEL);
	अगर (!adapter->rx_ring)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/**
 * pch_gbe_init_stats - Initialize status
 * @adapter:  Board निजी काष्ठाure to initialize
 */
अटल व्योम pch_gbe_init_stats(काष्ठा pch_gbe_adapter *adapter)
अणु
	स_रखो(&adapter->stats, 0, माप(adapter->stats));
	वापस;
पूर्ण

/**
 * pch_gbe_init_phy - Initialize PHY
 * @adapter:  Board निजी काष्ठाure to initialize
 * Returns:
 *	0:	Successfully
 *	Negative value:	Failed
 */
अटल पूर्णांक pch_gbe_init_phy(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	u32 addr;
	u16 bmcr, stat;

	/* Discover phy addr by searching addrs in order अणु1,0,2,..., 31पूर्ण */
	क्रम (addr = 0; addr < PCH_GBE_PHY_REGS_LEN; addr++) अणु
		adapter->mii.phy_id = (addr == 0) ? 1 : (addr == 1) ? 0 : addr;
		bmcr = pch_gbe_mdio_पढ़ो(netdev, adapter->mii.phy_id, MII_BMCR);
		stat = pch_gbe_mdio_पढ़ो(netdev, adapter->mii.phy_id, MII_BMSR);
		stat = pch_gbe_mdio_पढ़ो(netdev, adapter->mii.phy_id, MII_BMSR);
		अगर (!((bmcr == 0xFFFF) || ((stat == 0) && (bmcr == 0))))
			अवरोध;
	पूर्ण
	adapter->hw.phy.addr = adapter->mii.phy_id;
	netdev_dbg(netdev, "phy_addr = %d\n", adapter->mii.phy_id);
	अगर (addr == PCH_GBE_PHY_REGS_LEN)
		वापस -EAGAIN;
	/* Selected the phy and isolate the rest */
	क्रम (addr = 0; addr < PCH_GBE_PHY_REGS_LEN; addr++) अणु
		अगर (addr != adapter->mii.phy_id) अणु
			pch_gbe_mdio_ग_लिखो(netdev, addr, MII_BMCR,
					   BMCR_ISOLATE);
		पूर्ण अन्यथा अणु
			bmcr = pch_gbe_mdio_पढ़ो(netdev, addr, MII_BMCR);
			pch_gbe_mdio_ग_लिखो(netdev, addr, MII_BMCR,
					   bmcr & ~BMCR_ISOLATE);
		पूर्ण
	पूर्ण

	/* MII setup */
	adapter->mii.phy_id_mask = 0x1F;
	adapter->mii.reg_num_mask = 0x1F;
	adapter->mii.dev = adapter->netdev;
	adapter->mii.mdio_पढ़ो = pch_gbe_mdio_पढ़ो;
	adapter->mii.mdio_ग_लिखो = pch_gbe_mdio_ग_लिखो;
	adapter->mii.supports_gmii = mii_check_gmii_support(&adapter->mii);
	वापस 0;
पूर्ण

/**
 * pch_gbe_mdio_पढ़ो - The पढ़ो function क्रम mii
 * @netdev: Network पूर्णांकerface device काष्ठाure
 * @addr:   Phy ID
 * @reg:    Access location
 * Returns:
 *	0:	Successfully
 *	Negative value:	Failed
 */
अटल पूर्णांक pch_gbe_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक addr, पूर्णांक reg)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_hw *hw = &adapter->hw;

	वापस pch_gbe_mac_ctrl_miim(hw, addr, PCH_GBE_HAL_MIIM_READ, reg,
				     (u16) 0);
पूर्ण

/**
 * pch_gbe_mdio_ग_लिखो - The ग_लिखो function क्रम mii
 * @netdev: Network पूर्णांकerface device काष्ठाure
 * @addr:   Phy ID (not used)
 * @reg:    Access location
 * @data:   Write data
 */
अटल व्योम pch_gbe_mdio_ग_लिखो(काष्ठा net_device *netdev,
			       पूर्णांक addr, पूर्णांक reg, पूर्णांक data)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_hw *hw = &adapter->hw;

	pch_gbe_mac_ctrl_miim(hw, addr, PCH_GBE_HAL_MIIM_WRITE, reg, data);
पूर्ण

/**
 * pch_gbe_reset_task - Reset processing at the समय of transmission समयout
 * @work:  Poपूर्णांकer of board निजी काष्ठाure
 */
अटल व्योम pch_gbe_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pch_gbe_adapter *adapter;
	adapter = container_of(work, काष्ठा pch_gbe_adapter, reset_task);

	rtnl_lock();
	pch_gbe_reinit_locked(adapter);
	rtnl_unlock();
पूर्ण

/**
 * pch_gbe_reinit_locked- Re-initialization
 * @adapter:  Board निजी काष्ठाure
 */
व्योम pch_gbe_reinit_locked(काष्ठा pch_gbe_adapter *adapter)
अणु
	pch_gbe_करोwn(adapter);
	pch_gbe_up(adapter);
पूर्ण

/**
 * pch_gbe_reset - Reset GbE
 * @adapter:  Board निजी काष्ठाure
 */
व्योम pch_gbe_reset(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	s32 ret_val;

	pch_gbe_mac_reset_hw(hw);
	/* reprogram multicast address रेजिस्टर after reset */
	pch_gbe_set_multi(netdev);
	/* Setup the receive address. */
	pch_gbe_mac_init_rx_addrs(hw, PCH_GBE_MAR_ENTRIES);

	ret_val = pch_gbe_phy_get_id(hw);
	अगर (ret_val) अणु
		netdev_err(adapter->netdev, "pch_gbe_phy_get_id error\n");
		वापस;
	पूर्ण
	pch_gbe_phy_init_setting(hw);
	/* Setup Mac पूर्णांकerface option RGMII */
	pch_gbe_phy_set_rgmii(hw);
पूर्ण

/**
 * pch_gbe_मुक्त_irq - Free an पूर्णांकerrupt
 * @adapter:  Board निजी काष्ठाure
 */
अटल व्योम pch_gbe_मुक्त_irq(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	मुक्त_irq(adapter->irq, netdev);
	pci_मुक्त_irq_vectors(adapter->pdev);
पूर्ण

/**
 * pch_gbe_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 * @adapter:  Board निजी काष्ठाure
 */
अटल व्योम pch_gbe_irq_disable(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा pch_gbe_hw *hw = &adapter->hw;

	atomic_inc(&adapter->irq_sem);
	ioग_लिखो32(0, &hw->reg->INT_EN);
	ioपढ़ो32(&hw->reg->INT_ST);
	synchronize_irq(adapter->irq);

	netdev_dbg(adapter->netdev, "INT_EN reg : 0x%08x\n",
		   ioपढ़ो32(&hw->reg->INT_EN));
पूर्ण

/**
 * pch_gbe_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 * @adapter:  Board निजी काष्ठाure
 */
अटल व्योम pch_gbe_irq_enable(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा pch_gbe_hw *hw = &adapter->hw;

	अगर (likely(atomic_dec_and_test(&adapter->irq_sem)))
		ioग_लिखो32(PCH_GBE_INT_ENABLE_MASK, &hw->reg->INT_EN);
	ioपढ़ो32(&hw->reg->INT_ST);
	netdev_dbg(adapter->netdev, "INT_EN reg : 0x%08x\n",
		   ioपढ़ो32(&hw->reg->INT_EN));
पूर्ण



/**
 * pch_gbe_setup_tctl - configure the Transmit control रेजिस्टरs
 * @adapter:  Board निजी काष्ठाure
 */
अटल व्योम pch_gbe_setup_tctl(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	u32 tx_mode, tcpip;

	tx_mode = PCH_GBE_TM_LONG_PKT |
		PCH_GBE_TM_ST_AND_FD |
		PCH_GBE_TM_SHORT_PKT |
		PCH_GBE_TM_TH_TX_STRT_8 |
		PCH_GBE_TM_TH_ALM_EMP_4 | PCH_GBE_TM_TH_ALM_FULL_8;

	ioग_लिखो32(tx_mode, &hw->reg->TX_MODE);

	tcpip = ioपढ़ो32(&hw->reg->TCPIP_ACC);
	tcpip |= PCH_GBE_TX_TCPIPACC_EN;
	ioग_लिखो32(tcpip, &hw->reg->TCPIP_ACC);
	वापस;
पूर्ण

/**
 * pch_gbe_configure_tx - Configure Transmit Unit after Reset
 * @adapter:  Board निजी काष्ठाure
 */
अटल व्योम pch_gbe_configure_tx(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	u32 tdba, tdlen, dctrl;

	netdev_dbg(adapter->netdev, "dma addr = 0x%08llx  size = 0x%08x\n",
		   (अचिन्हित दीर्घ दीर्घ)adapter->tx_ring->dma,
		   adapter->tx_ring->size);

	/* Setup the HW Tx Head and Tail descriptor poपूर्णांकers */
	tdba = adapter->tx_ring->dma;
	tdlen = adapter->tx_ring->size - 0x10;
	ioग_लिखो32(tdba, &hw->reg->TX_DSC_BASE);
	ioग_लिखो32(tdlen, &hw->reg->TX_DSC_SIZE);
	ioग_लिखो32(tdba, &hw->reg->TX_DSC_SW_P);

	/* Enables Transmission DMA */
	dctrl = ioपढ़ो32(&hw->reg->DMA_CTRL);
	dctrl |= PCH_GBE_TX_DMA_EN;
	ioग_लिखो32(dctrl, &hw->reg->DMA_CTRL);
पूर्ण

/**
 * pch_gbe_setup_rctl - Configure the receive control रेजिस्टरs
 * @adapter:  Board निजी काष्ठाure
 */
अटल व्योम pch_gbe_setup_rctl(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	u32 rx_mode, tcpip;

	rx_mode = PCH_GBE_ADD_FIL_EN | PCH_GBE_MLT_FIL_EN |
	PCH_GBE_RH_ALM_EMP_4 | PCH_GBE_RH_ALM_FULL_4 | PCH_GBE_RH_RD_TRG_8;

	ioग_लिखो32(rx_mode, &hw->reg->RX_MODE);

	tcpip = ioपढ़ो32(&hw->reg->TCPIP_ACC);

	tcpip |= PCH_GBE_RX_TCPIPACC_OFF;
	tcpip &= ~PCH_GBE_RX_TCPIPACC_EN;
	ioग_लिखो32(tcpip, &hw->reg->TCPIP_ACC);
	वापस;
पूर्ण

/**
 * pch_gbe_configure_rx - Configure Receive Unit after Reset
 * @adapter:  Board निजी काष्ठाure
 */
अटल व्योम pch_gbe_configure_rx(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	u32 rdba, rdlen, rxdma;

	netdev_dbg(adapter->netdev, "dma adr = 0x%08llx  size = 0x%08x\n",
		   (अचिन्हित दीर्घ दीर्घ)adapter->rx_ring->dma,
		   adapter->rx_ring->size);

	pch_gbe_mac_क्रमce_mac_fc(hw);

	pch_gbe_disable_mac_rx(hw);

	/* Disables Receive DMA */
	rxdma = ioपढ़ो32(&hw->reg->DMA_CTRL);
	rxdma &= ~PCH_GBE_RX_DMA_EN;
	ioग_लिखो32(rxdma, &hw->reg->DMA_CTRL);

	netdev_dbg(adapter->netdev,
		   "MAC_RX_EN reg = 0x%08x  DMA_CTRL reg = 0x%08x\n",
		   ioपढ़ो32(&hw->reg->MAC_RX_EN),
		   ioपढ़ो32(&hw->reg->DMA_CTRL));

	/* Setup the HW Rx Head and Tail Descriptor Poपूर्णांकers and
	 * the Base and Length of the Rx Descriptor Ring */
	rdba = adapter->rx_ring->dma;
	rdlen = adapter->rx_ring->size - 0x10;
	ioग_लिखो32(rdba, &hw->reg->RX_DSC_BASE);
	ioग_लिखो32(rdlen, &hw->reg->RX_DSC_SIZE);
	ioग_लिखो32((rdba + rdlen), &hw->reg->RX_DSC_SW_P);
पूर्ण

/**
 * pch_gbe_unmap_and_मुक्त_tx_resource - Unmap and मुक्त tx socket buffer
 * @adapter:     Board निजी काष्ठाure
 * @buffer_info: Buffer inक्रमmation काष्ठाure
 */
अटल व्योम pch_gbe_unmap_and_मुक्त_tx_resource(
	काष्ठा pch_gbe_adapter *adapter, काष्ठा pch_gbe_buffer *buffer_info)
अणु
	अगर (buffer_info->mapped) अणु
		dma_unmap_single(&adapter->pdev->dev, buffer_info->dma,
				 buffer_info->length, DMA_TO_DEVICE);
		buffer_info->mapped = false;
	पूर्ण
	अगर (buffer_info->skb) अणु
		dev_kमुक्त_skb_any(buffer_info->skb);
		buffer_info->skb = शून्य;
	पूर्ण
पूर्ण

/**
 * pch_gbe_unmap_and_मुक्त_rx_resource - Unmap and मुक्त rx socket buffer
 * @adapter:      Board निजी काष्ठाure
 * @buffer_info:  Buffer inक्रमmation काष्ठाure
 */
अटल व्योम pch_gbe_unmap_and_मुक्त_rx_resource(
					काष्ठा pch_gbe_adapter *adapter,
					काष्ठा pch_gbe_buffer *buffer_info)
अणु
	अगर (buffer_info->mapped) अणु
		dma_unmap_single(&adapter->pdev->dev, buffer_info->dma,
				 buffer_info->length, DMA_FROM_DEVICE);
		buffer_info->mapped = false;
	पूर्ण
	अगर (buffer_info->skb) अणु
		dev_kमुक्त_skb_any(buffer_info->skb);
		buffer_info->skb = शून्य;
	पूर्ण
पूर्ण

/**
 * pch_gbe_clean_tx_ring - Free Tx Buffers
 * @adapter:  Board निजी काष्ठाure
 * @tx_ring:  Ring to be cleaned
 */
अटल व्योम pch_gbe_clean_tx_ring(काष्ठा pch_gbe_adapter *adapter,
				   काष्ठा pch_gbe_tx_ring *tx_ring)
अणु
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	काष्ठा pch_gbe_buffer *buffer_info;
	अचिन्हित दीर्घ size;
	अचिन्हित पूर्णांक i;

	/* Free all the Tx ring sk_buffs */
	क्रम (i = 0; i < tx_ring->count; i++) अणु
		buffer_info = &tx_ring->buffer_info[i];
		pch_gbe_unmap_and_मुक्त_tx_resource(adapter, buffer_info);
	पूर्ण
	netdev_dbg(adapter->netdev,
		   "call pch_gbe_unmap_and_free_tx_resource() %d count\n", i);

	size = (अचिन्हित दीर्घ)माप(काष्ठा pch_gbe_buffer) * tx_ring->count;
	स_रखो(tx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */
	स_रखो(tx_ring->desc, 0, tx_ring->size);
	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
	ioग_लिखो32(tx_ring->dma, &hw->reg->TX_DSC_HW_P);
	ioग_लिखो32((tx_ring->size - 0x10), &hw->reg->TX_DSC_SIZE);
पूर्ण

/**
 * pch_gbe_clean_rx_ring - Free Rx Buffers
 * @adapter:  Board निजी काष्ठाure
 * @rx_ring:  Ring to मुक्त buffers from
 */
अटल व्योम
pch_gbe_clean_rx_ring(काष्ठा pch_gbe_adapter *adapter,
		      काष्ठा pch_gbe_rx_ring *rx_ring)
अणु
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	काष्ठा pch_gbe_buffer *buffer_info;
	अचिन्हित दीर्घ size;
	अचिन्हित पूर्णांक i;

	/* Free all the Rx ring sk_buffs */
	क्रम (i = 0; i < rx_ring->count; i++) अणु
		buffer_info = &rx_ring->buffer_info[i];
		pch_gbe_unmap_and_मुक्त_rx_resource(adapter, buffer_info);
	पूर्ण
	netdev_dbg(adapter->netdev,
		   "call pch_gbe_unmap_and_free_rx_resource() %d count\n", i);
	size = (अचिन्हित दीर्घ)माप(काष्ठा pch_gbe_buffer) * rx_ring->count;
	स_रखो(rx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */
	स_रखो(rx_ring->desc, 0, rx_ring->size);
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
	ioग_लिखो32(rx_ring->dma, &hw->reg->RX_DSC_HW_P);
	ioग_लिखो32((rx_ring->size - 0x10), &hw->reg->RX_DSC_SIZE);
पूर्ण

अटल व्योम pch_gbe_set_rgmii_ctrl(काष्ठा pch_gbe_adapter *adapter, u16 speed,
				    u16 duplex)
अणु
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ rgmii = 0;

	/* Set the RGMII control. */
	चयन (speed) अणु
	हाल SPEED_10:
		rgmii = (PCH_GBE_RGMII_RATE_2_5M |
			 PCH_GBE_MAC_RGMII_CTRL_SETTING);
		अवरोध;
	हाल SPEED_100:
		rgmii = (PCH_GBE_RGMII_RATE_25M |
			 PCH_GBE_MAC_RGMII_CTRL_SETTING);
		अवरोध;
	हाल SPEED_1000:
		rgmii = (PCH_GBE_RGMII_RATE_125M |
			 PCH_GBE_MAC_RGMII_CTRL_SETTING);
		अवरोध;
	पूर्ण
	ioग_लिखो32(rgmii, &hw->reg->RGMII_CTRL);
पूर्ण
अटल व्योम pch_gbe_set_mode(काष्ठा pch_gbe_adapter *adapter, u16 speed,
			      u16 duplex)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ mode = 0;

	/* Set the communication mode */
	चयन (speed) अणु
	हाल SPEED_10:
		mode = PCH_GBE_MODE_MII_ETHER;
		netdev->tx_queue_len = 10;
		अवरोध;
	हाल SPEED_100:
		mode = PCH_GBE_MODE_MII_ETHER;
		netdev->tx_queue_len = 100;
		अवरोध;
	हाल SPEED_1000:
		mode = PCH_GBE_MODE_GMII_ETHER;
		अवरोध;
	पूर्ण
	अगर (duplex == DUPLEX_FULL)
		mode |= PCH_GBE_MODE_FULL_DUPLEX;
	अन्यथा
		mode |= PCH_GBE_MODE_HALF_DUPLEX;
	ioग_लिखो32(mode, &hw->reg->MODE);
पूर्ण

/**
 * pch_gbe_watchकरोg - Watchकरोg process
 * @t:  समयr list containing a Board निजी काष्ठाure
 */
अटल व्योम pch_gbe_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा pch_gbe_adapter *adapter = from_समयr(adapter, t,
						     watchकरोg_समयr);
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pch_gbe_hw *hw = &adapter->hw;

	netdev_dbg(netdev, "right now = %ld\n", jअगरfies);

	pch_gbe_update_stats(adapter);
	अगर ((mii_link_ok(&adapter->mii)) && (!netअगर_carrier_ok(netdev))) अणु
		काष्ठा ethtool_cmd cmd = अणु .cmd = ETHTOOL_GSET पूर्ण;
		netdev->tx_queue_len = adapter->tx_queue_len;
		/* mii library handles link मुख्यtenance tasks */
		अगर (mii_ethtool_gset(&adapter->mii, &cmd)) अणु
			netdev_err(netdev, "ethtool get setting Error\n");
			mod_समयr(&adapter->watchकरोg_समयr,
				  round_jअगरfies(jअगरfies +
						PCH_GBE_WATCHDOG_PERIOD));
			वापस;
		पूर्ण
		hw->mac.link_speed = ethtool_cmd_speed(&cmd);
		hw->mac.link_duplex = cmd.duplex;
		/* Set the RGMII control. */
		pch_gbe_set_rgmii_ctrl(adapter, hw->mac.link_speed,
						hw->mac.link_duplex);
		/* Set the communication mode */
		pch_gbe_set_mode(adapter, hw->mac.link_speed,
				 hw->mac.link_duplex);
		netdev_dbg(netdev,
			   "Link is Up %d Mbps %s-Duplex\n",
			   hw->mac.link_speed,
			   cmd.duplex == DUPLEX_FULL ? "Full" : "Half");
		netअगर_carrier_on(netdev);
		netअगर_wake_queue(netdev);
	पूर्ण अन्यथा अगर ((!mii_link_ok(&adapter->mii)) &&
		   (netअगर_carrier_ok(netdev))) अणु
		netdev_dbg(netdev, "NIC Link is Down\n");
		hw->mac.link_speed = SPEED_10;
		hw->mac.link_duplex = DUPLEX_HALF;
		netअगर_carrier_off(netdev);
		netअगर_stop_queue(netdev);
	पूर्ण
	mod_समयr(&adapter->watchकरोg_समयr,
		  round_jअगरfies(jअगरfies + PCH_GBE_WATCHDOG_PERIOD));
पूर्ण

/**
 * pch_gbe_tx_queue - Carry out queuing of the transmission data
 * @adapter:  Board निजी काष्ठाure
 * @tx_ring:  Tx descriptor ring काष्ठाure
 * @skb:      Sockt buffer काष्ठाure
 */
अटल व्योम pch_gbe_tx_queue(काष्ठा pch_gbe_adapter *adapter,
			      काष्ठा pch_gbe_tx_ring *tx_ring,
			      काष्ठा sk_buff *skb)
अणु
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	काष्ठा pch_gbe_tx_desc *tx_desc;
	काष्ठा pch_gbe_buffer *buffer_info;
	काष्ठा sk_buff *पंचांगp_skb;
	अचिन्हित पूर्णांक frame_ctrl;
	अचिन्हित पूर्णांक ring_num;

	/*-- Set frame control --*/
	frame_ctrl = 0;
	अगर (unlikely(skb->len < PCH_GBE_SHORT_PKT))
		frame_ctrl |= PCH_GBE_TXD_CTRL_APAD;
	अगर (skb->ip_summed == CHECKSUM_NONE)
		frame_ctrl |= PCH_GBE_TXD_CTRL_TCPIP_ACC_OFF;

	/* Perक्रमms checksum processing */
	/*
	 * It is because the hardware accelerator करोes not support a checksum,
	 * when the received data size is less than 64 bytes.
	 */
	अगर (skb->len < PCH_GBE_SHORT_PKT && skb->ip_summed != CHECKSUM_NONE) अणु
		frame_ctrl |= PCH_GBE_TXD_CTRL_APAD |
			      PCH_GBE_TXD_CTRL_TCPIP_ACC_OFF;
		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			काष्ठा iphdr *iph = ip_hdr(skb);
			अचिन्हित पूर्णांक offset;
			offset = skb_transport_offset(skb);
			अगर (iph->protocol == IPPROTO_TCP) अणु
				skb->csum = 0;
				tcp_hdr(skb)->check = 0;
				skb->csum = skb_checksum(skb, offset,
							 skb->len - offset, 0);
				tcp_hdr(skb)->check =
					csum_tcpudp_magic(iph->saddr,
							  iph->daddr,
							  skb->len - offset,
							  IPPROTO_TCP,
							  skb->csum);
			पूर्ण अन्यथा अगर (iph->protocol == IPPROTO_UDP) अणु
				skb->csum = 0;
				udp_hdr(skb)->check = 0;
				skb->csum =
					skb_checksum(skb, offset,
						     skb->len - offset, 0);
				udp_hdr(skb)->check =
					csum_tcpudp_magic(iph->saddr,
							  iph->daddr,
							  skb->len - offset,
							  IPPROTO_UDP,
							  skb->csum);
			पूर्ण
		पूर्ण
	पूर्ण

	ring_num = tx_ring->next_to_use;
	अगर (unlikely((ring_num + 1) == tx_ring->count))
		tx_ring->next_to_use = 0;
	अन्यथा
		tx_ring->next_to_use = ring_num + 1;


	buffer_info = &tx_ring->buffer_info[ring_num];
	पंचांगp_skb = buffer_info->skb;

	/* [Header:14][payload] ---> [Header:14][padकरोng:2][payload]    */
	स_नकल(पंचांगp_skb->data, skb->data, ETH_HLEN);
	पंचांगp_skb->data[ETH_HLEN] = 0x00;
	पंचांगp_skb->data[ETH_HLEN + 1] = 0x00;
	पंचांगp_skb->len = skb->len;
	स_नकल(&पंचांगp_skb->data[ETH_HLEN + 2], &skb->data[ETH_HLEN],
	       (skb->len - ETH_HLEN));
	/*-- Set Buffer inक्रमmation --*/
	buffer_info->length = पंचांगp_skb->len;
	buffer_info->dma = dma_map_single(&adapter->pdev->dev, पंचांगp_skb->data,
					  buffer_info->length,
					  DMA_TO_DEVICE);
	अगर (dma_mapping_error(&adapter->pdev->dev, buffer_info->dma)) अणु
		netdev_err(adapter->netdev, "TX DMA map failed\n");
		buffer_info->dma = 0;
		buffer_info->समय_stamp = 0;
		tx_ring->next_to_use = ring_num;
		वापस;
	पूर्ण
	buffer_info->mapped = true;
	buffer_info->समय_stamp = jअगरfies;

	/*-- Set Tx descriptor --*/
	tx_desc = PCH_GBE_TX_DESC(*tx_ring, ring_num);
	tx_desc->buffer_addr = (buffer_info->dma);
	tx_desc->length = (पंचांगp_skb->len);
	tx_desc->tx_words_eob = ((पंचांगp_skb->len + 3));
	tx_desc->tx_frame_ctrl = (frame_ctrl);
	tx_desc->gbec_status = (DSC_INIT16);

	अगर (unlikely(++ring_num == tx_ring->count))
		ring_num = 0;

	/* Update software poपूर्णांकer of TX descriptor */
	ioग_लिखो32(tx_ring->dma +
		  (पूर्णांक)माप(काष्ठा pch_gbe_tx_desc) * ring_num,
		  &hw->reg->TX_DSC_SW_P);

	pch_tx_बारtamp(adapter, skb);

	dev_kमुक्त_skb_any(skb);
पूर्ण

/**
 * pch_gbe_update_stats - Update the board statistics counters
 * @adapter:  Board निजी काष्ठाure
 */
व्योम pch_gbe_update_stats(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा pch_gbe_hw_stats *stats = &adapter->stats;
	अचिन्हित दीर्घ flags;

	/*
	 * Prevent stats update जबतक adapter is being reset, or अगर the pci
	 * connection is करोwn.
	 */
	अगर ((pdev->error_state) && (pdev->error_state != pci_channel_io_normal))
		वापस;

	spin_lock_irqsave(&adapter->stats_lock, flags);

	/* Update device status "adapter->stats" */
	stats->rx_errors = stats->rx_crc_errors + stats->rx_frame_errors;
	stats->tx_errors = stats->tx_length_errors +
	    stats->tx_पातed_errors +
	    stats->tx_carrier_errors + stats->tx_समयout_count;

	/* Update network device status "adapter->net_stats" */
	netdev->stats.rx_packets = stats->rx_packets;
	netdev->stats.rx_bytes = stats->rx_bytes;
	netdev->stats.rx_dropped = stats->rx_dropped;
	netdev->stats.tx_packets = stats->tx_packets;
	netdev->stats.tx_bytes = stats->tx_bytes;
	netdev->stats.tx_dropped = stats->tx_dropped;
	/* Fill out the OS statistics काष्ठाure */
	netdev->stats.multicast = stats->multicast;
	netdev->stats.collisions = stats->collisions;
	/* Rx Errors */
	netdev->stats.rx_errors = stats->rx_errors;
	netdev->stats.rx_crc_errors = stats->rx_crc_errors;
	netdev->stats.rx_frame_errors = stats->rx_frame_errors;
	/* Tx Errors */
	netdev->stats.tx_errors = stats->tx_errors;
	netdev->stats.tx_पातed_errors = stats->tx_पातed_errors;
	netdev->stats.tx_carrier_errors = stats->tx_carrier_errors;

	spin_unlock_irqrestore(&adapter->stats_lock, flags);
पूर्ण

अटल व्योम pch_gbe_disable_dma_rx(काष्ठा pch_gbe_hw *hw)
अणु
	u32 rxdma;

	/* Disable Receive DMA */
	rxdma = ioपढ़ो32(&hw->reg->DMA_CTRL);
	rxdma &= ~PCH_GBE_RX_DMA_EN;
	ioग_लिखो32(rxdma, &hw->reg->DMA_CTRL);
पूर्ण

अटल व्योम pch_gbe_enable_dma_rx(काष्ठा pch_gbe_hw *hw)
अणु
	u32 rxdma;

	/* Enables Receive DMA */
	rxdma = ioपढ़ो32(&hw->reg->DMA_CTRL);
	rxdma |= PCH_GBE_RX_DMA_EN;
	ioग_लिखो32(rxdma, &hw->reg->DMA_CTRL);
पूर्ण

/**
 * pch_gbe_पूर्णांकr - Interrupt Handler
 * @irq:   Interrupt number
 * @data:  Poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 * Returns:
 *	- IRQ_HANDLED:	Our पूर्णांकerrupt
 *	- IRQ_NONE:	Not our पूर्णांकerrupt
 */
अटल irqवापस_t pch_gbe_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	u32 पूर्णांक_st;
	u32 पूर्णांक_en;

	/* Check request status */
	पूर्णांक_st = ioपढ़ो32(&hw->reg->INT_ST);
	पूर्णांक_st = पूर्णांक_st & ioपढ़ो32(&hw->reg->INT_EN);
	/* When request status is no पूर्णांकerruption factor */
	अगर (unlikely(!पूर्णांक_st))
		वापस IRQ_NONE;	/* Not our पूर्णांकerrupt. End processing. */
	netdev_dbg(netdev, "%s occur int_st = 0x%08x\n", __func__, पूर्णांक_st);
	अगर (पूर्णांक_st & PCH_GBE_INT_RX_FRAME_ERR)
		adapter->stats.पूर्णांकr_rx_frame_err_count++;
	अगर (पूर्णांक_st & PCH_GBE_INT_RX_FIFO_ERR)
		अगर (!adapter->rx_stop_flag) अणु
			adapter->stats.पूर्णांकr_rx_fअगरo_err_count++;
			netdev_dbg(netdev, "Rx fifo over run\n");
			adapter->rx_stop_flag = true;
			पूर्णांक_en = ioपढ़ो32(&hw->reg->INT_EN);
			ioग_लिखो32((पूर्णांक_en & ~PCH_GBE_INT_RX_FIFO_ERR),
				  &hw->reg->INT_EN);
			pch_gbe_disable_dma_rx(&adapter->hw);
			पूर्णांक_st |= ioपढ़ो32(&hw->reg->INT_ST);
			पूर्णांक_st = पूर्णांक_st & ioपढ़ो32(&hw->reg->INT_EN);
		पूर्ण
	अगर (पूर्णांक_st & PCH_GBE_INT_RX_DMA_ERR)
		adapter->stats.पूर्णांकr_rx_dma_err_count++;
	अगर (पूर्णांक_st & PCH_GBE_INT_TX_FIFO_ERR)
		adapter->stats.पूर्णांकr_tx_fअगरo_err_count++;
	अगर (पूर्णांक_st & PCH_GBE_INT_TX_DMA_ERR)
		adapter->stats.पूर्णांकr_tx_dma_err_count++;
	अगर (पूर्णांक_st & PCH_GBE_INT_TCPIP_ERR)
		adapter->stats.पूर्णांकr_tcpip_err_count++;
	/* When Rx descriptor is empty  */
	अगर ((पूर्णांक_st & PCH_GBE_INT_RX_DSC_EMP)) अणु
		adapter->stats.पूर्णांकr_rx_dsc_empty_count++;
		netdev_dbg(netdev, "Rx descriptor is empty\n");
		पूर्णांक_en = ioपढ़ो32(&hw->reg->INT_EN);
		ioग_लिखो32((पूर्णांक_en & ~PCH_GBE_INT_RX_DSC_EMP), &hw->reg->INT_EN);
		अगर (hw->mac.tx_fc_enable) अणु
			/* Set Pause packet */
			pch_gbe_mac_set_छोड़ो_packet(hw);
		पूर्ण
	पूर्ण

	/* When request status is Receive पूर्णांकerruption */
	अगर ((पूर्णांक_st & (PCH_GBE_INT_RX_DMA_CMPLT | PCH_GBE_INT_TX_CMPLT)) ||
	    (adapter->rx_stop_flag)) अणु
		अगर (likely(napi_schedule_prep(&adapter->napi))) अणु
			/* Enable only Rx Descriptor empty */
			atomic_inc(&adapter->irq_sem);
			पूर्णांक_en = ioपढ़ो32(&hw->reg->INT_EN);
			पूर्णांक_en &=
			    ~(PCH_GBE_INT_RX_DMA_CMPLT | PCH_GBE_INT_TX_CMPLT);
			ioग_लिखो32(पूर्णांक_en, &hw->reg->INT_EN);
			/* Start polling क्रम NAPI */
			__napi_schedule(&adapter->napi);
		पूर्ण
	पूर्ण
	netdev_dbg(netdev, "return = 0x%08x  INT_EN reg = 0x%08x\n",
		   IRQ_HANDLED, ioपढ़ो32(&hw->reg->INT_EN));
	वापस IRQ_HANDLED;
पूर्ण

/**
 * pch_gbe_alloc_rx_buffers - Replace used receive buffers; legacy & extended
 * @adapter:       Board निजी काष्ठाure
 * @rx_ring:       Rx descriptor ring
 * @cleaned_count: Cleaned count
 */
अटल व्योम
pch_gbe_alloc_rx_buffers(काष्ठा pch_gbe_adapter *adapter,
			 काष्ठा pch_gbe_rx_ring *rx_ring, पूर्णांक cleaned_count)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	काष्ठा pch_gbe_rx_desc *rx_desc;
	काष्ठा pch_gbe_buffer *buffer_info;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक bufsz;

	bufsz = adapter->rx_buffer_len + NET_IP_ALIGN;
	i = rx_ring->next_to_use;

	जबतक ((cleaned_count--)) अणु
		buffer_info = &rx_ring->buffer_info[i];
		skb = netdev_alloc_skb(netdev, bufsz);
		अगर (unlikely(!skb)) अणु
			/* Better luck next round */
			adapter->stats.rx_alloc_buff_failed++;
			अवरोध;
		पूर्ण
		/* align */
		skb_reserve(skb, NET_IP_ALIGN);
		buffer_info->skb = skb;

		buffer_info->dma = dma_map_single(&pdev->dev,
						  buffer_info->rx_buffer,
						  buffer_info->length,
						  DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&adapter->pdev->dev, buffer_info->dma)) अणु
			dev_kमुक्त_skb(skb);
			buffer_info->skb = शून्य;
			buffer_info->dma = 0;
			adapter->stats.rx_alloc_buff_failed++;
			अवरोध; /* जबतक !buffer_info->skb */
		पूर्ण
		buffer_info->mapped = true;
		rx_desc = PCH_GBE_RX_DESC(*rx_ring, i);
		rx_desc->buffer_addr = (buffer_info->dma);
		rx_desc->gbec_status = DSC_INIT16;

		netdev_dbg(netdev,
			   "i = %d  buffer_info->dma = 0x08%llx  buffer_info->length = 0x%x\n",
			   i, (अचिन्हित दीर्घ दीर्घ)buffer_info->dma,
			   buffer_info->length);

		अगर (unlikely(++i == rx_ring->count))
			i = 0;
	पूर्ण
	अगर (likely(rx_ring->next_to_use != i)) अणु
		rx_ring->next_to_use = i;
		अगर (unlikely(i-- == 0))
			i = (rx_ring->count - 1);
		ioग_लिखो32(rx_ring->dma +
			  (पूर्णांक)माप(काष्ठा pch_gbe_rx_desc) * i,
			  &hw->reg->RX_DSC_SW_P);
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक
pch_gbe_alloc_rx_buffers_pool(काष्ठा pch_gbe_adapter *adapter,
			 काष्ठा pch_gbe_rx_ring *rx_ring, पूर्णांक cleaned_count)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा pch_gbe_buffer *buffer_info;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक bufsz;
	अचिन्हित पूर्णांक size;

	bufsz = adapter->rx_buffer_len;

	size = rx_ring->count * bufsz + PCH_GBE_RESERVE_MEMORY;
	rx_ring->rx_buff_pool =
		dma_alloc_coherent(&pdev->dev, size,
				   &rx_ring->rx_buff_pool_logic, GFP_KERNEL);
	अगर (!rx_ring->rx_buff_pool)
		वापस -ENOMEM;

	rx_ring->rx_buff_pool_size = size;
	क्रम (i = 0; i < rx_ring->count; i++) अणु
		buffer_info = &rx_ring->buffer_info[i];
		buffer_info->rx_buffer = rx_ring->rx_buff_pool + bufsz * i;
		buffer_info->length = bufsz;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pch_gbe_alloc_tx_buffers - Allocate transmit buffers
 * @adapter:   Board निजी काष्ठाure
 * @tx_ring:   Tx descriptor ring
 */
अटल व्योम pch_gbe_alloc_tx_buffers(काष्ठा pch_gbe_adapter *adapter,
					काष्ठा pch_gbe_tx_ring *tx_ring)
अणु
	काष्ठा pch_gbe_buffer *buffer_info;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक bufsz;
	काष्ठा pch_gbe_tx_desc *tx_desc;

	bufsz =
	    adapter->hw.mac.max_frame_size + PCH_GBE_DMA_ALIGN + NET_IP_ALIGN;

	क्रम (i = 0; i < tx_ring->count; i++) अणु
		buffer_info = &tx_ring->buffer_info[i];
		skb = netdev_alloc_skb(adapter->netdev, bufsz);
		skb_reserve(skb, PCH_GBE_DMA_ALIGN);
		buffer_info->skb = skb;
		tx_desc = PCH_GBE_TX_DESC(*tx_ring, i);
		tx_desc->gbec_status = (DSC_INIT16);
	पूर्ण
	वापस;
पूर्ण

/**
 * pch_gbe_clean_tx - Reclaim resources after transmit completes
 * @adapter:   Board निजी काष्ठाure
 * @tx_ring:   Tx descriptor ring
 * Returns:
 *	true:  Cleaned the descriptor
 *	false: Not cleaned the descriptor
 */
अटल bool
pch_gbe_clean_tx(काष्ठा pch_gbe_adapter *adapter,
		 काष्ठा pch_gbe_tx_ring *tx_ring)
अणु
	काष्ठा pch_gbe_tx_desc *tx_desc;
	काष्ठा pch_gbe_buffer *buffer_info;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक cleaned_count = 0;
	bool cleaned = false;
	पूर्णांक unused, thresh;

	netdev_dbg(adapter->netdev, "next_to_clean : %d\n",
		   tx_ring->next_to_clean);

	i = tx_ring->next_to_clean;
	tx_desc = PCH_GBE_TX_DESC(*tx_ring, i);
	netdev_dbg(adapter->netdev, "gbec_status:0x%04x  dma_status:0x%04x\n",
		   tx_desc->gbec_status, tx_desc->dma_status);

	unused = PCH_GBE_DESC_UNUSED(tx_ring);
	thresh = tx_ring->count - PCH_GBE_TX_WEIGHT;
	अगर ((tx_desc->gbec_status == DSC_INIT16) && (unused < thresh))
	अणु  /* current marked clean, tx queue filling up, करो extra clean */
		पूर्णांक j, k;
		अगर (unused < 8) अणु  /* tx queue nearly full */
			netdev_dbg(adapter->netdev,
				   "clean_tx: transmit queue warning (%x,%x) unused=%d\n",
				   tx_ring->next_to_clean, tx_ring->next_to_use,
				   unused);
		पूर्ण

		/* current marked clean, scan क्रम more that need cleaning. */
		k = i;
		क्रम (j = 0; j < PCH_GBE_TX_WEIGHT; j++)
		अणु
			tx_desc = PCH_GBE_TX_DESC(*tx_ring, k);
			अगर (tx_desc->gbec_status != DSC_INIT16) अवरोध; /*found*/
			अगर (++k >= tx_ring->count) k = 0;  /*increment, wrap*/
		पूर्ण
		अगर (j < PCH_GBE_TX_WEIGHT) अणु
			netdev_dbg(adapter->netdev,
				   "clean_tx: unused=%d loops=%d found tx_desc[%x,%x:%x].gbec_status=%04x\n",
				   unused, j, i, k, tx_ring->next_to_use,
				   tx_desc->gbec_status);
			i = k;  /*found one to clean, usu gbec_status==2000.*/
		पूर्ण
	पूर्ण

	जबतक ((tx_desc->gbec_status & DSC_INIT16) == 0x0000) अणु
		netdev_dbg(adapter->netdev, "gbec_status:0x%04x\n",
			   tx_desc->gbec_status);
		buffer_info = &tx_ring->buffer_info[i];
		skb = buffer_info->skb;
		cleaned = true;

		अगर ((tx_desc->gbec_status & PCH_GBE_TXD_GMAC_STAT_ABT)) अणु
			adapter->stats.tx_पातed_errors++;
			netdev_err(adapter->netdev, "Transfer Abort Error\n");
		पूर्ण अन्यथा अगर ((tx_desc->gbec_status & PCH_GBE_TXD_GMAC_STAT_CRSER)
			  ) अणु
			adapter->stats.tx_carrier_errors++;
			netdev_err(adapter->netdev,
				   "Transfer Carrier Sense Error\n");
		पूर्ण अन्यथा अगर ((tx_desc->gbec_status & PCH_GBE_TXD_GMAC_STAT_EXCOL)
			  ) अणु
			adapter->stats.tx_पातed_errors++;
			netdev_err(adapter->netdev,
				   "Transfer Collision Abort Error\n");
		पूर्ण अन्यथा अगर ((tx_desc->gbec_status &
			    (PCH_GBE_TXD_GMAC_STAT_SNGCOL |
			     PCH_GBE_TXD_GMAC_STAT_MLTCOL))) अणु
			adapter->stats.collisions++;
			adapter->stats.tx_packets++;
			adapter->stats.tx_bytes += skb->len;
			netdev_dbg(adapter->netdev, "Transfer Collision\n");
		पूर्ण अन्यथा अगर ((tx_desc->gbec_status & PCH_GBE_TXD_GMAC_STAT_CMPLT)
			  ) अणु
			adapter->stats.tx_packets++;
			adapter->stats.tx_bytes += skb->len;
		पूर्ण
		अगर (buffer_info->mapped) अणु
			netdev_dbg(adapter->netdev,
				   "unmap buffer_info->dma : %d\n", i);
			dma_unmap_single(&adapter->pdev->dev, buffer_info->dma,
					 buffer_info->length, DMA_TO_DEVICE);
			buffer_info->mapped = false;
		पूर्ण
		अगर (buffer_info->skb) अणु
			netdev_dbg(adapter->netdev,
				   "trim buffer_info->skb : %d\n", i);
			skb_trim(buffer_info->skb, 0);
		पूर्ण
		tx_desc->gbec_status = DSC_INIT16;
		अगर (unlikely(++i == tx_ring->count))
			i = 0;
		tx_desc = PCH_GBE_TX_DESC(*tx_ring, i);

		/* weight of a sort क्रम tx, to aव्योम endless transmit cleanup */
		अगर (cleaned_count++ == PCH_GBE_TX_WEIGHT) अणु
			cleaned = false;
			अवरोध;
		पूर्ण
	पूर्ण
	netdev_dbg(adapter->netdev,
		   "called pch_gbe_unmap_and_free_tx_resource() %d count\n",
		   cleaned_count);
	अगर (cleaned_count > 0)  अणु /*skip this अगर nothing cleaned*/
		/* Recover from running out of Tx resources in xmit_frame */
		netअगर_tx_lock(adapter->netdev);
		अगर (unlikely(cleaned && (netअगर_queue_stopped(adapter->netdev))))
		अणु
			netअगर_wake_queue(adapter->netdev);
			adapter->stats.tx_restart_count++;
			netdev_dbg(adapter->netdev, "Tx wake queue\n");
		पूर्ण

		tx_ring->next_to_clean = i;

		netdev_dbg(adapter->netdev, "next_to_clean : %d\n",
			   tx_ring->next_to_clean);
		netअगर_tx_unlock(adapter->netdev);
	पूर्ण
	वापस cleaned;
पूर्ण

/**
 * pch_gbe_clean_rx - Send received data up the network stack; legacy
 * @adapter:     Board निजी काष्ठाure
 * @rx_ring:     Rx descriptor ring
 * @work_करोne:   Completed count
 * @work_to_करो:  Request count
 * Returns:
 *	true:  Cleaned the descriptor
 *	false: Not cleaned the descriptor
 */
अटल bool
pch_gbe_clean_rx(काष्ठा pch_gbe_adapter *adapter,
		 काष्ठा pch_gbe_rx_ring *rx_ring,
		 पूर्णांक *work_करोne, पूर्णांक work_to_करो)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा pch_gbe_buffer *buffer_info;
	काष्ठा pch_gbe_rx_desc *rx_desc;
	u32 length;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक cleaned_count = 0;
	bool cleaned = false;
	काष्ठा sk_buff *skb;
	u8 dma_status;
	u16 gbec_status;
	u32 tcp_ip_status;

	i = rx_ring->next_to_clean;

	जबतक (*work_करोne < work_to_करो) अणु
		/* Check Rx descriptor status */
		rx_desc = PCH_GBE_RX_DESC(*rx_ring, i);
		अगर (rx_desc->gbec_status == DSC_INIT16)
			अवरोध;
		cleaned = true;
		cleaned_count++;

		dma_status = rx_desc->dma_status;
		gbec_status = rx_desc->gbec_status;
		tcp_ip_status = rx_desc->tcp_ip_status;
		rx_desc->gbec_status = DSC_INIT16;
		buffer_info = &rx_ring->buffer_info[i];
		skb = buffer_info->skb;
		buffer_info->skb = शून्य;

		/* unmap dma */
		dma_unmap_single(&pdev->dev, buffer_info->dma,
				   buffer_info->length, DMA_FROM_DEVICE);
		buffer_info->mapped = false;

		netdev_dbg(netdev,
			   "RxDecNo = 0x%04x  Status[DMA:0x%02x GBE:0x%04x TCP:0x%08x]  BufInf = 0x%p\n",
			   i, dma_status, gbec_status, tcp_ip_status,
			   buffer_info);
		/* Error check */
		अगर (unlikely(gbec_status & PCH_GBE_RXD_GMAC_STAT_NOTOCTAL)) अणु
			adapter->stats.rx_frame_errors++;
			netdev_err(netdev, "Receive Not Octal Error\n");
		पूर्ण अन्यथा अगर (unlikely(gbec_status &
				PCH_GBE_RXD_GMAC_STAT_NBLERR)) अणु
			adapter->stats.rx_frame_errors++;
			netdev_err(netdev, "Receive Nibble Error\n");
		पूर्ण अन्यथा अगर (unlikely(gbec_status &
				PCH_GBE_RXD_GMAC_STAT_CRCERR)) अणु
			adapter->stats.rx_crc_errors++;
			netdev_err(netdev, "Receive CRC Error\n");
		पूर्ण अन्यथा अणु
			/* get receive length */
			/* length convert[-3], length includes FCS length */
			length = (rx_desc->rx_words_eob) - 3 - ETH_FCS_LEN;
			अगर (rx_desc->rx_words_eob & 0x02)
				length = length - 4;
			/*
			 * buffer_info->rx_buffer: [Header:14][payload]
			 * skb->data: [Reserve:2][Header:14][payload]
			 */
			स_नकल(skb->data, buffer_info->rx_buffer, length);

			/* update status of driver */
			adapter->stats.rx_bytes += length;
			adapter->stats.rx_packets++;
			अगर ((gbec_status & PCH_GBE_RXD_GMAC_STAT_MARMLT))
				adapter->stats.multicast++;
			/* Write meta date of skb */
			skb_put(skb, length);

			pch_rx_बारtamp(adapter, skb);

			skb->protocol = eth_type_trans(skb, netdev);
			अगर (tcp_ip_status & PCH_GBE_RXD_ACC_STAT_TCPIPOK)
				skb->ip_summed = CHECKSUM_UNNECESSARY;
			अन्यथा
				skb->ip_summed = CHECKSUM_NONE;

			napi_gro_receive(&adapter->napi, skb);
			(*work_करोne)++;
			netdev_dbg(netdev,
				   "Receive skb->ip_summed: %d length: %d\n",
				   skb->ip_summed, length);
		पूर्ण
		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (unlikely(cleaned_count >= PCH_GBE_RX_BUFFER_WRITE)) अणु
			pch_gbe_alloc_rx_buffers(adapter, rx_ring,
						 cleaned_count);
			cleaned_count = 0;
		पूर्ण
		अगर (++i == rx_ring->count)
			i = 0;
	पूर्ण
	rx_ring->next_to_clean = i;
	अगर (cleaned_count)
		pch_gbe_alloc_rx_buffers(adapter, rx_ring, cleaned_count);
	वापस cleaned;
पूर्ण

/**
 * pch_gbe_setup_tx_resources - Allocate Tx resources (Descriptors)
 * @adapter:  Board निजी काष्ठाure
 * @tx_ring:  Tx descriptor ring (क्रम a specअगरic queue) to setup
 * Returns:
 *	0:		Successfully
 *	Negative value:	Failed
 */
पूर्णांक pch_gbe_setup_tx_resources(काष्ठा pch_gbe_adapter *adapter,
				काष्ठा pch_gbe_tx_ring *tx_ring)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा pch_gbe_tx_desc *tx_desc;
	पूर्णांक size;
	पूर्णांक desNo;

	size = (पूर्णांक)माप(काष्ठा pch_gbe_buffer) * tx_ring->count;
	tx_ring->buffer_info = vzalloc(size);
	अगर (!tx_ring->buffer_info)
		वापस -ENOMEM;

	tx_ring->size = tx_ring->count * (पूर्णांक)माप(काष्ठा pch_gbe_tx_desc);

	tx_ring->desc = dma_alloc_coherent(&pdev->dev, tx_ring->size,
					   &tx_ring->dma, GFP_KERNEL);
	अगर (!tx_ring->desc) अणु
		vमुक्त(tx_ring->buffer_info);
		वापस -ENOMEM;
	पूर्ण

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	क्रम (desNo = 0; desNo < tx_ring->count; desNo++) अणु
		tx_desc = PCH_GBE_TX_DESC(*tx_ring, desNo);
		tx_desc->gbec_status = DSC_INIT16;
	पूर्ण
	netdev_dbg(adapter->netdev,
		   "tx_ring->desc = 0x%p  tx_ring->dma = 0x%08llx next_to_clean = 0x%08x  next_to_use = 0x%08x\n",
		   tx_ring->desc, (अचिन्हित दीर्घ दीर्घ)tx_ring->dma,
		   tx_ring->next_to_clean, tx_ring->next_to_use);
	वापस 0;
पूर्ण

/**
 * pch_gbe_setup_rx_resources - Allocate Rx resources (Descriptors)
 * @adapter:  Board निजी काष्ठाure
 * @rx_ring:  Rx descriptor ring (क्रम a specअगरic queue) to setup
 * Returns:
 *	0:		Successfully
 *	Negative value:	Failed
 */
पूर्णांक pch_gbe_setup_rx_resources(काष्ठा pch_gbe_adapter *adapter,
				काष्ठा pch_gbe_rx_ring *rx_ring)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा pch_gbe_rx_desc *rx_desc;
	पूर्णांक size;
	पूर्णांक desNo;

	size = (पूर्णांक)माप(काष्ठा pch_gbe_buffer) * rx_ring->count;
	rx_ring->buffer_info = vzalloc(size);
	अगर (!rx_ring->buffer_info)
		वापस -ENOMEM;

	rx_ring->size = rx_ring->count * (पूर्णांक)माप(काष्ठा pch_gbe_rx_desc);
	rx_ring->desc =	dma_alloc_coherent(&pdev->dev, rx_ring->size,
						  &rx_ring->dma, GFP_KERNEL);
	अगर (!rx_ring->desc) अणु
		vमुक्त(rx_ring->buffer_info);
		वापस -ENOMEM;
	पूर्ण
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
	क्रम (desNo = 0; desNo < rx_ring->count; desNo++) अणु
		rx_desc = PCH_GBE_RX_DESC(*rx_ring, desNo);
		rx_desc->gbec_status = DSC_INIT16;
	पूर्ण
	netdev_dbg(adapter->netdev,
		   "rx_ring->desc = 0x%p  rx_ring->dma = 0x%08llx next_to_clean = 0x%08x  next_to_use = 0x%08x\n",
		   rx_ring->desc, (अचिन्हित दीर्घ दीर्घ)rx_ring->dma,
		   rx_ring->next_to_clean, rx_ring->next_to_use);
	वापस 0;
पूर्ण

/**
 * pch_gbe_मुक्त_tx_resources - Free Tx Resources
 * @adapter:  Board निजी काष्ठाure
 * @tx_ring:  Tx descriptor ring क्रम a specअगरic queue
 */
व्योम pch_gbe_मुक्त_tx_resources(काष्ठा pch_gbe_adapter *adapter,
				काष्ठा pch_gbe_tx_ring *tx_ring)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;

	pch_gbe_clean_tx_ring(adapter, tx_ring);
	vमुक्त(tx_ring->buffer_info);
	tx_ring->buffer_info = शून्य;
	dma_मुक्त_coherent(&pdev->dev, tx_ring->size, tx_ring->desc,
			  tx_ring->dma);
	tx_ring->desc = शून्य;
पूर्ण

/**
 * pch_gbe_मुक्त_rx_resources - Free Rx Resources
 * @adapter:  Board निजी काष्ठाure
 * @rx_ring:  Ring to clean the resources from
 */
व्योम pch_gbe_मुक्त_rx_resources(काष्ठा pch_gbe_adapter *adapter,
				काष्ठा pch_gbe_rx_ring *rx_ring)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;

	pch_gbe_clean_rx_ring(adapter, rx_ring);
	vमुक्त(rx_ring->buffer_info);
	rx_ring->buffer_info = शून्य;
	dma_मुक्त_coherent(&pdev->dev, rx_ring->size, rx_ring->desc,
			  rx_ring->dma);
	rx_ring->desc = शून्य;
पूर्ण

/**
 * pch_gbe_request_irq - Allocate an पूर्णांकerrupt line
 * @adapter:  Board निजी काष्ठाure
 * Returns:
 *	0:		Successfully
 *	Negative value:	Failed
 */
अटल पूर्णांक pch_gbe_request_irq(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err;

	err = pci_alloc_irq_vectors(adapter->pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (err < 0)
		वापस err;

	adapter->irq = pci_irq_vector(adapter->pdev, 0);

	err = request_irq(adapter->irq, &pch_gbe_पूर्णांकr, IRQF_SHARED,
			  netdev->name, netdev);
	अगर (err)
		netdev_err(netdev, "Unable to allocate interrupt Error: %d\n",
			   err);
	netdev_dbg(netdev, "have_msi : %d  return : 0x%04x\n",
		   pci_dev_msi_enabled(adapter->pdev), err);
	वापस err;
पूर्ण

/**
 * pch_gbe_up - Up GbE network device
 * @adapter:  Board निजी काष्ठाure
 * Returns:
 *	0:		Successfully
 *	Negative value:	Failed
 */
पूर्णांक pch_gbe_up(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pch_gbe_tx_ring *tx_ring = adapter->tx_ring;
	काष्ठा pch_gbe_rx_ring *rx_ring = adapter->rx_ring;
	पूर्णांक err = -EINVAL;

	/* Ensure we have a valid MAC */
	अगर (!is_valid_ether_addr(adapter->hw.mac.addr)) अणु
		netdev_err(netdev, "Error: Invalid MAC address\n");
		जाओ out;
	पूर्ण

	/* hardware has been reset, we need to reload some things */
	pch_gbe_set_multi(netdev);

	pch_gbe_setup_tctl(adapter);
	pch_gbe_configure_tx(adapter);
	pch_gbe_setup_rctl(adapter);
	pch_gbe_configure_rx(adapter);

	err = pch_gbe_request_irq(adapter);
	अगर (err) अणु
		netdev_err(netdev,
			   "Error: can't bring device up - irq request failed\n");
		जाओ out;
	पूर्ण
	err = pch_gbe_alloc_rx_buffers_pool(adapter, rx_ring, rx_ring->count);
	अगर (err) अणु
		netdev_err(netdev,
			   "Error: can't bring device up - alloc rx buffers pool failed\n");
		जाओ मुक्तirq;
	पूर्ण
	pch_gbe_alloc_tx_buffers(adapter, tx_ring);
	pch_gbe_alloc_rx_buffers(adapter, rx_ring, rx_ring->count);
	adapter->tx_queue_len = netdev->tx_queue_len;
	pch_gbe_enable_dma_rx(&adapter->hw);
	pch_gbe_enable_mac_rx(&adapter->hw);

	mod_समयr(&adapter->watchकरोg_समयr, jअगरfies);

	napi_enable(&adapter->napi);
	pch_gbe_irq_enable(adapter);
	netअगर_start_queue(adapter->netdev);

	वापस 0;

मुक्तirq:
	pch_gbe_मुक्त_irq(adapter);
out:
	वापस err;
पूर्ण

/**
 * pch_gbe_करोwn - Down GbE network device
 * @adapter:  Board निजी काष्ठाure
 */
व्योम pch_gbe_करोwn(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा pch_gbe_rx_ring *rx_ring = adapter->rx_ring;

	/* संकेत that we're करोwn so the पूर्णांकerrupt handler करोes not
	 * reschedule our watchकरोg समयr */
	napi_disable(&adapter->napi);
	atomic_set(&adapter->irq_sem, 0);

	pch_gbe_irq_disable(adapter);
	pch_gbe_मुक्त_irq(adapter);

	del_समयr_sync(&adapter->watchकरोg_समयr);

	netdev->tx_queue_len = adapter->tx_queue_len;
	netअगर_carrier_off(netdev);
	netअगर_stop_queue(netdev);

	अगर ((pdev->error_state) && (pdev->error_state != pci_channel_io_normal))
		pch_gbe_reset(adapter);
	pch_gbe_clean_tx_ring(adapter, adapter->tx_ring);
	pch_gbe_clean_rx_ring(adapter, adapter->rx_ring);

	dma_मुक्त_coherent(&adapter->pdev->dev, rx_ring->rx_buff_pool_size,
			  rx_ring->rx_buff_pool, rx_ring->rx_buff_pool_logic);
	rx_ring->rx_buff_pool_logic = 0;
	rx_ring->rx_buff_pool_size = 0;
	rx_ring->rx_buff_pool = शून्य;
पूर्ण

/**
 * pch_gbe_sw_init - Initialize general software काष्ठाures (काष्ठा pch_gbe_adapter)
 * @adapter:  Board निजी काष्ठाure to initialize
 * Returns:
 *	0:		Successfully
 *	Negative value:	Failed
 */
अटल पूर्णांक pch_gbe_sw_init(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;

	adapter->rx_buffer_len = PCH_GBE_FRAME_SIZE_2048;
	hw->mac.max_frame_size = netdev->mtu + ETH_HLEN + ETH_FCS_LEN;
	hw->mac.min_frame_size = ETH_ZLEN + ETH_FCS_LEN;
	hw->phy.reset_delay_us = PCH_GBE_PHY_RESET_DELAY_US;

	अगर (pch_gbe_alloc_queues(adapter)) अणु
		netdev_err(netdev, "Unable to allocate memory for queues\n");
		वापस -ENOMEM;
	पूर्ण
	spin_lock_init(&adapter->hw.miim_lock);
	spin_lock_init(&adapter->stats_lock);
	spin_lock_init(&adapter->ethtool_lock);
	atomic_set(&adapter->irq_sem, 0);
	pch_gbe_irq_disable(adapter);

	pch_gbe_init_stats(adapter);

	netdev_dbg(netdev,
		   "rx_buffer_len : %d  mac.min_frame_size : %d  mac.max_frame_size : %d\n",
		   (u32) adapter->rx_buffer_len,
		   hw->mac.min_frame_size, hw->mac.max_frame_size);
	वापस 0;
पूर्ण

/**
 * pch_gbe_खोलो - Called when a network पूर्णांकerface is made active
 * @netdev:	Network पूर्णांकerface device काष्ठाure
 * Returns:
 *	0:		Successfully
 *	Negative value:	Failed
 */
अटल पूर्णांक pch_gbe_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	पूर्णांक err;

	/* allocate transmit descriptors */
	err = pch_gbe_setup_tx_resources(adapter, adapter->tx_ring);
	अगर (err)
		जाओ err_setup_tx;
	/* allocate receive descriptors */
	err = pch_gbe_setup_rx_resources(adapter, adapter->rx_ring);
	अगर (err)
		जाओ err_setup_rx;
	pch_gbe_phy_घातer_up(hw);
	err = pch_gbe_up(adapter);
	अगर (err)
		जाओ err_up;
	netdev_dbg(netdev, "Success End\n");
	वापस 0;

err_up:
	अगर (!adapter->wake_up_evt)
		pch_gbe_phy_घातer_करोwn(hw);
	pch_gbe_मुक्त_rx_resources(adapter, adapter->rx_ring);
err_setup_rx:
	pch_gbe_मुक्त_tx_resources(adapter, adapter->tx_ring);
err_setup_tx:
	pch_gbe_reset(adapter);
	netdev_err(netdev, "Error End\n");
	वापस err;
पूर्ण

/**
 * pch_gbe_stop - Disables a network पूर्णांकerface
 * @netdev:  Network पूर्णांकerface device काष्ठाure
 * Returns:
 *	0: Successfully
 */
अटल पूर्णांक pch_gbe_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_hw *hw = &adapter->hw;

	pch_gbe_करोwn(adapter);
	अगर (!adapter->wake_up_evt)
		pch_gbe_phy_घातer_करोwn(hw);
	pch_gbe_मुक्त_tx_resources(adapter, adapter->tx_ring);
	pch_gbe_मुक्त_rx_resources(adapter, adapter->rx_ring);
	वापस 0;
पूर्ण

/**
 * pch_gbe_xmit_frame - Packet transmitting start
 * @skb:     Socket buffer काष्ठाure
 * @netdev:  Network पूर्णांकerface device काष्ठाure
 * Returns:
 *	- NETDEV_TX_OK:   Normal end
 *	- NETDEV_TX_BUSY: Error end
 */
अटल netdev_tx_t pch_gbe_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_tx_ring *tx_ring = adapter->tx_ring;

	अगर (unlikely(!PCH_GBE_DESC_UNUSED(tx_ring))) अणु
		netअगर_stop_queue(netdev);
		netdev_dbg(netdev,
			   "Return : BUSY  next_to use : 0x%08x  next_to clean : 0x%08x\n",
			   tx_ring->next_to_use, tx_ring->next_to_clean);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* CRC,ITAG no support */
	pch_gbe_tx_queue(adapter, tx_ring, skb);
	वापस NETDEV_TX_OK;
पूर्ण

/**
 * pch_gbe_set_multi - Multicast and Promiscuous mode set
 * @netdev:   Network पूर्णांकerface device काष्ठाure
 */
अटल व्योम pch_gbe_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	काष्ठा netdev_hw_addr *ha;
	u32 rctl, adrmask;
	पूर्णांक mc_count, i;

	netdev_dbg(netdev, "netdev->flags : 0x%08x\n", netdev->flags);

	/* By शेष enable address & multicast filtering */
	rctl = ioपढ़ो32(&hw->reg->RX_MODE);
	rctl |= PCH_GBE_ADD_FIL_EN | PCH_GBE_MLT_FIL_EN;

	/* Promiscuous mode disables all hardware address filtering */
	अगर (netdev->flags & IFF_PROMISC)
		rctl &= ~(PCH_GBE_ADD_FIL_EN | PCH_GBE_MLT_FIL_EN);

	/* If we want to monitor more multicast addresses than the hardware can
	 * support then disable hardware multicast filtering.
	 */
	mc_count = netdev_mc_count(netdev);
	अगर ((netdev->flags & IFF_ALLMULTI) || mc_count >= PCH_GBE_MAR_ENTRIES)
		rctl &= ~PCH_GBE_MLT_FIL_EN;

	ioग_लिखो32(rctl, &hw->reg->RX_MODE);

	/* If we're not using multicast filtering then there's no poपूर्णांक
	 * configuring the unused MAC address रेजिस्टरs.
	 */
	अगर (!(rctl & PCH_GBE_MLT_FIL_EN))
		वापस;

	/* Load the first set of multicast addresses पूर्णांकo MAC address रेजिस्टरs
	 * क्रम use by hardware filtering.
	 */
	i = 1;
	netdev_क्रम_each_mc_addr(ha, netdev)
		pch_gbe_mac_mar_set(hw, ha->addr, i++);

	/* If there are spare MAC रेजिस्टरs, mask & clear them */
	क्रम (; i < PCH_GBE_MAR_ENTRIES; i++) अणु
		/* Clear MAC address mask */
		adrmask = ioपढ़ो32(&hw->reg->ADDR_MASK);
		ioग_लिखो32(adrmask | BIT(i), &hw->reg->ADDR_MASK);
		/* रुको busy */
		pch_gbe_रुको_clr_bit(&hw->reg->ADDR_MASK, PCH_GBE_BUSY);
		/* Clear MAC address */
		ioग_लिखो32(0, &hw->reg->mac_adr[i].high);
		ioग_लिखो32(0, &hw->reg->mac_adr[i].low);
	पूर्ण

	netdev_dbg(netdev,
		 "RX_MODE reg(check bit31,30 ADD,MLT) : 0x%08x  netdev->mc_count : 0x%08x\n",
		 ioपढ़ो32(&hw->reg->RX_MODE), mc_count);
पूर्ण

/**
 * pch_gbe_set_mac - Change the Ethernet Address of the NIC
 * @netdev: Network पूर्णांकerface device काष्ठाure
 * @addr:   Poपूर्णांकer to an address काष्ठाure
 * Returns:
 *	0:		Successfully
 *	-EADDRNOTAVAIL:	Failed
 */
अटल पूर्णांक pch_gbe_set_mac(काष्ठा net_device *netdev, व्योम *addr)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा sockaddr *skaddr = addr;
	पूर्णांक ret_val;

	अगर (!is_valid_ether_addr(skaddr->sa_data)) अणु
		ret_val = -EADDRNOTAVAIL;
	पूर्ण अन्यथा अणु
		स_नकल(netdev->dev_addr, skaddr->sa_data, netdev->addr_len);
		स_नकल(adapter->hw.mac.addr, skaddr->sa_data, netdev->addr_len);
		pch_gbe_mac_mar_set(&adapter->hw, adapter->hw.mac.addr, 0);
		ret_val = 0;
	पूर्ण
	netdev_dbg(netdev, "ret_val : 0x%08x\n", ret_val);
	netdev_dbg(netdev, "dev_addr : %pM\n", netdev->dev_addr);
	netdev_dbg(netdev, "mac_addr : %pM\n", adapter->hw.mac.addr);
	netdev_dbg(netdev, "MAC_ADR1AB reg : 0x%08x 0x%08x\n",
		   ioपढ़ो32(&adapter->hw.reg->mac_adr[0].high),
		   ioपढ़ो32(&adapter->hw.reg->mac_adr[0].low));
	वापस ret_val;
पूर्ण

/**
 * pch_gbe_change_mtu - Change the Maximum Transfer Unit
 * @netdev:   Network पूर्णांकerface device काष्ठाure
 * @new_mtu:  New value क्रम maximum frame size
 * Returns:
 *	0:		Successfully
 *	-EINVAL:	Failed
 */
अटल पूर्णांक pch_gbe_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	पूर्णांक max_frame = new_mtu + ETH_HLEN + ETH_FCS_LEN;
	अचिन्हित दीर्घ old_rx_buffer_len = adapter->rx_buffer_len;
	पूर्णांक err;

	अगर (max_frame <= PCH_GBE_FRAME_SIZE_2048)
		adapter->rx_buffer_len = PCH_GBE_FRAME_SIZE_2048;
	अन्यथा अगर (max_frame <= PCH_GBE_FRAME_SIZE_4096)
		adapter->rx_buffer_len = PCH_GBE_FRAME_SIZE_4096;
	अन्यथा अगर (max_frame <= PCH_GBE_FRAME_SIZE_8192)
		adapter->rx_buffer_len = PCH_GBE_FRAME_SIZE_8192;
	अन्यथा
		adapter->rx_buffer_len = PCH_GBE_MAX_RX_BUFFER_SIZE;

	अगर (netअगर_running(netdev)) अणु
		pch_gbe_करोwn(adapter);
		err = pch_gbe_up(adapter);
		अगर (err) अणु
			adapter->rx_buffer_len = old_rx_buffer_len;
			pch_gbe_up(adapter);
			वापस err;
		पूर्ण अन्यथा अणु
			netdev->mtu = new_mtu;
			adapter->hw.mac.max_frame_size = max_frame;
		पूर्ण
	पूर्ण अन्यथा अणु
		pch_gbe_reset(adapter);
		netdev->mtu = new_mtu;
		adapter->hw.mac.max_frame_size = max_frame;
	पूर्ण

	netdev_dbg(netdev,
		   "max_frame : %d  rx_buffer_len : %d  mtu : %d  max_frame_size : %d\n",
		   max_frame, (u32) adapter->rx_buffer_len, netdev->mtu,
		   adapter->hw.mac.max_frame_size);
	वापस 0;
पूर्ण

/**
 * pch_gbe_set_features - Reset device after features changed
 * @netdev:   Network पूर्णांकerface device काष्ठाure
 * @features:  New features
 * Returns:
 *	0:		HW state updated successfully
 */
अटल पूर्णांक pch_gbe_set_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	netdev_features_t changed = features ^ netdev->features;

	अगर (!(changed & NETIF_F_RXCSUM))
		वापस 0;

	अगर (netअगर_running(netdev))
		pch_gbe_reinit_locked(adapter);
	अन्यथा
		pch_gbe_reset(adapter);

	वापस 0;
पूर्ण

/**
 * pch_gbe_ioctl - Controls रेजिस्टर through a MII पूर्णांकerface
 * @netdev:   Network पूर्णांकerface device काष्ठाure
 * @अगरr:      Poपूर्णांकer to अगरr काष्ठाure
 * @cmd:      Control command
 * Returns:
 *	0:	Successfully
 *	Negative value:	Failed
 */
अटल पूर्णांक pch_gbe_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);

	netdev_dbg(netdev, "cmd : 0x%04x\n", cmd);

	अगर (cmd == SIOCSHWTSTAMP)
		वापस hwtstamp_ioctl(netdev, अगरr, cmd);

	वापस generic_mii_ioctl(&adapter->mii, अगर_mii(अगरr), cmd, शून्य);
पूर्ण

/**
 * pch_gbe_tx_समयout - Respond to a Tx Hang
 * @netdev:   Network पूर्णांकerface device काष्ठाure
 * @txqueue: index of hanging queue
 */
अटल व्योम pch_gbe_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);

	/* Do the reset outside of पूर्णांकerrupt context */
	adapter->stats.tx_समयout_count++;
	schedule_work(&adapter->reset_task);
पूर्ण

/**
 * pch_gbe_napi_poll - NAPI receive and transfer polling callback
 * @napi:    Poपूर्णांकer of polling device काष्ठा
 * @budget:  The maximum number of a packet
 * Returns:
 *	false:  Exit the polling mode
 *	true:   Continue the polling mode
 */
अटल पूर्णांक pch_gbe_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा pch_gbe_adapter *adapter =
	    container_of(napi, काष्ठा pch_gbe_adapter, napi);
	पूर्णांक work_करोne = 0;
	bool poll_end_flag = false;
	bool cleaned = false;

	netdev_dbg(adapter->netdev, "budget : %d\n", budget);

	pch_gbe_clean_rx(adapter, adapter->rx_ring, &work_करोne, budget);
	cleaned = pch_gbe_clean_tx(adapter, adapter->tx_ring);

	अगर (cleaned)
		work_करोne = budget;
	/* If no Tx and not enough Rx work करोne,
	 * निकास the polling mode
	 */
	अगर (work_करोne < budget)
		poll_end_flag = true;

	अगर (poll_end_flag) अणु
		napi_complete_करोne(napi, work_करोne);
		pch_gbe_irq_enable(adapter);
	पूर्ण

	अगर (adapter->rx_stop_flag) अणु
		adapter->rx_stop_flag = false;
		pch_gbe_enable_dma_rx(&adapter->hw);
	पूर्ण

	netdev_dbg(adapter->netdev,
		   "poll_end_flag : %d  work_done : %d  budget : %d\n",
		   poll_end_flag, work_करोne, budget);

	वापस work_करोne;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/**
 * pch_gbe_netpoll - Used by things like netconsole to send skbs
 * @netdev:  Network पूर्णांकerface device काष्ठाure
 */
अटल व्योम pch_gbe_netpoll(काष्ठा net_device *netdev)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);

	disable_irq(adapter->irq);
	pch_gbe_पूर्णांकr(adapter->irq, netdev);
	enable_irq(adapter->irq);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops pch_gbe_netdev_ops = अणु
	.nकरो_खोलो = pch_gbe_खोलो,
	.nकरो_stop = pch_gbe_stop,
	.nकरो_start_xmit = pch_gbe_xmit_frame,
	.nकरो_set_mac_address = pch_gbe_set_mac,
	.nकरो_tx_समयout = pch_gbe_tx_समयout,
	.nकरो_change_mtu = pch_gbe_change_mtu,
	.nकरो_set_features = pch_gbe_set_features,
	.nकरो_करो_ioctl = pch_gbe_ioctl,
	.nकरो_set_rx_mode = pch_gbe_set_multi,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = pch_gbe_netpoll,
#पूर्ण_अगर
पूर्ण;

अटल pci_ers_result_t pch_gbe_io_error_detected(काष्ठा pci_dev *pdev,
						pci_channel_state_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);

	netअगर_device_detach(netdev);
	अगर (netअगर_running(netdev))
		pch_gbe_करोwn(adapter);
	pci_disable_device(pdev);
	/* Request a slot slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t pch_gbe_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_hw *hw = &adapter->hw;

	अगर (pci_enable_device(pdev)) अणु
		netdev_err(netdev, "Cannot re-enable PCI device after reset\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
	pci_set_master(pdev);
	pci_enable_wake(pdev, PCI_D0, 0);
	pch_gbe_phy_घातer_up(hw);
	pch_gbe_reset(adapter);
	/* Clear wake up status */
	pch_gbe_mac_set_wol_event(hw, 0);

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल व्योम pch_gbe_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);

	अगर (netअगर_running(netdev)) अणु
		अगर (pch_gbe_up(adapter)) अणु
			netdev_dbg(netdev,
				   "can't bring device back up after reset\n");
			वापस;
		पूर्ण
	पूर्ण
	netअगर_device_attach(netdev);
पूर्ण

अटल पूर्णांक __pch_gbe_suspend(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	u32 wufc = adapter->wake_up_evt;

	netअगर_device_detach(netdev);
	अगर (netअगर_running(netdev))
		pch_gbe_करोwn(adapter);
	अगर (wufc) अणु
		pch_gbe_set_multi(netdev);
		pch_gbe_setup_rctl(adapter);
		pch_gbe_configure_rx(adapter);
		pch_gbe_set_rgmii_ctrl(adapter, hw->mac.link_speed,
					hw->mac.link_duplex);
		pch_gbe_set_mode(adapter, hw->mac.link_speed,
					hw->mac.link_duplex);
		pch_gbe_mac_set_wol_event(hw, wufc);
		pci_disable_device(pdev);
	पूर्ण अन्यथा अणु
		pch_gbe_phy_घातer_करोwn(hw);
		pch_gbe_mac_set_wol_event(hw, wufc);
		pci_disable_device(pdev);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pch_gbe_suspend(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);

	वापस __pch_gbe_suspend(pdev);
पूर्ण

अटल पूर्णांक pch_gbe_resume(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	u32 err;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		netdev_err(netdev, "Cannot enable PCI device from suspend\n");
		वापस err;
	पूर्ण
	pci_set_master(pdev);
	pch_gbe_phy_घातer_up(hw);
	pch_gbe_reset(adapter);
	/* Clear wake on lan control and status */
	pch_gbe_mac_set_wol_event(hw, 0);

	अगर (netअगर_running(netdev))
		pch_gbe_up(adapter);
	netअगर_device_attach(netdev);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल व्योम pch_gbe_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	__pch_gbe_suspend(pdev);
	अगर (प्रणाली_state == SYSTEM_POWER_OFF) अणु
		pci_wake_from_d3(pdev, true);
		pci_set_घातer_state(pdev, PCI_D3hot);
	पूर्ण
पूर्ण

अटल व्योम pch_gbe_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);

	cancel_work_sync(&adapter->reset_task);
	unरेजिस्टर_netdev(netdev);

	pch_gbe_phy_hw_reset(&adapter->hw);

	मुक्त_netdev(netdev);
पूर्ण

अटल पूर्णांक pch_gbe_probe(काष्ठा pci_dev *pdev,
			  स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा net_device *netdev;
	काष्ठा pch_gbe_adapter *adapter;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	अगर (dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64))) अणु
		ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (ret) अणु
			dev_err(&pdev->dev, "ERR: No usable DMA configuration, aborting\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = pcim_iomap_regions(pdev, 1 << PCH_GBE_PCI_BAR, pci_name(pdev));
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"ERR: Can't reserve PCI I/O and memory resources\n");
		वापस ret;
	पूर्ण
	pci_set_master(pdev);

	netdev = alloc_etherdev((पूर्णांक)माप(काष्ठा pch_gbe_adapter));
	अगर (!netdev)
		वापस -ENOMEM;
	SET_NETDEV_DEV(netdev, &pdev->dev);

	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	adapter->hw.back = adapter;
	adapter->hw.reg = pcim_iomap_table(pdev)[PCH_GBE_PCI_BAR];
	adapter->pdata = (काष्ठा pch_gbe_privdata *)pci_id->driver_data;
	अगर (adapter->pdata && adapter->pdata->platक्रमm_init)
		adapter->pdata->platक्रमm_init(pdev);

	adapter->ptp_pdev =
		pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(adapter->pdev->bus),
					    adapter->pdev->bus->number,
					    PCI_DEVFN(12, 4));

	netdev->netdev_ops = &pch_gbe_netdev_ops;
	netdev->watchकरोg_समयo = PCH_GBE_WATCHDOG_PERIOD;
	netअगर_napi_add(netdev, &adapter->napi,
		       pch_gbe_napi_poll, PCH_GBE_RX_WEIGHT);
	netdev->hw_features = NETIF_F_RXCSUM |
		NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	netdev->features = netdev->hw_features;
	pch_gbe_set_ethtool_ops(netdev);

	/* MTU range: 46 - 10300 */
	netdev->min_mtu = ETH_ZLEN - ETH_HLEN;
	netdev->max_mtu = PCH_GBE_MAX_JUMBO_FRAME_SIZE -
			  (ETH_HLEN + ETH_FCS_LEN);

	pch_gbe_mac_load_mac_addr(&adapter->hw);
	pch_gbe_mac_reset_hw(&adapter->hw);

	/* setup the निजी काष्ठाure */
	ret = pch_gbe_sw_init(adapter);
	अगर (ret)
		जाओ err_मुक्त_netdev;

	/* Initialize PHY */
	ret = pch_gbe_init_phy(adapter);
	अगर (ret) अणु
		dev_err(&pdev->dev, "PHY initialize error\n");
		जाओ err_मुक्त_adapter;
	पूर्ण

	/* Read the MAC address. and store to the निजी data */
	ret = pch_gbe_mac_पढ़ो_mac_addr(&adapter->hw);
	अगर (ret) अणु
		dev_err(&pdev->dev, "MAC address Read Error\n");
		जाओ err_मुक्त_adapter;
	पूर्ण

	स_नकल(netdev->dev_addr, adapter->hw.mac.addr, netdev->addr_len);
	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		/*
		 * If the MAC is invalid (or just missing), display a warning
		 * but करो not पात setting up the device. pch_gbe_up will
		 * prevent the पूर्णांकerface from being brought up until a valid MAC
		 * is set.
		 */
		dev_err(&pdev->dev, "Invalid MAC address, "
		                    "interface disabled.\n");
	पूर्ण
	समयr_setup(&adapter->watchकरोg_समयr, pch_gbe_watchकरोg, 0);

	INIT_WORK(&adapter->reset_task, pch_gbe_reset_task);

	pch_gbe_check_options(adapter);

	/* initialize the wol settings based on the eeprom settings */
	adapter->wake_up_evt = PCH_GBE_WL_INIT_SETTING;
	dev_info(&pdev->dev, "MAC address : %pM\n", netdev->dev_addr);

	/* reset the hardware with the new settings */
	pch_gbe_reset(adapter);

	ret = रेजिस्टर_netdev(netdev);
	अगर (ret)
		जाओ err_मुक्त_adapter;
	/* tell the stack to leave us alone until pch_gbe_खोलो() is called */
	netअगर_carrier_off(netdev);
	netअगर_stop_queue(netdev);

	dev_dbg(&pdev->dev, "PCH Network Connection\n");

	/* Disable hibernation on certain platक्रमms */
	अगर (adapter->pdata && adapter->pdata->phy_disable_hibernate)
		pch_gbe_phy_disable_hibernate(&adapter->hw);

	device_set_wakeup_enable(&pdev->dev, 1);
	वापस 0;

err_मुक्त_adapter:
	pch_gbe_phy_hw_reset(&adapter->hw);
err_मुक्त_netdev:
	मुक्त_netdev(netdev);
	वापस ret;
पूर्ण

/* The AR803X PHY on the MinnowBoard requires a physical pin to be toggled to
 * ensure it is awake क्रम probe and init. Request the line and reset the PHY.
 */
अटल पूर्णांक pch_gbe_minnow_platक्रमm_init(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ flags = GPIOF_सूची_OUT | GPIOF_INIT_HIGH | GPIOF_EXPORT;
	अचिन्हित gpio = MINNOW_PHY_RESET_GPIO;
	पूर्णांक ret;

	ret = devm_gpio_request_one(&pdev->dev, gpio, flags,
				    "minnow_phy_reset");
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"ERR: Can't request PHY reset GPIO line '%d'\n", gpio);
		वापस ret;
	पूर्ण

	gpio_set_value(gpio, 0);
	usleep_range(1250, 1500);
	gpio_set_value(gpio, 1);
	usleep_range(1250, 1500);

	वापस ret;
पूर्ण

अटल काष्ठा pch_gbe_privdata pch_gbe_minnow_privdata = अणु
	.phy_tx_clk_delay = true,
	.phy_disable_hibernate = true,
	.platक्रमm_init = pch_gbe_minnow_platक्रमm_init,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pch_gbe_pcidev_id[] = अणु
	अणु.venकरोr = PCI_VENDOR_ID_INTEL,
	 .device = PCI_DEVICE_ID_INTEL_IOH1_GBE,
	 .subvenकरोr = PCI_VENDOR_ID_CIRCUITCO,
	 .subdevice = PCI_SUBSYSTEM_ID_CIRCUITCO_MINNOWBOARD,
	 .class = (PCI_CLASS_NETWORK_ETHERNET << 8),
	 .class_mask = (0xFFFF00),
	 .driver_data = (kernel_uदीर्घ_t)&pch_gbe_minnow_privdata
	 पूर्ण,
	अणु.venकरोr = PCI_VENDOR_ID_INTEL,
	 .device = PCI_DEVICE_ID_INTEL_IOH1_GBE,
	 .subvenकरोr = PCI_ANY_ID,
	 .subdevice = PCI_ANY_ID,
	 .class = (PCI_CLASS_NETWORK_ETHERNET << 8),
	 .class_mask = (0xFFFF00)
	 पूर्ण,
	अणु.venकरोr = PCI_VENDOR_ID_ROHM,
	 .device = PCI_DEVICE_ID_ROHM_ML7223_GBE,
	 .subvenकरोr = PCI_ANY_ID,
	 .subdevice = PCI_ANY_ID,
	 .class = (PCI_CLASS_NETWORK_ETHERNET << 8),
	 .class_mask = (0xFFFF00)
	 पूर्ण,
	अणु.venकरोr = PCI_VENDOR_ID_ROHM,
	 .device = PCI_DEVICE_ID_ROHM_ML7831_GBE,
	 .subvenकरोr = PCI_ANY_ID,
	 .subdevice = PCI_ANY_ID,
	 .class = (PCI_CLASS_NETWORK_ETHERNET << 8),
	 .class_mask = (0xFFFF00)
	 पूर्ण,
	/* required last entry */
	अणु0पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल स्थिर काष्ठा dev_pm_ops pch_gbe_pm_ops = अणु
	.suspend = pch_gbe_suspend,
	.resume = pch_gbe_resume,
	.मुक्तze = pch_gbe_suspend,
	.thaw = pch_gbe_resume,
	.घातeroff = pch_gbe_suspend,
	.restore = pch_gbe_resume,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_error_handlers pch_gbe_err_handler = अणु
	.error_detected = pch_gbe_io_error_detected,
	.slot_reset = pch_gbe_io_slot_reset,
	.resume = pch_gbe_io_resume
पूर्ण;

अटल काष्ठा pci_driver pch_gbe_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = pch_gbe_pcidev_id,
	.probe = pch_gbe_probe,
	.हटाओ = pch_gbe_हटाओ,
#अगर_घोषित CONFIG_PM
	.driver.pm = &pch_gbe_pm_ops,
#पूर्ण_अगर
	.shutकरोwn = pch_gbe_shutकरोwn,
	.err_handler = &pch_gbe_err_handler
पूर्ण;
module_pci_driver(pch_gbe_driver);

MODULE_DESCRIPTION("EG20T PCH Gigabit ethernet Driver");
MODULE_AUTHOR("LAPIS SEMICONDUCTOR, <tshimizu818@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
MODULE_DEVICE_TABLE(pci, pch_gbe_pcidev_id);

/* pch_gbe_मुख्य.c */
