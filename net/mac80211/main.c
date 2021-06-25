<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright (C) 2017     Intel Deutschland GmbH
 * Copyright (C) 2018-2021 Intel Corporation
 */

#समावेश <net/mac80211.h>
#समावेश <linux/module.h>
#समावेश <linux/fips.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/inetdevice.h>
#समावेश <net/net_namespace.h>
#समावेश <net/cfg80211.h>
#समावेश <net/addrconf.h>

#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "rate.h"
#समावेश "mesh.h"
#समावेश "wep.h"
#समावेश "led.h"
#समावेश "debugfs.h"

व्योम ieee80211_configure_filter(काष्ठा ieee80211_local *local)
अणु
	u64 mc;
	अचिन्हित पूर्णांक changed_flags;
	अचिन्हित पूर्णांक new_flags = 0;

	अगर (atomic_पढ़ो(&local->अगरf_allmultis))
		new_flags |= FIF_ALLMULTI;

	अगर (local->monitors || test_bit(SCAN_SW_SCANNING, &local->scanning) ||
	    test_bit(SCAN_ONCHANNEL_SCANNING, &local->scanning))
		new_flags |= FIF_BCN_PRBRESP_PROMISC;

	अगर (local->fअगर_probe_req || local->probe_req_reg)
		new_flags |= FIF_PROBE_REQ;

	अगर (local->fअगर_fcsfail)
		new_flags |= FIF_FCSFAIL;

	अगर (local->fअगर_plcpfail)
		new_flags |= FIF_PLCPFAIL;

	अगर (local->fअगर_control)
		new_flags |= FIF_CONTROL;

	अगर (local->fअगर_other_bss)
		new_flags |= FIF_OTHER_BSS;

	अगर (local->fअगर_pspoll)
		new_flags |= FIF_PSPOLL;

	अगर (local->rx_mcast_action_reg)
		new_flags |= FIF_MCAST_ACTION;

	spin_lock_bh(&local->filter_lock);
	changed_flags = local->filter_flags ^ new_flags;

	mc = drv_prepare_multicast(local, &local->mc_list);
	spin_unlock_bh(&local->filter_lock);

	/* be a bit nasty */
	new_flags |= (1<<31);

	drv_configure_filter(local, changed_flags, &new_flags, mc);

	WARN_ON(new_flags & (1<<31));

	local->filter_flags = new_flags & ~(1<<31);
पूर्ण

