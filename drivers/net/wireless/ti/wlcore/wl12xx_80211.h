<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __WL12XX_80211_H__
#घोषणा __WL12XX_80211_H__

#समावेश <linux/अगर_ether.h>	/* ETH_ALEN */
#समावेश <linux/अगर_arp.h>

/* RATES */
#घोषणा IEEE80211_CCK_RATE_1MB		        0x02
#घोषणा IEEE80211_CCK_RATE_2MB		        0x04
#घोषणा IEEE80211_CCK_RATE_5MB		        0x0B
#घोषणा IEEE80211_CCK_RATE_11MB		        0x16
#घोषणा IEEE80211_OFDM_RATE_6MB		        0x0C
#घोषणा IEEE80211_OFDM_RATE_9MB		        0x12
#घोषणा IEEE80211_OFDM_RATE_12MB		0x18
#घोषणा IEEE80211_OFDM_RATE_18MB		0x24
#घोषणा IEEE80211_OFDM_RATE_24MB		0x30
#घोषणा IEEE80211_OFDM_RATE_36MB		0x48
#घोषणा IEEE80211_OFDM_RATE_48MB		0x60
#घोषणा IEEE80211_OFDM_RATE_54MB		0x6C
#घोषणा IEEE80211_BASIC_RATE_MASK		0x80

#घोषणा IEEE80211_CCK_RATE_1MB_MASK		(1<<0)
#घोषणा IEEE80211_CCK_RATE_2MB_MASK		(1<<1)
#घोषणा IEEE80211_CCK_RATE_5MB_MASK		(1<<2)
#घोषणा IEEE80211_CCK_RATE_11MB_MASK		(1<<3)
#घोषणा IEEE80211_OFDM_RATE_6MB_MASK		(1<<4)
#घोषणा IEEE80211_OFDM_RATE_9MB_MASK		(1<<5)
#घोषणा IEEE80211_OFDM_RATE_12MB_MASK		(1<<6)
#घोषणा IEEE80211_OFDM_RATE_18MB_MASK		(1<<7)
#घोषणा IEEE80211_OFDM_RATE_24MB_MASK		(1<<8)
#घोषणा IEEE80211_OFDM_RATE_36MB_MASK		(1<<9)
#घोषणा IEEE80211_OFDM_RATE_48MB_MASK		(1<<10)
#घोषणा IEEE80211_OFDM_RATE_54MB_MASK		(1<<11)

#घोषणा IEEE80211_CCK_RATES_MASK	  0x0000000F
#घोषणा IEEE80211_CCK_BASIC_RATES_MASK	 (IEEE80211_CCK_RATE_1MB_MASK | \
	IEEE80211_CCK_RATE_2MB_MASK)
#घोषणा IEEE80211_CCK_DEFAULT_RATES_MASK (IEEE80211_CCK_BASIC_RATES_MASK | \
	IEEE80211_CCK_RATE_5MB_MASK | \
	IEEE80211_CCK_RATE_11MB_MASK)

#घोषणा IEEE80211_OFDM_RATES_MASK	  0x00000FF0
#घोषणा IEEE80211_OFDM_BASIC_RATES_MASK	  (IEEE80211_OFDM_RATE_6MB_MASK | \
	IEEE80211_OFDM_RATE_12MB_MASK | \
	IEEE80211_OFDM_RATE_24MB_MASK)
#घोषणा IEEE80211_OFDM_DEFAULT_RATES_MASK (IEEE80211_OFDM_BASIC_RATES_MASK | \
	IEEE80211_OFDM_RATE_9MB_MASK  | \
	IEEE80211_OFDM_RATE_18MB_MASK | \
	IEEE80211_OFDM_RATE_36MB_MASK | \
	IEEE80211_OFDM_RATE_48MB_MASK | \
	IEEE80211_OFDM_RATE_54MB_MASK)
#घोषणा IEEE80211_DEFAULT_RATES_MASK (IEEE80211_OFDM_DEFAULT_RATES_MASK | \
				      IEEE80211_CCK_DEFAULT_RATES_MASK)


/* This really should be 8, but not क्रम our firmware */
#घोषणा MAX_SUPPORTED_RATES 32
#घोषणा MAX_COUNTRY_TRIPLETS 32

/* Headers */
काष्ठा ieee80211_header अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 da[ETH_ALEN];
	u8 sa[ETH_ALEN];
	u8 bssid[ETH_ALEN];
	__le16 seq_ctl;
	u8 payload[];
पूर्ण __packed;

काष्ठा wl12xx_ie_header अणु
	u8 id;
	u8 len;
पूर्ण __packed;

/* IEs */

काष्ठा wl12xx_ie_ssid अणु
	काष्ठा wl12xx_ie_header header;
	अक्षर ssid[IEEE80211_MAX_SSID_LEN];
पूर्ण __packed;

काष्ठा wl12xx_ie_rates अणु
	काष्ठा wl12xx_ie_header header;
	u8 rates[MAX_SUPPORTED_RATES];
पूर्ण __packed;

काष्ठा wl12xx_ie_ds_params अणु
	काष्ठा wl12xx_ie_header header;
	u8 channel;
पूर्ण __packed;

काष्ठा country_triplet अणु
	u8 channel;
	u8 num_channels;
	u8 max_tx_घातer;
पूर्ण __packed;

काष्ठा wl12xx_ie_country अणु
	काष्ठा wl12xx_ie_header header;
	u8 country_string[IEEE80211_COUNTRY_STRING_LEN];
	काष्ठा country_triplet triplets[MAX_COUNTRY_TRIPLETS];
पूर्ण __packed;


/* Templates */

काष्ठा wl12xx_null_data_ढाँचा अणु
	काष्ठा ieee80211_header header;
पूर्ण __packed;

काष्ठा wl12xx_ps_poll_ढाँचा अणु
	__le16 fc;
	__le16 aid;
	u8 bssid[ETH_ALEN];
	u8 ta[ETH_ALEN];
पूर्ण __packed;

काष्ठा wl12xx_arp_rsp_ढाँचा अणु
	/* not including ieee80211 header */

	u8 llc_hdr[माप(rfc1042_header)];
	__be16 llc_type;

	काष्ठा arphdr arp_hdr;
	u8 sender_hw[ETH_ALEN];
	__be32 sender_ip;
	u8 target_hw[ETH_ALEN];
	__be32 target_ip;
पूर्ण __packed;

काष्ठा wl12xx_disconn_ढाँचा अणु
	काष्ठा ieee80211_header header;
	__le16 disconn_reason;
पूर्ण __packed;

#पूर्ण_अगर
