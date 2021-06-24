<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc.
 *
 * Author: Felix Fietkau <nbd@nbd.name>
 *	   Lorenzo Bianconi <lorenzo@kernel.org>
 *	   Sean Wang <sean.wang@mediatek.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/mmc/sdio_func.h>

#समावेश "../trace.h"
#समावेश "mt7615.h"
#समावेश "sdio.h"
#समावेश "mac.h"

अटल पूर्णांक mt7663s_refill_sched_quota(काष्ठा mt76_dev *dev, u32 *data)
अणु
	u32 ple_ac_data_quota[] = अणु
		FIELD_GET(TXQ_CNT_L, data[4]), /* VO */
		FIELD_GET(TXQ_CNT_H, data[3]), /* VI */
		FIELD_GET(TXQ_CNT_L, data[3]), /* BE */
		FIELD_GET(TXQ_CNT_H, data[2]), /* BK */
	पूर्ण;
	u32 pse_ac_data_quota[] = अणु
		FIELD_GET(TXQ_CNT_H, data[1]), /* VO */
		FIELD_GET(TXQ_CNT_L, data[1]), /* VI */
		FIELD_GET(TXQ_CNT_H, data[0]), /* BE */
		FIELD_GET(TXQ_CNT_L, data[0]), /* BK */
	पूर्ण;
	u32 pse_mcu_quota = FIELD_GET(TXQ_CNT_L, data[2]);
	u32 pse_data_quota = 0, ple_data_quota = 0;
	काष्ठा mt76_sdio *sdio = &dev->sdio;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pse_ac_data_quota); i++) अणु
		pse_data_quota += pse_ac_data_quota[i];
		ple_data_quota += ple_ac_data_quota[i];
	पूर्ण

	अगर (!pse_data_quota && !ple_data_quota && !pse_mcu_quota)
		वापस 0;

	sdio->sched.pse_mcu_quota += pse_mcu_quota;
	sdio->sched.pse_data_quota += pse_data_quota;
	sdio->sched.ple_data_quota += ple_data_quota;

	वापस pse_data_quota + ple_data_quota + pse_mcu_quota;
पूर्ण

अटल काष्ठा sk_buff *mt7663s_build_rx_skb(व्योम *data, पूर्णांक data_len,
					    पूर्णांक buf_len)
अणु
	पूर्णांक len = min_t(पूर्णांक, data_len, MT_SKB_HEAD_LEN);
	काष्ठा sk_buff *skb;

	skb = alloc_skb(len, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	skb_put_data(skb, data, len);
	अगर (data_len > len) अणु
		काष्ठा page *page;

		data += len;
		page = virt_to_head_page(data);
		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
				page, data - page_address(page),
				data_len - len, buf_len);
		get_page(page);
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक mt7663s_rx_run_queue(काष्ठा mt76_dev *dev, क्रमागत mt76_rxq_id qid,
				काष्ठा mt76s_पूर्णांकr *पूर्णांकr)
अणु
	काष्ठा mt76_queue *q = &dev->q_rx[qid];
	काष्ठा mt76_sdio *sdio = &dev->sdio;
	पूर्णांक len = 0, err, i;
	काष्ठा page *page;
	u8 *buf;

	क्रम (i = 0; i < पूर्णांकr->rx.num[qid]; i++)
		len += round_up(पूर्णांकr->rx.len[qid][i] + 4, 4);

	अगर (!len)
		वापस 0;

	अगर (len > sdio->func->cur_blksize)
		len = roundup(len, sdio->func->cur_blksize);

	page = __dev_alloc_pages(GFP_KERNEL, get_order(len));
	अगर (!page)
		वापस -ENOMEM;

	buf = page_address(page);

	err = sdio_पढ़ोsb(sdio->func, buf, MCR_WRDR(qid), len);
	अगर (err < 0) अणु
		dev_err(dev->dev, "sdio read data failed:%d\n", err);
		put_page(page);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < पूर्णांकr->rx.num[qid]; i++) अणु
		पूर्णांक index = (q->head + i) % q->ndesc;
		काष्ठा mt76_queue_entry *e = &q->entry[index];

		len = पूर्णांकr->rx.len[qid][i];
		e->skb = mt7663s_build_rx_skb(buf, len, round_up(len + 4, 4));
		अगर (!e->skb)
			अवरोध;

		buf += round_up(len + 4, 4);
		अगर (q->queued + i + 1 == q->ndesc)
			अवरोध;
	पूर्ण
	put_page(page);

	spin_lock_bh(&q->lock);
	q->head = (q->head + i) % q->ndesc;
	q->queued += i;
	spin_unlock_bh(&q->lock);

	वापस i;
