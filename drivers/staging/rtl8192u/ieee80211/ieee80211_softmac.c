<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* IEEE 802.11 SoftMAC layer
 * Copyright (c) 2005 Andrea Merello <andrea.merello@gmail.com>
 *
 * Mostly extracted from the rtl8180-sa2400 driver क्रम the
 * in-kernel generic ieee802.11 stack.
 *
 * Few lines might be stolen from other part of the ieee80211
 * stack. Copyright who own it's copyright
 *
 * WPA code stolen from the ipw2200 driver.
 * Copyright who own it's copyright.
 */
#समावेश "ieee80211.h"

#समावेश <linux/अक्रमom.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/etherdevice.h>

#समावेश "dot11d.h"

लघु ieee80211_is_54g(स्थिर काष्ठा ieee80211_network *net)
अणु
	वापस (net->rates_ex_len > 0) || (net->rates_len > 4);
पूर्ण
EXPORT_SYMBOL(ieee80211_is_54g);

लघु ieee80211_is_लघुslot(स्थिर काष्ठा ieee80211_network *net)
अणु
	वापस net->capability & WLAN_CAPABILITY_SHORT_SLOT;
पूर्ण
EXPORT_SYMBOL(ieee80211_is_लघुslot);

/* वापसs the total length needed क्रम pleacing the RATE MFIE
 * tag and the EXTENDED RATE MFIE tag अगर needed.
 * It encludes two bytes per tag क्रम the tag itself and its len
 */
अटल अचिन्हित पूर्णांक ieee80211_MFIE_rate_len(काष्ठा ieee80211_device *ieee)
अणु
	अचिन्हित पूर्णांक rate_len = 0;

	अगर (ieee->modulation & IEEE80211_CCK_MODULATION)
		rate_len = IEEE80211_CCK_RATE_LEN + 2;

	अगर (ieee->modulation & IEEE80211_OFDM_MODULATION)
		rate_len += IEEE80211_OFDM_RATE_LEN + 2;

	वापस rate_len;
पूर्ण

/* pleace the MFIE rate, tag to the memory (द्विगुन) poined.
 * Then it updates the poपूर्णांकer so that
 * it poपूर्णांकs after the new MFIE tag added.
 */
अटल व्योम ieee80211_MFIE_Brate(काष्ठा ieee80211_device *ieee, u8 **tag_p)
अणु
	u8 *tag = *tag_p;

	अगर (ieee->modulation & IEEE80211_CCK_MODULATION) अणु
		*tag++ = MFIE_TYPE_RATES;
		*tag++ = 4;
		*tag++ = IEEE80211_BASIC_RATE_MASK | IEEE80211_CCK_RATE_1MB;
		*tag++ = IEEE80211_BASIC_RATE_MASK | IEEE80211_CCK_RATE_2MB;
		*tag++ = IEEE80211_BASIC_RATE_MASK | IEEE80211_CCK_RATE_5MB;
		*tag++ = IEEE80211_BASIC_RATE_MASK | IEEE80211_CCK_RATE_11MB;
	पूर्ण

	/* We may add an option क्रम custom rates that specअगरic HW might support */
	*tag_p = tag;
पूर्ण

अटल व्योम ieee80211_MFIE_Grate(काष्ठा ieee80211_device *ieee, u8 **tag_p)
अणु
	u8 *tag = *tag_p;

	अगर (ieee->modulation & IEEE80211_OFDM_MODULATION) अणु
		*tag++ = MFIE_TYPE_RATES_EX;
		*tag++ = 8;
		*tag++ = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_6MB;
		*tag++ = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_9MB;
		*tag++ = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_12MB;
		*tag++ = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_18MB;
		*tag++ = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_24MB;
		*tag++ = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_36MB;
		*tag++ = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_48MB;
		*tag++ = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_54MB;
	पूर्ण

	/* We may add an option क्रम custom rates that specअगरic HW might support */
	*tag_p = tag;
पूर्ण

अटल व्योम ieee80211_WMM_Info(काष्ठा ieee80211_device *ieee, u8 **tag_p)
अणु
	u8 *tag = *tag_p;

	*tag++ = MFIE_TYPE_GENERIC; /* 0 */
	*tag++ = 7;
	*tag++ = 0x00;
	*tag++ = 0x50;
	*tag++ = 0xf2;
	*tag++ = 0x02;	/* 5 */
	*tag++ = 0x00;
	*tag++ = 0x01;
#अगर_घोषित SUPPORT_USPD
	अगर (ieee->current_network.wmm_info & 0x80)
		*tag++ = 0x0f | MAX_SP_Len;
	अन्यथा
		*tag++ = MAX_SP_Len;
#अन्यथा
	*tag++ = MAX_SP_Len;
#पूर्ण_अगर
	*tag_p = tag;
पूर्ण

#अगर_घोषित THOMAS_TURBO
अटल व्योम ieee80211_TURBO_Info(काष्ठा ieee80211_device *ieee, u8 **tag_p)
अणु
	u8 *tag = *tag_p;

	*tag++ = MFIE_TYPE_GENERIC; /* 0 */
	*tag++ = 7;
	*tag++ = 0x00;
	*tag++ = 0xe0;
	*tag++ = 0x4c;
	*tag++ = 0x01;	/* 5 */
	*tag++ = 0x02;
	*tag++ = 0x11;
	*tag++ = 0x00;

	*tag_p = tag;
	netdev_alert(ieee->dev, "This is enable turbo mode IE process\n");
पूर्ण
#पूर्ण_अगर

अटल व्योम enqueue_mgmt(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb)
अणु
	पूर्णांक nh;

	nh = (ieee->mgmt_queue_head + 1) % MGMT_QUEUE_NUM;

/*
 * अगर the queue is full but we have newer frames then
 * just overग_लिखोs the oldest.
 *
 * अगर (nh == ieee->mgmt_queue_tail)
 *		वापस -1;
 */
	ieee->mgmt_queue_head = nh;
	ieee->mgmt_queue_ring[nh] = skb;

	//वापस 0;
पूर्ण

अटल काष्ठा sk_buff *dequeue_mgmt(काष्ठा ieee80211_device *ieee)
अणु
	काष्ठा sk_buff *ret;

	अगर (ieee->mgmt_queue_tail == ieee->mgmt_queue_head)
		वापस शून्य;

	ret = ieee->mgmt_queue_ring[ieee->mgmt_queue_tail];

	ieee->mgmt_queue_tail =
		(ieee->mgmt_queue_tail + 1) % MGMT_QUEUE_NUM;

	वापस ret;
पूर्ण

अटल व्योम init_mgmt_queue(काष्ठा ieee80211_device *ieee)
अणु
	ieee->mgmt_queue_tail = ieee->mgmt_queue_head = 0;
पूर्ण

अटल u8 MgntQuery_MgntFrameTxRate(काष्ठा ieee80211_device *ieee)
अणु
	PRT_HIGH_THROUGHPUT      pHTInfo = ieee->pHTInfo;
	u8 rate;

	/* 2008/01/25 MH For broadcom, MGNT frame set as OFDM 6M. */
	अगर (pHTInfo->IOTAction & HT_IOT_ACT_MGNT_USE_CCK_6M)
		rate = 0x0c;
	अन्यथा
		rate = ieee->basic_rate & 0x7f;

	अगर (rate == 0) अणु
		/* 2005.01.26, by rcnjko. */
		अगर (ieee->mode == IEEE_A ||
		    ieee->mode == IEEE_N_5G ||
		    (ieee->mode == IEEE_N_24G && !pHTInfo->bCurSuppCCK))
			rate = 0x0c;
		अन्यथा
			rate = 0x02;
	पूर्ण

	/*
	// Data rate of ProbeReq is alपढ़ोy decided. Annie, 2005-03-31
	अगर( pMgntInfo->bScanInProgress || (pMgntInfo->bDualModeScanStep!=0) ) अणु
	अगर(pMgntInfo->करोt11CurrentWirelessMode==WIRELESS_MODE_A)
	rate = 0x0c;
	अन्यथा
	rate = 0x02;
	पूर्ण
	 */
	वापस rate;
पूर्ण

व्योम ieee80211_sta_wakeup(काष्ठा ieee80211_device *ieee, लघु nl);

अंतरभूत व्योम sofपंचांगac_mgmt_xmit(काष्ठा sk_buff *skb, काष्ठा ieee80211_device *ieee)
अणु
	अचिन्हित दीर्घ flags;
	लघु single = ieee->sofपंचांगac_features & IEEE_SOFTMAC_SINGLE_QUEUE;
	काष्ठा rtl_80211_hdr_3addr  *header =
		(काष्ठा rtl_80211_hdr_3addr  *)skb->data;

	काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);

	spin_lock_irqsave(&ieee->lock, flags);

	/* called with 2nd param 0, no mgmt lock required */
	ieee80211_sta_wakeup(ieee, 0);

	tcb_desc->queue_index = MGNT_QUEUE;
	tcb_desc->data_rate = MgntQuery_MgntFrameTxRate(ieee);
	tcb_desc->RATRIndex = 7;
	tcb_desc->bTxDisableRateFallBack = 1;
	tcb_desc->bTxUseDriverAssingedRate = 1;

	अगर (single) अणु
		अगर (ieee->queue_stop) अणु
			enqueue_mgmt(ieee, skb);
		पूर्ण अन्यथा अणु
			header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

			अगर (ieee->seq_ctrl[0] == 0xFFF)
				ieee->seq_ctrl[0] = 0;
			अन्यथा
				ieee->seq_ctrl[0]++;

			/* aव्योम watchकरोg triggers */
			netअगर_trans_update(ieee->dev);
			ieee->sofपंचांगac_data_hard_start_xmit(skb, ieee->dev, ieee->basic_rate);
			//dev_kमुक्त_skb_any(skb);//edit by thomas
		पूर्ण

		spin_unlock_irqrestore(&ieee->lock, flags);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&ieee->lock, flags);
		spin_lock_irqsave(&ieee->mgmt_tx_lock, flags);

		header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

		अगर (ieee->seq_ctrl[0] == 0xFFF)
			ieee->seq_ctrl[0] = 0;
		अन्यथा
			ieee->seq_ctrl[0]++;

		/* check whether the managed packet queued greater than 5 */
		अगर (!ieee->check_nic_enough_desc(ieee->dev, tcb_desc->queue_index) || \
		    (skb_queue_len(&ieee->skb_रुकोQ[tcb_desc->queue_index]) != 0) || \
		    (ieee->queue_stop)) अणु
			/* insert the skb packet to the management queue */
			/* as क्रम the completion function, it करोes not need
			 * to check it any more.
			 * */
			prपूर्णांकk("%s():insert to waitqueue!\n", __func__);
			skb_queue_tail(&ieee->skb_रुकोQ[tcb_desc->queue_index], skb);
		पूर्ण अन्यथा अणु
			ieee->sofपंचांगac_hard_start_xmit(skb, ieee->dev);
			//dev_kमुक्त_skb_any(skb);//edit by thomas
		पूर्ण
		spin_unlock_irqrestore(&ieee->mgmt_tx_lock, flags);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
sofपंचांगac_ps_mgmt_xmit(काष्ठा sk_buff *skb, काष्ठा ieee80211_device *ieee)
अणु
	लघु single = ieee->sofपंचांगac_features & IEEE_SOFTMAC_SINGLE_QUEUE;
	काष्ठा rtl_80211_hdr_3addr  *header =
		(काष्ठा rtl_80211_hdr_3addr  *)skb->data;

	अगर (single) अणु
		header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

		अगर (ieee->seq_ctrl[0] == 0xFFF)
			ieee->seq_ctrl[0] = 0;
		अन्यथा
			ieee->seq_ctrl[0]++;

		/* aव्योम watchकरोg triggers */
		netअगर_trans_update(ieee->dev);
		ieee->sofपंचांगac_data_hard_start_xmit(skb, ieee->dev, ieee->basic_rate);
	पूर्ण अन्यथा अणु
		header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

		अगर (ieee->seq_ctrl[0] == 0xFFF)
			ieee->seq_ctrl[0] = 0;
		अन्यथा
			ieee->seq_ctrl[0]++;

		ieee->sofपंचांगac_hard_start_xmit(skb, ieee->dev);
	पूर्ण
	//dev_kमुक्त_skb_any(skb);//edit by thomas
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *ieee80211_probe_req(काष्ठा ieee80211_device *ieee)
अणु
	अचिन्हित पूर्णांक len, rate_len;
	u8 *tag;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_probe_request *req;

	len = ieee->current_network.ssid_len;

	rate_len = ieee80211_MFIE_rate_len(ieee);

	skb = dev_alloc_skb(माप(काष्ठा ieee80211_probe_request) +
			    2 + len + rate_len + ieee->tx_headroom);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, ieee->tx_headroom);

	req = skb_put(skb, माप(काष्ठा ieee80211_probe_request));
	req->header.frame_ctl = cpu_to_le16(IEEE80211_STYPE_PROBE_REQ);
	req->header.duration_id = 0; /* FIXME: is this OK? */

	eth_broadcast_addr(req->header.addr1);
	स_नकल(req->header.addr2, ieee->dev->dev_addr, ETH_ALEN);
	eth_broadcast_addr(req->header.addr3);

	tag = skb_put(skb, len + 2 + rate_len);

	*tag++ = MFIE_TYPE_SSID;
	*tag++ = len;
	स_नकल(tag, ieee->current_network.ssid, len);
	tag += len;

	ieee80211_MFIE_Brate(ieee, &tag);
	ieee80211_MFIE_Grate(ieee, &tag);
	वापस skb;
पूर्ण

काष्ठा sk_buff *ieee80211_get_beacon_(काष्ठा ieee80211_device *ieee);

अटल व्योम ieee80211_send_beacon(काष्ठा ieee80211_device *ieee)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ieee->ieee_up)
		वापस;
	//अचिन्हित दीर्घ flags;
	skb = ieee80211_get_beacon_(ieee);

	अगर (skb) अणु
		sofपंचांगac_mgmt_xmit(skb, ieee);
		ieee->sofपंचांगac_stats.tx_beacons++;
		//dev_kमुक्त_skb_any(skb);//edit by thomas
	पूर्ण
//	ieee->beacon_समयr.expires = jअगरfies +
//		(MSECS( ieee->current_network.beacon_पूर्णांकerval -5));

	//spin_lock_irqsave(&ieee->beacon_lock,flags);
	अगर (ieee->beacon_txing && ieee->ieee_up) अणु
//		अगर(!समयr_pending(&ieee->beacon_समयr))
//			add_समयr(&ieee->beacon_समयr);
		mod_समयr(&ieee->beacon_समयr,
			  jअगरfies + msecs_to_jअगरfies(ieee->current_network.beacon_पूर्णांकerval - 5));
	पूर्ण
	//spin_unlock_irqrestore(&ieee->beacon_lock,flags);
पूर्ण

अटल व्योम ieee80211_send_beacon_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा ieee80211_device *ieee =
		from_समयr(ieee, t, beacon_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ieee->beacon_lock, flags);
	ieee80211_send_beacon(ieee);
	spin_unlock_irqrestore(&ieee->beacon_lock, flags);
पूर्ण

अटल व्योम ieee80211_send_probe(काष्ठा ieee80211_device *ieee)
अणु
	काष्ठा sk_buff *skb;

	skb = ieee80211_probe_req(ieee);
	अगर (skb) अणु
		sofपंचांगac_mgmt_xmit(skb, ieee);
		ieee->sofपंचांगac_stats.tx_probe_rq++;
		//dev_kमुक्त_skb_any(skb);//edit by thomas
	पूर्ण
पूर्ण

अटल व्योम ieee80211_send_probe_requests(काष्ठा ieee80211_device *ieee)
अणु
	अगर (ieee->active_scan && (ieee->sofपंचांगac_features & IEEE_SOFTMAC_PROBERQ)) अणु
		ieee80211_send_probe(ieee);
		ieee80211_send_probe(ieee);
	पूर्ण
पूर्ण

/* this perक्रमms syncro scan blocking the caller until all channels
 * in the allowed channel map has been checked.
 */
