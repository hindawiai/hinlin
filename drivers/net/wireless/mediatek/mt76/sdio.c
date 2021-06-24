<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc.
 *
 * This file is written based on mt76/usb.c.
 *
 * Author: Felix Fietkau <nbd@nbd.name>
 *	   Lorenzo Bianconi <lorenzo@kernel.org>
 *	   Sean Wang <sean.wang@mediatek.com>
 */

#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/sched.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "mt76.h"

अटल पूर्णांक
mt76s_alloc_rx_queue(काष्ठा mt76_dev *dev, क्रमागत mt76_rxq_id qid)
अणु
	काष्ठा mt76_queue *q = &dev->q_rx[qid];

	spin_lock_init(&q->lock);
	q->entry = devm_kसुस्मृति(dev->dev,
				MT_NUM_RX_ENTRIES, माप(*q->entry),
				GFP_KERNEL);
	अगर (!q->entry)
		वापस -ENOMEM;

	q->ndesc = MT_NUM_RX_ENTRIES;
	q->head = q->tail = 0;
	q->queued = 0;

	वापस 0;
पूर्ण

अटल काष्ठा mt76_queue *mt76s_alloc_tx_queue(काष्ठा mt76_dev *dev)
अणु
	काष्ठा mt76_queue *q;

	q = devm_kzalloc(dev->dev, माप(*q), GFP_KERNEL);
	अगर (!q)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&q->lock);
	q->entry = devm_kसुस्मृति(dev->dev,
				MT_NUM_TX_ENTRIES, माप(*q->entry),
				GFP_KERNEL);
	अगर (!q->entry)
		वापस ERR_PTR(-ENOMEM);

	q->ndesc = MT_NUM_TX_ENTRIES;

	वापस q;
पूर्ण

अटल पूर्णांक mt76s_alloc_tx(काष्ठा mt76_dev *dev)
अणु
	काष्ठा mt76_queue *q;
	पूर्णांक i;

	क्रम (i = 0; i <= MT_TXQ_PSD; i++) अणु
		q = mt76s_alloc_tx_queue(dev);
		अगर (IS_ERR(q))
			वापस PTR_ERR(q);

		q->qid = i;
		dev->phy.q_tx[i] = q;
	पूर्ण

	q = mt76s_alloc_tx_queue(dev);
	अगर (IS_ERR(q))
		वापस PTR_ERR(q);

	q->qid = MT_MCUQ_WM;
	dev->q_mcu[MT_MCUQ_WM] = q;

	वापस 0;
पूर्ण

पूर्णांक mt76s_alloc_queues(काष्ठा mt76_dev *dev)
अणु
	पूर्णांक err;

	err = mt76s_alloc_rx_queue(dev, MT_RXQ_MAIN);
	अगर (err < 0)
		वापस err;

	वापस mt76s_alloc_tx(dev);
पूर्ण
EXPORT_SYMBOL_GPL(mt76s_alloc_queues);

अटल काष्ठा mt76_queue_entry *
mt76s_get_next_rx_entry(काष्ठा mt76_queue *q)
अणु
	काष्ठा mt76_queue_entry *e = शून्य;

	spin_lock_bh(&q->lock);
	अगर (q->queued > 0) अणु
		e = &q->entry[q->tail];
		q->tail = (q->tail + 1) % q->ndesc;
		q->queued--;
	पूर्ण
	spin_unlock_bh(&q->lock);

	वापस e;
पूर्ण

अटल पूर्णांक
mt76s_process_rx_queue(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q)
अणु
	पूर्णांक qid = q - &dev->q_rx[MT_RXQ_MAIN];
	पूर्णांक nframes = 0;

	जबतक (true) अणु
		काष्ठा mt76_queue_entry *e;

		अगर (!test_bit(MT76_STATE_INITIALIZED, &dev->phy.state))
			अवरोध;

		e = mt76s_get_next_rx_entry(q);
		अगर (!e || !e->skb)
			अवरोध;

		dev->drv->rx_skb(dev, MT_RXQ_MAIN, e->skb);
		e->skb = शून्य;
		nframes++;
	पूर्ण
	अगर (qid == MT_RXQ_MAIN)
		mt76_rx_poll_complete(dev, MT_RXQ_MAIN, शून्य);

	वापस nframes;
