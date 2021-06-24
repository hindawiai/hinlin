<शैली गुरु>
/*
 * Copyright (c) 2004-2008 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2006-2008 Nick Kossअगरidis <mickflemm@gmail.com>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/*************************************\
* DMA and पूर्णांकerrupt masking functions *
\*************************************/

/**
 * DOC: DMA and पूर्णांकerrupt masking functions
 *
 * Here we setup descriptor poपूर्णांकers (rxdp/txdp) start/stop dma engine and
 * handle queue setup क्रम 5210 chipset (rest are handled on qcu.c).
 * Also we setup पूर्णांकerrupt mask रेजिस्टर (IMR) and पढ़ो the various पूर्णांकerrupt
 * status रेजिस्टरs (ISR).
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "ath5k.h"
#समावेश "reg.h"
#समावेश "debug.h"


/*********\
* Receive *
\*********/

/**
 * ath5k_hw_start_rx_dma() - Start DMA receive
 * @ah:	The &काष्ठा ath5k_hw
 */
व्योम
ath5k_hw_start_rx_dma(काष्ठा ath5k_hw *ah)
अणु
	ath5k_hw_reg_ग_लिखो(ah, AR5K_CR_RXE, AR5K_CR);
	ath5k_hw_reg_पढ़ो(ah, AR5K_CR);
पूर्ण

/**
 * ath5k_hw_stop_rx_dma() - Stop DMA receive
 * @ah:	The &काष्ठा ath5k_hw
 */
अटल पूर्णांक
ath5k_hw_stop_rx_dma(काष्ठा ath5k_hw *ah)
अणु
	अचिन्हित पूर्णांक i;

	ath5k_hw_reg_ग_लिखो(ah, AR5K_CR_RXD, AR5K_CR);

	/*
	 * It may take some समय to disable the DMA receive unit
	 */
	क्रम (i = 1000; i > 0 &&
			(ath5k_hw_reg_पढ़ो(ah, AR5K_CR) & AR5K_CR_RXE) != 0;
			i--)
		udelay(100);

	अगर (!i)
		ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
				"failed to stop RX DMA !\n");

	वापस i ? 0 : -EBUSY;
पूर्ण

/**
 * ath5k_hw_get_rxdp() - Get RX Descriptor's address
 * @ah: The &काष्ठा ath5k_hw
 */
u32
ath5k_hw_get_rxdp(काष्ठा ath5k_hw *ah)
अणु
	वापस ath5k_hw_reg_पढ़ो(ah, AR5K_RXDP);
पूर्ण

/**
 * ath5k_hw_set_rxdp() - Set RX Descriptor's address
 * @ah: The &काष्ठा ath5k_hw
 * @phys_addr: RX descriptor address
 *
 * Returns -EIO अगर rx is active
 */
पूर्णांक
ath5k_hw_set_rxdp(काष्ठा ath5k_hw *ah, u32 phys_addr)
अणु
	अगर (ath5k_hw_reg_पढ़ो(ah, AR5K_CR) & AR5K_CR_RXE) अणु
		ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
				"tried to set RXDP while rx was active !\n");
		वापस -EIO;
	पूर्ण

	ath5k_hw_reg_ग_लिखो(ah, phys_addr, AR5K_RXDP);
	वापस 0;
पूर्ण


/**********\
* Transmit *
\**********/

/**
 * ath5k_hw_start_tx_dma() - Start DMA transmit क्रम a specअगरic queue
 * @ah: The &काष्ठा ath5k_hw
 * @queue: The hw queue number
 *
 * Start DMA transmit क्रम a specअगरic queue and since 5210 करोesn't have
 * QCU/DCU, set up queue parameters क्रम 5210 here based on queue type (one
 * queue क्रम normal data and one queue क्रम beacons). For queue setup
 * on newer chips check out qcu.c. Returns -EINVAL अगर queue number is out
 * of range or अगर queue is alपढ़ोy disabled.
 *
 * NOTE: Must be called after setting up tx control descriptor क्रम that
 * queue (see below).
 */
