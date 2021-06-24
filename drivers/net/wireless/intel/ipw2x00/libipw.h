<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Merged with मुख्यline ieee80211.h in Aug 2004.  Original ieee802_11
 * reमुख्यs copyright by the original authors
 *
 * Portions of the merged code are based on Host AP (software wireless
 * LAN access poपूर्णांक) driver क्रम Intersil Prism2/2.5/3.
 *
 * Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
 * <j@w1.fi>
 * Copyright (c) 2002-2003, Jouni Malinen <j@w1.fi>
 *
 * Adaption to a generic IEEE 802.11 stack by James Ketrenos
 * <jketreno@linux.पूर्णांकel.com>
 * Copyright (c) 2004-2005, Intel Corporation
 *
 * API Version History
 * 1.0.x -- Initial version
 * 1.1.x -- Added radiotap, QoS, TIM, libipw_geo APIs,
 *          various काष्ठाure changes, and crypto API init method
 */
#अगर_अघोषित LIBIPW_H
#घोषणा LIBIPW_H
#समावेश <linux/अगर_ether.h>	/* ETH_ALEN */
#समावेश <linux/kernel.h>	/* ARRAY_SIZE */
#समावेश <linux/wireless.h>
#समावेश <linux/ieee80211.h>

#समावेश <net/lib80211.h>
#समावेश <net/cfg80211.h>

#घोषणा LIBIPW_VERSION "git-1.1.13"

#घोषणा LIBIPW_DATA_LEN		2304
/* Maximum size क्रम the MA-UNITDATA primitive, 802.11 standard section
   6.2.1.1.2.

   The figure in section 7.1.2 suggests a body size of up to 2312
   bytes is allowed, which is a bit confusing, I suspect this
   represents the 2304 bytes of real data, plus a possible 8 bytes of
   WEP IV and ICV. (this पूर्णांकerpretation suggested by Ramiro Barreiro) */

#घोषणा LIBIPW_1ADDR_LEN 10
#घोषणा LIBIPW_2ADDR_LEN 16
#घोषणा LIBIPW_3ADDR_LEN 24
#घोषणा LIBIPW_4ADDR_LEN 30
#घोषणा LIBIPW_FCS_LEN    4
#घोषणा LIBIPW_HLEN			(LIBIPW_4ADDR_LEN)
#घोषणा LIBIPW_FRAME_LEN		(LIBIPW_DATA_LEN + LIBIPW_HLEN)

#घोषणा MIN_FRAG_THRESHOLD     256U
#घोषणा	MAX_FRAG_THRESHOLD     2346U

/* QOS control */
#घोषणा LIBIPW_QCTL_TID		0x000F

/* debug macros */

