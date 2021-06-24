<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#समावेश "mt7601u.h"
#समावेश "dma.h"
#समावेश "usb.h"
#समावेश "trace.h"

अटल पूर्णांक mt7601u_submit_rx_buf(काष्ठा mt7601u_dev *dev,
				 काष्ठा mt7601u_dma_buf_rx *e, gfp_t gfp);

अटल अचिन्हित पूर्णांक ieee80211_get_hdrlen_from_buf(स्थिर u8 *data, अचिन्हित len)
अणु
	स्थिर काष्ठा ieee80211_hdr *hdr = (स्थिर काष्ठा ieee80211_hdr *)data;
	अचिन्हित पूर्णांक hdrlen;

	अगर (unlikely(len < 10))
		वापस 0;
	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	अगर (unlikely(hdrlen > len))
		वापस 0;
	वापस hdrlen;
पूर्ण

अटल काष्ठा sk_buff *
mt7601u_rx_skb_from_seg(काष्ठा mt7601u_dev *dev, काष्ठा mt7601u_rxwi *rxwi,
			व्योम *data, u32 seg_len, u32 truesize, काष्ठा page *p)
अणु
	काष्ठा sk_buff *skb;
	u32 true_len, hdr_len = 0, copy, frag;

	skb = alloc_skb(p ? 128 : seg_len, GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;

	true_len = mt76_mac_process_rx(dev, skb, data, rxwi);
	अगर (!true_len || true_len > seg_len)
		जाओ bad_frame;

	hdr_len = ieee80211_get_hdrlen_from_buf(data, true_len);
	अगर (!hdr_len)
		जाओ bad_frame;

	अगर (rxwi->rxinfo & cpu_to_le32(MT_RXINFO_L2PAD)) अणु
		skb_put_data(skb, data, hdr_len);

		data += hdr_len + 2;
		true_len -= hdr_len;
		hdr_len = 0;
	पूर्ण

	/* If not करोing paged RX allocated skb will always have enough space */
	copy = (true_len <= skb_tailroom(skb)) ? true_len : hdr_len + 8;
	frag = true_len - copy;

	skb_put_data(skb, data, copy);
	data += copy;

	अगर (frag) अणु
		skb_add_rx_frag(skb, 0, p, data - page_address(p),
				frag, truesize);
		get_page(p);
	पूर्ण

	वापस skb;

bad_frame:
	dev_err_ratelimited(dev->dev, "Error: incorrect frame len:%u hdr:%u\n",
			    true_len, hdr_len);
	dev_kमुक्त_skb(skb);
	वापस शून्य;
पूर्ण

अटल व्योम mt7601u_rx_process_seg(काष्ठा mt7601u_dev *dev, u8 *data,
				   u32 seg_len, काष्ठा page *p,
				   काष्ठा list_head *list)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा mt7601u_rxwi *rxwi;
	u32 fce_info, truesize = seg_len;

	/* DMA_INFO field at the beginning of the segment contains only some of
	 * the inक्रमmation, we need to पढ़ो the FCE descriptor from the end.
	 */
	fce_info = get_unaligned_le32(data + seg_len - MT_FCE_INFO_LEN);
	seg_len -= MT_FCE_INFO_LEN;

	data += MT_DMA_HDR_LEN;
	seg_len -= MT_DMA_HDR_LEN;

	rxwi = (काष्ठा mt7601u_rxwi *) data;
	data += माप(काष्ठा mt7601u_rxwi);
	seg_len -= माप(काष्ठा mt7601u_rxwi);

	अगर (unlikely(rxwi->zero[0] || rxwi->zero[1] || rxwi->zero[2]))
		dev_err_once(dev->dev, "Error: RXWI zero fields are set\n");
	अगर (unlikely(FIELD_GET(MT_RXD_INFO_TYPE, fce_info)))
		dev_err_once(dev->dev, "Error: RX path seen a non-pkt urb\n");

	trace_mt_rx(dev, rxwi, fce_info);

	skb = mt7601u_rx_skb_from_seg(dev, rxwi, data, seg_len, truesize, p);
	अगर (!skb)
		वापस;

	local_bh_disable();
	rcu_पढ़ो_lock();

	ieee80211_rx_list(dev->hw, शून्य, skb, list);

	rcu_पढ़ो_unlock();
	local_bh_enable();
पूर्ण

अटल u16 mt7601u_rx_next_seg_len(u8 *data, u32 data_len)
अणु
	u32 min_seg_len = MT_DMA_HDR_LEN + MT_RX_INFO_LEN +
		माप(काष्ठा mt7601u_rxwi) + MT_FCE_INFO_LEN;
	u16 dma_len = get_unaligned_le16(data);

	अगर (data_len < min_seg_len ||
	    WARN_ON_ONCE(!dma_len) ||
	    WARN_ON_ONCE(dma_len + MT_DMA_HDRS > data_len) ||
	    WARN_ON_ONCE(dma_len & 0x3))
		वापस 0;

	वापस MT_DMA_HDRS + dma_len;
पूर्ण

अटल व्योम
mt7601u_rx_process_entry(काष्ठा mt7601u_dev *dev, काष्ठा mt7601u_dma_buf_rx *e)
अणु
	u32 seg_len, data_len = e->urb->actual_length;
	u8 *data = page_address(e->p);
	काष्ठा page *new_p = शून्य;
	LIST_HEAD(list);
	पूर्णांक cnt = 0;

	अगर (!test_bit(MT7601U_STATE_INITIALIZED, &dev->state))
		वापस;

	/* Copy अगर there is very little data in the buffer. */
	अगर (data_len > 512)
		new_p = dev_alloc_pages(MT_RX_ORDER);

	जबतक ((seg_len = mt7601u_rx_next_seg_len(data, data_len))) अणु
		mt7601u_rx_process_seg(dev, data, seg_len,
				       new_p ? e->p : शून्य, &list);

		data_len -= seg_len;
		data += seg_len;
		cnt++;
	पूर्ण

	अगर (cnt > 1)
		trace_mt_rx_dma_aggr(dev, cnt, !!new_p);

	netअगर_receive_skb_list(&list);

	अगर (new_p) अणु
		/* we have one extra ref from the allocator */
		put_page(e->p);
		e->p = new_p;
	पूर्ण
पूर्ण

अटल काष्ठा mt7601u_dma_buf_rx *
mt7601u_rx_get_pending_entry(काष्ठा mt7601u_dev *dev)
अणु
	काष्ठा mt7601u_rx_queue *q = &dev->rx_q;
	काष्ठा mt7601u_dma_buf_rx *buf = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->rx_lock, flags);

	अगर (!q->pending)
		जाओ out;

	buf = &q->e[q->start];
	q->pending--;
	q->start = (q->start + 1) % q->entries;