अटल व्योम ieee80211_reconfig_filter(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_local *local =
		container_of(work, काष्ठा ieee80211_local, reconfig_filter);

	ieee80211_configure_filter(local);
पूर्ण

अटल u32 ieee80211_hw_conf_chan(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा cfg80211_chan_def chandef = अणुपूर्ण;
	u32 changed = 0;
	पूर्णांक घातer;
	u32 offchannel_flag;

	offchannel_flag = local->hw.conf.flags & IEEE80211_CONF_OFFCHANNEL;

	अगर (local->scan_chandef.chan) अणु
		chandef = local->scan_chandef;
	पूर्ण अन्यथा अगर (local->पंचांगp_channel) अणु
		chandef.chan = local->पंचांगp_channel;
		chandef.width = NL80211_CHAN_WIDTH_20_NOHT;
		chandef.center_freq1 = chandef.chan->center_freq;
		chandef.freq1_offset = chandef.chan->freq_offset;
	पूर्ण अन्यथा
		chandef = local->_oper_chandef;

	WARN(!cfg80211_chandef_valid(&chandef),
	     "control:%d.%03d MHz width:%d center: %d.%03d/%d MHz",
	     chandef.chan->center_freq, chandef.chan->freq_offset,
	     chandef.width, chandef.center_freq1, chandef.freq1_offset,
	     chandef.center_freq2);

	अगर (!cfg80211_chandef_identical(&chandef, &local->_oper_chandef))
		local->hw.conf.flags |= IEEE80211_CONF_OFFCHANNEL;
	अन्यथा
		local->hw.conf.flags &= ~IEEE80211_CONF_OFFCHANNEL;

	offchannel_flag ^= local->hw.conf.flags & IEEE80211_CONF_OFFCHANNEL;

	अगर (offchannel_flag ||
	    !cfg80211_chandef_identical(&local->hw.conf.chandef,
					&local->_oper_chandef)) अणु
		local->hw.conf.chandef = chandef;
		changed |= IEEE80211_CONF_CHANGE_CHANNEL;
	पूर्ण

	अगर (!conf_is_ht(&local->hw.conf)) अणु
		/*
		 * mac80211.h करोcuments that this is only valid
		 * when the channel is set to an HT type, and
		 * that otherwise STATIC is used.
		 */
		local->hw.conf.smps_mode = IEEE80211_SMPS_STATIC;
	पूर्ण अन्यथा अगर (local->hw.conf.smps_mode != local->smps_mode) अणु
		local->hw.conf.smps_mode = local->smps_mode;
		changed |= IEEE80211_CONF_CHANGE_SMPS;
	पूर्ण

	घातer = ieee80211_chandef_max_घातer(&chandef);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (!rcu_access_poपूर्णांकer(sdata->vअगर.chanctx_conf))
			जारी;
		अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
			जारी;
		अगर (sdata->vअगर.bss_conf.txघातer == पूर्णांक_न्यून)
			जारी;
		घातer = min(घातer, sdata->vअगर.bss_conf.txघातer);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (local->hw.conf.घातer_level != घातer) अणु
		changed |= IEEE80211_CONF_CHANGE_POWER;
		local->hw.conf.घातer_level = घातer;
	पूर्ण

	वापस changed;
पूर्ण

पूर्णांक ieee80211_hw_config(काष्ठा ieee80211_local *local, u32 changed)
अणु
	पूर्णांक ret = 0;

	might_sleep();

	अगर (!local->use_chanctx)
		changed |= ieee80211_hw_conf_chan(local);
	अन्यथा
		changed &= ~(IEEE80211_CONF_CHANGE_CHANNEL |
			     IEEE80211_CONF_CHANGE_POWER);

	अगर (changed && local->खोलो_count) अणु
		ret = drv_config(local, changed);
		/*
		 * Goal:
		 * HW reconfiguration should never fail, the driver has told
		 * us what it can support so it should live up to that promise.
		 *
		 * Current status:
		 * rfसमाप्त is not पूर्णांकegrated with mac80211 and a
		 * configuration command can thus fail अगर hardware rfसमाप्त
		 * is enabled
		 *
		 * FIXME: पूर्णांकegrate rfसमाप्त with mac80211 and then add this
		 * WARN_ON() back
		 *
		 */
		/* WARN_ON(ret); */
	पूर्ण

	वापस ret;
पूर्ण

व्योम ieee80211_bss_info_change_notअगरy(काष्ठा ieee80211_sub_अगर_data *sdata,
				      u32 changed)
अणु
	काष्ठा ieee80211_local *local = sdata->local;

	अगर (!changed || sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
		वापस;

	drv_bss_info_changed(local, sdata, &sdata->vअगर.bss_conf, changed);
पूर्ण

u32 ieee80211_reset_erp_info(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	sdata->vअगर.bss_conf.use_cts_prot = false;
	sdata->vअगर.bss_conf.use_लघु_preamble = false;
	sdata->vअगर.bss_conf.use_लघु_slot = false;
	वापस BSS_CHANGED_ERP_CTS_PROT |
	       BSS_CHANGED_ERP_PREAMBLE |
	       BSS_CHANGED_ERP_SLOT;
पूर्ण

अटल व्योम ieee80211_tasklet_handler(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ieee80211_local *local = from_tasklet(local, t, tasklet);
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&local->skb_queue)) ||
	       (skb = skb_dequeue(&local->skb_queue_unreliable))) अणु
		चयन (skb->pkt_type) अणु
		हाल IEEE80211_RX_MSG:
			/* Clear skb->pkt_type in order to not confuse kernel
			 * netstack. */
			skb->pkt_type = 0;
			ieee80211_rx(&local->hw, skb);
			अवरोध;
		हाल IEEE80211_TX_STATUS_MSG:
			skb->pkt_type = 0;
			ieee80211_tx_status(&local->hw, skb);
			अवरोध;
		शेष:
			WARN(1, "mac80211: Packet is of unknown type %d\n",
			     skb->pkt_type);
			dev_kमुक्त_skb(skb);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ieee80211_restart_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_local *local =
		container_of(work, काष्ठा ieee80211_local, restart_work);
	काष्ठा ieee80211_sub_अगर_data *sdata;
	पूर्णांक ret;

	/* रुको क्रम scan work complete */
	flush_workqueue(local->workqueue);
	flush_work(&local->sched_scan_stopped_work);

	WARN(test_bit(SCAN_HW_SCANNING, &local->scanning),
	     "%s called with hardware scan in progress\n", __func__);

	flush_work(&local->radar_detected_work);
	/* we might करो पूर्णांकerface manipulations, so need both */
	rtnl_lock();
	wiphy_lock(local->hw.wiphy);
	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		/*
		 * XXX: there may be more work क्रम other vअगर types and even
		 * क्रम station mode: a good thing would be to run most of
		 * the अगरace type's dependent _stop (ieee80211_mg_stop,
		 * ieee80211_ibss_stop) etc...
		 * For now, fix only the specअगरic bug that was seen: race
		 * between csa_connection_drop_work and us.
		 */
		अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION) अणु
			/*
			 * This worker is scheduled from the अगरace worker that
			 * runs on mac80211's workqueue, so we can't be
			 * scheduling this worker after the cancel right here.
			 * The exception is ieee80211_chचयन_करोne.
			 * Then we can have a race...
			 */
			cancel_work_sync(&sdata->u.mgd.csa_connection_drop_work);
			अगर (sdata->vअगर.csa_active) अणु
				sdata_lock(sdata);
				ieee80211_sta_connection_lost(sdata,
							      sdata->u.mgd.associated->bssid,
							      WLAN_REASON_UNSPECIFIED, false);
				sdata_unlock(sdata);
			पूर्ण
		पूर्ण
		flush_delayed_work(&sdata->dec_tailroom_needed_wk);
	पूर्ण
	ieee80211_scan_cancel(local);

	/* make sure any new ROC will consider local->in_reconfig */
	flush_delayed_work(&local->roc_work);
	flush_work(&local->hw_roc_करोne);

	/* रुको क्रम all packet processing to be करोne */
	synchronize_net();

	ret = ieee80211_reconfig(local);
	wiphy_unlock(local->hw.wiphy);

	अगर (ret)
		cfg80211_shutकरोwn_all_पूर्णांकerfaces(local->hw.wiphy);

	rtnl_unlock();
पूर्ण

व्योम ieee80211_restart_hw(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	trace_api_restart_hw(local);

	wiphy_info(hw->wiphy,
		   "Hardware restart was requested\n");

	/* use this reason, ieee80211_reconfig will unblock it */
	ieee80211_stop_queues_by_reason(hw, IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_REASON_SUSPEND,
					false);

	/*
	 * Stop all Rx during the reconfig. We करोn't want state changes
	 * or driver callbacks जबतक this is in progress.
	 */
	local->in_reconfig = true;
	barrier();

	queue_work(प्रणाली_मुक्तzable_wq, &local->restart_work);
पूर्ण
EXPORT_SYMBOL(ieee80211_restart_hw);

#अगर_घोषित CONFIG_INET
अटल पूर्णांक ieee80211_अगरa_changed(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ data, व्योम *arg)
अणु
	काष्ठा in_अगरaddr *अगरa = arg;
	काष्ठा ieee80211_local *local =
		container_of(nb, काष्ठा ieee80211_local,
			     अगरa_notअगरier);
	काष्ठा net_device *ndev = अगरa->अगरa_dev->dev;
	काष्ठा wireless_dev *wdev = ndev->ieee80211_ptr;
	काष्ठा in_device *idev;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_bss_conf *bss_conf;
	काष्ठा ieee80211_अगर_managed *अगरmgd;
	पूर्णांक c = 0;

	/* Make sure it's our पूर्णांकerface that got changed */
	अगर (!wdev)
		वापस NOTIFY_DONE;

	अगर (wdev->wiphy != local->hw.wiphy)
		वापस NOTIFY_DONE;

	sdata = IEEE80211_DEV_TO_SUB_IF(ndev);
	bss_conf = &sdata->vअगर.bss_conf;

	/* ARP filtering is only supported in managed mode */
	अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
		वापस NOTIFY_DONE;

	idev = __in_dev_get_rtnl(sdata->dev);
	अगर (!idev)
		वापस NOTIFY_DONE;

	अगरmgd = &sdata->u.mgd;
	sdata_lock(sdata);

	/* Copy the addresses to the bss_conf list */
	अगरa = rtnl_dereference(idev->अगरa_list);
	जबतक (अगरa) अणु
		अगर (c < IEEE80211_BSS_ARP_ADDR_LIST_LEN)
			bss_conf->arp_addr_list[c] = अगरa->अगरa_address;
		अगरa = rtnl_dereference(अगरa->अगरa_next);
		c++;
	पूर्ण

	bss_conf->arp_addr_cnt = c;

	/* Configure driver only अगर associated (which also implies it is up) */
	अगर (अगरmgd->associated)
		ieee80211_bss_info_change_notअगरy(sdata,
						 BSS_CHANGED_ARP_FILTER);

	sdata_unlock(sdata);

	वापस NOTIFY_OK;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक ieee80211_अगरa6_changed(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ data, व्योम *arg)
अणु
	काष्ठा inet6_अगरaddr *अगरa = (काष्ठा inet6_अगरaddr *)arg;
	काष्ठा inet6_dev *idev = अगरa->idev;
	काष्ठा net_device *ndev = अगरa->idev->dev;
	काष्ठा ieee80211_local *local =
		container_of(nb, काष्ठा ieee80211_local, अगरa6_notअगरier);
	काष्ठा wireless_dev *wdev = ndev->ieee80211_ptr;
	काष्ठा ieee80211_sub_अगर_data *sdata;

	/* Make sure it's our पूर्णांकerface that got changed */
	अगर (!wdev || wdev->wiphy != local->hw.wiphy)
		वापस NOTIFY_DONE;

	sdata = IEEE80211_DEV_TO_SUB_IF(ndev);

	/*
	 * For now only support station mode. This is mostly because
	 * करोing AP would have to handle AP_VLAN in some way ...
	 */
	अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
		वापस NOTIFY_DONE;

	drv_ipv6_addr_change(local, sdata, idev);

	वापस NOTIFY_OK;
पूर्ण
#पूर्ण_अगर

/* There isn't a lot of sense in it, but you can transmit anything you like */
अटल स्थिर काष्ठा ieee80211_txrx_stypes
ieee80211_शेष_mgmt_stypes[NUM_NL80211_IFTYPES] = अणु
	[NL80211_IFTYPE_ADHOC] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4),
	पूर्ण,
	[NL80211_IFTYPE_STATION] = अणु
		.tx = 0xffff,
		/*
		 * To support Pre Association Security Negotiation (PASN) जबतक
		 * alपढ़ोy associated to one AP, allow user space to रेजिस्टर to
		 * Rx authentication frames, so that the user space logic would
		 * be able to receive/handle authentication frames from a
		 * dअगरferent AP as part of PASN.
		 * It is expected that user space would पूर्णांकelligently रेजिस्टर
		 * क्रम Rx authentication frames, i.e., only when PASN is used
		 * and configure a match filter only क्रम PASN authentication
		 * algorithm, as otherwise the MLME functionality of mac80211
		 * would be broken.
		 */
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4),
	पूर्ण,
	[NL80211_IFTYPE_AP] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_REASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
			BIT(IEEE80211_STYPE_DISASSOC >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4) |
			BIT(IEEE80211_STYPE_ACTION >> 4),
	पूर्ण,
	[NL80211_IFTYPE_AP_VLAN] = अणु
		/* copy AP */
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_REASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
			BIT(IEEE80211_STYPE_DISASSOC >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4) |
			BIT(IEEE80211_STYPE_ACTION >> 4),
	पूर्ण,
	[NL80211_IFTYPE_P2P_CLIENT] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4),
	पूर्ण,
	[NL80211_IFTYPE_P2P_GO] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_REASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
			BIT(IEEE80211_STYPE_DISASSOC >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4) |
			BIT(IEEE80211_STYPE_ACTION >> 4),
	पूर्ण,
	[NL80211_IFTYPE_MESH_POINT] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4),
	पूर्ण,
	[NL80211_IFTYPE_P2P_DEVICE] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_ht_cap mac80211_ht_capa_mod_mask = अणु
	.ampdu_params_info = IEEE80211_HT_AMPDU_PARM_FACTOR |
			     IEEE80211_HT_AMPDU_PARM_DENSITY,

	.cap_info = cpu_to_le16(IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
				IEEE80211_HT_CAP_MAX_AMSDU |
				IEEE80211_HT_CAP_SGI_20 |
				IEEE80211_HT_CAP_SGI_40 |
				IEEE80211_HT_CAP_TX_STBC |
				IEEE80211_HT_CAP_RX_STBC |
				IEEE80211_HT_CAP_LDPC_CODING |
				IEEE80211_HT_CAP_40MHZ_INTOLERANT),
	.mcs = अणु
		.rx_mask = अणु 0xff, 0xff, 0xff, 0xff, 0xff,
			     0xff, 0xff, 0xff, 0xff, 0xff, पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_vht_cap mac80211_vht_capa_mod_mask = अणु
	.vht_cap_info =
		cpu_to_le32(IEEE80211_VHT_CAP_RXLDPC |
			    IEEE80211_VHT_CAP_SHORT_GI_80 |
			    IEEE80211_VHT_CAP_SHORT_GI_160 |
			    IEEE80211_VHT_CAP_RXSTBC_MASK |
			    IEEE80211_VHT_CAP_TXSTBC |
			    IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE |
			    IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
			    IEEE80211_VHT_CAP_TX_ANTENNA_PATTERN |
			    IEEE80211_VHT_CAP_RX_ANTENNA_PATTERN |
			    IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK),
	.supp_mcs = अणु
		.rx_mcs_map = cpu_to_le16(~0),
		.tx_mcs_map = cpu_to_le16(~0),
	पूर्ण,
