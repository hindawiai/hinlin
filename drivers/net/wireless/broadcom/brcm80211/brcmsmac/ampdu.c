<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#समावेश <net/mac80211.h>

#समावेश "rate.h"
#समावेश "scb.h"
#समावेश "phy/phy_hal.h"
#समावेश "antsel.h"
#समावेश "main.h"
#समावेश "ampdu.h"
#समावेश "debug.h"
#समावेश "brcms_trace_events.h"

/* max number of mpdus in an ampdu */
#घोषणा AMPDU_MAX_MPDU			32
/* max number of mpdus in an ampdu to a legacy */
#घोषणा AMPDU_NUM_MPDU_LEGACY		16
/* max Tx ba winकरोw size (in pdu) */
#घोषणा AMPDU_TX_BA_MAX_WSIZE		64
/* शेष Tx ba winकरोw size (in pdu) */
#घोषणा AMPDU_TX_BA_DEF_WSIZE		64
/* शेष Rx ba winकरोw size (in pdu) */
#घोषणा AMPDU_RX_BA_DEF_WSIZE		64
/* max Rx ba winकरोw size (in pdu) */
#घोषणा AMPDU_RX_BA_MAX_WSIZE		64
/* max dur of tx ampdu (in msec) */
#घोषणा	AMPDU_MAX_DUR			5
/* शेष tx retry limit */
#घोषणा AMPDU_DEF_RETRY_LIMIT		5
/* शेष tx retry limit at reg rate */
#घोषणा AMPDU_DEF_RR_RETRY_LIMIT	2
/* शेष ffpld reserved bytes */
#घोषणा AMPDU_DEF_FFPLD_RSVD		2048
/* # of inis to be मुक्तd on detach */
#घोषणा AMPDU_INI_FREE			10
/* max # of mpdus released at a समय */
#घोषणा	AMPDU_SCB_MAX_RELEASE		20

#घोषणा NUM_FFPLD_FIFO 4	/* number of fअगरo concerned by pre-loading */
#घोषणा FFPLD_TX_MAX_UNFL   200	/* शेष value of the average number of ampdu
				 * without underflows
				 */
#घोषणा FFPLD_MPDU_SIZE 1800	/* estimate of maximum mpdu size */
#घोषणा FFPLD_MAX_MCS 23	/* we करोn't deal with mcs 32 */
#घोषणा FFPLD_PLD_INCR 1000	/* increments in bytes */
#घोषणा FFPLD_MAX_AMPDU_CNT 5000	/* maximum number of ampdu we
					 * accumulate between resets.
					 */

#घोषणा AMPDU_DELIMITER_LEN	4

/* max allowed number of mpdus in an ampdu (2 streams) */
#घोषणा AMPDU_NUM_MPDU		16

#घोषणा TX_SEQ_TO_INDEX(seq) ((seq) % AMPDU_TX_BA_MAX_WSIZE)

/* max possible overhead per mpdu in the ampdu; 3 is क्रम roundup अगर needed */
#घोषणा AMPDU_MAX_MPDU_OVERHEAD (FCS_LEN + DOT11_ICV_AES_LEN +\
	AMPDU_DELIMITER_LEN + 3\
	+ DOT11_A4_HDR_LEN + DOT11_QOS_LEN + DOT11_IV_MAX_LEN)

/* modulo add/sub, bound = 2^k */
#घोषणा MODADD_POW2(x, y, bound) (((x) + (y)) & ((bound) - 1))
#घोषणा MODSUB_POW2(x, y, bound) (((x) - (y)) & ((bound) - 1))

/* काष्ठाure to hold tx fअगरo inक्रमmation and pre-loading state
 * counters specअगरic to tx underflows of ampdus
 * some counters might be redundant with the ones in wlc or ampdu काष्ठाures.
 * This allows to मुख्यtain a specअगरic state independently of
 * how often and/or when the wlc counters are updated.
 *
 * ampdu_pld_size: number of bytes to be pre-loaded
 * mcs2ampdu_table: per-mcs max # of mpdus in an ampdu
 * prev_txfunfl: num of underflows last पढ़ो from the HW macstats counter
 * accum_txfunfl: num of underflows since we modअगरied pld params
 * accum_txampdu: num of tx ampdu since we modअगरied pld params
 * prev_txampdu: previous पढ़ोing of tx ampdu
 * dmaxferrate: estimated dma avg xfer rate in kbits/sec
 */
काष्ठा brcms_fअगरo_info अणु
	u16 ampdu_pld_size;
	u8 mcs2ampdu_table[FFPLD_MAX_MCS + 1];
	u16 prev_txfunfl;
	u32 accum_txfunfl;
	u32 accum_txampdu;
	u32 prev_txampdu;
	u32 dmaxferrate;
पूर्ण;

/* AMPDU module specअगरic state
 *
 * wlc: poपूर्णांकer to मुख्य wlc काष्ठाure
 * scb_handle: scb cubby handle to retrieve data from scb
 * ini_enable: per-tid initiator enable/disable of ampdu
 * ba_tx_wsize: Tx ba winकरोw size (in pdu)
 * ba_rx_wsize: Rx ba winकरोw size (in pdu)
 * retry_limit: mpdu transmit retry limit
 * rr_retry_limit: mpdu transmit retry limit at regular rate
 * retry_limit_tid: per-tid mpdu transmit retry limit
 * rr_retry_limit_tid: per-tid mpdu transmit retry limit at regular rate
 * mpdu_density: min mpdu spacing (0-7) ==> 2^(x-1)/8 usec
 * max_pdu: max pdus allowed in ampdu
 * dur: max duration of an ampdu (in msec)
 * rx_factor: maximum rx ampdu factor (0-3) ==> 2^(13+x) bytes
 * ffpld_rsvd: number of bytes to reserve क्रम preload
 * max_txlen: max size of ampdu per mcs, bw and sgi
 * mfbr: enable multiple fallback rate
 * tx_max_funl: underflows should be kept such that
 *		(tx_max_funfl*underflows) < tx frames
 * fअगरo_tb: table of fअगरo infos
 */
काष्ठा ampdu_info अणु
	काष्ठा brcms_c_info *wlc;
	पूर्णांक scb_handle;
	u8 ini_enable[AMPDU_MAX_SCB_TID];
	u8 ba_tx_wsize;
	u8 ba_rx_wsize;
	u8 retry_limit;
	u8 rr_retry_limit;
	u8 retry_limit_tid[AMPDU_MAX_SCB_TID];
	u8 rr_retry_limit_tid[AMPDU_MAX_SCB_TID];
	u8 mpdu_density;
	s8 max_pdu;
	u8 dur;
	u8 rx_factor;
	u32 ffpld_rsvd;
	u32 max_txlen[MCS_TABLE_SIZE][2][2];
	bool mfbr;
	u32 tx_max_funl;
	काष्ठा brcms_fअगरo_info fअगरo_tb[NUM_FFPLD_FIFO];
