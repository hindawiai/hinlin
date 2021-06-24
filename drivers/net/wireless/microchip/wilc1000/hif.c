<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#समावेश "netdev.h"

#घोषणा WILC_HIF_SCAN_TIMEOUT_MS                5000
#घोषणा WILC_HIF_CONNECT_TIMEOUT_MS             9500

#घोषणा WILC_FALSE_FRMWR_CHANNEL		100

#घोषणा WILC_SCAN_WID_LIST_SIZE		6

काष्ठा wilc_rcvd_mac_info अणु
	u8 status;
पूर्ण;

काष्ठा wilc_set_multicast अणु
	u32 enabled;
	u32 cnt;
	u8 *mc_list;
पूर्ण;

काष्ठा wilc_del_all_sta अणु
	u8 assoc_sta;
	u8 mac[WILC_MAX_NUM_STA][ETH_ALEN];
पूर्ण;

जोड़ wilc_message_body अणु
	काष्ठा wilc_rcvd_net_info net_info;
	काष्ठा wilc_rcvd_mac_info mac_info;
	काष्ठा wilc_set_multicast mc_info;
	काष्ठा wilc_reमुख्य_ch reमुख्य_on_ch;
	अक्षर *data;
पूर्ण;

काष्ठा host_अगर_msg अणु
	जोड़ wilc_message_body body;
	काष्ठा wilc_vअगर *vअगर;
	काष्ठा work_काष्ठा work;
	व्योम (*fn)(काष्ठा work_काष्ठा *ws);
	काष्ठा completion work_comp;
	bool is_sync;
पूर्ण;

/* 'msg' should be मुक्त by the caller क्रम syc */
अटल काष्ठा host_अगर_msg*
wilc_alloc_work(काष्ठा wilc_vअगर *vअगर, व्योम (*work_fun)(काष्ठा work_काष्ठा *),
		bool is_sync)
अणु
	काष्ठा host_अगर_msg *msg;

	अगर (!work_fun)
		वापस ERR_PTR(-EINVAL);

	msg = kzalloc(माप(*msg), GFP_ATOMIC);
	अगर (!msg)
		वापस ERR_PTR(-ENOMEM);
	msg->fn = work_fun;
	msg->vअगर = vअगर;
	msg->is_sync = is_sync;
	अगर (is_sync)
		init_completion(&msg->work_comp);

	वापस msg;
पूर्ण

अटल पूर्णांक wilc_enqueue_work(काष्ठा host_अगर_msg *msg)
अणु
	INIT_WORK(&msg->work, msg->fn);

	अगर (!msg->vअगर || !msg->vअगर->wilc || !msg->vअगर->wilc->hअगर_workqueue)
		वापस -EINVAL;

	अगर (!queue_work(msg->vअगर->wilc->hअगर_workqueue, &msg->work))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* The idx starts from 0 to (NUM_CONCURRENT_IFC - 1), but 0 index used as
 * special purpose in wilc device, so we add 1 to the index to starts from 1.
 * As a result, the वापसed index will be 1 to NUM_CONCURRENT_IFC.
 */
पूर्णांक wilc_get_vअगर_idx(काष्ठा wilc_vअगर *vअगर)
अणु
	वापस vअगर->idx + 1;
पूर्ण

/* We need to minus 1 from idx which is from wilc device to get real index
 * of wilc->vअगर[], because we add 1 when pass to wilc device in the function
 * wilc_get_vअगर_idx.
 * As a result, the index should be between 0 and (NUM_CONCURRENT_IFC - 1).
 */
अटल काष्ठा wilc_vअगर *wilc_get_vअगर_from_idx(काष्ठा wilc *wilc, पूर्णांक idx)
अणु
	पूर्णांक index = idx - 1;
	काष्ठा wilc_vअगर *vअगर;

	अगर (index < 0 || index >= WILC_NUM_CONCURRENT_IFC)
		वापस शून्य;

	list_क्रम_each_entry_rcu(vअगर, &wilc->vअगर_list, list) अणु
		अगर (vअगर->idx == index)
			वापस vअगर;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक handle_scan_करोne(काष्ठा wilc_vअगर *vअगर, क्रमागत scan_event evt)
अणु
	पूर्णांक result = 0;
	u8 पात_running_scan;
	काष्ठा wid wid;
	काष्ठा host_अगर_drv *hअगर_drv = vअगर->hअगर_drv;
	काष्ठा wilc_user_scan_req *scan_req;

	अगर (evt == SCAN_EVENT_ABORTED) अणु
		पात_running_scan = 1;
		wid.id = WID_ABORT_RUNNING_SCAN;
		wid.type = WID_CHAR;
		wid.val = (s8 *)&पात_running_scan;
		wid.size = माप(अक्षर);

		result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
		अगर (result) अणु
			netdev_err(vअगर->ndev, "Failed to set abort running\n");
			result = -EFAULT;
		पूर्ण
	पूर्ण

	अगर (!hअगर_drv) अणु
		netdev_err(vअगर->ndev, "%s: hif driver is NULL\n", __func__);
		वापस result;
	पूर्ण

	scan_req = &hअगर_drv->usr_scan_req;
	अगर (scan_req->scan_result) अणु
		scan_req->scan_result(evt, शून्य, scan_req->arg);
		scan_req->scan_result = शून्य;
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक wilc_scan(काष्ठा wilc_vअगर *vअगर, u8 scan_source, u8 scan_type,
	      u8 *ch_freq_list, u8 ch_list_len,
	      व्योम (*scan_result_fn)(क्रमागत scan_event,
				     काष्ठा wilc_rcvd_net_info *, व्योम *),
	      व्योम *user_arg, काष्ठा cfg80211_scan_request *request)
अणु
	पूर्णांक result = 0;
	काष्ठा wid wid_list[WILC_SCAN_WID_LIST_SIZE];
	u32 index = 0;
	u32 i, scan_समयout;
	u8 *buffer;
	u8 valuesize = 0;
	u8 *search_ssid_vals = शून्य;
	काष्ठा host_अगर_drv *hअगर_drv = vअगर->hअगर_drv;

	अगर (hअगर_drv->hअगर_state >= HOST_IF_SCANNING &&
	    hअगर_drv->hअगर_state < HOST_IF_CONNECTED) अणु
		netdev_err(vअगर->ndev, "Already scan\n");
		result = -EBUSY;
		जाओ error;
	पूर्ण

	अगर (vअगर->connecting) अणु
		netdev_err(vअगर->ndev, "Don't do obss scan\n");
		result = -EBUSY;
		जाओ error;
	पूर्ण

	hअगर_drv->usr_scan_req.ch_cnt = 0;

	अगर (request->n_ssids) अणु
		क्रम (i = 0; i < request->n_ssids; i++)
			valuesize += ((request->ssids[i].ssid_len) + 1);
		search_ssid_vals = kदो_स्मृति(valuesize + 1, GFP_KERNEL);
		अगर (search_ssid_vals) अणु
			wid_list[index].id = WID_SSID_PROBE_REQ;
			wid_list[index].type = WID_STR;
			wid_list[index].val = search_ssid_vals;
			buffer = wid_list[index].val;

			*buffer++ = request->n_ssids;

			क्रम (i = 0; i < request->n_ssids; i++) अणु
				*buffer++ = request->ssids[i].ssid_len;
				स_नकल(buffer, request->ssids[i].ssid,
				       request->ssids[i].ssid_len);
				buffer += request->ssids[i].ssid_len;
			पूर्ण
			wid_list[index].size = (s32)(valuesize + 1);
			index++;
		पूर्ण
	पूर्ण

	wid_list[index].id = WID_INFO_ELEMENT_PROBE;
	wid_list[index].type = WID_BIN_DATA;
	wid_list[index].val = (s8 *)request->ie;
	wid_list[index].size = request->ie_len;
	index++;

	wid_list[index].id = WID_SCAN_TYPE;
	wid_list[index].type = WID_CHAR;
	wid_list[index].size = माप(अक्षर);
	wid_list[index].val = (s8 *)&scan_type;
	index++;

	अगर (scan_type == WILC_FW_PASSIVE_SCAN && request->duration) अणु
		wid_list[index].id = WID_PASSIVE_SCAN_TIME;
		wid_list[index].type = WID_SHORT;
		wid_list[index].size = माप(u16);
		wid_list[index].val = (s8 *)&request->duration;
		index++;

		scan_समयout = (request->duration * ch_list_len) + 500;
	पूर्ण अन्यथा अणु
		scan_समयout = WILC_HIF_SCAN_TIMEOUT_MS;
	पूर्ण

	wid_list[index].id = WID_SCAN_CHANNEL_LIST;
	wid_list[index].type = WID_BIN_DATA;

	अगर (ch_freq_list && ch_list_len > 0) अणु
		क्रम (i = 0; i < ch_list_len; i++) अणु
			अगर (ch_freq_list[i] > 0)
				ch_freq_list[i] -= 1;
		पूर्ण
	पूर्ण

	wid_list[index].val = ch_freq_list;
	wid_list[index].size = ch_list_len;
	index++;

	wid_list[index].id = WID_START_SCAN_REQ;
	wid_list[index].type = WID_CHAR;
	wid_list[index].size = माप(अक्षर);
	wid_list[index].val = (s8 *)&scan_source;
	index++;

	hअगर_drv->usr_scan_req.scan_result = scan_result_fn;
	hअगर_drv->usr_scan_req.arg = user_arg;

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, wid_list, index);
	अगर (result) अणु
		netdev_err(vअगर->ndev, "Failed to send scan parameters\n");
		जाओ error;
	पूर्ण

	hअगर_drv->scan_समयr_vअगर = vअगर;
	mod_समयr(&hअगर_drv->scan_समयr,
		  jअगरfies + msecs_to_jअगरfies(scan_समयout));

