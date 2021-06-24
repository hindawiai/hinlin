<शैली गुरु>
/* Synopsys DesignWare Core Enterprise Ethernet (XLGMAC) Driver
 *
 * Copyright (c) 2017 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is dual-licensed; you may select either version 2 of
 * the GNU General Public License ("GPL") or BSD license ("BSD").
 *
 * This Synopsys DWC XLGMAC software driver and associated करोcumentation
 * (hereinafter the "Software") is an unsupported proprietary work of
 * Synopsys, Inc. unless otherwise expressly agreed to in writing between
 * Synopsys and you. The Software IS NOT an item of Licensed Software or a
 * Licensed Product under any End User Software License Agreement or
 * Agreement क्रम Licensed Products with Synopsys or any supplement thereto.
 * Synopsys is a रेजिस्टरed trademark of Synopsys, Inc. Other names included
 * in the SOFTWARE may be the trademarks of their respective owners.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "dwc-xlgmac.h"
#समावेश "dwc-xlgmac-reg.h"

MODULE_LICENSE("Dual BSD/GPL");

अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "DWC ethernet debug level (0=none,...,16=all)");
अटल स्थिर u32 शेष_msg_level = (NETIF_MSG_LINK | NETIF_MSG_IFDOWN |
				      NETIF_MSG_IFUP);

अटल अचिन्हित अक्षर dev_addr[6] = अणु0, 0x55, 0x7b, 0xb5, 0x7d, 0xf7पूर्ण;

अटल व्योम xlgmac_पढ़ो_mac_addr(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा net_device *netdev = pdata->netdev;

	/* Currently it uses a अटल mac address क्रम test */
	स_नकल(pdata->mac_addr, dev_addr, netdev->addr_len);
पूर्ण

अटल व्योम xlgmac_शेष_config(काष्ठा xlgmac_pdata *pdata)
अणु
	pdata->tx_osp_mode = DMA_OSP_ENABLE;
	pdata->tx_sf_mode = MTL_TSF_ENABLE;
	pdata->rx_sf_mode = MTL_RSF_DISABLE;
	pdata->pblx8 = DMA_PBL_X8_ENABLE;
	pdata->tx_pbl = DMA_PBL_32;
	pdata->rx_pbl = DMA_PBL_32;
	pdata->tx_threshold = MTL_TX_THRESHOLD_128;
	pdata->rx_threshold = MTL_RX_THRESHOLD_128;
	pdata->tx_छोड़ो = 1;
	pdata->rx_छोड़ो = 1;
	pdata->phy_speed = SPEED_25000;
	pdata->sysclk_rate = XLGMAC_SYSCLOCK;

	strlcpy(pdata->drv_name, XLGMAC_DRV_NAME, माप(pdata->drv_name));
	strlcpy(pdata->drv_ver, XLGMAC_DRV_VERSION, माप(pdata->drv_ver));
पूर्ण

अटल व्योम xlgmac_init_all_ops(काष्ठा xlgmac_pdata *pdata)
अणु
	xlgmac_init_desc_ops(&pdata->desc_ops);
	xlgmac_init_hw_ops(&pdata->hw_ops);
पूर्ण

