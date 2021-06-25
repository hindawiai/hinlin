<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2002 Intersil Americas Inc.
 *  Copyright (C) 2004 Aurelien Alleaume <slts@मुक्त.fr>
 */

#समावेश <linux/module.h>
#समावेश <linux/gfp.h>

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "prismcompat.h"
#समावेश "isl_38xx.h"
#समावेश "islpci_eth.h"
#समावेश "islpci_mgt.h"
#समावेश "oid_mgt.h"

/******************************************************************************
    Network Interface functions
******************************************************************************/
व्योम
islpci_eth_cleanup_transmit(islpci_निजी *priv,
			    isl38xx_control_block *control_block)
अणु
	काष्ठा sk_buff *skb;
	u32 index;

	/* compare the control block पढ़ो poपूर्णांकer with the मुक्त poपूर्णांकer */
	जबतक (priv->मुक्त_data_tx !=
	       le32_to_cpu(control_block->
			   device_curr_frag[ISL38XX_CB_TX_DATA_LQ])) अणु
		/* पढ़ो the index of the first fragment to be मुक्तd */
		index = priv->मुक्त_data_tx % ISL38XX_CB_TX_QSIZE;

		/* check क्रम holes in the arrays caused by multi fragment frames
		 * searching क्रम the last fragment of a frame */
		अगर (priv->pci_map_tx_address[index]) अणु
			/* entry is the last fragment of a frame
			 * मुक्त the skb काष्ठाure and unmap pci memory */
			skb = priv->data_low_tx[index];

#अगर VERBOSE > SHOW_ERROR_MESSAGES
			DEBUG(SHOW_TRACING,
			      "cleanup skb %p skb->data %p skb->len %u truesize %u\n",
			      skb, skb->data, skb->len, skb->truesize);
#पूर्ण_अगर

			dma_unmap_single(&priv->pdev->dev,
					 priv->pci_map_tx_address[index],
					 skb->len, DMA_TO_DEVICE);
			dev_kमुक्त_skb_irq(skb);
			skb = शून्य;
		पूर्ण
		/* increment the मुक्त data low queue poपूर्णांकer */
		priv->मुक्त_data_tx++;
	पूर्ण
पूर्ण

netdev_tx_t
islpci_eth_transmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	isl38xx_control_block *cb = priv->control_block;
	u32 index;
	dma_addr_t pci_map_address;
	पूर्णांक frame_size;
	isl38xx_fragment *fragment;
	पूर्णांक offset;
	काष्ठा sk_buff *newskb;
	पूर्णांक newskb_offset;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर wds_mac[6];
	u32 curr_frag;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_FUNCTION_CALLS, "islpci_eth_transmit\n");
#पूर्ण_अगर

	/* lock the driver code */
	spin_lock_irqsave(&priv->slock, flags);

	/* check whether the destination queue has enough fragments क्रम the frame */
	curr_frag = le32_to_cpu(cb->driver_curr_frag[ISL38XX_CB_TX_DATA_LQ]);
	अगर (unlikely(curr_frag - priv->मुक्त_data_tx >= ISL38XX_CB_TX_QSIZE)) अणु
		prपूर्णांकk(KERN_ERR "%s: transmit device queue full when awake\n",
		       ndev->name);
		netअगर_stop_queue(ndev);

		/* trigger the device */
		isl38xx_w32_flush(priv->device_base, ISL38XX_DEV_INT_UPDATE,
				  ISL38XX_DEV_INT_REG);
		udelay(ISL38XX_WRITEIO_DELAY);
		जाओ drop_मुक्त;
	पूर्ण
	/* Check alignment and WDS frame क्रमmatting. The start of the packet should
	 * be aligned on a 4-byte boundary. If WDS is enabled add another 6 bytes
	 * and add WDS address inक्रमmation */
	अगर (likely(((दीर्घ) skb->data & 0x03) | init_wds)) अणु
		/* get the number of bytes to add and re-align */
		offset = (4 - (दीर्घ) skb->data) & 0x03;
		offset += init_wds ? 6 : 0;

		/* check whether the current skb can be used  */
		अगर (!skb_cloned(skb) && (skb_tailroom(skb) >= offset)) अणु
			अचिन्हित अक्षर *src = skb->data;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
			DEBUG(SHOW_TRACING, "skb offset %i wds %i\n", offset,
			      init_wds);