व्योम ieee80211_sofपंचांगac_scan_syncro(काष्ठा ieee80211_device *ieee)
अणु
	लघु ch = 0;
	u8 channel_map[MAX_CHANNEL_NUMBER + 1];

	स_नकल(channel_map, GET_DOT11D_INFO(ieee)->channel_map, MAX_CHANNEL_NUMBER + 1);
	mutex_lock(&ieee->scan_mutex);

	जबतक (1) अणु
		करो अणु
			ch++;
			अगर (ch > MAX_CHANNEL_NUMBER)
				जाओ out; /* scan completed */
		पूर्ण जबतक (!channel_map[ch]);

		/* this function can be called in two situations
		 * 1- We have चयनed to ad-hoc mode and we are
		 *    perक्रमming a complete syncro scan beक्रमe conclude
		 *    there are no पूर्णांकeresting cell and to create a
		 *    new one. In this हाल the link state is
		 *    IEEE80211_NOLINK until we found an पूर्णांकeresting cell.
		 *    If so the ieee8021_new_net, called by the RX path
		 *    will set the state to IEEE80211_LINKED, so we stop
		 *    scanning
		 * 2- We are linked and the root uses run iwlist scan.
		 *    So we चयन to IEEE80211_LINKED_SCANNING to remember
		 *    that we are still logically linked (not पूर्णांकerested in
		 *    new network events, despite क्रम updating the net list,
		 *    but we are temporarly 'unlinked' as the driver shall
		 *    not filter RX frames and the channel is changing.
		 * So the only situation in witch are पूर्णांकerested is to check
		 * अगर the state become LINKED because of the #1 situation
		 */

		अगर (ieee->state == IEEE80211_LINKED)
			जाओ out;
		ieee->set_chan(ieee->dev, ch);
		अगर (channel_map[ch] == 1)
			ieee80211_send_probe_requests(ieee);

		/* this prevent excessive समय रुको when we
		 * need to रुको क्रम a syncro scan to end..
		 */
		अगर (ieee->state >= IEEE80211_LINKED && ieee->sync_scan_hurryup)
			जाओ out;

		msleep_पूर्णांकerruptible(IEEE80211_SOFTMAC_SCAN_TIME);
	पूर्ण
out:
	अगर (ieee->state < IEEE80211_LINKED) अणु
		ieee->actscanning = false;
		mutex_unlock(&ieee->scan_mutex);
	पूर्ण अन्यथा अणु
		ieee->sync_scan_hurryup = 0;
		अगर (IS_DOT11D_ENABLE(ieee))
			करोt11d_scan_complete(ieee);
		mutex_unlock(&ieee->scan_mutex);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ieee80211_sofपंचांगac_scan_syncro);

अटल व्योम ieee80211_sofपंचांगac_scan_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा ieee80211_device *ieee = container_of(dwork, काष्ठा ieee80211_device, sofपंचांगac_scan_wq);
	अटल लघु watchकरोg;
	u8 channel_map[MAX_CHANNEL_NUMBER + 1];

	स_नकल(channel_map, GET_DOT11D_INFO(ieee)->channel_map, MAX_CHANNEL_NUMBER + 1);
	अगर (!ieee->ieee_up)
		वापस;
	mutex_lock(&ieee->scan_mutex);
	करो अणु
		ieee->current_network.channel =
			(ieee->current_network.channel + 1) % MAX_CHANNEL_NUMBER;
		अगर (watchकरोg++ > MAX_CHANNEL_NUMBER) अणु
		//अगर current channel is not in channel map, set to शेष channel.
			अगर (!channel_map[ieee->current_network.channel]) अणु
				ieee->current_network.channel = 6;
				जाओ out; /* no good chans */
			पूर्ण
		पूर्ण
	पूर्ण जबतक (!channel_map[ieee->current_network.channel]);
	अगर (ieee->scanning == 0)
		जाओ out;
	ieee->set_chan(ieee->dev, ieee->current_network.channel);
	अगर (channel_map[ieee->current_network.channel] == 1)
		ieee80211_send_probe_requests(ieee);

	schedule_delayed_work(&ieee->sofपंचांगac_scan_wq, IEEE80211_SOFTMAC_SCAN_TIME);

	mutex_unlock(&ieee->scan_mutex);
	वापस;
out:
	अगर (IS_DOT11D_ENABLE(ieee))
		करोt11d_scan_complete(ieee);
	ieee->actscanning = false;
	watchकरोg = 0;
	ieee->scanning = 0;
	mutex_unlock(&ieee->scan_mutex);
पूर्ण

अटल व्योम ieee80211_beacons_start(काष्ठा ieee80211_device *ieee)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&ieee->beacon_lock, flags);

	ieee->beacon_txing = 1;
	ieee80211_send_beacon(ieee);

	spin_unlock_irqrestore(&ieee->beacon_lock, flags);
पूर्ण

अटल व्योम ieee80211_beacons_stop(काष्ठा ieee80211_device *ieee)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ieee->beacon_lock, flags);

	ieee->beacon_txing = 0;
	del_समयr_sync(&ieee->beacon_समयr);

	spin_unlock_irqrestore(&ieee->beacon_lock, flags);
पूर्ण

व्योम ieee80211_stop_send_beacons(काष्ठा ieee80211_device *ieee)
अणु
	अगर (ieee->stop_send_beacons)
		ieee->stop_send_beacons(ieee->dev);
	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_BEACONS)
		ieee80211_beacons_stop(ieee);
पूर्ण
EXPORT_SYMBOL(ieee80211_stop_send_beacons);

व्योम ieee80211_start_send_beacons(काष्ठा ieee80211_device *ieee)
अणु
	अगर (ieee->start_send_beacons)
		ieee->start_send_beacons(ieee->dev, ieee->basic_rate);
	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_BEACONS)
		ieee80211_beacons_start(ieee);
पूर्ण
EXPORT_SYMBOL(ieee80211_start_send_beacons);

अटल व्योम ieee80211_sofपंचांगac_stop_scan(काष्ठा ieee80211_device *ieee)
अणु
//	अचिन्हित दीर्घ flags;

	//ieee->sync_scan_hurryup = 1;

	mutex_lock(&ieee->scan_mutex);
//	spin_lock_irqsave(&ieee->lock, flags);

	अगर (ieee->scanning == 1) अणु
		ieee->scanning = 0;

		cancel_delayed_work(&ieee->sofपंचांगac_scan_wq);
	पूर्ण

//	spin_unlock_irqrestore(&ieee->lock, flags);
	mutex_unlock(&ieee->scan_mutex);
पूर्ण

व्योम ieee80211_stop_scan(काष्ठा ieee80211_device *ieee)
अणु
	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_SCAN)
		ieee80211_sofपंचांगac_stop_scan(ieee);
	अन्यथा
		ieee->stop_scan(ieee->dev);
पूर्ण
EXPORT_SYMBOL(ieee80211_stop_scan);

/* called with ieee->lock held */
अटल व्योम ieee80211_start_scan(काष्ठा ieee80211_device *ieee)
अणु
	अगर (IS_DOT11D_ENABLE(ieee)) अणु
		अगर (IS_COUNTRY_IE_VALID(ieee))
			RESET_CIE_WATCHDOG(ieee);
	पूर्ण
	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_SCAN) अणु
		अगर (ieee->scanning == 0) अणु
			ieee->scanning = 1;
			schedule_delayed_work(&ieee->sofपंचांगac_scan_wq, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		ieee->start_scan(ieee->dev);
	पूर्ण
पूर्ण

/* called with wx_mutex held */
व्योम ieee80211_start_scan_syncro(काष्ठा ieee80211_device *ieee)
अणु
	अगर (IS_DOT11D_ENABLE(ieee)) अणु
		अगर (IS_COUNTRY_IE_VALID(ieee))
			RESET_CIE_WATCHDOG(ieee);
	पूर्ण
	ieee->sync_scan_hurryup = 0;
	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_SCAN)
		ieee80211_sofपंचांगac_scan_syncro(ieee);
	अन्यथा
		ieee->scan_syncro(ieee->dev);
पूर्ण
EXPORT_SYMBOL(ieee80211_start_scan_syncro);

अटल अंतरभूत काष्ठा sk_buff *
ieee80211_authentication_req(काष्ठा ieee80211_network *beacon,
			     काष्ठा ieee80211_device *ieee, पूर्णांक challengelen)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_authentication *auth;
	पूर्णांक len = माप(काष्ठा ieee80211_authentication) + challengelen + ieee->tx_headroom;

	skb = dev_alloc_skb(len);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, ieee->tx_headroom);
	auth = skb_put(skb, माप(काष्ठा ieee80211_authentication));

	अगर (challengelen)
		auth->header.frame_ctl = cpu_to_le16(IEEE80211_STYPE_AUTH
						     | IEEE80211_FCTL_WEP);
	अन्यथा
		auth->header.frame_ctl = cpu_to_le16(IEEE80211_STYPE_AUTH);

	auth->header.duration_id = cpu_to_le16(0x013a);

	स_नकल(auth->header.addr1, beacon->bssid, ETH_ALEN);
	स_नकल(auth->header.addr2, ieee->dev->dev_addr, ETH_ALEN);
	स_नकल(auth->header.addr3, beacon->bssid, ETH_ALEN);

	//auth->algorithm = ieee->खोलो_wep ? WLAN_AUTH_OPEN : WLAN_AUTH_SHARED_KEY;
	अगर (ieee->auth_mode == 0)
		auth->algorithm = WLAN_AUTH_OPEN;
	अन्यथा अगर (ieee->auth_mode == 1)
		auth->algorithm = cpu_to_le16(WLAN_AUTH_SHARED_KEY);
	अन्यथा अगर (ieee->auth_mode == 2)
		auth->algorithm = WLAN_AUTH_OPEN; /* 0x80; */
	prपूर्णांकk("=================>%s():auth->algorithm is %d\n", __func__, auth->algorithm);
	auth->transaction = cpu_to_le16(ieee->associate_seq);
	ieee->associate_seq++;

	auth->status = cpu_to_le16(WLAN_STATUS_SUCCESS);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *ieee80211_probe_resp(काष्ठा ieee80211_device *ieee, u8 *dest)
अणु
	u8 *tag;
	पूर्णांक beacon_size;
	काष्ठा ieee80211_probe_response *beacon_buf;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक encrypt;
	पूर्णांक atim_len, erp_len;
	काष्ठा ieee80211_crypt_data *crypt;

	अक्षर *ssid = ieee->current_network.ssid;
	पूर्णांक ssid_len = ieee->current_network.ssid_len;
	पूर्णांक rate_len = ieee->current_network.rates_len + 2;
	पूर्णांक rate_ex_len = ieee->current_network.rates_ex_len;
	पूर्णांक wpa_ie_len = ieee->wpa_ie_len;
	u8 erpinfo_content = 0;

	u8 *पंचांगp_ht_cap_buf;
	u8 पंचांगp_ht_cap_len = 0;
	u8 *पंचांगp_ht_info_buf;
	u8 पंचांगp_ht_info_len = 0;
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	u8 *पंचांगp_generic_ie_buf = शून्य;
	u8 पंचांगp_generic_ie_len = 0;

	अगर (rate_ex_len > 0)
		rate_ex_len += 2;

	अगर (ieee->current_network.capability & WLAN_CAPABILITY_IBSS)
		atim_len = 4;
	अन्यथा
		atim_len = 0;

	अगर (ieee80211_is_54g(&ieee->current_network))
		erp_len = 3;
	अन्यथा
		erp_len = 0;

	crypt = ieee->crypt[ieee->tx_keyidx];

	encrypt = ieee->host_encrypt && crypt && crypt->ops &&
		((0 == म_भेद(crypt->ops->name, "WEP") || wpa_ie_len));
	/* HT ralated element */
	पंचांगp_ht_cap_buf = (u8 *)&ieee->pHTInfo->SelfHTCap;
	पंचांगp_ht_cap_len = माप(ieee->pHTInfo->SelfHTCap);
	पंचांगp_ht_info_buf = (u8 *)&ieee->pHTInfo->SelfHTInfo;
	पंचांगp_ht_info_len = माप(ieee->pHTInfo->SelfHTInfo);
	HTConकाष्ठाCapabilityElement(ieee, पंचांगp_ht_cap_buf, &पंचांगp_ht_cap_len, encrypt);
	HTConकाष्ठाInfoElement(ieee, पंचांगp_ht_info_buf, &पंचांगp_ht_info_len, encrypt);

	अगर (pHTInfo->bRegRT2RTAggregation) अणु
		पंचांगp_generic_ie_buf = ieee->pHTInfo->szRT2RTAggBuffer;
		पंचांगp_generic_ie_len = माप(ieee->pHTInfo->szRT2RTAggBuffer);
		HTConकाष्ठाRT2RTAggElement(ieee, पंचांगp_generic_ie_buf, &पंचांगp_generic_ie_len);
	पूर्ण
//	prपूर्णांकk("===============>tmp_ht_cap_len is %d,tmp_ht_info_len is %d, tmp_generic_ie_len is %d\n",पंचांगp_ht_cap_len,पंचांगp_ht_info_len,पंचांगp_generic_ie_len);
	beacon_size = माप(काष्ठा ieee80211_probe_response) + 2
		+ ssid_len
		+ 3 //channel
		+ rate_len
		+ rate_ex_len
		+ atim_len
		+ erp_len
		+ wpa_ie_len
	//	+ पंचांगp_ht_cap_len
	//	+ पंचांगp_ht_info_len
	//	+ पंचांगp_generic_ie_len
//		+ wmm_len+2
		+ ieee->tx_headroom;
	skb = dev_alloc_skb(beacon_size);
	अगर (!skb)
		वापस शून्य;
	skb_reserve(skb, ieee->tx_headroom);
	beacon_buf = skb_put(skb, (beacon_size - ieee->tx_headroom));
	स_नकल(beacon_buf->header.addr1, dest, ETH_ALEN);
	स_नकल(beacon_buf->header.addr2, ieee->dev->dev_addr, ETH_ALEN);
	स_नकल(beacon_buf->header.addr3, ieee->current_network.bssid, ETH_ALEN);

	beacon_buf->header.duration_id = 0; /* FIXME */
	beacon_buf->beacon_पूर्णांकerval =
		cpu_to_le16(ieee->current_network.beacon_पूर्णांकerval);
	beacon_buf->capability =
		cpu_to_le16(ieee->current_network.capability & WLAN_CAPABILITY_IBSS);
	beacon_buf->capability |=
		cpu_to_le16(ieee->current_network.capability & WLAN_CAPABILITY_SHORT_PREAMBLE); /* add लघु preamble here */

	अगर (ieee->लघु_slot && (ieee->current_network.capability & WLAN_CAPABILITY_SHORT_SLOT))
		beacon_buf->capability |= cpu_to_le16(WLAN_CAPABILITY_SHORT_SLOT);

	अगर (encrypt)
		beacon_buf->capability |= cpu_to_le16(WLAN_CAPABILITY_PRIVACY);

	beacon_buf->header.frame_ctl = cpu_to_le16(IEEE80211_STYPE_PROBE_RESP);
	beacon_buf->info_element[0].id = MFIE_TYPE_SSID;
	beacon_buf->info_element[0].len = ssid_len;

	tag = (u8 *)beacon_buf->info_element[0].data;

	स_नकल(tag, ssid, ssid_len);

	tag += ssid_len;

	*(tag++) = MFIE_TYPE_RATES;
	*(tag++) = rate_len - 2;
	स_नकल(tag, ieee->current_network.rates, rate_len - 2);
	tag += rate_len - 2;

	*(tag++) = MFIE_TYPE_DS_SET;
	*(tag++) = 1;
	*(tag++) = ieee->current_network.channel;

	अगर (atim_len) अणु
		*(tag++) = MFIE_TYPE_IBSS_SET;
		*(tag++) = 2;

		put_unaligned_le16(ieee->current_network.atim_winकरोw,
				   tag);
		tag += 2;
	पूर्ण

	अगर (erp_len) अणु
		*(tag++) = MFIE_TYPE_ERP;
		*(tag++) = 1;
		*(tag++) = erpinfo_content;
	पूर्ण
	अगर (rate_ex_len) अणु
		*(tag++) = MFIE_TYPE_RATES_EX;
		*(tag++) = rate_ex_len - 2;
		स_नकल(tag, ieee->current_network.rates_ex, rate_ex_len - 2);
		tag += rate_ex_len - 2;
	पूर्ण

	अगर (wpa_ie_len) अणु
		अगर (ieee->iw_mode == IW_MODE_ADHOC) अणु
			//as Winकरोws will set pairwise key same as the group key which is not allowed in Linux, so set this क्रम IOT issue. WB 2008.07.07
			स_नकल(&ieee->wpa_ie[14], &ieee->wpa_ie[8], 4);
		पूर्ण
		स_नकल(tag, ieee->wpa_ie, ieee->wpa_ie_len);
		tag += wpa_ie_len;
	पूर्ण

	//skb->dev = ieee->dev;
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *ieee80211_assoc_resp(काष्ठा ieee80211_device *ieee,
					    u8 *dest)
