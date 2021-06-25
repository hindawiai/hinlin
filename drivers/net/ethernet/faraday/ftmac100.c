<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Faraday FTMAC100 10/100 Ethernet
 *
 * (C) Copyright 2009-2011 Faraday Technology
 * Po-Yu Chuang <ratbert@faraday-tech.com>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "ftmac100.h"

#घोषणा DRV_NAME	"ftmac100"

#घोषणा RX_QUEUE_ENTRIES	128	/* must be घातer of 2 */
#घोषणा TX_QUEUE_ENTRIES	16	/* must be घातer of 2 */

#घोषणा MAX_PKT_SIZE		1518
#घोषणा RX_BUF_SIZE		2044	/* must be smaller than 0x7ff */

#अगर MAX_PKT_SIZE > 0x7ff
#त्रुटि invalid MAX_PKT_SIZE
#पूर्ण_अगर

#अगर RX_BUF_SIZE > 0x7ff || RX_BUF_SIZE > PAGE_SIZE
#त्रुटि invalid RX_BUF_SIZE
#पूर्ण_अगर

/******************************************************************************
 * निजी data
 *****************************************************************************/
काष्ठा fपंचांगac100_descs अणु
	काष्ठा fपंचांगac100_rxdes rxdes[RX_QUEUE_ENTRIES];
	काष्ठा fपंचांगac100_txdes txdes[TX_QUEUE_ENTRIES];
पूर्ण;

काष्ठा fपंचांगac100 अणु
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक irq;

	काष्ठा fपंचांगac100_descs *descs;
	dma_addr_t descs_dma_addr;

	अचिन्हित पूर्णांक rx_poपूर्णांकer;
	अचिन्हित पूर्णांक tx_clean_poपूर्णांकer;
	अचिन्हित पूर्णांक tx_poपूर्णांकer;
	अचिन्हित पूर्णांक tx_pending;

	spinlock_t tx_lock;

	काष्ठा net_device *netdev;
	काष्ठा device *dev;
	काष्ठा napi_काष्ठा napi;

	काष्ठा mii_अगर_info mii;
पूर्ण;

अटल पूर्णांक fपंचांगac100_alloc_rx_page(काष्ठा fपंचांगac100 *priv,
				  काष्ठा fपंचांगac100_rxdes *rxdes, gfp_t gfp);

/******************************************************************************
 * पूर्णांकernal functions (hardware रेजिस्टर access)
 *****************************************************************************/
#घोषणा INT_MASK_ALL_ENABLED	(FTMAC100_INT_RPKT_FINISH	| \
				 FTMAC100_INT_NORXBUF		| \
				 FTMAC100_INT_XPKT_OK		| \
				 FTMAC100_INT_XPKT_LOST		| \
				 FTMAC100_INT_RPKT_LOST		| \
				 FTMAC100_INT_AHB_ERR		| \
				 FTMAC100_INT_PHYSTS_CHG)

#घोषणा INT_MASK_ALL_DISABLED	0

अटल व्योम fपंचांगac100_enable_all_पूर्णांक(काष्ठा fपंचांगac100 *priv)
अणु
	ioग_लिखो32(INT_MASK_ALL_ENABLED, priv->base + FTMAC100_OFFSET_IMR);
पूर्ण

अटल व्योम fपंचांगac100_disable_all_पूर्णांक(काष्ठा fपंचांगac100 *priv)
अणु
	ioग_लिखो32(INT_MASK_ALL_DISABLED, priv->base + FTMAC100_OFFSET_IMR);
पूर्ण

अटल व्योम fपंचांगac100_set_rx_ring_base(काष्ठा fपंचांगac100 *priv, dma_addr_t addr)
अणु
	ioग_लिखो32(addr, priv->base + FTMAC100_OFFSET_RXR_BADR);
पूर्ण

अटल व्योम fपंचांगac100_set_tx_ring_base(काष्ठा fपंचांगac100 *priv, dma_addr_t addr)
अणु
	ioग_लिखो32(addr, priv->base + FTMAC100_OFFSET_TXR_BADR);
पूर्ण

अटल व्योम fपंचांगac100_txdma_start_polling(काष्ठा fपंचांगac100 *priv)
अणु
	ioग_लिखो32(1, priv->base + FTMAC100_OFFSET_TXPD);
पूर्ण

अटल पूर्णांक fपंचांगac100_reset(काष्ठा fपंचांगac100 *priv)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	पूर्णांक i;

	/* NOTE: reset clears all रेजिस्टरs */
	ioग_लिखो32(FTMAC100_MACCR_SW_RST, priv->base + FTMAC100_OFFSET_MACCR);

	क्रम (i = 0; i < 5; i++) अणु
		अचिन्हित पूर्णांक maccr;

		maccr = ioपढ़ो32(priv->base + FTMAC100_OFFSET_MACCR);
		अगर (!(maccr & FTMAC100_MACCR_SW_RST)) अणु
			/*
			 * FTMAC100_MACCR_SW_RST cleared करोes not indicate
			 * that hardware reset completed (what the f*ck).
			 * We still need to रुको क्रम a जबतक.
			 */
			udelay(500);
			वापस 0;
		पूर्ण

		udelay(1000);
	पूर्ण

	netdev_err(netdev, "software reset failed\n");
	वापस -EIO;
पूर्ण