#पूर्ण_अगर

			/* align the buffer on 4-byte boundary */
			skb_reserve(skb, (4 - (दीर्घ) skb->data) & 0x03);
			अगर (init_wds) अणु
				/* wds requires an additional address field of 6 bytes */
				skb_put(skb, 6);
#अगर_घोषित ISLPCI_ETH_DEBUG
				prपूर्णांकk("islpci_eth_transmit:wds_mac\n");
#पूर्ण_अगर
				स_हटाओ(skb->data + 6, src, skb->len);
				skb_copy_to_linear_data(skb, wds_mac, 6);
			पूर्ण अन्यथा अणु
				स_हटाओ(skb->data, src, skb->len);
			पूर्ण

#अगर VERBOSE > SHOW_ERROR_MESSAGES
			DEBUG(SHOW_TRACING, "memmove %p %p %i\n", skb->data,
			      src, skb->len);
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			newskb =
			    dev_alloc_skb(init_wds ? skb->len + 6 : skb->len);
			अगर (unlikely(newskb == शून्य)) अणु
				prपूर्णांकk(KERN_ERR "%s: Cannot allocate skb\n",
				       ndev->name);
				जाओ drop_मुक्त;
			पूर्ण
			newskb_offset = (4 - (दीर्घ) newskb->data) & 0x03;

			/* Check अगर newskb->data is aligned */
			अगर (newskb_offset)
				skb_reserve(newskb, newskb_offset);

			skb_put(newskb, init_wds ? skb->len + 6 : skb->len);
			अगर (init_wds) अणु
				skb_copy_from_linear_data(skb,
							  newskb->data + 6,
							  skb->len);
				skb_copy_to_linear_data(newskb, wds_mac, 6);
#अगर_घोषित ISLPCI_ETH_DEBUG
				prपूर्णांकk("islpci_eth_transmit:wds_mac\n");
#पूर्ण_अगर
			पूर्ण अन्यथा
				skb_copy_from_linear_data(skb, newskb->data,
							  skb->len);

#अगर VERBOSE > SHOW_ERROR_MESSAGES
			DEBUG(SHOW_TRACING, "memcpy %p %p %i wds %i\n",
			      newskb->data, skb->data, skb->len, init_wds);
#पूर्ण_अगर

			newskb->dev = skb->dev;
			dev_kमुक्त_skb_irq(skb);
			skb = newskb;
		पूर्ण
	पूर्ण
	/* display the buffer contents क्रम debugging */
#अगर VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_BUFFER_CONTENTS, "\ntx %p ", skb->data);
	display_buffer((अक्षर *) skb->data, skb->len);
