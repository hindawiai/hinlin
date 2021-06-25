<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008, 2009 खोलो80211s Ltd.
 * Copyright (C) 2019 Intel Corporation
 * Author:     Luis Carlos Cobo <luisca@cozybit.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/etherdevice.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "wme.h"
#समावेश "mesh.h"

#घोषणा TEST_FRAME_LEN	8192
#घोषणा MAX_METRIC	0xffffffff
#घोषणा ARITH_SHIFT	8
#घोषणा LINK_FAIL_THRESH 95

#घोषणा MAX_PREQ_QUEUE_LEN	64

अटल व्योम mesh_queue_preq(काष्ठा mesh_path *, u8);

अटल अंतरभूत u32 u32_field_get(स्थिर u8 *preq_elem, पूर्णांक offset, bool ae)
अणु
	अगर (ae)
		offset += 6;
	वापस get_unaligned_le32(preq_elem + offset);
पूर्ण

अटल अंतरभूत u16 u16_field_get(स्थिर u8 *preq_elem, पूर्णांक offset, bool ae)
अणु
	अगर (ae)
		offset += 6;
	वापस get_unaligned_le16(preq_elem + offset);
पूर्ण

/* HWMP IE processing macros */
#घोषणा AE_F			(1<<6)
#घोषणा AE_F_SET(x)		(*x & AE_F)
#घोषणा PREQ_IE_FLAGS(x)	(*(x))
#घोषणा PREQ_IE_HOPCOUNT(x)	(*(x + 1))
#घोषणा PREQ_IE_TTL(x)		(*(x + 2))
#घोषणा PREQ_IE_PREQ_ID(x)	u32_field_get(x, 3, 0)
#घोषणा PREQ_IE_ORIG_ADDR(x)	(x + 7)
#घोषणा PREQ_IE_ORIG_SN(x)	u32_field_get(x, 13, 0)
#घोषणा PREQ_IE_LIFETIME(x)	u32_field_get(x, 17, AE_F_SET(x))
#घोषणा PREQ_IE_METRIC(x) 	u32_field_get(x, 21, AE_F_SET(x))
#घोषणा PREQ_IE_TARGET_F(x)	(*(AE_F_SET(x) ? x + 32 : x + 26))
#घोषणा PREQ_IE_TARGET_ADDR(x) 	(AE_F_SET(x) ? x + 33 : x + 27)
#घोषणा PREQ_IE_TARGET_SN(x) 	u32_field_get(x, 33, AE_F_SET(x))


#घोषणा PREP_IE_FLAGS(x)	PREQ_IE_FLAGS(x)
#घोषणा PREP_IE_HOPCOUNT(x)	PREQ_IE_HOPCOUNT(x)
#घोषणा PREP_IE_TTL(x)		PREQ_IE_TTL(x)
#घोषणा PREP_IE_ORIG_ADDR(x)	(AE_F_SET(x) ? x + 27 : x + 21)
#घोषणा PREP_IE_ORIG_SN(x)	u32_field_get(x, 27, AE_F_SET(x))
#घोषणा PREP_IE_LIFETIME(x)	u32_field_get(x, 13, AE_F_SET(x))
#घोषणा PREP_IE_METRIC(x)	u32_field_get(x, 17, AE_F_SET(x))
#घोषणा PREP_IE_TARGET_ADDR(x)	(x + 3)
#घोषणा PREP_IE_TARGET_SN(x)	u32_field_get(x, 9, 0)

#घोषणा PERR_IE_TTL(x)		(*(x))
#घोषणा PERR_IE_TARGET_FLAGS(x)	(*(x + 2))
#घोषणा PERR_IE_TARGET_ADDR(x)	(x + 3)
#घोषणा PERR_IE_TARGET_SN(x)	u32_field_get(x, 9, 0)
#घोषणा PERR_IE_TARGET_RCODE(x)	u16_field_get(x, 13, 0)

#घोषणा MSEC_TO_TU(x) (x*1000/1024)
#घोषणा SN_GT(x, y) ((s32)(y - x) < 0)
#घोषणा SN_LT(x, y) ((s32)(x - y) < 0)
#घोषणा MAX_SANE_SN_DELTA 32

अटल अंतरभूत u32 SN_DELTA(u32 x, u32 y)
अणु
	वापस x >= y ? x - y : y - x;
पूर्ण

#घोषणा net_traversal_jअगरfies(s) \
	msecs_to_jअगरfies(s->u.mesh.mshcfg.करोt11MeshHWMPnetDiameterTraversalTime)
#घोषणा शेष_lअगरeसमय(s) \
	MSEC_TO_TU(s->u.mesh.mshcfg.करोt11MeshHWMPactivePathTimeout)
#घोषणा min_preq_पूर्णांक_jअगरf(s) \
	(msecs_to_jअगरfies(s->u.mesh.mshcfg.करोt11MeshHWMPpreqMinInterval))
#घोषणा max_preq_retries(s) (s->u.mesh.mshcfg.करोt11MeshHWMPmaxPREQretries)
#घोषणा disc_समयout_jअगरf(s) \
	msecs_to_jअगरfies(sdata->u.mesh.mshcfg.min_discovery_समयout)
#घोषणा root_path_confirmation_jअगरfies(s) \
	msecs_to_jअगरfies(sdata->u.mesh.mshcfg.करोt11MeshHWMPconfirmationInterval)

क्रमागत mpath_frame_type अणु
	MPATH_PREQ = 0,
	MPATH_PREP,
	MPATH_PERR,
	MPATH_RANN
पूर्ण;

अटल स्थिर u8 broadcast_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

