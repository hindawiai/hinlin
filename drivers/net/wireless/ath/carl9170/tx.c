<शैली गुरु>
/*
 * Atheros CARL9170 driver
 *
 * 802.11 xmit & status routines
 *
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2009, 2010, Christian Lamparter <chunkeey@googlemail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; see the file COPYING.  If not, see
 * http://www.gnu.org/licenses/.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *    Copyright (c) 2007-2008 Atheros Communications, Inc.
 *
 *    Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/mac80211.h>
#समावेश "carl9170.h"
#समावेश "hw.h"
#समावेश "cmd.h"

अटल अंतरभूत अचिन्हित पूर्णांक __carl9170_get_queue(काष्ठा ar9170 *ar,
						अचिन्हित पूर्णांक queue)
अणु
	अगर (unlikely(modparam_noht)) अणु
		वापस queue;
	पूर्ण अन्यथा अणु
		/*
		 * This is just another workaround, until
		 * someone figures out how to get QoS and
		 * AMPDU to play nicely together.
		 */

		वापस 2;		/* AC_BE */
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक carl9170_get_queue(काष्ठा ar9170 *ar,
					      काष्ठा sk_buff *skb)
अणु
	वापस __carl9170_get_queue(ar, skb_get_queue_mapping(skb));
पूर्ण

अटल bool is_mem_full(काष्ठा ar9170 *ar)
अणु
	वापस (DIV_ROUND_UP(IEEE80211_MAX_FRAME_LEN, ar->fw.mem_block_size) >
		atomic_पढ़ो(&ar->mem_मुक्त_blocks));
पूर्ण

अटल व्योम carl9170_tx_accounting(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb)
अणु
	पूर्णांक queue, i;
	bool mem_full;

	atomic_inc(&ar->tx_total_queued);

	queue = skb_get_queue_mapping(skb);
	spin_lock_bh(&ar->tx_stats_lock);

	/*
	 * The driver has to accept the frame, regardless अगर the queue is
	 * full to the brim, or not. We have to करो the queuing पूर्णांकernally,
	 * since mac80211 assumes that a driver which can operate with
	 * aggregated frames करोes not reject frames क्रम this reason.
	 */
	ar->tx_stats[queue].len++;
	ar->tx_stats[queue].count++;

	mem_full = is_mem_full(ar);
	क्रम (i = 0; i < ar->hw->queues; i++) अणु
		अगर (mem_full || ar->tx_stats[i].len >= ar->tx_stats[i].limit) अणु
			ieee80211_stop_queue(ar->hw, i);
			ar->queue_stop_समयout[i] = jअगरfies;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&ar->tx_stats_lock);
पूर्ण

/* needs rcu_पढ़ो_lock */
अटल काष्ठा ieee80211_sta *__carl9170_get_tx_sta(काष्ठा ar9170 *ar,
						   काष्ठा sk_buff *skb)
अणु
	काष्ठा _carl9170_tx_superframe *super = (व्योम *) skb->data;
	काष्ठा ieee80211_hdr *hdr = (व्योम *) super->frame_data;
	काष्ठा ieee80211_vअगर *vअगर;
	अचिन्हित पूर्णांक vअगर_id;

	vअगर_id = (super->s.misc & CARL9170_TX_SUPER_MISC_VIF_ID) >>
		 CARL9170_TX_SUPER_MISC_VIF_ID_S;

	अगर (WARN_ON_ONCE(vअगर_id >= AR9170_MAX_VIRTUAL_MAC))
		वापस शून्य;

	vअगर = rcu_dereference(ar->vअगर_priv[vअगर_id].vअगर);
	अगर (unlikely(!vअगर))
		वापस शून्य;

	/*
	 * Normally we should use wrappers like ieee80211_get_DA to get
	 * the correct peer ieee80211_sta.
	 *
	 * But there is a problem with indirect traffic (broadcasts, or
	 * data which is designated क्रम other stations) in station mode.
	 * The frame will be directed to the AP क्रम distribution and not
	 * to the actual destination.
	 */

	वापस ieee80211_find_sta(vअगर, hdr->addr1);
पूर्ण

अटल व्योम carl9170_tx_ps_unblock(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा carl9170_sta_info *sta_info;

	rcu_पढ़ो_lock();
	sta = __carl9170_get_tx_sta(ar, skb);
	अगर (unlikely(!sta))
		जाओ out_rcu;

	sta_info = (काष्ठा carl9170_sta_info *) sta->drv_priv;
	अगर (atomic_dec_वापस(&sta_info->pending_frames) == 0)
		ieee80211_sta_block_awake(ar->hw, sta, false);

out_rcu:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम carl9170_tx_accounting_मुक्त(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb)
अणु
	पूर्णांक queue;

	queue = skb_get_queue_mapping(skb);

	spin_lock_bh(&ar->tx_stats_lock);

	ar->tx_stats[queue].len--;

	अगर (!is_mem_full(ar)) अणु
		अचिन्हित पूर्णांक i;
		क्रम (i = 0; i < ar->hw->queues; i++) अणु
			अगर (ar->tx_stats[i].len >= CARL9170_NUM_TX_LIMIT_SOFT)
				जारी;

			अगर (ieee80211_queue_stopped(ar->hw, i)) अणु
				अचिन्हित दीर्घ पंचांगp;

				पंचांगp = jअगरfies - ar->queue_stop_समयout[i];
				अगर (पंचांगp > ar->max_queue_stop_समयout[i])
					ar->max_queue_stop_समयout[i] = पंचांगp;
			पूर्ण

			ieee80211_wake_queue(ar->hw, i);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&ar->tx_stats_lock);

	अगर (atomic_dec_and_test(&ar->tx_total_queued))
		complete(&ar->tx_flush);
पूर्ण

