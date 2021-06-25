<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

/* Toplevel file. Relies on dhd_linux.c to send commands to the करोngle. */

#समावेश <linux/kernel.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/cfg80211.h>
#समावेश <net/netlink.h>
#समावेश <uapi/linux/अगर_arp.h>

#समावेश <brcmu_utils.h>
#समावेश <defs.h>
#समावेश <brcmu_wअगरi.h>
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "tracepoint.h"
#समावेश "fwil_types.h"
#समावेश "p2p.h"
#समावेश "btcoex.h"
#समावेश "pno.h"
#समावेश "fwsignal.h"
#समावेश "cfg80211.h"
#समावेश "feature.h"
#समावेश "fwil.h"
#समावेश "proto.h"
#समावेश "vendor.h"
#समावेश "bus.h"
#समावेश "common.h"

#घोषणा BRCMF_SCAN_IE_LEN_MAX		2048

#घोषणा WPA_OUI				"\x00\x50\xF2"	/* WPA OUI */
#घोषणा WPA_OUI_TYPE			1
#घोषणा RSN_OUI				"\x00\x0F\xAC"	/* RSN OUI */
#घोषणा	WME_OUI_TYPE			2
#घोषणा WPS_OUI_TYPE			4

#घोषणा VS_IE_FIXED_HDR_LEN		6
#घोषणा WPA_IE_VERSION_LEN		2
#घोषणा WPA_IE_MIN_OUI_LEN		4
#घोषणा WPA_IE_SUITE_COUNT_LEN		2

#घोषणा WPA_CIPHER_NONE			0	/* None */
#घोषणा WPA_CIPHER_WEP_40		1	/* WEP (40-bit) */
#घोषणा WPA_CIPHER_TKIP			2	/* TKIP: शेष क्रम WPA */
#घोषणा WPA_CIPHER_AES_CCM		4	/* AES (CCM) */
#घोषणा WPA_CIPHER_WEP_104		5	/* WEP (104-bit) */

#घोषणा RSN_AKM_NONE			0	/* None (IBSS) */
#घोषणा RSN_AKM_UNSPECIFIED		1	/* Over 802.1x */
#घोषणा RSN_AKM_PSK			2	/* Pre-shared Key */
#घोषणा RSN_AKM_SHA256_1X		5	/* SHA256, 802.1X */
#घोषणा RSN_AKM_SHA256_PSK		6	/* SHA256, Pre-shared Key */
#घोषणा RSN_AKM_SAE			8	/* SAE */
#घोषणा RSN_CAP_LEN			2	/* Length of RSN capabilities */
#घोषणा RSN_CAP_PTK_REPLAY_CNTR_MASK	(BIT(2) | BIT(3))
#घोषणा RSN_CAP_MFPR_MASK		BIT(6)
#घोषणा RSN_CAP_MFPC_MASK		BIT(7)
#घोषणा RSN_PMKID_COUNT_LEN		2

#घोषणा VNDR_IE_CMD_LEN			4	/* length of the set command
						 * string :"add", "del" (+ NUL)
						 */
#घोषणा VNDR_IE_COUNT_OFFSET		4
#घोषणा VNDR_IE_PKTFLAG_OFFSET		8
#घोषणा VNDR_IE_VSIE_OFFSET		12
#घोषणा VNDR_IE_HDR_SIZE		12
#घोषणा VNDR_IE_PARSE_LIMIT		5

#घोषणा	DOT11_MGMT_HDR_LEN		24	/* d11 management header len */
#घोषणा	DOT11_BCN_PRB_FIXED_LEN		12	/* beacon/probe fixed length */

#घोषणा BRCMF_SCAN_JOIN_ACTIVE_DWELL_TIME_MS	320
#घोषणा BRCMF_SCAN_JOIN_PASSIVE_DWELL_TIME_MS	400
#घोषणा BRCMF_SCAN_JOIN_PROBE_INTERVAL_MS	20

#घोषणा BRCMF_SCAN_CHANNEL_TIME		40
#घोषणा BRCMF_SCAN_UNASSOC_TIME		40
#घोषणा BRCMF_SCAN_PASSIVE_TIME		120

#घोषणा BRCMF_ND_INFO_TIMEOUT		msecs_to_jअगरfies(2000)

#घोषणा BRCMF_PS_MAX_TIMEOUT_MS		2000

#घोषणा BRCMF_ASSOC_PARAMS_FIXED_SIZE \
	(माप(काष्ठा brcmf_assoc_params_le) - माप(u16))

अटल bool check_vअगर_up(काष्ठा brcmf_cfg80211_vअगर *vअगर)
अणु
	अगर (!test_bit(BRCMF_VIF_STATUS_READY, &vअगर->sme_state)) अणु
		brcmf_dbg(INFO, "device is not ready : status (%lu)\n",
			  vअगर->sme_state);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

#घोषणा RATE_TO_BASE100KBPS(rate)   (((rate) * 10) / 2)
#घोषणा RATETAB_ENT(_rateid, _flags) \
	अणु                                                               \
		.bitrate        = RATE_TO_BASE100KBPS(_rateid),     \
		.hw_value       = (_rateid),                            \
		.flags          = (_flags),                             \
	पूर्ण

अटल काष्ठा ieee80211_rate __wl_rates[] = अणु
	RATETAB_ENT(BRCM_RATE_1M, 0),
	RATETAB_ENT(BRCM_RATE_2M, IEEE80211_RATE_SHORT_PREAMBLE),
	RATETAB_ENT(BRCM_RATE_5M5, IEEE80211_RATE_SHORT_PREAMBLE),
	RATETAB_ENT(BRCM_RATE_11M, IEEE80211_RATE_SHORT_PREAMBLE),
	RATETAB_ENT(BRCM_RATE_6M, 0),
	RATETAB_ENT(BRCM_RATE_9M, 0),
	RATETAB_ENT(BRCM_RATE_12M, 0),
	RATETAB_ENT(BRCM_RATE_18M, 0),
	RATETAB_ENT(BRCM_RATE_24M, 0),
	RATETAB_ENT(BRCM_RATE_36M, 0),
	RATETAB_ENT(BRCM_RATE_48M, 0),
	RATETAB_ENT(BRCM_RATE_54M, 0),
पूर्ण;

#घोषणा wl_g_rates		(__wl_rates + 0)
#घोषणा wl_g_rates_size		ARRAY_SIZE(__wl_rates)
#घोषणा wl_a_rates		(__wl_rates + 4)
#घोषणा wl_a_rates_size		(wl_g_rates_size - 4)

#घोषणा CHAN2G(_channel, _freq) अणु				\
	.band			= NL80211_BAND_2GHZ,		\
	.center_freq		= (_freq),			\
	.hw_value		= (_channel),			\
	.max_antenna_gain	= 0,				\
	.max_घातer		= 30,				\
पूर्ण

#घोषणा CHAN5G(_channel) अणु					\
	.band			= NL80211_BAND_5GHZ,		\
	.center_freq		= 5000 + (5 * (_channel)),	\
	.hw_value		= (_channel),			\
	.max_antenna_gain	= 0,				\
	.max_घातer		= 30,				\
पूर्ण

अटल काष्ठा ieee80211_channel __wl_2ghz_channels[] = अणु
	CHAN2G(1, 2412), CHAN2G(2, 2417), CHAN2G(3, 2422), CHAN2G(4, 2427),
	CHAN2G(5, 2432), CHAN2G(6, 2437), CHAN2G(7, 2442), CHAN2G(8, 2447),
	CHAN2G(9, 2452), CHAN2G(10, 2457), CHAN2G(11, 2462), CHAN2G(12, 2467),
	CHAN2G(13, 2472), CHAN2G(14, 2484)
पूर्ण;

अटल काष्ठा ieee80211_channel __wl_5ghz_channels[] = अणु
	CHAN5G(34), CHAN5G(36), CHAN5G(38), CHAN5G(40), CHAN5G(42),
	CHAN5G(44), CHAN5G(46), CHAN5G(48), CHAN5G(52), CHAN5G(56),
	CHAN5G(60), CHAN5G(64), CHAN5G(100), CHAN5G(104), CHAN5G(108),
	CHAN5G(112), CHAN5G(116), CHAN5G(120), CHAN5G(124), CHAN5G(128),
	CHAN5G(132), CHAN5G(136), CHAN5G(140), CHAN5G(144), CHAN5G(149),
	CHAN5G(153), CHAN5G(157), CHAN5G(161), CHAN5G(165)
पूर्ण;

/* Band ढाँचाs duplicated per wiphy. The channel info
 * above is added to the band during setup.
 */
अटल स्थिर काष्ठा ieee80211_supported_band __wl_band_2ghz = अणु
	.band = NL80211_BAND_2GHZ,
	.bitrates = wl_g_rates,
	.n_bitrates = wl_g_rates_size,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_supported_band __wl_band_5ghz = अणु
	.band = NL80211_BAND_5GHZ,
	.bitrates = wl_a_rates,
	.n_bitrates = wl_a_rates_size,
पूर्ण;

/* This is to override regulatory करोमुख्यs defined in cfg80211 module (reg.c)
 * By शेष world regulatory करोमुख्य defined in reg.c माला_दो the flags
 * NL80211_RRF_NO_IR क्रम 5GHz channels (क्रम * 36..48 and 149..165).
 * With respect to these flags, wpa_supplicant करोesn't * start p2p
 * operations on 5GHz channels. All the changes in world regulatory
 * करोमुख्य are to be करोne here.
 */
अटल स्थिर काष्ठा ieee80211_regकरोमुख्य brcmf_regकरोm = अणु
	.n_reg_rules = 4,
	.alpha2 =  "99",
	.reg_rules = अणु
		/* IEEE 802.11b/g, channels 1..11 */
		REG_RULE(2412-10, 2472+10, 40, 6, 20, 0),
		/* If any */
		/* IEEE 802.11 channel 14 - Only JP enables
		 * this and क्रम 802.11b only
		 */
		REG_RULE(2484-10, 2484+10, 20, 6, 20, 0),
		/* IEEE 802.11a, channel 36..64 */
		REG_RULE(5150-10, 5350+10, 160, 6, 20, 0),
		/* IEEE 802.11a, channel 100..165 */
		REG_RULE(5470-10, 5850+10, 160, 6, 20, 0), पूर्ण
पूर्ण;

/* Note: brcmf_cipher_suites is an array of पूर्णांक defining which cipher suites
 * are supported. A poपूर्णांकer to this array and the number of entries is passed
 * on to upper layers. AES_CMAC defines whether or not the driver supports MFP.
 * So the cipher suite AES_CMAC has to be the last one in the array, and when
 * device करोes not support MFP then the number of suites will be decreased by 1
 */
अटल स्थिर u32 brcmf_cipher_suites[] = अणु
	WLAN_CIPHER_SUITE_WEP40,
	WLAN_CIPHER_SUITE_WEP104,
	WLAN_CIPHER_SUITE_TKIP,
	WLAN_CIPHER_SUITE_CCMP,
	/* Keep as last entry: */
	WLAN_CIPHER_SUITE_AES_CMAC
पूर्ण;

/* Venकरोr specअगरic ie. id = 221, oui and type defines exact ie */
काष्ठा brcmf_vs_tlv अणु
	u8 id;
	u8 len;
	u8 oui[3];
	u8 oui_type;
पूर्ण;

काष्ठा parsed_vndr_ie_info अणु
	u8 *ie_ptr;
	u32 ie_len;	/* total length including id & length field */
	काष्ठा brcmf_vs_tlv vndrie;
पूर्ण;

काष्ठा parsed_vndr_ies अणु
	u32 count;
	काष्ठा parsed_vndr_ie_info ie_info[VNDR_IE_PARSE_LIMIT];
पूर्ण;

अटल u8 nl80211_band_to_fwil(क्रमागत nl80211_band band)
अणु
	चयन (band) अणु
	हाल NL80211_BAND_2GHZ:
		वापस WLC_BAND_2G;
	हाल NL80211_BAND_5GHZ:
		वापस WLC_BAND_5G;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल u16 chandef_to_chanspec(काष्ठा brcmu_d11inf *d11inf,
			       काष्ठा cfg80211_chan_def *ch)
अणु
	काष्ठा brcmu_chan ch_inf;
	s32 primary_offset;

	brcmf_dbg(TRACE, "chandef: control %d center %d width %d\n",
		  ch->chan->center_freq, ch->center_freq1, ch->width);
	ch_inf.chnum = ieee80211_frequency_to_channel(ch->center_freq1);
	primary_offset = ch->chan->center_freq - ch->center_freq1;
	चयन (ch->width) अणु
	हाल NL80211_CHAN_WIDTH_20:
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		ch_inf.bw = BRCMU_CHAN_BW_20;
		WARN_ON(primary_offset != 0);
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		ch_inf.bw = BRCMU_CHAN_BW_40;
		अगर (primary_offset > 0)
			ch_inf.sb = BRCMU_CHAN_SB_U;
		अन्यथा
			ch_inf.sb = BRCMU_CHAN_SB_L;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		ch_inf.bw = BRCMU_CHAN_BW_80;
		अगर (primary_offset == -30)
			ch_inf.sb = BRCMU_CHAN_SB_LL;
		अन्यथा अगर (primary_offset == -10)
			ch_inf.sb = BRCMU_CHAN_SB_LU;
		अन्यथा अगर (primary_offset == 10)
			ch_inf.sb = BRCMU_CHAN_SB_UL;
		अन्यथा
			ch_inf.sb = BRCMU_CHAN_SB_UU;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_160:
		ch_inf.bw = BRCMU_CHAN_BW_160;
		अगर (primary_offset == -70)
			ch_inf.sb = BRCMU_CHAN_SB_LLL;
		अन्यथा अगर (primary_offset == -50)
			ch_inf.sb = BRCMU_CHAN_SB_LLU;
		अन्यथा अगर (primary_offset == -30)
			ch_inf.sb = BRCMU_CHAN_SB_LUL;
		अन्यथा अगर (primary_offset == -10)
			ch_inf.sb = BRCMU_CHAN_SB_LUU;
		अन्यथा अगर (primary_offset == 10)
			ch_inf.sb = BRCMU_CHAN_SB_ULL;
		अन्यथा अगर (primary_offset == 30)
			ch_inf.sb = BRCMU_CHAN_SB_ULU;
		अन्यथा अगर (primary_offset == 50)
			ch_inf.sb = BRCMU_CHAN_SB_UUL;
		अन्यथा
			ch_inf.sb = BRCMU_CHAN_SB_UUU;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80P80:
	हाल NL80211_CHAN_WIDTH_5:
	हाल NL80211_CHAN_WIDTH_10:
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
	चयन (ch->chan->band) अणु
	हाल NL80211_BAND_2GHZ:
		ch_inf.band = BRCMU_CHAN_BAND_2G;
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		ch_inf.band = BRCMU_CHAN_BAND_5G;
		अवरोध;
	हाल NL80211_BAND_60GHZ:
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
	d11inf->encchspec(&ch_inf);

	brcmf_dbg(TRACE, "chanspec: 0x%x\n", ch_inf.chspec);
	वापस ch_inf.chspec;
पूर्ण

u16 channel_to_chanspec(काष्ठा brcmu_d11inf *d11inf,
			काष्ठा ieee80211_channel *ch)
अणु
	काष्ठा brcmu_chan ch_inf;

	ch_inf.chnum = ieee80211_frequency_to_channel(ch->center_freq);
	ch_inf.bw = BRCMU_CHAN_BW_20;
	d11inf->encchspec(&ch_inf);

	वापस ch_inf.chspec;
पूर्ण

/* Traverse a string of 1-byte tag/1-byte length/variable-length value
 * triples, वापसing a poपूर्णांकer to the substring whose first element
 * matches tag
 */
अटल स्थिर काष्ठा brcmf_tlv *
brcmf_parse_tlvs(स्थिर व्योम *buf, पूर्णांक buflen, uपूर्णांक key)
अणु
	स्थिर काष्ठा brcmf_tlv *elt = buf;
	पूर्णांक totlen = buflen;

	/* find tagged parameter */
	जबतक (totlen >= TLV_HDR_LEN) अणु
		पूर्णांक len = elt->len;

		/* validate reमुख्यing totlen */
		अगर ((elt->id == key) && (totlen >= (len + TLV_HDR_LEN)))
			वापस elt;

		elt = (काष्ठा brcmf_tlv *)((u8 *)elt + (len + TLV_HDR_LEN));
		totlen -= (len + TLV_HDR_LEN);
	पूर्ण

	वापस शून्य;
पूर्ण

/* Is any of the tlvs the expected entry? If
 * not update the tlvs buffer poपूर्णांकer/length.
 */
अटल bool
brcmf_tlv_has_ie(स्थिर u8 *ie, स्थिर u8 **tlvs, u32 *tlvs_len,
		 स्थिर u8 *oui, u32 oui_len, u8 type)
अणु
	/* If the contents match the OUI and the type */
	अगर (ie[TLV_LEN_OFF] >= oui_len + 1 &&
	    !स_भेद(&ie[TLV_BODY_OFF], oui, oui_len) &&
	    type == ie[TLV_BODY_OFF + oui_len]) अणु
		वापस true;
	पूर्ण

	अगर (tlvs == शून्य)
		वापस false;
	/* poपूर्णांक to the next ie */
	ie += ie[TLV_LEN_OFF] + TLV_HDR_LEN;
	/* calculate the length of the rest of the buffer */
	*tlvs_len -= (पूर्णांक)(ie - *tlvs);
	/* update the poपूर्णांकer to the start of the buffer */
	*tlvs = ie;

	वापस false;
पूर्ण

अटल काष्ठा brcmf_vs_tlv *
brcmf_find_wpaie(स्थिर u8 *parse, u32 len)
अणु
	स्थिर काष्ठा brcmf_tlv *ie;

	जबतक ((ie = brcmf_parse_tlvs(parse, len, WLAN_EID_VENDOR_SPECIFIC))) अणु
		अगर (brcmf_tlv_has_ie((स्थिर u8 *)ie, &parse, &len,
				     WPA_OUI, TLV_OUI_LEN, WPA_OUI_TYPE))
			वापस (काष्ठा brcmf_vs_tlv *)ie;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा brcmf_vs_tlv *
brcmf_find_wpsie(स्थिर u8 *parse, u32 len)
अणु
	स्थिर काष्ठा brcmf_tlv *ie;

	जबतक ((ie = brcmf_parse_tlvs(parse, len, WLAN_EID_VENDOR_SPECIFIC))) अणु
		अगर (brcmf_tlv_has_ie((u8 *)ie, &parse, &len,
				     WPA_OUI, TLV_OUI_LEN, WPS_OUI_TYPE))
			वापस (काष्ठा brcmf_vs_tlv *)ie;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक brcmf_vअगर_change_validate(काष्ठा brcmf_cfg80211_info *cfg,
				     काष्ठा brcmf_cfg80211_vअगर *vअगर,
				     क्रमागत nl80211_अगरtype new_type)
अणु
	काष्ठा brcmf_cfg80211_vअगर *pos;
	bool check_combos = false;
	पूर्णांक ret = 0;
	काष्ठा अगरace_combination_params params = अणु
		.num_dअगरferent_channels = 1,
	पूर्ण;

	list_क्रम_each_entry(pos, &cfg->vअगर_list, list)
		अगर (pos == vअगर) अणु
			params.अगरtype_num[new_type]++;
		पूर्ण अन्यथा अणु
			/* concurrent पूर्णांकerfaces so need check combinations */
			check_combos = true;
			params.अगरtype_num[pos->wdev.अगरtype]++;
		पूर्ण

	अगर (check_combos)
		ret = cfg80211_check_combinations(cfg->wiphy, &params);

	वापस ret;
पूर्ण

अटल पूर्णांक brcmf_vअगर_add_validate(काष्ठा brcmf_cfg80211_info *cfg,
				  क्रमागत nl80211_अगरtype new_type)
अणु
	काष्ठा brcmf_cfg80211_vअगर *pos;
	काष्ठा अगरace_combination_params params = अणु
		.num_dअगरferent_channels = 1,
	पूर्ण;

	list_क्रम_each_entry(pos, &cfg->vअगर_list, list)
		params.अगरtype_num[pos->wdev.अगरtype]++;

	params.अगरtype_num[new_type]++;
	वापस cfg80211_check_combinations(cfg->wiphy, &params);
पूर्ण

अटल व्योम convert_key_from_CPU(काष्ठा brcmf_wsec_key *key,
				 काष्ठा brcmf_wsec_key_le *key_le)
अणु
	key_le->index = cpu_to_le32(key->index);
	key_le->len = cpu_to_le32(key->len);
	key_le->algo = cpu_to_le32(key->algo);
	key_le->flags = cpu_to_le32(key->flags);
	key_le->rxiv.hi = cpu_to_le32(key->rxiv.hi);
	key_le->rxiv.lo = cpu_to_le16(key->rxiv.lo);
	key_le->iv_initialized = cpu_to_le32(key->iv_initialized);
	स_नकल(key_le->data, key->data, माप(key->data));
	स_नकल(key_le->ea, key->ea, माप(key->ea));
पूर्ण

अटल पूर्णांक
send_key_to_करोngle(काष्ठा brcmf_अगर *अगरp, काष्ठा brcmf_wsec_key *key)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	पूर्णांक err;
	काष्ठा brcmf_wsec_key_le key_le;

	convert_key_from_CPU(key, &key_le);

	brcmf_netdev_रुको_pend8021x(अगरp);

	err = brcmf_fil_bsscfg_data_set(अगरp, "wsec_key", &key_le,
					माप(key_le));

	अगर (err)
		bphy_err(drvr, "wsec_key error (%d)\n", err);
	वापस err;
पूर्ण

अटल व्योम
brcmf_cfg80211_update_proto_addr_mode(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	काष्ठा brcmf_अगर *अगरp;

	vअगर = container_of(wdev, काष्ठा brcmf_cfg80211_vअगर, wdev);
	अगरp = vअगर->अगरp;

	अगर ((wdev->अगरtype == NL80211_IFTYPE_ADHOC) ||
	    (wdev->अगरtype == NL80211_IFTYPE_AP) ||
	    (wdev->अगरtype == NL80211_IFTYPE_P2P_GO))
		brcmf_proto_configure_addr_mode(अगरp->drvr, अगरp->अगरidx,
						ADDR_सूचीECT);
	अन्यथा
		brcmf_proto_configure_addr_mode(अगरp->drvr, अगरp->अगरidx,
						ADDR_INसूचीECT);
पूर्ण

अटल पूर्णांक brcmf_get_first_मुक्त_bsscfgidx(काष्ठा brcmf_pub *drvr)
अणु
	पूर्णांक bsscfgidx;

	क्रम (bsscfgidx = 0; bsscfgidx < BRCMF_MAX_IFS; bsscfgidx++) अणु
		/* bsscfgidx 1 is reserved क्रम legacy P2P */
		अगर (bsscfgidx == 1)
			जारी;
		अगर (!drvr->अगरlist[bsscfgidx])
			वापस bsscfgidx;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक brcmf_cfg80211_request_ap_अगर(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_mbss_ssid_le mbss_ssid_le;
	पूर्णांक bsscfgidx;
	पूर्णांक err;

	स_रखो(&mbss_ssid_le, 0, माप(mbss_ssid_le));
	bsscfgidx = brcmf_get_first_मुक्त_bsscfgidx(अगरp->drvr);
	अगर (bsscfgidx < 0)
		वापस bsscfgidx;

	mbss_ssid_le.bsscfgidx = cpu_to_le32(bsscfgidx);
	mbss_ssid_le.SSID_len = cpu_to_le32(5);
	प्र_लिखो(mbss_ssid_le.SSID, "ssid%d" , bsscfgidx);

	err = brcmf_fil_bsscfg_data_set(अगरp, "bsscfg:ssid", &mbss_ssid_le,
					माप(mbss_ssid_le));
	अगर (err < 0)
		bphy_err(drvr, "setting ssid failed %d\n", err);

	वापस err;
पूर्ण

/**
 * brcmf_ap_add_vअगर() - create a new AP भव पूर्णांकerface क्रम multiple BSS
 *
 * @wiphy: wiphy device of new पूर्णांकerface.
 * @name: name of the new पूर्णांकerface.
 * @params: contains mac address क्रम AP device.
 */
अटल
काष्ठा wireless_dev *brcmf_ap_add_vअगर(काष्ठा wiphy *wiphy, स्थिर अक्षर *name,
				      काष्ठा vअगर_params *params)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(cfg_to_ndev(cfg));
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	पूर्णांक err;

	अगर (brcmf_cfg80211_vअगर_event_armed(cfg))
		वापस ERR_PTR(-EBUSY);

	brcmf_dbg(INFO, "Adding vif \"%s\"\n", name);

	vअगर = brcmf_alloc_vअगर(cfg, NL80211_IFTYPE_AP);
	अगर (IS_ERR(vअगर))
		वापस (काष्ठा wireless_dev *)vअगर;

	brcmf_cfg80211_arm_vअगर_event(cfg, vअगर);

	err = brcmf_cfg80211_request_ap_अगर(अगरp);
	अगर (err) अणु
		brcmf_cfg80211_arm_vअगर_event(cfg, शून्य);
		जाओ fail;
	पूर्ण

	/* रुको क्रम firmware event */
	err = brcmf_cfg80211_रुको_vअगर_event(cfg, BRCMF_E_IF_ADD,
					    BRCMF_VIF_EVENT_TIMEOUT);
	brcmf_cfg80211_arm_vअगर_event(cfg, शून्य);
	अगर (!err) अणु
		bphy_err(drvr, "timeout occurred\n");
		err = -EIO;
		जाओ fail;
	पूर्ण

	/* पूर्णांकerface created in firmware */
	अगरp = vअगर->अगरp;
	अगर (!अगरp) अणु
		bphy_err(drvr, "no if pointer provided\n");
		err = -ENOENT;
		जाओ fail;
	पूर्ण

	म_नकलन(अगरp->ndev->name, name, माप(अगरp->ndev->name) - 1);
	err = brcmf_net_attach(अगरp, true);
	अगर (err) अणु
		bphy_err(drvr, "Registering netdevice failed\n");
		मुक्त_netdev(अगरp->ndev);
		जाओ fail;
	पूर्ण

	वापस &अगरp->vअगर->wdev;

fail:
	brcmf_मुक्त_vअगर(vअगर);
	वापस ERR_PTR(err);
पूर्ण

अटल bool brcmf_is_apmode(काष्ठा brcmf_cfg80211_vअगर *vअगर)
अणु
	क्रमागत nl80211_अगरtype अगरtype;

	अगरtype = vअगर->wdev.अगरtype;
	वापस अगरtype == NL80211_IFTYPE_AP || अगरtype == NL80211_IFTYPE_P2P_GO;
पूर्ण

अटल bool brcmf_is_ibssmode(काष्ठा brcmf_cfg80211_vअगर *vअगर)
अणु
	वापस vअगर->wdev.अगरtype == NL80211_IFTYPE_ADHOC;
पूर्ण

/**
 * brcmf_mon_add_vअगर() - create monitor mode भव पूर्णांकerface
 *
 * @wiphy: wiphy device of new पूर्णांकerface.
 * @name: name of the new पूर्णांकerface.
 */
अटल काष्ठा wireless_dev *brcmf_mon_add_vअगर(काष्ठा wiphy *wiphy,
					      स्थिर अक्षर *name)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	काष्ठा net_device *ndev;
	काष्ठा brcmf_अगर *अगरp;
	पूर्णांक err;

	अगर (cfg->pub->mon_अगर) अणु
		err = -EEXIST;
		जाओ err_out;
	पूर्ण

	vअगर = brcmf_alloc_vअगर(cfg, NL80211_IFTYPE_MONITOR);
	अगर (IS_ERR(vअगर)) अणु
		err = PTR_ERR(vअगर);
		जाओ err_out;
	पूर्ण

	ndev = alloc_netdev(माप(*अगरp), name, NET_NAME_UNKNOWN, ether_setup);
	अगर (!ndev) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_vअगर;
	पूर्ण
	ndev->type = ARPHRD_IEEE80211_RADIOTAP;
	ndev->ieee80211_ptr = &vअगर->wdev;
	ndev->needs_मुक्त_netdev = true;
	ndev->priv_deकाष्ठाor = brcmf_cfg80211_मुक्त_netdev;
	SET_NETDEV_DEV(ndev, wiphy_dev(cfg->wiphy));

	अगरp = netdev_priv(ndev);
	अगरp->vअगर = vअगर;
	अगरp->ndev = ndev;
	अगरp->drvr = cfg->pub;

	vअगर->अगरp = अगरp;
	vअगर->wdev.netdev = ndev;

	err = brcmf_net_mon_attach(अगरp);
	अगर (err) अणु
		brcmf_err("Failed to attach %s device\n", ndev->name);
		मुक्त_netdev(ndev);
		जाओ err_मुक्त_vअगर;
	पूर्ण

	cfg->pub->mon_अगर = अगरp;

	वापस &vअगर->wdev;

err_मुक्त_vअगर:
	brcmf_मुक्त_vअगर(vअगर);
err_out:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक brcmf_mon_del_vअगर(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा net_device *ndev = wdev->netdev;

	ndev->netdev_ops->nकरो_stop(ndev);

	brcmf_net_detach(ndev, true);

	cfg->pub->mon_अगर = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा wireless_dev *brcmf_cfg80211_add_अगरace(काष्ठा wiphy *wiphy,
						     स्थिर अक्षर *name,
						     अचिन्हित अक्षर name_assign_type,
						     क्रमागत nl80211_अगरtype type,
						     काष्ठा vअगर_params *params)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा wireless_dev *wdev;
	पूर्णांक err;

	brcmf_dbg(TRACE, "enter: %s type %d\n", name, type);
	err = brcmf_vअगर_add_validate(wiphy_to_cfg(wiphy), type);
	अगर (err) अणु
		bphy_err(drvr, "iface validation failed: err=%d\n", err);
		वापस ERR_PTR(err);
	पूर्ण
	चयन (type) अणु
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_WDS:
	हाल NL80211_IFTYPE_MESH_POINT:
		वापस ERR_PTR(-EOPNOTSUPP);
	हाल NL80211_IFTYPE_MONITOR:
		वापस brcmf_mon_add_vअगर(wiphy, name);
	हाल NL80211_IFTYPE_AP:
		wdev = brcmf_ap_add_vअगर(wiphy, name, params);
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_P2P_DEVICE:
		wdev = brcmf_p2p_add_vअगर(wiphy, name, name_assign_type, type, params);
		अवरोध;
	हाल NL80211_IFTYPE_UNSPECIFIED:
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (IS_ERR(wdev))
		bphy_err(drvr, "add iface %s type %d failed: err=%d\n", name,
			 type, (पूर्णांक)PTR_ERR(wdev));
	अन्यथा
		brcmf_cfg80211_update_proto_addr_mode(wdev);

	वापस wdev;
पूर्ण

अटल व्योम brcmf_scan_config_mpc(काष्ठा brcmf_अगर *अगरp, पूर्णांक mpc)
अणु
	अगर (brcmf_feat_is_quirk_enabled(अगरp, BRCMF_FEAT_QUIRK_NEED_MPC))
		brcmf_set_mpc(अगरp, mpc);
पूर्ण

व्योम brcmf_set_mpc(काष्ठा brcmf_अगर *अगरp, पूर्णांक mpc)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 err = 0;

	अगर (check_vअगर_up(अगरp->vअगर)) अणु
		err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "mpc", mpc);
		अगर (err) अणु
			bphy_err(drvr, "fail to set mpc\n");
			वापस;
		पूर्ण
		brcmf_dbg(INFO, "MPC : %d\n", mpc);
	पूर्ण
पूर्ण

s32 brcmf_notअगरy_escan_complete(काष्ठा brcmf_cfg80211_info *cfg,
				काष्ठा brcmf_अगर *अगरp, bool पातed,
				bool fw_पात)
अणु
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_scan_params_le params_le;
	काष्ठा cfg80211_scan_request *scan_request;
	u64 reqid;
	u32 bucket;
	s32 err = 0;

	brcmf_dbg(SCAN, "Enter\n");

	/* clear scan request, because the FW पात can cause a second call */
	/* to this functon and might cause a द्विगुन cfg80211_scan_करोne      */
	scan_request = cfg->scan_request;
	cfg->scan_request = शून्य;

	अगर (समयr_pending(&cfg->escan_समयout))
		del_समयr_sync(&cfg->escan_समयout);

	अगर (fw_पात) अणु
		/* Do a scan पात to stop the driver's scan engine */
		brcmf_dbg(SCAN, "ABORT scan in firmware\n");
		स_रखो(&params_le, 0, माप(params_le));
		eth_broadcast_addr(params_le.bssid);
		params_le.bss_type = DOT11_BSSTYPE_ANY;
		params_le.scan_type = 0;
		params_le.channel_num = cpu_to_le32(1);
		params_le.nprobes = cpu_to_le32(1);
		params_le.active_समय = cpu_to_le32(-1);
		params_le.passive_समय = cpu_to_le32(-1);
		params_le.home_समय = cpu_to_le32(-1);
		/* Scan is पातed by setting channel_list[0] to -1 */
		params_le.channel_list[0] = cpu_to_le16(-1);
		/* E-Scan (or anyother type) can be पातed by SCAN */
		err = brcmf_fil_cmd_data_set(अगरp, BRCMF_C_SCAN,
					     &params_le, माप(params_le));
		अगर (err)
			bphy_err(drvr, "Scan abort failed\n");
	पूर्ण

	brcmf_scan_config_mpc(अगरp, 1);

	/*
	 * e-scan can be initiated पूर्णांकernally
	 * which takes precedence.
	 */
	अगर (cfg->पूर्णांक_escan_map) अणु
		brcmf_dbg(SCAN, "scheduled scan completed (%x)\n",
			  cfg->पूर्णांक_escan_map);
		जबतक (cfg->पूर्णांक_escan_map) अणु
			bucket = __ffs(cfg->पूर्णांक_escan_map);
			cfg->पूर्णांक_escan_map &= ~BIT(bucket);
			reqid = brcmf_pno_find_reqid_by_bucket(cfg->pno,
							       bucket);
			अगर (!पातed) अणु
				brcmf_dbg(SCAN, "report results: reqid=%llu\n",
					  reqid);
				cfg80211_sched_scan_results(cfg_to_wiphy(cfg),
							    reqid);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (scan_request) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = पातed,
		पूर्ण;

		brcmf_dbg(SCAN, "ESCAN Completed scan: %s\n",
			  पातed ? "Aborted" : "Done");
		cfg80211_scan_करोne(scan_request, &info);
	पूर्ण
	अगर (!test_and_clear_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status))
		brcmf_dbg(SCAN, "Scan complete, probably P2P scan\n");

	वापस err;
पूर्ण

अटल पूर्णांक brcmf_cfg80211_del_ap_अगरace(काष्ठा wiphy *wiphy,
				       काष्ठा wireless_dev *wdev)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा net_device *ndev = wdev->netdev;
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	पूर्णांक ret;
	पूर्णांक err;

	brcmf_cfg80211_arm_vअगर_event(cfg, अगरp->vअगर);

	err = brcmf_fil_bsscfg_data_set(अगरp, "interface_remove", शून्य, 0);
	अगर (err) अणु
		bphy_err(drvr, "interface_remove failed %d\n", err);
		जाओ err_unarm;
	पूर्ण

	/* रुको क्रम firmware event */
	ret = brcmf_cfg80211_रुको_vअगर_event(cfg, BRCMF_E_IF_DEL,
					    BRCMF_VIF_EVENT_TIMEOUT);
	अगर (!ret) अणु
		bphy_err(drvr, "timeout occurred\n");
		err = -EIO;
		जाओ err_unarm;
	पूर्ण

	brcmf_हटाओ_पूर्णांकerface(अगरp, true);

err_unarm:
	brcmf_cfg80211_arm_vअगर_event(cfg, शून्य);
	वापस err;
पूर्ण

अटल
पूर्णांक brcmf_cfg80211_del_अगरace(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा net_device *ndev = wdev->netdev;

	अगर (ndev && ndev == cfg_to_ndev(cfg))
		वापस -ENOTSUPP;

	/* vअगर event pending in firmware */
	अगर (brcmf_cfg80211_vअगर_event_armed(cfg))
		वापस -EBUSY;

	अगर (ndev) अणु
		अगर (test_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status) &&
		    cfg->escan_info.अगरp == netdev_priv(ndev))
			brcmf_notअगरy_escan_complete(cfg, netdev_priv(ndev),
						    true, true);

		brcmf_fil_iovar_पूर्णांक_set(netdev_priv(ndev), "mpc", 1);
	पूर्ण

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_WDS:
	हाल NL80211_IFTYPE_MESH_POINT:
		वापस -EOPNOTSUPP;
	हाल NL80211_IFTYPE_MONITOR:
		वापस brcmf_mon_del_vअगर(wiphy, wdev);
	हाल NL80211_IFTYPE_AP:
		वापस brcmf_cfg80211_del_ap_अगरace(wiphy, wdev);
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_P2P_DEVICE:
		वापस brcmf_p2p_del_vअगर(wiphy, wdev);
	हाल NL80211_IFTYPE_UNSPECIFIED:
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

अटल s32
brcmf_cfg80211_change_अगरace(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
			 क्रमागत nl80211_अगरtype type,
			 काष्ठा vअगर_params *params)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_cfg80211_vअगर *vअगर = अगरp->vअगर;
	काष्ठा brcmf_pub *drvr = cfg->pub;
	s32 infra = 0;
	s32 ap = 0;
	s32 err = 0;

	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d, type=%d\n", अगरp->bsscfgidx,
		  type);

	/* WAR: There are a number of p2p पूर्णांकerface related problems which
	 * need to be handled initially (beक्रमe करोing the validate).
	 * wpa_supplicant tends to करो अगरace changes on p2p device/client/go
	 * which are not always possible/allowed. However we need to वापस
	 * OK otherwise the wpa_supplicant wont start. The situation dअगरfers
	 * on configuration and setup (p2pon=1 module param). The first check
	 * is to see अगर the request is a change to station क्रम p2p अगरace.
	 */
	अगर ((type == NL80211_IFTYPE_STATION) &&
	    ((vअगर->wdev.अगरtype == NL80211_IFTYPE_P2P_CLIENT) ||
	     (vअगर->wdev.अगरtype == NL80211_IFTYPE_P2P_GO) ||
	     (vअगर->wdev.अगरtype == NL80211_IFTYPE_P2P_DEVICE))) अणु
		brcmf_dbg(TRACE, "Ignoring cmd for p2p if\n");
		/* Now depending on whether module param p2pon=1 was used the
		 * response needs to be either 0 or EOPNOTSUPP. The reason is
		 * that अगर p2pon=1 is used, but a newer supplicant is used then
		 * we should वापस an error, as this combination wont work.
		 * In other situations 0 is वापसed and supplicant will start
		 * normally. It will give a trace in cfg80211, but it is the
		 * only way to get it working. Unक्रमtunately this will result
		 * in situation where we wont support new supplicant in
		 * combination with module param p2pon=1, but that is the way
		 * it is. If the user tries this then unloading of driver might
		 * fail/lock.
		 */
		अगर (cfg->p2p.p2pdev_dynamically)
			वापस -EOPNOTSUPP;
		अन्यथा
			वापस 0;
	पूर्ण
	err = brcmf_vअगर_change_validate(wiphy_to_cfg(wiphy), vअगर, type);
	अगर (err) अणु
		bphy_err(drvr, "iface validation failed: err=%d\n", err);
		वापस err;
	पूर्ण
	चयन (type) अणु
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_WDS:
		bphy_err(drvr, "type (%d) : currently we do not support this type\n",
			 type);
		वापस -EOPNOTSUPP;
	हाल NL80211_IFTYPE_ADHOC:
		infra = 0;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		infra = 1;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
		ap = 1;
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (ap) अणु
		अगर (type == NL80211_IFTYPE_P2P_GO) अणु
			brcmf_dbg(INFO, "IF Type = P2P GO\n");
			err = brcmf_p2p_अगरchange(cfg, BRCMF_FIL_P2P_IF_GO);
		पूर्ण
		अगर (!err) अणु
			brcmf_dbg(INFO, "IF Type = AP\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_INFRA, infra);
		अगर (err) अणु
			bphy_err(drvr, "WLC_SET_INFRA error (%d)\n", err);
			err = -EAGAIN;
			जाओ करोne;
		पूर्ण
		brcmf_dbg(INFO, "IF Type = %s\n", brcmf_is_ibssmode(vअगर) ?
			  "Adhoc" : "Infra");
	पूर्ण
	ndev->ieee80211_ptr->अगरtype = type;

	brcmf_cfg80211_update_proto_addr_mode(&vअगर->wdev);

करोne:
	brcmf_dbg(TRACE, "Exit\n");

	वापस err;
पूर्ण

अटल व्योम brcmf_escan_prep(काष्ठा brcmf_cfg80211_info *cfg,
			     काष्ठा brcmf_scan_params_le *params_le,
			     काष्ठा cfg80211_scan_request *request)
अणु
	u32 n_ssids;
	u32 n_channels;
	s32 i;
	s32 offset;
	u16 chanspec;
	अक्षर *ptr;
	काष्ठा brcmf_ssid_le ssid_le;

	eth_broadcast_addr(params_le->bssid);
	params_le->bss_type = DOT11_BSSTYPE_ANY;
	params_le->scan_type = BRCMF_SCANTYPE_ACTIVE;
	params_le->channel_num = 0;
	params_le->nprobes = cpu_to_le32(-1);
	params_le->active_समय = cpu_to_le32(-1);
	params_le->passive_समय = cpu_to_le32(-1);
	params_le->home_समय = cpu_to_le32(-1);
	स_रखो(&params_le->ssid_le, 0, माप(params_le->ssid_le));

	n_ssids = request->n_ssids;
	n_channels = request->n_channels;

	/* Copy channel array अगर applicable */
	brcmf_dbg(SCAN, "### List of channelspecs to scan ### %d\n",
		  n_channels);
	अगर (n_channels > 0) अणु
		क्रम (i = 0; i < n_channels; i++) अणु
			chanspec = channel_to_chanspec(&cfg->d11inf,
						       request->channels[i]);
			brcmf_dbg(SCAN, "Chan : %d, Channel spec: %x\n",
				  request->channels[i]->hw_value, chanspec);
			params_le->channel_list[i] = cpu_to_le16(chanspec);
		पूर्ण
	पूर्ण अन्यथा अणु
		brcmf_dbg(SCAN, "Scanning all channels\n");
	पूर्ण
	/* Copy ssid array अगर applicable */
	brcmf_dbg(SCAN, "### List of SSIDs to scan ### %d\n", n_ssids);
	अगर (n_ssids > 0) अणु
		offset = दुरत्व(काष्ठा brcmf_scan_params_le, channel_list) +
				n_channels * माप(u16);
		offset = roundup(offset, माप(u32));
		ptr = (अक्षर *)params_le + offset;
		क्रम (i = 0; i < n_ssids; i++) अणु
			स_रखो(&ssid_le, 0, माप(ssid_le));
			ssid_le.SSID_len =
					cpu_to_le32(request->ssids[i].ssid_len);
			स_नकल(ssid_le.SSID, request->ssids[i].ssid,
			       request->ssids[i].ssid_len);
			अगर (!ssid_le.SSID_len)
				brcmf_dbg(SCAN, "%d: Broadcast scan\n", i);
			अन्यथा
				brcmf_dbg(SCAN, "%d: scan for  %.32s size=%d\n",
					  i, ssid_le.SSID, ssid_le.SSID_len);
			स_नकल(ptr, &ssid_le, माप(ssid_le));
			ptr += माप(ssid_le);
		पूर्ण
	पूर्ण अन्यथा अणु
		brcmf_dbg(SCAN, "Performing passive scan\n");
		params_le->scan_type = BRCMF_SCANTYPE_PASSIVE;
	पूर्ण
	/* Adding mask to channel numbers */
	params_le->channel_num =
		cpu_to_le32((n_ssids << BRCMF_SCAN_PARAMS_NSSID_SHIFT) |
			(n_channels & BRCMF_SCAN_PARAMS_COUNT_MASK));
पूर्ण

अटल s32
brcmf_run_escan(काष्ठा brcmf_cfg80211_info *cfg, काष्ठा brcmf_अगर *अगरp,
		काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा brcmf_pub *drvr = cfg->pub;
	s32 params_size = BRCMF_SCAN_PARAMS_FIXED_SIZE +
			  दुरत्व(काष्ठा brcmf_escan_params_le, params_le);
	काष्ठा brcmf_escan_params_le *params;
	s32 err = 0;

	brcmf_dbg(SCAN, "E-SCAN START\n");

	अगर (request != शून्य) अणु
		/* Allocate space क्रम populating ssids in काष्ठा */
		params_size += माप(u32) * ((request->n_channels + 1) / 2);

		/* Allocate space क्रम populating ssids in काष्ठा */
		params_size += माप(काष्ठा brcmf_ssid_le) * request->n_ssids;
	पूर्ण

	params = kzalloc(params_size, GFP_KERNEL);
	अगर (!params) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण
	BUG_ON(params_size + माप("escan") >= BRCMF_DCMD_MEDLEN);
	brcmf_escan_prep(cfg, &params->params_le, request);
	params->version = cpu_to_le32(BRCMF_ESCAN_REQ_VERSION);
	params->action = cpu_to_le16(WL_ESCAN_ACTION_START);
	params->sync_id = cpu_to_le16(0x1234);

	err = brcmf_fil_iovar_data_set(अगरp, "escan", params, params_size);
	अगर (err) अणु
		अगर (err == -EBUSY)
			brcmf_dbg(INFO, "system busy : escan canceled\n");
		अन्यथा
			bphy_err(drvr, "error (%d)\n", err);
	पूर्ण

	kमुक्त(params);
निकास:
	वापस err;
पूर्ण

अटल s32
brcmf_करो_escan(काष्ठा brcmf_अगर *अगरp, काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = अगरp->drvr->config;
	s32 err;
	काष्ठा brcmf_scan_results *results;
	काष्ठा escan_info *escan = &cfg->escan_info;

	brcmf_dbg(SCAN, "Enter\n");
	escan->अगरp = अगरp;
	escan->wiphy = cfg->wiphy;
	escan->escan_state = WL_ESCAN_STATE_SCANNING;

	brcmf_scan_config_mpc(अगरp, 0);
	results = (काष्ठा brcmf_scan_results *)cfg->escan_info.escan_buf;
	results->version = 0;
	results->count = 0;
	results->buflen = WL_ESCAN_RESULTS_FIXED_SIZE;

	err = escan->run(cfg, अगरp, request);
	अगर (err)
		brcmf_scan_config_mpc(अगरp, 1);
	वापस err;
पूर्ण

अटल s32
brcmf_cfg80211_scan(काष्ठा wiphy *wiphy, काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	s32 err = 0;

	brcmf_dbg(TRACE, "Enter\n");
	vअगर = container_of(request->wdev, काष्ठा brcmf_cfg80211_vअगर, wdev);
	अगर (!check_vअगर_up(vअगर))
		वापस -EIO;

	अगर (test_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status)) अणु
		bphy_err(drvr, "Scanning already: status (%lu)\n",
			 cfg->scan_status);
		वापस -EAGAIN;
	पूर्ण
	अगर (test_bit(BRCMF_SCAN_STATUS_ABORT, &cfg->scan_status)) अणु
		bphy_err(drvr, "Scanning being aborted: status (%lu)\n",
			 cfg->scan_status);
		वापस -EAGAIN;
	पूर्ण
	अगर (test_bit(BRCMF_SCAN_STATUS_SUPPRESS, &cfg->scan_status)) अणु
		bphy_err(drvr, "Scanning suppressed: status (%lu)\n",
			 cfg->scan_status);
		वापस -EAGAIN;
	पूर्ण
	अगर (test_bit(BRCMF_VIF_STATUS_CONNECTING, &vअगर->sme_state)) अणु
		bphy_err(drvr, "Connecting: status (%lu)\n", vअगर->sme_state);
		वापस -EAGAIN;
	पूर्ण

	/* If scan req comes क्रम p2p0, send it over primary I/F */
	अगर (vअगर == cfg->p2p.bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर)
		vअगर = cfg->p2p.bss_idx[P2PAPI_BSSCFG_PRIMARY].vअगर;

	brcmf_dbg(SCAN, "START ESCAN\n");

	cfg->scan_request = request;
	set_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status);

	cfg->escan_info.run = brcmf_run_escan;
	err = brcmf_p2p_scan_prep(wiphy, request, vअगर);
	अगर (err)
		जाओ scan_out;

	err = brcmf_vअगर_set_mgmt_ie(vअगर, BRCMF_VNDR_IE_PRBREQ_FLAG,
				    request->ie, request->ie_len);
	अगर (err)
		जाओ scan_out;

	err = brcmf_करो_escan(vअगर->अगरp, request);
	अगर (err)
		जाओ scan_out;

	/* Arm scan समयout समयr */
	mod_समयr(&cfg->escan_समयout,
		  jअगरfies + msecs_to_jअगरfies(BRCMF_ESCAN_TIMER_INTERVAL_MS));

	वापस 0;

scan_out:
	bphy_err(drvr, "scan error (%d)\n", err);
	clear_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status);
	cfg->scan_request = शून्य;
	वापस err;
पूर्ण

अटल s32 brcmf_set_rts(काष्ठा net_device *ndev, u32 rts_threshold)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 err = 0;

	err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "rtsthresh", rts_threshold);
	अगर (err)
		bphy_err(drvr, "Error (%d)\n", err);

	वापस err;
