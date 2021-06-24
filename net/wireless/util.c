<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Wireless utility functions
 *
 * Copyright 2007-2009	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright 2017	Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */
#समावेश <linux/export.h>
#समावेश <linux/bitops.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/ieee80211.h>
#समावेश <net/cfg80211.h>
#समावेश <net/ip.h>
#समावेश <net/dsfield.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/mpls.h>
#समावेश <linux/gcd.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/nospec.h>
#समावेश "core.h"
#समावेश "rdev-ops.h"


स्थिर काष्ठा ieee80211_rate *
ieee80211_get_response_rate(काष्ठा ieee80211_supported_band *sband,
			    u32 basic_rates, पूर्णांक bitrate)
अणु
	काष्ठा ieee80211_rate *result = &sband->bitrates[0];
	पूर्णांक i;

	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		अगर (!(basic_rates & BIT(i)))
			जारी;
		अगर (sband->bitrates[i].bitrate > bitrate)
			जारी;
		result = &sband->bitrates[i];
	पूर्ण

	वापस result;
पूर्ण
EXPORT_SYMBOL(ieee80211_get_response_rate);

u32 ieee80211_mandatory_rates(काष्ठा ieee80211_supported_band *sband,
			      क्रमागत nl80211_bss_scan_width scan_width)
अणु
	काष्ठा ieee80211_rate *bitrates;
	u32 mandatory_rates = 0;
	क्रमागत ieee80211_rate_flags mandatory_flag;
	पूर्णांक i;

	अगर (WARN_ON(!sband))
		वापस 1;

	अगर (sband->band == NL80211_BAND_2GHZ) अणु
		अगर (scan_width == NL80211_BSS_CHAN_WIDTH_5 ||
		    scan_width == NL80211_BSS_CHAN_WIDTH_10)
			mandatory_flag = IEEE80211_RATE_MANDATORY_G;
		अन्यथा
			mandatory_flag = IEEE80211_RATE_MANDATORY_B;
	पूर्ण अन्यथा अणु
		mandatory_flag = IEEE80211_RATE_MANDATORY_A;
	पूर्ण

	bitrates = sband->bitrates;
	क्रम (i = 0; i < sband->n_bitrates; i++)
		अगर (bitrates[i].flags & mandatory_flag)
			mandatory_rates |= BIT(i);
	वापस mandatory_rates;
पूर्ण
EXPORT_SYMBOL(ieee80211_mandatory_rates);

u32 ieee80211_channel_to_freq_khz(पूर्णांक chan, क्रमागत nl80211_band band)
अणु
	/* see 802.11 17.3.8.3.2 and Annex J
	 * there are overlapping channel numbers in 5GHz and 2GHz bands */
	अगर (chan <= 0)
		वापस 0; /* not supported */
	चयन (band) अणु
	हाल NL80211_BAND_2GHZ:
		अगर (chan == 14)
			वापस MHZ_TO_KHZ(2484);
		अन्यथा अगर (chan < 14)
			वापस MHZ_TO_KHZ(2407 + chan * 5);
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		अगर (chan >= 182 && chan <= 196)
			वापस MHZ_TO_KHZ(4000 + chan * 5);
		अन्यथा
			वापस MHZ_TO_KHZ(5000 + chan * 5);
		अवरोध;
	हाल NL80211_BAND_6GHZ:
		/* see 802.11ax D6.1 27.3.23.2 */
		अगर (chan == 2)
			वापस MHZ_TO_KHZ(5935);
		अगर (chan <= 233)
			वापस MHZ_TO_KHZ(5950 + chan * 5);
		अवरोध;
	हाल NL80211_BAND_60GHZ:
		अगर (chan < 7)
			वापस MHZ_TO_KHZ(56160 + chan * 2160);
		अवरोध;
	हाल NL80211_BAND_S1GHZ:
		वापस 902000 + chan * 500;
	शेष:
		;
	पूर्ण
	वापस 0; /* not supported */
पूर्ण
EXPORT_SYMBOL(ieee80211_channel_to_freq_khz);

क्रमागत nl80211_chan_width
ieee80211_s1g_channel_width(स्थिर काष्ठा ieee80211_channel *chan)
अणु
	अगर (WARN_ON(!chan || chan->band != NL80211_BAND_S1GHZ))
		वापस NL80211_CHAN_WIDTH_20_NOHT;

	/*S1G defines a single allowed channel width per channel.
	 * Extract that width here.
	 */
	अगर (chan->flags & IEEE80211_CHAN_1MHZ)
		वापस NL80211_CHAN_WIDTH_1;
	अन्यथा अगर (chan->flags & IEEE80211_CHAN_2MHZ)
		वापस NL80211_CHAN_WIDTH_2;
	अन्यथा अगर (chan->flags & IEEE80211_CHAN_4MHZ)
		वापस NL80211_CHAN_WIDTH_4;
	अन्यथा अगर (chan->flags & IEEE80211_CHAN_8MHZ)
		वापस NL80211_CHAN_WIDTH_8;
	अन्यथा अगर (chan->flags & IEEE80211_CHAN_16MHZ)
		वापस NL80211_CHAN_WIDTH_16;

	pr_err("unknown channel width for channel at %dKHz?\n",
	       ieee80211_channel_to_khz(chan));

	वापस NL80211_CHAN_WIDTH_1;
पूर्ण
EXPORT_SYMBOL(ieee80211_s1g_channel_width);

पूर्णांक ieee80211_freq_khz_to_channel(u32 freq)
अणु
	/* TODO: just handle MHz क्रम now */
	freq = KHZ_TO_MHZ(freq);

	/* see 802.11 17.3.8.3.2 and Annex J */
	अगर (freq == 2484)
		वापस 14;
	अन्यथा अगर (freq < 2484)
		वापस (freq - 2407) / 5;
	अन्यथा अगर (freq >= 4910 && freq <= 4980)
		वापस (freq - 4000) / 5;
	अन्यथा अगर (freq < 5925)
		वापस (freq - 5000) / 5;
	अन्यथा अगर (freq == 5935)
		वापस 2;
	अन्यथा अगर (freq <= 45000) /* DMG band lower limit */
		/* see 802.11ax D6.1 27.3.22.2 */
		वापस (freq - 5950) / 5;
	अन्यथा अगर (freq >= 58320 && freq <= 70200)
		वापस (freq - 56160) / 2160;
	अन्यथा
		वापस 0;
पूर्ण
EXPORT_SYMBOL(ieee80211_freq_khz_to_channel);

काष्ठा ieee80211_channel *ieee80211_get_channel_khz(काष्ठा wiphy *wiphy,
						    u32 freq)
अणु
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_supported_band *sband;
	पूर्णांक i;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		sband = wiphy->bands[band];

		अगर (!sband)
			जारी;

		क्रम (i = 0; i < sband->n_channels; i++) अणु
			काष्ठा ieee80211_channel *chan = &sband->channels[i];

			अगर (ieee80211_channel_to_khz(chan) == freq)
				वापस chan;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(ieee80211_get_channel_khz);

अटल व्योम set_mandatory_flags_band(काष्ठा ieee80211_supported_band *sband)
अणु
	पूर्णांक i, want;

	चयन (sband->band) अणु
	हाल NL80211_BAND_5GHZ:
	हाल NL80211_BAND_6GHZ:
		want = 3;
		क्रम (i = 0; i < sband->n_bitrates; i++) अणु
			अगर (sband->bitrates[i].bitrate == 60 ||
			    sband->bitrates[i].bitrate == 120 ||
			    sband->bitrates[i].bitrate == 240) अणु
				sband->bitrates[i].flags |=
					IEEE80211_RATE_MANDATORY_A;
				want--;
			पूर्ण
		पूर्ण
		WARN_ON(want);
		अवरोध;
	हाल NL80211_BAND_2GHZ:
		want = 7;
		क्रम (i = 0; i < sband->n_bitrates; i++) अणु
			चयन (sband->bitrates[i].bitrate) अणु
			हाल 10:
			हाल 20:
			हाल 55:
			हाल 110:
				sband->bitrates[i].flags |=
					IEEE80211_RATE_MANDATORY_B |
					IEEE80211_RATE_MANDATORY_G;
				want--;
				अवरोध;
			हाल 60:
			हाल 120:
			हाल 240:
				sband->bitrates[i].flags |=
					IEEE80211_RATE_MANDATORY_G;
				want--;
				fallthrough;
			शेष:
				sband->bitrates[i].flags |=
					IEEE80211_RATE_ERP_G;
				अवरोध;
			पूर्ण
		पूर्ण
		WARN_ON(want != 0 && want != 3);
		अवरोध;
	हाल NL80211_BAND_60GHZ:
		/* check क्रम mandatory HT MCS 1..4 */
		WARN_ON(!sband->ht_cap.ht_supported);
		WARN_ON((sband->ht_cap.mcs.rx_mask[0] & 0x1e) != 0x1e);
		अवरोध;
	हाल NL80211_BAND_S1GHZ:
		/* Figure 9-589bd: 3 means unsupported, so != 3 means at least
		 * mandatory is ok.
		 */
		WARN_ON((sband->s1g_cap.nss_mcs[0] & 0x3) == 0x3);
		अवरोध;
	हाल NUM_NL80211_BANDS:
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

व्योम ieee80211_set_bitrate_flags(काष्ठा wiphy *wiphy)
अणु
	क्रमागत nl80211_band band;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++)
		अगर (wiphy->bands[band])
			set_mandatory_flags_band(wiphy->bands[band]);
पूर्ण

bool cfg80211_supported_cipher_suite(काष्ठा wiphy *wiphy, u32 cipher)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < wiphy->n_cipher_suites; i++)
		अगर (cipher == wiphy->cipher_suites[i])
			वापस true;
	वापस false;
पूर्ण