पूर्ण;

काष्ठा ieee80211_hw *ieee80211_alloc_hw_nm(माप_प्रकार priv_data_len,
					   स्थिर काष्ठा ieee80211_ops *ops,
					   स्थिर अक्षर *requested_name)
अणु
	काष्ठा ieee80211_local *local;
	पूर्णांक priv_size, i;
	काष्ठा wiphy *wiphy;
	bool use_chanctx;

	अगर (WARN_ON(!ops->tx || !ops->start || !ops->stop || !ops->config ||
		    !ops->add_पूर्णांकerface || !ops->हटाओ_पूर्णांकerface ||
		    !ops->configure_filter))
		वापस शून्य;

	अगर (WARN_ON(ops->sta_state && (ops->sta_add || ops->sta_हटाओ)))
		वापस शून्य;

	/* check all or no channel context operations exist */
	i = !!ops->add_chanctx + !!ops->हटाओ_chanctx +
	    !!ops->change_chanctx + !!ops->assign_vअगर_chanctx +
	    !!ops->unassign_vअगर_chanctx;
	अगर (WARN_ON(i != 0 && i != 5))
		वापस शून्य;
	use_chanctx = i == 5;

	/* Ensure 32-byte alignment of our निजी data and hw निजी data.
	 * We use the wiphy priv data क्रम both our ieee80211_local and क्रम
	 * the driver's निजी data
	 *
	 * In memory it'll be like this:
	 *
	 * +-------------------------+
	 * | काष्ठा wiphy	    |
	 * +-------------------------+
	 * | काष्ठा ieee80211_local  |
	 * +-------------------------+
	 * | driver's निजी data   |
	 * +-------------------------+
	 *
	 */
	priv_size = ALIGN(माप(*local), NETDEV_ALIGN) + priv_data_len;

	wiphy = wiphy_new_nm(&mac80211_config_ops, priv_size, requested_name);

	अगर (!wiphy)
		वापस शून्य;

	wiphy->mgmt_stypes = ieee80211_शेष_mgmt_stypes;

	wiphy->privid = mac80211_wiphy_privid;

	wiphy->flags |= WIPHY_FLAG_NETNS_OK |
			WIPHY_FLAG_4ADDR_AP |
			WIPHY_FLAG_4ADDR_STATION |
			WIPHY_FLAG_REPORTS_OBSS |
			WIPHY_FLAG_OFFCHAN_TX;

	अगर (!use_chanctx || ops->reमुख्य_on_channel)
		wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;

	wiphy->features |= NL80211_FEATURE_SK_TX_STATUS |
			   NL80211_FEATURE_SAE |
			   NL80211_FEATURE_HT_IBSS |
			   NL80211_FEATURE_VIF_TXPOWER |
			   NL80211_FEATURE_MAC_ON_CREATE |
			   NL80211_FEATURE_USERSPACE_MPM |
			   NL80211_FEATURE_FULL_AP_CLIENT_STATE;
	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_FILS_STA);
	wiphy_ext_feature_set(wiphy,
			      NL80211_EXT_FEATURE_CONTROL_PORT_OVER_NL80211);
	wiphy_ext_feature_set(wiphy,
			      NL80211_EXT_FEATURE_CONTROL_PORT_NO_PREAUTH);
	wiphy_ext_feature_set(wiphy,
			      NL80211_EXT_FEATURE_CONTROL_PORT_OVER_NL80211_TX_STATUS);
	wiphy_ext_feature_set(wiphy,
			      NL80211_EXT_FEATURE_SCAN_FREQ_KHZ);

	अगर (!ops->hw_scan) अणु
		wiphy->features |= NL80211_FEATURE_LOW_PRIORITY_SCAN |
				   NL80211_FEATURE_AP_SCAN;
		/*
		 * अगर the driver behaves correctly using the probe request
		 * (ढाँचा) from mac80211, then both of these should be
		 * supported even with hw scan - but let drivers opt in.
		 */
		wiphy_ext_feature_set(wiphy,
				      NL80211_EXT_FEATURE_SCAN_RANDOM_SN);
		wiphy_ext_feature_set(wiphy,
				      NL80211_EXT_FEATURE_SCAN_MIN_PREQ_CONTENT);
	पूर्ण

	अगर (!ops->set_key)
		wiphy->flags |= WIPHY_FLAG_IBSS_RSN;

	अगर (ops->wake_tx_queue)
		wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_TXQS);

	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_RRM);

	wiphy->bss_priv_size = माप(काष्ठा ieee80211_bss);

	local = wiphy_priv(wiphy);

	अगर (sta_info_init(local))
		जाओ err_मुक्त;

	local->hw.wiphy = wiphy;

	local->hw.priv = (अक्षर *)local + ALIGN(माप(*local), NETDEV_ALIGN);

	local->ops = ops;
	local->use_chanctx = use_chanctx;

	/*
	 * We need a bit of data queued to build aggregates properly, so
	 * inकाष्ठा the TCP stack to allow more than a single ms of data
	 * to be queued in the stack. The value is a bit-shअगरt of 1
	 * second, so 7 is ~8ms of queued data. Only affects local TCP
	 * sockets.
	 * This is the शेष, anyhow - drivers may need to override it
	 * क्रम local reasons (दीर्घer buffers, दीर्घer completion समय, or
	 * similar).
	 */
	local->hw.tx_sk_pacing_shअगरt = 7;

	/* set up some शेषs */
	local->hw.queues = 1;
	local->hw.max_rates = 1;
	local->hw.max_report_rates = 0;
	local->hw.max_rx_aggregation_subframes = IEEE80211_MAX_AMPDU_BUF_HT;
	local->hw.max_tx_aggregation_subframes = IEEE80211_MAX_AMPDU_BUF_HT;
	local->hw.offchannel_tx_hw_queue = IEEE80211_INVAL_HW_QUEUE;
	local->hw.conf.दीर्घ_frame_max_tx_count = wiphy->retry_दीर्घ;
	local->hw.conf.लघु_frame_max_tx_count = wiphy->retry_लघु;
	local->hw.radiotap_mcs_details = IEEE80211_RADIOTAP_MCS_HAVE_MCS |
					 IEEE80211_RADIOTAP_MCS_HAVE_GI |
					 IEEE80211_RADIOTAP_MCS_HAVE_BW;
	local->hw.radiotap_vht_details = IEEE80211_RADIOTAP_VHT_KNOWN_GI |
					 IEEE80211_RADIOTAP_VHT_KNOWN_BANDWIDTH;
	local->hw.uapsd_queues = IEEE80211_DEFAULT_UAPSD_QUEUES;
	local->hw.uapsd_max_sp_len = IEEE80211_DEFAULT_MAX_SP_LEN;
	local->hw.max_mtu = IEEE80211_MAX_DATA_LEN;
	local->user_घातer_level = IEEE80211_UNSET_POWER_LEVEL;
	wiphy->ht_capa_mod_mask = &mac80211_ht_capa_mod_mask;
	wiphy->vht_capa_mod_mask = &mac80211_vht_capa_mod_mask;

	local->ext_capa[7] = WLAN_EXT_CAPA8_OPMODE_NOTIF;

	wiphy->extended_capabilities = local->ext_capa;
	wiphy->extended_capabilities_mask = local->ext_capa;
	wiphy->extended_capabilities_len =
		ARRAY_SIZE(local->ext_capa);

	INIT_LIST_HEAD(&local->पूर्णांकerfaces);
	INIT_LIST_HEAD(&local->mon_list);

	__hw_addr_init(&local->mc_list);

	mutex_init(&local->अगरlist_mtx);
	mutex_init(&local->mtx);

	mutex_init(&local->key_mtx);
	spin_lock_init(&local->filter_lock);
	spin_lock_init(&local->rx_path_lock);
	spin_lock_init(&local->queue_stop_reason_lock);

	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		INIT_LIST_HEAD(&local->active_txqs[i]);
		spin_lock_init(&local->active_txq_lock[i]);
		local->aql_txq_limit_low[i] = IEEE80211_DEFAULT_AQL_TXQ_LIMIT_L;
		local->aql_txq_limit_high[i] =
			IEEE80211_DEFAULT_AQL_TXQ_LIMIT_H;
	पूर्ण

	local->airसमय_flags = AIRTIME_USE_TX | AIRTIME_USE_RX;
	local->aql_threshold = IEEE80211_AQL_THRESHOLD;
	atomic_set(&local->aql_total_pending_airसमय, 0);

	INIT_LIST_HEAD(&local->chanctx_list);
	mutex_init(&local->chanctx_mtx);

	INIT_DELAYED_WORK(&local->scan_work, ieee80211_scan_work);

	INIT_WORK(&local->restart_work, ieee80211_restart_work);

	INIT_WORK(&local->radar_detected_work,
		  ieee80211_dfs_radar_detected_work);

	INIT_WORK(&local->reconfig_filter, ieee80211_reconfig_filter);
	local->smps_mode = IEEE80211_SMPS_OFF;

	INIT_WORK(&local->dynamic_ps_enable_work,
		  ieee80211_dynamic_ps_enable_work);
	INIT_WORK(&local->dynamic_ps_disable_work,
		  ieee80211_dynamic_ps_disable_work);
	समयr_setup(&local->dynamic_ps_समयr, ieee80211_dynamic_ps_समयr, 0);

	INIT_WORK(&local->sched_scan_stopped_work,
		  ieee80211_sched_scan_stopped_work);

	INIT_WORK(&local->tdls_chsw_work, ieee80211_tdls_chsw_work);

	spin_lock_init(&local->ack_status_lock);
	idr_init(&local->ack_status_frames);

	क्रम (i = 0; i < IEEE80211_MAX_QUEUES; i++) अणु
		skb_queue_head_init(&local->pending[i]);
		atomic_set(&local->agg_queue_stop[i], 0);
	पूर्ण
	tasklet_setup(&local->tx_pending_tasklet, ieee80211_tx_pending);

	अगर (ops->wake_tx_queue)
		tasklet_setup(&local->wake_txqs_tasklet, ieee80211_wake_txqs);

	tasklet_setup(&local->tasklet, ieee80211_tasklet_handler);

	skb_queue_head_init(&local->skb_queue);
	skb_queue_head_init(&local->skb_queue_unreliable);
	skb_queue_head_init(&local->skb_queue_tdls_chsw);

	ieee80211_alloc_led_names(local);

	ieee80211_roc_setup(local);

	local->hw.radiotap_बारtamp.units_pos = -1;
	local->hw.radiotap_बारtamp.accuracy = -1;

	वापस &local->hw;
 err_मुक्त:
	wiphy_मुक्त(wiphy);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(ieee80211_alloc_hw_nm);