अणु
	काष्ठा sk_buff *skb;
	u8 *tag;

	काष्ठा ieee80211_crypt_data *crypt;
	काष्ठा ieee80211_assoc_response_frame *assoc;
	लघु encrypt;

	अचिन्हित पूर्णांक rate_len = ieee80211_MFIE_rate_len(ieee);
	पूर्णांक len = माप(काष्ठा ieee80211_assoc_response_frame) + rate_len + ieee->tx_headroom;

	skb = dev_alloc_skb(len);

	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, ieee->tx_headroom);

	assoc = skb_put(skb, माप(काष्ठा ieee80211_assoc_response_frame));

	assoc->header.frame_ctl = cpu_to_le16(IEEE80211_STYPE_ASSOC_RESP);
	स_नकल(assoc->header.addr1, dest, ETH_ALEN);
	स_नकल(assoc->header.addr3, ieee->dev->dev_addr, ETH_ALEN);
	स_नकल(assoc->header.addr2, ieee->dev->dev_addr, ETH_ALEN);
	assoc->capability = cpu_to_le16(ieee->iw_mode == IW_MODE_MASTER ?
		WLAN_CAPABILITY_BSS : WLAN_CAPABILITY_IBSS);

	अगर (ieee->लघु_slot)
		assoc->capability |= cpu_to_le16(WLAN_CAPABILITY_SHORT_SLOT);

	अगर (ieee->host_encrypt)
		crypt = ieee->crypt[ieee->tx_keyidx];
	अन्यथा
		crypt = शून्य;

	encrypt = crypt && crypt->ops;

	अगर (encrypt)
		assoc->capability |= cpu_to_le16(WLAN_CAPABILITY_PRIVACY);

	assoc->status = 0;
	assoc->aid = cpu_to_le16(ieee->assoc_id);
	अगर (ieee->assoc_id == 0x2007)
		ieee->assoc_id = 0;
	अन्यथा
		ieee->assoc_id++;

	tag = skb_put(skb, rate_len);

	ieee80211_MFIE_Brate(ieee, &tag);
	ieee80211_MFIE_Grate(ieee, &tag);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *ieee80211_auth_resp(काष्ठा ieee80211_device *ieee,
					   पूर्णांक status, u8 *dest)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_authentication *auth;
	पूर्णांक len = ieee->tx_headroom + माप(काष्ठा ieee80211_authentication) + 1;

	skb = dev_alloc_skb(len);

	अगर (!skb)
		वापस शून्य;

	skb->len = माप(काष्ठा ieee80211_authentication);

	auth = (काष्ठा ieee80211_authentication *)skb->data;

	auth->status = cpu_to_le16(status);
	auth->transaction = cpu_to_le16(2);
	auth->algorithm = cpu_to_le16(WLAN_AUTH_OPEN);

	स_नकल(auth->header.addr3, ieee->dev->dev_addr, ETH_ALEN);
	स_नकल(auth->header.addr2, ieee->dev->dev_addr, ETH_ALEN);
	स_नकल(auth->header.addr1, dest, ETH_ALEN);
	auth->header.frame_ctl = cpu_to_le16(IEEE80211_STYPE_AUTH);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *ieee80211_null_func(काष्ठा ieee80211_device *ieee,
					   लघु pwr)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rtl_80211_hdr_3addr *hdr;

	skb = dev_alloc_skb(माप(काष्ठा rtl_80211_hdr_3addr));

	अगर (!skb)
		वापस शून्य;

	hdr = skb_put(skb, माप(काष्ठा rtl_80211_hdr_3addr));

	स_नकल(hdr->addr1, ieee->current_network.bssid, ETH_ALEN);
	स_नकल(hdr->addr2, ieee->dev->dev_addr, ETH_ALEN);
	स_नकल(hdr->addr3, ieee->current_network.bssid, ETH_ALEN);

	hdr->frame_ctl = cpu_to_le16(IEEE80211_FTYPE_DATA |
				     IEEE80211_STYPE_शून्यFUNC | IEEE80211_FCTL_TODS |
				     (pwr ? IEEE80211_FCTL_PM : 0));

	वापस skb;
पूर्ण

अटल व्योम ieee80211_resp_to_assoc_rq(काष्ठा ieee80211_device *ieee, u8 *dest)
अणु
	काष्ठा sk_buff *buf = ieee80211_assoc_resp(ieee, dest);

	अगर (buf)
		sofपंचांगac_mgmt_xmit(buf, ieee);
पूर्ण

अटल व्योम ieee80211_resp_to_auth(काष्ठा ieee80211_device *ieee, पूर्णांक s,
				   u8 *dest)
अणु
	काष्ठा sk_buff *buf = ieee80211_auth_resp(ieee, s, dest);

	अगर (buf)
		sofपंचांगac_mgmt_xmit(buf, ieee);
पूर्ण

अटल व्योम ieee80211_resp_to_probe(काष्ठा ieee80211_device *ieee, u8 *dest)
अणु
	काष्ठा sk_buff *buf = ieee80211_probe_resp(ieee, dest);
	अगर (buf)
		sofपंचांगac_mgmt_xmit(buf, ieee);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *
ieee80211_association_req(काष्ठा ieee80211_network *beacon,
			  काष्ठा ieee80211_device *ieee)
अणु
	काष्ठा sk_buff *skb;
	//अचिन्हित दीर्घ flags;

	काष्ठा ieee80211_assoc_request_frame *hdr;
	u8 *tag;//,*rsn_ie;
	//लघु info_addr = 0;
	//पूर्णांक i;
	//u16 suite_count = 0;
	//u8 suit_select = 0;
	//अचिन्हित पूर्णांक wpa_len = beacon->wpa_ie_len;
	//क्रम HT
	u8 *ht_cap_buf = शून्य;
	u8 ht_cap_len = 0;
	u8 *realtek_ie_buf = शून्य;
	u8 realtek_ie_len = 0;
	पूर्णांक wpa_ie_len = ieee->wpa_ie_len;
	अचिन्हित पूर्णांक ckip_ie_len = 0;
	अचिन्हित पूर्णांक ccxrm_ie_len = 0;
	अचिन्हित पूर्णांक cxvernum_ie_len = 0;
	काष्ठा ieee80211_crypt_data *crypt;
	पूर्णांक encrypt;

	अचिन्हित पूर्णांक rate_len = ieee80211_MFIE_rate_len(ieee);
	अचिन्हित पूर्णांक wmm_info_len = beacon->qos_data.supported ? 9 : 0;
#अगर_घोषित THOMAS_TURBO
	अचिन्हित पूर्णांक turbo_info_len = beacon->Turbo_Enable ? 9 : 0;
#पूर्ण_अगर

	पूर्णांक len = 0;

	crypt = ieee->crypt[ieee->tx_keyidx];
	encrypt = ieee->host_encrypt && crypt && crypt->ops && ((0 == म_भेद(crypt->ops->name, "WEP") || wpa_ie_len));

	/* Include High Throuput capability && Realtek proprietary */
	अगर (ieee->pHTInfo->bCurrentHTSupport && ieee->pHTInfo->bEnableHT) अणु
		ht_cap_buf = (u8 *)&ieee->pHTInfo->SelfHTCap;
		ht_cap_len = माप(ieee->pHTInfo->SelfHTCap);
		HTConकाष्ठाCapabilityElement(ieee, ht_cap_buf, &ht_cap_len, encrypt);
		अगर (ieee->pHTInfo->bCurrentRT2RTAggregation) अणु
			realtek_ie_buf = ieee->pHTInfo->szRT2RTAggBuffer;
			realtek_ie_len = माप(ieee->pHTInfo->szRT2RTAggBuffer);
			HTConकाष्ठाRT2RTAggElement(ieee, realtek_ie_buf, &realtek_ie_len);
		पूर्ण
	पूर्ण
	अगर (ieee->qos_support)
		wmm_info_len = beacon->qos_data.supported ? 9 : 0;

	अगर (beacon->bCkipSupported)
		ckip_ie_len = 30 + 2;

	अगर (beacon->bCcxRmEnable)
		ccxrm_ie_len = 6 + 2;

	अगर (beacon->BssCcxVerNumber >= 2)
		cxvernum_ie_len = 5 + 2;

#अगर_घोषित THOMAS_TURBO
	len = माप(काष्ठा ieee80211_assoc_request_frame) + 2
		+ beacon->ssid_len	/* essid tagged val */
		+ rate_len	/* rates tagged val */
		+ wpa_ie_len
		+ wmm_info_len
		+ turbo_info_len
		+ ht_cap_len
		+ realtek_ie_len
		+ ckip_ie_len
		+ ccxrm_ie_len
		+ cxvernum_ie_len
		+ ieee->tx_headroom;
#अन्यथा
	len = माप(काष्ठा ieee80211_assoc_request_frame) + 2
		+ beacon->ssid_len	/* essid tagged val */
		+ rate_len	/* rates tagged val */
		+ wpa_ie_len
		+ wmm_info_len
		+ ht_cap_len
		+ realtek_ie_len
		+ ckip_ie_len
		+ ccxrm_ie_len
		+ cxvernum_ie_len
		+ ieee->tx_headroom;
#पूर्ण_अगर
	skb = dev_alloc_skb(len);

	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, ieee->tx_headroom);

	hdr = skb_put(skb, माप(काष्ठा ieee80211_assoc_request_frame) + 2);

	hdr->header.frame_ctl = IEEE80211_STYPE_ASSOC_REQ;
	hdr->header.duration_id = cpu_to_le16(37);
	स_नकल(hdr->header.addr1, beacon->bssid, ETH_ALEN);
	स_नकल(hdr->header.addr2, ieee->dev->dev_addr, ETH_ALEN);
	स_नकल(hdr->header.addr3, beacon->bssid, ETH_ALEN);

	स_नकल(ieee->ap_mac_addr, beacon->bssid, ETH_ALEN);//क्रम HW security, John

	hdr->capability = cpu_to_le16(WLAN_CAPABILITY_BSS);
	अगर (beacon->capability & WLAN_CAPABILITY_PRIVACY)
		hdr->capability |= cpu_to_le16(WLAN_CAPABILITY_PRIVACY);

	अगर (beacon->capability & WLAN_CAPABILITY_SHORT_PREAMBLE)
		hdr->capability |= cpu_to_le16(WLAN_CAPABILITY_SHORT_PREAMBLE); //add लघु_preamble here

	अगर (ieee->लघु_slot)
		hdr->capability |= cpu_to_le16(WLAN_CAPABILITY_SHORT_SLOT);
	अगर (wmm_info_len) //QOS
		hdr->capability |= cpu_to_le16(WLAN_CAPABILITY_QOS);

	hdr->listen_पूर्णांकerval = cpu_to_le16(0xa);

	hdr->info_element[0].id = MFIE_TYPE_SSID;

	hdr->info_element[0].len = beacon->ssid_len;
	skb_put_data(skb, beacon->ssid, beacon->ssid_len);

	tag = skb_put(skb, rate_len);

	ieee80211_MFIE_Brate(ieee, &tag);
	ieee80211_MFIE_Grate(ieee, &tag);
	// For CCX 1 S13, CKIP. Added by Annie, 2006-08-14.
	अगर (beacon->bCkipSupported) अणु
		अटल u8	AironetIeOui[] = अणु0x00, 0x01, 0x66पूर्ण; // "4500-client"
		u8	CcxAironetBuf[30];
		काष्ठा octet_string	osCcxAironetIE;

		स_रखो(CcxAironetBuf, 0, 30);
		osCcxAironetIE.octet = CcxAironetBuf;
		osCcxAironetIE.length = माप(CcxAironetBuf);
		//
		// Ref. CCX test plan v3.61, 3.2.3.1 step 13.
		// We want to make the device type as "4500-client". 060926, by CCW.
		//
		स_नकल(osCcxAironetIE.octet, AironetIeOui, माप(AironetIeOui));

		// CCX1 spec V1.13, A01.1 CKIP Negotiation (page23):
		// "The CKIP negotiation is started with the associate request from the client to the access poपूर्णांक,
		//  containing an Aironet element with both the MIC and KP bits set."
		osCcxAironetIE.octet[IE_CISCO_FLAG_POSITION] |= (SUPPORT_CKIP_PK | SUPPORT_CKIP_MIC);
		tag = skb_put(skb, ckip_ie_len);
		*tag++ = MFIE_TYPE_AIRONET;
		*tag++ = osCcxAironetIE.length;
		स_नकल(tag, osCcxAironetIE.octet, osCcxAironetIE.length);
		tag += osCcxAironetIE.length;
	पूर्ण

	अगर (beacon->bCcxRmEnable) अणु
		अटल u8 CcxRmCapBuf[] = अणु0x00, 0x40, 0x96, 0x01, 0x01, 0x00पूर्ण;
		काष्ठा octet_string osCcxRmCap;

		osCcxRmCap.octet = CcxRmCapBuf;
		osCcxRmCap.length = माप(CcxRmCapBuf);
		tag = skb_put(skb, ccxrm_ie_len);
		*tag++ = MFIE_TYPE_GENERIC;
		*tag++ = osCcxRmCap.length;
		स_नकल(tag, osCcxRmCap.octet, osCcxRmCap.length);
		tag += osCcxRmCap.length;
	पूर्ण

	अगर (beacon->BssCcxVerNumber >= 2) अणु
		u8			CcxVerNumBuf[] = अणु0x00, 0x40, 0x96, 0x03, 0x00पूर्ण;
		काष्ठा octet_string	osCcxVerNum;
		CcxVerNumBuf[4] = beacon->BssCcxVerNumber;
		osCcxVerNum.octet = CcxVerNumBuf;
		osCcxVerNum.length = माप(CcxVerNumBuf);
		tag = skb_put(skb, cxvernum_ie_len);
		*tag++ = MFIE_TYPE_GENERIC;
		*tag++ = osCcxVerNum.length;
		स_नकल(tag, osCcxVerNum.octet, osCcxVerNum.length);
		tag += osCcxVerNum.length;
	पूर्ण
	//HT cap element
	अगर (ieee->pHTInfo->bCurrentHTSupport && ieee->pHTInfo->bEnableHT) अणु
		अगर (ieee->pHTInfo->ePeerHTSpecVer != HT_SPEC_VER_EWC) अणु
			tag = skb_put(skb, ht_cap_len);
			*tag++ = MFIE_TYPE_HT_CAP;
			*tag++ = ht_cap_len - 2;
			स_नकल(tag, ht_cap_buf, ht_cap_len - 2);
			tag += ht_cap_len - 2;
		पूर्ण
	पूर्ण

	//choose what wpa_supplicant gives to associate.
	अगर (wpa_ie_len)
		skb_put_data(skb, ieee->wpa_ie, wpa_ie_len);

	अगर (wmm_info_len) अणु
		tag = skb_put(skb, wmm_info_len);
		ieee80211_WMM_Info(ieee, &tag);
	पूर्ण
#अगर_घोषित THOMAS_TURBO
	अगर (turbo_info_len) अणु
		tag = skb_put(skb, turbo_info_len);
		ieee80211_TURBO_Info(ieee, &tag);
	पूर्ण