पूर्ण

अटल व्योम mt76s_net_worker(काष्ठा mt76_worker *w)
अणु
	काष्ठा mt76_sdio *sdio = container_of(w, काष्ठा mt76_sdio,
					      net_worker);
	काष्ठा mt76_dev *dev = container_of(sdio, काष्ठा mt76_dev, sdio);
	पूर्णांक i, nframes;

	करो अणु
		nframes = 0;

		local_bh_disable();
		rcu_पढ़ो_lock();

		mt76_क्रम_each_q_rx(dev, i)
			nframes += mt76s_process_rx_queue(dev, &dev->q_rx[i]);

		rcu_पढ़ो_unlock();
		local_bh_enable();
	पूर्ण जबतक (nframes > 0);
पूर्ण

अटल पूर्णांक mt76s_process_tx_queue(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q)
अणु
	काष्ठा mt76_queue_entry entry;
	पूर्णांक nframes = 0;
	bool mcu;

	अगर (!q)
		वापस 0;

	mcu = q == dev->q_mcu[MT_MCUQ_WM];
	जबतक (q->queued > 0) अणु
		अगर (!q->entry[q->tail].करोne)
			अवरोध;

		entry = q->entry[q->tail];
		q->entry[q->tail].करोne = false;

		अगर (mcu) अणु
			dev_kमुक्त_skb(entry.skb);
			entry.skb = शून्य;
		पूर्ण

		mt76_queue_tx_complete(dev, q, &entry);
		nframes++;
	पूर्ण

	अगर (!q->queued)
		wake_up(&dev->tx_रुको);

	अगर (!mcu)
		mt76_txq_schedule(&dev->phy, q->qid);

	वापस nframes;
पूर्ण

अटल व्योम mt76s_status_worker(काष्ठा mt76_worker *w)
अणु
	काष्ठा mt76_sdio *sdio = container_of(w, काष्ठा mt76_sdio,
					      status_worker);
	काष्ठा mt76_dev *dev = container_of(sdio, काष्ठा mt76_dev, sdio);
	पूर्णांक i, nframes;

	करो अणु
		nframes = mt76s_process_tx_queue(dev, dev->q_mcu[MT_MCUQ_WM]);

		क्रम (i = 0; i <= MT_TXQ_PSD; i++)
			nframes += mt76s_process_tx_queue(dev,
							  dev->phy.q_tx[i]);

		अगर (dev->drv->tx_status_data &&
		    !test_and_set_bit(MT76_READING_STATS, &dev->phy.state))
			queue_work(dev->wq, &dev->sdio.stat_work);
	पूर्ण जबतक (nframes > 0);
पूर्ण

