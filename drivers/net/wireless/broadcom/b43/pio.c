<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver

  PIO data transfer

  Copyright (c) 2005-2008 Michael Buesch <m@bues.ch>


*/

#समावेश "b43.h"
#समावेश "pio.h"
#समावेश "dma.h"
#समावेश "main.h"
#समावेश "xmit.h"

#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>


अटल u16 generate_cookie(काष्ठा b43_pio_txqueue *q,
			   काष्ठा b43_pio_txpacket *pack)
अणु
	u16 cookie;

	/* Use the upper 4 bits of the cookie as
	 * PIO controller ID and store the packet index number
	 * in the lower 12 bits.
	 * Note that the cookie must never be 0, as this
	 * is a special value used in RX path.
	 * It can also not be 0xFFFF because that is special
	 * क्रम multicast frames.
	 */
	cookie = (((u16)q->index + 1) << 12);
	cookie |= pack->index;

	वापस cookie;
पूर्ण

अटल
काष्ठा b43_pio_txqueue *parse_cookie(काष्ठा b43_wldev *dev,
				     u16 cookie,
				      काष्ठा b43_pio_txpacket **pack)
अणु
	काष्ठा b43_pio *pio = &dev->pio;
	काष्ठा b43_pio_txqueue *q = शून्य;
	अचिन्हित पूर्णांक pack_index;

	चयन (cookie & 0xF000) अणु
	हाल 0x1000:
		q = pio->tx_queue_AC_BK;
		अवरोध;
	हाल 0x2000:
		q = pio->tx_queue_AC_BE;
		अवरोध;
	हाल 0x3000:
		q = pio->tx_queue_AC_VI;
		अवरोध;
	हाल 0x4000:
		q = pio->tx_queue_AC_VO;
		अवरोध;
	हाल 0x5000:
		q = pio->tx_queue_mcast;
		अवरोध;
	पूर्ण
	अगर (B43_WARN_ON(!q))
		वापस शून्य;
	pack_index = (cookie & 0x0FFF);
	अगर (B43_WARN_ON(pack_index >= ARRAY_SIZE(q->packets)))
		वापस शून्य;
	*pack = &q->packets[pack_index];

	वापस q;
पूर्ण

अटल u16 index_to_pioqueue_base(काष्ठा b43_wldev *dev,
				  अचिन्हित पूर्णांक index)
अणु
	अटल स्थिर u16 bases[] = अणु
		B43_MMIO_PIO_BASE0,
		B43_MMIO_PIO_BASE1,
		B43_MMIO_PIO_BASE2,
		B43_MMIO_PIO_BASE3,
		B43_MMIO_PIO_BASE4,
		B43_MMIO_PIO_BASE5,
		B43_MMIO_PIO_BASE6,
		B43_MMIO_PIO_BASE7,
	पूर्ण;
	अटल स्थिर u16 bases_rev11[] = अणु
		B43_MMIO_PIO11_BASE0,
		B43_MMIO_PIO11_BASE1,
		B43_MMIO_PIO11_BASE2,
		B43_MMIO_PIO11_BASE3,
		B43_MMIO_PIO11_BASE4,
		B43_MMIO_PIO11_BASE5,
	पूर्ण;

	अगर (dev->dev->core_rev >= 11) अणु
		B43_WARN_ON(index >= ARRAY_SIZE(bases_rev11));
		वापस bases_rev11[index];
	पूर्ण
	B43_WARN_ON(index >= ARRAY_SIZE(bases));
	वापस bases[index];
पूर्ण

अटल u16 pio_txqueue_offset(काष्ठा b43_wldev *dev)
अणु
	अगर (dev->dev->core_rev >= 11)
		वापस 0x18;
	वापस 0;
पूर्ण

अटल u16 pio_rxqueue_offset(काष्ठा b43_wldev *dev)
अणु
	अगर (dev->dev->core_rev >= 11)
		वापस 0x38;
	वापस 8;
पूर्ण

अटल काष्ठा b43_pio_txqueue *b43_setup_pioqueue_tx(काष्ठा b43_wldev *dev,
						     अचिन्हित पूर्णांक index)