अटल पूर्णांक ieee80211_init_cipher_suites(काष्ठा ieee80211_local *local)
अणु
	bool have_wep = !fips_enabled; /* FIPS करोes not permit the use of RC4 */
	bool have_mfp = ieee80211_hw_check(&local->hw, MFP_CAPABLE);
	पूर्णांक n_suites = 0, r = 0, w = 0;
	u32 *suites;
	अटल स्थिर u32 cipher_suites[] = अणु
		/* keep WEP first, it may be हटाओd below */
		WLAN_CIPHER_SUITE_WEP40,
		WLAN_CIPHER_SUITE_WEP104,
		WLAN_CIPHER_SUITE_TKIP,
		WLAN_CIPHER_SUITE_CCMP,
		WLAN_CIPHER_SUITE_CCMP_256,
		WLAN_CIPHER_SUITE_GCMP,
		WLAN_CIPHER_SUITE_GCMP_256,

		/* keep last -- depends on hw flags! */
		WLAN_CIPHER_SUITE_AES_CMAC,
		WLAN_CIPHER_SUITE_BIP_CMAC_256,
		WLAN_CIPHER_SUITE_BIP_GMAC_128,
		WLAN_CIPHER_SUITE_BIP_GMAC_256,
	पूर्ण;

	अगर (ieee80211_hw_check(&local->hw, SW_CRYPTO_CONTROL) ||
	    local->hw.wiphy->cipher_suites) अणु
		/* If the driver advertises, or करोesn't support SW crypto,
		 * we only need to हटाओ WEP अगर necessary.
		 */
		अगर (have_wep)
			वापस 0;

		/* well अगर it has _no_ ciphers ... fine */
		अगर (!local->hw.wiphy->n_cipher_suites)
			वापस 0;

		/* Driver provides cipher suites, but we need to exclude WEP */
		suites = kmemdup(local->hw.wiphy->cipher_suites,
				 माप(u32) * local->hw.wiphy->n_cipher_suites,
				 GFP_KERNEL);
		अगर (!suites)
			वापस -ENOMEM;

		क्रम (r = 0; r < local->hw.wiphy->n_cipher_suites; r++) अणु
			u32 suite = local->hw.wiphy->cipher_suites[r];

			अगर (suite == WLAN_CIPHER_SUITE_WEP40 ||
			    suite == WLAN_CIPHER_SUITE_WEP104)
				जारी;
			suites[w++] = suite;
		पूर्ण
	पूर्ण अन्यथा अगर (!local->hw.cipher_schemes) अणु
		/* If the driver करोesn't have cipher schemes, there's nothing
		 * अन्यथा to करो other than assign the (software supported and
		 * perhaps offloaded) cipher suites.
		 */
		local->hw.wiphy->cipher_suites = cipher_suites;
		local->hw.wiphy->n_cipher_suites = ARRAY_SIZE(cipher_suites);

		अगर (!have_mfp)
			local->hw.wiphy->n_cipher_suites -= 4;

		अगर (!have_wep) अणु
			local->hw.wiphy->cipher_suites += 2;
			local->hw.wiphy->n_cipher_suites -= 2;
		पूर्ण

		/* not dynamically allocated, so just वापस */
		वापस 0;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा ieee80211_cipher_scheme *cs;

		cs = local->hw.cipher_schemes;

		/* Driver specअगरies cipher schemes only (but not cipher suites
		 * including the schemes)
		 *
		 * We start counting ciphers defined by schemes, TKIP, CCMP,
		 * CCMP-256, GCMP, and GCMP-256
		 */
		n_suites = local->hw.n_cipher_schemes + 5;

		/* check अगर we have WEP40 and WEP104 */
		अगर (have_wep)
			n_suites += 2;

		/* check अगर we have AES_CMAC, BIP-CMAC-256, BIP-GMAC-128,
		 * BIP-GMAC-256
		 */
		अगर (have_mfp)
			n_suites += 4;

		suites = kदो_स्मृति_array(n_suites, माप(u32), GFP_KERNEL);
		अगर (!suites)
			वापस -ENOMEM;

		suites[w++] = WLAN_CIPHER_SUITE_CCMP;
		suites[w++] = WLAN_CIPHER_SUITE_CCMP_256;
		suites[w++] = WLAN_CIPHER_SUITE_TKIP;
		suites[w++] = WLAN_CIPHER_SUITE_GCMP;
		suites[w++] = WLAN_CIPHER_SUITE_GCMP_256;

		अगर (have_wep) अणु
			suites[w++] = WLAN_CIPHER_SUITE_WEP40;
			suites[w++] = WLAN_CIPHER_SUITE_WEP104;
		पूर्ण

		अगर (have_mfp) अणु
			suites[w++] = WLAN_CIPHER_SUITE_AES_CMAC;
			suites[w++] = WLAN_CIPHER_SUITE_BIP_CMAC_256;
			suites[w++] = WLAN_CIPHER_SUITE_BIP_GMAC_128;
			suites[w++] = WLAN_CIPHER_SUITE_BIP_GMAC_256;
		पूर्ण

		क्रम (r = 0; r < local->hw.n_cipher_schemes; r++) अणु
			suites[w++] = cs[r].cipher;
			अगर (WARN_ON(cs[r].pn_len > IEEE80211_MAX_PN_LEN)) अणु
				kमुक्त(suites);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	local->hw.wiphy->cipher_suites = suites;
	local->hw.wiphy->n_cipher_suites = w;
	local->wiphy_ciphers_allocated = true;

	वापस 0;
