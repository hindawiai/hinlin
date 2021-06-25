<शैली गुरु>
/*
 * NXP Wireless LAN device driver: WMM
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश "decl.h"
#समावेश "ioctl.h"
#समावेश "util.h"
#समावेश "fw.h"
#समावेश "main.h"
#समावेश "wmm.h"
#समावेश "11n.h"


/* Maximum value FW can accept क्रम driver delay in packet transmission */
#घोषणा DRV_PKT_DELAY_TO_FW_MAX   512


#घोषणा WMM_QUEUED_PACKET_LOWER_LIMIT   180

#घोषणा WMM_QUEUED_PACKET_UPPER_LIMIT   200

/* Offset क्रम TOS field in the IP header */
#घोषणा IPTOS_OFFSET 5

अटल bool disable_tx_amsdu;
module_param(disable_tx_amsdu, bool, 0644);

/* This table inverses the tos_to_tid operation to get a priority
 * which is in sequential order, and can be compared.
 * Use this to compare the priority of two dअगरferent TIDs.
 */
स्थिर u8 tos_to_tid_inv[] = अणु
	0x02,  /* from tos_to_tid[2] = 0 */
	0x00,  /* from tos_to_tid[0] = 1 */
	0x01,  /* from tos_to_tid[1] = 2 */
	0x03,
	0x04,
	0x05,
	0x06,
	0x07
पूर्ण;

/* WMM inक्रमmation IE */
अटल स्थिर u8 wmm_info_ie[] = अणु WLAN_EID_VENDOR_SPECIFIC, 0x07,
	0x00, 0x50, 0xf2, 0x02,
	0x00, 0x01, 0x00
पूर्ण;

अटल स्थिर u8 wmm_aci_to_qidx_map[] = अणु WMM_AC_BE,
	WMM_AC_BK,
	WMM_AC_VI,
	WMM_AC_VO
पूर्ण;

अटल u8 tos_to_tid[] = अणु
	/* TID DSCP_P2 DSCP_P1 DSCP_P0 WMM_AC */
	0x01,			/* 0 1 0 AC_BK */
	0x02,			/* 0 0 0 AC_BK */
	0x00,			/* 0 0 1 AC_BE */
	0x03,			/* 0 1 1 AC_BE */
	0x04,			/* 1 0 0 AC_VI */
	0x05,			/* 1 0 1 AC_VI */
	0x06,			/* 1 1 0 AC_VO */
	0x07			/* 1 1 1 AC_VO */
पूर्ण;

अटल u8 ac_to_tid[4][2] = अणु अणु1, 2पूर्ण, अणु0, 3पूर्ण, अणु4, 5पूर्ण, अणु6, 7पूर्ण पूर्ण;

/*
 * This function debug prपूर्णांकs the priority parameters क्रम a WMM AC.
 */
अटल व्योम
mwअगरiex_wmm_ac_debug_prपूर्णांक(स्थिर काष्ठा ieee_types_wmm_ac_parameters *ac_param)
अणु
	स्थिर अक्षर *ac_str[] = अणु "BK", "BE", "VI", "VO" पूर्ण;

	pr_debug("info: WMM AC_%s: ACI=%d, ACM=%d, Aifsn=%d, "
		 "EcwMin=%d, EcwMax=%d, TxopLimit=%d\n",
		 ac_str[wmm_aci_to_qidx_map[(ac_param->aci_aअगरsn_biपंचांगap
					     & MWIFIEX_ACI) >> 5]],
		 (ac_param->aci_aअगरsn_biपंचांगap & MWIFIEX_ACI) >> 5,
		 (ac_param->aci_aअगरsn_biपंचांगap & MWIFIEX_ACM) >> 4,
		 ac_param->aci_aअगरsn_biपंचांगap & MWIFIEX_AIFSN,
		 ac_param->ecw_biपंचांगap & MWIFIEX_ECW_MIN,
		 (ac_param->ecw_biपंचांगap & MWIFIEX_ECW_MAX) >> 4,
		 le16_to_cpu(ac_param->tx_op_limit));
पूर्ण

/*
 * This function allocates a route address list.
 *
 * The function also initializes the list with the provided RA.
 */
अटल काष्ठा mwअगरiex_ra_list_tbl *
mwअगरiex_wmm_allocate_ralist_node(काष्ठा mwअगरiex_adapter *adapter, स्थिर u8 *ra)
अणु
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;

	ra_list = kzalloc(माप(काष्ठा mwअगरiex_ra_list_tbl), GFP_ATOMIC);
	अगर (!ra_list)
		वापस शून्य;

	INIT_LIST_HEAD(&ra_list->list);
	skb_queue_head_init(&ra_list->skb_head);

	स_नकल(ra_list->ra, ra, ETH_ALEN);

	ra_list->total_pkt_count = 0;

	mwअगरiex_dbg(adapter, INFO, "info: allocated ra_list %p\n", ra_list);

	वापस ra_list;
पूर्ण

/* This function वापसs अक्रमom no between 16 and 32 to be used as threshold
 * क्रम no of packets after which BA setup is initiated.
 */
अटल u8 mwअगरiex_get_अक्रमom_ba_threshold(व्योम)
अणु
	u64 ns;
	/* setup ba_packet_threshold here अक्रमom number between
	 * [BA_SETUP_PACKET_OFFSET,
	 * BA_SETUP_PACKET_OFFSET+BA_SETUP_MAX_PACKET_THRESHOLD-1]
	 */
	ns = kसमय_get_ns();
	ns += (ns >> 32) + (ns >> 16);

	वापस ((u8)ns % BA_SETUP_MAX_PACKET_THRESHOLD) + BA_SETUP_PACKET_OFFSET;
पूर्ण

/*
 * This function allocates and adds a RA list क्रम all TIDs
 * with the given RA.
 */
व्योम mwअगरiex_ralist_add(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *ra)
अणु
	पूर्णांक i;
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_sta_node *node;


	क्रम (i = 0; i < MAX_NUM_TID; ++i) अणु
		ra_list = mwअगरiex_wmm_allocate_ralist_node(adapter, ra);
		mwअगरiex_dbg(adapter, INFO,
			    "info: created ra_list %p\n", ra_list);

		अगर (!ra_list)
			अवरोध;

		ra_list->is_11n_enabled = 0;
		ra_list->tdls_link = false;
		ra_list->ba_status = BA_SETUP_NONE;
		ra_list->amsdu_in_ampdu = false;
		अगर (!mwअगरiex_queuing_ra_based(priv)) अणु
			अगर (mwअगरiex_is_tdls_link_setup
				(mwअगरiex_get_tdls_link_status(priv, ra))) अणु
				ra_list->tdls_link = true;
				ra_list->is_11n_enabled =
					mwअगरiex_tdls_peer_11n_enabled(priv, ra);
			पूर्ण अन्यथा अणु
				ra_list->is_11n_enabled = IS_11N_ENABLED(priv);
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_lock_bh(&priv->sta_list_spinlock);
			node = mwअगरiex_get_sta_entry(priv, ra);
			अगर (node)
				ra_list->tx_छोड़ोd = node->tx_छोड़ो;
			ra_list->is_11n_enabled =
				      mwअगरiex_is_sta_11n_enabled(priv, node);
			अगर (ra_list->is_11n_enabled)
				ra_list->max_amsdu = node->max_amsdu;
			spin_unlock_bh(&priv->sta_list_spinlock);
		पूर्ण

		mwअगरiex_dbg(adapter, DATA, "data: ralist %p: is_11n_enabled=%d\n",
			    ra_list, ra_list->is_11n_enabled);

		अगर (ra_list->is_11n_enabled) अणु
			ra_list->ba_pkt_count = 0;
			ra_list->ba_packet_thr =
					      mwअगरiex_get_अक्रमom_ba_threshold();
		पूर्ण
		list_add_tail(&ra_list->list,
			      &priv->wmm.tid_tbl_ptr[i].ra_list);
	पूर्ण