अटल पूर्णांक xlgmac_init(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_hw_ops *hw_ops = &pdata->hw_ops;
	काष्ठा net_device *netdev = pdata->netdev;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Set शेष configuration data */
	xlgmac_शेष_config(pdata);

	/* Set irq, base_addr, MAC address, */
	netdev->irq = pdata->dev_irq;
	netdev->base_addr = (अचिन्हित दीर्घ)pdata->mac_regs;
	xlgmac_पढ़ो_mac_addr(pdata);
	स_नकल(netdev->dev_addr, pdata->mac_addr, netdev->addr_len);

	/* Set all the function poपूर्णांकers */
	xlgmac_init_all_ops(pdata);

	/* Issue software reset to device */
	hw_ops->निकास(pdata);

	/* Populate the hardware features */
	xlgmac_get_all_hw_features(pdata);
	xlgmac_prपूर्णांक_all_hw_features(pdata);

	/* TODO: Set the PHY mode to XLGMII */

	/* Set the DMA mask */
	ret = dma_set_mask_and_coherent(pdata->dev,
					DMA_BIT_MASK(pdata->hw_feat.dma_width));
	अगर (ret) अणु
		dev_err(pdata->dev, "dma_set_mask_and_coherent failed\n");
		वापस ret;
	पूर्ण

	/* Channel and ring params initializtion
	 *  pdata->channel_count;
	 *  pdata->tx_ring_count;
	 *  pdata->rx_ring_count;
	 *  pdata->tx_desc_count;
	 *  pdata->rx_desc_count;
	 */
	BUILD_BUG_ON_NOT_POWER_OF_2(XLGMAC_TX_DESC_CNT);
	pdata->tx_desc_count = XLGMAC_TX_DESC_CNT;
	अगर (pdata->tx_desc_count & (pdata->tx_desc_count - 1)) अणु
		dev_err(pdata->dev, "tx descriptor count (%d) is not valid\n",
			pdata->tx_desc_count);
		ret = -EINVAL;
		वापस ret;
	पूर्ण
	BUILD_BUG_ON_NOT_POWER_OF_2(XLGMAC_RX_DESC_CNT);
	pdata->rx_desc_count = XLGMAC_RX_DESC_CNT;
	अगर (pdata->rx_desc_count & (pdata->rx_desc_count - 1)) अणु
		dev_err(pdata->dev, "rx descriptor count (%d) is not valid\n",
			pdata->rx_desc_count);
		ret = -EINVAL;
		वापस ret;
	पूर्ण

	pdata->tx_ring_count = min_t(अचिन्हित पूर्णांक, num_online_cpus(),
				     pdata->hw_feat.tx_ch_cnt);
	pdata->tx_ring_count = min_t(अचिन्हित पूर्णांक, pdata->tx_ring_count,
				     pdata->hw_feat.tx_q_cnt);
	pdata->tx_q_count = pdata->tx_ring_count;
	ret = netअगर_set_real_num_tx_queues(netdev, pdata->tx_q_count);
	अगर (ret) अणु
		dev_err(pdata->dev, "error setting real tx queue count\n");
		वापस ret;
	पूर्ण

	pdata->rx_ring_count = min_t(अचिन्हित पूर्णांक,
				     netअगर_get_num_शेष_rss_queues(),
				     pdata->hw_feat.rx_ch_cnt);
	pdata->rx_ring_count = min_t(अचिन्हित पूर्णांक, pdata->rx_ring_count,
				     pdata->hw_feat.rx_q_cnt);
	pdata->rx_q_count = pdata->rx_ring_count;
	ret = netअगर_set_real_num_rx_queues(netdev, pdata->rx_q_count);
	अगर (ret) अणु
		dev_err(pdata->dev, "error setting real rx queue count\n");
		वापस ret;
	पूर्ण

	pdata->channel_count =
		max_t(अचिन्हित पूर्णांक, pdata->tx_ring_count, pdata->rx_ring_count);

	/* Initialize RSS hash key and lookup table */
	netdev_rss_key_fill(pdata->rss_key, माप(pdata->rss_key));

	क्रम (i = 0; i < XLGMAC_RSS_MAX_TABLE_SIZE; i++)
		pdata->rss_table[i] = XLGMAC_SET_REG_BITS(
					pdata->rss_table[i],
					MAC_RSSDR_DMCH_POS,
					MAC_RSSDR_DMCH_LEN,
					i % pdata->rx_ring_count);

	pdata->rss_options = XLGMAC_SET_REG_BITS(
				pdata->rss_options,
				MAC_RSSCR_IP2TE_POS,
				MAC_RSSCR_IP2TE_LEN, 1);
	pdata->rss_options = XLGMAC_SET_REG_BITS(
				pdata->rss_options,
				MAC_RSSCR_TCP4TE_POS,
				MAC_RSSCR_TCP4TE_LEN, 1);
	pdata->rss_options = XLGMAC_SET_REG_BITS(
				pdata->rss_options,
				MAC_RSSCR_UDP4TE_POS,
				MAC_RSSCR_UDP4TE_LEN, 1);

	/* Set device operations */
	netdev->netdev_ops = xlgmac_get_netdev_ops();
	netdev->ethtool_ops = xlgmac_get_ethtool_ops();

	/* Set device features */
	अगर (pdata->hw_feat.tso) अणु
		netdev->hw_features = NETIF_F_TSO;
		netdev->hw_features |= NETIF_F_TSO6;
		netdev->hw_features |= NETIF_F_SG;
		netdev->hw_features |= NETIF_F_IP_CSUM;
		netdev->hw_features |= NETIF_F_IPV6_CSUM;
	पूर्ण अन्यथा अगर (pdata->hw_feat.tx_coe) अणु
		netdev->hw_features = NETIF_F_IP_CSUM;
		netdev->hw_features |= NETIF_F_IPV6_CSUM;
	पूर्ण

	अगर (pdata->hw_feat.rx_coe) अणु
		netdev->hw_features |= NETIF_F_RXCSUM;
		netdev->hw_features |= NETIF_F_GRO;
	पूर्ण

	अगर (pdata->hw_feat.rss)
		netdev->hw_features |= NETIF_F_RXHASH;

	netdev->vlan_features |= netdev->hw_features;

	netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_RX;
	अगर (pdata->hw_feat.sa_vlan_ins)
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_TX;
	अगर (pdata->hw_feat.vlhash)
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	netdev->features |= netdev->hw_features;
	pdata->netdev_features = netdev->features;

	netdev->priv_flags |= IFF_UNICAST_FLT;

	/* Use शेष watchकरोg समयout */
	netdev->watchकरोg_समयo = 0;

	/* Tx coalesce parameters initialization */
	pdata->tx_usecs = XLGMAC_INIT_DMA_TX_USECS;
	pdata->tx_frames = XLGMAC_INIT_DMA_TX_FRAMES;

	/* Rx coalesce parameters initialization */
	pdata->rx_riwt = hw_ops->usec_to_riwt(pdata, XLGMAC_INIT_DMA_RX_USECS);
	pdata->rx_usecs = XLGMAC_INIT_DMA_RX_USECS;
	pdata->rx_frames = XLGMAC_INIT_DMA_RX_FRAMES;

	वापस 0;
पूर्ण

पूर्णांक xlgmac_drv_probe(काष्ठा device *dev, काष्ठा xlgmac_resources *res)
अणु
	काष्ठा xlgmac_pdata *pdata;
	काष्ठा net_device *netdev;
	पूर्णांक ret;

	netdev = alloc_etherdev_mq(माप(काष्ठा xlgmac_pdata),
				   XLGMAC_MAX_DMA_CHANNELS);

	अगर (!netdev) अणु
		dev_err(dev, "alloc_etherdev failed\n");
		वापस -ENOMEM;
	पूर्ण

	SET_NETDEV_DEV(netdev, dev);
	dev_set_drvdata(dev, netdev);
	pdata = netdev_priv(netdev);
	pdata->dev = dev;
	pdata->netdev = netdev;

	pdata->dev_irq = res->irq;
	pdata->mac_regs = res->addr;

	mutex_init(&pdata->rss_mutex);
	pdata->msg_enable = netअगर_msg_init(debug, शेष_msg_level);

	ret = xlgmac_init(pdata);
	अगर (ret) अणु
		dev_err(dev, "xlgmac init failed\n");
		जाओ err_मुक्त_netdev;
	पूर्ण

	ret = रेजिस्टर_netdev(netdev);
	अगर (ret) अणु
		dev_err(dev, "net device registration failed\n");
		जाओ err_मुक्त_netdev;
	पूर्ण

	वापस 0;

err_मुक्त_netdev:
	मुक्त_netdev(netdev);

	वापस ret;
पूर्ण

पूर्णांक xlgmac_drv_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);

	unरेजिस्टर_netdev(netdev);
	मुक्त_netdev(netdev);

	वापस 0;