पूर्ण

पूर्णांक ieee80211_रेजिस्टर_hw(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	पूर्णांक result, i;
	क्रमागत nl80211_band band;
	पूर्णांक channels, max_bitrates;
	bool supp_ht, supp_vht, supp_he;
	काष्ठा cfg80211_chan_def dflt_chandef = अणुपूर्ण;

	अगर (ieee80211_hw_check(hw, QUEUE_CONTROL) &&
	    (local->hw.offchannel_tx_hw_queue == IEEE80211_INVAL_HW_QUEUE ||
	     local->hw.offchannel_tx_hw_queue >= local->hw.queues))
		वापस -EINVAL;

	अगर ((hw->wiphy->features & NL80211_FEATURE_TDLS_CHANNEL_SWITCH) &&
	    (!local->ops->tdls_channel_चयन ||
	     !local->ops->tdls_cancel_channel_चयन ||
	     !local->ops->tdls_recv_channel_चयन))
		वापस -EOPNOTSUPP;

	अगर (WARN_ON(ieee80211_hw_check(hw, SUPPORTS_TX_FRAG) &&
		    !local->ops->set_frag_threshold))
		वापस -EINVAL;

	अगर (WARN_ON(local->hw.wiphy->पूर्णांकerface_modes &
			BIT(NL80211_IFTYPE_न_अंक) &&
		    (!local->ops->start_nan || !local->ops->stop_nan)))
		वापस -EINVAL;

#अगर_घोषित CONFIG_PM
	अगर (hw->wiphy->wowlan && (!local->ops->suspend || !local->ops->resume))
		वापस -EINVAL;
#पूर्ण_अगर

	अगर (!local->use_chanctx) अणु
		क्रम (i = 0; i < local->hw.wiphy->n_अगरace_combinations; i++) अणु
			स्थिर काष्ठा ieee80211_अगरace_combination *comb;

			comb = &local->hw.wiphy->अगरace_combinations[i];

			अगर (comb->num_dअगरferent_channels > 1)
				वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* DFS is not supported with multi-channel combinations yet */
		क्रम (i = 0; i < local->hw.wiphy->n_अगरace_combinations; i++) अणु
			स्थिर काष्ठा ieee80211_अगरace_combination *comb;

			comb = &local->hw.wiphy->अगरace_combinations[i];

			अगर (comb->radar_detect_widths &&
			    comb->num_dअगरferent_channels > 1)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Only HW csum features are currently compatible with mac80211 */
	अगर (WARN_ON(hw->netdev_features & ~MAC80211_SUPPORTED_FEATURES))
		वापस -EINVAL;

	अगर (hw->max_report_rates == 0)
		hw->max_report_rates = hw->max_rates;

	local->rx_chains = 1;

	/*
	 * generic code guarantees at least one band,
	 * set this very early because much code assumes
	 * that hw.conf.channel is asचिन्हित
	 */
	channels = 0;
	max_bitrates = 0;
	supp_ht = false;
	supp_vht = false;
	supp_he = false;
	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		काष्ठा ieee80211_supported_band *sband;

		sband = local->hw.wiphy->bands[band];
		अगर (!sband)
			जारी;

		अगर (!dflt_chandef.chan) अणु
			/*
			 * Assign the first enabled channel to dflt_chandef
			 * from the list of channels
			 */
			क्रम (i = 0; i < sband->n_channels; i++)
				अगर (!(sband->channels[i].flags &
						IEEE80211_CHAN_DISABLED))
					अवरोध;
			/* अगर none found then use the first anyway */
			अगर (i == sband->n_channels)
				i = 0;
			cfg80211_chandef_create(&dflt_chandef,
						&sband->channels[i],
						NL80211_CHAN_NO_HT);
			/* init channel we're on */
			अगर (!local->use_chanctx && !local->_oper_chandef.chan) अणु
				local->hw.conf.chandef = dflt_chandef;
				local->_oper_chandef = dflt_chandef;
			पूर्ण
			local->monitor_chandef = dflt_chandef;
		पूर्ण

		channels += sband->n_channels;

		अगर (max_bitrates < sband->n_bitrates)
			max_bitrates = sband->n_bitrates;
		supp_ht = supp_ht || sband->ht_cap.ht_supported;
		supp_vht = supp_vht || sband->vht_cap.vht_supported;

		अगर (!supp_he)
			supp_he = !!ieee80211_get_he_sta_cap(sband);

		/* HT, VHT, HE require QoS, thus >= 4 queues */
		अगर (WARN_ON(local->hw.queues < IEEE80211_NUM_ACS &&
			    (supp_ht || supp_vht || supp_he)))
			वापस -EINVAL;

		अगर (!sband->ht_cap.ht_supported)
			जारी;

		/* TODO: consider VHT क्रम RX chains, hopefully it's the same */
		local->rx_chains =
			max(ieee80211_mcs_to_chains(&sband->ht_cap.mcs),
			    local->rx_chains);

		/* no need to mask, SM_PS_DISABLED has all bits set */
		sband->ht_cap.cap |= WLAN_HT_CAP_SM_PS_DISABLED <<
			             IEEE80211_HT_CAP_SM_PS_SHIFT;
	पूर्ण

	/* अगर low-level driver supports AP, we also support VLAN.
	 * drivers advertising SW_CRYPTO_CONTROL should enable AP_VLAN
	 * based on their support to transmit SW encrypted packets.
	 */
	अगर (local->hw.wiphy->पूर्णांकerface_modes & BIT(NL80211_IFTYPE_AP) &&
	    !ieee80211_hw_check(&local->hw, SW_CRYPTO_CONTROL)) अणु
		hw->wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_AP_VLAN);
		hw->wiphy->software_अगरtypes |= BIT(NL80211_IFTYPE_AP_VLAN);
	पूर्ण

	/* mac80211 always supports monitor */
	hw->wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_MONITOR);
	hw->wiphy->software_अगरtypes |= BIT(NL80211_IFTYPE_MONITOR);

	/* mac80211 करोesn't support more than one IBSS पूर्णांकerface right now */
	क्रम (i = 0; i < hw->wiphy->n_अगरace_combinations; i++) अणु
		स्थिर काष्ठा ieee80211_अगरace_combination *c;
		पूर्णांक j;

		c = &hw->wiphy->अगरace_combinations[i];

		क्रम (j = 0; j < c->n_limits; j++)
			अगर ((c->limits[j].types & BIT(NL80211_IFTYPE_ADHOC)) &&
			    c->limits[j].max > 1)
				वापस -EINVAL;
	पूर्ण

	local->पूर्णांक_scan_req = kzalloc(माप(*local->पूर्णांक_scan_req) +
				      माप(व्योम *) * channels, GFP_KERNEL);
	अगर (!local->पूर्णांक_scan_req)
		वापस -ENOMEM;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		अगर (!local->hw.wiphy->bands[band])
			जारी;
		local->पूर्णांक_scan_req->rates[band] = (u32) -1;
	पूर्ण

