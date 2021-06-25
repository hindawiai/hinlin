<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012-2013, Marco Porsch <marco.porsch@s2005.tu-chemnitz.de>
 * Copyright 2012-2013, cozybit Inc.
 */

#समावेश "mesh.h"
#समावेश "wme.h"


/* mesh PS management */

/**
 * mps_qos_null_get - create pre-addressed QoS Null frame क्रम mesh घातersave
 * @sta: the station to get the frame क्रम
 */
अटल काष्ठा sk_buff *mps_qos_null_get(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_hdr *nullfunc; /* use 4addr header */
	काष्ठा sk_buff *skb;
	पूर्णांक size = माप(*nullfunc);
	__le16 fc;

	skb = dev_alloc_skb(local->hw.extra_tx_headroom + size + 2);
	अगर (!skb)
		वापस शून्य;
	skb_reserve(skb, local->hw.extra_tx_headroom);

	nullfunc = skb_put(skb, size);
	fc = cpu_to_le16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_QOS_शून्यFUNC);
	ieee80211_fill_mesh_addresses(nullfunc, &fc, sta->sta.addr,
				      sdata->vअगर.addr);
	nullfunc->frame_control = fc;
	nullfunc->duration_id = 0;
	nullfunc->seq_ctrl = 0;
	/* no address resolution क्रम this frame -> set addr 1 immediately */
	स_नकल(nullfunc->addr1, sta->sta.addr, ETH_ALEN);
	skb_put_zero(skb, 2); /* append QoS control field */
	ieee80211_mps_set_frame_flags(sdata, sta, nullfunc);

	वापस skb;
पूर्ण

/**
 * mps_qos_null_tx - send a QoS Null to indicate link-specअगरic घातer mode
 * @sta: the station to send to
 */
अटल व्योम mps_qos_null_tx(काष्ठा sta_info *sta)
अणु
	काष्ठा sk_buff *skb;

	skb = mps_qos_null_get(sta);
	अगर (!skb)
		वापस;

	mps_dbg(sta->sdata, "announcing peer-specific power mode to %pM\n",
		sta->sta.addr);

	/* करोn't unपूर्णांकentionally start a MPSP */
	अगर (!test_sta_flag(sta, WLAN_STA_PS_STA)) अणु
		u8 *qc = ieee80211_get_qos_ctl((व्योम *) skb->data);

		qc[0] |= IEEE80211_QOS_CTL_EOSP;
	पूर्ण

	ieee80211_tx_skb(sta->sdata, skb);
पूर्ण

/**
 * ieee80211_mps_local_status_update - track status of local link-specअगरic PMs
 *
 * @sdata: local mesh subअगर
 *
 * sets the non-peer घातer mode and triggers the driver PS (re-)configuration
 * Return BSS_CHANGED_BEACON अगर a beacon update is necessary.
 */
