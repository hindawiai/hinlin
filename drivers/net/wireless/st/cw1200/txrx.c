<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Datapath implementation क्रम ST-Ericsson CW1200 mac80211 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#समावेश <net/mac80211.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>

#समावेश "cw1200.h"
#समावेश "wsm.h"
#समावेश "bh.h"
#समावेश "sta.h"
#समावेश "debug.h"

#घोषणा CW1200_INVALID_RATE_ID (0xFF)

अटल पूर्णांक cw1200_handle_action_rx(काष्ठा cw1200_common *priv,
				   काष्ठा sk_buff *skb);
अटल स्थिर काष्ठा ieee80211_rate *
cw1200_get_tx_rate(स्थिर काष्ठा cw1200_common *priv,
		   स्थिर काष्ठा ieee80211_tx_rate *rate);

/* ******************************************************************** */
/* TX queue lock / unlock						*/

अटल अंतरभूत व्योम cw1200_tx_queues_lock(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 4; ++i)
		cw1200_queue_lock(&priv->tx_queue[i]);
पूर्ण

अटल अंतरभूत व्योम cw1200_tx_queues_unlock(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 4; ++i)
		cw1200_queue_unlock(&priv->tx_queue[i]);
पूर्ण

/* ******************************************************************** */
/* TX policy cache implementation					*/

अटल व्योम tx_policy_dump(काष्ठा tx_policy *policy)
अणु
	pr_debug("[TX policy] %.1X%.1X%.1X%.1X%.1X%.1X%.1X%.1X %.1X%.1X%.1X%.1X%.1X%.1X%.1X%.1X %.1X%.1X%.1X%.1X%.1X%.1X%.1X%.1X: %d\n",
		 policy->raw[0] & 0x0F,  policy->raw[0] >> 4,
		 policy->raw[1] & 0x0F,  policy->raw[1] >> 4,
		 policy->raw[2] & 0x0F,  policy->raw[2] >> 4,
		 policy->raw[3] & 0x0F,  policy->raw[3] >> 4,
		 policy->raw[4] & 0x0F,  policy->raw[4] >> 4,
		 policy->raw[5] & 0x0F,  policy->raw[5] >> 4,
		 policy->raw[6] & 0x0F,  policy->raw[6] >> 4,
		 policy->raw[7] & 0x0F,  policy->raw[7] >> 4,
		 policy->raw[8] & 0x0F,  policy->raw[8] >> 4,
		 policy->raw[9] & 0x0F,  policy->raw[9] >> 4,
		 policy->raw[10] & 0x0F,  policy->raw[10] >> 4,
		 policy->raw[11] & 0x0F,  policy->raw[11] >> 4,
		 policy->defined);
पूर्ण

अटल व्योम tx_policy_build(स्थिर काष्ठा cw1200_common *priv,
	/* [out] */ काष्ठा tx_policy *policy,
	काष्ठा ieee80211_tx_rate *rates, माप_प्रकार count)
अणु
	पूर्णांक i, j;
	अचिन्हित limit = priv->लघु_frame_max_tx_count;
	अचिन्हित total = 0;
	BUG_ON(rates[0].idx < 0);
	स_रखो(policy, 0, माप(*policy));

	/* Sort rates in descending order. */
	क्रम (i = 1; i < count; ++i) अणु
		अगर (rates[i].idx < 0) अणु
			count = i;
			अवरोध;
		पूर्ण
		अगर (rates[i].idx > rates[i - 1].idx) अणु
			काष्ठा ieee80211_tx_rate पंचांगp = rates[i - 1];
			rates[i - 1] = rates[i];
			rates[i] = पंचांगp;
		पूर्ण
	पूर्ण

	/* Eliminate duplicates. */
	total = rates[0].count;
	क्रम (i = 0, j = 1; j < count; ++j) अणु
		अगर (rates[j].idx == rates[i].idx) अणु
			rates[i].count += rates[j].count;
		पूर्ण अन्यथा अगर (rates[j].idx > rates[i].idx) अणु
			अवरोध;
		पूर्ण अन्यथा अणु
			++i;
			अगर (i != j)
				rates[i] = rates[j];
		पूर्ण
		total += rates[j].count;
	पूर्ण
	count = i + 1;

	/* Re-fill policy trying to keep every requested rate and with
	 * respect to the global max tx retransmission count.
	 */
	अगर (limit < count)
		limit = count;
	अगर (total > limit) अणु
		क्रम (i = 0; i < count; ++i) अणु
			पूर्णांक left = count - i - 1;
			अगर (rates[i].count > limit - left)
				rates[i].count = limit - left;
			limit -= rates[i].count;
		पूर्ण
	पूर्ण

	/* HACK!!! Device has problems (at least) चयनing from
	 * 54Mbps CTS to 1Mbps. This चयन takes enormous amount
	 * of समय (100-200 ms), leading to valuable throughput drop.
	 * As a workaround, additional g-rates are injected to the
	 * policy.
	 */
	अगर (count == 2 && !(rates[0].flags & IEEE80211_TX_RC_MCS) &&
	    rates[0].idx > 4 && rates[0].count > 2 &&
	    rates[1].idx < 2) अणु
		पूर्णांक mid_rate = (rates[0].idx + 4) >> 1;

		/* Decrease number of retries क्रम the initial rate */
		rates[0].count -= 2;

		अगर (mid_rate != 4) अणु
			/* Keep fallback rate at 1Mbps. */
			rates[3] = rates[1];

			/* Inject 1 transmission on lowest g-rate */
			rates[2].idx = 4;
			rates[2].count = 1;
			rates[2].flags = rates[1].flags;

			/* Inject 1 transmission on mid-rate */
			rates[1].idx = mid_rate;
			rates[1].count = 1;

			/* Fallback to 1 Mbps is a really bad thing,
			 * so let's try to increase probability of
			 * successful transmission on the lowest g rate
			 * even more
			 */
			अगर (rates[0].count >= 3) अणु
				--rates[0].count;
				++rates[2].count;
			पूर्ण

			/* Adjust amount of rates defined */
			count += 2;
		पूर्ण अन्यथा अणु
			/* Keep fallback rate at 1Mbps. */
			rates[2] = rates[1];

			/* Inject 2 transmissions on lowest g-rate */
			rates[1].idx = 4;
			rates[1].count = 2;

			/* Adjust amount of rates defined */
			count += 1;
		पूर्ण
	पूर्ण

	policy->defined = cw1200_get_tx_rate(priv, &rates[0])->hw_value + 1;

	क्रम (i = 0; i < count; ++i) अणु
		रेजिस्टर अचिन्हित rateid, off, shअगरt, retries;

		rateid = cw1200_get_tx_rate(priv, &rates[i])->hw_value;
		off = rateid >> 3;		/* eq. rateid / 8 */
		shअगरt = (rateid & 0x07) << 2;	/* eq. (rateid % 8) * 4 */

		retries = rates[i].count;
		अगर (retries > 0x0F) अणु
			rates[i].count = 0x0f;
			retries = 0x0F;
		पूर्ण
		policy->tbl[off] |= __cpu_to_le32(retries << shअगरt);
		policy->retry_count += retries;
	पूर्ण

	pr_debug("[TX policy] Policy (%zu): %d:%d, %d:%d, %d:%d, %d:%d\n",
		 count,
		 rates[0].idx, rates[0].count,
		 rates[1].idx, rates[1].count,
		 rates[2].idx, rates[2].count,
		 rates[3].idx, rates[3].count);