#अगर_अघोषित CONFIG_MAC80211_MESH
	/* mesh depends on Kconfig, but drivers should set it अगर they want */
	local->hw.wiphy->पूर्णांकerface_modes &= ~BIT(NL80211_IFTYPE_MESH_POINT);
#पूर्ण_अगर

	/* अगर the underlying driver supports mesh, mac80211 will (at least)
	 * provide routing of mesh authentication frames to userspace */
	अगर (local->hw.wiphy->पूर्णांकerface_modes & BIT(NL80211_IFTYPE_MESH_POINT))
		local->hw.wiphy->flags |= WIPHY_FLAG_MESH_AUTH;

	/* mac80211 supports control port protocol changing */
	local->hw.wiphy->flags |= WIPHY_FLAG_CONTROL_PORT_PROTOCOL;

	अगर (ieee80211_hw_check(&local->hw, SIGNAL_DBM)) अणु
		local->hw.wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_MBM;
	पूर्ण अन्यथा अगर (ieee80211_hw_check(&local->hw, SIGNAL_UNSPEC)) अणु
		local->hw.wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_UNSPEC;
		अगर (hw->max_संकेत <= 0) अणु
			result = -EINVAL;
			जाओ fail_workqueue;
		पूर्ण
	पूर्ण

	/* Mac80211 and thereक्रमe all drivers using SW crypto only
	 * are able to handle PTK rekeys and Extended Key ID.
	 */
	अगर (!local->ops->set_key) अणु
		wiphy_ext_feature_set(local->hw.wiphy,
				      NL80211_EXT_FEATURE_CAN_REPLACE_PTK0);
		wiphy_ext_feature_set(local->hw.wiphy,
				      NL80211_EXT_FEATURE_EXT_KEY_ID);
	पूर्ण

	अगर (local->hw.wiphy->पूर्णांकerface_modes & BIT(NL80211_IFTYPE_ADHOC))
		wiphy_ext_feature_set(local->hw.wiphy,
				      NL80211_EXT_FEATURE_DEL_IBSS_STA);

	/*
	 * Calculate scan IE length -- we need this to alloc
	 * memory and to subtract from the driver limit. It
	 * includes the DS Params, (extended) supported rates, and HT
	 * inक्रमmation -- SSID is the driver's responsibility.
	 */
	local->scan_ies_len = 4 + max_bitrates /* (ext) supp rates */ +
		3 /* DS Params */;
	अगर (supp_ht)
		local->scan_ies_len += 2 + माप(काष्ठा ieee80211_ht_cap);

	अगर (supp_vht)
		local->scan_ies_len +=
			2 + माप(काष्ठा ieee80211_vht_cap);

	/* HE cap element is variable in size - set len to allow max size */
	/*
	 * TODO: 1 is added at the end of the calculation to accommodate क्रम
	 *	the temporary placing of the HE capabilities IE under EXT.
	 *	Remove it once it is placed in the final place.
	 */
	अगर (supp_he)
		local->scan_ies_len +=
			2 + माप(काष्ठा ieee80211_he_cap_elem) +
			माप(काष्ठा ieee80211_he_mcs_nss_supp) +
			IEEE80211_HE_PPE_THRES_MAX_LEN + 1;

	अगर (!local->ops->hw_scan) अणु
		/* For hw_scan, driver needs to set these up. */
		local->hw.wiphy->max_scan_ssids = 4;
		local->hw.wiphy->max_scan_ie_len = IEEE80211_MAX_DATA_LEN;
	पूर्ण

	/*
	 * If the driver supports any scan IEs, then assume the
	 * limit includes the IEs mac80211 will add, otherwise
	 * leave it at zero and let the driver sort it out; we
	 * still pass our IEs to the driver but userspace will
	 * not be allowed to in that हाल.
	 */
	अगर (local->hw.wiphy->max_scan_ie_len)
		local->hw.wiphy->max_scan_ie_len -= local->scan_ies_len;

	अगर (WARN_ON(!ieee80211_cs_list_valid(local->hw.cipher_schemes,
					     local->hw.n_cipher_schemes))) अणु
		result = -EINVAL;
		जाओ fail_workqueue;
	पूर्ण

	result = ieee80211_init_cipher_suites(local);
	अगर (result < 0)
		जाओ fail_workqueue;

	अगर (!local->ops->reमुख्य_on_channel)
		local->hw.wiphy->max_reमुख्य_on_channel_duration = 5000;

	/* mac80211 based drivers करोn't support पूर्णांकernal TDLS setup */
	अगर (local->hw.wiphy->flags & WIPHY_FLAG_SUPPORTS_TDLS)
		local->hw.wiphy->flags |= WIPHY_FLAG_TDLS_EXTERNAL_SETUP;

	/* mac80211 supports eCSA, अगर the driver supports STA CSA at all */
	अगर (ieee80211_hw_check(&local->hw, CHANCTX_STA_CSA))
		local->ext_capa[0] |= WLAN_EXT_CAPA1_EXT_CHANNEL_SWITCHING;

	/* mac80211 supports multi BSSID, अगर the driver supports it */
	अगर (ieee80211_hw_check(&local->hw, SUPPORTS_MULTI_BSSID)) अणु
		local->hw.wiphy->support_mbssid = true;
		अगर (ieee80211_hw_check(&local->hw,
				       SUPPORTS_ONLY_HE_MULTI_BSSID))
			local->hw.wiphy->support_only_he_mbssid = true;
		अन्यथा
			local->ext_capa[2] |=
				WLAN_EXT_CAPA3_MULTI_BSSID_SUPPORT;
	पूर्ण

	local->hw.wiphy->max_num_csa_counters = IEEE80211_MAX_CNTDWN_COUNTERS_NUM;

	/*
	 * We use the number of queues क्रम feature tests (QoS, HT) पूर्णांकernally
	 * so restrict them appropriately.
	 */
	अगर (hw->queues > IEEE80211_MAX_QUEUES)
		hw->queues = IEEE80211_MAX_QUEUES;

	local->workqueue =
		alloc_ordered_workqueue("%s", 0, wiphy_name(local->hw.wiphy));
	अगर (!local->workqueue) अणु
		result = -ENOMEM;
		जाओ fail_workqueue;
	पूर्ण

	/*
	 * The hardware needs headroom क्रम sending the frame,
	 * and we need some headroom क्रम passing the frame to monitor
	 * पूर्णांकerfaces, but never both at the same समय.
	 */
	local->tx_headroom = max_t(अचिन्हित पूर्णांक , local->hw.extra_tx_headroom,
				   IEEE80211_TX_STATUS_HEADROOM);

	/*
	 * अगर the driver करोesn't specअगरy a max listen पूर्णांकerval we
	 * use 5 which should be a safe शेष
	 */
	अगर (local->hw.max_listen_पूर्णांकerval == 0)
		local->hw.max_listen_पूर्णांकerval = 5;

	local->hw.conf.listen_पूर्णांकerval = local->hw.max_listen_पूर्णांकerval;

	local->dynamic_ps_क्रमced_समयout = -1;

	अगर (!local->hw.max_nan_de_entries)
		local->hw.max_nan_de_entries = IEEE80211_MAX_न_अंक_INSTANCE_ID;

	अगर (!local->hw.weight_multiplier)
		local->hw.weight_multiplier = 1;

	ieee80211_wep_init(local);

	local->hw.conf.flags = IEEE80211_CONF_IDLE;

	ieee80211_led_init(local);

	result = ieee80211_txq_setup_flows(local);
	अगर (result)
		जाओ fail_flows;

	rtnl_lock();
	result = ieee80211_init_rate_ctrl_alg(local,
					      hw->rate_control_algorithm);
	rtnl_unlock();
	अगर (result < 0) अणु
		wiphy_debug(local->hw.wiphy,
			    "Failed to initialize rate control algorithm\n");
		जाओ fail_rate;
	पूर्ण

	अगर (local->rate_ctrl) अणु
		clear_bit(IEEE80211_HW_SUPPORTS_VHT_EXT_NSS_BW, hw->flags);
		अगर (local->rate_ctrl->ops->capa & RATE_CTRL_CAPA_VHT_EXT_NSS_BW)
			ieee80211_hw_set(hw, SUPPORTS_VHT_EXT_NSS_BW);
	पूर्ण

	/*
	 * If the VHT capabilities करोn't have IEEE80211_VHT_EXT_NSS_BW_CAPABLE,
	 * or have it when we करोn't, copy the sband काष्ठाure and set/clear it.
	 * This is necessary because rate scaling algorithms could be चयनed
	 * and have dअगरferent support values.
	 * Prपूर्णांक a message so that in the common हाल the पुनः_स्मृतिation can be
	 * aव्योमed.
	 */
	BUILD_BUG_ON(NUM_NL80211_BANDS > 8 * माप(local->sband_allocated));
	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		काष्ठा ieee80211_supported_band *sband;
		bool local_cap, ie_cap;

		local_cap = ieee80211_hw_check(hw, SUPPORTS_VHT_EXT_NSS_BW);

		sband = local->hw.wiphy->bands[band];
		अगर (!sband || !sband->vht_cap.vht_supported)
			जारी;

		ie_cap = !!(sband->vht_cap.vht_mcs.tx_highest &
			    cpu_to_le16(IEEE80211_VHT_EXT_NSS_BW_CAPABLE));

		अगर (local_cap == ie_cap)
			जारी;

		sband = kmemdup(sband, माप(*sband), GFP_KERNEL);
		अगर (!sband) अणु
			result = -ENOMEM;
			जाओ fail_rate;
		पूर्ण

		wiphy_dbg(hw->wiphy, "copying sband (band %d) due to VHT EXT NSS BW flag\n",
			  band);

		sband->vht_cap.vht_mcs.tx_highest ^=
			cpu_to_le16(IEEE80211_VHT_EXT_NSS_BW_CAPABLE);

		local->hw.wiphy->bands[band] = sband;
		local->sband_allocated |= BIT(band);
	पूर्ण

	result = wiphy_रेजिस्टर(local->hw.wiphy);
	अगर (result < 0)
		जाओ fail_wiphy_रेजिस्टर;

	debugfs_hw_add(local);
	rate_control_add_debugfs(local);

	rtnl_lock();
	wiphy_lock(hw->wiphy);

	/* add one शेष STA पूर्णांकerface अगर supported */
	अगर (local->hw.wiphy->पूर्णांकerface_modes & BIT(NL80211_IFTYPE_STATION) &&
	    !ieee80211_hw_check(hw, NO_AUTO_VIF)) अणु
		काष्ठा vअगर_params params = अणु0पूर्ण;

		result = ieee80211_अगर_add(local, "wlan%d", NET_NAME_ENUM, शून्य,
					  NL80211_IFTYPE_STATION, &params);
		अगर (result)
			wiphy_warn(local->hw.wiphy,
				   "Failed to add default virtual iface\n");
	पूर्ण

	wiphy_unlock(hw->wiphy);
	rtnl_unlock();

