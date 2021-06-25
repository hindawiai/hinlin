<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Linux device driver क्रम ADMtek ADM8211 (IEEE 802.11b MAC/BBP)
 *
 * Copyright (c) 2003, Jouni Malinen <j@w1.fi>
 * Copyright (c) 2004-2007, Michael Wu <flamingice@sourmilk.net>
 * Some parts copyright (c) 2003 by David Young <dyoung@pobox.com>
 * and used with permission.
 *
 * Much thanks to Infineon-ADMtek क्रम their support of this driver.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अगर.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/crc32.h>
#समावेश <linux/eeprom_93cx6.h>
#समावेश <linux/module.h>
#समावेश <net/mac80211.h>

#समावेश "adm8211.h"

MODULE_AUTHOR("Michael Wu <flamingice@sourmilk.net>");
MODULE_AUTHOR("Jouni Malinen <j@w1.fi>");
MODULE_DESCRIPTION("Driver for IEEE 802.11b wireless cards based on ADMtek ADM8211");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक tx_ring_size __पढ़ो_mostly = 16;
अटल अचिन्हित पूर्णांक rx_ring_size __पढ़ो_mostly = 16;

module_param(tx_ring_size, uपूर्णांक, 0);
module_param(rx_ring_size, uपूर्णांक, 0);

अटल स्थिर काष्ठा pci_device_id adm8211_pci_id_table[] = अणु
	/* ADMtek ADM8211 */
	अणु PCI_DEVICE(0x10B7, 0x6000) पूर्ण, /* 3Com 3CRSHPW796 */
	अणु PCI_DEVICE(0x1200, 0x8201) पूर्ण, /* ? */
	अणु PCI_DEVICE(0x1317, 0x8201) पूर्ण, /* ADM8211A */
	अणु PCI_DEVICE(0x1317, 0x8211) पूर्ण, /* ADM8211B/C */
	अणु 0 पूर्ण
पूर्ण;

अटल काष्ठा ieee80211_rate adm8211_rates[] = अणु
	अणु .bitrate = 10, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 20, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 55, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 110, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 220, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण, /* XX ?? */
पूर्ण;

अटल स्थिर काष्ठा ieee80211_channel adm8211_channels[] = अणु
	अणु .center_freq = 2412पूर्ण,
	अणु .center_freq = 2417पूर्ण,
	अणु .center_freq = 2422पूर्ण,
	अणु .center_freq = 2427पूर्ण,
	अणु .center_freq = 2432पूर्ण,
	अणु .center_freq = 2437पूर्ण,
	अणु .center_freq = 2442पूर्ण,
	अणु .center_freq = 2447पूर्ण,
	अणु .center_freq = 2452पूर्ण,
	अणु .center_freq = 2457पूर्ण,
	अणु .center_freq = 2462पूर्ण,
	अणु .center_freq = 2467पूर्ण,
	अणु .center_freq = 2472पूर्ण,
	अणु .center_freq = 2484पूर्ण,
पूर्ण;


अटल व्योम adm8211_eeprom_रेजिस्टर_पढ़ो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा adm8211_priv *priv = eeprom->data;
	u32 reg = ADM8211_CSR_READ(SPR);

	eeprom->reg_data_in = reg & ADM8211_SPR_SDI;
	eeprom->reg_data_out = reg & ADM8211_SPR_SDO;
	eeprom->reg_data_घड़ी = reg & ADM8211_SPR_SCLK;
	eeprom->reg_chip_select = reg & ADM8211_SPR_SCS;
पूर्ण

अटल व्योम adm8211_eeprom_रेजिस्टर_ग_लिखो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा adm8211_priv *priv = eeprom->data;
	u32 reg = 0x4000 | ADM8211_SPR_SRS;

	अगर (eeprom->reg_data_in)
		reg |= ADM8211_SPR_SDI;
	अगर (eeprom->reg_data_out)
		reg |= ADM8211_SPR_SDO;
	अगर (eeprom->reg_data_घड़ी)
		reg |= ADM8211_SPR_SCLK;
	अगर (eeprom->reg_chip_select)
		reg |= ADM8211_SPR_SCS;

	ADM8211_CSR_WRITE(SPR, reg);
	ADM8211_CSR_READ(SPR);		/* eeprom_delay */
पूर्ण

अटल पूर्णांक adm8211_पढ़ो_eeprom(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	अचिन्हित पूर्णांक words, i;
	काष्ठा ieee80211_chan_range chan_range;
	u16 cr49;
	काष्ठा eeprom_93cx6 eeprom = अणु
		.data		= priv,
		.रेजिस्टर_पढ़ो	= adm8211_eeprom_रेजिस्टर_पढ़ो,
		.रेजिस्टर_ग_लिखो	= adm8211_eeprom_रेजिस्टर_ग_लिखो
	पूर्ण;

	अगर (ADM8211_CSR_READ(CSR_TEST0) & ADM8211_CSR_TEST0_EPTYP) अणु
		/* 256 * 16-bit = 512 bytes */
		eeprom.width = PCI_EEPROM_WIDTH_93C66;
		words = 256;
	पूर्ण अन्यथा अणु
		/* 64 * 16-bit = 128 bytes */
		eeprom.width = PCI_EEPROM_WIDTH_93C46;
		words = 64;
	पूर्ण

	priv->eeprom_len = words * 2;
	priv->eeprom = kदो_स्मृति(priv->eeprom_len, GFP_KERNEL);
	अगर (!priv->eeprom)
		वापस -ENOMEM;

	eeprom_93cx6_multiपढ़ो(&eeprom, 0, (__le16 *)priv->eeprom, words);

	cr49 = le16_to_cpu(priv->eeprom->cr49);
	priv->rf_type = (cr49 >> 3) & 0x7;
	चयन (priv->rf_type) अणु
	हाल ADM8211_TYPE_INTERSIL:
	हाल ADM8211_TYPE_RFMD:
	हाल ADM8211_TYPE_MARVEL:
	हाल ADM8211_TYPE_AIROHA:
	हाल ADM8211_TYPE_ADMTEK:
		अवरोध;

	शेष:
		अगर (priv->pdev->revision < ADM8211_REV_CA)
			priv->rf_type = ADM8211_TYPE_RFMD;
		अन्यथा
			priv->rf_type = ADM8211_TYPE_AIROHA;

		prपूर्णांकk(KERN_WARNING "%s (adm8211): Unknown RFtype %d\n",
		       pci_name(priv->pdev), (cr49 >> 3) & 0x7);
	पूर्ण

	priv->bbp_type = cr49 & 0x7;
	चयन (priv->bbp_type) अणु
	हाल ADM8211_TYPE_INTERSIL:
	हाल ADM8211_TYPE_RFMD:
	हाल ADM8211_TYPE_MARVEL:
	हाल ADM8211_TYPE_AIROHA:
	हाल ADM8211_TYPE_ADMTEK:
		अवरोध;
	शेष:
		अगर (priv->pdev->revision < ADM8211_REV_CA)
			priv->bbp_type = ADM8211_TYPE_RFMD;
		अन्यथा
			priv->bbp_type = ADM8211_TYPE_ADMTEK;

		prपूर्णांकk(KERN_WARNING "%s (adm8211): Unknown BBPtype: %d\n",
		       pci_name(priv->pdev), cr49 >> 3);
	पूर्ण

	अगर (priv->eeprom->country_code >= ARRAY_SIZE(cranges)) अणु
		prपूर्णांकk(KERN_WARNING "%s (adm8211): Invalid country code (%d)\n",
		       pci_name(priv->pdev), priv->eeprom->country_code);

		chan_range = cranges[2];
	पूर्ण अन्यथा
		chan_range = cranges[priv->eeprom->country_code];

	prपूर्णांकk(KERN_DEBUG "%s (adm8211): Channel range: %d - %d\n",
	       pci_name(priv->pdev), (पूर्णांक)chan_range.min, (पूर्णांक)chan_range.max);

	BUILD_BUG_ON(माप(priv->channels) != माप(adm8211_channels));

	स_नकल(priv->channels, adm8211_channels, माप(priv->channels));
	priv->band.channels = priv->channels;
	priv->band.n_channels = ARRAY_SIZE(adm8211_channels);
	priv->band.bitrates = adm8211_rates;
	priv->band.n_bitrates = ARRAY_SIZE(adm8211_rates);

	क्रम (i = 1; i <= ARRAY_SIZE(adm8211_channels); i++)
		अगर (i < chan_range.min || i > chan_range.max)
			priv->channels[i - 1].flags |= IEEE80211_CHAN_DISABLED;

	चयन (priv->eeprom->specअगरic_bbptype) अणु
	हाल ADM8211_BBP_RFMD3000:
	हाल ADM8211_BBP_RFMD3002:
	हाल ADM8211_BBP_ADM8011:
		priv->specअगरic_bbptype = priv->eeprom->specअगरic_bbptype;
		अवरोध;

	शेष:
		अगर (priv->pdev->revision < ADM8211_REV_CA)
			priv->specअगरic_bbptype = ADM8211_BBP_RFMD3000;
		अन्यथा
			priv->specअगरic_bbptype = ADM8211_BBP_ADM8011;

		prपूर्णांकk(KERN_WARNING "%s (adm8211): Unknown specific BBP: %d\n",
		       pci_name(priv->pdev), priv->eeprom->specअगरic_bbptype);
	पूर्ण

	चयन (priv->eeprom->specअगरic_rftype) अणु
	हाल ADM8211_RFMD2948:
	हाल ADM8211_RFMD2958:
	हाल ADM8211_RFMD2958_RF3000_CONTROL_POWER:
	हाल ADM8211_MAX2820:
	हाल ADM8211_AL2210L:
		priv->transceiver_type = priv->eeprom->specअगरic_rftype;
		अवरोध;

	शेष:
		अगर (priv->pdev->revision == ADM8211_REV_BA)
			priv->transceiver_type = ADM8211_RFMD2958_RF3000_CONTROL_POWER;
		अन्यथा अगर (priv->pdev->revision == ADM8211_REV_CA)
			priv->transceiver_type = ADM8211_AL2210L;
		अन्यथा अगर (priv->pdev->revision == ADM8211_REV_AB)
			priv->transceiver_type = ADM8211_RFMD2948;

		prपूर्णांकk(KERN_WARNING "%s (adm8211): Unknown transceiver: %d\n",
		       pci_name(priv->pdev), priv->eeprom->specअगरic_rftype);

		अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "%s (adm8211): RFtype=%d BBPtype=%d Specific BBP=%d "
               "Transceiver=%d\n", pci_name(priv->pdev), priv->rf_type,
	       priv->bbp_type, priv->specअगरic_bbptype, priv->transceiver_type);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम adm8211_ग_लिखो_sram(काष्ठा ieee80211_hw *dev,
				      u32 addr, u32 data)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;

	ADM8211_CSR_WRITE(WEPCTL, addr | ADM8211_WEPCTL_TABLE_WR |
			  (priv->pdev->revision < ADM8211_REV_BA ?
			   0 : ADM8211_WEPCTL_SEL_WEPTABLE ));
	ADM8211_CSR_READ(WEPCTL);
	msleep(1);

	ADM8211_CSR_WRITE(WESK, data);
	ADM8211_CSR_READ(WESK);
	msleep(1);