u32 ieee80211_mps_local_status_update(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	काष्ठा sta_info *sta;
	bool peering = false;
	पूर्णांक light_sleep_cnt = 0;
	पूर्णांक deep_sleep_cnt = 0;
	u32 changed = 0;
	क्रमागत nl80211_mesh_घातer_mode nonpeer_pm;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sta, &sdata->local->sta_list, list) अणु
		अगर (sdata != sta->sdata)
			जारी;

		चयन (sta->mesh->plink_state) अणु
		हाल NL80211_PLINK_OPN_SNT:
		हाल NL80211_PLINK_OPN_RCVD:
		हाल NL80211_PLINK_CNF_RCVD:
			peering = true;
			अवरोध;
		हाल NL80211_PLINK_ESTAB:
			अगर (sta->mesh->local_pm == NL80211_MESH_POWER_LIGHT_SLEEP)
				light_sleep_cnt++;
			अन्यथा अगर (sta->mesh->local_pm == NL80211_MESH_POWER_DEEP_SLEEP)
				deep_sleep_cnt++;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	/*
	 * Set non-peer mode to active during peering/scanning/authentication
	 * (see IEEE802.11-2012 13.14.8.3). The non-peer mesh घातer mode is
	 * deep sleep अगर the local STA is in light or deep sleep towards at
	 * least one mesh peer (see 13.14.3.1). Otherwise, set it to the
	 * user-configured शेष value.
	 */
	अगर (peering) अणु
		mps_dbg(sdata, "setting non-peer PM to active for peering\n");
		nonpeer_pm = NL80211_MESH_POWER_ACTIVE;
	पूर्ण अन्यथा अगर (light_sleep_cnt || deep_sleep_cnt) अणु
		mps_dbg(sdata, "setting non-peer PM to deep sleep\n");
		nonpeer_pm = NL80211_MESH_POWER_DEEP_SLEEP;
	पूर्ण अन्यथा अणु
		mps_dbg(sdata, "setting non-peer PM to user value\n");
		nonpeer_pm = अगरmsh->mshcfg.घातer_mode;
	पूर्ण

	/* need update अगर sleep counts move between 0 and non-zero */
	अगर (अगरmsh->nonpeer_pm != nonpeer_pm ||
	    !अगरmsh->ps_peers_light_sleep != !light_sleep_cnt ||
	    !अगरmsh->ps_peers_deep_sleep != !deep_sleep_cnt)
		changed = BSS_CHANGED_BEACON;

	अगरmsh->nonpeer_pm = nonpeer_pm;
	अगरmsh->ps_peers_light_sleep = light_sleep_cnt;
	अगरmsh->ps_peers_deep_sleep = deep_sleep_cnt;

	वापस changed;
पूर्ण

/**
 * ieee80211_mps_set_sta_local_pm - set local PM towards a mesh STA
 *
 * @sta: mesh STA
 * @pm: the घातer mode to set
 * Return BSS_CHANGED_BEACON अगर a beacon update is in order.
 */
u32 ieee80211_mps_set_sta_local_pm(काष्ठा sta_info *sta,
				   क्रमागत nl80211_mesh_घातer_mode pm)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;

	अगर (sta->mesh->local_pm == pm)
		वापस 0;

	mps_dbg(sdata, "local STA operates in mode %d with %pM\n",
		pm, sta->sta.addr);

	sta->mesh->local_pm = pm;

	/*
	 * announce peer-specअगरic घातer mode transition
	 * (see IEEE802.11-2012 13.14.3.2 and 13.14.3.3)
	 */
	अगर (sta->mesh->plink_state == NL80211_PLINK_ESTAB)
		mps_qos_null_tx(sta);

	वापस ieee80211_mps_local_status_update(sdata);
पूर्ण

/**
 * ieee80211_mps_set_frame_flags - set mesh PS flags in FC (and QoS Control)
 *
 * @sdata: local mesh subअगर
 * @sta: mesh STA
 * @hdr: 802.11 frame header
 *
 * see IEEE802.11-2012 8.2.4.1.7 and 8.2.4.5.11
 *
 * NOTE: sta must be given when an inभागidually-addressed QoS frame header
 * is handled, क्रम group-addressed and management frames it is not used
 */
व्योम ieee80211_mps_set_frame_flags(काष्ठा ieee80211_sub_अगर_data *sdata,
				   काष्ठा sta_info *sta,
				   काष्ठा ieee80211_hdr *hdr)
अणु
	क्रमागत nl80211_mesh_घातer_mode pm;
	u8 *qc;

	अगर (WARN_ON(is_unicast_ether_addr(hdr->addr1) &&
		    ieee80211_is_data_qos(hdr->frame_control) &&
		    !sta))
		वापस;

	अगर (is_unicast_ether_addr(hdr->addr1) &&
	    ieee80211_is_data_qos(hdr->frame_control) &&
	    sta->mesh->plink_state == NL80211_PLINK_ESTAB)
		pm = sta->mesh->local_pm;
	अन्यथा
		pm = sdata->u.mesh.nonpeer_pm;

	अगर (pm == NL80211_MESH_POWER_ACTIVE)
		hdr->frame_control &= cpu_to_le16(~IEEE80211_FCTL_PM);
	अन्यथा
		hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_PM);

	अगर (!ieee80211_is_data_qos(hdr->frame_control))
		वापस;

	qc = ieee80211_get_qos_ctl(hdr);

	अगर ((is_unicast_ether_addr(hdr->addr1) &&
	     pm == NL80211_MESH_POWER_DEEP_SLEEP) ||
	    (is_multicast_ether_addr(hdr->addr1) &&
	     sdata->u.mesh.ps_peers_deep_sleep > 0))
		qc[1] |= (IEEE80211_QOS_CTL_MESH_PS_LEVEL >> 8);
	अन्यथा
		qc[1] &= ~(IEEE80211_QOS_CTL_MESH_PS_LEVEL >> 8);
