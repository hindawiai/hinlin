<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43legacy wireless driver

  PIO Transmission

  Copyright (c) 2005 Michael Buesch <m@bues.ch>


*/

#समावेश "b43legacy.h"
#समावेश "pio.h"
#समावेश "main.h"
#समावेश "xmit.h"

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>


अटल व्योम tx_start(काष्ठा b43legacy_pioqueue *queue)
अणु
	b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_TXCTL,
			    B43legacy_PIO_TXCTL_INIT);
पूर्ण

अटल व्योम tx_octet(काष्ठा b43legacy_pioqueue *queue,
		     u8 octet)
अणु
	अगर (queue->need_workarounds) अणु
		b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_TXDATA, octet);
		b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_TXCTL,
				    B43legacy_PIO_TXCTL_WRITELO);
	पूर्ण अन्यथा अणु
		b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_TXCTL,
				    B43legacy_PIO_TXCTL_WRITELO);
		b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_TXDATA, octet);
	पूर्ण
पूर्ण

अटल u16 tx_get_next_word(स्थिर u8 *txhdr,
			    स्थिर u8 *packet,
			    माप_प्रकार txhdr_size,
			    अचिन्हित पूर्णांक *pos)
अणु
	स्थिर u8 *source;
	अचिन्हित पूर्णांक i = *pos;
	u16 ret;

	अगर (i < txhdr_size)
		source = txhdr;
	अन्यथा अणु
		source = packet;
		i -= txhdr_size;
	पूर्ण
	ret = le16_to_cpu(*((__le16 *)(source + i)));
	*pos += 2;

	वापस ret;
पूर्ण

अटल व्योम tx_data(काष्ठा b43legacy_pioqueue *queue,
		    u8 *txhdr,
		    स्थिर u8 *packet,
		    अचिन्हित पूर्णांक octets)
अणु
	u16 data;
	अचिन्हित पूर्णांक i = 0;

	अगर (queue->need_workarounds) अणु
		data = tx_get_next_word(txhdr, packet,
					माप(काष्ठा b43legacy_txhdr_fw3), &i);
		b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_TXDATA, data);
	पूर्ण
	b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_TXCTL,
			    B43legacy_PIO_TXCTL_WRITELO |
			    B43legacy_PIO_TXCTL_WRITEHI);
	जबतक (i < octets - 1) अणु
		data = tx_get_next_word(txhdr, packet,
					माप(काष्ठा b43legacy_txhdr_fw3), &i);
		b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_TXDATA, data);
	पूर्ण
	अगर (octets % 2)
		tx_octet(queue, packet[octets -
			 माप(काष्ठा b43legacy_txhdr_fw3) - 1]);
पूर्ण

अटल व्योम tx_complete(काष्ठा b43legacy_pioqueue *queue,
			काष्ठा sk_buff *skb)
अणु
	अगर (queue->need_workarounds) अणु
		b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_TXDATA,
				    skb->data[skb->len - 1]);
		b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_TXCTL,
				    B43legacy_PIO_TXCTL_WRITELO |
				    B43legacy_PIO_TXCTL_COMPLETE);
	पूर्ण अन्यथा
		b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_TXCTL,
				    B43legacy_PIO_TXCTL_COMPLETE);
पूर्ण

अटल u16 generate_cookie(काष्ठा b43legacy_pioqueue *queue,
			   काष्ठा b43legacy_pio_txpacket *packet)
अणु
	u16 cookie = 0x0000;
	पूर्णांक packetindex;

	/* We use the upper 4 bits क्रम the PIO
	 * controller ID and the lower 12 bits
	 * क्रम the packet index (in the cache).
	 */
	चयन (queue->mmio_base) अणु
	हाल B43legacy_MMIO_PIO1_BASE:
		अवरोध;
	हाल B43legacy_MMIO_PIO2_BASE:
		cookie = 0x1000;
		अवरोध;
	हाल B43legacy_MMIO_PIO3_BASE:
		cookie = 0x2000;
		अवरोध;
	हाल B43legacy_MMIO_PIO4_BASE:
		cookie = 0x3000;
		अवरोध;
	शेष:
		B43legacy_WARN_ON(1);
	पूर्ण
	packetindex = pio_txpacket_getindex(packet);
	B43legacy_WARN_ON(!(((u16)packetindex & 0xF000) == 0x0000));
	cookie |= (u16)packetindex;

	वापस cookie;