error:

	kमुक्त(search_ssid_vals);

	वापस result;
पूर्ण

अटल पूर्णांक wilc_send_connect_wid(काष्ठा wilc_vअगर *vअगर)
अणु
	पूर्णांक result = 0;
	काष्ठा wid wid_list[4];
	u32 wid_cnt = 0;
	काष्ठा host_अगर_drv *hअगर_drv = vअगर->hअगर_drv;
	काष्ठा wilc_conn_info *conn_attr = &hअगर_drv->conn_info;
	काष्ठा wilc_join_bss_param *bss_param = conn_attr->param;

	wid_list[wid_cnt].id = WID_INFO_ELEMENT_ASSOCIATE;
	wid_list[wid_cnt].type = WID_BIN_DATA;
	wid_list[wid_cnt].val = conn_attr->req_ies;
	wid_list[wid_cnt].size = conn_attr->req_ies_len;
	wid_cnt++;

	wid_list[wid_cnt].id = WID_11I_MODE;
	wid_list[wid_cnt].type = WID_CHAR;
	wid_list[wid_cnt].size = माप(अक्षर);
	wid_list[wid_cnt].val = (s8 *)&conn_attr->security;
	wid_cnt++;

	wid_list[wid_cnt].id = WID_AUTH_TYPE;
	wid_list[wid_cnt].type = WID_CHAR;
	wid_list[wid_cnt].size = माप(अक्षर);
	wid_list[wid_cnt].val = (s8 *)&conn_attr->auth_type;
	wid_cnt++;

	wid_list[wid_cnt].id = WID_JOIN_REQ_EXTENDED;
	wid_list[wid_cnt].type = WID_STR;
	wid_list[wid_cnt].size = माप(*bss_param);
	wid_list[wid_cnt].val = (u8 *)bss_param;
	wid_cnt++;

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, wid_list, wid_cnt);
	अगर (result) अणु
		netdev_err(vअगर->ndev, "failed to send config packet\n");
		जाओ error;
	पूर्ण अन्यथा अणु
		hअगर_drv->hअगर_state = HOST_IF_WAITING_CONN_RESP;
	पूर्ण

	वापस 0;

error:

	kमुक्त(conn_attr->req_ies);
	conn_attr->req_ies = शून्य;

	वापस result;
पूर्ण

अटल व्योम handle_connect_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा host_अगर_msg *msg = container_of(work, काष्ठा host_अगर_msg, work);
	काष्ठा wilc_vअगर *vअगर = msg->vअगर;
	पूर्णांक result;
	काष्ठा wid wid;
	u16 dummy_reason_code = 0;
	काष्ठा host_अगर_drv *hअगर_drv = vअगर->hअगर_drv;

	अगर (!hअगर_drv) अणु
		netdev_err(vअगर->ndev, "%s: hif driver is NULL\n", __func__);
		जाओ out;
	पूर्ण

	hअगर_drv->hअगर_state = HOST_IF_IDLE;

	अगर (hअगर_drv->conn_info.conn_result) अणु
		hअगर_drv->conn_info.conn_result(CONN_DISCONN_EVENT_CONN_RESP,
					       WILC_MAC_STATUS_DISCONNECTED,
					       hअगर_drv->conn_info.arg);

	पूर्ण अन्यथा अणु
		netdev_err(vअगर->ndev, "%s: conn_result is NULL\n", __func__);
	पूर्ण

	wid.id = WID_DISCONNECT;
	wid.type = WID_CHAR;
	wid.val = (s8 *)&dummy_reason_code;
	wid.size = माप(अक्षर);

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to send disconnect\n");

	hअगर_drv->conn_info.req_ies_len = 0;
	kमुक्त(hअगर_drv->conn_info.req_ies);
	hअगर_drv->conn_info.req_ies = शून्य;

out:
	kमुक्त(msg);
पूर्ण

व्योम *wilc_parse_join_bss_param(काष्ठा cfg80211_bss *bss,
				काष्ठा cfg80211_crypto_settings *crypto)
अणु
	काष्ठा wilc_join_bss_param *param;
	काष्ठा ieee80211_p2p_noa_attr noa_attr;
	u8 rates_len = 0;
	स्थिर u8 *tim_elm, *ssid_elm, *rates_ie, *supp_rates_ie;
	स्थिर u8 *ht_ie, *wpa_ie, *wmm_ie, *rsn_ie;
	पूर्णांक ret;
	स्थिर काष्ठा cfg80211_bss_ies *ies = rcu_dereference(bss->ies);

	param = kzalloc(माप(*param), GFP_KERNEL);
	अगर (!param)
		वापस शून्य;

	param->beacon_period = cpu_to_le16(bss->beacon_पूर्णांकerval);
	param->cap_info = cpu_to_le16(bss->capability);
	param->bss_type = WILC_FW_BSS_TYPE_INFRA;
	param->ch = ieee80211_frequency_to_channel(bss->channel->center_freq);
	ether_addr_copy(param->bssid, bss->bssid);

	ssid_elm = cfg80211_find_ie(WLAN_EID_SSID, ies->data, ies->len);
	अगर (ssid_elm) अणु
		अगर (ssid_elm[1] <= IEEE80211_MAX_SSID_LEN)
			स_नकल(param->ssid, ssid_elm + 2, ssid_elm[1]);
	पूर्ण

	tim_elm = cfg80211_find_ie(WLAN_EID_TIM, ies->data, ies->len);
	अगर (tim_elm && tim_elm[1] >= 2)
		param->dtim_period = tim_elm[3];

	स_रखो(param->p_suites, 0xFF, 3);
	स_रखो(param->akm_suites, 0xFF, 3);

	rates_ie = cfg80211_find_ie(WLAN_EID_SUPP_RATES, ies->data, ies->len);
	अगर (rates_ie) अणु
		rates_len = rates_ie[1];
		अगर (rates_len > WILC_MAX_RATES_SUPPORTED)
			rates_len = WILC_MAX_RATES_SUPPORTED;
		param->supp_rates[0] = rates_len;
		स_नकल(&param->supp_rates[1], rates_ie + 2, rates_len);
	पूर्ण

	अगर (rates_len < WILC_MAX_RATES_SUPPORTED) अणु
		supp_rates_ie = cfg80211_find_ie(WLAN_EID_EXT_SUPP_RATES,
						 ies->data, ies->len);
		अगर (supp_rates_ie) अणु
			u8 ext_rates = supp_rates_ie[1];

			अगर (ext_rates > (WILC_MAX_RATES_SUPPORTED - rates_len))
				param->supp_rates[0] = WILC_MAX_RATES_SUPPORTED;
			अन्यथा
				param->supp_rates[0] += ext_rates;

			स_नकल(&param->supp_rates[rates_len + 1],
			       supp_rates_ie + 2,
			       (param->supp_rates[0] - rates_len));
		पूर्ण
	पूर्ण

	ht_ie = cfg80211_find_ie(WLAN_EID_HT_CAPABILITY, ies->data, ies->len);
	अगर (ht_ie)
		param->ht_capable = true;

	ret = cfg80211_get_p2p_attr(ies->data, ies->len,
				    IEEE80211_P2P_ATTR_ABSENCE_NOTICE,
				    (u8 *)&noa_attr, माप(noa_attr));
	अगर (ret > 0) अणु
		param->tsf_lo = cpu_to_le32(ies->tsf);
		param->noa_enabled = 1;
		param->idx = noa_attr.index;
		अगर (noa_attr.oppps_ctwinकरोw & IEEE80211_P2P_OPPPS_ENABLE_BIT) अणु
			param->opp_enabled = 1;
			param->opp_en.ct_winकरोw = noa_attr.oppps_ctwinकरोw;
			param->opp_en.cnt = noa_attr.desc[0].count;
			param->opp_en.duration = noa_attr.desc[0].duration;
			param->opp_en.पूर्णांकerval = noa_attr.desc[0].पूर्णांकerval;
			param->opp_en.start_समय = noa_attr.desc[0].start_समय;
		पूर्ण अन्यथा अणु
			param->opp_enabled = 0;
			param->opp_dis.cnt = noa_attr.desc[0].count;
			param->opp_dis.duration = noa_attr.desc[0].duration;
			param->opp_dis.पूर्णांकerval = noa_attr.desc[0].पूर्णांकerval;
			param->opp_dis.start_समय = noa_attr.desc[0].start_समय;
		पूर्ण
	पूर्ण
	wmm_ie = cfg80211_find_venकरोr_ie(WLAN_OUI_MICROSOFT,
					 WLAN_OUI_TYPE_MICROSOFT_WMM,
					 ies->data, ies->len);
	अगर (wmm_ie) अणु
		काष्ठा ieee80211_wmm_param_ie *ie;

		ie = (काष्ठा ieee80211_wmm_param_ie *)wmm_ie;
		अगर ((ie->oui_subtype == 0 || ie->oui_subtype == 1) &&
		    ie->version == 1) अणु
			param->wmm_cap = true;
			अगर (ie->qos_info & BIT(7))
				param->uapsd_cap = true;
		पूर्ण
	पूर्ण

	wpa_ie = cfg80211_find_venकरोr_ie(WLAN_OUI_MICROSOFT,
					 WLAN_OUI_TYPE_MICROSOFT_WPA,
					 ies->data, ies->len);
	अगर (wpa_ie) अणु
		param->mode_802_11i = 1;
		param->rsn_found = true;
	पूर्ण

	rsn_ie = cfg80211_find_ie(WLAN_EID_RSN, ies->data, ies->len);
	अगर (rsn_ie) अणु
		पूर्णांक offset = 8;

		param->mode_802_11i = 2;
		param->rsn_found = true;
		/* extract RSN capabilities */
		offset += (rsn_ie[offset] * 4) + 2;
		offset += (rsn_ie[offset] * 4) + 2;
		स_नकल(param->rsn_cap, &rsn_ie[offset], 2);
	पूर्ण

	अगर (param->rsn_found) अणु
		पूर्णांक i;

		param->rsn_grp_policy = crypto->cipher_group & 0xFF;
		क्रम (i = 0; i < crypto->n_ciphers_pairwise && i < 3; i++)
			param->p_suites[i] = crypto->ciphers_pairwise[i] & 0xFF;

		क्रम (i = 0; i < crypto->n_akm_suites && i < 3; i++)
			param->akm_suites[i] = crypto->akm_suites[i] & 0xFF;
	पूर्ण

	वापस (व्योम *)param;
