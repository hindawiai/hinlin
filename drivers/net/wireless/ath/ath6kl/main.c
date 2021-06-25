<शैली गुरु>
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "core.h"
#समावेश "hif-ops.h"
#समावेश "cfg80211.h"
#समावेश "target.h"
#समावेश "debug.h"

काष्ठा ath6kl_sta *ath6kl_find_sta(काष्ठा ath6kl_vअगर *vअगर, u8 *node_addr)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	काष्ठा ath6kl_sta *conn = शून्य;
	u8 i, max_conn;

	अगर (is_zero_ether_addr(node_addr))
		वापस शून्य;

	max_conn = (vअगर->nw_type == AP_NETWORK) ? AP_MAX_NUM_STA : 0;

	क्रम (i = 0; i < max_conn; i++) अणु
		अगर (स_भेद(node_addr, ar->sta_list[i].mac, ETH_ALEN) == 0) अणु
			conn = &ar->sta_list[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस conn;
पूर्ण

काष्ठा ath6kl_sta *ath6kl_find_sta_by_aid(काष्ठा ath6kl *ar, u8 aid)
अणु
	काष्ठा ath6kl_sta *conn = शून्य;
	u8 ctr;

	क्रम (ctr = 0; ctr < AP_MAX_NUM_STA; ctr++) अणु
		अगर (ar->sta_list[ctr].aid == aid) अणु
			conn = &ar->sta_list[ctr];
			अवरोध;
		पूर्ण
	पूर्ण
	वापस conn;
पूर्ण

अटल व्योम ath6kl_add_new_sta(काष्ठा ath6kl_vअगर *vअगर, u8 *mac, u16 aid,
			       u8 *wpaie, माप_प्रकार ielen, u8 keymgmt,
			       u8 ucipher, u8 auth, u8 apsd_info)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	काष्ठा ath6kl_sta *sta;
	u8 मुक्त_slot;

	मुक्त_slot = aid - 1;

	sta = &ar->sta_list[मुक्त_slot];
	स_नकल(sta->mac, mac, ETH_ALEN);
	अगर (ielen <= ATH6KL_MAX_IE)
		स_नकल(sta->wpa_ie, wpaie, ielen);
	sta->aid = aid;
	sta->keymgmt = keymgmt;
	sta->ucipher = ucipher;
	sta->auth = auth;
	sta->apsd_info = apsd_info;

	ar->sta_list_index = ar->sta_list_index | (1 << मुक्त_slot);
	ar->ap_stats.sta[मुक्त_slot].aid = cpu_to_le32(aid);
	aggr_conn_init(vअगर, vअगर->aggr_cntxt, sta->aggr_conn);
पूर्ण

अटल व्योम ath6kl_sta_cleanup(काष्ठा ath6kl *ar, u8 i)
अणु
	काष्ठा ath6kl_sta *sta = &ar->sta_list[i];
	काष्ठा ath6kl_mgmt_buff *entry, *पंचांगp;

	/* empty the queued pkts in the PS queue अगर any */
	spin_lock_bh(&sta->psq_lock);
	skb_queue_purge(&sta->psq);
	skb_queue_purge(&sta->apsdq);

	अगर (sta->mgmt_psq_len != 0) अणु
		list_क्रम_each_entry_safe(entry, पंचांगp, &sta->mgmt_psq, list) अणु
			kमुक्त(entry);
		पूर्ण
		INIT_LIST_HEAD(&sta->mgmt_psq);
		sta->mgmt_psq_len = 0;
	पूर्ण

	spin_unlock_bh(&sta->psq_lock);

	स_रखो(&ar->ap_stats.sta[sta->aid - 1], 0,
	       माप(काष्ठा wmi_per_sta_stat));
	eth_zero_addr(sta->mac);
	स_रखो(sta->wpa_ie, 0, ATH6KL_MAX_IE);
	sta->aid = 0;
	sta->sta_flags = 0;

	ar->sta_list_index = ar->sta_list_index & ~(1 << i);
	aggr_reset_state(sta->aggr_conn);
पूर्ण

अटल u8 ath6kl_हटाओ_sta(काष्ठा ath6kl *ar, u8 *mac, u16 reason)
अणु
	u8 i, हटाओd = 0;

	अगर (is_zero_ether_addr(mac))
		वापस हटाओd;

	अगर (is_broadcast_ether_addr(mac)) अणु
		ath6kl_dbg(ATH6KL_DBG_TRC, "deleting all station\n");

		क्रम (i = 0; i < AP_MAX_NUM_STA; i++) अणु
			अगर (!is_zero_ether_addr(ar->sta_list[i].mac)) अणु
				ath6kl_sta_cleanup(ar, i);
				हटाओd = 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < AP_MAX_NUM_STA; i++) अणु
			अगर (स_भेद(ar->sta_list[i].mac, mac, ETH_ALEN) == 0) अणु
				ath6kl_dbg(ATH6KL_DBG_TRC,
					   "deleting station %pM aid=%d reason=%d\n",
					   mac, ar->sta_list[i].aid, reason);
				ath6kl_sta_cleanup(ar, i);
				हटाओd = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस हटाओd;
पूर्ण

क्रमागत htc_endpoपूर्णांक_id ath6kl_ac2_endpoपूर्णांक_id(व्योम *devt, u8 ac)
अणु
	काष्ठा ath6kl *ar = devt;
	वापस ar->ac2ep_map[ac];
पूर्ण

