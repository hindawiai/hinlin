<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
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
 */

#समावेश "hw.h"
#समावेश "hw-ops.h"
#समावेश <linux/export.h>

अटल व्योम ath9k_hw_set_txq_पूर्णांकerrupts(काष्ठा ath_hw *ah,
					काष्ठा ath9k_tx_queue_info *qi)
अणु
	ath_dbg(ath9k_hw_common(ah), INTERRUPT,
		"tx ok 0x%x err 0x%x desc 0x%x eol 0x%x urn 0x%x\n",
		ah->txok_पूर्णांकerrupt_mask, ah->txerr_पूर्णांकerrupt_mask,
		ah->txdesc_पूर्णांकerrupt_mask, ah->txeol_पूर्णांकerrupt_mask,
		ah->txurn_पूर्णांकerrupt_mask);

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_IMR_S0,
		  SM(ah->txok_पूर्णांकerrupt_mask, AR_IMR_S0_QCU_TXOK)
		  | SM(ah->txdesc_पूर्णांकerrupt_mask, AR_IMR_S0_QCU_TXDESC));
	REG_WRITE(ah, AR_IMR_S1,
		  SM(ah->txerr_पूर्णांकerrupt_mask, AR_IMR_S1_QCU_TXERR)
		  | SM(ah->txeol_पूर्णांकerrupt_mask, AR_IMR_S1_QCU_TXEOL));

	ah->imrs2_reg &= ~AR_IMR_S2_QCU_TXURN;
	ah->imrs2_reg |= (ah->txurn_पूर्णांकerrupt_mask & AR_IMR_S2_QCU_TXURN);
	REG_WRITE(ah, AR_IMR_S2, ah->imrs2_reg);

	REGWRITE_BUFFER_FLUSH(ah);
पूर्ण

u32 ath9k_hw_gettxbuf(काष्ठा ath_hw *ah, u32 q)
अणु
	वापस REG_READ(ah, AR_QTXDP(q));
पूर्ण
EXPORT_SYMBOL(ath9k_hw_gettxbuf);

व्योम ath9k_hw_puttxbuf(काष्ठा ath_hw *ah, u32 q, u32 txdp)
अणु
	REG_WRITE(ah, AR_QTXDP(q), txdp);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_puttxbuf);

व्योम ath9k_hw_txstart(काष्ठा ath_hw *ah, u32 q)
अणु
	ath_dbg(ath9k_hw_common(ah), QUEUE, "Enable TXE on queue: %u\n", q);
	REG_WRITE(ah, AR_Q_TXE, 1 << q);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_txstart);

u32 ath9k_hw_numtxpending(काष्ठा ath_hw *ah, u32 q)
अणु
	u32 npend;

	npend = REG_READ(ah, AR_QSTS(q)) & AR_Q_STS_PEND_FR_CNT;
	अगर (npend == 0) अणु

		अगर (REG_READ(ah, AR_Q_TXE) & (1 << q))
			npend = 1;
	पूर्ण

	वापस npend;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_numtxpending);

/**
 * ath9k_hw_updatetxtriglevel - adjusts the frame trigger level
 *
 * @ah: atheros hardware काष्ठा
 * @bIncTrigLevel: whether or not the frame trigger level should be updated
 *
 * The frame trigger level specअगरies the minimum number of bytes,
 * in units of 64 bytes, that must be DMA'ed पूर्णांकo the PCU TX FIFO
 * beक्रमe the PCU will initiate sending the frame on the air. This can
 * mean we initiate transmit beक्रमe a full frame is on the PCU TX FIFO.
 * Resets to 0x1 (meaning 64 bytes or a full frame, whichever occurs
 * first)
 *
 * Caution must be taken to ensure to set the frame trigger level based
 * on the DMA request size. For example अगर the DMA request size is set to
 * 128 bytes the trigger level cannot exceed 6 * 64 = 384. This is because
 * there need to be enough space in the tx FIFO क्रम the requested transfer
 * size. Hence the tx FIFO will stop with 512 - 128 = 384 bytes. If we set
 * the threshold to a value beyond 6, then the transmit will hang.
 *
 * Current dual   stream devices have a PCU TX FIFO size of 8 KB.
 * Current single stream devices have a PCU TX FIFO size of 4 KB, however,
 * there is a hardware issue which क्रमces us to use 2 KB instead so the
 * frame trigger level must not exceed 2 KB क्रम these chipsets.
 */
bool ath9k_hw_updatetxtriglevel(काष्ठा ath_hw *ah, bool bIncTrigLevel)
अणु
	u32 txcfg, curLevel, newLevel;

	अगर (ah->tx_trig_level >= ah->config.max_txtrig_level)
		वापस false;

	ath9k_hw_disable_पूर्णांकerrupts(ah);

	txcfg = REG_READ(ah, AR_TXCFG);
	curLevel = MS(txcfg, AR_FTRIG);
	newLevel = curLevel;
	अगर (bIncTrigLevel) अणु
		अगर (curLevel < ah->config.max_txtrig_level)
			newLevel++;
	पूर्ण अन्यथा अगर (curLevel > MIN_TX_FIFO_THRESHOLD)
		newLevel--;
	अगर (newLevel != curLevel)
		REG_WRITE(ah, AR_TXCFG,
			  (txcfg & ~AR_FTRIG) | SM(newLevel, AR_FTRIG));

	ath9k_hw_enable_पूर्णांकerrupts(ah);

	ah->tx_trig_level = newLevel;

	वापस newLevel != curLevel;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_updatetxtriglevel);