out:
	spin_unlock_irqrestore(&dev->rx_lock, flags);

	वापस buf;
पूर्ण

अटल व्योम mt7601u_complete_rx(काष्ठा urb *urb)
अणु
	काष्ठा mt7601u_dev *dev = urb->context;
	काष्ठा mt7601u_rx_queue *q = &dev->rx_q;
	अचिन्हित दीर्घ flags;

	/* करो no schedule rx tasklet अगर urb has been unlinked
	 * or the device has been हटाओd
	 */
	चयन (urb->status) अणु
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
	हाल -ENOENT:
	हाल -EPROTO:
		वापस;
	शेष:
		dev_err_ratelimited(dev->dev, "rx urb failed: %d\n",
				    urb->status);
		fallthrough;
	हाल 0:
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&dev->rx_lock, flags);
	अगर (WARN_ONCE(q->e[q->end].urb != urb, "RX urb mismatch"))
		जाओ out;

	q->end = (q->end + 1) % q->entries;
	q->pending++;
	tasklet_schedule(&dev->rx_tasklet);
out:
	spin_unlock_irqrestore(&dev->rx_lock, flags);
पूर्ण

अटल व्योम mt7601u_rx_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mt7601u_dev *dev = from_tasklet(dev, t, rx_tasklet);
	काष्ठा mt7601u_dma_buf_rx *e;

	जबतक ((e = mt7601u_rx_get_pending_entry(dev))) अणु
		अगर (e->urb->status)
			जारी;

		mt7601u_rx_process_entry(dev, e);
		mt7601u_submit_rx_buf(dev, e, GFP_ATOMIC);
	पूर्ण
पूर्ण

अटल व्योम mt7601u_complete_tx(काष्ठा urb *urb)
अणु
	काष्ठा mt7601u_tx_queue *q = urb->context;
	काष्ठा mt7601u_dev *dev = q->dev;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	चयन (urb->status) अणु
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
	हाल -ENOENT:
	हाल -EPROTO:
		वापस;
	शेष:
		dev_err_ratelimited(dev->dev, "tx urb failed: %d\n",
				    urb->status);
		fallthrough;
	हाल 0:
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&dev->tx_lock, flags);
	अगर (WARN_ONCE(q->e[q->start].urb != urb, "TX urb mismatch"))
		जाओ out;

	skb = q->e[q->start].skb;
	q->e[q->start].skb = शून्य;
	trace_mt_tx_dma_करोne(dev, skb);

	__skb_queue_tail(&dev->tx_skb_करोne, skb);
	tasklet_schedule(&dev->tx_tasklet);

	अगर (q->used == q->entries - q->entries / 8)
		ieee80211_wake_queue(dev->hw, skb_get_queue_mapping(skb));

	q->start = (q->start + 1) % q->entries;
	q->used--;