काष्ठा ath6kl_cookie *ath6kl_alloc_cookie(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_cookie *cookie;

	cookie = ar->cookie_list;
	अगर (cookie != शून्य) अणु
		ar->cookie_list = cookie->arc_list_next;
		ar->cookie_count--;
	पूर्ण

	वापस cookie;
पूर्ण

व्योम ath6kl_cookie_init(काष्ठा ath6kl *ar)
अणु
	u32 i;

	ar->cookie_list = शून्य;
	ar->cookie_count = 0;

	स_रखो(ar->cookie_mem, 0, माप(ar->cookie_mem));

	क्रम (i = 0; i < MAX_COOKIE_NUM; i++)
		ath6kl_मुक्त_cookie(ar, &ar->cookie_mem[i]);
पूर्ण

व्योम ath6kl_cookie_cleanup(काष्ठा ath6kl *ar)
अणु
	ar->cookie_list = शून्य;
	ar->cookie_count = 0;
पूर्ण

व्योम ath6kl_मुक्त_cookie(काष्ठा ath6kl *ar, काष्ठा ath6kl_cookie *cookie)
अणु
	/* Insert first */

	अगर (!ar || !cookie)
		वापस;

	cookie->arc_list_next = ar->cookie_list;
	ar->cookie_list = cookie;
	ar->cookie_count++;
पूर्ण

/*
 * Read from the hardware through its diagnostic winकरोw. No cooperation
 * from the firmware is required क्रम this.
 */
पूर्णांक ath6kl_diag_पढ़ो32(काष्ठा ath6kl *ar, u32 address, u32 *value)
अणु
	पूर्णांक ret;

	ret = ath6kl_hअगर_diag_पढ़ो32(ar, address, value);
	अगर (ret) अणु
		ath6kl_warn("failed to read32 through diagnose window: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Write to the ATH6KL through its diagnostic winकरोw. No cooperation from
 * the Target is required क्रम this.
 */
पूर्णांक ath6kl_diag_ग_लिखो32(काष्ठा ath6kl *ar, u32 address, __le32 value)
अणु
	पूर्णांक ret;

	ret = ath6kl_hअगर_diag_ग_लिखो32(ar, address, value);

	अगर (ret) अणु
		ath6kl_err("failed to write 0x%x during diagnose window to 0x%x\n",
			   address, value);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath6kl_diag_पढ़ो(काष्ठा ath6kl *ar, u32 address, व्योम *data, u32 length)
अणु
	u32 count, *buf = data;
	पूर्णांक ret;

	अगर (WARN_ON(length % 4))
		वापस -EINVAL;

	क्रम (count = 0; count < length / 4; count++, address += 4) अणु
		ret = ath6kl_diag_पढ़ो32(ar, address, &buf[count]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath6kl_diag_ग_लिखो(काष्ठा ath6kl *ar, u32 address, व्योम *data, u32 length)
अणु
	u32 count;
	__le32 *buf = data;
	पूर्णांक ret;

	अगर (WARN_ON(length % 4))
		वापस -EINVAL;

	क्रम (count = 0; count < length / 4; count++, address += 4) अणु
		ret = ath6kl_diag_ग_लिखो32(ar, address, buf[count]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath6kl_पढ़ो_fwlogs(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_dbglog_hdr debug_hdr;
	काष्ठा ath6kl_dbglog_buf debug_buf;
	u32 address, length, firstbuf, debug_hdr_addr;
	पूर्णांक ret, loop;
	u8 *buf;

	buf = kदो_स्मृति(ATH6KL_FWLOG_PAYLOAD_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	address = TARG_VTOP(ar->target_type,
			    ath6kl_get_hi_item_addr(ar,
						    HI_ITEM(hi_dbglog_hdr)));

	ret = ath6kl_diag_पढ़ो32(ar, address, &debug_hdr_addr);
	अगर (ret)
		जाओ out;

	/* Get the contents of the ring buffer */
	अगर (debug_hdr_addr == 0) अणु
		ath6kl_warn("Invalid address for debug_hdr_addr\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	address = TARG_VTOP(ar->target_type, debug_hdr_addr);
	ret = ath6kl_diag_पढ़ो(ar, address, &debug_hdr, माप(debug_hdr));
	अगर (ret)
		जाओ out;

	address = TARG_VTOP(ar->target_type,
			    le32_to_cpu(debug_hdr.dbuf_addr));
	firstbuf = address;
	ret = ath6kl_diag_पढ़ो(ar, address, &debug_buf, माप(debug_buf));
	अगर (ret)
		जाओ out;

	loop = 100;

	करो अणु
		address = TARG_VTOP(ar->target_type,
				    le32_to_cpu(debug_buf.buffer_addr));
		length = le32_to_cpu(debug_buf.length);

		अगर (length != 0 && (le32_to_cpu(debug_buf.length) <=
				    le32_to_cpu(debug_buf.bufsize))) अणु
			length = ALIGN(length, 4);

			ret = ath6kl_diag_पढ़ो(ar, address,
					       buf, length);
			अगर (ret)
				जाओ out;

			ath6kl_debug_fwlog_event(ar, buf, length);
		पूर्ण

		address = TARG_VTOP(ar->target_type,
				    le32_to_cpu(debug_buf.next));
		ret = ath6kl_diag_पढ़ो(ar, address, &debug_buf,
				       माप(debug_buf));
		अगर (ret)
			जाओ out;

		loop--;

		अगर (WARN_ON(loop == 0)) अणु
			ret = -ETIMEDOUT;
			जाओ out;
		पूर्ण
	पूर्ण जबतक (address != firstbuf);

out:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल व्योम ath6kl_install_अटल_wep_keys(काष्ठा ath6kl_vअगर *vअगर)
अणु
	u8 index;
	u8 keyusage;

	क्रम (index = 0; index <= WMI_MAX_KEY_INDEX; index++) अणु
		अगर (vअगर->wep_key_list[index].key_len) अणु
			keyusage = GROUP_USAGE;
			अगर (index == vअगर->def_txkey_index)
				keyusage |= TX_USAGE;

			ath6kl_wmi_addkey_cmd(vअगर->ar->wmi, vअगर->fw_vअगर_idx,
					      index,
					      WEP_CRYPT,
					      keyusage,
					      vअगर->wep_key_list[index].key_len,
					      शून्य, 0,
					      vअगर->wep_key_list[index].key,
					      KEY_OP_INIT_VAL, शून्य,
					      NO_SYNC_WMIFLAG);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ath6kl_connect_ap_mode_bss(काष्ठा ath6kl_vअगर *vअगर, u16 channel)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	काष्ठा ath6kl_req_key *ik;
	पूर्णांक res;
	u8 key_rsc[ATH6KL_KEY_SEQ_LEN];

	ik = &ar->ap_mode_bkey;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "AP mode started on %u MHz\n", channel);

	चयन (vअगर->auth_mode) अणु
	हाल NONE_AUTH:
		अगर (vअगर->prwise_crypto == WEP_CRYPT)
			ath6kl_install_अटल_wep_keys(vअगर);
		अगर (!ik->valid || ik->key_type != WAPI_CRYPT)
			अवरोध;
		/* क्रम WAPI, we need to set the delayed group key, जारी: */
		fallthrough;
	हाल WPA_PSK_AUTH:
	हाल WPA2_PSK_AUTH:
	हाल (WPA_PSK_AUTH | WPA2_PSK_AUTH):
		अगर (!ik->valid)
			अवरोध;

		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
			   "Delayed addkey for the initial group key for AP mode\n");
		स_रखो(key_rsc, 0, माप(key_rsc));
		res = ath6kl_wmi_addkey_cmd(
			ar->wmi, vअगर->fw_vअगर_idx, ik->key_index, ik->key_type,
			GROUP_USAGE, ik->key_len, key_rsc, ATH6KL_KEY_SEQ_LEN,
			ik->key,
			KEY_OP_INIT_VAL, शून्य, SYNC_BOTH_WMIFLAG);
		अगर (res) अणु
			ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
				   "Delayed addkey failed: %d\n", res);
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (ar->last_ch != channel)
		/* we actually करोn't know the phymode, शेष to HT20 */
		ath6kl_cfg80211_ch_चयन_notअगरy(vअगर, channel, WMI_11G_HT20);

	ath6kl_wmi_bssfilter_cmd(ar->wmi, vअगर->fw_vअगर_idx, NONE_BSS_FILTER, 0);
	set_bit(CONNECTED, &vअगर->flags);
	netअगर_carrier_on(vअगर->ndev);
पूर्ण

व्योम ath6kl_connect_ap_mode_sta(काष्ठा ath6kl_vअगर *vअगर, u16 aid, u8 *mac_addr,
				u8 keymgmt, u8 ucipher, u8 auth,
				u8 assoc_req_len, u8 *assoc_info, u8 apsd_info)
अणु
	u8 *ies = शून्य, *wpa_ie = शून्य, *pos;
	माप_प्रकार ies_len = 0;
	काष्ठा station_info *sinfo;

	ath6kl_dbg(ATH6KL_DBG_TRC, "new station %pM aid=%d\n", mac_addr, aid);

	अगर (aid < 1 || aid > AP_MAX_NUM_STA)
		वापस;

	अगर (assoc_req_len > माप(काष्ठा ieee80211_hdr_3addr)) अणु
		काष्ठा ieee80211_mgmt *mgmt =
			(काष्ठा ieee80211_mgmt *) assoc_info;
		अगर (ieee80211_is_assoc_req(mgmt->frame_control) &&
		    assoc_req_len >= माप(काष्ठा ieee80211_hdr_3addr) +
		    माप(mgmt->u.assoc_req)) अणु
			ies = mgmt->u.assoc_req.variable;
			ies_len = assoc_info + assoc_req_len - ies;
		पूर्ण अन्यथा अगर (ieee80211_is_reassoc_req(mgmt->frame_control) &&
			   assoc_req_len >= माप(काष्ठा ieee80211_hdr_3addr)
			   + माप(mgmt->u.reassoc_req)) अणु
			ies = mgmt->u.reassoc_req.variable;
			ies_len = assoc_info + assoc_req_len - ies;
		पूर्ण
	पूर्ण

	pos = ies;
	जबतक (pos && pos + 1 < ies + ies_len) अणु
		अगर (pos + 2 + pos[1] > ies + ies_len)
			अवरोध;
		अगर (pos[0] == WLAN_EID_RSN)
			wpa_ie = pos; /* RSN IE */
		अन्यथा अगर (pos[0] == WLAN_EID_VENDOR_SPECIFIC &&
			 pos[1] >= 4 &&
			 pos[2] == 0x00 && pos[3] == 0x50 && pos[4] == 0xf2) अणु
			अगर (pos[5] == 0x01)
				wpa_ie = pos; /* WPA IE */
			अन्यथा अगर (pos[5] == 0x04) अणु
				wpa_ie = pos; /* WPS IE */
				अवरोध; /* overrides WPA/RSN IE */
			पूर्ण
		पूर्ण अन्यथा अगर (pos[0] == 0x44 && wpa_ie == शून्य) अणु
			/*
			 * Note: WAPI Parameter Set IE re-uses Element ID that
			 * was officially allocated क्रम BSS AC Access Delay. As
			 * such, we need to be a bit more careful on when
			 * parsing the frame. However, BSS AC Access Delay
			 * element is not supposed to be included in
			 * (Re)Association Request frames, so this should not
			 * cause problems.
			 */
			wpa_ie = pos; /* WAPI IE */
			अवरोध;
		पूर्ण
		pos += 2 + pos[1];
	पूर्ण

	ath6kl_add_new_sta(vअगर, mac_addr, aid, wpa_ie,
			   wpa_ie ? 2 + wpa_ie[1] : 0,
			   keymgmt, ucipher, auth, apsd_info);

	/* send event to application */
	sinfo = kzalloc(माप(*sinfo), GFP_KERNEL);
	अगर (!sinfo)
		वापस;

	/* TODO: sinfo.generation */

	sinfo->assoc_req_ies = ies;
	sinfo->assoc_req_ies_len = ies_len;

	cfg80211_new_sta(vअगर->ndev, mac_addr, sinfo, GFP_KERNEL);

	netअगर_wake_queue(vअगर->ndev);

	kमुक्त(sinfo);
पूर्ण

व्योम disconnect_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा ath6kl_vअगर *vअगर = from_समयr(vअगर, t, disconnect_समयr);

	ath6kl_init_profile_info(vअगर);
	ath6kl_disconnect(vअगर);
पूर्ण

व्योम ath6kl_disconnect(काष्ठा ath6kl_vअगर *vअगर)
अणु
	अगर (test_bit(CONNECTED, &vअगर->flags) ||
	    test_bit(CONNECT_PEND, &vअगर->flags)) अणु
		ath6kl_wmi_disconnect_cmd(vअगर->ar->wmi, vअगर->fw_vअगर_idx);
		/*
		 * Disconnect command is issued, clear the connect pending
		 * flag. The connected flag will be cleared in
		 * disconnect event notअगरication.
		 */
		clear_bit(CONNECT_PEND, &vअगर->flags);
	पूर्ण
पूर्ण

/* WMI Event handlers */

व्योम ath6kl_पढ़ोy_event(व्योम *devt, u8 *datap, u32 sw_ver, u32 abi_ver,
			क्रमागत wmi_phy_cap cap)
अणु
	काष्ठा ath6kl *ar = devt;

	स_नकल(ar->mac_addr, datap, ETH_ALEN);

	ath6kl_dbg(ATH6KL_DBG_BOOT,
		   "ready event mac addr %pM sw_ver 0x%x abi_ver 0x%x cap 0x%x\n",
		   ar->mac_addr, sw_ver, abi_ver, cap);

	ar->version.wlan_ver = sw_ver;
	ar->version.abi_ver = abi_ver;
	ar->hw.cap = cap;

	अगर (म_माप(ar->wiphy->fw_version) == 0) अणु
		snम_लिखो(ar->wiphy->fw_version,
			 माप(ar->wiphy->fw_version),
			 "%u.%u.%u.%u",
			 (ar->version.wlan_ver & 0xf0000000) >> 28,
			 (ar->version.wlan_ver & 0x0f000000) >> 24,
			 (ar->version.wlan_ver & 0x00ff0000) >> 16,
			 (ar->version.wlan_ver & 0x0000ffff));
	पूर्ण

	/* indicate to the रुकोing thपढ़ो that the पढ़ोy event was received */
	set_bit(WMI_READY, &ar->flag);
	wake_up(&ar->event_wq);
पूर्ण

व्योम ath6kl_scan_complete_evt(काष्ठा ath6kl_vअगर *vअगर, पूर्णांक status)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	bool पातed = false;

	अगर (status != WMI_SCAN_STATUS_SUCCESS)
		पातed = true;

	ath6kl_cfg80211_scan_complete_event(vअगर, पातed);

	अगर (!ar->usr_bss_filter) अणु
		clear_bit(CLEAR_BSSFILTER_ON_BEACON, &vअगर->flags);
		ath6kl_wmi_bssfilter_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					 NONE_BSS_FILTER, 0);
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "scan complete: %d\n", status);
पूर्ण

अटल पूर्णांक ath6kl_commit_ch_चयन(काष्ठा ath6kl_vअगर *vअगर, u16 channel)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;

	vअगर->profile.ch = cpu_to_le16(channel);

	चयन (vअगर->nw_type) अणु
	हाल AP_NETWORK:
		/*
		 * reconfigure any saved RSN IE capabilites in the beacon /
		 * probe response to stay in sync with the supplicant.
		 */
		अगर (vअगर->rsn_capab &&
		    test_bit(ATH6KL_FW_CAPABILITY_RSN_CAP_OVERRIDE,
			     ar->fw_capabilities))
			ath6kl_wmi_set_ie_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					      WLAN_EID_RSN, WMI_RSN_IE_CAPB,
					      (स्थिर u8 *) &vअगर->rsn_capab,
					      माप(vअगर->rsn_capab));

		वापस ath6kl_wmi_ap_profile_commit(ar->wmi, vअगर->fw_vअगर_idx,
						    &vअगर->profile);
	शेष:
		ath6kl_err("won't switch channels nw_type=%d\n", vअगर->nw_type);
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम ath6kl_check_ch_चयन(काष्ठा ath6kl *ar, u16 channel)
अणु
	काष्ठा ath6kl_vअगर *vअगर;
	पूर्णांक res = 0;

	अगर (!ar->want_ch_चयन)
		वापस;

	spin_lock_bh(&ar->list_lock);
	list_क्रम_each_entry(vअगर, &ar->vअगर_list, list) अणु
		अगर (ar->want_ch_चयन & (1 << vअगर->fw_vअगर_idx))
			res = ath6kl_commit_ch_चयन(vअगर, channel);

		/* अगर channel चयन failed, oh well we tried */
		ar->want_ch_चयन &= ~(1 << vअगर->fw_vअगर_idx);

		अगर (res)
			ath6kl_err("channel switch failed nw_type %d res %d\n",
				   vअगर->nw_type, res);
	पूर्ण
	spin_unlock_bh(&ar->list_lock);
पूर्ण

व्योम ath6kl_connect_event(काष्ठा ath6kl_vअगर *vअगर, u16 channel, u8 *bssid,
			  u16 listen_पूर्णांक, u16 beacon_पूर्णांक,
			  क्रमागत network_type net_type, u8 beacon_ie_len,
			  u8 assoc_req_len, u8 assoc_resp_len,
			  u8 *assoc_info)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;

	ath6kl_cfg80211_connect_event(vअगर, channel, bssid,
				      listen_पूर्णांक, beacon_पूर्णांक,
				      net_type, beacon_ie_len,
				      assoc_req_len, assoc_resp_len,
				      assoc_info);

	स_नकल(vअगर->bssid, bssid, माप(vअगर->bssid));
	vअगर->bss_ch = channel;

	अगर (vअगर->nw_type == INFRA_NETWORK) अणु
		ath6kl_wmi_listenपूर्णांकerval_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					      vअगर->listen_पूर्णांकvl_t, 0);
		ath6kl_check_ch_चयन(ar, channel);
	पूर्ण

	netअगर_wake_queue(vअगर->ndev);

	/* Update connect & link status atomically */
	spin_lock_bh(&vअगर->अगर_lock);
	set_bit(CONNECTED, &vअगर->flags);
	clear_bit(CONNECT_PEND, &vअगर->flags);
	netअगर_carrier_on(vअगर->ndev);
	spin_unlock_bh(&vअगर->अगर_lock);

	aggr_reset_state(vअगर->aggr_cntxt->aggr_conn);
	vअगर->reconnect_flag = 0;

	अगर ((vअगर->nw_type == ADHOC_NETWORK) && ar->ibss_ps_enable) अणु
		स_रखो(ar->node_map, 0, माप(ar->node_map));
		ar->node_num = 0;
		ar->next_ep_id = ENDPOINT_2;
	पूर्ण

	अगर (!ar->usr_bss_filter) अणु
		set_bit(CLEAR_BSSFILTER_ON_BEACON, &vअगर->flags);
		ath6kl_wmi_bssfilter_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					 CURRENT_BSS_FILTER, 0);
	पूर्ण
