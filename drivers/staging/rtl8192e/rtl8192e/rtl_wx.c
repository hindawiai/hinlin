<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश <linux/माला.स>
#समावेश "rtl_core.h"
#समावेश "rtl_wx.h"

#घोषणा RATE_COUNT 12
अटल u32 rtl8192_rates[] = अणु
	1000000, 2000000, 5500000, 11000000, 6000000, 9000000, 12000000,
	18000000, 24000000, 36000000, 48000000, 54000000
पूर्ण;

#अगर_अघोषित ENETDOWN
#घोषणा ENETDOWN 1
#पूर्ण_अगर

अटल पूर्णांक _rtl92e_wx_get_freq(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *a,
			       जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	वापस rtllib_wx_get_freq(priv->rtllib, a, wrqu, b);
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_mode(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *a,
			       जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	वापस rtllib_wx_get_mode(priv->rtllib, a, wrqu, b);
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_rate(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	वापस rtllib_wx_get_rate(priv->rtllib, info, wrqu, extra);
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_rate(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->bHwRadioOff)
		वापस 0;

	mutex_lock(&priv->wx_mutex);

	ret = rtllib_wx_set_rate(priv->rtllib, info, wrqu, extra);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_rts(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->bHwRadioOff)
		वापस 0;

	mutex_lock(&priv->wx_mutex);

	ret = rtllib_wx_set_rts(priv->rtllib, info, wrqu, extra);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_rts(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	वापस rtllib_wx_get_rts(priv->rtllib, info, wrqu, extra);
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_घातer(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->bHwRadioOff) अणु
		netdev_warn(dev, "%s(): Can't set Power: Radio is Off.\n",
			    __func__);
		वापस 0;
	पूर्ण
	mutex_lock(&priv->wx_mutex);

	ret = rtllib_wx_set_घातer(priv->rtllib, info, wrqu, extra);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_घातer(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	वापस rtllib_wx_get_घातer(priv->rtllib, info, wrqu, extra);
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_rawtx(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	पूर्णांक ret;

	अगर (priv->bHwRadioOff)
		वापस 0;

	mutex_lock(&priv->wx_mutex);

	ret = rtllib_wx_set_rawtx(priv->rtllib, info, wrqu, extra);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_क्रमce_reset(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	mutex_lock(&priv->wx_mutex);

	RT_TRACE(COMP_DBG, "%s(): force reset ! extra is %d\n",
		 __func__, *extra);
	priv->क्रमce_reset = *extra;
	mutex_unlock(&priv->wx_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_wx_adapter_घातer_status(काष्ठा net_device *dev,
					   काष्ठा iw_request_info *info,
					   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rt_pwr_save_ctrl *pPSC = (काष्ठा rt_pwr_save_ctrl *)
					(&priv->rtllib->PowerSaveControl);
	काष्ठा rtllib_device *ieee = priv->rtllib;

	mutex_lock(&priv->wx_mutex);

	RT_TRACE(COMP_POWER, "%s(): %s\n", __func__, (*extra == 6) ?
		 "DC power" : "AC power");
	अगर (*extra || priv->क्रमce_lps) अणु
		priv->ps_क्रमce = false;
		pPSC->bLeisurePs = true;
	पूर्ण अन्यथा अणु
		अगर (priv->rtllib->state == RTLLIB_LINKED)
			rtl92e_leisure_ps_leave(dev);

		priv->ps_क्रमce = true;
		pPSC->bLeisurePs = false;
		ieee->ps = *extra;
	पूर्ण

	mutex_unlock(&priv->wx_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_lps_awake_पूर्णांकerval(काष्ठा net_device *dev,
					     काष्ठा iw_request_info *info,
					     जोड़ iwreq_data *wrqu,
					     अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rt_pwr_save_ctrl *pPSC = (काष्ठा rt_pwr_save_ctrl *)
					(&priv->rtllib->PowerSaveControl);

	mutex_lock(&priv->wx_mutex);

	netdev_info(dev, "%s(): set lps awake interval ! extra is %d\n",
		    __func__, *extra);

	pPSC->RegMaxLPSAwakeIntvl = *extra;
	mutex_unlock(&priv->wx_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_क्रमce_lps(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *info,
				    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	mutex_lock(&priv->wx_mutex);

	netdev_info(dev,
		    "%s(): force LPS ! extra is %d (1 is open 0 is close)\n",
		    __func__, *extra);
	priv->क्रमce_lps = *extra;
	mutex_unlock(&priv->wx_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_debug(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8 c = *extra;

	अगर (priv->bHwRadioOff)
		वापस 0;

	netdev_info(dev, "=====>%s(), *extra:%x, debugflag:%x\n", __func__,
		    *extra, rt_global_debug_component);
	अगर (c > 0)
		rt_global_debug_component |= (1 << c);
	अन्यथा
		rt_global_debug_component &= BIT31;
	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_mode(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *a,
			       जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = netdev_priv_rsl(dev);

	क्रमागत rt_rf_घातer_state rtState;
	पूर्णांक ret;

	अगर (priv->bHwRadioOff)
		वापस 0;
	rtState = priv->rtllib->eRFPowerState;
	mutex_lock(&priv->wx_mutex);
	अगर (wrqu->mode == IW_MODE_ADHOC || wrqu->mode == IW_MODE_MONITOR ||
	    ieee->bNetPromiscuousMode) अणु
		अगर (priv->rtllib->PowerSaveControl.bInactivePs) अणु
			अगर (rtState == eRfOff) अणु
				अगर (priv->rtllib->RfOffReason >
				    RF_CHANGE_BY_IPS) अणु
					netdev_warn(dev, "%s(): RF is OFF.\n",
						    __func__);
					mutex_unlock(&priv->wx_mutex);
					वापस -1;
				पूर्ण
				netdev_info(dev,
					    "=========>%s(): rtl92e_ips_leave\n",
					    __func__);
				mutex_lock(&priv->rtllib->ips_mutex);
				rtl92e_ips_leave(dev);
				mutex_unlock(&priv->rtllib->ips_mutex);
			पूर्ण
		पूर्ण
	पूर्ण
	ret = rtllib_wx_set_mode(priv->rtllib, a, wrqu, b);

	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

काष्ठा  iw_range_with_scan_capa अणु
	/* Inक्रमmative stuff (to choose between dअगरferent पूर्णांकerface) */
	__u32	   throughput;     /* To give an idea... */
	/* In theory this value should be the maximum benchmarked
	 * TCP/IP throughput, because with most of these devices the
	 * bit rate is meaningless (overhead an co) to estimate how
	 * fast the connection will go and pick the fastest one.
	 * I suggest people to play with Netperf or any benchmark...
	 */

	/* NWID (or करोमुख्य id) */
	__u32	   min_nwid;	/* Minimal NWID we are able to set */
	__u32	   max_nwid;	/* Maximal NWID we are able to set */

	/* Old Frequency (backward compat - moved lower ) */
	__u16	   old_num_channels;
	__u8	    old_num_frequency;

	/* Scan capabilities */
	__u8	    scan_capa;
पूर्ण;

अटल पूर्णांक _rtl92e_wx_get_range(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा iw_range *range = (काष्ठा iw_range *)extra;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u16 val;
	पूर्णांक i;

	wrqu->data.length = माप(*range);
	स_रखो(range, 0, माप(*range));

	/* ~130 Mb/s real (802.11n) */
	range->throughput = 130 * 1000 * 1000;

	अगर (priv->rf_set_sens != शून्य)
		/* संकेत level threshold range */
		range->sensitivity = priv->max_sens;

	range->max_qual.qual = 100;
	range->max_qual.level = 0;
	range->max_qual.noise = 0;
	range->max_qual.updated = 7; /* Updated all three */

	range->avg_qual.qual = 70; /* > 8% missed beacons is 'bad' */
	range->avg_qual.level = 0;
	range->avg_qual.noise = 0;
	range->avg_qual.updated = 7; /* Updated all three */

	range->num_bitrates = min(RATE_COUNT, IW_MAX_BITRATES);

	क्रम (i = 0; i < range->num_bitrates; i++)
		range->bitrate[i] = rtl8192_rates[i];

	range->max_rts = DEFAULT_RTS_THRESHOLD;
	range->min_frag = MIN_FRAG_THRESHOLD;
	range->max_frag = MAX_FRAG_THRESHOLD;

	range->min_pmp = 0;
	range->max_pmp = 5000000;
	range->min_pmt = 0;
	range->max_pmt = 65535 * 1000;
	range->pmp_flags = IW_POWER_PERIOD;
	range->pmt_flags = IW_POWER_TIMEOUT;
	range->pm_capa = IW_POWER_PERIOD | IW_POWER_TIMEOUT | IW_POWER_ALL_R;
	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 18;

	क्रम (i = 0, val = 0; i < 14; i++) अणु
		अगर ((priv->rtllib->active_channel_map)[i + 1]) अणु
			range->freq[val].i = i + 1;
			range->freq[val].m = rtllib_wlan_frequencies[i] *
					     100000;
			range->freq[val].e = 1;
			val++;
		पूर्ण

		अगर (val == IW_MAX_FREQUENCIES)
			अवरोध;
	पूर्ण
	range->num_frequency = val;
	range->num_channels = val;
	range->enc_capa = IW_ENC_CAPA_WPA | IW_ENC_CAPA_WPA2 |
			  IW_ENC_CAPA_CIPHER_TKIP | IW_ENC_CAPA_CIPHER_CCMP;
	range->scan_capa = IW_SCAN_CAPA_ESSID | IW_SCAN_CAPA_TYPE;

	/* Event capability (kernel + driver) */

	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_scan(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *a,
			       जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;
	क्रमागत rt_rf_घातer_state rtState;
	पूर्णांक ret;

	अगर (!(ieee->sofपंचांगac_features & IEEE_SOFTMAC_SCAN)) अणु
		अगर ((ieee->state >= RTLLIB_ASSOCIATING) &&
		    (ieee->state <= RTLLIB_ASSOCIATING_AUTHENTICATED))
			वापस 0;
		अगर ((priv->rtllib->state == RTLLIB_LINKED) &&
		    (priv->rtllib->CntAfterLink < 2))
			वापस 0;
	पूर्ण

	अगर (priv->bHwRadioOff) अणु
		netdev_info(dev, "================>%s(): hwradio off\n",
			    __func__);
		वापस 0;
	पूर्ण
	rtState = priv->rtllib->eRFPowerState;
	अगर (!priv->up)
		वापस -ENETDOWN;
	अगर (priv->rtllib->LinkDetectInfo.bBusyTraffic == true)
		वापस -EAGAIN;

	अगर (wrqu->data.flags & IW_SCAN_THIS_ESSID) अणु
		काष्ठा iw_scan_req *req = (काष्ठा iw_scan_req *)b;

		अगर (req->essid_len) अणु
			पूर्णांक len = min_t(पूर्णांक, req->essid_len, IW_ESSID_MAX_SIZE);

			ieee->current_network.ssid_len = len;
			स_नकल(ieee->current_network.ssid, req->essid, len);
		पूर्ण
	पूर्ण

	mutex_lock(&priv->wx_mutex);

	priv->rtllib->FirstIe_InScan = true;

	अगर (priv->rtllib->state != RTLLIB_LINKED) अणु
		अगर (priv->rtllib->PowerSaveControl.bInactivePs) अणु
			अगर (rtState == eRfOff) अणु
				अगर (priv->rtllib->RfOffReason >
				    RF_CHANGE_BY_IPS) अणु
					netdev_warn(dev, "%s(): RF is OFF.\n",
						    __func__);
					mutex_unlock(&priv->wx_mutex);
					वापस -1;
				पूर्ण
				RT_TRACE(COMP_PS,
					 "=========>%s(): rtl92e_ips_leave\n",
					 __func__);
				mutex_lock(&priv->rtllib->ips_mutex);
				rtl92e_ips_leave(dev);
				mutex_unlock(&priv->rtllib->ips_mutex);
			पूर्ण
		पूर्ण
		rtllib_stop_scan(priv->rtllib);
		अगर (priv->rtllib->LedControlHandler)
			priv->rtllib->LedControlHandler(dev,
							 LED_CTL_SITE_SURVEY);

		अगर (priv->rtllib->eRFPowerState != eRfOff) अणु
			priv->rtllib->actscanning = true;

			अगर (ieee->ScanOperationBackupHandler)
				ieee->ScanOperationBackupHandler(ieee->dev,
							 SCAN_OPT_BACKUP);

			rtllib_start_scan_syncro(priv->rtllib, 0);

			अगर (ieee->ScanOperationBackupHandler)
				ieee->ScanOperationBackupHandler(ieee->dev,
							 SCAN_OPT_RESTORE);
		पूर्ण
		ret = 0;
	पूर्ण अन्यथा अणु
		priv->rtllib->actscanning = true;
		ret = rtllib_wx_set_scan(priv->rtllib, a, wrqu, b);
	पूर्ण

	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_scan(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *a,
			       जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	पूर्णांक ret;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (!priv->up)
		वापस -ENETDOWN;

	अगर (priv->bHwRadioOff)
		वापस 0;

	mutex_lock(&priv->wx_mutex);

	ret = rtllib_wx_get_scan(priv->rtllib, a, wrqu, b);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_essid(काष्ठा net_device *dev,
				काष्ठा iw_request_info *a,
				जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	पूर्णांक ret;

	अगर (priv->bHwRadioOff) अणु
		netdev_info(dev,
			    "=========>%s():hw radio off,or Rf state is eRfOff, return\n",
			    __func__);
		वापस 0;
	पूर्ण
	mutex_lock(&priv->wx_mutex);
	ret = rtllib_wx_set_essid(priv->rtllib, a, wrqu, b);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_essid(काष्ठा net_device *dev,
				काष्ठा iw_request_info *a,
				जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	पूर्णांक ret;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	mutex_lock(&priv->wx_mutex);

	ret = rtllib_wx_get_essid(priv->rtllib, a, wrqu, b);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_nick(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (wrqu->data.length > IW_ESSID_MAX_SIZE)
		वापस -E2BIG;
	mutex_lock(&priv->wx_mutex);
	wrqu->data.length = min_t(माप_प्रकार, wrqu->data.length,
				  माप(priv->nick));
	स_रखो(priv->nick, 0, माप(priv->nick));
	स_नकल(priv->nick, extra, wrqu->data.length);
	mutex_unlock(&priv->wx_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_nick(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	mutex_lock(&priv->wx_mutex);
	wrqu->data.length = म_माप(priv->nick);
	स_नकल(extra, priv->nick, wrqu->data.length);
	wrqu->data.flags = 1;   /* active */
	mutex_unlock(&priv->wx_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_freq(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *a,
			       जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	पूर्णांक ret;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->bHwRadioOff)
		वापस 0;

	mutex_lock(&priv->wx_mutex);

	ret = rtllib_wx_set_freq(priv->rtllib, a, wrqu, b);

	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_name(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	वापस rtllib_wx_get_name(priv->rtllib, info, wrqu, extra);
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_frag(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->bHwRadioOff)
		वापस 0;

	अगर (wrqu->frag.disabled)
		priv->rtllib->fts = DEFAULT_FRAG_THRESHOLD;
	अन्यथा अणु
		अगर (wrqu->frag.value < MIN_FRAG_THRESHOLD ||
		    wrqu->frag.value > MAX_FRAG_THRESHOLD)
			वापस -EINVAL;

		priv->rtllib->fts = wrqu->frag.value & ~0x1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_frag(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	wrqu->frag.value = priv->rtllib->fts;
	wrqu->frag.fixed = 0;	/* no स्वतः select */
	wrqu->frag.disabled = (wrqu->frag.value == DEFAULT_FRAG_THRESHOLD);

	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_wap(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *awrq, अक्षर *extra)
अणु
	पूर्णांक ret;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->bHwRadioOff)
		वापस 0;

	mutex_lock(&priv->wx_mutex);

	ret = rtllib_wx_set_wap(priv->rtllib, info, awrq, extra);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_wap(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	वापस rtllib_wx_get_wap(priv->rtllib, info, wrqu, extra);
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_enc(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *key)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	वापस rtllib_wx_get_encode(priv->rtllib, info, wrqu, key);
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_enc(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *key)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	पूर्णांक ret;

	काष्ठा rtllib_device *ieee = priv->rtllib;
	u32 hwkey[4] = अणु0, 0, 0, 0पूर्ण;
	u8 mask = 0xff;
	u32 key_idx = 0;
	u8 zero_addr[4][6] = अणुअणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण,
			     अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x01पूर्ण,
			     अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x02पूर्ण,
			     अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x03पूर्ण पूर्ण;
	पूर्णांक i;

	अगर (priv->bHwRadioOff)
		वापस 0;

	अगर (!priv->up)
		वापस -ENETDOWN;

	priv->rtllib->wx_set_enc = 1;
	mutex_lock(&priv->rtllib->ips_mutex);
	rtl92e_ips_leave(dev);
	mutex_unlock(&priv->rtllib->ips_mutex);
	mutex_lock(&priv->wx_mutex);

	RT_TRACE(COMP_SEC, "Setting SW wep key");
	ret = rtllib_wx_set_encode(priv->rtllib, info, wrqu, key);
	mutex_unlock(&priv->wx_mutex);

	अगर (wrqu->encoding.flags & IW_ENCODE_DISABLED) अणु
		ieee->pairwise_key_type = ieee->group_key_type = KEY_TYPE_NA;
		rtl92e_cam_reset(dev);
		स_रखो(priv->rtllib->swcamtable, 0,
		       माप(काष्ठा sw_cam_table) * 32);
		जाओ end_hw_sec;
	पूर्ण
	अगर (wrqu->encoding.length != 0) अणु
		क्रम (i = 0; i < 4; i++) अणु
			hwkey[i] |=  key[4 * i + 0] & mask;
			अगर (i == 1 && (4 * i + 1) == wrqu->encoding.length)
				mask = 0x00;
			अगर (i == 3 && (4 * i + 1) == wrqu->encoding.length)
				mask = 0x00;
			hwkey[i] |= (key[4 * i + 1] & mask) << 8;
			hwkey[i] |= (key[4 * i + 2] & mask) << 16;
			hwkey[i] |= (key[4 * i + 3] & mask) << 24;
		पूर्ण

		चयन (wrqu->encoding.flags & IW_ENCODE_INDEX) अणु
		हाल 0:
			key_idx = ieee->crypt_info.tx_keyidx;
			अवरोध;
		हाल 1:
			key_idx = 0;
			अवरोध;
		हाल 2:
			key_idx = 1;
			अवरोध;
		हाल 3:
			key_idx = 2;
			अवरोध;
		हाल 4:
			key_idx	= 3;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (wrqu->encoding.length == 0x5) अणु
			ieee->pairwise_key_type = KEY_TYPE_WEP40;
			rtl92e_enable_hw_security_config(dev);
		पूर्ण

		अन्यथा अगर (wrqu->encoding.length == 0xd) अणु
			ieee->pairwise_key_type = KEY_TYPE_WEP104;
			rtl92e_enable_hw_security_config(dev);
			rtl92e_set_key(dev, key_idx, key_idx, KEY_TYPE_WEP104,
				       zero_addr[key_idx], 0, hwkey);
			rtl92e_set_swcam(dev, key_idx, key_idx, KEY_TYPE_WEP104,
					 zero_addr[key_idx], 0, hwkey, 0);
		पूर्ण अन्यथा अणु
			netdev_info(dev,
				    "wrong type in WEP, not WEP40 and WEP104\n");
		पूर्ण
	पूर्ण

end_hw_sec:
	priv->rtllib->wx_set_enc = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_scan_type(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *aa,
				    जोड़ iwreq_data *wrqu, अक्षर *p)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	पूर्णांक *parms = (पूर्णांक *)p;
	पूर्णांक mode = parms[0];

	अगर (priv->bHwRadioOff)
		वापस 0;

	priv->rtllib->active_scan = mode;

	वापस 1;
पूर्ण

#घोषणा R8192_MAX_RETRY 255
अटल पूर्णांक _rtl92e_wx_set_retry(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	पूर्णांक err = 0;

	अगर (priv->bHwRadioOff)
		वापस 0;

	mutex_lock(&priv->wx_mutex);

	अगर (wrqu->retry.flags & IW_RETRY_LIFETIME ||
	    wrqu->retry.disabled) अणु
		err = -EINVAL;
		जाओ निकास;
	पूर्ण
	अगर (!(wrqu->retry.flags & IW_RETRY_LIMIT)) अणु
		err = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (wrqu->retry.value > R8192_MAX_RETRY) अणु
		err = -EINVAL;
		जाओ निकास;
	पूर्ण
	अगर (wrqu->retry.flags & IW_RETRY_MAX)
		priv->retry_rts = wrqu->retry.value;
	अन्यथा
		priv->retry_data = wrqu->retry.value;

	rtl92e_commit(dev);
निकास:
	mutex_unlock(&priv->wx_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_retry(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	wrqu->retry.disabled = 0; /* can't be disabled */

	अगर ((wrqu->retry.flags & IW_RETRY_TYPE) ==
	    IW_RETRY_LIFETIME)
		वापस -EINVAL;

	अगर (wrqu->retry.flags & IW_RETRY_MAX) अणु
		wrqu->retry.flags = IW_RETRY_LIMIT | IW_RETRY_MAX;
		wrqu->retry.value = priv->retry_rts;
	पूर्ण अन्यथा अणु
		wrqu->retry.flags = IW_RETRY_LIMIT | IW_RETRY_MIN;
		wrqu->retry.value = priv->retry_data;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_sens(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->rf_set_sens == शून्य)
		वापस -1; /* we have not this support क्रम this radio */
	wrqu->sens.value = priv->sens;
	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_sens(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	लघु err = 0;

	अगर (priv->bHwRadioOff)
		वापस 0;

	mutex_lock(&priv->wx_mutex);
	अगर (priv->rf_set_sens == शून्य) अणु
		err = -1; /* we have not this support क्रम this radio */
		जाओ निकास;
	पूर्ण
	अगर (priv->rf_set_sens(dev, wrqu->sens.value) == 0)
		priv->sens = wrqu->sens.value;
	अन्यथा
		err = -EINVAL;

निकास:
	mutex_unlock(&priv->wx_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_encode_ext(काष्ठा net_device *dev,
				     काष्ठा iw_request_info *info,
				     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;

	अगर (priv->bHwRadioOff)
		वापस 0;

	mutex_lock(&priv->wx_mutex);

	priv->rtllib->wx_set_enc = 1;
	mutex_lock(&priv->rtllib->ips_mutex);
	rtl92e_ips_leave(dev);
	mutex_unlock(&priv->rtllib->ips_mutex);

	ret = rtllib_wx_set_encode_ext(ieee, info, wrqu, extra);
	अणु
		स्थिर u8 broadcast_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
		स्थिर u8 zero[ETH_ALEN] = अणु0पूर्ण;
		u32 key[4] = अणु0पूर्ण;
		काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
		काष्ठा iw_poपूर्णांक *encoding = &wrqu->encoding;
		u8 idx = 0, alg = 0, group = 0;

		अगर ((encoding->flags & IW_ENCODE_DISABLED) ||
		     ext->alg == IW_ENCODE_ALG_NONE) अणु
			ieee->pairwise_key_type = ieee->group_key_type
						= KEY_TYPE_NA;
			rtl92e_cam_reset(dev);
			स_रखो(priv->rtllib->swcamtable, 0,
			       माप(काष्ठा sw_cam_table) * 32);
			जाओ end_hw_sec;
		पूर्ण
		alg = (ext->alg == IW_ENCODE_ALG_CCMP) ? KEY_TYPE_CCMP :
		      ext->alg;
		idx = encoding->flags & IW_ENCODE_INDEX;
		अगर (idx)
			idx--;
		group = ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY;

		अगर ((!group) || (ieee->iw_mode == IW_MODE_ADHOC) ||
		    (alg ==  KEY_TYPE_WEP40)) अणु
			अगर ((ext->key_len == 13) && (alg == KEY_TYPE_WEP40))
				alg = KEY_TYPE_WEP104;
			ieee->pairwise_key_type = alg;
			rtl92e_enable_hw_security_config(dev);
		पूर्ण
		स_नकल((u8 *)key, ext->key, 16);

		अगर ((alg & KEY_TYPE_WEP40) && (ieee->auth_mode != 2)) अणु
			अगर (ext->key_len == 13)
				ieee->pairwise_key_type = alg = KEY_TYPE_WEP104;
			rtl92e_set_key(dev, idx, idx, alg, zero, 0, key);
			rtl92e_set_swcam(dev, idx, idx, alg, zero, 0, key, 0);
		पूर्ण अन्यथा अगर (group) अणु
			ieee->group_key_type = alg;
			rtl92e_set_key(dev, idx, idx, alg, broadcast_addr, 0,
				       key);
			rtl92e_set_swcam(dev, idx, idx, alg, broadcast_addr, 0,
					 key, 0);
		पूर्ण अन्यथा अणु
			अगर ((ieee->pairwise_key_type == KEY_TYPE_CCMP) &&
			     ieee->pHTInfo->bCurrentHTSupport)
				rtl92e_ग_लिखोb(dev, 0x173, 1);
			rtl92e_set_key(dev, 4, idx, alg,
				       (u8 *)ieee->ap_mac_addr, 0, key);
			rtl92e_set_swcam(dev, 4, idx, alg,
					 (u8 *)ieee->ap_mac_addr, 0, key, 0);
		पूर्ण
	पूर्ण

end_hw_sec:
	priv->rtllib->wx_set_enc = 0;
	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_auth(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *data, अक्षर *extra)
अणु
	पूर्णांक ret = 0;

	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->bHwRadioOff)
		वापस 0;

	mutex_lock(&priv->wx_mutex);
	ret = rtllib_wx_set_auth(priv->rtllib, info, &data->param, extra);
	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_mlme(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret = 0;

	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->bHwRadioOff)
		वापस 0;

	mutex_lock(&priv->wx_mutex);
	ret = rtllib_wx_set_mlme(priv->rtllib, info, wrqu, extra);
	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_set_gen_ie(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 जोड़ iwreq_data *data, अक्षर *extra)
अणु
	पूर्णांक ret = 0;

	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->bHwRadioOff)
		वापस 0;

	mutex_lock(&priv->wx_mutex);
	ret = rtllib_wx_set_gen_ie(priv->rtllib, extra, data->data.length);
	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_gen_ie(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 जोड़ iwreq_data *data, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;

	अगर (ieee->wpa_ie_len == 0 || ieee->wpa_ie == शून्य) अणु
		data->data.length = 0;
		वापस 0;
	पूर्ण

	अगर (data->data.length < ieee->wpa_ie_len)
		वापस -E2BIG;

	data->data.length = ieee->wpa_ie_len;
	स_नकल(extra, ieee->wpa_ie, ieee->wpa_ie_len);
	वापस ret;
पूर्ण

#घोषणा OID_RT_INTEL_PROMISCUOUS_MODE	0xFF0101F6

अटल पूर्णांक _rtl92e_wx_set_promisc_mode(काष्ठा net_device *dev,
				       काष्ठा iw_request_info *info,
				       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;

	u32 info_buf[3];

	u32 oid;
	u32 bPromiscuousOn;
	u32 bFilterSourceStationFrame;

	अगर (copy_from_user(info_buf, wrqu->data.poपूर्णांकer, माप(info_buf)))
		वापस -EFAULT;

	oid = info_buf[0];
	bPromiscuousOn = info_buf[1];
	bFilterSourceStationFrame = info_buf[2];

	अगर (oid == OID_RT_INTEL_PROMISCUOUS_MODE) अणु
		ieee->IntelPromiscuousModeInfo.bPromiscuousOn =
					(bPromiscuousOn) ? (true) : (false);
		ieee->IntelPromiscuousModeInfo.bFilterSourceStationFrame =
			(bFilterSourceStationFrame) ? (true) : (false);
		(bPromiscuousOn) ?
		(rtllib_EnableIntelPromiscuousMode(dev, false)) :
		(rtllib_DisableIntelPromiscuousMode(dev, false));

		netdev_info(dev,
			    "=======>%s(), on = %d, filter src sta = %d\n",
			    __func__, bPromiscuousOn,
			    bFilterSourceStationFrame);
	पूर्ण अन्यथा अणु
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _rtl92e_wx_get_promisc_mode(काष्ठा net_device *dev,
				       काष्ठा iw_request_info *info,
				       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;

	mutex_lock(&priv->wx_mutex);

	snम_लिखो(extra, 45, "PromiscuousMode:%d, FilterSrcSTAFrame:%d",
		 ieee->IntelPromiscuousModeInfo.bPromiscuousOn,
		 ieee->IntelPromiscuousModeInfo.bFilterSourceStationFrame);
	wrqu->data.length = म_माप(extra) + 1;

	mutex_unlock(&priv->wx_mutex);

	वापस 0;
पूर्ण

#घोषणा IW_IOCTL(x) ((x) - SIOCSIWCOMMIT)
अटल iw_handler r8192_wx_handlers[] = अणु
	[IW_IOCTL(SIOCGIWNAME)] = _rtl92e_wx_get_name,
	[IW_IOCTL(SIOCSIWFREQ)] = _rtl92e_wx_set_freq,
	[IW_IOCTL(SIOCGIWFREQ)] = _rtl92e_wx_get_freq,
	[IW_IOCTL(SIOCSIWMODE)] = _rtl92e_wx_set_mode,
	[IW_IOCTL(SIOCGIWMODE)] = _rtl92e_wx_get_mode,
	[IW_IOCTL(SIOCSIWSENS)] = _rtl92e_wx_set_sens,
	[IW_IOCTL(SIOCGIWSENS)] = _rtl92e_wx_get_sens,
	[IW_IOCTL(SIOCGIWRANGE)] = _rtl92e_wx_get_range,
	[IW_IOCTL(SIOCSIWAP)] = _rtl92e_wx_set_wap,
	[IW_IOCTL(SIOCGIWAP)] = _rtl92e_wx_get_wap,
	[IW_IOCTL(SIOCSIWSCAN)] = _rtl92e_wx_set_scan,
	[IW_IOCTL(SIOCGIWSCAN)] = _rtl92e_wx_get_scan,
	[IW_IOCTL(SIOCSIWESSID)] = _rtl92e_wx_set_essid,
	[IW_IOCTL(SIOCGIWESSID)] = _rtl92e_wx_get_essid,
	[IW_IOCTL(SIOCSIWNICKN)] = _rtl92e_wx_set_nick,
	[IW_IOCTL(SIOCGIWNICKN)] = _rtl92e_wx_get_nick,
	[IW_IOCTL(SIOCSIWRATE)] = _rtl92e_wx_set_rate,
	[IW_IOCTL(SIOCGIWRATE)] = _rtl92e_wx_get_rate,
	[IW_IOCTL(SIOCSIWRTS)] = _rtl92e_wx_set_rts,
	[IW_IOCTL(SIOCGIWRTS)] = _rtl92e_wx_get_rts,
	[IW_IOCTL(SIOCSIWFRAG)] = _rtl92e_wx_set_frag,
	[IW_IOCTL(SIOCGIWFRAG)] = _rtl92e_wx_get_frag,
	[IW_IOCTL(SIOCSIWRETRY)] = _rtl92e_wx_set_retry,
	[IW_IOCTL(SIOCGIWRETRY)] = _rtl92e_wx_get_retry,
	[IW_IOCTL(SIOCSIWENCODE)] = _rtl92e_wx_set_enc,
	[IW_IOCTL(SIOCGIWENCODE)] = _rtl92e_wx_get_enc,
	[IW_IOCTL(SIOCSIWPOWER)] = _rtl92e_wx_set_घातer,
	[IW_IOCTL(SIOCGIWPOWER)] = _rtl92e_wx_get_घातer,
	[IW_IOCTL(SIOCSIWGENIE)] = _rtl92e_wx_set_gen_ie,
	[IW_IOCTL(SIOCGIWGENIE)] = _rtl92e_wx_get_gen_ie,
	[IW_IOCTL(SIOCSIWMLME)] = _rtl92e_wx_set_mlme,
	[IW_IOCTL(SIOCSIWAUTH)] = _rtl92e_wx_set_auth,
	[IW_IOCTL(SIOCSIWENCODEEXT)] = _rtl92e_wx_set_encode_ext,
पूर्ण;

/* the following rule need to be following,
 * Odd : get (world access),
 * even : set (root access)
 */
अटल स्थिर काष्ठा iw_priv_args r8192_निजी_args[] = अणु
	अणु
		SIOCIWFIRSTPRIV + 0x0,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "set_debugflag"
	पूर्ण, अणु
		SIOCIWFIRSTPRIV + 0x1,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "activescan"
	पूर्ण, अणु
		SIOCIWFIRSTPRIV + 0x2,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "rawtx"
	पूर्ण, अणु
		SIOCIWFIRSTPRIV + 0x3,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "forcereset"
	पूर्ण, अणु
		SIOCIWFIRSTPRIV + 0x6,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, IW_PRIV_TYPE_NONE,
		"set_power"
	पूर्ण, अणु
		SIOCIWFIRSTPRIV + 0xa,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, IW_PRIV_TYPE_NONE,
		"lps_interv"
	पूर्ण, अणु
		SIOCIWFIRSTPRIV + 0xb,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, IW_PRIV_TYPE_NONE,
		"lps_force"
	पूर्ण, अणु
		SIOCIWFIRSTPRIV + 0x16,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 3, 0, "setpromisc"
	पूर्ण, अणु
		SIOCIWFIRSTPRIV + 0x17,
		0, IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | 45, "getpromisc"
	पूर्ण

पूर्ण;

अटल iw_handler r8192_निजी_handler[] = अणु
	(iw_handler)_rtl92e_wx_set_debug,   /*SIOCIWSECONDPRIV*/
	(iw_handler)_rtl92e_wx_set_scan_type,
	(iw_handler)_rtl92e_wx_set_rawtx,
	(iw_handler)_rtl92e_wx_क्रमce_reset,
	(iw_handler)शून्य,
	(iw_handler)शून्य,
	(iw_handler)_rtl92e_wx_adapter_घातer_status,
	(iw_handler)शून्य,
	(iw_handler)शून्य,
	(iw_handler)शून्य,
	(iw_handler)_rtl92e_wx_set_lps_awake_पूर्णांकerval,
	(iw_handler)_rtl92e_wx_set_क्रमce_lps,
	(iw_handler)शून्य,
	(iw_handler)शून्य,
	(iw_handler)शून्य,
	(iw_handler)शून्य,
	(iw_handler)शून्य,
	(iw_handler)शून्य,
	(iw_handler)शून्य,
	(iw_handler)शून्य,
	(iw_handler)शून्य,
	(iw_handler)शून्य,
	(iw_handler)_rtl92e_wx_set_promisc_mode,
	(iw_handler)_rtl92e_wx_get_promisc_mode,
पूर्ण;

अटल काष्ठा iw_statistics *_rtl92e_get_wireless_stats(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;
	काष्ठा iw_statistics *wstats = &priv->wstats;
	पूर्णांक पंचांगp_level = 0;
	पूर्णांक पंचांगp_qual = 0;
	पूर्णांक पंचांगp_noise = 0;

	अगर (ieee->state < RTLLIB_LINKED) अणु
		wstats->qual.qual = 10;
		wstats->qual.level = 0;
		wstats->qual.noise = 0x100 - 100;	/* -100 dBm */
		wstats->qual.updated = IW_QUAL_ALL_UPDATED | IW_QUAL_DBM;
		वापस wstats;
	पूर्ण

	पंचांगp_level = (&ieee->current_network)->stats.rssi;
	पंचांगp_qual = (&ieee->current_network)->stats.संकेत;
	पंचांगp_noise = (&ieee->current_network)->stats.noise;

	wstats->qual.level = पंचांगp_level;
	wstats->qual.qual = पंचांगp_qual;
	wstats->qual.noise = पंचांगp_noise;
	wstats->qual.updated = IW_QUAL_ALL_UPDATED | IW_QUAL_DBM;
	वापस wstats;
पूर्ण

स्थिर काष्ठा iw_handler_def r8192_wx_handlers_def = अणु
	.standard = r8192_wx_handlers,
	.num_standard = ARRAY_SIZE(r8192_wx_handlers),
	.निजी = r8192_निजी_handler,
	.num_निजी = ARRAY_SIZE(r8192_निजी_handler),
	.num_निजी_args = माप(r8192_निजी_args) /
			    माप(काष्ठा iw_priv_args),
	.get_wireless_stats = _rtl92e_get_wireless_stats,
	.निजी_args = (काष्ठा iw_priv_args *)r8192_निजी_args,
पूर्ण;
