<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Faraday FTGMAC100 Gigabit Ethernet
 *
 * (C) Copyright 2009-2011 Faraday Technology
 * Po-Yu Chuang <ratbert@faraday-tech.com>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/crc32.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/of_net.h>
#समावेश <net/ip.h>
#समावेश <net/ncsi.h>

#समावेश "ftgmac100.h"

#घोषणा DRV_NAME	"ftgmac100"

/* Arbitrary values, I am not sure the HW has limits */
#घोषणा MAX_RX_QUEUE_ENTRIES	1024
#घोषणा MAX_TX_QUEUE_ENTRIES	1024
#घोषणा MIN_RX_QUEUE_ENTRIES	32
#घोषणा MIN_TX_QUEUE_ENTRIES	32

/* Defaults */
#घोषणा DEF_RX_QUEUE_ENTRIES	128
#घोषणा DEF_TX_QUEUE_ENTRIES	128

#घोषणा MAX_PKT_SIZE		1536
#घोषणा RX_BUF_SIZE		MAX_PKT_SIZE	/* must be smaller than 0x3fff */

/* Min number of tx ring entries beक्रमe stopping queue */
#घोषणा TX_THRESHOLD		(MAX_SKB_FRAGS + 1)

#घोषणा FTGMAC_100MHZ		100000000
#घोषणा FTGMAC_25MHZ		25000000

काष्ठा ftgmac100 अणु
	/* Registers */
	काष्ठा resource *res;
	व्योम __iomem *base;

	/* Rx ring */
	अचिन्हित पूर्णांक rx_q_entries;
	काष्ठा ftgmac100_rxdes *rxdes;
	dma_addr_t rxdes_dma;
	काष्ठा sk_buff **rx_skbs;
	अचिन्हित पूर्णांक rx_poपूर्णांकer;
	u32 rxdes0_eकरोrr_mask;

	/* Tx ring */
	अचिन्हित पूर्णांक tx_q_entries;
	काष्ठा ftgmac100_txdes *txdes;
	dma_addr_t txdes_dma;
	काष्ठा sk_buff **tx_skbs;
	अचिन्हित पूर्णांक tx_clean_poपूर्णांकer;
	अचिन्हित पूर्णांक tx_poपूर्णांकer;
	u32 txdes0_eकरोtr_mask;

	/* Used to संकेत the reset task of ring change request */
	अचिन्हित पूर्णांक new_rx_q_entries;
	अचिन्हित पूर्णांक new_tx_q_entries;

	/* Scratch page to use when rx skb alloc fails */
	व्योम *rx_scratch;
	dma_addr_t rx_scratch_dma;

	/* Component काष्ठाures */
	काष्ठा net_device *netdev;
	काष्ठा device *dev;
	काष्ठा ncsi_dev *ndev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा work_काष्ठा reset_task;
	काष्ठा mii_bus *mii_bus;
	काष्ठा clk *clk;

	/* AST2500/AST2600 RMII ref घड़ी gate */
	काष्ठा clk *rclk;

	/* Link management */
	पूर्णांक cur_speed;
	पूर्णांक cur_duplex;
	bool use_ncsi;

	/* Multicast filter settings */
	u32 maht0;
	u32 maht1;

	/* Flow control settings */
	bool tx_छोड़ो;
	bool rx_छोड़ो;
	bool aneg_छोड़ो;

	/* Misc */
	bool need_mac_restart;
	bool is_aspeed;
पूर्ण;

अटल पूर्णांक ftgmac100_reset_mac(काष्ठा ftgmac100 *priv, u32 maccr)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	पूर्णांक i;

	/* NOTE: reset clears all रेजिस्टरs */
	ioग_लिखो32(maccr, priv->base + FTGMAC100_OFFSET_MACCR);
	ioग_लिखो32(maccr | FTGMAC100_MACCR_SW_RST,
		  priv->base + FTGMAC100_OFFSET_MACCR);
	क्रम (i = 0; i < 200; i++) अणु
		अचिन्हित पूर्णांक maccr;

		maccr = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_MACCR);
		अगर (!(maccr & FTGMAC100_MACCR_SW_RST))
			वापस 0;

		udelay(1);
	पूर्ण

	netdev_err(netdev, "Hardware reset failed\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक ftgmac100_reset_and_config_mac(काष्ठा ftgmac100 *priv)
अणु
	u32 maccr = 0;

	चयन (priv->cur_speed) अणु
	हाल SPEED_10:
	हाल 0: /* no link */
		अवरोध;

	हाल SPEED_100:
		maccr |= FTGMAC100_MACCR_FAST_MODE;
		अवरोध;

	हाल SPEED_1000:
		maccr |= FTGMAC100_MACCR_GIGA_MODE;
		अवरोध;
	शेष:
		netdev_err(priv->netdev, "Unknown speed %d !\n",
			   priv->cur_speed);
		अवरोध;
	पूर्ण

	/* (Re)initialize the queue poपूर्णांकers */
	priv->rx_poपूर्णांकer = 0;
	priv->tx_clean_poपूर्णांकer = 0;
	priv->tx_poपूर्णांकer = 0;

	/* The करोc says reset twice with 10us पूर्णांकerval */
	अगर (ftgmac100_reset_mac(priv, maccr))
		वापस -EIO;
	usleep_range(10, 1000);
	वापस ftgmac100_reset_mac(priv, maccr);
पूर्ण

अटल व्योम ftgmac100_ग_लिखो_mac_addr(काष्ठा ftgmac100 *priv, स्थिर u8 *mac)
अणु
	अचिन्हित पूर्णांक maddr = mac[0] << 8 | mac[1];
	अचिन्हित पूर्णांक laddr = mac[2] << 24 | mac[3] << 16 | mac[4] << 8 | mac[5];

	ioग_लिखो32(maddr, priv->base + FTGMAC100_OFFSET_MAC_MADR);
	ioग_लिखो32(laddr, priv->base + FTGMAC100_OFFSET_MAC_LADR);
पूर्ण

अटल व्योम ftgmac100_initial_mac(काष्ठा ftgmac100 *priv)
अणु
	u8 mac[ETH_ALEN];
	अचिन्हित पूर्णांक m;
	अचिन्हित पूर्णांक l;
	व्योम *addr;

	addr = device_get_mac_address(priv->dev, mac, ETH_ALEN);
	अगर (addr) अणु
		ether_addr_copy(priv->netdev->dev_addr, mac);
		dev_info(priv->dev, "Read MAC address %pM from device tree\n",
			 mac);
		वापस;
	पूर्ण

	m = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_MAC_MADR);
	l = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_MAC_LADR);

	mac[0] = (m >> 8) & 0xff;
	mac[1] = m & 0xff;
	mac[2] = (l >> 24) & 0xff;
	mac[3] = (l >> 16) & 0xff;
	mac[4] = (l >> 8) & 0xff;
	mac[5] = l & 0xff;

	अगर (is_valid_ether_addr(mac)) अणु
		ether_addr_copy(priv->netdev->dev_addr, mac);
		dev_info(priv->dev, "Read MAC address %pM from chip\n", mac);
	पूर्ण अन्यथा अणु
		eth_hw_addr_अक्रमom(priv->netdev);
		dev_info(priv->dev, "Generated random MAC address %pM\n",
			 priv->netdev->dev_addr);
	पूर्ण
पूर्ण

अटल पूर्णांक ftgmac100_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	पूर्णांक ret;

	ret = eth_prepare_mac_addr_change(dev, p);
	अगर (ret < 0)
		वापस ret;

	eth_commit_mac_addr_change(dev, p);
	ftgmac100_ग_लिखो_mac_addr(netdev_priv(dev), dev->dev_addr);

	वापस 0;
पूर्ण

अटल व्योम ftgmac100_config_छोड़ो(काष्ठा ftgmac100 *priv)
अणु
	u32 fcr = FTGMAC100_FCR_PAUSE_TIME(16);

	/* Throttle tx queue when receiving छोड़ो frames */
	अगर (priv->rx_छोड़ो)
		fcr |= FTGMAC100_FCR_FC_EN;

	/* Enables sending छोड़ो frames when the RX queue is past a
	 * certain threshold.
	 */
	अगर (priv->tx_छोड़ो)
		fcr |= FTGMAC100_FCR_FCTHR_EN;

	ioग_लिखो32(fcr, priv->base + FTGMAC100_OFFSET_FCR);
पूर्ण