अटल bool
cfg80211_igtk_cipher_supported(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा wiphy *wiphy = &rdev->wiphy;
	पूर्णांक i;

	क्रम (i = 0; i < wiphy->n_cipher_suites; i++) अणु
		चयन (wiphy->cipher_suites[i]) अणु
		हाल WLAN_CIPHER_SUITE_AES_CMAC:
		हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
		हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

bool cfg80211_valid_key_idx(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			    पूर्णांक key_idx, bool pairwise)
अणु
	पूर्णांक max_key_idx;

	अगर (pairwise)
		max_key_idx = 3;
	अन्यथा अगर (wiphy_ext_feature_isset(&rdev->wiphy,
					 NL80211_EXT_FEATURE_BEACON_PROTECTION) ||
		 wiphy_ext_feature_isset(&rdev->wiphy,
					 NL80211_EXT_FEATURE_BEACON_PROTECTION_CLIENT))
		max_key_idx = 7;
	अन्यथा अगर (cfg80211_igtk_cipher_supported(rdev))
		max_key_idx = 5;
	अन्यथा
		max_key_idx = 3;

	अगर (key_idx < 0 || key_idx > max_key_idx)
		वापस false;

	वापस true;
पूर्ण

पूर्णांक cfg80211_validate_key_settings(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा key_params *params, पूर्णांक key_idx,
				   bool pairwise, स्थिर u8 *mac_addr)
अणु
	अगर (!cfg80211_valid_key_idx(rdev, key_idx, pairwise))
		वापस -EINVAL;

	अगर (!pairwise && mac_addr && !(rdev->wiphy.flags & WIPHY_FLAG_IBSS_RSN))
		वापस -EINVAL;

	अगर (pairwise && !mac_addr)
		वापस -EINVAL;

	चयन (params->cipher) अणु
	हाल WLAN_CIPHER_SUITE_TKIP:
		/* Extended Key ID can only be used with CCMP/GCMP ciphers */
		अगर ((pairwise && key_idx) ||
		    params->mode != NL80211_KEY_RX_TX)
			वापस -EINVAL;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		/* IEEE802.11-2016 allows only 0 and - when supporting
		 * Extended Key ID - 1 as index क्रम pairwise keys.
		 * @NL80211_KEY_NO_TX is only allowed क्रम pairwise keys when
		 * the driver supports Extended Key ID.
		 * @NL80211_KEY_SET_TX can't be set when installing and
		 * validating a key.
		 */
		अगर ((params->mode == NL80211_KEY_NO_TX && !pairwise) ||
		    params->mode == NL80211_KEY_SET_TX)
			वापस -EINVAL;
		अगर (wiphy_ext_feature_isset(&rdev->wiphy,
					    NL80211_EXT_FEATURE_EXT_KEY_ID)) अणु
			अगर (pairwise && (key_idx < 0 || key_idx > 1))
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (pairwise && key_idx) अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		/* Disallow BIP (group-only) cipher as pairwise cipher */
		अगर (pairwise)
			वापस -EINVAL;
		अगर (key_idx < 4)
			वापस -EINVAL;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		अगर (key_idx > 3)
			वापस -EINVAL;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (params->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
		अगर (params->key_len != WLAN_KEY_LEN_WEP40)
			वापस -EINVAL;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		अगर (params->key_len != WLAN_KEY_LEN_TKIP)
			वापस -EINVAL;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		अगर (params->key_len != WLAN_KEY_LEN_CCMP)
			वापस -EINVAL;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		अगर (params->key_len != WLAN_KEY_LEN_CCMP_256)
			वापस -EINVAL;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_GCMP:
		अगर (params->key_len != WLAN_KEY_LEN_GCMP)
			वापस -EINVAL;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		अगर (params->key_len != WLAN_KEY_LEN_GCMP_256)
			वापस -EINVAL;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP104:
		अगर (params->key_len != WLAN_KEY_LEN_WEP104)
			वापस -EINVAL;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
		अगर (params->key_len != WLAN_KEY_LEN_AES_CMAC)
			वापस -EINVAL;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		अगर (params->key_len != WLAN_KEY_LEN_BIP_CMAC_256)
			वापस -EINVAL;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
		अगर (params->key_len != WLAN_KEY_LEN_BIP_GMAC_128)
			वापस -EINVAL;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		अगर (params->key_len != WLAN_KEY_LEN_BIP_GMAC_256)
			वापस -EINVAL;
		अवरोध;
	शेष:
		/*
		 * We करोn't know anything about this algorithm,
		 * allow using it -- but the driver must check
		 * all parameters! We still check below whether
		 * or not the driver supports this algorithm,
		 * of course.
		 */
		अवरोध;
	पूर्ण

	अगर (params->seq) अणु
		चयन (params->cipher) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
			/* These ciphers करो not use key sequence */
			वापस -EINVAL;
		हाल WLAN_CIPHER_SUITE_TKIP:
		हाल WLAN_CIPHER_SUITE_CCMP:
		हाल WLAN_CIPHER_SUITE_CCMP_256:
		हाल WLAN_CIPHER_SUITE_GCMP:
		हाल WLAN_CIPHER_SUITE_GCMP_256:
		हाल WLAN_CIPHER_SUITE_AES_CMAC:
		हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
		हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
			अगर (params->seq_len != 6)
				वापस -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!cfg80211_supported_cipher_suite(&rdev->wiphy, params->cipher))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक __attribute_स्थिर__ ieee80211_hdrlen(__le16 fc)
अणु
	अचिन्हित पूर्णांक hdrlen = 24;

	अगर (ieee80211_is_ext(fc)) अणु
		hdrlen = 4;
		जाओ out;
	पूर्ण

	अगर (ieee80211_is_data(fc)) अणु
		अगर (ieee80211_has_a4(fc))
			hdrlen = 30;
		अगर (ieee80211_is_data_qos(fc)) अणु
			hdrlen += IEEE80211_QOS_CTL_LEN;
			अगर (ieee80211_has_order(fc))
				hdrlen += IEEE80211_HT_CTL_LEN;
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (ieee80211_is_mgmt(fc)) अणु
		अगर (ieee80211_has_order(fc))
			hdrlen += IEEE80211_HT_CTL_LEN;
		जाओ out;
	पूर्ण

	अगर (ieee80211_is_ctl(fc)) अणु
		/*
		 * ACK and CTS are 10 bytes, all others 16. To see how
		 * to get this condition consider
		 *   subtype mask:   0b0000000011110000 (0x00F0)
		 *   ACK subtype:    0b0000000011010000 (0x00D0)
		 *   CTS subtype:    0b0000000011000000 (0x00C0)
		 *   bits that matter:         ^^^      (0x00E0)
		 *   value of those: 0b0000000011000000 (0x00C0)
		 */
		अगर ((fc & cpu_to_le16(0x00E0)) == cpu_to_le16(0x00C0))
			hdrlen = 10;
		अन्यथा
			hdrlen = 16;
	पूर्ण
out:
	वापस hdrlen;
पूर्ण
EXPORT_SYMBOL(ieee80211_hdrlen);

अचिन्हित पूर्णांक ieee80211_get_hdrlen_from_skb(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ieee80211_hdr *hdr =
			(स्थिर काष्ठा ieee80211_hdr *)skb->data;
	अचिन्हित पूर्णांक hdrlen;

	अगर (unlikely(skb->len < 10))
		वापस 0;
	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	अगर (unlikely(hdrlen > skb->len))
		वापस 0;
	वापस hdrlen;
पूर्ण
EXPORT_SYMBOL(ieee80211_get_hdrlen_from_skb);

अटल अचिन्हित पूर्णांक __ieee80211_get_mesh_hdrlen(u8 flags)
अणु
	पूर्णांक ae = flags & MESH_FLAGS_AE;
	/* 802.11-2012, 8.2.4.7.3 */
	चयन (ae) अणु
	शेष:
	हाल 0:
		वापस 6;
	हाल MESH_FLAGS_AE_A4:
		वापस 12;
	हाल MESH_FLAGS_AE_A5_A6:
		वापस 18;
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक ieee80211_get_mesh_hdrlen(काष्ठा ieee80211s_hdr *meshhdr)
अणु
	वापस __ieee80211_get_mesh_hdrlen(meshhdr->flags);
पूर्ण
EXPORT_SYMBOL(ieee80211_get_mesh_hdrlen);

पूर्णांक ieee80211_data_to_8023_exthdr(काष्ठा sk_buff *skb, काष्ठा ethhdr *ehdr,
				  स्थिर u8 *addr, क्रमागत nl80211_अगरtype अगरtype,
				  u8 data_offset, bool is_amsdu)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा अणु
		u8 hdr[ETH_ALEN] __aligned(2);
		__be16 proto;
	पूर्ण payload;
	काष्ठा ethhdr पंचांगp;
	u16 hdrlen;
	u8 mesh_flags = 0;

	अगर (unlikely(!ieee80211_is_data_present(hdr->frame_control)))
		वापस -1;

	hdrlen = ieee80211_hdrlen(hdr->frame_control) + data_offset;
	अगर (skb->len < hdrlen + 8)
		वापस -1;

	/* convert IEEE 802.11 header + possible LLC headers पूर्णांकo Ethernet
	 * header
	 * IEEE 802.11 address fields:
	 * ToDS FromDS Addr1 Addr2 Addr3 Addr4
	 *   0     0   DA    SA    BSSID n/a
	 *   0     1   DA    BSSID SA    n/a
	 *   1     0   BSSID SA    DA    n/a
	 *   1     1   RA    TA    DA    SA
	 */
	स_नकल(पंचांगp.h_dest, ieee80211_get_DA(hdr), ETH_ALEN);
	स_नकल(पंचांगp.h_source, ieee80211_get_SA(hdr), ETH_ALEN);

	अगर (अगरtype == NL80211_IFTYPE_MESH_POINT)
		skb_copy_bits(skb, hdrlen, &mesh_flags, 1);

	mesh_flags &= MESH_FLAGS_AE;

	चयन (hdr->frame_control &
		cpu_to_le16(IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) अणु
	हाल cpu_to_le16(IEEE80211_FCTL_TODS):
		अगर (unlikely(अगरtype != NL80211_IFTYPE_AP &&
			     अगरtype != NL80211_IFTYPE_AP_VLAN &&
			     अगरtype != NL80211_IFTYPE_P2P_GO))
			वापस -1;
		अवरोध;
	हाल cpu_to_le16(IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS):
		अगर (unlikely(अगरtype != NL80211_IFTYPE_MESH_POINT &&
			     अगरtype != NL80211_IFTYPE_AP_VLAN &&
			     अगरtype != NL80211_IFTYPE_STATION))
			वापस -1;
		अगर (अगरtype == NL80211_IFTYPE_MESH_POINT) अणु
			अगर (mesh_flags == MESH_FLAGS_AE_A4)
				वापस -1;
			अगर (mesh_flags == MESH_FLAGS_AE_A5_A6) अणु
				skb_copy_bits(skb, hdrlen +
					दुरत्व(काष्ठा ieee80211s_hdr, eaddr1),
					पंचांगp.h_dest, 2 * ETH_ALEN);
			पूर्ण
			hdrlen += __ieee80211_get_mesh_hdrlen(mesh_flags);
		पूर्ण
		अवरोध;
	हाल cpu_to_le16(IEEE80211_FCTL_FROMDS):
		अगर ((अगरtype != NL80211_IFTYPE_STATION &&
		     अगरtype != NL80211_IFTYPE_P2P_CLIENT &&
		     अगरtype != NL80211_IFTYPE_MESH_POINT) ||
		    (is_multicast_ether_addr(पंचांगp.h_dest) &&
		     ether_addr_equal(पंचांगp.h_source, addr)))
			वापस -1;
		अगर (अगरtype == NL80211_IFTYPE_MESH_POINT) अणु
			अगर (mesh_flags == MESH_FLAGS_AE_A5_A6)
				वापस -1;
			अगर (mesh_flags == MESH_FLAGS_AE_A4)
				skb_copy_bits(skb, hdrlen +
					दुरत्व(काष्ठा ieee80211s_hdr, eaddr1),
					पंचांगp.h_source, ETH_ALEN);
			hdrlen += __ieee80211_get_mesh_hdrlen(mesh_flags);
		पूर्ण
		अवरोध;
	हाल cpu_to_le16(0):
		अगर (अगरtype != NL80211_IFTYPE_ADHOC &&
		    अगरtype != NL80211_IFTYPE_STATION &&
		    अगरtype != NL80211_IFTYPE_OCB)
				वापस -1;
		अवरोध;
	पूर्ण

	skb_copy_bits(skb, hdrlen, &payload, माप(payload));
	पंचांगp.h_proto = payload.proto;

	अगर (likely((!is_amsdu && ether_addr_equal(payload.hdr, rfc1042_header) &&
		    पंचांगp.h_proto != htons(ETH_P_AARP) &&
		    पंचांगp.h_proto != htons(ETH_P_IPX)) ||
		   ether_addr_equal(payload.hdr, bridge_tunnel_header)))
		/* हटाओ RFC1042 or Bridge-Tunnel encapsulation and
		 * replace EtherType */
		hdrlen += ETH_ALEN + 2;
	अन्यथा
		पंचांगp.h_proto = htons(skb->len - hdrlen);

	pskb_pull(skb, hdrlen);

	अगर (!ehdr)
		ehdr = skb_push(skb, माप(काष्ठा ethhdr));
	स_नकल(ehdr, &पंचांगp, माप(पंचांगp));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ieee80211_data_to_8023_exthdr);

अटल व्योम
__frame_add_frag(काष्ठा sk_buff *skb, काष्ठा page *page,
		 व्योम *ptr, पूर्णांक len, पूर्णांक size)
अणु
	काष्ठा skb_shared_info *sh = skb_shinfo(skb);
	पूर्णांक page_offset;

	get_page(page);
	page_offset = ptr - page_address(page);
	skb_add_rx_frag(skb, sh->nr_frags, page, page_offset, len, size);
पूर्ण

अटल व्योम
__ieee80211_amsdu_copy_frag(काष्ठा sk_buff *skb, काष्ठा sk_buff *frame,
			    पूर्णांक offset, पूर्णांक len)
अणु
	काष्ठा skb_shared_info *sh = skb_shinfo(skb);
	स्थिर skb_frag_t *frag = &sh->frags[0];
	काष्ठा page *frag_page;
	व्योम *frag_ptr;
	पूर्णांक frag_len, frag_size;
	पूर्णांक head_size = skb->len - skb->data_len;
	पूर्णांक cur_len;

	frag_page = virt_to_head_page(skb->head);
	frag_ptr = skb->data;
	frag_size = head_size;

	जबतक (offset >= frag_size) अणु
		offset -= frag_size;
		frag_page = skb_frag_page(frag);
		frag_ptr = skb_frag_address(frag);
		frag_size = skb_frag_size(frag);
		frag++;
	पूर्ण

	frag_ptr += offset;
	frag_len = frag_size - offset;

	cur_len = min(len, frag_len);

	__frame_add_frag(frame, frag_page, frag_ptr, cur_len, frag_size);
	len -= cur_len;

	जबतक (len > 0) अणु
		frag_len = skb_frag_size(frag);
		cur_len = min(len, frag_len);
		__frame_add_frag(frame, skb_frag_page(frag),
				 skb_frag_address(frag), cur_len, frag_len);
		len -= cur_len;
		frag++;
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *
__ieee80211_amsdu_copy(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hlen,
		       पूर्णांक offset, पूर्णांक len, bool reuse_frag)
अणु
	काष्ठा sk_buff *frame;
	पूर्णांक cur_len = len;

	अगर (skb->len - offset < len)
		वापस शून्य;

	/*
	 * When reusing framents, copy some data to the head to simplअगरy
	 * ethernet header handling and speed up protocol header processing
	 * in the stack later.
	 */
	अगर (reuse_frag)
		cur_len = min_t(पूर्णांक, len, 32);

	/*
	 * Allocate and reserve two bytes more क्रम payload
	 * alignment since माप(काष्ठा ethhdr) is 14.
	 */
	frame = dev_alloc_skb(hlen + माप(काष्ठा ethhdr) + 2 + cur_len);
	अगर (!frame)
		वापस शून्य;

	skb_reserve(frame, hlen + माप(काष्ठा ethhdr) + 2);
	skb_copy_bits(skb, offset, skb_put(frame, cur_len), cur_len);

	len -= cur_len;
	अगर (!len)
		वापस frame;

	offset += cur_len;
	__ieee80211_amsdu_copy_frag(skb, frame, offset, len);

	वापस frame;
पूर्ण

व्योम ieee80211_amsdu_to_8023s(काष्ठा sk_buff *skb, काष्ठा sk_buff_head *list,
			      स्थिर u8 *addr, क्रमागत nl80211_अगरtype अगरtype,
			      स्थिर अचिन्हित पूर्णांक extra_headroom,
			      स्थिर u8 *check_da, स्थिर u8 *check_sa)
अणु
	अचिन्हित पूर्णांक hlen = ALIGN(extra_headroom, 4);
	काष्ठा sk_buff *frame = शून्य;
	u16 ethertype;
	u8 *payload;
	पूर्णांक offset = 0, reमुख्यing;
	काष्ठा ethhdr eth;
	bool reuse_frag = skb->head_frag && !skb_has_frag_list(skb);
	bool reuse_skb = false;
	bool last = false;

	जबतक (!last) अणु
		अचिन्हित पूर्णांक subframe_len;
		पूर्णांक len;
		u8 padding;

		skb_copy_bits(skb, offset, &eth, माप(eth));
		len = ntohs(eth.h_proto);
		subframe_len = माप(काष्ठा ethhdr) + len;
		padding = (4 - subframe_len) & 0x3;

		/* the last MSDU has no padding */
		reमुख्यing = skb->len - offset;
		अगर (subframe_len > reमुख्यing)
			जाओ purge;
		/* mitigate A-MSDU aggregation injection attacks */
		अगर (ether_addr_equal(eth.h_dest, rfc1042_header))
			जाओ purge;

		offset += माप(काष्ठा ethhdr);
		last = reमुख्यing <= subframe_len + padding;

		/* FIXME: should we really accept multicast DA? */
		अगर ((check_da && !is_multicast_ether_addr(eth.h_dest) &&
		     !ether_addr_equal(check_da, eth.h_dest)) ||
		    (check_sa && !ether_addr_equal(check_sa, eth.h_source))) अणु
			offset += len + padding;
			जारी;
		पूर्ण

		/* reuse skb क्रम the last subframe */
		अगर (!skb_is_nonlinear(skb) && !reuse_frag && last) अणु
			skb_pull(skb, offset);
			frame = skb;
			reuse_skb = true;
		पूर्ण अन्यथा अणु
			frame = __ieee80211_amsdu_copy(skb, hlen, offset, len,
						       reuse_frag);
			अगर (!frame)
				जाओ purge;

			offset += len + padding;
		पूर्ण

		skb_reset_network_header(frame);
		frame->dev = skb->dev;
		frame->priority = skb->priority;

		payload = frame->data;
		ethertype = (payload[6] << 8) | payload[7];
		अगर (likely((ether_addr_equal(payload, rfc1042_header) &&
			    ethertype != ETH_P_AARP && ethertype != ETH_P_IPX) ||
			   ether_addr_equal(payload, bridge_tunnel_header))) अणु
			eth.h_proto = htons(ethertype);
			skb_pull(frame, ETH_ALEN + 2);
		पूर्ण

		स_नकल(skb_push(frame, माप(eth)), &eth, माप(eth));
		__skb_queue_tail(list, frame);
	पूर्ण

	अगर (!reuse_skb)
		dev_kमुक्त_skb(skb);

	वापस;

 purge:
	__skb_queue_purge(list);
	dev_kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL(ieee80211_amsdu_to_8023s);

/* Given a data frame determine the 802.1p/1d tag to use. */
अचिन्हित पूर्णांक cfg80211_classअगरy8021d(काष्ठा sk_buff *skb,
				    काष्ठा cfg80211_qos_map *qos_map)
अणु
	अचिन्हित पूर्णांक dscp;
	अचिन्हित अक्षर vlan_priority;
	अचिन्हित पूर्णांक ret;

	/* skb->priority values from 256->263 are magic values to
	 * directly indicate a specअगरic 802.1d priority.  This is used
	 * to allow 802.1d priority to be passed directly in from VLAN
	 * tags, etc.
	 */
	अगर (skb->priority >= 256 && skb->priority <= 263) अणु
		ret = skb->priority - 256;
		जाओ out;
	पूर्ण

	अगर (skb_vlan_tag_present(skb)) अणु
		vlan_priority = (skb_vlan_tag_get(skb) & VLAN_PRIO_MASK)
			>> VLAN_PRIO_SHIFT;
		अगर (vlan_priority > 0) अणु
			ret = vlan_priority;
			जाओ out;
		पूर्ण
	पूर्ण

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		dscp = ipv4_get_dsfield(ip_hdr(skb)) & 0xfc;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		dscp = ipv6_get_dsfield(ipv6_hdr(skb)) & 0xfc;
		अवरोध;
	हाल htons(ETH_P_MPLS_UC):
	हाल htons(ETH_P_MPLS_MC): अणु
		काष्ठा mpls_label mpls_पंचांगp, *mpls;

		mpls = skb_header_poपूर्णांकer(skb, माप(काष्ठा ethhdr),
					  माप(*mpls), &mpls_पंचांगp);
		अगर (!mpls)
			वापस 0;

		ret = (ntohl(mpls->entry) & MPLS_LS_TC_MASK)
			>> MPLS_LS_TC_SHIFT;
		जाओ out;
	पूर्ण
	हाल htons(ETH_P_80221):
		/* 802.21 is always network control traffic */
		वापस 7;
	शेष:
		वापस 0;
	पूर्ण

	अगर (qos_map) अणु
		अचिन्हित पूर्णांक i, पंचांगp_dscp = dscp >> 2;

		क्रम (i = 0; i < qos_map->num_des; i++) अणु
			अगर (पंचांगp_dscp == qos_map->dscp_exception[i].dscp) अणु
				ret = qos_map->dscp_exception[i].up;
				जाओ out;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < 8; i++) अणु
			अगर (पंचांगp_dscp >= qos_map->up[i].low &&
			    पंचांगp_dscp <= qos_map->up[i].high) अणु
				ret = i;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = dscp >> 5;
out:
	वापस array_index_nospec(ret, IEEE80211_NUM_TIDS);
पूर्ण
EXPORT_SYMBOL(cfg80211_classअगरy8021d);

स्थिर काष्ठा element *ieee80211_bss_get_elem(काष्ठा cfg80211_bss *bss, u8 id)
अणु
	स्थिर काष्ठा cfg80211_bss_ies *ies;

	ies = rcu_dereference(bss->ies);
	अगर (!ies)
		वापस शून्य;

	वापस cfg80211_find_elem(id, ies->data, ies->len);
पूर्ण
EXPORT_SYMBOL(ieee80211_bss_get_elem);

व्योम cfg80211_upload_connect_keys(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा net_device *dev = wdev->netdev;
	पूर्णांक i;

	अगर (!wdev->connect_keys)
		वापस;

	क्रम (i = 0; i < CFG80211_MAX_WEP_KEYS; i++) अणु
		अगर (!wdev->connect_keys->params[i].cipher)
			जारी;
		अगर (rdev_add_key(rdev, dev, i, false, शून्य,
				 &wdev->connect_keys->params[i])) अणु
			netdev_err(dev, "failed to set key %d\n", i);
			जारी;
		पूर्ण
		अगर (wdev->connect_keys->def == i &&
		    rdev_set_शेष_key(rdev, dev, i, true, true)) अणु
			netdev_err(dev, "failed to set defkey %d\n", i);
			जारी;
		पूर्ण
	पूर्ण

	kमुक्त_sensitive(wdev->connect_keys);
	wdev->connect_keys = शून्य;
पूर्ण

व्योम cfg80211_process_wdev_events(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_event *ev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdev->event_lock, flags);
	जबतक (!list_empty(&wdev->event_list)) अणु
		ev = list_first_entry(&wdev->event_list,
				      काष्ठा cfg80211_event, list);
		list_del(&ev->list);
		spin_unlock_irqrestore(&wdev->event_lock, flags);

		wdev_lock(wdev);
		चयन (ev->type) अणु
		हाल EVENT_CONNECT_RESULT:
			__cfg80211_connect_result(
				wdev->netdev,
				&ev->cr,
				ev->cr.status == WLAN_STATUS_SUCCESS);
			अवरोध;
		हाल EVENT_ROAMED:
			__cfg80211_roamed(wdev, &ev->rm);
			अवरोध;
		हाल EVENT_DISCONNECTED:
			__cfg80211_disconnected(wdev->netdev,
						ev->dc.ie, ev->dc.ie_len,
						ev->dc.reason,
						!ev->dc.locally_generated);
			अवरोध;
		हाल EVENT_IBSS_JOINED:
			__cfg80211_ibss_joined(wdev->netdev, ev->ij.bssid,
					       ev->ij.channel);
			अवरोध;
		हाल EVENT_STOPPED:
			__cfg80211_leave(wiphy_to_rdev(wdev->wiphy), wdev);
			अवरोध;
		हाल EVENT_PORT_AUTHORIZED:
			__cfg80211_port_authorized(wdev, ev->pa.bssid);
			अवरोध;
		पूर्ण
		wdev_unlock(wdev);

		kमुक्त(ev);

		spin_lock_irqsave(&wdev->event_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&wdev->event_lock, flags);
पूर्ण

व्योम cfg80211_process_rdev_events(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा wireless_dev *wdev;

	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list)
		cfg80211_process_wdev_events(wdev);
पूर्ण

पूर्णांक cfg80211_change_अगरace(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा net_device *dev, क्रमागत nl80211_अगरtype ntype,
			  काष्ठा vअगर_params *params)
अणु
	पूर्णांक err;
	क्रमागत nl80211_अगरtype otype = dev->ieee80211_ptr->अगरtype;

	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	/* करोn't support changing VLANs, you just re-create them */
	अगर (otype == NL80211_IFTYPE_AP_VLAN)
		वापस -EOPNOTSUPP;

	/* cannot change पूर्णांकo P2P device or न_अंक */
	अगर (ntype == NL80211_IFTYPE_P2P_DEVICE ||
	    ntype == NL80211_IFTYPE_न_अंक)
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->change_भव_पूर्णांकf ||
	    !(rdev->wiphy.पूर्णांकerface_modes & (1 << ntype)))
		वापस -EOPNOTSUPP;

	/* अगर it's part of a bridge, reject changing type to station/ibss */
	अगर (netअगर_is_bridge_port(dev) &&
	    (ntype == NL80211_IFTYPE_ADHOC ||
	     ntype == NL80211_IFTYPE_STATION ||
	     ntype == NL80211_IFTYPE_P2P_CLIENT))
		वापस -EBUSY;

	अगर (ntype != otype) अणु
		dev->ieee80211_ptr->use_4addr = false;
		dev->ieee80211_ptr->mesh_id_up_len = 0;
		wdev_lock(dev->ieee80211_ptr);
		rdev_set_qos_map(rdev, dev, शून्य);
		wdev_unlock(dev->ieee80211_ptr);

		चयन (otype) अणु
		हाल NL80211_IFTYPE_AP:
			cfg80211_stop_ap(rdev, dev, true);
			अवरोध;
		हाल NL80211_IFTYPE_ADHOC:
			cfg80211_leave_ibss(rdev, dev, false);
			अवरोध;
		हाल NL80211_IFTYPE_STATION:
		हाल NL80211_IFTYPE_P2P_CLIENT:
			wdev_lock(dev->ieee80211_ptr);
			cfg80211_disconnect(rdev, dev,
					    WLAN_REASON_DEAUTH_LEAVING, true);
			wdev_unlock(dev->ieee80211_ptr);
			अवरोध;
		हाल NL80211_IFTYPE_MESH_POINT:
			/* mesh should be handled? */
			अवरोध;
		हाल NL80211_IFTYPE_OCB:
			cfg80211_leave_ocb(rdev, dev);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		cfg80211_process_rdev_events(rdev);
		cfg80211_mlme_purge_registrations(dev->ieee80211_ptr);
	पूर्ण

	err = rdev_change_भव_पूर्णांकf(rdev, dev, ntype, params);

	WARN_ON(!err && dev->ieee80211_ptr->अगरtype != ntype);

	अगर (!err && params && params->use_4addr != -1)
		dev->ieee80211_ptr->use_4addr = params->use_4addr;

	अगर (!err) अणु
		dev->priv_flags &= ~IFF_DONT_BRIDGE;
		चयन (ntype) अणु
		हाल NL80211_IFTYPE_STATION:
			अगर (dev->ieee80211_ptr->use_4addr)
				अवरोध;
			fallthrough;
		हाल NL80211_IFTYPE_OCB:
		हाल NL80211_IFTYPE_P2P_CLIENT:
		हाल NL80211_IFTYPE_ADHOC:
			dev->priv_flags |= IFF_DONT_BRIDGE;
			अवरोध;
		हाल NL80211_IFTYPE_P2P_GO:
		हाल NL80211_IFTYPE_AP:
		हाल NL80211_IFTYPE_AP_VLAN:
		हाल NL80211_IFTYPE_MESH_POINT:
			/* bridging OK */
			अवरोध;
		हाल NL80211_IFTYPE_MONITOR:
			/* monitor can't bridge anyway */
			अवरोध;
		हाल NL80211_IFTYPE_UNSPECIFIED:
		हाल NUM_NL80211_IFTYPES:
			/* not happening */
			अवरोध;
		हाल NL80211_IFTYPE_P2P_DEVICE:
		हाल NL80211_IFTYPE_WDS:
		हाल NL80211_IFTYPE_न_अंक:
			WARN_ON(1);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!err && ntype != otype && netअगर_running(dev)) अणु
		cfg80211_update_अगरace_num(rdev, ntype, 1);
		cfg80211_update_अगरace_num(rdev, otype, -1);
	पूर्ण

	वापस err;
