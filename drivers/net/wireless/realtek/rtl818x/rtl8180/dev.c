<शैली गुरु>

/* Linux device driver क्रम RTL8180 / RTL8185 / RTL8187SE
 *
 * Copyright 2007 Michael Wu <flamingice@sourmilk.net>
 * Copyright 2007,2014 Andrea Merello <andrea.merello@gmail.com>
 *
 * Based on the r8180 driver, which is:
 * Copyright 2004-2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 *
 * Thanks to Realtek क्रम their support!
 *
 ************************************************************************
 *
 * The driver was extended to the RTL8187SE in 2014 by
 * Andrea Merello <andrea.merello@gmail.com>
 *
 * based also on:
 *  - portions of rtl8187se Linux staging driver, Copyright Realtek corp.
 *    (available in drivers/staging/rtl8187se directory of Linux 3.14)
 *  - other GPL, unpublished (until now), Linux driver code,
 *    Copyright Larry Finger <Larry.Finger@lwfinger.net>
 *
 * A huge thanks goes to Sara V. Nari who क्रमgives me when I'm
 * sitting in front of my laptop at evening, week-end, night...
 *
 * A special thanks goes to Antonio Cuni, who helped me with
 * some python userspace stuff I used to debug RTL8187SE code, and who
 * bought a laptop with an unsupported Wi-Fi card some years ago...
 *
 * Thanks to Larry Finger क्रम writing some code क्रम rtl8187se and क्रम
 * his suggestions.
 *
 * Thanks to Dan Carpenter क्रम reviewing my initial patch and क्रम his
 * suggestions.
 *
 * Thanks to Bernhard Schअगरfner क्रम his help in testing and क्रम his
 * suggestions.
 *
 ************************************************************************
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/eeprom_93cx6.h>
#समावेश <linux/module.h>
#समावेश <net/mac80211.h>

#समावेश "rtl8180.h"
#समावेश "rtl8225.h"
#समावेश "sa2400.h"
#समावेश "max2820.h"
#समावेश "grf5101.h"
#समावेश "rtl8225se.h"

MODULE_AUTHOR("Michael Wu <flamingice@sourmilk.net>");
MODULE_AUTHOR("Andrea Merello <andrea.merello@gmail.com>");
MODULE_DESCRIPTION("RTL8180 / RTL8185 / RTL8187SE PCI wireless driver");
MODULE_LICENSE("GPL");

अटल स्थिर काष्ठा pci_device_id rtl8180_table[] = अणु

	/* rtl8187se */
	अणु PCI_DEVICE(PCI_VENDOR_ID_REALTEK, 0x8199) पूर्ण,

	/* rtl8185 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_REALTEK, 0x8185) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BELKIN, 0x700f) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BELKIN, 0x701f) पूर्ण,

	/* rtl8180 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_REALTEK, 0x8180) पूर्ण,
	अणु PCI_DEVICE(0x1799, 0x6001) पूर्ण,
	अणु PCI_DEVICE(0x1799, 0x6020) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DLINK, 0x3300) पूर्ण,
	अणु PCI_DEVICE(0x1186, 0x3301) पूर्ण,
	अणु PCI_DEVICE(0x1432, 0x7106) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, rtl8180_table);

अटल स्थिर काष्ठा ieee80211_rate rtl818x_rates[] = अणु
	अणु .bitrate = 10, .hw_value = 0, पूर्ण,
	अणु .bitrate = 20, .hw_value = 1, पूर्ण,
	अणु .bitrate = 55, .hw_value = 2, पूर्ण,
	अणु .bitrate = 110, .hw_value = 3, पूर्ण,
	अणु .bitrate = 60, .hw_value = 4, पूर्ण,
	अणु .bitrate = 90, .hw_value = 5, पूर्ण,
	अणु .bitrate = 120, .hw_value = 6, पूर्ण,
	अणु .bitrate = 180, .hw_value = 7, पूर्ण,
	अणु .bitrate = 240, .hw_value = 8, पूर्ण,
	अणु .bitrate = 360, .hw_value = 9, पूर्ण,
	अणु .bitrate = 480, .hw_value = 10, पूर्ण,
	अणु .bitrate = 540, .hw_value = 11, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_channel rtl818x_channels[] = अणु
	अणु .center_freq = 2412 पूर्ण,
	अणु .center_freq = 2417 पूर्ण,
	अणु .center_freq = 2422 पूर्ण,
	अणु .center_freq = 2427 पूर्ण,
	अणु .center_freq = 2432 पूर्ण,
	अणु .center_freq = 2437 पूर्ण,
	अणु .center_freq = 2442 पूर्ण,
	अणु .center_freq = 2447 पूर्ण,
	अणु .center_freq = 2452 पूर्ण,
	अणु .center_freq = 2457 पूर्ण,
	अणु .center_freq = 2462 पूर्ण,
	अणु .center_freq = 2467 पूर्ण,
	अणु .center_freq = 2472 पूर्ण,
	अणु .center_freq = 2484 पूर्ण,
पूर्ण;

/* Queues क्रम rtl8187se card
 *
 * name | reg  |  queue
 *  BC  |  7   |   6
 *  MG  |  1   |   0
 *  HI  |  6   |   1
 *  VO  |  5   |   2
 *  VI  |  4   |   3
 *  BE  |  3   |   4
 *  BK  |  2   |   5
 *
 * The complete map क्रम DMA kick reg using use all queue is:
 * अटल स्थिर पूर्णांक rtl8187se_queues_map[RTL8187SE_NR_TX_QUEUES] =
 *	अणु1, 6, 5, 4, 3, 2, 7पूर्ण;
 *
 * .. but.. Because क्रम mac80211 4 queues are enough क्रम QoS we use this
 *
 * name | reg  |  queue
 *  BC  |  7   |   4  <- currently not used yet
 *  MG  |  1   |   x  <- Not used
 *  HI  |  6   |   x  <- Not used
 *  VO  |  5   |   0  <- used
 *  VI  |  4   |   1  <- used
 *  BE  |  3   |   2  <- used
 *  BK  |  2   |   3  <- used
 *
 * Beacon queue could be used, but this is not finished yet.
 *
 * I thougth about using the other two queues but I decided not to करो this:
 *
 * - I'm unsure whether the mac80211 will ever try to use more than 4 queues
 *   by itself.
 *
 * - I could route MGMT frames (currently sent over VO queue) to the MGMT
 *   queue but since mac80211 will करो not know about it, I will probably gain
 *   some HW priority whenever the VO queue is not empty, but this gain is
 *   limited by the fact that I had to stop the mac80211 queue whenever one of
 *   the VO or MGMT queues is full, stopping also submitting of MGMT frame
 *   to the driver.
 *
 * - I करोn't know how to set in the HW the contention winकरोw params क्रम MGMT
 *   and HI-prio queues.
 */

अटल स्थिर पूर्णांक rtl8187se_queues_map[RTL8187SE_NR_TX_QUEUES] = अणु5, 4, 3, 2, 7पूर्ण;

/* Queues क्रम rtl8180/rtl8185 cards
 *
 * name | reg  |  prio
 *  BC  |  7   |   3
 *  HI  |  6   |   0
 *  NO  |  5   |   1
 *  LO  |  4   |   2
 *
 * The complete map क्रम DMA kick reg using all queue is:
 * अटल स्थिर पूर्णांक rtl8180_queues_map[RTL8180_NR_TX_QUEUES] = अणु6, 5, 4, 7पूर्ण;
 *
 * .. but .. Because the mac80211 needs at least 4 queues क्रम QoS or
 * otherwise QoS can't be करोne, we use just one.
 * Beacon queue could be used, but this is not finished yet.
 * Actual map is:
 *
 * name | reg  |  prio
 *  BC  |  7   |   1  <- currently not used yet.
 *  HI  |  6   |   x  <- not used
 *  NO  |  5   |   x  <- not used
 *  LO  |  4   |   0  <- used
 */

अटल स्थिर पूर्णांक rtl8180_queues_map[RTL8180_NR_TX_QUEUES] = अणु4, 7पूर्ण;

/* LNA gain table क्रम rtl8187se */
अटल स्थिर u8 rtl8187se_lna_gain[4] = अणु02, 17, 29, 39पूर्ण;

व्योम rtl8180_ग_लिखो_phy(काष्ठा ieee80211_hw *dev, u8 addr, u32 data)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	पूर्णांक i = 10;
	u32 buf;

	buf = (data << 8) | addr;

	rtl818x_ioग_लिखो32(priv, (__le32 __iomem *)&priv->map->PHY[0], buf | 0x80);
	जबतक (i--) अणु
		rtl818x_ioग_लिखो32(priv, (__le32 __iomem *)&priv->map->PHY[0], buf);
		अगर (rtl818x_ioपढ़ो8(priv, &priv->map->PHY[2]) == (data & 0xFF))
			वापस;
	पूर्ण
पूर्ण

