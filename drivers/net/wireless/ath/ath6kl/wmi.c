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

#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "testmode.h"
#समावेश "trace.h"
#समावेश "../regd.h"
#समावेश "../regd_common.h"

अटल पूर्णांक ath6kl_wmi_sync_poपूर्णांक(काष्ठा wmi *wmi, u8 अगर_idx);

अटल स्थिर s32 wmi_rate_tbl[][2] = अणु
	/* अणुW/O SGI, with SGIपूर्ण */
	अणु1000, 1000पूर्ण,
	अणु2000, 2000पूर्ण,
	अणु5500, 5500पूर्ण,
	अणु11000, 11000पूर्ण,
	अणु6000, 6000पूर्ण,
	अणु9000, 9000पूर्ण,
	अणु12000, 12000पूर्ण,
	अणु18000, 18000पूर्ण,
	अणु24000, 24000पूर्ण,
	अणु36000, 36000पूर्ण,
	अणु48000, 48000पूर्ण,
	अणु54000, 54000पूर्ण,
	अणु6500, 7200पूर्ण,
	अणु13000, 14400पूर्ण,
	अणु19500, 21700पूर्ण,
	अणु26000, 28900पूर्ण,
	अणु39000, 43300पूर्ण,
	अणु52000, 57800पूर्ण,
	अणु58500, 65000पूर्ण,
	अणु65000, 72200पूर्ण,
	अणु13500, 15000पूर्ण,
	अणु27000, 30000पूर्ण,
	अणु40500, 45000पूर्ण,
	अणु54000, 60000पूर्ण,
	अणु81000, 90000पूर्ण,
	अणु108000, 120000पूर्ण,
	अणु121500, 135000पूर्ण,
	अणु135000, 150000पूर्ण,
	अणु0, 0पूर्ण
पूर्ण;

अटल स्थिर s32 wmi_rate_tbl_mcs15[][2] = अणु
	/* अणुW/O SGI, with SGIपूर्ण */
	अणु1000, 1000पूर्ण,
	अणु2000, 2000पूर्ण,
	अणु5500, 5500पूर्ण,
	अणु11000, 11000पूर्ण,
	अणु6000, 6000पूर्ण,
	अणु9000, 9000पूर्ण,
	अणु12000, 12000पूर्ण,
	अणु18000, 18000पूर्ण,
	अणु24000, 24000पूर्ण,
	अणु36000, 36000पूर्ण,
	अणु48000, 48000पूर्ण,
	अणु54000, 54000पूर्ण,
	अणु6500, 7200पूर्ण,     /* HT 20, MCS 0 */
	अणु13000, 14400पूर्ण,
	अणु19500, 21700पूर्ण,
	अणु26000, 28900पूर्ण,
	अणु39000, 43300पूर्ण,
	अणु52000, 57800पूर्ण,
	अणु58500, 65000पूर्ण,
	अणु65000, 72200पूर्ण,
	अणु13000, 14400पूर्ण,   /* HT 20, MCS 8 */
	अणु26000, 28900पूर्ण,
	अणु39000, 43300पूर्ण,
	अणु52000, 57800पूर्ण,
	अणु78000, 86700पूर्ण,
	अणु104000, 115600पूर्ण,
	अणु117000, 130000पूर्ण,
	अणु130000, 144400पूर्ण, /* HT 20, MCS 15 */
	अणु13500, 15000पूर्ण,   /*HT 40, MCS 0 */
	अणु27000, 30000पूर्ण,
	अणु40500, 45000पूर्ण,
	अणु54000, 60000पूर्ण,
	अणु81000, 90000पूर्ण,
	अणु108000, 120000पूर्ण,
	अणु121500, 135000पूर्ण,
	अणु135000, 150000पूर्ण,
	अणु27000, 30000पूर्ण,   /*HT 40, MCS 8 */
	अणु54000, 60000पूर्ण,
	अणु81000, 90000पूर्ण,
	अणु108000, 120000पूर्ण,
	अणु162000, 180000पूर्ण,
	अणु216000, 240000पूर्ण,
	अणु243000, 270000पूर्ण,
	अणु270000, 300000पूर्ण, /*HT 40, MCS 15 */
	अणु0, 0पूर्ण
पूर्ण;

/* 802.1d to AC mapping. Refer pg 57 of WMM-test-plan-v1.2 */
अटल स्थिर u8 up_to_ac[] = अणु
	WMM_AC_BE,
	WMM_AC_BK,
	WMM_AC_BK,
	WMM_AC_BE,
	WMM_AC_VI,
	WMM_AC_VI,
	WMM_AC_VO,
	WMM_AC_VO,
पूर्ण;

व्योम ath6kl_wmi_set_control_ep(काष्ठा wmi *wmi, क्रमागत htc_endpoपूर्णांक_id ep_id)
अणु
	अगर (WARN_ON(ep_id == ENDPOINT_UNUSED || ep_id >= ENDPOपूर्णांक_उच्च))
		वापस;

	wmi->ep_id = ep_id;
पूर्ण

क्रमागत htc_endpoपूर्णांक_id ath6kl_wmi_get_control_ep(काष्ठा wmi *wmi)
अणु
	वापस wmi->ep_id;
पूर्ण

काष्ठा ath6kl_vअगर *ath6kl_get_vअगर_by_index(काष्ठा ath6kl *ar, u8 अगर_idx)
अणु
	काष्ठा ath6kl_vअगर *vअगर, *found = शून्य;

	अगर (WARN_ON(अगर_idx > (ar->vअगर_max - 1)))
		वापस शून्य;

	/* FIXME: Locking */
	spin_lock_bh(&ar->list_lock);
	list_क्रम_each_entry(vअगर, &ar->vअगर_list, list) अणु
		अगर (vअगर->fw_vअगर_idx == अगर_idx) अणु
			found = vअगर;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ar->list_lock);

	वापस found;
पूर्ण

/*  Perक्रमms DIX to 802.3 encapsulation क्रम transmit packets.
 *  Assumes the entire DIX header is contiguous and that there is
 *  enough room in the buffer क्रम a 802.3 mac header and LLC+SNAP headers.
 */
पूर्णांक ath6kl_wmi_dix_2_करोt3(काष्ठा wmi *wmi, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath6kl_llc_snap_hdr *llc_hdr;
	काष्ठा ethhdr *eth_hdr;
	माप_प्रकार new_len;
	__be16 type;
	u8 *datap;
	u16 size;

	अगर (WARN_ON(skb == शून्य))
		वापस -EINVAL;

	size = माप(काष्ठा ath6kl_llc_snap_hdr) + माप(काष्ठा wmi_data_hdr);
	अगर (skb_headroom(skb) < size)
		वापस -ENOMEM;

	eth_hdr = (काष्ठा ethhdr *) skb->data;
	type = eth_hdr->h_proto;

	अगर (!is_ethertype(be16_to_cpu(type))) अणु
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "%s: pkt is already in 802.3 format\n", __func__);
		वापस 0;
	पूर्ण

	new_len = skb->len - माप(*eth_hdr) + माप(*llc_hdr);

	skb_push(skb, माप(काष्ठा ath6kl_llc_snap_hdr));
	datap = skb->data;

	eth_hdr->h_proto = cpu_to_be16(new_len);

	स_नकल(datap, eth_hdr, माप(*eth_hdr));

	llc_hdr = (काष्ठा ath6kl_llc_snap_hdr *)(datap + माप(*eth_hdr));
	llc_hdr->dsap = 0xAA;
	llc_hdr->ssap = 0xAA;
	llc_hdr->cntl = 0x03;
	llc_hdr->org_code[0] = 0x0;
	llc_hdr->org_code[1] = 0x0;
	llc_hdr->org_code[2] = 0x0;
	llc_hdr->eth_type = type;

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_meta_add(काष्ठा wmi *wmi, काष्ठा sk_buff *skb,
			       u8 *version, व्योम *tx_meta_info)
अणु
	काष्ठा wmi_tx_meta_v1 *v1;
	काष्ठा wmi_tx_meta_v2 *v2;

	अगर (WARN_ON(skb == शून्य || version == शून्य))
		वापस -EINVAL;

	चयन (*version) अणु
	हाल WMI_META_VERSION_1:
		skb_push(skb, WMI_MAX_TX_META_SZ);
		v1 = (काष्ठा wmi_tx_meta_v1 *) skb->data;
		v1->pkt_id = 0;
		v1->rate_plcy_id = 0;
		*version = WMI_META_VERSION_1;
		अवरोध;
	हाल WMI_META_VERSION_2:
		skb_push(skb, WMI_MAX_TX_META_SZ);
		v2 = (काष्ठा wmi_tx_meta_v2 *) skb->data;
		स_नकल(v2, (काष्ठा wmi_tx_meta_v2 *) tx_meta_info,
		       माप(काष्ठा wmi_tx_meta_v2));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath6kl_wmi_data_hdr_add(काष्ठा wmi *wmi, काष्ठा sk_buff *skb,
			    u8 msg_type, u32 flags,
			    क्रमागत wmi_data_hdr_data_type data_type,
			    u8 meta_ver, व्योम *tx_meta_info, u8 अगर_idx)
अणु
	काष्ठा wmi_data_hdr *data_hdr;
	पूर्णांक ret;

	अगर (WARN_ON(skb == शून्य || (अगर_idx > wmi->parent_dev->vअगर_max - 1)))
		वापस -EINVAL;

	अगर (tx_meta_info) अणु
		ret = ath6kl_wmi_meta_add(wmi, skb, &meta_ver, tx_meta_info);
		अगर (ret)
			वापस ret;
	पूर्ण

	skb_push(skb, माप(काष्ठा wmi_data_hdr));

	data_hdr = (काष्ठा wmi_data_hdr *)skb->data;
	स_रखो(data_hdr, 0, माप(काष्ठा wmi_data_hdr));

	data_hdr->info = msg_type << WMI_DATA_HDR_MSG_TYPE_SHIFT;
	data_hdr->info |= data_type << WMI_DATA_HDR_DATA_TYPE_SHIFT;

	अगर (flags & WMI_DATA_HDR_FLAGS_MORE)
		data_hdr->info |= WMI_DATA_HDR_MORE;

	अगर (flags & WMI_DATA_HDR_FLAGS_EOSP)
		data_hdr->info3 |= cpu_to_le16(WMI_DATA_HDR_EOSP);

	data_hdr->info2 |= cpu_to_le16(meta_ver << WMI_DATA_HDR_META_SHIFT);
	data_hdr->info3 |= cpu_to_le16(अगर_idx & WMI_DATA_HDR_IF_IDX_MASK);

	वापस 0;
पूर्ण

u8 ath6kl_wmi_determine_user_priority(u8 *pkt, u32 layer2_pri)
अणु
	काष्ठा iphdr *ip_hdr = (काष्ठा iphdr *) pkt;
	u8 ip_pri;

	/*
	 * Determine IPTOS priority
	 *
	 * IP-TOS - 8bits
	 *          : DSCP(6-bits) ECN(2-bits)
	 *          : DSCP - P2 P1 P0 X X X
	 * where (P2 P1 P0) क्रमm 802.1D
	 */
	ip_pri = ip_hdr->tos >> 5;
	ip_pri &= 0x7;

	अगर ((layer2_pri & 0x7) > ip_pri)
		वापस (u8) layer2_pri & 0x7;
	अन्यथा
		वापस ip_pri;
पूर्ण

u8 ath6kl_wmi_get_traffic_class(u8 user_priority)
अणु
	वापस  up_to_ac[user_priority & 0x7];
पूर्ण

पूर्णांक ath6kl_wmi_implicit_create_pstream(काष्ठा wmi *wmi, u8 अगर_idx,
				       काष्ठा sk_buff *skb,
				       u32 layer2_priority, bool wmm_enabled,
				       u8 *ac)
अणु
	काष्ठा wmi_data_hdr *data_hdr;
	काष्ठा ath6kl_llc_snap_hdr *llc_hdr;
	काष्ठा wmi_create_pstream_cmd cmd;
	u32 meta_size, hdr_size;
	u16 ip_type = IP_ETHERTYPE;
	u8 stream_exist, usr_pri;
	u8 traffic_class = WMM_AC_BE;
	u8 *datap;

	अगर (WARN_ON(skb == शून्य))
		वापस -EINVAL;

	datap = skb->data;
	data_hdr = (काष्ठा wmi_data_hdr *) datap;

	meta_size = ((le16_to_cpu(data_hdr->info2) >> WMI_DATA_HDR_META_SHIFT) &
		     WMI_DATA_HDR_META_MASK) ? WMI_MAX_TX_META_SZ : 0;

	अगर (!wmm_enabled) अणु
		/* If WMM is disabled all traffic goes as BE traffic */
		usr_pri = 0;
	पूर्ण अन्यथा अणु
		hdr_size = माप(काष्ठा ethhdr);

		llc_hdr = (काष्ठा ath6kl_llc_snap_hdr *)(datap +
							 माप(काष्ठा
								wmi_data_hdr) +
							 meta_size + hdr_size);

		अगर (llc_hdr->eth_type == htons(ip_type)) अणु
			/*
			 * Extract the endpoपूर्णांक info from the TOS field
			 * in the IP header.
			 */
			usr_pri =
			   ath6kl_wmi_determine_user_priority(((u8 *) llc_hdr) +
					माप(काष्ठा ath6kl_llc_snap_hdr),
					layer2_priority);
		पूर्ण अन्यथा अणु
			usr_pri = layer2_priority & 0x7;
		पूर्ण

		/*
		 * Queue the EAPOL frames in the same WMM_AC_VO queue
		 * as that of management frames.
		 */
		अगर (skb->protocol == cpu_to_be16(ETH_P_PAE))
			usr_pri = WMI_VOICE_USER_PRIORITY;
	पूर्ण

	/*
	 * workaround क्रम WMM S5
	 *
	 * FIXME: wmi->traffic_class is always 100 so this test करोesn't
	 * make sense
	 */
	अगर ((wmi->traffic_class == WMM_AC_VI) &&
	    ((usr_pri == 5) || (usr_pri == 4)))
		usr_pri = 1;

	/* Convert user priority to traffic class */
	traffic_class = up_to_ac[usr_pri & 0x7];

	wmi_data_hdr_set_up(data_hdr, usr_pri);

	spin_lock_bh(&wmi->lock);
	stream_exist = wmi->fat_pipe_exist;
	spin_unlock_bh(&wmi->lock);

	अगर (!(stream_exist & (1 << traffic_class))) अणु
		स_रखो(&cmd, 0, माप(cmd));
		cmd.traffic_class = traffic_class;
		cmd.user_pri = usr_pri;
		cmd.inactivity_पूर्णांक =
			cpu_to_le32(WMI_IMPLICIT_PSTREAM_INACTIVITY_INT);
		/* Implicit streams are created with TSID 0xFF */
		cmd.tsid = WMI_IMPLICIT_PSTREAM;
		ath6kl_wmi_create_pstream_cmd(wmi, अगर_idx, &cmd);
	पूर्ण

	*ac = traffic_class;

	वापस 0;
पूर्ण