पूर्ण

व्योम ath6kl_tkip_micerr_event(काष्ठा ath6kl_vअगर *vअगर, u8 keyid, bool ismcast)
अणु
	काष्ठा ath6kl_sta *sta;
	काष्ठा ath6kl *ar = vअगर->ar;
	u8 tsc[6];

	/*
	 * For AP हाल, keyid will have aid of STA which sent pkt with
	 * MIC error. Use this aid to get MAC & send it to hostapd.
	 */
	अगर (vअगर->nw_type == AP_NETWORK) अणु
		sta = ath6kl_find_sta_by_aid(ar, (keyid >> 2));
		अगर (!sta)
			वापस;

		ath6kl_dbg(ATH6KL_DBG_TRC,
			   "ap tkip mic error received from aid=%d\n", keyid);

		स_रखो(tsc, 0, माप(tsc)); /* FIX: get correct TSC */
		cfg80211_michael_mic_failure(vअगर->ndev, sta->mac,
					     NL80211_KEYTYPE_PAIRWISE, keyid,
					     tsc, GFP_KERNEL);
	पूर्ण अन्यथा अणु
		ath6kl_cfg80211_tkip_micerr_event(vअगर, keyid, ismcast);
	पूर्ण
पूर्ण

अटल व्योम ath6kl_update_target_stats(काष्ठा ath6kl_vअगर *vअगर, u8 *ptr, u32 len)
अणु
	काष्ठा wmi_target_stats *tgt_stats =
		(काष्ठा wmi_target_stats *) ptr;
	काष्ठा ath6kl *ar = vअगर->ar;
	काष्ठा target_stats *stats = &vअगर->target_stats;
	काष्ठा tkip_ccmp_stats *ccmp_stats;
	s32 rate;
	u8 ac;

	अगर (len < माप(*tgt_stats))
		वापस;

	ath6kl_dbg(ATH6KL_DBG_TRC, "updating target stats\n");

	stats->tx_pkt += le32_to_cpu(tgt_stats->stats.tx.pkt);
	stats->tx_byte += le32_to_cpu(tgt_stats->stats.tx.byte);
	stats->tx_ucast_pkt += le32_to_cpu(tgt_stats->stats.tx.ucast_pkt);
	stats->tx_ucast_byte += le32_to_cpu(tgt_stats->stats.tx.ucast_byte);
	stats->tx_mcast_pkt += le32_to_cpu(tgt_stats->stats.tx.mcast_pkt);
	stats->tx_mcast_byte += le32_to_cpu(tgt_stats->stats.tx.mcast_byte);
	stats->tx_bcast_pkt  += le32_to_cpu(tgt_stats->stats.tx.bcast_pkt);
	stats->tx_bcast_byte += le32_to_cpu(tgt_stats->stats.tx.bcast_byte);
	stats->tx_rts_success_cnt +=
		le32_to_cpu(tgt_stats->stats.tx.rts_success_cnt);

	क्रम (ac = 0; ac < WMM_NUM_AC; ac++)
		stats->tx_pkt_per_ac[ac] +=
			le32_to_cpu(tgt_stats->stats.tx.pkt_per_ac[ac]);

	stats->tx_err += le32_to_cpu(tgt_stats->stats.tx.err);
	stats->tx_fail_cnt += le32_to_cpu(tgt_stats->stats.tx.fail_cnt);
	stats->tx_retry_cnt += le32_to_cpu(tgt_stats->stats.tx.retry_cnt);
	stats->tx_mult_retry_cnt +=
		le32_to_cpu(tgt_stats->stats.tx.mult_retry_cnt);
	stats->tx_rts_fail_cnt +=
		le32_to_cpu(tgt_stats->stats.tx.rts_fail_cnt);

	rate = a_sle32_to_cpu(tgt_stats->stats.tx.ucast_rate);
	stats->tx_ucast_rate = ath6kl_wmi_get_rate(ar->wmi, rate);

	stats->rx_pkt += le32_to_cpu(tgt_stats->stats.rx.pkt);
	stats->rx_byte += le32_to_cpu(tgt_stats->stats.rx.byte);
	stats->rx_ucast_pkt += le32_to_cpu(tgt_stats->stats.rx.ucast_pkt);
	stats->rx_ucast_byte += le32_to_cpu(tgt_stats->stats.rx.ucast_byte);
	stats->rx_mcast_pkt += le32_to_cpu(tgt_stats->stats.rx.mcast_pkt);
	stats->rx_mcast_byte += le32_to_cpu(tgt_stats->stats.rx.mcast_byte);
	stats->rx_bcast_pkt += le32_to_cpu(tgt_stats->stats.rx.bcast_pkt);
	stats->rx_bcast_byte += le32_to_cpu(tgt_stats->stats.rx.bcast_byte);
	stats->rx_frgment_pkt += le32_to_cpu(tgt_stats->stats.rx.frgment_pkt);
	stats->rx_err += le32_to_cpu(tgt_stats->stats.rx.err);
	stats->rx_crc_err += le32_to_cpu(tgt_stats->stats.rx.crc_err);
	stats->rx_key_cache_miss +=
		le32_to_cpu(tgt_stats->stats.rx.key_cache_miss);
	stats->rx_decrypt_err += le32_to_cpu(tgt_stats->stats.rx.decrypt_err);
	stats->rx_dupl_frame += le32_to_cpu(tgt_stats->stats.rx.dupl_frame);

	rate = a_sle32_to_cpu(tgt_stats->stats.rx.ucast_rate);
	stats->rx_ucast_rate = ath6kl_wmi_get_rate(ar->wmi, rate);

	ccmp_stats = &tgt_stats->stats.tkip_ccmp_stats;

	stats->tkip_local_mic_fail +=
		le32_to_cpu(ccmp_stats->tkip_local_mic_fail);
	stats->tkip_cnter_measures_invoked +=
		le32_to_cpu(ccmp_stats->tkip_cnter_measures_invoked);
	stats->tkip_fmt_err += le32_to_cpu(ccmp_stats->tkip_fmt_err);

	stats->ccmp_fmt_err += le32_to_cpu(ccmp_stats->ccmp_fmt_err);
	stats->ccmp_replays += le32_to_cpu(ccmp_stats->ccmp_replays);

	stats->pwr_save_fail_cnt +=
		le32_to_cpu(tgt_stats->pm_stats.pwr_save_failure_cnt);
	stats->noise_न्यूनमान_calib =
		a_sle32_to_cpu(tgt_stats->noise_न्यूनमान_calib);

	stats->cs_bmiss_cnt +=
		le32_to_cpu(tgt_stats->cserv_stats.cs_bmiss_cnt);
	stats->cs_low_rssi_cnt +=
		le32_to_cpu(tgt_stats->cserv_stats.cs_low_rssi_cnt);
	stats->cs_connect_cnt +=
		le16_to_cpu(tgt_stats->cserv_stats.cs_connect_cnt);
	stats->cs_discon_cnt +=
		le16_to_cpu(tgt_stats->cserv_stats.cs_discon_cnt);

	stats->cs_ave_beacon_rssi =
		a_sle16_to_cpu(tgt_stats->cserv_stats.cs_ave_beacon_rssi);

	stats->cs_last_roam_msec =
		tgt_stats->cserv_stats.cs_last_roam_msec;
	stats->cs_snr = tgt_stats->cserv_stats.cs_snr;
	stats->cs_rssi = a_sle16_to_cpu(tgt_stats->cserv_stats.cs_rssi);

	stats->lq_val = le32_to_cpu(tgt_stats->lq_val);

	stats->wow_pkt_dropped +=
		le32_to_cpu(tgt_stats->wow_stats.wow_pkt_dropped);
	stats->wow_host_pkt_wakeups +=
		tgt_stats->wow_stats.wow_host_pkt_wakeups;
	stats->wow_host_evt_wakeups +=
		tgt_stats->wow_stats.wow_host_evt_wakeups;
	stats->wow_evt_discarded +=
		le16_to_cpu(tgt_stats->wow_stats.wow_evt_discarded);

	stats->arp_received = le32_to_cpu(tgt_stats->arp_stats.arp_received);
	stats->arp_replied = le32_to_cpu(tgt_stats->arp_stats.arp_replied);
	stats->arp_matched = le32_to_cpu(tgt_stats->arp_stats.arp_matched);

	अगर (test_bit(STATS_UPDATE_PEND, &vअगर->flags)) अणु
		clear_bit(STATS_UPDATE_PEND, &vअगर->flags);
		wake_up(&ar->event_wq);
	पूर्ण