अटल पूर्णांक carl9170_alloc_dev_space(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा _carl9170_tx_superframe *super = (व्योम *) skb->data;
	अचिन्हित पूर्णांक chunks;
	पूर्णांक cookie = -1;

	atomic_inc(&ar->mem_allocs);

	chunks = DIV_ROUND_UP(skb->len, ar->fw.mem_block_size);
	अगर (unlikely(atomic_sub_वापस(chunks, &ar->mem_मुक्त_blocks) < 0)) अणु
		atomic_add(chunks, &ar->mem_मुक्त_blocks);
		वापस -ENOSPC;
	पूर्ण

	spin_lock_bh(&ar->mem_lock);
	cookie = biपंचांगap_find_मुक्त_region(ar->mem_biपंचांगap, ar->fw.mem_blocks, 0);
	spin_unlock_bh(&ar->mem_lock);

	अगर (unlikely(cookie < 0)) अणु
		atomic_add(chunks, &ar->mem_मुक्त_blocks);
		वापस -ENOSPC;
	पूर्ण

	super = (व्योम *) skb->data;

	/*
	 * Cookie #0 serves two special purposes:
	 *  1. The firmware might use it generate BlockACK frames
	 *     in responds of an incoming BlockAckReqs.
	 *
	 *  2. Prevent द्विगुन-मुक्त bugs.
	 */
	super->s.cookie = (u8) cookie + 1;
	वापस 0;
पूर्ण

अटल व्योम carl9170_release_dev_space(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा _carl9170_tx_superframe *super = (व्योम *) skb->data;
	पूर्णांक cookie;

	/* make a local copy of the cookie */
	cookie = super->s.cookie;
	/* invalidate cookie */
	super->s.cookie = 0;

	/*
	 * Do a out-of-bounds check on the cookie:
	 *
	 *  * cookie "0" is reserved and won't be asचिन्हित to any
	 *    out-going frame. Internally however, it is used to
	 *    mark no दीर्घer/un-accounted frames and serves as a
	 *    cheap way of preventing frames from being मुक्तd
	 *    twice by _accident_. NB: There is a tiny race...
	 *
	 *  * obviously, cookie number is limited by the amount
	 *    of available memory blocks, so the number can
	 *    never execeed the mem_blocks count.
	 */
	अगर (WARN_ON_ONCE(cookie == 0) ||
	    WARN_ON_ONCE(cookie > ar->fw.mem_blocks))
		वापस;

	atomic_add(DIV_ROUND_UP(skb->len, ar->fw.mem_block_size),
		   &ar->mem_मुक्त_blocks);

	spin_lock_bh(&ar->mem_lock);
	biपंचांगap_release_region(ar->mem_biपंचांगap, cookie - 1, 0);
	spin_unlock_bh(&ar->mem_lock);
पूर्ण

/* Called from any context */
अटल व्योम carl9170_tx_release(काष्ठा kref *ref)
अणु
	काष्ठा ar9170 *ar;
	काष्ठा carl9170_tx_info *arinfo;
	काष्ठा ieee80211_tx_info *txinfo;
	काष्ठा sk_buff *skb;

	arinfo = container_of(ref, काष्ठा carl9170_tx_info, ref);
	txinfo = container_of((व्योम *) arinfo, काष्ठा ieee80211_tx_info,
			      rate_driver_data);
	skb = container_of((व्योम *) txinfo, काष्ठा sk_buff, cb);

	ar = arinfo->ar;
	अगर (WARN_ON_ONCE(!ar))
		वापस;

	BUILD_BUG_ON(
	    दुरत्व(काष्ठा ieee80211_tx_info, status.ack_संकेत) != 20);

	स_रखो(&txinfo->status.ack_संकेत, 0,
	       माप(काष्ठा ieee80211_tx_info) -
	       दुरत्व(काष्ठा ieee80211_tx_info, status.ack_संकेत));

	अगर (atomic_पढ़ो(&ar->tx_total_queued))
		ar->tx_schedule = true;

	अगर (txinfo->flags & IEEE80211_TX_CTL_AMPDU) अणु
		अगर (!atomic_पढ़ो(&ar->tx_ampdu_upload))
			ar->tx_ampdu_schedule = true;

		अगर (txinfo->flags & IEEE80211_TX_STAT_AMPDU) अणु
			काष्ठा _carl9170_tx_superframe *super;

			super = (व्योम *)skb->data;
			txinfo->status.ampdu_len = super->s.rix;
			txinfo->status.ampdu_ack_len = super->s.cnt;
		पूर्ण अन्यथा अगर ((txinfo->flags & IEEE80211_TX_STAT_ACK) &&
			   !(txinfo->flags & IEEE80211_TX_CTL_REQ_TX_STATUS)) अणु
			/*
			 * drop redundant tx_status reports:
			 *
			 * 1. ampdu_ack_len of the final tx_status करोes
			 *    include the feedback of this particular frame.
			 *
			 * 2. tx_status_irqsafe only queues up to 128
			 *    tx feedback reports and discards the rest.
			 *
			 * 3. minstrel_ht is picky, it only accepts
			 *    reports of frames with the TX_STATUS_AMPDU flag.
			 *
			 * 4. mac80211 is not particularly पूर्णांकerested in
			 *    feedback either [CTL_REQ_TX_STATUS not set]
			 */

			ieee80211_मुक्त_txskb(ar->hw, skb);
			वापस;
		पूर्ण अन्यथा अणु
			/*
			 * Either the frame transmission has failed or
			 * mac80211 requested tx status.
			 */
		पूर्ण
	पूर्ण

	skb_pull(skb, माप(काष्ठा _carl9170_tx_superframe));
	ieee80211_tx_status_irqsafe(ar->hw, skb);
पूर्ण

व्योम carl9170_tx_get_skb(काष्ठा sk_buff *skb)
अणु
	काष्ठा carl9170_tx_info *arinfo = (व्योम *)
		(IEEE80211_SKB_CB(skb))->rate_driver_data;
	kref_get(&arinfo->ref);
पूर्ण

पूर्णांक carl9170_tx_put_skb(काष्ठा sk_buff *skb)
अणु
	काष्ठा carl9170_tx_info *arinfo = (व्योम *)
		(IEEE80211_SKB_CB(skb))->rate_driver_data;

	वापस kref_put(&arinfo->ref, carl9170_tx_release);
पूर्ण

/* Caller must hold the tid_info->lock & rcu_पढ़ो_lock */
अटल व्योम carl9170_tx_shअगरt_bm(काष्ठा ar9170 *ar,
	काष्ठा carl9170_sta_tid *tid_info, u16 seq)
अणु
	u16 off;

	off = SEQ_DIFF(seq, tid_info->bsn);

	अगर (WARN_ON_ONCE(off >= CARL9170_BAW_BITS))
		वापस;

	/*
	 * Sanity check. For each MPDU we set the bit in biपंचांगap and
	 * clear it once we received the tx_status.
	 * But अगर the bit is alपढ़ोy cleared then we've been bitten
	 * by a bug.
	 */
	WARN_ON_ONCE(!test_and_clear_bit(off, tid_info->biपंचांगap));

	off = SEQ_DIFF(tid_info->snx, tid_info->bsn);
	अगर (WARN_ON_ONCE(off >= CARL9170_BAW_BITS))
		वापस;

	अगर (!biपंचांगap_empty(tid_info->biपंचांगap, off))
		off = find_first_bit(tid_info->biपंचांगap, off);

	tid_info->bsn += off;
	tid_info->bsn &= 0x0fff;

	biपंचांगap_shअगरt_right(tid_info->biपंचांगap, tid_info->biपंचांगap,
			   off, CARL9170_BAW_BITS);
पूर्ण

अटल व्योम carl9170_tx_status_process_ampdu(काष्ठा ar9170 *ar,
	काष्ठा sk_buff *skb, काष्ठा ieee80211_tx_info *txinfo)
अणु
	काष्ठा _carl9170_tx_superframe *super = (व्योम *) skb->data;
	काष्ठा ieee80211_hdr *hdr = (व्योम *) super->frame_data;
	काष्ठा ieee80211_sta *sta;
	काष्ठा carl9170_sta_info *sta_info;
	काष्ठा carl9170_sta_tid *tid_info;
	u8 tid;

	अगर (!(txinfo->flags & IEEE80211_TX_CTL_AMPDU) ||
	    txinfo->flags & IEEE80211_TX_CTL_INJECTED)
		वापस;

	rcu_पढ़ो_lock();
	sta = __carl9170_get_tx_sta(ar, skb);
	अगर (unlikely(!sta))
		जाओ out_rcu;

	tid = ieee80211_get_tid(hdr);

	sta_info = (व्योम *) sta->drv_priv;
	tid_info = rcu_dereference(sta_info->agg[tid]);
	अगर (!tid_info)
		जाओ out_rcu;

	spin_lock_bh(&tid_info->lock);
	अगर (likely(tid_info->state >= CARL9170_TID_STATE_IDLE))
		carl9170_tx_shअगरt_bm(ar, tid_info, get_seq_h(hdr));

	अगर (sta_info->stats[tid].clear) अणु
		sta_info->stats[tid].clear = false;
		sta_info->stats[tid].req = false;
		sta_info->stats[tid].ampdu_len = 0;
		sta_info->stats[tid].ampdu_ack_len = 0;
	पूर्ण

	sta_info->stats[tid].ampdu_len++;
	अगर (txinfo->status.rates[0].count == 1)
		sta_info->stats[tid].ampdu_ack_len++;

	अगर (!(txinfo->flags & IEEE80211_TX_STAT_ACK))
		sta_info->stats[tid].req = true;

	अगर (super->f.mac_control & cpu_to_le16(AR9170_TX_MAC_IMM_BA)) अणु
		super->s.rix = sta_info->stats[tid].ampdu_len;
		super->s.cnt = sta_info->stats[tid].ampdu_ack_len;
		txinfo->flags |= IEEE80211_TX_STAT_AMPDU;
		अगर (sta_info->stats[tid].req)
			txinfo->flags |= IEEE80211_TX_STAT_AMPDU_NO_BACK;

		sta_info->stats[tid].clear = true;
	पूर्ण
	spin_unlock_bh(&tid_info->lock);

out_rcu:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम carl9170_tx_bar_status(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb,
	काष्ठा ieee80211_tx_info *tx_info)
अणु
	काष्ठा _carl9170_tx_superframe *super = (व्योम *) skb->data;
	काष्ठा ieee80211_bar *bar = (व्योम *) super->frame_data;

	/*
	 * Unlike all other frames, the status report क्रम BARs करोes
	 * not directly come from the hardware as it is incapable of
	 * matching a BA to a previously send BAR.
	 * Instead the RX-path will scan क्रम incoming BAs and set the
	 * IEEE80211_TX_STAT_ACK अगर it sees one that was likely
	 * caused by a BAR from us.
	 */

	अगर (unlikely(ieee80211_is_back_req(bar->frame_control)) &&
	   !(tx_info->flags & IEEE80211_TX_STAT_ACK)) अणु
		काष्ठा carl9170_bar_list_entry *entry;
		पूर्णांक queue = skb_get_queue_mapping(skb);

		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(entry, &ar->bar_list[queue], list) अणु
			अगर (entry->skb == skb) अणु
				spin_lock_bh(&ar->bar_list_lock[queue]);
				list_del_rcu(&entry->list);
				spin_unlock_bh(&ar->bar_list_lock[queue]);
				kमुक्त_rcu(entry, head);
				जाओ out;
			पूर्ण
		पूर्ण

		WARN(1, "bar not found in %d - ra:%pM ta:%pM c:%x ssn:%x\n",
		       queue, bar->ra, bar->ta, bar->control,
			bar->start_seq_num);
out:
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

व्योम carl9170_tx_status(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb,
			स्थिर bool success)
अणु
	काष्ठा ieee80211_tx_info *txinfo;

	carl9170_tx_accounting_मुक्त(ar, skb);

	txinfo = IEEE80211_SKB_CB(skb);

	carl9170_tx_bar_status(ar, skb, txinfo);

	अगर (success)
		txinfo->flags |= IEEE80211_TX_STAT_ACK;
	अन्यथा
		ar->tx_ack_failures++;

	अगर (txinfo->flags & IEEE80211_TX_CTL_AMPDU)
		carl9170_tx_status_process_ampdu(ar, skb, txinfo);

	carl9170_tx_ps_unblock(ar, skb);
	carl9170_tx_put_skb(skb);
पूर्ण

/* This function may be called क्रमm any context */
व्योम carl9170_tx_callback(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *txinfo = IEEE80211_SKB_CB(skb);

	atomic_dec(&ar->tx_total_pending);

	अगर (txinfo->flags & IEEE80211_TX_CTL_AMPDU)
		atomic_dec(&ar->tx_ampdu_upload);

	अगर (carl9170_tx_put_skb(skb))
		tasklet_hi_schedule(&ar->usb_tasklet);
पूर्ण

अटल काष्ठा sk_buff *carl9170_get_queued_skb(काष्ठा ar9170 *ar, u8 cookie,
					       काष्ठा sk_buff_head *queue)
अणु
	काष्ठा sk_buff *skb;

	spin_lock_bh(&queue->lock);
	skb_queue_walk(queue, skb) अणु
		काष्ठा _carl9170_tx_superframe *txc = (व्योम *) skb->data;

		अगर (txc->s.cookie != cookie)
			जारी;

		__skb_unlink(skb, queue);
		spin_unlock_bh(&queue->lock);

		carl9170_release_dev_space(ar, skb);
		वापस skb;
	पूर्ण
	spin_unlock_bh(&queue->lock);

	वापस शून्य;
पूर्ण

अटल व्योम carl9170_tx_fill_rateinfo(काष्ठा ar9170 *ar, अचिन्हित पूर्णांक rix,
	अचिन्हित पूर्णांक tries, काष्ठा ieee80211_tx_info *txinfo)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IEEE80211_TX_MAX_RATES; i++) अणु
		अगर (txinfo->status.rates[i].idx < 0)
			अवरोध;

		अगर (i == rix) अणु
			txinfo->status.rates[i].count = tries;
			i++;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (; i < IEEE80211_TX_MAX_RATES; i++) अणु
		txinfo->status.rates[i].idx = -1;
		txinfo->status.rates[i].count = 0;
	पूर्ण
पूर्ण

अटल व्योम carl9170_check_queue_stop_समयout(काष्ठा ar9170 *ar)
अणु
	पूर्णांक i;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *txinfo;
	काष्ठा carl9170_tx_info *arinfo;
	bool restart = false;

	क्रम (i = 0; i < ar->hw->queues; i++) अणु
		spin_lock_bh(&ar->tx_status[i].lock);

		skb = skb_peek(&ar->tx_status[i]);

		अगर (!skb)
			जाओ next;

		txinfo = IEEE80211_SKB_CB(skb);
		arinfo = (व्योम *) txinfo->rate_driver_data;

		अगर (समय_is_beक्रमe_jअगरfies(arinfo->समयout +
		    msecs_to_jअगरfies(CARL9170_QUEUE_STUCK_TIMEOUT)) == true)
			restart = true;

next:
		spin_unlock_bh(&ar->tx_status[i].lock);
	पूर्ण

	अगर (restart) अणु
		/*
		 * At least one queue has been stuck क्रम दीर्घ enough.
		 * Give the device a kick and hope it माला_लो back to
		 * work.
		 *
		 * possible reasons may include:
		 *  - frames got lost/corrupted (bad connection to the device)
		 *  - stalled rx processing/usb controller hiccups
		 *  - firmware errors/bugs
		 *  - every bug you can think of.
		 *  - all bugs you can't...
		 *  - ...
		 */
		carl9170_restart(ar, CARL9170_RR_STUCK_TX);
	पूर्ण
पूर्ण

अटल व्योम carl9170_tx_ampdu_समयout(काष्ठा ar9170 *ar)
अणु
	काष्ठा carl9170_sta_tid *iter;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *txinfo;
	काष्ठा carl9170_tx_info *arinfo;
	काष्ठा ieee80211_sta *sta;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(iter, &ar->tx_ampdu_list, list) अणु
		अगर (iter->state < CARL9170_TID_STATE_IDLE)
			जारी;

		spin_lock_bh(&iter->lock);
		skb = skb_peek(&iter->queue);
		अगर (!skb)
			जाओ unlock;

		txinfo = IEEE80211_SKB_CB(skb);
		arinfo = (व्योम *)txinfo->rate_driver_data;
		अगर (समय_is_after_jअगरfies(arinfo->समयout +
		    msecs_to_jअगरfies(CARL9170_QUEUE_TIMEOUT)))
			जाओ unlock;

		sta = iter->sta;
		अगर (WARN_ON(!sta))
			जाओ unlock;

		ieee80211_stop_tx_ba_session(sta, iter->tid);
unlock:
		spin_unlock_bh(&iter->lock);

	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम carl9170_tx_janitor(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ar9170 *ar = container_of(work, काष्ठा ar9170,
					 tx_janitor.work);
	अगर (!IS_STARTED(ar))
		वापस;

	ar->tx_janitor_last_run = jअगरfies;

	carl9170_check_queue_stop_समयout(ar);
	carl9170_tx_ampdu_समयout(ar);

	अगर (!atomic_पढ़ो(&ar->tx_total_queued))
		वापस;

	ieee80211_queue_delayed_work(ar->hw, &ar->tx_janitor,
		msecs_to_jअगरfies(CARL9170_TX_TIMEOUT));
पूर्ण

अटल व्योम __carl9170_tx_process_status(काष्ठा ar9170 *ar,
	स्थिर uपूर्णांक8_t cookie, स्थिर uपूर्णांक8_t info)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *txinfo;
	अचिन्हित पूर्णांक r, t, q;
	bool success = true;

	q = ar9170_qmap(info & CARL9170_TX_STATUS_QUEUE);

	skb = carl9170_get_queued_skb(ar, cookie, &ar->tx_status[q]);
	अगर (!skb) अणु
		/*
		 * We have lost the race to another thपढ़ो.
		 */

		वापस ;
	पूर्ण

	txinfo = IEEE80211_SKB_CB(skb);

	अगर (!(info & CARL9170_TX_STATUS_SUCCESS))
		success = false;

	r = (info & CARL9170_TX_STATUS_RIX) >> CARL9170_TX_STATUS_RIX_S;
	t = (info & CARL9170_TX_STATUS_TRIES) >> CARL9170_TX_STATUS_TRIES_S;

	carl9170_tx_fill_rateinfo(ar, r, t, txinfo);
	carl9170_tx_status(ar, skb, success);
पूर्ण

व्योम carl9170_tx_process_status(काष्ठा ar9170 *ar,
				स्थिर काष्ठा carl9170_rsp *cmd)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0;  i < cmd->hdr.ext; i++) अणु
		अगर (WARN_ON(i > ((cmd->hdr.len / 2) + 1))) अणु
			prपूर्णांक_hex_dump_bytes("UU:", DUMP_PREFIX_NONE,
					     (व्योम *) cmd, cmd->hdr.len + 4);
			अवरोध;
		पूर्ण

		__carl9170_tx_process_status(ar, cmd->_tx_status[i].cookie,
					     cmd->_tx_status[i].info);
	पूर्ण
पूर्ण

अटल व्योम carl9170_tx_rate_tpc_chains(काष्ठा ar9170 *ar,
	काष्ठा ieee80211_tx_info *info,	काष्ठा ieee80211_tx_rate *txrate,
	अचिन्हित पूर्णांक *phyrate, अचिन्हित पूर्णांक *tpc, अचिन्हित पूर्णांक *chains)
अणु
	काष्ठा ieee80211_rate *rate = शून्य;
	u8 *txघातer;
	अचिन्हित पूर्णांक idx;

	idx = txrate->idx;
	*tpc = 0;
	*phyrate = 0;

	अगर (txrate->flags & IEEE80211_TX_RC_MCS) अणु
		अगर (txrate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH) अणु
			/* +1 dBm क्रम HT40 */
			*tpc += 2;

			अगर (info->band == NL80211_BAND_2GHZ)
				txघातer = ar->घातer_2G_ht40;
			अन्यथा
				txघातer = ar->घातer_5G_ht40;
		पूर्ण अन्यथा अणु
			अगर (info->band == NL80211_BAND_2GHZ)
				txघातer = ar->घातer_2G_ht20;
			अन्यथा
				txघातer = ar->घातer_5G_ht20;
		पूर्ण

		*phyrate = txrate->idx;
		*tpc += txघातer[idx & 7];
	पूर्ण अन्यथा अणु
		अगर (info->band == NL80211_BAND_2GHZ) अणु
			अगर (idx < 4)
				txघातer = ar->घातer_2G_cck;
			अन्यथा
				txघातer = ar->घातer_2G_ofdm;
		पूर्ण अन्यथा अणु
			txघातer = ar->घातer_5G_leg;
			idx += 4;
		पूर्ण

		rate = &__carl9170_ratetable[idx];
		*tpc += txघातer[(rate->hw_value & 0x30) >> 4];
		*phyrate = rate->hw_value & 0xf;
	पूर्ण

	अगर (ar->eeprom.tx_mask == 1) अणु
		*chains = AR9170_TX_PHY_TXCHAIN_1;
	पूर्ण अन्यथा अणु
		अगर (!(txrate->flags & IEEE80211_TX_RC_MCS) &&
		    rate && rate->bitrate >= 360)
			*chains = AR9170_TX_PHY_TXCHAIN_1;
		अन्यथा
			*chains = AR9170_TX_PHY_TXCHAIN_2;
	पूर्ण

	*tpc = min_t(अचिन्हित पूर्णांक, *tpc, ar->hw->conf.घातer_level * 2);
पूर्ण

अटल __le32 carl9170_tx_physet(काष्ठा ar9170 *ar,
	काष्ठा ieee80211_tx_info *info, काष्ठा ieee80211_tx_rate *txrate)
अणु
	अचिन्हित पूर्णांक घातer = 0, chains = 0, phyrate = 0;
	__le32 पंचांगp;

	पंचांगp = cpu_to_le32(0);

	अगर (txrate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
		पंचांगp |= cpu_to_le32(AR9170_TX_PHY_BW_40MHZ <<
			AR9170_TX_PHY_BW_S);
	/* this works because 40 MHz is 2 and dup is 3 */
	अगर (txrate->flags & IEEE80211_TX_RC_DUP_DATA)
		पंचांगp |= cpu_to_le32(AR9170_TX_PHY_BW_40MHZ_DUP <<
			AR9170_TX_PHY_BW_S);

	अगर (txrate->flags & IEEE80211_TX_RC_SHORT_GI)
		पंचांगp |= cpu_to_le32(AR9170_TX_PHY_SHORT_GI);

	अगर (txrate->flags & IEEE80211_TX_RC_MCS) अणु
		SET_VAL(AR9170_TX_PHY_MCS, phyrate, txrate->idx);

		/* heavy clip control */
		पंचांगp |= cpu_to_le32((txrate->idx & 0x7) <<
			AR9170_TX_PHY_TX_HEAVY_CLIP_S);

		पंचांगp |= cpu_to_le32(AR9170_TX_PHY_MOD_HT);

		/*
		 * green field preamble करोes not work.
		 *
		 * अगर (txrate->flags & IEEE80211_TX_RC_GREEN_FIELD)
		 * पंचांगp |= cpu_to_le32(AR9170_TX_PHY_GREENFIELD);
		 */
	पूर्ण अन्यथा अणु
		अगर (info->band == NL80211_BAND_2GHZ) अणु
			अगर (txrate->idx <= AR9170_TX_PHY_RATE_CCK_11M)
				पंचांगp |= cpu_to_le32(AR9170_TX_PHY_MOD_CCK);
			अन्यथा
				पंचांगp |= cpu_to_le32(AR9170_TX_PHY_MOD_OFDM);
		पूर्ण अन्यथा अणु
			पंचांगp |= cpu_to_le32(AR9170_TX_PHY_MOD_OFDM);
		पूर्ण

		/*
		 * लघु preamble seems to be broken too.
		 *
		 * अगर (txrate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
		 *	पंचांगp |= cpu_to_le32(AR9170_TX_PHY_SHORT_PREAMBLE);
		 */
	पूर्ण
	carl9170_tx_rate_tpc_chains(ar, info, txrate,
				    &phyrate, &घातer, &chains);

	पंचांगp |= cpu_to_le32(SET_CONSTVAL(AR9170_TX_PHY_MCS, phyrate));
	पंचांगp |= cpu_to_le32(SET_CONSTVAL(AR9170_TX_PHY_TX_PWR, घातer));
	पंचांगp |= cpu_to_le32(SET_CONSTVAL(AR9170_TX_PHY_TXCHAIN, chains));
	वापस पंचांगp;
पूर्ण

अटल bool carl9170_tx_rts_check(काष्ठा ar9170 *ar,
				  काष्ठा ieee80211_tx_rate *rate,
				  bool ampdu, bool multi)
अणु
	चयन (ar->erp_mode) अणु
	हाल CARL9170_ERP_AUTO:
		अगर (ampdu)
			अवरोध;
		fallthrough;

	हाल CARL9170_ERP_MAC80211:
		अगर (!(rate->flags & IEEE80211_TX_RC_USE_RTS_CTS))
			अवरोध;
		fallthrough;

	हाल CARL9170_ERP_RTS:
		अगर (likely(!multi))
			वापस true;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल bool carl9170_tx_cts_check(काष्ठा ar9170 *ar,
				  काष्ठा ieee80211_tx_rate *rate)
अणु
	चयन (ar->erp_mode) अणु
	हाल CARL9170_ERP_AUTO:
	हाल CARL9170_ERP_MAC80211:
		अगर (!(rate->flags & IEEE80211_TX_RC_USE_CTS_PROTECT))
			अवरोध;
		fallthrough;

	हाल CARL9170_ERP_CTS:
		वापस true;

	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम carl9170_tx_get_rates(काष्ठा ar9170 *ar,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_sta *sta,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info;

	BUILD_BUG_ON(IEEE80211_TX_MAX_RATES < CARL9170_TX_MAX_RATES);
	BUILD_BUG_ON(IEEE80211_TX_MAX_RATES > IEEE80211_TX_RATE_TABLE_SIZE);

	info = IEEE80211_SKB_CB(skb);

	ieee80211_get_tx_rates(vअगर, sta, skb,
			       info->control.rates,
			       IEEE80211_TX_MAX_RATES);
पूर्ण

अटल व्योम carl9170_tx_apply_rateset(काष्ठा ar9170 *ar,
				      काष्ठा ieee80211_tx_info *sinfo,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_rate *txrate;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा _carl9170_tx_superframe *txc = (व्योम *) skb->data;
	पूर्णांक i;
	bool ampdu;
	bool no_ack;

	info = IEEE80211_SKB_CB(skb);
	ampdu = !!(info->flags & IEEE80211_TX_CTL_AMPDU);
	no_ack = !!(info->flags & IEEE80211_TX_CTL_NO_ACK);

	/* Set the rate control probe flag क्रम all (sub-) frames.
	 * This is because the TX_STATS_AMPDU flag is only set on
	 * the last frame, so it has to be inherited.
	 */
	info->flags |= (sinfo->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE);

	/* NOTE: For the first rate, the ERP & AMPDU flags are directly
	 * taken from mac_control. For all fallback rate, the firmware
	 * updates the mac_control flags from the rate info field.
	 */
	क्रम (i = 0; i < CARL9170_TX_MAX_RATES; i++) अणु
		__le32 phy_set;

		txrate = &sinfo->control.rates[i];
		अगर (txrate->idx < 0)
			अवरोध;

		phy_set = carl9170_tx_physet(ar, info, txrate);
		अगर (i == 0) अणु
			__le16 mac_पंचांगp = cpu_to_le16(0);

			/* first rate - part of the hw's frame header */
			txc->f.phy_control = phy_set;

			अगर (ampdu && txrate->flags & IEEE80211_TX_RC_MCS)
				mac_पंचांगp |= cpu_to_le16(AR9170_TX_MAC_AGGR);

			अगर (carl9170_tx_rts_check(ar, txrate, ampdu, no_ack))
				mac_पंचांगp |= cpu_to_le16(AR9170_TX_MAC_PROT_RTS);
			अन्यथा अगर (carl9170_tx_cts_check(ar, txrate))
				mac_पंचांगp |= cpu_to_le16(AR9170_TX_MAC_PROT_CTS);

			txc->f.mac_control |= mac_पंचांगp;
		पूर्ण अन्यथा अणु
			/* fallback rates are stored in the firmware's
			 * retry rate set array.
			 */
			txc->s.rr[i - 1] = phy_set;
		पूर्ण

		SET_VAL(CARL9170_TX_SUPER_RI_TRIES, txc->s.ri[i],
			txrate->count);

		अगर (carl9170_tx_rts_check(ar, txrate, ampdu, no_ack))
			txc->s.ri[i] |= (AR9170_TX_MAC_PROT_RTS <<
				CARL9170_TX_SUPER_RI_ERP_PROT_S);
		अन्यथा अगर (carl9170_tx_cts_check(ar, txrate))
			txc->s.ri[i] |= (AR9170_TX_MAC_PROT_CTS <<
				CARL9170_TX_SUPER_RI_ERP_PROT_S);

		अगर (ampdu && (txrate->flags & IEEE80211_TX_RC_MCS))
			txc->s.ri[i] |= CARL9170_TX_SUPER_RI_AMPDU;
	पूर्ण
पूर्ण

अटल पूर्णांक carl9170_tx_prepare(काष्ठा ar9170 *ar,
			       काष्ठा ieee80211_sta *sta,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा _carl9170_tx_superframe *txc;
	काष्ठा carl9170_vअगर_info *cvअगर;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा carl9170_tx_info *arinfo;
	अचिन्हित पूर्णांक hw_queue;
	__le16 mac_पंचांगp;
	u16 len;

	BUILD_BUG_ON(माप(*arinfo) > माप(info->rate_driver_data));
	BUILD_BUG_ON(माप(काष्ठा _carl9170_tx_superdesc) !=
		     CARL9170_TX_SUPERDESC_LEN);

	BUILD_BUG_ON(माप(काष्ठा _ar9170_tx_hwdesc) !=
		     AR9170_TX_HWDESC_LEN);

	BUILD_BUG_ON(AR9170_MAX_VIRTUAL_MAC >
		((CARL9170_TX_SUPER_MISC_VIF_ID >>
		 CARL9170_TX_SUPER_MISC_VIF_ID_S) + 1));

	hw_queue = ar9170_qmap(carl9170_get_queue(ar, skb));

	hdr = (व्योम *)skb->data;
	info = IEEE80211_SKB_CB(skb);
	len = skb->len;

	/*
	 * Note: If the frame was sent through a monitor पूर्णांकerface,
	 * the ieee80211_vअगर poपूर्णांकer can be शून्य.
	 */
	अगर (likely(info->control.vअगर))
		cvअगर = (व्योम *) info->control.vअगर->drv_priv;
	अन्यथा
		cvअगर = शून्य;

	txc = skb_push(skb, माप(*txc));
	स_रखो(txc, 0, माप(*txc));

	SET_VAL(CARL9170_TX_SUPER_MISC_QUEUE, txc->s.misc, hw_queue);

	अगर (likely(cvअगर))
		SET_VAL(CARL9170_TX_SUPER_MISC_VIF_ID, txc->s.misc, cvअगर->id);

	अगर (unlikely(info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM))
		txc->s.misc |= CARL9170_TX_SUPER_MISC_CAB;

	अगर (unlikely(info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ))
		txc->s.misc |= CARL9170_TX_SUPER_MISC_ASSIGN_SEQ;

	अगर (unlikely(ieee80211_is_probe_resp(hdr->frame_control)))
		txc->s.misc |= CARL9170_TX_SUPER_MISC_FILL_IN_TSF;

	mac_पंचांगp = cpu_to_le16(AR9170_TX_MAC_HW_DURATION |
			      AR9170_TX_MAC_BACKOFF);
	mac_पंचांगp |= cpu_to_le16((hw_queue << AR9170_TX_MAC_QOS_S) &
			       AR9170_TX_MAC_QOS);

	अगर (unlikely(info->flags & IEEE80211_TX_CTL_NO_ACK))
		mac_पंचांगp |= cpu_to_le16(AR9170_TX_MAC_NO_ACK);

	अगर (info->control.hw_key) अणु
		len += info->control.hw_key->icv_len;

		चयन (info->control.hw_key->cipher) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
		हाल WLAN_CIPHER_SUITE_TKIP:
			mac_पंचांगp |= cpu_to_le16(AR9170_TX_MAC_ENCR_RC4);
			अवरोध;
		हाल WLAN_CIPHER_SUITE_CCMP:
			mac_पंचांगp |= cpu_to_le16(AR9170_TX_MAC_ENCR_AES);
			अवरोध;
		शेष:
			WARN_ON(1);
			जाओ err_out;
		पूर्ण
	पूर्ण

	अगर (info->flags & IEEE80211_TX_CTL_AMPDU) अणु
		अचिन्हित पूर्णांक density, factor;

		अगर (unlikely(!sta || !cvअगर))
			जाओ err_out;

		factor = min_t(अचिन्हित पूर्णांक, 1u, sta->ht_cap.ampdu_factor);
		density = sta->ht_cap.ampdu_density;

		अगर (density) अणु
			/*
			 * Watch out!
			 *
			 * Otus uses slightly dअगरferent density values than
			 * those from the 802.11n spec.
			 */

			density = max_t(अचिन्हित पूर्णांक, density + 1, 7u);
		पूर्ण

		SET_VAL(CARL9170_TX_SUPER_AMPDU_DENSITY,
			txc->s.ampdu_settings, density);

		SET_VAL(CARL9170_TX_SUPER_AMPDU_FACTOR,
			txc->s.ampdu_settings, factor);
	पूर्ण

	txc->s.len = cpu_to_le16(skb->len);
	txc->f.length = cpu_to_le16(len + FCS_LEN);
	txc->f.mac_control = mac_पंचांगp;

	arinfo = (व्योम *)info->rate_driver_data;
	arinfo->समयout = jअगरfies;
	arinfo->ar = ar;
	kref_init(&arinfo->ref);
	वापस 0;

err_out:
	skb_pull(skb, माप(*txc));
	वापस -EINVAL;
पूर्ण

अटल व्योम carl9170_set_immba(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा _carl9170_tx_superframe *super;

	super = (व्योम *) skb->data;
	super->f.mac_control |= cpu_to_le16(AR9170_TX_MAC_IMM_BA);
पूर्ण

अटल व्योम carl9170_set_ampdu_params(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा _carl9170_tx_superframe *super;
	पूर्णांक पंचांगp;

	super = (व्योम *) skb->data;

	पंचांगp = (super->s.ampdu_settings & CARL9170_TX_SUPER_AMPDU_DENSITY) <<
		CARL9170_TX_SUPER_AMPDU_DENSITY_S;

	/*
	 * If you haven't noticed carl9170_tx_prepare has alपढ़ोy filled
	 * in all ampdu spacing & factor parameters.
	 * Now it's the समय to check whenever the settings have to be
	 * updated by the firmware, or अगर everything is still the same.
	 *
	 * There's no sane way to handle dअगरferent density values with
	 * this hardware, so we may as well just करो the compare in the
	 * driver.
	 */

	अगर (पंचांगp != ar->current_density) अणु
		ar->current_density = पंचांगp;
		super->s.ampdu_settings |=
			CARL9170_TX_SUPER_AMPDU_COMMIT_DENSITY;
	पूर्ण

	पंचांगp = (super->s.ampdu_settings & CARL9170_TX_SUPER_AMPDU_FACTOR) <<
		CARL9170_TX_SUPER_AMPDU_FACTOR_S;

	अगर (पंचांगp != ar->current_factor) अणु
		ar->current_factor = पंचांगp;
		super->s.ampdu_settings |=
			CARL9170_TX_SUPER_AMPDU_COMMIT_FACTOR;
	पूर्ण
पूर्ण

अटल व्योम carl9170_tx_ampdu(काष्ठा ar9170 *ar)
अणु
	काष्ठा sk_buff_head agg;
	काष्ठा carl9170_sta_tid *tid_info;
	काष्ठा sk_buff *skb, *first;
	काष्ठा ieee80211_tx_info *tx_info_first;
	अचिन्हित पूर्णांक i = 0, करोne_ampdus = 0;
	u16 seq, queue, पंचांगpssn;

	atomic_inc(&ar->tx_ampdu_scheduler);
	ar->tx_ampdu_schedule = false;

	अगर (atomic_पढ़ो(&ar->tx_ampdu_upload))
		वापस;

	अगर (!ar->tx_ampdu_list_len)
		वापस;

	__skb_queue_head_init(&agg);

	rcu_पढ़ो_lock();
	tid_info = rcu_dereference(ar->tx_ampdu_iter);
	अगर (WARN_ON_ONCE(!tid_info)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

retry:
	list_क्रम_each_entry_जारी_rcu(tid_info, &ar->tx_ampdu_list, list) अणु
		i++;

		अगर (tid_info->state < CARL9170_TID_STATE_PROGRESS)
			जारी;

		queue = TID_TO_WME_AC(tid_info->tid);

		spin_lock_bh(&tid_info->lock);
		अगर (tid_info->state != CARL9170_TID_STATE_XMIT)
			जाओ processed;

		tid_info->counter++;
		first = skb_peek(&tid_info->queue);
		पंचांगpssn = carl9170_get_seq(first);
		seq = tid_info->snx;

		अगर (unlikely(पंचांगpssn != seq)) अणु
			tid_info->state = CARL9170_TID_STATE_IDLE;

			जाओ processed;
		पूर्ण

		tx_info_first = शून्य;
		जबतक ((skb = skb_peek(&tid_info->queue))) अणु
			/* strict 0, 1, ..., n - 1, n frame sequence order */
			अगर (unlikely(carl9170_get_seq(skb) != seq))
				अवरोध;

			/* करोn't upload more than AMPDU FACTOR allows. */
			अगर (unlikely(SEQ_DIFF(tid_info->snx, tid_info->bsn) >=
			    (tid_info->max - 1)))
				अवरोध;

			अगर (!tx_info_first) अणु
				carl9170_tx_get_rates(ar, tid_info->vअगर,
						      tid_info->sta, first);
				tx_info_first = IEEE80211_SKB_CB(first);
			पूर्ण

			carl9170_tx_apply_rateset(ar, tx_info_first, skb);

			atomic_inc(&ar->tx_ampdu_upload);
			tid_info->snx = seq = SEQ_NEXT(seq);
			__skb_unlink(skb, &tid_info->queue);

			__skb_queue_tail(&agg, skb);

			अगर (skb_queue_len(&agg) >= CARL9170_NUM_TX_AGG_MAX)
				अवरोध;
		पूर्ण

		अगर (skb_queue_empty(&tid_info->queue) ||
		    carl9170_get_seq(skb_peek(&tid_info->queue)) !=
		    tid_info->snx) अणु
			/* stop TID, अगर A-MPDU frames are still missing,
			 * or whenever the queue is empty.
			 */

			tid_info->state = CARL9170_TID_STATE_IDLE;
		पूर्ण
		करोne_ampdus++;

processed:
		spin_unlock_bh(&tid_info->lock);

		अगर (skb_queue_empty(&agg))
			जारी;

		/* apply ampdu spacing & factor settings */
		carl9170_set_ampdu_params(ar, skb_peek(&agg));

		/* set aggregation push bit */
		carl9170_set_immba(ar, skb_peek_tail(&agg));

		spin_lock_bh(&ar->tx_pending[queue].lock);
		skb_queue_splice_tail_init(&agg, &ar->tx_pending[queue]);
		spin_unlock_bh(&ar->tx_pending[queue].lock);
		ar->tx_schedule = true;
	पूर्ण
	अगर ((करोne_ampdus++ == 0) && (i++ == 0))
		जाओ retry;

	rcu_assign_poपूर्णांकer(ar->tx_ampdu_iter, tid_info);
	rcu_पढ़ो_unlock();
पूर्ण

अटल काष्ठा sk_buff *carl9170_tx_pick_skb(काष्ठा ar9170 *ar,
					    काष्ठा sk_buff_head *queue)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा carl9170_tx_info *arinfo;

	BUILD_BUG_ON(माप(*arinfo) > माप(info->rate_driver_data));

	spin_lock_bh(&queue->lock);
	skb = skb_peek(queue);
	अगर (unlikely(!skb))
		जाओ err_unlock;

	अगर (carl9170_alloc_dev_space(ar, skb))
		जाओ err_unlock;

	__skb_unlink(skb, queue);
	spin_unlock_bh(&queue->lock);

	info = IEEE80211_SKB_CB(skb);
	arinfo = (व्योम *) info->rate_driver_data;

	arinfo->समयout = jअगरfies;
	वापस skb;

err_unlock:
	spin_unlock_bh(&queue->lock);
	वापस शून्य;
पूर्ण

व्योम carl9170_tx_drop(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा _carl9170_tx_superframe *super;
	uपूर्णांक8_t q = 0;

	ar->tx_dropped++;

	super = (व्योम *)skb->data;
	SET_VAL(CARL9170_TX_SUPER_MISC_QUEUE, q,
		ar9170_qmap(carl9170_get_queue(ar, skb)));
	__carl9170_tx_process_status(ar, super->s.cookie, q);
पूर्ण

अटल bool carl9170_tx_ps_drop(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा carl9170_sta_info *sta_info;
	काष्ठा ieee80211_tx_info *tx_info;

	rcu_पढ़ो_lock();
	sta = __carl9170_get_tx_sta(ar, skb);
	अगर (!sta)
		जाओ out_rcu;

	sta_info = (व्योम *) sta->drv_priv;
	tx_info = IEEE80211_SKB_CB(skb);

	अगर (unlikely(sta_info->sleeping) &&
	    !(tx_info->flags & (IEEE80211_TX_CTL_NO_PS_BUFFER |
				IEEE80211_TX_CTL_CLEAR_PS_FILT))) अणु
		rcu_पढ़ो_unlock();

		अगर (tx_info->flags & IEEE80211_TX_CTL_AMPDU)
			atomic_dec(&ar->tx_ampdu_upload);

		tx_info->flags |= IEEE80211_TX_STAT_TX_FILTERED;
		carl9170_release_dev_space(ar, skb);
		carl9170_tx_status(ar, skb, false);
		वापस true;
	पूर्ण

out_rcu:
	rcu_पढ़ो_unlock();
	वापस false;
पूर्ण

अटल व्योम carl9170_bar_check(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा _carl9170_tx_superframe *super = (व्योम *) skb->data;
	काष्ठा ieee80211_bar *bar = (व्योम *) super->frame_data;

	अगर (unlikely(ieee80211_is_back_req(bar->frame_control)) &&
	    skb->len >= माप(काष्ठा ieee80211_bar)) अणु
		काष्ठा carl9170_bar_list_entry *entry;
		अचिन्हित पूर्णांक queue = skb_get_queue_mapping(skb);

		entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
		अगर (!WARN_ON_ONCE(!entry)) अणु
			entry->skb = skb;
			spin_lock_bh(&ar->bar_list_lock[queue]);
			list_add_tail_rcu(&entry->list, &ar->bar_list[queue]);
			spin_unlock_bh(&ar->bar_list_lock[queue]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम carl9170_tx(काष्ठा ar9170 *ar)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक i, q;
	bool schedule_garbagecollector = false;

	ar->tx_schedule = false;

	अगर (unlikely(!IS_STARTED(ar)))
		वापस;

	carl9170_usb_handle_tx_err(ar);

	क्रम (i = 0; i < ar->hw->queues; i++) अणु
		जबतक (!skb_queue_empty(&ar->tx_pending[i])) अणु
			skb = carl9170_tx_pick_skb(ar, &ar->tx_pending[i]);
			अगर (unlikely(!skb))
				अवरोध;

			अगर (unlikely(carl9170_tx_ps_drop(ar, skb)))
				जारी;

			carl9170_bar_check(ar, skb);

			atomic_inc(&ar->tx_total_pending);

			q = __carl9170_get_queue(ar, i);
			/*
			 * NB: tx_status[i] vs. tx_status[q],
			 * TODO: Move पूर्णांकo pick_skb or alloc_dev_space.
			 */
			skb_queue_tail(&ar->tx_status[q], skb);

			/*
			 * increase ref count to "2".
			 * Ref counting is the easiest way to solve the
			 * race between the urb's completion routine:
			 *	carl9170_tx_callback
			 * and wlan tx status functions:
			 *	carl9170_tx_status/janitor.
			 */
			carl9170_tx_get_skb(skb);

			carl9170_usb_tx(ar, skb);
			schedule_garbagecollector = true;
		पूर्ण
	पूर्ण

	अगर (!schedule_garbagecollector)
		वापस;

	ieee80211_queue_delayed_work(ar->hw, &ar->tx_janitor,
		msecs_to_jअगरfies(CARL9170_TX_TIMEOUT));
पूर्ण

अटल bool carl9170_tx_ampdu_queue(काष्ठा ar9170 *ar,
	काष्ठा ieee80211_sta *sta, काष्ठा sk_buff *skb,
	काष्ठा ieee80211_tx_info *txinfo)
अणु
	काष्ठा carl9170_sta_info *sta_info;
	काष्ठा carl9170_sta_tid *agg;
	काष्ठा sk_buff *iter;
	u16 tid, seq, qseq, off;
	bool run = false;

	tid = carl9170_get_tid(skb);
	seq = carl9170_get_seq(skb);
	sta_info = (व्योम *) sta->drv_priv;

	rcu_पढ़ो_lock();
	agg = rcu_dereference(sta_info->agg[tid]);

	अगर (!agg)
		जाओ err_unlock_rcu;

	spin_lock_bh(&agg->lock);
	अगर (unlikely(agg->state < CARL9170_TID_STATE_IDLE))
		जाओ err_unlock;

	/* check अगर sequence is within the BA winकरोw */
	अगर (unlikely(!BAW_WITHIN(agg->bsn, CARL9170_BAW_BITS, seq)))
		जाओ err_unlock;

	अगर (WARN_ON_ONCE(!BAW_WITHIN(agg->snx, CARL9170_BAW_BITS, seq)))
		जाओ err_unlock;

	off = SEQ_DIFF(seq, agg->bsn);
	अगर (WARN_ON_ONCE(test_and_set_bit(off, agg->biपंचांगap)))
		जाओ err_unlock;

	अगर (likely(BAW_WITHIN(agg->hsn, CARL9170_BAW_BITS, seq))) अणु
		__skb_queue_tail(&agg->queue, skb);
		agg->hsn = seq;
		जाओ queued;
	पूर्ण

	skb_queue_reverse_walk(&agg->queue, iter) अणु
		qseq = carl9170_get_seq(iter);

		अगर (BAW_WITHIN(qseq, CARL9170_BAW_BITS, seq)) अणु
			__skb_queue_after(&agg->queue, iter, skb);
			जाओ queued;
		पूर्ण
	पूर्ण

	__skb_queue_head(&agg->queue, skb);
queued:

	अगर (unlikely(agg->state != CARL9170_TID_STATE_XMIT)) अणु
		अगर (agg->snx == carl9170_get_seq(skb_peek(&agg->queue))) अणु
			agg->state = CARL9170_TID_STATE_XMIT;
			run = true;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&agg->lock);
	rcu_पढ़ो_unlock();

	वापस run;

err_unlock:
	spin_unlock_bh(&agg->lock);

err_unlock_rcu:
	rcu_पढ़ो_unlock();
	txinfo->flags &= ~IEEE80211_TX_CTL_AMPDU;
	carl9170_tx_status(ar, skb, false);
	ar->tx_dropped++;
	वापस false;
पूर्ण

व्योम carl9170_op_tx(काष्ठा ieee80211_hw *hw,
		    काष्ठा ieee80211_tx_control *control,
		    काष्ठा sk_buff *skb)
अणु
	काष्ठा ar9170 *ar = hw->priv;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_sta *sta = control->sta;
	काष्ठा ieee80211_vअगर *vअगर;
	bool run;

	अगर (unlikely(!IS_STARTED(ar)))
		जाओ err_मुक्त;

	info = IEEE80211_SKB_CB(skb);
	vअगर = info->control.vअगर;

	अगर (unlikely(carl9170_tx_prepare(ar, sta, skb)))
		जाओ err_मुक्त;

	carl9170_tx_accounting(ar, skb);
	/*
	 * from now on, one has to use carl9170_tx_status to मुक्त
	 * all ressouces which are associated with the frame.
	 */

	अगर (sta) अणु
		काष्ठा carl9170_sta_info *stai = (व्योम *) sta->drv_priv;
		atomic_inc(&stai->pending_frames);
	पूर्ण

	अगर (info->flags & IEEE80211_TX_CTL_AMPDU) अणु
		/* to अटल code analyzers and reviewers:
		 * mac80211 guarantees that a valid "sta"
		 * reference is present, अगर a frame is to
		 * be part of an ampdu. Hence any extra
		 * sta == शून्य checks are redundant in this
		 * special हाल.
		 */
		run = carl9170_tx_ampdu_queue(ar, sta, skb, info);
		अगर (run)
			carl9170_tx_ampdu(ar);

	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक queue = skb_get_queue_mapping(skb);

		carl9170_tx_get_rates(ar, vअगर, sta, skb);
		carl9170_tx_apply_rateset(ar, info, skb);
		skb_queue_tail(&ar->tx_pending[queue], skb);
	पूर्ण

	carl9170_tx(ar);
	वापस;

err_मुक्त:
	ar->tx_dropped++;
	ieee80211_मुक्त_txskb(ar->hw, skb);
पूर्ण

व्योम carl9170_tx_scheduler(काष्ठा ar9170 *ar)
अणु

	अगर (ar->tx_ampdu_schedule)
		carl9170_tx_ampdu(ar);

	अगर (ar->tx_schedule)
		carl9170_tx(ar);
पूर्ण

/* caller has to take rcu_पढ़ो_lock */
अटल काष्ठा carl9170_vअगर_info *carl9170_pick_beaconing_vअगर(काष्ठा ar9170 *ar)
अणु
	काष्ठा carl9170_vअगर_info *cvअगर;
	पूर्णांक i = 1;

	/* The AR9170 hardware has no fancy beacon queue or some
	 * other scheduling mechanism. So, the driver has to make
	 * due by setting the two beacon समयrs (pretbtt and tbtt)
	 * once and then swapping the beacon address in the HW's
	 * रेजिस्टर file each समय the pretbtt fires.
	 */

	cvअगर = rcu_dereference(ar->beacon_iter);
	अगर (ar->vअगरs > 0 && cvअगर) अणु
		करो अणु
			list_क्रम_each_entry_जारी_rcu(cvअगर, &ar->vअगर_list,
							 list) अणु
				अगर (cvअगर->active && cvअगर->enable_beacon)
					जाओ out;
			पूर्ण
		पूर्ण जबतक (ar->beacon_enabled && i--);
	पूर्ण

out:
	RCU_INIT_POINTER(ar->beacon_iter, cvअगर);
	वापस cvअगर;
पूर्ण

अटल bool carl9170_tx_beacon_physet(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb,
				      u32 *ht1, u32 *plcp)
अणु
	काष्ठा ieee80211_tx_info *txinfo;
	काष्ठा ieee80211_tx_rate *rate;
	अचिन्हित पूर्णांक घातer, chains;
	bool ht_rate;

	txinfo = IEEE80211_SKB_CB(skb);
	rate = &txinfo->control.rates[0];
	ht_rate = !!(txinfo->control.rates[0].flags & IEEE80211_TX_RC_MCS);
	carl9170_tx_rate_tpc_chains(ar, txinfo, rate, plcp, &घातer, &chains);

	*ht1 = AR9170_MAC_BCN_HT1_TX_ANT0;
	अगर (chains == AR9170_TX_PHY_TXCHAIN_2)
		*ht1 |= AR9170_MAC_BCN_HT1_TX_ANT1;
	SET_VAL(AR9170_MAC_BCN_HT1_PWR_CTRL, *ht1, 7);
	SET_VAL(AR9170_MAC_BCN_HT1_TPC, *ht1, घातer);
	SET_VAL(AR9170_MAC_BCN_HT1_CHAIN_MASK, *ht1, chains);

	अगर (ht_rate) अणु
		*ht1 |= AR9170_MAC_BCN_HT1_HT_EN;
		अगर (rate->flags & IEEE80211_TX_RC_SHORT_GI)
			*plcp |= AR9170_MAC_BCN_HT2_SGI;

		अगर (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH) अणु
			*ht1 |= AR9170_MAC_BCN_HT1_BWC_40M_SHARED;
			*plcp |= AR9170_MAC_BCN_HT2_BW40;
		पूर्ण अन्यथा अगर (rate->flags & IEEE80211_TX_RC_DUP_DATA) अणु
			*ht1 |= AR9170_MAC_BCN_HT1_BWC_40M_DUP;
			*plcp |= AR9170_MAC_BCN_HT2_BW40;
		पूर्ण

		SET_VAL(AR9170_MAC_BCN_HT2_LEN, *plcp, skb->len + FCS_LEN);
	पूर्ण अन्यथा अणु
		अगर (*plcp <= AR9170_TX_PHY_RATE_CCK_11M)
			*plcp |= ((skb->len + FCS_LEN) << (3 + 16)) + 0x0400;
		अन्यथा
			*plcp |= ((skb->len + FCS_LEN) << 16) + 0x0010;
	पूर्ण

	वापस ht_rate;
पूर्ण

पूर्णांक carl9170_update_beacon(काष्ठा ar9170 *ar, स्थिर bool submit)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा carl9170_vअगर_info *cvअगर;
	__le32 *data, *old = शून्य;
	u32 word, ht1, plcp, off, addr, len;
	पूर्णांक i = 0, err = 0;
	bool ht_rate;

	rcu_पढ़ो_lock();
	cvअगर = carl9170_pick_beaconing_vअगर(ar);
	अगर (!cvअगर)
		जाओ out_unlock;

	skb = ieee80211_beacon_get_tim(ar->hw, carl9170_get_vअगर(cvअगर),
		शून्य, शून्य);

	अगर (!skb) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	spin_lock_bh(&ar->beacon_lock);
	data = (__le32 *)skb->data;
	अगर (cvअगर->beacon)
		old = (__le32 *)cvअगर->beacon->data;

	off = cvअगर->id * AR9170_MAC_BCN_LENGTH_MAX;
	addr = ar->fw.beacon_addr + off;
	len = roundup(skb->len + FCS_LEN, 4);

	अगर ((off + len) > ar->fw.beacon_max_len) अणु
		अगर (net_ratelimit()) अणु
			wiphy_err(ar->hw->wiphy, "beacon does not "
				  "fit into device memory!\n");
		पूर्ण
		err = -EINVAL;
		जाओ err_unlock;
	पूर्ण

	अगर (len > AR9170_MAC_BCN_LENGTH_MAX) अणु
		अगर (net_ratelimit()) अणु
			wiphy_err(ar->hw->wiphy, "no support for beacons "
				"bigger than %d (yours:%d).\n",
				 AR9170_MAC_BCN_LENGTH_MAX, len);
		पूर्ण

		err = -EMSGSIZE;
		जाओ err_unlock;
	पूर्ण

	ht_rate = carl9170_tx_beacon_physet(ar, skb, &ht1, &plcp);

	carl9170_async_regग_लिखो_begin(ar);
	carl9170_async_regग_लिखो(AR9170_MAC_REG_BCN_HT1, ht1);
	अगर (ht_rate)
		carl9170_async_regग_लिखो(AR9170_MAC_REG_BCN_HT2, plcp);
	अन्यथा
		carl9170_async_regग_लिखो(AR9170_MAC_REG_BCN_PLCP, plcp);

	क्रम (i = 0; i < DIV_ROUND_UP(skb->len, 4); i++) अणु
		/*
		 * XXX: This accesses beyond skb data क्रम up
		 *	to the last 3 bytes!!
		 */

		अगर (old && (data[i] == old[i]))
			जारी;

		word = le32_to_cpu(data[i]);
		carl9170_async_regग_लिखो(addr + 4 * i, word);
	पूर्ण
	carl9170_async_regग_लिखो_finish();

	dev_kमुक्त_skb_any(cvअगर->beacon);
	cvअगर->beacon = शून्य;

	err = carl9170_async_regग_लिखो_result();
	अगर (!err)
		cvअगर->beacon = skb;
	spin_unlock_bh(&ar->beacon_lock);
	अगर (err)
		जाओ err_मुक्त;

	अगर (submit) अणु
		err = carl9170_bcn_ctrl(ar, cvअगर->id,
					CARL9170_BCN_CTRL_CAB_TRIGGER,
					addr, skb->len + FCS_LEN);

		अगर (err)
			जाओ err_मुक्त;
	पूर्ण
out_unlock:
	rcu_पढ़ो_unlock();
	वापस 0;

err_unlock:
	spin_unlock_bh(&ar->beacon_lock);

err_मुक्त:
	rcu_पढ़ो_unlock();
	dev_kमुक्त_skb_any(skb);
	वापस err;
पूर्ण