पूर्ण

/**
 * ieee80211_mps_sta_status_update - update buffering status of neighbor STA
 *
 * @sta: mesh STA
 *
 * called after change of peering status or non-peer/peer-specअगरic घातer mode
 */
व्योम ieee80211_mps_sta_status_update(काष्ठा sta_info *sta)
अणु
	क्रमागत nl80211_mesh_घातer_mode pm;
	bool करो_buffer;

	/* For non-assoc STA, prevent buffering or frame transmission */
	अगर (sta->sta_state < IEEE80211_STA_ASSOC)
		वापस;

	/*
	 * use peer-specअगरic घातer mode अगर peering is established and the
	 * peer's घातer mode is known
	 */
	अगर (sta->mesh->plink_state == NL80211_PLINK_ESTAB &&
	    sta->mesh->peer_pm != NL80211_MESH_POWER_UNKNOWN)
		pm = sta->mesh->peer_pm;
	अन्यथा
		pm = sta->mesh->nonpeer_pm;

	करो_buffer = (pm != NL80211_MESH_POWER_ACTIVE);

	/* clear the MPSP flags क्रम non-peers or active STA */
	अगर (sta->mesh->plink_state != NL80211_PLINK_ESTAB) अणु
		clear_sta_flag(sta, WLAN_STA_MPSP_OWNER);
		clear_sta_flag(sta, WLAN_STA_MPSP_RECIPIENT);
	पूर्ण अन्यथा अगर (!करो_buffer) अणु
		clear_sta_flag(sta, WLAN_STA_MPSP_OWNER);
	पूर्ण

	/* Don't let the same PS state be set twice */
	अगर (test_sta_flag(sta, WLAN_STA_PS_STA) == करो_buffer)
		वापस;

	अगर (करो_buffer) अणु
		set_sta_flag(sta, WLAN_STA_PS_STA);
		atomic_inc(&sta->sdata->u.mesh.ps.num_sta_ps);
		mps_dbg(sta->sdata, "start PS buffering frames towards %pM\n",
			sta->sta.addr);
	पूर्ण अन्यथा अणु
		ieee80211_sta_ps_deliver_wakeup(sta);
	पूर्ण
पूर्ण

अटल व्योम mps_set_sta_peer_pm(काष्ठा sta_info *sta,
				काष्ठा ieee80211_hdr *hdr)
अणु
	क्रमागत nl80211_mesh_घातer_mode pm;
	u8 *qc = ieee80211_get_qos_ctl(hdr);

	/*
	 * Test Power Management field of frame control (PW) and
	 * mesh घातer save level subfield of QoS control field (PSL)
	 *
	 * | PM | PSL| Mesh PM |
	 * +----+----+---------+
	 * | 0  |Rsrv|  Active |
	 * | 1  | 0  |  Light  |
	 * | 1  | 1  |  Deep   |
	 */
	अगर (ieee80211_has_pm(hdr->frame_control)) अणु
		अगर (qc[1] & (IEEE80211_QOS_CTL_MESH_PS_LEVEL >> 8))
			pm = NL80211_MESH_POWER_DEEP_SLEEP;
		अन्यथा
			pm = NL80211_MESH_POWER_LIGHT_SLEEP;
	पूर्ण अन्यथा अणु
		pm = NL80211_MESH_POWER_ACTIVE;
	पूर्ण

	अगर (sta->mesh->peer_pm == pm)
		वापस;

	mps_dbg(sta->sdata, "STA %pM enters mode %d\n",
		sta->sta.addr, pm);

	sta->mesh->peer_pm = pm;

	ieee80211_mps_sta_status_update(sta);
