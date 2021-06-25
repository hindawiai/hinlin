<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#समावेश <linux/dma-mapping.h>
#समावेश "mt76.h"
#समावेश "dma.h"

अटल काष्ठा mt76_txwi_cache *
mt76_alloc_txwi(काष्ठा mt76_dev *dev)
अणु
	काष्ठा mt76_txwi_cache *t;
	dma_addr_t addr;
	u8 *txwi;
	पूर्णांक size;

	size = L1_CACHE_ALIGN(dev->drv->txwi_size + माप(*t));
	txwi = devm_kzalloc(dev->dev, size, GFP_ATOMIC);
	अगर (!txwi)
		वापस शून्य;

	addr = dma_map_single(dev->dev, txwi, dev->drv->txwi_size,
			      DMA_TO_DEVICE);
	t = (काष्ठा mt76_txwi_cache *)(txwi + dev->drv->txwi_size);
	t->dma_addr = addr;

	वापस t;
पूर्ण

अटल काष्ठा mt76_txwi_cache *
__mt76_get_txwi(काष्ठा mt76_dev *dev)
अणु
	काष्ठा mt76_txwi_cache *t = शून्य;

	spin_lock(&dev->lock);
	अगर (!list_empty(&dev->txwi_cache)) अणु
		t = list_first_entry(&dev->txwi_cache, काष्ठा mt76_txwi_cache,
				     list);
		list_del(&t->list);
	पूर्ण
	spin_unlock(&dev->lock);

	वापस t;
पूर्ण

अटल काष्ठा mt76_txwi_cache *
mt76_get_txwi(काष्ठा mt76_dev *dev)
अणु
	काष्ठा mt76_txwi_cache *t = __mt76_get_txwi(dev);

	अगर (t)
		वापस t;

	वापस mt76_alloc_txwi(dev);
पूर्ण

व्योम
mt76_put_txwi(काष्ठा mt76_dev *dev, काष्ठा mt76_txwi_cache *t)
अणु
	अगर (!t)
		वापस;

	spin_lock(&dev->lock);
	list_add(&t->list, &dev->txwi_cache);
	spin_unlock(&dev->lock);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_put_txwi);

अटल व्योम
mt76_मुक्त_pending_txwi(काष्ठा mt76_dev *dev)
अणु
	काष्ठा mt76_txwi_cache *t;

	local_bh_disable();
	जबतक ((t = __mt76_get_txwi(dev)) != शून्य)
		dma_unmap_single(dev->dev, t->dma_addr, dev->drv->txwi_size,
				 DMA_TO_DEVICE);
	local_bh_enable();
पूर्ण

अटल व्योम
mt76_dma_sync_idx(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q)
अणु
	ग_लिखोl(q->desc_dma, &q->regs->desc_base);
	ग_लिखोl(q->ndesc, &q->regs->ring_size);
	q->head = पढ़ोl(&q->regs->dma_idx);
	q->tail = q->head;
पूर्ण

अटल व्योम
mt76_dma_queue_reset(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q)
अणु
	पूर्णांक i;

	अगर (!q)
		वापस;

	/* clear descriptors */
	क्रम (i = 0; i < q->ndesc; i++)
		q->desc[i].ctrl = cpu_to_le32(MT_DMA_CTL_DMA_DONE);

	ग_लिखोl(0, &q->regs->cpu_idx);
	ग_लिखोl(0, &q->regs->dma_idx);
	mt76_dma_sync_idx(dev, q);
पूर्ण

अटल पूर्णांक
mt76_dma_alloc_queue(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
		     पूर्णांक idx, पूर्णांक n_desc, पूर्णांक bufsize,
		     u32 ring_base)