out:
	spin_unlock_irqrestore(&dev->tx_lock, flags);
पूर्ण

अटल व्योम mt7601u_tx_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mt7601u_dev *dev = from_tasklet(dev, t, tx_tasklet);
	काष्ठा sk_buff_head skbs;
	अचिन्हित दीर्घ flags;

	__skb_queue_head_init(&skbs);

	spin_lock_irqsave(&dev->tx_lock, flags);

	set_bit(MT7601U_STATE_MORE_STATS, &dev->state);
	अगर (!test_and_set_bit(MT7601U_STATE_READING_STATS, &dev->state))
		queue_delayed_work(dev->stat_wq, &dev->stat_work,
				   msecs_to_jअगरfies(10));

	skb_queue_splice_init(&dev->tx_skb_करोne, &skbs);

	spin_unlock_irqrestore(&dev->tx_lock, flags);

	जबतक (!skb_queue_empty(&skbs)) अणु
		काष्ठा sk_buff *skb = __skb_dequeue(&skbs);

		mt7601u_tx_status(dev, skb);
	पूर्ण
पूर्ण

अटल पूर्णांक mt7601u_dma_submit_tx(काष्ठा mt7601u_dev *dev,
				 काष्ठा sk_buff *skb, u8 ep)
अणु
	काष्ठा usb_device *usb_dev = mt7601u_to_usb_dev(dev);
	अचिन्हित snd_pipe = usb_sndbulkpipe(usb_dev, dev->out_eps[ep]);
	काष्ठा mt7601u_dma_buf_tx *e;
	काष्ठा mt7601u_tx_queue *q = &dev->tx_q[ep];
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&dev->tx_lock, flags);

	अगर (WARN_ON(q->entries <= q->used)) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	e = &q->e[q->end];
	usb_fill_bulk_urb(e->urb, usb_dev, snd_pipe, skb->data, skb->len,
			  mt7601u_complete_tx, q);
	ret = usb_submit_urb(e->urb, GFP_ATOMIC);
	अगर (ret) अणु
		/* Special-handle ENODEV from TX urb submission because it will
		 * often be the first ENODEV we see after device is हटाओd.
		 */
		अगर (ret == -ENODEV)
			set_bit(MT7601U_STATE_REMOVED, &dev->state);
		अन्यथा
			dev_err(dev->dev, "Error: TX urb submit failed:%d\n",
				ret);
		जाओ out;
	पूर्ण

	q->end = (q->end + 1) % q->entries;
	q->used++;
	e->skb = skb;

	अगर (q->used >= q->entries)
		ieee80211_stop_queue(dev->hw, skb_get_queue_mapping(skb));
out:
	spin_unlock_irqrestore(&dev->tx_lock, flags);

	वापस ret;
पूर्ण

/* Map hardware Q to USB endpoपूर्णांक number */
अटल u8 q2ep(u8 qid)
अणु
	/* TODO: take management packets to queue 5 */
	वापस qid + 1;
पूर्ण

/* Map USB endpoपूर्णांक number to Q id in the DMA engine */
अटल क्रमागत mt76_qsel ep2dmaq(u8 ep)
अणु
	अगर (ep == 5)
		वापस MT_QSEL_MGMT;
	वापस MT_QSEL_EDCA;
पूर्ण

पूर्णांक mt7601u_dma_enqueue_tx(काष्ठा mt7601u_dev *dev, काष्ठा sk_buff *skb,
			   काष्ठा mt76_wcid *wcid, पूर्णांक hw_q)
