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
#समावेश <linux/export.h>

#घोषणा AR_BufLen           0x00000fff

अटल व्योम ar9002_hw_rx_enable(काष्ठा ath_hw *ah)
अणु
	REG_WRITE(ah, AR_CR, AR_CR_RXE);
पूर्ण

अटल व्योम ar9002_hw_set_desc_link(व्योम *ds, u32 ds_link)
अणु
	((काष्ठा ath_desc*) ds)->ds_link = ds_link;
पूर्ण

अटल bool ar9002_hw_get_isr(काष्ठा ath_hw *ah, क्रमागत ath9k_पूर्णांक *masked,
			      u32 *sync_cause_p)
अणु
	u32 isr = 0;
	u32 mask2 = 0;
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;
	u32 sync_cause = 0;
	bool fatal_पूर्णांक = false;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (!AR_SREV_9100(ah)) अणु
		अगर (REG_READ(ah, AR_INTR_ASYNC_CAUSE) & AR_INTR_MAC_IRQ) अणु
			अगर ((REG_READ(ah, AR_RTC_STATUS) & AR_RTC_STATUS_M)
			    == AR_RTC_STATUS_ON) अणु
				isr = REG_READ(ah, AR_ISR);
			पूर्ण
		पूर्ण

		sync_cause = REG_READ(ah, AR_INTR_SYNC_CAUSE) &
			AR_INTR_SYNC_DEFAULT;

		*masked = 0;

		अगर (!isr && !sync_cause)
			वापस false;
	पूर्ण अन्यथा अणु
		*masked = 0;
		isr = REG_READ(ah, AR_ISR);
	पूर्ण

	अगर (isr) अणु
		अगर (isr & AR_ISR_BCNMISC) अणु
			u32 isr2;
			isr2 = REG_READ(ah, AR_ISR_S2);
			अगर (isr2 & AR_ISR_S2_TIM)
				mask2 |= ATH9K_INT_TIM;
			अगर (isr2 & AR_ISR_S2_DTIM)
				mask2 |= ATH9K_INT_DTIM;
			अगर (isr2 & AR_ISR_S2_DTIMSYNC)
				mask2 |= ATH9K_INT_DTIMSYNC;
			अगर (isr2 & (AR_ISR_S2_CABEND))
				mask2 |= ATH9K_INT_CABEND;
			अगर (isr2 & AR_ISR_S2_GTT)
				mask2 |= ATH9K_INT_GTT;
			अगर (isr2 & AR_ISR_S2_CST)
				mask2 |= ATH9K_INT_CST;
			अगर (isr2 & AR_ISR_S2_TSFOOR)
				mask2 |= ATH9K_INT_TSFOOR;

			अगर (!(pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED)) अणु
				REG_WRITE(ah, AR_ISR_S2, isr2);
				isr &= ~AR_ISR_BCNMISC;
			पूर्ण
		पूर्ण

		अगर (pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED)
			isr = REG_READ(ah, AR_ISR_RAC);

		अगर (isr == 0xffffffff) अणु
			*masked = 0;
			वापस false;
		पूर्ण

		*masked = isr & ATH9K_INT_COMMON;

		अगर (isr & (AR_ISR_RXMINTR | AR_ISR_RXINTM |
			   AR_ISR_RXOK | AR_ISR_RXERR))
			*masked |= ATH9K_INT_RX;

		अगर (isr &
		    (AR_ISR_TXOK | AR_ISR_TXDESC | AR_ISR_TXERR |
		     AR_ISR_TXEOL)) अणु
			u32 s0_s, s1_s;

			*masked |= ATH9K_INT_TX;

			अगर (pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED) अणु
				s0_s = REG_READ(ah, AR_ISR_S0_S);
				s1_s = REG_READ(ah, AR_ISR_S1_S);
			पूर्ण अन्यथा अणु
				s0_s = REG_READ(ah, AR_ISR_S0);
				REG_WRITE(ah, AR_ISR_S0, s0_s);
				s1_s = REG_READ(ah, AR_ISR_S1);
				REG_WRITE(ah, AR_ISR_S1, s1_s);

				isr &= ~(AR_ISR_TXOK |
					 AR_ISR_TXDESC |
					 AR_ISR_TXERR |
					 AR_ISR_TXEOL);
			पूर्ण

			ah->पूर्णांकr_txqs |= MS(s0_s, AR_ISR_S0_QCU_TXOK);
			ah->पूर्णांकr_txqs |= MS(s0_s, AR_ISR_S0_QCU_TXDESC);
			ah->पूर्णांकr_txqs |= MS(s1_s, AR_ISR_S1_QCU_TXERR);
			ah->पूर्णांकr_txqs |= MS(s1_s, AR_ISR_S1_QCU_TXEOL);
		पूर्ण

		अगर (isr & AR_ISR_RXORN) अणु
			ath_dbg(common, INTERRUPT,
				"receive FIFO overrun interrupt\n");
		पूर्ण

		*masked |= mask2;
	पूर्ण

	अगर (!AR_SREV_9100(ah) && (isr & AR_ISR_GENTMR)) अणु
		u32 s5_s;

		अगर (pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED) अणु
			s5_s = REG_READ(ah, AR_ISR_S5_S);
		पूर्ण अन्यथा अणु
			s5_s = REG_READ(ah, AR_ISR_S5);
		पूर्ण

		ah->पूर्णांकr_gen_समयr_trigger =
				MS(s5_s, AR_ISR_S5_GENTIMER_TRIG);

		ah->पूर्णांकr_gen_समयr_thresh =
			MS(s5_s, AR_ISR_S5_GENTIMER_THRESH);

		अगर (ah->पूर्णांकr_gen_समयr_trigger)
			*masked |= ATH9K_INT_GENTIMER;

		अगर ((s5_s & AR_ISR_S5_TIM_TIMER) &&
		    !(pCap->hw_caps & ATH9K_HW_CAP_AUTOSLEEP))
			*masked |= ATH9K_INT_TIM_TIMER;

		अगर (!(pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED)) अणु
			REG_WRITE(ah, AR_ISR_S5, s5_s);
			isr &= ~AR_ISR_GENTMR;
		पूर्ण
	पूर्ण

	अगर (!(pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED)) अणु
		REG_WRITE(ah, AR_ISR, isr);
		REG_READ(ah, AR_ISR);
	पूर्ण

	अगर (AR_SREV_9100(ah))
		वापस true;

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
			ath_dbg(common, INTERRUPT,
				"AR_INTR_SYNC_RADM_CPL_TIMEOUT\n");
			REG_WRITE(ah, AR_RC, AR_RC_HOSTIF);
			REG_WRITE(ah, AR_RC, 0);
			*masked |= ATH9K_INT_FATAL;
		पूर्ण
		अगर (sync_cause & AR_INTR_SYNC_LOCAL_TIMEOUT) अणु
			ath_dbg(common, INTERRUPT,
				"AR_INTR_SYNC_LOCAL_TIMEOUT\n");
		पूर्ण

		REG_WRITE(ah, AR_INTR_SYNC_CAUSE_CLR, sync_cause);
		(व्योम) REG_READ(ah, AR_INTR_SYNC_CAUSE_CLR);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम
ar9002_set_txdesc(काष्ठा ath_hw *ah, व्योम *ds, काष्ठा ath_tx_info *i)
अणु
	काष्ठा ar5416_desc *ads = AR5416DESC(ds);
	u32 ctl1, ctl6;

	ads->ds_txstatus0 = ads->ds_txstatus1 = 0;
	ads->ds_txstatus2 = ads->ds_txstatus3 = 0;
	ads->ds_txstatus4 = ads->ds_txstatus5 = 0;
	ads->ds_txstatus6 = ads->ds_txstatus7 = 0;
	ads->ds_txstatus8 = ads->ds_txstatus9 = 0;

	WRITE_ONCE(ads->ds_link, i->link);
	WRITE_ONCE(ads->ds_data, i->buf_addr[0]);

	ctl1 = i->buf_len[0] | (i->is_last ? 0 : AR_TxMore);
	ctl6 = SM(i->keytype, AR_EncrType);

	अगर (AR_SREV_9285(ah)) अणु
		ads->ds_ctl8 = 0;
		ads->ds_ctl9 = 0;
		ads->ds_ctl10 = 0;
		ads->ds_ctl11 = 0;
	पूर्ण

	अगर ((i->is_first || i->is_last) &&
	    i->aggr != AGGR_BUF_MIDDLE && i->aggr != AGGR_BUF_LAST) अणु
		WRITE_ONCE(ads->ds_ctl2, set11nTries(i->rates, 0)
			| set11nTries(i->rates, 1)
			| set11nTries(i->rates, 2)
			| set11nTries(i->rates, 3)
			| (i->dur_update ? AR_DurUpdateEna : 0)
			| SM(0, AR_BurstDur));

		WRITE_ONCE(ads->ds_ctl3, set11nRate(i->rates, 0)
			| set11nRate(i->rates, 1)
			| set11nRate(i->rates, 2)
			| set11nRate(i->rates, 3));
	पूर्ण अन्यथा अणु
		WRITE_ONCE(ads->ds_ctl2, 0);
		WRITE_ONCE(ads->ds_ctl3, 0);
	पूर्ण

	अगर (!i->is_first) अणु
		WRITE_ONCE(ads->ds_ctl0, 0);
		WRITE_ONCE(ads->ds_ctl1, ctl1);
		WRITE_ONCE(ads->ds_ctl6, ctl6);
		वापस;
	पूर्ण

	ctl1 |= (i->keyix != ATH9K_TXKEYIX_INVALID ? SM(i->keyix, AR_DestIdx) : 0)
		| SM(i->type, AR_FrameType)
		| (i->flags & ATH9K_TXDESC_NOACK ? AR_NoAck : 0)
		| (i->flags & ATH9K_TXDESC_EXT_ONLY ? AR_ExtOnly : 0)
		| (i->flags & ATH9K_TXDESC_EXT_AND_CTL ? AR_ExtAndCtl : 0);

	चयन (i->aggr) अणु
	हाल AGGR_BUF_FIRST:
		ctl6 |= SM(i->aggr_len, AR_AggrLen);
		fallthrough;
	हाल AGGR_BUF_MIDDLE:
		ctl1 |= AR_IsAggr | AR_MoreAggr;
		ctl6 |= SM(i->ndelim, AR_PadDelim);
		अवरोध;
	हाल AGGR_BUF_LAST:
		ctl1 |= AR_IsAggr;
		अवरोध;
	हाल AGGR_BUF_NONE:
		अवरोध;
	पूर्ण

	WRITE_ONCE(ads->ds_ctl0, (i->pkt_len & AR_FrameLen)
		| (i->flags & ATH9K_TXDESC_VMF ? AR_VirtMoreFrag : 0)
		| SM(i->txघातer[0], AR_XmitPower0)
		| (i->flags & ATH9K_TXDESC_VEOL ? AR_VEOL : 0)
		| (i->flags & ATH9K_TXDESC_INTREQ ? AR_TxIntrReq : 0)
		| (i->keyix != ATH9K_TXKEYIX_INVALID ? AR_DestIdxValid : 0)
		| (i->flags & ATH9K_TXDESC_CLRDMASK ? AR_ClrDestMask : 0)
		| (i->flags & ATH9K_TXDESC_RTSENA ? AR_RTSEnable :
		   (i->flags & ATH9K_TXDESC_CTSENA ? AR_CTSEnable : 0)));

	WRITE_ONCE(ads->ds_ctl1, ctl1);
	WRITE_ONCE(ads->ds_ctl6, ctl6);

	अगर (i->aggr == AGGR_BUF_MIDDLE || i->aggr == AGGR_BUF_LAST)
		वापस;

	WRITE_ONCE(ads->ds_ctl4, set11nPktDurRTSCTS(i->rates, 0)
		| set11nPktDurRTSCTS(i->rates, 1));

	WRITE_ONCE(ads->ds_ctl5, set11nPktDurRTSCTS(i->rates, 2)
		| set11nPktDurRTSCTS(i->rates, 3));

	WRITE_ONCE(ads->ds_ctl7, set11nRateFlags(i->rates, 0)
		| set11nRateFlags(i->rates, 1)
		| set11nRateFlags(i->rates, 2)
		| set11nRateFlags(i->rates, 3)
		| SM(i->rtscts_rate, AR_RTSCTSRate));

	WRITE_ONCE(ads->ds_ctl9, SM(i->txघातer[1], AR_XmitPower1));
	WRITE_ONCE(ads->ds_ctl10, SM(i->txघातer[2], AR_XmitPower2));
	WRITE_ONCE(ads->ds_ctl11, SM(i->txघातer[3], AR_XmitPower3));