अणु
	पूर्णांक size;

	spin_lock_init(&q->lock);
	spin_lock_init(&q->cleanup_lock);

	q->regs = dev->mmio.regs + ring_base + idx * MT_RING_SIZE;
	q->ndesc = n_desc;
	q->buf_size = bufsize;
	q->hw_idx = idx;

	size = q->ndesc * माप(काष्ठा mt76_desc);
	q->desc = dmam_alloc_coherent(dev->dev, size, &q->desc_dma, GFP_KERNEL);
	अगर (!q->desc)
		वापस -ENOMEM;

	size = q->ndesc * माप(*q->entry);
	q->entry = devm_kzalloc(dev->dev, size, GFP_KERNEL);
	अगर (!q->entry)
		वापस -ENOMEM;

	mt76_dma_queue_reset(dev, q);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt76_dma_add_buf(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
		 काष्ठा mt76_queue_buf *buf, पूर्णांक nbufs, u32 info,
		 काष्ठा sk_buff *skb, व्योम *txwi)
अणु
	काष्ठा mt76_queue_entry *entry;
	काष्ठा mt76_desc *desc;
	u32 ctrl;
	पूर्णांक i, idx = -1;

	अगर (txwi) अणु
		q->entry[q->head].txwi = DMA_DUMMY_DATA;
		q->entry[q->head].skip_buf0 = true;
	पूर्ण

	क्रम (i = 0; i < nbufs; i += 2, buf += 2) अणु
		u32 buf0 = buf[0].addr, buf1 = 0;

		idx = q->head;
		q->head = (q->head + 1) % q->ndesc;

		desc = &q->desc[idx];
		entry = &q->entry[idx];

		अगर (buf[0].skip_unmap)
			entry->skip_buf0 = true;
		entry->skip_buf1 = i == nbufs - 1;

		entry->dma_addr[0] = buf[0].addr;
		entry->dma_len[0] = buf[0].len;

		ctrl = FIELD_PREP(MT_DMA_CTL_SD_LEN0, buf[0].len);
		अगर (i < nbufs - 1) अणु
			entry->dma_addr[1] = buf[1].addr;
			entry->dma_len[1] = buf[1].len;
			buf1 = buf[1].addr;
			ctrl |= FIELD_PREP(MT_DMA_CTL_SD_LEN1, buf[1].len);
			अगर (buf[1].skip_unmap)
				entry->skip_buf1 = true;
		पूर्ण

		अगर (i == nbufs - 1)
			ctrl |= MT_DMA_CTL_LAST_SEC0;
		अन्यथा अगर (i == nbufs - 2)
			ctrl |= MT_DMA_CTL_LAST_SEC1;

		WRITE_ONCE(desc->buf0, cpu_to_le32(buf0));
		WRITE_ONCE(desc->buf1, cpu_to_le32(buf1));
		WRITE_ONCE(desc->info, cpu_to_le32(info));
		WRITE_ONCE(desc->ctrl, cpu_to_le32(ctrl));

		q->queued++;
	पूर्ण

	q->entry[idx].txwi = txwi;
	q->entry[idx].skb = skb;

	वापस idx;
पूर्ण

अटल व्योम
mt76_dma_tx_cleanup_idx(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q, पूर्णांक idx,
			काष्ठा mt76_queue_entry *prev_e)
अणु
	काष्ठा mt76_queue_entry *e = &q->entry[idx];

	अगर (!e->skip_buf0)
		dma_unmap_single(dev->dev, e->dma_addr[0], e->dma_len[0],
				 DMA_TO_DEVICE);

	अगर (!e->skip_buf1)
		dma_unmap_single(dev->dev, e->dma_addr[1], e->dma_len[1],
				 DMA_TO_DEVICE);

	अगर (e->txwi == DMA_DUMMY_DATA)
		e->txwi = शून्य;

	अगर (e->skb == DMA_DUMMY_DATA)
		e->skb = शून्य;

	*prev_e = *e;
	स_रखो(e, 0, माप(*e));
पूर्ण

अटल व्योम
mt76_dma_kick_queue(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q)
अणु
	wmb();
	ग_लिखोl(q->head, &q->regs->cpu_idx);
पूर्ण