#पूर्ण_अगर

	अगर (ieee->pHTInfo->bCurrentHTSupport && ieee->pHTInfo->bEnableHT) अणु
		अगर (ieee->pHTInfo->ePeerHTSpecVer == HT_SPEC_VER_EWC) अणु
			tag = skb_put(skb, ht_cap_len);
			*tag++ = MFIE_TYPE_GENERIC;
			*tag++ = ht_cap_len - 2;
			स_नकल(tag, ht_cap_buf, ht_cap_len - 2);
			tag += ht_cap_len - 2;
		पूर्ण

		अगर (ieee->pHTInfo->bCurrentRT2RTAggregation) अणु
			tag = skb_put(skb, realtek_ie_len);
			*tag++ = MFIE_TYPE_GENERIC;
			*tag++ = realtek_ie_len - 2;
			स_नकल(tag, realtek_ie_buf, realtek_ie_len - 2);
		पूर्ण
	पूर्ण
//	prपूर्णांकk("<=====%s(), %p, %p\n", __func__, ieee->dev, ieee->dev->dev_addr);
//	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA, skb->data, skb->len);
	वापस skb;
पूर्ण

व्योम ieee80211_associate_पात(काष्ठा ieee80211_device *ieee)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&ieee->lock, flags);

	ieee->associate_seq++;

	/* करोn't scan, and aव्योम to have the RX path possibily
	 * try again to associate. Even करो not react to AUTH or
	 * ASSOC response. Just रुको क्रम the retry wq to be scheduled.
	 * Here we will check अगर there are good nets to associate
	 * with, so we retry or just get back to NO_LINK and scanning
	 */
	अगर (ieee->state == IEEE80211_ASSOCIATING_AUTHENTICATING) अणु
		IEEE80211_DEBUG_MGMT("Authentication failed\n");
		ieee->sofपंचांगac_stats.no_auth_rs++;
	पूर्ण अन्यथा अणु
		IEEE80211_DEBUG_MGMT("Association failed\n");
		ieee->sofपंचांगac_stats.no_ass_rs++;
	पूर्ण

	ieee->state = IEEE80211_ASSOCIATING_RETRY;

	schedule_delayed_work(&ieee->associate_retry_wq, \
			      IEEE80211_SOFTMAC_ASSOC_RETRY_TIME);

	spin_unlock_irqrestore(&ieee->lock, flags);
पूर्ण

अटल व्योम ieee80211_associate_पात_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा ieee80211_device *dev = from_समयr(dev, t, associate_समयr);

	ieee80211_associate_पात(dev);
पूर्ण

अटल व्योम ieee80211_associate_step1(काष्ठा ieee80211_device *ieee)
अणु
	काष्ठा ieee80211_network *beacon = &ieee->current_network;
	काष्ठा sk_buff *skb;

	IEEE80211_DEBUG_MGMT("Stopping scan\n");

	ieee->sofपंचांगac_stats.tx_auth_rq++;
	skb = ieee80211_authentication_req(beacon, ieee, 0);

	अगर (!skb) अणु
		ieee80211_associate_पात(ieee);
	पूर्ण अन्यथा अणु
		ieee->state = IEEE80211_ASSOCIATING_AUTHENTICATING;
		IEEE80211_DEBUG_MGMT("Sending authentication request\n");
		sofपंचांगac_mgmt_xmit(skb, ieee);
		//BUGON when you try to add_समयr twice, using mod_समयr may be better, john0709
		अगर (!समयr_pending(&ieee->associate_समयr)) अणु
			ieee->associate_समयr.expires = jअगरfies + (HZ / 2);
			add_समयr(&ieee->associate_समयr);
		पूर्ण
		//dev_kमुक्त_skb_any(skb);//edit by thomas
	पूर्ण
पूर्ण

अटल व्योम ieee80211_auth_challenge(काष्ठा ieee80211_device *ieee,
				     u8 *challenge,
				     पूर्णांक chlen)
अणु
	u8 *c;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_network *beacon = &ieee->current_network;
//	पूर्णांक hlen = माप(काष्ठा ieee80211_authentication);

	ieee->associate_seq++;
	ieee->sofपंचांगac_stats.tx_auth_rq++;

	skb = ieee80211_authentication_req(beacon, ieee, chlen + 2);
	अगर (!skb) अणु
		ieee80211_associate_पात(ieee);
	पूर्ण अन्यथा अणु
		c = skb_put(skb, chlen + 2);
		*(c++) = MFIE_TYPE_CHALLENGE;
		*(c++) = chlen;
		स_नकल(c, challenge, chlen);

		IEEE80211_DEBUG_MGMT("Sending authentication challenge response\n");

		ieee80211_encrypt_fragment(ieee, skb, माप(काष्ठा rtl_80211_hdr_3addr));

		sofपंचांगac_mgmt_xmit(skb, ieee);
		mod_समयr(&ieee->associate_समयr, jअगरfies + (HZ / 2));
		//dev_kमुक्त_skb_any(skb);//edit by thomas
	पूर्ण
	kमुक्त(challenge);
पूर्ण

अटल व्योम ieee80211_associate_step2(काष्ठा ieee80211_device *ieee)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_network *beacon = &ieee->current_network;

	del_समयr_sync(&ieee->associate_समयr);

	IEEE80211_DEBUG_MGMT("Sending association request\n");

	ieee->sofपंचांगac_stats.tx_ass_rq++;
	skb = ieee80211_association_req(beacon, ieee);
	अगर (!skb) अणु
		ieee80211_associate_पात(ieee);
	पूर्ण अन्यथा अणु
		sofपंचांगac_mgmt_xmit(skb, ieee);
		mod_समयr(&ieee->associate_समयr, jअगरfies + (HZ / 2));
		//dev_kमुक्त_skb_any(skb);//edit by thomas
	पूर्ण
पूर्ण
अटल व्योम ieee80211_associate_complete_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_device *ieee = container_of(work, काष्ठा ieee80211_device, associate_complete_wq);

	netdev_info(ieee->dev, "Associated successfully\n");
	अगर (ieee80211_is_54g(&ieee->current_network) &&
	    (ieee->modulation & IEEE80211_OFDM_MODULATION)) अणु
		ieee->rate = 108;
		netdev_info(ieee->dev, "Using G rates:%d\n", ieee->rate);
	पूर्ण अन्यथा अणु
		ieee->rate = 22;
		netdev_info(ieee->dev, "Using B rates:%d\n", ieee->rate);
	पूर्ण
	अगर (ieee->pHTInfo->bCurrentHTSupport && ieee->pHTInfo->bEnableHT) अणु
		prपूर्णांकk("Successfully associated, ht enabled\n");
		HTOnAssocRsp(ieee);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("Successfully associated, ht not enabled(%d, %d)\n", ieee->pHTInfo->bCurrentHTSupport, ieee->pHTInfo->bEnableHT);
		स_रखो(ieee->करोt11HTOperationalRateSet, 0, 16);
		//HTSetConnectBwMode(ieee, HT_CHANNEL_WIDTH_20, HT_EXTCHNL_OFFSET_NO_EXT);
	पूर्ण
	ieee->LinkDetectInfo.SlotNum = 2 * (1 + ieee->current_network.beacon_पूर्णांकerval / 500);
	// To prevent the immediately calling watch_करोg after association.
	अगर (ieee->LinkDetectInfo.NumRecvBcnInPeriod == 0 || ieee->LinkDetectInfo.NumRecvDataInPeriod == 0) अणु
		ieee->LinkDetectInfo.NumRecvBcnInPeriod = 1;
		ieee->LinkDetectInfo.NumRecvDataInPeriod = 1;
	पूर्ण
	ieee->link_change(ieee->dev);
	अगर (!ieee->is_silent_reset) अणु
		prपूर्णांकk("============>normal associate\n");
		notअगरy_wx_assoc_event(ieee);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("==================>silent reset associate\n");
		ieee->is_silent_reset = false;
	पूर्ण

	अगर (ieee->data_hard_resume)
		ieee->data_hard_resume(ieee->dev);
	netअगर_carrier_on(ieee->dev);
पूर्ण

अटल व्योम ieee80211_associate_complete(काष्ठा ieee80211_device *ieee)
अणु
//	पूर्णांक i;
//	काष्ठा net_device* dev = ieee->dev;
	del_समयr_sync(&ieee->associate_समयr);

	ieee->state = IEEE80211_LINKED;
	//ieee->UpdateHalRATRTableHandler(dev, ieee->करोt11HTOperationalRateSet);
	schedule_work(&ieee->associate_complete_wq);
पूर्ण

अटल व्योम ieee80211_associate_procedure_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_device *ieee = container_of(work, काष्ठा ieee80211_device, associate_procedure_wq);
	ieee->sync_scan_hurryup = 1;
	mutex_lock(&ieee->wx_mutex);

	अगर (ieee->data_hard_stop)
		ieee->data_hard_stop(ieee->dev);

	ieee80211_stop_scan(ieee);
	prपूर्णांकk("===>%s(), chan:%d\n", __func__, ieee->current_network.channel);
	//ieee->set_chan(ieee->dev, ieee->current_network.channel);
	HTSetConnectBwMode(ieee, HT_CHANNEL_WIDTH_20, HT_EXTCHNL_OFFSET_NO_EXT);

	ieee->associate_seq = 1;
	ieee80211_associate_step1(ieee);

	mutex_unlock(&ieee->wx_mutex);
पूर्ण

अंतरभूत व्योम ieee80211_sofपंचांगac_new_net(काष्ठा ieee80211_device *ieee, काष्ठा ieee80211_network *net)
अणु
	u8 पंचांगp_ssid[IW_ESSID_MAX_SIZE + 1];
	पूर्णांक पंचांगp_ssid_len = 0;

	लघु apset, ssidset, ssidbroad, apmatch, ssidmatch;

	/* we are पूर्णांकerested in new new only अगर we are not associated
	 * and we are not associating / authenticating
	 */
	अगर (ieee->state != IEEE80211_NOLINK)
		वापस;

	अगर ((ieee->iw_mode == IW_MODE_INFRA) && !(net->capability & WLAN_CAPABILITY_BSS))
		वापस;

	अगर ((ieee->iw_mode == IW_MODE_ADHOC) && !(net->capability & WLAN_CAPABILITY_IBSS))
		वापस;

	अगर (ieee->iw_mode == IW_MODE_INFRA || ieee->iw_mode == IW_MODE_ADHOC) अणु
		/* अगर the user specअगरied the AP MAC, we need also the essid
		 * This could be obtained by beacons or, अगर the network करोes not
		 * broadcast it, it can be put manually.
		 */
		apset = ieee->wap_set;//(स_भेद(ieee->current_network.bssid, zero,ETH_ALEN)!=0 );
		ssidset = ieee->ssid_set;//ieee->current_network.ssid[0] != '\0';
		ssidbroad =  !(net->ssid_len == 0 || net->ssid[0] == '\0');
		apmatch = (स_भेद(ieee->current_network.bssid, net->bssid, ETH_ALEN) == 0);
		ssidmatch = (ieee->current_network.ssid_len == net->ssid_len) &&
			(!म_भेदन(ieee->current_network.ssid, net->ssid, net->ssid_len));

		/* अगर the user set the AP check अगर match.
		 * अगर the network करोes not broadcast essid we check the user supplyed ANY essid
		 * अगर the network करोes broadcast and the user करोes not set essid it is OK
		 * अगर the network करोes broadcast and the user did set essid chech अगर essid match
		 */
		अगर ((apset && apmatch &&
		     ((ssidset && ssidbroad && ssidmatch) || (ssidbroad && !ssidset) || (!ssidbroad && ssidset))) ||
		    /* अगर the ap is not set, check that the user set the bssid
		     * and the network करोes broadcast and that those two bssid matches
		     */
		    (!apset && ssidset && ssidbroad && ssidmatch)) अणु
			/* अगर the essid is hidden replace it with the
			 * essid provided by the user.
			 */
			अगर (!ssidbroad) अणु
				म_नकलन(पंचांगp_ssid, ieee->current_network.ssid, IW_ESSID_MAX_SIZE);
				पंचांगp_ssid_len = ieee->current_network.ssid_len;
			पूर्ण
			स_नकल(&ieee->current_network, net, माप(काष्ठा ieee80211_network));

			म_नकलन(ieee->current_network.ssid, पंचांगp_ssid, IW_ESSID_MAX_SIZE);
			ieee->current_network.ssid_len = पंचांगp_ssid_len;
			netdev_info(ieee->dev,
				    "Linking with %s,channel:%d, qos:%d, myHT:%d, networkHT:%d\n",
				    ieee->current_network.ssid,
				    ieee->current_network.channel,
				    ieee->current_network.qos_data.supported,
				    ieee->pHTInfo->bEnableHT,
				    ieee->current_network.bssht.bdSupportHT);

			//ieee->pHTInfo->IOTAction = 0;
			HTResetIOTSetting(ieee->pHTInfo);
			अगर (ieee->iw_mode == IW_MODE_INFRA) अणु
				/* Join the network क्रम the first समय */
				ieee->AsocRetryCount = 0;
				//क्रम HT by amy 080514
				अगर ((ieee->current_network.qos_data.supported == 1) &&
				    // (ieee->pHTInfo->bEnableHT && ieee->current_network.bssht.bdSupportHT))
				    ieee->current_network.bssht.bdSupportHT) अणु
/*WB, 2008.09.09:bCurrentHTSupport and bEnableHT two flags are going to put together to check whether we are in HT now, so needn't to check bEnableHT flags here. That's is to say we will set to HT support whenever joined AP has the ability to support HT. And whether we are in HT or not, please check bCurrentHTSupport&&bEnableHT now please.*/
					//	ieee->pHTInfo->bCurrentHTSupport = true;
					HTResetSelfAndSavePeerSetting(ieee, &ieee->current_network);
				पूर्ण अन्यथा अणु
					ieee->pHTInfo->bCurrentHTSupport = false;
				पूर्ण

				ieee->state = IEEE80211_ASSOCIATING;
				schedule_work(&ieee->associate_procedure_wq);
			पूर्ण अन्यथा अणु
				अगर (ieee80211_is_54g(&ieee->current_network) &&
				    (ieee->modulation & IEEE80211_OFDM_MODULATION)) अणु
					ieee->rate = 108;
					ieee->SetWirelessMode(ieee->dev, IEEE_G);
					netdev_info(ieee->dev,
						    "Using G rates\n");
				पूर्ण अन्यथा अणु
					ieee->rate = 22;
					ieee->SetWirelessMode(ieee->dev, IEEE_B);
					netdev_info(ieee->dev,
						    "Using B rates\n");
				पूर्ण
				स_रखो(ieee->करोt11HTOperationalRateSet, 0, 16);
				//HTSetConnectBwMode(ieee, HT_CHANNEL_WIDTH_20, HT_EXTCHNL_OFFSET_NO_EXT);
				ieee->state = IEEE80211_LINKED;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम ieee80211_sofपंचांगac_check_all_nets(काष्ठा ieee80211_device *ieee)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ieee80211_network *target;

	spin_lock_irqsave(&ieee->lock, flags);

	list_क्रम_each_entry(target, &ieee->network_list, list) अणु
		/* अगर the state become dअगरferent that NOLINK means
		 * we had found what we are searching क्रम
		 */

		अगर (ieee->state != IEEE80211_NOLINK)
			अवरोध;

		अगर (ieee->scan_age == 0 || समय_after(target->last_scanned + ieee->scan_age, jअगरfies))
			ieee80211_sofपंचांगac_new_net(ieee, target);
	पूर्ण

	spin_unlock_irqrestore(&ieee->lock, flags);
पूर्ण

अटल अंतरभूत u16 auth_parse(काष्ठा sk_buff *skb, u8 **challenge, पूर्णांक *chlen)
अणु
	काष्ठा ieee80211_authentication *a;
	u8 *t;
	अगर (skb->len < (माप(काष्ठा ieee80211_authentication) - माप(काष्ठा ieee80211_info_element))) अणु
		IEEE80211_DEBUG_MGMT("invalid len in auth resp: %d\n", skb->len);
		वापस 0xcafe;
	पूर्ण
	*challenge = शून्य;
	a = (काष्ठा ieee80211_authentication *)skb->data;
	अगर (skb->len > (माप(काष्ठा ieee80211_authentication) + 3)) अणु
		t = skb->data + माप(काष्ठा ieee80211_authentication);

		अगर (*(t++) == MFIE_TYPE_CHALLENGE) अणु
			*chlen = *(t++);
			*challenge = kmemdup(t, *chlen, GFP_ATOMIC);
			अगर (!*challenge)
				वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस le16_to_cpu(a->status);
