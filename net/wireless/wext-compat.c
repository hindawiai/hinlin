<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cfg80211 - wext compat code
 *
 * This is temporary code until all wireless functionality is migrated
 * पूर्णांकo cfg80211, when that happens all the exports here go away and
 * we directly assign the wireless handlers of wireless पूर्णांकerfaces.
 *
 * Copyright 2008-2009	Johannes Berg <johannes@sipsolutions.net>
 * Copyright (C) 2019-2021 Intel Corporation
 */

#समावेश <linux/export.h>
#समावेश <linux/wireless.h>
#समावेश <linux/nl80211.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/slab.h>
#समावेश <net/iw_handler.h>
#समावेश <net/cfg80211.h>
#समावेश <net/cfg80211-wext.h>
#समावेश "wext-compat.h"
#समावेश "core.h"
#समावेश "rdev-ops.h"

पूर्णांक cfg80211_wext_giwname(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  अक्षर *name, अक्षर *extra)
अणु
	म_नकल(name, "IEEE 802.11");
	वापस 0;
पूर्ण
EXPORT_WEXT_HANDLER(cfg80211_wext_giwname);

पूर्णांक cfg80211_wext_siwmode(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			  u32 *mode, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा vअगर_params vअगरparams;
	क्रमागत nl80211_अगरtype type;
	पूर्णांक ret;

	rdev = wiphy_to_rdev(wdev->wiphy);

	चयन (*mode) अणु
	हाल IW_MODE_INFRA:
		type = NL80211_IFTYPE_STATION;
		अवरोध;
	हाल IW_MODE_ADHOC:
		type = NL80211_IFTYPE_ADHOC;
		अवरोध;
	हाल IW_MODE_MONITOR:
		type = NL80211_IFTYPE_MONITOR;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (type == wdev->अगरtype)
		वापस 0;

	स_रखो(&vअगरparams, 0, माप(vअगरparams));

	wiphy_lock(wdev->wiphy);
	ret = cfg80211_change_अगरace(rdev, dev, type, &vअगरparams);
	wiphy_unlock(wdev->wiphy);

	वापस ret;
पूर्ण
EXPORT_WEXT_HANDLER(cfg80211_wext_siwmode);

पूर्णांक cfg80211_wext_giwmode(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			  u32 *mode, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

	अगर (!wdev)
		वापस -EOPNOTSUPP;

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
		*mode = IW_MODE_MASTER;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		*mode = IW_MODE_INFRA;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		*mode = IW_MODE_ADHOC;
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		*mode = IW_MODE_MONITOR;
		अवरोध;
	हाल NL80211_IFTYPE_WDS:
		*mode = IW_MODE_REPEAT;
		अवरोध;
	हाल NL80211_IFTYPE_AP_VLAN:
		*mode = IW_MODE_SECOND;		/* FIXME */
		अवरोध;
	शेष:
		*mode = IW_MODE_AUTO;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_WEXT_HANDLER(cfg80211_wext_giwmode);


पूर्णांक cfg80211_wext_giwrange(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा iw_range *range = (काष्ठा iw_range *) extra;
	क्रमागत nl80211_band band;
	पूर्णांक i, c = 0;

	अगर (!wdev)
		वापस -EOPNOTSUPP;

	data->length = माप(काष्ठा iw_range);
	स_रखो(range, 0, माप(काष्ठा iw_range));

	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 21;
	range->retry_capa = IW_RETRY_LIMIT;
	range->retry_flags = IW_RETRY_LIMIT;
	range->min_retry = 0;
	range->max_retry = 255;
	range->min_rts = 0;
	range->max_rts = 2347;
	range->min_frag = 256;
	range->max_frag = 2346;

	range->max_encoding_tokens = 4;

	range->max_qual.updated = IW_QUAL_NOISE_INVALID;

	चयन (wdev->wiphy->संकेत_type) अणु
	हाल CFG80211_SIGNAL_TYPE_NONE:
		अवरोध;
	हाल CFG80211_SIGNAL_TYPE_MBM:
		range->max_qual.level = (u8)-110;
		range->max_qual.qual = 70;
		range->avg_qual.qual = 35;
		range->max_qual.updated |= IW_QUAL_DBM;
		range->max_qual.updated |= IW_QUAL_QUAL_UPDATED;
		range->max_qual.updated |= IW_QUAL_LEVEL_UPDATED;
		अवरोध;
	हाल CFG80211_SIGNAL_TYPE_UNSPEC:
		range->max_qual.level = 100;
		range->max_qual.qual = 100;
		range->avg_qual.qual = 50;
		range->max_qual.updated |= IW_QUAL_QUAL_UPDATED;
		range->max_qual.updated |= IW_QUAL_LEVEL_UPDATED;
		अवरोध;
	पूर्ण

	range->avg_qual.level = range->max_qual.level / 2;
	range->avg_qual.noise = range->max_qual.noise / 2;
	range->avg_qual.updated = range->max_qual.updated;

	क्रम (i = 0; i < wdev->wiphy->n_cipher_suites; i++) अणु
		चयन (wdev->wiphy->cipher_suites[i]) अणु
		हाल WLAN_CIPHER_SUITE_TKIP:
			range->enc_capa |= (IW_ENC_CAPA_CIPHER_TKIP |
					    IW_ENC_CAPA_WPA);
			अवरोध;

		हाल WLAN_CIPHER_SUITE_CCMP:
			range->enc_capa |= (IW_ENC_CAPA_CIPHER_CCMP |
					    IW_ENC_CAPA_WPA2);
			अवरोध;

		हाल WLAN_CIPHER_SUITE_WEP40:
			range->encoding_size[range->num_encoding_sizes++] =
				WLAN_KEY_LEN_WEP40;
			अवरोध;

		हाल WLAN_CIPHER_SUITE_WEP104:
			range->encoding_size[range->num_encoding_sizes++] =
				WLAN_KEY_LEN_WEP104;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (band = 0; band < NUM_NL80211_BANDS; band ++) अणु
		काष्ठा ieee80211_supported_band *sband;

		sband = wdev->wiphy->bands[band];

		अगर (!sband)
			जारी;

		क्रम (i = 0; i < sband->n_channels && c < IW_MAX_FREQUENCIES; i++) अणु
			काष्ठा ieee80211_channel *chan = &sband->channels[i];

			अगर (!(chan->flags & IEEE80211_CHAN_DISABLED)) अणु
				range->freq[c].i =
					ieee80211_frequency_to_channel(
						chan->center_freq);
				range->freq[c].m = chan->center_freq;
				range->freq[c].e = 6;
				c++;
			पूर्ण
		पूर्ण
	पूर्ण
	range->num_channels = c;
	range->num_frequency = c;

	IW_EVENT_CAPA_SET_KERNEL(range->event_capa);
	IW_EVENT_CAPA_SET(range->event_capa, SIOCGIWAP);
	IW_EVENT_CAPA_SET(range->event_capa, SIOCGIWSCAN);

	अगर (wdev->wiphy->max_scan_ssids > 0)
		range->scan_capa |= IW_SCAN_CAPA_ESSID;

	वापस 0;
पूर्ण
EXPORT_WEXT_HANDLER(cfg80211_wext_giwrange);


/**
 * cfg80211_wext_freq - get wext frequency क्रम non-"auto"
 * @freq: the wext freq encoding
 *
 * Returns a frequency, or a negative error code, or 0 क्रम स्वतः.
 */
पूर्णांक cfg80211_wext_freq(काष्ठा iw_freq *freq)
अणु
	/*
	 * Parse frequency - वापस 0 क्रम स्वतः and
	 * -EINVAL क्रम impossible things.
	 */
	अगर (freq->e == 0) अणु
		क्रमागत nl80211_band band = NL80211_BAND_2GHZ;
		अगर (freq->m < 0)
			वापस 0;
		अगर (freq->m > 14)
			band = NL80211_BAND_5GHZ;
		वापस ieee80211_channel_to_frequency(freq->m, band);
	पूर्ण अन्यथा अणु
		पूर्णांक i, भाग = 1000000;
		क्रम (i = 0; i < freq->e; i++)
			भाग /= 10;
		अगर (भाग <= 0)
			वापस -EINVAL;
		वापस freq->m / भाग;
	पूर्ण
पूर्ण

पूर्णांक cfg80211_wext_siwrts(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_param *rts, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	u32 orts = wdev->wiphy->rts_threshold;
	पूर्णांक err;

	wiphy_lock(&rdev->wiphy);
	अगर (rts->disabled || !rts->fixed) अणु
		wdev->wiphy->rts_threshold = (u32) -1;
	पूर्ण अन्यथा अगर (rts->value < 0) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण अन्यथा अणु
		wdev->wiphy->rts_threshold = rts->value;
	पूर्ण

	err = rdev_set_wiphy_params(rdev, WIPHY_PARAM_RTS_THRESHOLD);

	अगर (err)
		wdev->wiphy->rts_threshold = orts;

out:
	wiphy_unlock(&rdev->wiphy);
	वापस err;
पूर्ण
EXPORT_WEXT_HANDLER(cfg80211_wext_siwrts);

पूर्णांक cfg80211_wext_giwrts(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_param *rts, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

	rts->value = wdev->wiphy->rts_threshold;
	rts->disabled = rts->value == (u32) -1;
	rts->fixed = 1;

	वापस 0;
पूर्ण
EXPORT_WEXT_HANDLER(cfg80211_wext_giwrts);

पूर्णांक cfg80211_wext_siwfrag(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_param *frag, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	u32 ofrag = wdev->wiphy->frag_threshold;
	पूर्णांक err;

	wiphy_lock(&rdev->wiphy);
	अगर (frag->disabled || !frag->fixed) अणु
		wdev->wiphy->frag_threshold = (u32) -1;
	पूर्ण अन्यथा अगर (frag->value < 256) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण अन्यथा अणु
		/* Fragment length must be even, so strip LSB. */
		wdev->wiphy->frag_threshold = frag->value & ~0x1;
	पूर्ण

	err = rdev_set_wiphy_params(rdev, WIPHY_PARAM_FRAG_THRESHOLD);
	अगर (err)
		wdev->wiphy->frag_threshold = ofrag;
out:
	wiphy_unlock(&rdev->wiphy);

	वापस err;
पूर्ण
EXPORT_WEXT_HANDLER(cfg80211_wext_siwfrag);

पूर्णांक cfg80211_wext_giwfrag(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_param *frag, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

	frag->value = wdev->wiphy->frag_threshold;
	frag->disabled = frag->value == (u32) -1;
	frag->fixed = 1;

	वापस 0;
पूर्ण
EXPORT_WEXT_HANDLER(cfg80211_wext_giwfrag);

अटल पूर्णांक cfg80211_wext_siwretry(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  काष्ठा iw_param *retry, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	u32 changed = 0;
	u8 oदीर्घ = wdev->wiphy->retry_दीर्घ;
	u8 oलघु = wdev->wiphy->retry_लघु;
	पूर्णांक err;

	अगर (retry->disabled || retry->value < 1 || retry->value > 255 ||
	    (retry->flags & IW_RETRY_TYPE) != IW_RETRY_LIMIT)
		वापस -EINVAL;

	wiphy_lock(&rdev->wiphy);
	अगर (retry->flags & IW_RETRY_LONG) अणु
		wdev->wiphy->retry_दीर्घ = retry->value;
		changed |= WIPHY_PARAM_RETRY_LONG;
	पूर्ण अन्यथा अगर (retry->flags & IW_RETRY_SHORT) अणु
		wdev->wiphy->retry_लघु = retry->value;
		changed |= WIPHY_PARAM_RETRY_SHORT;
	पूर्ण अन्यथा अणु
		wdev->wiphy->retry_लघु = retry->value;
		wdev->wiphy->retry_दीर्घ = retry->value;
		changed |= WIPHY_PARAM_RETRY_LONG;
		changed |= WIPHY_PARAM_RETRY_SHORT;
	पूर्ण

	err = rdev_set_wiphy_params(rdev, changed);
	अगर (err) अणु
		wdev->wiphy->retry_लघु = oलघु;
		wdev->wiphy->retry_दीर्घ = oदीर्घ;
	पूर्ण
	wiphy_unlock(&rdev->wiphy);

	वापस err;
पूर्ण

पूर्णांक cfg80211_wext_giwretry(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_param *retry, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

	retry->disabled = 0;

	अगर (retry->flags == 0 || (retry->flags & IW_RETRY_SHORT)) अणु
		/*
		 * First वापस लघु value, iwconfig will ask दीर्घ value
		 * later अगर needed
		 */
		retry->flags |= IW_RETRY_LIMIT | IW_RETRY_SHORT;
		retry->value = wdev->wiphy->retry_लघु;
		अगर (wdev->wiphy->retry_दीर्घ == wdev->wiphy->retry_लघु)
			retry->flags |= IW_RETRY_LONG;

		वापस 0;
	पूर्ण

	अगर (retry->flags & IW_RETRY_LONG) अणु
		retry->flags = IW_RETRY_LIMIT | IW_RETRY_LONG;
		retry->value = wdev->wiphy->retry_दीर्घ;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_WEXT_HANDLER(cfg80211_wext_giwretry);

अटल पूर्णांक __cfg80211_set_encryption(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     काष्ठा net_device *dev, bool pairwise,
				     स्थिर u8 *addr, bool हटाओ, bool tx_key,
				     पूर्णांक idx, काष्ठा key_params *params)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err, i;
	bool rejoin = false;

	अगर (pairwise && !addr)
		वापस -EINVAL;

	/*
	 * In many हालs we won't actually need this, but it's better
	 * to करो it first in हाल the allocation fails. Don't use wext.
	 */
	अगर (!wdev->wext.keys) अणु
		wdev->wext.keys = kzalloc(माप(*wdev->wext.keys),
					  GFP_KERNEL);
		अगर (!wdev->wext.keys)
			वापस -ENOMEM;
		क्रम (i = 0; i < CFG80211_MAX_WEP_KEYS; i++)
			wdev->wext.keys->params[i].key =
				wdev->wext.keys->data[i];
	पूर्ण

	अगर (wdev->अगरtype != NL80211_IFTYPE_ADHOC &&
	    wdev->अगरtype != NL80211_IFTYPE_STATION)
		वापस -EOPNOTSUPP;

	अगर (params->cipher == WLAN_CIPHER_SUITE_AES_CMAC) अणु
		अगर (!wdev->current_bss)
			वापस -ENOLINK;

		अगर (!rdev->ops->set_शेष_mgmt_key)
			वापस -EOPNOTSUPP;

		अगर (idx < 4 || idx > 5)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (idx < 0 || idx > 3)
		वापस -EINVAL;

	अगर (हटाओ) अणु
		err = 0;
		अगर (wdev->current_bss) अणु
			/*
			 * If removing the current TX key, we will need to
			 * join a new IBSS without the privacy bit clear.
			 */
			अगर (idx == wdev->wext.शेष_key &&
			    wdev->अगरtype == NL80211_IFTYPE_ADHOC) अणु
				__cfg80211_leave_ibss(rdev, wdev->netdev, true);
				rejoin = true;
			पूर्ण

			अगर (!pairwise && addr &&
			    !(rdev->wiphy.flags & WIPHY_FLAG_IBSS_RSN))
				err = -ENOENT;
			अन्यथा
				err = rdev_del_key(rdev, dev, idx, pairwise,
						   addr);
		पूर्ण
		wdev->wext.connect.privacy = false;
		/*
		 * Applications using wireless extensions expect to be
		 * able to delete keys that करोn't exist, so allow that.
		 */
		अगर (err == -ENOENT)
			err = 0;
		अगर (!err) अणु
			अगर (!addr && idx < 4) अणु
				स_रखो(wdev->wext.keys->data[idx], 0,
				       माप(wdev->wext.keys->data[idx]));
				wdev->wext.keys->params[idx].key_len = 0;
				wdev->wext.keys->params[idx].cipher = 0;
			पूर्ण
			अगर (idx == wdev->wext.शेष_key)
				wdev->wext.शेष_key = -1;
			अन्यथा अगर (idx == wdev->wext.शेष_mgmt_key)
				wdev->wext.शेष_mgmt_key = -1;
		पूर्ण

		अगर (!err && rejoin)
			err = cfg80211_ibss_wext_join(rdev, wdev);

		वापस err;
	पूर्ण

	अगर (addr)
		tx_key = false;

	अगर (cfg80211_validate_key_settings(rdev, params, idx, pairwise, addr))
		वापस -EINVAL;

	err = 0;
	अगर (wdev->current_bss)
		err = rdev_add_key(rdev, dev, idx, pairwise, addr, params);
	अन्यथा अगर (params->cipher != WLAN_CIPHER_SUITE_WEP40 &&
		 params->cipher != WLAN_CIPHER_SUITE_WEP104)
		वापस -EINVAL;
	अगर (err)
		वापस err;

	/*
	 * We only need to store WEP keys, since they're the only keys that
	 * can be set beक्रमe a connection is established and persist after
	 * disconnecting.
	 */
	अगर (!addr && (params->cipher == WLAN_CIPHER_SUITE_WEP40 ||
		      params->cipher == WLAN_CIPHER_SUITE_WEP104)) अणु
		wdev->wext.keys->params[idx] = *params;
		स_नकल(wdev->wext.keys->data[idx],
			params->key, params->key_len);
		wdev->wext.keys->params[idx].key =
			wdev->wext.keys->data[idx];
	पूर्ण

	अगर ((params->cipher == WLAN_CIPHER_SUITE_WEP40 ||
	     params->cipher == WLAN_CIPHER_SUITE_WEP104) &&
	    (tx_key || (!addr && wdev->wext.शेष_key == -1))) अणु
		अगर (wdev->current_bss) अणु
			/*
			 * If we are getting a new TX key from not having
			 * had one beक्रमe we need to join a new IBSS with
			 * the privacy bit set.
			 */
			अगर (wdev->अगरtype == NL80211_IFTYPE_ADHOC &&
			    wdev->wext.शेष_key == -1) अणु
				__cfg80211_leave_ibss(rdev, wdev->netdev, true);
				rejoin = true;
			पूर्ण
			err = rdev_set_शेष_key(rdev, dev, idx, true, true);
		पूर्ण
		अगर (!err) अणु
			wdev->wext.शेष_key = idx;
			अगर (rejoin)
				err = cfg80211_ibss_wext_join(rdev, wdev);
		पूर्ण
		वापस err;
	पूर्ण

	अगर (params->cipher == WLAN_CIPHER_SUITE_AES_CMAC &&
	    (tx_key || (!addr && wdev->wext.शेष_mgmt_key == -1))) अणु
		अगर (wdev->current_bss)
			err = rdev_set_शेष_mgmt_key(rdev, dev, idx);
		अगर (!err)
			wdev->wext.शेष_mgmt_key = idx;
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_set_encryption(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा net_device *dev, bool pairwise,
				   स्थिर u8 *addr, bool हटाओ, bool tx_key,
				   पूर्णांक idx, काष्ठा key_params *params)
अणु
	पूर्णांक err;

	wdev_lock(dev->ieee80211_ptr);
	err = __cfg80211_set_encryption(rdev, dev, pairwise, addr,
					हटाओ, tx_key, idx, params);
	wdev_unlock(dev->ieee80211_ptr);

	वापस err;
पूर्ण

अटल पूर्णांक cfg80211_wext_siwencode(काष्ठा net_device *dev,
				   काष्ठा iw_request_info *info,
				   काष्ठा iw_poपूर्णांक *erq, अक्षर *keybuf)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	पूर्णांक idx, err;
	bool हटाओ = false;
	काष्ठा key_params params;

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION &&
	    wdev->अगरtype != NL80211_IFTYPE_ADHOC)
		वापस -EOPNOTSUPP;

	/* no use -- only MFP (set_शेष_mgmt_key) is optional */
	अगर (!rdev->ops->del_key ||
	    !rdev->ops->add_key ||
	    !rdev->ops->set_शेष_key)
		वापस -EOPNOTSUPP;

	wiphy_lock(&rdev->wiphy);
	idx = erq->flags & IW_ENCODE_INDEX;
	अगर (idx == 0) अणु
		idx = wdev->wext.शेष_key;
		अगर (idx < 0)
			idx = 0;
	पूर्ण अन्यथा अगर (idx < 1 || idx > 4) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण अन्यथा अणु
		idx--;
	पूर्ण

	अगर (erq->flags & IW_ENCODE_DISABLED)
		हटाओ = true;
	अन्यथा अगर (erq->length == 0) अणु
		/* No key data - just set the शेष TX key index */
		err = 0;
		wdev_lock(wdev);
		अगर (wdev->current_bss)
			err = rdev_set_शेष_key(rdev, dev, idx, true,
						   true);
		अगर (!err)
			wdev->wext.शेष_key = idx;
		wdev_unlock(wdev);
		जाओ out;
	पूर्ण

	स_रखो(&params, 0, माप(params));
	params.key = keybuf;
	params.key_len = erq->length;
	अगर (erq->length == 5) अणु
		params.cipher = WLAN_CIPHER_SUITE_WEP40;
	पूर्ण अन्यथा अगर (erq->length == 13) अणु
		params.cipher = WLAN_CIPHER_SUITE_WEP104;
	पूर्ण अन्यथा अगर (!हटाओ) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	err = cfg80211_set_encryption(rdev, dev, false, शून्य, हटाओ,
				      wdev->wext.शेष_key == -1,
				      idx, &params);
out:
	wiphy_unlock(&rdev->wiphy);

	वापस err;
पूर्ण

अटल पूर्णांक cfg80211_wext_siwencodeext(काष्ठा net_device *dev,
				      काष्ठा iw_request_info *info,
				      काष्ठा iw_poपूर्णांक *erq, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *) extra;
	स्थिर u8 *addr;
	पूर्णांक idx;
	bool हटाओ = false;
	काष्ठा key_params params;
	u32 cipher;
	पूर्णांक ret;

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION &&
	    wdev->अगरtype != NL80211_IFTYPE_ADHOC)
		वापस -EOPNOTSUPP;

	/* no use -- only MFP (set_शेष_mgmt_key) is optional */
	अगर (!rdev->ops->del_key ||
	    !rdev->ops->add_key ||
	    !rdev->ops->set_शेष_key)
		वापस -EOPNOTSUPP;

	चयन (ext->alg) अणु
	हाल IW_ENCODE_ALG_NONE:
		हटाओ = true;
		cipher = 0;
		अवरोध;
	हाल IW_ENCODE_ALG_WEP:
		अगर (ext->key_len == 5)
			cipher = WLAN_CIPHER_SUITE_WEP40;
		अन्यथा अगर (ext->key_len == 13)
			cipher = WLAN_CIPHER_SUITE_WEP104;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल IW_ENCODE_ALG_TKIP:
		cipher = WLAN_CIPHER_SUITE_TKIP;
		अवरोध;
	हाल IW_ENCODE_ALG_CCMP:
		cipher = WLAN_CIPHER_SUITE_CCMP;
		अवरोध;
	हाल IW_ENCODE_ALG_AES_CMAC:
		cipher = WLAN_CIPHER_SUITE_AES_CMAC;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (erq->flags & IW_ENCODE_DISABLED)
		हटाओ = true;

	idx = erq->flags & IW_ENCODE_INDEX;
	अगर (cipher == WLAN_CIPHER_SUITE_AES_CMAC) अणु
		अगर (idx < 4 || idx > 5) अणु
			idx = wdev->wext.शेष_mgmt_key;
			अगर (idx < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा
			idx--;
	पूर्ण अन्यथा अणु
		अगर (idx < 1 || idx > 4) अणु
			idx = wdev->wext.शेष_key;
			अगर (idx < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा
			idx--;
	पूर्ण

	addr = ext->addr.sa_data;
	अगर (is_broadcast_ether_addr(addr))
		addr = शून्य;

	स_रखो(&params, 0, माप(params));
	params.key = ext->key;
	params.key_len = ext->key_len;
	params.cipher = cipher;

	अगर (ext->ext_flags & IW_ENCODE_EXT_RX_SEQ_VALID) अणु
		params.seq = ext->rx_seq;
		params.seq_len = 6;
	पूर्ण

	wiphy_lock(wdev->wiphy);
	ret = cfg80211_set_encryption(
			rdev, dev,
			!(ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY),
			addr, हटाओ,
			ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY,
			idx, &params);
	wiphy_unlock(wdev->wiphy);

	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_wext_giwencode(काष्ठा net_device *dev,
				   काष्ठा iw_request_info *info,
				   काष्ठा iw_poपूर्णांक *erq, अक्षर *keybuf)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक idx;

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION &&
	    wdev->अगरtype != NL80211_IFTYPE_ADHOC)
		वापस -EOPNOTSUPP;

	idx = erq->flags & IW_ENCODE_INDEX;
	अगर (idx == 0) अणु
		idx = wdev->wext.शेष_key;
		अगर (idx < 0)
			idx = 0;
	पूर्ण अन्यथा अगर (idx < 1 || idx > 4)
		वापस -EINVAL;
	अन्यथा
		idx--;

	erq->flags = idx + 1;

	अगर (!wdev->wext.keys || !wdev->wext.keys->params[idx].cipher) अणु
		erq->flags |= IW_ENCODE_DISABLED;
		erq->length = 0;
		वापस 0;
	पूर्ण

	erq->length = min_t(माप_प्रकार, erq->length,
			    wdev->wext.keys->params[idx].key_len);
	स_नकल(keybuf, wdev->wext.keys->params[idx].key, erq->length);
	erq->flags |= IW_ENCODE_ENABLED;

	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_wext_siwfreq(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_freq *wextfreq, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_chan_def chandef = अणु
		.width = NL80211_CHAN_WIDTH_20_NOHT,
	पूर्ण;
	पूर्णांक freq, ret;

	wiphy_lock(&rdev->wiphy);

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_STATION:
		ret = cfg80211_mgd_wext_siwfreq(dev, info, wextfreq, extra);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		ret = cfg80211_ibss_wext_siwfreq(dev, info, wextfreq, extra);
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		freq = cfg80211_wext_freq(wextfreq);
		अगर (freq < 0) अणु
			ret = freq;
			अवरोध;
		पूर्ण
		अगर (freq == 0) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		chandef.center_freq1 = freq;
		chandef.chan = ieee80211_get_channel(&rdev->wiphy, freq);
		अगर (!chandef.chan) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = cfg80211_set_monitor_channel(rdev, &chandef);
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		freq = cfg80211_wext_freq(wextfreq);
		अगर (freq < 0) अणु
			ret = freq;
			अवरोध;
		पूर्ण
		अगर (freq == 0) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		chandef.center_freq1 = freq;
		chandef.chan = ieee80211_get_channel(&rdev->wiphy, freq);
		अगर (!chandef.chan) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = cfg80211_set_mesh_channel(rdev, wdev, &chandef);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	wiphy_unlock(&rdev->wiphy);

	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_wext_giwfreq(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_freq *freq, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_chan_def chandef = अणुपूर्ण;
	पूर्णांक ret;

	wiphy_lock(&rdev->wiphy);
	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_STATION:
		ret = cfg80211_mgd_wext_giwfreq(dev, info, freq, extra);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		ret = cfg80211_ibss_wext_giwfreq(dev, info, freq, extra);
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		अगर (!rdev->ops->get_channel) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ret = rdev_get_channel(rdev, wdev, &chandef);
		अगर (ret)
			अवरोध;
		freq->m = chandef.chan->center_freq;
		freq->e = 6;
		ret = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	wiphy_unlock(&rdev->wiphy);

	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_wext_siwtxघातer(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *info,
				    जोड़ iwreq_data *data, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	क्रमागत nl80211_tx_घातer_setting type;
	पूर्णांक dbm = 0;
	पूर्णांक ret;

	अगर ((data->txघातer.flags & IW_TXPOW_TYPE) != IW_TXPOW_DBM)
		वापस -EINVAL;
	अगर (data->txघातer.flags & IW_TXPOW_RANGE)
		वापस -EINVAL;

	अगर (!rdev->ops->set_tx_घातer)
		वापस -EOPNOTSUPP;

	/* only change when not disabling */
	अगर (!data->txघातer.disabled) अणु
		rfसमाप्त_set_sw_state(rdev->rfसमाप्त, false);

		अगर (data->txघातer.fixed) अणु
			/*
			 * wext करोesn't support negative values, see
			 * below where it's क्रम स्वतःmatic
			 */
			अगर (data->txघातer.value < 0)
				वापस -EINVAL;
			dbm = data->txघातer.value;
			type = NL80211_TX_POWER_FIXED;
			/* TODO: करो regulatory check! */
		पूर्ण अन्यथा अणु
			/*
			 * Automatic घातer level setting, max being the value
			 * passed in from userland.
			 */
			अगर (data->txघातer.value < 0) अणु
				type = NL80211_TX_POWER_AUTOMATIC;
			पूर्ण अन्यथा अणु
				dbm = data->txघातer.value;
				type = NL80211_TX_POWER_LIMITED;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rfसमाप्त_set_sw_state(rdev->rfसमाप्त, true))
			schedule_work(&rdev->rfसमाप्त_block);
		वापस 0;
	पूर्ण

	wiphy_lock(&rdev->wiphy);
	ret = rdev_set_tx_घातer(rdev, wdev, type, DBM_TO_MBM(dbm));
	wiphy_unlock(&rdev->wiphy);

	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_wext_giwtxघातer(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *info,
				    जोड़ iwreq_data *data, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	पूर्णांक err, val;

	अगर ((data->txघातer.flags & IW_TXPOW_TYPE) != IW_TXPOW_DBM)
		वापस -EINVAL;
	अगर (data->txघातer.flags & IW_TXPOW_RANGE)
		वापस -EINVAL;

	अगर (!rdev->ops->get_tx_घातer)
		वापस -EOPNOTSUPP;

	wiphy_lock(&rdev->wiphy);
	err = rdev_get_tx_घातer(rdev, wdev, &val);
	wiphy_unlock(&rdev->wiphy);
	अगर (err)
		वापस err;

	/* well... oh well */
	data->txघातer.fixed = 1;
	data->txघातer.disabled = rfसमाप्त_blocked(rdev->rfसमाप्त);
	data->txघातer.value = val;
	data->txघातer.flags = IW_TXPOW_DBM;

	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_set_auth_alg(काष्ठा wireless_dev *wdev,
				 s32 auth_alg)
अणु
	पूर्णांक nr_alg = 0;

	अगर (!auth_alg)
		वापस -EINVAL;

	अगर (auth_alg & ~(IW_AUTH_ALG_OPEN_SYSTEM |
			 IW_AUTH_ALG_SHARED_KEY |
			 IW_AUTH_ALG_LEAP))
		वापस -EINVAL;

	अगर (auth_alg & IW_AUTH_ALG_OPEN_SYSTEM) अणु
		nr_alg++;
		wdev->wext.connect.auth_type = NL80211_AUTHTYPE_OPEN_SYSTEM;
	पूर्ण

	अगर (auth_alg & IW_AUTH_ALG_SHARED_KEY) अणु
		nr_alg++;
		wdev->wext.connect.auth_type = NL80211_AUTHTYPE_SHARED_KEY;
	पूर्ण

	अगर (auth_alg & IW_AUTH_ALG_LEAP) अणु
		nr_alg++;
		wdev->wext.connect.auth_type = NL80211_AUTHTYPE_NETWORK_EAP;
	पूर्ण

	अगर (nr_alg > 1)
		wdev->wext.connect.auth_type = NL80211_AUTHTYPE_AUTOMATIC;

	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_set_wpa_version(काष्ठा wireless_dev *wdev, u32 wpa_versions)
अणु
	अगर (wpa_versions & ~(IW_AUTH_WPA_VERSION_WPA |
			     IW_AUTH_WPA_VERSION_WPA2|
		             IW_AUTH_WPA_VERSION_DISABLED))
		वापस -EINVAL;

	अगर ((wpa_versions & IW_AUTH_WPA_VERSION_DISABLED) &&
	    (wpa_versions & (IW_AUTH_WPA_VERSION_WPA|
			     IW_AUTH_WPA_VERSION_WPA2)))
		वापस -EINVAL;

	अगर (wpa_versions & IW_AUTH_WPA_VERSION_DISABLED)
		wdev->wext.connect.crypto.wpa_versions &=
			~(NL80211_WPA_VERSION_1|NL80211_WPA_VERSION_2);

	अगर (wpa_versions & IW_AUTH_WPA_VERSION_WPA)
		wdev->wext.connect.crypto.wpa_versions |=
			NL80211_WPA_VERSION_1;

	अगर (wpa_versions & IW_AUTH_WPA_VERSION_WPA2)
		wdev->wext.connect.crypto.wpa_versions |=
			NL80211_WPA_VERSION_2;

	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_set_cipher_group(काष्ठा wireless_dev *wdev, u32 cipher)
अणु
	अगर (cipher & IW_AUTH_CIPHER_WEP40)
		wdev->wext.connect.crypto.cipher_group =
			WLAN_CIPHER_SUITE_WEP40;
	अन्यथा अगर (cipher & IW_AUTH_CIPHER_WEP104)
		wdev->wext.connect.crypto.cipher_group =
			WLAN_CIPHER_SUITE_WEP104;
	अन्यथा अगर (cipher & IW_AUTH_CIPHER_TKIP)
		wdev->wext.connect.crypto.cipher_group =
			WLAN_CIPHER_SUITE_TKIP;
	अन्यथा अगर (cipher & IW_AUTH_CIPHER_CCMP)
		wdev->wext.connect.crypto.cipher_group =
			WLAN_CIPHER_SUITE_CCMP;
	अन्यथा अगर (cipher & IW_AUTH_CIPHER_AES_CMAC)
		wdev->wext.connect.crypto.cipher_group =
			WLAN_CIPHER_SUITE_AES_CMAC;
	अन्यथा अगर (cipher & IW_AUTH_CIPHER_NONE)
		wdev->wext.connect.crypto.cipher_group = 0;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_set_cipher_pairwise(काष्ठा wireless_dev *wdev, u32 cipher)
अणु
	पूर्णांक nr_ciphers = 0;
	u32 *ciphers_pairwise = wdev->wext.connect.crypto.ciphers_pairwise;

	अगर (cipher & IW_AUTH_CIPHER_WEP40) अणु
		ciphers_pairwise[nr_ciphers] = WLAN_CIPHER_SUITE_WEP40;
		nr_ciphers++;
	पूर्ण

	अगर (cipher & IW_AUTH_CIPHER_WEP104) अणु
		ciphers_pairwise[nr_ciphers] = WLAN_CIPHER_SUITE_WEP104;
		nr_ciphers++;
	पूर्ण

	अगर (cipher & IW_AUTH_CIPHER_TKIP) अणु
		ciphers_pairwise[nr_ciphers] = WLAN_CIPHER_SUITE_TKIP;
		nr_ciphers++;
	पूर्ण

	अगर (cipher & IW_AUTH_CIPHER_CCMP) अणु
		ciphers_pairwise[nr_ciphers] = WLAN_CIPHER_SUITE_CCMP;
		nr_ciphers++;
	पूर्ण

	अगर (cipher & IW_AUTH_CIPHER_AES_CMAC) अणु
		ciphers_pairwise[nr_ciphers] = WLAN_CIPHER_SUITE_AES_CMAC;
		nr_ciphers++;
	पूर्ण

	BUILD_BUG_ON(NL80211_MAX_NR_CIPHER_SUITES < 5);

	wdev->wext.connect.crypto.n_ciphers_pairwise = nr_ciphers;

	वापस 0;
पूर्ण


अटल पूर्णांक cfg80211_set_key_mgt(काष्ठा wireless_dev *wdev, u32 key_mgt)
अणु
	पूर्णांक nr_akm_suites = 0;

	अगर (key_mgt & ~(IW_AUTH_KEY_MGMT_802_1X |
			IW_AUTH_KEY_MGMT_PSK))
		वापस -EINVAL;

	अगर (key_mgt & IW_AUTH_KEY_MGMT_802_1X) अणु
		wdev->wext.connect.crypto.akm_suites[nr_akm_suites] =
			WLAN_AKM_SUITE_8021X;
		nr_akm_suites++;
	पूर्ण

	अगर (key_mgt & IW_AUTH_KEY_MGMT_PSK) अणु
		wdev->wext.connect.crypto.akm_suites[nr_akm_suites] =
			WLAN_AKM_SUITE_PSK;
		nr_akm_suites++;
	पूर्ण

	wdev->wext.connect.crypto.n_akm_suites = nr_akm_suites;

	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_wext_siwauth(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_param *data, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION)
		वापस -EOPNOTSUPP;

	चयन (data->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_PRIVACY_INVOKED:
		wdev->wext.connect.privacy = data->value;
		वापस 0;
	हाल IW_AUTH_WPA_VERSION:
		वापस cfg80211_set_wpa_version(wdev, data->value);
	हाल IW_AUTH_CIPHER_GROUP:
		वापस cfg80211_set_cipher_group(wdev, data->value);
	हाल IW_AUTH_KEY_MGMT:
		वापस cfg80211_set_key_mgt(wdev, data->value);
	हाल IW_AUTH_CIPHER_PAIRWISE:
		वापस cfg80211_set_cipher_pairwise(wdev, data->value);
	हाल IW_AUTH_80211_AUTH_ALG:
		वापस cfg80211_set_auth_alg(wdev, data->value);
	हाल IW_AUTH_WPA_ENABLED:
	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:
	हाल IW_AUTH_DROP_UNENCRYPTED:
	हाल IW_AUTH_MFP:
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक cfg80211_wext_giwauth(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_param *data, अक्षर *extra)
अणु
	/* XXX: what करो we need? */

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक cfg80211_wext_siwघातer(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  काष्ठा iw_param *wrq, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	bool ps = wdev->ps;
	पूर्णांक समयout = wdev->ps_समयout;
	पूर्णांक err;

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION)
		वापस -EINVAL;

	अगर (!rdev->ops->set_घातer_mgmt)
		वापस -EOPNOTSUPP;

	अगर (wrq->disabled) अणु
		ps = false;
	पूर्ण अन्यथा अणु
		चयन (wrq->flags & IW_POWER_MODE) अणु
		हाल IW_POWER_ON:       /* If not specअगरied */
		हाल IW_POWER_MODE:     /* If set all mask */
		हाल IW_POWER_ALL_R:    /* If explicitely state all */
			ps = true;
			अवरोध;
		शेष:                /* Otherwise we ignore */
			वापस -EINVAL;
		पूर्ण

		अगर (wrq->flags & ~(IW_POWER_MODE | IW_POWER_TIMEOUT))
			वापस -EINVAL;

		अगर (wrq->flags & IW_POWER_TIMEOUT)
			समयout = wrq->value / 1000;
	पूर्ण

	wiphy_lock(&rdev->wiphy);
	err = rdev_set_घातer_mgmt(rdev, dev, ps, समयout);
	wiphy_unlock(&rdev->wiphy);
	अगर (err)
		वापस err;

	wdev->ps = ps;
	wdev->ps_समयout = समयout;

	वापस 0;

पूर्ण

अटल पूर्णांक cfg80211_wext_giwघातer(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  काष्ठा iw_param *wrq, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

	wrq->disabled = !wdev->ps;

	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_wext_siwrate(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_param *rate, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_bitrate_mask mask;
	u32 fixed, maxrate;
	काष्ठा ieee80211_supported_band *sband;
	पूर्णांक band, ridx, ret;
	bool match = false;

	अगर (!rdev->ops->set_bitrate_mask)
		वापस -EOPNOTSUPP;

	स_रखो(&mask, 0, माप(mask));
	fixed = 0;
	maxrate = (u32)-1;

	अगर (rate->value < 0) अणु
		/* nothing */
	पूर्ण अन्यथा अगर (rate->fixed) अणु
		fixed = rate->value / 100000;
	पूर्ण अन्यथा अणु
		maxrate = rate->value / 100000;
	पूर्ण

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		sband = wdev->wiphy->bands[band];
		अगर (sband == शून्य)
			जारी;
		क्रम (ridx = 0; ridx < sband->n_bitrates; ridx++) अणु
			काष्ठा ieee80211_rate *srate = &sband->bitrates[ridx];
			अगर (fixed == srate->bitrate) अणु
				mask.control[band].legacy = 1 << ridx;
				match = true;
				अवरोध;
			पूर्ण
			अगर (srate->bitrate <= maxrate) अणु
				mask.control[band].legacy |= 1 << ridx;
				match = true;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!match)
		वापस -EINVAL;

	wiphy_lock(&rdev->wiphy);
	ret = rdev_set_bitrate_mask(rdev, dev, शून्य, &mask);
	wiphy_unlock(&rdev->wiphy);

	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_wext_giwrate(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_param *rate, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा station_info sinfo = अणुपूर्ण;
	u8 addr[ETH_ALEN];
	पूर्णांक err;

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION)
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->get_station)
		वापस -EOPNOTSUPP;

	err = 0;
	wdev_lock(wdev);
	अगर (wdev->current_bss)
		स_नकल(addr, wdev->current_bss->pub.bssid, ETH_ALEN);
	अन्यथा
		err = -EOPNOTSUPP;
	wdev_unlock(wdev);
	अगर (err)
		वापस err;

	wiphy_lock(&rdev->wiphy);
	err = rdev_get_station(rdev, dev, addr, &sinfo);
	wiphy_unlock(&rdev->wiphy);
	अगर (err)
		वापस err;

	अगर (!(sinfo.filled & BIT_ULL(NL80211_STA_INFO_TX_BITRATE))) अणु
		err = -EOPNOTSUPP;
		जाओ मुक्त;
	पूर्ण

	rate->value = 100000 * cfg80211_calculate_bitrate(&sinfo.txrate);

मुक्त:
	cfg80211_sinfo_release_content(&sinfo);
	वापस err;
पूर्ण

/* Get wireless statistics.  Called by /proc/net/wireless and by SIOCGIWSTATS */
अटल काष्ठा iw_statistics *cfg80211_wireless_stats(काष्ठा net_device *dev)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	/* we are under RTNL - globally locked - so can use अटल काष्ठाs */
	अटल काष्ठा iw_statistics wstats;
	अटल काष्ठा station_info sinfo = अणुपूर्ण;
	u8 bssid[ETH_ALEN];
	पूर्णांक ret;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_STATION)
		वापस शून्य;

	अगर (!rdev->ops->get_station)
		वापस शून्य;

	/* Grab BSSID of current BSS, अगर any */
	wdev_lock(wdev);
	अगर (!wdev->current_bss) अणु
		wdev_unlock(wdev);
		वापस शून्य;
	पूर्ण
	स_नकल(bssid, wdev->current_bss->pub.bssid, ETH_ALEN);
	wdev_unlock(wdev);

	स_रखो(&sinfo, 0, माप(sinfo));

	wiphy_lock(&rdev->wiphy);
	ret = rdev_get_station(rdev, dev, bssid, &sinfo);
	wiphy_unlock(&rdev->wiphy);

	अगर (ret)
		वापस शून्य;

	स_रखो(&wstats, 0, माप(wstats));

	चयन (rdev->wiphy.संकेत_type) अणु
	हाल CFG80211_SIGNAL_TYPE_MBM:
		अगर (sinfo.filled & BIT_ULL(NL80211_STA_INFO_SIGNAL)) अणु
			पूर्णांक sig = sinfo.संकेत;
			wstats.qual.updated |= IW_QUAL_LEVEL_UPDATED;
			wstats.qual.updated |= IW_QUAL_QUAL_UPDATED;
			wstats.qual.updated |= IW_QUAL_DBM;
			wstats.qual.level = sig;
			अगर (sig < -110)
				sig = -110;
			अन्यथा अगर (sig > -40)
				sig = -40;
			wstats.qual.qual = sig + 110;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल CFG80211_SIGNAL_TYPE_UNSPEC:
		अगर (sinfo.filled & BIT_ULL(NL80211_STA_INFO_SIGNAL)) अणु
			wstats.qual.updated |= IW_QUAL_LEVEL_UPDATED;
			wstats.qual.updated |= IW_QUAL_QUAL_UPDATED;
			wstats.qual.level = sinfo.संकेत;
			wstats.qual.qual = sinfo.संकेत;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		wstats.qual.updated |= IW_QUAL_LEVEL_INVALID;
		wstats.qual.updated |= IW_QUAL_QUAL_INVALID;
	पूर्ण

	wstats.qual.updated |= IW_QUAL_NOISE_INVALID;
	अगर (sinfo.filled & BIT_ULL(NL80211_STA_INFO_RX_DROP_MISC))
		wstats.discard.misc = sinfo.rx_dropped_misc;
	अगर (sinfo.filled & BIT_ULL(NL80211_STA_INFO_TX_FAILED))
		wstats.discard.retries = sinfo.tx_failed;

	cfg80211_sinfo_release_content(&sinfo);

	वापस &wstats;
पूर्ण

अटल पूर्णांक cfg80211_wext_siwap(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       काष्ठा sockaddr *ap_addr, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	पूर्णांक ret;

	wiphy_lock(&rdev->wiphy);
	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_ADHOC:
		ret = cfg80211_ibss_wext_siwap(dev, info, ap_addr, extra);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		ret = cfg80211_mgd_wext_siwap(dev, info, ap_addr, extra);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	wiphy_unlock(&rdev->wiphy);

	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_wext_giwap(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       काष्ठा sockaddr *ap_addr, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	पूर्णांक ret;

	wiphy_lock(&rdev->wiphy);
	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_ADHOC:
		ret = cfg80211_ibss_wext_giwap(dev, info, ap_addr, extra);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		ret = cfg80211_mgd_wext_giwap(dev, info, ap_addr, extra);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	wiphy_unlock(&rdev->wiphy);

	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_wext_siwessid(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  काष्ठा iw_poपूर्णांक *data, अक्षर *ssid)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	पूर्णांक ret;

	wiphy_lock(&rdev->wiphy);
	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_ADHOC:
		ret = cfg80211_ibss_wext_siwessid(dev, info, data, ssid);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		ret = cfg80211_mgd_wext_siwessid(dev, info, data, ssid);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	wiphy_unlock(&rdev->wiphy);

	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_wext_giwessid(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  काष्ठा iw_poपूर्णांक *data, अक्षर *ssid)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	पूर्णांक ret;

	data->flags = 0;
	data->length = 0;

	wiphy_lock(&rdev->wiphy);
	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_ADHOC:
		ret = cfg80211_ibss_wext_giwessid(dev, info, data, ssid);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		ret = cfg80211_mgd_wext_giwessid(dev, info, data, ssid);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	wiphy_unlock(&rdev->wiphy);

	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_wext_siwpmksa(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_pmksa cfg_pmksa;
	काष्ठा iw_pmksa *pmksa = (काष्ठा iw_pmksa *)extra;
	पूर्णांक ret;

	स_रखो(&cfg_pmksa, 0, माप(काष्ठा cfg80211_pmksa));

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION)
		वापस -EINVAL;

	cfg_pmksa.bssid = pmksa->bssid.sa_data;
	cfg_pmksa.pmkid = pmksa->pmkid;

	wiphy_lock(&rdev->wiphy);
	चयन (pmksa->cmd) अणु
	हाल IW_PMKSA_ADD:
		अगर (!rdev->ops->set_pmksa) अणु
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		ret = rdev_set_pmksa(rdev, dev, &cfg_pmksa);
		अवरोध;
	हाल IW_PMKSA_REMOVE:
		अगर (!rdev->ops->del_pmksa) अणु
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		ret = rdev_del_pmksa(rdev, dev, &cfg_pmksa);
		अवरोध;
	हाल IW_PMKSA_FLUSH:
		अगर (!rdev->ops->flush_pmksa) अणु
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		ret = rdev_flush_pmksa(rdev, dev);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	wiphy_unlock(&rdev->wiphy);

	वापस ret;
पूर्ण

#घोषणा DEFINE_WEXT_COMPAT_STUB(func, type)			\
	अटल पूर्णांक __ ## func(काष्ठा net_device *dev,		\
			      काष्ठा iw_request_info *info,	\
			      जोड़ iwreq_data *wrqu,		\
			      अक्षर *extra)			\
	अणु							\
		वापस func(dev, info, (type *)wrqu, extra);	\
	पूर्ण

DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_giwname, अक्षर)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwfreq, काष्ठा iw_freq)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_giwfreq, काष्ठा iw_freq)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwmode, u32)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_giwmode, u32)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_giwrange, काष्ठा iw_poपूर्णांक)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwap, काष्ठा sockaddr)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_giwap, काष्ठा sockaddr)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwmlme, काष्ठा iw_poपूर्णांक)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_giwscan, काष्ठा iw_poपूर्णांक)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwessid, काष्ठा iw_poपूर्णांक)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_giwessid, काष्ठा iw_poपूर्णांक)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwrate, काष्ठा iw_param)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_giwrate, काष्ठा iw_param)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwrts, काष्ठा iw_param)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_giwrts, काष्ठा iw_param)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwfrag, काष्ठा iw_param)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_giwfrag, काष्ठा iw_param)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwretry, काष्ठा iw_param)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_giwretry, काष्ठा iw_param)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwencode, काष्ठा iw_poपूर्णांक)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_giwencode, काष्ठा iw_poपूर्णांक)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_giwघातer, काष्ठा iw_param)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwघातer, काष्ठा iw_param)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwgenie, काष्ठा iw_poपूर्णांक)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_giwauth, काष्ठा iw_param)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwauth, काष्ठा iw_param)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwencodeext, काष्ठा iw_poपूर्णांक)
DEFINE_WEXT_COMPAT_STUB(cfg80211_wext_siwpmksa, काष्ठा iw_poपूर्णांक)

