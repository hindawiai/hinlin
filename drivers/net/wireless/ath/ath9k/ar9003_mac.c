<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
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
#समावेश <linux/export.h>
#समावेश "hw.h"
#समावेश "ar9003_mac.h"
#समावेश "ar9003_mci.h"

अटल व्योम ar9003_hw_rx_enable(काष्ठा ath_hw *hw)
अणु
	REG_WRITE(hw, AR_CR, 0);
पूर्ण

अटल व्योम
ar9003_set_txdesc(काष्ठा ath_hw *ah, व्योम *ds, काष्ठा ath_tx_info *i)
अणु
	काष्ठा ar9003_txc *ads = ds;
	पूर्णांक checksum = 0;
	u32 val, ctl12, ctl17;
	u8 desc_len;

	desc_len = ((AR_SREV_9462(ah) || AR_SREV_9565(ah)) ? 0x18 : 0x17);

	val = (ATHEROS_VENDOR_ID << AR_DescId_S) |
	      (1 << AR_TxRxDesc_S) |
	      (1 << AR_CtrlStat_S) |
	      (i->qcu << AR_TxQcuNum_S) | desc_len;

	checksum += val;
	WRITE_ONCE(ads->info, val);

	checksum += i->link;
	WRITE_ONCE(ads->link, i->link);

	checksum += i->buf_addr[0];
	WRITE_ONCE(ads->data0, i->buf_addr[0]);
	checksum += i->buf_addr[1];
	WRITE_ONCE(ads->data1, i->buf_addr[1]);
	checksum += i->buf_addr[2];
	WRITE_ONCE(ads->data2, i->buf_addr[2]);
	checksum += i->buf_addr[3];
	WRITE_ONCE(ads->data3, i->buf_addr[3]);

	checksum += (val = (i->buf_len[0] << AR_BufLen_S) & AR_BufLen);
	WRITE_ONCE(ads->ctl3, val);
	checksum += (val = (i->buf_len[1] << AR_BufLen_S) & AR_BufLen);
	WRITE_ONCE(ads->ctl5, val);
	checksum += (val = (i->buf_len[2] << AR_BufLen_S) & AR_BufLen);
	WRITE_ONCE(ads->ctl7, val);
	checksum += (val = (i->buf_len[3] << AR_BufLen_S) & AR_BufLen);
	WRITE_ONCE(ads->ctl9, val);

	checksum = (u16) (((checksum & 0xffff) + (checksum >> 16)) & 0xffff);
	WRITE_ONCE(ads->ctl10, checksum);

	अगर (i->is_first || i->is_last) अणु
		WRITE_ONCE(ads->ctl13, set11nTries(i->rates, 0)
			| set11nTries(i->rates, 1)
			| set11nTries(i->rates, 2)
			| set11nTries(i->rates, 3)
			| (i->dur_update ? AR_DurUpdateEna : 0)
			| SM(0, AR_BurstDur));

		WRITE_ONCE(ads->ctl14, set11nRate(i->rates, 0)
			| set11nRate(i->rates, 1)
			| set11nRate(i->rates, 2)
			| set11nRate(i->rates, 3));
	पूर्ण अन्यथा अणु
		WRITE_ONCE(ads->ctl13, 0);
		WRITE_ONCE(ads->ctl14, 0);
	पूर्ण

	ads->ctl20 = 0;
	ads->ctl21 = 0;
	ads->ctl22 = 0;
	ads->ctl23 = 0;

	ctl17 = SM(i->keytype, AR_EncrType);
	अगर (!i->is_first) अणु
		WRITE_ONCE(ads->ctl11, 0);
		WRITE_ONCE(ads->ctl12, i->is_last ? 0 : AR_TxMore);
		WRITE_ONCE(ads->ctl15, 0);
		WRITE_ONCE(ads->ctl16, 0);
		WRITE_ONCE(ads->ctl17, ctl17);
		WRITE_ONCE(ads->ctl18, 0);
		WRITE_ONCE(ads->ctl19, 0);
		वापस;
	पूर्ण

	WRITE_ONCE(ads->ctl11, (i->pkt_len & AR_FrameLen)
		| (i->flags & ATH9K_TXDESC_VMF ? AR_VirtMoreFrag : 0)
		| SM(i->txघातer[0], AR_XmitPower0)
		| (i->flags & ATH9K_TXDESC_VEOL ? AR_VEOL : 0)
		| (i->keyix != ATH9K_TXKEYIX_INVALID ? AR_DestIdxValid : 0)
		| (i->flags & ATH9K_TXDESC_LOWRXCHAIN ? AR_LowRxChain : 0)
		| (i->flags & ATH9K_TXDESC_CLRDMASK ? AR_ClrDestMask : 0)
		| (i->flags & ATH9K_TXDESC_RTSENA ? AR_RTSEnable :
		   (i->flags & ATH9K_TXDESC_CTSENA ? AR_CTSEnable : 0)));

	ctl12 = (i->keyix != ATH9K_TXKEYIX_INVALID ?
		 SM(i->keyix, AR_DestIdx) : 0)
		| SM(i->type, AR_FrameType)
		| (i->flags & ATH9K_TXDESC_NOACK ? AR_NoAck : 0)
		| (i->flags & ATH9K_TXDESC_EXT_ONLY ? AR_ExtOnly : 0)
		| (i->flags & ATH9K_TXDESC_EXT_AND_CTL ? AR_ExtAndCtl : 0);

	ctl17 |= (i->flags & ATH9K_TXDESC_LDPC ? AR_LDPC : 0);
	चयन (i->aggr) अणु
	हाल AGGR_BUF_FIRST:
		ctl17 |= SM(i->aggr_len, AR_AggrLen);
		fallthrough;
	हाल AGGR_BUF_MIDDLE:
		ctl12 |= AR_IsAggr | AR_MoreAggr;
		ctl17 |= SM(i->ndelim, AR_PadDelim);
		अवरोध;
	हाल AGGR_BUF_LAST:
		ctl12 |= AR_IsAggr;
		अवरोध;
	हाल AGGR_BUF_NONE:
		अवरोध;
	पूर्ण

	val = (i->flags & ATH9K_TXDESC_PAPRD) >> ATH9K_TXDESC_PAPRD_S;
	ctl12 |= SM(val, AR_PAPRDChainMask);

	WRITE_ONCE(ads->ctl12, ctl12);
	WRITE_ONCE(ads->ctl17, ctl17);

	WRITE_ONCE(ads->ctl15, set11nPktDurRTSCTS(i->rates, 0)
		| set11nPktDurRTSCTS(i->rates, 1));

	WRITE_ONCE(ads->ctl16, set11nPktDurRTSCTS(i->rates, 2)
		| set11nPktDurRTSCTS(i->rates, 3));

	WRITE_ONCE(ads->ctl18, set11nRateFlags(i->rates, 0)
		| set11nRateFlags(i->rates, 1)
		| set11nRateFlags(i->rates, 2)
		| set11nRateFlags(i->rates, 3)
		| SM(i->rtscts_rate, AR_RTSCTSRate));

	WRITE_ONCE(ads->ctl19, AR_Not_Sounding);

	WRITE_ONCE(ads->ctl20, SM(i->txघातer[1], AR_XmitPower1));
	WRITE_ONCE(ads->ctl21, SM(i->txघातer[2], AR_XmitPower2));
	WRITE_ONCE(ads->ctl22, SM(i->txघातer[3], AR_XmitPower3));