अटल व्योम ftgmac100_init_hw(काष्ठा ftgmac100 *priv)
अणु
	u32 reg, rfअगरo_sz, tfअगरo_sz;

	/* Clear stale पूर्णांकerrupts */
	reg = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_ISR);
	ioग_लिखो32(reg, priv->base + FTGMAC100_OFFSET_ISR);

	/* Setup RX ring buffer base */
	ioग_लिखो32(priv->rxdes_dma, priv->base + FTGMAC100_OFFSET_RXR_BADR);

	/* Setup TX ring buffer base */
	ioग_लिखो32(priv->txdes_dma, priv->base + FTGMAC100_OFFSET_NPTXR_BADR);

	/* Configure RX buffer size */
	ioग_लिखो32(FTGMAC100_RBSR_SIZE(RX_BUF_SIZE),
		  priv->base + FTGMAC100_OFFSET_RBSR);

	/* Set RX descriptor स्वतःpoll */
	ioग_लिखो32(FTGMAC100_APTC_RXPOLL_CNT(1),
		  priv->base + FTGMAC100_OFFSET_APTC);

	/* Write MAC address */
	ftgmac100_ग_लिखो_mac_addr(priv, priv->netdev->dev_addr);

	/* Write multicast filter */
	ioग_लिखो32(priv->maht0, priv->base + FTGMAC100_OFFSET_MAHT0);
	ioग_लिखो32(priv->maht1, priv->base + FTGMAC100_OFFSET_MAHT1);

	/* Configure descriptor sizes and increase burst sizes according
	 * to values in Aspeed SDK. The FIFO arbitration is enabled and
	 * the thresholds set based on the recommended values in the
	 * AST2400 specअगरication.
	 */
	ioग_लिखो32(FTGMAC100_DBLAC_RXDES_SIZE(2) |   /* 2*8 bytes RX descs */
		  FTGMAC100_DBLAC_TXDES_SIZE(2) |   /* 2*8 bytes TX descs */
		  FTGMAC100_DBLAC_RXBURST_SIZE(3) | /* 512 bytes max RX bursts */
		  FTGMAC100_DBLAC_TXBURST_SIZE(3) | /* 512 bytes max TX bursts */
		  FTGMAC100_DBLAC_RX_THR_EN |       /* Enable fअगरo threshold arb */
		  FTGMAC100_DBLAC_RXFIFO_HTHR(6) |  /* 6/8 of FIFO high threshold */
		  FTGMAC100_DBLAC_RXFIFO_LTHR(2),   /* 2/8 of FIFO low threshold */
		  priv->base + FTGMAC100_OFFSET_DBLAC);

	/* Interrupt mitigation configured क्रम 1 पूर्णांकerrupt/packet. HW पूर्णांकerrupt
	 * mitigation करोesn't seem to provide any benefit with NAPI so leave
	 * it at that.
	 */
	ioग_लिखो32(FTGMAC100_ITC_RXINT_THR(1) |
		  FTGMAC100_ITC_TXINT_THR(1),
		  priv->base + FTGMAC100_OFFSET_ITC);

	/* Configure FIFO sizes in the TPAFCR रेजिस्टर */
	reg = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_FEAR);
	rfअगरo_sz = reg & 0x00000007;
	tfअगरo_sz = (reg >> 3) & 0x00000007;
	reg = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_TPAFCR);
	reg &= ~0x3f000000;
	reg |= (tfअगरo_sz << 27);
	reg |= (rfअगरo_sz << 24);
	ioग_लिखो32(reg, priv->base + FTGMAC100_OFFSET_TPAFCR);
पूर्ण

अटल व्योम ftgmac100_start_hw(काष्ठा ftgmac100 *priv)
अणु
	u32 maccr = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_MACCR);

	/* Keep the original GMAC and FAST bits */
	maccr &= (FTGMAC100_MACCR_FAST_MODE | FTGMAC100_MACCR_GIGA_MODE);

	/* Add all the मुख्य enable bits */
	maccr |= FTGMAC100_MACCR_TXDMA_EN	|
		 FTGMAC100_MACCR_RXDMA_EN	|
		 FTGMAC100_MACCR_TXMAC_EN	|
		 FTGMAC100_MACCR_RXMAC_EN	|
		 FTGMAC100_MACCR_CRC_APD	|
		 FTGMAC100_MACCR_PHY_LINK_LEVEL	|
		 FTGMAC100_MACCR_RX_RUNT	|
		 FTGMAC100_MACCR_RX_BROADPKT;

	/* Add other bits as needed */
	अगर (priv->cur_duplex == DUPLEX_FULL)
		maccr |= FTGMAC100_MACCR_FULLDUP;
	अगर (priv->netdev->flags & IFF_PROMISC)
		maccr |= FTGMAC100_MACCR_RX_ALL;
	अगर (priv->netdev->flags & IFF_ALLMULTI)
		maccr |= FTGMAC100_MACCR_RX_MULTIPKT;
	अन्यथा अगर (netdev_mc_count(priv->netdev))
		maccr |= FTGMAC100_MACCR_HT_MULTI_EN;

	/* Vlan filtering enabled */
	अगर (priv->netdev->features & NETIF_F_HW_VLAN_CTAG_RX)
		maccr |= FTGMAC100_MACCR_RM_VLAN;

	/* Hit the HW */
	ioग_लिखो32(maccr, priv->base + FTGMAC100_OFFSET_MACCR);
पूर्ण

अटल व्योम ftgmac100_stop_hw(काष्ठा ftgmac100 *priv)
अणु
	ioग_लिखो32(0, priv->base + FTGMAC100_OFFSET_MACCR);
पूर्ण

अटल व्योम ftgmac100_calc_mc_hash(काष्ठा ftgmac100 *priv)
अणु
	काष्ठा netdev_hw_addr *ha;

	priv->maht1 = 0;
	priv->maht0 = 0;
	netdev_क्रम_each_mc_addr(ha, priv->netdev) अणु
		u32 crc_val = ether_crc_le(ETH_ALEN, ha->addr);

		crc_val = (~(crc_val >> 2)) & 0x3f;
		अगर (crc_val >= 32)
			priv->maht1 |= 1ul << (crc_val - 32);
		अन्यथा
			priv->maht0 |= 1ul << (crc_val);
	पूर्ण
पूर्ण

अटल व्योम ftgmac100_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);

	/* Setup the hash filter */
	ftgmac100_calc_mc_hash(priv);

	/* Interface करोwn ? that's all there is to करो */
	अगर (!netअगर_running(netdev))
		वापस;

	/* Update the HW */
	ioग_लिखो32(priv->maht0, priv->base + FTGMAC100_OFFSET_MAHT0);
	ioग_लिखो32(priv->maht1, priv->base + FTGMAC100_OFFSET_MAHT1);

	/* Reconfigure MACCR */
	ftgmac100_start_hw(priv);
पूर्ण

अटल पूर्णांक ftgmac100_alloc_rx_buf(काष्ठा ftgmac100 *priv, अचिन्हित पूर्णांक entry,
				  काष्ठा ftgmac100_rxdes *rxdes, gfp_t gfp)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा sk_buff *skb;
	dma_addr_t map;
	पूर्णांक err = 0;

	skb = netdev_alloc_skb_ip_align(netdev, RX_BUF_SIZE);
	अगर (unlikely(!skb)) अणु
		अगर (net_ratelimit())
			netdev_warn(netdev, "failed to allocate rx skb\n");
		err = -ENOMEM;
		map = priv->rx_scratch_dma;
	पूर्ण अन्यथा अणु
		map = dma_map_single(priv->dev, skb->data, RX_BUF_SIZE,
				     DMA_FROM_DEVICE);
		अगर (unlikely(dma_mapping_error(priv->dev, map))) अणु
			अगर (net_ratelimit())
				netdev_err(netdev, "failed to map rx page\n");
			dev_kमुक्त_skb_any(skb);
			map = priv->rx_scratch_dma;
			skb = शून्य;
			err = -ENOMEM;
		पूर्ण
	पूर्ण

	/* Store skb */
	priv->rx_skbs[entry] = skb;

	/* Store DMA address पूर्णांकo RX desc */
	rxdes->rxdes3 = cpu_to_le32(map);

	/* Ensure the above is ordered vs clearing the OWN bit */
	dma_wmb();

	/* Clean status (which resets own bit) */
	अगर (entry == (priv->rx_q_entries - 1))
		rxdes->rxdes0 = cpu_to_le32(priv->rxdes0_eकरोrr_mask);
	अन्यथा
		rxdes->rxdes0 = 0;

	वापस err;
पूर्ण

अटल अचिन्हित पूर्णांक ftgmac100_next_rx_poपूर्णांकer(काष्ठा ftgmac100 *priv,
					      अचिन्हित पूर्णांक poपूर्णांकer)
अणु
	वापस (poपूर्णांकer + 1) & (priv->rx_q_entries - 1);
पूर्ण

अटल व्योम ftgmac100_rx_packet_error(काष्ठा ftgmac100 *priv, u32 status)
अणु
	काष्ठा net_device *netdev = priv->netdev;

	अगर (status & FTGMAC100_RXDES0_RX_ERR)
		netdev->stats.rx_errors++;

	अगर (status & FTGMAC100_RXDES0_CRC_ERR)
		netdev->stats.rx_crc_errors++;

	अगर (status & (FTGMAC100_RXDES0_FTL |
		      FTGMAC100_RXDES0_RUNT |
		      FTGMAC100_RXDES0_RX_ODD_NB))
		netdev->stats.rx_length_errors++;
पूर्ण

