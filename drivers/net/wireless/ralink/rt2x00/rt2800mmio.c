<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*	Copyright (C) 2009 - 2010 Ivo van Doorn <IvDoorn@gmail.com>
 *	Copyright (C) 2009 Alban Browaeys <prahal@yahoo.com>
 *	Copyright (C) 2009 Felix Fietkau <nbd@खोलोwrt.org>
 *	Copyright (C) 2009 Luis Correia <luis.f.correia@gmail.com>
 *	Copyright (C) 2009 Mattias Nissler <mattias.nissler@gmx.de>
 *	Copyright (C) 2009 Mark Asselstine <asselsm@gmail.com>
 *	Copyright (C) 2009 Xose Vazquez Perez <xose.vazquez@gmail.com>
 *	Copyright (C) 2009 Bart Zolnierkiewicz <bzolnier@gmail.com>
 *	<http://rt2x00.serialmonkey.com>
 */

/*	Module: rt2800mmio
 *	Abstract: rt2800 MMIO device routines.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/export.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00mmio.h"
#समावेश "rt2800.h"
#समावेश "rt2800lib.h"
#समावेश "rt2800mmio.h"

अचिन्हित पूर्णांक rt2800mmio_get_dma_करोne(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	काष्ठा queue_entry *entry;
	पूर्णांक idx, qid;

	चयन (queue->qid) अणु
	हाल QID_AC_VO:
	हाल QID_AC_VI:
	हाल QID_AC_BE:
	हाल QID_AC_BK:
		qid = queue->qid;
		idx = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TX_DTX_IDX(qid));
		अवरोध;
	हाल QID_MGMT:
		idx = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TX_DTX_IDX(5));
		अवरोध;
	हाल QID_RX:
		entry = rt2x00queue_get_entry(queue, Q_INDEX_DMA_DONE);
		idx = entry->entry_idx;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		idx = 0;
		अवरोध;
	पूर्ण

	वापस idx;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_get_dma_करोne);

/*
 * TX descriptor initialization
 */
__le32 *rt2800mmio_get_txwi(काष्ठा queue_entry *entry)
अणु
	वापस (__le32 *) entry->skb->data;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_get_txwi);

