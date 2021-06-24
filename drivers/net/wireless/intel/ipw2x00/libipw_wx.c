<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************

  Copyright(c) 2004-2005 Intel Corporation. All rights reserved.

  Portions of this file are based on the WEP enablement code provided by the
  Host AP project hostap-drivers v0.1.3
  Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
  <j@w1.fi>
  Copyright (c) 2002-2003, Jouni Malinen <j@w1.fi>


  Contact Inक्रमmation:
  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

******************************************************************************/

#समावेश <linux/hardirq.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>

#समावेश <net/lib80211.h>
#समावेश <linux/wireless.h>

#समावेश "libipw.h"

अटल स्थिर अक्षर *libipw_modes[] = अणु
	"?", "a", "b", "ab", "g", "ag", "bg", "abg"
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक elapsed_jअगरfies_msecs(अचिन्हित दीर्घ start)
अणु
	अचिन्हित दीर्घ end = jअगरfies;

	अगर (end >= start)
		वापस jअगरfies_to_msecs(end - start);

	वापस jअगरfies_to_msecs(end + (MAX_JIFFY_OFFSET - start) + 1);
पूर्ण

#घोषणा MAX_CUSTOM_LEN 64
अटल अक्षर *libipw_translate_scan(काष्ठा libipw_device *ieee,
				      अक्षर *start, अक्षर *stop,
				      काष्ठा libipw_network *network,
				      काष्ठा iw_request_info *info)