पूर्णांक ath6kl_wmi_करोt11_hdr_हटाओ(काष्ठा wmi *wmi, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr_3addr *pwh, wh;
	काष्ठा ath6kl_llc_snap_hdr *llc_hdr;
	काष्ठा ethhdr eth_hdr;
	u32 hdr_size;
	u8 *datap;
	__le16 sub_type;

	अगर (WARN_ON(skb == शून्य))
		वापस -EINVAL;

	datap = skb->data;
	pwh = (काष्ठा ieee80211_hdr_3addr *) datap;

	sub_type = pwh->frame_control & cpu_to_le16(IEEE80211_FCTL_STYPE);

	स_नकल((u8 *) &wh, datap, माप(काष्ठा ieee80211_hdr_3addr));

	/* Strip off the 802.11 header */
	अगर (sub_type == cpu_to_le16(IEEE80211_STYPE_QOS_DATA)) अणु
		hdr_size = roundup(माप(काष्ठा ieee80211_qos_hdr),
				   माप(u32));
		skb_pull(skb, hdr_size);
	पूर्ण अन्यथा अगर (sub_type == cpu_to_le16(IEEE80211_STYPE_DATA)) अणु
		skb_pull(skb, माप(काष्ठा ieee80211_hdr_3addr));
	पूर्ण

	datap = skb->data;
	llc_hdr = (काष्ठा ath6kl_llc_snap_hdr *)(datap);

	स_रखो(&eth_hdr, 0, माप(eth_hdr));
	eth_hdr.h_proto = llc_hdr->eth_type;

	चयन ((le16_to_cpu(wh.frame_control)) &
		(IEEE80211_FCTL_FROMDS | IEEE80211_FCTL_TODS)) अणु
	हाल IEEE80211_FCTL_TODS:
		स_नकल(eth_hdr.h_dest, wh.addr3, ETH_ALEN);
		स_नकल(eth_hdr.h_source, wh.addr2, ETH_ALEN);
		अवरोध;
	हाल IEEE80211_FCTL_FROMDS:
		स_नकल(eth_hdr.h_dest, wh.addr1, ETH_ALEN);
		स_नकल(eth_hdr.h_source, wh.addr3, ETH_ALEN);
		अवरोध;
	हाल IEEE80211_FCTL_FROMDS | IEEE80211_FCTL_TODS:
		अवरोध;
	शेष:
		स_नकल(eth_hdr.h_dest, wh.addr1, ETH_ALEN);
		स_नकल(eth_hdr.h_source, wh.addr2, ETH_ALEN);
		अवरोध;
	पूर्ण

	skb_pull(skb, माप(काष्ठा ath6kl_llc_snap_hdr));
	skb_push(skb, माप(eth_hdr));

	datap = skb->data;

	स_नकल(datap, &eth_hdr, माप(eth_hdr));

	वापस 0;
पूर्ण

/*
 * Perक्रमms 802.3 to DIX encapsulation क्रम received packets.
 * Assumes the entire 802.3 header is contiguous.
 */
पूर्णांक ath6kl_wmi_करोt3_2_dix(काष्ठा sk_buff *skb)
अणु
	काष्ठा ath6kl_llc_snap_hdr *llc_hdr;
	काष्ठा ethhdr eth_hdr;
	u8 *datap;

	अगर (WARN_ON(skb == शून्य))
		वापस -EINVAL;

	datap = skb->data;

	स_नकल(&eth_hdr, datap, माप(eth_hdr));

	llc_hdr = (काष्ठा ath6kl_llc_snap_hdr *) (datap + माप(eth_hdr));
	eth_hdr.h_proto = llc_hdr->eth_type;

	skb_pull(skb, माप(काष्ठा ath6kl_llc_snap_hdr));
	datap = skb->data;

	स_नकल(datap, &eth_hdr, माप(eth_hdr));

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_tx_complete_event_rx(u8 *datap, पूर्णांक len)
अणु
	काष्ठा tx_complete_msg_v1 *msg_v1;
	काष्ठा wmi_tx_complete_event *evt;
	पूर्णांक index;
	u16 size;

	evt = (काष्ठा wmi_tx_complete_event *) datap;

	ath6kl_dbg(ATH6KL_DBG_WMI, "comp: %d %d %d\n",
		   evt->num_msg, evt->msg_len, evt->msg_type);

	क्रम (index = 0; index < evt->num_msg; index++) अणु
		size = माप(काष्ठा wmi_tx_complete_event) +
		    (index * माप(काष्ठा tx_complete_msg_v1));
		msg_v1 = (काष्ठा tx_complete_msg_v1 *)(datap + size);

		ath6kl_dbg(ATH6KL_DBG_WMI, "msg: %d %d %d %d\n",
			   msg_v1->status, msg_v1->pkt_id,
			   msg_v1->rate_idx, msg_v1->ack_failures);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_reमुख्य_on_chnl_event_rx(काष्ठा wmi *wmi, u8 *datap,
					      पूर्णांक len, काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_reमुख्य_on_chnl_event *ev;
	u32 freq;
	u32 dur;
	काष्ठा ieee80211_channel *chan;
	काष्ठा ath6kl *ar = wmi->parent_dev;
	u32 id;

	अगर (len < माप(*ev))
		वापस -EINVAL;

	ev = (काष्ठा wmi_reमुख्य_on_chnl_event *) datap;
	freq = le32_to_cpu(ev->freq);
	dur = le32_to_cpu(ev->duration);
	ath6kl_dbg(ATH6KL_DBG_WMI, "remain_on_chnl: freq=%u dur=%u\n",
		   freq, dur);
	chan = ieee80211_get_channel(ar->wiphy, freq);
	अगर (!chan) अणु
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "remain_on_chnl: Unknown channel (freq=%u)\n",
			   freq);
		वापस -EINVAL;
	पूर्ण
	id = vअगर->last_roc_id;
	cfg80211_पढ़ोy_on_channel(&vअगर->wdev, id, chan,
				  dur, GFP_ATOMIC);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_cancel_reमुख्य_on_chnl_event_rx(काष्ठा wmi *wmi,
						     u8 *datap, पूर्णांक len,
						     काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_cancel_reमुख्य_on_chnl_event *ev;
	u32 freq;
	u32 dur;
	काष्ठा ieee80211_channel *chan;
	काष्ठा ath6kl *ar = wmi->parent_dev;
	u32 id;

	अगर (len < माप(*ev))
		वापस -EINVAL;

	ev = (काष्ठा wmi_cancel_reमुख्य_on_chnl_event *) datap;
	freq = le32_to_cpu(ev->freq);
	dur = le32_to_cpu(ev->duration);
	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "cancel_remain_on_chnl: freq=%u dur=%u status=%u\n",
		   freq, dur, ev->status);
	chan = ieee80211_get_channel(ar->wiphy, freq);
	अगर (!chan) अणु
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "cancel_remain_on_chnl: Unknown channel (freq=%u)\n",
			   freq);
		वापस -EINVAL;
	पूर्ण
	अगर (vअगर->last_cancel_roc_id &&
	    vअगर->last_cancel_roc_id + 1 == vअगर->last_roc_id)
		id = vअगर->last_cancel_roc_id; /* event क्रम cancel command */
	अन्यथा
		id = vअगर->last_roc_id; /* समयout on uncanceled r-o-c */
	vअगर->last_cancel_roc_id = 0;
	cfg80211_reमुख्य_on_channel_expired(&vअगर->wdev, id, chan, GFP_ATOMIC);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_tx_status_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
					 काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_tx_status_event *ev;
	u32 id;

	अगर (len < माप(*ev))
		वापस -EINVAL;

	ev = (काष्ठा wmi_tx_status_event *) datap;
	id = le32_to_cpu(ev->id);
	ath6kl_dbg(ATH6KL_DBG_WMI, "tx_status: id=%x ack_status=%u\n",
		   id, ev->ack_status);
	अगर (wmi->last_mgmt_tx_frame) अणु
		cfg80211_mgmt_tx_status(&vअगर->wdev, id,
					wmi->last_mgmt_tx_frame,
					wmi->last_mgmt_tx_frame_len,
					!!ev->ack_status, GFP_ATOMIC);
		kमुक्त(wmi->last_mgmt_tx_frame);
		wmi->last_mgmt_tx_frame = शून्य;
		wmi->last_mgmt_tx_frame_len = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_rx_probe_req_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
					    काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_p2p_rx_probe_req_event *ev;
	u32 freq;
	u16 dlen;

	अगर (len < माप(*ev))
		वापस -EINVAL;

	ev = (काष्ठा wmi_p2p_rx_probe_req_event *) datap;
	freq = le32_to_cpu(ev->freq);
	dlen = le16_to_cpu(ev->len);
	अगर (datap + len < ev->data + dlen) अणु
		ath6kl_err("invalid wmi_p2p_rx_probe_req_event: len=%d dlen=%u\n",
			   len, dlen);
		वापस -EINVAL;
	पूर्ण
	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "rx_probe_req: len=%u freq=%u probe_req_report=%d\n",
		   dlen, freq, vअगर->probe_req_report);

	अगर (vअगर->probe_req_report || vअगर->nw_type == AP_NETWORK)
		cfg80211_rx_mgmt(&vअगर->wdev, freq, 0, ev->data, dlen, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_p2p_capabilities_event_rx(u8 *datap, पूर्णांक len)
अणु
	काष्ठा wmi_p2p_capabilities_event *ev;
	u16 dlen;

	अगर (len < माप(*ev))
		वापस -EINVAL;

	ev = (काष्ठा wmi_p2p_capabilities_event *) datap;
	dlen = le16_to_cpu(ev->len);
	ath6kl_dbg(ATH6KL_DBG_WMI, "p2p_capab: len=%u\n", dlen);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_rx_action_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
					 काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_rx_action_event *ev;
	u32 freq;
	u16 dlen;

	अगर (len < माप(*ev))
		वापस -EINVAL;

	ev = (काष्ठा wmi_rx_action_event *) datap;
	freq = le32_to_cpu(ev->freq);
	dlen = le16_to_cpu(ev->len);
	अगर (datap + len < ev->data + dlen) अणु
		ath6kl_err("invalid wmi_rx_action_event: len=%d dlen=%u\n",
			   len, dlen);
		वापस -EINVAL;
	पूर्ण
	ath6kl_dbg(ATH6KL_DBG_WMI, "rx_action: len=%u freq=%u\n", dlen, freq);
	cfg80211_rx_mgmt(&vअगर->wdev, freq, 0, ev->data, dlen, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_p2p_info_event_rx(u8 *datap, पूर्णांक len)
अणु
	काष्ठा wmi_p2p_info_event *ev;
	u32 flags;
	u16 dlen;

	अगर (len < माप(*ev))
		वापस -EINVAL;

	ev = (काष्ठा wmi_p2p_info_event *) datap;
	flags = le32_to_cpu(ev->info_req_flags);
	dlen = le16_to_cpu(ev->len);
	ath6kl_dbg(ATH6KL_DBG_WMI, "p2p_info: flags=%x len=%d\n", flags, dlen);

	अगर (flags & P2P_FLAG_CAPABILITIES_REQ) अणु
		काष्ठा wmi_p2p_capabilities *cap;
		अगर (dlen < माप(*cap))
			वापस -EINVAL;
		cap = (काष्ठा wmi_p2p_capabilities *) ev->data;
		ath6kl_dbg(ATH6KL_DBG_WMI, "p2p_info: GO Power Save = %d\n",
			   cap->go_घातer_save);
	पूर्ण

	अगर (flags & P2P_FLAG_MACADDR_REQ) अणु
		काष्ठा wmi_p2p_macaddr *mac;
		अगर (dlen < माप(*mac))
			वापस -EINVAL;
		mac = (काष्ठा wmi_p2p_macaddr *) ev->data;
		ath6kl_dbg(ATH6KL_DBG_WMI, "p2p_info: MAC Address = %pM\n",
			   mac->mac_addr);
	पूर्ण

	अगर (flags & P2P_FLAG_HMODEL_REQ) अणु
		काष्ठा wmi_p2p_hmodel *mod;
		अगर (dlen < माप(*mod))
			वापस -EINVAL;
		mod = (काष्ठा wmi_p2p_hmodel *) ev->data;
		ath6kl_dbg(ATH6KL_DBG_WMI, "p2p_info: P2P Model = %d (%s)\n",
			   mod->p2p_model,
			   mod->p2p_model ? "host" : "firmware");
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *ath6kl_wmi_get_new_buf(u32 size)
अणु
	काष्ठा sk_buff *skb;

	skb = ath6kl_buf_alloc(size);
	अगर (!skb)
		वापस शून्य;

	skb_put(skb, size);
	अगर (size)
		स_रखो(skb->data, 0, size);

	वापस skb;
पूर्ण

/* Send a "simple" wmi command -- one with no arguments */
अटल पूर्णांक ath6kl_wmi_simple_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				 क्रमागत wmi_cmd_id cmd_id)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(0);
	अगर (!skb)
		वापस -ENOMEM;

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, cmd_id, NO_SYNC_WMIFLAG);

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_wmi_पढ़ोy_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len)
अणु
	काष्ठा wmi_पढ़ोy_event_2 *ev = (काष्ठा wmi_पढ़ोy_event_2 *) datap;

	अगर (len < माप(काष्ठा wmi_पढ़ोy_event_2))
		वापस -EINVAL;

	ath6kl_पढ़ोy_event(wmi->parent_dev, ev->mac_addr,
			   le32_to_cpu(ev->sw_version),
			   le32_to_cpu(ev->abi_version), ev->phy_cap);

	वापस 0;
पूर्ण

/*
 * Mechanism to modअगरy the roaming behavior in the firmware. The lower rssi
 * at which the station has to roam can be passed with
 * WMI_SET_LRSSI_SCAN_PARAMS. Subtract 96 from RSSI to get the संकेत level
 * in dBm.
 */
पूर्णांक ath6kl_wmi_set_roam_lrssi_cmd(काष्ठा wmi *wmi, u8 lrssi)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा roam_ctrl_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा roam_ctrl_cmd *) skb->data;

	cmd->info.params.lrssi_scan_period = cpu_to_le16(DEF_LRSSI_SCAN_PERIOD);
	cmd->info.params.lrssi_scan_threshold = a_cpu_to_sle16(lrssi +
						       DEF_SCAN_FOR_ROAM_INTVL);
	cmd->info.params.lrssi_roam_threshold = a_cpu_to_sle16(lrssi);
	cmd->info.params.roam_rssi_न्यूनमान = DEF_LRSSI_ROAM_FLOOR;
	cmd->roam_ctrl = WMI_SET_LRSSI_SCAN_PARAMS;

	वापस ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_SET_ROAM_CTRL_CMDID,
			    NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_क्रमce_roam_cmd(काष्ठा wmi *wmi, स्थिर u8 *bssid)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा roam_ctrl_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा roam_ctrl_cmd *) skb->data;

	स_नकल(cmd->info.bssid, bssid, ETH_ALEN);
	cmd->roam_ctrl = WMI_FORCE_ROAM;

	ath6kl_dbg(ATH6KL_DBG_WMI, "force roam to %pM\n", bssid);
	वापस ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_SET_ROAM_CTRL_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_ap_set_beacon_पूर्णांकvl_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				       u32 beacon_पूर्णांकvl)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा set_beacon_पूर्णांक_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा set_beacon_पूर्णांक_cmd *) skb->data;

	cmd->beacon_पूर्णांकvl = cpu_to_le32(beacon_पूर्णांकvl);
	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb,
				   WMI_SET_BEACON_INT_CMDID, NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_ap_set_dtim_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u32 dtim_period)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा set_dtim_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा set_dtim_cmd *) skb->data;

	cmd->dtim_period = cpu_to_le32(dtim_period);
	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb,
				   WMI_AP_SET_DTIM_CMDID, NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_set_roam_mode_cmd(काष्ठा wmi *wmi, क्रमागत wmi_roam_mode mode)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा roam_ctrl_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा roam_ctrl_cmd *) skb->data;

	cmd->info.roam_mode = mode;
	cmd->roam_ctrl = WMI_SET_ROAM_MODE;

	ath6kl_dbg(ATH6KL_DBG_WMI, "set roam mode %d\n", mode);
	वापस ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_SET_ROAM_CTRL_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

अटल पूर्णांक ath6kl_wmi_connect_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
				       काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_connect_event *ev;
	u8 *pie, *peie;

	अगर (len < माप(काष्ठा wmi_connect_event))
		वापस -EINVAL;

	ev = (काष्ठा wmi_connect_event *) datap;

	अगर (vअगर->nw_type == AP_NETWORK) अणु
		/* AP mode start/STA connected event */
		काष्ठा net_device *dev = vअगर->ndev;
		अगर (स_भेद(dev->dev_addr, ev->u.ap_bss.bssid, ETH_ALEN) == 0) अणु
			ath6kl_dbg(ATH6KL_DBG_WMI,
				   "%s: freq %d bssid %pM (AP started)\n",
				   __func__, le16_to_cpu(ev->u.ap_bss.ch),
				   ev->u.ap_bss.bssid);
			ath6kl_connect_ap_mode_bss(
				vअगर, le16_to_cpu(ev->u.ap_bss.ch));
		पूर्ण अन्यथा अणु
			ath6kl_dbg(ATH6KL_DBG_WMI,
				   "%s: aid %u mac_addr %pM auth=%u keymgmt=%u cipher=%u apsd_info=%u (STA connected)\n",
				   __func__, ev->u.ap_sta.aid,
				   ev->u.ap_sta.mac_addr,
				   ev->u.ap_sta.auth,
				   ev->u.ap_sta.keymgmt,
				   le16_to_cpu(ev->u.ap_sta.cipher),
				   ev->u.ap_sta.apsd_info);

			ath6kl_connect_ap_mode_sta(
				vअगर, ev->u.ap_sta.aid, ev->u.ap_sta.mac_addr,
				ev->u.ap_sta.keymgmt,
				le16_to_cpu(ev->u.ap_sta.cipher),
				ev->u.ap_sta.auth, ev->assoc_req_len,
				ev->assoc_info + ev->beacon_ie_len,
				ev->u.ap_sta.apsd_info);
		पूर्ण
		वापस 0;
	पूर्ण

	/* STA/IBSS mode connection event */

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "wmi event connect freq %d bssid %pM listen_intvl %d beacon_intvl %d type %d\n",
		   le16_to_cpu(ev->u.sta.ch), ev->u.sta.bssid,
		   le16_to_cpu(ev->u.sta.listen_पूर्णांकvl),
		   le16_to_cpu(ev->u.sta.beacon_पूर्णांकvl),
		   le32_to_cpu(ev->u.sta.nw_type));

	/* Start of assoc rsp IEs */
	pie = ev->assoc_info + ev->beacon_ie_len +
	      ev->assoc_req_len + (माप(u16) * 3); /* capinfo, status, aid */

	/* End of assoc rsp IEs */
	peie = ev->assoc_info + ev->beacon_ie_len + ev->assoc_req_len +
	    ev->assoc_resp_len;

	जबतक (pie < peie) अणु
		चयन (*pie) अणु
		हाल WLAN_EID_VENDOR_SPECIFIC:
			अगर (pie[1] > 3 && pie[2] == 0x00 && pie[3] == 0x50 &&
			    pie[4] == 0xf2 && pie[5] == WMM_OUI_TYPE) अणु
				/* WMM OUT (00:50:F2) */
				अगर (pie[1] > 5 &&
				    pie[6] == WMM_PARAM_OUI_SUBTYPE)
					wmi->is_wmm_enabled = true;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (wmi->is_wmm_enabled)
			अवरोध;

		pie += pie[1] + 2;
	पूर्ण

	ath6kl_connect_event(vअगर, le16_to_cpu(ev->u.sta.ch),
			     ev->u.sta.bssid,
			     le16_to_cpu(ev->u.sta.listen_पूर्णांकvl),
			     le16_to_cpu(ev->u.sta.beacon_पूर्णांकvl),
			     le32_to_cpu(ev->u.sta.nw_type),
			     ev->beacon_ie_len, ev->assoc_req_len,
			     ev->assoc_resp_len, ev->assoc_info);

	वापस 0;
पूर्ण