अणु
	काष्ठा b43_pio_txqueue *q;
	काष्ठा b43_pio_txpacket *p;
	अचिन्हित पूर्णांक i;

	q = kzalloc(माप(*q), GFP_KERNEL);
	अगर (!q)
		वापस शून्य;
	q->dev = dev;
	q->rev = dev->dev->core_rev;
	q->mmio_base = index_to_pioqueue_base(dev, index) +
		       pio_txqueue_offset(dev);
	q->index = index;

	q->मुक्त_packet_slots = B43_PIO_MAX_NR_TXPACKETS;
	अगर (q->rev >= 8) अणु
		q->buffer_size = 1920; //FIXME this स्थिरant is wrong.
	पूर्ण अन्यथा अणु
		q->buffer_size = b43_piotx_पढ़ो16(q, B43_PIO_TXQबफ_मानE);
		q->buffer_size -= 80;
	पूर्ण

	INIT_LIST_HEAD(&q->packets_list);
	क्रम (i = 0; i < ARRAY_SIZE(q->packets); i++) अणु
		p = &(q->packets[i]);
		INIT_LIST_HEAD(&p->list);
		p->index = i;
		p->queue = q;
		list_add(&p->list, &q->packets_list);
	पूर्ण

	वापस q;
पूर्ण

अटल काष्ठा b43_pio_rxqueue *b43_setup_pioqueue_rx(काष्ठा b43_wldev *dev,
						     अचिन्हित पूर्णांक index)
अणु
	काष्ठा b43_pio_rxqueue *q;

	q = kzalloc(माप(*q), GFP_KERNEL);
	अगर (!q)
		वापस शून्य;
	q->dev = dev;
	q->rev = dev->dev->core_rev;
	q->mmio_base = index_to_pioqueue_base(dev, index) +
		       pio_rxqueue_offset(dev);

	/* Enable Direct FIFO RX (PIO) on the engine. */
	b43_dma_direct_fअगरo_rx(dev, index, 1);

	वापस q;
पूर्ण

अटल व्योम b43_pio_cancel_tx_packets(काष्ठा b43_pio_txqueue *q)
अणु
	काष्ठा b43_pio_txpacket *pack;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(q->packets); i++) अणु
		pack = &(q->packets[i]);
		अगर (pack->skb) अणु
			ieee80211_मुक्त_txskb(q->dev->wl->hw, pack->skb);
			pack->skb = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम b43_destroy_pioqueue_tx(काष्ठा b43_pio_txqueue *q,
				    स्थिर अक्षर *name)
अणु
	अगर (!q)
		वापस;
	b43_pio_cancel_tx_packets(q);
	kमुक्त(q);
पूर्ण

अटल व्योम b43_destroy_pioqueue_rx(काष्ठा b43_pio_rxqueue *q,
				    स्थिर अक्षर *name)
अणु
	अगर (!q)
		वापस;
	kमुक्त(q);
पूर्ण

#घोषणा destroy_queue_tx(pio, queue) करो अणु				\
	b43_destroy_pioqueue_tx((pio)->queue, __stringअगरy(queue));	\
	(pio)->queue = शून्य;						\
  पूर्ण जबतक (0)

#घोषणा destroy_queue_rx(pio, queue) करो अणु				\
	b43_destroy_pioqueue_rx((pio)->queue, __stringअगरy(queue));	\
	(pio)->queue = शून्य;						\
  पूर्ण जबतक (0)