अणु
	अक्षर custom[MAX_CUSTOM_LEN];
	अक्षर *p;
	काष्ठा iw_event iwe;
	पूर्णांक i, j;
	अक्षर *current_val;	/* For rates */
	u8 rate;

	/* First entry *MUST* be the AP MAC address */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
	स_नकल(iwe.u.ap_addr.sa_data, network->bssid, ETH_ALEN);
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_ADDR_LEN);

	/* Reमुख्यing entries will be displayed in the order we provide them */

	/* Add the ESSID */
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.flags = 1;
	iwe.u.data.length = min(network->ssid_len, (u8) 32);
	start = iwe_stream_add_poपूर्णांक(info, start, stop,
				     &iwe, network->ssid);

	/* Add the protocol name */
	iwe.cmd = SIOCGIWNAME;
	snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11%s",
		 libipw_modes[network->mode]);
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_CHAR_LEN);

	/* Add mode */
	iwe.cmd = SIOCGIWMODE;
	अगर (network->capability & (WLAN_CAPABILITY_ESS | WLAN_CAPABILITY_IBSS)) अणु
		अगर (network->capability & WLAN_CAPABILITY_ESS)
			iwe.u.mode = IW_MODE_MASTER;
		अन्यथा
			iwe.u.mode = IW_MODE_ADHOC;

		start = iwe_stream_add_event(info, start, stop,
					     &iwe, IW_EV_UINT_LEN);
	पूर्ण

	/* Add channel and frequency */
	/* Note : userspace स्वतःmatically computes channel using iwrange */
	iwe.cmd = SIOCGIWFREQ;
	iwe.u.freq.m = libipw_channel_to_freq(ieee, network->channel);
	iwe.u.freq.e = 6;
	iwe.u.freq.i = 0;
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_FREQ_LEN);

	/* Add encryption capability */
	iwe.cmd = SIOCGIWENCODE;
	अगर (network->capability & WLAN_CAPABILITY_PRIVACY)
		iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
	अन्यथा
		iwe.u.data.flags = IW_ENCODE_DISABLED;
	iwe.u.data.length = 0;
	start = iwe_stream_add_poपूर्णांक(info, start, stop,
				     &iwe, network->ssid);

	/* Add basic and extended rates */
	/* Rate : stuffing multiple values in a single event require a bit
	 * more of magic - Jean II */
	current_val = start + iwe_stream_lcp_len(info);
	iwe.cmd = SIOCGIWRATE;
	/* Those two flags are ignored... */
	iwe.u.bitrate.fixed = iwe.u.bitrate.disabled = 0;

	क्रम (i = 0, j = 0; i < network->rates_len;) अणु
		अगर (j < network->rates_ex_len &&
		    ((network->rates_ex[j] & 0x7F) <
		     (network->rates[i] & 0x7F)))
			rate = network->rates_ex[j++] & 0x7F;
		अन्यथा
			rate = network->rates[i++] & 0x7F;
		/* Bit rate given in 500 kb/s units (+ 0x80) */
		iwe.u.bitrate.value = ((rate & 0x7f) * 500000);
		/* Add new value to event */
		current_val = iwe_stream_add_value(info, start, current_val,
						   stop, &iwe, IW_EV_PARAM_LEN);
	पूर्ण
	क्रम (; j < network->rates_ex_len; j++) अणु
		rate = network->rates_ex[j] & 0x7F;
		/* Bit rate given in 500 kb/s units (+ 0x80) */
		iwe.u.bitrate.value = ((rate & 0x7f) * 500000);
		/* Add new value to event */
		current_val = iwe_stream_add_value(info, start, current_val,
						   stop, &iwe, IW_EV_PARAM_LEN);
	पूर्ण
	/* Check अगर we added any rate */
	अगर ((current_val - start) > iwe_stream_lcp_len(info))
		start = current_val;

	/* Add quality statistics */
	iwe.cmd = IWEVQUAL;
	iwe.u.qual.updated = IW_QUAL_QUAL_UPDATED | IW_QUAL_LEVEL_UPDATED |
	    IW_QUAL_NOISE_UPDATED;

	अगर (!(network->stats.mask & LIBIPW_STATMASK_RSSI)) अणु
		iwe.u.qual.updated |= IW_QUAL_QUAL_INVALID |
		    IW_QUAL_LEVEL_INVALID;
		iwe.u.qual.qual = 0;
	पूर्ण अन्यथा अणु
		अगर (ieee->perfect_rssi == ieee->worst_rssi)
			iwe.u.qual.qual = 100;
		अन्यथा
			iwe.u.qual.qual =
			    (100 *
			     (ieee->perfect_rssi - ieee->worst_rssi) *
			     (ieee->perfect_rssi - ieee->worst_rssi) -
			     (ieee->perfect_rssi - network->stats.rssi) *
			     (15 * (ieee->perfect_rssi - ieee->worst_rssi) +
			      62 * (ieee->perfect_rssi -
				    network->stats.rssi))) /
			    ((ieee->perfect_rssi -
			      ieee->worst_rssi) * (ieee->perfect_rssi -
						   ieee->worst_rssi));
		अगर (iwe.u.qual.qual > 100)
			iwe.u.qual.qual = 100;
		अन्यथा अगर (iwe.u.qual.qual < 1)
			iwe.u.qual.qual = 0;
	पूर्ण

	अगर (!(network->stats.mask & LIBIPW_STATMASK_NOISE)) अणु
		iwe.u.qual.updated |= IW_QUAL_NOISE_INVALID;
		iwe.u.qual.noise = 0;
	पूर्ण अन्यथा अणु
		iwe.u.qual.noise = network->stats.noise;
	पूर्ण

	अगर (!(network->stats.mask & LIBIPW_STATMASK_SIGNAL)) अणु
		iwe.u.qual.updated |= IW_QUAL_LEVEL_INVALID;
		iwe.u.qual.level = 0;
	पूर्ण अन्यथा अणु
		iwe.u.qual.level = network->stats.संकेत;
	पूर्ण

	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_QUAL_LEN);

	iwe.cmd = IWEVCUSTOM;
	p = custom;

	iwe.u.data.length = p - custom;
	अगर (iwe.u.data.length)
		start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, custom);

	स_रखो(&iwe, 0, माप(iwe));
	अगर (network->wpa_ie_len) अणु
		अक्षर buf[MAX_WPA_IE_LEN];
		स_नकल(buf, network->wpa_ie, network->wpa_ie_len);
		iwe.cmd = IWEVGENIE;
		iwe.u.data.length = network->wpa_ie_len;
		start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, buf);
	पूर्ण

	स_रखो(&iwe, 0, माप(iwe));
	अगर (network->rsn_ie_len) अणु
		अक्षर buf[MAX_WPA_IE_LEN];
		स_नकल(buf, network->rsn_ie, network->rsn_ie_len);
		iwe.cmd = IWEVGENIE;
		iwe.u.data.length = network->rsn_ie_len;
		start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, buf);
	पूर्ण

	/* Add EXTRA: Age to display seconds since last beacon/probe response
	 * क्रम given network. */
	iwe.cmd = IWEVCUSTOM;
	p = custom;
	p += scnम_लिखो(p, MAX_CUSTOM_LEN - (p - custom),
		      " Last beacon: %ums ago",
		      elapsed_jअगरfies_msecs(network->last_scanned));
	iwe.u.data.length = p - custom;
	अगर (iwe.u.data.length)
		start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, custom);

	/* Add spectrum management inक्रमmation */
	iwe.cmd = -1;
	p = custom;
	p += scnम_लिखो(p, MAX_CUSTOM_LEN - (p - custom), " Channel flags: ");

	अगर (libipw_get_channel_flags(ieee, network->channel) &
	    LIBIPW_CH_INVALID) अणु
		iwe.cmd = IWEVCUSTOM;
		p += scnम_लिखो(p, MAX_CUSTOM_LEN - (p - custom), "INVALID ");
	पूर्ण

	अगर (libipw_get_channel_flags(ieee, network->channel) &
	    LIBIPW_CH_RADAR_DETECT) अणु
		iwe.cmd = IWEVCUSTOM;
		p += scnम_लिखो(p, MAX_CUSTOM_LEN - (p - custom), "DFS ");
	पूर्ण

	अगर (iwe.cmd == IWEVCUSTOM) अणु
		iwe.u.data.length = p - custom;
		start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, custom);
	पूर्ण

	वापस start;
