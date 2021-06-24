<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * This file contains wireless extension handlers.
 *
 * This is part of rtl8180 OpenSource driver.
 * Copyright (C) Andrea Merello 2004-2005  <andrea.merello@gmail.com>
 *
 * Parts of this driver are based on the GPL part
 * of the official realtek driver.
 *
 * Parts of this driver are based on the rtl8180 driver skeleton
 * from Patric Schenke & Andres Salomon.
 *
 * Parts of this driver are based on the Intel Pro Wireless 2100 GPL driver.
 *
 * We want to thank the Authors of those projects and the Ndiswrapper
 * project Authors.
 *
 *****************************************************************************/

#समावेश <linux/माला.स>
#समावेश "r8192U.h"
#समावेश "r8192U_hw.h"

#समावेश "ieee80211/dot11d.h"
#समावेश "r8192U_wx.h"

#घोषणा RATE_COUNT 12
अटल स्थिर u32 rtl8180_rates[] = अणु1000000, 2000000, 5500000, 11000000,
	6000000, 9000000, 12000000, 18000000, 24000000, 36000000, 48000000, 54000000पूर्ण;

#अगर_अघोषित ENETDOWN
#घोषणा ENETDOWN 1
#पूर्ण_अगर

अटल पूर्णांक r8192_wx_get_freq(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	वापस ieee80211_wx_get_freq(priv->ieee80211, a, wrqu, b);
पूर्ण

अटल पूर्णांक r8192_wx_get_mode(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	वापस ieee80211_wx_get_mode(priv->ieee80211, a, wrqu, b);
पूर्ण

अटल पूर्णांक r8192_wx_get_rate(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	वापस ieee80211_wx_get_rate(priv->ieee80211, info, wrqu, extra);
पूर्ण

अटल पूर्णांक r8192_wx_set_rate(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	mutex_lock(&priv->wx_mutex);

	ret = ieee80211_wx_set_rate(priv->ieee80211, info, wrqu, extra);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक r8192_wx_set_rts(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	mutex_lock(&priv->wx_mutex);

	ret = ieee80211_wx_set_rts(priv->ieee80211, info, wrqu, extra);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक r8192_wx_get_rts(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	वापस ieee80211_wx_get_rts(priv->ieee80211, info, wrqu, extra);
पूर्ण

अटल पूर्णांक r8192_wx_set_घातer(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	mutex_lock(&priv->wx_mutex);

	ret = ieee80211_wx_set_घातer(priv->ieee80211, info, wrqu, extra);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक r8192_wx_get_घातer(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	वापस ieee80211_wx_get_घातer(priv->ieee80211, info, wrqu, extra);
पूर्ण

अटल पूर्णांक r8192_wx_क्रमce_reset(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	mutex_lock(&priv->wx_mutex);

	netdev_dbg(dev, "%s(): force reset ! extra is %d\n", __func__, *extra);
	priv->क्रमce_reset = *extra;
	mutex_unlock(&priv->wx_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक r8192_wx_set_rawtx(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	पूर्णांक ret;

	mutex_lock(&priv->wx_mutex);

	ret = ieee80211_wx_set_rawtx(priv->ieee80211, info, wrqu, extra);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक r8192_wx_set_crcmon(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	पूर्णांक *parms = (पूर्णांक *)extra;
	पूर्णांक enable = (parms[0] > 0);

	mutex_lock(&priv->wx_mutex);

	अगर (enable)
		priv->crcmon = 1;
	अन्यथा
		priv->crcmon = 0;

	DMESG("bad CRC in monitor mode are %s",
	      priv->crcmon ? "accepted" : "rejected");

	mutex_unlock(&priv->wx_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक r8192_wx_set_mode(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	पूर्णांक ret;

	mutex_lock(&priv->wx_mutex);

	ret = ieee80211_wx_set_mode(priv->ieee80211, a, wrqu, b);

	rtl8192_set_rxconf(dev);

	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

काष्ठा  iw_range_with_scan_capa अणु
	/* Inक्रमmative stuff (to choose between dअगरferent पूर्णांकerface) */
	__u32           throughput;     /* To give an idea... */
	/* In theory this value should be the maximum benchmarked
	 * TCP/IP throughput, because with most of these devices the
	 * bit rate is meaningless (overhead an co) to estimate how
	 * fast the connection will go and pick the fastest one.
	 * I suggest people to play with Netperf or any benchmark...
	 */

	/* NWID (or करोमुख्य id) */
	__u32           min_nwid;       /* Minimal NWID we are able to set */
	__u32           max_nwid;       /* Maximal NWID we are able to set */

	/* Old Frequency (backward compat - moved lower ) */
	__u16           old_num_channels;
	__u8            old_num_frequency;

	/* Scan capabilities */
	__u8            scan_capa;
पूर्ण;

अटल पूर्णांक rtl8180_wx_get_range(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा iw_range *range = (काष्ठा iw_range *)extra;
	काष्ठा iw_range_with_scan_capa *पंचांगp = (काष्ठा iw_range_with_scan_capa *)range;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u16 val;
	पूर्णांक i;

	wrqu->data.length = माप(*range);
	स_रखो(range, 0, माप(*range));

	/* Let's try to keep this काष्ठा in the same order as in
	 * linux/include/wireless.h
	 */

	/* TODO: See what values we can set, and हटाओ the ones we can't
	 * set, or fill them with some शेष data.
	 */

	/* ~5 Mb/s real (802.11b) */
	range->throughput = 5 * 1000 * 1000;

	/* TODO: Not used in 802.11b? */
	/* range->min_nwid; */	/* Minimal NWID we are able to set */
	/* TODO: Not used in 802.11b? */
	/* range->max_nwid; */	/* Maximal NWID we are able to set */

	/* Old Frequency (backward compat - moved lower ) */
	/* range->old_num_channels; */
	/* range->old_num_frequency; */
	/* range->old_freq[6]; */ /* Filler to keep "version" at the same offset */
	अगर (priv->rf_set_sens)
		range->sensitivity = priv->max_sens;	/* संकेत level threshold range */

	range->max_qual.qual = 100;
	/* TODO: Find real max RSSI and stick here */
	range->max_qual.level = 0;
	range->max_qual.noise = 0x100 - 98;
	range->max_qual.updated = 7; /* Updated all three */

	range->avg_qual.qual = 92; /* > 8% missed beacons is 'bad' */
	/* TODO: Find real 'good' to 'bad' threshold value क्रम RSSI */
	range->avg_qual.level = 0x100 - 78;
	range->avg_qual.noise = 0;
	range->avg_qual.updated = 7; /* Updated all three */

	range->num_bitrates = RATE_COUNT;

	क्रम (i = 0; i < RATE_COUNT && i < IW_MAX_BITRATES; i++)
		range->bitrate[i] = rtl8180_rates[i];

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
	range->we_version_source = 16;

	/* range->retry_capa; */	/* What retry options are supported */
	/* range->retry_flags; */	/* How to decode max/min retry limit */
	/* range->r_समय_flags; */	/* How to decode max/min retry lअगरe */
	/* range->min_retry; */		/* Minimal number of retries */
	/* range->max_retry; */		/* Maximal number of retries */
	/* range->min_r_समय; */	/* Minimal retry lअगरeसमय */
	/* range->max_r_समय; */	/* Maximal retry lअगरeसमय */

	क्रम (i = 0, val = 0; i < 14; i++) अणु
		/* Include only legal frequencies क्रम some countries */
		अगर ((GET_DOT11D_INFO(priv->ieee80211)->channel_map)[i + 1]) अणु
			range->freq[val].i = i + 1;
			range->freq[val].m = ieee80211_wlan_frequencies[i] * 100000;
			range->freq[val].e = 1;
			val++;
		पूर्ण अन्यथा अणु
			/* FIXME: करो we need to set anything क्रम channels */
			/* we करोn't use ? */
		पूर्ण

		अगर (val == IW_MAX_FREQUENCIES)
			अवरोध;
	पूर्ण
	range->num_frequency = val;
	range->num_channels = val;
	range->enc_capa = IW_ENC_CAPA_WPA | IW_ENC_CAPA_WPA2 |
			  IW_ENC_CAPA_CIPHER_TKIP | IW_ENC_CAPA_CIPHER_CCMP;
	पंचांगp->scan_capa = 0x01;
	वापस 0;
पूर्ण

अटल पूर्णांक r8192_wx_set_scan(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा ieee80211_device *ieee = priv->ieee80211;
	पूर्णांक ret = 0;

	अगर (!priv->up)
		वापस -ENETDOWN;

	अगर (priv->ieee80211->LinkDetectInfo.bBusyTraffic)
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
	अगर (priv->ieee80211->state != IEEE80211_LINKED) अणु
		priv->ieee80211->scanning = 0;
		ieee80211_sofपंचांगac_scan_syncro(priv->ieee80211);
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = ieee80211_wx_set_scan(priv->ieee80211, a, wrqu, b);
	पूर्ण
	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक r8192_wx_get_scan(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	पूर्णांक ret;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (!priv->up)
		वापस -ENETDOWN;

	mutex_lock(&priv->wx_mutex);

	ret = ieee80211_wx_get_scan(priv->ieee80211, a, wrqu, b);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक r8192_wx_set_essid(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *a,
			      जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	पूर्णांक ret;

	mutex_lock(&priv->wx_mutex);

	ret = ieee80211_wx_set_essid(priv->ieee80211, a, wrqu, b);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक r8192_wx_get_essid(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *a,
			      जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	पूर्णांक ret;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	mutex_lock(&priv->wx_mutex);

	ret = ieee80211_wx_get_essid(priv->ieee80211, a, wrqu, b);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक r8192_wx_set_freq(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	पूर्णांक ret;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	mutex_lock(&priv->wx_mutex);

	ret = ieee80211_wx_set_freq(priv->ieee80211, a, wrqu, b);

	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक r8192_wx_get_name(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	वापस ieee80211_wx_get_name(priv->ieee80211, info, wrqu, extra);
पूर्ण

अटल पूर्णांक r8192_wx_set_frag(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (wrqu->frag.disabled) अणु
		priv->ieee80211->fts = DEFAULT_FRAG_THRESHOLD;
	पूर्ण अन्यथा अणु
		अगर (wrqu->frag.value < MIN_FRAG_THRESHOLD ||
		    wrqu->frag.value > MAX_FRAG_THRESHOLD)
			वापस -EINVAL;

		priv->ieee80211->fts = wrqu->frag.value & ~0x1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक r8192_wx_get_frag(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	wrqu->frag.value = priv->ieee80211->fts;
	wrqu->frag.fixed = 0;	/* no स्वतः select */
	wrqu->frag.disabled = (wrqu->frag.value == DEFAULT_FRAG_THRESHOLD);

	वापस 0;
पूर्ण

अटल पूर्णांक r8192_wx_set_wap(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *awrq,
			    अक्षर *extra)
अणु
	पूर्णांक ret;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	/* काष्ठा sockaddr *temp = (काष्ठा sockaddr *)awrq; */
	mutex_lock(&priv->wx_mutex);

	ret = ieee80211_wx_set_wap(priv->ieee80211, info, awrq, extra);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक r8192_wx_get_wap(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	वापस ieee80211_wx_get_wap(priv->ieee80211, info, wrqu, extra);
पूर्ण

अटल पूर्णांक r8192_wx_get_enc(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *key)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	वापस ieee80211_wx_get_encode(priv->ieee80211, info, wrqu, key);
पूर्ण

अटल पूर्णांक r8192_wx_set_enc(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *key)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा ieee80211_device *ieee = priv->ieee80211;
	पूर्णांक ret;
	u32 hwkey[4] = अणु0, 0, 0, 0पूर्ण;
	u8 mask = 0xff;
	u32 key_idx = 0;
	u8 zero_addr[4][6] = अणु	अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण,
				अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x01पूर्ण,
				अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x02पूर्ण,
				अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x03पूर्ण पूर्ण;
	पूर्णांक i;

	अगर (!priv->up)
		वापस -ENETDOWN;

	mutex_lock(&priv->wx_mutex);

	RT_TRACE(COMP_SEC, "Setting SW wep key");
	ret = ieee80211_wx_set_encode(priv->ieee80211, info, wrqu, key);

	mutex_unlock(&priv->wx_mutex);

	/* someबार, the length is zero जबतक we करो not type key value */
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

		#घोषणा CONF_WEP40  0x4
		#घोषणा CONF_WEP104 0x14

		चयन (wrqu->encoding.flags & IW_ENCODE_INDEX) अणु
		हाल 0:
			key_idx = ieee->tx_keyidx;
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
			EnableHWSecurityConfig8192(dev);

			setKey(dev,
			       key_idx,                /* EntryNo */
			       key_idx,                /* KeyIndex */
			       KEY_TYPE_WEP40,         /* KeyType */
			       zero_addr[key_idx],
			       0,                      /* DefaultKey */
			       hwkey);                 /* KeyContent */
		पूर्ण अन्यथा अगर (wrqu->encoding.length == 0xd) अणु
			ieee->pairwise_key_type = KEY_TYPE_WEP104;
			EnableHWSecurityConfig8192(dev);

			setKey(dev,
			       key_idx,                /* EntryNo */
			       key_idx,                /* KeyIndex */
			       KEY_TYPE_WEP104,        /* KeyType */
			       zero_addr[key_idx],
			       0,                      /* DefaultKey */
			       hwkey);                 /* KeyContent */
		पूर्ण अन्यथा अणु
			netdev_warn(dev, "wrong type in WEP, not WEP40 and WEP104\n");
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक r8192_wx_set_scan_type(काष्ठा net_device *dev, काष्ठा iw_request_info *aa,
				  जोड़ iwreq_data *wrqu, अक्षर *p)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	पूर्णांक *parms = (पूर्णांक *)p;
	पूर्णांक mode = parms[0];

	priv->ieee80211->active_scan = mode;

	वापस 1;
पूर्ण

अटल पूर्णांक r8192_wx_set_retry(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	पूर्णांक err = 0;

	mutex_lock(&priv->wx_mutex);

	अगर (wrqu->retry.flags & IW_RETRY_LIFETIME ||
	    wrqu->retry.disabled)अणु
		err = -EINVAL;
		जाओ निकास;
	पूर्ण
	अगर (!(wrqu->retry.flags & IW_RETRY_LIMIT)) अणु
		err = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (wrqu->retry.value > R8180_MAX_RETRY) अणु
		err = -EINVAL;
		जाओ निकास;
	पूर्ण
	अगर (wrqu->retry.flags & IW_RETRY_MAX) अणु
		priv->retry_rts = wrqu->retry.value;
		DMESG("Setting retry for RTS/CTS data to %d", wrqu->retry.value);

	पूर्ण अन्यथा अणु
		priv->retry_data = wrqu->retry.value;
		DMESG("Setting retry for non RTS/CTS data to %d", wrqu->retry.value);
	पूर्ण

	/* FIXME !
	 * We might try to ग_लिखो directly the TX config रेजिस्टर
	 * or to restart just the (R)TX process.
	 * I'm unsure अगर whole reset is really needed
	 */

	rtl8192_commit(dev);
निकास:
	mutex_unlock(&priv->wx_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक r8192_wx_get_retry(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

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

अटल पूर्णांक r8192_wx_get_sens(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (!priv->rf_set_sens)
		वापस -1; /* we have not this support क्रम this radio */
	wrqu->sens.value = priv->sens;
	वापस 0;
पूर्ण

अटल पूर्णांक r8192_wx_set_sens(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	लघु err = 0;

	mutex_lock(&priv->wx_mutex);
	अगर (!priv->rf_set_sens) अणु
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

/* hw security need to reorganized. */
अटल पूर्णांक r8192_wx_set_enc_ext(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा ieee80211_device *ieee = priv->ieee80211;

	mutex_lock(&priv->wx_mutex);
	ret = ieee80211_wx_set_encode_ext(priv->ieee80211, info, wrqu, extra);

	अणु
		u8 broadcast_addr[6] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
		u8 zero[6] = अणु0पूर्ण;
		u32 key[4] = अणु0पूर्ण;
		काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
		काष्ठा iw_poपूर्णांक *encoding = &wrqu->encoding;
		u8 idx = 0, alg = 0, group = 0;

		अगर ((encoding->flags & IW_ENCODE_DISABLED) || ext->alg == IW_ENCODE_ALG_NONE)
			/* none is not allowed to use hwsec WB 2008.07.01 */
			जाओ end_hw_sec;

		/* as IW_ENCODE_ALG_CCMP is defined to be 3 and KEY_TYPE_CCMP is defined to 4; */
		alg =  (ext->alg == IW_ENCODE_ALG_CCMP) ? KEY_TYPE_CCMP : ext->alg;
		idx = encoding->flags & IW_ENCODE_INDEX;
		अगर (idx)
			idx--;
		group = ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY;

		अगर ((!group) || (ieee->iw_mode == IW_MODE_ADHOC) || (alg ==  KEY_TYPE_WEP40)) अणु
			अगर ((ext->key_len == 13) && (alg == KEY_TYPE_WEP40))
				alg = KEY_TYPE_WEP104;
			ieee->pairwise_key_type = alg;
			EnableHWSecurityConfig8192(dev);
		पूर्ण
		स_नकल((u8 *)key, ext->key, 16); /* we only get 16 bytes key.why? WB 2008.7.1 */

		अगर ((alg & KEY_TYPE_WEP40) && (ieee->auth_mode != 2)) अणु
			setKey(dev,
			       idx,	/* EntryNao */
			       idx,	/* KeyIndex */
			       alg,	/* KeyType */
			       zero,	/* MacAddr */
			       0,	/* DefaultKey */
			       key);	/* KeyContent */
		पूर्ण अन्यथा अगर (group) अणु
			ieee->group_key_type = alg;
			setKey(dev,
			       idx,	/* EntryNo */
			       idx,	/* KeyIndex */
			       alg,	/* KeyType */
			       broadcast_addr,	/* MacAddr */
			       0,		/* DefaultKey */
			       key);		/* KeyContent */
		पूर्ण अन्यथा अणु	/* pairwise key */
			setKey(dev,
			       4,	/* EntryNo */
			       idx,	/* KeyIndex */
			       alg,	/* KeyType */
			       (u8 *)ieee->ap_mac_addr,/* MacAddr */
			       0,			/* DefaultKey */
			       key);			/* KeyContent */
		पूर्ण
	पूर्ण

end_hw_sec:

	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक r8192_wx_set_auth(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *data, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	mutex_lock(&priv->wx_mutex);
	ret = ieee80211_wx_set_auth(priv->ieee80211, info, &data->param, extra);
	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक r8192_wx_set_mlme(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	mutex_lock(&priv->wx_mutex);
	ret = ieee80211_wx_set_mlme(priv->ieee80211, info, wrqu, extra);

	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक r8192_wx_set_gen_ie(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *data, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	mutex_lock(&priv->wx_mutex);
	ret = ieee80211_wx_set_gen_ie(priv->ieee80211, extra, data->data.length);
	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dummy(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
		 जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	वापस -1;
पूर्ण

अटल iw_handler r8192_wx_handlers[] = अणु
	शून्य,                     /* SIOCSIWCOMMIT */
	r8192_wx_get_name,	  /* SIOCGIWNAME */
	dummy,                    /* SIOCSIWNWID */
	dummy,                    /* SIOCGIWNWID */
	r8192_wx_set_freq,        /* SIOCSIWFREQ */
	r8192_wx_get_freq,        /* SIOCGIWFREQ */
	r8192_wx_set_mode,        /* SIOCSIWMODE */
	r8192_wx_get_mode,        /* SIOCGIWMODE */
	r8192_wx_set_sens,        /* SIOCSIWSENS */
	r8192_wx_get_sens,        /* SIOCGIWSENS */
	शून्य,                     /* SIOCSIWRANGE */
	rtl8180_wx_get_range,	  /* SIOCGIWRANGE */
	शून्य,                     /* SIOCSIWPRIV */
	शून्य,                     /* SIOCGIWPRIV */
	शून्य,                     /* SIOCSIWSTATS */
	शून्य,                     /* SIOCGIWSTATS */
	dummy,                    /* SIOCSIWSPY */
	dummy,                    /* SIOCGIWSPY */
	शून्य,                     /* SIOCGIWTHRSPY */
	शून्य,                     /* SIOCWIWTHRSPY */
	r8192_wx_set_wap,	  /* SIOCSIWAP */
	r8192_wx_get_wap,         /* SIOCGIWAP */
	r8192_wx_set_mlme,                     /* MLME-- */
	dummy,                     /* SIOCGIWAPLIST -- deprecated */
	r8192_wx_set_scan,        /* SIOCSIWSCAN */
	r8192_wx_get_scan,        /* SIOCGIWSCAN */
	r8192_wx_set_essid,       /* SIOCSIWESSID */
	r8192_wx_get_essid,       /* SIOCGIWESSID */
	dummy,                    /* SIOCSIWNICKN */
	dummy,                    /* SIOCGIWNICKN */
	शून्य,                     /* -- hole -- */
	शून्य,                     /* -- hole -- */
	r8192_wx_set_rate,        /* SIOCSIWRATE */
	r8192_wx_get_rate,        /* SIOCGIWRATE */
	r8192_wx_set_rts,                    /* SIOCSIWRTS */
	r8192_wx_get_rts,                    /* SIOCGIWRTS */
	r8192_wx_set_frag,        /* SIOCSIWFRAG */
	r8192_wx_get_frag,        /* SIOCGIWFRAG */
	dummy,                    /* SIOCSIWTXPOW */
	dummy,                    /* SIOCGIWTXPOW */
	r8192_wx_set_retry,       /* SIOCSIWRETRY */
	r8192_wx_get_retry,       /* SIOCGIWRETRY */
	r8192_wx_set_enc,         /* SIOCSIWENCODE */
	r8192_wx_get_enc,         /* SIOCGIWENCODE */
	r8192_wx_set_घातer,                    /* SIOCSIWPOWER */
	r8192_wx_get_घातer,                    /* SIOCGIWPOWER */
	शून्य,			/*---hole---*/
	शून्य,			/*---hole---*/
	r8192_wx_set_gen_ie, /* शून्य, */		/* SIOCSIWGENIE */
	शून्य,			/* SIOCSIWGENIE */

	r8192_wx_set_auth,/* शून्य, */			/* SIOCSIWAUTH */
	शून्य,/* r8192_wx_get_auth, */ /* शून्य, */	/* SIOCSIWAUTH */
	r8192_wx_set_enc_ext,			/* SIOCSIWENCODEEXT */
	शून्य,/* r8192_wx_get_enc_ext, *//* शून्य, */			/* SIOCSIWENCODEEXT */
	शून्य,			/* SIOCSIWPMKSA */
	शून्य,			 /*---hole---*/

पूर्ण;

अटल स्थिर काष्ठा iw_priv_args r8192_निजी_args[] = अणु
	अणु
		SIOCIWFIRSTPRIV + 0x0,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "badcrc"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x1,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "activescan"

	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x2,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "rawtx"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x3,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "forcereset"
	पूर्ण
पूर्ण;

अटल iw_handler r8192_निजी_handler[] = अणु
	r8192_wx_set_crcmon,
	r8192_wx_set_scan_type,
	r8192_wx_set_rawtx,
	r8192_wx_क्रमce_reset,
पूर्ण;

काष्ठा iw_statistics *r8192_get_wireless_stats(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा ieee80211_device *ieee = priv->ieee80211;
	काष्ठा iw_statistics *wstats = &priv->wstats;
	पूर्णांक पंचांगp_level = 0;
	पूर्णांक पंचांगp_qual = 0;
	पूर्णांक पंचांगp_noise = 0;

	अगर (ieee->state < IEEE80211_LINKED) अणु
		wstats->qual.qual = 0;
		wstats->qual.level = 0;
		wstats->qual.noise = 0;
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

स्थिर काष्ठा iw_handler_def  r8192_wx_handlers_def = अणु
	.standard = r8192_wx_handlers,
	.num_standard = ARRAY_SIZE(r8192_wx_handlers),
	.निजी = r8192_निजी_handler,
	.num_निजी = ARRAY_SIZE(r8192_निजी_handler),
	.num_निजी_args = माप(r8192_निजी_args) / माप(काष्ठा iw_priv_args),
	.get_wireless_stats = r8192_get_wireless_stats,
	.निजी_args = (काष्ठा iw_priv_args *)r8192_निजी_args,
पूर्ण;