#अगर_घोषित CONFIG_LIBIPW_DEBUG
बाह्य u32 libipw_debug_level;
#घोषणा LIBIPW_DEBUG(level, fmt, args...) \
करो अणु अगर (libipw_debug_level & (level)) \
  prपूर्णांकk(KERN_DEBUG "libipw: %s " fmt, __func__ , ## args); पूर्ण जबतक (0)
#अन्यथा
#घोषणा LIBIPW_DEBUG(level, fmt, args...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर				/* CONFIG_LIBIPW_DEBUG */

/*
 * To use the debug प्रणाली:
 *
 * If you are defining a new debug classअगरication, simply add it to the #घोषणा
 * list here in the क्रमm of:
 *
 * #घोषणा LIBIPW_DL_xxxx VALUE
 *
 * shअगरting value to the left one bit from the previous entry.  xxxx should be
 * the name of the classअगरication (क्रम example, WEP)
 *
 * You then need to either add a LIBIPW_xxxx_DEBUG() macro definition क्रम your
 * classअगरication, or use LIBIPW_DEBUG(LIBIPW_DL_xxxx, ...) whenever you want
 * to send output to that classअगरication.
 *
 * To add your debug level to the list of levels seen when you perक्रमm
 *
 * % cat /proc/net/ieee80211/debug_level
 *
 * you simply need to add your entry to the libipw_debug_level array.
 *
 * If you करो not see debug_level in /proc/net/ieee80211 then you करो not have
 * CONFIG_LIBIPW_DEBUG defined in your kernel configuration
 *
 */

#घोषणा LIBIPW_DL_INFO          (1<<0)
#घोषणा LIBIPW_DL_WX            (1<<1)
#घोषणा LIBIPW_DL_SCAN          (1<<2)
#घोषणा LIBIPW_DL_STATE         (1<<3)
#घोषणा LIBIPW_DL_MGMT          (1<<4)
#घोषणा LIBIPW_DL_FRAG          (1<<5)
#घोषणा LIBIPW_DL_DROP          (1<<7)

#घोषणा LIBIPW_DL_TX            (1<<8)
#घोषणा LIBIPW_DL_RX            (1<<9)
#घोषणा LIBIPW_DL_QOS           (1<<31)

#घोषणा LIBIPW_ERROR(f, a...) prपूर्णांकk(KERN_ERR "libipw: " f, ## a)
#घोषणा LIBIPW_WARNING(f, a...) prपूर्णांकk(KERN_WARNING "libipw: " f, ## a)
#घोषणा LIBIPW_DEBUG_INFO(f, a...)   LIBIPW_DEBUG(LIBIPW_DL_INFO, f, ## a)

#घोषणा LIBIPW_DEBUG_WX(f, a...)     LIBIPW_DEBUG(LIBIPW_DL_WX, f, ## a)
#घोषणा LIBIPW_DEBUG_SCAN(f, a...)   LIBIPW_DEBUG(LIBIPW_DL_SCAN, f, ## a)
#घोषणा LIBIPW_DEBUG_STATE(f, a...)  LIBIPW_DEBUG(LIBIPW_DL_STATE, f, ## a)
#घोषणा LIBIPW_DEBUG_MGMT(f, a...)  LIBIPW_DEBUG(LIBIPW_DL_MGMT, f, ## a)
#घोषणा LIBIPW_DEBUG_FRAG(f, a...)  LIBIPW_DEBUG(LIBIPW_DL_FRAG, f, ## a)
#घोषणा LIBIPW_DEBUG_DROP(f, a...)  LIBIPW_DEBUG(LIBIPW_DL_DROP, f, ## a)
#घोषणा LIBIPW_DEBUG_TX(f, a...)  LIBIPW_DEBUG(LIBIPW_DL_TX, f, ## a)
#घोषणा LIBIPW_DEBUG_RX(f, a...)  LIBIPW_DEBUG(LIBIPW_DL_RX, f, ## a)
#घोषणा LIBIPW_DEBUG_QOS(f, a...)  LIBIPW_DEBUG(LIBIPW_DL_QOS, f, ## a)
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>	/* ARPHRD_ETHER */

#अगर_अघोषित WIRELESS_SPY
#घोषणा WIRELESS_SPY		/* enable iwspy support */
#पूर्ण_अगर
#समावेश <net/iw_handler.h>	/* new driver API */

#घोषणा ETH_P_PREAUTH 0x88C7	/* IEEE 802.11i pre-authentication */

#अगर_अघोषित ETH_P_80211_RAW
#घोषणा ETH_P_80211_RAW (ETH_P_ECONET + 1)
#पूर्ण_अगर

/* IEEE 802.11 defines */

#घोषणा P80211_OUI_LEN 3

काष्ठा libipw_snap_hdr अणु

	u8 dsap;		/* always 0xAA */
	u8 ssap;		/* always 0xAA */
	u8 ctrl;		/* always 0x03 */
	u8 oui[P80211_OUI_LEN];	/* organizational universal id */

पूर्ण __packed;

#घोषणा SNAP_SIZE माप(काष्ठा libipw_snap_hdr)

#घोषणा WLAN_FC_GET_VERS(fc) ((fc) & IEEE80211_FCTL_VERS)
#घोषणा WLAN_FC_GET_TYPE(fc) ((fc) & IEEE80211_FCTL_FTYPE)
#घोषणा WLAN_FC_GET_STYPE(fc) ((fc) & IEEE80211_FCTL_STYPE)

#घोषणा WLAN_GET_SEQ_FRAG(seq) ((seq) & IEEE80211_SCTL_FRAG)
#घोषणा WLAN_GET_SEQ_SEQ(seq)  (((seq) & IEEE80211_SCTL_SEQ) >> 4)

#घोषणा LIBIPW_STATMASK_SIGNAL (1<<0)
#घोषणा LIBIPW_STATMASK_RSSI (1<<1)
#घोषणा LIBIPW_STATMASK_NOISE (1<<2)
#घोषणा LIBIPW_STATMASK_RATE (1<<3)
#घोषणा LIBIPW_STATMASK_WEMASK 0x7

#घोषणा LIBIPW_CCK_MODULATION    (1<<0)
#घोषणा LIBIPW_OFDM_MODULATION   (1<<1)

#घोषणा LIBIPW_24GHZ_BAND     (1<<0)
#घोषणा LIBIPW_52GHZ_BAND     (1<<1)

#घोषणा LIBIPW_CCK_RATE_1MB		        0x02
#घोषणा LIBIPW_CCK_RATE_2MB		        0x04
#घोषणा LIBIPW_CCK_RATE_5MB		        0x0B
#घोषणा LIBIPW_CCK_RATE_11MB		        0x16
#घोषणा LIBIPW_OFDM_RATE_6MB		        0x0C
#घोषणा LIBIPW_OFDM_RATE_9MB		        0x12
#घोषणा LIBIPW_OFDM_RATE_12MB		0x18
#घोषणा LIBIPW_OFDM_RATE_18MB		0x24
#घोषणा LIBIPW_OFDM_RATE_24MB		0x30
#घोषणा LIBIPW_OFDM_RATE_36MB		0x48
#घोषणा LIBIPW_OFDM_RATE_48MB		0x60
#घोषणा LIBIPW_OFDM_RATE_54MB		0x6C
#घोषणा LIBIPW_BASIC_RATE_MASK		0x80

#घोषणा LIBIPW_CCK_RATE_1MB_MASK		(1<<0)
#घोषणा LIBIPW_CCK_RATE_2MB_MASK		(1<<1)
#घोषणा LIBIPW_CCK_RATE_5MB_MASK		(1<<2)
#घोषणा LIBIPW_CCK_RATE_11MB_MASK		(1<<3)
#घोषणा LIBIPW_OFDM_RATE_6MB_MASK		(1<<4)
#घोषणा LIBIPW_OFDM_RATE_9MB_MASK		(1<<5)
#घोषणा LIBIPW_OFDM_RATE_12MB_MASK		(1<<6)
#घोषणा LIBIPW_OFDM_RATE_18MB_MASK		(1<<7)
#घोषणा LIBIPW_OFDM_RATE_24MB_MASK		(1<<8)
#घोषणा LIBIPW_OFDM_RATE_36MB_MASK		(1<<9)
#घोषणा LIBIPW_OFDM_RATE_48MB_MASK		(1<<10)
#घोषणा LIBIPW_OFDM_RATE_54MB_MASK		(1<<11)

#घोषणा LIBIPW_CCK_RATES_MASK	        0x0000000F
#घोषणा LIBIPW_CCK_BASIC_RATES_MASK	(LIBIPW_CCK_RATE_1MB_MASK | \
	LIBIPW_CCK_RATE_2MB_MASK)