अटल व्योम rtl8180_handle_rx(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	काष्ठा rtl818x_rx_cmd_desc *cmd_desc;
	अचिन्हित पूर्णांक count = 32;
	u8 agc, sq;
	s8 संकेत = 1;
	dma_addr_t mapping;

	जबतक (count--) अणु
		व्योम *entry = priv->rx_ring + priv->rx_idx * priv->rx_ring_sz;
		काष्ठा sk_buff *skb = priv->rx_buf[priv->rx_idx];
		u32 flags, flags2, flags3 = 0;
		u64 tsft;

		अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) अणु
			काष्ठा rtl8187se_rx_desc *desc = entry;

			flags = le32_to_cpu(desc->flags);
			/* अगर ownership flag is set, then we can trust the
			 * HW has written other fields. We must not trust
			 * other descriptor data पढ़ो beक्रमe we checked (पढ़ो)
			 * the ownership flag
			 */
			rmb();
			flags3 = le32_to_cpu(desc->flags3);
			flags2 = le32_to_cpu(desc->flags2);
			tsft = le64_to_cpu(desc->tsft);
		पूर्ण अन्यथा अणु
			काष्ठा rtl8180_rx_desc *desc = entry;

			flags = le32_to_cpu(desc->flags);
			/* same as above */
			rmb();
			flags2 = le32_to_cpu(desc->flags2);
			tsft = le64_to_cpu(desc->tsft);
		पूर्ण

		अगर (flags & RTL818X_RX_DESC_FLAG_OWN)
			वापस;

		अगर (unlikely(flags & (RTL818X_RX_DESC_FLAG_DMA_FAIL |
				      RTL818X_RX_DESC_FLAG_FOF |
				      RTL818X_RX_DESC_FLAG_RX_ERR)))
			जाओ करोne;
		अन्यथा अणु
			काष्ठा ieee80211_rx_status rx_status = अणु0पूर्ण;
			काष्ठा sk_buff *new_skb = dev_alloc_skb(MAX_RX_SIZE);

			अगर (unlikely(!new_skb))
				जाओ करोne;

			mapping = dma_map_single(&priv->pdev->dev,
						 skb_tail_poपूर्णांकer(new_skb),
						 MAX_RX_SIZE, DMA_FROM_DEVICE);

			अगर (dma_mapping_error(&priv->pdev->dev, mapping)) अणु
				kमुक्त_skb(new_skb);
				dev_err(&priv->pdev->dev, "RX DMA map error\n");

				जाओ करोne;
			पूर्ण

			dma_unmap_single(&priv->pdev->dev,
					 *((dma_addr_t *)skb->cb),
					 MAX_RX_SIZE, DMA_FROM_DEVICE);
			skb_put(skb, flags & 0xFFF);

			rx_status.antenna = (flags2 >> 15) & 1;
			rx_status.rate_idx = (flags >> 20) & 0xF;
			agc = (flags2 >> 17) & 0x7F;

			चयन (priv->chip_family) अणु
			हाल RTL818X_CHIP_FAMILY_RTL8185:
				अगर (rx_status.rate_idx > 3)
					संकेत = -clamp_t(u8, agc, 25, 90) - 9;
				अन्यथा
					संकेत = -clamp_t(u8, agc, 30, 95);
				अवरोध;
			हाल RTL818X_CHIP_FAMILY_RTL8180:
				sq = flags2 & 0xff;
				संकेत = priv->rf->calc_rssi(agc, sq);
				अवरोध;
			हाल RTL818X_CHIP_FAMILY_RTL8187SE:
				/* OFDM measure reported by HW is चिन्हित,
				 * in 0.5dBm unit, with zero centered @ -41dBm
				 * input संकेत.
				 */
				अगर (rx_status.rate_idx > 3) अणु
					संकेत = (s8)((flags3 >> 16) & 0xff);
					संकेत = संकेत / 2 - 41;
				पूर्ण अन्यथा अणु
					पूर्णांक idx, bb;

					idx = (agc & 0x60) >> 5;
					bb = (agc & 0x1F) * 2;
					/* bias + BB gain + LNA gain */
					संकेत = 4 - bb - rtl8187se_lna_gain[idx];
				पूर्ण
				अवरोध;
			पूर्ण
			rx_status.संकेत = संकेत;
			rx_status.freq = dev->conf.chandef.chan->center_freq;
			rx_status.band = dev->conf.chandef.chan->band;
			rx_status.maस_समय = tsft;
			rx_status.flag |= RX_FLAG_MACTIME_START;
			अगर (flags & RTL818X_RX_DESC_FLAG_SPLCP)
				rx_status.enc_flags |= RX_ENC_FLAG_SHORTPRE;
			अगर (flags & RTL818X_RX_DESC_FLAG_CRC32_ERR)
				rx_status.flag |= RX_FLAG_FAILED_FCS_CRC;

			स_नकल(IEEE80211_SKB_RXCB(skb), &rx_status, माप(rx_status));
			ieee80211_rx_irqsafe(dev, skb);

			skb = new_skb;
			priv->rx_buf[priv->rx_idx] = skb;
			*((dma_addr_t *) skb->cb) = mapping;
		पूर्ण

	करोne:
		cmd_desc = entry;
		cmd_desc->rx_buf = cpu_to_le32(*((dma_addr_t *)skb->cb));
		cmd_desc->flags = cpu_to_le32(RTL818X_RX_DESC_FLAG_OWN |
					   MAX_RX_SIZE);
		अगर (priv->rx_idx == 31)
			cmd_desc->flags |=
				cpu_to_le32(RTL818X_RX_DESC_FLAG_EOR);
		priv->rx_idx = (priv->rx_idx + 1) % 32;
	पूर्ण
पूर्ण

अटल व्योम rtl8180_handle_tx(काष्ठा ieee80211_hw *dev, अचिन्हित पूर्णांक prio)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	काष्ठा rtl8180_tx_ring *ring = &priv->tx_ring[prio];

	जबतक (skb_queue_len(&ring->queue)) अणु
		काष्ठा rtl8180_tx_desc *entry = &ring->desc[ring->idx];
		काष्ठा sk_buff *skb;
		काष्ठा ieee80211_tx_info *info;
		u32 flags = le32_to_cpu(entry->flags);

		अगर (flags & RTL818X_TX_DESC_FLAG_OWN)
			वापस;

		ring->idx = (ring->idx + 1) % ring->entries;
		skb = __skb_dequeue(&ring->queue);
		dma_unmap_single(&priv->pdev->dev, le32_to_cpu(entry->tx_buf),
				 skb->len, DMA_TO_DEVICE);

		info = IEEE80211_SKB_CB(skb);
		ieee80211_tx_info_clear_status(info);

		अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK) &&
		    (flags & RTL818X_TX_DESC_FLAG_TX_OK))
			info->flags |= IEEE80211_TX_STAT_ACK;

		info->status.rates[0].count = (flags & 0xFF) + 1;

		ieee80211_tx_status_irqsafe(dev, skb);
		अगर (ring->entries - skb_queue_len(&ring->queue) == 2)
			ieee80211_wake_queue(dev, prio);
	पूर्ण
पूर्ण

अटल irqवापस_t rtl8187se_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ieee80211_hw *dev = dev_id;
	काष्ठा rtl8180_priv *priv = dev->priv;
	u32 reg;
	अचिन्हित दीर्घ flags;
	अटल पूर्णांक desc_err;

	spin_lock_irqsave(&priv->lock, flags);
	/* Note: 32-bit पूर्णांकerrupt status */
	reg = rtl818x_ioपढ़ो32(priv, &priv->map->INT_STATUS_SE);
	अगर (unlikely(reg == 0xFFFFFFFF)) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण

	rtl818x_ioग_लिखो32(priv, &priv->map->INT_STATUS_SE, reg);

	अगर (reg & IMR_TIMEOUT1)
		rtl818x_ioग_लिखो32(priv, &priv->map->INT_TIMEOUT, 0);

	अगर (reg & (IMR_TBDOK | IMR_TBDER))
		rtl8180_handle_tx(dev, 4);

	अगर (reg & (IMR_TVODOK | IMR_TVODER))
		rtl8180_handle_tx(dev, 0);

	अगर (reg & (IMR_TVIDOK | IMR_TVIDER))
		rtl8180_handle_tx(dev, 1);

	अगर (reg & (IMR_TBEDOK | IMR_TBEDER))
		rtl8180_handle_tx(dev, 2);

	अगर (reg & (IMR_TBKDOK | IMR_TBKDER))
		rtl8180_handle_tx(dev, 3);

	अगर (reg & (IMR_ROK | IMR_RER | RTL818X_INT_SE_RX_DU | IMR_RQOSOK))
		rtl8180_handle_rx(dev);
	/* The पूर्णांकerface someबार generates several RX DMA descriptor errors
	 * at startup. Do not report these.
	 */
	अगर ((reg & RTL818X_INT_SE_RX_DU) && desc_err++ > 2)
		अगर (net_ratelimit())
			wiphy_err(dev->wiphy, "No RX DMA Descriptor avail\n");

	spin_unlock_irqrestore(&priv->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t rtl8180_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ieee80211_hw *dev = dev_id;
	काष्ठा rtl8180_priv *priv = dev->priv;
	u16 reg;

	spin_lock(&priv->lock);
	reg = rtl818x_ioपढ़ो16(priv, &priv->map->INT_STATUS);
	अगर (unlikely(reg == 0xFFFF)) अणु
		spin_unlock(&priv->lock);
		वापस IRQ_HANDLED;
	पूर्ण

	rtl818x_ioग_लिखो16(priv, &priv->map->INT_STATUS, reg);

	अगर (reg & (RTL818X_INT_TXB_OK | RTL818X_INT_TXB_ERR))
		rtl8180_handle_tx(dev, 1);

	अगर (reg & (RTL818X_INT_TXL_OK | RTL818X_INT_TXL_ERR))
		rtl8180_handle_tx(dev, 0);

	अगर (reg & (RTL818X_INT_RX_OK | RTL818X_INT_RX_ERR))
		rtl8180_handle_rx(dev);

	spin_unlock(&priv->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rtl8180_tx(काष्ठा ieee80211_hw *dev,
		       काष्ठा ieee80211_tx_control *control,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा rtl8180_priv *priv = dev->priv;
	काष्ठा rtl8180_tx_ring *ring;
	काष्ठा rtl8180_tx_desc *entry;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक idx, prio, hw_prio;
	dma_addr_t mapping;
	u32 tx_flags;
	u8 rc_flags;
	u16 plcp_len = 0;
	__le16 rts_duration = 0;
	/* करो arithmetic and then convert to le16 */
	u16 frame_duration = 0;

	prio = skb_get_queue_mapping(skb);
	ring = &priv->tx_ring[prio];

	mapping = dma_map_single(&priv->pdev->dev, skb->data, skb->len,
				 DMA_TO_DEVICE);

	अगर (dma_mapping_error(&priv->pdev->dev, mapping)) अणु
		kमुक्त_skb(skb);
		dev_err(&priv->pdev->dev, "TX DMA mapping error\n");
		वापस;
	पूर्ण

	tx_flags = RTL818X_TX_DESC_FLAG_OWN | RTL818X_TX_DESC_FLAG_FS |
		   RTL818X_TX_DESC_FLAG_LS |
		   (ieee80211_get_tx_rate(dev, info)->hw_value << 24) |
		   skb->len;

	अगर (priv->chip_family != RTL818X_CHIP_FAMILY_RTL8180)
		tx_flags |= RTL818X_TX_DESC_FLAG_DMA |
			    RTL818X_TX_DESC_FLAG_NO_ENC;

	rc_flags = info->control.rates[0].flags;

	/* HW will perक्रमm RTS-CTS when only RTS flags is set.
	 * HW will perक्रमm CTS-to-self when both RTS and CTS flags are set.
	 * RTS rate and RTS duration will be used also क्रम CTS-to-self.
	 */
	अगर (rc_flags & IEEE80211_TX_RC_USE_RTS_CTS) अणु
		tx_flags |= RTL818X_TX_DESC_FLAG_RTS;
		tx_flags |= ieee80211_get_rts_cts_rate(dev, info)->hw_value << 19;
		rts_duration = ieee80211_rts_duration(dev, priv->vअगर,
						skb->len, info);
	पूर्ण अन्यथा अगर (rc_flags & IEEE80211_TX_RC_USE_CTS_PROTECT) अणु
		tx_flags |= RTL818X_TX_DESC_FLAG_RTS | RTL818X_TX_DESC_FLAG_CTS;
		tx_flags |= ieee80211_get_rts_cts_rate(dev, info)->hw_value << 19;
		rts_duration = ieee80211_ctstoself_duration(dev, priv->vअगर,
						skb->len, info);
	पूर्ण

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8180) अणु
		अचिन्हित पूर्णांक reमुख्यder;

		plcp_len = DIV_ROUND_UP(16 * (skb->len + 4),
				(ieee80211_get_tx_rate(dev, info)->bitrate * 2) / 10);
		reमुख्यder = (16 * (skb->len + 4)) %
			    ((ieee80211_get_tx_rate(dev, info)->bitrate * 2) / 10);
		अगर (reमुख्यder <= 6)
			plcp_len |= 1 << 15;
	पूर्ण

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) अणु
		__le16 duration;
		/* SIFS समय (required by HW) is alपढ़ोy included by
		 * ieee80211_generic_frame_duration
		 */
		duration = ieee80211_generic_frame_duration(dev, priv->vअगर,
					NL80211_BAND_2GHZ, skb->len,
					ieee80211_get_tx_rate(dev, info));

		frame_duration =  priv->ack_समय + le16_to_cpu(duration);
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);

	अगर (info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ) अणु
		अगर (info->flags & IEEE80211_TX_CTL_FIRST_FRAGMENT)
			priv->seqno += 0x10;
		hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
		hdr->seq_ctrl |= cpu_to_le16(priv->seqno);
	पूर्ण

	idx = (ring->idx + skb_queue_len(&ring->queue)) % ring->entries;
	entry = &ring->desc[idx];

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) अणु
		entry->frame_duration = cpu_to_le16(frame_duration);
		entry->frame_len_se = cpu_to_le16(skb->len);

		/* tpc polarity */
		entry->flags3 = cpu_to_le16(1<<4);
	पूर्ण अन्यथा
		entry->frame_len = cpu_to_le32(skb->len);

	entry->rts_duration = rts_duration;
	entry->plcp_len = cpu_to_le16(plcp_len);
	entry->tx_buf = cpu_to_le32(mapping);

	entry->retry_limit = info->control.rates[0].count - 1;

	/* We must be sure that tx_flags is written last because the HW
	 * looks at it to check अगर the rest of data is valid or not
	 */
	wmb();
	entry->flags = cpu_to_le32(tx_flags);
	/* We must be sure this has been written beक्रमe followings HW
	 * रेजिस्टर ग_लिखो, because this ग_लिखो will made the HW attempts
	 * to DMA the just-written data
	 */
	wmb();

	__skb_queue_tail(&ring->queue, skb);
	अगर (ring->entries - skb_queue_len(&ring->queue) < 2)
		ieee80211_stop_queue(dev, prio);

	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) अणु
		/* just poll: rings are stopped with TPPollStop reg */
		hw_prio = rtl8187se_queues_map[prio];
		rtl818x_ioग_लिखो8(priv, &priv->map->TX_DMA_POLLING,
			 (1 << hw_prio));
	पूर्ण अन्यथा अणु
		hw_prio = rtl8180_queues_map[prio];
		rtl818x_ioग_लिखो8(priv, &priv->map->TX_DMA_POLLING,
			 (1 << hw_prio) | /* ring to poll  */
			 (1<<1) | (1<<2));/* stopped rings */
	पूर्ण