पूर्ण

अटल s32 brcmf_set_frag(काष्ठा net_device *ndev, u32 frag_threshold)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 err = 0;

	err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "fragthresh",
				      frag_threshold);
	अगर (err)
		bphy_err(drvr, "Error (%d)\n", err);

	वापस err;
पूर्ण

अटल s32 brcmf_set_retry(काष्ठा net_device *ndev, u32 retry, bool l)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 err = 0;
	u32 cmd = (l ? BRCMF_C_SET_LRL : BRCMF_C_SET_SRL);

	err = brcmf_fil_cmd_पूर्णांक_set(अगरp, cmd, retry);
	अगर (err) अणु
		bphy_err(drvr, "cmd (%d) , error (%d)\n", cmd, err);
		वापस err;
	पूर्ण
	वापस err;
पूर्ण

अटल s32 brcmf_cfg80211_set_wiphy_params(काष्ठा wiphy *wiphy, u32 changed)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा net_device *ndev = cfg_to_ndev(cfg);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	s32 err = 0;

	brcmf_dbg(TRACE, "Enter\n");
	अगर (!check_vअगर_up(अगरp->vअगर))
		वापस -EIO;

	अगर (changed & WIPHY_PARAM_RTS_THRESHOLD &&
	    (cfg->conf->rts_threshold != wiphy->rts_threshold)) अणु
		cfg->conf->rts_threshold = wiphy->rts_threshold;
		err = brcmf_set_rts(ndev, cfg->conf->rts_threshold);
		अगर (!err)
			जाओ करोne;
	पूर्ण
	अगर (changed & WIPHY_PARAM_FRAG_THRESHOLD &&
	    (cfg->conf->frag_threshold != wiphy->frag_threshold)) अणु
		cfg->conf->frag_threshold = wiphy->frag_threshold;
		err = brcmf_set_frag(ndev, cfg->conf->frag_threshold);
		अगर (!err)
			जाओ करोne;
	पूर्ण
	अगर (changed & WIPHY_PARAM_RETRY_LONG
	    && (cfg->conf->retry_दीर्घ != wiphy->retry_दीर्घ)) अणु
		cfg->conf->retry_दीर्घ = wiphy->retry_दीर्घ;
		err = brcmf_set_retry(ndev, cfg->conf->retry_दीर्घ, true);
		अगर (!err)
			जाओ करोne;
	पूर्ण
	अगर (changed & WIPHY_PARAM_RETRY_SHORT
	    && (cfg->conf->retry_लघु != wiphy->retry_लघु)) अणु
		cfg->conf->retry_लघु = wiphy->retry_लघु;
		err = brcmf_set_retry(ndev, cfg->conf->retry_लघु, false);
		अगर (!err)
			जाओ करोne;
	पूर्ण

करोne:
	brcmf_dbg(TRACE, "Exit\n");
	वापस err;
पूर्ण

अटल व्योम brcmf_init_prof(काष्ठा brcmf_cfg80211_profile *prof)
अणु
	स_रखो(prof, 0, माप(*prof));
पूर्ण

अटल u16 brcmf_map_fw_linkकरोwn_reason(स्थिर काष्ठा brcmf_event_msg *e)
अणु
	u16 reason;

	चयन (e->event_code) अणु
	हाल BRCMF_E_DEAUTH:
	हाल BRCMF_E_DEAUTH_IND:
	हाल BRCMF_E_DISASSOC_IND:
		reason = e->reason;
		अवरोध;
	हाल BRCMF_E_LINK:
	शेष:
		reason = 0;
		अवरोध;
	पूर्ण
	वापस reason;
पूर्ण

अटल पूर्णांक brcmf_set_pmk(काष्ठा brcmf_अगर *अगरp, स्थिर u8 *pmk_data, u16 pmk_len)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_wsec_pmk_le pmk;
	पूर्णांक i, err;

	/* convert to firmware key क्रमmat */
	pmk.key_len = cpu_to_le16(pmk_len << 1);
	pmk.flags = cpu_to_le16(BRCMF_WSEC_PASSPHRASE);
	क्रम (i = 0; i < pmk_len; i++)
		snम_लिखो(&pmk.key[2 * i], 3, "%02x", pmk_data[i]);

	/* store psk in firmware */
	err = brcmf_fil_cmd_data_set(अगरp, BRCMF_C_SET_WSEC_PMK,
				     &pmk, माप(pmk));
	अगर (err < 0)
		bphy_err(drvr, "failed to change PSK in firmware (len=%u)\n",
			 pmk_len);

	वापस err;
पूर्ण

अटल पूर्णांक brcmf_set_sae_password(काष्ठा brcmf_अगर *अगरp, स्थिर u8 *pwd_data,
				  u16 pwd_len)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_wsec_sae_pwd_le sae_pwd;
	पूर्णांक err;

	अगर (pwd_len > BRCMF_WSEC_MAX_SAE_PASSWORD_LEN) अणु
		bphy_err(drvr, "sae_password must be less than %d\n",
			 BRCMF_WSEC_MAX_SAE_PASSWORD_LEN);
		वापस -EINVAL;
	पूर्ण

	sae_pwd.key_len = cpu_to_le16(pwd_len);
	स_नकल(sae_pwd.key, pwd_data, pwd_len);

	err = brcmf_fil_iovar_data_set(अगरp, "sae_password", &sae_pwd,
				       माप(sae_pwd));
	अगर (err < 0)
		bphy_err(drvr, "failed to set SAE password in firmware (len=%u)\n",
			 pwd_len);

	वापस err;
पूर्ण

अटल व्योम brcmf_link_करोwn(काष्ठा brcmf_cfg80211_vअगर *vअगर, u16 reason,
			    bool locally_generated)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(vअगर->wdev.wiphy);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	bool bus_up = drvr->bus_अगर->state == BRCMF_BUS_UP;
	s32 err = 0;

	brcmf_dbg(TRACE, "Enter\n");

	अगर (test_and_clear_bit(BRCMF_VIF_STATUS_CONNECTED, &vअगर->sme_state)) अणु
		अगर (bus_up) अणु
			brcmf_dbg(INFO, "Call WLC_DISASSOC to stop excess roaming\n");
			err = brcmf_fil_cmd_data_set(vअगर->अगरp,
						     BRCMF_C_DISASSOC, शून्य, 0);
			अगर (err)
				bphy_err(drvr, "WLC_DISASSOC failed (%d)\n",
					 err);
		पूर्ण

		अगर ((vअगर->wdev.अगरtype == NL80211_IFTYPE_STATION) ||
		    (vअगर->wdev.अगरtype == NL80211_IFTYPE_P2P_CLIENT))
			cfg80211_disconnected(vअगर->wdev.netdev, reason, शून्य, 0,
					      locally_generated, GFP_KERNEL);
	पूर्ण
	clear_bit(BRCMF_VIF_STATUS_CONNECTING, &vअगर->sme_state);
	clear_bit(BRCMF_SCAN_STATUS_SUPPRESS, &cfg->scan_status);
	brcmf_btcoex_set_mode(vअगर, BRCMF_BTCOEX_ENABLED, 0);
	अगर (vअगर->profile.use_fwsup != BRCMF_PROखाता_FWSUP_NONE) अणु
		अगर (bus_up)
			brcmf_set_pmk(vअगर->अगरp, शून्य, 0);
		vअगर->profile.use_fwsup = BRCMF_PROखाता_FWSUP_NONE;
	पूर्ण
	brcmf_dbg(TRACE, "Exit\n");
पूर्ण

अटल s32
brcmf_cfg80211_join_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
		      काष्ठा cfg80211_ibss_params *params)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_cfg80211_profile *profile = &अगरp->vअगर->profile;
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_join_params join_params;
	माप_प्रकार join_params_size = 0;
	s32 err = 0;
	s32 wsec = 0;
	s32 bcnprd;
	u16 chanspec;
	u32 ssid_len;

	brcmf_dbg(TRACE, "Enter\n");
	अगर (!check_vअगर_up(अगरp->vअगर))
		वापस -EIO;

	अगर (params->ssid)
		brcmf_dbg(CONN, "SSID: %s\n", params->ssid);
	अन्यथा अणु
		brcmf_dbg(CONN, "SSID: NULL, Not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	set_bit(BRCMF_VIF_STATUS_CONNECTING, &अगरp->vअगर->sme_state);

	अगर (params->bssid)
		brcmf_dbg(CONN, "BSSID: %pM\n", params->bssid);
	अन्यथा
		brcmf_dbg(CONN, "No BSSID specified\n");

	अगर (params->chandef.chan)
		brcmf_dbg(CONN, "channel: %d\n",
			  params->chandef.chan->center_freq);
	अन्यथा
		brcmf_dbg(CONN, "no channel specified\n");

	अगर (params->channel_fixed)
		brcmf_dbg(CONN, "fixed channel required\n");
	अन्यथा
		brcmf_dbg(CONN, "no fixed channel required\n");

	अगर (params->ie && params->ie_len)
		brcmf_dbg(CONN, "ie len: %d\n", params->ie_len);
	अन्यथा
		brcmf_dbg(CONN, "no ie specified\n");

	अगर (params->beacon_पूर्णांकerval)
		brcmf_dbg(CONN, "beacon interval: %d\n",
			  params->beacon_पूर्णांकerval);
	अन्यथा
		brcmf_dbg(CONN, "no beacon interval specified\n");

	अगर (params->basic_rates)
		brcmf_dbg(CONN, "basic rates: %08X\n", params->basic_rates);
	अन्यथा
		brcmf_dbg(CONN, "no basic rates specified\n");

	अगर (params->privacy)
		brcmf_dbg(CONN, "privacy required\n");
	अन्यथा
		brcmf_dbg(CONN, "no privacy required\n");

	/* Configure Privacy क्रम starter */
	अगर (params->privacy)
		wsec |= WEP_ENABLED;

	err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "wsec", wsec);
	अगर (err) अणु
		bphy_err(drvr, "wsec failed (%d)\n", err);
		जाओ करोne;
	पूर्ण

	/* Configure Beacon Interval क्रम starter */
	अगर (params->beacon_पूर्णांकerval)
		bcnprd = params->beacon_पूर्णांकerval;
	अन्यथा
		bcnprd = 100;

	err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_BCNPRD, bcnprd);
	अगर (err) अणु
		bphy_err(drvr, "WLC_SET_BCNPRD failed (%d)\n", err);
		जाओ करोne;
	पूर्ण

	/* Configure required join parameter */
	स_रखो(&join_params, 0, माप(काष्ठा brcmf_join_params));

	/* SSID */
	ssid_len = min_t(u32, params->ssid_len, IEEE80211_MAX_SSID_LEN);
	स_नकल(join_params.ssid_le.SSID, params->ssid, ssid_len);
	join_params.ssid_le.SSID_len = cpu_to_le32(ssid_len);
	join_params_size = माप(join_params.ssid_le);

	/* BSSID */
	अगर (params->bssid) अणु
		स_नकल(join_params.params_le.bssid, params->bssid, ETH_ALEN);
		join_params_size += BRCMF_ASSOC_PARAMS_FIXED_SIZE;
		स_नकल(profile->bssid, params->bssid, ETH_ALEN);
	पूर्ण अन्यथा अणु
		eth_broadcast_addr(join_params.params_le.bssid);
		eth_zero_addr(profile->bssid);
	पूर्ण

	/* Channel */
	अगर (params->chandef.chan) अणु
		u32 target_channel;

		cfg->channel =
			ieee80211_frequency_to_channel(
				params->chandef.chan->center_freq);
		अगर (params->channel_fixed) अणु
			/* adding chanspec */
			chanspec = chandef_to_chanspec(&cfg->d11inf,
						       &params->chandef);
			join_params.params_le.chanspec_list[0] =
				cpu_to_le16(chanspec);
			join_params.params_le.chanspec_num = cpu_to_le32(1);
			join_params_size += माप(join_params.params_le);
		पूर्ण

		/* set channel क्रम starter */
		target_channel = cfg->channel;
		err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_CHANNEL,
					    target_channel);
		अगर (err) अणु
			bphy_err(drvr, "WLC_SET_CHANNEL failed (%d)\n", err);
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा
		cfg->channel = 0;

	cfg->ibss_starter = false;


	err = brcmf_fil_cmd_data_set(अगरp, BRCMF_C_SET_SSID,
				     &join_params, join_params_size);
	अगर (err) अणु
		bphy_err(drvr, "WLC_SET_SSID failed (%d)\n", err);
		जाओ करोne;
	पूर्ण

करोne:
	अगर (err)
		clear_bit(BRCMF_VIF_STATUS_CONNECTING, &अगरp->vअगर->sme_state);
	brcmf_dbg(TRACE, "Exit\n");
	वापस err;
पूर्ण

अटल s32
brcmf_cfg80211_leave_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);

	brcmf_dbg(TRACE, "Enter\n");
	अगर (!check_vअगर_up(अगरp->vअगर)) अणु
		/* When driver is being unloaded, it can end up here. If an
		 * error is वापसed then later on a debug trace in the wireless
		 * core module will be prपूर्णांकed. To aव्योम this 0 is वापसed.
		 */
		वापस 0;
	पूर्ण

	brcmf_link_करोwn(अगरp->vअगर, WLAN_REASON_DEAUTH_LEAVING, true);
	brcmf_net_setcarrier(अगरp, false);

	brcmf_dbg(TRACE, "Exit\n");

	वापस 0;
पूर्ण