पूर्ण

अटल व्योम ath6kl_add_le32(__le32 *var, __le32 val)
अणु
	*var = cpu_to_le32(le32_to_cpu(*var) + le32_to_cpu(val));
पूर्ण

व्योम ath6kl_tgt_stats_event(काष्ठा ath6kl_vअगर *vअगर, u8 *ptr, u32 len)
अणु
	काष्ठा wmi_ap_mode_stat *p = (काष्ठा wmi_ap_mode_stat *) ptr;
	काष्ठा ath6kl *ar = vअगर->ar;
	काष्ठा wmi_ap_mode_stat *ap = &ar->ap_stats;
	काष्ठा wmi_per_sta_stat *st_ap, *st_p;
	u8 ac;

	अगर (vअगर->nw_type == AP_NETWORK) अणु
		अगर (len < माप(*p))
			वापस;

		क्रम (ac = 0; ac < AP_MAX_NUM_STA; ac++) अणु
			st_ap = &ap->sta[ac];
			st_p = &p->sta[ac];

			ath6kl_add_le32(&st_ap->tx_bytes, st_p->tx_bytes);
			ath6kl_add_le32(&st_ap->tx_pkts, st_p->tx_pkts);
			ath6kl_add_le32(&st_ap->tx_error, st_p->tx_error);
			ath6kl_add_le32(&st_ap->tx_discard, st_p->tx_discard);
			ath6kl_add_le32(&st_ap->rx_bytes, st_p->rx_bytes);
			ath6kl_add_le32(&st_ap->rx_pkts, st_p->rx_pkts);
			ath6kl_add_le32(&st_ap->rx_error, st_p->rx_error);
			ath6kl_add_le32(&st_ap->rx_discard, st_p->rx_discard);
		पूर्ण

	पूर्ण अन्यथा अणु
		ath6kl_update_target_stats(vअगर, ptr, len);
	पूर्ण