व्योम b43_pio_मुक्त(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_pio *pio;

	अगर (!b43_using_pio_transfers(dev))
		वापस;
	pio = &dev->pio;

	destroy_queue_rx(pio, rx_queue);
	destroy_queue_tx(pio, tx_queue_mcast);
	destroy_queue_tx(pio, tx_queue_AC_VO);
	destroy_queue_tx(pio, tx_queue_AC_VI);
	destroy_queue_tx(pio, tx_queue_AC_BE);
	destroy_queue_tx(pio, tx_queue_AC_BK);
पूर्ण

पूर्णांक b43_pio_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_pio *pio = &dev->pio;
	पूर्णांक err = -ENOMEM;

	b43_ग_लिखो32(dev, B43_MMIO_MACCTL, b43_पढ़ो32(dev, B43_MMIO_MACCTL)
		    & ~B43_MACCTL_BE);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_RXPADOFF, 0);

	pio->tx_queue_AC_BK = b43_setup_pioqueue_tx(dev, 0);
	अगर (!pio->tx_queue_AC_BK)
		जाओ out;

	pio->tx_queue_AC_BE = b43_setup_pioqueue_tx(dev, 1);
	अगर (!pio->tx_queue_AC_BE)
		जाओ err_destroy_bk;

	pio->tx_queue_AC_VI = b43_setup_pioqueue_tx(dev, 2);
	अगर (!pio->tx_queue_AC_VI)
		जाओ err_destroy_be;

	pio->tx_queue_AC_VO = b43_setup_pioqueue_tx(dev, 3);
	अगर (!pio->tx_queue_AC_VO)
		जाओ err_destroy_vi;

	pio->tx_queue_mcast = b43_setup_pioqueue_tx(dev, 4);
	अगर (!pio->tx_queue_mcast)
		जाओ err_destroy_vo;

	pio->rx_queue = b43_setup_pioqueue_rx(dev, 0);
	अगर (!pio->rx_queue)
		जाओ err_destroy_mcast;

	b43dbg(dev->wl, "PIO initialized\n");
	err = 0;
out:
	वापस err;

err_destroy_mcast:
	destroy_queue_tx(pio, tx_queue_mcast);
err_destroy_vo:
	destroy_queue_tx(pio, tx_queue_AC_VO);
err_destroy_vi:
	destroy_queue_tx(pio, tx_queue_AC_VI);
err_destroy_be:
	destroy_queue_tx(pio, tx_queue_AC_BE);
err_destroy_bk:
	destroy_queue_tx(pio, tx_queue_AC_BK);
	वापस err;
पूर्ण

/* Static mapping of mac80211's queues (priorities) to b43 PIO queues. */
अटल काष्ठा b43_pio_txqueue *select_queue_by_priority(काष्ठा b43_wldev *dev,
							u8 queue_prio)
अणु
	काष्ठा b43_pio_txqueue *q;

	अगर (dev->qos_enabled) अणु
		/* 0 = highest priority */
		चयन (queue_prio) अणु
		शेष:
			B43_WARN_ON(1);
			fallthrough;
		हाल 0:
			q = dev->pio.tx_queue_AC_VO;
			अवरोध;
		हाल 1:
			q = dev->pio.tx_queue_AC_VI;
			अवरोध;
		हाल 2:
			q = dev->pio.tx_queue_AC_BE;
			अवरोध;
		हाल 3:
			q = dev->pio.tx_queue_AC_BK;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		q = dev->pio.tx_queue_AC_BE;

	वापस q;
पूर्ण

अटल u16 tx_ग_लिखो_2byte_queue(काष्ठा b43_pio_txqueue *q,
				u16 ctl,
				स्थिर व्योम *_data,
				अचिन्हित पूर्णांक data_len)
अणु
	काष्ठा b43_wldev *dev = q->dev;
	काष्ठा b43_wl *wl = dev->wl;
	स्थिर u8 *data = _data;

	ctl |= B43_PIO_TXCTL_WRITELO | B43_PIO_TXCTL_WRITEHI;
	b43_piotx_ग_लिखो16(q, B43_PIO_TXCTL, ctl);

	b43_block_ग_लिखो(dev, data, (data_len & ~1),
			q->mmio_base + B43_PIO_TXDATA,
			माप(u16));
	अगर (data_len & 1) अणु
		u8 *tail = wl->pio_tailspace;
		BUILD_BUG_ON(माप(wl->pio_tailspace) < 2);

		/* Write the last byte. */
		ctl &= ~B43_PIO_TXCTL_WRITEHI;
		b43_piotx_ग_लिखो16(q, B43_PIO_TXCTL, ctl);
		tail[0] = data[data_len - 1];
		tail[1] = 0;
		b43_block_ग_लिखो(dev, tail, 2,
				q->mmio_base + B43_PIO_TXDATA,
				माप(u16));
	पूर्ण

	वापस ctl;
पूर्ण