अटल व्योम
mt76_dma_tx_cleanup(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q, bool flush)
अणु
	काष्ठा mt76_queue_entry entry;
	पूर्णांक last;

	अगर (!q)
		वापस;

	spin_lock_bh(&q->cleanup_lock);
	अगर (flush)
		last = -1;
	अन्यथा
		last = पढ़ोl(&q->regs->dma_idx);

	जबतक (q->queued > 0 && q->tail != last) अणु
		mt76_dma_tx_cleanup_idx(dev, q, q->tail, &entry);
		mt76_queue_tx_complete(dev, q, &entry);

		अगर (entry.txwi) अणु
			अगर (!(dev->drv->drv_flags & MT_DRV_TXWI_NO_FREE))
				mt76_put_txwi(dev, entry.txwi);
		पूर्ण

		अगर (!flush && q->tail == last)
			last = पढ़ोl(&q->regs->dma_idx);

	पूर्ण
	spin_unlock_bh(&q->cleanup_lock);

	अगर (flush) अणु
		spin_lock_bh(&q->lock);
		mt76_dma_sync_idx(dev, q);
		mt76_dma_kick_queue(dev, q);
		spin_unlock_bh(&q->lock);
	पूर्ण

	अगर (!q->queued)
		wake_up(&dev->tx_रुको);
पूर्ण

अटल व्योम *
mt76_dma_get_buf(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q, पूर्णांक idx,
		 पूर्णांक *len, u32 *info, bool *more)
अणु
	काष्ठा mt76_queue_entry *e = &q->entry[idx];
	काष्ठा mt76_desc *desc = &q->desc[idx];
	dma_addr_t buf_addr;
	व्योम *buf = e->buf;
	पूर्णांक buf_len = SKB_WITH_OVERHEAD(q->buf_size);

	buf_addr = e->dma_addr[0];
	अगर (len) अणु
		u32 ctl = le32_to_cpu(READ_ONCE(desc->ctrl));
		*len = FIELD_GET(MT_DMA_CTL_SD_LEN0, ctl);
		*more = !(ctl & MT_DMA_CTL_LAST_SEC0);
	पूर्ण

	अगर (info)
		*info = le32_to_cpu(desc->info);

	dma_unmap_single(dev->dev, buf_addr, buf_len, DMA_FROM_DEVICE);
	e->buf = शून्य;

	वापस buf;
पूर्ण

अटल व्योम *
mt76_dma_dequeue(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q, bool flush,
		 पूर्णांक *len, u32 *info, bool *more)
अणु
	पूर्णांक idx = q->tail;

	*more = false;
	अगर (!q->queued)
		वापस शून्य;

	अगर (flush)
		q->desc[idx].ctrl |= cpu_to_le32(MT_DMA_CTL_DMA_DONE);
	अन्यथा अगर (!(q->desc[idx].ctrl & cpu_to_le32(MT_DMA_CTL_DMA_DONE)))
		वापस शून्य;

	q->tail = (q->tail + 1) % q->ndesc;
	q->queued--;

	वापस mt76_dma_get_buf(dev, q, idx, len, info, more);
पूर्ण

अटल पूर्णांक
mt76_dma_tx_queue_skb_raw(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
			  काष्ठा sk_buff *skb, u32 tx_info)
अणु
	काष्ठा mt76_queue_buf buf = अणुपूर्ण;
	dma_addr_t addr;

	अगर (q->queued + 1 >= q->ndesc - 1)
		जाओ error;

	addr = dma_map_single(dev->dev, skb->data, skb->len,
			      DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev->dev, addr)))
		जाओ error;

	buf.addr = addr;
	buf.len = skb->len;

	spin_lock_bh(&q->lock);
	mt76_dma_add_buf(dev, q, &buf, 1, tx_info, skb, शून्य);
	mt76_dma_kick_queue(dev, q);
	spin_unlock_bh(&q->lock);

	वापस 0;

error:
	dev_kमुक्त_skb(skb);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक
mt76_dma_tx_queue_skb(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
		      काष्ठा sk_buff *skb, काष्ठा mt76_wcid *wcid,
		      काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt76_tx_info tx_info = अणु
		.skb = skb,
	पूर्ण;
	काष्ठा ieee80211_hw *hw;
	पूर्णांक len, n = 0, ret = -ENOMEM;
	काष्ठा mt76_txwi_cache *t;
	काष्ठा sk_buff *iter;
	dma_addr_t addr;
	u8 *txwi;

	t = mt76_get_txwi(dev);
	अगर (!t) अणु
		hw = mt76_tx_status_get_hw(dev, skb);
		ieee80211_मुक्त_txskb(hw, skb);
		वापस -ENOMEM;
	पूर्ण
	txwi = mt76_get_txwi_ptr(dev, t);

	skb->prev = skb->next = शून्य;
	अगर (dev->drv->drv_flags & MT_DRV_TX_ALIGNED4_SKBS)
		mt76_insert_hdr_pad(skb);

	len = skb_headlen(skb);
	addr = dma_map_single(dev->dev, skb->data, len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev->dev, addr)))
		जाओ मुक्त;

	tx_info.buf[n].addr = t->dma_addr;
	tx_info.buf[n++].len = dev->drv->txwi_size;
	tx_info.buf[n].addr = addr;
	tx_info.buf[n++].len = len;

	skb_walk_frags(skb, iter) अणु
		अगर (n == ARRAY_SIZE(tx_info.buf))
			जाओ unmap;

		addr = dma_map_single(dev->dev, iter->data, iter->len,
				      DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(dev->dev, addr)))
			जाओ unmap;

		tx_info.buf[n].addr = addr;
		tx_info.buf[n++].len = iter->len;
	पूर्ण
	tx_info.nbuf = n;

	अगर (q->queued + (tx_info.nbuf + 1) / 2 >= q->ndesc - 1) अणु
		ret = -ENOMEM;
		जाओ unmap;
	पूर्ण

	dma_sync_single_क्रम_cpu(dev->dev, t->dma_addr, dev->drv->txwi_size,
				DMA_TO_DEVICE);
	ret = dev->drv->tx_prepare_skb(dev, txwi, q->qid, wcid, sta, &tx_info);
	dma_sync_single_क्रम_device(dev->dev, t->dma_addr, dev->drv->txwi_size,
				   DMA_TO_DEVICE);
	अगर (ret < 0)
		जाओ unmap;

	वापस mt76_dma_add_buf(dev, q, tx_info.buf, tx_info.nbuf,
				tx_info.info, tx_info.skb, t);

unmap:
	क्रम (n--; n > 0; n--)
		dma_unmap_single(dev->dev, tx_info.buf[n].addr,
				 tx_info.buf[n].len, DMA_TO_DEVICE);

मुक्त:
#अगर_घोषित CONFIG_NL80211_TESTMODE
	/* fix tx_करोne accounting on queue overflow */
	अगर (mt76_is_tesपंचांगode_skb(dev, skb, &hw)) अणु
		काष्ठा mt76_phy *phy = hw->priv;

		अगर (tx_info.skb == phy->test.tx_skb)
			phy->test.tx_करोne--;
	पूर्ण
#पूर्ण_अगर

	dev_kमुक्त_skb(tx_info.skb);
	mt76_put_txwi(dev, t);
	वापस ret;
पूर्ण

अटल पूर्णांक
mt76_dma_rx_fill(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q)
अणु
	dma_addr_t addr;
	व्योम *buf;
	पूर्णांक frames = 0;
	पूर्णांक len = SKB_WITH_OVERHEAD(q->buf_size);
	पूर्णांक offset = q->buf_offset;

	spin_lock_bh(&q->lock);

	जबतक (q->queued < q->ndesc - 1) अणु
		काष्ठा mt76_queue_buf qbuf;

		buf = page_frag_alloc(&q->rx_page, q->buf_size, GFP_ATOMIC);
		अगर (!buf)
			अवरोध;

		addr = dma_map_single(dev->dev, buf, len, DMA_FROM_DEVICE);
		अगर (unlikely(dma_mapping_error(dev->dev, addr))) अणु
			skb_मुक्त_frag(buf);
			अवरोध;
		पूर्ण

		qbuf.addr = addr + offset;
		qbuf.len = len - offset;
		mt76_dma_add_buf(dev, q, &qbuf, 1, 0, buf, शून्य);
		frames++;
	पूर्ण

	अगर (frames)
		mt76_dma_kick_queue(dev, q);

	spin_unlock_bh(&q->lock);

	वापस frames;