अटल स्थिर iw_handler cfg80211_handlers[] = अणु
	[IW_IOCTL_IDX(SIOCGIWNAME)]	= __cfg80211_wext_giwname,
	[IW_IOCTL_IDX(SIOCSIWFREQ)]	= __cfg80211_wext_siwfreq,
	[IW_IOCTL_IDX(SIOCGIWFREQ)]	= __cfg80211_wext_giwfreq,
	[IW_IOCTL_IDX(SIOCSIWMODE)]	= __cfg80211_wext_siwmode,
	[IW_IOCTL_IDX(SIOCGIWMODE)]	= __cfg80211_wext_giwmode,
	[IW_IOCTL_IDX(SIOCGIWRANGE)]	= __cfg80211_wext_giwrange,
	[IW_IOCTL_IDX(SIOCSIWAP)]	= __cfg80211_wext_siwap,
	[IW_IOCTL_IDX(SIOCGIWAP)]	= __cfg80211_wext_giwap,
	[IW_IOCTL_IDX(SIOCSIWMLME)]	= __cfg80211_wext_siwmlme,
	[IW_IOCTL_IDX(SIOCSIWSCAN)]	= cfg80211_wext_siwscan,
	[IW_IOCTL_IDX(SIOCGIWSCAN)]	= __cfg80211_wext_giwscan,
	[IW_IOCTL_IDX(SIOCSIWESSID)]	= __cfg80211_wext_siwessid,
	[IW_IOCTL_IDX(SIOCGIWESSID)]	= __cfg80211_wext_giwessid,
	[IW_IOCTL_IDX(SIOCSIWRATE)]	= __cfg80211_wext_siwrate,
	[IW_IOCTL_IDX(SIOCGIWRATE)]	= __cfg80211_wext_giwrate,
	[IW_IOCTL_IDX(SIOCSIWRTS)]	= __cfg80211_wext_siwrts,
	[IW_IOCTL_IDX(SIOCGIWRTS)]	= __cfg80211_wext_giwrts,
	[IW_IOCTL_IDX(SIOCSIWFRAG)]	= __cfg80211_wext_siwfrag,
	[IW_IOCTL_IDX(SIOCGIWFRAG)]	= __cfg80211_wext_giwfrag,
	[IW_IOCTL_IDX(SIOCSIWTXPOW)]	= cfg80211_wext_siwtxघातer,
	[IW_IOCTL_IDX(SIOCGIWTXPOW)]	= cfg80211_wext_giwtxघातer,
	[IW_IOCTL_IDX(SIOCSIWRETRY)]	= __cfg80211_wext_siwretry,
	[IW_IOCTL_IDX(SIOCGIWRETRY)]	= __cfg80211_wext_giwretry,
	[IW_IOCTL_IDX(SIOCSIWENCODE)]	= __cfg80211_wext_siwencode,
	[IW_IOCTL_IDX(SIOCGIWENCODE)]	= __cfg80211_wext_giwencode,
	[IW_IOCTL_IDX(SIOCSIWPOWER)]	= __cfg80211_wext_siwघातer,
	[IW_IOCTL_IDX(SIOCGIWPOWER)]	= __cfg80211_wext_giwघातer,
	[IW_IOCTL_IDX(SIOCSIWGENIE)]	= __cfg80211_wext_siwgenie,
	[IW_IOCTL_IDX(SIOCSIWAUTH)]	= __cfg80211_wext_siwauth,
	[IW_IOCTL_IDX(SIOCGIWAUTH)]	= __cfg80211_wext_giwauth,
	[IW_IOCTL_IDX(SIOCSIWENCODEEXT)]= __cfg80211_wext_siwencodeext,
	[IW_IOCTL_IDX(SIOCSIWPMKSA)]	= __cfg80211_wext_siwpmksa,
पूर्ण;

स्थिर काष्ठा iw_handler_def cfg80211_wext_handler = अणु
	.num_standard		= ARRAY_SIZE(cfg80211_handlers),
	.standard		= cfg80211_handlers,
	.get_wireless_stats = cfg80211_wireless_stats,
पूर्ण;