अटल व्योम pio_tx_frame_2byte_queue(काष्ठा b43_pio_txpacket *pack,
				     स्थिर u8 *hdr, अचिन्हित पूर्णांक hdrlen)
अणु
	काष्ठा b43_pio_txqueue *q = pack->queue;
	स्थिर अक्षर *frame = pack->skb->data;
	अचिन्हित पूर्णांक frame_len = pack->skb->len;
	u16 ctl;

	ctl = b43_piotx_पढ़ो16(q, B43_PIO_TXCTL);
	ctl |= B43_PIO_TXCTL_FREADY;
	ctl &= ~B43_PIO_TXCTL_खातापूर्ण;

	/* Transfer the header data. */
	ctl = tx_ग_लिखो_2byte_queue(q, ctl, hdr, hdrlen);
	/* Transfer the frame data. */
	ctl = tx_ग_लिखो_2byte_queue(q, ctl, frame, frame_len);

	ctl |= B43_PIO_TXCTL_खातापूर्ण;
	b43_piotx_ग_लिखो16(q, B43_PIO_TXCTL, ctl);
पूर्ण

अटल u32 tx_ग_लिखो_4byte_queue(काष्ठा b43_pio_txqueue *q,
				u32 ctl,
				स्थिर व्योम *_data,
				अचिन्हित पूर्णांक data_len)
अणु
	काष्ठा b43_wldev *dev = q->dev;
	काष्ठा b43_wl *wl = dev->wl;
	स्थिर u8 *data = _data;

	ctl |= B43_PIO8_TXCTL_0_7 | B43_PIO8_TXCTL_8_15 |
	       B43_PIO8_TXCTL_16_23 | B43_PIO8_TXCTL_24_31;
	b43_piotx_ग_लिखो32(q, B43_PIO8_TXCTL, ctl);

	b43_block_ग_लिखो(dev, data, (data_len & ~3),
			q->mmio_base + B43_PIO8_TXDATA,
			माप(u32));
	अगर (data_len & 3) अणु
		u8 *tail = wl->pio_tailspace;
		BUILD_BUG_ON(माप(wl->pio_tailspace) < 4);

		स_रखो(tail, 0, 4);
		/* Write the last few bytes. */
		ctl &= ~(B43_PIO8_TXCTL_8_15 | B43_PIO8_TXCTL_16_23 |
			 B43_PIO8_TXCTL_24_31);
		चयन (data_len & 3) अणु
		हाल 3:
			ctl |= B43_PIO8_TXCTL_16_23 | B43_PIO8_TXCTL_8_15;
			tail[0] = data[data_len - 3];
			tail[1] = data[data_len - 2];
			tail[2] = data[data_len - 1];
			अवरोध;
		हाल 2:
			ctl |= B43_PIO8_TXCTL_8_15;
			tail[0] = data[data_len - 2];
			tail[1] = data[data_len - 1];
			अवरोध;
		हाल 1:
			tail[0] = data[data_len - 1];
			अवरोध;
		पूर्ण
		b43_piotx_ग_लिखो32(q, B43_PIO8_TXCTL, ctl);
		b43_block_ग_लिखो(dev, tail, 4,
				q->mmio_base + B43_PIO8_TXDATA,
				माप(u32));
	पूर्ण

	वापस ctl;
पूर्ण

अटल व्योम pio_tx_frame_4byte_queue(काष्ठा b43_pio_txpacket *pack,
				     स्थिर u8 *hdr, अचिन्हित पूर्णांक hdrlen)
अणु
	काष्ठा b43_pio_txqueue *q = pack->queue;
	स्थिर अक्षर *frame = pack->skb->data;
	अचिन्हित पूर्णांक frame_len = pack->skb->len;
	u32 ctl;

	ctl = b43_piotx_पढ़ो32(q, B43_PIO8_TXCTL);
	ctl |= B43_PIO8_TXCTL_FREADY;
	ctl &= ~B43_PIO8_TXCTL_खातापूर्ण;

	/* Transfer the header data. */
	ctl = tx_ग_लिखो_4byte_queue(q, ctl, hdr, hdrlen);
	/* Transfer the frame data. */
	ctl = tx_ग_लिखो_4byte_queue(q, ctl, frame, frame_len);

	ctl |= B43_PIO8_TXCTL_खातापूर्ण;
	b43_piotx_ग_लिखो32(q, B43_PIO_TXCTL, ctl);