पूर्ण

अटल
काष्ठा b43legacy_pioqueue *parse_cookie(काष्ठा b43legacy_wldev *dev,
					u16 cookie,
					काष्ठा b43legacy_pio_txpacket **packet)
अणु
	काष्ठा b43legacy_pio *pio = &dev->pio;
	काष्ठा b43legacy_pioqueue *queue = शून्य;
	पूर्णांक packetindex;

	चयन (cookie & 0xF000) अणु
	हाल 0x0000:
		queue = pio->queue0;
		अवरोध;
	हाल 0x1000:
		queue = pio->queue1;
		अवरोध;
	हाल 0x2000:
		queue = pio->queue2;
		अवरोध;
	हाल 0x3000:
		queue = pio->queue3;
		अवरोध;
	शेष:
		B43legacy_WARN_ON(1);
	पूर्ण
	packetindex = (cookie & 0x0FFF);
	B43legacy_WARN_ON(!(packetindex >= 0 && packetindex
			  < B43legacy_PIO_MAXTXPACKETS));
	*packet = &(queue->tx_packets_cache[packetindex]);

	वापस queue;
पूर्ण

जोड़ txhdr_जोड़ अणु
	काष्ठा b43legacy_txhdr_fw3 txhdr_fw3;
पूर्ण;

अटल पूर्णांक pio_tx_ग_लिखो_fragment(काष्ठा b43legacy_pioqueue *queue,
				  काष्ठा sk_buff *skb,
				  काष्ठा b43legacy_pio_txpacket *packet,
				  माप_प्रकार txhdr_size)
अणु
	जोड़ txhdr_जोड़ txhdr_data;
	u8 *txhdr = शून्य;
	अचिन्हित पूर्णांक octets;
	पूर्णांक err;

	txhdr = (u8 *)(&txhdr_data.txhdr_fw3);

	B43legacy_WARN_ON(skb_shinfo(skb)->nr_frags != 0);
	err = b43legacy_generate_txhdr(queue->dev,
				 txhdr, skb->data, skb->len,
				 IEEE80211_SKB_CB(skb),
				 generate_cookie(queue, packet));
	अगर (err)
		वापस err;

	tx_start(queue);
	octets = skb->len + txhdr_size;
	अगर (queue->need_workarounds)
		octets--;
	tx_data(queue, txhdr, (u8 *)skb->data, octets);
	tx_complete(queue, skb);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_txpacket(काष्ठा b43legacy_pio_txpacket *packet,
			  पूर्णांक irq_context)
अणु
	काष्ठा b43legacy_pioqueue *queue = packet->queue;

	अगर (packet->skb) अणु
		अगर (irq_context)
			dev_kमुक्त_skb_irq(packet->skb);
		अन्यथा
			dev_kमुक्त_skb(packet->skb);
	पूर्ण
	list_move(&packet->list, &queue->txमुक्त);
	queue->nr_txमुक्त++;
पूर्ण

अटल पूर्णांक pio_tx_packet(काष्ठा b43legacy_pio_txpacket *packet)
अणु
	काष्ठा b43legacy_pioqueue *queue = packet->queue;
	काष्ठा sk_buff *skb = packet->skb;
	u16 octets;
	पूर्णांक err;

	octets = (u16)skb->len + माप(काष्ठा b43legacy_txhdr_fw3);
	अगर (queue->tx_devq_size < octets) अणु
		b43legacywarn(queue->dev->wl, "PIO queue too small. "
			"Dropping packet.\n");
		/* Drop it silently (वापस success) */
		मुक्त_txpacket(packet, 1);
		वापस 0;
	पूर्ण
	B43legacy_WARN_ON(queue->tx_devq_packets >
			  B43legacy_PIO_MAXTXDEVQPACKETS);
	B43legacy_WARN_ON(queue->tx_devq_used > queue->tx_devq_size);
	/* Check अगर there is sufficient मुक्त space on the device
	 * TX queue. If not, वापस and let the TX tasklet
	 * retry later.
	 */
	अगर (queue->tx_devq_packets == B43legacy_PIO_MAXTXDEVQPACKETS)
		वापस -EBUSY;
	अगर (queue->tx_devq_used + octets > queue->tx_devq_size)
		वापस -EBUSY;
	/* Now poke the device. */
	err = pio_tx_ग_लिखो_fragment(queue, skb, packet,
			      माप(काष्ठा b43legacy_txhdr_fw3));
	अगर (unlikely(err == -ENOKEY)) अणु
		/* Drop this packet, as we करोn't have the encryption key
		 * anymore and must not transmit it unencrypted. */
		मुक्त_txpacket(packet, 1);
		वापस 0;
	पूर्ण

	/* Account क्रम the packet size.
	 * (We must not overflow the device TX queue)
	 */
	queue->tx_devq_packets++;
	queue->tx_devq_used += octets;

	/* Transmission started, everything ok, move the
	 * packet to the txrunning list.
	 */
	list_move_tail(&packet->list, &queue->txrunning);

	वापस 0;
