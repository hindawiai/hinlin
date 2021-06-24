<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1999 - 2010 Intel Corporation.
 * Copyright (C) 2010 OKI SEMICONDUCTOR Co., LTD.
 *
 * This code was derived from the Intel e1000e Linux driver.
 */
#समावेश "pch_gbe.h"
#समावेश "pch_gbe_phy.h"

/*
 * pch_gbe_stats - Stats item inक्रमmation
 */
काष्ठा pch_gbe_stats अणु
	अक्षर string[ETH_GSTRING_LEN];
	माप_प्रकार size;
	माप_प्रकार offset;
पूर्ण;

#घोषणा PCH_GBE_STAT(m)						\
अणु								\
	.string = #m,						\
	.size = माप_field(काष्ठा pch_gbe_hw_stats, m),	\
	.offset = दुरत्व(काष्ठा pch_gbe_hw_stats, m),		\
पूर्ण

/*
 * pch_gbe_gstrings_stats - ethtool inक्रमmation status name list
 */
अटल स्थिर काष्ठा pch_gbe_stats pch_gbe_gstrings_stats[] = अणु
	PCH_GBE_STAT(rx_packets),
	PCH_GBE_STAT(tx_packets),
	PCH_GBE_STAT(rx_bytes),
	PCH_GBE_STAT(tx_bytes),
	PCH_GBE_STAT(rx_errors),
	PCH_GBE_STAT(tx_errors),
	PCH_GBE_STAT(rx_dropped),
	PCH_GBE_STAT(tx_dropped),
	PCH_GBE_STAT(multicast),
	PCH_GBE_STAT(collisions),
	PCH_GBE_STAT(rx_crc_errors),
	PCH_GBE_STAT(rx_frame_errors),
	PCH_GBE_STAT(rx_alloc_buff_failed),
	PCH_GBE_STAT(tx_length_errors),
	PCH_GBE_STAT(tx_पातed_errors),
	PCH_GBE_STAT(tx_carrier_errors),
	PCH_GBE_STAT(tx_समयout_count),
	PCH_GBE_STAT(tx_restart_count),
	PCH_GBE_STAT(पूर्णांकr_rx_dsc_empty_count),
	PCH_GBE_STAT(पूर्णांकr_rx_frame_err_count),
	PCH_GBE_STAT(पूर्णांकr_rx_fअगरo_err_count),
	PCH_GBE_STAT(पूर्णांकr_rx_dma_err_count),
	PCH_GBE_STAT(पूर्णांकr_tx_fअगरo_err_count),
	PCH_GBE_STAT(पूर्णांकr_tx_dma_err_count),
	PCH_GBE_STAT(पूर्णांकr_tcpip_err_count)
पूर्ण;

#घोषणा PCH_GBE_QUEUE_STATS_LEN 0
#घोषणा PCH_GBE_GLOBAL_STATS_LEN	ARRAY_SIZE(pch_gbe_gstrings_stats)
#घोषणा PCH_GBE_STATS_LEN (PCH_GBE_GLOBAL_STATS_LEN + PCH_GBE_QUEUE_STATS_LEN)

#घोषणा PCH_GBE_MAC_REGS_LEN    (माप(काष्ठा pch_gbe_regs) / 4)
#घोषणा PCH_GBE_REGS_LEN        (PCH_GBE_MAC_REGS_LEN + PCH_GBE_PHY_REGS_LEN)
/**
 * pch_gbe_get_link_ksettings - Get device-specअगरic settings
 * @netdev: Network पूर्णांकerface device काष्ठाure
 * @ecmd:   Ethtool command
 * Returns:
 *	0:			Successful.
 *	Negative value:		Failed.
 */
अटल पूर्णांक pch_gbe_get_link_ksettings(काष्ठा net_device *netdev,
				      काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	u32 supported, advertising;

	mii_ethtool_get_link_ksettings(&adapter->mii, ecmd);

	ethtool_convert_link_mode_to_legacy_u32(&supported,
						ecmd->link_modes.supported);
	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						ecmd->link_modes.advertising);

	supported &= ~(SUPPORTED_TP | SUPPORTED_1000baseT_Half);
	advertising &= ~(ADVERTISED_TP | ADVERTISED_1000baseT_Half);

	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.advertising,
						advertising);

	अगर (!netअगर_carrier_ok(adapter->netdev))
		ecmd->base.speed = SPEED_UNKNOWN;

	वापस 0;