पूर्ण;

/* used क्रम flushing ampdu packets */
काष्ठा cb_del_ampdu_pars अणु
	काष्ठा ieee80211_sta *sta;
	u16 tid;
पूर्ण;

अटल व्योम brcms_c_scb_ampdu_update_max_txlen(काष्ठा ampdu_info *ampdu, u8 dur)
अणु
	u32 rate, mcs;

	क्रम (mcs = 0; mcs < MCS_TABLE_SIZE; mcs++) अणु
		/* rate is in Kbps; dur is in msec ==> len = (rate * dur) / 8 */
		/* 20MHz, No SGI */
		rate = mcs_2_rate(mcs, false, false);
		ampdu->max_txlen[mcs][0][0] = (rate * dur) >> 3;
		/* 40 MHz, No SGI */
		rate = mcs_2_rate(mcs, true, false);
		ampdu->max_txlen[mcs][1][0] = (rate * dur) >> 3;
		/* 20MHz, SGI */
		rate = mcs_2_rate(mcs, false, true);
		ampdu->max_txlen[mcs][0][1] = (rate * dur) >> 3;
		/* 40 MHz, SGI */
		rate = mcs_2_rate(mcs, true, true);
		ampdu->max_txlen[mcs][1][1] = (rate * dur) >> 3;
	पूर्ण
पूर्ण

अटल bool brcms_c_ampdu_cap(काष्ठा ampdu_info *ampdu)
अणु
	अगर (BRCMS_PHY_11N_CAP(ampdu->wlc->band))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक brcms_c_ampdu_set(काष्ठा ampdu_info *ampdu, bool on)
अणु
	काष्ठा brcms_c_info *wlc = ampdu->wlc;
	काष्ठा bcma_device *core = wlc->hw->d11core;

	wlc->pub->_ampdu = false;

	अगर (on) अणु
		अगर (!(wlc->pub->_n_enab & SUPPORT_11N)) अणु
			brcms_err(core, "wl%d: driver not nmode enabled\n",
				  wlc->pub->unit);
			वापस -ENOTSUPP;
		पूर्ण
		अगर (!brcms_c_ampdu_cap(ampdu)) अणु
			brcms_err(core, "wl%d: device not ampdu capable\n",
				  wlc->pub->unit);
			वापस -ENOTSUPP;
		पूर्ण
		wlc->pub->_ampdu = on;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम brcms_c_ffpld_init(काष्ठा ampdu_info *ampdu)
अणु
	पूर्णांक i, j;
	काष्ठा brcms_fअगरo_info *fअगरo;

	क्रम (j = 0; j < NUM_FFPLD_FIFO; j++) अणु
		fअगरo = (ampdu->fअगरo_tb + j);
		fअगरo->ampdu_pld_size = 0;
		क्रम (i = 0; i <= FFPLD_MAX_MCS; i++)
			fअगरo->mcs2ampdu_table[i] = 255;
		fअगरo->dmaxferrate = 0;
		fअगरo->accum_txampdu = 0;
		fअगरo->prev_txfunfl = 0;
		fअगरo->accum_txfunfl = 0;

	पूर्ण
पूर्ण

