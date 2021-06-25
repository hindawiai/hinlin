<शैली गुरु>
/*
 * Atheros CARL9170 driver
 *
 * mac80211 पूर्णांकeraction code
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
#समावेश <linux/अक्रमom.h>
#समावेश <net/mac80211.h>
#समावेश <net/cfg80211.h>
#समावेश "hw.h"
#समावेश "carl9170.h"
#समावेश "cmd.h"

अटल bool modparam_nohwcrypt;
module_param_named(nohwcrypt, modparam_nohwcrypt, bool, 0444);
MODULE_PARM_DESC(nohwcrypt, "Disable hardware crypto offload.");

पूर्णांक modparam_noht;
module_param_named(noht, modparam_noht, पूर्णांक, 0444);
MODULE_PARM_DESC(noht, "Disable MPDU aggregation.");

#घोषणा RATE(_bitrate, _hw_rate, _txpidx, _flags) अणु	\
	.bitrate	= (_bitrate),			\
	.flags		= (_flags),			\
	.hw_value	= (_hw_rate) | (_txpidx) << 4,	\
पूर्ण

काष्ठा ieee80211_rate __carl9170_ratetable[] = अणु
	RATE(10, 0, 0, 0),
	RATE(20, 1, 1, IEEE80211_RATE_SHORT_PREAMBLE),
	RATE(55, 2, 2, IEEE80211_RATE_SHORT_PREAMBLE),
	RATE(110, 3, 3, IEEE80211_RATE_SHORT_PREAMBLE),
	RATE(60, 0xb, 0, 0),
	RATE(90, 0xf, 0, 0),
	RATE(120, 0xa, 0, 0),
	RATE(180, 0xe, 0, 0),
	RATE(240, 0x9, 0, 0),
	RATE(360, 0xd, 1, 0),
	RATE(480, 0x8, 2, 0),
	RATE(540, 0xc, 3, 0),
पूर्ण;
#अघोषित RATE

#घोषणा carl9170_g_ratetable	(__carl9170_ratetable + 0)
#घोषणा carl9170_g_ratetable_size	12
#घोषणा carl9170_a_ratetable	(__carl9170_ratetable + 4)
#घोषणा carl9170_a_ratetable_size	8

/*
 * NB: The hw_value is used as an index पूर्णांकo the carl9170_phy_freq_params
 *     array in phy.c so that we करोn't have to करो frequency lookups!
 */
#घोषणा CHAN(_freq, _idx) अणु		\
	.center_freq	= (_freq),	\
	.hw_value	= (_idx),	\
	.max_घातer	= 18, /* XXX */	\
पूर्ण

अटल काष्ठा ieee80211_channel carl9170_2ghz_chantable[] = अणु
	CHAN(2412,  0),
	CHAN(2417,  1),
	CHAN(2422,  2),
	CHAN(2427,  3),
	CHAN(2432,  4),
	CHAN(2437,  5),
	CHAN(2442,  6),
	CHAN(2447,  7),
	CHAN(2452,  8),
	CHAN(2457,  9),
	CHAN(2462, 10),
	CHAN(2467, 11),
	CHAN(2472, 12),
	CHAN(2484, 13),
पूर्ण;

अटल काष्ठा ieee80211_channel carl9170_5ghz_chantable[] = अणु
	CHAN(4920, 14),
	CHAN(4940, 15),
	CHAN(4960, 16),
	CHAN(4980, 17),
	CHAN(5040, 18),
	CHAN(5060, 19),
	CHAN(5080, 20),
	CHAN(5180, 21),
	CHAN(5200, 22),
	CHAN(5220, 23),
	CHAN(5240, 24),
	CHAN(5260, 25),
	CHAN(5280, 26),
	CHAN(5300, 27),
	CHAN(5320, 28),
	CHAN(5500, 29),
	CHAN(5520, 30),
	CHAN(5540, 31),
	CHAN(5560, 32),
	CHAN(5580, 33),
	CHAN(5600, 34),
	CHAN(5620, 35),
	CHAN(5640, 36),
	CHAN(5660, 37),
	CHAN(5680, 38),
	CHAN(5700, 39),
	CHAN(5745, 40),
	CHAN(5765, 41),
	CHAN(5785, 42),
	CHAN(5805, 43),
	CHAN(5825, 44),
	CHAN(5170, 45),
	CHAN(5190, 46),
	CHAN(5210, 47),
	CHAN(5230, 48),
पूर्ण;
#अघोषित CHAN

#घोषणा CARL9170_HT_CAP							\
अणु									\
	.ht_supported	= true,						\
	.cap		= IEEE80211_HT_CAP_MAX_AMSDU |			\
			  IEEE80211_HT_CAP_SUP_WIDTH_20_40 |		\
			  IEEE80211_HT_CAP_SGI_40 |			\
			  IEEE80211_HT_CAP_DSSSCCK40 |			\
			  IEEE80211_HT_CAP_SM_PS,			\
	.ampdu_factor	= IEEE80211_HT_MAX_AMPDU_64K,			\
	.ampdu_density	= IEEE80211_HT_MPDU_DENSITY_8,			\
	.mcs		= अणु						\
		.rx_mask = अणु 0xff, 0xff, 0, 0, 0x1, 0, 0, 0, 0, 0, पूर्ण,	\
		.rx_highest = cpu_to_le16(300),				\
		.tx_params = IEEE80211_HT_MCS_TX_DEFINED,		\
	पूर्ण,								\
पूर्ण

अटल काष्ठा ieee80211_supported_band carl9170_band_2GHz = अणु
	.channels	= carl9170_2ghz_chantable,
	.n_channels	= ARRAY_SIZE(carl9170_2ghz_chantable),
	.bitrates	= carl9170_g_ratetable,
	.n_bitrates	= carl9170_g_ratetable_size,
	.ht_cap		= CARL9170_HT_CAP,
पूर्ण;

अटल काष्ठा ieee80211_supported_band carl9170_band_5GHz = अणु
	.channels	= carl9170_5ghz_chantable,
	.n_channels	= ARRAY_SIZE(carl9170_5ghz_chantable),
	.bitrates	= carl9170_a_ratetable,
	.n_bitrates	= carl9170_a_ratetable_size,
	.ht_cap		= CARL9170_HT_CAP,
पूर्ण;

अटल व्योम carl9170_ampdu_gc(काष्ठा ar9170 *ar)
अणु
	काष्ठा carl9170_sta_tid *tid_info;
	LIST_HEAD(tid_gc);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(tid_info, &ar->tx_ampdu_list, list) अणु
		spin_lock_bh(&ar->tx_ampdu_list_lock);
		अगर (tid_info->state == CARL9170_TID_STATE_SHUTDOWN) अणु
			tid_info->state = CARL9170_TID_STATE_KILLED;
			list_del_rcu(&tid_info->list);
			ar->tx_ampdu_list_len--;
			list_add_tail(&tid_info->पंचांगp_list, &tid_gc);
		पूर्ण
		spin_unlock_bh(&ar->tx_ampdu_list_lock);

	पूर्ण
	rcu_assign_poपूर्णांकer(ar->tx_ampdu_iter, tid_info);
	rcu_पढ़ो_unlock();

	synchronize_rcu();

	जबतक (!list_empty(&tid_gc)) अणु
		काष्ठा sk_buff *skb;
		tid_info = list_first_entry(&tid_gc, काष्ठा carl9170_sta_tid,
					    पंचांगp_list);

		जबतक ((skb = __skb_dequeue(&tid_info->queue)))
			carl9170_tx_status(ar, skb, false);

		list_del_init(&tid_info->पंचांगp_list);
		kमुक्त(tid_info);
	पूर्ण
पूर्ण

अटल व्योम carl9170_flush(काष्ठा ar9170 *ar, bool drop_queued)
अणु
	अगर (drop_queued) अणु
		पूर्णांक i;

		/*
		 * We can only drop frames which have not been uploaded
		 * to the device yet.
		 */

		क्रम (i = 0; i < ar->hw->queues; i++) अणु
			काष्ठा sk_buff *skb;

			जबतक ((skb = skb_dequeue(&ar->tx_pending[i]))) अणु
				काष्ठा ieee80211_tx_info *info;

				info = IEEE80211_SKB_CB(skb);
				अगर (info->flags & IEEE80211_TX_CTL_AMPDU)
					atomic_dec(&ar->tx_ampdu_upload);

				carl9170_tx_status(ar, skb, false);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Wait क्रम all other outstanding frames to समयout. */
	अगर (atomic_पढ़ो(&ar->tx_total_queued))
		WARN_ON(रुको_क्रम_completion_समयout(&ar->tx_flush, HZ) == 0);
पूर्ण