अटल bool ftgmac100_rx_packet(काष्ठा ftgmac100 *priv, पूर्णांक *processed)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा ftgmac100_rxdes *rxdes;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक poपूर्णांकer, size;
	u32 status, csum_vlan;
	dma_addr_t map;

	/* Grab next RX descriptor */
	poपूर्णांकer = priv->rx_poपूर्णांकer;
	rxdes = &priv->rxdes[poपूर्णांकer];

	/* Grab descriptor status */
	status = le32_to_cpu(rxdes->rxdes0);

	/* Do we have a packet ? */
	अगर (!(status & FTGMAC100_RXDES0_RXPKT_RDY))
		वापस false;

	/* Order subsequent पढ़ोs with the test क्रम the पढ़ोy bit */
	dma_rmb();

	/* We करोn't cope with fragmented RX packets */
	अगर (unlikely(!(status & FTGMAC100_RXDES0_FRS) ||
		     !(status & FTGMAC100_RXDES0_LRS)))
		जाओ drop;

	/* Grab received size and csum vlan field in the descriptor */
	size = status & FTGMAC100_RXDES0_VDBC;
	csum_vlan = le32_to_cpu(rxdes->rxdes1);

	/* Any error (other than csum offload) flagged ? */
	अगर (unlikely(status & RXDES0_ANY_ERROR)) अणु
		/* Correct क्रम incorrect flagging of runt packets
		 * with vlan tags... Just accept a runt packet that
		 * has been flagged as vlan and whose size is at
		 * least 60 bytes.
		 */
		अगर ((status & FTGMAC100_RXDES0_RUNT) &&
		    (csum_vlan & FTGMAC100_RXDES1_VLANTAG_AVAIL) &&
		    (size >= 60))
			status &= ~FTGMAC100_RXDES0_RUNT;

		/* Any error still in there ? */
		अगर (status & RXDES0_ANY_ERROR) अणु
			ftgmac100_rx_packet_error(priv, status);
			जाओ drop;
		पूर्ण
	पूर्ण

	/* If the packet had no skb (failed to allocate earlier)
	 * then try to allocate one and skip
	 */
	skb = priv->rx_skbs[poपूर्णांकer];
	अगर (!unlikely(skb)) अणु
		ftgmac100_alloc_rx_buf(priv, poपूर्णांकer, rxdes, GFP_ATOMIC);
		जाओ drop;
	पूर्ण

	अगर (unlikely(status & FTGMAC100_RXDES0_MULTICAST))
		netdev->stats.multicast++;

	/* If the HW found checksum errors, bounce it to software.
	 *
	 * If we didn't, we need to see अगर the packet was recognized
	 * by HW as one of the supported checksummed protocols beक्रमe
	 * we accept the HW test results.
	 */
	अगर (netdev->features & NETIF_F_RXCSUM) अणु
		u32 err_bits = FTGMAC100_RXDES1_TCP_CHKSUM_ERR |
			FTGMAC100_RXDES1_UDP_CHKSUM_ERR |
			FTGMAC100_RXDES1_IP_CHKSUM_ERR;
		अगर ((csum_vlan & err_bits) ||
		    !(csum_vlan & FTGMAC100_RXDES1_PROT_MASK))
			skb->ip_summed = CHECKSUM_NONE;
		अन्यथा
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण

	/* Transfer received size to skb */
	skb_put(skb, size);

	/* Extract vlan tag */
	अगर ((netdev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
	    (csum_vlan & FTGMAC100_RXDES1_VLANTAG_AVAIL))
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       csum_vlan & 0xffff);

	/* Tear करोwn DMA mapping, करो necessary cache management */
	map = le32_to_cpu(rxdes->rxdes3);

#अगर defined(CONFIG_ARM) && !defined(CONFIG_ARM_DMA_USE_IOMMU)
	/* When we करोn't have an iommu, we can save cycles by not
	 * invalidating the cache क्रम the part of the packet that
	 * wasn't received.
	 */
	dma_unmap_single(priv->dev, map, size, DMA_FROM_DEVICE);
#अन्यथा
	dma_unmap_single(priv->dev, map, RX_BUF_SIZE, DMA_FROM_DEVICE);
#पूर्ण_अगर


	/* Resplenish rx ring */
	ftgmac100_alloc_rx_buf(priv, poपूर्णांकer, rxdes, GFP_ATOMIC);
	priv->rx_poपूर्णांकer = ftgmac100_next_rx_poपूर्णांकer(priv, poपूर्णांकer);

	skb->protocol = eth_type_trans(skb, netdev);

	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += size;

	/* push packet to protocol stack */
	अगर (skb->ip_summed == CHECKSUM_NONE)
		netअगर_receive_skb(skb);
	अन्यथा
		napi_gro_receive(&priv->napi, skb);

	(*processed)++;
	वापस true;

 drop:
	/* Clean rxdes0 (which resets own bit) */
	rxdes->rxdes0 = cpu_to_le32(status & priv->rxdes0_eकरोrr_mask);
	priv->rx_poपूर्णांकer = ftgmac100_next_rx_poपूर्णांकer(priv, poपूर्णांकer);
	netdev->stats.rx_dropped++;
	वापस true;
पूर्ण

अटल u32 ftgmac100_base_tx_ctlstat(काष्ठा ftgmac100 *priv,
				     अचिन्हित पूर्णांक index)
अणु
	अगर (index == (priv->tx_q_entries - 1))
		वापस priv->txdes0_eकरोtr_mask;
	अन्यथा
		वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ftgmac100_next_tx_poपूर्णांकer(काष्ठा ftgmac100 *priv,
					      अचिन्हित पूर्णांक poपूर्णांकer)
अणु
	वापस (poपूर्णांकer + 1) & (priv->tx_q_entries - 1);
पूर्ण

अटल u32 ftgmac100_tx_buf_avail(काष्ठा ftgmac100 *priv)
अणु
	/* Returns the number of available slots in the TX queue
	 *
	 * This always leaves one मुक्त slot so we करोn't have to
	 * worry about empty vs. full, and this simplअगरies the
	 * test क्रम ftgmac100_tx_buf_cleanable() below
	 */
	वापस (priv->tx_clean_poपूर्णांकer - priv->tx_poपूर्णांकer - 1) &
		(priv->tx_q_entries - 1);
पूर्ण

अटल bool ftgmac100_tx_buf_cleanable(काष्ठा ftgmac100 *priv)
अणु
	वापस priv->tx_poपूर्णांकer != priv->tx_clean_poपूर्णांकer;
पूर्ण

अटल व्योम ftgmac100_मुक्त_tx_packet(काष्ठा ftgmac100 *priv,
				     अचिन्हित पूर्णांक poपूर्णांकer,
				     काष्ठा sk_buff *skb,
				     काष्ठा ftgmac100_txdes *txdes,
				     u32 ctl_stat)