पूर्ण

#घोषणा SCAN_ITEM_SIZE 128

पूर्णांक libipw_wx_get_scan(काष्ठा libipw_device *ieee,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा libipw_network *network;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	अक्षर *ev = extra;
	अक्षर *stop = ev + wrqu->data.length;
	पूर्णांक i = 0;

	LIBIPW_DEBUG_WX("Getting scan\n");

	spin_lock_irqsave(&ieee->lock, flags);

	list_क्रम_each_entry(network, &ieee->network_list, list) अणु
		i++;
		अगर (stop - ev < SCAN_ITEM_SIZE) अणु
			err = -E2BIG;
			अवरोध;
		पूर्ण

		अगर (ieee->scan_age == 0 ||
		    समय_after(network->last_scanned + ieee->scan_age, jअगरfies))
			ev = libipw_translate_scan(ieee, ev, stop, network,
						      info);
		अन्यथा अणु
			LIBIPW_DEBUG_SCAN("Not showing network '%*pE (%pM)' due to age (%ums).\n",
					  network->ssid_len, network->ssid,
					  network->bssid,
					  elapsed_jअगरfies_msecs(
					               network->last_scanned));
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&ieee->lock, flags);

	wrqu->data.length = ev - extra;
	wrqu->data.flags = 0;

	LIBIPW_DEBUG_WX("exit: %d networks returned.\n", i);

	वापस err;
पूर्ण

