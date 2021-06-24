<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 gelic network driver.
 *
 * Copyright (C) 2007 Sony Computer Entertainment Inc.
 * Copyright 2007 Sony Corporation
 */
#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>

#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/wireless.h>
#समावेश <linux/ieee80211.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <net/iw_handler.h>

#समावेश <linux/dma-mapping.h>
#समावेश <net/checksum.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/ps3.h>
#समावेश <यंत्र/lv1call.h>

#समावेश "ps3_gelic_net.h"
#समावेश "ps3_gelic_wireless.h"


अटल पूर्णांक gelic_wl_start_scan(काष्ठा gelic_wl_info *wl, पूर्णांक always_scan,
			       u8 *essid, माप_प्रकार essid_len);
अटल पूर्णांक gelic_wl_try_associate(काष्ठा net_device *netdev);

/*
 * tables
 */

/* 802.11b/g channel to freq in MHz */
अटल स्थिर पूर्णांक channel_freq[] = अणु
	2412, 2417, 2422, 2427, 2432,
	2437, 2442, 2447, 2452, 2457,
	2462, 2467, 2472, 2484
पूर्ण;
#घोषणा NUM_CHANNELS ARRAY_SIZE(channel_freq)

/* in bps */
अटल स्थिर पूर्णांक bitrate_list[] = अणु
	  1000000,
	  2000000,
	  5500000,
	 11000000,
	  6000000,
	  9000000,
	 12000000,
	 18000000,
	 24000000,
	 36000000,
	 48000000,
	 54000000
पूर्ण;
#घोषणा NUM_BITRATES ARRAY_SIZE(bitrate_list)

/*
 * wpa2 support requires the hypervisor version 2.0 or later
 */
अटल अंतरभूत पूर्णांक wpa2_capable(व्योम)
अणु
	वापस 0 <= ps3_compare_firmware_version(2, 0, 0);
पूर्ण

अटल अंतरभूत पूर्णांक precise_ie(व्योम)
अणु
	वापस 0 <= ps3_compare_firmware_version(2, 2, 0);
पूर्ण
/*
 * post_eurus_cmd helpers
 */
काष्ठा eurus_cmd_arg_info अणु
	पूर्णांक pre_arg; /* command requires arg1, arg2 at POST COMMAND */
	पूर्णांक post_arg; /* command requires arg1, arg2 at GET_RESULT */
पूर्ण;

अटल स्थिर काष्ठा eurus_cmd_arg_info cmd_info[GELIC_EURUS_CMD_MAX_INDEX] = अणु
	[GELIC_EURUS_CMD_SET_COMMON_CFG] = अणु .pre_arg = 1पूर्ण,
	[GELIC_EURUS_CMD_SET_WEP_CFG]    = अणु .pre_arg = 1पूर्ण,
	[GELIC_EURUS_CMD_SET_WPA_CFG]    = अणु .pre_arg = 1पूर्ण,
	[GELIC_EURUS_CMD_GET_COMMON_CFG] = अणु .post_arg = 1पूर्ण,
	[GELIC_EURUS_CMD_GET_WEP_CFG]    = अणु .post_arg = 1पूर्ण,
	[GELIC_EURUS_CMD_GET_WPA_CFG]    = अणु .post_arg = 1पूर्ण,
	[GELIC_EURUS_CMD_GET_RSSI_CFG]   = अणु .post_arg = 1पूर्ण,
	[GELIC_EURUS_CMD_START_SCAN]     = अणु .pre_arg = 1पूर्ण,
	[GELIC_EURUS_CMD_GET_SCAN]       = अणु .post_arg = 1पूर्ण,
पूर्ण;

#अगर_घोषित DEBUG
अटल स्थिर अक्षर *cmdstr(क्रमागत gelic_eurus_command ix)
अणु
	चयन (ix) अणु
	हाल GELIC_EURUS_CMD_ASSOC:
		वापस "ASSOC";
	हाल GELIC_EURUS_CMD_DISASSOC:
		वापस "DISASSOC";
	हाल GELIC_EURUS_CMD_START_SCAN:
		वापस "SCAN";
	हाल GELIC_EURUS_CMD_GET_SCAN:
		वापस "GET SCAN";
	हाल GELIC_EURUS_CMD_SET_COMMON_CFG:
		वापस "SET_COMMON_CFG";
	हाल GELIC_EURUS_CMD_GET_COMMON_CFG:
		वापस "GET_COMMON_CFG";
	हाल GELIC_EURUS_CMD_SET_WEP_CFG:
		वापस "SET_WEP_CFG";
	हाल GELIC_EURUS_CMD_GET_WEP_CFG:
		वापस "GET_WEP_CFG";
	हाल GELIC_EURUS_CMD_SET_WPA_CFG:
		वापस "SET_WPA_CFG";
	हाल GELIC_EURUS_CMD_GET_WPA_CFG:
		वापस "GET_WPA_CFG";
	हाल GELIC_EURUS_CMD_GET_RSSI_CFG:
		वापस "GET_RSSI";
	शेष:
		अवरोध;
	पूर्ण
	वापस "";
पूर्ण;
#अन्यथा
अटल अंतरभूत स्थिर अक्षर *cmdstr(क्रमागत gelic_eurus_command ix)
अणु
	वापस "";
पूर्ण
#पूर्ण_अगर

/* synchronously करो eurus commands */
अटल व्योम gelic_eurus_sync_cmd_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gelic_eurus_cmd *cmd;
	काष्ठा gelic_card *card;
	काष्ठा gelic_wl_info *wl;

	u64 arg1, arg2;

	pr_debug("%s: <-\n", __func__);
	cmd = container_of(work, काष्ठा gelic_eurus_cmd, work);
	BUG_ON(cmd_info[cmd->cmd].pre_arg &&
	       cmd_info[cmd->cmd].post_arg);
	wl = cmd->wl;
	card = port_to_card(wl_port(wl));

	अगर (cmd_info[cmd->cmd].pre_arg) अणु
		arg1 = (cmd->buffer) ?
			ps3_mm_phys_to_lpar(__pa(cmd->buffer)) :
			0;
		arg2 = cmd->buf_size;
	पूर्ण अन्यथा अणु
		arg1 = 0;
		arg2 = 0;
	पूर्ण
	init_completion(&wl->cmd_करोne_पूर्णांकr);
	pr_debug("%s: cmd='%s' start\n", __func__, cmdstr(cmd->cmd));
	cmd->status = lv1_net_control(bus_id(card), dev_id(card),
				      GELIC_LV1_POST_WLAN_CMD,
				      cmd->cmd, arg1, arg2,
				      &cmd->tag, &cmd->size);
	अगर (cmd->status) अणु
		complete(&cmd->करोne);
		pr_info("%s: cmd issue failed\n", __func__);
		वापस;
	पूर्ण

	रुको_क्रम_completion(&wl->cmd_करोne_पूर्णांकr);

	अगर (cmd_info[cmd->cmd].post_arg) अणु
		arg1 = ps3_mm_phys_to_lpar(__pa(cmd->buffer));
		arg2 = cmd->buf_size;
	पूर्ण अन्यथा अणु
		arg1 = 0;
		arg2 = 0;
	पूर्ण

	cmd->status = lv1_net_control(bus_id(card), dev_id(card),
				      GELIC_LV1_GET_WLAN_CMD_RESULT,
				      cmd->tag, arg1, arg2,
				      &cmd->cmd_status, &cmd->size);
#अगर_घोषित DEBUG
	अगर (cmd->status || cmd->cmd_status) अणु
	pr_debug("%s: cmd done tag=%#lx arg1=%#lx, arg2=%#lx\n", __func__,
		 cmd->tag, arg1, arg2);
	pr_debug("%s: cmd done status=%#x cmd_status=%#lx size=%#lx\n",
		 __func__, cmd->status, cmd->cmd_status, cmd->size);
	पूर्ण
#पूर्ण_अगर
	complete(&cmd->करोne);
	pr_debug("%s: cmd='%s' done\n", __func__, cmdstr(cmd->cmd));
पूर्ण

अटल काष्ठा gelic_eurus_cmd *gelic_eurus_sync_cmd(काष्ठा gelic_wl_info *wl,
						    अचिन्हित पूर्णांक eurus_cmd,
						    व्योम *buffer,
						    अचिन्हित पूर्णांक buf_size)
अणु
	काष्ठा gelic_eurus_cmd *cmd;

	/* allocate cmd */
	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस शून्य;

	/* initialize members */
	cmd->cmd = eurus_cmd;
	cmd->buffer = buffer;
	cmd->buf_size = buf_size;
	cmd->wl = wl;
	INIT_WORK(&cmd->work, gelic_eurus_sync_cmd_worker);
	init_completion(&cmd->करोne);
	queue_work(wl->eurus_cmd_queue, &cmd->work);

	/* रुको क्रम command completion */
	रुको_क्रम_completion(&cmd->करोne);

	वापस cmd;
पूर्ण

अटल u32 gelic_wl_get_link(काष्ठा net_device *netdev)
अणु
	काष्ठा gelic_wl_info *wl = port_wl(netdev_port(netdev));
	u32 ret;

	pr_debug("%s: <-\n", __func__);
	mutex_lock(&wl->assoc_stat_lock);
	अगर (wl->assoc_stat == GELIC_WL_ASSOC_STAT_ASSOCIATED)
		ret = 1;
	अन्यथा
		ret = 0;
	mutex_unlock(&wl->assoc_stat_lock);
	pr_debug("%s: ->\n", __func__);
	वापस ret;
पूर्ण

अटल व्योम gelic_wl_send_iwap_event(काष्ठा gelic_wl_info *wl, u8 *bssid)
अणु
	जोड़ iwreq_data data;

	स_रखो(&data, 0, माप(data));
	अगर (bssid)
		स_नकल(data.ap_addr.sa_data, bssid, ETH_ALEN);
	data.ap_addr.sa_family = ARPHRD_ETHER;
	wireless_send_event(port_to_netdev(wl_port(wl)), SIOCGIWAP,
			    &data, शून्य);
पूर्ण

/*
 * wireless extension handlers and helpers
 */

/* SIOGIWNAME */
अटल पूर्णांक gelic_wl_get_name(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *iwreq, अक्षर *extra)
अणु
	म_नकल(iwreq->name, "IEEE 802.11bg");
	वापस 0;
पूर्ण

अटल व्योम gelic_wl_get_ch_info(काष्ठा gelic_wl_info *wl)
अणु
	काष्ठा gelic_card *card = port_to_card(wl_port(wl));
	u64 ch_info_raw, पंचांगp;
	पूर्णांक status;

	अगर (!test_and_set_bit(GELIC_WL_STAT_CH_INFO, &wl->stat)) अणु
		status = lv1_net_control(bus_id(card), dev_id(card),
					 GELIC_LV1_GET_CHANNEL, 0, 0, 0,
					 &ch_info_raw,
					 &पंचांगp);
		/* some fw versions may वापस error */
		अगर (status) अणु
			अगर (status != LV1_NO_ENTRY)
				pr_info("%s: available ch unknown\n", __func__);
			wl->ch_info = 0x07ff;/* 11 ch */
		पूर्ण अन्यथा
			/* 16 bits of MSB has available channels */
			wl->ch_info = ch_info_raw >> 48;
	पूर्ण
पूर्ण

/* SIOGIWRANGE */
अटल पूर्णांक gelic_wl_get_range(काष्ठा net_device *netdev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *iwreq, अक्षर *extra)
अणु
	काष्ठा iw_poपूर्णांक *poपूर्णांक = &iwreq->data;
	काष्ठा iw_range *range = (काष्ठा iw_range *)extra;
	काष्ठा gelic_wl_info *wl = port_wl(netdev_port(netdev));
	अचिन्हित पूर्णांक i, chs;

	pr_debug("%s: <-\n", __func__);
	poपूर्णांक->length = माप(काष्ठा iw_range);
	स_रखो(range, 0, माप(काष्ठा iw_range));

	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 22;

	/* available channels and frequencies */
	gelic_wl_get_ch_info(wl);

	क्रम (i = 0, chs = 0;
	     i < NUM_CHANNELS && chs < IW_MAX_FREQUENCIES; i++)
		अगर (wl->ch_info & (1 << i)) अणु
			range->freq[chs].i = i + 1;
			range->freq[chs].m = channel_freq[i];
			range->freq[chs].e = 6;
			chs++;
		पूर्ण
	range->num_frequency = chs;
	range->old_num_frequency = chs;
	range->num_channels = chs;
	range->old_num_channels = chs;

	/* bitrates */
	क्रम (i = 0; i < NUM_BITRATES; i++)
		range->bitrate[i] = bitrate_list[i];
	range->num_bitrates = i;

	/* संकेत levels */
	range->max_qual.qual = 100; /* relative value */
	range->max_qual.level = 100;
	range->avg_qual.qual = 50;
	range->avg_qual.level = 50;
	range->sensitivity = 0;

	/* Event capability */
	IW_EVENT_CAPA_SET_KERNEL(range->event_capa);
	IW_EVENT_CAPA_SET(range->event_capa, SIOCGIWAP);
	IW_EVENT_CAPA_SET(range->event_capa, SIOCGIWSCAN);

	/* encryption capability */
	range->enc_capa = IW_ENC_CAPA_WPA |
		IW_ENC_CAPA_CIPHER_TKIP | IW_ENC_CAPA_CIPHER_CCMP |
		IW_ENC_CAPA_4WAY_HANDSHAKE;
	अगर (wpa2_capable())
		range->enc_capa |= IW_ENC_CAPA_WPA2;
	range->encoding_size[0] = 5;	/* 40bit WEP */
	range->encoding_size[1] = 13;	/* 104bit WEP */
	range->encoding_size[2] = 32;	/* WPA-PSK */
	range->num_encoding_sizes = 3;
	range->max_encoding_tokens = GELIC_WEP_KEYS;

	/* scan capability */
	range->scan_capa = IW_SCAN_CAPA_ESSID;

	pr_debug("%s: ->\n", __func__);
	वापस 0;