पूर्ण

अटल अंतरभूत bool tx_policy_is_equal(स्थिर काष्ठा tx_policy *wanted,
					स्थिर काष्ठा tx_policy *cached)
अणु
	माप_प्रकार count = wanted->defined >> 1;
	अगर (wanted->defined > cached->defined)
		वापस false;
	अगर (count) अणु
		अगर (स_भेद(wanted->raw, cached->raw, count))
			वापस false;
	पूर्ण
	अगर (wanted->defined & 1) अणु
		अगर ((wanted->raw[count] & 0x0F) != (cached->raw[count] & 0x0F))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक tx_policy_find(काष्ठा tx_policy_cache *cache,
				स्थिर काष्ठा tx_policy *wanted)
अणु
	/* O(n) complनिकासy. Not so good, but there's only 8 entries in
	 * the cache.
	 * Also lru helps to reduce search समय.
	 */
	काष्ठा tx_policy_cache_entry *it;
	/* First search क्रम policy in "used" list */
	list_क्रम_each_entry(it, &cache->used, link) अणु
		अगर (tx_policy_is_equal(wanted, &it->policy))
			वापस it - cache->cache;
	पूर्ण
	/* Then - in "free list" */
	list_क्रम_each_entry(it, &cache->मुक्त, link) अणु
		अगर (tx_policy_is_equal(wanted, &it->policy))
			वापस it - cache->cache;
	पूर्ण
	वापस -1;
पूर्ण

अटल अंतरभूत व्योम tx_policy_use(काष्ठा tx_policy_cache *cache,
				 काष्ठा tx_policy_cache_entry *entry)
अणु
	++entry->policy.usage_count;
	list_move(&entry->link, &cache->used);
पूर्ण

अटल अंतरभूत पूर्णांक tx_policy_release(काष्ठा tx_policy_cache *cache,
				    काष्ठा tx_policy_cache_entry *entry)
अणु
	पूर्णांक ret = --entry->policy.usage_count;
	अगर (!ret)
		list_move(&entry->link, &cache->मुक्त);
	वापस ret;
पूर्ण

व्योम tx_policy_clean(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक idx, locked;
	काष्ठा tx_policy_cache *cache = &priv->tx_policy_cache;
	काष्ठा tx_policy_cache_entry *entry;

	cw1200_tx_queues_lock(priv);
	spin_lock_bh(&cache->lock);
	locked = list_empty(&cache->मुक्त);

	क्रम (idx = 0; idx < TX_POLICY_CACHE_SIZE; idx++) अणु
		entry = &cache->cache[idx];
		/* Policy usage count should be 0 at this समय as all queues
		   should be empty
		 */
		अगर (WARN_ON(entry->policy.usage_count)) अणु
			entry->policy.usage_count = 0;
			list_move(&entry->link, &cache->मुक्त);
		पूर्ण
		स_रखो(&entry->policy, 0, माप(entry->policy));
	पूर्ण
	अगर (locked)
		cw1200_tx_queues_unlock(priv);

	cw1200_tx_queues_unlock(priv);
	spin_unlock_bh(&cache->lock);
पूर्ण

/* ******************************************************************** */
/* External TX policy cache API						*/

व्योम tx_policy_init(काष्ठा cw1200_common *priv)
अणु
	काष्ठा tx_policy_cache *cache = &priv->tx_policy_cache;
	पूर्णांक i;

	स_रखो(cache, 0, माप(*cache));

	spin_lock_init(&cache->lock);
	INIT_LIST_HEAD(&cache->used);
	INIT_LIST_HEAD(&cache->मुक्त);

	क्रम (i = 0; i < TX_POLICY_CACHE_SIZE; ++i)
		list_add(&cache->cache[i].link, &cache->मुक्त);
पूर्ण

अटल पूर्णांक tx_policy_get(काष्ठा cw1200_common *priv,
		  काष्ठा ieee80211_tx_rate *rates,
		  माप_प्रकार count, bool *renew)
अणु
	पूर्णांक idx;
	काष्ठा tx_policy_cache *cache = &priv->tx_policy_cache;
	काष्ठा tx_policy wanted;

	tx_policy_build(priv, &wanted, rates, count);

	spin_lock_bh(&cache->lock);
	अगर (WARN_ON_ONCE(list_empty(&cache->मुक्त))) अणु
		spin_unlock_bh(&cache->lock);
		वापस CW1200_INVALID_RATE_ID;
	पूर्ण
	idx = tx_policy_find(cache, &wanted);
	अगर (idx >= 0) अणु
		pr_debug("[TX policy] Used TX policy: %d\n", idx);
		*renew = false;
	पूर्ण अन्यथा अणु
		काष्ठा tx_policy_cache_entry *entry;
		*renew = true;
		/* If policy is not found create a new one
		 * using the oldest entry in "free" list
		 */
		entry = list_entry(cache->मुक्त.prev,
			काष्ठा tx_policy_cache_entry, link);
		entry->policy = wanted;
		idx = entry - cache->cache;
		pr_debug("[TX policy] New TX policy: %d\n", idx);
		tx_policy_dump(&entry->policy);
	पूर्ण
	tx_policy_use(cache, &cache->cache[idx]);
	अगर (list_empty(&cache->मुक्त)) अणु
		/* Lock TX queues. */
		cw1200_tx_queues_lock(priv);
	पूर्ण
	spin_unlock_bh(&cache->lock);
	वापस idx;
पूर्ण

अटल व्योम tx_policy_put(काष्ठा cw1200_common *priv, पूर्णांक idx)
अणु
	पूर्णांक usage, locked;
	काष्ठा tx_policy_cache *cache = &priv->tx_policy_cache;

	spin_lock_bh(&cache->lock);
	locked = list_empty(&cache->मुक्त);
	usage = tx_policy_release(cache, &cache->cache[idx]);
	अगर (locked && !usage) अणु
		/* Unlock TX queues. */
		cw1200_tx_queues_unlock(priv);
	पूर्ण
	spin_unlock_bh(&cache->lock);
पूर्ण

अटल पूर्णांक tx_policy_upload(काष्ठा cw1200_common *priv)
अणु
	काष्ठा tx_policy_cache *cache = &priv->tx_policy_cache;
	पूर्णांक i;
	काष्ठा wsm_set_tx_rate_retry_policy arg = अणु
		.num = 0,
	पूर्ण;
	spin_lock_bh(&cache->lock);

	/* Upload only modअगरied entries. */
	क्रम (i = 0; i < TX_POLICY_CACHE_SIZE; ++i) अणु
		काष्ठा tx_policy *src = &cache->cache[i].policy;
		अगर (src->retry_count && !src->uploaded) अणु
			काष्ठा wsm_tx_rate_retry_policy *dst =
				&arg.tbl[arg.num];
			dst->index = i;
			dst->लघु_retries = priv->लघु_frame_max_tx_count;
			dst->दीर्घ_retries = priv->दीर्घ_frame_max_tx_count;

			dst->flags = WSM_TX_RATE_POLICY_FLAG_TERMINATE_WHEN_FINISHED |
				WSM_TX_RATE_POLICY_FLAG_COUNT_INITIAL_TRANSMIT;
			स_नकल(dst->rate_count_indices, src->tbl,
			       माप(dst->rate_count_indices));
			src->uploaded = 1;
			++arg.num;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&cache->lock);
	cw1200_debug_tx_cache_miss(priv);
	pr_debug("[TX policy] Upload %d policies\n", arg.num);
	वापस wsm_set_tx_rate_retry_policy(priv, &arg);