अटल काष्ठा country_code_to_क्रमागत_rd *
ath6kl_regd_find_country(u16 countryCode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(allCountries); i++) अणु
		अगर (allCountries[i].countryCode == countryCode)
			वापस &allCountries[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा reg_dmn_pair_mapping *
ath6kl_get_regpair(u16 regdmn)
अणु
	पूर्णांक i;

	अगर (regdmn == NO_ENUMRD)
		वापस शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(regDoमुख्यPairs); i++) अणु
		अगर (regDoमुख्यPairs[i].reg_करोमुख्य == regdmn)
			वापस &regDoमुख्यPairs[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा country_code_to_क्रमागत_rd *
ath6kl_regd_find_country_by_rd(u16 regdmn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(allCountries); i++) अणु
		अगर (allCountries[i].regDmnEnum == regdmn)
			वापस &allCountries[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम ath6kl_wmi_regकरोमुख्य_event(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len)
अणु
	काष्ठा ath6kl_wmi_regकरोमुख्य *ev;
	काष्ठा country_code_to_क्रमागत_rd *country = शून्य;
	काष्ठा reg_dmn_pair_mapping *regpair = शून्य;
	अक्षर alpha2[2];
	u32 reg_code;

	ev = (काष्ठा ath6kl_wmi_regकरोमुख्य *) datap;
	reg_code = le32_to_cpu(ev->reg_code);

	अगर ((reg_code >> ATH6KL_COUNTRY_RD_SHIFT) & COUNTRY_ERD_FLAG) अणु
		country = ath6kl_regd_find_country((u16) reg_code);
	पूर्ण अन्यथा अगर (!(((u16) reg_code & WORLD_SKU_MASK) == WORLD_SKU_PREFIX)) अणु
		regpair = ath6kl_get_regpair((u16) reg_code);
		country = ath6kl_regd_find_country_by_rd((u16) reg_code);
		अगर (regpair)
			ath6kl_dbg(ATH6KL_DBG_WMI, "Regpair used: 0x%0x\n",
				   regpair->reg_करोमुख्य);
		अन्यथा
			ath6kl_warn("Regpair not found reg_code 0x%0x\n",
				    reg_code);
	पूर्ण

	अगर (country && wmi->parent_dev->wiphy_रेजिस्टरed) अणु
		alpha2[0] = country->isoName[0];
		alpha2[1] = country->isoName[1];

		regulatory_hपूर्णांक(wmi->parent_dev->wiphy, alpha2);

		ath6kl_dbg(ATH6KL_DBG_WMI, "Country alpha2 being used: %c%c\n",
			   alpha2[0], alpha2[1]);
	पूर्ण
पूर्ण

अटल पूर्णांक ath6kl_wmi_disconnect_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
					  काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_disconnect_event *ev;
	wmi->traffic_class = 100;

	अगर (len < माप(काष्ठा wmi_disconnect_event))
		वापस -EINVAL;

	ev = (काष्ठा wmi_disconnect_event *) datap;

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "wmi event disconnect proto_reason %d bssid %pM wmi_reason %d assoc_resp_len %d\n",
		   le16_to_cpu(ev->proto_reason_status), ev->bssid,
		   ev->disconn_reason, ev->assoc_resp_len);

	wmi->is_wmm_enabled = false;

	ath6kl_disconnect_event(vअगर, ev->disconn_reason,
				ev->bssid, ev->assoc_resp_len, ev->assoc_info,
				le16_to_cpu(ev->proto_reason_status));

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_peer_node_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len)
अणु
	काष्ठा wmi_peer_node_event *ev;

	अगर (len < माप(काष्ठा wmi_peer_node_event))
		वापस -EINVAL;

	ev = (काष्ठा wmi_peer_node_event *) datap;

	अगर (ev->event_code == PEER_NODE_JOIN_EVENT)
		ath6kl_dbg(ATH6KL_DBG_WMI, "joined node with mac addr: %pM\n",
			   ev->peer_mac_addr);
	अन्यथा अगर (ev->event_code == PEER_NODE_LEAVE_EVENT)
		ath6kl_dbg(ATH6KL_DBG_WMI, "left node with mac addr: %pM\n",
			   ev->peer_mac_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_tkip_micerr_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
					   काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_tkip_micerr_event *ev;

	अगर (len < माप(काष्ठा wmi_tkip_micerr_event))
		वापस -EINVAL;

	ev = (काष्ठा wmi_tkip_micerr_event *) datap;

	ath6kl_tkip_micerr_event(vअगर, ev->key_id, ev->is_mcast);

	वापस 0;
पूर्ण

व्योम ath6kl_wmi_sscan_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ath6kl_vअगर *vअगर = from_समयr(vअगर, t, sched_scan_समयr);

	cfg80211_sched_scan_results(vअगर->ar->wiphy, 0);
पूर्ण

अटल पूर्णांक ath6kl_wmi_bssinfo_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
				       काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_bss_info_hdr2 *bih;
	u8 *buf;
	काष्ठा ieee80211_channel *channel;
	काष्ठा ath6kl *ar = wmi->parent_dev;
	काष्ठा cfg80211_bss *bss;

	अगर (len <= माप(काष्ठा wmi_bss_info_hdr2))
		वापस -EINVAL;

	bih = (काष्ठा wmi_bss_info_hdr2 *) datap;
	buf = datap + माप(काष्ठा wmi_bss_info_hdr2);
	len -= माप(काष्ठा wmi_bss_info_hdr2);

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "bss info evt - ch %u, snr %d, rssi %d, bssid \"%pM\" "
		   "frame_type=%d\n",
		   bih->ch, bih->snr, bih->snr - 95, bih->bssid,
		   bih->frame_type);

	अगर (bih->frame_type != BEACON_FTYPE &&
	    bih->frame_type != PROBERESP_FTYPE)
		वापस 0; /* Only update BSS table क्रम now */

	अगर (bih->frame_type == BEACON_FTYPE &&
	    test_bit(CLEAR_BSSFILTER_ON_BEACON, &vअगर->flags)) अणु
		clear_bit(CLEAR_BSSFILTER_ON_BEACON, &vअगर->flags);
		ath6kl_wmi_bssfilter_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					 NONE_BSS_FILTER, 0);
	पूर्ण

	channel = ieee80211_get_channel(ar->wiphy, le16_to_cpu(bih->ch));
	अगर (channel == शून्य)
		वापस -EINVAL;

	अगर (len < 8 + 2 + 2)
		वापस -EINVAL;

	अगर (bih->frame_type == BEACON_FTYPE &&
	    test_bit(CONNECTED, &vअगर->flags) &&
	    स_भेद(bih->bssid, vअगर->bssid, ETH_ALEN) == 0) अणु
		स्थिर u8 *tim;
		tim = cfg80211_find_ie(WLAN_EID_TIM, buf + 8 + 2 + 2,
				       len - 8 - 2 - 2);
		अगर (tim && tim[1] >= 2) अणु
			vअगर->assoc_bss_dtim_period = tim[3];
			set_bit(DTIM_PERIOD_AVAIL, &vअगर->flags);
		पूर्ण
	पूर्ण

	bss = cfg80211_inक्रमm_bss(ar->wiphy, channel,
				  bih->frame_type == BEACON_FTYPE ?
					CFG80211_BSS_FTYPE_BEACON :
					CFG80211_BSS_FTYPE_PRESP,
				  bih->bssid, get_unaligned_le64((__le64 *)buf),
				  get_unaligned_le16(((__le16 *)buf) + 5),
				  get_unaligned_le16(((__le16 *)buf) + 4),
				  buf + 8 + 2 + 2, len - 8 - 2 - 2,
				  (bih->snr - 95) * 100, GFP_ATOMIC);
	अगर (bss == शून्य)
		वापस -ENOMEM;
	cfg80211_put_bss(ar->wiphy, bss);

	/*
	 * Firmware करोesn't वापस any event when scheduled scan has
	 * finished, so we need to use a समयr to find out when there are
	 * no more results.
	 *
	 * The समयr is started from the first bss info received, otherwise
	 * the समयr would not ever fire अगर the scan पूर्णांकerval is लघु
	 * enough.
	 */
	अगर (test_bit(SCHED_SCANNING, &vअगर->flags) &&
	    !समयr_pending(&vअगर->sched_scan_समयr)) अणु
		mod_समयr(&vअगर->sched_scan_समयr, jअगरfies +
			  msecs_to_jअगरfies(ATH6KL_SCHED_SCAN_RESULT_DELAY));
	पूर्ण

	वापस 0;
पूर्ण

/* Inactivity समयout of a fatpipe(pstream) at the target */
अटल पूर्णांक ath6kl_wmi_pstream_समयout_event_rx(काष्ठा wmi *wmi, u8 *datap,
					       पूर्णांक len)
अणु
	काष्ठा wmi_pstream_समयout_event *ev;

	अगर (len < माप(काष्ठा wmi_pstream_समयout_event))
		वापस -EINVAL;

	ev = (काष्ठा wmi_pstream_समयout_event *) datap;
	अगर (ev->traffic_class >= WMM_NUM_AC) अणु
		ath6kl_err("invalid traffic class: %d\n", ev->traffic_class);
		वापस -EINVAL;
	पूर्ण

	/*
	 * When the pstream (fat pipe == AC) बारout, it means there were
	 * no thinStreams within this pstream & it got implicitly created
	 * due to data flow on this AC. We start the inactivity समयr only
	 * क्रम implicitly created pstream. Just reset the host state.
	 */
	spin_lock_bh(&wmi->lock);
	wmi->stream_exist_क्रम_ac[ev->traffic_class] = 0;
	wmi->fat_pipe_exist &= ~(1 << ev->traffic_class);
	spin_unlock_bh(&wmi->lock);

	/* Indicate inactivity to driver layer क्रम this fatpipe (pstream) */
	ath6kl_indicate_tx_activity(wmi->parent_dev, ev->traffic_class, false);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_bitrate_reply_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len)
अणु
	काष्ठा wmi_bit_rate_reply *reply;
	u32 index;

	अगर (len < माप(काष्ठा wmi_bit_rate_reply))
		वापस -EINVAL;

	reply = (काष्ठा wmi_bit_rate_reply *) datap;

	ath6kl_dbg(ATH6KL_DBG_WMI, "rateindex %d\n", reply->rate_index);

	अगर (reply->rate_index != (s8) RATE_AUTO) अणु
		index = reply->rate_index & 0x7f;
		अगर (WARN_ON_ONCE(index > (RATE_MCS_7_40 + 1)))
			वापस -EINVAL;
	पूर्ण

	ath6kl_wakeup_event(wmi->parent_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_test_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len)
अणु
	ath6kl_पंचांग_rx_event(wmi->parent_dev, datap, len);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_ratemask_reply_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len)
अणु
	अगर (len < माप(काष्ठा wmi_fix_rates_reply))
		वापस -EINVAL;

	ath6kl_wakeup_event(wmi->parent_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_ch_list_reply_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len)
अणु
	अगर (len < माप(काष्ठा wmi_channel_list_reply))
		वापस -EINVAL;

	ath6kl_wakeup_event(wmi->parent_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_tx_pwr_reply_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len)
अणु
	काष्ठा wmi_tx_pwr_reply *reply;

	अगर (len < माप(काष्ठा wmi_tx_pwr_reply))
		वापस -EINVAL;

	reply = (काष्ठा wmi_tx_pwr_reply *) datap;
	ath6kl_txpwr_rx_evt(wmi->parent_dev, reply->dbM);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_keepalive_reply_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len)
अणु
	अगर (len < माप(काष्ठा wmi_get_keepalive_cmd))
		वापस -EINVAL;

	ath6kl_wakeup_event(wmi->parent_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_scan_complete_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
				       काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_scan_complete_event *ev;

	ev = (काष्ठा wmi_scan_complete_event *) datap;

	ath6kl_scan_complete_evt(vअगर, a_sle32_to_cpu(ev->status));
	wmi->is_probe_ssid = false;

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_neighbor_report_event_rx(काष्ठा wmi *wmi, u8 *datap,
					       पूर्णांक len, काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_neighbor_report_event *ev;
	u8 i;

	अगर (len < माप(*ev))
		वापस -EINVAL;
	ev = (काष्ठा wmi_neighbor_report_event *) datap;
	अगर (काष्ठा_size(ev, neighbor, ev->num_neighbors) > len) अणु
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "truncated neighbor event (num=%d len=%d)\n",
			   ev->num_neighbors, len);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < ev->num_neighbors; i++) अणु
		ath6kl_dbg(ATH6KL_DBG_WMI, "neighbor %d/%d - %pM 0x%x\n",
			   i + 1, ev->num_neighbors, ev->neighbor[i].bssid,
			   ev->neighbor[i].bss_flags);
		cfg80211_pmksa_candidate_notअगरy(vअगर->ndev, i,
						ev->neighbor[i].bssid,
						!!(ev->neighbor[i].bss_flags &
						   WMI_PREAUTH_CAPABLE_BSS),
						GFP_ATOMIC);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Target is reporting a programming error.  This is क्रम
 * developer aid only.  Target only checks a few common violations
 * and it is responsibility of host to करो all error checking.
 * Behavior of target after wmi error event is undefined.
 * A reset is recommended.
 */
अटल पूर्णांक ath6kl_wmi_error_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len)
अणु
	स्थिर अक्षर *type = "unknown error";
	काष्ठा wmi_cmd_error_event *ev;
	ev = (काष्ठा wmi_cmd_error_event *) datap;

	चयन (ev->err_code) अणु
	हाल INVALID_PARAM:
		type = "invalid parameter";
		अवरोध;
	हाल ILLEGAL_STATE:
		type = "invalid state";
		अवरोध;
	हाल INTERNAL_ERROR:
		type = "internal error";
		अवरोध;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_WMI, "programming error, cmd=%d %s\n",
		   ev->cmd_id, type);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_stats_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
				     काष्ठा ath6kl_vअगर *vअगर)
अणु
	ath6kl_tgt_stats_event(vअगर, datap, len);

	वापस 0;
पूर्ण

अटल u8 ath6kl_wmi_get_upper_threshold(s16 rssi,
					 काष्ठा sq_threshold_params *sq_thresh,
					 u32 size)
अणु
	u32 index;
	u8 threshold = (u8) sq_thresh->upper_threshold[size - 1];

	/* The list is alपढ़ोy in sorted order. Get the next lower value */
	क्रम (index = 0; index < size; index++) अणु
		अगर (rssi < sq_thresh->upper_threshold[index]) अणु
			threshold = (u8) sq_thresh->upper_threshold[index];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस threshold;
पूर्ण

अटल u8 ath6kl_wmi_get_lower_threshold(s16 rssi,
					 काष्ठा sq_threshold_params *sq_thresh,
					 u32 size)
अणु
	u32 index;
	u8 threshold = (u8) sq_thresh->lower_threshold[size - 1];

	/* The list is alपढ़ोy in sorted order. Get the next lower value */
	क्रम (index = 0; index < size; index++) अणु
		अगर (rssi > sq_thresh->lower_threshold[index]) अणु
			threshold = (u8) sq_thresh->lower_threshold[index];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस threshold;
पूर्ण

अटल पूर्णांक ath6kl_wmi_send_rssi_threshold_params(काष्ठा wmi *wmi,
			काष्ठा wmi_rssi_threshold_params_cmd *rssi_cmd)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_rssi_threshold_params_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_rssi_threshold_params_cmd *) skb->data;
	स_नकल(cmd, rssi_cmd, माप(काष्ठा wmi_rssi_threshold_params_cmd));

	वापस ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_RSSI_THRESHOLD_PARAMS_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

अटल पूर्णांक ath6kl_wmi_rssi_threshold_event_rx(काष्ठा wmi *wmi, u8 *datap,
					      पूर्णांक len)