पूर्णांक libipw_wx_set_encode(काष्ठा libipw_device *ieee,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *keybuf)
अणु
	काष्ठा iw_poपूर्णांक *erq = &(wrqu->encoding);
	काष्ठा net_device *dev = ieee->dev;
	काष्ठा libipw_security sec = अणु
		.flags = 0
	पूर्ण;
	पूर्णांक i, key, key_provided, len;
	काष्ठा lib80211_crypt_data **crypt;
	पूर्णांक host_crypto = ieee->host_encrypt || ieee->host_decrypt;

	LIBIPW_DEBUG_WX("SET_ENCODE\n");

	key = erq->flags & IW_ENCODE_INDEX;
	अगर (key) अणु
		अगर (key > WEP_KEYS)
			वापस -EINVAL;
		key--;
		key_provided = 1;
	पूर्ण अन्यथा अणु
		key_provided = 0;
		key = ieee->crypt_info.tx_keyidx;
	पूर्ण

	LIBIPW_DEBUG_WX("Key: %d [%s]\n", key, key_provided ?
			   "provided" : "default");

	crypt = &ieee->crypt_info.crypt[key];

	अगर (erq->flags & IW_ENCODE_DISABLED) अणु
		अगर (key_provided && *crypt) अणु
			LIBIPW_DEBUG_WX("Disabling encryption on key %d.\n",
					   key);
			lib80211_crypt_delayed_deinit(&ieee->crypt_info, crypt);
		पूर्ण अन्यथा
			LIBIPW_DEBUG_WX("Disabling encryption.\n");

		/* Check all the keys to see अगर any are still configured,
		 * and अगर no key index was provided, de-init them all */
		क्रम (i = 0; i < WEP_KEYS; i++) अणु
			अगर (ieee->crypt_info.crypt[i] != शून्य) अणु
				अगर (key_provided)
					अवरोध;
				lib80211_crypt_delayed_deinit(&ieee->crypt_info,
							       &ieee->crypt_info.crypt[i]);
			पूर्ण
		पूर्ण

		अगर (i == WEP_KEYS) अणु
			sec.enabled = 0;
			sec.encrypt = 0;
			sec.level = SEC_LEVEL_0;
			sec.flags |= SEC_ENABLED | SEC_LEVEL | SEC_ENCRYPT;
		पूर्ण

		जाओ करोne;
	पूर्ण

	sec.enabled = 1;
	sec.encrypt = 1;
	sec.flags |= SEC_ENABLED | SEC_ENCRYPT;

	अगर (*crypt != शून्य && (*crypt)->ops != शून्य &&
	    म_भेद((*crypt)->ops->name, "WEP") != 0) अणु
		/* changing to use WEP; deinit previously used algorithm
		 * on this key */
		lib80211_crypt_delayed_deinit(&ieee->crypt_info, crypt);
	पूर्ण

	अगर (*crypt == शून्य && host_crypto) अणु
		काष्ठा lib80211_crypt_data *new_crypt;

		/* take WEP पूर्णांकo use */
		new_crypt = kzalloc(माप(काष्ठा lib80211_crypt_data),
				    GFP_KERNEL);
		अगर (new_crypt == शून्य)
			वापस -ENOMEM;
		new_crypt->ops = lib80211_get_crypto_ops("WEP");
		अगर (!new_crypt->ops) अणु
			request_module("lib80211_crypt_wep");
			new_crypt->ops = lib80211_get_crypto_ops("WEP");
		पूर्ण

		अगर (new_crypt->ops && try_module_get(new_crypt->ops->owner))
			new_crypt->priv = new_crypt->ops->init(key);

		अगर (!new_crypt->ops || !new_crypt->priv) अणु
			kमुक्त(new_crypt);
			new_crypt = शून्य;

			prपूर्णांकk(KERN_WARNING "%s: could not initialize WEP: "
			       "load module lib80211_crypt_wep\n", dev->name);
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
		LIBIPW_DEBUG_WX("Setting key %d to '%*pE' (%d:%d bytes)\n",
				   key, len, sec.keys[key],
				   erq->length, len);
		sec.key_sizes[key] = len;
		अगर (*crypt)
			(*crypt)->ops->set_key(sec.keys[key], len, शून्य,
					       (*crypt)->priv);
		sec.flags |= (1 << key);
		/* This ensures a key will be activated अगर no key is
		 * explicitly set */
		अगर (key == sec.active_key)
			sec.flags |= SEC_ACTIVE_KEY;

	पूर्ण अन्यथा अणु
		अगर (host_crypto) अणु
			len = (*crypt)->ops->get_key(sec.keys[key], WEP_KEY_LEN,
						     शून्य, (*crypt)->priv);
			अगर (len == 0) अणु
				/* Set a शेष key of all 0 */
				LIBIPW_DEBUG_WX("Setting key %d to all "
						   "zero.\n", key);
				स_रखो(sec.keys[key], 0, 13);
				(*crypt)->ops->set_key(sec.keys[key], 13, शून्य,
						       (*crypt)->priv);
				sec.key_sizes[key] = 13;
				sec.flags |= (1 << key);
			पूर्ण
		पूर्ण
		/* No key data - just set the शेष TX key index */
		अगर (key_provided) अणु
			LIBIPW_DEBUG_WX("Setting key %d to default Tx "
					   "key.\n", key);
			ieee->crypt_info.tx_keyidx = key;
			sec.active_key = key;
			sec.flags |= SEC_ACTIVE_KEY;
		पूर्ण
	पूर्ण
	अगर (erq->flags & (IW_ENCODE_OPEN | IW_ENCODE_RESTRICTED)) अणु
		ieee->खोलो_wep = !(erq->flags & IW_ENCODE_RESTRICTED);
		sec.auth_mode = ieee->खोलो_wep ? WLAN_AUTH_OPEN :
		    WLAN_AUTH_SHARED_KEY;
		sec.flags |= SEC_AUTH_MODE;
		LIBIPW_DEBUG_WX("Auth: %s\n",
				   sec.auth_mode == WLAN_AUTH_OPEN ?
				   "OPEN" : "SHARED KEY");
	पूर्ण

	/* For now we just support WEP, so only set that security level...
	 * TODO: When WPA is added this is one place that needs to change */
	sec.flags |= SEC_LEVEL;
	sec.level = SEC_LEVEL_1;	/* 40 and 104 bit WEP */
	sec.encode_alg[key] = SEC_ALG_WEP;

      करोne:
	अगर (ieee->set_security)
		ieee->set_security(dev, &sec);

	वापस 0;
