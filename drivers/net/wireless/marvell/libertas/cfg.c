<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implement cfg80211 ("iw") support.
 *
 * Copyright (C) 2009 M&N Solutions GmbH, 61191 Rosbach, Germany
 * Holger Schurig <hs4233@mail.mn-solutions.de>
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/hardirq.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/ieee80211.h>
#समावेश <net/cfg80211.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "decl.h"
#समावेश "cfg.h"
#समावेश "cmd.h"
#समावेश "mesh.h"


#घोषणा CHAN2G(_channel, _freq, _flags) अणु        \
	.band             = NL80211_BAND_2GHZ, \
	.center_freq      = (_freq),             \
	.hw_value         = (_channel),          \
	.flags            = (_flags),            \
	.max_antenna_gain = 0,                   \
	.max_घातer        = 30,                  \
पूर्ण

अटल काष्ठा ieee80211_channel lbs_2ghz_channels[] = अणु
	CHAN2G(1,  2412, 0),
	CHAN2G(2,  2417, 0),
	CHAN2G(3,  2422, 0),
	CHAN2G(4,  2427, 0),
	CHAN2G(5,  2432, 0),
	CHAN2G(6,  2437, 0),
	CHAN2G(7,  2442, 0),
	CHAN2G(8,  2447, 0),
	CHAN2G(9,  2452, 0),
	CHAN2G(10, 2457, 0),
	CHAN2G(11, 2462, 0),
	CHAN2G(12, 2467, 0),
	CHAN2G(13, 2472, 0),
	CHAN2G(14, 2484, 0),
पूर्ण;

#घोषणा RATETAB_ENT(_rate, _hw_value, _flags) अणु \
	.bitrate  = (_rate),                    \
	.hw_value = (_hw_value),                \
	.flags    = (_flags),                   \
पूर्ण


/* Table 6 in section 3.2.1.1 */
अटल काष्ठा ieee80211_rate lbs_rates[] = अणु
	RATETAB_ENT(10,  0,  0),
	RATETAB_ENT(20,  1,  0),
	RATETAB_ENT(55,  2,  0),
	RATETAB_ENT(110, 3,  0),
	RATETAB_ENT(60,  9,  0),
	RATETAB_ENT(90,  6,  0),
	RATETAB_ENT(120, 7,  0),
	RATETAB_ENT(180, 8,  0),
	RATETAB_ENT(240, 9,  0),
	RATETAB_ENT(360, 10, 0),
	RATETAB_ENT(480, 11, 0),
	RATETAB_ENT(540, 12, 0),
पूर्ण;

अटल काष्ठा ieee80211_supported_band lbs_band_2ghz = अणु
	.channels = lbs_2ghz_channels,
	.n_channels = ARRAY_SIZE(lbs_2ghz_channels),
	.bitrates = lbs_rates,
	.n_bitrates = ARRAY_SIZE(lbs_rates),
पूर्ण;


अटल स्थिर u32 cipher_suites[] = अणु
	WLAN_CIPHER_SUITE_WEP40,
	WLAN_CIPHER_SUITE_WEP104,
	WLAN_CIPHER_SUITE_TKIP,
	WLAN_CIPHER_SUITE_CCMP,
पूर्ण;

/* Time to stay on the channel */
#घोषणा LBS_DWELL_PASSIVE 100
#घोषणा LBS_DWELL_ACTIVE  40


/***************************************************************************
 * Misc utility functions
 *
 * TLVs are Marvell specअगरic. They are very similar to IEs, they have the
 * same काष्ठाure: type, length, data*. The only dअगरference: क्रम IEs, the
 * type and length are u8, but क्रम TLVs they're __le16.
 */

/*
 * Convert NL80211's auth_type to the one from Libertas, see chapter 5.9.1
 * in the firmware spec
 */
अटल पूर्णांक lbs_auth_to_authtype(क्रमागत nl80211_auth_type auth_type)
अणु
	पूर्णांक ret = -ENOTSUPP;

	चयन (auth_type) अणु
	हाल NL80211_AUTHTYPE_OPEN_SYSTEM:
	हाल NL80211_AUTHTYPE_SHARED_KEY:
		ret = auth_type;
		अवरोध;
	हाल NL80211_AUTHTYPE_AUTOMATIC:
		ret = NL80211_AUTHTYPE_OPEN_SYSTEM;
		अवरोध;
	हाल NL80211_AUTHTYPE_NETWORK_EAP:
		ret = 0x80;
		अवरोध;
	शेष:
		/* silence compiler */
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण


/*
 * Various firmware commands need the list of supported rates, but with
 * the hight-bit set क्रम basic rates
 */
अटल पूर्णांक lbs_add_rates(u8 *rates)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < ARRAY_SIZE(lbs_rates); i++) अणु
		u8 rate = lbs_rates[i].bitrate / 5;
		अगर (rate == 0x02 || rate == 0x04 ||
		    rate == 0x0b || rate == 0x16)
			rate |= 0x80;
		rates[i] = rate;
	पूर्ण
	वापस ARRAY_SIZE(lbs_rates);
पूर्ण


/***************************************************************************
 * TLV utility functions
 *
 * TLVs are Marvell specअगरic. They are very similar to IEs, they have the
 * same काष्ठाure: type, length, data*. The only dअगरference: क्रम IEs, the
 * type and length are u8, but क्रम TLVs they're __le16.
 */


/*
 * Add ssid TLV
 */
#घोषणा LBS_MAX_SSID_TLV_SIZE			\
	(माप(काष्ठा mrvl_ie_header)		\
	 + IEEE80211_MAX_SSID_LEN)

अटल पूर्णांक lbs_add_ssid_tlv(u8 *tlv, स्थिर u8 *ssid, पूर्णांक ssid_len)
अणु
	काष्ठा mrvl_ie_ssid_param_set *ssid_tlv = (व्योम *)tlv;

	/*
	 * TLV-ID SSID  00 00
	 * length       06 00
	 * ssid         4d 4e 54 45 53 54
	 */
	ssid_tlv->header.type = cpu_to_le16(TLV_TYPE_SSID);
	ssid_tlv->header.len = cpu_to_le16(ssid_len);
	स_नकल(ssid_tlv->ssid, ssid, ssid_len);
	वापस माप(ssid_tlv->header) + ssid_len;
पूर्ण


/*
 * Add channel list TLV (section 8.4.2)
 *
 * Actual channel data comes from priv->wdev->wiphy->channels.
 */
#घोषणा LBS_MAX_CHANNEL_LIST_TLV_SIZE					\
	(माप(काष्ठा mrvl_ie_header)					\
	 + (LBS_SCAN_BEFORE_NAP * माप(काष्ठा chanscanparamset)))

अटल पूर्णांक lbs_add_channel_list_tlv(काष्ठा lbs_निजी *priv, u8 *tlv,
				    पूर्णांक last_channel, पूर्णांक active_scan)
अणु
	पूर्णांक chanscanparamsize = माप(काष्ठा chanscanparamset) *
		(last_channel - priv->scan_channel);

	काष्ठा mrvl_ie_header *header = (व्योम *) tlv;

	/*
	 * TLV-ID CHANLIST  01 01
	 * length           0e 00
	 * channel          00 01 00 00 00 64 00
	 *   radio type     00
	 *   channel           01
	 *   scan type            00
	 *   min scan समय           00 00
	 *   max scan समय                 64 00
	 * channel 2        00 02 00 00 00 64 00
	 *
	 */

	header->type = cpu_to_le16(TLV_TYPE_CHANLIST);
	header->len  = cpu_to_le16(chanscanparamsize);
	tlv += माप(काष्ठा mrvl_ie_header);

	/* lbs_deb_scan("scan: channels %d to %d\n", priv->scan_channel,
		     last_channel); */
	स_रखो(tlv, 0, chanscanparamsize);

	जबतक (priv->scan_channel < last_channel) अणु
		काष्ठा chanscanparamset *param = (व्योम *) tlv;

		param->radiotype = CMD_SCAN_RADIO_TYPE_BG;
		param->channumber =
			priv->scan_req->channels[priv->scan_channel]->hw_value;
		अगर (active_scan) अणु
			param->maxscanसमय = cpu_to_le16(LBS_DWELL_ACTIVE);
		पूर्ण अन्यथा अणु
			param->chanscanmode.passivescan = 1;
			param->maxscanसमय = cpu_to_le16(LBS_DWELL_PASSIVE);
		पूर्ण
		tlv += माप(काष्ठा chanscanparamset);
		priv->scan_channel++;
	पूर्ण
	वापस माप(काष्ठा mrvl_ie_header) + chanscanparamsize;
पूर्ण


/*
 * Add rates TLV
 *
 * The rates are in lbs_bg_rates[], but क्रम the 802.11b
 * rates the high bit is set. We add this TLV only because
 * there's a firmware which otherwise doesn't report all
 * APs in range.
 */
#घोषणा LBS_MAX_RATES_TLV_SIZE			\
	(माप(काष्ठा mrvl_ie_header)		\
	 + (ARRAY_SIZE(lbs_rates)))

/* Adds a TLV with all rates the hardware supports */
अटल पूर्णांक lbs_add_supported_rates_tlv(u8 *tlv)
अणु
	माप_प्रकार i;
	काष्ठा mrvl_ie_rates_param_set *rate_tlv = (व्योम *)tlv;

	/*
	 * TLV-ID RATES  01 00
	 * length        0e 00
	 * rates         82 84 8b 96 0c 12 18 24 30 48 60 6c
	 */
	rate_tlv->header.type = cpu_to_le16(TLV_TYPE_RATES);
	tlv += माप(rate_tlv->header);
	i = lbs_add_rates(tlv);
	tlv += i;
	rate_tlv->header.len = cpu_to_le16(i);
	वापस माप(rate_tlv->header) + i;