पूर्ण

अटल u32 cfg80211_calculate_bitrate_ht(काष्ठा rate_info *rate)
अणु
	पूर्णांक modulation, streams, bitrate;

	/* the क्रमmula below करोes only work क्रम MCS values smaller than 32 */
	अगर (WARN_ON_ONCE(rate->mcs >= 32))
		वापस 0;

	modulation = rate->mcs & 7;
	streams = (rate->mcs >> 3) + 1;

	bitrate = (rate->bw == RATE_INFO_BW_40) ? 13500000 : 6500000;

	अगर (modulation < 4)
		bitrate *= (modulation + 1);
	अन्यथा अगर (modulation == 4)
		bitrate *= (modulation + 2);
	अन्यथा
		bitrate *= (modulation + 3);

	bitrate *= streams;

	अगर (rate->flags & RATE_INFO_FLAGS_SHORT_GI)
		bitrate = (bitrate / 9) * 10;

	/* करो NOT round करोwn here */
	वापस (bitrate + 50000) / 100000;
पूर्ण

अटल u32 cfg80211_calculate_bitrate_dmg(काष्ठा rate_info *rate)
अणु
	अटल स्थिर u32 __mcs2bitrate[] = अणु
		/* control PHY */
		[0] =   275,
		/* SC PHY */
		[1] =  3850,
		[2] =  7700,
		[3] =  9625,
		[4] = 11550,
		[5] = 12512, /* 1251.25 mbps */
		[6] = 15400,
		[7] = 19250,
		[8] = 23100,
		[9] = 25025,
		[10] = 30800,
		[11] = 38500,
		[12] = 46200,
		/* OFDM PHY */
		[13] =  6930,
		[14] =  8662, /* 866.25 mbps */
		[15] = 13860,
		[16] = 17325,
		[17] = 20790,
		[18] = 27720,
		[19] = 34650,
		[20] = 41580,
		[21] = 45045,
		[22] = 51975,
		[23] = 62370,
		[24] = 67568, /* 6756.75 mbps */
		/* LP-SC PHY */
		[25] =  6260,
		[26] =  8340,
		[27] = 11120,
		[28] = 12510,
		[29] = 16680,
		[30] = 22240,
		[31] = 25030,
	पूर्ण;

	अगर (WARN_ON_ONCE(rate->mcs >= ARRAY_SIZE(__mcs2bitrate)))
		वापस 0;

	वापस __mcs2bitrate[rate->mcs];