पूर्ण

व्योम xlgmac_dump_tx_desc(काष्ठा xlgmac_pdata *pdata,
			 काष्ठा xlgmac_ring *ring,
			 अचिन्हित पूर्णांक idx,
			 अचिन्हित पूर्णांक count,
			 अचिन्हित पूर्णांक flag)
अणु
	काष्ठा xlgmac_desc_data *desc_data;
	काष्ठा xlgmac_dma_desc *dma_desc;

	जबतक (count--) अणु
		desc_data = XLGMAC_GET_DESC_DATA(ring, idx);
		dma_desc = desc_data->dma_desc;

		netdev_dbg(pdata->netdev, "TX: dma_desc=%p, dma_desc_addr=%pad\n",
			   desc_data->dma_desc, &desc_data->dma_desc_addr);
		netdev_dbg(pdata->netdev,
			   "TX_NORMAL_DESC[%d %s] = %08x:%08x:%08x:%08x\n", idx,
			   (flag == 1) ? "QUEUED FOR TX" : "TX BY DEVICE",
			   le32_to_cpu(dma_desc->desc0),
			   le32_to_cpu(dma_desc->desc1),
			   le32_to_cpu(dma_desc->desc2),
			   le32_to_cpu(dma_desc->desc3));

		idx++;
	पूर्ण