पूर्ण

/* Add common rates from a TLV and वापस the new end of the TLV */
अटल u8 *
add_ie_rates(u8 *tlv, स्थिर u8 *ie, पूर्णांक *nrates)
अणु
	पूर्णांक hw, ap, ap_max = ie[1];
	u8 hw_rate;

	अगर (ap_max > MAX_RATES) अणु
		lbs_deb_assoc("invalid rates\n");
		वापस tlv;
	पूर्ण
	/* Advance past IE header */
	ie += 2;

	lbs_deb_hex(LBS_DEB_ASSOC, "AP IE Rates", (u8 *) ie, ap_max);

	क्रम (hw = 0; hw < ARRAY_SIZE(lbs_rates); hw++) अणु
		hw_rate = lbs_rates[hw].bitrate / 5;
		क्रम (ap = 0; ap < ap_max; ap++) अणु
			अगर (hw_rate == (ie[ap] & 0x7f)) अणु
				*tlv++ = ie[ap];
				*nrates = *nrates + 1;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस tlv;
पूर्ण

/*
 * Adds a TLV with all rates the hardware *and* BSS supports.
 */
अटल पूर्णांक lbs_add_common_rates_tlv(u8 *tlv, काष्ठा cfg80211_bss *bss)
अणु
	काष्ठा mrvl_ie_rates_param_set *rate_tlv = (व्योम *)tlv;
	स्थिर u8 *rates_eid, *ext_rates_eid;
	पूर्णांक n = 0;

	rcu_पढ़ो_lock();
	rates_eid = ieee80211_bss_get_ie(bss, WLAN_EID_SUPP_RATES);
	ext_rates_eid = ieee80211_bss_get_ie(bss, WLAN_EID_EXT_SUPP_RATES);

	/*
	 * 01 00                   TLV_TYPE_RATES
	 * 04 00                   len
	 * 82 84 8b 96             rates
	 */
	rate_tlv->header.type = cpu_to_le16(TLV_TYPE_RATES);
	tlv += माप(rate_tlv->header);

	/* Add basic rates */
	अगर (rates_eid) अणु
		tlv = add_ie_rates(tlv, rates_eid, &n);

		/* Add extended rates, अगर any */
		अगर (ext_rates_eid)
			tlv = add_ie_rates(tlv, ext_rates_eid, &n);
	पूर्ण अन्यथा अणु
		lbs_deb_assoc("assoc: bss had no basic rate IE\n");
		/* Fallback: add basic 802.11b rates */
		*tlv++ = 0x82;
		*tlv++ = 0x84;
		*tlv++ = 0x8b;
		*tlv++ = 0x96;
		n = 4;
	पूर्ण
	rcu_पढ़ो_unlock();

	rate_tlv->header.len = cpu_to_le16(n);
	वापस माप(rate_tlv->header) + n;
पूर्ण


/*
 * Add auth type TLV.
 *
 * This is only needed क्रम newer firmware (V9 and up).
 */
#घोषणा LBS_MAX_AUTH_TYPE_TLV_SIZE \
	माप(काष्ठा mrvl_ie_auth_type)

अटल पूर्णांक lbs_add_auth_type_tlv(u8 *tlv, क्रमागत nl80211_auth_type auth_type)
अणु
	काष्ठा mrvl_ie_auth_type *auth = (व्योम *) tlv;

	/*
	 * 1f 01  TLV_TYPE_AUTH_TYPE
	 * 01 00  len
	 * 01     auth type
	 */
	auth->header.type = cpu_to_le16(TLV_TYPE_AUTH_TYPE);
	auth->header.len = cpu_to_le16(माप(*auth)-माप(auth->header));
	auth->auth = cpu_to_le16(lbs_auth_to_authtype(auth_type));
	वापस माप(*auth);
पूर्ण


/*
 * Add channel (phy ds) TLV
 */
#घोषणा LBS_MAX_CHANNEL_TLV_SIZE \
	माप(काष्ठा mrvl_ie_header)

अटल पूर्णांक lbs_add_channel_tlv(u8 *tlv, u8 channel)
अणु
	काष्ठा mrvl_ie_ds_param_set *ds = (व्योम *) tlv;

	/*
	 * 03 00  TLV_TYPE_PHY_DS
	 * 01 00  len
	 * 06     channel
	 */
	ds->header.type = cpu_to_le16(TLV_TYPE_PHY_DS);
	ds->header.len = cpu_to_le16(माप(*ds)-माप(ds->header));
	ds->channel = channel;
	वापस माप(*ds);
पूर्ण


/*
 * Add (empty) CF param TLV of the क्रमm:
 */
#घोषणा LBS_MAX_CF_PARAM_TLV_SIZE		\
	माप(काष्ठा mrvl_ie_header)

अटल पूर्णांक lbs_add_cf_param_tlv(u8 *tlv)
अणु
	काष्ठा mrvl_ie_cf_param_set *cf = (व्योम *)tlv;

	/*
	 * 04 00  TLV_TYPE_CF
	 * 06 00  len
	 * 00     cfpcnt
	 * 00     cfpperiod
	 * 00 00  cfpmaxduration
	 * 00 00  cfpdurationreमुख्यing
	 */
	cf->header.type = cpu_to_le16(TLV_TYPE_CF);
	cf->header.len = cpu_to_le16(माप(*cf)-माप(cf->header));
	वापस माप(*cf);
पूर्ण

/*
 * Add WPA TLV
 */
#घोषणा LBS_MAX_WPA_TLV_SIZE			\
	(माप(काष्ठा mrvl_ie_header)		\
	 + 128 /* TODO: I guessed the size */)

अटल पूर्णांक lbs_add_wpa_tlv(u8 *tlv, स्थिर u8 *ie, u8 ie_len)
अणु
	माप_प्रकार tlv_len;

	/*
	 * We need just convert an IE to an TLV. IEs use u8 क्रम the header,
	 *   u8      type
	 *   u8      len
	 *   u8[]    data
	 * but TLVs use __le16 instead:
	 *   __le16  type
	 *   __le16  len
	 *   u8[]    data
	 */
	*tlv++ = *ie++;
	*tlv++ = 0;
	tlv_len = *tlv++ = *ie++;
	*tlv++ = 0;
	जबतक (tlv_len--)
		*tlv++ = *ie++;
	/* the TLV is two bytes larger than the IE */
	वापस ie_len + 2;
पूर्ण

/*
 * Set Channel
 */