पूर्ण

अटल पूर्णांक ar9002_hw_proc_txdesc(काष्ठा ath_hw *ah, व्योम *ds,
				 काष्ठा ath_tx_status *ts)
अणु
	काष्ठा ar5416_desc *ads = AR5416DESC(ds);
	u32 status;

	status = READ_ONCE(ads->ds_txstatus9);
	अगर ((status & AR_TxDone) == 0)
		वापस -EINPROGRESS;

	ts->ts_tstamp = ads->AR_SendTimestamp;
	ts->ts_status = 0;
	ts->ts_flags = 0;

	अगर (status & AR_TxOpExceeded)
		ts->ts_status |= ATH9K_TXERR_XTXOP;
	ts->tid = MS(status, AR_TxTid);
	ts->ts_rateindex = MS(status, AR_FinalTxIdx);
	ts->ts_seqnum = MS(status, AR_SeqNum);

	status = READ_ONCE(ads->ds_txstatus0);
	ts->ts_rssi_ctl0 = MS(status, AR_TxRSSIAnt00);
	ts->ts_rssi_ctl1 = MS(status, AR_TxRSSIAnt01);
	ts->ts_rssi_ctl2 = MS(status, AR_TxRSSIAnt02);
	अगर (status & AR_TxBaStatus) अणु
		ts->ts_flags |= ATH9K_TX_BA;
		ts->ba_low = ads->AR_BaBiपंचांगapLow;
		ts->ba_high = ads->AR_BaBiपंचांगapHigh;
	पूर्ण

	status = READ_ONCE(ads->ds_txstatus1);
	अगर (status & AR_FrmXmitOK)
		ts->ts_status |= ATH9K_TX_ACKED;
	अन्यथा अणु
		अगर (status & AR_ExcessiveRetries)
			ts->ts_status |= ATH9K_TXERR_XRETRY;
		अगर (status & AR_Filtered)
			ts->ts_status |= ATH9K_TXERR_FILT;
		अगर (status & AR_FIFOUnderrun) अणु
			ts->ts_status |= ATH9K_TXERR_FIFO;
			ath9k_hw_updatetxtriglevel(ah, true);
		पूर्ण
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

	status = READ_ONCE(ads->ds_txstatus5);
	ts->ts_rssi = MS(status, AR_TxRSSICombined);
	ts->ts_rssi_ext0 = MS(status, AR_TxRSSIAnt10);
	ts->ts_rssi_ext1 = MS(status, AR_TxRSSIAnt11);
	ts->ts_rssi_ext2 = MS(status, AR_TxRSSIAnt12);

	ts->evm0 = ads->AR_TxEVM0;
	ts->evm1 = ads->AR_TxEVM1;
	ts->evm2 = ads->AR_TxEVM2;

	वापस 0;