पूर्ण

व्योम xlgmac_dump_rx_desc(काष्ठा xlgmac_pdata *pdata,
			 काष्ठा xlgmac_ring *ring,
			 अचिन्हित पूर्णांक idx)
अणु
	काष्ठा xlgmac_desc_data *desc_data;
	काष्ठा xlgmac_dma_desc *dma_desc;

	desc_data = XLGMAC_GET_DESC_DATA(ring, idx);
	dma_desc = desc_data->dma_desc;

	netdev_dbg(pdata->netdev, "RX: dma_desc=%p, dma_desc_addr=%pad\n",
		   desc_data->dma_desc, &desc_data->dma_desc_addr);
	netdev_dbg(pdata->netdev,
		   "RX_NORMAL_DESC[%d RX BY DEVICE] = %08x:%08x:%08x:%08x\n",
		   idx,
		   le32_to_cpu(dma_desc->desc0),
		   le32_to_cpu(dma_desc->desc1),
		   le32_to_cpu(dma_desc->desc2),
		   le32_to_cpu(dma_desc->desc3));
पूर्ण

व्योम xlgmac_prपूर्णांक_pkt(काष्ठा net_device *netdev,
		      काष्ठा sk_buff *skb, bool tx_rx)
अणु
	काष्ठा ethhdr *eth = (काष्ठा ethhdr *)skb->data;
	अचिन्हित अक्षर buffer[128];
	अचिन्हित पूर्णांक i;

	netdev_dbg(netdev, "\n************** SKB dump ****************\n");

	netdev_dbg(netdev, "%s packet of %d bytes\n",
		   (tx_rx ? "TX" : "RX"), skb->len);

	netdev_dbg(netdev, "Dst MAC addr: %pM\n", eth->h_dest);
	netdev_dbg(netdev, "Src MAC addr: %pM\n", eth->h_source);
	netdev_dbg(netdev, "Protocol: %#06hx\n", ntohs(eth->h_proto));

	क्रम (i = 0; i < skb->len; i += 32) अणु
		अचिन्हित पूर्णांक len = min(skb->len - i, 32U);

		hex_dump_to_buffer(&skb->data[i], len, 32, 1,
				   buffer, माप(buffer), false);
		netdev_dbg(netdev, "  %#06x: %s\n", i, buffer);
	पूर्ण

	netdev_dbg(netdev, "\n************** SKB dump ****************\n");
पूर्ण