#घोषणा LIBIPW_CCK_DEFAULT_RATES_MASK	(LIBIPW_CCK_BASIC_RATES_MASK | \
        LIBIPW_CCK_RATE_5MB_MASK | \
        LIBIPW_CCK_RATE_11MB_MASK)

#घोषणा LIBIPW_OFDM_RATES_MASK		0x00000FF0
#घोषणा LIBIPW_OFDM_BASIC_RATES_MASK	(LIBIPW_OFDM_RATE_6MB_MASK | \
	LIBIPW_OFDM_RATE_12MB_MASK | \
	LIBIPW_OFDM_RATE_24MB_MASK)
#घोषणा LIBIPW_OFDM_DEFAULT_RATES_MASK	(LIBIPW_OFDM_BASIC_RATES_MASK | \
	LIBIPW_OFDM_RATE_9MB_MASK  | \
	LIBIPW_OFDM_RATE_18MB_MASK | \
	LIBIPW_OFDM_RATE_36MB_MASK | \
	LIBIPW_OFDM_RATE_48MB_MASK | \
	LIBIPW_OFDM_RATE_54MB_MASK)
#घोषणा LIBIPW_DEFAULT_RATES_MASK (LIBIPW_OFDM_DEFAULT_RATES_MASK | \
                                LIBIPW_CCK_DEFAULT_RATES_MASK)

#घोषणा LIBIPW_NUM_OFDM_RATES	    8
#घोषणा LIBIPW_NUM_CCK_RATES	            4
#घोषणा LIBIPW_OFDM_SHIFT_MASK_A         4

/* NOTE: This data is क्रम statistical purposes; not all hardware provides this
 *       inक्रमmation क्रम frames received.
 *       For libipw_rx_mgt, you need to set at least the 'len' parameter.
 */
काष्ठा libipw_rx_stats अणु
	u32 mac_समय;
	s8 rssi;
	u8 संकेत;
	u8 noise;
	u16 rate;		/* in 100 kbps */
	u8 received_channel;
	u8 control;
	u8 mask;
	u8 freq;
	u16 len;
	u64 tsf;
	u32 beacon_समय;
पूर्ण;

/* IEEE 802.11 requires that STA supports concurrent reception of at least
 * three fragmented frames. This define can be increased to support more
 * concurrent frames, but it should be noted that each entry can consume about
 * 2 kB of RAM and increasing cache size will slow करोwn frame reassembly. */
#घोषणा LIBIPW_FRAG_CACHE_LEN 4

काष्ठा libipw_frag_entry अणु
	अचिन्हित दीर्घ first_frag_समय;
	अचिन्हित पूर्णांक seq;
	अचिन्हित पूर्णांक last_frag;
	काष्ठा sk_buff *skb;
	u8 src_addr[ETH_ALEN];
	u8 dst_addr[ETH_ALEN];
पूर्ण;

काष्ठा libipw_stats अणु
	अचिन्हित पूर्णांक tx_unicast_frames;
	अचिन्हित पूर्णांक tx_multicast_frames;
	अचिन्हित पूर्णांक tx_fragments;
	अचिन्हित पूर्णांक tx_unicast_octets;
	अचिन्हित पूर्णांक tx_multicast_octets;
	अचिन्हित पूर्णांक tx_deferred_transmissions;
	अचिन्हित पूर्णांक tx_single_retry_frames;
	अचिन्हित पूर्णांक tx_multiple_retry_frames;
	अचिन्हित पूर्णांक tx_retry_limit_exceeded;
	अचिन्हित पूर्णांक tx_discards;
	अचिन्हित पूर्णांक rx_unicast_frames;
	अचिन्हित पूर्णांक rx_multicast_frames;
	अचिन्हित पूर्णांक rx_fragments;
	अचिन्हित पूर्णांक rx_unicast_octets;
	अचिन्हित पूर्णांक rx_multicast_octets;
	अचिन्हित पूर्णांक rx_fcs_errors;
	अचिन्हित पूर्णांक rx_discards_no_buffer;
	अचिन्हित पूर्णांक tx_discards_wrong_sa;
	अचिन्हित पूर्णांक rx_discards_undecryptable;
	अचिन्हित पूर्णांक rx_message_in_msg_fragments;
	अचिन्हित पूर्णांक rx_message_in_bad_msg_fragments;
पूर्ण;

काष्ठा libipw_device;

#घोषणा SEC_KEY_1		(1<<0)
#घोषणा SEC_KEY_2		(1<<1)
#घोषणा SEC_KEY_3		(1<<2)
#घोषणा SEC_KEY_4		(1<<3)
#घोषणा SEC_ACTIVE_KEY		(1<<4)
#घोषणा SEC_AUTH_MODE		(1<<5)
#घोषणा SEC_UNICAST_GROUP	(1<<6)
#घोषणा SEC_LEVEL		(1<<7)
#घोषणा SEC_ENABLED		(1<<8)
#घोषणा SEC_ENCRYPT		(1<<9)

#घोषणा SEC_LEVEL_0		0	/* None */
#घोषणा SEC_LEVEL_1		1	/* WEP 40 and 104 bit */
#घोषणा SEC_LEVEL_2		2	/* Level 1 + TKIP */
#घोषणा SEC_LEVEL_2_CKIP	3	/* Level 1 + CKIP */
#घोषणा SEC_LEVEL_3		4	/* Level 2 + CCMP */