अटल s32 brcmf_set_wpa_version(काष्ठा net_device *ndev,
				 काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_cfg80211_profile *profile = ndev_to_prof(ndev);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_cfg80211_security *sec;
	s32 val = 0;
	s32 err = 0;

	अगर (sme->crypto.wpa_versions & NL80211_WPA_VERSION_1)
		val = WPA_AUTH_PSK | WPA_AUTH_UNSPECIFIED;
	अन्यथा अगर (sme->crypto.wpa_versions & NL80211_WPA_VERSION_2)
		val = WPA2_AUTH_PSK | WPA2_AUTH_UNSPECIFIED;
	अन्यथा अगर (sme->crypto.wpa_versions & NL80211_WPA_VERSION_3)
		val = WPA3_AUTH_SAE_PSK;
	अन्यथा
		val = WPA_AUTH_DISABLED;
	brcmf_dbg(CONN, "setting wpa_auth to 0x%0x\n", val);
	err = brcmf_fil_bsscfg_पूर्णांक_set(अगरp, "wpa_auth", val);
	अगर (err) अणु
		bphy_err(drvr, "set wpa_auth failed (%d)\n", err);
		वापस err;
	पूर्ण
	sec = &profile->sec;
	sec->wpa_versions = sme->crypto.wpa_versions;
	वापस err;
पूर्ण

अटल s32 brcmf_set_auth_type(काष्ठा net_device *ndev,
			       काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_cfg80211_profile *profile = ndev_to_prof(ndev);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_cfg80211_security *sec;
	s32 val = 0;
	s32 err = 0;

	चयन (sme->auth_type) अणु
	हाल NL80211_AUTHTYPE_OPEN_SYSTEM:
		val = 0;
		brcmf_dbg(CONN, "open system\n");
		अवरोध;
	हाल NL80211_AUTHTYPE_SHARED_KEY:
		val = 1;
		brcmf_dbg(CONN, "shared key\n");
		अवरोध;
	हाल NL80211_AUTHTYPE_SAE:
		val = 3;
		brcmf_dbg(CONN, "SAE authentication\n");
		अवरोध;
	शेष:
		val = 2;
		brcmf_dbg(CONN, "automatic, auth type (%d)\n", sme->auth_type);
		अवरोध;
	पूर्ण

	err = brcmf_fil_bsscfg_पूर्णांक_set(अगरp, "auth", val);
	अगर (err) अणु
		bphy_err(drvr, "set auth failed (%d)\n", err);
		वापस err;
	पूर्ण
	sec = &profile->sec;
	sec->auth_type = sme->auth_type;
	वापस err;
पूर्ण

अटल s32
brcmf_set_wsec_mode(काष्ठा net_device *ndev,
		    काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_cfg80211_profile *profile = ndev_to_prof(ndev);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_cfg80211_security *sec;
	s32 pval = 0;
	s32 gval = 0;
	s32 wsec;
	s32 err = 0;

	अगर (sme->crypto.n_ciphers_pairwise) अणु
		चयन (sme->crypto.ciphers_pairwise[0]) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
			pval = WEP_ENABLED;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_TKIP:
			pval = TKIP_ENABLED;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_CCMP:
			pval = AES_ENABLED;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_AES_CMAC:
			pval = AES_ENABLED;
			अवरोध;
		शेष:
			bphy_err(drvr, "invalid cipher pairwise (%d)\n",
				 sme->crypto.ciphers_pairwise[0]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (sme->crypto.cipher_group) अणु
		चयन (sme->crypto.cipher_group) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
			gval = WEP_ENABLED;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_TKIP:
			gval = TKIP_ENABLED;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_CCMP:
			gval = AES_ENABLED;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_AES_CMAC:
			gval = AES_ENABLED;
			अवरोध;
		शेष:
			bphy_err(drvr, "invalid cipher group (%d)\n",
				 sme->crypto.cipher_group);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	brcmf_dbg(CONN, "pval (%d) gval (%d)\n", pval, gval);
	/* In हाल of privacy, but no security and WPS then simulate */
	/* setting AES. WPS-2.0 allows no security                   */
	अगर (brcmf_find_wpsie(sme->ie, sme->ie_len) && !pval && !gval &&
	    sme->privacy)
		pval = AES_ENABLED;

	wsec = pval | gval;
	err = brcmf_fil_bsscfg_पूर्णांक_set(अगरp, "wsec", wsec);
	अगर (err) अणु
		bphy_err(drvr, "error (%d)\n", err);
		वापस err;
	पूर्ण

	sec = &profile->sec;
	sec->cipher_pairwise = sme->crypto.ciphers_pairwise[0];
	sec->cipher_group = sme->crypto.cipher_group;

	वापस err;
पूर्ण

अटल s32
brcmf_set_key_mgmt(काष्ठा net_device *ndev, काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_cfg80211_profile *profile = &अगरp->vअगर->profile;
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 val;
	s32 err;
	स्थिर काष्ठा brcmf_tlv *rsn_ie;
	स्थिर u8 *ie;
	u32 ie_len;
	u32 offset;
	u16 rsn_cap;
	u32 mfp;
	u16 count;

	profile->use_fwsup = BRCMF_PROखाता_FWSUP_NONE;
	profile->is_ft = false;

	अगर (!sme->crypto.n_akm_suites)
		वापस 0;

	err = brcmf_fil_bsscfg_पूर्णांक_get(netdev_priv(ndev), "wpa_auth", &val);
	अगर (err) अणु
		bphy_err(drvr, "could not get wpa_auth (%d)\n", err);
		वापस err;
	पूर्ण
	अगर (val & (WPA_AUTH_PSK | WPA_AUTH_UNSPECIFIED)) अणु
		चयन (sme->crypto.akm_suites[0]) अणु
		हाल WLAN_AKM_SUITE_8021X:
			val = WPA_AUTH_UNSPECIFIED;
			अगर (sme->want_1x)
				profile->use_fwsup = BRCMF_PROखाता_FWSUP_1X;
			अवरोध;
		हाल WLAN_AKM_SUITE_PSK:
			val = WPA_AUTH_PSK;
			अवरोध;
		शेष:
			bphy_err(drvr, "invalid cipher group (%d)\n",
				 sme->crypto.cipher_group);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (val & (WPA2_AUTH_PSK | WPA2_AUTH_UNSPECIFIED)) अणु
		चयन (sme->crypto.akm_suites[0]) अणु
		हाल WLAN_AKM_SUITE_8021X:
			val = WPA2_AUTH_UNSPECIFIED;
			अगर (sme->want_1x)
				profile->use_fwsup = BRCMF_PROखाता_FWSUP_1X;
			अवरोध;
		हाल WLAN_AKM_SUITE_8021X_SHA256:
			val = WPA2_AUTH_1X_SHA256;
			अगर (sme->want_1x)
				profile->use_fwsup = BRCMF_PROखाता_FWSUP_1X;
			अवरोध;
		हाल WLAN_AKM_SUITE_PSK_SHA256:
			val = WPA2_AUTH_PSK_SHA256;
			अवरोध;
		हाल WLAN_AKM_SUITE_PSK:
			val = WPA2_AUTH_PSK;
			अवरोध;
		हाल WLAN_AKM_SUITE_FT_8021X:
			val = WPA2_AUTH_UNSPECIFIED | WPA2_AUTH_FT;
			profile->is_ft = true;
			अगर (sme->want_1x)
				profile->use_fwsup = BRCMF_PROखाता_FWSUP_1X;
			अवरोध;
		हाल WLAN_AKM_SUITE_FT_PSK:
			val = WPA2_AUTH_PSK | WPA2_AUTH_FT;
			profile->is_ft = true;
			अवरोध;
		शेष:
			bphy_err(drvr, "invalid cipher group (%d)\n",
				 sme->crypto.cipher_group);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (val & WPA3_AUTH_SAE_PSK) अणु
		चयन (sme->crypto.akm_suites[0]) अणु
		हाल WLAN_AKM_SUITE_SAE:
			val = WPA3_AUTH_SAE_PSK;
			अगर (sme->crypto.sae_pwd) अणु
				brcmf_dbg(INFO, "using SAE offload\n");
				profile->use_fwsup = BRCMF_PROखाता_FWSUP_SAE;
			पूर्ण
			अवरोध;
		शेष:
			bphy_err(drvr, "invalid cipher group (%d)\n",
				 sme->crypto.cipher_group);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (profile->use_fwsup == BRCMF_PROखाता_FWSUP_1X)
		brcmf_dbg(INFO, "using 1X offload\n");

	अगर (!brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_MFP))
		जाओ skip_mfp_config;
	/* The MFP mode (1 or 2) needs to be determined, parse IEs. The
	 * IE will not be verअगरied, just a quick search क्रम MFP config
	 */
	rsn_ie = brcmf_parse_tlvs((स्थिर u8 *)sme->ie, sme->ie_len,
				  WLAN_EID_RSN);
	अगर (!rsn_ie)
		जाओ skip_mfp_config;
	ie = (स्थिर u8 *)rsn_ie;
	ie_len = rsn_ie->len + TLV_HDR_LEN;
	/* Skip unicast suite */
	offset = TLV_HDR_LEN + WPA_IE_VERSION_LEN + WPA_IE_MIN_OUI_LEN;
	अगर (offset + WPA_IE_SUITE_COUNT_LEN >= ie_len)
		जाओ skip_mfp_config;
	/* Skip multicast suite */
	count = ie[offset] + (ie[offset + 1] << 8);
	offset += WPA_IE_SUITE_COUNT_LEN + (count * WPA_IE_MIN_OUI_LEN);
	अगर (offset + WPA_IE_SUITE_COUNT_LEN >= ie_len)
		जाओ skip_mfp_config;
	/* Skip auth key management suite(s) */
	count = ie[offset] + (ie[offset + 1] << 8);
	offset += WPA_IE_SUITE_COUNT_LEN + (count * WPA_IE_MIN_OUI_LEN);
	अगर (offset + WPA_IE_SUITE_COUNT_LEN > ie_len)
		जाओ skip_mfp_config;
	/* Ready to पढ़ो capabilities */
	mfp = BRCMF_MFP_NONE;
	rsn_cap = ie[offset] + (ie[offset + 1] << 8);
	अगर (rsn_cap & RSN_CAP_MFPR_MASK)
		mfp = BRCMF_MFP_REQUIRED;
	अन्यथा अगर (rsn_cap & RSN_CAP_MFPC_MASK)
		mfp = BRCMF_MFP_CAPABLE;
	brcmf_fil_bsscfg_पूर्णांक_set(netdev_priv(ndev), "mfp", mfp);

skip_mfp_config:
	brcmf_dbg(CONN, "setting wpa_auth to %d\n", val);
	err = brcmf_fil_bsscfg_पूर्णांक_set(netdev_priv(ndev), "wpa_auth", val);
	अगर (err) अणु
		bphy_err(drvr, "could not set wpa_auth (%d)\n", err);
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल s32
brcmf_set_sharedkey(काष्ठा net_device *ndev,
		    काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_cfg80211_profile *profile = ndev_to_prof(ndev);
	काष्ठा brcmf_cfg80211_security *sec;
	काष्ठा brcmf_wsec_key key;
	s32 val;
	s32 err = 0;

	brcmf_dbg(CONN, "key len (%d)\n", sme->key_len);

	अगर (sme->key_len == 0)
		वापस 0;

	sec = &profile->sec;
	brcmf_dbg(CONN, "wpa_versions 0x%x cipher_pairwise 0x%x\n",
		  sec->wpa_versions, sec->cipher_pairwise);

	अगर (sec->wpa_versions & (NL80211_WPA_VERSION_1 | NL80211_WPA_VERSION_2 |
				 NL80211_WPA_VERSION_3))
		वापस 0;

	अगर (!(sec->cipher_pairwise &
	    (WLAN_CIPHER_SUITE_WEP40 | WLAN_CIPHER_SUITE_WEP104)))
		वापस 0;

	स_रखो(&key, 0, माप(key));
	key.len = (u32) sme->key_len;
	key.index = (u32) sme->key_idx;
	अगर (key.len > माप(key.data)) अणु
		bphy_err(drvr, "Too long key length (%u)\n", key.len);
		वापस -EINVAL;
	पूर्ण
	स_नकल(key.data, sme->key, key.len);
	key.flags = BRCMF_PRIMARY_KEY;
	चयन (sec->cipher_pairwise) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
		key.algo = CRYPTO_ALGO_WEP1;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP104:
		key.algo = CRYPTO_ALGO_WEP128;
		अवरोध;
	शेष:
		bphy_err(drvr, "Invalid algorithm (%d)\n",
			 sme->crypto.ciphers_pairwise[0]);
		वापस -EINVAL;
	पूर्ण
	/* Set the new key/index */
	brcmf_dbg(CONN, "key length (%d) key index (%d) algo (%d)\n",
		  key.len, key.index, key.algo);
	brcmf_dbg(CONN, "key \"%s\"\n", key.data);
	err = send_key_to_करोngle(अगरp, &key);
	अगर (err)
		वापस err;

	अगर (sec->auth_type == NL80211_AUTHTYPE_SHARED_KEY) अणु
		brcmf_dbg(CONN, "set auth_type to shared key\n");
		val = WL_AUTH_SHARED_KEY;	/* shared key */
		err = brcmf_fil_bsscfg_पूर्णांक_set(अगरp, "auth", val);
		अगर (err)
			bphy_err(drvr, "set auth failed (%d)\n", err);
	पूर्ण
	वापस err;
पूर्ण

अटल
क्रमागत nl80211_auth_type brcmf_war_auth_type(काष्ठा brcmf_अगर *अगरp,
					   क्रमागत nl80211_auth_type type)
अणु
	अगर (type == NL80211_AUTHTYPE_AUTOMATIC &&
	    brcmf_feat_is_quirk_enabled(अगरp, BRCMF_FEAT_QUIRK_AUTO_AUTH)) अणु
		brcmf_dbg(CONN, "WAR: use OPEN instead of AUTO\n");
		type = NL80211_AUTHTYPE_OPEN_SYSTEM;
	पूर्ण
	वापस type;
पूर्ण

अटल व्योम brcmf_set_join_pref(काष्ठा brcmf_अगर *अगरp,
				काष्ठा cfg80211_bss_selection *bss_select)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_join_pref_params join_pref_params[2];
	क्रमागत nl80211_band band;
	पूर्णांक err, i = 0;

	join_pref_params[i].len = 2;
	join_pref_params[i].rssi_gain = 0;

	अगर (bss_select->behaviour != NL80211_BSS_SELECT_ATTR_BAND_PREF)
		brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_ASSOC_PREFER, WLC_BAND_AUTO);

	चयन (bss_select->behaviour) अणु
	हाल __NL80211_BSS_SELECT_ATTR_INVALID:
		brcmf_c_set_joinpref_शेष(अगरp);
		वापस;
	हाल NL80211_BSS_SELECT_ATTR_BAND_PREF:
		join_pref_params[i].type = BRCMF_JOIN_PREF_BAND;
		band = bss_select->param.band_pref;
		join_pref_params[i].band = nl80211_band_to_fwil(band);
		i++;
		अवरोध;
	हाल NL80211_BSS_SELECT_ATTR_RSSI_ADJUST:
		join_pref_params[i].type = BRCMF_JOIN_PREF_RSSI_DELTA;
		band = bss_select->param.adjust.band;
		join_pref_params[i].band = nl80211_band_to_fwil(band);
		join_pref_params[i].rssi_gain = bss_select->param.adjust.delta;
		i++;
		अवरोध;
	हाल NL80211_BSS_SELECT_ATTR_RSSI:
	शेष:
		अवरोध;
	पूर्ण
	join_pref_params[i].type = BRCMF_JOIN_PREF_RSSI;
	join_pref_params[i].len = 2;
	join_pref_params[i].rssi_gain = 0;
	join_pref_params[i].band = 0;
	err = brcmf_fil_iovar_data_set(अगरp, "join_pref", join_pref_params,
				       माप(join_pref_params));
	अगर (err)
		bphy_err(drvr, "Set join_pref error (%d)\n", err);
पूर्ण

अटल s32
brcmf_cfg80211_connect(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
		       काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_cfg80211_profile *profile = &अगरp->vअगर->profile;
	काष्ठा ieee80211_channel *chan = sme->channel;
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_join_params join_params;
	माप_प्रकार join_params_size;
	स्थिर काष्ठा brcmf_tlv *rsn_ie;
	स्थिर काष्ठा brcmf_vs_tlv *wpa_ie;
	स्थिर व्योम *ie;
	u32 ie_len;
	काष्ठा brcmf_ext_join_params_le *ext_join_params;
	u16 chanspec;
	s32 err = 0;
	u32 ssid_len;

	brcmf_dbg(TRACE, "Enter\n");
	अगर (!check_vअगर_up(अगरp->vअगर))
		वापस -EIO;

	अगर (!sme->ssid) अणु
		bphy_err(drvr, "Invalid ssid\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (अगरp->vअगर == cfg->p2p.bss_idx[P2PAPI_BSSCFG_PRIMARY].vअगर) अणु
		/* A normal (non P2P) connection request setup. */
		ie = शून्य;
		ie_len = 0;
		/* find the WPA_IE */
		wpa_ie = brcmf_find_wpaie((u8 *)sme->ie, sme->ie_len);
		अगर (wpa_ie) अणु
			ie = wpa_ie;
			ie_len = wpa_ie->len + TLV_HDR_LEN;
		पूर्ण अन्यथा अणु
			/* find the RSN_IE */
			rsn_ie = brcmf_parse_tlvs((स्थिर u8 *)sme->ie,
						  sme->ie_len,
						  WLAN_EID_RSN);
			अगर (rsn_ie) अणु
				ie = rsn_ie;
				ie_len = rsn_ie->len + TLV_HDR_LEN;
			पूर्ण
		पूर्ण
		brcmf_fil_iovar_data_set(अगरp, "wpaie", ie, ie_len);
	पूर्ण

	err = brcmf_vअगर_set_mgmt_ie(अगरp->vअगर, BRCMF_VNDR_IE_ASSOCREQ_FLAG,
				    sme->ie, sme->ie_len);
	अगर (err)
		bphy_err(drvr, "Set Assoc REQ IE Failed\n");
	अन्यथा
		brcmf_dbg(TRACE, "Applied Vndr IEs for Assoc request\n");

	set_bit(BRCMF_VIF_STATUS_CONNECTING, &अगरp->vअगर->sme_state);

	अगर (chan) अणु
		cfg->channel =
			ieee80211_frequency_to_channel(chan->center_freq);
		chanspec = channel_to_chanspec(&cfg->d11inf, chan);
		brcmf_dbg(CONN, "channel=%d, center_req=%d, chanspec=0x%04x\n",
			  cfg->channel, chan->center_freq, chanspec);
	पूर्ण अन्यथा अणु
		cfg->channel = 0;
		chanspec = 0;
	पूर्ण

	brcmf_dbg(INFO, "ie (%p), ie_len (%zd)\n", sme->ie, sme->ie_len);

	err = brcmf_set_wpa_version(ndev, sme);
	अगर (err) अणु
		bphy_err(drvr, "wl_set_wpa_version failed (%d)\n", err);
		जाओ करोne;
	पूर्ण

	sme->auth_type = brcmf_war_auth_type(अगरp, sme->auth_type);
	err = brcmf_set_auth_type(ndev, sme);
	अगर (err) अणु
		bphy_err(drvr, "wl_set_auth_type failed (%d)\n", err);
		जाओ करोne;
	पूर्ण

	err = brcmf_set_wsec_mode(ndev, sme);
	अगर (err) अणु
		bphy_err(drvr, "wl_set_set_cipher failed (%d)\n", err);
		जाओ करोne;
	पूर्ण

	err = brcmf_set_key_mgmt(ndev, sme);
	अगर (err) अणु
		bphy_err(drvr, "wl_set_key_mgmt failed (%d)\n", err);
		जाओ करोne;
	पूर्ण

	err = brcmf_set_sharedkey(ndev, sme);
	अगर (err) अणु
		bphy_err(drvr, "brcmf_set_sharedkey failed (%d)\n", err);
		जाओ करोne;
	पूर्ण

	अगर (sme->crypto.psk &&
	    profile->use_fwsup != BRCMF_PROखाता_FWSUP_SAE) अणु
		अगर (WARN_ON(profile->use_fwsup != BRCMF_PROखाता_FWSUP_NONE)) अणु
			err = -EINVAL;
			जाओ करोne;
		पूर्ण
		brcmf_dbg(INFO, "using PSK offload\n");
		profile->use_fwsup = BRCMF_PROखाता_FWSUP_PSK;
	पूर्ण

	अगर (profile->use_fwsup != BRCMF_PROखाता_FWSUP_NONE) अणु
		/* enable firmware supplicant क्रम this पूर्णांकerface */
		err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "sup_wpa", 1);
		अगर (err < 0) अणु
			bphy_err(drvr, "failed to enable fw supplicant\n");
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (profile->use_fwsup == BRCMF_PROखाता_FWSUP_PSK)
		err = brcmf_set_pmk(अगरp, sme->crypto.psk,
				    BRCMF_WSEC_MAX_PSK_LEN);
	अन्यथा अगर (profile->use_fwsup == BRCMF_PROखाता_FWSUP_SAE) अणु
		/* clean up user-space RSNE */
		err = brcmf_fil_iovar_data_set(अगरp, "wpaie", शून्य, 0);
		अगर (err) अणु
			bphy_err(drvr, "failed to clean up user-space RSNE\n");
			जाओ करोne;
		पूर्ण
		err = brcmf_set_sae_password(अगरp, sme->crypto.sae_pwd,
					     sme->crypto.sae_pwd_len);
		अगर (!err && sme->crypto.psk)
			err = brcmf_set_pmk(अगरp, sme->crypto.psk,
					    BRCMF_WSEC_MAX_PSK_LEN);
	पूर्ण
	अगर (err)
		जाओ करोne;

	/* Join with specअगरic BSSID and cached SSID
	 * If SSID is zero join based on BSSID only
	 */
	join_params_size = दुरत्व(काष्ठा brcmf_ext_join_params_le, assoc_le) +
		दुरत्व(काष्ठा brcmf_assoc_params_le, chanspec_list);
	अगर (cfg->channel)
		join_params_size += माप(u16);
	ext_join_params = kzalloc(join_params_size, GFP_KERNEL);
	अगर (ext_join_params == शून्य) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण
	ssid_len = min_t(u32, sme->ssid_len, IEEE80211_MAX_SSID_LEN);
	ext_join_params->ssid_le.SSID_len = cpu_to_le32(ssid_len);
	स_नकल(&ext_join_params->ssid_le.SSID, sme->ssid, ssid_len);
	अगर (ssid_len < IEEE80211_MAX_SSID_LEN)
		brcmf_dbg(CONN, "SSID \"%s\", len (%d)\n",
			  ext_join_params->ssid_le.SSID, ssid_len);

	/* Set up join scan parameters */
	ext_join_params->scan_le.scan_type = -1;
	ext_join_params->scan_le.home_समय = cpu_to_le32(-1);

	अगर (sme->bssid)
		स_नकल(&ext_join_params->assoc_le.bssid, sme->bssid, ETH_ALEN);
	अन्यथा
		eth_broadcast_addr(ext_join_params->assoc_le.bssid);

	अगर (cfg->channel) अणु
		ext_join_params->assoc_le.chanspec_num = cpu_to_le32(1);

		ext_join_params->assoc_le.chanspec_list[0] =
			cpu_to_le16(chanspec);
		/* Increase dwell समय to receive probe response or detect
		 * beacon from target AP at a noisy air only during connect
		 * command.
		 */
		ext_join_params->scan_le.active_समय =
			cpu_to_le32(BRCMF_SCAN_JOIN_ACTIVE_DWELL_TIME_MS);
		ext_join_params->scan_le.passive_समय =
			cpu_to_le32(BRCMF_SCAN_JOIN_PASSIVE_DWELL_TIME_MS);
		/* To sync with presence period of VSDB GO send probe request
		 * more frequently. Probe request will be stopped when it माला_लो
		 * probe response from target AP/GO.
		 */
		ext_join_params->scan_le.nprobes =
			cpu_to_le32(BRCMF_SCAN_JOIN_ACTIVE_DWELL_TIME_MS /
				    BRCMF_SCAN_JOIN_PROBE_INTERVAL_MS);
	पूर्ण अन्यथा अणु
		ext_join_params->scan_le.active_समय = cpu_to_le32(-1);
		ext_join_params->scan_le.passive_समय = cpu_to_le32(-1);
		ext_join_params->scan_le.nprobes = cpu_to_le32(-1);
	पूर्ण

	brcmf_set_join_pref(अगरp, &sme->bss_select);

	err  = brcmf_fil_bsscfg_data_set(अगरp, "join", ext_join_params,
					 join_params_size);
	kमुक्त(ext_join_params);
	अगर (!err)
		/* This is it. join command worked, we are करोne */
		जाओ करोne;

	/* join command failed, fallback to set ssid */
	स_रखो(&join_params, 0, माप(join_params));
	join_params_size = माप(join_params.ssid_le);

	स_नकल(&join_params.ssid_le.SSID, sme->ssid, ssid_len);
	join_params.ssid_le.SSID_len = cpu_to_le32(ssid_len);

	अगर (sme->bssid)
		स_नकल(join_params.params_le.bssid, sme->bssid, ETH_ALEN);
	अन्यथा
		eth_broadcast_addr(join_params.params_le.bssid);

	अगर (cfg->channel) अणु
		join_params.params_le.chanspec_list[0] = cpu_to_le16(chanspec);
		join_params.params_le.chanspec_num = cpu_to_le32(1);
		join_params_size += माप(join_params.params_le);
	पूर्ण
	err = brcmf_fil_cmd_data_set(अगरp, BRCMF_C_SET_SSID,
				     &join_params, join_params_size);
	अगर (err)
		bphy_err(drvr, "BRCMF_C_SET_SSID failed (%d)\n", err);

करोne:
	अगर (err)
		clear_bit(BRCMF_VIF_STATUS_CONNECTING, &अगरp->vअगर->sme_state);
	brcmf_dbg(TRACE, "Exit\n");
	वापस err;
पूर्ण

अटल s32
brcmf_cfg80211_disconnect(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
		       u16 reason_code)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_cfg80211_profile *profile = &अगरp->vअगर->profile;
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_scb_val_le scbval;
	s32 err = 0;

	brcmf_dbg(TRACE, "Enter. Reason code = %d\n", reason_code);
	अगर (!check_vअगर_up(अगरp->vअगर))
		वापस -EIO;

	clear_bit(BRCMF_VIF_STATUS_CONNECTED, &अगरp->vअगर->sme_state);
	clear_bit(BRCMF_VIF_STATUS_CONNECTING, &अगरp->vअगर->sme_state);
	cfg80211_disconnected(ndev, reason_code, शून्य, 0, true, GFP_KERNEL);

	स_नकल(&scbval.ea, &profile->bssid, ETH_ALEN);
	scbval.val = cpu_to_le32(reason_code);
	err = brcmf_fil_cmd_data_set(अगरp, BRCMF_C_DISASSOC,
				     &scbval, माप(scbval));
	अगर (err)
		bphy_err(drvr, "error (%d)\n", err);

	brcmf_dbg(TRACE, "Exit\n");
	वापस err;
पूर्ण

अटल s32
brcmf_cfg80211_set_tx_घातer(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			    क्रमागत nl80211_tx_घातer_setting type, s32 mbm)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा net_device *ndev = cfg_to_ndev(cfg);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	s32 err;
	s32 disable;
	u32 qdbm = 127;

	brcmf_dbg(TRACE, "Enter %d %d\n", type, mbm);
	अगर (!check_vअगर_up(अगरp->vअगर))
		वापस -EIO;

	चयन (type) अणु
	हाल NL80211_TX_POWER_AUTOMATIC:
		अवरोध;
	हाल NL80211_TX_POWER_LIMITED:
	हाल NL80211_TX_POWER_FIXED:
		अगर (mbm < 0) अणु
			bphy_err(drvr, "TX_POWER_FIXED - dbm is negative\n");
			err = -EINVAL;
			जाओ करोne;
		पूर्ण
		qdbm =  MBM_TO_DBM(4 * mbm);
		अगर (qdbm > 127)
			qdbm = 127;
		qdbm |= WL_TXPWR_OVERRIDE;
		अवरोध;
	शेष:
		bphy_err(drvr, "Unsupported type %d\n", type);
		err = -EINVAL;
		जाओ करोne;
	पूर्ण
	/* Make sure radio is off or on as far as software is concerned */
	disable = WL_RADIO_SW_DISABLE << 16;
	err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_RADIO, disable);
	अगर (err)
		bphy_err(drvr, "WLC_SET_RADIO error (%d)\n", err);

	err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "qtxpower", qdbm);
	अगर (err)
		bphy_err(drvr, "qtxpower error (%d)\n", err);

करोne:
	brcmf_dbg(TRACE, "Exit %d (qdbm)\n", qdbm & ~WL_TXPWR_OVERRIDE);
	वापस err;
पूर्ण

अटल s32
brcmf_cfg80211_get_tx_घातer(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			    s32 *dbm)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_cfg80211_vअगर *vअगर = wdev_to_vअगर(wdev);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	s32 qdbm = 0;
	s32 err;

	brcmf_dbg(TRACE, "Enter\n");
	अगर (!check_vअगर_up(vअगर))
		वापस -EIO;

	err = brcmf_fil_iovar_पूर्णांक_get(vअगर->अगरp, "qtxpower", &qdbm);
	अगर (err) अणु
		bphy_err(drvr, "error (%d)\n", err);
		जाओ करोne;
	पूर्ण
	*dbm = (qdbm & ~WL_TXPWR_OVERRIDE) / 4;

करोne:
	brcmf_dbg(TRACE, "Exit (0x%x %d)\n", qdbm, *dbm);
	वापस err;
पूर्ण

अटल s32
brcmf_cfg80211_config_शेष_key(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
				  u8 key_idx, bool unicast, bool multicast)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	u32 index;
	u32 wsec;
	s32 err = 0;

	brcmf_dbg(TRACE, "Enter\n");
	brcmf_dbg(CONN, "key index (%d)\n", key_idx);
	अगर (!check_vअगर_up(अगरp->vअगर))
		वापस -EIO;

	err = brcmf_fil_bsscfg_पूर्णांक_get(अगरp, "wsec", &wsec);
	अगर (err) अणु
		bphy_err(drvr, "WLC_GET_WSEC error (%d)\n", err);
		जाओ करोne;
	पूर्ण

	अगर (wsec & WEP_ENABLED) अणु
		/* Just select a new current key */
		index = key_idx;
		err = brcmf_fil_cmd_पूर्णांक_set(अगरp,
					    BRCMF_C_SET_KEY_PRIMARY, index);
		अगर (err)
			bphy_err(drvr, "error (%d)\n", err);
	पूर्ण
करोne:
	brcmf_dbg(TRACE, "Exit\n");
	वापस err;
पूर्ण

अटल s32
brcmf_cfg80211_del_key(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
		       u8 key_idx, bool pairwise, स्थिर u8 *mac_addr)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_wsec_key *key;
	s32 err;

	brcmf_dbg(TRACE, "Enter\n");
	brcmf_dbg(CONN, "key index (%d)\n", key_idx);

	अगर (!check_vअगर_up(अगरp->vअगर))
		वापस -EIO;

	अगर (key_idx >= BRCMF_MAX_DEFAULT_KEYS) अणु
		/* we ignore this key index in this हाल */
		वापस -EINVAL;
	पूर्ण

	key = &अगरp->vअगर->profile.key[key_idx];

	अगर (key->algo == CRYPTO_ALGO_OFF) अणु
		brcmf_dbg(CONN, "Ignore clearing of (never configured) key\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(key, 0, माप(*key));
	key->index = (u32)key_idx;
	key->flags = BRCMF_PRIMARY_KEY;

	/* Clear the key/index */
	err = send_key_to_करोngle(अगरp, key);

	brcmf_dbg(TRACE, "Exit\n");
	वापस err;
पूर्ण

अटल s32
brcmf_cfg80211_add_key(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
		       u8 key_idx, bool pairwise, स्थिर u8 *mac_addr,
		       काष्ठा key_params *params)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_wsec_key *key;
	s32 val;
	s32 wsec;
	s32 err;
	u8 keybuf[8];
	bool ext_key;

	brcmf_dbg(TRACE, "Enter\n");
	brcmf_dbg(CONN, "key index (%d)\n", key_idx);
	अगर (!check_vअगर_up(अगरp->vअगर))
		वापस -EIO;

	अगर (key_idx >= BRCMF_MAX_DEFAULT_KEYS) अणु
		/* we ignore this key index in this हाल */
		bphy_err(drvr, "invalid key index (%d)\n", key_idx);
		वापस -EINVAL;
	पूर्ण

	अगर (params->key_len == 0)
		वापस brcmf_cfg80211_del_key(wiphy, ndev, key_idx, pairwise,
					      mac_addr);

	अगर (params->key_len > माप(key->data)) अणु
		bphy_err(drvr, "Too long key length (%u)\n", params->key_len);
		वापस -EINVAL;
	पूर्ण

	ext_key = false;
	अगर (mac_addr && (params->cipher != WLAN_CIPHER_SUITE_WEP40) &&
	    (params->cipher != WLAN_CIPHER_SUITE_WEP104)) अणु
		brcmf_dbg(TRACE, "Ext key, mac %pM", mac_addr);
		ext_key = true;
	पूर्ण

	key = &अगरp->vअगर->profile.key[key_idx];
	स_रखो(key, 0, माप(*key));
	अगर ((ext_key) && (!is_multicast_ether_addr(mac_addr)))
		स_नकल((अक्षर *)&key->ea, (व्योम *)mac_addr, ETH_ALEN);
	key->len = params->key_len;
	key->index = key_idx;
	स_नकल(key->data, params->key, key->len);
	अगर (!ext_key)
		key->flags = BRCMF_PRIMARY_KEY;

	अगर (params->seq && params->seq_len == 6) अणु
		/* rx iv */
		u8 *ivptr;

		ivptr = (u8 *)params->seq;
		key->rxiv.hi = (ivptr[5] << 24) | (ivptr[4] << 16) |
			(ivptr[3] << 8) | ivptr[2];
		key->rxiv.lo = (ivptr[1] << 8) | ivptr[0];
		key->iv_initialized = true;
	पूर्ण

	चयन (params->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
		key->algo = CRYPTO_ALGO_WEP1;
		val = WEP_ENABLED;
		brcmf_dbg(CONN, "WLAN_CIPHER_SUITE_WEP40\n");
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP104:
		key->algo = CRYPTO_ALGO_WEP128;
		val = WEP_ENABLED;
		brcmf_dbg(CONN, "WLAN_CIPHER_SUITE_WEP104\n");
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		अगर (!brcmf_is_apmode(अगरp->vअगर)) अणु
			brcmf_dbg(CONN, "Swapping RX/TX MIC key\n");
			स_नकल(keybuf, &key->data[24], माप(keybuf));
			स_नकल(&key->data[24], &key->data[16], माप(keybuf));
			स_नकल(&key->data[16], keybuf, माप(keybuf));
		पूर्ण
		key->algo = CRYPTO_ALGO_TKIP;
		val = TKIP_ENABLED;
		brcmf_dbg(CONN, "WLAN_CIPHER_SUITE_TKIP\n");
		अवरोध;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
		key->algo = CRYPTO_ALGO_AES_CCM;
		val = AES_ENABLED;
		brcmf_dbg(CONN, "WLAN_CIPHER_SUITE_AES_CMAC\n");
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		key->algo = CRYPTO_ALGO_AES_CCM;
		val = AES_ENABLED;
		brcmf_dbg(CONN, "WLAN_CIPHER_SUITE_CCMP\n");
		अवरोध;
	शेष:
		bphy_err(drvr, "Invalid cipher (0x%x)\n", params->cipher);
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	err = send_key_to_करोngle(अगरp, key);
	अगर (ext_key || err)
		जाओ करोne;

	err = brcmf_fil_bsscfg_पूर्णांक_get(अगरp, "wsec", &wsec);
	अगर (err) अणु
		bphy_err(drvr, "get wsec error (%d)\n", err);
		जाओ करोne;
	पूर्ण
	wsec |= val;
	err = brcmf_fil_bsscfg_पूर्णांक_set(अगरp, "wsec", wsec);
	अगर (err) अणु
		bphy_err(drvr, "set wsec error (%d)\n", err);
		जाओ करोne;
	पूर्ण

करोne:
	brcmf_dbg(TRACE, "Exit\n");
	वापस err;
पूर्ण

अटल s32
brcmf_cfg80211_get_key(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev, u8 key_idx,
		       bool pairwise, स्थिर u8 *mac_addr, व्योम *cookie,
		       व्योम (*callback)(व्योम *cookie,
					काष्ठा key_params *params))
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा key_params params;
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_cfg80211_profile *profile = &अगरp->vअगर->profile;
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_cfg80211_security *sec;
	s32 wsec;
	s32 err = 0;

	brcmf_dbg(TRACE, "Enter\n");
	brcmf_dbg(CONN, "key index (%d)\n", key_idx);
	अगर (!check_vअगर_up(अगरp->vअगर))
		वापस -EIO;

	स_रखो(&params, 0, माप(params));

	err = brcmf_fil_bsscfg_पूर्णांक_get(अगरp, "wsec", &wsec);
	अगर (err) अणु
		bphy_err(drvr, "WLC_GET_WSEC error (%d)\n", err);
		/* Ignore this error, may happen during DISASSOC */
		err = -EAGAIN;
		जाओ करोne;
	पूर्ण
	अगर (wsec & WEP_ENABLED) अणु
		sec = &profile->sec;
		अगर (sec->cipher_pairwise & WLAN_CIPHER_SUITE_WEP40) अणु
			params.cipher = WLAN_CIPHER_SUITE_WEP40;
			brcmf_dbg(CONN, "WLAN_CIPHER_SUITE_WEP40\n");
		पूर्ण अन्यथा अगर (sec->cipher_pairwise & WLAN_CIPHER_SUITE_WEP104) अणु
			params.cipher = WLAN_CIPHER_SUITE_WEP104;
			brcmf_dbg(CONN, "WLAN_CIPHER_SUITE_WEP104\n");
		पूर्ण
	पूर्ण अन्यथा अगर (wsec & TKIP_ENABLED) अणु
		params.cipher = WLAN_CIPHER_SUITE_TKIP;
		brcmf_dbg(CONN, "WLAN_CIPHER_SUITE_TKIP\n");
	पूर्ण अन्यथा अगर (wsec & AES_ENABLED) अणु
		params.cipher = WLAN_CIPHER_SUITE_AES_CMAC;
		brcmf_dbg(CONN, "WLAN_CIPHER_SUITE_AES_CMAC\n");
	पूर्ण अन्यथा  अणु
		bphy_err(drvr, "Invalid algo (0x%x)\n", wsec);
		err = -EINVAL;
		जाओ करोne;
	पूर्ण
	callback(cookie, &params);

करोne:
	brcmf_dbg(TRACE, "Exit\n");
	वापस err;
पूर्ण

अटल s32
brcmf_cfg80211_config_शेष_mgmt_key(काष्ठा wiphy *wiphy,
				       काष्ठा net_device *ndev, u8 key_idx)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);

	brcmf_dbg(TRACE, "Enter key_idx %d\n", key_idx);

	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_MFP))
		वापस 0;

	brcmf_dbg(INFO, "Not supported\n");

	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम
brcmf_cfg80211_reconfigure_wep(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 err;
	u8 key_idx;
	काष्ठा brcmf_wsec_key *key;
	s32 wsec;

	क्रम (key_idx = 0; key_idx < BRCMF_MAX_DEFAULT_KEYS; key_idx++) अणु
		key = &अगरp->vअगर->profile.key[key_idx];
		अगर ((key->algo == CRYPTO_ALGO_WEP1) ||
		    (key->algo == CRYPTO_ALGO_WEP128))
			अवरोध;
	पूर्ण
	अगर (key_idx == BRCMF_MAX_DEFAULT_KEYS)
		वापस;

	err = send_key_to_करोngle(अगरp, key);
	अगर (err) अणु
		bphy_err(drvr, "Setting WEP key failed (%d)\n", err);
		वापस;
	पूर्ण
	err = brcmf_fil_bsscfg_पूर्णांक_get(अगरp, "wsec", &wsec);
	अगर (err) अणु
		bphy_err(drvr, "get wsec error (%d)\n", err);
		वापस;
	पूर्ण
	wsec |= WEP_ENABLED;
	err = brcmf_fil_bsscfg_पूर्णांक_set(अगरp, "wsec", wsec);
	अगर (err)
		bphy_err(drvr, "set wsec error (%d)\n", err);
पूर्ण

अटल व्योम brcmf_convert_sta_flags(u32 fw_sta_flags, काष्ठा station_info *si)
अणु
	काष्ठा nl80211_sta_flag_update *sfu;

	brcmf_dbg(TRACE, "flags %08x\n", fw_sta_flags);
	si->filled |= BIT_ULL(NL80211_STA_INFO_STA_FLAGS);
	sfu = &si->sta_flags;
	sfu->mask = BIT(NL80211_STA_FLAG_WME) |
		    BIT(NL80211_STA_FLAG_AUTHENTICATED) |
		    BIT(NL80211_STA_FLAG_ASSOCIATED) |
		    BIT(NL80211_STA_FLAG_AUTHORIZED);
	अगर (fw_sta_flags & BRCMF_STA_WME)
		sfu->set |= BIT(NL80211_STA_FLAG_WME);
	अगर (fw_sta_flags & BRCMF_STA_AUTHE)
		sfu->set |= BIT(NL80211_STA_FLAG_AUTHENTICATED);
	अगर (fw_sta_flags & BRCMF_STA_ASSOC)
		sfu->set |= BIT(NL80211_STA_FLAG_ASSOCIATED);
	अगर (fw_sta_flags & BRCMF_STA_AUTHO)
		sfu->set |= BIT(NL80211_STA_FLAG_AUTHORIZED);
पूर्ण

अटल व्योम brcmf_fill_bss_param(काष्ठा brcmf_अगर *अगरp, काष्ठा station_info *si)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा अणु
		__le32 len;
		काष्ठा brcmf_bss_info_le bss_le;
	पूर्ण *buf;
	u16 capability;
	पूर्णांक err;

	buf = kzalloc(WL_BSS_INFO_MAX, GFP_KERNEL);
	अगर (!buf)
		वापस;

	buf->len = cpu_to_le32(WL_BSS_INFO_MAX);
	err = brcmf_fil_cmd_data_get(अगरp, BRCMF_C_GET_BSS_INFO, buf,
				     WL_BSS_INFO_MAX);
	अगर (err) अणु
		bphy_err(drvr, "Failed to get bss info (%d)\n", err);
		जाओ out_kमुक्त;
	पूर्ण
	si->filled |= BIT_ULL(NL80211_STA_INFO_BSS_PARAM);
	si->bss_param.beacon_पूर्णांकerval = le16_to_cpu(buf->bss_le.beacon_period);
	si->bss_param.dtim_period = buf->bss_le.dtim_period;
	capability = le16_to_cpu(buf->bss_le.capability);
	अगर (capability & IEEE80211_HT_STBC_PARAM_DUAL_CTS_PROT)
		si->bss_param.flags |= BSS_PARAM_FLAGS_CTS_PROT;
	अगर (capability & WLAN_CAPABILITY_SHORT_PREAMBLE)
		si->bss_param.flags |= BSS_PARAM_FLAGS_SHORT_PREAMBLE;
	अगर (capability & WLAN_CAPABILITY_SHORT_SLOT_TIME)
		si->bss_param.flags |= BSS_PARAM_FLAGS_SHORT_SLOT_TIME;

out_kमुक्त:
	kमुक्त(buf);
पूर्ण

अटल s32
brcmf_cfg80211_get_station_ibss(काष्ठा brcmf_अगर *अगरp,
				काष्ठा station_info *sinfo)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_scb_val_le scbval;
	काष्ठा brcmf_pktcnt_le pktcnt;
	s32 err;
	u32 rate;
	u32 rssi;

	/* Get the current tx rate */
	err = brcmf_fil_cmd_पूर्णांक_get(अगरp, BRCMF_C_GET_RATE, &rate);
	अगर (err < 0) अणु
		bphy_err(drvr, "BRCMF_C_GET_RATE error (%d)\n", err);
		वापस err;
	पूर्ण
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
	sinfo->txrate.legacy = rate * 5;

	स_रखो(&scbval, 0, माप(scbval));
	err = brcmf_fil_cmd_data_get(अगरp, BRCMF_C_GET_RSSI, &scbval,
				     माप(scbval));
	अगर (err) अणु
		bphy_err(drvr, "BRCMF_C_GET_RSSI error (%d)\n", err);
		वापस err;
	पूर्ण
	rssi = le32_to_cpu(scbval.val);
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
	sinfo->संकेत = rssi;

	err = brcmf_fil_cmd_data_get(अगरp, BRCMF_C_GET_GET_PKTCNTS, &pktcnt,
				     माप(pktcnt));
	अगर (err) अणु
		bphy_err(drvr, "BRCMF_C_GET_GET_PKTCNTS error (%d)\n", err);
		वापस err;
	पूर्ण
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_PACKETS) |
			 BIT_ULL(NL80211_STA_INFO_RX_DROP_MISC) |
			 BIT_ULL(NL80211_STA_INFO_TX_PACKETS) |
			 BIT_ULL(NL80211_STA_INFO_TX_FAILED);
	sinfo->rx_packets = le32_to_cpu(pktcnt.rx_good_pkt);
	sinfo->rx_dropped_misc = le32_to_cpu(pktcnt.rx_bad_pkt);
	sinfo->tx_packets = le32_to_cpu(pktcnt.tx_good_pkt);
	sinfo->tx_failed  = le32_to_cpu(pktcnt.tx_bad_pkt);

	वापस 0;
पूर्ण

अटल s32
brcmf_cfg80211_get_station(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
			   स्थिर u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_scb_val_le scb_val;
	s32 err = 0;
	काष्ठा brcmf_sta_info_le sta_info_le;
	u32 sta_flags;
	u32 is_tdls_peer;
	s32 total_rssi;
	s32 count_rssi;
	पूर्णांक rssi;
	u32 i;

	brcmf_dbg(TRACE, "Enter, MAC %pM\n", mac);
	अगर (!check_vअगर_up(अगरp->vअगर))
		वापस -EIO;

	अगर (brcmf_is_ibssmode(अगरp->vअगर))
		वापस brcmf_cfg80211_get_station_ibss(अगरp, sinfo);

	स_रखो(&sta_info_le, 0, माप(sta_info_le));
	स_नकल(&sta_info_le, mac, ETH_ALEN);
	err = brcmf_fil_iovar_data_get(अगरp, "tdls_sta_info",
				       &sta_info_le,
				       माप(sta_info_le));
	is_tdls_peer = !err;
	अगर (err) अणु
		err = brcmf_fil_iovar_data_get(अगरp, "sta_info",
					       &sta_info_le,
					       माप(sta_info_le));
		अगर (err < 0) अणु
			bphy_err(drvr, "GET STA INFO failed, %d\n", err);
			जाओ करोne;
		पूर्ण
	पूर्ण
	brcmf_dbg(TRACE, "version %d\n", le16_to_cpu(sta_info_le.ver));
	sinfo->filled = BIT_ULL(NL80211_STA_INFO_INACTIVE_TIME);
	sinfo->inactive_समय = le32_to_cpu(sta_info_le.idle) * 1000;
	sta_flags = le32_to_cpu(sta_info_le.flags);
	brcmf_convert_sta_flags(sta_flags, sinfo);
	sinfo->sta_flags.mask |= BIT(NL80211_STA_FLAG_TDLS_PEER);
	अगर (is_tdls_peer)
		sinfo->sta_flags.set |= BIT(NL80211_STA_FLAG_TDLS_PEER);
	अन्यथा
		sinfo->sta_flags.set &= ~BIT(NL80211_STA_FLAG_TDLS_PEER);
	अगर (sta_flags & BRCMF_STA_ASSOC) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_CONNECTED_TIME);
		sinfo->connected_समय = le32_to_cpu(sta_info_le.in);
		brcmf_fill_bss_param(अगरp, sinfo);
	पूर्ण
	अगर (sta_flags & BRCMF_STA_SCBSTATS) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_FAILED);
		sinfo->tx_failed = le32_to_cpu(sta_info_le.tx_failures);
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_PACKETS);
		sinfo->tx_packets = le32_to_cpu(sta_info_le.tx_pkts);
		sinfo->tx_packets += le32_to_cpu(sta_info_le.tx_mcast_pkts);
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_PACKETS);
		sinfo->rx_packets = le32_to_cpu(sta_info_le.rx_ucast_pkts);
		sinfo->rx_packets += le32_to_cpu(sta_info_le.rx_mcast_pkts);
		अगर (sinfo->tx_packets) अणु
			sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
			sinfo->txrate.legacy =
				le32_to_cpu(sta_info_le.tx_rate) / 100;
		पूर्ण
		अगर (sinfo->rx_packets) अणु
			sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_BITRATE);
			sinfo->rxrate.legacy =
				le32_to_cpu(sta_info_le.rx_rate) / 100;
		पूर्ण
		अगर (le16_to_cpu(sta_info_le.ver) >= 4) अणु
			sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BYTES);
			sinfo->tx_bytes = le64_to_cpu(sta_info_le.tx_tot_bytes);
			sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_BYTES);
			sinfo->rx_bytes = le64_to_cpu(sta_info_le.rx_tot_bytes);
		पूर्ण
		total_rssi = 0;
		count_rssi = 0;
		क्रम (i = 0; i < BRCMF_ANT_MAX; i++) अणु
			अगर (sta_info_le.rssi[i]) अणु
				sinfo->chain_संकेत_avg[count_rssi] =
					sta_info_le.rssi[i];
				sinfo->chain_संकेत[count_rssi] =
					sta_info_le.rssi[i];
				total_rssi += sta_info_le.rssi[i];
				count_rssi++;
			पूर्ण
		पूर्ण
		अगर (count_rssi) अणु
			sinfo->filled |= BIT_ULL(NL80211_STA_INFO_CHAIN_SIGNAL);
			sinfo->chains = count_rssi;

			sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
			total_rssi /= count_rssi;
			sinfo->संकेत = total_rssi;
		पूर्ण अन्यथा अगर (test_bit(BRCMF_VIF_STATUS_CONNECTED,
			&अगरp->vअगर->sme_state)) अणु
			स_रखो(&scb_val, 0, माप(scb_val));
			err = brcmf_fil_cmd_data_get(अगरp, BRCMF_C_GET_RSSI,
						     &scb_val, माप(scb_val));
			अगर (err) अणु
				bphy_err(drvr, "Could not get rssi (%d)\n",
					 err);
				जाओ करोne;
			पूर्ण अन्यथा अणु
				rssi = le32_to_cpu(scb_val.val);
				sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
				sinfo->संकेत = rssi;
				brcmf_dbg(CONN, "RSSI %d dBm\n", rssi);
			पूर्ण
		पूर्ण
	पूर्ण
करोne:
	brcmf_dbg(TRACE, "Exit\n");
	वापस err;
पूर्ण

अटल पूर्णांक
brcmf_cfg80211_dump_station(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
			    पूर्णांक idx, u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	s32 err;

	brcmf_dbg(TRACE, "Enter, idx %d\n", idx);

	अगर (idx == 0) अणु
		cfg->assoclist.count = cpu_to_le32(BRCMF_MAX_ASSOCLIST);
		err = brcmf_fil_cmd_data_get(अगरp, BRCMF_C_GET_ASSOCLIST,
					     &cfg->assoclist,
					     माप(cfg->assoclist));
		अगर (err) अणु
			bphy_err(drvr, "BRCMF_C_GET_ASSOCLIST unsupported, err=%d\n",
				 err);
			cfg->assoclist.count = 0;
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण
	अगर (idx < le32_to_cpu(cfg->assoclist.count)) अणु
		स_नकल(mac, cfg->assoclist.mac[idx], ETH_ALEN);
		वापस brcmf_cfg80211_get_station(wiphy, ndev, mac, sinfo);
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल s32
brcmf_cfg80211_set_घातer_mgmt(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
			   bool enabled, s32 समयout)
अणु
	s32 pm;
	s32 err = 0;
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = cfg->pub;

	brcmf_dbg(TRACE, "Enter\n");

	/*
	 * Powersave enable/disable request is coming from the
	 * cfg80211 even beक्रमe the पूर्णांकerface is up. In that
	 * scenario, driver will be storing the घातer save
	 * preference in cfg काष्ठा to apply this to
	 * FW later जबतक initializing the करोngle
	 */
	cfg->pwr_save = enabled;
	अगर (!check_vअगर_up(अगरp->vअगर)) अणु

		brcmf_dbg(INFO, "Device is not ready, storing the value in cfg_info struct\n");
		जाओ करोne;
	पूर्ण

	pm = enabled ? PM_FAST : PM_OFF;
	/* Do not enable the घातer save after assoc अगर it is a p2p पूर्णांकerface */
	अगर (अगरp->vअगर->wdev.अगरtype == NL80211_IFTYPE_P2P_CLIENT) अणु
		brcmf_dbg(INFO, "Do not enable power save for P2P clients\n");
		pm = PM_OFF;
	पूर्ण
	brcmf_dbg(INFO, "power save %s\n", (pm ? "enabled" : "disabled"));

	err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_PM, pm);
	अगर (err) अणु
		अगर (err == -ENODEV)
			bphy_err(drvr, "net_device is not ready yet\n");
		अन्यथा
			bphy_err(drvr, "error (%d)\n", err);
	पूर्ण

	err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "pm2_sleep_ret",
				min_t(u32, समयout, BRCMF_PS_MAX_TIMEOUT_MS));
	अगर (err)
		bphy_err(drvr, "Unable to set pm timeout, (%d)\n", err);

करोne:
	brcmf_dbg(TRACE, "Exit\n");
	वापस err;
पूर्ण

अटल s32 brcmf_inक्रमm_single_bss(काष्ठा brcmf_cfg80211_info *cfg,
				   काष्ठा brcmf_bss_info_le *bi)