व्योम rt2800mmio_ग_लिखो_tx_desc(काष्ठा queue_entry *entry,
			      काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	काष्ठा queue_entry_priv_mmio *entry_priv = entry->priv_data;
	__le32 *txd = entry_priv->desc;
	u32 word;
	स्थिर अचिन्हित पूर्णांक txwi_size = entry->queue->winfo_size;

	/*
	 * The buffers poपूर्णांकed by SD_PTR0/SD_LEN0 and SD_PTR1/SD_LEN1
	 * must contains a TXWI काष्ठाure + 802.11 header + padding + 802.11
	 * data. We choose to have SD_PTR0/SD_LEN0 only contains TXWI and
	 * SD_PTR1/SD_LEN1 contains 802.11 header + padding + 802.11
	 * data. It means that LAST_SEC0 is always 0.
	 */

	/*
	 * Initialize TX descriptor
	 */
	word = 0;
	rt2x00_set_field32(&word, TXD_W0_SD_PTR0, skbdesc->skb_dma);
	rt2x00_desc_ग_लिखो(txd, 0, word);

	word = 0;
	rt2x00_set_field32(&word, TXD_W1_SD_LEN1, entry->skb->len);
	rt2x00_set_field32(&word, TXD_W1_LAST_SEC1,
			   !test_bit(ENTRY_TXD_MORE_FRAG, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W1_BURST,
			   test_bit(ENTRY_TXD_BURST, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W1_SD_LEN0, txwi_size);
	rt2x00_set_field32(&word, TXD_W1_LAST_SEC0, 0);
	rt2x00_set_field32(&word, TXD_W1_DMA_DONE, 0);
	rt2x00_desc_ग_लिखो(txd, 1, word);

	word = 0;
	rt2x00_set_field32(&word, TXD_W2_SD_PTR1,
			   skbdesc->skb_dma + txwi_size);
	rt2x00_desc_ग_लिखो(txd, 2, word);

	word = 0;
	rt2x00_set_field32(&word, TXD_W3_WIV,
			   !test_bit(ENTRY_TXD_ENCRYPT_IV, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W3_QSEL, 2);
	rt2x00_desc_ग_लिखो(txd, 3, word);

	/*
	 * Register descriptor details in skb frame descriptor.
	 */
	skbdesc->desc = txd;
	skbdesc->desc_len = TXD_DESC_SIZE;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_ग_लिखो_tx_desc);

/*
 * RX control handlers
 */
व्योम rt2800mmio_fill_rxकरोne(काष्ठा queue_entry *entry,
			    काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
	काष्ठा queue_entry_priv_mmio *entry_priv = entry->priv_data;
	__le32 *rxd = entry_priv->desc;
	u32 word;

	word = rt2x00_desc_पढ़ो(rxd, 3);

	अगर (rt2x00_get_field32(word, RXD_W3_CRC_ERROR))
		rxdesc->flags |= RX_FLAG_FAILED_FCS_CRC;

	/*
	 * Unक्रमtunately we करोn't know the cipher type used during
	 * decryption. This prevents us from correct providing
	 * correct statistics through debugfs.
	 */
	rxdesc->cipher_status = rt2x00_get_field32(word, RXD_W3_CIPHER_ERROR);

	अगर (rt2x00_get_field32(word, RXD_W3_DECRYPTED)) अणु
		/*
		 * Hardware has stripped IV/EIV data from 802.11 frame during
		 * decryption. Unक्रमtunately the descriptor करोesn't contain
		 * any fields with the EIV/IV data either, so they can't
		 * be restored by rt2x00lib.
		 */
		rxdesc->flags |= RX_FLAG_IV_STRIPPED;

		/*
		 * The hardware has alपढ़ोy checked the Michael Mic and has
		 * stripped it from the frame. Signal this to mac80211.
		 */
		rxdesc->flags |= RX_FLAG_MMIC_STRIPPED;

		अगर (rxdesc->cipher_status == RX_CRYPTO_SUCCESS) अणु
			rxdesc->flags |= RX_FLAG_DECRYPTED;
		पूर्ण अन्यथा अगर (rxdesc->cipher_status == RX_CRYPTO_FAIL_MIC) अणु
			/*
			 * In order to check the Michael Mic, the packet must have
			 * been decrypted.  Mac80211 करोesnt check the MMIC failure 
			 * flag to initiate MMIC countermeasures अगर the decoded flag
			 * has not been set.
			 */
			rxdesc->flags |= RX_FLAG_DECRYPTED;

			rxdesc->flags |= RX_FLAG_MMIC_ERROR;
		पूर्ण
	पूर्ण

	अगर (rt2x00_get_field32(word, RXD_W3_MY_BSS))
		rxdesc->dev_flags |= RXDONE_MY_BSS;

	अगर (rt2x00_get_field32(word, RXD_W3_L2PAD))
		rxdesc->dev_flags |= RXDONE_L2PAD;

	/*
	 * Process the RXWI काष्ठाure that is at the start of the buffer.
	 */
	rt2800_process_rxwi(entry, rxdesc);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_fill_rxकरोne);

/*
 * Interrupt functions.
 */
अटल व्योम rt2800mmio_wakeup(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा ieee80211_conf conf = अणु .flags = 0 पूर्ण;
	काष्ठा rt2x00lib_conf libconf = अणु .conf = &conf पूर्ण;

	rt2800_config(rt2x00dev, &libconf, IEEE80211_CONF_CHANGE_PS);
पूर्ण

अटल अंतरभूत व्योम rt2800mmio_enable_पूर्णांकerrupt(काष्ठा rt2x00_dev *rt2x00dev,
					       काष्ठा rt2x00_field32 irq_field)
अणु
	u32 reg;

	/*
	 * Enable a single पूर्णांकerrupt. The पूर्णांकerrupt mask रेजिस्टर
	 * access needs locking.
	 */
	spin_lock_irq(&rt2x00dev->irqmask_lock);
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, INT_MASK_CSR);
	rt2x00_set_field32(&reg, irq_field, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, INT_MASK_CSR, reg);
	spin_unlock_irq(&rt2x00dev->irqmask_lock);
पूर्ण

व्योम rt2800mmio_pretbtt_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = from_tasklet(rt2x00dev, t,
						    pretbtt_tasklet);
	rt2x00lib_pretbtt(rt2x00dev);
	अगर (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt2800mmio_enable_पूर्णांकerrupt(rt2x00dev, INT_MASK_CSR_PRE_TBTT);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_pretbtt_tasklet);

व्योम rt2800mmio_tbtt_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = from_tasklet(rt2x00dev, t, tbtt_tasklet);
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u32 reg;

	rt2x00lib_beaconकरोne(rt2x00dev);

	अगर (rt2x00dev->पूर्णांकf_ap_count) अणु
		/*
		 * The rt2800pci hardware tbtt समयr is off by 1us per tbtt
		 * causing beacon skew and as a result causing problems with
		 * some घातersaving clients over समय. Shorten the beacon
		 * पूर्णांकerval every 64 beacons by 64us to mitigate this effect.
		 */
		अगर (drv_data->tbtt_tick == (BCN_TBTT_OFFSET - 2)) अणु
			reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, BCN_TIME_CFG);
			rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_INTERVAL,
					   (rt2x00dev->beacon_पूर्णांक * 16) - 1);
			rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_TIME_CFG, reg);
		पूर्ण अन्यथा अगर (drv_data->tbtt_tick == (BCN_TBTT_OFFSET - 1)) अणु
			reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, BCN_TIME_CFG);
			rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_INTERVAL,
					   (rt2x00dev->beacon_पूर्णांक * 16));
			rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_TIME_CFG, reg);
		पूर्ण
		drv_data->tbtt_tick++;
		drv_data->tbtt_tick %= BCN_TBTT_OFFSET;
	पूर्ण

	अगर (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt2800mmio_enable_पूर्णांकerrupt(rt2x00dev, INT_MASK_CSR_TBTT);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_tbtt_tasklet);