पूर्ण

व्योम tx_policy_upload_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, tx_policy_upload_work);

	pr_debug("[TX] TX policy upload.\n");
	tx_policy_upload(priv);

	wsm_unlock_tx(priv);
	cw1200_tx_queues_unlock(priv);
पूर्ण

/* ******************************************************************** */
/* cw1200 TX implementation						*/

काष्ठा cw1200_txinfo अणु
	काष्ठा sk_buff *skb;
	अचिन्हित queue;
	काष्ठा ieee80211_tx_info *tx_info;
	स्थिर काष्ठा ieee80211_rate *rate;
	काष्ठा ieee80211_hdr *hdr;
	माप_प्रकार hdrlen;
	स्थिर u8 *da;
	काष्ठा cw1200_sta_priv *sta_priv;
	काष्ठा ieee80211_sta *sta;
	काष्ठा cw1200_txpriv txpriv;
पूर्ण;

u32 cw1200_rate_mask_to_wsm(काष्ठा cw1200_common *priv, u32 rates)
अणु
	u32 ret = 0;
	पूर्णांक i;
	क्रम (i = 0; i < 32; ++i) अणु
		अगर (rates & BIT(i))
			ret |= BIT(priv->rates[i].hw_value);
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ieee80211_rate *
cw1200_get_tx_rate(स्थिर काष्ठा cw1200_common *priv,
		   स्थिर काष्ठा ieee80211_tx_rate *rate)
अणु
	अगर (rate->idx < 0)
		वापस शून्य;
	अगर (rate->flags & IEEE80211_TX_RC_MCS)
		वापस &priv->mcs_rates[rate->idx];
	वापस &priv->hw->wiphy->bands[priv->channel->band]->
		bitrates[rate->idx];
पूर्ण

अटल पूर्णांक
cw1200_tx_h_calc_link_ids(काष्ठा cw1200_common *priv,
			  काष्ठा cw1200_txinfo *t)
अणु
	अगर (t->sta && t->sta_priv->link_id)
		t->txpriv.raw_link_id =
				t->txpriv.link_id =
				t->sta_priv->link_id;
	अन्यथा अगर (priv->mode != NL80211_IFTYPE_AP)
		t->txpriv.raw_link_id =
				t->txpriv.link_id = 0;
	अन्यथा अगर (is_multicast_ether_addr(t->da)) अणु
		अगर (priv->enable_beacon) अणु
			t->txpriv.raw_link_id = 0;
			t->txpriv.link_id = CW1200_LINK_ID_AFTER_DTIM;
		पूर्ण अन्यथा अणु
			t->txpriv.raw_link_id = 0;
			t->txpriv.link_id = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		t->txpriv.link_id = cw1200_find_link_id(priv, t->da);
		अगर (!t->txpriv.link_id)
			t->txpriv.link_id = cw1200_alloc_link_id(priv, t->da);
		अगर (!t->txpriv.link_id) अणु
			wiphy_err(priv->hw->wiphy,
				  "No more link IDs available.\n");
			वापस -ENOENT;
		पूर्ण
		t->txpriv.raw_link_id = t->txpriv.link_id;
	पूर्ण
	अगर (t->txpriv.raw_link_id)
		priv->link_id_db[t->txpriv.raw_link_id - 1].बारtamp =
				jअगरfies;
	अगर (t->sta && (t->sta->uapsd_queues & BIT(t->queue)))
		t->txpriv.link_id = CW1200_LINK_ID_UAPSD;
	वापस 0;
पूर्ण

अटल व्योम
cw1200_tx_h_pm(काष्ठा cw1200_common *priv,
	       काष्ठा cw1200_txinfo *t)
अणु
	अगर (ieee80211_is_auth(t->hdr->frame_control)) अणु
		u32 mask = ~BIT(t->txpriv.raw_link_id);
		spin_lock_bh(&priv->ps_state_lock);
		priv->sta_asleep_mask &= mask;
		priv->pspoll_mask &= mask;
		spin_unlock_bh(&priv->ps_state_lock);
	पूर्ण
पूर्ण

अटल व्योम
cw1200_tx_h_calc_tid(काष्ठा cw1200_common *priv,
		     काष्ठा cw1200_txinfo *t)
अणु
	अगर (ieee80211_is_data_qos(t->hdr->frame_control)) अणु
		u8 *qos = ieee80211_get_qos_ctl(t->hdr);
		t->txpriv.tid = qos[0] & IEEE80211_QOS_CTL_TID_MASK;
	पूर्ण अन्यथा अगर (ieee80211_is_data(t->hdr->frame_control)) अणु
		t->txpriv.tid = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
cw1200_tx_h_crypt(काष्ठा cw1200_common *priv,
		  काष्ठा cw1200_txinfo *t)
अणु
	अगर (!t->tx_info->control.hw_key ||
	    !ieee80211_has_रक्षित(t->hdr->frame_control))
		वापस 0;

	t->hdrlen += t->tx_info->control.hw_key->iv_len;
	skb_put(t->skb, t->tx_info->control.hw_key->icv_len);

	अगर (t->tx_info->control.hw_key->cipher == WLAN_CIPHER_SUITE_TKIP)
		skb_put(t->skb, 8); /* MIC space */

	वापस 0;
पूर्ण

अटल पूर्णांक
cw1200_tx_h_align(काष्ठा cw1200_common *priv,
		  काष्ठा cw1200_txinfo *t,
		  u8 *flags)
अणु
	माप_प्रकार offset = (माप_प्रकार)t->skb->data & 3;

	अगर (!offset)
		वापस 0;

	अगर (offset & 1) अणु
		wiphy_err(priv->hw->wiphy,
			  "Bug: attempt to transmit a frame with wrong alignment: %zu\n",
			  offset);
		वापस -EINVAL;
	पूर्ण

	अगर (skb_headroom(t->skb) < offset) अणु
		wiphy_err(priv->hw->wiphy,
			  "Bug: no space allocated for DMA alignment. headroom: %d\n",
			  skb_headroom(t->skb));
		वापस -ENOMEM;
	पूर्ण
	skb_push(t->skb, offset);
	t->hdrlen += offset;
	t->txpriv.offset += offset;
	*flags |= WSM_TX_2BYTES_SHIFT;
	cw1200_debug_tx_align(priv);
	वापस 0;
पूर्ण

अटल पूर्णांक
cw1200_tx_h_action(काष्ठा cw1200_common *priv,
		   काष्ठा cw1200_txinfo *t)
अणु
	काष्ठा ieee80211_mgmt *mgmt =
		(काष्ठा ieee80211_mgmt *)t->hdr;
	अगर (ieee80211_is_action(t->hdr->frame_control) &&
	    mgmt->u.action.category == WLAN_CATEGORY_BACK)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/* Add WSM header */
अटल काष्ठा wsm_tx *
cw1200_tx_h_wsm(काष्ठा cw1200_common *priv,
		काष्ठा cw1200_txinfo *t)