पूर्ण

अटल व्योम mps_set_sta_nonpeer_pm(काष्ठा sta_info *sta,
				   काष्ठा ieee80211_hdr *hdr)
अणु
	क्रमागत nl80211_mesh_घातer_mode pm;

	अगर (ieee80211_has_pm(hdr->frame_control))
		pm = NL80211_MESH_POWER_DEEP_SLEEP;
	अन्यथा
		pm = NL80211_MESH_POWER_ACTIVE;

	अगर (sta->mesh->nonpeer_pm == pm)
		वापस;

	mps_dbg(sta->sdata, "STA %pM sets non-peer mode to %d\n",
		sta->sta.addr, pm);

	sta->mesh->nonpeer_pm = pm;

	ieee80211_mps_sta_status_update(sta);
पूर्ण

/**
 * ieee80211_mps_rx_h_sta_process - frame receive handler क्रम mesh घातersave
 *
 * @sta: STA info that transmitted the frame
 * @hdr: IEEE 802.11 (QoS) Header
 */
व्योम ieee80211_mps_rx_h_sta_process(काष्ठा sta_info *sta,
				    काष्ठा ieee80211_hdr *hdr)
अणु
	अगर (is_unicast_ether_addr(hdr->addr1) &&
	    ieee80211_is_data_qos(hdr->frame_control)) अणु
		/*
		 * inभागidually addressed QoS Data/Null frames contain
		 * peer link-specअगरic PS mode towards the local STA
		 */
		mps_set_sta_peer_pm(sta, hdr);

		/* check क्रम mesh Peer Service Period trigger frames */
		ieee80211_mpsp_trigger_process(ieee80211_get_qos_ctl(hdr),
					       sta, false, false);
	पूर्ण अन्यथा अणु
		/*
		 * can only determine non-peer PS mode
		 * (see IEEE802.11-2012 8.2.4.1.7)
		 */
		mps_set_sta_nonpeer_pm(sta, hdr);
	पूर्ण
पूर्ण


/* mesh PS frame release */

अटल व्योम mpsp_trigger_send(काष्ठा sta_info *sta, bool rspi, bool eosp)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr *nullfunc;
	काष्ठा ieee80211_tx_info *info;
	u8 *qc;

	skb = mps_qos_null_get(sta);
	अगर (!skb)
		वापस;

	nullfunc = (काष्ठा ieee80211_hdr *) skb->data;
	अगर (!eosp)
		nullfunc->frame_control |=
				cpu_to_le16(IEEE80211_FCTL_MOREDATA);
	/*
	 * | RSPI | EOSP |  MPSP triggering   |
	 * +------+------+--------------------+
	 * |  0   |  0   | local STA is owner |
	 * |  0   |  1   | no MPSP (MPSP end) |
	 * |  1   |  0   | both STA are owner |
	 * |  1   |  1   | peer STA is owner  | see IEEE802.11-2012 13.14.9.2
	 */
	qc = ieee80211_get_qos_ctl(nullfunc);
	अगर (rspi)
		qc[1] |= (IEEE80211_QOS_CTL_RSPI >> 8);
	अगर (eosp)
		qc[0] |= IEEE80211_QOS_CTL_EOSP;

	info = IEEE80211_SKB_CB(skb);

	info->flags |= IEEE80211_TX_CTL_NO_PS_BUFFER |
		       IEEE80211_TX_CTL_REQ_TX_STATUS;

	mps_dbg(sdata, "sending MPSP trigger%s%s to %pM\n",
		rspi ? " RSPI" : "", eosp ? " EOSP" : "", sta->sta.addr);

	ieee80211_tx_skb(sdata, skb);
पूर्ण