पूर्ण

/**
 * pch_gbe_set_link_ksettings - Set device-specअगरic settings
 * @netdev: Network पूर्णांकerface device काष्ठाure
 * @ecmd:   Ethtool command
 * Returns:
 *	0:			Successful.
 *	Negative value:		Failed.
 */
अटल पूर्णांक pch_gbe_set_link_ksettings(काष्ठा net_device *netdev,
				      स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	काष्ठा ethtool_link_ksettings copy_ecmd;
	u32 speed = ecmd->base.speed;
	u32 advertising;
	पूर्णांक ret;

	pch_gbe_phy_ग_लिखो_reg_miic(hw, MII_BMCR, BMCR_RESET);

	स_नकल(&copy_ecmd, ecmd, माप(*ecmd));

	/* when set_settings() is called with a ethtool_cmd previously
	 * filled by get_settings() on a करोwn link, speed is -1: */
	अगर (speed == अच_पूर्णांक_उच्च) अणु
		speed = SPEED_1000;
		copy_ecmd.base.speed = speed;
		copy_ecmd.base.duplex = DUPLEX_FULL;
	पूर्ण
	ret = mii_ethtool_set_link_ksettings(&adapter->mii, &copy_ecmd);
	अगर (ret) अणु
		netdev_err(netdev, "Error: mii_ethtool_set_link_ksettings\n");
		वापस ret;
	पूर्ण
	hw->mac.link_speed = speed;
	hw->mac.link_duplex = copy_ecmd.base.duplex;
	ethtool_convert_link_mode_to_legacy_u32(
		&advertising, copy_ecmd.link_modes.advertising);
	hw->phy.स्वतःneg_advertised = advertising;
	hw->mac.स्वतःneg = copy_ecmd.base.स्वतःneg;

	/* reset the link */
	अगर (netअगर_running(adapter->netdev)) अणु
		pch_gbe_करोwn(adapter);
		ret = pch_gbe_up(adapter);
	पूर्ण अन्यथा अणु
		pch_gbe_reset(adapter);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * pch_gbe_get_regs_len - Report the size of device रेजिस्टरs
 * @netdev: Network पूर्णांकerface device काष्ठाure
 * Returns: the size of device रेजिस्टरs.
 */
अटल पूर्णांक pch_gbe_get_regs_len(काष्ठा net_device *netdev)
अणु
	वापस PCH_GBE_REGS_LEN * (पूर्णांक)माप(u32);
पूर्ण

/**
 * pch_gbe_get_drvinfo - Report driver inक्रमmation
 * @netdev:  Network पूर्णांकerface device काष्ठाure
 * @drvinfo: Driver inक्रमmation काष्ठाure
 */
अटल व्योम pch_gbe_get_drvinfo(काष्ठा net_device *netdev,
				 काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver, KBUILD_MODNAME, माप(drvinfo->driver));
	strlcpy(drvinfo->version, pch_driver_version, माप(drvinfo->version));
	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));
पूर्ण

/**
 * pch_gbe_get_regs - Get device रेजिस्टरs
 * @netdev: Network पूर्णांकerface device काष्ठाure
 * @regs:   Ethtool रेजिस्टर काष्ठाure
 * @p:      Buffer poपूर्णांकer of पढ़ो device रेजिस्टर date
 */
