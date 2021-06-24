<शैली गुरु>
/*
 * Copyright (c) 2014, Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
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

#समावेश "ath9k.h"
#समावेश "hw.h"
#समावेश "dynack.h"

#घोषणा COMPUTE_TO		(5 * HZ)
#घोषणा LATEACK_DELAY		(10 * HZ)
#घोषणा EWMA_LEVEL		96
#घोषणा EWMA_DIV		128

/**
 * ath_dynack_get_max_to - set max समयout according to channel width
 * @ah: ath hw
 *
 */
अटल u32 ath_dynack_get_max_to(काष्ठा ath_hw *ah)
अणु
	स्थिर काष्ठा ath9k_channel *chan = ah->curchan;

	अगर (!chan)
		वापस 300;

	अगर (IS_CHAN_HT40(chan))
		वापस 300;
	अगर (IS_CHAN_HALF_RATE(chan))
		वापस 750;
	अगर (IS_CHAN_QUARTER_RATE(chan))
		वापस 1500;
	वापस 600;
पूर्ण

/*
 * ath_dynack_ewma - EWMA (Exponentially Weighted Moving Average) calculation
 */
अटल अंतरभूत पूर्णांक ath_dynack_ewma(पूर्णांक old, पूर्णांक new)
अणु
	अगर (old > 0)
		वापस (new * (EWMA_DIV - EWMA_LEVEL) +
			old * EWMA_LEVEL) / EWMA_DIV;
	अन्यथा
		वापस new;
पूर्ण

/**
 * ath_dynack_get_sअगरs - get sअगरs समय based on phy used
 * @ah: ath hw
 * @phy: phy used
 *
 */
अटल अंतरभूत u32 ath_dynack_get_sअगरs(काष्ठा ath_hw *ah, पूर्णांक phy)
अणु
	u32 sअगरs = CCK_SIFS_TIME;

	अगर (phy == WLAN_RC_PHY_OFDM) अणु
		अगर (IS_CHAN_QUARTER_RATE(ah->curchan))
			sअगरs = OFDM_SIFS_TIME_QUARTER;
		अन्यथा अगर (IS_CHAN_HALF_RATE(ah->curchan))
			sअगरs = OFDM_SIFS_TIME_HALF;
		अन्यथा
			sअगरs = OFDM_SIFS_TIME;
	पूर्ण
	वापस sअगरs;
पूर्ण

/**
 * ath_dynack_bssidmask - filter out ACK frames based on BSSID mask
 * @ah: ath hw
 * @mac: receiver address
 */
अटल अंतरभूत bool ath_dynack_bssidmask(काष्ठा ath_hw *ah, स्थिर u8 *mac)
अणु
	पूर्णांक i;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		अगर ((common->macaddr[i] & common->bssidmask[i]) !=
		    (mac[i] & common->bssidmask[i]))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * ath_dynack_set_समयout - configure समयouts/slotसमय रेजिस्टरs
 * @ah: ath hw
 * @to: समयout value
 *
 */
अटल व्योम ath_dynack_set_समयout(काष्ठा ath_hw *ah, पूर्णांक to)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक slotसमय = (to - 3) / 2;

	ath_dbg(common, DYNACK, "ACK timeout %u slottime %u\n",
		to, slotसमय);
	ath9k_hw_setslotसमय(ah, slotसमय);
	ath9k_hw_set_ack_समयout(ah, to);
	ath9k_hw_set_cts_समयout(ah, to);
पूर्ण

/**
 * ath_dynack_compute_ackto - compute ACK समयout as the maximum STA समयout
 * @ah: ath hw
 *
 * should be called जबतक holding qlock
 */