पूर्ण

व्योम ath6kl_wakeup_event(व्योम *dev)
अणु
	काष्ठा ath6kl *ar = (काष्ठा ath6kl *) dev;

	wake_up(&ar->event_wq);
पूर्ण

व्योम ath6kl_txpwr_rx_evt(व्योम *devt, u8 tx_pwr)
अणु
	काष्ठा ath6kl *ar = (काष्ठा ath6kl *) devt;

	ar->tx_pwr = tx_pwr;
	wake_up(&ar->event_wq);
पूर्ण

व्योम ath6kl_pspoll_event(काष्ठा ath6kl_vअगर *vअगर, u8 aid)
अणु
	काष्ठा ath6kl_sta *conn;
	काष्ठा sk_buff *skb;
	bool psq_empty = false;
	काष्ठा ath6kl *ar = vअगर->ar;
	काष्ठा ath6kl_mgmt_buff *mgmt_buf;

	conn = ath6kl_find_sta_by_aid(ar, aid);

	अगर (!conn)
		वापस;
	/*
	 * Send out a packet queued on ps queue. When the ps queue
	 * becomes empty update the PVB क्रम this station.
	 */
	spin_lock_bh(&conn->psq_lock);
	psq_empty  = skb_queue_empty(&conn->psq) && (conn->mgmt_psq_len == 0);
	spin_unlock_bh(&conn->psq_lock);

	अगर (psq_empty)
		/* TODO: Send out a शून्य data frame */
		वापस;

	spin_lock_bh(&conn->psq_lock);
	अगर (conn->mgmt_psq_len > 0) अणु
		mgmt_buf = list_first_entry(&conn->mgmt_psq,
					काष्ठा ath6kl_mgmt_buff, list);
		list_del(&mgmt_buf->list);
		conn->mgmt_psq_len--;
		spin_unlock_bh(&conn->psq_lock);

		conn->sta_flags |= STA_PS_POLLED;
		ath6kl_wmi_send_mgmt_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					 mgmt_buf->id, mgmt_buf->freq,
					 mgmt_buf->रुको, mgmt_buf->buf,
					 mgmt_buf->len, mgmt_buf->no_cck);
		conn->sta_flags &= ~STA_PS_POLLED;
		kमुक्त(mgmt_buf);
	पूर्ण अन्यथा अणु
		skb = skb_dequeue(&conn->psq);
		spin_unlock_bh(&conn->psq_lock);

		conn->sta_flags |= STA_PS_POLLED;
		ath6kl_data_tx(skb, vअगर->ndev);
		conn->sta_flags &= ~STA_PS_POLLED;
	पूर्ण

	spin_lock_bh(&conn->psq_lock);
	psq_empty  = skb_queue_empty(&conn->psq) && (conn->mgmt_psq_len == 0);
	spin_unlock_bh(&conn->psq_lock);

	अगर (psq_empty)
		ath6kl_wmi_set_pvb_cmd(ar->wmi, vअगर->fw_vअगर_idx, conn->aid, 0);