पूर्ण

/* SIOCअणुG,Sपूर्णIWSCAN */
अटल पूर्णांक gelic_wl_set_scan(काष्ठा net_device *netdev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा gelic_wl_info *wl = port_wl(netdev_priv(netdev));
	काष्ठा iw_scan_req *req;
	u8 *essid = शून्य;
	माप_प्रकार essid_len = 0;

	अगर (wrqu->data.length == माप(काष्ठा iw_scan_req) &&
	    wrqu->data.flags & IW_SCAN_THIS_ESSID) अणु
		req = (काष्ठा iw_scan_req*)extra;
		essid = req->essid;
		essid_len = req->essid_len;
		pr_debug("%s: ESSID scan =%s\n", __func__, essid);
	पूर्ण
	वापस gelic_wl_start_scan(wl, 1, essid, essid_len);
पूर्ण

#घोषणा OUI_LEN 3
अटल स्थिर u8 rsn_oui[OUI_LEN] = अणु 0x00, 0x0f, 0xac पूर्ण;
अटल स्थिर u8 wpa_oui[OUI_LEN] = अणु 0x00, 0x50, 0xf2 पूर्ण;

/*
 * synthesize WPA/RSN IE data
 * See WiFi WPA specअगरication and IEEE 802.11-2007 7.3.2.25
 * क्रम the क्रमmat
 */
अटल माप_प्रकार gelic_wl_synthesize_ie(u8 *buf,
				     काष्ठा gelic_eurus_scan_info *scan)
अणु

	स्थिर u8 *oui_header;
	u8 *start = buf;
	पूर्णांक rsn;
	पूर्णांक ccmp;

	pr_debug("%s: <- sec=%16x\n", __func__, scan->security);
	चयन (be16_to_cpu(scan->security) & GELIC_EURUS_SCAN_SEC_MASK) अणु
	हाल GELIC_EURUS_SCAN_SEC_WPA:
		rsn = 0;
		अवरोध;
	हाल GELIC_EURUS_SCAN_SEC_WPA2:
		rsn = 1;
		अवरोध;
	शेष:
		/* WEP or none.  No IE वापसed */
		वापस 0;
	पूर्ण

	चयन (be16_to_cpu(scan->security) & GELIC_EURUS_SCAN_SEC_WPA_MASK) अणु
	हाल GELIC_EURUS_SCAN_SEC_WPA_TKIP:
		ccmp = 0;
		अवरोध;
	हाल GELIC_EURUS_SCAN_SEC_WPA_AES:
		ccmp = 1;
		अवरोध;
	शेष:
		अगर (rsn) अणु
			ccmp = 1;
			pr_info("%s: no cipher info. defaulted to CCMP\n",
				__func__);
		पूर्ण अन्यथा अणु
			ccmp = 0;
			pr_info("%s: no cipher info. defaulted to TKIP\n",
				__func__);
		पूर्ण
	पूर्ण

	अगर (rsn)
		oui_header = rsn_oui;
	अन्यथा
		oui_header = wpa_oui;

	/* element id */
	अगर (rsn)
		*buf++ = WLAN_EID_RSN;
	अन्यथा
		*buf++ = WLAN_EID_VENDOR_SPECIFIC;

	/* length filed; set later */
	buf++;

	/* wpa special header */
	अगर (!rsn) अणु
		स_नकल(buf, wpa_oui, OUI_LEN);
		buf += OUI_LEN;
		*buf++ = 0x01;
	पूर्ण

	/* version */
	*buf++ = 0x01; /* version 1.0 */
	*buf++ = 0x00;

	/* group cipher */
	स_नकल(buf, oui_header, OUI_LEN);
	buf += OUI_LEN;

	अगर (ccmp)
		*buf++ = 0x04; /* CCMP */
	अन्यथा
		*buf++ = 0x02; /* TKIP */

	/* pairwise key count always 1 */
	*buf++ = 0x01;
	*buf++ = 0x00;

	/* pairwise key suit */
	स_नकल(buf, oui_header, OUI_LEN);
	buf += OUI_LEN;
	अगर (ccmp)
		*buf++ = 0x04; /* CCMP */
	अन्यथा
		*buf++ = 0x02; /* TKIP */

	/* AKM count is 1 */
	*buf++ = 0x01;
	*buf++ = 0x00;

	/* AKM suite is assumed as PSK*/
	स_नकल(buf, oui_header, OUI_LEN);
	buf += OUI_LEN;
	*buf++ = 0x02; /* PSK */

	/* RSN capabilities is 0 */
	*buf++ = 0x00;
	*buf++ = 0x00;

	/* set length field */
	start[1] = (buf - start - 2);

	pr_debug("%s: ->\n", __func__);
	वापस buf - start;
पूर्ण

काष्ठा ie_item अणु
	u8 *data;
	u8 len;
पूर्ण;

काष्ठा ie_info अणु
	काष्ठा ie_item wpa;
	काष्ठा ie_item rsn;
पूर्ण;

अटल व्योम gelic_wl_parse_ie(u8 *data, माप_प्रकार len,
			      काष्ठा ie_info *ie_info)
अणु
	माप_प्रकार data_left = len;
	u8 *pos = data;
	u8 item_len;
	u8 item_id;

	pr_debug("%s: data=%p len=%ld\n", __func__,
		 data, len);
	स_रखो(ie_info, 0, माप(काष्ठा ie_info));

	जबतक (2 <= data_left) अणु
		item_id = *pos++;
		item_len = *pos++;
		data_left -= 2;

		अगर (data_left < item_len)
			अवरोध;

		चयन (item_id) अणु
		हाल WLAN_EID_VENDOR_SPECIFIC:
			अगर ((OUI_LEN + 1 <= item_len) &&
			    !स_भेद(pos, wpa_oui, OUI_LEN) &&
			    pos[OUI_LEN] == 0x01) अणु
				ie_info->wpa.data = pos - 2;
				ie_info->wpa.len = item_len + 2;
			पूर्ण
			अवरोध;
		हाल WLAN_EID_RSN:
			ie_info->rsn.data = pos - 2;
			/* length includes the header */
			ie_info->rsn.len = item_len + 2;
			अवरोध;
		शेष:
			pr_debug("%s: ignore %#x,%d\n", __func__,
				 item_id, item_len);
			अवरोध;
		पूर्ण
		pos += item_len;
		data_left -= item_len;
	पूर्ण
	pr_debug("%s: wpa=%p,%d wpa2=%p,%d\n", __func__,
		 ie_info->wpa.data, ie_info->wpa.len,
		 ie_info->rsn.data, ie_info->rsn.len);
पूर्ण


/*
 * translate the scan inक्रमmations from hypervisor to a
 * independent क्रमmat
 */
अटल अक्षर *gelic_wl_translate_scan(काष्ठा net_device *netdev,
				     काष्ठा iw_request_info *info,
				     अक्षर *ev,
				     अक्षर *stop,
				     काष्ठा gelic_wl_scan_info *network)
अणु
	काष्ठा iw_event iwe;
	काष्ठा gelic_eurus_scan_info *scan = network->hwinfo;
	अक्षर *पंचांगp;
	u8 rate;
	अचिन्हित पूर्णांक i, j, len;
	u8 buf[64]; /* arbitrary size large enough */

	pr_debug("%s: <-\n", __func__);

	/* first entry should be AP's mac address */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
	स_नकल(iwe.u.ap_addr.sa_data, &scan->bssid[2], ETH_ALEN);
	ev = iwe_stream_add_event(info, ev, stop, &iwe, IW_EV_ADDR_LEN);

	/* ESSID */
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.flags = 1;
	iwe.u.data.length = strnlen(scan->essid, 32);
	ev = iwe_stream_add_poपूर्णांक(info, ev, stop, &iwe, scan->essid);

	/* FREQUENCY */
	iwe.cmd = SIOCGIWFREQ;
	iwe.u.freq.m = be16_to_cpu(scan->channel);
	iwe.u.freq.e = 0; /* table value in MHz */
	iwe.u.freq.i = 0;
	ev = iwe_stream_add_event(info, ev, stop, &iwe, IW_EV_FREQ_LEN);

	/* RATES */
	iwe.cmd = SIOCGIWRATE;
	iwe.u.bitrate.fixed = iwe.u.bitrate.disabled = 0;
	/* to stuff multiple values in one event */
	पंचांगp = ev + iwe_stream_lcp_len(info);
	/* put them in ascendant order (older is first) */
	i = 0;
	j = 0;
	pr_debug("%s: rates=%d rate=%d\n", __func__,
		 network->rate_len, network->rate_ext_len);
	जबतक (i < network->rate_len) अणु
		अगर (j < network->rate_ext_len &&
		    ((scan->ext_rate[j] & 0x7f) < (scan->rate[i] & 0x7f)))
		    rate = scan->ext_rate[j++] & 0x7f;
		अन्यथा
		    rate = scan->rate[i++] & 0x7f;
		iwe.u.bitrate.value = rate * 500000; /* 500kbps unit */
		पंचांगp = iwe_stream_add_value(info, ev, पंचांगp, stop, &iwe,
					   IW_EV_PARAM_LEN);
	पूर्ण
	जबतक (j < network->rate_ext_len) अणु
		iwe.u.bitrate.value = (scan->ext_rate[j++] & 0x7f) * 500000;
		पंचांगp = iwe_stream_add_value(info, ev, पंचांगp, stop, &iwe,
					   IW_EV_PARAM_LEN);
	पूर्ण
	/* Check अगर we added any rate */
	अगर (iwe_stream_lcp_len(info) < (पंचांगp - ev))
		ev = पंचांगp;

	/* ENCODE */
	iwe.cmd = SIOCGIWENCODE;
	अगर (be16_to_cpu(scan->capability) & WLAN_CAPABILITY_PRIVACY)
		iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
	अन्यथा
		iwe.u.data.flags = IW_ENCODE_DISABLED;
	iwe.u.data.length = 0;
	ev = iwe_stream_add_poपूर्णांक(info, ev, stop, &iwe, scan->essid);

	/* MODE */
	iwe.cmd = SIOCGIWMODE;
	अगर (be16_to_cpu(scan->capability) &
	    (WLAN_CAPABILITY_ESS | WLAN_CAPABILITY_IBSS)) अणु
		अगर (be16_to_cpu(scan->capability) & WLAN_CAPABILITY_ESS)
			iwe.u.mode = IW_MODE_MASTER;
		अन्यथा
			iwe.u.mode = IW_MODE_ADHOC;
		ev = iwe_stream_add_event(info, ev, stop, &iwe, IW_EV_UINT_LEN);
	पूर्ण

	/* QUAL */
	iwe.cmd = IWEVQUAL;
	iwe.u.qual.updated  = IW_QUAL_ALL_UPDATED |
			IW_QUAL_QUAL_INVALID | IW_QUAL_NOISE_INVALID;
	iwe.u.qual.level = be16_to_cpu(scan->rssi);
	iwe.u.qual.qual = be16_to_cpu(scan->rssi);
	iwe.u.qual.noise = 0;
	ev  = iwe_stream_add_event(info, ev, stop, &iwe, IW_EV_QUAL_LEN);

	/* RSN */
	स_रखो(&iwe, 0, माप(iwe));
	अगर (be16_to_cpu(scan->size) <= माप(*scan)) अणु
		/* If wpa[2] capable station, synthesize IE and put it */
		len = gelic_wl_synthesize_ie(buf, scan);
		अगर (len) अणु
			iwe.cmd = IWEVGENIE;
			iwe.u.data.length = len;
			ev = iwe_stream_add_poपूर्णांक(info, ev, stop, &iwe, buf);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* this scan info has IE data */
		काष्ठा ie_info ie_info;
		माप_प्रकार data_len;

		data_len = be16_to_cpu(scan->size) - माप(*scan);

		gelic_wl_parse_ie(scan->elements, data_len, &ie_info);

		अगर (ie_info.wpa.len && (ie_info.wpa.len <= माप(buf))) अणु
			स_नकल(buf, ie_info.wpa.data, ie_info.wpa.len);
			iwe.cmd = IWEVGENIE;
			iwe.u.data.length = ie_info.wpa.len;
			ev = iwe_stream_add_poपूर्णांक(info, ev, stop, &iwe, buf);
		पूर्ण

		अगर (ie_info.rsn.len && (ie_info.rsn.len <= माप(buf))) अणु
			स_रखो(&iwe, 0, माप(iwe));
			स_नकल(buf, ie_info.rsn.data, ie_info.rsn.len);
			iwe.cmd = IWEVGENIE;
			iwe.u.data.length = ie_info.rsn.len;
			ev = iwe_stream_add_poपूर्णांक(info, ev, stop, &iwe, buf);
		पूर्ण
	पूर्ण

	pr_debug("%s: ->\n", __func__);
	वापस ev;
पूर्ण


अटल पूर्णांक gelic_wl_get_scan(काष्ठा net_device *netdev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा gelic_wl_info *wl = port_wl(netdev_priv(netdev));
	काष्ठा gelic_wl_scan_info *scan_info;
	अक्षर *ev = extra;
	अक्षर *stop = ev + wrqu->data.length;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ this_समय = jअगरfies;

	pr_debug("%s: <-\n", __func__);
	अगर (mutex_lock_पूर्णांकerruptible(&wl->scan_lock))
		वापस -EAGAIN;

	चयन (wl->scan_stat) अणु
	हाल GELIC_WL_SCAN_STAT_SCANNING:
		/* If a scan in progress, caller should call me again */
		ret = -EAGAIN;
		जाओ out;
	हाल GELIC_WL_SCAN_STAT_INIT:
		/* last scan request failed or never issued */
		ret = -ENODEV;
		जाओ out;
	हाल GELIC_WL_SCAN_STAT_GOT_LIST:
		/* ok, use current list */
		अवरोध;
	पूर्ण

	list_क्रम_each_entry(scan_info, &wl->network_list, list) अणु
		अगर (wl->scan_age == 0 ||
		    समय_after(scan_info->last_scanned + wl->scan_age,
			       this_समय))
			ev = gelic_wl_translate_scan(netdev, info,
						     ev, stop,
						     scan_info);
		अन्यथा
			pr_debug("%s:entry too old\n", __func__);

		अगर (stop - ev <= IW_EV_ADDR_LEN) अणु
			ret = -E2BIG;
			जाओ out;
		पूर्ण
	पूर्ण

	wrqu->data.length = ev - extra;
	wrqu->data.flags = 0;
out:
	mutex_unlock(&wl->scan_lock);
	pr_debug("%s: -> %d %d\n", __func__, ret, wrqu->data.length);
	वापस ret;
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम scan_list_dump(काष्ठा gelic_wl_info *wl)
अणु
	काष्ठा gelic_wl_scan_info *scan_info;
	पूर्णांक i;

	i = 0;
	list_क्रम_each_entry(scan_info, &wl->network_list, list) अणु
		pr_debug("%s: item %d\n", __func__, i++);
		pr_debug("valid=%d eurusindex=%d last=%lx\n",
			 scan_info->valid, scan_info->eurus_index,
			 scan_info->last_scanned);
		pr_debug("r_len=%d r_ext_len=%d essid_len=%d\n",
			 scan_info->rate_len, scan_info->rate_ext_len,
			 scan_info->essid_len);
		/* -- */
		pr_debug("bssid=%pM\n", &scan_info->hwinfo->bssid[2]);
		pr_debug("essid=%s\n", scan_info->hwinfo->essid);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक gelic_wl_set_auth(काष्ठा net_device *netdev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *data, अक्षर *extra)
अणु
	काष्ठा iw_param *param = &data->param;
	काष्ठा gelic_wl_info *wl = port_wl(netdev_port(netdev));
	अचिन्हित दीर्घ irqflag;
	पूर्णांक ret = 0;

	pr_debug("%s: <- %d\n", __func__, param->flags & IW_AUTH_INDEX);
	spin_lock_irqsave(&wl->lock, irqflag);
	चयन (param->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_WPA_VERSION:
		अगर (param->value & IW_AUTH_WPA_VERSION_DISABLED) अणु
			pr_debug("%s: NO WPA selected\n", __func__);
			wl->wpa_level = GELIC_WL_WPA_LEVEL_NONE;
			wl->group_cipher_method = GELIC_WL_CIPHER_WEP;
			wl->pairwise_cipher_method = GELIC_WL_CIPHER_WEP;
		पूर्ण
		अगर (param->value & IW_AUTH_WPA_VERSION_WPA) अणु
			pr_debug("%s: WPA version 1 selected\n", __func__);
			wl->wpa_level = GELIC_WL_WPA_LEVEL_WPA;
			wl->group_cipher_method = GELIC_WL_CIPHER_TKIP;
			wl->pairwise_cipher_method = GELIC_WL_CIPHER_TKIP;
			wl->auth_method = GELIC_EURUS_AUTH_OPEN;
		पूर्ण
		अगर (param->value & IW_AUTH_WPA_VERSION_WPA2) अणु
			/*
			 * As the hypervisor may not tell the cipher
			 * inक्रमmation of the AP अगर it is WPA2,
			 * you will not decide suitable cipher from
			 * its beacon.
			 * You should have knowledge about the AP's
			 * cipher inक्रमmation in other method prior to
			 * the association.
			 */
			अगर (!precise_ie())
				pr_info("%s: WPA2 may not work\n", __func__);
			अगर (wpa2_capable()) अणु
				wl->wpa_level = GELIC_WL_WPA_LEVEL_WPA2;
				wl->group_cipher_method = GELIC_WL_CIPHER_AES;
				wl->pairwise_cipher_method =
					GELIC_WL_CIPHER_AES;
				wl->auth_method = GELIC_EURUS_AUTH_OPEN;
			पूर्ण अन्यथा
				ret = -EINVAL;
		पूर्ण
		अवरोध;

	हाल IW_AUTH_CIPHER_PAIRWISE:
		अगर (param->value &
		    (IW_AUTH_CIPHER_WEP104 | IW_AUTH_CIPHER_WEP40)) अणु
			pr_debug("%s: WEP selected\n", __func__);
			wl->pairwise_cipher_method = GELIC_WL_CIPHER_WEP;
		पूर्ण
		अगर (param->value & IW_AUTH_CIPHER_TKIP) अणु
			pr_debug("%s: TKIP selected\n", __func__);
			wl->pairwise_cipher_method = GELIC_WL_CIPHER_TKIP;
		पूर्ण
		अगर (param->value & IW_AUTH_CIPHER_CCMP) अणु
			pr_debug("%s: CCMP selected\n", __func__);
			wl->pairwise_cipher_method = GELIC_WL_CIPHER_AES;
		पूर्ण
		अगर (param->value & IW_AUTH_CIPHER_NONE) अणु
			pr_debug("%s: no auth selected\n", __func__);
			wl->pairwise_cipher_method = GELIC_WL_CIPHER_NONE;
		पूर्ण
		अवरोध;
	हाल IW_AUTH_CIPHER_GROUP:
		अगर (param->value &
		    (IW_AUTH_CIPHER_WEP104 | IW_AUTH_CIPHER_WEP40)) अणु
			pr_debug("%s: WEP selected\n", __func__);
			wl->group_cipher_method = GELIC_WL_CIPHER_WEP;
		पूर्ण
		अगर (param->value & IW_AUTH_CIPHER_TKIP) अणु
			pr_debug("%s: TKIP selected\n", __func__);
			wl->group_cipher_method = GELIC_WL_CIPHER_TKIP;
		पूर्ण
		अगर (param->value & IW_AUTH_CIPHER_CCMP) अणु
			pr_debug("%s: CCMP selected\n", __func__);
			wl->group_cipher_method = GELIC_WL_CIPHER_AES;
		पूर्ण
		अगर (param->value & IW_AUTH_CIPHER_NONE) अणु
			pr_debug("%s: no auth selected\n", __func__);
			wl->group_cipher_method = GELIC_WL_CIPHER_NONE;
		पूर्ण
		अवरोध;
	हाल IW_AUTH_80211_AUTH_ALG:
		अगर (param->value & IW_AUTH_ALG_SHARED_KEY) अणु
			pr_debug("%s: shared key specified\n", __func__);
			wl->auth_method = GELIC_EURUS_AUTH_SHARED;
		पूर्ण अन्यथा अगर (param->value & IW_AUTH_ALG_OPEN_SYSTEM) अणु
			pr_debug("%s: open system specified\n", __func__);
			wl->auth_method = GELIC_EURUS_AUTH_OPEN;
		पूर्ण अन्यथा
			ret = -EINVAL;
		अवरोध;

	हाल IW_AUTH_WPA_ENABLED:
		अगर (param->value) अणु
			pr_debug("%s: WPA enabled\n", __func__);
			wl->wpa_level = GELIC_WL_WPA_LEVEL_WPA;
		पूर्ण अन्यथा अणु
			pr_debug("%s: WPA disabled\n", __func__);
			wl->wpa_level = GELIC_WL_WPA_LEVEL_NONE;
		पूर्ण
		अवरोध;

	हाल IW_AUTH_KEY_MGMT:
		अगर (param->value & IW_AUTH_KEY_MGMT_PSK)
			अवरोध;
		fallthrough;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	अगर (!ret)
		set_bit(GELIC_WL_STAT_CONFIGURED, &wl->stat);

	spin_unlock_irqrestore(&wl->lock, irqflag);
	pr_debug("%s: -> %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक gelic_wl_get_auth(काष्ठा net_device *netdev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *iwreq, अक्षर *extra)
अणु
	काष्ठा iw_param *param = &iwreq->param;
	काष्ठा gelic_wl_info *wl = port_wl(netdev_port(netdev));
	अचिन्हित दीर्घ irqflag;
	पूर्णांक ret = 0;

	pr_debug("%s: <- %d\n", __func__, param->flags & IW_AUTH_INDEX);
	spin_lock_irqsave(&wl->lock, irqflag);
	चयन (param->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_WPA_VERSION:
		चयन (wl->wpa_level) अणु
		हाल GELIC_WL_WPA_LEVEL_WPA:
			param->value |= IW_AUTH_WPA_VERSION_WPA;
			अवरोध;
		हाल GELIC_WL_WPA_LEVEL_WPA2:
			param->value |= IW_AUTH_WPA_VERSION_WPA2;
			अवरोध;
		शेष:
			param->value |= IW_AUTH_WPA_VERSION_DISABLED;
		पूर्ण
		अवरोध;

	हाल IW_AUTH_80211_AUTH_ALG:
		अगर (wl->auth_method == GELIC_EURUS_AUTH_SHARED)
			param->value = IW_AUTH_ALG_SHARED_KEY;
		अन्यथा अगर (wl->auth_method == GELIC_EURUS_AUTH_OPEN)
			param->value = IW_AUTH_ALG_OPEN_SYSTEM;
		अवरोध;

	हाल IW_AUTH_WPA_ENABLED:
		चयन (wl->wpa_level) अणु
		हाल GELIC_WL_WPA_LEVEL_WPA:
		हाल GELIC_WL_WPA_LEVEL_WPA2:
			param->value = 1;
			अवरोध;
		शेष:
			param->value = 0;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
	पूर्ण

	spin_unlock_irqrestore(&wl->lock, irqflag);
	pr_debug("%s: -> %d\n", __func__, ret);
	वापस ret;
पूर्ण

/* SIOCअणुS,Gपूर्णIWESSID */
अटल पूर्णांक gelic_wl_set_essid(काष्ठा net_device *netdev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *data, अक्षर *extra)
अणु
	काष्ठा gelic_wl_info *wl = port_wl(netdev_priv(netdev));
	अचिन्हित दीर्घ irqflag;

	pr_debug("%s: <- l=%d f=%d\n", __func__,
		 data->essid.length, data->essid.flags);
	अगर (IW_ESSID_MAX_SIZE < data->essid.length)
		वापस -EINVAL;

	spin_lock_irqsave(&wl->lock, irqflag);
	अगर (data->essid.flags) अणु
		wl->essid_len = data->essid.length;
		स_नकल(wl->essid, extra, wl->essid_len);
		pr_debug("%s: essid = '%s'\n", __func__, extra);
		set_bit(GELIC_WL_STAT_ESSID_SET, &wl->stat);
	पूर्ण अन्यथा अणु
		pr_debug("%s: ESSID any\n", __func__);
		clear_bit(GELIC_WL_STAT_ESSID_SET, &wl->stat);
	पूर्ण
	set_bit(GELIC_WL_STAT_CONFIGURED, &wl->stat);
	spin_unlock_irqrestore(&wl->lock, irqflag);


	gelic_wl_try_associate(netdev); /* FIXME */
	pr_debug("%s: ->\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक gelic_wl_get_essid(काष्ठा net_device *netdev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *data, अक्षर *extra)
अणु
	काष्ठा gelic_wl_info *wl = port_wl(netdev_priv(netdev));
	अचिन्हित दीर्घ irqflag;

	pr_debug("%s: <-\n", __func__);
	mutex_lock(&wl->assoc_stat_lock);
	spin_lock_irqsave(&wl->lock, irqflag);
	अगर (test_bit(GELIC_WL_STAT_ESSID_SET, &wl->stat) ||
	    wl->assoc_stat == GELIC_WL_ASSOC_STAT_ASSOCIATED) अणु
		स_नकल(extra, wl->essid, wl->essid_len);
		data->essid.length = wl->essid_len;
		data->essid.flags = 1;
	पूर्ण अन्यथा
		data->essid.flags = 0;

	mutex_unlock(&wl->assoc_stat_lock);
	spin_unlock_irqrestore(&wl->lock, irqflag);
	pr_debug("%s: -> len=%d\n", __func__, data->essid.length);

	वापस 0;
पूर्ण

/* SIOअणुS,Gपूर्णIWENCODE */
अटल पूर्णांक gelic_wl_set_encode(काष्ठा net_device *netdev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *data, अक्षर *extra)
अणु
	काष्ठा gelic_wl_info *wl = port_wl(netdev_priv(netdev));
	काष्ठा iw_poपूर्णांक *enc = &data->encoding;
	__u16 flags;
	अचिन्हित दीर्घ irqflag;
	पूर्णांक key_index, index_specअगरied;
	पूर्णांक ret = 0;

	pr_debug("%s: <-\n", __func__);
	flags = enc->flags & IW_ENCODE_FLAGS;
	key_index = enc->flags & IW_ENCODE_INDEX;

	pr_debug("%s: key_index = %d\n", __func__, key_index);
	pr_debug("%s: key_len = %d\n", __func__, enc->length);
	pr_debug("%s: flag=%x\n", __func__, enc->flags & IW_ENCODE_FLAGS);

	अगर (GELIC_WEP_KEYS < key_index)
		वापस -EINVAL;

	spin_lock_irqsave(&wl->lock, irqflag);
	अगर (key_index) अणु
		index_specअगरied = 1;
		key_index--;
	पूर्ण अन्यथा अणु
		index_specअगरied = 0;
		key_index = wl->current_key;
	पूर्ण

	अगर (flags & IW_ENCODE_NOKEY) अणु
		/* अगर just IW_ENCODE_NOKEY, change current key index */
		अगर (!flags && index_specअगरied) अणु
			wl->current_key = key_index;
			जाओ करोne;
		पूर्ण

		अगर (flags & IW_ENCODE_DISABLED) अणु
			अगर (!index_specअगरied) अणु
				/* disable encryption */
				wl->group_cipher_method = GELIC_WL_CIPHER_NONE;
				wl->pairwise_cipher_method =
					GELIC_WL_CIPHER_NONE;
				/* invalidate all key */
				wl->key_enabled = 0;
			पूर्ण अन्यथा
				clear_bit(key_index, &wl->key_enabled);
		पूर्ण

		अगर (flags & IW_ENCODE_OPEN)
			wl->auth_method = GELIC_EURUS_AUTH_OPEN;
		अगर (flags & IW_ENCODE_RESTRICTED) अणु
			pr_info("%s: shared key mode enabled\n", __func__);
			wl->auth_method = GELIC_EURUS_AUTH_SHARED;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (IW_ENCODING_TOKEN_MAX < enc->length) अणु
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
		wl->key_len[key_index] = enc->length;
		स_नकल(wl->key[key_index], extra, enc->length);
		set_bit(key_index, &wl->key_enabled);
		wl->pairwise_cipher_method = GELIC_WL_CIPHER_WEP;
		wl->group_cipher_method = GELIC_WL_CIPHER_WEP;
	पूर्ण
	set_bit(GELIC_WL_STAT_CONFIGURED, &wl->stat);
करोne:
	spin_unlock_irqrestore(&wl->lock, irqflag);
	pr_debug("%s: ->\n", __func__);
	वापस ret;
पूर्ण

अटल पूर्णांक gelic_wl_get_encode(काष्ठा net_device *netdev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *data, अक्षर *extra)
अणु
	काष्ठा gelic_wl_info *wl = port_wl(netdev_priv(netdev));
	काष्ठा iw_poपूर्णांक *enc = &data->encoding;
	अचिन्हित दीर्घ irqflag;
	अचिन्हित पूर्णांक key_index;
	पूर्णांक ret = 0;

	pr_debug("%s: <-\n", __func__);
	key_index = enc->flags & IW_ENCODE_INDEX;
	pr_debug("%s: flag=%#x point=%p len=%d extra=%p\n", __func__,
		 enc->flags, enc->poपूर्णांकer, enc->length, extra);
	अगर (GELIC_WEP_KEYS < key_index)
		वापस -EINVAL;

	spin_lock_irqsave(&wl->lock, irqflag);
	अगर (key_index)
		key_index--;
	अन्यथा
		key_index = wl->current_key;

	अगर (wl->group_cipher_method == GELIC_WL_CIPHER_WEP) अणु
		चयन (wl->auth_method) अणु
		हाल GELIC_EURUS_AUTH_OPEN:
			enc->flags = IW_ENCODE_OPEN;
			अवरोध;
		हाल GELIC_EURUS_AUTH_SHARED:
			enc->flags = IW_ENCODE_RESTRICTED;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		enc->flags = IW_ENCODE_DISABLED;

	अगर (test_bit(key_index, &wl->key_enabled)) अणु
		अगर (enc->length < wl->key_len[key_index]) अणु
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
		enc->length = wl->key_len[key_index];
		स_नकल(extra, wl->key[key_index], wl->key_len[key_index]);
	पूर्ण अन्यथा अणु
		enc->length = 0;
		enc->flags |= IW_ENCODE_NOKEY;
	पूर्ण
	enc->flags |= key_index + 1;
	pr_debug("%s: -> flag=%x len=%d\n", __func__,
		 enc->flags, enc->length);

करोne:
	spin_unlock_irqrestore(&wl->lock, irqflag);
	वापस ret;
पूर्ण

/* SIOCअणुS,Gपूर्णIWAP */
अटल पूर्णांक gelic_wl_set_ap(काष्ठा net_device *netdev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *data, अक्षर *extra)
अणु
	काष्ठा gelic_wl_info *wl = port_wl(netdev_priv(netdev));
	अचिन्हित दीर्घ irqflag;

	pr_debug("%s: <-\n", __func__);
	अगर (data->ap_addr.sa_family != ARPHRD_ETHER)
		वापस -EINVAL;

	spin_lock_irqsave(&wl->lock, irqflag);
	अगर (is_valid_ether_addr(data->ap_addr.sa_data)) अणु
		स_नकल(wl->bssid, data->ap_addr.sa_data,
		       ETH_ALEN);
		set_bit(GELIC_WL_STAT_BSSID_SET, &wl->stat);
		set_bit(GELIC_WL_STAT_CONFIGURED, &wl->stat);
		pr_debug("%s: bss=%pM\n", __func__, wl->bssid);
	पूर्ण अन्यथा अणु
		pr_debug("%s: clear bssid\n", __func__);
		clear_bit(GELIC_WL_STAT_BSSID_SET, &wl->stat);
		eth_zero_addr(wl->bssid);
	पूर्ण
	spin_unlock_irqrestore(&wl->lock, irqflag);
	pr_debug("%s: ->\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक gelic_wl_get_ap(काष्ठा net_device *netdev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *data, अक्षर *extra)
अणु
	काष्ठा gelic_wl_info *wl = port_wl(netdev_priv(netdev));
	अचिन्हित दीर्घ irqflag;

	pr_debug("%s: <-\n", __func__);
	mutex_lock(&wl->assoc_stat_lock);
	spin_lock_irqsave(&wl->lock, irqflag);
	अगर (wl->assoc_stat == GELIC_WL_ASSOC_STAT_ASSOCIATED) अणु
		data->ap_addr.sa_family = ARPHRD_ETHER;
		स_नकल(data->ap_addr.sa_data, wl->active_bssid,
		       ETH_ALEN);
	पूर्ण अन्यथा
		eth_zero_addr(data->ap_addr.sa_data);

	spin_unlock_irqrestore(&wl->lock, irqflag);
	mutex_unlock(&wl->assoc_stat_lock);
	pr_debug("%s: ->\n", __func__);
	वापस 0;
पूर्ण

/* SIOCअणुS,Gपूर्णIWENCODEEXT */
अटल पूर्णांक gelic_wl_set_encodeext(काष्ठा net_device *netdev,
				  काष्ठा iw_request_info *info,
				  जोड़ iwreq_data *data, अक्षर *extra)
अणु
	काष्ठा gelic_wl_info *wl = port_wl(netdev_priv(netdev));
	काष्ठा iw_poपूर्णांक *enc = &data->encoding;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
	__u16 alg;
	__u16 flags;
	अचिन्हित दीर्घ irqflag;
	पूर्णांक key_index;
	पूर्णांक ret = 0;

	pr_debug("%s: <-\n", __func__);
	flags = enc->flags & IW_ENCODE_FLAGS;
	alg = ext->alg;
	key_index = enc->flags & IW_ENCODE_INDEX;

	pr_debug("%s: key_index = %d\n", __func__, key_index);
	pr_debug("%s: key_len = %d\n", __func__, enc->length);
	pr_debug("%s: flag=%x\n", __func__, enc->flags & IW_ENCODE_FLAGS);
	pr_debug("%s: ext_flag=%x\n", __func__, ext->ext_flags);
	pr_debug("%s: ext_key_len=%x\n", __func__, ext->key_len);

	अगर (GELIC_WEP_KEYS < key_index)
		वापस -EINVAL;

	spin_lock_irqsave(&wl->lock, irqflag);
	अगर (key_index)
		key_index--;
	अन्यथा
		key_index = wl->current_key;

	अगर (!enc->length && (ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY)) अणु
		/* reques to change शेष key index */
		pr_debug("%s: request to change default key to %d\n",
			 __func__, key_index);
		wl->current_key = key_index;
		जाओ करोne;
	पूर्ण

	अगर (alg == IW_ENCODE_ALG_NONE || (flags & IW_ENCODE_DISABLED)) अणु
		pr_debug("%s: alg disabled\n", __func__);
		wl->wpa_level = GELIC_WL_WPA_LEVEL_NONE;
		wl->group_cipher_method = GELIC_WL_CIPHER_NONE;
		wl->pairwise_cipher_method = GELIC_WL_CIPHER_NONE;
		wl->auth_method = GELIC_EURUS_AUTH_OPEN; /* should be खोलो */
	पूर्ण अन्यथा अगर (alg == IW_ENCODE_ALG_WEP) अणु
		pr_debug("%s: WEP requested\n", __func__);
		अगर (flags & IW_ENCODE_OPEN) अणु
			pr_debug("%s: open key mode\n", __func__);
			wl->auth_method = GELIC_EURUS_AUTH_OPEN;
		पूर्ण
		अगर (flags & IW_ENCODE_RESTRICTED) अणु
			pr_debug("%s: shared key mode\n", __func__);
			wl->auth_method = GELIC_EURUS_AUTH_SHARED;
		पूर्ण
		अगर (IW_ENCODING_TOKEN_MAX < ext->key_len) अणु
			pr_info("%s: key is too long %d\n", __func__,
				ext->key_len);
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
		/* OK, update the key */
		wl->key_len[key_index] = ext->key_len;
		स_रखो(wl->key[key_index], 0, IW_ENCODING_TOKEN_MAX);
		स_नकल(wl->key[key_index], ext->key, ext->key_len);
		set_bit(key_index, &wl->key_enabled);
		/* remember wep info changed */
		set_bit(GELIC_WL_STAT_CONFIGURED, &wl->stat);
	पूर्ण अन्यथा अगर (alg == IW_ENCODE_ALG_PMK) अणु
		अगर (ext->key_len != WPA_PSK_LEN) अणु
			pr_err("%s: PSK length wrong %d\n", __func__,
			       ext->key_len);
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
		स_रखो(wl->psk, 0, माप(wl->psk));
		स_नकल(wl->psk, ext->key, ext->key_len);
		wl->psk_len = ext->key_len;
		wl->psk_type = GELIC_EURUS_WPA_PSK_BIN;
		/* remember PSK configured */
		set_bit(GELIC_WL_STAT_WPA_PSK_SET, &wl->stat);
	पूर्ण
करोne:
	spin_unlock_irqrestore(&wl->lock, irqflag);
	pr_debug("%s: ->\n", __func__);
	वापस ret;
पूर्ण

अटल पूर्णांक gelic_wl_get_encodeext(काष्ठा net_device *netdev,
				  काष्ठा iw_request_info *info,
				  जोड़ iwreq_data *data, अक्षर *extra)
अणु
	काष्ठा gelic_wl_info *wl = port_wl(netdev_priv(netdev));
	काष्ठा iw_poपूर्णांक *enc = &data->encoding;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
	अचिन्हित दीर्घ irqflag;
	पूर्णांक key_index;
	पूर्णांक ret = 0;
	पूर्णांक max_key_len;

	pr_debug("%s: <-\n", __func__);

	max_key_len = enc->length - माप(काष्ठा iw_encode_ext);
	अगर (max_key_len < 0)
		वापस -EINVAL;
	key_index = enc->flags & IW_ENCODE_INDEX;

	pr_debug("%s: key_index = %d\n", __func__, key_index);
	pr_debug("%s: key_len = %d\n", __func__, enc->length);
	pr_debug("%s: flag=%x\n", __func__, enc->flags & IW_ENCODE_FLAGS);

	अगर (GELIC_WEP_KEYS < key_index)
		वापस -EINVAL;

	spin_lock_irqsave(&wl->lock, irqflag);
	अगर (key_index)
		key_index--;
	अन्यथा
		key_index = wl->current_key;

	स_रखो(ext, 0, माप(काष्ठा iw_encode_ext));
	चयन (wl->group_cipher_method) अणु
	हाल GELIC_WL_CIPHER_WEP:
		ext->alg = IW_ENCODE_ALG_WEP;
		enc->flags |= IW_ENCODE_ENABLED;
		अवरोध;
	हाल GELIC_WL_CIPHER_TKIP:
		ext->alg = IW_ENCODE_ALG_TKIP;
		enc->flags |= IW_ENCODE_ENABLED;
		अवरोध;
	हाल GELIC_WL_CIPHER_AES:
		ext->alg = IW_ENCODE_ALG_CCMP;
		enc->flags |= IW_ENCODE_ENABLED;
		अवरोध;
	हाल GELIC_WL_CIPHER_NONE:
	शेष:
		ext->alg = IW_ENCODE_ALG_NONE;
		enc->flags |= IW_ENCODE_NOKEY;
		अवरोध;
	पूर्ण

	अगर (!(enc->flags & IW_ENCODE_NOKEY)) अणु
		अगर (max_key_len < wl->key_len[key_index]) अणु
			ret = -E2BIG;
			जाओ out;
		पूर्ण
		अगर (test_bit(key_index, &wl->key_enabled))
			स_नकल(ext->key, wl->key[key_index],
			       wl->key_len[key_index]);
		अन्यथा
			pr_debug("%s: disabled key requested ix=%d\n",
				 __func__, key_index);
	पूर्ण
out:
	spin_unlock_irqrestore(&wl->lock, irqflag);
	pr_debug("%s: ->\n", __func__);
	वापस ret;
पूर्ण
/* SIOCअणुS,Gपूर्णIWMODE */
अटल पूर्णांक gelic_wl_set_mode(काष्ठा net_device *netdev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *data, अक्षर *extra)
अणु
	__u32 mode = data->mode;
	पूर्णांक ret;

	pr_debug("%s: <-\n", __func__);
	अगर (mode == IW_MODE_INFRA)
		ret = 0;
	अन्यथा
		ret = -EOPNOTSUPP;
	pr_debug("%s: -> %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक gelic_wl_get_mode(काष्ठा net_device *netdev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *data, अक्षर *extra)
अणु
	__u32 *mode = &data->mode;
	pr_debug("%s: <-\n", __func__);
	*mode = IW_MODE_INFRA;
	pr_debug("%s: ->\n", __func__);
	वापस 0;
पूर्ण

/* SIOCGIWNICKN */
अटल पूर्णांक gelic_wl_get_nick(काष्ठा net_device *net_dev,
				  काष्ठा iw_request_info *info,
				  जोड़ iwreq_data *data, अक्षर *extra)
अणु
	म_नकल(extra, "gelic_wl");
	data->data.length = म_माप(extra);
	data->data.flags = 1;
	वापस 0;
पूर्ण


/* --- */

अटल काष्ठा iw_statistics *gelic_wl_get_wireless_stats(
	काष्ठा net_device *netdev)
अणु

	काष्ठा gelic_wl_info *wl = port_wl(netdev_priv(netdev));
	काष्ठा gelic_eurus_cmd *cmd;
	काष्ठा iw_statistics *is;
	काष्ठा gelic_eurus_rssi_info *rssi;
	व्योम *buf;

	pr_debug("%s: <-\n", __func__);

	buf = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	is = &wl->iwstat;
	स_रखो(is, 0, माप(*is));
	cmd = gelic_eurus_sync_cmd(wl, GELIC_EURUS_CMD_GET_RSSI_CFG,
				   buf, माप(*rssi));
	अगर (cmd && !cmd->status && !cmd->cmd_status) अणु
		rssi = buf;
		is->qual.level = be16_to_cpu(rssi->rssi);
		is->qual.updated = IW_QUAL_LEVEL_UPDATED |
			IW_QUAL_QUAL_INVALID | IW_QUAL_NOISE_INVALID;
	पूर्ण अन्यथा
		/* not associated */
		is->qual.updated = IW_QUAL_ALL_INVALID;

	kमुक्त(cmd);
	मुक्त_page((अचिन्हित दीर्घ)buf);
	pr_debug("%s: ->\n", __func__);
	वापस is;
पूर्ण

/*
 *  scanning helpers
 */
अटल पूर्णांक gelic_wl_start_scan(काष्ठा gelic_wl_info *wl, पूर्णांक always_scan,
			       u8 *essid, माप_प्रकार essid_len)
अणु
	काष्ठा gelic_eurus_cmd *cmd;
	पूर्णांक ret = 0;
	व्योम *buf = शून्य;
	माप_प्रकार len;

	pr_debug("%s: <- always=%d\n", __func__, always_scan);
	अगर (mutex_lock_पूर्णांकerruptible(&wl->scan_lock))
		वापस -ERESTARTSYS;

	/*
	 * If alपढ़ोy a scan in progress, करो not trigger more
	 */
	अगर (wl->scan_stat == GELIC_WL_SCAN_STAT_SCANNING) अणु
		pr_debug("%s: scanning now\n", __func__);
		जाओ out;
	पूर्ण

	init_completion(&wl->scan_करोne);
	/*
	 * If we have alपढ़ोy a bss list, करोn't try to get new
	 * unless we are करोing an ESSID scan
	 */
	अगर ((!essid_len && !always_scan)
	    && wl->scan_stat == GELIC_WL_SCAN_STAT_GOT_LIST) अणु
		pr_debug("%s: already has the list\n", __func__);
		complete(&wl->scan_करोne);
		जाओ out;
	पूर्ण

	/* ESSID scan ? */
	अगर (essid_len && essid) अणु
		buf = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
		अगर (!buf) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		len = IW_ESSID_MAX_SIZE; /* hypervisor always requires 32 */
		स_रखो(buf, 0, len);
		स_नकल(buf, essid, essid_len);
		pr_debug("%s: essid scan='%s'\n", __func__, (अक्षर *)buf);
	पूर्ण अन्यथा
		len = 0;

	/*
	 * issue start scan request
	 */
	wl->scan_stat = GELIC_WL_SCAN_STAT_SCANNING;
	cmd = gelic_eurus_sync_cmd(wl, GELIC_EURUS_CMD_START_SCAN,
				   buf, len);
	अगर (!cmd || cmd->status || cmd->cmd_status) अणु
		wl->scan_stat = GELIC_WL_SCAN_STAT_INIT;
		complete(&wl->scan_करोne);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	kमुक्त(cmd);
out:
	मुक्त_page((अचिन्हित दीर्घ)buf);
	mutex_unlock(&wl->scan_lock);
	pr_debug("%s: ->\n", __func__);
	वापस ret;
पूर्ण

/*
 * retrieve scan result from the chip (hypervisor)
 * this function is invoked by schedule work.
 */
अटल व्योम gelic_wl_scan_complete_event(काष्ठा gelic_wl_info *wl)
अणु
	काष्ठा gelic_eurus_cmd *cmd = शून्य;
	काष्ठा gelic_wl_scan_info *target, *पंचांगp;
	काष्ठा gelic_wl_scan_info *oldest = शून्य;
	काष्ठा gelic_eurus_scan_info *scan_info;
	अचिन्हित पूर्णांक scan_info_size;
	जोड़ iwreq_data data;
	अचिन्हित दीर्घ this_समय = jअगरfies;
	अचिन्हित पूर्णांक data_len, i, found, r;
	व्योम *buf;

	pr_debug("%s:start\n", __func__);
	mutex_lock(&wl->scan_lock);

	buf = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!buf) अणु
		pr_info("%s: scan buffer alloc failed\n", __func__);
		जाओ out;
	पूर्ण

	अगर (wl->scan_stat != GELIC_WL_SCAN_STAT_SCANNING) अणु
		/*
		 * stop() may be called जबतक scanning, ignore result
		 */
		pr_debug("%s: scan complete when stat != scanning(%d)\n",
			 __func__, wl->scan_stat);
		जाओ out;
	पूर्ण

	cmd = gelic_eurus_sync_cmd(wl, GELIC_EURUS_CMD_GET_SCAN,
				   buf, PAGE_SIZE);
	अगर (!cmd || cmd->status || cmd->cmd_status) अणु
		wl->scan_stat = GELIC_WL_SCAN_STAT_INIT;
		pr_info("%s:cmd failed\n", __func__);
		kमुक्त(cmd);
		जाओ out;
	पूर्ण
	data_len = cmd->size;
	pr_debug("%s: data_len = %d\n", __func__, data_len);
	kमुक्त(cmd);

	/* OK, bss list retrieved */
	wl->scan_stat = GELIC_WL_SCAN_STAT_GOT_LIST;

	/* mark all entries are old */
	list_क्रम_each_entry_safe(target, पंचांगp, &wl->network_list, list) अणु
		target->valid = 0;
		/* expire too old entries */
		अगर (समय_beक्रमe(target->last_scanned + wl->scan_age,
				this_समय)) अणु
			kमुक्त(target->hwinfo);
			target->hwinfo = शून्य;
			list_move_tail(&target->list, &wl->network_मुक्त_list);
		पूर्ण
	पूर्ण

	/* put them in the network_list */
	क्रम (i = 0, scan_info_size = 0, scan_info = buf;
	     scan_info_size < data_len;
	     i++, scan_info_size += be16_to_cpu(scan_info->size),
	     scan_info = (व्योम *)scan_info + be16_to_cpu(scan_info->size)) अणु
		pr_debug("%s:size=%d bssid=%pM scan_info=%p\n", __func__,
			 be16_to_cpu(scan_info->size),
			 &scan_info->bssid[2], scan_info);

		/*
		 * The wireless firmware may वापस invalid channel 0 and/or
		 * invalid rate अगर the AP emits zero length SSID ie. As this
		 * scan inक्रमmation is useless, ignore it
		 */
		अगर (!be16_to_cpu(scan_info->channel) || !scan_info->rate[0]) अणु
			pr_debug("%s: invalid scan info\n", __func__);
			जारी;
		पूर्ण

		found = 0;
		oldest = शून्य;
		list_क्रम_each_entry(target, &wl->network_list, list) अणु
			अगर (ether_addr_equal(&target->hwinfo->bssid[2],
					     &scan_info->bssid[2])) अणु
				found = 1;
				pr_debug("%s: same BBS found scanned list\n",
					 __func__);
				अवरोध;
			पूर्ण
			अगर (!oldest ||
			    (target->last_scanned < oldest->last_scanned))
				oldest = target;
		पूर्ण

		अगर (!found) अणु
			/* not found in the list */
			अगर (list_empty(&wl->network_मुक्त_list)) अणु
				/* expire oldest */
				target = oldest;
			पूर्ण अन्यथा अणु
				target = list_entry(wl->network_मुक्त_list.next,
						    काष्ठा gelic_wl_scan_info,
						    list);
			पूर्ण
		पूर्ण

		/* update the item */
		target->last_scanned = this_समय;
		target->valid = 1;
		target->eurus_index = i;
		kमुक्त(target->hwinfo);
		target->hwinfo = kmemdup(scan_info,
					 be16_to_cpu(scan_info->size),
					 GFP_KERNEL);
		अगर (!target->hwinfo)
			जारी;

		/* copy hw scan info */
		target->essid_len = strnlen(scan_info->essid,
					    माप(scan_info->essid));
		target->rate_len = 0;
		क्रम (r = 0; r < 12; r++)
			अगर (scan_info->rate[r])
				target->rate_len++;
		अगर (8 < target->rate_len)
			pr_info("%s: AP returns %d rates\n", __func__,
				target->rate_len);
		target->rate_ext_len = 0;
		क्रम (r = 0; r < 16; r++)
			अगर (scan_info->ext_rate[r])
				target->rate_ext_len++;
		list_move_tail(&target->list, &wl->network_list);
	पूर्ण
	स_रखो(&data, 0, माप(data));
	wireless_send_event(port_to_netdev(wl_port(wl)), SIOCGIWSCAN, &data,
			    शून्य);
out:
	मुक्त_page((अचिन्हित दीर्घ)buf);
	complete(&wl->scan_करोne);
	mutex_unlock(&wl->scan_lock);
	pr_debug("%s:end\n", __func__);
पूर्ण

/*
 * Select an appropriate bss from current scan list regarding
 * current settings from userspace.
 * The caller must hold wl->scan_lock,
 * and on the state of wl->scan_state == GELIC_WL_SCAN_GOT_LIST
 */
अटल व्योम update_best(काष्ठा gelic_wl_scan_info **best,
			काष्ठा gelic_wl_scan_info *candid,
			पूर्णांक *best_weight,
			पूर्णांक *weight)
अणु
	अगर (*best_weight < ++(*weight)) अणु
		*best_weight = *weight;
		*best = candid;
	पूर्ण
पूर्ण

अटल
काष्ठा gelic_wl_scan_info *gelic_wl_find_best_bss(काष्ठा gelic_wl_info *wl)
अणु
	काष्ठा gelic_wl_scan_info *scan_info;
	काष्ठा gelic_wl_scan_info *best_bss;
	पूर्णांक weight, best_weight;
	u16 security;

	pr_debug("%s: <-\n", __func__);

	best_bss = शून्य;
	best_weight = 0;

	list_क्रम_each_entry(scan_info, &wl->network_list, list) अणु
		pr_debug("%s: station %p\n", __func__, scan_info);

		अगर (!scan_info->valid) अणु
			pr_debug("%s: station invalid\n", __func__);
			जारी;
		पूर्ण

		/* If bss specअगरied, check it only */
		अगर (test_bit(GELIC_WL_STAT_BSSID_SET, &wl->stat)) अणु
			अगर (ether_addr_equal(&scan_info->hwinfo->bssid[2],
					     wl->bssid)) अणु
				best_bss = scan_info;
				pr_debug("%s: bssid matched\n", __func__);
				अवरोध;
			पूर्ण अन्यथा अणु
				pr_debug("%s: bssid unmatched\n", __func__);
				जारी;
			पूर्ण
		पूर्ण

		weight = 0;

		/* security */
		security = be16_to_cpu(scan_info->hwinfo->security) &
			GELIC_EURUS_SCAN_SEC_MASK;
		अगर (wl->wpa_level == GELIC_WL_WPA_LEVEL_WPA2) अणु
			अगर (security == GELIC_EURUS_SCAN_SEC_WPA2)
				update_best(&best_bss, scan_info,
					    &best_weight, &weight);
			अन्यथा
				जारी;
		पूर्ण अन्यथा अगर (wl->wpa_level == GELIC_WL_WPA_LEVEL_WPA) अणु
			अगर (security == GELIC_EURUS_SCAN_SEC_WPA)
				update_best(&best_bss, scan_info,
					    &best_weight, &weight);
			अन्यथा
				जारी;
		पूर्ण अन्यथा अगर (wl->wpa_level == GELIC_WL_WPA_LEVEL_NONE &&
			   wl->group_cipher_method == GELIC_WL_CIPHER_WEP) अणु
			अगर (security == GELIC_EURUS_SCAN_SEC_WEP)
				update_best(&best_bss, scan_info,
					    &best_weight, &weight);
			अन्यथा
				जारी;
		पूर्ण

		/* If ESSID is set, check it */
		अगर (test_bit(GELIC_WL_STAT_ESSID_SET, &wl->stat)) अणु
			अगर ((scan_info->essid_len == wl->essid_len) &&
			    !म_भेदन(wl->essid,
				     scan_info->hwinfo->essid,
				     scan_info->essid_len))
				update_best(&best_bss, scan_info,
					    &best_weight, &weight);
			अन्यथा
				जारी;
		पूर्ण
	पूर्ण

#अगर_घोषित DEBUG
	pr_debug("%s: -> bss=%p\n", __func__, best_bss);
	अगर (best_bss) अणु
		pr_debug("%s:addr=%pM\n", __func__,
			 &best_bss->hwinfo->bssid[2]);
	पूर्ण
#पूर्ण_अगर
	वापस best_bss;
पूर्ण

/*
 * Setup WEP configuration to the chip
 * The caller must hold wl->scan_lock,
 * and on the state of wl->scan_state == GELIC_WL_SCAN_GOT_LIST
 */
अटल पूर्णांक gelic_wl_करो_wep_setup(काष्ठा gelic_wl_info *wl)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा gelic_eurus_wep_cfg *wep;
	काष्ठा gelic_eurus_cmd *cmd;
	पूर्णांक wep104 = 0;
	पूर्णांक have_key = 0;
	पूर्णांक ret = 0;

	pr_debug("%s: <-\n", __func__);
	/* we can assume no one should uses the buffer */
	wep = (काष्ठा gelic_eurus_wep_cfg *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!wep)
		वापस -ENOMEM;

	स_रखो(wep, 0, माप(*wep));

	अगर (wl->group_cipher_method == GELIC_WL_CIPHER_WEP) अणु
		pr_debug("%s: WEP mode\n", __func__);
		क्रम (i = 0; i < GELIC_WEP_KEYS; i++) अणु
			अगर (!test_bit(i, &wl->key_enabled))
				जारी;

			pr_debug("%s: key#%d enabled\n", __func__, i);
			have_key = 1;
			अगर (wl->key_len[i] == 13)
				wep104 = 1;
			अन्यथा अगर (wl->key_len[i] != 5) अणु
				pr_info("%s: wrong wep key[%d]=%d\n",
					__func__, i, wl->key_len[i]);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			स_नकल(wep->key[i], wl->key[i], wl->key_len[i]);
		पूर्ण

		अगर (!have_key) अणु
			pr_info("%s: all wep key disabled\n", __func__);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (wep104) अणु
			pr_debug("%s: 104bit key\n", __func__);
			wep->security = cpu_to_be16(GELIC_EURUS_WEP_SEC_104BIT);
		पूर्ण अन्यथा अणु
			pr_debug("%s: 40bit key\n", __func__);
			wep->security = cpu_to_be16(GELIC_EURUS_WEP_SEC_40BIT);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_debug("%s: NO encryption\n", __func__);
		wep->security = cpu_to_be16(GELIC_EURUS_WEP_SEC_NONE);
	पूर्ण

	/* issue wep setup */
	cmd = gelic_eurus_sync_cmd(wl, GELIC_EURUS_CMD_SET_WEP_CFG,
				   wep, माप(*wep));
	अगर (!cmd)
		ret = -ENOMEM;
	अन्यथा अगर (cmd->status || cmd->cmd_status)
		ret = -ENXIO;

	kमुक्त(cmd);
out:
	मुक्त_page((अचिन्हित दीर्घ)wep);
	pr_debug("%s: ->\n", __func__);
	वापस ret;
पूर्ण

#अगर_घोषित DEBUG
अटल स्थिर अक्षर *wpasecstr(क्रमागत gelic_eurus_wpa_security sec)
अणु
	चयन (sec) अणु
	हाल GELIC_EURUS_WPA_SEC_NONE:
		वापस "NONE";
	हाल GELIC_EURUS_WPA_SEC_WPA_TKIP_TKIP:
		वापस "WPA_TKIP_TKIP";
	हाल GELIC_EURUS_WPA_SEC_WPA_TKIP_AES:
		वापस "WPA_TKIP_AES";
	हाल GELIC_EURUS_WPA_SEC_WPA_AES_AES:
		वापस "WPA_AES_AES";
	हाल GELIC_EURUS_WPA_SEC_WPA2_TKIP_TKIP:
		वापस "WPA2_TKIP_TKIP";
	हाल GELIC_EURUS_WPA_SEC_WPA2_TKIP_AES:
		वापस "WPA2_TKIP_AES";
	हाल GELIC_EURUS_WPA_SEC_WPA2_AES_AES:
		वापस "WPA2_AES_AES";
	पूर्ण
	वापस "";
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक gelic_wl_करो_wpa_setup(काष्ठा gelic_wl_info *wl)
अणु
	काष्ठा gelic_eurus_wpa_cfg *wpa;
	काष्ठा gelic_eurus_cmd *cmd;
	u16 security;
	पूर्णांक ret = 0;

	pr_debug("%s: <-\n", __func__);
	/* we can assume no one should uses the buffer */
	wpa = (काष्ठा gelic_eurus_wpa_cfg *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!wpa)
		वापस -ENOMEM;

	स_रखो(wpa, 0, माप(*wpa));

	अगर (!test_bit(GELIC_WL_STAT_WPA_PSK_SET, &wl->stat))
		pr_info("%s: PSK not configured yet\n", __func__);

	/* copy key */
	स_नकल(wpa->psk, wl->psk, wl->psk_len);

	/* set security level */
	अगर (wl->wpa_level == GELIC_WL_WPA_LEVEL_WPA2) अणु
		अगर (wl->group_cipher_method == GELIC_WL_CIPHER_AES) अणु
			security = GELIC_EURUS_WPA_SEC_WPA2_AES_AES;
		पूर्ण अन्यथा अणु
			अगर (wl->pairwise_cipher_method == GELIC_WL_CIPHER_AES &&
			    precise_ie())
				security = GELIC_EURUS_WPA_SEC_WPA2_TKIP_AES;
			अन्यथा
				security = GELIC_EURUS_WPA_SEC_WPA2_TKIP_TKIP;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (wl->group_cipher_method == GELIC_WL_CIPHER_AES) अणु
			security = GELIC_EURUS_WPA_SEC_WPA_AES_AES;
		पूर्ण अन्यथा अणु
			अगर (wl->pairwise_cipher_method == GELIC_WL_CIPHER_AES &&
			    precise_ie())
				security = GELIC_EURUS_WPA_SEC_WPA_TKIP_AES;
			अन्यथा
				security = GELIC_EURUS_WPA_SEC_WPA_TKIP_TKIP;
		पूर्ण
	पूर्ण
	wpa->security = cpu_to_be16(security);

	/* PSK type */
	wpa->psk_type = cpu_to_be16(wl->psk_type);
#अगर_घोषित DEBUG
	pr_debug("%s: sec=%s psktype=%s\n", __func__,
		 wpasecstr(wpa->security),
		 (wpa->psk_type == GELIC_EURUS_WPA_PSK_BIN) ?
		 "BIN" : "passphrase");
#अगर 0
	/*
	 * करोn't enable here अगर you plan to submit
	 * the debug log because this dumps your precious
	 * passphrase/key.
	 */
	pr_debug("%s: psk=%s\n", __func__,
		 (wpa->psk_type == GELIC_EURUS_WPA_PSK_BIN) ?
		 "N/A" : wpa->psk);
#पूर्ण_अगर
#पूर्ण_अगर
	/* issue wpa setup */
	cmd = gelic_eurus_sync_cmd(wl, GELIC_EURUS_CMD_SET_WPA_CFG,
				   wpa, माप(*wpa));
	अगर (!cmd)
		ret = -ENOMEM;
	अन्यथा अगर (cmd->status || cmd->cmd_status)
		ret = -ENXIO;
	kमुक्त(cmd);
	मुक्त_page((अचिन्हित दीर्घ)wpa);
	pr_debug("%s: --> %d\n", __func__, ret);
	वापस ret;
पूर्ण

/*
 * Start association. caller must hold assoc_stat_lock
 */
अटल पूर्णांक gelic_wl_associate_bss(काष्ठा gelic_wl_info *wl,
				  काष्ठा gelic_wl_scan_info *bss)
अणु
	काष्ठा gelic_eurus_cmd *cmd;
	काष्ठा gelic_eurus_common_cfg *common;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ rc;

	pr_debug("%s: <-\n", __func__);

	/* करो common config */
	common = (काष्ठा gelic_eurus_common_cfg *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!common)
		वापस -ENOMEM;

	स_रखो(common, 0, माप(*common));
	common->bss_type = cpu_to_be16(GELIC_EURUS_BSS_INFRA);
	common->op_mode = cpu_to_be16(GELIC_EURUS_OPMODE_11BG);

	common->scan_index = cpu_to_be16(bss->eurus_index);
	चयन (wl->auth_method) अणु
	हाल GELIC_EURUS_AUTH_OPEN:
		common->auth_method = cpu_to_be16(GELIC_EURUS_AUTH_OPEN);
		अवरोध;
	हाल GELIC_EURUS_AUTH_SHARED:
		common->auth_method = cpu_to_be16(GELIC_EURUS_AUTH_SHARED);
		अवरोध;
	पूर्ण

#अगर_घोषित DEBUG
	scan_list_dump(wl);
#पूर्ण_अगर
	pr_debug("%s: common cfg index=%d bsstype=%d auth=%d\n", __func__,
		 be16_to_cpu(common->scan_index),
		 be16_to_cpu(common->bss_type),
		 be16_to_cpu(common->auth_method));

	cmd = gelic_eurus_sync_cmd(wl, GELIC_EURUS_CMD_SET_COMMON_CFG,
				   common, माप(*common));
	अगर (!cmd || cmd->status || cmd->cmd_status) अणु
		ret = -ENOMEM;
		kमुक्त(cmd);
		जाओ out;
	पूर्ण
	kमुक्त(cmd);

	/* WEP/WPA */
	चयन (wl->wpa_level) अणु
	हाल GELIC_WL_WPA_LEVEL_NONE:
		/* If WEP or no security, setup WEP config */
		ret = gelic_wl_करो_wep_setup(wl);
		अवरोध;
	हाल GELIC_WL_WPA_LEVEL_WPA:
	हाल GELIC_WL_WPA_LEVEL_WPA2:
		ret = gelic_wl_करो_wpa_setup(wl);
		अवरोध;
	पूर्ण

	अगर (ret) अणु
		pr_debug("%s: WEP/WPA setup failed %d\n", __func__,
			 ret);
		ret = -EPERM;
		gelic_wl_send_iwap_event(wl, शून्य);
		जाओ out;
	पूर्ण

	/* start association */
	init_completion(&wl->assoc_करोne);
	wl->assoc_stat = GELIC_WL_ASSOC_STAT_ASSOCIATING;
	cmd = gelic_eurus_sync_cmd(wl, GELIC_EURUS_CMD_ASSOC,
				   शून्य, 0);
	अगर (!cmd || cmd->status || cmd->cmd_status) अणु
		pr_debug("%s: assoc request failed\n", __func__);
		wl->assoc_stat = GELIC_WL_ASSOC_STAT_DISCONN;
		kमुक्त(cmd);
		ret = -ENOMEM;
		gelic_wl_send_iwap_event(wl, शून्य);
		जाओ out;
	पूर्ण
	kमुक्त(cmd);

	/* रुको क्रम connected event */
	rc = रुको_क्रम_completion_समयout(&wl->assoc_करोne, HZ * 4);/*FIXME*/

	अगर (!rc) अणु
		/* समयouted.  Maybe key or cyrpt mode is wrong */
		pr_info("%s: connect timeout\n", __func__);
		cmd = gelic_eurus_sync_cmd(wl, GELIC_EURUS_CMD_DISASSOC,
					   शून्य, 0);
		kमुक्त(cmd);
		wl->assoc_stat = GELIC_WL_ASSOC_STAT_DISCONN;
		gelic_wl_send_iwap_event(wl, शून्य);
		ret = -ENXIO;
	पूर्ण अन्यथा अणु
		wl->assoc_stat = GELIC_WL_ASSOC_STAT_ASSOCIATED;
		/* copy bssid */
		स_नकल(wl->active_bssid, &bss->hwinfo->bssid[2], ETH_ALEN);

		/* send connect event */
		gelic_wl_send_iwap_event(wl, wl->active_bssid);
		pr_info("%s: connected\n", __func__);
	पूर्ण
out:
	मुक्त_page((अचिन्हित दीर्घ)common);
	pr_debug("%s: ->\n", __func__);
	वापस ret;
पूर्ण

/*
 * connected event
 */
अटल व्योम gelic_wl_connected_event(काष्ठा gelic_wl_info *wl,
				     u64 event)
अणु
	u64 desired_event = 0;

	चयन (wl->wpa_level) अणु
	हाल GELIC_WL_WPA_LEVEL_NONE:
		desired_event = GELIC_LV1_WL_EVENT_CONNECTED;
		अवरोध;
	हाल GELIC_WL_WPA_LEVEL_WPA:
	हाल GELIC_WL_WPA_LEVEL_WPA2:
		desired_event = GELIC_LV1_WL_EVENT_WPA_CONNECTED;
		अवरोध;
	पूर्ण

	अगर (desired_event == event) अणु
		pr_debug("%s: completed\n", __func__);
		complete(&wl->assoc_करोne);
		netअगर_carrier_on(port_to_netdev(wl_port(wl)));
	पूर्ण अन्यथा
		pr_debug("%s: event %#llx under wpa\n",
				 __func__, event);
पूर्ण

/*
 * disconnect event
 */
अटल व्योम gelic_wl_disconnect_event(काष्ठा gelic_wl_info *wl,
				      u64 event)
अणु
	काष्ठा gelic_eurus_cmd *cmd;
	पूर्णांक lock;

	/*
	 * If we fall here in the middle of association,
	 * associate_bss() should be रुकोing क्रम complation of
	 * wl->assoc_करोne.
	 * As it रुकोs with समयout, just leave assoc_करोne
	 * uncompleted, then it terminates with समयout
	 */
	अगर (!mutex_trylock(&wl->assoc_stat_lock)) अणु
		pr_debug("%s: already locked\n", __func__);
		lock = 0;
	पूर्ण अन्यथा अणु
		pr_debug("%s: obtain lock\n", __func__);
		lock = 1;
	पूर्ण

	cmd = gelic_eurus_sync_cmd(wl, GELIC_EURUS_CMD_DISASSOC, शून्य, 0);
	kमुक्त(cmd);

	/* send disconnected event to the supplicant */
	अगर (wl->assoc_stat == GELIC_WL_ASSOC_STAT_ASSOCIATED)
		gelic_wl_send_iwap_event(wl, शून्य);

	wl->assoc_stat = GELIC_WL_ASSOC_STAT_DISCONN;
	netअगर_carrier_off(port_to_netdev(wl_port(wl)));

	अगर (lock)
		mutex_unlock(&wl->assoc_stat_lock);
पूर्ण
/*
 * event worker
 */
#अगर_घोषित DEBUG
अटल स्थिर अक्षर *eventstr(क्रमागत gelic_lv1_wl_event event)
अणु
	अटल अक्षर buf[32];
	अक्षर *ret;
	अगर (event & GELIC_LV1_WL_EVENT_DEVICE_READY)
		ret = "EURUS_READY";
	अन्यथा अगर (event & GELIC_LV1_WL_EVENT_SCAN_COMPLETED)
		ret = "SCAN_COMPLETED";
	अन्यथा अगर (event & GELIC_LV1_WL_EVENT_DEAUTH)
		ret = "DEAUTH";
	अन्यथा अगर (event & GELIC_LV1_WL_EVENT_BEACON_LOST)
		ret = "BEACON_LOST";
	अन्यथा अगर (event & GELIC_LV1_WL_EVENT_CONNECTED)
		ret = "CONNECTED";
	अन्यथा अगर (event & GELIC_LV1_WL_EVENT_WPA_CONNECTED)
		ret = "WPA_CONNECTED";
	अन्यथा अगर (event & GELIC_LV1_WL_EVENT_WPA_ERROR)
		ret = "WPA_ERROR";
	अन्यथा अणु
		प्र_लिखो(buf, "Unknown(%#x)", event);
		ret = buf;
	पूर्ण
	वापस ret;
पूर्ण
#अन्यथा
अटल स्थिर अक्षर *eventstr(क्रमागत gelic_lv1_wl_event event)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर
अटल व्योम gelic_wl_event_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gelic_wl_info *wl;
	काष्ठा gelic_port *port;
	u64 event, पंचांगp;
	पूर्णांक status;

	pr_debug("%s:start\n", __func__);
	wl = container_of(work, काष्ठा gelic_wl_info, event_work.work);
	port = wl_port(wl);
	जबतक (1) अणु
		status = lv1_net_control(bus_id(port->card), dev_id(port->card),
					 GELIC_LV1_GET_WLAN_EVENT, 0, 0, 0,
					 &event, &पंचांगp);
		अगर (status) अणु
			अगर (status != LV1_NO_ENTRY)
				pr_debug("%s:wlan event failed %d\n",
					 __func__, status);
			/* got all events */
			pr_debug("%s:end\n", __func__);
			वापस;
		पूर्ण
		pr_debug("%s: event=%s\n", __func__, eventstr(event));
		चयन (event) अणु
		हाल GELIC_LV1_WL_EVENT_SCAN_COMPLETED:
			gelic_wl_scan_complete_event(wl);
			अवरोध;
		हाल GELIC_LV1_WL_EVENT_BEACON_LOST:
		हाल GELIC_LV1_WL_EVENT_DEAUTH:
			gelic_wl_disconnect_event(wl, event);
			अवरोध;
		हाल GELIC_LV1_WL_EVENT_CONNECTED:
		हाल GELIC_LV1_WL_EVENT_WPA_CONNECTED:
			gelic_wl_connected_event(wl, event);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण /* जबतक */
पूर्ण
/*
 * association worker
 */
अटल व्योम gelic_wl_assoc_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gelic_wl_info *wl;

	काष्ठा gelic_wl_scan_info *best_bss;
	पूर्णांक ret;
	अचिन्हित दीर्घ irqflag;
	u8 *essid;
	माप_प्रकार essid_len;

	wl = container_of(work, काष्ठा gelic_wl_info, assoc_work.work);

	mutex_lock(&wl->assoc_stat_lock);

	अगर (wl->assoc_stat != GELIC_WL_ASSOC_STAT_DISCONN)
		जाओ out;

	spin_lock_irqsave(&wl->lock, irqflag);
	अगर (test_bit(GELIC_WL_STAT_ESSID_SET, &wl->stat)) अणु
		pr_debug("%s: assoc ESSID configured %s\n", __func__,
			 wl->essid);
		essid = wl->essid;
		essid_len = wl->essid_len;
	पूर्ण अन्यथा अणु
		essid = शून्य;
		essid_len = 0;
	पूर्ण
	spin_unlock_irqrestore(&wl->lock, irqflag);

	ret = gelic_wl_start_scan(wl, 0, essid, essid_len);
	अगर (ret == -ERESTARTSYS) अणु
		pr_debug("%s: scan start failed association\n", __func__);
		schedule_delayed_work(&wl->assoc_work, HZ/10); /*FIXME*/
		जाओ out;
	पूर्ण अन्यथा अगर (ret) अणु
		pr_info("%s: scan prerequisite failed\n", __func__);
		जाओ out;
	पूर्ण

	/*
	 * Wait क्रम bss scan completion
	 * If we have scan list alपढ़ोy, gelic_wl_start_scan()
	 * वापसs OK and उठाओs the complete.  Thus,
	 * it's ok to रुको unconditionally here
	 */
	रुको_क्रम_completion(&wl->scan_करोne);

	pr_debug("%s: scan done\n", __func__);
	mutex_lock(&wl->scan_lock);
	अगर (wl->scan_stat != GELIC_WL_SCAN_STAT_GOT_LIST) अणु
		gelic_wl_send_iwap_event(wl, शून्य);
		pr_info("%s: no scan list. association failed\n", __func__);
		जाओ scan_lock_out;
	पूर्ण

	/* find best matching bss */
	best_bss = gelic_wl_find_best_bss(wl);
	अगर (!best_bss) अणु
		gelic_wl_send_iwap_event(wl, शून्य);
		pr_info("%s: no bss matched. association failed\n", __func__);
		जाओ scan_lock_out;
	पूर्ण

	/* ok, करो association */
	ret = gelic_wl_associate_bss(wl, best_bss);
	अगर (ret)
		pr_info("%s: association failed %d\n", __func__, ret);
scan_lock_out:
	mutex_unlock(&wl->scan_lock);
out:
	mutex_unlock(&wl->assoc_stat_lock);
पूर्ण
/*
 * Interrupt handler
 * Called from the ethernet पूर्णांकerrupt handler
 * Processes wireless specअगरic भव पूर्णांकerrupts only
 */
व्योम gelic_wl_पूर्णांकerrupt(काष्ठा net_device *netdev, u64 status)
अणु
	काष्ठा gelic_wl_info *wl = port_wl(netdev_priv(netdev));

	अगर (status & GELIC_CARD_WLAN_COMMAND_COMPLETED) अणु
		pr_debug("%s:cmd complete\n", __func__);
		complete(&wl->cmd_करोne_पूर्णांकr);
	पूर्ण

	अगर (status & GELIC_CARD_WLAN_EVENT_RECEIVED) अणु
		pr_debug("%s:event received\n", __func__);
		queue_delayed_work(wl->event_queue, &wl->event_work, 0);
	पूर्ण
पूर्ण

/*
 * driver helpers
 */
अटल स्थिर iw_handler gelic_wl_wext_handler[] =
अणु
	IW_HANDLER(SIOCGIWNAME, gelic_wl_get_name),
	IW_HANDLER(SIOCGIWRANGE, gelic_wl_get_range),
	IW_HANDLER(SIOCSIWSCAN, gelic_wl_set_scan),
	IW_HANDLER(SIOCGIWSCAN, gelic_wl_get_scan),
	IW_HANDLER(SIOCSIWAUTH, gelic_wl_set_auth),
	IW_HANDLER(SIOCGIWAUTH, gelic_wl_get_auth),
	IW_HANDLER(SIOCSIWESSID, gelic_wl_set_essid),
	IW_HANDLER(SIOCGIWESSID, gelic_wl_get_essid),
	IW_HANDLER(SIOCSIWENCODE, gelic_wl_set_encode),
	IW_HANDLER(SIOCGIWENCODE, gelic_wl_get_encode),
	IW_HANDLER(SIOCSIWAP, gelic_wl_set_ap),
	IW_HANDLER(SIOCGIWAP, gelic_wl_get_ap),
	IW_HANDLER(SIOCSIWENCODEEXT, gelic_wl_set_encodeext),
	IW_HANDLER(SIOCGIWENCODEEXT, gelic_wl_get_encodeext),
	IW_HANDLER(SIOCSIWMODE, gelic_wl_set_mode),
	IW_HANDLER(SIOCGIWMODE, gelic_wl_get_mode),
	IW_HANDLER(SIOCGIWNICKN, gelic_wl_get_nick),
पूर्ण;

अटल स्थिर काष्ठा iw_handler_def gelic_wl_wext_handler_def = अणु
	.num_standard		= ARRAY_SIZE(gelic_wl_wext_handler),
	.standard		= gelic_wl_wext_handler,
	.get_wireless_stats	= gelic_wl_get_wireless_stats,
पूर्ण;

अटल काष्ठा net_device *gelic_wl_alloc(काष्ठा gelic_card *card)
अणु
	काष्ठा net_device *netdev;
	काष्ठा gelic_port *port;
	काष्ठा gelic_wl_info *wl;
	अचिन्हित पूर्णांक i;

	pr_debug("%s:start\n", __func__);
	netdev = alloc_etherdev(माप(काष्ठा gelic_port) +
				माप(काष्ठा gelic_wl_info));
	pr_debug("%s: netdev =%p card=%p\n", __func__, netdev, card);
	अगर (!netdev)
		वापस शून्य;

	म_नकल(netdev->name, "wlan%d");

	port = netdev_priv(netdev);
	port->netdev = netdev;
	port->card = card;
	port->type = GELIC_PORT_WIRELESS;

	wl = port_wl(port);
	pr_debug("%s: wl=%p port=%p\n", __func__, wl, port);

	/* allocate scan list */
	wl->networks = kसुस्मृति(GELIC_WL_BSS_MAX_ENT,
			       माप(काष्ठा gelic_wl_scan_info),
			       GFP_KERNEL);

	अगर (!wl->networks)
		जाओ fail_bss;

	wl->eurus_cmd_queue = create_singlethपढ़ो_workqueue("gelic_cmd");
	अगर (!wl->eurus_cmd_queue)
		जाओ fail_cmd_workqueue;

	wl->event_queue = create_singlethपढ़ो_workqueue("gelic_event");
	अगर (!wl->event_queue)
		जाओ fail_event_workqueue;

	INIT_LIST_HEAD(&wl->network_मुक्त_list);
	INIT_LIST_HEAD(&wl->network_list);
	क्रम (i = 0; i < GELIC_WL_BSS_MAX_ENT; i++)
		list_add_tail(&wl->networks[i].list,
			      &wl->network_मुक्त_list);
	init_completion(&wl->cmd_करोne_पूर्णांकr);

	INIT_DELAYED_WORK(&wl->event_work, gelic_wl_event_worker);
	INIT_DELAYED_WORK(&wl->assoc_work, gelic_wl_assoc_worker);
	mutex_init(&wl->scan_lock);
	mutex_init(&wl->assoc_stat_lock);

	init_completion(&wl->scan_करोne);
	/* क्रम the हाल that no scan request is issued and stop() is called */
	complete(&wl->scan_करोne);

	spin_lock_init(&wl->lock);

	wl->scan_age = 5*HZ; /* FIXME */

	/* buffer क्रम receiving scanned list etc */
	BUILD_BUG_ON(PAGE_SIZE <
		     माप(काष्ठा gelic_eurus_scan_info) *
		     GELIC_EURUS_MAX_SCAN);
	pr_debug("%s:end\n", __func__);
	वापस netdev;

fail_event_workqueue:
	destroy_workqueue(wl->eurus_cmd_queue);
fail_cmd_workqueue:
	kमुक्त(wl->networks);
fail_bss:
	मुक्त_netdev(netdev);
	pr_debug("%s:end error\n", __func__);
	वापस शून्य;

पूर्ण

अटल व्योम gelic_wl_मुक्त(काष्ठा gelic_wl_info *wl)
अणु
	काष्ठा gelic_wl_scan_info *scan_info;
	अचिन्हित पूर्णांक i;

	pr_debug("%s: <-\n", __func__);

	pr_debug("%s: destroy queues\n", __func__);
	destroy_workqueue(wl->eurus_cmd_queue);
	destroy_workqueue(wl->event_queue);

	scan_info = wl->networks;
	क्रम (i = 0; i < GELIC_WL_BSS_MAX_ENT; i++, scan_info++)
		kमुक्त(scan_info->hwinfo);
	kमुक्त(wl->networks);

	मुक्त_netdev(port_to_netdev(wl_port(wl)));

	pr_debug("%s: ->\n", __func__);
पूर्ण

अटल पूर्णांक gelic_wl_try_associate(काष्ठा net_device *netdev)
अणु
	काष्ठा gelic_wl_info *wl = port_wl(netdev_priv(netdev));
	पूर्णांक ret = -1;
	अचिन्हित पूर्णांक i;

	pr_debug("%s: <-\n", __func__);

	/* check स्थिरraits क्रम start association */
	/* क्रम no access restriction AP */
	अगर (wl->group_cipher_method == GELIC_WL_CIPHER_NONE) अणु
		अगर (test_bit(GELIC_WL_STAT_CONFIGURED,
			     &wl->stat))
			जाओ करो_associate;
		अन्यथा अणु
			pr_debug("%s: no wep, not configured\n", __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	/* क्रम WEP, one of four keys should be set */
	अगर (wl->group_cipher_method == GELIC_WL_CIPHER_WEP) अणु
		/* one of keys set */
		क्रम (i = 0; i < GELIC_WEP_KEYS; i++) अणु
			अगर (test_bit(i, &wl->key_enabled))
			    जाओ करो_associate;
		पूर्ण
		pr_debug("%s: WEP, but no key specified\n", __func__);
		वापस ret;
	पूर्ण

	/* क्रम WPA[2], psk should be set */
	अगर ((wl->group_cipher_method == GELIC_WL_CIPHER_TKIP) ||
	    (wl->group_cipher_method == GELIC_WL_CIPHER_AES)) अणु
		अगर (test_bit(GELIC_WL_STAT_WPA_PSK_SET,
			     &wl->stat))
			जाओ करो_associate;
		अन्यथा अणु
			pr_debug("%s: AES/TKIP, but PSK not configured\n",
				 __func__);
			वापस ret;
		पूर्ण
	पूर्ण

करो_associate:
	ret = schedule_delayed_work(&wl->assoc_work, 0);
	pr_debug("%s: start association work %d\n", __func__, ret);
	वापस ret;
पूर्ण

/*
 * netdev handlers
 */
अटल पूर्णांक gelic_wl_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा gelic_card *card = netdev_card(netdev);

	pr_debug("%s:->%p\n", __func__, netdev);

	gelic_card_up(card);

	/* try to associate */
	gelic_wl_try_associate(netdev);

	netअगर_start_queue(netdev);

	pr_debug("%s:<-\n", __func__);
	वापस 0;
पूर्ण

/*
 * reset state machine
 */
अटल पूर्णांक gelic_wl_reset_state(काष्ठा gelic_wl_info *wl)
अणु
	काष्ठा gelic_wl_scan_info *target;
	काष्ठा gelic_wl_scan_info *पंचांगp;

	/* empty scan list */
	list_क्रम_each_entry_safe(target, पंचांगp, &wl->network_list, list) अणु
		list_move_tail(&target->list, &wl->network_मुक्त_list);
	पूर्ण
	wl->scan_stat = GELIC_WL_SCAN_STAT_INIT;

	/* clear configuration */
	wl->auth_method = GELIC_EURUS_AUTH_OPEN;
	wl->group_cipher_method = GELIC_WL_CIPHER_NONE;
	wl->pairwise_cipher_method = GELIC_WL_CIPHER_NONE;
	wl->wpa_level = GELIC_WL_WPA_LEVEL_NONE;

	wl->key_enabled = 0;
	wl->current_key = 0;

	wl->psk_type = GELIC_EURUS_WPA_PSK_PASSPHRASE;
	wl->psk_len = 0;

	wl->essid_len = 0;
	स_रखो(wl->essid, 0, माप(wl->essid));
	स_रखो(wl->bssid, 0, माप(wl->bssid));
	स_रखो(wl->active_bssid, 0, माप(wl->active_bssid));

	wl->assoc_stat = GELIC_WL_ASSOC_STAT_DISCONN;

	स_रखो(&wl->iwstat, 0, माप(wl->iwstat));
	/* all status bit clear */
	wl->stat = 0;
	वापस 0;
पूर्ण

/*
 * Tell eurus to terminate association
 */
अटल व्योम gelic_wl_disconnect(काष्ठा net_device *netdev)
अणु
	काष्ठा gelic_port *port = netdev_priv(netdev);
	काष्ठा gelic_wl_info *wl = port_wl(port);
	काष्ठा gelic_eurus_cmd *cmd;

	/*
	 * If scann process is running on chip,
	 * further requests will be rejected
	 */
	अगर (wl->scan_stat == GELIC_WL_SCAN_STAT_SCANNING)
		रुको_क्रम_completion_समयout(&wl->scan_करोne, HZ);

	cmd = gelic_eurus_sync_cmd(wl, GELIC_EURUS_CMD_DISASSOC, शून्य, 0);
	kमुक्त(cmd);
	gelic_wl_send_iwap_event(wl, शून्य);
पूर्ण;

अटल पूर्णांक gelic_wl_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा gelic_port *port = netdev_priv(netdev);
	काष्ठा gelic_wl_info *wl = port_wl(port);
	काष्ठा gelic_card *card = netdev_card(netdev);

	pr_debug("%s:<-\n", __func__);

	/*
	 * Cancel pending association work.
	 * event work can run after netdev करोwn
	 */
	cancel_delayed_work(&wl->assoc_work);

	अगर (wl->assoc_stat == GELIC_WL_ASSOC_STAT_ASSOCIATED)
		gelic_wl_disconnect(netdev);

	/* reset our state machine */
	gelic_wl_reset_state(wl);

	netअगर_stop_queue(netdev);

	gelic_card_करोwn(card);

	pr_debug("%s:->\n", __func__);
	वापस 0;
पूर्ण

/* -- */

अटल स्थिर काष्ठा net_device_ops gelic_wl_netdevice_ops = अणु
	.nकरो_खोलो = gelic_wl_खोलो,
	.nकरो_stop = gelic_wl_stop,
	.nकरो_start_xmit = gelic_net_xmit,
	.nकरो_set_rx_mode = gelic_net_set_multi,
	.nकरो_tx_समयout = gelic_net_tx_समयout,
	.nकरो_set_mac_address = eth_mac_addr,
	.nकरो_validate_addr = eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = gelic_net_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops gelic_wl_ethtool_ops = अणु
	.get_drvinfo	= gelic_net_get_drvinfo,
	.get_link	= gelic_wl_get_link,
पूर्ण;

अटल व्योम gelic_wl_setup_netdev_ops(काष्ठा net_device *netdev)
अणु
	काष्ठा gelic_wl_info *wl;
	wl = port_wl(netdev_priv(netdev));
	BUG_ON(!wl);
	netdev->watchकरोg_समयo = GELIC_NET_WATCHDOG_TIMEOUT;

	netdev->ethtool_ops = &gelic_wl_ethtool_ops;
	netdev->netdev_ops = &gelic_wl_netdevice_ops;
	netdev->wireless_data = &wl->wireless_data;
	netdev->wireless_handlers = &gelic_wl_wext_handler_def;
पूर्ण

/*
 * driver probe/हटाओ
 */
पूर्णांक gelic_wl_driver_probe(काष्ठा gelic_card *card)
अणु
	पूर्णांक ret;
	काष्ठा net_device *netdev;

	pr_debug("%s:start\n", __func__);

	अगर (ps3_compare_firmware_version(1, 6, 0) < 0)
		वापस 0;
	अगर (!card->vlan[GELIC_PORT_WIRELESS].tx)
		वापस 0;

	/* alloc netdevice क्रम wireless */
	netdev = gelic_wl_alloc(card);
	अगर (!netdev)
		वापस -ENOMEM;

	/* setup net_device काष्ठाure */
	SET_NETDEV_DEV(netdev, &card->dev->core);
	gelic_wl_setup_netdev_ops(netdev);

	/* setup some of net_device and रेजिस्टर it */
	ret = gelic_net_setup_netdev(netdev, card);
	अगर (ret)
		जाओ fail_setup;
	card->netdev[GELIC_PORT_WIRELESS] = netdev;

	/* add enable wireless पूर्णांकerrupt */
	card->irq_mask |= GELIC_CARD_WLAN_EVENT_RECEIVED |
		GELIC_CARD_WLAN_COMMAND_COMPLETED;
	/* to allow wireless commands जबतक both पूर्णांकerfaces are करोwn */
	gelic_card_set_irq_mask(card, GELIC_CARD_WLAN_EVENT_RECEIVED |
				GELIC_CARD_WLAN_COMMAND_COMPLETED);
	pr_debug("%s:end\n", __func__);
	वापस 0;

fail_setup:
	gelic_wl_मुक्त(port_wl(netdev_port(netdev)));

	वापस ret;
पूर्ण

पूर्णांक gelic_wl_driver_हटाओ(काष्ठा gelic_card *card)
अणु
	काष्ठा gelic_wl_info *wl;
	काष्ठा net_device *netdev;

	pr_debug("%s:start\n", __func__);

	अगर (ps3_compare_firmware_version(1, 6, 0) < 0)
		वापस 0;
	अगर (!card->vlan[GELIC_PORT_WIRELESS].tx)
		वापस 0;

	netdev = card->netdev[GELIC_PORT_WIRELESS];
	wl = port_wl(netdev_priv(netdev));

	/* अगर the पूर्णांकerface was not up, but associated */
	अगर (wl->assoc_stat == GELIC_WL_ASSOC_STAT_ASSOCIATED)
		gelic_wl_disconnect(netdev);

	complete(&wl->cmd_करोne_पूर्णांकr);

	/* cancel all work queue */
	cancel_delayed_work(&wl->assoc_work);
	cancel_delayed_work(&wl->event_work);
	flush_workqueue(wl->eurus_cmd_queue);
	flush_workqueue(wl->event_queue);

	unरेजिस्टर_netdev(netdev);

	/* disable wireless पूर्णांकerrupt */
	pr_debug("%s: disable intr\n", __func__);
	card->irq_mask &= ~(GELIC_CARD_WLAN_EVENT_RECEIVED |
			    GELIC_CARD_WLAN_COMMAND_COMPLETED);
	/* मुक्त bss list, netdev*/
	gelic_wl_मुक्त(wl);
	pr_debug("%s:end\n", __func__);
	वापस 0;
पूर्ण
