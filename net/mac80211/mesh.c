<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008, 2009 खोलो80211s Ltd.
 * Copyright (C) 2018 - 2020 Intel Corporation
 * Authors:    Luis Carlos Cobo <luisca@cozybit.com>
 * 	       Javier Carकरोna <javier@cozybit.com>
 */

#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "ieee80211_i.h"
#समावेश "mesh.h"
#समावेश "driver-ops.h"

अटल पूर्णांक mesh_allocated;
अटल काष्ठा kmem_cache *rm_cache;

bool mesh_action_is_path_sel(काष्ठा ieee80211_mgmt *mgmt)
अणु
	वापस (mgmt->u.action.u.mesh_action.action_code ==
			WLAN_MESH_ACTION_HWMP_PATH_SELECTION);
पूर्ण

व्योम ieee80211s_init(व्योम)
अणु
	mesh_allocated = 1;
	rm_cache = kmem_cache_create("mesh_rmc", माप(काष्ठा rmc_entry),
				     0, 0, शून्य);
पूर्ण

व्योम ieee80211s_stop(व्योम)
अणु
	अगर (!mesh_allocated)
		वापस;
	kmem_cache_destroy(rm_cache);
पूर्ण

अटल व्योम ieee80211_mesh_housekeeping_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		from_समयr(sdata, t, u.mesh.housekeeping_समयr);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;

	set_bit(MESH_WORK_HOUSEKEEPING, &अगरmsh->wrkq_flags);

	ieee80211_queue_work(&local->hw, &sdata->work);
पूर्ण

/**
 * mesh_matches_local - check अगर the config of a mesh poपूर्णांक matches ours
 *
 * @sdata: local mesh subअगर
 * @ie: inक्रमmation elements of a management frame from the mesh peer
 *
 * This function checks अगर the mesh configuration of a mesh poपूर्णांक matches the
 * local mesh configuration, i.e. अगर both nodes beदीर्घ to the same mesh network.
 */
bool mesh_matches_local(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा ieee802_11_elems *ie)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	u32 basic_rates = 0;
	काष्ठा cfg80211_chan_def sta_chan_def;
	काष्ठा ieee80211_supported_band *sband;
	u32 vht_cap_info = 0;

	/*
	 * As support क्रम each feature is added, check क्रम matching
	 * - On mesh config capabilities
	 *   - Power Save Support En
	 *   - Sync support enabled
	 *   - Sync support active
	 *   - Sync support required from peer
	 *   - MDA enabled
	 * - Power management control on fc
	 */
	अगर (!(अगरmsh->mesh_id_len == ie->mesh_id_len &&
	     स_भेद(अगरmsh->mesh_id, ie->mesh_id, ie->mesh_id_len) == 0 &&
	     (अगरmsh->mesh_pp_id == ie->mesh_config->meshconf_psel) &&
	     (अगरmsh->mesh_pm_id == ie->mesh_config->meshconf_pmetric) &&
	     (अगरmsh->mesh_cc_id == ie->mesh_config->meshconf_congest) &&
	     (अगरmsh->mesh_sp_id == ie->mesh_config->meshconf_synch) &&
	     (अगरmsh->mesh_auth_id == ie->mesh_config->meshconf_auth)))
		वापस false;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस false;

	ieee80211_sta_get_rates(sdata, ie, sband->band,
				&basic_rates);

	अगर (sdata->vअगर.bss_conf.basic_rates != basic_rates)
		वापस false;

	cfg80211_chandef_create(&sta_chan_def, sdata->vअगर.bss_conf.chandef.chan,
				NL80211_CHAN_NO_HT);
	ieee80211_chandef_ht_oper(ie->ht_operation, &sta_chan_def);

	अगर (ie->vht_cap_elem)
		vht_cap_info = le32_to_cpu(ie->vht_cap_elem->vht_cap_info);

	ieee80211_chandef_vht_oper(&sdata->local->hw, vht_cap_info,
				   ie->vht_operation, ie->ht_operation,
				   &sta_chan_def);
	ieee80211_chandef_he_6ghz_oper(sdata, ie->he_operation, &sta_chan_def);

	अगर (!cfg80211_chandef_compatible(&sdata->vअगर.bss_conf.chandef,
					 &sta_chan_def))
		वापस false;

	वापस true;
पूर्ण

/**
 * mesh_peer_accepts_plinks - check अगर an mp is willing to establish peer links
 *
 * @ie: inक्रमmation elements of a management frame from the mesh peer
 */
bool mesh_peer_accepts_plinks(काष्ठा ieee802_11_elems *ie)
अणु
	वापस (ie->mesh_config->meshconf_cap &
			IEEE80211_MESHCONF_CAPAB_ACCEPT_PLINKS) != 0;
पूर्ण

/**
 * mesh_accept_plinks_update - update accepting_plink in local mesh beacons
 *
 * @sdata: mesh पूर्णांकerface in which mesh beacons are going to be updated
 *
 * Returns: beacon changed flag अगर the beacon content changed.
 */