अटल पूर्णांक mesh_path_sel_frame_tx(क्रमागत mpath_frame_type action, u8 flags,
				  स्थिर u8 *orig_addr, u32 orig_sn,
				  u8 target_flags, स्थिर u8 *target,
				  u32 target_sn, स्थिर u8 *da,
				  u8 hop_count, u8 ttl,
				  u32 lअगरeसमय, u32 metric, u32 preq_id,
				  काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *mgmt;
	u8 *pos, ie_len;
	पूर्णांक hdr_len = दुरत्वend(काष्ठा ieee80211_mgmt,
				  u.action.u.mesh_action);

	skb = dev_alloc_skb(local->tx_headroom +
			    hdr_len +
			    2 + 37); /* max HWMP IE */
	अगर (!skb)
		वापस -1;
	skb_reserve(skb, local->tx_headroom);
	mgmt = skb_put_zero(skb, hdr_len);
	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);

	स_नकल(mgmt->da, da, ETH_ALEN);
	स_नकल(mgmt->sa, sdata->vअगर.addr, ETH_ALEN);
	/* BSSID == SA */
	स_नकल(mgmt->bssid, sdata->vअगर.addr, ETH_ALEN);
	mgmt->u.action.category = WLAN_CATEGORY_MESH_ACTION;
	mgmt->u.action.u.mesh_action.action_code =
					WLAN_MESH_ACTION_HWMP_PATH_SELECTION;

	चयन (action) अणु
	हाल MPATH_PREQ:
		mhwmp_dbg(sdata, "sending PREQ to %pM\n", target);
		ie_len = 37;
		pos = skb_put(skb, 2 + ie_len);
		*pos++ = WLAN_EID_PREQ;
		अवरोध;
	हाल MPATH_PREP:
		mhwmp_dbg(sdata, "sending PREP to %pM\n", orig_addr);
		ie_len = 31;
		pos = skb_put(skb, 2 + ie_len);
		*pos++ = WLAN_EID_PREP;
		अवरोध;
	हाल MPATH_RANN:
		mhwmp_dbg(sdata, "sending RANN from %pM\n", orig_addr);
		ie_len = माप(काष्ठा ieee80211_rann_ie);
		pos = skb_put(skb, 2 + ie_len);
		*pos++ = WLAN_EID_RANN;
		अवरोध;
	शेष:
		kमुक्त_skb(skb);
		वापस -ENOTSUPP;
	पूर्ण
	*pos++ = ie_len;
	*pos++ = flags;
	*pos++ = hop_count;
	*pos++ = ttl;
	अगर (action == MPATH_PREP) अणु
		स_नकल(pos, target, ETH_ALEN);
		pos += ETH_ALEN;
		put_unaligned_le32(target_sn, pos);
		pos += 4;
	पूर्ण अन्यथा अणु
		अगर (action == MPATH_PREQ) अणु
			put_unaligned_le32(preq_id, pos);
			pos += 4;
		पूर्ण
		स_नकल(pos, orig_addr, ETH_ALEN);
		pos += ETH_ALEN;
		put_unaligned_le32(orig_sn, pos);
		pos += 4;
	पूर्ण
	put_unaligned_le32(lअगरeसमय, pos); /* पूर्णांकerval क्रम RANN */
	pos += 4;
	put_unaligned_le32(metric, pos);
	pos += 4;
	अगर (action == MPATH_PREQ) अणु
		*pos++ = 1; /* destination count */
		*pos++ = target_flags;
		स_नकल(pos, target, ETH_ALEN);
		pos += ETH_ALEN;
		put_unaligned_le32(target_sn, pos);
		pos += 4;
	पूर्ण अन्यथा अगर (action == MPATH_PREP) अणु
		स_नकल(pos, orig_addr, ETH_ALEN);
		pos += ETH_ALEN;
		put_unaligned_le32(orig_sn, pos);
		pos += 4;
	पूर्ण

	ieee80211_tx_skb(sdata, skb);
	वापस 0;
पूर्ण


/*  Headroom is not adjusted.  Caller should ensure that skb has sufficient
 *  headroom in हाल the frame is encrypted. */
अटल व्योम prepare_frame_क्रम_deferred_tx(काष्ठा ieee80211_sub_अगर_data *sdata,
		काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;

	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);

	/* Send all पूर्णांकernal mgmt frames on VO. Accordingly set TID to 7. */
	skb_set_queue_mapping(skb, IEEE80211_AC_VO);
	skb->priority = 7;

	info->control.vअगर = &sdata->vअगर;
	info->control.flags |= IEEE80211_TX_INTCFL_NEED_TXPROCESSING;
	ieee80211_set_qos_hdr(sdata, skb);
	ieee80211_mps_set_frame_flags(sdata, शून्य, hdr);
पूर्ण

/**
 * mesh_path_error_tx - Sends a PERR mesh management frame
 *
 * @ttl: allowed reमुख्यing hops
 * @target: broken destination
 * @target_sn: SN of the broken destination
 * @target_rcode: reason code क्रम this PERR
 * @ra: node this frame is addressed to
 * @sdata: local mesh subअगर
 *
 * Note: This function may be called with driver locks taken that the driver
 * also acquires in the TX path.  To aव्योम a deadlock we करोn't transmit the
 * frame directly but add it to the pending queue instead.
 */
पूर्णांक mesh_path_error_tx(काष्ठा ieee80211_sub_अगर_data *sdata,
		       u8 ttl, स्थिर u8 *target, u32 target_sn,
		       u16 target_rcode, स्थिर u8 *ra)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा ieee80211_mgmt *mgmt;
	u8 *pos, ie_len;
	पूर्णांक hdr_len = दुरत्वend(काष्ठा ieee80211_mgmt,
				  u.action.u.mesh_action);

	अगर (समय_beक्रमe(jअगरfies, अगरmsh->next_perr))
		वापस -EAGAIN;

	skb = dev_alloc_skb(local->tx_headroom +
			    sdata->encrypt_headroom +
			    IEEE80211_ENCRYPT_TAILROOM +
			    hdr_len +
			    2 + 15 /* PERR IE */);
	अगर (!skb)
		वापस -1;
	skb_reserve(skb, local->tx_headroom + sdata->encrypt_headroom);
	mgmt = skb_put_zero(skb, hdr_len);
	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);

	स_नकल(mgmt->da, ra, ETH_ALEN);
	स_नकल(mgmt->sa, sdata->vअगर.addr, ETH_ALEN);
	/* BSSID == SA */
	स_नकल(mgmt->bssid, sdata->vअगर.addr, ETH_ALEN);
	mgmt->u.action.category = WLAN_CATEGORY_MESH_ACTION;
	mgmt->u.action.u.mesh_action.action_code =
					WLAN_MESH_ACTION_HWMP_PATH_SELECTION;
	ie_len = 15;
	pos = skb_put(skb, 2 + ie_len);
	*pos++ = WLAN_EID_PERR;
	*pos++ = ie_len;
	/* ttl */
	*pos++ = ttl;
	/* number of destinations */
	*pos++ = 1;
	/* Flags field has AE bit only as defined in
	 * sec 8.4.2.117 IEEE802.11-2012
	 */
	*pos = 0;
	pos++;
	स_नकल(pos, target, ETH_ALEN);
	pos += ETH_ALEN;
	put_unaligned_le32(target_sn, pos);
	pos += 4;
	put_unaligned_le16(target_rcode, pos);

	/* see note in function header */
	prepare_frame_क्रम_deferred_tx(sdata, skb);
	अगरmsh->next_perr = TU_TO_EXP_TIME(
				   अगरmsh->mshcfg.करोt11MeshHWMPperrMinInterval);
	ieee80211_add_pending_skb(local, skb);
	वापस 0;
पूर्ण

व्योम ieee80211s_update_metric(काष्ठा ieee80211_local *local,
			      काष्ठा sta_info *sta,
			      काष्ठा ieee80211_tx_status *st)
अणु
	काष्ठा ieee80211_tx_info *txinfo = st->info;
	पूर्णांक failed;
	काष्ठा rate_info rinfo;

	failed = !(txinfo->flags & IEEE80211_TX_STAT_ACK);

	/* moving average, scaled to 100.
	 * feed failure as 100 and success as 0
	 */
	ewma_mesh_fail_avg_add(&sta->mesh->fail_avg, failed * 100);
	अगर (ewma_mesh_fail_avg_पढ़ो(&sta->mesh->fail_avg) >
			LINK_FAIL_THRESH)
		mesh_plink_broken(sta);

	sta_set_rate_info_tx(sta, &sta->tx_stats.last_rate, &rinfo);
	ewma_mesh_tx_rate_avg_add(&sta->mesh->tx_rate_avg,
				  cfg80211_calculate_bitrate(&rinfo));
