<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************

  Copyright(c) 2004 Intel Corporation. All rights reserved.

  Portions of this file are based on the WEP enablement code provided by the
  Host AP project hostap-drivers v0.1.3
  Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
  <jkmaline@cc.hut.fi>
  Copyright (c) 2002-2003, Jouni Malinen <jkmaline@cc.hut.fi>

  Contact Inक्रमmation:
  James P. Ketrenos <ipw2100-admin@linux.पूर्णांकel.com>
  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

******************************************************************************/
#समावेश <linux/wireless.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश "ieee80211.h"
काष्ठा modes_unit अणु
	अक्षर *mode_string;
	पूर्णांक mode_size;
पूर्ण;
अटल काष्ठा modes_unit ieee80211_modes[] = अणु
	अणु"a", 1पूर्ण,
	अणु"b", 1पूर्ण,
	अणु"g", 1पूर्ण,
	अणु"?", 1पूर्ण,
	अणु"N-24G", 5पूर्ण,
	अणु"N-5G", 4पूर्ण,
पूर्ण;

#घोषणा iwe_stream_add_event_rsl iwe_stream_add_event

#घोषणा MAX_CUSTOM_LEN 64
अटल अंतरभूत अक्षर *rtl819x_translate_scan(काष्ठा ieee80211_device *ieee,
					   अक्षर *start, अक्षर *stop,
					   काष्ठा ieee80211_network *network,
					   काष्ठा iw_request_info *info)
अणु
	अक्षर custom[MAX_CUSTOM_LEN];
	अक्षर proto_name[IFNAMSIZ];
	अक्षर *pname = proto_name;
	अक्षर *p;
	काष्ठा iw_event iwe;
	पूर्णांक i, j;
	u16 max_rate, rate;
	अटल u8	EWC11NHTCap[] = अणु0x00, 0x90, 0x4c, 0x33पूर्ण;

	/* First entry *MUST* be the AP MAC address */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
	स_नकल(iwe.u.ap_addr.sa_data, network->bssid, ETH_ALEN);
	start = iwe_stream_add_event_rsl(info, start, stop, &iwe, IW_EV_ADDR_LEN);
	/* Reमुख्यing entries will be displayed in the order we provide them */

	/* Add the ESSID */
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.flags = 1;
//	अगर (network->flags & NETWORK_EMPTY_ESSID) अणु
	अगर (network->ssid_len == 0) अणु
		iwe.u.data.length = माप("<hidden>");
		start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, "<hidden>");
	पूर्ण अन्यथा अणु
		iwe.u.data.length = min(network->ssid_len, (u8)32);
		start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, network->ssid);
	पूर्ण
	/* Add the protocol name */
	iwe.cmd = SIOCGIWNAME;
	क्रम (i = 0; i < ARRAY_SIZE(ieee80211_modes); i++) अणु
		अगर (network->mode & BIT(i)) अणु
			प्र_लिखो(pname, ieee80211_modes[i].mode_string, ieee80211_modes[i].mode_size);
			pname += ieee80211_modes[i].mode_size;
		पूर्ण
	पूर्ण
	*pname = '\0';
	snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE802.11%s", proto_name);
	start = iwe_stream_add_event_rsl(info, start, stop, &iwe, IW_EV_CHAR_LEN);
	/* Add mode */
	iwe.cmd = SIOCGIWMODE;
	अगर (network->capability &
	    (WLAN_CAPABILITY_BSS | WLAN_CAPABILITY_IBSS)) अणु
		अगर (network->capability & WLAN_CAPABILITY_BSS)
			iwe.u.mode = IW_MODE_MASTER;
		अन्यथा
			iwe.u.mode = IW_MODE_ADHOC;
		start = iwe_stream_add_event_rsl(info, start, stop, &iwe, IW_EV_UINT_LEN);
	पूर्ण

	/* Add frequency/channel */
	iwe.cmd = SIOCGIWFREQ;