अटल व्योम pch_gbe_get_regs(काष्ठा net_device *netdev,
				काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	काष्ठा pci_dev *pdev = adapter->pdev;
	u32 *regs_buff = p;
	u16 i, पंचांगp;

	regs->version = 0x1000000 | (__u32)pdev->revision << 16 | pdev->device;
	क्रम (i = 0; i < PCH_GBE_MAC_REGS_LEN; i++)
		*regs_buff++ = ioपढ़ो32(&hw->reg->INT_ST + i);
	/* PHY रेजिस्टर */
	क्रम (i = 0; i < PCH_GBE_PHY_REGS_LEN; i++) अणु
		pch_gbe_phy_पढ़ो_reg_miic(&adapter->hw, i, &पंचांगp);
		*regs_buff++ = पंचांगp;
	पूर्ण
पूर्ण

/**
 * pch_gbe_get_wol - Report whether Wake-on-Lan is enabled
 * @netdev: Network पूर्णांकerface device काष्ठाure
 * @wol:    Wake-on-Lan inक्रमmation
 */
अटल व्योम pch_gbe_get_wol(काष्ठा net_device *netdev,
				काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);

	wol->supported = WAKE_UCAST | WAKE_MCAST | WAKE_BCAST | WAKE_MAGIC;
	wol->wolopts = 0;

	अगर ((adapter->wake_up_evt & PCH_GBE_WLC_IND))
		wol->wolopts |= WAKE_UCAST;
	अगर ((adapter->wake_up_evt & PCH_GBE_WLC_MLT))
		wol->wolopts |= WAKE_MCAST;
	अगर ((adapter->wake_up_evt & PCH_GBE_WLC_BR))
		wol->wolopts |= WAKE_BCAST;
	अगर ((adapter->wake_up_evt & PCH_GBE_WLC_MP))
		wol->wolopts |= WAKE_MAGIC;
पूर्ण

/**
 * pch_gbe_set_wol - Turn Wake-on-Lan on or off
 * @netdev: Network पूर्णांकerface device काष्ठाure
 * @wol:    Poपूर्णांकer of wake-on-Lan inक्रमmation straucture
 * Returns:
 *	0:			Successful.
 *	Negative value:		Failed.
 */
अटल पूर्णांक pch_gbe_set_wol(काष्ठा net_device *netdev,
				काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);

	अगर ((wol->wolopts & (WAKE_PHY | WAKE_ARP | WAKE_MAGICSECURE)))
		वापस -EOPNOTSUPP;
	/* these settings will always override what we currently have */
	adapter->wake_up_evt = 0;

	अगर ((wol->wolopts & WAKE_UCAST))
		adapter->wake_up_evt |= PCH_GBE_WLC_IND;
	अगर ((wol->wolopts & WAKE_MCAST))
		adapter->wake_up_evt |= PCH_GBE_WLC_MLT;
	अगर ((wol->wolopts & WAKE_BCAST))
		adapter->wake_up_evt |= PCH_GBE_WLC_BR;
	अगर ((wol->wolopts & WAKE_MAGIC))
		adapter->wake_up_evt |= PCH_GBE_WLC_MP;
	वापस 0;
पूर्ण

/**
 * pch_gbe_nway_reset - Restart स्वतःnegotiation
 * @netdev: Network पूर्णांकerface device काष्ठाure
 * Returns:
 *	0:			Successful.
 *	Negative value:		Failed.
 */
अटल पूर्णांक pch_gbe_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);

	वापस mii_nway_restart(&adapter->mii);
पूर्ण

/**
 * pch_gbe_get_ringparam - Report ring sizes
 * @netdev:  Network पूर्णांकerface device काष्ठाure
 * @ring:    Ring param काष्ठाure
 */
