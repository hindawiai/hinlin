<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>

#समावेश "cfg80211.h"
#समावेश "core.h"
#समावेश "qlink.h"
#समावेश "qlink_util.h"
#समावेश "bus.h"
#समावेश "commands.h"

/* Let device itself to select best values क्रम current conditions */
#घोषणा QTNF_SCAN_TIME_AUTO	0

#घोषणा QTNF_SCAN_DWELL_ACTIVE_DEFAULT		90
#घोषणा QTNF_SCAN_DWELL_PASSIVE_DEFAULT		100
#घोषणा QTNF_SCAN_SAMPLE_DURATION_DEFAULT	QTNF_SCAN_TIME_AUTO

अटल पूर्णांक qtnf_cmd_check_reply_header(स्थिर काष्ठा qlink_resp *resp,
				       u16 cmd_id, u8 mac_id, u8 vअगर_id,
				       माप_प्रकार resp_size)
अणु
	अगर (unlikely(le16_to_cpu(resp->cmd_id) != cmd_id)) अणु
		pr_warn("VIF%u.%u CMD%x: bad cmd_id in response: 0x%.4X\n",
			mac_id, vअगर_id, cmd_id, le16_to_cpu(resp->cmd_id));
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(resp->macid != mac_id)) अणु
		pr_warn("VIF%u.%u CMD%x: bad MAC in response: %u\n",
			mac_id, vअगर_id, cmd_id, resp->macid);
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(resp->vअगरid != vअगर_id)) अणु
		pr_warn("VIF%u.%u CMD%x: bad VIF in response: %u\n",
			mac_id, vअगर_id, cmd_id, resp->vअगरid);
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(le16_to_cpu(resp->mhdr.len) < resp_size)) अणु
		pr_warn("VIF%u.%u CMD%x: bad response size %u < %zu\n",
			mac_id, vअगर_id, cmd_id,
			le16_to_cpu(resp->mhdr.len), resp_size);
		वापस -ENOSPC;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qtnf_cmd_resp_result_decode(क्रमागत qlink_cmd_result qcode)
अणु
	चयन (qcode) अणु
	हाल QLINK_CMD_RESULT_OK:
		वापस 0;
	हाल QLINK_CMD_RESULT_INVALID:
		वापस -EINVAL;
	हाल QLINK_CMD_RESULT_ENOTSUPP:
		वापस -ENOTSUPP;
	हाल QLINK_CMD_RESULT_ENOTFOUND:
		वापस -ENOENT;
	हाल QLINK_CMD_RESULT_EALREADY:
		वापस -EALREADY;
	हाल QLINK_CMD_RESULT_EADDRINUSE:
		वापस -EADDRINUSE;
	हाल QLINK_CMD_RESULT_EADDRNOTAVAIL:
		वापस -EADDRNOTAVAIL;
	हाल QLINK_CMD_RESULT_EBUSY:
		वापस -EBUSY;
	शेष:
		वापस -EFAULT;
	पूर्ण
पूर्ण

अटल पूर्णांक qtnf_cmd_send_with_reply(काष्ठा qtnf_bus *bus,
				    काष्ठा sk_buff *cmd_skb,
				    काष्ठा sk_buff **response_skb,
				    माप_प्रकार स्थिर_resp_size,
				    माप_प्रकार *var_resp_size)