काष्ठा ampdu_info *brcms_c_ampdu_attach(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा ampdu_info *ampdu;
	पूर्णांक i;

	ampdu = kzalloc(माप(काष्ठा ampdu_info), GFP_ATOMIC);
	अगर (!ampdu)
		वापस शून्य;

	ampdu->wlc = wlc;

	क्रम (i = 0; i < AMPDU_MAX_SCB_TID; i++)
		ampdu->ini_enable[i] = true;
	/* Disable ampdu क्रम VO by शेष */
	ampdu->ini_enable[PRIO_8021D_VO] = false;
	ampdu->ini_enable[PRIO_8021D_NC] = false;

	/* Disable ampdu क्रम BK by शेष since not enough fअगरo space */
	ampdu->ini_enable[PRIO_8021D_NONE] = false;
	ampdu->ini_enable[PRIO_8021D_BK] = false;

	ampdu->ba_tx_wsize = AMPDU_TX_BA_DEF_WSIZE;
	ampdu->ba_rx_wsize = AMPDU_RX_BA_DEF_WSIZE;
	ampdu->mpdu_density = AMPDU_DEF_MPDU_DENSITY;
	ampdu->max_pdu = AUTO;
	ampdu->dur = AMPDU_MAX_DUR;

	ampdu->ffpld_rsvd = AMPDU_DEF_FFPLD_RSVD;
	/*
	 * bump max ampdu rcv size to 64k क्रम all 11n
	 * devices except 4321A0 and 4321A1
	 */
	अगर (BRCMS_ISNPHY(wlc->band) && NREV_LT(wlc->band->phyrev, 2))
		ampdu->rx_factor = IEEE80211_HT_MAX_AMPDU_32K;
	अन्यथा
		ampdu->rx_factor = IEEE80211_HT_MAX_AMPDU_64K;
	ampdu->retry_limit = AMPDU_DEF_RETRY_LIMIT;
	ampdu->rr_retry_limit = AMPDU_DEF_RR_RETRY_LIMIT;

	क्रम (i = 0; i < AMPDU_MAX_SCB_TID; i++) अणु
		ampdu->retry_limit_tid[i] = ampdu->retry_limit;
		ampdu->rr_retry_limit_tid[i] = ampdu->rr_retry_limit;
	पूर्ण

	brcms_c_scb_ampdu_update_max_txlen(ampdu, ampdu->dur);
	ampdu->mfbr = false;
	/* try to set ampdu to the शेष value */
	brcms_c_ampdu_set(ampdu, wlc->pub->_ampdu);

	ampdu->tx_max_funl = FFPLD_TX_MAX_UNFL;
	brcms_c_ffpld_init(ampdu);

	वापस ampdu;
पूर्ण

व्योम brcms_c_ampdu_detach(काष्ठा ampdu_info *ampdu)
अणु
	kमुक्त(ampdu);
पूर्ण

अटल व्योम brcms_c_scb_ampdu_update_config(काष्ठा ampdu_info *ampdu,
					    काष्ठा scb *scb)
अणु
	काष्ठा scb_ampdu *scb_ampdu = &scb->scb_ampdu;
	पूर्णांक i;

	scb_ampdu->max_pdu = AMPDU_NUM_MPDU;

	/* go back to legacy size अगर some preloading is occurring */
	क्रम (i = 0; i < NUM_FFPLD_FIFO; i++) अणु
		अगर (ampdu->fअगरo_tb[i].ampdu_pld_size > FFPLD_PLD_INCR)
			scb_ampdu->max_pdu = AMPDU_NUM_MPDU_LEGACY;
	पूर्ण

	/* apply user override */
	अगर (ampdu->max_pdu != AUTO)
		scb_ampdu->max_pdu = (u8) ampdu->max_pdu;

	scb_ampdu->release = min_t(u8, scb_ampdu->max_pdu,
				   AMPDU_SCB_MAX_RELEASE);

	अगर (scb_ampdu->max_rx_ampdu_bytes)
		scb_ampdu->release = min_t(u8, scb_ampdu->release,
			scb_ampdu->max_rx_ampdu_bytes / 1600);

	scb_ampdu->release = min(scb_ampdu->release,
				 ampdu->fअगरo_tb[TX_AC_BE_FIFO].
				 mcs2ampdu_table[FFPLD_MAX_MCS]);
पूर्ण

अटल व्योम brcms_c_scb_ampdu_update_config_all(काष्ठा ampdu_info *ampdu)
अणु
	brcms_c_scb_ampdu_update_config(ampdu, &ampdu->wlc->pri_scb);
पूर्ण

अटल व्योम brcms_c_ffpld_calc_mcs2ampdu_table(काष्ठा ampdu_info *ampdu, पूर्णांक f)
अणु
	पूर्णांक i;
	u32 phy_rate, dma_rate, पंचांगp;
	u8 max_mpdu;
	काष्ठा brcms_fअगरo_info *fअगरo = (ampdu->fअगरo_tb + f);

	/* recompute the dma rate */
	/* note : we भागide/multiply by 100 to aव्योम पूर्णांकeger overflows */
	max_mpdu = min_t(u8, fअगरo->mcs2ampdu_table[FFPLD_MAX_MCS],
			 AMPDU_NUM_MPDU_LEGACY);
	phy_rate = mcs_2_rate(FFPLD_MAX_MCS, true, false);
	dma_rate =
	    (((phy_rate / 100) *
	      (max_mpdu * FFPLD_MPDU_SIZE - fअगरo->ampdu_pld_size))
	     / (max_mpdu * FFPLD_MPDU_SIZE)) * 100;
	fअगरo->dmaxferrate = dma_rate;

	/* fill up the mcs2ampdu table; करो not recalc the last mcs */
	dma_rate = dma_rate >> 7;
	क्रम (i = 0; i < FFPLD_MAX_MCS; i++) अणु
		/* shअगरting to keep it within पूर्णांकeger range */
		phy_rate = mcs_2_rate(i, true, false) >> 7;
		अगर (phy_rate > dma_rate) अणु
			पंचांगp = ((fअगरo->ampdu_pld_size * phy_rate) /
			       ((phy_rate - dma_rate) * FFPLD_MPDU_SIZE)) + 1;
			पंचांगp = min_t(u32, पंचांगp, 255);
			fअगरo->mcs2ampdu_table[i] = (u8) पंचांगp;
		पूर्ण
	पूर्ण
पूर्ण

/* evaluate the dma transfer rate using the tx underflows as feedback.
 * If necessary, increase tx fअगरo preloading. If not enough,
 * decrease maximum ampdu size क्रम each mcs till underflows stop
 * Return 1 अगर pre-loading not active, -1 अगर not an underflow event,
 * 0 अगर pre-loading module took care of the event.
 */
अटल पूर्णांक brcms_c_ffpld_check_txfunfl(काष्ठा brcms_c_info *wlc, पूर्णांक fid)
अणु
	काष्ठा ampdu_info *ampdu = wlc->ampdu;
	u32 phy_rate = mcs_2_rate(FFPLD_MAX_MCS, true, false);
	u32 txunfl_ratio;
	u8 max_mpdu;
	u32 current_ampdu_cnt = 0;
	u16 max_pld_size;
	u32 new_txunfl;
	काष्ठा brcms_fअगरo_info *fअगरo = (ampdu->fअगरo_tb + fid);
	uपूर्णांक xmtfअगरo_sz;
	u16 cur_txunfl;

	/* वापस अगर we got here क्रम a dअगरferent reason than underflows */
	cur_txunfl = brcms_b_पढ़ो_shm(wlc->hw,
				      M_UCODE_MACSTAT +
				      दुरत्व(काष्ठा macstat, txfunfl[fid]));
	new_txunfl = (u16) (cur_txunfl - fअगरo->prev_txfunfl);
	अगर (new_txunfl == 0) अणु
		brcms_dbg_ht(wlc->hw->d11core,
			     "TX status FRAG set but no tx underflows\n");
		वापस -1;
	पूर्ण
	fअगरo->prev_txfunfl = cur_txunfl;

	अगर (!ampdu->tx_max_funl)
		वापस 1;

	/* check अगर fअगरo is big enough */
	अगर (brcms_b_xmtfअगरo_sz_get(wlc->hw, fid, &xmtfअगरo_sz))
		वापस -1;

	अगर ((TXFIFO_SIZE_UNIT * (u32) xmtfअगरo_sz) <= ampdu->ffpld_rsvd)
		वापस 1;

	max_pld_size = TXFIFO_SIZE_UNIT * xmtfअगरo_sz - ampdu->ffpld_rsvd;
	fअगरo->accum_txfunfl += new_txunfl;

	/* we need to रुको क्रम at least 10 underflows */
	अगर (fअगरo->accum_txfunfl < 10)
		वापस 0;

	brcms_dbg_ht(wlc->hw->d11core, "ampdu_count %d  tx_underflows %d\n",
		     current_ampdu_cnt, fअगरo->accum_txfunfl);

	/*
	   compute the current ratio of tx unfl per ampdu.
	   When the current ampdu count becomes too
	   big जबतक the ratio reमुख्यs small, we reset
	   the current count in order to not
	   पूर्णांकroduce too big of a latency in detecting a
	   large amount of tx underflows later.
	 */

	txunfl_ratio = current_ampdu_cnt / fअगरo->accum_txfunfl;

	अगर (txunfl_ratio > ampdu->tx_max_funl) अणु
		अगर (current_ampdu_cnt >= FFPLD_MAX_AMPDU_CNT)
			fअगरo->accum_txfunfl = 0;

		वापस 0;
	पूर्ण
	max_mpdu = min_t(u8, fअगरo->mcs2ampdu_table[FFPLD_MAX_MCS],
			 AMPDU_NUM_MPDU_LEGACY);

	/* In हाल max value max_pdu is alपढ़ोy lower than
	   the fअगरo depth, there is nothing more we can करो.
	 */

	अगर (fअगरo->ampdu_pld_size >= max_mpdu * FFPLD_MPDU_SIZE) अणु
		fअगरo->accum_txfunfl = 0;
		वापस 0;
	पूर्ण

	अगर (fअगरo->ampdu_pld_size < max_pld_size) अणु

		/* increment by TX_FIFO_PLD_INC bytes */
		fअगरo->ampdu_pld_size += FFPLD_PLD_INCR;
		अगर (fअगरo->ampdu_pld_size > max_pld_size)
			fअगरo->ampdu_pld_size = max_pld_size;

		/* update scb release size */
		brcms_c_scb_ampdu_update_config_all(ampdu);

		/*
		 * compute a new dma xfer rate क्रम max_mpdu @ max mcs.
		 * This is the minimum dma rate that can achieve no
		 * underflow condition क्रम the current mpdu size.
		 *
		 * note : we भागide/multiply by 100 to aव्योम पूर्णांकeger overflows
		 */
		fअगरo->dmaxferrate =
		    (((phy_rate / 100) *
		      (max_mpdu * FFPLD_MPDU_SIZE - fअगरo->ampdu_pld_size))
		     / (max_mpdu * FFPLD_MPDU_SIZE)) * 100;

		brcms_dbg_ht(wlc->hw->d11core,
			     "DMA estimated transfer rate %d; "
			     "pre-load size %d\n",
			     fअगरo->dmaxferrate, fअगरo->ampdu_pld_size);
	पूर्ण अन्यथा अणु

		/* decrease ampdu size */
		अगर (fअगरo->mcs2ampdu_table[FFPLD_MAX_MCS] > 1) अणु
			अगर (fअगरo->mcs2ampdu_table[FFPLD_MAX_MCS] == 255)
				fअगरo->mcs2ampdu_table[FFPLD_MAX_MCS] =
				    AMPDU_NUM_MPDU_LEGACY - 1;
			अन्यथा
				fअगरo->mcs2ampdu_table[FFPLD_MAX_MCS] -= 1;

			/* recompute the table */
			brcms_c_ffpld_calc_mcs2ampdu_table(ampdu, fid);

			/* update scb release size */
			brcms_c_scb_ampdu_update_config_all(ampdu);
		पूर्ण
	पूर्ण
	fअगरo->accum_txfunfl = 0;
	वापस 0;
पूर्ण

व्योम
brcms_c_ampdu_tx_operational(काष्ठा brcms_c_info *wlc, u8 tid,
	u8 ba_wsize,		/* negotiated ba winकरोw size (in pdu) */
	uपूर्णांक max_rx_ampdu_bytes) /* from ht_cap in beacon */
अणु
	काष्ठा scb_ampdu *scb_ampdu;
	काष्ठा scb_ampdu_tid_ini *ini;
	काष्ठा ampdu_info *ampdu = wlc->ampdu;
	काष्ठा scb *scb = &wlc->pri_scb;
	scb_ampdu = &scb->scb_ampdu;

	अगर (!ampdu->ini_enable[tid]) अणु
		brcms_err(wlc->hw->d11core, "%s: Rejecting tid %d\n",
			  __func__, tid);
		वापस;
	पूर्ण

	ini = &scb_ampdu->ini[tid];
	ini->tid = tid;
	ini->scb = scb_ampdu->scb;
	ini->ba_wsize = ba_wsize;
	scb_ampdu->max_rx_ampdu_bytes = max_rx_ampdu_bytes;
पूर्ण

व्योम brcms_c_ampdu_reset_session(काष्ठा brcms_ampdu_session *session,
				 काष्ठा brcms_c_info *wlc)
अणु
	session->wlc = wlc;
	skb_queue_head_init(&session->skb_list);
	session->max_ampdu_len = 0;    /* determined from first MPDU */
	session->max_ampdu_frames = 0; /* determined from first MPDU */
	session->ampdu_len = 0;
	session->dma_len = 0;
पूर्ण

/*
 * Preps the given packet क्रम AMPDU based on the session data. If the
 * frame cannot be accomodated in the current session, -ENOSPC is
 * वापसed.
 */
पूर्णांक brcms_c_ampdu_add_frame(काष्ठा brcms_ampdu_session *session,
			    काष्ठा sk_buff *p)
अणु
	काष्ठा brcms_c_info *wlc = session->wlc;
	काष्ठा ampdu_info *ampdu = wlc->ampdu;
	काष्ठा scb *scb = &wlc->pri_scb;
	काष्ठा scb_ampdu *scb_ampdu = &scb->scb_ampdu;
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(p);
	काष्ठा ieee80211_tx_rate *txrate = tx_info->status.rates;
	काष्ठा d11txh *txh = (काष्ठा d11txh *)p->data;
	अचिन्हित ampdu_frames;
	u8 ndelim, tid;
	u8 *plcp;
	uपूर्णांक len;
	u16 mcl;
	bool fbr_iscck;
	bool rr;

	ndelim = txh->RTSPLCPFallback[AMPDU_FBR_शून्य_DELIM];
	plcp = (u8 *)(txh + 1);
	fbr_iscck = !(le16_to_cpu(txh->XtraFrameTypes) & 0x03);
	len = fbr_iscck ? BRCMS_GET_CCK_PLCP_LEN(txh->FragPLCPFallback) :
			  BRCMS_GET_MIMO_PLCP_LEN(txh->FragPLCPFallback);
	len = roundup(len, 4) + (ndelim + 1) * AMPDU_DELIMITER_LEN;

	ampdu_frames = skb_queue_len(&session->skb_list);
	अगर (ampdu_frames != 0) अणु
		काष्ठा sk_buff *first;

		अगर (ampdu_frames + 1 > session->max_ampdu_frames ||
		    session->ampdu_len + len > session->max_ampdu_len)
			वापस -ENOSPC;

		/*
		 * We aren't really out of space अगर the new frame is of
		 * a dअगरferent priority, but we want the same behaviour
		 * so वापस -ENOSPC anyway.
		 *
		 * XXX: The old AMPDU code did this, but is it really
		 * necessary?
		 */
		first = skb_peek(&session->skb_list);
		अगर (p->priority != first->priority)
			वापस -ENOSPC;
	पूर्ण

	/*
	 * Now that we're sure this frame can be accomodated, update the
	 * session inक्रमmation.
	 */
	session->ampdu_len += len;
	session->dma_len += p->len;

	tid = (u8)p->priority;

	/* Handle retry limits */
	अगर (txrate[0].count <= ampdu->rr_retry_limit_tid[tid]) अणु
		txrate[0].count++;
		rr = true;
	पूर्ण अन्यथा अणु
		txrate[1].count++;
		rr = false;
	पूर्ण

	अगर (ampdu_frames == 0) अणु
		u8 plcp0, plcp3, is40, sgi, mcs;
		uपूर्णांक fअगरo = le16_to_cpu(txh->TxFrameID) & TXFID_QUEUE_MASK;
		काष्ठा brcms_fअगरo_info *f = &ampdu->fअगरo_tb[fअगरo];

		अगर (rr) अणु
			plcp0 = plcp[0];
			plcp3 = plcp[3];
		पूर्ण अन्यथा अणु
			plcp0 = txh->FragPLCPFallback[0];
			plcp3 = txh->FragPLCPFallback[3];

		पूर्ण

		/* Limit AMPDU size based on MCS */
		is40 = (plcp0 & MIMO_PLCP_40MHZ) ? 1 : 0;
		sgi = plcp3_issgi(plcp3) ? 1 : 0;
		mcs = plcp0 & ~MIMO_PLCP_40MHZ;
		session->max_ampdu_len = min(scb_ampdu->max_rx_ampdu_bytes,
					     ampdu->max_txlen[mcs][is40][sgi]);

		session->max_ampdu_frames = scb_ampdu->max_pdu;
		अगर (mcs_2_rate(mcs, true, false) >= f->dmaxferrate) अणु
			session->max_ampdu_frames =
				min_t(u16, f->mcs2ampdu_table[mcs],
				      session->max_ampdu_frames);
		पूर्ण
	पूर्ण

	/*
	 * Treat all frames as "middle" frames of AMPDU here. First and
	 * last frames must be fixed up after all MPDUs have been prepped.
	 */
	mcl = le16_to_cpu(txh->MacTxControlLow);
	mcl &= ~TXC_AMPDU_MASK;
	mcl |= (TXC_AMPDU_MIDDLE << TXC_AMPDU_SHIFT);
	mcl &= ~(TXC_STARTMSDU | TXC_SENDRTS | TXC_SENDCTS);
	txh->MacTxControlLow = cpu_to_le16(mcl);
	txh->PreloadSize = 0;	/* always शेष to 0 */

	skb_queue_tail(&session->skb_list, p);

	वापस 0;
पूर्ण

व्योम brcms_c_ampdu_finalize(काष्ठा brcms_ampdu_session *session)
अणु
	काष्ठा brcms_c_info *wlc = session->wlc;
	काष्ठा ampdu_info *ampdu = wlc->ampdu;
	काष्ठा sk_buff *first, *last;
	काष्ठा d11txh *txh;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा ieee80211_tx_rate *txrate;
	u8 ndelim;
	u8 *plcp;
	uपूर्णांक len;
	uपूर्णांक fअगरo;
	काष्ठा brcms_fअगरo_info *f;
	u16 mcl;
	bool fbr;
	bool fbr_iscck;
	काष्ठा ieee80211_rts *rts;
	bool use_rts = false, use_cts = false;
	u16 dma_len = session->dma_len;
	u16 mimo_ctlchbw = PHY_TXC1_BW_20MHZ;
	u32 rspec = 0, rspec_fallback = 0;
	u32 rts_rspec = 0, rts_rspec_fallback = 0;
	u8 plcp0, is40, mcs;
	u16 mch;
	u8 preamble_type = BRCMS_GF_PREAMBLE;
	u8 fbr_preamble_type = BRCMS_GF_PREAMBLE;
	u8 rts_preamble_type = BRCMS_LONG_PREAMBLE;
	u8 rts_fbr_preamble_type = BRCMS_LONG_PREAMBLE;

	अगर (skb_queue_empty(&session->skb_list))
		वापस;

	first = skb_peek(&session->skb_list);
	last = skb_peek_tail(&session->skb_list);

	/* Need to fix up last MPDU first to adjust AMPDU length */
	txh = (काष्ठा d11txh *)last->data;
	fअगरo = le16_to_cpu(txh->TxFrameID) & TXFID_QUEUE_MASK;
	f = &ampdu->fअगरo_tb[fअगरo];

	mcl = le16_to_cpu(txh->MacTxControlLow);
	mcl &= ~TXC_AMPDU_MASK;
	mcl |= (TXC_AMPDU_LAST << TXC_AMPDU_SHIFT);
	txh->MacTxControlLow = cpu_to_le16(mcl);

	/* हटाओ the null delimiter after last mpdu */
	ndelim = txh->RTSPLCPFallback[AMPDU_FBR_शून्य_DELIM];
	txh->RTSPLCPFallback[AMPDU_FBR_शून्य_DELIM] = 0;
	session->ampdu_len -= ndelim * AMPDU_DELIMITER_LEN;

	/* हटाओ the pad len from last mpdu */
	fbr_iscck = ((le16_to_cpu(txh->XtraFrameTypes) & 0x3) == 0);
	len = fbr_iscck ? BRCMS_GET_CCK_PLCP_LEN(txh->FragPLCPFallback) :
			  BRCMS_GET_MIMO_PLCP_LEN(txh->FragPLCPFallback);
	session->ampdu_len -= roundup(len, 4) - len;

	/* Now fix up the first MPDU */
	tx_info = IEEE80211_SKB_CB(first);
	txrate = tx_info->status.rates;
	txh = (काष्ठा d11txh *)first->data;
	plcp = (u8 *)(txh + 1);
	rts = (काष्ठा ieee80211_rts *)&txh->rts_frame;

	mcl = le16_to_cpu(txh->MacTxControlLow);
	/* If only one MPDU leave it marked as last */
	अगर (first != last) अणु
		mcl &= ~TXC_AMPDU_MASK;
		mcl |= (TXC_AMPDU_FIRST << TXC_AMPDU_SHIFT);
	पूर्ण
	mcl |= TXC_STARTMSDU;
	अगर (ieee80211_is_rts(rts->frame_control)) अणु
		mcl |= TXC_SENDRTS;
		use_rts = true;
	पूर्ण
	अगर (ieee80211_is_cts(rts->frame_control)) अणु
		mcl |= TXC_SENDCTS;
		use_cts = true;
	पूर्ण
	txh->MacTxControlLow = cpu_to_le16(mcl);

	fbr = txrate[1].count > 0;
	अगर (!fbr)
		plcp0 = plcp[0];
	अन्यथा
		plcp0 = txh->FragPLCPFallback[0];

	is40 = (plcp0 & MIMO_PLCP_40MHZ) ? 1 : 0;
	mcs = plcp0 & ~MIMO_PLCP_40MHZ;

	अगर (is40) अणु
		अगर (CHSPEC_SB_UPPER(wlc_phy_chanspec_get(wlc->band->pi)))
			mimo_ctlchbw = PHY_TXC1_BW_20MHZ_UP;
		अन्यथा
			mimo_ctlchbw = PHY_TXC1_BW_20MHZ;
	पूर्ण

	/* rebuild the rspec and rspec_fallback */
	rspec = RSPEC_MIMORATE;
	rspec |= plcp[0] & ~MIMO_PLCP_40MHZ;
	अगर (plcp[0] & MIMO_PLCP_40MHZ)
		rspec |= (PHY_TXC1_BW_40MHZ << RSPEC_BW_SHIFT);

	fbr_iscck = !(le16_to_cpu(txh->XtraFrameTypes) & 0x03);
	अगर (fbr_iscck) अणु
		rspec_fallback =
			cck_rspec(cck_phy2mac_rate(txh->FragPLCPFallback[0]));
	पूर्ण अन्यथा अणु
		rspec_fallback = RSPEC_MIMORATE;
		rspec_fallback |= txh->FragPLCPFallback[0] & ~MIMO_PLCP_40MHZ;
		अगर (txh->FragPLCPFallback[0] & MIMO_PLCP_40MHZ)
			rspec_fallback |= PHY_TXC1_BW_40MHZ << RSPEC_BW_SHIFT;
	पूर्ण

	अगर (use_rts || use_cts) अणु
		rts_rspec =
			brcms_c_rspec_to_rts_rspec(wlc, rspec,
						   false, mimo_ctlchbw);
		rts_rspec_fallback =
			brcms_c_rspec_to_rts_rspec(wlc, rspec_fallback,
						   false, mimo_ctlchbw);
	पूर्ण

	BRCMS_SET_MIMO_PLCP_LEN(plcp, session->ampdu_len);
	/* mark plcp to indicate ampdu */
	BRCMS_SET_MIMO_PLCP_AMPDU(plcp);

	/* reset the mixed mode header durations */
	अगर (txh->MModeLen) अणु
		u16 mmodelen = brcms_c_calc_lsig_len(wlc, rspec,
						     session->ampdu_len);
		txh->MModeLen = cpu_to_le16(mmodelen);
		preamble_type = BRCMS_MM_PREAMBLE;
	पूर्ण
	अगर (txh->MModeFbrLen) अणु
		u16 mmfbrlen = brcms_c_calc_lsig_len(wlc, rspec_fallback,
						     session->ampdu_len);
		txh->MModeFbrLen = cpu_to_le16(mmfbrlen);
		fbr_preamble_type = BRCMS_MM_PREAMBLE;
	पूर्ण

	/* set the preload length */
	अगर (mcs_2_rate(mcs, true, false) >= f->dmaxferrate) अणु
		dma_len = min(dma_len, f->ampdu_pld_size);
		txh->PreloadSize = cpu_to_le16(dma_len);
	पूर्ण अन्यथा अणु
		txh->PreloadSize = 0;
	पूर्ण

	mch = le16_to_cpu(txh->MacTxControlHigh);

	/* update RTS dur fields */
	अगर (use_rts || use_cts) अणु
		u16 durid;
		अगर ((mch & TXC_PREAMBLE_RTS_MAIN_SHORT) ==
		    TXC_PREAMBLE_RTS_MAIN_SHORT)
			rts_preamble_type = BRCMS_SHORT_PREAMBLE;

		अगर ((mch & TXC_PREAMBLE_RTS_FB_SHORT) ==
		     TXC_PREAMBLE_RTS_FB_SHORT)
			rts_fbr_preamble_type = BRCMS_SHORT_PREAMBLE;

		durid = brcms_c_compute_rtscts_dur(wlc, use_cts, rts_rspec,
						   rspec, rts_preamble_type,
						   preamble_type,
						   session->ampdu_len, true);
		rts->duration = cpu_to_le16(durid);
		durid = brcms_c_compute_rtscts_dur(wlc, use_cts,
						   rts_rspec_fallback,
						   rspec_fallback,
						   rts_fbr_preamble_type,
						   fbr_preamble_type,
						   session->ampdu_len, true);
		txh->RTSDurFallback = cpu_to_le16(durid);
		/* set TxFesTimeNormal */
		txh->TxFesTimeNormal = rts->duration;
		/* set fallback rate version of TxFesTimeNormal */
		txh->TxFesTimeFallback = txh->RTSDurFallback;
	पूर्ण

	/* set flag and plcp क्रम fallback rate */
	अगर (fbr) अणु
		mch |= TXC_AMPDU_FBR;
		txh->MacTxControlHigh = cpu_to_le16(mch);
		BRCMS_SET_MIMO_PLCP_AMPDU(plcp);
		BRCMS_SET_MIMO_PLCP_AMPDU(txh->FragPLCPFallback);
	पूर्ण

	brcms_dbg_ht(wlc->hw->d11core, "wl%d: count %d ampdu_len %d\n",
		     wlc->pub->unit, skb_queue_len(&session->skb_list),
		     session->ampdu_len);
पूर्ण

अटल व्योम
brcms_c_ampdu_rate_status(काष्ठा brcms_c_info *wlc,
			  काष्ठा ieee80211_tx_info *tx_info,
			  काष्ठा tx_status *txs, u8 mcs)
अणु
	काष्ठा ieee80211_tx_rate *txrate = tx_info->status.rates;
	पूर्णांक i;

	/* clear the rest of the rates */
	क्रम (i = 2; i < IEEE80211_TX_MAX_RATES; i++) अणु
		txrate[i].idx = -1;
		txrate[i].count = 0;
	पूर्ण
पूर्ण

अटल व्योम
brcms_c_ampdu_करोtxstatus_complete(काष्ठा ampdu_info *ampdu, काष्ठा scb *scb,
			      काष्ठा sk_buff *p, काष्ठा tx_status *txs,
			      u32 s1, u32 s2)
अणु
	काष्ठा scb_ampdu *scb_ampdu;
	काष्ठा brcms_c_info *wlc = ampdu->wlc;
	काष्ठा scb_ampdu_tid_ini *ini;
	u8 biपंचांगap[8], queue, tid;
	काष्ठा d11txh *txh;
	u8 *plcp;
	काष्ठा ieee80211_hdr *h;
	u16 seq, start_seq = 0, bindex, index, mcl;
	u8 mcs = 0;
	bool ba_recd = false, ack_recd = false;
	u8 suc_mpdu = 0, tot_mpdu = 0;
	uपूर्णांक supr_status;
	bool retry = true;
	u16 mimoantsel = 0;
	u8 retry_limit;
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(p);

#अगर_घोषित DEBUG
	u8 hole[AMPDU_MAX_MPDU];
	स_रखो(hole, 0, माप(hole));
#पूर्ण_अगर

	scb_ampdu = &scb->scb_ampdu;
	tid = (u8) (p->priority);

	ini = &scb_ampdu->ini[tid];
	retry_limit = ampdu->retry_limit_tid[tid];
	स_रखो(biपंचांगap, 0, माप(biपंचांगap));
	queue = txs->frameid & TXFID_QUEUE_MASK;
	supr_status = txs->status & TX_STATUS_SUPR_MASK;

	अगर (txs->status & TX_STATUS_ACK_RCV) अणु
		WARN_ON(!(txs->status & TX_STATUS_INTERMEDIATE));
		start_seq = txs->sequence >> SEQNUM_SHIFT;
		biपंचांगap[0] = (txs->status & TX_STATUS_BA_BMAP03_MASK) >>
		    TX_STATUS_BA_BMAP03_SHIFT;

		WARN_ON(s1 & TX_STATUS_INTERMEDIATE);
		WARN_ON(!(s1 & TX_STATUS_AMPDU));

		biपंचांगap[0] |=
		    (s1 & TX_STATUS_BA_BMAP47_MASK) <<
		    TX_STATUS_BA_BMAP47_SHIFT;
		biपंचांगap[1] = (s1 >> 8) & 0xff;
		biपंचांगap[2] = (s1 >> 16) & 0xff;
		biपंचांगap[3] = (s1 >> 24) & 0xff;

		biपंचांगap[4] = s2 & 0xff;
		biपंचांगap[5] = (s2 >> 8) & 0xff;
		biपंचांगap[6] = (s2 >> 16) & 0xff;
		biपंचांगap[7] = (s2 >> 24) & 0xff;

		ba_recd = true;
	पूर्ण अन्यथा अणु
		अगर (supr_status) अणु
			अगर (supr_status == TX_STATUS_SUPR_BADCH) अणु
				brcms_dbg_ht(wlc->hw->d11core,
					  "%s: Pkt tx suppressed, illegal channel possibly %d\n",
					  __func__, CHSPEC_CHANNEL(
					  wlc->शेष_bss->chanspec));
			पूर्ण अन्यथा अणु
				अगर (supr_status != TX_STATUS_SUPR_FRAG)
					brcms_err(wlc->hw->d11core,
						  "%s: supr_status 0x%x\n",
						  __func__, supr_status);
			पूर्ण
			/* no need to retry क्रम badch; will fail again */
			अगर (supr_status == TX_STATUS_SUPR_BADCH ||
			    supr_status == TX_STATUS_SUPR_EXPTIME) अणु
				retry = false;
			पूर्ण अन्यथा अगर (supr_status == TX_STATUS_SUPR_EXPTIME) अणु
				/* TX underflow:
				 *   try tuning pre-loading or ampdu size
				 */
			पूर्ण अन्यथा अगर (supr_status == TX_STATUS_SUPR_FRAG) अणु
				/*
				 * अगर there were underflows, but pre-loading
				 * is not active, notअगरy rate adaptation.
				 */
				brcms_c_ffpld_check_txfunfl(wlc, queue);
			पूर्ण
		पूर्ण अन्यथा अगर (txs->phyerr) अणु
			brcms_dbg_ht(wlc->hw->d11core,
				     "%s: ampdu tx phy error (0x%x)\n",
				     __func__, txs->phyerr);
		पूर्ण
	पूर्ण

	/* loop through all pkts and retry अगर not acked */
	जबतक (p) अणु
		tx_info = IEEE80211_SKB_CB(p);
		txh = (काष्ठा d11txh *) p->data;
		mcl = le16_to_cpu(txh->MacTxControlLow);
		plcp = (u8 *) (txh + 1);
		h = (काष्ठा ieee80211_hdr *)(plcp + D11_PHY_HDR_LEN);
		seq = le16_to_cpu(h->seq_ctrl) >> SEQNUM_SHIFT;

		trace_brcms_txdesc(&wlc->hw->d11core->dev, txh, माप(*txh));

		अगर (tot_mpdu == 0) अणु
			mcs = plcp[0] & MIMO_PLCP_MCS_MASK;
			mimoantsel = le16_to_cpu(txh->ABI_MimoAntSel);
		पूर्ण

		index = TX_SEQ_TO_INDEX(seq);
		ack_recd = false;
		अगर (ba_recd) अणु
			पूर्णांक block_acked;

			bindex = MODSUB_POW2(seq, start_seq, SEQNUM_MAX);
			अगर (bindex < AMPDU_TX_BA_MAX_WSIZE)
				block_acked = isset(biपंचांगap, bindex);
			अन्यथा
				block_acked = 0;
			brcms_dbg_ht(wlc->hw->d11core,
				     "tid %d seq %d, start_seq %d, bindex %d set %d, index %d\n",
				     tid, seq, start_seq, bindex,
				     block_acked, index);
			/* अगर acked then clear bit and मुक्त packet */
			अगर (block_acked) अणु
				ini->txretry[index] = 0;

				/*
				 * ampdu_ack_len:
				 *   number of acked aggregated frames
				 */
				/* ampdu_len: number of aggregated frames */
				brcms_c_ampdu_rate_status(wlc, tx_info, txs,
							  mcs);
				tx_info->flags |= IEEE80211_TX_STAT_ACK;
				tx_info->flags |= IEEE80211_TX_STAT_AMPDU;
				tx_info->status.ampdu_ack_len =
					tx_info->status.ampdu_len = 1;

				skb_pull(p, D11_PHY_HDR_LEN);
				skb_pull(p, D11_TXH_LEN);

				ieee80211_tx_status_irqsafe(wlc->pub->ieee_hw,
							    p);
				ack_recd = true;
				suc_mpdu++;
			पूर्ण
		पूर्ण
		/* either retransmit or send bar अगर ack not recd */
		अगर (!ack_recd) अणु
			अगर (retry && (ini->txretry[index] < (पूर्णांक)retry_limit)) अणु
				पूर्णांक ret;
				ini->txretry[index]++;
				ret = brcms_c_txfअगरo(wlc, queue, p);
				/*
				 * We shouldn't be out of space in the DMA
				 * ring here since we're reinserting a frame
				 * that was just pulled out.
				 */
				WARN_ONCE(ret, "queue %d out of txds\n", queue);
			पूर्ण अन्यथा अणु
				/* Retry समयout */
				ieee80211_tx_info_clear_status(tx_info);
				tx_info->status.ampdu_ack_len = 0;
				tx_info->status.ampdu_len = 1;
				tx_info->flags |=
				    IEEE80211_TX_STAT_AMPDU_NO_BACK;
				skb_pull(p, D11_PHY_HDR_LEN);
				skb_pull(p, D11_TXH_LEN);
				brcms_dbg_ht(wlc->hw->d11core,
					     "BA Timeout, seq %d\n",
					     seq);
				ieee80211_tx_status_irqsafe(wlc->pub->ieee_hw,
							    p);
			पूर्ण
		पूर्ण
		tot_mpdu++;

		/* अवरोध out अगर last packet of ampdu */
		अगर (((mcl & TXC_AMPDU_MASK) >> TXC_AMPDU_SHIFT) ==
		    TXC_AMPDU_LAST)
			अवरोध;

		p = dma_getnexttxp(wlc->hw->di[queue], DMA_RANGE_TRANSMITTED);
	पूर्ण

	/* update rate state */
	brcms_c_antsel_antsel2id(wlc->asi, mimoantsel);
पूर्ण

व्योम
brcms_c_ampdu_करोtxstatus(काष्ठा ampdu_info *ampdu, काष्ठा scb *scb,
		     काष्ठा sk_buff *p, काष्ठा tx_status *txs)
अणु
	काष्ठा brcms_c_info *wlc = ampdu->wlc;
	u32 s1 = 0, s2 = 0;

	/* BMAC_NOTE: For the split driver, second level txstatus comes later
	 * So अगर the ACK was received then रुको क्रम the second level अन्यथा just
	 * call the first one
	 */
	अगर (txs->status & TX_STATUS_ACK_RCV) अणु
		u8 status_delay = 0;

		/* रुको till the next 8 bytes of txstatus is available */
		s1 = bcma_पढ़ो32(wlc->hw->d11core, D11REGOFFS(frmtxstatus));
		जबतक ((s1 & TXS_V) == 0) अणु
			udelay(1);
			status_delay++;
			अगर (status_delay > 10)
				वापस; /* error condition */
			s1 = bcma_पढ़ो32(wlc->hw->d11core,
					 D11REGOFFS(frmtxstatus));
		पूर्ण

		s2 = bcma_पढ़ो32(wlc->hw->d11core, D11REGOFFS(frmtxstatus2));
	पूर्ण

	अगर (scb) अणु
		brcms_c_ampdu_करोtxstatus_complete(ampdu, scb, p, txs, s1, s2);
	पूर्ण अन्यथा अणु
		/* loop through all pkts and मुक्त */
		u8 queue = txs->frameid & TXFID_QUEUE_MASK;
		काष्ठा d11txh *txh;
		u16 mcl;
		जबतक (p) अणु
			txh = (काष्ठा d11txh *) p->data;
			trace_brcms_txdesc(&wlc->hw->d11core->dev, txh,
					   माप(*txh));
			mcl = le16_to_cpu(txh->MacTxControlLow);
			brcmu_pkt_buf_मुक्त_skb(p);
			/* अवरोध out अगर last packet of ampdu */
			अगर (((mcl & TXC_AMPDU_MASK) >> TXC_AMPDU_SHIFT) ==
			    TXC_AMPDU_LAST)
				अवरोध;
			p = dma_getnexttxp(wlc->hw->di[queue],
					   DMA_RANGE_TRANSMITTED);
		पूर्ण
	पूर्ण
पूर्ण

व्योम brcms_c_ampdu_macaddr_upd(काष्ठा brcms_c_info *wlc)
अणु
	अक्षर ढाँचा[T_RAM_ACCESS_SZ * 2];

	/* driver needs to ग_लिखो the ta in the ढाँचा; ta is at offset 16 */
	स_रखो(ढाँचा, 0, माप(ढाँचा));
	स_नकल(ढाँचा, wlc->pub->cur_etheraddr, ETH_ALEN);
	brcms_b_ग_लिखो_ढाँचा_ram(wlc->hw, (T_BA_TPL_BASE + 16),
				  (T_RAM_ACCESS_SZ * 2),
				  ढाँचा);
पूर्ण

bool brcms_c_aggregatable(काष्ठा brcms_c_info *wlc, u8 tid)
अणु
	वापस wlc->ampdu->ini_enable[tid];
पूर्ण

व्योम brcms_c_ampdu_shm_upd(काष्ठा ampdu_info *ampdu)
अणु
	काष्ठा brcms_c_info *wlc = ampdu->wlc;

	/*
	 * Extend ucode पूर्णांकernal watchकरोg समयr to
	 * match larger received frames
	 */
	अगर ((ampdu->rx_factor & IEEE80211_HT_AMPDU_PARM_FACTOR) ==
	    IEEE80211_HT_MAX_AMPDU_64K) अणु
		brcms_b_ग_लिखो_shm(wlc->hw, M_MIMO_MAXSYM, MIMO_MAXSYM_MAX);
		brcms_b_ग_लिखो_shm(wlc->hw, M_WATCHDOG_8TU, WATCHDOG_8TU_MAX);
	पूर्ण अन्यथा अणु
		brcms_b_ग_लिखो_shm(wlc->hw, M_MIMO_MAXSYM, MIMO_MAXSYM_DEF);
		brcms_b_ग_लिखो_shm(wlc->hw, M_WATCHDOG_8TU, WATCHDOG_8TU_DEF);
	पूर्ण
पूर्ण

/*
 * callback function that helps invalidating ampdu packets in a DMA queue
 */
अटल व्योम dma_cb_fn_ampdu(व्योम *txi, व्योम *arg_a)
अणु
	काष्ठा ieee80211_sta *sta = arg_a;
	काष्ठा ieee80211_tx_info *tx_info = (काष्ठा ieee80211_tx_info *)txi;

	अगर ((tx_info->flags & IEEE80211_TX_CTL_AMPDU) &&
	    (tx_info->rate_driver_data[0] == sta || sta == शून्य))
		tx_info->rate_driver_data[0] = शून्य;
पूर्ण

/*
 * When a remote party is no दीर्घer available क्रम ampdu communication, any
 * pending tx ampdu packets in the driver have to be flushed.
 */
व्योम brcms_c_ampdu_flush(काष्ठा brcms_c_info *wlc,
		     काष्ठा ieee80211_sta *sta, u16 tid)
अणु
	brcms_c_inval_dma_pkts(wlc->hw, sta, dma_cb_fn_ampdu);
पूर्ण