व्योम ath9k_hw_पात_tx_dma(काष्ठा ath_hw *ah)
अणु
	पूर्णांक maxdelay = 1000;
	पूर्णांक i, q;

	अगर (ah->curchan) अणु
		अगर (IS_CHAN_HALF_RATE(ah->curchan))
			maxdelay *= 2;
		अन्यथा अगर (IS_CHAN_QUARTER_RATE(ah->curchan))
			maxdelay *= 4;
	पूर्ण

	REG_WRITE(ah, AR_Q_TXD, AR_Q_TXD_M);

	REG_SET_BIT(ah, AR_PCU_MISC, AR_PCU_FORCE_QUIET_COLL | AR_PCU_CLEAR_VMF);
	REG_SET_BIT(ah, AR_DIAG_SW, AR_DIAG_FORCE_CH_IDLE_HIGH);
	REG_SET_BIT(ah, AR_D_GBL_IFS_MISC, AR_D_GBL_IFS_MISC_IGNORE_BACKOFF);

	क्रम (q = 0; q < AR_NUM_QCU; q++) अणु
		क्रम (i = 0; i < maxdelay; i++) अणु
			अगर (i)
				udelay(5);

			अगर (!ath9k_hw_numtxpending(ah, q))
				अवरोध;
		पूर्ण
	पूर्ण

	REG_CLR_BIT(ah, AR_PCU_MISC, AR_PCU_FORCE_QUIET_COLL | AR_PCU_CLEAR_VMF);
	REG_CLR_BIT(ah, AR_DIAG_SW, AR_DIAG_FORCE_CH_IDLE_HIGH);
	REG_CLR_BIT(ah, AR_D_GBL_IFS_MISC, AR_D_GBL_IFS_MISC_IGNORE_BACKOFF);

	REG_WRITE(ah, AR_Q_TXD, 0);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_पात_tx_dma);

bool ath9k_hw_stop_dma_queue(काष्ठा ath_hw *ah, u32 q)
अणु
#घोषणा ATH9K_TX_STOP_DMA_TIMEOUT	1000    /* usec */
#घोषणा ATH9K_TIME_QUANTUM		100     /* usec */
	पूर्णांक रुको_समय = ATH9K_TX_STOP_DMA_TIMEOUT / ATH9K_TIME_QUANTUM;
	पूर्णांक रुको;

	REG_WRITE(ah, AR_Q_TXD, 1 << q);

	क्रम (रुको = रुको_समय; रुको != 0; रुको--) अणु
		अगर (रुको != रुको_समय)
			udelay(ATH9K_TIME_QUANTUM);

		अगर (ath9k_hw_numtxpending(ah, q) == 0)
			अवरोध;
	पूर्ण

	REG_WRITE(ah, AR_Q_TXD, 0);

	वापस रुको != 0;

#अघोषित ATH9K_TX_STOP_DMA_TIMEOUT
#अघोषित ATH9K_TIME_QUANTUM
पूर्ण
EXPORT_SYMBOL(ath9k_hw_stop_dma_queue);

bool ath9k_hw_set_txq_props(काष्ठा ath_hw *ah, पूर्णांक q,
			    स्थिर काष्ठा ath9k_tx_queue_info *qinfo)
अणु
	u32 cw;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_tx_queue_info *qi;

	qi = &ah->txq[q];
	अगर (qi->tqi_type == ATH9K_TX_QUEUE_INACTIVE) अणु
		ath_dbg(common, QUEUE,
			"Set TXQ properties, inactive queue: %u\n", q);
		वापस false;
	पूर्ण

	ath_dbg(common, QUEUE, "Set queue properties for: %u\n", q);

	qi->tqi_ver = qinfo->tqi_ver;
	qi->tqi_subtype = qinfo->tqi_subtype;
	qi->tqi_qflags = qinfo->tqi_qflags;
	qi->tqi_priority = qinfo->tqi_priority;
	अगर (qinfo->tqi_aअगरs != ATH9K_TXQ_USEDEFAULT)
		qi->tqi_aअगरs = min(qinfo->tqi_aअगरs, 255U);
	अन्यथा
		qi->tqi_aअगरs = INIT_AIFS;
	अगर (qinfo->tqi_cwmin != ATH9K_TXQ_USEDEFAULT) अणु
		cw = min(qinfo->tqi_cwmin, 1024U);
		qi->tqi_cwmin = 1;
		जबतक (qi->tqi_cwmin < cw)
			qi->tqi_cwmin = (qi->tqi_cwmin << 1) | 1;
	पूर्ण अन्यथा
		qi->tqi_cwmin = qinfo->tqi_cwmin;
	अगर (qinfo->tqi_cwmax != ATH9K_TXQ_USEDEFAULT) अणु
		cw = min(qinfo->tqi_cwmax, 1024U);
		qi->tqi_cwmax = 1;
		जबतक (qi->tqi_cwmax < cw)
			qi->tqi_cwmax = (qi->tqi_cwmax << 1) | 1;
	पूर्ण अन्यथा
		qi->tqi_cwmax = INIT_CWMAX;

	अगर (qinfo->tqi_shretry != 0)
		qi->tqi_shretry = min((u32) qinfo->tqi_shretry, 15U);
	अन्यथा
		qi->tqi_shretry = INIT_SH_RETRY;
	अगर (qinfo->tqi_lgretry != 0)
		qi->tqi_lgretry = min((u32) qinfo->tqi_lgretry, 15U);
	अन्यथा
		qi->tqi_lgretry = INIT_LG_RETRY;
	qi->tqi_cbrPeriod = qinfo->tqi_cbrPeriod;
	qi->tqi_cbrOverflowLimit = qinfo->tqi_cbrOverflowLimit;
	qi->tqi_burstTime = qinfo->tqi_burstTime;
	qi->tqi_पढ़ोyTime = qinfo->tqi_पढ़ोyTime;

	चयन (qinfo->tqi_subtype) अणु
	हाल ATH9K_WME_UPSD:
		अगर (qi->tqi_type == ATH9K_TX_QUEUE_DATA)
			qi->tqi_पूर्णांकFlags = ATH9K_TXQ_USE_LOCKOUT_BKOFF_DIS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_set_txq_props);

bool ath9k_hw_get_txq_props(काष्ठा ath_hw *ah, पूर्णांक q,
			    काष्ठा ath9k_tx_queue_info *qinfo)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_tx_queue_info *qi;

	qi = &ah->txq[q];
	अगर (qi->tqi_type == ATH9K_TX_QUEUE_INACTIVE) अणु
		ath_dbg(common, QUEUE,
			"Get TXQ properties, inactive queue: %u\n", q);
		वापस false;
	पूर्ण

	qinfo->tqi_qflags = qi->tqi_qflags;
	qinfo->tqi_ver = qi->tqi_ver;
	qinfo->tqi_subtype = qi->tqi_subtype;
	qinfo->tqi_qflags = qi->tqi_qflags;
	qinfo->tqi_priority = qi->tqi_priority;
	qinfo->tqi_aअगरs = qi->tqi_aअगरs;
	qinfo->tqi_cwmin = qi->tqi_cwmin;
	qinfo->tqi_cwmax = qi->tqi_cwmax;
	qinfo->tqi_shretry = qi->tqi_shretry;
	qinfo->tqi_lgretry = qi->tqi_lgretry;
	qinfo->tqi_cbrPeriod = qi->tqi_cbrPeriod;
	qinfo->tqi_cbrOverflowLimit = qi->tqi_cbrOverflowLimit;
	qinfo->tqi_burstTime = qi->tqi_burstTime;
	qinfo->tqi_पढ़ोyTime = qi->tqi_पढ़ोyTime;

	वापस true;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_get_txq_props);