व्योम rt2800mmio_rxकरोne_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = from_tasklet(rt2x00dev, t,
						    rxकरोne_tasklet);
	अगर (rt2x00mmio_rxकरोne(rt2x00dev))
		tasklet_schedule(&rt2x00dev->rxकरोne_tasklet);
	अन्यथा अगर (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt2800mmio_enable_पूर्णांकerrupt(rt2x00dev, INT_MASK_CSR_RX_DONE);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_rxकरोne_tasklet);

व्योम rt2800mmio_स्वतःwake_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = from_tasklet(rt2x00dev, t,
						    स्वतःwake_tasklet);
	rt2800mmio_wakeup(rt2x00dev);
	अगर (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt2800mmio_enable_पूर्णांकerrupt(rt2x00dev,
					    INT_MASK_CSR_AUTO_WAKEUP);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_स्वतःwake_tasklet);

अटल व्योम rt2800mmio_fetch_txstatus(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 status;
	अचिन्हित दीर्घ flags;

	/*
	 * The TX_FIFO_STATUS पूर्णांकerrupt needs special care. We should
	 * पढ़ो TX_STA_FIFO but we should करो it immediately as otherwise
	 * the रेजिस्टर can overflow and we would lose status reports.
	 *
	 * Hence, पढ़ो the TX_STA_FIFO रेजिस्टर and copy all tx status
	 * reports पूर्णांकo a kernel FIFO which is handled in the txstatus
	 * tasklet. We use a tasklet to process the tx status reports
	 * because we can schedule the tasklet multiple बार (when the
	 * पूर्णांकerrupt fires again during tx status processing).
	 *
	 * We also पढ़ो statuses from tx status समयout समयr, use
	 * lock to prevent concurent ग_लिखोs to fअगरo.
	 */

	spin_lock_irqsave(&rt2x00dev->irqmask_lock, flags);

	जबतक (!kfअगरo_is_full(&rt2x00dev->txstatus_fअगरo)) अणु
		status = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TX_STA_FIFO);
		अगर (!rt2x00_get_field32(status, TX_STA_FIFO_VALID))
			अवरोध;

		kfअगरo_put(&rt2x00dev->txstatus_fअगरo, status);
	पूर्ण

	spin_unlock_irqrestore(&rt2x00dev->irqmask_lock, flags);