#घोषणा SEC_ALG_NONE		0
#घोषणा SEC_ALG_WEP		1
#घोषणा SEC_ALG_TKIP		2
#घोषणा SEC_ALG_CCMP		3

#घोषणा WEP_KEYS		4
#घोषणा WEP_KEY_LEN		13
#घोषणा SCM_KEY_LEN		32
#घोषणा SCM_TEMPORAL_KEY_LENGTH	16

काष्ठा libipw_security अणु
	u16 active_key:2, enabled:1, unicast_uses_group:1, encrypt:1;
	u8 auth_mode;
	u8 encode_alg[WEP_KEYS];
	u8 key_sizes[WEP_KEYS];
	u8 keys[WEP_KEYS][SCM_KEY_LEN];
	u8 level;
	u16 flags;
पूर्ण __packed;

/*

 802.11 data frame from AP

      ,-------------------------------------------------------------------.
Bytes |  2   |  2   |    6    |    6    |    6    |  2   | 0..2312 |   4  |
      |------|------|---------|---------|---------|------|---------|------|
Desc. | ctrl | dura |  DA/RA  |   TA    |    SA   | Sequ |  frame  |  fcs |
      |      | tion | (BSSID) |         |         | ence |  data   |      |
      `-------------------------------------------------------------------'

Total: 28-2340 bytes

*/

#घोषणा BEACON_PROBE_SSID_ID_POSITION 12

काष्ठा libipw_hdr_1addr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 payload[];
पूर्ण __packed;

काष्ठा libipw_hdr_2addr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 payload[];
पूर्ण __packed;

काष्ठा libipw_hdr_3addr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctl;
	u8 payload[];
पूर्ण __packed;

काष्ठा libipw_hdr_4addr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctl;
	u8 addr4[ETH_ALEN];
	u8 payload[];
पूर्ण __packed;

काष्ठा libipw_hdr_3addrqos अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctl;
	u8 payload[0];
	__le16 qos_ctl;
पूर्ण __packed;

काष्ठा libipw_info_element अणु
	u8 id;
	u8 len;
	u8 data[];
पूर्ण __packed;

/*
 * These are the data types that can make up management packets
 *
	u16 auth_algorithm;
	u16 auth_sequence;
	u16 beacon_पूर्णांकerval;
	u16 capability;
	u8 current_ap[ETH_ALEN];
	u16 listen_पूर्णांकerval;
	काष्ठा अणु
		u16 association_id:14, reserved:2;
	पूर्ण __packed;
	u32 समय_stamp[2];
	u16 reason;
	u16 status;
*/

काष्ठा libipw_auth अणु
	काष्ठा libipw_hdr_3addr header;
	__le16 algorithm;
	__le16 transaction;
	__le16 status;
	/* challenge */
	काष्ठा libipw_info_element info_element[];
पूर्ण __packed;

काष्ठा libipw_channel_चयन अणु
	u8 id;
	u8 len;
	u8 mode;
	u8 channel;
	u8 count;
पूर्ण __packed;

काष्ठा libipw_action अणु
	काष्ठा libipw_hdr_3addr header;
	u8 category;
	u8 action;
	जोड़ अणु
		काष्ठा libipw_action_exchange अणु
			u8 token;
			काष्ठा libipw_info_element info_element[0];
		पूर्ण exchange;
		काष्ठा libipw_channel_चयन channel_चयन;

	पूर्ण क्रमmat;
पूर्ण __packed;

काष्ठा libipw_disassoc अणु
	काष्ठा libipw_hdr_3addr header;
	__le16 reason;
पूर्ण __packed;

/* Alias deauth क्रम disassoc */
#घोषणा libipw_deauth libipw_disassoc

काष्ठा libipw_probe_request अणु
	काष्ठा libipw_hdr_3addr header;
	/* SSID, supported rates */
	काष्ठा libipw_info_element info_element[];
पूर्ण __packed;

काष्ठा libipw_probe_response अणु
	काष्ठा libipw_hdr_3addr header;
	__le32 समय_stamp[2];
	__le16 beacon_पूर्णांकerval;
	__le16 capability;
	/* SSID, supported rates, FH params, DS params,
	 * CF params, IBSS params, TIM (अगर beacon), RSN */
	काष्ठा libipw_info_element info_element[];
पूर्ण __packed;

/* Alias beacon क्रम probe_response */
#घोषणा libipw_beacon libipw_probe_response

काष्ठा libipw_assoc_request अणु
	काष्ठा libipw_hdr_3addr header;
	__le16 capability;
	__le16 listen_पूर्णांकerval;
	/* SSID, supported rates, RSN */
	काष्ठा libipw_info_element info_element[];
पूर्ण __packed;

काष्ठा libipw_reassoc_request अणु
	काष्ठा libipw_hdr_3addr header;
	__le16 capability;
	__le16 listen_पूर्णांकerval;
	u8 current_ap[ETH_ALEN];
	काष्ठा libipw_info_element info_element[];
पूर्ण __packed;

काष्ठा libipw_assoc_response अणु
	काष्ठा libipw_hdr_3addr header;
	__le16 capability;
	__le16 status;
	__le16 aid;
	/* supported rates */
	काष्ठा libipw_info_element info_element[];
पूर्ण __packed;