पूर्ण

व्योम ath6kl_dसमयxpiry_event(काष्ठा ath6kl_vअगर *vअगर)
अणु
	bool mcastq_empty = false;
	काष्ठा sk_buff *skb;
	काष्ठा ath6kl *ar = vअगर->ar;

	/*
	 * If there are no associated STAs, ignore the DTIM expiry event.
	 * There can be potential race conditions where the last associated
	 * STA may disconnect & beक्रमe the host could clear the 'Indicate
	 * DTIM' request to the firmware, the firmware would have just
	 * indicated a DTIM expiry event. The race is between 'clear DTIM
	 * expiry cmd' going from the host to the firmware & the DTIM
	 * expiry event happening from the firmware to the host.
	 */
	अगर (!ar->sta_list_index)
		वापस;

	spin_lock_bh(&ar->mcastpsq_lock);
	mcastq_empty = skb_queue_empty(&ar->mcastpsq);
	spin_unlock_bh(&ar->mcastpsq_lock);

	अगर (mcastq_empty)
		वापस;

	/* set the STA flag to dtim_expired क्रम the frame to go out */
	set_bit(DTIM_EXPIRED, &vअगर->flags);

	spin_lock_bh(&ar->mcastpsq_lock);
	जबतक ((skb = skb_dequeue(&ar->mcastpsq)) != शून्य) अणु
		spin_unlock_bh(&ar->mcastpsq_lock);

		ath6kl_data_tx(skb, vअगर->ndev);

		spin_lock_bh(&ar->mcastpsq_lock);
	पूर्ण
	spin_unlock_bh(&ar->mcastpsq_lock);

	clear_bit(DTIM_EXPIRED, &vअगर->flags);

	/* clear the LSB of the BitMapCtl field of the TIM IE */
	ath6kl_wmi_set_pvb_cmd(ar->wmi, vअगर->fw_vअगर_idx, MCAST_AID, 0);