अणु
	काष्ठा wmi_rssi_threshold_event *reply;
	काष्ठा wmi_rssi_threshold_params_cmd cmd;
	काष्ठा sq_threshold_params *sq_thresh;
	क्रमागत wmi_rssi_threshold_val new_threshold;
	u8 upper_rssi_threshold, lower_rssi_threshold;
	s16 rssi;
	पूर्णांक ret;

	अगर (len < माप(काष्ठा wmi_rssi_threshold_event))
		वापस -EINVAL;

	reply = (काष्ठा wmi_rssi_threshold_event *) datap;
	new_threshold = (क्रमागत wmi_rssi_threshold_val) reply->range;
	rssi = a_sle16_to_cpu(reply->rssi);

	sq_thresh = &wmi->sq_threshld[SIGNAL_QUALITY_METRICS_RSSI];

	/*
	 * Identअगरy the threshold breached and communicate that to the app.
	 * After that install a new set of thresholds based on the संकेत
	 * quality reported by the target
	 */
	अगर (new_threshold) अणु
		/* Upper threshold breached */
		अगर (rssi < sq_thresh->upper_threshold[0]) अणु
			ath6kl_dbg(ATH6KL_DBG_WMI,
				   "spurious upper rssi threshold event: %d\n",
				   rssi);
		पूर्ण अन्यथा अगर ((rssi < sq_thresh->upper_threshold[1]) &&
			   (rssi >= sq_thresh->upper_threshold[0])) अणु
			new_threshold = WMI_RSSI_THRESHOLD1_ABOVE;
		पूर्ण अन्यथा अगर ((rssi < sq_thresh->upper_threshold[2]) &&
			   (rssi >= sq_thresh->upper_threshold[1])) अणु
			new_threshold = WMI_RSSI_THRESHOLD2_ABOVE;
		पूर्ण अन्यथा अगर ((rssi < sq_thresh->upper_threshold[3]) &&
			   (rssi >= sq_thresh->upper_threshold[2])) अणु
			new_threshold = WMI_RSSI_THRESHOLD3_ABOVE;
		पूर्ण अन्यथा अगर ((rssi < sq_thresh->upper_threshold[4]) &&
			   (rssi >= sq_thresh->upper_threshold[3])) अणु
			new_threshold = WMI_RSSI_THRESHOLD4_ABOVE;
		पूर्ण अन्यथा अगर ((rssi < sq_thresh->upper_threshold[5]) &&
			   (rssi >= sq_thresh->upper_threshold[4])) अणु
			new_threshold = WMI_RSSI_THRESHOLD5_ABOVE;
		पूर्ण अन्यथा अगर (rssi >= sq_thresh->upper_threshold[5]) अणु
			new_threshold = WMI_RSSI_THRESHOLD6_ABOVE;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Lower threshold breached */
		अगर (rssi > sq_thresh->lower_threshold[0]) अणु
			ath6kl_dbg(ATH6KL_DBG_WMI,
				   "spurious lower rssi threshold event: %d %d\n",
				rssi, sq_thresh->lower_threshold[0]);
		पूर्ण अन्यथा अगर ((rssi > sq_thresh->lower_threshold[1]) &&
			   (rssi <= sq_thresh->lower_threshold[0])) अणु
			new_threshold = WMI_RSSI_THRESHOLD6_BELOW;
		पूर्ण अन्यथा अगर ((rssi > sq_thresh->lower_threshold[2]) &&
			   (rssi <= sq_thresh->lower_threshold[1])) अणु
			new_threshold = WMI_RSSI_THRESHOLD5_BELOW;
		पूर्ण अन्यथा अगर ((rssi > sq_thresh->lower_threshold[3]) &&
			   (rssi <= sq_thresh->lower_threshold[2])) अणु
			new_threshold = WMI_RSSI_THRESHOLD4_BELOW;
		पूर्ण अन्यथा अगर ((rssi > sq_thresh->lower_threshold[4]) &&
			   (rssi <= sq_thresh->lower_threshold[3])) अणु
			new_threshold = WMI_RSSI_THRESHOLD3_BELOW;
		पूर्ण अन्यथा अगर ((rssi > sq_thresh->lower_threshold[5]) &&
			   (rssi <= sq_thresh->lower_threshold[4])) अणु
			new_threshold = WMI_RSSI_THRESHOLD2_BELOW;
		पूर्ण अन्यथा अगर (rssi <= sq_thresh->lower_threshold[5]) अणु
			new_threshold = WMI_RSSI_THRESHOLD1_BELOW;
		पूर्ण
	पूर्ण

	/* Calculate and install the next set of thresholds */
	lower_rssi_threshold = ath6kl_wmi_get_lower_threshold(rssi, sq_thresh,
				       sq_thresh->lower_threshold_valid_count);
	upper_rssi_threshold = ath6kl_wmi_get_upper_threshold(rssi, sq_thresh,
				       sq_thresh->upper_threshold_valid_count);

	/* Issue a wmi command to install the thresholds */
	cmd.thresh_above1_val = a_cpu_to_sle16(upper_rssi_threshold);
	cmd.thresh_below1_val = a_cpu_to_sle16(lower_rssi_threshold);
	cmd.weight = sq_thresh->weight;
	cmd.poll_समय = cpu_to_le32(sq_thresh->polling_पूर्णांकerval);

	ret = ath6kl_wmi_send_rssi_threshold_params(wmi, &cmd);
	अगर (ret) अणु
		ath6kl_err("unable to configure rssi thresholds\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_cac_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
				   काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_cac_event *reply;
	काष्ठा ieee80211_tspec_ie *ts;
	u16 active_tsids, tsinfo;
	u8 tsid, index;
	u8 ts_id;

	अगर (len < माप(काष्ठा wmi_cac_event))
		वापस -EINVAL;

	reply = (काष्ठा wmi_cac_event *) datap;
	अगर (reply->ac >= WMM_NUM_AC) अणु
		ath6kl_err("invalid AC: %d\n", reply->ac);
		वापस -EINVAL;
	पूर्ण

	अगर ((reply->cac_indication == CAC_INDICATION_ADMISSION_RESP) &&
	    (reply->status_code != IEEE80211_TSPEC_STATUS_ADMISS_ACCEPTED)) अणु
		ts = (काष्ठा ieee80211_tspec_ie *) &(reply->tspec_suggestion);
		tsinfo = le16_to_cpu(ts->tsinfo);
		tsid = (tsinfo >> IEEE80211_WMM_IE_TSPEC_TID_SHIFT) &
			IEEE80211_WMM_IE_TSPEC_TID_MASK;

		ath6kl_wmi_delete_pstream_cmd(wmi, vअगर->fw_vअगर_idx,
					      reply->ac, tsid);
	पूर्ण अन्यथा अगर (reply->cac_indication == CAC_INDICATION_NO_RESP) अणु
		/*
		 * Following assumes that there is only one outstanding
		 * ADDTS request when this event is received
		 */
		spin_lock_bh(&wmi->lock);
		active_tsids = wmi->stream_exist_क्रम_ac[reply->ac];
		spin_unlock_bh(&wmi->lock);

		क्रम (index = 0; index < माप(active_tsids) * 8; index++) अणु
			अगर ((active_tsids >> index) & 1)
				अवरोध;
		पूर्ण
		अगर (index < (माप(active_tsids) * 8))
			ath6kl_wmi_delete_pstream_cmd(wmi, vअगर->fw_vअगर_idx,
						      reply->ac, index);
	पूर्ण

	/*
	 * Clear active tsids and Add missing handling
	 * क्रम delete qos stream from AP
	 */
	अन्यथा अगर (reply->cac_indication == CAC_INDICATION_DELETE) अणु
		ts = (काष्ठा ieee80211_tspec_ie *) &(reply->tspec_suggestion);
		tsinfo = le16_to_cpu(ts->tsinfo);
		ts_id = ((tsinfo >> IEEE80211_WMM_IE_TSPEC_TID_SHIFT) &
			 IEEE80211_WMM_IE_TSPEC_TID_MASK);

		spin_lock_bh(&wmi->lock);
		wmi->stream_exist_क्रम_ac[reply->ac] &= ~(1 << ts_id);
		active_tsids = wmi->stream_exist_क्रम_ac[reply->ac];
		spin_unlock_bh(&wmi->lock);

		/* Indicate stream inactivity to driver layer only अगर all tsids
		 * within this AC are deleted.
		 */
		अगर (!active_tsids) अणु
			ath6kl_indicate_tx_activity(wmi->parent_dev, reply->ac,
						    false);
			wmi->fat_pipe_exist &= ~(1 << reply->ac);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_txe_notअगरy_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
					  काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_txe_notअगरy_event *ev;
	u32 rate, pkts;

	अगर (len < माप(*ev))
		वापस -EINVAL;

	अगर (vअगर->nw_type != INFRA_NETWORK ||
	    !test_bit(ATH6KL_FW_CAPABILITY_TX_ERR_NOTIFY,
		      vअगर->ar->fw_capabilities))
		वापस -EOPNOTSUPP;

	अगर (vअगर->sme_state != SME_CONNECTED)
		वापस -ENOTCONN;

	ev = (काष्ठा wmi_txe_notअगरy_event *) datap;
	rate = le32_to_cpu(ev->rate);
	pkts = le32_to_cpu(ev->pkts);

	ath6kl_dbg(ATH6KL_DBG_WMI, "TXE notify event: peer %pM rate %d%% pkts %d intvl %ds\n",
		   vअगर->bssid, rate, pkts, vअगर->txe_पूर्णांकvl);

	cfg80211_cqm_txe_notअगरy(vअगर->ndev, vअगर->bssid, pkts,
				rate, vअगर->txe_पूर्णांकvl, GFP_KERNEL);

	वापस 0;
पूर्ण

पूर्णांक ath6kl_wmi_set_txe_notअगरy(काष्ठा wmi *wmi, u8 idx,
			      u32 rate, u32 pkts, u32 पूर्णांकvl)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_txe_notअगरy_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_txe_notअगरy_cmd *) skb->data;
	cmd->rate = cpu_to_le32(rate);
	cmd->pkts = cpu_to_le32(pkts);
	cmd->पूर्णांकvl = cpu_to_le32(पूर्णांकvl);

	वापस ath6kl_wmi_cmd_send(wmi, idx, skb, WMI_SET_TXE_NOTIFY_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_set_rssi_filter_cmd(काष्ठा wmi *wmi, u8 अगर_idx, s8 rssi)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_set_rssi_filter_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_set_rssi_filter_cmd *) skb->data;
	cmd->rssi = rssi;

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_RSSI_FILTER_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_wmi_send_snr_threshold_params(काष्ठा wmi *wmi,
			काष्ठा wmi_snr_threshold_params_cmd *snr_cmd)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_snr_threshold_params_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_snr_threshold_params_cmd *) skb->data;
	स_नकल(cmd, snr_cmd, माप(काष्ठा wmi_snr_threshold_params_cmd));

	वापस ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_SNR_THRESHOLD_PARAMS_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

अटल पूर्णांक ath6kl_wmi_snr_threshold_event_rx(काष्ठा wmi *wmi, u8 *datap,
					     पूर्णांक len)
अणु
	काष्ठा wmi_snr_threshold_event *reply;
	काष्ठा sq_threshold_params *sq_thresh;
	काष्ठा wmi_snr_threshold_params_cmd cmd;
	क्रमागत wmi_snr_threshold_val new_threshold;
	u8 upper_snr_threshold, lower_snr_threshold;
	s16 snr;
	पूर्णांक ret;

	अगर (len < माप(काष्ठा wmi_snr_threshold_event))
		वापस -EINVAL;

	reply = (काष्ठा wmi_snr_threshold_event *) datap;

	new_threshold = (क्रमागत wmi_snr_threshold_val) reply->range;
	snr = reply->snr;

	sq_thresh = &wmi->sq_threshld[SIGNAL_QUALITY_METRICS_SNR];

	/*
	 * Identअगरy the threshold breached and communicate that to the app.
	 * After that install a new set of thresholds based on the संकेत
	 * quality reported by the target.
	 */
	अगर (new_threshold) अणु
		/* Upper threshold breached */
		अगर (snr < sq_thresh->upper_threshold[0]) अणु
			ath6kl_dbg(ATH6KL_DBG_WMI,
				   "spurious upper snr threshold event: %d\n",
				   snr);
		पूर्ण अन्यथा अगर ((snr < sq_thresh->upper_threshold[1]) &&
			   (snr >= sq_thresh->upper_threshold[0])) अणु
			new_threshold = WMI_SNR_THRESHOLD1_ABOVE;
		पूर्ण अन्यथा अगर ((snr < sq_thresh->upper_threshold[2]) &&
			   (snr >= sq_thresh->upper_threshold[1])) अणु
			new_threshold = WMI_SNR_THRESHOLD2_ABOVE;
		पूर्ण अन्यथा अगर ((snr < sq_thresh->upper_threshold[3]) &&
			   (snr >= sq_thresh->upper_threshold[2])) अणु
			new_threshold = WMI_SNR_THRESHOLD3_ABOVE;
		पूर्ण अन्यथा अगर (snr >= sq_thresh->upper_threshold[3]) अणु
			new_threshold = WMI_SNR_THRESHOLD4_ABOVE;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Lower threshold breached */
		अगर (snr > sq_thresh->lower_threshold[0]) अणु
			ath6kl_dbg(ATH6KL_DBG_WMI,
				   "spurious lower snr threshold event: %d\n",
				   sq_thresh->lower_threshold[0]);
		पूर्ण अन्यथा अगर ((snr > sq_thresh->lower_threshold[1]) &&
			   (snr <= sq_thresh->lower_threshold[0])) अणु
			new_threshold = WMI_SNR_THRESHOLD4_BELOW;
		पूर्ण अन्यथा अगर ((snr > sq_thresh->lower_threshold[2]) &&
			   (snr <= sq_thresh->lower_threshold[1])) अणु
			new_threshold = WMI_SNR_THRESHOLD3_BELOW;
		पूर्ण अन्यथा अगर ((snr > sq_thresh->lower_threshold[3]) &&
			   (snr <= sq_thresh->lower_threshold[2])) अणु
			new_threshold = WMI_SNR_THRESHOLD2_BELOW;
		पूर्ण अन्यथा अगर (snr <= sq_thresh->lower_threshold[3]) अणु
			new_threshold = WMI_SNR_THRESHOLD1_BELOW;
		पूर्ण
	पूर्ण

	/* Calculate and install the next set of thresholds */
	lower_snr_threshold = ath6kl_wmi_get_lower_threshold(snr, sq_thresh,
				       sq_thresh->lower_threshold_valid_count);
	upper_snr_threshold = ath6kl_wmi_get_upper_threshold(snr, sq_thresh,
				       sq_thresh->upper_threshold_valid_count);

	/* Issue a wmi command to install the thresholds */
	cmd.thresh_above1_val = upper_snr_threshold;
	cmd.thresh_below1_val = lower_snr_threshold;
	cmd.weight = sq_thresh->weight;
	cmd.poll_समय = cpu_to_le32(sq_thresh->polling_पूर्णांकerval);

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "snr: %d, threshold: %d, lower: %d, upper: %d\n",
		   snr, new_threshold,
		   lower_snr_threshold, upper_snr_threshold);

	ret = ath6kl_wmi_send_snr_threshold_params(wmi, &cmd);
	अगर (ret) अणु
		ath6kl_err("unable to configure snr threshold\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_aplist_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len)
अणु
	u16 ap_info_entry_size;
	काष्ठा wmi_aplist_event *ev = (काष्ठा wmi_aplist_event *) datap;
	काष्ठा wmi_ap_info_v1 *ap_info_v1;
	u8 index;

	अगर (len < माप(काष्ठा wmi_aplist_event) ||
	    ev->ap_list_ver != APLIST_VER1)
		वापस -EINVAL;

	ap_info_entry_size = माप(काष्ठा wmi_ap_info_v1);
	ap_info_v1 = (काष्ठा wmi_ap_info_v1 *) ev->ap_list;

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "number of APs in aplist event: %d\n", ev->num_ap);

	अगर (len < (पूर्णांक) (माप(काष्ठा wmi_aplist_event) +
			 (ev->num_ap - 1) * ap_info_entry_size))
		वापस -EINVAL;

	/* AP list version 1 contents */
	क्रम (index = 0; index < ev->num_ap; index++) अणु
		ath6kl_dbg(ATH6KL_DBG_WMI, "AP#%d BSSID %pM Channel %d\n",
			   index, ap_info_v1->bssid, ap_info_v1->channel);
		ap_info_v1++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath6kl_wmi_cmd_send(काष्ठा wmi *wmi, u8 अगर_idx, काष्ठा sk_buff *skb,
			क्रमागत wmi_cmd_id cmd_id, क्रमागत wmi_sync_flag sync_flag)
अणु
	काष्ठा wmi_cmd_hdr *cmd_hdr;
	क्रमागत htc_endpoपूर्णांक_id ep_id = wmi->ep_id;
	पूर्णांक ret;
	u16 info1;

	अगर (WARN_ON(skb == शून्य ||
		    (अगर_idx > (wmi->parent_dev->vअगर_max - 1)))) अणु
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_WMI, "wmi tx id %d len %d flag %d\n",
		   cmd_id, skb->len, sync_flag);
	ath6kl_dbg_dump(ATH6KL_DBG_WMI_DUMP, शून्य, "wmi tx ",
			skb->data, skb->len);

	अगर (sync_flag >= END_WMIFLAG) अणु
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	अगर ((sync_flag == SYNC_BEFORE_WMIFLAG) ||
	    (sync_flag == SYNC_BOTH_WMIFLAG)) अणु
		/*
		 * Make sure all data currently queued is transmitted beक्रमe
		 * the cmd execution.  Establish a new sync poपूर्णांक.
		 */
		ath6kl_wmi_sync_poपूर्णांक(wmi, अगर_idx);
	पूर्ण

	skb_push(skb, माप(काष्ठा wmi_cmd_hdr));

	cmd_hdr = (काष्ठा wmi_cmd_hdr *) skb->data;
	cmd_hdr->cmd_id = cpu_to_le16(cmd_id);
	info1 = अगर_idx & WMI_CMD_HDR_IF_ID_MASK;
	cmd_hdr->info1 = cpu_to_le16(info1);

	/* Only क्रम OPT_TX_CMD, use BE endpoपूर्णांक. */
	अगर (cmd_id == WMI_OPT_TX_FRAME_CMDID) अणु
		ret = ath6kl_wmi_data_hdr_add(wmi, skb, OPT_MSGTYPE, false,
				WMI_DATA_HDR_DATA_TYPE_802_3, 0, शून्य, अगर_idx);
		अगर (ret) अणु
			dev_kमुक्त_skb(skb);
			वापस ret;
		पूर्ण
		ep_id = ath6kl_ac2_endpoपूर्णांक_id(wmi->parent_dev, WMM_AC_BE);
	पूर्ण

	ath6kl_control_tx(wmi->parent_dev, skb, ep_id);

	अगर ((sync_flag == SYNC_AFTER_WMIFLAG) ||
	    (sync_flag == SYNC_BOTH_WMIFLAG)) अणु
		/*
		 * Make sure all new data queued रुकोs क्रम the command to
		 * execute. Establish a new sync poपूर्णांक.
		 */
		ath6kl_wmi_sync_poपूर्णांक(wmi, अगर_idx);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath6kl_wmi_connect_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
			   क्रमागत network_type nw_type,
			   क्रमागत करोt11_auth_mode करोt11_auth_mode,
			   क्रमागत auth_mode auth_mode,
			   क्रमागत ath6kl_crypto_type pairwise_crypto,
			   u8 pairwise_crypto_len,
			   क्रमागत ath6kl_crypto_type group_crypto,
			   u8 group_crypto_len, पूर्णांक ssid_len, u8 *ssid,
			   u8 *bssid, u16 channel, u32 ctrl_flags,
			   u8 nw_subtype)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_connect_cmd *cc;
	पूर्णांक ret;

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "wmi connect bssid %pM freq %d flags 0x%x ssid_len %d "
		   "type %d dot11_auth %d auth %d pairwise %d group %d\n",
		   bssid, channel, ctrl_flags, ssid_len, nw_type,
		   करोt11_auth_mode, auth_mode, pairwise_crypto, group_crypto);
	ath6kl_dbg_dump(ATH6KL_DBG_WMI, शून्य, "ssid ", ssid, ssid_len);

	wmi->traffic_class = 100;

	अगर ((pairwise_crypto == NONE_CRYPT) && (group_crypto != NONE_CRYPT))
		वापस -EINVAL;

	अगर ((pairwise_crypto != NONE_CRYPT) && (group_crypto == NONE_CRYPT))
		वापस -EINVAL;

	skb = ath6kl_wmi_get_new_buf(माप(काष्ठा wmi_connect_cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cc = (काष्ठा wmi_connect_cmd *) skb->data;

	अगर (ssid_len)
		स_नकल(cc->ssid, ssid, ssid_len);

	cc->ssid_len = ssid_len;
	cc->nw_type = nw_type;
	cc->करोt11_auth_mode = करोt11_auth_mode;
	cc->auth_mode = auth_mode;
	cc->prwise_crypto_type = pairwise_crypto;
	cc->prwise_crypto_len = pairwise_crypto_len;
	cc->grp_crypto_type = group_crypto;
	cc->grp_crypto_len = group_crypto_len;
	cc->ch = cpu_to_le16(channel);
	cc->ctrl_flags = cpu_to_le32(ctrl_flags);
	cc->nw_subtype = nw_subtype;

	अगर (bssid != शून्य)
		स_नकल(cc->bssid, bssid, ETH_ALEN);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_CONNECT_CMDID,
				  NO_SYNC_WMIFLAG);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_reconnect_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 *bssid,
			     u16 channel)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_reconnect_cmd *cc;
	पूर्णांक ret;

	ath6kl_dbg(ATH6KL_DBG_WMI, "wmi reconnect bssid %pM freq %d\n",
		   bssid, channel);

	wmi->traffic_class = 100;

	skb = ath6kl_wmi_get_new_buf(माप(काष्ठा wmi_reconnect_cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cc = (काष्ठा wmi_reconnect_cmd *) skb->data;
	cc->channel = cpu_to_le16(channel);

	अगर (bssid != शून्य)
		स_नकल(cc->bssid, bssid, ETH_ALEN);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_RECONNECT_CMDID,
				  NO_SYNC_WMIFLAG);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_disconnect_cmd(काष्ठा wmi *wmi, u8 अगर_idx)
अणु
	पूर्णांक ret;

	ath6kl_dbg(ATH6KL_DBG_WMI, "wmi disconnect\n");

	wmi->traffic_class = 100;

	/* Disconnect command करोes not need to करो a SYNC beक्रमe. */
	ret = ath6kl_wmi_simple_cmd(wmi, अगर_idx, WMI_DISCONNECT_CMDID);

	वापस ret;
पूर्ण

/* ath6kl_wmi_start_scan_cmd is to be deprecated. Use
 * ath6kl_wmi_begin_scan_cmd instead. The new function supports P2P
 * mgmt operations using station पूर्णांकerface.
 */
अटल पूर्णांक ath6kl_wmi_startscan_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				    क्रमागत wmi_scan_type scan_type,
				    u32 क्रमce_fgscan, u32 is_legacy,
				    u32 home_dwell_समय,
				    u32 क्रमce_scan_पूर्णांकerval,
				    s8 num_chan, u16 *ch_list)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_start_scan_cmd *sc;
	s8 size;
	पूर्णांक i, ret;

	size = माप(काष्ठा wmi_start_scan_cmd);

	अगर ((scan_type != WMI_LONG_SCAN) && (scan_type != WMI_SHORT_SCAN))
		वापस -EINVAL;

	अगर (num_chan > WMI_MAX_CHANNELS)
		वापस -EINVAL;

	अगर (num_chan)
		size += माप(u16) * (num_chan - 1);

	skb = ath6kl_wmi_get_new_buf(size);
	अगर (!skb)
		वापस -ENOMEM;

	sc = (काष्ठा wmi_start_scan_cmd *) skb->data;
	sc->scan_type = scan_type;
	sc->क्रमce_fg_scan = cpu_to_le32(क्रमce_fgscan);
	sc->is_legacy = cpu_to_le32(is_legacy);
	sc->home_dwell_समय = cpu_to_le32(home_dwell_समय);
	sc->क्रमce_scan_पूर्णांकvl = cpu_to_le32(क्रमce_scan_पूर्णांकerval);
	sc->num_ch = num_chan;

	क्रम (i = 0; i < num_chan; i++)
		sc->ch_list[i] = cpu_to_le16(ch_list[i]);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_START_SCAN_CMDID,
				  NO_SYNC_WMIFLAG);

	वापस ret;