अणु
	dma_addr_t map = le32_to_cpu(txdes->txdes3);
	माप_प्रकार len;

	अगर (ctl_stat & FTGMAC100_TXDES0_FTS) अणु
		len = skb_headlen(skb);
		dma_unmap_single(priv->dev, map, len, DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		len = FTGMAC100_TXDES0_TXBUF_SIZE(ctl_stat);
		dma_unmap_page(priv->dev, map, len, DMA_TO_DEVICE);
	पूर्ण

	/* Free SKB on last segment */
	अगर (ctl_stat & FTGMAC100_TXDES0_LTS)
		dev_kमुक्त_skb(skb);
	priv->tx_skbs[poपूर्णांकer] = शून्य;
पूर्ण

अटल bool ftgmac100_tx_complete_packet(काष्ठा ftgmac100 *priv)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा ftgmac100_txdes *txdes;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक poपूर्णांकer;
	u32 ctl_stat;

	poपूर्णांकer = priv->tx_clean_poपूर्णांकer;
	txdes = &priv->txdes[poपूर्णांकer];

	ctl_stat = le32_to_cpu(txdes->txdes0);
	अगर (ctl_stat & FTGMAC100_TXDES0_TXDMA_OWN)
		वापस false;

	skb = priv->tx_skbs[poपूर्णांकer];
	netdev->stats.tx_packets++;
	netdev->stats.tx_bytes += skb->len;
	ftgmac100_मुक्त_tx_packet(priv, poपूर्णांकer, skb, txdes, ctl_stat);
	txdes->txdes0 = cpu_to_le32(ctl_stat & priv->txdes0_eकरोtr_mask);

	priv->tx_clean_poपूर्णांकer = ftgmac100_next_tx_poपूर्णांकer(priv, poपूर्णांकer);

	वापस true;
पूर्ण

अटल व्योम ftgmac100_tx_complete(काष्ठा ftgmac100 *priv)
अणु
	काष्ठा net_device *netdev = priv->netdev;

	/* Process all completed packets */
	जबतक (ftgmac100_tx_buf_cleanable(priv) &&
	       ftgmac100_tx_complete_packet(priv))
		;

	/* Restart queue अगर needed */
	smp_mb();
	अगर (unlikely(netअगर_queue_stopped(netdev) &&
		     ftgmac100_tx_buf_avail(priv) >= TX_THRESHOLD)) अणु
		काष्ठा netdev_queue *txq;

		txq = netdev_get_tx_queue(netdev, 0);
		__netअगर_tx_lock(txq, smp_processor_id());
		अगर (netअगर_queue_stopped(netdev) &&
		    ftgmac100_tx_buf_avail(priv) >= TX_THRESHOLD)
			netअगर_wake_queue(netdev);
		__netअगर_tx_unlock(txq);
	पूर्ण
पूर्ण

अटल bool ftgmac100_prep_tx_csum(काष्ठा sk_buff *skb, u32 *csum_vlan)
अणु
	अगर (skb->protocol == cpu_to_be16(ETH_P_IP)) अणु
		u8 ip_proto = ip_hdr(skb)->protocol;

		*csum_vlan |= FTGMAC100_TXDES1_IP_CHKSUM;
		चयन(ip_proto) अणु
		हाल IPPROTO_TCP:
			*csum_vlan |= FTGMAC100_TXDES1_TCP_CHKSUM;
			वापस true;
		हाल IPPROTO_UDP:
			*csum_vlan |= FTGMAC100_TXDES1_UDP_CHKSUM;
			वापस true;
		हाल IPPROTO_IP:
			वापस true;
		पूर्ण
	पूर्ण
	वापस skb_checksum_help(skb) == 0;
पूर्ण

अटल netdev_tx_t ftgmac100_hard_start_xmit(काष्ठा sk_buff *skb,
					     काष्ठा net_device *netdev)
अणु
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);
	काष्ठा ftgmac100_txdes *txdes, *first;
	अचिन्हित पूर्णांक poपूर्णांकer, nfrags, len, i, j;
	u32 f_ctl_stat, ctl_stat, csum_vlan;
	dma_addr_t map;

	/* The HW करोesn't pad small frames */
	अगर (eth_skb_pad(skb)) अणु
		netdev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Reject oversize packets */
	अगर (unlikely(skb->len > MAX_PKT_SIZE)) अणु
		अगर (net_ratelimit())
			netdev_dbg(netdev, "tx packet too big\n");
		जाओ drop;
	पूर्ण

	/* Do we have a limit on #fragments ? I yet have to get a reply
	 * from Aspeed. If there's one I haven't hit it.
	 */
	nfrags = skb_shinfo(skb)->nr_frags;

	/* Setup HW checksumming */
	csum_vlan = 0;
	अगर (skb->ip_summed == CHECKSUM_PARTIAL &&
	    !ftgmac100_prep_tx_csum(skb, &csum_vlan))
		जाओ drop;

	/* Add VLAN tag */
	अगर (skb_vlan_tag_present(skb)) अणु
		csum_vlan |= FTGMAC100_TXDES1_INS_VLANTAG;
		csum_vlan |= skb_vlan_tag_get(skb) & 0xffff;
	पूर्ण

	/* Get header len */
	len = skb_headlen(skb);

	/* Map the packet head */
	map = dma_map_single(priv->dev, skb->data, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(priv->dev, map)) अणु
		अगर (net_ratelimit())
			netdev_err(netdev, "map tx packet head failed\n");
		जाओ drop;
	पूर्ण

	/* Grab the next मुक्त tx descriptor */
	poपूर्णांकer = priv->tx_poपूर्णांकer;
	txdes = first = &priv->txdes[poपूर्णांकer];

	/* Setup it up with the packet head. Don't ग_लिखो the head to the
	 * ring just yet
	 */
	priv->tx_skbs[poपूर्णांकer] = skb;
	f_ctl_stat = ftgmac100_base_tx_ctlstat(priv, poपूर्णांकer);
	f_ctl_stat |= FTGMAC100_TXDES0_TXDMA_OWN;
	f_ctl_stat |= FTGMAC100_TXDES0_TXBUF_SIZE(len);
	f_ctl_stat |= FTGMAC100_TXDES0_FTS;
	अगर (nfrags == 0)
		f_ctl_stat |= FTGMAC100_TXDES0_LTS;
	txdes->txdes3 = cpu_to_le32(map);
	txdes->txdes1 = cpu_to_le32(csum_vlan);

	/* Next descriptor */
	poपूर्णांकer = ftgmac100_next_tx_poपूर्णांकer(priv, poपूर्णांकer);

	/* Add the fragments */
	क्रम (i = 0; i < nfrags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		len = skb_frag_size(frag);

		/* Map it */
		map = skb_frag_dma_map(priv->dev, frag, 0, len,
				       DMA_TO_DEVICE);
		अगर (dma_mapping_error(priv->dev, map))
			जाओ dma_err;

		/* Setup descriptor */
		priv->tx_skbs[poपूर्णांकer] = skb;
		txdes = &priv->txdes[poपूर्णांकer];
		ctl_stat = ftgmac100_base_tx_ctlstat(priv, poपूर्णांकer);
		ctl_stat |= FTGMAC100_TXDES0_TXDMA_OWN;
		ctl_stat |= FTGMAC100_TXDES0_TXBUF_SIZE(len);
		अगर (i == (nfrags - 1))
			ctl_stat |= FTGMAC100_TXDES0_LTS;
		txdes->txdes0 = cpu_to_le32(ctl_stat);
		txdes->txdes1 = 0;
		txdes->txdes3 = cpu_to_le32(map);

		/* Next one */
		poपूर्णांकer = ftgmac100_next_tx_poपूर्णांकer(priv, poपूर्णांकer);
	पूर्ण

	/* Order the previous packet and descriptor udpates
	 * beक्रमe setting the OWN bit on the first descriptor.
	 */
	dma_wmb();
	first->txdes0 = cpu_to_le32(f_ctl_stat);

	/* Update next TX poपूर्णांकer */
	priv->tx_poपूर्णांकer = poपूर्णांकer;

	/* If there isn't enough room क्रम all the fragments of a new packet
	 * in the TX ring, stop the queue. The sequence below is race मुक्त
	 * vs. a concurrent restart in ftgmac100_poll()
	 */
	अगर (unlikely(ftgmac100_tx_buf_avail(priv) < TX_THRESHOLD)) अणु
		netअगर_stop_queue(netdev);
		/* Order the queue stop with the test below */
		smp_mb();
		अगर (ftgmac100_tx_buf_avail(priv) >= TX_THRESHOLD)
			netअगर_wake_queue(netdev);
	पूर्ण

	/* Poke transmitter to पढ़ो the updated TX descriptors */
	ioग_लिखो32(1, priv->base + FTGMAC100_OFFSET_NPTXPD);

	वापस NETDEV_TX_OK;

 dma_err:
	अगर (net_ratelimit())
		netdev_err(netdev, "map tx fragment failed\n");

	/* Free head */
	poपूर्णांकer = priv->tx_poपूर्णांकer;
	ftgmac100_मुक्त_tx_packet(priv, poपूर्णांकer, skb, first, f_ctl_stat);
	first->txdes0 = cpu_to_le32(f_ctl_stat & priv->txdes0_eकरोtr_mask);

	/* Then all fragments */
	क्रम (j = 0; j < i; j++) अणु
		poपूर्णांकer = ftgmac100_next_tx_poपूर्णांकer(priv, poपूर्णांकer);
		txdes = &priv->txdes[poपूर्णांकer];
		ctl_stat = le32_to_cpu(txdes->txdes0);
		ftgmac100_मुक्त_tx_packet(priv, poपूर्णांकer, skb, txdes, ctl_stat);
		txdes->txdes0 = cpu_to_le32(ctl_stat & priv->txdes0_eकरोtr_mask);
	पूर्ण

	/* This cannot be reached अगर we successfully mapped the
	 * last fragment, so we know ftgmac100_मुक्त_tx_packet()
	 * hasn't मुक्तd the skb yet.
	 */
 drop:
	/* Drop the packet */
	dev_kमुक्त_skb_any(skb);
	netdev->stats.tx_dropped++;

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम ftgmac100_मुक्त_buffers(काष्ठा ftgmac100 *priv)
अणु
	पूर्णांक i;

	/* Free all RX buffers */
	क्रम (i = 0; i < priv->rx_q_entries; i++) अणु
		काष्ठा ftgmac100_rxdes *rxdes = &priv->rxdes[i];
		काष्ठा sk_buff *skb = priv->rx_skbs[i];
		dma_addr_t map = le32_to_cpu(rxdes->rxdes3);

		अगर (!skb)
			जारी;

		priv->rx_skbs[i] = शून्य;
		dma_unmap_single(priv->dev, map, RX_BUF_SIZE, DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	/* Free all TX buffers */
	क्रम (i = 0; i < priv->tx_q_entries; i++) अणु
		काष्ठा ftgmac100_txdes *txdes = &priv->txdes[i];
		काष्ठा sk_buff *skb = priv->tx_skbs[i];

		अगर (!skb)
			जारी;
		ftgmac100_मुक्त_tx_packet(priv, i, skb, txdes,
					 le32_to_cpu(txdes->txdes0));
	पूर्ण
पूर्ण

अटल व्योम ftgmac100_मुक्त_rings(काष्ठा ftgmac100 *priv)
अणु
	/* Free skb arrays */
	kमुक्त(priv->rx_skbs);
	kमुक्त(priv->tx_skbs);

	/* Free descriptors */
	अगर (priv->rxdes)
		dma_मुक्त_coherent(priv->dev, MAX_RX_QUEUE_ENTRIES *
				  माप(काष्ठा ftgmac100_rxdes),
				  priv->rxdes, priv->rxdes_dma);
	priv->rxdes = शून्य;

	अगर (priv->txdes)
		dma_मुक्त_coherent(priv->dev, MAX_TX_QUEUE_ENTRIES *
				  माप(काष्ठा ftgmac100_txdes),
				  priv->txdes, priv->txdes_dma);
	priv->txdes = शून्य;

	/* Free scratch packet buffer */
	अगर (priv->rx_scratch)
		dma_मुक्त_coherent(priv->dev, RX_BUF_SIZE,
				  priv->rx_scratch, priv->rx_scratch_dma);
पूर्ण

अटल पूर्णांक ftgmac100_alloc_rings(काष्ठा ftgmac100 *priv)
अणु
	/* Allocate skb arrays */
	priv->rx_skbs = kसुस्मृति(MAX_RX_QUEUE_ENTRIES, माप(व्योम *),
				GFP_KERNEL);
	अगर (!priv->rx_skbs)
		वापस -ENOMEM;
	priv->tx_skbs = kसुस्मृति(MAX_TX_QUEUE_ENTRIES, माप(व्योम *),
				GFP_KERNEL);
	अगर (!priv->tx_skbs)
		वापस -ENOMEM;

	/* Allocate descriptors */
	priv->rxdes = dma_alloc_coherent(priv->dev,
					 MAX_RX_QUEUE_ENTRIES * माप(काष्ठा ftgmac100_rxdes),
					 &priv->rxdes_dma, GFP_KERNEL);
	अगर (!priv->rxdes)
		वापस -ENOMEM;
	priv->txdes = dma_alloc_coherent(priv->dev,
					 MAX_TX_QUEUE_ENTRIES * माप(काष्ठा ftgmac100_txdes),
					 &priv->txdes_dma, GFP_KERNEL);
	अगर (!priv->txdes)
		वापस -ENOMEM;

	/* Allocate scratch packet buffer */
	priv->rx_scratch = dma_alloc_coherent(priv->dev,
					      RX_BUF_SIZE,
					      &priv->rx_scratch_dma,
					      GFP_KERNEL);
	अगर (!priv->rx_scratch)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम ftgmac100_init_rings(काष्ठा ftgmac100 *priv)
अणु
	काष्ठा ftgmac100_rxdes *rxdes = शून्य;
	काष्ठा ftgmac100_txdes *txdes = शून्य;
	पूर्णांक i;

	/* Update entries counts */
	priv->rx_q_entries = priv->new_rx_q_entries;
	priv->tx_q_entries = priv->new_tx_q_entries;

	अगर (WARN_ON(priv->rx_q_entries < MIN_RX_QUEUE_ENTRIES))
		वापस;

	/* Initialize RX ring */
	क्रम (i = 0; i < priv->rx_q_entries; i++) अणु
		rxdes = &priv->rxdes[i];
		rxdes->rxdes0 = 0;
		rxdes->rxdes3 = cpu_to_le32(priv->rx_scratch_dma);
	पूर्ण
	/* Mark the end of the ring */
	rxdes->rxdes0 |= cpu_to_le32(priv->rxdes0_eकरोrr_mask);

	अगर (WARN_ON(priv->tx_q_entries < MIN_RX_QUEUE_ENTRIES))
		वापस;

	/* Initialize TX ring */
	क्रम (i = 0; i < priv->tx_q_entries; i++) अणु
		txdes = &priv->txdes[i];
		txdes->txdes0 = 0;
	पूर्ण
	txdes->txdes0 |= cpu_to_le32(priv->txdes0_eकरोtr_mask);
पूर्ण

अटल पूर्णांक ftgmac100_alloc_rx_buffers(काष्ठा ftgmac100 *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->rx_q_entries; i++) अणु
		काष्ठा ftgmac100_rxdes *rxdes = &priv->rxdes[i];

		अगर (ftgmac100_alloc_rx_buf(priv, i, rxdes, GFP_KERNEL))
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ftgmac100_adjust_link(काष्ठा net_device *netdev)
अणु
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);
	काष्ठा phy_device *phydev = netdev->phydev;
	bool tx_छोड़ो, rx_छोड़ो;
	पूर्णांक new_speed;

	/* We store "no link" as speed 0 */
	अगर (!phydev->link)
		new_speed = 0;
	अन्यथा
		new_speed = phydev->speed;

	/* Grab छोड़ो settings from PHY अगर configured to करो so */
	अगर (priv->aneg_छोड़ो) अणु
		rx_छोड़ो = tx_छोड़ो = phydev->छोड़ो;
		अगर (phydev->asym_छोड़ो)
			tx_छोड़ो = !rx_छोड़ो;
	पूर्ण अन्यथा अणु
		rx_छोड़ो = priv->rx_छोड़ो;
		tx_छोड़ो = priv->tx_छोड़ो;
	पूर्ण

	/* Link hasn't changed, करो nothing */
	अगर (phydev->speed == priv->cur_speed &&
	    phydev->duplex == priv->cur_duplex &&
	    rx_छोड़ो == priv->rx_छोड़ो &&
	    tx_छोड़ो == priv->tx_छोड़ो)
		वापस;

	/* Prपूर्णांक status अगर we have a link or we had one and just lost it,
	 * करोn't prपूर्णांक otherwise.
	 */
	अगर (new_speed || priv->cur_speed)
		phy_prपूर्णांक_status(phydev);

	priv->cur_speed = new_speed;
	priv->cur_duplex = phydev->duplex;
	priv->rx_छोड़ो = rx_छोड़ो;
	priv->tx_छोड़ो = tx_छोड़ो;

	/* Link is करोwn, करो nothing अन्यथा */
	अगर (!new_speed)
		वापस;

	/* Disable all पूर्णांकerrupts */
	ioग_लिखो32(0, priv->base + FTGMAC100_OFFSET_IER);

	/* Reset the adapter asynchronously */
	schedule_work(&priv->reset_task);
पूर्ण

अटल पूर्णांक ftgmac100_mii_probe(काष्ठा net_device *netdev)
अणु
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(priv->dev);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा phy_device *phydev;
	phy_पूर्णांकerface_t phy_पूर्णांकf;
	पूर्णांक err;

	/* Default to RGMII. It's a gigabit part after all */
	err = of_get_phy_mode(np, &phy_पूर्णांकf);
	अगर (err)
		phy_पूर्णांकf = PHY_INTERFACE_MODE_RGMII;

	/* Aspeed only supports these. I करोn't know about other IP
	 * block venकरोrs so I'm going to just let them through क्रम
	 * now. Note that this is only a warning अगर क्रम some obscure
	 * reason the DT really means to lie about it or it's a newer
	 * part we करोn't know about.
	 *
	 * On the Aspeed SoC there are additionally straps and SCU
	 * control bits that could tell us what the पूर्णांकerface is
	 * (or allow us to configure it जबतक the IP block is held
	 * in reset). For now I chose to keep this driver away from
	 * those SoC specअगरic bits and assume the device-tree is
	 * right and the SCU has been configured properly by pinmux
	 * or the firmware.
	 */
	अगर (priv->is_aspeed && !(phy_पूर्णांकerface_mode_is_rgmii(phy_पूर्णांकf))) अणु
		netdev_warn(netdev,
			    "Unsupported PHY mode %s !\n",
			    phy_modes(phy_पूर्णांकf));
	पूर्ण

	phydev = phy_find_first(priv->mii_bus);
	अगर (!phydev) अणु
		netdev_info(netdev, "%s: no PHY found\n", netdev->name);
		वापस -ENODEV;
	पूर्ण

	phydev = phy_connect(netdev, phydev_name(phydev),
			     &ftgmac100_adjust_link, phy_पूर्णांकf);

	अगर (IS_ERR(phydev)) अणु
		netdev_err(netdev, "%s: Could not attach to PHY\n", netdev->name);
		वापस PTR_ERR(phydev);
	पूर्ण

	/* Indicate that we support PAUSE frames (see comment in
	 * Documentation/networking/phy.rst)
	 */
	phy_support_asym_छोड़ो(phydev);

	/* Display what we found */
	phy_attached_info(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक ftgmac100_mdiobus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक regnum)
अणु
	काष्ठा net_device *netdev = bus->priv;
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);
	अचिन्हित पूर्णांक phycr;
	पूर्णांक i;

	phycr = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_PHYCR);

	/* preserve MDC cycle threshold */
	phycr &= FTGMAC100_PHYCR_MDC_CYCTHR_MASK;

	phycr |= FTGMAC100_PHYCR_PHYAD(phy_addr) |
		 FTGMAC100_PHYCR_REGAD(regnum) |
		 FTGMAC100_PHYCR_MIIRD;

	ioग_लिखो32(phycr, priv->base + FTGMAC100_OFFSET_PHYCR);

	क्रम (i = 0; i < 10; i++) अणु
		phycr = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_PHYCR);

		अगर ((phycr & FTGMAC100_PHYCR_MIIRD) == 0) अणु
			पूर्णांक data;

			data = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_PHYDATA);
			वापस FTGMAC100_PHYDATA_MIIRDATA(data);
		पूर्ण

		udelay(100);
	पूर्ण

	netdev_err(netdev, "mdio read timed out\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक ftgmac100_mdiobus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_addr,
				   पूर्णांक regnum, u16 value)