#पूर्ण_अगर

	/* map the skb buffer to pci memory क्रम DMA operation */
	pci_map_address = dma_map_single(&priv->pdev->dev, (व्योम *)skb->data,
					 skb->len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&priv->pdev->dev, pci_map_address)) अणु
		prपूर्णांकk(KERN_WARNING "%s: cannot map buffer to PCI\n",
		       ndev->name);
		जाओ drop_मुक्त;
	पूर्ण
	/* Place the fragment in the control block काष्ठाure. */
	index = curr_frag % ISL38XX_CB_TX_QSIZE;
	fragment = &cb->tx_data_low[index];

	priv->pci_map_tx_address[index] = pci_map_address;
	/* store the skb address क्रम future मुक्तing  */
	priv->data_low_tx[index] = skb;
	/* set the proper fragment start address and size inक्रमmation */
	frame_size = skb->len;
	fragment->size = cpu_to_le16(frame_size);
	fragment->flags = cpu_to_le16(0);	/* set to 1 अगर more fragments */
	fragment->address = cpu_to_le32(pci_map_address);
	curr_frag++;

	/* The fragment address in the control block must have been
	 * written beक्रमe announcing the frame buffer to device. */
	wmb();
	cb->driver_curr_frag[ISL38XX_CB_TX_DATA_LQ] = cpu_to_le32(curr_frag);

	अगर (curr_frag - priv->मुक्त_data_tx + ISL38XX_MIN_QTHRESHOLD
	    > ISL38XX_CB_TX_QSIZE) अणु
		/* stop sends from upper layers */
		netअगर_stop_queue(ndev);

		/* set the full flag क्रम the transmission queue */
		priv->data_low_tx_full = 1;
	पूर्ण

	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += skb->len;

	/* trigger the device */
	islpci_trigger(priv);

	/* unlock the driver code */
	spin_unlock_irqrestore(&priv->slock, flags);

	वापस NETDEV_TX_OK;

      drop_मुक्त:
	ndev->stats.tx_dropped++;
	spin_unlock_irqrestore(&priv->slock, flags);
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल अंतरभूत पूर्णांक
islpci_monitor_rx(islpci_निजी *priv, काष्ठा sk_buff **skb)
अणु
	/* The card reports full 802.11 packets but with a 20 bytes
	 * header and without the FCS. But there a is a bit that
	 * indicates अगर the packet is corrupted :-) */
	काष्ठा rfmon_header *hdr = (काष्ठा rfmon_header *) (*skb)->data;

	अगर (hdr->flags & 0x01)
		/* This one is bad. Drop it ! */
		वापस -1;
	अगर (priv->ndev->type == ARPHRD_IEEE80211_PRISM) अणु
		काष्ठा avs_80211_1_header *avs;
		/* extract the relevant data from the header */
		u32 घड़ी = le32_to_cpu(hdr->घड़ी);
		u8 rate = hdr->rate;
		u16 freq = le16_to_cpu(hdr->freq);
		u8 rssi = hdr->rssi;

		skb_pull(*skb, माप (काष्ठा rfmon_header));

		अगर (skb_headroom(*skb) < माप (काष्ठा avs_80211_1_header)) अणु
			काष्ठा sk_buff *newskb = skb_copy_expand(*skb,
								 माप (काष्ठा
									 avs_80211_1_header),
								 0, GFP_ATOMIC);
			अगर (newskb) अणु
				dev_kमुक्त_skb_irq(*skb);
				*skb = newskb;
			पूर्ण अन्यथा
				वापस -1;
			/* This behavior is not very subtile... */
		पूर्ण

		/* make room क्रम the new header and fill it. */
		avs = skb_push(*skb, माप(काष्ठा avs_80211_1_header));

		avs->version = cpu_to_be32(P80211CAPTURE_VERSION);
		avs->length = cpu_to_be32(माप (काष्ठा avs_80211_1_header));
		avs->maस_समय = cpu_to_be64(घड़ी);
		avs->hostसमय = cpu_to_be64(jअगरfies);
		avs->phytype = cpu_to_be32(6);	/*OFDM: 6 क्रम (g), 8 क्रम (a) */
		avs->channel = cpu_to_be32(channel_of_freq(freq));
		avs->datarate = cpu_to_be32(rate * 5);
		avs->antenna = cpu_to_be32(0);	/*unknown */
		avs->priority = cpu_to_be32(0);	/*unknown */
		avs->ssi_type = cpu_to_be32(3);	/*2: dBm, 3: raw RSSI */
		avs->ssi_संकेत = cpu_to_be32(rssi & 0x7f);
		avs->ssi_noise = cpu_to_be32(priv->local_iwstatistics.qual.noise);	/*better than 'undefined', I assume */
		avs->preamble = cpu_to_be32(0);	/*unknown */
		avs->encoding = cpu_to_be32(0);	/*unknown */
	पूर्ण अन्यथा
		skb_pull(*skb, माप (काष्ठा rfmon_header));

	(*skb)->protocol = htons(ETH_P_802_2);
	skb_reset_mac_header(*skb);
	(*skb)->pkt_type = PACKET_OTHERHOST;

	वापस 0;
पूर्ण

पूर्णांक
islpci_eth_receive(islpci_निजी *priv)
अणु
	काष्ठा net_device *ndev = priv->ndev;
	isl38xx_control_block *control_block = priv->control_block;
	काष्ठा sk_buff *skb;
	u16 size;
	u32 index, offset;
	अचिन्हित अक्षर *src;
	पूर्णांक discard = 0;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_FUNCTION_CALLS, "islpci_eth_receive\n");