अटल व्योम carl9170_flush_ba(काष्ठा ar9170 *ar)
अणु
	काष्ठा sk_buff_head मुक्त;
	काष्ठा carl9170_sta_tid *tid_info;
	काष्ठा sk_buff *skb;

	__skb_queue_head_init(&मुक्त);

	rcu_पढ़ो_lock();
	spin_lock_bh(&ar->tx_ampdu_list_lock);
	list_क्रम_each_entry_rcu(tid_info, &ar->tx_ampdu_list, list) अणु
		अगर (tid_info->state > CARL9170_TID_STATE_SUSPEND) अणु
			tid_info->state = CARL9170_TID_STATE_SUSPEND;

			spin_lock(&tid_info->lock);
			जबतक ((skb = __skb_dequeue(&tid_info->queue)))
				__skb_queue_tail(&मुक्त, skb);
			spin_unlock(&tid_info->lock);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ar->tx_ampdu_list_lock);
	rcu_पढ़ो_unlock();

	जबतक ((skb = __skb_dequeue(&मुक्त)))
		carl9170_tx_status(ar, skb, false);
पूर्ण

अटल व्योम carl9170_zap_queues(काष्ठा ar9170 *ar)
अणु
	काष्ठा carl9170_vअगर_info *cvअगर;
	अचिन्हित पूर्णांक i;

	carl9170_ampdu_gc(ar);

	carl9170_flush_ba(ar);
	carl9170_flush(ar, true);

	क्रम (i = 0; i < ar->hw->queues; i++) अणु
		spin_lock_bh(&ar->tx_status[i].lock);
		जबतक (!skb_queue_empty(&ar->tx_status[i])) अणु
			काष्ठा sk_buff *skb;

			skb = skb_peek(&ar->tx_status[i]);
			carl9170_tx_get_skb(skb);
			spin_unlock_bh(&ar->tx_status[i].lock);
			carl9170_tx_drop(ar, skb);
			spin_lock_bh(&ar->tx_status[i].lock);
			carl9170_tx_put_skb(skb);
		पूर्ण
		spin_unlock_bh(&ar->tx_status[i].lock);
	पूर्ण

	BUILD_BUG_ON(CARL9170_NUM_TX_LIMIT_SOFT < 1);
	BUILD_BUG_ON(CARL9170_NUM_TX_LIMIT_HARD < CARL9170_NUM_TX_LIMIT_SOFT);
	BUILD_BUG_ON(CARL9170_NUM_TX_LIMIT_HARD >= CARL9170_BAW_BITS);

	/* reinitialize queues statistics */
	स_रखो(&ar->tx_stats, 0, माप(ar->tx_stats));
	क्रम (i = 0; i < ar->hw->queues; i++)
		ar->tx_stats[i].limit = CARL9170_NUM_TX_LIMIT_HARD;

	क्रम (i = 0; i < DIV_ROUND_UP(ar->fw.mem_blocks, BITS_PER_LONG); i++)
		ar->mem_biपंचांगap[i] = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(cvअगर, &ar->vअगर_list, list) अणु
		spin_lock_bh(&ar->beacon_lock);
		dev_kमुक्त_skb_any(cvअगर->beacon);
		cvअगर->beacon = शून्य;
		spin_unlock_bh(&ar->beacon_lock);
	पूर्ण
	rcu_पढ़ो_unlock();

	atomic_set(&ar->tx_ampdu_upload, 0);
	atomic_set(&ar->tx_ampdu_scheduler, 0);
	atomic_set(&ar->tx_total_pending, 0);
	atomic_set(&ar->tx_total_queued, 0);
	atomic_set(&ar->mem_मुक्त_blocks, ar->fw.mem_blocks);
पूर्ण

#घोषणा CARL9170_FILL_QUEUE(queue, ai_fs, cwmin, cwmax, _txop)		\
करो अणु									\
	queue.aअगरs = ai_fs;						\
	queue.cw_min = cwmin;						\
	queue.cw_max = cwmax;						\
	queue.txop = _txop;						\
पूर्ण जबतक (0)

अटल पूर्णांक carl9170_op_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ar9170 *ar = hw->priv;
	पूर्णांक err, i;

	mutex_lock(&ar->mutex);

	carl9170_zap_queues(ar);

	/* reset QoS शेषs */
	CARL9170_FILL_QUEUE(ar->edcf[AR9170_TXQ_VO], 2, 3,     7, 47);
	CARL9170_FILL_QUEUE(ar->edcf[AR9170_TXQ_VI], 2, 7,    15, 94);
	CARL9170_FILL_QUEUE(ar->edcf[AR9170_TXQ_BE], 3, 15, 1023,  0);
	CARL9170_FILL_QUEUE(ar->edcf[AR9170_TXQ_BK], 7, 15, 1023,  0);
	CARL9170_FILL_QUEUE(ar->edcf[AR9170_TXQ_SPECIAL], 2, 3, 7, 0);

	ar->current_factor = ar->current_density = -1;
	/* "The first key is unique." */
	ar->usedkeys = 1;
	ar->filter_state = 0;
	ar->ps.last_action = jअगरfies;
	ar->ps.last_slept = jअगरfies;
	ar->erp_mode = CARL9170_ERP_AUTO;

	/* Set "disable hw crypto offload" whenever the module parameter
	 * nohwcrypt is true or अगर the firmware करोes not support it.
	 */
	ar->disable_offload = modparam_nohwcrypt |
		ar->fw.disable_offload_fw;
	ar->rx_software_decryption = ar->disable_offload;

	क्रम (i = 0; i < ar->hw->queues; i++) अणु
		ar->queue_stop_समयout[i] = jअगरfies;
		ar->max_queue_stop_समयout[i] = 0;
	पूर्ण

	atomic_set(&ar->mem_allocs, 0);

	err = carl9170_usb_खोलो(ar);
	अगर (err)
		जाओ out;

	err = carl9170_init_mac(ar);
	अगर (err)
		जाओ out;

	err = carl9170_set_qos(ar);
	अगर (err)
		जाओ out;

	अगर (ar->fw.rx_filter) अणु
		err = carl9170_rx_filter(ar, CARL9170_RX_FILTER_OTHER_RA |
			CARL9170_RX_FILTER_CTL_OTHER | CARL9170_RX_FILTER_BAD);
		अगर (err)
			जाओ out;
	पूर्ण

	err = carl9170_ग_लिखो_reg(ar, AR9170_MAC_REG_DMA_TRIGGER,
				 AR9170_DMA_TRIGGER_RXQ);
	अगर (err)
		जाओ out;

	/* Clear key-cache */
	क्रम (i = 0; i < AR9170_CAM_MAX_USER + 4; i++) अणु
		err = carl9170_upload_key(ar, i, शून्य, AR9170_ENC_ALG_NONE,
					  0, शून्य, 0);
		अगर (err)
			जाओ out;

		err = carl9170_upload_key(ar, i, शून्य, AR9170_ENC_ALG_NONE,
					  1, शून्य, 0);
		अगर (err)
			जाओ out;

		अगर (i < AR9170_CAM_MAX_USER) अणु
			err = carl9170_disable_key(ar, i);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

	carl9170_set_state_when(ar, CARL9170_IDLE, CARL9170_STARTED);

	ieee80211_queue_delayed_work(ar->hw, &ar->stat_work,
		round_jअगरfies(msecs_to_jअगरfies(CARL9170_STAT_WORK)));

	ieee80211_wake_queues(ar->hw);
	err = 0;

out:
	mutex_unlock(&ar->mutex);
	वापस err;
पूर्ण

अटल व्योम carl9170_cancel_worker(काष्ठा ar9170 *ar)
अणु
	cancel_delayed_work_sync(&ar->stat_work);
	cancel_delayed_work_sync(&ar->tx_janitor);
#अगर_घोषित CONFIG_CARL9170_LEDS
	cancel_delayed_work_sync(&ar->led_work);
#पूर्ण_अगर /* CONFIG_CARL9170_LEDS */
	cancel_work_sync(&ar->ps_work);
	cancel_work_sync(&ar->ping_work);
	cancel_work_sync(&ar->ampdu_work);
पूर्ण

अटल व्योम carl9170_op_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ar9170 *ar = hw->priv;

	carl9170_set_state_when(ar, CARL9170_STARTED, CARL9170_IDLE);

	ieee80211_stop_queues(ar->hw);

	mutex_lock(&ar->mutex);
	अगर (IS_ACCEPTING_CMD(ar)) अणु
		RCU_INIT_POINTER(ar->beacon_iter, शून्य);

		carl9170_led_set_state(ar, 0);

		/* stop DMA */
		carl9170_ग_लिखो_reg(ar, AR9170_MAC_REG_DMA_TRIGGER, 0);
		carl9170_usb_stop(ar);
	पूर्ण

	carl9170_zap_queues(ar);
	mutex_unlock(&ar->mutex);

	carl9170_cancel_worker(ar);
पूर्ण