पूर्णांक ath9k_hw_setuptxqueue(काष्ठा ath_hw *ah, क्रमागत ath9k_tx_queue type,
			  स्थिर काष्ठा ath9k_tx_queue_info *qinfo)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_tx_queue_info *qi;
	पूर्णांक q;

	चयन (type) अणु
	हाल ATH9K_TX_QUEUE_BEACON:
		q = ATH9K_NUM_TX_QUEUES - 1;
		अवरोध;
	हाल ATH9K_TX_QUEUE_CAB:
		q = ATH9K_NUM_TX_QUEUES - 2;
		अवरोध;
	हाल ATH9K_TX_QUEUE_PSPOLL:
		q = 1;
		अवरोध;
	हाल ATH9K_TX_QUEUE_UAPSD:
		q = ATH9K_NUM_TX_QUEUES - 3;
		अवरोध;
	हाल ATH9K_TX_QUEUE_DATA:
		q = qinfo->tqi_subtype;
		अवरोध;
	शेष:
		ath_err(common, "Invalid TX queue type: %u\n", type);
		वापस -1;
	पूर्ण

	ath_dbg(common, QUEUE, "Setup TX queue: %u\n", q);

	qi = &ah->txq[q];
	अगर (qi->tqi_type != ATH9K_TX_QUEUE_INACTIVE) अणु
		ath_err(common, "TX queue: %u already active\n", q);
		वापस -1;
	पूर्ण
	स_रखो(qi, 0, माप(काष्ठा ath9k_tx_queue_info));
	qi->tqi_type = type;
	qi->tqi_physCompBuf = qinfo->tqi_physCompBuf;
	(व्योम) ath9k_hw_set_txq_props(ah, q, qinfo);

	वापस q;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_setuptxqueue);

अटल व्योम ath9k_hw_clear_queue_पूर्णांकerrupts(काष्ठा ath_hw *ah, u32 q)
अणु
	ah->txok_पूर्णांकerrupt_mask &= ~(1 << q);
	ah->txerr_पूर्णांकerrupt_mask &= ~(1 << q);
	ah->txdesc_पूर्णांकerrupt_mask &= ~(1 << q);
	ah->txeol_पूर्णांकerrupt_mask &= ~(1 << q);
	ah->txurn_पूर्णांकerrupt_mask &= ~(1 << q);
पूर्ण

bool ath9k_hw_releasetxqueue(काष्ठा ath_hw *ah, u32 q)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_tx_queue_info *qi;

	qi = &ah->txq[q];
	अगर (qi->tqi_type == ATH9K_TX_QUEUE_INACTIVE) अणु
		ath_dbg(common, QUEUE, "Release TXQ, inactive queue: %u\n", q);
		वापस false;
	पूर्ण

	ath_dbg(common, QUEUE, "Release TX queue: %u\n", q);

	qi->tqi_type = ATH9K_TX_QUEUE_INACTIVE;
	ath9k_hw_clear_queue_पूर्णांकerrupts(ah, q);
	ath9k_hw_set_txq_पूर्णांकerrupts(ah, qi);

	वापस true;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_releasetxqueue);