पूर्ण

/*
 * beginscan supports (compared to old startscan) P2P mgmt operations using
 * station पूर्णांकerface, send additional inक्रमmation like supported rates to
 * advertise and xmit rates क्रम probe requests
 */
पूर्णांक ath6kl_wmi_beginscan_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
			     क्रमागत wmi_scan_type scan_type,
			     u32 क्रमce_fgscan, u32 is_legacy,
			     u32 home_dwell_समय, u32 क्रमce_scan_पूर्णांकerval,
			     s8 num_chan, u16 *ch_list, u32 no_cck, u32 *rates)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा sk_buff *skb;
	काष्ठा wmi_begin_scan_cmd *sc;
	s8 size, *supp_rates;
	पूर्णांक i, band, ret;
	काष्ठा ath6kl *ar = wmi->parent_dev;
	पूर्णांक num_rates;
	u32 ratemask;

	अगर (!test_bit(ATH6KL_FW_CAPABILITY_STA_P2PDEV_DUPLEX,
		      ar->fw_capabilities)) अणु
		वापस ath6kl_wmi_startscan_cmd(wmi, अगर_idx,
						scan_type, क्रमce_fgscan,
						is_legacy, home_dwell_समय,
						क्रमce_scan_पूर्णांकerval,
						num_chan, ch_list);
	पूर्ण

	size = माप(काष्ठा wmi_begin_scan_cmd);

	अगर ((scan_type != WMI_LONG_SCAN) && (scan_type != WMI_SHORT_SCAN))
		वापस -EINVAL;

	अगर (num_chan > WMI_MAX_CHANNELS)
		वापस -EINVAL;

	अगर (num_chan)
		size += माप(u16) * (num_chan - 1);

	skb = ath6kl_wmi_get_new_buf(size);
	अगर (!skb)
		वापस -ENOMEM;

	sc = (काष्ठा wmi_begin_scan_cmd *) skb->data;
	sc->scan_type = scan_type;
	sc->क्रमce_fg_scan = cpu_to_le32(क्रमce_fgscan);
	sc->is_legacy = cpu_to_le32(is_legacy);
	sc->home_dwell_समय = cpu_to_le32(home_dwell_समय);
	sc->क्रमce_scan_पूर्णांकvl = cpu_to_le32(क्रमce_scan_पूर्णांकerval);
	sc->no_cck = cpu_to_le32(no_cck);
	sc->num_ch = num_chan;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		sband = ar->wiphy->bands[band];

		अगर (!sband)
			जारी;

		अगर (WARN_ON(band >= ATH6KL_NUM_BANDS))
			अवरोध;

		ratemask = rates[band];
		supp_rates = sc->supp_rates[band].rates;
		num_rates = 0;

		क्रम (i = 0; i < sband->n_bitrates; i++) अणु
			अगर ((BIT(i) & ratemask) == 0)
				जारी; /* skip rate */
			supp_rates[num_rates++] =
			    (u8) (sband->bitrates[i].bitrate / 5);
		पूर्ण
		sc->supp_rates[band].nrates = num_rates;
	पूर्ण

	क्रम (i = 0; i < num_chan; i++)
		sc->ch_list[i] = cpu_to_le16(ch_list[i]);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_BEGIN_SCAN_CMDID,
				  NO_SYNC_WMIFLAG);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_enable_sched_scan_cmd(काष्ठा wmi *wmi, u8 अगर_idx, bool enable)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_enable_sched_scan_cmd *sc;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*sc));
	अगर (!skb)
		वापस -ENOMEM;

	ath6kl_dbg(ATH6KL_DBG_WMI, "%s scheduled scan on vif %d\n",
		   enable ? "enabling" : "disabling", अगर_idx);
	sc = (काष्ठा wmi_enable_sched_scan_cmd *) skb->data;
	sc->enable = enable ? 1 : 0;

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb,
				  WMI_ENABLE_SCHED_SCAN_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_scanparams_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
			      u16 fg_start_sec,
			      u16 fg_end_sec, u16 bg_sec,
			      u16 minact_chdw_msec, u16 maxact_chdw_msec,
			      u16 pas_chdw_msec, u8 लघु_scan_ratio,
			      u8 scan_ctrl_flag, u32 max_dfsch_act_समय,
			      u16 maxact_scan_per_ssid)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_scan_params_cmd *sc;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*sc));
	अगर (!skb)
		वापस -ENOMEM;

	sc = (काष्ठा wmi_scan_params_cmd *) skb->data;
	sc->fg_start_period = cpu_to_le16(fg_start_sec);
	sc->fg_end_period = cpu_to_le16(fg_end_sec);
	sc->bg_period = cpu_to_le16(bg_sec);
	sc->minact_chdwell_समय = cpu_to_le16(minact_chdw_msec);
	sc->maxact_chdwell_समय = cpu_to_le16(maxact_chdw_msec);
	sc->pas_chdwell_समय = cpu_to_le16(pas_chdw_msec);
	sc->लघु_scan_ratio = लघु_scan_ratio;
	sc->scan_ctrl_flags = scan_ctrl_flag;
	sc->max_dfsch_act_समय = cpu_to_le32(max_dfsch_act_समय);
	sc->maxact_scan_per_ssid = cpu_to_le16(maxact_scan_per_ssid);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_SCAN_PARAMS_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_bssfilter_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 filter, u32 ie_mask)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_bss_filter_cmd *cmd;
	पूर्णांक ret;

	अगर (filter >= LAST_BSS_FILTER)
		वापस -EINVAL;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_bss_filter_cmd *) skb->data;
	cmd->bss_filter = filter;
	cmd->ie_mask = cpu_to_le32(ie_mask);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_BSS_FILTER_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_probedssid_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 index, u8 flag,
			      u8 ssid_len, u8 *ssid)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_probed_ssid_cmd *cmd;
	पूर्णांक ret;

	अगर (index >= MAX_PROBED_SSIDS)
		वापस -EINVAL;

	अगर (ssid_len > माप(cmd->ssid))
		वापस -EINVAL;

	अगर ((flag & (DISABLE_SSID_FLAG | ANY_SSID_FLAG)) && (ssid_len > 0))
		वापस -EINVAL;

	अगर ((flag & SPECIFIC_SSID_FLAG) && !ssid_len)
		वापस -EINVAL;

	अगर (flag & SPECIFIC_SSID_FLAG)
		wmi->is_probe_ssid = true;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_probed_ssid_cmd *) skb->data;
	cmd->entry_index = index;
	cmd->flag = flag;
	cmd->ssid_len = ssid_len;
	स_नकल(cmd->ssid, ssid, ssid_len);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_PROBED_SSID_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_listenपूर्णांकerval_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				  u16 listen_पूर्णांकerval,
				  u16 listen_beacons)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_listen_पूर्णांक_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_listen_पूर्णांक_cmd *) skb->data;
	cmd->listen_पूर्णांकvl = cpu_to_le16(listen_पूर्णांकerval);
	cmd->num_beacons = cpu_to_le16(listen_beacons);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_LISTEN_INT_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_bmissसमय_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
			     u16 bmiss_समय, u16 num_beacons)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_bmiss_समय_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_bmiss_समय_cmd *) skb->data;
	cmd->bmiss_समय = cpu_to_le16(bmiss_समय);
	cmd->num_beacons = cpu_to_le16(num_beacons);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_BMISS_TIME_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_घातermode_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 pwr_mode)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_घातer_mode_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_घातer_mode_cmd *) skb->data;
	cmd->pwr_mode = pwr_mode;
	wmi->pwr_mode = pwr_mode;

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_POWER_MODE_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_pmparams_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u16 idle_period,
			    u16 ps_poll_num, u16 dtim_policy,
			    u16 tx_wakeup_policy, u16 num_tx_to_wakeup,
			    u16 ps_fail_event_policy)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_घातer_params_cmd *pm;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*pm));
	अगर (!skb)
		वापस -ENOMEM;

	pm = (काष्ठा wmi_घातer_params_cmd *)skb->data;
	pm->idle_period = cpu_to_le16(idle_period);
	pm->pspoll_number = cpu_to_le16(ps_poll_num);
	pm->dtim_policy = cpu_to_le16(dtim_policy);
	pm->tx_wakeup_policy = cpu_to_le16(tx_wakeup_policy);
	pm->num_tx_to_wakeup = cpu_to_le16(num_tx_to_wakeup);
	pm->ps_fail_event_policy = cpu_to_le16(ps_fail_event_policy);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_POWER_PARAMS_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_disस_समयout_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 समयout)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_disc_समयout_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_disc_समयout_cmd *) skb->data;
	cmd->discon_समयout = समयout;

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_DISC_TIMEOUT_CMDID,
				  NO_SYNC_WMIFLAG);

	अगर (ret == 0)
		ath6kl_debug_set_disconnect_समयout(wmi->parent_dev, समयout);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_addkey_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 key_index,
			  क्रमागत ath6kl_crypto_type key_type,
			  u8 key_usage, u8 key_len,
			  u8 *key_rsc, अचिन्हित पूर्णांक key_rsc_len,
			  u8 *key_material,
			  u8 key_op_ctrl, u8 *mac_addr,
			  क्रमागत wmi_sync_flag sync_flag)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_add_cipher_key_cmd *cmd;
	पूर्णांक ret;

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "addkey cmd: key_index=%u key_type=%d key_usage=%d key_len=%d key_op_ctrl=%d\n",
		   key_index, key_type, key_usage, key_len, key_op_ctrl);

	अगर ((key_index > WMI_MAX_KEY_INDEX) || (key_len > WMI_MAX_KEY_LEN) ||
	    (key_material == शून्य) || key_rsc_len > 8)
		वापस -EINVAL;

	अगर ((WEP_CRYPT != key_type) && (शून्य == key_rsc))
		वापस -EINVAL;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_add_cipher_key_cmd *) skb->data;
	cmd->key_index = key_index;
	cmd->key_type = key_type;
	cmd->key_usage = key_usage;
	cmd->key_len = key_len;
	स_नकल(cmd->key, key_material, key_len);

	अगर (key_rsc != शून्य)
		स_नकल(cmd->key_rsc, key_rsc, key_rsc_len);

	cmd->key_op_ctrl = key_op_ctrl;

	अगर (mac_addr)
		स_नकल(cmd->key_mac_addr, mac_addr, ETH_ALEN);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_ADD_CIPHER_KEY_CMDID,
				  sync_flag);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_add_krk_cmd(काष्ठा wmi *wmi, u8 अगर_idx, स्थिर u8 *krk)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_add_krk_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_add_krk_cmd *) skb->data;
	स_नकल(cmd->krk, krk, WMI_KRK_LEN);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_ADD_KRK_CMDID,
				  NO_SYNC_WMIFLAG);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_deletekey_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 key_index)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_delete_cipher_key_cmd *cmd;
	पूर्णांक ret;

	अगर (key_index > WMI_MAX_KEY_INDEX)
		वापस -EINVAL;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_delete_cipher_key_cmd *) skb->data;
	cmd->key_index = key_index;

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_DELETE_CIPHER_KEY_CMDID,
				  NO_SYNC_WMIFLAG);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_setpmkid_cmd(काष्ठा wmi *wmi, u8 अगर_idx, स्थिर u8 *bssid,
			    स्थिर u8 *pmkid, bool set)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_setpmkid_cmd *cmd;
	पूर्णांक ret;

	अगर (bssid == शून्य)
		वापस -EINVAL;

	अगर (set && pmkid == शून्य)
		वापस -EINVAL;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_setpmkid_cmd *) skb->data;
	स_नकल(cmd->bssid, bssid, ETH_ALEN);
	अगर (set) अणु
		स_नकल(cmd->pmkid, pmkid, माप(cmd->pmkid));
		cmd->enable = PMKID_ENABLE;
	पूर्ण अन्यथा अणु
		स_रखो(cmd->pmkid, 0, माप(cmd->pmkid));
		cmd->enable = PMKID_DISABLE;
	पूर्ण

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_PMKID_CMDID,
				  NO_SYNC_WMIFLAG);

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_wmi_data_sync_send(काष्ठा wmi *wmi, काष्ठा sk_buff *skb,
			      क्रमागत htc_endpoपूर्णांक_id ep_id, u8 अगर_idx)
अणु
	काष्ठा wmi_data_hdr *data_hdr;
	पूर्णांक ret;

	अगर (WARN_ON(skb == शून्य || ep_id == wmi->ep_id)) अणु
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	skb_push(skb, माप(काष्ठा wmi_data_hdr));

	data_hdr = (काष्ठा wmi_data_hdr *) skb->data;
	data_hdr->info = SYNC_MSGTYPE << WMI_DATA_HDR_MSG_TYPE_SHIFT;
	data_hdr->info3 = cpu_to_le16(अगर_idx & WMI_DATA_HDR_IF_IDX_MASK);

	ret = ath6kl_control_tx(wmi->parent_dev, skb, ep_id);

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_wmi_sync_poपूर्णांक(काष्ठा wmi *wmi, u8 अगर_idx)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_sync_cmd *cmd;
	काष्ठा wmi_data_sync_bufs data_sync_bufs[WMM_NUM_AC];
	क्रमागत htc_endpoपूर्णांक_id ep_id;
	u8 index, num_pri_streams = 0;
	पूर्णांक ret = 0;

	स_रखो(data_sync_bufs, 0, माप(data_sync_bufs));

	spin_lock_bh(&wmi->lock);

	क्रम (index = 0; index < WMM_NUM_AC; index++) अणु
		अगर (wmi->fat_pipe_exist & (1 << index)) अणु
			num_pri_streams++;
			data_sync_bufs[num_pri_streams - 1].traffic_class =
			    index;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&wmi->lock);

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_sync_cmd *) skb->data;

	/*
	 * In the SYNC cmd sent on the control Ep, send a biपंचांगap
	 * of the data eps on which the Data Sync will be sent
	 */
	cmd->data_sync_map = wmi->fat_pipe_exist;

	क्रम (index = 0; index < num_pri_streams; index++) अणु
		data_sync_bufs[index].skb = ath6kl_buf_alloc(0);
		अगर (data_sync_bufs[index].skb == शून्य) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If buffer allocation क्रम any of the dataSync fails,
	 * then करो not send the Synchronize cmd on the control ep
	 */
	अगर (ret)
		जाओ मुक्त_cmd_skb;

	/*
	 * Send sync cmd followed by sync data messages on all
	 * endpoपूर्णांकs being used
	 */
	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SYNCHRONIZE_CMDID,
				  NO_SYNC_WMIFLAG);

	अगर (ret)
		जाओ मुक्त_data_skb;

	क्रम (index = 0; index < num_pri_streams; index++) अणु
		अगर (WARN_ON(!data_sync_bufs[index].skb))
			जाओ मुक्त_data_skb;

		ep_id = ath6kl_ac2_endpoपूर्णांक_id(wmi->parent_dev,
					       data_sync_bufs[index].
					       traffic_class);
		ret =
		    ath6kl_wmi_data_sync_send(wmi, data_sync_bufs[index].skb,
					      ep_id, अगर_idx);

		data_sync_bufs[index].skb = शून्य;

		अगर (ret)
			जाओ मुक्त_data_skb;
	पूर्ण

	वापस 0;