अटल पूर्णांक lbs_cfg_set_monitor_channel(काष्ठा wiphy *wiphy,
				       काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा lbs_निजी *priv = wiphy_priv(wiphy);
	पूर्णांक ret = -ENOTSUPP;

	अगर (cfg80211_get_chandef_type(chandef) != NL80211_CHAN_NO_HT)
		जाओ out;

	ret = lbs_set_channel(priv, chandef->chan->hw_value);

 out:
	वापस ret;
पूर्ण

अटल पूर्णांक lbs_cfg_set_mesh_channel(काष्ठा wiphy *wiphy,
				    काष्ठा net_device *netdev,
				    काष्ठा ieee80211_channel *channel)
अणु
	काष्ठा lbs_निजी *priv = wiphy_priv(wiphy);
	पूर्णांक ret = -ENOTSUPP;

	अगर (netdev != priv->mesh_dev)
		जाओ out;

	ret = lbs_mesh_set_channel(priv, channel->hw_value);

 out:
	वापस ret;
पूर्ण



/*
 * Scanning
 */

/*
 * When scanning, the firmware करोesn't send a nul packet with the घातer-safe
 * bit to the AP. So we cannot stay away from our current channel too दीर्घ,
 * otherwise we loose data. So take a "nap" जबतक scanning every other
 * जबतक.
 */
#घोषणा LBS_SCAN_BEFORE_NAP 4


/*
 * When the firmware reports back a scan-result, it gives us an "u8 rssi",
 * which isn't really an RSSI, as it becomes larger when moving away from
 * the AP. Anyway, we need to convert that पूर्णांकo mBm.
 */
#घोषणा LBS_SCAN_RSSI_TO_MBM(rssi) \
	((-(पूर्णांक)rssi + 3)*100)

अटल पूर्णांक lbs_ret_scan(काष्ठा lbs_निजी *priv, अचिन्हित दीर्घ dummy,
	काष्ठा cmd_header *resp)
अणु
	काष्ठा cfg80211_bss *bss;
	काष्ठा cmd_ds_802_11_scan_rsp *scanresp = (व्योम *)resp;
	पूर्णांक bsssize;
	स्थिर u8 *pos;
	स्थिर u8 *tsfdesc;
	पूर्णांक tsfsize;
	पूर्णांक i;
	पूर्णांक ret = -EILSEQ;

	bsssize = get_unaligned_le16(&scanresp->bssdescriptsize);

	lbs_deb_scan("scan response: %d BSSs (%d bytes); resp size %d bytes\n",
			scanresp->nr_sets, bsssize, le16_to_cpu(resp->size));

	अगर (scanresp->nr_sets == 0) अणु
		ret = 0;
		जाओ करोne;
	पूर्ण

	/*
	 * The general layout of the scan response is described in chapter
	 * 5.7.1. Basically we have a common part, then any number of BSS
	 * descriptor sections. Finally we have section with the same number
	 * of TSFs.
	 *
	 * cmd_ds_802_11_scan_rsp
	 *   cmd_header
	 *   pos_size
	 *   nr_sets
	 *   bssdesc 1
	 *     bssid
	 *     rssi
	 *     बारtamp
	 *     पूर्णांकvl
	 *     capa
	 *     IEs
	 *   bssdesc 2
	 *   bssdesc n
	 *   MrvlIEtypes_TsfFimestamp_t
	 *     TSF क्रम BSS 1
	 *     TSF क्रम BSS 2
	 *     TSF क्रम BSS n
	 */

	pos = scanresp->bssdesc_and_tlvbuffer;

	lbs_deb_hex(LBS_DEB_SCAN, "SCAN_RSP", scanresp->bssdesc_and_tlvbuffer,
			scanresp->bssdescriptsize);

	tsfdesc = pos + bsssize;
	tsfsize = 4 + 8 * scanresp->nr_sets;
	lbs_deb_hex(LBS_DEB_SCAN, "SCAN_TSF", (u8 *) tsfdesc, tsfsize);

	/* Validity check: we expect a Marvell-Local TLV */
	i = get_unaligned_le16(tsfdesc);
	tsfdesc += 2;
	अगर (i != TLV_TYPE_TSFTIMESTAMP) अणु
		lbs_deb_scan("scan response: invalid TSF Timestamp %d\n", i);
		जाओ करोne;
	पूर्ण

	/*
	 * Validity check: the TLV holds TSF values with 8 bytes each, so
	 * the size in the TLV must match the nr_sets value
	 */
	i = get_unaligned_le16(tsfdesc);
	tsfdesc += 2;
	अगर (i / 8 != scanresp->nr_sets) अणु
		lbs_deb_scan("scan response: invalid number of TSF timestamp "
			     "sets (expected %d got %d)\n", scanresp->nr_sets,
			     i / 8);
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < scanresp->nr_sets; i++) अणु
		स्थिर u8 *bssid;
		स्थिर u8 *ie;
		पूर्णांक left;
		पूर्णांक ielen;
		पूर्णांक rssi;
		u16 पूर्णांकvl;
		u16 capa;
		पूर्णांक chan_no = -1;
		स्थिर u8 *ssid = शून्य;
		u8 ssid_len = 0;

		पूर्णांक len = get_unaligned_le16(pos);
		pos += 2;

		/* BSSID */
		bssid = pos;
		pos += ETH_ALEN;
		/* RSSI */
		rssi = *pos++;
		/* Packet समय stamp */
		pos += 8;
		/* Beacon पूर्णांकerval */
		पूर्णांकvl = get_unaligned_le16(pos);
		pos += 2;
		/* Capabilities */
		capa = get_unaligned_le16(pos);
		pos += 2;

		/* To find out the channel, we must parse the IEs */
		ie = pos;
		/*
		 * 6+1+8+2+2: size of BSSID, RSSI, समय stamp, beacon
		 * पूर्णांकerval, capabilities
		 */
		ielen = left = len - (6 + 1 + 8 + 2 + 2);
		जबतक (left >= 2) अणु
			u8 id, elen;
			id = *pos++;
			elen = *pos++;
			left -= 2;
			अगर (elen > left) अणु
				lbs_deb_scan("scan response: invalid IE fmt\n");
				जाओ करोne;
			पूर्ण

			अगर (id == WLAN_EID_DS_PARAMS)
				chan_no = *pos;
			अगर (id == WLAN_EID_SSID) अणु
				ssid = pos;
				ssid_len = elen;
			पूर्ण
			left -= elen;
			pos += elen;
		पूर्ण

		/* No channel, no luck */
		अगर (chan_no != -1) अणु
			काष्ठा wiphy *wiphy = priv->wdev->wiphy;
			पूर्णांक freq = ieee80211_channel_to_frequency(chan_no,
							NL80211_BAND_2GHZ);
			काष्ठा ieee80211_channel *channel =
				ieee80211_get_channel(wiphy, freq);

			lbs_deb_scan("scan: %pM, capa %04x, chan %2d, %*pE, %d dBm\n",
				     bssid, capa, chan_no, ssid_len, ssid,
				     LBS_SCAN_RSSI_TO_MBM(rssi)/100);

			अगर (channel &&
			    !(channel->flags & IEEE80211_CHAN_DISABLED)) अणु
				bss = cfg80211_inक्रमm_bss(wiphy, channel,
					CFG80211_BSS_FTYPE_UNKNOWN,
					bssid, get_unaligned_le64(tsfdesc),
					capa, पूर्णांकvl, ie, ielen,
					LBS_SCAN_RSSI_TO_MBM(rssi),
					GFP_KERNEL);
				cfg80211_put_bss(wiphy, bss);
			पूर्ण
		पूर्ण अन्यथा
			lbs_deb_scan("scan response: missing BSS channel IE\n");

		tsfdesc += 8;
	पूर्ण
	ret = 0;

 करोne:
	वापस ret;
पूर्ण


/*
 * Our scan command contains a TLV, स्थिरing of a SSID TLV, a channel list
 * TLV and a rates TLV. Determine the maximum size of them:
 */
#घोषणा LBS_SCAN_MAX_CMD_SIZE			\
	(माप(काष्ठा cmd_ds_802_11_scan)	\
	 + LBS_MAX_SSID_TLV_SIZE		\
	 + LBS_MAX_CHANNEL_LIST_TLV_SIZE	\
	 + LBS_MAX_RATES_TLV_SIZE)

/*
 * Assumes priv->scan_req is initialized and valid
 * Assumes priv->scan_channel is initialized
 */
अटल व्योम lbs_scan_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lbs_निजी *priv =
		container_of(work, काष्ठा lbs_निजी, scan_work.work);
	काष्ठा cmd_ds_802_11_scan *scan_cmd;
	u8 *tlv; /* poपूर्णांकer पूर्णांकo our current, growing TLV storage area */
	पूर्णांक last_channel;
	पूर्णांक running, carrier;

	scan_cmd = kzalloc(LBS_SCAN_MAX_CMD_SIZE, GFP_KERNEL);
	अगर (scan_cmd == शून्य)
		वापस;

	/* prepare fixed part of scan command */
	scan_cmd->bsstype = CMD_BSS_TYPE_ANY;

	/* stop network जबतक we're away from our मुख्य channel */
	running = !netअगर_queue_stopped(priv->dev);
	carrier = netअगर_carrier_ok(priv->dev);
	अगर (running)
		netअगर_stop_queue(priv->dev);
	अगर (carrier)
		netअगर_carrier_off(priv->dev);

	/* prepare fixed part of scan command */
	tlv = scan_cmd->tlvbuffer;

	/* add SSID TLV */
	अगर (priv->scan_req->n_ssids && priv->scan_req->ssids[0].ssid_len > 0)
		tlv += lbs_add_ssid_tlv(tlv,
					priv->scan_req->ssids[0].ssid,
					priv->scan_req->ssids[0].ssid_len);

	/* add channel TLVs */
	last_channel = priv->scan_channel + LBS_SCAN_BEFORE_NAP;
	अगर (last_channel > priv->scan_req->n_channels)
		last_channel = priv->scan_req->n_channels;
	tlv += lbs_add_channel_list_tlv(priv, tlv, last_channel,
		priv->scan_req->n_ssids);

	/* add rates TLV */
	tlv += lbs_add_supported_rates_tlv(tlv);

	अगर (priv->scan_channel < priv->scan_req->n_channels) अणु
		cancel_delayed_work(&priv->scan_work);
		अगर (netअगर_running(priv->dev))
			queue_delayed_work(priv->work_thपढ़ो, &priv->scan_work,
				msecs_to_jअगरfies(300));
	पूर्ण

	/* This is the final data we are about to send */
	scan_cmd->hdr.size = cpu_to_le16(tlv - (u8 *)scan_cmd);
	lbs_deb_hex(LBS_DEB_SCAN, "SCAN_CMD", (व्योम *)scan_cmd,
		    माप(*scan_cmd));
	lbs_deb_hex(LBS_DEB_SCAN, "SCAN_TLV", scan_cmd->tlvbuffer,
		    tlv - scan_cmd->tlvbuffer);

	__lbs_cmd(priv, CMD_802_11_SCAN, &scan_cmd->hdr,
		le16_to_cpu(scan_cmd->hdr.size),
		lbs_ret_scan, 0);

	अगर (priv->scan_channel >= priv->scan_req->n_channels) अणु
		/* Mark scan करोne */
		cancel_delayed_work(&priv->scan_work);
		lbs_scan_करोne(priv);
	पूर्ण

	/* Restart network */
	अगर (carrier)
		netअगर_carrier_on(priv->dev);
	अगर (running && !priv->tx_pending_len)
		netअगर_wake_queue(priv->dev);

	kमुक्त(scan_cmd);

	/* Wake up anything रुकोing on scan completion */
	अगर (priv->scan_req == शून्य) अणु
		lbs_deb_scan("scan: waking up waiters\n");
		wake_up_all(&priv->scan_q);
	पूर्ण
पूर्ण

अटल व्योम _पूर्णांकernal_start_scan(काष्ठा lbs_निजी *priv, bool पूर्णांकernal,
	काष्ठा cfg80211_scan_request *request)
अणु
	lbs_deb_scan("scan: ssids %d, channels %d, ie_len %zd\n",
		request->n_ssids, request->n_channels, request->ie_len);

	priv->scan_channel = 0;
	priv->scan_req = request;
	priv->पूर्णांकernal_scan = पूर्णांकernal;

	queue_delayed_work(priv->work_thपढ़ो, &priv->scan_work,
		msecs_to_jअगरfies(50));
पूर्ण

/*
 * Clean up priv->scan_req.  Should be used to handle the allocation details.
 */
व्योम lbs_scan_करोne(काष्ठा lbs_निजी *priv)
अणु
	WARN_ON(!priv->scan_req);

	अगर (priv->पूर्णांकernal_scan) अणु
		kमुक्त(priv->scan_req);
	पूर्ण अन्यथा अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = false,
		पूर्ण;

		cfg80211_scan_करोne(priv->scan_req, &info);
	पूर्ण

	priv->scan_req = शून्य;