पूर्ण

अटल u32 cfg80211_calculate_bitrate_extended_sc_dmg(काष्ठा rate_info *rate)
अणु
	अटल स्थिर u32 __mcs2bitrate[] = अणु
		[6 - 6] = 26950, /* MCS 9.1 : 2695.0 mbps */
		[7 - 6] = 50050, /* MCS 12.1 */
		[8 - 6] = 53900,
		[9 - 6] = 57750,
		[10 - 6] = 63900,
		[11 - 6] = 75075,
		[12 - 6] = 80850,
	पूर्ण;

	/* Extended SC MCS not defined क्रम base MCS below 6 or above 12 */
	अगर (WARN_ON_ONCE(rate->mcs < 6 || rate->mcs > 12))
		वापस 0;

	वापस __mcs2bitrate[rate->mcs - 6];
पूर्ण

अटल u32 cfg80211_calculate_bitrate_edmg(काष्ठा rate_info *rate)
अणु
	अटल स्थिर u32 __mcs2bitrate[] = अणु
		/* control PHY */
		[0] =   275,
		/* SC PHY */
		[1] =  3850,
		[2] =  7700,
		[3] =  9625,
		[4] = 11550,
		[5] = 12512, /* 1251.25 mbps */
		[6] = 13475,
		[7] = 15400,
		[8] = 19250,
		[9] = 23100,
		[10] = 25025,
		[11] = 26950,
		[12] = 30800,
		[13] = 38500,
		[14] = 46200,
		[15] = 50050,
		[16] = 53900,
		[17] = 57750,
		[18] = 69300,
		[19] = 75075,
		[20] = 80850,
	पूर्ण;

	अगर (WARN_ON_ONCE(rate->mcs >= ARRAY_SIZE(__mcs2bitrate)))
		वापस 0;

	वापस __mcs2bitrate[rate->mcs] * rate->n_bonded_ch;
