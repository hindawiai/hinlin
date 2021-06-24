<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 * Copyright 2007	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright (C) 2015-2017	Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 *
 * utilities क्रम mac80211
 */

#समावेश <net/mac80211.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/crc32.h>
#समावेश <net/net_namespace.h>
#समावेश <net/cfg80211.h>
#समावेश <net/rtnetlink.h>

#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "rate.h"
#समावेश "mesh.h"
#समावेश "wme.h"
#समावेश "led.h"
#समावेश "wep.h"

/* privid क्रम wiphys to determine whether they beदीर्घ to us or not */
स्थिर व्योम *स्थिर mac80211_wiphy_privid = &mac80211_wiphy_privid;

काष्ठा ieee80211_hw *wiphy_to_ieee80211_hw(काष्ठा wiphy *wiphy)
अणु
	काष्ठा ieee80211_local *local;

	local = wiphy_priv(wiphy);
	वापस &local->hw;
पूर्ण
EXPORT_SYMBOL(wiphy_to_ieee80211_hw);

u8 *ieee80211_get_bssid(काष्ठा ieee80211_hdr *hdr, माप_प्रकार len,
			क्रमागत nl80211_अगरtype type)
अणु
	__le16 fc = hdr->frame_control;

	अगर (ieee80211_is_data(fc)) अणु
		अगर (len < 24) /* drop incorrect hdr len (data) */
			वापस शून्य;

		अगर (ieee80211_has_a4(fc))
			वापस शून्य;
		अगर (ieee80211_has_tods(fc))
			वापस hdr->addr1;
		अगर (ieee80211_has_fromds(fc))
			वापस hdr->addr2;

		वापस hdr->addr3;
	पूर्ण

	अगर (ieee80211_is_s1g_beacon(fc)) अणु
		काष्ठा ieee80211_ext *ext = (व्योम *) hdr;

		वापस ext->u.s1g_beacon.sa;
	पूर्ण

	अगर (ieee80211_is_mgmt(fc)) अणु
		अगर (len < 24) /* drop incorrect hdr len (mgmt) */
			वापस शून्य;
		वापस hdr->addr3;
	पूर्ण

	अगर (ieee80211_is_ctl(fc)) अणु
		अगर (ieee80211_is_pspoll(fc))
			वापस hdr->addr1;

		अगर (ieee80211_is_back_req(fc)) अणु
			चयन (type) अणु
			हाल NL80211_IFTYPE_STATION:
				वापस hdr->addr2;
			हाल NL80211_IFTYPE_AP:
			हाल NL80211_IFTYPE_AP_VLAN:
				वापस hdr->addr1;
			शेष:
				अवरोध; /* fall through to the वापस */
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(ieee80211_get_bssid);

व्योम ieee80211_tx_set_रक्षित(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr *hdr;

	skb_queue_walk(&tx->skbs, skb) अणु
		hdr = (काष्ठा ieee80211_hdr *) skb->data;
		hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_PROTECTED);
	पूर्ण
पूर्ण

पूर्णांक ieee80211_frame_duration(क्रमागत nl80211_band band, माप_प्रकार len,
			     पूर्णांक rate, पूर्णांक erp, पूर्णांक लघु_preamble,
			     पूर्णांक shअगरt)
अणु
	पूर्णांक dur;

	/* calculate duration (in microseconds, rounded up to next higher
	 * पूर्णांकeger अगर it includes a fractional microsecond) to send frame of
	 * len bytes (करोes not include FCS) at the given rate. Duration will
	 * also include SIFS.
	 *
	 * rate is in 100 kbps, so भागident is multiplied by 10 in the
	 * DIV_ROUND_UP() operations.
	 *
	 * shअगरt may be 2 क्रम 5 MHz channels or 1 क्रम 10 MHz channels, and
	 * is assumed to be 0 otherwise.
	 */

	अगर (band == NL80211_BAND_5GHZ || erp) अणु
		/*
		 * OFDM:
		 *
		 * N_DBPS = DATARATE x 4
		 * N_SYM = Ceiling((16+8xLENGTH+6) / N_DBPS)
		 *	(16 = SIGNAL समय, 6 = tail bits)
		 * TXTIME = T_PREAMBLE + T_SIGNAL + T_SYM x N_SYM + Signal Ext
		 *
		 * T_SYM = 4 usec
		 * 802.11a - 18.5.2: aSIFSTime = 16 usec
		 * 802.11g - 19.8.4: aSIFSTime = 10 usec +
		 *	संकेत ext = 6 usec
		 */
		dur = 16; /* SIFS + संकेत ext */
		dur += 16; /* IEEE 802.11-2012 18.3.2.4: T_PREAMBLE = 16 usec */
		dur += 4; /* IEEE 802.11-2012 18.3.2.4: T_SIGNAL = 4 usec */

		/* IEEE 802.11-2012 18.3.2.4: all values above are:
		 *  * बार 4 क्रम 5 MHz
		 *  * बार 2 क्रम 10 MHz
		 */
		dur *= 1 << shअगरt;

		/* rates should alपढ़ोy consider the channel bandwidth,
		 * करोn't apply भागisor again.
		 */
		dur += 4 * DIV_ROUND_UP((16 + 8 * (len + 4) + 6) * 10,
					4 * rate); /* T_SYM x N_SYM */
	पूर्ण अन्यथा अणु
		/*
		 * 802.11b or 802.11g with 802.11b compatibility:
		 * 18.3.4: TXTIME = PreambleLength + PLCPHeaderTime +
		 * Ceiling(((LENGTH+PBCC)x8)/DATARATE). PBCC=0.
		 *
		 * 802.11 (DS): 15.3.3, 802.11b: 18.3.4
		 * aSIFSTime = 10 usec
		 * aPreambleLength = 144 usec or 72 usec with लघु preamble
		 * aPLCPHeaderLength = 48 usec or 24 usec with लघु preamble
		 */
		dur = 10; /* aSIFSTime = 10 usec */
		dur += लघु_preamble ? (72 + 24) : (144 + 48);

		dur += DIV_ROUND_UP(8 * (len + 4) * 10, rate);
	पूर्ण

	वापस dur;
पूर्ण

/* Exported duration function क्रम driver use */
__le16 ieee80211_generic_frame_duration(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर,
					क्रमागत nl80211_band band,
					माप_प्रकार frame_len,
					काष्ठा ieee80211_rate *rate)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	u16 dur;
	पूर्णांक erp, shअगरt = 0;
	bool लघु_preamble = false;

	erp = 0;
	अगर (vअगर) अणु
		sdata = vअगर_to_sdata(vअगर);
		लघु_preamble = sdata->vअगर.bss_conf.use_लघु_preamble;
		अगर (sdata->flags & IEEE80211_SDATA_OPERATING_GMODE)
			erp = rate->flags & IEEE80211_RATE_ERP_G;
		shअगरt = ieee80211_vअगर_get_shअगरt(vअगर);
	पूर्ण

	dur = ieee80211_frame_duration(band, frame_len, rate->bitrate, erp,
				       लघु_preamble, shअगरt);

	वापस cpu_to_le16(dur);
पूर्ण
EXPORT_SYMBOL(ieee80211_generic_frame_duration);

__le16 ieee80211_rts_duration(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर, माप_प्रकार frame_len,
			      स्थिर काष्ठा ieee80211_tx_info *frame_txctl)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_rate *rate;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	bool लघु_preamble;
	पूर्णांक erp, shअगरt = 0, bitrate;
	u16 dur;
	काष्ठा ieee80211_supported_band *sband;

	sband = local->hw.wiphy->bands[frame_txctl->band];

	लघु_preamble = false;

	rate = &sband->bitrates[frame_txctl->control.rts_cts_rate_idx];

	erp = 0;
	अगर (vअगर) अणु
		sdata = vअगर_to_sdata(vअगर);
		लघु_preamble = sdata->vअगर.bss_conf.use_लघु_preamble;
		अगर (sdata->flags & IEEE80211_SDATA_OPERATING_GMODE)
			erp = rate->flags & IEEE80211_RATE_ERP_G;
		shअगरt = ieee80211_vअगर_get_shअगरt(vअगर);
	पूर्ण

	bitrate = DIV_ROUND_UP(rate->bitrate, 1 << shअगरt);

	/* CTS duration */
	dur = ieee80211_frame_duration(sband->band, 10, bitrate,
				       erp, लघु_preamble, shअगरt);
	/* Data frame duration */
	dur += ieee80211_frame_duration(sband->band, frame_len, bitrate,
					erp, लघु_preamble, shअगरt);
	/* ACK duration */
	dur += ieee80211_frame_duration(sband->band, 10, bitrate,
					erp, लघु_preamble, shअगरt);

	वापस cpu_to_le16(dur);
पूर्ण
EXPORT_SYMBOL(ieee80211_rts_duration);

__le16 ieee80211_ctstoself_duration(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    माप_प्रकार frame_len,
				    स्थिर काष्ठा ieee80211_tx_info *frame_txctl)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_rate *rate;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	bool लघु_preamble;
	पूर्णांक erp, shअगरt = 0, bitrate;
	u16 dur;
	काष्ठा ieee80211_supported_band *sband;

	sband = local->hw.wiphy->bands[frame_txctl->band];

	लघु_preamble = false;

	rate = &sband->bitrates[frame_txctl->control.rts_cts_rate_idx];
	erp = 0;
	अगर (vअगर) अणु
		sdata = vअगर_to_sdata(vअगर);
		लघु_preamble = sdata->vअगर.bss_conf.use_लघु_preamble;
		अगर (sdata->flags & IEEE80211_SDATA_OPERATING_GMODE)
			erp = rate->flags & IEEE80211_RATE_ERP_G;
		shअगरt = ieee80211_vअगर_get_shअगरt(vअगर);
	पूर्ण

	bitrate = DIV_ROUND_UP(rate->bitrate, 1 << shअगरt);

	/* Data frame duration */
	dur = ieee80211_frame_duration(sband->band, frame_len, bitrate,
				       erp, लघु_preamble, shअगरt);
	अगर (!(frame_txctl->flags & IEEE80211_TX_CTL_NO_ACK)) अणु
		/* ACK duration */
		dur += ieee80211_frame_duration(sband->band, 10, bitrate,
						erp, लघु_preamble, shअगरt);
	पूर्ण

	वापस cpu_to_le16(dur);
पूर्ण
EXPORT_SYMBOL(ieee80211_ctstoself_duration);

अटल व्योम __ieee80211_wake_txqs(काष्ठा ieee80211_sub_अगर_data *sdata, पूर्णांक ac)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_vअगर *vअगर = &sdata->vअगर;
	काष्ठा fq *fq = &local->fq;
	काष्ठा ps_data *ps = शून्य;
	काष्ठा txq_info *txqi;
	काष्ठा sta_info *sta;
	पूर्णांक i;

	local_bh_disable();
	spin_lock(&fq->lock);

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
		ps = &sdata->bss->ps;

	sdata->vअगर.txqs_stopped[ac] = false;

	list_क्रम_each_entry_rcu(sta, &local->sta_list, list) अणु
		अगर (sdata != sta->sdata)
			जारी;

		क्रम (i = 0; i < ARRAY_SIZE(sta->sta.txq); i++) अणु
			काष्ठा ieee80211_txq *txq = sta->sta.txq[i];

			अगर (!txq)
				जारी;

			txqi = to_txq_info(txq);

			अगर (ac != txq->ac)
				जारी;

			अगर (!test_and_clear_bit(IEEE80211_TXQ_STOP_NETIF_TX,
						&txqi->flags))
				जारी;

			spin_unlock(&fq->lock);
			drv_wake_tx_queue(local, txqi);
			spin_lock(&fq->lock);
		पूर्ण
	पूर्ण

	अगर (!vअगर->txq)
		जाओ out;

	txqi = to_txq_info(vअगर->txq);

	अगर (!test_and_clear_bit(IEEE80211_TXQ_STOP_NETIF_TX, &txqi->flags) ||
	    (ps && atomic_पढ़ो(&ps->num_sta_ps)) || ac != vअगर->txq->ac)
		जाओ out;

	spin_unlock(&fq->lock);

	drv_wake_tx_queue(local, txqi);
	local_bh_enable();
	वापस;
out:
	spin_unlock(&fq->lock);
	local_bh_enable();
पूर्ण

अटल व्योम
__releases(&local->queue_stop_reason_lock)
__acquires(&local->queue_stop_reason_lock)
_ieee80211_wake_txqs(काष्ठा ieee80211_local *local, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	पूर्णांक n_acs = IEEE80211_NUM_ACS;
	पूर्णांक i;

	rcu_पढ़ो_lock();

	अगर (local->hw.queues < IEEE80211_NUM_ACS)
		n_acs = 1;

	क्रम (i = 0; i < local->hw.queues; i++) अणु
		अगर (local->queue_stop_reasons[i])
			जारी;

		spin_unlock_irqrestore(&local->queue_stop_reason_lock, *flags);
		list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
			पूर्णांक ac;

			क्रम (ac = 0; ac < n_acs; ac++) अणु
				पूर्णांक ac_queue = sdata->vअगर.hw_queue[ac];

				अगर (ac_queue == i ||
				    sdata->vअगर.cab_queue == i)
					__ieee80211_wake_txqs(sdata, ac);
			पूर्ण
		पूर्ण
		spin_lock_irqsave(&local->queue_stop_reason_lock, *flags);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

व्योम ieee80211_wake_txqs(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ieee80211_local *local = from_tasklet(local, t,
						     wake_txqs_tasklet);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
	_ieee80211_wake_txqs(local, &flags);
	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);
पूर्ण

व्योम ieee80211_propagate_queue_wake(काष्ठा ieee80211_local *local, पूर्णांक queue)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	पूर्णांक n_acs = IEEE80211_NUM_ACS;

	अगर (local->ops->wake_tx_queue)
		वापस;

	अगर (local->hw.queues < IEEE80211_NUM_ACS)
		n_acs = 1;

	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		पूर्णांक ac;

		अगर (!sdata->dev)
			जारी;

		अगर (sdata->vअगर.cab_queue != IEEE80211_INVAL_HW_QUEUE &&
		    local->queue_stop_reasons[sdata->vअगर.cab_queue] != 0)
			जारी;

		क्रम (ac = 0; ac < n_acs; ac++) अणु
			पूर्णांक ac_queue = sdata->vअगर.hw_queue[ac];

			अगर (ac_queue == queue ||
			    (sdata->vअगर.cab_queue == queue &&
			     local->queue_stop_reasons[ac_queue] == 0 &&
			     skb_queue_empty(&local->pending[ac_queue])))
				netअगर_wake_subqueue(sdata->dev, ac);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __ieee80211_wake_queue(काष्ठा ieee80211_hw *hw, पूर्णांक queue,
				   क्रमागत queue_stop_reason reason,
				   bool refcounted,
				   अचिन्हित दीर्घ *flags)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	trace_wake_queue(local, queue, reason);

	अगर (WARN_ON(queue >= hw->queues))
		वापस;

	अगर (!test_bit(reason, &local->queue_stop_reasons[queue]))
		वापस;

	अगर (!refcounted) अणु
		local->q_stop_reasons[queue][reason] = 0;
	पूर्ण अन्यथा अणु
		local->q_stop_reasons[queue][reason]--;
		अगर (WARN_ON(local->q_stop_reasons[queue][reason] < 0))
			local->q_stop_reasons[queue][reason] = 0;
	पूर्ण

	अगर (local->q_stop_reasons[queue][reason] == 0)
		__clear_bit(reason, &local->queue_stop_reasons[queue]);

	अगर (local->queue_stop_reasons[queue] != 0)
		/* someone still has this queue stopped */
		वापस;

	अगर (skb_queue_empty(&local->pending[queue])) अणु
		rcu_पढ़ो_lock();
		ieee80211_propagate_queue_wake(local, queue);
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा
		tasklet_schedule(&local->tx_pending_tasklet);

	/*
	 * Calling _ieee80211_wake_txqs here can be a problem because it may
	 * release queue_stop_reason_lock which has been taken by
	 * __ieee80211_wake_queue's caller. It is certainly not very nice to
	 * release someone's lock, but it is fine because all the callers of
	 * __ieee80211_wake_queue call it right beक्रमe releasing the lock.
	 */
	अगर (local->ops->wake_tx_queue) अणु
		अगर (reason == IEEE80211_QUEUE_STOP_REASON_DRIVER)
			tasklet_schedule(&local->wake_txqs_tasklet);
		अन्यथा
			_ieee80211_wake_txqs(local, flags);
	पूर्ण
पूर्ण

व्योम ieee80211_wake_queue_by_reason(काष्ठा ieee80211_hw *hw, पूर्णांक queue,
				    क्रमागत queue_stop_reason reason,
				    bool refcounted)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
	__ieee80211_wake_queue(hw, queue, reason, refcounted, &flags);
	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);
पूर्ण

व्योम ieee80211_wake_queue(काष्ठा ieee80211_hw *hw, पूर्णांक queue)
अणु
	ieee80211_wake_queue_by_reason(hw, queue,
				       IEEE80211_QUEUE_STOP_REASON_DRIVER,
				       false);
पूर्ण
EXPORT_SYMBOL(ieee80211_wake_queue);

अटल व्योम __ieee80211_stop_queue(काष्ठा ieee80211_hw *hw, पूर्णांक queue,
				   क्रमागत queue_stop_reason reason,
				   bool refcounted)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_sub_अगर_data *sdata;
	पूर्णांक n_acs = IEEE80211_NUM_ACS;

	trace_stop_queue(local, queue, reason);

	अगर (WARN_ON(queue >= hw->queues))
		वापस;

	अगर (!refcounted)
		local->q_stop_reasons[queue][reason] = 1;
	अन्यथा
		local->q_stop_reasons[queue][reason]++;

	अगर (__test_and_set_bit(reason, &local->queue_stop_reasons[queue]))
		वापस;

	अगर (local->hw.queues < IEEE80211_NUM_ACS)
		n_acs = 1;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		पूर्णांक ac;

		अगर (!sdata->dev)
			जारी;

		क्रम (ac = 0; ac < n_acs; ac++) अणु
			अगर (sdata->vअगर.hw_queue[ac] == queue ||
			    sdata->vअगर.cab_queue == queue) अणु
				अगर (!local->ops->wake_tx_queue) अणु
					netअगर_stop_subqueue(sdata->dev, ac);
					जारी;
				पूर्ण
				spin_lock(&local->fq.lock);
				sdata->vअगर.txqs_stopped[ac] = true;
				spin_unlock(&local->fq.lock);
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम ieee80211_stop_queue_by_reason(काष्ठा ieee80211_hw *hw, पूर्णांक queue,
				    क्रमागत queue_stop_reason reason,
				    bool refcounted)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
	__ieee80211_stop_queue(hw, queue, reason, refcounted);
	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);
पूर्ण

व्योम ieee80211_stop_queue(काष्ठा ieee80211_hw *hw, पूर्णांक queue)
अणु
	ieee80211_stop_queue_by_reason(hw, queue,
				       IEEE80211_QUEUE_STOP_REASON_DRIVER,
				       false);
पूर्ण
EXPORT_SYMBOL(ieee80211_stop_queue);

व्योम ieee80211_add_pending_skb(काष्ठा ieee80211_local *local,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hw *hw = &local->hw;
	अचिन्हित दीर्घ flags;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	पूर्णांक queue = info->hw_queue;

	अगर (WARN_ON(!info->control.vअगर)) अणु
		ieee80211_मुक्त_txskb(&local->hw, skb);
		वापस;
	पूर्ण

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
	__ieee80211_stop_queue(hw, queue, IEEE80211_QUEUE_STOP_REASON_SKB_ADD,
			       false);
	__skb_queue_tail(&local->pending[queue], skb);
	__ieee80211_wake_queue(hw, queue, IEEE80211_QUEUE_STOP_REASON_SKB_ADD,
			       false, &flags);
	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);
पूर्ण

व्योम ieee80211_add_pending_skbs(काष्ठा ieee80211_local *local,
				काष्ठा sk_buff_head *skbs)
अणु
	काष्ठा ieee80211_hw *hw = &local->hw;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	पूर्णांक queue, i;

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
	जबतक ((skb = skb_dequeue(skbs))) अणु
		काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

		अगर (WARN_ON(!info->control.vअगर)) अणु
			ieee80211_मुक्त_txskb(&local->hw, skb);
			जारी;
		पूर्ण

		queue = info->hw_queue;

		__ieee80211_stop_queue(hw, queue,
				IEEE80211_QUEUE_STOP_REASON_SKB_ADD,
				false);

		__skb_queue_tail(&local->pending[queue], skb);
	पूर्ण

	क्रम (i = 0; i < hw->queues; i++)
		__ieee80211_wake_queue(hw, i,
			IEEE80211_QUEUE_STOP_REASON_SKB_ADD,
			false, &flags);
	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);
पूर्ण