पूर्ण

व्योम rt2800mmio_txstatus_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = from_tasklet(rt2x00dev, t,
						    txstatus_tasklet);

	rt2800_txकरोne(rt2x00dev, 16);

	अगर (!kfअगरo_is_empty(&rt2x00dev->txstatus_fअगरo))
		tasklet_schedule(&rt2x00dev->txstatus_tasklet);

पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_txstatus_tasklet);

irqवापस_t rt2800mmio_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = dev_instance;
	u32 reg, mask;

	/* Read status and ACK all पूर्णांकerrupts */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, INT_SOURCE_CSR);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, INT_SOURCE_CSR, reg);

	अगर (!reg)
		वापस IRQ_NONE;

	अगर (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		वापस IRQ_HANDLED;

	/*
	 * Since INT_MASK_CSR and INT_SOURCE_CSR use the same bits
	 * क्रम पूर्णांकerrupts and पूर्णांकerrupt masks we can just use the value of
	 * INT_SOURCE_CSR to create the पूर्णांकerrupt mask.
	 */
	mask = ~reg;

	अगर (rt2x00_get_field32(reg, INT_SOURCE_CSR_TX_FIFO_STATUS)) अणु
		rt2x00_set_field32(&mask, INT_MASK_CSR_TX_FIFO_STATUS, 1);
		rt2800mmio_fetch_txstatus(rt2x00dev);
		अगर (!kfअगरo_is_empty(&rt2x00dev->txstatus_fअगरo))
			tasklet_schedule(&rt2x00dev->txstatus_tasklet);
	पूर्ण

	अगर (rt2x00_get_field32(reg, INT_SOURCE_CSR_PRE_TBTT))
		tasklet_hi_schedule(&rt2x00dev->pretbtt_tasklet);

	अगर (rt2x00_get_field32(reg, INT_SOURCE_CSR_TBTT))
		tasklet_hi_schedule(&rt2x00dev->tbtt_tasklet);

	अगर (rt2x00_get_field32(reg, INT_SOURCE_CSR_RX_DONE))
		tasklet_schedule(&rt2x00dev->rxकरोne_tasklet);

	अगर (rt2x00_get_field32(reg, INT_SOURCE_CSR_AUTO_WAKEUP))
		tasklet_schedule(&rt2x00dev->स्वतःwake_tasklet);

	/*
	 * Disable all पूर्णांकerrupts क्रम which a tasklet was scheduled right now,
	 * the tasklet will reenable the appropriate पूर्णांकerrupts.
	 */
	spin_lock(&rt2x00dev->irqmask_lock);
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, INT_MASK_CSR);
	reg &= mask;
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, INT_MASK_CSR, reg);
	spin_unlock(&rt2x00dev->irqmask_lock);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_पूर्णांकerrupt);

व्योम rt2800mmio_toggle_irq(काष्ठा rt2x00_dev *rt2x00dev,
			   क्रमागत dev_state state)