पूर्ण

u32 airसमय_link_metric_get(काष्ठा ieee80211_local *local,
			    काष्ठा sta_info *sta)
अणु
	/* This should be adjusted क्रम each device */
	पूर्णांक device_स्थिरant = 1 << ARITH_SHIFT;
	पूर्णांक test_frame_len = TEST_FRAME_LEN << ARITH_SHIFT;
	पूर्णांक s_unit = 1 << ARITH_SHIFT;
	पूर्णांक rate, err;
	u32 tx_समय, estimated_retx;
	u64 result;
	अचिन्हित दीर्घ fail_avg =
		ewma_mesh_fail_avg_पढ़ो(&sta->mesh->fail_avg);

	अगर (sta->mesh->plink_state != NL80211_PLINK_ESTAB)
		वापस MAX_METRIC;

	/* Try to get rate based on HW/SW RC algorithm.
	 * Rate is वापसed in units of Kbps, correct this
	 * to comply with airसमय calculation units
	 * Round up in हाल we get rate < 100Kbps
	 */
	rate = DIV_ROUND_UP(sta_get_expected_throughput(sta), 100);

	अगर (rate) अणु
		err = 0;
	पूर्ण अन्यथा अणु
		अगर (fail_avg > LINK_FAIL_THRESH)
			वापस MAX_METRIC;

		rate = ewma_mesh_tx_rate_avg_पढ़ो(&sta->mesh->tx_rate_avg);
		अगर (WARN_ON(!rate))
			वापस MAX_METRIC;

		err = (fail_avg << ARITH_SHIFT) / 100;
	पूर्ण

	/* bitrate is in units of 100 Kbps, जबतक we need rate in units of
	 * 1Mbps. This will be corrected on tx_समय computation.
	 */
	tx_समय = (device_स्थिरant + 10 * test_frame_len / rate);
	estimated_retx = ((1 << (2 * ARITH_SHIFT)) / (s_unit - err));
	result = ((u64)tx_समय * estimated_retx) >> (2 * ARITH_SHIFT);
	वापस (u32)result;
पूर्ण

/**
 * hwmp_route_info_get - Update routing info to originator and transmitter
 *
 * @sdata: local mesh subअगर
 * @mgmt: mesh management frame
 * @hwmp_ie: hwmp inक्रमmation element (PREP or PREQ)
 * @action: type of hwmp ie
 *
 * This function updates the path routing inक्रमmation to the originator and the
 * transmitter of a HWMP PREQ or PREP frame.
 *
 * Returns: metric to frame originator or 0 अगर the frame should not be further
 * processed
 *
 * Notes: this function is the only place (besides user-provided info) where
 * path routing inक्रमmation is updated.
 */
अटल u32 hwmp_route_info_get(काष्ठा ieee80211_sub_अगर_data *sdata,
			       काष्ठा ieee80211_mgmt *mgmt,
			       स्थिर u8 *hwmp_ie, क्रमागत mpath_frame_type action)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा mesh_path *mpath;
	काष्ठा sta_info *sta;
	bool fresh_info;
	स्थिर u8 *orig_addr, *ta;
	u32 orig_sn, orig_metric;
	अचिन्हित दीर्घ orig_lअगरeसमय, exp_समय;
	u32 last_hop_metric, new_metric;
	bool process = true;
	u8 hopcount;

	rcu_पढ़ो_lock();
	sta = sta_info_get(sdata, mgmt->sa);
	अगर (!sta) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	last_hop_metric = airसमय_link_metric_get(local, sta);
	/* Update and check originator routing info */
	fresh_info = true;

	चयन (action) अणु
	हाल MPATH_PREQ:
		orig_addr = PREQ_IE_ORIG_ADDR(hwmp_ie);
		orig_sn = PREQ_IE_ORIG_SN(hwmp_ie);
		orig_lअगरeसमय = PREQ_IE_LIFETIME(hwmp_ie);
		orig_metric = PREQ_IE_METRIC(hwmp_ie);
		hopcount = PREQ_IE_HOPCOUNT(hwmp_ie) + 1;
		अवरोध;
	हाल MPATH_PREP:
		/* Originator here refers to the MP that was the target in the
		 * Path Request. We भागert from the nomenclature in the draft
		 * so that we can easily use a single function to gather path
		 * inक्रमmation from both PREQ and PREP frames.
		 */
		orig_addr = PREP_IE_TARGET_ADDR(hwmp_ie);
		orig_sn = PREP_IE_TARGET_SN(hwmp_ie);
		orig_lअगरeसमय = PREP_IE_LIFETIME(hwmp_ie);
		orig_metric = PREP_IE_METRIC(hwmp_ie);
		hopcount = PREP_IE_HOPCOUNT(hwmp_ie) + 1;
		अवरोध;
	शेष:
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण
	new_metric = orig_metric + last_hop_metric;
	अगर (new_metric < orig_metric)
		new_metric = MAX_METRIC;
	exp_समय = TU_TO_EXP_TIME(orig_lअगरeसमय);

	अगर (ether_addr_equal(orig_addr, sdata->vअगर.addr)) अणु
		/* This MP is the originator, we are not पूर्णांकerested in this
		 * frame, except क्रम updating transmitter's path info.
		 */
		process = false;
		fresh_info = false;
	पूर्ण अन्यथा अणु
		mpath = mesh_path_lookup(sdata, orig_addr);
		अगर (mpath) अणु
			spin_lock_bh(&mpath->state_lock);
			अगर (mpath->flags & MESH_PATH_FIXED)
				fresh_info = false;
			अन्यथा अगर ((mpath->flags & MESH_PATH_ACTIVE) &&
			    (mpath->flags & MESH_PATH_SN_VALID)) अणु
				अगर (SN_GT(mpath->sn, orig_sn) ||
				    (mpath->sn == orig_sn &&
				     (rcu_access_poपूर्णांकer(mpath->next_hop) !=
						      sta ?
					      mult_frac(new_metric, 10, 9) :
					      new_metric) >= mpath->metric)) अणु
					process = false;
					fresh_info = false;
				पूर्ण
			पूर्ण अन्यथा अगर (!(mpath->flags & MESH_PATH_ACTIVE)) अणु
				bool have_sn, newer_sn, bounced;

				have_sn = mpath->flags & MESH_PATH_SN_VALID;
				newer_sn = have_sn && SN_GT(orig_sn, mpath->sn);
				bounced = have_sn &&
					  (SN_DELTA(orig_sn, mpath->sn) >
							MAX_SANE_SN_DELTA);

				अगर (!have_sn || newer_sn) अणु
					/* अगर SN is newer than what we had
					 * then we can take it */;
				पूर्ण अन्यथा अगर (bounced) अणु
					/* अगर SN is way dअगरferent than what
					 * we had then assume the other side
					 * rebooted or restarted */;
				पूर्ण अन्यथा अणु
					process = false;
					fresh_info = false;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			mpath = mesh_path_add(sdata, orig_addr);
			अगर (IS_ERR(mpath)) अणु
				rcu_पढ़ो_unlock();
				वापस 0;
			पूर्ण
			spin_lock_bh(&mpath->state_lock);
		पूर्ण

		अगर (fresh_info) अणु
			अगर (rcu_access_poपूर्णांकer(mpath->next_hop) != sta)
				mpath->path_change_count++;
			mesh_path_assign_nexthop(mpath, sta);
			mpath->flags |= MESH_PATH_SN_VALID;
			mpath->metric = new_metric;
			mpath->sn = orig_sn;
			mpath->exp_समय = समय_after(mpath->exp_समय, exp_समय)
					  ?  mpath->exp_समय : exp_समय;
			mpath->hop_count = hopcount;
			mesh_path_activate(mpath);
			spin_unlock_bh(&mpath->state_lock);
			ewma_mesh_fail_avg_init(&sta->mesh->fail_avg);
			/* init it at a low value - 0 start is tricky */
			ewma_mesh_fail_avg_add(&sta->mesh->fail_avg, 1);
			mesh_path_tx_pending(mpath);
			/* draft says preq_id should be saved to, but there करोes
			 * not seem to be any use क्रम it, skipping by now
			 */
		पूर्ण अन्यथा
			spin_unlock_bh(&mpath->state_lock);
	पूर्ण

	/* Update and check transmitter routing info */
	ta = mgmt->sa;
	अगर (ether_addr_equal(orig_addr, ta))
		fresh_info = false;
	अन्यथा अणु
		fresh_info = true;

		mpath = mesh_path_lookup(sdata, ta);
		अगर (mpath) अणु
			spin_lock_bh(&mpath->state_lock);
			अगर ((mpath->flags & MESH_PATH_FIXED) ||
			    ((mpath->flags & MESH_PATH_ACTIVE) &&
			     ((rcu_access_poपूर्णांकer(mpath->next_hop) != sta ?
				       mult_frac(last_hop_metric, 10, 9) :
				       last_hop_metric) > mpath->metric)))
				fresh_info = false;
		पूर्ण अन्यथा अणु
			mpath = mesh_path_add(sdata, ta);
			अगर (IS_ERR(mpath)) अणु
				rcu_पढ़ो_unlock();
				वापस 0;
			पूर्ण
			spin_lock_bh(&mpath->state_lock);
		पूर्ण

		अगर (fresh_info) अणु
			अगर (rcu_access_poपूर्णांकer(mpath->next_hop) != sta)
				mpath->path_change_count++;
			mesh_path_assign_nexthop(mpath, sta);
			mpath->metric = last_hop_metric;
			mpath->exp_समय = समय_after(mpath->exp_समय, exp_समय)
					  ?  mpath->exp_समय : exp_समय;
			mpath->hop_count = 1;
			mesh_path_activate(mpath);
			spin_unlock_bh(&mpath->state_lock);
			ewma_mesh_fail_avg_init(&sta->mesh->fail_avg);
			/* init it at a low value - 0 start is tricky */
			ewma_mesh_fail_avg_add(&sta->mesh->fail_avg, 1);
			mesh_path_tx_pending(mpath);
		पूर्ण अन्यथा
			spin_unlock_bh(&mpath->state_lock);
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस process ? new_metric : 0;
पूर्ण