व्योम ieee80211_stop_queues_by_reason(काष्ठा ieee80211_hw *hw,
				     अचिन्हित दीर्घ queues,
				     क्रमागत queue_stop_reason reason,
				     bool refcounted)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);

	क्रम_each_set_bit(i, &queues, hw->queues)
		__ieee80211_stop_queue(hw, i, reason, refcounted);

	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);
पूर्ण

व्योम ieee80211_stop_queues(काष्ठा ieee80211_hw *hw)
अणु
	ieee80211_stop_queues_by_reason(hw, IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_REASON_DRIVER,
					false);
पूर्ण
EXPORT_SYMBOL(ieee80211_stop_queues);

पूर्णांक ieee80211_queue_stopped(काष्ठा ieee80211_hw *hw, पूर्णांक queue)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (WARN_ON(queue >= hw->queues))
		वापस true;

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
	ret = test_bit(IEEE80211_QUEUE_STOP_REASON_DRIVER,
		       &local->queue_stop_reasons[queue]);
	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ieee80211_queue_stopped);

व्योम ieee80211_wake_queues_by_reason(काष्ठा ieee80211_hw *hw,
				     अचिन्हित दीर्घ queues,
				     क्रमागत queue_stop_reason reason,
				     bool refcounted)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);

	क्रम_each_set_bit(i, &queues, hw->queues)
		__ieee80211_wake_queue(hw, i, reason, refcounted, &flags);

	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);
पूर्ण

व्योम ieee80211_wake_queues(काष्ठा ieee80211_hw *hw)
अणु
	ieee80211_wake_queues_by_reason(hw, IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_REASON_DRIVER,
					false);
पूर्ण
EXPORT_SYMBOL(ieee80211_wake_queues);

अटल अचिन्हित पूर्णांक
ieee80211_get_vअगर_queues(काष्ठा ieee80211_local *local,
			 काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अचिन्हित पूर्णांक queues;

	अगर (sdata && ieee80211_hw_check(&local->hw, QUEUE_CONTROL)) अणु
		पूर्णांक ac;

		queues = 0;

		क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			queues |= BIT(sdata->vअगर.hw_queue[ac]);
		अगर (sdata->vअगर.cab_queue != IEEE80211_INVAL_HW_QUEUE)
			queues |= BIT(sdata->vअगर.cab_queue);
	पूर्ण अन्यथा अणु
		/* all queues */
		queues = BIT(local->hw.queues) - 1;
	पूर्ण

	वापस queues;
पूर्ण

व्योम __ieee80211_flush_queues(काष्ठा ieee80211_local *local,
			      काष्ठा ieee80211_sub_अगर_data *sdata,
			      अचिन्हित पूर्णांक queues, bool drop)
अणु
	अगर (!local->ops->flush)
		वापस;

	/*
	 * If no queue was set, or अगर the HW करोesn't support
	 * IEEE80211_HW_QUEUE_CONTROL - flush all queues
	 */
	अगर (!queues || !ieee80211_hw_check(&local->hw, QUEUE_CONTROL))
		queues = ieee80211_get_vअगर_queues(local, sdata);

	ieee80211_stop_queues_by_reason(&local->hw, queues,
					IEEE80211_QUEUE_STOP_REASON_FLUSH,
					false);

	drv_flush(local, sdata, queues, drop);

	ieee80211_wake_queues_by_reason(&local->hw, queues,
					IEEE80211_QUEUE_STOP_REASON_FLUSH,
					false);
पूर्ण

व्योम ieee80211_flush_queues(काष्ठा ieee80211_local *local,
			    काष्ठा ieee80211_sub_अगर_data *sdata, bool drop)
अणु
	__ieee80211_flush_queues(local, sdata, 0, drop);
पूर्ण

व्योम ieee80211_stop_vअगर_queues(काष्ठा ieee80211_local *local,
			       काष्ठा ieee80211_sub_अगर_data *sdata,
			       क्रमागत queue_stop_reason reason)
अणु
	ieee80211_stop_queues_by_reason(&local->hw,
					ieee80211_get_vअगर_queues(local, sdata),
					reason, true);
पूर्ण

व्योम ieee80211_wake_vअगर_queues(काष्ठा ieee80211_local *local,
			       काष्ठा ieee80211_sub_अगर_data *sdata,
			       क्रमागत queue_stop_reason reason)
अणु
	ieee80211_wake_queues_by_reason(&local->hw,
					ieee80211_get_vअगर_queues(local, sdata),
					reason, true);
पूर्ण

अटल व्योम __iterate_पूर्णांकerfaces(काष्ठा ieee80211_local *local,
				 u32 iter_flags,
				 व्योम (*iterator)(व्योम *data, u8 *mac,
						  काष्ठा ieee80211_vअगर *vअगर),
				 व्योम *data)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	bool active_only = iter_flags & IEEE80211_IFACE_ITER_ACTIVE;

	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		चयन (sdata->vअगर.type) अणु
		हाल NL80211_IFTYPE_MONITOR:
			अगर (!(sdata->u.mntr.flags & MONITOR_FLAG_ACTIVE))
				जारी;
			अवरोध;
		हाल NL80211_IFTYPE_AP_VLAN:
			जारी;
		शेष:
			अवरोध;
		पूर्ण
		अगर (!(iter_flags & IEEE80211_IFACE_ITER_RESUME_ALL) &&
		    active_only && !(sdata->flags & IEEE80211_SDATA_IN_DRIVER))
			जारी;
		अगर ((iter_flags & IEEE80211_IFACE_SKIP_SDATA_NOT_IN_DRIVER) &&
		    !(sdata->flags & IEEE80211_SDATA_IN_DRIVER))
			जारी;
		अगर (ieee80211_sdata_running(sdata) || !active_only)
			iterator(data, sdata->vअगर.addr,
				 &sdata->vअगर);
	पूर्ण

	sdata = rcu_dereference_check(local->monitor_sdata,
				      lockdep_is_held(&local->अगरlist_mtx) ||
				      lockdep_rtnl_is_held());
	अगर (sdata &&
	    (iter_flags & IEEE80211_IFACE_ITER_RESUME_ALL || !active_only ||
	     sdata->flags & IEEE80211_SDATA_IN_DRIVER))
		iterator(data, sdata->vअगर.addr, &sdata->vअगर);
पूर्ण

व्योम ieee80211_iterate_पूर्णांकerfaces(
	काष्ठा ieee80211_hw *hw, u32 iter_flags,
	व्योम (*iterator)(व्योम *data, u8 *mac,
			 काष्ठा ieee80211_vअगर *vअगर),
	व्योम *data)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	mutex_lock(&local->अगरlist_mtx);
	__iterate_पूर्णांकerfaces(local, iter_flags, iterator, data);
	mutex_unlock(&local->अगरlist_mtx);
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_iterate_पूर्णांकerfaces);

व्योम ieee80211_iterate_active_पूर्णांकerfaces_atomic(
	काष्ठा ieee80211_hw *hw, u32 iter_flags,
	व्योम (*iterator)(व्योम *data, u8 *mac,
			 काष्ठा ieee80211_vअगर *vअगर),
	व्योम *data)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	rcu_पढ़ो_lock();
	__iterate_पूर्णांकerfaces(local, iter_flags | IEEE80211_IFACE_ITER_ACTIVE,
			     iterator, data);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_iterate_active_पूर्णांकerfaces_atomic);

व्योम ieee80211_iterate_active_पूर्णांकerfaces_mtx(
	काष्ठा ieee80211_hw *hw, u32 iter_flags,
	व्योम (*iterator)(व्योम *data, u8 *mac,
			 काष्ठा ieee80211_vअगर *vअगर),
	व्योम *data)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	lockdep_निश्चित_wiphy(hw->wiphy);

	__iterate_पूर्णांकerfaces(local, iter_flags | IEEE80211_IFACE_ITER_ACTIVE,
			     iterator, data);
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_iterate_active_पूर्णांकerfaces_mtx);

अटल व्योम __iterate_stations(काष्ठा ieee80211_local *local,
			       व्योम (*iterator)(व्योम *data,
						काष्ठा ieee80211_sta *sta),
			       व्योम *data)
अणु
	काष्ठा sta_info *sta;

	list_क्रम_each_entry_rcu(sta, &local->sta_list, list) अणु
		अगर (!sta->uploaded)
			जारी;

		iterator(data, &sta->sta);
	पूर्ण
पूर्ण

व्योम ieee80211_iterate_stations_atomic(काष्ठा ieee80211_hw *hw,
			व्योम (*iterator)(व्योम *data,
					 काष्ठा ieee80211_sta *sta),
			व्योम *data)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	rcu_पढ़ो_lock();
	__iterate_stations(local, iterator, data);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_iterate_stations_atomic);

काष्ठा ieee80211_vअगर *wdev_to_ieee80211_vअगर(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);

	अगर (!ieee80211_sdata_running(sdata) ||
	    !(sdata->flags & IEEE80211_SDATA_IN_DRIVER))
		वापस शून्य;
	वापस &sdata->vअगर;
पूर्ण
EXPORT_SYMBOL_GPL(wdev_to_ieee80211_vअगर);

काष्ठा wireless_dev *ieee80211_vअगर_to_wdev(काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (!vअगर)
		वापस शून्य;

	वापस &vअगर_to_sdata(vअगर)->wdev;
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_vअगर_to_wdev);

/*
 * Nothing should have been stuffed पूर्णांकo the workqueue during
 * the suspend->resume cycle. Since we can't check each caller
 * of this function अगर we are alपढ़ोy quiescing / suspended,
 * check here and करोn't WARN since this can actually happen when
 * the rx path (क्रम example) is racing against __ieee80211_suspend
 * and suspending / quiescing was set after the rx path checked
 * them.
 */
