<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2005 - 2011 Intel Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/mac80211.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>

#समावेश <linux/workqueue.h>

#समावेश "commands.h"
#समावेश "3945.h"

#घोषणा RS_NAME "iwl-3945-rs"

अटल s32 il3945_expected_tpt_g[RATE_COUNT_3945] = अणु
	7, 13, 35, 58, 0, 0, 76, 104, 130, 168, 191, 202
पूर्ण;

अटल s32 il3945_expected_tpt_g_prot[RATE_COUNT_3945] = अणु
	7, 13, 35, 58, 0, 0, 0, 80, 93, 113, 123, 125
पूर्ण;

अटल s32 il3945_expected_tpt_a[RATE_COUNT_3945] = अणु
	0, 0, 0, 0, 40, 57, 72, 98, 121, 154, 177, 186
पूर्ण;

अटल s32 il3945_expected_tpt_b[RATE_COUNT_3945] = अणु
	7, 13, 35, 58, 0, 0, 0, 0, 0, 0, 0, 0
पूर्ण;

काष्ठा il3945_tpt_entry अणु
	s8 min_rssi;
	u8 idx;
पूर्ण;

अटल काष्ठा il3945_tpt_entry il3945_tpt_table_a[] = अणु
	अणु-60, RATE_54M_IDXपूर्ण,
	अणु-64, RATE_48M_IDXपूर्ण,
	अणु-72, RATE_36M_IDXपूर्ण,
	अणु-80, RATE_24M_IDXपूर्ण,
	अणु-84, RATE_18M_IDXपूर्ण,
	अणु-85, RATE_12M_IDXपूर्ण,
	अणु-87, RATE_9M_IDXपूर्ण,
	अणु-89, RATE_6M_IDXपूर्ण
पूर्ण;

अटल काष्ठा il3945_tpt_entry il3945_tpt_table_g[] = अणु
	अणु-60, RATE_54M_IDXपूर्ण,
	अणु-64, RATE_48M_IDXपूर्ण,
	अणु-68, RATE_36M_IDXपूर्ण,
	अणु-80, RATE_24M_IDXपूर्ण,
	अणु-84, RATE_18M_IDXपूर्ण,
	अणु-85, RATE_12M_IDXपूर्ण,
	अणु-86, RATE_11M_IDXपूर्ण,
	अणु-88, RATE_5M_IDXपूर्ण,
	अणु-90, RATE_2M_IDXपूर्ण,
	अणु-92, RATE_1M_IDXपूर्ण
पूर्ण;

#घोषणा RATE_MAX_WINDOW		62
#घोषणा RATE_FLUSH		(3*HZ)
#घोषणा RATE_WIN_FLUSH		(HZ/2)
#घोषणा IL39_RATE_HIGH_TH	11520
#घोषणा IL_SUCCESS_UP_TH	8960
#घोषणा IL_SUCCESS_DOWN_TH	10880
#घोषणा RATE_MIN_FAILURE_TH	6
#घोषणा RATE_MIN_SUCCESS_TH	8
#घोषणा RATE_DECREASE_TH	1920
#घोषणा RATE_RETRY_TH		15

अटल u8
il3945_get_rate_idx_by_rssi(s32 rssi, क्रमागत nl80211_band band)
अणु
	u32 idx = 0;
	u32 table_size = 0;
	काष्ठा il3945_tpt_entry *tpt_table = शून्य;

	अगर (rssi < IL_MIN_RSSI_VAL || rssi > IL_MAX_RSSI_VAL)
		rssi = IL_MIN_RSSI_VAL;

	चयन (band) अणु
	हाल NL80211_BAND_2GHZ:
		tpt_table = il3945_tpt_table_g;
		table_size = ARRAY_SIZE(il3945_tpt_table_g);
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		tpt_table = il3945_tpt_table_a;
		table_size = ARRAY_SIZE(il3945_tpt_table_a);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	जबतक (idx < table_size && rssi < tpt_table[idx].min_rssi)
		idx++;

	idx = min(idx, table_size - 1);

	वापस tpt_table[idx].idx;
पूर्ण

अटल व्योम
il3945_clear_win(काष्ठा il3945_rate_scale_data *win)
अणु
	win->data = 0;
	win->success_counter = 0;
	win->success_ratio = -1;
	win->counter = 0;
	win->average_tpt = IL_INVALID_VALUE;
	win->stamp = 0;