अणु
	काष्ठा net_device *netdev = bus->priv;
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);
	अचिन्हित पूर्णांक phycr;
	पूर्णांक data;
	पूर्णांक i;

	phycr = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_PHYCR);

	/* preserve MDC cycle threshold */
	phycr &= FTGMAC100_PHYCR_MDC_CYCTHR_MASK;

	phycr |= FTGMAC100_PHYCR_PHYAD(phy_addr) |
		 FTGMAC100_PHYCR_REGAD(regnum) |
		 FTGMAC100_PHYCR_MIIWR;

	data = FTGMAC100_PHYDATA_MIIWDATA(value);

	ioग_लिखो32(data, priv->base + FTGMAC100_OFFSET_PHYDATA);
	ioग_लिखो32(phycr, priv->base + FTGMAC100_OFFSET_PHYCR);

	क्रम (i = 0; i < 10; i++) अणु
		phycr = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_PHYCR);

		अगर ((phycr & FTGMAC100_PHYCR_MIIWR) == 0)
			वापस 0;

		udelay(100);
	पूर्ण

	netdev_err(netdev, "mdio write timed out\n");
	वापस -EIO;
पूर्ण

अटल व्योम ftgmac100_get_drvinfo(काष्ठा net_device *netdev,
				  काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, dev_name(&netdev->dev), माप(info->bus_info));
पूर्ण

अटल व्योम ftgmac100_get_ringparam(काष्ठा net_device *netdev,
				    काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);

	स_रखो(ering, 0, माप(*ering));
	ering->rx_max_pending = MAX_RX_QUEUE_ENTRIES;
	ering->tx_max_pending = MAX_TX_QUEUE_ENTRIES;
	ering->rx_pending = priv->rx_q_entries;
	ering->tx_pending = priv->tx_q_entries;