अटल bool ieee80211_can_queue_work(काष्ठा ieee80211_local *local)
अणु
	अगर (local->quiescing || (local->suspended && !local->resuming)) अणु
		pr_warn("queueing ieee80211 work while going to suspend\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम ieee80211_queue_work(काष्ठा ieee80211_hw *hw, काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	अगर (!ieee80211_can_queue_work(local))
		वापस;

	queue_work(local->workqueue, work);
पूर्ण
EXPORT_SYMBOL(ieee80211_queue_work);

व्योम ieee80211_queue_delayed_work(काष्ठा ieee80211_hw *hw,
				  काष्ठा delayed_work *dwork,
				  अचिन्हित दीर्घ delay)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	अगर (!ieee80211_can_queue_work(local))
		वापस;

	queue_delayed_work(local->workqueue, dwork, delay);
पूर्ण
EXPORT_SYMBOL(ieee80211_queue_delayed_work);

अटल व्योम ieee80211_parse_extension_element(u32 *crc,
					      स्थिर काष्ठा element *elem,
					      काष्ठा ieee802_11_elems *elems)
अणु
	स्थिर व्योम *data = elem->data + 1;
	u8 len = elem->datalen - 1;

	चयन (elem->data[0]) अणु
	हाल WLAN_EID_EXT_HE_MU_EDCA:
		अगर (len >= माप(*elems->mu_edca_param_set)) अणु
			elems->mu_edca_param_set = data;
			अगर (crc)
				*crc = crc32_be(*crc, (व्योम *)elem,
						elem->datalen + 2);
		पूर्ण
		अवरोध;
	हाल WLAN_EID_EXT_HE_CAPABILITY:
		elems->he_cap = data;
		elems->he_cap_len = len;
		अवरोध;
	हाल WLAN_EID_EXT_HE_OPERATION:
		अगर (len >= माप(*elems->he_operation) &&
		    len >= ieee80211_he_oper_size(data) - 1) अणु
			अगर (crc)
				*crc = crc32_be(*crc, (व्योम *)elem,
						elem->datalen + 2);
			elems->he_operation = data;
		पूर्ण
		अवरोध;
	हाल WLAN_EID_EXT_UORA:
		अगर (len >= 1)
			elems->uora_element = data;
		अवरोध;
	हाल WLAN_EID_EXT_MAX_CHANNEL_SWITCH_TIME:
		अगर (len == 3)
			elems->max_channel_चयन_समय = data;
		अवरोध;
	हाल WLAN_EID_EXT_MULTIPLE_BSSID_CONFIGURATION:
		अगर (len >= माप(*elems->mbssid_config_ie))
			elems->mbssid_config_ie = data;
		अवरोध;
	हाल WLAN_EID_EXT_HE_SPR:
		अगर (len >= माप(*elems->he_spr) &&
		    len >= ieee80211_he_spr_size(data))
			elems->he_spr = data;
		अवरोध;
	हाल WLAN_EID_EXT_HE_6GHZ_CAPA:
		अगर (len >= माप(*elems->he_6ghz_capa))
			elems->he_6ghz_capa = data;
		अवरोध;
	पूर्ण
पूर्ण

अटल u32
_ieee802_11_parse_elems_crc(स्थिर u8 *start, माप_प्रकार len, bool action,
			    काष्ठा ieee802_11_elems *elems,
			    u64 filter, u32 crc,
			    स्थिर काष्ठा element *check_inherit)
अणु
	स्थिर काष्ठा element *elem;
	bool calc_crc = filter != 0;
	DECLARE_BITMAP(seen_elems, 256);
	स्थिर u8 *ie;

	biपंचांगap_zero(seen_elems, 256);

	क्रम_each_element(elem, start, len) अणु
		bool elem_parse_failed;
		u8 id = elem->id;
		u8 elen = elem->datalen;
		स्थिर u8 *pos = elem->data;

		अगर (check_inherit &&
		    !cfg80211_is_element_inherited(elem,
						   check_inherit))
			जारी;

		चयन (id) अणु
		हाल WLAN_EID_SSID:
		हाल WLAN_EID_SUPP_RATES:
		हाल WLAN_EID_FH_PARAMS:
		हाल WLAN_EID_DS_PARAMS:
		हाल WLAN_EID_CF_PARAMS:
		हाल WLAN_EID_TIM:
		हाल WLAN_EID_IBSS_PARAMS:
		हाल WLAN_EID_CHALLENGE:
		हाल WLAN_EID_RSN:
		हाल WLAN_EID_ERP_INFO:
		हाल WLAN_EID_EXT_SUPP_RATES:
		हाल WLAN_EID_HT_CAPABILITY:
		हाल WLAN_EID_HT_OPERATION:
		हाल WLAN_EID_VHT_CAPABILITY:
		हाल WLAN_EID_VHT_OPERATION:
		हाल WLAN_EID_MESH_ID:
		हाल WLAN_EID_MESH_CONFIG:
		हाल WLAN_EID_PEER_MGMT:
		हाल WLAN_EID_PREQ:
		हाल WLAN_EID_PREP:
		हाल WLAN_EID_PERR:
		हाल WLAN_EID_RANN:
		हाल WLAN_EID_CHANNEL_SWITCH:
		हाल WLAN_EID_EXT_CHANSWITCH_ANN:
		हाल WLAN_EID_COUNTRY:
		हाल WLAN_EID_PWR_CONSTRAINT:
		हाल WLAN_EID_TIMEOUT_INTERVAL:
		हाल WLAN_EID_SECONDARY_CHANNEL_OFFSET:
		हाल WLAN_EID_WIDE_BW_CHANNEL_SWITCH:
		हाल WLAN_EID_CHAN_SWITCH_PARAM:
		हाल WLAN_EID_EXT_CAPABILITY:
		हाल WLAN_EID_CHAN_SWITCH_TIMING:
		हाल WLAN_EID_LINK_ID:
		हाल WLAN_EID_BSS_MAX_IDLE_PERIOD:
		हाल WLAN_EID_RSNX:
		हाल WLAN_EID_S1G_BCN_COMPAT:
		हाल WLAN_EID_S1G_CAPABILITIES:
		हाल WLAN_EID_S1G_OPERATION:
		हाल WLAN_EID_AID_RESPONSE:
		हाल WLAN_EID_S1G_SHORT_BCN_INTERVAL:
		/*
		 * not listing WLAN_EID_CHANNEL_SWITCH_WRAPPER -- it seems possible
		 * that अगर the content माला_लो bigger it might be needed more than once
		 */
			अगर (test_bit(id, seen_elems)) अणु
				elems->parse_error = true;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (calc_crc && id < 64 && (filter & (1ULL << id)))
			crc = crc32_be(crc, pos - 2, elen + 2);

		elem_parse_failed = false;

		चयन (id) अणु
		हाल WLAN_EID_LINK_ID:
			अगर (elen + 2 < माप(काष्ठा ieee80211_tdls_lnkie)) अणु
				elem_parse_failed = true;
				अवरोध;
			पूर्ण
			elems->lnk_id = (व्योम *)(pos - 2);
			अवरोध;
		हाल WLAN_EID_CHAN_SWITCH_TIMING:
			अगर (elen < माप(काष्ठा ieee80211_ch_चयन_timing)) अणु
				elem_parse_failed = true;
				अवरोध;
			पूर्ण
			elems->ch_sw_timing = (व्योम *)pos;
			अवरोध;
		हाल WLAN_EID_EXT_CAPABILITY:
			elems->ext_capab = pos;
			elems->ext_capab_len = elen;
			अवरोध;
		हाल WLAN_EID_SSID:
			elems->ssid = pos;
			elems->ssid_len = elen;
			अवरोध;
		हाल WLAN_EID_SUPP_RATES:
			elems->supp_rates = pos;
			elems->supp_rates_len = elen;
			अवरोध;
		हाल WLAN_EID_DS_PARAMS:
			अगर (elen >= 1)
				elems->ds_params = pos;
			अन्यथा
				elem_parse_failed = true;
			अवरोध;
		हाल WLAN_EID_TIM:
			अगर (elen >= माप(काष्ठा ieee80211_tim_ie)) अणु
				elems->tim = (व्योम *)pos;
				elems->tim_len = elen;
			पूर्ण अन्यथा
				elem_parse_failed = true;
			अवरोध;
		हाल WLAN_EID_CHALLENGE:
			elems->challenge = pos;
			elems->challenge_len = elen;
			अवरोध;
		हाल WLAN_EID_VENDOR_SPECIFIC:
			अगर (elen >= 4 && pos[0] == 0x00 && pos[1] == 0x50 &&
			    pos[2] == 0xf2) अणु
				/* Microsoft OUI (00:50:F2) */

				अगर (calc_crc)
					crc = crc32_be(crc, pos - 2, elen + 2);

				अगर (elen >= 5 && pos[3] == 2) अणु
					/* OUI Type 2 - WMM IE */
					अगर (pos[4] == 0) अणु
						elems->wmm_info = pos;
						elems->wmm_info_len = elen;
					पूर्ण अन्यथा अगर (pos[4] == 1) अणु
						elems->wmm_param = pos;
						elems->wmm_param_len = elen;
					पूर्ण
				पूर्ण
			पूर्ण
			अवरोध;
		हाल WLAN_EID_RSN:
			elems->rsn = pos;
			elems->rsn_len = elen;
			अवरोध;
		हाल WLAN_EID_ERP_INFO:
			अगर (elen >= 1)
				elems->erp_info = pos;
			अन्यथा
				elem_parse_failed = true;
			अवरोध;
		हाल WLAN_EID_EXT_SUPP_RATES:
			elems->ext_supp_rates = pos;
			elems->ext_supp_rates_len = elen;
			अवरोध;
		हाल WLAN_EID_HT_CAPABILITY:
			अगर (elen >= माप(काष्ठा ieee80211_ht_cap))
				elems->ht_cap_elem = (व्योम *)pos;
			अन्यथा
				elem_parse_failed = true;
			अवरोध;
		हाल WLAN_EID_HT_OPERATION:
			अगर (elen >= माप(काष्ठा ieee80211_ht_operation))
				elems->ht_operation = (व्योम *)pos;
			अन्यथा
				elem_parse_failed = true;
			अवरोध;
		हाल WLAN_EID_VHT_CAPABILITY:
			अगर (elen >= माप(काष्ठा ieee80211_vht_cap))
				elems->vht_cap_elem = (व्योम *)pos;
			अन्यथा
				elem_parse_failed = true;
			अवरोध;
		हाल WLAN_EID_VHT_OPERATION:
			अगर (elen >= माप(काष्ठा ieee80211_vht_operation)) अणु
				elems->vht_operation = (व्योम *)pos;
				अगर (calc_crc)
					crc = crc32_be(crc, pos - 2, elen + 2);
				अवरोध;
			पूर्ण
			elem_parse_failed = true;
			अवरोध;
		हाल WLAN_EID_OPMODE_NOTIF:
			अगर (elen > 0) अणु
				elems->opmode_notअगर = pos;
				अगर (calc_crc)
					crc = crc32_be(crc, pos - 2, elen + 2);
				अवरोध;
			पूर्ण
			elem_parse_failed = true;
			अवरोध;
		हाल WLAN_EID_MESH_ID:
			elems->mesh_id = pos;
			elems->mesh_id_len = elen;
			अवरोध;
		हाल WLAN_EID_MESH_CONFIG:
			अगर (elen >= माप(काष्ठा ieee80211_meshconf_ie))
				elems->mesh_config = (व्योम *)pos;
			अन्यथा
				elem_parse_failed = true;
			अवरोध;
		हाल WLAN_EID_PEER_MGMT:
			elems->peering = pos;
			elems->peering_len = elen;
			अवरोध;
		हाल WLAN_EID_MESH_AWAKE_WINDOW:
			अगर (elen >= 2)
				elems->awake_winकरोw = (व्योम *)pos;
			अवरोध;
		हाल WLAN_EID_PREQ:
			elems->preq = pos;
			elems->preq_len = elen;
			अवरोध;
		हाल WLAN_EID_PREP:
			elems->prep = pos;
			elems->prep_len = elen;
			अवरोध;
		हाल WLAN_EID_PERR:
			elems->perr = pos;
			elems->perr_len = elen;
			अवरोध;
		हाल WLAN_EID_RANN:
			अगर (elen >= माप(काष्ठा ieee80211_rann_ie))
				elems->rann = (व्योम *)pos;
			अन्यथा
				elem_parse_failed = true;
			अवरोध;
		हाल WLAN_EID_CHANNEL_SWITCH:
			अगर (elen != माप(काष्ठा ieee80211_channel_sw_ie)) अणु
				elem_parse_failed = true;
				अवरोध;
			पूर्ण
			elems->ch_चयन_ie = (व्योम *)pos;
			अवरोध;
		हाल WLAN_EID_EXT_CHANSWITCH_ANN:
			अगर (elen != माप(काष्ठा ieee80211_ext_chansw_ie)) अणु
				elem_parse_failed = true;
				अवरोध;
			पूर्ण
			elems->ext_chansw_ie = (व्योम *)pos;
			अवरोध;
		हाल WLAN_EID_SECONDARY_CHANNEL_OFFSET:
			अगर (elen != माप(काष्ठा ieee80211_sec_chan_offs_ie)) अणु
				elem_parse_failed = true;
				अवरोध;
			पूर्ण
			elems->sec_chan_offs = (व्योम *)pos;
			अवरोध;
		हाल WLAN_EID_CHAN_SWITCH_PARAM:
			अगर (elen <
			    माप(*elems->mesh_chansw_params_ie)) अणु
				elem_parse_failed = true;
				अवरोध;
			पूर्ण
			elems->mesh_chansw_params_ie = (व्योम *)pos;
			अवरोध;
		हाल WLAN_EID_WIDE_BW_CHANNEL_SWITCH:
			अगर (!action ||
			    elen < माप(*elems->wide_bw_chansw_ie)) अणु
				elem_parse_failed = true;
				अवरोध;
			पूर्ण
			elems->wide_bw_chansw_ie = (व्योम *)pos;
			अवरोध;
		हाल WLAN_EID_CHANNEL_SWITCH_WRAPPER:
			अगर (action) अणु
				elem_parse_failed = true;
				अवरोध;
			पूर्ण
			/*
			 * This is a bit tricky, but as we only care about
			 * the wide bandwidth channel चयन element, so
			 * just parse it out manually.
			 */
			ie = cfg80211_find_ie(WLAN_EID_WIDE_BW_CHANNEL_SWITCH,
					      pos, elen);
			अगर (ie) अणु
				अगर (ie[1] >= माप(*elems->wide_bw_chansw_ie))
					elems->wide_bw_chansw_ie =
						(व्योम *)(ie + 2);
				अन्यथा
					elem_parse_failed = true;
			पूर्ण
			अवरोध;
		हाल WLAN_EID_COUNTRY:
			elems->country_elem = pos;
			elems->country_elem_len = elen;
			अवरोध;
		हाल WLAN_EID_PWR_CONSTRAINT:
			अगर (elen != 1) अणु
				elem_parse_failed = true;
				अवरोध;
			पूर्ण
			elems->pwr_स्थिरr_elem = pos;
			अवरोध;
		हाल WLAN_EID_CISCO_VENDOR_SPECIFIC:
			/* Lots of dअगरferent options exist, but we only care
			 * about the Dynamic Transmit Power Control element.
			 * First check क्रम the Cisco OUI, then क्रम the DTPC
			 * tag (0x00).
			 */
			अगर (elen < 4) अणु
				elem_parse_failed = true;
				अवरोध;
			पूर्ण

			अगर (pos[0] != 0x00 || pos[1] != 0x40 ||
			    pos[2] != 0x96 || pos[3] != 0x00)
				अवरोध;

			अगर (elen != 6) अणु
				elem_parse_failed = true;
				अवरोध;
			पूर्ण

			अगर (calc_crc)
				crc = crc32_be(crc, pos - 2, elen + 2);

			elems->cisco_dtpc_elem = pos;
			अवरोध;
		हाल WLAN_EID_ADDBA_EXT:
			अगर (elen < माप(काष्ठा ieee80211_addba_ext_ie)) अणु
				elem_parse_failed = true;
				अवरोध;
			पूर्ण
			elems->addba_ext_ie = (व्योम *)pos;
			अवरोध;
		हाल WLAN_EID_TIMEOUT_INTERVAL:
			अगर (elen >= माप(काष्ठा ieee80211_समयout_पूर्णांकerval_ie))
				elems->समयout_पूर्णांक = (व्योम *)pos;
			अन्यथा
				elem_parse_failed = true;
			अवरोध;
		हाल WLAN_EID_BSS_MAX_IDLE_PERIOD:
			अगर (elen >= माप(*elems->max_idle_period_ie))
				elems->max_idle_period_ie = (व्योम *)pos;
			अवरोध;
		हाल WLAN_EID_RSNX:
			elems->rsnx = pos;
			elems->rsnx_len = elen;
			अवरोध;
		हाल WLAN_EID_EXTENSION:
			ieee80211_parse_extension_element(calc_crc ?
								&crc : शून्य,
							  elem, elems);
			अवरोध;
		हाल WLAN_EID_S1G_CAPABILITIES:
			अगर (elen >= माप(*elems->s1g_capab))
				elems->s1g_capab = (व्योम *)pos;
			अन्यथा
				elem_parse_failed = true;
			अवरोध;
		हाल WLAN_EID_S1G_OPERATION:
			अगर (elen == माप(*elems->s1g_oper))
				elems->s1g_oper = (व्योम *)pos;
			अन्यथा
				elem_parse_failed = true;
			अवरोध;
		हाल WLAN_EID_S1G_BCN_COMPAT:
			अगर (elen == माप(*elems->s1g_bcn_compat))
				elems->s1g_bcn_compat = (व्योम *)pos;
			अन्यथा
				elem_parse_failed = true;
			अवरोध;
		हाल WLAN_EID_AID_RESPONSE:
			अगर (elen == माप(काष्ठा ieee80211_aid_response_ie))
				elems->aid_resp = (व्योम *)pos;
			अन्यथा
				elem_parse_failed = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (elem_parse_failed)
			elems->parse_error = true;
		अन्यथा
			__set_bit(id, seen_elems);
	पूर्ण

	अगर (!क्रम_each_element_completed(elem, start, len))
		elems->parse_error = true;

	वापस crc;
पूर्ण

अटल माप_प्रकार ieee802_11_find_bssid_profile(स्थिर u8 *start, माप_प्रकार len,
					    काष्ठा ieee802_11_elems *elems,
					    u8 *transmitter_bssid,
					    u8 *bss_bssid,
					    u8 *nontransmitted_profile)
अणु
	स्थिर काष्ठा element *elem, *sub;
	माप_प्रकार profile_len = 0;
	bool found = false;

	अगर (!bss_bssid || !transmitter_bssid)
		वापस profile_len;

	क्रम_each_element_id(elem, WLAN_EID_MULTIPLE_BSSID, start, len) अणु
		अगर (elem->datalen < 2)
			जारी;

		क्रम_each_element(sub, elem->data + 1, elem->datalen - 1) अणु
			u8 new_bssid[ETH_ALEN];
			स्थिर u8 *index;

			अगर (sub->id != 0 || sub->datalen < 4) अणु
				/* not a valid BSS profile */
				जारी;
			पूर्ण

			अगर (sub->data[0] != WLAN_EID_NON_TX_BSSID_CAP ||
			    sub->data[1] != 2) अणु
				/* The first element of the
				 * Nontransmitted BSSID Profile is not
				 * the Nontransmitted BSSID Capability
				 * element.
				 */
				जारी;
			पूर्ण

			स_रखो(nontransmitted_profile, 0, len);
			profile_len = cfg80211_merge_profile(start, len,
							     elem,
							     sub,
							     nontransmitted_profile,
							     len);

			/* found a Nontransmitted BSSID Profile */
			index = cfg80211_find_ie(WLAN_EID_MULTI_BSSID_IDX,
						 nontransmitted_profile,
						 profile_len);
			अगर (!index || index[1] < 1 || index[2] == 0) अणु
				/* Invalid MBSSID Index element */
				जारी;
			पूर्ण

			cfg80211_gen_new_bssid(transmitter_bssid,
					       elem->data[0],
					       index[2],
					       new_bssid);
			अगर (ether_addr_equal(new_bssid, bss_bssid)) अणु
				found = true;
				elems->bssid_index_len = index[1];
				elems->bssid_index = (व्योम *)&index[2];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस found ? profile_len : 0;
पूर्ण

u32 ieee802_11_parse_elems_crc(स्थिर u8 *start, माप_प्रकार len, bool action,
			       काष्ठा ieee802_11_elems *elems,
			       u64 filter, u32 crc, u8 *transmitter_bssid,
			       u8 *bss_bssid)
अणु
	स्थिर काष्ठा element *non_inherit = शून्य;
	u8 *nontransmitted_profile;
	पूर्णांक nontransmitted_profile_len = 0;

	स_रखो(elems, 0, माप(*elems));
	elems->ie_start = start;
	elems->total_len = len;

	nontransmitted_profile = kदो_स्मृति(len, GFP_ATOMIC);
	अगर (nontransmitted_profile) अणु
		nontransmitted_profile_len =
			ieee802_11_find_bssid_profile(start, len, elems,
						      transmitter_bssid,
						      bss_bssid,
						      nontransmitted_profile);
		non_inherit =
			cfg80211_find_ext_elem(WLAN_EID_EXT_NON_INHERITANCE,
					       nontransmitted_profile,
					       nontransmitted_profile_len);
	पूर्ण

	crc = _ieee802_11_parse_elems_crc(start, len, action, elems, filter,
					  crc, non_inherit);

	/* Override with nontransmitted profile, अगर found */
	अगर (nontransmitted_profile_len)
		_ieee802_11_parse_elems_crc(nontransmitted_profile,
					    nontransmitted_profile_len,
					    action, elems, 0, 0, शून्य);

	अगर (elems->tim && !elems->parse_error) अणु
		स्थिर काष्ठा ieee80211_tim_ie *tim_ie = elems->tim;

		elems->dtim_period = tim_ie->dtim_period;
		elems->dtim_count = tim_ie->dtim_count;
	पूर्ण

	/* Override DTIM period and count अगर needed */
	अगर (elems->bssid_index &&
	    elems->bssid_index_len >=
	    दुरत्वend(काष्ठा ieee80211_bssid_index, dtim_period))
		elems->dtim_period = elems->bssid_index->dtim_period;

	अगर (elems->bssid_index &&
	    elems->bssid_index_len >=
	    दुरत्वend(काष्ठा ieee80211_bssid_index, dtim_count))
		elems->dtim_count = elems->bssid_index->dtim_count;

	kमुक्त(nontransmitted_profile);

	वापस crc;
पूर्ण

व्योम ieee80211_regulatory_limit_wmm_params(काष्ठा ieee80211_sub_अगर_data *sdata,
					   काष्ठा ieee80211_tx_queue_params
					   *qparam, पूर्णांक ac)
अणु
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	स्थिर काष्ठा ieee80211_reg_rule *rrule;
	स्थिर काष्ठा ieee80211_wmm_ac *wmm_ac;
	u16 center_freq = 0;

	अगर (sdata->vअगर.type != NL80211_IFTYPE_AP &&
	    sdata->vअगर.type != NL80211_IFTYPE_STATION)
		वापस;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (chanctx_conf)
		center_freq = chanctx_conf->def.chan->center_freq;

	अगर (!center_freq) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	rrule = freq_reg_info(sdata->wdev.wiphy, MHZ_TO_KHZ(center_freq));

	अगर (IS_ERR_OR_शून्य(rrule) || !rrule->has_wmm) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
		wmm_ac = &rrule->wmm_rule.ap[ac];
	अन्यथा
		wmm_ac = &rrule->wmm_rule.client[ac];
	qparam->cw_min = max_t(u16, qparam->cw_min, wmm_ac->cw_min);
	qparam->cw_max = max_t(u16, qparam->cw_max, wmm_ac->cw_max);
	qparam->aअगरs = max_t(u8, qparam->aअगरs, wmm_ac->aअगरsn);
	qparam->txop = min_t(u16, qparam->txop, wmm_ac->cot / 32);
	rcu_पढ़ो_unlock();
पूर्ण

व्योम ieee80211_set_wmm_शेष(काष्ठा ieee80211_sub_अगर_data *sdata,
			       bool bss_notअगरy, bool enable_qos)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_tx_queue_params qparam;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	पूर्णांक ac;
	bool use_11b;
	bool is_ocb; /* Use another EDCA parameters अगर करोt11OCBActivated=true */
	पूर्णांक aCWmin, aCWmax;

	अगर (!local->ops->conf_tx)
		वापस;

	अगर (local->hw.queues < IEEE80211_NUM_ACS)
		वापस;

	स_रखो(&qparam, 0, माप(qparam));

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	use_11b = (chanctx_conf &&
		   chanctx_conf->def.chan->band == NL80211_BAND_2GHZ) &&
		 !(sdata->flags & IEEE80211_SDATA_OPERATING_GMODE);
	rcu_पढ़ो_unlock();

	is_ocb = (sdata->vअगर.type == NL80211_IFTYPE_OCB);

	/* Set शेषs according to 802.11-2007 Table 7-37 */
	aCWmax = 1023;
	अगर (use_11b)
		aCWmin = 31;
	अन्यथा
		aCWmin = 15;

	/* Confiure old 802.11b/g medium access rules. */
	qparam.cw_max = aCWmax;
	qparam.cw_min = aCWmin;
	qparam.txop = 0;
	qparam.aअगरs = 2;

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		/* Update अगर QoS is enabled. */
		अगर (enable_qos) अणु
			चयन (ac) अणु
			हाल IEEE80211_AC_BK:
				qparam.cw_max = aCWmax;
				qparam.cw_min = aCWmin;
				qparam.txop = 0;
				अगर (is_ocb)
					qparam.aअगरs = 9;
				अन्यथा
					qparam.aअगरs = 7;
				अवरोध;
			/* never happens but let's not leave undefined */
			शेष:
			हाल IEEE80211_AC_BE:
				qparam.cw_max = aCWmax;
				qparam.cw_min = aCWmin;
				qparam.txop = 0;
				अगर (is_ocb)
					qparam.aअगरs = 6;
				अन्यथा
					qparam.aअगरs = 3;
				अवरोध;
			हाल IEEE80211_AC_VI:
				qparam.cw_max = aCWmin;
				qparam.cw_min = (aCWmin + 1) / 2 - 1;
				अगर (is_ocb)
					qparam.txop = 0;
				अन्यथा अगर (use_11b)
					qparam.txop = 6016/32;
				अन्यथा
					qparam.txop = 3008/32;

				अगर (is_ocb)
					qparam.aअगरs = 3;
				अन्यथा
					qparam.aअगरs = 2;
				अवरोध;
			हाल IEEE80211_AC_VO:
				qparam.cw_max = (aCWmin + 1) / 2 - 1;
				qparam.cw_min = (aCWmin + 1) / 4 - 1;
				अगर (is_ocb)
					qparam.txop = 0;
				अन्यथा अगर (use_11b)
					qparam.txop = 3264/32;
				अन्यथा
					qparam.txop = 1504/32;
				qparam.aअगरs = 2;
				अवरोध;
			पूर्ण
		पूर्ण
		ieee80211_regulatory_limit_wmm_params(sdata, &qparam, ac);

		qparam.uapsd = false;

		sdata->tx_conf[ac] = qparam;
		drv_conf_tx(local, sdata, ac, &qparam);
	पूर्ण

	अगर (sdata->vअगर.type != NL80211_IFTYPE_MONITOR &&
	    sdata->vअगर.type != NL80211_IFTYPE_P2P_DEVICE &&
	    sdata->vअगर.type != NL80211_IFTYPE_न_अंक) अणु
		sdata->vअगर.bss_conf.qos = enable_qos;
		अगर (bss_notअगरy)
			ieee80211_bss_info_change_notअगरy(sdata,
							 BSS_CHANGED_QOS);
	पूर्ण
पूर्ण

व्योम ieee80211_send_auth(काष्ठा ieee80211_sub_अगर_data *sdata,
			 u16 transaction, u16 auth_alg, u16 status,
			 स्थिर u8 *extra, माप_प्रकार extra_len, स्थिर u8 *da,
			 स्थिर u8 *bssid, स्थिर u8 *key, u8 key_len, u8 key_idx,
			 u32 tx_flags)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *mgmt;
	पूर्णांक err;

	/* 24 + 6 = header + auth_algo + auth_transaction + status_code */
	skb = dev_alloc_skb(local->hw.extra_tx_headroom + IEEE80211_WEP_IV_LEN +
			    24 + 6 + extra_len + IEEE80211_WEP_ICV_LEN);
	अगर (!skb)
		वापस;

	skb_reserve(skb, local->hw.extra_tx_headroom + IEEE80211_WEP_IV_LEN);

	mgmt = skb_put_zero(skb, 24 + 6);
	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_AUTH);
	स_नकल(mgmt->da, da, ETH_ALEN);
	स_नकल(mgmt->sa, sdata->vअगर.addr, ETH_ALEN);
	स_नकल(mgmt->bssid, bssid, ETH_ALEN);
	mgmt->u.auth.auth_alg = cpu_to_le16(auth_alg);
	mgmt->u.auth.auth_transaction = cpu_to_le16(transaction);
	mgmt->u.auth.status_code = cpu_to_le16(status);
	अगर (extra)
		skb_put_data(skb, extra, extra_len);

	अगर (auth_alg == WLAN_AUTH_SHARED_KEY && transaction == 3) अणु
		mgmt->frame_control |= cpu_to_le16(IEEE80211_FCTL_PROTECTED);
		err = ieee80211_wep_encrypt(local, skb, key, key_len, key_idx);
		WARN_ON(err);
	पूर्ण

	IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT |
					tx_flags;
	ieee80211_tx_skb(sdata, skb);
पूर्ण

व्योम ieee80211_send_deauth_disassoc(काष्ठा ieee80211_sub_अगर_data *sdata,
				    स्थिर u8 *da, स्थिर u8 *bssid,
				    u16 stype, u16 reason,
				    bool send_frame, u8 *frame_buf)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)frame_buf;

	/* build frame */
	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT | stype);
	mgmt->duration = 0; /* initialize only */
	mgmt->seq_ctrl = 0; /* initialize only */
	स_नकल(mgmt->da, da, ETH_ALEN);
	स_नकल(mgmt->sa, sdata->vअगर.addr, ETH_ALEN);
	स_नकल(mgmt->bssid, bssid, ETH_ALEN);
	/* u.deauth.reason_code == u.disassoc.reason_code */
	mgmt->u.deauth.reason_code = cpu_to_le16(reason);

	अगर (send_frame) अणु
		skb = dev_alloc_skb(local->hw.extra_tx_headroom +
				    IEEE80211_DEAUTH_FRAME_LEN);
		अगर (!skb)
			वापस;

		skb_reserve(skb, local->hw.extra_tx_headroom);

		/* copy in frame */
		skb_put_data(skb, mgmt, IEEE80211_DEAUTH_FRAME_LEN);

		अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION ||
		    !(sdata->u.mgd.flags & IEEE80211_STA_MFP_ENABLED))
			IEEE80211_SKB_CB(skb)->flags |=
				IEEE80211_TX_INTFL_DONT_ENCRYPT;

		ieee80211_tx_skb(sdata, skb);
	पूर्ण
पूर्ण

अटल u8 *ieee80211_ग_लिखो_he_6ghz_cap(u8 *pos, __le16 cap, u8 *end)
अणु
	अगर ((end - pos) < 5)
		वापस pos;

	*pos++ = WLAN_EID_EXTENSION;
	*pos++ = 1 + माप(cap);
	*pos++ = WLAN_EID_EXT_HE_6GHZ_CAPA;
	स_नकल(pos, &cap, माप(cap));

	वापस pos + 2;
पूर्ण