पूर्ण

व्योम ath6kl_disconnect_event(काष्ठा ath6kl_vअगर *vअगर, u8 reason, u8 *bssid,
			     u8 assoc_resp_len, u8 *assoc_info,
			     u16 prot_reason_status)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;

	अगर (vअगर->nw_type == AP_NETWORK) अणु
		/* disconnect due to other STA vअगर चयनing channels */
		अगर (reason == BSS_DISCONNECTED &&
		    prot_reason_status == WMI_AP_REASON_STA_ROAM) अणु
			ar->want_ch_चयन |= 1 << vअगर->fw_vअगर_idx;
			/* bail back to this channel अगर STA vअगर fails connect */
			ar->last_ch = le16_to_cpu(vअगर->profile.ch);
		पूर्ण

		अगर (prot_reason_status == WMI_AP_REASON_MAX_STA) अणु
			/* send max client reached notअगरication to user space */
			cfg80211_conn_failed(vअगर->ndev, bssid,
					     NL80211_CONN_FAIL_MAX_CLIENTS,
					     GFP_KERNEL);
		पूर्ण

		अगर (prot_reason_status == WMI_AP_REASON_ACL) अणु
			/* send blocked client notअगरication to user space */
			cfg80211_conn_failed(vअगर->ndev, bssid,
					     NL80211_CONN_FAIL_BLOCKED_CLIENT,
					     GFP_KERNEL);
		पूर्ण

		अगर (!ath6kl_हटाओ_sta(ar, bssid, prot_reason_status))
			वापस;

		/* अगर no more associated STAs, empty the mcast PS q */
		अगर (ar->sta_list_index == 0) अणु
			spin_lock_bh(&ar->mcastpsq_lock);
			skb_queue_purge(&ar->mcastpsq);
			spin_unlock_bh(&ar->mcastpsq_lock);

			/* clear the LSB of the TIM IE's BitMapCtl field */
			अगर (test_bit(WMI_READY, &ar->flag))
				ath6kl_wmi_set_pvb_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						       MCAST_AID, 0);
		पूर्ण

		अगर (!is_broadcast_ether_addr(bssid)) अणु
			/* send event to application */
			cfg80211_del_sta(vअगर->ndev, bssid, GFP_KERNEL);
		पूर्ण

		अगर (स_भेद(vअगर->ndev->dev_addr, bssid, ETH_ALEN) == 0) अणु
			स_रखो(vअगर->wep_key_list, 0, माप(vअगर->wep_key_list));
			clear_bit(CONNECTED, &vअगर->flags);
		पूर्ण
		वापस;
	पूर्ण

	ath6kl_cfg80211_disconnect_event(vअगर, reason, bssid,
					 assoc_resp_len, assoc_info,
					 prot_reason_status);

	aggr_reset_state(vअगर->aggr_cntxt->aggr_conn);

	del_समयr(&vअगर->disconnect_समयr);

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "disconnect reason is %d\n", reason);

	/*
	 * If the event is due to disconnect cmd from the host, only they
	 * the target would stop trying to connect. Under any other
	 * condition, target would keep trying to connect.
	 */
	अगर (reason == DISCONNECT_CMD) अणु
		अगर (!ar->usr_bss_filter && test_bit(WMI_READY, &ar->flag))
			ath6kl_wmi_bssfilter_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						 NONE_BSS_FILTER, 0);
	पूर्ण अन्यथा अणु
		set_bit(CONNECT_PEND, &vअगर->flags);
		अगर (((reason == ASSOC_FAILED) &&
		     (prot_reason_status == 0x11)) ||
		    ((reason == ASSOC_FAILED) && (prot_reason_status == 0x0) &&
		     (vअगर->reconnect_flag == 1))) अणु
			set_bit(CONNECTED, &vअगर->flags);
			वापस;
		पूर्ण
	पूर्ण

	/* restart disconnected concurrent vअगरs रुकोing क्रम new channel */
	ath6kl_check_ch_चयन(ar, ar->last_ch);

	/* update connect & link status atomically */
	spin_lock_bh(&vअगर->अगर_lock);
	clear_bit(CONNECTED, &vअगर->flags);
	netअगर_carrier_off(vअगर->ndev);
	spin_unlock_bh(&vअगर->अगर_lock);

	अगर ((reason != CSERV_DISCONNECT) || (vअगर->reconnect_flag != 1))
		vअगर->reconnect_flag = 0;

	अगर (reason != CSERV_DISCONNECT)
		ar->user_key_ctrl = 0;

	netअगर_stop_queue(vअगर->ndev);
	स_रखो(vअगर->bssid, 0, माप(vअगर->bssid));
	vअगर->bss_ch = 0;

	ath6kl_tx_data_cleanup(ar);
पूर्ण

काष्ठा ath6kl_vअगर *ath6kl_vअगर_first(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_vअगर *vअगर;

	spin_lock_bh(&ar->list_lock);
	अगर (list_empty(&ar->vअगर_list)) अणु
		spin_unlock_bh(&ar->list_lock);
		वापस शून्य;
	पूर्ण

	vअगर = list_first_entry(&ar->vअगर_list, काष्ठा ath6kl_vअगर, list);

	spin_unlock_bh(&ar->list_lock);

	वापस vअगर;
पूर्ण

अटल पूर्णांक ath6kl_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);

	set_bit(WLAN_ENABLED, &vअगर->flags);

	अगर (test_bit(CONNECTED, &vअगर->flags)) अणु
		netअगर_carrier_on(dev);
		netअगर_wake_queue(dev);
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);

	netअगर_stop_queue(dev);

	ath6kl_cfg80211_stop(vअगर);

	clear_bit(WLAN_ENABLED, &vअगर->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_set_features(काष्ठा net_device *dev,
			       netdev_features_t features)
अणु
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);
	काष्ठा ath6kl *ar = vअगर->ar;
	पूर्णांक err = 0;

	अगर ((features & NETIF_F_RXCSUM) &&
	    (ar->rx_meta_ver != WMI_META_VERSION_2)) अणु
		ar->rx_meta_ver = WMI_META_VERSION_2;
		err = ath6kl_wmi_set_rx_frame_क्रमmat_cmd(ar->wmi,
							 vअगर->fw_vअगर_idx,
							 ar->rx_meta_ver, 0, 0);
		अगर (err) अणु
			dev->features = features & ~NETIF_F_RXCSUM;
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अगर (!(features & NETIF_F_RXCSUM) &&
		   (ar->rx_meta_ver == WMI_META_VERSION_2)) अणु
		ar->rx_meta_ver = 0;
		err = ath6kl_wmi_set_rx_frame_क्रमmat_cmd(ar->wmi,
							 vअगर->fw_vअगर_idx,
							 ar->rx_meta_ver, 0, 0);
		अगर (err) अणु
			dev->features = features | NETIF_F_RXCSUM;
			वापस err;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम ath6kl_set_multicast_list(काष्ठा net_device *ndev)