पूर्णांक
ath5k_hw_start_tx_dma(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue)
अणु
	u32 tx_queue;

	AR5K_ASSERT_ENTRY(queue, ah->ah_capabilities.cap_queues.q_tx_num);

	/* Return अगर queue is declared inactive */
	अगर (ah->ah_txq[queue].tqi_type == AR5K_TX_QUEUE_INACTIVE)
		वापस -EINVAL;

	अगर (ah->ah_version == AR5K_AR5210) अणु
		tx_queue = ath5k_hw_reg_पढ़ो(ah, AR5K_CR);

		/*
		 * Set the queue by type on 5210
		 */
		चयन (ah->ah_txq[queue].tqi_type) अणु
		हाल AR5K_TX_QUEUE_DATA:
			tx_queue |= AR5K_CR_TXE0 & ~AR5K_CR_TXD0;
			अवरोध;
		हाल AR5K_TX_QUEUE_BEACON:
			tx_queue |= AR5K_CR_TXE1 & ~AR5K_CR_TXD1;
			ath5k_hw_reg_ग_लिखो(ah, AR5K_BCR_TQ1V | AR5K_BCR_BDMAE,
					AR5K_BSR);
			अवरोध;
		हाल AR5K_TX_QUEUE_CAB:
			tx_queue |= AR5K_CR_TXE1 & ~AR5K_CR_TXD1;
			ath5k_hw_reg_ग_लिखो(ah, AR5K_BCR_TQ1FV | AR5K_BCR_TQ1V |
				AR5K_BCR_BDMAE, AR5K_BSR);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		/* Start queue */
		ath5k_hw_reg_ग_लिखो(ah, tx_queue, AR5K_CR);
		ath5k_hw_reg_पढ़ो(ah, AR5K_CR);
	पूर्ण अन्यथा अणु
		/* Return अगर queue is disabled */
		अगर (AR5K_REG_READ_Q(ah, AR5K_QCU_TXD, queue))
			वापस -EIO;

		/* Start queue */
		AR5K_REG_WRITE_Q(ah, AR5K_QCU_TXE, queue);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ath5k_hw_stop_tx_dma() - Stop DMA transmit on a specअगरic queue
 * @ah: The &काष्ठा ath5k_hw
 * @queue: The hw queue number
 *
 * Stop DMA transmit on a specअगरic hw queue and drain queue so we करोn't
 * have any pending frames. Returns -EBUSY अगर we still have pending frames,
 * -EINVAL अगर queue number is out of range or inactive.
 */
अटल पूर्णांक
ath5k_hw_stop_tx_dma(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक i = 40;
	u32 tx_queue, pending;

	AR5K_ASSERT_ENTRY(queue, ah->ah_capabilities.cap_queues.q_tx_num);

	/* Return अगर queue is declared inactive */
	अगर (ah->ah_txq[queue].tqi_type == AR5K_TX_QUEUE_INACTIVE)
		वापस -EINVAL;

	अगर (ah->ah_version == AR5K_AR5210) अणु
		tx_queue = ath5k_hw_reg_पढ़ो(ah, AR5K_CR);

		/*
		 * Set by queue type
		 */
		चयन (ah->ah_txq[queue].tqi_type) अणु
		हाल AR5K_TX_QUEUE_DATA:
			tx_queue |= AR5K_CR_TXD0 & ~AR5K_CR_TXE0;
			अवरोध;
		हाल AR5K_TX_QUEUE_BEACON:
		हाल AR5K_TX_QUEUE_CAB:
			/* XXX Fix me... */
			tx_queue |= AR5K_CR_TXD1 & ~AR5K_CR_TXD1;
			ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_BSR);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		/* Stop queue */
		ath5k_hw_reg_ग_लिखो(ah, tx_queue, AR5K_CR);
		ath5k_hw_reg_पढ़ो(ah, AR5K_CR);
	पूर्ण अन्यथा अणु

		/*
		 * Enable DCU early termination to quickly
		 * flush any pending frames from QCU
		 */
		AR5K_REG_ENABLE_BITS(ah, AR5K_QUEUE_MISC(queue),
					AR5K_QCU_MISC_DCU_EARLY);

		/*
		 * Schedule TX disable and रुको until queue is empty
		 */
		AR5K_REG_WRITE_Q(ah, AR5K_QCU_TXD, queue);

		/* Wait क्रम queue to stop */
		क्रम (i = 1000; i > 0 &&
		(AR5K_REG_READ_Q(ah, AR5K_QCU_TXE, queue) != 0);
		i--)
			udelay(100);

		अगर (AR5K_REG_READ_Q(ah, AR5K_QCU_TXE, queue))
			ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
				"queue %i didn't stop !\n", queue);

		/* Check क्रम pending frames */
		i = 1000;
		करो अणु
			pending = ath5k_hw_reg_पढ़ो(ah,
				AR5K_QUEUE_STATUS(queue)) &
				AR5K_QCU_STS_FRMPENDCNT;
			udelay(100);
		पूर्ण जबतक (--i && pending);

		/* For 2413+ order PCU to drop packets using
		 * QUIET mechanism */
		अगर (ah->ah_mac_version >= (AR5K_SREV_AR2414 >> 4) &&
		    pending) अणु
			/* Set periodicity and duration */
			ath5k_hw_reg_ग_लिखो(ah,
				AR5K_REG_SM(100, AR5K_QUIET_CTL2_QT_PER)|
				AR5K_REG_SM(10, AR5K_QUIET_CTL2_QT_DUR),
				AR5K_QUIET_CTL2);

			/* Enable quiet period क्रम current TSF */
			ath5k_hw_reg_ग_लिखो(ah,
				AR5K_QUIET_CTL1_QT_EN |
				AR5K_REG_SM(ath5k_hw_reg_पढ़ो(ah,
						AR5K_TSF_L32_5211) >> 10,
						AR5K_QUIET_CTL1_NEXT_QT_TSF),
				AR5K_QUIET_CTL1);

			/* Force channel idle high */
			AR5K_REG_ENABLE_BITS(ah, AR5K_DIAG_SW_5211,
					AR5K_DIAG_SW_CHANNEL_IDLE_HIGH);

			/* Wait a जबतक and disable mechanism */
			udelay(400);
			AR5K_REG_DISABLE_BITS(ah, AR5K_QUIET_CTL1,
						AR5K_QUIET_CTL1_QT_EN);

			/* Re-check क्रम pending frames */
			i = 100;
			करो अणु
				pending = ath5k_hw_reg_पढ़ो(ah,
					AR5K_QUEUE_STATUS(queue)) &
					AR5K_QCU_STS_FRMPENDCNT;
				udelay(100);
			पूर्ण जबतक (--i && pending);

			AR5K_REG_DISABLE_BITS(ah, AR5K_DIAG_SW_5211,
					AR5K_DIAG_SW_CHANNEL_IDLE_HIGH);

			अगर (pending)
				ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
					"quiet mechanism didn't work q:%i !\n",
					queue);
		पूर्ण

		/*
		 * Disable DCU early termination
		 */
		AR5K_REG_DISABLE_BITS(ah, AR5K_QUEUE_MISC(queue),
					AR5K_QCU_MISC_DCU_EARLY);

		/* Clear रेजिस्टर */
		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_QCU_TXD);
		अगर (pending) अणु
			ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
					"tx dma didn't stop (q:%i, frm:%i) !\n",
					queue, pending);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* TODO: Check क्रम success on 5210 अन्यथा वापस error */
	वापस 0;
