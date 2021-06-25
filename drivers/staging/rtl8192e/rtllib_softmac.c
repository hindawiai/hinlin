<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* IEEE 802.11 SoftMAC layer
 * Copyright (c) 2005 Andrea Merello <andrea.merello@gmail.com>
 *
 * Mostly extracted from the rtl8180-sa2400 driver क्रम the
 * in-kernel generic ieee802.11 stack.
 *
 * Few lines might be stolen from other part of the rtllib
 * stack. Copyright who own it's copyright
 *
 * WPA code stolen from the ipw2200 driver.
 * Copyright who own it's copyright.
 */
#समावेश "rtllib.h"

#समावेश <linux/अक्रमom.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ieee80211.h>
#समावेश "dot11d.h"

अटल व्योम rtllib_sta_wakeup(काष्ठा rtllib_device *ieee, लघु nl);


अटल लघु rtllib_is_54g(काष्ठा rtllib_network *net)
अणु
	वापस (net->rates_ex_len > 0) || (net->rates_len > 4);
पूर्ण

/* वापसs the total length needed क्रम placing the RATE MFIE
 * tag and the EXTENDED RATE MFIE tag अगर needed.
 * It encludes two bytes per tag क्रम the tag itself and its len
 */
अटल अचिन्हित पूर्णांक rtllib_MFIE_rate_len(काष्ठा rtllib_device *ieee)
अणु
	अचिन्हित पूर्णांक rate_len = 0;

	अगर (ieee->modulation & RTLLIB_CCK_MODULATION)
		rate_len = RTLLIB_CCK_RATE_LEN + 2;

	अगर (ieee->modulation & RTLLIB_OFDM_MODULATION)

		rate_len += RTLLIB_OFDM_RATE_LEN + 2;

	वापस rate_len;
पूर्ण

/* place the MFIE rate, tag to the memory (द्विगुन) poपूर्णांकed.
 * Then it updates the poपूर्णांकer so that
 * it poपूर्णांकs after the new MFIE tag added.
 */
अटल व्योम rtllib_MFIE_Brate(काष्ठा rtllib_device *ieee, u8 **tag_p)
अणु
	u8 *tag = *tag_p;

	अगर (ieee->modulation & RTLLIB_CCK_MODULATION) अणु
		*tag++ = MFIE_TYPE_RATES;
		*tag++ = 4;
		*tag++ = RTLLIB_BASIC_RATE_MASK | RTLLIB_CCK_RATE_1MB;
		*tag++ = RTLLIB_BASIC_RATE_MASK | RTLLIB_CCK_RATE_2MB;
		*tag++ = RTLLIB_BASIC_RATE_MASK | RTLLIB_CCK_RATE_5MB;
		*tag++ = RTLLIB_BASIC_RATE_MASK | RTLLIB_CCK_RATE_11MB;
	पूर्ण

	/* We may add an option क्रम custom rates that specअगरic HW
	 * might support
	 */
	*tag_p = tag;
पूर्ण

अटल व्योम rtllib_MFIE_Grate(काष्ठा rtllib_device *ieee, u8 **tag_p)
अणु
	u8 *tag = *tag_p;

	अगर (ieee->modulation & RTLLIB_OFDM_MODULATION) अणु
		*tag++ = MFIE_TYPE_RATES_EX;
		*tag++ = 8;
		*tag++ = RTLLIB_BASIC_RATE_MASK | RTLLIB_OFDM_RATE_6MB;
		*tag++ = RTLLIB_BASIC_RATE_MASK | RTLLIB_OFDM_RATE_9MB;
		*tag++ = RTLLIB_BASIC_RATE_MASK | RTLLIB_OFDM_RATE_12MB;
		*tag++ = RTLLIB_BASIC_RATE_MASK | RTLLIB_OFDM_RATE_18MB;
		*tag++ = RTLLIB_BASIC_RATE_MASK | RTLLIB_OFDM_RATE_24MB;
		*tag++ = RTLLIB_BASIC_RATE_MASK | RTLLIB_OFDM_RATE_36MB;
		*tag++ = RTLLIB_BASIC_RATE_MASK | RTLLIB_OFDM_RATE_48MB;
		*tag++ = RTLLIB_BASIC_RATE_MASK | RTLLIB_OFDM_RATE_54MB;
	पूर्ण
	/* We may add an option क्रम custom rates that specअगरic HW might
	 * support
	 */
	*tag_p = tag;
पूर्ण

अटल व्योम rtllib_WMM_Info(काष्ठा rtllib_device *ieee, u8 **tag_p)
अणु
	u8 *tag = *tag_p;

	*tag++ = MFIE_TYPE_GENERIC;
	*tag++ = 7;
	*tag++ = 0x00;
	*tag++ = 0x50;
	*tag++ = 0xf2;
	*tag++ = 0x02;
	*tag++ = 0x00;
	*tag++ = 0x01;
	*tag++ = MAX_SP_Len;
	*tag_p = tag;
पूर्ण

अटल व्योम rtllib_TURBO_Info(काष्ठा rtllib_device *ieee, u8 **tag_p)
अणु
	u8 *tag = *tag_p;

	*tag++ = MFIE_TYPE_GENERIC;
	*tag++ = 7;
	*tag++ = 0x00;
	*tag++ = 0xe0;
	*tag++ = 0x4c;
	*tag++ = 0x01;
	*tag++ = 0x02;
	*tag++ = 0x11;
	*tag++ = 0x00;

	*tag_p = tag;
	netdev_alert(ieee->dev, "This is enable turbo mode IE process\n");
पूर्ण

अटल व्योम enqueue_mgmt(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb)
अणु
	पूर्णांक nh;

	nh = (ieee->mgmt_queue_head + 1) % MGMT_QUEUE_NUM;

/* अगर the queue is full but we have newer frames then
 * just overग_लिखोs the oldest.
 *
 * अगर (nh == ieee->mgmt_queue_tail)
 *		वापस -1;
 */
	ieee->mgmt_queue_head = nh;
	ieee->mgmt_queue_ring[nh] = skb;

पूर्ण

अटल व्योम init_mgmt_queue(काष्ठा rtllib_device *ieee)
अणु
	ieee->mgmt_queue_tail = ieee->mgmt_queue_head = 0;
पूर्ण


u8
MgntQuery_TxRateExcludeCCKRates(काष्ठा rtllib_device *ieee)
अणु
	u16	i;
	u8	QueryRate = 0;
	u8	BasicRate;


	क्रम (i = 0; i < ieee->current_network.rates_len; i++) अणु
		BasicRate = ieee->current_network.rates[i]&0x7F;
		अगर (!rtllib_is_cck_rate(BasicRate)) अणु
			अगर (QueryRate == 0) अणु
				QueryRate = BasicRate;
			पूर्ण अन्यथा अणु
				अगर (BasicRate < QueryRate)
					QueryRate = BasicRate;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (QueryRate == 0) अणु
		QueryRate = 12;
		netdev_info(ieee->dev, "No BasicRate found!!\n");
	पूर्ण
	वापस QueryRate;
पूर्ण

अटल u8 MgntQuery_MgntFrameTxRate(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा rt_hi_throughput *pHTInfo = ieee->pHTInfo;
	u8 rate;

	अगर (pHTInfo->IOTAction & HT_IOT_ACT_MGNT_USE_CCK_6M)
		rate = 0x0c;
	अन्यथा
		rate = ieee->basic_rate & 0x7f;

	अगर (rate == 0) अणु
		अगर (ieee->mode == IEEE_A ||
		   ieee->mode == IEEE_N_5G ||
		   (ieee->mode == IEEE_N_24G && !pHTInfo->bCurSuppCCK))
			rate = 0x0c;
		अन्यथा
			rate = 0x02;
	पूर्ण

	वापस rate;
पूर्ण

अंतरभूत व्योम sofपंचांगac_mgmt_xmit(काष्ठा sk_buff *skb, काष्ठा rtllib_device *ieee)
अणु
	अचिन्हित दीर्घ flags;
	लघु single = ieee->sofपंचांगac_features & IEEE_SOFTMAC_SINGLE_QUEUE;
	काष्ठा rtllib_hdr_3addr  *header =
		(काष्ठा rtllib_hdr_3addr  *) skb->data;

	काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(skb->cb + 8);

	spin_lock_irqsave(&ieee->lock, flags);

	/* called with 2nd param 0, no mgmt lock required */
	rtllib_sta_wakeup(ieee, 0);

	अगर (le16_to_cpu(header->frame_ctl) == RTLLIB_STYPE_BEACON)
		tcb_desc->queue_index = BEACON_QUEUE;
	अन्यथा
		tcb_desc->queue_index = MGNT_QUEUE;

	अगर (ieee->disable_mgnt_queue)
		tcb_desc->queue_index = HIGH_QUEUE;

	tcb_desc->data_rate = MgntQuery_MgntFrameTxRate(ieee);
	tcb_desc->RATRIndex = 7;
	tcb_desc->bTxDisableRateFallBack = 1;
	tcb_desc->bTxUseDriverAssingedRate = 1;
	अगर (single) अणु
		अगर (ieee->queue_stop) अणु
			enqueue_mgmt(ieee, skb);
		पूर्ण अन्यथा अणु
			header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0]<<4);

			अगर (ieee->seq_ctrl[0] == 0xFFF)
				ieee->seq_ctrl[0] = 0;
			अन्यथा
				ieee->seq_ctrl[0]++;

			/* aव्योम watchकरोg triggers */
			ieee->sofपंचांगac_data_hard_start_xmit(skb, ieee->dev,
							   ieee->basic_rate);
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
		अगर (!ieee->check_nic_enough_desc(ieee->dev,
						 tcb_desc->queue_index) ||
		    skb_queue_len(&ieee->skb_रुकोQ[tcb_desc->queue_index]) ||
		    ieee->queue_stop) अणु
			/* insert the skb packet to the management queue
			 *
			 * as क्रम the completion function, it करोes not need
			 * to check it any more.
			 */
			netdev_info(ieee->dev,
			       "%s():insert to waitqueue, queue_index:%d!\n",
			       __func__, tcb_desc->queue_index);
			skb_queue_tail(&ieee->skb_रुकोQ[tcb_desc->queue_index],
				       skb);
		पूर्ण अन्यथा अणु
			ieee->sofपंचांगac_hard_start_xmit(skb, ieee->dev);
		पूर्ण
		spin_unlock_irqrestore(&ieee->mgmt_tx_lock, flags);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
sofपंचांगac_ps_mgmt_xmit(काष्ठा sk_buff *skb,
		     काष्ठा rtllib_device *ieee)
अणु
	लघु single = ieee->sofपंचांगac_features & IEEE_SOFTMAC_SINGLE_QUEUE;
	काष्ठा rtllib_hdr_3addr  *header =
		(काष्ठा rtllib_hdr_3addr  *) skb->data;
	u16 fc, type, stype;
	काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(skb->cb + 8);

	fc = le16_to_cpu(header->frame_ctl);
	type = WLAN_FC_GET_TYPE(fc);
	stype = WLAN_FC_GET_STYPE(fc);


	अगर (stype != RTLLIB_STYPE_PSPOLL)
		tcb_desc->queue_index = MGNT_QUEUE;
	अन्यथा
		tcb_desc->queue_index = HIGH_QUEUE;

	अगर (ieee->disable_mgnt_queue)
		tcb_desc->queue_index = HIGH_QUEUE;


	tcb_desc->data_rate = MgntQuery_MgntFrameTxRate(ieee);
	tcb_desc->RATRIndex = 7;
	tcb_desc->bTxDisableRateFallBack = 1;
	tcb_desc->bTxUseDriverAssingedRate = 1;
	अगर (single) अणु
		अगर (type != RTLLIB_FTYPE_CTL) अणु
			header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

			अगर (ieee->seq_ctrl[0] == 0xFFF)
				ieee->seq_ctrl[0] = 0;
			अन्यथा
				ieee->seq_ctrl[0]++;

		पूर्ण
		/* aव्योम watchकरोg triggers */
		ieee->sofपंचांगac_data_hard_start_xmit(skb, ieee->dev,
						   ieee->basic_rate);

	पूर्ण अन्यथा अणु
		अगर (type != RTLLIB_FTYPE_CTL) अणु
			header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

			अगर (ieee->seq_ctrl[0] == 0xFFF)
				ieee->seq_ctrl[0] = 0;
			अन्यथा
				ieee->seq_ctrl[0]++;
		पूर्ण
		ieee->sofपंचांगac_hard_start_xmit(skb, ieee->dev);

	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *rtllib_probe_req(काष्ठा rtllib_device *ieee)
अणु
	अचिन्हित पूर्णांक len, rate_len;
	u8 *tag;
	काष्ठा sk_buff *skb;
	काष्ठा rtllib_probe_request *req;

	len = ieee->current_network.ssid_len;

	rate_len = rtllib_MFIE_rate_len(ieee);

	skb = dev_alloc_skb(माप(काष्ठा rtllib_probe_request) +
			    2 + len + rate_len + ieee->tx_headroom);

	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, ieee->tx_headroom);

	req = skb_put(skb, माप(काष्ठा rtllib_probe_request));
	req->header.frame_ctl = cpu_to_le16(RTLLIB_STYPE_PROBE_REQ);
	req->header.duration_id = 0;

	eth_broadcast_addr(req->header.addr1);
	ether_addr_copy(req->header.addr2, ieee->dev->dev_addr);
	eth_broadcast_addr(req->header.addr3);

	tag = skb_put(skb, len + 2 + rate_len);

	*tag++ = MFIE_TYPE_SSID;
	*tag++ = len;
	स_नकल(tag, ieee->current_network.ssid, len);
	tag += len;

	rtllib_MFIE_Brate(ieee, &tag);
	rtllib_MFIE_Grate(ieee, &tag);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *rtllib_get_beacon_(काष्ठा rtllib_device *ieee);

अटल व्योम rtllib_send_beacon(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ieee->ieee_up)
		वापस;
	skb = rtllib_get_beacon_(ieee);

	अगर (skb) अणु
		sofपंचांगac_mgmt_xmit(skb, ieee);
		ieee->sofपंचांगac_stats.tx_beacons++;
	पूर्ण

	अगर (ieee->beacon_txing && ieee->ieee_up)
		mod_समयr(&ieee->beacon_समयr, jअगरfies +
			  (msecs_to_jअगरfies(ieee->current_network.beacon_पूर्णांकerval - 5)));
पूर्ण


अटल व्योम rtllib_send_beacon_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा rtllib_device *ieee =
		from_समयr(ieee, t, beacon_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ieee->beacon_lock, flags);
	rtllib_send_beacon(ieee);
	spin_unlock_irqrestore(&ieee->beacon_lock, flags);
पूर्ण

/* Enables network monitor mode, all rx packets will be received. */
व्योम rtllib_EnableNetMonitorMode(काष्ठा net_device *dev,
		bool bInitState)
अणु
	काष्ठा rtllib_device *ieee = netdev_priv_rsl(dev);

	netdev_info(dev, "========>Enter Monitor Mode\n");

	ieee->AllowAllDestAddrHandler(dev, true, !bInitState);
पूर्ण


/* Disables network monitor mode. Only packets destinated to
 * us will be received.
 */
व्योम rtllib_DisableNetMonitorMode(काष्ठा net_device *dev,
		bool bInitState)
अणु
	काष्ठा rtllib_device *ieee = netdev_priv_rsl(dev);

	netdev_info(dev, "========>Exit Monitor Mode\n");

	ieee->AllowAllDestAddrHandler(dev, false, !bInitState);
पूर्ण


/* Enables the specialized promiscuous mode required by Intel.
 * In this mode, Intel पूर्णांकends to hear traffics from/to other STAs in the
 * same BSS. Thereक्रमe we करोn't have to disable checking BSSID and we only need
 * to allow all dest. BUT: अगर we enable checking BSSID then we can't recv
 * packets from other STA.
 */
व्योम rtllib_EnableIntelPromiscuousMode(काष्ठा net_device *dev,
		bool bInitState)