अटल व्योम mt76s_tx_status_data(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt76_sdio *sdio;
	काष्ठा mt76_dev *dev;
	u8 update = 1;
	u16 count = 0;

	sdio = container_of(work, काष्ठा mt76_sdio, stat_work);
	dev = container_of(sdio, काष्ठा mt76_dev, sdio);

	जबतक (true) अणु
		अगर (test_bit(MT76_REMOVED, &dev->phy.state))
			अवरोध;

		अगर (!dev->drv->tx_status_data(dev, &update))
			अवरोध;
		count++;
	पूर्ण

	अगर (count && test_bit(MT76_STATE_RUNNING, &dev->phy.state))
		queue_work(dev->wq, &sdio->stat_work);
	अन्यथा
		clear_bit(MT76_READING_STATS, &dev->phy.state);
पूर्ण

अटल पूर्णांक
mt76s_tx_queue_skb(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
		   काष्ठा sk_buff *skb, काष्ठा mt76_wcid *wcid,
		   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt76_tx_info tx_info = अणु
		.skb = skb,
	पूर्ण;
	पूर्णांक err, len = skb->len;
	u16 idx = q->head;

	अगर (q->queued == q->ndesc)
		वापस -ENOSPC;

	skb->prev = skb->next = शून्य;
	err = dev->drv->tx_prepare_skb(dev, शून्य, q->qid, wcid, sta, &tx_info);
	अगर (err < 0)
		वापस err;

	q->entry[q->head].skb = tx_info.skb;
	q->entry[q->head].buf_sz = len;

	smp_wmb();

	q->head = (q->head + 1) % q->ndesc;
	q->queued++;

	वापस idx;
पूर्ण

अटल पूर्णांक
mt76s_tx_queue_skb_raw(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
		       काष्ठा sk_buff *skb, u32 tx_info)
अणु
	पूर्णांक ret = -ENOSPC, len = skb->len, pad;

	अगर (q->queued == q->ndesc)
		जाओ error;

	pad = round_up(skb->len, 4) - skb->len;
	ret = mt76_skb_adjust_pad(skb, pad);
	अगर (ret)
		जाओ error;

	spin_lock_bh(&q->lock);

	q->entry[q->head].buf_sz = len;
	q->entry[q->head].skb = skb;
	q->head = (q->head + 1) % q->ndesc;
	q->queued++;

	spin_unlock_bh(&q->lock);

	वापस 0;

error:
	dev_kमुक्त_skb(skb);

	वापस ret;
पूर्ण

अटल व्योम mt76s_tx_kick(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q)
अणु
	काष्ठा mt76_sdio *sdio = &dev->sdio;

	mt76_worker_schedule(&sdio->txrx_worker);
पूर्ण

अटल स्थिर काष्ठा mt76_queue_ops sdio_queue_ops = अणु
	.tx_queue_skb = mt76s_tx_queue_skb,
	.kick = mt76s_tx_kick,
	.tx_queue_skb_raw = mt76s_tx_queue_skb_raw,
पूर्ण;

व्योम mt76s_deinit(काष्ठा mt76_dev *dev)
अणु
	काष्ठा mt76_sdio *sdio = &dev->sdio;
	पूर्णांक i;

	mt76_worker_tearकरोwn(&sdio->txrx_worker);
	mt76_worker_tearकरोwn(&sdio->status_worker);
	mt76_worker_tearकरोwn(&sdio->net_worker);

	cancel_work_sync(&sdio->stat_work);
	clear_bit(MT76_READING_STATS, &dev->phy.state);

	mt76_tx_status_check(dev, शून्य, true);

	sdio_claim_host(sdio->func);
	sdio_release_irq(sdio->func);
	sdio_release_host(sdio->func);

	mt76_क्रम_each_q_rx(dev, i) अणु
		काष्ठा mt76_queue *q = &dev->q_rx[i];
		पूर्णांक j;

		क्रम (j = 0; j < q->ndesc; j++) अणु
			काष्ठा mt76_queue_entry *e = &q->entry[j];

			अगर (!e->skb)
				जारी;

			dev_kमुक्त_skb(e->skb);
			e->skb = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76s_deinit);

पूर्णांक mt76s_init(काष्ठा mt76_dev *dev, काष्ठा sdio_func *func,
	       स्थिर काष्ठा mt76_bus_ops *bus_ops)
अणु
	काष्ठा mt76_sdio *sdio = &dev->sdio;
	पूर्णांक err;

	err = mt76_worker_setup(dev->hw, &sdio->status_worker,
				mt76s_status_worker, "sdio-status");
	अगर (err)
		वापस err;

	err = mt76_worker_setup(dev->hw, &sdio->net_worker, mt76s_net_worker,
				"sdio-net");
	अगर (err)
		वापस err;

	sched_set_fअगरo_low(sdio->status_worker.task);
	sched_set_fअगरo_low(sdio->net_worker.task);

	INIT_WORK(&sdio->stat_work, mt76s_tx_status_data);

	dev->queue_ops = &sdio_queue_ops;
	dev->bus = bus_ops;
	dev->sdio.func = func;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76s_init);

MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_AUTHOR("Lorenzo Bianconi <lorenzo@kernel.org>");
MODULE_LICENSE("Dual BSD/GPL");