पूर्ण

अटल व्योम adm8211_ग_लिखो_sram_bytes(काष्ठा ieee80211_hw *dev,
				     अचिन्हित पूर्णांक addr, u8 *buf,
				     अचिन्हित पूर्णांक len)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	u32 reg = ADM8211_CSR_READ(WEPCTL);
	अचिन्हित पूर्णांक i;

	अगर (priv->pdev->revision < ADM8211_REV_BA) अणु
		क्रम (i = 0; i < len; i += 2) अणु
			u16 val = buf[i] | (buf[i + 1] << 8);
			adm8211_ग_लिखो_sram(dev, addr + i / 2, val);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < len; i += 4) अणु
			u32 val = (buf[i + 0] << 0 ) | (buf[i + 1] << 8 ) |
				  (buf[i + 2] << 16) | (buf[i + 3] << 24);
			adm8211_ग_लिखो_sram(dev, addr + i / 4, val);
		पूर्ण
	पूर्ण

	ADM8211_CSR_WRITE(WEPCTL, reg);
पूर्ण

अटल व्योम adm8211_clear_sram(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	u32 reg = ADM8211_CSR_READ(WEPCTL);
	अचिन्हित पूर्णांक addr;

	क्रम (addr = 0; addr < ADM8211_SRAM_SIZE; addr++)
		adm8211_ग_लिखो_sram(dev, addr, 0);

	ADM8211_CSR_WRITE(WEPCTL, reg);
पूर्ण

अटल पूर्णांक adm8211_get_stats(काष्ठा ieee80211_hw *dev,
			     काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;

	स_नकल(stats, &priv->stats, माप(*stats));

	वापस 0;
पूर्ण

अटल व्योम adm8211_पूर्णांकerrupt_tci(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	अचिन्हित पूर्णांक dirty_tx;

	spin_lock(&priv->lock);

	क्रम (dirty_tx = priv->dirty_tx; priv->cur_tx - dirty_tx; dirty_tx++) अणु
		अचिन्हित पूर्णांक entry = dirty_tx % priv->tx_ring_size;
		u32 status = le32_to_cpu(priv->tx_ring[entry].status);
		काष्ठा ieee80211_tx_info *txi;
		काष्ठा adm8211_tx_ring_info *info;
		काष्ठा sk_buff *skb;

		अगर (status & TDES0_CONTROL_OWN ||
		    !(status & TDES0_CONTROL_DONE))
			अवरोध;

		info = &priv->tx_buffers[entry];
		skb = info->skb;
		txi = IEEE80211_SKB_CB(skb);

		/* TODO: check TDES0_STATUS_TUF and TDES0_STATUS_TRO */

		dma_unmap_single(&priv->pdev->dev, info->mapping,
				 info->skb->len, DMA_TO_DEVICE);

		ieee80211_tx_info_clear_status(txi);

		skb_pull(skb, माप(काष्ठा adm8211_tx_hdr));
		स_नकल(skb_push(skb, info->hdrlen), skb->cb, info->hdrlen);
		अगर (!(txi->flags & IEEE80211_TX_CTL_NO_ACK) &&
		    !(status & TDES0_STATUS_ES))
			txi->flags |= IEEE80211_TX_STAT_ACK;

		ieee80211_tx_status_irqsafe(dev, skb);

		info->skb = शून्य;
	पूर्ण

	अगर (priv->cur_tx - dirty_tx < priv->tx_ring_size - 2)
		ieee80211_wake_queue(dev, 0);

	priv->dirty_tx = dirty_tx;
	spin_unlock(&priv->lock);
पूर्ण


अटल व्योम adm8211_पूर्णांकerrupt_rci(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	अचिन्हित पूर्णांक entry = priv->cur_rx % priv->rx_ring_size;
	u32 status;
	अचिन्हित पूर्णांक pktlen;
	काष्ठा sk_buff *skb, *newskb;
	अचिन्हित पूर्णांक limit = priv->rx_ring_size;
	u8 rssi, rate;

	जबतक (!(priv->rx_ring[entry].status & cpu_to_le32(RDES0_STATUS_OWN))) अणु
		अगर (!limit--)
			अवरोध;

		status = le32_to_cpu(priv->rx_ring[entry].status);
		rate = (status & RDES0_STATUS_RXDR) >> 12;
		rssi = le32_to_cpu(priv->rx_ring[entry].length) &
			RDES1_STATUS_RSSI;

		pktlen = status & RDES0_STATUS_FL;
		अगर (pktlen > RX_PKT_SIZE) अणु
			अगर (net_ratelimit())
				wiphy_debug(dev->wiphy, "frame too long (%d)\n",
					    pktlen);
			pktlen = RX_PKT_SIZE;
		पूर्ण

		अगर (!priv->soft_rx_crc && status & RDES0_STATUS_ES) अणु
			skb = शून्य; /* old buffer will be reused */
			/* TODO: update RX error stats */
			/* TODO: check RDES0_STATUS_CRC*E */
		पूर्ण अन्यथा अगर (pktlen < RX_COPY_BREAK) अणु
			skb = dev_alloc_skb(pktlen);
			अगर (skb) अणु
				dma_sync_single_क्रम_cpu(&priv->pdev->dev,
							priv->rx_buffers[entry].mapping,
							pktlen,
							DMA_FROM_DEVICE);
				skb_put_data(skb,
					     skb_tail_poपूर्णांकer(priv->rx_buffers[entry].skb),
					     pktlen);
				dma_sync_single_क्रम_device(&priv->pdev->dev,
							   priv->rx_buffers[entry].mapping,
							   RX_PKT_SIZE,
							   DMA_FROM_DEVICE);
			पूर्ण
		पूर्ण अन्यथा अणु
			newskb = dev_alloc_skb(RX_PKT_SIZE);
			अगर (newskb) अणु
				skb = priv->rx_buffers[entry].skb;
				skb_put(skb, pktlen);
				dma_unmap_single(&priv->pdev->dev,
						 priv->rx_buffers[entry].mapping,
						 RX_PKT_SIZE, DMA_FROM_DEVICE);
				priv->rx_buffers[entry].skb = newskb;
				priv->rx_buffers[entry].mapping =
					dma_map_single(&priv->pdev->dev,
						       skb_tail_poपूर्णांकer(newskb),
						       RX_PKT_SIZE,
						       DMA_FROM_DEVICE);
				अगर (dma_mapping_error(&priv->pdev->dev,
						      priv->rx_buffers[entry].mapping)) अणु
					priv->rx_buffers[entry].skb = शून्य;
					dev_kमुक्त_skb(newskb);
					skb = शून्य;
					/* TODO: update rx dropped stats */
				पूर्ण
			पूर्ण अन्यथा अणु
				skb = शून्य;
				/* TODO: update rx dropped stats */
			पूर्ण

			priv->rx_ring[entry].buffer1 =
				cpu_to_le32(priv->rx_buffers[entry].mapping);
		पूर्ण

		priv->rx_ring[entry].status = cpu_to_le32(RDES0_STATUS_OWN |
							  RDES0_STATUS_SQL);
		priv->rx_ring[entry].length =
			cpu_to_le32(RX_PKT_SIZE |
				    (entry == priv->rx_ring_size - 1 ?
				     RDES1_CONTROL_RER : 0));

		अगर (skb) अणु
			काष्ठा ieee80211_rx_status rx_status = अणु0पूर्ण;

			अगर (priv->pdev->revision < ADM8211_REV_CA)
				rx_status.संकेत = rssi;
			अन्यथा
				rx_status.संकेत = 100 - rssi;

			rx_status.rate_idx = rate;

			rx_status.freq = adm8211_channels[priv->channel - 1].center_freq;
			rx_status.band = NL80211_BAND_2GHZ;

			स_नकल(IEEE80211_SKB_RXCB(skb), &rx_status, माप(rx_status));
			ieee80211_rx_irqsafe(dev, skb);
		पूर्ण

		entry = (++priv->cur_rx) % priv->rx_ring_size;
	पूर्ण

	/* TODO: check LPC and update stats? */
पूर्ण


अटल irqवापस_t adm8211_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
#घोषणा ADM8211_INT(x)						\
करो अणु								\
	अगर (unlikely(stsr & ADM8211_STSR_ ## x))		\
		wiphy_debug(dev->wiphy, "%s\n", #x);		\
पूर्ण जबतक (0)

	काष्ठा ieee80211_hw *dev = dev_id;
	काष्ठा adm8211_priv *priv = dev->priv;
	u32 stsr = ADM8211_CSR_READ(STSR);
	ADM8211_CSR_WRITE(STSR, stsr);
	अगर (stsr == 0xffffffff)
		वापस IRQ_HANDLED;

	अगर (!(stsr & (ADM8211_STSR_NISS | ADM8211_STSR_AISS)))
		वापस IRQ_HANDLED;

	अगर (stsr & ADM8211_STSR_RCI)
		adm8211_पूर्णांकerrupt_rci(dev);
	अगर (stsr & ADM8211_STSR_TCI)
		adm8211_पूर्णांकerrupt_tci(dev);

	ADM8211_INT(PCF);
	ADM8211_INT(BCNTC);
	ADM8211_INT(GPINT);
	ADM8211_INT(ATIMTC);
	ADM8211_INT(TSFTF);
	ADM8211_INT(TSCZ);
	ADM8211_INT(SQL);
	ADM8211_INT(WEPTD);
	ADM8211_INT(ATIME);
	ADM8211_INT(TEIS);
	ADM8211_INT(FBE);
	ADM8211_INT(REIS);
	ADM8211_INT(GPTT);
	ADM8211_INT(RPS);
	ADM8211_INT(RDU);
	ADM8211_INT(TUF);
	ADM8211_INT(TPS);

	वापस IRQ_HANDLED;

#अघोषित ADM8211_INT
पूर्ण

#घोषणा WRITE_SYN(name,v_mask,v_shअगरt,a_mask,a_shअगरt,bits,preग_लिखो,postग_लिखो)\
अटल व्योम adm8211_rf_ग_लिखो_syn_ ## name (काष्ठा ieee80211_hw *dev,	     \
					   u16 addr, u32 value) अणु	     \
	काष्ठा adm8211_priv *priv = dev->priv;				     \
	अचिन्हित पूर्णांक i;							     \
	u32 reg, bitbuf;						     \
									     \
	value &= v_mask;						     \
	addr &= a_mask;							     \
	bitbuf = (value << v_shअगरt) | (addr << a_shअगरt);		     \
									     \
	ADM8211_CSR_WRITE(SYNRF, ADM8211_SYNRF_IF_SELECT_1);		     \
	ADM8211_CSR_READ(SYNRF);					     \
	ADM8211_CSR_WRITE(SYNRF, ADM8211_SYNRF_IF_SELECT_0);		     \
	ADM8211_CSR_READ(SYNRF);					     \
									     \
	अगर (preग_लिखो) अणु							     \
		ADM8211_CSR_WRITE(SYNRF, ADM8211_SYNRF_WRITE_SYNDATA_0);     \
		ADM8211_CSR_READ(SYNRF);				     \
	पूर्ण								     \
									     \
	क्रम (i = 0; i <= bits; i++) अणु					     \
		अगर (bitbuf & (1 << (bits - i)))				     \
			reg = ADM8211_SYNRF_WRITE_SYNDATA_1;		     \
		अन्यथा							     \
			reg = ADM8211_SYNRF_WRITE_SYNDATA_0;		     \
									     \
		ADM8211_CSR_WRITE(SYNRF, reg);				     \
		ADM8211_CSR_READ(SYNRF);				     \
									     \
		ADM8211_CSR_WRITE(SYNRF, reg | ADM8211_SYNRF_WRITE_CLOCK_1); \
		ADM8211_CSR_READ(SYNRF);				     \
		ADM8211_CSR_WRITE(SYNRF, reg | ADM8211_SYNRF_WRITE_CLOCK_0); \
		ADM8211_CSR_READ(SYNRF);				     \
	पूर्ण								     \
									     \
	अगर (postग_लिखो == 1) अणु						     \
		ADM8211_CSR_WRITE(SYNRF, reg | ADM8211_SYNRF_IF_SELECT_0);   \
		ADM8211_CSR_READ(SYNRF);				     \
	पूर्ण								     \
	अगर (postग_लिखो == 2) अणु						     \
		ADM8211_CSR_WRITE(SYNRF, reg | ADM8211_SYNRF_IF_SELECT_1);   \
		ADM8211_CSR_READ(SYNRF);				     \
	पूर्ण								     \
									     \
	ADM8211_CSR_WRITE(SYNRF, 0);					     \
	ADM8211_CSR_READ(SYNRF);					     \
पूर्ण

WRITE_SYN(max2820,  0x00FFF, 0, 0x0F, 12, 15, 1, 1)
WRITE_SYN(al2210l,  0xFFFFF, 4, 0x0F,  0, 23, 1, 1)
WRITE_SYN(rfmd2958, 0x3FFFF, 0, 0x1F, 18, 23, 0, 1)
WRITE_SYN(rfmd2948, 0x0FFFF, 4, 0x0F,  0, 21, 0, 2)

#अघोषित WRITE_SYN

अटल पूर्णांक adm8211_ग_लिखो_bbp(काष्ठा ieee80211_hw *dev, u8 addr, u8 data)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	अचिन्हित पूर्णांक समयout;
	u32 reg;

	समयout = 10;
	जबतक (समयout > 0) अणु
		reg = ADM8211_CSR_READ(BBPCTL);
		अगर (!(reg & (ADM8211_BBPCTL_WR | ADM8211_BBPCTL_RD)))
			अवरोध;
		समयout--;
		msleep(2);
	पूर्ण

	अगर (समयout == 0) अणु
		wiphy_debug(dev->wiphy,
			    "adm8211_write_bbp(%d,%d) failed prewrite (reg=0x%08x)\n",
			    addr, data, reg);
		वापस -ETIMEDOUT;
	पूर्ण

	चयन (priv->bbp_type) अणु
	हाल ADM8211_TYPE_INTERSIL:
		reg = ADM8211_BBPCTL_MMISEL;	/* three wire पूर्णांकerface */
		अवरोध;
	हाल ADM8211_TYPE_RFMD:
		reg = (0x20 << 24) | ADM8211_BBPCTL_TXCE | ADM8211_BBPCTL_CCAP |
		      (0x01 << 18);
		अवरोध;
	हाल ADM8211_TYPE_ADMTEK:
		reg = (0x20 << 24) | ADM8211_BBPCTL_TXCE | ADM8211_BBPCTL_CCAP |
		      (0x05 << 18);
		अवरोध;
	पूर्ण
	reg |= ADM8211_BBPCTL_WR | (addr << 8) | data;

	ADM8211_CSR_WRITE(BBPCTL, reg);

	समयout = 10;
	जबतक (समयout > 0) अणु
		reg = ADM8211_CSR_READ(BBPCTL);
		अगर (!(reg & ADM8211_BBPCTL_WR))
			अवरोध;
		समयout--;
		msleep(2);
	पूर्ण

	अगर (समयout == 0) अणु
		ADM8211_CSR_WRITE(BBPCTL, ADM8211_CSR_READ(BBPCTL) &
				  ~ADM8211_BBPCTL_WR);
		wiphy_debug(dev->wiphy,
			    "adm8211_write_bbp(%d,%d) failed postwrite (reg=0x%08x)\n",
			    addr, data, reg);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adm8211_rf_set_channel(काष्ठा ieee80211_hw *dev, अचिन्हित पूर्णांक chan)
अणु
	अटल स्थिर u32 adm8211_rfmd2958_reg5[] =
		अणु0x22BD, 0x22D2, 0x22E8, 0x22FE, 0x2314, 0x232A, 0x2340,
		 0x2355, 0x236B, 0x2381, 0x2397, 0x23AD, 0x23C2, 0x23F7पूर्ण;
	अटल स्थिर u32 adm8211_rfmd2958_reg6[] =
		अणु0x05D17, 0x3A2E8, 0x2E8BA, 0x22E8B, 0x1745D, 0x0BA2E, 0x00000,
		 0x345D1, 0x28BA2, 0x1D174, 0x11745, 0x05D17, 0x3A2E8, 0x11745पूर्ण;

	काष्ठा adm8211_priv *priv = dev->priv;
	u8 ant_घातer = priv->ant_घातer > 0x3F ?
		priv->eeprom->antenna_घातer[chan - 1] : priv->ant_घातer;
	u8 tx_घातer = priv->tx_घातer > 0x3F ?
		priv->eeprom->tx_घातer[chan - 1] : priv->tx_घातer;
	u8 lpf_cutoff = priv->lpf_cutoff == 0xFF ?
		priv->eeprom->lpf_cutoff[chan - 1] : priv->lpf_cutoff;
	u8 lnags_thresh = priv->lnags_threshold == 0xFF ?
		priv->eeprom->lnags_threshold[chan - 1] : priv->lnags_threshold;
	u32 reg;

	ADM8211_IDLE();

	/* Program synthesizer to new channel */
	चयन (priv->transceiver_type) अणु
	हाल ADM8211_RFMD2958:
	हाल ADM8211_RFMD2958_RF3000_CONTROL_POWER:
		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x00, 0x04007);
		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x02, 0x00033);

		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x05,
			adm8211_rfmd2958_reg5[chan - 1]);
		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x06,
			adm8211_rfmd2958_reg6[chan - 1]);
		अवरोध;

	हाल ADM8211_RFMD2948:
		adm8211_rf_ग_लिखो_syn_rfmd2948(dev, SI4126_MAIN_CONF,
					      SI4126_MAIN_XINDIV2);
		adm8211_rf_ग_लिखो_syn_rfmd2948(dev, SI4126_POWERDOWN,
					      SI4126_POWERDOWN_PDIB |
					      SI4126_POWERDOWN_PDRB);
		adm8211_rf_ग_लिखो_syn_rfmd2948(dev, SI4126_PHASE_DET_GAIN, 0);
		adm8211_rf_ग_लिखो_syn_rfmd2948(dev, SI4126_RF2_N_DIV,
					      (chan == 14 ?
					       2110 : (2033 + (chan * 5))));
		adm8211_rf_ग_लिखो_syn_rfmd2948(dev, SI4126_IF_N_DIV, 1496);
		adm8211_rf_ग_लिखो_syn_rfmd2948(dev, SI4126_RF2_R_DIV, 44);
		adm8211_rf_ग_लिखो_syn_rfmd2948(dev, SI4126_IF_R_DIV, 44);
		अवरोध;

	हाल ADM8211_MAX2820:
		adm8211_rf_ग_लिखो_syn_max2820(dev, 0x3,
			(chan == 14 ? 0x054 : (0x7 + (chan * 5))));
		अवरोध;

	हाल ADM8211_AL2210L:
		adm8211_rf_ग_लिखो_syn_al2210l(dev, 0x0,
			(chan == 14 ? 0x229B4 : (0x22967 + (chan * 5))));
		अवरोध;

	शेष:
		wiphy_debug(dev->wiphy, "unsupported transceiver type %d\n",
			    priv->transceiver_type);
		अवरोध;
	पूर्ण

	/* ग_लिखो BBP regs */
	अगर (priv->bbp_type == ADM8211_TYPE_RFMD) अणु

	/* SMC 2635W specअगरic? adm8211b करोesn't use the 2948 though.. */
	/* TODO: हटाओ अगर SMC 2635W करोesn't need this */
	अगर (priv->transceiver_type == ADM8211_RFMD2948) अणु
		reg = ADM8211_CSR_READ(GPIO);
		reg &= 0xfffc0000;
		reg |= ADM8211_CSR_GPIO_EN0;
		अगर (chan != 14)
			reg |= ADM8211_CSR_GPIO_O0;
		ADM8211_CSR_WRITE(GPIO, reg);
	पूर्ण

	अगर (priv->transceiver_type == ADM8211_RFMD2958) अणु
		/* set PCNT2 */
		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x0B, 0x07100);
		/* set PCNT1 P_DESIRED/MID_BIAS */
		reg = le16_to_cpu(priv->eeprom->cr49);
		reg >>= 13;
		reg <<= 15;
		reg |= ant_घातer << 9;
		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x0A, reg);
		/* set TXRX TX_GAIN */
		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x09, 0x00050 |
			(priv->pdev->revision < ADM8211_REV_CA ? tx_घातer : 0));
	पूर्ण अन्यथा अणु
		reg = ADM8211_CSR_READ(PLCPHD);
		reg &= 0xff00ffff;
		reg |= tx_घातer << 18;
		ADM8211_CSR_WRITE(PLCPHD, reg);
	पूर्ण

	ADM8211_CSR_WRITE(SYNRF, ADM8211_SYNRF_SELRF |
			  ADM8211_SYNRF_PE1 | ADM8211_SYNRF_PHYRST);
	ADM8211_CSR_READ(SYNRF);
	msleep(30);

	/* RF3000 BBP */
	अगर (priv->transceiver_type != ADM8211_RFMD2958)
		adm8211_ग_लिखो_bbp(dev, RF3000_TX_VAR_GAIN__TX_LEN_EXT,
				  tx_घातer<<2);
	adm8211_ग_लिखो_bbp(dev, RF3000_LOW_GAIN_CALIB, lpf_cutoff);
	adm8211_ग_लिखो_bbp(dev, RF3000_HIGH_GAIN_CALIB, lnags_thresh);
	adm8211_ग_लिखो_bbp(dev, 0x1c, priv->pdev->revision == ADM8211_REV_BA ?
				     priv->eeprom->cr28 : 0);
	adm8211_ग_लिखो_bbp(dev, 0x1d, priv->eeprom->cr29);

	ADM8211_CSR_WRITE(SYNRF, 0);

	/* Nothing to करो क्रम ADMtek BBP */
	पूर्ण अन्यथा अगर (priv->bbp_type != ADM8211_TYPE_ADMTEK)
		wiphy_debug(dev->wiphy, "unsupported BBP type %d\n",
			    priv->bbp_type);

	ADM8211_RESTORE();

	/* update current channel क्रम adhoc (and maybe AP mode) */
	reg = ADM8211_CSR_READ(CAP0);
	reg &= ~0xF;
	reg |= chan;
	ADM8211_CSR_WRITE(CAP0, reg);

	वापस 0;