अणु
	काष्ठा wiphy *wiphy = cfg_to_wiphy(cfg);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा cfg80211_bss *bss;
	क्रमागत nl80211_band band;
	काष्ठा brcmu_chan ch;
	u16 channel;
	u32 freq;
	u16 notअगरy_capability;
	u16 notअगरy_पूर्णांकerval;
	u8 *notअगरy_ie;
	माप_प्रकार notअगरy_ielen;
	काष्ठा cfg80211_inक्रमm_bss bss_data = अणुपूर्ण;

	अगर (le32_to_cpu(bi->length) > WL_BSS_INFO_MAX) अणु
		bphy_err(drvr, "Bss info is larger than buffer. Discarding\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!bi->ctl_ch) अणु
		ch.chspec = le16_to_cpu(bi->chanspec);
		cfg->d11inf.decchspec(&ch);
		bi->ctl_ch = ch.control_ch_num;
	पूर्ण
	channel = bi->ctl_ch;

	अगर (channel <= CH_MAX_2G_CHANNEL)
		band = NL80211_BAND_2GHZ;
	अन्यथा
		band = NL80211_BAND_5GHZ;

	freq = ieee80211_channel_to_frequency(channel, band);
	bss_data.chan = ieee80211_get_channel(wiphy, freq);
	bss_data.scan_width = NL80211_BSS_CHAN_WIDTH_20;
	bss_data.bootसमय_ns = kसमय_प्रकारo_ns(kसमय_get_bootसमय());

	notअगरy_capability = le16_to_cpu(bi->capability);
	notअगरy_पूर्णांकerval = le16_to_cpu(bi->beacon_period);
	notअगरy_ie = (u8 *)bi + le16_to_cpu(bi->ie_offset);
	notअगरy_ielen = le32_to_cpu(bi->ie_length);
	bss_data.संकेत = (s16)le16_to_cpu(bi->RSSI) * 100;

	brcmf_dbg(CONN, "bssid: %pM\n", bi->BSSID);
	brcmf_dbg(CONN, "Channel: %d(%d)\n", channel, freq);
	brcmf_dbg(CONN, "Capability: %X\n", notअगरy_capability);
	brcmf_dbg(CONN, "Beacon interval: %d\n", notअगरy_पूर्णांकerval);
	brcmf_dbg(CONN, "Signal: %d\n", bss_data.संकेत);

	bss = cfg80211_inक्रमm_bss_data(wiphy, &bss_data,
				       CFG80211_BSS_FTYPE_UNKNOWN,
				       (स्थिर u8 *)bi->BSSID,
				       0, notअगरy_capability,
				       notअगरy_पूर्णांकerval, notअगरy_ie,
				       notअगरy_ielen, GFP_KERNEL);

	अगर (!bss)
		वापस -ENOMEM;

	cfg80211_put_bss(wiphy, bss);

	वापस 0;
पूर्ण

अटल काष्ठा brcmf_bss_info_le *
next_bss_le(काष्ठा brcmf_scan_results *list, काष्ठा brcmf_bss_info_le *bss)
अणु
	अगर (bss == शून्य)
		वापस list->bss_info_le;
	वापस (काष्ठा brcmf_bss_info_le *)((अचिन्हित दीर्घ)bss +
					    le32_to_cpu(bss->length));
पूर्ण

अटल s32 brcmf_inक्रमm_bss(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_scan_results *bss_list;
	काष्ठा brcmf_bss_info_le *bi = शून्य;	/* must be initialized */
	s32 err = 0;
	पूर्णांक i;

	bss_list = (काष्ठा brcmf_scan_results *)cfg->escan_info.escan_buf;
	अगर (bss_list->count != 0 &&
	    bss_list->version != BRCMF_BSS_INFO_VERSION) अणु
		bphy_err(drvr, "Version %d != WL_BSS_INFO_VERSION\n",
			 bss_list->version);
		वापस -EOPNOTSUPP;
	पूर्ण
	brcmf_dbg(SCAN, "scanned AP count (%d)\n", bss_list->count);
	क्रम (i = 0; i < bss_list->count; i++) अणु
		bi = next_bss_le(bss_list, bi);
		err = brcmf_inक्रमm_single_bss(cfg, bi);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल s32 brcmf_inक्रमm_ibss(काष्ठा brcmf_cfg80211_info *cfg,
			     काष्ठा net_device *ndev, स्थिर u8 *bssid)
अणु
	काष्ठा wiphy *wiphy = cfg_to_wiphy(cfg);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा ieee80211_channel *notअगरy_channel;
	काष्ठा brcmf_bss_info_le *bi = शून्य;
	काष्ठा ieee80211_supported_band *band;
	काष्ठा cfg80211_bss *bss;
	काष्ठा brcmu_chan ch;
	u8 *buf = शून्य;
	s32 err = 0;
	u32 freq;
	u16 notअगरy_capability;
	u16 notअगरy_पूर्णांकerval;
	u8 *notअगरy_ie;
	माप_प्रकार notअगरy_ielen;
	s32 notअगरy_संकेत;

	brcmf_dbg(TRACE, "Enter\n");

	buf = kzalloc(WL_BSS_INFO_MAX, GFP_KERNEL);
	अगर (buf == शून्य) अणु
		err = -ENOMEM;
		जाओ CleanUp;
	पूर्ण

	*(__le32 *)buf = cpu_to_le32(WL_BSS_INFO_MAX);

	err = brcmf_fil_cmd_data_get(netdev_priv(ndev), BRCMF_C_GET_BSS_INFO,
				     buf, WL_BSS_INFO_MAX);
	अगर (err) अणु
		bphy_err(drvr, "WLC_GET_BSS_INFO failed: %d\n", err);
		जाओ CleanUp;
	पूर्ण

	bi = (काष्ठा brcmf_bss_info_le *)(buf + 4);

	ch.chspec = le16_to_cpu(bi->chanspec);
	cfg->d11inf.decchspec(&ch);

	अगर (ch.band == BRCMU_CHAN_BAND_2G)
		band = wiphy->bands[NL80211_BAND_2GHZ];
	अन्यथा
		band = wiphy->bands[NL80211_BAND_5GHZ];

	freq = ieee80211_channel_to_frequency(ch.control_ch_num, band->band);
	cfg->channel = freq;
	notअगरy_channel = ieee80211_get_channel(wiphy, freq);

	notअगरy_capability = le16_to_cpu(bi->capability);
	notअगरy_पूर्णांकerval = le16_to_cpu(bi->beacon_period);
	notअगरy_ie = (u8 *)bi + le16_to_cpu(bi->ie_offset);
	notअगरy_ielen = le32_to_cpu(bi->ie_length);
	notअगरy_संकेत = (s16)le16_to_cpu(bi->RSSI) * 100;

	brcmf_dbg(CONN, "channel: %d(%d)\n", ch.control_ch_num, freq);
	brcmf_dbg(CONN, "capability: %X\n", notअगरy_capability);
	brcmf_dbg(CONN, "beacon interval: %d\n", notअगरy_पूर्णांकerval);
	brcmf_dbg(CONN, "signal: %d\n", notअगरy_संकेत);

	bss = cfg80211_inक्रमm_bss(wiphy, notअगरy_channel,
				  CFG80211_BSS_FTYPE_UNKNOWN, bssid, 0,
				  notअगरy_capability, notअगरy_पूर्णांकerval,
				  notअगरy_ie, notअगरy_ielen, notअगरy_संकेत,
				  GFP_KERNEL);

	अगर (!bss) अणु
		err = -ENOMEM;
		जाओ CleanUp;
	पूर्ण

	cfg80211_put_bss(wiphy, bss);

CleanUp:

	kमुक्त(buf);

	brcmf_dbg(TRACE, "Exit\n");

	वापस err;
पूर्ण

अटल s32 brcmf_update_bss_info(काष्ठा brcmf_cfg80211_info *cfg,
				 काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_bss_info_le *bi;
	स्थिर काष्ठा brcmf_tlv *tim;
	माप_प्रकार ie_len;
	u8 *ie;
	s32 err = 0;

	brcmf_dbg(TRACE, "Enter\n");
	अगर (brcmf_is_ibssmode(अगरp->vअगर))
		वापस err;

	*(__le32 *)cfg->extra_buf = cpu_to_le32(WL_EXTRA_BUF_MAX);
	err = brcmf_fil_cmd_data_get(अगरp, BRCMF_C_GET_BSS_INFO,
				     cfg->extra_buf, WL_EXTRA_BUF_MAX);
	अगर (err) अणु
		bphy_err(drvr, "Could not get bss info %d\n", err);
		जाओ update_bss_info_out;
	पूर्ण

	bi = (काष्ठा brcmf_bss_info_le *)(cfg->extra_buf + 4);
	err = brcmf_inक्रमm_single_bss(cfg, bi);
	अगर (err)
		जाओ update_bss_info_out;

	ie = ((u8 *)bi) + le16_to_cpu(bi->ie_offset);
	ie_len = le32_to_cpu(bi->ie_length);

	tim = brcmf_parse_tlvs(ie, ie_len, WLAN_EID_TIM);
	अगर (!tim) अणु
		/*
		* active scan was करोne so we could not get dtim
		* inक्रमmation out of probe response.
		* so we speficially query dtim inक्रमmation to करोngle.
		*/
		u32 var;
		err = brcmf_fil_iovar_पूर्णांक_get(अगरp, "dtim_assoc", &var);
		अगर (err) अणु
			bphy_err(drvr, "wl dtim_assoc failed (%d)\n", err);
			जाओ update_bss_info_out;
		पूर्ण
	पूर्ण

update_bss_info_out:
	brcmf_dbg(TRACE, "Exit");
	वापस err;
पूर्ण

व्योम brcmf_पात_scanning(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	काष्ठा escan_info *escan = &cfg->escan_info;

	set_bit(BRCMF_SCAN_STATUS_ABORT, &cfg->scan_status);
	अगर (cfg->पूर्णांक_escan_map || cfg->scan_request) अणु
		escan->escan_state = WL_ESCAN_STATE_IDLE;
		brcmf_notअगरy_escan_complete(cfg, escan->अगरp, true, true);
	पूर्ण
	clear_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status);
	clear_bit(BRCMF_SCAN_STATUS_ABORT, &cfg->scan_status);
पूर्ण

अटल व्योम brcmf_cfg80211_escan_समयout_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा brcmf_cfg80211_info *cfg =
			container_of(work, काष्ठा brcmf_cfg80211_info,
				     escan_समयout_work);

	brcmf_inक्रमm_bss(cfg);
	brcmf_notअगरy_escan_complete(cfg, cfg->escan_info.अगरp, true, true);
पूर्ण

अटल व्योम brcmf_escan_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा brcmf_cfg80211_info *cfg =
			from_समयr(cfg, t, escan_समयout);
	काष्ठा brcmf_pub *drvr = cfg->pub;

	अगर (cfg->पूर्णांक_escan_map || cfg->scan_request) अणु
		bphy_err(drvr, "timer expired\n");
		schedule_work(&cfg->escan_समयout_work);
	पूर्ण
पूर्ण

अटल s32
brcmf_compare_update_same_bss(काष्ठा brcmf_cfg80211_info *cfg,
			      काष्ठा brcmf_bss_info_le *bss,
			      काष्ठा brcmf_bss_info_le *bss_info_le)
अणु
	काष्ठा brcmu_chan ch_bss, ch_bss_info_le;

	ch_bss.chspec = le16_to_cpu(bss->chanspec);
	cfg->d11inf.decchspec(&ch_bss);
	ch_bss_info_le.chspec = le16_to_cpu(bss_info_le->chanspec);
	cfg->d11inf.decchspec(&ch_bss_info_le);

	अगर (!स_भेद(&bss_info_le->BSSID, &bss->BSSID, ETH_ALEN) &&
		ch_bss.band == ch_bss_info_le.band &&
		bss_info_le->SSID_len == bss->SSID_len &&
		!स_भेद(bss_info_le->SSID, bss->SSID, bss_info_le->SSID_len)) अणु
		अगर ((bss->flags & BRCMF_BSS_RSSI_ON_CHANNEL) ==
			(bss_info_le->flags & BRCMF_BSS_RSSI_ON_CHANNEL)) अणु
			s16 bss_rssi = le16_to_cpu(bss->RSSI);
			s16 bss_info_rssi = le16_to_cpu(bss_info_le->RSSI);

			/* preserve max RSSI अगर the measurements are
			* both on-channel or both off-channel
			*/
			अगर (bss_info_rssi > bss_rssi)
				bss->RSSI = bss_info_le->RSSI;
		पूर्ण अन्यथा अगर ((bss->flags & BRCMF_BSS_RSSI_ON_CHANNEL) &&
			(bss_info_le->flags & BRCMF_BSS_RSSI_ON_CHANNEL) == 0) अणु
			/* preserve the on-channel rssi measurement
			* अगर the new measurement is off channel
			*/
			bss->RSSI = bss_info_le->RSSI;
			bss->flags |= BRCMF_BSS_RSSI_ON_CHANNEL;
		पूर्ण
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल s32
brcmf_cfg80211_escan_handler(काष्ठा brcmf_अगर *अगरp,
			     स्थिर काष्ठा brcmf_event_msg *e, व्योम *data)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_cfg80211_info *cfg = drvr->config;
	s32 status;
	काष्ठा brcmf_escan_result_le *escan_result_le;
	u32 escan_buflen;
	काष्ठा brcmf_bss_info_le *bss_info_le;
	काष्ठा brcmf_bss_info_le *bss = शून्य;
	u32 bi_length;
	काष्ठा brcmf_scan_results *list;
	u32 i;
	bool पातed;

	status = e->status;

	अगर (status == BRCMF_E_STATUS_ABORT)
		जाओ निकास;

	अगर (!test_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status)) अणु
		bphy_err(drvr, "scan not ready, bsscfgidx=%d\n",
			 अगरp->bsscfgidx);
		वापस -EPERM;
	पूर्ण

	अगर (status == BRCMF_E_STATUS_PARTIAL) अणु
		brcmf_dbg(SCAN, "ESCAN Partial result\n");
		अगर (e->datalen < माप(*escan_result_le)) अणु
			bphy_err(drvr, "invalid event data length\n");
			जाओ निकास;
		पूर्ण
		escan_result_le = (काष्ठा brcmf_escan_result_le *) data;
		अगर (!escan_result_le) अणु
			bphy_err(drvr, "Invalid escan result (NULL pointer)\n");
			जाओ निकास;
		पूर्ण
		escan_buflen = le32_to_cpu(escan_result_le->buflen);
		अगर (escan_buflen > BRCMF_ESCAN_BUF_SIZE ||
		    escan_buflen > e->datalen ||
		    escan_buflen < माप(*escan_result_le)) अणु
			bphy_err(drvr, "Invalid escan buffer length: %d\n",
				 escan_buflen);
			जाओ निकास;
		पूर्ण
		अगर (le16_to_cpu(escan_result_le->bss_count) != 1) अणु
			bphy_err(drvr, "Invalid bss_count %d: ignoring\n",
				 escan_result_le->bss_count);
			जाओ निकास;
		पूर्ण
		bss_info_le = &escan_result_le->bss_info_le;

		अगर (brcmf_p2p_scan_finding_common_channel(cfg, bss_info_le))
			जाओ निकास;

		अगर (!cfg->पूर्णांक_escan_map && !cfg->scan_request) अणु
			brcmf_dbg(SCAN, "result without cfg80211 request\n");
			जाओ निकास;
		पूर्ण

		bi_length = le32_to_cpu(bss_info_le->length);
		अगर (bi_length != escan_buflen -	WL_ESCAN_RESULTS_FIXED_SIZE) अणु
			bphy_err(drvr, "Ignoring invalid bss_info length: %d\n",
				 bi_length);
			जाओ निकास;
		पूर्ण

		अगर (!(cfg_to_wiphy(cfg)->पूर्णांकerface_modes &
					BIT(NL80211_IFTYPE_ADHOC))) अणु
			अगर (le16_to_cpu(bss_info_le->capability) &
						WLAN_CAPABILITY_IBSS) अणु
				bphy_err(drvr, "Ignoring IBSS result\n");
				जाओ निकास;
			पूर्ण
		पूर्ण

		list = (काष्ठा brcmf_scan_results *)
				cfg->escan_info.escan_buf;
		अगर (bi_length > BRCMF_ESCAN_BUF_SIZE - list->buflen) अणु
			bphy_err(drvr, "Buffer is too small: ignoring\n");
			जाओ निकास;
		पूर्ण

		क्रम (i = 0; i < list->count; i++) अणु
			bss = bss ? (काष्ठा brcmf_bss_info_le *)
				((अचिन्हित अक्षर *)bss +
				le32_to_cpu(bss->length)) : list->bss_info_le;
			अगर (brcmf_compare_update_same_bss(cfg, bss,
							  bss_info_le))
				जाओ निकास;
		पूर्ण
		स_नकल(&cfg->escan_info.escan_buf[list->buflen], bss_info_le,
		       bi_length);
		list->version = le32_to_cpu(bss_info_le->version);
		list->buflen += bi_length;
		list->count++;
	पूर्ण अन्यथा अणु
		cfg->escan_info.escan_state = WL_ESCAN_STATE_IDLE;
		अगर (brcmf_p2p_scan_finding_common_channel(cfg, शून्य))
			जाओ निकास;
		अगर (cfg->पूर्णांक_escan_map || cfg->scan_request) अणु
			brcmf_inक्रमm_bss(cfg);
			पातed = status != BRCMF_E_STATUS_SUCCESS;
			brcmf_notअगरy_escan_complete(cfg, अगरp, पातed, false);
		पूर्ण अन्यथा
			brcmf_dbg(SCAN, "Ignored scan complete result 0x%x\n",
				  status);
	पूर्ण
निकास:
	वापस 0;
पूर्ण

अटल व्योम brcmf_init_escan(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_ESCAN_RESULT,
			    brcmf_cfg80211_escan_handler);
	cfg->escan_info.escan_state = WL_ESCAN_STATE_IDLE;
	/* Init scan_समयout समयr */
	समयr_setup(&cfg->escan_समयout, brcmf_escan_समयout, 0);
	INIT_WORK(&cfg->escan_समयout_work,
		  brcmf_cfg80211_escan_समयout_worker);
पूर्ण

अटल काष्ठा cfg80211_scan_request *
brcmf_alloc_पूर्णांकernal_escan_request(काष्ठा wiphy *wiphy, u32 n_netinfo) अणु
	काष्ठा cfg80211_scan_request *req;
	माप_प्रकार req_size;

	req_size = माप(*req) +
		   n_netinfo * माप(req->channels[0]) +
		   n_netinfo * माप(*req->ssids);

	req = kzalloc(req_size, GFP_KERNEL);
	अगर (req) अणु
		req->wiphy = wiphy;
		req->ssids = (व्योम *)(&req->channels[0]) +
			     n_netinfo * माप(req->channels[0]);
	पूर्ण
	वापस req;
पूर्ण

अटल पूर्णांक brcmf_पूर्णांकernal_escan_add_info(काष्ठा cfg80211_scan_request *req,
					 u8 *ssid, u8 ssid_len, u8 channel)
अणु
	काष्ठा ieee80211_channel *chan;
	क्रमागत nl80211_band band;
	पूर्णांक freq, i;

	अगर (channel <= CH_MAX_2G_CHANNEL)
		band = NL80211_BAND_2GHZ;
	अन्यथा
		band = NL80211_BAND_5GHZ;

	freq = ieee80211_channel_to_frequency(channel, band);
	अगर (!freq)
		वापस -EINVAL;

	chan = ieee80211_get_channel(req->wiphy, freq);
	अगर (!chan)
		वापस -EINVAL;

	क्रम (i = 0; i < req->n_channels; i++) अणु
		अगर (req->channels[i] == chan)
			अवरोध;
	पूर्ण
	अगर (i == req->n_channels)
		req->channels[req->n_channels++] = chan;

	क्रम (i = 0; i < req->n_ssids; i++) अणु
		अगर (req->ssids[i].ssid_len == ssid_len &&
		    !स_भेद(req->ssids[i].ssid, ssid, ssid_len))
			अवरोध;
	पूर्ण
	अगर (i == req->n_ssids) अणु
		स_नकल(req->ssids[req->n_ssids].ssid, ssid, ssid_len);
		req->ssids[req->n_ssids++].ssid_len = ssid_len;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_start_पूर्णांकernal_escan(काष्ठा brcmf_अगर *अगरp, u32 fwmap,
				      काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = अगरp->drvr->config;
	पूर्णांक err;

	अगर (test_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status)) अणु
		अगर (cfg->पूर्णांक_escan_map)
			brcmf_dbg(SCAN, "aborting internal scan: map=%u\n",
				  cfg->पूर्णांक_escan_map);
		/* Abort any on-going scan */
		brcmf_पात_scanning(cfg);
	पूर्ण

	brcmf_dbg(SCAN, "start internal scan: map=%u\n", fwmap);
	set_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status);
	cfg->escan_info.run = brcmf_run_escan;
	err = brcmf_करो_escan(अगरp, request);
	अगर (err) अणु
		clear_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status);
		वापस err;
	पूर्ण
	cfg->पूर्णांक_escan_map = fwmap;
	वापस 0;
पूर्ण

अटल काष्ठा brcmf_pno_net_info_le *
brcmf_get_netinfo_array(काष्ठा brcmf_pno_scanresults_le *pfn_v1)
अणु
	काष्ठा brcmf_pno_scanresults_v2_le *pfn_v2;
	काष्ठा brcmf_pno_net_info_le *netinfo;

	चयन (pfn_v1->version) अणु
	शेष:
		WARN_ON(1);
		fallthrough;
	हाल cpu_to_le32(1):
		netinfo = (काष्ठा brcmf_pno_net_info_le *)(pfn_v1 + 1);
		अवरोध;
	हाल cpu_to_le32(2):
		pfn_v2 = (काष्ठा brcmf_pno_scanresults_v2_le *)pfn_v1;
		netinfo = (काष्ठा brcmf_pno_net_info_le *)(pfn_v2 + 1);
		अवरोध;
	पूर्ण

	वापस netinfo;
पूर्ण

/* PFN result करोesn't have all the info which are required by the supplicant
 * (For e.g IEs) Do a target Escan so that sched scan results are reported
 * via wl_inक्रमm_single_bss in the required क्रमmat. Escan करोes require the
 * scan request in the क्रमm of cfg80211_scan_request. For समयbeing, create
 * cfg80211_scan_request one out of the received PNO event.
 */
अटल s32
brcmf_notअगरy_sched_scan_results(काष्ठा brcmf_अगर *अगरp,
				स्थिर काष्ठा brcmf_event_msg *e, व्योम *data)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_cfg80211_info *cfg = drvr->config;
	काष्ठा brcmf_pno_net_info_le *netinfo, *netinfo_start;
	काष्ठा cfg80211_scan_request *request = शून्य;
	काष्ठा wiphy *wiphy = cfg_to_wiphy(cfg);
	पूर्णांक i, err = 0;
	काष्ठा brcmf_pno_scanresults_le *pfn_result;
	u32 bucket_map;
	u32 result_count;
	u32 status;
	u32 datalen;

	brcmf_dbg(SCAN, "Enter\n");

	अगर (e->datalen < (माप(*pfn_result) + माप(*netinfo))) अणु
		brcmf_dbg(SCAN, "Event data to small. Ignore\n");
		वापस 0;
	पूर्ण

	अगर (e->event_code == BRCMF_E_PFN_NET_LOST) अणु
		brcmf_dbg(SCAN, "PFN NET LOST event. Do Nothing\n");
		वापस 0;
	पूर्ण

	pfn_result = (काष्ठा brcmf_pno_scanresults_le *)data;
	result_count = le32_to_cpu(pfn_result->count);
	status = le32_to_cpu(pfn_result->status);

	/* PFN event is limited to fit 512 bytes so we may get
	 * multiple NET_FOUND events. For now place a warning here.
	 */
	WARN_ON(status != BRCMF_PNO_SCAN_COMPLETE);
	brcmf_dbg(SCAN, "PFN NET FOUND event. count: %d\n", result_count);
	अगर (!result_count) अणु
		bphy_err(drvr, "FALSE PNO Event. (pfn_count == 0)\n");
		जाओ out_err;
	पूर्ण

	netinfo_start = brcmf_get_netinfo_array(pfn_result);
	datalen = e->datalen - ((व्योम *)netinfo_start - (व्योम *)pfn_result);
	अगर (datalen < result_count * माप(*netinfo)) अणु
		bphy_err(drvr, "insufficient event data\n");
		जाओ out_err;
	पूर्ण

	request = brcmf_alloc_पूर्णांकernal_escan_request(wiphy,
						     result_count);
	अगर (!request) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण

	bucket_map = 0;
	क्रम (i = 0; i < result_count; i++) अणु
		netinfo = &netinfo_start[i];

		अगर (netinfo->SSID_len > IEEE80211_MAX_SSID_LEN)
			netinfo->SSID_len = IEEE80211_MAX_SSID_LEN;
		brcmf_dbg(SCAN, "SSID:%.32s Channel:%d\n",
			  netinfo->SSID, netinfo->channel);
		bucket_map |= brcmf_pno_get_bucket_map(cfg->pno, netinfo);
		err = brcmf_पूर्णांकernal_escan_add_info(request,
						    netinfo->SSID,
						    netinfo->SSID_len,
						    netinfo->channel);
		अगर (err)
			जाओ out_err;
	पूर्ण

	अगर (!bucket_map)
		जाओ मुक्त_req;

	err = brcmf_start_पूर्णांकernal_escan(अगरp, bucket_map, request);
	अगर (!err)
		जाओ मुक्त_req;

out_err:
	cfg80211_sched_scan_stopped(wiphy, 0);
मुक्त_req:
	kमुक्त(request);
	वापस err;
पूर्ण

अटल पूर्णांक
brcmf_cfg80211_sched_scan_start(काष्ठा wiphy *wiphy,
				काष्ठा net_device *ndev,
				काष्ठा cfg80211_sched_scan_request *req)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = cfg->pub;

	brcmf_dbg(SCAN, "Enter: n_match_sets=%d n_ssids=%d\n",
		  req->n_match_sets, req->n_ssids);

	अगर (test_bit(BRCMF_SCAN_STATUS_SUPPRESS, &cfg->scan_status)) अणु
		bphy_err(drvr, "Scanning suppressed: status=%lu\n",
			 cfg->scan_status);
		वापस -EAGAIN;
	पूर्ण

	अगर (req->n_match_sets <= 0) अणु
		brcmf_dbg(SCAN, "invalid number of matchsets specified: %d\n",
			  req->n_match_sets);
		वापस -EINVAL;
	पूर्ण

	वापस brcmf_pno_start_sched_scan(अगरp, req);
पूर्ण

अटल पूर्णांक brcmf_cfg80211_sched_scan_stop(काष्ठा wiphy *wiphy,
					  काष्ठा net_device *ndev, u64 reqid)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);

	brcmf_dbg(SCAN, "enter\n");
	brcmf_pno_stop_sched_scan(अगरp, reqid);
	अगर (cfg->पूर्णांक_escan_map)
		brcmf_notअगरy_escan_complete(cfg, अगरp, true, true);
	वापस 0;
पूर्ण

अटल __always_अंतरभूत व्योम brcmf_delay(u32 ms)
अणु
	अगर (ms < 1000 / HZ) अणु
		cond_resched();
		mdelay(ms);
	पूर्ण अन्यथा अणु
		msleep(ms);
	पूर्ण
पूर्ण

अटल s32 brcmf_config_wowl_pattern(काष्ठा brcmf_अगर *अगरp, u8 cmd[4],
				     u8 *pattern, u32 patternsize, u8 *mask,
				     u32 packet_offset)
अणु
	काष्ठा brcmf_fil_wowl_pattern_le *filter;
	u32 masksize;
	u32 patternoffset;
	u8 *buf;
	u32 bufsize;
	s32 ret;

	masksize = (patternsize + 7) / 8;
	patternoffset = माप(*filter) - माप(filter->cmd) + masksize;

	bufsize = माप(*filter) + patternsize + masksize;
	buf = kzalloc(bufsize, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	filter = (काष्ठा brcmf_fil_wowl_pattern_le *)buf;

	स_नकल(filter->cmd, cmd, 4);
	filter->masksize = cpu_to_le32(masksize);
	filter->offset = cpu_to_le32(packet_offset);
	filter->patternoffset = cpu_to_le32(patternoffset);
	filter->patternsize = cpu_to_le32(patternsize);
	filter->type = cpu_to_le32(BRCMF_WOWL_PATTERN_TYPE_BITMAP);

	अगर ((mask) && (masksize))
		स_नकल(buf + माप(*filter), mask, masksize);
	अगर ((pattern) && (patternsize))
		स_नकल(buf + माप(*filter) + masksize, pattern, patternsize);

	ret = brcmf_fil_iovar_data_set(अगरp, "wowl_pattern", buf, bufsize);

	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल s32
brcmf_wowl_nd_results(काष्ठा brcmf_अगर *अगरp, स्थिर काष्ठा brcmf_event_msg *e,
		      व्योम *data)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_cfg80211_info *cfg = drvr->config;
	काष्ठा brcmf_pno_scanresults_le *pfn_result;
	काष्ठा brcmf_pno_net_info_le *netinfo;

	brcmf_dbg(SCAN, "Enter\n");

	अगर (e->datalen < (माप(*pfn_result) + माप(*netinfo))) अणु
		brcmf_dbg(SCAN, "Event data to small. Ignore\n");
		वापस 0;
	पूर्ण

	pfn_result = (काष्ठा brcmf_pno_scanresults_le *)data;

	अगर (e->event_code == BRCMF_E_PFN_NET_LOST) अणु
		brcmf_dbg(SCAN, "PFN NET LOST event. Ignore\n");
		वापस 0;
	पूर्ण

	अगर (le32_to_cpu(pfn_result->count) < 1) अणु
		bphy_err(drvr, "Invalid result count, expected 1 (%d)\n",
			 le32_to_cpu(pfn_result->count));
		वापस -EINVAL;
	पूर्ण

	netinfo = brcmf_get_netinfo_array(pfn_result);
	अगर (netinfo->SSID_len > IEEE80211_MAX_SSID_LEN)
		netinfo->SSID_len = IEEE80211_MAX_SSID_LEN;
	स_नकल(cfg->wowl.nd->ssid.ssid, netinfo->SSID, netinfo->SSID_len);
	cfg->wowl.nd->ssid.ssid_len = netinfo->SSID_len;
	cfg->wowl.nd->n_channels = 1;
	cfg->wowl.nd->channels[0] =
		ieee80211_channel_to_frequency(netinfo->channel,
			netinfo->channel <= CH_MAX_2G_CHANNEL ?
					NL80211_BAND_2GHZ : NL80211_BAND_5GHZ);
	cfg->wowl.nd_info->n_matches = 1;
	cfg->wowl.nd_info->matches[0] = cfg->wowl.nd;

	/* Inक्रमm (the resume task) that the net detect inक्रमmation was recvd */
	cfg->wowl.nd_data_completed = true;
	wake_up(&cfg->wowl.nd_data_रुको);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल व्योम brcmf_report_wowl_wakeind(काष्ठा wiphy *wiphy, काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_wowl_wakeind_le wake_ind_le;
	काष्ठा cfg80211_wowlan_wakeup wakeup_data;
	काष्ठा cfg80211_wowlan_wakeup *wakeup;
	u32 wakeind;
	s32 err;
	पूर्णांक समयout;

	err = brcmf_fil_iovar_data_get(अगरp, "wowl_wakeind", &wake_ind_le,
				       माप(wake_ind_le));
	अगर (err) अणु
		bphy_err(drvr, "Get wowl_wakeind failed, err = %d\n", err);
		वापस;
	पूर्ण

	wakeind = le32_to_cpu(wake_ind_le.ucode_wakeind);
	अगर (wakeind & (BRCMF_WOWL_MAGIC | BRCMF_WOWL_DIS | BRCMF_WOWL_BCN |
		       BRCMF_WOWL_RETR | BRCMF_WOWL_NET |
		       BRCMF_WOWL_PFN_FOUND)) अणु
		wakeup = &wakeup_data;
		स_रखो(&wakeup_data, 0, माप(wakeup_data));
		wakeup_data.pattern_idx = -1;

		अगर (wakeind & BRCMF_WOWL_MAGIC) अणु
			brcmf_dbg(INFO, "WOWL Wake indicator: BRCMF_WOWL_MAGIC\n");
			wakeup_data.magic_pkt = true;
		पूर्ण
		अगर (wakeind & BRCMF_WOWL_DIS) अणु
			brcmf_dbg(INFO, "WOWL Wake indicator: BRCMF_WOWL_DIS\n");
			wakeup_data.disconnect = true;
		पूर्ण
		अगर (wakeind & BRCMF_WOWL_BCN) अणु
			brcmf_dbg(INFO, "WOWL Wake indicator: BRCMF_WOWL_BCN\n");
			wakeup_data.disconnect = true;
		पूर्ण
		अगर (wakeind & BRCMF_WOWL_RETR) अणु
			brcmf_dbg(INFO, "WOWL Wake indicator: BRCMF_WOWL_RETR\n");
			wakeup_data.disconnect = true;
		पूर्ण
		अगर (wakeind & BRCMF_WOWL_NET) अणु
			brcmf_dbg(INFO, "WOWL Wake indicator: BRCMF_WOWL_NET\n");
			/* For now always map to pattern 0, no API to get
			 * correct inक्रमmation available at the moment.
			 */
			wakeup_data.pattern_idx = 0;
		पूर्ण
		अगर (wakeind & BRCMF_WOWL_PFN_FOUND) अणु
			brcmf_dbg(INFO, "WOWL Wake indicator: BRCMF_WOWL_PFN_FOUND\n");
			समयout = रुको_event_समयout(cfg->wowl.nd_data_रुको,
				cfg->wowl.nd_data_completed,
				BRCMF_ND_INFO_TIMEOUT);
			अगर (!समयout)
				bphy_err(drvr, "No result for wowl net detect\n");
			अन्यथा
				wakeup_data.net_detect = cfg->wowl.nd_info;
		पूर्ण
		अगर (wakeind & BRCMF_WOWL_GTK_FAILURE) अणु
			brcmf_dbg(INFO, "WOWL Wake indicator: BRCMF_WOWL_GTK_FAILURE\n");
			wakeup_data.gtk_rekey_failure = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		wakeup = शून्य;
	पूर्ण
	cfg80211_report_wowlan_wakeup(&अगरp->vअगर->wdev, wakeup, GFP_KERNEL);
पूर्ण

#अन्यथा

अटल व्योम brcmf_report_wowl_wakeind(काष्ठा wiphy *wiphy, काष्ठा brcmf_अगर *अगरp)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

अटल s32 brcmf_cfg80211_resume(काष्ठा wiphy *wiphy)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा net_device *ndev = cfg_to_ndev(cfg);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);

	brcmf_dbg(TRACE, "Enter\n");

	अगर (cfg->wowl.active) अणु
		brcmf_report_wowl_wakeind(wiphy, अगरp);
		brcmf_fil_iovar_पूर्णांक_set(अगरp, "wowl_clear", 0);
		brcmf_config_wowl_pattern(अगरp, "clr", शून्य, 0, शून्य, 0);
		अगर (!brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_WOWL_ARP_ND))
			brcmf_configure_arp_nd_offload(अगरp, true);
		brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_PM,
				      cfg->wowl.pre_pmmode);
		cfg->wowl.active = false;
		अगर (cfg->wowl.nd_enabled) अणु
			brcmf_cfg80211_sched_scan_stop(cfg->wiphy, अगरp->ndev, 0);
			brcmf_fweh_unरेजिस्टर(cfg->pub, BRCMF_E_PFN_NET_FOUND);
			brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_PFN_NET_FOUND,
					    brcmf_notअगरy_sched_scan_results);
			cfg->wowl.nd_enabled = false;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम brcmf_configure_wowl(काष्ठा brcmf_cfg80211_info *cfg,
				 काष्ठा brcmf_अगर *अगरp,
				 काष्ठा cfg80211_wowlan *wowl)
अणु
	u32 wowl_config;
	काष्ठा brcmf_wowl_wakeind_le wowl_wakeind;
	u32 i;

	brcmf_dbg(TRACE, "Suspend, wowl config.\n");

	अगर (!brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_WOWL_ARP_ND))
		brcmf_configure_arp_nd_offload(अगरp, false);
	brcmf_fil_cmd_पूर्णांक_get(अगरp, BRCMF_C_GET_PM, &cfg->wowl.pre_pmmode);
	brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_PM, PM_MAX);

	wowl_config = 0;
	अगर (wowl->disconnect)
		wowl_config = BRCMF_WOWL_DIS | BRCMF_WOWL_BCN | BRCMF_WOWL_RETR;
	अगर (wowl->magic_pkt)
		wowl_config |= BRCMF_WOWL_MAGIC;
	अगर ((wowl->patterns) && (wowl->n_patterns)) अणु
		wowl_config |= BRCMF_WOWL_NET;
		क्रम (i = 0; i < wowl->n_patterns; i++) अणु
			brcmf_config_wowl_pattern(अगरp, "add",
				(u8 *)wowl->patterns[i].pattern,
				wowl->patterns[i].pattern_len,
				(u8 *)wowl->patterns[i].mask,
				wowl->patterns[i].pkt_offset);
		पूर्ण
	पूर्ण
	अगर (wowl->nd_config) अणु
		brcmf_cfg80211_sched_scan_start(cfg->wiphy, अगरp->ndev,
						wowl->nd_config);
		wowl_config |= BRCMF_WOWL_PFN_FOUND;

		cfg->wowl.nd_data_completed = false;
		cfg->wowl.nd_enabled = true;
		/* Now reroute the event क्रम PFN to the wowl function. */
		brcmf_fweh_unरेजिस्टर(cfg->pub, BRCMF_E_PFN_NET_FOUND);
		brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_PFN_NET_FOUND,
				    brcmf_wowl_nd_results);
	पूर्ण
	अगर (wowl->gtk_rekey_failure)
		wowl_config |= BRCMF_WOWL_GTK_FAILURE;
	अगर (!test_bit(BRCMF_VIF_STATUS_CONNECTED, &अगरp->vअगर->sme_state))
		wowl_config |= BRCMF_WOWL_UNASSOC;

	स_नकल(&wowl_wakeind, "clear", 6);
	brcmf_fil_iovar_data_set(अगरp, "wowl_wakeind", &wowl_wakeind,
				 माप(wowl_wakeind));
	brcmf_fil_iovar_पूर्णांक_set(अगरp, "wowl", wowl_config);
	brcmf_fil_iovar_पूर्णांक_set(अगरp, "wowl_activate", 1);
	brcmf_bus_wowl_config(cfg->pub->bus_अगर, true);
	cfg->wowl.active = true;
पूर्ण

अटल s32 brcmf_cfg80211_suspend(काष्ठा wiphy *wiphy,
				  काष्ठा cfg80211_wowlan *wowl)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा net_device *ndev = cfg_to_ndev(cfg);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_cfg80211_vअगर *vअगर;

	brcmf_dbg(TRACE, "Enter\n");

	/* अगर the primary net_device is not READY there is nothing
	 * we can करो but pray resume goes smoothly.
	 */
	अगर (!check_vअगर_up(अगरp->vअगर))
		जाओ निकास;

	/* Stop scheduled scan */
	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_PNO))
		brcmf_cfg80211_sched_scan_stop(wiphy, ndev, 0);

	/* end any scanning */
	अगर (test_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status))
		brcmf_पात_scanning(cfg);

	अगर (wowl == शून्य) अणु
		brcmf_bus_wowl_config(cfg->pub->bus_अगर, false);
		list_क्रम_each_entry(vअगर, &cfg->vअगर_list, list) अणु
			अगर (!test_bit(BRCMF_VIF_STATUS_READY, &vअगर->sme_state))
				जारी;
			/* While going to suspend अगर associated with AP
			 * disassociate from AP to save घातer जबतक प्रणाली is
			 * in suspended state
			 */
			brcmf_link_करोwn(vअगर, WLAN_REASON_UNSPECIFIED, true);
			/* Make sure WPA_Supplicant receives all the event
			 * generated due to DISASSOC call to the fw to keep
			 * the state fw and WPA_Supplicant state consistent
			 */
			brcmf_delay(500);
		पूर्ण
		/* Configure MPC */
		brcmf_set_mpc(अगरp, 1);

	पूर्ण अन्यथा अणु
		/* Configure WOWL paramaters */
		brcmf_configure_wowl(cfg, अगरp, wowl);
	पूर्ण