पूर्ण

/**
 * ath5k_hw_stop_beacon_queue() - Stop beacon queue
 * @ah: The &काष्ठा ath5k_hw
 * @queue: The queue number
 *
 * Returns -EIO अगर queue didn't stop
 */
पूर्णांक
ath5k_hw_stop_beacon_queue(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue)
अणु
	पूर्णांक ret;
	ret = ath5k_hw_stop_tx_dma(ah, queue);
	अगर (ret) अणु
		ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
				"beacon queue didn't stop !\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ath5k_hw_get_txdp() - Get TX Descriptor's address क्रम a specअगरic queue
 * @ah: The &काष्ठा ath5k_hw
 * @queue: The hw queue number
 *
 * Get TX descriptor's address क्रम a specअगरic queue. For 5210 we ignore
 * the queue number and use tx queue type since we only have 2 queues.
 * We use TXDP0 क्रम normal data queue and TXDP1 क्रम beacon queue.
 * For newer chips with QCU/DCU we just पढ़ो the corresponding TXDP रेजिस्टर.
 *
 * XXX: Is TXDP पढ़ो and clear ?
 */
u32
ath5k_hw_get_txdp(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue)
अणु
	u16 tx_reg;

	AR5K_ASSERT_ENTRY(queue, ah->ah_capabilities.cap_queues.q_tx_num);

	/*
	 * Get the transmit queue descriptor poपूर्णांकer from the selected queue
	 */
	/*5210 करोesn't have QCU*/
	अगर (ah->ah_version == AR5K_AR5210) अणु
		चयन (ah->ah_txq[queue].tqi_type) अणु
		हाल AR5K_TX_QUEUE_DATA:
			tx_reg = AR5K_NOQCU_TXDP0;
			अवरोध;
		हाल AR5K_TX_QUEUE_BEACON:
		हाल AR5K_TX_QUEUE_CAB:
			tx_reg = AR5K_NOQCU_TXDP1;
			अवरोध;
		शेष:
			वापस 0xffffffff;
		पूर्ण
	पूर्ण अन्यथा अणु
		tx_reg = AR5K_QUEUE_TXDP(queue);
	पूर्ण

	वापस ath5k_hw_reg_पढ़ो(ah, tx_reg);
पूर्ण

/**
 * ath5k_hw_set_txdp() - Set TX Descriptor's address क्रम a specअगरic queue
 * @ah: The &काष्ठा ath5k_hw
 * @queue: The hw queue number
 * @phys_addr: The physical address
 *
 * Set TX descriptor's address क्रम a specअगरic queue. For 5210 we ignore
 * the queue number and we use tx queue type since we only have 2 queues
 * so as above we use TXDP0 क्रम normal data queue and TXDP1 क्रम beacon queue.
 * For newer chips with QCU/DCU we just set the corresponding TXDP रेजिस्टर.
 * Returns -EINVAL अगर queue type is invalid क्रम 5210 and -EIO अगर queue is still
 * active.
 */