पूर्ण

अटल पूर्णांक auth_rq_parse(काष्ठा sk_buff *skb, u8 *dest)
अणु
	काष्ठा ieee80211_authentication *a;

	अगर (skb->len < (माप(काष्ठा ieee80211_authentication) - माप(काष्ठा ieee80211_info_element))) अणु
		IEEE80211_DEBUG_MGMT("invalid len in auth request: %d\n", skb->len);
		वापस -1;
	पूर्ण
	a = (काष्ठा ieee80211_authentication *)skb->data;

	स_नकल(dest, a->header.addr2, ETH_ALEN);

	अगर (le16_to_cpu(a->algorithm) != WLAN_AUTH_OPEN)
		वापस  WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG;

	वापस WLAN_STATUS_SUCCESS;
पूर्ण

अटल लघु probe_rq_parse(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb, u8 *src)
अणु
	u8 *tag;
	u8 *skbend;
	u8 *ssid = शून्य;
	u8 ssidlen = 0;

	काष्ठा rtl_80211_hdr_3addr   *header =
		(काष्ठा rtl_80211_hdr_3addr   *)skb->data;

	अगर (skb->len < माप(काष्ठा rtl_80211_hdr_3addr))
		वापस -1; /* corrupted */

	स_नकल(src, header->addr2, ETH_ALEN);

	skbend = (u8 *)skb->data + skb->len;

	tag = skb->data + माप(काष्ठा rtl_80211_hdr_3addr);

	जबतक (tag + 1 < skbend) अणु
		अगर (*tag == 0) अणु
			ssid = tag + 2;
			ssidlen = *(tag + 1);
			अवरोध;
		पूर्ण
		tag++; /* poपूर्णांक to the len field */
		tag = tag + *(tag); /* poपूर्णांक to the last data byte of the tag */
		tag++; /* poपूर्णांक to the next tag */
	पूर्ण

	//IEEE80211DMESG("Card MAC address is "MACSTR, MAC2STR(src));
	अगर (ssidlen == 0)
		वापस 1;

	अगर (!ssid)
		वापस 1; /* ssid not found in tagged param */

	वापस (!म_भेदन(ssid, ieee->current_network.ssid, ssidlen));
पूर्ण

अटल पूर्णांक assoc_rq_parse(काष्ठा sk_buff *skb, u8 *dest)
अणु
	काष्ठा ieee80211_assoc_request_frame *a;

	अगर (skb->len < (माप(काष्ठा ieee80211_assoc_request_frame) -
		माप(काष्ठा ieee80211_info_element))) अणु
		IEEE80211_DEBUG_MGMT("invalid len in auth request:%d \n", skb->len);
		वापस -1;
	पूर्ण

	a = (काष्ठा ieee80211_assoc_request_frame *)skb->data;

	स_नकल(dest, a->header.addr2, ETH_ALEN);

	वापस 0;
पूर्ण

अटल अंतरभूत u16 assoc_parse(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb, पूर्णांक *aid)
अणु
	काष्ठा ieee80211_assoc_response_frame *response_head;
	u16 status_code;

	अगर (skb->len < माप(काष्ठा ieee80211_assoc_response_frame)) अणु
		IEEE80211_DEBUG_MGMT("invalid len in auth resp: %d\n", skb->len);
		वापस 0xcafe;
	पूर्ण

	response_head = (काष्ठा ieee80211_assoc_response_frame *)skb->data;
	*aid = le16_to_cpu(response_head->aid) & 0x3fff;

	status_code = le16_to_cpu(response_head->status);
	अगर ((status_code == WLAN_STATUS_ASSOC_DENIED_RATES ||
	     status_code == WLAN_STATUS_CAPS_UNSUPPORTED) &&
	    ((ieee->mode == IEEE_G) &&
	     (ieee->current_network.mode == IEEE_N_24G) &&
	     (ieee->AsocRetryCount++ < (RT_ASOC_RETRY_LIMIT - 1)))) अणु
		ieee->pHTInfo->IOTAction |= HT_IOT_ACT_PURE_N_MODE;
	पूर्ण अन्यथा अणु
		ieee->AsocRetryCount = 0;
	पूर्ण

	वापस le16_to_cpu(response_head->status);
पूर्ण

अटल अंतरभूत व्योम
ieee80211_rx_probe_rq(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb)
अणु
	u8 dest[ETH_ALEN];

	//IEEE80211DMESG("Rx probe");
	ieee->sofपंचांगac_stats.rx_probe_rq++;
	//DMESG("Dest is "MACSTR, MAC2STR(dest));
	अगर (probe_rq_parse(ieee, skb, dest)) अणु
		//IEEE80211DMESG("Was for me!");
		ieee->sofपंचांगac_stats.tx_probe_rs++;
		ieee80211_resp_to_probe(ieee, dest);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
ieee80211_rx_auth_rq(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb)
अणु
	u8 dest[ETH_ALEN];
	पूर्णांक status;
	//IEEE80211DMESG("Rx probe");
	ieee->sofपंचांगac_stats.rx_auth_rq++;

	status = auth_rq_parse(skb, dest);
	अगर (status != -1)
		ieee80211_resp_to_auth(ieee, status, dest);
	//DMESG("Dest is "MACSTR, MAC2STR(dest));
पूर्ण

अटल अंतरभूत व्योम
ieee80211_rx_assoc_rq(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb)
अणु
	u8 dest[ETH_ALEN];
	//अचिन्हित दीर्घ flags;

	ieee->sofपंचांगac_stats.rx_ass_rq++;
	अगर (assoc_rq_parse(skb, dest) != -1)
		ieee80211_resp_to_assoc_rq(ieee, dest);

	netdev_info(ieee->dev, "New client associated: %pM\n", dest);
	//FIXME
पूर्ण

अटल व्योम ieee80211_sta_ps_send_null_frame(काष्ठा ieee80211_device *ieee,
					     लघु pwr)
अणु
	काष्ठा sk_buff *buf = ieee80211_null_func(ieee, pwr);

	अगर (buf)
		sofपंचांगac_ps_mgmt_xmit(buf, ieee);
पूर्ण
/* EXPORT_SYMBOL(ieee80211_sta_ps_send_null_frame); */

अटल लघु ieee80211_sta_ps_sleep(काष्ठा ieee80211_device *ieee, u32 *समय_h,
				    u32 *समय_l)
अणु
	पूर्णांक समयout;
	u8 dtim;
	/*अगर(ieee->ps == IEEE80211_PS_DISABLED ||
		ieee->iw_mode != IW_MODE_INFRA ||
		ieee->state != IEEE80211_LINKED)

		वापस 0;
	*/
	dtim = ieee->current_network.dtim_data;
	अगर (!(dtim & IEEE80211_DTIM_VALID))
		वापस 0;
	समयout = ieee->current_network.beacon_पूर्णांकerval; //should we use ps_समयout value or beacon_पूर्णांकerval
	ieee->current_network.dtim_data = IEEE80211_DTIM_INVALID;

	अगर (dtim & ((IEEE80211_DTIM_UCAST | IEEE80211_DTIM_MBCAST) & ieee->ps))
		वापस 2;

	अगर (!समय_after(jअगरfies,
			dev_trans_start(ieee->dev) + msecs_to_jअगरfies(समयout)))
		वापस 0;

	अगर (!समय_after(jअगरfies,
			ieee->last_rx_ps_समय + msecs_to_jअगरfies(समयout)))
		वापस 0;

	अगर ((ieee->sofपंचांगac_features & IEEE_SOFTMAC_SINGLE_QUEUE) &&
	    (ieee->mgmt_queue_tail != ieee->mgmt_queue_head))
		वापस 0;

	अगर (समय_l) अणु
		*समय_l = ieee->current_network.last_dtim_sta_समय[0]
			+ (ieee->current_network.beacon_पूर्णांकerval
			   * ieee->current_network.dtim_period) * 1000;
	पूर्ण

	अगर (समय_h) अणु
		*समय_h = ieee->current_network.last_dtim_sta_समय[1];
		अगर (समय_l && *समय_l < ieee->current_network.last_dtim_sta_समय[0])
			*समय_h += 1;
	पूर्ण

	वापस 1;
पूर्ण

अटल अंतरभूत व्योम ieee80211_sta_ps(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ieee80211_device *ieee = from_tasklet(ieee, t, ps_task);
	u32 th, tl;
	लघु sleep;

	अचिन्हित दीर्घ flags, flags2;

	spin_lock_irqsave(&ieee->lock, flags);

	अगर ((ieee->ps == IEEE80211_PS_DISABLED ||
	     ieee->iw_mode != IW_MODE_INFRA ||
	     ieee->state != IEEE80211_LINKED)) अणु
		//	#warning CHECK_LOCK_HERE
		spin_lock_irqsave(&ieee->mgmt_tx_lock, flags2);

		ieee80211_sta_wakeup(ieee, 1);

		spin_unlock_irqrestore(&ieee->mgmt_tx_lock, flags2);
	पूर्ण

	sleep = ieee80211_sta_ps_sleep(ieee, &th, &tl);
	/* 2 wake, 1 sleep, 0 करो nothing */
	अगर (sleep == 0)
		जाओ out;

	अगर (sleep == 1) अणु
		अगर (ieee->sta_sleep == 1) अणु
			ieee->enter_sleep_state(ieee->dev, th, tl);
		पूर्ण अन्यथा अगर (ieee->sta_sleep == 0) अणु
		//	prपूर्णांकk("send null 1\n");
			spin_lock_irqsave(&ieee->mgmt_tx_lock, flags2);

			अगर (ieee->ps_is_queue_empty(ieee->dev)) अणु
				ieee->sta_sleep = 2;

				ieee->ps_request_tx_ack(ieee->dev);

				ieee80211_sta_ps_send_null_frame(ieee, 1);

				ieee->ps_th = th;
				ieee->ps_tl = tl;
			पूर्ण
			spin_unlock_irqrestore(&ieee->mgmt_tx_lock, flags2);
		पूर्ण
	पूर्ण अन्यथा अगर (sleep == 2) अणु
//#warning CHECK_LOCK_HERE
		spin_lock_irqsave(&ieee->mgmt_tx_lock, flags2);

		ieee80211_sta_wakeup(ieee, 1);

		spin_unlock_irqrestore(&ieee->mgmt_tx_lock, flags2);
	पूर्ण
out:
	spin_unlock_irqrestore(&ieee->lock, flags);
पूर्ण

व्योम ieee80211_sta_wakeup(काष्ठा ieee80211_device *ieee, लघु nl)
अणु
	अगर (ieee->sta_sleep == 0) अणु
		अगर (nl) अणु
			prपूर्णांकk("Warning: driver is probably failing to report TX ps error\n");
			ieee->ps_request_tx_ack(ieee->dev);
			ieee80211_sta_ps_send_null_frame(ieee, 0);
		पूर्ण
		वापस;
	पूर्ण

	अगर (ieee->sta_sleep == 1)
		ieee->sta_wake_up(ieee->dev);

	ieee->sta_sleep = 0;

	अगर (nl) अणु
		ieee->ps_request_tx_ack(ieee->dev);
		ieee80211_sta_ps_send_null_frame(ieee, 0);
	पूर्ण
पूर्ण

व्योम ieee80211_ps_tx_ack(काष्ठा ieee80211_device *ieee, लघु success)
अणु
	अचिन्हित दीर्घ flags, flags2;

	spin_lock_irqsave(&ieee->lock, flags);

	अगर (ieee->sta_sleep == 2) अणु
		/* Null frame with PS bit set */
		अगर (success) अणु
			ieee->sta_sleep = 1;
			ieee->enter_sleep_state(ieee->dev, ieee->ps_th, ieee->ps_tl);
		पूर्ण
		/* अगर the card report not success we can't be sure the AP
		 * has not RXed so we can't assume the AP believe us awake
		 */
	पूर्ण अन्यथा अणु
		/* 21112005 - tx again null without PS bit अगर lost */
		अगर ((ieee->sta_sleep == 0) && !success) अणु
			spin_lock_irqsave(&ieee->mgmt_tx_lock, flags2);
			ieee80211_sta_ps_send_null_frame(ieee, 0);
			spin_unlock_irqrestore(&ieee->mgmt_tx_lock, flags2);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ieee->lock, flags);
पूर्ण
EXPORT_SYMBOL(ieee80211_ps_tx_ack);

अटल व्योम ieee80211_process_action(काष्ठा ieee80211_device *ieee,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_80211_hdr *header = (काष्ठा rtl_80211_hdr *)skb->data;
	u8 *act = ieee80211_get_payload(header);
	u8 पंचांगp = 0;
//	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA|IEEE80211_DL_BA, skb->data, skb->len);
	अगर (!act) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "error to get payload of action frame\n");
		वापस;
	पूर्ण
	पंचांगp = *act;
	act++;
	चयन (पंचांगp) अणु
	हाल ACT_CAT_BA:
		अगर (*act == ACT_ADDBAREQ)
			ieee80211_rx_ADDBAReq(ieee, skb);
		अन्यथा अगर (*act == ACT_ADDBARSP)
			ieee80211_rx_ADDBARsp(ieee, skb);
		अन्यथा अगर (*act == ACT_DELBA)
			ieee80211_rx_DELBA(ieee, skb);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस;
पूर्ण

अटल व्योम ieee80211_check_auth_response(काष्ठा ieee80211_device *ieee,
					  काष्ठा sk_buff *skb)
अणु
	/* शेष support N mode, disable halfNmode */
	bool bSupportNmode = true, bHalfSupportNmode = false;
	u16 errcode;
	u8 *challenge;
	पूर्णांक chlen = 0;
	u32 iotAction;

	errcode = auth_parse(skb, &challenge, &chlen);
	अगर (!errcode) अणु
		अगर (ieee->खोलो_wep || !challenge) अणु
			ieee->state = IEEE80211_ASSOCIATING_AUTHENTICATED;
			ieee->sofपंचांगac_stats.rx_auth_rs_ok++;
			iotAction = ieee->pHTInfo->IOTAction;
			अगर (!(iotAction & HT_IOT_ACT_PURE_N_MODE)) अणु
				अगर (!ieee->GetNmodeSupportBySecCfg(ieee->dev)) अणु
					/* WEP or TKIP encryption */
					अगर (IsHTHalfNmodeAPs(ieee)) अणु
						bSupportNmode = true;
						bHalfSupportNmode = true;
					पूर्ण अन्यथा अणु
						bSupportNmode = false;
						bHalfSupportNmode = false;
					पूर्ण
					netdev_dbg(ieee->dev, "SEC(%d, %d)\n",
							bSupportNmode,
							bHalfSupportNmode);
				पूर्ण
			पूर्ण
			/* Dummy wirless mode setting- aव्योम encryption issue */
			अगर (bSupportNmode) अणु
				/* N mode setting */
				ieee->SetWirelessMode(ieee->dev,
						ieee->current_network.mode);
			पूर्ण अन्यथा अणु
				/* b/g mode setting - TODO */
				ieee->SetWirelessMode(ieee->dev, IEEE_G);
			पूर्ण

			अगर (ieee->current_network.mode == IEEE_N_24G &&
					bHalfSupportNmode) अणु
				netdev_dbg(ieee->dev, "enter half N mode\n");
				ieee->bHalfWirelessN24GMode = true;
			पूर्ण अन्यथा अणु
				ieee->bHalfWirelessN24GMode = false;
			पूर्ण
			ieee80211_associate_step2(ieee);
		पूर्ण अन्यथा अणु
			ieee80211_auth_challenge(ieee, challenge, chlen);
		पूर्ण
	पूर्ण अन्यथा अणु
		ieee->sofपंचांगac_stats.rx_auth_rs_err++;
		IEEE80211_DEBUG_MGMT("Auth response status code 0x%x", errcode);
		ieee80211_associate_पात(ieee);
	पूर्ण
पूर्ण