अटल व्योम hwmp_preq_frame_process(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा ieee80211_mgmt *mgmt,
				    स्थिर u8 *preq_elem, u32 orig_metric)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा mesh_path *mpath = शून्य;
	स्थिर u8 *target_addr, *orig_addr;
	स्थिर u8 *da;
	u8 target_flags, ttl, flags;
	u32 orig_sn, target_sn, lअगरeसमय, target_metric = 0;
	bool reply = false;
	bool क्रमward = true;
	bool root_is_gate;

	/* Update target SN, अगर present */
	target_addr = PREQ_IE_TARGET_ADDR(preq_elem);
	orig_addr = PREQ_IE_ORIG_ADDR(preq_elem);
	target_sn = PREQ_IE_TARGET_SN(preq_elem);
	orig_sn = PREQ_IE_ORIG_SN(preq_elem);
	target_flags = PREQ_IE_TARGET_F(preq_elem);
	/* Proactive PREQ gate announcements */
	flags = PREQ_IE_FLAGS(preq_elem);
	root_is_gate = !!(flags & RANN_FLAG_IS_GATE);

	mhwmp_dbg(sdata, "received PREQ from %pM\n", orig_addr);

	अगर (ether_addr_equal(target_addr, sdata->vअगर.addr)) अणु
		mhwmp_dbg(sdata, "PREQ is for us\n");
		क्रमward = false;
		reply = true;
		target_metric = 0;

		अगर (SN_GT(target_sn, अगरmsh->sn))
			अगरmsh->sn = target_sn;

		अगर (समय_after(jअगरfies, अगरmsh->last_sn_update +
					net_traversal_jअगरfies(sdata)) ||
		    समय_beक्रमe(jअगरfies, अगरmsh->last_sn_update)) अणु
			++अगरmsh->sn;
			अगरmsh->last_sn_update = jअगरfies;
		पूर्ण
		target_sn = अगरmsh->sn;
	पूर्ण अन्यथा अगर (is_broadcast_ether_addr(target_addr) &&
		   (target_flags & IEEE80211_PREQ_TO_FLAG)) अणु
		rcu_पढ़ो_lock();
		mpath = mesh_path_lookup(sdata, orig_addr);
		अगर (mpath) अणु
			अगर (flags & IEEE80211_PREQ_PROACTIVE_PREP_FLAG) अणु
				reply = true;
				target_addr = sdata->vअगर.addr;
				target_sn = ++अगरmsh->sn;
				target_metric = 0;
				अगरmsh->last_sn_update = jअगरfies;
			पूर्ण
			अगर (root_is_gate)
				mesh_path_add_gate(mpath);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_lock();
		mpath = mesh_path_lookup(sdata, target_addr);
		अगर (mpath) अणु
			अगर ((!(mpath->flags & MESH_PATH_SN_VALID)) ||
					SN_LT(mpath->sn, target_sn)) अणु
				mpath->sn = target_sn;
				mpath->flags |= MESH_PATH_SN_VALID;
			पूर्ण अन्यथा अगर ((!(target_flags & IEEE80211_PREQ_TO_FLAG)) &&
					(mpath->flags & MESH_PATH_ACTIVE)) अणु
				reply = true;
				target_metric = mpath->metric;
				target_sn = mpath->sn;
				/* Case E2 of sec 13.10.9.3 IEEE 802.11-2012*/
				target_flags |= IEEE80211_PREQ_TO_FLAG;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (reply) अणु
		lअगरeसमय = PREQ_IE_LIFETIME(preq_elem);
		ttl = अगरmsh->mshcfg.element_ttl;
		अगर (ttl != 0) अणु
			mhwmp_dbg(sdata, "replying to the PREQ\n");
			mesh_path_sel_frame_tx(MPATH_PREP, 0, orig_addr,
					       orig_sn, 0, target_addr,
					       target_sn, mgmt->sa, 0, ttl,
					       lअगरeसमय, target_metric, 0,
					       sdata);
		पूर्ण अन्यथा अणु
			अगरmsh->mshstats.dropped_frames_ttl++;
		पूर्ण
	पूर्ण

	अगर (क्रमward && अगरmsh->mshcfg.करोt11MeshForwarding) अणु
		u32 preq_id;
		u8 hopcount;

		ttl = PREQ_IE_TTL(preq_elem);
		lअगरeसमय = PREQ_IE_LIFETIME(preq_elem);
		अगर (ttl <= 1) अणु
			अगरmsh->mshstats.dropped_frames_ttl++;
			वापस;
		पूर्ण
		mhwmp_dbg(sdata, "forwarding the PREQ from %pM\n", orig_addr);
		--ttl;
		preq_id = PREQ_IE_PREQ_ID(preq_elem);
		hopcount = PREQ_IE_HOPCOUNT(preq_elem) + 1;
		da = (mpath && mpath->is_root) ?
			mpath->rann_snd_addr : broadcast_addr;

		अगर (flags & IEEE80211_PREQ_PROACTIVE_PREP_FLAG) अणु
			target_addr = PREQ_IE_TARGET_ADDR(preq_elem);
			target_sn = PREQ_IE_TARGET_SN(preq_elem);
		पूर्ण

		mesh_path_sel_frame_tx(MPATH_PREQ, flags, orig_addr,
				       orig_sn, target_flags, target_addr,
				       target_sn, da, hopcount, ttl, lअगरeसमय,
				       orig_metric, preq_id, sdata);
		अगर (!is_multicast_ether_addr(da))
			अगरmsh->mshstats.fwded_unicast++;
		अन्यथा
			अगरmsh->mshstats.fwded_mcast++;
		अगरmsh->mshstats.fwded_frames++;
	पूर्ण