पूर्ण

अटल व्योम rtl8180_set_anaparam3(काष्ठा rtl8180_priv *priv, u16 anaparam3)
अणु
	u8 reg;

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_CONFIG);

	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG3);
	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG3,
		 reg | RTL818X_CONFIG3_ANAPARAM_WRITE);

	rtl818x_ioग_लिखो16(priv, &priv->map->ANAPARAM3, anaparam3);

	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG3,
		 reg & ~RTL818X_CONFIG3_ANAPARAM_WRITE);

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_NORMAL);
पूर्ण

व्योम rtl8180_set_anaparam2(काष्ठा rtl8180_priv *priv, u32 anaparam2)
अणु
	u8 reg;

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_CONFIG);

	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG3);
	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG3,
		 reg | RTL818X_CONFIG3_ANAPARAM_WRITE);

	rtl818x_ioग_लिखो32(priv, &priv->map->ANAPARAM2, anaparam2);

	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG3,
		 reg & ~RTL818X_CONFIG3_ANAPARAM_WRITE);

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_NORMAL);
पूर्ण

व्योम rtl8180_set_anaparam(काष्ठा rtl8180_priv *priv, u32 anaparam)
अणु
	u8 reg;

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG3);
	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG3,
		 reg | RTL818X_CONFIG3_ANAPARAM_WRITE);
	rtl818x_ioग_लिखो32(priv, &priv->map->ANAPARAM, anaparam);
	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG3,
		 reg & ~RTL818X_CONFIG3_ANAPARAM_WRITE);
	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);
पूर्ण

अटल व्योम rtl8187se_mac_config(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u8 reg;

	rtl818x_ioग_लिखो32(priv, REG_ADDR4(0x1F0), 0);
	rtl818x_ioपढ़ो32(priv, REG_ADDR4(0x1F0));
	rtl818x_ioग_लिखो32(priv, REG_ADDR4(0x1F4), 0);
	rtl818x_ioपढ़ो32(priv, REG_ADDR4(0x1F4));
	rtl818x_ioग_लिखो8(priv, REG_ADDR1(0x1F8), 0);
	rtl818x_ioपढ़ो8(priv, REG_ADDR1(0x1F8));
	/* Enable DA10 TX घातer saving */
	reg = rtl818x_ioपढ़ो8(priv, &priv->map->PHY_PR);
	rtl818x_ioग_लिखो8(priv, &priv->map->PHY_PR, reg | 0x04);
	/* Power */
	rtl818x_ioग_लिखो16(priv, PI_DATA_REG, 0x1000);
	rtl818x_ioग_लिखो16(priv, SI_DATA_REG, 0x1000);
	/* AFE - शेष to घातer ON */
	rtl818x_ioग_लिखो16(priv, REG_ADDR2(0x370), 0x0560);
	rtl818x_ioग_लिखो16(priv, REG_ADDR2(0x372), 0x0560);
	rtl818x_ioग_लिखो16(priv, REG_ADDR2(0x374), 0x0DA4);
	rtl818x_ioग_लिखो16(priv, REG_ADDR2(0x376), 0x0DA4);
	rtl818x_ioग_लिखो16(priv, REG_ADDR2(0x378), 0x0560);
	rtl818x_ioग_लिखो16(priv, REG_ADDR2(0x37A), 0x0560);
	rtl818x_ioग_लिखो16(priv, REG_ADDR2(0x37C), 0x00EC);
	rtl818x_ioग_लिखो16(priv, REG_ADDR2(0x37E), 0x00EC);
	rtl818x_ioग_लिखो8(priv, REG_ADDR1(0x24E), 0x01);
	/* unknown, needed क्रम suspend to RAM resume */
	rtl818x_ioग_लिखो8(priv, REG_ADDR1(0x0A), 0x72);
पूर्ण

अटल व्योम rtl8187se_set_antenna_config(काष्ठा ieee80211_hw *dev, u8 def_ant,
					 bool भागersity)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;

	rtl8225_ग_लिखो_phy_cck(dev, 0x0C, 0x09);
	अगर (भागersity) अणु
		अगर (def_ant == 1) अणु
			rtl818x_ioग_लिखो8(priv, &priv->map->TX_ANTENNA, 0x00);
			rtl8225_ग_लिखो_phy_cck(dev, 0x11, 0xBB);
			rtl8225_ग_लिखो_phy_cck(dev, 0x01, 0xC7);
			rtl8225_ग_लिखो_phy_ofdm(dev, 0x0D, 0x54);
			rtl8225_ग_लिखो_phy_ofdm(dev, 0x18, 0xB2);
		पूर्ण अन्यथा अणु /* मुख्य antenna */
			rtl818x_ioग_लिखो8(priv, &priv->map->TX_ANTENNA, 0x03);
			rtl8225_ग_लिखो_phy_cck(dev, 0x11, 0x9B);
			rtl8225_ग_लिखो_phy_cck(dev, 0x01, 0xC7);
			rtl8225_ग_लिखो_phy_ofdm(dev, 0x0D, 0x5C);
			rtl8225_ग_लिखो_phy_ofdm(dev, 0x18, 0xB2);
		पूर्ण
	पूर्ण अन्यथा अणु /* disable antenna भागersity */
		अगर (def_ant == 1) अणु
			rtl818x_ioग_लिखो8(priv, &priv->map->TX_ANTENNA, 0x00);
			rtl8225_ग_लिखो_phy_cck(dev, 0x11, 0xBB);
			rtl8225_ग_लिखो_phy_cck(dev, 0x01, 0x47);
			rtl8225_ग_लिखो_phy_ofdm(dev, 0x0D, 0x54);
			rtl8225_ग_लिखो_phy_ofdm(dev, 0x18, 0x32);
		पूर्ण अन्यथा अणु /* मुख्य antenna */
			rtl818x_ioग_लिखो8(priv, &priv->map->TX_ANTENNA, 0x03);
			rtl8225_ग_लिखो_phy_cck(dev, 0x11, 0x9B);
			rtl8225_ग_लिखो_phy_cck(dev, 0x01, 0x47);
			rtl8225_ग_लिखो_phy_ofdm(dev, 0x0D, 0x5C);
			rtl8225_ग_लिखो_phy_ofdm(dev, 0x18, 0x32);
		पूर्ण
	पूर्ण
	/* priv->curr_ant = def_ant; */
पूर्ण

अटल व्योम rtl8180_पूर्णांक_enable(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) अणु
		rtl818x_ioग_लिखो32(priv, &priv->map->IMR,
			  IMR_TBDER | IMR_TBDOK |
			  IMR_TVODER | IMR_TVODOK |
			  IMR_TVIDER | IMR_TVIDOK |
			  IMR_TBEDER | IMR_TBEDOK |
			  IMR_TBKDER | IMR_TBKDOK |
			  IMR_RDU | IMR_RER |
			  IMR_ROK | IMR_RQOSOK);
	पूर्ण अन्यथा अणु
		rtl818x_ioग_लिखो16(priv, &priv->map->INT_MASK, 0xFFFF);
	पूर्ण
पूर्ण

अटल व्योम rtl8180_पूर्णांक_disable(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) अणु
		rtl818x_ioग_लिखो32(priv, &priv->map->IMR, 0);
	पूर्ण अन्यथा अणु
		rtl818x_ioग_लिखो16(priv, &priv->map->INT_MASK, 0);
	पूर्ण
पूर्ण

अटल व्योम rtl8180_conf_basic_rates(काष्ठा ieee80211_hw *dev,
			    u32 basic_mask)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u16 reg;
	u32 resp_mask;
	u8 basic_max;
	u8 resp_max, resp_min;

	resp_mask = basic_mask;
	/* IEEE80211 says the response rate should be equal to the highest basic
	 * rate that is not faster than received frame. But it says also that अगर
	 * the basic rate set करोes not contains any rate क्रम the current
	 * modulation class then mandatory rate set must be used क्रम that
	 * modulation class. Eventually add OFDM mandatory rates..
	 */
	अगर ((resp_mask & 0xf) == resp_mask)
		resp_mask |= 0x150; /* 6, 12, 24Mbps */

	चयन (priv->chip_family) अणु

	हाल RTL818X_CHIP_FAMILY_RTL8180:
		/* in 8180 this is NOT a BITMAP */
		basic_max = fls(basic_mask) - 1;
		reg = rtl818x_ioपढ़ो16(priv, &priv->map->BRSR);
		reg &= ~3;
		reg |= basic_max;
		rtl818x_ioग_लिखो16(priv, &priv->map->BRSR, reg);
		अवरोध;

	हाल RTL818X_CHIP_FAMILY_RTL8185:
		resp_max = fls(resp_mask) - 1;
		resp_min = ffs(resp_mask) - 1;
		/* in 8185 this is a BITMAP */
		rtl818x_ioग_लिखो16(priv, &priv->map->BRSR, basic_mask);
		rtl818x_ioग_लिखो8(priv, &priv->map->RESP_RATE, (resp_max << 4) |
				resp_min);
		अवरोध;

	हाल RTL818X_CHIP_FAMILY_RTL8187SE:
		/* in 8187se this is a BITMAP. BRSR reg actually sets
		 * response rates.
		 */
		rtl818x_ioग_लिखो16(priv, &priv->map->BRSR_8187SE, resp_mask);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtl8180_config_cardbus(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u16 reg16;
	u8 reg8;

	reg8 = rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG3);
	reg8 |= 1 << 1;
	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG3, reg8);

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) अणु
		rtl818x_ioग_लिखो16(priv, FEMR_SE, 0xffff);
	पूर्ण अन्यथा अणु
		reg16 = rtl818x_ioपढ़ो16(priv, &priv->map->FEMR);
		reg16 |= (1 << 15) | (1 << 14) | (1 << 4);
		rtl818x_ioग_लिखो16(priv, &priv->map->FEMR, reg16);
	पूर्ण