पूर्ण

/*
 * il3945_rate_scale_flush_wins - flush out the rate scale wins
 *
 * Returns the number of wins that have gathered data but were
 * not flushed.  If there were any that were not flushed, then
 * reschedule the rate flushing routine.
 */
अटल पूर्णांक
il3945_rate_scale_flush_wins(काष्ठा il3945_rs_sta *rs_sta)
अणु
	पूर्णांक unflushed = 0;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा il_priv *il __maybe_unused = rs_sta->il;

	/*
	 * For each rate, अगर we have collected data on that rate
	 * and it has been more than RATE_WIN_FLUSH
	 * since we flushed, clear out the gathered stats
	 */
	क्रम (i = 0; i < RATE_COUNT_3945; i++) अणु
		अगर (!rs_sta->win[i].counter)
			जारी;

		spin_lock_irqsave(&rs_sta->lock, flags);
		अगर (समय_after(jअगरfies, rs_sta->win[i].stamp + RATE_WIN_FLUSH)) अणु
			D_RATE("flushing %d samples of rate " "idx %d\n",
			       rs_sta->win[i].counter, i);
			il3945_clear_win(&rs_sta->win[i]);
		पूर्ण अन्यथा
			unflushed++;
		spin_unlock_irqrestore(&rs_sta->lock, flags);
	पूर्ण

	वापस unflushed;
पूर्ण

#घोषणा RATE_FLUSH_MAX              5000	/* msec */
#घोषणा RATE_FLUSH_MIN              50	/* msec */
#घोषणा IL_AVERAGE_PACKETS             1500

अटल व्योम
il3945_bg_rate_scale_flush(काष्ठा समयr_list *t)
अणु
	काष्ठा il3945_rs_sta *rs_sta = from_समयr(rs_sta, t, rate_scale_flush);
	काष्ठा il_priv *il __maybe_unused = rs_sta->il;
	पूर्णांक unflushed = 0;
	अचिन्हित दीर्घ flags;
	u32 packet_count, duration, pps;

	D_RATE("enter\n");

	unflushed = il3945_rate_scale_flush_wins(rs_sta);

	spin_lock_irqsave(&rs_sta->lock, flags);

	/* Number of packets Rx'd since last समय this समयr ran */
	packet_count = (rs_sta->tx_packets - rs_sta->last_tx_packets) + 1;

	rs_sta->last_tx_packets = rs_sta->tx_packets + 1;

	अगर (unflushed) अणु
		duration =
		    jअगरfies_to_msecs(jअगरfies - rs_sta->last_partial_flush);

		D_RATE("Tx'd %d packets in %dms\n", packet_count, duration);

		/* Determine packets per second */
		अगर (duration)
			pps = (packet_count * 1000) / duration;
		अन्यथा
			pps = 0;

		अगर (pps) अणु
			duration = (IL_AVERAGE_PACKETS * 1000) / pps;
			अगर (duration < RATE_FLUSH_MIN)
				duration = RATE_FLUSH_MIN;
			अन्यथा अगर (duration > RATE_FLUSH_MAX)
				duration = RATE_FLUSH_MAX;
		पूर्ण अन्यथा
			duration = RATE_FLUSH_MAX;

		rs_sta->flush_समय = msecs_to_jअगरfies(duration);

		D_RATE("new flush period: %d msec ave %d\n", duration,
		       packet_count);

		mod_समयr(&rs_sta->rate_scale_flush,
			  jअगरfies + rs_sta->flush_समय);

		rs_sta->last_partial_flush = jअगरfies;
	पूर्ण अन्यथा अणु
		rs_sta->flush_समय = RATE_FLUSH;
		rs_sta->flush_pending = 0;
	पूर्ण
	/* If there weren't any unflushed entries, we don't schedule the समयr
	 * to run again */

	rs_sta->last_flush = jअगरfies;

	spin_unlock_irqrestore(&rs_sta->lock, flags);

	D_RATE("leave\n");
पूर्ण

/*
 * il3945_collect_tx_data - Update the success/failure sliding win
 *
 * We keep a sliding win of the last 64 packets transmitted
 * at this rate.  win->data contains the biपंचांगask of successful
 * packets.
 */
अटल व्योम
il3945_collect_tx_data(काष्ठा il3945_rs_sta *rs_sta,
		       काष्ठा il3945_rate_scale_data *win, पूर्णांक success,
		       पूर्णांक retries, पूर्णांक idx)