/*	iwe.u.freq.m = ieee80211_frequency(network->channel, network->mode);
	iwe.u.freq.e = 3; */
	iwe.u.freq.m = network->channel;
	iwe.u.freq.e = 0;
	iwe.u.freq.i = 0;
	start = iwe_stream_add_event_rsl(info, start, stop, &iwe, IW_EV_FREQ_LEN);
	/* Add encryption capability */
	iwe.cmd = SIOCGIWENCODE;
	अगर (network->capability & WLAN_CAPABILITY_PRIVACY)
		iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
	अन्यथा
		iwe.u.data.flags = IW_ENCODE_DISABLED;
	iwe.u.data.length = 0;
	start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, network->ssid);
	/* Add basic and extended rates */
	max_rate = 0;
	p = custom;
	p += scnम_लिखो(p, MAX_CUSTOM_LEN - (p - custom), " Rates (Mb/s): ");
	क्रम (i = 0, j = 0; i < network->rates_len; ) अणु
		अगर (j < network->rates_ex_len &&
		    ((network->rates_ex[j] & 0x7F) <
		     (network->rates[i] & 0x7F)))
			rate = network->rates_ex[j++] & 0x7F;
		अन्यथा
			rate = network->rates[i++] & 0x7F;
		अगर (rate > max_rate)
			max_rate = rate;
		p += scnम_लिखो(p, MAX_CUSTOM_LEN - (p - custom),
			      "%d%s ", rate >> 1, (rate & 1) ? ".5" : "");
	पूर्ण
	क्रम (; j < network->rates_ex_len; j++) अणु
		rate = network->rates_ex[j] & 0x7F;
		p += scnम_लिखो(p, MAX_CUSTOM_LEN - (p - custom),
			      "%d%s ", rate >> 1, (rate & 1) ? ".5" : "");
		अगर (rate > max_rate)
			max_rate = rate;
	पूर्ण

	अगर (network->mode >= IEEE_N_24G) /* add N rate here */ अणु
		काष्ठा ht_capability_ele *ht_cap = शून्य;
		bool is40M = false, isShortGI = false;
		u8 max_mcs = 0;
		अगर (!स_भेद(network->bssht.bdHTCapBuf, EWC11NHTCap, 4))
			ht_cap = (काष्ठा ht_capability_ele *)&network->bssht.bdHTCapBuf[4];
		अन्यथा
			ht_cap = (काष्ठा ht_capability_ele *)&network->bssht.bdHTCapBuf[0];
		is40M = (ht_cap->ChlWidth) ? 1 : 0;
		isShortGI = (ht_cap->ChlWidth) ?
					((ht_cap->ShortGI40Mhz) ? 1 : 0) :
					((ht_cap->ShortGI20Mhz) ? 1 : 0);

		max_mcs = HTGetHighestMCSRate(ieee, ht_cap->MCS, MCS_FILTER_ALL);
		rate = MCS_DATA_RATE[is40M][isShortGI][max_mcs & 0x7f];
		अगर (rate > max_rate)
			max_rate = rate;
	पूर्ण
	iwe.cmd = SIOCGIWRATE;
	iwe.u.bitrate.fixed = iwe.u.bitrate.disabled = 0;
	iwe.u.bitrate.value = max_rate * 500000;
	start = iwe_stream_add_event_rsl(info, start, stop, &iwe,
				     IW_EV_PARAM_LEN);
	iwe.cmd = IWEVCUSTOM;
	iwe.u.data.length = p - custom;
	अगर (iwe.u.data.length)
		start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, custom);
	/* Add quality statistics */
	/* TODO: Fix these values... */
	iwe.cmd = IWEVQUAL;
	iwe.u.qual.qual = network->stats.संकेत;
	iwe.u.qual.level = network->stats.rssi;
	iwe.u.qual.noise = network->stats.noise;
	iwe.u.qual.updated = network->stats.mask & IEEE80211_STATMASK_WEMASK;
	अगर (!(network->stats.mask & IEEE80211_STATMASK_RSSI))
		iwe.u.qual.updated |= IW_QUAL_LEVEL_INVALID;
	अगर (!(network->stats.mask & IEEE80211_STATMASK_NOISE))
		iwe.u.qual.updated |= IW_QUAL_NOISE_INVALID;
	अगर (!(network->stats.mask & IEEE80211_STATMASK_SIGNAL))
		iwe.u.qual.updated |= IW_QUAL_QUAL_INVALID;
	iwe.u.qual.updated = 7;
	start = iwe_stream_add_event_rsl(info, start, stop, &iwe, IW_EV_QUAL_LEN);
	iwe.cmd = IWEVCUSTOM;
	p = custom;

	iwe.u.data.length = p - custom;
	अगर (iwe.u.data.length)
		start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, custom);

	अगर (ieee->wpa_enabled && network->wpa_ie_len) अणु
		अक्षर buf[MAX_WPA_IE_LEN * 2 + 30];
	//	prपूर्णांकk("WPA IE\n");
		u8 *p = buf;
		p += प्र_लिखो(p, "wpa_ie=");
		क्रम (i = 0; i < network->wpa_ie_len; i++)
			p += प्र_लिखो(p, "%02x", network->wpa_ie[i]);

		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = IWEVCUSTOM;
		iwe.u.data.length = म_माप(buf);
		start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, buf);
	पूर्ण

	अगर (ieee->wpa_enabled && network->rsn_ie_len) अणु
		अक्षर buf[MAX_WPA_IE_LEN * 2 + 30];

		u8 *p = buf;
		p += प्र_लिखो(p, "rsn_ie=");
		क्रम (i = 0; i < network->rsn_ie_len; i++)
			p += प्र_लिखो(p, "%02x", network->rsn_ie[i]);

		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = IWEVCUSTOM;
		iwe.u.data.length = म_माप(buf);
		start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, buf);
	पूर्ण


	/* Add EXTRA: Age to display seconds since last beacon/probe response
	 * क्रम given network. */
	iwe.cmd = IWEVCUSTOM;
	p = custom;
	p += scnम_लिखो(p, MAX_CUSTOM_LEN - (p - custom),
		      " Last beacon: %lums ago", (jअगरfies - network->last_scanned) / (HZ / 100));
	iwe.u.data.length = p - custom;
	अगर (iwe.u.data.length)
		start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, custom);

	वापस start;