पूर्ण

अटल व्योम handle_rcvd_ntwrk_info(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा host_अगर_msg *msg = container_of(work, काष्ठा host_अगर_msg, work);
	काष्ठा wilc_rcvd_net_info *rcvd_info = &msg->body.net_info;
	काष्ठा wilc_user_scan_req *scan_req = &msg->vअगर->hअगर_drv->usr_scan_req;
	स्थिर u8 *ch_elm;
	u8 *ies;
	पूर्णांक ies_len;
	माप_प्रकार offset;

	अगर (ieee80211_is_probe_resp(rcvd_info->mgmt->frame_control))
		offset = दुरत्व(काष्ठा ieee80211_mgmt, u.probe_resp.variable);
	अन्यथा अगर (ieee80211_is_beacon(rcvd_info->mgmt->frame_control))
		offset = दुरत्व(काष्ठा ieee80211_mgmt, u.beacon.variable);
	अन्यथा
		जाओ करोne;

	ies = rcvd_info->mgmt->u.beacon.variable;
	ies_len = rcvd_info->frame_len - offset;
	अगर (ies_len <= 0)
		जाओ करोne;

	ch_elm = cfg80211_find_ie(WLAN_EID_DS_PARAMS, ies, ies_len);
	अगर (ch_elm && ch_elm[1] > 0)
		rcvd_info->ch = ch_elm[2];

	अगर (scan_req->scan_result)
		scan_req->scan_result(SCAN_EVENT_NETWORK_FOUND, rcvd_info,
				      scan_req->arg);

करोne:
	kमुक्त(rcvd_info->mgmt);
	kमुक्त(msg);
पूर्ण

अटल व्योम host_पूर्णांक_get_assoc_res_info(काष्ठा wilc_vअगर *vअगर,
					u8 *assoc_resp_info,
					u32 max_assoc_resp_info_len,
					u32 *rcvd_assoc_resp_info_len)
अणु
	पूर्णांक result;
	काष्ठा wid wid;

	wid.id = WID_ASSOC_RES_INFO;
	wid.type = WID_STR;
	wid.val = assoc_resp_info;
	wid.size = max_assoc_resp_info_len;

	result = wilc_send_config_pkt(vअगर, WILC_GET_CFG, &wid, 1);
	अगर (result) अणु
		*rcvd_assoc_resp_info_len = 0;
		netdev_err(vअगर->ndev, "Failed to send association response\n");
		वापस;
	पूर्ण

	*rcvd_assoc_resp_info_len = wid.size;
पूर्ण

अटल s32 wilc_parse_assoc_resp_info(u8 *buffer, u32 buffer_len,
				      काष्ठा wilc_conn_info *ret_conn_info)
अणु
	u8 *ies;
	u16 ies_len;
	काष्ठा wilc_assoc_resp *res = (काष्ठा wilc_assoc_resp *)buffer;

	ret_conn_info->status = le16_to_cpu(res->status_code);
	अगर (ret_conn_info->status == WLAN_STATUS_SUCCESS) अणु
		ies = &buffer[माप(*res)];
		ies_len = buffer_len - माप(*res);

		ret_conn_info->resp_ies = kmemdup(ies, ies_len, GFP_KERNEL);
		अगर (!ret_conn_info->resp_ies)
			वापस -ENOMEM;

		ret_conn_info->resp_ies_len = ies_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम host_पूर्णांक_parse_assoc_resp_info(काष्ठा wilc_vअगर *vअगर,
						  u8 mac_status)
अणु
	काष्ठा host_अगर_drv *hअगर_drv = vअगर->hअगर_drv;
	काष्ठा wilc_conn_info *conn_info = &hअगर_drv->conn_info;

	अगर (mac_status == WILC_MAC_STATUS_CONNECTED) अणु
		u32 assoc_resp_info_len;

		स_रखो(hअगर_drv->assoc_resp, 0, WILC_MAX_ASSOC_RESP_FRAME_SIZE);

		host_पूर्णांक_get_assoc_res_info(vअगर, hअगर_drv->assoc_resp,
					    WILC_MAX_ASSOC_RESP_FRAME_SIZE,
					    &assoc_resp_info_len);

		अगर (assoc_resp_info_len != 0) अणु
			s32 err = 0;

			err = wilc_parse_assoc_resp_info(hअगर_drv->assoc_resp,
							 assoc_resp_info_len,
							 conn_info);
			अगर (err)
				netdev_err(vअगर->ndev,
					   "wilc_parse_assoc_resp_info() returned error %d\n",
					   err);
		पूर्ण
	पूर्ण

	del_समयr(&hअगर_drv->connect_समयr);
	conn_info->conn_result(CONN_DISCONN_EVENT_CONN_RESP, mac_status,
			       hअगर_drv->conn_info.arg);

	अगर (mac_status == WILC_MAC_STATUS_CONNECTED &&
	    conn_info->status == WLAN_STATUS_SUCCESS) अणु
		ether_addr_copy(hअगर_drv->assoc_bssid, conn_info->bssid);
		hअगर_drv->hअगर_state = HOST_IF_CONNECTED;
	पूर्ण अन्यथा अणु
		hअगर_drv->hअगर_state = HOST_IF_IDLE;
	पूर्ण

	kमुक्त(conn_info->resp_ies);
	conn_info->resp_ies = शून्य;
	conn_info->resp_ies_len = 0;

	kमुक्त(conn_info->req_ies);
	conn_info->req_ies = शून्य;
	conn_info->req_ies_len = 0;
पूर्ण

अटल अंतरभूत व्योम host_पूर्णांक_handle_disconnect(काष्ठा wilc_vअगर *vअगर)
अणु
	काष्ठा host_अगर_drv *hअगर_drv = vअगर->hअगर_drv;

	अगर (hअगर_drv->usr_scan_req.scan_result) अणु
		del_समयr(&hअगर_drv->scan_समयr);
		handle_scan_करोne(vअगर, SCAN_EVENT_ABORTED);
	पूर्ण

	अगर (hअगर_drv->conn_info.conn_result)
		hअगर_drv->conn_info.conn_result(CONN_DISCONN_EVENT_DISCONN_NOTIF,
					       0, hअगर_drv->conn_info.arg);
	अन्यथा
		netdev_err(vअगर->ndev, "%s: conn_result is NULL\n", __func__);

	eth_zero_addr(hअगर_drv->assoc_bssid);

	hअगर_drv->conn_info.req_ies_len = 0;
	kमुक्त(hअगर_drv->conn_info.req_ies);
	hअगर_drv->conn_info.req_ies = शून्य;
	hअगर_drv->hअगर_state = HOST_IF_IDLE;
पूर्ण

अटल व्योम handle_rcvd_gnrl_async_info(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा host_अगर_msg *msg = container_of(work, काष्ठा host_अगर_msg, work);
	काष्ठा wilc_vअगर *vअगर = msg->vअगर;
	काष्ठा wilc_rcvd_mac_info *mac_info = &msg->body.mac_info;
	काष्ठा host_अगर_drv *hअगर_drv = vअगर->hअगर_drv;

	अगर (!hअगर_drv) अणु
		netdev_err(vअगर->ndev, "%s: hif driver is NULL\n", __func__);
		जाओ मुक्त_msg;
	पूर्ण

	अगर (!hअगर_drv->conn_info.conn_result) अणु
		netdev_err(vअगर->ndev, "%s: conn_result is NULL\n", __func__);
		जाओ मुक्त_msg;
	पूर्ण

	अगर (hअगर_drv->hअगर_state == HOST_IF_WAITING_CONN_RESP) अणु
		host_पूर्णांक_parse_assoc_resp_info(vअगर, mac_info->status);
	पूर्ण अन्यथा अगर (mac_info->status == WILC_MAC_STATUS_DISCONNECTED) अणु
		अगर (hअगर_drv->hअगर_state == HOST_IF_CONNECTED) अणु
			host_पूर्णांक_handle_disconnect(vअगर);
		पूर्ण अन्यथा अगर (hअगर_drv->usr_scan_req.scan_result) अणु
			del_समयr(&hअगर_drv->scan_समयr);
			handle_scan_करोne(vअगर, SCAN_EVENT_ABORTED);
		पूर्ण
	पूर्ण

मुक्त_msg:
	kमुक्त(msg);
पूर्ण

पूर्णांक wilc_disconnect(काष्ठा wilc_vअगर *vअगर)
अणु
	काष्ठा wid wid;
	काष्ठा host_अगर_drv *hअगर_drv = vअगर->hअगर_drv;
	काष्ठा wilc_user_scan_req *scan_req;
	काष्ठा wilc_conn_info *conn_info;
	पूर्णांक result;
	u16 dummy_reason_code = 0;

	wid.id = WID_DISCONNECT;
	wid.type = WID_CHAR;
	wid.val = (s8 *)&dummy_reason_code;
	wid.size = माप(अक्षर);

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result) अणु
		netdev_err(vअगर->ndev, "Failed to send disconnect\n");
		वापस result;
	पूर्ण

	scan_req = &hअगर_drv->usr_scan_req;
	conn_info = &hअगर_drv->conn_info;

	अगर (scan_req->scan_result) अणु
		del_समयr(&hअगर_drv->scan_समयr);
		scan_req->scan_result(SCAN_EVENT_ABORTED, शून्य, scan_req->arg);
		scan_req->scan_result = शून्य;
	पूर्ण

	अगर (conn_info->conn_result) अणु
		अगर (hअगर_drv->hअगर_state == HOST_IF_WAITING_CONN_RESP)
			del_समयr(&hअगर_drv->connect_समयr);

		conn_info->conn_result(CONN_DISCONN_EVENT_DISCONN_NOTIF, 0,
				       conn_info->arg);
	पूर्ण अन्यथा अणु
		netdev_err(vअगर->ndev, "%s: conn_result is NULL\n", __func__);
	पूर्ण

	hअगर_drv->hअगर_state = HOST_IF_IDLE;

	eth_zero_addr(hअगर_drv->assoc_bssid);

	conn_info->req_ies_len = 0;
	kमुक्त(conn_info->req_ies);
	conn_info->req_ies = शून्य;

	वापस 0;
पूर्ण

पूर्णांक wilc_get_statistics(काष्ठा wilc_vअगर *vअगर, काष्ठा rf_info *stats)
अणु
	काष्ठा wid wid_list[5];
	u32 wid_cnt = 0, result;

	wid_list[wid_cnt].id = WID_LINKSPEED;
	wid_list[wid_cnt].type = WID_CHAR;
	wid_list[wid_cnt].size = माप(अक्षर);
	wid_list[wid_cnt].val = (s8 *)&stats->link_speed;
	wid_cnt++;

	wid_list[wid_cnt].id = WID_RSSI;
	wid_list[wid_cnt].type = WID_CHAR;
	wid_list[wid_cnt].size = माप(अक्षर);
	wid_list[wid_cnt].val = (s8 *)&stats->rssi;
	wid_cnt++;

	wid_list[wid_cnt].id = WID_SUCCESS_FRAME_COUNT;
	wid_list[wid_cnt].type = WID_INT;
	wid_list[wid_cnt].size = माप(u32);
	wid_list[wid_cnt].val = (s8 *)&stats->tx_cnt;
	wid_cnt++;

	wid_list[wid_cnt].id = WID_RECEIVED_FRAGMENT_COUNT;
	wid_list[wid_cnt].type = WID_INT;
	wid_list[wid_cnt].size = माप(u32);
	wid_list[wid_cnt].val = (s8 *)&stats->rx_cnt;
	wid_cnt++;

	wid_list[wid_cnt].id = WID_FAILED_COUNT;
	wid_list[wid_cnt].type = WID_INT;
	wid_list[wid_cnt].size = माप(u32);
	wid_list[wid_cnt].val = (s8 *)&stats->tx_fail_cnt;
	wid_cnt++;

	result = wilc_send_config_pkt(vअगर, WILC_GET_CFG, wid_list, wid_cnt);
	अगर (result) अणु
		netdev_err(vअगर->ndev, "Failed to send scan parameters\n");
		वापस result;
	पूर्ण

	अगर (stats->link_speed > TCP_ACK_FILTER_LINK_SPEED_THRESH &&
	    stats->link_speed != DEFAULT_LINK_SPEED)
		wilc_enable_tcp_ack_filter(vअगर, true);
	अन्यथा अगर (stats->link_speed != DEFAULT_LINK_SPEED)
		wilc_enable_tcp_ack_filter(vअगर, false);

	वापस result;
पूर्ण

अटल व्योम handle_get_statistics(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा host_अगर_msg *msg = container_of(work, काष्ठा host_अगर_msg, work);
	काष्ठा wilc_vअगर *vअगर = msg->vअगर;
	काष्ठा rf_info *stats = (काष्ठा rf_info *)msg->body.data;

	wilc_get_statistics(vअगर, stats);

	kमुक्त(msg);
पूर्ण

अटल व्योम wilc_hअगर_pack_sta_param(u8 *cur_byte, स्थिर u8 *mac,
				    काष्ठा station_parameters *params)
अणु
	ether_addr_copy(cur_byte, mac);
	cur_byte += ETH_ALEN;

	put_unaligned_le16(params->aid, cur_byte);
	cur_byte += 2;

	*cur_byte++ = params->supported_rates_len;
	अगर (params->supported_rates_len > 0)
		स_नकल(cur_byte, params->supported_rates,
		       params->supported_rates_len);
	cur_byte += params->supported_rates_len;

	अगर (params->ht_capa) अणु
		*cur_byte++ = true;
		स_नकल(cur_byte, params->ht_capa,
		       माप(काष्ठा ieee80211_ht_cap));
	पूर्ण अन्यथा अणु
		*cur_byte++ = false;
	पूर्ण
	cur_byte += माप(काष्ठा ieee80211_ht_cap);

	put_unaligned_le16(params->sta_flags_mask, cur_byte);
	cur_byte += 2;
	put_unaligned_le16(params->sta_flags_set, cur_byte);
पूर्ण

अटल पूर्णांक handle_reमुख्य_on_chan(काष्ठा wilc_vअगर *vअगर,
				 काष्ठा wilc_reमुख्य_ch *hअगर_reमुख्य_ch)
अणु
	पूर्णांक result;
	u8 reमुख्य_on_chan_flag;
	काष्ठा wid wid;
	काष्ठा host_अगर_drv *hअगर_drv = vअगर->hअगर_drv;

	अगर (hअगर_drv->usr_scan_req.scan_result)
		वापस -EBUSY;

	अगर (hअगर_drv->hअगर_state == HOST_IF_WAITING_CONN_RESP)
		वापस -EBUSY;

	अगर (vअगर->connecting)
		वापस -EBUSY;

	reमुख्य_on_chan_flag = true;
	wid.id = WID_REMAIN_ON_CHAN;
	wid.type = WID_STR;
	wid.size = 2;
	wid.val = kदो_स्मृति(wid.size, GFP_KERNEL);
	अगर (!wid.val)
		वापस -ENOMEM;

	wid.val[0] = reमुख्य_on_chan_flag;
	wid.val[1] = (s8)hअगर_reमुख्य_ch->ch;

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	kमुक्त(wid.val);
	अगर (result)
		वापस -EBUSY;

	hअगर_drv->reमुख्य_on_ch.arg = hअगर_reमुख्य_ch->arg;
	hअगर_drv->reमुख्य_on_ch.expired = hअगर_reमुख्य_ch->expired;
	hअगर_drv->reमुख्य_on_ch.ch = hअगर_reमुख्य_ch->ch;
	hअगर_drv->reमुख्य_on_ch.cookie = hअगर_reमुख्य_ch->cookie;
	hअगर_drv->reमुख्य_on_ch_समयr_vअगर = vअगर;

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_handle_roc_expired(काष्ठा wilc_vअगर *vअगर, u64 cookie)
अणु
	u8 reमुख्य_on_chan_flag;
	काष्ठा wid wid;
	पूर्णांक result;
	काष्ठा host_अगर_drv *hअगर_drv = vअगर->hअगर_drv;

	अगर (vअगर->priv.p2p_listen_state) अणु
		reमुख्य_on_chan_flag = false;
		wid.id = WID_REMAIN_ON_CHAN;
		wid.type = WID_STR;
		wid.size = 2;

		wid.val = kदो_स्मृति(wid.size, GFP_KERNEL);
		अगर (!wid.val)
			वापस -ENOMEM;

		wid.val[0] = reमुख्य_on_chan_flag;
		wid.val[1] = WILC_FALSE_FRMWR_CHANNEL;

		result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
		kमुक्त(wid.val);
		अगर (result != 0) अणु
			netdev_err(vअगर->ndev, "Failed to set remain channel\n");
			वापस -EINVAL;
		पूर्ण

		अगर (hअगर_drv->reमुख्य_on_ch.expired) अणु
			hअगर_drv->reमुख्य_on_ch.expired(hअगर_drv->reमुख्य_on_ch.arg,
						      cookie);
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev_dbg(vअगर->ndev, "Not in listen state\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wilc_handle_listen_state_expired(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा host_अगर_msg *msg = container_of(work, काष्ठा host_अगर_msg, work);

	wilc_handle_roc_expired(msg->vअगर, msg->body.reमुख्य_on_ch.cookie);
	kमुक्त(msg);
पूर्ण

अटल व्योम listen_समयr_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा host_अगर_drv *hअगर_drv = from_समयr(hअगर_drv, t,
						      reमुख्य_on_ch_समयr);
	काष्ठा wilc_vअगर *vअगर = hअगर_drv->reमुख्य_on_ch_समयr_vअगर;
	पूर्णांक result;
	काष्ठा host_अगर_msg *msg;

	del_समयr(&vअगर->hअगर_drv->reमुख्य_on_ch_समयr);

	msg = wilc_alloc_work(vअगर, wilc_handle_listen_state_expired, false);
	अगर (IS_ERR(msg))
		वापस;

	msg->body.reमुख्य_on_ch.cookie = vअगर->hअगर_drv->reमुख्य_on_ch.cookie;

	result = wilc_enqueue_work(msg);
	अगर (result) अणु
		netdev_err(vअगर->ndev, "%s: enqueue work failed\n", __func__);
		kमुक्त(msg);
	पूर्ण
पूर्ण

अटल व्योम handle_set_mcast_filter(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा host_अगर_msg *msg = container_of(work, काष्ठा host_अगर_msg, work);
	काष्ठा wilc_vअगर *vअगर = msg->vअगर;
	काष्ठा wilc_set_multicast *set_mc = &msg->body.mc_info;
	पूर्णांक result;
	काष्ठा wid wid;
	u8 *cur_byte;

	wid.id = WID_SETUP_MULTICAST_FILTER;
	wid.type = WID_BIN;
	wid.size = माप(काष्ठा wilc_set_multicast) + (set_mc->cnt * ETH_ALEN);
	wid.val = kदो_स्मृति(wid.size, GFP_KERNEL);
	अगर (!wid.val)
		जाओ error;

	cur_byte = wid.val;
	put_unaligned_le32(set_mc->enabled, cur_byte);
	cur_byte += 4;

	put_unaligned_le32(set_mc->cnt, cur_byte);
	cur_byte += 4;

	अगर (set_mc->cnt > 0 && set_mc->mc_list)
		स_नकल(cur_byte, set_mc->mc_list, set_mc->cnt * ETH_ALEN);

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to send setup multicast\n");

error:
	kमुक्त(set_mc->mc_list);
	kमुक्त(wid.val);
	kमुक्त(msg);
पूर्ण

अटल व्योम handle_scan_समयr(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा host_अगर_msg *msg = container_of(work, काष्ठा host_अगर_msg, work);

	handle_scan_करोne(msg->vअगर, SCAN_EVENT_ABORTED);
	kमुक्त(msg);
पूर्ण

अटल व्योम handle_scan_complete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा host_अगर_msg *msg = container_of(work, काष्ठा host_अगर_msg, work);

	del_समयr(&msg->vअगर->hअगर_drv->scan_समयr);

	handle_scan_करोne(msg->vअगर, SCAN_EVENT_DONE);

	kमुक्त(msg);
पूर्ण

अटल व्योम समयr_scan_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा host_अगर_drv *hअगर_drv = from_समयr(hअगर_drv, t, scan_समयr);
	काष्ठा wilc_vअगर *vअगर = hअगर_drv->scan_समयr_vअगर;
	काष्ठा host_अगर_msg *msg;
	पूर्णांक result;

	msg = wilc_alloc_work(vअगर, handle_scan_समयr, false);
	अगर (IS_ERR(msg))
		वापस;

	result = wilc_enqueue_work(msg);
	अगर (result)
		kमुक्त(msg);
पूर्ण

अटल व्योम समयr_connect_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा host_अगर_drv *hअगर_drv = from_समयr(hअगर_drv, t,
						      connect_समयr);
	काष्ठा wilc_vअगर *vअगर = hअगर_drv->connect_समयr_vअगर;
	काष्ठा host_अगर_msg *msg;
	पूर्णांक result;

	msg = wilc_alloc_work(vअगर, handle_connect_समयout, false);
	अगर (IS_ERR(msg))
		वापस;

	result = wilc_enqueue_work(msg);
	अगर (result)
		kमुक्त(msg);
पूर्ण

पूर्णांक wilc_हटाओ_wep_key(काष्ठा wilc_vअगर *vअगर, u8 index)
अणु
	काष्ठा wid wid;
	पूर्णांक result;

	wid.id = WID_REMOVE_WEP_KEY;
	wid.type = WID_STR;
	wid.size = माप(अक्षर);
	wid.val = &index;

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev,
			   "Failed to send remove wep key config packet\n");
	वापस result;
पूर्ण

पूर्णांक wilc_set_wep_शेष_keyid(काष्ठा wilc_vअगर *vअगर, u8 index)
अणु
	काष्ठा wid wid;
	पूर्णांक result;

	wid.id = WID_KEY_ID;
	wid.type = WID_CHAR;
	wid.size = माप(अक्षर);
	wid.val = &index;
	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev,
			   "Failed to send wep default key config packet\n");

	वापस result;
पूर्ण

पूर्णांक wilc_add_wep_key_bss_sta(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *key, u8 len,
			     u8 index)
अणु
	काष्ठा wid wid;
	पूर्णांक result;
	काष्ठा wilc_wep_key *wep_key;

	wid.id = WID_ADD_WEP_KEY;
	wid.type = WID_STR;
	wid.size = माप(*wep_key) + len;
	wep_key = kzalloc(wid.size, GFP_KERNEL);
	अगर (!wep_key)
		वापस -ENOMEM;

	wid.val = (u8 *)wep_key;

	wep_key->index = index;
	wep_key->key_len = len;
	स_नकल(wep_key->key, key, len);

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev,
			   "Failed to add wep key config packet\n");

	kमुक्त(wep_key);
	वापस result;
पूर्ण

पूर्णांक wilc_add_wep_key_bss_ap(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *key, u8 len,
			    u8 index, u8 mode, क्रमागत authtype auth_type)
अणु
	काष्ठा wid wid_list[3];
	पूर्णांक result;
	काष्ठा wilc_wep_key *wep_key;

	wid_list[0].id = WID_11I_MODE;
	wid_list[0].type = WID_CHAR;
	wid_list[0].size = माप(अक्षर);
	wid_list[0].val = &mode;

	wid_list[1].id = WID_AUTH_TYPE;
	wid_list[1].type = WID_CHAR;
	wid_list[1].size = माप(अक्षर);
	wid_list[1].val = (s8 *)&auth_type;

	wid_list[2].id = WID_WEP_KEY_VALUE;
	wid_list[2].type = WID_STR;
	wid_list[2].size = माप(*wep_key) + len;
	wep_key = kzalloc(wid_list[2].size, GFP_KERNEL);
	अगर (!wep_key)
		वापस -ENOMEM;

	wid_list[2].val = (u8 *)wep_key;

	wep_key->index = index;
	wep_key->key_len = len;
	स_नकल(wep_key->key, key, len);
	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, wid_list,
				      ARRAY_SIZE(wid_list));
	अगर (result)
		netdev_err(vअगर->ndev,
			   "Failed to add wep ap key config packet\n");

	kमुक्त(wep_key);
	वापस result;
पूर्ण

पूर्णांक wilc_add_ptk(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *ptk, u8 ptk_key_len,
		 स्थिर u8 *mac_addr, स्थिर u8 *rx_mic, स्थिर u8 *tx_mic,
		 u8 mode, u8 cipher_mode, u8 index)
अणु
	पूर्णांक result = 0;
	u8 t_key_len  = ptk_key_len + WILC_RX_MIC_KEY_LEN + WILC_TX_MIC_KEY_LEN;

	अगर (mode == WILC_AP_MODE) अणु
		काष्ठा wid wid_list[2];
		काष्ठा wilc_ap_wpa_ptk *key_buf;

		wid_list[0].id = WID_11I_MODE;
		wid_list[0].type = WID_CHAR;
		wid_list[0].size = माप(अक्षर);
		wid_list[0].val = (s8 *)&cipher_mode;

		key_buf = kzalloc(माप(*key_buf) + t_key_len, GFP_KERNEL);
		अगर (!key_buf)
			वापस -ENOMEM;

		ether_addr_copy(key_buf->mac_addr, mac_addr);
		key_buf->index = index;
		key_buf->key_len = t_key_len;
		स_नकल(&key_buf->key[0], ptk, ptk_key_len);

		अगर (rx_mic)
			स_नकल(&key_buf->key[ptk_key_len], rx_mic,
			       WILC_RX_MIC_KEY_LEN);

		अगर (tx_mic)
			स_नकल(&key_buf->key[ptk_key_len + WILC_RX_MIC_KEY_LEN],
			       tx_mic, WILC_TX_MIC_KEY_LEN);

		wid_list[1].id = WID_ADD_PTK;
		wid_list[1].type = WID_STR;
		wid_list[1].size = माप(*key_buf) + t_key_len;
		wid_list[1].val = (u8 *)key_buf;
		result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, wid_list,
					      ARRAY_SIZE(wid_list));
		kमुक्त(key_buf);
	पूर्ण अन्यथा अगर (mode == WILC_STATION_MODE) अणु
		काष्ठा wid wid;
		काष्ठा wilc_sta_wpa_ptk *key_buf;

		key_buf = kzalloc(माप(*key_buf) + t_key_len, GFP_KERNEL);
		अगर (!key_buf)
			वापस -ENOMEM;

		ether_addr_copy(key_buf->mac_addr, mac_addr);
		key_buf->key_len = t_key_len;
		स_नकल(&key_buf->key[0], ptk, ptk_key_len);

		अगर (rx_mic)
			स_नकल(&key_buf->key[ptk_key_len], rx_mic,
			       WILC_RX_MIC_KEY_LEN);

		अगर (tx_mic)
			स_नकल(&key_buf->key[ptk_key_len + WILC_RX_MIC_KEY_LEN],
			       tx_mic, WILC_TX_MIC_KEY_LEN);

		wid.id = WID_ADD_PTK;
		wid.type = WID_STR;
		wid.size = माप(*key_buf) + t_key_len;
		wid.val = (s8 *)key_buf;
		result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
		kमुक्त(key_buf);
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक wilc_add_rx_gtk(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *rx_gtk, u8 gtk_key_len,
		    u8 index, u32 key_rsc_len, स्थिर u8 *key_rsc,
		    स्थिर u8 *rx_mic, स्थिर u8 *tx_mic, u8 mode,
		    u8 cipher_mode)