निकास:
	brcmf_dbg(TRACE, "Exit\n");
	/* clear any scanning activity */
	cfg->scan_status = 0;
	वापस 0;
पूर्ण

अटल __used s32
brcmf_update_pmklist(काष्ठा brcmf_cfg80211_info *cfg, काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pmk_list_le *pmk_list;
	पूर्णांक i;
	u32 npmk;
	s32 err;

	pmk_list = &cfg->pmk_list;
	npmk = le32_to_cpu(pmk_list->npmk);

	brcmf_dbg(CONN, "No of elements %d\n", npmk);
	क्रम (i = 0; i < npmk; i++)
		brcmf_dbg(CONN, "PMK[%d]: %pM\n", i, &pmk_list->pmk[i].bssid);

	err = brcmf_fil_iovar_data_set(अगरp, "pmkid_info", pmk_list,
				       माप(*pmk_list));

	वापस err;
पूर्ण

अटल s32
brcmf_cfg80211_set_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
			 काष्ठा cfg80211_pmksa *pmksa)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pmksa *pmk = &cfg->pmk_list.pmk[0];
	काष्ठा brcmf_pub *drvr = cfg->pub;
	s32 err;
	u32 npmk, i;

	brcmf_dbg(TRACE, "Enter\n");
	अगर (!check_vअगर_up(अगरp->vअगर))
		वापस -EIO;

	npmk = le32_to_cpu(cfg->pmk_list.npmk);
	क्रम (i = 0; i < npmk; i++)
		अगर (!स_भेद(pmksa->bssid, pmk[i].bssid, ETH_ALEN))
			अवरोध;
	अगर (i < BRCMF_MAXPMKID) अणु
		स_नकल(pmk[i].bssid, pmksa->bssid, ETH_ALEN);
		स_नकल(pmk[i].pmkid, pmksa->pmkid, WLAN_PMKID_LEN);
		अगर (i == npmk) अणु
			npmk++;
			cfg->pmk_list.npmk = cpu_to_le32(npmk);
		पूर्ण
	पूर्ण अन्यथा अणु
		bphy_err(drvr, "Too many PMKSA entries cached %d\n", npmk);
		वापस -EINVAL;
	पूर्ण

	brcmf_dbg(CONN, "set_pmksa - PMK bssid: %pM =\n", pmk[npmk].bssid);
	brcmf_dbg(CONN, "%*ph\n", WLAN_PMKID_LEN, pmk[npmk].pmkid);

	err = brcmf_update_pmklist(cfg, अगरp);

	brcmf_dbg(TRACE, "Exit\n");
	वापस err;
पूर्ण

अटल s32
brcmf_cfg80211_del_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
			 काष्ठा cfg80211_pmksa *pmksa)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pmksa *pmk = &cfg->pmk_list.pmk[0];
	काष्ठा brcmf_pub *drvr = cfg->pub;
	s32 err;
	u32 npmk, i;

	brcmf_dbg(TRACE, "Enter\n");
	अगर (!check_vअगर_up(अगरp->vअगर))
		वापस -EIO;

	brcmf_dbg(CONN, "del_pmksa - PMK bssid = %pM\n", pmksa->bssid);

	npmk = le32_to_cpu(cfg->pmk_list.npmk);
	क्रम (i = 0; i < npmk; i++)
		अगर (!स_भेद(pmksa->bssid, pmk[i].bssid, ETH_ALEN))
			अवरोध;

	अगर ((npmk > 0) && (i < npmk)) अणु
		क्रम (; i < (npmk - 1); i++) अणु
			स_नकल(&pmk[i].bssid, &pmk[i + 1].bssid, ETH_ALEN);
			स_नकल(&pmk[i].pmkid, &pmk[i + 1].pmkid,
			       WLAN_PMKID_LEN);
		पूर्ण
		स_रखो(&pmk[i], 0, माप(*pmk));
		cfg->pmk_list.npmk = cpu_to_le32(npmk - 1);
	पूर्ण अन्यथा अणु
		bphy_err(drvr, "Cache entry not found\n");
		वापस -EINVAL;
	पूर्ण

	err = brcmf_update_pmklist(cfg, अगरp);

	brcmf_dbg(TRACE, "Exit\n");
	वापस err;

पूर्ण

अटल s32
brcmf_cfg80211_flush_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	s32 err;

	brcmf_dbg(TRACE, "Enter\n");
	अगर (!check_vअगर_up(अगरp->vअगर))
		वापस -EIO;

	स_रखो(&cfg->pmk_list, 0, माप(cfg->pmk_list));
	err = brcmf_update_pmklist(cfg, अगरp);

	brcmf_dbg(TRACE, "Exit\n");
	वापस err;

पूर्ण

अटल s32 brcmf_configure_खोलोsecurity(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 err;
	s32 wpa_val;

	/* set auth */
	err = brcmf_fil_bsscfg_पूर्णांक_set(अगरp, "auth", 0);
	अगर (err < 0) अणु
		bphy_err(drvr, "auth error %d\n", err);
		वापस err;
	पूर्ण
	/* set wsec */
	err = brcmf_fil_bsscfg_पूर्णांक_set(अगरp, "wsec", 0);
	अगर (err < 0) अणु
		bphy_err(drvr, "wsec error %d\n", err);
		वापस err;
	पूर्ण
	/* set upper-layer auth */
	अगर (brcmf_is_ibssmode(अगरp->vअगर))
		wpa_val = WPA_AUTH_NONE;
	अन्यथा
		wpa_val = WPA_AUTH_DISABLED;
	err = brcmf_fil_bsscfg_पूर्णांक_set(अगरp, "wpa_auth", wpa_val);
	अगर (err < 0) अणु
		bphy_err(drvr, "wpa_auth error %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool brcmf_valid_wpa_oui(u8 *oui, bool is_rsn_ie)
अणु
	अगर (is_rsn_ie)
		वापस (स_भेद(oui, RSN_OUI, TLV_OUI_LEN) == 0);

	वापस (स_भेद(oui, WPA_OUI, TLV_OUI_LEN) == 0);
पूर्ण

अटल s32
brcmf_configure_wpaie(काष्ठा brcmf_अगर *अगरp,
		      स्थिर काष्ठा brcmf_vs_tlv *wpa_ie,
		      bool is_rsn_ie)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	u32 auth = 0; /* d11 खोलो authentication */
	u16 count;
	s32 err = 0;
	s32 len;
	u32 i;
	u32 wsec;
	u32 pval = 0;
	u32 gval = 0;
	u32 wpa_auth = 0;
	u32 offset;
	u8 *data;
	u16 rsn_cap;
	u32 wme_bss_disable;
	u32 mfp;

	brcmf_dbg(TRACE, "Enter\n");
	अगर (wpa_ie == शून्य)
		जाओ निकास;

	len = wpa_ie->len + TLV_HDR_LEN;
	data = (u8 *)wpa_ie;
	offset = TLV_HDR_LEN;
	अगर (!is_rsn_ie)
		offset += VS_IE_FIXED_HDR_LEN;
	अन्यथा
		offset += WPA_IE_VERSION_LEN;

	/* check क्रम multicast cipher suite */
	अगर (offset + WPA_IE_MIN_OUI_LEN > len) अणु
		err = -EINVAL;
		bphy_err(drvr, "no multicast cipher suite\n");
		जाओ निकास;
	पूर्ण

	अगर (!brcmf_valid_wpa_oui(&data[offset], is_rsn_ie)) अणु
		err = -EINVAL;
		bphy_err(drvr, "ivalid OUI\n");
		जाओ निकास;
	पूर्ण
	offset += TLV_OUI_LEN;

	/* pick up multicast cipher */
	चयन (data[offset]) अणु
	हाल WPA_CIPHER_NONE:
		gval = 0;
		अवरोध;
	हाल WPA_CIPHER_WEP_40:
	हाल WPA_CIPHER_WEP_104:
		gval = WEP_ENABLED;
		अवरोध;
	हाल WPA_CIPHER_TKIP:
		gval = TKIP_ENABLED;
		अवरोध;
	हाल WPA_CIPHER_AES_CCM:
		gval = AES_ENABLED;
		अवरोध;
	शेष:
		err = -EINVAL;
		bphy_err(drvr, "Invalid multi cast cipher info\n");
		जाओ निकास;
	पूर्ण

	offset++;
	/* walk thru unicast cipher list and pick up what we recognize */
	count = data[offset] + (data[offset + 1] << 8);
	offset += WPA_IE_SUITE_COUNT_LEN;
	/* Check क्रम unicast suite(s) */
	अगर (offset + (WPA_IE_MIN_OUI_LEN * count) > len) अणु
		err = -EINVAL;
		bphy_err(drvr, "no unicast cipher suite\n");
		जाओ निकास;
	पूर्ण
	क्रम (i = 0; i < count; i++) अणु
		अगर (!brcmf_valid_wpa_oui(&data[offset], is_rsn_ie)) अणु
			err = -EINVAL;
			bphy_err(drvr, "ivalid OUI\n");
			जाओ निकास;
		पूर्ण
		offset += TLV_OUI_LEN;
		चयन (data[offset]) अणु
		हाल WPA_CIPHER_NONE:
			अवरोध;
		हाल WPA_CIPHER_WEP_40:
		हाल WPA_CIPHER_WEP_104:
			pval |= WEP_ENABLED;
			अवरोध;
		हाल WPA_CIPHER_TKIP:
			pval |= TKIP_ENABLED;
			अवरोध;
		हाल WPA_CIPHER_AES_CCM:
			pval |= AES_ENABLED;
			अवरोध;
		शेष:
			bphy_err(drvr, "Invalid unicast security info\n");
		पूर्ण
		offset++;
	पूर्ण
	/* walk thru auth management suite list and pick up what we recognize */
	count = data[offset] + (data[offset + 1] << 8);
	offset += WPA_IE_SUITE_COUNT_LEN;
	/* Check क्रम auth key management suite(s) */
	अगर (offset + (WPA_IE_MIN_OUI_LEN * count) > len) अणु
		err = -EINVAL;
		bphy_err(drvr, "no auth key mgmt suite\n");
		जाओ निकास;
	पूर्ण
	क्रम (i = 0; i < count; i++) अणु
		अगर (!brcmf_valid_wpa_oui(&data[offset], is_rsn_ie)) अणु
			err = -EINVAL;
			bphy_err(drvr, "ivalid OUI\n");
			जाओ निकास;
		पूर्ण
		offset += TLV_OUI_LEN;
		चयन (data[offset]) अणु
		हाल RSN_AKM_NONE:
			brcmf_dbg(TRACE, "RSN_AKM_NONE\n");
			wpa_auth |= WPA_AUTH_NONE;
			अवरोध;
		हाल RSN_AKM_UNSPECIFIED:
			brcmf_dbg(TRACE, "RSN_AKM_UNSPECIFIED\n");
			is_rsn_ie ? (wpa_auth |= WPA2_AUTH_UNSPECIFIED) :
				    (wpa_auth |= WPA_AUTH_UNSPECIFIED);
			अवरोध;
		हाल RSN_AKM_PSK:
			brcmf_dbg(TRACE, "RSN_AKM_PSK\n");
			is_rsn_ie ? (wpa_auth |= WPA2_AUTH_PSK) :
				    (wpa_auth |= WPA_AUTH_PSK);
			अवरोध;
		हाल RSN_AKM_SHA256_PSK:
			brcmf_dbg(TRACE, "RSN_AKM_MFP_PSK\n");
			wpa_auth |= WPA2_AUTH_PSK_SHA256;
			अवरोध;
		हाल RSN_AKM_SHA256_1X:
			brcmf_dbg(TRACE, "RSN_AKM_MFP_1X\n");
			wpa_auth |= WPA2_AUTH_1X_SHA256;
			अवरोध;
		हाल RSN_AKM_SAE:
			brcmf_dbg(TRACE, "RSN_AKM_SAE\n");
			wpa_auth |= WPA3_AUTH_SAE_PSK;
			अवरोध;
		शेष:
			bphy_err(drvr, "Invalid key mgmt info\n");
		पूर्ण
		offset++;
	पूर्ण

	mfp = BRCMF_MFP_NONE;
	अगर (is_rsn_ie) अणु
		wme_bss_disable = 1;
		अगर ((offset + RSN_CAP_LEN) <= len) अणु
			rsn_cap = data[offset] + (data[offset + 1] << 8);
			अगर (rsn_cap & RSN_CAP_PTK_REPLAY_CNTR_MASK)
				wme_bss_disable = 0;
			अगर (rsn_cap & RSN_CAP_MFPR_MASK) अणु
				brcmf_dbg(TRACE, "MFP Required\n");
				mfp = BRCMF_MFP_REQUIRED;
				/* Firmware only supports mfp required in
				 * combination with WPA2_AUTH_PSK_SHA256,
				 * WPA2_AUTH_1X_SHA256, or WPA3_AUTH_SAE_PSK.
				 */
				अगर (!(wpa_auth & (WPA2_AUTH_PSK_SHA256 |
						  WPA2_AUTH_1X_SHA256 |
						  WPA3_AUTH_SAE_PSK))) अणु
					err = -EINVAL;
					जाओ निकास;
				पूर्ण
				/* Firmware has requirement that WPA2_AUTH_PSK/
				 * WPA2_AUTH_UNSPECIFIED be set, अगर SHA256 OUI
				 * is to be included in the rsn ie.
				 */
				अगर (wpa_auth & WPA2_AUTH_PSK_SHA256)
					wpa_auth |= WPA2_AUTH_PSK;
				अन्यथा अगर (wpa_auth & WPA2_AUTH_1X_SHA256)
					wpa_auth |= WPA2_AUTH_UNSPECIFIED;
			पूर्ण अन्यथा अगर (rsn_cap & RSN_CAP_MFPC_MASK) अणु
				brcmf_dbg(TRACE, "MFP Capable\n");
				mfp = BRCMF_MFP_CAPABLE;
			पूर्ण
		पूर्ण
		offset += RSN_CAP_LEN;
		/* set wme_bss_disable to sync RSN Capabilities */
		err = brcmf_fil_bsscfg_पूर्णांक_set(अगरp, "wme_bss_disable",
					       wme_bss_disable);
		अगर (err < 0) अणु
			bphy_err(drvr, "wme_bss_disable error %d\n", err);
			जाओ निकास;
		पूर्ण

		/* Skip PMKID cnt as it is know to be 0 क्रम AP. */
		offset += RSN_PMKID_COUNT_LEN;

		/* See अगर there is BIP wpa suite left क्रम MFP */
		अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_MFP) &&
		    ((offset + WPA_IE_MIN_OUI_LEN) <= len)) अणु
			err = brcmf_fil_bsscfg_data_set(अगरp, "bip",
							&data[offset],
							WPA_IE_MIN_OUI_LEN);
			अगर (err < 0) अणु
				bphy_err(drvr, "bip error %d\n", err);
				जाओ निकास;
			पूर्ण
		पूर्ण
	पूर्ण
	/* FOR WPS , set SES_OW_ENABLED */
	wsec = (pval | gval | SES_OW_ENABLED);

	/* set auth */
	err = brcmf_fil_bsscfg_पूर्णांक_set(अगरp, "auth", auth);
	अगर (err < 0) अणु
		bphy_err(drvr, "auth error %d\n", err);
		जाओ निकास;
	पूर्ण
	/* set wsec */
	err = brcmf_fil_bsscfg_पूर्णांक_set(अगरp, "wsec", wsec);
	अगर (err < 0) अणु
		bphy_err(drvr, "wsec error %d\n", err);
		जाओ निकास;
	पूर्ण
	/* Configure MFP, this needs to go after wsec otherwise the wsec command
	 * will overग_लिखो the values set by MFP
	 */
	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_MFP)) अणु
		err = brcmf_fil_bsscfg_पूर्णांक_set(अगरp, "mfp", mfp);
		अगर (err < 0) अणु
			bphy_err(drvr, "mfp error %d\n", err);
			जाओ निकास;
		पूर्ण
	पूर्ण
	/* set upper-layer auth */
	err = brcmf_fil_bsscfg_पूर्णांक_set(अगरp, "wpa_auth", wpa_auth);
	अगर (err < 0) अणु
		bphy_err(drvr, "wpa_auth error %d\n", err);
		जाओ निकास;
	पूर्ण

निकास:
	वापस err;
पूर्ण

अटल s32
brcmf_parse_vndr_ies(स्थिर u8 *vndr_ie_buf, u32 vndr_ie_len,
		     काष्ठा parsed_vndr_ies *vndr_ies)
अणु
	काष्ठा brcmf_vs_tlv *vndrie;
	काष्ठा brcmf_tlv *ie;
	काष्ठा parsed_vndr_ie_info *parsed_info;
	s32 reमुख्यing_len;

	reमुख्यing_len = (s32)vndr_ie_len;
	स_रखो(vndr_ies, 0, माप(*vndr_ies));

	ie = (काष्ठा brcmf_tlv *)vndr_ie_buf;
	जबतक (ie) अणु
		अगर (ie->id != WLAN_EID_VENDOR_SPECIFIC)
			जाओ next;
		vndrie = (काष्ठा brcmf_vs_tlv *)ie;
		/* len should be bigger than OUI length + one */
		अगर (vndrie->len < (VS_IE_FIXED_HDR_LEN - TLV_HDR_LEN + 1)) अणु
			brcmf_err("invalid vndr ie. length is too small %d\n",
				  vndrie->len);
			जाओ next;
		पूर्ण
		/* अगर wpa or wme ie, करो not add ie */
		अगर (!स_भेद(vndrie->oui, (u8 *)WPA_OUI, TLV_OUI_LEN) &&
		    ((vndrie->oui_type == WPA_OUI_TYPE) ||
		    (vndrie->oui_type == WME_OUI_TYPE))) अणु
			brcmf_dbg(TRACE, "Found WPA/WME oui. Do not add it\n");
			जाओ next;
		पूर्ण

		parsed_info = &vndr_ies->ie_info[vndr_ies->count];

		/* save vndr ie inक्रमmation */
		parsed_info->ie_ptr = (अक्षर *)vndrie;
		parsed_info->ie_len = vndrie->len + TLV_HDR_LEN;
		स_नकल(&parsed_info->vndrie, vndrie, माप(*vndrie));

		vndr_ies->count++;

		brcmf_dbg(TRACE, "** OUI %3ph, type 0x%02x\n",
			  parsed_info->vndrie.oui,
			  parsed_info->vndrie.oui_type);

		अगर (vndr_ies->count >= VNDR_IE_PARSE_LIMIT)
			अवरोध;
next:
		reमुख्यing_len -= (ie->len + TLV_HDR_LEN);
		अगर (reमुख्यing_len <= TLV_HDR_LEN)
			ie = शून्य;
		अन्यथा
			ie = (काष्ठा brcmf_tlv *)(((u8 *)ie) + ie->len +
				TLV_HDR_LEN);
	पूर्ण
	वापस 0;
पूर्ण

अटल u32
brcmf_vndr_ie(u8 *iebuf, s32 pktflag, u8 *ie_ptr, u32 ie_len, s8 *add_del_cmd)
अणु
	strscpy(iebuf, add_del_cmd, VNDR_IE_CMD_LEN);

	put_unaligned_le32(1, &iebuf[VNDR_IE_COUNT_OFFSET]);

	put_unaligned_le32(pktflag, &iebuf[VNDR_IE_PKTFLAG_OFFSET]);

	स_नकल(&iebuf[VNDR_IE_VSIE_OFFSET], ie_ptr, ie_len);

	वापस ie_len + VNDR_IE_HDR_SIZE;
पूर्ण

s32 brcmf_vअगर_set_mgmt_ie(काष्ठा brcmf_cfg80211_vअगर *vअगर, s32 pktflag,
			  स्थिर u8 *vndr_ie_buf, u32 vndr_ie_len)
अणु
	काष्ठा brcmf_pub *drvr;
	काष्ठा brcmf_अगर *अगरp;
	काष्ठा vअगर_saved_ie *saved_ie;
	s32 err = 0;
	u8  *iovar_ie_buf;
	u8  *curr_ie_buf;
	u8  *mgmt_ie_buf = शून्य;
	पूर्णांक mgmt_ie_buf_len;
	u32 *mgmt_ie_len;
	u32 del_add_ie_buf_len = 0;
	u32 total_ie_buf_len = 0;
	u32 parsed_ie_buf_len = 0;
	काष्ठा parsed_vndr_ies old_vndr_ies;
	काष्ठा parsed_vndr_ies new_vndr_ies;
	काष्ठा parsed_vndr_ie_info *vndrie_info;
	s32 i;
	u8 *ptr;
	पूर्णांक reमुख्यed_buf_len;

	अगर (!vअगर)
		वापस -ENODEV;
	अगरp = vअगर->अगरp;
	drvr = अगरp->drvr;
	saved_ie = &vअगर->saved_ie;

	brcmf_dbg(TRACE, "bsscfgidx %d, pktflag : 0x%02X\n", अगरp->bsscfgidx,
		  pktflag);
	iovar_ie_buf = kzalloc(WL_EXTRA_BUF_MAX, GFP_KERNEL);
	अगर (!iovar_ie_buf)
		वापस -ENOMEM;
	curr_ie_buf = iovar_ie_buf;
	चयन (pktflag) अणु
	हाल BRCMF_VNDR_IE_PRBREQ_FLAG:
		mgmt_ie_buf = saved_ie->probe_req_ie;
		mgmt_ie_len = &saved_ie->probe_req_ie_len;
		mgmt_ie_buf_len = माप(saved_ie->probe_req_ie);
		अवरोध;
	हाल BRCMF_VNDR_IE_PRBRSP_FLAG:
		mgmt_ie_buf = saved_ie->probe_res_ie;
		mgmt_ie_len = &saved_ie->probe_res_ie_len;
		mgmt_ie_buf_len = माप(saved_ie->probe_res_ie);
		अवरोध;
	हाल BRCMF_VNDR_IE_BEACON_FLAG:
		mgmt_ie_buf = saved_ie->beacon_ie;
		mgmt_ie_len = &saved_ie->beacon_ie_len;
		mgmt_ie_buf_len = माप(saved_ie->beacon_ie);
		अवरोध;
	हाल BRCMF_VNDR_IE_ASSOCREQ_FLAG:
		mgmt_ie_buf = saved_ie->assoc_req_ie;
		mgmt_ie_len = &saved_ie->assoc_req_ie_len;
		mgmt_ie_buf_len = माप(saved_ie->assoc_req_ie);
		अवरोध;
	हाल BRCMF_VNDR_IE_ASSOCRSP_FLAG:
		mgmt_ie_buf = saved_ie->assoc_res_ie;
		mgmt_ie_len = &saved_ie->assoc_res_ie_len;
		mgmt_ie_buf_len = माप(saved_ie->assoc_res_ie);
		अवरोध;
	शेष:
		err = -EPERM;
		bphy_err(drvr, "not suitable type\n");
		जाओ निकास;
	पूर्ण

	अगर (vndr_ie_len > mgmt_ie_buf_len) अणु
		err = -ENOMEM;
		bphy_err(drvr, "extra IE size too big\n");
		जाओ निकास;
	पूर्ण

	/* parse and save new vndr_ie in curr_ie_buff beक्रमe comparing it */
	अगर (vndr_ie_buf && vndr_ie_len && curr_ie_buf) अणु
		ptr = curr_ie_buf;
		brcmf_parse_vndr_ies(vndr_ie_buf, vndr_ie_len, &new_vndr_ies);
		क्रम (i = 0; i < new_vndr_ies.count; i++) अणु
			vndrie_info = &new_vndr_ies.ie_info[i];
			स_नकल(ptr + parsed_ie_buf_len, vndrie_info->ie_ptr,
			       vndrie_info->ie_len);
			parsed_ie_buf_len += vndrie_info->ie_len;
		पूर्ण
	पूर्ण

	अगर (mgmt_ie_buf && *mgmt_ie_len) अणु
		अगर (parsed_ie_buf_len && (parsed_ie_buf_len == *mgmt_ie_len) &&
		    (स_भेद(mgmt_ie_buf, curr_ie_buf,
			    parsed_ie_buf_len) == 0)) अणु
			brcmf_dbg(TRACE, "Previous mgmt IE equals to current IE\n");
			जाओ निकास;
		पूर्ण

		/* parse old vndr_ie */
		brcmf_parse_vndr_ies(mgmt_ie_buf, *mgmt_ie_len, &old_vndr_ies);

		/* make a command to delete old ie */
		क्रम (i = 0; i < old_vndr_ies.count; i++) अणु
			vndrie_info = &old_vndr_ies.ie_info[i];

			brcmf_dbg(TRACE, "DEL ID : %d, Len: %d , OUI:%3ph\n",
				  vndrie_info->vndrie.id,
				  vndrie_info->vndrie.len,
				  vndrie_info->vndrie.oui);

			del_add_ie_buf_len = brcmf_vndr_ie(curr_ie_buf, pktflag,
							   vndrie_info->ie_ptr,
							   vndrie_info->ie_len,
							   "del");
			curr_ie_buf += del_add_ie_buf_len;
			total_ie_buf_len += del_add_ie_buf_len;
		पूर्ण
	पूर्ण

	*mgmt_ie_len = 0;
	/* Add अगर there is any extra IE */
	अगर (mgmt_ie_buf && parsed_ie_buf_len) अणु
		ptr = mgmt_ie_buf;

		reमुख्यed_buf_len = mgmt_ie_buf_len;

		/* make a command to add new ie */
		क्रम (i = 0; i < new_vndr_ies.count; i++) अणु
			vndrie_info = &new_vndr_ies.ie_info[i];

			/* verअगरy reमुख्यed buf size beक्रमe copy data */
			अगर (reमुख्यed_buf_len < (vndrie_info->vndrie.len +
							VNDR_IE_VSIE_OFFSET)) अणु
				bphy_err(drvr, "no space in mgmt_ie_buf: len left %d",
					 reमुख्यed_buf_len);
				अवरोध;
			पूर्ण
			reमुख्यed_buf_len -= (vndrie_info->ie_len +
					     VNDR_IE_VSIE_OFFSET);

			brcmf_dbg(TRACE, "ADDED ID : %d, Len: %d, OUI:%3ph\n",
				  vndrie_info->vndrie.id,
				  vndrie_info->vndrie.len,
				  vndrie_info->vndrie.oui);

			del_add_ie_buf_len = brcmf_vndr_ie(curr_ie_buf, pktflag,
							   vndrie_info->ie_ptr,
							   vndrie_info->ie_len,
							   "add");

			/* save the parsed IE in wl काष्ठा */
			स_नकल(ptr + (*mgmt_ie_len), vndrie_info->ie_ptr,
			       vndrie_info->ie_len);
			*mgmt_ie_len += vndrie_info->ie_len;

			curr_ie_buf += del_add_ie_buf_len;
			total_ie_buf_len += del_add_ie_buf_len;
		पूर्ण
	पूर्ण
	अगर (total_ie_buf_len) अणु
		err  = brcmf_fil_bsscfg_data_set(अगरp, "vndr_ie", iovar_ie_buf,
						 total_ie_buf_len);
		अगर (err)
			bphy_err(drvr, "vndr ie set error : %d\n", err);
	पूर्ण

निकास:
	kमुक्त(iovar_ie_buf);
	वापस err;
पूर्ण

s32 brcmf_vअगर_clear_mgmt_ies(काष्ठा brcmf_cfg80211_vअगर *vअगर)
अणु
	s32 pktflags[] = अणु
		BRCMF_VNDR_IE_PRBREQ_FLAG,
		BRCMF_VNDR_IE_PRBRSP_FLAG,
		BRCMF_VNDR_IE_BEACON_FLAG
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pktflags); i++)
		brcmf_vअगर_set_mgmt_ie(vअगर, pktflags[i], शून्य, 0);

	स_रखो(&vअगर->saved_ie, 0, माप(vअगर->saved_ie));
	वापस 0;
पूर्ण

अटल s32
brcmf_config_ap_mgmt_ie(काष्ठा brcmf_cfg80211_vअगर *vअगर,
			काष्ठा cfg80211_beacon_data *beacon)
अणु
	काष्ठा brcmf_pub *drvr = vअगर->अगरp->drvr;
	s32 err;

	/* Set Beacon IEs to FW */
	err = brcmf_vअगर_set_mgmt_ie(vअगर, BRCMF_VNDR_IE_BEACON_FLAG,
				    beacon->tail, beacon->tail_len);
	अगर (err) अणु
		bphy_err(drvr, "Set Beacon IE Failed\n");
		वापस err;
	पूर्ण
	brcmf_dbg(TRACE, "Applied Vndr IEs for Beacon\n");

	/* Set Probe Response IEs to FW */
	err = brcmf_vअगर_set_mgmt_ie(vअगर, BRCMF_VNDR_IE_PRBRSP_FLAG,
				    beacon->proberesp_ies,
				    beacon->proberesp_ies_len);
	अगर (err)
		bphy_err(drvr, "Set Probe Resp IE Failed\n");
	अन्यथा
		brcmf_dbg(TRACE, "Applied Vndr IEs for Probe Resp\n");

	/* Set Assoc Response IEs to FW */
	err = brcmf_vअगर_set_mgmt_ie(vअगर, BRCMF_VNDR_IE_ASSOCRSP_FLAG,
				    beacon->assocresp_ies,
				    beacon->assocresp_ies_len);
	अगर (err)
		brcmf_err("Set Assoc Resp IE Failed\n");
	अन्यथा
		brcmf_dbg(TRACE, "Applied Vndr IEs for Assoc Resp\n");

	वापस err;
पूर्ण

अटल s32
brcmf_parse_configure_security(काष्ठा brcmf_अगर *अगरp,
			       काष्ठा cfg80211_ap_settings *settings,
			       क्रमागत nl80211_अगरtype dev_role)
अणु
	स्थिर काष्ठा brcmf_tlv *rsn_ie;
	स्थिर काष्ठा brcmf_vs_tlv *wpa_ie;
	s32 err = 0;

	/* find the RSN_IE */
	rsn_ie = brcmf_parse_tlvs((u8 *)settings->beacon.tail,
				  settings->beacon.tail_len, WLAN_EID_RSN);

	/* find the WPA_IE */
	wpa_ie = brcmf_find_wpaie((u8 *)settings->beacon.tail,
				  settings->beacon.tail_len);

	अगर (wpa_ie || rsn_ie) अणु
		brcmf_dbg(TRACE, "WPA(2) IE is found\n");
		अगर (wpa_ie) अणु
			/* WPA IE */
			err = brcmf_configure_wpaie(अगरp, wpa_ie, false);
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अणु
			काष्ठा brcmf_vs_tlv *पंचांगp_ie;

			पंचांगp_ie = (काष्ठा brcmf_vs_tlv *)rsn_ie;

			/* RSN IE */
			err = brcmf_configure_wpaie(अगरp, पंचांगp_ie, true);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		brcmf_dbg(TRACE, "No WPA(2) IEs found\n");
		brcmf_configure_खोलोsecurity(अगरp);
	पूर्ण

	वापस err;
पूर्ण

अटल s32
brcmf_cfg80211_start_ap(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
			काष्ठा cfg80211_ap_settings *settings)
अणु
	s32 ie_offset;
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_cfg80211_profile *profile = &अगरp->vअगर->profile;
	काष्ठा cfg80211_crypto_settings *crypto = &settings->crypto;
	स्थिर काष्ठा brcmf_tlv *ssid_ie;
	स्थिर काष्ठा brcmf_tlv *country_ie;
	काष्ठा brcmf_ssid_le ssid_le;
	s32 err = -EPERM;
	काष्ठा brcmf_join_params join_params;
	क्रमागत nl80211_अगरtype dev_role;
	काष्ठा brcmf_fil_bss_enable_le bss_enable;
	u16 chanspec = chandef_to_chanspec(&cfg->d11inf, &settings->chandef);
	bool mbss;
	पूर्णांक is_11d;
	bool supports_11d;

	brcmf_dbg(TRACE, "ctrlchn=%d, center=%d, bw=%d, beacon_interval=%d, dtim_period=%d,\n",
		  settings->chandef.chan->hw_value,
		  settings->chandef.center_freq1, settings->chandef.width,
		  settings->beacon_पूर्णांकerval, settings->dtim_period);
	brcmf_dbg(TRACE, "ssid=%s(%zu), auth_type=%d, inactivity_timeout=%d\n",
		  settings->ssid, settings->ssid_len, settings->auth_type,
		  settings->inactivity_समयout);
	dev_role = अगरp->vअगर->wdev.अगरtype;
	mbss = अगरp->vअगर->mbss;

	/* store current 11d setting */
	अगर (brcmf_fil_cmd_पूर्णांक_get(अगरp, BRCMF_C_GET_REGULATORY,
				  &अगरp->vअगर->is_11d)) अणु
		is_11d = supports_11d = false;
	पूर्ण अन्यथा अणु
		country_ie = brcmf_parse_tlvs((u8 *)settings->beacon.tail,
					      settings->beacon.tail_len,
					      WLAN_EID_COUNTRY);
		is_11d = country_ie ? 1 : 0;
		supports_11d = true;
	पूर्ण

	स_रखो(&ssid_le, 0, माप(ssid_le));
	अगर (settings->ssid == शून्य || settings->ssid_len == 0) अणु
		ie_offset = DOT11_MGMT_HDR_LEN + DOT11_BCN_PRB_FIXED_LEN;
		ssid_ie = brcmf_parse_tlvs(
				(u8 *)&settings->beacon.head[ie_offset],
				settings->beacon.head_len - ie_offset,
				WLAN_EID_SSID);
		अगर (!ssid_ie || ssid_ie->len > IEEE80211_MAX_SSID_LEN)
			वापस -EINVAL;

		स_नकल(ssid_le.SSID, ssid_ie->data, ssid_ie->len);
		ssid_le.SSID_len = cpu_to_le32(ssid_ie->len);
		brcmf_dbg(TRACE, "SSID is (%s) in Head\n", ssid_le.SSID);
	पूर्ण अन्यथा अणु
		स_नकल(ssid_le.SSID, settings->ssid, settings->ssid_len);
		ssid_le.SSID_len = cpu_to_le32((u32)settings->ssid_len);
	पूर्ण

	अगर (!mbss) अणु
		brcmf_set_mpc(अगरp, 0);
		brcmf_configure_arp_nd_offload(अगरp, false);
	पूर्ण

	/* Parameters shared by all radio पूर्णांकerfaces */
	अगर (!mbss) अणु
		अगर ((supports_11d) && (is_11d != अगरp->vअगर->is_11d)) अणु
			err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_REGULATORY,
						    is_11d);
			अगर (err < 0) अणु
				bphy_err(drvr, "Regulatory Set Error, %d\n",
					 err);
				जाओ निकास;
			पूर्ण
		पूर्ण
		अगर (settings->beacon_पूर्णांकerval) अणु
			err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_BCNPRD,
						    settings->beacon_पूर्णांकerval);
			अगर (err < 0) अणु
				bphy_err(drvr, "Beacon Interval Set Error, %d\n",
					 err);
				जाओ निकास;
			पूर्ण
		पूर्ण
		अगर (settings->dtim_period) अणु
			err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_DTIMPRD,
						    settings->dtim_period);
			अगर (err < 0) अणु
				bphy_err(drvr, "DTIM Interval Set Error, %d\n",
					 err);
				जाओ निकास;
			पूर्ण
		पूर्ण

		अगर ((dev_role == NL80211_IFTYPE_AP) &&
		    ((अगरp->अगरidx == 0) ||
		     (!brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_RSDB) &&
		      !brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_MCHAN)))) अणु
			err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_DOWN, 1);
			अगर (err < 0) अणु
				bphy_err(drvr, "BRCMF_C_DOWN error %d\n",
					 err);
				जाओ निकास;
			पूर्ण
			brcmf_fil_iovar_पूर्णांक_set(अगरp, "apsta", 0);
		पूर्ण

		err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_INFRA, 1);
		अगर (err < 0) अणु
			bphy_err(drvr, "SET INFRA error %d\n", err);
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अगर (WARN_ON(supports_11d && (is_11d != अगरp->vअगर->is_11d))) अणु
		/* Multiple-BSS should use same 11d configuration */
		err = -EINVAL;
		जाओ निकास;
	पूर्ण

	/* Interface specअगरic setup */
	अगर (dev_role == NL80211_IFTYPE_AP) अणु
		अगर ((brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_MBSS)) && (!mbss))
			brcmf_fil_iovar_पूर्णांक_set(अगरp, "mbss", 1);

		err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_AP, 1);
		अगर (err < 0) अणु
			bphy_err(drvr, "setting AP mode failed %d\n",
				 err);
			जाओ निकास;
		पूर्ण
		अगर (!mbss) अणु
			/* Firmware 10.x requires setting channel after enabling
			 * AP and beक्रमe bringing पूर्णांकerface up.
			 */
			err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "chanspec", chanspec);
			अगर (err < 0) अणु
				bphy_err(drvr, "Set Channel failed: chspec=%d, %d\n",
					 chanspec, err);
				जाओ निकास;
			पूर्ण
		पूर्ण
		err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_UP, 1);
		अगर (err < 0) अणु
			bphy_err(drvr, "BRCMF_C_UP error (%d)\n", err);
			जाओ निकास;
		पूर्ण

		अगर (crypto->psk) अणु
			brcmf_dbg(INFO, "using PSK offload\n");
			profile->use_fwauth |= BIT(BRCMF_PROखाता_FWAUTH_PSK);
			err = brcmf_set_pmk(अगरp, crypto->psk,
					    BRCMF_WSEC_MAX_PSK_LEN);
			अगर (err < 0)
				जाओ निकास;
		पूर्ण
		अगर (crypto->sae_pwd) अणु
			brcmf_dbg(INFO, "using SAE offload\n");
			profile->use_fwauth |= BIT(BRCMF_PROखाता_FWAUTH_SAE);
			err = brcmf_set_sae_password(अगरp, crypto->sae_pwd,
						     crypto->sae_pwd_len);
			अगर (err < 0)
				जाओ निकास;
		पूर्ण
		अगर (profile->use_fwauth == 0)
			profile->use_fwauth = BIT(BRCMF_PROखाता_FWAUTH_NONE);

		err = brcmf_parse_configure_security(अगरp, settings,
						     NL80211_IFTYPE_AP);
		अगर (err < 0) अणु
			bphy_err(drvr, "brcmf_parse_configure_security error\n");
			जाओ निकास;
		पूर्ण

		/* On DOWN the firmware हटाओs the WEP keys, reconfigure
		 * them अगर they were set.
		 */
		brcmf_cfg80211_reconfigure_wep(अगरp);

		स_रखो(&join_params, 0, माप(join_params));
		/* join parameters starts with ssid */
		स_नकल(&join_params.ssid_le, &ssid_le, माप(ssid_le));
		/* create softap */
		err = brcmf_fil_cmd_data_set(अगरp, BRCMF_C_SET_SSID,
					     &join_params, माप(join_params));
		अगर (err < 0) अणु
			bphy_err(drvr, "SET SSID error (%d)\n", err);
			जाओ निकास;
		पूर्ण

		err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "closednet",
					      settings->hidden_ssid);
		अगर (err) अणु
			bphy_err(drvr, "%s closednet error (%d)\n",
				 settings->hidden_ssid ?
				 "enabled" : "disabled",
				 err);
			जाओ निकास;
		पूर्ण

		brcmf_dbg(TRACE, "AP mode configuration complete\n");
	पूर्ण अन्यथा अगर (dev_role == NL80211_IFTYPE_P2P_GO) अणु
		err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "chanspec", chanspec);
		अगर (err < 0) अणु
			bphy_err(drvr, "Set Channel failed: chspec=%d, %d\n",
				 chanspec, err);
			जाओ निकास;
		पूर्ण

		err = brcmf_parse_configure_security(अगरp, settings,
						     NL80211_IFTYPE_P2P_GO);
		अगर (err < 0) अणु
			brcmf_err("brcmf_parse_configure_security error\n");
			जाओ निकास;
		पूर्ण

		err = brcmf_fil_bsscfg_data_set(अगरp, "ssid", &ssid_le,
						माप(ssid_le));
		अगर (err < 0) अणु
			bphy_err(drvr, "setting ssid failed %d\n", err);
			जाओ निकास;
		पूर्ण
		bss_enable.bsscfgidx = cpu_to_le32(अगरp->bsscfgidx);
		bss_enable.enable = cpu_to_le32(1);
		err = brcmf_fil_iovar_data_set(अगरp, "bss", &bss_enable,
					       माप(bss_enable));
		अगर (err < 0) अणु
			bphy_err(drvr, "bss_enable config failed %d\n", err);
			जाओ निकास;
		पूर्ण

		brcmf_dbg(TRACE, "GO mode configuration complete\n");
	पूर्ण अन्यथा अणु
		WARN_ON(1);
	पूर्ण

	brcmf_config_ap_mgmt_ie(अगरp->vअगर, &settings->beacon);
	set_bit(BRCMF_VIF_STATUS_AP_CREATED, &अगरp->vअगर->sme_state);
	brcmf_net_setcarrier(अगरp, true);

