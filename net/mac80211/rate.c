<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright (c) 2006 Jiri Benc <jbenc@suse.cz>
 * Copyright 2017	Intel Deutschland GmbH
 */

#समावेश <linux/kernel.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश "rate.h"
#समावेश "ieee80211_i.h"
#समावेश "debugfs.h"

काष्ठा rate_control_alg अणु
	काष्ठा list_head list;
	स्थिर काष्ठा rate_control_ops *ops;
पूर्ण;

अटल LIST_HEAD(rate_ctrl_algs);
अटल DEFINE_MUTEX(rate_ctrl_mutex);

अटल अक्षर *ieee80211_शेष_rc_algo = CONFIG_MAC80211_RC_DEFAULT;
module_param(ieee80211_शेष_rc_algo, अक्षरp, 0644);
MODULE_PARM_DESC(ieee80211_शेष_rc_algo,
		 "Default rate control algorithm for mac80211 to use");

व्योम rate_control_rate_init(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_local *local = sta->sdata->local;
	काष्ठा rate_control_ref *ref = sta->rate_ctrl;
	काष्ठा ieee80211_sta *ista = &sta->sta;
	व्योम *priv_sta = sta->rate_ctrl_priv;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;

	ieee80211_sta_set_rx_nss(sta);

	अगर (!ref)
		वापस;

	rcu_पढ़ो_lock();

	chanctx_conf = rcu_dereference(sta->sdata->vअगर.chanctx_conf);
	अगर (WARN_ON(!chanctx_conf)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	sband = local->hw.wiphy->bands[chanctx_conf->def.chan->band];

	/* TODO: check क्रम minstrel_s1g ? */
	अगर (sband->band == NL80211_BAND_S1GHZ) अणु
		ieee80211_s1g_sta_rate_init(sta);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	spin_lock_bh(&sta->rate_ctrl_lock);
	ref->ops->rate_init(ref->priv, sband, &chanctx_conf->def, ista,
			    priv_sta);
	spin_unlock_bh(&sta->rate_ctrl_lock);
	rcu_पढ़ो_unlock();
	set_sta_flag(sta, WLAN_STA_RATE_CONTROL);
पूर्ण

व्योम rate_control_tx_status(काष्ठा ieee80211_local *local,
			    काष्ठा ieee80211_supported_band *sband,
			    काष्ठा ieee80211_tx_status *st)
अणु
	काष्ठा rate_control_ref *ref = local->rate_ctrl;
	काष्ठा sta_info *sta = container_of(st->sta, काष्ठा sta_info, sta);
	व्योम *priv_sta = sta->rate_ctrl_priv;

	अगर (!ref || !test_sta_flag(sta, WLAN_STA_RATE_CONTROL))
		वापस;

	spin_lock_bh(&sta->rate_ctrl_lock);
	अगर (ref->ops->tx_status_ext)
		ref->ops->tx_status_ext(ref->priv, sband, priv_sta, st);
	अन्यथा अगर (st->skb)
		ref->ops->tx_status(ref->priv, sband, st->sta, priv_sta, st->skb);
	अन्यथा
		WARN_ON_ONCE(1);

	spin_unlock_bh(&sta->rate_ctrl_lock);
पूर्ण

व्योम rate_control_rate_update(काष्ठा ieee80211_local *local,
				    काष्ठा ieee80211_supported_band *sband,
				    काष्ठा sta_info *sta, u32 changed)
अणु
	काष्ठा rate_control_ref *ref = local->rate_ctrl;
	काष्ठा ieee80211_sta *ista = &sta->sta;
	व्योम *priv_sta = sta->rate_ctrl_priv;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;

	अगर (ref && ref->ops->rate_update) अणु
		rcu_पढ़ो_lock();

		chanctx_conf = rcu_dereference(sta->sdata->vअगर.chanctx_conf);
		अगर (WARN_ON(!chanctx_conf)) अणु
			rcu_पढ़ो_unlock();
			वापस;
		पूर्ण

		spin_lock_bh(&sta->rate_ctrl_lock);
		ref->ops->rate_update(ref->priv, sband, &chanctx_conf->def,
				      ista, priv_sta, changed);
		spin_unlock_bh(&sta->rate_ctrl_lock);
		rcu_पढ़ो_unlock();
	पूर्ण
	drv_sta_rc_update(local, sta->sdata, &sta->sta, changed);
पूर्ण

पूर्णांक ieee80211_rate_control_रेजिस्टर(स्थिर काष्ठा rate_control_ops *ops)
अणु
	काष्ठा rate_control_alg *alg;

	अगर (!ops->name)
		वापस -EINVAL;

	mutex_lock(&rate_ctrl_mutex);
	list_क्रम_each_entry(alg, &rate_ctrl_algs, list) अणु
		अगर (!म_भेद(alg->ops->name, ops->name)) अणु
			/* करोn't रेजिस्टर an algorithm twice */
			WARN_ON(1);
			mutex_unlock(&rate_ctrl_mutex);
			वापस -EALREADY;
		पूर्ण
	पूर्ण

	alg = kzalloc(माप(*alg), GFP_KERNEL);
	अगर (alg == शून्य) अणु
		mutex_unlock(&rate_ctrl_mutex);
		वापस -ENOMEM;
	पूर्ण
	alg->ops = ops;

	list_add_tail(&alg->list, &rate_ctrl_algs);
	mutex_unlock(&rate_ctrl_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ieee80211_rate_control_रेजिस्टर);

व्योम ieee80211_rate_control_unरेजिस्टर(स्थिर काष्ठा rate_control_ops *ops)
अणु
	काष्ठा rate_control_alg *alg;

	mutex_lock(&rate_ctrl_mutex);
	list_क्रम_each_entry(alg, &rate_ctrl_algs, list) अणु
		अगर (alg->ops == ops) अणु
			list_del(&alg->list);
			kमुक्त(alg);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&rate_ctrl_mutex);
पूर्ण
EXPORT_SYMBOL(ieee80211_rate_control_unरेजिस्टर);

अटल स्थिर काष्ठा rate_control_ops *
ieee80211_try_rate_control_ops_get(स्थिर अक्षर *name)
अणु
	काष्ठा rate_control_alg *alg;
	स्थिर काष्ठा rate_control_ops *ops = शून्य;

	अगर (!name)
		वापस शून्य;

	mutex_lock(&rate_ctrl_mutex);
	list_क्रम_each_entry(alg, &rate_ctrl_algs, list) अणु
		अगर (!म_भेद(alg->ops->name, name)) अणु
			ops = alg->ops;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&rate_ctrl_mutex);
	वापस ops;