पूर्ण

अटल पूर्णांक ftgmac100_set_ringparam(काष्ठा net_device *netdev,
				   काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);

	अगर (ering->rx_pending > MAX_RX_QUEUE_ENTRIES ||
	    ering->tx_pending > MAX_TX_QUEUE_ENTRIES ||
	    ering->rx_pending < MIN_RX_QUEUE_ENTRIES ||
	    ering->tx_pending < MIN_TX_QUEUE_ENTRIES ||
	    !is_घातer_of_2(ering->rx_pending) ||
	    !is_घातer_of_2(ering->tx_pending))
		वापस -EINVAL;

	priv->new_rx_q_entries = ering->rx_pending;
	priv->new_tx_q_entries = ering->tx_pending;
	अगर (netअगर_running(netdev))
		schedule_work(&priv->reset_task);

	वापस 0;
पूर्ण

अटल व्योम ftgmac100_get_छोड़ोparam(काष्ठा net_device *netdev,
				     काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);

	छोड़ो->स्वतःneg = priv->aneg_छोड़ो;
	छोड़ो->tx_छोड़ो = priv->tx_छोड़ो;
	छोड़ो->rx_छोड़ो = priv->rx_छोड़ो;
पूर्ण

अटल पूर्णांक ftgmac100_set_छोड़ोparam(काष्ठा net_device *netdev,
				    काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);
	काष्ठा phy_device *phydev = netdev->phydev;

	priv->aneg_छोड़ो = छोड़ो->स्वतःneg;
	priv->tx_छोड़ो = छोड़ो->tx_छोड़ो;
	priv->rx_छोड़ो = छोड़ो->rx_छोड़ो;

	अगर (phydev)
		phy_set_asym_छोड़ो(phydev, छोड़ो->rx_छोड़ो, छोड़ो->tx_छोड़ो);

	अगर (netअगर_running(netdev)) अणु
		अगर (!(phydev && priv->aneg_छोड़ो))
			ftgmac100_config_छोड़ो(priv);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ftgmac100_ethtool_ops = अणु
	.get_drvinfo		= ftgmac100_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
	.nway_reset		= phy_ethtool_nway_reset,
	.get_ringparam		= ftgmac100_get_ringparam,
	.set_ringparam		= ftgmac100_set_ringparam,
	.get_छोड़ोparam		= ftgmac100_get_छोड़ोparam,
	.set_छोड़ोparam		= ftgmac100_set_छोड़ोparam,
पूर्ण;

अटल irqवापस_t ftgmac100_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *netdev = dev_id;
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);
	अचिन्हित पूर्णांक status, new_mask = FTGMAC100_INT_BAD;

	/* Fetch and clear पूर्णांकerrupt bits, process abnormal ones */
	status = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_ISR);
	ioग_लिखो32(status, priv->base + FTGMAC100_OFFSET_ISR);
	अगर (unlikely(status & FTGMAC100_INT_BAD)) अणु

		/* RX buffer unavailable */
		अगर (status & FTGMAC100_INT_NO_RXBUF)
			netdev->stats.rx_over_errors++;

		/* received packet lost due to RX FIFO full */
		अगर (status & FTGMAC100_INT_RPKT_LOST)
			netdev->stats.rx_fअगरo_errors++;

		/* sent packet lost due to excessive TX collision */
		अगर (status & FTGMAC100_INT_XPKT_LOST)
			netdev->stats.tx_fअगरo_errors++;

		/* AHB error -> Reset the chip */
		अगर (status & FTGMAC100_INT_AHB_ERR) अणु
			अगर (net_ratelimit())
				netdev_warn(netdev,
					   "AHB bus error ! Resetting chip.\n");
			ioग_लिखो32(0, priv->base + FTGMAC100_OFFSET_IER);
			schedule_work(&priv->reset_task);
			वापस IRQ_HANDLED;
		पूर्ण

		/* We may need to restart the MAC after such errors, delay
		 * this until after we have मुक्तd some Rx buffers though
		 */
		priv->need_mac_restart = true;

		/* Disable those errors until we restart */
		new_mask &= ~status;
	पूर्ण

	/* Only enable "bad" पूर्णांकerrupts जबतक NAPI is on */
	ioग_लिखो32(new_mask, priv->base + FTGMAC100_OFFSET_IER);

	/* Schedule NAPI bh */
	napi_schedule_irqoff(&priv->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल bool ftgmac100_check_rx(काष्ठा ftgmac100 *priv)
अणु
	काष्ठा ftgmac100_rxdes *rxdes = &priv->rxdes[priv->rx_poपूर्णांकer];

	/* Do we have a packet ? */
	वापस !!(rxdes->rxdes0 & cpu_to_le32(FTGMAC100_RXDES0_RXPKT_RDY));
पूर्ण

अटल पूर्णांक ftgmac100_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ftgmac100 *priv = container_of(napi, काष्ठा ftgmac100, napi);
	पूर्णांक work_करोne = 0;
	bool more;

	/* Handle TX completions */
	अगर (ftgmac100_tx_buf_cleanable(priv))
		ftgmac100_tx_complete(priv);

	/* Handle RX packets */
	करो अणु
		more = ftgmac100_rx_packet(priv, &work_करोne);
	पूर्ण जबतक (more && work_करोne < budget);


	/* The पूर्णांकerrupt is telling us to kick the MAC back to lअगरe
	 * after an RX overflow
	 */
	अगर (unlikely(priv->need_mac_restart)) अणु
		ftgmac100_start_hw(priv);
		priv->need_mac_restart = false;

		/* Re-enable "bad" पूर्णांकerrupts */
		ioग_लिखो32(FTGMAC100_INT_BAD,
			  priv->base + FTGMAC100_OFFSET_IER);
	पूर्ण

	/* As दीर्घ as we are रुकोing क्रम transmit packets to be
	 * completed we keep NAPI going
	 */
	अगर (ftgmac100_tx_buf_cleanable(priv))
		work_करोne = budget;

	अगर (work_करोne < budget) अणु
		/* We are about to re-enable all पूर्णांकerrupts. However
		 * the HW has been latching RX/TX packet पूर्णांकerrupts जबतक
		 * they were masked. So we clear them first, then we need
		 * to re-check अगर there's something to process
		 */
		ioग_लिखो32(FTGMAC100_INT_RXTX,
			  priv->base + FTGMAC100_OFFSET_ISR);

		/* Push the above (and provides a barrier vs. subsequent
		 * पढ़ोs of the descriptor).
		 */
		ioपढ़ो32(priv->base + FTGMAC100_OFFSET_ISR);

		/* Check RX and TX descriptors क्रम more work to करो */
		अगर (ftgmac100_check_rx(priv) ||
		    ftgmac100_tx_buf_cleanable(priv))
			वापस budget;

		/* deschedule NAPI */
		napi_complete(napi);

		/* enable all पूर्णांकerrupts */
		ioग_लिखो32(FTGMAC100_INT_ALL,
			  priv->base + FTGMAC100_OFFSET_IER);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक ftgmac100_init_all(काष्ठा ftgmac100 *priv, bool ignore_alloc_err)
अणु
	पूर्णांक err = 0;

	/* Re-init descriptors (adjust queue sizes) */
	ftgmac100_init_rings(priv);

	/* Realloc rx descriptors */
	err = ftgmac100_alloc_rx_buffers(priv);
	अगर (err && !ignore_alloc_err)
		वापस err;

	/* Reinit and restart HW */
	ftgmac100_init_hw(priv);
	ftgmac100_config_छोड़ो(priv);
	ftgmac100_start_hw(priv);

	/* Re-enable the device */
	napi_enable(&priv->napi);
	netअगर_start_queue(priv->netdev);

	/* Enable all पूर्णांकerrupts */
	ioग_लिखो32(FTGMAC100_INT_ALL, priv->base + FTGMAC100_OFFSET_IER);

	वापस err;
पूर्ण

अटल व्योम ftgmac100_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ftgmac100 *priv = container_of(work, काष्ठा ftgmac100,
					      reset_task);
	काष्ठा net_device *netdev = priv->netdev;
	पूर्णांक err;

	netdev_dbg(netdev, "Resetting NIC...\n");

	/* Lock the world */
	rtnl_lock();
	अगर (netdev->phydev)
		mutex_lock(&netdev->phydev->lock);
	अगर (priv->mii_bus)
		mutex_lock(&priv->mii_bus->mdio_lock);


	/* Check अगर the पूर्णांकerface is still up */
	अगर (!netअगर_running(netdev))
		जाओ bail;

	/* Stop the network stack */
	netअगर_trans_update(netdev);
	napi_disable(&priv->napi);
	netअगर_tx_disable(netdev);

	/* Stop and reset the MAC */
	ftgmac100_stop_hw(priv);
	err = ftgmac100_reset_and_config_mac(priv);
	अगर (err) अणु
		/* Not much we can करो ... it might come back... */
		netdev_err(netdev, "attempting to continue...\n");
	पूर्ण

	/* Free all rx and tx buffers */
	ftgmac100_मुक्त_buffers(priv);

	/* Setup everything again and restart chip */
	ftgmac100_init_all(priv, true);

	netdev_dbg(netdev, "Reset done !\n");
 bail:
	अगर (priv->mii_bus)
		mutex_unlock(&priv->mii_bus->mdio_lock);
	अगर (netdev->phydev)
		mutex_unlock(&netdev->phydev->lock);
	rtnl_unlock();
पूर्ण

अटल पूर्णांक ftgmac100_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);
	पूर्णांक err;

	/* Allocate ring buffers  */
	err = ftgmac100_alloc_rings(priv);
	अगर (err) अणु
		netdev_err(netdev, "Failed to allocate descriptors\n");
		वापस err;
	पूर्ण

	/* When using NC-SI we क्रमce the speed to 100Mbit/s full duplex,
	 *
	 * Otherwise we leave it set to 0 (no link), the link
	 * message from the PHY layer will handle setting it up to
	 * something अन्यथा अगर needed.
	 */
	अगर (priv->use_ncsi) अणु
		priv->cur_duplex = DUPLEX_FULL;
		priv->cur_speed = SPEED_100;
	पूर्ण अन्यथा अणु
		priv->cur_duplex = 0;
		priv->cur_speed = 0;
	पूर्ण

	/* Reset the hardware */
	err = ftgmac100_reset_and_config_mac(priv);
	अगर (err)
		जाओ err_hw;

	/* Initialize NAPI */
	netअगर_napi_add(netdev, &priv->napi, ftgmac100_poll, 64);

	/* Grab our पूर्णांकerrupt */
	err = request_irq(netdev->irq, ftgmac100_पूर्णांकerrupt, 0, netdev->name, netdev);
	अगर (err) अणु
		netdev_err(netdev, "failed to request irq %d\n", netdev->irq);
		जाओ err_irq;
	पूर्ण

	/* Start things up */
	err = ftgmac100_init_all(priv, false);
	अगर (err) अणु
		netdev_err(netdev, "Failed to allocate packet buffers\n");
		जाओ err_alloc;
	पूर्ण

	अगर (netdev->phydev) अणु
		/* If we have a PHY, start polling */
		phy_start(netdev->phydev);
	पूर्ण अन्यथा अगर (priv->use_ncsi) अणु
		/* If using NC-SI, set our carrier on and start the stack */
		netअगर_carrier_on(netdev);

		/* Start the NCSI device */
		err = ncsi_start_dev(priv->ndev);
		अगर (err)
			जाओ err_ncsi;
	पूर्ण

	वापस 0;

 err_ncsi:
	napi_disable(&priv->napi);
	netअगर_stop_queue(netdev);
 err_alloc:
	ftgmac100_मुक्त_buffers(priv);
	मुक्त_irq(netdev->irq, netdev);
 err_irq:
	netअगर_napi_del(&priv->napi);
 err_hw:
	ioग_लिखो32(0, priv->base + FTGMAC100_OFFSET_IER);
	ftgmac100_मुक्त_rings(priv);
	वापस err;