अंतरभूत पूर्णांक
ieee80211_rx_frame_sofपंचांगac(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb,
			   काष्ठा ieee80211_rx_stats *rx_stats, u16 type,
			   u16 stype)
अणु
	काष्ठा rtl_80211_hdr_3addr *header = (काष्ठा rtl_80211_hdr_3addr *)skb->data;
	u16 errcode;
	पूर्णांक aid;
	काष्ठा ieee80211_assoc_response_frame *assoc_resp;
//	काष्ठा ieee80211_info_element *info_element;

	अगर (!ieee->proto_started)
		वापस 0;

	अगर (ieee->sta_sleep || (ieee->ps != IEEE80211_PS_DISABLED &&
				ieee->iw_mode == IW_MODE_INFRA &&
				ieee->state == IEEE80211_LINKED))
		tasklet_schedule(&ieee->ps_task);

	अगर (WLAN_FC_GET_STYPE(header->frame_ctl) != IEEE80211_STYPE_PROBE_RESP &&
	    WLAN_FC_GET_STYPE(header->frame_ctl) != IEEE80211_STYPE_BEACON)
		ieee->last_rx_ps_समय = jअगरfies;

	चयन (WLAN_FC_GET_STYPE(header->frame_ctl)) अणु
	हाल IEEE80211_STYPE_ASSOC_RESP:
	हाल IEEE80211_STYPE_REASSOC_RESP:
		IEEE80211_DEBUG_MGMT("received [RE]ASSOCIATION RESPONSE (%d)\n",
				WLAN_FC_GET_STYPE(header->frame_ctl));
		अगर ((ieee->sofपंचांगac_features & IEEE_SOFTMAC_ASSOCIATE) &&
		    ieee->state == IEEE80211_ASSOCIATING_AUTHENTICATED &&
		    ieee->iw_mode == IW_MODE_INFRA) अणु
			काष्ठा ieee80211_network network_resp;
			काष्ठा ieee80211_network *network = &network_resp;

			errcode = assoc_parse(ieee, skb, &aid);
			अगर (!errcode) अणु
				ieee->state = IEEE80211_LINKED;
				ieee->assoc_id = aid;
				ieee->sofपंचांगac_stats.rx_ass_ok++;
				/* station support qos */
				/* Let the रेजिस्टर setting शेषly with Legacy station */
				अगर (ieee->qos_support) अणु
					assoc_resp = (काष्ठा ieee80211_assoc_response_frame *)skb->data;
					स_रखो(network, 0, माप(*network));
					अगर (ieee80211_parse_info_param(ieee, assoc_resp->info_element,\
								       rx_stats->len - माप(*assoc_resp), \
								       network, rx_stats)) अणु
						वापस 1;
					पूर्ण अन्यथा अणु
						//filling the PeerHTCap. //maybe not necessary as we can get its info from current_network.
						स_नकल(ieee->pHTInfo->PeerHTCapBuf, network->bssht.bdHTCapBuf, network->bssht.bdHTCapLen);
						स_नकल(ieee->pHTInfo->PeerHTInfoBuf, network->bssht.bdHTInfoBuf, network->bssht.bdHTInfoLen);
					पूर्ण
					अगर (ieee->handle_assoc_response)
						ieee->handle_assoc_response(ieee->dev, (काष्ठा ieee80211_assoc_response_frame *)header, network);
				पूर्ण
				ieee80211_associate_complete(ieee);
			पूर्ण अन्यथा अणु
				/* aid could not been allocated */
				ieee->sofपंचांगac_stats.rx_ass_err++;
				prपूर्णांकk("Association response status code 0x%x\n",
				       errcode);
				IEEE80211_DEBUG_MGMT("Association response status code 0x%x\n",
						     errcode);
				अगर (ieee->AsocRetryCount < RT_ASOC_RETRY_LIMIT)
					schedule_work(&ieee->associate_procedure_wq);
				अन्यथा
					ieee80211_associate_पात(ieee);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल IEEE80211_STYPE_ASSOC_REQ:
	हाल IEEE80211_STYPE_REASSOC_REQ:
		अगर ((ieee->sofपंचांगac_features & IEEE_SOFTMAC_ASSOCIATE) &&
		    ieee->iw_mode == IW_MODE_MASTER)
			ieee80211_rx_assoc_rq(ieee, skb);
		अवरोध;

	हाल IEEE80211_STYPE_AUTH:
		अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_ASSOCIATE) अणु
			अगर (ieee->state == IEEE80211_ASSOCIATING_AUTHENTICATING
			    && ieee->iw_mode == IW_MODE_INFRA) अणु
				IEEE80211_DEBUG_MGMT("Received auth response");
				ieee80211_check_auth_response(ieee, skb);
			पूर्ण अन्यथा अगर (ieee->iw_mode == IW_MODE_MASTER) अणु
				ieee80211_rx_auth_rq(ieee, skb);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल IEEE80211_STYPE_PROBE_REQ:
		अगर ((ieee->sofपंचांगac_features & IEEE_SOFTMAC_PROBERS) &&
		    ((ieee->iw_mode == IW_MODE_ADHOC ||
		      ieee->iw_mode == IW_MODE_MASTER) &&
		     ieee->state == IEEE80211_LINKED)) अणु
			ieee80211_rx_probe_rq(ieee, skb);
		पूर्ण
		अवरोध;

	हाल IEEE80211_STYPE_DISASSOC:
	हाल IEEE80211_STYPE_DEAUTH:
		/* FIXME क्रम now repeat all the association procedure
		* both क्रम disassociation and deauthentication
		*/
		अगर ((ieee->sofपंचांगac_features & IEEE_SOFTMAC_ASSOCIATE) &&
		    ieee->state == IEEE80211_LINKED &&
		    ieee->iw_mode == IW_MODE_INFRA) अणु
			ieee->state = IEEE80211_ASSOCIATING;
			ieee->sofपंचांगac_stats.reassoc++;

			notअगरy_wx_assoc_event(ieee);
			//HTSetConnectBwMode(ieee, HT_CHANNEL_WIDTH_20, HT_EXTCHNL_OFFSET_NO_EXT);
			RemovePeerTS(ieee, header->addr2);
			schedule_work(&ieee->associate_procedure_wq);
		पूर्ण
		अवरोध;
	हाल IEEE80211_STYPE_MANAGE_ACT:
		ieee80211_process_action(ieee, skb);
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	//dev_kमुक्त_skb_any(skb);
	वापस 0;
पूर्ण

/* The following are क्रम a simpler TX queue management.
 * Instead of using netअगर_[stop/wake]_queue, the driver
 * will use these two functions (plus a reset one) that
 * will पूर्णांकernally call the kernel netअगर_* and take care
 * of the ieee802.11 fragmentation.
 * So, the driver receives a fragment at a समय and might
 * call the stop function when it wants, without taking
 * care to have enough room to TX an entire packet.
 * This might be useful अगर each fragment needs its own
 * descriptor. Thus, just keeping a total मुक्त memory > than
 * the max fragmentation threshold is not enough. If the
 * ieee802.11 stack passed a TXB काष्ठा, then you would need
 * to keep N मुक्त descriptors where
 * N = MAX_PACKET_SIZE / MIN_FRAG_THRESHOLD.
 * In this way you need just one and the 802.11 stack
 * will take care of buffering fragments and pass them to
 * to the driver later, when it wakes the queue.
 */
व्योम ieee80211_sofपंचांगac_xmit(काष्ठा ieee80211_txb *txb, काष्ठा ieee80211_device *ieee)
अणु
	अचिन्हित पूर्णांक queue_index = txb->queue_index;
	अचिन्हित दीर्घ flags;
	पूर्णांक  i;
	काष्ठा cb_desc *tcb_desc = शून्य;

	spin_lock_irqsave(&ieee->lock, flags);

	/* called with 2nd parm 0, no tx mgmt lock required */
	ieee80211_sta_wakeup(ieee, 0);

	/* update the tx status */
	ieee->stats.tx_bytes += le16_to_cpu(txb->payload_size);
	ieee->stats.tx_packets++;
	tcb_desc = (काष्ठा cb_desc *)(txb->fragments[0]->cb + MAX_DEV_ADDR_SIZE);
	अगर (tcb_desc->bMulticast)
		ieee->stats.multicast++;

	/* अगर xmit available, just xmit it immediately, अन्यथा just insert it to the रुको queue */
	क्रम (i = 0; i < txb->nr_frags; i++) अणु
#अगर_घोषित USB_TX_DRIVER_AGGREGATION_ENABLE
		अगर ((skb_queue_len(&ieee->skb_drv_aggQ[queue_index]) != 0) ||
#अन्यथा
		अगर ((skb_queue_len(&ieee->skb_रुकोQ[queue_index]) != 0) ||
#पूर्ण_अगर
		    (!ieee->check_nic_enough_desc(ieee->dev, queue_index)) ||
		    (ieee->queue_stop)) अणु
			/* insert the skb packet to the रुको queue */
			/* as क्रम the completion function, it करोes not need
			 * to check it any more.
			 * */
			//prपूर्णांकk("error:no descriptor left@queue_index %d\n", queue_index);
			//ieee80211_stop_queue(ieee);
#अगर_घोषित USB_TX_DRIVER_AGGREGATION_ENABLE
			skb_queue_tail(&ieee->skb_drv_aggQ[queue_index], txb->fragments[i]);
#अन्यथा
			skb_queue_tail(&ieee->skb_रुकोQ[queue_index], txb->fragments[i]);
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			ieee->sofपंचांगac_data_hard_start_xmit(txb->fragments[i],
							   ieee->dev, ieee->rate);
			//ieee->stats.tx_packets++;
			//ieee->stats.tx_bytes += txb->fragments[i]->len;
			//ieee->dev->trans_start = jअगरfies;
		पूर्ण
	पूर्ण
	ieee80211_txb_मुक्त(txb);

//निकास:
	spin_unlock_irqrestore(&ieee->lock, flags);
पूर्ण
EXPORT_SYMBOL(ieee80211_sofपंचांगac_xmit);

/* called with ieee->lock acquired */
अटल व्योम ieee80211_resume_tx(काष्ठा ieee80211_device *ieee)
अणु
	पूर्णांक i;
	क्रम (i = ieee->tx_pending.frag; i < ieee->tx_pending.txb->nr_frags; i++) अणु
		अगर (ieee->queue_stop) अणु
			ieee->tx_pending.frag = i;
			वापस;
		पूर्ण अन्यथा अणु
			ieee->sofपंचांगac_data_hard_start_xmit(ieee->tx_pending.txb->fragments[i],
							   ieee->dev, ieee->rate);
			//(i+1)<ieee->tx_pending.txb->nr_frags);
			ieee->stats.tx_packets++;
			netअगर_trans_update(ieee->dev);
		पूर्ण
	पूर्ण

	ieee80211_txb_मुक्त(ieee->tx_pending.txb);
	ieee->tx_pending.txb = शून्य;
पूर्ण

व्योम ieee80211_reset_queue(काष्ठा ieee80211_device *ieee)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ieee->lock, flags);
	init_mgmt_queue(ieee);
	अगर (ieee->tx_pending.txb) अणु
		ieee80211_txb_मुक्त(ieee->tx_pending.txb);
		ieee->tx_pending.txb = शून्य;
	पूर्ण
	ieee->queue_stop = 0;
	spin_unlock_irqrestore(&ieee->lock, flags);
पूर्ण
EXPORT_SYMBOL(ieee80211_reset_queue);

व्योम ieee80211_wake_queue(काष्ठा ieee80211_device *ieee)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb;
	काष्ठा rtl_80211_hdr_3addr  *header;

	spin_lock_irqsave(&ieee->lock, flags);
	अगर (!ieee->queue_stop)
		जाओ निकास;

	ieee->queue_stop = 0;

	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_SINGLE_QUEUE) अणु
		जबतक (!ieee->queue_stop && (skb = dequeue_mgmt(ieee))) अणु
			header = (काष्ठा rtl_80211_hdr_3addr  *)skb->data;

			header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

			अगर (ieee->seq_ctrl[0] == 0xFFF)
				ieee->seq_ctrl[0] = 0;
			अन्यथा
				ieee->seq_ctrl[0]++;

			ieee->sofपंचांगac_data_hard_start_xmit(skb, ieee->dev, ieee->basic_rate);
			//dev_kमुक्त_skb_any(skb);//edit by thomas
		पूर्ण
	पूर्ण
	अगर (!ieee->queue_stop && ieee->tx_pending.txb)
		ieee80211_resume_tx(ieee);

	अगर (!ieee->queue_stop && netअगर_queue_stopped(ieee->dev)) अणु
		ieee->sofपंचांगac_stats.swtxawake++;
		netअगर_wake_queue(ieee->dev);
	पूर्ण
निकास:
	spin_unlock_irqrestore(&ieee->lock, flags);
पूर्ण
EXPORT_SYMBOL(ieee80211_wake_queue);

व्योम ieee80211_stop_queue(काष्ठा ieee80211_device *ieee)
अणु
	//अचिन्हित दीर्घ flags;
	//spin_lock_irqsave(&ieee->lock,flags);

	अगर (!netअगर_queue_stopped(ieee->dev)) अणु
		netअगर_stop_queue(ieee->dev);
		ieee->sofपंचांगac_stats.swtxstop++;
	पूर्ण
	ieee->queue_stop = 1;
	//spin_unlock_irqrestore(&ieee->lock,flags);
पूर्ण
EXPORT_SYMBOL(ieee80211_stop_queue);

/* called in user context only */
व्योम ieee80211_start_master_bss(काष्ठा ieee80211_device *ieee)
अणु
	ieee->assoc_id = 1;

	अगर (ieee->current_network.ssid_len == 0) अणु
		म_नकलन(ieee->current_network.ssid,
			IEEE80211_DEFAULT_TX_ESSID,
			IW_ESSID_MAX_SIZE);

		ieee->current_network.ssid_len = म_माप(IEEE80211_DEFAULT_TX_ESSID);
		ieee->ssid_set = 1;
	पूर्ण

	स_नकल(ieee->current_network.bssid, ieee->dev->dev_addr, ETH_ALEN);

	ieee->set_chan(ieee->dev, ieee->current_network.channel);
	ieee->state = IEEE80211_LINKED;
	ieee->link_change(ieee->dev);
	notअगरy_wx_assoc_event(ieee);

	अगर (ieee->data_hard_resume)
		ieee->data_hard_resume(ieee->dev);

	netअगर_carrier_on(ieee->dev);
पूर्ण

अटल व्योम ieee80211_start_monitor_mode(काष्ठा ieee80211_device *ieee)
अणु
	अगर (ieee->raw_tx) अणु
		अगर (ieee->data_hard_resume)
			ieee->data_hard_resume(ieee->dev);

		netअगर_carrier_on(ieee->dev);
	पूर्ण
पूर्ण
अटल व्योम ieee80211_start_ibss_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा ieee80211_device *ieee = container_of(dwork, काष्ठा ieee80211_device, start_ibss_wq);
	/* iwconfig mode ad-hoc will schedule this and वापस
	 * on the other hand this will block further iwconfig SET
	 * operations because of the wx_mutex hold.
	 * Anyway some most set operations set a flag to speed-up
	 * (पात) this wq (when syncro scanning) beक्रमe sleeping
	 * on the semaphore
	 */
	अगर (!ieee->proto_started) अणु
		prपूर्णांकk("==========oh driver down return\n");
		वापस;
	पूर्ण
	mutex_lock(&ieee->wx_mutex);

	अगर (ieee->current_network.ssid_len == 0) अणु
		म_नकल(ieee->current_network.ssid, IEEE80211_DEFAULT_TX_ESSID);
		ieee->current_network.ssid_len = म_माप(IEEE80211_DEFAULT_TX_ESSID);
		ieee->ssid_set = 1;
	पूर्ण

	/* check अगर we have this cell in our network list */
	ieee80211_sofपंचांगac_check_all_nets(ieee);