अटल व्योम carl9170_restart_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ar9170 *ar = container_of(work, काष्ठा ar9170,
					 restart_work);
	पूर्णांक err = -EIO;

	ar->usedkeys = 0;
	ar->filter_state = 0;
	carl9170_cancel_worker(ar);

	mutex_lock(&ar->mutex);
	अगर (!ar->क्रमce_usb_reset) अणु
		err = carl9170_usb_restart(ar);
		अगर (net_ratelimit()) अणु
			अगर (err)
				dev_err(&ar->udev->dev, "Failed to restart device (%d).\n", err);
			अन्यथा
				dev_info(&ar->udev->dev, "device restarted successfully.\n");
		पूर्ण
	पूर्ण
	carl9170_zap_queues(ar);
	mutex_unlock(&ar->mutex);

	अगर (!err && !ar->क्रमce_usb_reset) अणु
		ar->restart_counter++;
		atomic_set(&ar->pending_restarts, 0);

		ieee80211_restart_hw(ar->hw);
	पूर्ण अन्यथा अणु
		/*
		 * The reset was unsuccessful and the device seems to
		 * be dead. But there's still one option: a low-level
		 * usb subप्रणाली reset...
		 */

		carl9170_usb_reset(ar);
	पूर्ण
पूर्ण

व्योम carl9170_restart(काष्ठा ar9170 *ar, स्थिर क्रमागत carl9170_restart_reasons r)
अणु
	carl9170_set_state_when(ar, CARL9170_STARTED, CARL9170_IDLE);

	/*
	 * Someबार, an error can trigger several dअगरferent reset events.
	 * By ignoring these *surplus* reset events, the device won't be
	 * समाप्तed again, right after it has recovered.
	 */
	अगर (atomic_inc_वापस(&ar->pending_restarts) > 1) अणु
		dev_dbg(&ar->udev->dev, "ignoring restart (%d)\n", r);
		वापस;
	पूर्ण

	ieee80211_stop_queues(ar->hw);

	dev_err(&ar->udev->dev, "restart device (%d)\n", r);

	अगर (!WARN_ON(r == CARL9170_RR_NO_REASON) ||
	    !WARN_ON(r >= __CARL9170_RR_LAST))
		ar->last_reason = r;

	अगर (!ar->रेजिस्टरed)
		वापस;

	अगर (!IS_ACCEPTING_CMD(ar) || ar->needs_full_reset)
		ar->क्रमce_usb_reset = true;

	ieee80211_queue_work(ar->hw, &ar->restart_work);

	/*
	 * At this poपूर्णांक, the device instance might have vanished/disabled.
	 * So, करोn't put any code which access the ar9170 काष्ठा
	 * without proper protection.
	 */
पूर्ण

अटल व्योम carl9170_ping_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ar9170 *ar = container_of(work, काष्ठा ar9170, ping_work);
	पूर्णांक err;

	अगर (!IS_STARTED(ar))
		वापस;

	mutex_lock(&ar->mutex);
	err = carl9170_echo_test(ar, 0xdeadbeef);
	अगर (err)
		carl9170_restart(ar, CARL9170_RR_UNRESPONSIVE_DEVICE);
	mutex_unlock(&ar->mutex);
पूर्ण