पूर्ण

अटल व्योम
mt76_dma_rx_cleanup(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q)
अणु
	काष्ठा page *page;
	व्योम *buf;
	bool more;

	spin_lock_bh(&q->lock);
	करो अणु
		buf = mt76_dma_dequeue(dev, q, true, शून्य, शून्य, &more);
		अगर (!buf)
			अवरोध;

		skb_मुक्त_frag(buf);
	पूर्ण जबतक (1);
	spin_unlock_bh(&q->lock);

	अगर (!q->rx_page.va)
		वापस;

	page = virt_to_page(q->rx_page.va);
	__page_frag_cache_drain(page, q->rx_page.pagecnt_bias);
	स_रखो(&q->rx_page, 0, माप(q->rx_page));
पूर्ण

अटल व्योम
mt76_dma_rx_reset(काष्ठा mt76_dev *dev, क्रमागत mt76_rxq_id qid)
अणु
	काष्ठा mt76_queue *q = &dev->q_rx[qid];
	पूर्णांक i;

	क्रम (i = 0; i < q->ndesc; i++)
		q->desc[i].ctrl = cpu_to_le32(MT_DMA_CTL_DMA_DONE);

	mt76_dma_rx_cleanup(dev, q);
	mt76_dma_sync_idx(dev, q);
	mt76_dma_rx_fill(dev, q);

	अगर (!q->rx_head)
		वापस;

	dev_kमुक्त_skb(q->rx_head);
	q->rx_head = शून्य;
पूर्ण

अटल व्योम
mt76_add_fragment(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q, व्योम *data,
		  पूर्णांक len, bool more)
अणु
	काष्ठा sk_buff *skb = q->rx_head;
	काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);
	पूर्णांक nr_frags = shinfo->nr_frags;

	अगर (nr_frags < ARRAY_SIZE(shinfo->frags)) अणु
		काष्ठा page *page = virt_to_head_page(data);
		पूर्णांक offset = data - page_address(page) + q->buf_offset;

		skb_add_rx_frag(skb, nr_frags, page, offset, len, q->buf_size);
	पूर्ण अन्यथा अणु
		skb_मुक्त_frag(data);
	पूर्ण

	अगर (more)
		वापस;

	q->rx_head = शून्य;
	अगर (nr_frags < ARRAY_SIZE(shinfo->frags))
		dev->drv->rx_skb(dev, q - dev->q_rx, skb);
	अन्यथा
		dev_kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक
mt76_dma_rx_process(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q, पूर्णांक budget)
अणु
	पूर्णांक len, data_len, करोne = 0;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *data;
	bool more;

	जबतक (करोne < budget) अणु
		u32 info;

		data = mt76_dma_dequeue(dev, q, false, &len, &info, &more);
		अगर (!data)
			अवरोध;

		अगर (q->rx_head)
			data_len = q->buf_size;
		अन्यथा
			data_len = SKB_WITH_OVERHEAD(q->buf_size);

		अगर (data_len < len + q->buf_offset) अणु
			dev_kमुक्त_skb(q->rx_head);
			q->rx_head = शून्य;

			skb_मुक्त_frag(data);
			जारी;
		पूर्ण

		अगर (q->rx_head) अणु
			mt76_add_fragment(dev, q, data, len, more);
			जारी;
		पूर्ण

		skb = build_skb(data, q->buf_size);
		अगर (!skb) अणु
			skb_मुक्त_frag(data);
			जारी;
		पूर्ण
		skb_reserve(skb, q->buf_offset);

		अगर (q == &dev->q_rx[MT_RXQ_MCU]) अणु
			u32 *rxfce = (u32 *)skb->cb;
			*rxfce = info;
		पूर्ण

		__skb_put(skb, len);
		करोne++;

		अगर (more) अणु
			q->rx_head = skb;
			जारी;
		पूर्ण

		dev->drv->rx_skb(dev, q - dev->q_rx, skb);
	पूर्ण

	mt76_dma_rx_fill(dev, q);
	वापस करोne;