//	अगर((IS_DOT11D_ENABLE(ieee)) && (ieee->state == IEEE80211_NOLINK))
	अगर (ieee->state == IEEE80211_NOLINK)
		ieee->current_network.channel = 6;
	/* अगर not then the state is not linked. Maybe the user चयनed to
	 * ad-hoc mode just after being in monitor mode, or just after
	 * being very few समय in managed mode (so the card have had no
	 * समय to scan all the chans..) or we have just run up the अगरace
	 * after setting ad-hoc mode. So we have to give another try..
	 * Here, in ibss mode, should be safe to करो this without extra care
	 * (in bss mode we had to make sure no-one tryed to associate when
	 * we had just checked the ieee->state and we was going to start the
	 * scan) beacause in ibss mode the ieee80211_new_net function, when
	 * finds a good net, just set the ieee->state to IEEE80211_LINKED,
	 * so, at worst, we waste a bit of समय to initiate an unneeded syncro
	 * scan, that will stop at the first round because it sees the state
	 * associated.
	 */
	अगर (ieee->state == IEEE80211_NOLINK)
		ieee80211_start_scan_syncro(ieee);

	/* the network definitively is not here.. create a new cell */
	अगर (ieee->state == IEEE80211_NOLINK) अणु
		prपूर्णांकk("creating new IBSS cell\n");
		अगर (!ieee->wap_set)
			eth_अक्रमom_addr(ieee->current_network.bssid);

		अगर (ieee->modulation & IEEE80211_CCK_MODULATION) अणु
			ieee->current_network.rates_len = 4;

			ieee->current_network.rates[0] = IEEE80211_BASIC_RATE_MASK | IEEE80211_CCK_RATE_1MB;
			ieee->current_network.rates[1] = IEEE80211_BASIC_RATE_MASK | IEEE80211_CCK_RATE_2MB;
			ieee->current_network.rates[2] = IEEE80211_BASIC_RATE_MASK | IEEE80211_CCK_RATE_5MB;
			ieee->current_network.rates[3] = IEEE80211_BASIC_RATE_MASK | IEEE80211_CCK_RATE_11MB;
		पूर्ण अन्यथा अणु
			ieee->current_network.rates_len = 0;
		पूर्ण
		अगर (ieee->modulation & IEEE80211_OFDM_MODULATION) अणु
			ieee->current_network.rates_ex_len = 8;

			ieee->current_network.rates_ex[0] = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_6MB;
			ieee->current_network.rates_ex[1] = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_9MB;
			ieee->current_network.rates_ex[2] = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_12MB;
			ieee->current_network.rates_ex[3] = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_18MB;
			ieee->current_network.rates_ex[4] = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_24MB;
			ieee->current_network.rates_ex[5] = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_36MB;
			ieee->current_network.rates_ex[6] = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_48MB;
			ieee->current_network.rates_ex[7] = IEEE80211_BASIC_RATE_MASK | IEEE80211_OFDM_RATE_54MB;

			ieee->rate = 108;
		पूर्ण अन्यथा अणु
			ieee->current_network.rates_ex_len = 0;
			ieee->rate = 22;
		पूर्ण

		// By शेष, WMM function will be disabled in IBSS mode
		ieee->current_network.QoS_Enable = 0;
		ieee->SetWirelessMode(ieee->dev, IEEE_G);
		ieee->current_network.atim_winकरोw = 0;
		ieee->current_network.capability = WLAN_CAPABILITY_IBSS;
		अगर (ieee->लघु_slot)
			ieee->current_network.capability |= WLAN_CAPABILITY_SHORT_SLOT;
	पूर्ण

	ieee->state = IEEE80211_LINKED;

	ieee->set_chan(ieee->dev, ieee->current_network.channel);
	ieee->link_change(ieee->dev);

	notअगरy_wx_assoc_event(ieee);

	ieee80211_start_send_beacons(ieee);

	अगर (ieee->data_hard_resume)
		ieee->data_hard_resume(ieee->dev);
	netअगर_carrier_on(ieee->dev);

	mutex_unlock(&ieee->wx_mutex);
पूर्ण

अंतरभूत व्योम ieee80211_start_ibss(काष्ठा ieee80211_device *ieee)
अणु
	schedule_delayed_work(&ieee->start_ibss_wq, 150);
पूर्ण

/* this is called only in user context, with wx_mutex held */
व्योम ieee80211_start_bss(काष्ठा ieee80211_device *ieee)
अणु
	अचिन्हित दीर्घ flags;
	//
	// Ref: 802.11d 11.1.3.3
	// STA shall not start a BSS unless properly क्रमmed Beacon frame including a Country IE.
	//
	अगर (IS_DOT11D_ENABLE(ieee) && !IS_COUNTRY_IE_VALID(ieee)) अणु
		अगर (!ieee->bGlobalDoमुख्य)
			वापस;
	पूर्ण
	/* check अगर we have alपढ़ोy found the net we
	 * are पूर्णांकerested in (अगर any).
	 * अगर not (we are disassociated and we are not
	 * in associating / authenticating phase) start the background scanning.
	 */
	ieee80211_sofपंचांगac_check_all_nets(ieee);

	/* ensure no-one start an associating process (thus setting
	 * the ieee->state to ieee80211_ASSOCIATING) जबतक we
	 * have just checked it and we are going to enable scan.
	 * The ieee80211_new_net function is always called with
	 * lock held (from both ieee80211_sofपंचांगac_check_all_nets and
	 * the rx path), so we cannot be in the middle of such function
	 */
	spin_lock_irqsave(&ieee->lock, flags);

	अगर (ieee->state == IEEE80211_NOLINK) अणु
		ieee->actscanning = true;
		ieee80211_start_scan(ieee);
	पूर्ण
	spin_unlock_irqrestore(&ieee->lock, flags);
पूर्ण

/* called only in userspace context */
व्योम ieee80211_disassociate(काष्ठा ieee80211_device *ieee)
अणु
	netअगर_carrier_off(ieee->dev);
	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_TX_QUEUE)
		ieee80211_reset_queue(ieee);

	अगर (ieee->data_hard_stop)
		ieee->data_hard_stop(ieee->dev);
	अगर (IS_DOT11D_ENABLE(ieee))
		करोt11d_reset(ieee);
	ieee->state = IEEE80211_NOLINK;
	ieee->is_set_key = false;
	ieee->link_change(ieee->dev);
	//HTSetConnectBwMode(ieee, HT_CHANNEL_WIDTH_20, HT_EXTCHNL_OFFSET_NO_EXT);
	notअगरy_wx_assoc_event(ieee);
पूर्ण
EXPORT_SYMBOL(ieee80211_disassociate);

अटल व्योम ieee80211_associate_retry_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा ieee80211_device *ieee = container_of(dwork, काष्ठा ieee80211_device, associate_retry_wq);
	अचिन्हित दीर्घ flags;

	mutex_lock(&ieee->wx_mutex);
	अगर (!ieee->proto_started)
		जाओ निकास;

	अगर (ieee->state != IEEE80211_ASSOCIATING_RETRY)
		जाओ निकास;

	/* until we करो not set the state to IEEE80211_NOLINK
	* there are no possibility to have someone अन्यथा trying
	* to start an association procedure (we get here with
	* ieee->state = IEEE80211_ASSOCIATING).
	* When we set the state to IEEE80211_NOLINK it is possible
	* that the RX path run an attempt to associate, but
	* both ieee80211_sofपंचांगac_check_all_nets and the
	* RX path works with ieee->lock held so there are no
	* problems. If we are still disassociated then start a scan.
	* the lock here is necessary to ensure no one try to start
	* an association procedure when we have just checked the
	* state and we are going to start the scan.
	*/
	ieee->state = IEEE80211_NOLINK;

	ieee80211_sofपंचांगac_check_all_nets(ieee);

	spin_lock_irqsave(&ieee->lock, flags);

	अगर (ieee->state == IEEE80211_NOLINK)
		ieee80211_start_scan(ieee);

	spin_unlock_irqrestore(&ieee->lock, flags);

निकास:
	mutex_unlock(&ieee->wx_mutex);
पूर्ण

काष्ठा sk_buff *ieee80211_get_beacon_(काष्ठा ieee80211_device *ieee)
अणु
	u8 broadcast_addr[] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_probe_response *b;

	skb = ieee80211_probe_resp(ieee, broadcast_addr);

	अगर (!skb)
		वापस शून्य;

	b = (काष्ठा ieee80211_probe_response *)skb->data;
	b->header.frame_ctl = cpu_to_le16(IEEE80211_STYPE_BEACON);

	वापस skb;
पूर्ण

काष्ठा sk_buff *ieee80211_get_beacon(काष्ठा ieee80211_device *ieee)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_probe_response *b;

	skb = ieee80211_get_beacon_(ieee);
	अगर (!skb)
		वापस शून्य;

	b = (काष्ठा ieee80211_probe_response *)skb->data;
	b->header.seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

	अगर (ieee->seq_ctrl[0] == 0xFFF)
		ieee->seq_ctrl[0] = 0;
	अन्यथा
		ieee->seq_ctrl[0]++;

	वापस skb;
पूर्ण
EXPORT_SYMBOL(ieee80211_get_beacon);

व्योम ieee80211_sofपंचांगac_stop_protocol(काष्ठा ieee80211_device *ieee)
अणु
	ieee->sync_scan_hurryup = 1;
	mutex_lock(&ieee->wx_mutex);
	ieee80211_stop_protocol(ieee);
	mutex_unlock(&ieee->wx_mutex);
पूर्ण
EXPORT_SYMBOL(ieee80211_sofपंचांगac_stop_protocol);

व्योम ieee80211_stop_protocol(काष्ठा ieee80211_device *ieee)
अणु
	अगर (!ieee->proto_started)
		वापस;

	ieee->proto_started = 0;

	ieee80211_stop_send_beacons(ieee);
	del_समयr_sync(&ieee->associate_समयr);
	cancel_delayed_work(&ieee->associate_retry_wq);
	cancel_delayed_work(&ieee->start_ibss_wq);
	ieee80211_stop_scan(ieee);

	ieee80211_disassociate(ieee);
	RemoveAllTS(ieee); //added as we disconnect from the previous BSS, Remove all TS
पूर्ण

व्योम ieee80211_sofपंचांगac_start_protocol(काष्ठा ieee80211_device *ieee)
अणु
	ieee->sync_scan_hurryup = 0;
	mutex_lock(&ieee->wx_mutex);
	ieee80211_start_protocol(ieee);
	mutex_unlock(&ieee->wx_mutex);
पूर्ण
EXPORT_SYMBOL(ieee80211_sofपंचांगac_start_protocol);

व्योम ieee80211_start_protocol(काष्ठा ieee80211_device *ieee)
अणु
	लघु ch = 0;
	पूर्णांक i = 0;

	अगर (ieee->proto_started)
		वापस;

	ieee->proto_started = 1;

	अगर (ieee->current_network.channel == 0) अणु
		करो अणु
			ch++;
			अगर (ch > MAX_CHANNEL_NUMBER)
				वापस; /* no channel found */
		पूर्ण जबतक (!GET_DOT11D_INFO(ieee)->channel_map[ch]);
		ieee->current_network.channel = ch;
	पूर्ण

	अगर (ieee->current_network.beacon_पूर्णांकerval == 0)
		ieee->current_network.beacon_पूर्णांकerval = 100;
//	prपूर्णांकk("===>%s(), chan:%d\n", __func__, ieee->current_network.channel);
//	ieee->set_chan(ieee->dev,ieee->current_network.channel);

	क्रम (i = 0; i < 17; i++) अणु
		ieee->last_rxseq_num[i] = -1;
		ieee->last_rxfrag_num[i] = -1;
		ieee->last_packet_समय[i] = 0;
	पूर्ण

	ieee->init_wmmparam_flag = 0;//reinitialize AC_xx_PARAM रेजिस्टरs.

	/* अगर the user set the MAC of the ad-hoc cell and then
	 * चयन to managed mode, shall we  make sure that association
	 * attempts करोes not fail just because the user provide the essid
	 * and the nic is still checking क्रम the AP MAC ??
	 */
	अगर (ieee->iw_mode == IW_MODE_INFRA)
		ieee80211_start_bss(ieee);

	अन्यथा अगर (ieee->iw_mode == IW_MODE_ADHOC)
		ieee80211_start_ibss(ieee);

	अन्यथा अगर (ieee->iw_mode == IW_MODE_MASTER)
		ieee80211_start_master_bss(ieee);

	अन्यथा अगर (ieee->iw_mode == IW_MODE_MONITOR)
		ieee80211_start_monitor_mode(ieee);
पूर्ण

#घोषणा DRV_NAME  "Ieee80211"
व्योम ieee80211_sofपंचांगac_init(काष्ठा ieee80211_device *ieee)
अणु
	पूर्णांक i;
	स_रखो(&ieee->current_network, 0, माप(काष्ठा ieee80211_network));

	ieee->state = IEEE80211_NOLINK;
	ieee->sync_scan_hurryup = 0;
	क्रम (i = 0; i < 5; i++)
		ieee->seq_ctrl[i] = 0;

	ieee->करोt11d_info = kzalloc(माप(काष्ठा rt_करोt11d_info), GFP_KERNEL);
	अगर (!ieee->करोt11d_info)
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "can't alloc memory for DOT11D\n");
	//added क्रम  AP roaming
	ieee->LinkDetectInfo.SlotNum = 2;
	ieee->LinkDetectInfo.NumRecvBcnInPeriod = 0;
	ieee->LinkDetectInfo.NumRecvDataInPeriod = 0;

	ieee->assoc_id = 0;
	ieee->queue_stop = 0;
	ieee->scanning = 0;
	ieee->sofपंचांगac_features = 0; //so IEEE2100-like driver are happy
	ieee->wap_set = 0;
	ieee->ssid_set = 0;
	ieee->proto_started = 0;
	ieee->basic_rate = IEEE80211_DEFAULT_BASIC_RATE;
	ieee->rate = 22;
	ieee->ps = IEEE80211_PS_DISABLED;
	ieee->sta_sleep = 0;
	ieee->Regकरोt11HTOperationalRateSet[0] = 0xff;//support MCS 0~7
	ieee->Regकरोt11HTOperationalRateSet[1] = 0xff;//support MCS 8~15
	ieee->Regकरोt11HTOperationalRateSet[4] = 0x01;
	//added by amy
	ieee->actscanning = false;
	ieee->beinretry = false;
	ieee->is_set_key = false;
	init_mgmt_queue(ieee);

	ieee->sta_edca_param[0] = 0x0000A403;
	ieee->sta_edca_param[1] = 0x0000A427;
	ieee->sta_edca_param[2] = 0x005E4342;
	ieee->sta_edca_param[3] = 0x002F3262;
	ieee->aggregation = true;
	ieee->enable_rx_imm_BA = true;
	ieee->tx_pending.txb = शून्य;

	समयr_setup(&ieee->associate_समयr, ieee80211_associate_पात_cb, 0);

	समयr_setup(&ieee->beacon_समयr, ieee80211_send_beacon_cb, 0);

	INIT_DELAYED_WORK(&ieee->start_ibss_wq, ieee80211_start_ibss_wq);
	INIT_WORK(&ieee->associate_complete_wq, ieee80211_associate_complete_wq);
	INIT_WORK(&ieee->associate_procedure_wq, ieee80211_associate_procedure_wq);
	INIT_DELAYED_WORK(&ieee->sofपंचांगac_scan_wq, ieee80211_sofपंचांगac_scan_wq);
	INIT_DELAYED_WORK(&ieee->associate_retry_wq, ieee80211_associate_retry_wq);
	INIT_WORK(&ieee->wx_sync_scan_wq, ieee80211_wx_sync_scan_wq);

	mutex_init(&ieee->wx_mutex);
	mutex_init(&ieee->scan_mutex);

	spin_lock_init(&ieee->mgmt_tx_lock);
	spin_lock_init(&ieee->beacon_lock);

	tasklet_setup(&ieee->ps_task, ieee80211_sta_ps);
पूर्ण

व्योम ieee80211_sofपंचांगac_मुक्त(काष्ठा ieee80211_device *ieee)
अणु
	mutex_lock(&ieee->wx_mutex);
	kमुक्त(ieee->करोt11d_info);
	ieee->करोt11d_info = शून्य;
	del_समयr_sync(&ieee->associate_समयr);

	cancel_delayed_work(&ieee->associate_retry_wq);

	mutex_unlock(&ieee->wx_mutex);