अणु
	u32 reg;
	अचिन्हित दीर्घ flags;

	/*
	 * When पूर्णांकerrupts are being enabled, the पूर्णांकerrupt रेजिस्टरs
	 * should clear the रेजिस्टर to assure a clean state.
	 */
	अगर (state == STATE_RADIO_IRQ_ON) अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, INT_SOURCE_CSR);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, INT_SOURCE_CSR, reg);
	पूर्ण

	spin_lock_irqsave(&rt2x00dev->irqmask_lock, flags);
	reg = 0;
	अगर (state == STATE_RADIO_IRQ_ON) अणु
		rt2x00_set_field32(&reg, INT_MASK_CSR_RX_DONE, 1);
		rt2x00_set_field32(&reg, INT_MASK_CSR_TBTT, 1);
		rt2x00_set_field32(&reg, INT_MASK_CSR_PRE_TBTT, 1);
		rt2x00_set_field32(&reg, INT_MASK_CSR_TX_FIFO_STATUS, 1);
		rt2x00_set_field32(&reg, INT_MASK_CSR_AUTO_WAKEUP, 1);
	पूर्ण
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, INT_MASK_CSR, reg);
	spin_unlock_irqrestore(&rt2x00dev->irqmask_lock, flags);

	अगर (state == STATE_RADIO_IRQ_OFF) अणु
		/*
		 * Wait क्रम possibly running tasklets to finish.
		 */
		tasklet_समाप्त(&rt2x00dev->txstatus_tasklet);
		tasklet_समाप्त(&rt2x00dev->rxकरोne_tasklet);
		tasklet_समाप्त(&rt2x00dev->स्वतःwake_tasklet);
		tasklet_समाप्त(&rt2x00dev->tbtt_tasklet);
		tasklet_समाप्त(&rt2x00dev->pretbtt_tasklet);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_toggle_irq);

/*
 * Queue handlers.
 */
व्योम rt2800mmio_start_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	चयन (queue->qid) अणु
	हाल QID_RX:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_SYS_CTRL);
		rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_RX, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_SYS_CTRL, reg);
		अवरोध;
	हाल QID_BEACON:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, BCN_TIME_CFG);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_TSF_TICKING, 1);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_TBTT_ENABLE, 1);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_GEN, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_TIME_CFG, reg);

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, INT_TIMER_EN);
		rt2x00_set_field32(&reg, INT_TIMER_EN_PRE_TBTT_TIMER, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, INT_TIMER_EN, reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_start_queue);

/* 200 ms */
#घोषणा TXSTATUS_TIMEOUT 200000000

व्योम rt2800mmio_kick_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	काष्ठा queue_entry *entry;

	चयन (queue->qid) अणु
	हाल QID_AC_VO:
	हाल QID_AC_VI:
	हाल QID_AC_BE:
	हाल QID_AC_BK:
		WARN_ON_ONCE(rt2x00queue_empty(queue));
		entry = rt2x00queue_get_entry(queue, Q_INDEX);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CTX_IDX(queue->qid),
					  entry->entry_idx);
		hrसमयr_start(&rt2x00dev->txstatus_समयr,
			      TXSTATUS_TIMEOUT, HRTIMER_MODE_REL);
		अवरोध;
	हाल QID_MGMT:
		entry = rt2x00queue_get_entry(queue, Q_INDEX);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CTX_IDX(5),
					  entry->entry_idx);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_kick_queue);

व्योम rt2800mmio_flush_queue(काष्ठा data_queue *queue, bool drop)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	bool tx_queue = false;
	अचिन्हित पूर्णांक i;

	चयन (queue->qid) अणु
	हाल QID_AC_VO:
	हाल QID_AC_VI:
	हाल QID_AC_BE:
	हाल QID_AC_BK:
		tx_queue = true;
		अवरोध;
	हाल QID_RX:
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	क्रम (i = 0; i < 5; i++) अणु
		/*
		 * Check अगर the driver is alपढ़ोy करोne, otherwise we
		 * have to sleep a little जबतक to give the driver/hw
		 * the oppurtunity to complete पूर्णांकerrupt process itself.
		 */
		अगर (rt2x00queue_empty(queue))
			अवरोध;

		/*
		 * For TX queues schedule completion tasklet to catch
		 * tx status समयouts, othewise just रुको.
		 */
		अगर (tx_queue)
			queue_work(rt2x00dev->workqueue, &rt2x00dev->txकरोne_work);

		/*
		 * Wait क्रम a little जबतक to give the driver
		 * the oppurtunity to recover itself.
		 */
		msleep(50);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_flush_queue);