#पूर्ण_अगर

	/* the device has written an Ethernet frame in the data area
	 * of the sk_buff without updating the काष्ठाure, करो it now */
	index = priv->मुक्त_data_rx % ISL38XX_CB_RX_QSIZE;
	size = le16_to_cpu(control_block->rx_data_low[index].size);
	skb = priv->data_low_rx[index];
	offset = ((अचिन्हित दीर्घ)
		  le32_to_cpu(control_block->rx_data_low[index].address) -
		  (अचिन्हित दीर्घ) skb->data) & 3;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_TRACING,
	      "frq->addr %x skb->data %p skb->len %u offset %u truesize %u\n",
	      control_block->rx_data_low[priv->मुक्त_data_rx].address, skb->data,
	      skb->len, offset, skb->truesize);
#पूर्ण_अगर

	/* delete the streaming DMA mapping beक्रमe processing the skb */
	dma_unmap_single(&priv->pdev->dev, priv->pci_map_rx_address[index],
			 MAX_FRAGMENT_SIZE_RX + 2, DMA_FROM_DEVICE);

	/* update the skb काष्ठाure and align the buffer */
	skb_put(skb, size);
	अगर (offset) अणु
		/* shअगरt the buffer allocation offset bytes to get the right frame */
		skb_pull(skb, 2);
		skb_put(skb, 2);
	पूर्ण
#अगर VERBOSE > SHOW_ERROR_MESSAGES
	/* display the buffer contents क्रम debugging */
	DEBUG(SHOW_BUFFER_CONTENTS, "\nrx %p ", skb->data);
	display_buffer((अक्षर *) skb->data, skb->len);
#पूर्ण_अगर

	/* check whether WDS is enabled and whether the data frame is a WDS frame */

	अगर (init_wds) अणु
		/* WDS enabled, check क्रम the wds address on the first 6 bytes of the buffer */
		src = skb->data + 6;
		स_हटाओ(skb->data, src, skb->len - 6);
		skb_trim(skb, skb->len - 6);
	पूर्ण
#अगर VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_TRACING, "Fragment size %i in skb at %p\n", size, skb);
	DEBUG(SHOW_TRACING, "Skb data at %p, length %i\n", skb->data, skb->len);

	/* display the buffer contents क्रम debugging */
	DEBUG(SHOW_BUFFER_CONTENTS, "\nrx %p ", skb->data);
	display_buffer((अक्षर *) skb->data, skb->len);
#पूर्ण_अगर
	/* take care of monitor mode and spy monitoring. */
	अगर (unlikely(priv->iw_mode == IW_MODE_MONITOR)) अणु
		skb->dev = ndev;
		discard = islpci_monitor_rx(priv, &skb);
	पूर्ण अन्यथा अणु
		अगर (unlikely(skb->data[2 * ETH_ALEN] == 0)) अणु
			/* The packet has a rx_annex. Read it क्रम spy monitoring, Then
			 * हटाओ it, जबतक keeping the 2 leading MAC addr.
			 */
			काष्ठा iw_quality wstats;
			काष्ठा rx_annex_header *annex =
			    (काष्ठा rx_annex_header *) skb->data;
			wstats.level = annex->rfmon.rssi;
			/* The noise value can be a bit outdated अगर nobody's
			 * पढ़ोing wireless stats... */
			wstats.noise = priv->local_iwstatistics.qual.noise;
			wstats.qual = wstats.level - wstats.noise;
			wstats.updated = 0x07;
			/* Update spy records */
			wireless_spy_update(ndev, annex->addr2, &wstats);

			skb_copy_from_linear_data(skb,
						  (skb->data +
						   माप(काष्ठा rfmon_header)),
						  2 * ETH_ALEN);
			skb_pull(skb, माप (काष्ठा rfmon_header));
		पूर्ण
		skb->protocol = eth_type_trans(skb, ndev);
	पूर्ण
	skb->ip_summed = CHECKSUM_NONE;
	ndev->stats.rx_packets++;
	ndev->stats.rx_bytes += size;

	/* deliver the skb to the network layer */