पूर्ण

/********************************************************
 * Start of WPA code.                                   *
 * this is stolen from the ipw2200 driver               *
 ********************************************************/
अटल पूर्णांक ieee80211_wpa_enable(काष्ठा ieee80211_device *ieee, पूर्णांक value)
अणु
	/* This is called when wpa_supplicant loads and बंदs the driver
	 * पूर्णांकerface. */
	prपूर्णांकk("%s WPA\n", value ? "enabling" : "disabling");
	ieee->wpa_enabled = value;
	वापस 0;
पूर्ण

अटल व्योम ieee80211_wpa_assoc_frame(काष्ठा ieee80211_device *ieee,
				      अक्षर *wpa_ie, पूर्णांक wpa_ie_len)
अणु
	/* make sure WPA is enabled */
	ieee80211_wpa_enable(ieee, 1);

	ieee80211_disassociate(ieee);
पूर्ण

अटल पूर्णांक ieee80211_wpa_mlme(काष्ठा ieee80211_device *ieee, पूर्णांक command, पूर्णांक reason)
अणु
	पूर्णांक ret = 0;

	चयन (command) अणु
	हाल IEEE_MLME_STA_DEAUTH:
		// silently ignore
		अवरोध;

	हाल IEEE_MLME_STA_DISASSOC:
		ieee80211_disassociate(ieee);
		अवरोध;

	शेष:
		prपूर्णांकk("Unknown MLME request: %d\n", command);
		ret = -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_wpa_set_wpa_ie(काष्ठा ieee80211_device *ieee,
			      काष्ठा ieee_param *param, पूर्णांक plen)
अणु
	u8 *buf;

	अगर (param->u.wpa_ie.len > MAX_WPA_IE_LEN)
		वापस -EINVAL;

	अगर (param->u.wpa_ie.len) अणु
		buf = kmemdup(param->u.wpa_ie.data, param->u.wpa_ie.len,
			      GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;

		kमुक्त(ieee->wpa_ie);
		ieee->wpa_ie = buf;
		ieee->wpa_ie_len = param->u.wpa_ie.len;
	पूर्ण अन्यथा अणु
		kमुक्त(ieee->wpa_ie);
		ieee->wpa_ie = शून्य;
		ieee->wpa_ie_len = 0;
	पूर्ण

	ieee80211_wpa_assoc_frame(ieee, ieee->wpa_ie, ieee->wpa_ie_len);
	वापस 0;
पूर्ण

#घोषणा AUTH_ALG_OPEN_SYSTEM			0x1
#घोषणा AUTH_ALG_SHARED_KEY			0x2

अटल पूर्णांक ieee80211_wpa_set_auth_algs(काष्ठा ieee80211_device *ieee, पूर्णांक value)
अणु
	काष्ठा ieee80211_security sec = अणु
		.flags = SEC_AUTH_MODE,
	पूर्ण;

	अगर (value & AUTH_ALG_SHARED_KEY) अणु
		sec.auth_mode = WLAN_AUTH_SHARED_KEY;
		ieee->खोलो_wep = 0;
		ieee->auth_mode = 1;
	पूर्ण अन्यथा अगर (value & AUTH_ALG_OPEN_SYSTEM) अणु
		sec.auth_mode = WLAN_AUTH_OPEN;
		ieee->खोलो_wep = 1;
		ieee->auth_mode = 0;
	पूर्ण अन्यथा अगर (value & IW_AUTH_ALG_LEAP) अणु
		sec.auth_mode = WLAN_AUTH_LEAP;
		ieee->खोलो_wep = 1;
		ieee->auth_mode = 2;
	पूर्ण

	अगर (ieee->set_security)
		ieee->set_security(ieee->dev, &sec);
	//अन्यथा
	//	ret = -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_wpa_set_param(काष्ठा ieee80211_device *ieee, u8 name, u32 value)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	चयन (name) अणु
	हाल IEEE_PARAM_WPA_ENABLED:
		ret = ieee80211_wpa_enable(ieee, value);
		अवरोध;

	हाल IEEE_PARAM_TKIP_COUNTERMEASURES:
		ieee->tkip_countermeasures = value;
		अवरोध;

	हाल IEEE_PARAM_DROP_UNENCRYPTED: अणु
		/* HACK:
		 *
		 * wpa_supplicant calls set_wpa_enabled when the driver
		 * is loaded and unloaded, regardless of अगर WPA is being
		 * used.  No other calls are made which can be used to
		 * determine अगर encryption will be used or not prior to
		 * association being expected.  If encryption is not being
		 * used, drop_unencrypted is set to false, अन्यथा true -- we
		 * can use this to determine अगर the CAP_PRIVACY_ON bit should
		 * be set.
		 */
		काष्ठा ieee80211_security sec = अणु
			.flags = SEC_ENABLED,
			.enabled = value,
		पूर्ण;
		ieee->drop_unencrypted = value;
		/* We only change SEC_LEVEL क्रम खोलो mode. Others
		 * are set by ipw_wpa_set_encryption.
		 */
		अगर (!value) अणु
			sec.flags |= SEC_LEVEL;
			sec.level = SEC_LEVEL_0;
		पूर्ण अन्यथा अणु
			sec.flags |= SEC_LEVEL;
			sec.level = SEC_LEVEL_1;
		पूर्ण
		अगर (ieee->set_security)
			ieee->set_security(ieee->dev, &sec);
		अवरोध;
	पूर्ण

	हाल IEEE_PARAM_PRIVACY_INVOKED:
		ieee->privacy_invoked = value;
		अवरोध;

	हाल IEEE_PARAM_AUTH_ALGS:
		ret = ieee80211_wpa_set_auth_algs(ieee, value);
		अवरोध;

	हाल IEEE_PARAM_IEEE_802_1X:
		ieee->ieee802_1x = value;
		अवरोध;
	हाल IEEE_PARAM_WPAX_SELECT:
		// added क्रम WPA2 mixed mode
		spin_lock_irqsave(&ieee->wpax_suitlist_lock, flags);
		ieee->wpax_type_set = 1;
		ieee->wpax_type_notअगरy = value;
		spin_unlock_irqrestore(&ieee->wpax_suitlist_lock, flags);
		अवरोध;

	शेष:
		prपूर्णांकk("Unknown WPA param: %d\n", name);
		ret = -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

/* implementation borrowed from hostap driver */
अटल पूर्णांक ieee80211_wpa_set_encryption(काष्ठा ieee80211_device *ieee,
				  काष्ठा ieee_param *param, पूर्णांक param_len)
अणु
	पूर्णांक ret = 0;
	स्थिर अक्षर *module = शून्य;

	काष्ठा ieee80211_crypto_ops *ops = शून्य;
	काष्ठा ieee80211_crypt_data **crypt;

	काष्ठा ieee80211_security sec = अणु
		.flags = 0,
	पूर्ण;

	param->u.crypt.err = 0;
	param->u.crypt.alg[IEEE_CRYPT_ALG_NAME_LEN - 1] = '\0';

	अगर (param_len !=
	    (पूर्णांक)((अक्षर *)param->u.crypt.key - (अक्षर *)param) +
	    param->u.crypt.key_len) अणु
		prपूर्णांकk("Len mismatch %d, %d\n", param_len,
			       param->u.crypt.key_len);
		वापस -EINVAL;
	पूर्ण
	अगर (is_broadcast_ether_addr(param->sta_addr)) अणु
		अगर (param->u.crypt.idx >= WEP_KEYS)
			वापस -EINVAL;
		crypt = &ieee->crypt[param->u.crypt.idx];
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (म_भेद(param->u.crypt.alg, "none") == 0) अणु
		अगर (crypt) अणु
			sec.enabled = 0;
			// FIXME FIXME
			//sec.encrypt = 0;
			sec.level = SEC_LEVEL_0;
			sec.flags |= SEC_ENABLED | SEC_LEVEL;
			ieee80211_crypt_delayed_deinit(ieee, crypt);
		पूर्ण
		जाओ करोne;
	पूर्ण
	sec.enabled = 1;
// FIXME FIXME
//	sec.encrypt = 1;
	sec.flags |= SEC_ENABLED;

	/* IPW HW cannot build TKIP MIC, host decryption still needed. */
	अगर (!(ieee->host_encrypt || ieee->host_decrypt) &&
	    म_भेद(param->u.crypt.alg, "TKIP"))
		जाओ skip_host_crypt;

	//set WEP40 first, it will be modअगरied according to WEP104 or WEP40 at other place
	अगर (!म_भेद(param->u.crypt.alg, "WEP"))
		module = "ieee80211_crypt_wep";
	अन्यथा अगर (!म_भेद(param->u.crypt.alg, "TKIP"))
		module = "ieee80211_crypt_tkip";
	अन्यथा अगर (!म_भेद(param->u.crypt.alg, "CCMP"))
		module = "ieee80211_crypt_ccmp";
	अगर (module)
		ops = try_then_request_module(ieee80211_get_crypto_ops(param->u.crypt.alg),
					      module);
	अगर (!ops) अणु
		prपूर्णांकk("unknown crypto alg '%s'\n", param->u.crypt.alg);
		param->u.crypt.err = IEEE_CRYPT_ERR_UNKNOWN_ALG;
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (!*crypt || (*crypt)->ops != ops) अणु
		काष्ठा ieee80211_crypt_data *new_crypt;

		ieee80211_crypt_delayed_deinit(ieee, crypt);

		new_crypt = kzalloc(माप(*new_crypt), GFP_KERNEL);
		अगर (!new_crypt) अणु
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण
		new_crypt->ops = ops;
		अगर (new_crypt->ops && try_module_get(new_crypt->ops->owner))
			new_crypt->priv =
				new_crypt->ops->init(param->u.crypt.idx);

		अगर (!new_crypt->priv) अणु
			kमुक्त(new_crypt);
			param->u.crypt.err = IEEE_CRYPT_ERR_CRYPT_INIT_FAILED;
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण

		*crypt = new_crypt;
	पूर्ण

	अगर (param->u.crypt.key_len > 0 && (*crypt)->ops->set_key &&
	    (*crypt)->ops->set_key(param->u.crypt.key,
				   param->u.crypt.key_len, param->u.crypt.seq,
				   (*crypt)->priv) < 0) अणु
		prपूर्णांकk("key setting failed\n");
		param->u.crypt.err = IEEE_CRYPT_ERR_KEY_SET_FAILED;
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

 skip_host_crypt:
	अगर (param->u.crypt.set_tx) अणु
		ieee->tx_keyidx = param->u.crypt.idx;
		sec.active_key = param->u.crypt.idx;
		sec.flags |= SEC_ACTIVE_KEY;
	पूर्ण अन्यथा अणु
		sec.flags &= ~SEC_ACTIVE_KEY;
	पूर्ण
	स_नकल(sec.keys[param->u.crypt.idx],
	       param->u.crypt.key,
	       param->u.crypt.key_len);
	sec.key_sizes[param->u.crypt.idx] = param->u.crypt.key_len;
	sec.flags |= (1 << param->u.crypt.idx);

	अगर (म_भेद(param->u.crypt.alg, "WEP") == 0) अणु
		sec.flags |= SEC_LEVEL;
		sec.level = SEC_LEVEL_1;
	पूर्ण अन्यथा अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0) अणु
		sec.flags |= SEC_LEVEL;
		sec.level = SEC_LEVEL_2;
	पूर्ण अन्यथा अगर (म_भेद(param->u.crypt.alg, "CCMP") == 0) अणु
		sec.flags |= SEC_LEVEL;
		sec.level = SEC_LEVEL_3;
	पूर्ण
 करोne:
	अगर (ieee->set_security)
		ieee->set_security(ieee->dev, &sec);

	/* Do not reset port अगर card is in Managed mode since resetting will
	 * generate new IEEE 802.11 authentication which may end up in looping
	 * with IEEE 802.1X.  If your hardware requires a reset after WEP
	 * configuration (क्रम example... Prism2), implement the reset_port in
	 * the callbacks काष्ठाures used to initialize the 802.11 stack. */
	अगर (ieee->reset_on_keychange &&
	    ieee->iw_mode != IW_MODE_INFRA &&
	    ieee->reset_port &&
	    ieee->reset_port(ieee->dev)) अणु
		prपूर्णांकk("reset_port failed\n");
		param->u.crypt.err = IEEE_CRYPT_ERR_CARD_CONF_FAILED;
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *ieee80211_disassociate_skb(काष्ठा ieee80211_network *beacon,
							 काष्ठा ieee80211_device *ieee,
							 u8	asRsn)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_disassoc *disass;

	skb = dev_alloc_skb(माप(काष्ठा ieee80211_disassoc));
	अगर (!skb)
		वापस शून्य;

	disass = skb_put(skb, माप(काष्ठा ieee80211_disassoc));
	disass->header.frame_ctl = cpu_to_le16(IEEE80211_STYPE_DISASSOC);
	disass->header.duration_id = 0;

	स_नकल(disass->header.addr1, beacon->bssid, ETH_ALEN);
	स_नकल(disass->header.addr2, ieee->dev->dev_addr, ETH_ALEN);
	स_नकल(disass->header.addr3, beacon->bssid, ETH_ALEN);

	disass->reason = cpu_to_le16(asRsn);
	वापस skb;
पूर्ण

व्योम
SendDisassociation(काष्ठा ieee80211_device *ieee,
		   u8			   *asSta,
		   u8			    asRsn
)
अणु
	काष्ठा ieee80211_network *beacon = &ieee->current_network;
	काष्ठा sk_buff *skb;

	skb = ieee80211_disassociate_skb(beacon, ieee, asRsn);
	अगर (skb) अणु
		sofपंचांगac_mgmt_xmit(skb, ieee);
		//dev_kमुक्त_skb_any(skb);//edit by thomas
	पूर्ण
पूर्ण
EXPORT_SYMBOL(SendDisassociation);

पूर्णांक ieee80211_wpa_supplicant_ioctl(काष्ठा ieee80211_device *ieee, काष्ठा iw_poपूर्णांक *p)
अणु
	काष्ठा ieee_param *param;
	पूर्णांक ret = 0;

	mutex_lock(&ieee->wx_mutex);
	//IEEE_DEBUG_INFO("wpa_supplicant: len=%d\n", p->length);

	अगर (p->length < माप(काष्ठा ieee_param) || !p->poपूर्णांकer) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	param = memdup_user(p->poपूर्णांकer, p->length);
	अगर (IS_ERR(param)) अणु
		ret = PTR_ERR(param);
		जाओ out;
	पूर्ण

	चयन (param->cmd) अणु
	हाल IEEE_CMD_SET_WPA_PARAM:
		ret = ieee80211_wpa_set_param(ieee, param->u.wpa_param.name,
					param->u.wpa_param.value);
		अवरोध;

	हाल IEEE_CMD_SET_WPA_IE:
		ret = ieee80211_wpa_set_wpa_ie(ieee, param, p->length);
		अवरोध;

	हाल IEEE_CMD_SET_ENCRYPTION:
		ret = ieee80211_wpa_set_encryption(ieee, param, p->length);
		अवरोध;

	हाल IEEE_CMD_MLME:
		ret = ieee80211_wpa_mlme(ieee, param->u.mlme.command,
				   param->u.mlme.reason_code);
		अवरोध;

	शेष:
		prपूर्णांकk("Unknown WPA supplicant request: %d\n", param->cmd);
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	अगर (ret == 0 && copy_to_user(p->poपूर्णांकer, param, p->length))
		ret = -EFAULT;

	kमुक्त(param);
out:
	mutex_unlock(&ieee->wx_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ieee80211_wpa_supplicant_ioctl);

व्योम notअगरy_wx_assoc_event(काष्ठा ieee80211_device *ieee)
अणु
	जोड़ iwreq_data wrqu;

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	अगर (ieee->state == IEEE80211_LINKED)
		स_नकल(wrqu.ap_addr.sa_data, ieee->current_network.bssid, ETH_ALEN);
	अन्यथा
		eth_zero_addr(wrqu.ap_addr.sa_data);
	wireless_send_event(ieee->dev, SIOCGIWAP, &wrqu, शून्य);
पूर्ण
EXPORT_SYMBOL(notअगरy_wx_assoc_event);