अटल पूर्णांक ieee80211_build_preq_ies_band(काष्ठा ieee80211_sub_अगर_data *sdata,
					 u8 *buffer, माप_प्रकार buffer_len,
					 स्थिर u8 *ie, माप_प्रकार ie_len,
					 क्रमागत nl80211_band band,
					 u32 rate_mask,
					 काष्ठा cfg80211_chan_def *chandef,
					 माप_प्रकार *offset, u32 flags)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_supported_band *sband;
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap;
	u8 *pos = buffer, *end = buffer + buffer_len;
	माप_प्रकार noffset;
	पूर्णांक supp_rates_len, i;
	u8 rates[32];
	पूर्णांक num_rates;
	पूर्णांक ext_rates_len;
	पूर्णांक shअगरt;
	u32 rate_flags;
	bool have_80mhz = false;

	*offset = 0;

	sband = local->hw.wiphy->bands[band];
	अगर (WARN_ON_ONCE(!sband))
		वापस 0;

	rate_flags = ieee80211_chandef_rate_flags(chandef);
	shअगरt = ieee80211_chandef_get_shअगरt(chandef);

	num_rates = 0;
	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		अगर ((BIT(i) & rate_mask) == 0)
			जारी; /* skip rate */
		अगर ((rate_flags & sband->bitrates[i].flags) != rate_flags)
			जारी;

		rates[num_rates++] =
			(u8) DIV_ROUND_UP(sband->bitrates[i].bitrate,
					  (1 << shअगरt) * 5);
	पूर्ण

	supp_rates_len = min_t(पूर्णांक, num_rates, 8);

	अगर (end - pos < 2 + supp_rates_len)
		जाओ out_err;
	*pos++ = WLAN_EID_SUPP_RATES;
	*pos++ = supp_rates_len;
	स_नकल(pos, rates, supp_rates_len);
	pos += supp_rates_len;

	/* insert "request information" अगर in custom IEs */
	अगर (ie && ie_len) अणु
		अटल स्थिर u8 beक्रमe_extrates[] = अणु
			WLAN_EID_SSID,
			WLAN_EID_SUPP_RATES,
			WLAN_EID_REQUEST,
		पूर्ण;
		noffset = ieee80211_ie_split(ie, ie_len,
					     beक्रमe_extrates,
					     ARRAY_SIZE(beक्रमe_extrates),
					     *offset);
		अगर (end - pos < noffset - *offset)
			जाओ out_err;
		स_नकल(pos, ie + *offset, noffset - *offset);
		pos += noffset - *offset;
		*offset = noffset;
	पूर्ण

	ext_rates_len = num_rates - supp_rates_len;
	अगर (ext_rates_len > 0) अणु
		अगर (end - pos < 2 + ext_rates_len)
			जाओ out_err;
		*pos++ = WLAN_EID_EXT_SUPP_RATES;
		*pos++ = ext_rates_len;
		स_नकल(pos, rates + supp_rates_len, ext_rates_len);
		pos += ext_rates_len;
	पूर्ण

	अगर (chandef->chan && sband->band == NL80211_BAND_2GHZ) अणु
		अगर (end - pos < 3)
			जाओ out_err;
		*pos++ = WLAN_EID_DS_PARAMS;
		*pos++ = 1;
		*pos++ = ieee80211_frequency_to_channel(
				chandef->chan->center_freq);
	पूर्ण

	अगर (flags & IEEE80211_PROBE_FLAG_MIN_CONTENT)
		जाओ करोne;

	/* insert custom IEs that go beक्रमe HT */
	अगर (ie && ie_len) अणु
		अटल स्थिर u8 beक्रमe_ht[] = अणु
			/*
			 * no need to list the ones split off alपढ़ोy
			 * (or generated here)
			 */
			WLAN_EID_DS_PARAMS,
			WLAN_EID_SUPPORTED_REGULATORY_CLASSES,
		पूर्ण;
		noffset = ieee80211_ie_split(ie, ie_len,
					     beक्रमe_ht, ARRAY_SIZE(beक्रमe_ht),
					     *offset);
		अगर (end - pos < noffset - *offset)
			जाओ out_err;
		स_नकल(pos, ie + *offset, noffset - *offset);
		pos += noffset - *offset;
		*offset = noffset;
	पूर्ण

	अगर (sband->ht_cap.ht_supported) अणु
		अगर (end - pos < 2 + माप(काष्ठा ieee80211_ht_cap))
			जाओ out_err;
		pos = ieee80211_ie_build_ht_cap(pos, &sband->ht_cap,
						sband->ht_cap.cap);
	पूर्ण

	/* insert custom IEs that go beक्रमe VHT */
	अगर (ie && ie_len) अणु
		अटल स्थिर u8 beक्रमe_vht[] = अणु
			/*
			 * no need to list the ones split off alपढ़ोy
			 * (or generated here)
			 */
			WLAN_EID_BSS_COEX_2040,
			WLAN_EID_EXT_CAPABILITY,
			WLAN_EID_SSID_LIST,
			WLAN_EID_CHANNEL_USAGE,
			WLAN_EID_INTERWORKING,
			WLAN_EID_MESH_ID,
			/* 60 GHz (Multi-band, DMG, MMS) can't happen */
		पूर्ण;
		noffset = ieee80211_ie_split(ie, ie_len,
					     beक्रमe_vht, ARRAY_SIZE(beक्रमe_vht),
					     *offset);
		अगर (end - pos < noffset - *offset)
			जाओ out_err;
		स_नकल(pos, ie + *offset, noffset - *offset);
		pos += noffset - *offset;
		*offset = noffset;
	पूर्ण

	/* Check अगर any channel in this sband supports at least 80 MHz */
	क्रम (i = 0; i < sband->n_channels; i++) अणु
		अगर (sband->channels[i].flags & (IEEE80211_CHAN_DISABLED |
						IEEE80211_CHAN_NO_80MHZ))
			जारी;

		have_80mhz = true;
		अवरोध;
	पूर्ण

	अगर (sband->vht_cap.vht_supported && have_80mhz) अणु
		अगर (end - pos < 2 + माप(काष्ठा ieee80211_vht_cap))
			जाओ out_err;
		pos = ieee80211_ie_build_vht_cap(pos, &sband->vht_cap,
						 sband->vht_cap.cap);
	पूर्ण

	/* insert custom IEs that go beक्रमe HE */
	अगर (ie && ie_len) अणु
		अटल स्थिर u8 beक्रमe_he[] = अणु
			/*
			 * no need to list the ones split off beक्रमe VHT
			 * or generated here
			 */
			WLAN_EID_EXTENSION, WLAN_EID_EXT_FILS_REQ_PARAMS,
			WLAN_EID_AP_CSN,
			/* TODO: add 11ah/11aj/11ak elements */
		पूर्ण;
		noffset = ieee80211_ie_split(ie, ie_len,
					     beक्रमe_he, ARRAY_SIZE(beक्रमe_he),
					     *offset);
		अगर (end - pos < noffset - *offset)
			जाओ out_err;
		स_नकल(pos, ie + *offset, noffset - *offset);
		pos += noffset - *offset;
		*offset = noffset;
	पूर्ण

	he_cap = ieee80211_get_he_sta_cap(sband);
	अगर (he_cap) अणु
		pos = ieee80211_ie_build_he_cap(pos, he_cap, end);
		अगर (!pos)
			जाओ out_err;

		अगर (sband->band == NL80211_BAND_6GHZ) अणु
			क्रमागत nl80211_अगरtype अगरtype =
				ieee80211_vअगर_type_p2p(&sdata->vअगर);
			__le16 cap = ieee80211_get_he_6ghz_capa(sband, अगरtype);

			pos = ieee80211_ग_लिखो_he_6ghz_cap(pos, cap, end);
		पूर्ण
	पूर्ण

	/*
	 * If adding more here, adjust code in मुख्य.c
	 * that calculates local->scan_ies_len.
	 */

	वापस pos - buffer;
 out_err:
	WARN_ONCE(1, "not enough space for preq IEs\n");
 करोne:
	वापस pos - buffer;
पूर्ण

पूर्णांक ieee80211_build_preq_ies(काष्ठा ieee80211_sub_अगर_data *sdata, u8 *buffer,
			     माप_प्रकार buffer_len,
			     काष्ठा ieee80211_scan_ies *ie_desc,
			     स्थिर u8 *ie, माप_प्रकार ie_len,
			     u8 bands_used, u32 *rate_masks,
			     काष्ठा cfg80211_chan_def *chandef,
			     u32 flags)
अणु
	माप_प्रकार pos = 0, old_pos = 0, custom_ie_offset = 0;
	पूर्णांक i;

	स_रखो(ie_desc, 0, माप(*ie_desc));

	क्रम (i = 0; i < NUM_NL80211_BANDS; i++) अणु
		अगर (bands_used & BIT(i)) अणु
			pos += ieee80211_build_preq_ies_band(sdata,
							     buffer + pos,
							     buffer_len - pos,
							     ie, ie_len, i,
							     rate_masks[i],
							     chandef,
							     &custom_ie_offset,
							     flags);
			ie_desc->ies[i] = buffer + old_pos;
			ie_desc->len[i] = pos - old_pos;
			old_pos = pos;
		पूर्ण
	पूर्ण

	/* add any reमुख्यing custom IEs */
	अगर (ie && ie_len) अणु
		अगर (WARN_ONCE(buffer_len - pos < ie_len - custom_ie_offset,
			      "not enough space for preq custom IEs\n"))
			वापस pos;
		स_नकल(buffer + pos, ie + custom_ie_offset,
		       ie_len - custom_ie_offset);
		ie_desc->common_ies = buffer + pos;
		ie_desc->common_ie_len = ie_len - custom_ie_offset;
		pos += ie_len - custom_ie_offset;
	पूर्ण

	वापस pos;
पूर्ण;

काष्ठा sk_buff *ieee80211_build_probe_req(काष्ठा ieee80211_sub_अगर_data *sdata,
					  स्थिर u8 *src, स्थिर u8 *dst,
					  u32 ratemask,
					  काष्ठा ieee80211_channel *chan,
					  स्थिर u8 *ssid, माप_प्रकार ssid_len,
					  स्थिर u8 *ie, माप_प्रकार ie_len,
					  u32 flags)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा cfg80211_chan_def chandef;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *mgmt;
	पूर्णांक ies_len;
	u32 rate_masks[NUM_NL80211_BANDS] = अणुपूर्ण;
	काष्ठा ieee80211_scan_ies dummy_ie_desc;

	/*
	 * Do not send DS Channel parameter क्रम directed probe requests
	 * in order to maximize the chance that we get a response.  Some
	 * badly-behaved APs करोn't respond when this parameter is included.
	 */
	chandef.width = sdata->vअगर.bss_conf.chandef.width;
	अगर (flags & IEEE80211_PROBE_FLAG_सूचीECTED)
		chandef.chan = शून्य;
	अन्यथा
		chandef.chan = chan;

	skb = ieee80211_probereq_get(&local->hw, src, ssid, ssid_len,
				     100 + ie_len);
	अगर (!skb)
		वापस शून्य;

	rate_masks[chan->band] = ratemask;
	ies_len = ieee80211_build_preq_ies(sdata, skb_tail_poपूर्णांकer(skb),
					   skb_tailroom(skb), &dummy_ie_desc,
					   ie, ie_len, BIT(chan->band),
					   rate_masks, &chandef, flags);
	skb_put(skb, ies_len);

	अगर (dst) अणु
		mgmt = (काष्ठा ieee80211_mgmt *) skb->data;
		स_नकल(mgmt->da, dst, ETH_ALEN);
		स_नकल(mgmt->bssid, dst, ETH_ALEN);
	पूर्ण

	IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT;

	वापस skb;
पूर्ण

u32 ieee80211_sta_get_rates(काष्ठा ieee80211_sub_अगर_data *sdata,
			    काष्ठा ieee802_11_elems *elems,
			    क्रमागत nl80211_band band, u32 *basic_rates)
अणु
	काष्ठा ieee80211_supported_band *sband;
	माप_प्रकार num_rates;
	u32 supp_rates, rate_flags;
	पूर्णांक i, j, shअगरt;

	sband = sdata->local->hw.wiphy->bands[band];
	अगर (WARN_ON(!sband))
		वापस 1;

	rate_flags = ieee80211_chandef_rate_flags(&sdata->vअगर.bss_conf.chandef);
	shअगरt = ieee80211_vअगर_get_shअगरt(&sdata->vअगर);

	num_rates = sband->n_bitrates;
	supp_rates = 0;
	क्रम (i = 0; i < elems->supp_rates_len +
		     elems->ext_supp_rates_len; i++) अणु
		u8 rate = 0;
		पूर्णांक own_rate;
		bool is_basic;
		अगर (i < elems->supp_rates_len)
			rate = elems->supp_rates[i];
		अन्यथा अगर (elems->ext_supp_rates)
			rate = elems->ext_supp_rates
				[i - elems->supp_rates_len];
		own_rate = 5 * (rate & 0x7f);
		is_basic = !!(rate & 0x80);

		अगर (is_basic && (rate & 0x7f) == BSS_MEMBERSHIP_SELECTOR_HT_PHY)
			जारी;

		क्रम (j = 0; j < num_rates; j++) अणु
			पूर्णांक brate;
			अगर ((rate_flags & sband->bitrates[j].flags)
			    != rate_flags)
				जारी;

			brate = DIV_ROUND_UP(sband->bitrates[j].bitrate,
					     1 << shअगरt);

			अगर (brate == own_rate) अणु
				supp_rates |= BIT(j);
				अगर (basic_rates && is_basic)
					*basic_rates |= BIT(j);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस supp_rates;
पूर्ण

व्योम ieee80211_stop_device(काष्ठा ieee80211_local *local)
अणु
	ieee80211_led_radio(local, false);
	ieee80211_mod_tpt_led_trig(local, 0, IEEE80211_TPT_LEDTRIG_FL_RADIO);

	cancel_work_sync(&local->reconfig_filter);

	flush_workqueue(local->workqueue);
	drv_stop(local);
पूर्ण

अटल व्योम ieee80211_flush_completed_scan(काष्ठा ieee80211_local *local,
					   bool पातed)
अणु
	/* It's possible that we don't handle the scan completion in
	 * समय during suspend, so अगर it's still marked as completed
	 * here, queue the work and flush it to clean things up.
	 * Instead of calling the worker function directly here, we
	 * really queue it to aव्योम potential races with other flows
	 * scheduling the same work.
	 */
	अगर (test_bit(SCAN_COMPLETED, &local->scanning)) अणु
		/* If coming from reconfiguration failure, पात the scan so
		 * we करोn't attempt to जारी a partial HW scan - which is
		 * possible otherwise अगर (e.g.) the 2.4 GHz portion was the
		 * completed scan, and a 5 GHz portion is still pending.
		 */
		अगर (पातed)
			set_bit(SCAN_ABORTED, &local->scanning);
		ieee80211_queue_delayed_work(&local->hw, &local->scan_work, 0);
		flush_delayed_work(&local->scan_work);
	पूर्ण
पूर्ण

अटल व्योम ieee80211_handle_reconfig_failure(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_chanctx *ctx;

	/*
	 * We get here अगर during resume the device can't be restarted properly.
	 * We might also get here अगर this happens during HW reset, which is a
	 * slightly dअगरferent situation and we need to drop all connections in
	 * the latter हाल.
	 *
	 * Ask cfg80211 to turn off all पूर्णांकerfaces, this will result in more
	 * warnings but at least we'll then get पूर्णांकo a clean stopped state.
	 */

	local->resuming = false;
	local->suspended = false;
	local->in_reconfig = false;

	ieee80211_flush_completed_scan(local, true);

	/* scheduled scan clearly can't be running any more, but tell
	 * cfg80211 and clear local state
	 */
	ieee80211_sched_scan_end(local);

	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list)
		sdata->flags &= ~IEEE80211_SDATA_IN_DRIVER;

	/* Mark channel contexts as not being in the driver any more to aव्योम
	 * removing them from the driver during the shutकरोwn process...
	 */
	mutex_lock(&local->chanctx_mtx);
	list_क्रम_each_entry(ctx, &local->chanctx_list, list)
		ctx->driver_present = false;
	mutex_unlock(&local->chanctx_mtx);
पूर्ण