अणु
	bool bFilterOutNonAssociatedBSSID = false;

	काष्ठा rtllib_device *ieee = netdev_priv_rsl(dev);

	netdev_info(dev, "========>Enter Intel Promiscuous Mode\n");

	ieee->AllowAllDestAddrHandler(dev, true, !bInitState);
	ieee->SetHwRegHandler(dev, HW_VAR_CECHK_BSSID,
			     (u8 *)&bFilterOutNonAssociatedBSSID);

	ieee->bNetPromiscuousMode = true;
पूर्ण
EXPORT_SYMBOL(rtllib_EnableIntelPromiscuousMode);


/* Disables the specialized promiscuous mode required by Intel.
 * See MgntEnableIntelPromiscuousMode क्रम detail.
 */
व्योम rtllib_DisableIntelPromiscuousMode(काष्ठा net_device *dev,
		bool bInitState)
अणु
	bool bFilterOutNonAssociatedBSSID = true;

	काष्ठा rtllib_device *ieee = netdev_priv_rsl(dev);

	netdev_info(dev, "========>Exit Intel Promiscuous Mode\n");

	ieee->AllowAllDestAddrHandler(dev, false, !bInitState);
	ieee->SetHwRegHandler(dev, HW_VAR_CECHK_BSSID,
			     (u8 *)&bFilterOutNonAssociatedBSSID);

	ieee->bNetPromiscuousMode = false;
पूर्ण
EXPORT_SYMBOL(rtllib_DisableIntelPromiscuousMode);

अटल व्योम rtllib_send_probe(काष्ठा rtllib_device *ieee, u8 is_mesh)
अणु
	काष्ठा sk_buff *skb;

	skb = rtllib_probe_req(ieee);
	अगर (skb) अणु
		sofपंचांगac_mgmt_xmit(skb, ieee);
		ieee->sofपंचांगac_stats.tx_probe_rq++;
	पूर्ण
पूर्ण


अटल व्योम rtllib_send_probe_requests(काष्ठा rtllib_device *ieee, u8 is_mesh)
अणु
	अगर (ieee->active_scan && (ieee->sofपंचांगac_features &
	    IEEE_SOFTMAC_PROBERQ)) अणु
		rtllib_send_probe(ieee, 0);
		rtllib_send_probe(ieee, 0);
	पूर्ण
पूर्ण

अटल व्योम rtllib_update_active_chan_map(काष्ठा rtllib_device *ieee)
अणु
	स_नकल(ieee->active_channel_map, GET_DOT11D_INFO(ieee)->channel_map,
	       MAX_CHANNEL_NUMBER+1);
पूर्ण

/* this perक्रमms syncro scan blocking the caller until all channels
 * in the allowed channel map has been checked.
 */
अटल व्योम rtllib_sofपंचांगac_scan_syncro(काष्ठा rtllib_device *ieee, u8 is_mesh)
अणु
	जोड़ iwreq_data wrqu;
	लघु ch = 0;

	rtllib_update_active_chan_map(ieee);

	ieee->be_scan_inprogress = true;

	mutex_lock(&ieee->scan_mutex);

	जबतक (1) अणु
		करो अणु
			ch++;
			अगर (ch > MAX_CHANNEL_NUMBER)
				जाओ out; /* scan completed */
		पूर्ण जबतक (!ieee->active_channel_map[ch]);

		/* this function can be called in two situations
		 * 1- We have चयनed to ad-hoc mode and we are
		 *    perक्रमming a complete syncro scan beक्रमe conclude
		 *    there are no पूर्णांकeresting cell and to create a
		 *    new one. In this हाल the link state is
		 *    RTLLIB_NOLINK until we found an पूर्णांकeresting cell.
		 *    If so the ieee8021_new_net, called by the RX path
		 *    will set the state to RTLLIB_LINKED, so we stop
		 *    scanning
		 * 2- We are linked and the root uses run iwlist scan.
		 *    So we चयन to RTLLIB_LINKED_SCANNING to remember
		 *    that we are still logically linked (not पूर्णांकerested in
		 *    new network events, despite क्रम updating the net list,
		 *    but we are temporarly 'unlinked' as the driver shall
		 *    not filter RX frames and the channel is changing.
		 * So the only situation in which are पूर्णांकerested is to check
		 * अगर the state become LINKED because of the #1 situation
		 */

		अगर (ieee->state == RTLLIB_LINKED)
			जाओ out;
		अगर (ieee->sync_scan_hurryup) अणु
			netdev_info(ieee->dev,
				    "============>sync_scan_hurryup out\n");
			जाओ out;
		पूर्ण

		ieee->set_chan(ieee->dev, ch);
		अगर (ieee->active_channel_map[ch] == 1)
			rtllib_send_probe_requests(ieee, 0);

		/* this prevent excessive समय रुको when we
		 * need to रुको क्रम a syncro scan to end..
		 */
		msleep_पूर्णांकerruptible_rsl(RTLLIB_SOFTMAC_SCAN_TIME);
	पूर्ण
out:
	ieee->actscanning = false;
	ieee->sync_scan_hurryup = 0;

	अगर (ieee->state >= RTLLIB_LINKED) अणु
		अगर (IS_DOT11D_ENABLE(ieee))
			करोt11d_scan_complete(ieee);
	पूर्ण
	mutex_unlock(&ieee->scan_mutex);

	ieee->be_scan_inprogress = false;

	स_रखो(&wrqu, 0, माप(wrqu));
	wireless_send_event(ieee->dev, SIOCGIWSCAN, &wrqu, शून्य);
पूर्ण

अटल व्योम rtllib_sofपंचांगac_scan_wq(व्योम *data)
अणु
	काष्ठा rtllib_device *ieee = container_of_dwork_rsl(data,
				     काष्ठा rtllib_device, sofपंचांगac_scan_wq);
	u8 last_channel = ieee->current_network.channel;

	rtllib_update_active_chan_map(ieee);

	अगर (!ieee->ieee_up)
		वापस;
	अगर (rtllib_act_scanning(ieee, true))
		वापस;

	mutex_lock(&ieee->scan_mutex);

	अगर (ieee->eRFPowerState == eRfOff) अणु
		netdev_info(ieee->dev,
			    "======>%s():rf state is eRfOff, return\n",
			    __func__);
		जाओ out1;
	पूर्ण

	करो अणु
		ieee->current_network.channel =
			(ieee->current_network.channel + 1) %
			MAX_CHANNEL_NUMBER;
		अगर (ieee->scan_watch_करोg++ > MAX_CHANNEL_NUMBER) अणु
			अगर (!ieee->active_channel_map[ieee->current_network.channel])
				ieee->current_network.channel = 6;
			जाओ out; /* no good chans */
		पूर्ण
	पूर्ण जबतक (!ieee->active_channel_map[ieee->current_network.channel]);

	अगर (ieee->scanning_जारी == 0)
		जाओ out;

	ieee->set_chan(ieee->dev, ieee->current_network.channel);

	अगर (ieee->active_channel_map[ieee->current_network.channel] == 1)
		rtllib_send_probe_requests(ieee, 0);

	schedule_delayed_work(&ieee->sofपंचांगac_scan_wq,
			      msecs_to_jअगरfies(RTLLIB_SOFTMAC_SCAN_TIME));

	mutex_unlock(&ieee->scan_mutex);
	वापस;

out:
	अगर (IS_DOT11D_ENABLE(ieee))
		करोt11d_scan_complete(ieee);
	ieee->current_network.channel = last_channel;

out1:
	ieee->actscanning = false;
	ieee->scan_watch_करोg = 0;
	ieee->scanning_जारी = 0;
	mutex_unlock(&ieee->scan_mutex);
पूर्ण



अटल व्योम rtllib_beacons_start(काष्ठा rtllib_device *ieee)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ieee->beacon_lock, flags);

	ieee->beacon_txing = 1;
	rtllib_send_beacon(ieee);

	spin_unlock_irqrestore(&ieee->beacon_lock, flags);
पूर्ण

अटल व्योम rtllib_beacons_stop(काष्ठा rtllib_device *ieee)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ieee->beacon_lock, flags);

	ieee->beacon_txing = 0;
	del_समयr_sync(&ieee->beacon_समयr);

	spin_unlock_irqrestore(&ieee->beacon_lock, flags);

पूर्ण


व्योम rtllib_stop_send_beacons(काष्ठा rtllib_device *ieee)
अणु
	अगर (ieee->stop_send_beacons)
		ieee->stop_send_beacons(ieee->dev);
	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_BEACONS)
		rtllib_beacons_stop(ieee);
पूर्ण
EXPORT_SYMBOL(rtllib_stop_send_beacons);


व्योम rtllib_start_send_beacons(काष्ठा rtllib_device *ieee)
अणु
	अगर (ieee->start_send_beacons)
		ieee->start_send_beacons(ieee->dev);
	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_BEACONS)
		rtllib_beacons_start(ieee);
पूर्ण
EXPORT_SYMBOL(rtllib_start_send_beacons);


अटल व्योम rtllib_sofपंचांगac_stop_scan(काष्ठा rtllib_device *ieee)
अणु
	mutex_lock(&ieee->scan_mutex);
	ieee->scan_watch_करोg = 0;
	अगर (ieee->scanning_जारी == 1) अणु
		ieee->scanning_जारी = 0;
		ieee->actscanning = false;

		cancel_delayed_work_sync(&ieee->sofपंचांगac_scan_wq);
	पूर्ण

	mutex_unlock(&ieee->scan_mutex);
पूर्ण

व्योम rtllib_stop_scan(काष्ठा rtllib_device *ieee)
अणु
	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_SCAN) अणु
		rtllib_sofपंचांगac_stop_scan(ieee);
	पूर्ण अन्यथा अणु
		अगर (ieee->rtllib_stop_hw_scan)
			ieee->rtllib_stop_hw_scan(ieee->dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtllib_stop_scan);

व्योम rtllib_stop_scan_syncro(काष्ठा rtllib_device *ieee)
अणु
	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_SCAN) अणु
		ieee->sync_scan_hurryup = 1;
	पूर्ण अन्यथा अणु
		अगर (ieee->rtllib_stop_hw_scan)
			ieee->rtllib_stop_hw_scan(ieee->dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtllib_stop_scan_syncro);

bool rtllib_act_scanning(काष्ठा rtllib_device *ieee, bool sync_scan)
अणु
	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_SCAN) अणु
		अगर (sync_scan)
			वापस ieee->be_scan_inprogress;
		अन्यथा
			वापस ieee->actscanning || ieee->be_scan_inprogress;
	पूर्ण अन्यथा अणु
		वापस test_bit(STATUS_SCANNING, &ieee->status);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtllib_act_scanning);

/* called with ieee->lock held */
अटल व्योम rtllib_start_scan(काष्ठा rtllib_device *ieee)
अणु
	RT_TRACE(COMP_DBG, "===>%s()\n", __func__);
	अगर (ieee->rtllib_ips_leave_wq != शून्य)
		ieee->rtllib_ips_leave_wq(ieee->dev);

	अगर (IS_DOT11D_ENABLE(ieee)) अणु
		अगर (IS_COUNTRY_IE_VALID(ieee))
			RESET_CIE_WATCHDOG(ieee);
	पूर्ण
	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_SCAN) अणु
		अगर (ieee->scanning_जारी == 0) अणु
			ieee->actscanning = true;
			ieee->scanning_जारी = 1;
			schedule_delayed_work(&ieee->sofपंचांगac_scan_wq, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ieee->rtllib_start_hw_scan)
			ieee->rtllib_start_hw_scan(ieee->dev);
	पूर्ण
पूर्ण

/* called with wx_mutex held */
व्योम rtllib_start_scan_syncro(काष्ठा rtllib_device *ieee, u8 is_mesh)
अणु
	अगर (IS_DOT11D_ENABLE(ieee)) अणु
		अगर (IS_COUNTRY_IE_VALID(ieee))
			RESET_CIE_WATCHDOG(ieee);
	पूर्ण
	ieee->sync_scan_hurryup = 0;
	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_SCAN) अणु
		rtllib_sofपंचांगac_scan_syncro(ieee, is_mesh);
	पूर्ण अन्यथा अणु
		अगर (ieee->rtllib_start_hw_scan)
			ieee->rtllib_start_hw_scan(ieee->dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtllib_start_scan_syncro);

अटल अंतरभूत काष्ठा sk_buff *
rtllib_authentication_req(काष्ठा rtllib_network *beacon,
			  काष्ठा rtllib_device *ieee,
			  पूर्णांक challengelen, u8 *daddr)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rtllib_authentication *auth;
	पूर्णांक  len;

	len = माप(काष्ठा rtllib_authentication) + challengelen +
		     ieee->tx_headroom + 4;
	skb = dev_alloc_skb(len);

	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, ieee->tx_headroom);

	auth = skb_put(skb, माप(काष्ठा rtllib_authentication));

	auth->header.frame_ctl = cpu_to_le16(RTLLIB_STYPE_AUTH);
	अगर (challengelen)
		auth->header.frame_ctl |= cpu_to_le16(RTLLIB_FCTL_WEP);

	auth->header.duration_id = cpu_to_le16(0x013a);
	ether_addr_copy(auth->header.addr1, beacon->bssid);
	ether_addr_copy(auth->header.addr2, ieee->dev->dev_addr);
	ether_addr_copy(auth->header.addr3, beacon->bssid);
	अगर (ieee->auth_mode == 0)
		auth->algorithm = WLAN_AUTH_OPEN;
	अन्यथा अगर (ieee->auth_mode == 1)
		auth->algorithm = cpu_to_le16(WLAN_AUTH_SHARED_KEY);
	अन्यथा अगर (ieee->auth_mode == 2)
		auth->algorithm = WLAN_AUTH_OPEN;
	auth->transaction = cpu_to_le16(ieee->associate_seq);
	ieee->associate_seq++;

	auth->status = cpu_to_le16(WLAN_STATUS_SUCCESS);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *rtllib_probe_resp(काष्ठा rtllib_device *ieee,
					 स्थिर u8 *dest)