पूर्ण

अटल व्योम tx_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा b43legacy_pioqueue *queue = from_tasklet(queue, t, txtask);
	काष्ठा b43legacy_wldev *dev = queue->dev;
	अचिन्हित दीर्घ flags;
	काष्ठा b43legacy_pio_txpacket *packet, *पंचांगp_packet;
	पूर्णांक err;
	u16 txctl;

	spin_lock_irqsave(&dev->wl->irq_lock, flags);
	अगर (queue->tx_frozen)
		जाओ out_unlock;
	txctl = b43legacy_pio_पढ़ो(queue, B43legacy_PIO_TXCTL);
	अगर (txctl & B43legacy_PIO_TXCTL_SUSPEND)
		जाओ out_unlock;

	list_क्रम_each_entry_safe(packet, पंचांगp_packet, &queue->txqueue, list) अणु
		/* Try to transmit the packet. This can fail, अगर
		 * the device queue is full. In हाल of failure, the
		 * packet is left in the txqueue.
		 * If transmission succeed, the packet is moved to txrunning.
		 * If it is impossible to transmit the packet, it
		 * is dropped.
		 */
		err = pio_tx_packet(packet);
		अगर (err)
			अवरोध;
	पूर्ण
out_unlock:
	spin_unlock_irqrestore(&dev->wl->irq_lock, flags);
पूर्ण

अटल व्योम setup_txqueues(काष्ठा b43legacy_pioqueue *queue)
अणु
	काष्ठा b43legacy_pio_txpacket *packet;
	पूर्णांक i;

	queue->nr_txमुक्त = B43legacy_PIO_MAXTXPACKETS;
	क्रम (i = 0; i < B43legacy_PIO_MAXTXPACKETS; i++) अणु
		packet = &(queue->tx_packets_cache[i]);

		packet->queue = queue;
		INIT_LIST_HEAD(&packet->list);

		list_add(&packet->list, &queue->txमुक्त);
	पूर्ण
पूर्ण

अटल
काष्ठा b43legacy_pioqueue *b43legacy_setup_pioqueue(काष्ठा b43legacy_wldev *dev,
						    u16 pio_mmio_base)
अणु
	काष्ठा b43legacy_pioqueue *queue;
	u32 value;
	u16 qsize;

	queue = kzalloc(माप(*queue), GFP_KERNEL);
	अगर (!queue)
		जाओ out;

	queue->dev = dev;
	queue->mmio_base = pio_mmio_base;
	queue->need_workarounds = (dev->dev->id.revision < 3);

	INIT_LIST_HEAD(&queue->txमुक्त);
	INIT_LIST_HEAD(&queue->txqueue);
	INIT_LIST_HEAD(&queue->txrunning);
	tasklet_setup(&queue->txtask, tx_tasklet);

	value = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	value &= ~B43legacy_MACCTL_BE;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, value);

	qsize = b43legacy_पढ़ो16(dev, queue->mmio_base
				 + B43legacy_PIO_TXQबफ_मानE);
	अगर (qsize == 0) अणु
		b43legacyerr(dev->wl, "This card does not support PIO "
		       "operation mode. Please use DMA mode "
		       "(module parameter pio=0).\n");
		जाओ err_मुक्तqueue;
	पूर्ण
	अगर (qsize <= B43legacy_PIO_TXQADJUST) अणु
		b43legacyerr(dev->wl, "PIO tx device-queue too small (%u)\n",
		       qsize);
		जाओ err_मुक्तqueue;
	पूर्ण
	qsize -= B43legacy_PIO_TXQADJUST;
	queue->tx_devq_size = qsize;

	setup_txqueues(queue);

out:
	वापस queue;

err_मुक्तqueue:
	kमुक्त(queue);
	queue = शून्य;
	जाओ out;
पूर्ण