bool ath9k_hw_resettxqueue(काष्ठा ath_hw *ah, u32 q)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_tx_queue_info *qi;
	u32 cwMin, chanCwMin, value;

	qi = &ah->txq[q];
	अगर (qi->tqi_type == ATH9K_TX_QUEUE_INACTIVE) अणु
		ath_dbg(common, QUEUE, "Reset TXQ, inactive queue: %u\n", q);
		वापस true;
	पूर्ण

	ath_dbg(common, QUEUE, "Reset TX queue: %u\n", q);

	अगर (qi->tqi_cwmin == ATH9K_TXQ_USEDEFAULT) अणु
		chanCwMin = INIT_CWMIN;

		क्रम (cwMin = 1; cwMin < chanCwMin; cwMin = (cwMin << 1) | 1);
	पूर्ण अन्यथा
		cwMin = qi->tqi_cwmin;

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_DLCL_IFS(q),
		  SM(cwMin, AR_D_LCL_IFS_CWMIN) |
		  SM(qi->tqi_cwmax, AR_D_LCL_IFS_CWMAX) |
		  SM(qi->tqi_aअगरs, AR_D_LCL_IFS_AIFS));

	REG_WRITE(ah, AR_DRETRY_LIMIT(q),
		  SM(INIT_SSH_RETRY, AR_D_RETRY_LIMIT_STA_SH) |
		  SM(INIT_SLG_RETRY, AR_D_RETRY_LIMIT_STA_LG) |
		  SM(qi->tqi_shretry, AR_D_RETRY_LIMIT_FR_SH));

	REG_WRITE(ah, AR_QMISC(q), AR_Q_MISC_DCU_EARLY_TERM_REQ);

	अगर (AR_SREV_9340(ah) && !AR_SREV_9340_13_OR_LATER(ah))
		REG_WRITE(ah, AR_DMISC(q),
			  AR_D_MISC_CW_BKOFF_EN | AR_D_MISC_FRAG_WAIT_EN | 0x1);
	अन्यथा
		REG_WRITE(ah, AR_DMISC(q),
			  AR_D_MISC_CW_BKOFF_EN | AR_D_MISC_FRAG_WAIT_EN | 0x2);

	अगर (qi->tqi_cbrPeriod) अणु
		REG_WRITE(ah, AR_QCBRCFG(q),
			  SM(qi->tqi_cbrPeriod, AR_Q_CBRCFG_INTERVAL) |
			  SM(qi->tqi_cbrOverflowLimit, AR_Q_CBRCFG_OVF_THRESH));
		REG_SET_BIT(ah, AR_QMISC(q), AR_Q_MISC_FSP_CBR |
			    (qi->tqi_cbrOverflowLimit ?
			     AR_Q_MISC_CBR_EXP_CNTR_LIMIT_EN : 0));
	पूर्ण
	अगर (qi->tqi_पढ़ोyTime && (qi->tqi_type != ATH9K_TX_QUEUE_CAB)) अणु
		REG_WRITE(ah, AR_QRDYTIMECFG(q),
			  SM(qi->tqi_पढ़ोyTime, AR_Q_RDYTIMECFG_DURATION) |
			  AR_Q_RDYTIMECFG_EN);
	पूर्ण

	REG_WRITE(ah, AR_DCHNTIME(q),
		  SM(qi->tqi_burstTime, AR_D_CHNTIME_DUR) |
		  (qi->tqi_burstTime ? AR_D_CHNTIME_EN : 0));

	अगर (qi->tqi_burstTime
	    && (qi->tqi_qflags & TXQ_FLAG_RDYTIME_EXP_POLICY_ENABLE))
		REG_SET_BIT(ah, AR_QMISC(q), AR_Q_MISC_RDYTIME_EXP_POLICY);

	अगर (qi->tqi_qflags & TXQ_FLAG_BACKOFF_DISABLE)
		REG_SET_BIT(ah, AR_DMISC(q), AR_D_MISC_POST_FR_BKOFF_DIS);

	REGWRITE_BUFFER_FLUSH(ah);

	अगर (qi->tqi_qflags & TXQ_FLAG_FRAG_BURST_BACKOFF_ENABLE)
		REG_SET_BIT(ah, AR_DMISC(q), AR_D_MISC_FRAG_BKOFF_EN);

	चयन (qi->tqi_type) अणु
	हाल ATH9K_TX_QUEUE_BEACON:
		ENABLE_REGWRITE_BUFFER(ah);

		REG_SET_BIT(ah, AR_QMISC(q),
			    AR_Q_MISC_FSP_DBA_GATED
			    | AR_Q_MISC_BEACON_USE
			    | AR_Q_MISC_CBR_INCR_DIS1);

		REG_SET_BIT(ah, AR_DMISC(q),
			    (AR_D_MISC_ARB_LOCKOUT_CNTRL_GLOBAL <<
			     AR_D_MISC_ARB_LOCKOUT_CNTRL_S)
			    | AR_D_MISC_BEACON_USE
			    | AR_D_MISC_POST_FR_BKOFF_DIS);

		REGWRITE_BUFFER_FLUSH(ah);

		/*
		 * cwmin and cwmax should be 0 क्रम beacon queue
		 * but not क्रम IBSS as we would create an imbalance
		 * on beaconing fairness क्रम participating nodes.
		 */
		अगर (AR_SREV_9300_20_OR_LATER(ah) &&
		    ah->opmode != NL80211_IFTYPE_ADHOC) अणु
			REG_WRITE(ah, AR_DLCL_IFS(q), SM(0, AR_D_LCL_IFS_CWMIN)
				  | SM(0, AR_D_LCL_IFS_CWMAX)
				  | SM(qi->tqi_aअगरs, AR_D_LCL_IFS_AIFS));
		पूर्ण
		अवरोध;
	हाल ATH9K_TX_QUEUE_CAB:
		ENABLE_REGWRITE_BUFFER(ah);

		REG_SET_BIT(ah, AR_QMISC(q),
			    AR_Q_MISC_FSP_DBA_GATED
			    | AR_Q_MISC_CBR_INCR_DIS1
			    | AR_Q_MISC_CBR_INCR_DIS0);
		value = (qi->tqi_पढ़ोyTime -
			 (ah->config.sw_beacon_response_समय -
			  ah->config.dma_beacon_response_समय)) * 1024;
		REG_WRITE(ah, AR_QRDYTIMECFG(q),
			  value | AR_Q_RDYTIMECFG_EN);
		REG_SET_BIT(ah, AR_DMISC(q),
			    (AR_D_MISC_ARB_LOCKOUT_CNTRL_GLOBAL <<
			     AR_D_MISC_ARB_LOCKOUT_CNTRL_S));

		REGWRITE_BUFFER_FLUSH(ah);

		अवरोध;
	हाल ATH9K_TX_QUEUE_PSPOLL:
		REG_SET_BIT(ah, AR_QMISC(q), AR_Q_MISC_CBR_INCR_DIS1);
		अवरोध;
	हाल ATH9K_TX_QUEUE_UAPSD:
		REG_SET_BIT(ah, AR_DMISC(q), AR_D_MISC_POST_FR_BKOFF_DIS);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (qi->tqi_पूर्णांकFlags & ATH9K_TXQ_USE_LOCKOUT_BKOFF_DIS) अणु
		REG_SET_BIT(ah, AR_DMISC(q),
			    SM(AR_D_MISC_ARB_LOCKOUT_CNTRL_GLOBAL,
			       AR_D_MISC_ARB_LOCKOUT_CNTRL) |
			    AR_D_MISC_POST_FR_BKOFF_DIS);
	पूर्ण

	अगर (AR_SREV_9300_20_OR_LATER(ah))
		REG_WRITE(ah, AR_Q_DESC_CRCCHK, AR_Q_DESC_CRCCHK_EN);

	ath9k_hw_clear_queue_पूर्णांकerrupts(ah, q);
	अगर (qi->tqi_qflags & TXQ_FLAG_TXINT_ENABLE) अणु
		ah->txok_पूर्णांकerrupt_mask |= 1 << q;
		ah->txerr_पूर्णांकerrupt_mask |= 1 << q;
	पूर्ण
	अगर (qi->tqi_qflags & TXQ_FLAG_TXDESCINT_ENABLE)
		ah->txdesc_पूर्णांकerrupt_mask |= 1 << q;
	अगर (qi->tqi_qflags & TXQ_FLAG_TXEOLINT_ENABLE)
		ah->txeol_पूर्णांकerrupt_mask |= 1 << q;
	अगर (qi->tqi_qflags & TXQ_FLAG_TXURNINT_ENABLE)
		ah->txurn_पूर्णांकerrupt_mask |= 1 << q;
	ath9k_hw_set_txq_पूर्णांकerrupts(ah, qi);

	वापस true;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_resettxqueue);