अणु
	u8 *tag;
	पूर्णांक beacon_size;
	काष्ठा rtllib_probe_response *beacon_buf;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक encrypt;
	पूर्णांक atim_len, erp_len;
	काष्ठा lib80211_crypt_data *crypt;

	अक्षर *ssid = ieee->current_network.ssid;
	पूर्णांक ssid_len = ieee->current_network.ssid_len;
	पूर्णांक rate_len = ieee->current_network.rates_len+2;
	पूर्णांक rate_ex_len = ieee->current_network.rates_ex_len;
	पूर्णांक wpa_ie_len = ieee->wpa_ie_len;
	u8 erpinfo_content = 0;

	u8 *पंचांगp_ht_cap_buf = शून्य;
	u8 पंचांगp_ht_cap_len = 0;
	u8 *पंचांगp_ht_info_buf = शून्य;
	u8 पंचांगp_ht_info_len = 0;
	काष्ठा rt_hi_throughput *pHTInfo = ieee->pHTInfo;
	u8 *पंचांगp_generic_ie_buf = शून्य;
	u8 पंचांगp_generic_ie_len = 0;

	अगर (rate_ex_len > 0)
		rate_ex_len += 2;

	अगर (ieee->current_network.capability & WLAN_CAPABILITY_IBSS)
		atim_len = 4;
	अन्यथा
		atim_len = 0;

	अगर ((ieee->current_network.mode == IEEE_G) ||
	   (ieee->current_network.mode == IEEE_N_24G &&
	   ieee->pHTInfo->bCurSuppCCK)) अणु
		erp_len = 3;
		erpinfo_content = 0;
		अगर (ieee->current_network.buseprotection)
			erpinfo_content |= ERP_UseProtection;
	पूर्ण अन्यथा
		erp_len = 0;

	crypt = ieee->crypt_info.crypt[ieee->crypt_info.tx_keyidx];
	encrypt = ieee->host_encrypt && crypt && crypt->ops &&
		((म_भेद(crypt->ops->name, "R-WEP") == 0 || wpa_ie_len));
	अगर (ieee->pHTInfo->bCurrentHTSupport) अणु
		पंचांगp_ht_cap_buf = (u8 *) &(ieee->pHTInfo->SelfHTCap);
		पंचांगp_ht_cap_len = माप(ieee->pHTInfo->SelfHTCap);
		पंचांगp_ht_info_buf = (u8 *) &(ieee->pHTInfo->SelfHTInfo);
		पंचांगp_ht_info_len = माप(ieee->pHTInfo->SelfHTInfo);
		HTConकाष्ठाCapabilityElement(ieee, पंचांगp_ht_cap_buf,
					     &पंचांगp_ht_cap_len, encrypt, false);
		HTConकाष्ठाInfoElement(ieee, पंचांगp_ht_info_buf, &पंचांगp_ht_info_len,
				       encrypt);

		अगर (pHTInfo->bRegRT2RTAggregation) अणु
			पंचांगp_generic_ie_buf = ieee->pHTInfo->szRT2RTAggBuffer;
			पंचांगp_generic_ie_len =
				 माप(ieee->pHTInfo->szRT2RTAggBuffer);
			HTConकाष्ठाRT2RTAggElement(ieee, पंचांगp_generic_ie_buf,
						   &पंचांगp_generic_ie_len);
		पूर्ण
	पूर्ण

	beacon_size = माप(काष्ठा rtllib_probe_response)+2+
		ssid_len + 3 + rate_len + rate_ex_len + atim_len + erp_len
		+ wpa_ie_len + ieee->tx_headroom;
	skb = dev_alloc_skb(beacon_size);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, ieee->tx_headroom);

	beacon_buf = skb_put(skb, (beacon_size - ieee->tx_headroom));
	ether_addr_copy(beacon_buf->header.addr1, dest);
	ether_addr_copy(beacon_buf->header.addr2, ieee->dev->dev_addr);
	ether_addr_copy(beacon_buf->header.addr3, ieee->current_network.bssid);

	beacon_buf->header.duration_id = 0;
	beacon_buf->beacon_पूर्णांकerval =
		cpu_to_le16(ieee->current_network.beacon_पूर्णांकerval);
	beacon_buf->capability =
		cpu_to_le16(ieee->current_network.capability &
		WLAN_CAPABILITY_IBSS);
	beacon_buf->capability |=
		cpu_to_le16(ieee->current_network.capability &
		WLAN_CAPABILITY_SHORT_PREAMBLE);

	अगर (ieee->लघु_slot && (ieee->current_network.capability &
	    WLAN_CAPABILITY_SHORT_SLOT_TIME))
		beacon_buf->capability |=
			cpu_to_le16(WLAN_CAPABILITY_SHORT_SLOT_TIME);

	crypt = ieee->crypt_info.crypt[ieee->crypt_info.tx_keyidx];
	अगर (encrypt)
		beacon_buf->capability |= cpu_to_le16(WLAN_CAPABILITY_PRIVACY);


	beacon_buf->header.frame_ctl = cpu_to_le16(RTLLIB_STYPE_PROBE_RESP);
	beacon_buf->info_element[0].id = MFIE_TYPE_SSID;
	beacon_buf->info_element[0].len = ssid_len;

	tag = (u8 *) beacon_buf->info_element[0].data;

	स_नकल(tag, ssid, ssid_len);

	tag += ssid_len;

	*(tag++) = MFIE_TYPE_RATES;
	*(tag++) = rate_len-2;
	स_नकल(tag, ieee->current_network.rates, rate_len-2);
	tag += rate_len-2;

	*(tag++) = MFIE_TYPE_DS_SET;
	*(tag++) = 1;
	*(tag++) = ieee->current_network.channel;

	अगर (atim_len) अणु
		u16 val16;
		*(tag++) = MFIE_TYPE_IBSS_SET;
		*(tag++) = 2;
		val16 = ieee->current_network.atim_winकरोw;
		स_नकल((u8 *)tag, (u8 *)&val16, 2);
		tag += 2;
	पूर्ण

	अगर (erp_len) अणु
		*(tag++) = MFIE_TYPE_ERP;
		*(tag++) = 1;
		*(tag++) = erpinfo_content;
	पूर्ण
	अगर (rate_ex_len) अणु
		*(tag++) = MFIE_TYPE_RATES_EX;
		*(tag++) = rate_ex_len-2;
		स_नकल(tag, ieee->current_network.rates_ex, rate_ex_len-2);
		tag += rate_ex_len-2;
	पूर्ण

	अगर (wpa_ie_len) अणु
		अगर (ieee->iw_mode == IW_MODE_ADHOC)
			स_नकल(&ieee->wpa_ie[14], &ieee->wpa_ie[8], 4);
		स_नकल(tag, ieee->wpa_ie, ieee->wpa_ie_len);
		tag += ieee->wpa_ie_len;
	पूर्ण
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *rtllib_assoc_resp(काष्ठा rtllib_device *ieee, u8 *dest)
अणु
	काष्ठा sk_buff *skb;
	u8 *tag;

	काष्ठा lib80211_crypt_data *crypt;
	काष्ठा rtllib_assoc_response_frame *assoc;
	लघु encrypt;

	अचिन्हित पूर्णांक rate_len = rtllib_MFIE_rate_len(ieee);
	पूर्णांक len = माप(काष्ठा rtllib_assoc_response_frame) + rate_len +
		  ieee->tx_headroom;

	skb = dev_alloc_skb(len);

	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, ieee->tx_headroom);

	assoc = skb_put(skb, माप(काष्ठा rtllib_assoc_response_frame));

	assoc->header.frame_ctl = cpu_to_le16(RTLLIB_STYPE_ASSOC_RESP);
	ether_addr_copy(assoc->header.addr1, dest);
	ether_addr_copy(assoc->header.addr3, ieee->dev->dev_addr);
	ether_addr_copy(assoc->header.addr2, ieee->dev->dev_addr);
	assoc->capability = cpu_to_le16(ieee->iw_mode == IW_MODE_MASTER ?
		WLAN_CAPABILITY_ESS : WLAN_CAPABILITY_IBSS);


	अगर (ieee->लघु_slot)
		assoc->capability |=
				 cpu_to_le16(WLAN_CAPABILITY_SHORT_SLOT_TIME);

	अगर (ieee->host_encrypt)
		crypt = ieee->crypt_info.crypt[ieee->crypt_info.tx_keyidx];
	अन्यथा
		crypt = शून्य;

	encrypt = (crypt && crypt->ops);

	अगर (encrypt)
		assoc->capability |= cpu_to_le16(WLAN_CAPABILITY_PRIVACY);

	assoc->status = 0;
	assoc->aid = cpu_to_le16(ieee->assoc_id);
	अगर (ieee->assoc_id == 0x2007)
		ieee->assoc_id = 0;
	अन्यथा
		ieee->assoc_id++;

	tag = skb_put(skb, rate_len);
	rtllib_MFIE_Brate(ieee, &tag);
	rtllib_MFIE_Grate(ieee, &tag);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *rtllib_auth_resp(काष्ठा rtllib_device *ieee, पूर्णांक status,
				 u8 *dest)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा rtllib_authentication *auth;
	पूर्णांक len = ieee->tx_headroom + माप(काष्ठा rtllib_authentication) + 1;

	skb = dev_alloc_skb(len);
	अगर (!skb)
		वापस शून्य;

	skb->len = माप(काष्ठा rtllib_authentication);

	skb_reserve(skb, ieee->tx_headroom);

	auth = skb_put(skb, माप(काष्ठा rtllib_authentication));

	auth->status = cpu_to_le16(status);
	auth->transaction = cpu_to_le16(2);
	auth->algorithm = cpu_to_le16(WLAN_AUTH_OPEN);

	ether_addr_copy(auth->header.addr3, ieee->dev->dev_addr);
	ether_addr_copy(auth->header.addr2, ieee->dev->dev_addr);
	ether_addr_copy(auth->header.addr1, dest);
	auth->header.frame_ctl = cpu_to_le16(RTLLIB_STYPE_AUTH);
	वापस skb;


पूर्ण

अटल काष्ठा sk_buff *rtllib_null_func(काष्ठा rtllib_device *ieee, लघु pwr)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rtllib_hdr_3addr *hdr;

	skb = dev_alloc_skb(माप(काष्ठा rtllib_hdr_3addr)+ieee->tx_headroom);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, ieee->tx_headroom);

	hdr = skb_put(skb, माप(काष्ठा rtllib_hdr_3addr));

	ether_addr_copy(hdr->addr1, ieee->current_network.bssid);
	ether_addr_copy(hdr->addr2, ieee->dev->dev_addr);
	ether_addr_copy(hdr->addr3, ieee->current_network.bssid);

	hdr->frame_ctl = cpu_to_le16(RTLLIB_FTYPE_DATA |
		RTLLIB_STYPE_शून्यFUNC | RTLLIB_FCTL_TODS |
		(pwr ? RTLLIB_FCTL_PM : 0));

	वापस skb;


पूर्ण

अटल काष्ठा sk_buff *rtllib_pspoll_func(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rtllib_pspoll_hdr *hdr;

	skb = dev_alloc_skb(माप(काष्ठा rtllib_pspoll_hdr)+ieee->tx_headroom);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, ieee->tx_headroom);

	hdr = skb_put(skb, माप(काष्ठा rtllib_pspoll_hdr));

	ether_addr_copy(hdr->bssid, ieee->current_network.bssid);
	ether_addr_copy(hdr->ta, ieee->dev->dev_addr);

	hdr->aid = cpu_to_le16(ieee->assoc_id | 0xc000);
	hdr->frame_ctl = cpu_to_le16(RTLLIB_FTYPE_CTL | RTLLIB_STYPE_PSPOLL |
			 RTLLIB_FCTL_PM);

	वापस skb;

पूर्ण

अटल व्योम rtllib_resp_to_assoc_rq(काष्ठा rtllib_device *ieee, u8 *dest)
अणु
	काष्ठा sk_buff *buf = rtllib_assoc_resp(ieee, dest);

	अगर (buf)
		sofपंचांगac_mgmt_xmit(buf, ieee);
पूर्ण


अटल व्योम rtllib_resp_to_auth(काष्ठा rtllib_device *ieee, पूर्णांक s, u8 *dest)
अणु
	काष्ठा sk_buff *buf = rtllib_auth_resp(ieee, s, dest);

	अगर (buf)
		sofपंचांगac_mgmt_xmit(buf, ieee);
पूर्ण


अटल व्योम rtllib_resp_to_probe(काष्ठा rtllib_device *ieee, u8 *dest)
अणु
	काष्ठा sk_buff *buf = rtllib_probe_resp(ieee, dest);

	अगर (buf)
		sofपंचांगac_mgmt_xmit(buf, ieee);
पूर्ण


अटल अंतरभूत पूर्णांक SecIsInPMKIDList(काष्ठा rtllib_device *ieee, u8 *bssid)
अणु
	पूर्णांक i = 0;

	करो अणु
		अगर ((ieee->PMKIDList[i].bUsed) &&
		   (स_भेद(ieee->PMKIDList[i].Bssid, bssid, ETH_ALEN) == 0))
			अवरोध;
		i++;
	पूर्ण जबतक (i < NUM_PMKID_CACHE);

	अगर (i == NUM_PMKID_CACHE)
		i = -1;
	वापस i;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *
rtllib_association_req(काष्ठा rtllib_network *beacon,
		       काष्ठा rtllib_device *ieee)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rtllib_assoc_request_frame *hdr;
	u8 *tag, *ies;
	पूर्णांक i;
	u8 *ht_cap_buf = शून्य;
	u8 ht_cap_len = 0;
	u8 *realtek_ie_buf = शून्य;
	u8 realtek_ie_len = 0;
	पूर्णांक wpa_ie_len = ieee->wpa_ie_len;
	पूर्णांक wps_ie_len = ieee->wps_ie_len;
	अचिन्हित पूर्णांक ckip_ie_len = 0;
	अचिन्हित पूर्णांक ccxrm_ie_len = 0;
	अचिन्हित पूर्णांक cxvernum_ie_len = 0;
	काष्ठा lib80211_crypt_data *crypt;
	पूर्णांक encrypt;
	पूर्णांक	PMKCacheIdx;

	अचिन्हित पूर्णांक rate_len = (beacon->rates_len ?
				(beacon->rates_len + 2) : 0) +
				(beacon->rates_ex_len ? (beacon->rates_ex_len) +
				2 : 0);

	अचिन्हित पूर्णांक wmm_info_len = beacon->qos_data.supported ? 9 : 0;
	अचिन्हित पूर्णांक turbo_info_len = beacon->Turbo_Enable ? 9 : 0;

	पूर्णांक len = 0;

	crypt = ieee->crypt_info.crypt[ieee->crypt_info.tx_keyidx];
	अगर (crypt != शून्य)
		encrypt = ieee->host_encrypt && crypt && crypt->ops &&
			  ((म_भेद(crypt->ops->name, "R-WEP") == 0 ||
			  wpa_ie_len));
	अन्यथा
		encrypt = 0;

	अगर ((ieee->rtllib_ap_sec_type &&
	    (ieee->rtllib_ap_sec_type(ieee) & SEC_ALG_TKIP)) ||
	    ieee->bForcedBgMode) अणु
		ieee->pHTInfo->bEnableHT = 0;
		ieee->mode = WIRELESS_MODE_G;
	पूर्ण

	अगर (ieee->pHTInfo->bCurrentHTSupport && ieee->pHTInfo->bEnableHT) अणु
		ht_cap_buf = (u8 *)&(ieee->pHTInfo->SelfHTCap);
		ht_cap_len = माप(ieee->pHTInfo->SelfHTCap);
		HTConकाष्ठाCapabilityElement(ieee, ht_cap_buf, &ht_cap_len,
					     encrypt, true);
		अगर (ieee->pHTInfo->bCurrentRT2RTAggregation) अणु
			realtek_ie_buf = ieee->pHTInfo->szRT2RTAggBuffer;
			realtek_ie_len =
				 माप(ieee->pHTInfo->szRT2RTAggBuffer);
			HTConकाष्ठाRT2RTAggElement(ieee, realtek_ie_buf,
						   &realtek_ie_len);
		पूर्ण
	पूर्ण

	अगर (beacon->bCkipSupported)
		ckip_ie_len = 30+2;
	अगर (beacon->bCcxRmEnable)
		ccxrm_ie_len = 6+2;
	अगर (beacon->BssCcxVerNumber >= 2)
		cxvernum_ie_len = 5+2;

	PMKCacheIdx = SecIsInPMKIDList(ieee, ieee->current_network.bssid);
	अगर (PMKCacheIdx >= 0) अणु
		wpa_ie_len += 18;
		netdev_info(ieee->dev, "[PMK cache]: WPA2 IE length: %x\n",
			    wpa_ie_len);
	पूर्ण
	len = माप(काष्ठा rtllib_assoc_request_frame) + 2
		+ beacon->ssid_len
		+ rate_len
		+ wpa_ie_len
		+ wps_ie_len
		+ wmm_info_len
		+ turbo_info_len
		+ ht_cap_len
		+ realtek_ie_len
		+ ckip_ie_len
		+ ccxrm_ie_len
		+ cxvernum_ie_len
		+ ieee->tx_headroom;

	skb = dev_alloc_skb(len);

	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, ieee->tx_headroom);

	hdr = skb_put(skb, माप(काष्ठा rtllib_assoc_request_frame) + 2);


	hdr->header.frame_ctl = cpu_to_le16(RTLLIB_STYPE_ASSOC_REQ);
	hdr->header.duration_id = cpu_to_le16(37);
	ether_addr_copy(hdr->header.addr1, beacon->bssid);
	ether_addr_copy(hdr->header.addr2, ieee->dev->dev_addr);
	ether_addr_copy(hdr->header.addr3, beacon->bssid);

	ether_addr_copy(ieee->ap_mac_addr, beacon->bssid);

	hdr->capability = cpu_to_le16(WLAN_CAPABILITY_ESS);
	अगर (beacon->capability & WLAN_CAPABILITY_PRIVACY)
		hdr->capability |= cpu_to_le16(WLAN_CAPABILITY_PRIVACY);

	अगर (beacon->capability & WLAN_CAPABILITY_SHORT_PREAMBLE)
		hdr->capability |= cpu_to_le16(WLAN_CAPABILITY_SHORT_PREAMBLE);

	अगर (ieee->लघु_slot &&
	   (beacon->capability&WLAN_CAPABILITY_SHORT_SLOT_TIME))
		hdr->capability |= cpu_to_le16(WLAN_CAPABILITY_SHORT_SLOT_TIME);


	hdr->listen_पूर्णांकerval = cpu_to_le16(beacon->listen_पूर्णांकerval);

	hdr->info_element[0].id = MFIE_TYPE_SSID;

	hdr->info_element[0].len = beacon->ssid_len;
	skb_put_data(skb, beacon->ssid, beacon->ssid_len);

	tag = skb_put(skb, rate_len);

	अगर (beacon->rates_len) अणु
		*tag++ = MFIE_TYPE_RATES;
		*tag++ = beacon->rates_len;
		क्रम (i = 0; i < beacon->rates_len; i++)
			*tag++ = beacon->rates[i];
	पूर्ण

	अगर (beacon->rates_ex_len) अणु
		*tag++ = MFIE_TYPE_RATES_EX;
		*tag++ = beacon->rates_ex_len;
		क्रम (i = 0; i < beacon->rates_ex_len; i++)
			*tag++ = beacon->rates_ex[i];
	पूर्ण

	अगर (beacon->bCkipSupported) अणु
		अटल स्थिर u8 AironetIeOui[] = अणु0x00, 0x01, 0x66पूर्ण;
		u8	CcxAironetBuf[30];
		काष्ठा octet_string osCcxAironetIE;

		स_रखो(CcxAironetBuf, 0, 30);
		osCcxAironetIE.Octet = CcxAironetBuf;
		osCcxAironetIE.Length = माप(CcxAironetBuf);
		स_नकल(osCcxAironetIE.Octet, AironetIeOui,
		       माप(AironetIeOui));

		osCcxAironetIE.Octet[IE_CISCO_FLAG_POSITION] |=
					 (SUPPORT_CKIP_PK|SUPPORT_CKIP_MIC);
		tag = skb_put(skb, ckip_ie_len);
		*tag++ = MFIE_TYPE_AIRONET;
		*tag++ = osCcxAironetIE.Length;
		स_नकल(tag, osCcxAironetIE.Octet, osCcxAironetIE.Length);
		tag += osCcxAironetIE.Length;
	पूर्ण

	अगर (beacon->bCcxRmEnable) अणु
		अटल स्थिर u8 CcxRmCapBuf[] = अणु0x00, 0x40, 0x96, 0x01, 0x01,
			0x00पूर्ण;
		काष्ठा octet_string osCcxRmCap;

		osCcxRmCap.Octet = (u8 *) CcxRmCapBuf;
		osCcxRmCap.Length = माप(CcxRmCapBuf);
		tag = skb_put(skb, ccxrm_ie_len);
		*tag++ = MFIE_TYPE_GENERIC;
		*tag++ = osCcxRmCap.Length;
		स_नकल(tag, osCcxRmCap.Octet, osCcxRmCap.Length);
		tag += osCcxRmCap.Length;
	पूर्ण

	अगर (beacon->BssCcxVerNumber >= 2) अणु
		u8 CcxVerNumBuf[] = अणु0x00, 0x40, 0x96, 0x03, 0x00पूर्ण;
		काष्ठा octet_string osCcxVerNum;

		CcxVerNumBuf[4] = beacon->BssCcxVerNumber;
		osCcxVerNum.Octet = CcxVerNumBuf;
		osCcxVerNum.Length = माप(CcxVerNumBuf);
		tag = skb_put(skb, cxvernum_ie_len);
		*tag++ = MFIE_TYPE_GENERIC;
		*tag++ = osCcxVerNum.Length;
		स_नकल(tag, osCcxVerNum.Octet, osCcxVerNum.Length);
		tag += osCcxVerNum.Length;
	पूर्ण
	अगर (ieee->pHTInfo->bCurrentHTSupport && ieee->pHTInfo->bEnableHT) अणु
		अगर (ieee->pHTInfo->ePeerHTSpecVer != HT_SPEC_VER_EWC) अणु
			tag = skb_put(skb, ht_cap_len);
			*tag++ = MFIE_TYPE_HT_CAP;
			*tag++ = ht_cap_len - 2;
			स_नकल(tag, ht_cap_buf, ht_cap_len - 2);
			tag += ht_cap_len - 2;
		पूर्ण
	पूर्ण

	अगर (wpa_ie_len) अणु
		skb_put_data(skb, ieee->wpa_ie, ieee->wpa_ie_len);

		अगर (PMKCacheIdx >= 0) अणु
			tag = skb_put(skb, 18);
			*tag = 1;
			*(tag + 1) = 0;
			स_नकल((tag + 2), &ieee->PMKIDList[PMKCacheIdx].PMKID,
			       16);
		पूर्ण
	पूर्ण
	अगर (wmm_info_len) अणु
		tag = skb_put(skb, wmm_info_len);
		rtllib_WMM_Info(ieee, &tag);
	पूर्ण

	अगर (wps_ie_len && ieee->wps_ie)
		skb_put_data(skb, ieee->wps_ie, wps_ie_len);

	अगर (turbo_info_len) अणु
		tag = skb_put(skb, turbo_info_len);
		rtllib_TURBO_Info(ieee, &tag);
	पूर्ण

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

	kमुक्त(ieee->assocreq_ies);
	ieee->assocreq_ies = शून्य;
	ies = &(hdr->info_element[0].id);
	ieee->assocreq_ies_len = (skb->data + skb->len) - ies;
	ieee->assocreq_ies = kmemdup(ies, ieee->assocreq_ies_len, GFP_ATOMIC);
	अगर (!ieee->assocreq_ies)
		ieee->assocreq_ies_len = 0;

	वापस skb;
पूर्ण

अटल व्योम rtllib_associate_पात(काष्ठा rtllib_device *ieee)
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
	अगर (ieee->state == RTLLIB_ASSOCIATING_AUTHENTICATING) अणु
		netdev_dbg(ieee->dev, "Authentication failed\n");
		ieee->sofपंचांगac_stats.no_auth_rs++;
	पूर्ण अन्यथा अणु
		netdev_dbg(ieee->dev, "Association failed\n");
		ieee->sofपंचांगac_stats.no_ass_rs++;
	पूर्ण

	ieee->state = RTLLIB_ASSOCIATING_RETRY;

	schedule_delayed_work(&ieee->associate_retry_wq,
			      RTLLIB_SOFTMAC_ASSOC_RETRY_TIME);

	spin_unlock_irqrestore(&ieee->lock, flags);
पूर्ण

अटल व्योम rtllib_associate_पात_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा rtllib_device *dev = from_समयr(dev, t, associate_समयr);

	rtllib_associate_पात(dev);
पूर्ण

अटल व्योम rtllib_associate_step1(काष्ठा rtllib_device *ieee, u8 *daddr)
अणु
	काष्ठा rtllib_network *beacon = &ieee->current_network;
	काष्ठा sk_buff *skb;

	netdev_dbg(ieee->dev, "Stopping scan\n");

	ieee->sofपंचांगac_stats.tx_auth_rq++;

	skb = rtllib_authentication_req(beacon, ieee, 0, daddr);

	अगर (!skb)
		rtllib_associate_पात(ieee);
	अन्यथा अणु
		ieee->state = RTLLIB_ASSOCIATING_AUTHENTICATING;
		netdev_dbg(ieee->dev, "Sending authentication request\n");
		sofपंचांगac_mgmt_xmit(skb, ieee);
		अगर (!समयr_pending(&ieee->associate_समयr)) अणु
			ieee->associate_समयr.expires = jअगरfies + (HZ / 2);
			add_समयr(&ieee->associate_समयr);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtllib_auth_challenge(काष्ठा rtllib_device *ieee, u8 *challenge,
				  पूर्णांक chlen)
अणु
	u8 *c;
	काष्ठा sk_buff *skb;
	काष्ठा rtllib_network *beacon = &ieee->current_network;

	ieee->associate_seq++;
	ieee->sofपंचांगac_stats.tx_auth_rq++;

	skb = rtllib_authentication_req(beacon, ieee, chlen + 2, beacon->bssid);

	अगर (!skb)
		rtllib_associate_पात(ieee);
	अन्यथा अणु
		c = skb_put(skb, chlen+2);
		*(c++) = MFIE_TYPE_CHALLENGE;
		*(c++) = chlen;
		स_नकल(c, challenge, chlen);

		netdev_dbg(ieee->dev,
			   "Sending authentication challenge response\n");

		rtllib_encrypt_fragment(ieee, skb,
					माप(काष्ठा rtllib_hdr_3addr));

		sofपंचांगac_mgmt_xmit(skb, ieee);
		mod_समयr(&ieee->associate_समयr, jअगरfies + (HZ/2));
	पूर्ण
	kमुक्त(challenge);
पूर्ण