अटल व्योम ieee80211_assign_chanctx(काष्ठा ieee80211_local *local,
				     काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_chanctx_conf *conf;
	काष्ठा ieee80211_chanctx *ctx;

	अगर (!local->use_chanctx)
		वापस;

	mutex_lock(&local->chanctx_mtx);
	conf = rcu_dereference_रक्षित(sdata->vअगर.chanctx_conf,
					 lockdep_is_held(&local->chanctx_mtx));
	अगर (conf) अणु
		ctx = container_of(conf, काष्ठा ieee80211_chanctx, conf);
		drv_assign_vअगर_chanctx(local, sdata, ctx);
	पूर्ण
	mutex_unlock(&local->chanctx_mtx);
पूर्ण

अटल व्योम ieee80211_reconfig_stations(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;

	/* add STAs back */
	mutex_lock(&local->sta_mtx);
	list_क्रम_each_entry(sta, &local->sta_list, list) अणु
		क्रमागत ieee80211_sta_state state;

		अगर (!sta->uploaded || sta->sdata != sdata)
			जारी;

		क्रम (state = IEEE80211_STA_NOTEXIST;
		     state < sta->sta_state; state++)
			WARN_ON(drv_sta_state(local, sta->sdata, sta, state,
					      state + 1));
	पूर्ण
	mutex_unlock(&local->sta_mtx);
पूर्ण

अटल पूर्णांक ieee80211_reconfig_nan(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा cfg80211_nan_func *func, **funcs;
	पूर्णांक res, id, i = 0;

	res = drv_start_nan(sdata->local, sdata,
			    &sdata->u.nan.conf);
	अगर (WARN_ON(res))
		वापस res;

	funcs = kसुस्मृति(sdata->local->hw.max_nan_de_entries + 1,
			माप(*funcs),
			GFP_KERNEL);
	अगर (!funcs)
		वापस -ENOMEM;

	/* Add all the functions:
	 * This is a little bit ugly. We need to call a potentially sleeping
	 * callback क्रम each न_अंक function, so we can't hold the spinlock.
	 */
	spin_lock_bh(&sdata->u.nan.func_lock);

	idr_क्रम_each_entry(&sdata->u.nan.function_inst_ids, func, id)
		funcs[i++] = func;

	spin_unlock_bh(&sdata->u.nan.func_lock);

	क्रम (i = 0; funcs[i]; i++) अणु
		res = drv_add_nan_func(sdata->local, sdata, funcs[i]);
		अगर (WARN_ON(res))
			ieee80211_nan_func_terminated(&sdata->vअगर,
						      funcs[i]->instance_id,
						      NL80211_न_अंक_FUNC_TERM_REASON_ERROR,
						      GFP_KERNEL);
	पूर्ण

	kमुक्त(funcs);

	वापस 0;
पूर्ण

पूर्णांक ieee80211_reconfig(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_hw *hw = &local->hw;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_chanctx *ctx;
	काष्ठा sta_info *sta;
	पूर्णांक res, i;
	bool reconfig_due_to_wowlan = false;
	काष्ठा ieee80211_sub_अगर_data *sched_scan_sdata;
	काष्ठा cfg80211_sched_scan_request *sched_scan_req;
	bool sched_scan_stopped = false;
	bool suspended = local->suspended;

	/* nothing to करो अगर HW shouldn't run */
	अगर (!local->खोलो_count)
		जाओ wake_up;

#अगर_घोषित CONFIG_PM
	अगर (suspended)
		local->resuming = true;

	अगर (local->wowlan) अणु
		/*
		 * In the wowlan हाल, both mac80211 and the device
		 * are functional when the resume op is called, so
		 * clear local->suspended so the device could operate
		 * normally (e.g. pass rx frames).
		 */
		local->suspended = false;
		res = drv_resume(local);
		local->wowlan = false;
		अगर (res < 0) अणु
			local->resuming = false;
			वापस res;
		पूर्ण
		अगर (res == 0)
			जाओ wake_up;
		WARN_ON(res > 1);
		/*
		 * res is 1, which means the driver requested
		 * to go through a regular reset on wakeup.
		 * restore local->suspended in this हाल.
		 */
		reconfig_due_to_wowlan = true;
		local->suspended = true;
	पूर्ण
#पूर्ण_अगर

	/*
	 * In हाल of hw_restart during suspend (without wowlan),
	 * cancel restart work, as we are reconfiguring the device
	 * anyway.
	 * Note that restart_work is scheduled on a frozen workqueue,
	 * so we can't deadlock in this हाल.
	 */
	अगर (suspended && local->in_reconfig && !reconfig_due_to_wowlan)
		cancel_work_sync(&local->restart_work);

	local->started = false;

	/*
	 * Upon resume hardware can someबार be goofy due to
	 * various platक्रमm / driver / bus issues, so restarting
	 * the device may at बार not work immediately. Propagate
	 * the error.
	 */
	res = drv_start(local);
	अगर (res) अणु
		अगर (suspended)
			WARN(1, "Hardware became unavailable upon resume. This could be a software issue prior to suspend or a hardware issue.\n");
		अन्यथा
			WARN(1, "Hardware became unavailable during restart.\n");
		ieee80211_handle_reconfig_failure(local);
		वापस res;
	पूर्ण

	/* setup fragmentation threshold */
	drv_set_frag_threshold(local, hw->wiphy->frag_threshold);

	/* setup RTS threshold */
	drv_set_rts_threshold(local, hw->wiphy->rts_threshold);

	/* reset coverage class */
	drv_set_coverage_class(local, hw->wiphy->coverage_class);

	ieee80211_led_radio(local, true);
	ieee80211_mod_tpt_led_trig(local,
				   IEEE80211_TPT_LEDTRIG_FL_RADIO, 0);

	/* add पूर्णांकerfaces */
	sdata = rtnl_dereference(local->monitor_sdata);
	अगर (sdata) अणु
		/* in HW restart it exists alपढ़ोy */
		WARN_ON(local->resuming);
		res = drv_add_पूर्णांकerface(local, sdata);
		अगर (WARN_ON(res)) अणु
			RCU_INIT_POINTER(local->monitor_sdata, शून्य);
			synchronize_net();
			kमुक्त(sdata);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN &&
		    sdata->vअगर.type != NL80211_IFTYPE_MONITOR &&
		    ieee80211_sdata_running(sdata)) अणु
			res = drv_add_पूर्णांकerface(local, sdata);
			अगर (WARN_ON(res))
				अवरोध;
		पूर्ण
	पूर्ण

	/* If adding any of the पूर्णांकerfaces failed above, roll back and
	 * report failure.
	 */
	अगर (res) अणु
		list_क्रम_each_entry_जारी_reverse(sdata, &local->पूर्णांकerfaces,
						     list)
			अगर (sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN &&
			    sdata->vअगर.type != NL80211_IFTYPE_MONITOR &&
			    ieee80211_sdata_running(sdata))
				drv_हटाओ_पूर्णांकerface(local, sdata);
		ieee80211_handle_reconfig_failure(local);
		वापस res;
	पूर्ण

	/* add channel contexts */
	अगर (local->use_chanctx) अणु
		mutex_lock(&local->chanctx_mtx);
		list_क्रम_each_entry(ctx, &local->chanctx_list, list)
			अगर (ctx->replace_state !=
			    IEEE80211_CHANCTX_REPLACES_OTHER)
				WARN_ON(drv_add_chanctx(local, ctx));
		mutex_unlock(&local->chanctx_mtx);

		sdata = rtnl_dereference(local->monitor_sdata);
		अगर (sdata && ieee80211_sdata_running(sdata))
			ieee80211_assign_chanctx(local, sdata);
	पूर्ण

	/* reconfigure hardware */
	ieee80211_hw_config(local, ~0);

	ieee80211_configure_filter(local);

	/* Finally also reconfigure all the BSS inक्रमmation */
	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		u32 changed;

		अगर (!ieee80211_sdata_running(sdata))
			जारी;

		ieee80211_assign_chanctx(local, sdata);

		चयन (sdata->vअगर.type) अणु
		हाल NL80211_IFTYPE_AP_VLAN:
		हाल NL80211_IFTYPE_MONITOR:
			अवरोध;
		हाल NL80211_IFTYPE_ADHOC:
			अगर (sdata->vअगर.bss_conf.ibss_joined)
				WARN_ON(drv_join_ibss(local, sdata));
			fallthrough;
		शेष:
			ieee80211_reconfig_stations(sdata);
			fallthrough;
		हाल NL80211_IFTYPE_AP: /* AP stations are handled later */
			क्रम (i = 0; i < IEEE80211_NUM_ACS; i++)
				drv_conf_tx(local, sdata, i,
					    &sdata->tx_conf[i]);
			अवरोध;
		पूर्ण

		/* common change flags क्रम all पूर्णांकerface types */
		changed = BSS_CHANGED_ERP_CTS_PROT |
			  BSS_CHANGED_ERP_PREAMBLE |
			  BSS_CHANGED_ERP_SLOT |
			  BSS_CHANGED_HT |
			  BSS_CHANGED_BASIC_RATES |
			  BSS_CHANGED_BEACON_INT |
			  BSS_CHANGED_BSSID |
			  BSS_CHANGED_CQM |
			  BSS_CHANGED_QOS |
			  BSS_CHANGED_IDLE |
			  BSS_CHANGED_TXPOWER |
			  BSS_CHANGED_MCAST_RATE;

		अगर (sdata->vअगर.mu_mimo_owner)
			changed |= BSS_CHANGED_MU_GROUPS;

		चयन (sdata->vअगर.type) अणु
		हाल NL80211_IFTYPE_STATION:
			changed |= BSS_CHANGED_ASSOC |
				   BSS_CHANGED_ARP_FILTER |
				   BSS_CHANGED_PS;

			/* Re-send beacon info report to the driver */
			अगर (sdata->u.mgd.have_beacon)
				changed |= BSS_CHANGED_BEACON_INFO;

			अगर (sdata->vअगर.bss_conf.max_idle_period ||
			    sdata->vअगर.bss_conf.रक्षित_keep_alive)
				changed |= BSS_CHANGED_KEEP_ALIVE;

			sdata_lock(sdata);
			ieee80211_bss_info_change_notअगरy(sdata, changed);
			sdata_unlock(sdata);
			अवरोध;
		हाल NL80211_IFTYPE_OCB:
			changed |= BSS_CHANGED_OCB;
			ieee80211_bss_info_change_notअगरy(sdata, changed);
			अवरोध;
		हाल NL80211_IFTYPE_ADHOC:
			changed |= BSS_CHANGED_IBSS;
			fallthrough;
		हाल NL80211_IFTYPE_AP:
			changed |= BSS_CHANGED_SSID | BSS_CHANGED_P2P_PS;

			अगर (sdata->vअगर.bss_conf.fपंचांग_responder == 1 &&
			    wiphy_ext_feature_isset(sdata->local->hw.wiphy,
					NL80211_EXT_FEATURE_ENABLE_FTM_RESPONDER))
				changed |= BSS_CHANGED_FTM_RESPONDER;

			अगर (sdata->vअगर.type == NL80211_IFTYPE_AP) अणु
				changed |= BSS_CHANGED_AP_PROBE_RESP;

				अगर (rcu_access_poपूर्णांकer(sdata->u.ap.beacon))
					drv_start_ap(local, sdata);
			पूर्ण
			fallthrough;
		हाल NL80211_IFTYPE_MESH_POINT:
			अगर (sdata->vअगर.bss_conf.enable_beacon) अणु
				changed |= BSS_CHANGED_BEACON |
					   BSS_CHANGED_BEACON_ENABLED;
				ieee80211_bss_info_change_notअगरy(sdata, changed);
			पूर्ण
			अवरोध;
		हाल NL80211_IFTYPE_न_अंक:
			res = ieee80211_reconfig_nan(sdata);
			अगर (res < 0) अणु
				ieee80211_handle_reconfig_failure(local);
				वापस res;
			पूर्ण
			अवरोध;
		हाल NL80211_IFTYPE_AP_VLAN:
		हाल NL80211_IFTYPE_MONITOR:
		हाल NL80211_IFTYPE_P2P_DEVICE:
			/* nothing to करो */
			अवरोध;
		हाल NL80211_IFTYPE_UNSPECIFIED:
		हाल NUM_NL80211_IFTYPES:
		हाल NL80211_IFTYPE_P2P_CLIENT:
		हाल NL80211_IFTYPE_P2P_GO:
		हाल NL80211_IFTYPE_WDS:
			WARN_ON(1);
			अवरोध;
		पूर्ण
	पूर्ण

	ieee80211_recalc_ps(local);

	/*
	 * The sta might be in psm against the ap (e.g. because
	 * this was the state beक्रमe a hw restart), so we
	 * explicitly send a null packet in order to make sure
	 * it'll sync against the ap (and get out of psm).
	 */
	अगर (!(local->hw.conf.flags & IEEE80211_CONF_PS)) अणु
		list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
			अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
				जारी;
			अगर (!sdata->u.mgd.associated)
				जारी;

			ieee80211_send_nullfunc(local, sdata, false);
		पूर्ण
	पूर्ण

	/* APs are now beaconing, add back stations */
	mutex_lock(&local->sta_mtx);
	list_क्रम_each_entry(sta, &local->sta_list, list) अणु
		क्रमागत ieee80211_sta_state state;

		अगर (!sta->uploaded)
			जारी;

		अगर (sta->sdata->vअगर.type != NL80211_IFTYPE_AP &&
		    sta->sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN)
			जारी;

		क्रम (state = IEEE80211_STA_NOTEXIST;
		     state < sta->sta_state; state++)
			WARN_ON(drv_sta_state(local, sta->sdata, sta, state,
					      state + 1));
	पूर्ण
	mutex_unlock(&local->sta_mtx);

	/* add back keys */
	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list)
		ieee80211_reenable_keys(sdata);

	/* Reconfigure sched scan अगर it was पूर्णांकerrupted by FW restart */
	mutex_lock(&local->mtx);
	sched_scan_sdata = rcu_dereference_रक्षित(local->sched_scan_sdata,
						lockdep_is_held(&local->mtx));
	sched_scan_req = rcu_dereference_रक्षित(local->sched_scan_req,
						lockdep_is_held(&local->mtx));
	अगर (sched_scan_sdata && sched_scan_req)
		/*
		 * Sched scan stopped, but we करोn't want to report it. Instead,
		 * we're trying to reschedule. However, अगर more than one scan
		 * plan was set, we cannot reschedule since we करोn't know which
		 * scan plan was currently running (and some scan plans may have
		 * alपढ़ोy finished).
		 */
		अगर (sched_scan_req->n_scan_plans > 1 ||
		    __ieee80211_request_sched_scan_start(sched_scan_sdata,
							 sched_scan_req)) अणु
			RCU_INIT_POINTER(local->sched_scan_sdata, शून्य);
			RCU_INIT_POINTER(local->sched_scan_req, शून्य);
			sched_scan_stopped = true;
		पूर्ण
	mutex_unlock(&local->mtx);

	अगर (sched_scan_stopped)
		cfg80211_sched_scan_stopped_locked(local->hw.wiphy, 0);

 wake_up:

	अगर (local->monitors == local->खोलो_count && local->monitors > 0)
		ieee80211_add_भव_monitor(local);

	/*
	 * Clear the WLAN_STA_BLOCK_BA flag so new aggregation
	 * sessions can be established after a resume.
	 *
	 * Also tear करोwn aggregation sessions since reconfiguring
	 * them in a hardware restart scenario is not easily करोne
	 * right now, and the hardware will have lost inक्रमmation
	 * about the sessions, but we and the AP still think they
	 * are active. This is really a workaround though.
	 */
	अगर (ieee80211_hw_check(hw, AMPDU_AGGREGATION)) अणु
		mutex_lock(&local->sta_mtx);

		list_क्रम_each_entry(sta, &local->sta_list, list) अणु
			अगर (!local->resuming)
				ieee80211_sta_tear_करोwn_BA_sessions(
						sta, AGG_STOP_LOCAL_REQUEST);
			clear_sta_flag(sta, WLAN_STA_BLOCK_BA);
		पूर्ण

		mutex_unlock(&local->sta_mtx);
	पूर्ण

	अगर (local->in_reconfig) अणु
		local->in_reconfig = false;
		barrier();

		/* Restart deferred ROCs */
		mutex_lock(&local->mtx);
		ieee80211_start_next_roc(local);
		mutex_unlock(&local->mtx);

		/* Requeue all works */
		list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list)
			ieee80211_queue_work(&local->hw, &sdata->work);
	पूर्ण

	ieee80211_wake_queues_by_reason(hw, IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_REASON_SUSPEND,
					false);

	/*
	 * If this is क्रम hw restart things are still running.
	 * We may want to change that later, however.
	 */
	अगर (local->खोलो_count && (!suspended || reconfig_due_to_wowlan))
		drv_reconfig_complete(local, IEEE80211_RECONFIG_TYPE_RESTART);

	अगर (!suspended)
		वापस 0;

#अगर_घोषित CONFIG_PM
	/* first set suspended false, then resuming */
	local->suspended = false;
	mb();
	local->resuming = false;

	ieee80211_flush_completed_scan(local, false);

	अगर (local->खोलो_count && !reconfig_due_to_wowlan)
		drv_reconfig_complete(local, IEEE80211_RECONFIG_TYPE_SUSPEND);

	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (!ieee80211_sdata_running(sdata))
			जारी;
		अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION)
			ieee80211_sta_restart(sdata);
	पूर्ण

	mod_समयr(&local->sta_cleanup, jअगरfies + 1);
#अन्यथा
	WARN_ON(1);
#पूर्ण_अगर

	वापस 0;
पूर्ण

व्योम ieee80211_resume_disconnect(काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_local *local;
	काष्ठा ieee80211_key *key;

	अगर (WARN_ON(!vअगर))
		वापस;

	sdata = vअगर_to_sdata(vअगर);
	local = sdata->local;

	अगर (WARN_ON(!local->resuming))
		वापस;

	अगर (WARN_ON(vअगर->type != NL80211_IFTYPE_STATION))
		वापस;

	sdata->flags |= IEEE80211_SDATA_DISCONNECT_RESUME;

	mutex_lock(&local->key_mtx);
	list_क्रम_each_entry(key, &sdata->key_list, list)
		key->flags |= KEY_FLAG_TAINTED;
	mutex_unlock(&local->key_mtx);
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_resume_disconnect);