अटल पूर्णांक carl9170_init_पूर्णांकerface(काष्ठा ar9170 *ar,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_common *common = &ar->common;
	पूर्णांक err;

	अगर (!vअगर) अणु
		WARN_ON_ONCE(IS_STARTED(ar));
		वापस 0;
	पूर्ण

	स_नकल(common->macaddr, vअगर->addr, ETH_ALEN);

	/* We have to fall back to software crypto, whenever
	 * the user choose to participates in an IBSS. HW
	 * offload क्रम IBSS RSN is not supported by this driver.
	 *
	 * NOTE: If the previous मुख्य पूर्णांकerface has alपढ़ोy
	 * disabled hw crypto offload, we have to keep this
	 * previous disable_offload setting as it was.
	 * Altough ideally, we should notअगरy mac80211 and tell
	 * it to क्रमget about any HW crypto offload क्रम now.
	 */
	ar->disable_offload |= ((vअगर->type != NL80211_IFTYPE_STATION) &&
	    (vअगर->type != NL80211_IFTYPE_AP));

	/* The driver used to have P2P GO+CLIENT support,
	 * but since this was dropped and we करोn't know अगर
	 * there are any gremlins lurking in the shaकरोws,
	 * so best we keep HW offload disabled क्रम P2P.
	 */
	ar->disable_offload |= vअगर->p2p;

	ar->rx_software_decryption = ar->disable_offload;

	err = carl9170_set_operating_mode(ar);
	वापस err;
पूर्ण

अटल पूर्णांक carl9170_op_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा carl9170_vअगर_info *vअगर_priv = (व्योम *) vअगर->drv_priv;
	काष्ठा ieee80211_vअगर *मुख्य_vअगर, *old_मुख्य = शून्य;
	काष्ठा ar9170 *ar = hw->priv;
	पूर्णांक vअगर_id = -1, err = 0;

	mutex_lock(&ar->mutex);
	rcu_पढ़ो_lock();
	अगर (vअगर_priv->active) अणु
		/*
		 * Skip the पूर्णांकerface काष्ठाure initialization,
		 * अगर the vअगर survived the _restart call.
		 */
		vअगर_id = vअगर_priv->id;
		vअगर_priv->enable_beacon = false;

		spin_lock_bh(&ar->beacon_lock);
		dev_kमुक्त_skb_any(vअगर_priv->beacon);
		vअगर_priv->beacon = शून्य;
		spin_unlock_bh(&ar->beacon_lock);

		जाओ init;
	पूर्ण

	/* Because the AR9170 HW's MAC doesn't provide full support क्रम
	 * multiple, independent पूर्णांकerfaces [of dअगरferent operation modes].
	 * We have to select ONE मुख्य पूर्णांकerface [मुख्य mode of HW], but we
	 * can have multiple slaves [AKA: entry in the ACK-table].
	 *
	 * The first (from HEAD/TOP) पूर्णांकerface in the ar->vअगर_list is
	 * always the मुख्य पूर्णांकf. All following पूर्णांकfs in this list
	 * are considered to be slave पूर्णांकfs.
	 */
	मुख्य_vअगर = carl9170_get_मुख्य_vअगर(ar);

	अगर (मुख्य_vअगर) अणु
		चयन (मुख्य_vअगर->type) अणु
		हाल NL80211_IFTYPE_STATION:
			अगर (vअगर->type == NL80211_IFTYPE_STATION)
				अवरोध;

			err = -EBUSY;
			rcu_पढ़ो_unlock();

			जाओ unlock;

		हाल NL80211_IFTYPE_MESH_POINT:
		हाल NL80211_IFTYPE_AP:
			अगर ((vअगर->type == NL80211_IFTYPE_STATION) ||
			    (vअगर->type == NL80211_IFTYPE_AP) ||
			    (vअगर->type == NL80211_IFTYPE_MESH_POINT))
				अवरोध;

			err = -EBUSY;
			rcu_पढ़ो_unlock();
			जाओ unlock;

		शेष:
			rcu_पढ़ो_unlock();
			जाओ unlock;
		पूर्ण
	पूर्ण

	vअगर_id = biपंचांगap_find_मुक्त_region(&ar->vअगर_biपंचांगap, ar->fw.vअगर_num, 0);

	अगर (vअगर_id < 0) अणु
		rcu_पढ़ो_unlock();

		err = -ENOSPC;
		जाओ unlock;
	पूर्ण

	BUG_ON(ar->vअगर_priv[vअगर_id].id != vअगर_id);

	vअगर_priv->active = true;
	vअगर_priv->id = vअगर_id;
	vअगर_priv->enable_beacon = false;
	ar->vअगरs++;
	अगर (old_मुख्य) अणु
		/* We end up in here, अगर the मुख्य पूर्णांकerface is being replaced.
		 * Put the new मुख्य पूर्णांकerface at the HEAD of the list and the
		 * previous पूर्णांकeface will स्वतःmatically become second in line.
		 */
		list_add_rcu(&vअगर_priv->list, &ar->vअगर_list);
	पूर्ण अन्यथा अणु
		/* Add new पूर्णांकeface. If the list is empty, it will become the
		 * मुख्य पूर्णांकeface, otherwise it will be slave.
		 */
		list_add_tail_rcu(&vअगर_priv->list, &ar->vअगर_list);
	पूर्ण
	rcu_assign_poपूर्णांकer(ar->vअगर_priv[vअगर_id].vअगर, vअगर);

init:
	मुख्य_vअगर = carl9170_get_मुख्य_vअगर(ar);

	अगर (मुख्य_vअगर == vअगर) अणु
		rcu_assign_poपूर्णांकer(ar->beacon_iter, vअगर_priv);
		rcu_पढ़ो_unlock();

		अगर (old_मुख्य) अणु
			काष्ठा carl9170_vअगर_info *old_मुख्य_priv =
				(व्योम *) old_मुख्य->drv_priv;
			/* करोwngrade old मुख्य पूर्णांकf to slave पूर्णांकf.
			 * NOTE: We are no दीर्घer under rcu_पढ़ो_lock.
			 * But we are still holding ar->mutex, so the
			 * vअगर data [id, addr] is safe.
			 */
			err = carl9170_mod_भव_mac(ar, old_मुख्य_priv->id,
						       old_मुख्य->addr);
			अगर (err)
				जाओ unlock;
		पूर्ण

		err = carl9170_init_पूर्णांकerface(ar, vअगर);
		अगर (err)
			जाओ unlock;
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_unlock();
		err = carl9170_mod_भव_mac(ar, vअगर_id, vअगर->addr);

		अगर (err)
			जाओ unlock;
	पूर्ण

	अगर (ar->fw.tx_seq_table) अणु
		err = carl9170_ग_लिखो_reg(ar, ar->fw.tx_seq_table + vअगर_id * 4,
					 0);
		अगर (err)
			जाओ unlock;
	पूर्ण

unlock:
	अगर (err && (vअगर_id >= 0)) अणु
		vअगर_priv->active = false;
		biपंचांगap_release_region(&ar->vअगर_biपंचांगap, vअगर_id, 0);
		ar->vअगरs--;
		RCU_INIT_POINTER(ar->vअगर_priv[vअगर_id].vअगर, शून्य);
		list_del_rcu(&vअगर_priv->list);
		mutex_unlock(&ar->mutex);
		synchronize_rcu();
	पूर्ण अन्यथा अणु
		अगर (ar->vअगरs > 1)
			ar->ps.off_override |= PS_OFF_VIF;

		mutex_unlock(&ar->mutex);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम carl9170_op_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा carl9170_vअगर_info *vअगर_priv = (व्योम *) vअगर->drv_priv;
	काष्ठा ieee80211_vअगर *मुख्य_vअगर;
	काष्ठा ar9170 *ar = hw->priv;
	अचिन्हित पूर्णांक id;

	mutex_lock(&ar->mutex);

	अगर (WARN_ON_ONCE(!vअगर_priv->active))
		जाओ unlock;

	ar->vअगरs--;

	rcu_पढ़ो_lock();
	मुख्य_vअगर = carl9170_get_मुख्य_vअगर(ar);

	id = vअगर_priv->id;

	vअगर_priv->active = false;
	WARN_ON(vअगर_priv->enable_beacon);
	vअगर_priv->enable_beacon = false;
	list_del_rcu(&vअगर_priv->list);
	RCU_INIT_POINTER(ar->vअगर_priv[id].vअगर, शून्य);

	अगर (vअगर == मुख्य_vअगर) अणु
		rcu_पढ़ो_unlock();

		अगर (ar->vअगरs) अणु
			WARN_ON(carl9170_init_पूर्णांकerface(ar,
					carl9170_get_मुख्य_vअगर(ar)));
		पूर्ण अन्यथा अणु
			carl9170_set_operating_mode(ar);
		पूर्ण
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_unlock();

		WARN_ON(carl9170_mod_भव_mac(ar, id, शून्य));
	पूर्ण

	carl9170_update_beacon(ar, false);
	carl9170_flush_cab(ar, id);

	spin_lock_bh(&ar->beacon_lock);
	dev_kमुक्त_skb_any(vअगर_priv->beacon);
	vअगर_priv->beacon = शून्य;
	spin_unlock_bh(&ar->beacon_lock);

	biपंचांगap_release_region(&ar->vअगर_biपंचांगap, id, 0);

	carl9170_set_beacon_समयrs(ar);

	अगर (ar->vअगरs == 1)
		ar->ps.off_override &= ~PS_OFF_VIF;

unlock:
	mutex_unlock(&ar->mutex);

	synchronize_rcu();
पूर्ण

व्योम carl9170_ps_check(काष्ठा ar9170 *ar)
अणु
	ieee80211_queue_work(ar->hw, &ar->ps_work);
पूर्ण

/* caller must hold ar->mutex */
अटल पूर्णांक carl9170_ps_update(काष्ठा ar9170 *ar)
अणु
	bool ps = false;
	पूर्णांक err = 0;

	अगर (!ar->ps.off_override)
		ps = (ar->hw->conf.flags & IEEE80211_CONF_PS);

	अगर (ps != ar->ps.state) अणु
		err = carl9170_घातersave(ar, ps);
		अगर (err)
			वापस err;

		अगर (ar->ps.state && !ps) अणु
			ar->ps.sleep_ms = jअगरfies_to_msecs(jअगरfies -
				ar->ps.last_action);
		पूर्ण

		अगर (ps)
			ar->ps.last_slept = jअगरfies;

		ar->ps.last_action = jअगरfies;
		ar->ps.state = ps;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम carl9170_ps_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ar9170 *ar = container_of(work, काष्ठा ar9170,
					 ps_work);
	mutex_lock(&ar->mutex);
	अगर (IS_STARTED(ar))
		WARN_ON_ONCE(carl9170_ps_update(ar) != 0);
	mutex_unlock(&ar->mutex);
पूर्ण

अटल पूर्णांक carl9170_update_survey(काष्ठा ar9170 *ar, bool flush, bool noise)
अणु
	पूर्णांक err;

	अगर (noise) अणु
		err = carl9170_get_noiseन्यूनमान(ar);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (ar->fw.hw_counters) अणु
		err = carl9170_collect_tally(ar);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (flush)
		स_रखो(&ar->tally, 0, माप(ar->tally));

	वापस 0;
पूर्ण

अटल व्योम carl9170_stat_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ar9170 *ar = container_of(work, काष्ठा ar9170, stat_work.work);
	पूर्णांक err;

	mutex_lock(&ar->mutex);
	err = carl9170_update_survey(ar, false, true);
	mutex_unlock(&ar->mutex);

	अगर (err)
		वापस;

	ieee80211_queue_delayed_work(ar->hw, &ar->stat_work,
		round_jअगरfies(msecs_to_jअगरfies(CARL9170_STAT_WORK)));
पूर्ण

अटल पूर्णांक carl9170_op_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा ar9170 *ar = hw->priv;
	पूर्णांक err = 0;

	mutex_lock(&ar->mutex);
	अगर (changed & IEEE80211_CONF_CHANGE_LISTEN_INTERVAL) अणु
		/* TODO */
		err = 0;
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_PS) अणु
		err = carl9170_ps_update(ar);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_SMPS) अणु
		/* TODO */
		err = 0;
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		क्रमागत nl80211_channel_type channel_type =
			cfg80211_get_chandef_type(&hw->conf.chandef);

		/* adjust slot समय क्रम 5 GHz */
		err = carl9170_set_slot_समय(ar);
		अगर (err)
			जाओ out;

		err = carl9170_update_survey(ar, true, false);
		अगर (err)
			जाओ out;

		err = carl9170_set_channel(ar, hw->conf.chandef.chan,
					   channel_type);
		अगर (err)
			जाओ out;

		err = carl9170_update_survey(ar, false, true);
		अगर (err)
			जाओ out;

		err = carl9170_set_dyn_sअगरs_ack(ar);
		अगर (err)
			जाओ out;

		err = carl9170_set_rts_cts_rate(ar);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_POWER) अणु
		err = carl9170_set_mac_tpc(ar, ar->hw->conf.chandef.chan);
		अगर (err)
			जाओ out;
	पूर्ण

out:
	mutex_unlock(&ar->mutex);
	वापस err;
पूर्ण

अटल u64 carl9170_op_prepare_multicast(काष्ठा ieee80211_hw *hw,
					 काष्ठा netdev_hw_addr_list *mc_list)
अणु
	काष्ठा netdev_hw_addr *ha;
	u64 mchash;

	/* always get broadcast frames */
	mchash = 1ULL << (0xff >> 2);

	netdev_hw_addr_list_क्रम_each(ha, mc_list)
		mchash |= 1ULL << (ha->addr[5] >> 2);

	वापस mchash;
पूर्ण

अटल व्योम carl9170_op_configure_filter(काष्ठा ieee80211_hw *hw,
					 अचिन्हित पूर्णांक changed_flags,
					 अचिन्हित पूर्णांक *new_flags,
					 u64 multicast)
अणु
	काष्ठा ar9170 *ar = hw->priv;

	/* mask supported flags */
	*new_flags &= FIF_ALLMULTI | ar->rx_filter_caps;

	अगर (!IS_ACCEPTING_CMD(ar))
		वापस;

	mutex_lock(&ar->mutex);

	ar->filter_state = *new_flags;
	/*
	 * We can support more by setting the snअगरfer bit and
	 * then checking the error flags, later.
	 */

	अगर (*new_flags & FIF_ALLMULTI)
		multicast = ~0ULL;

	अगर (multicast != ar->cur_mc_hash)
		WARN_ON(carl9170_update_multicast(ar, multicast));

	अगर (changed_flags & FIF_OTHER_BSS) अणु
		ar->snअगरfer_enabled = !!(*new_flags & FIF_OTHER_BSS);

		WARN_ON(carl9170_set_operating_mode(ar));
	पूर्ण

	अगर (ar->fw.rx_filter && changed_flags & ar->rx_filter_caps) अणु
		u32 rx_filter = 0;

		अगर (!ar->fw.ba_filter)
			rx_filter |= CARL9170_RX_FILTER_CTL_OTHER;

		अगर (!(*new_flags & (FIF_FCSFAIL | FIF_PLCPFAIL)))
			rx_filter |= CARL9170_RX_FILTER_BAD;

		अगर (!(*new_flags & FIF_CONTROL))
			rx_filter |= CARL9170_RX_FILTER_CTL_OTHER;

		अगर (!(*new_flags & FIF_PSPOLL))
			rx_filter |= CARL9170_RX_FILTER_CTL_PSPOLL;

		अगर (!(*new_flags & FIF_OTHER_BSS)) अणु
			rx_filter |= CARL9170_RX_FILTER_OTHER_RA;
			rx_filter |= CARL9170_RX_FILTER_DECRY_FAIL;
		पूर्ण

		WARN_ON(carl9170_rx_filter(ar, rx_filter));
	पूर्ण

	mutex_unlock(&ar->mutex);