#अगर_घोषित CONFIG_INET
	local->अगरa_notअगरier.notअगरier_call = ieee80211_अगरa_changed;
	result = रेजिस्टर_inetaddr_notअगरier(&local->अगरa_notअगरier);
	अगर (result)
		जाओ fail_अगरa;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
	local->अगरa6_notअगरier.notअगरier_call = ieee80211_अगरa6_changed;
	result = रेजिस्टर_inet6addr_notअगरier(&local->अगरa6_notअगरier);
	अगर (result)
		जाओ fail_अगरa6;
#पूर्ण_अगर

	वापस 0;

#अगर IS_ENABLED(CONFIG_IPV6)
 fail_अगरa6:
#अगर_घोषित CONFIG_INET
	unरेजिस्टर_inetaddr_notअगरier(&local->अगरa_notअगरier);
#पूर्ण_अगर
#पूर्ण_अगर
#अगर defined(CONFIG_INET) || defined(CONFIG_IPV6)
 fail_अगरa:
#पूर्ण_अगर
	wiphy_unरेजिस्टर(local->hw.wiphy);
 fail_wiphy_रेजिस्टर:
	rtnl_lock();
	rate_control_deinitialize(local);
	ieee80211_हटाओ_पूर्णांकerfaces(local);
	rtnl_unlock();
 fail_rate:
 fail_flows:
	ieee80211_led_निकास(local);
	destroy_workqueue(local->workqueue);
 fail_workqueue:
	अगर (local->wiphy_ciphers_allocated)
		kमुक्त(local->hw.wiphy->cipher_suites);
	kमुक्त(local->पूर्णांक_scan_req);
	वापस result;