व्योम ieee80211_recalc_smps(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_chanctx *chanctx;

	mutex_lock(&local->chanctx_mtx);

	chanctx_conf = rcu_dereference_रक्षित(sdata->vअगर.chanctx_conf,
					lockdep_is_held(&local->chanctx_mtx));

	/*
	 * This function can be called from a work, thus it may be possible
	 * that the chanctx_conf is हटाओd (due to a disconnection, क्रम
	 * example).
	 * So nothing should be करोne in such हाल.
	 */
	अगर (!chanctx_conf)
		जाओ unlock;

	chanctx = container_of(chanctx_conf, काष्ठा ieee80211_chanctx, conf);
	ieee80211_recalc_smps_chanctx(local, chanctx);
 unlock:
	mutex_unlock(&local->chanctx_mtx);
पूर्ण

व्योम ieee80211_recalc_min_chandef(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_chanctx *chanctx;

	mutex_lock(&local->chanctx_mtx);

	chanctx_conf = rcu_dereference_रक्षित(sdata->vअगर.chanctx_conf,
					lockdep_is_held(&local->chanctx_mtx));

	अगर (WARN_ON_ONCE(!chanctx_conf))
		जाओ unlock;

	chanctx = container_of(chanctx_conf, काष्ठा ieee80211_chanctx, conf);
	ieee80211_recalc_chanctx_min_def(local, chanctx);
 unlock:
	mutex_unlock(&local->chanctx_mtx);
पूर्ण

माप_प्रकार ieee80211_ie_split_venकरोr(स्थिर u8 *ies, माप_प्रकार ielen, माप_प्रकार offset)
अणु
	माप_प्रकार pos = offset;

	जबतक (pos < ielen && ies[pos] != WLAN_EID_VENDOR_SPECIFIC)
		pos += 2 + ies[pos + 1];

	वापस pos;
पूर्ण

अटल व्योम _ieee80211_enable_rssi_reports(काष्ठा ieee80211_sub_अगर_data *sdata,
					    पूर्णांक rssi_min_thold,
					    पूर्णांक rssi_max_thold)
अणु
	trace_api_enable_rssi_reports(sdata, rssi_min_thold, rssi_max_thold);

	अगर (WARN_ON(sdata->vअगर.type != NL80211_IFTYPE_STATION))
		वापस;

	/*
	 * Scale up threshold values beक्रमe storing it, as the RSSI averaging
	 * algorithm uses a scaled up value as well. Change this scaling
	 * factor अगर the RSSI averaging algorithm changes.
	 */
	sdata->u.mgd.rssi_min_thold = rssi_min_thold*16;
	sdata->u.mgd.rssi_max_thold = rssi_max_thold*16;
पूर्ण

व्योम ieee80211_enable_rssi_reports(काष्ठा ieee80211_vअगर *vअगर,
				    पूर्णांक rssi_min_thold,
				    पूर्णांक rssi_max_thold)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);

	WARN_ON(rssi_min_thold == rssi_max_thold ||
		rssi_min_thold > rssi_max_thold);

	_ieee80211_enable_rssi_reports(sdata, rssi_min_thold,
				       rssi_max_thold);
पूर्ण
EXPORT_SYMBOL(ieee80211_enable_rssi_reports);

व्योम ieee80211_disable_rssi_reports(काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);

	_ieee80211_enable_rssi_reports(sdata, 0, 0);
पूर्ण
EXPORT_SYMBOL(ieee80211_disable_rssi_reports);

u8 *ieee80211_ie_build_ht_cap(u8 *pos, काष्ठा ieee80211_sta_ht_cap *ht_cap,
			      u16 cap)
अणु
	__le16 पंचांगp;

	*pos++ = WLAN_EID_HT_CAPABILITY;
	*pos++ = माप(काष्ठा ieee80211_ht_cap);
	स_रखो(pos, 0, माप(काष्ठा ieee80211_ht_cap));

	/* capability flags */
	पंचांगp = cpu_to_le16(cap);
	स_नकल(pos, &पंचांगp, माप(u16));
	pos += माप(u16);

	/* AMPDU parameters */
	*pos++ = ht_cap->ampdu_factor |
		 (ht_cap->ampdu_density <<
			IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT);

	/* MCS set */
	स_नकल(pos, &ht_cap->mcs, माप(ht_cap->mcs));
	pos += माप(ht_cap->mcs);

	/* extended capabilities */
	pos += माप(__le16);

	/* BF capabilities */
	pos += माप(__le32);

	/* antenna selection */
	pos += माप(u8);

	वापस pos;
पूर्ण

u8 *ieee80211_ie_build_vht_cap(u8 *pos, काष्ठा ieee80211_sta_vht_cap *vht_cap,
			       u32 cap)
अणु
	__le32 पंचांगp;

	*pos++ = WLAN_EID_VHT_CAPABILITY;
	*pos++ = माप(काष्ठा ieee80211_vht_cap);
	स_रखो(pos, 0, माप(काष्ठा ieee80211_vht_cap));

	/* capability flags */
	पंचांगp = cpu_to_le32(cap);
	स_नकल(pos, &पंचांगp, माप(u32));
	pos += माप(u32);

	/* VHT MCS set */
	स_नकल(pos, &vht_cap->vht_mcs, माप(vht_cap->vht_mcs));
	pos += माप(vht_cap->vht_mcs);

	वापस pos;
पूर्ण

u8 ieee80211_ie_len_he_cap(काष्ठा ieee80211_sub_अगर_data *sdata, u8 अगरtype)
अणु
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap;
	काष्ठा ieee80211_supported_band *sband;
	u8 n;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस 0;

	he_cap = ieee80211_get_he_अगरtype_cap(sband, अगरtype);
	अगर (!he_cap)
		वापस 0;

	n = ieee80211_he_mcs_nss_size(&he_cap->he_cap_elem);
	वापस 2 + 1 +
	       माप(he_cap->he_cap_elem) + n +
	       ieee80211_he_ppe_size(he_cap->ppe_thres[0],
				     he_cap->he_cap_elem.phy_cap_info);
पूर्ण

u8 *ieee80211_ie_build_he_cap(u8 *pos,
			      स्थिर काष्ठा ieee80211_sta_he_cap *he_cap,
			      u8 *end)
अणु
	u8 n;
	u8 ie_len;
	u8 *orig_pos = pos;

	/* Make sure we have place क्रम the IE */
	/*
	 * TODO: the 1 added is because this temporarily is under the EXTENSION
	 * IE. Get rid of it when it moves.
	 */
	अगर (!he_cap)
		वापस orig_pos;

	n = ieee80211_he_mcs_nss_size(&he_cap->he_cap_elem);
	ie_len = 2 + 1 +
		 माप(he_cap->he_cap_elem) + n +
		 ieee80211_he_ppe_size(he_cap->ppe_thres[0],
				       he_cap->he_cap_elem.phy_cap_info);

	अगर ((end - pos) < ie_len)
		वापस orig_pos;

	*pos++ = WLAN_EID_EXTENSION;
	pos++; /* We'll set the size later below */
	*pos++ = WLAN_EID_EXT_HE_CAPABILITY;

	/* Fixed data */
	स_नकल(pos, &he_cap->he_cap_elem, माप(he_cap->he_cap_elem));
	pos += माप(he_cap->he_cap_elem);

	स_नकल(pos, &he_cap->he_mcs_nss_supp, n);
	pos += n;

	/* Check अगर PPE Threshold should be present */
	अगर ((he_cap->he_cap_elem.phy_cap_info[6] &
	     IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT) == 0)
		जाओ end;

	/*
	 * Calculate how many PPET16/PPET8 pairs are to come. Algorithm:
	 * (NSS_M1 + 1) x (num of 1 bits in RU_INDEX_BITMASK)
	 */
	n = hweight8(he_cap->ppe_thres[0] &
		     IEEE80211_PPE_THRES_RU_INDEX_BITMASK_MASK);
	n *= (1 + ((he_cap->ppe_thres[0] & IEEE80211_PPE_THRES_NSS_MASK) >>
		   IEEE80211_PPE_THRES_NSS_POS));

	/*
	 * Each pair is 6 bits, and we need to add the 7 "header" bits to the
	 * total size.
	 */
	n = (n * IEEE80211_PPE_THRES_INFO_PPET_SIZE * 2) + 7;
	n = DIV_ROUND_UP(n, 8);

	/* Copy PPE Thresholds */
	स_नकल(pos, &he_cap->ppe_thres, n);
	pos += n;

end:
	orig_pos[1] = (pos - orig_pos) - 2;
	वापस pos;
पूर्ण

व्योम ieee80211_ie_build_he_6ghz_cap(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_supported_band *sband;
	स्थिर काष्ठा ieee80211_sband_अगरtype_data *अगरtd;
	क्रमागत nl80211_अगरtype अगरtype = ieee80211_vअगर_type_p2p(&sdata->vअगर);
	u8 *pos;
	u16 cap;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस;

	अगरtd = ieee80211_get_sband_अगरtype_data(sband, अगरtype);
	अगर (WARN_ON(!अगरtd))
		वापस;

	/* Check क्रम device HE 6 GHz capability beक्रमe adding element */
	अगर (!अगरtd->he_6ghz_capa.capa)
		वापस;

	cap = le16_to_cpu(अगरtd->he_6ghz_capa.capa);
	cap &= ~IEEE80211_HE_6GHZ_CAP_SM_PS;

	चयन (sdata->smps_mode) अणु
	हाल IEEE80211_SMPS_AUTOMATIC:
	हाल IEEE80211_SMPS_NUM_MODES:
		WARN_ON(1);
		fallthrough;
	हाल IEEE80211_SMPS_OFF:
		cap |= u16_encode_bits(WLAN_HT_CAP_SM_PS_DISABLED,
				       IEEE80211_HE_6GHZ_CAP_SM_PS);
		अवरोध;
	हाल IEEE80211_SMPS_STATIC:
		cap |= u16_encode_bits(WLAN_HT_CAP_SM_PS_STATIC,
				       IEEE80211_HE_6GHZ_CAP_SM_PS);
		अवरोध;
	हाल IEEE80211_SMPS_DYNAMIC:
		cap |= u16_encode_bits(WLAN_HT_CAP_SM_PS_DYNAMIC,
				       IEEE80211_HE_6GHZ_CAP_SM_PS);
		अवरोध;
	पूर्ण

	pos = skb_put(skb, 2 + 1 + माप(cap));
	ieee80211_ग_लिखो_he_6ghz_cap(pos, cpu_to_le16(cap),
				    pos + 2 + 1 + माप(cap));
पूर्ण

u8 *ieee80211_ie_build_ht_oper(u8 *pos, काष्ठा ieee80211_sta_ht_cap *ht_cap,
			       स्थिर काष्ठा cfg80211_chan_def *chandef,
			       u16 prot_mode, bool rअगरs_mode)
अणु
	काष्ठा ieee80211_ht_operation *ht_oper;
	/* Build HT Inक्रमmation */
	*pos++ = WLAN_EID_HT_OPERATION;
	*pos++ = माप(काष्ठा ieee80211_ht_operation);
	ht_oper = (काष्ठा ieee80211_ht_operation *)pos;
	ht_oper->primary_chan = ieee80211_frequency_to_channel(
					chandef->chan->center_freq);
	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_160:
	हाल NL80211_CHAN_WIDTH_80P80:
	हाल NL80211_CHAN_WIDTH_80:
	हाल NL80211_CHAN_WIDTH_40:
		अगर (chandef->center_freq1 > chandef->chan->center_freq)
			ht_oper->ht_param = IEEE80211_HT_PARAM_CHA_SEC_ABOVE;
		अन्यथा
			ht_oper->ht_param = IEEE80211_HT_PARAM_CHA_SEC_BELOW;
		अवरोध;
	शेष:
		ht_oper->ht_param = IEEE80211_HT_PARAM_CHA_SEC_NONE;
		अवरोध;
	पूर्ण
	अगर (ht_cap->cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 &&
	    chandef->width != NL80211_CHAN_WIDTH_20_NOHT &&
	    chandef->width != NL80211_CHAN_WIDTH_20)
		ht_oper->ht_param |= IEEE80211_HT_PARAM_CHAN_WIDTH_ANY;

	अगर (rअगरs_mode)
		ht_oper->ht_param |= IEEE80211_HT_PARAM_RIFS_MODE;

	ht_oper->operation_mode = cpu_to_le16(prot_mode);
	ht_oper->stbc_param = 0x0000;

	/* It seems that Basic MCS set and Supported MCS set
	   are identical क्रम the first 10 bytes */
	स_रखो(&ht_oper->basic_set, 0, 16);
	स_नकल(&ht_oper->basic_set, &ht_cap->mcs, 10);

	वापस pos + माप(काष्ठा ieee80211_ht_operation);
पूर्ण

व्योम ieee80211_ie_build_wide_bw_cs(u8 *pos,
				   स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	*pos++ = WLAN_EID_WIDE_BW_CHANNEL_SWITCH;	/* EID */
	*pos++ = 3;					/* IE length */
	/* New channel width */
	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_80:
		*pos++ = IEEE80211_VHT_CHANWIDTH_80MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_160:
		*pos++ = IEEE80211_VHT_CHANWIDTH_160MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80P80:
		*pos++ = IEEE80211_VHT_CHANWIDTH_80P80MHZ;
		अवरोध;
	शेष:
		*pos++ = IEEE80211_VHT_CHANWIDTH_USE_HT;
	पूर्ण

	/* new center frequency segment 0 */
	*pos++ = ieee80211_frequency_to_channel(chandef->center_freq1);
	/* new center frequency segment 1 */
	अगर (chandef->center_freq2)
		*pos++ = ieee80211_frequency_to_channel(chandef->center_freq2);
	अन्यथा
		*pos++ = 0;
पूर्ण

u8 *ieee80211_ie_build_vht_oper(u8 *pos, काष्ठा ieee80211_sta_vht_cap *vht_cap,
				स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_vht_operation *vht_oper;

	*pos++ = WLAN_EID_VHT_OPERATION;
	*pos++ = माप(काष्ठा ieee80211_vht_operation);
	vht_oper = (काष्ठा ieee80211_vht_operation *)pos;
	vht_oper->center_freq_seg0_idx = ieee80211_frequency_to_channel(
							chandef->center_freq1);
	अगर (chandef->center_freq2)
		vht_oper->center_freq_seg1_idx =
			ieee80211_frequency_to_channel(chandef->center_freq2);
	अन्यथा
		vht_oper->center_freq_seg1_idx = 0x00;

	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_160:
		/*
		 * Convert 160 MHz channel width to new style as पूर्णांकerop
		 * workaround.
		 */
		vht_oper->chan_width = IEEE80211_VHT_CHANWIDTH_80MHZ;
		vht_oper->center_freq_seg1_idx = vht_oper->center_freq_seg0_idx;
		अगर (chandef->chan->center_freq < chandef->center_freq1)
			vht_oper->center_freq_seg0_idx -= 8;
		अन्यथा
			vht_oper->center_freq_seg0_idx += 8;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80P80:
		/*
		 * Convert 80+80 MHz channel width to new style as पूर्णांकerop
		 * workaround.
		 */
		vht_oper->chan_width = IEEE80211_VHT_CHANWIDTH_80MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		vht_oper->chan_width = IEEE80211_VHT_CHANWIDTH_80MHZ;
		अवरोध;
	शेष:
		vht_oper->chan_width = IEEE80211_VHT_CHANWIDTH_USE_HT;
		अवरोध;
	पूर्ण

	/* करोn't require special VHT peer rates */
	vht_oper->basic_mcs_set = cpu_to_le16(0xffff);

	वापस pos + माप(काष्ठा ieee80211_vht_operation);
पूर्ण

u8 *ieee80211_ie_build_he_oper(u8 *pos, काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_he_operation *he_oper;
	काष्ठा ieee80211_he_6ghz_oper *he_6ghz_op;
	u32 he_oper_params;
	u8 ie_len = 1 + माप(काष्ठा ieee80211_he_operation);

	अगर (chandef->chan->band == NL80211_BAND_6GHZ)
		ie_len += माप(काष्ठा ieee80211_he_6ghz_oper);

	*pos++ = WLAN_EID_EXTENSION;
	*pos++ = ie_len;
	*pos++ = WLAN_EID_EXT_HE_OPERATION;

	he_oper_params = 0;
	he_oper_params |= u32_encode_bits(1023, /* disabled */
				IEEE80211_HE_OPERATION_RTS_THRESHOLD_MASK);
	he_oper_params |= u32_encode_bits(1,
				IEEE80211_HE_OPERATION_ER_SU_DISABLE);
	he_oper_params |= u32_encode_bits(1,
				IEEE80211_HE_OPERATION_BSS_COLOR_DISABLED);
	अगर (chandef->chan->band == NL80211_BAND_6GHZ)
		he_oper_params |= u32_encode_bits(1,
				IEEE80211_HE_OPERATION_6GHZ_OP_INFO);

	he_oper = (काष्ठा ieee80211_he_operation *)pos;
	he_oper->he_oper_params = cpu_to_le32(he_oper_params);

	/* करोn't require special HE peer rates */
	he_oper->he_mcs_nss_set = cpu_to_le16(0xffff);
	pos += माप(काष्ठा ieee80211_he_operation);

	अगर (chandef->chan->band != NL80211_BAND_6GHZ)
		जाओ out;

	/* TODO add VHT operational */
	he_6ghz_op = (काष्ठा ieee80211_he_6ghz_oper *)pos;
	he_6ghz_op->minrate = 6; /* 6 Mbps */
	he_6ghz_op->primary =
		ieee80211_frequency_to_channel(chandef->chan->center_freq);
	he_6ghz_op->ccfs0 =
		ieee80211_frequency_to_channel(chandef->center_freq1);
	अगर (chandef->center_freq2)
		he_6ghz_op->ccfs1 =
			ieee80211_frequency_to_channel(chandef->center_freq2);
	अन्यथा
		he_6ghz_op->ccfs1 = 0;

	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_160:
		/* Convert 160 MHz channel width to new style as पूर्णांकerop
		 * workaround.
		 */
		he_6ghz_op->control =
			IEEE80211_HE_6GHZ_OPER_CTRL_CHANWIDTH_160MHZ;
		he_6ghz_op->ccfs1 = he_6ghz_op->ccfs0;
		अगर (chandef->chan->center_freq < chandef->center_freq1)
			he_6ghz_op->ccfs0 -= 8;
		अन्यथा
			he_6ghz_op->ccfs0 += 8;
		fallthrough;
	हाल NL80211_CHAN_WIDTH_80P80:
		he_6ghz_op->control =
			IEEE80211_HE_6GHZ_OPER_CTRL_CHANWIDTH_160MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		he_6ghz_op->control =
			IEEE80211_HE_6GHZ_OPER_CTRL_CHANWIDTH_80MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		he_6ghz_op->control =
			IEEE80211_HE_6GHZ_OPER_CTRL_CHANWIDTH_40MHZ;
		अवरोध;
	शेष:
		he_6ghz_op->control =
			IEEE80211_HE_6GHZ_OPER_CTRL_CHANWIDTH_20MHZ;
		अवरोध;
	पूर्ण

	pos += माप(काष्ठा ieee80211_he_6ghz_oper);

out:
	वापस pos;
पूर्ण

bool ieee80211_chandef_ht_oper(स्थिर काष्ठा ieee80211_ht_operation *ht_oper,
			       काष्ठा cfg80211_chan_def *chandef)
अणु
	क्रमागत nl80211_channel_type channel_type;

	अगर (!ht_oper)
		वापस false;

	चयन (ht_oper->ht_param & IEEE80211_HT_PARAM_CHA_SEC_OFFSET) अणु
	हाल IEEE80211_HT_PARAM_CHA_SEC_NONE:
		channel_type = NL80211_CHAN_HT20;
		अवरोध;
	हाल IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
		channel_type = NL80211_CHAN_HT40PLUS;
		अवरोध;
	हाल IEEE80211_HT_PARAM_CHA_SEC_BELOW:
		channel_type = NL80211_CHAN_HT40MINUS;
		अवरोध;
	शेष:
		channel_type = NL80211_CHAN_NO_HT;
		वापस false;
	पूर्ण

	cfg80211_chandef_create(chandef, chandef->chan, channel_type);
	वापस true;
पूर्ण

bool ieee80211_chandef_vht_oper(काष्ठा ieee80211_hw *hw, u32 vht_cap_info,
				स्थिर काष्ठा ieee80211_vht_operation *oper,
				स्थिर काष्ठा ieee80211_ht_operation *htop,
				काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा cfg80211_chan_def new = *chandef;
	पूर्णांक cf0, cf1;
	पूर्णांक ccfs0, ccfs1, ccfs2;
	पूर्णांक ccf0, ccf1;
	u32 vht_cap;
	bool support_80_80 = false;
	bool support_160 = false;
	u8 ext_nss_bw_supp = u32_get_bits(vht_cap_info,
					  IEEE80211_VHT_CAP_EXT_NSS_BW_MASK);
	u8 supp_chwidth = u32_get_bits(vht_cap_info,
				       IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK);

	अगर (!oper || !htop)
		वापस false;

	vht_cap = hw->wiphy->bands[chandef->chan->band]->vht_cap.cap;
	support_160 = (vht_cap & (IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK |
				  IEEE80211_VHT_CAP_EXT_NSS_BW_MASK));
	support_80_80 = ((vht_cap &
			 IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ) ||
			(vht_cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ &&
			 vht_cap & IEEE80211_VHT_CAP_EXT_NSS_BW_MASK) ||
			((vht_cap & IEEE80211_VHT_CAP_EXT_NSS_BW_MASK) >>
				    IEEE80211_VHT_CAP_EXT_NSS_BW_SHIFT > 1));
	ccfs0 = oper->center_freq_seg0_idx;
	ccfs1 = oper->center_freq_seg1_idx;
	ccfs2 = (le16_to_cpu(htop->operation_mode) &
				IEEE80211_HT_OP_MODE_CCFS2_MASK)
			>> IEEE80211_HT_OP_MODE_CCFS2_SHIFT;

	ccf0 = ccfs0;

	/* अगर not supported, parse as though we didn't understand it */
	अगर (!ieee80211_hw_check(hw, SUPPORTS_VHT_EXT_NSS_BW))
		ext_nss_bw_supp = 0;

	/*
	 * Cf. IEEE 802.11 Table 9-250
	 *
	 * We really just consider that because it's inefficient to connect
	 * at a higher bandwidth than we'll actually be able to use.
	 */
	चयन ((supp_chwidth << 4) | ext_nss_bw_supp) अणु
	शेष:
	हाल 0x00:
		ccf1 = 0;
		support_160 = false;
		support_80_80 = false;
		अवरोध;
	हाल 0x01:
		support_80_80 = false;
		fallthrough;
	हाल 0x02:
	हाल 0x03:
		ccf1 = ccfs2;
		अवरोध;
	हाल 0x10:
		ccf1 = ccfs1;
		अवरोध;
	हाल 0x11:
	हाल 0x12:
		अगर (!ccfs1)
			ccf1 = ccfs2;
		अन्यथा
			ccf1 = ccfs1;
		अवरोध;
	हाल 0x13:
	हाल 0x20:
	हाल 0x23:
		ccf1 = ccfs1;
		अवरोध;
	पूर्ण

	cf0 = ieee80211_channel_to_frequency(ccf0, chandef->chan->band);
	cf1 = ieee80211_channel_to_frequency(ccf1, chandef->chan->band);

	चयन (oper->chan_width) अणु
	हाल IEEE80211_VHT_CHANWIDTH_USE_HT:
		/* just use HT inक्रमmation directly */
		अवरोध;
	हाल IEEE80211_VHT_CHANWIDTH_80MHZ:
		new.width = NL80211_CHAN_WIDTH_80;
		new.center_freq1 = cf0;
		/* If needed, adjust based on the newer पूर्णांकerop workaround. */
		अगर (ccf1) अणु
			अचिन्हित पूर्णांक dअगरf;

			dअगरf = असल(ccf1 - ccf0);
			अगर ((dअगरf == 8) && support_160) अणु
				new.width = NL80211_CHAN_WIDTH_160;
				new.center_freq1 = cf1;
			पूर्ण अन्यथा अगर ((dअगरf > 8) && support_80_80) अणु
				new.width = NL80211_CHAN_WIDTH_80P80;
				new.center_freq2 = cf1;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल IEEE80211_VHT_CHANWIDTH_160MHZ:
		/* deprecated encoding */
		new.width = NL80211_CHAN_WIDTH_160;
		new.center_freq1 = cf0;
		अवरोध;
	हाल IEEE80211_VHT_CHANWIDTH_80P80MHZ:
		/* deprecated encoding */
		new.width = NL80211_CHAN_WIDTH_80P80;
		new.center_freq1 = cf0;
		new.center_freq2 = cf1;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (!cfg80211_chandef_valid(&new))
		वापस false;

	*chandef = new;
	वापस true;
पूर्ण

bool ieee80211_chandef_he_6ghz_oper(काष्ठा ieee80211_sub_अगर_data *sdata,
				    स्थिर काष्ठा ieee80211_he_operation *he_oper,
				    काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_supported_band *sband;
	क्रमागत nl80211_अगरtype अगरtype = ieee80211_vअगर_type_p2p(&sdata->vअगर);
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap;
	काष्ठा cfg80211_chan_def he_chandef = *chandef;
	स्थिर काष्ठा ieee80211_he_6ghz_oper *he_6ghz_oper;
	bool support_80_80, support_160;
	u8 he_phy_cap;
	u32 freq;

	अगर (chandef->chan->band != NL80211_BAND_6GHZ)
		वापस true;

	sband = local->hw.wiphy->bands[NL80211_BAND_6GHZ];

	he_cap = ieee80211_get_he_अगरtype_cap(sband, अगरtype);
	अगर (!he_cap) अणु
		sdata_info(sdata, "Missing iftype sband data/HE cap");
		वापस false;
	पूर्ण

	he_phy_cap = he_cap->he_cap_elem.phy_cap_info[0];
	support_160 =
		he_phy_cap &
		IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G;
	support_80_80 =
		he_phy_cap &
		IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G;

	अगर (!he_oper) अणु
		sdata_info(sdata,
			   "HE is not advertised on (on %d MHz), expect issues\n",
			   chandef->chan->center_freq);
		वापस false;
	पूर्ण

	he_6ghz_oper = ieee80211_he_6ghz_oper(he_oper);

	अगर (!he_6ghz_oper) अणु
		sdata_info(sdata,
			   "HE 6GHz operation missing (on %d MHz), expect issues\n",
			   chandef->chan->center_freq);
		वापस false;
	पूर्ण

	freq = ieee80211_channel_to_frequency(he_6ghz_oper->primary,
					      NL80211_BAND_6GHZ);
	he_chandef.chan = ieee80211_get_channel(sdata->local->hw.wiphy, freq);

	चयन (u8_get_bits(he_6ghz_oper->control,
			    IEEE80211_HE_6GHZ_OPER_CTRL_CHANWIDTH)) अणु
	हाल IEEE80211_HE_6GHZ_OPER_CTRL_CHANWIDTH_20MHZ:
		he_chandef.width = NL80211_CHAN_WIDTH_20;
		अवरोध;
	हाल IEEE80211_HE_6GHZ_OPER_CTRL_CHANWIDTH_40MHZ:
		he_chandef.width = NL80211_CHAN_WIDTH_40;
		अवरोध;
	हाल IEEE80211_HE_6GHZ_OPER_CTRL_CHANWIDTH_80MHZ:
		he_chandef.width = NL80211_CHAN_WIDTH_80;
		अवरोध;
	हाल IEEE80211_HE_6GHZ_OPER_CTRL_CHANWIDTH_160MHZ:
		he_chandef.width = NL80211_CHAN_WIDTH_80;
		अगर (!he_6ghz_oper->ccfs1)
			अवरोध;
		अगर (असल(he_6ghz_oper->ccfs1 - he_6ghz_oper->ccfs0) == 8) अणु
			अगर (support_160)
				he_chandef.width = NL80211_CHAN_WIDTH_160;
		पूर्ण अन्यथा अणु
			अगर (support_80_80)
				he_chandef.width = NL80211_CHAN_WIDTH_80P80;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (he_chandef.width == NL80211_CHAN_WIDTH_160) अणु
		he_chandef.center_freq1 =
			ieee80211_channel_to_frequency(he_6ghz_oper->ccfs1,
						       NL80211_BAND_6GHZ);
	पूर्ण अन्यथा अणु
		he_chandef.center_freq1 =
			ieee80211_channel_to_frequency(he_6ghz_oper->ccfs0,
						       NL80211_BAND_6GHZ);
		अगर (support_80_80 || support_160)
			he_chandef.center_freq2 =
				ieee80211_channel_to_frequency(he_6ghz_oper->ccfs1,
							       NL80211_BAND_6GHZ);
	पूर्ण

	अगर (!cfg80211_chandef_valid(&he_chandef)) अणु
		sdata_info(sdata,
			   "HE 6GHz operation resulted in invalid chandef: %d MHz/%d/%d MHz/%d MHz\n",
			   he_chandef.chan ? he_chandef.chan->center_freq : 0,
			   he_chandef.width,
			   he_chandef.center_freq1,
			   he_chandef.center_freq2);
		वापस false;
	पूर्ण

	*chandef = he_chandef;

	वापस true;
पूर्ण

bool ieee80211_chandef_s1g_oper(स्थिर काष्ठा ieee80211_s1g_oper_ie *oper,
				काष्ठा cfg80211_chan_def *chandef)
अणु
	u32 oper_freq;

	अगर (!oper)
		वापस false;

	चयन (FIELD_GET(S1G_OPER_CH_WIDTH_OPER, oper->ch_width)) अणु
	हाल IEEE80211_S1G_CHANWIDTH_1MHZ:
		chandef->width = NL80211_CHAN_WIDTH_1;
		अवरोध;
	हाल IEEE80211_S1G_CHANWIDTH_2MHZ:
		chandef->width = NL80211_CHAN_WIDTH_2;
		अवरोध;
	हाल IEEE80211_S1G_CHANWIDTH_4MHZ:
		chandef->width = NL80211_CHAN_WIDTH_4;
		अवरोध;
	हाल IEEE80211_S1G_CHANWIDTH_8MHZ:
		chandef->width = NL80211_CHAN_WIDTH_8;
		अवरोध;
	हाल IEEE80211_S1G_CHANWIDTH_16MHZ:
		chandef->width = NL80211_CHAN_WIDTH_16;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	oper_freq = ieee80211_channel_to_freq_khz(oper->oper_ch,
						  NL80211_BAND_S1GHZ);
	chandef->center_freq1 = KHZ_TO_MHZ(oper_freq);
	chandef->freq1_offset = oper_freq % 1000;

	वापस true;
पूर्ण

पूर्णांक ieee80211_parse_bitrates(काष्ठा cfg80211_chan_def *chandef,
			     स्थिर काष्ठा ieee80211_supported_band *sband,
			     स्थिर u8 *srates, पूर्णांक srates_len, u32 *rates)
अणु
	u32 rate_flags = ieee80211_chandef_rate_flags(chandef);
	पूर्णांक shअगरt = ieee80211_chandef_get_shअगरt(chandef);
	काष्ठा ieee80211_rate *br;
	पूर्णांक brate, rate, i, j, count = 0;

	*rates = 0;

	क्रम (i = 0; i < srates_len; i++) अणु
		rate = srates[i] & 0x7f;

		क्रम (j = 0; j < sband->n_bitrates; j++) अणु
			br = &sband->bitrates[j];
			अगर ((rate_flags & br->flags) != rate_flags)
				जारी;

			brate = DIV_ROUND_UP(br->bitrate, (1 << shअगरt) * 5);
			अगर (brate == rate) अणु
				*rates |= BIT(j);
				count++;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

पूर्णांक ieee80211_add_srates_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
			    काष्ठा sk_buff *skb, bool need_basic,
			    क्रमागत nl80211_band band)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_supported_band *sband;
	पूर्णांक rate, shअगरt;
	u8 i, rates, *pos;
	u32 basic_rates = sdata->vअगर.bss_conf.basic_rates;
	u32 rate_flags;

	shअगरt = ieee80211_vअगर_get_shअगरt(&sdata->vअगर);
	rate_flags = ieee80211_chandef_rate_flags(&sdata->vअगर.bss_conf.chandef);
	sband = local->hw.wiphy->bands[band];
	rates = 0;
	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		अगर ((rate_flags & sband->bitrates[i].flags) != rate_flags)
			जारी;
		rates++;
	पूर्ण
	अगर (rates > 8)
		rates = 8;

	अगर (skb_tailroom(skb) < rates + 2)
		वापस -ENOMEM;

	pos = skb_put(skb, rates + 2);
	*pos++ = WLAN_EID_SUPP_RATES;
	*pos++ = rates;
	क्रम (i = 0; i < rates; i++) अणु
		u8 basic = 0;
		अगर ((rate_flags & sband->bitrates[i].flags) != rate_flags)
			जारी;

		अगर (need_basic && basic_rates & BIT(i))
			basic = 0x80;
		rate = DIV_ROUND_UP(sband->bitrates[i].bitrate,
				    5 * (1 << shअगरt));
		*pos++ = basic | (u8) rate;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ieee80211_add_ext_srates_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
				काष्ठा sk_buff *skb, bool need_basic,
				क्रमागत nl80211_band band)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_supported_band *sband;
	पूर्णांक rate, shअगरt;
	u8 i, exrates, *pos;
	u32 basic_rates = sdata->vअगर.bss_conf.basic_rates;
	u32 rate_flags;

	rate_flags = ieee80211_chandef_rate_flags(&sdata->vअगर.bss_conf.chandef);
	shअगरt = ieee80211_vअगर_get_shअगरt(&sdata->vअगर);

	sband = local->hw.wiphy->bands[band];
	exrates = 0;
	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		अगर ((rate_flags & sband->bitrates[i].flags) != rate_flags)
			जारी;
		exrates++;
	पूर्ण

	अगर (exrates > 8)
		exrates -= 8;
	अन्यथा
		exrates = 0;

	अगर (skb_tailroom(skb) < exrates + 2)
		वापस -ENOMEM;

	अगर (exrates) अणु
		pos = skb_put(skb, exrates + 2);
		*pos++ = WLAN_EID_EXT_SUPP_RATES;
		*pos++ = exrates;
		क्रम (i = 8; i < sband->n_bitrates; i++) अणु
			u8 basic = 0;
			अगर ((rate_flags & sband->bitrates[i].flags)
			    != rate_flags)
				जारी;
			अगर (need_basic && basic_rates & BIT(i))
				basic = 0x80;
			rate = DIV_ROUND_UP(sband->bitrates[i].bitrate,
					    5 * (1 << shअगरt));
			*pos++ = basic | (u8) rate;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ieee80211_ave_rssi(काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;

	अगर (WARN_ON_ONCE(sdata->vअगर.type != NL80211_IFTYPE_STATION)) अणु
		/* non-managed type inferfaces */
		वापस 0;
	पूर्ण
	वापस -ewma_beacon_संकेत_पढ़ो(&अगरmgd->ave_beacon_संकेत);
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_ave_rssi);

u8 ieee80211_mcs_to_chains(स्थिर काष्ठा ieee80211_mcs_info *mcs)
अणु
	अगर (!mcs)
		वापस 1;

	/* TODO: consider rx_highest */

	अगर (mcs->rx_mask[3])
		वापस 4;
	अगर (mcs->rx_mask[2])
		वापस 3;
	अगर (mcs->rx_mask[1])
		वापस 2;
	वापस 1;
पूर्ण

/**
 * ieee80211_calculate_rx_बारtamp - calculate बारtamp in frame
 * @local: mac80211 hw info काष्ठा
 * @status: RX status
 * @mpdu_len: total MPDU length (including FCS)
 * @mpdu_offset: offset पूर्णांकo MPDU to calculate बारtamp at
 *
 * This function calculates the RX बारtamp at the given MPDU offset, taking
 * पूर्णांकo account what the RX बारtamp was. An offset of 0 will just normalize
 * the बारtamp to TSF at beginning of MPDU reception.
 */
u64 ieee80211_calculate_rx_बारtamp(काष्ठा ieee80211_local *local,
				     काष्ठा ieee80211_rx_status *status,
				     अचिन्हित पूर्णांक mpdu_len,
				     अचिन्हित पूर्णांक mpdu_offset)
अणु
	u64 ts = status->maस_समय;
	काष्ठा rate_info ri;
	u16 rate;
	u8 n_ltf;

	अगर (WARN_ON(!ieee80211_have_rx_बारtamp(status)))
		वापस 0;

	स_रखो(&ri, 0, माप(ri));

	ri.bw = status->bw;

	/* Fill cfg80211 rate info */
	चयन (status->encoding) अणु
	हाल RX_ENC_HE:
		ri.flags |= RATE_INFO_FLAGS_HE_MCS;
		ri.mcs = status->rate_idx;
		ri.nss = status->nss;
		ri.he_ru_alloc = status->he_ru;
		अगर (status->enc_flags & RX_ENC_FLAG_SHORT_GI)
			ri.flags |= RATE_INFO_FLAGS_SHORT_GI;

		/*
		 * See P802.11ax_D6.0, section 27.3.4 क्रम
		 * VHT PPDU क्रमmat.
		 */
		अगर (status->flag & RX_FLAG_MACTIME_PLCP_START) अणु
			mpdu_offset += 2;
			ts += 36;

			/*
			 * TODO:
			 * For HE MU PPDU, add the HE-SIG-B.
			 * For HE ER PPDU, add 8us क्रम the HE-SIG-A.
			 * For HE TB PPDU, add 4us क्रम the HE-STF.
			 * Add the HE-LTF durations - variable.
			 */
		पूर्ण

		अवरोध;
	हाल RX_ENC_HT:
		ri.mcs = status->rate_idx;
		ri.flags |= RATE_INFO_FLAGS_MCS;
		अगर (status->enc_flags & RX_ENC_FLAG_SHORT_GI)
			ri.flags |= RATE_INFO_FLAGS_SHORT_GI;

		/*
		 * See P802.11REVmd_D3.0, section 19.3.2 क्रम
		 * HT PPDU क्रमmat.
		 */
		अगर (status->flag & RX_FLAG_MACTIME_PLCP_START) अणु
			mpdu_offset += 2;
			अगर (status->enc_flags & RX_ENC_FLAG_HT_GF)
				ts += 24;
			अन्यथा
				ts += 32;

			/*
			 * Add Data HT-LTFs per streams
			 * TODO: add Extension HT-LTFs, 4us per LTF
			 */
			n_ltf = ((ri.mcs >> 3) & 3) + 1;
			n_ltf = n_ltf == 3 ? 4 : n_ltf;
			ts += n_ltf * 4;
		पूर्ण

		अवरोध;
	हाल RX_ENC_VHT:
		ri.flags |= RATE_INFO_FLAGS_VHT_MCS;
		ri.mcs = status->rate_idx;
		ri.nss = status->nss;
		अगर (status->enc_flags & RX_ENC_FLAG_SHORT_GI)
			ri.flags |= RATE_INFO_FLAGS_SHORT_GI;

		/*
		 * See P802.11REVmd_D3.0, section 21.3.2 क्रम
		 * VHT PPDU क्रमmat.
		 */
		अगर (status->flag & RX_FLAG_MACTIME_PLCP_START) अणु
			mpdu_offset += 2;
			ts += 36;

			/*
			 * Add VHT-LTFs per streams
			 */
			n_ltf = (ri.nss != 1) && (ri.nss % 2) ?
				ri.nss + 1 : ri.nss;
			ts += 4 * n_ltf;
		पूर्ण

		अवरोध;
	शेष:
		WARN_ON(1);
		fallthrough;
	हाल RX_ENC_LEGACY: अणु
		काष्ठा ieee80211_supported_band *sband;
		पूर्णांक shअगरt = 0;
		पूर्णांक bitrate;

		चयन (status->bw) अणु
		हाल RATE_INFO_BW_10:
			shअगरt = 1;
			अवरोध;
		हाल RATE_INFO_BW_5:
			shअगरt = 2;
			अवरोध;
		पूर्ण

		sband = local->hw.wiphy->bands[status->band];
		bitrate = sband->bitrates[status->rate_idx].bitrate;
		ri.legacy = DIV_ROUND_UP(bitrate, (1 << shअगरt));

		अगर (status->flag & RX_FLAG_MACTIME_PLCP_START) अणु
			अगर (status->band == NL80211_BAND_5GHZ) अणु
				ts += 20 << shअगरt;
				mpdu_offset += 2;
			पूर्ण अन्यथा अगर (status->enc_flags & RX_ENC_FLAG_SHORTPRE) अणु
				ts += 96;
			पूर्ण अन्यथा अणु
				ts += 192;
			पूर्ण
		पूर्ण
		अवरोध;
		पूर्ण
	पूर्ण

	rate = cfg80211_calculate_bitrate(&ri);
	अगर (WARN_ONCE(!rate,
		      "Invalid bitrate: flags=0x%llx, idx=%d, vht_nss=%d\n",
		      (अचिन्हित दीर्घ दीर्घ)status->flag, status->rate_idx,
		      status->nss))
		वापस 0;

	/* शुरुआत from end of MPDU */
	अगर (status->flag & RX_FLAG_MACTIME_END)
		ts -= mpdu_len * 8 * 10 / rate;

	ts += mpdu_offset * 8 * 10 / rate;

	वापस ts;
पूर्ण

व्योम ieee80211_dfs_cac_cancel(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा cfg80211_chan_def chandef;

	/* क्रम पूर्णांकerface list, to aव्योम linking अगरlist_mtx and chanctx_mtx */
	lockdep_निश्चित_wiphy(local->hw.wiphy);

	mutex_lock(&local->mtx);
	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		/* it might be रुकोing क्रम the local->mtx, but then
		 * by the समय it माला_लो it, sdata->wdev.cac_started
		 * will no दीर्घer be true
		 */
		cancel_delayed_work(&sdata->dfs_cac_समयr_work);

		अगर (sdata->wdev.cac_started) अणु
			chandef = sdata->vअगर.bss_conf.chandef;
			ieee80211_vअगर_release_channel(sdata);
			cfg80211_cac_event(sdata->dev,
					   &chandef,
					   NL80211_RADAR_CAC_ABORTED,
					   GFP_KERNEL);
		पूर्ण
	पूर्ण
	mutex_unlock(&local->mtx);
पूर्ण

व्योम ieee80211_dfs_radar_detected_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_local *local =
		container_of(work, काष्ठा ieee80211_local, radar_detected_work);
	काष्ठा cfg80211_chan_def chandef = local->hw.conf.chandef;
	काष्ठा ieee80211_chanctx *ctx;
	पूर्णांक num_chanctx = 0;

	mutex_lock(&local->chanctx_mtx);
	list_क्रम_each_entry(ctx, &local->chanctx_list, list) अणु
		अगर (ctx->replace_state == IEEE80211_CHANCTX_REPLACES_OTHER)
			जारी;

		num_chanctx++;
		chandef = ctx->conf.def;
	पूर्ण
	mutex_unlock(&local->chanctx_mtx);

	wiphy_lock(local->hw.wiphy);
	ieee80211_dfs_cac_cancel(local);
	wiphy_unlock(local->hw.wiphy);

	अगर (num_chanctx > 1)
		/* XXX: multi-channel is not supported yet */
		WARN_ON(1);
	अन्यथा
		cfg80211_radar_event(local->hw.wiphy, &chandef, GFP_KERNEL);
पूर्ण

व्योम ieee80211_radar_detected(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	trace_api_radar_detected(local);

	schedule_work(&local->radar_detected_work);
पूर्ण
EXPORT_SYMBOL(ieee80211_radar_detected);

u32 ieee80211_chandef_करोwngrade(काष्ठा cfg80211_chan_def *c)
अणु
	u32 ret;
	पूर्णांक पंचांगp;

	चयन (c->width) अणु
	हाल NL80211_CHAN_WIDTH_20:
		c->width = NL80211_CHAN_WIDTH_20_NOHT;
		ret = IEEE80211_STA_DISABLE_HT | IEEE80211_STA_DISABLE_VHT;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		c->width = NL80211_CHAN_WIDTH_20;
		c->center_freq1 = c->chan->center_freq;
		ret = IEEE80211_STA_DISABLE_40MHZ |
		      IEEE80211_STA_DISABLE_VHT;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		पंचांगp = (30 + c->chan->center_freq - c->center_freq1)/20;
		/* n_P40 */
		पंचांगp /= 2;
		/* freq_P40 */
		c->center_freq1 = c->center_freq1 - 20 + 40 * पंचांगp;
		c->width = NL80211_CHAN_WIDTH_40;
		ret = IEEE80211_STA_DISABLE_VHT;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80P80:
		c->center_freq2 = 0;
		c->width = NL80211_CHAN_WIDTH_80;
		ret = IEEE80211_STA_DISABLE_80P80MHZ |
		      IEEE80211_STA_DISABLE_160MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_160:
		/* n_P20 */
		पंचांगp = (70 + c->chan->center_freq - c->center_freq1)/20;
		/* n_P80 */
		पंचांगp /= 4;
		c->center_freq1 = c->center_freq1 - 40 + 80 * पंचांगp;
		c->width = NL80211_CHAN_WIDTH_80;
		ret = IEEE80211_STA_DISABLE_80P80MHZ |
		      IEEE80211_STA_DISABLE_160MHZ;
		अवरोध;
	शेष:
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		WARN_ON_ONCE(1);
		c->width = NL80211_CHAN_WIDTH_20_NOHT;
		ret = IEEE80211_STA_DISABLE_HT | IEEE80211_STA_DISABLE_VHT;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_1:
	हाल NL80211_CHAN_WIDTH_2:
	हाल NL80211_CHAN_WIDTH_4:
	हाल NL80211_CHAN_WIDTH_8:
	हाल NL80211_CHAN_WIDTH_16:
	हाल NL80211_CHAN_WIDTH_5:
	हाल NL80211_CHAN_WIDTH_10:
		WARN_ON_ONCE(1);
		/* keep c->width */
		ret = IEEE80211_STA_DISABLE_HT | IEEE80211_STA_DISABLE_VHT;
		अवरोध;
	पूर्ण

	WARN_ON_ONCE(!cfg80211_chandef_valid(c));

	वापस ret;
पूर्ण

/*
 * Returns true अगर smps_mode_new is strictly more restrictive than
 * smps_mode_old.
 */
bool ieee80211_smps_is_restrictive(क्रमागत ieee80211_smps_mode smps_mode_old,
				   क्रमागत ieee80211_smps_mode smps_mode_new)
अणु
	अगर (WARN_ON_ONCE(smps_mode_old == IEEE80211_SMPS_AUTOMATIC ||
			 smps_mode_new == IEEE80211_SMPS_AUTOMATIC))
		वापस false;

	चयन (smps_mode_old) अणु
	हाल IEEE80211_SMPS_STATIC:
		वापस false;
	हाल IEEE80211_SMPS_DYNAMIC:
		वापस smps_mode_new == IEEE80211_SMPS_STATIC;
	हाल IEEE80211_SMPS_OFF:
		वापस smps_mode_new != IEEE80211_SMPS_OFF;
	शेष:
		WARN_ON(1);
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक ieee80211_send_action_csa(काष्ठा ieee80211_sub_अगर_data *sdata,
			      काष्ठा cfg80211_csa_settings *csa_settings)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *mgmt;
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक freq;
	पूर्णांक hdr_len = दुरत्वend(काष्ठा ieee80211_mgmt,
				  u.action.u.chan_चयन);
	u8 *pos;

	अगर (sdata->vअगर.type != NL80211_IFTYPE_ADHOC &&
	    sdata->vअगर.type != NL80211_IFTYPE_MESH_POINT)
		वापस -EOPNOTSUPP;

	skb = dev_alloc_skb(local->tx_headroom + hdr_len +
			    5 + /* channel चयन announcement element */
			    3 + /* secondary channel offset element */
			    5 + /* wide bandwidth channel चयन announcement */
			    8); /* mesh channel चयन parameters element */
	अगर (!skb)
		वापस -ENOMEM;

	skb_reserve(skb, local->tx_headroom);
	mgmt = skb_put_zero(skb, hdr_len);
	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);

	eth_broadcast_addr(mgmt->da);
	स_नकल(mgmt->sa, sdata->vअगर.addr, ETH_ALEN);
	अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर)) अणु
		स_नकल(mgmt->bssid, sdata->vअगर.addr, ETH_ALEN);
	पूर्ण अन्यथा अणु
		काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
		स_नकल(mgmt->bssid, अगरibss->bssid, ETH_ALEN);
	पूर्ण
	mgmt->u.action.category = WLAN_CATEGORY_SPECTRUM_MGMT;
	mgmt->u.action.u.chan_चयन.action_code = WLAN_ACTION_SPCT_CHL_SWITCH;
	pos = skb_put(skb, 5);
	*pos++ = WLAN_EID_CHANNEL_SWITCH;			/* EID */
	*pos++ = 3;						/* IE length */
	*pos++ = csa_settings->block_tx ? 1 : 0;		/* CSA mode */
	freq = csa_settings->chandef.chan->center_freq;
	*pos++ = ieee80211_frequency_to_channel(freq);		/* channel */
	*pos++ = csa_settings->count;				/* count */

	अगर (csa_settings->chandef.width == NL80211_CHAN_WIDTH_40) अणु
		क्रमागत nl80211_channel_type ch_type;

		skb_put(skb, 3);
		*pos++ = WLAN_EID_SECONDARY_CHANNEL_OFFSET;	/* EID */
		*pos++ = 1;					/* IE length */
		ch_type = cfg80211_get_chandef_type(&csa_settings->chandef);
		अगर (ch_type == NL80211_CHAN_HT40PLUS)
			*pos++ = IEEE80211_HT_PARAM_CHA_SEC_ABOVE;
		अन्यथा
			*pos++ = IEEE80211_HT_PARAM_CHA_SEC_BELOW;
	पूर्ण

	अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर)) अणु
		काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;

		skb_put(skb, 8);
		*pos++ = WLAN_EID_CHAN_SWITCH_PARAM;		/* EID */
		*pos++ = 6;					/* IE length */
		*pos++ = sdata->u.mesh.mshcfg.करोt11MeshTTL;	/* Mesh TTL */
		*pos = 0x00;	/* Mesh Flag: Tx Restrict, Initiator, Reason */
		*pos |= WLAN_EID_CHAN_SWITCH_PARAM_INITIATOR;
		*pos++ |= csa_settings->block_tx ?
			  WLAN_EID_CHAN_SWITCH_PARAM_TX_RESTRICT : 0x00;
		put_unaligned_le16(WLAN_REASON_MESH_CHAN, pos); /* Reason Cd */
		pos += 2;
		put_unaligned_le16(अगरmsh->pre_value, pos);/* Precedence Value */
		pos += 2;
	पूर्ण

	अगर (csa_settings->chandef.width == NL80211_CHAN_WIDTH_80 ||
	    csa_settings->chandef.width == NL80211_CHAN_WIDTH_80P80 ||
	    csa_settings->chandef.width == NL80211_CHAN_WIDTH_160) अणु
		skb_put(skb, 5);
		ieee80211_ie_build_wide_bw_cs(pos, &csa_settings->chandef);
	पूर्ण

	ieee80211_tx_skb(sdata, skb);
	वापस 0;
पूर्ण

bool ieee80211_cs_valid(स्थिर काष्ठा ieee80211_cipher_scheme *cs)
अणु
	वापस !(cs == शून्य || cs->cipher == 0 ||
		 cs->hdr_len < cs->pn_len + cs->pn_off ||
		 cs->hdr_len <= cs->key_idx_off ||
		 cs->key_idx_shअगरt > 7 ||
		 cs->key_idx_mask == 0);
पूर्ण

bool ieee80211_cs_list_valid(स्थिर काष्ठा ieee80211_cipher_scheme *cs, पूर्णांक n)
अणु
	पूर्णांक i;

	/* Ensure we have enough अगरtype biपंचांगap space क्रम all अगरtype values */
	WARN_ON((NUM_NL80211_IFTYPES / 8 + 1) > माप(cs[0].अगरtype));

	क्रम (i = 0; i < n; i++)
		अगर (!ieee80211_cs_valid(&cs[i]))
			वापस false;

	वापस true;
पूर्ण

स्थिर काष्ठा ieee80211_cipher_scheme *
ieee80211_cs_get(काष्ठा ieee80211_local *local, u32 cipher,
		 क्रमागत nl80211_अगरtype अगरtype)
अणु
	स्थिर काष्ठा ieee80211_cipher_scheme *l = local->hw.cipher_schemes;
	पूर्णांक n = local->hw.n_cipher_schemes;
	पूर्णांक i;
	स्थिर काष्ठा ieee80211_cipher_scheme *cs = शून्य;

	क्रम (i = 0; i < n; i++) अणु
		अगर (l[i].cipher == cipher) अणु
			cs = &l[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!cs || !(cs->अगरtype & BIT(अगरtype)))
		वापस शून्य;

	वापस cs;
पूर्ण

पूर्णांक ieee80211_cs_headroom(काष्ठा ieee80211_local *local,
			  काष्ठा cfg80211_crypto_settings *crypto,
			  क्रमागत nl80211_अगरtype अगरtype)
अणु
	स्थिर काष्ठा ieee80211_cipher_scheme *cs;
	पूर्णांक headroom = IEEE80211_ENCRYPT_HEADROOM;
	पूर्णांक i;

	क्रम (i = 0; i < crypto->n_ciphers_pairwise; i++) अणु
		cs = ieee80211_cs_get(local, crypto->ciphers_pairwise[i],
				      अगरtype);

		अगर (cs && headroom < cs->hdr_len)
			headroom = cs->hdr_len;
	पूर्ण

	cs = ieee80211_cs_get(local, crypto->cipher_group, अगरtype);
	अगर (cs && headroom < cs->hdr_len)
		headroom = cs->hdr_len;

	वापस headroom;
पूर्ण

अटल bool
ieee80211_extend_noa_desc(काष्ठा ieee80211_noa_data *data, u32 tsf, पूर्णांक i)
अणु
	s32 end = data->desc[i].start + data->desc[i].duration - (tsf + 1);
	पूर्णांक skip;

	अगर (end > 0)
		वापस false;

	/* One shot NOA  */
	अगर (data->count[i] == 1)
		वापस false;

	अगर (data->desc[i].पूर्णांकerval == 0)
		वापस false;

	/* End समय is in the past, check क्रम repetitions */
	skip = DIV_ROUND_UP(-end, data->desc[i].पूर्णांकerval);
	अगर (data->count[i] < 255) अणु
		अगर (data->count[i] <= skip) अणु
			data->count[i] = 0;
			वापस false;
		पूर्ण

		data->count[i] -= skip;
	पूर्ण

	data->desc[i].start += skip * data->desc[i].पूर्णांकerval;

	वापस true;
पूर्ण

अटल bool
ieee80211_extend_असलent_समय(काष्ठा ieee80211_noa_data *data, u32 tsf,
			     s32 *offset)
अणु
	bool ret = false;
	पूर्णांक i;

	क्रम (i = 0; i < IEEE80211_P2P_NOA_DESC_MAX; i++) अणु
		s32 cur;

		अगर (!data->count[i])
			जारी;

		अगर (ieee80211_extend_noa_desc(data, tsf + *offset, i))
			ret = true;

		cur = data->desc[i].start - tsf;
		अगर (cur > *offset)
			जारी;

		cur = data->desc[i].start + data->desc[i].duration - tsf;
		अगर (cur > *offset)
			*offset = cur;
	पूर्ण

	वापस ret;
पूर्ण

अटल u32
ieee80211_get_noa_असलent_समय(काष्ठा ieee80211_noa_data *data, u32 tsf)
अणु
	s32 offset = 0;
	पूर्णांक tries = 0;
	/*
	 * arbitrary limit, used to aव्योम infinite loops when combined NoA
	 * descriptors cover the full समय period.
	 */
	पूर्णांक max_tries = 5;

	ieee80211_extend_असलent_समय(data, tsf, &offset);
	करो अणु
		अगर (!ieee80211_extend_असलent_समय(data, tsf, &offset))
			अवरोध;

		tries++;
	पूर्ण जबतक (tries < max_tries);

	वापस offset;
पूर्ण

व्योम ieee80211_update_p2p_noa(काष्ठा ieee80211_noa_data *data, u32 tsf)
अणु
	u32 next_offset = BIT(31) - 1;
	पूर्णांक i;

	data->असलent = 0;
	data->has_next_tsf = false;
	क्रम (i = 0; i < IEEE80211_P2P_NOA_DESC_MAX; i++) अणु
		s32 start;

		अगर (!data->count[i])
			जारी;

		ieee80211_extend_noa_desc(data, tsf, i);
		start = data->desc[i].start - tsf;
		अगर (start <= 0)
			data->असलent |= BIT(i);

		अगर (next_offset > start)
			next_offset = start;

		data->has_next_tsf = true;
	पूर्ण

	अगर (data->असलent)
		next_offset = ieee80211_get_noa_असलent_समय(data, tsf);

	data->next_tsf = tsf + next_offset;
पूर्ण
EXPORT_SYMBOL(ieee80211_update_p2p_noa);

पूर्णांक ieee80211_parse_p2p_noa(स्थिर काष्ठा ieee80211_p2p_noa_attr *attr,
			    काष्ठा ieee80211_noa_data *data, u32 tsf)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	स_रखो(data, 0, माप(*data));

	क्रम (i = 0; i < IEEE80211_P2P_NOA_DESC_MAX; i++) अणु
		स्थिर काष्ठा ieee80211_p2p_noa_desc *desc = &attr->desc[i];

		अगर (!desc->count || !desc->duration)
			जारी;

		data->count[i] = desc->count;
		data->desc[i].start = le32_to_cpu(desc->start_समय);
		data->desc[i].duration = le32_to_cpu(desc->duration);
		data->desc[i].पूर्णांकerval = le32_to_cpu(desc->पूर्णांकerval);

		अगर (data->count[i] > 1 &&
		    data->desc[i].पूर्णांकerval < data->desc[i].duration)
			जारी;

		ieee80211_extend_noa_desc(data, tsf, i);
		ret++;
	पूर्ण

	अगर (ret)
		ieee80211_update_p2p_noa(data, tsf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ieee80211_parse_p2p_noa);

व्योम ieee80211_recalc_dtim(काष्ठा ieee80211_local *local,
			   काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	u64 tsf = drv_get_tsf(local, sdata);
	u64 dtim_count = 0;
	u16 beacon_पूर्णांक = sdata->vअगर.bss_conf.beacon_पूर्णांक * 1024;
	u8 dtim_period = sdata->vअगर.bss_conf.dtim_period;
	काष्ठा ps_data *ps;
	u8 bcns_from_dtim;

	अगर (tsf == -1ULL || !beacon_पूर्णांक || !dtim_period)
		वापस;

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP ||
	    sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN) अणु
		अगर (!sdata->bss)
			वापस;

		ps = &sdata->bss->ps;
	पूर्ण अन्यथा अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर)) अणु
		ps = &sdata->u.mesh.ps;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	/*
	 * actually finds last dtim_count, mac80211 will update in
	 * __beacon_add_tim().
	 * dtim_count = dtim_period - (tsf / bcn_पूर्णांक) % dtim_period
	 */
	करो_भाग(tsf, beacon_पूर्णांक);
	bcns_from_dtim = करो_भाग(tsf, dtim_period);
	/* just had a DTIM */
	अगर (!bcns_from_dtim)
		dtim_count = 0;
	अन्यथा
		dtim_count = dtim_period - bcns_from_dtim;

	ps->dtim_count = dtim_count;