#अगर_घोषित ISLPCI_ETH_DEBUG
	prपूर्णांकk
	    ("islpci_eth_receive:netif_rx %2.2X %2.2X %2.2X %2.2X %2.2X %2.2X\n",
	     skb->data[0], skb->data[1], skb->data[2], skb->data[3],
	     skb->data[4], skb->data[5]);
#पूर्ण_अगर
	अगर (unlikely(discard)) अणु
		dev_kमुक्त_skb_irq(skb);
		skb = शून्य;
	पूर्ण अन्यथा
		netअगर_rx(skb);

	/* increment the पढ़ो index क्रम the rx data low queue */
	priv->मुक्त_data_rx++;

	/* add one or more sk_buff काष्ठाures */
	जबतक (index =
	       le32_to_cpu(control_block->
			   driver_curr_frag[ISL38XX_CB_RX_DATA_LQ]),
	       index - priv->मुक्त_data_rx < ISL38XX_CB_RX_QSIZE) अणु
		/* allocate an sk_buff क्रम received data frames storage
		 * include any required allignment operations */
		skb = dev_alloc_skb(MAX_FRAGMENT_SIZE_RX + 2);
		अगर (unlikely(skb == शून्य)) अणु
			/* error allocating an sk_buff काष्ठाure elements */
			DEBUG(SHOW_ERROR_MESSAGES, "Error allocating skb\n");
			अवरोध;
		पूर्ण
		skb_reserve(skb, (4 - (दीर्घ) skb->data) & 0x03);
		/* store the new skb काष्ठाure poपूर्णांकer */
		index = index % ISL38XX_CB_RX_QSIZE;
		priv->data_low_rx[index] = skb;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
		DEBUG(SHOW_TRACING,
		      "new alloc skb %p skb->data %p skb->len %u index %u truesize %u\n",
		      skb, skb->data, skb->len, index, skb->truesize);
#पूर्ण_अगर

		/* set the streaming DMA mapping क्रम proper PCI bus operation */
		priv->pci_map_rx_address[index] =
		    dma_map_single(&priv->pdev->dev, (व्योम *)skb->data,
				   MAX_FRAGMENT_SIZE_RX + 2, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&priv->pdev->dev, priv->pci_map_rx_address[index])) अणु
			/* error mapping the buffer to device accessible memory address */
			DEBUG(SHOW_ERROR_MESSAGES,
			      "Error mapping DMA address\n");

			/* मुक्त the skbuf काष्ठाure beक्रमe पातing */
			dev_kमुक्त_skb_irq(skb);
			skb = शून्य;
			अवरोध;
		पूर्ण
		/* update the fragment address */
		control_block->rx_data_low[index].address =
			cpu_to_le32((u32)priv->pci_map_rx_address[index]);
		wmb();

		/* increment the driver पढ़ो poपूर्णांकer */
		le32_add_cpu(&control_block->
			     driver_curr_frag[ISL38XX_CB_RX_DATA_LQ], 1);
	पूर्ण

	/* trigger the device */
	islpci_trigger(priv);

	वापस 0;
पूर्ण

व्योम
islpci_करो_reset_and_wake(काष्ठा work_काष्ठा *work)
अणु
	islpci_निजी *priv = container_of(work, islpci_निजी, reset_task);

	islpci_reset(priv, 1);
	priv->reset_task_pending = 0;
	smp_wmb();
	netअगर_wake_queue(priv->ndev);
पूर्ण

व्योम
islpci_eth_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	islpci_निजी *priv = netdev_priv(ndev);

	/* increment the transmit error counter */
	ndev->stats.tx_errors++;

	अगर (!priv->reset_task_pending) अणु
		prपूर्णांकk(KERN_WARNING
			"%s: tx_timeout, scheduling reset", ndev->name);
		netअगर_stop_queue(ndev);
		priv->reset_task_pending = 1;
		schedule_work(&priv->reset_task);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING
			"%s: tx_timeout, waiting for reset", ndev->name);
	पूर्ण
पूर्ण