पूर्ण

अटल पूर्णांक lbs_cfg_scan(काष्ठा wiphy *wiphy,
	काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा lbs_निजी *priv = wiphy_priv(wiphy);
	पूर्णांक ret = 0;

	अगर (priv->scan_req || delayed_work_pending(&priv->scan_work)) अणु
		/* old scan request not yet processed */
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	_पूर्णांकernal_start_scan(priv, false, request);

	अगर (priv->surpriseहटाओd)
		ret = -EIO;

 out:
	वापस ret;
पूर्ण




/*
 * Events
 */

व्योम lbs_send_disconnect_notअगरication(काष्ठा lbs_निजी *priv,
				      bool locally_generated)
अणु
	cfg80211_disconnected(priv->dev, 0, शून्य, 0, locally_generated,
			      GFP_KERNEL);
पूर्ण

व्योम lbs_send_mic_failureevent(काष्ठा lbs_निजी *priv, u32 event)
अणु
	cfg80211_michael_mic_failure(priv->dev,
		priv->assoc_bss,
		event == MACREG_INT_CODE_MIC_ERR_MULTICAST ?
			NL80211_KEYTYPE_GROUP :
			NL80211_KEYTYPE_PAIRWISE,
		-1,
		शून्य,
		GFP_KERNEL);
पूर्ण




/*
 * Connect/disconnect
 */


/*
 * This हटाओs all WEP keys
 */
अटल पूर्णांक lbs_हटाओ_wep_keys(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा cmd_ds_802_11_set_wep cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.keyindex = cpu_to_le16(priv->wep_tx_key);
	cmd.action = cpu_to_le16(CMD_ACT_REMOVE);

	ret = lbs_cmd_with_response(priv, CMD_802_11_SET_WEP, &cmd);

	वापस ret;
पूर्ण

/*
 * Set WEP keys
 */
अटल पूर्णांक lbs_set_wep_keys(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा cmd_ds_802_11_set_wep cmd;
	पूर्णांक i;
	पूर्णांक ret;

	/*
	 * command         13 00
	 * size            50 00
	 * sequence        xx xx
	 * result          00 00
	 * action          02 00     ACT_ADD
	 * transmit key    00 00
	 * type क्रम key 1  01        WEP40
	 * type क्रम key 2  00
	 * type क्रम key 3  00
	 * type क्रम key 4  00
	 * key 1           39 39 39 39 39 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 * key 2           00 00 00 00 00 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 * key 3           00 00 00 00 00 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 * key 4           00 00 00 00 00 00 00 00
	 */
	अगर (priv->wep_key_len[0] || priv->wep_key_len[1] ||
	    priv->wep_key_len[2] || priv->wep_key_len[3]) अणु
		/* Only set wep keys अगर we have at least one of them */
		स_रखो(&cmd, 0, माप(cmd));
		cmd.hdr.size = cpu_to_le16(माप(cmd));
		cmd.keyindex = cpu_to_le16(priv->wep_tx_key);
		cmd.action = cpu_to_le16(CMD_ACT_ADD);

		क्रम (i = 0; i < 4; i++) अणु
			चयन (priv->wep_key_len[i]) अणु
			हाल WLAN_KEY_LEN_WEP40:
				cmd.keytype[i] = CMD_TYPE_WEP_40_BIT;
				अवरोध;
			हाल WLAN_KEY_LEN_WEP104:
				cmd.keytype[i] = CMD_TYPE_WEP_104_BIT;
				अवरोध;
			शेष:
				cmd.keytype[i] = 0;
				अवरोध;
			पूर्ण
			स_नकल(cmd.keymaterial[i], priv->wep_key[i],
			       priv->wep_key_len[i]);
		पूर्ण

		ret = lbs_cmd_with_response(priv, CMD_802_11_SET_WEP, &cmd);
	पूर्ण अन्यथा अणु
		/* Otherwise हटाओ all wep keys */
		ret = lbs_हटाओ_wep_keys(priv);
	पूर्ण

	वापस ret;
पूर्ण


/*
 * Enable/Disable RSN status
 */
अटल पूर्णांक lbs_enable_rsn(काष्ठा lbs_निजी *priv, पूर्णांक enable)
अणु
	काष्ठा cmd_ds_802_11_enable_rsn cmd;
	पूर्णांक ret;

	/*
	 * cmd       2f 00
	 * size      0c 00
	 * sequence  xx xx
	 * result    00 00
	 * action    01 00    ACT_SET
	 * enable    01 00
	 */
	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	cmd.enable = cpu_to_le16(enable);

	ret = lbs_cmd_with_response(priv, CMD_802_11_ENABLE_RSN, &cmd);

	वापस ret;
पूर्ण


/*
 * Set WPA/WPA key material
 */

/*
 * like "struct cmd_ds_802_11_key_material", but with cmd_header. Once we
 * get rid of WEXT, this should go पूर्णांकo host.h
 */

काष्ठा cmd_key_material अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	काष्ठा MrvlIEtype_keyParamSet param;
पूर्ण __packed;

अटल पूर्णांक lbs_set_key_material(काष्ठा lbs_निजी *priv,
				पूर्णांक key_type, पूर्णांक key_info,
				स्थिर u8 *key, u16 key_len)
अणु
	काष्ठा cmd_key_material cmd;
	पूर्णांक ret;

	/*
	 * Example क्रम WPA (TKIP):
	 *
	 * cmd       5e 00
	 * size      34 00
	 * sequence  xx xx
	 * result    00 00
	 * action    01 00
	 * TLV type  00 01    key param
	 * length    00 26
	 * key type  01 00    TKIP
	 * key info  06 00    UNICAST | ENABLED
	 * key len   20 00
	 * key       32 bytes
	 */
	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	cmd.param.type = cpu_to_le16(TLV_TYPE_KEY_MATERIAL);
	cmd.param.length = cpu_to_le16(माप(cmd.param) - 4);
	cmd.param.keytypeid = cpu_to_le16(key_type);
	cmd.param.keyinfo = cpu_to_le16(key_info);
	cmd.param.keylen = cpu_to_le16(key_len);
	अगर (key && key_len)
		स_नकल(cmd.param.key, key, key_len);

	ret = lbs_cmd_with_response(priv, CMD_802_11_KEY_MATERIAL, &cmd);

	वापस ret;
पूर्ण


/*
 * Sets the auth type (खोलो, shared, etc) in the firmware. That
 * we use CMD_802_11_AUTHENTICATE is misleading, this firmware
 * command करोesn't send an authentication frame at all, it just
 * stores the auth_type.
 */
अटल पूर्णांक lbs_set_authtype(काष्ठा lbs_निजी *priv,
			    काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा cmd_ds_802_11_authenticate cmd;
	पूर्णांक ret;

	/*
	 * cmd        11 00
	 * size       19 00
	 * sequence   xx xx
	 * result     00 00
	 * BSS id     00 13 19 80 da 30
	 * auth type  00
	 * reserved   00 00 00 00 00 00 00 00 00 00
	 */
	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	अगर (sme->bssid)
		स_नकल(cmd.bssid, sme->bssid, ETH_ALEN);
	/* convert auth_type */
	ret = lbs_auth_to_authtype(sme->auth_type);
	अगर (ret < 0)
		जाओ करोne;

	cmd.authtype = ret;
	ret = lbs_cmd_with_response(priv, CMD_802_11_AUTHENTICATE, &cmd);

 करोne:
	वापस ret;
पूर्ण


/*
 * Create association request
 */
#घोषणा LBS_ASSOC_MAX_CMD_SIZE                     \
	(माप(काष्ठा cmd_ds_802_11_associate)    \
	 - 512 /* cmd_ds_802_11_associate.iebuf */ \
	 + LBS_MAX_SSID_TLV_SIZE                   \
	 + LBS_MAX_CHANNEL_TLV_SIZE                \
	 + LBS_MAX_CF_PARAM_TLV_SIZE               \
	 + LBS_MAX_AUTH_TYPE_TLV_SIZE              \
	 + LBS_MAX_WPA_TLV_SIZE)

अटल पूर्णांक lbs_associate(काष्ठा lbs_निजी *priv,
		काष्ठा cfg80211_bss *bss,
		काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा cmd_ds_802_11_associate_response *resp;
	काष्ठा cmd_ds_802_11_associate *cmd = kzalloc(LBS_ASSOC_MAX_CMD_SIZE,
						      GFP_KERNEL);
	स्थिर u8 *ssid_eid;
	माप_प्रकार len, resp_ie_len;
	पूर्णांक status;
	पूर्णांक ret;
	u8 *pos;
	u8 *पंचांगp;

	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण
	pos = &cmd->iebuf[0];

	/*
	 * cmd              50 00
	 * length           34 00
	 * sequence         xx xx
	 * result           00 00
	 * BSS id           00 13 19 80 da 30
	 * capabilities     11 00
	 * listen पूर्णांकerval  0a 00
	 * beacon पूर्णांकerval  00 00
	 * DTIM period      00
	 * TLVs             xx   (up to 512 bytes)
	 */
	cmd->hdr.command = cpu_to_le16(CMD_802_11_ASSOCIATE);

	/* Fill in अटल fields */
	स_नकल(cmd->bssid, bss->bssid, ETH_ALEN);
	cmd->listenपूर्णांकerval = cpu_to_le16(MRVDRV_DEFAULT_LISTEN_INTERVAL);
	cmd->capability = cpu_to_le16(bss->capability);

	/* add SSID TLV */
	rcu_पढ़ो_lock();
	ssid_eid = ieee80211_bss_get_ie(bss, WLAN_EID_SSID);
	अगर (ssid_eid)
		pos += lbs_add_ssid_tlv(pos, ssid_eid + 2, ssid_eid[1]);
	अन्यथा
		lbs_deb_assoc("no SSID\n");
	rcu_पढ़ो_unlock();

	/* add DS param TLV */
	अगर (bss->channel)
		pos += lbs_add_channel_tlv(pos, bss->channel->hw_value);
	अन्यथा
		lbs_deb_assoc("no channel\n");

	/* add (empty) CF param TLV */
	pos += lbs_add_cf_param_tlv(pos);

	/* add rates TLV */
	पंचांगp = pos + 4; /* skip Marvell IE header */
	pos += lbs_add_common_rates_tlv(pos, bss);
	lbs_deb_hex(LBS_DEB_ASSOC, "Common Rates", पंचांगp, pos - पंचांगp);

	/* add auth type TLV */
	अगर (MRVL_FW_MAJOR_REV(priv->fwrelease) >= 9)
		pos += lbs_add_auth_type_tlv(pos, sme->auth_type);

	/* add WPA/WPA2 TLV */
	अगर (sme->ie && sme->ie_len)
		pos += lbs_add_wpa_tlv(pos, sme->ie, sme->ie_len);

	len = (माप(*cmd) - माप(cmd->iebuf)) +
		(u16)(pos - (u8 *) &cmd->iebuf);
	cmd->hdr.size = cpu_to_le16(len);

	lbs_deb_hex(LBS_DEB_ASSOC, "ASSOC_CMD", (u8 *) cmd,
			le16_to_cpu(cmd->hdr.size));

	/* store क्रम later use */
	स_नकल(priv->assoc_bss, bss->bssid, ETH_ALEN);

	ret = lbs_cmd_with_response(priv, CMD_802_11_ASSOCIATE, cmd);
	अगर (ret)
		जाओ करोne;

	/* generate connect message to cfg80211 */

	resp = (व्योम *) cmd; /* recast क्रम easier field access */
	status = le16_to_cpu(resp->statuscode);

	/* Older FW versions map the IEEE 802.11 Status Code in the association
	 * response to the following values वापसed in resp->statuscode:
	 *
	 *    IEEE Status Code                Marvell Status Code
	 *    0                       ->      0x0000 ASSOC_RESULT_SUCCESS
	 *    13                      ->      0x0004 ASSOC_RESULT_AUTH_REFUSED
	 *    14                      ->      0x0004 ASSOC_RESULT_AUTH_REFUSED
	 *    15                      ->      0x0004 ASSOC_RESULT_AUTH_REFUSED
	 *    16                      ->      0x0004 ASSOC_RESULT_AUTH_REFUSED
	 *    others                  ->      0x0003 ASSOC_RESULT_REFUSED
	 *
	 * Other response codes:
	 *    0x0001 -> ASSOC_RESULT_INVALID_PARAMETERS (unused)
	 *    0x0002 -> ASSOC_RESULT_TIMEOUT (पूर्णांकernal समयr expired रुकोing क्रम
	 *                                    association response from the AP)
	 */
	अगर (MRVL_FW_MAJOR_REV(priv->fwrelease) <= 8) अणु
		चयन (status) अणु
		हाल 0:
			अवरोध;
		हाल 1:
			lbs_deb_assoc("invalid association parameters\n");
			status = WLAN_STATUS_CAPS_UNSUPPORTED;
			अवरोध;
		हाल 2:
			lbs_deb_assoc("timer expired while waiting for AP\n");
			status = WLAN_STATUS_AUTH_TIMEOUT;
			अवरोध;
		हाल 3:
			lbs_deb_assoc("association refused by AP\n");
			status = WLAN_STATUS_ASSOC_DENIED_UNSPEC;
			अवरोध;
		हाल 4:
			lbs_deb_assoc("authentication refused by AP\n");
			status = WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION;
			अवरोध;
		शेष:
			lbs_deb_assoc("association failure %d\n", status);
			/* v5 OLPC firmware करोes वापस the AP status code अगर
			 * it's not one of the values above.  Let that through.
			 */
			अवरोध;
		पूर्ण
	पूर्ण

	lbs_deb_assoc("status %d, statuscode 0x%04x, capability 0x%04x, "
		      "aid 0x%04x\n", status, le16_to_cpu(resp->statuscode),
		      le16_to_cpu(resp->capability), le16_to_cpu(resp->aid));

	resp_ie_len = le16_to_cpu(resp->hdr.size)
		- माप(resp->hdr)
		- 6;
	cfg80211_connect_result(priv->dev,
				priv->assoc_bss,
				sme->ie, sme->ie_len,
				resp->iebuf, resp_ie_len,
				status,
				GFP_KERNEL);

	अगर (status == 0) अणु
		/* TODO: get rid of priv->connect_status */
		priv->connect_status = LBS_CONNECTED;
		netअगर_carrier_on(priv->dev);
		अगर (!priv->tx_pending_len)
			netअगर_tx_wake_all_queues(priv->dev);
	पूर्ण

	kमुक्त(cmd);
करोne:
	वापस ret;
पूर्ण

अटल काष्ठा cfg80211_scan_request *
_new_connect_scan_req(काष्ठा wiphy *wiphy, काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा cfg80211_scan_request *creq = शून्य;
	पूर्णांक i, n_channels = ieee80211_get_num_supported_channels(wiphy);
	क्रमागत nl80211_band band;

	creq = kzalloc(माप(*creq) + माप(काष्ठा cfg80211_ssid) +
		       n_channels * माप(व्योम *),
		       GFP_ATOMIC);
	अगर (!creq)
		वापस शून्य;

	/* SSIDs come after channels */
	creq->ssids = (व्योम *)&creq->channels[n_channels];
	creq->n_channels = n_channels;
	creq->n_ssids = 1;

	/* Scan all available channels */
	i = 0;
	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		पूर्णांक j;

		अगर (!wiphy->bands[band])
			जारी;

		क्रम (j = 0; j < wiphy->bands[band]->n_channels; j++) अणु
			/* ignore disabled channels */
			अगर (wiphy->bands[band]->channels[j].flags &
						IEEE80211_CHAN_DISABLED)
				जारी;

			creq->channels[i] = &wiphy->bands[band]->channels[j];
			i++;
		पूर्ण
	पूर्ण
	अगर (i) अणु
		/* Set real number of channels specअगरied in creq->channels[] */
		creq->n_channels = i;

		/* Scan क्रम the SSID we're going to connect to */
		स_नकल(creq->ssids[0].ssid, sme->ssid, sme->ssid_len);
		creq->ssids[0].ssid_len = sme->ssid_len;
	पूर्ण अन्यथा अणु
		/* No channels found... */
		kमुक्त(creq);
		creq = शून्य;
	पूर्ण

	वापस creq;
पूर्ण

अटल पूर्णांक lbs_cfg_connect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			   काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा lbs_निजी *priv = wiphy_priv(wiphy);
	काष्ठा cfg80211_bss *bss = शून्य;
	पूर्णांक ret = 0;
	u8 preamble = RADIO_PREAMBLE_SHORT;

	अगर (dev == priv->mesh_dev)
		वापस -EOPNOTSUPP;

	अगर (!sme->bssid) अणु
		काष्ठा cfg80211_scan_request *creq;

		/*
		 * Scan क्रम the requested network after रुकोing क्रम existing
		 * scans to finish.
		 */
		lbs_deb_assoc("assoc: waiting for existing scans\n");
		रुको_event_पूर्णांकerruptible_समयout(priv->scan_q,
						 (priv->scan_req == शून्य),
						 (15 * HZ));

		creq = _new_connect_scan_req(wiphy, sme);
		अगर (!creq) अणु
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण

		lbs_deb_assoc("assoc: scanning for compatible AP\n");
		_पूर्णांकernal_start_scan(priv, true, creq);

		lbs_deb_assoc("assoc: waiting for scan to complete\n");
		रुको_event_पूर्णांकerruptible_समयout(priv->scan_q,
						 (priv->scan_req == शून्य),
						 (15 * HZ));
		lbs_deb_assoc("assoc: scanning completed\n");
	पूर्ण

	/* Find the BSS we want using available scan results */
	bss = cfg80211_get_bss(wiphy, sme->channel, sme->bssid,
		sme->ssid, sme->ssid_len, IEEE80211_BSS_TYPE_ESS,
		IEEE80211_PRIVACY_ANY);
	अगर (!bss) अणु
		wiphy_err(wiphy, "assoc: bss %pM not in scan results\n",
			  sme->bssid);
		ret = -ENOENT;
		जाओ करोne;
	पूर्ण
	lbs_deb_assoc("trying %pM\n", bss->bssid);
	lbs_deb_assoc("cipher 0x%x, key index %d, key len %d\n",
		      sme->crypto.cipher_group,
		      sme->key_idx, sme->key_len);

	/* As this is a new connection, clear locally stored WEP keys */
	priv->wep_tx_key = 0;
	स_रखो(priv->wep_key, 0, माप(priv->wep_key));
	स_रखो(priv->wep_key_len, 0, माप(priv->wep_key_len));

	/* set/हटाओ WEP keys */
	चयन (sme->crypto.cipher_group) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		/* Store provided WEP keys in priv-> */
		priv->wep_tx_key = sme->key_idx;
		priv->wep_key_len[sme->key_idx] = sme->key_len;
		स_नकल(priv->wep_key[sme->key_idx], sme->key, sme->key_len);
		/* Set WEP keys and WEP mode */
		lbs_set_wep_keys(priv);
		priv->mac_control |= CMD_ACT_MAC_WEP_ENABLE;
		lbs_set_mac_control(priv);
		/* No RSN mode क्रम WEP */
		lbs_enable_rsn(priv, 0);
		अवरोध;
	हाल 0: /* there's no WLAN_CIPHER_SUITE_NONE definition */
		/*
		 * If we करोn't have no WEP, no WPA and no WPA2,
		 * we हटाओ all keys like in the WPA/WPA2 setup,
		 * we just करोn't set RSN.
		 *
		 * Thereक्रमe: fall-through
		 */
	हाल WLAN_CIPHER_SUITE_TKIP:
	हाल WLAN_CIPHER_SUITE_CCMP:
		/* Remove WEP keys and WEP mode */
		lbs_हटाओ_wep_keys(priv);
		priv->mac_control &= ~CMD_ACT_MAC_WEP_ENABLE;
		lbs_set_mac_control(priv);

		/* clear the WPA/WPA2 keys */
		lbs_set_key_material(priv,
			KEY_TYPE_ID_WEP, /* करोesn't matter */
			KEY_INFO_WPA_UNICAST,
			शून्य, 0);
		lbs_set_key_material(priv,
			KEY_TYPE_ID_WEP, /* करोesn't matter */
			KEY_INFO_WPA_MCAST,
			शून्य, 0);
		/* RSN mode क्रम WPA/WPA2 */
		lbs_enable_rsn(priv, sme->crypto.cipher_group != 0);
		अवरोध;
	शेष:
		wiphy_err(wiphy, "unsupported cipher group 0x%x\n",
			  sme->crypto.cipher_group);
		ret = -ENOTSUPP;
		जाओ करोne;
	पूर्ण

	ret = lbs_set_authtype(priv, sme);
	अगर (ret == -ENOTSUPP) अणु
		wiphy_err(wiphy, "unsupported authtype 0x%x\n", sme->auth_type);
		जाओ करोne;
	पूर्ण

	lbs_set_radio(priv, preamble, 1);

	/* Do the actual association */
	ret = lbs_associate(priv, bss, sme);

 करोne:
	अगर (bss)
		cfg80211_put_bss(wiphy, bss);
	वापस ret;
पूर्ण

पूर्णांक lbs_disconnect(काष्ठा lbs_निजी *priv, u16 reason)
अणु
	काष्ठा cmd_ds_802_11_deauthenticate cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	/* Mildly ugly to use a locally store my own BSSID ... */
	स_नकल(cmd.macaddr, &priv->assoc_bss, ETH_ALEN);
	cmd.reasoncode = cpu_to_le16(reason);

	ret = lbs_cmd_with_response(priv, CMD_802_11_DEAUTHENTICATE, &cmd);
	अगर (ret)
		वापस ret;

	cfg80211_disconnected(priv->dev,
			reason,
			शून्य, 0, true,
			GFP_KERNEL);
	priv->connect_status = LBS_DISCONNECTED;

	वापस 0;
पूर्ण

अटल पूर्णांक lbs_cfg_disconnect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
	u16 reason_code)
अणु
	काष्ठा lbs_निजी *priv = wiphy_priv(wiphy);

	अगर (dev == priv->mesh_dev)
		वापस -EOPNOTSUPP;

	/* store क्रम lbs_cfg_ret_disconnect() */
	priv->disassoc_reason = reason_code;

	वापस lbs_disconnect(priv, reason_code);
पूर्ण

अटल पूर्णांक lbs_cfg_set_शेष_key(काष्ठा wiphy *wiphy,
				   काष्ठा net_device *netdev,
				   u8 key_index, bool unicast,
				   bool multicast)
अणु
	काष्ठा lbs_निजी *priv = wiphy_priv(wiphy);

	अगर (netdev == priv->mesh_dev)
		वापस -EOPNOTSUPP;

	अगर (key_index != priv->wep_tx_key) अणु
		lbs_deb_assoc("set_default_key: to %d\n", key_index);
		priv->wep_tx_key = key_index;
		lbs_set_wep_keys(priv);
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक lbs_cfg_add_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			   u8 idx, bool pairwise, स्थिर u8 *mac_addr,
			   काष्ठा key_params *params)
अणु
	काष्ठा lbs_निजी *priv = wiphy_priv(wiphy);
	u16 key_info;
	u16 key_type;
	पूर्णांक ret = 0;

	अगर (netdev == priv->mesh_dev)
		वापस -EOPNOTSUPP;

	lbs_deb_assoc("add_key: cipher 0x%x, mac_addr %pM\n",
		      params->cipher, mac_addr);
	lbs_deb_assoc("add_key: key index %d, key len %d\n",
		      idx, params->key_len);
	अगर (params->key_len)
		lbs_deb_hex(LBS_DEB_CFG80211, "KEY",
			    params->key, params->key_len);

	lbs_deb_assoc("add_key: seq len %d\n", params->seq_len);
	अगर (params->seq_len)
		lbs_deb_hex(LBS_DEB_CFG80211, "SEQ",
			    params->seq, params->seq_len);

	चयन (params->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		/* actually compare अगर something has changed ... */
		अगर ((priv->wep_key_len[idx] != params->key_len) ||
			स_भेद(priv->wep_key[idx],
			       params->key, params->key_len) != 0) अणु
			priv->wep_key_len[idx] = params->key_len;
			स_नकल(priv->wep_key[idx],
			       params->key, params->key_len);
			lbs_set_wep_keys(priv);
		पूर्ण
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
	हाल WLAN_CIPHER_SUITE_CCMP:
		key_info = KEY_INFO_WPA_ENABLED | ((idx == 0)
						   ? KEY_INFO_WPA_UNICAST
						   : KEY_INFO_WPA_MCAST);
		key_type = (params->cipher == WLAN_CIPHER_SUITE_TKIP)
			? KEY_TYPE_ID_TKIP
			: KEY_TYPE_ID_AES;
		lbs_set_key_material(priv,
				     key_type,
				     key_info,
				     params->key, params->key_len);
		अवरोध;
	शेष:
		wiphy_err(wiphy, "unhandled cipher 0x%x\n", params->cipher);
		ret = -ENOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण


अटल पूर्णांक lbs_cfg_del_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			   u8 key_index, bool pairwise, स्थिर u8 *mac_addr)
अणु

	lbs_deb_assoc("del_key: key_idx %d, mac_addr %pM\n",
		      key_index, mac_addr);

#अगर_घोषित TODO
	काष्ठा lbs_निजी *priv = wiphy_priv(wiphy);
	/*
	 * I think can keep this a NO-OP, because:

	 * - we clear all keys whenever we करो lbs_cfg_connect() anyway
	 * - neither "iw" nor "wpa_supplicant" won't call this during
	 *   an ongoing connection
	 * - TODO: but I have to check अगर this is still true when
	 *   I set the AP to periodic re-keying
	 * - we've not kzallec() something when we've added a key at
	 *   lbs_cfg_connect() or lbs_cfg_add_key().
	 *
	 * This causes lbs_cfg_del_key() only called at disconnect समय,
	 * where we'd just waste समय deleting a key that is not going
	 * to be used anyway.
	 */
	अगर (key_index < 3 && priv->wep_key_len[key_index]) अणु
		priv->wep_key_len[key_index] = 0;
		lbs_set_wep_keys(priv);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण


/*
 * Get station
 */

अटल पूर्णांक lbs_cfg_get_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       स्थिर u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा lbs_निजी *priv = wiphy_priv(wiphy);
	s8 संकेत, noise;
	पूर्णांक ret;
	माप_प्रकार i;

	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BYTES) |
			 BIT_ULL(NL80211_STA_INFO_TX_PACKETS) |
			 BIT_ULL(NL80211_STA_INFO_RX_BYTES) |
			 BIT_ULL(NL80211_STA_INFO_RX_PACKETS);
	sinfo->tx_bytes = priv->dev->stats.tx_bytes;
	sinfo->tx_packets = priv->dev->stats.tx_packets;
	sinfo->rx_bytes = priv->dev->stats.rx_bytes;
	sinfo->rx_packets = priv->dev->stats.rx_packets;

	/* Get current RSSI */
	ret = lbs_get_rssi(priv, &संकेत, &noise);
	अगर (ret == 0) अणु
		sinfo->संकेत = संकेत;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
	पूर्ण

	/* Convert priv->cur_rate from hw_value to NL80211 value */
	क्रम (i = 0; i < ARRAY_SIZE(lbs_rates); i++) अणु
		अगर (priv->cur_rate == lbs_rates[i].hw_value) अणु
			sinfo->txrate.legacy = lbs_rates[i].bitrate;
			sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण




/*
 * Change पूर्णांकerface
 */

अटल पूर्णांक lbs_change_पूर्णांकf(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
	क्रमागत nl80211_अगरtype type,
	       काष्ठा vअगर_params *params)
अणु
	काष्ठा lbs_निजी *priv = wiphy_priv(wiphy);
	पूर्णांक ret = 0;

	अगर (dev == priv->mesh_dev)
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (priv->अगरace_running)
		ret = lbs_set_अगरace_type(priv, type);

	अगर (!ret)
		priv->wdev->अगरtype = type;

	वापस ret;
पूर्ण



/*
 * IBSS (Ad-Hoc)
 */

/*
 * The firmware needs the following bits masked out of the beacon-derived
 * capability field when associating/joining to a BSS:
 *  9 (QoS), 11 (APSD), 12 (unused), 14 (unused), 15 (unused)
 */
#घोषणा CAPINFO_MASK (~(0xda00))


अटल व्योम lbs_join_post(काष्ठा lbs_निजी *priv,
			  काष्ठा cfg80211_ibss_params *params,
			  u8 *bssid, u16 capability)
अणु
	u8 fake_ie[2 + IEEE80211_MAX_SSID_LEN + /* ssid */
		   2 + 4 +                      /* basic rates */
		   2 + 1 +                      /* DS parameter */
		   2 + 2 +                      /* atim */
		   2 + 8];                      /* extended rates */
	u8 *fake = fake_ie;
	काष्ठा cfg80211_bss *bss;

	/*
	 * For cfg80211_inक्रमm_bss, we'll need a fake IE, as we can't get
	 * the real IE from the firmware. So we fabricate a fake IE based on
	 * what the firmware actually sends (snअगरfed with wireshark).
	 */
	/* Fake SSID IE */
	*fake++ = WLAN_EID_SSID;
	*fake++ = params->ssid_len;
	स_नकल(fake, params->ssid, params->ssid_len);
	fake += params->ssid_len;
	/* Fake supported basic rates IE */
	*fake++ = WLAN_EID_SUPP_RATES;
	*fake++ = 4;
	*fake++ = 0x82;
	*fake++ = 0x84;
	*fake++ = 0x8b;
	*fake++ = 0x96;
	/* Fake DS channel IE */
	*fake++ = WLAN_EID_DS_PARAMS;
	*fake++ = 1;
	*fake++ = params->chandef.chan->hw_value;
	/* Fake IBSS params IE */
	*fake++ = WLAN_EID_IBSS_PARAMS;
	*fake++ = 2;
	*fake++ = 0; /* ATIM=0 */
	*fake++ = 0;
	/* Fake extended rates IE, TODO: करोn't add this क्रम 802.11b only,
	 * but I करोn't know how this could be checked */
	*fake++ = WLAN_EID_EXT_SUPP_RATES;
	*fake++ = 8;
	*fake++ = 0x0c;
	*fake++ = 0x12;
	*fake++ = 0x18;
	*fake++ = 0x24;
	*fake++ = 0x30;
	*fake++ = 0x48;
	*fake++ = 0x60;
	*fake++ = 0x6c;
	lbs_deb_hex(LBS_DEB_CFG80211, "IE", fake_ie, fake - fake_ie);

	bss = cfg80211_inक्रमm_bss(priv->wdev->wiphy,
				  params->chandef.chan,
				  CFG80211_BSS_FTYPE_UNKNOWN,
				  bssid,
				  0,
				  capability,
				  params->beacon_पूर्णांकerval,
				  fake_ie, fake - fake_ie,
				  0, GFP_KERNEL);
	cfg80211_put_bss(priv->wdev->wiphy, bss);

	cfg80211_ibss_joined(priv->dev, bssid, params->chandef.chan,
			     GFP_KERNEL);

	/* TODO: consider करोing this at MACREG_INT_CODE_LINK_SENSED समय */
	priv->connect_status = LBS_CONNECTED;
	netअगर_carrier_on(priv->dev);
	अगर (!priv->tx_pending_len)
		netअगर_wake_queue(priv->dev);
पूर्ण

अटल पूर्णांक lbs_ibss_join_existing(काष्ठा lbs_निजी *priv,
	काष्ठा cfg80211_ibss_params *params,
	काष्ठा cfg80211_bss *bss)
अणु
	स्थिर u8 *rates_eid;
	काष्ठा cmd_ds_802_11_ad_hoc_join cmd;
	u8 preamble = RADIO_PREAMBLE_SHORT;
	पूर्णांक ret = 0;
	पूर्णांक hw, i;
	u8 rates_max;
	u8 *rates;

	/* TODO: set preamble based on scan result */
	ret = lbs_set_radio(priv, preamble, 1);
	अगर (ret)
		जाओ out;

	/*
	 * Example CMD_802_11_AD_HOC_JOIN command:
	 *
	 * command         2c 00         CMD_802_11_AD_HOC_JOIN
	 * size            65 00
	 * sequence        xx xx
	 * result          00 00
	 * bssid           02 27 27 97 2f 96
	 * ssid            49 42 53 53 00 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 * type            02            CMD_BSS_TYPE_IBSS
	 * beacon period   64 00
	 * dtim period     00
	 * बारtamp       00 00 00 00 00 00 00 00
	 * स_स्थानीय       00 00 00 00 00 00 00 00
	 * IE DS           03
	 * IE DS len       01
	 * IE DS channel   01
	 * reserveed       00 00 00 00
	 * IE IBSS         06
	 * IE IBSS len     02
	 * IE IBSS atim    00 00
	 * reserved        00 00 00 00
	 * capability      02 00
	 * rates           82 84 8b 96 0c 12 18 24 30 48 60 6c 00
	 * fail समयout    ff 00
	 * probe delay     00 00
	 */
	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));

	स_नकल(cmd.bss.bssid, bss->bssid, ETH_ALEN);
	स_नकल(cmd.bss.ssid, params->ssid, params->ssid_len);
	cmd.bss.type = CMD_BSS_TYPE_IBSS;
	cmd.bss.beaconperiod = cpu_to_le16(params->beacon_पूर्णांकerval);
	cmd.bss.ds.header.id = WLAN_EID_DS_PARAMS;
	cmd.bss.ds.header.len = 1;
	cmd.bss.ds.channel = params->chandef.chan->hw_value;
	cmd.bss.ibss.header.id = WLAN_EID_IBSS_PARAMS;
	cmd.bss.ibss.header.len = 2;
	cmd.bss.ibss.atimwinकरोw = 0;
	cmd.bss.capability = cpu_to_le16(bss->capability & CAPINFO_MASK);

	/* set rates to the पूर्णांकersection of our rates and the rates in the
	   bss */
	rcu_पढ़ो_lock();
	rates_eid = ieee80211_bss_get_ie(bss, WLAN_EID_SUPP_RATES);
	अगर (!rates_eid) अणु
		lbs_add_rates(cmd.bss.rates);
	पूर्ण अन्यथा अणु
		rates_max = rates_eid[1];
		अगर (rates_max > MAX_RATES) अणु
			lbs_deb_join("invalid rates");
			rcu_पढ़ो_unlock();
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		rates = cmd.bss.rates;
		क्रम (hw = 0; hw < ARRAY_SIZE(lbs_rates); hw++) अणु
			u8 hw_rate = lbs_rates[hw].bitrate / 5;
			क्रम (i = 0; i < rates_max; i++) अणु
				अगर (hw_rate == (rates_eid[i+2] & 0x7f)) अणु
					u8 rate = rates_eid[i+2];
					अगर (rate == 0x02 || rate == 0x04 ||
					    rate == 0x0b || rate == 0x16)
						rate |= 0x80;
					*rates++ = rate;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	/* Only v8 and below support setting this */
	अगर (MRVL_FW_MAJOR_REV(priv->fwrelease) <= 8) अणु
		cmd.failसमयout = cpu_to_le16(MRVDRV_ASSOCIATION_TIME_OUT);
		cmd.probedelay = cpu_to_le16(CMD_SCAN_PROBE_DELAY_TIME);
	पूर्ण
	ret = lbs_cmd_with_response(priv, CMD_802_11_AD_HOC_JOIN, &cmd);
	अगर (ret)
		जाओ out;

	/*
	 * This is a sample response to CMD_802_11_AD_HOC_JOIN:
	 *
	 * response        2c 80
	 * size            09 00
	 * sequence        xx xx
	 * result          00 00
	 * reserved        00
	 */
	lbs_join_post(priv, params, bss->bssid, bss->capability);

 out:
	वापस ret;
पूर्ण



अटल पूर्णांक lbs_ibss_start_new(काष्ठा lbs_निजी *priv,
	काष्ठा cfg80211_ibss_params *params)
अणु
	काष्ठा cmd_ds_802_11_ad_hoc_start cmd;
	काष्ठा cmd_ds_802_11_ad_hoc_result *resp =
		(काष्ठा cmd_ds_802_11_ad_hoc_result *) &cmd;
	u8 preamble = RADIO_PREAMBLE_SHORT;
	पूर्णांक ret = 0;
	u16 capability;

	ret = lbs_set_radio(priv, preamble, 1);
	अगर (ret)
		जाओ out;

	/*
	 * Example CMD_802_11_AD_HOC_START command:
	 *
	 * command         2b 00         CMD_802_11_AD_HOC_START
	 * size            b1 00
	 * sequence        xx xx
	 * result          00 00
	 * ssid            54 45 53 54 00 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 * bss type        02
	 * beacon period   64 00
	 * dtim period     00
	 * IE IBSS         06
	 * IE IBSS len     02
	 * IE IBSS atim    00 00
	 * reserved        00 00 00 00
	 * IE DS           03
	 * IE DS len       01
	 * IE DS channel   01
	 * reserved        00 00 00 00
	 * probe delay     00 00
	 * capability      02 00
	 * rates           82 84 8b 96   (basic rates with have bit 7 set)
	 *                 0c 12 18 24 30 48 60 6c
	 * padding         100 bytes
	 */
	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	स_नकल(cmd.ssid, params->ssid, params->ssid_len);
	cmd.bsstype = CMD_BSS_TYPE_IBSS;
	cmd.beaconperiod = cpu_to_le16(params->beacon_पूर्णांकerval);
	cmd.ibss.header.id = WLAN_EID_IBSS_PARAMS;
	cmd.ibss.header.len = 2;
	cmd.ibss.atimwinकरोw = 0;
	cmd.ds.header.id = WLAN_EID_DS_PARAMS;
	cmd.ds.header.len = 1;
	cmd.ds.channel = params->chandef.chan->hw_value;
	/* Only v8 and below support setting probe delay */
	अगर (MRVL_FW_MAJOR_REV(priv->fwrelease) <= 8)
		cmd.probedelay = cpu_to_le16(CMD_SCAN_PROBE_DELAY_TIME);
	/* TODO: mix in WLAN_CAPABILITY_PRIVACY */
	capability = WLAN_CAPABILITY_IBSS;
	cmd.capability = cpu_to_le16(capability);
	lbs_add_rates(cmd.rates);


	ret = lbs_cmd_with_response(priv, CMD_802_11_AD_HOC_START, &cmd);
	अगर (ret)
		जाओ out;

	/*
	 * This is a sample response to CMD_802_11_AD_HOC_JOIN:
	 *
	 * response        2b 80
	 * size            14 00
	 * sequence        xx xx
	 * result          00 00
	 * reserved        00
	 * bssid           02 2b 7b 0f 86 0e
	 */
	lbs_join_post(priv, params, resp->bssid, capability);

 out:
	वापस ret;
पूर्ण


अटल पूर्णांक lbs_join_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		काष्ठा cfg80211_ibss_params *params)
अणु
	काष्ठा lbs_निजी *priv = wiphy_priv(wiphy);
	पूर्णांक ret = 0;
	काष्ठा cfg80211_bss *bss;

	अगर (dev == priv->mesh_dev)
		वापस -EOPNOTSUPP;

	अगर (!params->chandef.chan) अणु
		ret = -ENOTSUPP;
		जाओ out;
	पूर्ण

	ret = lbs_set_channel(priv, params->chandef.chan->hw_value);
	अगर (ret)
		जाओ out;

	/* Search अगर someone is beaconing. This assumes that the
	 * bss list is populated alपढ़ोy */
	bss = cfg80211_get_bss(wiphy, params->chandef.chan, params->bssid,
		params->ssid, params->ssid_len,
		IEEE80211_BSS_TYPE_IBSS, IEEE80211_PRIVACY_ANY);

	अगर (bss) अणु
		ret = lbs_ibss_join_existing(priv, params, bss);
		cfg80211_put_bss(wiphy, bss);
	पूर्ण अन्यथा
		ret = lbs_ibss_start_new(priv, params);


 out:
	वापस ret;