पूर्ण

अटल पूर्णांक pio_tx_frame(काष्ठा b43_pio_txqueue *q,
			काष्ठा sk_buff *skb)
अणु
	काष्ठा b43_wldev *dev = q->dev;
	काष्ठा b43_wl *wl = dev->wl;
	काष्ठा b43_pio_txpacket *pack;
	u16 cookie;
	पूर्णांक err;
	अचिन्हित पूर्णांक hdrlen;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा b43_txhdr *txhdr = (काष्ठा b43_txhdr *)wl->pio_scratchspace;

	B43_WARN_ON(list_empty(&q->packets_list));
	pack = list_entry(q->packets_list.next,
			  काष्ठा b43_pio_txpacket, list);

	cookie = generate_cookie(q, pack);
	hdrlen = b43_txhdr_size(dev);
	BUILD_BUG_ON(माप(wl->pio_scratchspace) < माप(काष्ठा b43_txhdr));
	B43_WARN_ON(माप(wl->pio_scratchspace) < hdrlen);
	err = b43_generate_txhdr(dev, (u8 *)txhdr, skb,
				 info, cookie);
	अगर (err)
		वापस err;

	अगर (info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM) अणु
		/* Tell the firmware about the cookie of the last
		 * mcast frame, so it can clear the more-data bit in it. */
		b43_shm_ग_लिखो16(dev, B43_SHM_SHARED,
				B43_SHM_SH_MCASTCOOKIE, cookie);
	पूर्ण

	pack->skb = skb;
	अगर (q->rev >= 8)
		pio_tx_frame_4byte_queue(pack, (स्थिर u8 *)txhdr, hdrlen);
	अन्यथा
		pio_tx_frame_2byte_queue(pack, (स्थिर u8 *)txhdr, hdrlen);

	/* Remove it from the list of available packet slots.
	 * It will be put back when we receive the status report. */
	list_del(&pack->list);

	/* Update the queue statistics. */
	q->buffer_used += roundup(skb->len + hdrlen, 4);
	q->मुक्त_packet_slots -= 1;

	वापस 0;
पूर्ण

पूर्णांक b43_pio_tx(काष्ठा b43_wldev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा b43_pio_txqueue *q;
	काष्ठा ieee80211_hdr *hdr;
	अचिन्हित पूर्णांक hdrlen, total_len;
	पूर्णांक err = 0;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	hdr = (काष्ठा ieee80211_hdr *)skb->data;

	अगर (info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM) अणु
		/* The multicast queue will be sent after the DTIM. */
		q = dev->pio.tx_queue_mcast;
		/* Set the frame More-Data bit. Ucode will clear it
		 * क्रम us on the last frame. */
		hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_MOREDATA);
	पूर्ण अन्यथा अणु
		/* Decide by priority where to put this frame. */
		q = select_queue_by_priority(dev, skb_get_queue_mapping(skb));
	पूर्ण

	hdrlen = b43_txhdr_size(dev);
	total_len = roundup(skb->len + hdrlen, 4);

	अगर (unlikely(total_len > q->buffer_size)) अणु
		err = -ENOBUFS;
		b43dbg(dev->wl, "PIO: TX packet longer than queue.\n");
		जाओ out;
	पूर्ण
	अगर (unlikely(q->मुक्त_packet_slots == 0)) अणु
		err = -ENOBUFS;
		b43warn(dev->wl, "PIO: TX packet overflow.\n");
		जाओ out;
	पूर्ण
	B43_WARN_ON(q->buffer_used > q->buffer_size);

	अगर (total_len > (q->buffer_size - q->buffer_used)) अणु
		/* Not enough memory on the queue. */
		err = -EBUSY;
		ieee80211_stop_queue(dev->wl->hw, skb_get_queue_mapping(skb));
		q->stopped = true;
		जाओ out;
	पूर्ण

	/* Assign the queue number to the ring (अगर not alपढ़ोy करोne beक्रमe)
	 * so TX status handling can use it. The mac80211-queue to b43-queue
	 * mapping is अटल, so we करोn't need to store it per frame. */
	q->queue_prio = skb_get_queue_mapping(skb);

	err = pio_tx_frame(q, skb);
	अगर (unlikely(err == -ENOKEY)) अणु
		/* Drop this packet, as we करोn't have the encryption key
		 * anymore and must not transmit it unencrypted. */
		ieee80211_मुक्त_txskb(dev->wl->hw, skb);
		err = 0;
		जाओ out;
	पूर्ण
	अगर (unlikely(err)) अणु
		b43err(dev->wl, "PIO transmission failure\n");
		जाओ out;
	पूर्ण

	B43_WARN_ON(q->buffer_used > q->buffer_size);
	अगर (((q->buffer_size - q->buffer_used) < roundup(2 + 2 + 6, 4)) ||
	    (q->मुक्त_packet_slots == 0)) अणु
		/* The queue is full. */
		ieee80211_stop_queue(dev->wl->hw, skb_get_queue_mapping(skb));
		q->stopped = true;
	पूर्ण