अणु
	काष्ठा wsm_tx *wsm;

	अगर (skb_headroom(t->skb) < माप(काष्ठा wsm_tx)) अणु
		wiphy_err(priv->hw->wiphy,
			  "Bug: no space allocated for WSM header. headroom: %d\n",
			  skb_headroom(t->skb));
		वापस शून्य;
	पूर्ण

	wsm = skb_push(t->skb, माप(काष्ठा wsm_tx));
	t->txpriv.offset += माप(काष्ठा wsm_tx);
	स_रखो(wsm, 0, माप(*wsm));
	wsm->hdr.len = __cpu_to_le16(t->skb->len);
	wsm->hdr.id = __cpu_to_le16(0x0004);
	wsm->queue_id = wsm_queue_id_to_wsm(t->queue);
	वापस wsm;
पूर्ण

/* BT Coex specअगरic handling */
अटल व्योम
cw1200_tx_h_bt(काष्ठा cw1200_common *priv,
	       काष्ठा cw1200_txinfo *t,
	       काष्ठा wsm_tx *wsm)
अणु
	u8 priority = 0;

	अगर (!priv->bt_present)
		वापस;

	अगर (ieee80211_is_nullfunc(t->hdr->frame_control)) अणु
		priority = WSM_EPTA_PRIORITY_MGT;
	पूर्ण अन्यथा अगर (ieee80211_is_data(t->hdr->frame_control)) अणु
		/* Skip LLC SNAP header (+6) */
		u8 *payload = &t->skb->data[t->hdrlen];
		__be16 *ethertype = (__be16 *)&payload[6];
		अगर (be16_to_cpu(*ethertype) == ETH_P_PAE)
			priority = WSM_EPTA_PRIORITY_EAPOL;
	पूर्ण अन्यथा अगर (ieee80211_is_assoc_req(t->hdr->frame_control) ||
		ieee80211_is_reassoc_req(t->hdr->frame_control)) अणु
		काष्ठा ieee80211_mgmt *mgt_frame =
				(काष्ठा ieee80211_mgmt *)t->hdr;

		अगर (le16_to_cpu(mgt_frame->u.assoc_req.listen_पूर्णांकerval) <
						priv->listen_पूर्णांकerval) अणु
			pr_debug("Modified Listen Interval to %d from %d\n",
				 priv->listen_पूर्णांकerval,
				 mgt_frame->u.assoc_req.listen_पूर्णांकerval);
			/* Replace listen पूर्णांकerval derieved from
			 * the one पढ़ो from SDD
			 */
			mgt_frame->u.assoc_req.listen_पूर्णांकerval = cpu_to_le16(priv->listen_पूर्णांकerval);
		पूर्ण
	पूर्ण

	अगर (!priority) अणु
		अगर (ieee80211_is_action(t->hdr->frame_control))
			priority = WSM_EPTA_PRIORITY_ACTION;
		अन्यथा अगर (ieee80211_is_mgmt(t->hdr->frame_control))
			priority = WSM_EPTA_PRIORITY_MGT;
		अन्यथा अगर (wsm->queue_id == WSM_QUEUE_VOICE)
			priority = WSM_EPTA_PRIORITY_VOICE;
		अन्यथा अगर (wsm->queue_id == WSM_QUEUE_VIDEO)
			priority = WSM_EPTA_PRIORITY_VIDEO;
		अन्यथा
			priority = WSM_EPTA_PRIORITY_DATA;
	पूर्ण

	pr_debug("[TX] EPTA priority %d.\n", priority);

	wsm->flags |= priority << 1;
पूर्ण

अटल पूर्णांक
cw1200_tx_h_rate_policy(काष्ठा cw1200_common *priv,
			काष्ठा cw1200_txinfo *t,
			काष्ठा wsm_tx *wsm)
अणु
	bool tx_policy_renew = false;

	t->txpriv.rate_id = tx_policy_get(priv,
		t->tx_info->control.rates, IEEE80211_TX_MAX_RATES,
		&tx_policy_renew);
	अगर (t->txpriv.rate_id == CW1200_INVALID_RATE_ID)
		वापस -EFAULT;

	wsm->flags |= t->txpriv.rate_id << 4;

	t->rate = cw1200_get_tx_rate(priv,
		&t->tx_info->control.rates[0]);
	wsm->max_tx_rate = t->rate->hw_value;
	अगर (t->rate->flags & IEEE80211_TX_RC_MCS) अणु
		अगर (cw1200_ht_greenfield(&priv->ht_info))
			wsm->ht_tx_parameters |=
				__cpu_to_le32(WSM_HT_TX_GREENFIELD);
		अन्यथा
			wsm->ht_tx_parameters |=
				__cpu_to_le32(WSM_HT_TX_MIXED);
	पूर्ण

	अगर (tx_policy_renew) अणु
		pr_debug("[TX] TX policy renew.\n");
		/* It's not so optimal to stop TX queues every now and then.
		 * Better to reimplement task scheduling with
		 * a counter. TODO.
		 */
		wsm_lock_tx_async(priv);
		cw1200_tx_queues_lock(priv);
		अगर (queue_work(priv->workqueue,
			       &priv->tx_policy_upload_work) <= 0) अणु
			cw1200_tx_queues_unlock(priv);
			wsm_unlock_tx(priv);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल bool
cw1200_tx_h_pm_state(काष्ठा cw1200_common *priv,
		     काष्ठा cw1200_txinfo *t)
अणु
	पूर्णांक was_buffered = 1;

	अगर (t->txpriv.link_id == CW1200_LINK_ID_AFTER_DTIM &&
	    !priv->buffered_multicasts) अणु
		priv->buffered_multicasts = true;
		अगर (priv->sta_asleep_mask)
			queue_work(priv->workqueue,
				   &priv->multicast_start_work);
	पूर्ण

	अगर (t->txpriv.raw_link_id && t->txpriv.tid < CW1200_MAX_TID)
		was_buffered = priv->link_id_db[t->txpriv.raw_link_id - 1].buffered[t->txpriv.tid]++;

	वापस !was_buffered;
पूर्ण

/* ******************************************************************** */

व्योम cw1200_tx(काष्ठा ieee80211_hw *dev,
	       काष्ठा ieee80211_tx_control *control,
	       काष्ठा sk_buff *skb)
अणु
	काष्ठा cw1200_common *priv = dev->priv;
	काष्ठा cw1200_txinfo t = अणु
		.skb = skb,
		.queue = skb_get_queue_mapping(skb),
		.tx_info = IEEE80211_SKB_CB(skb),
		.hdr = (काष्ठा ieee80211_hdr *)skb->data,
		.txpriv.tid = CW1200_MAX_TID,
		.txpriv.rate_id = CW1200_INVALID_RATE_ID,
	पूर्ण;
	काष्ठा ieee80211_sta *sta;
	काष्ठा wsm_tx *wsm;
	bool tid_update = false;
	u8 flags = 0;
	पूर्णांक ret;

	अगर (priv->bh_error)
		जाओ drop;

	t.hdrlen = ieee80211_hdrlen(t.hdr->frame_control);
	t.da = ieee80211_get_DA(t.hdr);
	अगर (control) अणु
		t.sta = control->sta;
		t.sta_priv = (काष्ठा cw1200_sta_priv *)&t.sta->drv_priv;
	पूर्ण

	अगर (WARN_ON(t.queue >= 4))
		जाओ drop;

	ret = cw1200_tx_h_calc_link_ids(priv, &t);
	अगर (ret)
		जाओ drop;

	pr_debug("[TX] TX %d bytes (queue: %d, link_id: %d (%d)).\n",
		 skb->len, t.queue, t.txpriv.link_id,
		 t.txpriv.raw_link_id);

	cw1200_tx_h_pm(priv, &t);
	cw1200_tx_h_calc_tid(priv, &t);
	ret = cw1200_tx_h_crypt(priv, &t);
	अगर (ret)
		जाओ drop;
	ret = cw1200_tx_h_align(priv, &t, &flags);
	अगर (ret)
		जाओ drop;
	ret = cw1200_tx_h_action(priv, &t);
	अगर (ret)
		जाओ drop;
	wsm = cw1200_tx_h_wsm(priv, &t);
	अगर (!wsm) अणु
		ret = -ENOMEM;
		जाओ drop;
	पूर्ण
	wsm->flags |= flags;
	cw1200_tx_h_bt(priv, &t, wsm);
	ret = cw1200_tx_h_rate_policy(priv, &t, wsm);
	अगर (ret)
		जाओ drop;

	rcu_पढ़ो_lock();
	sta = rcu_dereference(t.sta);

	spin_lock_bh(&priv->ps_state_lock);
	अणु
		tid_update = cw1200_tx_h_pm_state(priv, &t);
		BUG_ON(cw1200_queue_put(&priv->tx_queue[t.queue],
					t.skb, &t.txpriv));
	पूर्ण
	spin_unlock_bh(&priv->ps_state_lock);

	अगर (tid_update && sta)
		ieee80211_sta_set_buffered(sta, t.txpriv.tid, true);

	rcu_पढ़ो_unlock();

	cw1200_bh_wakeup(priv);

	वापस;