व्योम xlgmac_get_all_hw_features(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_hw_features *hw_feat = &pdata->hw_feat;
	अचिन्हित पूर्णांक mac_hfr0, mac_hfr1, mac_hfr2;

	mac_hfr0 = पढ़ोl(pdata->mac_regs + MAC_HWF0R);
	mac_hfr1 = पढ़ोl(pdata->mac_regs + MAC_HWF1R);
	mac_hfr2 = पढ़ोl(pdata->mac_regs + MAC_HWF2R);

	स_रखो(hw_feat, 0, माप(*hw_feat));

	hw_feat->version = पढ़ोl(pdata->mac_regs + MAC_VR);

	/* Hardware feature रेजिस्टर 0 */
	hw_feat->phyअगरsel    = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_PHYIFSEL_POS,
						MAC_HWF0R_PHYIFSEL_LEN);
	hw_feat->vlhash      = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_VLHASH_POS,
						MAC_HWF0R_VLHASH_LEN);
	hw_feat->sma         = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_SMASEL_POS,
						MAC_HWF0R_SMASEL_LEN);
	hw_feat->rwk         = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_RWKSEL_POS,
						MAC_HWF0R_RWKSEL_LEN);
	hw_feat->mgk         = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_MGKSEL_POS,
						MAC_HWF0R_MGKSEL_LEN);
	hw_feat->mmc         = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_MMCSEL_POS,
						MAC_HWF0R_MMCSEL_LEN);
	hw_feat->aoe         = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_ARPOFFSEL_POS,
						MAC_HWF0R_ARPOFFSEL_LEN);
	hw_feat->ts          = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_TSSEL_POS,
						MAC_HWF0R_TSSEL_LEN);
	hw_feat->eee         = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_EEESEL_POS,
						MAC_HWF0R_EEESEL_LEN);
	hw_feat->tx_coe      = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_TXCOESEL_POS,
						MAC_HWF0R_TXCOESEL_LEN);
	hw_feat->rx_coe      = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_RXCOESEL_POS,
						MAC_HWF0R_RXCOESEL_LEN);
	hw_feat->addn_mac    = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_ADDMACADRSEL_POS,
						MAC_HWF0R_ADDMACADRSEL_LEN);
	hw_feat->ts_src      = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_TSSTSSEL_POS,
						MAC_HWF0R_TSSTSSEL_LEN);
	hw_feat->sa_vlan_ins = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_SAVLANINS_POS,
						MAC_HWF0R_SAVLANINS_LEN);

	/* Hardware feature रेजिस्टर 1 */
	hw_feat->rx_fअगरo_size  = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_RXFIFOSIZE_POS,
						MAC_HWF1R_RXFIFOSIZE_LEN);
	hw_feat->tx_fअगरo_size  = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_TXFIFOSIZE_POS,
						MAC_HWF1R_TXFIFOSIZE_LEN);
	hw_feat->adv_ts_hi     = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_ADVTHWORD_POS,
						MAC_HWF1R_ADVTHWORD_LEN);
	hw_feat->dma_width     = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_ADDR64_POS,
						MAC_HWF1R_ADDR64_LEN);
	hw_feat->dcb           = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_DCBEN_POS,
						MAC_HWF1R_DCBEN_LEN);
	hw_feat->sph           = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_SPHEN_POS,
						MAC_HWF1R_SPHEN_LEN);
	hw_feat->tso           = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_TSOEN_POS,
						MAC_HWF1R_TSOEN_LEN);
	hw_feat->dma_debug     = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_DBGMEMA_POS,
						MAC_HWF1R_DBGMEMA_LEN);
	hw_feat->rss           = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_RSSEN_POS,
						MAC_HWF1R_RSSEN_LEN);
	hw_feat->tc_cnt	       = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_NUMTC_POS,
						MAC_HWF1R_NUMTC_LEN);
	hw_feat->hash_table_size = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_HASHTBLSZ_POS,
						MAC_HWF1R_HASHTBLSZ_LEN);
	hw_feat->l3l4_filter_num = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_L3L4FNUM_POS,
						MAC_HWF1R_L3L4FNUM_LEN);

	/* Hardware feature रेजिस्टर 2 */
	hw_feat->rx_q_cnt     = XLGMAC_GET_REG_BITS(mac_hfr2,
						MAC_HWF2R_RXQCNT_POS,
						MAC_HWF2R_RXQCNT_LEN);
	hw_feat->tx_q_cnt     = XLGMAC_GET_REG_BITS(mac_hfr2,
						MAC_HWF2R_TXQCNT_POS,
						MAC_HWF2R_TXQCNT_LEN);
	hw_feat->rx_ch_cnt    = XLGMAC_GET_REG_BITS(mac_hfr2,
						MAC_HWF2R_RXCHCNT_POS,
						MAC_HWF2R_RXCHCNT_LEN);
	hw_feat->tx_ch_cnt    = XLGMAC_GET_REG_BITS(mac_hfr2,
						MAC_HWF2R_TXCHCNT_POS,
						MAC_HWF2R_TXCHCNT_LEN);
	hw_feat->pps_out_num  = XLGMAC_GET_REG_BITS(mac_hfr2,
						MAC_HWF2R_PPSOUTNUM_POS,
						MAC_HWF2R_PPSOUTNUM_LEN);
	hw_feat->aux_snap_num = XLGMAC_GET_REG_BITS(mac_hfr2,
						MAC_HWF2R_AUXSNAPNUM_POS,
						MAC_HWF2R_AUXSNAPNUM_LEN);

	/* Translate the Hash Table size पूर्णांकo actual number */
	चयन (hw_feat->hash_table_size) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		hw_feat->hash_table_size = 64;
		अवरोध;
	हाल 2:
		hw_feat->hash_table_size = 128;
		अवरोध;
	हाल 3:
		hw_feat->hash_table_size = 256;
		अवरोध;
	पूर्ण

	/* Translate the address width setting पूर्णांकo actual number */
	चयन (hw_feat->dma_width) अणु
	हाल 0:
		hw_feat->dma_width = 32;
		अवरोध;
	हाल 1:
		hw_feat->dma_width = 40;
		अवरोध;
	हाल 2:
		hw_feat->dma_width = 48;
		अवरोध;
	शेष:
		hw_feat->dma_width = 32;
	पूर्ण

	/* The Queue, Channel and TC counts are zero based so increment them
	 * to get the actual number
	 */
	hw_feat->rx_q_cnt++;
	hw_feat->tx_q_cnt++;
	hw_feat->rx_ch_cnt++;
	hw_feat->tx_ch_cnt++;
	hw_feat->tc_cnt++;