/**
 * mpsp_qos_null_append - append QoS Null frame to MPSP skb queue अगर needed
 * @sta: the station to handle
 * @frames: the frame list to append to
 *
 * To properly end a mesh MPSP the last transmitted frame has to set the EOSP
 * flag in the QoS Control field. In हाल the current tailing frame is not a
 * QoS Data frame, append a QoS Null to carry the flag.
 */
अटल व्योम mpsp_qos_null_append(काष्ठा sta_info *sta,
				 काष्ठा sk_buff_head *frames)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा sk_buff *new_skb, *skb = skb_peek_tail(frames);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ieee80211_tx_info *info;

	अगर (ieee80211_is_data_qos(hdr->frame_control))
		वापस;

	new_skb = mps_qos_null_get(sta);
	अगर (!new_skb)
		वापस;

	mps_dbg(sdata, "appending QoS Null in MPSP towards %pM\n",
		sta->sta.addr);
	/*
	 * This frame has to be transmitted last. Assign lowest priority to
	 * make sure it cannot pass other frames when releasing multiple ACs.
	 */
	new_skb->priority = 1;
	skb_set_queue_mapping(new_skb, IEEE80211_AC_BK);
	ieee80211_set_qos_hdr(sdata, new_skb);

	info = IEEE80211_SKB_CB(new_skb);
	info->control.vअगर = &sdata->vअगर;
	info->control.flags |= IEEE80211_TX_INTCFL_NEED_TXPROCESSING;

	__skb_queue_tail(frames, new_skb);
पूर्ण

/**
 * mps_frame_deliver - transmit frames during mesh घातersave
 *
 * @sta: STA info to transmit to
 * @n_frames: number of frames to transmit. -1 क्रम all
 */
अटल व्योम mps_frame_deliver(काष्ठा sta_info *sta, पूर्णांक n_frames)
अणु
	काष्ठा ieee80211_local *local = sta->sdata->local;
	पूर्णांक ac;
	काष्ठा sk_buff_head frames;
	काष्ठा sk_buff *skb;
	bool more_data = false;

	skb_queue_head_init(&frames);

	/* collect frame(s) from buffers */
	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		जबतक (n_frames != 0) अणु
			skb = skb_dequeue(&sta->tx_filtered[ac]);
			अगर (!skb) अणु
				skb = skb_dequeue(
					&sta->ps_tx_buf[ac]);
				अगर (skb)
					local->total_ps_buffered--;
			पूर्ण
			अगर (!skb)
				अवरोध;
			n_frames--;
			__skb_queue_tail(&frames, skb);
		पूर्ण

		अगर (!skb_queue_empty(&sta->tx_filtered[ac]) ||
		    !skb_queue_empty(&sta->ps_tx_buf[ac]))
			more_data = true;
	पूर्ण

	/* nothing to send? -> EOSP */
	अगर (skb_queue_empty(&frames)) अणु
		mpsp_trigger_send(sta, false, true);
		वापस;
	पूर्ण

	/* in a MPSP make sure the last skb is a QoS Data frame */
	अगर (test_sta_flag(sta, WLAN_STA_MPSP_OWNER))
		mpsp_qos_null_append(sta, &frames);

	mps_dbg(sta->sdata, "sending %d frames to PS STA %pM\n",
		skb_queue_len(&frames), sta->sta.addr);

	/* prepare collected frames क्रम transmission */
	skb_queue_walk(&frames, skb) अणु
		काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
		काष्ठा ieee80211_hdr *hdr = (व्योम *) skb->data;

		/*
		 * Tell TX path to send this frame even though the
		 * STA may still reमुख्य is PS mode after this frame
		 * exchange.
		 */
		info->flags |= IEEE80211_TX_CTL_NO_PS_BUFFER;

		अगर (more_data || !skb_queue_is_last(&frames, skb))
			hdr->frame_control |=
				cpu_to_le16(IEEE80211_FCTL_MOREDATA);
		अन्यथा
			hdr->frame_control &=
				cpu_to_le16(~IEEE80211_FCTL_MOREDATA);

		अगर (skb_queue_is_last(&frames, skb) &&
		    ieee80211_is_data_qos(hdr->frame_control)) अणु
			u8 *qoshdr = ieee80211_get_qos_ctl(hdr);

			/* MPSP trigger frame ends service period */
			*qoshdr |= IEEE80211_QOS_CTL_EOSP;
			info->flags |= IEEE80211_TX_CTL_REQ_TX_STATUS;
		पूर्ण
	पूर्ण

	ieee80211_add_pending_skbs(local, &frames);
	sta_info_recalc_tim(sta);
