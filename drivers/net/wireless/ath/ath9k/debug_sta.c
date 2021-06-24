<शैली गुरु>
/*
 * Copyright (c) 2013 Qualcomm Atheros, Inc.
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

/*************/
/* node_aggr */
/*************/

अटल sमाप_प्रकार पढ़ो_file_node_aggr(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_node *an = file->निजी_data;
	काष्ठा ath_softc *sc = an->sc;
	काष्ठा ath_atx_tid *tid;
	काष्ठा ath_txq *txq;
	u32 len = 0, size = 4096;
	अक्षर *buf;
	माप_प्रकार retval;
	पूर्णांक tidno;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	अगर (!an->sta->ht_cap.ht_supported) अणु
		len = scnम_लिखो(buf, size, "%s\n",
				"HT not supported");
		जाओ निकास;
	पूर्ण

	len = scnम_लिखो(buf, size, "Max-AMPDU: %d\n",
			an->maxampdu);
	len += scnम_लिखो(buf + len, size - len, "MPDU Density: %d\n\n",
			 an->mpdudensity);

	len += scnम_लिखो(buf + len, size - len,
			 "\n%3s%11s%10s%10s%10s%10s%9s%6s%8s\n",
			 "TID", "SEQ_START", "SEQ_NEXT", "BAW_SIZE",
			 "BAW_HEAD", "BAW_TAIL", "BAR_IDX", "SCHED", "PAUSED");

	क्रम (tidno = 0; tidno < IEEE80211_NUM_TIDS; tidno++) अणु
		tid = ath_node_to_tid(an, tidno);
		txq = tid->txq;
		ath_txq_lock(sc, txq);
		अगर (tid->active) अणु
			len += scnम_लिखो(buf + len, size - len,
					 "%3d%11d%10d%10d%10d%10d%9d%6d\n",
					 tid->tidno,
					 tid->seq_start,
					 tid->seq_next,
					 tid->baw_size,
					 tid->baw_head,
					 tid->baw_tail,
					 tid->bar_index,
					 !list_empty(&tid->list));
		पूर्ण
		ath_txq_unlock(sc, txq);
	पूर्ण
निकास:
	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_node_aggr = अणु
	.पढ़ो = पढ़ो_file_node_aggr,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

/*************/
/* node_recv */
/*************/

व्योम ath_debug_rate_stats(काष्ठा ath_softc *sc,
			  काष्ठा ath_rx_status *rs,
			  काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ieee80211_rx_status *rxs;
	काष्ठा ath_rx_rate_stats *rstats;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ath_node *an;

	अगर (!ieee80211_is_data(hdr->frame_control))
		वापस;

	rcu_पढ़ो_lock();

	sta = ieee80211_find_sta_by_अगरaddr(sc->hw, hdr->addr2, शून्य);
	अगर (!sta)
		जाओ निकास;

	an = (काष्ठा ath_node *) sta->drv_priv;
	rstats = &an->rx_rate_stats;
	rxs = IEEE80211_SKB_RXCB(skb);

	अगर (IS_HT_RATE(rs->rs_rate)) अणु
		अगर (rxs->rate_idx >= ARRAY_SIZE(rstats->ht_stats))
			जाओ निकास;

		अगर (rxs->bw == RATE_INFO_BW_40)
			rstats->ht_stats[rxs->rate_idx].ht40_cnt++;
		अन्यथा
			rstats->ht_stats[rxs->rate_idx].ht20_cnt++;

		अगर (rxs->enc_flags & RX_ENC_FLAG_SHORT_GI)
			rstats->ht_stats[rxs->rate_idx].sgi_cnt++;
		अन्यथा
			rstats->ht_stats[rxs->rate_idx].lgi_cnt++;

		जाओ निकास;
	पूर्ण

	अगर (IS_CCK_RATE(rs->rs_rate)) अणु
		अगर (rxs->enc_flags & RX_ENC_FLAG_SHORTPRE)
			rstats->cck_stats[rxs->rate_idx].cck_sp_cnt++;
		अन्यथा
			rstats->cck_stats[rxs->rate_idx].cck_lp_cnt++;

		जाओ निकास;
	पूर्ण

	अगर (IS_OFDM_RATE(rs->rs_rate)) अणु
		अगर (ah->curchan->chan->band == NL80211_BAND_2GHZ)
			rstats->ofdm_stats[rxs->rate_idx - 4].ofdm_cnt++;
		अन्यथा
			rstats->ofdm_stats[rxs->rate_idx].ofdm_cnt++;
	पूर्ण
निकास:
	rcu_पढ़ो_unlock();
पूर्ण

#घोषणा PRINT_CCK_RATE(str, i, sp)					\
	करो अणु								\
		len += scnम_लिखो(buf + len, size - len,			\
			 "%11s : %10u\n",				\
			 str,						\
			 (sp) ? rstats->cck_stats[i].cck_sp_cnt :	\
			 rstats->cck_stats[i].cck_lp_cnt);		\
	पूर्ण जबतक (0)

#घोषणा PRINT_OFDM_RATE(str, i)					\
	करो अणु							\
		len += scnम_लिखो(buf + len, size - len,		\
			 "%11s : %10u\n",			\
			 str,					\
			 rstats->ofdm_stats[i].ofdm_cnt);	\
	पूर्ण जबतक (0)

अटल sमाप_प्रकार पढ़ो_file_node_recv(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_node *an = file->निजी_data;
	काष्ठा ath_softc *sc = an->sc;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_rx_rate_stats *rstats;
	काष्ठा ieee80211_sta *sta = an->sta;
	क्रमागत nl80211_band band;
	u32 len = 0, size = 4096;
	अक्षर *buf;
	माप_प्रकार retval;
	पूर्णांक i;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	band = ah->curchan->chan->band;
	rstats = &an->rx_rate_stats;

	अगर (!sta->ht_cap.ht_supported)
		जाओ legacy;

	len += scnम_लिखो(buf + len, size - len,
			 "%24s%10s%10s%10s\n",
			 "HT20", "HT40", "SGI", "LGI");

	क्रम (i = 0; i < 24; i++) अणु
		len += scnम_लिखो(buf + len, size - len,
				 "%8s%3u : %10u%10u%10u%10u\n",
				 "MCS", i,
				 rstats->ht_stats[i].ht20_cnt,
				 rstats->ht_stats[i].ht40_cnt,
				 rstats->ht_stats[i].sgi_cnt,
				 rstats->ht_stats[i].lgi_cnt);
	पूर्ण

	len += scnम_लिखो(buf + len, size - len, "\n");

legacy:
	अगर (band == NL80211_BAND_2GHZ) अणु
		PRINT_CCK_RATE("CCK-1M/LP", 0, false);
		PRINT_CCK_RATE("CCK-2M/LP", 1, false);
		PRINT_CCK_RATE("CCK-5.5M/LP", 2, false);
		PRINT_CCK_RATE("CCK-11M/LP", 3, false);

		PRINT_CCK_RATE("CCK-2M/SP", 1, true);
		PRINT_CCK_RATE("CCK-5.5M/SP", 2, true);
		PRINT_CCK_RATE("CCK-11M/SP", 3, true);
	पूर्ण

	PRINT_OFDM_RATE("OFDM-6M", 0);
	PRINT_OFDM_RATE("OFDM-9M", 1);
	PRINT_OFDM_RATE("OFDM-12M", 2);
	PRINT_OFDM_RATE("OFDM-18M", 3);
	PRINT_OFDM_RATE("OFDM-24M", 4);
	PRINT_OFDM_RATE("OFDM-36M", 5);
	PRINT_OFDM_RATE("OFDM-48M", 6);
	PRINT_OFDM_RATE("OFDM-54M", 7);

	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;
पूर्ण

#अघोषित PRINT_OFDM_RATE
#अघोषित PRINT_CCK_RATE

अटल स्थिर काष्ठा file_operations fops_node_recv = अणु
	.पढ़ो = पढ़ो_file_node_recv,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

व्योम ath9k_sta_add_debugfs(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta,
			   काष्ठा dentry *dir)
अणु
	काष्ठा ath_node *an = (काष्ठा ath_node *)sta->drv_priv;

	debugfs_create_file("node_aggr", 0444, dir, an, &fops_node_aggr);
	debugfs_create_file("node_recv", 0444, dir, an, &fops_node_recv);
पूर्ण