अणु
	अचिन्हित दीर्घ flags;
	s32 fail_count;
	काष्ठा il_priv *il __maybe_unused = rs_sta->il;

	अगर (!retries) अणु
		D_RATE("leave: retries == 0 -- should be at least 1\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&rs_sta->lock, flags);

	/*
	 * Keep track of only the latest 62 tx frame attempts in this rate's
	 * history win; anything older isn't really relevant any more.
	 * If we have filled up the sliding win, drop the oldest attempt;
	 * अगर the oldest attempt (highest bit in biपंचांगap) shows "success",
	 * subtract "1" from the success counter (this is the मुख्य reason
	 * we keep these biपंचांगaps!).
	 * */
	जबतक (retries > 0) अणु
		अगर (win->counter >= RATE_MAX_WINDOW) अणु

			/* हटाओ earliest */
			win->counter = RATE_MAX_WINDOW - 1;

			अगर (win->data & (1ULL << (RATE_MAX_WINDOW - 1))) अणु
				win->data &= ~(1ULL << (RATE_MAX_WINDOW - 1));
				win->success_counter--;
			पूर्ण
		पूर्ण

		/* Increment frames-attempted counter */
		win->counter++;

		/* Shअगरt biपंचांगap by one frame (throw away oldest history),
		 * OR in "1", and increment "success" अगर this
		 * frame was successful. */
		win->data <<= 1;
		अगर (success > 0) अणु
			win->success_counter++;
			win->data |= 0x1;
			success--;
		पूर्ण

		retries--;
	पूर्ण

	/* Calculate current success ratio, aव्योम भागide-by-0! */
	अगर (win->counter > 0)
		win->success_ratio =
		    128 * (100 * win->success_counter) / win->counter;
	अन्यथा
		win->success_ratio = IL_INVALID_VALUE;

	fail_count = win->counter - win->success_counter;

	/* Calculate average throughput, अगर we have enough history. */
	अगर (fail_count >= RATE_MIN_FAILURE_TH ||
	    win->success_counter >= RATE_MIN_SUCCESS_TH)
		win->average_tpt =
		    ((win->success_ratio * rs_sta->expected_tpt[idx] +
		      64) / 128);
	अन्यथा
		win->average_tpt = IL_INVALID_VALUE;

	/* Tag this win as having been updated */
	win->stamp = jअगरfies;

	spin_unlock_irqrestore(&rs_sta->lock, flags);
पूर्ण

/*
 * Called after adding a new station to initialize rate scaling
 */
व्योम
il3945_rs_rate_init(काष्ठा il_priv *il, काष्ठा ieee80211_sta *sta, u8 sta_id)
अणु
	काष्ठा ieee80211_hw *hw = il->hw;
	काष्ठा ieee80211_conf *conf = &il->hw->conf;
	काष्ठा il3945_sta_priv *psta;
	काष्ठा il3945_rs_sta *rs_sta;
	काष्ठा ieee80211_supported_band *sband;
	पूर्णांक i;

	D_INFO("enter\n");
	अगर (sta_id == il->hw_params.bcast_id)
		जाओ out;

	psta = (काष्ठा il3945_sta_priv *)sta->drv_priv;
	rs_sta = &psta->rs_sta;
	sband = hw->wiphy->bands[conf->chandef.chan->band];

	rs_sta->il = il;

	rs_sta->start_rate = RATE_INVALID;

	/* शेष to just 802.11b */
	rs_sta->expected_tpt = il3945_expected_tpt_b;

	rs_sta->last_partial_flush = jअगरfies;
	rs_sta->last_flush = jअगरfies;
	rs_sta->flush_समय = RATE_FLUSH;
	rs_sta->last_tx_packets = 0;

	क्रम (i = 0; i < RATE_COUNT_3945; i++)
		il3945_clear_win(&rs_sta->win[i]);

	/* TODO: what is a good starting rate क्रम STA? About middle? Maybe not
	 * the lowest or the highest rate.. Could consider using RSSI from
	 * previous packets? Need to have IEEE 802.1X auth succeed immediately
	 * after assoc.. */

	क्रम (i = sband->n_bitrates - 1; i >= 0; i--) अणु
		अगर (sta->supp_rates[sband->band] & (1 << i)) अणु
			rs_sta->last_txrate_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	il->_3945.sta_supp_rates = sta->supp_rates[sband->band];
	/* For 5 GHz band it start at IL_FIRST_OFDM_RATE */
	अगर (sband->band == NL80211_BAND_5GHZ) अणु
		rs_sta->last_txrate_idx += IL_FIRST_OFDM_RATE;
		il->_3945.sta_supp_rates <<= IL_FIRST_OFDM_RATE;
	पूर्ण

out:
	il->stations[sta_id].used &= ~IL_STA_UCODE_INPROGRESS;

	D_INFO("leave\n");
पूर्ण

अटल व्योम *
il3945_rs_alloc(काष्ठा ieee80211_hw *hw)
अणु
	वापस hw->priv;
पूर्ण

/* rate scale requires मुक्त function to be implemented */
अटल व्योम
il3945_rs_मुक्त(व्योम *il)
अणु
पूर्ण

अटल व्योम *
il3945_rs_alloc_sta(व्योम *il_priv, काष्ठा ieee80211_sta *sta, gfp_t gfp)
अणु
	काष्ठा il3945_rs_sta *rs_sta;
	काष्ठा il3945_sta_priv *psta = (व्योम *)sta->drv_priv;
	काष्ठा il_priv *il __maybe_unused = il_priv;

	D_RATE("enter\n");

	rs_sta = &psta->rs_sta;

	spin_lock_init(&rs_sta->lock);
	समयr_setup(&rs_sta->rate_scale_flush, il3945_bg_rate_scale_flush, 0);
	D_RATE("leave\n");

	वापस rs_sta;
पूर्ण

अटल व्योम
il3945_rs_मुक्त_sta(व्योम *il_priv, काष्ठा ieee80211_sta *sta, व्योम *il_sta)
अणु
	काष्ठा il3945_rs_sta *rs_sta = il_sta;

	/*
	 * Be careful not to use any members of il3945_rs_sta (like trying
	 * to use il_priv to prपूर्णांक out debugging) since it may not be fully
	 * initialized at this poपूर्णांक.
	 */
	del_समयr_sync(&rs_sta->rate_scale_flush);
पूर्ण

/*
 * il3945_rs_tx_status - Update rate control values based on Tx results
 *
 * NOTE: Uses il_priv->retry_rate क्रम the # of retries attempted by
 * the hardware क्रम each rate.
 */
अटल व्योम
il3945_rs_tx_status(व्योम *il_rate, काष्ठा ieee80211_supported_band *sband,
		    काष्ठा ieee80211_sta *sta, व्योम *il_sta,
		    काष्ठा sk_buff *skb)
अणु
	s8 retries = 0, current_count;
	पूर्णांक scale_rate_idx, first_idx, last_idx;
	अचिन्हित दीर्घ flags;
	काष्ठा il_priv *il = (काष्ठा il_priv *)il_rate;
	काष्ठा il3945_rs_sta *rs_sta = il_sta;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	D_RATE("enter\n");

	retries = info->status.rates[0].count;
	/* Sanity Check क्रम retries */
	अगर (retries > RATE_RETRY_TH)
		retries = RATE_RETRY_TH;

	first_idx = sband->bitrates[info->status.rates[0].idx].hw_value;
	अगर (first_idx < 0 || first_idx >= RATE_COUNT_3945) अणु
		D_RATE("leave: Rate out of bounds: %d\n", first_idx);
		वापस;
	पूर्ण

	अगर (!il_sta) अणु
		D_RATE("leave: No STA il data to update!\n");
		वापस;
	पूर्ण

	/* Treat uninitialized rate scaling data same as non-existing. */
	अगर (!rs_sta->il) अणु
		D_RATE("leave: STA il data uninitialized!\n");
		वापस;
	पूर्ण

	rs_sta->tx_packets++;

	scale_rate_idx = first_idx;
	last_idx = first_idx;

	/*
	 * Update the win क्रम each rate.  We determine which rates
	 * were Tx'd based on the total number of retries vs. the number
	 * of retries configured क्रम each rate -- currently set to the
	 * il value 'retry_rate' vs. rate specअगरic
	 *
	 * On निकास from this जबतक loop last_idx indicates the rate
	 * at which the frame was finally transmitted (or failed अगर no
	 * ACK)
	 */
	जबतक (retries > 1) अणु
		अगर ((retries - 1) < il->retry_rate) अणु
			current_count = (retries - 1);
			last_idx = scale_rate_idx;
		पूर्ण अन्यथा अणु
			current_count = il->retry_rate;
			last_idx = il3945_rs_next_rate(il, scale_rate_idx);
		पूर्ण

		/* Update this rate accounting क्रम as many retries
		 * as was used क्रम it (per current_count) */
		il3945_collect_tx_data(rs_sta, &rs_sta->win[scale_rate_idx], 0,
				       current_count, scale_rate_idx);
		D_RATE("Update rate %d for %d retries.\n", scale_rate_idx,
		       current_count);

		retries -= current_count;

		scale_rate_idx = last_idx;
	पूर्ण

	/* Update the last idx win with success/failure based on ACK */
	D_RATE("Update rate %d with %s.\n", last_idx,
	       (info->flags & IEEE80211_TX_STAT_ACK) ? "success" : "failure");
	il3945_collect_tx_data(rs_sta, &rs_sta->win[last_idx],
			       info->flags & IEEE80211_TX_STAT_ACK, 1,
			       last_idx);

	/* We updated the rate scale win -- अगर its been more than
	 * flush_समय since the last run, schedule the flush
	 * again */
	spin_lock_irqsave(&rs_sta->lock, flags);

	अगर (!rs_sta->flush_pending &&
	    समय_after(jअगरfies, rs_sta->last_flush + rs_sta->flush_समय)) अणु

		rs_sta->last_partial_flush = jअगरfies;
		rs_sta->flush_pending = 1;
		mod_समयr(&rs_sta->rate_scale_flush,
			  jअगरfies + rs_sta->flush_समय);
	पूर्ण

	spin_unlock_irqrestore(&rs_sta->lock, flags);

	D_RATE("leave\n");
पूर्ण

अटल u16
il3945_get_adjacent_rate(काष्ठा il3945_rs_sta *rs_sta, u8 idx, u16 rate_mask,
			 क्रमागत nl80211_band band)
अणु
	u8 high = RATE_INVALID;
	u8 low = RATE_INVALID;
	काष्ठा il_priv *il __maybe_unused = rs_sta->il;

	/* 802.11A walks to the next literal adjacent rate in
	 * the rate table */
	अगर (unlikely(band == NL80211_BAND_5GHZ)) अणु
		पूर्णांक i;
		u32 mask;

		/* Find the previous rate that is in the rate mask */
		i = idx - 1;
		क्रम (mask = (1 << i); i >= 0; i--, mask >>= 1) अणु
			अगर (rate_mask & mask) अणु
				low = i;
				अवरोध;
			पूर्ण
		पूर्ण

		/* Find the next rate that is in the rate mask */
		i = idx + 1;
		क्रम (mask = (1 << i); i < RATE_COUNT_3945; i++, mask <<= 1) अणु
			अगर (rate_mask & mask) अणु
				high = i;
				अवरोध;
			पूर्ण
		पूर्ण

		वापस (high << 8) | low;
	पूर्ण

	low = idx;
	जबतक (low != RATE_INVALID) अणु
		अगर (rs_sta->tgg)
			low = il3945_rates[low].prev_rs_tgg;
		अन्यथा
			low = il3945_rates[low].prev_rs;
		अगर (low == RATE_INVALID)
			अवरोध;
		अगर (rate_mask & (1 << low))
			अवरोध;
		D_RATE("Skipping masked lower rate: %d\n", low);
	पूर्ण

	high = idx;
	जबतक (high != RATE_INVALID) अणु
		अगर (rs_sta->tgg)
			high = il3945_rates[high].next_rs_tgg;
		अन्यथा
			high = il3945_rates[high].next_rs;
		अगर (high == RATE_INVALID)
			अवरोध;
		अगर (rate_mask & (1 << high))
			अवरोध;
		D_RATE("Skipping masked higher rate: %d\n", high);
	पूर्ण

	वापस (high << 8) | low;
पूर्ण

/*
 * il3945_rs_get_rate - find the rate क्रम the requested packet
 *
 * Returns the ieee80211_rate काष्ठाure allocated by the driver.
 *
 * The rate control algorithm has no पूर्णांकernal mapping between hw_mode's
 * rate ordering and the rate ordering used by the rate control algorithm.
 *
 * The rate control algorithm uses a single table of rates that goes across
 * the entire A/B/G spectrum vs. being limited to just one particular
 * hw_mode.
 *
 * As such, we can't convert the idx obtained below into the hw_mode's
 * rate table and must reference the driver allocated rate table
 *
 */
अटल व्योम
il3945_rs_get_rate(व्योम *il_r, काष्ठा ieee80211_sta *sta, व्योम *il_sta,
		   काष्ठा ieee80211_tx_rate_control *txrc)
अणु
	काष्ठा ieee80211_supported_band *sband = txrc->sband;
	काष्ठा sk_buff *skb = txrc->skb;
	u8 low = RATE_INVALID;
	u8 high = RATE_INVALID;
	u16 high_low;
	पूर्णांक idx;
	काष्ठा il3945_rs_sta *rs_sta = il_sta;
	काष्ठा il3945_rate_scale_data *win = शून्य;
	पूर्णांक current_tpt = IL_INVALID_VALUE;
	पूर्णांक low_tpt = IL_INVALID_VALUE;
	पूर्णांक high_tpt = IL_INVALID_VALUE;
	u32 fail_count;
	s8 scale_action = 0;
	अचिन्हित दीर्घ flags;
	u16 rate_mask;
	s8 max_rate_idx = -1;
	काष्ठा il_priv *il __maybe_unused = (काष्ठा il_priv *)il_r;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	D_RATE("enter\n");

	/* Treat uninitialized rate scaling data same as non-existing. */
	अगर (rs_sta && !rs_sta->il) अणु
		D_RATE("Rate scaling information not initialized yet.\n");
		il_sta = शून्य;
	पूर्ण

	rate_mask = sta->supp_rates[sband->band];

	/* get user max rate अगर set */
	max_rate_idx = fls(txrc->rate_idx_mask) - 1;
	अगर (sband->band == NL80211_BAND_5GHZ && max_rate_idx != -1)
		max_rate_idx += IL_FIRST_OFDM_RATE;
	अगर (max_rate_idx < 0 || max_rate_idx >= RATE_COUNT)
		max_rate_idx = -1;

	idx = min(rs_sta->last_txrate_idx & 0xffff, RATE_COUNT_3945 - 1);

	अगर (sband->band == NL80211_BAND_5GHZ)
		rate_mask = rate_mask << IL_FIRST_OFDM_RATE;

	spin_lock_irqsave(&rs_sta->lock, flags);

	/* क्रम recent assoc, choose best rate regarding
	 * to rssi value
	 */
	अगर (rs_sta->start_rate != RATE_INVALID) अणु
		अगर (rs_sta->start_rate < idx &&
		    (rate_mask & (1 << rs_sta->start_rate)))
			idx = rs_sta->start_rate;
		rs_sta->start_rate = RATE_INVALID;
	पूर्ण

	/* क्रमce user max rate अगर set by user */
	अगर (max_rate_idx != -1 && max_rate_idx < idx) अणु
		अगर (rate_mask & (1 << max_rate_idx))
			idx = max_rate_idx;
	पूर्ण

	win = &(rs_sta->win[idx]);

	fail_count = win->counter - win->success_counter;

	अगर (fail_count < RATE_MIN_FAILURE_TH &&
	    win->success_counter < RATE_MIN_SUCCESS_TH) अणु
		spin_unlock_irqrestore(&rs_sta->lock, flags);

		D_RATE("Invalid average_tpt on rate %d: "
		       "counter: %d, success_counter: %d, "
		       "expected_tpt is %sNULL\n", idx, win->counter,
		       win->success_counter,
		       rs_sta->expected_tpt ? "not " : "");

		/* Can't calculate this yet; not enough history */
		win->average_tpt = IL_INVALID_VALUE;
		जाओ out;

	पूर्ण

	current_tpt = win->average_tpt;

	high_low =
	    il3945_get_adjacent_rate(rs_sta, idx, rate_mask, sband->band);
	low = high_low & 0xff;
	high = (high_low >> 8) & 0xff;

	/* If user set max rate, करोnt allow higher than user स्थिरrain */
	अगर (max_rate_idx != -1 && max_rate_idx < high)
		high = RATE_INVALID;

	/* Collect Measured throughमाला_दो of adjacent rates */
	अगर (low != RATE_INVALID)
		low_tpt = rs_sta->win[low].average_tpt;

	अगर (high != RATE_INVALID)
		high_tpt = rs_sta->win[high].average_tpt;

	spin_unlock_irqrestore(&rs_sta->lock, flags);

	scale_action = 0;

	/* Low success ratio , need to drop the rate */
	अगर (win->success_ratio < RATE_DECREASE_TH || !current_tpt) अणु
		D_RATE("decrease rate because of low success_ratio\n");
		scale_action = -1;
		/* No throughput measured yet क्रम adjacent rates,
		 * try increase */
	पूर्ण अन्यथा अगर (low_tpt == IL_INVALID_VALUE && high_tpt == IL_INVALID_VALUE) अणु

		अगर (high != RATE_INVALID &&
		    win->success_ratio >= RATE_INCREASE_TH)
			scale_action = 1;
		अन्यथा अगर (low != RATE_INVALID)
			scale_action = 0;

		/* Both adjacent throughमाला_दो are measured, but neither one has
		 * better throughput; we're using the best rate, don't change
		 * it! */
	पूर्ण अन्यथा अगर (low_tpt != IL_INVALID_VALUE && high_tpt != IL_INVALID_VALUE
		   && low_tpt < current_tpt && high_tpt < current_tpt) अणु

		D_RATE("No action -- low [%d] & high [%d] < "
		       "current_tpt [%d]\n", low_tpt, high_tpt, current_tpt);
		scale_action = 0;

		/* At least one of the rates has better throughput */
	पूर्ण अन्यथा अणु
		अगर (high_tpt != IL_INVALID_VALUE) अणु

			/* High rate has better throughput, Increase
			 * rate */
			अगर (high_tpt > current_tpt &&
			    win->success_ratio >= RATE_INCREASE_TH)
				scale_action = 1;
			अन्यथा अणु
				D_RATE("decrease rate because of high tpt\n");
				scale_action = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (low_tpt != IL_INVALID_VALUE) अणु
			अगर (low_tpt > current_tpt) अणु
				D_RATE("decrease rate because of low tpt\n");
				scale_action = -1;
			पूर्ण अन्यथा अगर (win->success_ratio >= RATE_INCREASE_TH) अणु
				/* Lower rate has better
				 * throughput,decrease rate */
				scale_action = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Sanity check; asked क्रम decrease, but success rate or throughput
	 * has been good at old rate.  Don't change it. */
	अगर (scale_action == -1 && low != RATE_INVALID &&
	    (win->success_ratio > RATE_HIGH_TH ||
	     current_tpt > 100 * rs_sta->expected_tpt[low]))
		scale_action = 0;

	चयन (scale_action) अणु
	हाल -1:
		/* Decrease rate */
		अगर (low != RATE_INVALID)
			idx = low;
		अवरोध;
	हाल 1:
		/* Increase rate */
		अगर (high != RATE_INVALID)
			idx = high;

		अवरोध;
	हाल 0:
	शेष:
		/* No change */
		अवरोध;
	पूर्ण

	D_RATE("Selected %d (action %d) - low %d high %d\n", idx, scale_action,
	       low, high);

out:

	अगर (sband->band == NL80211_BAND_5GHZ) अणु
		अगर (WARN_ON_ONCE(idx < IL_FIRST_OFDM_RATE))
			idx = IL_FIRST_OFDM_RATE;
		rs_sta->last_txrate_idx = idx;
		info->control.rates[0].idx = idx - IL_FIRST_OFDM_RATE;
	पूर्ण अन्यथा अणु
		rs_sta->last_txrate_idx = idx;
		info->control.rates[0].idx = rs_sta->last_txrate_idx;
	पूर्ण
	info->control.rates[0].count = 1;

	D_RATE("leave: %d\n", idx);
पूर्ण

#अगर_घोषित CONFIG_MAC80211_DEBUGFS

अटल sमाप_प्रकार
il3945_sta_dbgfs_stats_table_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *buff;
	पूर्णांक desc = 0;
	पूर्णांक j;
	sमाप_प्रकार ret;
	काष्ठा il3945_rs_sta *lq_sta = file->निजी_data;

	buff = kदो_स्मृति(1024, GFP_KERNEL);
	अगर (!buff)
		वापस -ENOMEM;

	desc +=
	    प्र_लिखो(buff + desc,
		    "tx packets=%d last rate idx=%d\n"
		    "rate=0x%X flush time %d\n", lq_sta->tx_packets,
		    lq_sta->last_txrate_idx, lq_sta->start_rate,
		    jअगरfies_to_msecs(lq_sta->flush_समय));
	क्रम (j = 0; j < RATE_COUNT_3945; j++) अणु
		desc +=
		    प्र_लिखो(buff + desc, "counter=%d success=%d %%=%d\n",
			    lq_sta->win[j].counter,
			    lq_sta->win[j].success_counter,
			    lq_sta->win[j].success_ratio);
	पूर्ण
	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buff, desc);
	kमुक्त(buff);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations rs_sta_dbgfs_stats_table_ops = अणु
	.पढ़ो = il3945_sta_dbgfs_stats_table_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल व्योम