पूर्ण

/*
 * This function sets the WMM queue priorities to their शेष values.
 */
अटल व्योम mwअगरiex_wmm_शेष_queue_priorities(काष्ठा mwअगरiex_निजी *priv)
अणु
	/* Default queue priorities: VO->VI->BE->BK */
	priv->wmm.queue_priority[0] = WMM_AC_VO;
	priv->wmm.queue_priority[1] = WMM_AC_VI;
	priv->wmm.queue_priority[2] = WMM_AC_BE;
	priv->wmm.queue_priority[3] = WMM_AC_BK;
पूर्ण

/*
 * This function map ACs to TIDs.
 */
अटल व्योम
mwअगरiex_wmm_queue_priorities_tid(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_wmm_desc *wmm = &priv->wmm;
	u8 *queue_priority = wmm->queue_priority;
	पूर्णांक i;

	क्रम (i = 0; i < 4; ++i) अणु
		tos_to_tid[7 - (i * 2)] = ac_to_tid[queue_priority[i]][1];
		tos_to_tid[6 - (i * 2)] = ac_to_tid[queue_priority[i]][0];
	पूर्ण

	क्रम (i = 0; i < MAX_NUM_TID; ++i)
		priv->tos_to_tid_inv[tos_to_tid[i]] = (u8)i;

	atomic_set(&wmm->highest_queued_prio, HIGH_PRIO_TID);
पूर्ण

/*
 * This function initializes WMM priority queues.
 */
व्योम
mwअगरiex_wmm_setup_queue_priorities(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा ieee_types_wmm_parameter *wmm_ie)
अणु
	u16 cw_min, avg_back_off, पंचांगp[4];
	u32 i, j, num_ac;
	u8 ac_idx;

	अगर (!wmm_ie || !priv->wmm_enabled) अणु
		/* WMM is not enabled, just set the शेषs and वापस */
		mwअगरiex_wmm_शेष_queue_priorities(priv);
		वापस;
	पूर्ण

	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: WMM Parameter IE: version=%d,\t"
		    "qos_info Parameter Set Count=%d, Reserved=%#x\n",
		    wmm_ie->version, wmm_ie->qos_info_biपंचांगap &
		    IEEE80211_WMM_IE_AP_QOSINFO_PARAM_SET_CNT_MASK,
		    wmm_ie->reserved);

	क्रम (num_ac = 0; num_ac < ARRAY_SIZE(wmm_ie->ac_params); num_ac++) अणु
		u8 ecw = wmm_ie->ac_params[num_ac].ecw_biपंचांगap;
		u8 aci_aअगरsn = wmm_ie->ac_params[num_ac].aci_aअगरsn_biपंचांगap;
		cw_min = (1 << (ecw & MWIFIEX_ECW_MIN)) - 1;
		avg_back_off = (cw_min >> 1) + (aci_aअगरsn & MWIFIEX_AIFSN);

		ac_idx = wmm_aci_to_qidx_map[(aci_aअगरsn & MWIFIEX_ACI) >> 5];
		priv->wmm.queue_priority[ac_idx] = ac_idx;
		पंचांगp[ac_idx] = avg_back_off;

		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: WMM: CWmax=%d CWmin=%d Avg Back-off=%d\n",
			    (1 << ((ecw & MWIFIEX_ECW_MAX) >> 4)) - 1,
			    cw_min, avg_back_off);
		mwअगरiex_wmm_ac_debug_prपूर्णांक(&wmm_ie->ac_params[num_ac]);
	पूर्ण

	/* Bubble sort */
	क्रम (i = 0; i < num_ac; i++) अणु
		क्रम (j = 1; j < num_ac - i; j++) अणु
			अगर (पंचांगp[j - 1] > पंचांगp[j]) अणु
				swap(पंचांगp[j - 1], पंचांगp[j]);
				swap(priv->wmm.queue_priority[j - 1],
				     priv->wmm.queue_priority[j]);
			पूर्ण अन्यथा अगर (पंचांगp[j - 1] == पंचांगp[j]) अणु
				अगर (priv->wmm.queue_priority[j - 1]
				    < priv->wmm.queue_priority[j])
					swap(priv->wmm.queue_priority[j - 1],
					     priv->wmm.queue_priority[j]);
			पूर्ण
		पूर्ण
	पूर्ण

	mwअगरiex_wmm_queue_priorities_tid(priv);
पूर्ण

/*
 * This function evaluates whether or not an AC is to be करोwngraded.
 *
 * In हाल the AC is not enabled, the highest AC is वापसed that is
 * enabled and करोes not require admission control.
 */
अटल क्रमागत mwअगरiex_wmm_ac_e
mwअगरiex_wmm_eval_करोwngrade_ac(काष्ठा mwअगरiex_निजी *priv,
			      क्रमागत mwअगरiex_wmm_ac_e eval_ac)
अणु
	पूर्णांक करोwn_ac;
	क्रमागत mwअगरiex_wmm_ac_e ret_ac;
	काष्ठा mwअगरiex_wmm_ac_status *ac_status;

	ac_status = &priv->wmm.ac_status[eval_ac];

	अगर (!ac_status->disabled)
		/* Okay to use this AC, its enabled */
		वापस eval_ac;

	/* Setup a शेष वापस value of the lowest priority */
	ret_ac = WMM_AC_BK;

	/*
	 *  Find the highest AC that is enabled and करोes not require
	 *  admission control. The spec disallows करोwngrading to an AC,
	 *  which is enabled due to a completed admission control.
	 *  Unadmitted traffic is not to be sent on an AC with admitted
	 *  traffic.
	 */
	क्रम (करोwn_ac = WMM_AC_BK; करोwn_ac < eval_ac; करोwn_ac++) अणु
		ac_status = &priv->wmm.ac_status[करोwn_ac];

		अगर (!ac_status->disabled && !ac_status->flow_required)
			/* AC is enabled and करोes not require admission
			   control */
			ret_ac = (क्रमागत mwअगरiex_wmm_ac_e) करोwn_ac;
	पूर्ण

	वापस ret_ac;
पूर्ण

/*
 * This function करोwngrades WMM priority queue.
 */
व्योम
mwअगरiex_wmm_setup_ac_करोwngrade(काष्ठा mwअगरiex_निजी *priv)
अणु
	पूर्णांक ac_val;

	mwअगरiex_dbg(priv->adapter, INFO, "info: WMM: AC Priorities:\t"
		    "BK(0), BE(1), VI(2), VO(3)\n");

	अगर (!priv->wmm_enabled) अणु
		/* WMM is not enabled, शेष priorities */
		क्रम (ac_val = WMM_AC_BK; ac_val <= WMM_AC_VO; ac_val++)
			priv->wmm.ac_करोwn_graded_vals[ac_val] =
						(क्रमागत mwअगरiex_wmm_ac_e) ac_val;
	पूर्ण अन्यथा अणु
		क्रम (ac_val = WMM_AC_BK; ac_val <= WMM_AC_VO; ac_val++) अणु
			priv->wmm.ac_करोwn_graded_vals[ac_val]
				= mwअगरiex_wmm_eval_करोwngrade_ac(priv,
						(क्रमागत mwअगरiex_wmm_ac_e) ac_val);
			mwअगरiex_dbg(priv->adapter, INFO,
				    "info: WMM: AC PRIO %d maps to %d\n",
				    ac_val,
				    priv->wmm.ac_करोwn_graded_vals[ac_val]);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This function converts the IP TOS field to an WMM AC
 * Queue assignment.
 */