व्योम rt2800mmio_stop_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	चयन (queue->qid) अणु
	हाल QID_RX:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_SYS_CTRL);
		rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_RX, 0);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_SYS_CTRL, reg);
		अवरोध;
	हाल QID_BEACON:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, BCN_TIME_CFG);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_TSF_TICKING, 0);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_TBTT_ENABLE, 0);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_GEN, 0);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_TIME_CFG, reg);

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, INT_TIMER_EN);
		rt2x00_set_field32(&reg, INT_TIMER_EN_PRE_TBTT_TIMER, 0);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, INT_TIMER_EN, reg);

		/*
		 * Wait क्रम current invocation to finish. The tasklet
		 * won't be scheduled anymore afterwards since we disabled
		 * the TBTT and PRE TBTT समयr.
		 */
		tasklet_समाप्त(&rt2x00dev->tbtt_tasklet);
		tasklet_समाप्त(&rt2x00dev->pretbtt_tasklet);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_stop_queue);

व्योम rt2800mmio_queue_init(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	अचिन्हित लघु txwi_size, rxwi_size;

	rt2800_get_txwi_rxwi_size(rt2x00dev, &txwi_size, &rxwi_size);

	चयन (queue->qid) अणु
	हाल QID_RX:
		queue->limit = 128;
		queue->data_size = AGGREGATION_SIZE;
		queue->desc_size = RXD_DESC_SIZE;
		queue->winfo_size = rxwi_size;
		queue->priv_size = माप(काष्ठा queue_entry_priv_mmio);
		अवरोध;

	हाल QID_AC_VO:
	हाल QID_AC_VI:
	हाल QID_AC_BE:
	हाल QID_AC_BK:
		queue->limit = 64;
		queue->data_size = AGGREGATION_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->winfo_size = txwi_size;
		queue->priv_size = माप(काष्ठा queue_entry_priv_mmio);
		अवरोध;

	हाल QID_BEACON:
		queue->limit = 8;
		queue->data_size = 0; /* No DMA required क्रम beacons */
		queue->desc_size = TXD_DESC_SIZE;
		queue->winfo_size = txwi_size;
		queue->priv_size = माप(काष्ठा queue_entry_priv_mmio);
		अवरोध;

	हाल QID_ATIM:
	शेष:
		BUG();
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_queue_init);

/*
 * Initialization functions.
 */
bool rt2800mmio_get_entry_state(काष्ठा queue_entry *entry)
अणु
	काष्ठा queue_entry_priv_mmio *entry_priv = entry->priv_data;
	u32 word;

	अगर (entry->queue->qid == QID_RX) अणु
		word = rt2x00_desc_पढ़ो(entry_priv->desc, 1);

		वापस (!rt2x00_get_field32(word, RXD_W1_DMA_DONE));
	पूर्ण अन्यथा अणु
		word = rt2x00_desc_पढ़ो(entry_priv->desc, 1);

		वापस (!rt2x00_get_field32(word, TXD_W1_DMA_DONE));
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_get_entry_state);