पूर्ण

अटल u8 ieee80211_chanctx_radar_detect(काष्ठा ieee80211_local *local,
					 काष्ठा ieee80211_chanctx *ctx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	u8 radar_detect = 0;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	अगर (WARN_ON(ctx->replace_state == IEEE80211_CHANCTX_WILL_BE_REPLACED))
		वापस 0;

	list_क्रम_each_entry(sdata, &ctx->reserved_vअगरs, reserved_chanctx_list)
		अगर (sdata->reserved_radar_required)
			radar_detect |= BIT(sdata->reserved_chandef.width);

	/*
	 * An in-place reservation context should not have any asचिन्हित vअगरs
	 * until it replaces the other context.
	 */
	WARN_ON(ctx->replace_state == IEEE80211_CHANCTX_REPLACES_OTHER &&
		!list_empty(&ctx->asचिन्हित_vअगरs));

	list_क्रम_each_entry(sdata, &ctx->asचिन्हित_vअगरs, asचिन्हित_chanctx_list)
		अगर (sdata->radar_required)
			radar_detect |= BIT(sdata->vअगर.bss_conf.chandef.width);

	वापस radar_detect;
पूर्ण

पूर्णांक ieee80211_check_combinations(काष्ठा ieee80211_sub_अगर_data *sdata,
				 स्थिर काष्ठा cfg80211_chan_def *chandef,
				 क्रमागत ieee80211_chanctx_mode chanmode,
				 u8 radar_detect)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_sub_अगर_data *sdata_iter;
	क्रमागत nl80211_अगरtype अगरtype = sdata->wdev.अगरtype;
	काष्ठा ieee80211_chanctx *ctx;
	पूर्णांक total = 1;
	काष्ठा अगरace_combination_params params = अणु
		.radar_detect = radar_detect,
	पूर्ण;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	अगर (WARN_ON(hweight32(radar_detect) > 1))
		वापस -EINVAL;

	अगर (WARN_ON(chandef && chanmode == IEEE80211_CHANCTX_SHARED &&
		    !chandef->chan))
		वापस -EINVAL;

	अगर (WARN_ON(अगरtype >= NUM_NL80211_IFTYPES))
		वापस -EINVAL;

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP ||
	    sdata->vअगर.type == NL80211_IFTYPE_MESH_POINT) अणु
		/*
		 * always passing this is harmless, since it'll be the
		 * same value that cfg80211 finds अगर it finds the same
		 * पूर्णांकerface ... and that's always allowed
		 */
		params.new_beacon_पूर्णांक = sdata->vअगर.bss_conf.beacon_पूर्णांक;
	पूर्ण

	/* Always allow software अगरtypes */
	अगर (cfg80211_अगरtype_allowed(local->hw.wiphy, अगरtype, 0, 1)) अणु
		अगर (radar_detect)
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	अगर (chandef)
		params.num_dअगरferent_channels = 1;

	अगर (अगरtype != NL80211_IFTYPE_UNSPECIFIED)
		params.अगरtype_num[अगरtype] = 1;

	list_क्रम_each_entry(ctx, &local->chanctx_list, list) अणु
		अगर (ctx->replace_state == IEEE80211_CHANCTX_WILL_BE_REPLACED)
			जारी;
		params.radar_detect |=
			ieee80211_chanctx_radar_detect(local, ctx);
		अगर (ctx->mode == IEEE80211_CHANCTX_EXCLUSIVE) अणु
			params.num_dअगरferent_channels++;
			जारी;
		पूर्ण
		अगर (chandef && chanmode == IEEE80211_CHANCTX_SHARED &&
		    cfg80211_chandef_compatible(chandef,
						&ctx->conf.def))
			जारी;
		params.num_dअगरferent_channels++;
	पूर्ण

	list_क्रम_each_entry_rcu(sdata_iter, &local->पूर्णांकerfaces, list) अणु
		काष्ठा wireless_dev *wdev_iter;

		wdev_iter = &sdata_iter->wdev;

		अगर (sdata_iter == sdata ||
		    !ieee80211_sdata_running(sdata_iter) ||
		    cfg80211_अगरtype_allowed(local->hw.wiphy,
					    wdev_iter->अगरtype, 0, 1))
			जारी;

		params.अगरtype_num[wdev_iter->अगरtype]++;
		total++;
	पूर्ण

	अगर (total == 1 && !params.radar_detect)
		वापस 0;

	वापस cfg80211_check_combinations(local->hw.wiphy, &params);