अटल क्रमागत mwअगरiex_wmm_ac_e
mwअगरiex_wmm_convert_tos_to_ac(काष्ठा mwअगरiex_adapter *adapter, u32 tos)
अणु
	/* Map of TOS UP values to WMM AC */
	अटल स्थिर क्रमागत mwअगरiex_wmm_ac_e tos_to_ac[] = अणु
		WMM_AC_BE,
		WMM_AC_BK,
		WMM_AC_BK,
		WMM_AC_BE,
		WMM_AC_VI,
		WMM_AC_VI,
		WMM_AC_VO,
		WMM_AC_VO
	पूर्ण;

	अगर (tos >= ARRAY_SIZE(tos_to_ac))
		वापस WMM_AC_BE;

	वापस tos_to_ac[tos];
पूर्ण

/*
 * This function evaluates a given TID and करोwngrades it to a lower
 * TID अगर the WMM Parameter IE received from the AP indicates that the
 * AP is disabled (due to call admission control (ACM bit). Mapping
 * of TID to AC is taken care of पूर्णांकernally.
 */
u8 mwअगरiex_wmm_करोwngrade_tid(काष्ठा mwअगरiex_निजी *priv, u32 tid)
अणु
	क्रमागत mwअगरiex_wmm_ac_e ac, ac_करोwn;
	u8 new_tid;

	ac = mwअगरiex_wmm_convert_tos_to_ac(priv->adapter, tid);
	ac_करोwn = priv->wmm.ac_करोwn_graded_vals[ac];

	/* Send the index to tid array, picking from the array will be
	 * taken care by dequeuing function
	 */
	new_tid = ac_to_tid[ac_करोwn][tid % 2];

	वापस new_tid;
पूर्ण

/*
 * This function initializes the WMM state inक्रमmation and the
 * WMM data path queues.
 */