अणु
	पूर्णांक result = 0;
	काष्ठा wilc_gtk_key *gtk_key;
	पूर्णांक t_key_len = gtk_key_len + WILC_RX_MIC_KEY_LEN + WILC_TX_MIC_KEY_LEN;

	gtk_key = kzalloc(माप(*gtk_key) + t_key_len, GFP_KERNEL);
	अगर (!gtk_key)
		वापस -ENOMEM;

	/* fill bssid value only in station mode */
	अगर (mode == WILC_STATION_MODE &&
	    vअगर->hअगर_drv->hअगर_state == HOST_IF_CONNECTED)
		स_नकल(gtk_key->mac_addr, vअगर->hअगर_drv->assoc_bssid, ETH_ALEN);

	अगर (key_rsc)
		स_नकल(gtk_key->rsc, key_rsc, 8);
	gtk_key->index = index;
	gtk_key->key_len = t_key_len;
	स_नकल(&gtk_key->key[0], rx_gtk, gtk_key_len);

	अगर (rx_mic)
		स_नकल(&gtk_key->key[gtk_key_len], rx_mic, WILC_RX_MIC_KEY_LEN);

	अगर (tx_mic)
		स_नकल(&gtk_key->key[gtk_key_len + WILC_RX_MIC_KEY_LEN],
		       tx_mic, WILC_TX_MIC_KEY_LEN);

	अगर (mode == WILC_AP_MODE) अणु
		काष्ठा wid wid_list[2];

		wid_list[0].id = WID_11I_MODE;
		wid_list[0].type = WID_CHAR;
		wid_list[0].size = माप(अक्षर);
		wid_list[0].val = (s8 *)&cipher_mode;

		wid_list[1].id = WID_ADD_RX_GTK;
		wid_list[1].type = WID_STR;
		wid_list[1].size = माप(*gtk_key) + t_key_len;
		wid_list[1].val = (u8 *)gtk_key;

		result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, wid_list,
					      ARRAY_SIZE(wid_list));
	पूर्ण अन्यथा अगर (mode == WILC_STATION_MODE) अणु
		काष्ठा wid wid;

		wid.id = WID_ADD_RX_GTK;
		wid.type = WID_STR;
		wid.size = माप(*gtk_key) + t_key_len;
		wid.val = (u8 *)gtk_key;
		result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	पूर्ण

	kमुक्त(gtk_key);
	वापस result;