पूर्ण

अटल पूर्णांक rtl8180_init_hw(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u16 reg;
	u32 reg32;

	rtl818x_ioग_लिखो8(priv, &priv->map->CMD, 0);
	rtl818x_ioपढ़ो8(priv, &priv->map->CMD);
	msleep(10);

	/* reset */
	rtl8180_पूर्णांक_disable(dev);
	rtl818x_ioपढ़ो8(priv, &priv->map->CMD);

	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CMD);
	reg &= (1 << 1);
	reg |= RTL818X_CMD_RESET;
	rtl818x_ioग_लिखो8(priv, &priv->map->CMD, RTL818X_CMD_RESET);
	rtl818x_ioपढ़ो8(priv, &priv->map->CMD);
	msleep(200);

	/* check success of reset */
	अगर (rtl818x_ioपढ़ो8(priv, &priv->map->CMD) & RTL818X_CMD_RESET) अणु
		wiphy_err(dev->wiphy, "reset timeout!\n");
		वापस -ETIMEDOUT;
	पूर्ण

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_LOAD);
	rtl818x_ioपढ़ो8(priv, &priv->map->CMD);
	msleep(200);

	अगर (rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG3) & (1 << 3)) अणु
		rtl8180_config_cardbus(dev);
	पूर्ण

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE)
		rtl818x_ioग_लिखो8(priv, &priv->map->MSR, RTL818X_MSR_ENEDCA);
	अन्यथा
		rtl818x_ioग_लिखो8(priv, &priv->map->MSR, 0);

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8180)
		rtl8180_set_anaparam(priv, priv->anaparam);

	rtl818x_ioग_लिखो32(priv, &priv->map->RDSAR, priv->rx_ring_dma);
	/* mac80211 queue have higher prio क्रम lower index. The last queue
	 * (that mac80211 is not aware of) is reserved क्रम beacons (and have
	 * the highest priority on the NIC)
	 */
	अगर (priv->chip_family != RTL818X_CHIP_FAMILY_RTL8187SE) अणु
		rtl818x_ioग_लिखो32(priv, &priv->map->TBDA,
				  priv->tx_ring[1].dma);
		rtl818x_ioग_लिखो32(priv, &priv->map->TLPDA,
				  priv->tx_ring[0].dma);
	पूर्ण अन्यथा अणु
		rtl818x_ioग_लिखो32(priv, &priv->map->TBDA,
				  priv->tx_ring[4].dma);
		rtl818x_ioग_लिखो32(priv, &priv->map->TVODA,
				  priv->tx_ring[0].dma);
		rtl818x_ioग_लिखो32(priv, &priv->map->TVIDA,
				  priv->tx_ring[1].dma);
		rtl818x_ioग_लिखो32(priv, &priv->map->TBEDA,
				  priv->tx_ring[2].dma);
		rtl818x_ioग_लिखो32(priv, &priv->map->TBKDA,
				  priv->tx_ring[3].dma);
	पूर्ण

	/* TODO: necessary? specs indicate not */
	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG2);
	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG2, reg & ~(1 << 3));
	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8185) अणु
		reg = rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG2);
		rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG2, reg | (1 << 4));
	पूर्ण
	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

	/* TODO: set CONFIG5 क्रम calibrating AGC on rtl8180 + philips radio? */

	/* TODO: turn off hw wep on rtl8180 */

	rtl818x_ioग_लिखो32(priv, &priv->map->INT_TIMEOUT, 0);

	अगर (priv->chip_family != RTL818X_CHIP_FAMILY_RTL8180) अणु
		rtl818x_ioग_लिखो8(priv, &priv->map->WPA_CONF, 0);
		rtl818x_ioग_लिखो8(priv, &priv->map->RATE_FALLBACK, 0);
	पूर्ण अन्यथा अणु
		rtl818x_ioग_लिखो8(priv, &priv->map->SECURITY, 0);

		rtl818x_ioग_लिखो8(priv, &priv->map->PHY_DELAY, 0x6);
		rtl818x_ioग_लिखो8(priv, &priv->map->CARRIER_SENSE_COUNTER, 0x4C);
	पूर्ण

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8185) अणु
		/* TODO: set ClkRun enable? necessary? */
		reg = rtl818x_ioपढ़ो8(priv, &priv->map->GP_ENABLE);
		rtl818x_ioग_लिखो8(priv, &priv->map->GP_ENABLE, reg & ~(1 << 6));
		rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
		reg = rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG3);
		rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG3, reg | (1 << 2));
		rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);
		/* fix eccessive IFS after CTS-to-self */
		अगर (priv->map_pio) अणु
			u8 reg;

			reg = rtl818x_ioपढ़ो8(priv, &priv->map->PGSELECT);
			rtl818x_ioग_लिखो8(priv, &priv->map->PGSELECT, reg | 1);
			rtl818x_ioग_लिखो8(priv, REG_ADDR1(0xff), 0x35);
			rtl818x_ioग_लिखो8(priv, &priv->map->PGSELECT, reg);
		पूर्ण अन्यथा
			rtl818x_ioग_लिखो8(priv, REG_ADDR1(0x1ff), 0x35);
	पूर्ण

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) अणु

		/* the set स्वतः rate fallback biपंचांगask from 1M to 54 Mb/s */
		rtl818x_ioग_लिखो16(priv, ARFR, 0xFFF);
		rtl818x_ioपढ़ो16(priv, ARFR);

		/* stop unused queus (no dma alloc) */
		rtl818x_ioग_लिखो8(priv, &priv->map->TPPOLL_STOP,
			       RTL818x_TPPOLL_STOP_MG | RTL818x_TPPOLL_STOP_HI);

		rtl818x_ioग_लिखो8(priv, &priv->map->ACM_CONTROL, 0x00);
		rtl818x_ioग_लिखो16(priv, &priv->map->TID_AC_MAP, 0xFA50);

		rtl818x_ioग_लिखो16(priv, &priv->map->INT_MIG, 0);

		/* some black magic here.. */
		rtl8187se_mac_config(dev);

		rtl818x_ioग_लिखो16(priv, RFSW_CTRL, 0x569A);
		rtl818x_ioपढ़ो16(priv, RFSW_CTRL);

		rtl8180_set_anaparam(priv, RTL8225SE_ANAPARAM_ON);
		rtl8180_set_anaparam2(priv, RTL8225SE_ANAPARAM2_ON);
		rtl8180_set_anaparam3(priv, RTL8225SE_ANAPARAM3);


		rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG5,
			    rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG5) & 0x7F);

		/*probably this चयन led on */
		rtl818x_ioग_लिखो8(priv, &priv->map->PGSELECT,
			    rtl818x_ioपढ़ो8(priv, &priv->map->PGSELECT) | 0x08);

		rtl818x_ioग_लिखो16(priv, &priv->map->RFPinsOutput, 0x0480);
		rtl818x_ioग_लिखो16(priv, &priv->map->RFPinsEnable, 0x1BFF);
		rtl818x_ioग_लिखो16(priv, &priv->map->RFPinsSelect, 0x2488);

		rtl818x_ioग_लिखो32(priv, &priv->map->RF_TIMING, 0x4003);

		/* the reference code mac hardcode table ग_लिखो
		 * this reg by करोing byte-wide accesses.
		 * It करोes it just क्रम lowest and highest byte..
		 */
		reg32 = rtl818x_ioपढ़ो32(priv, &priv->map->RF_PARA);
		reg32 &= 0x00ffff00;
		reg32 |= 0xb8000054;
		rtl818x_ioग_लिखो32(priv, &priv->map->RF_PARA, reg32);
	पूर्ण अन्यथा
		/* stop unused queus (no dma alloc) */
		rtl818x_ioग_लिखो8(priv, &priv->map->TX_DMA_POLLING,
			    (1<<1) | (1<<2));

	priv->rf->init(dev);

	/* शेष basic rates are 1,2 Mbps क्रम rtl8180. 1,2,6,9,12,18,24 Mbps
	 * otherwise. biपंचांगask 0x3 and 0x01f3 respectively.
	 * NOTE: currenty rtl8225 RF code changes basic rates, so we need to करो
	 * this after rf init.
	 * TODO: try to find out whether RF code really needs to करो this..
	 */
	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8180)
		rtl8180_conf_basic_rates(dev, 0x3);
	अन्यथा
		rtl8180_conf_basic_rates(dev, 0x1f3);

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE)
		rtl8187se_set_antenna_config(dev,
					     priv->antenna_भागersity_शेष,
					     priv->antenna_भागersity_en);
	वापस 0;