पूर्ण

अटल पूर्णांक mt7663s_rx_handler(काष्ठा mt76_dev *dev)
अणु
	काष्ठा mt76_sdio *sdio = &dev->sdio;
	काष्ठा mt76s_पूर्णांकr *पूर्णांकr = sdio->पूर्णांकr_data;
	पूर्णांक nframes = 0, ret;

	ret = sdio_पढ़ोsb(sdio->func, पूर्णांकr, MCR_WHISR, माप(*पूर्णांकr));
	अगर (ret < 0)
		वापस ret;

	trace_dev_irq(dev, पूर्णांकr->isr, 0);

	अगर (पूर्णांकr->isr & WHIER_RX0_DONE_INT_EN) अणु
		ret = mt7663s_rx_run_queue(dev, 0, पूर्णांकr);
		अगर (ret > 0) अणु
			mt76_worker_schedule(&sdio->net_worker);
			nframes += ret;
		पूर्ण
	पूर्ण

	अगर (पूर्णांकr->isr & WHIER_RX1_DONE_INT_EN) अणु
		ret = mt7663s_rx_run_queue(dev, 1, पूर्णांकr);
		अगर (ret > 0) अणु
			mt76_worker_schedule(&sdio->net_worker);
			nframes += ret;
		पूर्ण
	पूर्ण

	nframes += !!mt7663s_refill_sched_quota(dev, पूर्णांकr->tx.wtqcr);

	वापस nframes;
पूर्ण

अटल पूर्णांक mt7663s_tx_pick_quota(काष्ठा mt76_sdio *sdio, bool mcu, पूर्णांक buf_sz,
				 पूर्णांक *pse_size, पूर्णांक *ple_size)
अणु
	पूर्णांक pse_sz;

	pse_sz = DIV_ROUND_UP(buf_sz + sdio->sched.deficit, MT_PSE_PAGE_SZ);

	अगर (mcu) अणु
		अगर (sdio->sched.pse_mcu_quota < *pse_size + pse_sz)
			वापस -EBUSY;
	पूर्ण अन्यथा अणु
		अगर (sdio->sched.pse_data_quota < *pse_size + pse_sz ||
		    sdio->sched.ple_data_quota < *ple_size + 1)
			वापस -EBUSY;

		*ple_size = *ple_size + 1;
	पूर्ण
	*pse_size = *pse_size + pse_sz;

	वापस 0;
पूर्ण

अटल व्योम mt7663s_tx_update_quota(काष्ठा mt76_sdio *sdio, bool mcu,
				    पूर्णांक pse_size, पूर्णांक ple_size)
अणु
	अगर (mcu) अणु
		sdio->sched.pse_mcu_quota -= pse_size;
	पूर्ण अन्यथा अणु
		sdio->sched.pse_data_quota -= pse_size;
		sdio->sched.ple_data_quota -= ple_size;
	पूर्ण
पूर्ण