व्योम
mwअगरiex_wmm_init(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक i, j;
	काष्ठा mwअगरiex_निजी *priv;

	क्रम (j = 0; j < adapter->priv_num; ++j) अणु
		priv = adapter->priv[j];
		अगर (!priv)
			जारी;

		क्रम (i = 0; i < MAX_NUM_TID; ++i) अणु
			अगर (!disable_tx_amsdu &&
			    adapter->tx_buf_size > MWIFIEX_TX_DATA_BUF_SIZE_2K)
				priv->aggr_prio_tbl[i].amsdu =
							priv->tos_to_tid_inv[i];
			अन्यथा
				priv->aggr_prio_tbl[i].amsdu =
							BA_STREAM_NOT_ALLOWED;
			priv->aggr_prio_tbl[i].ampdu_ap =
							priv->tos_to_tid_inv[i];
			priv->aggr_prio_tbl[i].ampdu_user =
							priv->tos_to_tid_inv[i];
		पूर्ण

		priv->aggr_prio_tbl[6].amsdu
					= priv->aggr_prio_tbl[6].ampdu_ap
					= priv->aggr_prio_tbl[6].ampdu_user
					= BA_STREAM_NOT_ALLOWED;

		priv->aggr_prio_tbl[7].amsdu = priv->aggr_prio_tbl[7].ampdu_ap
					= priv->aggr_prio_tbl[7].ampdu_user
					= BA_STREAM_NOT_ALLOWED;

		mwअगरiex_set_ba_params(priv);
		mwअगरiex_reset_11n_rx_seq_num(priv);

		priv->wmm.drv_pkt_delay_max = MWIFIEX_WMM_DRV_DELAY_MAX;
		atomic_set(&priv->wmm.tx_pkts_queued, 0);
		atomic_set(&priv->wmm.highest_queued_prio, HIGH_PRIO_TID);
	पूर्ण
पूर्ण

पूर्णांक mwअगरiex_bypass_txlist_empty(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा mwअगरiex_निजी *priv;
	पूर्णांक i;

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		priv = adapter->priv[i];
		अगर (!priv)
			जारी;
		अगर (adapter->अगर_ops.is_port_पढ़ोy &&
		    !adapter->अगर_ops.is_port_पढ़ोy(priv))
			जारी;
		अगर (!skb_queue_empty(&priv->bypass_txq))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * This function checks अगर WMM Tx queue is empty.
 */
पूर्णांक
mwअगरiex_wmm_lists_empty(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक i;
	काष्ठा mwअगरiex_निजी *priv;

	क्रम (i = 0; i < adapter->priv_num; ++i) अणु
		priv = adapter->priv[i];
		अगर (!priv)
			जारी;
		अगर (!priv->port_खोलो &&
		    (priv->bss_mode != NL80211_IFTYPE_ADHOC))
			जारी;
		अगर (adapter->अगर_ops.is_port_पढ़ोy &&
		    !adapter->अगर_ops.is_port_पढ़ोy(priv))
			जारी;
		अगर (atomic_पढ़ो(&priv->wmm.tx_pkts_queued))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * This function deletes all packets in an RA list node.
 *
 * The packet sent completion callback handler are called with
 * status failure, after they are dequeued to ensure proper
 * cleanup. The RA list node itself is मुक्तd at the end.
 */
अटल व्योम
mwअगरiex_wmm_del_pkts_in_ralist_node(काष्ठा mwअगरiex_निजी *priv,
				    काष्ठा mwअगरiex_ra_list_tbl *ra_list)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा sk_buff *skb, *पंचांगp;

	skb_queue_walk_safe(&ra_list->skb_head, skb, पंचांगp) अणु
		skb_unlink(skb, &ra_list->skb_head);
		mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0, -1);
	पूर्ण
पूर्ण

/*
 * This function deletes all packets in an RA list.
 *
 * Each nodes in the RA list are मुक्तd inभागidually first, and then
 * the RA list itself is मुक्तd.
 */
अटल व्योम
mwअगरiex_wmm_del_pkts_in_ralist(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा list_head *ra_list_head)
अणु
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;

	list_क्रम_each_entry(ra_list, ra_list_head, list)
		mwअगरiex_wmm_del_pkts_in_ralist_node(priv, ra_list);
पूर्ण

/*
 * This function deletes all packets in all RA lists.
 */
अटल व्योम mwअगरiex_wmm_cleanup_queues(काष्ठा mwअगरiex_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_NUM_TID; i++)
		mwअगरiex_wmm_del_pkts_in_ralist(priv, &priv->wmm.tid_tbl_ptr[i].
								       ra_list);

	atomic_set(&priv->wmm.tx_pkts_queued, 0);
	atomic_set(&priv->wmm.highest_queued_prio, HIGH_PRIO_TID);
पूर्ण

/*
 * This function deletes all route addresses from all RA lists.
 */
अटल व्योम mwअगरiex_wmm_delete_all_ralist(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_ra_list_tbl *ra_list, *पंचांगp_node;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_NUM_TID; ++i) अणु
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: ra_list: freeing buf for tid %d\n", i);
		list_क्रम_each_entry_safe(ra_list, पंचांगp_node,
					 &priv->wmm.tid_tbl_ptr[i].ra_list,
					 list) अणु
			list_del(&ra_list->list);
			kमुक्त(ra_list);
		पूर्ण

		INIT_LIST_HEAD(&priv->wmm.tid_tbl_ptr[i].ra_list);
	पूर्ण
पूर्ण

अटल पूर्णांक mwअगरiex_मुक्त_ack_frame(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	pr_warn("Have pending ack frames!\n");
	kमुक्त_skb(p);
	वापस 0;
पूर्ण

/*
 * This function cleans up the Tx and Rx queues.
 *
 * Cleanup includes -
 *      - All packets in RA lists
 *      - All entries in Rx reorder table
 *      - All entries in Tx BA stream table
 *      - MPA buffer (अगर required)
 *      - All RA lists
 */
व्योम
mwअगरiex_clean_txrx(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा sk_buff *skb, *पंचांगp;

	mwअगरiex_11n_cleanup_reorder_tbl(priv);
	spin_lock_bh(&priv->wmm.ra_list_spinlock);

	mwअगरiex_wmm_cleanup_queues(priv);
	mwअगरiex_11n_delete_all_tx_ba_stream_tbl(priv);

	अगर (priv->adapter->अगर_ops.cleanup_mpa_buf)
		priv->adapter->अगर_ops.cleanup_mpa_buf(priv->adapter);

	mwअगरiex_wmm_delete_all_ralist(priv);
	स_नकल(tos_to_tid, ac_to_tid, माप(tos_to_tid));

	अगर (priv->adapter->अगर_ops.clean_pcie_ring &&
	    !test_bit(MWIFIEX_SURPRISE_REMOVED, &priv->adapter->work_flags))
		priv->adapter->अगर_ops.clean_pcie_ring(priv->adapter);
	spin_unlock_bh(&priv->wmm.ra_list_spinlock);

	skb_queue_walk_safe(&priv->tdls_txq, skb, पंचांगp) अणु
		skb_unlink(skb, &priv->tdls_txq);
		mwअगरiex_ग_लिखो_data_complete(priv->adapter, skb, 0, -1);
	पूर्ण

	skb_queue_walk_safe(&priv->bypass_txq, skb, पंचांगp) अणु
		skb_unlink(skb, &priv->bypass_txq);
		mwअगरiex_ग_लिखो_data_complete(priv->adapter, skb, 0, -1);
	पूर्ण
	atomic_set(&priv->adapter->bypass_tx_pending, 0);

	idr_क्रम_each(&priv->ack_status_frames, mwअगरiex_मुक्त_ack_frame, शून्य);
	idr_destroy(&priv->ack_status_frames);
पूर्ण

/*
 * This function retrieves a particular RA list node, matching with the
 * given TID and RA address.
 */
काष्ठा mwअगरiex_ra_list_tbl *
mwअगरiex_wmm_get_ralist_node(काष्ठा mwअगरiex_निजी *priv, u8 tid,
			    स्थिर u8 *ra_addr)
अणु
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;

	list_क्रम_each_entry(ra_list, &priv->wmm.tid_tbl_ptr[tid].ra_list,
			    list) अणु
		अगर (!स_भेद(ra_list->ra, ra_addr, ETH_ALEN))
			वापस ra_list;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम mwअगरiex_update_ralist_tx_छोड़ो(काष्ठा mwअगरiex_निजी *priv, u8 *mac,
				    u8 tx_छोड़ो)
अणु
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;
	u32 pkt_cnt = 0, tx_pkts_queued;
	पूर्णांक i;

	spin_lock_bh(&priv->wmm.ra_list_spinlock);

	क्रम (i = 0; i < MAX_NUM_TID; ++i) अणु
		ra_list = mwअगरiex_wmm_get_ralist_node(priv, i, mac);
		अगर (ra_list && ra_list->tx_छोड़ोd != tx_छोड़ो) अणु
			pkt_cnt += ra_list->total_pkt_count;
			ra_list->tx_छोड़ोd = tx_छोड़ो;
			अगर (tx_छोड़ो)
				priv->wmm.pkts_छोड़ोd[i] +=
					ra_list->total_pkt_count;
			अन्यथा
				priv->wmm.pkts_छोड़ोd[i] -=
					ra_list->total_pkt_count;
		पूर्ण
	पूर्ण

	अगर (pkt_cnt) अणु
		tx_pkts_queued = atomic_पढ़ो(&priv->wmm.tx_pkts_queued);
		अगर (tx_छोड़ो)
			tx_pkts_queued -= pkt_cnt;
		अन्यथा
			tx_pkts_queued += pkt_cnt;

		atomic_set(&priv->wmm.tx_pkts_queued, tx_pkts_queued);
		atomic_set(&priv->wmm.highest_queued_prio, HIGH_PRIO_TID);
	पूर्ण
	spin_unlock_bh(&priv->wmm.ra_list_spinlock);
पूर्ण

/* This function updates non-tdls peer ralist tx_छोड़ो जबतक
 * tdls channel चयनing
 */
व्योम mwअगरiex_update_ralist_tx_छोड़ो_in_tdls_cs(काष्ठा mwअगरiex_निजी *priv,
					       u8 *mac, u8 tx_छोड़ो)
अणु
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;
	u32 pkt_cnt = 0, tx_pkts_queued;
	पूर्णांक i;

	spin_lock_bh(&priv->wmm.ra_list_spinlock);

	क्रम (i = 0; i < MAX_NUM_TID; ++i) अणु
		list_क्रम_each_entry(ra_list, &priv->wmm.tid_tbl_ptr[i].ra_list,
				    list) अणु
			अगर (!स_भेद(ra_list->ra, mac, ETH_ALEN))
				जारी;

			अगर (ra_list->tx_छोड़ोd != tx_छोड़ो) अणु
				pkt_cnt += ra_list->total_pkt_count;
				ra_list->tx_छोड़ोd = tx_छोड़ो;
				अगर (tx_छोड़ो)
					priv->wmm.pkts_छोड़ोd[i] +=
						ra_list->total_pkt_count;
				अन्यथा
					priv->wmm.pkts_छोड़ोd[i] -=
						ra_list->total_pkt_count;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (pkt_cnt) अणु
		tx_pkts_queued = atomic_पढ़ो(&priv->wmm.tx_pkts_queued);
		अगर (tx_छोड़ो)
			tx_pkts_queued -= pkt_cnt;
		अन्यथा
			tx_pkts_queued += pkt_cnt;

		atomic_set(&priv->wmm.tx_pkts_queued, tx_pkts_queued);
		atomic_set(&priv->wmm.highest_queued_prio, HIGH_PRIO_TID);
	पूर्ण
	spin_unlock_bh(&priv->wmm.ra_list_spinlock);
पूर्ण

/*
 * This function retrieves an RA list node क्रम a given TID and
 * RA address pair.
 *
 * If no such node is found, a new node is added first and then
 * retrieved.
 */
काष्ठा mwअगरiex_ra_list_tbl *
mwअगरiex_wmm_get_queue_raptr(काष्ठा mwअगरiex_निजी *priv, u8 tid,
			    स्थिर u8 *ra_addr)
अणु
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;

	ra_list = mwअगरiex_wmm_get_ralist_node(priv, tid, ra_addr);
	अगर (ra_list)
		वापस ra_list;
	mwअगरiex_ralist_add(priv, ra_addr);

	वापस mwअगरiex_wmm_get_ralist_node(priv, tid, ra_addr);
पूर्ण

/*
 * This function deletes RA list nodes क्रम given mac क्रम all TIDs.
 * Function also decrements TX pending count accordingly.
 */
व्योम
mwअगरiex_wmm_del_peer_ra_list(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *ra_addr)
अणु
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;
	पूर्णांक i;

	spin_lock_bh(&priv->wmm.ra_list_spinlock);

	क्रम (i = 0; i < MAX_NUM_TID; ++i) अणु
		ra_list = mwअगरiex_wmm_get_ralist_node(priv, i, ra_addr);

		अगर (!ra_list)
			जारी;
		mwअगरiex_wmm_del_pkts_in_ralist_node(priv, ra_list);
		अगर (ra_list->tx_छोड़ोd)
			priv->wmm.pkts_छोड़ोd[i] -= ra_list->total_pkt_count;
		अन्यथा
			atomic_sub(ra_list->total_pkt_count,
				   &priv->wmm.tx_pkts_queued);
		list_del(&ra_list->list);
		kमुक्त(ra_list);
	पूर्ण
	spin_unlock_bh(&priv->wmm.ra_list_spinlock);
पूर्ण

/*
 * This function checks अगर a particular RA list node exists in a given TID
 * table index.
 */
पूर्णांक
mwअगरiex_is_ralist_valid(काष्ठा mwअगरiex_निजी *priv,
			काष्ठा mwअगरiex_ra_list_tbl *ra_list, पूर्णांक ptr_index)
अणु
	काष्ठा mwअगरiex_ra_list_tbl *rlist;

	list_क्रम_each_entry(rlist, &priv->wmm.tid_tbl_ptr[ptr_index].ra_list,
			    list) अणु
		अगर (rlist == ra_list)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * This function adds a packet to bypass TX queue.
 * This is special TX queue क्रम packets which can be sent even when port_खोलो
 * is false.
 */
व्योम
mwअगरiex_wmm_add_buf_bypass_txqueue(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा sk_buff *skb)
अणु
	skb_queue_tail(&priv->bypass_txq, skb);
पूर्ण

/*
 * This function adds a packet to WMM queue.
 *
 * In disconnected state the packet is immediately dropped and the
 * packet send completion callback is called with status failure.
 *
 * Otherwise, the correct RA list node is located and the packet
 * is queued at the list tail.
 */
व्योम
mwअगरiex_wmm_add_buf_txqueue(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	u32 tid;
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;
	u8 ra[ETH_ALEN], tid_करोwn;
	काष्ठा list_head list_head;
	पूर्णांक tdls_status = TDLS_NOT_SETUP;
	काष्ठा ethhdr *eth_hdr = (काष्ठा ethhdr *)skb->data;
	काष्ठा mwअगरiex_txinfo *tx_info = MWIFIEX_SKB_TXCB(skb);

	स_नकल(ra, eth_hdr->h_dest, ETH_ALEN);

	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA &&
	    ISSUPP_TDLS_ENABLED(adapter->fw_cap_info)) अणु
		अगर (ntohs(eth_hdr->h_proto) == ETH_P_TDLS)
			mwअगरiex_dbg(adapter, DATA,
				    "TDLS setup packet for %pM.\t"
				    "Don't block\n", ra);
		अन्यथा अगर (स_भेद(priv->cfg_bssid, ra, ETH_ALEN))
			tdls_status = mwअगरiex_get_tdls_link_status(priv, ra);
	पूर्ण

	अगर (!priv->media_connected && !mwअगरiex_is_skb_mgmt_frame(skb)) अणु
		mwअगरiex_dbg(adapter, DATA, "data: drop packet in disconnect\n");
		mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0, -1);
		वापस;
	पूर्ण

	tid = skb->priority;

	spin_lock_bh(&priv->wmm.ra_list_spinlock);

	tid_करोwn = mwअगरiex_wmm_करोwngrade_tid(priv, tid);

	/* In हाल of infra as we have alपढ़ोy created the list during
	   association we just करोn't have to call get_queue_raptr, we will
	   have only 1 raptr क्रम a tid in हाल of infra */
	अगर (!mwअगरiex_queuing_ra_based(priv) &&
	    !mwअगरiex_is_skb_mgmt_frame(skb)) अणु
		चयन (tdls_status) अणु
		हाल TDLS_SETUP_COMPLETE:
		हाल TDLS_CHAN_SWITCHING:
		हाल TDLS_IN_BASE_CHAN:
		हाल TDLS_IN_OFF_CHAN:
			ra_list = mwअगरiex_wmm_get_queue_raptr(priv, tid_करोwn,
							      ra);
			tx_info->flags |= MWIFIEX_BUF_FLAG_TDLS_PKT;
			अवरोध;
		हाल TDLS_SETUP_INPROGRESS:
			skb_queue_tail(&priv->tdls_txq, skb);
			spin_unlock_bh(&priv->wmm.ra_list_spinlock);
			वापस;
		शेष:
			list_head = priv->wmm.tid_tbl_ptr[tid_करोwn].ra_list;
			ra_list = list_first_entry_or_null(&list_head,
					काष्ठा mwअगरiex_ra_list_tbl, list);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(ra, skb->data, ETH_ALEN);
		अगर (ra[0] & 0x01 || mwअगरiex_is_skb_mgmt_frame(skb))
			eth_broadcast_addr(ra);
		ra_list = mwअगरiex_wmm_get_queue_raptr(priv, tid_करोwn, ra);
	पूर्ण

	अगर (!ra_list) अणु
		spin_unlock_bh(&priv->wmm.ra_list_spinlock);
		mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0, -1);
		वापस;
	पूर्ण

	skb_queue_tail(&ra_list->skb_head, skb);

	ra_list->ba_pkt_count++;
	ra_list->total_pkt_count++;

	अगर (atomic_पढ़ो(&priv->wmm.highest_queued_prio) <
						priv->tos_to_tid_inv[tid_करोwn])
		atomic_set(&priv->wmm.highest_queued_prio,
			   priv->tos_to_tid_inv[tid_करोwn]);

	अगर (ra_list->tx_छोड़ोd)
		priv->wmm.pkts_छोड़ोd[tid_करोwn]++;
	अन्यथा
		atomic_inc(&priv->wmm.tx_pkts_queued);

	spin_unlock_bh(&priv->wmm.ra_list_spinlock);
पूर्ण

/*
 * This function processes the get WMM status command response from firmware.
 *
 * The response may contain multiple TLVs -
 *      - AC Queue status TLVs
 *      - Current WMM Parameter IE TLV
 *      - Admission Control action frame TLVs
 *
 * This function parses the TLVs and then calls further specअगरic functions
 * to process any changes in the queue prioritize or state.
 */
पूर्णांक mwअगरiex_ret_wmm_get_status(काष्ठा mwअगरiex_निजी *priv,
			       स्थिर काष्ठा host_cmd_ds_command *resp)
अणु
	u8 *curr = (u8 *) &resp->params.get_wmm_status;
	uपूर्णांक16_t resp_len = le16_to_cpu(resp->size), tlv_len;
	पूर्णांक mask = IEEE80211_WMM_IE_AP_QOSINFO_PARAM_SET_CNT_MASK;
	bool valid = true;

	काष्ठा mwअगरiex_ie_types_data *tlv_hdr;
	काष्ठा mwअगरiex_ie_types_wmm_queue_status *tlv_wmm_qstatus;
	काष्ठा ieee_types_wmm_parameter *wmm_param_ie = शून्य;
	काष्ठा mwअगरiex_wmm_ac_status *ac_status;

	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: WMM: WMM_GET_STATUS cmdresp received: %d\n",
		    resp_len);

	जबतक ((resp_len >= माप(tlv_hdr->header)) && valid) अणु
		tlv_hdr = (काष्ठा mwअगरiex_ie_types_data *) curr;
		tlv_len = le16_to_cpu(tlv_hdr->header.len);

		अगर (resp_len < tlv_len + माप(tlv_hdr->header))
			अवरोध;

		चयन (le16_to_cpu(tlv_hdr->header.type)) अणु
		हाल TLV_TYPE_WMMQSTATUS:
			tlv_wmm_qstatus =
				(काष्ठा mwअगरiex_ie_types_wmm_queue_status *)
				tlv_hdr;
			mwअगरiex_dbg(priv->adapter, CMD,
				    "info: CMD_RESP: WMM_GET_STATUS:\t"
				    "QSTATUS TLV: %d, %d, %d\n",
				    tlv_wmm_qstatus->queue_index,
				    tlv_wmm_qstatus->flow_required,
				    tlv_wmm_qstatus->disabled);

			ac_status = &priv->wmm.ac_status[tlv_wmm_qstatus->
							 queue_index];
			ac_status->disabled = tlv_wmm_qstatus->disabled;
			ac_status->flow_required =
						tlv_wmm_qstatus->flow_required;
			ac_status->flow_created = tlv_wmm_qstatus->flow_created;
			अवरोध;

		हाल WLAN_EID_VENDOR_SPECIFIC:
			/*
			 * Poपूर्णांक the regular IEEE IE 2 bytes पूर्णांकo the Marvell IE
			 *   and setup the IEEE IE type and length byte fields
			 */

			wmm_param_ie =
				(काष्ठा ieee_types_wmm_parameter *) (curr +
								    2);
			wmm_param_ie->vend_hdr.len = (u8) tlv_len;
			wmm_param_ie->vend_hdr.element_id =
						WLAN_EID_VENDOR_SPECIFIC;

			mwअगरiex_dbg(priv->adapter, CMD,
				    "info: CMD_RESP: WMM_GET_STATUS:\t"
				    "WMM Parameter Set Count: %d\n",
				    wmm_param_ie->qos_info_biपंचांगap & mask);

			अगर (wmm_param_ie->vend_hdr.len + 2 >
				माप(काष्ठा ieee_types_wmm_parameter))
				अवरोध;

			स_नकल((u8 *) &priv->curr_bss_params.bss_descriptor.
			       wmm_ie, wmm_param_ie,
			       wmm_param_ie->vend_hdr.len + 2);

			अवरोध;

		शेष:
			valid = false;
			अवरोध;
		पूर्ण

		curr += (tlv_len + माप(tlv_hdr->header));
		resp_len -= (tlv_len + माप(tlv_hdr->header));
	पूर्ण

	mwअगरiex_wmm_setup_queue_priorities(priv, wmm_param_ie);
	mwअगरiex_wmm_setup_ac_करोwngrade(priv);

	वापस 0;
पूर्ण

/*
 * Callback handler from the command module to allow insertion of a WMM TLV.
 *
 * If the BSS we are associating to supports WMM, this function adds the
 * required WMM Inक्रमmation IE to the association request command buffer in
 * the क्रमm of a Marvell extended IEEE IE.
 */
u32
mwअगरiex_wmm_process_association_req(काष्ठा mwअगरiex_निजी *priv,
				    u8 **assoc_buf,
				    काष्ठा ieee_types_wmm_parameter *wmm_ie,
				    काष्ठा ieee80211_ht_cap *ht_cap)
अणु
	काष्ठा mwअगरiex_ie_types_wmm_param_set *wmm_tlv;
	u32 ret_len = 0;

	/* Null checks */
	अगर (!assoc_buf)
		वापस 0;
	अगर (!(*assoc_buf))
		वापस 0;

	अगर (!wmm_ie)
		वापस 0;

	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: WMM: process assoc req: bss->wmm_ie=%#x\n",
		    wmm_ie->vend_hdr.element_id);

	अगर ((priv->wmm_required ||
	     (ht_cap && (priv->adapter->config_bands & BAND_GN ||
	     priv->adapter->config_bands & BAND_AN))) &&
	    wmm_ie->vend_hdr.element_id == WLAN_EID_VENDOR_SPECIFIC) अणु
		wmm_tlv = (काष्ठा mwअगरiex_ie_types_wmm_param_set *) *assoc_buf;
		wmm_tlv->header.type = cpu_to_le16((u16) wmm_info_ie[0]);
		wmm_tlv->header.len = cpu_to_le16((u16) wmm_info_ie[1]);
		स_नकल(wmm_tlv->wmm_ie, &wmm_info_ie[2],
		       le16_to_cpu(wmm_tlv->header.len));
		अगर (wmm_ie->qos_info_biपंचांगap & IEEE80211_WMM_IE_AP_QOSINFO_UAPSD)
			स_नकल((u8 *) (wmm_tlv->wmm_ie
				       + le16_to_cpu(wmm_tlv->header.len)
				       - माप(priv->wmm_qosinfo)),
			       &priv->wmm_qosinfo, माप(priv->wmm_qosinfo));

		ret_len = माप(wmm_tlv->header)
			  + le16_to_cpu(wmm_tlv->header.len);

		*assoc_buf += ret_len;
	पूर्ण

	वापस ret_len;