पूर्ण

/**
 * ieee80211_mpsp_trigger_process - track status of mesh Peer Service Periods
 *
 * @qc: QoS Control field
 * @sta: peer to start a MPSP with
 * @tx: frame was transmitted by the local STA
 * @acked: frame has been transmitted successfully
 *
 * NOTE: active mode STA may only serve as MPSP owner
 */
व्योम ieee80211_mpsp_trigger_process(u8 *qc, काष्ठा sta_info *sta,
				    bool tx, bool acked)
अणु
	u8 rspi = qc[1] & (IEEE80211_QOS_CTL_RSPI >> 8);
	u8 eosp = qc[0] & IEEE80211_QOS_CTL_EOSP;

	अगर (tx) अणु
		अगर (rspi && acked)
			set_sta_flag(sta, WLAN_STA_MPSP_RECIPIENT);

		अगर (eosp)
			clear_sta_flag(sta, WLAN_STA_MPSP_OWNER);
		अन्यथा अगर (acked &&
			 test_sta_flag(sta, WLAN_STA_PS_STA) &&
			 !test_and_set_sta_flag(sta, WLAN_STA_MPSP_OWNER))
			mps_frame_deliver(sta, -1);
	पूर्ण अन्यथा अणु
		अगर (eosp)
			clear_sta_flag(sta, WLAN_STA_MPSP_RECIPIENT);
		अन्यथा अगर (sta->mesh->local_pm != NL80211_MESH_POWER_ACTIVE)
			set_sta_flag(sta, WLAN_STA_MPSP_RECIPIENT);

		अगर (rspi && !test_and_set_sta_flag(sta, WLAN_STA_MPSP_OWNER))
			mps_frame_deliver(sta, -1);
	पूर्ण
पूर्ण

/**
 * ieee80211_mps_frame_release - release frames buffered due to mesh घातer save
 *
 * @sta: mesh STA
 * @elems: IEs of beacon or probe response
 *
 * For peers अगर we have inभागidually-addressed frames buffered or the peer
 * indicates buffered frames, send a corresponding MPSP trigger frame. Since
 * we करो not evaluate the awake winकरोw duration, QoS Nulls are used as MPSP
 * trigger frames. If the neighbour STA is not a peer, only send single frames.
 */
व्योम ieee80211_mps_frame_release(काष्ठा sta_info *sta,
				 काष्ठा ieee802_11_elems *elems)
अणु
	पूर्णांक ac, buffer_local = 0;
	bool has_buffered = false;

	अगर (sta->mesh->plink_state == NL80211_PLINK_ESTAB)
		has_buffered = ieee80211_check_tim(elems->tim, elems->tim_len,
						   sta->mesh->aid);

	अगर (has_buffered)
		mps_dbg(sta->sdata, "%pM indicates buffered frames\n",
			sta->sta.addr);

	/* only transmit to PS STA with announced, non-zero awake winकरोw */
	अगर (test_sta_flag(sta, WLAN_STA_PS_STA) &&
	    (!elems->awake_winकरोw || !le16_to_cpu(*elems->awake_winकरोw)))
		वापस;

	अगर (!test_sta_flag(sta, WLAN_STA_MPSP_OWNER))
		क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			buffer_local += skb_queue_len(&sta->ps_tx_buf[ac]) +
					skb_queue_len(&sta->tx_filtered[ac]);

	अगर (!has_buffered && !buffer_local)
		वापस;

	अगर (sta->mesh->plink_state == NL80211_PLINK_ESTAB)
		mpsp_trigger_send(sta, has_buffered, !buffer_local);
	अन्यथा
		mps_frame_deliver(sta, 1);
पूर्ण