मुक्त_cmd_skb:
	/* मुक्त up any resources left over (possibly due to an error) */
	dev_kमुक्त_skb(skb);

मुक्त_data_skb:
	क्रम (index = 0; index < num_pri_streams; index++)
		dev_kमुक्त_skb((काष्ठा sk_buff *)data_sync_bufs[index].skb);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_create_pstream_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				  काष्ठा wmi_create_pstream_cmd *params)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_create_pstream_cmd *cmd;
	u8 fatpipe_exist_क्रम_ac = 0;
	s32 min_phy = 0;
	s32 nominal_phy = 0;
	पूर्णांक ret;

	अगर (!((params->user_pri <= 0x7) &&
	      (up_to_ac[params->user_pri & 0x7] == params->traffic_class) &&
	      (params->traffic_direc == UPLINK_TRAFFIC ||
	       params->traffic_direc == DNLINK_TRAFFIC ||
	       params->traffic_direc == BIसूची_TRAFFIC) &&
	      (params->traffic_type == TRAFFIC_TYPE_APERIODIC ||
	       params->traffic_type == TRAFFIC_TYPE_PERIODIC) &&
	      (params->voice_psc_cap == DISABLE_FOR_THIS_AC ||
	       params->voice_psc_cap == ENABLE_FOR_THIS_AC ||
	       params->voice_psc_cap == ENABLE_FOR_ALL_AC) &&
	      (params->tsid == WMI_IMPLICIT_PSTREAM ||
	       params->tsid <= WMI_MAX_THINSTREAM))) अणु
		वापस -EINVAL;
	पूर्ण

	/*
	 * Check nominal PHY rate is >= minimalPHY,
	 * so that DUT can allow TSRS IE
	 */

	/* Get the physical rate (units of bps) */
	min_phy = ((le32_to_cpu(params->min_phy_rate) / 1000) / 1000);

	/* Check minimal phy < nominal phy rate */
	अगर (params->nominal_phy >= min_phy) अणु
		/* unit of 500 kbps */
		nominal_phy = (params->nominal_phy * 1000) / 500;
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "TSRS IE enabled::MinPhy %x->NominalPhy ===> %x\n",
			   min_phy, nominal_phy);

		params->nominal_phy = nominal_phy;
	पूर्ण अन्यथा अणु
		params->nominal_phy = 0;
	पूर्ण

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "sending create_pstream_cmd: ac=%d  tsid:%d\n",
		   params->traffic_class, params->tsid);

	cmd = (काष्ठा wmi_create_pstream_cmd *) skb->data;
	स_नकल(cmd, params, माप(*cmd));

	/* This is an implicitly created Fat pipe */
	अगर ((u32) params->tsid == (u32) WMI_IMPLICIT_PSTREAM) अणु
		spin_lock_bh(&wmi->lock);
		fatpipe_exist_क्रम_ac = (wmi->fat_pipe_exist &
					(1 << params->traffic_class));
		wmi->fat_pipe_exist |= (1 << params->traffic_class);
		spin_unlock_bh(&wmi->lock);
	पूर्ण अन्यथा अणु
		/* explicitly created thin stream within a fat pipe */
		spin_lock_bh(&wmi->lock);
		fatpipe_exist_क्रम_ac = (wmi->fat_pipe_exist &
					(1 << params->traffic_class));
		wmi->stream_exist_क्रम_ac[params->traffic_class] |=
		    (1 << params->tsid);
		/*
		 * If a thinstream becomes active, the fat pipe स्वतःmatically
		 * becomes active
		 */
		wmi->fat_pipe_exist |= (1 << params->traffic_class);
		spin_unlock_bh(&wmi->lock);
	पूर्ण

	/*
	 * Indicate activty change to driver layer only अगर this is the
	 * first TSID to get created in this AC explicitly or an implicit
	 * fat pipe is getting created.
	 */
	अगर (!fatpipe_exist_क्रम_ac)
		ath6kl_indicate_tx_activity(wmi->parent_dev,
					    params->traffic_class, true);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_CREATE_PSTREAM_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_delete_pstream_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 traffic_class,
				  u8 tsid)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_delete_pstream_cmd *cmd;
	u16 active_tsids = 0;
	पूर्णांक ret;

	अगर (traffic_class >= WMM_NUM_AC) अणु
		ath6kl_err("invalid traffic class: %d\n", traffic_class);
		वापस -EINVAL;
	पूर्ण

	अगर (tsid >= 16) अणु
		ath6kl_err("invalid tsid: %d\n", tsid);
		वापस -EINVAL;
	पूर्ण

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_delete_pstream_cmd *) skb->data;
	cmd->traffic_class = traffic_class;
	cmd->tsid = tsid;

	spin_lock_bh(&wmi->lock);
	active_tsids = wmi->stream_exist_क्रम_ac[traffic_class];
	spin_unlock_bh(&wmi->lock);

	अगर (!(active_tsids & (1 << tsid))) अणु
		dev_kमुक्त_skb(skb);
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "TSID %d doesn't exist for traffic class: %d\n",
			   tsid, traffic_class);
		वापस -ENODATA;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "sending delete_pstream_cmd: traffic class: %d tsid=%d\n",
		   traffic_class, tsid);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_DELETE_PSTREAM_CMDID,
				  SYNC_BEFORE_WMIFLAG);

	spin_lock_bh(&wmi->lock);
	wmi->stream_exist_क्रम_ac[traffic_class] &= ~(1 << tsid);
	active_tsids = wmi->stream_exist_क्रम_ac[traffic_class];
	spin_unlock_bh(&wmi->lock);

	/*
	 * Indicate stream inactivity to driver layer only अगर all tsids
	 * within this AC are deleted.
	 */
	अगर (!active_tsids) अणु
		ath6kl_indicate_tx_activity(wmi->parent_dev,
					    traffic_class, false);
		wmi->fat_pipe_exist &= ~(1 << traffic_class);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_set_ip_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
			  __be32 ips0, __be32 ips1)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_set_ip_cmd *cmd;
	पूर्णांक ret;

	/* Multicast address are not valid */
	अगर (ipv4_is_multicast(ips0) ||
	    ipv4_is_multicast(ips1))
		वापस -EINVAL;

	skb = ath6kl_wmi_get_new_buf(माप(काष्ठा wmi_set_ip_cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_set_ip_cmd *) skb->data;
	cmd->ips[0] = ips0;
	cmd->ips[1] = ips1;

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_IP_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

अटल व्योम ath6kl_wmi_relinquish_implicit_pstream_credits(काष्ठा wmi *wmi)
अणु
	u16 active_tsids;
	u8 stream_exist;
	पूर्णांक i;

	/*
	 * Relinquish credits from all implicitly created pstreams
	 * since when we go to sleep. If user created explicit
	 * thinstreams exists with in a fatpipe leave them पूर्णांकact
	 * क्रम the user to delete.
	 */
	spin_lock_bh(&wmi->lock);
	stream_exist = wmi->fat_pipe_exist;
	spin_unlock_bh(&wmi->lock);

	क्रम (i = 0; i < WMM_NUM_AC; i++) अणु
		अगर (stream_exist & (1 << i)) अणु
			/*
			 * FIXME: Is this lock & unlock inside
			 * क्रम loop correct? may need rework.
			 */
			spin_lock_bh(&wmi->lock);
			active_tsids = wmi->stream_exist_क्रम_ac[i];
			spin_unlock_bh(&wmi->lock);

			/*
			 * If there are no user created thin streams
			 * delete the fatpipe
			 */
			अगर (!active_tsids) अणु
				stream_exist &= ~(1 << i);
				/*
				 * Indicate inactivity to driver layer क्रम
				 * this fatpipe (pstream)
				 */
				ath6kl_indicate_tx_activity(wmi->parent_dev,
							    i, false);
			पूर्ण
		पूर्ण
	पूर्ण

	/* FIXME: Can we करो this assignment without locking ? */
	spin_lock_bh(&wmi->lock);
	wmi->fat_pipe_exist = stream_exist;
	spin_unlock_bh(&wmi->lock);
पूर्ण

अटल पूर्णांक ath6kl_set_bitrate_mask64(काष्ठा wmi *wmi, u8 अगर_idx,
				     स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret, mode, band;
	u64 mcsrate, ratemask[ATH6KL_NUM_BANDS];
	काष्ठा wmi_set_tx_select_rates64_cmd *cmd;

	स_रखो(&ratemask, 0, माप(ratemask));

	/* only check 2.4 and 5 GHz bands, skip the rest */
	क्रम (band = 0; band <= NL80211_BAND_5GHZ; band++) अणु
		/* copy legacy rate mask */
		ratemask[band] = mask->control[band].legacy;
		अगर (band == NL80211_BAND_5GHZ)
			ratemask[band] =
				mask->control[band].legacy << 4;

		/* copy mcs rate mask */
		mcsrate = mask->control[band].ht_mcs[1];
		mcsrate <<= 8;
		mcsrate |= mask->control[band].ht_mcs[0];
		ratemask[band] |= mcsrate << 12;
		ratemask[band] |= mcsrate << 28;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "Ratemask 64 bit: 2.4:%llx 5:%llx\n",
		   ratemask[0], ratemask[1]);

	skb = ath6kl_wmi_get_new_buf(माप(*cmd) * WMI_RATES_MODE_MAX);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_set_tx_select_rates64_cmd *) skb->data;
	क्रम (mode = 0; mode < WMI_RATES_MODE_MAX; mode++) अणु
		/* A mode operate in 5GHZ band */
		अगर (mode == WMI_RATES_MODE_11A ||
		    mode == WMI_RATES_MODE_11A_HT20 ||
		    mode == WMI_RATES_MODE_11A_HT40)
			band = NL80211_BAND_5GHZ;
		अन्यथा
			band = NL80211_BAND_2GHZ;
		cmd->ratemask[mode] = cpu_to_le64(ratemask[band]);
	पूर्ण

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb,
				  WMI_SET_TX_SELECT_RATES_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_set_bitrate_mask32(काष्ठा wmi *wmi, u8 अगर_idx,
				     स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret, mode, band;
	u32 mcsrate, ratemask[ATH6KL_NUM_BANDS];
	काष्ठा wmi_set_tx_select_rates32_cmd *cmd;

	स_रखो(&ratemask, 0, माप(ratemask));

	/* only check 2.4 and 5 GHz bands, skip the rest */
	क्रम (band = 0; band <= NL80211_BAND_5GHZ; band++) अणु
		/* copy legacy rate mask */
		ratemask[band] = mask->control[band].legacy;
		अगर (band == NL80211_BAND_5GHZ)
			ratemask[band] =
				mask->control[band].legacy << 4;

		/* copy mcs rate mask */
		mcsrate = mask->control[band].ht_mcs[0];
		ratemask[band] |= mcsrate << 12;
		ratemask[band] |= mcsrate << 20;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "Ratemask 32 bit: 2.4:%x 5:%x\n",
		   ratemask[0], ratemask[1]);

	skb = ath6kl_wmi_get_new_buf(माप(*cmd) * WMI_RATES_MODE_MAX);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_set_tx_select_rates32_cmd *) skb->data;
	क्रम (mode = 0; mode < WMI_RATES_MODE_MAX; mode++) अणु
		/* A mode operate in 5GHZ band */
		अगर (mode == WMI_RATES_MODE_11A ||
		    mode == WMI_RATES_MODE_11A_HT20 ||
		    mode == WMI_RATES_MODE_11A_HT40)
			band = NL80211_BAND_5GHZ;
		अन्यथा
			band = NL80211_BAND_2GHZ;
		cmd->ratemask[mode] = cpu_to_le32(ratemask[band]);
	पूर्ण

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb,
				  WMI_SET_TX_SELECT_RATES_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_set_bitrate_mask(काष्ठा wmi *wmi, u8 अगर_idx,
				स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	काष्ठा ath6kl *ar = wmi->parent_dev;

	अगर (test_bit(ATH6KL_FW_CAPABILITY_64BIT_RATES,
		     ar->fw_capabilities))
		वापस ath6kl_set_bitrate_mask64(wmi, अगर_idx, mask);
	अन्यथा
		वापस ath6kl_set_bitrate_mask32(wmi, अगर_idx, mask);
पूर्ण

पूर्णांक ath6kl_wmi_set_host_sleep_mode_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				       क्रमागत ath6kl_host_mode host_mode)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_set_host_sleep_mode_cmd *cmd;
	पूर्णांक ret;

	अगर ((host_mode != ATH6KL_HOST_MODE_ASLEEP) &&
	    (host_mode != ATH6KL_HOST_MODE_AWAKE)) अणु
		ath6kl_err("invalid host sleep mode: %d\n", host_mode);
		वापस -EINVAL;
	पूर्ण

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_set_host_sleep_mode_cmd *) skb->data;

	अगर (host_mode == ATH6KL_HOST_MODE_ASLEEP) अणु
		ath6kl_wmi_relinquish_implicit_pstream_credits(wmi);
		cmd->asleep = cpu_to_le32(1);
	पूर्ण अन्यथा अणु
		cmd->awake = cpu_to_le32(1);
	पूर्ण

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb,
				  WMI_SET_HOST_SLEEP_MODE_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

/* This command has zero length payload */
अटल पूर्णांक ath6kl_wmi_host_sleep_mode_cmd_prcd_evt_rx(काष्ठा wmi *wmi,
						      काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा ath6kl *ar = wmi->parent_dev;

	set_bit(HOST_SLEEP_MODE_CMD_PROCESSED, &vअगर->flags);
	wake_up(&ar->event_wq);

	वापस 0;
पूर्ण

पूर्णांक ath6kl_wmi_set_wow_mode_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				क्रमागत ath6kl_wow_mode wow_mode,
				u32 filter, u16 host_req_delay)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_set_wow_mode_cmd *cmd;
	पूर्णांक ret;

	अगर ((wow_mode != ATH6KL_WOW_MODE_ENABLE) &&
	    wow_mode != ATH6KL_WOW_MODE_DISABLE) अणु
		ath6kl_err("invalid wow mode: %d\n", wow_mode);
		वापस -EINVAL;
	पूर्ण

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_set_wow_mode_cmd *) skb->data;
	cmd->enable_wow = cpu_to_le32(wow_mode);
	cmd->filter = cpu_to_le32(filter);
	cmd->host_req_delay = cpu_to_le16(host_req_delay);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_WOW_MODE_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_add_wow_pattern_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				   u8 list_id, u8 filter_size,
				   u8 filter_offset, स्थिर u8 *filter,
				   स्थिर u8 *mask)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_add_wow_pattern_cmd *cmd;
	u16 size;
	u8 *filter_mask;
	पूर्णांक ret;

	/*
	 * Allocate additional memory in the buffer to hold
	 * filter and mask value, which is twice of filter_size.
	 */
	size = माप(*cmd) + (2 * filter_size);

	skb = ath6kl_wmi_get_new_buf(size);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_add_wow_pattern_cmd *) skb->data;
	cmd->filter_list_id = list_id;
	cmd->filter_size = filter_size;
	cmd->filter_offset = filter_offset;

	स_नकल(cmd->filter, filter, filter_size);

	filter_mask = (u8 *) (cmd->filter + filter_size);
	स_नकल(filter_mask, mask, filter_size);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_ADD_WOW_PATTERN_CMDID,
				  NO_SYNC_WMIFLAG);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_del_wow_pattern_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				   u16 list_id, u16 filter_id)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_del_wow_pattern_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_del_wow_pattern_cmd *) skb->data;
	cmd->filter_list_id = cpu_to_le16(list_id);
	cmd->filter_id = cpu_to_le16(filter_id);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_DEL_WOW_PATTERN_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_wmi_cmd_send_xtnd(काष्ठा wmi *wmi, काष्ठा sk_buff *skb,
				    क्रमागत wmix_command_id cmd_id,
				    क्रमागत wmi_sync_flag sync_flag)
अणु
	काष्ठा wmix_cmd_hdr *cmd_hdr;
	पूर्णांक ret;

	skb_push(skb, माप(काष्ठा wmix_cmd_hdr));

	cmd_hdr = (काष्ठा wmix_cmd_hdr *) skb->data;
	cmd_hdr->cmd_id = cpu_to_le32(cmd_id);

	ret = ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_EXTENSION_CMDID, sync_flag);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_get_challenge_resp_cmd(काष्ठा wmi *wmi, u32 cookie, u32 source)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmix_hb_challenge_resp_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmix_hb_challenge_resp_cmd *) skb->data;
	cmd->cookie = cpu_to_le32(cookie);
	cmd->source = cpu_to_le32(source);

	ret = ath6kl_wmi_cmd_send_xtnd(wmi, skb, WMIX_HB_CHALLENGE_RESP_CMDID,
				       NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_config_debug_module_cmd(काष्ठा wmi *wmi, u32 valid, u32 config)
अणु
	काष्ठा ath6kl_wmix_dbglog_cfg_module_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा ath6kl_wmix_dbglog_cfg_module_cmd *) skb->data;
	cmd->valid = cpu_to_le32(valid);
	cmd->config = cpu_to_le32(config);

	ret = ath6kl_wmi_cmd_send_xtnd(wmi, skb, WMIX_DBGLOG_CFG_MODULE_CMDID,
				       NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_get_stats_cmd(काष्ठा wmi *wmi, u8 अगर_idx)
अणु
	वापस ath6kl_wmi_simple_cmd(wmi, अगर_idx, WMI_GET_STATISTICS_CMDID);
पूर्ण

पूर्णांक ath6kl_wmi_set_tx_pwr_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 dbM)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_set_tx_pwr_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(काष्ठा wmi_set_tx_pwr_cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_set_tx_pwr_cmd *) skb->data;
	cmd->dbM = dbM;

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_TX_PWR_CMDID,
				  NO_SYNC_WMIFLAG);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_get_tx_pwr_cmd(काष्ठा wmi *wmi, u8 अगर_idx)
