<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Implementation of host-to-chip MIBs of WFxxx Split Mac (WSM) API.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 * Copyright (C) 2010, ST-Ericsson SA
 */

#समावेश <linux/etherdevice.h>

#समावेश "wfx.h"
#समावेश "hif_tx.h"
#समावेश "hif_tx_mib.h"
#समावेश "hif_api_mib.h"

पूर्णांक hअगर_set_output_घातer(काष्ठा wfx_vअगर *wvअगर, पूर्णांक val)
अणु
	काष्ठा hअगर_mib_current_tx_घातer_level arg = अणु
		.घातer_level = cpu_to_le32(val * 10),
	पूर्ण;

	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id,
			     HIF_MIB_ID_CURRENT_TX_POWER_LEVEL,
			     &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_set_beacon_wakeup_period(काष्ठा wfx_vअगर *wvअगर,
				 अचिन्हित पूर्णांक dtim_पूर्णांकerval,
				 अचिन्हित पूर्णांक listen_पूर्णांकerval)
अणु
	काष्ठा hअगर_mib_beacon_wake_up_period arg = अणु
		.wakeup_period_min = dtim_पूर्णांकerval,
		.receive_dtim = 0,
		.wakeup_period_max = listen_पूर्णांकerval,
	पूर्ण;

	अगर (dtim_पूर्णांकerval > 0xFF || listen_पूर्णांकerval > 0xFFFF)
		वापस -EINVAL;
	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id,
			     HIF_MIB_ID_BEACON_WAKEUP_PERIOD,
			     &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_set_rcpi_rssi_threshold(काष्ठा wfx_vअगर *wvअगर,
				पूर्णांक rssi_thold, पूर्णांक rssi_hyst)
अणु
	काष्ठा hअगर_mib_rcpi_rssi_threshold arg = अणु
		.rolling_average_count = 8,
		.detection = 1,
	पूर्ण;

	अगर (!rssi_thold && !rssi_hyst) अणु
		arg.upperthresh = 1;
		arg.lowerthresh = 1;
	पूर्ण अन्यथा अणु
		arg.upper_threshold = rssi_thold + rssi_hyst;
		arg.upper_threshold = (arg.upper_threshold + 110) * 2;
		arg.lower_threshold = rssi_thold;
		arg.lower_threshold = (arg.lower_threshold + 110) * 2;
	पूर्ण

	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id,
			     HIF_MIB_ID_RCPI_RSSI_THRESHOLD, &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_get_counters_table(काष्ठा wfx_dev *wdev, पूर्णांक vअगर_id,
			   काष्ठा hअगर_mib_extended_count_table *arg)
अणु
	अगर (wfx_api_older_than(wdev, 1, 3)) अणु
		// extended_count_table is wider than count_table
		स_रखो(arg, 0xFF, माप(*arg));
		वापस hअगर_पढ़ो_mib(wdev, vअगर_id, HIF_MIB_ID_COUNTERS_TABLE,
				    arg, माप(काष्ठा hअगर_mib_count_table));
	पूर्ण अन्यथा अणु
		वापस hअगर_पढ़ो_mib(wdev, vअगर_id,
				    HIF_MIB_ID_EXTENDED_COUNTERS_TABLE, arg,
				माप(काष्ठा hअगर_mib_extended_count_table));
	पूर्ण
पूर्ण

पूर्णांक hअगर_set_macaddr(काष्ठा wfx_vअगर *wvअगर, u8 *mac)
अणु
	काष्ठा hअगर_mib_mac_address msg = अणु पूर्ण;

	अगर (mac)
		ether_addr_copy(msg.mac_addr, mac);
	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id, HIF_MIB_ID_DOT11_MAC_ADDRESS,
			     &msg, माप(msg));
पूर्ण

पूर्णांक hअगर_set_rx_filter(काष्ठा wfx_vअगर *wvअगर,
		      bool filter_bssid, bool filter_prbreq)
अणु
	काष्ठा hअगर_mib_rx_filter arg = अणु पूर्ण;

	अगर (filter_bssid)
		arg.bssid_filter = 1;
	अगर (!filter_prbreq)
		arg.fwd_probe_req = 1;
	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id, HIF_MIB_ID_RX_FILTER,
			     &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_set_beacon_filter_table(काष्ठा wfx_vअगर *wvअगर, पूर्णांक tbl_len,
				स्थिर काष्ठा hअगर_ie_table_entry *tbl)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_mib_bcn_filter_table *arg;
	पूर्णांक buf_len = काष्ठा_size(arg, ie_table, tbl_len);

	arg = kzalloc(buf_len, GFP_KERNEL);
	अगर (!arg)
		वापस -ENOMEM;
	arg->num_of_info_elmts = cpu_to_le32(tbl_len);
	स_नकल(arg->ie_table, tbl, flex_array_size(arg, ie_table, tbl_len));
	ret = hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id,
			    HIF_MIB_ID_BEACON_FILTER_TABLE, arg, buf_len);
	kमुक्त(arg);
	वापस ret;