अटल व्योम fपंचांगac100_set_mac(काष्ठा fपंचांगac100 *priv, स्थिर अचिन्हित अक्षर *mac)
अणु
	अचिन्हित पूर्णांक maddr = mac[0] << 8 | mac[1];
	अचिन्हित पूर्णांक laddr = mac[2] << 24 | mac[3] << 16 | mac[4] << 8 | mac[5];

	ioग_लिखो32(maddr, priv->base + FTMAC100_OFFSET_MAC_MADR);
	ioग_लिखो32(laddr, priv->base + FTMAC100_OFFSET_MAC_LADR);
पूर्ण

#घोषणा MACCR_ENABLE_ALL	(FTMAC100_MACCR_XMT_EN	| \
				 FTMAC100_MACCR_RCV_EN	| \
				 FTMAC100_MACCR_XDMA_EN	| \
				 FTMAC100_MACCR_RDMA_EN	| \
				 FTMAC100_MACCR_CRC_APD	| \
				 FTMAC100_MACCR_FULLDUP	| \
				 FTMAC100_MACCR_RX_RUNT	| \
				 FTMAC100_MACCR_RX_BROADPKT)

अटल पूर्णांक fपंचांगac100_start_hw(काष्ठा fपंचांगac100 *priv)
अणु
	काष्ठा net_device *netdev = priv->netdev;

	अगर (fपंचांगac100_reset(priv))
		वापस -EIO;

	/* setup ring buffer base रेजिस्टरs */
	fपंचांगac100_set_rx_ring_base(priv,
				  priv->descs_dma_addr +
				  दुरत्व(काष्ठा fपंचांगac100_descs, rxdes));
	fपंचांगac100_set_tx_ring_base(priv,
				  priv->descs_dma_addr +
				  दुरत्व(काष्ठा fपंचांगac100_descs, txdes));

	ioग_लिखो32(FTMAC100_APTC_RXPOLL_CNT(1), priv->base + FTMAC100_OFFSET_APTC);

	fपंचांगac100_set_mac(priv, netdev->dev_addr);

	ioग_लिखो32(MACCR_ENABLE_ALL, priv->base + FTMAC100_OFFSET_MACCR);
	वापस 0;
पूर्ण

अटल व्योम fपंचांगac100_stop_hw(काष्ठा fपंचांगac100 *priv)
अणु
	ioग_लिखो32(0, priv->base + FTMAC100_OFFSET_MACCR);
पूर्ण

/******************************************************************************
 * पूर्णांकernal functions (receive descriptor)
 *****************************************************************************/