पूर्ण

अटल u16 ar9003_calc_ptr_chksum(काष्ठा ar9003_txc *ads)
अणु
	पूर्णांक checksum;

	checksum = ads->info + ads->link
		+ ads->data0 + ads->ctl3
		+ ads->data1 + ads->ctl5
		+ ads->data2 + ads->ctl7
		+ ads->data3 + ads->ctl9;

	वापस ((checksum & 0xffff) + (checksum >> 16)) & AR_TxPtrChkSum;
पूर्ण

अटल व्योम ar9003_hw_set_desc_link(व्योम *ds, u32 ds_link)
अणु
	काष्ठा ar9003_txc *ads = ds;

	ads->link = ds_link;
	ads->ctl10 &= ~AR_TxPtrChkSum;
	ads->ctl10 |= ar9003_calc_ptr_chksum(ads);
पूर्ण

अटल bool ar9003_hw_get_isr(काष्ठा ath_hw *ah, क्रमागत ath9k_पूर्णांक *masked,
			      u32 *sync_cause_p)
अणु
	u32 isr = 0;
	u32 mask2 = 0;
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 sync_cause = 0, async_cause, async_mask = AR_INTR_MAC_IRQ;
	bool fatal_पूर्णांक;

	अगर (ath9k_hw_mci_is_enabled(ah))
		async_mask |= AR_INTR_ASYNC_MASK_MCI;

	async_cause = REG_READ(ah, AR_INTR_ASYNC_CAUSE);

	अगर (async_cause & async_mask) अणु
		अगर ((REG_READ(ah, AR_RTC_STATUS) & AR_RTC_STATUS_M)
				== AR_RTC_STATUS_ON)
			isr = REG_READ(ah, AR_ISR);
	पूर्ण


	sync_cause = REG_READ(ah, AR_INTR_SYNC_CAUSE) & AR_INTR_SYNC_DEFAULT;

	*masked = 0;

	अगर (!isr && !sync_cause && !async_cause)
		वापस false;

	अगर (isr) अणु
		अगर (isr & AR_ISR_BCNMISC) अणु
			u32 isr2;
			isr2 = REG_READ(ah, AR_ISR_S2);

			mask2 |= ((isr2 & AR_ISR_S2_TIM) >>
				  MAP_ISR_S2_TIM);
			mask2 |= ((isr2 & AR_ISR_S2_DTIM) >>
				  MAP_ISR_S2_DTIM);
			mask2 |= ((isr2 & AR_ISR_S2_DTIMSYNC) >>
				  MAP_ISR_S2_DTIMSYNC);
			mask2 |= ((isr2 & AR_ISR_S2_CABEND) >>
				  MAP_ISR_S2_CABEND);
			mask2 |= ((isr2 & AR_ISR_S2_GTT) <<
				  MAP_ISR_S2_GTT);
			mask2 |= ((isr2 & AR_ISR_S2_CST) <<
				  MAP_ISR_S2_CST);
			mask2 |= ((isr2 & AR_ISR_S2_TSFOOR) >>
				  MAP_ISR_S2_TSFOOR);
			mask2 |= ((isr2 & AR_ISR_S2_BB_WATCHDOG) >>
				  MAP_ISR_S2_BB_WATCHDOG);

			अगर (!(pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED)) अणु
				REG_WRITE(ah, AR_ISR_S2, isr2);
				isr &= ~AR_ISR_BCNMISC;
			पूर्ण
		पूर्ण

		अगर ((pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED))
			isr = REG_READ(ah, AR_ISR_RAC);

		अगर (isr == 0xffffffff) अणु
			*masked = 0;
			वापस false;
		पूर्ण

		*masked = isr & ATH9K_INT_COMMON;

		अगर (ah->config.rx_पूर्णांकr_mitigation)
			अगर (isr & (AR_ISR_RXMINTR | AR_ISR_RXINTM))
				*masked |= ATH9K_INT_RXLP;

		अगर (ah->config.tx_पूर्णांकr_mitigation)
			अगर (isr & (AR_ISR_TXMINTR | AR_ISR_TXINTM))
				*masked |= ATH9K_INT_TX;

		अगर (isr & (AR_ISR_LP_RXOK | AR_ISR_RXERR))
			*masked |= ATH9K_INT_RXLP;

		अगर (isr & AR_ISR_HP_RXOK)
			*masked |= ATH9K_INT_RXHP;

		अगर (isr & (AR_ISR_TXOK | AR_ISR_TXERR | AR_ISR_TXEOL)) अणु
			*masked |= ATH9K_INT_TX;

			अगर (!(pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED)) अणु
				u32 s0, s1;
				s0 = REG_READ(ah, AR_ISR_S0);
				REG_WRITE(ah, AR_ISR_S0, s0);
				s1 = REG_READ(ah, AR_ISR_S1);
				REG_WRITE(ah, AR_ISR_S1, s1);

				isr &= ~(AR_ISR_TXOK | AR_ISR_TXERR |
					 AR_ISR_TXEOL);
			पूर्ण
		पूर्ण

		अगर (isr & AR_ISR_GENTMR) अणु
			u32 s5;

			अगर (pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED)
				s5 = REG_READ(ah, AR_ISR_S5_S);
			अन्यथा
				s5 = REG_READ(ah, AR_ISR_S5);

			ah->पूर्णांकr_gen_समयr_trigger =
				MS(s5, AR_ISR_S5_GENTIMER_TRIG);

			ah->पूर्णांकr_gen_समयr_thresh =
				MS(s5, AR_ISR_S5_GENTIMER_THRESH);

			अगर (ah->पूर्णांकr_gen_समयr_trigger)
				*masked |= ATH9K_INT_GENTIMER;

			अगर (!(pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED)) अणु
				REG_WRITE(ah, AR_ISR_S5, s5);
				isr &= ~AR_ISR_GENTMR;
			पूर्ण

		पूर्ण

		*masked |= mask2;

		अगर (!(pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED)) अणु
			REG_WRITE(ah, AR_ISR, isr);

			(व्योम) REG_READ(ah, AR_ISR);
		पूर्ण

		अगर (*masked & ATH9K_INT_BB_WATCHDOG)
			ar9003_hw_bb_watchकरोg_पढ़ो(ah);
	पूर्ण

	अगर (async_cause & AR_INTR_ASYNC_MASK_MCI)
		ar9003_mci_get_isr(ah, masked);

	अगर (sync_cause) अणु
		अगर (sync_cause_p)
			*sync_cause_p = sync_cause;
		fatal_पूर्णांक =
			(sync_cause &
			 (AR_INTR_SYNC_HOST1_FATAL | AR_INTR_SYNC_HOST1_PERR))
			? true : false;

		अगर (fatal_पूर्णांक) अणु
			अगर (sync_cause & AR_INTR_SYNC_HOST1_FATAL) अणु
				ath_dbg(common, ANY,
					"received PCI FATAL interrupt\n");
			पूर्ण
			अगर (sync_cause & AR_INTR_SYNC_HOST1_PERR) अणु
				ath_dbg(common, ANY,
					"received PCI PERR interrupt\n");
			पूर्ण
			*masked |= ATH9K_INT_FATAL;
		पूर्ण

		अगर (sync_cause & AR_INTR_SYNC_RADM_CPL_TIMEOUT) अणु
			REG_WRITE(ah, AR_RC, AR_RC_HOSTIF);
			REG_WRITE(ah, AR_RC, 0);
			*masked |= ATH9K_INT_FATAL;
		पूर्ण

		अगर (sync_cause & AR_INTR_SYNC_LOCAL_TIMEOUT)
			ath_dbg(common, INTERRUPT,
				"AR_INTR_SYNC_LOCAL_TIMEOUT\n");

		REG_WRITE(ah, AR_INTR_SYNC_CAUSE_CLR, sync_cause);
		(व्योम) REG_READ(ah, AR_INTR_SYNC_CAUSE_CLR);

	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक ar9003_hw_proc_txdesc(काष्ठा ath_hw *ah, व्योम *ds,
				 काष्ठा ath_tx_status *ts)