अटल व्योम cancel_transfers(काष्ठा b43legacy_pioqueue *queue)
अणु
	काष्ठा b43legacy_pio_txpacket *packet, *पंचांगp_packet;

	tasklet_समाप्त(&queue->txtask);

	list_क्रम_each_entry_safe(packet, पंचांगp_packet, &queue->txrunning, list)
		मुक्त_txpacket(packet, 0);
	list_क्रम_each_entry_safe(packet, पंचांगp_packet, &queue->txqueue, list)
		मुक्त_txpacket(packet, 0);
पूर्ण

अटल व्योम b43legacy_destroy_pioqueue(काष्ठा b43legacy_pioqueue *queue)
अणु
	अगर (!queue)
		वापस;

	cancel_transfers(queue);
	kमुक्त(queue);
पूर्ण

व्योम b43legacy_pio_मुक्त(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_pio *pio;

	अगर (!b43legacy_using_pio(dev))
		वापस;
	pio = &dev->pio;

	b43legacy_destroy_pioqueue(pio->queue3);
	pio->queue3 = शून्य;
	b43legacy_destroy_pioqueue(pio->queue2);
	pio->queue2 = शून्य;
	b43legacy_destroy_pioqueue(pio->queue1);
	pio->queue1 = शून्य;
	b43legacy_destroy_pioqueue(pio->queue0);
	pio->queue0 = शून्य;
पूर्ण

पूर्णांक b43legacy_pio_init(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_pio *pio = &dev->pio;
	काष्ठा b43legacy_pioqueue *queue;
	पूर्णांक err = -ENOMEM;

	queue = b43legacy_setup_pioqueue(dev, B43legacy_MMIO_PIO1_BASE);
	अगर (!queue)
		जाओ out;
	pio->queue0 = queue;

	queue = b43legacy_setup_pioqueue(dev, B43legacy_MMIO_PIO2_BASE);
	अगर (!queue)
		जाओ err_destroy0;
	pio->queue1 = queue;

	queue = b43legacy_setup_pioqueue(dev, B43legacy_MMIO_PIO3_BASE);
	अगर (!queue)
		जाओ err_destroy1;
	pio->queue2 = queue;

	queue = b43legacy_setup_pioqueue(dev, B43legacy_MMIO_PIO4_BASE);
	अगर (!queue)
		जाओ err_destroy2;
	pio->queue3 = queue;

	अगर (dev->dev->id.revision < 3)
		dev->irq_mask |= B43legacy_IRQ_PIO_WORKAROUND;

	b43legacydbg(dev->wl, "PIO initialized\n");
	err = 0;
out:
	वापस err;

err_destroy2:
	b43legacy_destroy_pioqueue(pio->queue2);
	pio->queue2 = शून्य;
err_destroy1:
	b43legacy_destroy_pioqueue(pio->queue1);
	pio->queue1 = शून्य;
err_destroy0:
	b43legacy_destroy_pioqueue(pio->queue0);
	pio->queue0 = शून्य;
	जाओ out;
पूर्ण

पूर्णांक b43legacy_pio_tx(काष्ठा b43legacy_wldev *dev,
		     काष्ठा sk_buff *skb)
अणु
	काष्ठा b43legacy_pioqueue *queue = dev->pio.queue1;
	काष्ठा b43legacy_pio_txpacket *packet;

	B43legacy_WARN_ON(queue->tx_suspended);
	B43legacy_WARN_ON(list_empty(&queue->txमुक्त));

	packet = list_entry(queue->txमुक्त.next, काष्ठा b43legacy_pio_txpacket,
			    list);
	packet->skb = skb;

	list_move_tail(&packet->list, &queue->txqueue);
	queue->nr_txमुक्त--;
	B43legacy_WARN_ON(queue->nr_txमुक्त >= B43legacy_PIO_MAXTXPACKETS);

	tasklet_schedule(&queue->txtask);

	वापस 0;
पूर्ण

व्योम b43legacy_pio_handle_txstatus(काष्ठा b43legacy_wldev *dev,
				   स्थिर काष्ठा b43legacy_txstatus *status)
अणु
	काष्ठा b43legacy_pioqueue *queue;
	काष्ठा b43legacy_pio_txpacket *packet;
	काष्ठा ieee80211_tx_info *info;
	पूर्णांक retry_limit;

	queue = parse_cookie(dev, status->cookie, &packet);
	B43legacy_WARN_ON(!queue);

	अगर (!packet->skb)
		वापस;

	queue->tx_devq_packets--;
	queue->tx_devq_used -= (packet->skb->len +
				माप(काष्ठा b43legacy_txhdr_fw3));

	info = IEEE80211_SKB_CB(packet->skb);

	/* preserve the confiured retry limit beक्रमe clearing the status
	 * The xmit function has overwritten the rc's value with the actual
	 * retry limit करोne by the hardware */
	retry_limit = info->status.rates[0].count;
	ieee80211_tx_info_clear_status(info);

	अगर (status->acked)
		info->flags |= IEEE80211_TX_STAT_ACK;

	अगर (status->rts_count > dev->wl->hw->conf.लघु_frame_max_tx_count) अणु
		/*
		 * If the लघु retries (RTS, not data frame) have exceeded
		 * the limit, the hw will not have tried the selected rate,
		 * but will have used the fallback rate instead.
		 * Don't let the rate control count attempts क्रम the selected
		 * rate in this हाल, otherwise the statistics will be off.
		 */
		info->status.rates[0].count = 0;
		info->status.rates[1].count = status->frame_count;
	पूर्ण अन्यथा अणु
		अगर (status->frame_count > retry_limit) अणु
			info->status.rates[0].count = retry_limit;
			info->status.rates[1].count = status->frame_count -
					retry_limit;

		पूर्ण अन्यथा अणु
			info->status.rates[0].count = status->frame_count;
			info->status.rates[1].idx = -1;
		पूर्ण
	पूर्ण
	ieee80211_tx_status_irqsafe(dev->wl->hw, packet->skb);
	packet->skb = शून्य;

	मुक्त_txpacket(packet, 1);
	/* If there are packets on the txqueue, poke the tasklet
	 * to transmit them.
	 */
	अगर (!list_empty(&queue->txqueue))
		tasklet_schedule(&queue->txtask);
पूर्ण

अटल व्योम pio_rx_error(काष्ठा b43legacy_pioqueue *queue,
			 पूर्णांक clear_buffers,
			 स्थिर अक्षर *error)
अणु
	पूर्णांक i;

	b43legacyerr(queue->dev->wl, "PIO RX error: %s\n", error);
	b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_RXCTL,
			    B43legacy_PIO_RXCTL_READY);
	अगर (clear_buffers) अणु
		B43legacy_WARN_ON(queue->mmio_base != B43legacy_MMIO_PIO1_BASE);
		क्रम (i = 0; i < 15; i++) अणु
			/* Dummy पढ़ो. */
			b43legacy_pio_पढ़ो(queue, B43legacy_PIO_RXDATA);
		पूर्ण
	पूर्ण
पूर्ण

व्योम b43legacy_pio_rx(काष्ठा b43legacy_pioqueue *queue)
अणु
	__le16 preamble[21] = अणु 0 पूर्ण;
	काष्ठा b43legacy_rxhdr_fw3 *rxhdr;
	u16 पंचांगp;
	u16 len;
	u16 macstat;
	पूर्णांक i;
	पूर्णांक preamble_पढ़ोwords;
	काष्ठा sk_buff *skb;

	पंचांगp = b43legacy_pio_पढ़ो(queue, B43legacy_PIO_RXCTL);
	अगर (!(पंचांगp & B43legacy_PIO_RXCTL_DATAAVAILABLE))
		वापस;
	b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_RXCTL,
			    B43legacy_PIO_RXCTL_DATAAVAILABLE);

	क्रम (i = 0; i < 10; i++) अणु
		पंचांगp = b43legacy_pio_पढ़ो(queue, B43legacy_PIO_RXCTL);
		अगर (पंचांगp & B43legacy_PIO_RXCTL_READY)
			जाओ data_पढ़ोy;
		udelay(10);
	पूर्ण
	b43legacydbg(queue->dev->wl, "PIO RX timed out\n");
	वापस;