पूर्ण


अटल व्योम carl9170_op_bss_info_changed(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_vअगर *vअगर,
					 काष्ठा ieee80211_bss_conf *bss_conf,
					 u32 changed)
अणु
	काष्ठा ar9170 *ar = hw->priv;
	काष्ठा ath_common *common = &ar->common;
	पूर्णांक err = 0;
	काष्ठा carl9170_vअगर_info *vअगर_priv;
	काष्ठा ieee80211_vअगर *मुख्य_vअगर;

	mutex_lock(&ar->mutex);
	vअगर_priv = (व्योम *) vअगर->drv_priv;
	मुख्य_vअगर = carl9170_get_मुख्य_vअगर(ar);
	अगर (WARN_ON(!मुख्य_vअगर))
		जाओ out;

	अगर (changed & BSS_CHANGED_BEACON_ENABLED) अणु
		काष्ठा carl9170_vअगर_info *iter;
		पूर्णांक i = 0;

		vअगर_priv->enable_beacon = bss_conf->enable_beacon;
		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(iter, &ar->vअगर_list, list) अणु
			अगर (iter->active && iter->enable_beacon)
				i++;

		पूर्ण
		rcu_पढ़ो_unlock();

		ar->beacon_enabled = i;
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON) अणु
		err = carl9170_update_beacon(ar, false);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (changed & (BSS_CHANGED_BEACON_ENABLED | BSS_CHANGED_BEACON |
		       BSS_CHANGED_BEACON_INT)) अणु

		अगर (मुख्य_vअगर != vअगर) अणु
			bss_conf->beacon_पूर्णांक = मुख्य_vअगर->bss_conf.beacon_पूर्णांक;
			bss_conf->dtim_period = मुख्य_vअगर->bss_conf.dtim_period;
		पूर्ण

		/*
		 * Thereक्रमe a hard limit क्रम the broadcast traffic should
		 * prevent false alarms.
		 */
		अगर (vअगर->type != NL80211_IFTYPE_STATION &&
		    (bss_conf->beacon_पूर्णांक * bss_conf->dtim_period >=
		     (CARL9170_QUEUE_STUCK_TIMEOUT / 2))) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		err = carl9170_set_beacon_समयrs(ar);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (changed & BSS_CHANGED_HT) अणु
		/* TODO */
		err = 0;
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (मुख्य_vअगर != vअगर)
		जाओ out;

	/*
	 * The following settings can only be changed by the
	 * master पूर्णांकerface.
	 */

	अगर (changed & BSS_CHANGED_BSSID) अणु
		स_नकल(common->curbssid, bss_conf->bssid, ETH_ALEN);
		err = carl9170_set_operating_mode(ar);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		ar->common.curaid = bss_conf->aid;
		err = carl9170_set_beacon_समयrs(ar);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		err = carl9170_set_slot_समय(ar);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (changed & BSS_CHANGED_BASIC_RATES) अणु
		err = carl9170_set_mac_rates(ar);
		अगर (err)
			जाओ out;
	पूर्ण

out:
	WARN_ON_ONCE(err && IS_STARTED(ar));
	mutex_unlock(&ar->mutex);
पूर्ण