पूर्ण

व्योम xlgmac_prपूर्णांक_all_hw_features(काष्ठा xlgmac_pdata *pdata)
अणु
	अक्षर __maybe_unused *str = शून्य;

	XLGMAC_PR("\n");
	XLGMAC_PR("=====================================================\n");
	XLGMAC_PR("\n");
	XLGMAC_PR("HW support following features\n");
	XLGMAC_PR("\n");
	/* HW Feature Register0 */
	XLGMAC_PR("VLAN Hash Filter Selected                   : %s\n",
		  pdata->hw_feat.vlhash ? "YES" : "NO");
	XLGMAC_PR("SMA (MDIO) Interface                        : %s\n",
		  pdata->hw_feat.sma ? "YES" : "NO");
	XLGMAC_PR("PMT Remote Wake-up Packet Enable            : %s\n",
		  pdata->hw_feat.rwk ? "YES" : "NO");
	XLGMAC_PR("PMT Magic Packet Enable                     : %s\n",
		  pdata->hw_feat.mgk ? "YES" : "NO");
	XLGMAC_PR("RMON/MMC Module Enable                      : %s\n",
		  pdata->hw_feat.mmc ? "YES" : "NO");
	XLGMAC_PR("ARP Offload Enabled                         : %s\n",
		  pdata->hw_feat.aoe ? "YES" : "NO");
	XLGMAC_PR("IEEE 1588-2008 Timestamp Enabled            : %s\n",
		  pdata->hw_feat.ts ? "YES" : "NO");
	XLGMAC_PR("Energy Efficient Ethernet Enabled           : %s\n",
		  pdata->hw_feat.eee ? "YES" : "NO");
	XLGMAC_PR("Transmit Checksum Offload Enabled           : %s\n",
		  pdata->hw_feat.tx_coe ? "YES" : "NO");
	XLGMAC_PR("Receive Checksum Offload Enabled            : %s\n",
		  pdata->hw_feat.rx_coe ? "YES" : "NO");
	XLGMAC_PR("Additional MAC Addresses 1-31 Selected      : %s\n",
		  pdata->hw_feat.addn_mac ? "YES" : "NO");

	चयन (pdata->hw_feat.ts_src) अणु
	हाल 0:
		str = "RESERVED";
		अवरोध;
	हाल 1:
		str = "INTERNAL";
		अवरोध;
	हाल 2:
		str = "EXTERNAL";
		अवरोध;
	हाल 3:
		str = "BOTH";
		अवरोध;
	पूर्ण
	XLGMAC_PR("Timestamp System Time Source                : %s\n", str);

	XLGMAC_PR("Source Address or VLAN Insertion Enable     : %s\n",
		  pdata->hw_feat.sa_vlan_ins ? "YES" : "NO");

	/* HW Feature Register1 */
	चयन (pdata->hw_feat.rx_fअगरo_size) अणु
	हाल 0:
		str = "128 bytes";
		अवरोध;
	हाल 1:
		str = "256 bytes";
		अवरोध;
	हाल 2:
		str = "512 bytes";
		अवरोध;
	हाल 3:
		str = "1 KBytes";
		अवरोध;
	हाल 4:
		str = "2 KBytes";
		अवरोध;
	हाल 5:
		str = "4 KBytes";
		अवरोध;
	हाल 6:
		str = "8 KBytes";
		अवरोध;
	हाल 7:
		str = "16 KBytes";
		अवरोध;
	हाल 8:
		str = "32 kBytes";
		अवरोध;
	हाल 9:
		str = "64 KBytes";
		अवरोध;
	हाल 10:
		str = "128 KBytes";
		अवरोध;
	हाल 11:
		str = "256 KBytes";
		अवरोध;
	शेष:
		str = "RESERVED";
	पूर्ण
	XLGMAC_PR("MTL Receive FIFO Size                       : %s\n", str);

	चयन (pdata->hw_feat.tx_fअगरo_size) अणु
	हाल 0:
		str = "128 bytes";
		अवरोध;
	हाल 1:
		str = "256 bytes";
		अवरोध;
	हाल 2:
		str = "512 bytes";
		अवरोध;
	हाल 3:
		str = "1 KBytes";
		अवरोध;
	हाल 4:
		str = "2 KBytes";
		अवरोध;
	हाल 5:
		str = "4 KBytes";
		अवरोध;
	हाल 6:
		str = "8 KBytes";
		अवरोध;
	हाल 7:
		str = "16 KBytes";
		अवरोध;
	हाल 8:
		str = "32 kBytes";
		अवरोध;
	हाल 9:
		str = "64 KBytes";
		अवरोध;
	हाल 10:
		str = "128 KBytes";
		अवरोध;
	हाल 11:
		str = "256 KBytes";
		अवरोध;
	शेष:
		str = "RESERVED";
	पूर्ण
	XLGMAC_PR("MTL Transmit FIFO Size                      : %s\n", str);

	XLGMAC_PR("IEEE 1588 High Word Register Enable         : %s\n",
		  pdata->hw_feat.adv_ts_hi ? "YES" : "NO");
	XLGMAC_PR("Address width                               : %u\n",
		  pdata->hw_feat.dma_width);
	XLGMAC_PR("DCB Feature Enable                          : %s\n",
		  pdata->hw_feat.dcb ? "YES" : "NO");
	XLGMAC_PR("Split Header Feature Enable                 : %s\n",
		  pdata->hw_feat.sph ? "YES" : "NO");
	XLGMAC_PR("TCP Segmentation Offload Enable             : %s\n",
		  pdata->hw_feat.tso ? "YES" : "NO");
	XLGMAC_PR("DMA Debug Registers Enabled                 : %s\n",
		  pdata->hw_feat.dma_debug ? "YES" : "NO");
	XLGMAC_PR("RSS Feature Enabled                         : %s\n",
		  pdata->hw_feat.rss ? "YES" : "NO");
	XLGMAC_PR("Number of Traffic classes                   : %u\n",
		  (pdata->hw_feat.tc_cnt));
	XLGMAC_PR("Hash Table Size                             : %u\n",
		  pdata->hw_feat.hash_table_size);
	XLGMAC_PR("Total number of L3 or L4 Filters            : %u\n",
		  pdata->hw_feat.l3l4_filter_num);

	/* HW Feature Register2 */
	XLGMAC_PR("Number of MTL Receive Queues                : %u\n",
		  pdata->hw_feat.rx_q_cnt);
	XLGMAC_PR("Number of MTL Transmit Queues               : %u\n",
		  pdata->hw_feat.tx_q_cnt);
	XLGMAC_PR("Number of DMA Receive Channels              : %u\n",
		  pdata->hw_feat.rx_ch_cnt);
	XLGMAC_PR("Number of DMA Transmit Channels             : %u\n",
		  pdata->hw_feat.tx_ch_cnt);

	चयन (pdata->hw_feat.pps_out_num) अणु
	हाल 0:
		str = "No PPS output";
		अवरोध;
	हाल 1:
		str = "1 PPS output";
		अवरोध;
	हाल 2:
		str = "2 PPS output";
		अवरोध;
	हाल 3:
		str = "3 PPS output";
		अवरोध;
	हाल 4:
		str = "4 PPS output";
		अवरोध;
	शेष:
		str = "RESERVED";
	पूर्ण
	XLGMAC_PR("Number of PPS Outputs                       : %s\n", str);

	चयन (pdata->hw_feat.aux_snap_num) अणु
	हाल 0:
		str = "No auxiliary input";
		अवरोध;
	हाल 1:
		str = "1 auxiliary input";
		अवरोध;
	हाल 2:
		str = "2 auxiliary input";
		अवरोध;
	हाल 3:
		str = "3 auxiliary input";
		अवरोध;
	हाल 4:
		str = "4 auxiliary input";
		अवरोध;
	शेष:
		str = "RESERVED";
	पूर्ण
	XLGMAC_PR("Number of Auxiliary Snapshot Inputs         : %s", str);

	XLGMAC_PR("\n");
	XLGMAC_PR("=====================================================\n");
	XLGMAC_PR("\n");
पूर्ण