पूर्ण

पूर्णांक libipw_wx_get_encode(काष्ठा libipw_device *ieee,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *keybuf)
अणु
	काष्ठा iw_poपूर्णांक *erq = &(wrqu->encoding);
	पूर्णांक len, key;
	काष्ठा libipw_security *sec = &ieee->sec;

	LIBIPW_DEBUG_WX("GET_ENCODE\n");

	key = erq->flags & IW_ENCODE_INDEX;
	अगर (key) अणु
		अगर (key > WEP_KEYS)
			वापस -EINVAL;
		key--;
	पूर्ण अन्यथा
		key = ieee->crypt_info.tx_keyidx;

	erq->flags = key + 1;

	अगर (!sec->enabled) अणु
		erq->length = 0;
		erq->flags |= IW_ENCODE_DISABLED;
		वापस 0;
	पूर्ण

	len = sec->key_sizes[key];
	स_नकल(keybuf, sec->keys[key], len);

	erq->length = len;
	erq->flags |= IW_ENCODE_ENABLED;

	अगर (ieee->खोलो_wep)
		erq->flags |= IW_ENCODE_OPEN;
	अन्यथा
		erq->flags |= IW_ENCODE_RESTRICTED;

	वापस 0;
पूर्ण

पूर्णांक libipw_wx_set_encodeext(काष्ठा libipw_device *ieee,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा net_device *dev = ieee->dev;
	काष्ठा iw_poपूर्णांक *encoding = &wrqu->encoding;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
	पूर्णांक i, idx, ret = 0;
	पूर्णांक group_key = 0;
	स्थिर अक्षर *alg, *module;
	काष्ठा lib80211_crypto_ops *ops;
	काष्ठा lib80211_crypt_data **crypt;

	काष्ठा libipw_security sec = अणु
		.flags = 0,
	पूर्ण;

	idx = encoding->flags & IW_ENCODE_INDEX;
	अगर (idx) अणु
		अगर (idx < 1 || idx > WEP_KEYS)
			वापस -EINVAL;
		idx--;
	पूर्ण अन्यथा
		idx = ieee->crypt_info.tx_keyidx;

	अगर (ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY) अणु
		crypt = &ieee->crypt_info.crypt[idx];
		group_key = 1;
	पूर्ण अन्यथा अणु
		/* some Cisco APs use idx>0 क्रम unicast in dynamic WEP */
		अगर (idx != 0 && ext->alg != IW_ENCODE_ALG_WEP)
			वापस -EINVAL;
		अगर (ieee->iw_mode == IW_MODE_INFRA)
			crypt = &ieee->crypt_info.crypt[idx];
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	sec.flags |= SEC_ENABLED | SEC_ENCRYPT;
	अगर ((encoding->flags & IW_ENCODE_DISABLED) ||
	    ext->alg == IW_ENCODE_ALG_NONE) अणु
		अगर (*crypt)
			lib80211_crypt_delayed_deinit(&ieee->crypt_info, crypt);

		क्रम (i = 0; i < WEP_KEYS; i++)
			अगर (ieee->crypt_info.crypt[i] != शून्य)
				अवरोध;

		अगर (i == WEP_KEYS) अणु
			sec.enabled = 0;
			sec.encrypt = 0;
			sec.level = SEC_LEVEL_0;
			sec.flags |= SEC_LEVEL;
		पूर्ण
		जाओ करोne;
	पूर्ण

	sec.enabled = 1;
	sec.encrypt = 1;

	अगर (group_key ? !ieee->host_mc_decrypt :
	    !(ieee->host_encrypt || ieee->host_decrypt ||
	      ieee->host_encrypt_msdu))
		जाओ skip_host_crypt;

	चयन (ext->alg) अणु
	हाल IW_ENCODE_ALG_WEP:
		alg = "WEP";
		module = "lib80211_crypt_wep";
		अवरोध;
	हाल IW_ENCODE_ALG_TKIP:
		alg = "TKIP";
		module = "lib80211_crypt_tkip";
		अवरोध;
	हाल IW_ENCODE_ALG_CCMP:
		alg = "CCMP";
		module = "lib80211_crypt_ccmp";
		अवरोध;
	शेष:
		LIBIPW_DEBUG_WX("%s: unknown crypto alg %d\n",
				   dev->name, ext->alg);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	ops = lib80211_get_crypto_ops(alg);
	अगर (ops == शून्य) अणु
		request_module(module);
		ops = lib80211_get_crypto_ops(alg);
	पूर्ण
	अगर (ops == शून्य) अणु
		LIBIPW_DEBUG_WX("%s: unknown crypto alg %d\n",
				   dev->name, ext->alg);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (*crypt == शून्य || (*crypt)->ops != ops) अणु
		काष्ठा lib80211_crypt_data *new_crypt;

		lib80211_crypt_delayed_deinit(&ieee->crypt_info, crypt);

		new_crypt = kzalloc(माप(*new_crypt), GFP_KERNEL);
		अगर (new_crypt == शून्य) अणु
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण
		new_crypt->ops = ops;
		अगर (new_crypt->ops && try_module_get(new_crypt->ops->owner))
			new_crypt->priv = new_crypt->ops->init(idx);
		अगर (new_crypt->priv == शून्य) अणु
			kमुक्त(new_crypt);
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
		*crypt = new_crypt;
	पूर्ण

	अगर (ext->key_len > 0 && (*crypt)->ops->set_key &&
	    (*crypt)->ops->set_key(ext->key, ext->key_len, ext->rx_seq,
				   (*crypt)->priv) < 0) अणु
		LIBIPW_DEBUG_WX("%s: key setting failed\n", dev->name);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

      skip_host_crypt:
	अगर (ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY) अणु
		ieee->crypt_info.tx_keyidx = idx;
		sec.active_key = idx;
		sec.flags |= SEC_ACTIVE_KEY;
	पूर्ण

	अगर (ext->alg != IW_ENCODE_ALG_NONE) अणु
		पूर्णांक key_len = clamp_val(ext->key_len, 0, SCM_KEY_LEN);

		स_नकल(sec.keys[idx], ext->key, key_len);
		sec.key_sizes[idx] = key_len;
		sec.flags |= (1 << idx);
		अगर (ext->alg == IW_ENCODE_ALG_WEP) अणु
			sec.encode_alg[idx] = SEC_ALG_WEP;
			sec.flags |= SEC_LEVEL;
			sec.level = SEC_LEVEL_1;
		पूर्ण अन्यथा अगर (ext->alg == IW_ENCODE_ALG_TKIP) अणु
			sec.encode_alg[idx] = SEC_ALG_TKIP;
			sec.flags |= SEC_LEVEL;
			sec.level = SEC_LEVEL_2;
		पूर्ण अन्यथा अगर (ext->alg == IW_ENCODE_ALG_CCMP) अणु
			sec.encode_alg[idx] = SEC_ALG_CCMP;
			sec.flags |= SEC_LEVEL;
			sec.level = SEC_LEVEL_3;
		पूर्ण
		/* Don't set sec level क्रम group keys. */
		अगर (group_key)
			sec.flags &= ~SEC_LEVEL;
	पूर्ण
      करोne:
	अगर (ieee->set_security)
		ieee->set_security(dev, &sec);

	वापस ret;
पूर्ण

पूर्णांक libipw_wx_get_encodeext(काष्ठा libipw_device *ieee,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा iw_poपूर्णांक *encoding = &wrqu->encoding;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
	काष्ठा libipw_security *sec = &ieee->sec;
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
		idx = ieee->crypt_info.tx_keyidx;

	अगर (!(ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY) &&
	    ext->alg != IW_ENCODE_ALG_WEP)
		अगर (idx != 0 || ieee->iw_mode != IW_MODE_INFRA)
			वापस -EINVAL;

	encoding->flags = idx + 1;
	स_रखो(ext, 0, माप(*ext));

	अगर (!sec->enabled) अणु
		ext->alg = IW_ENCODE_ALG_NONE;
		ext->key_len = 0;
		encoding->flags |= IW_ENCODE_DISABLED;
	पूर्ण अन्यथा अणु
		अगर (sec->encode_alg[idx] == SEC_ALG_WEP)
			ext->alg = IW_ENCODE_ALG_WEP;
		अन्यथा अगर (sec->encode_alg[idx] == SEC_ALG_TKIP)
			ext->alg = IW_ENCODE_ALG_TKIP;
		अन्यथा अगर (sec->encode_alg[idx] == SEC_ALG_CCMP)
			ext->alg = IW_ENCODE_ALG_CCMP;
		अन्यथा
			वापस -EINVAL;

		ext->key_len = sec->key_sizes[idx];
		स_नकल(ext->key, sec->keys[idx], ext->key_len);
		encoding->flags |= IW_ENCODE_ENABLED;
		अगर (ext->key_len &&
		    (ext->alg == IW_ENCODE_ALG_TKIP ||
		     ext->alg == IW_ENCODE_ALG_CCMP))
			ext->ext_flags |= IW_ENCODE_EXT_TX_SEQ_VALID;

	पूर्ण

	वापस 0;
पूर्ण

EXPORT_SYMBOL(libipw_wx_set_encodeext);
EXPORT_SYMBOL(libipw_wx_get_encodeext);

EXPORT_SYMBOL(libipw_wx_get_scan);
EXPORT_SYMBOL(libipw_wx_set_encode);
EXPORT_SYMBOL(libipw_wx_get_encode);