पूर्ण

अटल पूर्णांक rtl8180_init_rx_ring(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	काष्ठा rtl818x_rx_cmd_desc *entry;
	पूर्णांक i;

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE)
		priv->rx_ring_sz = माप(काष्ठा rtl8187se_rx_desc);
	अन्यथा
		priv->rx_ring_sz = माप(काष्ठा rtl8180_rx_desc);

	priv->rx_ring = dma_alloc_coherent(&priv->pdev->dev,
					   priv->rx_ring_sz * 32,
					   &priv->rx_ring_dma, GFP_KERNEL);
	अगर (!priv->rx_ring || (अचिन्हित दीर्घ)priv->rx_ring & 0xFF) अणु
		wiphy_err(dev->wiphy, "Cannot allocate RX ring\n");
		वापस -ENOMEM;
	पूर्ण

	priv->rx_idx = 0;

	क्रम (i = 0; i < 32; i++) अणु
		काष्ठा sk_buff *skb = dev_alloc_skb(MAX_RX_SIZE);
		dma_addr_t *mapping;
		entry = priv->rx_ring + priv->rx_ring_sz*i;
		अगर (!skb) अणु
			dma_मुक्त_coherent(&priv->pdev->dev,
					  priv->rx_ring_sz * 32,
					  priv->rx_ring, priv->rx_ring_dma);
			wiphy_err(dev->wiphy, "Cannot allocate RX skb\n");
			वापस -ENOMEM;
		पूर्ण
		priv->rx_buf[i] = skb;
		mapping = (dma_addr_t *)skb->cb;
		*mapping = dma_map_single(&priv->pdev->dev,
					  skb_tail_poपूर्णांकer(skb), MAX_RX_SIZE,
					  DMA_FROM_DEVICE);

		अगर (dma_mapping_error(&priv->pdev->dev, *mapping)) अणु
			kमुक्त_skb(skb);
			dma_मुक्त_coherent(&priv->pdev->dev,
					  priv->rx_ring_sz * 32,
					  priv->rx_ring, priv->rx_ring_dma);
			wiphy_err(dev->wiphy, "Cannot map DMA for RX skb\n");
			वापस -ENOMEM;
		पूर्ण

		entry->rx_buf = cpu_to_le32(*mapping);
		entry->flags = cpu_to_le32(RTL818X_RX_DESC_FLAG_OWN |
					   MAX_RX_SIZE);
	पूर्ण
	entry->flags |= cpu_to_le32(RTL818X_RX_DESC_FLAG_EOR);
	वापस 0;
पूर्ण

अटल व्योम rtl8180_मुक्त_rx_ring(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	पूर्णांक i;

	क्रम (i = 0; i < 32; i++) अणु
		काष्ठा sk_buff *skb = priv->rx_buf[i];
		अगर (!skb)
			जारी;

		dma_unmap_single(&priv->pdev->dev, *((dma_addr_t *)skb->cb),
				 MAX_RX_SIZE, DMA_FROM_DEVICE);
		kमुक्त_skb(skb);
	पूर्ण

	dma_मुक्त_coherent(&priv->pdev->dev, priv->rx_ring_sz * 32,
			  priv->rx_ring, priv->rx_ring_dma);
	priv->rx_ring = शून्य;
पूर्ण

अटल पूर्णांक rtl8180_init_tx_ring(काष्ठा ieee80211_hw *dev,
				अचिन्हित पूर्णांक prio, अचिन्हित पूर्णांक entries)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	काष्ठा rtl8180_tx_desc *ring;
	dma_addr_t dma;
	पूर्णांक i;

	ring = dma_alloc_coherent(&priv->pdev->dev, माप(*ring) * entries,
				  &dma, GFP_KERNEL);
	अगर (!ring || (अचिन्हित दीर्घ)ring & 0xFF) अणु
		wiphy_err(dev->wiphy, "Cannot allocate TX ring (prio = %d)\n",
			  prio);
		वापस -ENOMEM;
	पूर्ण

	priv->tx_ring[prio].desc = ring;
	priv->tx_ring[prio].dma = dma;
	priv->tx_ring[prio].idx = 0;
	priv->tx_ring[prio].entries = entries;
	skb_queue_head_init(&priv->tx_ring[prio].queue);

	क्रम (i = 0; i < entries; i++)
		ring[i].next_tx_desc =
			cpu_to_le32((u32)dma + ((i + 1) % entries) * माप(*ring));

	वापस 0;
पूर्ण

अटल व्योम rtl8180_मुक्त_tx_ring(काष्ठा ieee80211_hw *dev, अचिन्हित पूर्णांक prio)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	काष्ठा rtl8180_tx_ring *ring = &priv->tx_ring[prio];

	जबतक (skb_queue_len(&ring->queue)) अणु
		काष्ठा rtl8180_tx_desc *entry = &ring->desc[ring->idx];
		काष्ठा sk_buff *skb = __skb_dequeue(&ring->queue);

		dma_unmap_single(&priv->pdev->dev, le32_to_cpu(entry->tx_buf),
				 skb->len, DMA_TO_DEVICE);
		kमुक्त_skb(skb);
		ring->idx = (ring->idx + 1) % ring->entries;
	पूर्ण

	dma_मुक्त_coherent(&priv->pdev->dev,
			  माप(*ring->desc) * ring->entries, ring->desc,
			  ring->dma);
	ring->desc = शून्य;
पूर्ण

अटल पूर्णांक rtl8180_start(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	पूर्णांक ret, i;
	u32 reg;

	ret = rtl8180_init_rx_ring(dev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < (dev->queues + 1); i++)
		अगर ((ret = rtl8180_init_tx_ring(dev, i, 16)))
			जाओ err_मुक्त_rings;

	ret = rtl8180_init_hw(dev);
	अगर (ret)
		जाओ err_मुक्त_rings;

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) अणु
		ret = request_irq(priv->pdev->irq, rtl8187se_पूर्णांकerrupt,
			  IRQF_SHARED, KBUILD_MODNAME, dev);
	पूर्ण अन्यथा अणु
		ret = request_irq(priv->pdev->irq, rtl8180_पूर्णांकerrupt,
			  IRQF_SHARED, KBUILD_MODNAME, dev);
	पूर्ण

	अगर (ret) अणु
		wiphy_err(dev->wiphy, "failed to register IRQ handler\n");
		जाओ err_मुक्त_rings;
	पूर्ण

	rtl8180_पूर्णांक_enable(dev);

	/* in rtl8187se at MAR regs offset there is the management
	 * TX descriptor DMA addres..
	 */
	अगर (priv->chip_family != RTL818X_CHIP_FAMILY_RTL8187SE) अणु
		rtl818x_ioग_लिखो32(priv, &priv->map->MAR[0], ~0);
		rtl818x_ioग_लिखो32(priv, &priv->map->MAR[1], ~0);
	पूर्ण

	reg = RTL818X_RX_CONF_ONLYERLPKT |
	      RTL818X_RX_CONF_RX_AUTORESETPHY |
	      RTL818X_RX_CONF_MGMT |
	      RTL818X_RX_CONF_DATA |
	      (7 << 8 /* MAX RX DMA */) |
	      RTL818X_RX_CONF_BROADCAST |
	      RTL818X_RX_CONF_NICMAC;

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8185)
		reg |= RTL818X_RX_CONF_CSDM1 | RTL818X_RX_CONF_CSDM2;
	अन्यथा अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8180) अणु
		reg |= (priv->rfparam & RF_PARAM_CARRIERSENSE1)
			? RTL818X_RX_CONF_CSDM1 : 0;
		reg |= (priv->rfparam & RF_PARAM_CARRIERSENSE2)
			? RTL818X_RX_CONF_CSDM2 : 0;
	पूर्ण अन्यथा अणु
		reg &= ~(RTL818X_RX_CONF_CSDM1 | RTL818X_RX_CONF_CSDM2);
	पूर्ण

	priv->rx_conf = reg;
	rtl818x_ioग_लिखो32(priv, &priv->map->RX_CONF, reg);

	अगर (priv->chip_family != RTL818X_CHIP_FAMILY_RTL8180) अणु
		reg = rtl818x_ioपढ़ो8(priv, &priv->map->CW_CONF);

		/* CW is not on per-packet basis.
		 * in rtl8185 the CW_VALUE reg is used.
		 * in rtl8187se the AC param regs are used.
		 */
		reg &= ~RTL818X_CW_CONF_PERPACKET_CW;
		/* retry limit IS on per-packet basis.
		 * the लघु and दीर्घ retry limit in TX_CONF
		 * reg are ignored
		 */
		reg |= RTL818X_CW_CONF_PERPACKET_RETRY;
		rtl818x_ioग_लिखो8(priv, &priv->map->CW_CONF, reg);

		reg = rtl818x_ioपढ़ो8(priv, &priv->map->TX_AGC_CTL);
		/* TX antenna and TX gain are not on per-packet basis.
		 * TX Antenna is selected by ANTSEL reg (RX in BB regs).
		 * TX gain is selected with CCK_TX_AGC and OFDM_TX_AGC regs
		 */
		reg &= ~RTL818X_TX_AGC_CTL_PERPACKET_GAIN;
		reg &= ~RTL818X_TX_AGC_CTL_PERPACKET_ANTSEL;
		reg |=  RTL818X_TX_AGC_CTL_FEEDBACK_ANT;
		rtl818x_ioग_लिखो8(priv, &priv->map->TX_AGC_CTL, reg);

		/* disable early TX */
		rtl818x_ioग_लिखो8(priv, (u8 __iomem *)priv->map + 0xec, 0x3f);
	पूर्ण

	reg = rtl818x_ioपढ़ो32(priv, &priv->map->TX_CONF);
	reg |= (6 << 21 /* MAX TX DMA */) |
	       RTL818X_TX_CONF_NO_ICV;

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE)
		reg |= 1<<30;  /*  "duration procedure mode" */

	अगर (priv->chip_family != RTL818X_CHIP_FAMILY_RTL8180)
		reg &= ~RTL818X_TX_CONF_PROBE_DTS;
	अन्यथा
		reg &= ~RTL818X_TX_CONF_HW_SEQNUM;

	reg &= ~RTL818X_TX_CONF_DISCW;

	/* dअगरferent meaning, same value on both rtl8185 and rtl8180 */
	reg &= ~RTL818X_TX_CONF_SAT_HWPLCP;

	rtl818x_ioग_लिखो32(priv, &priv->map->TX_CONF, reg);

	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CMD);
	reg |= RTL818X_CMD_RX_ENABLE;
	reg |= RTL818X_CMD_TX_ENABLE;
	rtl818x_ioग_लिखो8(priv, &priv->map->CMD, reg);

	वापस 0;

 err_मुक्त_rings:
	rtl8180_मुक्त_rx_ring(dev);
	क्रम (i = 0; i < (dev->queues + 1); i++)
		अगर (priv->tx_ring[i].desc)
			rtl8180_मुक्त_tx_ring(dev, i);

	वापस ret;