पूर्णांक ath9k_hw_rxprocdesc(काष्ठा ath_hw *ah, काष्ठा ath_desc *ds,
			काष्ठा ath_rx_status *rs)
अणु
	काष्ठा ar5416_desc ads;
	काष्ठा ar5416_desc *adsp = AR5416DESC(ds);
	u32 phyerr;

	अगर ((adsp->ds_rxstatus8 & AR_RxDone) == 0)
		वापस -EINPROGRESS;

	ads.u.rx = adsp->u.rx;

	rs->rs_status = 0;
	rs->rs_flags = 0;
	rs->enc_flags = 0;
	rs->bw = RATE_INFO_BW_20;

	rs->rs_datalen = ads.ds_rxstatus1 & AR_DataLen;
	rs->rs_tstamp = ads.AR_RcvTimestamp;

	अगर (ads.ds_rxstatus8 & AR_PostDelimCRCErr) अणु
		rs->rs_rssi = ATH9K_RSSI_BAD;
		rs->rs_rssi_ctl[0] = ATH9K_RSSI_BAD;
		rs->rs_rssi_ctl[1] = ATH9K_RSSI_BAD;
		rs->rs_rssi_ctl[2] = ATH9K_RSSI_BAD;
		rs->rs_rssi_ext[0] = ATH9K_RSSI_BAD;
		rs->rs_rssi_ext[1] = ATH9K_RSSI_BAD;
		rs->rs_rssi_ext[2] = ATH9K_RSSI_BAD;
	पूर्ण अन्यथा अणु
		rs->rs_rssi = MS(ads.ds_rxstatus4, AR_RxRSSICombined);
		rs->rs_rssi_ctl[0] = MS(ads.ds_rxstatus0,
						AR_RxRSSIAnt00);
		rs->rs_rssi_ctl[1] = MS(ads.ds_rxstatus0,
						AR_RxRSSIAnt01);
		rs->rs_rssi_ctl[2] = MS(ads.ds_rxstatus0,
						AR_RxRSSIAnt02);
		rs->rs_rssi_ext[0] = MS(ads.ds_rxstatus4,
						AR_RxRSSIAnt10);
		rs->rs_rssi_ext[1] = MS(ads.ds_rxstatus4,
						AR_RxRSSIAnt11);
		rs->rs_rssi_ext[2] = MS(ads.ds_rxstatus4,
						AR_RxRSSIAnt12);
	पूर्ण
	अगर (ads.ds_rxstatus8 & AR_RxKeyIdxValid)
		rs->rs_keyix = MS(ads.ds_rxstatus8, AR_KeyIdx);
	अन्यथा
		rs->rs_keyix = ATH9K_RXKEYIX_INVALID;

	rs->rs_rate = MS(ads.ds_rxstatus0, AR_RxRate);
	rs->rs_more = (ads.ds_rxstatus1 & AR_RxMore) ? 1 : 0;

	rs->rs_firstaggr = (ads.ds_rxstatus8 & AR_RxFirstAggr) ? 1 : 0;
	rs->rs_isaggr = (ads.ds_rxstatus8 & AR_RxAggr) ? 1 : 0;
	rs->rs_moreaggr = (ads.ds_rxstatus8 & AR_RxMoreAggr) ? 1 : 0;
	rs->rs_antenna = MS(ads.ds_rxstatus3, AR_RxAntenna);

	/* directly mapped flags क्रम ieee80211_rx_status */
	rs->enc_flags |=
		(ads.ds_rxstatus3 & AR_GI) ? RX_ENC_FLAG_SHORT_GI : 0;
	rs->bw = (ads.ds_rxstatus3 & AR_2040) ? RATE_INFO_BW_40 :
						RATE_INFO_BW_20;
	अगर (AR_SREV_9280_20_OR_LATER(ah))
		rs->enc_flags |=
			(ads.ds_rxstatus3 & AR_STBC) ?
				/* we can only Nss=1 STBC */
				(1 << RX_ENC_FLAG_STBC_SHIFT) : 0;

	अगर (ads.ds_rxstatus8 & AR_PreDelimCRCErr)
		rs->rs_flags |= ATH9K_RX_DELIM_CRC_PRE;
	अगर (ads.ds_rxstatus8 & AR_PostDelimCRCErr)
		rs->rs_flags |= ATH9K_RX_DELIM_CRC_POST;
	अगर (ads.ds_rxstatus8 & AR_DecryptBusyErr)
		rs->rs_flags |= ATH9K_RX_DECRYPT_BUSY;

	अगर ((ads.ds_rxstatus8 & AR_RxFrameOK) == 0) अणु
		/*
		 * Treat these errors as mutually exclusive to aव्योम spurious
		 * extra error reports from the hardware. If a CRC error is
		 * reported, then decryption and MIC errors are irrelevant,
		 * the frame is going to be dropped either way
		 */
		अगर (ads.ds_rxstatus8 & AR_PHYErr) अणु
			rs->rs_status |= ATH9K_RXERR_PHY;
			phyerr = MS(ads.ds_rxstatus8, AR_PHYErrCode);
			rs->rs_phyerr = phyerr;
		पूर्ण अन्यथा अगर (ads.ds_rxstatus8 & AR_CRCErr)
			rs->rs_status |= ATH9K_RXERR_CRC;
		अन्यथा अगर (ads.ds_rxstatus8 & AR_DecryptCRCErr)
			rs->rs_status |= ATH9K_RXERR_DECRYPT;
		अन्यथा अगर (ads.ds_rxstatus8 & AR_MichaelErr)
			rs->rs_status |= ATH9K_RXERR_MIC;
	पूर्ण अन्यथा अणु
		अगर (ads.ds_rxstatus8 &
		    (AR_CRCErr | AR_PHYErr | AR_DecryptCRCErr | AR_MichaelErr))
			rs->rs_status |= ATH9K_RXERR_CORRUPT_DESC;

		/* Only up to MCS16 supported, everything above is invalid */
		अगर (rs->rs_rate >= 0x90)
			rs->rs_status |= ATH9K_RXERR_CORRUPT_DESC;
	पूर्ण

	अगर (ads.ds_rxstatus8 & AR_KeyMiss)
		rs->rs_status |= ATH9K_RXERR_KEYMISS;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_rxprocdesc);