data_पढ़ोy:

	len = b43legacy_pio_पढ़ो(queue, B43legacy_PIO_RXDATA);
	अगर (unlikely(len > 0x700)) अणु
		pio_rx_error(queue, 0, "len > 0x700");
		वापस;
	पूर्ण
	अगर (unlikely(len == 0 && queue->mmio_base !=
		     B43legacy_MMIO_PIO4_BASE)) अणु
		pio_rx_error(queue, 0, "len == 0");
		वापस;
	पूर्ण
	preamble[0] = cpu_to_le16(len);
	अगर (queue->mmio_base == B43legacy_MMIO_PIO4_BASE)
		preamble_पढ़ोwords = 14 / माप(u16);
	अन्यथा
		preamble_पढ़ोwords = 18 / माप(u16);
	क्रम (i = 0; i < preamble_पढ़ोwords; i++) अणु
		पंचांगp = b43legacy_pio_पढ़ो(queue, B43legacy_PIO_RXDATA);
		preamble[i + 1] = cpu_to_le16(पंचांगp);
	पूर्ण
	rxhdr = (काष्ठा b43legacy_rxhdr_fw3 *)preamble;
	macstat = le16_to_cpu(rxhdr->mac_status);
	अगर (macstat & B43legacy_RX_MAC_FCSERR) अणु
		pio_rx_error(queue,
			     (queue->mmio_base == B43legacy_MMIO_PIO1_BASE),
			     "Frame FCS error");
		वापस;
	पूर्ण
	अगर (queue->mmio_base == B43legacy_MMIO_PIO4_BASE) अणु
		/* We received an xmit status. */
		काष्ठा b43legacy_hwtxstatus *hw;

		hw = (काष्ठा b43legacy_hwtxstatus *)(preamble + 1);
		b43legacy_handle_hwtxstatus(queue->dev, hw);

		वापस;
	पूर्ण

	skb = dev_alloc_skb(len);
	अगर (unlikely(!skb)) अणु
		pio_rx_error(queue, 1, "OOM");
		वापस;
	पूर्ण
	skb_put(skb, len);
	क्रम (i = 0; i < len - 1; i += 2) अणु
		पंचांगp = b43legacy_pio_पढ़ो(queue, B43legacy_PIO_RXDATA);
		*((__le16 *)(skb->data + i)) = cpu_to_le16(पंचांगp);
	पूर्ण
	अगर (len % 2) अणु
		पंचांगp = b43legacy_pio_पढ़ो(queue, B43legacy_PIO_RXDATA);
		skb->data[len - 1] = (पंचांगp & 0x00FF);
	पूर्ण
	b43legacy_rx(queue->dev, skb, rxhdr);
