<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* IEEE 802.11 SoftMAC layer
 * Copyright (c) 2005 Andrea Merello <andrea.merello@gmail.com>
 *
 * Mostly extracted from the rtl8180-sa2400 driver क्रम the
 * in-kernel generic ieee802.11 stack.
 *
 * Some pieces of code might be stolen from ipw2100 driver
 * copyright of who own it's copyright ;-)
 *
 * PS wx handler mostly stolen from hostap, copyright who
 * own it's copyright ;-)
 */
#समावेश <linux/etherdevice.h>

#समावेश "rtllib.h"
#समावेश "dot11d.h"
/* FIXME: add A freqs */

स्थिर दीर्घ rtllib_wlan_frequencies[] = अणु
	2412, 2417, 2422, 2427,
	2432, 2437, 2442, 2447,
	2452, 2457, 2462, 2467,
	2472, 2484
पूर्ण;
EXPORT_SYMBOL(rtllib_wlan_frequencies);


पूर्णांक rtllib_wx_set_freq(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	पूर्णांक ret;
	काष्ठा iw_freq *fwrq = &wrqu->freq;

	mutex_lock(&ieee->wx_mutex);

	अगर (ieee->iw_mode == IW_MODE_INFRA) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	/* अगर setting by freq convert to channel */
	अगर (fwrq->e == 1) अणु
		अगर ((fwrq->m >= (पूर्णांक) 2.412e8 &&
		     fwrq->m <= (पूर्णांक) 2.487e8)) अणु
			पूर्णांक f = fwrq->m / 100000;
			पूर्णांक c = 0;

			जबतक ((c < 14) && (f != rtllib_wlan_frequencies[c]))
				c++;

			/* hack to fall through */
			fwrq->e = 0;
			fwrq->m = c + 1;
		पूर्ण
	पूर्ण

	अगर (fwrq->e > 0 || fwrq->m > 14 || fwrq->m < 1) अणु
		ret = -EOPNOTSUPP;
		जाओ out;

	पूर्ण अन्यथा अणु /* Set the channel */

		अगर (ieee->active_channel_map[fwrq->m] != 1) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		ieee->current_network.channel = fwrq->m;
		ieee->set_chan(ieee->dev, ieee->current_network.channel);

		अगर (ieee->iw_mode == IW_MODE_ADHOC ||
		    ieee->iw_mode == IW_MODE_MASTER)
			अगर (ieee->state == RTLLIB_LINKED) अणु
				rtllib_stop_send_beacons(ieee);
				rtllib_start_send_beacons(ieee);
			पूर्ण
	पूर्ण

	ret = 0;
out:
	mutex_unlock(&ieee->wx_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rtllib_wx_set_freq);


पूर्णांक rtllib_wx_get_freq(काष्ठा rtllib_device *ieee,
			     काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा iw_freq *fwrq = &wrqu->freq;

	अगर (ieee->current_network.channel == 0)
		वापस -1;
	fwrq->m = rtllib_wlan_frequencies[ieee->current_network.channel-1] *
		  100000;
	fwrq->e = 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtllib_wx_get_freq);

पूर्णांक rtllib_wx_get_wap(काष्ठा rtllib_device *ieee,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	अचिन्हित दीर्घ flags;

	wrqu->ap_addr.sa_family = ARPHRD_ETHER;

	अगर (ieee->iw_mode == IW_MODE_MONITOR)
		वापस -1;

	/* We want aव्योम to give to the user inconsistent infos*/
	spin_lock_irqsave(&ieee->lock, flags);

	अगर (ieee->state != RTLLIB_LINKED &&
		ieee->state != RTLLIB_LINKED_SCANNING &&
		ieee->wap_set == 0)

		eth_zero_addr(wrqu->ap_addr.sa_data);
	अन्यथा
		स_नकल(wrqu->ap_addr.sa_data,
		       ieee->current_network.bssid, ETH_ALEN);

	spin_unlock_irqrestore(&ieee->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtllib_wx_get_wap);


पूर्णांक rtllib_wx_set_wap(काष्ठा rtllib_device *ieee,
			 काष्ठा iw_request_info *info,
			 जोड़ iwreq_data *awrq,
			 अक्षर *extra)
अणु

	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	लघु अगरup = ieee->proto_started;
	काष्ठा sockaddr *temp = (काष्ठा sockaddr *)awrq;

	rtllib_stop_scan_syncro(ieee);

	mutex_lock(&ieee->wx_mutex);
	/* use अगरconfig hw ether */
	अगर (ieee->iw_mode == IW_MODE_MASTER) अणु
		ret = -1;
		जाओ out;
	पूर्ण

	अगर (temp->sa_family != ARPHRD_ETHER) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (is_zero_ether_addr(temp->sa_data)) अणु
		spin_lock_irqsave(&ieee->lock, flags);
		ether_addr_copy(ieee->current_network.bssid, temp->sa_data);
		ieee->wap_set = 0;
		spin_unlock_irqrestore(&ieee->lock, flags);
		ret = -1;
		जाओ out;
	पूर्ण


	अगर (अगरup)
		rtllib_stop_protocol(ieee, true);

	/* just to aव्योम to give inconsistent infos in the
	 * get wx method. not really needed otherwise
	 */
	spin_lock_irqsave(&ieee->lock, flags);

	ieee->cannot_notअगरy = false;
	ether_addr_copy(ieee->current_network.bssid, temp->sa_data);
	ieee->wap_set = !is_zero_ether_addr(temp->sa_data);

	spin_unlock_irqrestore(&ieee->lock, flags);

	अगर (अगरup)
		rtllib_start_protocol(ieee);
out:
	mutex_unlock(&ieee->wx_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rtllib_wx_set_wap);

पूर्णांक rtllib_wx_get_essid(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *a,
			 जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	पूर्णांक len, ret = 0;
	अचिन्हित दीर्घ flags;

	अगर (ieee->iw_mode == IW_MODE_MONITOR)
		वापस -1;

	/* We want aव्योम to give to the user inconsistent infos*/
	spin_lock_irqsave(&ieee->lock, flags);

	अगर (ieee->current_network.ssid[0] == '\0' ||
		ieee->current_network.ssid_len == 0) अणु
		ret = -1;
		जाओ out;
	पूर्ण

	अगर (ieee->state != RTLLIB_LINKED &&
		ieee->state != RTLLIB_LINKED_SCANNING &&
		ieee->ssid_set == 0) अणु
		ret = -1;
		जाओ out;
	पूर्ण
	len = ieee->current_network.ssid_len;
	wrqu->essid.length = len;
	म_नकलन(b, ieee->current_network.ssid, len);
	wrqu->essid.flags = 1;

out:
	spin_unlock_irqrestore(&ieee->lock, flags);

	वापस ret;

पूर्ण
EXPORT_SYMBOL(rtllib_wx_get_essid);

पूर्णांक rtllib_wx_set_rate(काष्ठा rtllib_device *ieee,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु

	u32 target_rate = wrqu->bitrate.value;

	ieee->rate = target_rate/100000;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtllib_wx_set_rate);

पूर्णांक rtllib_wx_get_rate(काष्ठा rtllib_device *ieee,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	u32 पंचांगp_rate;

	पंचांगp_rate = TxCountToDataRate(ieee,
				     ieee->sofपंचांगac_stats.CurrentShowTxate);
	wrqu->bitrate.value = पंचांगp_rate * 500000;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtllib_wx_get_rate);


पूर्णांक rtllib_wx_set_rts(काष्ठा rtllib_device *ieee,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	अगर (wrqu->rts.disabled || !wrqu->rts.fixed)
		ieee->rts = DEFAULT_RTS_THRESHOLD;
	अन्यथा अणु
		अगर (wrqu->rts.value < MIN_RTS_THRESHOLD ||
				wrqu->rts.value > MAX_RTS_THRESHOLD)
			वापस -EINVAL;
		ieee->rts = wrqu->rts.value;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtllib_wx_set_rts);

पूर्णांक rtllib_wx_get_rts(काष्ठा rtllib_device *ieee,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	wrqu->rts.value = ieee->rts;
	wrqu->rts.fixed = 0;	/* no स्वतः select */
	wrqu->rts.disabled = (wrqu->rts.value == DEFAULT_RTS_THRESHOLD);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtllib_wx_get_rts);

पूर्णांक rtllib_wx_set_mode(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	पूर्णांक set_mode_status = 0;

	rtllib_stop_scan_syncro(ieee);
	mutex_lock(&ieee->wx_mutex);
	चयन (wrqu->mode) अणु
	हाल IW_MODE_MONITOR:
	हाल IW_MODE_ADHOC:
	हाल IW_MODE_INFRA:
		अवरोध;
	हाल IW_MODE_AUTO:
		wrqu->mode = IW_MODE_INFRA;
		अवरोध;
	शेष:
		set_mode_status = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (wrqu->mode == ieee->iw_mode)
		जाओ out;

	अगर (wrqu->mode == IW_MODE_MONITOR) अणु
		ieee->dev->type = ARPHRD_IEEE80211;
		rtllib_EnableNetMonitorMode(ieee->dev, false);
	पूर्ण अन्यथा अणु
		ieee->dev->type = ARPHRD_ETHER;
		अगर (ieee->iw_mode == IW_MODE_MONITOR)
			rtllib_DisableNetMonitorMode(ieee->dev, false);
	पूर्ण

	अगर (!ieee->proto_started) अणु
		ieee->iw_mode = wrqu->mode;
	पूर्ण अन्यथा अणु
		rtllib_stop_protocol(ieee, true);
		ieee->iw_mode = wrqu->mode;
		rtllib_start_protocol(ieee);
	पूर्ण

out:
	mutex_unlock(&ieee->wx_mutex);
	वापस set_mode_status;
पूर्ण
EXPORT_SYMBOL(rtllib_wx_set_mode);

व्योम rtllib_wx_sync_scan_wq(व्योम *data)
अणु
	काष्ठा rtllib_device *ieee = container_of_work_rsl(data,
				     काष्ठा rtllib_device, wx_sync_scan_wq);
	लघु chan;
	क्रमागत ht_extchnl_offset chan_offset = 0;
	क्रमागत ht_channel_width bandwidth = 0;
	पूर्णांक b40M = 0;

	अगर (!(ieee->sofपंचांगac_features & IEEE_SOFTMAC_SCAN)) अणु
		rtllib_start_scan_syncro(ieee, 0);
		जाओ out;
	पूर्ण

	chan = ieee->current_network.channel;

	अगर (ieee->LeisurePSLeave)
		ieee->LeisurePSLeave(ieee->dev);
	/* notअगरy AP to be in PS mode */
	rtllib_sta_ps_send_null_frame(ieee, 1);
	rtllib_sta_ps_send_null_frame(ieee, 1);

	rtllib_stop_all_queues(ieee);

	अगर (ieee->data_hard_stop)
		ieee->data_hard_stop(ieee->dev);
	rtllib_stop_send_beacons(ieee);
	ieee->state = RTLLIB_LINKED_SCANNING;
	ieee->link_change(ieee->dev);
	/* रुको क्रम ps packet to be kicked out successfully */
	msleep(50);

	अगर (ieee->ScanOperationBackupHandler)
		ieee->ScanOperationBackupHandler(ieee->dev, SCAN_OPT_BACKUP);

	अगर (ieee->pHTInfo->bCurrentHTSupport && ieee->pHTInfo->bEnableHT &&
	    ieee->pHTInfo->bCurBW40MHz) अणु
		b40M = 1;
		chan_offset = ieee->pHTInfo->CurSTAExtChnlOffset;
		bandwidth = (क्रमागत ht_channel_width)ieee->pHTInfo->bCurBW40MHz;
		RT_TRACE(COMP_DBG, "Scan in 40M, force to 20M first:%d, %d\n",
			 chan_offset, bandwidth);
		ieee->SetBWModeHandler(ieee->dev, HT_CHANNEL_WIDTH_20,
				       HT_EXTCHNL_OFFSET_NO_EXT);
	पूर्ण

	rtllib_start_scan_syncro(ieee, 0);

	अगर (b40M) अणु
		RT_TRACE(COMP_DBG, "Scan in 20M, back to 40M\n");
		अगर (chan_offset == HT_EXTCHNL_OFFSET_UPPER)
			ieee->set_chan(ieee->dev, chan + 2);
		अन्यथा अगर (chan_offset == HT_EXTCHNL_OFFSET_LOWER)
			ieee->set_chan(ieee->dev, chan - 2);
		अन्यथा
			ieee->set_chan(ieee->dev, chan);
		ieee->SetBWModeHandler(ieee->dev, bandwidth, chan_offset);
	पूर्ण अन्यथा अणु
		ieee->set_chan(ieee->dev, chan);
	पूर्ण

	अगर (ieee->ScanOperationBackupHandler)
		ieee->ScanOperationBackupHandler(ieee->dev, SCAN_OPT_RESTORE);

	ieee->state = RTLLIB_LINKED;
	ieee->link_change(ieee->dev);

	/* Notअगरy AP that I wake up again */
	rtllib_sta_ps_send_null_frame(ieee, 0);

	अगर (ieee->LinkDetectInfo.NumRecvBcnInPeriod == 0 ||
	    ieee->LinkDetectInfo.NumRecvDataInPeriod == 0) अणु
		ieee->LinkDetectInfo.NumRecvBcnInPeriod = 1;
		ieee->LinkDetectInfo.NumRecvDataInPeriod = 1;
	पूर्ण

	अगर (ieee->data_hard_resume)
		ieee->data_hard_resume(ieee->dev);

	अगर (ieee->iw_mode == IW_MODE_ADHOC || ieee->iw_mode == IW_MODE_MASTER)
		rtllib_start_send_beacons(ieee);

	rtllib_wake_all_queues(ieee);

out:
	mutex_unlock(&ieee->wx_mutex);

पूर्ण

पूर्णांक rtllib_wx_set_scan(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&ieee->wx_mutex);

	अगर (ieee->iw_mode == IW_MODE_MONITOR || !(ieee->proto_started)) अणु
		ret = -1;
		जाओ out;
	पूर्ण

	अगर (ieee->state == RTLLIB_LINKED) अणु
		schedule_work(&ieee->wx_sync_scan_wq);
		/* पूर्णांकentionally क्रमget to up sem */
		वापस 0;
	पूर्ण

out:
	mutex_unlock(&ieee->wx_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rtllib_wx_set_scan);

पूर्णांक rtllib_wx_set_essid(काष्ठा rtllib_device *ieee,
			काष्ठा iw_request_info *a,
			जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु

	पूर्णांक ret = 0, len, i;
	लघु proto_started;
	अचिन्हित दीर्घ flags;

	rtllib_stop_scan_syncro(ieee);
	mutex_lock(&ieee->wx_mutex);

	proto_started = ieee->proto_started;

	len = min_t(__u16, wrqu->essid.length, IW_ESSID_MAX_SIZE);

	अगर (ieee->iw_mode == IW_MODE_MONITOR) अणु
		ret = -1;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		अगर (extra[i] < 0) अणु
			ret = -1;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (proto_started)
		rtllib_stop_protocol(ieee, true);


	/* this is just to be sure that the GET wx callback
	 * has consistent infos. not needed otherwise
	 */
	spin_lock_irqsave(&ieee->lock, flags);

	अगर (wrqu->essid.flags && wrqu->essid.length) अणु
		म_नकलन(ieee->current_network.ssid, extra, len);
		ieee->current_network.ssid_len = len;
		ieee->cannot_notअगरy = false;
		ieee->ssid_set = 1;
	पूर्ण अन्यथा अणु
		ieee->ssid_set = 0;
		ieee->current_network.ssid[0] = '\0';
		ieee->current_network.ssid_len = 0;
	पूर्ण
	spin_unlock_irqrestore(&ieee->lock, flags);

	अगर (proto_started)
		rtllib_start_protocol(ieee);
out:
	mutex_unlock(&ieee->wx_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rtllib_wx_set_essid);

पूर्णांक rtllib_wx_get_mode(काष्ठा rtllib_device *ieee, काष्ठा iw_request_info *a,
		       जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	wrqu->mode = ieee->iw_mode;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtllib_wx_get_mode);

पूर्णांक rtllib_wx_set_rawtx(काष्ठा rtllib_device *ieee,
			काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु

	पूर्णांक *parms = (पूर्णांक *)extra;
	पूर्णांक enable = (parms[0] > 0);
	लघु prev = ieee->raw_tx;

	mutex_lock(&ieee->wx_mutex);

	अगर (enable)
		ieee->raw_tx = 1;
	अन्यथा
		ieee->raw_tx = 0;

	netdev_info(ieee->dev, "raw TX is %s\n",
		    ieee->raw_tx ? "enabled" : "disabled");

	अगर (ieee->iw_mode == IW_MODE_MONITOR) अणु
		अगर (prev == 0 && ieee->raw_tx) अणु
			अगर (ieee->data_hard_resume)
				ieee->data_hard_resume(ieee->dev);

			netअगर_carrier_on(ieee->dev);
		पूर्ण

		अगर (prev && ieee->raw_tx == 1)
			netअगर_carrier_off(ieee->dev);
	पूर्ण

	mutex_unlock(&ieee->wx_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtllib_wx_set_rawtx);

पूर्णांक rtllib_wx_get_name(काष्ठा rtllib_device *ieee,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	म_नकल(wrqu->name, "802.11");

	अगर (ieee->modulation & RTLLIB_CCK_MODULATION)
		म_जोड़ो(wrqu->name, "b");
	अगर (ieee->modulation & RTLLIB_OFDM_MODULATION)
		म_जोड़ो(wrqu->name, "g");
	अगर (ieee->mode & (IEEE_N_24G | IEEE_N_5G))
		म_जोड़ो(wrqu->name, "n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtllib_wx_get_name);


/* this is mostly stolen from hostap */
पूर्णांक rtllib_wx_set_घातer(काष्ठा rtllib_device *ieee,
				 काष्ठा iw_request_info *info,
				 जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret = 0;

	अगर ((!ieee->sta_wake_up) ||
	    (!ieee->enter_sleep_state) ||
	    (!ieee->ps_is_queue_empty)) अणु
		netdev_warn(ieee->dev,
			    "%s(): PS mode is tried to be use but driver missed a callback\n",
			    __func__);
		वापस -1;
	पूर्ण

	mutex_lock(&ieee->wx_mutex);

	अगर (wrqu->घातer.disabled) अणु
		RT_TRACE(COMP_DBG, "===>%s(): power disable\n", __func__);
		ieee->ps = RTLLIB_PS_DISABLED;
		जाओ निकास;
	पूर्ण
	अगर (wrqu->घातer.flags & IW_POWER_TIMEOUT) अणु
		ieee->ps_समयout = wrqu->घातer.value / 1000;
		RT_TRACE(COMP_DBG, "===>%s():ps_timeout is %d\n", __func__,
			 ieee->ps_समयout);
	पूर्ण

	अगर (wrqu->घातer.flags & IW_POWER_PERIOD)
		ieee->ps_period = wrqu->घातer.value / 1000;

	चयन (wrqu->घातer.flags & IW_POWER_MODE) अणु
	हाल IW_POWER_UNICAST_R:
		ieee->ps = RTLLIB_PS_UNICAST;
		अवरोध;
	हाल IW_POWER_MULTICAST_R:
		ieee->ps = RTLLIB_PS_MBCAST;
		अवरोध;
	हाल IW_POWER_ALL_R:
		ieee->ps = RTLLIB_PS_UNICAST | RTLLIB_PS_MBCAST;
		अवरोध;

	हाल IW_POWER_ON:
		अवरोध;

	शेष:
		ret = -EINVAL;
		जाओ निकास;

	पूर्ण
निकास:
	mutex_unlock(&ieee->wx_mutex);
	वापस ret;

पूर्ण
EXPORT_SYMBOL(rtllib_wx_set_घातer);

/* this is stolen from hostap */
पूर्णांक rtllib_wx_get_घातer(काष्ठा rtllib_device *ieee,
				 काष्ठा iw_request_info *info,
				 जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	mutex_lock(&ieee->wx_mutex);

	अगर (ieee->ps == RTLLIB_PS_DISABLED) अणु
		wrqu->घातer.disabled = 1;
		जाओ निकास;
	पूर्ण

	wrqu->घातer.disabled = 0;

	अगर ((wrqu->घातer.flags & IW_POWER_TYPE) == IW_POWER_TIMEOUT) अणु
		wrqu->घातer.flags = IW_POWER_TIMEOUT;
		wrqu->घातer.value = ieee->ps_समयout * 1000;
	पूर्ण अन्यथा अणु
		wrqu->घातer.flags = IW_POWER_PERIOD;
		wrqu->घातer.value = ieee->ps_period * 1000;
	पूर्ण

	अगर ((ieee->ps & (RTLLIB_PS_MBCAST | RTLLIB_PS_UNICAST)) ==
	    (RTLLIB_PS_MBCAST | RTLLIB_PS_UNICAST))
		wrqu->घातer.flags |= IW_POWER_ALL_R;
	अन्यथा अगर (ieee->ps & RTLLIB_PS_MBCAST)
		wrqu->घातer.flags |= IW_POWER_MULTICAST_R;
	अन्यथा
		wrqu->घातer.flags |= IW_POWER_UNICAST_R;

निकास:
	mutex_unlock(&ieee->wx_mutex);
	वापस 0;

पूर्ण
EXPORT_SYMBOL(rtllib_wx_get_घातer);