निकास:
	अगर ((err) && (!mbss)) अणु
		brcmf_set_mpc(अगरp, 1);
		brcmf_configure_arp_nd_offload(अगरp, true);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक brcmf_cfg80211_stop_ap(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_cfg80211_profile *profile = &अगरp->vअगर->profile;
	s32 err;
	काष्ठा brcmf_fil_bss_enable_le bss_enable;
	काष्ठा brcmf_join_params join_params;

	brcmf_dbg(TRACE, "Enter\n");

	अगर (अगरp->vअगर->wdev.अगरtype == NL80211_IFTYPE_AP) अणु
		/* Due to most likely deauths outstanding we sleep */
		/* first to make sure they get processed by fw. */
		msleep(400);

		अगर (profile->use_fwauth != BIT(BRCMF_PROखाता_FWAUTH_NONE)) अणु
			अगर (profile->use_fwauth & BIT(BRCMF_PROखाता_FWAUTH_PSK))
				brcmf_set_pmk(अगरp, शून्य, 0);
			अगर (profile->use_fwauth & BIT(BRCMF_PROखाता_FWAUTH_SAE))
				brcmf_set_sae_password(अगरp, शून्य, 0);
			profile->use_fwauth = BIT(BRCMF_PROखाता_FWAUTH_NONE);
		पूर्ण

		अगर (अगरp->vअगर->mbss) अणु
			err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_DOWN, 1);
			वापस err;
		पूर्ण

		/* First BSS करोesn't get a full reset */
		अगर (अगरp->bsscfgidx == 0)
			brcmf_fil_iovar_पूर्णांक_set(अगरp, "closednet", 0);

		स_रखो(&join_params, 0, माप(join_params));
		err = brcmf_fil_cmd_data_set(अगरp, BRCMF_C_SET_SSID,
					     &join_params, माप(join_params));
		अगर (err < 0)
			bphy_err(drvr, "SET SSID error (%d)\n", err);
		err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_DOWN, 1);
		अगर (err < 0)
			bphy_err(drvr, "BRCMF_C_DOWN error %d\n", err);
		err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_AP, 0);
		अगर (err < 0)
			bphy_err(drvr, "setting AP mode failed %d\n", err);
		अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_MBSS))
			brcmf_fil_iovar_पूर्णांक_set(अगरp, "mbss", 0);
		brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_REGULATORY,
				      अगरp->vअगर->is_11d);
		/* Bring device back up so it can be used again */
		err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_UP, 1);
		अगर (err < 0)
			bphy_err(drvr, "BRCMF_C_UP error %d\n", err);

		brcmf_vअगर_clear_mgmt_ies(अगरp->vअगर);
	पूर्ण अन्यथा अणु
		bss_enable.bsscfgidx = cpu_to_le32(अगरp->bsscfgidx);
		bss_enable.enable = cpu_to_le32(0);
		err = brcmf_fil_iovar_data_set(अगरp, "bss", &bss_enable,
					       माप(bss_enable));
		अगर (err < 0)
			bphy_err(drvr, "bss_enable config failed %d\n", err);
	पूर्ण
	brcmf_set_mpc(अगरp, 1);
	brcmf_configure_arp_nd_offload(अगरp, true);
	clear_bit(BRCMF_VIF_STATUS_AP_CREATED, &अगरp->vअगर->sme_state);
	brcmf_net_setcarrier(अगरp, false);

	वापस err;
पूर्ण

अटल s32
brcmf_cfg80211_change_beacon(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
			     काष्ठा cfg80211_beacon_data *info)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	s32 err;

	brcmf_dbg(TRACE, "Enter\n");

	err = brcmf_config_ap_mgmt_ie(अगरp->vअगर, info);

	वापस err;
पूर्ण

अटल पूर्णांक
brcmf_cfg80211_del_station(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
			   काष्ठा station_del_parameters *params)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_scb_val_le scbval;
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	s32 err;

	अगर (!params->mac)
		वापस -EFAULT;

	brcmf_dbg(TRACE, "Enter %pM\n", params->mac);

	अगर (अगरp->vअगर == cfg->p2p.bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर)
		अगरp = cfg->p2p.bss_idx[P2PAPI_BSSCFG_PRIMARY].vअगर->अगरp;
	अगर (!check_vअगर_up(अगरp->vअगर))
		वापस -EIO;

	स_नकल(&scbval.ea, params->mac, ETH_ALEN);
	scbval.val = cpu_to_le32(params->reason_code);
	err = brcmf_fil_cmd_data_set(अगरp, BRCMF_C_SCB_DEAUTHENTICATE_FOR_REASON,
				     &scbval, माप(scbval));
	अगर (err)
		bphy_err(drvr, "SCB_DEAUTHENTICATE_FOR_REASON failed %d\n",
			 err);

	brcmf_dbg(TRACE, "Exit\n");
	वापस err;
पूर्ण

अटल पूर्णांक
brcmf_cfg80211_change_station(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
			      स्थिर u8 *mac, काष्ठा station_parameters *params)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	s32 err;

	brcmf_dbg(TRACE, "Enter, MAC %pM, mask 0x%04x set 0x%04x\n", mac,
		  params->sta_flags_mask, params->sta_flags_set);

	/* Ignore all 00 MAC */
	अगर (is_zero_ether_addr(mac))
		वापस 0;

	अगर (!(params->sta_flags_mask & BIT(NL80211_STA_FLAG_AUTHORIZED)))
		वापस 0;

	अगर (params->sta_flags_set & BIT(NL80211_STA_FLAG_AUTHORIZED))
		err = brcmf_fil_cmd_data_set(अगरp, BRCMF_C_SET_SCB_AUTHORIZE,
					     (व्योम *)mac, ETH_ALEN);
	अन्यथा
		err = brcmf_fil_cmd_data_set(अगरp, BRCMF_C_SET_SCB_DEAUTHORIZE,
					     (व्योम *)mac, ETH_ALEN);
	अगर (err < 0)
		bphy_err(drvr, "Setting SCB (de-)authorize failed, %d\n", err);

	वापस err;
पूर्ण

अटल व्योम
brcmf_cfg80211_update_mgmt_frame_registrations(काष्ठा wiphy *wiphy,
					       काष्ठा wireless_dev *wdev,
					       काष्ठा mgmt_frame_regs *upd)
अणु
	काष्ठा brcmf_cfg80211_vअगर *vअगर;

	vअगर = container_of(wdev, काष्ठा brcmf_cfg80211_vअगर, wdev);

	vअगर->mgmt_rx_reg = upd->पूर्णांकerface_stypes;
पूर्ण


अटल पूर्णांक
brcmf_cfg80211_mgmt_tx(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		       काष्ठा cfg80211_mgmt_tx_params *params, u64 *cookie)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा ieee80211_channel *chan = params->chan;
	काष्ठा brcmf_pub *drvr = cfg->pub;
	स्थिर u8 *buf = params->buf;
	माप_प्रकार len = params->len;
	स्थिर काष्ठा ieee80211_mgmt *mgmt;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	s32 err = 0;
	s32 ie_offset;
	s32 ie_len;
	काष्ठा brcmf_fil_action_frame_le *action_frame;
	काष्ठा brcmf_fil_af_params_le *af_params;
	bool ack;
	s32 chan_nr;
	u32 freq;

	brcmf_dbg(TRACE, "Enter\n");

	*cookie = 0;

	mgmt = (स्थिर काष्ठा ieee80211_mgmt *)buf;

	अगर (!ieee80211_is_mgmt(mgmt->frame_control)) अणु
		bphy_err(drvr, "Driver only allows MGMT packet type\n");
		वापस -EPERM;
	पूर्ण

	vअगर = container_of(wdev, काष्ठा brcmf_cfg80211_vअगर, wdev);

	अगर (ieee80211_is_probe_resp(mgmt->frame_control)) अणु
		/* Right now the only reason to get a probe response */
		/* is क्रम p2p listen response or क्रम p2p GO from     */
		/* wpa_supplicant. Unक्रमtunately the probe is send   */
		/* on primary ndev, जबतक करोngle wants it on the p2p */
		/* vअगर. Since this is only reason क्रम a probe        */
		/* response to be sent, the vअगर is taken from cfg.   */
		/* If ever desired to send proberesp क्रम non p2p     */
		/* response then data should be checked क्रम          */
		/* "DIRECT-". Note in future supplicant will take    */
		/* dedicated p2p wdev to करो this and then this 'hack'*/
		/* is not needed anymore.                            */
		ie_offset =  DOT11_MGMT_HDR_LEN +
			     DOT11_BCN_PRB_FIXED_LEN;
		ie_len = len - ie_offset;
		अगर (vअगर == cfg->p2p.bss_idx[P2PAPI_BSSCFG_PRIMARY].vअगर)
			vअगर = cfg->p2p.bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर;
		err = brcmf_vअगर_set_mgmt_ie(vअगर,
					    BRCMF_VNDR_IE_PRBRSP_FLAG,
					    &buf[ie_offset],
					    ie_len);
		cfg80211_mgmt_tx_status(wdev, *cookie, buf, len, true,
					GFP_KERNEL);
	पूर्ण अन्यथा अगर (ieee80211_is_action(mgmt->frame_control)) अणु
		अगर (len > BRCMF_FIL_ACTION_FRAME_SIZE + DOT11_MGMT_HDR_LEN) अणु
			bphy_err(drvr, "invalid action frame length\n");
			err = -EINVAL;
			जाओ निकास;
		पूर्ण
		af_params = kzalloc(माप(*af_params), GFP_KERNEL);
		अगर (af_params == शून्य) अणु
			bphy_err(drvr, "unable to allocate frame\n");
			err = -ENOMEM;
			जाओ निकास;
		पूर्ण
		action_frame = &af_params->action_frame;
		/* Add the packet Id */
		action_frame->packet_id = cpu_to_le32(*cookie);
		/* Add BSSID */
		स_नकल(&action_frame->da[0], &mgmt->da[0], ETH_ALEN);
		स_नकल(&af_params->bssid[0], &mgmt->bssid[0], ETH_ALEN);
		/* Add the length exepted क्रम 802.11 header  */
		action_frame->len = cpu_to_le16(len - DOT11_MGMT_HDR_LEN);
		/* Add the channel. Use the one specअगरied as parameter अगर any or
		 * the current one (got from the firmware) otherwise
		 */
		अगर (chan)
			freq = chan->center_freq;
		अन्यथा
			brcmf_fil_cmd_पूर्णांक_get(vअगर->अगरp, BRCMF_C_GET_CHANNEL,
					      &freq);
		chan_nr = ieee80211_frequency_to_channel(freq);
		af_params->channel = cpu_to_le32(chan_nr);
		af_params->dwell_समय = cpu_to_le32(params->रुको);
		स_नकल(action_frame->data, &buf[DOT11_MGMT_HDR_LEN],
		       le16_to_cpu(action_frame->len));

		brcmf_dbg(TRACE, "Action frame, cookie=%lld, len=%d, freq=%d\n",
			  *cookie, le16_to_cpu(action_frame->len), freq);

		ack = brcmf_p2p_send_action_frame(cfg, cfg_to_ndev(cfg),
						  af_params);

		cfg80211_mgmt_tx_status(wdev, *cookie, buf, len, ack,
					GFP_KERNEL);
		kमुक्त(af_params);
	पूर्ण अन्यथा अणु
		brcmf_dbg(TRACE, "Unhandled, fc=%04x!!\n", mgmt->frame_control);
		brcmf_dbg_hex_dump(true, buf, len, "payload, len=%zu\n", len);
	पूर्ण

निकास:
	वापस err;
पूर्ण

अटल पूर्णांक brcmf_cfg80211_set_cqm_rssi_range_config(काष्ठा wiphy *wiphy,
						    काष्ठा net_device *ndev,
						    s32 rssi_low, s32 rssi_high)
अणु
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	काष्ठा brcmf_अगर *अगरp;
	पूर्णांक err = 0;

	brcmf_dbg(TRACE, "low=%d high=%d", rssi_low, rssi_high);

	अगरp = netdev_priv(ndev);
	vअगर = अगरp->vअगर;

	अगर (rssi_low != vअगर->cqm_rssi_low || rssi_high != vअगर->cqm_rssi_high) अणु
		/* The firmware will send an event when the RSSI is less than or
		 * equal to a configured level and the previous RSSI event was
		 * less than or equal to a dअगरferent level. Set a third level
		 * so that we also detect the transition from rssi <= rssi_high
		 * to rssi > rssi_high.
		 */
		काष्ठा brcmf_rssi_event_le config = अणु
			.rate_limit_msec = cpu_to_le32(0),
			.rssi_level_num = 3,
			.rssi_levels = अणु
				clamp_val(rssi_low, S8_MIN, S8_MAX - 2),
				clamp_val(rssi_high, S8_MIN + 1, S8_MAX - 1),
				S8_MAX,
			पूर्ण,
		पूर्ण;

		err = brcmf_fil_iovar_data_set(अगरp, "rssi_event", &config,
					       माप(config));
		अगर (err) अणु
			err = -EINVAL;
		पूर्ण अन्यथा अणु
			vअगर->cqm_rssi_low = rssi_low;
			vअगर->cqm_rssi_high = rssi_high;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक
brcmf_cfg80211_cancel_reमुख्य_on_channel(काष्ठा wiphy *wiphy,
					काष्ठा wireless_dev *wdev,
					u64 cookie)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	पूर्णांक err = 0;

	brcmf_dbg(TRACE, "Enter p2p listen cancel\n");

	vअगर = cfg->p2p.bss_idx[P2PAPI_BSSCFG_DEVICE].vअगर;
	अगर (vअगर == शून्य) अणु
		bphy_err(drvr, "No p2p device available for probe response\n");
		err = -ENODEV;
		जाओ निकास;
	पूर्ण
	brcmf_p2p_cancel_reमुख्य_on_channel(vअगर->अगरp);
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक brcmf_cfg80211_get_channel(काष्ठा wiphy *wiphy,
				      काष्ठा wireless_dev *wdev,
				      काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा net_device *ndev = wdev->netdev;
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmu_chan ch;
	क्रमागत nl80211_band band = 0;
	क्रमागत nl80211_chan_width width = 0;
	u32 chanspec;
	पूर्णांक freq, err;

	अगर (!ndev || drvr->bus_अगर->state != BRCMF_BUS_UP)
		वापस -ENODEV;

	err = brcmf_fil_iovar_पूर्णांक_get(netdev_priv(ndev), "chanspec", &chanspec);
	अगर (err) अणु
		bphy_err(drvr, "chanspec failed (%d)\n", err);
		वापस err;
	पूर्ण

	ch.chspec = chanspec;
	cfg->d11inf.decchspec(&ch);

	चयन (ch.band) अणु
	हाल BRCMU_CHAN_BAND_2G:
		band = NL80211_BAND_2GHZ;
		अवरोध;
	हाल BRCMU_CHAN_BAND_5G:
		band = NL80211_BAND_5GHZ;
		अवरोध;
	पूर्ण

	चयन (ch.bw) अणु
	हाल BRCMU_CHAN_BW_80:
		width = NL80211_CHAN_WIDTH_80;
		अवरोध;
	हाल BRCMU_CHAN_BW_40:
		width = NL80211_CHAN_WIDTH_40;
		अवरोध;
	हाल BRCMU_CHAN_BW_20:
		width = NL80211_CHAN_WIDTH_20;
		अवरोध;
	हाल BRCMU_CHAN_BW_80P80:
		width = NL80211_CHAN_WIDTH_80P80;
		अवरोध;
	हाल BRCMU_CHAN_BW_160:
		width = NL80211_CHAN_WIDTH_160;
		अवरोध;
	पूर्ण

	freq = ieee80211_channel_to_frequency(ch.control_ch_num, band);
	chandef->chan = ieee80211_get_channel(wiphy, freq);
	chandef->width = width;
	chandef->center_freq1 = ieee80211_channel_to_frequency(ch.chnum, band);
	chandef->center_freq2 = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_cfg80211_crit_proto_start(काष्ठा wiphy *wiphy,
					   काष्ठा wireless_dev *wdev,
					   क्रमागत nl80211_crit_proto_id proto,
					   u16 duration)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_cfg80211_vअगर *vअगर;

	vअगर = container_of(wdev, काष्ठा brcmf_cfg80211_vअगर, wdev);

	/* only DHCP support क्रम now */
	अगर (proto != NL80211_CRIT_PROTO_DHCP)
		वापस -EINVAL;

	/* suppress and पात scanning */
	set_bit(BRCMF_SCAN_STATUS_SUPPRESS, &cfg->scan_status);
	brcmf_पात_scanning(cfg);

	वापस brcmf_btcoex_set_mode(vअगर, BRCMF_BTCOEX_DISABLED, duration);
पूर्ण

अटल व्योम brcmf_cfg80211_crit_proto_stop(काष्ठा wiphy *wiphy,
					   काष्ठा wireless_dev *wdev)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_cfg80211_vअगर *vअगर;

	vअगर = container_of(wdev, काष्ठा brcmf_cfg80211_vअगर, wdev);

	brcmf_btcoex_set_mode(vअगर, BRCMF_BTCOEX_ENABLED, 0);
	clear_bit(BRCMF_SCAN_STATUS_SUPPRESS, &cfg->scan_status);
पूर्ण

अटल s32
brcmf_notअगरy_tdls_peer_event(काष्ठा brcmf_अगर *अगरp,
			     स्थिर काष्ठा brcmf_event_msg *e, व्योम *data)
अणु
	चयन (e->reason) अणु
	हाल BRCMF_E_REASON_TDLS_PEER_DISCOVERED:
		brcmf_dbg(TRACE, "TDLS Peer Discovered\n");
		अवरोध;
	हाल BRCMF_E_REASON_TDLS_PEER_CONNECTED:
		brcmf_dbg(TRACE, "TDLS Peer Connected\n");
		brcmf_proto_add_tdls_peer(अगरp->drvr, अगरp->अगरidx, (u8 *)e->addr);
		अवरोध;
	हाल BRCMF_E_REASON_TDLS_PEER_DISCONNECTED:
		brcmf_dbg(TRACE, "TDLS Peer Disconnected\n");
		brcmf_proto_delete_peer(अगरp->drvr, अगरp->अगरidx, (u8 *)e->addr);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_convert_nl80211_tdls_oper(क्रमागत nl80211_tdls_operation oper)
अणु
	पूर्णांक ret;

	चयन (oper) अणु
	हाल NL80211_TDLS_DISCOVERY_REQ:
		ret = BRCMF_TDLS_MANUAL_EP_DISCOVERY;
		अवरोध;
	हाल NL80211_TDLS_SETUP:
		ret = BRCMF_TDLS_MANUAL_EP_CREATE;
		अवरोध;
	हाल NL80211_TDLS_TEARDOWN:
		ret = BRCMF_TDLS_MANUAL_EP_DELETE;
		अवरोध;
	शेष:
		brcmf_err("unsupported operation: %d\n", oper);
		ret = -EOPNOTSUPP;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक brcmf_cfg80211_tdls_oper(काष्ठा wiphy *wiphy,
				    काष्ठा net_device *ndev, स्थिर u8 *peer,
				    क्रमागत nl80211_tdls_operation oper)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_अगर *अगरp;
	काष्ठा brcmf_tdls_iovar_le info;
	पूर्णांक ret = 0;

	ret = brcmf_convert_nl80211_tdls_oper(oper);
	अगर (ret < 0)
		वापस ret;

	अगरp = netdev_priv(ndev);
	स_रखो(&info, 0, माप(info));
	info.mode = (u8)ret;
	अगर (peer)
		स_नकल(info.ea, peer, ETH_ALEN);

	ret = brcmf_fil_iovar_data_set(अगरp, "tdls_endpoint",
				       &info, माप(info));
	अगर (ret < 0)
		bphy_err(drvr, "tdls_endpoint iovar failed: ret=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक
brcmf_cfg80211_update_conn_params(काष्ठा wiphy *wiphy,
				  काष्ठा net_device *ndev,
				  काष्ठा cfg80211_connect_params *sme,
				  u32 changed)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_अगर *अगरp;
	पूर्णांक err;

	अगर (!(changed & UPDATE_ASSOC_IES))
		वापस 0;

	अगरp = netdev_priv(ndev);
	err = brcmf_vअगर_set_mgmt_ie(अगरp->vअगर, BRCMF_VNDR_IE_ASSOCREQ_FLAG,
				    sme->ie, sme->ie_len);
	अगर (err)
		bphy_err(drvr, "Set Assoc REQ IE Failed\n");
	अन्यथा
		brcmf_dbg(TRACE, "Applied Vndr IEs for Assoc request\n");

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक
brcmf_cfg80211_set_rekey_data(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
			      काष्ठा cfg80211_gtk_rekey_data *gtk)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_gtk_keyinfo_le gtk_le;
	पूर्णांक ret;

	brcmf_dbg(TRACE, "Enter, bssidx=%d\n", अगरp->bsscfgidx);

	स_नकल(gtk_le.kck, gtk->kck, माप(gtk_le.kck));
	स_नकल(gtk_le.kek, gtk->kek, माप(gtk_le.kek));
	स_नकल(gtk_le.replay_counter, gtk->replay_ctr,
	       माप(gtk_le.replay_counter));

	ret = brcmf_fil_iovar_data_set(अगरp, "gtk_key_info", &gtk_le,
				       माप(gtk_le));
	अगर (ret < 0)
		bphy_err(drvr, "gtk_key_info iovar failed: ret=%d\n", ret);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक brcmf_cfg80211_set_pmk(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  स्थिर काष्ठा cfg80211_pmk_conf *conf)
अणु
	काष्ठा brcmf_अगर *अगरp;

	brcmf_dbg(TRACE, "enter\n");

	/* expect using firmware supplicant क्रम 1X */
	अगरp = netdev_priv(dev);
	अगर (WARN_ON(अगरp->vअगर->profile.use_fwsup != BRCMF_PROखाता_FWSUP_1X))
		वापस -EINVAL;

	अगर (conf->pmk_len > BRCMF_WSEC_MAX_PSK_LEN)
		वापस -दुस्फल;

	वापस brcmf_set_pmk(अगरp, conf->pmk, conf->pmk_len);
पूर्ण

अटल पूर्णांक brcmf_cfg80211_del_pmk(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  स्थिर u8 *aa)
अणु
	काष्ठा brcmf_अगर *अगरp;

	brcmf_dbg(TRACE, "enter\n");
	अगरp = netdev_priv(dev);
	अगर (WARN_ON(अगरp->vअगर->profile.use_fwsup != BRCMF_PROखाता_FWSUP_1X))
		वापस -EINVAL;

	वापस brcmf_set_pmk(अगरp, शून्य, 0);
पूर्ण

अटल काष्ठा cfg80211_ops brcmf_cfg80211_ops = अणु
	.add_भव_पूर्णांकf = brcmf_cfg80211_add_अगरace,
	.del_भव_पूर्णांकf = brcmf_cfg80211_del_अगरace,
	.change_भव_पूर्णांकf = brcmf_cfg80211_change_अगरace,
	.scan = brcmf_cfg80211_scan,
	.set_wiphy_params = brcmf_cfg80211_set_wiphy_params,
	.join_ibss = brcmf_cfg80211_join_ibss,
	.leave_ibss = brcmf_cfg80211_leave_ibss,
	.get_station = brcmf_cfg80211_get_station,
	.dump_station = brcmf_cfg80211_dump_station,
	.set_tx_घातer = brcmf_cfg80211_set_tx_घातer,
	.get_tx_घातer = brcmf_cfg80211_get_tx_घातer,
	.add_key = brcmf_cfg80211_add_key,
	.del_key = brcmf_cfg80211_del_key,
	.get_key = brcmf_cfg80211_get_key,
	.set_शेष_key = brcmf_cfg80211_config_शेष_key,
	.set_शेष_mgmt_key = brcmf_cfg80211_config_शेष_mgmt_key,
	.set_घातer_mgmt = brcmf_cfg80211_set_घातer_mgmt,
	.connect = brcmf_cfg80211_connect,
	.disconnect = brcmf_cfg80211_disconnect,
	.suspend = brcmf_cfg80211_suspend,
	.resume = brcmf_cfg80211_resume,
	.set_pmksa = brcmf_cfg80211_set_pmksa,
	.del_pmksa = brcmf_cfg80211_del_pmksa,
	.flush_pmksa = brcmf_cfg80211_flush_pmksa,
	.start_ap = brcmf_cfg80211_start_ap,
	.stop_ap = brcmf_cfg80211_stop_ap,
	.change_beacon = brcmf_cfg80211_change_beacon,
	.del_station = brcmf_cfg80211_del_station,
	.change_station = brcmf_cfg80211_change_station,
	.sched_scan_start = brcmf_cfg80211_sched_scan_start,
	.sched_scan_stop = brcmf_cfg80211_sched_scan_stop,
	.update_mgmt_frame_registrations =
		brcmf_cfg80211_update_mgmt_frame_registrations,
	.mgmt_tx = brcmf_cfg80211_mgmt_tx,
	.set_cqm_rssi_range_config = brcmf_cfg80211_set_cqm_rssi_range_config,
	.reमुख्य_on_channel = brcmf_p2p_reमुख्य_on_channel,
	.cancel_reमुख्य_on_channel = brcmf_cfg80211_cancel_reमुख्य_on_channel,
	.get_channel = brcmf_cfg80211_get_channel,
	.start_p2p_device = brcmf_p2p_start_device,
	.stop_p2p_device = brcmf_p2p_stop_device,
	.crit_proto_start = brcmf_cfg80211_crit_proto_start,
	.crit_proto_stop = brcmf_cfg80211_crit_proto_stop,
	.tdls_oper = brcmf_cfg80211_tdls_oper,
	.update_connect_params = brcmf_cfg80211_update_conn_params,
	.set_pmk = brcmf_cfg80211_set_pmk,
	.del_pmk = brcmf_cfg80211_del_pmk,
पूर्ण;

काष्ठा cfg80211_ops *brcmf_cfg80211_get_ops(काष्ठा brcmf_mp_device *settings)
अणु
	काष्ठा cfg80211_ops *ops;

	ops = kmemdup(&brcmf_cfg80211_ops, माप(brcmf_cfg80211_ops),
		       GFP_KERNEL);

	अगर (ops && settings->roamoff)
		ops->update_connect_params = शून्य;

	वापस ops;
पूर्ण

काष्ठा brcmf_cfg80211_vअगर *brcmf_alloc_vअगर(काष्ठा brcmf_cfg80211_info *cfg,
					   क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा brcmf_cfg80211_vअगर *vअगर_walk;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	bool mbss;
	काष्ठा brcmf_अगर *अगरp = brcmf_get_अगरp(cfg->pub, 0);

	brcmf_dbg(TRACE, "allocating virtual interface (size=%zu)\n",
		  माप(*vअगर));
	vअगर = kzalloc(माप(*vअगर), GFP_KERNEL);
	अगर (!vअगर)
		वापस ERR_PTR(-ENOMEM);

	vअगर->wdev.wiphy = cfg->wiphy;
	vअगर->wdev.अगरtype = type;

	brcmf_init_prof(&vअगर->profile);

	अगर (type == NL80211_IFTYPE_AP &&
	    brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_MBSS)) अणु
		mbss = false;
		list_क्रम_each_entry(vअगर_walk, &cfg->vअगर_list, list) अणु
			अगर (vअगर_walk->wdev.अगरtype == NL80211_IFTYPE_AP) अणु
				mbss = true;
				अवरोध;
			पूर्ण
		पूर्ण
		vअगर->mbss = mbss;
	पूर्ण

	list_add_tail(&vअगर->list, &cfg->vअगर_list);
	वापस vअगर;
पूर्ण

व्योम brcmf_मुक्त_vअगर(काष्ठा brcmf_cfg80211_vअगर *vअगर)
अणु
	list_del(&vअगर->list);
	kमुक्त(vअगर);
पूर्ण

व्योम brcmf_cfg80211_मुक्त_netdev(काष्ठा net_device *ndev)
अणु
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	काष्ठा brcmf_अगर *अगरp;

	अगरp = netdev_priv(ndev);
	vअगर = अगरp->vअगर;

	अगर (vअगर)
		brcmf_मुक्त_vअगर(vअगर);
पूर्ण

अटल bool brcmf_is_linkup(काष्ठा brcmf_cfg80211_vअगर *vअगर,
			    स्थिर काष्ठा brcmf_event_msg *e)
अणु
	u32 event = e->event_code;
	u32 status = e->status;

	अगर ((vअगर->profile.use_fwsup == BRCMF_PROखाता_FWSUP_PSK ||
	     vअगर->profile.use_fwsup == BRCMF_PROखाता_FWSUP_SAE) &&
	    event == BRCMF_E_PSK_SUP &&
	    status == BRCMF_E_STATUS_FWSUP_COMPLETED)
		set_bit(BRCMF_VIF_STATUS_EAP_SUCCESS, &vअगर->sme_state);
	अगर (event == BRCMF_E_SET_SSID && status == BRCMF_E_STATUS_SUCCESS) अणु
		brcmf_dbg(CONN, "Processing set ssid\n");
		स_नकल(vअगर->profile.bssid, e->addr, ETH_ALEN);
		अगर (vअगर->profile.use_fwsup != BRCMF_PROखाता_FWSUP_PSK &&
		    vअगर->profile.use_fwsup != BRCMF_PROखाता_FWSUP_SAE)
			वापस true;

		set_bit(BRCMF_VIF_STATUS_ASSOC_SUCCESS, &vअगर->sme_state);
	पूर्ण

	अगर (test_bit(BRCMF_VIF_STATUS_EAP_SUCCESS, &vअगर->sme_state) &&
	    test_bit(BRCMF_VIF_STATUS_ASSOC_SUCCESS, &vअगर->sme_state)) अणु
		clear_bit(BRCMF_VIF_STATUS_EAP_SUCCESS, &vअगर->sme_state);
		clear_bit(BRCMF_VIF_STATUS_ASSOC_SUCCESS, &vअगर->sme_state);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool brcmf_is_linkकरोwn(काष्ठा brcmf_cfg80211_vअगर *vअगर,
			    स्थिर काष्ठा brcmf_event_msg *e)
अणु
	u32 event = e->event_code;
	u16 flags = e->flags;

	अगर ((event == BRCMF_E_DEAUTH) || (event == BRCMF_E_DEAUTH_IND) ||
	    (event == BRCMF_E_DISASSOC_IND) ||
	    ((event == BRCMF_E_LINK) && (!(flags & BRCMF_EVENT_MSG_LINK)))) अणु
		brcmf_dbg(CONN, "Processing link down\n");
		clear_bit(BRCMF_VIF_STATUS_EAP_SUCCESS, &vअगर->sme_state);
		clear_bit(BRCMF_VIF_STATUS_ASSOC_SUCCESS, &vअगर->sme_state);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool brcmf_is_nonetwork(काष्ठा brcmf_cfg80211_info *cfg,
			       स्थिर काष्ठा brcmf_event_msg *e)
अणु
	u32 event = e->event_code;
	u32 status = e->status;

	अगर (event == BRCMF_E_LINK && status == BRCMF_E_STATUS_NO_NETWORKS) अणु
		brcmf_dbg(CONN, "Processing Link %s & no network found\n",
			  e->flags & BRCMF_EVENT_MSG_LINK ? "up" : "down");
		वापस true;
	पूर्ण

	अगर (event == BRCMF_E_SET_SSID && status != BRCMF_E_STATUS_SUCCESS) अणु
		brcmf_dbg(CONN, "Processing connecting & no network found\n");
		वापस true;
	पूर्ण

	अगर (event == BRCMF_E_PSK_SUP &&
	    status != BRCMF_E_STATUS_FWSUP_COMPLETED) अणु
		brcmf_dbg(CONN, "Processing failed supplicant state: %u\n",
			  status);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम brcmf_clear_assoc_ies(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	काष्ठा brcmf_cfg80211_connect_info *conn_info = cfg_to_conn(cfg);

	kमुक्त(conn_info->req_ie);
	conn_info->req_ie = शून्य;
	conn_info->req_ie_len = 0;
	kमुक्त(conn_info->resp_ie);
	conn_info->resp_ie = शून्य;
	conn_info->resp_ie_len = 0;
पूर्ण

u8 brcmf_map_prio_to_prec(व्योम *config, u8 prio)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = (काष्ठा brcmf_cfg80211_info *)config;

	अगर (!cfg)
		वापस (prio == PRIO_8021D_NONE || prio == PRIO_8021D_BE) ?
		       (prio ^ 2) : prio;

	/* For those AC(s) with ACM flag set to 1, convert its 4-level priority
	 * to an 8-level precedence which is the same as BE's
	 */
	अगर (prio > PRIO_8021D_EE &&
	    cfg->ac_priority[prio] == cfg->ac_priority[PRIO_8021D_BE])
		वापस cfg->ac_priority[prio] * 2;

	/* Conversion of 4-level priority to 8-level precedence */
	अगर (prio == PRIO_8021D_BE || prio == PRIO_8021D_BK ||
	    prio == PRIO_8021D_CL || prio == PRIO_8021D_VO)
		वापस cfg->ac_priority[prio] * 2;
	अन्यथा
		वापस cfg->ac_priority[prio] * 2 + 1;
पूर्ण

u8 brcmf_map_prio_to_aci(व्योम *config, u8 prio)
अणु
	/* Prio here refers to the 802.1d priority in range of 0 to 7.
	 * ACI here refers to the WLAN AC Index in range of 0 to 3.
	 * This function will वापस ACI corresponding to input prio.
	 */
	काष्ठा brcmf_cfg80211_info *cfg = (काष्ठा brcmf_cfg80211_info *)config;

	अगर (cfg)
		वापस cfg->ac_priority[prio];

	वापस prio;
पूर्ण

अटल व्योम brcmf_init_wmm_prio(u8 *priority)
अणु
	/* Initialize AC priority array to शेष
	 * 802.1d priority as per following table:
	 * 802.1d prio 0,3 maps to BE
	 * 802.1d prio 1,2 maps to BK
	 * 802.1d prio 4,5 maps to VI
	 * 802.1d prio 6,7 maps to VO
	 */
	priority[0] = BRCMF_FWS_FIFO_AC_BE;
	priority[3] = BRCMF_FWS_FIFO_AC_BE;
	priority[1] = BRCMF_FWS_FIFO_AC_BK;
	priority[2] = BRCMF_FWS_FIFO_AC_BK;
	priority[4] = BRCMF_FWS_FIFO_AC_VI;
	priority[5] = BRCMF_FWS_FIFO_AC_VI;
	priority[6] = BRCMF_FWS_FIFO_AC_VO;
	priority[7] = BRCMF_FWS_FIFO_AC_VO;
पूर्ण

अटल व्योम brcmf_wअगरi_prioritize_acparams(स्थिर
	काष्ठा brcmf_cfg80211_edcf_acparam *acp, u8 *priority)
अणु
	u8 aci;
	u8 aअगरsn;
	u8 ecwmin;
	u8 ecwmax;
	u8 acm;
	u8 ranking_basis[EDCF_AC_COUNT];
	u8 aci_prio[EDCF_AC_COUNT]; /* AC_BE, AC_BK, AC_VI, AC_VO */
	u8 index;

	क्रम (aci = 0; aci < EDCF_AC_COUNT; aci++, acp++) अणु
		aअगरsn  = acp->ACI & EDCF_AIFSN_MASK;
		acm = (acp->ACI & EDCF_ACM_MASK) ? 1 : 0;
		ecwmin = acp->ECW & EDCF_ECWMIN_MASK;
		ecwmax = (acp->ECW & EDCF_ECWMAX_MASK) >> EDCF_ECWMAX_SHIFT;
		brcmf_dbg(CONN, "ACI %d aifsn %d acm %d ecwmin %d ecwmax %d\n",
			  aci, aअगरsn, acm, ecwmin, ecwmax);
		/* Default AC_VO will be the lowest ranking value */
		ranking_basis[aci] = aअगरsn + ecwmin + ecwmax;
		/* Initialise priority starting at 0 (AC_BE) */
		aci_prio[aci] = 0;

		/* If ACM is set, STA can't use this AC as per 802.11.
		 * Change the ranking to BE
		 */
		अगर (aci != AC_BE && aci != AC_BK && acm == 1)
			ranking_basis[aci] = ranking_basis[AC_BE];
	पूर्ण

	/* Ranking method which works क्रम AC priority
	 * swapping when values क्रम cwmin, cwmax and aअगरsn are varied
	 * Compare each aci_prio against each other aci_prio
	 */
	क्रम (aci = 0; aci < EDCF_AC_COUNT; aci++) अणु
		क्रम (index = 0; index < EDCF_AC_COUNT; index++) अणु
			अगर (index != aci) अणु
				/* Smaller ranking value has higher priority,
				 * so increment priority क्रम each ACI which has
				 * a higher ranking value
				 */
				अगर (ranking_basis[aci] < ranking_basis[index])
					aci_prio[aci]++;
			पूर्ण
		पूर्ण
	पूर्ण

	/* By now, aci_prio[] will be in range of 0 to 3.
	 * Use ACI prio to get the new priority value क्रम
	 * each 802.1d traffic type, in this range.
	 */
	अगर (!(aci_prio[AC_BE] == aci_prio[AC_BK] &&
	      aci_prio[AC_BK] == aci_prio[AC_VI] &&
	      aci_prio[AC_VI] == aci_prio[AC_VO])) अणु
		/* 802.1d 0,3 maps to BE */
		priority[0] = aci_prio[AC_BE];
		priority[3] = aci_prio[AC_BE];

		/* 802.1d 1,2 maps to BK */
		priority[1] = aci_prio[AC_BK];
		priority[2] = aci_prio[AC_BK];

		/* 802.1d 4,5 maps to VO */
		priority[4] = aci_prio[AC_VI];
		priority[5] = aci_prio[AC_VI];

		/* 802.1d 6,7 maps to VO */
		priority[6] = aci_prio[AC_VO];
		priority[7] = aci_prio[AC_VO];
	पूर्ण अन्यथा अणु
		/* Initialize to शेष priority */
		brcmf_init_wmm_prio(priority);
	पूर्ण

	brcmf_dbg(CONN, "Adj prio BE 0->%d, BK 1->%d, BK 2->%d, BE 3->%d\n",
		  priority[0], priority[1], priority[2], priority[3]);

	brcmf_dbg(CONN, "Adj prio VI 4->%d, VI 5->%d, VO 6->%d, VO 7->%d\n",
		  priority[4], priority[5], priority[6], priority[7]);
पूर्ण

अटल s32 brcmf_get_assoc_ies(काष्ठा brcmf_cfg80211_info *cfg,
			       काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_cfg80211_assoc_ielen_le *assoc_info;
	काष्ठा brcmf_cfg80211_connect_info *conn_info = cfg_to_conn(cfg);
	काष्ठा brcmf_cfg80211_edcf_acparam edcf_acparam_info[EDCF_AC_COUNT];
	u32 req_len;
	u32 resp_len;
	s32 err = 0;

	brcmf_clear_assoc_ies(cfg);

	err = brcmf_fil_iovar_data_get(अगरp, "assoc_info",
				       cfg->extra_buf, WL_ASSOC_INFO_MAX);
	अगर (err) अणु
		bphy_err(drvr, "could not get assoc info (%d)\n", err);
		वापस err;
	पूर्ण
	assoc_info =
		(काष्ठा brcmf_cfg80211_assoc_ielen_le *)cfg->extra_buf;
	req_len = le32_to_cpu(assoc_info->req_len);
	resp_len = le32_to_cpu(assoc_info->resp_len);
	अगर (req_len) अणु
		err = brcmf_fil_iovar_data_get(अगरp, "assoc_req_ies",
					       cfg->extra_buf,
					       WL_ASSOC_INFO_MAX);
		अगर (err) अणु
			bphy_err(drvr, "could not get assoc req (%d)\n", err);
			वापस err;
		पूर्ण
		conn_info->req_ie_len = req_len;
		conn_info->req_ie =
		    kmemdup(cfg->extra_buf, conn_info->req_ie_len,
			    GFP_KERNEL);
		अगर (!conn_info->req_ie)
			conn_info->req_ie_len = 0;
	पूर्ण अन्यथा अणु
		conn_info->req_ie_len = 0;
		conn_info->req_ie = शून्य;
	पूर्ण
	अगर (resp_len) अणु
		err = brcmf_fil_iovar_data_get(अगरp, "assoc_resp_ies",
					       cfg->extra_buf,
					       WL_ASSOC_INFO_MAX);
		अगर (err) अणु
			bphy_err(drvr, "could not get assoc resp (%d)\n", err);
			वापस err;
		पूर्ण
		conn_info->resp_ie_len = resp_len;
		conn_info->resp_ie =
		    kmemdup(cfg->extra_buf, conn_info->resp_ie_len,
			    GFP_KERNEL);
		अगर (!conn_info->resp_ie)
			conn_info->resp_ie_len = 0;

		err = brcmf_fil_iovar_data_get(अगरp, "wme_ac_sta",
					       edcf_acparam_info,
					       माप(edcf_acparam_info));
		अगर (err) अणु
			brcmf_err("could not get wme_ac_sta (%d)\n", err);
			वापस err;
		पूर्ण

		brcmf_wअगरi_prioritize_acparams(edcf_acparam_info,
					       cfg->ac_priority);
	पूर्ण अन्यथा अणु
		conn_info->resp_ie_len = 0;
		conn_info->resp_ie = शून्य;
	पूर्ण
	brcmf_dbg(CONN, "req len (%d) resp len (%d)\n",
		  conn_info->req_ie_len, conn_info->resp_ie_len);

	वापस err;
पूर्ण

अटल s32
brcmf_bss_roaming_करोne(काष्ठा brcmf_cfg80211_info *cfg,
		       काष्ठा net_device *ndev,
		       स्थिर काष्ठा brcmf_event_msg *e)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_cfg80211_profile *profile = &अगरp->vअगर->profile;
	काष्ठा brcmf_cfg80211_connect_info *conn_info = cfg_to_conn(cfg);
	काष्ठा wiphy *wiphy = cfg_to_wiphy(cfg);
	काष्ठा ieee80211_channel *notअगरy_channel = शून्य;
	काष्ठा ieee80211_supported_band *band;
	काष्ठा brcmf_bss_info_le *bi;
	काष्ठा brcmu_chan ch;
	काष्ठा cfg80211_roam_info roam_info = अणुपूर्ण;
	u32 freq;
	s32 err = 0;
	u8 *buf;

	brcmf_dbg(TRACE, "Enter\n");

	brcmf_get_assoc_ies(cfg, अगरp);
	स_नकल(profile->bssid, e->addr, ETH_ALEN);
	brcmf_update_bss_info(cfg, अगरp);

	buf = kzalloc(WL_BSS_INFO_MAX, GFP_KERNEL);
	अगर (buf == शून्य) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* data sent to करोngle has to be little endian */
	*(__le32 *)buf = cpu_to_le32(WL_BSS_INFO_MAX);
	err = brcmf_fil_cmd_data_get(अगरp, BRCMF_C_GET_BSS_INFO,
				     buf, WL_BSS_INFO_MAX);

	अगर (err)
		जाओ करोne;

	bi = (काष्ठा brcmf_bss_info_le *)(buf + 4);
	ch.chspec = le16_to_cpu(bi->chanspec);
	cfg->d11inf.decchspec(&ch);

	अगर (ch.band == BRCMU_CHAN_BAND_2G)
		band = wiphy->bands[NL80211_BAND_2GHZ];
	अन्यथा
		band = wiphy->bands[NL80211_BAND_5GHZ];

	freq = ieee80211_channel_to_frequency(ch.control_ch_num, band->band);
	notअगरy_channel = ieee80211_get_channel(wiphy, freq);

करोne:
	kमुक्त(buf);

	roam_info.channel = notअगरy_channel;
	roam_info.bssid = profile->bssid;
	roam_info.req_ie = conn_info->req_ie;
	roam_info.req_ie_len = conn_info->req_ie_len;
	roam_info.resp_ie = conn_info->resp_ie;
	roam_info.resp_ie_len = conn_info->resp_ie_len;

	cfg80211_roamed(ndev, &roam_info, GFP_KERNEL);
	brcmf_dbg(CONN, "Report roaming result\n");

	अगर (profile->use_fwsup == BRCMF_PROखाता_FWSUP_1X && profile->is_ft) अणु
		cfg80211_port_authorized(ndev, profile->bssid, GFP_KERNEL);
		brcmf_dbg(CONN, "Report port authorized\n");
	पूर्ण

	set_bit(BRCMF_VIF_STATUS_CONNECTED, &अगरp->vअगर->sme_state);
	brcmf_dbg(TRACE, "Exit\n");
	वापस err;
पूर्ण

अटल s32
brcmf_bss_connect_करोne(काष्ठा brcmf_cfg80211_info *cfg,
		       काष्ठा net_device *ndev, स्थिर काष्ठा brcmf_event_msg *e,
		       bool completed)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_cfg80211_profile *profile = &अगरp->vअगर->profile;
	काष्ठा brcmf_cfg80211_connect_info *conn_info = cfg_to_conn(cfg);
	काष्ठा cfg80211_connect_resp_params conn_params;

	brcmf_dbg(TRACE, "Enter\n");

	अगर (test_and_clear_bit(BRCMF_VIF_STATUS_CONNECTING,
			       &अगरp->vअगर->sme_state)) अणु
		स_रखो(&conn_params, 0, माप(conn_params));
		अगर (completed) अणु
			brcmf_get_assoc_ies(cfg, अगरp);
			brcmf_update_bss_info(cfg, अगरp);
			set_bit(BRCMF_VIF_STATUS_CONNECTED,
				&अगरp->vअगर->sme_state);
			conn_params.status = WLAN_STATUS_SUCCESS;
		पूर्ण अन्यथा अणु
			conn_params.status = WLAN_STATUS_AUTH_TIMEOUT;
		पूर्ण
		conn_params.bssid = profile->bssid;
		conn_params.req_ie = conn_info->req_ie;
		conn_params.req_ie_len = conn_info->req_ie_len;
		conn_params.resp_ie = conn_info->resp_ie;
		conn_params.resp_ie_len = conn_info->resp_ie_len;
		cfg80211_connect_करोne(ndev, &conn_params, GFP_KERNEL);
		brcmf_dbg(CONN, "Report connect result - connection %s\n",
			  completed ? "succeeded" : "failed");
	पूर्ण
	brcmf_dbg(TRACE, "Exit\n");
	वापस 0;
पूर्ण

अटल s32
brcmf_notअगरy_connect_status_ap(काष्ठा brcmf_cfg80211_info *cfg,
			       काष्ठा net_device *ndev,
			       स्थिर काष्ठा brcmf_event_msg *e, व्योम *data)
अणु
	काष्ठा brcmf_pub *drvr = cfg->pub;
	अटल पूर्णांक generation;
	u32 event = e->event_code;
	u32 reason = e->reason;
	काष्ठा station_info *sinfo;

	brcmf_dbg(CONN, "event %s (%u), reason %d\n",
		  brcmf_fweh_event_name(event), event, reason);
	अगर (event == BRCMF_E_LINK && reason == BRCMF_E_REASON_LINK_BSSCFG_DIS &&
	    ndev != cfg_to_ndev(cfg)) अणु
		brcmf_dbg(CONN, "AP mode link down\n");
		complete(&cfg->vअगर_disabled);
		वापस 0;
	पूर्ण

	अगर (((event == BRCMF_E_ASSOC_IND) || (event == BRCMF_E_REASSOC_IND)) &&
	    (reason == BRCMF_E_STATUS_SUCCESS)) अणु
		अगर (!data) अणु
			bphy_err(drvr, "No IEs present in ASSOC/REASSOC_IND\n");
			वापस -EINVAL;
		पूर्ण

		sinfo = kzalloc(माप(*sinfo), GFP_KERNEL);
		अगर (!sinfo)
			वापस -ENOMEM;

		sinfo->assoc_req_ies = data;
		sinfo->assoc_req_ies_len = e->datalen;
		generation++;
		sinfo->generation = generation;
		cfg80211_new_sta(ndev, e->addr, sinfo, GFP_KERNEL);

		kमुक्त(sinfo);
	पूर्ण अन्यथा अगर ((event == BRCMF_E_DISASSOC_IND) ||
		   (event == BRCMF_E_DEAUTH_IND) ||
		   (event == BRCMF_E_DEAUTH)) अणु
		cfg80211_del_sta(ndev, e->addr, GFP_KERNEL);
	पूर्ण
	वापस 0;
पूर्ण

अटल s32
brcmf_notअगरy_connect_status(काष्ठा brcmf_अगर *अगरp,
			    स्थिर काष्ठा brcmf_event_msg *e, व्योम *data)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = अगरp->drvr->config;
	काष्ठा net_device *ndev = अगरp->ndev;
	काष्ठा brcmf_cfg80211_profile *profile = &अगरp->vअगर->profile;
	काष्ठा ieee80211_channel *chan;
	s32 err = 0;

	अगर ((e->event_code == BRCMF_E_DEAUTH) ||
	    (e->event_code == BRCMF_E_DEAUTH_IND) ||
	    (e->event_code == BRCMF_E_DISASSOC_IND) ||
	    ((e->event_code == BRCMF_E_LINK) && (!e->flags))) अणु
		brcmf_proto_delete_peer(अगरp->drvr, अगरp->अगरidx, (u8 *)e->addr);
	पूर्ण

	अगर (brcmf_is_apmode(अगरp->vअगर)) अणु
		err = brcmf_notअगरy_connect_status_ap(cfg, ndev, e, data);
	पूर्ण अन्यथा अगर (brcmf_is_linkup(अगरp->vअगर, e)) अणु
		brcmf_dbg(CONN, "Linkup\n");
		अगर (brcmf_is_ibssmode(अगरp->vअगर)) अणु
			brcmf_inक्रमm_ibss(cfg, ndev, e->addr);
			chan = ieee80211_get_channel(cfg->wiphy, cfg->channel);
			स_नकल(profile->bssid, e->addr, ETH_ALEN);
			cfg80211_ibss_joined(ndev, e->addr, chan, GFP_KERNEL);
			clear_bit(BRCMF_VIF_STATUS_CONNECTING,
				  &अगरp->vअगर->sme_state);
			set_bit(BRCMF_VIF_STATUS_CONNECTED,
				&अगरp->vअगर->sme_state);
		पूर्ण अन्यथा
			brcmf_bss_connect_करोne(cfg, ndev, e, true);
		brcmf_net_setcarrier(अगरp, true);
	पूर्ण अन्यथा अगर (brcmf_is_linkकरोwn(अगरp->vअगर, e)) अणु
		brcmf_dbg(CONN, "Linkdown\n");
		अगर (!brcmf_is_ibssmode(अगरp->vअगर) &&
		    test_bit(BRCMF_VIF_STATUS_CONNECTED,
			     &अगरp->vअगर->sme_state)) अणु
			अगर (स_भेद(profile->bssid, e->addr, ETH_ALEN))
				वापस err;

			brcmf_bss_connect_करोne(cfg, ndev, e, false);
			brcmf_link_करोwn(अगरp->vअगर,
					brcmf_map_fw_linkकरोwn_reason(e),
					e->event_code &
					(BRCMF_E_DEAUTH_IND |
					BRCMF_E_DISASSOC_IND)
					? false : true);
			brcmf_init_prof(ndev_to_prof(ndev));
			अगर (ndev != cfg_to_ndev(cfg))
				complete(&cfg->vअगर_disabled);
			brcmf_net_setcarrier(अगरp, false);
		पूर्ण
	पूर्ण अन्यथा अगर (brcmf_is_nonetwork(cfg, e)) अणु
		अगर (brcmf_is_ibssmode(अगरp->vअगर))
			clear_bit(BRCMF_VIF_STATUS_CONNECTING,
				  &अगरp->vअगर->sme_state);
		अन्यथा
			brcmf_bss_connect_करोne(cfg, ndev, e, false);
	पूर्ण

	वापस err;
पूर्ण

अटल s32
brcmf_notअगरy_roaming_status(काष्ठा brcmf_अगर *अगरp,
			    स्थिर काष्ठा brcmf_event_msg *e, व्योम *data)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = अगरp->drvr->config;
	u32 event = e->event_code;
	u32 status = e->status;

	अगर (event == BRCMF_E_ROAM && status == BRCMF_E_STATUS_SUCCESS) अणु
		अगर (test_bit(BRCMF_VIF_STATUS_CONNECTED,
			     &अगरp->vअगर->sme_state)) अणु
			brcmf_bss_roaming_करोne(cfg, अगरp->ndev, e);
		पूर्ण अन्यथा अणु
			brcmf_bss_connect_करोne(cfg, अगरp->ndev, e, true);
			brcmf_net_setcarrier(अगरp, true);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल s32
brcmf_notअगरy_mic_status(काष्ठा brcmf_अगर *अगरp,
			स्थिर काष्ठा brcmf_event_msg *e, व्योम *data)
अणु
	u16 flags = e->flags;
	क्रमागत nl80211_key_type key_type;

	अगर (flags & BRCMF_EVENT_MSG_GROUP)
		key_type = NL80211_KEYTYPE_GROUP;
	अन्यथा
		key_type = NL80211_KEYTYPE_PAIRWISE;

	cfg80211_michael_mic_failure(अगरp->ndev, (u8 *)&e->addr, key_type, -1,
				     शून्य, GFP_KERNEL);

	वापस 0;
पूर्ण

अटल s32 brcmf_notअगरy_rssi(काष्ठा brcmf_अगर *अगरp,
			     स्थिर काष्ठा brcmf_event_msg *e, व्योम *data)
अणु
	काष्ठा brcmf_cfg80211_vअगर *vअगर = अगरp->vअगर;
	काष्ठा brcmf_rssi_be *info = data;
	s32 rssi, snr, noise;
	s32 low, high, last;

	अगर (e->datalen < माप(*info)) अणु
		brcmf_err("insufficient RSSI event data\n");
		वापस 0;
	पूर्ण

	rssi = be32_to_cpu(info->rssi);
	snr = be32_to_cpu(info->snr);
	noise = be32_to_cpu(info->noise);

	low = vअगर->cqm_rssi_low;
	high = vअगर->cqm_rssi_high;
	last = vअगर->cqm_rssi_last;

	brcmf_dbg(TRACE, "rssi=%d snr=%d noise=%d low=%d high=%d last=%d\n",
		  rssi, snr, noise, low, high, last);

	vअगर->cqm_rssi_last = rssi;

	अगर (rssi <= low || rssi == 0) अणु
		brcmf_dbg(INFO, "LOW rssi=%d\n", rssi);
		cfg80211_cqm_rssi_notअगरy(अगरp->ndev,
					 NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW,
					 rssi, GFP_KERNEL);
	पूर्ण अन्यथा अगर (rssi > high) अणु
		brcmf_dbg(INFO, "HIGH rssi=%d\n", rssi);
		cfg80211_cqm_rssi_notअगरy(अगरp->ndev,
					 NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH,
					 rssi, GFP_KERNEL);
	पूर्ण

	वापस 0;
पूर्ण

अटल s32 brcmf_notअगरy_vअगर_event(काष्ठा brcmf_अगर *अगरp,
				  स्थिर काष्ठा brcmf_event_msg *e, व्योम *data)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = अगरp->drvr->config;
	काष्ठा brcmf_अगर_event *अगरevent = (काष्ठा brcmf_अगर_event *)data;
	काष्ठा brcmf_cfg80211_vअगर_event *event = &cfg->vअगर_event;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;

	brcmf_dbg(TRACE, "Enter: action %u flags %u ifidx %u bsscfgidx %u\n",
		  अगरevent->action, अगरevent->flags, अगरevent->अगरidx,
		  अगरevent->bsscfgidx);

	spin_lock(&event->vअगर_event_lock);
	event->action = अगरevent->action;
	vअगर = event->vअगर;

	चयन (अगरevent->action) अणु
	हाल BRCMF_E_IF_ADD:
		/* रुकोing process may have समयd out */
		अगर (!cfg->vअगर_event.vअगर) अणु
			spin_unlock(&event->vअगर_event_lock);
			वापस -EBADF;
		पूर्ण

		अगरp->vअगर = vअगर;
		vअगर->अगरp = अगरp;
		अगर (अगरp->ndev) अणु
			vअगर->wdev.netdev = अगरp->ndev;
			अगरp->ndev->ieee80211_ptr = &vअगर->wdev;
			SET_NETDEV_DEV(अगरp->ndev, wiphy_dev(cfg->wiphy));
		पूर्ण
		spin_unlock(&event->vअगर_event_lock);
		wake_up(&event->vअगर_wq);
		वापस 0;

	हाल BRCMF_E_IF_DEL:
		spin_unlock(&event->vअगर_event_lock);
		/* event may not be upon user request */
		अगर (brcmf_cfg80211_vअगर_event_armed(cfg))
			wake_up(&event->vअगर_wq);
		वापस 0;

	हाल BRCMF_E_IF_CHANGE:
		spin_unlock(&event->vअगर_event_lock);
		wake_up(&event->vअगर_wq);
		वापस 0;

	शेष:
		spin_unlock(&event->vअगर_event_lock);
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम brcmf_init_conf(काष्ठा brcmf_cfg80211_conf *conf)
अणु
	conf->frag_threshold = (u32)-1;
	conf->rts_threshold = (u32)-1;
	conf->retry_लघु = (u32)-1;
	conf->retry_दीर्घ = (u32)-1;
पूर्ण

अटल व्योम brcmf_रेजिस्टर_event_handlers(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_LINK,
			    brcmf_notअगरy_connect_status);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_DEAUTH_IND,
			    brcmf_notअगरy_connect_status);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_DEAUTH,
			    brcmf_notअगरy_connect_status);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_DISASSOC_IND,
			    brcmf_notअगरy_connect_status);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_ASSOC_IND,
			    brcmf_notअगरy_connect_status);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_REASSOC_IND,
			    brcmf_notअगरy_connect_status);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_ROAM,
			    brcmf_notअगरy_roaming_status);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_MIC_ERROR,
			    brcmf_notअगरy_mic_status);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_SET_SSID,
			    brcmf_notअगरy_connect_status);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_PFN_NET_FOUND,
			    brcmf_notअगरy_sched_scan_results);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_IF,
			    brcmf_notअगरy_vअगर_event);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_P2P_PROBEREQ_MSG,
			    brcmf_p2p_notअगरy_rx_mgmt_p2p_probereq);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_P2P_DISC_LISTEN_COMPLETE,
			    brcmf_p2p_notअगरy_listen_complete);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_ACTION_FRAME_RX,
			    brcmf_p2p_notअगरy_action_frame_rx);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_ACTION_FRAME_COMPLETE,
			    brcmf_p2p_notअगरy_action_tx_complete);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_ACTION_FRAME_OFF_CHAN_COMPLETE,
			    brcmf_p2p_notअगरy_action_tx_complete);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_PSK_SUP,
			    brcmf_notअगरy_connect_status);
	brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_RSSI, brcmf_notअगरy_rssi);