drop:
	cw1200_skb_dtor(priv, skb, &t.txpriv);
	वापस;
पूर्ण

/* ******************************************************************** */

अटल पूर्णांक cw1200_handle_action_rx(काष्ठा cw1200_common *priv,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)skb->data;

	/* Filter block ACK negotiation: fully controlled by firmware */
	अगर (mgmt->u.action.category == WLAN_CATEGORY_BACK)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक cw1200_handle_pspoll(काष्ठा cw1200_common *priv,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_pspoll *pspoll = (काष्ठा ieee80211_pspoll *)skb->data;
	पूर्णांक link_id = 0;
	u32 pspoll_mask = 0;
	पूर्णांक drop = 1;
	पूर्णांक i;

	अगर (priv->join_status != CW1200_JOIN_STATUS_AP)
		जाओ करोne;
	अगर (स_भेद(priv->vअगर->addr, pspoll->bssid, ETH_ALEN))
		जाओ करोne;

	rcu_पढ़ो_lock();
	sta = ieee80211_find_sta(priv->vअगर, pspoll->ta);
	अगर (sta) अणु
		काष्ठा cw1200_sta_priv *sta_priv;
		sta_priv = (काष्ठा cw1200_sta_priv *)&sta->drv_priv;
		link_id = sta_priv->link_id;
		pspoll_mask = BIT(sta_priv->link_id);
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (!link_id)
		जाओ करोne;

	priv->pspoll_mask |= pspoll_mask;
	drop = 0;

	/* Do not report pspols अगर data क्रम given link id is queued alपढ़ोy. */
	क्रम (i = 0; i < 4; ++i) अणु
		अगर (cw1200_queue_get_num_queued(&priv->tx_queue[i],
						pspoll_mask)) अणु
			cw1200_bh_wakeup(priv);
			drop = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	pr_debug("[RX] PSPOLL: %s\n", drop ? "local" : "fwd");
करोne:
	वापस drop;
पूर्ण

/* ******************************************************************** */

व्योम cw1200_tx_confirm_cb(काष्ठा cw1200_common *priv,
			  पूर्णांक link_id,
			  काष्ठा wsm_tx_confirm *arg)
अणु
	u8 queue_id = cw1200_queue_get_queue_id(arg->packet_id);
	काष्ठा cw1200_queue *queue = &priv->tx_queue[queue_id];
	काष्ठा sk_buff *skb;
	स्थिर काष्ठा cw1200_txpriv *txpriv;

	pr_debug("[TX] TX confirm: %d, %d.\n",
		 arg->status, arg->ack_failures);

	अगर (priv->mode == NL80211_IFTYPE_UNSPECIFIED) अणु
		/* STA is stopped. */
		वापस;
	पूर्ण

	अगर (WARN_ON(queue_id >= 4))
		वापस;

	अगर (arg->status)
		pr_debug("TX failed: %d.\n", arg->status);

	अगर ((arg->status == WSM_REQUEUE) &&
	    (arg->flags & WSM_TX_STATUS_REQUEUE)) अणु
		/* "Requeue" means "implicit suspend" */
		काष्ठा wsm_suspend_resume suspend = अणु
			.link_id = link_id,
			.stop = 1,
			.multicast = !link_id,
		पूर्ण;
		cw1200_suspend_resume(priv, &suspend);
		wiphy_warn(priv->hw->wiphy, "Requeue for link_id %d (try %d). STAs asleep: 0x%.8X\n",
			   link_id,
			   cw1200_queue_get_generation(arg->packet_id) + 1,
			   priv->sta_asleep_mask);
		cw1200_queue_requeue(queue, arg->packet_id);
		spin_lock_bh(&priv->ps_state_lock);
		अगर (!link_id) अणु
			priv->buffered_multicasts = true;
			अगर (priv->sta_asleep_mask) अणु
				queue_work(priv->workqueue,
					   &priv->multicast_start_work);
			पूर्ण
		पूर्ण
		spin_unlock_bh(&priv->ps_state_lock);
	पूर्ण अन्यथा अगर (!cw1200_queue_get_skb(queue, arg->packet_id,
					 &skb, &txpriv)) अणु
		काष्ठा ieee80211_tx_info *tx = IEEE80211_SKB_CB(skb);
		पूर्णांक tx_count = arg->ack_failures;
		u8 ht_flags = 0;
		पूर्णांक i;

		अगर (cw1200_ht_greenfield(&priv->ht_info))
			ht_flags |= IEEE80211_TX_RC_GREEN_FIELD;

		spin_lock(&priv->bss_loss_lock);
		अगर (priv->bss_loss_state &&
		    arg->packet_id == priv->bss_loss_confirm_id) अणु
			अगर (arg->status) अणु
				/* Recovery failed */
				__cw1200_cqm_bssloss_sm(priv, 0, 0, 1);
			पूर्ण अन्यथा अणु
				/* Recovery succeeded */
				__cw1200_cqm_bssloss_sm(priv, 0, 1, 0);
			पूर्ण
		पूर्ण
		spin_unlock(&priv->bss_loss_lock);

		अगर (!arg->status) अणु
			tx->flags |= IEEE80211_TX_STAT_ACK;
			++tx_count;
			cw1200_debug_txed(priv);
			अगर (arg->flags & WSM_TX_STATUS_AGGREGATION) अणु
				/* Do not report aggregation to mac80211:
				 * it confuses minstrel a lot.
				 */
				/* tx->flags |= IEEE80211_TX_STAT_AMPDU; */
				cw1200_debug_txed_agg(priv);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (tx_count)
				++tx_count;
		पूर्ण

		क्रम (i = 0; i < IEEE80211_TX_MAX_RATES; ++i) अणु
			अगर (tx->status.rates[i].count >= tx_count) अणु
				tx->status.rates[i].count = tx_count;
				अवरोध;
			पूर्ण
			tx_count -= tx->status.rates[i].count;
			अगर (tx->status.rates[i].flags & IEEE80211_TX_RC_MCS)
				tx->status.rates[i].flags |= ht_flags;
		पूर्ण

		क्रम (++i; i < IEEE80211_TX_MAX_RATES; ++i) अणु
			tx->status.rates[i].count = 0;
			tx->status.rates[i].idx = -1;
		पूर्ण

		/* Pull off any crypto trailers that we added on */
		अगर (tx->control.hw_key) अणु
			skb_trim(skb, skb->len - tx->control.hw_key->icv_len);
			अगर (tx->control.hw_key->cipher == WLAN_CIPHER_SUITE_TKIP)
				skb_trim(skb, skb->len - 8); /* MIC space */
		पूर्ण
		cw1200_queue_हटाओ(queue, arg->packet_id);
	पूर्ण
	/* XXX TODO:  Only wake अगर there are pending transmits.. */
	cw1200_bh_wakeup(priv);
पूर्ण

अटल व्योम cw1200_notअगरy_buffered_tx(काष्ठा cw1200_common *priv,
			       काष्ठा sk_buff *skb, पूर्णांक link_id, पूर्णांक tid)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_hdr *hdr;
	u8 *buffered;
	u8 still_buffered = 0;

	अगर (link_id && tid < CW1200_MAX_TID) अणु
		buffered = priv->link_id_db
				[link_id - 1].buffered;

		spin_lock_bh(&priv->ps_state_lock);
		अगर (!WARN_ON(!buffered[tid]))
			still_buffered = --buffered[tid];
		spin_unlock_bh(&priv->ps_state_lock);

		अगर (!still_buffered && tid < CW1200_MAX_TID) अणु
			hdr = (काष्ठा ieee80211_hdr *)skb->data;
			rcu_पढ़ो_lock();
			sta = ieee80211_find_sta(priv->vअगर, hdr->addr1);
			अगर (sta)
				ieee80211_sta_set_buffered(sta, tid, false);
			rcu_पढ़ो_unlock();
		पूर्ण
	पूर्ण
पूर्ण

व्योम cw1200_skb_dtor(काष्ठा cw1200_common *priv,
		     काष्ठा sk_buff *skb,
		     स्थिर काष्ठा cw1200_txpriv *txpriv)
अणु
	skb_pull(skb, txpriv->offset);
	अगर (txpriv->rate_id != CW1200_INVALID_RATE_ID) अणु
		cw1200_notअगरy_buffered_tx(priv, skb,
					  txpriv->raw_link_id, txpriv->tid);
		tx_policy_put(priv, txpriv->rate_id);
	पूर्ण
	ieee80211_tx_status(priv->hw, skb);
पूर्ण

व्योम cw1200_rx_cb(काष्ठा cw1200_common *priv,
		  काष्ठा wsm_rx *arg,
		  पूर्णांक link_id,
		  काष्ठा sk_buff **skb_p)
अणु
	काष्ठा sk_buff *skb = *skb_p;
	काष्ठा ieee80211_rx_status *hdr = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_hdr *frame = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)skb->data;
	काष्ठा cw1200_link_entry *entry = शून्य;
	अचिन्हित दीर्घ grace_period;

	bool early_data = false;
	bool p2p = priv->vअगर && priv->vअगर->p2p;
	माप_प्रकार hdrlen;
	hdr->flag = 0;

	अगर (priv->mode == NL80211_IFTYPE_UNSPECIFIED) अणु
		/* STA is stopped. */
		जाओ drop;
	पूर्ण

	अगर (link_id && link_id <= CW1200_MAX_STA_IN_AP_MODE) अणु
		entry =	&priv->link_id_db[link_id - 1];
		अगर (entry->status == CW1200_LINK_SOFT &&
		    ieee80211_is_data(frame->frame_control))
			early_data = true;
		entry->बारtamp = jअगरfies;
	पूर्ण अन्यथा अगर (p2p &&
		   ieee80211_is_action(frame->frame_control) &&
		   (mgmt->u.action.category == WLAN_CATEGORY_PUBLIC)) अणु
		pr_debug("[RX] Going to MAP&RESET link ID\n");
		WARN_ON(work_pending(&priv->linkid_reset_work));
		स_नकल(&priv->action_frame_sa[0],
		       ieee80211_get_SA(frame), ETH_ALEN);
		priv->action_linkid = 0;
		schedule_work(&priv->linkid_reset_work);
	पूर्ण

	अगर (link_id && p2p &&
	    ieee80211_is_action(frame->frame_control) &&
	    (mgmt->u.action.category == WLAN_CATEGORY_PUBLIC)) अणु
		/* Link ID alपढ़ोy exists क्रम the ACTION frame.
		 * Reset and Remap
		 */
		WARN_ON(work_pending(&priv->linkid_reset_work));
		स_नकल(&priv->action_frame_sa[0],
		       ieee80211_get_SA(frame), ETH_ALEN);
		priv->action_linkid = link_id;
		schedule_work(&priv->linkid_reset_work);
	पूर्ण
	अगर (arg->status) अणु
		अगर (arg->status == WSM_STATUS_MICFAILURE) अणु
			pr_debug("[RX] MIC failure.\n");
			hdr->flag |= RX_FLAG_MMIC_ERROR;
		पूर्ण अन्यथा अगर (arg->status == WSM_STATUS_NO_KEY_FOUND) अणु
			pr_debug("[RX] No key found.\n");
			जाओ drop;
		पूर्ण अन्यथा अणु
			pr_debug("[RX] Receive failure: %d.\n",
				 arg->status);
			जाओ drop;
		पूर्ण
	पूर्ण

	अगर (skb->len < माप(काष्ठा ieee80211_pspoll)) अणु
		wiphy_warn(priv->hw->wiphy, "Malformed SDU rx'ed. Size is lesser than IEEE header.\n");
		जाओ drop;
	पूर्ण

	अगर (ieee80211_is_pspoll(frame->frame_control))
		अगर (cw1200_handle_pspoll(priv, skb))
			जाओ drop;

	hdr->band = ((arg->channel_number & 0xff00) ||
		     (arg->channel_number > 14)) ?
			NL80211_BAND_5GHZ : NL80211_BAND_2GHZ;
	hdr->freq = ieee80211_channel_to_frequency(
			arg->channel_number,
			hdr->band);

	अगर (arg->rx_rate >= 14) अणु
		hdr->encoding = RX_ENC_HT;
		hdr->rate_idx = arg->rx_rate - 14;
	पूर्ण अन्यथा अगर (arg->rx_rate >= 4) अणु
		hdr->rate_idx = arg->rx_rate - 2;
	पूर्ण अन्यथा अणु
		hdr->rate_idx = arg->rx_rate;
	पूर्ण

	hdr->संकेत = (s8)arg->rcpi_rssi;
	hdr->antenna = 0;

	hdrlen = ieee80211_hdrlen(frame->frame_control);

	अगर (WSM_RX_STATUS_ENCRYPTION(arg->flags)) अणु
		माप_प्रकार iv_len = 0, icv_len = 0;

		hdr->flag |= RX_FLAG_DECRYPTED | RX_FLAG_IV_STRIPPED;

		/* Oops... There is no fast way to ask mac80211 about
		 * IV/ICV lengths. Even defineas are not exposed.
		 */
		चयन (WSM_RX_STATUS_ENCRYPTION(arg->flags)) अणु
		हाल WSM_RX_STATUS_WEP:
			iv_len = 4 /* WEP_IV_LEN */;
			icv_len = 4 /* WEP_ICV_LEN */;
			अवरोध;
		हाल WSM_RX_STATUS_TKIP:
			iv_len = 8 /* TKIP_IV_LEN */;
			icv_len = 4 /* TKIP_ICV_LEN */
				+ 8 /*MICHAEL_MIC_LEN*/;
			hdr->flag |= RX_FLAG_MMIC_STRIPPED;
			अवरोध;
		हाल WSM_RX_STATUS_AES:
			iv_len = 8 /* CCMP_HDR_LEN */;
			icv_len = 8 /* CCMP_MIC_LEN */;
			अवरोध;
		हाल WSM_RX_STATUS_WAPI:
			iv_len = 18 /* WAPI_HDR_LEN */;
			icv_len = 16 /* WAPI_MIC_LEN */;
			अवरोध;
		शेष:
			pr_warn("Unknown encryption type %d\n",
				WSM_RX_STATUS_ENCRYPTION(arg->flags));
			जाओ drop;
		पूर्ण

		/* Firmware strips ICV in हाल of MIC failure. */
		अगर (arg->status == WSM_STATUS_MICFAILURE)
			icv_len = 0;

		अगर (skb->len < hdrlen + iv_len + icv_len) अणु
			wiphy_warn(priv->hw->wiphy, "Malformed SDU rx'ed. Size is lesser than crypto headers.\n");
			जाओ drop;
		पूर्ण

		/* Remove IV, ICV and MIC */
		skb_trim(skb, skb->len - icv_len);
		स_हटाओ(skb->data + iv_len, skb->data, hdrlen);
		skb_pull(skb, iv_len);
	पूर्ण

	/* Remove TSF from the end of frame */
	अगर (arg->flags & WSM_RX_STATUS_TSF_INCLUDED) अणु
		स_नकल(&hdr->maस_समय, skb->data + skb->len - 8, 8);
		hdr->maस_समय = le64_to_cpu(hdr->maस_समय);
		अगर (skb->len >= 8)
			skb_trim(skb, skb->len - 8);
	पूर्ण अन्यथा अणु
		hdr->maस_समय = 0;
	पूर्ण

	cw1200_debug_rxed(priv);
	अगर (arg->flags & WSM_RX_STATUS_AGGREGATE)
		cw1200_debug_rxed_agg(priv);

	अगर (ieee80211_is_action(frame->frame_control) &&
	    (arg->flags & WSM_RX_STATUS_ADDRESS1)) अणु
		अगर (cw1200_handle_action_rx(priv, skb))
			वापस;
	पूर्ण अन्यथा अगर (ieee80211_is_beacon(frame->frame_control) &&
		   !arg->status && priv->vअगर &&
		   ether_addr_equal(ieee80211_get_SA(frame), priv->vअगर->bss_conf.bssid)) अणु
		स्थिर u8 *tim_ie;
		u8 *ies = ((काष्ठा ieee80211_mgmt *)
			  (skb->data))->u.beacon.variable;
		माप_प्रकार ies_len = skb->len - (ies - (u8 *)(skb->data));

		tim_ie = cfg80211_find_ie(WLAN_EID_TIM, ies, ies_len);
		अगर (tim_ie) अणु
			काष्ठा ieee80211_tim_ie *tim =
				(काष्ठा ieee80211_tim_ie *)&tim_ie[2];

			अगर (priv->join_dtim_period != tim->dtim_period) अणु
				priv->join_dtim_period = tim->dtim_period;
				queue_work(priv->workqueue,
					   &priv->set_beacon_wakeup_period_work);
			पूर्ण
		पूर्ण

		/* Disable beacon filter once we're associated... */
		अगर (priv->disable_beacon_filter &&
		    (priv->vअगर->bss_conf.assoc ||
		     priv->vअगर->bss_conf.ibss_joined)) अणु
			priv->disable_beacon_filter = false;
			queue_work(priv->workqueue,
				   &priv->update_filtering_work);
		पूर्ण
	पूर्ण

	/* Stay awake after frame is received to give
	 * userspace chance to react and acquire appropriate
	 * wakelock.
	 */
	अगर (ieee80211_is_auth(frame->frame_control))
		grace_period = 5 * HZ;
	अन्यथा अगर (ieee80211_is_deauth(frame->frame_control))
		grace_period = 5 * HZ;
	अन्यथा
		grace_period = 1 * HZ;
	cw1200_pm_stay_awake(&priv->pm_state, grace_period);

	अगर (early_data) अणु
		spin_lock_bh(&priv->ps_state_lock);
		/* Double-check status with lock held */
		अगर (entry->status == CW1200_LINK_SOFT)
			skb_queue_tail(&entry->rx_queue, skb);
		अन्यथा
			ieee80211_rx_irqsafe(priv->hw, skb);
		spin_unlock_bh(&priv->ps_state_lock);
	पूर्ण अन्यथा अणु
		ieee80211_rx_irqsafe(priv->hw, skb);
	पूर्ण
	*skb_p = शून्य;

	वापस;