out:
	वापस err;
पूर्ण

व्योम b43_pio_handle_txstatus(काष्ठा b43_wldev *dev,
			     स्थिर काष्ठा b43_txstatus *status)
अणु
	काष्ठा b43_pio_txqueue *q;
	काष्ठा b43_pio_txpacket *pack = शून्य;
	अचिन्हित पूर्णांक total_len;
	काष्ठा ieee80211_tx_info *info;

	q = parse_cookie(dev, status->cookie, &pack);
	अगर (unlikely(!q))
		वापस;
	B43_WARN_ON(!pack);

	info = IEEE80211_SKB_CB(pack->skb);

	b43_fill_txstatus_report(dev, info, status);

	total_len = pack->skb->len + b43_txhdr_size(dev);
	total_len = roundup(total_len, 4);
	q->buffer_used -= total_len;
	q->मुक्त_packet_slots += 1;

	ieee80211_tx_status(dev->wl->hw, pack->skb);
	pack->skb = शून्य;
	list_add(&pack->list, &q->packets_list);

	अगर (q->stopped) अणु
		ieee80211_wake_queue(dev->wl->hw, q->queue_prio);
		q->stopped = false;
	पूर्ण
पूर्ण

/* Returns whether we should fetch another frame. */
अटल bool pio_rx_frame(काष्ठा b43_pio_rxqueue *q)
अणु
	काष्ठा b43_wldev *dev = q->dev;
	काष्ठा b43_wl *wl = dev->wl;
	u16 len;
	u32 macstat = 0;
	अचिन्हित पूर्णांक i, padding;
	काष्ठा sk_buff *skb;
	स्थिर अक्षर *err_msg = शून्य;
	काष्ठा b43_rxhdr_fw4 *rxhdr =
		(काष्ठा b43_rxhdr_fw4 *)wl->pio_scratchspace;
	माप_प्रकार rxhdr_size = माप(*rxhdr);

	BUILD_BUG_ON(माप(wl->pio_scratchspace) < माप(*rxhdr));
	चयन (dev->fw.hdr_क्रमmat) अणु
	हाल B43_FW_HDR_410:
	हाल B43_FW_HDR_351:
		rxhdr_size -= माप(rxhdr->क्रमmat_598) -
			माप(rxhdr->क्रमmat_351);
		अवरोध;
	हाल B43_FW_HDR_598:
		अवरोध;
	पूर्ण
	स_रखो(rxhdr, 0, rxhdr_size);

	/* Check अगर we have data and रुको क्रम it to get पढ़ोy. */
	अगर (q->rev >= 8) अणु
		u32 ctl;

		ctl = b43_piorx_पढ़ो32(q, B43_PIO8_RXCTL);
		अगर (!(ctl & B43_PIO8_RXCTL_FRAMERDY))
			वापस false;
		b43_piorx_ग_लिखो32(q, B43_PIO8_RXCTL,
				  B43_PIO8_RXCTL_FRAMERDY);
		क्रम (i = 0; i < 10; i++) अणु
			ctl = b43_piorx_पढ़ो32(q, B43_PIO8_RXCTL);
			अगर (ctl & B43_PIO8_RXCTL_DATARDY)
				जाओ data_पढ़ोy;
			udelay(10);
		पूर्ण
	पूर्ण अन्यथा अणु
		u16 ctl;

		ctl = b43_piorx_पढ़ो16(q, B43_PIO_RXCTL);
		अगर (!(ctl & B43_PIO_RXCTL_FRAMERDY))
			वापस false;
		b43_piorx_ग_लिखो16(q, B43_PIO_RXCTL,
				  B43_PIO_RXCTL_FRAMERDY);
		क्रम (i = 0; i < 10; i++) अणु
			ctl = b43_piorx_पढ़ो16(q, B43_PIO_RXCTL);
			अगर (ctl & B43_PIO_RXCTL_DATARDY)
				जाओ data_पढ़ोy;
			udelay(10);
		पूर्ण
	पूर्ण
	b43dbg(q->dev->wl, "PIO RX timed out\n");
	वापस true;