पूर्ण

व्योम b43legacy_pio_tx_suspend(काष्ठा b43legacy_pioqueue *queue)
अणु
	b43legacy_घातer_saving_ctl_bits(queue->dev, -1, 1);
	b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_TXCTL,
			    b43legacy_pio_पढ़ो(queue, B43legacy_PIO_TXCTL)
			    | B43legacy_PIO_TXCTL_SUSPEND);
पूर्ण

व्योम b43legacy_pio_tx_resume(काष्ठा b43legacy_pioqueue *queue)
अणु
	b43legacy_pio_ग_लिखो(queue, B43legacy_PIO_TXCTL,
			    b43legacy_pio_पढ़ो(queue, B43legacy_PIO_TXCTL)
			    & ~B43legacy_PIO_TXCTL_SUSPEND);
	b43legacy_घातer_saving_ctl_bits(queue->dev, -1, -1);
	tasklet_schedule(&queue->txtask);
पूर्ण

व्योम b43legacy_pio_मुक्तze_txqueues(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_pio *pio;

	B43legacy_WARN_ON(!b43legacy_using_pio(dev));
	pio = &dev->pio;
	pio->queue0->tx_frozen = 1;
	pio->queue1->tx_frozen = 1;
	pio->queue2->tx_frozen = 1;
	pio->queue3->tx_frozen = 1;
पूर्ण

व्योम b43legacy_pio_thaw_txqueues(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_pio *pio;

	B43legacy_WARN_ON(!b43legacy_using_pio(dev));
	pio = &dev->pio;
	pio->queue0->tx_frozen = 0;
	pio->queue1->tx_frozen = 0;
	pio->queue2->tx_frozen = 0;
	pio->queue3->tx_frozen = 0;
	अगर (!list_empty(&pio->queue0->txqueue))
		tasklet_schedule(&pio->queue0->txtask);
	अगर (!list_empty(&pio->queue1->txqueue))
		tasklet_schedule(&pio->queue1->txtask);
	अगर (!list_empty(&pio->queue2->txqueue))
		tasklet_schedule(&pio->queue2->txtask);
	अगर (!list_empty(&pio->queue3->txqueue))
		tasklet_schedule(&pio->queue3->txtask);
पूर्ण