अटल bool fपंचांगac100_rxdes_first_segment(काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	वापस rxdes->rxdes0 & cpu_to_le32(FTMAC100_RXDES0_FRS);
पूर्ण

अटल bool fपंचांगac100_rxdes_last_segment(काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	वापस rxdes->rxdes0 & cpu_to_le32(FTMAC100_RXDES0_LRS);
पूर्ण

अटल bool fपंचांगac100_rxdes_owned_by_dma(काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	वापस rxdes->rxdes0 & cpu_to_le32(FTMAC100_RXDES0_RXDMA_OWN);
पूर्ण

अटल व्योम fपंचांगac100_rxdes_set_dma_own(काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	/* clear status bits */
	rxdes->rxdes0 = cpu_to_le32(FTMAC100_RXDES0_RXDMA_OWN);
पूर्ण

अटल bool fपंचांगac100_rxdes_rx_error(काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	वापस rxdes->rxdes0 & cpu_to_le32(FTMAC100_RXDES0_RX_ERR);
पूर्ण

अटल bool fपंचांगac100_rxdes_crc_error(काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	वापस rxdes->rxdes0 & cpu_to_le32(FTMAC100_RXDES0_CRC_ERR);
पूर्ण

अटल bool fपंचांगac100_rxdes_frame_too_दीर्घ(काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	वापस rxdes->rxdes0 & cpu_to_le32(FTMAC100_RXDES0_FTL);
पूर्ण

अटल bool fपंचांगac100_rxdes_runt(काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	वापस rxdes->rxdes0 & cpu_to_le32(FTMAC100_RXDES0_RUNT);
पूर्ण

अटल bool fपंचांगac100_rxdes_odd_nibble(काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	वापस rxdes->rxdes0 & cpu_to_le32(FTMAC100_RXDES0_RX_ODD_NB);
पूर्ण

अटल अचिन्हित पूर्णांक fपंचांगac100_rxdes_frame_length(काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	वापस le32_to_cpu(rxdes->rxdes0) & FTMAC100_RXDES0_RFL;
पूर्ण

अटल bool fपंचांगac100_rxdes_multicast(काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	वापस rxdes->rxdes0 & cpu_to_le32(FTMAC100_RXDES0_MULTICAST);
पूर्ण

अटल व्योम fपंचांगac100_rxdes_set_buffer_size(काष्ठा fपंचांगac100_rxdes *rxdes,
					   अचिन्हित पूर्णांक size)
अणु
	rxdes->rxdes1 &= cpu_to_le32(FTMAC100_RXDES1_EDORR);
	rxdes->rxdes1 |= cpu_to_le32(FTMAC100_RXDES1_RXBUF_SIZE(size));
पूर्ण

अटल व्योम fपंचांगac100_rxdes_set_end_of_ring(काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	rxdes->rxdes1 |= cpu_to_le32(FTMAC100_RXDES1_EDORR);
पूर्ण

अटल व्योम fपंचांगac100_rxdes_set_dma_addr(काष्ठा fपंचांगac100_rxdes *rxdes,
					dma_addr_t addr)
अणु
	rxdes->rxdes2 = cpu_to_le32(addr);
पूर्ण

अटल dma_addr_t fपंचांगac100_rxdes_get_dma_addr(काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	वापस le32_to_cpu(rxdes->rxdes2);
पूर्ण

/*
 * rxdes3 is not used by hardware. We use it to keep track of page.
 * Since hardware करोes not touch it, we can skip cpu_to_le32()/le32_to_cpu().
 */
अटल व्योम fपंचांगac100_rxdes_set_page(काष्ठा fपंचांगac100_rxdes *rxdes, काष्ठा page *page)
अणु
	rxdes->rxdes3 = (अचिन्हित पूर्णांक)page;
पूर्ण

अटल काष्ठा page *fपंचांगac100_rxdes_get_page(काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	वापस (काष्ठा page *)rxdes->rxdes3;
पूर्ण

/******************************************************************************
 * पूर्णांकernal functions (receive)
 *****************************************************************************/
अटल पूर्णांक fपंचांगac100_next_rx_poपूर्णांकer(पूर्णांक poपूर्णांकer)
अणु
	वापस (poपूर्णांकer + 1) & (RX_QUEUE_ENTRIES - 1);
पूर्ण

अटल व्योम fपंचांगac100_rx_poपूर्णांकer_advance(काष्ठा fपंचांगac100 *priv)
अणु
	priv->rx_poपूर्णांकer = fपंचांगac100_next_rx_poपूर्णांकer(priv->rx_poपूर्णांकer);
पूर्ण

अटल काष्ठा fपंचांगac100_rxdes *fपंचांगac100_current_rxdes(काष्ठा fपंचांगac100 *priv)
अणु
	वापस &priv->descs->rxdes[priv->rx_poपूर्णांकer];
पूर्ण

अटल काष्ठा fपंचांगac100_rxdes *
fपंचांगac100_rx_locate_first_segment(काष्ठा fपंचांगac100 *priv)
अणु
	काष्ठा fपंचांगac100_rxdes *rxdes = fपंचांगac100_current_rxdes(priv);

	जबतक (!fपंचांगac100_rxdes_owned_by_dma(rxdes)) अणु
		अगर (fपंचांगac100_rxdes_first_segment(rxdes))
			वापस rxdes;

		fपंचांगac100_rxdes_set_dma_own(rxdes);
		fपंचांगac100_rx_poपूर्णांकer_advance(priv);
		rxdes = fपंचांगac100_current_rxdes(priv);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool fपंचांगac100_rx_packet_error(काष्ठा fपंचांगac100 *priv,
				     काष्ठा fपंचांगac100_rxdes *rxdes)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	bool error = false;

	अगर (unlikely(fपंचांगac100_rxdes_rx_error(rxdes))) अणु
		अगर (net_ratelimit())
			netdev_info(netdev, "rx err\n");

		netdev->stats.rx_errors++;
		error = true;
	पूर्ण

	अगर (unlikely(fपंचांगac100_rxdes_crc_error(rxdes))) अणु
		अगर (net_ratelimit())
			netdev_info(netdev, "rx crc err\n");

		netdev->stats.rx_crc_errors++;
		error = true;
	पूर्ण

	अगर (unlikely(fपंचांगac100_rxdes_frame_too_दीर्घ(rxdes))) अणु
		अगर (net_ratelimit())
			netdev_info(netdev, "rx frame too long\n");

		netdev->stats.rx_length_errors++;
		error = true;
	पूर्ण अन्यथा अगर (unlikely(fपंचांगac100_rxdes_runt(rxdes))) अणु
		अगर (net_ratelimit())
			netdev_info(netdev, "rx runt\n");

		netdev->stats.rx_length_errors++;
		error = true;
	पूर्ण अन्यथा अगर (unlikely(fपंचांगac100_rxdes_odd_nibble(rxdes))) अणु
		अगर (net_ratelimit())
			netdev_info(netdev, "rx odd nibble\n");

		netdev->stats.rx_length_errors++;
		error = true;
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम fपंचांगac100_rx_drop_packet(काष्ठा fपंचांगac100 *priv)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा fपंचांगac100_rxdes *rxdes = fपंचांगac100_current_rxdes(priv);
	bool करोne = false;

	अगर (net_ratelimit())
		netdev_dbg(netdev, "drop packet %p\n", rxdes);

	करो अणु
		अगर (fपंचांगac100_rxdes_last_segment(rxdes))
			करोne = true;

		fपंचांगac100_rxdes_set_dma_own(rxdes);
		fपंचांगac100_rx_poपूर्णांकer_advance(priv);
		rxdes = fपंचांगac100_current_rxdes(priv);
	पूर्ण जबतक (!करोne && !fपंचांगac100_rxdes_owned_by_dma(rxdes));

	netdev->stats.rx_dropped++;
पूर्ण

अटल bool fपंचांगac100_rx_packet(काष्ठा fपंचांगac100 *priv, पूर्णांक *processed)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा fपंचांगac100_rxdes *rxdes;
	काष्ठा sk_buff *skb;
	काष्ठा page *page;
	dma_addr_t map;
	पूर्णांक length;
	bool ret;

	rxdes = fपंचांगac100_rx_locate_first_segment(priv);
	अगर (!rxdes)
		वापस false;

	अगर (unlikely(fपंचांगac100_rx_packet_error(priv, rxdes))) अणु
		fपंचांगac100_rx_drop_packet(priv);
		वापस true;
	पूर्ण

	/*
	 * It is impossible to get multi-segment packets
	 * because we always provide big enough receive buffers.
	 */
	ret = fपंचांगac100_rxdes_last_segment(rxdes);
	BUG_ON(!ret);

	/* start processing */
	skb = netdev_alloc_skb_ip_align(netdev, 128);
	अगर (unlikely(!skb)) अणु
		अगर (net_ratelimit())
			netdev_err(netdev, "rx skb alloc failed\n");

		fपंचांगac100_rx_drop_packet(priv);
		वापस true;
	पूर्ण

	अगर (unlikely(fपंचांगac100_rxdes_multicast(rxdes)))
		netdev->stats.multicast++;

	map = fपंचांगac100_rxdes_get_dma_addr(rxdes);
	dma_unmap_page(priv->dev, map, RX_BUF_SIZE, DMA_FROM_DEVICE);

	length = fपंचांगac100_rxdes_frame_length(rxdes);
	page = fपंचांगac100_rxdes_get_page(rxdes);
	skb_fill_page_desc(skb, 0, page, 0, length);
	skb->len += length;
	skb->data_len += length;

	अगर (length > 128) अणु
		skb->truesize += PAGE_SIZE;
		/* We pull the minimum amount पूर्णांकo linear part */
		__pskb_pull_tail(skb, ETH_HLEN);
	पूर्ण अन्यथा अणु
		/* Small frames are copied पूर्णांकo linear part to मुक्त one page */
		__pskb_pull_tail(skb, length);
	पूर्ण
	fपंचांगac100_alloc_rx_page(priv, rxdes, GFP_ATOMIC);

	fपंचांगac100_rx_poपूर्णांकer_advance(priv);

	skb->protocol = eth_type_trans(skb, netdev);

	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += skb->len;

	/* push packet to protocol stack */
	netअगर_receive_skb(skb);

	(*processed)++;
	वापस true;
पूर्ण

/******************************************************************************
 * पूर्णांकernal functions (transmit descriptor)
 *****************************************************************************/
अटल व्योम fपंचांगac100_txdes_reset(काष्ठा fपंचांगac100_txdes *txdes)
अणु
	/* clear all except end of ring bit */
	txdes->txdes0 = 0;
	txdes->txdes1 &= cpu_to_le32(FTMAC100_TXDES1_EDOTR);
	txdes->txdes2 = 0;
	txdes->txdes3 = 0;
पूर्ण

अटल bool fपंचांगac100_txdes_owned_by_dma(काष्ठा fपंचांगac100_txdes *txdes)
अणु
	वापस txdes->txdes0 & cpu_to_le32(FTMAC100_TXDES0_TXDMA_OWN);
पूर्ण

अटल व्योम fपंचांगac100_txdes_set_dma_own(काष्ठा fपंचांगac100_txdes *txdes)
अणु
	/*
	 * Make sure dma own bit will not be set beक्रमe any other
	 * descriptor fields.
	 */
	wmb();
	txdes->txdes0 |= cpu_to_le32(FTMAC100_TXDES0_TXDMA_OWN);
पूर्ण

अटल bool fपंचांगac100_txdes_excessive_collision(काष्ठा fपंचांगac100_txdes *txdes)
अणु
	वापस txdes->txdes0 & cpu_to_le32(FTMAC100_TXDES0_TXPKT_EXSCOL);
पूर्ण

अटल bool fपंचांगac100_txdes_late_collision(काष्ठा fपंचांगac100_txdes *txdes)
अणु
	वापस txdes->txdes0 & cpu_to_le32(FTMAC100_TXDES0_TXPKT_LATECOL);
पूर्ण

अटल व्योम fपंचांगac100_txdes_set_end_of_ring(काष्ठा fपंचांगac100_txdes *txdes)
अणु
	txdes->txdes1 |= cpu_to_le32(FTMAC100_TXDES1_EDOTR);
पूर्ण

अटल व्योम fपंचांगac100_txdes_set_first_segment(काष्ठा fपंचांगac100_txdes *txdes)
अणु
	txdes->txdes1 |= cpu_to_le32(FTMAC100_TXDES1_FTS);
पूर्ण

अटल व्योम fपंचांगac100_txdes_set_last_segment(काष्ठा fपंचांगac100_txdes *txdes)
अणु
	txdes->txdes1 |= cpu_to_le32(FTMAC100_TXDES1_LTS);
पूर्ण

अटल व्योम fपंचांगac100_txdes_set_txपूर्णांक(काष्ठा fपंचांगac100_txdes *txdes)
अणु
	txdes->txdes1 |= cpu_to_le32(FTMAC100_TXDES1_TXIC);
पूर्ण

अटल व्योम fपंचांगac100_txdes_set_buffer_size(काष्ठा fपंचांगac100_txdes *txdes,
					   अचिन्हित पूर्णांक len)
अणु
	txdes->txdes1 |= cpu_to_le32(FTMAC100_TXDES1_TXBUF_SIZE(len));
पूर्ण

अटल व्योम fपंचांगac100_txdes_set_dma_addr(काष्ठा fपंचांगac100_txdes *txdes,
					dma_addr_t addr)
अणु
	txdes->txdes2 = cpu_to_le32(addr);
पूर्ण

अटल dma_addr_t fपंचांगac100_txdes_get_dma_addr(काष्ठा fपंचांगac100_txdes *txdes)
अणु
	वापस le32_to_cpu(txdes->txdes2);
पूर्ण

/*
 * txdes3 is not used by hardware. We use it to keep track of socket buffer.
 * Since hardware करोes not touch it, we can skip cpu_to_le32()/le32_to_cpu().
 */
अटल व्योम fपंचांगac100_txdes_set_skb(काष्ठा fपंचांगac100_txdes *txdes, काष्ठा sk_buff *skb)
अणु
	txdes->txdes3 = (अचिन्हित पूर्णांक)skb;
पूर्ण

अटल काष्ठा sk_buff *fपंचांगac100_txdes_get_skb(काष्ठा fपंचांगac100_txdes *txdes)
अणु
	वापस (काष्ठा sk_buff *)txdes->txdes3;
पूर्ण

/******************************************************************************
 * पूर्णांकernal functions (transmit)
 *****************************************************************************/
अटल पूर्णांक fपंचांगac100_next_tx_poपूर्णांकer(पूर्णांक poपूर्णांकer)
अणु
	वापस (poपूर्णांकer + 1) & (TX_QUEUE_ENTRIES - 1);
पूर्ण

अटल व्योम fपंचांगac100_tx_poपूर्णांकer_advance(काष्ठा fपंचांगac100 *priv)
अणु
	priv->tx_poपूर्णांकer = fपंचांगac100_next_tx_poपूर्णांकer(priv->tx_poपूर्णांकer);
पूर्ण

अटल व्योम fपंचांगac100_tx_clean_poपूर्णांकer_advance(काष्ठा fपंचांगac100 *priv)
अणु
	priv->tx_clean_poपूर्णांकer = fपंचांगac100_next_tx_poपूर्णांकer(priv->tx_clean_poपूर्णांकer);
पूर्ण

अटल काष्ठा fपंचांगac100_txdes *fपंचांगac100_current_txdes(काष्ठा fपंचांगac100 *priv)
अणु
	वापस &priv->descs->txdes[priv->tx_poपूर्णांकer];
पूर्ण

अटल काष्ठा fपंचांगac100_txdes *fपंचांगac100_current_clean_txdes(काष्ठा fपंचांगac100 *priv)
अणु
	वापस &priv->descs->txdes[priv->tx_clean_poपूर्णांकer];
पूर्ण

अटल bool fपंचांगac100_tx_complete_packet(काष्ठा fपंचांगac100 *priv)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा fपंचांगac100_txdes *txdes;
	काष्ठा sk_buff *skb;
	dma_addr_t map;

	अगर (priv->tx_pending == 0)
		वापस false;

	txdes = fपंचांगac100_current_clean_txdes(priv);

	अगर (fपंचांगac100_txdes_owned_by_dma(txdes))
		वापस false;

	skb = fपंचांगac100_txdes_get_skb(txdes);
	map = fपंचांगac100_txdes_get_dma_addr(txdes);

	अगर (unlikely(fपंचांगac100_txdes_excessive_collision(txdes) ||
		     fपंचांगac100_txdes_late_collision(txdes))) अणु
		/*
		 * packet transmitted to ethernet lost due to late collision
		 * or excessive collision
		 */
		netdev->stats.tx_पातed_errors++;
	पूर्ण अन्यथा अणु
		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += skb->len;
	पूर्ण

	dma_unmap_single(priv->dev, map, skb_headlen(skb), DMA_TO_DEVICE);
	dev_kमुक्त_skb(skb);

	fपंचांगac100_txdes_reset(txdes);

	fपंचांगac100_tx_clean_poपूर्णांकer_advance(priv);

	spin_lock(&priv->tx_lock);
	priv->tx_pending--;
	spin_unlock(&priv->tx_lock);
	netअगर_wake_queue(netdev);

	वापस true;
पूर्ण

अटल व्योम fपंचांगac100_tx_complete(काष्ठा fपंचांगac100 *priv)
अणु
	जबतक (fपंचांगac100_tx_complete_packet(priv))
		;
पूर्ण

अटल netdev_tx_t fपंचांगac100_xmit(काष्ठा fपंचांगac100 *priv, काष्ठा sk_buff *skb,
				 dma_addr_t map)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा fपंचांगac100_txdes *txdes;
	अचिन्हित पूर्णांक len = (skb->len < ETH_ZLEN) ? ETH_ZLEN : skb->len;

	txdes = fपंचांगac100_current_txdes(priv);
	fपंचांगac100_tx_poपूर्णांकer_advance(priv);

	/* setup TX descriptor */
	fपंचांगac100_txdes_set_skb(txdes, skb);
	fपंचांगac100_txdes_set_dma_addr(txdes, map);

	fपंचांगac100_txdes_set_first_segment(txdes);
	fपंचांगac100_txdes_set_last_segment(txdes);
	fपंचांगac100_txdes_set_txपूर्णांक(txdes);
	fपंचांगac100_txdes_set_buffer_size(txdes, len);

	spin_lock(&priv->tx_lock);
	priv->tx_pending++;
	अगर (priv->tx_pending == TX_QUEUE_ENTRIES)
		netअगर_stop_queue(netdev);

	/* start transmit */
	fपंचांगac100_txdes_set_dma_own(txdes);
	spin_unlock(&priv->tx_lock);

	fपंचांगac100_txdma_start_polling(priv);
	वापस NETDEV_TX_OK;
पूर्ण

/******************************************************************************
 * पूर्णांकernal functions (buffer)
 *****************************************************************************/
अटल पूर्णांक fपंचांगac100_alloc_rx_page(काष्ठा fपंचांगac100 *priv,
				  काष्ठा fपंचांगac100_rxdes *rxdes, gfp_t gfp)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा page *page;
	dma_addr_t map;

	page = alloc_page(gfp);
	अगर (!page) अणु
		अगर (net_ratelimit())
			netdev_err(netdev, "failed to allocate rx page\n");
		वापस -ENOMEM;
	पूर्ण

	map = dma_map_page(priv->dev, page, 0, RX_BUF_SIZE, DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(priv->dev, map))) अणु
		अगर (net_ratelimit())
			netdev_err(netdev, "failed to map rx page\n");
		__मुक्त_page(page);
		वापस -ENOMEM;
	पूर्ण

	fपंचांगac100_rxdes_set_page(rxdes, page);
	fपंचांगac100_rxdes_set_dma_addr(rxdes, map);
	fपंचांगac100_rxdes_set_buffer_size(rxdes, RX_BUF_SIZE);
	fपंचांगac100_rxdes_set_dma_own(rxdes);
	वापस 0;
पूर्ण

अटल व्योम fपंचांगac100_मुक्त_buffers(काष्ठा fपंचांगac100 *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RX_QUEUE_ENTRIES; i++) अणु
		काष्ठा fपंचांगac100_rxdes *rxdes = &priv->descs->rxdes[i];
		काष्ठा page *page = fपंचांगac100_rxdes_get_page(rxdes);
		dma_addr_t map = fपंचांगac100_rxdes_get_dma_addr(rxdes);

		अगर (!page)
			जारी;

		dma_unmap_page(priv->dev, map, RX_BUF_SIZE, DMA_FROM_DEVICE);
		__मुक्त_page(page);
	पूर्ण

	क्रम (i = 0; i < TX_QUEUE_ENTRIES; i++) अणु
		काष्ठा fपंचांगac100_txdes *txdes = &priv->descs->txdes[i];
		काष्ठा sk_buff *skb = fपंचांगac100_txdes_get_skb(txdes);
		dma_addr_t map = fपंचांगac100_txdes_get_dma_addr(txdes);

		अगर (!skb)
			जारी;

		dma_unmap_single(priv->dev, map, skb_headlen(skb), DMA_TO_DEVICE);
		dev_kमुक्त_skb(skb);
	पूर्ण

	dma_मुक्त_coherent(priv->dev, माप(काष्ठा fपंचांगac100_descs),
			  priv->descs, priv->descs_dma_addr);
पूर्ण

अटल पूर्णांक fपंचांगac100_alloc_buffers(काष्ठा fपंचांगac100 *priv)
अणु
	पूर्णांक i;

	priv->descs = dma_alloc_coherent(priv->dev,
					 माप(काष्ठा fपंचांगac100_descs),
					 &priv->descs_dma_addr, GFP_KERNEL);
	अगर (!priv->descs)
		वापस -ENOMEM;

	/* initialize RX ring */
	fपंचांगac100_rxdes_set_end_of_ring(&priv->descs->rxdes[RX_QUEUE_ENTRIES - 1]);

	क्रम (i = 0; i < RX_QUEUE_ENTRIES; i++) अणु
		काष्ठा fपंचांगac100_rxdes *rxdes = &priv->descs->rxdes[i];

		अगर (fपंचांगac100_alloc_rx_page(priv, rxdes, GFP_KERNEL))
			जाओ err;
	पूर्ण

	/* initialize TX ring */
	fपंचांगac100_txdes_set_end_of_ring(&priv->descs->txdes[TX_QUEUE_ENTRIES - 1]);
	वापस 0;

err:
	fपंचांगac100_मुक्त_buffers(priv);
	वापस -ENOMEM;
पूर्ण

/******************************************************************************
 * काष्ठा mii_अगर_info functions
 *****************************************************************************/
अटल पूर्णांक fपंचांगac100_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक reg)
अणु
	काष्ठा fपंचांगac100 *priv = netdev_priv(netdev);
	अचिन्हित पूर्णांक phycr;
	पूर्णांक i;

	phycr = FTMAC100_PHYCR_PHYAD(phy_id) |
		FTMAC100_PHYCR_REGAD(reg) |
		FTMAC100_PHYCR_MIIRD;

	ioग_लिखो32(phycr, priv->base + FTMAC100_OFFSET_PHYCR);

	क्रम (i = 0; i < 10; i++) अणु
		phycr = ioपढ़ो32(priv->base + FTMAC100_OFFSET_PHYCR);

		अगर ((phycr & FTMAC100_PHYCR_MIIRD) == 0)
			वापस phycr & FTMAC100_PHYCR_MIIRDATA;

		udelay(100);
	पूर्ण

	netdev_err(netdev, "mdio read timed out\n");
	वापस 0;
पूर्ण

अटल व्योम fपंचांगac100_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक reg,
				पूर्णांक data)
अणु
	काष्ठा fपंचांगac100 *priv = netdev_priv(netdev);
	अचिन्हित पूर्णांक phycr;
	पूर्णांक i;

	phycr = FTMAC100_PHYCR_PHYAD(phy_id) |
		FTMAC100_PHYCR_REGAD(reg) |
		FTMAC100_PHYCR_MIIWR;

	data = FTMAC100_PHYWDATA_MIIWDATA(data);

	ioग_लिखो32(data, priv->base + FTMAC100_OFFSET_PHYWDATA);
	ioग_लिखो32(phycr, priv->base + FTMAC100_OFFSET_PHYCR);

	क्रम (i = 0; i < 10; i++) अणु
		phycr = ioपढ़ो32(priv->base + FTMAC100_OFFSET_PHYCR);

		अगर ((phycr & FTMAC100_PHYCR_MIIWR) == 0)
			वापस;

		udelay(100);
	पूर्ण

	netdev_err(netdev, "mdio write timed out\n");
पूर्ण

/******************************************************************************
 * काष्ठा ethtool_ops functions
 *****************************************************************************/
अटल व्योम fपंचांगac100_get_drvinfo(काष्ठा net_device *netdev,
				 काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, dev_name(&netdev->dev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक fपंचांगac100_get_link_ksettings(काष्ठा net_device *netdev,
				       काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा fपंचांगac100 *priv = netdev_priv(netdev);

	mii_ethtool_get_link_ksettings(&priv->mii, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक fपंचांगac100_set_link_ksettings(काष्ठा net_device *netdev,
				       स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा fपंचांगac100 *priv = netdev_priv(netdev);
	वापस mii_ethtool_set_link_ksettings(&priv->mii, cmd);
पूर्ण

अटल पूर्णांक fपंचांगac100_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा fपंचांगac100 *priv = netdev_priv(netdev);
	वापस mii_nway_restart(&priv->mii);
पूर्ण

अटल u32 fपंचांगac100_get_link(काष्ठा net_device *netdev)
अणु
	काष्ठा fपंचांगac100 *priv = netdev_priv(netdev);
	वापस mii_link_ok(&priv->mii);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops fपंचांगac100_ethtool_ops = अणु
	.get_drvinfo		= fपंचांगac100_get_drvinfo,
	.nway_reset		= fपंचांगac100_nway_reset,
	.get_link		= fपंचांगac100_get_link,
	.get_link_ksettings	= fपंचांगac100_get_link_ksettings,
	.set_link_ksettings	= fपंचांगac100_set_link_ksettings,
पूर्ण;

/******************************************************************************
 * पूर्णांकerrupt handler
 *****************************************************************************/
अटल irqवापस_t fपंचांगac100_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *netdev = dev_id;
	काष्ठा fपंचांगac100 *priv = netdev_priv(netdev);

	/* Disable पूर्णांकerrupts क्रम polling */
	fपंचांगac100_disable_all_पूर्णांक(priv);
	अगर (likely(netअगर_running(netdev)))
		napi_schedule(&priv->napi);

	वापस IRQ_HANDLED;
पूर्ण

/******************************************************************************
 * काष्ठा napi_काष्ठा functions
 *****************************************************************************/
अटल पूर्णांक fपंचांगac100_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा fपंचांगac100 *priv = container_of(napi, काष्ठा fपंचांगac100, napi);
	काष्ठा net_device *netdev = priv->netdev;
	अचिन्हित पूर्णांक status;
	bool completed = true;
	पूर्णांक rx = 0;

	status = ioपढ़ो32(priv->base + FTMAC100_OFFSET_ISR);

	अगर (status & (FTMAC100_INT_RPKT_FINISH | FTMAC100_INT_NORXBUF)) अणु
		/*
		 * FTMAC100_INT_RPKT_FINISH:
		 *	RX DMA has received packets पूर्णांकo RX buffer successfully
		 *
		 * FTMAC100_INT_NORXBUF:
		 *	RX buffer unavailable
		 */
		bool retry;

		करो अणु
			retry = fपंचांगac100_rx_packet(priv, &rx);
		पूर्ण जबतक (retry && rx < budget);

		अगर (retry && rx == budget)
			completed = false;
	पूर्ण

	अगर (status & (FTMAC100_INT_XPKT_OK | FTMAC100_INT_XPKT_LOST)) अणु
		/*
		 * FTMAC100_INT_XPKT_OK:
		 *	packet transmitted to ethernet successfully
		 *
		 * FTMAC100_INT_XPKT_LOST:
		 *	packet transmitted to ethernet lost due to late
		 *	collision or excessive collision
		 */
		fपंचांगac100_tx_complete(priv);
	पूर्ण

	अगर (status & (FTMAC100_INT_NORXBUF | FTMAC100_INT_RPKT_LOST |
		      FTMAC100_INT_AHB_ERR | FTMAC100_INT_PHYSTS_CHG)) अणु
		अगर (net_ratelimit())
			netdev_info(netdev, "[ISR] = 0x%x: %s%s%s%s\n", status,
				    status & FTMAC100_INT_NORXBUF ? "NORXBUF " : "",
				    status & FTMAC100_INT_RPKT_LOST ? "RPKT_LOST " : "",
				    status & FTMAC100_INT_AHB_ERR ? "AHB_ERR " : "",
				    status & FTMAC100_INT_PHYSTS_CHG ? "PHYSTS_CHG" : "");

		अगर (status & FTMAC100_INT_NORXBUF) अणु
			/* RX buffer unavailable */
			netdev->stats.rx_over_errors++;
		पूर्ण

		अगर (status & FTMAC100_INT_RPKT_LOST) अणु
			/* received packet lost due to RX FIFO full */
			netdev->stats.rx_fअगरo_errors++;
		पूर्ण

		अगर (status & FTMAC100_INT_PHYSTS_CHG) अणु
			/* PHY link status change */
			mii_check_link(&priv->mii);
		पूर्ण
	पूर्ण

	अगर (completed) अणु
		/* stop polling */
		napi_complete(napi);
		fपंचांगac100_enable_all_पूर्णांक(priv);
	पूर्ण

	वापस rx;
पूर्ण

/******************************************************************************
 * काष्ठा net_device_ops functions
 *****************************************************************************/
अटल पूर्णांक fपंचांगac100_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा fपंचांगac100 *priv = netdev_priv(netdev);
	पूर्णांक err;

	err = fपंचांगac100_alloc_buffers(priv);
	अगर (err) अणु
		netdev_err(netdev, "failed to allocate buffers\n");
		जाओ err_alloc;
	पूर्ण

	err = request_irq(priv->irq, fपंचांगac100_पूर्णांकerrupt, 0, netdev->name, netdev);
	अगर (err) अणु
		netdev_err(netdev, "failed to request irq %d\n", priv->irq);
		जाओ err_irq;
	पूर्ण

	priv->rx_poपूर्णांकer = 0;
	priv->tx_clean_poपूर्णांकer = 0;
	priv->tx_poपूर्णांकer = 0;
	priv->tx_pending = 0;

	err = fपंचांगac100_start_hw(priv);
	अगर (err)
		जाओ err_hw;

	napi_enable(&priv->napi);
	netअगर_start_queue(netdev);

	fपंचांगac100_enable_all_पूर्णांक(priv);

	वापस 0;

err_hw:
	मुक्त_irq(priv->irq, netdev);
err_irq:
	fपंचांगac100_मुक्त_buffers(priv);
err_alloc:
	वापस err;
पूर्ण

अटल पूर्णांक fपंचांगac100_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा fपंचांगac100 *priv = netdev_priv(netdev);

	fपंचांगac100_disable_all_पूर्णांक(priv);
	netअगर_stop_queue(netdev);
	napi_disable(&priv->napi);
	fपंचांगac100_stop_hw(priv);
	मुक्त_irq(priv->irq, netdev);
	fपंचांगac100_मुक्त_buffers(priv);

	वापस 0;
पूर्ण

अटल netdev_tx_t
fपंचांगac100_hard_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा fपंचांगac100 *priv = netdev_priv(netdev);
	dma_addr_t map;

	अगर (unlikely(skb->len > MAX_PKT_SIZE)) अणु
		अगर (net_ratelimit())
			netdev_dbg(netdev, "tx packet too big\n");

		netdev->stats.tx_dropped++;
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	map = dma_map_single(priv->dev, skb->data, skb_headlen(skb), DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(priv->dev, map))) अणु
		/* drop packet */
		अगर (net_ratelimit())
			netdev_err(netdev, "map socket buffer failed\n");

		netdev->stats.tx_dropped++;
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	वापस fपंचांगac100_xmit(priv, skb, map);
पूर्ण

/* optional */
अटल पूर्णांक fपंचांगac100_करो_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा fपंचांगac100 *priv = netdev_priv(netdev);
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);

	वापस generic_mii_ioctl(&priv->mii, data, cmd, शून्य);
पूर्ण

अटल स्थिर काष्ठा net_device_ops fपंचांगac100_netdev_ops = अणु
	.nकरो_खोलो		= fपंचांगac100_खोलो,
	.nकरो_stop		= fपंचांगac100_stop,
	.nकरो_start_xmit		= fपंचांगac100_hard_start_xmit,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= fपंचांगac100_करो_ioctl,
पूर्ण;

/******************************************************************************
 * काष्ठा platक्रमm_driver functions
 *****************************************************************************/
अटल पूर्णांक fपंचांगac100_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	पूर्णांक irq;
	काष्ठा net_device *netdev;
	काष्ठा fपंचांगac100 *priv;
	पूर्णांक err;

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
	netdev->ethtool_ops = &fपंचांगac100_ethtool_ops;
	netdev->netdev_ops = &fपंचांगac100_netdev_ops;

	platक्रमm_set_drvdata(pdev, netdev);

	/* setup निजी data */
	priv = netdev_priv(netdev);
	priv->netdev = netdev;
	priv->dev = &pdev->dev;

	spin_lock_init(&priv->tx_lock);

	/* initialize NAPI */
	netअगर_napi_add(netdev, &priv->napi, fपंचांगac100_poll, 64);

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

	priv->irq = irq;

	/* initialize काष्ठा mii_अगर_info */
	priv->mii.phy_id	= 0;
	priv->mii.phy_id_mask	= 0x1f;
	priv->mii.reg_num_mask	= 0x1f;
	priv->mii.dev		= netdev;
	priv->mii.mdio_पढ़ो	= fपंचांगac100_mdio_पढ़ो;
	priv->mii.mdio_ग_लिखो	= fपंचांगac100_mdio_ग_लिखो;

	/* रेजिस्टर network device */
	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register netdev\n");
		जाओ err_रेजिस्टर_netdev;
	पूर्ण

	netdev_info(netdev, "irq %d, mapped at %p\n", priv->irq, priv->base);

	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		eth_hw_addr_अक्रमom(netdev);
		netdev_info(netdev, "generated random MAC address %pM\n",
			    netdev->dev_addr);
	पूर्ण

	वापस 0;

err_रेजिस्टर_netdev:
	iounmap(priv->base);
err_ioremap:
	release_resource(priv->res);
err_req_mem:
	netअगर_napi_del(&priv->napi);
	मुक्त_netdev(netdev);
err_alloc_etherdev:
	वापस err;
पूर्ण

अटल पूर्णांक fपंचांगac100_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *netdev;
	काष्ठा fपंचांगac100 *priv;

	netdev = platक्रमm_get_drvdata(pdev);
	priv = netdev_priv(netdev);

	unरेजिस्टर_netdev(netdev);

	iounmap(priv->base);
	release_resource(priv->res);

	netअगर_napi_del(&priv->napi);
	मुक्त_netdev(netdev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fपंचांगac100_of_ids[] = अणु
	अणु .compatible = "andestech,atmac100" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver fपंचांगac100_driver = अणु
	.probe		= fपंचांगac100_probe,
	.हटाओ		= fपंचांगac100_हटाओ,
	.driver		= अणु
		.name	= DRV_NAME,
		.of_match_table = fपंचांगac100_of_ids
	पूर्ण,
पूर्ण;

/******************************************************************************
 * initialization / finalization
 *****************************************************************************/
module_platक्रमm_driver(fपंचांगac100_driver);

MODULE_AUTHOR("Po-Yu Chuang <ratbert@faraday-tech.com>");
MODULE_DESCRIPTION("FTMAC100 driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(of, fपंचांगac100_of_ids);