पूर्ण

/* Get the rate control algorithm. */
अटल स्थिर काष्ठा rate_control_ops *
ieee80211_rate_control_ops_get(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा rate_control_ops *ops;
	स्थिर अक्षर *alg_name;

	kernel_param_lock(THIS_MODULE);
	अगर (!name)
		alg_name = ieee80211_शेष_rc_algo;
	अन्यथा
		alg_name = name;

	ops = ieee80211_try_rate_control_ops_get(alg_name);
	अगर (!ops && name)
		/* try शेष अगर specअगरic alg requested but not found */
		ops = ieee80211_try_rate_control_ops_get(ieee80211_शेष_rc_algo);

	/* Note: check क्रम > 0 is पूर्णांकentional to aव्योम clang warning */
	अगर (!ops && (म_माप(CONFIG_MAC80211_RC_DEFAULT) > 0))
		/* try built-in one अगर specअगरic alg requested but not found */
		ops = ieee80211_try_rate_control_ops_get(CONFIG_MAC80211_RC_DEFAULT);

	kernel_param_unlock(THIS_MODULE);

	वापस ops;
पूर्ण

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
अटल sमाप_प्रकार rcname_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rate_control_ref *ref = file->निजी_data;
	पूर्णांक len = म_माप(ref->ops->name);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos,
				       ref->ops->name, len);
पूर्ण

स्थिर काष्ठा file_operations rcname_ops = अणु
	.पढ़ो = rcname_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा rate_control_ref *
rate_control_alloc(स्थिर अक्षर *name, काष्ठा ieee80211_local *local)
अणु
	काष्ठा rate_control_ref *ref;

	ref = kदो_स्मृति(माप(काष्ठा rate_control_ref), GFP_KERNEL);
	अगर (!ref)
		वापस शून्य;
	ref->ops = ieee80211_rate_control_ops_get(name);
	अगर (!ref->ops)
		जाओ मुक्त;

	ref->priv = ref->ops->alloc(&local->hw);
	अगर (!ref->priv)
		जाओ मुक्त;
	वापस ref;

मुक्त:
	kमुक्त(ref);
	वापस शून्य;
पूर्ण

अटल व्योम rate_control_मुक्त(काष्ठा ieee80211_local *local,
			      काष्ठा rate_control_ref *ctrl_ref)
अणु
	ctrl_ref->ops->मुक्त(ctrl_ref->priv);

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	debugfs_हटाओ_recursive(local->debugfs.rcdir);
	local->debugfs.rcdir = शून्य;
#पूर्ण_अगर

	kमुक्त(ctrl_ref);
पूर्ण