drop:
	/* TODO: update failure counters */
	वापस;
पूर्ण

/* ******************************************************************** */
/* Security								*/

पूर्णांक cw1200_alloc_key(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक idx;

	idx = ffs(~priv->key_map) - 1;
	अगर (idx < 0 || idx > WSM_KEY_MAX_INDEX)
		वापस -1;

	priv->key_map |= BIT(idx);
	priv->keys[idx].index = idx;
	वापस idx;
पूर्ण

व्योम cw1200_मुक्त_key(काष्ठा cw1200_common *priv, पूर्णांक idx)
अणु
	BUG_ON(!(priv->key_map & BIT(idx)));
	स_रखो(&priv->keys[idx], 0, माप(priv->keys[idx]));
	priv->key_map &= ~BIT(idx);
पूर्ण

व्योम cw1200_मुक्त_keys(काष्ठा cw1200_common *priv)
अणु
	स_रखो(&priv->keys, 0, माप(priv->keys));
	priv->key_map = 0;
पूर्ण

पूर्णांक cw1200_upload_keys(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक idx, ret = 0;
	क्रम (idx = 0; idx <= WSM_KEY_MAX_INDEX; ++idx)
		अगर (priv->key_map & BIT(idx)) अणु
			ret = wsm_add_key(priv, &priv->keys[idx]);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
	वापस ret;
पूर्ण

/* Workaround क्रम WFD test हाल 6.1.10 */
व्योम cw1200_link_id_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, linkid_reset_work);
	पूर्णांक temp_linkid;

	अगर (!priv->action_linkid) अणु
		/* In GO mode we can receive ACTION frames without a linkID */
		temp_linkid = cw1200_alloc_link_id(priv,
				&priv->action_frame_sa[0]);
		WARN_ON(!temp_linkid);
		अगर (temp_linkid) अणु
			/* Make sure we execute the WQ */
			flush_workqueue(priv->workqueue);
			/* Release the link ID */
			spin_lock_bh(&priv->ps_state_lock);
			priv->link_id_db[temp_linkid - 1].prev_status =
				priv->link_id_db[temp_linkid - 1].status;
			priv->link_id_db[temp_linkid - 1].status =
				CW1200_LINK_RESET;
			spin_unlock_bh(&priv->ps_state_lock);
			wsm_lock_tx_async(priv);
			अगर (queue_work(priv->workqueue,
				       &priv->link_id_work) <= 0)
				wsm_unlock_tx(priv);
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_lock_bh(&priv->ps_state_lock);
		priv->link_id_db[priv->action_linkid - 1].prev_status =
			priv->link_id_db[priv->action_linkid - 1].status;
		priv->link_id_db[priv->action_linkid - 1].status =
			CW1200_LINK_RESET_REMAP;
		spin_unlock_bh(&priv->ps_state_lock);
		wsm_lock_tx_async(priv);
		अगर (queue_work(priv->workqueue, &priv->link_id_work) <= 0)
			wsm_unlock_tx(priv);
		flush_workqueue(priv->workqueue);
	पूर्ण
पूर्ण

पूर्णांक cw1200_find_link_id(काष्ठा cw1200_common *priv, स्थिर u8 *mac)
अणु
	पूर्णांक i, ret = 0;
	spin_lock_bh(&priv->ps_state_lock);
	क्रम (i = 0; i < CW1200_MAX_STA_IN_AP_MODE; ++i) अणु
		अगर (!स_भेद(mac, priv->link_id_db[i].mac, ETH_ALEN) &&
		    priv->link_id_db[i].status) अणु
			priv->link_id_db[i].बारtamp = jअगरfies;
			ret = i + 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->ps_state_lock);
	वापस ret;
