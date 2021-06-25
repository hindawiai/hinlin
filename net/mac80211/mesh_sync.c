<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2011-2012, Pavel Zubarev <pavel.zubarev@gmail.com>
 * Copyright 2011-2012, Marco Porsch <marco.porsch@s2005.tu-chemnitz.de>
 * Copyright 2011-2012, cozybit Inc.
 */

#समावेश "ieee80211_i.h"
#समावेश "mesh.h"
#समावेश "driver-ops.h"

/* This is not in the standard.  It represents a tolerable tsf drअगरt below
 * which we करो no TSF adjusपंचांगent.
 */
#घोषणा TOFFSET_MINIMUM_ADJUSTMENT 10

/* This is not in the standard. It is a margin added to the
 * Toffset setpoपूर्णांक to mitigate TSF overcorrection
 * पूर्णांकroduced by TSF adjusपंचांगent latency.
 */
#घोषणा TOFFSET_SET_MARGIN 20

/* This is not in the standard.  It represents the maximum Toffset jump above
 * which we'll invalidate the Toffset setpoपूर्णांक and choose a new setpoपूर्णांक.  This
 * could be, क्रम instance, in हाल a neighbor is restarted and its TSF counter
 * reset.
 */
#घोषणा TOFFSET_MAXIMUM_ADJUSTMENT 800		/* 0.8 ms */

काष्ठा sync_method अणु
	u8 method;
	काष्ठा ieee80211_mesh_sync_ops ops;
पूर्ण;

/**
 * mesh_peer_tbtt_adjusting - check अगर an mp is currently adjusting its TBTT
 *
 * @ie: inक्रमmation elements of a management frame from the mesh peer
 */
अटल bool mesh_peer_tbtt_adjusting(काष्ठा ieee802_11_elems *ie)
अणु
	वापस (ie->mesh_config->meshconf_cap &
			IEEE80211_MESHCONF_CAPAB_TBTT_ADJUSTING) != 0;
पूर्ण