व्योम ieee80211_check_rate_mask(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_supported_band *sband;
	u32 user_mask, basic_rates = sdata->vअगर.bss_conf.basic_rates;
	क्रमागत nl80211_band band;

	अगर (WARN_ON(!sdata->vअगर.bss_conf.chandef.chan))
		वापस;

	band = sdata->vअगर.bss_conf.chandef.chan->band;
	अगर (band == NL80211_BAND_S1GHZ) अणु
		/* TODO */
		वापस;
	पूर्ण

	अगर (WARN_ON_ONCE(!basic_rates))
		वापस;

	user_mask = sdata->rc_rateidx_mask[band];
	sband = local->hw.wiphy->bands[band];

	अगर (user_mask & basic_rates)
		वापस;

	sdata_dbg(sdata,
		  "no overlap between basic rates (0x%x) and user mask (0x%x on band %d) - clearing the latter",
		  basic_rates, user_mask, band);
	sdata->rc_rateidx_mask[band] = (1 << sband->n_bitrates) - 1;
पूर्ण

अटल bool rc_no_data_or_no_ack_use_min(काष्ठा ieee80211_tx_rate_control *txrc)
अणु
	काष्ठा sk_buff *skb = txrc->skb;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	__le16 fc;

	fc = hdr->frame_control;

	वापस (info->flags & (IEEE80211_TX_CTL_NO_ACK |
			       IEEE80211_TX_CTL_USE_MINRATE)) ||
		!ieee80211_is_data(fc);
पूर्ण

अटल व्योम rc_send_low_basicrate(काष्ठा ieee80211_tx_rate *rate,
				  u32 basic_rates,
				  काष्ठा ieee80211_supported_band *sband)
अणु
	u8 i;

	अगर (sband->band == NL80211_BAND_S1GHZ) अणु
		/* TODO */
		rate->flags |= IEEE80211_TX_RC_S1G_MCS;
		rate->idx = 0;
		वापस;
	पूर्ण

	अगर (basic_rates == 0)
		वापस; /* assume basic rates unknown and accept rate */
	अगर (rate->idx < 0)
		वापस;
	अगर (basic_rates & (1 << rate->idx))
		वापस; /* selected rate is a basic rate */

	क्रम (i = rate->idx + 1; i <= sband->n_bitrates; i++) अणु
		अगर (basic_rates & (1 << i)) अणु
			rate->idx = i;
			वापस;
		पूर्ण
	पूर्ण

	/* could not find a basic rate; use original selection */
पूर्ण

अटल व्योम __rate_control_send_low(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_supported_band *sband,
				    काष्ठा ieee80211_sta *sta,
				    काष्ठा ieee80211_tx_info *info,
				    u32 rate_mask)
अणु
	पूर्णांक i;
	u32 rate_flags =
		ieee80211_chandef_rate_flags(&hw->conf.chandef);

	अगर (sband->band == NL80211_BAND_S1GHZ) अणु
		info->control.rates[0].flags |= IEEE80211_TX_RC_S1G_MCS;
		info->control.rates[0].idx = 0;
		वापस;
	पूर्ण

	अगर ((sband->band == NL80211_BAND_2GHZ) &&
	    (info->flags & IEEE80211_TX_CTL_NO_CCK_RATE))
		rate_flags |= IEEE80211_RATE_ERP_G;

	info->control.rates[0].idx = 0;
	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		अगर (!(rate_mask & BIT(i)))
			जारी;

		अगर ((rate_flags & sband->bitrates[i].flags) != rate_flags)
			जारी;

		अगर (!rate_supported(sta, sband->band, i))
			जारी;

		info->control.rates[0].idx = i;
		अवरोध;
	पूर्ण
	WARN_ONCE(i == sband->n_bitrates,
		  "no supported rates for sta %pM (0x%x, band %d) in rate_mask 0x%x with flags 0x%x\n",
		  sta ? sta->addr : शून्य,
		  sta ? sta->supp_rates[sband->band] : -1,
		  sband->band,
		  rate_mask, rate_flags);

	info->control.rates[0].count =
		(info->flags & IEEE80211_TX_CTL_NO_ACK) ?
		1 : hw->max_rate_tries;

	info->control.skip_table = 1;
पूर्ण


अटल bool rate_control_send_low(काष्ठा ieee80211_sta *pubsta,
				  काष्ठा ieee80211_tx_rate_control *txrc)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(txrc->skb);
	काष्ठा ieee80211_supported_band *sband = txrc->sband;
	काष्ठा sta_info *sta;
	पूर्णांक mcast_rate;
	bool use_basicrate = false;

	अगर (!pubsta || rc_no_data_or_no_ack_use_min(txrc)) अणु
		__rate_control_send_low(txrc->hw, sband, pubsta, info,
					txrc->rate_idx_mask);

		अगर (!pubsta && txrc->bss) अणु
			mcast_rate = txrc->bss_conf->mcast_rate[sband->band];
			अगर (mcast_rate > 0) अणु
				info->control.rates[0].idx = mcast_rate - 1;
				वापस true;
			पूर्ण
			use_basicrate = true;
		पूर्ण अन्यथा अगर (pubsta) अणु
			sta = container_of(pubsta, काष्ठा sta_info, sta);
			अगर (ieee80211_vअगर_is_mesh(&sta->sdata->vअगर))
				use_basicrate = true;
		पूर्ण

		अगर (use_basicrate)
			rc_send_low_basicrate(&info->control.rates[0],
					      txrc->bss_conf->basic_rates,
					      sband);

		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool rate_idx_match_legacy_mask(s8 *rate_idx, पूर्णांक n_bitrates, u32 mask)
अणु
	पूर्णांक j;

	/* See whether the selected rate or anything below it is allowed. */
	क्रम (j = *rate_idx; j >= 0; j--) अणु
		अगर (mask & (1 << j)) अणु
			/* Okay, found a suitable rate. Use it. */
			*rate_idx = j;
			वापस true;
		पूर्ण
	पूर्ण

	/* Try to find a higher rate that would be allowed */
	क्रम (j = *rate_idx + 1; j < n_bitrates; j++) अणु
		अगर (mask & (1 << j)) अणु
			/* Okay, found a suitable rate. Use it. */
			*rate_idx = j;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल bool rate_idx_match_mcs_mask(s8 *rate_idx, u8 *mcs_mask)
अणु
	पूर्णांक i, j;
	पूर्णांक ridx, rbit;

	ridx = *rate_idx / 8;
	rbit = *rate_idx % 8;

	/* sanity check */
	अगर (ridx < 0 || ridx >= IEEE80211_HT_MCS_MASK_LEN)
		वापस false;

	/* See whether the selected rate or anything below it is allowed. */
	क्रम (i = ridx; i >= 0; i--) अणु
		क्रम (j = rbit; j >= 0; j--)
			अगर (mcs_mask[i] & BIT(j)) अणु
				*rate_idx = i * 8 + j;
				वापस true;
			पूर्ण
		rbit = 7;
	पूर्ण

	/* Try to find a higher rate that would be allowed */
	ridx = (*rate_idx + 1) / 8;
	rbit = (*rate_idx + 1) % 8;

	क्रम (i = ridx; i < IEEE80211_HT_MCS_MASK_LEN; i++) अणु
		क्रम (j = rbit; j < 8; j++)
			अगर (mcs_mask[i] & BIT(j)) अणु
				*rate_idx = i * 8 + j;
				वापस true;
			पूर्ण
		rbit = 0;
	पूर्ण
	वापस false;
पूर्ण

अटल bool rate_idx_match_vht_mcs_mask(s8 *rate_idx, u16 *vht_mask)
अणु
	पूर्णांक i, j;
	पूर्णांक ridx, rbit;

	ridx = *rate_idx >> 4;
	rbit = *rate_idx & 0xf;

	अगर (ridx < 0 || ridx >= NL80211_VHT_NSS_MAX)
		वापस false;

	/* See whether the selected rate or anything below it is allowed. */
	क्रम (i = ridx; i >= 0; i--) अणु
		क्रम (j = rbit; j >= 0; j--) अणु
			अगर (vht_mask[i] & BIT(j)) अणु
				*rate_idx = (i << 4) | j;
				वापस true;
			पूर्ण
		पूर्ण
		rbit = 15;
	पूर्ण

	/* Try to find a higher rate that would be allowed */
	ridx = (*rate_idx + 1) >> 4;
	rbit = (*rate_idx + 1) & 0xf;

	क्रम (i = ridx; i < NL80211_VHT_NSS_MAX; i++) अणु
		क्रम (j = rbit; j < 16; j++) अणु
			अगर (vht_mask[i] & BIT(j)) अणु
				*rate_idx = (i << 4) | j;
				वापस true;
			पूर्ण
		पूर्ण
		rbit = 0;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम rate_idx_match_mask(s8 *rate_idx, u16 *rate_flags,
				काष्ठा ieee80211_supported_band *sband,
				क्रमागत nl80211_chan_width chan_width,
				u32 mask,
				u8 mcs_mask[IEEE80211_HT_MCS_MASK_LEN],
				u16 vht_mask[NL80211_VHT_NSS_MAX])
अणु
	अगर (*rate_flags & IEEE80211_TX_RC_VHT_MCS) अणु
		/* handle VHT rates */
		अगर (rate_idx_match_vht_mcs_mask(rate_idx, vht_mask))
			वापस;

		*rate_idx = 0;
		/* keep protection flags */
		*rate_flags &= (IEEE80211_TX_RC_USE_RTS_CTS |
				IEEE80211_TX_RC_USE_CTS_PROTECT |
				IEEE80211_TX_RC_USE_SHORT_PREAMBLE);

		*rate_flags |= IEEE80211_TX_RC_MCS;
		अगर (chan_width == NL80211_CHAN_WIDTH_40)
			*rate_flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;

		अगर (rate_idx_match_mcs_mask(rate_idx, mcs_mask))
			वापस;

		/* also try the legacy rates. */
		*rate_flags &= ~(IEEE80211_TX_RC_MCS |
				 IEEE80211_TX_RC_40_MHZ_WIDTH);
		अगर (rate_idx_match_legacy_mask(rate_idx, sband->n_bitrates,
					       mask))
			वापस;
	पूर्ण अन्यथा अगर (*rate_flags & IEEE80211_TX_RC_MCS) अणु
		/* handle HT rates */
		अगर (rate_idx_match_mcs_mask(rate_idx, mcs_mask))
			वापस;

		/* also try the legacy rates. */
		*rate_idx = 0;
		/* keep protection flags */
		*rate_flags &= (IEEE80211_TX_RC_USE_RTS_CTS |
				IEEE80211_TX_RC_USE_CTS_PROTECT |
				IEEE80211_TX_RC_USE_SHORT_PREAMBLE);
		अगर (rate_idx_match_legacy_mask(rate_idx, sband->n_bitrates,
					       mask))
			वापस;
	पूर्ण अन्यथा अणु
		/* handle legacy rates */
		अगर (rate_idx_match_legacy_mask(rate_idx, sband->n_bitrates,
					       mask))
			वापस;

		/* अगर HT BSS, and we handle a data frame, also try HT rates */
		चयन (chan_width) अणु
		हाल NL80211_CHAN_WIDTH_20_NOHT:
		हाल NL80211_CHAN_WIDTH_5:
		हाल NL80211_CHAN_WIDTH_10:
			वापस;
		शेष:
			अवरोध;
		पूर्ण

		*rate_idx = 0;
		/* keep protection flags */
		*rate_flags &= (IEEE80211_TX_RC_USE_RTS_CTS |
				IEEE80211_TX_RC_USE_CTS_PROTECT |
				IEEE80211_TX_RC_USE_SHORT_PREAMBLE);

		*rate_flags |= IEEE80211_TX_RC_MCS;

		अगर (chan_width == NL80211_CHAN_WIDTH_40)
			*rate_flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;

		अगर (rate_idx_match_mcs_mask(rate_idx, mcs_mask))
			वापस;
	पूर्ण

	/*
	 * Uh.. No suitable rate exists. This should not really happen with
	 * sane TX rate mask configurations. However, should someone manage to
	 * configure supported rates and TX rate mask in incompatible way,
	 * allow the frame to be transmitted with whatever the rate control
	 * selected.
	 */
पूर्ण

अटल व्योम rate_fixup_ratelist(काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_supported_band *sband,
				काष्ठा ieee80211_tx_info *info,
				काष्ठा ieee80211_tx_rate *rates,
				पूर्णांक max_rates)
अणु
	काष्ठा ieee80211_rate *rate;
	bool inval = false;
	पूर्णांक i;

	/*
	 * Set up the RTS/CTS rate as the fastest basic rate
	 * that is not faster than the data rate unless there
	 * is no basic rate slower than the data rate, in which
	 * हाल we pick the slowest basic rate
	 *
	 * XXX: Should this check all retry rates?
	 */
	अगर (!(rates[0].flags &
	      (IEEE80211_TX_RC_MCS | IEEE80211_TX_RC_VHT_MCS))) अणु
		u32 basic_rates = vअगर->bss_conf.basic_rates;
		s8 baserate = basic_rates ? ffs(basic_rates) - 1 : 0;

		rate = &sband->bitrates[rates[0].idx];

		क्रम (i = 0; i < sband->n_bitrates; i++) अणु
			/* must be a basic rate */
			अगर (!(basic_rates & BIT(i)))
				जारी;
			/* must not be faster than the data rate */
			अगर (sband->bitrates[i].bitrate > rate->bitrate)
				जारी;
			/* maximum */
			अगर (sband->bitrates[baserate].bitrate <
			     sband->bitrates[i].bitrate)
				baserate = i;
		पूर्ण

		info->control.rts_cts_rate_idx = baserate;
	पूर्ण

	क्रम (i = 0; i < max_rates; i++) अणु
		/*
		 * make sure there's no valid rate following
		 * an invalid one, just in हाल drivers करोn't
		 * take the API seriously to stop at -1.
		 */
		अगर (inval) अणु
			rates[i].idx = -1;
			जारी;
		पूर्ण
		अगर (rates[i].idx < 0) अणु
			inval = true;
			जारी;
		पूर्ण

		/*
		 * For now assume MCS is alपढ़ोy set up correctly, this
		 * needs to be fixed.
		 */
		अगर (rates[i].flags & IEEE80211_TX_RC_MCS) अणु
			WARN_ON(rates[i].idx > 76);

			अगर (!(rates[i].flags & IEEE80211_TX_RC_USE_RTS_CTS) &&
			    info->control.use_cts_prot)
				rates[i].flags |=
					IEEE80211_TX_RC_USE_CTS_PROTECT;
			जारी;
		पूर्ण

		अगर (rates[i].flags & IEEE80211_TX_RC_VHT_MCS) अणु
			WARN_ON(ieee80211_rate_get_vht_mcs(&rates[i]) > 9);
			जारी;
		पूर्ण

		/* set up RTS protection अगर desired */
		अगर (info->control.use_rts) अणु
			rates[i].flags |= IEEE80211_TX_RC_USE_RTS_CTS;
			info->control.use_cts_prot = false;
		पूर्ण

		/* RC is busted */
		अगर (WARN_ON_ONCE(rates[i].idx >= sband->n_bitrates)) अणु
			rates[i].idx = -1;
			जारी;
		पूर्ण

		rate = &sband->bitrates[rates[i].idx];

		/* set up लघु preamble */
		अगर (info->control.लघु_preamble &&
		    rate->flags & IEEE80211_RATE_SHORT_PREAMBLE)
			rates[i].flags |= IEEE80211_TX_RC_USE_SHORT_PREAMBLE;

		/* set up G protection */
		अगर (!(rates[i].flags & IEEE80211_TX_RC_USE_RTS_CTS) &&
		    info->control.use_cts_prot &&
		    rate->flags & IEEE80211_RATE_ERP_G)
			rates[i].flags |= IEEE80211_TX_RC_USE_CTS_PROTECT;
	पूर्ण
पूर्ण


अटल व्योम rate_control_fill_sta_table(काष्ठा ieee80211_sta *sta,
					काष्ठा ieee80211_tx_info *info,
					काष्ठा ieee80211_tx_rate *rates,
					पूर्णांक max_rates)
अणु
	काष्ठा ieee80211_sta_rates *ratetbl = शून्य;
	पूर्णांक i;

	अगर (sta && !info->control.skip_table)
		ratetbl = rcu_dereference(sta->rates);

	/* Fill reमुख्यing rate slots with data from the sta rate table. */
	max_rates = min_t(पूर्णांक, max_rates, IEEE80211_TX_RATE_TABLE_SIZE);
	क्रम (i = 0; i < max_rates; i++) अणु
		अगर (i < ARRAY_SIZE(info->control.rates) &&
		    info->control.rates[i].idx >= 0 &&
		    info->control.rates[i].count) अणु
			अगर (rates != info->control.rates)
				rates[i] = info->control.rates[i];
		पूर्ण अन्यथा अगर (ratetbl) अणु
			rates[i].idx = ratetbl->rate[i].idx;
			rates[i].flags = ratetbl->rate[i].flags;
			अगर (info->control.use_rts)
				rates[i].count = ratetbl->rate[i].count_rts;
			अन्यथा अगर (info->control.use_cts_prot)
				rates[i].count = ratetbl->rate[i].count_cts;
			अन्यथा
				rates[i].count = ratetbl->rate[i].count;
		पूर्ण अन्यथा अणु
			rates[i].idx = -1;
			rates[i].count = 0;
		पूर्ण

		अगर (rates[i].idx < 0 || !rates[i].count)
			अवरोध;
	पूर्ण
पूर्ण

अटल bool rate_control_cap_mask(काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा ieee80211_supported_band *sband,
				  काष्ठा ieee80211_sta *sta, u32 *mask,
				  u8 mcs_mask[IEEE80211_HT_MCS_MASK_LEN],
				  u16 vht_mask[NL80211_VHT_NSS_MAX])
अणु
	u32 i, flags;

	*mask = sdata->rc_rateidx_mask[sband->band];
	flags = ieee80211_chandef_rate_flags(&sdata->vअगर.bss_conf.chandef);
	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		अगर ((flags & sband->bitrates[i].flags) != flags)
			*mask &= ~BIT(i);
	पूर्ण

	अगर (*mask == (1 << sband->n_bitrates) - 1 &&
	    !sdata->rc_has_mcs_mask[sband->band] &&
	    !sdata->rc_has_vht_mcs_mask[sband->band])
		वापस false;

	अगर (sdata->rc_has_mcs_mask[sband->band])
		स_नकल(mcs_mask, sdata->rc_rateidx_mcs_mask[sband->band],
		       IEEE80211_HT_MCS_MASK_LEN);
	अन्यथा
		स_रखो(mcs_mask, 0xff, IEEE80211_HT_MCS_MASK_LEN);

	अगर (sdata->rc_has_vht_mcs_mask[sband->band])
		स_नकल(vht_mask, sdata->rc_rateidx_vht_mcs_mask[sband->band],
		       माप(u16) * NL80211_VHT_NSS_MAX);
	अन्यथा
		स_रखो(vht_mask, 0xff, माप(u16) * NL80211_VHT_NSS_MAX);

	अगर (sta) अणु
		__le16 sta_vht_cap;
		u16 sta_vht_mask[NL80211_VHT_NSS_MAX];

		/* Filter out rates that the STA करोes not support */
		*mask &= sta->supp_rates[sband->band];
		क्रम (i = 0; i < IEEE80211_HT_MCS_MASK_LEN; i++)
			mcs_mask[i] &= sta->ht_cap.mcs.rx_mask[i];

		sta_vht_cap = sta->vht_cap.vht_mcs.rx_mcs_map;
		ieee80211_get_vht_mask_from_cap(sta_vht_cap, sta_vht_mask);
		क्रम (i = 0; i < NL80211_VHT_NSS_MAX; i++)
			vht_mask[i] &= sta_vht_mask[i];
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम
rate_control_apply_mask_ratetbl(काष्ठा sta_info *sta,
				काष्ठा ieee80211_supported_band *sband,
				काष्ठा ieee80211_sta_rates *rates)
अणु
	पूर्णांक i;
	u32 mask;
	u8 mcs_mask[IEEE80211_HT_MCS_MASK_LEN];
	u16 vht_mask[NL80211_VHT_NSS_MAX];
	क्रमागत nl80211_chan_width chan_width;

	अगर (!rate_control_cap_mask(sta->sdata, sband, &sta->sta, &mask,
				   mcs_mask, vht_mask))
		वापस;

	chan_width = sta->sdata->vअगर.bss_conf.chandef.width;
	क्रम (i = 0; i < IEEE80211_TX_RATE_TABLE_SIZE; i++) अणु
		अगर (rates->rate[i].idx < 0)
			अवरोध;

		rate_idx_match_mask(&rates->rate[i].idx, &rates->rate[i].flags,
				    sband, chan_width, mask, mcs_mask,
				    vht_mask);
	पूर्ण
पूर्ण

अटल व्योम rate_control_apply_mask(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा ieee80211_sta *sta,
				    काष्ठा ieee80211_supported_band *sband,
				    काष्ठा ieee80211_tx_rate *rates,
				    पूर्णांक max_rates)
अणु
	क्रमागत nl80211_chan_width chan_width;
	u8 mcs_mask[IEEE80211_HT_MCS_MASK_LEN];
	u32 mask;
	u16 rate_flags, vht_mask[NL80211_VHT_NSS_MAX];
	पूर्णांक i;

	/*
	 * Try to enक्रमce the rateidx mask the user wanted. skip this अगर the
	 * शेष mask (allow all rates) is used to save some processing क्रम
	 * the common हाल.
	 */
	अगर (!rate_control_cap_mask(sdata, sband, sta, &mask, mcs_mask,
				   vht_mask))
		वापस;

	/*
	 * Make sure the rate index selected क्रम each TX rate is
	 * included in the configured mask and change the rate indexes
	 * अगर needed.
	 */
	chan_width = sdata->vअगर.bss_conf.chandef.width;
	क्रम (i = 0; i < max_rates; i++) अणु
		/* Skip invalid rates */
		अगर (rates[i].idx < 0)
			अवरोध;

		rate_flags = rates[i].flags;
		rate_idx_match_mask(&rates[i].idx, &rate_flags, sband,
				    chan_width, mask, mcs_mask, vht_mask);
		rates[i].flags = rate_flags;
	पूर्ण
पूर्ण

व्योम ieee80211_get_tx_rates(काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta,
			    काष्ठा sk_buff *skb,
			    काष्ठा ieee80211_tx_rate *dest,
			    पूर्णांक max_rates)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_supported_band *sband;

	rate_control_fill_sta_table(sta, info, dest, max_rates);

	अगर (!vअगर)
		वापस;

	sdata = vअगर_to_sdata(vअगर);
	sband = sdata->local->hw.wiphy->bands[info->band];

	अगर (ieee80211_is_data(hdr->frame_control))
		rate_control_apply_mask(sdata, sta, sband, dest, max_rates);

	अगर (dest[0].idx < 0)
		__rate_control_send_low(&sdata->local->hw, sband, sta, info,
					sdata->rc_rateidx_mask[info->band]);

	अगर (sta)
		rate_fixup_ratelist(vअगर, sband, info, dest, max_rates);
पूर्ण
EXPORT_SYMBOL(ieee80211_get_tx_rates);

व्योम rate_control_get_rate(काष्ठा ieee80211_sub_अगर_data *sdata,
			   काष्ठा sta_info *sta,
			   काष्ठा ieee80211_tx_rate_control *txrc)
अणु
	काष्ठा rate_control_ref *ref = sdata->local->rate_ctrl;
	व्योम *priv_sta = शून्य;
	काष्ठा ieee80211_sta *ista = शून्य;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(txrc->skb);
	पूर्णांक i;

	क्रम (i = 0; i < IEEE80211_TX_MAX_RATES; i++) अणु
		info->control.rates[i].idx = -1;
		info->control.rates[i].flags = 0;
		info->control.rates[i].count = 0;
	पूर्ण

	अगर (rate_control_send_low(sta ? &sta->sta : शून्य, txrc))
		वापस;

	अगर (ieee80211_hw_check(&sdata->local->hw, HAS_RATE_CONTROL))
		वापस;

	अगर (sta && test_sta_flag(sta, WLAN_STA_RATE_CONTROL)) अणु
		ista = &sta->sta;
		priv_sta = sta->rate_ctrl_priv;
	पूर्ण

	अगर (ista) अणु
		spin_lock_bh(&sta->rate_ctrl_lock);
		ref->ops->get_rate(ref->priv, ista, priv_sta, txrc);
		spin_unlock_bh(&sta->rate_ctrl_lock);
	पूर्ण अन्यथा अणु
		rate_control_send_low(शून्य, txrc);
	पूर्ण

	अगर (ieee80211_hw_check(&sdata->local->hw, SUPPORTS_RC_TABLE))
		वापस;

	ieee80211_get_tx_rates(&sdata->vअगर, ista, txrc->skb,
			       info->control.rates,
			       ARRAY_SIZE(info->control.rates));
पूर्ण

पूर्णांक rate_control_set_rates(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_sta *pubsta,
			   काष्ठा ieee80211_sta_rates *rates)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);
	काष्ठा ieee80211_sta_rates *old;
	काष्ठा ieee80211_supported_band *sband;

	sband = ieee80211_get_sband(sta->sdata);
	अगर (!sband)
		वापस -EINVAL;
	rate_control_apply_mask_ratetbl(sta, sband, rates);
	/*
	 * mac80211 guarantees that this function will not be called
	 * concurrently, so the following RCU access is safe, even without
	 * extra locking. This can not be checked easily, so we just set
	 * the condition to true.
	 */
	old = rcu_dereference_रक्षित(pubsta->rates, true);
	rcu_assign_poपूर्णांकer(pubsta->rates, rates);
	अगर (old)
		kमुक्त_rcu(old, rcu_head);

	अगर (sta->uploaded)
		drv_sta_rate_tbl_update(hw_to_local(hw), sta->sdata, pubsta);

	ieee80211_sta_set_expected_throughput(pubsta, sta_get_expected_throughput(sta));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rate_control_set_rates);

पूर्णांक ieee80211_init_rate_ctrl_alg(काष्ठा ieee80211_local *local,
				 स्थिर अक्षर *name)
अणु
	काष्ठा rate_control_ref *ref;

	ASSERT_RTNL();

	अगर (local->खोलो_count)
		वापस -EBUSY;

	अगर (ieee80211_hw_check(&local->hw, HAS_RATE_CONTROL)) अणु
		अगर (WARN_ON(!local->ops->set_rts_threshold))
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	ref = rate_control_alloc(name, local);
	अगर (!ref) अणु
		wiphy_warn(local->hw.wiphy,
			   "Failed to select rate control algorithm\n");
		वापस -ENOENT;
	पूर्ण

	WARN_ON(local->rate_ctrl);
	local->rate_ctrl = ref;

	wiphy_debug(local->hw.wiphy, "Selected rate control algorithm '%s'\n",
		    ref->ops->name);

	वापस 0;
पूर्ण

व्योम rate_control_deinitialize(काष्ठा ieee80211_local *local)
अणु
	काष्ठा rate_control_ref *ref;

	ref = local->rate_ctrl;

	अगर (!ref)
		वापस;

	local->rate_ctrl = शून्य;
	rate_control_मुक्त(local, ref);
पूर्ण