il3945_add_debugfs(व्योम *il, व्योम *il_sta, काष्ठा dentry *dir)
अणु
	काष्ठा il3945_rs_sta *lq_sta = il_sta;

	debugfs_create_file("rate_stats_table", 0600, dir, lq_sta,
			    &rs_sta_dbgfs_stats_table_ops);
पूर्ण
#पूर्ण_अगर

/*
 * Initialization of rate scaling inक्रमmation is करोne by driver after
 * the station is added. Since mac80211 calls this function beक्रमe a
 * station is added we ignore it.
 */
अटल व्योम
il3945_rs_rate_init_stub(व्योम *il_r, काष्ठा ieee80211_supported_band *sband,
			 काष्ठा cfg80211_chan_def *chandef,
			 काष्ठा ieee80211_sta *sta, व्योम *il_sta)
अणु
पूर्ण

अटल स्थिर काष्ठा rate_control_ops rs_ops = अणु
	.name = RS_NAME,
	.tx_status = il3945_rs_tx_status,
	.get_rate = il3945_rs_get_rate,
	.rate_init = il3945_rs_rate_init_stub,
	.alloc = il3945_rs_alloc,
	.मुक्त = il3945_rs_मुक्त,
	.alloc_sta = il3945_rs_alloc_sta,
	.मुक्त_sta = il3945_rs_मुक्त_sta,
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	.add_sta_debugfs = il3945_add_debugfs,
#पूर्ण_अगर