पूर्ण

अटल व्योम rtl8180_stop(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u8 reg;
	पूर्णांक i;

	rtl8180_पूर्णांक_disable(dev);

	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CMD);
	reg &= ~RTL818X_CMD_TX_ENABLE;
	reg &= ~RTL818X_CMD_RX_ENABLE;
	rtl818x_ioग_लिखो8(priv, &priv->map->CMD, reg);

	priv->rf->stop(dev);

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG4);
	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG4, reg | RTL818X_CONFIG4_VCOOFF);
	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

	मुक्त_irq(priv->pdev->irq, dev);

	rtl8180_मुक्त_rx_ring(dev);
	क्रम (i = 0; i < (dev->queues + 1); i++)
		rtl8180_मुक्त_tx_ring(dev, i);
पूर्ण

अटल u64 rtl8180_get_tsf(काष्ठा ieee80211_hw *dev,
			   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;

	वापस rtl818x_ioपढ़ो32(priv, &priv->map->TSFT[0]) |
	       (u64)(rtl818x_ioपढ़ो32(priv, &priv->map->TSFT[1])) << 32;
पूर्ण

अटल व्योम rtl8180_beacon_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl8180_vअगर *vअगर_priv =
		container_of(work, काष्ठा rtl8180_vअगर, beacon_work.work);
	काष्ठा ieee80211_vअगर *vअगर =
		container_of((व्योम *)vअगर_priv, काष्ठा ieee80211_vअगर, drv_priv);
	काष्ठा ieee80211_hw *dev = vअगर_priv->dev;
	काष्ठा ieee80211_mgmt *mgmt;
	काष्ठा sk_buff *skb;

	/* करोn't overflow the tx ring */
	अगर (ieee80211_queue_stopped(dev, 0))
		जाओ resched;

	/* grab a fresh beacon */
	skb = ieee80211_beacon_get(dev, vअगर);
	अगर (!skb)
		जाओ resched;

	/*
	 * update beacon बारtamp w/ TSF value
	 * TODO: make hardware update beacon बारtamp
	 */
	mgmt = (काष्ठा ieee80211_mgmt *)skb->data;
	mgmt->u.beacon.बारtamp = cpu_to_le64(rtl8180_get_tsf(dev, vअगर));

	/* TODO: use actual beacon queue */
	skb_set_queue_mapping(skb, 0);

	rtl8180_tx(dev, शून्य, skb);

resched:
	/*
	 * schedule next beacon
	 * TODO: use hardware support क्रम beacon timing
	 */
	schedule_delayed_work(&vअगर_priv->beacon_work,
			usecs_to_jअगरfies(1024 * vअगर->bss_conf.beacon_पूर्णांक));
पूर्ण

अटल पूर्णांक rtl8180_add_पूर्णांकerface(काष्ठा ieee80211_hw *dev,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	काष्ठा rtl8180_vअगर *vअगर_priv;

	/*
	 * We only support one active पूर्णांकerface at a समय.
	 */
	अगर (priv->vअगर)
		वापस -EBUSY;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	priv->vअगर = vअगर;

	/* Initialize driver निजी area */
	vअगर_priv = (काष्ठा rtl8180_vअगर *)&vअगर->drv_priv;
	vअगर_priv->dev = dev;
	INIT_DELAYED_WORK(&vअगर_priv->beacon_work, rtl8180_beacon_work);
	vअगर_priv->enable_beacon = false;

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	rtl818x_ioग_लिखो32(priv, (__le32 __iomem *)&priv->map->MAC[0],
			  le32_to_cpu(*(__le32 *)vअगर->addr));
	rtl818x_ioग_लिखो16(priv, (__le16 __iomem *)&priv->map->MAC[4],
			  le16_to_cpu(*(__le16 *)(vअगर->addr + 4)));
	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

	वापस 0;
पूर्ण

अटल व्योम rtl8180_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *dev,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	priv->vअगर = शून्य;
पूर्ण

अटल पूर्णांक rtl8180_config(काष्ठा ieee80211_hw *dev, u32 changed)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	काष्ठा ieee80211_conf *conf = &dev->conf;

	priv->rf->set_chan(dev, conf);

	वापस 0;
पूर्ण

अटल व्योम rtl8187se_conf_ac_parm(काष्ठा ieee80211_hw *dev, u8 queue)
अणु
	स्थिर काष्ठा ieee80211_tx_queue_params *params;
	काष्ठा rtl8180_priv *priv = dev->priv;

	/* hw value */
	u32 ac_param;

	u8 aअगरs;
	u8 txop;
	u8 cw_min, cw_max;

	params = &priv->queue_param[queue];

	cw_min = fls(params->cw_min);
	cw_max = fls(params->cw_max);

	aअगरs = 10 + params->aअगरs * priv->slot_समय;

	/* TODO: check अगर txop HW is in us (mult by 32) */
	txop = params->txop;

	ac_param = txop << AC_PARAM_TXOP_LIMIT_SHIFT |
		cw_max << AC_PARAM_ECW_MAX_SHIFT |
		cw_min << AC_PARAM_ECW_MIN_SHIFT |
		aअगरs << AC_PARAM_AIFS_SHIFT;

	चयन (queue) अणु
	हाल IEEE80211_AC_BK:
		rtl818x_ioग_लिखो32(priv, &priv->map->AC_BK_PARAM, ac_param);
		अवरोध;
	हाल IEEE80211_AC_BE:
		rtl818x_ioग_लिखो32(priv, &priv->map->AC_BE_PARAM, ac_param);
		अवरोध;
	हाल IEEE80211_AC_VI:
		rtl818x_ioग_लिखो32(priv, &priv->map->AC_VI_PARAM, ac_param);
		अवरोध;
	हाल IEEE80211_AC_VO:
		rtl818x_ioग_लिखो32(priv, &priv->map->AC_VO_PARAM, ac_param);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rtl8180_conf_tx(काष्ठा ieee80211_hw *dev,
			    काष्ठा ieee80211_vअगर *vअगर, u16 queue,
			    स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u8 cw_min, cw_max;

	/* nothing to करो ? */
	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8180)
		वापस 0;

	cw_min = fls(params->cw_min);
	cw_max = fls(params->cw_max);

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) अणु
		priv->queue_param[queue] = *params;
		rtl8187se_conf_ac_parm(dev, queue);
	पूर्ण अन्यथा
		rtl818x_ioग_लिखो8(priv, &priv->map->CW_VAL,
				 (cw_max << 4) | cw_min);
	वापस 0;
पूर्ण

अटल व्योम rtl8180_conf_erp(काष्ठा ieee80211_hw *dev,
			    काष्ठा ieee80211_bss_conf *info)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u8 sअगरs, dअगरs;
	पूर्णांक eअगरs;
	u8 hw_eअगरs;

	/* TODO: should we करो something ? */
	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8180)
		वापस;

	/* I _hope_ this means 10uS क्रम the HW.
	 * In reference code it is 0x22 क्रम
	 * both rtl8187L and rtl8187SE
	 */
	sअगरs = 0x22;

	अगर (info->use_लघु_slot)
		priv->slot_समय = 9;
	अन्यथा
		priv->slot_समय = 20;

	/* 10 is SIFS समय in uS */
	dअगरs = 10 + 2 * priv->slot_समय;
	eअगरs = 10 + dअगरs + priv->ack_समय;

	/* HW should use 4uS units क्रम EIFS (I'm sure क्रम rtl8185)*/
	hw_eअगरs = DIV_ROUND_UP(eअगरs, 4);


	rtl818x_ioग_लिखो8(priv, &priv->map->SLOT, priv->slot_समय);
	rtl818x_ioग_लिखो8(priv, &priv->map->SIFS, sअगरs);
	rtl818x_ioग_लिखो8(priv, &priv->map->DIFS, dअगरs);

	/* from reference code. set ack समयout reg = eअगरs reg */
	rtl818x_ioग_लिखो8(priv, &priv->map->CARRIER_SENSE_COUNTER, hw_eअगरs);

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE)
		rtl818x_ioग_लिखो8(priv, &priv->map->EIFS_8187SE, hw_eअगरs);
	अन्यथा अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8185) अणु
		/* rtl8187/rtl8185 HW bug. After EIFS is elapsed,
		 * the HW still रुको क्रम DIFS.
		 * HW uses 4uS units क्रम EIFS.
		 */
		hw_eअगरs = DIV_ROUND_UP(eअगरs - dअगरs, 4);

		rtl818x_ioग_लिखो8(priv, &priv->map->EIFS, hw_eअगरs);
	पूर्ण