अणु
	काष्ठा qlink_cmd *cmd;
	काष्ठा qlink_resp *resp = शून्य;
	काष्ठा sk_buff *resp_skb = शून्य;
	पूर्णांक resp_res = 0;
	u16 cmd_id;
	u8 mac_id;
	u8 vअगर_id;
	पूर्णांक ret;

	cmd = (काष्ठा qlink_cmd *)cmd_skb->data;
	cmd_id = le16_to_cpu(cmd->cmd_id);
	mac_id = cmd->macid;
	vअगर_id = cmd->vअगरid;
	cmd->mhdr.len = cpu_to_le16(cmd_skb->len);

	pr_debug("VIF%u.%u cmd=0x%.4X\n", mac_id, vअगर_id, cmd_id);

	अगर (!qtnf_fw_is_up(bus) && cmd_id != QLINK_CMD_FW_INIT) अणु
		pr_warn("VIF%u.%u: drop cmd 0x%.4X in fw state %d\n",
			mac_id, vअगर_id, cmd_id, bus->fw_state);
		dev_kमुक्त_skb(cmd_skb);
		वापस -ENODEV;
	पूर्ण

	ret = qtnf_trans_send_cmd_with_resp(bus, cmd_skb, &resp_skb);
	अगर (ret)
		जाओ out;

	अगर (WARN_ON(!resp_skb || !resp_skb->data)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	resp = (काष्ठा qlink_resp *)resp_skb->data;
	resp_res = le16_to_cpu(resp->result);
	ret = qtnf_cmd_check_reply_header(resp, cmd_id, mac_id, vअगर_id,
					  स्थिर_resp_size);
	अगर (ret)
		जाओ out;

	/* Return length of variable part of response */
	अगर (response_skb && var_resp_size)
		*var_resp_size = le16_to_cpu(resp->mhdr.len) - स्थिर_resp_size;

out:
	अगर (response_skb)
		*response_skb = resp_skb;
	अन्यथा
		consume_skb(resp_skb);

	अगर (!ret)
		वापस qtnf_cmd_resp_result_decode(resp_res);

	pr_warn("VIF%u.%u: cmd 0x%.4X failed: %d\n",
		mac_id, vअगर_id, cmd_id, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक qtnf_cmd_send(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *cmd_skb)
अणु
	वापस qtnf_cmd_send_with_reply(bus, cmd_skb, शून्य,
					माप(काष्ठा qlink_resp), शून्य);
पूर्ण

अटल काष्ठा sk_buff *qtnf_cmd_alloc_new_cmdskb(u8 macid, u8 vअगरid, u16 cmd_no,
						 माप_प्रकार cmd_size)
अणु
	काष्ठा qlink_cmd *cmd;
	काष्ठा sk_buff *cmd_skb;

	cmd_skb = __dev_alloc_skb(माप(*cmd) +
				  QTNF_MAX_CMD_BUF_SIZE, GFP_KERNEL);
	अगर (unlikely(!cmd_skb)) अणु
		pr_err("VIF%u.%u CMD %u: alloc failed\n", macid, vअगरid, cmd_no);
		वापस शून्य;
	पूर्ण

	skb_put_zero(cmd_skb, cmd_size);

	cmd = (काष्ठा qlink_cmd *)cmd_skb->data;
	cmd->mhdr.len = cpu_to_le16(cmd_skb->len);
	cmd->mhdr.type = cpu_to_le16(QLINK_MSG_TYPE_CMD);
	cmd->cmd_id = cpu_to_le16(cmd_no);
	cmd->macid = macid;
	cmd->vअगरid = vअगरid;

	वापस cmd_skb;
पूर्ण

अटल व्योम qtnf_cmd_tlv_ie_set_add(काष्ठा sk_buff *cmd_skb, u8 frame_type,
				    स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा qlink_tlv_ie_set *tlv;

	tlv = (काष्ठा qlink_tlv_ie_set *)skb_put(cmd_skb, माप(*tlv) +
						 round_up(len, QLINK_ALIGN));
	tlv->hdr.type = cpu_to_le16(QTN_TLV_ID_IE_SET);
	tlv->hdr.len = cpu_to_le16(len + माप(*tlv) - माप(tlv->hdr));
	tlv->type = frame_type;
	tlv->flags = 0;

	अगर (len && buf)
		स_नकल(tlv->ie_data, buf, len);
पूर्ण

अटल bool qtnf_cmd_start_ap_can_fit(स्थिर काष्ठा qtnf_vअगर *vअगर,
				      स्थिर काष्ठा cfg80211_ap_settings *s)
अणु
	अचिन्हित पूर्णांक len = माप(काष्ठा qlink_cmd_start_ap);

	len += round_up(s->ssid_len, QLINK_ALIGN);
	len += round_up(s->beacon.head_len, QLINK_ALIGN);
	len += round_up(s->beacon.tail_len, QLINK_ALIGN);
	len += round_up(s->beacon.beacon_ies_len, QLINK_ALIGN);
	len += round_up(s->beacon.proberesp_ies_len, QLINK_ALIGN);
	len += round_up(s->beacon.assocresp_ies_len, QLINK_ALIGN);
	len += round_up(s->beacon.probe_resp_len, QLINK_ALIGN);

	अगर (cfg80211_chandef_valid(&s->chandef))
		len += माप(काष्ठा qlink_tlv_chandef);

	अगर (s->acl) अणु
		अचिन्हित पूर्णांक acl_len = काष्ठा_size(s->acl, mac_addrs,
						   s->acl->n_acl_entries);

		len += माप(काष्ठा qlink_tlv_hdr) +
			round_up(acl_len, QLINK_ALIGN);
	पूर्ण

	अगर (len > (माप(काष्ठा qlink_cmd) + QTNF_MAX_CMD_BUF_SIZE)) अणु
		pr_err("VIF%u.%u: can not fit AP settings: %u\n",
		       vअगर->mac->macid, vअगर->vअगरid, len);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम qtnf_cmd_tlv_ie_ext_add(काष्ठा sk_buff *cmd_skb, u8 eid_ext,
				    स्थिर व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा qlink_tlv_ext_ie *tlv;

	tlv = (काष्ठा qlink_tlv_ext_ie *)skb_put(cmd_skb, माप(*tlv) + len);
	tlv->hdr.type = cpu_to_le16(WLAN_EID_EXTENSION);
	tlv->hdr.len = cpu_to_le16(माप(*tlv) + len - माप(tlv->hdr));
	tlv->eid_ext = eid_ext;

	अगर (len && buf)
		स_नकल(tlv->ie_data, buf, len);
पूर्ण

पूर्णांक qtnf_cmd_send_start_ap(काष्ठा qtnf_vअगर *vअगर,
			   स्थिर काष्ठा cfg80211_ap_settings *s)
अणु
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_start_ap *cmd;
	काष्ठा qlink_auth_encr *aen;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!qtnf_cmd_start_ap_can_fit(vअगर, s))
		वापस -E2BIG;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_START_AP,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	cmd = (काष्ठा qlink_cmd_start_ap *)cmd_skb->data;
	cmd->dtim_period = s->dtim_period;
	cmd->beacon_पूर्णांकerval = cpu_to_le16(s->beacon_पूर्णांकerval);
	cmd->hidden_ssid = qlink_hidden_ssid_nl2q(s->hidden_ssid);
	cmd->inactivity_समयout = cpu_to_le16(s->inactivity_समयout);
	cmd->smps_mode = s->smps_mode;
	cmd->p2p_ctwinकरोw = s->p2p_ctwinकरोw;
	cmd->p2p_opp_ps = s->p2p_opp_ps;
	cmd->pbss = s->pbss;
	cmd->ht_required = s->ht_required;
	cmd->vht_required = s->vht_required;
	cmd->twt_responder = s->twt_responder;
	अगर (s->he_obss_pd.enable) अणु
		cmd->sr_params.sr_control |= QLINK_SR_SRG_INFORMATION_PRESENT;
		cmd->sr_params.srg_obss_pd_min_offset =
			s->he_obss_pd.min_offset;
		cmd->sr_params.srg_obss_pd_max_offset =
			s->he_obss_pd.max_offset;
	पूर्ण

	aen = &cmd->aen;
	aen->auth_type = s->auth_type;
	aen->privacy = !!s->privacy;
	aen->wpa_versions = cpu_to_le32(s->crypto.wpa_versions);
	aen->cipher_group = cpu_to_le32(s->crypto.cipher_group);
	aen->n_ciphers_pairwise = cpu_to_le32(s->crypto.n_ciphers_pairwise);
	क्रम (i = 0; i < QLINK_MAX_NR_CIPHER_SUITES; i++)
		aen->ciphers_pairwise[i] =
				cpu_to_le32(s->crypto.ciphers_pairwise[i]);
	aen->n_akm_suites = cpu_to_le32(s->crypto.n_akm_suites);
	क्रम (i = 0; i < QLINK_MAX_NR_AKM_SUITES; i++)
		aen->akm_suites[i] = cpu_to_le32(s->crypto.akm_suites[i]);
	aen->control_port = s->crypto.control_port;
	aen->control_port_no_encrypt = s->crypto.control_port_no_encrypt;
	aen->control_port_ethertype =
		cpu_to_le16(be16_to_cpu(s->crypto.control_port_ethertype));

	अगर (s->ssid && s->ssid_len > 0 && s->ssid_len <= IEEE80211_MAX_SSID_LEN)
		qtnf_cmd_skb_put_tlv_arr(cmd_skb, WLAN_EID_SSID, s->ssid,
					 s->ssid_len);

	अगर (cfg80211_chandef_valid(&s->chandef)) अणु
		काष्ठा qlink_tlv_chandef *chtlv =
			(काष्ठा qlink_tlv_chandef *)skb_put(cmd_skb,
							    माप(*chtlv));

		chtlv->hdr.type = cpu_to_le16(QTN_TLV_ID_CHANDEF);
		chtlv->hdr.len = cpu_to_le16(माप(*chtlv) -
					     माप(chtlv->hdr));
		qlink_chandef_cfg2q(&s->chandef, &chtlv->chdef);
	पूर्ण

	qtnf_cmd_tlv_ie_set_add(cmd_skb, QLINK_IE_SET_BEACON_HEAD,
				s->beacon.head, s->beacon.head_len);
	qtnf_cmd_tlv_ie_set_add(cmd_skb, QLINK_IE_SET_BEACON_TAIL,
				s->beacon.tail, s->beacon.tail_len);
	qtnf_cmd_tlv_ie_set_add(cmd_skb, QLINK_IE_SET_BEACON_IES,
				s->beacon.beacon_ies, s->beacon.beacon_ies_len);
	qtnf_cmd_tlv_ie_set_add(cmd_skb, QLINK_IE_SET_PROBE_RESP,
				s->beacon.probe_resp, s->beacon.probe_resp_len);
	qtnf_cmd_tlv_ie_set_add(cmd_skb, QLINK_IE_SET_PROBE_RESP_IES,
				s->beacon.proberesp_ies,
				s->beacon.proberesp_ies_len);
	qtnf_cmd_tlv_ie_set_add(cmd_skb, QLINK_IE_SET_ASSOC_RESP,
				s->beacon.assocresp_ies,
				s->beacon.assocresp_ies_len);

	अगर (s->ht_cap) अणु
		काष्ठा qlink_tlv_hdr *tlv = (काष्ठा qlink_tlv_hdr *)
			skb_put(cmd_skb, माप(*tlv) +
				round_up(माप(*s->ht_cap), QLINK_ALIGN));

		tlv->type = cpu_to_le16(WLAN_EID_HT_CAPABILITY);
		tlv->len = cpu_to_le16(माप(*s->ht_cap));
		स_नकल(tlv->val, s->ht_cap, माप(*s->ht_cap));
	पूर्ण

	अगर (s->vht_cap) अणु
		काष्ठा qlink_tlv_hdr *tlv = (काष्ठा qlink_tlv_hdr *)
			skb_put(cmd_skb, माप(*tlv) + माप(*s->vht_cap));

		tlv->type = cpu_to_le16(WLAN_EID_VHT_CAPABILITY);
		tlv->len = cpu_to_le16(माप(*s->vht_cap));
		स_नकल(tlv->val, s->vht_cap, माप(*s->vht_cap));
	पूर्ण

	अगर (s->he_cap)
		qtnf_cmd_tlv_ie_ext_add(cmd_skb, WLAN_EID_EXT_HE_CAPABILITY,
					s->he_cap, माप(*s->he_cap));

	अगर (s->acl) अणु
		माप_प्रकार acl_size = काष्ठा_size(s->acl, mac_addrs,
					      s->acl->n_acl_entries);
		काष्ठा qlink_tlv_hdr *tlv =
			skb_put(cmd_skb,
				माप(*tlv) + round_up(acl_size, QLINK_ALIGN));

		tlv->type = cpu_to_le16(QTN_TLV_ID_ACL_DATA);
		tlv->len = cpu_to_le16(acl_size);
		qlink_acl_data_cfg2q(s->acl, (काष्ठा qlink_acl_data *)tlv->val);
	पूर्ण

	qtnf_bus_lock(vअगर->mac->bus);
	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);
	अगर (ret)
		जाओ out;

	netअगर_carrier_on(vअगर->netdev);

out:
	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_stop_ap(काष्ठा qtnf_vअगर *vअगर)
अणु
	काष्ठा sk_buff *cmd_skb;
	पूर्णांक ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_STOP_AP,
					    माप(काष्ठा qlink_cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(vअगर->mac->bus);
	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);
	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_रेजिस्टर_mgmt(काष्ठा qtnf_vअगर *vअगर, u16 frame_type, bool reg)
अणु
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_mgmt_frame_रेजिस्टर *cmd;
	पूर्णांक ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_REGISTER_MGMT,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(vअगर->mac->bus);

	cmd = (काष्ठा qlink_cmd_mgmt_frame_रेजिस्टर *)cmd_skb->data;
	cmd->frame_type = cpu_to_le16(frame_type);
	cmd->करो_रेजिस्टर = reg;

	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);

	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_frame(काष्ठा qtnf_vअगर *vअगर, u32 cookie, u16 flags,
			u16 freq, स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_frame_tx *cmd;
	पूर्णांक ret;

	अगर (माप(*cmd) + len > QTNF_MAX_CMD_BUF_SIZE) अणु
		pr_warn("VIF%u.%u: frame is too big: %zu\n", vअगर->mac->macid,
			vअगर->vअगरid, len);
		वापस -E2BIG;
	पूर्ण

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_SEND_FRAME,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(vअगर->mac->bus);

	cmd = (काष्ठा qlink_cmd_frame_tx *)cmd_skb->data;
	cmd->cookie = cpu_to_le32(cookie);
	cmd->freq = cpu_to_le16(freq);
	cmd->flags = cpu_to_le16(flags);

	अगर (len && buf)
		qtnf_cmd_skb_put_buffer(cmd_skb, buf, len);

	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);

	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_mgmt_set_appie(काष्ठा qtnf_vअगर *vअगर, u8 frame_type,
				 स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा sk_buff *cmd_skb;
	पूर्णांक ret;

	अगर (len > QTNF_MAX_CMD_BUF_SIZE) अणु
		pr_warn("VIF%u.%u: %u frame is too big: %zu\n", vअगर->mac->macid,
			vअगर->vअगरid, frame_type, len);
		वापस -E2BIG;
	पूर्ण

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_MGMT_SET_APPIE,
					    माप(काष्ठा qlink_cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_cmd_tlv_ie_set_add(cmd_skb, frame_type, buf, len);

	qtnf_bus_lock(vअगर->mac->bus);
	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);
	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

अटल व्योम
qtnf_sta_info_parse_rate(काष्ठा rate_info *rate_dst,
			 स्थिर काष्ठा qlink_sta_info_rate *rate_src)
अणु
	rate_dst->legacy = get_unaligned_le16(&rate_src->rate) * 10;

	rate_dst->mcs = rate_src->mcs;
	rate_dst->nss = rate_src->nss;
	rate_dst->flags = 0;

	चयन (rate_src->bw) अणु
	हाल QLINK_CHAN_WIDTH_5:
		rate_dst->bw = RATE_INFO_BW_5;
		अवरोध;
	हाल QLINK_CHAN_WIDTH_10:
		rate_dst->bw = RATE_INFO_BW_10;
		अवरोध;
	हाल QLINK_CHAN_WIDTH_20:
	हाल QLINK_CHAN_WIDTH_20_NOHT:
		rate_dst->bw = RATE_INFO_BW_20;
		अवरोध;
	हाल QLINK_CHAN_WIDTH_40:
		rate_dst->bw = RATE_INFO_BW_40;
		अवरोध;
	हाल QLINK_CHAN_WIDTH_80:
		rate_dst->bw = RATE_INFO_BW_80;
		अवरोध;
	हाल QLINK_CHAN_WIDTH_160:
		rate_dst->bw = RATE_INFO_BW_160;
		अवरोध;
	शेष:
		rate_dst->bw = 0;
		अवरोध;
	पूर्ण

	अगर (rate_src->flags & QLINK_STA_INFO_RATE_FLAG_HT_MCS)
		rate_dst->flags |= RATE_INFO_FLAGS_MCS;
	अन्यथा अगर (rate_src->flags & QLINK_STA_INFO_RATE_FLAG_VHT_MCS)
		rate_dst->flags |= RATE_INFO_FLAGS_VHT_MCS;
	अन्यथा अगर (rate_src->flags & QLINK_STA_INFO_RATE_FLAG_HE_MCS)
		rate_dst->flags |= RATE_INFO_FLAGS_HE_MCS;

	अगर (rate_src->flags & QLINK_STA_INFO_RATE_FLAG_SHORT_GI)
		rate_dst->flags |= RATE_INFO_FLAGS_SHORT_GI;
पूर्ण

अटल व्योम
qtnf_sta_info_parse_flags(काष्ठा nl80211_sta_flag_update *dst,
			  स्थिर काष्ठा qlink_sta_info_state *src)
अणु
	u32 mask, value;

	dst->mask = 0;
	dst->set = 0;

	mask = le32_to_cpu(src->mask);
	value = le32_to_cpu(src->value);

	अगर (mask & QLINK_STA_FLAG_AUTHORIZED) अणु
		dst->mask |= BIT(NL80211_STA_FLAG_AUTHORIZED);
		अगर (value & QLINK_STA_FLAG_AUTHORIZED)
			dst->set |= BIT(NL80211_STA_FLAG_AUTHORIZED);
	पूर्ण

	अगर (mask & QLINK_STA_FLAG_SHORT_PREAMBLE) अणु
		dst->mask |= BIT(NL80211_STA_FLAG_SHORT_PREAMBLE);
		अगर (value & QLINK_STA_FLAG_SHORT_PREAMBLE)
			dst->set |= BIT(NL80211_STA_FLAG_SHORT_PREAMBLE);
	पूर्ण

	अगर (mask & QLINK_STA_FLAG_WME) अणु
		dst->mask |= BIT(NL80211_STA_FLAG_WME);
		अगर (value & QLINK_STA_FLAG_WME)
			dst->set |= BIT(NL80211_STA_FLAG_WME);
	पूर्ण

	अगर (mask & QLINK_STA_FLAG_MFP) अणु
		dst->mask |= BIT(NL80211_STA_FLAG_MFP);
		अगर (value & QLINK_STA_FLAG_MFP)
			dst->set |= BIT(NL80211_STA_FLAG_MFP);
	पूर्ण

	अगर (mask & QLINK_STA_FLAG_AUTHENTICATED) अणु
		dst->mask |= BIT(NL80211_STA_FLAG_AUTHENTICATED);
		अगर (value & QLINK_STA_FLAG_AUTHENTICATED)
			dst->set |= BIT(NL80211_STA_FLAG_AUTHENTICATED);
	पूर्ण

	अगर (mask & QLINK_STA_FLAG_TDLS_PEER) अणु
		dst->mask |= BIT(NL80211_STA_FLAG_TDLS_PEER);
		अगर (value & QLINK_STA_FLAG_TDLS_PEER)
			dst->set |= BIT(NL80211_STA_FLAG_TDLS_PEER);
	पूर्ण

	अगर (mask & QLINK_STA_FLAG_ASSOCIATED) अणु
		dst->mask |= BIT(NL80211_STA_FLAG_ASSOCIATED);
		अगर (value & QLINK_STA_FLAG_ASSOCIATED)
			dst->set |= BIT(NL80211_STA_FLAG_ASSOCIATED);
	पूर्ण
पूर्ण

अटल व्योम
qtnf_cmd_sta_info_parse(काष्ठा station_info *sinfo, स्थिर u8 *data,
			माप_प्रकार resp_size)
अणु
	स्थिर काष्ठा qlink_tlv_hdr *tlv;
	स्थिर काष्ठा qlink_sta_stats *stats = शून्य;
	स्थिर u8 *map = शून्य;
	अचिन्हित पूर्णांक map_len = 0;
	अचिन्हित पूर्णांक stats_len = 0;
	u16 tlv_len;

#घोषणा qtnf_sta_stat_avail(stat_name, bitn)	\
	(qtnf_utils_is_bit_set(map, bitn, map_len) && \
	 (दुरत्वend(काष्ठा qlink_sta_stats, stat_name) <= stats_len))

	qlink_क्रम_each_tlv(tlv, data, resp_size) अणु
		tlv_len = le16_to_cpu(tlv->len);

		चयन (le16_to_cpu(tlv->type)) अणु
		हाल QTN_TLV_ID_BITMAP:
			map_len = tlv_len;
			map = tlv->val;
			अवरोध;
		हाल QTN_TLV_ID_STA_STATS:
			stats_len = tlv_len;
			stats = (स्थिर काष्ठा qlink_sta_stats *)tlv->val;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!qlink_tlv_parsing_ok(tlv, data, resp_size)) अणु
		pr_err("Malformed TLV buffer\n");
		वापस;
	पूर्ण

	अगर (!map || !stats)
		वापस;

	अगर (qtnf_sta_stat_avail(inactive_समय, QLINK_STA_INFO_INACTIVE_TIME)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_INACTIVE_TIME);
		sinfo->inactive_समय = le32_to_cpu(stats->inactive_समय);
	पूर्ण

	अगर (qtnf_sta_stat_avail(connected_समय,
				QLINK_STA_INFO_CONNECTED_TIME)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_CONNECTED_TIME);
		sinfo->connected_समय = le32_to_cpu(stats->connected_समय);
	पूर्ण

	अगर (qtnf_sta_stat_avail(संकेत, QLINK_STA_INFO_SIGNAL)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
		sinfo->संकेत = stats->संकेत - QLINK_RSSI_OFFSET;
	पूर्ण

	अगर (qtnf_sta_stat_avail(संकेत_avg, QLINK_STA_INFO_SIGNAL_AVG)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL_AVG);
		sinfo->संकेत_avg = stats->संकेत_avg - QLINK_RSSI_OFFSET;
	पूर्ण

	अगर (qtnf_sta_stat_avail(rxrate, QLINK_STA_INFO_RX_BITRATE)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_BITRATE);
		qtnf_sta_info_parse_rate(&sinfo->rxrate, &stats->rxrate);
	पूर्ण

	अगर (qtnf_sta_stat_avail(txrate, QLINK_STA_INFO_TX_BITRATE)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
		qtnf_sta_info_parse_rate(&sinfo->txrate, &stats->txrate);
	पूर्ण

	अगर (qtnf_sta_stat_avail(sta_flags, QLINK_STA_INFO_STA_FLAGS)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_STA_FLAGS);
		qtnf_sta_info_parse_flags(&sinfo->sta_flags, &stats->sta_flags);
	पूर्ण

	अगर (qtnf_sta_stat_avail(rx_bytes, QLINK_STA_INFO_RX_BYTES)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_BYTES);
		sinfo->rx_bytes = le64_to_cpu(stats->rx_bytes);
	पूर्ण

	अगर (qtnf_sta_stat_avail(tx_bytes, QLINK_STA_INFO_TX_BYTES)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BYTES);
		sinfo->tx_bytes = le64_to_cpu(stats->tx_bytes);
	पूर्ण

	अगर (qtnf_sta_stat_avail(rx_bytes, QLINK_STA_INFO_RX_BYTES64)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_BYTES64);
		sinfo->rx_bytes = le64_to_cpu(stats->rx_bytes);
	पूर्ण

	अगर (qtnf_sta_stat_avail(tx_bytes, QLINK_STA_INFO_TX_BYTES64)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BYTES64);
		sinfo->tx_bytes = le64_to_cpu(stats->tx_bytes);
	पूर्ण

	अगर (qtnf_sta_stat_avail(rx_packets, QLINK_STA_INFO_RX_PACKETS)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_PACKETS);
		sinfo->rx_packets = le32_to_cpu(stats->rx_packets);
	पूर्ण

	अगर (qtnf_sta_stat_avail(tx_packets, QLINK_STA_INFO_TX_PACKETS)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_PACKETS);
		sinfo->tx_packets = le32_to_cpu(stats->tx_packets);
	पूर्ण

	अगर (qtnf_sta_stat_avail(rx_beacon, QLINK_STA_INFO_BEACON_RX)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_BEACON_RX);
		sinfo->rx_beacon = le64_to_cpu(stats->rx_beacon);
	पूर्ण

	अगर (qtnf_sta_stat_avail(rx_dropped_misc, QLINK_STA_INFO_RX_DROP_MISC)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_DROP_MISC);
		sinfo->rx_dropped_misc = le32_to_cpu(stats->rx_dropped_misc);
	पूर्ण

	अगर (qtnf_sta_stat_avail(tx_failed, QLINK_STA_INFO_TX_FAILED)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_FAILED);
		sinfo->tx_failed = le32_to_cpu(stats->tx_failed);
	पूर्ण

#अघोषित qtnf_sta_stat_avail
पूर्ण

पूर्णांक qtnf_cmd_get_sta_info(काष्ठा qtnf_vअगर *vअगर, स्थिर u8 *sta_mac,
			  काष्ठा station_info *sinfo)
अणु
	काष्ठा sk_buff *cmd_skb, *resp_skb = शून्य;
	काष्ठा qlink_cmd_get_sta_info *cmd;
	स्थिर काष्ठा qlink_resp_get_sta_info *resp;
	माप_प्रकार var_resp_len = 0;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_GET_STA_INFO,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(vअगर->mac->bus);

	cmd = (काष्ठा qlink_cmd_get_sta_info *)cmd_skb->data;
	ether_addr_copy(cmd->sta_addr, sta_mac);

	ret = qtnf_cmd_send_with_reply(vअगर->mac->bus, cmd_skb, &resp_skb,
				       माप(*resp), &var_resp_len);
	अगर (ret)
		जाओ out;

	resp = (स्थिर काष्ठा qlink_resp_get_sta_info *)resp_skb->data;

	अगर (!ether_addr_equal(sta_mac, resp->sta_addr)) अणु
		pr_err("VIF%u.%u: wrong mac in reply: %pM != %pM\n",
		       vअगर->mac->macid, vअगर->vअगरid, resp->sta_addr, sta_mac);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	qtnf_cmd_sta_info_parse(sinfo, resp->info, var_resp_len);

out:
	qtnf_bus_unlock(vअगर->mac->bus);
	consume_skb(resp_skb);

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_cmd_send_add_change_पूर्णांकf(काष्ठा qtnf_vअगर *vअगर,
					 क्रमागत nl80211_अगरtype अगरtype,
					 पूर्णांक use4addr,
					 u8 *mac_addr,
					 क्रमागत qlink_cmd_type cmd_type)
अणु
	काष्ठा sk_buff *cmd_skb, *resp_skb = शून्य;
	काष्ठा qlink_cmd_manage_पूर्णांकf *cmd;
	स्थिर काष्ठा qlink_resp_manage_पूर्णांकf *resp;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    cmd_type,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(vअगर->mac->bus);

	cmd = (काष्ठा qlink_cmd_manage_पूर्णांकf *)cmd_skb->data;
	cmd->पूर्णांकf_info.use4addr = use4addr;

	चयन (अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
		cmd->पूर्णांकf_info.अगर_type = cpu_to_le16(QLINK_IFTYPE_AP);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		cmd->पूर्णांकf_info.अगर_type = cpu_to_le16(QLINK_IFTYPE_STATION);
		अवरोध;
	शेष:
		pr_err("VIF%u.%u: unsupported type %d\n", vअगर->mac->macid,
		       vअगर->vअगरid, अगरtype);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (mac_addr)
		ether_addr_copy(cmd->पूर्णांकf_info.mac_addr, mac_addr);
	अन्यथा
		eth_zero_addr(cmd->पूर्णांकf_info.mac_addr);

	ret = qtnf_cmd_send_with_reply(vअगर->mac->bus, cmd_skb, &resp_skb,
				       माप(*resp), शून्य);
	अगर (ret)
		जाओ out;

	resp = (स्थिर काष्ठा qlink_resp_manage_पूर्णांकf *)resp_skb->data;
	ether_addr_copy(vअगर->mac_addr, resp->पूर्णांकf_info.mac_addr);

out:
	qtnf_bus_unlock(vअगर->mac->bus);
	consume_skb(resp_skb);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_add_पूर्णांकf(काष्ठा qtnf_vअगर *vअगर, क्रमागत nl80211_अगरtype अगरtype,
			   पूर्णांक use4addr, u8 *mac_addr)
अणु
	वापस qtnf_cmd_send_add_change_पूर्णांकf(vअगर, अगरtype, use4addr, mac_addr,
			QLINK_CMD_ADD_INTF);
पूर्ण

पूर्णांक qtnf_cmd_send_change_पूर्णांकf_type(काष्ठा qtnf_vअगर *vअगर,
				   क्रमागत nl80211_अगरtype अगरtype,
				   पूर्णांक use4addr,
				   u8 *mac_addr)
अणु
	पूर्णांक ret;

	ret = qtnf_cmd_send_add_change_पूर्णांकf(vअगर, अगरtype, use4addr, mac_addr,
					    QLINK_CMD_CHANGE_INTF);

	/* Regulatory settings may be dअगरferent क्रम dअगरferent पूर्णांकerface types */
	अगर (ret == 0 && vअगर->wdev.अगरtype != अगरtype) अणु
		क्रमागत nl80211_band band;
		काष्ठा wiphy *wiphy = priv_to_wiphy(vअगर->mac);

		क्रम (band = 0; band < NUM_NL80211_BANDS; ++band) अणु
			अगर (!wiphy->bands[band])
				जारी;

			qtnf_cmd_band_info_get(vअगर->mac, wiphy->bands[band]);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_del_पूर्णांकf(काष्ठा qtnf_vअगर *vअगर)
अणु
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_manage_पूर्णांकf *cmd;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_DEL_INTF,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(vअगर->mac->bus);

	cmd = (काष्ठा qlink_cmd_manage_पूर्णांकf *)cmd_skb->data;

	चयन (vअगर->wdev.अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
		cmd->पूर्णांकf_info.अगर_type = cpu_to_le16(QLINK_IFTYPE_AP);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		cmd->पूर्णांकf_info.अगर_type = cpu_to_le16(QLINK_IFTYPE_STATION);
		अवरोध;
	शेष:
		pr_warn("VIF%u.%u: unsupported iftype %d\n", vअगर->mac->macid,
			vअगर->vअगरid, vअगर->wdev.अगरtype);
		dev_kमुक्त_skb(cmd_skb);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	eth_zero_addr(cmd->पूर्णांकf_info.mac_addr);

	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);
	अगर (ret)
		जाओ out;

out:
	qtnf_bus_unlock(vअगर->mac->bus);
	वापस ret;
पूर्ण

अटल पूर्णांक
qtnf_cmd_resp_proc_hw_info(काष्ठा qtnf_bus *bus,
			   स्थिर काष्ठा qlink_resp_get_hw_info *resp,
			   माप_प्रकार info_len)
अणु
	काष्ठा qtnf_hw_info *hwinfo = &bus->hw_info;
	स्थिर काष्ठा qlink_tlv_hdr *tlv;
	स्थिर अक्षर *bld_name = शून्य;
	स्थिर अक्षर *bld_rev = शून्य;
	स्थिर अक्षर *bld_type = शून्य;
	स्थिर अक्षर *bld_label = शून्य;
	u32 bld_पंचांगstamp = 0;
	u32 plat_id = 0;
	स्थिर अक्षर *hw_id = शून्य;
	स्थिर अक्षर *calibration_ver = शून्य;
	स्थिर अक्षर *uboot_ver = शून्य;
	u32 hw_ver = 0;
	u16 tlv_type;
	u16 tlv_len;

	hwinfo->num_mac = resp->num_mac;
	hwinfo->mac_biपंचांगap = resp->mac_biपंचांगap;
	hwinfo->fw_ver = le32_to_cpu(resp->fw_ver);
	hwinfo->total_tx_chain = resp->total_tx_chain;
	hwinfo->total_rx_chain = resp->total_rx_chain;

	bld_पंचांगstamp = le32_to_cpu(resp->bld_पंचांगstamp);
	plat_id = le32_to_cpu(resp->plat_id);
	hw_ver = le32_to_cpu(resp->hw_ver);

	qlink_क्रम_each_tlv(tlv, resp->info, info_len) अणु
		tlv_type = le16_to_cpu(tlv->type);
		tlv_len = le16_to_cpu(tlv->len);

		चयन (tlv_type) अणु
		हाल QTN_TLV_ID_BUILD_NAME:
			bld_name = (स्थिर व्योम *)tlv->val;
			अवरोध;
		हाल QTN_TLV_ID_BUILD_REV:
			bld_rev = (स्थिर व्योम *)tlv->val;
			अवरोध;
		हाल QTN_TLV_ID_BUILD_TYPE:
			bld_type = (स्थिर व्योम *)tlv->val;
			अवरोध;
		हाल QTN_TLV_ID_BUILD_LABEL:
			bld_label = (स्थिर व्योम *)tlv->val;
			अवरोध;
		हाल QTN_TLV_ID_HW_ID:
			hw_id = (स्थिर व्योम *)tlv->val;
			अवरोध;
		हाल QTN_TLV_ID_CALIBRATION_VER:
			calibration_ver = (स्थिर व्योम *)tlv->val;
			अवरोध;
		हाल QTN_TLV_ID_UBOOT_VER:
			uboot_ver = (स्थिर व्योम *)tlv->val;
			अवरोध;
		हाल QTN_TLV_ID_BITMAP:
			स_नकल(hwinfo->hw_capab, tlv->val,
			       min(माप(hwinfo->hw_capab), (माप_प्रकार)tlv_len));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!qlink_tlv_parsing_ok(tlv, resp->info, info_len)) अणु
		pr_err("Malformed TLV buffer\n");
		वापस -EINVAL;
	पूर्ण

	pr_info("\nBuild name:            %s\n"
		"Build revision:        %s\n"
		"Build type:            %s\n"
		"Build label:           %s\n"
		"Build timestamp:       %lu\n"
		"Platform ID:           %lu\n"
		"Hardware ID:           %s\n"
		"Calibration version:   %s\n"
		"U-Boot version:        %s\n"
		"Hardware version:      0x%08x\n"
		"Qlink ver:             %u.%u\n"
		"MACs map:              %#x\n"
		"Chains Rx-Tx:          %ux%u\n"
		"FW version:            0x%x\n",
		bld_name, bld_rev, bld_type, bld_label,
		(अचिन्हित दीर्घ)bld_पंचांगstamp,
		(अचिन्हित दीर्घ)plat_id,
		hw_id, calibration_ver, uboot_ver, hw_ver,
		QLINK_VER_MAJOR(bus->hw_info.ql_proto_ver),
		QLINK_VER_MINOR(bus->hw_info.ql_proto_ver),
		hwinfo->mac_biपंचांगap,
		hwinfo->total_rx_chain, hwinfo->total_tx_chain,
		hwinfo->fw_ver);

	strlcpy(hwinfo->fw_version, bld_label, माप(hwinfo->fw_version));
	hwinfo->hw_version = hw_ver;

	वापस 0;
पूर्ण

अटल व्योम
qtnf_parse_wowlan_info(काष्ठा qtnf_wmac *mac,
		       स्थिर काष्ठा qlink_wowlan_capab_data *wowlan)
अणु
	काष्ठा qtnf_mac_info *mac_info = &mac->macinfo;
	स्थिर काष्ठा qlink_wowlan_support *data1;
	काष्ठा wiphy_wowlan_support *supp;

	supp = kzalloc(माप(*supp), GFP_KERNEL);
	अगर (!supp)
		वापस;

	चयन (le16_to_cpu(wowlan->version)) अणु
	हाल 0x1:
		data1 = (काष्ठा qlink_wowlan_support *)wowlan->data;

		supp->flags = WIPHY_WOWLAN_MAGIC_PKT | WIPHY_WOWLAN_DISCONNECT;
		supp->n_patterns = le32_to_cpu(data1->n_patterns);
		supp->pattern_max_len = le32_to_cpu(data1->pattern_max_len);
		supp->pattern_min_len = le32_to_cpu(data1->pattern_min_len);

		mac_info->wowlan = supp;
		अवरोध;
	शेष:
		pr_warn("MAC%u: unsupported WoWLAN version 0x%x\n",
			mac->macid, le16_to_cpu(wowlan->version));
		kमुक्त(supp);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
qtnf_parse_variable_mac_info(काष्ठा qtnf_wmac *mac,
			     स्थिर काष्ठा qlink_resp_get_mac_info *resp,
			     माप_प्रकार tlv_buf_size)
अणु
	काष्ठा ieee80211_अगरace_combination *comb = mac->macinfo.अगर_comb;
	माप_प्रकार n_comb = 0;
	काष्ठा ieee80211_अगरace_limit *limits;
	स्थिर काष्ठा qlink_अगरace_limit_record *rec;
	स्थिर काष्ठा qlink_अगरace_limit *lim;
	स्थिर काष्ठा qlink_wowlan_capab_data *wowlan;
	u16 rec_len;
	u16 tlv_type;
	u16 tlv_value_len;
	स्थिर काष्ठा qlink_tlv_hdr *tlv;
	u8 *ext_capa = शून्य;
	u8 *ext_capa_mask = शून्य;
	u8 ext_capa_len = 0;
	u8 ext_capa_mask_len = 0;
	पूर्णांक i = 0;
	काष्ठा ieee80211_reg_rule *rule;
	अचिन्हित पूर्णांक rule_idx = 0;
	स्थिर काष्ठा qlink_tlv_reg_rule *tlv_rule;

	अगर (WARN_ON(resp->n_reg_rules > NL80211_MAX_SUPP_REG_RULES))
		वापस -E2BIG;

	mac->rd = kzalloc(काष्ठा_size(mac->rd, reg_rules, resp->n_reg_rules),
			  GFP_KERNEL);
	अगर (!mac->rd)
		वापस -ENOMEM;

	mac->rd->n_reg_rules = resp->n_reg_rules;
	mac->rd->alpha2[0] = resp->alpha2[0];
	mac->rd->alpha2[1] = resp->alpha2[1];

	चयन (resp->dfs_region) अणु
	हाल QLINK_DFS_FCC:
		mac->rd->dfs_region = NL80211_DFS_FCC;
		अवरोध;
	हाल QLINK_DFS_ETSI:
		mac->rd->dfs_region = NL80211_DFS_ETSI;
		अवरोध;
	हाल QLINK_DFS_JP:
		mac->rd->dfs_region = NL80211_DFS_JP;
		अवरोध;
	हाल QLINK_DFS_UNSET:
	शेष:
		mac->rd->dfs_region = NL80211_DFS_UNSET;
		अवरोध;
	पूर्ण

	qlink_क्रम_each_tlv(tlv, resp->var_info, tlv_buf_size) अणु
		tlv_type = le16_to_cpu(tlv->type);
		tlv_value_len = le16_to_cpu(tlv->len);

		चयन (tlv_type) अणु
		हाल QTN_TLV_ID_IFACE_LIMIT:
			अगर (unlikely(!comb)) अणु
				pr_warn("MAC%u: no combinations advertised\n",
					mac->macid);
				वापस -EINVAL;
			पूर्ण

			अगर (n_comb >= mac->macinfo.n_अगर_comb) अणु
				pr_warn("MAC%u: combinations count exceeded\n",
					mac->macid);
				n_comb++;
				अवरोध;
			पूर्ण

			rec = (व्योम *)tlv->val;
			rec_len = माप(*rec) + rec->n_limits * माप(*lim);

			अगर (unlikely(tlv_value_len != rec_len)) अणु
				pr_warn("MAC%u: record %zu size mismatch\n",
					mac->macid, n_comb);
				वापस -EINVAL;
			पूर्ण

			limits = kसुस्मृति(rec->n_limits, माप(*limits),
					 GFP_KERNEL);
			अगर (!limits)
				वापस -ENOMEM;

			comb[n_comb].num_dअगरferent_channels =
				rec->num_dअगरferent_channels;
			comb[n_comb].max_पूर्णांकerfaces =
				le16_to_cpu(rec->max_पूर्णांकerfaces);
			comb[n_comb].n_limits = rec->n_limits;
			comb[n_comb].limits = limits;

			क्रम (i = 0; i < rec->n_limits; i++) अणु
				lim = &rec->limits[i];
				limits[i].max = le16_to_cpu(lim->max_num);
				limits[i].types =
					qlink_अगरace_type_to_nl_mask(le16_to_cpu(lim->type));
				pr_debug("MAC%u: comb[%zu]: MAX:%u TYPES:%.4X\n",
					 mac->macid, n_comb,
					 limits[i].max, limits[i].types);
			पूर्ण

			n_comb++;
			अवरोध;
		हाल WLAN_EID_EXT_CAPABILITY:
			अगर (unlikely(tlv_value_len > U8_MAX))
				वापस -EINVAL;
			ext_capa = (u8 *)tlv->val;
			ext_capa_len = tlv_value_len;
			अवरोध;
		हाल QTN_TLV_ID_EXT_CAPABILITY_MASK:
			अगर (unlikely(tlv_value_len > U8_MAX))
				वापस -EINVAL;
			ext_capa_mask = (u8 *)tlv->val;
			ext_capa_mask_len = tlv_value_len;
			अवरोध;
		हाल QTN_TLV_ID_WOWLAN_CAPAB:
			अगर (tlv_value_len < माप(*wowlan))
				वापस -EINVAL;

			wowlan = (व्योम *)tlv->val;
			अगर (!le16_to_cpu(wowlan->len)) अणु
				pr_warn("MAC%u: skip empty WoWLAN data\n",
					mac->macid);
				अवरोध;
			पूर्ण

			rec_len = माप(*wowlan) + le16_to_cpu(wowlan->len);
			अगर (unlikely(tlv_value_len != rec_len)) अणु
				pr_warn("MAC%u: WoWLAN data size mismatch\n",
					mac->macid);
				वापस -EINVAL;
			पूर्ण

			kमुक्त(mac->macinfo.wowlan);
			mac->macinfo.wowlan = शून्य;
			qtnf_parse_wowlan_info(mac, wowlan);
			अवरोध;
		हाल QTN_TLV_ID_REG_RULE:
			अगर (rule_idx >= resp->n_reg_rules) अणु
				pr_warn("unexpected number of rules: %u\n",
					resp->n_reg_rules);
				वापस -EINVAL;
			पूर्ण

			अगर (tlv_value_len != माप(*tlv_rule) - माप(*tlv)) अणु
				pr_warn("malformed TLV 0x%.2X; LEN: %u\n",
					tlv_type, tlv_value_len);
				वापस -EINVAL;
			पूर्ण

			tlv_rule = (स्थिर काष्ठा qlink_tlv_reg_rule *)tlv;
			rule = &mac->rd->reg_rules[rule_idx++];
			qlink_utils_regrule_q2nl(rule, tlv_rule);
			अवरोध;
		शेष:
			pr_warn("MAC%u: unknown TLV type %u\n",
				mac->macid, tlv_type);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!qlink_tlv_parsing_ok(tlv, resp->var_info, tlv_buf_size)) अणु
		pr_err("Malformed TLV buffer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mac->macinfo.n_अगर_comb != n_comb) अणु
		pr_err("MAC%u: combination mismatch: reported=%zu parsed=%zu\n",
		       mac->macid, mac->macinfo.n_अगर_comb, n_comb);
		वापस -EINVAL;
	पूर्ण

	अगर (ext_capa_len != ext_capa_mask_len) अणु
		pr_err("MAC%u: ext_capa/_mask lengths mismatch: %u != %u\n",
		       mac->macid, ext_capa_len, ext_capa_mask_len);
		वापस -EINVAL;
	पूर्ण

	अगर (rule_idx != resp->n_reg_rules) अणु
		pr_warn("unexpected number of rules: expected %u got %u\n",
			resp->n_reg_rules, rule_idx);
		वापस -EINVAL;
	पूर्ण

	अगर (ext_capa_len > 0) अणु
		ext_capa = kmemdup(ext_capa, ext_capa_len, GFP_KERNEL);
		अगर (!ext_capa)
			वापस -ENOMEM;

		ext_capa_mask =
			kmemdup(ext_capa_mask, ext_capa_mask_len, GFP_KERNEL);
		अगर (!ext_capa_mask) अणु
			kमुक्त(ext_capa);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		ext_capa = शून्य;
		ext_capa_mask = शून्य;
	पूर्ण

	qtnf_mac_ext_caps_मुक्त(mac);
	mac->macinfo.extended_capabilities = ext_capa;
	mac->macinfo.extended_capabilities_mask = ext_capa_mask;
	mac->macinfo.extended_capabilities_len = ext_capa_len;

	वापस 0;
पूर्ण

अटल पूर्णांक
qtnf_cmd_resp_proc_mac_info(काष्ठा qtnf_wmac *mac,
			    स्थिर काष्ठा qlink_resp_get_mac_info *resp_info)
अणु
	काष्ठा qtnf_mac_info *mac_info;
	काष्ठा qtnf_vअगर *vअगर;

	qtnf_mac_अगरace_comb_मुक्त(mac);

	mac_info = &mac->macinfo;

	mac_info->bands_cap = resp_info->bands_cap;
	ether_addr_copy(mac->macaddr, resp_info->dev_mac);

	vअगर = qtnf_mac_get_base_vअगर(mac);
	अगर (vअगर)
		ether_addr_copy(vअगर->mac_addr, mac->macaddr);
	अन्यथा
		pr_err("could not get valid base vif\n");

	mac_info->num_tx_chain = resp_info->num_tx_chain;
	mac_info->num_rx_chain = resp_info->num_rx_chain;

	mac_info->max_ap_assoc_sta = le16_to_cpu(resp_info->max_ap_assoc_sta);
	mac_info->radar_detect_widths =
			qlink_chan_width_mask_to_nl(le16_to_cpu(
					resp_info->radar_detect_widths));
	mac_info->max_acl_mac_addrs = le16_to_cpu(resp_info->max_acl_mac_addrs);
	mac_info->frag_thr = le32_to_cpu(resp_info->frag_threshold);
	mac_info->rts_thr = le32_to_cpu(resp_info->rts_threshold);
	mac_info->sretry_limit = resp_info->retry_लघु;
	mac_info->lretry_limit = resp_info->retry_दीर्घ;
	mac_info->coverage_class = resp_info->coverage_class;
	mac_info->max_scan_ssids = resp_info->max_scan_ssids;

	स_नकल(&mac_info->ht_cap_mod_mask, &resp_info->ht_cap_mod_mask,
	       माप(mac_info->ht_cap_mod_mask));
	स_नकल(&mac_info->vht_cap_mod_mask, &resp_info->vht_cap_mod_mask,
	       माप(mac_info->vht_cap_mod_mask));

	mac_info->n_अगर_comb = resp_info->n_अगरace_combinations;
	mac_info->अगर_comb = kसुस्मृति(mac->macinfo.n_अगर_comb,
				    माप(*mac->macinfo.अगर_comb),
				    GFP_KERNEL);

	अगर (!mac->macinfo.अगर_comb)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम qtnf_cmd_resp_band_fill_htcap(स्थिर u8 *info,
					  काष्ठा ieee80211_sta_ht_cap *bcap)
अणु
	स्थिर काष्ठा ieee80211_ht_cap *ht_cap =
		(स्थिर काष्ठा ieee80211_ht_cap *)info;

	bcap->ht_supported = true;
	bcap->cap = le16_to_cpu(ht_cap->cap_info);
	bcap->ampdu_factor =
		ht_cap->ampdu_params_info & IEEE80211_HT_AMPDU_PARM_FACTOR;
	bcap->ampdu_density =
		(ht_cap->ampdu_params_info & IEEE80211_HT_AMPDU_PARM_DENSITY) >>
		IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT;
	स_नकल(&bcap->mcs, &ht_cap->mcs, माप(bcap->mcs));
पूर्ण

अटल व्योम qtnf_cmd_resp_band_fill_vhtcap(स्थिर u8 *info,
					   काष्ठा ieee80211_sta_vht_cap *bcap)
अणु
	स्थिर काष्ठा ieee80211_vht_cap *vht_cap =
		(स्थिर काष्ठा ieee80211_vht_cap *)info;

	bcap->vht_supported = true;
	bcap->cap = le32_to_cpu(vht_cap->vht_cap_info);
	स_नकल(&bcap->vht_mcs, &vht_cap->supp_mcs, माप(bcap->vht_mcs));
पूर्ण

अटल व्योम qtnf_cmd_conv_अगरtype(काष्ठा ieee80211_sband_अगरtype_data
				  *अगरtype_data,
				  स्थिर काष्ठा qlink_sband_अगरtype_data
				  *qlink_data)
अणु
	अगरtype_data->types_mask = le16_to_cpu(qlink_data->types_mask);

	अगरtype_data->he_cap.has_he = true;
	स_नकल(&अगरtype_data->he_cap.he_cap_elem, &qlink_data->he_cap_elem,
	       माप(qlink_data->he_cap_elem));
	स_नकल(अगरtype_data->he_cap.ppe_thres, qlink_data->ppe_thres,
	       ARRAY_SIZE(qlink_data->ppe_thres));

	अगरtype_data->he_cap.he_mcs_nss_supp.rx_mcs_80 =
		qlink_data->he_mcs_nss_supp.rx_mcs_80;
	अगरtype_data->he_cap.he_mcs_nss_supp.tx_mcs_80 =
		qlink_data->he_mcs_nss_supp.tx_mcs_80;
	अगरtype_data->he_cap.he_mcs_nss_supp.rx_mcs_160 =
		qlink_data->he_mcs_nss_supp.rx_mcs_160;
	अगरtype_data->he_cap.he_mcs_nss_supp.tx_mcs_160 =
		qlink_data->he_mcs_nss_supp.tx_mcs_160;
	अगरtype_data->he_cap.he_mcs_nss_supp.rx_mcs_80p80 =
		qlink_data->he_mcs_nss_supp.rx_mcs_80p80;
	अगरtype_data->he_cap.he_mcs_nss_supp.tx_mcs_80p80 =
		qlink_data->he_mcs_nss_supp.tx_mcs_80p80;
पूर्ण

अटल पूर्णांक qtnf_cmd_band_fill_अगरtype(स्थिर u8 *data,
				     काष्ठा ieee80211_supported_band *band)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ieee80211_sband_अगरtype_data *अगरtype_data;
	स्थिर काष्ठा qlink_tlv_अगरtype_data *tlv =
		(स्थिर काष्ठा qlink_tlv_अगरtype_data *)data;
	माप_प्रकार payload_len = tlv->n_अगरtype_data * माप(*tlv->अगरtype_data) +
		माप(*tlv) -
		माप(काष्ठा qlink_tlv_hdr);

	अगर (tlv->hdr.len != cpu_to_le16(payload_len)) अणु
		pr_err("bad IFTYPE_DATA TLV len %u\n", tlv->hdr.len);
		वापस -EINVAL;
	पूर्ण

	kमुक्त(band->अगरtype_data);
	band->अगरtype_data = शून्य;
	band->n_अगरtype_data = tlv->n_अगरtype_data;
	अगर (band->n_अगरtype_data == 0)
		वापस 0;

	अगरtype_data = kसुस्मृति(band->n_अगरtype_data, माप(*अगरtype_data),
			      GFP_KERNEL);
	अगर (!अगरtype_data) अणु
		band->n_अगरtype_data = 0;
		वापस -ENOMEM;
	पूर्ण
	band->अगरtype_data = अगरtype_data;

	क्रम (i = 0; i < band->n_अगरtype_data; i++)
		qtnf_cmd_conv_अगरtype(अगरtype_data++, &tlv->अगरtype_data[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक
qtnf_cmd_resp_fill_band_info(काष्ठा ieee80211_supported_band *band,
			     काष्ठा qlink_resp_band_info_get *resp,
			     माप_प्रकार payload_len)
अणु
	u16 tlv_type;
	माप_प्रकार tlv_dlen;
	स्थिर काष्ठा qlink_tlv_hdr *tlv;
	स्थिर काष्ठा qlink_channel *qchan;
	काष्ठा ieee80211_channel *chan;
	अचिन्हित पूर्णांक chidx = 0;
	u32 qflags;
	पूर्णांक ret = -EINVAL;

	स_रखो(&band->ht_cap, 0, माप(band->ht_cap));
	स_रखो(&band->vht_cap, 0, माप(band->vht_cap));

	अगर (band->channels) अणु
		अगर (band->n_channels == resp->num_chans) अणु
			स_रखो(band->channels, 0,
			       माप(*band->channels) * band->n_channels);
		पूर्ण अन्यथा अणु
			kमुक्त(band->channels);
			band->n_channels = 0;
			band->channels = शून्य;
		पूर्ण
	पूर्ण

	band->n_channels = resp->num_chans;
	अगर (band->n_channels == 0)
		वापस 0;

	अगर (!band->channels)
		band->channels = kसुस्मृति(band->n_channels, माप(*chan),
					 GFP_KERNEL);
	अगर (!band->channels) अणु
		band->n_channels = 0;
		वापस -ENOMEM;
	पूर्ण

	qlink_क्रम_each_tlv(tlv, resp->info, payload_len) अणु
		tlv_type = le16_to_cpu(tlv->type);
		tlv_dlen = le16_to_cpu(tlv->len);

		चयन (tlv_type) अणु
		हाल QTN_TLV_ID_CHANNEL:
			अगर (unlikely(tlv_dlen != माप(*qchan))) अणु
				pr_err("invalid channel TLV len %zu\n",
				       tlv_dlen);
				जाओ error_ret;
			पूर्ण

			अगर (chidx == band->n_channels) अणु
				pr_err("too many channel TLVs\n");
				जाओ error_ret;
			पूर्ण

			qchan = (स्थिर काष्ठा qlink_channel *)tlv->val;
			chan = &band->channels[chidx++];
			qflags = le32_to_cpu(qchan->flags);

			chan->hw_value = le16_to_cpu(qchan->hw_value);
			chan->band = band->band;
			chan->center_freq = le16_to_cpu(qchan->center_freq);
			chan->max_antenna_gain = (पूर्णांक)qchan->max_antenna_gain;
			chan->max_घातer = (पूर्णांक)qchan->max_घातer;
			chan->max_reg_घातer = (पूर्णांक)qchan->max_reg_घातer;
			chan->beacon_found = qchan->beacon_found;
			chan->dfs_cac_ms = le32_to_cpu(qchan->dfs_cac_ms);
			chan->flags = 0;

			अगर (qflags & QLINK_CHAN_DISABLED)
				chan->flags |= IEEE80211_CHAN_DISABLED;

			अगर (qflags & QLINK_CHAN_NO_IR)
				chan->flags |= IEEE80211_CHAN_NO_IR;

			अगर (qflags & QLINK_CHAN_NO_HT40PLUS)
				chan->flags |= IEEE80211_CHAN_NO_HT40PLUS;

			अगर (qflags & QLINK_CHAN_NO_HT40MINUS)
				chan->flags |= IEEE80211_CHAN_NO_HT40MINUS;

			अगर (qflags & QLINK_CHAN_NO_OFDM)
				chan->flags |= IEEE80211_CHAN_NO_OFDM;

			अगर (qflags & QLINK_CHAN_NO_80MHZ)
				chan->flags |= IEEE80211_CHAN_NO_80MHZ;

			अगर (qflags & QLINK_CHAN_NO_160MHZ)
				chan->flags |= IEEE80211_CHAN_NO_160MHZ;

			अगर (qflags & QLINK_CHAN_INDOOR_ONLY)
				chan->flags |= IEEE80211_CHAN_INDOOR_ONLY;

			अगर (qflags & QLINK_CHAN_IR_CONCURRENT)
				chan->flags |= IEEE80211_CHAN_IR_CONCURRENT;

			अगर (qflags & QLINK_CHAN_NO_20MHZ)
				chan->flags |= IEEE80211_CHAN_NO_20MHZ;

			अगर (qflags & QLINK_CHAN_NO_10MHZ)
				chan->flags |= IEEE80211_CHAN_NO_10MHZ;

			अगर (qflags & QLINK_CHAN_RADAR) अणु
				chan->flags |= IEEE80211_CHAN_RADAR;
				chan->dfs_state_entered = jअगरfies;

				अगर (qchan->dfs_state == QLINK_DFS_USABLE)
					chan->dfs_state = NL80211_DFS_USABLE;
				अन्यथा अगर (qchan->dfs_state ==
					QLINK_DFS_AVAILABLE)
					chan->dfs_state = NL80211_DFS_AVAILABLE;
				अन्यथा
					chan->dfs_state =
						NL80211_DFS_UNAVAILABLE;
			पूर्ण

			pr_debug("chan=%d flags=%#x max_pow=%d max_reg_pow=%d\n",
				 chan->hw_value, chan->flags, chan->max_घातer,
				 chan->max_reg_घातer);
			अवरोध;
		हाल WLAN_EID_HT_CAPABILITY:
			अगर (unlikely(tlv_dlen !=
				     माप(काष्ठा ieee80211_ht_cap))) अणु
				pr_err("bad HTCAP TLV len %zu\n", tlv_dlen);
				जाओ error_ret;
			पूर्ण

			qtnf_cmd_resp_band_fill_htcap(tlv->val, &band->ht_cap);
			अवरोध;
		हाल WLAN_EID_VHT_CAPABILITY:
			अगर (unlikely(tlv_dlen !=
				     माप(काष्ठा ieee80211_vht_cap))) अणु
				pr_err("bad VHTCAP TLV len %zu\n", tlv_dlen);
				जाओ error_ret;
			पूर्ण

			qtnf_cmd_resp_band_fill_vhtcap(tlv->val,
						       &band->vht_cap);
			अवरोध;
		हाल QTN_TLV_ID_IFTYPE_DATA:
			ret = qtnf_cmd_band_fill_अगरtype((स्थिर uपूर्णांक8_t *)tlv,
							band);
			अगर (ret)
				जाओ error_ret;
			अवरोध;
		शेष:
			pr_warn("unknown TLV type: %#x\n", tlv_type);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!qlink_tlv_parsing_ok(tlv, resp->info, payload_len)) अणु
		pr_err("Malformed TLV buffer\n");
		जाओ error_ret;
	पूर्ण

	अगर (band->n_channels != chidx) अणु
		pr_err("channel count mismatch: reported=%d, parsed=%d\n",
		       band->n_channels, chidx);
		जाओ error_ret;
	पूर्ण

	वापस 0;

error_ret:
	kमुक्त(band->channels);
	band->channels = शून्य;
	band->n_channels = 0;

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_get_mac_info(काष्ठा qtnf_wmac *mac)
अणु
	काष्ठा sk_buff *cmd_skb, *resp_skb = शून्य;
	स्थिर काष्ठा qlink_resp_get_mac_info *resp;
	माप_प्रकार var_data_len = 0;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, QLINK_VIFID_RSVD,
					    QLINK_CMD_MAC_INFO,
					    माप(काष्ठा qlink_cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(mac->bus);
	ret = qtnf_cmd_send_with_reply(mac->bus, cmd_skb, &resp_skb,
				       माप(*resp), &var_data_len);
	अगर (ret)
		जाओ out;

	resp = (स्थिर काष्ठा qlink_resp_get_mac_info *)resp_skb->data;
	ret = qtnf_cmd_resp_proc_mac_info(mac, resp);
	अगर (ret)
		जाओ out;

	ret = qtnf_parse_variable_mac_info(mac, resp, var_data_len);

out:
	qtnf_bus_unlock(mac->bus);
	consume_skb(resp_skb);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_get_hw_info(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा sk_buff *cmd_skb, *resp_skb = शून्य;
	स्थिर काष्ठा qlink_resp_get_hw_info *resp;
	माप_प्रकार info_len = 0;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(QLINK_MACID_RSVD, QLINK_VIFID_RSVD,
					    QLINK_CMD_GET_HW_INFO,
					    माप(काष्ठा qlink_cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(bus);
	ret = qtnf_cmd_send_with_reply(bus, cmd_skb, &resp_skb,
				       माप(*resp), &info_len);
	अगर (ret)
		जाओ out;

	resp = (स्थिर काष्ठा qlink_resp_get_hw_info *)resp_skb->data;
	ret = qtnf_cmd_resp_proc_hw_info(bus, resp, info_len);

out:
	qtnf_bus_unlock(bus);
	consume_skb(resp_skb);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_band_info_get(काष्ठा qtnf_wmac *mac,
			   काष्ठा ieee80211_supported_band *band)
अणु
	काष्ठा sk_buff *cmd_skb, *resp_skb = शून्य;
	काष्ठा qlink_cmd_band_info_get *cmd;
	काष्ठा qlink_resp_band_info_get *resp;
	माप_प्रकार info_len = 0;
	पूर्णांक ret = 0;
	u8 qband = qlink_utils_band_cfg2q(band->band);

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, 0,
					    QLINK_CMD_BAND_INFO_GET,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	cmd = (काष्ठा qlink_cmd_band_info_get *)cmd_skb->data;
	cmd->band = qband;

	qtnf_bus_lock(mac->bus);
	ret = qtnf_cmd_send_with_reply(mac->bus, cmd_skb, &resp_skb,
				       माप(*resp), &info_len);
	अगर (ret)
		जाओ out;

	resp = (काष्ठा qlink_resp_band_info_get *)resp_skb->data;
	अगर (resp->band != qband) अणु
		pr_err("MAC%u: reply band %u != cmd band %u\n", mac->macid,
		       resp->band, qband);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = qtnf_cmd_resp_fill_band_info(band, resp, info_len);

out:
	qtnf_bus_unlock(mac->bus);
	consume_skb(resp_skb);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_update_phy_params(काष्ठा qtnf_wmac *mac, u32 changed)
अणु
	काष्ठा wiphy *wiphy = priv_to_wiphy(mac);
	काष्ठा sk_buff *cmd_skb;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, 0,
					    QLINK_CMD_PHY_PARAMS_SET,
					    माप(काष्ठा qlink_cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(mac->bus);

	अगर (changed & WIPHY_PARAM_FRAG_THRESHOLD)
		qtnf_cmd_skb_put_tlv_u32(cmd_skb, QTN_TLV_ID_FRAG_THRESH,
					 wiphy->frag_threshold);
	अगर (changed & WIPHY_PARAM_RTS_THRESHOLD)
		qtnf_cmd_skb_put_tlv_u32(cmd_skb, QTN_TLV_ID_RTS_THRESH,
					 wiphy->rts_threshold);
	अगर (changed & WIPHY_PARAM_COVERAGE_CLASS)
		qtnf_cmd_skb_put_tlv_u32(cmd_skb, QTN_TLV_ID_COVERAGE_CLASS,
					 wiphy->coverage_class);

	अगर (changed & WIPHY_PARAM_RETRY_LONG)
		qtnf_cmd_skb_put_tlv_u32(cmd_skb, QTN_TLV_ID_LRETRY_LIMIT,
					 wiphy->retry_दीर्घ);

	अगर (changed & WIPHY_PARAM_RETRY_SHORT)
		qtnf_cmd_skb_put_tlv_u32(cmd_skb, QTN_TLV_ID_SRETRY_LIMIT,
					 wiphy->retry_लघु);

	ret = qtnf_cmd_send(mac->bus, cmd_skb);

	qtnf_bus_unlock(mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_init_fw(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा sk_buff *resp_skb = शून्य;
	काष्ठा qlink_resp_init_fw *resp;
	काष्ठा qlink_cmd_init_fw *cmd;
	काष्ठा sk_buff *cmd_skb;
	माप_प्रकार info_len = 0;
	पूर्णांक ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(QLINK_MACID_RSVD, QLINK_VIFID_RSVD,
					    QLINK_CMD_FW_INIT,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	cmd = (काष्ठा qlink_cmd_init_fw *)cmd_skb->data;
	cmd->qlink_proto_ver = cpu_to_le32(QLINK_PROTO_VER);

	qtnf_bus_lock(bus);
	ret = qtnf_cmd_send_with_reply(bus, cmd_skb, &resp_skb,
				       माप(*resp), &info_len);
	qtnf_bus_unlock(bus);

	अगर (ret)
		जाओ out;

	resp = (काष्ठा qlink_resp_init_fw *)resp_skb->data;
	bus->hw_info.ql_proto_ver = le32_to_cpu(resp->qlink_proto_ver);

out:
	consume_skb(resp_skb);
	वापस ret;
पूर्ण

व्योम qtnf_cmd_send_deinit_fw(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा sk_buff *cmd_skb;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(QLINK_MACID_RSVD, QLINK_VIFID_RSVD,
					    QLINK_CMD_FW_DEINIT,
					    माप(काष्ठा qlink_cmd));
	अगर (!cmd_skb)
		वापस;

	qtnf_bus_lock(bus);
	qtnf_cmd_send(bus, cmd_skb);
	qtnf_bus_unlock(bus);
पूर्ण

पूर्णांक qtnf_cmd_send_add_key(काष्ठा qtnf_vअगर *vअगर, u8 key_index, bool pairwise,
			  स्थिर u8 *mac_addr, काष्ठा key_params *params)
अणु
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_add_key *cmd;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_ADD_KEY,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(vअगर->mac->bus);

	cmd = (काष्ठा qlink_cmd_add_key *)cmd_skb->data;

	अगर (mac_addr)
		ether_addr_copy(cmd->addr, mac_addr);
	अन्यथा
		eth_broadcast_addr(cmd->addr);

	cmd->cipher = cpu_to_le32(params->cipher);
	cmd->key_index = key_index;
	cmd->pairwise = pairwise;

	अगर (params->key && params->key_len > 0)
		qtnf_cmd_skb_put_tlv_arr(cmd_skb, QTN_TLV_ID_KEY,
					 params->key,
					 params->key_len);

	अगर (params->seq && params->seq_len > 0)
		qtnf_cmd_skb_put_tlv_arr(cmd_skb, QTN_TLV_ID_SEQ,
					 params->seq,
					 params->seq_len);

	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);

	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_del_key(काष्ठा qtnf_vअगर *vअगर, u8 key_index, bool pairwise,
			  स्थिर u8 *mac_addr)
अणु
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_del_key *cmd;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_DEL_KEY,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(vअगर->mac->bus);

	cmd = (काष्ठा qlink_cmd_del_key *)cmd_skb->data;

	अगर (mac_addr)
		ether_addr_copy(cmd->addr, mac_addr);
	अन्यथा
		eth_broadcast_addr(cmd->addr);

	cmd->key_index = key_index;
	cmd->pairwise = pairwise;

	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);

	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_set_शेष_key(काष्ठा qtnf_vअगर *vअगर, u8 key_index,
				  bool unicast, bool multicast)
अणु
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_set_def_key *cmd;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_SET_DEFAULT_KEY,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(vअगर->mac->bus);

	cmd = (काष्ठा qlink_cmd_set_def_key *)cmd_skb->data;
	cmd->key_index = key_index;
	cmd->unicast = unicast;
	cmd->multicast = multicast;

	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);

	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_set_शेष_mgmt_key(काष्ठा qtnf_vअगर *vअगर, u8 key_index)
अणु
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_set_def_mgmt_key *cmd;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_SET_DEFAULT_MGMT_KEY,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(vअगर->mac->bus);

	cmd = (काष्ठा qlink_cmd_set_def_mgmt_key *)cmd_skb->data;
	cmd->key_index = key_index;

	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);

	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

अटल u32 qtnf_encode_sta_flags(u32 flags)
अणु
	u32 code = 0;

	अगर (flags & BIT(NL80211_STA_FLAG_AUTHORIZED))
		code |= QLINK_STA_FLAG_AUTHORIZED;
	अगर (flags & BIT(NL80211_STA_FLAG_SHORT_PREAMBLE))
		code |= QLINK_STA_FLAG_SHORT_PREAMBLE;
	अगर (flags & BIT(NL80211_STA_FLAG_WME))
		code |= QLINK_STA_FLAG_WME;
	अगर (flags & BIT(NL80211_STA_FLAG_MFP))
		code |= QLINK_STA_FLAG_MFP;
	अगर (flags & BIT(NL80211_STA_FLAG_AUTHENTICATED))
		code |= QLINK_STA_FLAG_AUTHENTICATED;
	अगर (flags & BIT(NL80211_STA_FLAG_TDLS_PEER))
		code |= QLINK_STA_FLAG_TDLS_PEER;
	अगर (flags & BIT(NL80211_STA_FLAG_ASSOCIATED))
		code |= QLINK_STA_FLAG_ASSOCIATED;
	वापस code;
पूर्ण

पूर्णांक qtnf_cmd_send_change_sta(काष्ठा qtnf_vअगर *vअगर, स्थिर u8 *mac,
			     काष्ठा station_parameters *params)
अणु
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_change_sta *cmd;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_CHANGE_STA,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(vअगर->mac->bus);

	cmd = (काष्ठा qlink_cmd_change_sta *)cmd_skb->data;
	ether_addr_copy(cmd->sta_addr, mac);
	cmd->flag_update.mask =
		cpu_to_le32(qtnf_encode_sta_flags(params->sta_flags_mask));
	cmd->flag_update.value =
		cpu_to_le32(qtnf_encode_sta_flags(params->sta_flags_set));

	चयन (vअगर->wdev.अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
		cmd->अगर_type = cpu_to_le16(QLINK_IFTYPE_AP);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		cmd->अगर_type = cpu_to_le16(QLINK_IFTYPE_STATION);
		अवरोध;
	शेष:
		pr_err("unsupported iftype %d\n", vअगर->wdev.अगरtype);
		dev_kमुक्त_skb(cmd_skb);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);

out:
	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_del_sta(काष्ठा qtnf_vअगर *vअगर,
			  काष्ठा station_del_parameters *params)
अणु
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_del_sta *cmd;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_DEL_STA,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(vअगर->mac->bus);

	cmd = (काष्ठा qlink_cmd_del_sta *)cmd_skb->data;

	अगर (params->mac)
		ether_addr_copy(cmd->sta_addr, params->mac);
	अन्यथा
		eth_broadcast_addr(cmd->sta_addr);	/* flush all stations */

	cmd->subtype = params->subtype;
	cmd->reason_code = cpu_to_le16(params->reason_code);

	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);

	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

अटल व्योम qtnf_cmd_channel_tlv_add(काष्ठा sk_buff *cmd_skb,
				     स्थिर काष्ठा ieee80211_channel *sc)
अणु
	काष्ठा qlink_tlv_channel *tlv;
	काष्ठा qlink_channel *qch;

	tlv = skb_put_zero(cmd_skb, माप(*tlv));
	qch = &tlv->chan;
	tlv->hdr.type = cpu_to_le16(QTN_TLV_ID_CHANNEL);
	tlv->hdr.len = cpu_to_le16(माप(*qch));

	qch->center_freq = cpu_to_le16(sc->center_freq);
	qch->hw_value = cpu_to_le16(sc->hw_value);
	qch->band = qlink_utils_band_cfg2q(sc->band);
	qch->max_घातer = sc->max_घातer;
	qch->max_reg_घातer = sc->max_reg_घातer;
	qch->max_antenna_gain = sc->max_antenna_gain;
	qch->beacon_found = sc->beacon_found;
	qch->dfs_state = qlink_utils_dfs_state_cfg2q(sc->dfs_state);
	qch->flags = cpu_to_le32(qlink_utils_chflags_cfg2q(sc->flags));
पूर्ण

अटल व्योम qtnf_cmd_अक्रमmac_tlv_add(काष्ठा sk_buff *cmd_skb,
				     स्थिर u8 *mac_addr,
				     स्थिर u8 *mac_addr_mask)
अणु
	काष्ठा qlink_अक्रमom_mac_addr *अक्रमmac;
	काष्ठा qlink_tlv_hdr *hdr =
		skb_put(cmd_skb, माप(*hdr) + माप(*अक्रमmac));

	hdr->type = cpu_to_le16(QTN_TLV_ID_RANDOM_MAC_ADDR);
	hdr->len = cpu_to_le16(माप(*अक्रमmac));
	अक्रमmac = (काष्ठा qlink_अक्रमom_mac_addr *)hdr->val;

	स_नकल(अक्रमmac->mac_addr, mac_addr, ETH_ALEN);
	स_नकल(अक्रमmac->mac_addr_mask, mac_addr_mask, ETH_ALEN);
पूर्ण

पूर्णांक qtnf_cmd_send_scan(काष्ठा qtnf_wmac *mac)
अणु
	काष्ठा cfg80211_scan_request *scan_req = mac->scan_req;
	u16 dwell_passive = QTNF_SCAN_DWELL_PASSIVE_DEFAULT;
	u16 dwell_active = QTNF_SCAN_DWELL_ACTIVE_DEFAULT;
	काष्ठा wireless_dev *wdev = scan_req->wdev;
	काष्ठा ieee80211_channel *sc;
	काष्ठा qlink_cmd_scan *cmd;
	काष्ठा sk_buff *cmd_skb;
	पूर्णांक n_channels = 0;
	u64 flags = 0;
	पूर्णांक count;
	पूर्णांक ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, QLINK_VIFID_RSVD,
					    QLINK_CMD_SCAN,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	cmd = (काष्ठा qlink_cmd_scan *)cmd_skb->data;

	अगर (scan_req->duration) अणु
		dwell_active = scan_req->duration;
		dwell_passive = scan_req->duration;
	पूर्ण अन्यथा अगर (wdev->अगरtype == NL80211_IFTYPE_STATION &&
		   wdev->current_bss) अणु
		/* let device select dwell based on traffic conditions */
		dwell_active = QTNF_SCAN_TIME_AUTO;
		dwell_passive = QTNF_SCAN_TIME_AUTO;
	पूर्ण

	cmd->n_ssids = cpu_to_le16(scan_req->n_ssids);
	क्रम (count = 0; count < scan_req->n_ssids; ++count) अणु
		qtnf_cmd_skb_put_tlv_arr(cmd_skb, WLAN_EID_SSID,
					 scan_req->ssids[count].ssid,
					 scan_req->ssids[count].ssid_len);
	पूर्ण

	अगर (scan_req->ie_len != 0)
		qtnf_cmd_tlv_ie_set_add(cmd_skb, QLINK_IE_SET_PROBE_REQ,
					scan_req->ie, scan_req->ie_len);

	क्रम (count = 0; count < scan_req->n_channels; ++count) अणु
		sc = scan_req->channels[count];
		अगर (sc->flags & IEEE80211_CHAN_DISABLED)
			जारी;

		pr_debug("[MAC%u] scan chan=%d, freq=%d, flags=%#x\n",
			 mac->macid, sc->hw_value, sc->center_freq,
			 sc->flags);

		qtnf_cmd_channel_tlv_add(cmd_skb, sc);
		++n_channels;
	पूर्ण

	अगर (scan_req->flags & NL80211_SCAN_FLAG_FLUSH)
		flags |= QLINK_SCAN_FLAG_FLUSH;

	अगर (scan_req->duration_mandatory)
		flags |= QLINK_SCAN_FLAG_DURATION_MANDATORY;

	cmd->n_channels = cpu_to_le16(n_channels);
	cmd->active_dwell = cpu_to_le16(dwell_active);
	cmd->passive_dwell = cpu_to_le16(dwell_passive);
	cmd->sample_duration = cpu_to_le16(QTNF_SCAN_SAMPLE_DURATION_DEFAULT);
	cmd->flags = cpu_to_le64(flags);

	pr_debug("[MAC%u] %s scan dwell active=%u passive=%u duration=%u\n",
		 mac->macid,
		 scan_req->duration_mandatory ? "mandatory" : "max",
		 dwell_active, dwell_passive,
		 QTNF_SCAN_SAMPLE_DURATION_DEFAULT);

	अगर (scan_req->flags & NL80211_SCAN_FLAG_RANDOM_ADDR) अणु
		pr_debug("[MAC%u] scan with random addr=%pM, mask=%pM\n",
			 mac->macid,
			 scan_req->mac_addr, scan_req->mac_addr_mask);
		qtnf_cmd_अक्रमmac_tlv_add(cmd_skb, scan_req->mac_addr,
					 scan_req->mac_addr_mask);
	पूर्ण

	qtnf_bus_lock(mac->bus);
	ret = qtnf_cmd_send(mac->bus, cmd_skb);
	qtnf_bus_unlock(mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_connect(काष्ठा qtnf_vअगर *vअगर,
			  काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_connect *cmd;
	काष्ठा qlink_auth_encr *aen;
	पूर्णांक ret;
	पूर्णांक i;
	u32 connect_flags = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_CONNECT,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	cmd = (काष्ठा qlink_cmd_connect *)cmd_skb->data;

	ether_addr_copy(cmd->bssid, vअगर->bssid);

	अगर (sme->bssid_hपूर्णांक)
		ether_addr_copy(cmd->bssid_hपूर्णांक, sme->bssid_hपूर्णांक);
	अन्यथा
		eth_zero_addr(cmd->bssid_hपूर्णांक);

	अगर (sme->prev_bssid)
		ether_addr_copy(cmd->prev_bssid, sme->prev_bssid);
	अन्यथा
		eth_zero_addr(cmd->prev_bssid);

	अगर ((sme->bg_scan_period >= 0) &&
	    (sme->bg_scan_period <= लघु_उच्च))
		cmd->bg_scan_period = cpu_to_le16(sme->bg_scan_period);
	अन्यथा
		cmd->bg_scan_period = cpu_to_le16(-1); /* use शेष value */

	अगर (sme->flags & ASSOC_REQ_DISABLE_HT)
		connect_flags |= QLINK_STA_CONNECT_DISABLE_HT;
	अगर (sme->flags & ASSOC_REQ_DISABLE_VHT)
		connect_flags |= QLINK_STA_CONNECT_DISABLE_VHT;
	अगर (sme->flags & ASSOC_REQ_USE_RRM)
		connect_flags |= QLINK_STA_CONNECT_USE_RRM;

	cmd->flags = cpu_to_le32(connect_flags);
	स_नकल(&cmd->ht_capa, &sme->ht_capa, माप(cmd->ht_capa));
	स_नकल(&cmd->ht_capa_mask, &sme->ht_capa_mask,
	       माप(cmd->ht_capa_mask));
	स_नकल(&cmd->vht_capa, &sme->vht_capa, माप(cmd->vht_capa));
	स_नकल(&cmd->vht_capa_mask, &sme->vht_capa_mask,
	       माप(cmd->vht_capa_mask));
	cmd->pbss = sme->pbss;

	aen = &cmd->aen;
	aen->auth_type = sme->auth_type;
	aen->privacy = !!sme->privacy;
	cmd->mfp = sme->mfp;
	aen->wpa_versions = cpu_to_le32(sme->crypto.wpa_versions);
	aen->cipher_group = cpu_to_le32(sme->crypto.cipher_group);
	aen->n_ciphers_pairwise = cpu_to_le32(sme->crypto.n_ciphers_pairwise);

	क्रम (i = 0; i < QLINK_MAX_NR_CIPHER_SUITES; i++)
		aen->ciphers_pairwise[i] =
			cpu_to_le32(sme->crypto.ciphers_pairwise[i]);

	aen->n_akm_suites = cpu_to_le32(sme->crypto.n_akm_suites);

	क्रम (i = 0; i < QLINK_MAX_NR_AKM_SUITES; i++)
		aen->akm_suites[i] = cpu_to_le32(sme->crypto.akm_suites[i]);

	aen->control_port = sme->crypto.control_port;
	aen->control_port_no_encrypt =
		sme->crypto.control_port_no_encrypt;
	aen->control_port_ethertype =
		cpu_to_le16(be16_to_cpu(sme->crypto.control_port_ethertype));

	qtnf_cmd_skb_put_tlv_arr(cmd_skb, WLAN_EID_SSID, sme->ssid,
				 sme->ssid_len);

	अगर (sme->ie_len != 0)
		qtnf_cmd_tlv_ie_set_add(cmd_skb, QLINK_IE_SET_ASSOC_REQ,
					sme->ie, sme->ie_len);

	अगर (sme->channel)
		qtnf_cmd_channel_tlv_add(cmd_skb, sme->channel);

	qtnf_bus_lock(vअगर->mac->bus);
	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);
	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_बाह्यal_auth(काष्ठा qtnf_vअगर *vअगर,
				काष्ठा cfg80211_बाह्यal_auth_params *auth)
अणु
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_बाह्यal_auth *cmd;
	पूर्णांक ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_EXTERNAL_AUTH,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	cmd = (काष्ठा qlink_cmd_बाह्यal_auth *)cmd_skb->data;

	ether_addr_copy(cmd->peer, auth->bssid);
	cmd->status = cpu_to_le16(auth->status);

	qtnf_bus_lock(vअगर->mac->bus);
	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);
	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_disconnect(काष्ठा qtnf_vअगर *vअगर, u16 reason_code)
अणु
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_disconnect *cmd;
	पूर्णांक ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_DISCONNECT,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(vअगर->mac->bus);

	cmd = (काष्ठा qlink_cmd_disconnect *)cmd_skb->data;
	cmd->reason = cpu_to_le16(reason_code);

	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);

	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_upकरोwn_पूर्णांकf(काष्ठा qtnf_vअगर *vअगर, bool up)
अणु
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_upकरोwn *cmd;
	पूर्णांक ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_UPDOWN_INTF,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	cmd = (काष्ठा qlink_cmd_upकरोwn *)cmd_skb->data;
	cmd->अगर_up = !!up;

	qtnf_bus_lock(vअगर->mac->bus);
	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);
	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_reg_notअगरy(काष्ठा qtnf_wmac *mac, काष्ठा regulatory_request *req,
			bool slave_radar, bool dfs_offload)
अणु
	काष्ठा wiphy *wiphy = priv_to_wiphy(mac);
	काष्ठा qtnf_bus *bus = mac->bus;
	काष्ठा sk_buff *cmd_skb;
	पूर्णांक ret;
	काष्ठा qlink_cmd_reg_notअगरy *cmd;
	क्रमागत nl80211_band band;
	स्थिर काष्ठा ieee80211_supported_band *cfg_band;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, QLINK_VIFID_RSVD,
					    QLINK_CMD_REG_NOTIFY,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	cmd = (काष्ठा qlink_cmd_reg_notअगरy *)cmd_skb->data;
	cmd->alpha2[0] = req->alpha2[0];
	cmd->alpha2[1] = req->alpha2[1];

	चयन (req->initiator) अणु
	हाल NL80211_REGDOM_SET_BY_CORE:
		cmd->initiator = QLINK_REGDOM_SET_BY_CORE;
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_USER:
		cmd->initiator = QLINK_REGDOM_SET_BY_USER;
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_DRIVER:
		cmd->initiator = QLINK_REGDOM_SET_BY_DRIVER;
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_COUNTRY_IE:
		cmd->initiator = QLINK_REGDOM_SET_BY_COUNTRY_IE;
		अवरोध;
	पूर्ण

	चयन (req->user_reg_hपूर्णांक_type) अणु
	हाल NL80211_USER_REG_HINT_USER:
		cmd->user_reg_hपूर्णांक_type = QLINK_USER_REG_HINT_USER;
		अवरोध;
	हाल NL80211_USER_REG_HINT_CELL_BASE:
		cmd->user_reg_hपूर्णांक_type = QLINK_USER_REG_HINT_CELL_BASE;
		अवरोध;
	हाल NL80211_USER_REG_HINT_INDOOR:
		cmd->user_reg_hपूर्णांक_type = QLINK_USER_REG_HINT_INDOOR;
		अवरोध;
	पूर्ण

	चयन (req->dfs_region) अणु
	हाल NL80211_DFS_FCC:
		cmd->dfs_region = QLINK_DFS_FCC;
		अवरोध;
	हाल NL80211_DFS_ETSI:
		cmd->dfs_region = QLINK_DFS_ETSI;
		अवरोध;
	हाल NL80211_DFS_JP:
		cmd->dfs_region = QLINK_DFS_JP;
		अवरोध;
	शेष:
		cmd->dfs_region = QLINK_DFS_UNSET;
		अवरोध;
	पूर्ण

	cmd->slave_radar = slave_radar;
	cmd->dfs_offload = dfs_offload;
	cmd->num_channels = 0;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		अचिन्हित पूर्णांक i;

		cfg_band = wiphy->bands[band];
		अगर (!cfg_band)
			जारी;

		cmd->num_channels += cfg_band->n_channels;

		क्रम (i = 0; i < cfg_band->n_channels; ++i) अणु
			qtnf_cmd_channel_tlv_add(cmd_skb,
						 &cfg_band->channels[i]);
		पूर्ण
	पूर्ण

	qtnf_bus_lock(bus);
	ret = qtnf_cmd_send(bus, cmd_skb);
	qtnf_bus_unlock(bus);

	वापस ret;
पूर्ण

अटल पूर्णांक
qtnf_cmd_resp_proc_chan_stat_info(काष्ठा survey_info *survey,
				  स्थिर u8 *payload, माप_प्रकार payload_len)
अणु
	स्थिर काष्ठा qlink_chan_stats *stats = शून्य;
	स्थिर काष्ठा qlink_tlv_hdr *tlv;
	u16 tlv_value_len;
	u16 tlv_type;
	स्थिर u8 *map = शून्य;
	अचिन्हित पूर्णांक map_len = 0;
	अचिन्हित पूर्णांक stats_len = 0;

	qlink_क्रम_each_tlv(tlv, payload, payload_len) अणु
		tlv_type = le16_to_cpu(tlv->type);
		tlv_value_len = le16_to_cpu(tlv->len);

		चयन (tlv_type) अणु
		हाल QTN_TLV_ID_BITMAP:
			map = tlv->val;
			map_len = tlv_value_len;
			अवरोध;
		हाल QTN_TLV_ID_CHANNEL_STATS:
			stats = (काष्ठा qlink_chan_stats *)tlv->val;
			stats_len = tlv_value_len;
			अवरोध;
		शेष:
			pr_info("Unknown TLV type: %#x\n", tlv_type);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!qlink_tlv_parsing_ok(tlv, payload, payload_len)) अणु
		pr_err("Malformed TLV buffer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!map || !stats)
		वापस 0;

#घोषणा qtnf_chan_stat_avail(stat_name, bitn)	\
	(qtnf_utils_is_bit_set(map, bitn, map_len) && \
	 (दुरत्वend(काष्ठा qlink_chan_stats, stat_name) <= stats_len))

	अगर (qtnf_chan_stat_avail(समय_on, QLINK_CHAN_STAT_TIME_ON)) अणु
		survey->filled |= SURVEY_INFO_TIME;
		survey->समय = le64_to_cpu(stats->समय_on);
	पूर्ण

	अगर (qtnf_chan_stat_avail(समय_प्रकारx, QLINK_CHAN_STAT_TIME_TX)) अणु
		survey->filled |= SURVEY_INFO_TIME_TX;
		survey->समय_प्रकारx = le64_to_cpu(stats->समय_प्रकारx);
	पूर्ण

	अगर (qtnf_chan_stat_avail(समय_rx, QLINK_CHAN_STAT_TIME_RX)) अणु
		survey->filled |= SURVEY_INFO_TIME_RX;
		survey->समय_rx = le64_to_cpu(stats->समय_rx);
	पूर्ण

	अगर (qtnf_chan_stat_avail(cca_busy, QLINK_CHAN_STAT_CCA_BUSY)) अणु
		survey->filled |= SURVEY_INFO_TIME_BUSY;
		survey->समय_busy = le64_to_cpu(stats->cca_busy);
	पूर्ण

	अगर (qtnf_chan_stat_avail(cca_busy_ext, QLINK_CHAN_STAT_CCA_BUSY_EXT)) अणु
		survey->filled |= SURVEY_INFO_TIME_EXT_BUSY;
		survey->समय_ext_busy = le64_to_cpu(stats->cca_busy_ext);
	पूर्ण

	अगर (qtnf_chan_stat_avail(समय_scan, QLINK_CHAN_STAT_TIME_SCAN)) अणु
		survey->filled |= SURVEY_INFO_TIME_SCAN;
		survey->समय_scan = le64_to_cpu(stats->समय_scan);
	पूर्ण

	अगर (qtnf_chan_stat_avail(chan_noise, QLINK_CHAN_STAT_CHAN_NOISE)) अणु
		survey->filled |= SURVEY_INFO_NOISE_DBM;
		survey->noise = stats->chan_noise;
	पूर्ण

#अघोषित qtnf_chan_stat_avail

	वापस 0;
पूर्ण

पूर्णांक qtnf_cmd_get_chan_stats(काष्ठा qtnf_wmac *mac, u32 chan_freq,
			    काष्ठा survey_info *survey)
अणु
	काष्ठा sk_buff *cmd_skb, *resp_skb = शून्य;
	काष्ठा qlink_cmd_get_chan_stats *cmd;
	काष्ठा qlink_resp_get_chan_stats *resp;
	माप_प्रकार var_data_len = 0;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, QLINK_VIFID_RSVD,
					    QLINK_CMD_CHAN_STATS,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	cmd = (काष्ठा qlink_cmd_get_chan_stats *)cmd_skb->data;
	cmd->channel_freq = cpu_to_le32(chan_freq);

	qtnf_bus_lock(mac->bus);
	ret = qtnf_cmd_send_with_reply(mac->bus, cmd_skb, &resp_skb,
				       माप(*resp), &var_data_len);
	qtnf_bus_unlock(mac->bus);

	अगर (ret)
		जाओ out;

	resp = (काष्ठा qlink_resp_get_chan_stats *)resp_skb->data;

	अगर (le32_to_cpu(resp->chan_freq) != chan_freq) अणु
		pr_err("[MAC%u] channel stats freq %u != requested %u\n",
		       mac->macid, le32_to_cpu(resp->chan_freq), chan_freq);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = qtnf_cmd_resp_proc_chan_stat_info(survey, resp->info,
						var_data_len);

out:
	consume_skb(resp_skb);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_chan_चयन(काष्ठा qtnf_vअगर *vअगर,
			      काष्ठा cfg80211_csa_settings *params)
अणु
	काष्ठा qtnf_wmac *mac = vअगर->mac;
	काष्ठा qlink_cmd_chan_चयन *cmd;
	काष्ठा sk_buff *cmd_skb;
	पूर्णांक ret;
	u64 flags = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, vअगर->vअगरid,
					    QLINK_CMD_CHAN_SWITCH,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	अगर (params->radar_required)
		flags |= QLINK_CHAN_SW_RADAR_REQUIRED;

	अगर (params->block_tx)
		flags |= QLINK_CHAN_SW_BLOCK_TX;

	cmd = (काष्ठा qlink_cmd_chan_चयन *)cmd_skb->data;
	qlink_chandef_cfg2q(&params->chandef, &cmd->channel);
	cmd->flags = cpu_to_le64(flags);
	cmd->beacon_count = params->count;

	qtnf_bus_lock(mac->bus);
	ret = qtnf_cmd_send(mac->bus, cmd_skb);
	qtnf_bus_unlock(mac->bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_get_channel(काष्ठा qtnf_vअगर *vअगर, काष्ठा cfg80211_chan_def *chdef)
अणु
	काष्ठा qtnf_bus *bus = vअगर->mac->bus;
	स्थिर काष्ठा qlink_resp_channel_get *resp;
	काष्ठा sk_buff *cmd_skb;
	काष्ठा sk_buff *resp_skb = शून्य;
	पूर्णांक ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_CHAN_GET,
					    माप(काष्ठा qlink_cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(bus);
	ret = qtnf_cmd_send_with_reply(bus, cmd_skb, &resp_skb,
				       माप(*resp), शून्य);
	अगर (ret)
		जाओ out;

	resp = (स्थिर काष्ठा qlink_resp_channel_get *)resp_skb->data;
	qlink_chandef_q2cfg(priv_to_wiphy(vअगर->mac), &resp->chan, chdef);

out:
	qtnf_bus_unlock(bus);
	consume_skb(resp_skb);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_start_cac(स्थिर काष्ठा qtnf_vअगर *vअगर,
		       स्थिर काष्ठा cfg80211_chan_def *chdef,
		       u32 cac_समय_ms)
अणु
	काष्ठा qtnf_bus *bus = vअगर->mac->bus;
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_start_cac *cmd;
	पूर्णांक ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_START_CAC,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	cmd = (काष्ठा qlink_cmd_start_cac *)cmd_skb->data;
	cmd->cac_समय_ms = cpu_to_le32(cac_समय_ms);
	qlink_chandef_cfg2q(chdef, &cmd->chan);

	qtnf_bus_lock(bus);
	ret = qtnf_cmd_send(bus, cmd_skb);
	qtnf_bus_unlock(bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_set_mac_acl(स्थिर काष्ठा qtnf_vअगर *vअगर,
			 स्थिर काष्ठा cfg80211_acl_data *params)
अणु
	काष्ठा qtnf_bus *bus = vअगर->mac->bus;
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_tlv_hdr *tlv;
	माप_प्रकार acl_size = काष्ठा_size(params, mac_addrs, params->n_acl_entries);
	पूर्णांक ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_SET_MAC_ACL,
					    माप(काष्ठा qlink_cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	tlv = skb_put(cmd_skb, माप(*tlv) + round_up(acl_size, QLINK_ALIGN));
	tlv->type = cpu_to_le16(QTN_TLV_ID_ACL_DATA);
	tlv->len = cpu_to_le16(acl_size);
	qlink_acl_data_cfg2q(params, (काष्ठा qlink_acl_data *)tlv->val);

	qtnf_bus_lock(bus);
	ret = qtnf_cmd_send(bus, cmd_skb);
	qtnf_bus_unlock(bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_pm_set(स्थिर काष्ठा qtnf_vअगर *vअगर, u8 pm_mode, पूर्णांक समयout)
अणु
	काष्ठा qtnf_bus *bus = vअगर->mac->bus;
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_pm_set *cmd;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_PM_SET, माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	cmd = (काष्ठा qlink_cmd_pm_set *)cmd_skb->data;
	cmd->pm_mode = pm_mode;
	cmd->pm_standby_समयr = cpu_to_le32(समयout);

	qtnf_bus_lock(bus);

	ret = qtnf_cmd_send(bus, cmd_skb);

	qtnf_bus_unlock(bus);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_get_tx_घातer(स्थिर काष्ठा qtnf_vअगर *vअगर, पूर्णांक *dbm)
अणु
	काष्ठा qtnf_bus *bus = vअगर->mac->bus;
	स्थिर काष्ठा qlink_resp_txpwr *resp;
	काष्ठा sk_buff *resp_skb = शून्य;
	काष्ठा qlink_cmd_txpwr *cmd;
	काष्ठा sk_buff *cmd_skb;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_TXPWR, माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	cmd = (काष्ठा qlink_cmd_txpwr *)cmd_skb->data;
	cmd->op_type = QLINK_TXPWR_GET;

	qtnf_bus_lock(bus);

	ret = qtnf_cmd_send_with_reply(bus, cmd_skb, &resp_skb,
				       माप(*resp), शून्य);
	अगर (ret)
		जाओ out;

	resp = (स्थिर काष्ठा qlink_resp_txpwr *)resp_skb->data;
	*dbm = MBM_TO_DBM(le32_to_cpu(resp->txpwr));

out:
	qtnf_bus_unlock(bus);
	consume_skb(resp_skb);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_set_tx_घातer(स्थिर काष्ठा qtnf_vअगर *vअगर,
			  क्रमागत nl80211_tx_घातer_setting type, पूर्णांक mbm)
अणु
	काष्ठा qtnf_bus *bus = vअगर->mac->bus;
	स्थिर काष्ठा qlink_resp_txpwr *resp;
	काष्ठा sk_buff *resp_skb = शून्य;
	काष्ठा qlink_cmd_txpwr *cmd;
	काष्ठा sk_buff *cmd_skb;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_TXPWR, माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	cmd = (काष्ठा qlink_cmd_txpwr *)cmd_skb->data;
	cmd->op_type = QLINK_TXPWR_SET;
	cmd->txpwr_setting = type;
	cmd->txpwr = cpu_to_le32(mbm);

	qtnf_bus_lock(bus);

	ret = qtnf_cmd_send_with_reply(bus, cmd_skb, &resp_skb,
				       माप(*resp), शून्य);

	qtnf_bus_unlock(bus);
	consume_skb(resp_skb);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_wowlan_set(स्थिर काष्ठा qtnf_vअगर *vअगर,
			     स्थिर काष्ठा cfg80211_wowlan *wowl)
अणु
	काष्ठा qtnf_bus *bus = vअगर->mac->bus;
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_wowlan_set *cmd;
	u32 triggers = 0;
	पूर्णांक count = 0;
	पूर्णांक ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_WOWLAN_SET, माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	qtnf_bus_lock(bus);

	cmd = (काष्ठा qlink_cmd_wowlan_set *)cmd_skb->data;

	अगर (wowl) अणु
		अगर (wowl->disconnect)
			triggers |=  QLINK_WOWLAN_TRIG_DISCONNECT;

		अगर (wowl->magic_pkt)
			triggers |= QLINK_WOWLAN_TRIG_MAGIC_PKT;

		अगर (wowl->n_patterns && wowl->patterns) अणु
			triggers |= QLINK_WOWLAN_TRIG_PATTERN_PKT;
			जबतक (count < wowl->n_patterns) अणु
				qtnf_cmd_skb_put_tlv_arr(cmd_skb,
					QTN_TLV_ID_WOWLAN_PATTERN,
					wowl->patterns[count].pattern,
					wowl->patterns[count].pattern_len);
				count++;
			पूर्ण
		पूर्ण
	पूर्ण

	cmd->triggers = cpu_to_le32(triggers);

	ret = qtnf_cmd_send(bus, cmd_skb);

	qtnf_bus_unlock(bus);
	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_netdev_changeupper(स्थिर काष्ठा qtnf_vअगर *vअगर, पूर्णांक br_करोमुख्य)
अणु
	काष्ठा qtnf_bus *bus = vअगर->mac->bus;
	काष्ठा sk_buff *cmd_skb;
	काष्ठा qlink_cmd_ndev_changeupper *cmd;
	पूर्णांक ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_NDEV_EVENT,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	pr_debug("[VIF%u.%u] set broadcast domain to %d\n",
		 vअगर->mac->macid, vअगर->vअगरid, br_करोमुख्य);

	cmd = (काष्ठा qlink_cmd_ndev_changeupper *)cmd_skb->data;
	cmd->nehdr.event = cpu_to_le16(QLINK_NDEV_EVENT_CHANGEUPPER);
	cmd->upper_type = QLINK_NDEV_UPPER_TYPE_BRIDGE;
	cmd->br_करोमुख्य = cpu_to_le32(br_करोमुख्य);

	qtnf_bus_lock(bus);
	ret = qtnf_cmd_send(bus, cmd_skb);
	qtnf_bus_unlock(bus);

	अगर (ret)
		pr_err("[VIF%u.%u] failed to set broadcast domain\n",
		       vअगर->mac->macid, vअगर->vअगरid);

	वापस ret;
पूर्ण

पूर्णांक qtnf_cmd_send_update_owe(काष्ठा qtnf_vअगर *vअगर,
			     काष्ठा cfg80211_update_owe_info *owe)
अणु
	काष्ठा qlink_cmd_update_owe *cmd;
	काष्ठा sk_buff *cmd_skb;
	पूर्णांक ret;

	अगर (माप(*cmd) + owe->ie_len > QTNF_MAX_CMD_BUF_SIZE) अणु
		pr_warn("VIF%u.%u: OWE update IEs too big: %zu\n",
			vअगर->mac->macid, vअगर->vअगरid, owe->ie_len);
		वापस -E2BIG;
	पूर्ण

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vअगर->mac->macid, vअगर->vअगरid,
					    QLINK_CMD_UPDATE_OWE,
					    माप(*cmd));
	अगर (!cmd_skb)
		वापस -ENOMEM;

	cmd = (काष्ठा qlink_cmd_update_owe *)cmd_skb->data;
	ether_addr_copy(cmd->peer, owe->peer);
	cmd->status = cpu_to_le16(owe->status);
	अगर (owe->ie_len && owe->ie)
		qtnf_cmd_skb_put_buffer(cmd_skb, owe->ie, owe->ie_len);

	qtnf_bus_lock(vअगर->mac->bus);
	ret = qtnf_cmd_send(vअगर->mac->bus, cmd_skb);
	qtnf_bus_unlock(vअगर->mac->bus);

	वापस ret;
पूर्ण