पूर्ण;

व्योम
il3945_rate_scale_init(काष्ठा ieee80211_hw *hw, s32 sta_id)
अणु
	काष्ठा il_priv *il = hw->priv;
	s32 rssi = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा il3945_rs_sta *rs_sta;
	काष्ठा ieee80211_sta *sta;
	काष्ठा il3945_sta_priv *psta;

	D_RATE("enter\n");

	rcu_पढ़ो_lock();

	sta = ieee80211_find_sta(il->vअगर, il->stations[sta_id].sta.sta.addr);
	अगर (!sta) अणु
		D_RATE("Unable to find station to initialize rate scaling.\n");
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	psta = (व्योम *)sta->drv_priv;
	rs_sta = &psta->rs_sta;

	spin_lock_irqsave(&rs_sta->lock, flags);

	rs_sta->tgg = 0;
	चयन (il->band) अणु
	हाल NL80211_BAND_2GHZ:
		/* TODO: this always करोes G, not a regression */
		अगर (il->active.flags & RXON_FLG_TGG_PROTECT_MSK) अणु
			rs_sta->tgg = 1;
			rs_sta->expected_tpt = il3945_expected_tpt_g_prot;
		पूर्ण अन्यथा
			rs_sta->expected_tpt = il3945_expected_tpt_g;
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		rs_sta->expected_tpt = il3945_expected_tpt_a;
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&rs_sta->lock, flags);

	rssi = il->_3945.last_rx_rssi;
	अगर (rssi == 0)
		rssi = IL_MIN_RSSI_VAL;

	D_RATE("Network RSSI: %d\n", rssi);

	rs_sta->start_rate = il3945_get_rate_idx_by_rssi(rssi, il->band);

	D_RATE("leave: rssi %d assign rate idx: " "%d (plcp 0x%x)\n", rssi,
	       rs_sta->start_rate, il3945_rates[rs_sta->start_rate].plcp);
	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक
il3945_rate_control_रेजिस्टर(व्योम)
अणु
	वापस ieee80211_rate_control_रेजिस्टर(&rs_ops);
पूर्ण

व्योम
il3945_rate_control_unरेजिस्टर(व्योम)
अणु
	ieee80211_rate_control_unरेजिस्टर(&rs_ops);
पूर्ण