पूर्ण

अटल u32 cfg80211_calculate_bitrate_vht(काष्ठा rate_info *rate)
अणु
	अटल स्थिर u32 base[4][12] = अणु
		अणु   6500000,
		   13000000,
		   19500000,
		   26000000,
		   39000000,
		   52000000,
		   58500000,
		   65000000,
		   78000000,
		/* not in the spec, but some devices use this: */
		   86700000,
		   97500000,
		  108300000,
		पूर्ण,
		अणु  13500000,
		   27000000,
		   40500000,
		   54000000,
		   81000000,
		  108000000,
		  121500000,
		  135000000,
		  162000000,
		  180000000,
		  202500000,
		  225000000,
		पूर्ण,
		अणु  29300000,
		   58500000,
		   87800000,
		  117000000,
		  175500000,
		  234000000,
		  263300000,
		  292500000,
		  351000000,
		  390000000,
		  438800000,
		  487500000,
		पूर्ण,
		अणु  58500000,
		  117000000,
		  175500000,
		  234000000,
		  351000000,
		  468000000,
		  526500000,
		  585000000,
		  702000000,
		  780000000,
		  877500000,
		  975000000,
		पूर्ण,
	पूर्ण;
	u32 bitrate;
	पूर्णांक idx;

	अगर (rate->mcs > 11)
		जाओ warn;

	चयन (rate->bw) अणु
	हाल RATE_INFO_BW_160:
		idx = 3;
		अवरोध;
	हाल RATE_INFO_BW_80:
		idx = 2;
		अवरोध;
	हाल RATE_INFO_BW_40:
		idx = 1;
		अवरोध;
	हाल RATE_INFO_BW_5:
	हाल RATE_INFO_BW_10:
	शेष:
		जाओ warn;
	हाल RATE_INFO_BW_20:
		idx = 0;
	पूर्ण

	bitrate = base[idx][rate->mcs];
	bitrate *= rate->nss;

	अगर (rate->flags & RATE_INFO_FLAGS_SHORT_GI)
		bitrate = (bitrate / 9) * 10;

	/* करो NOT round करोwn here */
	वापस (bitrate + 50000) / 100000;
 warn:
	WARN_ONCE(1, "invalid rate bw=%d, mcs=%d, nss=%d\n",
		  rate->bw, rate->mcs, rate->nss);
	वापस 0;
पूर्ण

अटल u32 cfg80211_calculate_bitrate_he(काष्ठा rate_info *rate)
अणु
#घोषणा SCALE 6144
	u32 mcs_भागisors[14] = अणु
		102399, /* 16.666666... */
		 51201, /*  8.333333... */
		 34134, /*  5.555555... */
		 25599, /*  4.166666... */
		 17067, /*  2.777777... */
		 12801, /*  2.083333... */
		 11769, /*  1.851851... */
		 10239, /*  1.666666... */
		  8532, /*  1.388888... */
		  7680, /*  1.250000... */
		  6828, /*  1.111111... */
		  6144, /*  1.000000... */
		  5690, /*  0.926106... */
		  5120, /*  0.833333... */
	पूर्ण;
	u32 rates_160M[3] = अणु 960777777, 907400000, 816666666 पूर्ण;
	u32 rates_969[3] =  अणु 480388888, 453700000, 408333333 पूर्ण;
	u32 rates_484[3] =  अणु 229411111, 216666666, 195000000 पूर्ण;
	u32 rates_242[3] =  अणु 114711111, 108333333,  97500000 पूर्ण;
	u32 rates_106[3] =  अणु  40000000,  37777777,  34000000 पूर्ण;
	u32 rates_52[3]  =  अणु  18820000,  17777777,  16000000 पूर्ण;
	u32 rates_26[3]  =  अणु   9411111,   8888888,   8000000 पूर्ण;
	u64 पंचांगp;
	u32 result;

	अगर (WARN_ON_ONCE(rate->mcs > 13))
		वापस 0;

	अगर (WARN_ON_ONCE(rate->he_gi > NL80211_RATE_INFO_HE_GI_3_2))
		वापस 0;
	अगर (WARN_ON_ONCE(rate->he_ru_alloc >
			 NL80211_RATE_INFO_HE_RU_ALLOC_2x996))
		वापस 0;
	अगर (WARN_ON_ONCE(rate->nss < 1 || rate->nss > 8))
		वापस 0;

	अगर (rate->bw == RATE_INFO_BW_160)
		result = rates_160M[rate->he_gi];
	अन्यथा अगर (rate->bw == RATE_INFO_BW_80 ||
		 (rate->bw == RATE_INFO_BW_HE_RU &&
		  rate->he_ru_alloc == NL80211_RATE_INFO_HE_RU_ALLOC_996))
		result = rates_969[rate->he_gi];
	अन्यथा अगर (rate->bw == RATE_INFO_BW_40 ||
		 (rate->bw == RATE_INFO_BW_HE_RU &&
		  rate->he_ru_alloc == NL80211_RATE_INFO_HE_RU_ALLOC_484))
		result = rates_484[rate->he_gi];
	अन्यथा अगर (rate->bw == RATE_INFO_BW_20 ||
		 (rate->bw == RATE_INFO_BW_HE_RU &&
		  rate->he_ru_alloc == NL80211_RATE_INFO_HE_RU_ALLOC_242))
		result = rates_242[rate->he_gi];
	अन्यथा अगर (rate->bw == RATE_INFO_BW_HE_RU &&
		 rate->he_ru_alloc == NL80211_RATE_INFO_HE_RU_ALLOC_106)
		result = rates_106[rate->he_gi];
	अन्यथा अगर (rate->bw == RATE_INFO_BW_HE_RU &&
		 rate->he_ru_alloc == NL80211_RATE_INFO_HE_RU_ALLOC_52)
		result = rates_52[rate->he_gi];
	अन्यथा अगर (rate->bw == RATE_INFO_BW_HE_RU &&
		 rate->he_ru_alloc == NL80211_RATE_INFO_HE_RU_ALLOC_26)
		result = rates_26[rate->he_gi];
	अन्यथा अणु
		WARN(1, "invalid HE MCS: bw:%d, ru:%d\n",
		     rate->bw, rate->he_ru_alloc);
		वापस 0;
	पूर्ण

	/* now scale to the appropriate MCS */
	पंचांगp = result;
	पंचांगp *= SCALE;
	करो_भाग(पंचांगp, mcs_भागisors[rate->mcs]);
	result = पंचांगp;

	/* and take NSS, DCM पूर्णांकo account */
	result = (result * rate->nss) / 8;
	अगर (rate->he_dcm)
		result /= 2;

	वापस result / 10000;