पूर्ण

अटल पूर्णांक ftgmac100_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);

	/* Note about the reset task: We are called with the rtnl lock
	 * held, so we are synchronized against the core of the reset
	 * task. We must not try to synchronously cancel it otherwise
	 * we can deadlock. But since it will test क्रम netअगर_running()
	 * which has alपढ़ोy been cleared by the net core, we करोn't
	 * anything special to करो.
	 */

	/* disable all पूर्णांकerrupts */
	ioग_लिखो32(0, priv->base + FTGMAC100_OFFSET_IER);

	netअगर_stop_queue(netdev);
	napi_disable(&priv->napi);
	netअगर_napi_del(&priv->napi);
	अगर (netdev->phydev)
		phy_stop(netdev->phydev);
	अन्यथा अगर (priv->use_ncsi)
		ncsi_stop_dev(priv->ndev);

	ftgmac100_stop_hw(priv);
	मुक्त_irq(netdev->irq, netdev);
	ftgmac100_मुक्त_buffers(priv);
	ftgmac100_मुक्त_rings(priv);

	वापस 0;
पूर्ण

अटल व्योम ftgmac100_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);

	/* Disable all पूर्णांकerrupts */
	ioग_लिखो32(0, priv->base + FTGMAC100_OFFSET_IER);

	/* Do the reset outside of पूर्णांकerrupt context */
	schedule_work(&priv->reset_task);
पूर्ण

अटल पूर्णांक ftgmac100_set_features(काष्ठा net_device *netdev,
				  netdev_features_t features)
अणु
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);
	netdev_features_t changed = netdev->features ^ features;

	अगर (!netअगर_running(netdev))
		वापस 0;

	/* Update the vlan filtering bit */
	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX) अणु
		u32 maccr;

		maccr = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_MACCR);
		अगर (priv->netdev->features & NETIF_F_HW_VLAN_CTAG_RX)
			maccr |= FTGMAC100_MACCR_RM_VLAN;
		अन्यथा
			maccr &= ~FTGMAC100_MACCR_RM_VLAN;
		ioग_लिखो32(maccr, priv->base + FTGMAC100_OFFSET_MACCR);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम ftgmac100_poll_controller(काष्ठा net_device *netdev)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	ftgmac100_पूर्णांकerrupt(netdev->irq, netdev);
	local_irq_restore(flags);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops ftgmac100_netdev_ops = अणु
	.nकरो_खोलो		= ftgmac100_खोलो,
	.nकरो_stop		= ftgmac100_stop,
	.nकरो_start_xmit		= ftgmac100_hard_start_xmit,
	.nकरो_set_mac_address	= ftgmac100_set_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= phy_करो_ioctl,
	.nकरो_tx_समयout		= ftgmac100_tx_समयout,
	.nकरो_set_rx_mode	= ftgmac100_set_rx_mode,
	.nकरो_set_features	= ftgmac100_set_features,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= ftgmac100_poll_controller,
#पूर्ण_अगर
	.nकरो_vlan_rx_add_vid	= ncsi_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= ncsi_vlan_rx_समाप्त_vid,
पूर्ण;

अटल पूर्णांक ftgmac100_setup_mdio(काष्ठा net_device *netdev)
अणु
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(priv->dev);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *mdio_np;
	पूर्णांक i, err = 0;
	u32 reg;

	/* initialize mdio bus */
	priv->mii_bus = mdiobus_alloc();
	अगर (!priv->mii_bus)
		वापस -EIO;

	अगर (of_device_is_compatible(np, "aspeed,ast2400-mac") ||
	    of_device_is_compatible(np, "aspeed,ast2500-mac")) अणु
		/* The AST2600 has a separate MDIO controller */

		/* For the AST2400 and AST2500 this driver only supports the
		 * old MDIO पूर्णांकerface
		 */
		reg = ioपढ़ो32(priv->base + FTGMAC100_OFFSET_REVR);
		reg &= ~FTGMAC100_REVR_NEW_MDIO_INTERFACE;
		ioग_लिखो32(reg, priv->base + FTGMAC100_OFFSET_REVR);
	पूर्ण

	priv->mii_bus->name = "ftgmac100_mdio";
	snम_लिखो(priv->mii_bus->id, MII_BUS_ID_SIZE, "%s-%d",
		 pdev->name, pdev->id);
	priv->mii_bus->parent = priv->dev;
	priv->mii_bus->priv = priv->netdev;
	priv->mii_bus->पढ़ो = ftgmac100_mdiobus_पढ़ो;
	priv->mii_bus->ग_लिखो = ftgmac100_mdiobus_ग_लिखो;

	क्रम (i = 0; i < PHY_MAX_ADDR; i++)
		priv->mii_bus->irq[i] = PHY_POLL;

	mdio_np = of_get_child_by_name(np, "mdio");

	err = of_mdiobus_रेजिस्टर(priv->mii_bus, mdio_np);
	अगर (err) अणु
		dev_err(priv->dev, "Cannot register MDIO bus!\n");
		जाओ err_रेजिस्टर_mdiobus;
	पूर्ण

	of_node_put(mdio_np);

	वापस 0;

err_रेजिस्टर_mdiobus:
	mdiobus_मुक्त(priv->mii_bus);
	वापस err;
पूर्ण

अटल व्योम ftgmac100_phy_disconnect(काष्ठा net_device *netdev)
अणु
	अगर (!netdev->phydev)
		वापस;

	phy_disconnect(netdev->phydev);
पूर्ण

अटल व्योम ftgmac100_destroy_mdio(काष्ठा net_device *netdev)
अणु
	काष्ठा ftgmac100 *priv = netdev_priv(netdev);

	अगर (!priv->mii_bus)
		वापस;

	mdiobus_unरेजिस्टर(priv->mii_bus);
	mdiobus_मुक्त(priv->mii_bus);
पूर्ण

अटल व्योम ftgmac100_ncsi_handler(काष्ठा ncsi_dev *nd)
अणु
	अगर (unlikely(nd->state != ncsi_dev_state_functional))
		वापस;

	netdev_dbg(nd->dev, "NCSI interface %s\n",
		   nd->link_up ? "up" : "down");
पूर्ण

अटल पूर्णांक ftgmac100_setup_clk(काष्ठा ftgmac100 *priv)
अणु
	काष्ठा clk *clk;
	पूर्णांक rc;

	clk = devm_clk_get(priv->dev, शून्य /* MACCLK */);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);
	priv->clk = clk;
	rc = clk_prepare_enable(priv->clk);
	अगर (rc)
		वापस rc;

	/* Aspeed specअगरies a 100MHz घड़ी is required क्रम up to
	 * 1000Mbit link speeds. As NCSI is limited to 100Mbit, 25MHz
	 * is sufficient
	 */
	rc = clk_set_rate(priv->clk, priv->use_ncsi ? FTGMAC_25MHZ :
			  FTGMAC_100MHZ);
	अगर (rc)
		जाओ cleanup_clk;

	/* RCLK is क्रम RMII, typically used क्रम NCSI. Optional because it's not
	 * necessary अगर it's the AST2400 MAC, or the MAC is configured क्रम
	 * RGMII, or the controller is not an ASPEED-based controller.
	 */
	priv->rclk = devm_clk_get_optional(priv->dev, "RCLK");
	rc = clk_prepare_enable(priv->rclk);
	अगर (!rc)
		वापस 0;