व्योम rt2800mmio_clear_entry(काष्ठा queue_entry *entry)
अणु
	काष्ठा queue_entry_priv_mmio *entry_priv = entry->priv_data;
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	u32 word;

	अगर (entry->queue->qid == QID_RX) अणु
		word = rt2x00_desc_पढ़ो(entry_priv->desc, 0);
		rt2x00_set_field32(&word, RXD_W0_SDP0, skbdesc->skb_dma);
		rt2x00_desc_ग_लिखो(entry_priv->desc, 0, word);

		word = rt2x00_desc_पढ़ो(entry_priv->desc, 1);
		rt2x00_set_field32(&word, RXD_W1_DMA_DONE, 0);
		rt2x00_desc_ग_लिखो(entry_priv->desc, 1, word);

		/*
		 * Set RX IDX in रेजिस्टर to inक्रमm hardware that we have
		 * handled this entry and it is available क्रम reuse again.
		 */
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RX_CRX_IDX,
					  entry->entry_idx);
	पूर्ण अन्यथा अणु
		word = rt2x00_desc_पढ़ो(entry_priv->desc, 1);
		rt2x00_set_field32(&word, TXD_W1_DMA_DONE, 1);
		rt2x00_desc_ग_लिखो(entry_priv->desc, 1, word);

		/* If last entry stop txstatus समयr */
		अगर (entry->queue->length == 1)
			hrसमयr_cancel(&rt2x00dev->txstatus_समयr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_clear_entry);

पूर्णांक rt2800mmio_init_queues(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा queue_entry_priv_mmio *entry_priv;

	/*
	 * Initialize रेजिस्टरs.
	 */
	entry_priv = rt2x00dev->tx[0].entries[0].priv_data;
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_BASE_PTR0,
				  entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_MAX_CNT0,
				  rt2x00dev->tx[0].limit);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CTX_IDX0, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_DTX_IDX0, 0);

	entry_priv = rt2x00dev->tx[1].entries[0].priv_data;
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_BASE_PTR1,
				  entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_MAX_CNT1,
				  rt2x00dev->tx[1].limit);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CTX_IDX1, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_DTX_IDX1, 0);

	entry_priv = rt2x00dev->tx[2].entries[0].priv_data;
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_BASE_PTR2,
				  entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_MAX_CNT2,
				  rt2x00dev->tx[2].limit);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CTX_IDX2, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_DTX_IDX2, 0);

	entry_priv = rt2x00dev->tx[3].entries[0].priv_data;
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_BASE_PTR3,
				  entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_MAX_CNT3,
				  rt2x00dev->tx[3].limit);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CTX_IDX3, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_DTX_IDX3, 0);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_BASE_PTR4, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_MAX_CNT4, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CTX_IDX4, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_DTX_IDX4, 0);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_BASE_PTR5, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_MAX_CNT5, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CTX_IDX5, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_DTX_IDX5, 0);

	entry_priv = rt2x00dev->rx->entries[0].priv_data;
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RX_BASE_PTR,
				  entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RX_MAX_CNT,
				  rt2x00dev->rx[0].limit);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RX_CRX_IDX,
				  rt2x00dev->rx[0].limit - 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RX_DRX_IDX, 0);

	rt2800_disable_wpdma(rt2x00dev);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, DELAY_INT_CFG, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_init_queues);