पूर्ण

/*
 * This function computes the समय delay in the driver queues क्रम a
 * given packet.
 *
 * When the packet is received at the OS/Driver पूर्णांकerface, the current
 * समय is set in the packet काष्ठाure. The dअगरference between the present
 * समय and that received समय is computed in this function and limited
 * based on pre-compiled limits in the driver.
 */
u8
mwअगरiex_wmm_compute_drv_pkt_delay(काष्ठा mwअगरiex_निजी *priv,
				  स्थिर काष्ठा sk_buff *skb)
अणु
	u32 queue_delay = kसमय_प्रकारo_ms(net_समयdelta(skb->tstamp));
	u8 ret_val;

	/*
	 * Queue delay is passed as a uपूर्णांक8 in units of 2ms (ms shअगरted
	 *  by 1). Min value (other than 0) is thereक्रमe 2ms, max is 510ms.
	 *
	 * Pass max value अगर queue_delay is beyond the uपूर्णांक8 range
	 */
	ret_val = (u8) (min(queue_delay, priv->wmm.drv_pkt_delay_max) >> 1);

	mwअगरiex_dbg(priv->adapter, DATA, "data: WMM: Pkt Delay: %d ms,\t"
		    "%d ms sent to FW\n", queue_delay, ret_val);

	वापस ret_val;