अणु
	काष्ठा ar9003_txs *ads;
	u32 status;

	ads = &ah->ts_ring[ah->ts_tail];

	status = READ_ONCE(ads->status8);
	अगर ((status & AR_TxDone) == 0)
		वापस -EINPROGRESS;

	ah->ts_tail = (ah->ts_tail + 1) % ah->ts_size;

	अगर ((MS(ads->ds_info, AR_DescId) != ATHEROS_VENDOR_ID) ||
	    (MS(ads->ds_info, AR_TxRxDesc) != 1)) अणु
		ath_dbg(ath9k_hw_common(ah), XMIT,
			"Tx Descriptor error %x\n", ads->ds_info);
		स_रखो(ads, 0, माप(*ads));
		वापस -EIO;
	पूर्ण

	ts->ts_rateindex = MS(status, AR_FinalTxIdx);
	ts->ts_seqnum = MS(status, AR_SeqNum);
	ts->tid = MS(status, AR_TxTid);

	ts->qid = MS(ads->ds_info, AR_TxQcuNum);
	ts->desc_id = MS(ads->status1, AR_TxDescId);
	ts->ts_tstamp = ads->status4;
	ts->ts_status = 0;
	ts->ts_flags  = 0;

	अगर (status & AR_TxOpExceeded)
		ts->ts_status |= ATH9K_TXERR_XTXOP;
	status = READ_ONCE(ads->status2);
	ts->ts_rssi_ctl0 = MS(status, AR_TxRSSIAnt00);
	ts->ts_rssi_ctl1 = MS(status, AR_TxRSSIAnt01);
	ts->ts_rssi_ctl2 = MS(status, AR_TxRSSIAnt02);
	अगर (status & AR_TxBaStatus) अणु
		ts->ts_flags |= ATH9K_TX_BA;
		ts->ba_low = ads->status5;
		ts->ba_high = ads->status6;
	पूर्ण

	status = READ_ONCE(ads->status3);
	अगर (status & AR_ExcessiveRetries)
		ts->ts_status |= ATH9K_TXERR_XRETRY;
	अगर (status & AR_Filtered)
		ts->ts_status |= ATH9K_TXERR_FILT;
	अगर (status & AR_FIFOUnderrun) अणु
		ts->ts_status |= ATH9K_TXERR_FIFO;
		ath9k_hw_updatetxtriglevel(ah, true);
	पूर्ण
	अगर (status & AR_TxTimerExpired)
		ts->ts_status |= ATH9K_TXERR_TIMER_EXPIRED;
	अगर (status & AR_DescCfgErr)
		ts->ts_flags |= ATH9K_TX_DESC_CFG_ERR;
	अगर (status & AR_TxDataUnderrun) अणु
		ts->ts_flags |= ATH9K_TX_DATA_UNDERRUN;
		ath9k_hw_updatetxtriglevel(ah, true);
	पूर्ण
	अगर (status & AR_TxDelimUnderrun) अणु
		ts->ts_flags |= ATH9K_TX_DELIM_UNDERRUN;
		ath9k_hw_updatetxtriglevel(ah, true);
	पूर्ण
	ts->ts_लघुretry = MS(status, AR_RTSFailCnt);
	ts->ts_दीर्घretry = MS(status, AR_DataFailCnt);
	ts->ts_virtcol = MS(status, AR_VirtRetryCnt);

	status = READ_ONCE(ads->status7);
	ts->ts_rssi = MS(status, AR_TxRSSICombined);
	ts->ts_rssi_ext0 = MS(status, AR_TxRSSIAnt10);
	ts->ts_rssi_ext1 = MS(status, AR_TxRSSIAnt11);
	ts->ts_rssi_ext2 = MS(status, AR_TxRSSIAnt12);

	स_रखो(ads, 0, माप(*ads));

	वापस 0;