पूर्ण

अटल व्योम rtl8180_bss_info_changed(काष्ठा ieee80211_hw *dev,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_bss_conf *info,
				     u32 changed)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	काष्ठा rtl8180_vअगर *vअगर_priv;
	पूर्णांक i;
	u8 reg;

	vअगर_priv = (काष्ठा rtl8180_vअगर *)&vअगर->drv_priv;

	अगर (changed & BSS_CHANGED_BSSID) अणु
		rtl818x_ioग_लिखो16(priv, (__le16 __iomem *)&priv->map->BSSID[0],
				  le16_to_cpu(*(__le16 *)info->bssid));
		rtl818x_ioग_लिखो32(priv, (__le32 __iomem *)&priv->map->BSSID[2],
				  le32_to_cpu(*(__le32 *)(info->bssid + 2)));

		अगर (is_valid_ether_addr(info->bssid)) अणु
			अगर (vअगर->type == NL80211_IFTYPE_ADHOC)
				reg = RTL818X_MSR_ADHOC;
			अन्यथा
				reg = RTL818X_MSR_INFRA;
		पूर्ण अन्यथा
			reg = RTL818X_MSR_NO_LINK;

		अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE)
			reg |= RTL818X_MSR_ENEDCA;

		rtl818x_ioग_लिखो8(priv, &priv->map->MSR, reg);
	पूर्ण

	अगर (changed & BSS_CHANGED_BASIC_RATES)
		rtl8180_conf_basic_rates(dev, info->basic_rates);

	अगर (changed & (BSS_CHANGED_ERP_SLOT | BSS_CHANGED_ERP_PREAMBLE)) अणु

		/* when preamble changes, ackसमय duration changes, and erp must
		 * be recalculated. ACK समय is calculated at lowest rate.
		 * Since mac80211 include SIFS समय we हटाओ it (-10)
		 */
		priv->ack_समय =
			le16_to_cpu(ieee80211_generic_frame_duration(dev,
					priv->vअगर,
					NL80211_BAND_2GHZ, 10,
					&priv->rates[0])) - 10;

		rtl8180_conf_erp(dev, info);

		/* mac80211 supplies aअगरs_n to driver and calls
		 * conf_tx callback whether aअगरs_n changes, NOT
		 * when aअगरs changes.
		 * Aअगरs should be recalculated अगर slot changes.
		 */
		अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) अणु
			क्रम (i = 0; i < 4; i++)
				rtl8187se_conf_ac_parm(dev, i);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_ENABLED)
		vअगर_priv->enable_beacon = info->enable_beacon;

	अगर (changed & (BSS_CHANGED_BEACON_ENABLED | BSS_CHANGED_BEACON)) अणु
		cancel_delayed_work_sync(&vअगर_priv->beacon_work);
		अगर (vअगर_priv->enable_beacon)
			schedule_work(&vअगर_priv->beacon_work.work);
	पूर्ण
पूर्ण

अटल u64 rtl8180_prepare_multicast(काष्ठा ieee80211_hw *dev,
				     काष्ठा netdev_hw_addr_list *mc_list)
अणु
	वापस netdev_hw_addr_list_count(mc_list);
पूर्ण

अटल व्योम rtl8180_configure_filter(काष्ठा ieee80211_hw *dev,
				     अचिन्हित पूर्णांक changed_flags,
				     अचिन्हित पूर्णांक *total_flags,
				     u64 multicast)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;

	अगर (changed_flags & FIF_FCSFAIL)
		priv->rx_conf ^= RTL818X_RX_CONF_FCS;
	अगर (changed_flags & FIF_CONTROL)
		priv->rx_conf ^= RTL818X_RX_CONF_CTRL;
	अगर (changed_flags & FIF_OTHER_BSS)
		priv->rx_conf ^= RTL818X_RX_CONF_MONITOR;
	अगर (*total_flags & FIF_ALLMULTI || multicast > 0)
		priv->rx_conf |= RTL818X_RX_CONF_MULTICAST;
	अन्यथा
		priv->rx_conf &= ~RTL818X_RX_CONF_MULTICAST;

	*total_flags = 0;

	अगर (priv->rx_conf & RTL818X_RX_CONF_FCS)
		*total_flags |= FIF_FCSFAIL;
	अगर (priv->rx_conf & RTL818X_RX_CONF_CTRL)
		*total_flags |= FIF_CONTROL;
	अगर (priv->rx_conf & RTL818X_RX_CONF_MONITOR)
		*total_flags |= FIF_OTHER_BSS;
	अगर (priv->rx_conf & RTL818X_RX_CONF_MULTICAST)
		*total_flags |= FIF_ALLMULTI;

	rtl818x_ioग_लिखो32(priv, &priv->map->RX_CONF, priv->rx_conf);
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops rtl8180_ops = अणु
	.tx			= rtl8180_tx,
	.start			= rtl8180_start,
	.stop			= rtl8180_stop,
	.add_पूर्णांकerface		= rtl8180_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= rtl8180_हटाओ_पूर्णांकerface,
	.config			= rtl8180_config,
	.bss_info_changed	= rtl8180_bss_info_changed,
	.conf_tx		= rtl8180_conf_tx,
	.prepare_multicast	= rtl8180_prepare_multicast,
	.configure_filter	= rtl8180_configure_filter,
	.get_tsf		= rtl8180_get_tsf,
पूर्ण;

अटल व्योम rtl8180_eeprom_रेजिस्टर_पढ़ो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा rtl8180_priv *priv = eeprom->data;
	u8 reg = rtl818x_ioपढ़ो8(priv, &priv->map->EEPROM_CMD);

	eeprom->reg_data_in = reg & RTL818X_EEPROM_CMD_WRITE;
	eeprom->reg_data_out = reg & RTL818X_EEPROM_CMD_READ;
	eeprom->reg_data_घड़ी = reg & RTL818X_EEPROM_CMD_CK;
	eeprom->reg_chip_select = reg & RTL818X_EEPROM_CMD_CS;
पूर्ण

अटल व्योम rtl8180_eeprom_रेजिस्टर_ग_लिखो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा rtl8180_priv *priv = eeprom->data;
	u8 reg = 2 << 6;

	अगर (eeprom->reg_data_in)
		reg |= RTL818X_EEPROM_CMD_WRITE;
	अगर (eeprom->reg_data_out)
		reg |= RTL818X_EEPROM_CMD_READ;
	अगर (eeprom->reg_data_घड़ी)
		reg |= RTL818X_EEPROM_CMD_CK;
	अगर (eeprom->reg_chip_select)
		reg |= RTL818X_EEPROM_CMD_CS;

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, reg);
	rtl818x_ioपढ़ो8(priv, &priv->map->EEPROM_CMD);
	udelay(10);
पूर्ण

अटल व्योम rtl8180_eeprom_पढ़ो(काष्ठा rtl8180_priv *priv)
अणु
	काष्ठा eeprom_93cx6 eeprom;
	पूर्णांक eeprom_cck_table_adr;
	u16 eeprom_val;
	पूर्णांक i;

	eeprom.data = priv;
	eeprom.रेजिस्टर_पढ़ो = rtl8180_eeprom_रेजिस्टर_पढ़ो;
	eeprom.रेजिस्टर_ग_लिखो = rtl8180_eeprom_रेजिस्टर_ग_लिखो;
	अगर (rtl818x_ioपढ़ो32(priv, &priv->map->RX_CONF) & (1 << 6))
		eeprom.width = PCI_EEPROM_WIDTH_93C66;
	अन्यथा
		eeprom.width = PCI_EEPROM_WIDTH_93C46;

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD,
			RTL818X_EEPROM_CMD_PROGRAM);
	rtl818x_ioपढ़ो8(priv, &priv->map->EEPROM_CMD);
	udelay(10);

	eeprom_93cx6_पढ़ो(&eeprom, 0x06, &eeprom_val);
	eeprom_val &= 0xFF;
	priv->rf_type = eeprom_val;

	eeprom_93cx6_पढ़ो(&eeprom, 0x17, &eeprom_val);
	priv->csthreshold = eeprom_val >> 8;

	eeprom_93cx6_multiपढ़ो(&eeprom, 0x7, (__le16 *)priv->mac_addr, 3);

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE)
		eeprom_cck_table_adr = 0x30;
	अन्यथा
		eeprom_cck_table_adr = 0x10;

	/* CCK TX घातer */
	क्रम (i = 0; i < 14; i += 2) अणु
		u16 txpwr;
		eeprom_93cx6_पढ़ो(&eeprom, eeprom_cck_table_adr + (i >> 1),
				&txpwr);
		priv->channels[i].hw_value = txpwr & 0xFF;
		priv->channels[i + 1].hw_value = txpwr >> 8;
	पूर्ण

	/* OFDM TX घातer */
	अगर (priv->chip_family != RTL818X_CHIP_FAMILY_RTL8180) अणु
		क्रम (i = 0; i < 14; i += 2) अणु
			u16 txpwr;
			eeprom_93cx6_पढ़ो(&eeprom, 0x20 + (i >> 1), &txpwr);
			priv->channels[i].hw_value |= (txpwr & 0xFF) << 8;
			priv->channels[i + 1].hw_value |= txpwr & 0xFF00;
		पूर्ण
	पूर्ण

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8180) अणु
		__le32 anaparam;
		eeprom_93cx6_multiपढ़ो(&eeprom, 0xD, (__le16 *)&anaparam, 2);
		priv->anaparam = le32_to_cpu(anaparam);
		eeprom_93cx6_पढ़ो(&eeprom, 0x19, &priv->rfparam);
	पूर्ण

	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) अणु
		eeprom_93cx6_पढ़ो(&eeprom, 0x3F, &eeprom_val);
		priv->antenna_भागersity_en = !!(eeprom_val & 0x100);
		priv->antenna_भागersity_शेष = (eeprom_val & 0xC00) == 0x400;

		eeprom_93cx6_पढ़ो(&eeprom, 0x7C, &eeprom_val);
		priv->xtal_out = eeprom_val & 0xF;
		priv->xtal_in = (eeprom_val & 0xF0) >> 4;
		priv->xtal_cal = !!(eeprom_val & 0x1000);
		priv->thermal_meter_val = (eeprom_val & 0xF00) >> 8;
		priv->thermal_meter_en = !!(eeprom_val & 0x2000);
	पूर्ण

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD,
			RTL818X_EEPROM_CMD_NORMAL);