अटल व्योम ath_dynack_compute_ackto(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_dynack *da = &ah->dynack;
	काष्ठा ath_node *an;
	पूर्णांक to = 0;

	list_क्रम_each_entry(an, &da->nodes, list)
		अगर (an->ackto > to)
			to = an->ackto;

	अगर (to && da->ackto != to) अणु
		ath_dynack_set_समयout(ah, to);
		da->ackto = to;
	पूर्ण
पूर्ण

/**
 * ath_dynack_compute_to - compute STA ACK समयout
 * @ah: ath hw
 *
 * should be called जबतक holding qlock
 */
अटल व्योम ath_dynack_compute_to(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_dynack *da = &ah->dynack;
	u32 ackto, ack_ts, max_to;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ts_info *st_ts;
	काष्ठा ath_node *an;
	u8 *dst, *src;

	rcu_पढ़ो_lock();

	max_to = ath_dynack_get_max_to(ah);
	जबतक (da->st_rbf.h_rb != da->st_rbf.t_rb &&
	       da->ack_rbf.h_rb != da->ack_rbf.t_rb) अणु
		ack_ts = da->ack_rbf.tstamp[da->ack_rbf.h_rb];
		st_ts = &da->st_rbf.ts[da->st_rbf.h_rb];
		dst = da->st_rbf.addr[da->st_rbf.h_rb].h_dest;
		src = da->st_rbf.addr[da->st_rbf.h_rb].h_src;

		ath_dbg(ath9k_hw_common(ah), DYNACK,
			"ack_ts %u st_ts %u st_dur %u [%u-%u]\n",
			ack_ts, st_ts->tstamp, st_ts->dur,
			da->ack_rbf.h_rb, da->st_rbf.h_rb);

		अगर (ack_ts > st_ts->tstamp + st_ts->dur) अणु
			ackto = ack_ts - st_ts->tstamp - st_ts->dur;

			अगर (ackto < max_to) अणु
				sta = ieee80211_find_sta_by_अगरaddr(ah->hw, dst,
								   src);
				अगर (sta) अणु
					an = (काष्ठा ath_node *)sta->drv_priv;
					an->ackto = ath_dynack_ewma(an->ackto,
								    ackto);
					ath_dbg(ath9k_hw_common(ah), DYNACK,
						"%pM to %d [%u]\n", dst,
						an->ackto, ackto);
					अगर (समय_is_beक्रमe_jअगरfies(da->lto)) अणु
						ath_dynack_compute_ackto(ah);
						da->lto = jअगरfies + COMPUTE_TO;
					पूर्ण
				पूर्ण
				INCR(da->ack_rbf.h_rb, ATH_DYN_BUF);
			पूर्ण
			INCR(da->st_rbf.h_rb, ATH_DYN_BUF);
		पूर्ण अन्यथा अणु
			INCR(da->ack_rbf.h_rb, ATH_DYN_BUF);
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

/**
 * ath_dynack_sample_tx_ts - status बारtamp sampling method
 * @ah: ath hw
 * @skb: socket buffer
 * @ts: tx status info
 * @sta: station poपूर्णांकer
 *
 */
व्योम ath_dynack_sample_tx_ts(काष्ठा ath_hw *ah, काष्ठा sk_buff *skb,
			     काष्ठा ath_tx_status *ts,
			     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ath_dynack *da = &ah->dynack;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u32 dur = ts->duration;
	u8 ridx;

	अगर (!da->enabled || (info->flags & IEEE80211_TX_CTL_NO_ACK))
		वापस;

	spin_lock_bh(&da->qlock);

	hdr = (काष्ठा ieee80211_hdr *)skb->data;

	/* late ACK */
	अगर (ts->ts_status & ATH9K_TXERR_XRETRY) अणु
		अगर (ieee80211_is_assoc_req(hdr->frame_control) ||
		    ieee80211_is_assoc_resp(hdr->frame_control) ||
		    ieee80211_is_auth(hdr->frame_control)) अणु
			u32 max_to = ath_dynack_get_max_to(ah);

			ath_dbg(common, DYNACK, "late ack\n");
			ath_dynack_set_समयout(ah, max_to);
			अगर (sta) अणु
				काष्ठा ath_node *an;

				an = (काष्ठा ath_node *)sta->drv_priv;
				an->ackto = -1;
			पूर्ण
			da->lto = jअगरfies + LATEACK_DELAY;
		पूर्ण

		spin_unlock_bh(&da->qlock);
		वापस;
	पूर्ण

	ridx = ts->ts_rateindex;

	da->st_rbf.ts[da->st_rbf.t_rb].tstamp = ts->ts_tstamp;

	/* ether_addr_copy() gives a false warning on gcc-10 so use स_नकल()
	 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=97490
	 */
	स_नकल(da->st_rbf.addr[da->st_rbf.t_rb].h_dest, hdr->addr1, ETH_ALEN);
	स_नकल(da->st_rbf.addr[da->st_rbf.t_rb].h_src, hdr->addr2, ETH_ALEN);

	अगर (!(info->status.rates[ridx].flags & IEEE80211_TX_RC_MCS)) अणु
		स्थिर काष्ठा ieee80211_rate *rate;
		काष्ठा ieee80211_tx_rate *rates = info->status.rates;
		u32 phy;

		rate = &common->sbands[info->band].bitrates[rates[ridx].idx];
		अगर (info->band == NL80211_BAND_2GHZ &&
		    !(rate->flags & IEEE80211_RATE_ERP_G))
			phy = WLAN_RC_PHY_CCK;
		अन्यथा
			phy = WLAN_RC_PHY_OFDM;

		dur -= ath_dynack_get_sअगरs(ah, phy);
	पूर्ण
	da->st_rbf.ts[da->st_rbf.t_rb].dur = dur;

	INCR(da->st_rbf.t_rb, ATH_DYN_BUF);
	अगर (da->st_rbf.t_rb == da->st_rbf.h_rb)
		INCR(da->st_rbf.h_rb, ATH_DYN_BUF);

	ath_dbg(common, DYNACK, "{%pM} tx sample %u [dur %u][h %u-t %u]\n",
		hdr->addr1, ts->ts_tstamp, dur, da->st_rbf.h_rb,
		da->st_rbf.t_rb);

	ath_dynack_compute_to(ah);

	spin_unlock_bh(&da->qlock);
पूर्ण
EXPORT_SYMBOL(ath_dynack_sample_tx_ts);

/**
 * ath_dynack_sample_ack_ts - ACK बारtamp sampling method
 * @ah: ath hw
 * @skb: socket buffer
 * @ts: rx बारtamp
 *
 */
व्योम ath_dynack_sample_ack_ts(काष्ठा ath_hw *ah, काष्ठा sk_buff *skb,
			      u32 ts)
अणु
	काष्ठा ath_dynack *da = &ah->dynack;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;

	अगर (!da->enabled || !ath_dynack_bssidmask(ah, hdr->addr1))
		वापस;

	spin_lock_bh(&da->qlock);
	da->ack_rbf.tstamp[da->ack_rbf.t_rb] = ts;

	INCR(da->ack_rbf.t_rb, ATH_DYN_BUF);
	अगर (da->ack_rbf.t_rb == da->ack_rbf.h_rb)
		INCR(da->ack_rbf.h_rb, ATH_DYN_BUF);

	ath_dbg(common, DYNACK, "rx sample %u [h %u-t %u]\n",
		ts, da->ack_rbf.h_rb, da->ack_rbf.t_rb);

	ath_dynack_compute_to(ah);

	spin_unlock_bh(&da->qlock);
पूर्ण
EXPORT_SYMBOL(ath_dynack_sample_ack_ts);

/**
 * ath_dynack_node_init - init ath_node related info
 * @ah: ath hw
 * @an: ath node
 *
 */
व्योम ath_dynack_node_init(काष्ठा ath_hw *ah, काष्ठा ath_node *an)
अणु
	काष्ठा ath_dynack *da = &ah->dynack;

	an->ackto = da->ackto;

	spin_lock_bh(&da->qlock);
	list_add_tail(&an->list, &da->nodes);
	spin_unlock_bh(&da->qlock);
पूर्ण
EXPORT_SYMBOL(ath_dynack_node_init);

/**
 * ath_dynack_node_deinit - deinit ath_node related info
 * @ah: ath hw
 * @an: ath node
 *
 */
व्योम ath_dynack_node_deinit(काष्ठा ath_hw *ah, काष्ठा ath_node *an)
अणु
	काष्ठा ath_dynack *da = &ah->dynack;

	spin_lock_bh(&da->qlock);
	list_del(&an->list);
	spin_unlock_bh(&da->qlock);
पूर्ण
EXPORT_SYMBOL(ath_dynack_node_deinit);

/**
 * ath_dynack_reset - reset dynack processing
 * @ah: ath hw
 *
 */
व्योम ath_dynack_reset(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_dynack *da = &ah->dynack;
	काष्ठा ath_node *an;

	spin_lock_bh(&da->qlock);

	da->lto = jअगरfies + COMPUTE_TO;

	da->st_rbf.t_rb = 0;
	da->st_rbf.h_rb = 0;
	da->ack_rbf.t_rb = 0;
	da->ack_rbf.h_rb = 0;

	da->ackto = ath_dynack_get_max_to(ah);
	list_क्रम_each_entry(an, &da->nodes, list)
		an->ackto = da->ackto;

	/* init ackसमयout */
	ath_dynack_set_समयout(ah, da->ackto);

	spin_unlock_bh(&da->qlock);
पूर्ण
EXPORT_SYMBOL(ath_dynack_reset);

/**
 * ath_dynack_init - init dynack data काष्ठाure
 * @ah: ath hw
 *
 */
व्योम ath_dynack_init(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_dynack *da = &ah->dynack;

	स_रखो(da, 0, माप(काष्ठा ath_dynack));

	spin_lock_init(&da->qlock);
	INIT_LIST_HEAD(&da->nodes);
	/* ackto = slotसमय + sअगरs + air delay */
	da->ackto = 9 + 16 + 64;

	ah->hw->wiphy->features |= NL80211_FEATURE_ACKTO_ESTIMATION;
पूर्ण