पूर्ण

u32 cfg80211_calculate_bitrate(काष्ठा rate_info *rate)
अणु
	अगर (rate->flags & RATE_INFO_FLAGS_MCS)
		वापस cfg80211_calculate_bitrate_ht(rate);
	अगर (rate->flags & RATE_INFO_FLAGS_DMG)
		वापस cfg80211_calculate_bitrate_dmg(rate);
	अगर (rate->flags & RATE_INFO_FLAGS_EXTENDED_SC_DMG)
		वापस cfg80211_calculate_bitrate_extended_sc_dmg(rate);
	अगर (rate->flags & RATE_INFO_FLAGS_EDMG)
		वापस cfg80211_calculate_bitrate_edmg(rate);
	अगर (rate->flags & RATE_INFO_FLAGS_VHT_MCS)
		वापस cfg80211_calculate_bitrate_vht(rate);
	अगर (rate->flags & RATE_INFO_FLAGS_HE_MCS)
		वापस cfg80211_calculate_bitrate_he(rate);

	वापस rate->legacy;
पूर्ण
EXPORT_SYMBOL(cfg80211_calculate_bitrate);

पूर्णांक cfg80211_get_p2p_attr(स्थिर u8 *ies, अचिन्हित पूर्णांक len,
			  क्रमागत ieee80211_p2p_attr_id attr,
			  u8 *buf, अचिन्हित पूर्णांक bufsize)
अणु
	u8 *out = buf;
	u16 attr_reमुख्यing = 0;
	bool desired_attr = false;
	u16 desired_len = 0;

	जबतक (len > 0) अणु
		अचिन्हित पूर्णांक iedatalen;
		अचिन्हित पूर्णांक copy;
		स्थिर u8 *iedata;

		अगर (len < 2)
			वापस -EILSEQ;
		iedatalen = ies[1];
		अगर (iedatalen + 2 > len)
			वापस -EILSEQ;

		अगर (ies[0] != WLAN_EID_VENDOR_SPECIFIC)
			जाओ cont;

		अगर (iedatalen < 4)
			जाओ cont;

		iedata = ies + 2;

		/* check WFA OUI, P2P subtype */
		अगर (iedata[0] != 0x50 || iedata[1] != 0x6f ||
		    iedata[2] != 0x9a || iedata[3] != 0x09)
			जाओ cont;

		iedatalen -= 4;
		iedata += 4;

		/* check attribute continuation पूर्णांकo this IE */
		copy = min_t(अचिन्हित पूर्णांक, attr_reमुख्यing, iedatalen);
		अगर (copy && desired_attr) अणु
			desired_len += copy;
			अगर (out) अणु
				स_नकल(out, iedata, min(bufsize, copy));
				out += min(bufsize, copy);
				bufsize -= min(bufsize, copy);
			पूर्ण


			अगर (copy == attr_reमुख्यing)
				वापस desired_len;
		पूर्ण

		attr_reमुख्यing -= copy;
		अगर (attr_reमुख्यing)
			जाओ cont;

		iedatalen -= copy;
		iedata += copy;

		जबतक (iedatalen > 0) अणु
			u16 attr_len;

			/* P2P attribute ID & size must fit */
			अगर (iedatalen < 3)
				वापस -EILSEQ;
			desired_attr = iedata[0] == attr;
			attr_len = get_unaligned_le16(iedata + 1);
			iedatalen -= 3;
			iedata += 3;

			copy = min_t(अचिन्हित पूर्णांक, attr_len, iedatalen);

			अगर (desired_attr) अणु
				desired_len += copy;
				अगर (out) अणु
					स_नकल(out, iedata, min(bufsize, copy));
					out += min(bufsize, copy);
					bufsize -= min(bufsize, copy);
				पूर्ण

				अगर (copy == attr_len)
					वापस desired_len;
			पूर्ण

			iedata += copy;
			iedatalen -= copy;
			attr_reमुख्यing = attr_len - copy;
		पूर्ण

 cont:
		len -= ies[1] + 2;
		ies += ies[1] + 2;
	पूर्ण

	अगर (attr_reमुख्यing && desired_attr)
		वापस -EILSEQ;

	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL(cfg80211_get_p2p_attr);

अटल bool ieee80211_id_in_list(स्थिर u8 *ids, पूर्णांक n_ids, u8 id, bool id_ext)
अणु
	पूर्णांक i;

	/* Make sure array values are legal */
	अगर (WARN_ON(ids[n_ids - 1] == WLAN_EID_EXTENSION))
		वापस false;

	i = 0;
	जबतक (i < n_ids) अणु
		अगर (ids[i] == WLAN_EID_EXTENSION) अणु
			अगर (id_ext && (ids[i + 1] == id))
				वापस true;

			i += 2;
			जारी;
		पूर्ण

		अगर (ids[i] == id && !id_ext)
			वापस true;

		i++;
	पूर्ण
	वापस false;
पूर्ण

अटल माप_प्रकार skip_ie(स्थिर u8 *ies, माप_प्रकार ielen, माप_प्रकार pos)
अणु
	/* we assume a validly क्रमmed IEs buffer */
	u8 len = ies[pos + 1];

	pos += 2 + len;

	/* the IE itself must have 255 bytes क्रम fragments to follow */
	अगर (len < 255)
		वापस pos;

	जबतक (pos < ielen && ies[pos] == WLAN_EID_FRAGMENT) अणु
		len = ies[pos + 1];
		pos += 2 + len;
	पूर्ण

	वापस pos;
पूर्ण

माप_प्रकार ieee80211_ie_split_ric(स्थिर u8 *ies, माप_प्रकार ielen,
			      स्थिर u8 *ids, पूर्णांक n_ids,
			      स्थिर u8 *after_ric, पूर्णांक n_after_ric,
			      माप_प्रकार offset)
अणु
	माप_प्रकार pos = offset;

	जबतक (pos < ielen) अणु
		u8 ext = 0;

		अगर (ies[pos] == WLAN_EID_EXTENSION)
			ext = 2;
		अगर ((pos + ext) >= ielen)
			अवरोध;

		अगर (!ieee80211_id_in_list(ids, n_ids, ies[pos + ext],
					  ies[pos] == WLAN_EID_EXTENSION))
			अवरोध;

		अगर (ies[pos] == WLAN_EID_RIC_DATA && n_after_ric) अणु
			pos = skip_ie(ies, ielen, pos);

			जबतक (pos < ielen) अणु
				अगर (ies[pos] == WLAN_EID_EXTENSION)
					ext = 2;
				अन्यथा
					ext = 0;

				अगर ((pos + ext) >= ielen)
					अवरोध;

				अगर (!ieee80211_id_in_list(after_ric,
							  n_after_ric,
							  ies[pos + ext],
							  ext == 2))
					pos = skip_ie(ies, ielen, pos);
				अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			pos = skip_ie(ies, ielen, pos);
		पूर्ण
	पूर्ण

	वापस pos;
पूर्ण
EXPORT_SYMBOL(ieee80211_ie_split_ric);

bool ieee80211_operating_class_to_band(u8 operating_class,
				       क्रमागत nl80211_band *band)
अणु
	चयन (operating_class) अणु
	हाल 112:
	हाल 115 ... 127:
	हाल 128 ... 130:
		*band = NL80211_BAND_5GHZ;
		वापस true;
	हाल 131 ... 135:
		*band = NL80211_BAND_6GHZ;
		वापस true;
	हाल 81:
	हाल 82:
	हाल 83:
	हाल 84:
		*band = NL80211_BAND_2GHZ;
		वापस true;
	हाल 180:
		*band = NL80211_BAND_60GHZ;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(ieee80211_operating_class_to_band);

bool ieee80211_chandef_to_operating_class(काष्ठा cfg80211_chan_def *chandef,
					  u8 *op_class)
अणु
	u8 vht_opclass;
	u32 freq = chandef->center_freq1;

	अगर (freq >= 2412 && freq <= 2472) अणु
		अगर (chandef->width > NL80211_CHAN_WIDTH_40)
			वापस false;

		/* 2.407 GHz, channels 1..13 */
		अगर (chandef->width == NL80211_CHAN_WIDTH_40) अणु
			अगर (freq > chandef->chan->center_freq)
				*op_class = 83; /* HT40+ */
			अन्यथा
				*op_class = 84; /* HT40- */
		पूर्ण अन्यथा अणु
			*op_class = 81;
		पूर्ण

		वापस true;
	पूर्ण

	अगर (freq == 2484) अणु
		/* channel 14 is only क्रम IEEE 802.11b */
		अगर (chandef->width != NL80211_CHAN_WIDTH_20_NOHT)
			वापस false;

		*op_class = 82; /* channel 14 */
		वापस true;
	पूर्ण

	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_80:
		vht_opclass = 128;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_160:
		vht_opclass = 129;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80P80:
		vht_opclass = 130;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_10:
	हाल NL80211_CHAN_WIDTH_5:
		वापस false; /* unsupported क्रम now */
	शेष:
		vht_opclass = 0;
		अवरोध;
	पूर्ण

	/* 5 GHz, channels 36..48 */
	अगर (freq >= 5180 && freq <= 5240) अणु
		अगर (vht_opclass) अणु
			*op_class = vht_opclass;
		पूर्ण अन्यथा अगर (chandef->width == NL80211_CHAN_WIDTH_40) अणु
			अगर (freq > chandef->chan->center_freq)
				*op_class = 116;
			अन्यथा
				*op_class = 117;
		पूर्ण अन्यथा अणु
			*op_class = 115;
		पूर्ण

		वापस true;
	पूर्ण

	/* 5 GHz, channels 52..64 */
	अगर (freq >= 5260 && freq <= 5320) अणु
		अगर (vht_opclass) अणु
			*op_class = vht_opclass;
		पूर्ण अन्यथा अगर (chandef->width == NL80211_CHAN_WIDTH_40) अणु
			अगर (freq > chandef->chan->center_freq)
				*op_class = 119;
			अन्यथा
				*op_class = 120;
		पूर्ण अन्यथा अणु
			*op_class = 118;
		पूर्ण

		वापस true;
	पूर्ण

	/* 5 GHz, channels 100..144 */
	अगर (freq >= 5500 && freq <= 5720) अणु
		अगर (vht_opclass) अणु
			*op_class = vht_opclass;
		पूर्ण अन्यथा अगर (chandef->width == NL80211_CHAN_WIDTH_40) अणु
			अगर (freq > chandef->chan->center_freq)
				*op_class = 122;
			अन्यथा
				*op_class = 123;
		पूर्ण अन्यथा अणु
			*op_class = 121;
		पूर्ण

		वापस true;
	पूर्ण

	/* 5 GHz, channels 149..169 */
	अगर (freq >= 5745 && freq <= 5845) अणु
		अगर (vht_opclass) अणु
			*op_class = vht_opclass;
		पूर्ण अन्यथा अगर (chandef->width == NL80211_CHAN_WIDTH_40) अणु
			अगर (freq > chandef->chan->center_freq)
				*op_class = 126;
			अन्यथा
				*op_class = 127;
		पूर्ण अन्यथा अगर (freq <= 5805) अणु
			*op_class = 124;
		पूर्ण अन्यथा अणु
			*op_class = 125;
		पूर्ण

		वापस true;
	पूर्ण

	/* 56.16 GHz, channel 1..4 */
	अगर (freq >= 56160 + 2160 * 1 && freq <= 56160 + 2160 * 6) अणु
		अगर (chandef->width >= NL80211_CHAN_WIDTH_40)
			वापस false;

		*op_class = 180;
		वापस true;
	पूर्ण

	/* not supported yet */
	वापस false;