अटल व्योम rtllib_associate_step2(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rtllib_network *beacon = &ieee->current_network;

	del_समयr_sync(&ieee->associate_समयr);

	netdev_dbg(ieee->dev, "Sending association request\n");

	ieee->sofपंचांगac_stats.tx_ass_rq++;
	skb = rtllib_association_req(beacon, ieee);
	अगर (!skb)
		rtllib_associate_पात(ieee);
	अन्यथा अणु
		sofपंचांगac_mgmt_xmit(skb, ieee);
		mod_समयr(&ieee->associate_समयr, jअगरfies + (HZ/2));
	पूर्ण
पूर्ण

अटल व्योम rtllib_associate_complete_wq(व्योम *data)
अणु
	काष्ठा rtllib_device *ieee = (काष्ठा rtllib_device *)
				     container_of_work_rsl(data,
				     काष्ठा rtllib_device,
				     associate_complete_wq);
	काष्ठा rt_pwr_save_ctrl *pPSC = &(ieee->PowerSaveControl);

	netdev_info(ieee->dev, "Associated successfully with %pM\n",
		    ieee->current_network.bssid);
	अगर (!ieee->is_silent_reset) अणु
		netdev_info(ieee->dev, "normal associate\n");
		notअगरy_wx_assoc_event(ieee);
	पूर्ण

	netअगर_carrier_on(ieee->dev);
	ieee->is_roaming = false;
	अगर (rtllib_is_54g(&ieee->current_network) &&
	   (ieee->modulation & RTLLIB_OFDM_MODULATION)) अणु
		ieee->rate = 108;
		netdev_info(ieee->dev, "Using G rates:%d\n", ieee->rate);
	पूर्ण अन्यथा अणु
		ieee->rate = 22;
		ieee->SetWirelessMode(ieee->dev, IEEE_B);
		netdev_info(ieee->dev, "Using B rates:%d\n", ieee->rate);
	पूर्ण
	अगर (ieee->pHTInfo->bCurrentHTSupport && ieee->pHTInfo->bEnableHT) अणु
		netdev_info(ieee->dev, "Successfully associated, ht enabled\n");
		HTOnAssocRsp(ieee);
	पूर्ण अन्यथा अणु
		netdev_info(ieee->dev,
			    "Successfully associated, ht not enabled(%d, %d)\n",
			    ieee->pHTInfo->bCurrentHTSupport,
			    ieee->pHTInfo->bEnableHT);
		स_रखो(ieee->करोt11HTOperationalRateSet, 0, 16);
	पूर्ण
	ieee->LinkDetectInfo.SlotNum = 2 * (1 +
				       ieee->current_network.beacon_पूर्णांकerval /
				       500);
	अगर (ieee->LinkDetectInfo.NumRecvBcnInPeriod == 0 ||
	    ieee->LinkDetectInfo.NumRecvDataInPeriod == 0) अणु
		ieee->LinkDetectInfo.NumRecvBcnInPeriod = 1;
		ieee->LinkDetectInfo.NumRecvDataInPeriod = 1;
	पूर्ण
	pPSC->LpsIdleCount = 0;
	ieee->link_change(ieee->dev);

	अगर (ieee->is_silent_reset) अणु
		netdev_info(ieee->dev, "silent reset associate\n");
		ieee->is_silent_reset = false;
	पूर्ण

	अगर (ieee->data_hard_resume)
		ieee->data_hard_resume(ieee->dev);

पूर्ण

अटल व्योम rtllib_sta_send_associnfo(काष्ठा rtllib_device *ieee)
अणु
पूर्ण

अटल व्योम rtllib_associate_complete(काष्ठा rtllib_device *ieee)
अणु
	del_समयr_sync(&ieee->associate_समयr);

	ieee->state = RTLLIB_LINKED;
	rtllib_sta_send_associnfo(ieee);

	schedule_work(&ieee->associate_complete_wq);
पूर्ण

अटल व्योम rtllib_associate_procedure_wq(व्योम *data)
अणु
	काष्ठा rtllib_device *ieee = container_of_dwork_rsl(data,
				     काष्ठा rtllib_device,
				     associate_procedure_wq);
	rtllib_stop_scan_syncro(ieee);
	अगर (ieee->rtllib_ips_leave != शून्य)
		ieee->rtllib_ips_leave(ieee->dev);
	mutex_lock(&ieee->wx_mutex);

	अगर (ieee->data_hard_stop)
		ieee->data_hard_stop(ieee->dev);

	rtllib_stop_scan(ieee);
	RT_TRACE(COMP_DBG, "===>%s(), chan:%d\n", __func__,
		 ieee->current_network.channel);
	HTSetConnectBwMode(ieee, HT_CHANNEL_WIDTH_20, HT_EXTCHNL_OFFSET_NO_EXT);
	अगर (ieee->eRFPowerState == eRfOff) अणु
		RT_TRACE(COMP_DBG,
			 "=============>%s():Rf state is eRfOff, schedule ipsleave wq again,return\n",
			 __func__);
		अगर (ieee->rtllib_ips_leave_wq != शून्य)
			ieee->rtllib_ips_leave_wq(ieee->dev);
		mutex_unlock(&ieee->wx_mutex);
		वापस;
	पूर्ण
	ieee->associate_seq = 1;

	rtllib_associate_step1(ieee, ieee->current_network.bssid);

	mutex_unlock(&ieee->wx_mutex);
पूर्ण

अंतरभूत व्योम rtllib_sofपंचांगac_new_net(काष्ठा rtllib_device *ieee,
				   काष्ठा rtllib_network *net)
अणु
	u8 पंचांगp_ssid[IW_ESSID_MAX_SIZE + 1];
	पूर्णांक पंचांगp_ssid_len = 0;

	लघु apset, ssidset, ssidbroad, apmatch, ssidmatch;

	/* we are पूर्णांकerested in new new only अगर we are not associated
	 * and we are not associating / authenticating
	 */
	अगर (ieee->state != RTLLIB_NOLINK)
		वापस;

	अगर ((ieee->iw_mode == IW_MODE_INFRA) && !(net->capability &
	    WLAN_CAPABILITY_ESS))
		वापस;

	अगर ((ieee->iw_mode == IW_MODE_ADHOC) && !(net->capability &
	     WLAN_CAPABILITY_IBSS))
		वापस;

	अगर ((ieee->iw_mode == IW_MODE_ADHOC) &&
	    (net->channel > ieee->ibss_maxjoin_chal))
		वापस;
	अगर (ieee->iw_mode == IW_MODE_INFRA || ieee->iw_mode == IW_MODE_ADHOC) अणु
		/* अगर the user specअगरied the AP MAC, we need also the essid
		 * This could be obtained by beacons or, अगर the network करोes not
		 * broadcast it, it can be put manually.
		 */
		apset = ieee->wap_set;
		ssidset = ieee->ssid_set;
		ssidbroad =  !(net->ssid_len == 0 || net->ssid[0] == '\0');
		apmatch = (स_भेद(ieee->current_network.bssid, net->bssid,
				  ETH_ALEN) == 0);
		अगर (!ssidbroad) अणु
			ssidmatch = (ieee->current_network.ssid_len ==
				    net->hidden_ssid_len) &&
				    (!म_भेदन(ieee->current_network.ssid,
				    net->hidden_ssid, net->hidden_ssid_len));
			अगर (net->hidden_ssid_len > 0) अणु
				म_नकलन(net->ssid, net->hidden_ssid,
					net->hidden_ssid_len);
				net->ssid_len = net->hidden_ssid_len;
				ssidbroad = 1;
			पूर्ण
		पूर्ण अन्यथा
			ssidmatch =
			   (ieee->current_network.ssid_len == net->ssid_len) &&
			   (!म_भेदन(ieee->current_network.ssid, net->ssid,
			   net->ssid_len));

		/* अगर the user set the AP check अगर match.
		 * अगर the network करोes not broadcast essid we check the
		 *	 user supplied ANY essid
		 * अगर the network करोes broadcast and the user करोes not set
		 *	 essid it is OK
		 * अगर the network करोes broadcast and the user did set essid
		 * check अगर essid match
		 * अगर the ap is not set, check that the user set the bssid
		 * and the network करोes broadcast and that those two bssid match
		 */
		अगर ((apset && apmatch &&
		   ((ssidset && ssidbroad && ssidmatch) ||
		   (ssidbroad && !ssidset) || (!ssidbroad && ssidset))) ||
		   (!apset && ssidset && ssidbroad && ssidmatch) ||
		   (ieee->is_roaming && ssidset && ssidbroad && ssidmatch)) अणु
			/* Save the essid so that अगर it is hidden, it is
			 * replaced with the essid provided by the user.
			 */
			अगर (!ssidbroad) अणु
				स_नकल(पंचांगp_ssid, ieee->current_network.ssid,
				       ieee->current_network.ssid_len);
				पंचांगp_ssid_len = ieee->current_network.ssid_len;
			पूर्ण
			स_नकल(&ieee->current_network, net,
				माप(ieee->current_network));
			अगर (!ssidbroad) अणु
				स_नकल(ieee->current_network.ssid, पंचांगp_ssid,
				       पंचांगp_ssid_len);
				ieee->current_network.ssid_len = पंचांगp_ssid_len;
			पूर्ण
			netdev_info(ieee->dev,
				    "Linking with %s,channel:%d, qos:%d, myHT:%d, networkHT:%d, mode:%x cur_net.flags:0x%x\n",
				    ieee->current_network.ssid,
				    ieee->current_network.channel,
				    ieee->current_network.qos_data.supported,
				    ieee->pHTInfo->bEnableHT,
				    ieee->current_network.bssht.bd_support_ht,
				    ieee->current_network.mode,
				    ieee->current_network.flags);

			अगर ((rtllib_act_scanning(ieee, false)) &&
			   !(ieee->sofपंचांगac_features & IEEE_SOFTMAC_SCAN))
				rtllib_stop_scan_syncro(ieee);

			HTResetIOTSetting(ieee->pHTInfo);
			ieee->wmm_acm = 0;
			अगर (ieee->iw_mode == IW_MODE_INFRA) अणु
				/* Join the network क्रम the first समय */
				ieee->AsocRetryCount = 0;
				अगर ((ieee->current_network.qos_data.supported == 1) &&
				    ieee->current_network.bssht.bd_support_ht)
					HTResetSelfAndSavePeerSetting(ieee,
						 &(ieee->current_network));
				अन्यथा
					ieee->pHTInfo->bCurrentHTSupport =
								 false;

				ieee->state = RTLLIB_ASSOCIATING;
				अगर (ieee->LedControlHandler != शून्य)
					ieee->LedControlHandler(ieee->dev,
							 LED_CTL_START_TO_LINK);
				schedule_delayed_work(
					   &ieee->associate_procedure_wq, 0);
			पूर्ण अन्यथा अणु
				अगर (rtllib_is_54g(&ieee->current_network) &&
				    (ieee->modulation &
				     RTLLIB_OFDM_MODULATION)) अणु
					ieee->rate = 108;
					ieee->SetWirelessMode(ieee->dev,
							      IEEE_G);
					netdev_info(ieee->dev,
						    "Using G rates\n");
				पूर्ण अन्यथा अणु
					ieee->rate = 22;
					ieee->SetWirelessMode(ieee->dev,
							      IEEE_B);
					netdev_info(ieee->dev,
						    "Using B rates\n");
				पूर्ण
				स_रखो(ieee->करोt11HTOperationalRateSet, 0, 16);
				ieee->state = RTLLIB_LINKED;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtllib_sofपंचांगac_check_all_nets(काष्ठा rtllib_device *ieee)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rtllib_network *target;

	spin_lock_irqsave(&ieee->lock, flags);

	list_क्रम_each_entry(target, &ieee->network_list, list) अणु

		/* अगर the state become dअगरferent that NOLINK means
		 * we had found what we are searching क्रम
		 */

		अगर (ieee->state != RTLLIB_NOLINK)
			अवरोध;

		अगर (ieee->scan_age == 0 || समय_after(target->last_scanned +
		    ieee->scan_age, jअगरfies))
			rtllib_sofपंचांगac_new_net(ieee, target);
	पूर्ण
	spin_unlock_irqrestore(&ieee->lock, flags);
पूर्ण

अटल अंतरभूत u16 auth_parse(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			     u8 **challenge, पूर्णांक *chlen)
अणु
	काष्ठा rtllib_authentication *a;
	u8 *t;

	अगर (skb->len <  (माप(काष्ठा rtllib_authentication) -
	    माप(काष्ठा rtllib_info_element))) अणु
		netdev_dbg(dev, "invalid len in auth resp: %d\n", skb->len);
		वापस 0xcafe;
	पूर्ण
	*challenge = शून्य;
	a = (काष्ठा rtllib_authentication *) skb->data;
	अगर (skb->len > (माप(काष्ठा rtllib_authentication) + 3)) अणु
		t = skb->data + माप(काष्ठा rtllib_authentication);

		अगर (*(t++) == MFIE_TYPE_CHALLENGE) अणु
			*chlen = *(t++);
			*challenge = kmemdup(t, *chlen, GFP_ATOMIC);
			अगर (!*challenge)
				वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस le16_to_cpu(a->status);
पूर्ण

अटल पूर्णांक auth_rq_parse(काष्ठा net_device *dev, काष्ठा sk_buff *skb, u8 *dest)
अणु
	काष्ठा rtllib_authentication *a;

	अगर (skb->len <  (माप(काष्ठा rtllib_authentication) -
	    माप(काष्ठा rtllib_info_element))) अणु
		netdev_dbg(dev, "invalid len in auth request: %d\n", skb->len);
		वापस -1;
	पूर्ण
	a = (काष्ठा rtllib_authentication *) skb->data;

	ether_addr_copy(dest, a->header.addr2);

	अगर (le16_to_cpu(a->algorithm) != WLAN_AUTH_OPEN)
		वापस  WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG;

	वापस WLAN_STATUS_SUCCESS;
पूर्ण

अटल लघु probe_rq_parse(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
			    u8 *src)
अणु
	u8 *tag;
	u8 *skbend;
	u8 *ssid = शून्य;
	u8 ssidlen = 0;
	काष्ठा rtllib_hdr_3addr   *header =
		(काष्ठा rtllib_hdr_3addr   *) skb->data;
	bool bssid_match;

	अगर (skb->len < माप(काष्ठा rtllib_hdr_3addr))
		वापस -1; /* corrupted */

	bssid_match =
	  (!ether_addr_equal(header->addr3, ieee->current_network.bssid)) &&
	  (!is_broadcast_ether_addr(header->addr3));
	अगर (bssid_match)
		वापस -1;

	ether_addr_copy(src, header->addr2);

	skbend = (u8 *)skb->data + skb->len;

	tag = skb->data + माप(काष्ठा rtllib_hdr_3addr);

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

	अगर (ssidlen == 0)
		वापस 1;

	अगर (!ssid)
		वापस 1; /* ssid not found in tagged param */

	वापस !म_भेदन(ssid, ieee->current_network.ssid, ssidlen);
पूर्ण

अटल पूर्णांक assoc_rq_parse(काष्ठा net_device *dev, काष्ठा sk_buff *skb, u8 *dest)
अणु
	काष्ठा rtllib_assoc_request_frame *a;

	अगर (skb->len < (माप(काष्ठा rtllib_assoc_request_frame) -
		माप(काष्ठा rtllib_info_element))) अणु
		netdev_dbg(dev, "invalid len in auth request:%d\n", skb->len);
		वापस -1;
	पूर्ण

	a = (काष्ठा rtllib_assoc_request_frame *) skb->data;

	ether_addr_copy(dest, a->header.addr2);

	वापस 0;
पूर्ण

अटल अंतरभूत u16 assoc_parse(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
			      पूर्णांक *aid)
अणु
	काष्ठा rtllib_assoc_response_frame *response_head;
	u16 status_code;

	अगर (skb->len <  माप(काष्ठा rtllib_assoc_response_frame)) अणु
		netdev_dbg(ieee->dev, "Invalid len in auth resp: %d\n",
			   skb->len);
		वापस 0xcafe;
	पूर्ण

	response_head = (काष्ठा rtllib_assoc_response_frame *) skb->data;
	*aid = le16_to_cpu(response_head->aid) & 0x3fff;

	status_code = le16_to_cpu(response_head->status);
	अगर ((status_code == WLAN_STATUS_ASSOC_DENIED_RATES ||
	   status_code == WLAN_STATUS_CAPS_UNSUPPORTED) &&
	   ((ieee->mode == IEEE_G) &&
	   (ieee->current_network.mode == IEEE_N_24G) &&
	   (ieee->AsocRetryCount++ < (RT_ASOC_RETRY_LIMIT-1)))) अणु
		ieee->pHTInfo->IOTAction |= HT_IOT_ACT_PURE_N_MODE;
	पूर्ण अन्यथा अणु
		ieee->AsocRetryCount = 0;
	पूर्ण

	वापस le16_to_cpu(response_head->status);
पूर्ण

व्योम rtllib_rx_probe_rq(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb)
अणु
	u8 dest[ETH_ALEN];

	ieee->sofपंचांगac_stats.rx_probe_rq++;
	अगर (probe_rq_parse(ieee, skb, dest) > 0) अणु
		ieee->sofपंचांगac_stats.tx_probe_rs++;
		rtllib_resp_to_probe(ieee, dest);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम rtllib_rx_auth_rq(काष्ठा rtllib_device *ieee,
				     काष्ठा sk_buff *skb)
अणु
	u8 dest[ETH_ALEN];
	पूर्णांक status;

	ieee->sofपंचांगac_stats.rx_auth_rq++;

	status = auth_rq_parse(ieee->dev, skb, dest);
	अगर (status != -1)
		rtllib_resp_to_auth(ieee, status, dest);
पूर्ण

अटल अंतरभूत व्योम rtllib_rx_assoc_rq(काष्ठा rtllib_device *ieee,
				      काष्ठा sk_buff *skb)
अणु
	u8 dest[ETH_ALEN];


	ieee->sofपंचांगac_stats.rx_ass_rq++;
	अगर (assoc_rq_parse(ieee->dev, skb, dest) != -1)
		rtllib_resp_to_assoc_rq(ieee, dest);

	netdev_info(ieee->dev, "New client associated: %pM\n", dest);
पूर्ण

व्योम rtllib_sta_ps_send_null_frame(काष्ठा rtllib_device *ieee, लघु pwr)
अणु

	काष्ठा sk_buff *buf = rtllib_null_func(ieee, pwr);

	अगर (buf)
		sofपंचांगac_ps_mgmt_xmit(buf, ieee);
पूर्ण
EXPORT_SYMBOL(rtllib_sta_ps_send_null_frame);

व्योम rtllib_sta_ps_send_pspoll_frame(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा sk_buff *buf = rtllib_pspoll_func(ieee);

	अगर (buf)
		sofपंचांगac_ps_mgmt_xmit(buf, ieee);
पूर्ण

अटल लघु rtllib_sta_ps_sleep(काष्ठा rtllib_device *ieee, u64 *समय)
अणु
	पूर्णांक समयout;
	u8 dtim;
	काष्ठा rt_pwr_save_ctrl *pPSC = &(ieee->PowerSaveControl);

	अगर (ieee->LPSDelayCnt) अणु
		ieee->LPSDelayCnt--;
		वापस 0;
	पूर्ण

	dtim = ieee->current_network.dtim_data;
	अगर (!(dtim & RTLLIB_DTIM_VALID))
		वापस 0;
	समयout = ieee->current_network.beacon_पूर्णांकerval;
	ieee->current_network.dtim_data = RTLLIB_DTIM_INVALID;
	/* there's no need to nofity AP that I find you buffered
	 * with broadcast packet
	 */
	अगर (dtim & (RTLLIB_DTIM_UCAST & ieee->ps))
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

	अगर (समय) अणु
		अगर (ieee->bAwakePktSent) अणु
			pPSC->LPSAwakeIntvl = 1;
		पूर्ण अन्यथा अणु
			u8 MaxPeriod = 1;

			अगर (pPSC->LPSAwakeIntvl == 0)
				pPSC->LPSAwakeIntvl = 1;
			अगर (pPSC->RegMaxLPSAwakeIntvl == 0)
				MaxPeriod = 1;
			अन्यथा अगर (pPSC->RegMaxLPSAwakeIntvl == 0xFF)
				MaxPeriod = ieee->current_network.dtim_period;
			अन्यथा
				MaxPeriod = pPSC->RegMaxLPSAwakeIntvl;
			pPSC->LPSAwakeIntvl = (pPSC->LPSAwakeIntvl >=
					       MaxPeriod) ? MaxPeriod :
					       (pPSC->LPSAwakeIntvl + 1);
		पूर्ण
		अणु
			u8 LPSAwakeIntvl_पंचांगp = 0;
			u8 period = ieee->current_network.dtim_period;
			u8 count = ieee->current_network.tim.tim_count;

			अगर (count == 0) अणु
				अगर (pPSC->LPSAwakeIntvl > period)
					LPSAwakeIntvl_पंचांगp = period +
						 (pPSC->LPSAwakeIntvl -
						 period) -
						 ((pPSC->LPSAwakeIntvl-period) %
						 period);
				अन्यथा
					LPSAwakeIntvl_पंचांगp = pPSC->LPSAwakeIntvl;

			पूर्ण अन्यथा अणु
				अगर (pPSC->LPSAwakeIntvl >
				    ieee->current_network.tim.tim_count)
					LPSAwakeIntvl_पंचांगp = count +
					(pPSC->LPSAwakeIntvl - count) -
					((pPSC->LPSAwakeIntvl-count)%period);
				अन्यथा
					LPSAwakeIntvl_पंचांगp = pPSC->LPSAwakeIntvl;
			पूर्ण

		*समय = ieee->current_network.last_dtim_sta_समय
			+ msecs_to_jअगरfies(ieee->current_network.beacon_पूर्णांकerval *
			LPSAwakeIntvl_पंचांगp);
	पूर्ण
	पूर्ण

	वापस 1;


पूर्ण

अटल अंतरभूत व्योम rtllib_sta_ps(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rtllib_device *ieee = from_tasklet(ieee, t, ps_task);
	u64 समय;
	लघु sleep;
	अचिन्हित दीर्घ flags, flags2;

	spin_lock_irqsave(&ieee->lock, flags);

	अगर ((ieee->ps == RTLLIB_PS_DISABLED ||
	     ieee->iw_mode != IW_MODE_INFRA ||
	     ieee->state != RTLLIB_LINKED)) अणु
		RT_TRACE(COMP_DBG,
			 "=====>%s(): no need to ps,wake up!! ieee->ps is %d, ieee->iw_mode is %d, ieee->state is %d\n",
			 __func__, ieee->ps, ieee->iw_mode, ieee->state);
		spin_lock_irqsave(&ieee->mgmt_tx_lock, flags2);
		rtllib_sta_wakeup(ieee, 1);

		spin_unlock_irqrestore(&ieee->mgmt_tx_lock, flags2);
	पूर्ण
	sleep = rtllib_sta_ps_sleep(ieee, &समय);
	/* 2 wake, 1 sleep, 0 करो nothing */
	अगर (sleep == 0)
		जाओ out;
	अगर (sleep == 1) अणु
		अगर (ieee->sta_sleep == LPS_IS_SLEEP) अणु
			ieee->enter_sleep_state(ieee->dev, समय);
		पूर्ण अन्यथा अगर (ieee->sta_sleep == LPS_IS_WAKE) अणु
			spin_lock_irqsave(&ieee->mgmt_tx_lock, flags2);

			अगर (ieee->ps_is_queue_empty(ieee->dev)) अणु
				ieee->sta_sleep = LPS_WAIT_शून्य_DATA_SEND;
				ieee->ack_tx_to_ieee = 1;
				rtllib_sta_ps_send_null_frame(ieee, 1);
				ieee->ps_समय = समय;
			पूर्ण
			spin_unlock_irqrestore(&ieee->mgmt_tx_lock, flags2);

		पूर्ण

		ieee->bAwakePktSent = false;

	पूर्ण अन्यथा अगर (sleep == 2) अणु
		spin_lock_irqsave(&ieee->mgmt_tx_lock, flags2);

		rtllib_sta_wakeup(ieee, 1);

		spin_unlock_irqrestore(&ieee->mgmt_tx_lock, flags2);
	पूर्ण

out:
	spin_unlock_irqrestore(&ieee->lock, flags);

पूर्ण

अटल व्योम rtllib_sta_wakeup(काष्ठा rtllib_device *ieee, लघु nl)
अणु
	अगर (ieee->sta_sleep == LPS_IS_WAKE) अणु
		अगर (nl) अणु
			अगर (ieee->pHTInfo->IOTAction &
			    HT_IOT_ACT_शून्य_DATA_POWER_SAVING) अणु
				ieee->ack_tx_to_ieee = 1;
				rtllib_sta_ps_send_null_frame(ieee, 0);
			पूर्ण अन्यथा अणु
				ieee->ack_tx_to_ieee = 1;
				rtllib_sta_ps_send_pspoll_frame(ieee);
			पूर्ण
		पूर्ण
		वापस;

	पूर्ण

	अगर (ieee->sta_sleep == LPS_IS_SLEEP)
		ieee->sta_wake_up(ieee->dev);
	अगर (nl) अणु
		अगर (ieee->pHTInfo->IOTAction &
		    HT_IOT_ACT_शून्य_DATA_POWER_SAVING) अणु
			ieee->ack_tx_to_ieee = 1;
			rtllib_sta_ps_send_null_frame(ieee, 0);
		पूर्ण अन्यथा अणु
			ieee->ack_tx_to_ieee = 1;
			ieee->polling = true;
			rtllib_sta_ps_send_pspoll_frame(ieee);
		पूर्ण

	पूर्ण अन्यथा अणु
		ieee->sta_sleep = LPS_IS_WAKE;
		ieee->polling = false;
	पूर्ण
पूर्ण

व्योम rtllib_ps_tx_ack(काष्ठा rtllib_device *ieee, लघु success)
अणु
	अचिन्हित दीर्घ flags, flags2;

	spin_lock_irqsave(&ieee->lock, flags);

	अगर (ieee->sta_sleep == LPS_WAIT_शून्य_DATA_SEND) अणु
		/* Null frame with PS bit set */
		अगर (success) अणु
			ieee->sta_sleep = LPS_IS_SLEEP;
			ieee->enter_sleep_state(ieee->dev, ieee->ps_समय);
		पूर्ण
		/* अगर the card report not success we can't be sure the AP
		 * has not RXed so we can't assume the AP believe us awake
		 */
	पूर्ण अन्यथा अणु/* 21112005 - tx again null without PS bit अगर lost */

		अगर ((ieee->sta_sleep == LPS_IS_WAKE) && !success) अणु
			spin_lock_irqsave(&ieee->mgmt_tx_lock, flags2);
			अगर (ieee->pHTInfo->IOTAction &
			    HT_IOT_ACT_शून्य_DATA_POWER_SAVING)
				rtllib_sta_ps_send_null_frame(ieee, 0);
			अन्यथा
				rtllib_sta_ps_send_pspoll_frame(ieee);
			spin_unlock_irqrestore(&ieee->mgmt_tx_lock, flags2);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ieee->lock, flags);
पूर्ण
EXPORT_SYMBOL(rtllib_ps_tx_ack);

अटल व्योम rtllib_process_action(काष्ठा rtllib_device *ieee,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा rtllib_hdr_3addr *header = (काष्ठा rtllib_hdr_3addr *) skb->data;
	u8 *act = rtllib_get_payload((काष्ठा rtllib_hdr *)header);
	u8 category = 0;

	अगर (act == शून्य) अणु
		netdev_warn(ieee->dev,
			    "Error getting payload of action frame\n");
		वापस;
	पूर्ण

	category = *act;
	act++;
	चयन (category) अणु
	हाल ACT_CAT_BA:
		चयन (*act) अणु
		हाल ACT_ADDBAREQ:
			rtllib_rx_ADDBAReq(ieee, skb);
			अवरोध;
		हाल ACT_ADDBARSP:
			rtllib_rx_ADDBARsp(ieee, skb);
			अवरोध;
		हाल ACT_DELBA:
			rtllib_rx_DELBA(ieee, skb);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
rtllib_rx_assoc_resp(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
		     काष्ठा rtllib_rx_stats *rx_stats)
अणु
	u16 errcode;
	पूर्णांक aid;
	u8 *ies;
	काष्ठा rtllib_assoc_response_frame *assoc_resp;
	काष्ठा rtllib_hdr_3addr *header = (काष्ठा rtllib_hdr_3addr *) skb->data;
	u16 frame_ctl = le16_to_cpu(header->frame_ctl);

	netdev_dbg(ieee->dev, "received [RE]ASSOCIATION RESPONSE (%d)\n",
		   WLAN_FC_GET_STYPE(frame_ctl));

	अगर ((ieee->sofपंचांगac_features & IEEE_SOFTMAC_ASSOCIATE) &&
	     ieee->state == RTLLIB_ASSOCIATING_AUTHENTICATED &&
	     (ieee->iw_mode == IW_MODE_INFRA)) अणु
		errcode = assoc_parse(ieee, skb, &aid);
		अगर (!errcode) अणु
			काष्ठा rtllib_network *network =
				 kzalloc(माप(काष्ठा rtllib_network),
				 GFP_ATOMIC);

			अगर (!network)
				वापस 1;
			ieee->state = RTLLIB_LINKED;
			ieee->assoc_id = aid;
			ieee->sofपंचांगac_stats.rx_ass_ok++;
			/* station support qos */
			/* Let the रेजिस्टर setting शेष with Legacy station */
			assoc_resp = (काष्ठा rtllib_assoc_response_frame *)skb->data;
			अगर (ieee->current_network.qos_data.supported == 1) अणु
				अगर (rtllib_parse_info_param(ieee, assoc_resp->info_element,
							rx_stats->len - माप(*assoc_resp),
							network, rx_stats)) अणु
					kमुक्त(network);
					वापस 1;
				पूर्ण
				स_नकल(ieee->pHTInfo->PeerHTCapBuf,
				       network->bssht.bd_ht_cap_buf,
				       network->bssht.bd_ht_cap_len);
				स_नकल(ieee->pHTInfo->PeerHTInfoBuf,
				       network->bssht.bd_ht_info_buf,
				       network->bssht.bd_ht_info_len);
				अगर (ieee->handle_assoc_response != शून्य)
					ieee->handle_assoc_response(ieee->dev,
						 (काष्ठा rtllib_assoc_response_frame *)header,
						 network);
			पूर्ण
			kमुक्त(network);

			kमुक्त(ieee->assocresp_ies);
			ieee->assocresp_ies = शून्य;
			ies = &(assoc_resp->info_element[0].id);
			ieee->assocresp_ies_len = (skb->data + skb->len) - ies;
			ieee->assocresp_ies = kmemdup(ies,
						      ieee->assocresp_ies_len,
						      GFP_ATOMIC);
			अगर (!ieee->assocresp_ies)
				ieee->assocresp_ies_len = 0;

			rtllib_associate_complete(ieee);
		पूर्ण अन्यथा अणु
			/* aid could not been allocated */
			ieee->sofपंचांगac_stats.rx_ass_err++;
			netdev_info(ieee->dev,
				    "Association response status code 0x%x\n",
				    errcode);
			अगर (ieee->AsocRetryCount < RT_ASOC_RETRY_LIMIT)
				schedule_delayed_work(
					 &ieee->associate_procedure_wq, 0);
			अन्यथा
				rtllib_associate_पात(ieee);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम rtllib_rx_auth_resp(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb)
अणु
	u16 errcode;
	u8 *challenge;
	पूर्णांक chlen = 0;
	bool bSupportNmode = true, bHalfSupportNmode = false;

	errcode = auth_parse(ieee->dev, skb, &challenge, &chlen);

	अगर (errcode) अणु
		ieee->sofपंचांगac_stats.rx_auth_rs_err++;
		netdev_info(ieee->dev,
			    "Authentication response status code 0x%x",
			    errcode);
		rtllib_associate_पात(ieee);
		वापस;
	पूर्ण

	अगर (ieee->खोलो_wep || !challenge) अणु
		ieee->state = RTLLIB_ASSOCIATING_AUTHENTICATED;
		ieee->sofपंचांगac_stats.rx_auth_rs_ok++;
		अगर (!(ieee->pHTInfo->IOTAction & HT_IOT_ACT_PURE_N_MODE)) अणु
			अगर (!ieee->GetNmodeSupportBySecCfg(ieee->dev)) अणु
				अगर (IsHTHalfNmodeAPs(ieee)) अणु
					bSupportNmode = true;
					bHalfSupportNmode = true;
				पूर्ण अन्यथा अणु
					bSupportNmode = false;
					bHalfSupportNmode = false;
				पूर्ण
			पूर्ण
		पूर्ण
		/* Dummy wirless mode setting to aव्योम encryption issue */
		अगर (bSupportNmode) अणु
			ieee->SetWirelessMode(ieee->dev,
					      ieee->current_network.mode);
		पूर्ण अन्यथा अणु
			/*TODO*/
			ieee->SetWirelessMode(ieee->dev, IEEE_G);
		पूर्ण

		अगर ((ieee->current_network.mode == IEEE_N_24G) &&
		    bHalfSupportNmode) अणु
			netdev_info(ieee->dev, "======>enter half N mode\n");
			ieee->bHalfWirelessN24GMode = true;
		पूर्ण अन्यथा अणु
			ieee->bHalfWirelessN24GMode = false;
		पूर्ण
		rtllib_associate_step2(ieee);
	पूर्ण अन्यथा अणु
		rtllib_auth_challenge(ieee, challenge,  chlen);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
rtllib_rx_auth(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
	       काष्ठा rtllib_rx_stats *rx_stats)
अणु

	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_ASSOCIATE) अणु
		अगर (ieee->state == RTLLIB_ASSOCIATING_AUTHENTICATING &&
		    (ieee->iw_mode == IW_MODE_INFRA)) अणु
			netdev_dbg(ieee->dev,
				   "Received authentication response");
			rtllib_rx_auth_resp(ieee, skb);
		पूर्ण अन्यथा अगर (ieee->iw_mode == IW_MODE_MASTER) अणु
			rtllib_rx_auth_rq(ieee, skb);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
rtllib_rx_deauth(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtllib_hdr_3addr *header = (काष्ठा rtllib_hdr_3addr *) skb->data;
	u16 frame_ctl;

	अगर (स_भेद(header->addr3, ieee->current_network.bssid, ETH_ALEN) != 0)
		वापस 0;

	/* FIXME क्रम now repeat all the association procedure
	 * both क्रम disassociation and deauthentication
	 */
	अगर ((ieee->sofपंचांगac_features & IEEE_SOFTMAC_ASSOCIATE) &&
	    ieee->state == RTLLIB_LINKED &&
	    (ieee->iw_mode == IW_MODE_INFRA)) अणु
		frame_ctl = le16_to_cpu(header->frame_ctl);
		netdev_info(ieee->dev,
			    "==========>received disassoc/deauth(%x) frame, reason code:%x\n",
			    WLAN_FC_GET_STYPE(frame_ctl),
			    ((काष्ठा rtllib_disassoc *)skb->data)->reason);
		ieee->state = RTLLIB_ASSOCIATING;
		ieee->sofपंचांगac_stats.reassoc++;
		ieee->is_roaming = true;
		ieee->LinkDetectInfo.bBusyTraffic = false;
		rtllib_disassociate(ieee);
		RemovePeerTS(ieee, header->addr2);
		अगर (ieee->LedControlHandler != शून्य)
			ieee->LedControlHandler(ieee->dev,
						LED_CTL_START_TO_LINK);

		अगर (!(ieee->rtllib_ap_sec_type(ieee) &
		    (SEC_ALG_CCMP|SEC_ALG_TKIP)))
			schedule_delayed_work(
				       &ieee->associate_procedure_wq, 5);
	पूर्ण
	वापस 0;
पूर्ण

अंतरभूत पूर्णांक rtllib_rx_frame_sofपंचांगac(काष्ठा rtllib_device *ieee,
				   काष्ठा sk_buff *skb,
				   काष्ठा rtllib_rx_stats *rx_stats, u16 type,
				   u16 stype)
अणु
	काष्ठा rtllib_hdr_3addr *header = (काष्ठा rtllib_hdr_3addr *) skb->data;
	u16 frame_ctl;

	अगर (!ieee->proto_started)
		वापस 0;

	frame_ctl = le16_to_cpu(header->frame_ctl);
	चयन (WLAN_FC_GET_STYPE(frame_ctl)) अणु
	हाल RTLLIB_STYPE_ASSOC_RESP:
	हाल RTLLIB_STYPE_REASSOC_RESP:
		अगर (rtllib_rx_assoc_resp(ieee, skb, rx_stats) == 1)
			वापस 1;
		अवरोध;
	हाल RTLLIB_STYPE_ASSOC_REQ:
	हाल RTLLIB_STYPE_REASSOC_REQ:
		अगर ((ieee->sofपंचांगac_features & IEEE_SOFTMAC_ASSOCIATE) &&
		     ieee->iw_mode == IW_MODE_MASTER)
			rtllib_rx_assoc_rq(ieee, skb);
		अवरोध;
	हाल RTLLIB_STYPE_AUTH:
		rtllib_rx_auth(ieee, skb, rx_stats);
		अवरोध;
	हाल RTLLIB_STYPE_DISASSOC:
	हाल RTLLIB_STYPE_DEAUTH:
		rtllib_rx_deauth(ieee, skb);
		अवरोध;
	हाल RTLLIB_STYPE_MANAGE_ACT:
		rtllib_process_action(ieee, skb);
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/* following are क्रम a simpler TX queue management.
 * Instead of using netअगर_[stop/wake]_queue the driver
 * will use these two functions (plus a reset one), that
 * will पूर्णांकernally use the kernel netअगर_* and takes
 * care of the ieee802.11 fragmentation.
 * So the driver receives a fragment per समय and might
 * call the stop function when it wants to not
 * have enough room to TX an entire packet.
 * This might be useful अगर each fragment needs it's own
 * descriptor, thus just keep a total मुक्त memory > than
 * the max fragmentation threshold is not enough.. If the
 * ieee802.11 stack passed a TXB काष्ठा then you need
 * to keep N मुक्त descriptors where
 * N = MAX_PACKET_SIZE / MIN_FRAG_TRESHOLD
 * In this way you need just one and the 802.11 stack
 * will take care of buffering fragments and pass them to
 * the driver later, when it wakes the queue.
 */
व्योम rtllib_sofपंचांगac_xmit(काष्ठा rtllib_txb *txb, काष्ठा rtllib_device *ieee)
अणु

	अचिन्हित पूर्णांक queue_index = txb->queue_index;
	अचिन्हित दीर्घ flags;
	पूर्णांक  i;
	काष्ठा cb_desc *tcb_desc = शून्य;
	अचिन्हित दीर्घ queue_len = 0;

	spin_lock_irqsave(&ieee->lock, flags);

	/* called with 2nd parm 0, no tx mgmt lock required */
	rtllib_sta_wakeup(ieee, 0);

	/* update the tx status */
	tcb_desc = (काष्ठा cb_desc *)(txb->fragments[0]->cb +
		   MAX_DEV_ADDR_SIZE);
	अगर (tcb_desc->bMulticast)
		ieee->stats.multicast++;

	/* अगर xmit available, just xmit it immediately, अन्यथा just insert it to
	 * the रुको queue
	 */
	क्रम (i = 0; i < txb->nr_frags; i++) अणु
		queue_len = skb_queue_len(&ieee->skb_रुकोQ[queue_index]);
		अगर ((queue_len  != 0) ||
		    (!ieee->check_nic_enough_desc(ieee->dev, queue_index)) ||
		    (ieee->queue_stop)) अणु
			/* insert the skb packet to the रुको queue
			 * as क्रम the completion function, it करोes not need
			 * to check it any more.
			 */
			अगर (queue_len < 200)
				skb_queue_tail(&ieee->skb_रुकोQ[queue_index],
					       txb->fragments[i]);
			अन्यथा
				kमुक्त_skb(txb->fragments[i]);
		पूर्ण अन्यथा अणु
			ieee->sofपंचांगac_data_hard_start_xmit(
					txb->fragments[i],
					ieee->dev, ieee->rate);
		पूर्ण
	पूर्ण

	rtllib_txb_मुक्त(txb);

	spin_unlock_irqrestore(&ieee->lock, flags);

पूर्ण

व्योम rtllib_reset_queue(काष्ठा rtllib_device *ieee)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ieee->lock, flags);
	init_mgmt_queue(ieee);
	अगर (ieee->tx_pending.txb) अणु
		rtllib_txb_मुक्त(ieee->tx_pending.txb);
		ieee->tx_pending.txb = शून्य;
	पूर्ण
	ieee->queue_stop = 0;
	spin_unlock_irqrestore(&ieee->lock, flags);

पूर्ण
EXPORT_SYMBOL(rtllib_reset_queue);

व्योम rtllib_stop_all_queues(काष्ठा rtllib_device *ieee)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ieee->dev->num_tx_queues; i++)
		netdev_get_tx_queue(ieee->dev, i)->trans_start = jअगरfies;

	netअगर_tx_stop_all_queues(ieee->dev);
पूर्ण

व्योम rtllib_wake_all_queues(काष्ठा rtllib_device *ieee)
अणु
	netअगर_tx_wake_all_queues(ieee->dev);
पूर्ण

/* called in user context only */
अटल व्योम rtllib_start_master_bss(काष्ठा rtllib_device *ieee)
अणु
	ieee->assoc_id = 1;

	अगर (ieee->current_network.ssid_len == 0) अणु
		म_नकलन(ieee->current_network.ssid,
			RTLLIB_DEFAULT_TX_ESSID,
			IW_ESSID_MAX_SIZE);

		ieee->current_network.ssid_len =
				 म_माप(RTLLIB_DEFAULT_TX_ESSID);
		ieee->ssid_set = 1;
	पूर्ण

	ether_addr_copy(ieee->current_network.bssid, ieee->dev->dev_addr);

	ieee->set_chan(ieee->dev, ieee->current_network.channel);
	ieee->state = RTLLIB_LINKED;
	ieee->link_change(ieee->dev);
	notअगरy_wx_assoc_event(ieee);

	अगर (ieee->data_hard_resume)
		ieee->data_hard_resume(ieee->dev);

	netअगर_carrier_on(ieee->dev);
पूर्ण

अटल व्योम rtllib_start_monitor_mode(काष्ठा rtllib_device *ieee)
अणु
	/* reset hardware status */
	अगर (ieee->raw_tx) अणु
		अगर (ieee->data_hard_resume)
			ieee->data_hard_resume(ieee->dev);

		netअगर_carrier_on(ieee->dev);
	पूर्ण
पूर्ण

अटल व्योम rtllib_start_ibss_wq(व्योम *data)
अणु
	काष्ठा rtllib_device *ieee = container_of_dwork_rsl(data,
				     काष्ठा rtllib_device, start_ibss_wq);
	/* iwconfig mode ad-hoc will schedule this and वापस
	 * on the other hand this will block further iwconfig SET
	 * operations because of the wx_mutex hold.
	 * Anyway some most set operations set a flag to speed-up
	 * (पात) this wq (when syncro scanning) beक्रमe sleeping
	 * on the mutex
	 */
	अगर (!ieee->proto_started) अणु
		netdev_info(ieee->dev, "==========oh driver down return\n");
		वापस;
	पूर्ण
	mutex_lock(&ieee->wx_mutex);

	अगर (ieee->current_network.ssid_len == 0) अणु
		म_नकल(ieee->current_network.ssid, RTLLIB_DEFAULT_TX_ESSID);
		ieee->current_network.ssid_len = म_माप(RTLLIB_DEFAULT_TX_ESSID);
		ieee->ssid_set = 1;
	पूर्ण

	ieee->state = RTLLIB_NOLINK;
	ieee->mode = IEEE_G;
	/* check अगर we have this cell in our network list */
	rtllib_sofपंचांगac_check_all_nets(ieee);


	/* अगर not then the state is not linked. Maybe the user चयनed to
	 * ad-hoc mode just after being in monitor mode, or just after
	 * being very few समय in managed mode (so the card have had no
	 * समय to scan all the chans..) or we have just run up the अगरace
	 * after setting ad-hoc mode. So we have to give another try..
	 * Here, in ibss mode, should be safe to करो this without extra care
	 * (in bss mode we had to make sure no-one tried to associate when
	 * we had just checked the ieee->state and we was going to start the
	 * scan) because in ibss mode the rtllib_new_net function, when
	 * finds a good net, just set the ieee->state to RTLLIB_LINKED,
	 * so, at worst, we waste a bit of समय to initiate an unneeded syncro
	 * scan, that will stop at the first round because it sees the state
	 * associated.
	 */
	अगर (ieee->state == RTLLIB_NOLINK)
		rtllib_start_scan_syncro(ieee, 0);

	/* the network definitively is not here.. create a new cell */
	अगर (ieee->state == RTLLIB_NOLINK) अणु
		netdev_info(ieee->dev, "creating new IBSS cell\n");
		ieee->current_network.channel = ieee->bss_start_channel;
		अगर (!ieee->wap_set)
			eth_अक्रमom_addr(ieee->current_network.bssid);

		अगर (ieee->modulation & RTLLIB_CCK_MODULATION) अणु

			ieee->current_network.rates_len = 4;

			ieee->current_network.rates[0] =
				 RTLLIB_BASIC_RATE_MASK | RTLLIB_CCK_RATE_1MB;
			ieee->current_network.rates[1] =
				 RTLLIB_BASIC_RATE_MASK | RTLLIB_CCK_RATE_2MB;
			ieee->current_network.rates[2] =
				 RTLLIB_BASIC_RATE_MASK | RTLLIB_CCK_RATE_5MB;
			ieee->current_network.rates[3] =
				 RTLLIB_BASIC_RATE_MASK | RTLLIB_CCK_RATE_11MB;

		पूर्ण अन्यथा
			ieee->current_network.rates_len = 0;

		अगर (ieee->modulation & RTLLIB_OFDM_MODULATION) अणु
			ieee->current_network.rates_ex_len = 8;

			ieee->current_network.rates_ex[0] =
						 RTLLIB_OFDM_RATE_6MB;
			ieee->current_network.rates_ex[1] =
						 RTLLIB_OFDM_RATE_9MB;
			ieee->current_network.rates_ex[2] =
						 RTLLIB_OFDM_RATE_12MB;
			ieee->current_network.rates_ex[3] =
						 RTLLIB_OFDM_RATE_18MB;
			ieee->current_network.rates_ex[4] =
						 RTLLIB_OFDM_RATE_24MB;
			ieee->current_network.rates_ex[5] =
						 RTLLIB_OFDM_RATE_36MB;
			ieee->current_network.rates_ex[6] =
						 RTLLIB_OFDM_RATE_48MB;
			ieee->current_network.rates_ex[7] =
						 RTLLIB_OFDM_RATE_54MB;

			ieee->rate = 108;
		पूर्ण अन्यथा अणु
			ieee->current_network.rates_ex_len = 0;
			ieee->rate = 22;
		पूर्ण

		ieee->current_network.qos_data.supported = 0;
		ieee->SetWirelessMode(ieee->dev, IEEE_G);
		ieee->current_network.mode = ieee->mode;
		ieee->current_network.atim_winकरोw = 0;
		ieee->current_network.capability = WLAN_CAPABILITY_IBSS;
	पूर्ण

	netdev_info(ieee->dev, "%s(): ieee->mode = %d\n", __func__, ieee->mode);
	अगर ((ieee->mode == IEEE_N_24G) || (ieee->mode == IEEE_N_5G))
		HTUseDefaultSetting(ieee);
	अन्यथा
		ieee->pHTInfo->bCurrentHTSupport = false;

	ieee->SetHwRegHandler(ieee->dev, HW_VAR_MEDIA_STATUS,
			      (u8 *)(&ieee->state));

	ieee->state = RTLLIB_LINKED;
	ieee->link_change(ieee->dev);

	HTSetConnectBwMode(ieee, HT_CHANNEL_WIDTH_20, HT_EXTCHNL_OFFSET_NO_EXT);
	अगर (ieee->LedControlHandler != शून्य)
		ieee->LedControlHandler(ieee->dev, LED_CTL_LINK);

	rtllib_start_send_beacons(ieee);

	notअगरy_wx_assoc_event(ieee);

	अगर (ieee->data_hard_resume)
		ieee->data_hard_resume(ieee->dev);

	netअगर_carrier_on(ieee->dev);

	mutex_unlock(&ieee->wx_mutex);
पूर्ण

अंतरभूत व्योम rtllib_start_ibss(काष्ठा rtllib_device *ieee)
अणु
	schedule_delayed_work(&ieee->start_ibss_wq, msecs_to_jअगरfies(150));
पूर्ण

/* this is called only in user context, with wx_mutex held */
अटल व्योम rtllib_start_bss(काष्ठा rtllib_device *ieee)
अणु
	अचिन्हित दीर्घ flags;

	अगर (IS_DOT11D_ENABLE(ieee) && !IS_COUNTRY_IE_VALID(ieee)) अणु
		अगर (!ieee->global_करोमुख्य)
			वापस;
	पूर्ण
	/* check अगर we have alपढ़ोy found the net we
	 * are पूर्णांकerested in (अगर any).
	 * अगर not (we are disassociated and we are not
	 * in associating / authenticating phase) start the background scanning.
	 */
	rtllib_sofपंचांगac_check_all_nets(ieee);

	/* ensure no-one start an associating process (thus setting
	 * the ieee->state to rtllib_ASSOCIATING) जबतक we
	 * have just checked it and we are going to enable scan.
	 * The rtllib_new_net function is always called with
	 * lock held (from both rtllib_sofपंचांगac_check_all_nets and
	 * the rx path), so we cannot be in the middle of such function
	 */
	spin_lock_irqsave(&ieee->lock, flags);

	अगर (ieee->state == RTLLIB_NOLINK)
		rtllib_start_scan(ieee);
	spin_unlock_irqrestore(&ieee->lock, flags);
पूर्ण

अटल व्योम rtllib_link_change_wq(व्योम *data)
अणु
	काष्ठा rtllib_device *ieee = container_of_dwork_rsl(data,
				     काष्ठा rtllib_device, link_change_wq);
	ieee->link_change(ieee->dev);
पूर्ण
/* called only in userspace context */
व्योम rtllib_disassociate(काष्ठा rtllib_device *ieee)
अणु
	netअगर_carrier_off(ieee->dev);
	अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_TX_QUEUE)
		rtllib_reset_queue(ieee);

	अगर (ieee->data_hard_stop)
		ieee->data_hard_stop(ieee->dev);
	अगर (IS_DOT11D_ENABLE(ieee))
		करोt11d_reset(ieee);
	ieee->state = RTLLIB_NOLINK;
	ieee->is_set_key = false;
	ieee->wap_set = 0;

	schedule_delayed_work(&ieee->link_change_wq, 0);

	notअगरy_wx_assoc_event(ieee);