व्योम mesh_sync_adjust_tsf(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	/* sdata->vअगर.bss_conf.beacon_पूर्णांक in 1024us units, 0.04% */
	u64 beacon_पूर्णांक_fraction = sdata->vअगर.bss_conf.beacon_पूर्णांक * 1024 / 2500;
	u64 tsf;
	u64 tsfdelta;

	spin_lock_bh(&अगरmsh->sync_offset_lock);
	अगर (अगरmsh->sync_offset_घड़ीdrअगरt_max < beacon_पूर्णांक_fraction) अणु
		msync_dbg(sdata, "TSF : max clockdrift=%lld; adjusting\n",
			  (दीर्घ दीर्घ) अगरmsh->sync_offset_घड़ीdrअगरt_max);
		tsfdelta = -अगरmsh->sync_offset_घड़ीdrअगरt_max;
		अगरmsh->sync_offset_घड़ीdrअगरt_max = 0;
	पूर्ण अन्यथा अणु
		msync_dbg(sdata, "TSF : max clockdrift=%lld; adjusting by %llu\n",
			  (दीर्घ दीर्घ) अगरmsh->sync_offset_घड़ीdrअगरt_max,
			  (अचिन्हित दीर्घ दीर्घ) beacon_पूर्णांक_fraction);
		tsfdelta = -beacon_पूर्णांक_fraction;
		अगरmsh->sync_offset_घड़ीdrअगरt_max -= beacon_पूर्णांक_fraction;
	पूर्ण
	spin_unlock_bh(&अगरmsh->sync_offset_lock);

	अगर (local->ops->offset_tsf) अणु
		drv_offset_tsf(local, sdata, tsfdelta);
	पूर्ण अन्यथा अणु
		tsf = drv_get_tsf(local, sdata);
		अगर (tsf != -1ULL)
			drv_set_tsf(local, sdata, tsf + tsfdelta);
	पूर्ण
पूर्ण

अटल व्योम mesh_sync_offset_rx_bcn_presp(काष्ठा ieee80211_sub_अगर_data *sdata,
				   u16 stype,
				   काष्ठा ieee80211_mgmt *mgmt,
				   काष्ठा ieee802_11_elems *elems,
				   काष्ठा ieee80211_rx_status *rx_status)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	u64 t_t, t_r;

	WARN_ON(अगरmsh->mesh_sp_id != IEEE80211_SYNC_METHOD_NEIGHBOR_OFFSET);

	/* standard mentions only beacons */
	अगर (stype != IEEE80211_STYPE_BEACON)
		वापस;

	/*
	 * Get समय when बारtamp field was received.  If we करोn't
	 * have rx बारtamps, then use current tsf as an approximation.
	 * drv_get_tsf() must be called beक्रमe entering the rcu-पढ़ो
	 * section.
	 */
	अगर (ieee80211_have_rx_बारtamp(rx_status))
		t_r = ieee80211_calculate_rx_बारtamp(local, rx_status,
						       24 + 12 +
						       elems->total_len +
						       FCS_LEN,
						       24);
	अन्यथा
		t_r = drv_get_tsf(local, sdata);

	rcu_पढ़ो_lock();
	sta = sta_info_get(sdata, mgmt->sa);
	अगर (!sta)
		जाओ no_sync;

	/* check offset sync conditions (13.13.2.2.1)
	 *
	 * TODO also sync to
	 * करोt11MeshNbrOffsetMaxNeighbor non-peer non-MBSS neighbors
	 */

	अगर (elems->mesh_config && mesh_peer_tbtt_adjusting(elems)) अणु
		msync_dbg(sdata, "STA %pM : is adjusting TBTT\n",
			  sta->sta.addr);
		जाओ no_sync;
	पूर्ण

	/* Timing offset calculation (see 13.13.2.2.2) */
	t_t = le64_to_cpu(mgmt->u.beacon.बारtamp);
	sta->mesh->t_offset = t_t - t_r;

	अगर (test_sta_flag(sta, WLAN_STA_TOFFSET_KNOWN)) अणु
		s64 t_घड़ीdrअगरt = sta->mesh->t_offset_setpoपूर्णांक - sta->mesh->t_offset;
		msync_dbg(sdata,
			  "STA %pM : t_offset=%lld, t_offset_setpoint=%lld, t_clockdrift=%lld\n",
			  sta->sta.addr, (दीर्घ दीर्घ) sta->mesh->t_offset,
			  (दीर्घ दीर्घ) sta->mesh->t_offset_setpoपूर्णांक,
			  (दीर्घ दीर्घ) t_घड़ीdrअगरt);

		अगर (t_घड़ीdrअगरt > TOFFSET_MAXIMUM_ADJUSTMENT ||
		    t_घड़ीdrअगरt < -TOFFSET_MAXIMUM_ADJUSTMENT) अणु
			msync_dbg(sdata,
				  "STA %pM : t_clockdrift=%lld too large, setpoint reset\n",
				  sta->sta.addr,
				  (दीर्घ दीर्घ) t_घड़ीdrअगरt);
			clear_sta_flag(sta, WLAN_STA_TOFFSET_KNOWN);
			जाओ no_sync;
		पूर्ण

		spin_lock_bh(&अगरmsh->sync_offset_lock);
		अगर (t_घड़ीdrअगरt > अगरmsh->sync_offset_घड़ीdrअगरt_max)
			अगरmsh->sync_offset_घड़ीdrअगरt_max = t_घड़ीdrअगरt;
		spin_unlock_bh(&अगरmsh->sync_offset_lock);
	पूर्ण अन्यथा अणु
		sta->mesh->t_offset_setpoपूर्णांक = sta->mesh->t_offset - TOFFSET_SET_MARGIN;
		set_sta_flag(sta, WLAN_STA_TOFFSET_KNOWN);
		msync_dbg(sdata,
			  "STA %pM : offset was invalid, t_offset=%lld\n",
			  sta->sta.addr,
			  (दीर्घ दीर्घ) sta->mesh->t_offset);
	पूर्ण

no_sync:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम mesh_sync_offset_adjust_tsf(काष्ठा ieee80211_sub_अगर_data *sdata,
					 काष्ठा beacon_data *beacon)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;

	WARN_ON(अगरmsh->mesh_sp_id != IEEE80211_SYNC_METHOD_NEIGHBOR_OFFSET);
	WARN_ON(!rcu_पढ़ो_lock_held());

	spin_lock_bh(&अगरmsh->sync_offset_lock);

	अगर (अगरmsh->sync_offset_घड़ीdrअगरt_max > TOFFSET_MINIMUM_ADJUSTMENT) अणु
		/* Since ajusting the tsf here would
		 * require a possibly blocking call
		 * to the driver tsf setter, we punt
		 * the tsf adjusपंचांगent to the mesh tasklet
		 */
		msync_dbg(sdata,
			  "TSF : kicking off TSF adjustment with clockdrift_max=%lld\n",
			  अगरmsh->sync_offset_घड़ीdrअगरt_max);
		set_bit(MESH_WORK_DRIFT_ADJUST, &अगरmsh->wrkq_flags);
	पूर्ण अन्यथा अणु
		msync_dbg(sdata,
			  "TSF : max clockdrift=%lld; too small to adjust\n",
			  (दीर्घ दीर्घ)अगरmsh->sync_offset_घड़ीdrअगरt_max);
		अगरmsh->sync_offset_घड़ीdrअगरt_max = 0;
	पूर्ण
	spin_unlock_bh(&अगरmsh->sync_offset_lock);
पूर्ण

अटल स्थिर काष्ठा sync_method sync_methods[] = अणु
	अणु
		.method = IEEE80211_SYNC_METHOD_NEIGHBOR_OFFSET,
		.ops = अणु
			.rx_bcn_presp = &mesh_sync_offset_rx_bcn_presp,
			.adjust_tsf = &mesh_sync_offset_adjust_tsf,
		पूर्ण
	पूर्ण,
पूर्ण;

स्थिर काष्ठा ieee80211_mesh_sync_ops *ieee80211_mesh_sync_ops_get(u8 method)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < ARRAY_SIZE(sync_methods); ++i) अणु
		अगर (sync_methods[i].method == method)
			वापस &sync_methods[i].ops;
	पूर्ण
	वापस शून्य;
पूर्ण