पूर्ण

अटल व्योम
ieee80211_iter_max_chans(स्थिर काष्ठा ieee80211_अगरace_combination *c,
			 व्योम *data)
अणु
	u32 *max_num_dअगरferent_channels = data;

	*max_num_dअगरferent_channels = max(*max_num_dअगरferent_channels,
					  c->num_dअगरferent_channels);
पूर्ण

पूर्णांक ieee80211_max_num_channels(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_chanctx *ctx;
	u32 max_num_dअगरferent_channels = 1;
	पूर्णांक err;
	काष्ठा अगरace_combination_params params = अणु0पूर्ण;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	list_क्रम_each_entry(ctx, &local->chanctx_list, list) अणु
		अगर (ctx->replace_state == IEEE80211_CHANCTX_WILL_BE_REPLACED)
			जारी;

		params.num_dअगरferent_channels++;

		params.radar_detect |=
			ieee80211_chanctx_radar_detect(local, ctx);
	पूर्ण

	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list)
		params.अगरtype_num[sdata->wdev.अगरtype]++;

	err = cfg80211_iter_combinations(local->hw.wiphy, &params,
					 ieee80211_iter_max_chans,
					 &max_num_dअगरferent_channels);
	अगर (err < 0)
		वापस err;

	वापस max_num_dअगरferent_channels;
पूर्ण

व्योम ieee80211_add_s1g_capab_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
				काष्ठा ieee80211_sta_s1g_cap *caps,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा ieee80211_s1g_cap s1g_capab;
	u8 *pos;
	पूर्णांक i;

	अगर (WARN_ON(sdata->vअगर.type != NL80211_IFTYPE_STATION))
		वापस;

	अगर (!caps->s1g)
		वापस;

	स_नकल(s1g_capab.capab_info, caps->cap, माप(caps->cap));
	स_नकल(s1g_capab.supp_mcs_nss, caps->nss_mcs, माप(caps->nss_mcs));

	/* override the capability info */
	क्रम (i = 0; i < माप(अगरmgd->s1g_capa.capab_info); i++) अणु
		u8 mask = अगरmgd->s1g_capa_mask.capab_info[i];

		s1g_capab.capab_info[i] &= ~mask;
		s1g_capab.capab_info[i] |= अगरmgd->s1g_capa.capab_info[i] & mask;
	पूर्ण

	/* then MCS and NSS set */
	क्रम (i = 0; i < माप(अगरmgd->s1g_capa.supp_mcs_nss); i++) अणु
		u8 mask = अगरmgd->s1g_capa_mask.supp_mcs_nss[i];

		s1g_capab.supp_mcs_nss[i] &= ~mask;
		s1g_capab.supp_mcs_nss[i] |=
			अगरmgd->s1g_capa.supp_mcs_nss[i] & mask;
	पूर्ण

	pos = skb_put(skb, 2 + माप(s1g_capab));
	*pos++ = WLAN_EID_S1G_CAPABILITIES;
	*pos++ = माप(s1g_capab);

	स_नकल(pos, &s1g_capab, माप(s1g_capab));
पूर्ण

व्योम ieee80211_add_aid_request_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा sk_buff *skb)
अणु
	u8 *pos = skb_put(skb, 3);

	*pos++ = WLAN_EID_AID_REQUEST;
	*pos++ = 1;
	*pos++ = 0;
पूर्ण

u8 *ieee80211_add_wmm_info_ie(u8 *buf, u8 qosinfo)
अणु
	*buf++ = WLAN_EID_VENDOR_SPECIFIC;
	*buf++ = 7; /* len */
	*buf++ = 0x00; /* Microsoft OUI 00:50:F2 */
	*buf++ = 0x50;
	*buf++ = 0xf2;
	*buf++ = 2; /* WME */
	*buf++ = 0; /* WME info */
	*buf++ = 1; /* WME ver */
	*buf++ = qosinfo; /* U-APSD no in use */

	वापस buf;
पूर्ण

व्योम ieee80211_txq_get_depth(काष्ठा ieee80211_txq *txq,
			     अचिन्हित दीर्घ *frame_cnt,
			     अचिन्हित दीर्घ *byte_cnt)
अणु
	काष्ठा txq_info *txqi = to_txq_info(txq);
	u32 frag_cnt = 0, frag_bytes = 0;
	काष्ठा sk_buff *skb;

	skb_queue_walk(&txqi->frags, skb) अणु
		frag_cnt++;
		frag_bytes += skb->len;
	पूर्ण

	अगर (frame_cnt)
		*frame_cnt = txqi->tin.backlog_packets + frag_cnt;

	अगर (byte_cnt)
		*byte_cnt = txqi->tin.backlog_bytes + frag_bytes;
पूर्ण
EXPORT_SYMBOL(ieee80211_txq_get_depth);

स्थिर u8 ieee80211_ac_to_qos_mask[IEEE80211_NUM_ACS] = अणु
	IEEE80211_WMM_IE_STA_QOSINFO_AC_VO,
	IEEE80211_WMM_IE_STA_QOSINFO_AC_VI,
	IEEE80211_WMM_IE_STA_QOSINFO_AC_BE,
	IEEE80211_WMM_IE_STA_QOSINFO_AC_BK
पूर्ण;

u16 ieee80211_encode_usf(पूर्णांक listen_पूर्णांकerval)
अणु
	अटल स्थिर पूर्णांक listen_पूर्णांक_usf[] = अणु 1, 10, 1000, 10000 पूर्ण;
	u16 ui, usf = 0;

	/* find greatest USF */
	जबतक (usf < IEEE80211_MAX_USF) अणु
		अगर (listen_पूर्णांकerval % listen_पूर्णांक_usf[usf + 1])
			अवरोध;
		usf += 1;
	पूर्ण
	ui = listen_पूर्णांकerval / listen_पूर्णांक_usf[usf];

	/* error अगर there is a reमुख्यder. Should've been checked by user */
	WARN_ON_ONCE(ui > IEEE80211_MAX_UI);
	listen_पूर्णांकerval = FIELD_PREP(LISTEN_INT_USF, usf) |
			  FIELD_PREP(LISTEN_INT_UI, ui);

	वापस (u16) listen_पूर्णांकerval;
पूर्ण