पूर्ण

/*
 * This function retrieves the highest priority RA list table poपूर्णांकer.
 */
अटल काष्ठा mwअगरiex_ra_list_tbl *
mwअगरiex_wmm_get_highest_priolist_ptr(काष्ठा mwअगरiex_adapter *adapter,
				     काष्ठा mwअगरiex_निजी **priv, पूर्णांक *tid)
अणु
	काष्ठा mwअगरiex_निजी *priv_पंचांगp;
	काष्ठा mwअगरiex_ra_list_tbl *ptr;
	काष्ठा mwअगरiex_tid_tbl *tid_ptr;
	atomic_t *hqp;
	पूर्णांक i, j;

	/* check the BSS with highest priority first */
	क्रम (j = adapter->priv_num - 1; j >= 0; --j) अणु
		/* iterate over BSS with the equal priority */
		list_क्रम_each_entry(adapter->bss_prio_tbl[j].bss_prio_cur,
				    &adapter->bss_prio_tbl[j].bss_prio_head,
				    list) अणु

try_again:
			priv_पंचांगp = adapter->bss_prio_tbl[j].bss_prio_cur->priv;

			अगर (((priv_पंचांगp->bss_mode != NL80211_IFTYPE_ADHOC) &&
			     !priv_पंचांगp->port_खोलो) ||
			    (atomic_पढ़ो(&priv_पंचांगp->wmm.tx_pkts_queued) == 0))
				जारी;

			अगर (adapter->अगर_ops.is_port_पढ़ोy &&
			    !adapter->अगर_ops.is_port_पढ़ोy(priv_पंचांगp))
				जारी;

			/* iterate over the WMM queues of the BSS */
			hqp = &priv_पंचांगp->wmm.highest_queued_prio;
			क्रम (i = atomic_पढ़ो(hqp); i >= LOW_PRIO_TID; --i) अणु

				spin_lock_bh(&priv_पंचांगp->wmm.ra_list_spinlock);

				tid_ptr = &(priv_पंचांगp)->wmm.
					tid_tbl_ptr[tos_to_tid[i]];

				/* iterate over receiver addresses */
				list_क्रम_each_entry(ptr, &tid_ptr->ra_list,
						    list) अणु

					अगर (!ptr->tx_छोड़ोd &&
					    !skb_queue_empty(&ptr->skb_head))
						/* holds both locks */
						जाओ found;
				पूर्ण

				spin_unlock_bh(&priv_पंचांगp->wmm.ra_list_spinlock);
			पूर्ण

			अगर (atomic_पढ़ो(&priv_पंचांगp->wmm.tx_pkts_queued) != 0) अणु
				atomic_set(&priv_पंचांगp->wmm.highest_queued_prio,
					   HIGH_PRIO_TID);
				/* Iterate current निजी once more, since
				 * there still exist packets in data queue
				 */
				जाओ try_again;
			पूर्ण अन्यथा
				atomic_set(&priv_पंचांगp->wmm.highest_queued_prio,
					   NO_PKT_PRIO_TID);
		पूर्ण
	पूर्ण

	वापस शून्य;