पूर्ण


अटल पूर्णांक lbs_leave_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *dev)
अणु
	काष्ठा lbs_निजी *priv = wiphy_priv(wiphy);
	काष्ठा cmd_ds_802_11_ad_hoc_stop cmd;
	पूर्णांक ret = 0;

	अगर (dev == priv->mesh_dev)
		वापस -EOPNOTSUPP;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	ret = lbs_cmd_with_response(priv, CMD_802_11_AD_HOC_STOP, &cmd);

	/* TODO: consider करोing this at MACREG_INT_CODE_ADHOC_BCN_LOST समय */
	lbs_mac_event_disconnected(priv, true);

	वापस ret;
पूर्ण



अटल पूर्णांक lbs_set_घातer_mgmt(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      bool enabled, पूर्णांक समयout)
अणु
	काष्ठा lbs_निजी *priv = wiphy_priv(wiphy);

	अगर  (!(priv->fwcapinfo & FW_CAPINFO_PS)) अणु
		अगर (!enabled)
			वापस 0;
		अन्यथा
			वापस -EINVAL;
	पूर्ण
	/* firmware करोes not work well with too दीर्घ latency with घातer saving
	 * enabled, so करो not enable it अगर there is only polling, no
	 * पूर्णांकerrupts (like in some sdio hosts which can only
	 * poll क्रम sdio irqs)
	 */
	अगर  (priv->is_polling) अणु
		अगर (!enabled)
			वापस 0;
		अन्यथा
			वापस -EINVAL;
	पूर्ण
	अगर (!enabled) अणु
		priv->psmode = LBS802_11POWERMODECAM;
		अगर (priv->psstate != PS_STATE_FULL_POWER)
			lbs_set_ps_mode(priv,
					PS_MODE_ACTION_EXIT_PS,
					true);
		वापस 0;
	पूर्ण
	अगर (priv->psmode != LBS802_11POWERMODECAM)
		वापस 0;
	priv->psmode = LBS802_11POWERMODEMAX_PSP;
	अगर (priv->connect_status == LBS_CONNECTED)
		lbs_set_ps_mode(priv, PS_MODE_ACTION_ENTER_PS, true);
	वापस 0;