पूर्ण

अटल व्योम brcmf_deinit_priv_mem(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	kमुक्त(cfg->conf);
	cfg->conf = शून्य;
	kमुक्त(cfg->extra_buf);
	cfg->extra_buf = शून्य;
	kमुक्त(cfg->wowl.nd);
	cfg->wowl.nd = शून्य;
	kमुक्त(cfg->wowl.nd_info);
	cfg->wowl.nd_info = शून्य;
	kमुक्त(cfg->escan_info.escan_buf);
	cfg->escan_info.escan_buf = शून्य;
पूर्ण

अटल s32 brcmf_init_priv_mem(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	cfg->conf = kzalloc(माप(*cfg->conf), GFP_KERNEL);
	अगर (!cfg->conf)
		जाओ init_priv_mem_out;
	cfg->extra_buf = kzalloc(WL_EXTRA_BUF_MAX, GFP_KERNEL);
	अगर (!cfg->extra_buf)
		जाओ init_priv_mem_out;
	cfg->wowl.nd = kzalloc(माप(*cfg->wowl.nd) + माप(u32), GFP_KERNEL);
	अगर (!cfg->wowl.nd)
		जाओ init_priv_mem_out;
	cfg->wowl.nd_info = kzalloc(माप(*cfg->wowl.nd_info) +
				    माप(काष्ठा cfg80211_wowlan_nd_match *),
				    GFP_KERNEL);
	अगर (!cfg->wowl.nd_info)
		जाओ init_priv_mem_out;
	cfg->escan_info.escan_buf = kzalloc(BRCMF_ESCAN_BUF_SIZE, GFP_KERNEL);
	अगर (!cfg->escan_info.escan_buf)
		जाओ init_priv_mem_out;

	वापस 0;

init_priv_mem_out:
	brcmf_deinit_priv_mem(cfg);

	वापस -ENOMEM;
पूर्ण

अटल s32 wl_init_priv(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	s32 err = 0;

	cfg->scan_request = शून्य;
	cfg->pwr_save = true;
	cfg->करोngle_up = false;		/* करोngle is not up yet */
	err = brcmf_init_priv_mem(cfg);
	अगर (err)
		वापस err;
	brcmf_रेजिस्टर_event_handlers(cfg);
	mutex_init(&cfg->usr_sync);
	brcmf_init_escan(cfg);
	brcmf_init_conf(cfg->conf);
	brcmf_init_wmm_prio(cfg->ac_priority);
	init_completion(&cfg->vअगर_disabled);
	वापस err;
पूर्ण

अटल व्योम wl_deinit_priv(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	cfg->करोngle_up = false;	/* करोngle करोwn */
	brcmf_पात_scanning(cfg);
	brcmf_deinit_priv_mem(cfg);
पूर्ण

अटल व्योम init_vअगर_event(काष्ठा brcmf_cfg80211_vअगर_event *event)
अणु
	init_रुकोqueue_head(&event->vअगर_wq);
	spin_lock_init(&event->vअगर_event_lock);
पूर्ण

अटल s32 brcmf_करोngle_roam(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 err;
	u32 bcn_समयout;
	__le32 roamtrigger[2];
	__le32 roam_delta[2];

	/* Configure beacon समयout value based upon roaming setting */
	अगर (अगरp->drvr->settings->roamoff)
		bcn_समयout = BRCMF_DEFAULT_BCN_TIMEOUT_ROAM_OFF;
	अन्यथा
		bcn_समयout = BRCMF_DEFAULT_BCN_TIMEOUT_ROAM_ON;
	err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "bcn_timeout", bcn_समयout);
	अगर (err) अणु
		bphy_err(drvr, "bcn_timeout error (%d)\n", err);
		जाओ roam_setup_करोne;
	पूर्ण

	/* Enable/Disable built-in roaming to allow supplicant to take care of
	 * roaming.
	 */
	brcmf_dbg(INFO, "Internal Roaming = %s\n",
		  अगरp->drvr->settings->roamoff ? "Off" : "On");
	err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "roam_off",
				      अगरp->drvr->settings->roamoff);
	अगर (err) अणु
		bphy_err(drvr, "roam_off error (%d)\n", err);
		जाओ roam_setup_करोne;
	पूर्ण

	roamtrigger[0] = cpu_to_le32(WL_ROAM_TRIGGER_LEVEL);
	roamtrigger[1] = cpu_to_le32(BRCM_BAND_ALL);
	err = brcmf_fil_cmd_data_set(अगरp, BRCMF_C_SET_ROAM_TRIGGER,
				     (व्योम *)roamtrigger, माप(roamtrigger));
	अगर (err)
		bphy_err(drvr, "WLC_SET_ROAM_TRIGGER error (%d)\n", err);

	roam_delta[0] = cpu_to_le32(WL_ROAM_DELTA);
	roam_delta[1] = cpu_to_le32(BRCM_BAND_ALL);
	err = brcmf_fil_cmd_data_set(अगरp, BRCMF_C_SET_ROAM_DELTA,
				     (व्योम *)roam_delta, माप(roam_delta));
	अगर (err)
		bphy_err(drvr, "WLC_SET_ROAM_DELTA error (%d)\n", err);

	वापस 0;

roam_setup_करोne:
	वापस err;
पूर्ण

अटल s32
brcmf_करोngle_scanसमय(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 err = 0;

	err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_SCAN_CHANNEL_TIME,
				    BRCMF_SCAN_CHANNEL_TIME);
	अगर (err) अणु
		bphy_err(drvr, "Scan assoc time error (%d)\n", err);
		जाओ करोngle_scanसमय_out;
	पूर्ण
	err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_SCAN_UNASSOC_TIME,
				    BRCMF_SCAN_UNASSOC_TIME);
	अगर (err) अणु
		bphy_err(drvr, "Scan unassoc time error (%d)\n", err);
		जाओ करोngle_scanसमय_out;
	पूर्ण

	err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_SCAN_PASSIVE_TIME,
				    BRCMF_SCAN_PASSIVE_TIME);
	अगर (err) अणु
		bphy_err(drvr, "Scan passive time error (%d)\n", err);
		जाओ करोngle_scanसमय_out;
	पूर्ण

करोngle_scanसमय_out:
	वापस err;
पूर्ण

अटल व्योम brcmf_update_bw40_channel_flag(काष्ठा ieee80211_channel *channel,
					   काष्ठा brcmu_chan *ch)
अणु
	u32 ht40_flag;

	ht40_flag = channel->flags & IEEE80211_CHAN_NO_HT40;
	अगर (ch->sb == BRCMU_CHAN_SB_U) अणु
		अगर (ht40_flag == IEEE80211_CHAN_NO_HT40)
			channel->flags &= ~IEEE80211_CHAN_NO_HT40;
		channel->flags |= IEEE80211_CHAN_NO_HT40PLUS;
	पूर्ण अन्यथा अणु
		/* It should be one of
		 * IEEE80211_CHAN_NO_HT40 or
		 * IEEE80211_CHAN_NO_HT40PLUS
		 */
		channel->flags &= ~IEEE80211_CHAN_NO_HT40;
		अगर (ht40_flag == IEEE80211_CHAN_NO_HT40)
			channel->flags |= IEEE80211_CHAN_NO_HT40MINUS;
	पूर्ण
पूर्ण

अटल पूर्णांक brcmf_स्थिरruct_chaninfo(काष्ठा brcmf_cfg80211_info *cfg,
				    u32 bw_cap[])
अणु
	काष्ठा wiphy *wiphy = cfg_to_wiphy(cfg);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_अगर *अगरp = brcmf_get_अगरp(drvr, 0);
	काष्ठा ieee80211_supported_band *band;
	काष्ठा ieee80211_channel *channel;
	काष्ठा brcmf_chanspec_list *list;
	काष्ठा brcmu_chan ch;
	पूर्णांक err;
	u8 *pbuf;
	u32 i, j;
	u32 total;
	u32 chaninfo;

	pbuf = kzalloc(BRCMF_DCMD_MEDLEN, GFP_KERNEL);

	अगर (pbuf == शून्य)
		वापस -ENOMEM;

	list = (काष्ठा brcmf_chanspec_list *)pbuf;

	err = brcmf_fil_iovar_data_get(अगरp, "chanspecs", pbuf,
				       BRCMF_DCMD_MEDLEN);
	अगर (err) अणु
		bphy_err(drvr, "get chanspecs error (%d)\n", err);
		जाओ fail_pbuf;
	पूर्ण

	band = wiphy->bands[NL80211_BAND_2GHZ];
	अगर (band)
		क्रम (i = 0; i < band->n_channels; i++)
			band->channels[i].flags = IEEE80211_CHAN_DISABLED;
	band = wiphy->bands[NL80211_BAND_5GHZ];
	अगर (band)
		क्रम (i = 0; i < band->n_channels; i++)
			band->channels[i].flags = IEEE80211_CHAN_DISABLED;

	total = le32_to_cpu(list->count);
	क्रम (i = 0; i < total; i++) अणु
		ch.chspec = (u16)le32_to_cpu(list->element[i]);
		cfg->d11inf.decchspec(&ch);

		अगर (ch.band == BRCMU_CHAN_BAND_2G) अणु
			band = wiphy->bands[NL80211_BAND_2GHZ];
		पूर्ण अन्यथा अगर (ch.band == BRCMU_CHAN_BAND_5G) अणु
			band = wiphy->bands[NL80211_BAND_5GHZ];
		पूर्ण अन्यथा अणु
			bphy_err(drvr, "Invalid channel Spec. 0x%x.\n",
				 ch.chspec);
			जारी;
		पूर्ण
		अगर (!band)
			जारी;
		अगर (!(bw_cap[band->band] & WLC_BW_40MHZ_BIT) &&
		    ch.bw == BRCMU_CHAN_BW_40)
			जारी;
		अगर (!(bw_cap[band->band] & WLC_BW_80MHZ_BIT) &&
		    ch.bw == BRCMU_CHAN_BW_80)
			जारी;

		channel = शून्य;
		क्रम (j = 0; j < band->n_channels; j++) अणु
			अगर (band->channels[j].hw_value == ch.control_ch_num) अणु
				channel = &band->channels[j];
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!channel) अणु
			/* It seems firmware supports some channel we never
			 * considered. Something new in IEEE standard?
			 */
			bphy_err(drvr, "Ignoring unexpected firmware channel %d\n",
				 ch.control_ch_num);
			जारी;
		पूर्ण

		अगर (channel->orig_flags & IEEE80211_CHAN_DISABLED)
			जारी;

		/* assuming the chanspecs order is HT20,
		 * HT40 upper, HT40 lower, and VHT80.
		 */
		चयन (ch.bw) अणु
		हाल BRCMU_CHAN_BW_160:
			channel->flags &= ~IEEE80211_CHAN_NO_160MHZ;
			अवरोध;
		हाल BRCMU_CHAN_BW_80:
			channel->flags &= ~IEEE80211_CHAN_NO_80MHZ;
			अवरोध;
		हाल BRCMU_CHAN_BW_40:
			brcmf_update_bw40_channel_flag(channel, &ch);
			अवरोध;
		शेष:
			wiphy_warn(wiphy, "Firmware reported unsupported bandwidth %d\n",
				   ch.bw);
			fallthrough;
		हाल BRCMU_CHAN_BW_20:
			/* enable the channel and disable other bandwidths
			 * क्रम now as mentioned order assure they are enabled
			 * क्रम subsequent chanspecs.
			 */
			channel->flags = IEEE80211_CHAN_NO_HT40 |
					 IEEE80211_CHAN_NO_80MHZ |
					 IEEE80211_CHAN_NO_160MHZ;
			ch.bw = BRCMU_CHAN_BW_20;
			cfg->d11inf.encchspec(&ch);
			chaninfo = ch.chspec;
			err = brcmf_fil_bsscfg_पूर्णांक_get(अगरp, "per_chan_info",
						       &chaninfo);
			अगर (!err) अणु
				अगर (chaninfo & WL_CHAN_RADAR)
					channel->flags |=
						(IEEE80211_CHAN_RADAR |
						 IEEE80211_CHAN_NO_IR);
				अगर (chaninfo & WL_CHAN_PASSIVE)
					channel->flags |=
						IEEE80211_CHAN_NO_IR;
			पूर्ण
		पूर्ण
	पूर्ण

fail_pbuf:
	kमुक्त(pbuf);
	वापस err;
पूर्ण

अटल पूर्णांक brcmf_enable_bw40_2g(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_अगर *अगरp = brcmf_get_अगरp(drvr, 0);
	काष्ठा ieee80211_supported_band *band;
	काष्ठा brcmf_fil_bwcap_le band_bwcap;
	काष्ठा brcmf_chanspec_list *list;
	u8 *pbuf;
	u32 val;
	पूर्णांक err;
	काष्ठा brcmu_chan ch;
	u32 num_chan;
	पूर्णांक i, j;

	/* verअगरy support क्रम bw_cap command */
	val = WLC_BAND_5G;
	err = brcmf_fil_iovar_पूर्णांक_get(अगरp, "bw_cap", &val);

	अगर (!err) अणु
		/* only set 2G bandwidth using bw_cap command */
		band_bwcap.band = cpu_to_le32(WLC_BAND_2G);
		band_bwcap.bw_cap = cpu_to_le32(WLC_BW_CAP_40MHZ);
		err = brcmf_fil_iovar_data_set(अगरp, "bw_cap", &band_bwcap,
					       माप(band_bwcap));
	पूर्ण अन्यथा अणु
		brcmf_dbg(INFO, "fallback to mimo_bw_cap\n");
		val = WLC_N_BW_40ALL;
		err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "mimo_bw_cap", val);
	पूर्ण

	अगर (!err) अणु
		/* update channel info in 2G band */
		pbuf = kzalloc(BRCMF_DCMD_MEDLEN, GFP_KERNEL);

		अगर (pbuf == शून्य)
			वापस -ENOMEM;

		ch.band = BRCMU_CHAN_BAND_2G;
		ch.bw = BRCMU_CHAN_BW_40;
		ch.sb = BRCMU_CHAN_SB_NONE;
		ch.chnum = 0;
		cfg->d11inf.encchspec(&ch);

		/* pass encoded chanspec in query */
		*(__le16 *)pbuf = cpu_to_le16(ch.chspec);

		err = brcmf_fil_iovar_data_get(अगरp, "chanspecs", pbuf,
					       BRCMF_DCMD_MEDLEN);
		अगर (err) अणु
			bphy_err(drvr, "get chanspecs error (%d)\n", err);
			kमुक्त(pbuf);
			वापस err;
		पूर्ण

		band = cfg_to_wiphy(cfg)->bands[NL80211_BAND_2GHZ];
		list = (काष्ठा brcmf_chanspec_list *)pbuf;
		num_chan = le32_to_cpu(list->count);
		क्रम (i = 0; i < num_chan; i++) अणु
			ch.chspec = (u16)le32_to_cpu(list->element[i]);
			cfg->d11inf.decchspec(&ch);
			अगर (WARN_ON(ch.band != BRCMU_CHAN_BAND_2G))
				जारी;
			अगर (WARN_ON(ch.bw != BRCMU_CHAN_BW_40))
				जारी;
			क्रम (j = 0; j < band->n_channels; j++) अणु
				अगर (band->channels[j].hw_value == ch.control_ch_num)
					अवरोध;
			पूर्ण
			अगर (WARN_ON(j == band->n_channels))
				जारी;

			brcmf_update_bw40_channel_flag(&band->channels[j], &ch);
		पूर्ण
		kमुक्त(pbuf);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम brcmf_get_bwcap(काष्ठा brcmf_अगर *अगरp, u32 bw_cap[])
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	u32 band, mimo_bwcap;
	पूर्णांक err;

	band = WLC_BAND_2G;
	err = brcmf_fil_iovar_पूर्णांक_get(अगरp, "bw_cap", &band);
	अगर (!err) अणु
		bw_cap[NL80211_BAND_2GHZ] = band;
		band = WLC_BAND_5G;
		err = brcmf_fil_iovar_पूर्णांक_get(अगरp, "bw_cap", &band);
		अगर (!err) अणु
			bw_cap[NL80211_BAND_5GHZ] = band;
			वापस;
		पूर्ण
		WARN_ON(1);
		वापस;
	पूर्ण
	brcmf_dbg(INFO, "fallback to mimo_bw_cap info\n");
	mimo_bwcap = 0;
	err = brcmf_fil_iovar_पूर्णांक_get(अगरp, "mimo_bw_cap", &mimo_bwcap);
	अगर (err)
		/* assume 20MHz अगर firmware करोes not give a clue */
		mimo_bwcap = WLC_N_BW_20ALL;

	चयन (mimo_bwcap) अणु
	हाल WLC_N_BW_40ALL:
		bw_cap[NL80211_BAND_2GHZ] |= WLC_BW_40MHZ_BIT;
		fallthrough;
	हाल WLC_N_BW_20IN2G_40IN5G:
		bw_cap[NL80211_BAND_5GHZ] |= WLC_BW_40MHZ_BIT;
		fallthrough;
	हाल WLC_N_BW_20ALL:
		bw_cap[NL80211_BAND_2GHZ] |= WLC_BW_20MHZ_BIT;
		bw_cap[NL80211_BAND_5GHZ] |= WLC_BW_20MHZ_BIT;
		अवरोध;
	शेष:
		bphy_err(drvr, "invalid mimo_bw_cap value\n");
	पूर्ण
पूर्ण

अटल व्योम brcmf_update_ht_cap(काष्ठा ieee80211_supported_band *band,
				u32 bw_cap[2], u32 nchain)
अणु
	band->ht_cap.ht_supported = true;
	अगर (bw_cap[band->band] & WLC_BW_40MHZ_BIT) अणु
		band->ht_cap.cap |= IEEE80211_HT_CAP_SGI_40;
		band->ht_cap.cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
	पूर्ण
	band->ht_cap.cap |= IEEE80211_HT_CAP_SGI_20;
	band->ht_cap.cap |= IEEE80211_HT_CAP_DSSSCCK40;
	band->ht_cap.ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
	band->ht_cap.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16;
	स_रखो(band->ht_cap.mcs.rx_mask, 0xff, nchain);
	band->ht_cap.mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
पूर्ण