काष्ठा libipw_txb अणु
	u8 nr_frags;
	u8 encrypted;
	u8 rts_included;
	u8 reserved;
	u16 frag_size;
	u16 payload_size;
	काष्ठा sk_buff *fragments[];
पूर्ण;

/* SWEEP TABLE ENTRIES NUMBER */
#घोषणा MAX_SWEEP_TAB_ENTRIES		  42
#घोषणा MAX_SWEEP_TAB_ENTRIES_PER_PACKET  7
/* MAX_RATES_LENGTH needs to be 12.  The spec says 8, and many APs
 * only use 8, and then use extended rates क्रम the reमुख्यing supported
 * rates.  Other APs, however, stick all of their supported rates on the
 * मुख्य rates inक्रमmation element... */
#घोषणा MAX_RATES_LENGTH                  ((u8)12)
#घोषणा MAX_RATES_EX_LENGTH               ((u8)16)
#घोषणा MAX_NETWORK_COUNT                  128

#घोषणा CRC_LENGTH                 4U

#घोषणा MAX_WPA_IE_LEN 64

#घोषणा NETWORK_HAS_OFDM       (1<<1)
#घोषणा NETWORK_HAS_CCK        (1<<2)

/* QoS काष्ठाure */
#घोषणा NETWORK_HAS_QOS_PARAMETERS      (1<<3)
#घोषणा NETWORK_HAS_QOS_INFORMATION     (1<<4)
#घोषणा NETWORK_HAS_QOS_MASK            (NETWORK_HAS_QOS_PARAMETERS | \
					 NETWORK_HAS_QOS_INFORMATION)

/* 802.11h */
#घोषणा NETWORK_HAS_POWER_CONSTRAINT    (1<<5)
#घोषणा NETWORK_HAS_CSA                 (1<<6)
#घोषणा NETWORK_HAS_QUIET               (1<<7)
#घोषणा NETWORK_HAS_IBSS_DFS            (1<<8)
#घोषणा NETWORK_HAS_TPC_REPORT          (1<<9)

#घोषणा NETWORK_HAS_ERP_VALUE           (1<<10)

#घोषणा QOS_QUEUE_NUM                   4
#घोषणा QOS_OUI_LEN                     3
#घोषणा QOS_OUI_TYPE                    2
#घोषणा QOS_ELEMENT_ID                  221
#घोषणा QOS_OUI_INFO_SUB_TYPE           0
#घोषणा QOS_OUI_PARAM_SUB_TYPE          1
#घोषणा QOS_VERSION_1                   1
#घोषणा QOS_AIFSN_MIN_VALUE             2

काष्ठा libipw_qos_inक्रमmation_element अणु
	u8 elementID;
	u8 length;
	u8 qui[QOS_OUI_LEN];
	u8 qui_type;
	u8 qui_subtype;
	u8 version;
	u8 ac_info;
पूर्ण __packed;

काष्ठा libipw_qos_ac_parameter अणु
	u8 aci_aअगरsn;
	u8 ecw_min_max;
	__le16 tx_op_limit;
पूर्ण __packed;

काष्ठा libipw_qos_parameter_info अणु
	काष्ठा libipw_qos_inक्रमmation_element info_element;
	u8 reserved;
	काष्ठा libipw_qos_ac_parameter ac_params_record[QOS_QUEUE_NUM];
पूर्ण __packed;

काष्ठा libipw_qos_parameters अणु
	__le16 cw_min[QOS_QUEUE_NUM];
	__le16 cw_max[QOS_QUEUE_NUM];
	u8 aअगरs[QOS_QUEUE_NUM];
	u8 flag[QOS_QUEUE_NUM];
	__le16 tx_op_limit[QOS_QUEUE_NUM];
पूर्ण __packed;

काष्ठा libipw_qos_data अणु
	काष्ठा libipw_qos_parameters parameters;
	पूर्णांक active;
	पूर्णांक supported;
	u8 param_count;
	u8 old_param_count;
पूर्ण;

काष्ठा libipw_tim_parameters अणु
	u8 tim_count;
	u8 tim_period;
पूर्ण __packed;

/*******************************************************/

काष्ठा libipw_tpc_report अणु
	u8 transmit_घातer;
	u8 link_margin;
पूर्ण __packed;

काष्ठा libipw_channel_map अणु
	u8 channel;
	u8 map;
पूर्ण __packed;

काष्ठा libipw_ibss_dfs अणु
	काष्ठा libipw_info_element ie;
	u8 owner[ETH_ALEN];
	u8 recovery_पूर्णांकerval;
	काष्ठा libipw_channel_map channel_map[];
पूर्ण;

काष्ठा libipw_csa अणु
	u8 mode;
	u8 channel;
	u8 count;
पूर्ण __packed;

काष्ठा libipw_quiet अणु
	u8 count;
	u8 period;
	u8 duration;
	u8 offset;
पूर्ण __packed;