found:
	/* holds ra_list_spinlock */
	अगर (atomic_पढ़ो(hqp) > i)
		atomic_set(hqp, i);
	spin_unlock_bh(&priv_पंचांगp->wmm.ra_list_spinlock);

	*priv = priv_पंचांगp;
	*tid = tos_to_tid[i];

	वापस ptr;
पूर्ण

/* This functions rotates ra and bss lists so packets are picked round robin.
 *
 * After a packet is successfully transmitted, rotate the ra list, so the ra
 * next to the one transmitted, will come first in the list. This way we pick
 * the ra' in a round robin fashion. Same applies to bss nodes of equal
 * priority.
 *
 * Function also increments wmm.packets_out counter.
 */
व्योम mwअगरiex_rotate_priolists(काष्ठा mwअगरiex_निजी *priv,
				 काष्ठा mwअगरiex_ra_list_tbl *ra,
				 पूर्णांक tid)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_bss_prio_tbl *tbl = adapter->bss_prio_tbl;
	काष्ठा mwअगरiex_tid_tbl *tid_ptr = &priv->wmm.tid_tbl_ptr[tid];

	spin_lock_bh(&tbl[priv->bss_priority].bss_prio_lock);
	/*
	 * dirty trick: we हटाओ 'head' temporarily and reinsert it after
	 * curr bss node. imagine list to stay fixed जबतक head is moved
	 */
	list_move(&tbl[priv->bss_priority].bss_prio_head,
		  &tbl[priv->bss_priority].bss_prio_cur->list);
	spin_unlock_bh(&tbl[priv->bss_priority].bss_prio_lock);

	spin_lock_bh(&priv->wmm.ra_list_spinlock);
	अगर (mwअगरiex_is_ralist_valid(priv, ra, tid)) अणु
		priv->wmm.packets_out[tid]++;
		/* same as above */
		list_move(&tid_ptr->ra_list, &ra->list);
	पूर्ण
	spin_unlock_bh(&priv->wmm.ra_list_spinlock);
पूर्ण

/*
 * This function checks अगर 11n aggregation is possible.
 */
अटल पूर्णांक
mwअगरiex_is_11n_aggragation_possible(काष्ठा mwअगरiex_निजी *priv,
				    काष्ठा mwअगरiex_ra_list_tbl *ptr,
				    पूर्णांक max_buf_size)
अणु
	पूर्णांक count = 0, total_size = 0;
	काष्ठा sk_buff *skb, *पंचांगp;
	पूर्णांक max_amsdu_size;

	अगर (priv->bss_role == MWIFIEX_BSS_ROLE_UAP && priv->ap_11n_enabled &&
	    ptr->is_11n_enabled)
		max_amsdu_size = min_t(पूर्णांक, ptr->max_amsdu, max_buf_size);
	अन्यथा
		max_amsdu_size = max_buf_size;

	skb_queue_walk_safe(&ptr->skb_head, skb, पंचांगp) अणु
		total_size += skb->len;
		अगर (total_size >= max_amsdu_size)
			अवरोध;
		अगर (++count >= MIN_NUM_AMSDU)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * This function sends a single packet to firmware क्रम transmission.
 */
अटल व्योम
mwअगरiex_send_single_packet(काष्ठा mwअगरiex_निजी *priv,
			   काष्ठा mwअगरiex_ra_list_tbl *ptr, पूर्णांक ptr_index)
			   __releases(&priv->wmm.ra_list_spinlock)
अणु
	काष्ठा sk_buff *skb, *skb_next;
	काष्ठा mwअगरiex_tx_param tx_param;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_txinfo *tx_info;

	अगर (skb_queue_empty(&ptr->skb_head)) अणु
		spin_unlock_bh(&priv->wmm.ra_list_spinlock);
		mwअगरiex_dbg(adapter, DATA, "data: nothing to send\n");
		वापस;
	पूर्ण

	skb = skb_dequeue(&ptr->skb_head);

	tx_info = MWIFIEX_SKB_TXCB(skb);
	mwअगरiex_dbg(adapter, DATA,
		    "data: dequeuing the packet %p %p\n", ptr, skb);

	ptr->total_pkt_count--;

	अगर (!skb_queue_empty(&ptr->skb_head))
		skb_next = skb_peek(&ptr->skb_head);
	अन्यथा
		skb_next = शून्य;

	spin_unlock_bh(&priv->wmm.ra_list_spinlock);

	tx_param.next_pkt_len = ((skb_next) ? skb_next->len +
				माप(काष्ठा txpd) : 0);

	अगर (mwअगरiex_process_tx(priv, skb, &tx_param) == -EBUSY) अणु
		/* Queue the packet back at the head */
		spin_lock_bh(&priv->wmm.ra_list_spinlock);

		अगर (!mwअगरiex_is_ralist_valid(priv, ptr, ptr_index)) अणु
			spin_unlock_bh(&priv->wmm.ra_list_spinlock);
			mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0, -1);
			वापस;
		पूर्ण

		skb_queue_tail(&ptr->skb_head, skb);

		ptr->total_pkt_count++;
		ptr->ba_pkt_count++;
		tx_info->flags |= MWIFIEX_BUF_FLAG_REQUEUED_PKT;
		spin_unlock_bh(&priv->wmm.ra_list_spinlock);
	पूर्ण अन्यथा अणु
		mwअगरiex_rotate_priolists(priv, ptr, ptr_index);
		atomic_dec(&priv->wmm.tx_pkts_queued);
	पूर्ण
पूर्ण

/*
 * This function checks अगर the first packet in the given RA list
 * is alपढ़ोy processed or not.
 */
अटल पूर्णांक
mwअगरiex_is_ptr_processed(काष्ठा mwअगरiex_निजी *priv,
			 काष्ठा mwअगरiex_ra_list_tbl *ptr)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा mwअगरiex_txinfo *tx_info;

	अगर (skb_queue_empty(&ptr->skb_head))
		वापस false;

	skb = skb_peek(&ptr->skb_head);

	tx_info = MWIFIEX_SKB_TXCB(skb);
	अगर (tx_info->flags & MWIFIEX_BUF_FLAG_REQUEUED_PKT)
		वापस true;

	वापस false;
पूर्ण

/*
 * This function sends a single processed packet to firmware क्रम
 * transmission.
 */
अटल व्योम
mwअगरiex_send_processed_packet(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा mwअगरiex_ra_list_tbl *ptr, पूर्णांक ptr_index)
				__releases(&priv->wmm.ra_list_spinlock)