u32 mesh_accept_plinks_update(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	bool मुक्त_plinks;
	u32 changed = 0;

	/* In हाल mesh_plink_मुक्त_count > 0 and mesh_plinktbl_capacity == 0,
	 * the mesh पूर्णांकerface might be able to establish plinks with peers that
	 * are alपढ़ोy on the table but are not on PLINK_ESTAB state. However,
	 * in general the mesh पूर्णांकerface is not accepting peer link requests
	 * from new peers, and that must be reflected in the beacon
	 */
	मुक्त_plinks = mesh_plink_availables(sdata);

	अगर (मुक्त_plinks != sdata->u.mesh.accepting_plinks) अणु
		sdata->u.mesh.accepting_plinks = मुक्त_plinks;
		changed = BSS_CHANGED_BEACON;
	पूर्ण

	वापस changed;
पूर्ण

/*
 * mesh_sta_cleanup - clean up any mesh sta state
 *
 * @sta: mesh sta to clean up.
 */
व्योम mesh_sta_cleanup(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	u32 changed = mesh_plink_deactivate(sta);

	अगर (changed)
		ieee80211_mbss_info_change_notअगरy(sdata, changed);
पूर्ण

पूर्णांक mesh_rmc_init(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	पूर्णांक i;

	sdata->u.mesh.rmc = kदो_स्मृति(माप(काष्ठा mesh_rmc), GFP_KERNEL);
	अगर (!sdata->u.mesh.rmc)
		वापस -ENOMEM;
	sdata->u.mesh.rmc->idx_mask = RMC_BUCKETS - 1;
	क्रम (i = 0; i < RMC_BUCKETS; i++)
		INIT_HLIST_HEAD(&sdata->u.mesh.rmc->bucket[i]);
	वापस 0;
पूर्ण

व्योम mesh_rmc_मुक्त(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा mesh_rmc *rmc = sdata->u.mesh.rmc;
	काष्ठा rmc_entry *p;
	काष्ठा hlist_node *n;
	पूर्णांक i;

	अगर (!sdata->u.mesh.rmc)
		वापस;

	क्रम (i = 0; i < RMC_BUCKETS; i++) अणु
		hlist_क्रम_each_entry_safe(p, n, &rmc->bucket[i], list) अणु
			hlist_del(&p->list);
			kmem_cache_मुक्त(rm_cache, p);
		पूर्ण
	पूर्ण

	kमुक्त(rmc);
	sdata->u.mesh.rmc = शून्य;
पूर्ण

/**
 * mesh_rmc_check - Check frame in recent multicast cache and add अगर असलent.
 *
 * @sdata:	पूर्णांकerface
 * @sa:		source address
 * @mesh_hdr:	mesh_header
 *
 * Returns: 0 अगर the frame is not in the cache, nonzero otherwise.
 *
 * Checks using the source address and the mesh sequence number अगर we have
 * received this frame lately. If the frame is not in the cache, it is added to
 * it.
 */
पूर्णांक mesh_rmc_check(काष्ठा ieee80211_sub_अगर_data *sdata,
		   स्थिर u8 *sa, काष्ठा ieee80211s_hdr *mesh_hdr)
अणु
	काष्ठा mesh_rmc *rmc = sdata->u.mesh.rmc;
	u32 seqnum = 0;
	पूर्णांक entries = 0;
	u8 idx;
	काष्ठा rmc_entry *p;
	काष्ठा hlist_node *n;

	अगर (!rmc)
		वापस -1;

	/* Don't care about endianness since only match matters */
	स_नकल(&seqnum, &mesh_hdr->seqnum, माप(mesh_hdr->seqnum));
	idx = le32_to_cpu(mesh_hdr->seqnum) & rmc->idx_mask;
	hlist_क्रम_each_entry_safe(p, n, &rmc->bucket[idx], list) अणु
		++entries;
		अगर (समय_after(jअगरfies, p->exp_समय) ||
		    entries == RMC_QUEUE_MAX_LEN) अणु
			hlist_del(&p->list);
			kmem_cache_मुक्त(rm_cache, p);
			--entries;
		पूर्ण अन्यथा अगर ((seqnum == p->seqnum) && ether_addr_equal(sa, p->sa))
			वापस -1;
	पूर्ण

	p = kmem_cache_alloc(rm_cache, GFP_ATOMIC);
	अगर (!p)
		वापस 0;

	p->seqnum = seqnum;
	p->exp_समय = jअगरfies + RMC_TIMEOUT;
	स_नकल(p->sa, sa, ETH_ALEN);
	hlist_add_head(&p->list, &rmc->bucket[idx]);
	वापस 0;
पूर्ण

पूर्णांक mesh_add_meshconf_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	u8 *pos, neighbors;
	u8 meshconf_len = माप(काष्ठा ieee80211_meshconf_ie);
	bool is_connected_to_gate = अगरmsh->num_gates > 0 ||
		अगरmsh->mshcfg.करोt11MeshGateAnnouncementProtocol ||
		अगरmsh->mshcfg.करोt11MeshConnectedToMeshGate;
	bool is_connected_to_as = अगरmsh->mshcfg.करोt11MeshConnectedToAuthServer;

	अगर (skb_tailroom(skb) < 2 + meshconf_len)
		वापस -ENOMEM;

	pos = skb_put(skb, 2 + meshconf_len);
	*pos++ = WLAN_EID_MESH_CONFIG;
	*pos++ = meshconf_len;

	/* save a poपूर्णांकer क्रम quick updates in pre-tbtt */
	अगरmsh->meshconf_offset = pos - skb->data;

	/* Active path selection protocol ID */
	*pos++ = अगरmsh->mesh_pp_id;
	/* Active path selection metric ID   */
	*pos++ = अगरmsh->mesh_pm_id;
	/* Congestion control mode identअगरier */
	*pos++ = अगरmsh->mesh_cc_id;
	/* Synchronization protocol identअगरier */
	*pos++ = अगरmsh->mesh_sp_id;
	/* Authentication Protocol identअगरier */
	*pos++ = अगरmsh->mesh_auth_id;
	/* Mesh Formation Info - number of neighbors */
	neighbors = atomic_पढ़ो(&अगरmsh->estab_plinks);
	neighbors = min_t(पूर्णांक, neighbors, IEEE80211_MAX_MESH_PEERINGS);
	*pos++ = (is_connected_to_as << 7) |
		 (neighbors << 1) |
		 is_connected_to_gate;
	/* Mesh capability */
	*pos = 0x00;
	*pos |= अगरmsh->mshcfg.करोt11MeshForwarding ?
			IEEE80211_MESHCONF_CAPAB_FORWARDING : 0x00;
	*pos |= अगरmsh->accepting_plinks ?
			IEEE80211_MESHCONF_CAPAB_ACCEPT_PLINKS : 0x00;
	/* Mesh PS mode. See IEEE802.11-2012 8.4.2.100.8 */
	*pos |= अगरmsh->ps_peers_deep_sleep ?
			IEEE80211_MESHCONF_CAPAB_POWER_SAVE_LEVEL : 0x00;
	वापस 0;
पूर्ण

पूर्णांक mesh_add_meshid_ie(काष्ठा ieee80211_sub_अगर_data *sdata, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	u8 *pos;

	अगर (skb_tailroom(skb) < 2 + अगरmsh->mesh_id_len)
		वापस -ENOMEM;

	pos = skb_put(skb, 2 + अगरmsh->mesh_id_len);
	*pos++ = WLAN_EID_MESH_ID;
	*pos++ = अगरmsh->mesh_id_len;
	अगर (अगरmsh->mesh_id_len)
		स_नकल(pos, अगरmsh->mesh_id, अगरmsh->mesh_id_len);

	वापस 0;
पूर्ण

अटल पूर्णांक mesh_add_awake_winकरोw_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	u8 *pos;

	/* see IEEE802.11-2012 13.14.6 */
	अगर (अगरmsh->ps_peers_light_sleep == 0 &&
	    अगरmsh->ps_peers_deep_sleep == 0 &&
	    अगरmsh->nonpeer_pm == NL80211_MESH_POWER_ACTIVE)
		वापस 0;

	अगर (skb_tailroom(skb) < 4)
		वापस -ENOMEM;

	pos = skb_put(skb, 2 + 2);
	*pos++ = WLAN_EID_MESH_AWAKE_WINDOW;
	*pos++ = 2;
	put_unaligned_le16(अगरmsh->mshcfg.करोt11MeshAwakeWinकरोwDuration, pos);

	वापस 0;
पूर्ण

पूर्णांक mesh_add_venकरोr_ies(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	u8 offset, len;
	स्थिर u8 *data;

	अगर (!अगरmsh->ie || !अगरmsh->ie_len)
		वापस 0;

	/* fast-क्रमward to venकरोr IEs */
	offset = ieee80211_ie_split_venकरोr(अगरmsh->ie, अगरmsh->ie_len, 0);

	अगर (offset < अगरmsh->ie_len) अणु
		len = अगरmsh->ie_len - offset;
		data = अगरmsh->ie + offset;
		अगर (skb_tailroom(skb) < len)
			वापस -ENOMEM;
		skb_put_data(skb, data, len);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mesh_add_rsn_ie(काष्ठा ieee80211_sub_अगर_data *sdata, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	u8 len = 0;
	स्थिर u8 *data;

	अगर (!अगरmsh->ie || !अगरmsh->ie_len)
		वापस 0;

	/* find RSN IE */
	data = cfg80211_find_ie(WLAN_EID_RSN, अगरmsh->ie, अगरmsh->ie_len);
	अगर (!data)
		वापस 0;

	len = data[1] + 2;

	अगर (skb_tailroom(skb) < len)
		वापस -ENOMEM;
	skb_put_data(skb, data, len);

	वापस 0;
पूर्ण

अटल पूर्णांक mesh_add_ds_params_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_channel *chan;
	u8 *pos;

	अगर (skb_tailroom(skb) < 3)
		वापस -ENOMEM;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (WARN_ON(!chanctx_conf)) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण
	chan = chanctx_conf->def.chan;
	rcu_पढ़ो_unlock();

	pos = skb_put(skb, 2 + 1);
	*pos++ = WLAN_EID_DS_PARAMS;
	*pos++ = 1;
	*pos++ = ieee80211_frequency_to_channel(chan->center_freq);

	वापस 0;
पूर्ण

पूर्णांक mesh_add_ht_cap_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_supported_band *sband;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस -EINVAL;

	/* HT not allowed in 6 GHz */
	अगर (sband->band == NL80211_BAND_6GHZ)
		वापस 0;

	अगर (!sband->ht_cap.ht_supported ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_5 ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_10)
		वापस 0;

	अगर (skb_tailroom(skb) < 2 + माप(काष्ठा ieee80211_ht_cap))
		वापस -ENOMEM;

	pos = skb_put(skb, 2 + माप(काष्ठा ieee80211_ht_cap));
	ieee80211_ie_build_ht_cap(pos, &sband->ht_cap, sband->ht_cap.cap);

	वापस 0;
पूर्ण

पूर्णांक mesh_add_ht_oper_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_channel *channel;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_sta_ht_cap *ht_cap;
	u8 *pos;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (WARN_ON(!chanctx_conf)) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण
	channel = chanctx_conf->def.chan;
	rcu_पढ़ो_unlock();

	sband = local->hw.wiphy->bands[channel->band];
	ht_cap = &sband->ht_cap;

	/* HT not allowed in 6 GHz */
	अगर (sband->band == NL80211_BAND_6GHZ)
		वापस 0;

	अगर (!ht_cap->ht_supported ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_5 ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_10)
		वापस 0;

	अगर (skb_tailroom(skb) < 2 + माप(काष्ठा ieee80211_ht_operation))
		वापस -ENOMEM;

	pos = skb_put(skb, 2 + माप(काष्ठा ieee80211_ht_operation));
	ieee80211_ie_build_ht_oper(pos, ht_cap, &sdata->vअगर.bss_conf.chandef,
				   sdata->vअगर.bss_conf.ht_operation_mode,
				   false);

	वापस 0;
पूर्ण

पूर्णांक mesh_add_vht_cap_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_supported_band *sband;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस -EINVAL;

	/* VHT not allowed in 6 GHz */
	अगर (sband->band == NL80211_BAND_6GHZ)
		वापस 0;

	अगर (!sband->vht_cap.vht_supported ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_5 ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_10)
		वापस 0;

	अगर (skb_tailroom(skb) < 2 + माप(काष्ठा ieee80211_vht_cap))
		वापस -ENOMEM;

	pos = skb_put(skb, 2 + माप(काष्ठा ieee80211_vht_cap));
	ieee80211_ie_build_vht_cap(pos, &sband->vht_cap, sband->vht_cap.cap);

	वापस 0;
पूर्ण

पूर्णांक mesh_add_vht_oper_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_channel *channel;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_sta_vht_cap *vht_cap;
	u8 *pos;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (WARN_ON(!chanctx_conf)) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण
	channel = chanctx_conf->def.chan;
	rcu_पढ़ो_unlock();

	sband = local->hw.wiphy->bands[channel->band];
	vht_cap = &sband->vht_cap;

	/* VHT not allowed in 6 GHz */
	अगर (sband->band == NL80211_BAND_6GHZ)
		वापस 0;

	अगर (!vht_cap->vht_supported ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_5 ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_10)
		वापस 0;

	अगर (skb_tailroom(skb) < 2 + माप(काष्ठा ieee80211_vht_operation))
		वापस -ENOMEM;

	pos = skb_put(skb, 2 + माप(काष्ठा ieee80211_vht_operation));
	ieee80211_ie_build_vht_oper(pos, vht_cap,
				    &sdata->vअगर.bss_conf.chandef);

	वापस 0;
पूर्ण

पूर्णांक mesh_add_he_cap_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
		       काष्ठा sk_buff *skb, u8 ie_len)
अणु
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap;
	काष्ठा ieee80211_supported_band *sband;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस -EINVAL;

	he_cap = ieee80211_get_he_अगरtype_cap(sband, NL80211_IFTYPE_MESH_POINT);

	अगर (!he_cap ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_5 ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_10)
		वापस 0;

	अगर (skb_tailroom(skb) < ie_len)
		वापस -ENOMEM;

	pos = skb_put(skb, ie_len);
	ieee80211_ie_build_he_cap(pos, he_cap, pos + ie_len);

	वापस 0;
पूर्ण

पूर्णांक mesh_add_he_oper_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap;
	काष्ठा ieee80211_supported_band *sband;
	u32 len;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस -EINVAL;

	he_cap = ieee80211_get_he_अगरtype_cap(sband, NL80211_IFTYPE_MESH_POINT);
	अगर (!he_cap ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_5 ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_10)
		वापस 0;

	len = 2 + 1 + माप(काष्ठा ieee80211_he_operation);
	अगर (sdata->vअगर.bss_conf.chandef.chan->band == NL80211_BAND_6GHZ)
		len += माप(काष्ठा ieee80211_he_6ghz_oper);

	अगर (skb_tailroom(skb) < len)
		वापस -ENOMEM;

	pos = skb_put(skb, len);
	ieee80211_ie_build_he_oper(pos, &sdata->vअगर.bss_conf.chandef);

	वापस 0;
पूर्ण

पूर्णांक mesh_add_he_6ghz_cap_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_supported_band *sband;
	स्थिर काष्ठा ieee80211_sband_अगरtype_data *अगरtd;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस -EINVAL;

	अगरtd = ieee80211_get_sband_अगरtype_data(sband,
					       NL80211_IFTYPE_MESH_POINT);
	/* The device करोesn't support HE in mesh mode or at all */
	अगर (!अगरtd)
		वापस 0;

	ieee80211_ie_build_he_6ghz_cap(sdata, skb);
	वापस 0;
पूर्ण

अटल व्योम ieee80211_mesh_path_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		from_समयr(sdata, t, u.mesh.mesh_path_समयr);

	ieee80211_queue_work(&sdata->local->hw, &sdata->work);
पूर्ण

अटल व्योम ieee80211_mesh_path_root_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		from_समयr(sdata, t, u.mesh.mesh_path_root_समयr);
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;

	set_bit(MESH_WORK_ROOT, &अगरmsh->wrkq_flags);

	ieee80211_queue_work(&sdata->local->hw, &sdata->work);
पूर्ण

व्योम ieee80211_mesh_root_setup(काष्ठा ieee80211_अगर_mesh *अगरmsh)
अणु
	अगर (अगरmsh->mshcfg.करोt11MeshHWMPRootMode > IEEE80211_ROOTMODE_ROOT)
		set_bit(MESH_WORK_ROOT, &अगरmsh->wrkq_flags);
	अन्यथा अणु
		clear_bit(MESH_WORK_ROOT, &अगरmsh->wrkq_flags);
		/* stop running समयr */
		del_समयr_sync(&अगरmsh->mesh_path_root_समयr);
	पूर्ण
पूर्ण

अटल व्योम
ieee80211_mesh_update_bss_params(काष्ठा ieee80211_sub_अगर_data *sdata,
				 u8 *ie, u8 ie_len)
अणु
	काष्ठा ieee80211_supported_band *sband;
	स्थिर u8 *cap;
	स्थिर काष्ठा ieee80211_he_operation *he_oper = शून्य;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस;

	अगर (!ieee80211_get_he_अगरtype_cap(sband, NL80211_IFTYPE_MESH_POINT) ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_5 ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_10)
		वापस;

	sdata->vअगर.bss_conf.he_support = true;

	cap = cfg80211_find_ext_ie(WLAN_EID_EXT_HE_OPERATION, ie, ie_len);
	अगर (cap && cap[1] >= ieee80211_he_oper_size(&cap[3]))
		he_oper = (व्योम *)(cap + 3);

	अगर (he_oper)
		sdata->vअगर.bss_conf.he_oper.params =
			__le32_to_cpu(he_oper->he_oper_params);
पूर्ण

/**
 * ieee80211_fill_mesh_addresses - fill addresses of a locally originated mesh frame
 * @hdr:	802.11 frame header
 * @fc:		frame control field
 * @meshda:	destination address in the mesh
 * @meshsa:	source address in the mesh.  Same as TA, as frame is
 *              locally originated.
 *
 * Return the length of the 802.11 (करोes not include a mesh control header)
 */
पूर्णांक ieee80211_fill_mesh_addresses(काष्ठा ieee80211_hdr *hdr, __le16 *fc,
				  स्थिर u8 *meshda, स्थिर u8 *meshsa)
अणु
	अगर (is_multicast_ether_addr(meshda)) अणु
		*fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS);
		/* DA TA SA */
		स_नकल(hdr->addr1, meshda, ETH_ALEN);
		स_नकल(hdr->addr2, meshsa, ETH_ALEN);
		स_नकल(hdr->addr3, meshsa, ETH_ALEN);
		वापस 24;
	पूर्ण अन्यथा अणु
		*fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS | IEEE80211_FCTL_TODS);
		/* RA TA DA SA */
		eth_zero_addr(hdr->addr1);   /* RA is resolved later */
		स_नकल(hdr->addr2, meshsa, ETH_ALEN);
		स_नकल(hdr->addr3, meshda, ETH_ALEN);
		स_नकल(hdr->addr4, meshsa, ETH_ALEN);
		वापस 30;
	पूर्ण
पूर्ण

/**
 * ieee80211_new_mesh_header - create a new mesh header
 * @sdata:	mesh पूर्णांकerface to be used
 * @meshhdr:    uninitialized mesh header
 * @addr4or5:   1st address in the ae header, which may correspond to address 4
 *              (अगर addr6 is शून्य) or address 5 (अगर addr6 is present). It may
 *              be शून्य.
 * @addr6:	2nd address in the ae header, which corresponds to addr6 of the
 *              mesh frame
 *
 * Return the header length.
 */
अचिन्हित पूर्णांक ieee80211_new_mesh_header(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा ieee80211s_hdr *meshhdr,
				       स्थिर अक्षर *addr4or5, स्थिर अक्षर *addr6)
अणु
	अगर (WARN_ON(!addr4or5 && addr6))
		वापस 0;

	स_रखो(meshhdr, 0, माप(*meshhdr));

	meshhdr->ttl = sdata->u.mesh.mshcfg.करोt11MeshTTL;

	/* FIXME: racy -- TX on multiple queues can be concurrent */
	put_unaligned(cpu_to_le32(sdata->u.mesh.mesh_seqnum), &meshhdr->seqnum);
	sdata->u.mesh.mesh_seqnum++;

	अगर (addr4or5 && !addr6) अणु
		meshhdr->flags |= MESH_FLAGS_AE_A4;
		स_नकल(meshhdr->eaddr1, addr4or5, ETH_ALEN);
		वापस 2 * ETH_ALEN;
	पूर्ण अन्यथा अगर (addr4or5 && addr6) अणु
		meshhdr->flags |= MESH_FLAGS_AE_A5_A6;
		स_नकल(meshhdr->eaddr1, addr4or5, ETH_ALEN);
		स_नकल(meshhdr->eaddr2, addr6, ETH_ALEN);
		वापस 3 * ETH_ALEN;
	पूर्ण

	वापस ETH_ALEN;
पूर्ण

अटल व्योम ieee80211_mesh_housekeeping(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	u32 changed;

	अगर (अगरmsh->mshcfg.plink_समयout > 0)
		ieee80211_sta_expire(sdata, अगरmsh->mshcfg.plink_समयout * HZ);
	mesh_path_expire(sdata);

	changed = mesh_accept_plinks_update(sdata);
	ieee80211_mbss_info_change_notअगरy(sdata, changed);

	mod_समयr(&अगरmsh->housekeeping_समयr,
		  round_jअगरfies(jअगरfies +
				IEEE80211_MESH_HOUSEKEEPING_INTERVAL));
पूर्ण

अटल व्योम ieee80211_mesh_rootpath(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	u32 पूर्णांकerval;

	mesh_path_tx_root_frame(sdata);

	अगर (अगरmsh->mshcfg.करोt11MeshHWMPRootMode == IEEE80211_PROACTIVE_RANN)
		पूर्णांकerval = अगरmsh->mshcfg.करोt11MeshHWMPRannInterval;
	अन्यथा
		पूर्णांकerval = अगरmsh->mshcfg.करोt11MeshHWMProotInterval;

	mod_समयr(&अगरmsh->mesh_path_root_समयr,
		  round_jअगरfies(TU_TO_EXP_TIME(पूर्णांकerval)));
पूर्ण

अटल पूर्णांक
ieee80211_mesh_build_beacon(काष्ठा ieee80211_अगर_mesh *अगरmsh)
अणु
	काष्ठा beacon_data *bcn;
	पूर्णांक head_len, tail_len;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *mgmt;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा mesh_csa_settings *csa;
	क्रमागत nl80211_band band;
	u8 ie_len_he_cap;
	u8 *pos;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	पूर्णांक hdr_len = दुरत्वend(काष्ठा ieee80211_mgmt, u.beacon);

	sdata = container_of(अगरmsh, काष्ठा ieee80211_sub_अगर_data, u.mesh);
	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	band = chanctx_conf->def.chan->band;
	rcu_पढ़ो_unlock();

	ie_len_he_cap = ieee80211_ie_len_he_cap(sdata,
						NL80211_IFTYPE_MESH_POINT);
	head_len = hdr_len +
		   2 + /* शून्य SSID */
		   /* Channel Switch Announcement */
		   2 + माप(काष्ठा ieee80211_channel_sw_ie) +
		   /* Mesh Channel Switch Parameters */
		   2 + माप(काष्ठा ieee80211_mesh_chansw_params_ie) +
		   /* Channel Switch Wrapper + Wide Bandwidth CSA IE */
		   2 + 2 + माप(काष्ठा ieee80211_wide_bw_chansw_ie) +
		   2 + माप(काष्ठा ieee80211_sec_chan_offs_ie) +
		   2 + 8 + /* supported rates */
		   2 + 3; /* DS params */
	tail_len = 2 + (IEEE80211_MAX_SUPP_RATES - 8) +
		   2 + माप(काष्ठा ieee80211_ht_cap) +
		   2 + माप(काष्ठा ieee80211_ht_operation) +
		   2 + अगरmsh->mesh_id_len +
		   2 + माप(काष्ठा ieee80211_meshconf_ie) +
		   2 + माप(__le16) + /* awake winकरोw */
		   2 + माप(काष्ठा ieee80211_vht_cap) +
		   2 + माप(काष्ठा ieee80211_vht_operation) +
		   ie_len_he_cap +
		   2 + 1 + माप(काष्ठा ieee80211_he_operation) +
			   माप(काष्ठा ieee80211_he_6ghz_oper) +
		   2 + 1 + माप(काष्ठा ieee80211_he_6ghz_capa) +
		   अगरmsh->ie_len;

	bcn = kzalloc(माप(*bcn) + head_len + tail_len, GFP_KERNEL);
	/* need an skb क्रम IE builders to operate on */
	skb = dev_alloc_skb(max(head_len, tail_len));

	अगर (!bcn || !skb)
		जाओ out_मुक्त;

	/*
	 * poपूर्णांकers go पूर्णांकo the block we allocated,
	 * memory is | beacon_data | head | tail |
	 */
	bcn->head = ((u8 *) bcn) + माप(*bcn);

	/* fill in the head */
	mgmt = skb_put_zero(skb, hdr_len);
	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_BEACON);
	eth_broadcast_addr(mgmt->da);
	स_नकल(mgmt->sa, sdata->vअगर.addr, ETH_ALEN);
	स_नकल(mgmt->bssid, sdata->vअगर.addr, ETH_ALEN);
	ieee80211_mps_set_frame_flags(sdata, शून्य, (व्योम *) mgmt);
	mgmt->u.beacon.beacon_पूर्णांक =
		cpu_to_le16(sdata->vअगर.bss_conf.beacon_पूर्णांक);
	mgmt->u.beacon.capab_info |= cpu_to_le16(
		sdata->u.mesh.security ? WLAN_CAPABILITY_PRIVACY : 0);

	pos = skb_put(skb, 2);
	*pos++ = WLAN_EID_SSID;
	*pos++ = 0x0;

	rcu_पढ़ो_lock();
	csa = rcu_dereference(अगरmsh->csa);
	अगर (csa) अणु
		क्रमागत nl80211_channel_type ct;
		काष्ठा cfg80211_chan_def *chandef;
		पूर्णांक ie_len = 2 + माप(काष्ठा ieee80211_channel_sw_ie) +
			     2 + माप(काष्ठा ieee80211_mesh_chansw_params_ie);

		pos = skb_put_zero(skb, ie_len);
		*pos++ = WLAN_EID_CHANNEL_SWITCH;
		*pos++ = 3;
		*pos++ = 0x0;
		*pos++ = ieee80211_frequency_to_channel(
				csa->settings.chandef.chan->center_freq);
		bcn->cntdwn_current_counter = csa->settings.count;
		bcn->cntdwn_counter_offsets[0] = hdr_len + 6;
		*pos++ = csa->settings.count;
		*pos++ = WLAN_EID_CHAN_SWITCH_PARAM;
		*pos++ = 6;
		अगर (अगरmsh->csa_role == IEEE80211_MESH_CSA_ROLE_INIT) अणु
			*pos++ = अगरmsh->mshcfg.करोt11MeshTTL;
			*pos |= WLAN_EID_CHAN_SWITCH_PARAM_INITIATOR;
		पूर्ण अन्यथा अणु
			*pos++ = अगरmsh->chsw_ttl;
		पूर्ण
		*pos++ |= csa->settings.block_tx ?
			  WLAN_EID_CHAN_SWITCH_PARAM_TX_RESTRICT : 0x00;
		put_unaligned_le16(WLAN_REASON_MESH_CHAN, pos);
		pos += 2;
		put_unaligned_le16(अगरmsh->pre_value, pos);
		pos += 2;

		चयन (csa->settings.chandef.width) अणु
		हाल NL80211_CHAN_WIDTH_40:
			ie_len = 2 + माप(काष्ठा ieee80211_sec_chan_offs_ie);
			pos = skb_put_zero(skb, ie_len);

			*pos++ = WLAN_EID_SECONDARY_CHANNEL_OFFSET; /* EID */
			*pos++ = 1;				    /* len */
			ct = cfg80211_get_chandef_type(&csa->settings.chandef);
			अगर (ct == NL80211_CHAN_HT40PLUS)
				*pos++ = IEEE80211_HT_PARAM_CHA_SEC_ABOVE;
			अन्यथा
				*pos++ = IEEE80211_HT_PARAM_CHA_SEC_BELOW;
			अवरोध;
		हाल NL80211_CHAN_WIDTH_80:
		हाल NL80211_CHAN_WIDTH_80P80:
		हाल NL80211_CHAN_WIDTH_160:
			/* Channel Switch Wrapper + Wide Bandwidth CSA IE */
			ie_len = 2 + 2 +
				 माप(काष्ठा ieee80211_wide_bw_chansw_ie);
			pos = skb_put_zero(skb, ie_len);

			*pos++ = WLAN_EID_CHANNEL_SWITCH_WRAPPER; /* EID */
			*pos++ = 5;				  /* len */
			/* put sub IE */
			chandef = &csa->settings.chandef;
			ieee80211_ie_build_wide_bw_cs(pos, chandef);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (ieee80211_add_srates_ie(sdata, skb, true, band) ||
	    mesh_add_ds_params_ie(sdata, skb))
		जाओ out_मुक्त;

	bcn->head_len = skb->len;
	स_नकल(bcn->head, skb->data, bcn->head_len);

	/* now the tail */
	skb_trim(skb, 0);
	bcn->tail = bcn->head + bcn->head_len;

	अगर (ieee80211_add_ext_srates_ie(sdata, skb, true, band) ||
	    mesh_add_rsn_ie(sdata, skb) ||
	    mesh_add_ht_cap_ie(sdata, skb) ||
	    mesh_add_ht_oper_ie(sdata, skb) ||
	    mesh_add_meshid_ie(sdata, skb) ||
	    mesh_add_meshconf_ie(sdata, skb) ||
	    mesh_add_awake_winकरोw_ie(sdata, skb) ||
	    mesh_add_vht_cap_ie(sdata, skb) ||
	    mesh_add_vht_oper_ie(sdata, skb) ||
	    mesh_add_he_cap_ie(sdata, skb, ie_len_he_cap) ||
	    mesh_add_he_oper_ie(sdata, skb) ||
	    mesh_add_he_6ghz_cap_ie(sdata, skb) ||
	    mesh_add_venकरोr_ies(sdata, skb))
		जाओ out_मुक्त;

	bcn->tail_len = skb->len;
	स_नकल(bcn->tail, skb->data, bcn->tail_len);
	ieee80211_mesh_update_bss_params(sdata, bcn->tail, bcn->tail_len);
	bcn->meshconf = (काष्ठा ieee80211_meshconf_ie *)
					(bcn->tail + अगरmsh->meshconf_offset);

	dev_kमुक्त_skb(skb);
	rcu_assign_poपूर्णांकer(अगरmsh->beacon, bcn);
	वापस 0;
out_मुक्त:
	kमुक्त(bcn);
	dev_kमुक्त_skb(skb);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक
ieee80211_mesh_rebuild_beacon(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा beacon_data *old_bcn;
	पूर्णांक ret;

	old_bcn = rcu_dereference_रक्षित(sdata->u.mesh.beacon,
					    lockdep_is_held(&sdata->wdev.mtx));
	ret = ieee80211_mesh_build_beacon(&sdata->u.mesh);
	अगर (ret)
		/* just reuse old beacon */
		वापस ret;

	अगर (old_bcn)
		kमुक्त_rcu(old_bcn, rcu_head);
	वापस 0;
पूर्ण

व्योम ieee80211_mbss_info_change_notअगरy(काष्ठा ieee80211_sub_अगर_data *sdata,
				       u32 changed)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	अचिन्हित दीर्घ bits = changed;
	u32 bit;

	अगर (!bits)
		वापस;

	/* अगर we race with running work, worst हाल this work becomes a noop */
	क्रम_each_set_bit(bit, &bits, माप(changed) * BITS_PER_BYTE)
		set_bit(bit, &अगरmsh->mbss_changed);
	set_bit(MESH_WORK_MBSS_CHANGED, &अगरmsh->wrkq_flags);
	ieee80211_queue_work(&sdata->local->hw, &sdata->work);
पूर्ण

पूर्णांक ieee80211_start_mesh(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा ieee80211_local *local = sdata->local;
	u32 changed = BSS_CHANGED_BEACON |
		      BSS_CHANGED_BEACON_ENABLED |
		      BSS_CHANGED_HT |
		      BSS_CHANGED_BASIC_RATES |
		      BSS_CHANGED_BEACON_INT |
		      BSS_CHANGED_MCAST_RATE;

	local->fअगर_other_bss++;
	/* mesh अगरaces must set allmulti to क्रमward mcast traffic */
	atomic_inc(&local->अगरf_allmultis);
	ieee80211_configure_filter(local);

	अगरmsh->mesh_cc_id = 0;	/* Disabled */
	/* रेजिस्टर sync ops from extensible synchronization framework */
	अगरmsh->sync_ops = ieee80211_mesh_sync_ops_get(अगरmsh->mesh_sp_id);
	अगरmsh->sync_offset_घड़ीdrअगरt_max = 0;
	set_bit(MESH_WORK_HOUSEKEEPING, &अगरmsh->wrkq_flags);
	ieee80211_mesh_root_setup(अगरmsh);
	ieee80211_queue_work(&local->hw, &sdata->work);
	sdata->vअगर.bss_conf.ht_operation_mode =
				अगरmsh->mshcfg.ht_opmode;
	sdata->vअगर.bss_conf.enable_beacon = true;

	changed |= ieee80211_mps_local_status_update(sdata);

	अगर (ieee80211_mesh_build_beacon(अगरmsh)) अणु
		ieee80211_stop_mesh(sdata);
		वापस -ENOMEM;
	पूर्ण

	ieee80211_recalc_dtim(local, sdata);
	ieee80211_bss_info_change_notअगरy(sdata, changed);

	netअगर_carrier_on(sdata->dev);
	वापस 0;
पूर्ण

व्योम ieee80211_stop_mesh(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा beacon_data *bcn;

	netअगर_carrier_off(sdata->dev);

	/* flush STAs and mpaths on this अगरace */
	sta_info_flush(sdata);
	ieee80211_मुक्त_keys(sdata, true);
	mesh_path_flush_by_अगरace(sdata);

	/* stop the beacon */
	अगरmsh->mesh_id_len = 0;
	sdata->vअगर.bss_conf.enable_beacon = false;
	sdata->beacon_rate_set = false;
	clear_bit(SDATA_STATE_OFFCHANNEL_BEACON_STOPPED, &sdata->state);
	ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_BEACON_ENABLED);

	/* हटाओ beacon */
	bcn = rcu_dereference_रक्षित(अगरmsh->beacon,
					lockdep_is_held(&sdata->wdev.mtx));
	RCU_INIT_POINTER(अगरmsh->beacon, शून्य);
	kमुक्त_rcu(bcn, rcu_head);

	/* मुक्त all potentially still buffered group-addressed frames */
	local->total_ps_buffered -= skb_queue_len(&अगरmsh->ps.bc_buf);
	skb_queue_purge(&अगरmsh->ps.bc_buf);

	del_समयr_sync(&sdata->u.mesh.housekeeping_समयr);
	del_समयr_sync(&sdata->u.mesh.mesh_path_root_समयr);
	del_समयr_sync(&sdata->u.mesh.mesh_path_समयr);

	/* clear any mesh work (क्रम next join) we may have accrued */
	अगरmsh->wrkq_flags = 0;
	अगरmsh->mbss_changed = 0;

	local->fअगर_other_bss--;
	atomic_dec(&local->अगरf_allmultis);
	ieee80211_configure_filter(local);
पूर्ण

अटल व्योम ieee80211_mesh_csa_mark_radar(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	पूर्णांक err;

	/* अगर the current channel is a DFS channel, mark the channel as
	 * unavailable.
	 */
	err = cfg80211_chandef_dfs_required(sdata->local->hw.wiphy,
					    &sdata->vअगर.bss_conf.chandef,
					    NL80211_IFTYPE_MESH_POINT);
	अगर (err > 0)
		cfg80211_radar_event(sdata->local->hw.wiphy,
				     &sdata->vअगर.bss_conf.chandef, GFP_ATOMIC);
पूर्ण

अटल bool
ieee80211_mesh_process_chnचयन(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा ieee802_11_elems *elems, bool beacon)
अणु
	काष्ठा cfg80211_csa_settings params;
	काष्ठा ieee80211_csa_ie csa_ie;
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा ieee80211_supported_band *sband;
	पूर्णांक err;
	u32 sta_flags, vht_cap_info = 0;

	sdata_निश्चित_lock(sdata);

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस false;

	sta_flags = 0;
	चयन (sdata->vअगर.bss_conf.chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		sta_flags |= IEEE80211_STA_DISABLE_HT;
		fallthrough;
	हाल NL80211_CHAN_WIDTH_20:
		sta_flags |= IEEE80211_STA_DISABLE_40MHZ;
		fallthrough;
	हाल NL80211_CHAN_WIDTH_40:
		sta_flags |= IEEE80211_STA_DISABLE_VHT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (elems->vht_cap_elem)
		vht_cap_info =
			le32_to_cpu(elems->vht_cap_elem->vht_cap_info);

	स_रखो(&params, 0, माप(params));
	err = ieee80211_parse_ch_चयन_ie(sdata, elems, sband->band,
					   vht_cap_info,
					   sta_flags, sdata->vअगर.addr,
					   &csa_ie);
	अगर (err < 0)
		वापस false;
	अगर (err)
		वापस false;

	/* Mark the channel unavailable अगर the reason क्रम the चयन is
	 * regulatory.
	 */
	अगर (csa_ie.reason_code == WLAN_REASON_MESH_CHAN_REGULATORY)
		ieee80211_mesh_csa_mark_radar(sdata);

	params.chandef = csa_ie.chandef;
	params.count = csa_ie.count;

	अगर (!cfg80211_chandef_usable(sdata->local->hw.wiphy, &params.chandef,
				     IEEE80211_CHAN_DISABLED) ||
	    !cfg80211_reg_can_beacon(sdata->local->hw.wiphy, &params.chandef,
				     NL80211_IFTYPE_MESH_POINT)) अणु
		sdata_info(sdata,
			   "mesh STA %pM switches to unsupported channel (%d MHz, width:%d, CF1/2: %d/%d MHz), aborting\n",
			   sdata->vअगर.addr,
			   params.chandef.chan->center_freq,
			   params.chandef.width,
			   params.chandef.center_freq1,
			   params.chandef.center_freq2);
		वापस false;
	पूर्ण

	err = cfg80211_chandef_dfs_required(sdata->local->hw.wiphy,
					    &params.chandef,
					    NL80211_IFTYPE_MESH_POINT);
	अगर (err < 0)
		वापस false;
	अगर (err > 0 && !अगरmsh->userspace_handles_dfs) अणु
		sdata_info(sdata,
			   "mesh STA %pM switches to channel requiring DFS (%d MHz, width:%d, CF1/2: %d/%d MHz), aborting\n",
			   sdata->vअगर.addr,
			   params.chandef.chan->center_freq,
			   params.chandef.width,
			   params.chandef.center_freq1,
			   params.chandef.center_freq2);
		वापस false;
	पूर्ण

	params.radar_required = err;

	अगर (cfg80211_chandef_identical(&params.chandef,
				       &sdata->vअगर.bss_conf.chandef)) अणु
		mcsa_dbg(sdata,
			 "received csa with an identical chandef, ignoring\n");
		वापस true;
	पूर्ण

	mcsa_dbg(sdata,
		 "received channel switch announcement to go to channel %d MHz\n",
		 params.chandef.chan->center_freq);

	params.block_tx = csa_ie.mode & WLAN_EID_CHAN_SWITCH_PARAM_TX_RESTRICT;
	अगर (beacon) अणु
		अगरmsh->chsw_ttl = csa_ie.ttl - 1;
		अगर (अगरmsh->pre_value >= csa_ie.pre_value)
			वापस false;
		अगरmsh->pre_value = csa_ie.pre_value;
	पूर्ण

	अगर (अगरmsh->chsw_ttl >= अगरmsh->mshcfg.करोt11MeshTTL)
		वापस false;

	अगरmsh->csa_role = IEEE80211_MESH_CSA_ROLE_REPEATER;

	अगर (ieee80211_channel_चयन(sdata->local->hw.wiphy, sdata->dev,
				     &params) < 0)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम
ieee80211_mesh_rx_probe_req(काष्ठा ieee80211_sub_अगर_data *sdata,
			    काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा sk_buff *presp;
	काष्ठा beacon_data *bcn;
	काष्ठा ieee80211_mgmt *hdr;
	काष्ठा ieee802_11_elems elems;
	माप_प्रकार baselen;
	u8 *pos;

	pos = mgmt->u.probe_req.variable;
	baselen = (u8 *) pos - (u8 *) mgmt;
	अगर (baselen > len)
		वापस;

	ieee802_11_parse_elems(pos, len - baselen, false, &elems, mgmt->bssid,
			       शून्य);

	अगर (!elems.mesh_id)
		वापस;

	/* 802.11-2012 10.1.4.3.2 */
	अगर ((!ether_addr_equal(mgmt->da, sdata->vअगर.addr) &&
	     !is_broadcast_ether_addr(mgmt->da)) ||
	    elems.ssid_len != 0)
		वापस;

	अगर (elems.mesh_id_len != 0 &&
	    (elems.mesh_id_len != अगरmsh->mesh_id_len ||
	     स_भेद(elems.mesh_id, अगरmsh->mesh_id, अगरmsh->mesh_id_len)))
		वापस;

	rcu_पढ़ो_lock();
	bcn = rcu_dereference(अगरmsh->beacon);

	अगर (!bcn)
		जाओ out;

	presp = dev_alloc_skb(local->tx_headroom +
			      bcn->head_len + bcn->tail_len);
	अगर (!presp)
		जाओ out;

	skb_reserve(presp, local->tx_headroom);
	skb_put_data(presp, bcn->head, bcn->head_len);
	skb_put_data(presp, bcn->tail, bcn->tail_len);
	hdr = (काष्ठा ieee80211_mgmt *) presp->data;
	hdr->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					 IEEE80211_STYPE_PROBE_RESP);
	स_नकल(hdr->da, mgmt->sa, ETH_ALEN);
	IEEE80211_SKB_CB(presp)->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT;
	ieee80211_tx_skb(sdata, presp);
out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ieee80211_mesh_rx_bcn_presp(काष्ठा ieee80211_sub_अगर_data *sdata,
					u16 stype,
					काष्ठा ieee80211_mgmt *mgmt,
					माप_प्रकार len,
					काष्ठा ieee80211_rx_status *rx_status)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा ieee802_11_elems elems;
	काष्ठा ieee80211_channel *channel;
	माप_प्रकार baselen;
	पूर्णांक freq;
	क्रमागत nl80211_band band = rx_status->band;

	/* ignore ProbeResp to क्रमeign address */
	अगर (stype == IEEE80211_STYPE_PROBE_RESP &&
	    !ether_addr_equal(mgmt->da, sdata->vअगर.addr))
		वापस;

	baselen = (u8 *) mgmt->u.probe_resp.variable - (u8 *) mgmt;
	अगर (baselen > len)
		वापस;

	ieee802_11_parse_elems(mgmt->u.probe_resp.variable, len - baselen,
			       false, &elems, mgmt->bssid, शून्य);

	/* ignore non-mesh or secure / unsecure mismatch */
	अगर ((!elems.mesh_id || !elems.mesh_config) ||
	    (elems.rsn && sdata->u.mesh.security == IEEE80211_MESH_SEC_NONE) ||
	    (!elems.rsn && sdata->u.mesh.security != IEEE80211_MESH_SEC_NONE))
		वापस;

	अगर (elems.ds_params)
		freq = ieee80211_channel_to_frequency(elems.ds_params[0], band);
	अन्यथा
		freq = rx_status->freq;

	channel = ieee80211_get_channel(local->hw.wiphy, freq);

	अगर (!channel || channel->flags & IEEE80211_CHAN_DISABLED)
		वापस;

	अगर (mesh_matches_local(sdata, &elems)) अणु
		mpl_dbg(sdata, "rssi_threshold=%d,rx_status->signal=%d\n",
			sdata->u.mesh.mshcfg.rssi_threshold, rx_status->संकेत);
		अगर (!sdata->u.mesh.user_mpm ||
		    sdata->u.mesh.mshcfg.rssi_threshold == 0 ||
		    sdata->u.mesh.mshcfg.rssi_threshold < rx_status->संकेत)
			mesh_neighbour_update(sdata, mgmt->sa, &elems,
					      rx_status);

		अगर (अगरmsh->csa_role != IEEE80211_MESH_CSA_ROLE_INIT &&
		    !sdata->vअगर.csa_active)
			ieee80211_mesh_process_chnचयन(sdata, &elems, true);
	पूर्ण

	अगर (अगरmsh->sync_ops)
		अगरmsh->sync_ops->rx_bcn_presp(sdata,
			stype, mgmt, &elems, rx_status);
पूर्ण

पूर्णांक ieee80211_mesh_finish_csa(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा mesh_csa_settings *पंचांगp_csa_settings;
	पूर्णांक ret = 0;
	पूर्णांक changed = 0;

	/* Reset the TTL value and Initiator flag */
	अगरmsh->csa_role = IEEE80211_MESH_CSA_ROLE_NONE;
	अगरmsh->chsw_ttl = 0;

	/* Remove the CSA and MCSP elements from the beacon */
	पंचांगp_csa_settings = rcu_dereference_रक्षित(अगरmsh->csa,
					    lockdep_is_held(&sdata->wdev.mtx));
	RCU_INIT_POINTER(अगरmsh->csa, शून्य);
	अगर (पंचांगp_csa_settings)
		kमुक्त_rcu(पंचांगp_csa_settings, rcu_head);
	ret = ieee80211_mesh_rebuild_beacon(sdata);
	अगर (ret)
		वापस -EINVAL;

	changed |= BSS_CHANGED_BEACON;

	mcsa_dbg(sdata, "complete switching to center freq %d MHz",
		 sdata->vअगर.bss_conf.chandef.chan->center_freq);
	वापस changed;
पूर्ण

पूर्णांक ieee80211_mesh_csa_beacon(काष्ठा ieee80211_sub_अगर_data *sdata,
			      काष्ठा cfg80211_csa_settings *csa_settings)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा mesh_csa_settings *पंचांगp_csa_settings;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&sdata->wdev.mtx);

	पंचांगp_csa_settings = kदो_स्मृति(माप(*पंचांगp_csa_settings),
				   GFP_ATOMIC);
	अगर (!पंचांगp_csa_settings)
		वापस -ENOMEM;

	स_नकल(&पंचांगp_csa_settings->settings, csa_settings,
	       माप(काष्ठा cfg80211_csa_settings));

	rcu_assign_poपूर्णांकer(अगरmsh->csa, पंचांगp_csa_settings);

	ret = ieee80211_mesh_rebuild_beacon(sdata);
	अगर (ret) अणु
		पंचांगp_csa_settings = rcu_dereference(अगरmsh->csa);
		RCU_INIT_POINTER(अगरmsh->csa, शून्य);
		kमुक्त_rcu(पंचांगp_csa_settings, rcu_head);
		वापस ret;
	पूर्ण

	वापस BSS_CHANGED_BEACON;
पूर्ण

अटल पूर्णांक mesh_fwd_csa_frame(काष्ठा ieee80211_sub_अगर_data *sdata,
			       काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
			       काष्ठा ieee802_11_elems *elems)
अणु
	काष्ठा ieee80211_mgmt *mgmt_fwd;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_local *local = sdata->local;

	skb = dev_alloc_skb(local->tx_headroom + len);
	अगर (!skb)
		वापस -ENOMEM;
	skb_reserve(skb, local->tx_headroom);
	mgmt_fwd = skb_put(skb, len);

	elems->mesh_chansw_params_ie->mesh_ttl--;
	elems->mesh_chansw_params_ie->mesh_flags &=
		~WLAN_EID_CHAN_SWITCH_PARAM_INITIATOR;

	स_नकल(mgmt_fwd, mgmt, len);
	eth_broadcast_addr(mgmt_fwd->da);
	स_नकल(mgmt_fwd->sa, sdata->vअगर.addr, ETH_ALEN);
	स_नकल(mgmt_fwd->bssid, sdata->vअगर.addr, ETH_ALEN);

	ieee80211_tx_skb(sdata, skb);
	वापस 0;
पूर्ण

अटल व्योम mesh_rx_csa_frame(काष्ठा ieee80211_sub_अगर_data *sdata,
			      काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा ieee802_11_elems elems;
	u16 pre_value;
	bool fwd_csa = true;
	माप_प्रकार baselen;
	u8 *pos;

	अगर (mgmt->u.action.u.measurement.action_code !=
	    WLAN_ACTION_SPCT_CHL_SWITCH)
		वापस;

	pos = mgmt->u.action.u.chan_चयन.variable;
	baselen = दुरत्व(काष्ठा ieee80211_mgmt,
			   u.action.u.chan_चयन.variable);
	ieee802_11_parse_elems(pos, len - baselen, true, &elems,
			       mgmt->bssid, शून्य);

	अगर (!mesh_matches_local(sdata, &elems))
		वापस;

	अगरmsh->chsw_ttl = elems.mesh_chansw_params_ie->mesh_ttl;
	अगर (!--अगरmsh->chsw_ttl)
		fwd_csa = false;

	pre_value = le16_to_cpu(elems.mesh_chansw_params_ie->mesh_pre_value);
	अगर (अगरmsh->pre_value >= pre_value)
		वापस;

	अगरmsh->pre_value = pre_value;

	अगर (!sdata->vअगर.csa_active &&
	    !ieee80211_mesh_process_chnचयन(sdata, &elems, false)) अणु
		mcsa_dbg(sdata, "Failed to process CSA action frame");
		वापस;
	पूर्ण

	/* क्रमward or re-broadcast the CSA frame */
	अगर (fwd_csa) अणु
		अगर (mesh_fwd_csa_frame(sdata, mgmt, len, &elems) < 0)
			mcsa_dbg(sdata, "Failed to forward the CSA frame");
	पूर्ण
पूर्ण

अटल व्योम ieee80211_mesh_rx_mgmt_action(काष्ठा ieee80211_sub_अगर_data *sdata,
					  काष्ठा ieee80211_mgmt *mgmt,
					  माप_प्रकार len,
					  काष्ठा ieee80211_rx_status *rx_status)
अणु
	चयन (mgmt->u.action.category) अणु
	हाल WLAN_CATEGORY_SELF_PROTECTED:
		चयन (mgmt->u.action.u.self_prot.action_code) अणु
		हाल WLAN_SP_MESH_PEERING_OPEN:
		हाल WLAN_SP_MESH_PEERING_CLOSE:
		हाल WLAN_SP_MESH_PEERING_CONFIRM:
			mesh_rx_plink_frame(sdata, mgmt, len, rx_status);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल WLAN_CATEGORY_MESH_ACTION:
		अगर (mesh_action_is_path_sel(mgmt))
			mesh_rx_path_sel_frame(sdata, mgmt, len);
		अवरोध;
	हाल WLAN_CATEGORY_SPECTRUM_MGMT:
		mesh_rx_csa_frame(sdata, mgmt, len);
		अवरोध;
	पूर्ण
पूर्ण

व्योम ieee80211_mesh_rx_queued_mgmt(काष्ठा ieee80211_sub_अगर_data *sdata,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_rx_status *rx_status;
	काष्ठा ieee80211_mgmt *mgmt;
	u16 stype;

	sdata_lock(sdata);

	/* mesh alपढ़ोy went करोwn */
	अगर (!sdata->u.mesh.mesh_id_len)
		जाओ out;

	rx_status = IEEE80211_SKB_RXCB(skb);
	mgmt = (काष्ठा ieee80211_mgmt *) skb->data;
	stype = le16_to_cpu(mgmt->frame_control) & IEEE80211_FCTL_STYPE;

	चयन (stype) अणु
	हाल IEEE80211_STYPE_PROBE_RESP:
	हाल IEEE80211_STYPE_BEACON:
		ieee80211_mesh_rx_bcn_presp(sdata, stype, mgmt, skb->len,
					    rx_status);
		अवरोध;
	हाल IEEE80211_STYPE_PROBE_REQ:
		ieee80211_mesh_rx_probe_req(sdata, mgmt, skb->len);
		अवरोध;
	हाल IEEE80211_STYPE_ACTION:
		ieee80211_mesh_rx_mgmt_action(sdata, mgmt, skb->len, rx_status);
		अवरोध;
	पूर्ण
out:
	sdata_unlock(sdata);
पूर्ण

अटल व्योम mesh_bss_info_changed(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	u32 bit, changed = 0;

	क्रम_each_set_bit(bit, &अगरmsh->mbss_changed,
			 माप(changed) * BITS_PER_BYTE) अणु
		clear_bit(bit, &अगरmsh->mbss_changed);
		changed |= BIT(bit);
	पूर्ण

	अगर (sdata->vअगर.bss_conf.enable_beacon &&
	    (changed & (BSS_CHANGED_BEACON |
			BSS_CHANGED_HT |
			BSS_CHANGED_BASIC_RATES |
			BSS_CHANGED_BEACON_INT)))
		अगर (ieee80211_mesh_rebuild_beacon(sdata))
			वापस;

	ieee80211_bss_info_change_notअगरy(sdata, changed);
पूर्ण

व्योम ieee80211_mesh_work(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;

	sdata_lock(sdata);

	/* mesh alपढ़ोy went करोwn */
	अगर (!sdata->u.mesh.mesh_id_len)
		जाओ out;

	अगर (अगरmsh->preq_queue_len &&
	    समय_after(jअगरfies,
		       अगरmsh->last_preq + msecs_to_jअगरfies(अगरmsh->mshcfg.करोt11MeshHWMPpreqMinInterval)))
		mesh_path_start_discovery(sdata);

	अगर (test_and_clear_bit(MESH_WORK_HOUSEKEEPING, &अगरmsh->wrkq_flags))
		ieee80211_mesh_housekeeping(sdata);

	अगर (test_and_clear_bit(MESH_WORK_ROOT, &अगरmsh->wrkq_flags))
		ieee80211_mesh_rootpath(sdata);

	अगर (test_and_clear_bit(MESH_WORK_DRIFT_ADJUST, &अगरmsh->wrkq_flags))
		mesh_sync_adjust_tsf(sdata);

	अगर (test_and_clear_bit(MESH_WORK_MBSS_CHANGED, &अगरmsh->wrkq_flags))
		mesh_bss_info_changed(sdata);
out:
	sdata_unlock(sdata);
पूर्ण


व्योम ieee80211_mesh_init_sdata(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	अटल u8 zero_addr[ETH_ALEN] = अणुपूर्ण;

	समयr_setup(&अगरmsh->housekeeping_समयr,
		    ieee80211_mesh_housekeeping_समयr, 0);

	अगरmsh->accepting_plinks = true;
	atomic_set(&अगरmsh->mpaths, 0);
	mesh_rmc_init(sdata);
	अगरmsh->last_preq = jअगरfies;
	अगरmsh->next_perr = jअगरfies;
	अगरmsh->csa_role = IEEE80211_MESH_CSA_ROLE_NONE;
	/* Allocate all mesh काष्ठाures when creating the first mesh पूर्णांकerface. */
	अगर (!mesh_allocated)
		ieee80211s_init();

	mesh_pathtbl_init(sdata);

	समयr_setup(&अगरmsh->mesh_path_समयr, ieee80211_mesh_path_समयr, 0);
	समयr_setup(&अगरmsh->mesh_path_root_समयr,
		    ieee80211_mesh_path_root_समयr, 0);
	INIT_LIST_HEAD(&अगरmsh->preq_queue.list);
	skb_queue_head_init(&अगरmsh->ps.bc_buf);
	spin_lock_init(&अगरmsh->mesh_preq_queue_lock);
	spin_lock_init(&अगरmsh->sync_offset_lock);
	RCU_INIT_POINTER(अगरmsh->beacon, शून्य);

	sdata->vअगर.bss_conf.bssid = zero_addr;
पूर्ण

व्योम ieee80211_mesh_tearकरोwn_sdata(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	mesh_rmc_मुक्त(sdata);
	mesh_pathtbl_unरेजिस्टर(sdata);
पूर्ण