काष्ठा libipw_network अणु
	/* These entries are used to identअगरy a unique network */
	u8 bssid[ETH_ALEN];
	u8 channel;
	/* Ensure null-terminated क्रम any debug msgs */
	u8 ssid[IW_ESSID_MAX_SIZE + 1];
	u8 ssid_len;

	काष्ठा libipw_qos_data qos_data;

	/* These are network statistics */
	काष्ठा libipw_rx_stats stats;
	u16 capability;
	u8 rates[MAX_RATES_LENGTH];
	u8 rates_len;
	u8 rates_ex[MAX_RATES_EX_LENGTH];
	u8 rates_ex_len;
	अचिन्हित दीर्घ last_scanned;
	u8 mode;
	u32 flags;
	u32 last_associate;
	u32 समय_stamp[2];
	u16 beacon_पूर्णांकerval;
	u16 listen_पूर्णांकerval;
	u16 atim_winकरोw;
	u8 erp_value;
	u8 wpa_ie[MAX_WPA_IE_LEN];
	माप_प्रकार wpa_ie_len;
	u8 rsn_ie[MAX_WPA_IE_LEN];
	माप_प्रकार rsn_ie_len;
	काष्ठा libipw_tim_parameters tim;

	/* 802.11h info */

	/* Power Constraपूर्णांक - mandatory अगर spctrm mgmt required */
	u8 घातer_स्थिरraपूर्णांक;

	/* TPC Report - mandatory अगर spctrm mgmt required */
	काष्ठा libipw_tpc_report tpc_report;

	/* Channel Switch Announcement - optional अगर spctrm mgmt required */
	काष्ठा libipw_csa csa;

	/* Quiet - optional अगर spctrm mgmt required */
	काष्ठा libipw_quiet quiet;

	काष्ठा list_head list;
पूर्ण;

क्रमागत libipw_state अणु
	LIBIPW_UNINITIALIZED = 0,
	LIBIPW_INITIALIZED,
	LIBIPW_ASSOCIATING,
	LIBIPW_ASSOCIATED,
	LIBIPW_AUTHENTICATING,
	LIBIPW_AUTHENTICATED,
	LIBIPW_SHUTDOWN
पूर्ण;

#घोषणा DEFAULT_MAX_SCAN_AGE (15 * HZ)
#घोषणा DEFAULT_FTS 2346

#घोषणा CFG_LIBIPW_RESERVE_FCS (1<<0)
#घोषणा CFG_LIBIPW_COMPUTE_FCS (1<<1)
#घोषणा CFG_LIBIPW_RTS (1<<2)

#घोषणा LIBIPW_24GHZ_MIN_CHANNEL 1
#घोषणा LIBIPW_24GHZ_MAX_CHANNEL 14
#घोषणा LIBIPW_24GHZ_CHANNELS (LIBIPW_24GHZ_MAX_CHANNEL - \
				  LIBIPW_24GHZ_MIN_CHANNEL + 1)

#घोषणा LIBIPW_52GHZ_MIN_CHANNEL 34
#घोषणा LIBIPW_52GHZ_MAX_CHANNEL 165
#घोषणा LIBIPW_52GHZ_CHANNELS (LIBIPW_52GHZ_MAX_CHANNEL - \
				  LIBIPW_52GHZ_MIN_CHANNEL + 1)

क्रमागत अणु
	LIBIPW_CH_PASSIVE_ONLY = (1 << 0),
	LIBIPW_CH_80211H_RULES = (1 << 1),
	LIBIPW_CH_B_ONLY = (1 << 2),
	LIBIPW_CH_NO_IBSS = (1 << 3),
	LIBIPW_CH_UNIFORM_SPREADING = (1 << 4),
	LIBIPW_CH_RADAR_DETECT = (1 << 5),
	LIBIPW_CH_INVALID = (1 << 6),
पूर्ण;

काष्ठा libipw_channel अणु
	u32 freq;	/* in MHz */
	u8 channel;
	u8 flags;
	u8 max_घातer;	/* in dBm */
पूर्ण;

काष्ठा libipw_geo अणु
	u8 name[4];
	u8 bg_channels;
	u8 a_channels;
	काष्ठा libipw_channel bg[LIBIPW_24GHZ_CHANNELS];
	काष्ठा libipw_channel a[LIBIPW_52GHZ_CHANNELS];
पूर्ण;