पूर्ण


अटल अंतरभूत काष्ठा sta_info *
next_hop_deref_रक्षित(काष्ठा mesh_path *mpath)
अणु
	वापस rcu_dereference_रक्षित(mpath->next_hop,
					 lockdep_is_held(&mpath->state_lock));
पूर्ण


अटल व्योम hwmp_prep_frame_process(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा ieee80211_mgmt *mgmt,
				    स्थिर u8 *prep_elem, u32 metric)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा mesh_path *mpath;
	स्थिर u8 *target_addr, *orig_addr;
	u8 ttl, hopcount, flags;
	u8 next_hop[ETH_ALEN];
	u32 target_sn, orig_sn, lअगरeसमय;

	mhwmp_dbg(sdata, "received PREP from %pM\n",
		  PREP_IE_TARGET_ADDR(prep_elem));

	orig_addr = PREP_IE_ORIG_ADDR(prep_elem);
	अगर (ether_addr_equal(orig_addr, sdata->vअगर.addr))
		/* destination, no क्रमwarding required */
		वापस;

	अगर (!अगरmsh->mshcfg.करोt11MeshForwarding)
		वापस;

	ttl = PREP_IE_TTL(prep_elem);
	अगर (ttl <= 1) अणु
		sdata->u.mesh.mshstats.dropped_frames_ttl++;
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	mpath = mesh_path_lookup(sdata, orig_addr);
	अगर (mpath)
		spin_lock_bh(&mpath->state_lock);
	अन्यथा
		जाओ fail;
	अगर (!(mpath->flags & MESH_PATH_ACTIVE)) अणु
		spin_unlock_bh(&mpath->state_lock);
		जाओ fail;
	पूर्ण
	स_नकल(next_hop, next_hop_deref_रक्षित(mpath)->sta.addr, ETH_ALEN);
	spin_unlock_bh(&mpath->state_lock);
	--ttl;
	flags = PREP_IE_FLAGS(prep_elem);
	lअगरeसमय = PREP_IE_LIFETIME(prep_elem);
	hopcount = PREP_IE_HOPCOUNT(prep_elem) + 1;
	target_addr = PREP_IE_TARGET_ADDR(prep_elem);
	target_sn = PREP_IE_TARGET_SN(prep_elem);
	orig_sn = PREP_IE_ORIG_SN(prep_elem);

	mesh_path_sel_frame_tx(MPATH_PREP, flags, orig_addr, orig_sn, 0,
			       target_addr, target_sn, next_hop, hopcount,
			       ttl, lअगरeसमय, metric, 0, sdata);
	rcu_पढ़ो_unlock();

	sdata->u.mesh.mshstats.fwded_unicast++;
	sdata->u.mesh.mshstats.fwded_frames++;
	वापस;

fail:
	rcu_पढ़ो_unlock();
	sdata->u.mesh.mshstats.dropped_frames_no_route++;
पूर्ण

अटल व्योम hwmp_perr_frame_process(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा ieee80211_mgmt *mgmt,
				    स्थिर u8 *perr_elem)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा mesh_path *mpath;
	u8 ttl;
	स्थिर u8 *ta, *target_addr;
	u32 target_sn;
	u16 target_rcode;

	ta = mgmt->sa;
	ttl = PERR_IE_TTL(perr_elem);
	अगर (ttl <= 1) अणु
		अगरmsh->mshstats.dropped_frames_ttl++;
		वापस;
	पूर्ण
	ttl--;
	target_addr = PERR_IE_TARGET_ADDR(perr_elem);
	target_sn = PERR_IE_TARGET_SN(perr_elem);
	target_rcode = PERR_IE_TARGET_RCODE(perr_elem);

	rcu_पढ़ो_lock();
	mpath = mesh_path_lookup(sdata, target_addr);
	अगर (mpath) अणु
		काष्ठा sta_info *sta;

		spin_lock_bh(&mpath->state_lock);
		sta = next_hop_deref_रक्षित(mpath);
		अगर (mpath->flags & MESH_PATH_ACTIVE &&
		    ether_addr_equal(ta, sta->sta.addr) &&
		    !(mpath->flags & MESH_PATH_FIXED) &&
		    (!(mpath->flags & MESH_PATH_SN_VALID) ||
		    SN_GT(target_sn, mpath->sn)  || target_sn == 0)) अणु
			mpath->flags &= ~MESH_PATH_ACTIVE;
			अगर (target_sn != 0)
				mpath->sn = target_sn;
			अन्यथा
				mpath->sn += 1;
			spin_unlock_bh(&mpath->state_lock);
			अगर (!अगरmsh->mshcfg.करोt11MeshForwarding)
				जाओ endperr;
			mesh_path_error_tx(sdata, ttl, target_addr,
					   target_sn, target_rcode,
					   broadcast_addr);
		पूर्ण अन्यथा
			spin_unlock_bh(&mpath->state_lock);
	पूर्ण