/*
 * This can stop or re-enables RX.
 *
 * If bool is set this will समाप्त any frame which is currently being
 * transferred between the MAC and baseband and also prevent any new
 * frames from getting started.
 */
bool ath9k_hw_setrxपात(काष्ठा ath_hw *ah, bool set)
अणु
	u32 reg;

	अगर (set) अणु
		REG_SET_BIT(ah, AR_DIAG_SW,
			    (AR_DIAG_RX_DIS | AR_DIAG_RX_ABORT));

		अगर (!ath9k_hw_रुको(ah, AR_OBS_BUS_1, AR_OBS_BUS_1_RX_STATE,
				   0, AH_WAIT_TIMEOUT)) अणु
			REG_CLR_BIT(ah, AR_DIAG_SW,
				    (AR_DIAG_RX_DIS |
				     AR_DIAG_RX_ABORT));

			reg = REG_READ(ah, AR_OBS_BUS_1);
			ath_err(ath9k_hw_common(ah),
				"RX failed to go idle in 10 ms RXSM=0x%x\n",
				reg);

			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		REG_CLR_BIT(ah, AR_DIAG_SW,
			    (AR_DIAG_RX_DIS | AR_DIAG_RX_ABORT));
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_setrxपात);

व्योम ath9k_hw_putrxbuf(काष्ठा ath_hw *ah, u32 rxdp)
अणु
	REG_WRITE(ah, AR_RXDP, rxdp);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_putrxbuf);

व्योम ath9k_hw_startpcureceive(काष्ठा ath_hw *ah, bool is_scanning)
अणु
	ath9k_enable_mib_counters(ah);

	ath9k_ani_reset(ah, is_scanning);

	REG_CLR_BIT(ah, AR_DIAG_SW, (AR_DIAG_RX_DIS | AR_DIAG_RX_ABORT));
पूर्ण
EXPORT_SYMBOL(ath9k_hw_startpcureceive);

व्योम ath9k_hw_पातpcurecv(काष्ठा ath_hw *ah)
अणु
	REG_SET_BIT(ah, AR_DIAG_SW, AR_DIAG_RX_ABORT | AR_DIAG_RX_DIS);

	ath9k_hw_disable_mib_counters(ah);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_पातpcurecv);

bool ath9k_hw_stopdmarecv(काष्ठा ath_hw *ah, bool *reset)
अणु
#घोषणा AH_RX_STOP_DMA_TIMEOUT 10000   /* usec */
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 mac_status, last_mac_status = 0;
	पूर्णांक i;

	/* Enable access to the DMA observation bus */
	REG_WRITE(ah, AR_MACMISC,
		  ((AR_MACMISC_DMA_OBS_LINE_8 << AR_MACMISC_DMA_OBS_S) |
		   (AR_MACMISC_MISC_OBS_BUS_1 <<
		    AR_MACMISC_MISC_OBS_BUS_MSB_S)));

	REG_WRITE(ah, AR_CR, AR_CR_RXD);

	/* Wait क्रम rx enable bit to go low */
	क्रम (i = AH_RX_STOP_DMA_TIMEOUT / AH_TIME_QUANTUM; i != 0; i--) अणु
		अगर ((REG_READ(ah, AR_CR) & AR_CR_RXE) == 0)
			अवरोध;

		अगर (!AR_SREV_9300_20_OR_LATER(ah)) अणु
			mac_status = REG_READ(ah, AR_DMADBG_7) & 0x7f0;
			अगर (mac_status == 0x1c0 && mac_status == last_mac_status) अणु
				*reset = true;
				अवरोध;
			पूर्ण

			last_mac_status = mac_status;
		पूर्ण

		udelay(AH_TIME_QUANTUM);
	पूर्ण

	अगर (i == 0) अणु
		ath_err(common,
			"DMA failed to stop in %d ms AR_CR=0x%08x AR_DIAG_SW=0x%08x DMADBG_7=0x%08x\n",
			AH_RX_STOP_DMA_TIMEOUT / 1000,
			REG_READ(ah, AR_CR),
			REG_READ(ah, AR_DIAG_SW),
			REG_READ(ah, AR_DMADBG_7));
		वापस false;
	पूर्ण अन्यथा अणु
		वापस true;
	पूर्ण

#अघोषित AH_RX_STOP_DMA_TIMEOUT
पूर्ण
EXPORT_SYMBOL(ath9k_hw_stopdmarecv);

पूर्णांक ath9k_hw_beaconq_setup(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_tx_queue_info qi;

	स_रखो(&qi, 0, माप(qi));
	qi.tqi_aअगरs = 1;
	qi.tqi_cwmin = 0;
	qi.tqi_cwmax = 0;

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		qi.tqi_qflags = TXQ_FLAG_TXINT_ENABLE;

	वापस ath9k_hw_setuptxqueue(ah, ATH9K_TX_QUEUE_BEACON, &qi);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_beaconq_setup);

bool ath9k_hw_पूर्णांकrpend(काष्ठा ath_hw *ah)
अणु
	u32 host_isr;

	अगर (AR_SREV_9100(ah))
		वापस true;

	host_isr = REG_READ(ah, AR_INTR_ASYNC_CAUSE);

	अगर (((host_isr & AR_INTR_MAC_IRQ) ||
	     (host_isr & AR_INTR_ASYNC_MASK_MCI)) &&
	    (host_isr != AR_INTR_SPURIOUS))
		वापस true;

	host_isr = REG_READ(ah, AR_INTR_SYNC_CAUSE);
	अगर ((host_isr & AR_INTR_SYNC_DEFAULT)
	    && (host_isr != AR_INTR_SPURIOUS))
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_पूर्णांकrpend);

व्योम ath9k_hw_समाप्त_पूर्णांकerrupts(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	ath_dbg(common, INTERRUPT, "disable IER\n");
	REG_WRITE(ah, AR_IER, AR_IER_DISABLE);
	(व्योम) REG_READ(ah, AR_IER);
	अगर (!AR_SREV_9100(ah)) अणु
		REG_WRITE(ah, AR_INTR_ASYNC_ENABLE, 0);
		(व्योम) REG_READ(ah, AR_INTR_ASYNC_ENABLE);

		REG_WRITE(ah, AR_INTR_SYNC_ENABLE, 0);
		(व्योम) REG_READ(ah, AR_INTR_SYNC_ENABLE);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath9k_hw_समाप्त_पूर्णांकerrupts);