पूर्ण

अटल पूर्णांक ar9003_hw_get_duration(काष्ठा ath_hw *ah, स्थिर व्योम *ds, पूर्णांक index)
अणु
	स्थिर काष्ठा ar9003_txc *adc = ds;

	चयन (index) अणु
	हाल 0:
		वापस MS(READ_ONCE(adc->ctl15), AR_PacketDur0);
	हाल 1:
		वापस MS(READ_ONCE(adc->ctl15), AR_PacketDur1);
	हाल 2:
		वापस MS(READ_ONCE(adc->ctl16), AR_PacketDur2);
	हाल 3:
		वापस MS(READ_ONCE(adc->ctl16), AR_PacketDur3);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

व्योम ar9003_hw_attach_mac_ops(काष्ठा ath_hw *hw)
अणु
	काष्ठा ath_hw_ops *ops = ath9k_hw_ops(hw);

	ops->rx_enable = ar9003_hw_rx_enable;
	ops->set_desc_link = ar9003_hw_set_desc_link;
	ops->get_isr = ar9003_hw_get_isr;
	ops->set_txdesc = ar9003_set_txdesc;
	ops->proc_txdesc = ar9003_hw_proc_txdesc;
	ops->get_duration = ar9003_hw_get_duration;
पूर्ण