पूर्ण

/*
 * Initialization
 */

अटल स्थिर काष्ठा cfg80211_ops lbs_cfg80211_ops = अणु
	.set_monitor_channel = lbs_cfg_set_monitor_channel,
	.libertas_set_mesh_channel = lbs_cfg_set_mesh_channel,
	.scan = lbs_cfg_scan,
	.connect = lbs_cfg_connect,
	.disconnect = lbs_cfg_disconnect,
	.add_key = lbs_cfg_add_key,
	.del_key = lbs_cfg_del_key,
	.set_शेष_key = lbs_cfg_set_शेष_key,
	.get_station = lbs_cfg_get_station,
	.change_भव_पूर्णांकf = lbs_change_पूर्णांकf,
	.join_ibss = lbs_join_ibss,
	.leave_ibss = lbs_leave_ibss,
	.set_घातer_mgmt = lbs_set_घातer_mgmt,
पूर्ण;


/*
 * At this समय lbs_निजी *priv करोesn't even exist, so we just allocate
 * memory and करोn't initialize the wiphy further. This is postponed until we
 * can talk to the firmware and happens at registration समय in
 * lbs_cfg_wiphy_रेजिस्टर().
 */
काष्ठा wireless_dev *lbs_cfg_alloc(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा wireless_dev *wdev;

	wdev = kzalloc(माप(काष्ठा wireless_dev), GFP_KERNEL);
	अगर (!wdev)
		वापस ERR_PTR(-ENOMEM);

	wdev->wiphy = wiphy_new(&lbs_cfg80211_ops, माप(काष्ठा lbs_निजी));
	अगर (!wdev->wiphy) अणु
		dev_err(dev, "cannot allocate wiphy\n");
		ret = -ENOMEM;
		जाओ err_wiphy_new;
	पूर्ण

	वापस wdev;

 err_wiphy_new:
	kमुक्त(wdev);
	वापस ERR_PTR(ret);
पूर्ण


अटल व्योम lbs_cfg_set_regulatory_hपूर्णांक(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा region_code_mapping अणु
		स्थिर अक्षर *cn;
		पूर्णांक code;
	पूर्ण;

	/* Section 5.17.2 */
	अटल स्थिर काष्ठा region_code_mapping regmap[] = अणु
		अणु"US ", 0x10पूर्ण, /* US FCC */
		अणु"CA ", 0x20पूर्ण, /* Canada */
		अणु"EU ", 0x30पूर्ण, /* ETSI   */
		अणु"ES ", 0x31पूर्ण, /* Spain  */
		अणु"FR ", 0x32पूर्ण, /* France */
		अणु"JP ", 0x40पूर्ण, /* Japan  */
	पूर्ण;
	माप_प्रकार i;

	क्रम (i = 0; i < ARRAY_SIZE(regmap); i++)
		अगर (regmap[i].code == priv->regioncode) अणु
			regulatory_hपूर्णांक(priv->wdev->wiphy, regmap[i].cn);
			अवरोध;
		पूर्ण
पूर्ण

अटल व्योम lbs_reg_notअगरier(काष्ठा wiphy *wiphy,
			     काष्ठा regulatory_request *request)
अणु
	काष्ठा lbs_निजी *priv = wiphy_priv(wiphy);

	स_नकल(priv->country_code, request->alpha2, माप(request->alpha2));
	अगर (lbs_अगरace_active(priv))
		lbs_set_11d_करोमुख्य_info(priv);
पूर्ण

/*
 * This function get's called after lbs_setup_firmware() determined the
 * firmware capabities. So we can setup the wiphy according to our
 * hardware/firmware.
 */
पूर्णांक lbs_cfg_रेजिस्टर(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा wireless_dev *wdev = priv->wdev;
	पूर्णांक ret;

	wdev->wiphy->max_scan_ssids = 1;
	wdev->wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_MBM;

	wdev->wiphy->पूर्णांकerface_modes =
			BIT(NL80211_IFTYPE_STATION) |
			BIT(NL80211_IFTYPE_ADHOC);
	अगर (lbs_rtap_supported(priv))
		wdev->wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_MONITOR);
	अगर (lbs_mesh_activated(priv))
		wdev->wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_MESH_POINT);

	wdev->wiphy->bands[NL80211_BAND_2GHZ] = &lbs_band_2ghz;

	/*
	 * We could check priv->fwcapinfo && FW_CAPINFO_WPA, but I have
	 * never seen a firmware without WPA
	 */
	wdev->wiphy->cipher_suites = cipher_suites;
	wdev->wiphy->n_cipher_suites = ARRAY_SIZE(cipher_suites);
	wdev->wiphy->reg_notअगरier = lbs_reg_notअगरier;

	ret = wiphy_रेजिस्टर(wdev->wiphy);
	अगर (ret < 0)
		pr_err("cannot register wiphy device\n");

	priv->wiphy_रेजिस्टरed = true;

	ret = रेजिस्टर_netdev(priv->dev);
	अगर (ret)
		pr_err("cannot register network device\n");

	INIT_DELAYED_WORK(&priv->scan_work, lbs_scan_worker);

	lbs_cfg_set_regulatory_hपूर्णांक(priv);

	वापस ret;
पूर्ण

व्योम lbs_scan_deinit(काष्ठा lbs_निजी *priv)
अणु
	cancel_delayed_work_sync(&priv->scan_work);
पूर्ण


व्योम lbs_cfg_मुक्त(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा wireless_dev *wdev = priv->wdev;

	अगर (!wdev)
		वापस;

	अगर (priv->wiphy_रेजिस्टरed)
		wiphy_unरेजिस्टर(wdev->wiphy);

	अगर (wdev->wiphy)
		wiphy_मुक्त(wdev->wiphy);

	kमुक्त(wdev);
पूर्ण