पूर्ण

पूर्णांक hअगर_beacon_filter_control(काष्ठा wfx_vअगर *wvअगर,
			      पूर्णांक enable, पूर्णांक beacon_count)
अणु
	काष्ठा hअगर_mib_bcn_filter_enable arg = अणु
		.enable = cpu_to_le32(enable),
		.bcn_count = cpu_to_le32(beacon_count),
	पूर्ण;
	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id,
			     HIF_MIB_ID_BEACON_FILTER_ENABLE,
			     &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_set_operational_mode(काष्ठा wfx_dev *wdev, क्रमागत hअगर_op_घातer_mode mode)
अणु
	काष्ठा hअगर_mib_gl_operational_घातer_mode arg = अणु
		.घातer_mode = mode,
		.wup_ind_activation = 1,
	पूर्ण;

	वापस hअगर_ग_लिखो_mib(wdev, -1, HIF_MIB_ID_GL_OPERATIONAL_POWER_MODE,
			     &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_set_ढाँचा_frame(काष्ठा wfx_vअगर *wvअगर, काष्ठा sk_buff *skb,
			   u8 frame_type, पूर्णांक init_rate)
अणु
	काष्ठा hअगर_mib_ढाँचा_frame *arg;

	WARN(skb->len > HIF_API_MAX_TEMPLATE_FRAME_SIZE, "frame is too big");
	skb_push(skb, 4);
	arg = (काष्ठा hअगर_mib_ढाँचा_frame *)skb->data;
	skb_pull(skb, 4);
	arg->init_rate = init_rate;
	arg->frame_type = frame_type;
	arg->frame_length = cpu_to_le16(skb->len);
	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id, HIF_MIB_ID_TEMPLATE_FRAME,
			     arg, माप(*arg) + skb->len);
पूर्ण

पूर्णांक hअगर_set_mfp(काष्ठा wfx_vअगर *wvअगर, bool capable, bool required)
अणु
	काष्ठा hअगर_mib_रक्षित_mgmt_policy arg = अणु पूर्ण;

	WARN(required && !capable, "incoherent arguments");
	अगर (capable) अणु
		arg.pmf_enable = 1;
		arg.host_enc_auth_frames = 1;
	पूर्ण
	अगर (!required)
		arg.unpmf_allowed = 1;
	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id,
			     HIF_MIB_ID_PROTECTED_MGMT_POLICY,
			     &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_set_block_ack_policy(काष्ठा wfx_vअगर *wvअगर,
			     u8 tx_tid_policy, u8 rx_tid_policy)
अणु
	काष्ठा hअगर_mib_block_ack_policy arg = अणु
		.block_ack_tx_tid_policy = tx_tid_policy,
		.block_ack_rx_tid_policy = rx_tid_policy,
	पूर्ण;

	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id, HIF_MIB_ID_BLOCK_ACK_POLICY,
			     &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_set_association_mode(काष्ठा wfx_vअगर *wvअगर, पूर्णांक ampdu_density,
			     bool greenfield, bool लघु_preamble)
अणु
	काष्ठा hअगर_mib_set_association_mode arg = अणु
		.preambtype_use = 1,
		.mode = 1,
		.spacing = 1,
		.लघु_preamble = लघु_preamble,
		.greenfield = greenfield,
		.mpdu_start_spacing = ampdu_density,
	पूर्ण;

	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id,
			     HIF_MIB_ID_SET_ASSOCIATION_MODE, &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_set_tx_rate_retry_policy(काष्ठा wfx_vअगर *wvअगर,
				 पूर्णांक policy_index, u8 *rates)