पूर्ण

अटल व्योम rtllib_associate_retry_wq(व्योम *data)
अणु
	काष्ठा rtllib_device *ieee = container_of_dwork_rsl(data,
				     काष्ठा rtllib_device, associate_retry_wq);
	अचिन्हित दीर्घ flags;

	mutex_lock(&ieee->wx_mutex);
	अगर (!ieee->proto_started)
		जाओ निकास;

	अगर (ieee->state != RTLLIB_ASSOCIATING_RETRY)
		जाओ निकास;

	/* until we करो not set the state to RTLLIB_NOLINK
	 * there are no possibility to have someone अन्यथा trying
	 * to start an association procedure (we get here with
	 * ieee->state = RTLLIB_ASSOCIATING).
	 * When we set the state to RTLLIB_NOLINK it is possible
	 * that the RX path run an attempt to associate, but
	 * both rtllib_sofपंचांगac_check_all_nets and the
	 * RX path works with ieee->lock held so there are no
	 * problems. If we are still disassociated then start a scan.
	 * the lock here is necessary to ensure no one try to start
	 * an association procedure when we have just checked the
	 * state and we are going to start the scan.
	 */
	ieee->beinretry = true;
	ieee->state = RTLLIB_NOLINK;

	rtllib_sofपंचांगac_check_all_nets(ieee);

	spin_lock_irqsave(&ieee->lock, flags);

	अगर (ieee->state == RTLLIB_NOLINK)
		rtllib_start_scan(ieee);
	spin_unlock_irqrestore(&ieee->lock, flags);

	ieee->beinretry = false;