पूर्ण

पूर्णांक ieee80211_wx_get_scan(काष्ठा ieee80211_device *ieee,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ieee80211_network *network;
	अचिन्हित दीर्घ flags;

	अक्षर *ev = extra;
//	अक्षर *stop = ev + IW_SCAN_MAX_DATA;
	अक्षर *stop = ev + wrqu->data.length;//IW_SCAN_MAX_DATA;
	//अक्षर *stop = ev + IW_SCAN_MAX_DATA;
	पूर्णांक i = 0;
	पूर्णांक err = 0;
	IEEE80211_DEBUG_WX("Getting scan\n");
	mutex_lock(&ieee->wx_mutex);
	spin_lock_irqsave(&ieee->lock, flags);

	list_क्रम_each_entry(network, &ieee->network_list, list) अणु
		i++;
		अगर ((stop - ev) < 200) अणु
			err = -E2BIG;
			अवरोध;
		पूर्ण
		अगर (ieee->scan_age == 0 ||
		    समय_after(network->last_scanned + ieee->scan_age, jअगरfies))
			ev = rtl819x_translate_scan(ieee, ev, stop, network, info);
		अन्यथा
			IEEE80211_DEBUG_SCAN(
				"Not showing network '%s ("
				"%pM)' due to age (%lums).\n",
				escape_essid(network->ssid,
					     network->ssid_len),
				network->bssid,
				(jअगरfies - network->last_scanned) / (HZ / 100));
	पूर्ण

	spin_unlock_irqrestore(&ieee->lock, flags);
	mutex_unlock(&ieee->wx_mutex);
	wrqu->data.length = ev -  extra;
	wrqu->data.flags = 0;

	IEEE80211_DEBUG_WX("exit: %d networks returned.\n", i);

	वापस err;
पूर्ण
EXPORT_SYMBOL(ieee80211_wx_get_scan);

पूर्णांक ieee80211_wx_set_encode(काष्ठा ieee80211_device *ieee,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *keybuf)
अणु
	काष्ठा iw_poपूर्णांक *erq = &(wrqu->encoding);
	काष्ठा net_device *dev = ieee->dev;
	काष्ठा ieee80211_security sec = अणु
		.flags = 0
	पूर्ण;
	पूर्णांक i, key, key_provided, len;
	काष्ठा ieee80211_crypt_data **crypt;

	IEEE80211_DEBUG_WX("SET_ENCODE\n");

	key = erq->flags & IW_ENCODE_INDEX;
	अगर (key) अणु
		अगर (key > WEP_KEYS)
			वापस -EINVAL;
		key--;
		key_provided = 1;
	पूर्ण अन्यथा अणु
		key_provided = 0;
		key = ieee->tx_keyidx;
	पूर्ण

	IEEE80211_DEBUG_WX("Key: %d [%s]\n", key, key_provided ?
			   "provided" : "default");
	crypt = &ieee->crypt[key];

	अगर (erq->flags & IW_ENCODE_DISABLED) अणु
		अगर (key_provided && *crypt) अणु
			IEEE80211_DEBUG_WX("Disabling encryption on key %d.\n",
					   key);
			ieee80211_crypt_delayed_deinit(ieee, crypt);
		पूर्ण अन्यथा
			IEEE80211_DEBUG_WX("Disabling encryption.\n");

		/* Check all the keys to see अगर any are still configured,
		 * and अगर no key index was provided, de-init them all */
		क्रम (i = 0; i < WEP_KEYS; i++) अणु
			अगर (ieee->crypt[i]) अणु
				अगर (key_provided)
					अवरोध;
				ieee80211_crypt_delayed_deinit(
					ieee, &ieee->crypt[i]);
			पूर्ण
		पूर्ण

		अगर (i == WEP_KEYS) अणु
			sec.enabled = 0;
			sec.level = SEC_LEVEL_0;
			sec.flags |= SEC_ENABLED | SEC_LEVEL;
		पूर्ण

		जाओ करोne;
	पूर्ण



	sec.enabled = 1;
	sec.flags |= SEC_ENABLED;

	अगर (*crypt && (*crypt)->ops &&
	    म_भेद((*crypt)->ops->name, "WEP") != 0) अणु
		/* changing to use WEP; deinit previously used algorithm
		 * on this key */
		ieee80211_crypt_delayed_deinit(ieee, crypt);
	पूर्ण

	अगर (!*crypt) अणु
		काष्ठा ieee80211_crypt_data *new_crypt;

		/* take WEP पूर्णांकo use */
		new_crypt = kzalloc(माप(काष्ठा ieee80211_crypt_data),
				    GFP_KERNEL);
		अगर (!new_crypt)
			वापस -ENOMEM;
		new_crypt->ops = try_then_request_module(ieee80211_get_crypto_ops("WEP"),
							 "ieee80211_crypt_wep");
		अगर (new_crypt->ops && try_module_get(new_crypt->ops->owner))
			new_crypt->priv = new_crypt->ops->init(key);

		अगर (!new_crypt->ops || !new_crypt->priv) अणु
			kमुक्त(new_crypt);
			new_crypt = शून्य;

			netdev_warn(dev, "could not initialize WEP: "
				    "load module ieee80211_crypt_wep\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		*crypt = new_crypt;
	पूर्ण

	/* If a new key was provided, set it up */
	अगर (erq->length > 0) अणु
		len = erq->length <= 5 ? 5 : 13;
		स_नकल(sec.keys[key], keybuf, erq->length);
		अगर (len > erq->length)
			स_रखो(sec.keys[key] + erq->length, 0,
			       len - erq->length);
		IEEE80211_DEBUG_WX("Setting key %d to '%s' (%d:%d bytes)\n",
				   key, escape_essid(sec.keys[key], len),
				   erq->length, len);
		sec.key_sizes[key] = len;
		(*crypt)->ops->set_key(sec.keys[key], len, शून्य,
				       (*crypt)->priv);
		sec.flags |= BIT(key);
		/* This ensures a key will be activated अगर no key is
		 * explicitly set
		 */
		अगर (key == sec.active_key)
			sec.flags |= SEC_ACTIVE_KEY;
		ieee->tx_keyidx = key;

	पूर्ण अन्यथा अणु
		len = (*crypt)->ops->get_key(sec.keys[key], WEP_KEY_LEN,
					     शून्य, (*crypt)->priv);
		अगर (len == 0) अणु
			/* Set a शेष key of all 0 */
			prपूर्णांकk("Setting key %d to all zero.\n",
					   key);

			IEEE80211_DEBUG_WX("Setting key %d to all zero.\n",
					   key);
			स_रखो(sec.keys[key], 0, 13);
			(*crypt)->ops->set_key(sec.keys[key], 13, शून्य,
					       (*crypt)->priv);
			sec.key_sizes[key] = 13;
			sec.flags |= BIT(key);
		पूर्ण

		/* No key data - just set the शेष TX key index */
		अगर (key_provided) अणु
			IEEE80211_DEBUG_WX(
				"Setting key %d to default Tx key.\n", key);
			ieee->tx_keyidx = key;
			sec.active_key = key;
			sec.flags |= SEC_ACTIVE_KEY;
		पूर्ण
	पूर्ण

 करोne:
	ieee->खोलो_wep = !(erq->flags & IW_ENCODE_RESTRICTED);
	ieee->auth_mode = ieee->खोलो_wep ? WLAN_AUTH_OPEN : WLAN_AUTH_SHARED_KEY;
	sec.auth_mode = ieee->खोलो_wep ? WLAN_AUTH_OPEN : WLAN_AUTH_SHARED_KEY;
	sec.flags |= SEC_AUTH_MODE;
	IEEE80211_DEBUG_WX("Auth: %s\n", sec.auth_mode == WLAN_AUTH_OPEN ?
			   "OPEN" : "SHARED KEY");

	/* For now we just support WEP, so only set that security level...
	 * TODO: When WPA is added this is one place that needs to change */
	sec.flags |= SEC_LEVEL;
	sec.level = SEC_LEVEL_1; /* 40 and 104 bit WEP */

	अगर (ieee->set_security)
		ieee->set_security(dev, &sec);

	/* Do not reset port अगर card is in Managed mode since resetting will
	 * generate new IEEE 802.11 authentication which may end up in looping
	 * with IEEE 802.1X.  If your hardware requires a reset after WEP
	 * configuration (क्रम example... Prism2), implement the reset_port in
	 * the callbacks काष्ठाures used to initialize the 802.11 stack. */
	अगर (ieee->reset_on_keychange &&
	    ieee->iw_mode != IW_MODE_INFRA &&
	    ieee->reset_port && ieee->reset_port(dev)) अणु
		netdev_dbg(ieee->dev, "reset_port failed\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ieee80211_wx_set_encode);

पूर्णांक ieee80211_wx_get_encode(काष्ठा ieee80211_device *ieee,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *keybuf)
अणु
	काष्ठा iw_poपूर्णांक *erq = &(wrqu->encoding);
	पूर्णांक len, key;
	काष्ठा ieee80211_crypt_data *crypt;

	IEEE80211_DEBUG_WX("GET_ENCODE\n");

	अगर (ieee->iw_mode == IW_MODE_MONITOR)
		वापस -1;

	key = erq->flags & IW_ENCODE_INDEX;
	अगर (key) अणु
		अगर (key > WEP_KEYS)
			वापस -EINVAL;
		key--;
	पूर्ण अन्यथा
		key = ieee->tx_keyidx;

	crypt = ieee->crypt[key];
	erq->flags = key + 1;

	अगर (!crypt || !crypt->ops) अणु
		erq->length = 0;
		erq->flags |= IW_ENCODE_DISABLED;
		वापस 0;
	पूर्ण
	len = crypt->ops->get_key(keybuf, SCM_KEY_LEN, शून्य, crypt->priv);
	erq->length = (len >= 0 ? len : 0);

	erq->flags |= IW_ENCODE_ENABLED;

	अगर (ieee->खोलो_wep)
		erq->flags |= IW_ENCODE_OPEN;
	अन्यथा
		erq->flags |= IW_ENCODE_RESTRICTED;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ieee80211_wx_get_encode);

पूर्णांक ieee80211_wx_set_encode_ext(काष्ठा ieee80211_device *ieee,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	काष्ठा net_device *dev = ieee->dev;
	काष्ठा iw_poपूर्णांक *encoding = &wrqu->encoding;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
	पूर्णांक i, idx;
	पूर्णांक group_key = 0;
	स्थिर अक्षर *alg, *module;
	काष्ठा ieee80211_crypto_ops *ops;
	काष्ठा ieee80211_crypt_data **crypt;

	काष्ठा ieee80211_security sec = अणु
		.flags = 0,
	पूर्ण;
	idx = encoding->flags & IW_ENCODE_INDEX;
	अगर (idx) अणु
		अगर (idx < 1 || idx > WEP_KEYS)
			वापस -EINVAL;
		idx--;
	पूर्ण अन्यथा
		idx = ieee->tx_keyidx;

	अगर (ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY) अणु

		crypt = &ieee->crypt[idx];

		group_key = 1;
	पूर्ण अन्यथा अणु
		/* some Cisco APs use idx>0 क्रम unicast in dynamic WEP */
		अगर (idx != 0 && ext->alg != IW_ENCODE_ALG_WEP)
			वापस -EINVAL;
		अगर (ieee->iw_mode == IW_MODE_INFRA)

			crypt = &ieee->crypt[idx];

		अन्यथा
			वापस -EINVAL;
	पूर्ण

	sec.flags |= SEC_ENABLED;// | SEC_ENCRYPT;
	अगर ((encoding->flags & IW_ENCODE_DISABLED) ||
	    ext->alg == IW_ENCODE_ALG_NONE) अणु
		अगर (*crypt)
			ieee80211_crypt_delayed_deinit(ieee, crypt);

		क्रम (i = 0; i < WEP_KEYS; i++)

			अगर (ieee->crypt[i])

				अवरोध;

		अगर (i == WEP_KEYS) अणु
			sec.enabled = 0;
		      //  sec.encrypt = 0;
			sec.level = SEC_LEVEL_0;
			sec.flags |= SEC_LEVEL;
		पूर्ण
		जाओ करोne;
	पूर्ण

	sec.enabled = 1;
    //    sec.encrypt = 1;
	चयन (ext->alg) अणु
	हाल IW_ENCODE_ALG_WEP:
		alg = "WEP";
		module = "ieee80211_crypt_wep";
		अवरोध;
	हाल IW_ENCODE_ALG_TKIP:
		alg = "TKIP";
		module = "ieee80211_crypt_tkip";
		अवरोध;
	हाल IW_ENCODE_ALG_CCMP:
		alg = "CCMP";
		module = "ieee80211_crypt_ccmp";
		अवरोध;
	शेष:
		IEEE80211_DEBUG_WX("%s: unknown crypto alg %d\n",
				   dev->name, ext->alg);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण
	prपूर्णांकk("alg name:%s\n", alg);

	ops = try_then_request_module(ieee80211_get_crypto_ops(alg), module);
	अगर (!ops) अणु
		IEEE80211_DEBUG_WX("%s: unknown crypto alg %d\n",
				   dev->name, ext->alg);
		prपूर्णांकk("========>unknown crypto alg %d\n", ext->alg);
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
			new_crypt->priv = new_crypt->ops->init(idx);
		अगर (!new_crypt->priv) अणु
			kमुक्त(new_crypt);
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
		*crypt = new_crypt;
	पूर्ण

	अगर (ext->key_len > 0 && (*crypt)->ops->set_key &&
	    (*crypt)->ops->set_key(ext->key, ext->key_len, ext->rx_seq,
				   (*crypt)->priv) < 0) अणु
		IEEE80211_DEBUG_WX("%s: key setting failed\n", dev->name);
		prपूर्णांकk("key setting failed\n");
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण
 //skip_host_crypt:
	अगर (ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY) अणु
		ieee->tx_keyidx = idx;
		sec.active_key = idx;
		sec.flags |= SEC_ACTIVE_KEY;
	पूर्ण

	अगर (ext->alg != IW_ENCODE_ALG_NONE) अणु
		//स_नकल(sec.keys[idx], ext->key, ext->key_len);
		sec.key_sizes[idx] = ext->key_len;
		sec.flags |= BIT(idx);
		अगर (ext->alg == IW_ENCODE_ALG_WEP) अणु
		      //  sec.encode_alg[idx] = SEC_ALG_WEP;
			sec.flags |= SEC_LEVEL;
			sec.level = SEC_LEVEL_1;
		पूर्ण अन्यथा अगर (ext->alg == IW_ENCODE_ALG_TKIP) अणु
		      //  sec.encode_alg[idx] = SEC_ALG_TKIP;
			sec.flags |= SEC_LEVEL;
			sec.level = SEC_LEVEL_2;
		पूर्ण अन्यथा अगर (ext->alg == IW_ENCODE_ALG_CCMP) अणु
		       // sec.encode_alg[idx] = SEC_ALG_CCMP;
			sec.flags |= SEC_LEVEL;
			sec.level = SEC_LEVEL_3;
		पूर्ण
		/* Don't set sec level क्रम group keys. */
		अगर (group_key)
			sec.flags &= ~SEC_LEVEL;
	पूर्ण
करोne:
	अगर (ieee->set_security)
		ieee->set_security(ieee->dev, &sec);

	अगर (ieee->reset_on_keychange &&
	    ieee->iw_mode != IW_MODE_INFRA &&
	    ieee->reset_port && ieee->reset_port(dev)) अणु
		IEEE80211_DEBUG_WX("%s: reset_port failed\n", dev->name);
		वापस -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ieee80211_wx_set_encode_ext);

पूर्णांक ieee80211_wx_get_encode_ext(काष्ठा ieee80211_device *ieee,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा iw_poपूर्णांक *encoding = &wrqu->encoding;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
	काष्ठा ieee80211_crypt_data *crypt;
	पूर्णांक idx, max_key_len;

	max_key_len = encoding->length - माप(*ext);
	अगर (max_key_len < 0)
		वापस -EINVAL;

	idx = encoding->flags & IW_ENCODE_INDEX;
	अगर (idx) अणु
		अगर (idx < 1 || idx > WEP_KEYS)
			वापस -EINVAL;
		idx--;
	पूर्ण अन्यथा
		idx = ieee->tx_keyidx;

	अगर (!(ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY) &&
	    ext->alg != IW_ENCODE_ALG_WEP)
		अगर (idx != 0 || ieee->iw_mode != IW_MODE_INFRA)
			वापस -EINVAL;

	crypt = ieee->crypt[idx];
	encoding->flags = idx + 1;
	स_रखो(ext, 0, माप(*ext));

	अगर (!crypt || !crypt->ops) अणु
		ext->alg = IW_ENCODE_ALG_NONE;
		ext->key_len = 0;
		encoding->flags |= IW_ENCODE_DISABLED;
	पूर्ण अन्यथा अणु
		अगर (म_भेद(crypt->ops->name, "WEP") == 0)
			ext->alg = IW_ENCODE_ALG_WEP;
		अन्यथा अगर (म_भेद(crypt->ops->name, "TKIP"))
			ext->alg = IW_ENCODE_ALG_TKIP;
		अन्यथा अगर (म_भेद(crypt->ops->name, "CCMP"))
			ext->alg = IW_ENCODE_ALG_CCMP;
		अन्यथा
			वापस -EINVAL;
		ext->key_len = crypt->ops->get_key(ext->key, SCM_KEY_LEN, शून्य, crypt->priv);
		encoding->flags |= IW_ENCODE_ENABLED;
		अगर (ext->key_len &&
		    (ext->alg == IW_ENCODE_ALG_TKIP ||
		     ext->alg == IW_ENCODE_ALG_CCMP))
			ext->ext_flags |= IW_ENCODE_EXT_TX_SEQ_VALID;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ieee80211_wx_get_encode_ext);

पूर्णांक ieee80211_wx_set_mlme(काष्ठा ieee80211_device *ieee,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा iw_mlme *mlme = (काष्ठा iw_mlme *)extra;
	चयन (mlme->cmd) अणु
	हाल IW_MLME_DEAUTH:
	हाल IW_MLME_DISASSOC:
		ieee80211_disassociate(ieee);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ieee80211_wx_set_mlme);

पूर्णांक ieee80211_wx_set_auth(काष्ठा ieee80211_device *ieee,
			       काष्ठा iw_request_info *info,
			       काष्ठा iw_param *data, अक्षर *extra)
अणु
	चयन (data->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_WPA_VERSION:
	     /*need to support wpa2 here*/
		अवरोध;
	हाल IW_AUTH_CIPHER_PAIRWISE:
	हाल IW_AUTH_CIPHER_GROUP:
	हाल IW_AUTH_KEY_MGMT:
		/*
 *                  * Host AP driver करोes not use these parameters and allows
 *                                   * wpa_supplicant to control them पूर्णांकernally.
 *                                                    */
		अवरोध;
	हाल IW_AUTH_TKIP_COUNTERMEASURES:
		ieee->tkip_countermeasures = data->value;
		अवरोध;
	हाल IW_AUTH_DROP_UNENCRYPTED:
		ieee->drop_unencrypted = data->value;
		अवरोध;

	हाल IW_AUTH_80211_AUTH_ALG:
		//prपूर्णांकk("======>%s():data->value is %d\n",__func__,data->value);
	//	ieee->खोलो_wep = (data->value&IW_AUTH_ALG_OPEN_SYSTEM)?1:0;
		अगर (data->value & IW_AUTH_ALG_SHARED_KEY) अणु
			ieee->खोलो_wep = 0;
			ieee->auth_mode = 1;
		पूर्ण अन्यथा अगर (data->value & IW_AUTH_ALG_OPEN_SYSTEM) अणु
			ieee->खोलो_wep = 1;
			ieee->auth_mode = 0;
		पूर्ण अन्यथा अगर (data->value & IW_AUTH_ALG_LEAP) अणु
			ieee->खोलो_wep = 1;
			ieee->auth_mode = 2;
		पूर्ण अन्यथा
			वापस -EINVAL;
		अवरोध;

	हाल IW_AUTH_WPA_ENABLED:
		ieee->wpa_enabled = (data->value) ? 1 : 0;
		अवरोध;

	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:
		ieee->ieee802_1x = data->value;
		अवरोध;
	हाल IW_AUTH_PRIVACY_INVOKED:
		ieee->privacy_invoked = data->value;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ieee80211_wx_set_auth);

पूर्णांक ieee80211_wx_set_gen_ie(काष्ठा ieee80211_device *ieee, u8 *ie, माप_प्रकार len)
अणु
	u8 *buf;

	अगर (len > MAX_WPA_IE_LEN || (len && !ie)) अणु
		//prपूर्णांकk("return error out, len:%d\n", len);
		वापस -EINVAL;
	पूर्ण


	अगर (len) अणु
		अगर (len != ie[1] + 2) अणु
			prपूर्णांकk("len:%zu, ie:%d\n", len, ie[1]);
			वापस -EINVAL;
		पूर्ण
		buf = kmemdup(ie, len, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;
		kमुक्त(ieee->wpa_ie);
		ieee->wpa_ie = buf;
		ieee->wpa_ie_len = len;
	पूर्ण अन्यथा अणु
		kमुक्त(ieee->wpa_ie);
		ieee->wpa_ie = शून्य;
		ieee->wpa_ie_len = 0;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ieee80211_wx_set_gen_ie);