पूर्ण

अटल पूर्णांक ar9002_hw_get_duration(काष्ठा ath_hw *ah, स्थिर व्योम *ds, पूर्णांक index)
अणु
	काष्ठा ar5416_desc *ads = AR5416DESC(ds);

	चयन (index) अणु
	हाल 0:
		वापस MS(READ_ONCE(ads->ds_ctl4), AR_PacketDur0);
	हाल 1:
		वापस MS(READ_ONCE(ads->ds_ctl4), AR_PacketDur1);
	हाल 2:
		वापस MS(READ_ONCE(ads->ds_ctl5), AR_PacketDur2);
	हाल 3:
		वापस MS(READ_ONCE(ads->ds_ctl5), AR_PacketDur3);
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

व्योम ath9k_hw_setuprxdesc(काष्ठा ath_hw *ah, काष्ठा ath_desc *ds,
			  u32 size, u32 flags)
अणु
	काष्ठा ar5416_desc *ads = AR5416DESC(ds);

	ads->ds_ctl1 = size & AR_BufLen;
	अगर (flags & ATH9K_RXDESC_INTREQ)
		ads->ds_ctl1 |= AR_RxIntrReq;

	स_रखो(&ads->u.rx, 0, माप(ads->u.rx));
पूर्ण
EXPORT_SYMBOL(ath9k_hw_setuprxdesc);

व्योम ar9002_hw_attach_mac_ops(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_hw_ops *ops = ath9k_hw_ops(ah);

	ops->rx_enable = ar9002_hw_rx_enable;
	ops->set_desc_link = ar9002_hw_set_desc_link;
	ops->get_isr = ar9002_hw_get_isr;
	ops->set_txdesc = ar9002_set_txdesc;
	ops->proc_txdesc = ar9002_hw_proc_txdesc;
	ops->get_duration = ar9002_hw_get_duration;
पूर्ण