पूर्णांक
ath5k_hw_set_txdp(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue, u32 phys_addr)
अणु
	u16 tx_reg;

	AR5K_ASSERT_ENTRY(queue, ah->ah_capabilities.cap_queues.q_tx_num);

	/*
	 * Set the transmit queue descriptor poपूर्णांकer रेजिस्टर by type
	 * on 5210
	 */
	अगर (ah->ah_version == AR5K_AR5210) अणु
		चयन (ah->ah_txq[queue].tqi_type) अणु
		हाल AR5K_TX_QUEUE_DATA:
			tx_reg = AR5K_NOQCU_TXDP0;
			अवरोध;
		हाल AR5K_TX_QUEUE_BEACON:
		हाल AR5K_TX_QUEUE_CAB:
			tx_reg = AR5K_NOQCU_TXDP1;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Set the transmit queue descriptor poपूर्णांकer क्रम
		 * the selected queue on QCU क्रम 5211+
		 * (this won't work अगर the queue is still active)
		 */
		अगर (AR5K_REG_READ_Q(ah, AR5K_QCU_TXE, queue))
			वापस -EIO;

		tx_reg = AR5K_QUEUE_TXDP(queue);
	पूर्ण

	/* Set descriptor poपूर्णांकer */
	ath5k_hw_reg_ग_लिखो(ah, phys_addr, tx_reg);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_update_tx_triglevel() - Update tx trigger level
 * @ah: The &काष्ठा ath5k_hw
 * @increase: Flag to क्रमce increase of trigger level
 *
 * This function increases/decreases the tx trigger level क्रम the tx fअगरo
 * buffer (aka FIFO threshold) that is used to indicate when PCU flushes
 * the buffer and transmits its data. Lowering this results sending small
 * frames more quickly but can lead to tx underruns, raising it a lot can
 * result other problems. Right now we start with the lowest possible
 * (64Bytes) and अगर we get tx underrun we increase it using the increase
 * flag. Returns -EIO अगर we have reached maximum/minimum.
 *
 * XXX: Link this with tx DMA size ?
 * XXX2: Use it to save पूर्णांकerrupts ?
 */
पूर्णांक
ath5k_hw_update_tx_triglevel(काष्ठा ath5k_hw *ah, bool increase)
अणु
	u32 trigger_level, imr;
	पूर्णांक ret = -EIO;

	/*
	 * Disable पूर्णांकerrupts by setting the mask
	 */
	imr = ath5k_hw_set_imr(ah, ah->ah_imr & ~AR5K_INT_GLOBAL);

	trigger_level = AR5K_REG_MS(ath5k_hw_reg_पढ़ो(ah, AR5K_TXCFG),
			AR5K_TXCFG_TXFULL);

	अगर (!increase) अणु
		अगर (--trigger_level < AR5K_TUNE_MIN_TX_FIFO_THRES)
			जाओ करोne;
	पूर्ण अन्यथा
		trigger_level +=
			((AR5K_TUNE_MAX_TX_FIFO_THRES - trigger_level) / 2);

	/*
	 * Update trigger level on success
	 */
	अगर (ah->ah_version == AR5K_AR5210)
		ath5k_hw_reg_ग_लिखो(ah, trigger_level, AR5K_TRIG_LVL);
	अन्यथा
		AR5K_REG_WRITE_BITS(ah, AR5K_TXCFG,
				AR5K_TXCFG_TXFULL, trigger_level);

	ret = 0;

करोne:
	/*
	 * Restore पूर्णांकerrupt mask
	 */
	ath5k_hw_set_imr(ah, imr);

	वापस ret;
पूर्ण


/*******************\
* Interrupt masking *
\*******************/

/**
 * ath5k_hw_is_पूर्णांकr_pending() - Check अगर we have pending पूर्णांकerrupts
 * @ah: The &काष्ठा ath5k_hw
 *
 * Check अगर we have pending पूर्णांकerrupts to process. Returns 1 अगर we
 * have pending पूर्णांकerrupts and 0 अगर we haven't.
 */
bool
ath5k_hw_is_पूर्णांकr_pending(काष्ठा ath5k_hw *ah)
अणु
	वापस ath5k_hw_reg_पढ़ो(ah, AR5K_INTPEND) == 1 ? 1 : 0;
पूर्ण

/**
 * ath5k_hw_get_isr() - Get पूर्णांकerrupt status
 * @ah: The @काष्ठा ath5k_hw
 * @पूर्णांकerrupt_mask: Driver's पूर्णांकerrupt mask used to filter out
 * पूर्णांकerrupts in sw.
 *
 * This function is used inside our पूर्णांकerrupt handler to determine the reason
 * क्रम the पूर्णांकerrupt by पढ़ोing Primary Interrupt Status Register. Returns an
 * असलtract पूर्णांकerrupt status mask which is mostly ISR with some uncommon bits
 * being mapped on some standard non hw-specअगरic positions
 * (check out &ath5k_पूर्णांक).
 *
 * NOTE: We करो ग_लिखो-to-clear, so the active PISR/SISR bits at the समय this
 * function माला_लो called are cleared on वापस.
 */
पूर्णांक
ath5k_hw_get_isr(काष्ठा ath5k_hw *ah, क्रमागत ath5k_पूर्णांक *पूर्णांकerrupt_mask)
अणु
	u32 data = 0;

	/*
	 * Read पूर्णांकerrupt status from Primary Interrupt
	 * Register.
	 *
	 * Note: PISR/SISR Not available on 5210
	 */
	अगर (ah->ah_version == AR5K_AR5210) अणु
		u32 isr = 0;
		isr = ath5k_hw_reg_पढ़ो(ah, AR5K_ISR);
		अगर (unlikely(isr == AR5K_INT_NOCARD)) अणु
			*पूर्णांकerrupt_mask = isr;
			वापस -ENODEV;
		पूर्ण

		/*
		 * Filter out the non-common bits from the पूर्णांकerrupt
		 * status.
		 */
		*पूर्णांकerrupt_mask = (isr & AR5K_INT_COMMON) & ah->ah_imr;

		/* Hanlde INT_FATAL */
		अगर (unlikely(isr & (AR5K_ISR_SSERR | AR5K_ISR_MCABT
						| AR5K_ISR_DPERR)))
			*पूर्णांकerrupt_mask |= AR5K_INT_FATAL;

		/*
		 * XXX: BMISS पूर्णांकerrupts may occur after association.
		 * I found this on 5210 code but it needs testing. If this is
		 * true we should disable them beक्रमe assoc and re-enable them
		 * after a successful assoc + some jअगरfies.
			पूर्णांकerrupt_mask &= ~AR5K_INT_BMISS;
		 */

		data = isr;
	पूर्ण अन्यथा अणु
		u32 pisr = 0;
		u32 pisr_clear = 0;
		u32 sisr0 = 0;
		u32 sisr1 = 0;
		u32 sisr2 = 0;
		u32 sisr3 = 0;
		u32 sisr4 = 0;

		/* Read PISR and SISRs... */
		pisr = ath5k_hw_reg_पढ़ो(ah, AR5K_PISR);
		अगर (unlikely(pisr == AR5K_INT_NOCARD)) अणु
			*पूर्णांकerrupt_mask = pisr;
			वापस -ENODEV;
		पूर्ण

		sisr0 = ath5k_hw_reg_पढ़ो(ah, AR5K_SISR0);
		sisr1 = ath5k_hw_reg_पढ़ो(ah, AR5K_SISR1);
		sisr2 = ath5k_hw_reg_पढ़ो(ah, AR5K_SISR2);
		sisr3 = ath5k_hw_reg_पढ़ो(ah, AR5K_SISR3);
		sisr4 = ath5k_hw_reg_पढ़ो(ah, AR5K_SISR4);

		/*
		 * PISR holds the logical OR of पूर्णांकerrupt bits
		 * from SISR रेजिस्टरs:
		 *
		 * TXOK and TXDESC  -> Logical OR of TXOK and TXDESC
		 *			per-queue bits on SISR0
		 *
		 * TXERR and TXEOL -> Logical OR of TXERR and TXEOL
		 *			per-queue bits on SISR1
		 *
		 * TXURN -> Logical OR of TXURN per-queue bits on SISR2
		 *
		 * HIUERR -> Logical OR of MCABT, SSERR and DPER bits on SISR2
		 *
		 * BCNMISC -> Logical OR of TIM, CAB_END, DTIM_SYNC
		 *		BCN_TIMEOUT, CAB_TIMEOUT and DTIM
		 *		(and TSFOOR ?) bits on SISR2
		 *
		 * QCBRORN and QCBRURN -> Logical OR of QCBRORN and
		 *			QCBRURN per-queue bits on SISR3
		 * QTRIG -> Logical OR of QTRIG per-queue bits on SISR4
		 *
		 * If we clean these bits on PISR we 'll also clear all
		 * related bits from SISRs, e.g. अगर we ग_लिखो the TXOK bit on
		 * PISR we 'll clean all TXOK bits from SISR0 so अगर a new TXOK
		 * पूर्णांकerrupt got fired क्रम another queue जबतक we were पढ़ोing
		 * the पूर्णांकerrupt रेजिस्टरs and we ग_लिखो back the TXOK bit on
		 * PISR we 'll lose it. So make sure that we don't ग_लिखो back
		 * on PISR any bits that come from SISRs. Clearing them from
		 * SISRs will also clear PISR so no need to worry here.
		 */

		/* XXX: There seems to be  an issue on some cards
		 *	with tx पूर्णांकerrupt flags not being updated
		 *	on PISR despite that all Tx पूर्णांकerrupt bits
		 * 	are cleared on SISRs. Since we handle all
		 *	Tx queues all together it shouldn't be an
		 *	issue अगर we clear Tx पूर्णांकerrupt flags also
		 * 	on PISR to aव्योम that.
		 */
		pisr_clear = (pisr & ~AR5K_ISR_BITS_FROM_SISRS) |
					(pisr & AR5K_INT_TX_ALL);

		/*
		 * Write to clear them...
		 * Note: This means that each bit we ग_लिखो back
		 * to the रेजिस्टरs will get cleared, leaving the
		 * rest unaffected. So this won't affect new पूर्णांकerrupts
		 * we didn't catch while reading/processing, we 'll get
		 * them next समय get_isr माला_लो called.
		 */
		ath5k_hw_reg_ग_लिखो(ah, sisr0, AR5K_SISR0);
		ath5k_hw_reg_ग_लिखो(ah, sisr1, AR5K_SISR1);
		ath5k_hw_reg_ग_लिखो(ah, sisr2, AR5K_SISR2);
		ath5k_hw_reg_ग_लिखो(ah, sisr3, AR5K_SISR3);
		ath5k_hw_reg_ग_लिखो(ah, sisr4, AR5K_SISR4);
		ath5k_hw_reg_ग_लिखो(ah, pisr_clear, AR5K_PISR);
		/* Flush previous ग_लिखो */
		ath5k_hw_reg_पढ़ो(ah, AR5K_PISR);

		/*
		 * Filter out the non-common bits from the पूर्णांकerrupt
		 * status.
		 */
		*पूर्णांकerrupt_mask = (pisr & AR5K_INT_COMMON) & ah->ah_imr;


		/* We treat TXOK,TXDESC, TXERR and TXEOL
		 * the same way (schedule the tx tasklet)
		 * so we track them all together per queue */
		अगर (pisr & AR5K_ISR_TXOK)
			ah->ah_txq_isr_txok_all |= AR5K_REG_MS(sisr0,
						AR5K_SISR0_QCU_TXOK);

		अगर (pisr & AR5K_ISR_TXDESC)
			ah->ah_txq_isr_txok_all |= AR5K_REG_MS(sisr0,
						AR5K_SISR0_QCU_TXDESC);

		अगर (pisr & AR5K_ISR_TXERR)
			ah->ah_txq_isr_txok_all |= AR5K_REG_MS(sisr1,
						AR5K_SISR1_QCU_TXERR);

		अगर (pisr & AR5K_ISR_TXEOL)
			ah->ah_txq_isr_txok_all |= AR5K_REG_MS(sisr1,
						AR5K_SISR1_QCU_TXEOL);

		/* Currently this is not much useful since we treat
		 * all queues the same way अगर we get a TXURN (update
		 * tx trigger level) but we might need it later on*/
		अगर (pisr & AR5K_ISR_TXURN)
			ah->ah_txq_isr_txurn |= AR5K_REG_MS(sisr2,
						AR5K_SISR2_QCU_TXURN);

		/* Misc Beacon related पूर्णांकerrupts */

		/* For AR5211 */
		अगर (pisr & AR5K_ISR_TIM)
			*पूर्णांकerrupt_mask |= AR5K_INT_TIM;

		/* For AR5212+ */
		अगर (pisr & AR5K_ISR_BCNMISC) अणु
			अगर (sisr2 & AR5K_SISR2_TIM)
				*पूर्णांकerrupt_mask |= AR5K_INT_TIM;
			अगर (sisr2 & AR5K_SISR2_DTIM)
				*पूर्णांकerrupt_mask |= AR5K_INT_DTIM;
			अगर (sisr2 & AR5K_SISR2_DTIM_SYNC)
				*पूर्णांकerrupt_mask |= AR5K_INT_DTIM_SYNC;
			अगर (sisr2 & AR5K_SISR2_BCN_TIMEOUT)
				*पूर्णांकerrupt_mask |= AR5K_INT_BCN_TIMEOUT;
			अगर (sisr2 & AR5K_SISR2_CAB_TIMEOUT)
				*पूर्णांकerrupt_mask |= AR5K_INT_CAB_TIMEOUT;
		पूर्ण

		/* Below पूर्णांकerrupts are unlikely to happen */

		/* HIU = Host Interface Unit (PCI etc)
		 * Can be one of MCABT, SSERR, DPERR from SISR2 */
		अगर (unlikely(pisr & (AR5K_ISR_HIUERR)))
			*पूर्णांकerrupt_mask |= AR5K_INT_FATAL;

		/*Beacon Not Ready*/
		अगर (unlikely(pisr & (AR5K_ISR_BNR)))
			*पूर्णांकerrupt_mask |= AR5K_INT_BNR;

		/* A queue got CBR overrun */
		अगर (unlikely(pisr & (AR5K_ISR_QCBRORN))) अणु
			*पूर्णांकerrupt_mask |= AR5K_INT_QCBRORN;
			ah->ah_txq_isr_qcborn |= AR5K_REG_MS(sisr3,
						AR5K_SISR3_QCBRORN);
		पूर्ण

		/* A queue got CBR underrun */
		अगर (unlikely(pisr & (AR5K_ISR_QCBRURN))) अणु
			*पूर्णांकerrupt_mask |= AR5K_INT_QCBRURN;
			ah->ah_txq_isr_qcburn |= AR5K_REG_MS(sisr3,
						AR5K_SISR3_QCBRURN);
		पूर्ण

		/* A queue got triggered */
		अगर (unlikely(pisr & (AR5K_ISR_QTRIG))) अणु
			*पूर्णांकerrupt_mask |= AR5K_INT_QTRIG;
			ah->ah_txq_isr_qtrig |= AR5K_REG_MS(sisr4,
						AR5K_SISR4_QTRIG);
		पूर्ण

		data = pisr;
	पूर्ण

	/*
	 * In हाल we didn't handle anything,
	 * prपूर्णांक the रेजिस्टर value.
	 */
	अगर (unlikely(*पूर्णांकerrupt_mask == 0 && net_ratelimit()))
		ATH5K_PRINTF("ISR: 0x%08x IMR: 0x%08x\n", data, ah->ah_imr);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_set_imr() - Set पूर्णांकerrupt mask
 * @ah: The &काष्ठा ath5k_hw
 * @new_mask: The new पूर्णांकerrupt mask to be set
 *
 * Set the पूर्णांकerrupt mask in hw to save पूर्णांकerrupts. We करो that by mapping
 * ath5k_पूर्णांक bits to hw-specअगरic bits to हटाओ असलtraction and writing
 * Interrupt Mask Register.
 */
क्रमागत ath5k_पूर्णांक
ath5k_hw_set_imr(काष्ठा ath5k_hw *ah, क्रमागत ath5k_पूर्णांक new_mask)
अणु
	क्रमागत ath5k_पूर्णांक old_mask, पूर्णांक_mask;

	old_mask = ah->ah_imr;

	/*
	 * Disable card पूर्णांकerrupts to prevent any race conditions
	 * (they will be re-enabled afterwards अगर AR5K_INT GLOBAL
	 * is set again on the new mask).
	 */
	अगर (old_mask & AR5K_INT_GLOBAL) अणु
		ath5k_hw_reg_ग_लिखो(ah, AR5K_IER_DISABLE, AR5K_IER);
		ath5k_hw_reg_पढ़ो(ah, AR5K_IER);
	पूर्ण

	/*
	 * Add additional, chipset-dependent पूर्णांकerrupt mask flags
	 * and ग_लिखो them to the IMR (पूर्णांकerrupt mask रेजिस्टर).
	 */
	पूर्णांक_mask = new_mask & AR5K_INT_COMMON;

	अगर (ah->ah_version != AR5K_AR5210) अणु
		/* Preserve per queue TXURN पूर्णांकerrupt mask */
		u32 simr2 = ath5k_hw_reg_पढ़ो(ah, AR5K_SIMR2)
				& AR5K_SIMR2_QCU_TXURN;

		/* Fatal पूर्णांकerrupt असलtraction क्रम 5211+ */
		अगर (new_mask & AR5K_INT_FATAL) अणु
			पूर्णांक_mask |= AR5K_IMR_HIUERR;
			simr2 |= (AR5K_SIMR2_MCABT | AR5K_SIMR2_SSERR
				| AR5K_SIMR2_DPERR);
		पूर्ण

		/* Misc beacon related पूर्णांकerrupts */
		अगर (new_mask & AR5K_INT_TIM)
			पूर्णांक_mask |= AR5K_IMR_TIM;

		अगर (new_mask & AR5K_INT_TIM)
			simr2 |= AR5K_SISR2_TIM;
		अगर (new_mask & AR5K_INT_DTIM)
			simr2 |= AR5K_SISR2_DTIM;
		अगर (new_mask & AR5K_INT_DTIM_SYNC)
			simr2 |= AR5K_SISR2_DTIM_SYNC;
		अगर (new_mask & AR5K_INT_BCN_TIMEOUT)
			simr2 |= AR5K_SISR2_BCN_TIMEOUT;
		अगर (new_mask & AR5K_INT_CAB_TIMEOUT)
			simr2 |= AR5K_SISR2_CAB_TIMEOUT;

		/*Beacon Not Ready*/
		अगर (new_mask & AR5K_INT_BNR)
			पूर्णांक_mask |= AR5K_INT_BNR;

		/* Note: Per queue पूर्णांकerrupt masks
		 * are set via ath5k_hw_reset_tx_queue() (qcu.c) */
		ath5k_hw_reg_ग_लिखो(ah, पूर्णांक_mask, AR5K_PIMR);
		ath5k_hw_reg_ग_लिखो(ah, simr2, AR5K_SIMR2);

	पूर्ण अन्यथा अणु
		/* Fatal पूर्णांकerrupt असलtraction क्रम 5210 */
		अगर (new_mask & AR5K_INT_FATAL)
			पूर्णांक_mask |= (AR5K_IMR_SSERR | AR5K_IMR_MCABT
				| AR5K_IMR_HIUERR | AR5K_IMR_DPERR);

		/* Only common पूर्णांकerrupts left क्रम 5210 (no SIMRs) */
		ath5k_hw_reg_ग_लिखो(ah, पूर्णांक_mask, AR5K_IMR);
	पूर्ण

	/* If RXNOFRM पूर्णांकerrupt is masked disable it
	 * by setting AR5K_RXNOFRM to zero */
	अगर (!(new_mask & AR5K_INT_RXNOFRM))
		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_RXNOFRM);

	/* Store new पूर्णांकerrupt mask */
	ah->ah_imr = new_mask;

	/* ..re-enable पूर्णांकerrupts अगर AR5K_INT_GLOBAL is set */
	अगर (new_mask & AR5K_INT_GLOBAL) अणु
		ath5k_hw_reg_ग_लिखो(ah, AR5K_IER_ENABLE, AR5K_IER);
		ath5k_hw_reg_पढ़ो(ah, AR5K_IER);
	पूर्ण

	वापस old_mask;