अटल पूर्णांक __mt7663s_xmit_queue(काष्ठा mt76_dev *dev, u8 *data, पूर्णांक len)
अणु
	काष्ठा mt76_sdio *sdio = &dev->sdio;
	पूर्णांक err;

	अगर (len > sdio->func->cur_blksize)
		len = roundup(len, sdio->func->cur_blksize);

	err = sdio_ग_लिखोsb(sdio->func, MCR_WTDR1, data, len);
	अगर (err)
		dev_err(dev->dev, "sdio write failed: %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक mt7663s_tx_run_queue(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q)
अणु
	पूर्णांक qid, err, nframes = 0, len = 0, pse_sz = 0, ple_sz = 0;
	bool mcu = q == dev->q_mcu[MT_MCUQ_WM];
	काष्ठा mt76_sdio *sdio = &dev->sdio;
	u8 pad;

	qid = mcu ? ARRAY_SIZE(sdio->xmit_buf) - 1 : q->qid;
	जबतक (q->first != q->head) अणु
		काष्ठा mt76_queue_entry *e = &q->entry[q->first];
		काष्ठा sk_buff *iter;

		smp_rmb();

		अगर (!test_bit(MT76_STATE_MCU_RUNNING, &dev->phy.state)) अणु
			__skb_put_zero(e->skb, 4);
			err = __mt7663s_xmit_queue(dev, e->skb->data,
						   e->skb->len);
			अगर (err)
				वापस err;

			जाओ next;
		पूर्ण

		pad = roundup(e->skb->len, 4) - e->skb->len;
		अगर (len + e->skb->len + pad + 4 > MT76S_XMIT_BUF_SZ)
			अवरोध;

		अगर (mt7663s_tx_pick_quota(sdio, mcu, e->buf_sz, &pse_sz,
					  &ple_sz))
			अवरोध;

		स_नकल(sdio->xmit_buf[qid] + len, e->skb->data,
		       skb_headlen(e->skb));
		len += skb_headlen(e->skb);
		nframes++;

		skb_walk_frags(e->skb, iter) अणु
			स_नकल(sdio->xmit_buf[qid] + len, iter->data,
			       iter->len);
			len += iter->len;
			nframes++;
		पूर्ण

		अगर (unlikely(pad)) अणु
			स_रखो(sdio->xmit_buf[qid] + len, 0, pad);
			len += pad;
		पूर्ण
next:
		q->first = (q->first + 1) % q->ndesc;
		e->करोne = true;
	पूर्ण

	अगर (nframes) अणु
		स_रखो(sdio->xmit_buf[qid] + len, 0, 4);
		err = __mt7663s_xmit_queue(dev, sdio->xmit_buf[qid], len + 4);
		अगर (err)
			वापस err;
	पूर्ण
	mt7663s_tx_update_quota(sdio, mcu, pse_sz, ple_sz);

	mt76_worker_schedule(&sdio->status_worker);

	वापस nframes;
पूर्ण

व्योम mt7663s_txrx_worker(काष्ठा mt76_worker *w)
अणु
	काष्ठा mt76_sdio *sdio = container_of(w, काष्ठा mt76_sdio,
					      txrx_worker);
	काष्ठा mt76_dev *dev = container_of(sdio, काष्ठा mt76_dev, sdio);
	पूर्णांक i, nframes, ret;

	/* disable पूर्णांकerrupt */
	sdio_claim_host(sdio->func);
	sdio_ग_लिखोl(sdio->func, WHLPCR_INT_EN_CLR, MCR_WHLPCR, शून्य);

	करो अणु
		nframes = 0;

		/* tx */
		क्रम (i = 0; i <= MT_TXQ_PSD; i++) अणु
			ret = mt7663s_tx_run_queue(dev, dev->phy.q_tx[i]);
			अगर (ret > 0)
				nframes += ret;
		पूर्ण
		ret = mt7663s_tx_run_queue(dev, dev->q_mcu[MT_MCUQ_WM]);
		अगर (ret > 0)
			nframes += ret;

		/* rx */
		ret = mt7663s_rx_handler(dev);
		अगर (ret > 0)
			nframes += ret;
	पूर्ण जबतक (nframes > 0);

	/* enable पूर्णांकerrupt */
	sdio_ग_लिखोl(sdio->func, WHLPCR_INT_EN_SET, MCR_WHLPCR, शून्य);
	sdio_release_host(sdio->func);
पूर्ण

व्योम mt7663s_sdio_irq(काष्ठा sdio_func *func)
अणु
	काष्ठा mt7615_dev *dev = sdio_get_drvdata(func);
	काष्ठा mt76_sdio *sdio = &dev->mt76.sdio;

	अगर (!test_bit(MT76_STATE_INITIALIZED, &dev->mt76.phy.state))
		वापस;

	mt76_worker_schedule(&sdio->txrx_worker);
पूर्ण