अटल व्योम pch_gbe_get_ringparam(काष्ठा net_device *netdev,
					काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_tx_ring *txdr = adapter->tx_ring;
	काष्ठा pch_gbe_rx_ring *rxdr = adapter->rx_ring;

	ring->rx_max_pending = PCH_GBE_MAX_RXD;
	ring->tx_max_pending = PCH_GBE_MAX_TXD;
	ring->rx_pending = rxdr->count;
	ring->tx_pending = txdr->count;
पूर्ण

/**
 * pch_gbe_set_ringparam - Set ring sizes
 * @netdev:  Network पूर्णांकerface device काष्ठाure
 * @ring:    Ring param काष्ठाure
 * Returns
 *	0:			Successful.
 *	Negative value:		Failed.
 */
अटल पूर्णांक pch_gbe_set_ringparam(काष्ठा net_device *netdev,
					काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_tx_ring *txdr, *tx_old;
	काष्ठा pch_gbe_rx_ring *rxdr, *rx_old;
	पूर्णांक tx_ring_size, rx_ring_size;
	पूर्णांक err = 0;

	अगर ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		वापस -EINVAL;
	tx_ring_size = (पूर्णांक)माप(काष्ठा pch_gbe_tx_ring);
	rx_ring_size = (पूर्णांक)माप(काष्ठा pch_gbe_rx_ring);

	अगर ((netअगर_running(adapter->netdev)))
		pch_gbe_करोwn(adapter);
	tx_old = adapter->tx_ring;
	rx_old = adapter->rx_ring;

	txdr = kzalloc(tx_ring_size, GFP_KERNEL);
	अगर (!txdr) अणु
		err = -ENOMEM;
		जाओ err_alloc_tx;
	पूर्ण
	rxdr = kzalloc(rx_ring_size, GFP_KERNEL);
	अगर (!rxdr) अणु
		err = -ENOMEM;
		जाओ err_alloc_rx;
	पूर्ण
	adapter->tx_ring = txdr;
	adapter->rx_ring = rxdr;

	rxdr->count =
		clamp_val(ring->rx_pending, PCH_GBE_MIN_RXD, PCH_GBE_MAX_RXD);
	rxdr->count = roundup(rxdr->count, PCH_GBE_RX_DESC_MULTIPLE);

	txdr->count =
		clamp_val(ring->tx_pending, PCH_GBE_MIN_RXD, PCH_GBE_MAX_RXD);
	txdr->count = roundup(txdr->count, PCH_GBE_TX_DESC_MULTIPLE);

	अगर ((netअगर_running(adapter->netdev))) अणु
		/* Try to get new resources beक्रमe deleting old */
		err = pch_gbe_setup_rx_resources(adapter, adapter->rx_ring);
		अगर (err)
			जाओ err_setup_rx;
		err = pch_gbe_setup_tx_resources(adapter, adapter->tx_ring);
		अगर (err)
			जाओ err_setup_tx;
		pch_gbe_मुक्त_rx_resources(adapter, rx_old);
		pch_gbe_मुक्त_tx_resources(adapter, tx_old);
		kमुक्त(tx_old);
		kमुक्त(rx_old);
		adapter->rx_ring = rxdr;
		adapter->tx_ring = txdr;
		err = pch_gbe_up(adapter);
	पूर्ण
	वापस err;

err_setup_tx:
	pch_gbe_मुक्त_rx_resources(adapter, adapter->rx_ring);
err_setup_rx:
	adapter->rx_ring = rx_old;
	adapter->tx_ring = tx_old;
	kमुक्त(rxdr);
err_alloc_rx:
	kमुक्त(txdr);
err_alloc_tx:
	अगर (netअगर_running(adapter->netdev))
		pch_gbe_up(adapter);
	वापस err;
पूर्ण

/**
 * pch_gbe_get_छोड़ोparam - Report छोड़ो parameters
 * @netdev:  Network पूर्णांकerface device काष्ठाure
 * @छोड़ो:   Pause parameters काष्ठाure
 */
अटल व्योम pch_gbe_get_छोड़ोparam(काष्ठा net_device *netdev,
				       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_hw *hw = &adapter->hw;

	छोड़ो->स्वतःneg =
	    ((hw->mac.fc_स्वतःneg) ? AUTONEG_ENABLE : AUTONEG_DISABLE);

	अगर (hw->mac.fc == PCH_GBE_FC_RX_PAUSE) अणु
		छोड़ो->rx_छोड़ो = 1;
	पूर्ण अन्यथा अगर (hw->mac.fc == PCH_GBE_FC_TX_PAUSE) अणु
		छोड़ो->tx_छोड़ो = 1;
	पूर्ण अन्यथा अगर (hw->mac.fc == PCH_GBE_FC_FULL) अणु
		छोड़ो->rx_छोड़ो = 1;
		छोड़ो->tx_छोड़ो = 1;
	पूर्ण
पूर्ण

/**
 * pch_gbe_set_छोड़ोparam - Set छोड़ो parameters
 * @netdev:  Network पूर्णांकerface device काष्ठाure
 * @छोड़ो:   Pause parameters काष्ठाure
 * Returns:
 *	0:			Successful.
 *	Negative value:		Failed.
 */
अटल पूर्णांक pch_gbe_set_छोड़ोparam(काष्ठा net_device *netdev,
				       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	पूर्णांक ret = 0;

	hw->mac.fc_स्वतःneg = छोड़ो->स्वतःneg;
	अगर ((छोड़ो->rx_छोड़ो) && (छोड़ो->tx_छोड़ो))
		hw->mac.fc = PCH_GBE_FC_FULL;
	अन्यथा अगर ((छोड़ो->rx_छोड़ो) && (!छोड़ो->tx_छोड़ो))
		hw->mac.fc = PCH_GBE_FC_RX_PAUSE;
	अन्यथा अगर ((!छोड़ो->rx_छोड़ो) && (छोड़ो->tx_छोड़ो))
		hw->mac.fc = PCH_GBE_FC_TX_PAUSE;
	अन्यथा अगर ((!छोड़ो->rx_छोड़ो) && (!छोड़ो->tx_छोड़ो))
		hw->mac.fc = PCH_GBE_FC_NONE;

	अगर (hw->mac.fc_स्वतःneg == AUTONEG_ENABLE) अणु
		अगर ((netअगर_running(adapter->netdev))) अणु
			pch_gbe_करोwn(adapter);
			ret = pch_gbe_up(adapter);
		पूर्ण अन्यथा अणु
			pch_gbe_reset(adapter);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = pch_gbe_mac_क्रमce_mac_fc(hw);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * pch_gbe_get_strings - Return a set of strings that describe the requested
 *			 objects
 * @netdev:    Network पूर्णांकerface device काष्ठाure
 * @stringset: Select the stringset. [ETH_SS_TEST] [ETH_SS_STATS]
 * @data:      Poपूर्णांकer of पढ़ो string data.
 */
अटल व्योम pch_gbe_get_strings(काष्ठा net_device *netdev, u32 stringset,
					u8 *data)
अणु
	u8 *p = data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल (u32) ETH_SS_STATS:
		क्रम (i = 0; i < PCH_GBE_GLOBAL_STATS_LEN; i++) अणु
			स_नकल(p, pch_gbe_gstrings_stats[i].string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/**
 * pch_gbe_get_ethtool_stats - Return statistics about the device
 * @netdev: Network पूर्णांकerface device काष्ठाure
 * @stats:  Ethtool statue काष्ठाure
 * @data:   Poपूर्णांकer of पढ़ो status area
 */
अटल व्योम pch_gbe_get_ethtool_stats(काष्ठा net_device *netdev,
				  काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा pch_gbe_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i;
	स्थिर काष्ठा pch_gbe_stats *gstats = pch_gbe_gstrings_stats;
	अक्षर *hw_stats = (अक्षर *)&adapter->stats;

	pch_gbe_update_stats(adapter);
	क्रम (i = 0; i < PCH_GBE_GLOBAL_STATS_LEN; i++) अणु
		अक्षर *p = hw_stats + gstats->offset;
		data[i] = gstats->size == माप(u64) ? *(u64 *)p:(*(u32 *)p);
		gstats++;
	पूर्ण
पूर्ण

अटल पूर्णांक pch_gbe_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस PCH_GBE_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ethtool_ops pch_gbe_ethtool_ops = अणु
	.get_drvinfo = pch_gbe_get_drvinfo,
	.get_regs_len = pch_gbe_get_regs_len,
	.get_regs = pch_gbe_get_regs,
	.get_wol = pch_gbe_get_wol,
	.set_wol = pch_gbe_set_wol,
	.nway_reset = pch_gbe_nway_reset,
	.get_link = ethtool_op_get_link,
	.get_ringparam = pch_gbe_get_ringparam,
	.set_ringparam = pch_gbe_set_ringparam,
	.get_छोड़ोparam = pch_gbe_get_छोड़ोparam,
	.set_छोड़ोparam = pch_gbe_set_छोड़ोparam,
	.get_strings = pch_gbe_get_strings,
	.get_ethtool_stats = pch_gbe_get_ethtool_stats,
	.get_sset_count = pch_gbe_get_sset_count,
	.get_link_ksettings = pch_gbe_get_link_ksettings,
	.set_link_ksettings = pch_gbe_set_link_ksettings,
पूर्ण;

व्योम pch_gbe_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &pch_gbe_ethtool_ops;
पूर्ण