पूर्ण


/********************\
 Init/Stop functions
\********************/

/**
 * ath5k_hw_dma_init() - Initialize DMA unit
 * @ah: The &काष्ठा ath5k_hw
 *
 * Set DMA size and pre-enable पूर्णांकerrupts
 * (driver handles tx/rx buffer setup and
 * dma start/stop)
 *
 * XXX: Save/restore RXDP/TXDP रेजिस्टरs ?
 */
व्योम
ath5k_hw_dma_init(काष्ठा ath5k_hw *ah)
अणु
	/*
	 * Set Rx/Tx DMA Configuration
	 *
	 * Set standard DMA size (128). Note that
	 * a DMA size of 512 causes rx overruns and tx errors
	 * on pci-e cards (tested on 5424 but since rx overruns
	 * also occur on 5416/5418 with madwअगरi we set 128
	 * क्रम all PCI-E cards to be safe).
	 *
	 * XXX: need to check 5210 क्रम this
	 * TODO: Check out tx trigger level, it's always 64 on dumps but I
	 * guess we can tweak it and see how it goes ;-)
	 */
	अगर (ah->ah_version != AR5K_AR5210) अणु
		AR5K_REG_WRITE_BITS(ah, AR5K_TXCFG,
			AR5K_TXCFG_SDMAMR, AR5K_DMASIZE_128B);
		AR5K_REG_WRITE_BITS(ah, AR5K_RXCFG,
			AR5K_RXCFG_SDMAMW, AR5K_DMASIZE_128B);
	पूर्ण

	/* Pre-enable पूर्णांकerrupts on 5211/5212*/
	अगर (ah->ah_version != AR5K_AR5210)
		ath5k_hw_set_imr(ah, ah->ah_imr);