endperr:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम hwmp_rann_frame_process(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा ieee80211_mgmt *mgmt,
				    स्थिर काष्ठा ieee80211_rann_ie *rann)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	काष्ठा mesh_path *mpath;
	u8 ttl, flags, hopcount;
	स्थिर u8 *orig_addr;
	u32 orig_sn, new_metric, orig_metric, last_hop_metric, पूर्णांकerval;
	bool root_is_gate;

	ttl = rann->rann_ttl;
	flags = rann->rann_flags;
	root_is_gate = !!(flags & RANN_FLAG_IS_GATE);
	orig_addr = rann->rann_addr;
	orig_sn = le32_to_cpu(rann->rann_seq);
	पूर्णांकerval = le32_to_cpu(rann->rann_पूर्णांकerval);
	hopcount = rann->rann_hopcount;
	hopcount++;
	orig_metric = le32_to_cpu(rann->rann_metric);

	/*  Ignore our own RANNs */
	अगर (ether_addr_equal(orig_addr, sdata->vअगर.addr))
		वापस;

	mhwmp_dbg(sdata,
		  "received RANN from %pM via neighbour %pM (is_gate=%d)\n",
		  orig_addr, mgmt->sa, root_is_gate);

	rcu_पढ़ो_lock();
	sta = sta_info_get(sdata, mgmt->sa);
	अगर (!sta) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	last_hop_metric = airसमय_link_metric_get(local, sta);
	new_metric = orig_metric + last_hop_metric;
	अगर (new_metric < orig_metric)
		new_metric = MAX_METRIC;

	mpath = mesh_path_lookup(sdata, orig_addr);
	अगर (!mpath) अणु
		mpath = mesh_path_add(sdata, orig_addr);
		अगर (IS_ERR(mpath)) अणु
			rcu_पढ़ो_unlock();
			sdata->u.mesh.mshstats.dropped_frames_no_route++;
			वापस;
		पूर्ण
	पूर्ण

	अगर (!(SN_LT(mpath->sn, orig_sn)) &&
	    !(mpath->sn == orig_sn && new_metric < mpath->rann_metric)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	अगर ((!(mpath->flags & (MESH_PATH_ACTIVE | MESH_PATH_RESOLVING)) ||
	     (समय_after(jअगरfies, mpath->last_preq_to_root +
				  root_path_confirmation_jअगरfies(sdata)) ||
	     समय_beक्रमe(jअगरfies, mpath->last_preq_to_root))) &&
	     !(mpath->flags & MESH_PATH_FIXED) && (ttl != 0)) अणु
		mhwmp_dbg(sdata,
			  "time to refresh root mpath %pM\n",
			  orig_addr);
		mesh_queue_preq(mpath, PREQ_Q_F_START | PREQ_Q_F_REFRESH);
		mpath->last_preq_to_root = jअगरfies;
	पूर्ण

	mpath->sn = orig_sn;
	mpath->rann_metric = new_metric;
	mpath->is_root = true;
	/* Recording RANNs sender address to send inभागidually
	 * addressed PREQs destined क्रम root mesh STA */
	स_नकल(mpath->rann_snd_addr, mgmt->sa, ETH_ALEN);

	अगर (root_is_gate)
		mesh_path_add_gate(mpath);

	अगर (ttl <= 1) अणु
		अगरmsh->mshstats.dropped_frames_ttl++;
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	ttl--;

	अगर (अगरmsh->mshcfg.करोt11MeshForwarding) अणु
		mesh_path_sel_frame_tx(MPATH_RANN, flags, orig_addr,
				       orig_sn, 0, शून्य, 0, broadcast_addr,
				       hopcount, ttl, पूर्णांकerval,
				       new_metric, 0, sdata);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण


व्योम mesh_rx_path_sel_frame(काष्ठा ieee80211_sub_अगर_data *sdata,
			    काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len)
अणु
	काष्ठा ieee802_11_elems elems;
	माप_प्रकार baselen;
	u32 path_metric;
	काष्ठा sta_info *sta;

	/* need action_code */
	अगर (len < IEEE80211_MIN_ACTION_SIZE + 1)
		वापस;

	rcu_पढ़ो_lock();
	sta = sta_info_get(sdata, mgmt->sa);
	अगर (!sta || sta->mesh->plink_state != NL80211_PLINK_ESTAB) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	rcu_पढ़ो_unlock();

	baselen = (u8 *) mgmt->u.action.u.mesh_action.variable - (u8 *) mgmt;
	ieee802_11_parse_elems(mgmt->u.action.u.mesh_action.variable,
			       len - baselen, false, &elems, mgmt->bssid, शून्य);

	अगर (elems.preq) अणु
		अगर (elems.preq_len != 37)
			/* Right now we support just 1 destination and no AE */
			वापस;
		path_metric = hwmp_route_info_get(sdata, mgmt, elems.preq,
						  MPATH_PREQ);
		अगर (path_metric)
			hwmp_preq_frame_process(sdata, mgmt, elems.preq,
						path_metric);
	पूर्ण
	अगर (elems.prep) अणु
		अगर (elems.prep_len != 31)
			/* Right now we support no AE */
			वापस;
		path_metric = hwmp_route_info_get(sdata, mgmt, elems.prep,
						  MPATH_PREP);
		अगर (path_metric)
			hwmp_prep_frame_process(sdata, mgmt, elems.prep,
						path_metric);
	पूर्ण
	अगर (elems.perr) अणु
		अगर (elems.perr_len != 15)
			/* Right now we support only one destination per PERR */
			वापस;
		hwmp_perr_frame_process(sdata, mgmt, elems.perr);
	पूर्ण
	अगर (elems.rann)
		hwmp_rann_frame_process(sdata, mgmt, elems.rann);
पूर्ण

/**
 * mesh_queue_preq - queue a PREQ to a given destination
 *
 * @mpath: mesh path to discover
 * @flags: special attributes of the PREQ to be sent
 *
 * Locking: the function must be called from within a rcu पढ़ो lock block.
 *
 */
अटल व्योम mesh_queue_preq(काष्ठा mesh_path *mpath, u8 flags)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = mpath->sdata;
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा mesh_preq_queue *preq_node;

	preq_node = kदो_स्मृति(माप(काष्ठा mesh_preq_queue), GFP_ATOMIC);
	अगर (!preq_node) अणु
		mhwmp_dbg(sdata, "could not allocate PREQ node\n");
		वापस;
	पूर्ण

	spin_lock_bh(&अगरmsh->mesh_preq_queue_lock);
	अगर (अगरmsh->preq_queue_len == MAX_PREQ_QUEUE_LEN) अणु
		spin_unlock_bh(&अगरmsh->mesh_preq_queue_lock);
		kमुक्त(preq_node);
		अगर (prपूर्णांकk_ratelimit())
			mhwmp_dbg(sdata, "PREQ node queue full\n");
		वापस;
	पूर्ण

	spin_lock(&mpath->state_lock);
	अगर (mpath->flags & MESH_PATH_REQ_QUEUED) अणु
		spin_unlock(&mpath->state_lock);
		spin_unlock_bh(&अगरmsh->mesh_preq_queue_lock);
		kमुक्त(preq_node);
		वापस;
	पूर्ण

	स_नकल(preq_node->dst, mpath->dst, ETH_ALEN);
	preq_node->flags = flags;

	mpath->flags |= MESH_PATH_REQ_QUEUED;
	spin_unlock(&mpath->state_lock);

	list_add_tail(&preq_node->list, &अगरmsh->preq_queue.list);
	++अगरmsh->preq_queue_len;
	spin_unlock_bh(&अगरmsh->mesh_preq_queue_lock);

	अगर (समय_after(jअगरfies, अगरmsh->last_preq + min_preq_पूर्णांक_jअगरf(sdata)))
		ieee80211_queue_work(&sdata->local->hw, &sdata->work);

	अन्यथा अगर (समय_beक्रमe(jअगरfies, अगरmsh->last_preq)) अणु
		/* aव्योम दीर्घ रुको अगर did not send preqs क्रम a दीर्घ समय
		 * and jअगरfies wrapped around
		 */
		अगरmsh->last_preq = jअगरfies - min_preq_पूर्णांक_jअगरf(sdata) - 1;
		ieee80211_queue_work(&sdata->local->hw, &sdata->work);
	पूर्ण अन्यथा
		mod_समयr(&अगरmsh->mesh_path_समयr, अगरmsh->last_preq +
						min_preq_पूर्णांक_jअगरf(sdata));
पूर्ण

/**
 * mesh_path_start_discovery - launch a path discovery from the PREQ queue
 *
 * @sdata: local mesh subअगर
 */
व्योम mesh_path_start_discovery(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा mesh_preq_queue *preq_node;
	काष्ठा mesh_path *mpath;
	u8 ttl, target_flags = 0;
	स्थिर u8 *da;
	u32 lअगरeसमय;

	spin_lock_bh(&अगरmsh->mesh_preq_queue_lock);
	अगर (!अगरmsh->preq_queue_len ||
		समय_beक्रमe(jअगरfies, अगरmsh->last_preq +
				min_preq_पूर्णांक_jअगरf(sdata))) अणु
		spin_unlock_bh(&अगरmsh->mesh_preq_queue_lock);
		वापस;
	पूर्ण

	preq_node = list_first_entry(&अगरmsh->preq_queue.list,
			काष्ठा mesh_preq_queue, list);
	list_del(&preq_node->list);
	--अगरmsh->preq_queue_len;
	spin_unlock_bh(&अगरmsh->mesh_preq_queue_lock);

	rcu_पढ़ो_lock();
	mpath = mesh_path_lookup(sdata, preq_node->dst);
	अगर (!mpath)
		जाओ enddiscovery;

	spin_lock_bh(&mpath->state_lock);
	अगर (mpath->flags & (MESH_PATH_DELETED | MESH_PATH_FIXED)) अणु
		spin_unlock_bh(&mpath->state_lock);
		जाओ enddiscovery;
	पूर्ण
	mpath->flags &= ~MESH_PATH_REQ_QUEUED;
	अगर (preq_node->flags & PREQ_Q_F_START) अणु
		अगर (mpath->flags & MESH_PATH_RESOLVING) अणु
			spin_unlock_bh(&mpath->state_lock);
			जाओ enddiscovery;
		पूर्ण अन्यथा अणु
			mpath->flags &= ~MESH_PATH_RESOLVED;
			mpath->flags |= MESH_PATH_RESOLVING;
			mpath->discovery_retries = 0;
			mpath->discovery_समयout = disc_समयout_jअगरf(sdata);
		पूर्ण
	पूर्ण अन्यथा अगर (!(mpath->flags & MESH_PATH_RESOLVING) ||
			mpath->flags & MESH_PATH_RESOLVED) अणु
		mpath->flags &= ~MESH_PATH_RESOLVING;
		spin_unlock_bh(&mpath->state_lock);
		जाओ enddiscovery;
	पूर्ण

	अगरmsh->last_preq = jअगरfies;

	अगर (समय_after(jअगरfies, अगरmsh->last_sn_update +
				net_traversal_jअगरfies(sdata)) ||
	    समय_beक्रमe(jअगरfies, अगरmsh->last_sn_update)) अणु
		++अगरmsh->sn;
		sdata->u.mesh.last_sn_update = jअगरfies;
	पूर्ण
	lअगरeसमय = शेष_lअगरeसमय(sdata);
	ttl = sdata->u.mesh.mshcfg.element_ttl;
	अगर (ttl == 0) अणु
		sdata->u.mesh.mshstats.dropped_frames_ttl++;
		spin_unlock_bh(&mpath->state_lock);
		जाओ enddiscovery;
	पूर्ण

	अगर (preq_node->flags & PREQ_Q_F_REFRESH)
		target_flags |= IEEE80211_PREQ_TO_FLAG;
	अन्यथा
		target_flags &= ~IEEE80211_PREQ_TO_FLAG;

	spin_unlock_bh(&mpath->state_lock);
	da = (mpath->is_root) ? mpath->rann_snd_addr : broadcast_addr;
	mesh_path_sel_frame_tx(MPATH_PREQ, 0, sdata->vअगर.addr, अगरmsh->sn,
			       target_flags, mpath->dst, mpath->sn, da, 0,
			       ttl, lअगरeसमय, 0, अगरmsh->preq_id++, sdata);

	spin_lock_bh(&mpath->state_lock);
	अगर (!(mpath->flags & MESH_PATH_DELETED))
		mod_समयr(&mpath->समयr, jअगरfies + mpath->discovery_समयout);
	spin_unlock_bh(&mpath->state_lock);

enddiscovery:
	rcu_पढ़ो_unlock();
	kमुक्त(preq_node);
पूर्ण

/**
 * mesh_nexthop_resolve - lookup next hop; conditionally start path discovery
 *
 * @skb: 802.11 frame to be sent
 * @sdata: network subअगर the frame will be sent through
 *
 * Lookup next hop क्रम given skb and start path discovery अगर no
 * क्रमwarding inक्रमmation is found.
 *
 * Returns: 0 अगर the next hop was found and -ENOENT अगर the frame was queued.
 * skb is मुक्तed here अगर no mpath could be allocated.
 */
पूर्णांक mesh_nexthop_resolve(काष्ठा ieee80211_sub_अगर_data *sdata,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा mesh_path *mpath;
	काष्ठा sk_buff *skb_to_मुक्त = शून्य;
	u8 *target_addr = hdr->addr3;

	/* Nulls are only sent to peers क्रम PS and should be pre-addressed */
	अगर (ieee80211_is_qos_nullfunc(hdr->frame_control))
		वापस 0;

	/* Allow injected packets to bypass mesh routing */
	अगर (info->control.flags & IEEE80211_TX_CTRL_SKIP_MPATH_LOOKUP)
		वापस 0;

	अगर (!mesh_nexthop_lookup(sdata, skb))
		वापस 0;

	/* no nexthop found, start resolving */
	mpath = mesh_path_lookup(sdata, target_addr);
	अगर (!mpath) अणु
		mpath = mesh_path_add(sdata, target_addr);
		अगर (IS_ERR(mpath)) अणु
			mesh_path_discard_frame(sdata, skb);
			वापस PTR_ERR(mpath);
		पूर्ण
	पूर्ण

	अगर (!(mpath->flags & MESH_PATH_RESOLVING) &&
	    mesh_path_sel_is_hwmp(sdata))
		mesh_queue_preq(mpath, PREQ_Q_F_START);

	अगर (skb_queue_len(&mpath->frame_queue) >= MESH_FRAME_QUEUE_LEN)
		skb_to_मुक्त = skb_dequeue(&mpath->frame_queue);

	info->control.flags |= IEEE80211_TX_INTCFL_NEED_TXPROCESSING;
	ieee80211_set_qos_hdr(sdata, skb);
	skb_queue_tail(&mpath->frame_queue, skb);
	अगर (skb_to_मुक्त)
		mesh_path_discard_frame(sdata, skb_to_मुक्त);

	वापस -ENOENT;
पूर्ण

/**
 * mesh_nexthop_lookup_nolearn - try to set next hop without path discovery
 * @skb: 802.11 frame to be sent
 * @sdata: network subअगर the frame will be sent through
 *
 * Check अगर the meshDA (addr3) of a unicast frame is a direct neighbor.
 * And अगर so, set the RA (addr1) to it to transmit to this node directly,
 * aव्योमing PREQ/PREP path discovery.
 *
 * Returns: 0 अगर the next hop was found and -ENOENT otherwise.
 */
अटल पूर्णांक mesh_nexthop_lookup_nolearn(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा sta_info *sta;

	अगर (is_multicast_ether_addr(hdr->addr1))
		वापस -ENOENT;

	rcu_पढ़ो_lock();
	sta = sta_info_get(sdata, hdr->addr3);

	अगर (!sta || sta->mesh->plink_state != NL80211_PLINK_ESTAB) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण
	rcu_पढ़ो_unlock();

	स_नकल(hdr->addr1, hdr->addr3, ETH_ALEN);
	स_नकल(hdr->addr2, sdata->vअगर.addr, ETH_ALEN);
	वापस 0;
पूर्ण

/**
 * mesh_nexthop_lookup - put the appropriate next hop on a mesh frame. Calling
 * this function is considered "using" the associated mpath, so preempt a path
 * refresh अगर this mpath expires soon.
 *
 * @skb: 802.11 frame to be sent
 * @sdata: network subअगर the frame will be sent through
 *
 * Returns: 0 अगर the next hop was found. Nonzero otherwise.
 */
पूर्णांक mesh_nexthop_lookup(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा mesh_path *mpath;
	काष्ठा sta_info *next_hop;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	u8 *target_addr = hdr->addr3;

	अगर (अगरmsh->mshcfg.करोt11MeshNolearn &&
	    !mesh_nexthop_lookup_nolearn(sdata, skb))
		वापस 0;

	mpath = mesh_path_lookup(sdata, target_addr);
	अगर (!mpath || !(mpath->flags & MESH_PATH_ACTIVE))
		वापस -ENOENT;

	अगर (समय_after(jअगरfies,
		       mpath->exp_समय -
		       msecs_to_jअगरfies(sdata->u.mesh.mshcfg.path_refresh_समय)) &&
	    ether_addr_equal(sdata->vअगर.addr, hdr->addr4) &&
	    !(mpath->flags & MESH_PATH_RESOLVING) &&
	    !(mpath->flags & MESH_PATH_FIXED))
		mesh_queue_preq(mpath, PREQ_Q_F_START | PREQ_Q_F_REFRESH);

	next_hop = rcu_dereference(mpath->next_hop);
	अगर (next_hop) अणु
		स_नकल(hdr->addr1, next_hop->sta.addr, ETH_ALEN);
		स_नकल(hdr->addr2, sdata->vअगर.addr, ETH_ALEN);
		ieee80211_mps_set_frame_flags(sdata, next_hop, hdr);
		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

व्योम mesh_path_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा mesh_path *mpath = from_समयr(mpath, t, समयr);
	काष्ठा ieee80211_sub_अगर_data *sdata = mpath->sdata;
	पूर्णांक ret;

	अगर (sdata->local->quiescing)
		वापस;

	spin_lock_bh(&mpath->state_lock);
	अगर (mpath->flags & MESH_PATH_RESOLVED ||
			(!(mpath->flags & MESH_PATH_RESOLVING))) अणु
		mpath->flags &= ~(MESH_PATH_RESOLVING | MESH_PATH_RESOLVED);
		spin_unlock_bh(&mpath->state_lock);
	पूर्ण अन्यथा अगर (mpath->discovery_retries < max_preq_retries(sdata)) अणु
		++mpath->discovery_retries;
		mpath->discovery_समयout *= 2;
		mpath->flags &= ~MESH_PATH_REQ_QUEUED;
		spin_unlock_bh(&mpath->state_lock);
		mesh_queue_preq(mpath, 0);
	पूर्ण अन्यथा अणु
		mpath->flags &= ~(MESH_PATH_RESOLVING |
				  MESH_PATH_RESOLVED |
				  MESH_PATH_REQ_QUEUED);
		mpath->exp_समय = jअगरfies;
		spin_unlock_bh(&mpath->state_lock);
		अगर (!mpath->is_gate && mesh_gate_num(sdata) > 0) अणु
			ret = mesh_path_send_to_gates(mpath);
			अगर (ret)
				mhwmp_dbg(sdata, "no gate was reachable\n");
		पूर्ण अन्यथा
			mesh_path_flush_pending(mpath);
	पूर्ण
पूर्ण

व्योम mesh_path_tx_root_frame(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	u32 पूर्णांकerval = अगरmsh->mshcfg.करोt11MeshHWMPRannInterval;
	u8 flags, target_flags = 0;

	flags = (अगरmsh->mshcfg.करोt11MeshGateAnnouncementProtocol)
			? RANN_FLAG_IS_GATE : 0;

	चयन (अगरmsh->mshcfg.करोt11MeshHWMPRootMode) अणु
	हाल IEEE80211_PROACTIVE_RANN:
		mesh_path_sel_frame_tx(MPATH_RANN, flags, sdata->vअगर.addr,
				       ++अगरmsh->sn, 0, शून्य, 0, broadcast_addr,
				       0, अगरmsh->mshcfg.element_ttl,
				       पूर्णांकerval, 0, 0, sdata);
		अवरोध;
	हाल IEEE80211_PROACTIVE_PREQ_WITH_PREP:
		flags |= IEEE80211_PREQ_PROACTIVE_PREP_FLAG;
		fallthrough;
	हाल IEEE80211_PROACTIVE_PREQ_NO_PREP:
		पूर्णांकerval = अगरmsh->mshcfg.करोt11MeshHWMPactivePathToRootTimeout;
		target_flags |= IEEE80211_PREQ_TO_FLAG |
				IEEE80211_PREQ_USN_FLAG;
		mesh_path_sel_frame_tx(MPATH_PREQ, flags, sdata->vअगर.addr,
				       ++अगरmsh->sn, target_flags,
				       (u8 *) broadcast_addr, 0, broadcast_addr,
				       0, अगरmsh->mshcfg.element_ttl, पूर्णांकerval,
				       0, अगरmsh->preq_id++, sdata);
		अवरोध;
	शेष:
		mhwmp_dbg(sdata, "Proactive mechanism not supported\n");
		वापस;
	पूर्ण
पूर्ण