काष्ठा libipw_device अणु
	काष्ठा net_device *dev;
	काष्ठा wireless_dev wdev;
	काष्ठा libipw_security sec;

	/* Bookkeeping काष्ठाures */
	काष्ठा libipw_stats ieee_stats;

	काष्ठा libipw_geo geo;
	काष्ठा ieee80211_supported_band bg_band;
	काष्ठा ieee80211_supported_band a_band;

	/* Probe / Beacon management */
	काष्ठा list_head network_मुक्त_list;
	काष्ठा list_head network_list;
	काष्ठा libipw_network *networks[MAX_NETWORK_COUNT];
	पूर्णांक scans;
	पूर्णांक scan_age;

	पूर्णांक iw_mode;		/* operating mode (IW_MODE_*) */
	काष्ठा iw_spy_data spy_data;	/* iwspy support */

	spinlock_t lock;

	पूर्णांक tx_headroom;	/* Set to size of any additional room needed at front
				 * of allocated Tx SKBs */
	u32 config;

	/* WEP and other encryption related settings at the device level */
	पूर्णांक खोलो_wep;		/* Set to 1 to allow unencrypted frames */

	/* If the host perक्रमms अणुen,deपूर्णcryption, then set to 1 */
	पूर्णांक host_encrypt;
	पूर्णांक host_encrypt_msdu;
	पूर्णांक host_decrypt;
	/* host perक्रमms multicast decryption */
	पूर्णांक host_mc_decrypt;

	/* host should strip IV and ICV from रक्षित frames */
	/* meaningful only when hardware decryption is being used */
	पूर्णांक host_strip_iv_icv;

	पूर्णांक host_खोलो_frag;
	पूर्णांक ieee802_1x;		/* is IEEE 802.1X used */

	/* WPA data */
	पूर्णांक wpa_enabled;
	पूर्णांक drop_unencrypted;
	पूर्णांक privacy_invoked;
	माप_प्रकार wpa_ie_len;
	u8 *wpa_ie;

	काष्ठा lib80211_crypt_info crypt_info;

	पूर्णांक bcrx_sta_key;	/* use inभागidual keys to override शेष keys even
				 * with RX of broad/multicast frames */

	/* Fragmentation काष्ठाures */
	काष्ठा libipw_frag_entry frag_cache[LIBIPW_FRAG_CACHE_LEN];
	अचिन्हित पूर्णांक frag_next_idx;
	u16 fts;		/* Fragmentation Threshold */
	u16 rts;		/* RTS threshold */

	/* Association info */
	u8 bssid[ETH_ALEN];

	क्रमागत libipw_state state;

	पूर्णांक mode;		/* A, B, G */
	पूर्णांक modulation;		/* CCK, OFDM */
	पूर्णांक freq_band;		/* 2.4Ghz, 5.2Ghz, Mixed */
	पूर्णांक abg_true;		/* ABG flag              */

	पूर्णांक perfect_rssi;
	पूर्णांक worst_rssi;

	u16 prev_seq_ctl;	/* used to drop duplicate frames */

	/* Callback functions */
	व्योम (*set_security) (काष्ठा net_device * dev,
			      काष्ठा libipw_security * sec);
	netdev_tx_t (*hard_start_xmit) (काष्ठा libipw_txb * txb,
					काष्ठा net_device * dev, पूर्णांक pri);
	पूर्णांक (*is_queue_full) (काष्ठा net_device * dev, पूर्णांक pri);

	पूर्णांक (*handle_management) (काष्ठा net_device * dev,
				  काष्ठा libipw_network * network, u16 type);
	पूर्णांक (*is_qos_active) (काष्ठा net_device *dev, काष्ठा sk_buff *skb);

	/* Typical STA methods */
	पूर्णांक (*handle_auth) (काष्ठा net_device * dev,
			    काष्ठा libipw_auth * auth);
	पूर्णांक (*handle_deauth) (काष्ठा net_device * dev,
			      काष्ठा libipw_deauth * auth);
	पूर्णांक (*handle_action) (काष्ठा net_device * dev,
			      काष्ठा libipw_action * action,
			      काष्ठा libipw_rx_stats * stats);
	पूर्णांक (*handle_disassoc) (काष्ठा net_device * dev,
				काष्ठा libipw_disassoc * assoc);
	पूर्णांक (*handle_beacon) (काष्ठा net_device * dev,
			      काष्ठा libipw_beacon * beacon,
			      काष्ठा libipw_network * network);
	पूर्णांक (*handle_probe_response) (काष्ठा net_device * dev,
				      काष्ठा libipw_probe_response * resp,
				      काष्ठा libipw_network * network);
	पूर्णांक (*handle_probe_request) (काष्ठा net_device * dev,
				     काष्ठा libipw_probe_request * req,
				     काष्ठा libipw_rx_stats * stats);
	पूर्णांक (*handle_assoc_response) (काष्ठा net_device * dev,
				      काष्ठा libipw_assoc_response * resp,
				      काष्ठा libipw_network * network);

	/* Typical AP methods */
	पूर्णांक (*handle_assoc_request) (काष्ठा net_device * dev);
	पूर्णांक (*handle_reassoc_request) (काष्ठा net_device * dev,
				       काष्ठा libipw_reassoc_request * req);

	/* This must be the last item so that it poपूर्णांकs to the data
	 * allocated beyond this काष्ठाure by alloc_libipw */
	u8 priv[];
पूर्ण;

#घोषणा IEEE_A            (1<<0)
#घोषणा IEEE_B            (1<<1)
#घोषणा IEEE_G            (1<<2)
#घोषणा IEEE_MODE_MASK    (IEEE_A|IEEE_B|IEEE_G)

अटल अंतरभूत व्योम *libipw_priv(काष्ठा net_device *dev)
अणु
	वापस ((काष्ठा libipw_device *)netdev_priv(dev))->priv;
पूर्ण

अटल अंतरभूत पूर्णांक libipw_is_valid_mode(काष्ठा libipw_device *ieee,
					  पूर्णांक mode)
अणु
	/*
	 * It is possible क्रम both access poपूर्णांकs and our device to support
	 * combinations of modes, so as दीर्घ as there is one valid combination
	 * of ap/device supported modes, then वापस success
	 *
	 */
	अगर ((mode & IEEE_A) &&
	    (ieee->modulation & LIBIPW_OFDM_MODULATION) &&
	    (ieee->freq_band & LIBIPW_52GHZ_BAND))
		वापस 1;

	अगर ((mode & IEEE_G) &&
	    (ieee->modulation & LIBIPW_OFDM_MODULATION) &&
	    (ieee->freq_band & LIBIPW_24GHZ_BAND))
		वापस 1;

	अगर ((mode & IEEE_B) &&
	    (ieee->modulation & LIBIPW_CCK_MODULATION) &&
	    (ieee->freq_band & LIBIPW_24GHZ_BAND))
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक libipw_get_hdrlen(u16 fc)
अणु
	पूर्णांक hdrlen = LIBIPW_3ADDR_LEN;
	u16 stype = WLAN_FC_GET_STYPE(fc);

	चयन (WLAN_FC_GET_TYPE(fc)) अणु
	हाल IEEE80211_FTYPE_DATA:
		अगर ((fc & IEEE80211_FCTL_FROMDS) && (fc & IEEE80211_FCTL_TODS))
			hdrlen = LIBIPW_4ADDR_LEN;
		अगर (stype & IEEE80211_STYPE_QOS_DATA)
			hdrlen += 2;
		अवरोध;
	हाल IEEE80211_FTYPE_CTL:
		चयन (WLAN_FC_GET_STYPE(fc)) अणु
		हाल IEEE80211_STYPE_CTS:
		हाल IEEE80211_STYPE_ACK:
			hdrlen = LIBIPW_1ADDR_LEN;
			अवरोध;
		शेष:
			hdrlen = LIBIPW_2ADDR_LEN;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस hdrlen;