पूर्ण
EXPORT_SYMBOL(ieee80211_chandef_to_operating_class);

अटल व्योम cfg80211_calculate_bi_data(काष्ठा wiphy *wiphy, u32 new_beacon_पूर्णांक,
				       u32 *beacon_पूर्णांक_gcd,
				       bool *beacon_पूर्णांक_dअगरferent)
अणु
	काष्ठा wireless_dev *wdev;

	*beacon_पूर्णांक_gcd = 0;
	*beacon_पूर्णांक_dअगरferent = false;

	list_क्रम_each_entry(wdev, &wiphy->wdev_list, list) अणु
		अगर (!wdev->beacon_पूर्णांकerval)
			जारी;

		अगर (!*beacon_पूर्णांक_gcd) अणु
			*beacon_पूर्णांक_gcd = wdev->beacon_पूर्णांकerval;
			जारी;
		पूर्ण

		अगर (wdev->beacon_पूर्णांकerval == *beacon_पूर्णांक_gcd)
			जारी;

		*beacon_पूर्णांक_dअगरferent = true;
		*beacon_पूर्णांक_gcd = gcd(*beacon_पूर्णांक_gcd, wdev->beacon_पूर्णांकerval);
	पूर्ण

	अगर (new_beacon_पूर्णांक && *beacon_पूर्णांक_gcd != new_beacon_पूर्णांक) अणु
		अगर (*beacon_पूर्णांक_gcd)
			*beacon_पूर्णांक_dअगरferent = true;
		*beacon_पूर्णांक_gcd = gcd(*beacon_पूर्णांक_gcd, new_beacon_पूर्णांक);
	पूर्ण
पूर्ण

पूर्णांक cfg80211_validate_beacon_पूर्णांक(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 क्रमागत nl80211_अगरtype अगरtype, u32 beacon_पूर्णांक)
अणु
	/*
	 * This is just a basic pre-condition check; अगर पूर्णांकerface combinations
	 * are possible the driver must alपढ़ोy be checking those with a call
	 * to cfg80211_check_combinations(), in which हाल we'll validate more
	 * through the cfg80211_calculate_bi_data() call and code in
	 * cfg80211_iter_combinations().
	 */

	अगर (beacon_पूर्णांक < 10 || beacon_पूर्णांक > 10000)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक cfg80211_iter_combinations(काष्ठा wiphy *wiphy,
			       काष्ठा अगरace_combination_params *params,
			       व्योम (*iter)(स्थिर काष्ठा ieee80211_अगरace_combination *c,
					    व्योम *data),
			       व्योम *data)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regकरोm;
	क्रमागत nl80211_dfs_regions region = 0;
	पूर्णांक i, j, अगरtype;
	पूर्णांक num_पूर्णांकerfaces = 0;
	u32 used_अगरtypes = 0;
	u32 beacon_पूर्णांक_gcd;
	bool beacon_पूर्णांक_dअगरferent;

	/*
	 * This is a bit strange, since the iteration used to rely only on
	 * the data given by the driver, but here it now relies on context,
	 * in क्रमm of the currently operating पूर्णांकerfaces.
	 * This is OK क्रम all current users, and saves us from having to
	 * push the GCD calculations पूर्णांकo all the drivers.
	 * In the future, this should probably rely more on data that's in
	 * cfg80211 alपढ़ोy - the only thing not would appear to be any new
	 * पूर्णांकerfaces (जबतक being brought up) and channel/radar data.
	 */
	cfg80211_calculate_bi_data(wiphy, params->new_beacon_पूर्णांक,
				   &beacon_पूर्णांक_gcd, &beacon_पूर्णांक_dअगरferent);

	अगर (params->radar_detect) अणु
		rcu_पढ़ो_lock();
		regकरोm = rcu_dereference(cfg80211_regकरोमुख्य);
		अगर (regकरोm)
			region = regकरोm->dfs_region;
		rcu_पढ़ो_unlock();
	पूर्ण

	क्रम (अगरtype = 0; अगरtype < NUM_NL80211_IFTYPES; अगरtype++) अणु
		num_पूर्णांकerfaces += params->अगरtype_num[अगरtype];
		अगर (params->अगरtype_num[अगरtype] > 0 &&
		    !cfg80211_अगरtype_allowed(wiphy, अगरtype, 0, 1))
			used_अगरtypes |= BIT(अगरtype);
	पूर्ण

	क्रम (i = 0; i < wiphy->n_अगरace_combinations; i++) अणु
		स्थिर काष्ठा ieee80211_अगरace_combination *c;
		काष्ठा ieee80211_अगरace_limit *limits;
		u32 all_अगरtypes = 0;

		c = &wiphy->अगरace_combinations[i];

		अगर (num_पूर्णांकerfaces > c->max_पूर्णांकerfaces)
			जारी;
		अगर (params->num_dअगरferent_channels > c->num_dअगरferent_channels)
			जारी;

		limits = kmemdup(c->limits, माप(limits[0]) * c->n_limits,
				 GFP_KERNEL);
		अगर (!limits)
			वापस -ENOMEM;

		क्रम (अगरtype = 0; अगरtype < NUM_NL80211_IFTYPES; अगरtype++) अणु
			अगर (cfg80211_अगरtype_allowed(wiphy, अगरtype, 0, 1))
				जारी;
			क्रम (j = 0; j < c->n_limits; j++) अणु
				all_अगरtypes |= limits[j].types;
				अगर (!(limits[j].types & BIT(अगरtype)))
					जारी;
				अगर (limits[j].max < params->अगरtype_num[अगरtype])
					जाओ cont;
				limits[j].max -= params->अगरtype_num[अगरtype];
			पूर्ण
		पूर्ण

		अगर (params->radar_detect !=
			(c->radar_detect_widths & params->radar_detect))
			जाओ cont;

		अगर (params->radar_detect && c->radar_detect_regions &&
		    !(c->radar_detect_regions & BIT(region)))
			जाओ cont;

		/* Finally check that all अगरtypes that we're currently
		 * using are actually part of this combination. If they
		 * aren't then we can't use this combination and have
		 * to जारी to the next.
		 */
		अगर ((all_अगरtypes & used_अगरtypes) != used_अगरtypes)
			जाओ cont;

		अगर (beacon_पूर्णांक_gcd) अणु
			अगर (c->beacon_पूर्णांक_min_gcd &&
			    beacon_पूर्णांक_gcd < c->beacon_पूर्णांक_min_gcd)
				जाओ cont;
			अगर (!c->beacon_पूर्णांक_min_gcd && beacon_पूर्णांक_dअगरferent)
				जाओ cont;
		पूर्ण

		/* This combination covered all पूर्णांकerface types and
		 * supported the requested numbers, so we're good.
		 */

		(*iter)(c, data);
 cont:
		kमुक्त(limits);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cfg80211_iter_combinations);

अटल व्योम
cfg80211_iter_sum_अगरcombs(स्थिर काष्ठा ieee80211_अगरace_combination *c,
			  व्योम *data)
अणु
	पूर्णांक *num = data;
	(*num)++;
पूर्ण

पूर्णांक cfg80211_check_combinations(काष्ठा wiphy *wiphy,
				काष्ठा अगरace_combination_params *params)
अणु
	पूर्णांक err, num = 0;

	err = cfg80211_iter_combinations(wiphy, params,
					 cfg80211_iter_sum_अगरcombs, &num);
	अगर (err)
		वापस err;
	अगर (num == 0)
		वापस -EBUSY;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cfg80211_check_combinations);

पूर्णांक ieee80211_get_ratemask(काष्ठा ieee80211_supported_band *sband,
			   स्थिर u8 *rates, अचिन्हित पूर्णांक n_rates,
			   u32 *mask)
अणु
	पूर्णांक i, j;

	अगर (!sband)
		वापस -EINVAL;

	अगर (n_rates == 0 || n_rates > NL80211_MAX_SUPP_RATES)
		वापस -EINVAL;

	*mask = 0;

	क्रम (i = 0; i < n_rates; i++) अणु
		पूर्णांक rate = (rates[i] & 0x7f) * 5;
		bool found = false;

		क्रम (j = 0; j < sband->n_bitrates; j++) अणु
			अगर (sband->bitrates[j].bitrate == rate) अणु
				found = true;
				*mask |= BIT(j);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!found)
			वापस -EINVAL;
	पूर्ण

	/*
	 * mask must have at least one bit set here since we
	 * didn't accept a 0-length rates array nor allowed
	 * entries in the array that didn't exist
	 */

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक ieee80211_get_num_supported_channels(काष्ठा wiphy *wiphy)
अणु
	क्रमागत nl80211_band band;
	अचिन्हित पूर्णांक n_channels = 0;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++)
		अगर (wiphy->bands[band])
			n_channels += wiphy->bands[band]->n_channels;

	वापस n_channels;