पूर्ण

पूर्णांक wilc_set_pmkid_info(काष्ठा wilc_vअगर *vअगर, काष्ठा wilc_pmkid_attr *pmkid)
अणु
	काष्ठा wid wid;

	wid.id = WID_PMKID_INFO;
	wid.type = WID_STR;
	wid.size = (pmkid->numpmkid * माप(काष्ठा wilc_pmkid)) + 1;
	wid.val = (u8 *)pmkid;

	वापस wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
पूर्ण

पूर्णांक wilc_get_mac_address(काष्ठा wilc_vअगर *vअगर, u8 *mac_addr)
अणु
	पूर्णांक result;
	काष्ठा wid wid;

	wid.id = WID_MAC_ADDR;
	wid.type = WID_STR;
	wid.size = ETH_ALEN;
	wid.val = mac_addr;

	result = wilc_send_config_pkt(vअगर, WILC_GET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to get mac address\n");

	वापस result;
पूर्ण

पूर्णांक wilc_set_mac_address(काष्ठा wilc_vअगर *vअगर, u8 *mac_addr)
अणु
	काष्ठा wid wid;
	पूर्णांक result;

	wid.id = WID_MAC_ADDR;
	wid.type = WID_STR;
	wid.size = ETH_ALEN;
	wid.val = mac_addr;

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to get mac address\n");

	वापस result;
पूर्ण

पूर्णांक wilc_set_join_req(काष्ठा wilc_vअगर *vअगर, u8 *bssid, स्थिर u8 *ies,
		      माप_प्रकार ies_len)
अणु
	पूर्णांक result;
	काष्ठा host_अगर_drv *hअगर_drv = vअगर->hअगर_drv;
	काष्ठा wilc_conn_info *conn_info = &hअगर_drv->conn_info;

	अगर (bssid)
		ether_addr_copy(conn_info->bssid, bssid);

	अगर (ies) अणु
		conn_info->req_ies_len = ies_len;
		conn_info->req_ies = kmemdup(ies, ies_len, GFP_KERNEL);
		अगर (!conn_info->req_ies)
			वापस -ENOMEM;
	पूर्ण

	result = wilc_send_connect_wid(vअगर);
	अगर (result)
		जाओ मुक्त_ies;

	hअगर_drv->connect_समयr_vअगर = vअगर;
	mod_समयr(&hअगर_drv->connect_समयr,
		  jअगरfies + msecs_to_jअगरfies(WILC_HIF_CONNECT_TIMEOUT_MS));

	वापस 0;

मुक्त_ies:
	kमुक्त(conn_info->req_ies);

	वापस result;
पूर्ण

पूर्णांक wilc_set_mac_chnl_num(काष्ठा wilc_vअगर *vअगर, u8 channel)
अणु
	काष्ठा wid wid;
	पूर्णांक result;

	wid.id = WID_CURRENT_CHANNEL;
	wid.type = WID_CHAR;
	wid.size = माप(अक्षर);
	wid.val = &channel;

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to set channel\n");

	वापस result;
पूर्ण

पूर्णांक wilc_set_operation_mode(काष्ठा wilc_vअगर *vअगर, पूर्णांक index, u8 mode,
			    u8 अगरc_id)
अणु
	काष्ठा wid wid;
	पूर्णांक result;
	काष्ठा wilc_drv_handler drv;

	wid.id = WID_SET_OPERATION_MODE;
	wid.type = WID_STR;
	wid.size = माप(drv);
	wid.val = (u8 *)&drv;

	drv.handler = cpu_to_le32(index);
	drv.mode = (अगरc_id | (mode << 1));

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to set driver handler\n");

	वापस result;
पूर्ण

s32 wilc_get_inactive_समय(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *mac, u32 *out_val)
अणु
	काष्ठा wid wid;
	s32 result;

	wid.id = WID_SET_STA_MAC_INACTIVE_TIME;
	wid.type = WID_STR;
	wid.size = ETH_ALEN;
	wid.val = kzalloc(wid.size, GFP_KERNEL);
	अगर (!wid.val)
		वापस -ENOMEM;

	ether_addr_copy(wid.val, mac);
	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	kमुक्त(wid.val);
	अगर (result) अणु
		netdev_err(vअगर->ndev, "Failed to set inactive mac\n");
		वापस result;
	पूर्ण

	wid.id = WID_GET_INACTIVE_TIME;
	wid.type = WID_INT;
	wid.val = (s8 *)out_val;
	wid.size = माप(u32);
	result = wilc_send_config_pkt(vअगर, WILC_GET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to get inactive time\n");

	वापस result;
पूर्ण

पूर्णांक wilc_get_rssi(काष्ठा wilc_vअगर *vअगर, s8 *rssi_level)
अणु
	काष्ठा wid wid;
	पूर्णांक result;

	अगर (!rssi_level) अणु
		netdev_err(vअगर->ndev, "%s: RSSI level is NULL\n", __func__);
		वापस -EFAULT;
	पूर्ण

	wid.id = WID_RSSI;
	wid.type = WID_CHAR;
	wid.size = माप(अक्षर);
	wid.val = rssi_level;
	result = wilc_send_config_pkt(vअगर, WILC_GET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to get RSSI value\n");

	वापस result;
पूर्ण

अटल पूर्णांक wilc_get_stats_async(काष्ठा wilc_vअगर *vअगर, काष्ठा rf_info *stats)
अणु
	पूर्णांक result;
	काष्ठा host_अगर_msg *msg;

	msg = wilc_alloc_work(vअगर, handle_get_statistics, false);
	अगर (IS_ERR(msg))
		वापस PTR_ERR(msg);

	msg->body.data = (अक्षर *)stats;

	result = wilc_enqueue_work(msg);
	अगर (result) अणु
		netdev_err(vअगर->ndev, "%s: enqueue work failed\n", __func__);
		kमुक्त(msg);
		वापस result;
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक wilc_hअगर_set_cfg(काष्ठा wilc_vअगर *vअगर, काष्ठा cfg_param_attr *param)
अणु
	काष्ठा wid wid_list[4];
	पूर्णांक i = 0;

	अगर (param->flag & WILC_CFG_PARAM_RETRY_SHORT) अणु
		wid_list[i].id = WID_SHORT_RETRY_LIMIT;
		wid_list[i].val = (s8 *)&param->लघु_retry_limit;
		wid_list[i].type = WID_SHORT;
		wid_list[i].size = माप(u16);
		i++;
	पूर्ण
	अगर (param->flag & WILC_CFG_PARAM_RETRY_LONG) अणु
		wid_list[i].id = WID_LONG_RETRY_LIMIT;
		wid_list[i].val = (s8 *)&param->दीर्घ_retry_limit;
		wid_list[i].type = WID_SHORT;
		wid_list[i].size = माप(u16);
		i++;
	पूर्ण
	अगर (param->flag & WILC_CFG_PARAM_FRAG_THRESHOLD) अणु
		wid_list[i].id = WID_FRAG_THRESHOLD;
		wid_list[i].val = (s8 *)&param->frag_threshold;
		wid_list[i].type = WID_SHORT;
		wid_list[i].size = माप(u16);
		i++;
	पूर्ण
	अगर (param->flag & WILC_CFG_PARAM_RTS_THRESHOLD) अणु
		wid_list[i].id = WID_RTS_THRESHOLD;
		wid_list[i].val = (s8 *)&param->rts_threshold;
		wid_list[i].type = WID_SHORT;
		wid_list[i].size = माप(u16);
		i++;
	पूर्ण

	वापस wilc_send_config_pkt(vअगर, WILC_SET_CFG, wid_list, i);
पूर्ण

अटल व्योम get_periodic_rssi(काष्ठा समयr_list *t)
अणु
	काष्ठा wilc_vअगर *vअगर = from_समयr(vअगर, t, periodic_rssi);

	अगर (!vअगर->hअगर_drv) अणु
		netdev_err(vअगर->ndev, "%s: hif driver is NULL", __func__);
		वापस;
	पूर्ण

	अगर (vअगर->hअगर_drv->hअगर_state == HOST_IF_CONNECTED)
		wilc_get_stats_async(vअगर, &vअगर->periodic_stat);

	mod_समयr(&vअगर->periodic_rssi, jअगरfies + msecs_to_jअगरfies(5000));
पूर्ण

पूर्णांक wilc_init(काष्ठा net_device *dev, काष्ठा host_अगर_drv **hअगर_drv_handler)
अणु
	काष्ठा host_अगर_drv *hअगर_drv;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc = vअगर->wilc;

	hअगर_drv  = kzalloc(माप(*hअगर_drv), GFP_KERNEL);
	अगर (!hअगर_drv)
		वापस -ENOMEM;

	*hअगर_drv_handler = hअगर_drv;

	vअगर->hअगर_drv = hअगर_drv;

	अगर (wilc->clients_count == 0)
		mutex_init(&wilc->deinit_lock);

	समयr_setup(&vअगर->periodic_rssi, get_periodic_rssi, 0);
	mod_समयr(&vअगर->periodic_rssi, jअगरfies + msecs_to_jअगरfies(5000));

	समयr_setup(&hअगर_drv->scan_समयr, समयr_scan_cb, 0);
	समयr_setup(&hअगर_drv->connect_समयr, समयr_connect_cb, 0);
	समयr_setup(&hअगर_drv->reमुख्य_on_ch_समयr, listen_समयr_cb, 0);

	hअगर_drv->hअगर_state = HOST_IF_IDLE;

	hअगर_drv->p2p_समयout = 0;

	wilc->clients_count++;

	वापस 0;
पूर्ण

पूर्णांक wilc_deinit(काष्ठा wilc_vअगर *vअगर)
अणु
	पूर्णांक result = 0;
	काष्ठा host_अगर_drv *hअगर_drv = vअगर->hअगर_drv;

	अगर (!hअगर_drv) अणु
		netdev_err(vअगर->ndev, "%s: hif driver is NULL", __func__);
		वापस -EFAULT;
	पूर्ण

	mutex_lock(&vअगर->wilc->deinit_lock);

	del_समयr_sync(&hअगर_drv->scan_समयr);
	del_समयr_sync(&hअगर_drv->connect_समयr);
	del_समयr_sync(&vअगर->periodic_rssi);
	del_समयr_sync(&hअगर_drv->reमुख्य_on_ch_समयr);

	अगर (hअगर_drv->usr_scan_req.scan_result) अणु
		hअगर_drv->usr_scan_req.scan_result(SCAN_EVENT_ABORTED, शून्य,
						  hअगर_drv->usr_scan_req.arg);
		hअगर_drv->usr_scan_req.scan_result = शून्य;
	पूर्ण

	hअगर_drv->hअगर_state = HOST_IF_IDLE;

	kमुक्त(hअगर_drv);
	vअगर->hअगर_drv = शून्य;
	vअगर->wilc->clients_count--;
	mutex_unlock(&vअगर->wilc->deinit_lock);
	वापस result;
पूर्ण

व्योम wilc_network_info_received(काष्ठा wilc *wilc, u8 *buffer, u32 length)
अणु
	पूर्णांक result;
	काष्ठा host_अगर_msg *msg;
	पूर्णांक id;
	काष्ठा host_अगर_drv *hअगर_drv;
	काष्ठा wilc_vअगर *vअगर;

	id = get_unaligned_le32(&buffer[length - 4]);
	vअगर = wilc_get_vअगर_from_idx(wilc, id);
	अगर (!vअगर)
		वापस;
	hअगर_drv = vअगर->hअगर_drv;

	अगर (!hअगर_drv) अणु
		netdev_err(vअगर->ndev, "driver not init[%p]\n", hअगर_drv);
		वापस;
	पूर्ण

	msg = wilc_alloc_work(vअगर, handle_rcvd_ntwrk_info, false);
	अगर (IS_ERR(msg))
		वापस;

	msg->body.net_info.frame_len = get_unaligned_le16(&buffer[6]) - 1;
	msg->body.net_info.rssi = buffer[8];
	msg->body.net_info.mgmt = kmemdup(&buffer[9],
					  msg->body.net_info.frame_len,
					  GFP_KERNEL);
	अगर (!msg->body.net_info.mgmt) अणु
		kमुक्त(msg);
		वापस;
	पूर्ण

	result = wilc_enqueue_work(msg);
	अगर (result) अणु
		netdev_err(vअगर->ndev, "%s: enqueue work failed\n", __func__);
		kमुक्त(msg->body.net_info.mgmt);
		kमुक्त(msg);
	पूर्ण
पूर्ण

व्योम wilc_gnrl_async_info_received(काष्ठा wilc *wilc, u8 *buffer, u32 length)
अणु
	पूर्णांक result;
	काष्ठा host_अगर_msg *msg;
	पूर्णांक id;
	काष्ठा host_अगर_drv *hअगर_drv;
	काष्ठा wilc_vअगर *vअगर;

	mutex_lock(&wilc->deinit_lock);

	id = get_unaligned_le32(&buffer[length - 4]);
	vअगर = wilc_get_vअगर_from_idx(wilc, id);
	अगर (!vअगर) अणु
		mutex_unlock(&wilc->deinit_lock);
		वापस;
	पूर्ण

	hअगर_drv = vअगर->hअगर_drv;

	अगर (!hअगर_drv) अणु
		mutex_unlock(&wilc->deinit_lock);
		वापस;
	पूर्ण

	अगर (!hअगर_drv->conn_info.conn_result) अणु
		netdev_err(vअगर->ndev, "%s: conn_result is NULL\n", __func__);
		mutex_unlock(&wilc->deinit_lock);
		वापस;
	पूर्ण

	msg = wilc_alloc_work(vअगर, handle_rcvd_gnrl_async_info, false);
	अगर (IS_ERR(msg)) अणु
		mutex_unlock(&wilc->deinit_lock);
		वापस;
	पूर्ण

	msg->body.mac_info.status = buffer[7];
	result = wilc_enqueue_work(msg);
	अगर (result) अणु
		netdev_err(vअगर->ndev, "%s: enqueue work failed\n", __func__);
		kमुक्त(msg);
	पूर्ण

	mutex_unlock(&wilc->deinit_lock);
पूर्ण

व्योम wilc_scan_complete_received(काष्ठा wilc *wilc, u8 *buffer, u32 length)
अणु
	पूर्णांक result;
	पूर्णांक id;
	काष्ठा host_अगर_drv *hअगर_drv;
	काष्ठा wilc_vअगर *vअगर;

	id = get_unaligned_le32(&buffer[length - 4]);
	vअगर = wilc_get_vअगर_from_idx(wilc, id);
	अगर (!vअगर)
		वापस;
	hअगर_drv = vअगर->hअगर_drv;

	अगर (!hअगर_drv)
		वापस;

	अगर (hअगर_drv->usr_scan_req.scan_result) अणु
		काष्ठा host_अगर_msg *msg;

		msg = wilc_alloc_work(vअगर, handle_scan_complete, false);
		अगर (IS_ERR(msg))
			वापस;

		result = wilc_enqueue_work(msg);
		अगर (result) अणु
			netdev_err(vअगर->ndev, "%s: enqueue work failed\n",
				   __func__);
			kमुक्त(msg);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक wilc_reमुख्य_on_channel(काष्ठा wilc_vअगर *vअगर, u64 cookie,
			   u32 duration, u16 chan,
			   व्योम (*expired)(व्योम *, u64),
			   व्योम *user_arg)
अणु
	काष्ठा wilc_reमुख्य_ch roc;
	पूर्णांक result;

	roc.ch = chan;
	roc.expired = expired;
	roc.arg = user_arg;
	roc.duration = duration;
	roc.cookie = cookie;
	result = handle_reमुख्य_on_chan(vअगर, &roc);
	अगर (result)
		netdev_err(vअगर->ndev, "%s: failed to set remain on channel\n",
			   __func__);

	वापस result;
पूर्ण

पूर्णांक wilc_listen_state_expired(काष्ठा wilc_vअगर *vअगर, u64 cookie)
अणु
	अगर (!vअगर->hअगर_drv) अणु
		netdev_err(vअगर->ndev, "%s: hif driver is NULL", __func__);
		वापस -EFAULT;
	पूर्ण

	del_समयr(&vअगर->hअगर_drv->reमुख्य_on_ch_समयr);

	वापस wilc_handle_roc_expired(vअगर, cookie);
पूर्ण

व्योम wilc_frame_रेजिस्टर(काष्ठा wilc_vअगर *vअगर, u16 frame_type, bool reg)
अणु
	काष्ठा wid wid;
	पूर्णांक result;
	काष्ठा wilc_reg_frame reg_frame;

	wid.id = WID_REGISTER_FRAME;
	wid.type = WID_STR;
	wid.size = माप(reg_frame);
	wid.val = (u8 *)&reg_frame;

	स_रखो(&reg_frame, 0x0, माप(reg_frame));

	अगर (reg)
		reg_frame.reg = 1;

	चयन (frame_type) अणु
	हाल IEEE80211_STYPE_ACTION:
		reg_frame.reg_id = WILC_FW_ACTION_FRM_IDX;
		अवरोध;

	हाल IEEE80211_STYPE_PROBE_REQ:
		reg_frame.reg_id = WILC_FW_PROBE_REQ_IDX;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	reg_frame.frame_type = cpu_to_le16(frame_type);
	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to frame register\n");
पूर्ण

पूर्णांक wilc_add_beacon(काष्ठा wilc_vअगर *vअगर, u32 पूर्णांकerval, u32 dtim_period,
		    काष्ठा cfg80211_beacon_data *params)
अणु
	काष्ठा wid wid;
	पूर्णांक result;
	u8 *cur_byte;

	wid.id = WID_ADD_BEACON;
	wid.type = WID_BIN;
	wid.size = params->head_len + params->tail_len + 16;
	wid.val = kzalloc(wid.size, GFP_KERNEL);
	अगर (!wid.val)
		वापस -ENOMEM;

	cur_byte = wid.val;
	put_unaligned_le32(पूर्णांकerval, cur_byte);
	cur_byte += 4;
	put_unaligned_le32(dtim_period, cur_byte);
	cur_byte += 4;
	put_unaligned_le32(params->head_len, cur_byte);
	cur_byte += 4;

	अगर (params->head_len > 0)
		स_नकल(cur_byte, params->head, params->head_len);
	cur_byte += params->head_len;

	put_unaligned_le32(params->tail_len, cur_byte);
	cur_byte += 4;

	अगर (params->tail_len > 0)
		स_नकल(cur_byte, params->tail, params->tail_len);

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to send add beacon\n");

	kमुक्त(wid.val);

	वापस result;
पूर्ण

पूर्णांक wilc_del_beacon(काष्ठा wilc_vअगर *vअगर)
अणु
	पूर्णांक result;
	काष्ठा wid wid;
	u8 del_beacon = 0;

	wid.id = WID_DEL_BEACON;
	wid.type = WID_CHAR;
	wid.size = माप(अक्षर);
	wid.val = &del_beacon;

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to send delete beacon\n");

	वापस result;
पूर्ण

पूर्णांक wilc_add_station(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *mac,
		     काष्ठा station_parameters *params)
अणु
	काष्ठा wid wid;
	पूर्णांक result;
	u8 *cur_byte;

	wid.id = WID_ADD_STA;
	wid.type = WID_BIN;
	wid.size = WILC_ADD_STA_LENGTH + params->supported_rates_len;
	wid.val = kदो_स्मृति(wid.size, GFP_KERNEL);
	अगर (!wid.val)
		वापस -ENOMEM;

	cur_byte = wid.val;
	wilc_hअगर_pack_sta_param(cur_byte, mac, params);

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result != 0)
		netdev_err(vअगर->ndev, "Failed to send add station\n");

	kमुक्त(wid.val);

	वापस result;
पूर्ण

पूर्णांक wilc_del_station(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *mac_addr)
अणु
	काष्ठा wid wid;
	पूर्णांक result;

	wid.id = WID_REMOVE_STA;
	wid.type = WID_BIN;
	wid.size = ETH_ALEN;
	wid.val = kzalloc(wid.size, GFP_KERNEL);
	अगर (!wid.val)
		वापस -ENOMEM;

	अगर (!mac_addr)
		eth_broadcast_addr(wid.val);
	अन्यथा
		ether_addr_copy(wid.val, mac_addr);

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to del station\n");

	kमुक्त(wid.val);

	वापस result;
पूर्ण

पूर्णांक wilc_del_allstation(काष्ठा wilc_vअगर *vअगर, u8 mac_addr[][ETH_ALEN])
अणु
	काष्ठा wid wid;
	पूर्णांक result;
	पूर्णांक i;
	u8 assoc_sta = 0;
	काष्ठा wilc_del_all_sta del_sta;

	स_रखो(&del_sta, 0x0, माप(del_sta));
	क्रम (i = 0; i < WILC_MAX_NUM_STA; i++) अणु
		अगर (!is_zero_ether_addr(mac_addr[i])) अणु
			assoc_sta++;
			ether_addr_copy(del_sta.mac[i], mac_addr[i]);
		पूर्ण
	पूर्ण

	अगर (!assoc_sta)
		वापस 0;

	del_sta.assoc_sta = assoc_sta;

	wid.id = WID_DEL_ALL_STA;
	wid.type = WID_STR;
	wid.size = (assoc_sta * ETH_ALEN) + 1;
	wid.val = (u8 *)&del_sta;

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to send delete all station\n");

	वापस result;
पूर्ण

पूर्णांक wilc_edit_station(काष्ठा wilc_vअगर *vअगर, स्थिर u8 *mac,
		      काष्ठा station_parameters *params)
अणु
	काष्ठा wid wid;
	पूर्णांक result;
	u8 *cur_byte;

	wid.id = WID_EDIT_STA;
	wid.type = WID_BIN;
	wid.size = WILC_ADD_STA_LENGTH + params->supported_rates_len;
	wid.val = kदो_स्मृति(wid.size, GFP_KERNEL);
	अगर (!wid.val)
		वापस -ENOMEM;

	cur_byte = wid.val;
	wilc_hअगर_pack_sta_param(cur_byte, mac, params);

	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to send edit station\n");

	kमुक्त(wid.val);
	वापस result;
पूर्ण

पूर्णांक wilc_set_घातer_mgmt(काष्ठा wilc_vअगर *vअगर, bool enabled, u32 समयout)
अणु
	काष्ठा wid wid;
	पूर्णांक result;
	s8 घातer_mode;

	अगर (enabled)
		घातer_mode = WILC_FW_MIN_FAST_PS;
	अन्यथा
		घातer_mode = WILC_FW_NO_POWERSAVE;

	wid.id = WID_POWER_MANAGEMENT;
	wid.val = &घातer_mode;
	wid.size = माप(अक्षर);
	result = wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
	अगर (result)
		netdev_err(vअगर->ndev, "Failed to send power management\n");

	वापस result;
पूर्ण

पूर्णांक wilc_setup_multicast_filter(काष्ठा wilc_vअगर *vअगर, u32 enabled, u32 count,
				u8 *mc_list)
अणु
	पूर्णांक result;
	काष्ठा host_अगर_msg *msg;

	msg = wilc_alloc_work(vअगर, handle_set_mcast_filter, false);
	अगर (IS_ERR(msg))
		वापस PTR_ERR(msg);

	msg->body.mc_info.enabled = enabled;
	msg->body.mc_info.cnt = count;
	msg->body.mc_info.mc_list = mc_list;

	result = wilc_enqueue_work(msg);
	अगर (result) अणु
		netdev_err(vअगर->ndev, "%s: enqueue work failed\n", __func__);
		kमुक्त(msg);
	पूर्ण
	वापस result;
पूर्ण

पूर्णांक wilc_set_tx_घातer(काष्ठा wilc_vअगर *vअगर, u8 tx_घातer)
अणु
	काष्ठा wid wid;

	wid.id = WID_TX_POWER;
	wid.type = WID_CHAR;
	wid.val = &tx_घातer;
	wid.size = माप(अक्षर);

	वापस wilc_send_config_pkt(vअगर, WILC_SET_CFG, &wid, 1);
पूर्ण

पूर्णांक wilc_get_tx_घातer(काष्ठा wilc_vअगर *vअगर, u8 *tx_घातer)
अणु
	काष्ठा wid wid;

	wid.id = WID_TX_POWER;
	wid.type = WID_CHAR;
	wid.val = tx_घातer;
	wid.size = माप(अक्षर);

	वापस wilc_send_config_pkt(vअगर, WILC_GET_CFG, &wid, 1);
पूर्ण