पूर्ण

पूर्णांक cw1200_alloc_link_id(काष्ठा cw1200_common *priv, स्थिर u8 *mac)
अणु
	पूर्णांक i, ret = 0;
	अचिन्हित दीर्घ max_inactivity = 0;
	अचिन्हित दीर्घ now = jअगरfies;

	spin_lock_bh(&priv->ps_state_lock);
	क्रम (i = 0; i < CW1200_MAX_STA_IN_AP_MODE; ++i) अणु
		अगर (!priv->link_id_db[i].status) अणु
			ret = i + 1;
			अवरोध;
		पूर्ण अन्यथा अगर (priv->link_id_db[i].status != CW1200_LINK_HARD &&
			   !priv->tx_queue_stats.link_map_cache[i + 1]) अणु
			अचिन्हित दीर्घ inactivity =
				now - priv->link_id_db[i].बारtamp;
			अगर (inactivity < max_inactivity)
				जारी;
			max_inactivity = inactivity;
			ret = i + 1;
		पूर्ण
	पूर्ण
	अगर (ret) अणु
		काष्ठा cw1200_link_entry *entry = &priv->link_id_db[ret - 1];
		pr_debug("[AP] STA added, link_id: %d\n", ret);
		entry->status = CW1200_LINK_RESERVE;
		स_नकल(&entry->mac, mac, ETH_ALEN);
		स_रखो(&entry->buffered, 0, CW1200_MAX_TID);
		skb_queue_head_init(&entry->rx_queue);
		wsm_lock_tx_async(priv);
		अगर (queue_work(priv->workqueue, &priv->link_id_work) <= 0)
			wsm_unlock_tx(priv);
	पूर्ण अन्यथा अणु
		wiphy_info(priv->hw->wiphy,
			   "[AP] Early: no more link IDs available.\n");
	पूर्ण

	spin_unlock_bh(&priv->ps_state_lock);
	वापस ret;