अणु
	काष्ठा hअगर_mib_set_tx_rate_retry_policy *arg;
	माप_प्रकार size = काष्ठा_size(arg, tx_rate_retry_policy, 1);
	पूर्णांक ret;

	arg = kzalloc(size, GFP_KERNEL);
	अगर (!arg)
		वापस -ENOMEM;
	arg->num_tx_rate_policies = 1;
	arg->tx_rate_retry_policy[0].policy_index = policy_index;
	arg->tx_rate_retry_policy[0].लघु_retry_count = 255;
	arg->tx_rate_retry_policy[0].दीर्घ_retry_count = 255;
	arg->tx_rate_retry_policy[0].first_rate_sel = 1;
	arg->tx_rate_retry_policy[0].terminate = 1;
	arg->tx_rate_retry_policy[0].count_init = 1;
	स_नकल(&arg->tx_rate_retry_policy[0].rates, rates,
	       माप(arg->tx_rate_retry_policy[0].rates));
	ret = hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id,
			    HIF_MIB_ID_SET_TX_RATE_RETRY_POLICY, arg, size);
	kमुक्त(arg);
	वापस ret;
पूर्ण

पूर्णांक hअगर_keep_alive_period(काष्ठा wfx_vअगर *wvअगर, पूर्णांक period)
अणु
	काष्ठा hअगर_mib_keep_alive_period arg = अणु
		.keep_alive_period = cpu_to_le16(period),
	पूर्ण;

	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id, HIF_MIB_ID_KEEP_ALIVE_PERIOD,
			     &arg, माप(arg));
पूर्ण;

पूर्णांक hअगर_set_arp_ipv4_filter(काष्ठा wfx_vअगर *wvअगर, पूर्णांक idx, __be32 *addr)
अणु
	काष्ठा hअगर_mib_arp_ip_addr_table arg = अणु
		.condition_idx = idx,
		.arp_enable = HIF_ARP_NS_FILTERING_DISABLE,
	पूर्ण;

	अगर (addr) अणु
		// Caution: type of addr is __be32
		स_नकल(arg.ipv4_address, addr, माप(arg.ipv4_address));
		arg.arp_enable = HIF_ARP_NS_FILTERING_ENABLE;
	पूर्ण
	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id,
			     HIF_MIB_ID_ARP_IP_ADDRESSES_TABLE,
			     &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_use_multi_tx_conf(काष्ठा wfx_dev *wdev, bool enable)
अणु
	काष्ठा hअगर_mib_gl_set_multi_msg arg = अणु
		.enable_multi_tx_conf = enable,
	पूर्ण;

	वापस hअगर_ग_लिखो_mib(wdev, -1, HIF_MIB_ID_GL_SET_MULTI_MSG,
			     &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_set_uapsd_info(काष्ठा wfx_vअगर *wvअगर, अचिन्हित दीर्घ val)
अणु
	काष्ठा hअगर_mib_set_uapsd_inक्रमmation arg = अणु पूर्ण;

	अगर (val & BIT(IEEE80211_AC_VO))
		arg.trig_voice = 1;
	अगर (val & BIT(IEEE80211_AC_VI))
		arg.trig_video = 1;
	अगर (val & BIT(IEEE80211_AC_BE))
		arg.trig_be = 1;
	अगर (val & BIT(IEEE80211_AC_BK))
		arg.trig_bckgrnd = 1;
	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id,
			     HIF_MIB_ID_SET_UAPSD_INFORMATION,
			     &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_erp_use_protection(काष्ठा wfx_vअगर *wvअगर, bool enable)
अणु
	काष्ठा hअगर_mib_non_erp_protection arg = अणु
		.use_cts_to_self = enable,
	पूर्ण;

	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id,
			     HIF_MIB_ID_NON_ERP_PROTECTION, &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_slot_समय(काष्ठा wfx_vअगर *wvअगर, पूर्णांक val)
अणु
	काष्ठा hअगर_mib_slot_समय arg = अणु
		.slot_समय = cpu_to_le32(val),
	पूर्ण;

	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id, HIF_MIB_ID_SLOT_TIME,
			     &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_wep_शेष_key_id(काष्ठा wfx_vअगर *wvअगर, पूर्णांक val)
अणु
	काष्ठा hअगर_mib_wep_शेष_key_id arg = अणु
		.wep_शेष_key_id = val,
	पूर्ण;

	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id,
			     HIF_MIB_ID_DOT11_WEP_DEFAULT_KEY_ID,
			     &arg, माप(arg));
पूर्ण

पूर्णांक hअगर_rts_threshold(काष्ठा wfx_vअगर *wvअगर, पूर्णांक val)
अणु
	काष्ठा hअगर_mib_करोt11_rts_threshold arg = अणु
		.threshold = cpu_to_le32(val >= 0 ? val : 0xFFFF),
	पूर्ण;

	वापस hअगर_ग_लिखो_mib(wvअगर->wdev, wvअगर->id,
			     HIF_MIB_ID_DOT11_RTS_THRESHOLD, &arg, माप(arg));
पूर्ण