व्योम ath9k_hw_set_rx_bufsize(काष्ठा ath_hw *ah, u16 buf_size)
अणु
	REG_WRITE(ah, AR_DATABUF_SIZE, buf_size & AR_DATABUF_SIZE_MASK);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_set_rx_bufsize);

व्योम ath9k_hw_addrxbuf_edma(काष्ठा ath_hw *ah, u32 rxdp,
			    क्रमागत ath9k_rx_qtype qtype)
अणु
	अगर (qtype == ATH9K_RX_QUEUE_HP)
		REG_WRITE(ah, AR_HP_RXDP, rxdp);
	अन्यथा
		REG_WRITE(ah, AR_LP_RXDP, rxdp);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_addrxbuf_edma);

पूर्णांक ath9k_hw_process_rxdesc_edma(काष्ठा ath_hw *ah, काष्ठा ath_rx_status *rxs,
				 व्योम *buf_addr)
अणु
	काष्ठा ar9003_rxs *rxsp = buf_addr;
	अचिन्हित पूर्णांक phyerr;

	अगर ((rxsp->status11 & AR_RxDone) == 0)
		वापस -EINPROGRESS;

	अगर (MS(rxsp->ds_info, AR_DescId) != 0x168c)
		वापस -EINVAL;

	अगर ((rxsp->ds_info & (AR_TxRxDesc | AR_CtrlStat)) != 0)
		वापस -EINPROGRESS;

	rxs->rs_status = 0;
	rxs->rs_flags =  0;
	rxs->enc_flags = 0;
	rxs->bw = RATE_INFO_BW_20;

	rxs->rs_datalen = rxsp->status2 & AR_DataLen;
	rxs->rs_tstamp =  rxsp->status3;

	/* XXX: Keycache */
	rxs->rs_rssi = MS(rxsp->status5, AR_RxRSSICombined);
	rxs->rs_rssi_ctl[0] = MS(rxsp->status1, AR_RxRSSIAnt00);
	rxs->rs_rssi_ctl[1] = MS(rxsp->status1, AR_RxRSSIAnt01);
	rxs->rs_rssi_ctl[2] = MS(rxsp->status1, AR_RxRSSIAnt02);
	rxs->rs_rssi_ext[0] = MS(rxsp->status5, AR_RxRSSIAnt10);
	rxs->rs_rssi_ext[1] = MS(rxsp->status5, AR_RxRSSIAnt11);
	rxs->rs_rssi_ext[2] = MS(rxsp->status5, AR_RxRSSIAnt12);

	अगर (rxsp->status11 & AR_RxKeyIdxValid)
		rxs->rs_keyix = MS(rxsp->status11, AR_KeyIdx);
	अन्यथा
		rxs->rs_keyix = ATH9K_RXKEYIX_INVALID;

	rxs->rs_rate = MS(rxsp->status1, AR_RxRate);
	rxs->rs_more = (rxsp->status2 & AR_RxMore) ? 1 : 0;

	rxs->rs_firstaggr = (rxsp->status11 & AR_RxFirstAggr) ? 1 : 0;
	rxs->rs_isaggr = (rxsp->status11 & AR_RxAggr) ? 1 : 0;
	rxs->rs_moreaggr = (rxsp->status11 & AR_RxMoreAggr) ? 1 : 0;
	rxs->rs_antenna = (MS(rxsp->status4, AR_RxAntenna) & 0x7);
	rxs->enc_flags |= (rxsp->status4 & AR_GI) ? RX_ENC_FLAG_SHORT_GI : 0;
	rxs->bw = (rxsp->status4 & AR_2040) ? RATE_INFO_BW_40 : RATE_INFO_BW_20;

	rxs->evm0 = rxsp->status6;
	rxs->evm1 = rxsp->status7;
	rxs->evm2 = rxsp->status8;
	rxs->evm3 = rxsp->status9;
	rxs->evm4 = (rxsp->status10 & 0xffff);

	अगर (rxsp->status11 & AR_PreDelimCRCErr)
		rxs->rs_flags |= ATH9K_RX_DELIM_CRC_PRE;

	अगर (rxsp->status11 & AR_PostDelimCRCErr)
		rxs->rs_flags |= ATH9K_RX_DELIM_CRC_POST;

	अगर (rxsp->status11 & AR_DecryptBusyErr)
		rxs->rs_flags |= ATH9K_RX_DECRYPT_BUSY;

	अगर ((rxsp->status11 & AR_RxFrameOK) == 0) अणु
		/*
		 * AR_CRCErr will bet set to true अगर we're on the last
		 * subframe and the AR_PostDelimCRCErr is caught.
		 * In a way this also gives us a guarantee that when
		 * (!(AR_CRCErr) && (AR_PostDelimCRCErr)) we cannot
		 * possibly be reviewing the last subframe. AR_CRCErr
		 * is the CRC of the actual data.
		 */
		अगर (rxsp->status11 & AR_CRCErr)
			rxs->rs_status |= ATH9K_RXERR_CRC;
		अन्यथा अगर (rxsp->status11 & AR_DecryptCRCErr)
			rxs->rs_status |= ATH9K_RXERR_DECRYPT;
		अन्यथा अगर (rxsp->status11 & AR_MichaelErr)
			rxs->rs_status |= ATH9K_RXERR_MIC;
		अगर (rxsp->status11 & AR_PHYErr) अणु
			phyerr = MS(rxsp->status11, AR_PHYErrCode);
			/*
			 * If we reach a poपूर्णांक here where AR_PostDelimCRCErr is
			 * true it implies we're *not* on the last subframe. In
			 * in that हाल that we know alपढ़ोy that the CRC of
			 * the frame was OK, and MAC would send an ACK क्रम that
			 * subframe, even अगर we did get a phy error of type
			 * ATH9K_PHYERR_OFDM_RESTART. This is only applicable
			 * to frame that are prior to the last subframe.
			 * The AR_PostDelimCRCErr is the CRC क्रम the MPDU
			 * delimiter, which contains the 4 reserved bits,
			 * the MPDU length (12 bits), and follows the MPDU
			 * delimiter क्रम an A-MPDU subframe (0x4E = 'N' ASCII).
			 */
			अगर ((phyerr == ATH9K_PHYERR_OFDM_RESTART) &&
			    (rxsp->status11 & AR_PostDelimCRCErr)) अणु
				rxs->rs_phyerr = 0;
			पूर्ण अन्यथा अणु
				rxs->rs_status |= ATH9K_RXERR_PHY;
				rxs->rs_phyerr = phyerr;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rxsp->status11 & AR_KeyMiss)
		rxs->rs_status |= ATH9K_RXERR_KEYMISS;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_process_rxdesc_edma);

व्योम ath9k_hw_reset_txstatus_ring(काष्ठा ath_hw *ah)
अणु
	ah->ts_tail = 0;

	स_रखो((व्योम *) ah->ts_ring, 0,
		ah->ts_size * माप(काष्ठा ar9003_txs));

	ath_dbg(ath9k_hw_common(ah), XMIT,
		"TS Start 0x%x End 0x%x Virt %p, Size %d\n",
		ah->ts_paddr_start, ah->ts_paddr_end,
		ah->ts_ring, ah->ts_size);

	REG_WRITE(ah, AR_Q_STATUS_RING_START, ah->ts_paddr_start);
	REG_WRITE(ah, AR_Q_STATUS_RING_END, ah->ts_paddr_end);
पूर्ण

व्योम ath9k_hw_setup_statusring(काष्ठा ath_hw *ah, व्योम *ts_start,
			       u32 ts_paddr_start,
			       u16 size)
अणु

	ah->ts_paddr_start = ts_paddr_start;
	ah->ts_paddr_end = ts_paddr_start + (size * माप(काष्ठा ar9003_txs));
	ah->ts_size = size;
	ah->ts_ring = ts_start;

	ath9k_hw_reset_txstatus_ring(ah);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_setup_statusring);