अणु
	वापस ath6kl_wmi_simple_cmd(wmi, अगर_idx, WMI_GET_TX_PWR_CMDID);
पूर्ण

पूर्णांक ath6kl_wmi_get_roam_tbl_cmd(काष्ठा wmi *wmi)
अणु
	वापस ath6kl_wmi_simple_cmd(wmi, 0, WMI_GET_ROAM_TBL_CMDID);
पूर्ण

पूर्णांक ath6kl_wmi_set_lpreamble_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 status,
				 u8 preamble_policy)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_set_lpreamble_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(काष्ठा wmi_set_lpreamble_cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_set_lpreamble_cmd *) skb->data;
	cmd->status = status;
	cmd->preamble_policy = preamble_policy;

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_LPREAMBLE_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_set_rts_cmd(काष्ठा wmi *wmi, u16 threshold)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_set_rts_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(काष्ठा wmi_set_rts_cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_set_rts_cmd *) skb->data;
	cmd->threshold = cpu_to_le16(threshold);

	ret = ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_SET_RTS_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_set_wmm_txop(काष्ठा wmi *wmi, u8 अगर_idx, क्रमागत wmi_txop_cfg cfg)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_set_wmm_txop_cmd *cmd;
	पूर्णांक ret;

	अगर (!((cfg == WMI_TXOP_DISABLED) || (cfg == WMI_TXOP_ENABLED)))
		वापस -EINVAL;

	skb = ath6kl_wmi_get_new_buf(माप(काष्ठा wmi_set_wmm_txop_cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_set_wmm_txop_cmd *) skb->data;
	cmd->txop_enable = cfg;

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_WMM_TXOP_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_set_keepalive_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				 u8 keep_alive_पूर्णांकvl)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_set_keepalive_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_set_keepalive_cmd *) skb->data;
	cmd->keep_alive_पूर्णांकvl = keep_alive_पूर्णांकvl;

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_KEEPALIVE_CMDID,
				  NO_SYNC_WMIFLAG);

	अगर (ret == 0)
		ath6kl_debug_set_keepalive(wmi->parent_dev, keep_alive_पूर्णांकvl);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_set_htcap_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
			     क्रमागत nl80211_band band,
			     काष्ठा ath6kl_htcap *htcap)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_set_htcap_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_set_htcap_cmd *) skb->data;

	/*
	 * NOTE: Band in firmware matches क्रमागत nl80211_band, it is unlikely
	 * this will be changed in firmware. If at all there is any change in
	 * band value, the host needs to be fixed.
	 */
	cmd->band = band;
	cmd->ht_enable = !!htcap->ht_enable;
	cmd->ht20_sgi = !!(htcap->cap_info & IEEE80211_HT_CAP_SGI_20);
	cmd->ht40_supported =
		!!(htcap->cap_info & IEEE80211_HT_CAP_SUP_WIDTH_20_40);
	cmd->ht40_sgi = !!(htcap->cap_info & IEEE80211_HT_CAP_SGI_40);
	cmd->पूर्णांकolerant_40mhz =
		!!(htcap->cap_info & IEEE80211_HT_CAP_40MHZ_INTOLERANT);
	cmd->max_ampdu_len_exp = htcap->ampdu_factor;

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "Set htcap: band:%d ht_enable:%d 40mhz:%d sgi_20mhz:%d sgi_40mhz:%d 40mhz_intolerant:%d ampdu_len_exp:%d\n",
		   cmd->band, cmd->ht_enable, cmd->ht40_supported,
		   cmd->ht20_sgi, cmd->ht40_sgi, cmd->पूर्णांकolerant_40mhz,
		   cmd->max_ampdu_len_exp);
	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_HT_CAP_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_test_cmd(काष्ठा wmi *wmi, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(len);
	अगर (!skb)
		वापस -ENOMEM;

	स_नकल(skb->data, buf, len);

	ret = ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_TEST_CMDID, NO_SYNC_WMIFLAG);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_mcast_filter_cmd(काष्ठा wmi *wmi, u8 अगर_idx, bool mc_all_on)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_mcast_filter_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_mcast_filter_cmd *) skb->data;
	cmd->mcast_all_enable = mc_all_on;

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_MCAST_FILTER_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_add_del_mcast_filter_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
					u8 *filter, bool add_filter)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_mcast_filter_add_del_cmd *cmd;
	पूर्णांक ret;

	अगर ((filter[0] != 0x33 || filter[1] != 0x33) &&
	    (filter[0] != 0x01 || filter[1] != 0x00 ||
	    filter[2] != 0x5e || filter[3] > 0x7f)) अणु
		ath6kl_warn("invalid multicast filter address\n");
		वापस -EINVAL;
	पूर्ण

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_mcast_filter_add_del_cmd *) skb->data;
	स_नकल(cmd->mcast_mac, filter, ATH6KL_MCAST_FILTER_MAC_ADDR_SIZE);
	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb,
				  add_filter ? WMI_SET_MCAST_FILTER_CMDID :
				  WMI_DEL_MCAST_FILTER_CMDID,
				  NO_SYNC_WMIFLAG);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_sta_bmiss_enhance_cmd(काष्ठा wmi *wmi, u8 अगर_idx, bool enhance)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_sta_bmiss_enhance_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_sta_bmiss_enhance_cmd *) skb->data;
	cmd->enable = enhance ? 1 : 0;

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb,
				  WMI_STA_BMISS_ENHANCE_CMDID,
				  NO_SYNC_WMIFLAG);
	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_set_regकरोमुख्य_cmd(काष्ठा wmi *wmi, स्थिर अक्षर *alpha2)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_set_regकरोमुख्य_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_set_regकरोमुख्य_cmd *) skb->data;
	स_नकल(cmd->iso_name, alpha2, 2);

	वापस ath6kl_wmi_cmd_send(wmi, 0, skb,
				   WMI_SET_REGDOMAIN_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

s32 ath6kl_wmi_get_rate(काष्ठा wmi *wmi, s8 rate_index)
अणु
	काष्ठा ath6kl *ar = wmi->parent_dev;
	u8 sgi = 0;
	s32 ret;

	अगर (rate_index == RATE_AUTO)
		वापस 0;

	/* SGI is stored as the MSB of the rate_index */
	अगर (rate_index & RATE_INDEX_MSB) अणु
		rate_index &= RATE_INDEX_WITHOUT_SGI_MASK;
		sgi = 1;
	पूर्ण

	अगर (test_bit(ATH6KL_FW_CAPABILITY_RATETABLE_MCS15,
		     ar->fw_capabilities)) अणु
		अगर (WARN_ON(rate_index >= ARRAY_SIZE(wmi_rate_tbl_mcs15)))
			वापस 0;

		ret = wmi_rate_tbl_mcs15[(u32) rate_index][sgi];
	पूर्ण अन्यथा अणु
		अगर (WARN_ON(rate_index >= ARRAY_SIZE(wmi_rate_tbl)))
			वापस 0;

		ret = wmi_rate_tbl[(u32) rate_index][sgi];
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_wmi_get_pmkid_list_event_rx(काष्ठा wmi *wmi, u8 *datap,
					      u32 len)
अणु
	काष्ठा wmi_pmkid_list_reply *reply;
	u32 expected_len;

	अगर (len < माप(काष्ठा wmi_pmkid_list_reply))
		वापस -EINVAL;

	reply = (काष्ठा wmi_pmkid_list_reply *)datap;
	expected_len = माप(reply->num_pmkid) +
		le32_to_cpu(reply->num_pmkid) * WMI_PMKID_LEN;

	अगर (len < expected_len)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_addba_req_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
					 काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_addba_req_event *cmd = (काष्ठा wmi_addba_req_event *) datap;

	aggr_recv_addba_req_evt(vअगर, cmd->tid,
				le16_to_cpu(cmd->st_seq_no), cmd->win_sz);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_delba_req_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
					 काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_delba_event *cmd = (काष्ठा wmi_delba_event *) datap;

	aggr_recv_delba_req_evt(vअगर, cmd->tid);

	वापस 0;
पूर्ण

/*  AP mode functions */

पूर्णांक ath6kl_wmi_ap_profile_commit(काष्ठा wmi *wmip, u8 अगर_idx,
				 काष्ठा wmi_connect_cmd *p)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_connect_cmd *cm;
	पूर्णांक res;

	skb = ath6kl_wmi_get_new_buf(माप(*cm));
	अगर (!skb)
		वापस -ENOMEM;

	cm = (काष्ठा wmi_connect_cmd *) skb->data;
	स_नकल(cm, p, माप(*cm));

	res = ath6kl_wmi_cmd_send(wmip, अगर_idx, skb, WMI_AP_CONFIG_COMMIT_CMDID,
				  NO_SYNC_WMIFLAG);
	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "%s: nw_type=%u auth_mode=%u ch=%u ctrl_flags=0x%x-> res=%d\n",
		   __func__, p->nw_type, p->auth_mode, le16_to_cpu(p->ch),
		   le32_to_cpu(p->ctrl_flags), res);
	वापस res;
पूर्ण

पूर्णांक ath6kl_wmi_ap_set_mlme(काष्ठा wmi *wmip, u8 अगर_idx, u8 cmd, स्थिर u8 *mac,
			   u16 reason)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_ap_set_mlme_cmd *cm;

	skb = ath6kl_wmi_get_new_buf(माप(*cm));
	अगर (!skb)
		वापस -ENOMEM;

	cm = (काष्ठा wmi_ap_set_mlme_cmd *) skb->data;
	स_नकल(cm->mac, mac, ETH_ALEN);
	cm->reason = cpu_to_le16(reason);
	cm->cmd = cmd;

	ath6kl_dbg(ATH6KL_DBG_WMI, "ap_set_mlme: cmd=%d reason=%d\n", cm->cmd,
		   cm->reason);

	वापस ath6kl_wmi_cmd_send(wmip, अगर_idx, skb, WMI_AP_SET_MLME_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_ap_hidden_ssid(काष्ठा wmi *wmi, u8 अगर_idx, bool enable)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_ap_hidden_ssid_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_ap_hidden_ssid_cmd *) skb->data;
	cmd->hidden_ssid = enable ? 1 : 0;

	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_AP_HIDDEN_SSID_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

/* This command will be used to enable/disable AP uAPSD feature */
पूर्णांक ath6kl_wmi_ap_set_apsd(काष्ठा wmi *wmi, u8 अगर_idx, u8 enable)
अणु
	काष्ठा wmi_ap_set_apsd_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_ap_set_apsd_cmd *)skb->data;
	cmd->enable = enable;

	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_AP_SET_APSD_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_set_apsd_bfrd_traf(काष्ठा wmi *wmi, u8 अगर_idx,
					     u16 aid, u16 biपंचांगap, u32 flags)
अणु
	काष्ठा wmi_ap_apsd_buffered_traffic_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_ap_apsd_buffered_traffic_cmd *)skb->data;
	cmd->aid = cpu_to_le16(aid);
	cmd->biपंचांगap = cpu_to_le16(biपंचांगap);
	cmd->flags = cpu_to_le32(flags);

	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb,
				   WMI_AP_APSD_BUFFERED_TRAFFIC_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

अटल पूर्णांक ath6kl_wmi_pspoll_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
				      काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wmi_pspoll_event *ev;

	अगर (len < माप(काष्ठा wmi_pspoll_event))
		वापस -EINVAL;

	ev = (काष्ठा wmi_pspoll_event *) datap;

	ath6kl_pspoll_event(vअगर, le16_to_cpu(ev->aid));

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_dसमयxpiry_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len,
					  काष्ठा ath6kl_vअगर *vअगर)
अणु
	ath6kl_dसमयxpiry_event(vअगर);

	वापस 0;
पूर्ण

पूर्णांक ath6kl_wmi_set_pvb_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u16 aid,
			   bool flag)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_ap_set_pvb_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(काष्ठा wmi_ap_set_pvb_cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_ap_set_pvb_cmd *) skb->data;
	cmd->aid = cpu_to_le16(aid);
	cmd->rsvd = cpu_to_le16(0);
	cmd->flag = cpu_to_le32(flag);

	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_AP_SET_PVB_CMDID,
				  NO_SYNC_WMIFLAG);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_set_rx_frame_क्रमmat_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				       u8 rx_meta_ver,
				       bool rx_करोt11_hdr, bool defrag_on_host)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_rx_frame_क्रमmat_cmd *cmd;
	पूर्णांक ret;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_rx_frame_क्रमmat_cmd *) skb->data;
	cmd->करोt11_hdr = rx_करोt11_hdr ? 1 : 0;
	cmd->defrag_on_host = defrag_on_host ? 1 : 0;
	cmd->meta_ver = rx_meta_ver;

	/* Delete the local aggr state, on host */
	ret = ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_RX_FRAME_FORMAT_CMDID,
				  NO_SYNC_WMIFLAG);

	वापस ret;
पूर्ण

पूर्णांक ath6kl_wmi_set_appie_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 mgmt_frm_type,
			     स्थिर u8 *ie, u8 ie_len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_set_appie_cmd *p;

	skb = ath6kl_wmi_get_new_buf(माप(*p) + ie_len);
	अगर (!skb)
		वापस -ENOMEM;

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "set_appie_cmd: mgmt_frm_type=%u ie_len=%u\n",
		   mgmt_frm_type, ie_len);
	p = (काष्ठा wmi_set_appie_cmd *) skb->data;
	p->mgmt_frm_type = mgmt_frm_type;
	p->ie_len = ie_len;

	अगर (ie != शून्य && ie_len > 0)
		स_नकल(p->ie_info, ie, ie_len);

	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_APPIE_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_set_ie_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 ie_id, u8 ie_field,
			  स्थिर u8 *ie_info, u8 ie_len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_set_ie_cmd *p;

	skb = ath6kl_wmi_get_new_buf(माप(*p) + ie_len);
	अगर (!skb)
		वापस -ENOMEM;

	ath6kl_dbg(ATH6KL_DBG_WMI, "set_ie_cmd: ie_id=%u ie_ie_field=%u ie_len=%u\n",
		   ie_id, ie_field, ie_len);
	p = (काष्ठा wmi_set_ie_cmd *) skb->data;
	p->ie_id = ie_id;
	p->ie_field = ie_field;
	p->ie_len = ie_len;
	अगर (ie_info && ie_len > 0)
		स_नकल(p->ie_info, ie_info, ie_len);

	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SET_IE_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_disable_11b_rates_cmd(काष्ठा wmi *wmi, bool disable)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_disable_11b_rates_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	ath6kl_dbg(ATH6KL_DBG_WMI, "disable_11b_rates_cmd: disable=%u\n",
		   disable);
	cmd = (काष्ठा wmi_disable_11b_rates_cmd *) skb->data;
	cmd->disable = disable ? 1 : 0;

	वापस ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_DISABLE_11B_RATES_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_reमुख्य_on_chnl_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u32 freq, u32 dur)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_reमुख्य_on_chnl_cmd *p;

	skb = ath6kl_wmi_get_new_buf(माप(*p));
	अगर (!skb)
		वापस -ENOMEM;

	ath6kl_dbg(ATH6KL_DBG_WMI, "remain_on_chnl_cmd: freq=%u dur=%u\n",
		   freq, dur);
	p = (काष्ठा wmi_reमुख्य_on_chnl_cmd *) skb->data;
	p->freq = cpu_to_le32(freq);
	p->duration = cpu_to_le32(dur);
	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_REMAIN_ON_CHNL_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

/* ath6kl_wmi_send_action_cmd is to be deprecated. Use
 * ath6kl_wmi_send_mgmt_cmd instead. The new function supports P2P
 * mgmt operations using station पूर्णांकerface.
 */
अटल पूर्णांक ath6kl_wmi_send_action_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u32 id,
				      u32 freq, u32 रुको, स्थिर u8 *data,
				      u16 data_len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_send_action_cmd *p;
	u8 *buf;

	अगर (रुको)
		वापस -EINVAL; /* Offload क्रम रुको not supported */

	buf = kmemdup(data, data_len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	skb = ath6kl_wmi_get_new_buf(माप(*p) + data_len);
	अगर (!skb) अणु
		kमुक्त(buf);
		वापस -ENOMEM;
	पूर्ण

	kमुक्त(wmi->last_mgmt_tx_frame);
	wmi->last_mgmt_tx_frame = buf;
	wmi->last_mgmt_tx_frame_len = data_len;

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "send_action_cmd: id=%u freq=%u wait=%u len=%u\n",
		   id, freq, रुको, data_len);
	p = (काष्ठा wmi_send_action_cmd *) skb->data;
	p->id = cpu_to_le32(id);
	p->freq = cpu_to_le32(freq);
	p->रुको = cpu_to_le32(रुको);
	p->len = cpu_to_le16(data_len);
	स_नकल(p->data, data, data_len);
	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SEND_ACTION_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

अटल पूर्णांक __ath6kl_wmi_send_mgmt_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u32 id,
				      u32 freq, u32 रुको, स्थिर u8 *data,
				      u16 data_len, u32 no_cck)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_send_mgmt_cmd *p;
	u8 *buf;

	अगर (रुको)
		वापस -EINVAL; /* Offload क्रम रुको not supported */

	buf = kmemdup(data, data_len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	skb = ath6kl_wmi_get_new_buf(माप(*p) + data_len);
	अगर (!skb) अणु
		kमुक्त(buf);
		वापस -ENOMEM;
	पूर्ण

	kमुक्त(wmi->last_mgmt_tx_frame);
	wmi->last_mgmt_tx_frame = buf;
	wmi->last_mgmt_tx_frame_len = data_len;

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "send_action_cmd: id=%u freq=%u wait=%u len=%u\n",
		   id, freq, रुको, data_len);
	p = (काष्ठा wmi_send_mgmt_cmd *) skb->data;
	p->id = cpu_to_le32(id);
	p->freq = cpu_to_le32(freq);
	p->रुको = cpu_to_le32(रुको);
	p->no_cck = cpu_to_le32(no_cck);
	p->len = cpu_to_le16(data_len);
	स_नकल(p->data, data, data_len);
	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_SEND_MGMT_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_send_mgmt_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u32 id, u32 freq,
				u32 रुको, स्थिर u8 *data, u16 data_len,
				u32 no_cck)