अटल __le16 brcmf_get_mcs_map(u32 nchain, क्रमागत ieee80211_vht_mcs_support supp)
अणु
	u16 mcs_map;
	पूर्णांक i;

	क्रम (i = 0, mcs_map = 0xFFFF; i < nchain; i++)
		mcs_map = (mcs_map << 2) | supp;

	वापस cpu_to_le16(mcs_map);
पूर्ण

अटल व्योम brcmf_update_vht_cap(काष्ठा ieee80211_supported_band *band,
				 u32 bw_cap[2], u32 nchain, u32 txstreams,
				 u32 txbf_bfe_cap, u32 txbf_bfr_cap)
अणु
	__le16 mcs_map;

	/* not allowed in 2.4G band */
	अगर (band->band == NL80211_BAND_2GHZ)
		वापस;

	band->vht_cap.vht_supported = true;
	/* 80MHz is mandatory */
	band->vht_cap.cap |= IEEE80211_VHT_CAP_SHORT_GI_80;
	अगर (bw_cap[band->band] & WLC_BW_160MHZ_BIT) अणु
		band->vht_cap.cap |= IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ;
		band->vht_cap.cap |= IEEE80211_VHT_CAP_SHORT_GI_160;
	पूर्ण
	/* all support 256-QAM */
	mcs_map = brcmf_get_mcs_map(nchain, IEEE80211_VHT_MCS_SUPPORT_0_9);
	band->vht_cap.vht_mcs.rx_mcs_map = mcs_map;
	band->vht_cap.vht_mcs.tx_mcs_map = mcs_map;

	/* Beamक्रमming support inक्रमmation */
	अगर (txbf_bfe_cap & BRCMF_TXBF_SU_BFE_CAP)
		band->vht_cap.cap |= IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE;
	अगर (txbf_bfe_cap & BRCMF_TXBF_MU_BFE_CAP)
		band->vht_cap.cap |= IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE;
	अगर (txbf_bfr_cap & BRCMF_TXBF_SU_BFR_CAP)
		band->vht_cap.cap |= IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE;
	अगर (txbf_bfr_cap & BRCMF_TXBF_MU_BFR_CAP)
		band->vht_cap.cap |= IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE;

	अगर ((txbf_bfe_cap || txbf_bfr_cap) && (txstreams > 1)) अणु
		band->vht_cap.cap |=
			(2 << IEEE80211_VHT_CAP_BEAMFORMEE_STS_SHIFT);
		band->vht_cap.cap |= ((txstreams - 1) <<
				IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT);
		band->vht_cap.cap |=
			IEEE80211_VHT_CAP_VHT_LINK_ADAPTATION_VHT_MRQ_MFB;
	पूर्ण
पूर्ण

अटल पूर्णांक brcmf_setup_wiphybands(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_अगर *अगरp = brcmf_get_अगरp(drvr, 0);
	काष्ठा wiphy *wiphy = cfg_to_wiphy(cfg);
	u32 nmode = 0;
	u32 vhपंचांगode = 0;
	u32 bw_cap[2] = अणु WLC_BW_20MHZ_BIT, WLC_BW_20MHZ_BIT पूर्ण;
	u32 rxchain;
	u32 nchain;
	पूर्णांक err;
	s32 i;
	काष्ठा ieee80211_supported_band *band;
	u32 txstreams = 0;
	u32 txbf_bfe_cap = 0;
	u32 txbf_bfr_cap = 0;

	(व्योम)brcmf_fil_iovar_पूर्णांक_get(अगरp, "vhtmode", &vhपंचांगode);
	err = brcmf_fil_iovar_पूर्णांक_get(अगरp, "nmode", &nmode);
	अगर (err) अणु
		bphy_err(drvr, "nmode error (%d)\n", err);
	पूर्ण अन्यथा अणु
		brcmf_get_bwcap(अगरp, bw_cap);
	पूर्ण
	brcmf_dbg(INFO, "nmode=%d, vhtmode=%d, bw_cap=(%d, %d)\n",
		  nmode, vhपंचांगode, bw_cap[NL80211_BAND_2GHZ],
		  bw_cap[NL80211_BAND_5GHZ]);

	err = brcmf_fil_iovar_पूर्णांक_get(अगरp, "rxchain", &rxchain);
	अगर (err) अणु
		bphy_err(drvr, "rxchain error (%d)\n", err);
		nchain = 1;
	पूर्ण अन्यथा अणु
		क्रम (nchain = 0; rxchain; nchain++)
			rxchain = rxchain & (rxchain - 1);
	पूर्ण
	brcmf_dbg(INFO, "nchain=%d\n", nchain);

	err = brcmf_स्थिरruct_chaninfo(cfg, bw_cap);
	अगर (err) अणु
		bphy_err(drvr, "brcmf_construct_chaninfo failed (%d)\n", err);
		वापस err;
	पूर्ण

	अगर (vhपंचांगode) अणु
		(व्योम)brcmf_fil_iovar_पूर्णांक_get(अगरp, "txstreams", &txstreams);
		(व्योम)brcmf_fil_iovar_पूर्णांक_get(अगरp, "txbf_bfe_cap",
					      &txbf_bfe_cap);
		(व्योम)brcmf_fil_iovar_पूर्णांक_get(अगरp, "txbf_bfr_cap",
					      &txbf_bfr_cap);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wiphy->bands); i++) अणु
		band = wiphy->bands[i];
		अगर (band == शून्य)
			जारी;

		अगर (nmode)
			brcmf_update_ht_cap(band, bw_cap, nchain);
		अगर (vhपंचांगode)
			brcmf_update_vht_cap(band, bw_cap, nchain, txstreams,
					     txbf_bfe_cap, txbf_bfr_cap);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee80211_txrx_stypes
brcmf_txrx_stypes[NUM_NL80211_IFTYPES] = अणु
	[NL80211_IFTYPE_STATION] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	पूर्ण,
	[NL80211_IFTYPE_P2P_CLIENT] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	पूर्ण,
	[NL80211_IFTYPE_P2P_GO] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ASSOC_REQ >> 4) |
		      BIT(IEEE80211_STYPE_REASSOC_REQ >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
		      BIT(IEEE80211_STYPE_DISASSOC >> 4) |
		      BIT(IEEE80211_STYPE_AUTH >> 4) |
		      BIT(IEEE80211_STYPE_DEAUTH >> 4) |
		      BIT(IEEE80211_STYPE_ACTION >> 4)
	पूर्ण,
	[NL80211_IFTYPE_P2P_DEVICE] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	पूर्ण,
	[NL80211_IFTYPE_AP] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ASSOC_REQ >> 4) |
		      BIT(IEEE80211_STYPE_REASSOC_REQ >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
		      BIT(IEEE80211_STYPE_DISASSOC >> 4) |
		      BIT(IEEE80211_STYPE_AUTH >> 4) |
		      BIT(IEEE80211_STYPE_DEAUTH >> 4) |
		      BIT(IEEE80211_STYPE_ACTION >> 4)
	पूर्ण
पूर्ण;

/**
 * brcmf_setup_अगरmodes() - determine पूर्णांकerface modes and combinations.
 *
 * @wiphy: wiphy object.
 * @अगरp: पूर्णांकerface object needed क्रम feat module api.
 *
 * The पूर्णांकerface modes and combinations are determined dynamically here
 * based on firmware functionality.
 *
 * no p2p and no mbss:
 *
 *	#STA <= 1, #AP <= 1, channels = 1, 2 total
 *
 * no p2p and mbss:
 *
 *	#STA <= 1, #AP <= 1, channels = 1, 2 total
 *	#AP <= 4, matching BI, channels = 1, 4 total
 *
 * no p2p and rsdb:
 *	#STA <= 1, #AP <= 2, channels = 2, 4 total
 *
 * p2p, no mchan, and mbss:
 *
 *	#STA <= 1, #P2P-DEV <= 1, #अणुP2P-CL, P2P-GOपूर्ण <= 1, channels = 1, 3 total
 *	#STA <= 1, #P2P-DEV <= 1, #AP <= 1, #P2P-CL <= 1, channels = 1, 4 total
 *	#AP <= 4, matching BI, channels = 1, 4 total
 *
 * p2p, mchan, and mbss:
 *
 *	#STA <= 1, #P2P-DEV <= 1, #अणुP2P-CL, P2P-GOपूर्ण <= 1, channels = 2, 3 total
 *	#STA <= 1, #P2P-DEV <= 1, #AP <= 1, #P2P-CL <= 1, channels = 1, 4 total
 *	#AP <= 4, matching BI, channels = 1, 4 total
 *
 * p2p, rsdb, and no mbss:
 *	#STA <= 1, #P2P-DEV <= 1, #अणुP2P-CL, P2P-GOपूर्ण <= 2, AP <= 2,
 *	 channels = 2, 4 total
 */
अटल पूर्णांक brcmf_setup_अगरmodes(काष्ठा wiphy *wiphy, काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा ieee80211_अगरace_combination *combo = शून्य;
	काष्ठा ieee80211_अगरace_limit *c0_limits = शून्य;
	काष्ठा ieee80211_अगरace_limit *p2p_limits = शून्य;
	काष्ठा ieee80211_अगरace_limit *mbss_limits = शून्य;
	bool mon_flag, mbss, p2p, rsdb, mchan;
	पूर्णांक i, c, n_combos, n_limits;

	mon_flag = brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_MONITOR_FLAG);
	mbss = brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_MBSS);
	p2p = brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_P2P);
	rsdb = brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_RSDB);
	mchan = brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_MCHAN);

	n_combos = 1 + !!(p2p && !rsdb) + !!mbss;
	combo = kसुस्मृति(n_combos, माप(*combo), GFP_KERNEL);
	अगर (!combo)
		जाओ err;

	wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
				 BIT(NL80211_IFTYPE_ADHOC) |
				 BIT(NL80211_IFTYPE_AP);
	अगर (mon_flag)
		wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_MONITOR);
	अगर (p2p)
		wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_P2P_CLIENT) |
					  BIT(NL80211_IFTYPE_P2P_GO) |
					  BIT(NL80211_IFTYPE_P2P_DEVICE);

	c = 0;
	i = 0;
	n_limits = 1 + mon_flag + (p2p ? 2 : 0) + (rsdb || !p2p);
	c0_limits = kसुस्मृति(n_limits, माप(*c0_limits), GFP_KERNEL);
	अगर (!c0_limits)
		जाओ err;

	combo[c].num_dअगरferent_channels = 1 + (rsdb || (p2p && mchan));
	c0_limits[i].max = 1;
	c0_limits[i++].types = BIT(NL80211_IFTYPE_STATION);
	अगर (mon_flag) अणु
		c0_limits[i].max = 1;
		c0_limits[i++].types = BIT(NL80211_IFTYPE_MONITOR);
	पूर्ण
	अगर (p2p) अणु
		c0_limits[i].max = 1;
		c0_limits[i++].types = BIT(NL80211_IFTYPE_P2P_DEVICE);
		c0_limits[i].max = 1 + rsdb;
		c0_limits[i++].types = BIT(NL80211_IFTYPE_P2P_CLIENT) |
				       BIT(NL80211_IFTYPE_P2P_GO);
	पूर्ण
	अगर (p2p && rsdb) अणु
		c0_limits[i].max = 2;
		c0_limits[i++].types = BIT(NL80211_IFTYPE_AP);
		combo[c].max_पूर्णांकerfaces = 4;
	पूर्ण अन्यथा अगर (p2p) अणु
		combo[c].max_पूर्णांकerfaces = i;
	पूर्ण अन्यथा अगर (rsdb) अणु
		c0_limits[i].max = 2;
		c0_limits[i++].types = BIT(NL80211_IFTYPE_AP);
		combo[c].max_पूर्णांकerfaces = 3;
	पूर्ण अन्यथा अणु
		c0_limits[i].max = 1;
		c0_limits[i++].types = BIT(NL80211_IFTYPE_AP);
		combo[c].max_पूर्णांकerfaces = i;
	पूर्ण
	combo[c].n_limits = i;
	combo[c].limits = c0_limits;

	अगर (p2p && !rsdb) अणु
		c++;
		i = 0;
		p2p_limits = kसुस्मृति(4, माप(*p2p_limits), GFP_KERNEL);
		अगर (!p2p_limits)
			जाओ err;
		p2p_limits[i].max = 1;
		p2p_limits[i++].types = BIT(NL80211_IFTYPE_STATION);
		p2p_limits[i].max = 1;
		p2p_limits[i++].types = BIT(NL80211_IFTYPE_AP);
		p2p_limits[i].max = 1;
		p2p_limits[i++].types = BIT(NL80211_IFTYPE_P2P_CLIENT);
		p2p_limits[i].max = 1;
		p2p_limits[i++].types = BIT(NL80211_IFTYPE_P2P_DEVICE);
		combo[c].num_dअगरferent_channels = 1;
		combo[c].max_पूर्णांकerfaces = i;
		combo[c].n_limits = i;
		combo[c].limits = p2p_limits;
	पूर्ण

	अगर (mbss) अणु
		c++;
		i = 0;
		n_limits = 1 + mon_flag;
		mbss_limits = kसुस्मृति(n_limits, माप(*mbss_limits),
				      GFP_KERNEL);
		अगर (!mbss_limits)
			जाओ err;
		mbss_limits[i].max = 4;
		mbss_limits[i++].types = BIT(NL80211_IFTYPE_AP);
		अगर (mon_flag) अणु
			mbss_limits[i].max = 1;
			mbss_limits[i++].types = BIT(NL80211_IFTYPE_MONITOR);
		पूर्ण
		combo[c].beacon_पूर्णांक_infra_match = true;
		combo[c].num_dअगरferent_channels = 1;
		combo[c].max_पूर्णांकerfaces = 4 + mon_flag;
		combo[c].n_limits = i;
		combo[c].limits = mbss_limits;
	पूर्ण

	wiphy->n_अगरace_combinations = n_combos;
	wiphy->अगरace_combinations = combo;
	वापस 0;

err:
	kमुक्त(c0_limits);
	kमुक्त(p2p_limits);
	kमुक्त(mbss_limits);
	kमुक्त(combo);
	वापस -ENOMEM;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल स्थिर काष्ठा wiphy_wowlan_support brcmf_wowlan_support = अणु
	.flags = WIPHY_WOWLAN_MAGIC_PKT | WIPHY_WOWLAN_DISCONNECT,
	.n_patterns = BRCMF_WOWL_MAXPATTERNS,
	.pattern_max_len = BRCMF_WOWL_MAXPATTERNSIZE,
	.pattern_min_len = 1,
	.max_pkt_offset = 1500,
पूर्ण;
#पूर्ण_अगर

अटल व्योम brcmf_wiphy_wowl_params(काष्ठा wiphy *wiphy, काष्ठा brcmf_अगर *अगरp)
अणु
#अगर_घोषित CONFIG_PM
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा wiphy_wowlan_support *wowl;

	wowl = kmemdup(&brcmf_wowlan_support, माप(brcmf_wowlan_support),
		       GFP_KERNEL);
	अगर (!wowl) अणु
		bphy_err(drvr, "only support basic wowlan features\n");
		wiphy->wowlan = &brcmf_wowlan_support;
		वापस;
	पूर्ण

	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_PNO)) अणु
		अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_WOWL_ND)) अणु
			wowl->flags |= WIPHY_WOWLAN_NET_DETECT;
			wowl->max_nd_match_sets = BRCMF_PNO_MAX_PFN_COUNT;
			init_रुकोqueue_head(&cfg->wowl.nd_data_रुको);
		पूर्ण
	पूर्ण
	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_WOWL_GTK)) अणु
		wowl->flags |= WIPHY_WOWLAN_SUPPORTS_GTK_REKEY;
		wowl->flags |= WIPHY_WOWLAN_GTK_REKEY_FAILURE;
	पूर्ण

	wiphy->wowlan = wowl;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक brcmf_setup_wiphy(काष्ठा wiphy *wiphy, काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	स्थिर काष्ठा ieee80211_अगरace_combination *combo;
	काष्ठा ieee80211_supported_band *band;
	u16 max_पूर्णांकerfaces = 0;
	bool gscan;
	__le32 bandlist[3];
	u32 n_bands;
	पूर्णांक err, i;

	wiphy->max_scan_ssids = WL_NUM_SCAN_MAX;
	wiphy->max_scan_ie_len = BRCMF_SCAN_IE_LEN_MAX;
	wiphy->max_num_pmkids = BRCMF_MAXPMKID;

	err = brcmf_setup_अगरmodes(wiphy, अगरp);
	अगर (err)
		वापस err;

	क्रम (i = 0, combo = wiphy->अगरace_combinations;
	     i < wiphy->n_अगरace_combinations; i++, combo++) अणु
		max_पूर्णांकerfaces = max(max_पूर्णांकerfaces, combo->max_पूर्णांकerfaces);
	पूर्ण

	क्रम (i = 0; i < max_पूर्णांकerfaces && i < ARRAY_SIZE(drvr->addresses);
	     i++) अणु
		u8 *addr = drvr->addresses[i].addr;

		स_नकल(addr, drvr->mac, ETH_ALEN);
		अगर (i) अणु
			addr[0] |= BIT(1);
			addr[ETH_ALEN - 1] ^= i;
		पूर्ण
	पूर्ण
	wiphy->addresses = drvr->addresses;
	wiphy->n_addresses = i;

	wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_MBM;
	wiphy->cipher_suites = brcmf_cipher_suites;
	wiphy->n_cipher_suites = ARRAY_SIZE(brcmf_cipher_suites);
	अगर (!brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_MFP))
		wiphy->n_cipher_suites--;
	wiphy->bss_select_support = BIT(NL80211_BSS_SELECT_ATTR_RSSI) |
				    BIT(NL80211_BSS_SELECT_ATTR_BAND_PREF) |
				    BIT(NL80211_BSS_SELECT_ATTR_RSSI_ADJUST);

	wiphy->flags |= WIPHY_FLAG_NETNS_OK |
			WIPHY_FLAG_PS_ON_BY_DEFAULT |
			WIPHY_FLAG_HAVE_AP_SME |
			WIPHY_FLAG_OFFCHAN_TX |
			WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;
	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_TDLS))
		wiphy->flags |= WIPHY_FLAG_SUPPORTS_TDLS;
	अगर (!अगरp->drvr->settings->roamoff)
		wiphy->flags |= WIPHY_FLAG_SUPPORTS_FW_ROAM;
	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_FWSUP)) अणु
		wiphy_ext_feature_set(wiphy,
				      NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_PSK);
		wiphy_ext_feature_set(wiphy,
				      NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_1X);
		अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_SAE))
			wiphy_ext_feature_set(wiphy,
					      NL80211_EXT_FEATURE_SAE_OFFLOAD);
	पूर्ण
	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_FWAUTH)) अणु
		wiphy_ext_feature_set(wiphy,
				      NL80211_EXT_FEATURE_4WAY_HANDSHAKE_AP_PSK);
		अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_SAE))
			wiphy_ext_feature_set(wiphy,
					      NL80211_EXT_FEATURE_SAE_OFFLOAD_AP);
	पूर्ण
	wiphy->mgmt_stypes = brcmf_txrx_stypes;
	wiphy->max_reमुख्य_on_channel_duration = 5000;
	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_PNO)) अणु
		gscan = brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_GSCAN);
		brcmf_pno_wiphy_params(wiphy, gscan);
	पूर्ण
	/* venकरोr commands/events support */
	wiphy->venकरोr_commands = brcmf_venकरोr_cmds;
	wiphy->n_venकरोr_commands = BRCMF_VNDR_CMDS_LAST - 1;

	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_WOWL))
		brcmf_wiphy_wowl_params(wiphy, अगरp);
	err = brcmf_fil_cmd_data_get(अगरp, BRCMF_C_GET_BANDLIST, &bandlist,
				     माप(bandlist));
	अगर (err) अणु
		bphy_err(drvr, "could not obtain band info: err=%d\n", err);
		वापस err;
	पूर्ण
	/* first entry in bandlist is number of bands */
	n_bands = le32_to_cpu(bandlist[0]);
	क्रम (i = 1; i <= n_bands && i < ARRAY_SIZE(bandlist); i++) अणु
		अगर (bandlist[i] == cpu_to_le32(WLC_BAND_2G)) अणु
			band = kmemdup(&__wl_band_2ghz, माप(__wl_band_2ghz),
				       GFP_KERNEL);
			अगर (!band)
				वापस -ENOMEM;

			band->channels = kmemdup(&__wl_2ghz_channels,
						 माप(__wl_2ghz_channels),
						 GFP_KERNEL);
			अगर (!band->channels) अणु
				kमुक्त(band);
				वापस -ENOMEM;
			पूर्ण

			band->n_channels = ARRAY_SIZE(__wl_2ghz_channels);
			wiphy->bands[NL80211_BAND_2GHZ] = band;
		पूर्ण
		अगर (bandlist[i] == cpu_to_le32(WLC_BAND_5G)) अणु
			band = kmemdup(&__wl_band_5ghz, माप(__wl_band_5ghz),
				       GFP_KERNEL);
			अगर (!band)
				वापस -ENOMEM;

			band->channels = kmemdup(&__wl_5ghz_channels,
						 माप(__wl_5ghz_channels),
						 GFP_KERNEL);
			अगर (!band->channels) अणु
				kमुक्त(band);
				वापस -ENOMEM;
			पूर्ण

			band->n_channels = ARRAY_SIZE(__wl_5ghz_channels);
			wiphy->bands[NL80211_BAND_5GHZ] = band;
		पूर्ण
	पूर्ण

	अगर (wiphy->bands[NL80211_BAND_5GHZ] &&
	    brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_DOT11H))
		wiphy_ext_feature_set(wiphy,
				      NL80211_EXT_FEATURE_DFS_OFFLOAD);

	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	wiphy_पढ़ो_of_freq_limits(wiphy);

	वापस 0;
पूर्ण

अटल s32 brcmf_config_करोngle(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा net_device *ndev;
	काष्ठा wireless_dev *wdev;
	काष्ठा brcmf_अगर *अगरp;
	s32 घातer_mode;
	s32 err = 0;

	अगर (cfg->करोngle_up)
		वापस err;

	ndev = cfg_to_ndev(cfg);
	wdev = ndev->ieee80211_ptr;
	अगरp = netdev_priv(ndev);

	/* make sure RF is पढ़ोy क्रम work */
	brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_UP, 0);

	brcmf_करोngle_scanसमय(अगरp);

	घातer_mode = cfg->pwr_save ? PM_FAST : PM_OFF;
	err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_PM, घातer_mode);
	अगर (err)
		जाओ शेष_conf_out;
	brcmf_dbg(INFO, "power save set to %s\n",
		  (घातer_mode ? "enabled" : "disabled"));

	err = brcmf_करोngle_roam(अगरp);
	अगर (err)
		जाओ शेष_conf_out;
	err = brcmf_cfg80211_change_अगरace(wdev->wiphy, ndev, wdev->अगरtype,
					  शून्य);
	अगर (err)
		जाओ शेष_conf_out;

	brcmf_configure_arp_nd_offload(अगरp, true);

	err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_FAKEFRAG, 1);
	अगर (err) अणु
		bphy_err(drvr, "failed to set frameburst mode\n");
		जाओ शेष_conf_out;
	पूर्ण

	cfg->करोngle_up = true;
शेष_conf_out:

	वापस err;

पूर्ण

अटल s32 __brcmf_cfg80211_up(काष्ठा brcmf_अगर *अगरp)
अणु
	set_bit(BRCMF_VIF_STATUS_READY, &अगरp->vअगर->sme_state);

	वापस brcmf_config_करोngle(अगरp->drvr->config);
पूर्ण

अटल s32 __brcmf_cfg80211_करोwn(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = अगरp->drvr->config;

	/*
	 * While going करोwn, अगर associated with AP disassociate
	 * from AP to save घातer
	 */
	अगर (check_vअगर_up(अगरp->vअगर)) अणु
		brcmf_link_करोwn(अगरp->vअगर, WLAN_REASON_UNSPECIFIED, true);

		/* Make sure WPA_Supplicant receives all the event
		   generated due to DISASSOC call to the fw to keep
		   the state fw and WPA_Supplicant state consistent
		 */
		brcmf_delay(500);
	पूर्ण

	brcmf_पात_scanning(cfg);
	clear_bit(BRCMF_VIF_STATUS_READY, &अगरp->vअगर->sme_state);

	वापस 0;
पूर्ण

s32 brcmf_cfg80211_up(काष्ठा net_device *ndev)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_cfg80211_info *cfg = अगरp->drvr->config;
	s32 err = 0;

	mutex_lock(&cfg->usr_sync);
	err = __brcmf_cfg80211_up(अगरp);
	mutex_unlock(&cfg->usr_sync);

	वापस err;
पूर्ण

s32 brcmf_cfg80211_करोwn(काष्ठा net_device *ndev)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_cfg80211_info *cfg = अगरp->drvr->config;
	s32 err = 0;

	mutex_lock(&cfg->usr_sync);
	err = __brcmf_cfg80211_करोwn(अगरp);
	mutex_unlock(&cfg->usr_sync);

	वापस err;
पूर्ण

क्रमागत nl80211_अगरtype brcmf_cfg80211_get_अगरtype(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा wireless_dev *wdev = &अगरp->vअगर->wdev;

	वापस wdev->अगरtype;
पूर्ण

bool brcmf_get_vअगर_state_any(काष्ठा brcmf_cfg80211_info *cfg,
			     अचिन्हित दीर्घ state)
अणु
	काष्ठा brcmf_cfg80211_vअगर *vअगर;

	list_क्रम_each_entry(vअगर, &cfg->vअगर_list, list) अणु
		अगर (test_bit(state, &vअगर->sme_state))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत bool vअगर_event_equals(काष्ठा brcmf_cfg80211_vअगर_event *event,
				    u8 action)
अणु
	u8 evt_action;

	spin_lock(&event->vअगर_event_lock);
	evt_action = event->action;
	spin_unlock(&event->vअगर_event_lock);
	वापस evt_action == action;
पूर्ण

व्योम brcmf_cfg80211_arm_vअगर_event(काष्ठा brcmf_cfg80211_info *cfg,
				  काष्ठा brcmf_cfg80211_vअगर *vअगर)
अणु
	काष्ठा brcmf_cfg80211_vअगर_event *event = &cfg->vअगर_event;

	spin_lock(&event->vअगर_event_lock);
	event->vअगर = vअगर;
	event->action = 0;
	spin_unlock(&event->vअगर_event_lock);
पूर्ण

bool brcmf_cfg80211_vअगर_event_armed(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	काष्ठा brcmf_cfg80211_vअगर_event *event = &cfg->vअगर_event;
	bool armed;

	spin_lock(&event->vअगर_event_lock);
	armed = event->vअगर != शून्य;
	spin_unlock(&event->vअगर_event_lock);

	वापस armed;
पूर्ण

पूर्णांक brcmf_cfg80211_रुको_vअगर_event(काष्ठा brcmf_cfg80211_info *cfg,
				  u8 action, uदीर्घ समयout)
अणु
	काष्ठा brcmf_cfg80211_vअगर_event *event = &cfg->vअगर_event;

	वापस रुको_event_समयout(event->vअगर_wq,
				  vअगर_event_equals(event, action), समयout);
पूर्ण

अटल s32 brcmf_translate_country_code(काष्ठा brcmf_pub *drvr, अक्षर alpha2[2],
					काष्ठा brcmf_fil_country_le *ccreq)
अणु
	काष्ठा brcmfmac_pd_cc *country_codes;
	काष्ठा brcmfmac_pd_cc_entry *cc;
	s32 found_index;
	पूर्णांक i;

	country_codes = drvr->settings->country_codes;
	अगर (!country_codes) अणु
		brcmf_dbg(TRACE, "No country codes configured for device\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((alpha2[0] == ccreq->country_abbrev[0]) &&
	    (alpha2[1] == ccreq->country_abbrev[1])) अणु
		brcmf_dbg(TRACE, "Country code already set\n");
		वापस -EAGAIN;
	पूर्ण

	found_index = -1;
	क्रम (i = 0; i < country_codes->table_size; i++) अणु
		cc = &country_codes->table[i];
		अगर ((cc->iso3166[0] == '\0') && (found_index == -1))
			found_index = i;
		अगर ((cc->iso3166[0] == alpha2[0]) &&
		    (cc->iso3166[1] == alpha2[1])) अणु
			found_index = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (found_index == -1) अणु
		brcmf_dbg(TRACE, "No country code match found\n");
		वापस -EINVAL;
	पूर्ण
	स_रखो(ccreq, 0, माप(*ccreq));
	ccreq->rev = cpu_to_le32(country_codes->table[found_index].rev);
	स_नकल(ccreq->ccode, country_codes->table[found_index].cc,
	       BRCMF_COUNTRY_BUF_SZ);
	ccreq->country_abbrev[0] = alpha2[0];
	ccreq->country_abbrev[1] = alpha2[1];
	ccreq->country_abbrev[2] = 0;

	वापस 0;
पूर्ण

अटल व्योम brcmf_cfg80211_reg_notअगरier(काष्ठा wiphy *wiphy,
					काष्ठा regulatory_request *req)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	काष्ठा brcmf_अगर *अगरp = brcmf_get_अगरp(cfg->pub, 0);
	काष्ठा brcmf_pub *drvr = cfg->pub;
	काष्ठा brcmf_fil_country_le ccreq;
	s32 err;
	पूर्णांक i;

	/* The country code माला_लो set to "00" by शेष at boot, ignore */
	अगर (req->alpha2[0] == '0' && req->alpha2[1] == '0')
		वापस;

	/* ignore non-ISO3166 country codes */
	क्रम (i = 0; i < 2; i++)
		अगर (req->alpha2[i] < 'A' || req->alpha2[i] > 'Z') अणु
			bphy_err(drvr, "not an ISO3166 code (0x%02x 0x%02x)\n",
				 req->alpha2[0], req->alpha2[1]);
			वापस;
		पूर्ण

	brcmf_dbg(TRACE, "Enter: initiator=%d, alpha=%c%c\n", req->initiator,
		  req->alpha2[0], req->alpha2[1]);

	err = brcmf_fil_iovar_data_get(अगरp, "country", &ccreq, माप(ccreq));
	अगर (err) अणु
		bphy_err(drvr, "Country code iovar returned err = %d\n", err);
		वापस;
	पूर्ण

	err = brcmf_translate_country_code(अगरp->drvr, req->alpha2, &ccreq);
	अगर (err)
		वापस;

	err = brcmf_fil_iovar_data_set(अगरp, "country", &ccreq, माप(ccreq));
	अगर (err) अणु
		bphy_err(drvr, "Firmware rejected country setting\n");
		वापस;
	पूर्ण
	brcmf_setup_wiphybands(cfg);
पूर्ण

अटल व्योम brcmf_मुक्त_wiphy(काष्ठा wiphy *wiphy)
अणु
	पूर्णांक i;

	अगर (!wiphy)
		वापस;

	अगर (wiphy->अगरace_combinations) अणु
		क्रम (i = 0; i < wiphy->n_अगरace_combinations; i++)
			kमुक्त(wiphy->अगरace_combinations[i].limits);
	पूर्ण
	kमुक्त(wiphy->अगरace_combinations);
	अगर (wiphy->bands[NL80211_BAND_2GHZ]) अणु
		kमुक्त(wiphy->bands[NL80211_BAND_2GHZ]->channels);
		kमुक्त(wiphy->bands[NL80211_BAND_2GHZ]);
	पूर्ण
	अगर (wiphy->bands[NL80211_BAND_5GHZ]) अणु
		kमुक्त(wiphy->bands[NL80211_BAND_5GHZ]->channels);
		kमुक्त(wiphy->bands[NL80211_BAND_5GHZ]);
	पूर्ण
#अगर IS_ENABLED(CONFIG_PM)
	अगर (wiphy->wowlan != &brcmf_wowlan_support)
		kमुक्त(wiphy->wowlan);
#पूर्ण_अगर
पूर्ण

काष्ठा brcmf_cfg80211_info *brcmf_cfg80211_attach(काष्ठा brcmf_pub *drvr,
						  काष्ठा cfg80211_ops *ops,
						  bool p2pdev_क्रमced)
अणु
	काष्ठा wiphy *wiphy = drvr->wiphy;
	काष्ठा net_device *ndev = brcmf_get_अगरp(drvr, 0)->ndev;
	काष्ठा brcmf_cfg80211_info *cfg;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	काष्ठा brcmf_अगर *अगरp;
	s32 err = 0;
	s32 io_type;
	u16 *cap = शून्य;

	अगर (!ndev) अणु
		bphy_err(drvr, "ndev is invalid\n");
		वापस शून्य;
	पूर्ण

	cfg = kzalloc(माप(*cfg), GFP_KERNEL);
	अगर (!cfg) अणु
		bphy_err(drvr, "Could not allocate wiphy device\n");
		वापस शून्य;
	पूर्ण

	cfg->wiphy = wiphy;
	cfg->pub = drvr;
	init_vअगर_event(&cfg->vअगर_event);
	INIT_LIST_HEAD(&cfg->vअगर_list);

	vअगर = brcmf_alloc_vअगर(cfg, NL80211_IFTYPE_STATION);
	अगर (IS_ERR(vअगर))
		जाओ wiphy_out;

	अगरp = netdev_priv(ndev);
	vअगर->अगरp = अगरp;
	vअगर->wdev.netdev = ndev;
	ndev->ieee80211_ptr = &vअगर->wdev;
	SET_NETDEV_DEV(ndev, wiphy_dev(cfg->wiphy));

	err = wl_init_priv(cfg);
	अगर (err) अणु
		bphy_err(drvr, "Failed to init iwm_priv (%d)\n", err);
		brcmf_मुक्त_vअगर(vअगर);
		जाओ wiphy_out;
	पूर्ण
	अगरp->vअगर = vअगर;

	/* determine d11 io type beक्रमe wiphy setup */
	err = brcmf_fil_cmd_पूर्णांक_get(अगरp, BRCMF_C_GET_VERSION, &io_type);
	अगर (err) अणु
		bphy_err(drvr, "Failed to get D11 version (%d)\n", err);
		जाओ priv_out;
	पूर्ण
	cfg->d11inf.io_type = (u8)io_type;
	brcmu_d11_attach(&cfg->d11inf);

	/* regulatory notअगरer below needs access to cfg so
	 * assign it now.
	 */
	drvr->config = cfg;

	err = brcmf_setup_wiphy(wiphy, अगरp);
	अगर (err < 0)
		जाओ priv_out;

	brcmf_dbg(INFO, "Registering custom regulatory\n");
	wiphy->reg_notअगरier = brcmf_cfg80211_reg_notअगरier;
	wiphy->regulatory_flags |= REGULATORY_CUSTOM_REG;
	wiphy_apply_custom_regulatory(wiphy, &brcmf_regकरोm);

	/* firmware शेषs to 40MHz disabled in 2G band. We संकेत
	 * cfg80211 here that we करो and have it decide we can enable
	 * it. But first check अगर device करोes support 2G operation.
	 */
	अगर (wiphy->bands[NL80211_BAND_2GHZ]) अणु
		cap = &wiphy->bands[NL80211_BAND_2GHZ]->ht_cap.cap;
		*cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
	पूर्ण
#अगर_घोषित CONFIG_PM
	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_WOWL_GTK))
		ops->set_rekey_data = brcmf_cfg80211_set_rekey_data;
#पूर्ण_अगर
	err = wiphy_रेजिस्टर(wiphy);
	अगर (err < 0) अणु
		bphy_err(drvr, "Could not register wiphy device (%d)\n", err);
		जाओ priv_out;
	पूर्ण

	err = brcmf_setup_wiphybands(cfg);
	अगर (err) अणु
		bphy_err(drvr, "Setting wiphy bands failed (%d)\n", err);
		जाओ wiphy_unreg_out;
	पूर्ण

	/* If cfg80211 didn't disable 40MHz HT CAP in wiphy_रेजिस्टर(),
	 * setup 40MHz in 2GHz band and enable OBSS scanning.
	 */
	अगर (cap && (*cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40)) अणु
		err = brcmf_enable_bw40_2g(cfg);
		अगर (!err)
			err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "obss_coex",
						      BRCMF_OBSS_COEX_AUTO);
		अन्यथा
			*cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;
	पूर्ण

	err = brcmf_fweh_activate_events(अगरp);
	अगर (err) अणु
		bphy_err(drvr, "FWEH activation failed (%d)\n", err);
		जाओ wiphy_unreg_out;
	पूर्ण

	err = brcmf_p2p_attach(cfg, p2pdev_क्रमced);
	अगर (err) अणु
		bphy_err(drvr, "P2P initialisation failed (%d)\n", err);
		जाओ wiphy_unreg_out;
	पूर्ण
	err = brcmf_btcoex_attach(cfg);
	अगर (err) अणु
		bphy_err(drvr, "BT-coex initialisation failed (%d)\n", err);
		brcmf_p2p_detach(&cfg->p2p);
		जाओ wiphy_unreg_out;
	पूर्ण
	err = brcmf_pno_attach(cfg);
	अगर (err) अणु
		bphy_err(drvr, "PNO initialisation failed (%d)\n", err);
		brcmf_btcoex_detach(cfg);
		brcmf_p2p_detach(&cfg->p2p);
		जाओ wiphy_unreg_out;
	पूर्ण

	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_TDLS)) अणु
		err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "tdls_enable", 1);
		अगर (err) अणु
			brcmf_dbg(INFO, "TDLS not enabled (%d)\n", err);
			wiphy->flags &= ~WIPHY_FLAG_SUPPORTS_TDLS;
		पूर्ण अन्यथा अणु
			brcmf_fweh_रेजिस्टर(cfg->pub, BRCMF_E_TDLS_PEER_EVENT,
					    brcmf_notअगरy_tdls_peer_event);
		पूर्ण
	पूर्ण

	/* (re-) activate FWEH event handling */
	err = brcmf_fweh_activate_events(अगरp);
	अगर (err) अणु
		bphy_err(drvr, "FWEH activation failed (%d)\n", err);
		जाओ detach;
	पूर्ण

	/* Fill in some of the advertised nl80211 supported features */
	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_SCAN_RANDOM_MAC)) अणु
		wiphy->features |= NL80211_FEATURE_SCHED_SCAN_RANDOM_MAC_ADDR;
#अगर_घोषित CONFIG_PM
		अगर (wiphy->wowlan &&
		    wiphy->wowlan->flags & WIPHY_WOWLAN_NET_DETECT)
			wiphy->features |= NL80211_FEATURE_ND_RANDOM_MAC_ADDR;
#पूर्ण_अगर
	पूर्ण

	वापस cfg;

detach:
	brcmf_pno_detach(cfg);
	brcmf_btcoex_detach(cfg);
	brcmf_p2p_detach(&cfg->p2p);
wiphy_unreg_out:
	wiphy_unरेजिस्टर(cfg->wiphy);
priv_out:
	wl_deinit_priv(cfg);
	brcmf_मुक्त_vअगर(vअगर);
	अगरp->vअगर = शून्य;
wiphy_out:
	brcmf_मुक्त_wiphy(wiphy);
	kमुक्त(cfg);
	वापस शून्य;
पूर्ण

व्योम brcmf_cfg80211_detach(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	अगर (!cfg)
		वापस;

	brcmf_pno_detach(cfg);
	brcmf_btcoex_detach(cfg);
	wiphy_unरेजिस्टर(cfg->wiphy);
	wl_deinit_priv(cfg);
	brcmf_मुक्त_wiphy(cfg->wiphy);
	kमुक्त(cfg);
पूर्ण