पूर्ण

अटल अंतरभूत u8 *libipw_get_payload(काष्ठा ieee80211_hdr *hdr)
अणु
	चयन (libipw_get_hdrlen(le16_to_cpu(hdr->frame_control))) अणु
	हाल LIBIPW_1ADDR_LEN:
		वापस ((काष्ठा libipw_hdr_1addr *)hdr)->payload;
	हाल LIBIPW_2ADDR_LEN:
		वापस ((काष्ठा libipw_hdr_2addr *)hdr)->payload;
	हाल LIBIPW_3ADDR_LEN:
		वापस ((काष्ठा libipw_hdr_3addr *)hdr)->payload;
	हाल LIBIPW_4ADDR_LEN:
		वापस ((काष्ठा libipw_hdr_4addr *)hdr)->payload;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक libipw_is_ofdm_rate(u8 rate)
अणु
	चयन (rate & ~LIBIPW_BASIC_RATE_MASK) अणु
	हाल LIBIPW_OFDM_RATE_6MB:
	हाल LIBIPW_OFDM_RATE_9MB:
	हाल LIBIPW_OFDM_RATE_12MB:
	हाल LIBIPW_OFDM_RATE_18MB:
	हाल LIBIPW_OFDM_RATE_24MB:
	हाल LIBIPW_OFDM_RATE_36MB:
	हाल LIBIPW_OFDM_RATE_48MB:
	हाल LIBIPW_OFDM_RATE_54MB:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक libipw_is_cck_rate(u8 rate)
अणु
	चयन (rate & ~LIBIPW_BASIC_RATE_MASK) अणु
	हाल LIBIPW_CCK_RATE_1MB:
	हाल LIBIPW_CCK_RATE_2MB:
	हाल LIBIPW_CCK_RATE_5MB:
	हाल LIBIPW_CCK_RATE_11MB:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* libipw.c */
व्योम मुक्त_libipw(काष्ठा net_device *dev, पूर्णांक monitor);
काष्ठा net_device *alloc_libipw(पूर्णांक माप_priv, पूर्णांक monitor);

व्योम libipw_networks_age(काष्ठा libipw_device *ieee, अचिन्हित दीर्घ age_secs);

पूर्णांक libipw_set_encryption(काष्ठा libipw_device *ieee);

/* libipw_tx.c */
netdev_tx_t libipw_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
व्योम libipw_txb_मुक्त(काष्ठा libipw_txb *);

/* libipw_rx.c */
व्योम libipw_rx_any(काष्ठा libipw_device *ieee, काष्ठा sk_buff *skb,
		   काष्ठा libipw_rx_stats *stats);
पूर्णांक libipw_rx(काष्ठा libipw_device *ieee, काष्ठा sk_buff *skb,
	      काष्ठा libipw_rx_stats *rx_stats);
/* make sure to set stats->len */
व्योम libipw_rx_mgt(काष्ठा libipw_device *ieee, काष्ठा libipw_hdr_4addr *header,
		   काष्ठा libipw_rx_stats *stats);

/* libipw_geo.c */
स्थिर काष्ठा libipw_geo *libipw_get_geo(काष्ठा libipw_device *ieee);
व्योम libipw_set_geo(काष्ठा libipw_device *ieee, स्थिर काष्ठा libipw_geo *geo);

पूर्णांक libipw_is_valid_channel(काष्ठा libipw_device *ieee, u8 channel);
पूर्णांक libipw_channel_to_index(काष्ठा libipw_device *ieee, u8 channel);
u8 libipw_freq_to_channel(काष्ठा libipw_device *ieee, u32 freq);
u8 libipw_get_channel_flags(काष्ठा libipw_device *ieee, u8 channel);
स्थिर काष्ठा libipw_channel *libipw_get_channel(काष्ठा libipw_device *ieee,
						u8 channel);
u32 libipw_channel_to_freq(काष्ठा libipw_device *ieee, u8 channel);

/* libipw_wx.c */
पूर्णांक libipw_wx_get_scan(काष्ठा libipw_device *ieee, काष्ठा iw_request_info *info,
		       जोड़ iwreq_data *wrqu, अक्षर *key);
पूर्णांक libipw_wx_set_encode(काष्ठा libipw_device *ieee,
			 काष्ठा iw_request_info *info, जोड़ iwreq_data *wrqu,
			 अक्षर *key);
पूर्णांक libipw_wx_get_encode(काष्ठा libipw_device *ieee,
			 काष्ठा iw_request_info *info, जोड़ iwreq_data *wrqu,
			 अक्षर *key);
पूर्णांक libipw_wx_set_encodeext(काष्ठा libipw_device *ieee,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra);
पूर्णांक libipw_wx_get_encodeext(काष्ठा libipw_device *ieee,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra);

अटल अंतरभूत व्योम libipw_increment_scans(काष्ठा libipw_device *ieee)
अणु
	ieee->scans++;
पूर्ण

अटल अंतरभूत पूर्णांक libipw_get_scans(काष्ठा libipw_device *ieee)
अणु
	वापस ieee->scans;
पूर्ण

#पूर्ण_अगर				/* LIBIPW_H */