पूर्ण

अटल व्योम adm8211_update_mode(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;

	ADM8211_IDLE();

	priv->soft_rx_crc = 0;
	चयन (priv->mode) अणु
	हाल NL80211_IFTYPE_STATION:
		priv->nar &= ~(ADM8211_NAR_PR | ADM8211_NAR_EA);
		priv->nar |= ADM8211_NAR_ST | ADM8211_NAR_SR;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		priv->nar &= ~ADM8211_NAR_PR;
		priv->nar |= ADM8211_NAR_EA | ADM8211_NAR_ST | ADM8211_NAR_SR;

		/* करोn't trust the error bits on rev 0x20 and up in adhoc */
		अगर (priv->pdev->revision >= ADM8211_REV_BA)
			priv->soft_rx_crc = 1;
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		priv->nar &= ~(ADM8211_NAR_EA | ADM8211_NAR_ST);
		priv->nar |= ADM8211_NAR_PR | ADM8211_NAR_SR;
		अवरोध;
	पूर्ण

	ADM8211_RESTORE();
पूर्ण

अटल व्योम adm8211_hw_init_syn(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;

	चयन (priv->transceiver_type) अणु
	हाल ADM8211_RFMD2958:
	हाल ADM8211_RFMD2958_RF3000_CONTROL_POWER:
		/* comments taken from ADMtek venकरोr driver */

		/* Reset RF2958 after घातer on */
		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x1F, 0x00000);
		/* Initialize RF VCO Core Bias to maximum */
		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x0C, 0x3001F);
		/* Initialize IF PLL */
		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x01, 0x29C03);
		/* Initialize IF PLL Coarse Tuning */
		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x03, 0x1FF6F);
		/* Initialize RF PLL */
		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x04, 0x29403);
		/* Initialize RF PLL Coarse Tuning */
		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x07, 0x1456F);
		/* Initialize TX gain and filter BW (R9) */
		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x09,
			(priv->transceiver_type == ADM8211_RFMD2958 ?
			 0x10050 : 0x00050));
		/* Initialize CAL रेजिस्टर */
		adm8211_rf_ग_लिखो_syn_rfmd2958(dev, 0x08, 0x3FFF8);
		अवरोध;

	हाल ADM8211_MAX2820:
		adm8211_rf_ग_लिखो_syn_max2820(dev, 0x1, 0x01E);
		adm8211_rf_ग_लिखो_syn_max2820(dev, 0x2, 0x001);
		adm8211_rf_ग_लिखो_syn_max2820(dev, 0x3, 0x054);
		adm8211_rf_ग_लिखो_syn_max2820(dev, 0x4, 0x310);
		adm8211_rf_ग_लिखो_syn_max2820(dev, 0x5, 0x000);
		अवरोध;

	हाल ADM8211_AL2210L:
		adm8211_rf_ग_लिखो_syn_al2210l(dev, 0x0, 0x0196C);
		adm8211_rf_ग_लिखो_syn_al2210l(dev, 0x1, 0x007CB);
		adm8211_rf_ग_लिखो_syn_al2210l(dev, 0x2, 0x3582F);
		adm8211_rf_ग_लिखो_syn_al2210l(dev, 0x3, 0x010A9);
		adm8211_rf_ग_लिखो_syn_al2210l(dev, 0x4, 0x77280);
		adm8211_rf_ग_लिखो_syn_al2210l(dev, 0x5, 0x45641);
		adm8211_rf_ग_लिखो_syn_al2210l(dev, 0x6, 0xEA130);
		adm8211_rf_ग_लिखो_syn_al2210l(dev, 0x7, 0x80000);
		adm8211_rf_ग_लिखो_syn_al2210l(dev, 0x8, 0x7850F);
		adm8211_rf_ग_लिखो_syn_al2210l(dev, 0x9, 0xF900C);
		adm8211_rf_ग_लिखो_syn_al2210l(dev, 0xA, 0x00000);
		adm8211_rf_ग_लिखो_syn_al2210l(dev, 0xB, 0x00000);
		अवरोध;

	हाल ADM8211_RFMD2948:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक adm8211_hw_init_bbp(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	u32 reg;

	/* ग_लिखो addresses */
	अगर (priv->bbp_type == ADM8211_TYPE_INTERSIL) अणु
		ADM8211_CSR_WRITE(MMIWA,  0x100E0C0A);
		ADM8211_CSR_WRITE(MMIRD0, 0x00007C7E);
		ADM8211_CSR_WRITE(MMIRD1, 0x00100000);
	पूर्ण अन्यथा अगर (priv->bbp_type == ADM8211_TYPE_RFMD ||
		   priv->bbp_type == ADM8211_TYPE_ADMTEK) अणु
		/* check specअगरic BBP type */
		चयन (priv->specअगरic_bbptype) अणु
		हाल ADM8211_BBP_RFMD3000:
		हाल ADM8211_BBP_RFMD3002:
			ADM8211_CSR_WRITE(MMIWA,  0x00009101);
			ADM8211_CSR_WRITE(MMIRD0, 0x00000301);
			अवरोध;

		हाल ADM8211_BBP_ADM8011:
			ADM8211_CSR_WRITE(MMIWA,  0x00008903);
			ADM8211_CSR_WRITE(MMIRD0, 0x00001716);

			reg = ADM8211_CSR_READ(BBPCTL);
			reg &= ~ADM8211_BBPCTL_TYPE;
			reg |= 0x5 << 18;
			ADM8211_CSR_WRITE(BBPCTL, reg);
			अवरोध;
		पूर्ण

		चयन (priv->pdev->revision) अणु
		हाल ADM8211_REV_CA:
			अगर (priv->transceiver_type == ADM8211_RFMD2958 ||
			    priv->transceiver_type == ADM8211_RFMD2958_RF3000_CONTROL_POWER ||
			    priv->transceiver_type == ADM8211_RFMD2948)
				ADM8211_CSR_WRITE(SYNCTL, 0x1 << 22);
			अन्यथा अगर (priv->transceiver_type == ADM8211_MAX2820 ||
				 priv->transceiver_type == ADM8211_AL2210L)
				ADM8211_CSR_WRITE(SYNCTL, 0x3 << 22);
			अवरोध;

		हाल ADM8211_REV_BA:
			reg  = ADM8211_CSR_READ(MMIRD1);
			reg &= 0x0000FFFF;
			reg |= 0x7e100000;
			ADM8211_CSR_WRITE(MMIRD1, reg);
			अवरोध;

		हाल ADM8211_REV_AB:
		हाल ADM8211_REV_AF:
		शेष:
			ADM8211_CSR_WRITE(MMIRD1, 0x7e100000);
			अवरोध;
		पूर्ण

		/* For RFMD */
		ADM8211_CSR_WRITE(MACTEST, 0x800);
	पूर्ण

	adm8211_hw_init_syn(dev);

	/* Set RF Power control IF pin to PE1+PHYRST# */
	ADM8211_CSR_WRITE(SYNRF, ADM8211_SYNRF_SELRF |
			  ADM8211_SYNRF_PE1 | ADM8211_SYNRF_PHYRST);
	ADM8211_CSR_READ(SYNRF);
	msleep(20);

	/* ग_लिखो BBP regs */
	अगर (priv->bbp_type == ADM8211_TYPE_RFMD) अणु
		/* RF3000 BBP */
		/* another set:
		 * 11: c8
		 * 14: 14
		 * 15: 50 (chan 1..13; chan 14: d0)
		 * 1c: 00
		 * 1d: 84
		 */
		adm8211_ग_लिखो_bbp(dev, RF3000_CCA_CTRL, 0x80);
		/* antenna selection: भागersity */
		adm8211_ग_लिखो_bbp(dev, RF3000_DIVERSITY__RSSI, 0x80);
		adm8211_ग_लिखो_bbp(dev, RF3000_TX_VAR_GAIN__TX_LEN_EXT, 0x74);
		adm8211_ग_लिखो_bbp(dev, RF3000_LOW_GAIN_CALIB, 0x38);
		adm8211_ग_लिखो_bbp(dev, RF3000_HIGH_GAIN_CALIB, 0x40);

		अगर (priv->eeprom->major_version < 2) अणु
			adm8211_ग_लिखो_bbp(dev, 0x1c, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x1d, 0x80);
		पूर्ण अन्यथा अणु
			अगर (priv->pdev->revision == ADM8211_REV_BA)
				adm8211_ग_लिखो_bbp(dev, 0x1c, priv->eeprom->cr28);
			अन्यथा
				adm8211_ग_लिखो_bbp(dev, 0x1c, 0x00);

			adm8211_ग_लिखो_bbp(dev, 0x1d, priv->eeprom->cr29);
		पूर्ण
	पूर्ण अन्यथा अगर (priv->bbp_type == ADM8211_TYPE_ADMTEK) अणु
		/* reset baseband */
		adm8211_ग_लिखो_bbp(dev, 0x00, 0xFF);
		/* antenna selection: भागersity */
		adm8211_ग_लिखो_bbp(dev, 0x07, 0x0A);

		/* TODO: find करोcumentation क्रम this */
		चयन (priv->transceiver_type) अणु
		हाल ADM8211_RFMD2958:
		हाल ADM8211_RFMD2958_RF3000_CONTROL_POWER:
			adm8211_ग_लिखो_bbp(dev, 0x00, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x01, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x02, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x03, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x06, 0x0f);
			adm8211_ग_लिखो_bbp(dev, 0x09, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x0a, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x0b, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x0c, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x0f, 0xAA);
			adm8211_ग_लिखो_bbp(dev, 0x10, 0x8c);
			adm8211_ग_लिखो_bbp(dev, 0x11, 0x43);
			adm8211_ग_लिखो_bbp(dev, 0x18, 0x40);
			adm8211_ग_लिखो_bbp(dev, 0x20, 0x23);
			adm8211_ग_लिखो_bbp(dev, 0x21, 0x02);
			adm8211_ग_लिखो_bbp(dev, 0x22, 0x28);
			adm8211_ग_लिखो_bbp(dev, 0x23, 0x30);
			adm8211_ग_लिखो_bbp(dev, 0x24, 0x2d);
			adm8211_ग_लिखो_bbp(dev, 0x28, 0x35);
			adm8211_ग_लिखो_bbp(dev, 0x2a, 0x8c);
			adm8211_ग_लिखो_bbp(dev, 0x2b, 0x81);
			adm8211_ग_लिखो_bbp(dev, 0x2c, 0x44);
			adm8211_ग_लिखो_bbp(dev, 0x2d, 0x0A);
			adm8211_ग_लिखो_bbp(dev, 0x29, 0x40);
			adm8211_ग_लिखो_bbp(dev, 0x60, 0x08);
			adm8211_ग_लिखो_bbp(dev, 0x64, 0x01);
			अवरोध;

		हाल ADM8211_MAX2820:
			adm8211_ग_लिखो_bbp(dev, 0x00, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x01, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x02, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x03, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x06, 0x0f);
			adm8211_ग_लिखो_bbp(dev, 0x09, 0x05);
			adm8211_ग_लिखो_bbp(dev, 0x0a, 0x02);
			adm8211_ग_लिखो_bbp(dev, 0x0b, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x0c, 0x0f);
			adm8211_ग_लिखो_bbp(dev, 0x0f, 0x55);
			adm8211_ग_लिखो_bbp(dev, 0x10, 0x8d);
			adm8211_ग_लिखो_bbp(dev, 0x11, 0x43);
			adm8211_ग_लिखो_bbp(dev, 0x18, 0x4a);
			adm8211_ग_लिखो_bbp(dev, 0x20, 0x20);
			adm8211_ग_लिखो_bbp(dev, 0x21, 0x02);
			adm8211_ग_लिखो_bbp(dev, 0x22, 0x23);
			adm8211_ग_लिखो_bbp(dev, 0x23, 0x30);
			adm8211_ग_लिखो_bbp(dev, 0x24, 0x2d);
			adm8211_ग_लिखो_bbp(dev, 0x2a, 0x8c);
			adm8211_ग_लिखो_bbp(dev, 0x2b, 0x81);
			adm8211_ग_लिखो_bbp(dev, 0x2c, 0x44);
			adm8211_ग_लिखो_bbp(dev, 0x29, 0x4a);
			adm8211_ग_लिखो_bbp(dev, 0x60, 0x2b);
			adm8211_ग_लिखो_bbp(dev, 0x64, 0x01);
			अवरोध;

		हाल ADM8211_AL2210L:
			adm8211_ग_लिखो_bbp(dev, 0x00, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x01, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x02, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x03, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x06, 0x0f);
			adm8211_ग_लिखो_bbp(dev, 0x07, 0x05);
			adm8211_ग_लिखो_bbp(dev, 0x08, 0x03);
			adm8211_ग_लिखो_bbp(dev, 0x09, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x0a, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x0b, 0x00);
			adm8211_ग_लिखो_bbp(dev, 0x0c, 0x10);
			adm8211_ग_लिखो_bbp(dev, 0x0f, 0x55);
			adm8211_ग_लिखो_bbp(dev, 0x10, 0x8d);
			adm8211_ग_लिखो_bbp(dev, 0x11, 0x43);
			adm8211_ग_लिखो_bbp(dev, 0x18, 0x4a);
			adm8211_ग_लिखो_bbp(dev, 0x20, 0x20);
			adm8211_ग_लिखो_bbp(dev, 0x21, 0x02);
			adm8211_ग_लिखो_bbp(dev, 0x22, 0x23);
			adm8211_ग_लिखो_bbp(dev, 0x23, 0x30);
			adm8211_ग_लिखो_bbp(dev, 0x24, 0x2d);
			adm8211_ग_लिखो_bbp(dev, 0x2a, 0xaa);
			adm8211_ग_लिखो_bbp(dev, 0x2b, 0x81);
			adm8211_ग_लिखो_bbp(dev, 0x2c, 0x44);
			adm8211_ग_लिखो_bbp(dev, 0x29, 0xfa);
			adm8211_ग_लिखो_bbp(dev, 0x60, 0x2d);
			adm8211_ग_लिखो_bbp(dev, 0x64, 0x01);
			अवरोध;

		हाल ADM8211_RFMD2948:
			अवरोध;

		शेष:
			wiphy_debug(dev->wiphy, "unsupported transceiver %d\n",
				    priv->transceiver_type);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		wiphy_debug(dev->wiphy, "unsupported BBP %d\n", priv->bbp_type);

	ADM8211_CSR_WRITE(SYNRF, 0);

	/* Set RF CAL control source to MAC control */
	reg = ADM8211_CSR_READ(SYNCTL);
	reg |= ADM8211_SYNCTL_SELCAL;
	ADM8211_CSR_WRITE(SYNCTL, reg);

	वापस 0;
पूर्ण

/* configures hw beacons/probe responses */
अटल पूर्णांक adm8211_set_rate(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	u32 reg;
	पूर्णांक i = 0;
	u8 rate_buf[12] = अणु0पूर्ण;

	/* ग_लिखो supported rates */
	अगर (priv->pdev->revision != ADM8211_REV_BA) अणु
		rate_buf[0] = ARRAY_SIZE(adm8211_rates);
		क्रम (i = 0; i < ARRAY_SIZE(adm8211_rates); i++)
			rate_buf[i + 1] = (adm8211_rates[i].bitrate / 5) | 0x80;
	पूर्ण अन्यथा अणु
		/* workaround क्रम rev BA specअगरic bug */
		rate_buf[0] = 0x04;
		rate_buf[1] = 0x82;
		rate_buf[2] = 0x04;
		rate_buf[3] = 0x0b;
		rate_buf[4] = 0x16;
	पूर्ण

	adm8211_ग_लिखो_sram_bytes(dev, ADM8211_SRAM_SUPP_RATE, rate_buf,
				 ARRAY_SIZE(adm8211_rates) + 1);

	reg = ADM8211_CSR_READ(PLCPHD) & 0x00FFFFFF; /* keep bits 0-23 */
	reg |= 1 << 15;	/* लघु preamble */
	reg |= 110 << 24;
	ADM8211_CSR_WRITE(PLCPHD, reg);

	/* MTMLT   = 512 TU (max TX MSDU lअगरeसमय)
	 * BCNTSIG = plcp_संकेत (beacon, probe resp, and atim TX rate)
	 * SRTYLIM = 224 (लघु retry limit, TX header value is शेष) */
	ADM8211_CSR_WRITE(TXLMT, (512 << 16) | (110 << 8) | (224 << 0));

	वापस 0;
पूर्ण

अटल व्योम adm8211_hw_init(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	u32 reg;
	u8 cline;

	reg = ADM8211_CSR_READ(PAR);
	reg |= ADM8211_PAR_MRLE | ADM8211_PAR_MRME;
	reg &= ~(ADM8211_PAR_BAR | ADM8211_PAR_CAL);

	अगर (!pci_set_mwi(priv->pdev)) अणु
		reg |= 0x1 << 24;
		pci_पढ़ो_config_byte(priv->pdev, PCI_CACHE_LINE_SIZE, &cline);

		चयन (cline) अणु
		हाल  0x8:
			reg |= (0x1 << 14);
			अवरोध;
		हाल 0x10:
			reg |= (0x2 << 14);
			अवरोध;
		हाल 0x20:
			reg |= (0x3 << 14);
			अवरोध;
		शेष:
			reg |= (0x0 << 14);
			अवरोध;
		पूर्ण
	पूर्ण

	ADM8211_CSR_WRITE(PAR, reg);

	reg = ADM8211_CSR_READ(CSR_TEST1);
	reg &= ~(0xF << 28);
	reg |= (1 << 28) | (1 << 31);
	ADM8211_CSR_WRITE(CSR_TEST1, reg);

	/* lose link after 4 lost beacons */
	reg = (0x04 << 21) | ADM8211_WCSR_TSFTWE | ADM8211_WCSR_LSOE;
	ADM8211_CSR_WRITE(WCSR, reg);

	/* Disable APM, enable receive FIFO threshold, and set drain receive
	 * threshold to store-and-क्रमward */
	reg = ADM8211_CSR_READ(CMDR);
	reg &= ~(ADM8211_CMDR_APM | ADM8211_CMDR_DRT);
	reg |= ADM8211_CMDR_RTE | ADM8211_CMDR_DRT_SF;
	ADM8211_CSR_WRITE(CMDR, reg);

	adm8211_set_rate(dev);

	/* 4-bit values:
	 * PWR1UP   = 8 * 2 ms
	 * PWR0PAPE = 8 us or 5 us
	 * PWR1PAPE = 1 us or 3 us
	 * PWR0TRSW = 5 us
	 * PWR1TRSW = 12 us
	 * PWR0PE2  = 13 us
	 * PWR1PE2  = 1 us
	 * PWR0TXPE = 8 or 6 */
	अगर (priv->pdev->revision < ADM8211_REV_CA)
		ADM8211_CSR_WRITE(TOFS2, 0x8815cd18);
	अन्यथा
		ADM8211_CSR_WRITE(TOFS2, 0x8535cd16);

	/* Enable store and क्रमward क्रम transmit */
	priv->nar = ADM8211_NAR_SF | ADM8211_NAR_PB;
	ADM8211_CSR_WRITE(NAR, priv->nar);

	/* Reset RF */
	ADM8211_CSR_WRITE(SYNRF, ADM8211_SYNRF_RADIO);
	ADM8211_CSR_READ(SYNRF);
	msleep(10);
	ADM8211_CSR_WRITE(SYNRF, 0);
	ADM8211_CSR_READ(SYNRF);
	msleep(5);

	/* Set CFP Max Duration to 0x10 TU */
	reg = ADM8211_CSR_READ(CFPP);
	reg &= ~(0xffff << 8);
	reg |= 0x0010 << 8;
	ADM8211_CSR_WRITE(CFPP, reg);

	/* USCNT = 0x16 (number of प्रणाली घड़ीs, 22 MHz, in 1us
	 * TUCNT = 0x3ff - Tu counter 1024 us  */
	ADM8211_CSR_WRITE(TOFS0, (0x16 << 24) | 0x3ff);

	/* SLOT=20 us, SIFS=110 cycles of 22 MHz (5 us),
	 * DIFS=50 us, EIFS=100 us */
	अगर (priv->pdev->revision < ADM8211_REV_CA)
		ADM8211_CSR_WRITE(IFST, (20 << 23) | (110 << 15) |
					(50 << 9)  | 100);
	अन्यथा
		ADM8211_CSR_WRITE(IFST, (20 << 23) | (24 << 15) |
					(50 << 9)  | 100);

	/* PCNT = 1 (MAC idle समय awake/sleep, unit S)
	 * RMRD = 2346 * 8 + 1 us (max RX duration)  */
	ADM8211_CSR_WRITE(RMD, (1 << 16) | 18769);

	/* MART=65535 us, MIRT=256 us, TSFTOFST=0 us */
	ADM8211_CSR_WRITE(RSPT, 0xffffff00);

	/* Initialize BBP (and SYN) */
	adm8211_hw_init_bbp(dev);

	/* make sure पूर्णांकerrupts are off */
	ADM8211_CSR_WRITE(IER, 0);

	/* ACK पूर्णांकerrupts */
	ADM8211_CSR_WRITE(STSR, ADM8211_CSR_READ(STSR));

	/* Setup WEP (turns it off क्रम now) */
	reg = ADM8211_CSR_READ(MACTEST);
	reg &= ~(7 << 20);
	ADM8211_CSR_WRITE(MACTEST, reg);

	reg = ADM8211_CSR_READ(WEPCTL);
	reg &= ~ADM8211_WEPCTL_WEPENABLE;
	reg |= ADM8211_WEPCTL_WEPRXBYP;
	ADM8211_CSR_WRITE(WEPCTL, reg);

	/* Clear the missed-packet counter. */
	ADM8211_CSR_READ(LPC);
पूर्ण

अटल पूर्णांक adm8211_hw_reset(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	u32 reg, पंचांगp;
	पूर्णांक समयout = 100;

	/* Power-on issue */
	/* TODO: check अगर this is necessary */
	ADM8211_CSR_WRITE(FRCTL, 0);

	/* Reset the chip */
	पंचांगp = ADM8211_CSR_READ(PAR);
	ADM8211_CSR_WRITE(PAR, ADM8211_PAR_SWR);

	जबतक ((ADM8211_CSR_READ(PAR) & ADM8211_PAR_SWR) && समयout--)
		msleep(50);

	अगर (समयout <= 0)
		वापस -ETIMEDOUT;

	ADM8211_CSR_WRITE(PAR, पंचांगp);

	अगर (priv->pdev->revision == ADM8211_REV_BA &&
	    (priv->transceiver_type == ADM8211_RFMD2958_RF3000_CONTROL_POWER ||
	     priv->transceiver_type == ADM8211_RFMD2958)) अणु
		reg = ADM8211_CSR_READ(CSR_TEST1);
		reg |= (1 << 4) | (1 << 5);
		ADM8211_CSR_WRITE(CSR_TEST1, reg);
	पूर्ण अन्यथा अगर (priv->pdev->revision == ADM8211_REV_CA) अणु
		reg = ADM8211_CSR_READ(CSR_TEST1);
		reg &= ~((1 << 4) | (1 << 5));
		ADM8211_CSR_WRITE(CSR_TEST1, reg);
	पूर्ण

	ADM8211_CSR_WRITE(FRCTL, 0);

	reg = ADM8211_CSR_READ(CSR_TEST0);
	reg |= ADM8211_CSR_TEST0_EPRLD;	/* EEPROM Recall */
	ADM8211_CSR_WRITE(CSR_TEST0, reg);

	adm8211_clear_sram(dev);

	वापस 0;
पूर्ण

अटल u64 adm8211_get_tsft(काष्ठा ieee80211_hw *dev,
			    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	u32 tsftl;
	u64 tsft;

	tsftl = ADM8211_CSR_READ(TSFTL);
	tsft = ADM8211_CSR_READ(TSFTH);
	tsft <<= 32;
	tsft |= tsftl;

	वापस tsft;
पूर्ण

अटल व्योम adm8211_set_पूर्णांकerval(काष्ठा ieee80211_hw *dev,
				 अचिन्हित लघु bi, अचिन्हित लघु li)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	u32 reg;

	/* BP (beacon पूर्णांकerval) = data->beacon_पूर्णांकerval
	 * LI (listen पूर्णांकerval) = data->listen_पूर्णांकerval (in beacon पूर्णांकervals) */
	reg = (bi << 16) | li;
	ADM8211_CSR_WRITE(BPLI, reg);
पूर्ण

अटल व्योम adm8211_set_bssid(काष्ठा ieee80211_hw *dev, स्थिर u8 *bssid)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	u32 reg;

	ADM8211_CSR_WRITE(BSSID0, le32_to_cpu(*(__le32 *)bssid));
	reg = ADM8211_CSR_READ(ABDA1);
	reg &= 0x0000ffff;
	reg |= (bssid[4] << 16) | (bssid[5] << 24);
	ADM8211_CSR_WRITE(ABDA1, reg);
पूर्ण

अटल पूर्णांक adm8211_config(काष्ठा ieee80211_hw *dev, u32 changed)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	काष्ठा ieee80211_conf *conf = &dev->conf;
	पूर्णांक channel =
		ieee80211_frequency_to_channel(conf->chandef.chan->center_freq);

	अगर (channel != priv->channel) अणु
		priv->channel = channel;
		adm8211_rf_set_channel(dev, priv->channel);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम adm8211_bss_info_changed(काष्ठा ieee80211_hw *dev,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_bss_conf *conf,
				     u32 changes)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;

	अगर (!(changes & BSS_CHANGED_BSSID))
		वापस;

	अगर (!ether_addr_equal(conf->bssid, priv->bssid)) अणु
		adm8211_set_bssid(dev, conf->bssid);
		स_नकल(priv->bssid, conf->bssid, ETH_ALEN);
	पूर्ण
पूर्ण

अटल u64 adm8211_prepare_multicast(काष्ठा ieee80211_hw *hw,
				     काष्ठा netdev_hw_addr_list *mc_list)
अणु
	अचिन्हित पूर्णांक bit_nr;
	u32 mc_filter[2];
	काष्ठा netdev_hw_addr *ha;

	mc_filter[1] = mc_filter[0] = 0;

	netdev_hw_addr_list_क्रम_each(ha, mc_list) अणु
		bit_nr = ether_crc(ETH_ALEN, ha->addr) >> 26;

		bit_nr &= 0x3F;
		mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
	पूर्ण

	वापस mc_filter[0] | ((u64)(mc_filter[1]) << 32);
पूर्ण

अटल व्योम adm8211_configure_filter(काष्ठा ieee80211_hw *dev,
				     अचिन्हित पूर्णांक changed_flags,
				     अचिन्हित पूर्णांक *total_flags,
				     u64 multicast)
अणु
	अटल स्थिर u8 bcast[ETH_ALEN] = अणु 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;
	काष्ठा adm8211_priv *priv = dev->priv;
	अचिन्हित पूर्णांक new_flags;
	u32 mc_filter[2];

	mc_filter[0] = multicast;
	mc_filter[1] = multicast >> 32;

	new_flags = 0;

	अगर (*total_flags & FIF_ALLMULTI || multicast == ~(0ULL)) अणु
		new_flags |= FIF_ALLMULTI;
		priv->nar &= ~ADM8211_NAR_PR;
		priv->nar |= ADM8211_NAR_MM;
		mc_filter[1] = mc_filter[0] = ~0;
	पूर्ण अन्यथा अणु
		priv->nar &= ~(ADM8211_NAR_MM | ADM8211_NAR_PR);
	पूर्ण

	ADM8211_IDLE_RX();

	ADM8211_CSR_WRITE(MAR0, mc_filter[0]);
	ADM8211_CSR_WRITE(MAR1, mc_filter[1]);
	ADM8211_CSR_READ(NAR);

	अगर (priv->nar & ADM8211_NAR_PR)
		ieee80211_hw_set(dev, RX_INCLUDES_FCS);
	अन्यथा
		__clear_bit(IEEE80211_HW_RX_INCLUDES_FCS, dev->flags);

	अगर (*total_flags & FIF_BCN_PRBRESP_PROMISC)
		adm8211_set_bssid(dev, bcast);
	अन्यथा
		adm8211_set_bssid(dev, priv->bssid);

	ADM8211_RESTORE();

	*total_flags = new_flags;
पूर्ण

अटल पूर्णांक adm8211_add_पूर्णांकerface(काष्ठा ieee80211_hw *dev,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	अगर (priv->mode != NL80211_IFTYPE_MONITOR)
		वापस -EOPNOTSUPP;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		priv->mode = vअगर->type;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	ADM8211_IDLE();

	ADM8211_CSR_WRITE(PAR0, le32_to_cpu(*(__le32 *)vअगर->addr));
	ADM8211_CSR_WRITE(PAR1, le16_to_cpu(*(__le16 *)(vअगर->addr + 4)));

	adm8211_update_mode(dev);

	ADM8211_RESTORE();

	वापस 0;
पूर्ण

अटल व्योम adm8211_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *dev,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	priv->mode = NL80211_IFTYPE_MONITOR;
पूर्ण

अटल पूर्णांक adm8211_init_rings(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	काष्ठा adm8211_desc *desc = शून्य;
	काष्ठा adm8211_rx_ring_info *rx_info;
	काष्ठा adm8211_tx_ring_info *tx_info;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < priv->rx_ring_size; i++) अणु
		desc = &priv->rx_ring[i];
		desc->status = 0;
		desc->length = cpu_to_le32(RX_PKT_SIZE);
		priv->rx_buffers[i].skb = शून्य;
	पूर्ण
	/* Mark the end of RX ring; hw वापसs to base address after this
	 * descriptor */
	desc->length |= cpu_to_le32(RDES1_CONTROL_RER);

	क्रम (i = 0; i < priv->rx_ring_size; i++) अणु
		desc = &priv->rx_ring[i];
		rx_info = &priv->rx_buffers[i];

		rx_info->skb = dev_alloc_skb(RX_PKT_SIZE);
		अगर (rx_info->skb == शून्य)
			अवरोध;
		rx_info->mapping = dma_map_single(&priv->pdev->dev,
						  skb_tail_poपूर्णांकer(rx_info->skb),
						  RX_PKT_SIZE,
						  DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&priv->pdev->dev, rx_info->mapping)) अणु
			dev_kमुक्त_skb(rx_info->skb);
			rx_info->skb = शून्य;
			अवरोध;
		पूर्ण

		desc->buffer1 = cpu_to_le32(rx_info->mapping);
		desc->status = cpu_to_le32(RDES0_STATUS_OWN | RDES0_STATUS_SQL);
	पूर्ण

	/* Setup TX ring. TX buffers descriptors will be filled in as needed */
	क्रम (i = 0; i < priv->tx_ring_size; i++) अणु
		desc = &priv->tx_ring[i];
		tx_info = &priv->tx_buffers[i];

		tx_info->skb = शून्य;
		tx_info->mapping = 0;
		desc->status = 0;
	पूर्ण
	desc->length = cpu_to_le32(TDES1_CONTROL_TER);

	priv->cur_rx = priv->cur_tx = priv->dirty_tx = 0;
	ADM8211_CSR_WRITE(RDB, priv->rx_ring_dma);
	ADM8211_CSR_WRITE(TDBD, priv->tx_ring_dma);

	वापस 0;
पूर्ण

अटल व्योम adm8211_मुक्त_rings(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < priv->rx_ring_size; i++) अणु
		अगर (!priv->rx_buffers[i].skb)
			जारी;

		dma_unmap_single(&priv->pdev->dev,
				 priv->rx_buffers[i].mapping, RX_PKT_SIZE,
				 DMA_FROM_DEVICE);

		dev_kमुक्त_skb(priv->rx_buffers[i].skb);
	पूर्ण

	क्रम (i = 0; i < priv->tx_ring_size; i++) अणु
		अगर (!priv->tx_buffers[i].skb)
			जारी;

		dma_unmap_single(&priv->pdev->dev,
				 priv->tx_buffers[i].mapping,
				 priv->tx_buffers[i].skb->len, DMA_TO_DEVICE);

		dev_kमुक्त_skb(priv->tx_buffers[i].skb);
	पूर्ण
पूर्ण

अटल पूर्णांक adm8211_start(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	पूर्णांक retval;

	/* Power up MAC and RF chips */
	retval = adm8211_hw_reset(dev);
	अगर (retval) अणु
		wiphy_err(dev->wiphy, "hardware reset failed\n");
		जाओ fail;
	पूर्ण

	retval = adm8211_init_rings(dev);
	अगर (retval) अणु
		wiphy_err(dev->wiphy, "failed to initialize rings\n");
		जाओ fail;
	पूर्ण

	/* Init hardware */
	adm8211_hw_init(dev);
	adm8211_rf_set_channel(dev, priv->channel);

	retval = request_irq(priv->pdev->irq, adm8211_पूर्णांकerrupt,
			     IRQF_SHARED, "adm8211", dev);
	अगर (retval) अणु
		wiphy_err(dev->wiphy, "failed to register IRQ handler\n");
		जाओ fail;
	पूर्ण

	ADM8211_CSR_WRITE(IER, ADM8211_IER_NIE | ADM8211_IER_AIE |
			       ADM8211_IER_RCIE | ADM8211_IER_TCIE |
			       ADM8211_IER_TDUIE | ADM8211_IER_GPTIE);
	priv->mode = NL80211_IFTYPE_MONITOR;
	adm8211_update_mode(dev);
	ADM8211_CSR_WRITE(RDR, 0);

	adm8211_set_पूर्णांकerval(dev, 100, 10);
	वापस 0;

fail:
	वापस retval;
पूर्ण

अटल व्योम adm8211_stop(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;

	priv->mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->nar = 0;
	ADM8211_CSR_WRITE(NAR, 0);
	ADM8211_CSR_WRITE(IER, 0);
	ADM8211_CSR_READ(NAR);

	मुक्त_irq(priv->pdev->irq, dev);

	adm8211_मुक्त_rings(dev);
पूर्ण

अटल व्योम adm8211_calc_durations(पूर्णांक *dur, पूर्णांक *plcp, माप_प्रकार payload_len, पूर्णांक len,
				   पूर्णांक plcp_संकेत, पूर्णांक लघु_preamble)
अणु
	/* Alternative calculation from NetBSD: */

/* IEEE 802.11b durations क्रम DSSS PHY in microseconds */
#घोषणा IEEE80211_DUR_DS_LONG_PREAMBLE	144
#घोषणा IEEE80211_DUR_DS_SHORT_PREAMBLE	72
#घोषणा IEEE80211_DUR_DS_FAST_PLCPHDR	24
#घोषणा IEEE80211_DUR_DS_SLOW_PLCPHDR	48
#घोषणा IEEE80211_DUR_DS_SLOW_ACK	112
#घोषणा IEEE80211_DUR_DS_FAST_ACK	56
#घोषणा IEEE80211_DUR_DS_SLOW_CTS	112
#घोषणा IEEE80211_DUR_DS_FAST_CTS	56
#घोषणा IEEE80211_DUR_DS_SLOT		20
#घोषणा IEEE80211_DUR_DS_SIFS		10

	पूर्णांक reमुख्यder;

	*dur = (80 * (24 + payload_len) + plcp_संकेत - 1)
		/ plcp_संकेत;

	अगर (plcp_संकेत <= PLCP_SIGNAL_2M)
		/* 1-2Mbps WLAN: send ACK/CTS at 1Mbps */
		*dur += 3 * (IEEE80211_DUR_DS_SIFS +
			     IEEE80211_DUR_DS_SHORT_PREAMBLE +
			     IEEE80211_DUR_DS_FAST_PLCPHDR) +
			     IEEE80211_DUR_DS_SLOW_CTS + IEEE80211_DUR_DS_SLOW_ACK;
	अन्यथा
		/* 5-11Mbps WLAN: send ACK/CTS at 2Mbps */
		*dur += 3 * (IEEE80211_DUR_DS_SIFS +
			     IEEE80211_DUR_DS_SHORT_PREAMBLE +
			     IEEE80211_DUR_DS_FAST_PLCPHDR) +
			     IEEE80211_DUR_DS_FAST_CTS + IEEE80211_DUR_DS_FAST_ACK;

	/* lengthen duration अगर दीर्घ preamble */
	अगर (!लघु_preamble)
		*dur +=	3 * (IEEE80211_DUR_DS_LONG_PREAMBLE -
			     IEEE80211_DUR_DS_SHORT_PREAMBLE) +
			3 * (IEEE80211_DUR_DS_SLOW_PLCPHDR -
			     IEEE80211_DUR_DS_FAST_PLCPHDR);


	*plcp = (80 * len) / plcp_संकेत;
	reमुख्यder = (80 * len) % plcp_संकेत;
	अगर (plcp_संकेत == PLCP_SIGNAL_11M &&
	    reमुख्यder <= 30 && reमुख्यder > 0)
		*plcp = (*plcp | 0x8000) + 1;
	अन्यथा अगर (reमुख्यder)
		(*plcp)++;
पूर्ण

/* Transmit skb w/adm8211_tx_hdr (802.11 header created by hardware) */
अटल पूर्णांक adm8211_tx_raw(काष्ठा ieee80211_hw *dev, काष्ठा sk_buff *skb,
			   u16 plcp_संकेत,
			   माप_प्रकार hdrlen)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	अचिन्हित दीर्घ flags;
	dma_addr_t mapping;
	अचिन्हित पूर्णांक entry;
	u32 flag;

	mapping = dma_map_single(&priv->pdev->dev, skb->data, skb->len,
				 DMA_TO_DEVICE);
	अगर (dma_mapping_error(&priv->pdev->dev, mapping))
		वापस -ENOMEM;

	spin_lock_irqsave(&priv->lock, flags);

	अगर (priv->cur_tx - priv->dirty_tx == priv->tx_ring_size / 2)
		flag = TDES1_CONTROL_IC | TDES1_CONTROL_LS | TDES1_CONTROL_FS;
	अन्यथा
		flag = TDES1_CONTROL_LS | TDES1_CONTROL_FS;

	अगर (priv->cur_tx - priv->dirty_tx == priv->tx_ring_size - 2)
		ieee80211_stop_queue(dev, 0);

	entry = priv->cur_tx % priv->tx_ring_size;

	priv->tx_buffers[entry].skb = skb;
	priv->tx_buffers[entry].mapping = mapping;
	priv->tx_buffers[entry].hdrlen = hdrlen;
	priv->tx_ring[entry].buffer1 = cpu_to_le32(mapping);

	अगर (entry == priv->tx_ring_size - 1)
		flag |= TDES1_CONTROL_TER;
	priv->tx_ring[entry].length = cpu_to_le32(flag | skb->len);

	/* Set TX rate (SIGNAL field in PLCP PPDU क्रमmat) */
	flag = TDES0_CONTROL_OWN | (plcp_संकेत << 20) | 8 /* ? */;
	priv->tx_ring[entry].status = cpu_to_le32(flag);

	priv->cur_tx++;

	spin_unlock_irqrestore(&priv->lock, flags);

	/* Trigger transmit poll */
	ADM8211_CSR_WRITE(TDR, 0);

	वापस 0;
पूर्ण

/* Put adm8211_tx_hdr on skb and transmit */
अटल व्योम adm8211_tx(काष्ठा ieee80211_hw *dev,
		       काष्ठा ieee80211_tx_control *control,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा adm8211_tx_hdr *txhdr;
	माप_प्रकार payload_len, hdrlen;
	पूर्णांक plcp, dur, len, plcp_संकेत, लघु_preamble;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_rate *txrate = ieee80211_get_tx_rate(dev, info);
	u8 rc_flags;

	rc_flags = info->control.rates[0].flags;
	लघु_preamble = !!(rc_flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE);
	plcp_संकेत = txrate->bitrate;

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	स_नकल(skb->cb, skb->data, hdrlen);
	hdr = (काष्ठा ieee80211_hdr *)skb->cb;
	skb_pull(skb, hdrlen);
	payload_len = skb->len;

	txhdr = skb_push(skb, माप(*txhdr));
	स_रखो(txhdr, 0, माप(*txhdr));
	स_नकल(txhdr->da, ieee80211_get_DA(hdr), ETH_ALEN);
	txhdr->संकेत = plcp_संकेत;
	txhdr->frame_body_size = cpu_to_le16(payload_len);
	txhdr->frame_control = hdr->frame_control;

	len = hdrlen + payload_len + FCS_LEN;

	txhdr->frag = cpu_to_le16(0x0FFF);
	adm8211_calc_durations(&dur, &plcp, payload_len,
			       len, plcp_संकेत, लघु_preamble);
	txhdr->plcp_frag_head_len = cpu_to_le16(plcp);
	txhdr->plcp_frag_tail_len = cpu_to_le16(plcp);
	txhdr->dur_frag_head = cpu_to_le16(dur);
	txhdr->dur_frag_tail = cpu_to_le16(dur);

	txhdr->header_control = cpu_to_le16(ADM8211_TXHDRCTL_ENABLE_EXTEND_HEADER);

	अगर (लघु_preamble)
		txhdr->header_control |= cpu_to_le16(ADM8211_TXHDRCTL_SHORT_PREAMBLE);

	अगर (rc_flags & IEEE80211_TX_RC_USE_RTS_CTS)
		txhdr->header_control |= cpu_to_le16(ADM8211_TXHDRCTL_ENABLE_RTS);

	txhdr->retry_limit = info->control.rates[0].count;

	अगर (adm8211_tx_raw(dev, skb, plcp_संकेत, hdrlen)) अणु
		/* Drop packet */
		ieee80211_मुक्त_txskb(dev, skb);
	पूर्ण
पूर्ण

अटल पूर्णांक adm8211_alloc_rings(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा adm8211_priv *priv = dev->priv;
	अचिन्हित पूर्णांक ring_size;

	priv->rx_buffers = kदो_स्मृति(माप(*priv->rx_buffers) * priv->rx_ring_size +
				   माप(*priv->tx_buffers) * priv->tx_ring_size, GFP_KERNEL);
	अगर (!priv->rx_buffers)
		वापस -ENOMEM;

	priv->tx_buffers = (व्योम *)priv->rx_buffers +
			   माप(*priv->rx_buffers) * priv->rx_ring_size;

	/* Allocate TX/RX descriptors */
	ring_size = माप(काष्ठा adm8211_desc) * priv->rx_ring_size +
		    माप(काष्ठा adm8211_desc) * priv->tx_ring_size;
	priv->rx_ring = dma_alloc_coherent(&priv->pdev->dev, ring_size,
					   &priv->rx_ring_dma, GFP_KERNEL);

	अगर (!priv->rx_ring) अणु
		kमुक्त(priv->rx_buffers);
		priv->rx_buffers = शून्य;
		priv->tx_buffers = शून्य;
		वापस -ENOMEM;
	पूर्ण

	priv->tx_ring = priv->rx_ring + priv->rx_ring_size;
	priv->tx_ring_dma = priv->rx_ring_dma +
			    माप(काष्ठा adm8211_desc) * priv->rx_ring_size;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops adm8211_ops = अणु
	.tx			= adm8211_tx,
	.start			= adm8211_start,
	.stop			= adm8211_stop,
	.add_पूर्णांकerface		= adm8211_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= adm8211_हटाओ_पूर्णांकerface,
	.config			= adm8211_config,
	.bss_info_changed	= adm8211_bss_info_changed,
	.prepare_multicast	= adm8211_prepare_multicast,
	.configure_filter	= adm8211_configure_filter,
	.get_stats		= adm8211_get_stats,
	.get_tsf		= adm8211_get_tsft
पूर्ण;

अटल पूर्णांक adm8211_probe(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ieee80211_hw *dev;
	काष्ठा adm8211_priv *priv;
	अचिन्हित दीर्घ mem_len;
	अचिन्हित पूर्णांक io_len;
	पूर्णांक err;
	u32 reg;
	u8 perm_addr[ETH_ALEN];

	err = pci_enable_device(pdev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s (adm8211): Cannot enable new PCI device\n",
		       pci_name(pdev));
		वापस err;
	पूर्ण

	io_len = pci_resource_len(pdev, 0);
	mem_len = pci_resource_len(pdev, 1);
	अगर (io_len < 256 || mem_len < 1024) अणु
		prपूर्णांकk(KERN_ERR "%s (adm8211): Too short PCI resources\n",
		       pci_name(pdev));
		err = -ENOMEM;
		जाओ err_disable_pdev;
	पूर्ण


	/* check signature */
	pci_पढ़ो_config_dword(pdev, 0x80 /* CR32 */, &reg);
	अगर (reg != ADM8211_SIG1 && reg != ADM8211_SIG2) अणु
		prपूर्णांकk(KERN_ERR "%s (adm8211): Invalid signature (0x%x)\n",
		       pci_name(pdev), reg);
		err = -EINVAL;
		जाओ err_disable_pdev;
	पूर्ण

	err = pci_request_regions(pdev, "adm8211");
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s (adm8211): Cannot obtain PCI resources\n",
		       pci_name(pdev));
		वापस err; /* someone अन्यथा grabbed it? करोn't disable it */
	पूर्ण

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s (adm8211): No suitable DMA available\n",
		       pci_name(pdev));
		जाओ err_मुक्त_reg;
	पूर्ण

	pci_set_master(pdev);

	dev = ieee80211_alloc_hw(माप(*priv), &adm8211_ops);
	अगर (!dev) अणु
		prपूर्णांकk(KERN_ERR "%s (adm8211): ieee80211 alloc failed\n",
		       pci_name(pdev));
		err = -ENOMEM;
		जाओ err_मुक्त_reg;
	पूर्ण
	priv = dev->priv;
	priv->pdev = pdev;

	spin_lock_init(&priv->lock);

	SET_IEEE80211_DEV(dev, &pdev->dev);

	pci_set_drvdata(pdev, dev);

	priv->map = pci_iomap(pdev, 1, mem_len);
	अगर (!priv->map)
		priv->map = pci_iomap(pdev, 0, io_len);

	अगर (!priv->map) अणु
		prपूर्णांकk(KERN_ERR "%s (adm8211): Cannot map device memory\n",
		       pci_name(pdev));
		err = -ENOMEM;
		जाओ err_मुक्त_dev;
	पूर्ण

	priv->rx_ring_size = rx_ring_size;
	priv->tx_ring_size = tx_ring_size;

	err = adm8211_alloc_rings(dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s (adm8211): Cannot allocate TX/RX ring\n",
		       pci_name(pdev));
		जाओ err_iounmap;
	पूर्ण

	*(__le32 *)perm_addr = cpu_to_le32(ADM8211_CSR_READ(PAR0));
	*(__le16 *)&perm_addr[4] =
		cpu_to_le16(ADM8211_CSR_READ(PAR1) & 0xFFFF);

	अगर (!is_valid_ether_addr(perm_addr)) अणु
		prपूर्णांकk(KERN_WARNING "%s (adm8211): Invalid hwaddr in EEPROM!\n",
		       pci_name(pdev));
		eth_अक्रमom_addr(perm_addr);
	पूर्ण
	SET_IEEE80211_PERM_ADDR(dev, perm_addr);

	dev->extra_tx_headroom = माप(काष्ठा adm8211_tx_hdr);
	/* dev->flags = RX_INCLUDES_FCS in promisc mode */
	ieee80211_hw_set(dev, SIGNAL_UNSPEC);
	dev->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION);

	dev->max_संकेत = 100;    /* FIXME: find better value */

	dev->queues = 1; /* ADM8211C supports more, maybe ADM8211B too */

	priv->retry_limit = 3;
	priv->ant_घातer = 0x40;
	priv->tx_घातer = 0x40;
	priv->lpf_cutoff = 0xFF;
	priv->lnags_threshold = 0xFF;
	priv->mode = NL80211_IFTYPE_UNSPECIFIED;

	/* Power-on issue. EEPROM won't पढ़ो correctly without */
	अगर (pdev->revision >= ADM8211_REV_BA) अणु
		ADM8211_CSR_WRITE(FRCTL, 0);
		ADM8211_CSR_READ(FRCTL);
		ADM8211_CSR_WRITE(FRCTL, 1);
		ADM8211_CSR_READ(FRCTL);
		msleep(100);
	पूर्ण

	err = adm8211_पढ़ो_eeprom(dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s (adm8211): Can't alloc eeprom buffer\n",
		       pci_name(pdev));
		जाओ err_मुक्त_desc;
	पूर्ण

	priv->channel = 1;

	dev->wiphy->bands[NL80211_BAND_2GHZ] = &priv->band;

	wiphy_ext_feature_set(dev->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	err = ieee80211_रेजिस्टर_hw(dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s (adm8211): Cannot register device\n",
		       pci_name(pdev));
		जाओ err_मुक्त_eeprom;
	पूर्ण

	wiphy_info(dev->wiphy, "hwaddr %pM, Rev 0x%02x\n",
		   dev->wiphy->perm_addr, pdev->revision);

	वापस 0;

 err_मुक्त_eeprom:
	kमुक्त(priv->eeprom);

 err_मुक्त_desc:
	dma_मुक्त_coherent(&pdev->dev,
			  माप(काष्ठा adm8211_desc) * priv->rx_ring_size +
			  माप(काष्ठा adm8211_desc) * priv->tx_ring_size,
			  priv->rx_ring, priv->rx_ring_dma);
	kमुक्त(priv->rx_buffers);

 err_iounmap:
	pci_iounmap(pdev, priv->map);

 err_मुक्त_dev:
	ieee80211_मुक्त_hw(dev);

 err_मुक्त_reg:
	pci_release_regions(pdev);

 err_disable_pdev:
	pci_disable_device(pdev);
	वापस err;
पूर्ण


अटल व्योम adm8211_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ieee80211_hw *dev = pci_get_drvdata(pdev);
	काष्ठा adm8211_priv *priv;

	अगर (!dev)
		वापस;

	ieee80211_unरेजिस्टर_hw(dev);

	priv = dev->priv;

	dma_मुक्त_coherent(&pdev->dev,
			  माप(काष्ठा adm8211_desc) * priv->rx_ring_size +
			  माप(काष्ठा adm8211_desc) * priv->tx_ring_size,
			  priv->rx_ring, priv->rx_ring_dma);

	kमुक्त(priv->rx_buffers);
	kमुक्त(priv->eeprom);
	pci_iounmap(pdev, priv->map);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	ieee80211_मुक्त_hw(dev);
पूर्ण


#घोषणा adm8211_suspend शून्य
#घोषणा adm8211_resume शून्य

MODULE_DEVICE_TABLE(pci, adm8211_pci_id_table);

अटल SIMPLE_DEV_PM_OPS(adm8211_pm_ops, adm8211_suspend, adm8211_resume);

/* TODO: implement enable_wake */
अटल काष्ठा pci_driver adm8211_driver = अणु
	.name		= "adm8211",
	.id_table	= adm8211_pci_id_table,
	.probe		= adm8211_probe,
	.हटाओ		= adm8211_हटाओ,
	.driver.pm	= &adm8211_pm_ops,
पूर्ण;

module_pci_driver(adm8211_driver);