अणु
	u8 ep = q2ep(hw_q);
	u32 dma_flags;
	पूर्णांक ret;

	dma_flags = MT_TXD_PKT_INFO_80211;
	अगर (wcid->hw_key_idx == 0xff)
		dma_flags |= MT_TXD_PKT_INFO_WIV;

	ret = mt7601u_dma_skb_wrap_pkt(skb, ep2dmaq(ep), dma_flags);
	अगर (ret)
		वापस ret;

	ret = mt7601u_dma_submit_tx(dev, skb, ep);
	अगर (ret) अणु
		ieee80211_मुक्त_txskb(dev->hw, skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mt7601u_समाप्त_rx(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev->rx_q.entries; i++)
		usb_poison_urb(dev->rx_q.e[i].urb);
पूर्ण

अटल पूर्णांक mt7601u_submit_rx_buf(काष्ठा mt7601u_dev *dev,
				 काष्ठा mt7601u_dma_buf_rx *e, gfp_t gfp)
अणु
	काष्ठा usb_device *usb_dev = mt7601u_to_usb_dev(dev);
	u8 *buf = page_address(e->p);
	अचिन्हित pipe;
	पूर्णांक ret;

	pipe = usb_rcvbulkpipe(usb_dev, dev->in_eps[MT_EP_IN_PKT_RX]);

	usb_fill_bulk_urb(e->urb, usb_dev, pipe, buf, MT_RX_URB_SIZE,
			  mt7601u_complete_rx, dev);

	trace_mt_submit_urb(dev, e->urb);
	ret = usb_submit_urb(e->urb, gfp);
	अगर (ret)
		dev_err(dev->dev, "Error: submit RX URB failed:%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mt7601u_submit_rx(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < dev->rx_q.entries; i++) अणु
		ret = mt7601u_submit_rx_buf(dev, &dev->rx_q.e[i], GFP_KERNEL);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mt7601u_मुक्त_rx(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev->rx_q.entries; i++) अणु
		__मुक्त_pages(dev->rx_q.e[i].p, MT_RX_ORDER);
		usb_मुक्त_urb(dev->rx_q.e[i].urb);
	पूर्ण
पूर्ण

अटल पूर्णांक mt7601u_alloc_rx(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक i;

	स_रखो(&dev->rx_q, 0, माप(dev->rx_q));
	dev->rx_q.dev = dev;
	dev->rx_q.entries = N_RX_ENTRIES;

	क्रम (i = 0; i < N_RX_ENTRIES; i++) अणु
		dev->rx_q.e[i].urb = usb_alloc_urb(0, GFP_KERNEL);
		dev->rx_q.e[i].p = dev_alloc_pages(MT_RX_ORDER);

		अगर (!dev->rx_q.e[i].urb || !dev->rx_q.e[i].p)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mt7601u_मुक्त_tx_queue(काष्ठा mt7601u_tx_queue *q)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < q->entries; i++)  अणु
		usb_poison_urb(q->e[i].urb);
		अगर (q->e[i].skb)
			mt7601u_tx_status(q->dev, q->e[i].skb);
		usb_मुक्त_urb(q->e[i].urb);
	पूर्ण
पूर्ण

अटल व्योम mt7601u_मुक्त_tx(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक i;

	अगर (!dev->tx_q)
		वापस;

	क्रम (i = 0; i < __MT_EP_OUT_MAX; i++)
		mt7601u_मुक्त_tx_queue(&dev->tx_q[i]);
पूर्ण

अटल पूर्णांक mt7601u_alloc_tx_queue(काष्ठा mt7601u_dev *dev,
				  काष्ठा mt7601u_tx_queue *q)
अणु
	पूर्णांक i;

	q->dev = dev;
	q->entries = N_TX_ENTRIES;

	क्रम (i = 0; i < N_TX_ENTRIES; i++) अणु
		q->e[i].urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!q->e[i].urb)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt7601u_alloc_tx(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक i;

	dev->tx_q = devm_kसुस्मृति(dev->dev, __MT_EP_OUT_MAX,
				 माप(*dev->tx_q), GFP_KERNEL);
	अगर (!dev->tx_q)
		वापस -ENOMEM;

	क्रम (i = 0; i < __MT_EP_OUT_MAX; i++)
		अगर (mt7601u_alloc_tx_queue(dev, &dev->tx_q[i]))
			वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक mt7601u_dma_init(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक ret = -ENOMEM;

	tasklet_setup(&dev->tx_tasklet, mt7601u_tx_tasklet);
	tasklet_setup(&dev->rx_tasklet, mt7601u_rx_tasklet);

	ret = mt7601u_alloc_tx(dev);
	अगर (ret)
		जाओ err;
	ret = mt7601u_alloc_rx(dev);
	अगर (ret)
		जाओ err;

	ret = mt7601u_submit_rx(dev);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	mt7601u_dma_cleanup(dev);
	वापस ret;
पूर्ण

व्योम mt7601u_dma_cleanup(काष्ठा mt7601u_dev *dev)
अणु
	mt7601u_समाप्त_rx(dev);

	tasklet_समाप्त(&dev->rx_tasklet);

	mt7601u_मुक्त_rx(dev);
	mt7601u_मुक्त_tx(dev);

	tasklet_समाप्त(&dev->tx_tasklet);
पूर्ण