data_पढ़ोy:

	/* Get the preamble (RX header) */
	अगर (q->rev >= 8) अणु
		b43_block_पढ़ो(dev, rxhdr, rxhdr_size,
			       q->mmio_base + B43_PIO8_RXDATA,
			       माप(u32));
	पूर्ण अन्यथा अणु
		b43_block_पढ़ो(dev, rxhdr, rxhdr_size,
			       q->mmio_base + B43_PIO_RXDATA,
			       माप(u16));
	पूर्ण
	/* Sanity checks. */
	len = le16_to_cpu(rxhdr->frame_len);
	अगर (unlikely(len > 0x700)) अणु
		err_msg = "len > 0x700";
		जाओ rx_error;
	पूर्ण
	अगर (unlikely(len == 0)) अणु
		err_msg = "len == 0";
		जाओ rx_error;
	पूर्ण

	चयन (dev->fw.hdr_क्रमmat) अणु
	हाल B43_FW_HDR_598:
		macstat = le32_to_cpu(rxhdr->क्रमmat_598.mac_status);
		अवरोध;
	हाल B43_FW_HDR_410:
	हाल B43_FW_HDR_351:
		macstat = le32_to_cpu(rxhdr->क्रमmat_351.mac_status);
		अवरोध;
	पूर्ण
	अगर (macstat & B43_RX_MAC_FCSERR) अणु
		अगर (!(q->dev->wl->filter_flags & FIF_FCSFAIL)) अणु
			/* Drop frames with failed FCS. */
			err_msg = "Frame FCS error";
			जाओ rx_error;
		पूर्ण
	पूर्ण

	/* We always pad 2 bytes, as that's what upstream code expects
	 * due to the RX-header being 30 bytes. In हाल the frame is
	 * unaligned, we pad another 2 bytes. */
	padding = (macstat & B43_RX_MAC_PADDING) ? 2 : 0;
	skb = dev_alloc_skb(len + padding + 2);
	अगर (unlikely(!skb)) अणु
		err_msg = "Out of memory";
		जाओ rx_error;
	पूर्ण
	skb_reserve(skb, 2);
	skb_put(skb, len + padding);
	अगर (q->rev >= 8) अणु
		b43_block_पढ़ो(dev, skb->data + padding, (len & ~3),
			       q->mmio_base + B43_PIO8_RXDATA,
			       माप(u32));
		अगर (len & 3) अणु
			u8 *tail = wl->pio_tailspace;
			BUILD_BUG_ON(माप(wl->pio_tailspace) < 4);

			/* Read the last few bytes. */
			b43_block_पढ़ो(dev, tail, 4,
				       q->mmio_base + B43_PIO8_RXDATA,
				       माप(u32));
			चयन (len & 3) अणु
			हाल 3:
				skb->data[len + padding - 3] = tail[0];
				skb->data[len + padding - 2] = tail[1];
				skb->data[len + padding - 1] = tail[2];
				अवरोध;
			हाल 2:
				skb->data[len + padding - 2] = tail[0];
				skb->data[len + padding - 1] = tail[1];
				अवरोध;
			हाल 1:
				skb->data[len + padding - 1] = tail[0];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		b43_block_पढ़ो(dev, skb->data + padding, (len & ~1),
			       q->mmio_base + B43_PIO_RXDATA,
			       माप(u16));
		अगर (len & 1) अणु
			u8 *tail = wl->pio_tailspace;
			BUILD_BUG_ON(माप(wl->pio_tailspace) < 2);

			/* Read the last byte. */
			b43_block_पढ़ो(dev, tail, 2,
				       q->mmio_base + B43_PIO_RXDATA,
				       माप(u16));
			skb->data[len + padding - 1] = tail[0];
		पूर्ण
	पूर्ण

	b43_rx(q->dev, skb, rxhdr);

	वापस true;