पूर्ण
EXPORT_SYMBOL(ieee80211_get_num_supported_channels);

पूर्णांक cfg80211_get_station(काष्ठा net_device *dev, स्थिर u8 *mac_addr,
			 काष्ठा station_info *sinfo)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wireless_dev *wdev;

	wdev = dev->ieee80211_ptr;
	अगर (!wdev)
		वापस -EOPNOTSUPP;

	rdev = wiphy_to_rdev(wdev->wiphy);
	अगर (!rdev->ops->get_station)
		वापस -EOPNOTSUPP;

	स_रखो(sinfo, 0, माप(*sinfo));

	वापस rdev_get_station(rdev, dev, mac_addr, sinfo);
पूर्ण
EXPORT_SYMBOL(cfg80211_get_station);

व्योम cfg80211_मुक्त_nan_func(काष्ठा cfg80211_nan_func *f)
अणु
	पूर्णांक i;

	अगर (!f)
		वापस;

	kमुक्त(f->serv_spec_info);
	kमुक्त(f->srf_bf);
	kमुक्त(f->srf_macs);
	क्रम (i = 0; i < f->num_rx_filters; i++)
		kमुक्त(f->rx_filters[i].filter);

	क्रम (i = 0; i < f->num_tx_filters; i++)
		kमुक्त(f->tx_filters[i].filter);

	kमुक्त(f->rx_filters);
	kमुक्त(f->tx_filters);
	kमुक्त(f);
पूर्ण
EXPORT_SYMBOL(cfg80211_मुक्त_nan_func);

bool cfg80211_करोes_bw_fit_range(स्थिर काष्ठा ieee80211_freq_range *freq_range,
				u32 center_freq_khz, u32 bw_khz)
अणु
	u32 start_freq_khz, end_freq_khz;

	start_freq_khz = center_freq_khz - (bw_khz / 2);
	end_freq_khz = center_freq_khz + (bw_khz / 2);

	अगर (start_freq_khz >= freq_range->start_freq_khz &&
	    end_freq_khz <= freq_range->end_freq_khz)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक cfg80211_sinfo_alloc_tid_stats(काष्ठा station_info *sinfo, gfp_t gfp)
अणु
	sinfo->pertid = kसुस्मृति(IEEE80211_NUM_TIDS + 1,
				माप(*(sinfo->pertid)),
				gfp);
	अगर (!sinfo->pertid)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cfg80211_sinfo_alloc_tid_stats);

/* See IEEE 802.1H क्रम LLC/SNAP encapsulation/decapsulation */
/* Ethernet-II snap header (RFC1042 क्रम most EtherTypes) */
स्थिर अचिन्हित अक्षर rfc1042_header[] __aligned(2) =
	अणु 0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00 पूर्ण;
EXPORT_SYMBOL(rfc1042_header);

/* Bridge-Tunnel header (क्रम EtherTypes ETH_P_AARP and ETH_P_IPX) */
स्थिर अचिन्हित अक्षर bridge_tunnel_header[] __aligned(2) =
	अणु 0xaa, 0xaa, 0x03, 0x00, 0x00, 0xf8 पूर्ण;
EXPORT_SYMBOL(bridge_tunnel_header);

/* Layer 2 Update frame (802.2 Type 1 LLC XID Update response) */
काष्ठा iapp_layer2_update अणु
	u8 da[ETH_ALEN];	/* broadcast */
	u8 sa[ETH_ALEN];	/* STA addr */
	__be16 len;		/* 6 */
	u8 dsap;		/* 0 */
	u8 ssap;		/* 0 */
	u8 control;
	u8 xid_info[3];
पूर्ण __packed;

व्योम cfg80211_send_layer2_update(काष्ठा net_device *dev, स्थिर u8 *addr)
अणु
	काष्ठा iapp_layer2_update *msg;
	काष्ठा sk_buff *skb;

	/* Send Level 2 Update Frame to update क्रमwarding tables in layer 2
	 * bridge devices */

	skb = dev_alloc_skb(माप(*msg));
	अगर (!skb)
		वापस;
	msg = skb_put(skb, माप(*msg));

	/* 802.2 Type 1 Logical Link Control (LLC) Exchange Identअगरier (XID)
	 * Update response frame; IEEE Std 802.2-1998, 5.4.1.2.1 */

	eth_broadcast_addr(msg->da);
	ether_addr_copy(msg->sa, addr);
	msg->len = htons(6);
	msg->dsap = 0;
	msg->ssap = 0x01;	/* शून्य LSAP, CR Bit: Response */
	msg->control = 0xaf;	/* XID response lsb.1111F101.
				 * F=0 (no poll command; unsolicited frame) */
	msg->xid_info[0] = 0x81;	/* XID क्रमmat identअगरier */
	msg->xid_info[1] = 1;	/* LLC types/classes: Type 1 LLC */
	msg->xid_info[2] = 0;	/* XID sender's receive winकरोw size (RW) */

	skb->dev = dev;
	skb->protocol = eth_type_trans(skb, dev);
	स_रखो(skb->cb, 0, माप(skb->cb));
	netअगर_rx_ni(skb);
पूर्ण
EXPORT_SYMBOL(cfg80211_send_layer2_update);

पूर्णांक ieee80211_get_vht_max_nss(काष्ठा ieee80211_vht_cap *cap,
			      क्रमागत ieee80211_vht_chanwidth bw,
			      पूर्णांक mcs, bool ext_nss_bw_capable,
			      अचिन्हित पूर्णांक max_vht_nss)
अणु
	u16 map = le16_to_cpu(cap->supp_mcs.rx_mcs_map);
	पूर्णांक ext_nss_bw;
	पूर्णांक supp_width;
	पूर्णांक i, mcs_encoding;

	अगर (map == 0xffff)
		वापस 0;

	अगर (WARN_ON(mcs > 9 || max_vht_nss > 8))
		वापस 0;
	अगर (mcs <= 7)
		mcs_encoding = 0;
	अन्यथा अगर (mcs == 8)
		mcs_encoding = 1;
	अन्यथा
		mcs_encoding = 2;

	अगर (!max_vht_nss) अणु
		/* find max_vht_nss क्रम the given MCS */
		क्रम (i = 7; i >= 0; i--) अणु
			पूर्णांक supp = (map >> (2 * i)) & 3;

			अगर (supp == 3)
				जारी;

			अगर (supp >= mcs_encoding) अणु
				max_vht_nss = i + 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!(cap->supp_mcs.tx_mcs_map &
			cpu_to_le16(IEEE80211_VHT_EXT_NSS_BW_CAPABLE)))
		वापस max_vht_nss;

	ext_nss_bw = le32_get_bits(cap->vht_cap_info,
				   IEEE80211_VHT_CAP_EXT_NSS_BW_MASK);
	supp_width = le32_get_bits(cap->vht_cap_info,
				   IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK);

	/* अगर not capable, treat ext_nss_bw as 0 */
	अगर (!ext_nss_bw_capable)
		ext_nss_bw = 0;

	/* This is invalid */
	अगर (supp_width == 3)
		वापस 0;

	/* This is an invalid combination so pretend nothing is supported */
	अगर (supp_width == 2 && (ext_nss_bw == 1 || ext_nss_bw == 2))
		वापस 0;

	/*
	 * Cover all the special हालs according to IEEE 802.11-2016
	 * Table 9-250. All other हालs are either factor of 1 or not
	 * valid/supported.
	 */
	चयन (bw) अणु
	हाल IEEE80211_VHT_CHANWIDTH_USE_HT:
	हाल IEEE80211_VHT_CHANWIDTH_80MHZ:
		अगर ((supp_width == 1 || supp_width == 2) &&
		    ext_nss_bw == 3)
			वापस 2 * max_vht_nss;
		अवरोध;
	हाल IEEE80211_VHT_CHANWIDTH_160MHZ:
		अगर (supp_width == 0 &&
		    (ext_nss_bw == 1 || ext_nss_bw == 2))
			वापस max_vht_nss / 2;
		अगर (supp_width == 0 &&
		    ext_nss_bw == 3)
			वापस (3 * max_vht_nss) / 4;
		अगर (supp_width == 1 &&
		    ext_nss_bw == 3)
			वापस 2 * max_vht_nss;
		अवरोध;
	हाल IEEE80211_VHT_CHANWIDTH_80P80MHZ:
		अगर (supp_width == 0 && ext_nss_bw == 1)
			वापस 0; /* not possible */
		अगर (supp_width == 0 &&
		    ext_nss_bw == 2)
			वापस max_vht_nss / 2;
		अगर (supp_width == 0 &&
		    ext_nss_bw == 3)
			वापस (3 * max_vht_nss) / 4;
		अगर (supp_width == 1 &&
		    ext_nss_bw == 0)
			वापस 0; /* not possible */
		अगर (supp_width == 1 &&
		    ext_nss_bw == 1)
			वापस max_vht_nss / 2;
		अगर (supp_width == 1 &&
		    ext_nss_bw == 2)
			वापस (3 * max_vht_nss) / 4;
		अवरोध;
	पूर्ण

	/* not covered or invalid combination received */
	वापस max_vht_nss;
पूर्ण
EXPORT_SYMBOL(ieee80211_get_vht_max_nss);

bool cfg80211_अगरtype_allowed(काष्ठा wiphy *wiphy, क्रमागत nl80211_अगरtype अगरtype,
			     bool is_4addr, u8 check_swअगर)

अणु
	bool is_vlan = अगरtype == NL80211_IFTYPE_AP_VLAN;

	चयन (check_swअगर) अणु
	हाल 0:
		अगर (is_vlan && is_4addr)
			वापस wiphy->flags & WIPHY_FLAG_4ADDR_AP;
		वापस wiphy->पूर्णांकerface_modes & BIT(अगरtype);
	हाल 1:
		अगर (!(wiphy->software_अगरtypes & BIT(अगरtype)) && is_vlan)
			वापस wiphy->flags & WIPHY_FLAG_4ADDR_AP;
		वापस wiphy->software_अगरtypes & BIT(अगरtype);
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(cfg80211_अगरtype_allowed);