पूर्ण

पूर्णांक mt76_dma_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mt76_dev *dev;
	पूर्णांक qid, करोne = 0, cur;

	dev = container_of(napi->dev, काष्ठा mt76_dev, napi_dev);
	qid = napi - dev->napi;

	rcu_पढ़ो_lock();

	करो अणु
		cur = mt76_dma_rx_process(dev, &dev->q_rx[qid], budget - करोne);
		mt76_rx_poll_complete(dev, qid, napi);
		करोne += cur;
	पूर्ण जबतक (cur && करोne < budget);

	rcu_पढ़ो_unlock();

	अगर (करोne < budget && napi_complete(napi))
		dev->drv->rx_poll_complete(dev, qid);

	वापस करोne;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_dma_rx_poll);

अटल पूर्णांक
mt76_dma_init(काष्ठा mt76_dev *dev,
	      पूर्णांक (*poll)(काष्ठा napi_काष्ठा *napi, पूर्णांक budget))
अणु
	पूर्णांक i;

	init_dummy_netdev(&dev->napi_dev);
	init_dummy_netdev(&dev->tx_napi_dev);
	snम_लिखो(dev->napi_dev.name, माप(dev->napi_dev.name), "%s",
		 wiphy_name(dev->hw->wiphy));
	dev->napi_dev.thपढ़ोed = 1;

	mt76_क्रम_each_q_rx(dev, i) अणु
		netअगर_napi_add(&dev->napi_dev, &dev->napi[i], poll, 64);
		mt76_dma_rx_fill(dev, &dev->q_rx[i]);
		napi_enable(&dev->napi[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mt76_queue_ops mt76_dma_ops = अणु
	.init = mt76_dma_init,
	.alloc = mt76_dma_alloc_queue,
	.reset_q = mt76_dma_queue_reset,
	.tx_queue_skb_raw = mt76_dma_tx_queue_skb_raw,
	.tx_queue_skb = mt76_dma_tx_queue_skb,
	.tx_cleanup = mt76_dma_tx_cleanup,
	.rx_cleanup = mt76_dma_rx_cleanup,
	.rx_reset = mt76_dma_rx_reset,
	.kick = mt76_dma_kick_queue,
पूर्ण;

व्योम mt76_dma_attach(काष्ठा mt76_dev *dev)
अणु
	dev->queue_ops = &mt76_dma_ops;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_dma_attach);

व्योम mt76_dma_cleanup(काष्ठा mt76_dev *dev)
अणु
	पूर्णांक i;

	mt76_worker_disable(&dev->tx_worker);
	netअगर_napi_del(&dev->tx_napi);

	क्रम (i = 0; i < ARRAY_SIZE(dev->phy.q_tx); i++) अणु
		mt76_dma_tx_cleanup(dev, dev->phy.q_tx[i], true);
		अगर (dev->phy2)
			mt76_dma_tx_cleanup(dev, dev->phy2->q_tx[i], true);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(dev->q_mcu); i++)
		mt76_dma_tx_cleanup(dev, dev->q_mcu[i], true);

	mt76_क्रम_each_q_rx(dev, i) अणु
		netअगर_napi_del(&dev->napi[i]);
		mt76_dma_rx_cleanup(dev, &dev->q_rx[i]);
	पूर्ण

	mt76_मुक्त_pending_txwi(dev);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_dma_cleanup);