अणु
	काष्ठा mwअगरiex_tx_param tx_param;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	पूर्णांक ret = -1;
	काष्ठा sk_buff *skb, *skb_next;
	काष्ठा mwअगरiex_txinfo *tx_info;

	अगर (skb_queue_empty(&ptr->skb_head)) अणु
		spin_unlock_bh(&priv->wmm.ra_list_spinlock);
		वापस;
	पूर्ण

	skb = skb_dequeue(&ptr->skb_head);

	अगर (adapter->data_sent || adapter->tx_lock_flag) अणु
		ptr->total_pkt_count--;
		spin_unlock_bh(&priv->wmm.ra_list_spinlock);
		skb_queue_tail(&adapter->tx_data_q, skb);
		atomic_dec(&priv->wmm.tx_pkts_queued);
		atomic_inc(&adapter->tx_queued);
		वापस;
	पूर्ण

	अगर (!skb_queue_empty(&ptr->skb_head))
		skb_next = skb_peek(&ptr->skb_head);
	अन्यथा
		skb_next = शून्य;

	tx_info = MWIFIEX_SKB_TXCB(skb);

	spin_unlock_bh(&priv->wmm.ra_list_spinlock);

	tx_param.next_pkt_len =
		((skb_next) ? skb_next->len +
		 माप(काष्ठा txpd) : 0);
	अगर (adapter->अगरace_type == MWIFIEX_USB) अणु
		ret = adapter->अगर_ops.host_to_card(adapter, priv->usb_port,
						   skb, &tx_param);
	पूर्ण अन्यथा अणु
		ret = adapter->अगर_ops.host_to_card(adapter, MWIFIEX_TYPE_DATA,
						   skb, &tx_param);
	पूर्ण

	चयन (ret) अणु
	हाल -EBUSY:
		mwअगरiex_dbg(adapter, ERROR, "data: -EBUSY is returned\n");
		spin_lock_bh(&priv->wmm.ra_list_spinlock);

		अगर (!mwअगरiex_is_ralist_valid(priv, ptr, ptr_index)) अणु
			spin_unlock_bh(&priv->wmm.ra_list_spinlock);
			mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0, -1);
			वापस;
		पूर्ण

		skb_queue_tail(&ptr->skb_head, skb);

		tx_info->flags |= MWIFIEX_BUF_FLAG_REQUEUED_PKT;
		spin_unlock_bh(&priv->wmm.ra_list_spinlock);
		अवरोध;
	हाल -1:
		mwअगरiex_dbg(adapter, ERROR, "host_to_card failed: %#x\n", ret);
		adapter->dbg.num_tx_host_to_card_failure++;
		mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0, ret);
		अवरोध;
	हाल -EINPROGRESS:
		अवरोध;
	हाल 0:
		mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0, ret);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (ret != -EBUSY) अणु
		mwअगरiex_rotate_priolists(priv, ptr, ptr_index);
		atomic_dec(&priv->wmm.tx_pkts_queued);
		spin_lock_bh(&priv->wmm.ra_list_spinlock);
		ptr->total_pkt_count--;
		spin_unlock_bh(&priv->wmm.ra_list_spinlock);
	पूर्ण
पूर्ण

/*
 * This function dequeues a packet from the highest priority list
 * and transmits it.
 */
अटल पूर्णांक
mwअगरiex_dequeue_tx_packet(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा mwअगरiex_ra_list_tbl *ptr;
	काष्ठा mwअगरiex_निजी *priv = शून्य;
	पूर्णांक ptr_index = 0;
	u8 ra[ETH_ALEN];
	पूर्णांक tid_del = 0, tid = 0;

	ptr = mwअगरiex_wmm_get_highest_priolist_ptr(adapter, &priv, &ptr_index);
	अगर (!ptr)
		वापस -1;

	tid = mwअगरiex_get_tid(ptr);

	mwअगरiex_dbg(adapter, DATA, "data: tid=%d\n", tid);

	spin_lock_bh(&priv->wmm.ra_list_spinlock);
	अगर (!mwअगरiex_is_ralist_valid(priv, ptr, ptr_index)) अणु
		spin_unlock_bh(&priv->wmm.ra_list_spinlock);
		वापस -1;
	पूर्ण

	अगर (mwअगरiex_is_ptr_processed(priv, ptr)) अणु
		mwअगरiex_send_processed_packet(priv, ptr, ptr_index);
		/* ra_list_spinlock has been मुक्तd in
		   mwअगरiex_send_processed_packet() */
		वापस 0;
	पूर्ण

	अगर (!ptr->is_11n_enabled ||
		ptr->ba_status ||
		priv->wps.session_enable) अणु
		अगर (ptr->is_11n_enabled &&
			ptr->ba_status &&
			ptr->amsdu_in_ampdu &&
			mwअगरiex_is_amsdu_allowed(priv, tid) &&
			mwअगरiex_is_11n_aggragation_possible(priv, ptr,
							adapter->tx_buf_size))
			mwअगरiex_11n_aggregate_pkt(priv, ptr, ptr_index);
			/* ra_list_spinlock has been मुक्तd in
			 * mwअगरiex_11n_aggregate_pkt()
			 */
		अन्यथा
			mwअगरiex_send_single_packet(priv, ptr, ptr_index);
			/* ra_list_spinlock has been मुक्तd in
			 * mwअगरiex_send_single_packet()
			 */
	पूर्ण अन्यथा अणु
		अगर (mwअगरiex_is_ampdu_allowed(priv, ptr, tid) &&
		    ptr->ba_pkt_count > ptr->ba_packet_thr) अणु
			अगर (mwअगरiex_space_avail_क्रम_new_ba_stream(adapter)) अणु
				mwअगरiex_create_ba_tbl(priv, ptr->ra, tid,
						      BA_SETUP_INPROGRESS);
				mwअगरiex_send_addba(priv, tid, ptr->ra);
			पूर्ण अन्यथा अगर (mwअगरiex_find_stream_to_delete
				   (priv, tid, &tid_del, ra)) अणु
				mwअगरiex_create_ba_tbl(priv, ptr->ra, tid,
						      BA_SETUP_INPROGRESS);
				mwअगरiex_send_delba(priv, tid_del, ra, 1);
			पूर्ण
		पूर्ण
		अगर (mwअगरiex_is_amsdu_allowed(priv, tid) &&
		    mwअगरiex_is_11n_aggragation_possible(priv, ptr,
							adapter->tx_buf_size))
			mwअगरiex_11n_aggregate_pkt(priv, ptr, ptr_index);
			/* ra_list_spinlock has been मुक्तd in
			   mwअगरiex_11n_aggregate_pkt() */
		अन्यथा
			mwअगरiex_send_single_packet(priv, ptr, ptr_index);
			/* ra_list_spinlock has been मुक्तd in
			   mwअगरiex_send_single_packet() */
	पूर्ण
	वापस 0;
पूर्ण

व्योम mwअगरiex_process_bypass_tx(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा mwअगरiex_tx_param tx_param;
	काष्ठा sk_buff *skb;
	काष्ठा mwअगरiex_txinfo *tx_info;
	काष्ठा mwअगरiex_निजी *priv;
	पूर्णांक i;

	अगर (adapter->data_sent || adapter->tx_lock_flag)
		वापस;

	क्रम (i = 0; i < adapter->priv_num; ++i) अणु
		priv = adapter->priv[i];

		अगर (!priv)
			जारी;

		अगर (adapter->अगर_ops.is_port_पढ़ोy &&
		    !adapter->अगर_ops.is_port_पढ़ोy(priv))
			जारी;

		अगर (skb_queue_empty(&priv->bypass_txq))
			जारी;

		skb = skb_dequeue(&priv->bypass_txq);
		tx_info = MWIFIEX_SKB_TXCB(skb);

		/* no aggregation क्रम bypass packets */
		tx_param.next_pkt_len = 0;

		अगर (mwअगरiex_process_tx(priv, skb, &tx_param) == -EBUSY) अणु
			skb_queue_head(&priv->bypass_txq, skb);
			tx_info->flags |= MWIFIEX_BUF_FLAG_REQUEUED_PKT;
		पूर्ण अन्यथा अणु
			atomic_dec(&adapter->bypass_tx_pending);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This function transmits the highest priority packet aरुकोing in the
 * WMM Queues.
 */
व्योम
mwअगरiex_wmm_process_tx(काष्ठा mwअगरiex_adapter *adapter)
अणु
	करो अणु
		अगर (mwअगरiex_dequeue_tx_packet(adapter))
			अवरोध;
		अगर (adapter->अगरace_type != MWIFIEX_SDIO) अणु
			अगर (adapter->data_sent ||
			    adapter->tx_lock_flag)
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (atomic_पढ़ो(&adapter->tx_queued) >=
			    MWIFIEX_MAX_PKTS_TXQ)
				अवरोध;
		पूर्ण
	पूर्ण जबतक (!mwअगरiex_wmm_lists_empty(adapter));
पूर्ण