cleanup_clk:
	clk_disable_unprepare(priv->clk);

	वापस rc;
पूर्ण

अटल पूर्णांक ftgmac100_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	पूर्णांक irq;
	काष्ठा net_device *netdev;
	काष्ठा ftgmac100 *priv;
	काष्ठा device_node *np;
	पूर्णांक err = 0;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENXIO;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	/* setup net_device */
	netdev = alloc_etherdev(माप(*priv));
	अगर (!netdev) अणु
		err = -ENOMEM;
		जाओ err_alloc_etherdev;
	पूर्ण

	SET_NETDEV_DEV(netdev, &pdev->dev);

	netdev->ethtool_ops = &ftgmac100_ethtool_ops;
	netdev->netdev_ops = &ftgmac100_netdev_ops;
	netdev->watchकरोg_समयo = 5 * HZ;

	platक्रमm_set_drvdata(pdev, netdev);

	/* setup निजी data */
	priv = netdev_priv(netdev);
	priv->netdev = netdev;
	priv->dev = &pdev->dev;
	INIT_WORK(&priv->reset_task, ftgmac100_reset_task);

	/* map io memory */
	priv->res = request_mem_region(res->start, resource_size(res),
				       dev_name(&pdev->dev));
	अगर (!priv->res) अणु
		dev_err(&pdev->dev, "Could not reserve memory region\n");
		err = -ENOMEM;
		जाओ err_req_mem;
	पूर्ण

	priv->base = ioremap(res->start, resource_size(res));
	अगर (!priv->base) अणु
		dev_err(&pdev->dev, "Failed to ioremap ethernet registers\n");
		err = -EIO;
		जाओ err_ioremap;
	पूर्ण

	netdev->irq = irq;

	/* Enable छोड़ो */
	priv->tx_छोड़ो = true;
	priv->rx_छोड़ो = true;
	priv->aneg_छोड़ो = true;

	/* MAC address from chip or अक्रमom one */
	ftgmac100_initial_mac(priv);

	np = pdev->dev.of_node;
	अगर (np && (of_device_is_compatible(np, "aspeed,ast2400-mac") ||
		   of_device_is_compatible(np, "aspeed,ast2500-mac") ||
		   of_device_is_compatible(np, "aspeed,ast2600-mac"))) अणु
		priv->rxdes0_eकरोrr_mask = BIT(30);
		priv->txdes0_eकरोtr_mask = BIT(30);
		priv->is_aspeed = true;
		/* Disable ast2600 problematic HW arbitration */
		अगर (of_device_is_compatible(np, "aspeed,ast2600-mac")) अणु
			ioग_लिखो32(FTGMAC100_TM_DEFAULT,
				  priv->base + FTGMAC100_OFFSET_TM);
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->rxdes0_eकरोrr_mask = BIT(15);
		priv->txdes0_eकरोtr_mask = BIT(15);
	पूर्ण

	अगर (np && of_get_property(np, "use-ncsi", शून्य)) अणु
		अगर (!IS_ENABLED(CONFIG_NET_NCSI)) अणु
			dev_err(&pdev->dev, "NCSI stack not enabled\n");
			जाओ err_phy_connect;
		पूर्ण

		dev_info(&pdev->dev, "Using NCSI interface\n");
		priv->use_ncsi = true;
		priv->ndev = ncsi_रेजिस्टर_dev(netdev, ftgmac100_ncsi_handler);
		अगर (!priv->ndev)
			जाओ err_phy_connect;
	पूर्ण अन्यथा अगर (np && of_get_property(np, "phy-handle", शून्य)) अणु
		काष्ठा phy_device *phy;

		/* Support "mdio"/"phy" child nodes क्रम ast2400/2500 with
		 * an embedded MDIO controller. Automatically scan the DTS क्रम
		 * available PHYs and रेजिस्टर them.
		 */
		अगर (of_device_is_compatible(np, "aspeed,ast2400-mac") ||
		    of_device_is_compatible(np, "aspeed,ast2500-mac")) अणु
			err = ftgmac100_setup_mdio(netdev);
			अगर (err)
				जाओ err_setup_mdio;
		पूर्ण

		phy = of_phy_get_and_connect(priv->netdev, np,
					     &ftgmac100_adjust_link);
		अगर (!phy) अणु
			dev_err(&pdev->dev, "Failed to connect to phy\n");
			जाओ err_phy_connect;
		पूर्ण

		/* Indicate that we support PAUSE frames (see comment in
		 * Documentation/networking/phy.rst)
		 */
		phy_support_asym_छोड़ो(phy);

		/* Display what we found */
		phy_attached_info(phy);
	पूर्ण अन्यथा अगर (np && !of_get_child_by_name(np, "mdio")) अणु
		/* Support legacy ASPEED devicetree descriptions that decribe a
		 * MAC with an embedded MDIO controller but have no "mdio"
		 * child node. Automatically scan the MDIO bus क्रम available
		 * PHYs.
		 */
		priv->use_ncsi = false;
		err = ftgmac100_setup_mdio(netdev);
		अगर (err)
			जाओ err_setup_mdio;

		err = ftgmac100_mii_probe(netdev);
		अगर (err) अणु
			dev_err(priv->dev, "MII probe failed!\n");
			जाओ err_ncsi_dev;
		पूर्ण

	पूर्ण

	अगर (priv->is_aspeed) अणु
		err = ftgmac100_setup_clk(priv);
		अगर (err)
			जाओ err_phy_connect;
	पूर्ण

	/* Default ring sizes */
	priv->rx_q_entries = priv->new_rx_q_entries = DEF_RX_QUEUE_ENTRIES;
	priv->tx_q_entries = priv->new_tx_q_entries = DEF_TX_QUEUE_ENTRIES;

	/* Base feature set */
	netdev->hw_features = NETIF_F_RXCSUM | NETIF_F_HW_CSUM |
		NETIF_F_GRO | NETIF_F_SG | NETIF_F_HW_VLAN_CTAG_RX |
		NETIF_F_HW_VLAN_CTAG_TX;

	अगर (priv->use_ncsi)
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	/* AST2400  करोesn't have working HW checksum generation */
	अगर (np && (of_device_is_compatible(np, "aspeed,ast2400-mac")))
		netdev->hw_features &= ~NETIF_F_HW_CSUM;
	अगर (np && of_get_property(np, "no-hw-checksum", शून्य))
		netdev->hw_features &= ~(NETIF_F_HW_CSUM | NETIF_F_RXCSUM);
	netdev->features |= netdev->hw_features;

	/* रेजिस्टर network device */
	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register netdev\n");
		जाओ err_रेजिस्टर_netdev;
	पूर्ण

	netdev_info(netdev, "irq %d, mapped at %p\n", netdev->irq, priv->base);

	वापस 0;

err_रेजिस्टर_netdev:
	clk_disable_unprepare(priv->rclk);
	clk_disable_unprepare(priv->clk);
err_phy_connect:
	ftgmac100_phy_disconnect(netdev);
err_ncsi_dev:
	अगर (priv->ndev)
		ncsi_unरेजिस्टर_dev(priv->ndev);
	ftgmac100_destroy_mdio(netdev);
err_setup_mdio:
	iounmap(priv->base);
err_ioremap:
	release_resource(priv->res);
err_req_mem:
	मुक्त_netdev(netdev);
err_alloc_etherdev:
	वापस err;
पूर्ण

अटल पूर्णांक ftgmac100_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *netdev;
	काष्ठा ftgmac100 *priv;

	netdev = platक्रमm_get_drvdata(pdev);
	priv = netdev_priv(netdev);

	अगर (priv->ndev)
		ncsi_unरेजिस्टर_dev(priv->ndev);
	unरेजिस्टर_netdev(netdev);

	clk_disable_unprepare(priv->rclk);
	clk_disable_unprepare(priv->clk);

	/* There's a small chance the reset task will have been re-queued,
	 * during stop, make sure it's gone beक्रमe we मुक्त the काष्ठाure.
	 */
	cancel_work_sync(&priv->reset_task);

	ftgmac100_phy_disconnect(netdev);
	ftgmac100_destroy_mdio(netdev);

	iounmap(priv->base);
	release_resource(priv->res);

	netअगर_napi_del(&priv->napi);
	मुक्त_netdev(netdev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ftgmac100_of_match[] = अणु
	अणु .compatible = "faraday,ftgmac100" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ftgmac100_of_match);

अटल काष्ठा platक्रमm_driver ftgmac100_driver = अणु
	.probe	= ftgmac100_probe,
	.हटाओ	= ftgmac100_हटाओ,
	.driver	= अणु
		.name		= DRV_NAME,
		.of_match_table	= ftgmac100_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ftgmac100_driver);

MODULE_AUTHOR("Po-Yu Chuang <ratbert@faraday-tech.com>");
MODULE_DESCRIPTION("FTGMAC100 driver");
MODULE_LICENSE("GPL");