पूर्णांक rt2800mmio_init_रेजिस्टरs(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	/*
	 * Reset DMA indexes
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, WPDMA_RST_IDX);
	rt2x00_set_field32(&reg, WPDMA_RST_IDX_DTX_IDX0, 1);
	rt2x00_set_field32(&reg, WPDMA_RST_IDX_DTX_IDX1, 1);
	rt2x00_set_field32(&reg, WPDMA_RST_IDX_DTX_IDX2, 1);
	rt2x00_set_field32(&reg, WPDMA_RST_IDX_DTX_IDX3, 1);
	rt2x00_set_field32(&reg, WPDMA_RST_IDX_DTX_IDX4, 1);
	rt2x00_set_field32(&reg, WPDMA_RST_IDX_DTX_IDX5, 1);
	rt2x00_set_field32(&reg, WPDMA_RST_IDX_DRX_IDX0, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, WPDMA_RST_IDX, reg);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PBF_SYS_CTRL, 0x00000e1f);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PBF_SYS_CTRL, 0x00000e00);

	अगर (rt2x00_is_pcie(rt2x00dev) &&
	    (rt2x00_rt(rt2x00dev, RT3090) ||
	     rt2x00_rt(rt2x00dev, RT3390) ||
	     rt2x00_rt(rt2x00dev, RT3572) ||
	     rt2x00_rt(rt2x00dev, RT3593) ||
	     rt2x00_rt(rt2x00dev, RT5390) ||
	     rt2x00_rt(rt2x00dev, RT5392) ||
	     rt2x00_rt(rt2x00dev, RT5592))) अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, AUX_CTRL);
		rt2x00_set_field32(&reg, AUX_CTRL_FORCE_PCIE_CLK, 1);
		rt2x00_set_field32(&reg, AUX_CTRL_WAKE_PCIE_EN, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, AUX_CTRL, reg);
	पूर्ण

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PWR_PIN_CFG, 0x00000003);

	reg = 0;
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_RESET_CSR, 1);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_RESET_BBP, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_SYS_CTRL, reg);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_SYS_CTRL, 0x00000000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_init_रेजिस्टरs);

/*
 * Device state चयन handlers.
 */
पूर्णांक rt2800mmio_enable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	/* Wait क्रम DMA, ignore error until we initialize queues. */
	rt2800_रुको_wpdma_पढ़ोy(rt2x00dev);

	अगर (unlikely(rt2800mmio_init_queues(rt2x00dev)))
		वापस -EIO;

	वापस rt2800_enable_radio(rt2x00dev);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_enable_radio);

अटल व्योम rt2800mmio_work_txकरोne(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt2x00_dev *rt2x00dev =
	    container_of(work, काष्ठा rt2x00_dev, txकरोne_work);

	अगर (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		वापस;

	जबतक (!kfअगरo_is_empty(&rt2x00dev->txstatus_fअगरo) ||
	       rt2800_txstatus_समयout(rt2x00dev)) अणु

		tasklet_disable(&rt2x00dev->txstatus_tasklet);
		rt2800_txकरोne(rt2x00dev, अच_पूर्णांक_उच्च);
		rt2800_txकरोne_nostatus(rt2x00dev);
		tasklet_enable(&rt2x00dev->txstatus_tasklet);
	पूर्ण

	अगर (rt2800_txstatus_pending(rt2x00dev))
		hrसमयr_start(&rt2x00dev->txstatus_समयr,
			      TXSTATUS_TIMEOUT, HRTIMER_MODE_REL);
पूर्ण

अटल क्रमागत hrसमयr_restart rt2800mmio_tx_sta_fअगरo_समयout(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा rt2x00_dev *rt2x00dev =
	    container_of(समयr, काष्ठा rt2x00_dev, txstatus_समयr);

	अगर (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		जाओ out;

	अगर (!rt2800_txstatus_pending(rt2x00dev))
		जाओ out;

	rt2800mmio_fetch_txstatus(rt2x00dev);
	अगर (!kfअगरo_is_empty(&rt2x00dev->txstatus_fअगरo))
		tasklet_schedule(&rt2x00dev->txstatus_tasklet);
	अन्यथा
		queue_work(rt2x00dev->workqueue, &rt2x00dev->txकरोne_work);
out:
	वापस HRTIMER_NORESTART;
पूर्ण

पूर्णांक rt2800mmio_probe_hw(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक retval;

	retval = rt2800_probe_hw(rt2x00dev);
	अगर (retval)
		वापस retval;

	/*
	 * Set txstatus समयr function.
	 */
	rt2x00dev->txstatus_समयr.function = rt2800mmio_tx_sta_fअगरo_समयout;

	/*
	 * Overग_लिखो TX करोne handler
	 */
	INIT_WORK(&rt2x00dev->txकरोne_work, rt2800mmio_work_txकरोne);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800mmio_probe_hw);

MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("rt2800 MMIO library");
MODULE_LICENSE("GPL");