अटल u64 carl9170_op_get_tsf(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ar9170 *ar = hw->priv;
	काष्ठा carl9170_tsf_rsp tsf;
	पूर्णांक err;

	mutex_lock(&ar->mutex);
	err = carl9170_exec_cmd(ar, CARL9170_CMD_READ_TSF,
				0, शून्य, माप(tsf), &tsf);
	mutex_unlock(&ar->mutex);
	अगर (WARN_ON(err))
		वापस 0;

	वापस le64_to_cpu(tsf.tsf_64);
पूर्ण

अटल पूर्णांक carl9170_op_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ieee80211_sta *sta,
			       काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा ar9170 *ar = hw->priv;
	पूर्णांक err = 0, i;
	u8 ktype;

	अगर (ar->disable_offload || !vअगर)
		वापस -EOPNOTSUPP;

	/* Fall back to software encryption whenever the driver is connected
	 * to more than one network.
	 *
	 * This is very unक्रमtunate, because some machines cannot handle
	 * the high througput speed in 802.11n networks.
	 */

	अगर (!is_मुख्य_vअगर(ar, vअगर)) अणु
		mutex_lock(&ar->mutex);
		जाओ err_softw;
	पूर्ण

	/*
	 * While the hardware supports *catch-all* key, क्रम offloading
	 * group-key en-/de-cryption. The way of how the hardware
	 * decides which keyId maps to which key, reमुख्यs a mystery...
	 */
	अगर ((vअगर->type != NL80211_IFTYPE_STATION &&
	     vअगर->type != NL80211_IFTYPE_ADHOC) &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		वापस -EOPNOTSUPP;

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
		ktype = AR9170_ENC_ALG_WEP64;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP104:
		ktype = AR9170_ENC_ALG_WEP128;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		ktype = AR9170_ENC_ALG_TKIP;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		ktype = AR9170_ENC_ALG_AESCCMP;
		key->flags |= IEEE80211_KEY_FLAG_SW_MGMT_TX;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	mutex_lock(&ar->mutex);
	अगर (cmd == SET_KEY) अणु
		अगर (!IS_STARTED(ar)) अणु
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		अगर (!(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)) अणु
			sta = शून्य;

			i = 64 + key->keyidx;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < 64; i++)
				अगर (!(ar->usedkeys & BIT(i)))
					अवरोध;
			अगर (i == 64)
				जाओ err_softw;
		पूर्ण

		key->hw_key_idx = i;

		err = carl9170_upload_key(ar, i, sta ? sta->addr : शून्य,
					  ktype, 0, key->key,
					  min_t(u8, 16, key->keylen));
		अगर (err)
			जाओ out;

		अगर (key->cipher == WLAN_CIPHER_SUITE_TKIP) अणु
			err = carl9170_upload_key(ar, i, sta ? sta->addr :
						  शून्य, ktype, 1,
						  key->key + 16, 16);
			अगर (err)
				जाओ out;

			/*
			 * hardware is not capable generating MMIC
			 * of fragmented frames!
			 */
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
		पूर्ण

		अगर (i < 64)
			ar->usedkeys |= BIT(i);

		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
	पूर्ण अन्यथा अणु
		अगर (!IS_STARTED(ar)) अणु
			/* The device is gone... together with the key ;-) */
			err = 0;
			जाओ out;
		पूर्ण

		अगर (key->hw_key_idx < 64) अणु
			ar->usedkeys &= ~BIT(key->hw_key_idx);
		पूर्ण अन्यथा अणु
			err = carl9170_upload_key(ar, key->hw_key_idx, शून्य,
						  AR9170_ENC_ALG_NONE, 0,
						  शून्य, 0);
			अगर (err)
				जाओ out;

			अगर (key->cipher == WLAN_CIPHER_SUITE_TKIP) अणु
				err = carl9170_upload_key(ar, key->hw_key_idx,
							  शून्य,
							  AR9170_ENC_ALG_NONE,
							  1, शून्य, 0);
				अगर (err)
					जाओ out;
			पूर्ण

		पूर्ण

		err = carl9170_disable_key(ar, key->hw_key_idx);
		अगर (err)
			जाओ out;
	पूर्ण

out:
	mutex_unlock(&ar->mutex);
	वापस err;

err_softw:
	अगर (!ar->rx_software_decryption) अणु
		ar->rx_software_decryption = true;
		carl9170_set_operating_mode(ar);
	पूर्ण
	mutex_unlock(&ar->mutex);
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक carl9170_op_sta_add(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा carl9170_sta_info *sta_info = (व्योम *) sta->drv_priv;
	अचिन्हित पूर्णांक i;

	atomic_set(&sta_info->pending_frames, 0);

	अगर (sta->ht_cap.ht_supported) अणु
		अगर (sta->ht_cap.ampdu_density > 6) अणु
			/*
			 * HW करोes support 16us AMPDU density.
			 * No HT-Xmit क्रम station.
			 */

			वापस 0;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(sta_info->agg); i++)
			RCU_INIT_POINTER(sta_info->agg[i], शून्य);

		sta_info->ampdu_max_len = 1 << (3 + sta->ht_cap.ampdu_factor);
		sta_info->ht_sta = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक carl9170_op_sta_हटाओ(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ar9170 *ar = hw->priv;
	काष्ठा carl9170_sta_info *sta_info = (व्योम *) sta->drv_priv;
	अचिन्हित पूर्णांक i;
	bool cleanup = false;

	अगर (sta->ht_cap.ht_supported) अणु

		sta_info->ht_sta = false;

		rcu_पढ़ो_lock();
		क्रम (i = 0; i < ARRAY_SIZE(sta_info->agg); i++) अणु
			काष्ठा carl9170_sta_tid *tid_info;

			tid_info = rcu_dereference(sta_info->agg[i]);
			RCU_INIT_POINTER(sta_info->agg[i], शून्य);

			अगर (!tid_info)
				जारी;

			spin_lock_bh(&ar->tx_ampdu_list_lock);
			अगर (tid_info->state > CARL9170_TID_STATE_SHUTDOWN)
				tid_info->state = CARL9170_TID_STATE_SHUTDOWN;
			spin_unlock_bh(&ar->tx_ampdu_list_lock);
			cleanup = true;
		पूर्ण
		rcu_पढ़ो_unlock();

		अगर (cleanup)
			carl9170_ampdu_gc(ar);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक carl9170_op_conf_tx(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर, u16 queue,
			       स्थिर काष्ठा ieee80211_tx_queue_params *param)
अणु
	काष्ठा ar9170 *ar = hw->priv;
	पूर्णांक ret;

	mutex_lock(&ar->mutex);
	स_नकल(&ar->edcf[ar9170_qmap(queue)], param, माप(*param));
	ret = carl9170_set_qos(ar);
	mutex_unlock(&ar->mutex);
	वापस ret;
पूर्ण

अटल व्योम carl9170_ampdu_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ar9170 *ar = container_of(work, काष्ठा ar9170,
					 ampdu_work);

	अगर (!IS_STARTED(ar))
		वापस;

	mutex_lock(&ar->mutex);
	carl9170_ampdu_gc(ar);
	mutex_unlock(&ar->mutex);
पूर्ण

अटल पूर्णांक carl9170_op_ampdu_action(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u16 *ssn = &params->ssn;
	काष्ठा ar9170 *ar = hw->priv;
	काष्ठा carl9170_sta_info *sta_info = (व्योम *) sta->drv_priv;
	काष्ठा carl9170_sta_tid *tid_info;

	अगर (modparam_noht)
		वापस -EOPNOTSUPP;

	चयन (action) अणु
	हाल IEEE80211_AMPDU_TX_START:
		अगर (!sta_info->ht_sta)
			वापस -EOPNOTSUPP;

		tid_info = kzalloc(माप(काष्ठा carl9170_sta_tid),
				   GFP_ATOMIC);
		अगर (!tid_info)
			वापस -ENOMEM;

		tid_info->hsn = tid_info->bsn = tid_info->snx = (*ssn);
		tid_info->state = CARL9170_TID_STATE_PROGRESS;
		tid_info->tid = tid;
		tid_info->max = sta_info->ampdu_max_len;
		tid_info->sta = sta;
		tid_info->vअगर = vअगर;

		INIT_LIST_HEAD(&tid_info->list);
		INIT_LIST_HEAD(&tid_info->पंचांगp_list);
		skb_queue_head_init(&tid_info->queue);
		spin_lock_init(&tid_info->lock);

		spin_lock_bh(&ar->tx_ampdu_list_lock);
		ar->tx_ampdu_list_len++;
		list_add_tail_rcu(&tid_info->list, &ar->tx_ampdu_list);
		rcu_assign_poपूर्णांकer(sta_info->agg[tid], tid_info);
		spin_unlock_bh(&ar->tx_ampdu_list_lock);

		वापस IEEE80211_AMPDU_TX_START_IMMEDIATE;

	हाल IEEE80211_AMPDU_TX_STOP_CONT:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		rcu_पढ़ो_lock();
		tid_info = rcu_dereference(sta_info->agg[tid]);
		अगर (tid_info) अणु
			spin_lock_bh(&ar->tx_ampdu_list_lock);
			अगर (tid_info->state > CARL9170_TID_STATE_SHUTDOWN)
				tid_info->state = CARL9170_TID_STATE_SHUTDOWN;
			spin_unlock_bh(&ar->tx_ampdu_list_lock);
		पूर्ण

		RCU_INIT_POINTER(sta_info->agg[tid], शून्य);
		rcu_पढ़ो_unlock();

		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		ieee80211_queue_work(ar->hw, &ar->ampdu_work);
		अवरोध;

	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		rcu_पढ़ो_lock();
		tid_info = rcu_dereference(sta_info->agg[tid]);

		sta_info->stats[tid].clear = true;
		sta_info->stats[tid].req = false;

		अगर (tid_info) अणु
			biपंचांगap_zero(tid_info->biपंचांगap, CARL9170_BAW_SIZE);
			tid_info->state = CARL9170_TID_STATE_IDLE;
		पूर्ण
		rcu_पढ़ो_unlock();

		अगर (WARN_ON_ONCE(!tid_info))
			वापस -EFAULT;

		अवरोध;

	हाल IEEE80211_AMPDU_RX_START:
	हाल IEEE80211_AMPDU_RX_STOP:
		/* Handled by hardware */
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CARL9170_WPC
अटल पूर्णांक carl9170_रेजिस्टर_wps_button(काष्ठा ar9170 *ar)
अणु
	काष्ठा input_dev *input;
	पूर्णांक err;

	अगर (!(ar->features & CARL9170_WPS_BUTTON))
		वापस 0;

	input = input_allocate_device();
	अगर (!input)
		वापस -ENOMEM;

	snम_लिखो(ar->wps.name, माप(ar->wps.name), "%s WPS Button",
		 wiphy_name(ar->hw->wiphy));

	snम_लिखो(ar->wps.phys, माप(ar->wps.phys),
		 "ieee80211/%s/input0", wiphy_name(ar->hw->wiphy));

	input->name = ar->wps.name;
	input->phys = ar->wps.phys;
	input->id.bustype = BUS_USB;
	input->dev.parent = &ar->hw->wiphy->dev;

	input_set_capability(input, EV_KEY, KEY_WPS_BUTTON);

	err = input_रेजिस्टर_device(input);
	अगर (err) अणु
		input_मुक्त_device(input);
		वापस err;
	पूर्ण

	ar->wps.pbc = input;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_CARL9170_WPC */

#अगर_घोषित CONFIG_CARL9170_HWRNG
अटल पूर्णांक carl9170_rng_get(काष्ठा ar9170 *ar)
अणु

#घोषणा RW	(CARL9170_MAX_CMD_PAYLOAD_LEN / माप(u32))
#घोषणा RB	(CARL9170_MAX_CMD_PAYLOAD_LEN)

	अटल स्थिर __le32 rng_load[RW] = अणु
		[0 ... (RW - 1)] = cpu_to_le32(AR9170_RAND_REG_NUM)पूर्ण;

	u32 buf[RW];

	अचिन्हित पूर्णांक i, off = 0, transfer, count;
	पूर्णांक err;

	BUILD_BUG_ON(RB > CARL9170_MAX_CMD_PAYLOAD_LEN);

	अगर (!IS_ACCEPTING_CMD(ar) || !ar->rng.initialized)
		वापस -EAGAIN;

	count = ARRAY_SIZE(ar->rng.cache);
	जबतक (count) अणु
		err = carl9170_exec_cmd(ar, CARL9170_CMD_RREG,
					RB, (u8 *) rng_load,
					RB, (u8 *) buf);
		अगर (err)
			वापस err;

		transfer = min_t(अचिन्हित पूर्णांक, count, RW);
		क्रम (i = 0; i < transfer; i++)
			ar->rng.cache[off + i] = buf[i];

		off += transfer;
		count -= transfer;
	पूर्ण

	ar->rng.cache_idx = 0;

#अघोषित RW
#अघोषित RB
	वापस 0;
पूर्ण

अटल पूर्णांक carl9170_rng_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	काष्ठा ar9170 *ar = (काष्ठा ar9170 *)rng->priv;
	पूर्णांक ret = -EIO;

	mutex_lock(&ar->mutex);
	अगर (ar->rng.cache_idx >= ARRAY_SIZE(ar->rng.cache)) अणु
		ret = carl9170_rng_get(ar);
		अगर (ret) अणु
			mutex_unlock(&ar->mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	*data = ar->rng.cache[ar->rng.cache_idx++];
	mutex_unlock(&ar->mutex);

	वापस माप(u16);
पूर्ण

अटल व्योम carl9170_unरेजिस्टर_hwrng(काष्ठा ar9170 *ar)
अणु
	अगर (ar->rng.initialized) अणु
		hwrng_unरेजिस्टर(&ar->rng.rng);
		ar->rng.initialized = false;
	पूर्ण
पूर्ण

अटल पूर्णांक carl9170_रेजिस्टर_hwrng(काष्ठा ar9170 *ar)
अणु
	पूर्णांक err;

	snम_लिखो(ar->rng.name, ARRAY_SIZE(ar->rng.name),
		 "%s_%s", KBUILD_MODNAME, wiphy_name(ar->hw->wiphy));
	ar->rng.rng.name = ar->rng.name;
	ar->rng.rng.data_पढ़ो = carl9170_rng_पढ़ो;
	ar->rng.rng.priv = (अचिन्हित दीर्घ)ar;

	अगर (WARN_ON(ar->rng.initialized))
		वापस -EALREADY;

	err = hwrng_रेजिस्टर(&ar->rng.rng);
	अगर (err) अणु
		dev_err(&ar->udev->dev, "Failed to register the random "
			"number generator (%d)\n", err);
		वापस err;
	पूर्ण

	ar->rng.initialized = true;

	err = carl9170_rng_get(ar);
	अगर (err) अणु
		carl9170_unरेजिस्टर_hwrng(ar);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_CARL9170_HWRNG */

अटल पूर्णांक carl9170_op_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
				काष्ठा survey_info *survey)
अणु
	काष्ठा ar9170 *ar = hw->priv;
	काष्ठा ieee80211_channel *chan;
	काष्ठा ieee80211_supported_band *band;
	पूर्णांक err, b, i;

	chan = ar->channel;
	अगर (!chan)
		वापस -ENODEV;

	अगर (idx == chan->hw_value) अणु
		mutex_lock(&ar->mutex);
		err = carl9170_update_survey(ar, false, true);
		mutex_unlock(&ar->mutex);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (b = 0; b < NUM_NL80211_BANDS; b++) अणु
		band = ar->hw->wiphy->bands[b];

		अगर (!band)
			जारी;

		क्रम (i = 0; i < band->n_channels; i++) अणु
			अगर (band->channels[i].hw_value == idx) अणु
				chan = &band->channels[i];
				जाओ found;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस -ENOENT;

found:
	स_नकल(survey, &ar->survey[idx], माप(*survey));

	survey->channel = chan;
	survey->filled = SURVEY_INFO_NOISE_DBM;

	अगर (ar->channel == chan)
		survey->filled |= SURVEY_INFO_IN_USE;

	अगर (ar->fw.hw_counters) अणु
		survey->filled |= SURVEY_INFO_TIME |
				  SURVEY_INFO_TIME_BUSY |
				  SURVEY_INFO_TIME_TX;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम carl9170_op_flush(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      u32 queues, bool drop)
अणु
	काष्ठा ar9170 *ar = hw->priv;
	अचिन्हित पूर्णांक vid;

	mutex_lock(&ar->mutex);
	क्रम_each_set_bit(vid, &ar->vअगर_biपंचांगap, ar->fw.vअगर_num)
		carl9170_flush_cab(ar, vid);

	carl9170_flush(ar, drop);
	mutex_unlock(&ar->mutex);
पूर्ण

अटल पूर्णांक carl9170_op_get_stats(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा ar9170 *ar = hw->priv;

	स_रखो(stats, 0, माप(*stats));
	stats->करोt11ACKFailureCount = ar->tx_ack_failures;
	stats->करोt11FCSErrorCount = ar->tx_fcs_errors;
	वापस 0;
पूर्ण

अटल व्योम carl9170_op_sta_notअगरy(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   क्रमागत sta_notअगरy_cmd cmd,
				   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा carl9170_sta_info *sta_info = (व्योम *) sta->drv_priv;

	चयन (cmd) अणु
	हाल STA_NOTIFY_SLEEP:
		sta_info->sleeping = true;
		अगर (atomic_पढ़ो(&sta_info->pending_frames))
			ieee80211_sta_block_awake(hw, sta, true);
		अवरोध;

	हाल STA_NOTIFY_AWAKE:
		sta_info->sleeping = false;
		अवरोध;
	पूर्ण
पूर्ण

अटल bool carl9170_tx_frames_pending(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ar9170 *ar = hw->priv;

	वापस !!atomic_पढ़ो(&ar->tx_total_queued);
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops carl9170_ops = अणु
	.start			= carl9170_op_start,
	.stop			= carl9170_op_stop,
	.tx			= carl9170_op_tx,
	.flush			= carl9170_op_flush,
	.add_पूर्णांकerface		= carl9170_op_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= carl9170_op_हटाओ_पूर्णांकerface,
	.config			= carl9170_op_config,
	.prepare_multicast	= carl9170_op_prepare_multicast,
	.configure_filter	= carl9170_op_configure_filter,
	.conf_tx		= carl9170_op_conf_tx,
	.bss_info_changed	= carl9170_op_bss_info_changed,
	.get_tsf		= carl9170_op_get_tsf,
	.set_key		= carl9170_op_set_key,
	.sta_add		= carl9170_op_sta_add,
	.sta_हटाओ		= carl9170_op_sta_हटाओ,
	.sta_notअगरy		= carl9170_op_sta_notअगरy,
	.get_survey		= carl9170_op_get_survey,
	.get_stats		= carl9170_op_get_stats,
	.ampdu_action		= carl9170_op_ampdu_action,
	.tx_frames_pending	= carl9170_tx_frames_pending,
पूर्ण;

व्योम *carl9170_alloc(माप_प्रकार priv_size)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा ar9170 *ar;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	/*
	 * this buffer is used क्रम rx stream reस्थिरruction.
	 * Under heavy load this device (or the transport layer?)
	 * tends to split the streams पूर्णांकo separate rx descriptors.
	 */

	skb = __dev_alloc_skb(AR9170_RX_STREAM_MAX_SIZE, GFP_KERNEL);
	अगर (!skb)
		जाओ err_nomem;

	hw = ieee80211_alloc_hw(priv_size, &carl9170_ops);
	अगर (!hw)
		जाओ err_nomem;

	ar = hw->priv;
	ar->hw = hw;
	ar->rx_failover = skb;

	स_रखो(&ar->rx_plcp, 0, माप(काष्ठा ar9170_rx_head));
	ar->rx_has_plcp = false;

	/*
	 * Here's a hidden pitfall!
	 *
	 * All 4 AC queues work perfectly well under _legacy_ operation.
	 * However as soon as aggregation is enabled, the traffic flow
	 * माला_लो very bumpy. Thereक्रमe we have to _चयन_ to a
	 * software AC with a single HW queue.
	 */
	hw->queues = __AR9170_NUM_TXQ;

	mutex_init(&ar->mutex);
	spin_lock_init(&ar->beacon_lock);
	spin_lock_init(&ar->cmd_lock);
	spin_lock_init(&ar->tx_stats_lock);
	spin_lock_init(&ar->tx_ampdu_list_lock);
	spin_lock_init(&ar->mem_lock);
	spin_lock_init(&ar->state_lock);
	atomic_set(&ar->pending_restarts, 0);
	ar->vअगरs = 0;
	क्रम (i = 0; i < ar->hw->queues; i++) अणु
		skb_queue_head_init(&ar->tx_status[i]);
		skb_queue_head_init(&ar->tx_pending[i]);

		INIT_LIST_HEAD(&ar->bar_list[i]);
		spin_lock_init(&ar->bar_list_lock[i]);
	पूर्ण
	INIT_WORK(&ar->ps_work, carl9170_ps_work);
	INIT_WORK(&ar->ping_work, carl9170_ping_work);
	INIT_WORK(&ar->restart_work, carl9170_restart_work);
	INIT_WORK(&ar->ampdu_work, carl9170_ampdu_work);
	INIT_DELAYED_WORK(&ar->stat_work, carl9170_stat_work);
	INIT_DELAYED_WORK(&ar->tx_janitor, carl9170_tx_janitor);
	INIT_LIST_HEAD(&ar->tx_ampdu_list);
	rcu_assign_poपूर्णांकer(ar->tx_ampdu_iter,
			   (काष्ठा carl9170_sta_tid *) &ar->tx_ampdu_list);

	biपंचांगap_zero(&ar->vअगर_biपंचांगap, ar->fw.vअगर_num);
	INIT_LIST_HEAD(&ar->vअगर_list);
	init_completion(&ar->tx_flush);

	/* firmware decides which modes we support */
	hw->wiphy->पूर्णांकerface_modes = 0;

	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, MFP_CAPABLE);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, SUPPORTS_PS);
	ieee80211_hw_set(hw, PS_शून्यFUNC_STACK);
	ieee80211_hw_set(hw, NEED_DTIM_BEFORE_ASSOC);
	ieee80211_hw_set(hw, SUPPORTS_RC_TABLE);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, SUPPORTS_HT_CCK_RATES);

	अगर (!modparam_noht) अणु
		/*
		 * see the comment above, why we allow the user
		 * to disable HT by a module parameter.
		 */
		ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	पूर्ण

	hw->extra_tx_headroom = माप(काष्ठा _carl9170_tx_superframe);
	hw->sta_data_size = माप(काष्ठा carl9170_sta_info);
	hw->vअगर_data_size = माप(काष्ठा carl9170_vअगर_info);

	hw->max_rates = CARL9170_TX_MAX_RATES;
	hw->max_rate_tries = CARL9170_TX_USER_RATE_TRIES;

	क्रम (i = 0; i < ARRAY_SIZE(ar->noise); i++)
		ar->noise[i] = -95; /* ATH_DEFAULT_NOISE_FLOOR */

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	वापस ar;

err_nomem:
	kमुक्त_skb(skb);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल पूर्णांक carl9170_पढ़ो_eeprom(काष्ठा ar9170 *ar)
अणु
#घोषणा RW	8	/* number of words to पढ़ो at once */
#घोषणा RB	(माप(u32) * RW)
	u8 *eeprom = (व्योम *)&ar->eeprom;
	__le32 offsets[RW];
	पूर्णांक i, j, err;

	BUILD_BUG_ON(माप(ar->eeprom) & 3);

	BUILD_BUG_ON(RB > CARL9170_MAX_CMD_LEN - 4);
#अगर_अघोषित __CHECKER__
	/* करोn't want to handle trailing reमुख्यs */
	BUILD_BUG_ON(माप(ar->eeprom) % RB);
#पूर्ण_अगर

	क्रम (i = 0; i < माप(ar->eeprom) / RB; i++) अणु
		क्रम (j = 0; j < RW; j++)
			offsets[j] = cpu_to_le32(AR9170_EEPROM_START +
						 RB * i + 4 * j);

		err = carl9170_exec_cmd(ar, CARL9170_CMD_RREG,
					RB, (u8 *) &offsets,
					RB, eeprom + RB * i);
		अगर (err)
			वापस err;
	पूर्ण

#अघोषित RW
#अघोषित RB
	वापस 0;
पूर्ण

अटल पूर्णांक carl9170_parse_eeprom(काष्ठा ar9170 *ar)
अणु
	काष्ठा ath_regulatory *regulatory = &ar->common.regulatory;
	अचिन्हित पूर्णांक rx_streams, tx_streams, tx_params = 0;
	पूर्णांक bands = 0;
	पूर्णांक chans = 0;

	अगर (ar->eeprom.length == cpu_to_le16(0xffff))
		वापस -ENODATA;

	rx_streams = hweight8(ar->eeprom.rx_mask);
	tx_streams = hweight8(ar->eeprom.tx_mask);

	अगर (rx_streams != tx_streams) अणु
		tx_params = IEEE80211_HT_MCS_TX_RX_DIFF;

		WARN_ON(!(tx_streams >= 1 && tx_streams <=
			IEEE80211_HT_MCS_TX_MAX_STREAMS));

		tx_params = (tx_streams - 1) <<
			    IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT;

		carl9170_band_2GHz.ht_cap.mcs.tx_params |= tx_params;
		carl9170_band_5GHz.ht_cap.mcs.tx_params |= tx_params;
	पूर्ण

	अगर (ar->eeprom.operating_flags & AR9170_OPFLAG_2GHZ) अणु
		ar->hw->wiphy->bands[NL80211_BAND_2GHZ] =
			&carl9170_band_2GHz;
		chans += carl9170_band_2GHz.n_channels;
		bands++;
	पूर्ण
	अगर (ar->eeprom.operating_flags & AR9170_OPFLAG_5GHZ) अणु
		ar->hw->wiphy->bands[NL80211_BAND_5GHZ] =
			&carl9170_band_5GHz;
		chans += carl9170_band_5GHz.n_channels;
		bands++;
	पूर्ण

	अगर (!bands)
		वापस -EINVAL;

	ar->survey = kसुस्मृति(chans, माप(काष्ठा survey_info), GFP_KERNEL);
	अगर (!ar->survey)
		वापस -ENOMEM;
	ar->num_channels = chans;

	regulatory->current_rd = le16_to_cpu(ar->eeprom.reg_करोमुख्य[0]);

	/* second part of wiphy init */
	SET_IEEE80211_PERM_ADDR(ar->hw, ar->eeprom.mac_address);

	वापस 0;
पूर्ण

अटल व्योम carl9170_reg_notअगरier(काष्ठा wiphy *wiphy,
				  काष्ठा regulatory_request *request)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा ar9170 *ar = hw->priv;

	ath_reg_notअगरier_apply(wiphy, request, &ar->common.regulatory);
पूर्ण

पूर्णांक carl9170_रेजिस्टर(काष्ठा ar9170 *ar)
अणु
	काष्ठा ath_regulatory *regulatory = &ar->common.regulatory;
	पूर्णांक err = 0, i;

	अगर (WARN_ON(ar->mem_biपंचांगap))
		वापस -EINVAL;

	ar->mem_biपंचांगap = kसुस्मृति(roundup(ar->fw.mem_blocks, BITS_PER_LONG),
				 माप(अचिन्हित दीर्घ),
				 GFP_KERNEL);

	अगर (!ar->mem_biपंचांगap)
		वापस -ENOMEM;

	/* try to पढ़ो EEPROM, init MAC addr */
	err = carl9170_पढ़ो_eeprom(ar);
	अगर (err)
		वापस err;

	err = carl9170_parse_eeprom(ar);
	अगर (err)
		वापस err;

	err = ath_regd_init(regulatory, ar->hw->wiphy,
			    carl9170_reg_notअगरier);
	अगर (err)
		वापस err;

	अगर (modparam_noht) अणु
		carl9170_band_2GHz.ht_cap.ht_supported = false;
		carl9170_band_5GHz.ht_cap.ht_supported = false;
	पूर्ण

	क्रम (i = 0; i < ar->fw.vअगर_num; i++) अणु
		ar->vअगर_priv[i].id = i;
		ar->vअगर_priv[i].vअगर = शून्य;
	पूर्ण

	err = ieee80211_रेजिस्टर_hw(ar->hw);
	अगर (err)
		वापस err;

	/* mac80211 पूर्णांकerface is now रेजिस्टरed */
	ar->रेजिस्टरed = true;

	अगर (!ath_is_world_regd(regulatory))
		regulatory_hपूर्णांक(ar->hw->wiphy, regulatory->alpha2);

#अगर_घोषित CONFIG_CARL9170_DEBUGFS
	carl9170_debugfs_रेजिस्टर(ar);
#पूर्ण_अगर /* CONFIG_CARL9170_DEBUGFS */

	err = carl9170_led_init(ar);
	अगर (err)
		जाओ err_unreg;

#अगर_घोषित CONFIG_CARL9170_LEDS
	err = carl9170_led_रेजिस्टर(ar);
	अगर (err)
		जाओ err_unreg;
#पूर्ण_अगर /* CONFIG_CARL9170_LEDS */

#अगर_घोषित CONFIG_CARL9170_WPC
	err = carl9170_रेजिस्टर_wps_button(ar);
	अगर (err)
		जाओ err_unreg;
#पूर्ण_अगर /* CONFIG_CARL9170_WPC */

#अगर_घोषित CONFIG_CARL9170_HWRNG
	err = carl9170_रेजिस्टर_hwrng(ar);
	अगर (err)
		जाओ err_unreg;
#पूर्ण_अगर /* CONFIG_CARL9170_HWRNG */

	dev_info(&ar->udev->dev, "Atheros AR9170 is registered as '%s'\n",
		 wiphy_name(ar->hw->wiphy));

	वापस 0;

err_unreg:
	carl9170_unरेजिस्टर(ar);
	वापस err;
पूर्ण

व्योम carl9170_unरेजिस्टर(काष्ठा ar9170 *ar)
अणु
	अगर (!ar->रेजिस्टरed)
		वापस;

	ar->रेजिस्टरed = false;

#अगर_घोषित CONFIG_CARL9170_LEDS
	carl9170_led_unरेजिस्टर(ar);
#पूर्ण_अगर /* CONFIG_CARL9170_LEDS */

#अगर_घोषित CONFIG_CARL9170_DEBUGFS
	carl9170_debugfs_unरेजिस्टर(ar);
#पूर्ण_अगर /* CONFIG_CARL9170_DEBUGFS */

#अगर_घोषित CONFIG_CARL9170_WPC
	अगर (ar->wps.pbc) अणु
		input_unरेजिस्टर_device(ar->wps.pbc);
		ar->wps.pbc = शून्य;
	पूर्ण
#पूर्ण_अगर /* CONFIG_CARL9170_WPC */

#अगर_घोषित CONFIG_CARL9170_HWRNG
	carl9170_unरेजिस्टर_hwrng(ar);
#पूर्ण_अगर /* CONFIG_CARL9170_HWRNG */

	carl9170_cancel_worker(ar);
	cancel_work_sync(&ar->restart_work);

	ieee80211_unरेजिस्टर_hw(ar->hw);
पूर्ण

व्योम carl9170_मुक्त(काष्ठा ar9170 *ar)
अणु
	WARN_ON(ar->रेजिस्टरed);
	WARN_ON(IS_INITIALIZED(ar));

	kमुक्त_skb(ar->rx_failover);
	ar->rx_failover = शून्य;

	kमुक्त(ar->mem_biपंचांगap);
	ar->mem_biपंचांगap = शून्य;

	kमुक्त(ar->survey);
	ar->survey = शून्य;

	mutex_destroy(&ar->mutex);

	ieee80211_मुक्त_hw(ar->hw);
पूर्ण