पूर्ण

व्योम cw1200_link_id_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, link_id_work);
	wsm_flush_tx(priv);
	cw1200_link_id_gc_work(&priv->link_id_gc_work.work);
	wsm_unlock_tx(priv);
पूर्ण

व्योम cw1200_link_id_gc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, link_id_gc_work.work);
	काष्ठा wsm_reset reset = अणु
		.reset_statistics = false,
	पूर्ण;
	काष्ठा wsm_map_link map_link = अणु
		.link_id = 0,
	पूर्ण;
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ next_gc = -1;
	दीर्घ ttl;
	bool need_reset;
	u32 mask;
	पूर्णांक i;

	अगर (priv->join_status != CW1200_JOIN_STATUS_AP)
		वापस;

	wsm_lock_tx(priv);
	spin_lock_bh(&priv->ps_state_lock);
	क्रम (i = 0; i < CW1200_MAX_STA_IN_AP_MODE; ++i) अणु
		need_reset = false;
		mask = BIT(i + 1);
		अगर (priv->link_id_db[i].status == CW1200_LINK_RESERVE ||
		    (priv->link_id_db[i].status == CW1200_LINK_HARD &&
		     !(priv->link_id_map & mask))) अणु
			अगर (priv->link_id_map & mask) अणु
				priv->sta_asleep_mask &= ~mask;
				priv->pspoll_mask &= ~mask;
				need_reset = true;
			पूर्ण
			priv->link_id_map |= mask;
			अगर (priv->link_id_db[i].status != CW1200_LINK_HARD)
				priv->link_id_db[i].status = CW1200_LINK_SOFT;
			स_नकल(map_link.mac_addr, priv->link_id_db[i].mac,
			       ETH_ALEN);
			spin_unlock_bh(&priv->ps_state_lock);
			अगर (need_reset) अणु
				reset.link_id = i + 1;
				wsm_reset(priv, &reset);
			पूर्ण
			map_link.link_id = i + 1;
			wsm_map_link(priv, &map_link);
			next_gc = min(next_gc, CW1200_LINK_ID_GC_TIMEOUT);
			spin_lock_bh(&priv->ps_state_lock);
		पूर्ण अन्यथा अगर (priv->link_id_db[i].status == CW1200_LINK_SOFT) अणु
			ttl = priv->link_id_db[i].बारtamp - now +
					CW1200_LINK_ID_GC_TIMEOUT;
			अगर (ttl <= 0) अणु
				need_reset = true;
				priv->link_id_db[i].status = CW1200_LINK_OFF;
				priv->link_id_map &= ~mask;
				priv->sta_asleep_mask &= ~mask;
				priv->pspoll_mask &= ~mask;
				eth_zero_addr(map_link.mac_addr);
				spin_unlock_bh(&priv->ps_state_lock);
				reset.link_id = i + 1;
				wsm_reset(priv, &reset);
				spin_lock_bh(&priv->ps_state_lock);
			पूर्ण अन्यथा अणु
				next_gc = min_t(अचिन्हित दीर्घ, next_gc, ttl);
			पूर्ण
		पूर्ण अन्यथा अगर (priv->link_id_db[i].status == CW1200_LINK_RESET ||
				priv->link_id_db[i].status ==
				CW1200_LINK_RESET_REMAP) अणु
			पूर्णांक status = priv->link_id_db[i].status;
			priv->link_id_db[i].status =
					priv->link_id_db[i].prev_status;
			priv->link_id_db[i].बारtamp = now;
			reset.link_id = i + 1;
			spin_unlock_bh(&priv->ps_state_lock);
			wsm_reset(priv, &reset);
			अगर (status == CW1200_LINK_RESET_REMAP) अणु
				स_नकल(map_link.mac_addr,
				       priv->link_id_db[i].mac,
				       ETH_ALEN);
				map_link.link_id = i + 1;
				wsm_map_link(priv, &map_link);
				next_gc = min(next_gc,
						CW1200_LINK_ID_GC_TIMEOUT);
			पूर्ण
			spin_lock_bh(&priv->ps_state_lock);
		पूर्ण
		अगर (need_reset) अणु
			skb_queue_purge(&priv->link_id_db[i].rx_queue);
			pr_debug("[AP] STA removed, link_id: %d\n",
				 reset.link_id);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->ps_state_lock);
	अगर (next_gc != -1)
		queue_delayed_work(priv->workqueue,
				   &priv->link_id_gc_work, next_gc);
	wsm_unlock_tx(priv);
पूर्ण