पूर्ण
EXPORT_SYMBOL(ieee80211_रेजिस्टर_hw);

व्योम ieee80211_unरेजिस्टर_hw(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	tasklet_समाप्त(&local->tx_pending_tasklet);
	tasklet_समाप्त(&local->tasklet);

#अगर_घोषित CONFIG_INET
	unरेजिस्टर_inetaddr_notअगरier(&local->अगरa_notअगरier);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IPV6)
	unरेजिस्टर_inet6addr_notअगरier(&local->अगरa6_notअगरier);
#पूर्ण_अगर

	rtnl_lock();

	/*
	 * At this poपूर्णांक, पूर्णांकerface list manipulations are fine
	 * because the driver cannot be handing us frames any
	 * more and the tasklet is समाप्तed.
	 */
	ieee80211_हटाओ_पूर्णांकerfaces(local);

	rtnl_unlock();

	cancel_delayed_work_sync(&local->roc_work);
	cancel_work_sync(&local->restart_work);
	cancel_work_sync(&local->reconfig_filter);
	cancel_work_sync(&local->tdls_chsw_work);
	flush_work(&local->sched_scan_stopped_work);
	flush_work(&local->radar_detected_work);

	ieee80211_clear_tx_pending(local);
	rate_control_deinitialize(local);

	अगर (skb_queue_len(&local->skb_queue) ||
	    skb_queue_len(&local->skb_queue_unreliable))
		wiphy_warn(local->hw.wiphy, "skb_queue not empty\n");
	skb_queue_purge(&local->skb_queue);
	skb_queue_purge(&local->skb_queue_unreliable);
	skb_queue_purge(&local->skb_queue_tdls_chsw);

	wiphy_unरेजिस्टर(local->hw.wiphy);
	destroy_workqueue(local->workqueue);
	ieee80211_led_निकास(local);
	kमुक्त(local->पूर्णांक_scan_req);
पूर्ण
EXPORT_SYMBOL(ieee80211_unरेजिस्टर_hw);

अटल पूर्णांक ieee80211_मुक्त_ack_frame(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	WARN_ONCE(1, "Have pending ack frames!\n");
	kमुक्त_skb(p);
	वापस 0;
पूर्ण

व्योम ieee80211_मुक्त_hw(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	क्रमागत nl80211_band band;

	mutex_destroy(&local->अगरlist_mtx);
	mutex_destroy(&local->mtx);

	अगर (local->wiphy_ciphers_allocated)
		kमुक्त(local->hw.wiphy->cipher_suites);

	idr_क्रम_each(&local->ack_status_frames,
		     ieee80211_मुक्त_ack_frame, शून्य);
	idr_destroy(&local->ack_status_frames);

	sta_info_stop(local);

	ieee80211_मुक्त_led_names(local);

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		अगर (!(local->sband_allocated & BIT(band)))
			जारी;
		kमुक्त(local->hw.wiphy->bands[band]);
	पूर्ण

	wiphy_मुक्त(local->hw.wiphy);
पूर्ण
EXPORT_SYMBOL(ieee80211_मुक्त_hw);

अटल पूर्णांक __init ieee80211_init(व्योम)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	BUILD_BUG_ON(माप(काष्ठा ieee80211_tx_info) > माप(skb->cb));
	BUILD_BUG_ON(दुरत्व(काष्ठा ieee80211_tx_info, driver_data) +
		     IEEE80211_TX_INFO_DRIVER_DATA_SIZE > माप(skb->cb));

	ret = rc80211_minstrel_init();
	अगर (ret)
		वापस ret;

	ret = ieee80211_अगरace_init();
	अगर (ret)
		जाओ err_netdev;

	वापस 0;
 err_netdev:
	rc80211_minstrel_निकास();

	वापस ret;
पूर्ण

अटल व्योम __निकास ieee80211_निकास(व्योम)
अणु
	rc80211_minstrel_निकास();

	ieee80211s_stop();

	ieee80211_अगरace_निकास();

	rcu_barrier();
पूर्ण


subsys_initcall(ieee80211_init);
module_निकास(ieee80211_निकास);

MODULE_DESCRIPTION("IEEE 802.11 subsystem");
MODULE_LICENSE("GPL");