पूर्ण

/**
 * ath5k_hw_dma_stop() - stop DMA unit
 * @ah: The &काष्ठा ath5k_hw
 *
 * Stop tx/rx DMA and पूर्णांकerrupts. Returns
 * -EBUSY अगर tx or rx dma failed to stop.
 *
 * XXX: Someबार DMA unit hangs and we have
 * stuck frames on tx queues, only a reset
 * can fix that.
 */
पूर्णांक
ath5k_hw_dma_stop(काष्ठा ath5k_hw *ah)
अणु
	पूर्णांक i, qmax, err;
	err = 0;

	/* Disable पूर्णांकerrupts */
	ath5k_hw_set_imr(ah, 0);

	/* Stop rx dma */
	err = ath5k_hw_stop_rx_dma(ah);
	अगर (err)
		वापस err;

	/* Clear any pending पूर्णांकerrupts
	 * and disable tx dma */
	अगर (ah->ah_version != AR5K_AR5210) अणु
		ath5k_hw_reg_ग_लिखो(ah, 0xffffffff, AR5K_PISR);
		qmax = AR5K_NUM_TX_QUEUES;
	पूर्ण अन्यथा अणु
		/* PISR/SISR Not available on 5210 */
		ath5k_hw_reg_पढ़ो(ah, AR5K_ISR);
		qmax = AR5K_NUM_TX_QUEUES_NOQCU;
	पूर्ण

	क्रम (i = 0; i < qmax; i++) अणु
		err = ath5k_hw_stop_tx_dma(ah, i);
		/* -EINVAL -> queue inactive */
		अगर (err && err != -EINVAL)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