व्योम ath9k_hw_disable_पूर्णांकerrupts(काष्ठा ath_hw *ah)
अणु
	अगर (!(ah->imask & ATH9K_INT_GLOBAL))
		atomic_set(&ah->पूर्णांकr_ref_cnt, -1);
	अन्यथा
		atomic_dec(&ah->पूर्णांकr_ref_cnt);

	ath9k_hw_समाप्त_पूर्णांकerrupts(ah);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_disable_पूर्णांकerrupts);

अटल व्योम __ath9k_hw_enable_पूर्णांकerrupts(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 sync_शेष = AR_INTR_SYNC_DEFAULT;
	u32 async_mask;

	अगर (AR_SREV_9340(ah) || AR_SREV_9550(ah) || AR_SREV_9531(ah) ||
	    AR_SREV_9561(ah))
		sync_शेष &= ~AR_INTR_SYNC_HOST1_FATAL;

	async_mask = AR_INTR_MAC_IRQ;

	अगर (ah->imask & ATH9K_INT_MCI)
		async_mask |= AR_INTR_ASYNC_MASK_MCI;

	ath_dbg(common, INTERRUPT, "enable IER\n");
	REG_WRITE(ah, AR_IER, AR_IER_ENABLE);
	अगर (!AR_SREV_9100(ah)) अणु
		REG_WRITE(ah, AR_INTR_ASYNC_ENABLE, async_mask);
		REG_WRITE(ah, AR_INTR_ASYNC_MASK, async_mask);

		REG_WRITE(ah, AR_INTR_SYNC_ENABLE, sync_शेष);
		REG_WRITE(ah, AR_INTR_SYNC_MASK, sync_शेष);
	पूर्ण
	ath_dbg(common, INTERRUPT, "AR_IMR 0x%x IER 0x%x\n",
		REG_READ(ah, AR_IMR), REG_READ(ah, AR_IER));

	अगर (ah->msi_enabled) अणु
		u32 _msi_reg = 0;
		u32 i = 0;
		u32 msi_pend_addr_mask = AR_PCIE_MSI_HW_INT_PENDING_ADDR_MSI_64;

		ath_dbg(ath9k_hw_common(ah), INTERRUPT,
			"Enabling MSI, msi_mask=0x%X\n", ah->msi_mask);

		REG_WRITE(ah, AR_INTR_PRIO_ASYNC_ENABLE, ah->msi_mask);
		REG_WRITE(ah, AR_INTR_PRIO_ASYNC_MASK, ah->msi_mask);
		ath_dbg(ath9k_hw_common(ah), INTERRUPT,
			"AR_INTR_PRIO_ASYNC_ENABLE=0x%X, AR_INTR_PRIO_ASYNC_MASK=0x%X\n",
			REG_READ(ah, AR_INTR_PRIO_ASYNC_ENABLE),
			REG_READ(ah, AR_INTR_PRIO_ASYNC_MASK));

		अगर (ah->msi_reg == 0)
			ah->msi_reg = REG_READ(ah, AR_PCIE_MSI);

		ath_dbg(ath9k_hw_common(ah), INTERRUPT,
			"AR_PCIE_MSI=0x%X, ah->msi_reg = 0x%X\n",
			AR_PCIE_MSI, ah->msi_reg);

		i = 0;
		करो अणु
			REG_WRITE(ah, AR_PCIE_MSI,
				  (ah->msi_reg | AR_PCIE_MSI_ENABLE)
				  & msi_pend_addr_mask);
			_msi_reg = REG_READ(ah, AR_PCIE_MSI);
			i++;
		पूर्ण जबतक ((_msi_reg & AR_PCIE_MSI_ENABLE) == 0 && i < 200);

		अगर (i >= 200)
			ath_err(ath9k_hw_common(ah),
				"%s: _msi_reg = 0x%X\n",
				__func__, _msi_reg);
	पूर्ण
पूर्ण

व्योम ath9k_hw_resume_पूर्णांकerrupts(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (!(ah->imask & ATH9K_INT_GLOBAL))
		वापस;

	अगर (atomic_पढ़ो(&ah->पूर्णांकr_ref_cnt) != 0) अणु
		ath_dbg(common, INTERRUPT, "Do not enable IER ref count %d\n",
			atomic_पढ़ो(&ah->पूर्णांकr_ref_cnt));
		वापस;
	पूर्ण

	__ath9k_hw_enable_पूर्णांकerrupts(ah);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_resume_पूर्णांकerrupts);

व्योम ath9k_hw_enable_पूर्णांकerrupts(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (!(ah->imask & ATH9K_INT_GLOBAL))
		वापस;

	अगर (!atomic_inc_and_test(&ah->पूर्णांकr_ref_cnt)) अणु
		ath_dbg(common, INTERRUPT, "Do not enable IER ref count %d\n",
			atomic_पढ़ो(&ah->पूर्णांकr_ref_cnt));
		वापस;
	पूर्ण

	__ath9k_hw_enable_पूर्णांकerrupts(ah);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_enable_पूर्णांकerrupts);

व्योम ath9k_hw_set_पूर्णांकerrupts(काष्ठा ath_hw *ah)
अणु
	क्रमागत ath9k_पूर्णांक पूर्णांकs = ah->imask;
	u32 mask, mask2;
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (!(पूर्णांकs & ATH9K_INT_GLOBAL))
		ath9k_hw_disable_पूर्णांकerrupts(ah);

	अगर (ah->msi_enabled) अणु
		ath_dbg(common, INTERRUPT, "Clearing AR_INTR_PRIO_ASYNC_ENABLE\n");

		REG_WRITE(ah, AR_INTR_PRIO_ASYNC_ENABLE, 0);
		REG_READ(ah, AR_INTR_PRIO_ASYNC_ENABLE);
	पूर्ण

	ath_dbg(common, INTERRUPT, "New interrupt mask 0x%x\n", पूर्णांकs);

	mask = पूर्णांकs & ATH9K_INT_COMMON;
	mask2 = 0;

	ah->msi_mask = 0;
	अगर (पूर्णांकs & ATH9K_INT_TX) अणु
		ah->msi_mask |= AR_INTR_PRIO_TX;
		अगर (ah->config.tx_पूर्णांकr_mitigation)
			mask |= AR_IMR_TXMINTR | AR_IMR_TXINTM;
		अन्यथा अणु
			अगर (ah->txok_पूर्णांकerrupt_mask)
				mask |= AR_IMR_TXOK;
			अगर (ah->txdesc_पूर्णांकerrupt_mask)
				mask |= AR_IMR_TXDESC;
		पूर्ण
		अगर (ah->txerr_पूर्णांकerrupt_mask)
			mask |= AR_IMR_TXERR;
		अगर (ah->txeol_पूर्णांकerrupt_mask)
			mask |= AR_IMR_TXEOL;
	पूर्ण
	अगर (पूर्णांकs & ATH9K_INT_RX) अणु
		ah->msi_mask |= AR_INTR_PRIO_RXLP | AR_INTR_PRIO_RXHP;
		अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
			mask |= AR_IMR_RXERR | AR_IMR_RXOK_HP;
			अगर (ah->config.rx_पूर्णांकr_mitigation) अणु
				mask &= ~AR_IMR_RXOK_LP;
				mask |=  AR_IMR_RXMINTR | AR_IMR_RXINTM;
			पूर्ण अन्यथा अणु
				mask |= AR_IMR_RXOK_LP;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (ah->config.rx_पूर्णांकr_mitigation)
				mask |= AR_IMR_RXMINTR | AR_IMR_RXINTM;
			अन्यथा
				mask |= AR_IMR_RXOK | AR_IMR_RXDESC;
		पूर्ण
		अगर (!(pCap->hw_caps & ATH9K_HW_CAP_AUTOSLEEP))
			mask |= AR_IMR_GENTMR;
	पूर्ण

	अगर (पूर्णांकs & ATH9K_INT_GENTIMER)
		mask |= AR_IMR_GENTMR;

	अगर (पूर्णांकs & (ATH9K_INT_BMISC)) अणु
		mask |= AR_IMR_BCNMISC;
		अगर (पूर्णांकs & ATH9K_INT_TIM)
			mask2 |= AR_IMR_S2_TIM;
		अगर (पूर्णांकs & ATH9K_INT_DTIM)
			mask2 |= AR_IMR_S2_DTIM;
		अगर (पूर्णांकs & ATH9K_INT_DTIMSYNC)
			mask2 |= AR_IMR_S2_DTIMSYNC;
		अगर (पूर्णांकs & ATH9K_INT_CABEND)
			mask2 |= AR_IMR_S2_CABEND;
		अगर (पूर्णांकs & ATH9K_INT_TSFOOR)
			mask2 |= AR_IMR_S2_TSFOOR;
	पूर्ण

	अगर (पूर्णांकs & (ATH9K_INT_GTT | ATH9K_INT_CST)) अणु
		mask |= AR_IMR_BCNMISC;
		अगर (पूर्णांकs & ATH9K_INT_GTT)
			mask2 |= AR_IMR_S2_GTT;
		अगर (पूर्णांकs & ATH9K_INT_CST)
			mask2 |= AR_IMR_S2_CST;
	पूर्ण

	अगर (ah->config.hw_hang_checks & HW_BB_WATCHDOG) अणु
		अगर (पूर्णांकs & ATH9K_INT_BB_WATCHDOG) अणु
			mask |= AR_IMR_BCNMISC;
			mask2 |= AR_IMR_S2_BB_WATCHDOG;
		पूर्ण
	पूर्ण

	ath_dbg(common, INTERRUPT, "new IMR 0x%x\n", mask);
	REG_WRITE(ah, AR_IMR, mask);
	ah->imrs2_reg &= ~(AR_IMR_S2_TIM |
			   AR_IMR_S2_DTIM |
			   AR_IMR_S2_DTIMSYNC |
			   AR_IMR_S2_CABEND |
			   AR_IMR_S2_CABTO |
			   AR_IMR_S2_TSFOOR |
			   AR_IMR_S2_GTT |
			   AR_IMR_S2_CST);

	अगर (ah->config.hw_hang_checks & HW_BB_WATCHDOG) अणु
		अगर (पूर्णांकs & ATH9K_INT_BB_WATCHDOG)
			ah->imrs2_reg &= ~AR_IMR_S2_BB_WATCHDOG;
	पूर्ण

	ah->imrs2_reg |= mask2;
	REG_WRITE(ah, AR_IMR_S2, ah->imrs2_reg);

	अगर (!(pCap->hw_caps & ATH9K_HW_CAP_AUTOSLEEP)) अणु
		अगर (पूर्णांकs & ATH9K_INT_TIM_TIMER)
			REG_SET_BIT(ah, AR_IMR_S5, AR_IMR_S5_TIM_TIMER);
		अन्यथा
			REG_CLR_BIT(ah, AR_IMR_S5, AR_IMR_S5_TIM_TIMER);
	पूर्ण

	वापस;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_set_पूर्णांकerrupts);

#घोषणा ATH9K_HW_MAX_DCU       10
#घोषणा ATH9K_HW_SLICE_PER_DCU 16
#घोषणा ATH9K_HW_BIT_IN_SLICE  16
व्योम ath9k_hw_set_tx_filter(काष्ठा ath_hw *ah, u8 destidx, bool set)
अणु
	पूर्णांक dcu_idx;
	u32 filter;

	क्रम (dcu_idx = 0; dcu_idx < 10; dcu_idx++) अणु
		filter = SM(set, AR_D_TXBLK_WRITE_COMMAND);
		filter |= SM(dcu_idx, AR_D_TXBLK_WRITE_DCU);
		filter |= SM((destidx / ATH9K_HW_SLICE_PER_DCU),
			     AR_D_TXBLK_WRITE_SLICE);
		filter |= BIT(destidx % ATH9K_HW_BIT_IN_SLICE);
		ath_dbg(ath9k_hw_common(ah), PS,
			"DCU%d staid %d set %d txfilter %08x\n",
			dcu_idx, destidx, set, filter);
		REG_WRITE(ah, AR_D_TXBLK_BASE, filter);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath9k_hw_set_tx_filter);