अणु
	पूर्णांक status;
	काष्ठा ath6kl *ar = wmi->parent_dev;

	अगर (test_bit(ATH6KL_FW_CAPABILITY_STA_P2PDEV_DUPLEX,
		     ar->fw_capabilities)) अणु
		/*
		 * If capable of करोing P2P mgmt operations using
		 * station पूर्णांकerface, send additional inक्रमmation like
		 * supported rates to advertise and xmit rates क्रम
		 * probe requests
		 */
		status = __ath6kl_wmi_send_mgmt_cmd(ar->wmi, अगर_idx, id, freq,
						    रुको, data, data_len,
						    no_cck);
	पूर्ण अन्यथा अणु
		status = ath6kl_wmi_send_action_cmd(ar->wmi, अगर_idx, id, freq,
						    रुको, data, data_len);
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक ath6kl_wmi_send_probe_response_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u32 freq,
				       स्थिर u8 *dst, स्थिर u8 *data,
				       u16 data_len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_p2p_probe_response_cmd *p;
	माप_प्रकार cmd_len = माप(*p) + data_len;

	अगर (data_len == 0)
		cmd_len++; /* work around target minimum length requirement */

	skb = ath6kl_wmi_get_new_buf(cmd_len);
	अगर (!skb)
		वापस -ENOMEM;

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "send_probe_response_cmd: freq=%u dst=%pM len=%u\n",
		   freq, dst, data_len);
	p = (काष्ठा wmi_p2p_probe_response_cmd *) skb->data;
	p->freq = cpu_to_le32(freq);
	स_नकल(p->destination_addr, dst, ETH_ALEN);
	p->len = cpu_to_le16(data_len);
	स_नकल(p->data, data, data_len);
	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb,
				   WMI_SEND_PROBE_RESPONSE_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_probe_report_req_cmd(काष्ठा wmi *wmi, u8 अगर_idx, bool enable)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_probe_req_report_cmd *p;

	skb = ath6kl_wmi_get_new_buf(माप(*p));
	अगर (!skb)
		वापस -ENOMEM;

	ath6kl_dbg(ATH6KL_DBG_WMI, "probe_report_req_cmd: enable=%u\n",
		   enable);
	p = (काष्ठा wmi_probe_req_report_cmd *) skb->data;
	p->enable = enable ? 1 : 0;
	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_PROBE_REQ_REPORT_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_info_req_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u32 info_req_flags)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_get_p2p_info *p;

	skb = ath6kl_wmi_get_new_buf(माप(*p));
	अगर (!skb)
		वापस -ENOMEM;

	ath6kl_dbg(ATH6KL_DBG_WMI, "info_req_cmd: flags=%x\n",
		   info_req_flags);
	p = (काष्ठा wmi_get_p2p_info *) skb->data;
	p->info_req_flags = cpu_to_le32(info_req_flags);
	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_GET_P2P_INFO_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

पूर्णांक ath6kl_wmi_cancel_reमुख्य_on_chnl_cmd(काष्ठा wmi *wmi, u8 अगर_idx)
अणु
	ath6kl_dbg(ATH6KL_DBG_WMI, "cancel_remain_on_chnl_cmd\n");
	वापस ath6kl_wmi_simple_cmd(wmi, अगर_idx,
				     WMI_CANCEL_REMAIN_ON_CHNL_CMDID);
पूर्ण

पूर्णांक ath6kl_wmi_set_inact_period(काष्ठा wmi *wmi, u8 अगर_idx, पूर्णांक inact_समयout)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_set_inact_period_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_set_inact_period_cmd *) skb->data;
	cmd->inact_period = cpu_to_le32(inact_समयout);
	cmd->num_null_func = 0;

	वापस ath6kl_wmi_cmd_send(wmi, अगर_idx, skb, WMI_AP_CONN_INACT_CMDID,
				   NO_SYNC_WMIFLAG);
पूर्ण

अटल व्योम ath6kl_wmi_hb_challenge_resp_event(काष्ठा wmi *wmi, u8 *datap,
					       पूर्णांक len)
अणु
	काष्ठा wmix_hb_challenge_resp_cmd *cmd;

	अगर (len < माप(काष्ठा wmix_hb_challenge_resp_cmd))
		वापस;

	cmd = (काष्ठा wmix_hb_challenge_resp_cmd *) datap;
	ath6kl_recovery_hb_event(wmi->parent_dev,
				 le32_to_cpu(cmd->cookie));
पूर्ण

अटल पूर्णांक ath6kl_wmi_control_rx_xtnd(काष्ठा wmi *wmi, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmix_cmd_hdr *cmd;
	u32 len;
	u16 id;
	u8 *datap;
	पूर्णांक ret = 0;

	अगर (skb->len < माप(काष्ठा wmix_cmd_hdr)) अणु
		ath6kl_err("bad packet 1\n");
		वापस -EINVAL;
	पूर्ण

	cmd = (काष्ठा wmix_cmd_hdr *) skb->data;
	id = le32_to_cpu(cmd->cmd_id);

	skb_pull(skb, माप(काष्ठा wmix_cmd_hdr));

	datap = skb->data;
	len = skb->len;

	चयन (id) अणु
	हाल WMIX_HB_CHALLENGE_RESP_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "wmi event hb challenge resp\n");
		ath6kl_wmi_hb_challenge_resp_event(wmi, datap, len);
		अवरोध;
	हाल WMIX_DBGLOG_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "wmi event dbglog len %d\n", len);
		ath6kl_debug_fwlog_event(wmi->parent_dev, datap, len);
		अवरोध;
	शेष:
		ath6kl_warn("unknown cmd id 0x%x\n", id);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_wmi_roam_tbl_event_rx(काष्ठा wmi *wmi, u8 *datap, पूर्णांक len)
अणु
	वापस ath6kl_debug_roam_tbl_event(wmi->parent_dev, datap, len);
पूर्ण

/* Process पूर्णांकerface specअगरic wmi events, caller would मुक्त the datap */
अटल पूर्णांक ath6kl_wmi_proc_events_vअगर(काष्ठा wmi *wmi, u16 अगर_idx, u16 cmd_id,
					u8 *datap, u32 len)
अणु
	काष्ठा ath6kl_vअगर *vअगर;

	vअगर = ath6kl_get_vअगर_by_index(wmi->parent_dev, अगर_idx);
	अगर (!vअगर) अणु
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "Wmi event for unavailable vif, vif_index:%d\n",
			    अगर_idx);
		वापस -EINVAL;
	पूर्ण

	चयन (cmd_id) अणु
	हाल WMI_CONNECT_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_CONNECT_EVENTID\n");
		वापस ath6kl_wmi_connect_event_rx(wmi, datap, len, vअगर);
	हाल WMI_DISCONNECT_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_DISCONNECT_EVENTID\n");
		वापस ath6kl_wmi_disconnect_event_rx(wmi, datap, len, vअगर);
	हाल WMI_TKIP_MICERR_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_TKIP_MICERR_EVENTID\n");
		वापस ath6kl_wmi_tkip_micerr_event_rx(wmi, datap, len, vअगर);
	हाल WMI_BSSINFO_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_BSSINFO_EVENTID\n");
		वापस ath6kl_wmi_bssinfo_event_rx(wmi, datap, len, vअगर);
	हाल WMI_NEIGHBOR_REPORT_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_NEIGHBOR_REPORT_EVENTID\n");
		वापस ath6kl_wmi_neighbor_report_event_rx(wmi, datap, len,
							   vअगर);
	हाल WMI_SCAN_COMPLETE_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_SCAN_COMPLETE_EVENTID\n");
		वापस ath6kl_wmi_scan_complete_rx(wmi, datap, len, vअगर);
	हाल WMI_REPORT_STATISTICS_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_REPORT_STATISTICS_EVENTID\n");
		वापस ath6kl_wmi_stats_event_rx(wmi, datap, len, vअगर);
	हाल WMI_CAC_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_CAC_EVENTID\n");
		वापस ath6kl_wmi_cac_event_rx(wmi, datap, len, vअगर);
	हाल WMI_PSPOLL_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_PSPOLL_EVENTID\n");
		वापस ath6kl_wmi_pspoll_event_rx(wmi, datap, len, vअगर);
	हाल WMI_DTIMEXPIRY_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_DTIMEXPIRY_EVENTID\n");
		वापस ath6kl_wmi_dसमयxpiry_event_rx(wmi, datap, len, vअगर);
	हाल WMI_ADDBA_REQ_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_ADDBA_REQ_EVENTID\n");
		वापस ath6kl_wmi_addba_req_event_rx(wmi, datap, len, vअगर);
	हाल WMI_DELBA_REQ_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_DELBA_REQ_EVENTID\n");
		वापस ath6kl_wmi_delba_req_event_rx(wmi, datap, len, vअगर);
	हाल WMI_SET_HOST_SLEEP_MODE_CMD_PROCESSED_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "WMI_SET_HOST_SLEEP_MODE_CMD_PROCESSED_EVENTID");
		वापस ath6kl_wmi_host_sleep_mode_cmd_prcd_evt_rx(wmi, vअगर);
	हाल WMI_REMAIN_ON_CHNL_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_REMAIN_ON_CHNL_EVENTID\n");
		वापस ath6kl_wmi_reमुख्य_on_chnl_event_rx(wmi, datap, len, vअगर);
	हाल WMI_CANCEL_REMAIN_ON_CHNL_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "WMI_CANCEL_REMAIN_ON_CHNL_EVENTID\n");
		वापस ath6kl_wmi_cancel_reमुख्य_on_chnl_event_rx(wmi, datap,
								 len, vअगर);
	हाल WMI_TX_STATUS_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_TX_STATUS_EVENTID\n");
		वापस ath6kl_wmi_tx_status_event_rx(wmi, datap, len, vअगर);
	हाल WMI_RX_PROBE_REQ_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_RX_PROBE_REQ_EVENTID\n");
		वापस ath6kl_wmi_rx_probe_req_event_rx(wmi, datap, len, vअगर);
	हाल WMI_RX_ACTION_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_RX_ACTION_EVENTID\n");
		वापस ath6kl_wmi_rx_action_event_rx(wmi, datap, len, vअगर);
	हाल WMI_TXE_NOTIFY_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_TXE_NOTIFY_EVENTID\n");
		वापस ath6kl_wmi_txe_notअगरy_event_rx(wmi, datap, len, vअगर);
	शेष:
		ath6kl_dbg(ATH6KL_DBG_WMI, "unknown cmd id 0x%x\n", cmd_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wmi_proc_events(काष्ठा wmi *wmi, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_cmd_hdr *cmd;
	पूर्णांक ret = 0;
	u32 len;
	u16 id;
	u8 अगर_idx;
	u8 *datap;

	cmd = (काष्ठा wmi_cmd_hdr *) skb->data;
	id = le16_to_cpu(cmd->cmd_id);
	अगर_idx = le16_to_cpu(cmd->info1) & WMI_CMD_HDR_IF_ID_MASK;

	skb_pull(skb, माप(काष्ठा wmi_cmd_hdr));
	datap = skb->data;
	len = skb->len;

	ath6kl_dbg(ATH6KL_DBG_WMI, "wmi rx id %d len %d\n", id, len);
	ath6kl_dbg_dump(ATH6KL_DBG_WMI_DUMP, शून्य, "wmi rx ",
			datap, len);

	चयन (id) अणु
	हाल WMI_GET_BITRATE_CMDID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_GET_BITRATE_CMDID\n");
		ret = ath6kl_wmi_bitrate_reply_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_GET_CHANNEL_LIST_CMDID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_GET_CHANNEL_LIST_CMDID\n");
		ret = ath6kl_wmi_ch_list_reply_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_GET_TX_PWR_CMDID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_GET_TX_PWR_CMDID\n");
		ret = ath6kl_wmi_tx_pwr_reply_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_READY_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_READY_EVENTID\n");
		ret = ath6kl_wmi_पढ़ोy_event_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_PEER_NODE_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_PEER_NODE_EVENTID\n");
		ret = ath6kl_wmi_peer_node_event_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_REGDOMAIN_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_REGDOMAIN_EVENTID\n");
		ath6kl_wmi_regकरोमुख्य_event(wmi, datap, len);
		अवरोध;
	हाल WMI_PSTREAM_TIMEOUT_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_PSTREAM_TIMEOUT_EVENTID\n");
		ret = ath6kl_wmi_pstream_समयout_event_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_CMDERROR_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_CMDERROR_EVENTID\n");
		ret = ath6kl_wmi_error_event_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_RSSI_THRESHOLD_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_RSSI_THRESHOLD_EVENTID\n");
		ret = ath6kl_wmi_rssi_threshold_event_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_ERROR_REPORT_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_ERROR_REPORT_EVENTID\n");
		अवरोध;
	हाल WMI_OPT_RX_FRAME_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_OPT_RX_FRAME_EVENTID\n");
		/* this event has been deprecated */
		अवरोध;
	हाल WMI_REPORT_ROAM_TBL_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_REPORT_ROAM_TBL_EVENTID\n");
		ret = ath6kl_wmi_roam_tbl_event_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_EXTENSION_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_EXTENSION_EVENTID\n");
		ret = ath6kl_wmi_control_rx_xtnd(wmi, skb);
		अवरोध;
	हाल WMI_CHANNEL_CHANGE_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_CHANNEL_CHANGE_EVENTID\n");
		अवरोध;
	हाल WMI_REPORT_ROAM_DATA_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_REPORT_ROAM_DATA_EVENTID\n");
		अवरोध;
	हाल WMI_TEST_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_TEST_EVENTID\n");
		ret = ath6kl_wmi_test_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_GET_FIXRATES_CMDID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_GET_FIXRATES_CMDID\n");
		ret = ath6kl_wmi_ratemask_reply_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_TX_RETRY_ERR_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_TX_RETRY_ERR_EVENTID\n");
		अवरोध;
	हाल WMI_SNR_THRESHOLD_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_SNR_THRESHOLD_EVENTID\n");
		ret = ath6kl_wmi_snr_threshold_event_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_LQ_THRESHOLD_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_LQ_THRESHOLD_EVENTID\n");
		अवरोध;
	हाल WMI_APLIST_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_APLIST_EVENTID\n");
		ret = ath6kl_wmi_aplist_event_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_GET_KEEPALIVE_CMDID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_GET_KEEPALIVE_CMDID\n");
		ret = ath6kl_wmi_keepalive_reply_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_GET_WOW_LIST_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_GET_WOW_LIST_EVENTID\n");
		अवरोध;
	हाल WMI_GET_PMKID_LIST_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_GET_PMKID_LIST_EVENTID\n");
		ret = ath6kl_wmi_get_pmkid_list_event_rx(wmi, datap, len);
		अवरोध;
	हाल WMI_SET_PARAMS_REPLY_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_SET_PARAMS_REPLY_EVENTID\n");
		अवरोध;
	हाल WMI_ADDBA_RESP_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_ADDBA_RESP_EVENTID\n");
		अवरोध;
	हाल WMI_REPORT_BTCOEX_CONFIG_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "WMI_REPORT_BTCOEX_CONFIG_EVENTID\n");
		अवरोध;
	हाल WMI_REPORT_BTCOEX_STATS_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "WMI_REPORT_BTCOEX_STATS_EVENTID\n");
		अवरोध;
	हाल WMI_TX_COMPLETE_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_TX_COMPLETE_EVENTID\n");
		ret = ath6kl_wmi_tx_complete_event_rx(datap, len);
		अवरोध;
	हाल WMI_P2P_CAPABILITIES_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_P2P_CAPABILITIES_EVENTID\n");
		ret = ath6kl_wmi_p2p_capabilities_event_rx(datap, len);
		अवरोध;
	हाल WMI_P2P_INFO_EVENTID:
		ath6kl_dbg(ATH6KL_DBG_WMI, "WMI_P2P_INFO_EVENTID\n");
		ret = ath6kl_wmi_p2p_info_event_rx(datap, len);
		अवरोध;
	शेष:
		/* may be the event is पूर्णांकerface specअगरic */
		ret = ath6kl_wmi_proc_events_vअगर(wmi, अगर_idx, id, datap, len);
		अवरोध;
	पूर्ण

	dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

/* Control Path */
पूर्णांक ath6kl_wmi_control_rx(काष्ठा wmi *wmi, काष्ठा sk_buff *skb)
अणु
	अगर (WARN_ON(skb == शून्य))
		वापस -EINVAL;

	अगर (skb->len < माप(काष्ठा wmi_cmd_hdr)) अणु
		ath6kl_err("bad packet 1\n");
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	trace_ath6kl_wmi_event(skb->data, skb->len);

	वापस ath6kl_wmi_proc_events(wmi, skb);
पूर्ण

व्योम ath6kl_wmi_reset(काष्ठा wmi *wmi)
अणु
	spin_lock_bh(&wmi->lock);

	wmi->fat_pipe_exist = 0;
	स_रखो(wmi->stream_exist_क्रम_ac, 0, माप(wmi->stream_exist_क्रम_ac));

	spin_unlock_bh(&wmi->lock);
पूर्ण

व्योम *ath6kl_wmi_init(काष्ठा ath6kl *dev)
अणु
	काष्ठा wmi *wmi;

	wmi = kzalloc(माप(काष्ठा wmi), GFP_KERNEL);
	अगर (!wmi)
		वापस शून्य;

	spin_lock_init(&wmi->lock);

	wmi->parent_dev = dev;

	wmi->pwr_mode = REC_POWER;

	ath6kl_wmi_reset(wmi);

	वापस wmi;
पूर्ण

व्योम ath6kl_wmi_shutकरोwn(काष्ठा wmi *wmi)
अणु
	अगर (!wmi)
		वापस;

	kमुक्त(wmi->last_mgmt_tx_frame);
	kमुक्त(wmi);
पूर्ण