निकास:
	mutex_unlock(&ieee->wx_mutex);
पूर्ण

अटल काष्ठा sk_buff *rtllib_get_beacon_(काष्ठा rtllib_device *ieee)
अणु
	अटल स्थिर u8 broadcast_addr[] = अणु
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	पूर्ण;
	काष्ठा sk_buff *skb;
	काष्ठा rtllib_probe_response *b;

	skb = rtllib_probe_resp(ieee, broadcast_addr);

	अगर (!skb)
		वापस शून्य;

	b = (काष्ठा rtllib_probe_response *) skb->data;
	b->header.frame_ctl = cpu_to_le16(RTLLIB_STYPE_BEACON);

	वापस skb;

पूर्ण

काष्ठा sk_buff *rtllib_get_beacon(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rtllib_probe_response *b;

	skb = rtllib_get_beacon_(ieee);
	अगर (!skb)
		वापस शून्य;

	b = (काष्ठा rtllib_probe_response *) skb->data;
	b->header.seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

	अगर (ieee->seq_ctrl[0] == 0xFFF)
		ieee->seq_ctrl[0] = 0;
	अन्यथा
		ieee->seq_ctrl[0]++;

	वापस skb;
पूर्ण
EXPORT_SYMBOL(rtllib_get_beacon);

व्योम rtllib_sofपंचांगac_stop_protocol(काष्ठा rtllib_device *ieee, u8 mesh_flag,
				  u8 shutकरोwn)
अणु
	rtllib_stop_scan_syncro(ieee);
	mutex_lock(&ieee->wx_mutex);
	rtllib_stop_protocol(ieee, shutकरोwn);
	mutex_unlock(&ieee->wx_mutex);
पूर्ण
EXPORT_SYMBOL(rtllib_sofपंचांगac_stop_protocol);


व्योम rtllib_stop_protocol(काष्ठा rtllib_device *ieee, u8 shutकरोwn)
अणु
	अगर (!ieee->proto_started)
		वापस;

	अगर (shutकरोwn) अणु
		ieee->proto_started = 0;
		ieee->proto_stoppping = 1;
		अगर (ieee->rtllib_ips_leave != शून्य)
			ieee->rtllib_ips_leave(ieee->dev);
	पूर्ण

	rtllib_stop_send_beacons(ieee);
	del_समयr_sync(&ieee->associate_समयr);
	cancel_delayed_work_sync(&ieee->associate_retry_wq);
	cancel_delayed_work_sync(&ieee->start_ibss_wq);
	cancel_delayed_work_sync(&ieee->link_change_wq);
	rtllib_stop_scan(ieee);

	अगर (ieee->state <= RTLLIB_ASSOCIATING_AUTHENTICATED)
		ieee->state = RTLLIB_NOLINK;

	अगर (ieee->state == RTLLIB_LINKED) अणु
		अगर (ieee->iw_mode == IW_MODE_INFRA)
			SendDisassociation(ieee, 1, WLAN_REASON_DEAUTH_LEAVING);
		rtllib_disassociate(ieee);
	पूर्ण

	अगर (shutकरोwn) अणु
		RemoveAllTS(ieee);
		ieee->proto_stoppping = 0;
	पूर्ण
	kमुक्त(ieee->assocreq_ies);
	ieee->assocreq_ies = शून्य;
	ieee->assocreq_ies_len = 0;
	kमुक्त(ieee->assocresp_ies);
	ieee->assocresp_ies = शून्य;
	ieee->assocresp_ies_len = 0;
पूर्ण

व्योम rtllib_sofपंचांगac_start_protocol(काष्ठा rtllib_device *ieee, u8 mesh_flag)
अणु
	mutex_lock(&ieee->wx_mutex);
	rtllib_start_protocol(ieee);
	mutex_unlock(&ieee->wx_mutex);
पूर्ण
EXPORT_SYMBOL(rtllib_sofपंचांगac_start_protocol);

व्योम rtllib_start_protocol(काष्ठा rtllib_device *ieee)
अणु
	लघु ch = 0;
	पूर्णांक i = 0;

	rtllib_update_active_chan_map(ieee);

	अगर (ieee->proto_started)
		वापस;

	ieee->proto_started = 1;

	अगर (ieee->current_network.channel == 0) अणु
		करो अणु
			ch++;
			अगर (ch > MAX_CHANNEL_NUMBER)
				वापस; /* no channel found */
		पूर्ण जबतक (!ieee->active_channel_map[ch]);
		ieee->current_network.channel = ch;
	पूर्ण

	अगर (ieee->current_network.beacon_पूर्णांकerval == 0)
		ieee->current_network.beacon_पूर्णांकerval = 100;

	क्रम (i = 0; i < 17; i++) अणु
		ieee->last_rxseq_num[i] = -1;
		ieee->last_rxfrag_num[i] = -1;
		ieee->last_packet_समय[i] = 0;
	पूर्ण

	अगर (ieee->UpdateBeaconInterruptHandler)
		ieee->UpdateBeaconInterruptHandler(ieee->dev, false);

	ieee->wmm_acm = 0;
	/* अगर the user set the MAC of the ad-hoc cell and then
	 * चयन to managed mode, shall we  make sure that association
	 * attempts करोes not fail just because the user provide the essid
	 * and the nic is still checking क्रम the AP MAC ??
	 */
	अगर (ieee->iw_mode == IW_MODE_INFRA) अणु
		rtllib_start_bss(ieee);
	पूर्ण अन्यथा अगर (ieee->iw_mode == IW_MODE_ADHOC) अणु
		अगर (ieee->UpdateBeaconInterruptHandler)
			ieee->UpdateBeaconInterruptHandler(ieee->dev, true);

		rtllib_start_ibss(ieee);

	पूर्ण अन्यथा अगर (ieee->iw_mode == IW_MODE_MASTER) अणु
		rtllib_start_master_bss(ieee);
	पूर्ण अन्यथा अगर (ieee->iw_mode == IW_MODE_MONITOR) अणु
		rtllib_start_monitor_mode(ieee);
	पूर्ण
पूर्ण

व्योम rtllib_sofपंचांगac_init(काष्ठा rtllib_device *ieee)
अणु
	पूर्णांक i;

	स_रखो(&ieee->current_network, 0, माप(काष्ठा rtllib_network));

	ieee->state = RTLLIB_NOLINK;
	क्रम (i = 0; i < 5; i++)
		ieee->seq_ctrl[i] = 0;
	ieee->करोt11d_info = kzalloc(माप(काष्ठा rt_करोt11d_info), GFP_ATOMIC);
	अगर (!ieee->करोt11d_info)
		netdev_err(ieee->dev, "Can't alloc memory for DOT11D\n");
	ieee->LinkDetectInfo.SlotIndex = 0;
	ieee->LinkDetectInfo.SlotNum = 2;
	ieee->LinkDetectInfo.NumRecvBcnInPeriod = 0;
	ieee->LinkDetectInfo.NumRecvDataInPeriod = 0;
	ieee->LinkDetectInfo.NumTxOkInPeriod = 0;
	ieee->LinkDetectInfo.NumRxOkInPeriod = 0;
	ieee->LinkDetectInfo.NumRxUnicastOkInPeriod = 0;
	ieee->bIsAggregateFrame = false;
	ieee->assoc_id = 0;
	ieee->queue_stop = 0;
	ieee->scanning_जारी = 0;
	ieee->sofपंचांगac_features = 0;
	ieee->wap_set = 0;
	ieee->ssid_set = 0;
	ieee->proto_started = 0;
	ieee->proto_stoppping = 0;
	ieee->basic_rate = RTLLIB_DEFAULT_BASIC_RATE;
	ieee->rate = 22;
	ieee->ps = RTLLIB_PS_DISABLED;
	ieee->sta_sleep = LPS_IS_WAKE;

	ieee->Regकरोt11HTOperationalRateSet[0] = 0xff;
	ieee->Regकरोt11HTOperationalRateSet[1] = 0xff;
	ieee->Regकरोt11HTOperationalRateSet[4] = 0x01;

	ieee->Regकरोt11TxHTOperationalRateSet[0] = 0xff;
	ieee->Regकरोt11TxHTOperationalRateSet[1] = 0xff;
	ieee->Regकरोt11TxHTOperationalRateSet[4] = 0x01;

	ieee->FirstIe_InScan = false;
	ieee->actscanning = false;
	ieee->beinretry = false;
	ieee->is_set_key = false;
	init_mgmt_queue(ieee);

	ieee->tx_pending.txb = शून्य;

	समयr_setup(&ieee->associate_समयr, rtllib_associate_पात_cb, 0);

	समयr_setup(&ieee->beacon_समयr, rtllib_send_beacon_cb, 0);

	INIT_DELAYED_WORK_RSL(&ieee->link_change_wq,
			      (व्योम *)rtllib_link_change_wq, ieee);
	INIT_DELAYED_WORK_RSL(&ieee->start_ibss_wq,
			      (व्योम *)rtllib_start_ibss_wq, ieee);
	INIT_WORK_RSL(&ieee->associate_complete_wq,
		      (व्योम *)rtllib_associate_complete_wq, ieee);
	INIT_DELAYED_WORK_RSL(&ieee->associate_procedure_wq,
			      (व्योम *)rtllib_associate_procedure_wq, ieee);
	INIT_DELAYED_WORK_RSL(&ieee->sofपंचांगac_scan_wq,
			      (व्योम *)rtllib_sofपंचांगac_scan_wq, ieee);
	INIT_DELAYED_WORK_RSL(&ieee->associate_retry_wq,
			      (व्योम *)rtllib_associate_retry_wq, ieee);
	INIT_WORK_RSL(&ieee->wx_sync_scan_wq, (व्योम *)rtllib_wx_sync_scan_wq,
		      ieee);

	mutex_init(&ieee->wx_mutex);
	mutex_init(&ieee->scan_mutex);
	mutex_init(&ieee->ips_mutex);

	spin_lock_init(&ieee->mgmt_tx_lock);
	spin_lock_init(&ieee->beacon_lock);

	tasklet_setup(&ieee->ps_task, rtllib_sta_ps);

पूर्ण

व्योम rtllib_sofपंचांगac_मुक्त(काष्ठा rtllib_device *ieee)
अणु
	mutex_lock(&ieee->wx_mutex);
	kमुक्त(ieee->करोt11d_info);
	ieee->करोt11d_info = शून्य;
	del_समयr_sync(&ieee->associate_समयr);

	cancel_delayed_work_sync(&ieee->associate_retry_wq);
	cancel_delayed_work_sync(&ieee->associate_procedure_wq);
	cancel_delayed_work_sync(&ieee->sofपंचांगac_scan_wq);
	cancel_delayed_work_sync(&ieee->start_ibss_wq);
	cancel_delayed_work_sync(&ieee->hw_wakeup_wq);
	cancel_delayed_work_sync(&ieee->hw_sleep_wq);
	cancel_delayed_work_sync(&ieee->link_change_wq);
	cancel_work_sync(&ieee->associate_complete_wq);
	cancel_work_sync(&ieee->ips_leave_wq);
	cancel_work_sync(&ieee->wx_sync_scan_wq);
	mutex_unlock(&ieee->wx_mutex);
	tasklet_समाप्त(&ieee->ps_task);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *
rtllib_disauth_skb(काष्ठा rtllib_network *beacon,
		   काष्ठा rtllib_device *ieee, u16 asRsn)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rtllib_disauth *disauth;
	पूर्णांक len = माप(काष्ठा rtllib_disauth) + ieee->tx_headroom;

	skb = dev_alloc_skb(len);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, ieee->tx_headroom);

	disauth = skb_put(skb, माप(काष्ठा rtllib_disauth));
	disauth->header.frame_ctl = cpu_to_le16(RTLLIB_STYPE_DEAUTH);
	disauth->header.duration_id = 0;

	ether_addr_copy(disauth->header.addr1, beacon->bssid);
	ether_addr_copy(disauth->header.addr2, ieee->dev->dev_addr);
	ether_addr_copy(disauth->header.addr3, beacon->bssid);

	disauth->reason = cpu_to_le16(asRsn);
	वापस skb;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *
rtllib_disassociate_skb(काष्ठा rtllib_network *beacon,
			काष्ठा rtllib_device *ieee, u16 asRsn)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rtllib_disassoc *disass;
	पूर्णांक len = माप(काष्ठा rtllib_disassoc) + ieee->tx_headroom;

	skb = dev_alloc_skb(len);

	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, ieee->tx_headroom);

	disass = skb_put(skb, माप(काष्ठा rtllib_disassoc));
	disass->header.frame_ctl = cpu_to_le16(RTLLIB_STYPE_DISASSOC);
	disass->header.duration_id = 0;

	ether_addr_copy(disass->header.addr1, beacon->bssid);
	ether_addr_copy(disass->header.addr2, ieee->dev->dev_addr);
	ether_addr_copy(disass->header.addr3, beacon->bssid);

	disass->reason = cpu_to_le16(asRsn);
	वापस skb;
पूर्ण

व्योम SendDisassociation(काष्ठा rtllib_device *ieee, bool deauth, u16 asRsn)
अणु
	काष्ठा rtllib_network *beacon = &ieee->current_network;
	काष्ठा sk_buff *skb;

	अगर (deauth)
		skb = rtllib_disauth_skb(beacon, ieee, asRsn);
	अन्यथा
		skb = rtllib_disassociate_skb(beacon, ieee, asRsn);

	अगर (skb)
		sofपंचांगac_mgmt_xmit(skb, ieee);
पूर्ण

u8 rtllib_ap_sec_type(काष्ठा rtllib_device *ieee)
अणु
	अटल u8 ccmp_ie[4] = अणु0x00, 0x50, 0xf2, 0x04पूर्ण;
	अटल u8 ccmp_rsn_ie[4] = अणु0x00, 0x0f, 0xac, 0x04पूर्ण;
	पूर्णांक wpa_ie_len = ieee->wpa_ie_len;
	काष्ठा lib80211_crypt_data *crypt;
	पूर्णांक encrypt;

	crypt = ieee->crypt_info.crypt[ieee->crypt_info.tx_keyidx];
	encrypt = (ieee->current_network.capability & WLAN_CAPABILITY_PRIVACY)
		  || (ieee->host_encrypt && crypt && crypt->ops &&
		  (म_भेद(crypt->ops->name, "R-WEP") == 0));

	/* simply judge  */
	अगर (encrypt && (wpa_ie_len == 0)) अणु
		वापस SEC_ALG_WEP;
	पूर्ण अन्यथा अगर ((wpa_ie_len != 0)) अणु
		अगर (((ieee->wpa_ie[0] == 0xdd) &&
		    (!स_भेद(&(ieee->wpa_ie[14]), ccmp_ie, 4))) ||
		    ((ieee->wpa_ie[0] == 0x30) &&
		    (!स_भेद(&ieee->wpa_ie[10], ccmp_rsn_ie, 4))))
			वापस SEC_ALG_CCMP;
		अन्यथा
			वापस SEC_ALG_TKIP;
	पूर्ण अन्यथा अणु
		वापस SEC_ALG_NONE;
	पूर्ण
पूर्ण

अटल व्योम rtllib_MgntDisconnectIBSS(काष्ठा rtllib_device *rtllib)
अणु
	u8	OpMode;
	u8	i;
	bool	bFilterOutNonAssociatedBSSID = false;

	rtllib->state = RTLLIB_NOLINK;

	क्रम (i = 0; i < 6; i++)
		rtllib->current_network.bssid[i] = 0x55;

	rtllib->OpMode = RT_OP_MODE_NO_LINK;
	rtllib->SetHwRegHandler(rtllib->dev, HW_VAR_BSSID,
				rtllib->current_network.bssid);
	OpMode = RT_OP_MODE_NO_LINK;
	rtllib->SetHwRegHandler(rtllib->dev, HW_VAR_MEDIA_STATUS, &OpMode);
	rtllib_stop_send_beacons(rtllib);

	bFilterOutNonAssociatedBSSID = false;
	rtllib->SetHwRegHandler(rtllib->dev, HW_VAR_CECHK_BSSID,
				(u8 *)(&bFilterOutNonAssociatedBSSID));
	notअगरy_wx_assoc_event(rtllib);

पूर्ण

अटल व्योम rtllib_MlmeDisassociateRequest(काष्ठा rtllib_device *rtllib,
					   u8 *asSta, u8 asRsn)
अणु
	u8 i;
	u8	OpMode;

	RemovePeerTS(rtllib, asSta);

	अगर (स_भेद(rtllib->current_network.bssid, asSta, 6) == 0) अणु
		rtllib->state = RTLLIB_NOLINK;

		क्रम (i = 0; i < 6; i++)
			rtllib->current_network.bssid[i] = 0x22;
		OpMode = RT_OP_MODE_NO_LINK;
		rtllib->OpMode = RT_OP_MODE_NO_LINK;
		rtllib->SetHwRegHandler(rtllib->dev, HW_VAR_MEDIA_STATUS,
					(u8 *)(&OpMode));
		rtllib_disassociate(rtllib);

		rtllib->SetHwRegHandler(rtllib->dev, HW_VAR_BSSID,
					rtllib->current_network.bssid);

	पूर्ण

पूर्ण

अटल व्योम
rtllib_MgntDisconnectAP(
	काष्ठा rtllib_device *rtllib,
	u8 asRsn
)
अणु
	bool bFilterOutNonAssociatedBSSID = false;

	bFilterOutNonAssociatedBSSID = false;
	rtllib->SetHwRegHandler(rtllib->dev, HW_VAR_CECHK_BSSID,
				(u8 *)(&bFilterOutNonAssociatedBSSID));
	rtllib_MlmeDisassociateRequest(rtllib, rtllib->current_network.bssid,
				       asRsn);

	rtllib->state = RTLLIB_NOLINK;
पूर्ण

bool rtllib_MgntDisconnect(काष्ठा rtllib_device *rtllib, u8 asRsn)
अणु
	अगर (rtllib->ps != RTLLIB_PS_DISABLED)
		rtllib->sta_wake_up(rtllib->dev);

	अगर (rtllib->state == RTLLIB_LINKED) अणु
		अगर (rtllib->iw_mode == IW_MODE_ADHOC)
			rtllib_MgntDisconnectIBSS(rtllib);
		अगर (rtllib->iw_mode == IW_MODE_INFRA)
			rtllib_MgntDisconnectAP(rtllib, asRsn);

	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(rtllib_MgntDisconnect);

व्योम notअगरy_wx_assoc_event(काष्ठा rtllib_device *ieee)
अणु
	जोड़ iwreq_data wrqu;

	अगर (ieee->cannot_notअगरy)
		वापस;

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	अगर (ieee->state == RTLLIB_LINKED)
		स_नकल(wrqu.ap_addr.sa_data, ieee->current_network.bssid,
		       ETH_ALEN);
	अन्यथा अणु

		netdev_info(ieee->dev, "%s(): Tell user space disconnected\n",
			    __func__);
		eth_zero_addr(wrqu.ap_addr.sa_data);
	पूर्ण
	wireless_send_event(ieee->dev, SIOCGIWAP, &wrqu, शून्य);
पूर्ण
EXPORT_SYMBOL(notअगरy_wx_assoc_event);