पूर्ण

अटल पूर्णांक rtl8180_probe(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ieee80211_hw *dev;
	काष्ठा rtl8180_priv *priv;
	अचिन्हित दीर्घ mem_len;
	अचिन्हित पूर्णांक io_len;
	पूर्णांक err;
	स्थिर अक्षर *chip_name, *rf_name = शून्य;
	u32 reg;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s (rtl8180): Cannot enable new PCI device\n",
		       pci_name(pdev));
		वापस err;
	पूर्ण

	err = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s (rtl8180): Cannot obtain PCI resources\n",
		       pci_name(pdev));
		जाओ err_disable_dev;
	पूर्ण

	io_len = pci_resource_len(pdev, 0);
	mem_len = pci_resource_len(pdev, 1);

	अगर (mem_len < माप(काष्ठा rtl818x_csr) ||
	    io_len < माप(काष्ठा rtl818x_csr)) अणु
		prपूर्णांकk(KERN_ERR "%s (rtl8180): Too short PCI resources\n",
		       pci_name(pdev));
		err = -ENOMEM;
		जाओ err_मुक्त_reg;
	पूर्ण

	अगर ((err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) ||
	    (err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32)))) अणु
		prपूर्णांकk(KERN_ERR "%s (rtl8180): No suitable DMA available\n",
		       pci_name(pdev));
		जाओ err_मुक्त_reg;
	पूर्ण

	pci_set_master(pdev);

	dev = ieee80211_alloc_hw(माप(*priv), &rtl8180_ops);
	अगर (!dev) अणु
		prपूर्णांकk(KERN_ERR "%s (rtl8180): ieee80211 alloc failed\n",
		       pci_name(pdev));
		err = -ENOMEM;
		जाओ err_मुक्त_reg;
	पूर्ण

	priv = dev->priv;
	priv->pdev = pdev;

	dev->max_rates = 1;
	SET_IEEE80211_DEV(dev, &pdev->dev);
	pci_set_drvdata(pdev, dev);

	priv->map_pio = false;
	priv->map = pci_iomap(pdev, 1, mem_len);
	अगर (!priv->map) अणु
		priv->map = pci_iomap(pdev, 0, io_len);
		priv->map_pio = true;
	पूर्ण

	अगर (!priv->map) अणु
		dev_err(&pdev->dev, "Cannot map device memory/PIO\n");
		err = -ENOMEM;
		जाओ err_मुक्त_dev;
	पूर्ण

	BUILD_BUG_ON(माप(priv->channels) != माप(rtl818x_channels));
	BUILD_BUG_ON(माप(priv->rates) != माप(rtl818x_rates));

	स_नकल(priv->channels, rtl818x_channels, माप(rtl818x_channels));
	स_नकल(priv->rates, rtl818x_rates, माप(rtl818x_rates));

	priv->band.band = NL80211_BAND_2GHZ;
	priv->band.channels = priv->channels;
	priv->band.n_channels = ARRAY_SIZE(rtl818x_channels);
	priv->band.bitrates = priv->rates;
	priv->band.n_bitrates = 4;
	dev->wiphy->bands[NL80211_BAND_2GHZ] = &priv->band;

	ieee80211_hw_set(dev, HOST_BROADCAST_PS_BUFFERING);
	ieee80211_hw_set(dev, RX_INCLUDES_FCS);

	dev->vअगर_data_size = माप(काष्ठा rtl8180_vअगर);
	dev->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
					BIT(NL80211_IFTYPE_ADHOC);
	dev->max_संकेत = 65;

	reg = rtl818x_ioपढ़ो32(priv, &priv->map->TX_CONF);
	reg &= RTL818X_TX_CONF_HWVER_MASK;
	चयन (reg) अणु
	हाल RTL818X_TX_CONF_R8180_ABCD:
		chip_name = "RTL8180";
		priv->chip_family = RTL818X_CHIP_FAMILY_RTL8180;
		अवरोध;

	हाल RTL818X_TX_CONF_R8180_F:
		chip_name = "RTL8180vF";
		priv->chip_family = RTL818X_CHIP_FAMILY_RTL8180;
		अवरोध;

	हाल RTL818X_TX_CONF_R8185_ABC:
		chip_name = "RTL8185";
		priv->chip_family = RTL818X_CHIP_FAMILY_RTL8185;
		अवरोध;

	हाल RTL818X_TX_CONF_R8185_D:
		chip_name = "RTL8185vD";
		priv->chip_family = RTL818X_CHIP_FAMILY_RTL8185;
		अवरोध;

	हाल RTL818X_TX_CONF_RTL8187SE:
		chip_name = "RTL8187SE";
		अगर (priv->map_pio) अणु
			dev_err(&pdev->dev,
				"MMIO failed. PIO not supported on RTL8187SE\n");
			err = -ENOMEM;
			जाओ err_iounmap;
		पूर्ण
		priv->chip_family = RTL818X_CHIP_FAMILY_RTL8187SE;
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "%s (rtl8180): Unknown chip! (0x%x)\n",
		       pci_name(pdev), reg >> 25);
		err = -ENODEV;
		जाओ err_iounmap;
	पूर्ण

	/* we declare to MAC80211 all the queues except क्रम beacon queue
	 * that will be eventually handled by DRV.
	 * TX rings are arranged in such a way that lower is the IDX,
	 * higher is the priority, in order to achieve direct mapping
	 * with mac80211, however the beacon queue is an exception and it
	 * is mapped on the highst tx ring IDX.
	 */
	अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE)
		dev->queues = RTL8187SE_NR_TX_QUEUES - 1;
	अन्यथा
		dev->queues = RTL8180_NR_TX_QUEUES - 1;

	अगर (priv->chip_family != RTL818X_CHIP_FAMILY_RTL8180) अणु
		priv->band.n_bitrates = ARRAY_SIZE(rtl818x_rates);
		pci_try_set_mwi(pdev);
	पूर्ण

	अगर (priv->chip_family != RTL818X_CHIP_FAMILY_RTL8180)
		ieee80211_hw_set(dev, SIGNAL_DBM);
	अन्यथा
		ieee80211_hw_set(dev, SIGNAL_UNSPEC);

	wiphy_ext_feature_set(dev->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	rtl8180_eeprom_पढ़ो(priv);

	चयन (priv->rf_type) अणु
	हाल 1:	rf_name = "Intersil";
		अवरोध;
	हाल 2:	rf_name = "RFMD";
		अवरोध;
	हाल 3:	priv->rf = &sa2400_rf_ops;
		अवरोध;
	हाल 4:	priv->rf = &max2820_rf_ops;
		अवरोध;
	हाल 5:	priv->rf = &grf5101_rf_ops;
		अवरोध;
	हाल 9:
		अगर (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE)
			priv->rf = rtl8187se_detect_rf(dev);
		अन्यथा
			priv->rf = rtl8180_detect_rf(dev);
		अवरोध;
	हाल 10:
		rf_name = "RTL8255";
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s (rtl8180): Unknown RF! (0x%x)\n",
		       pci_name(pdev), priv->rf_type);
		err = -ENODEV;
		जाओ err_iounmap;
	पूर्ण

	अगर (!priv->rf) अणु
		prपूर्णांकk(KERN_ERR "%s (rtl8180): %s RF frontend not supported!\n",
		       pci_name(pdev), rf_name);
		err = -ENODEV;
		जाओ err_iounmap;
	पूर्ण

	अगर (!is_valid_ether_addr(priv->mac_addr)) अणु
		prपूर्णांकk(KERN_WARNING "%s (rtl8180): Invalid hwaddr! Using"
		       " randomly generated MAC addr\n", pci_name(pdev));
		eth_अक्रमom_addr(priv->mac_addr);
	पूर्ण
	SET_IEEE80211_PERM_ADDR(dev, priv->mac_addr);

	spin_lock_init(&priv->lock);

	err = ieee80211_रेजिस्टर_hw(dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s (rtl8180): Cannot register device\n",
		       pci_name(pdev));
		जाओ err_iounmap;
	पूर्ण

	wiphy_info(dev->wiphy, "hwaddr %pm, %s + %s\n",
		   priv->mac_addr, chip_name, priv->rf->name);

	वापस 0;

 err_iounmap:
	pci_iounmap(pdev, priv->map);

 err_मुक्त_dev:
	ieee80211_मुक्त_hw(dev);

 err_मुक्त_reg:
	pci_release_regions(pdev);

 err_disable_dev:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

अटल व्योम rtl8180_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ieee80211_hw *dev = pci_get_drvdata(pdev);
	काष्ठा rtl8180_priv *priv;

	अगर (!dev)
		वापस;

	ieee80211_unरेजिस्टर_hw(dev);

	priv = dev->priv;

	pci_iounmap(pdev, priv->map);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	ieee80211_मुक्त_hw(dev);
पूर्ण

#घोषणा rtl8180_suspend शून्य
#घोषणा rtl8180_resume शून्य

अटल SIMPLE_DEV_PM_OPS(rtl8180_pm_ops, rtl8180_suspend, rtl8180_resume);

अटल काष्ठा pci_driver rtl8180_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= rtl8180_table,
	.probe		= rtl8180_probe,
	.हटाओ		= rtl8180_हटाओ,
	.driver.pm	= &rtl8180_pm_ops,
पूर्ण;

module_pci_driver(rtl8180_driver);