अणु
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(ndev);
	bool mc_all_on = false;
	पूर्णांक mc_count = netdev_mc_count(ndev);
	काष्ठा netdev_hw_addr *ha;
	bool found;
	काष्ठा ath6kl_mc_filter *mc_filter, *पंचांगp;
	काष्ठा list_head mc_filter_new;
	पूर्णांक ret;

	अगर (!test_bit(WMI_READY, &vअगर->ar->flag) ||
	    !test_bit(WLAN_ENABLED, &vअगर->flags))
		वापस;

	/* Enable multicast-all filter. */
	mc_all_on = !!(ndev->flags & IFF_PROMISC) ||
		    !!(ndev->flags & IFF_ALLMULTI) ||
		    !!(mc_count > ATH6K_MAX_MC_FILTERS_PER_LIST);

	अगर (mc_all_on)
		set_bit(NETDEV_MCAST_ALL_ON, &vअगर->flags);
	अन्यथा
		clear_bit(NETDEV_MCAST_ALL_ON, &vअगर->flags);

	अगर (test_bit(ATH6KL_FW_CAPABILITY_WOW_MULTICAST_FILTER,
		     vअगर->ar->fw_capabilities)) अणु
		mc_all_on = mc_all_on || (vअगर->ar->state == ATH6KL_STATE_ON);
	पूर्ण

	अगर (!(ndev->flags & IFF_MULTICAST)) अणु
		mc_all_on = false;
		set_bit(NETDEV_MCAST_ALL_OFF, &vअगर->flags);
	पूर्ण अन्यथा अणु
		clear_bit(NETDEV_MCAST_ALL_OFF, &vअगर->flags);
	पूर्ण

	/* Enable/disable "multicast-all" filter*/
	ath6kl_dbg(ATH6KL_DBG_TRC, "%s multicast-all filter\n",
		   mc_all_on ? "enabling" : "disabling");

	ret = ath6kl_wmi_mcast_filter_cmd(vअगर->ar->wmi, vअगर->fw_vअगर_idx,
						  mc_all_on);
	अगर (ret) अणु
		ath6kl_warn("Failed to %s multicast-all receive\n",
			    mc_all_on ? "enable" : "disable");
		वापस;
	पूर्ण

	अगर (test_bit(NETDEV_MCAST_ALL_ON, &vअगर->flags))
		वापस;

	/* Keep the driver and firmware mcast list in sync. */
	list_क्रम_each_entry_safe(mc_filter, पंचांगp, &vअगर->mc_filter, list) अणु
		found = false;
		netdev_क्रम_each_mc_addr(ha, ndev) अणु
			अगर (स_भेद(ha->addr, mc_filter->hw_addr,
				   ATH6KL_MCAST_FILTER_MAC_ADDR_SIZE) == 0) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			/*
			 * Delete the filter which was previously set
			 * but not in the new request.
			 */
			ath6kl_dbg(ATH6KL_DBG_TRC,
				   "Removing %pM from multicast filter\n",
				   mc_filter->hw_addr);
			ret = ath6kl_wmi_add_del_mcast_filter_cmd(vअगर->ar->wmi,
					vअगर->fw_vअगर_idx, mc_filter->hw_addr,
					false);
			अगर (ret) अणु
				ath6kl_warn("Failed to remove multicast filter:%pM\n",
					    mc_filter->hw_addr);
				वापस;
			पूर्ण

			list_del(&mc_filter->list);
			kमुक्त(mc_filter);
		पूर्ण
	पूर्ण

	INIT_LIST_HEAD(&mc_filter_new);

	netdev_क्रम_each_mc_addr(ha, ndev) अणु
		found = false;
		list_क्रम_each_entry(mc_filter, &vअगर->mc_filter, list) अणु
			अगर (स_भेद(ha->addr, mc_filter->hw_addr,
				   ATH6KL_MCAST_FILTER_MAC_ADDR_SIZE) == 0) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			mc_filter = kzalloc(माप(काष्ठा ath6kl_mc_filter),
					    GFP_ATOMIC);
			अगर (!mc_filter) अणु
				WARN_ON(1);
				जाओ out;
			पूर्ण

			स_नकल(mc_filter->hw_addr, ha->addr,
			       ATH6KL_MCAST_FILTER_MAC_ADDR_SIZE);
			/* Set the multicast filter */
			ath6kl_dbg(ATH6KL_DBG_TRC,
				   "Adding %pM to multicast filter list\n",
				   mc_filter->hw_addr);
			ret = ath6kl_wmi_add_del_mcast_filter_cmd(vअगर->ar->wmi,
					vअगर->fw_vअगर_idx, mc_filter->hw_addr,
					true);
			अगर (ret) अणु
				ath6kl_warn("Failed to add multicast filter :%pM\n",
					    mc_filter->hw_addr);
				kमुक्त(mc_filter);
				जाओ out;
			पूर्ण

			list_add_tail(&mc_filter->list, &mc_filter_new);
		पूर्ण
	पूर्ण

out:
	list_splice_tail(&mc_filter_new, &vअगर->mc_filter);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ath6kl_netdev_ops = अणु
	.nकरो_खोलो               = ath6kl_खोलो,
	.nकरो_stop               = ath6kl_बंद,
	.nकरो_start_xmit         = ath6kl_data_tx,
	.nकरो_set_features       = ath6kl_set_features,
	.nकरो_set_rx_mode	= ath6kl_set_multicast_list,
पूर्ण;

व्योम init_netdev(काष्ठा net_device *dev)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);

	dev->netdev_ops = &ath6kl_netdev_ops;
	dev->needs_मुक्त_netdev = true;
	dev->watchकरोg_समयo = ATH6KL_TX_TIMEOUT;

	dev->needed_headroom = ETH_HLEN;
	dev->needed_headroom += roundup(माप(काष्ठा ath6kl_llc_snap_hdr) +
					माप(काष्ठा wmi_data_hdr) +
					HTC_HDR_LENGTH +
					WMI_MAX_TX_META_SZ +
					ATH6KL_HTC_ALIGN_BYTES, 4);

	अगर (!test_bit(ATH6KL_FW_CAPABILITY_NO_IP_CHECKSUM,
		      ar->fw_capabilities))
		dev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_RXCSUM;

	वापस;
पूर्ण