rx_error:
	अगर (err_msg)
		b43dbg(q->dev->wl, "PIO RX error: %s\n", err_msg);
	अगर (q->rev >= 8)
		b43_piorx_ग_लिखो32(q, B43_PIO8_RXCTL, B43_PIO8_RXCTL_DATARDY);
	अन्यथा
		b43_piorx_ग_लिखो16(q, B43_PIO_RXCTL, B43_PIO_RXCTL_DATARDY);

	वापस true;
पूर्ण

व्योम b43_pio_rx(काष्ठा b43_pio_rxqueue *q)
अणु
	अचिन्हित पूर्णांक count = 0;
	bool stop;

	जबतक (1) अणु
		stop = !pio_rx_frame(q);
		अगर (stop)
			अवरोध;
		cond_resched();
		अगर (WARN_ON_ONCE(++count > 10000))
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम b43_pio_tx_suspend_queue(काष्ठा b43_pio_txqueue *q)
अणु
	अगर (q->rev >= 8) अणु
		b43_piotx_ग_लिखो32(q, B43_PIO8_TXCTL,
				  b43_piotx_पढ़ो32(q, B43_PIO8_TXCTL)
				  | B43_PIO8_TXCTL_SUSPREQ);
	पूर्ण अन्यथा अणु
		b43_piotx_ग_लिखो16(q, B43_PIO_TXCTL,
				  b43_piotx_पढ़ो16(q, B43_PIO_TXCTL)
				  | B43_PIO_TXCTL_SUSPREQ);
	पूर्ण
पूर्ण

अटल व्योम b43_pio_tx_resume_queue(काष्ठा b43_pio_txqueue *q)
अणु
	अगर (q->rev >= 8) अणु
		b43_piotx_ग_लिखो32(q, B43_PIO8_TXCTL,
				  b43_piotx_पढ़ो32(q, B43_PIO8_TXCTL)
				  & ~B43_PIO8_TXCTL_SUSPREQ);
	पूर्ण अन्यथा अणु
		b43_piotx_ग_लिखो16(q, B43_PIO_TXCTL,
				  b43_piotx_पढ़ो16(q, B43_PIO_TXCTL)
				  & ~B43_PIO_TXCTL_SUSPREQ);
	पूर्ण
पूर्ण

व्योम b43_pio_tx_suspend(काष्ठा b43_wldev *dev)
अणु
	b43_घातer_saving_ctl_bits(dev, B43_PS_AWAKE);
	b43_pio_tx_suspend_queue(dev->pio.tx_queue_AC_BK);
	b43_pio_tx_suspend_queue(dev->pio.tx_queue_AC_BE);
	b43_pio_tx_suspend_queue(dev->pio.tx_queue_AC_VI);
	b43_pio_tx_suspend_queue(dev->pio.tx_queue_AC_VO);
	b43_pio_tx_suspend_queue(dev->pio.tx_queue_mcast);
पूर्ण

व्योम b43_pio_tx_resume(काष्ठा b43_wldev *dev)
अणु
	b43_pio_tx_resume_queue(dev->pio.tx_queue_mcast);
	b43_pio_tx_resume_queue(dev->pio.tx_queue_AC_VO);
	b43_pio_tx_resume_queue(dev->pio.tx_queue_AC_VI);
	b43_pio_tx_resume_queue(dev->pio.tx_queue_AC_BE);
	b43_pio_tx_resume_queue(dev->pio.tx_queue_AC_BK);
	b43_घातer_saving_ctl_bits(dev, 0);
पूर्ण
