<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012 Broadcom Corporation
 */


#अगर_अघोषित FWIL_TYPES_H_
#घोषणा FWIL_TYPES_H_

#समावेश <linux/अगर_ether.h>


#घोषणा BRCMF_FIL_ACTION_FRAME_SIZE	1800

/* ARP Offload feature flags क्रम arp_ol iovar */
#घोषणा BRCMF_ARP_OL_AGENT		0x00000001
#घोषणा BRCMF_ARP_OL_SNOOP		0x00000002
#घोषणा BRCMF_ARP_OL_HOST_AUTO_REPLY	0x00000004
#घोषणा BRCMF_ARP_OL_PEER_AUTO_REPLY	0x00000008

#घोषणा	BRCMF_BSS_INFO_VERSION	109 /* curr ver of brcmf_bss_info_le काष्ठा */
#घोषणा BRCMF_BSS_RSSI_ON_CHANNEL	0x0004

#घोषणा BRCMF_STA_BRCM			0x00000001	/* Running a Broadcom driver */
#घोषणा BRCMF_STA_WME			0x00000002	/* WMM association */
#घोषणा BRCMF_STA_NONERP		0x00000004	/* No ERP */
#घोषणा BRCMF_STA_AUTHE			0x00000008	/* Authenticated */
#घोषणा BRCMF_STA_ASSOC			0x00000010	/* Associated */
#घोषणा BRCMF_STA_AUTHO			0x00000020	/* Authorized */
#घोषणा BRCMF_STA_WDS			0x00000040	/* Wireless Distribution System */
#घोषणा BRCMF_STA_WDS_LINKUP		0x00000080	/* WDS traffic/probes flowing properly */
#घोषणा BRCMF_STA_PS			0x00000100	/* STA is in घातer save mode from AP's viewpoपूर्णांक */
#घोषणा BRCMF_STA_APSD_BE		0x00000200	/* APSD delv/trigger क्रम AC_BE is शेष enabled */
#घोषणा BRCMF_STA_APSD_BK		0x00000400	/* APSD delv/trigger क्रम AC_BK is शेष enabled */
#घोषणा BRCMF_STA_APSD_VI		0x00000800	/* APSD delv/trigger क्रम AC_VI is शेष enabled */
#घोषणा BRCMF_STA_APSD_VO		0x00001000	/* APSD delv/trigger क्रम AC_VO is शेष enabled */
#घोषणा BRCMF_STA_N_CAP			0x00002000	/* STA 802.11n capable */
#घोषणा BRCMF_STA_SCBSTATS		0x00004000	/* Per STA debug stats */
#घोषणा BRCMF_STA_AMPDU_CAP		0x00008000	/* STA AMPDU capable */
#घोषणा BRCMF_STA_AMSDU_CAP		0x00010000	/* STA AMSDU capable */
#घोषणा BRCMF_STA_MIMO_PS		0x00020000	/* mimo ps mode is enabled */
#घोषणा BRCMF_STA_MIMO_RTS		0x00040000	/* send rts in mimo ps mode */
#घोषणा BRCMF_STA_RIFS_CAP		0x00080000	/* rअगरs enabled */
#घोषणा BRCMF_STA_VHT_CAP		0x00100000	/* STA VHT(11ac) capable */
#घोषणा BRCMF_STA_WPS			0x00200000	/* WPS state */
#घोषणा BRCMF_STA_DWDS_CAP		0x01000000	/* DWDS CAP */
#घोषणा BRCMF_STA_DWDS			0x02000000	/* DWDS active */

/* size of brcmf_scan_params not including variable length array */
#घोषणा BRCMF_SCAN_PARAMS_FIXED_SIZE	64

/* masks क्रम channel and ssid count */
#घोषणा BRCMF_SCAN_PARAMS_COUNT_MASK	0x0000ffff
#घोषणा BRCMF_SCAN_PARAMS_NSSID_SHIFT	16

/* scan type definitions */
#घोषणा BRCMF_SCANTYPE_DEFAULT		0xFF
#घोषणा BRCMF_SCANTYPE_ACTIVE		0
#घोषणा BRCMF_SCANTYPE_PASSIVE		1

#घोषणा BRCMF_WSEC_MAX_PSK_LEN		32
#घोषणा	BRCMF_WSEC_PASSPHRASE		BIT(0)

#घोषणा BRCMF_WSEC_MAX_SAE_PASSWORD_LEN 128

/* primary (ie tx) key */
#घोषणा BRCMF_PRIMARY_KEY		(1 << 1)
#घोषणा DOT11_BSSTYPE_ANY		2
#घोषणा BRCMF_ESCAN_REQ_VERSION		1

#घोषणा BRCMF_MAXRATES_IN_SET		16	/* max # of rates in rateset */

/* OBSS Coex Auto/On/Off */
#घोषणा BRCMF_OBSS_COEX_AUTO		(-1)
#घोषणा BRCMF_OBSS_COEX_OFF		0
#घोषणा BRCMF_OBSS_COEX_ON		1

/* WOWL bits */
/* Wakeup on Magic packet: */
#घोषणा BRCMF_WOWL_MAGIC		(1 << 0)
/* Wakeup on Netpattern */
#घोषणा BRCMF_WOWL_NET			(1 << 1)
/* Wakeup on loss-of-link due to Disassoc/Deauth: */
#घोषणा BRCMF_WOWL_DIS			(1 << 2)
/* Wakeup on retrograde TSF: */
#घोषणा BRCMF_WOWL_RETR			(1 << 3)
/* Wakeup on loss of beacon: */
#घोषणा BRCMF_WOWL_BCN			(1 << 4)
/* Wakeup after test: */
#घोषणा BRCMF_WOWL_TST			(1 << 5)
/* Wakeup after PTK refresh: */
#घोषणा BRCMF_WOWL_M1			(1 << 6)
/* Wakeup after receipt of EAP-Identity Req: */
#घोषणा BRCMF_WOWL_EAPID		(1 << 7)
/* Wakeind via PME(0) or GPIO(1): */
#घोषणा BRCMF_WOWL_PME_GPIO		(1 << 8)
/* need tkip phase 1 key to be updated by the driver: */
#घोषणा BRCMF_WOWL_NEEDTKIP1		(1 << 9)
/* enable wakeup अगर GTK fails: */
#घोषणा BRCMF_WOWL_GTK_FAILURE		(1 << 10)
/* support extended magic packets: */
#घोषणा BRCMF_WOWL_EXTMAGPAT		(1 << 11)
/* support ARP/NS/keepalive offloading: */
#घोषणा BRCMF_WOWL_ARPOFFLOAD		(1 << 12)
/* पढ़ो protocol version क्रम EAPOL frames: */
#घोषणा BRCMF_WOWL_WPA2			(1 << 13)
/* If the bit is set, use key rotaton: */
#घोषणा BRCMF_WOWL_KEYROT		(1 << 14)
/* If the bit is set, frm received was bcast frame: */
#घोषणा BRCMF_WOWL_BCAST		(1 << 15)
/* If the bit is set, scan offload is enabled: */
#घोषणा BRCMF_WOWL_SCANOL		(1 << 16)
/* Wakeup on tcpkeep alive समयout: */
#घोषणा BRCMF_WOWL_TCPKEEP_TIME		(1 << 17)
/* Wakeup on mDNS Conflict Resolution: */
#घोषणा BRCMF_WOWL_MDNS_CONFLICT	(1 << 18)
/* Wakeup on mDNS Service Connect: */
#घोषणा BRCMF_WOWL_MDNS_SERVICE		(1 << 19)
/* tcp keepalive got data: */
#घोषणा BRCMF_WOWL_TCPKEEP_DATA		(1 << 20)
/* Firmware died in wowl mode: */
#घोषणा BRCMF_WOWL_FW_HALT		(1 << 21)
/* Enable detection of radio button changes: */
#घोषणा BRCMF_WOWL_ENAB_HWRADIO		(1 << 22)
/* Offloads detected MIC failure(s): */
#घोषणा BRCMF_WOWL_MIC_FAIL		(1 << 23)
/* Wakeup in Unassociated state (Net/Magic Pattern): */
#घोषणा BRCMF_WOWL_UNASSOC		(1 << 24)
/* Wakeup अगर received matched secured pattern: */
#घोषणा BRCMF_WOWL_SECURE		(1 << 25)
/* Wakeup on finding preferred network */
#घोषणा BRCMF_WOWL_PFN_FOUND		(1 << 27)
/* Wakeup on receiving pairwise key EAP packets: */
#घोषणा WIPHY_WOWL_EAP_PK		(1 << 28)
/* Link Down indication in WoWL mode: */
#घोषणा BRCMF_WOWL_LINKDOWN		(1 << 31)

#घोषणा BRCMF_WOWL_MAXPATTERNS		8
#घोषणा BRCMF_WOWL_MAXPATTERNSIZE	128

#घोषणा BRCMF_COUNTRY_BUF_SZ		4
#घोषणा BRCMF_ANT_MAX			4

#घोषणा BRCMF_MAX_ASSOCLIST		128

#घोषणा BRCMF_TXBF_SU_BFE_CAP		BIT(0)
#घोषणा BRCMF_TXBF_MU_BFE_CAP		BIT(1)
#घोषणा BRCMF_TXBF_SU_BFR_CAP		BIT(0)
#घोषणा BRCMF_TXBF_MU_BFR_CAP		BIT(1)

#घोषणा	BRCMF_MAXPMKID			16	/* max # PMKID cache entries */
#घोषणा BRCMF_NUMCHANNELS		64

#घोषणा BRCMF_PFN_MACADDR_CFG_VER	1
#घोषणा BRCMF_PFN_MAC_OUI_ONLY		BIT(0)
#घोषणा BRCMF_PFN_SET_MAC_UNASSOC	BIT(1)

#घोषणा BRCMF_MCSSET_LEN		16

#घोषणा BRCMF_RSN_KCK_LENGTH		16
#घोषणा BRCMF_RSN_KEK_LENGTH		16
#घोषणा BRCMF_RSN_REPLAY_LEN		8

#घोषणा BRCMF_MFP_NONE			0
#घोषणा BRCMF_MFP_CAPABLE		1
#घोषणा BRCMF_MFP_REQUIRED		2

#घोषणा BRCMF_VHT_CAP_MCS_MAP_NSS_MAX	8

#घोषणा BRCMF_HE_CAP_MCS_MAP_NSS_MAX	8

/* MAX_CHUNK_LEN is the maximum length क्रम data passing to firmware in each
 * ioctl. It is relatively small because firmware has small maximum size input
 * playload restriction क्रम ioctls.
 */
#घोषणा MAX_CHUNK_LEN			1400

#घोषणा DLOAD_HANDLER_VER		1	/* Downloader version */
#घोषणा DLOAD_FLAG_VER_MASK		0xf000	/* Downloader version mask */
#घोषणा DLOAD_FLAG_VER_SHIFT		12	/* Downloader version shअगरt */

#घोषणा DL_BEGIN			0x0002
#घोषणा DL_END				0x0004

#घोषणा DL_TYPE_CLM			2

/* join preference types क्रम join_pref iovar */
क्रमागत brcmf_join_pref_types अणु
	BRCMF_JOIN_PREF_RSSI = 1,
	BRCMF_JOIN_PREF_WPA,
	BRCMF_JOIN_PREF_BAND,
	BRCMF_JOIN_PREF_RSSI_DELTA,
पूर्ण;

क्रमागत brcmf_fil_p2p_अगर_types अणु
	BRCMF_FIL_P2P_IF_CLIENT,
	BRCMF_FIL_P2P_IF_GO,
	BRCMF_FIL_P2P_IF_DYNBCN_GO,
	BRCMF_FIL_P2P_IF_DEV,
पूर्ण;

क्रमागत brcmf_wowl_pattern_type अणु
	BRCMF_WOWL_PATTERN_TYPE_BITMAP = 0,
	BRCMF_WOWL_PATTERN_TYPE_ARP,
	BRCMF_WOWL_PATTERN_TYPE_NA
पूर्ण;

काष्ठा brcmf_fil_p2p_अगर_le अणु
	u8 addr[ETH_ALEN];
	__le16 type;
	__le16 chspec;
पूर्ण;

काष्ठा brcmf_fil_chan_info_le अणु
	__le32 hw_channel;
	__le32 target_channel;
	__le32 scan_channel;
पूर्ण;

काष्ठा brcmf_fil_action_frame_le अणु
	u8	da[ETH_ALEN];
	__le16	len;
	__le32	packet_id;
	u8	data[BRCMF_FIL_ACTION_FRAME_SIZE];
पूर्ण;

काष्ठा brcmf_fil_af_params_le अणु
	__le32					channel;
	__le32					dwell_समय;
	u8					bssid[ETH_ALEN];
	u8					pad[2];
	काष्ठा brcmf_fil_action_frame_le	action_frame;
पूर्ण;

काष्ठा brcmf_fil_bss_enable_le अणु
	__le32 bsscfgidx;
	__le32 enable;
पूर्ण;

काष्ठा brcmf_fil_bwcap_le अणु
	__le32 band;
	__le32 bw_cap;
पूर्ण;

/**
 * काष्ठा tdls_iovar - common काष्ठाure क्रम tdls iovars.
 *
 * @ea: ether address of peer station.
 * @mode: mode value depending on specअगरic tdls iovar.
 * @chanspec: channel specअगरication.
 * @pad: unused (क्रम future use).
 */
काष्ठा brcmf_tdls_iovar_le अणु
	u8 ea[ETH_ALEN];		/* Station address */
	u8 mode;			/* mode: depends on iovar */
	__le16 chanspec;
	__le32 pad;			/* future */
पूर्ण;

क्रमागत brcmf_tdls_manual_ep_ops अणु
	BRCMF_TDLS_MANUAL_EP_CREATE = 1,
	BRCMF_TDLS_MANUAL_EP_DELETE = 3,
	BRCMF_TDLS_MANUAL_EP_DISCOVERY = 6
पूर्ण;

/* Pattern matching filter. Specअगरies an offset within received packets to
 * start matching, the pattern to match, the size of the pattern, and a biपंचांगask
 * that indicates which bits within the pattern should be matched.
 */
काष्ठा brcmf_pkt_filter_pattern_le अणु
	/*
	 * Offset within received packet to start pattern matching.
	 * Offset '0' is the first byte of the ethernet header.
	 */
	__le32 offset;
	/* Size of the pattern.  Biपंचांगask must be the same size.*/
	__le32 size_bytes;
	/*
	 * Variable length mask and pattern data. mask starts at offset 0.
	 * Pattern immediately follows mask.
	 */
	u8 mask_and_pattern[1];
पूर्ण;

/* IOVAR "pkt_filter_add" parameter. Used to install packet filters. */
काष्ठा brcmf_pkt_filter_le अणु
	__le32 id;		/* Unique filter id, specअगरied by app. */
	__le32 type;		/* Filter type (WL_PKT_FILTER_TYPE_xxx). */
	__le32 negate_match;	/* Negate the result of filter matches */
	जोड़ अणु			/* Filter definitions */
		काष्ठा brcmf_pkt_filter_pattern_le pattern; /* Filter pattern */
	पूर्ण u;
पूर्ण;

/* IOVAR "pkt_filter_enable" parameter. */
काष्ठा brcmf_pkt_filter_enable_le अणु
	__le32 id;		/* Unique filter id */
	__le32 enable;		/* Enable/disable bool */
पूर्ण;

/* BSS info काष्ठाure
 * Applications MUST CHECK ie_offset field and length field to access IEs and
 * next bss_info काष्ठाure in a vector (in काष्ठा brcmf_scan_results)
 */
काष्ठा brcmf_bss_info_le अणु
	__le32 version;		/* version field */
	__le32 length;		/* byte length of data in this record,
				 * starting at version and including IEs
				 */
	u8 BSSID[ETH_ALEN];
	__le16 beacon_period;	/* units are Kusec */
	__le16 capability;	/* Capability inक्रमmation */
	u8 SSID_len;
	u8 SSID[32];
	काष्ठा अणु
		__le32 count;   /* # rates in this set */
		u8 rates[16]; /* rates in 500kbps units w/hi bit set अगर basic */
	पूर्ण rateset;		/* supported rates */
	__le16 chanspec;	/* chanspec क्रम bss */
	__le16 atim_winकरोw;	/* units are Kusec */
	u8 dtim_period;	/* DTIM period */
	__le16 RSSI;		/* receive संकेत strength (in dBm) */
	s8 phy_noise;		/* noise (in dBm) */

	u8 n_cap;		/* BSS is 802.11N Capable */
	/* 802.11N BSS Capabilities (based on HT_CAP_*): */
	__le32 nbss_cap;
	u8 ctl_ch;		/* 802.11N BSS control channel number */
	__le32 reserved32[1];	/* Reserved क्रम expansion of BSS properties */
	u8 flags;		/* flags */
	u8 reserved[3];	/* Reserved क्रम expansion of BSS properties */
	u8 basic_mcs[BRCMF_MCSSET_LEN];	/* 802.11N BSS required MCS set */

	__le16 ie_offset;	/* offset at which IEs start, from beginning */
	__le32 ie_length;	/* byte length of Inक्रमmation Elements */
	__le16 SNR;		/* average SNR of during frame reception */
	/* Add new fields here */
	/* variable length Inक्रमmation Elements */
पूर्ण;

काष्ठा brcm_rateset_le अणु
	/* # rates in this set */
	__le32 count;
	/* rates in 500kbps units w/hi bit set अगर basic */
	u8 rates[BRCMF_MAXRATES_IN_SET];
पूर्ण;

काष्ठा brcmf_ssid_le अणु
	__le32 SSID_len;
	अचिन्हित अक्षर SSID[IEEE80211_MAX_SSID_LEN];
पूर्ण;

काष्ठा brcmf_scan_params_le अणु
	काष्ठा brcmf_ssid_le ssid_le;	/* शेष: अणु0, ""पूर्ण */
	u8 bssid[ETH_ALEN];	/* शेष: bcast */
	s8 bss_type;		/* शेष: any,
				 * DOT11_BSSTYPE_ANY/INFRASTRUCTURE/INDEPENDENT
				 */
	u8 scan_type;	/* flags, 0 use शेष */
	__le32 nprobes;	  /* -1 use शेष, number of probes per channel */
	__le32 active_समय;	/* -1 use शेष, dwell समय per channel क्रम
				 * active scanning
				 */
	__le32 passive_समय;	/* -1 use शेष, dwell समय per channel
				 * क्रम passive scanning
				 */
	__le32 home_समय;	/* -1 use शेष, dwell समय क्रम the
				 * home channel between channel scans
				 */
	__le32 channel_num;	/* count of channels and ssids that follow
				 *
				 * low half is count of channels in
				 * channel_list, 0 means शेष (use all
				 * available channels)
				 *
				 * high half is entries in काष्ठा brcmf_ssid
				 * array that follows channel_list, aligned क्रम
				 * s32 (4 bytes) meaning an odd channel count
				 * implies a 2-byte pad between end of
				 * channel_list and first ssid
				 *
				 * अगर ssid count is zero, single ssid in the
				 * fixed parameter portion is assumed, otherwise
				 * ssid in the fixed portion is ignored
				 */
	__le16 channel_list[1];	/* list of chanspecs */
पूर्ण;

काष्ठा brcmf_scan_results अणु
	u32 buflen;
	u32 version;
	u32 count;
	काष्ठा brcmf_bss_info_le bss_info_le[];
पूर्ण;

काष्ठा brcmf_escan_params_le अणु
	__le32 version;
	__le16 action;
	__le16 sync_id;
	काष्ठा brcmf_scan_params_le params_le;
पूर्ण;

काष्ठा brcmf_escan_result_le अणु
	__le32 buflen;
	__le32 version;
	__le16 sync_id;
	__le16 bss_count;
	काष्ठा brcmf_bss_info_le bss_info_le;
पूर्ण;

#घोषणा WL_ESCAN_RESULTS_FIXED_SIZE (माप(काष्ठा brcmf_escan_result_le) - \
	माप(काष्ठा brcmf_bss_info_le))

/* used क्रम association with a specअगरic BSSID and chanspec list */
काष्ठा brcmf_assoc_params_le अणु
	/* 00:00:00:00:00:00: broadcast scan */
	u8 bssid[ETH_ALEN];
	/* 0: all available channels, otherwise count of chanspecs in
	 * chanspec_list */
	__le32 chanspec_num;
	/* list of chanspecs */
	__le16 chanspec_list[1];
पूर्ण;

/**
 * काष्ठा join_pref params - parameters क्रम preferred join selection.
 *
 * @type: preference type (see क्रमागत brcmf_join_pref_types).
 * @len: length of bytes following (currently always 2).
 * @rssi_gain: संकेत gain क्रम selection (only when @type is RSSI_DELTA).
 * @band: band to which selection preference applies.
 *	This is used अगर @type is BAND or RSSI_DELTA.
 */
काष्ठा brcmf_join_pref_params अणु
	u8 type;
	u8 len;
	u8 rssi_gain;
	u8 band;
पूर्ण;

/* used क्रम join with or without a specअगरic bssid and channel list */
काष्ठा brcmf_join_params अणु
	काष्ठा brcmf_ssid_le ssid_le;
	काष्ठा brcmf_assoc_params_le params_le;
पूर्ण;

/* scan params क्रम extended join */
काष्ठा brcmf_join_scan_params_le अणु
	u8 scan_type;		/* 0 use शेष, active or passive scan */
	__le32 nprobes;		/* -1 use शेष, nr of probes per channel */
	__le32 active_समय;	/* -1 use शेष, dwell समय per channel क्रम
				 * active scanning
				 */
	__le32 passive_समय;	/* -1 use शेष, dwell समय per channel
				 * क्रम passive scanning
				 */
	__le32 home_समय;	/* -1 use शेष, dwell समय क्रम the home
				 * channel between channel scans
				 */
पूर्ण;

/* extended join params */
काष्ठा brcmf_ext_join_params_le अणु
	काष्ठा brcmf_ssid_le ssid_le;	/* अणु0, ""पूर्ण: wildcard scan */
	काष्ठा brcmf_join_scan_params_le scan_le;
	काष्ठा brcmf_assoc_params_le assoc_le;
पूर्ण;

काष्ठा brcmf_wsec_key अणु
	u32 index;		/* key index */
	u32 len;		/* key length */
	u8 data[WLAN_MAX_KEY_LEN];	/* key data */
	u32 pad_1[18];
	u32 algo;	/* CRYPTO_ALGO_AES_CCM, CRYPTO_ALGO_WEP128, etc */
	u32 flags;	/* misc flags */
	u32 pad_2[3];
	u32 iv_initialized;	/* has IV been initialized alपढ़ोy? */
	u32 pad_3;
	/* Rx IV */
	काष्ठा अणु
		u32 hi;	/* upper 32 bits of IV */
		u16 lo;	/* lower 16 bits of IV */
	पूर्ण rxiv;
	u32 pad_4[2];
	u8 ea[ETH_ALEN];	/* per station */
पूर्ण;

/*
 * करोngle requires same काष्ठा as above but with fields in little endian order
 */
काष्ठा brcmf_wsec_key_le अणु
	__le32 index;		/* key index */
	__le32 len;		/* key length */
	u8 data[WLAN_MAX_KEY_LEN];	/* key data */
	__le32 pad_1[18];
	__le32 algo;	/* CRYPTO_ALGO_AES_CCM, CRYPTO_ALGO_WEP128, etc */
	__le32 flags;	/* misc flags */
	__le32 pad_2[3];
	__le32 iv_initialized;	/* has IV been initialized alपढ़ोy? */
	__le32 pad_3;
	/* Rx IV */
	काष्ठा अणु
		__le32 hi;	/* upper 32 bits of IV */
		__le16 lo;	/* lower 16 bits of IV */
	पूर्ण rxiv;
	__le32 pad_4[2];
	u8 ea[ETH_ALEN];	/* per station */
पूर्ण;

/**
 * काष्ठा brcmf_wsec_pmk_le - firmware pmk material.
 *
 * @key_len: number of octets in key material.
 * @flags: key handling qualअगरiers.
 * @key: PMK key material.
 */
काष्ठा brcmf_wsec_pmk_le अणु
	__le16  key_len;
	__le16  flags;
	u8 key[2 * BRCMF_WSEC_MAX_PSK_LEN + 1];
पूर्ण;

/**
 * काष्ठा brcmf_wsec_sae_pwd_le - firmware SAE password material.
 *
 * @key_len: number of octets in key materials.
 * @key: SAE password material.
 */
काष्ठा brcmf_wsec_sae_pwd_le अणु
	__le16 key_len;
	u8 key[BRCMF_WSEC_MAX_SAE_PASSWORD_LEN];
पूर्ण;

/* Used to get specअगरic STA parameters */
काष्ठा brcmf_scb_val_le अणु
	__le32 val;
	u8 ea[ETH_ALEN];
पूर्ण;

/* channel encoding */
काष्ठा brcmf_channel_info_le अणु
	__le32 hw_channel;
	__le32 target_channel;
	__le32 scan_channel;
पूर्ण;

काष्ठा brcmf_sta_info_le अणु
	__le16 ver;		/* version of this काष्ठा */
	__le16 len;		/* length in bytes of this काष्ठाure */
	__le16 cap;		/* sta's advertised capabilities */
	__le32 flags;		/* flags defined below */
	__le32 idle;		/* समय since data pkt rx'd from sta */
	u8 ea[ETH_ALEN];		/* Station address */
	__le32 count;			/* # rates in this set */
	u8 rates[BRCMF_MAXRATES_IN_SET];	/* rates in 500kbps units */
						/* w/hi bit set अगर basic */
	__le32 in;		/* seconds elapsed since associated */
	__le32 listen_पूर्णांकerval_inms; /* Min Listen पूर्णांकerval in ms क्रम STA */

	/* Fields valid क्रम ver >= 3 */
	__le32 tx_pkts;	/* # of packets transmitted */
	__le32 tx_failures;	/* # of packets failed */
	__le32 rx_ucast_pkts;	/* # of unicast packets received */
	__le32 rx_mcast_pkts;	/* # of multicast packets received */
	__le32 tx_rate;	/* Rate of last successful tx frame */
	__le32 rx_rate;	/* Rate of last successful rx frame */
	__le32 rx_decrypt_succeeds;	/* # of packet decrypted successfully */
	__le32 rx_decrypt_failures;	/* # of packet decrypted failed */

	/* Fields valid क्रम ver >= 4 */
	__le32 tx_tot_pkts;    /* # of tx pkts (ucast + mcast) */
	__le32 rx_tot_pkts;    /* # of data packets recvd (uni + mcast) */
	__le32 tx_mcast_pkts;  /* # of mcast pkts txed */
	__le64 tx_tot_bytes;   /* data bytes txed (ucast + mcast) */
	__le64 rx_tot_bytes;   /* data bytes recvd (ucast + mcast) */
	__le64 tx_ucast_bytes; /* data bytes txed (ucast) */
	__le64 tx_mcast_bytes; /* # data bytes txed (mcast) */
	__le64 rx_ucast_bytes; /* data bytes recvd (ucast) */
	__le64 rx_mcast_bytes; /* data bytes recvd (mcast) */
	s8 rssi[BRCMF_ANT_MAX];   /* per antenna rssi */
	s8 nf[BRCMF_ANT_MAX];     /* per antenna noise न्यूनमान */
	__le16 aid;                    /* association ID */
	__le16 ht_capabilities;        /* advertised ht caps */
	__le16 vht_flags;              /* converted vht flags */
	__le32 tx_pkts_retry_cnt;      /* # of frames where a retry was
					 * exhausted.
					 */
	__le32 tx_pkts_retry_exhausted; /* # of user frames where a retry
					 * was exhausted
					 */
	s8 rx_lastpkt_rssi[BRCMF_ANT_MAX]; /* Per antenna RSSI of last
					    * received data frame.
					    */
	/* TX WLAN retry/failure statistics:
	 * Separated क्रम host requested frames and locally generated frames.
	 * Include unicast frame only where the retries/failures can be counted.
	 */
	__le32 tx_pkts_total;          /* # user frames sent successfully */
	__le32 tx_pkts_retries;        /* # user frames retries */
	__le32 tx_pkts_fw_total;       /* # FW generated sent successfully */
	__le32 tx_pkts_fw_retries;     /* # retries क्रम FW generated frames */
	__le32 tx_pkts_fw_retry_exhausted;     /* # FW generated where a retry
						* was exhausted
						*/
	__le32 rx_pkts_retried;        /* # rx with retry bit set */
	__le32 tx_rate_fallback;       /* lowest fallback TX rate */

	जोड़ अणु
		काष्ठा अणु
			काष्ठा अणु
				__le32 count;					/* # rates in this set */
				u8 rates[BRCMF_MAXRATES_IN_SET];		/* rates in 500kbps units w/hi bit set अगर basic */
				u8 mcs[BRCMF_MCSSET_LEN];			/* supported mcs index bit map */
				__le16 vht_mcs[BRCMF_VHT_CAP_MCS_MAP_NSS_MAX];	/* supported mcs index bit map per nss */
			पूर्ण rateset_adv;
		पूर्ण v5;

		काष्ठा अणु
			__le32 rx_dur_total;	/* total user RX duration (estimated) */
			__le16 chanspec;	/** chanspec this sta is on */
			__le16 pad_1;
			काष्ठा अणु
				__le16 version;					/* version */
				__le16 len;					/* length */
				__le32 count;					/* # rates in this set */
				u8 rates[BRCMF_MAXRATES_IN_SET];		/* rates in 500kbps units w/hi bit set अगर basic */
				u8 mcs[BRCMF_MCSSET_LEN];			/* supported mcs index bit map */
				__le16 vht_mcs[BRCMF_VHT_CAP_MCS_MAP_NSS_MAX];	/* supported mcs index bit map per nss */
				__le16 he_mcs[BRCMF_HE_CAP_MCS_MAP_NSS_MAX];	/* supported he mcs index bit map per nss */
			पूर्ण rateset_adv;		/* rateset aदीर्घ with mcs index biपंचांगap */
			__le16 wpauth;		/* authentication type */
			u8 algo;		/* crypto algorithm */
			u8 pad_2;
			__le32 tx_rspec;	/* Rate of last successful tx frame */
			__le32 rx_rspec;	/* Rate of last successful rx frame */
			__le32 wnm_cap;		/* wnm capabilities */
		पूर्ण v7;
	पूर्ण;
पूर्ण;

काष्ठा brcmf_chanspec_list अणु
	__le32	count;		/* # of entries */
	__le32	element[1];	/* variable length uपूर्णांक32 list */
पूर्ण;

/*
 * WLC_E_PROBRESP_MSG
 * WLC_E_P2P_PROBREQ_MSG
 * WLC_E_ACTION_FRAME_RX
 */
काष्ठा brcmf_rx_mgmt_data अणु
	__be16	version;
	__be16	chanspec;
	__be32	rssi;
	__be32	maस_समय;
	__be32	rate;
पूर्ण;

/**
 * काष्ठा brcmf_fil_wowl_pattern_le - wowl pattern configuration काष्ठा.
 *
 * @cmd: "add", "del" or "clr".
 * @masksize: Size of the mask in #of bytes
 * @offset: Pattern byte offset in packet
 * @patternoffset: Offset of start of pattern. Starting from field masksize.
 * @patternsize: Size of the pattern itself in #of bytes
 * @id: id
 * @reasonsize: Size of the wakeup reason code
 * @type: Type of pattern (क्रमागत brcmf_wowl_pattern_type)
 */
काष्ठा brcmf_fil_wowl_pattern_le अणु
	u8	cmd[4];
	__le32	masksize;
	__le32	offset;
	__le32	patternoffset;
	__le32	patternsize;
	__le32	id;
	__le32	reasonsize;
	__le32	type;
	/* u8 mask[] - Mask follows the काष्ठाure above */
	/* u8 pattern[] - Pattern follows the mask is at 'patternoffset' */
पूर्ण;

काष्ठा brcmf_mbss_ssid_le अणु
	__le32	bsscfgidx;
	__le32	SSID_len;
	अचिन्हित अक्षर SSID[32];
पूर्ण;

/**
 * काष्ठा brcmf_fil_country_le - country configuration काष्ठाure.
 *
 * @country_abbrev: null-terminated country code used in the country IE.
 * @rev: revision specअगरier क्रम ccode. on set, -1 indicates unspecअगरied.
 * @ccode: null-terminated built-in country code.
 */
काष्ठा brcmf_fil_country_le अणु
	अक्षर country_abbrev[BRCMF_COUNTRY_BUF_SZ];
	__le32 rev;
	अक्षर ccode[BRCMF_COUNTRY_BUF_SZ];
पूर्ण;

/**
 * काष्ठा brcmf_rev_info_le - device revision info.
 *
 * @venकरोrid: PCI venकरोr id.
 * @deviceid: device id of chip.
 * @radiorev: radio revision.
 * @chiprev: chip revision.
 * @corerev: core revision.
 * @boardid: board identअगरier (usu. PCI sub-device id).
 * @boardvenकरोr: board venकरोr (usu. PCI sub-venकरोr id).
 * @boardrev: board revision.
 * @driverrev: driver version.
 * @ucoderev: microcode version.
 * @bus: bus type.
 * @chipnum: chip number.
 * @phytype: phy type.
 * @phyrev: phy revision.
 * @anarev: anacore rev.
 * @chippkg: chip package info.
 * @nvramrev: nvram revision number.
 */
काष्ठा brcmf_rev_info_le अणु
	__le32 venकरोrid;
	__le32 deviceid;
	__le32 radiorev;
	__le32 chiprev;
	__le32 corerev;
	__le32 boardid;
	__le32 boardvenकरोr;
	__le32 boardrev;
	__le32 driverrev;
	__le32 ucoderev;
	__le32 bus;
	__le32 chipnum;
	__le32 phytype;
	__le32 phyrev;
	__le32 anarev;
	__le32 chippkg;
	__le32 nvramrev;
पूर्ण;

/**
 * काष्ठा brcmf_assoclist_le - request assoc list.
 *
 * @count: indicates number of stations.
 * @mac: MAC addresses of stations.
 */
काष्ठा brcmf_assoclist_le अणु
	__le32 count;
	u8 mac[BRCMF_MAX_ASSOCLIST][ETH_ALEN];
पूर्ण;

/**
 * काष्ठा brcmf_rssi_be - RSSI threshold event क्रमmat
 *
 * @rssi: receive संकेत strength (in dBm)
 * @snr: संकेत-noise ratio
 * @noise: noise (in dBm)
 */
काष्ठा brcmf_rssi_be अणु
	__be32 rssi;
	__be32 snr;
	__be32 noise;
पूर्ण;

#घोषणा BRCMF_MAX_RSSI_LEVELS 8

/**
 * काष्ठा brcm_rssi_event_le - rssi_event IOVAR क्रमmat
 *
 * @rate_limit_msec: RSSI event rate limit
 * @rssi_level_num: number of supplied RSSI levels
 * @rssi_levels: RSSI levels in ascending order
 */
काष्ठा brcmf_rssi_event_le अणु
	__le32 rate_limit_msec;
	s8 rssi_level_num;
	s8 rssi_levels[BRCMF_MAX_RSSI_LEVELS];
पूर्ण;

/**
 * काष्ठा brcmf_wowl_wakeind_le - Wakeup indicators
 *	Note: note both fields contain same inक्रमmation.
 *
 * @pci_wakeind: Whether PCI PMECSR PMEStatus bit was set.
 * @ucode_wakeind: What wakeup-event indication was set by ucode
 */
काष्ठा brcmf_wowl_wakeind_le अणु
	__le32 pci_wakeind;
	__le32 ucode_wakeind;
पूर्ण;

/**
 * काष्ठा brcmf_pmksa - PMK Security Association
 *
 * @bssid: The AP's BSSID.
 * @pmkid: he PMK material itself.
 */
काष्ठा brcmf_pmksa अणु
	u8 bssid[ETH_ALEN];
	u8 pmkid[WLAN_PMKID_LEN];
पूर्ण;

/**
 * काष्ठा brcmf_pmk_list_le - List of pmksa's.
 *
 * @npmk: Number of pmksa's.
 * @pmk: PMK SA inक्रमmation.
 */
काष्ठा brcmf_pmk_list_le अणु
	__le32 npmk;
	काष्ठा brcmf_pmksa pmk[BRCMF_MAXPMKID];
पूर्ण;

/**
 * काष्ठा brcmf_pno_param_le - PNO scan configuration parameters
 *
 * @version: PNO parameters version.
 * @scan_freq: scan frequency.
 * @lost_network_समयout: #sec. to declare discovered network as lost.
 * @flags: Bit field to control features of PFN such as sort criteria स्वतः
 *	enable चयन and background scan.
 * @rssi_margin: Margin to aव्योम jitter क्रम choosing a PFN based on RSSI sort
 *	criteria.
 * @bestn: number of best networks in each scan.
 * @mscan: number of scans recorded.
 * @repeat: minimum number of scan पूर्णांकervals beक्रमe scan frequency changes
 *	in adaptive scan.
 * @exp: exponent of 2 क्रम maximum scan पूर्णांकerval.
 * @slow_freq: slow scan period.
 */
काष्ठा brcmf_pno_param_le अणु
	__le32 version;
	__le32 scan_freq;
	__le32 lost_network_समयout;
	__le16 flags;
	__le16 rssi_margin;
	u8 bestn;
	u8 mscan;
	u8 repeat;
	u8 exp;
	__le32 slow_freq;
पूर्ण;

/**
 * काष्ठा brcmf_pno_config_le - PNO channel configuration.
 *
 * @reporttype: determines what is reported.
 * @channel_num: number of channels specअगरied in @channel_list.
 * @channel_list: channels to use in PNO scan.
 * @flags: reserved.
 */
काष्ठा brcmf_pno_config_le अणु
	__le32  reporttype;
	__le32  channel_num;
	__le16  channel_list[BRCMF_NUMCHANNELS];
	__le32  flags;
पूर्ण;

/**
 * काष्ठा brcmf_pno_net_param_le - scan parameters per preferred network.
 *
 * @ssid: ssid name and its length.
 * @flags: bit2: hidden.
 * @infra: BSS vs IBSS.
 * @auth: Open vs Closed.
 * @wpa_auth: WPA type.
 * @wsec: wsec value.
 */
काष्ठा brcmf_pno_net_param_le अणु
	काष्ठा brcmf_ssid_le ssid;
	__le32 flags;
	__le32 infra;
	__le32 auth;
	__le32 wpa_auth;
	__le32 wsec;
पूर्ण;

/**
 * काष्ठा brcmf_pno_net_info_le - inक्रमmation per found network.
 *
 * @bssid: BSS network identअगरier.
 * @channel: channel number only.
 * @SSID_len: length of ssid.
 * @SSID: ssid अक्षरacters.
 * @RSSI: receive संकेत strength (in dBm).
 * @बारtamp: age in seconds.
 */
काष्ठा brcmf_pno_net_info_le अणु
	u8 bssid[ETH_ALEN];
	u8 channel;
	u8 SSID_len;
	u8 SSID[32];
	__le16	RSSI;
	__le16	बारtamp;
पूर्ण;

/**
 * काष्ठा brcmf_pno_scanresults_le - result वापसed in PNO NET FOUND event.
 *
 * @version: PNO version identअगरier.
 * @status: indicates completion status of PNO scan.
 * @count: amount of brcmf_pno_net_info_le entries appended.
 */
काष्ठा brcmf_pno_scanresults_le अणु
	__le32 version;
	__le32 status;
	__le32 count;
पूर्ण;

काष्ठा brcmf_pno_scanresults_v2_le अणु
	__le32 version;
	__le32 status;
	__le32 count;
	__le32 scan_ch_bucket;
पूर्ण;

/**
 * काष्ठा brcmf_pno_macaddr_le - to configure PNO macaddr अक्रमomization.
 *
 * @version: PNO version identअगरier.
 * @flags: Flags defining how mac addrss should be used.
 * @mac: MAC address.
 */
काष्ठा brcmf_pno_macaddr_le अणु
	u8 version;
	u8 flags;
	u8 mac[ETH_ALEN];
पूर्ण;

/**
 * काष्ठा brcmf_dload_data_le - data passing to firmware क्रम करोwnloading
 * @flag: flags related to करोwnload data.
 * @dload_type: type of करोwnload data.
 * @len: length in bytes of करोwnload data.
 * @crc: crc of करोwnload data.
 * @data: करोwnload data.
 */
काष्ठा brcmf_dload_data_le अणु
	__le16 flag;
	__le16 dload_type;
	__le32 len;
	__le32 crc;
	u8 data[1];
पूर्ण;

/**
 * काष्ठा brcmf_pno_bssid_le - bssid configuration क्रम PNO scan.
 *
 * @bssid: BSS network identअगरier.
 * @flags: flags क्रम this BSSID.
 */
काष्ठा brcmf_pno_bssid_le अणु
	u8 bssid[ETH_ALEN];
	__le16 flags;
पूर्ण;

/**
 * काष्ठा brcmf_pktcnt_le - packet counters.
 *
 * @rx_good_pkt: packets (MSDUs & MMPDUs) received from this station
 * @rx_bad_pkt: failed rx packets
 * @tx_good_pkt: packets (MSDUs & MMPDUs) transmitted to this station
 * @tx_bad_pkt: failed tx packets
 * @rx_ocast_good_pkt: unicast packets destined क्रम others
 */
काष्ठा brcmf_pktcnt_le अणु
	__le32 rx_good_pkt;
	__le32 rx_bad_pkt;
	__le32 tx_good_pkt;
	__le32 tx_bad_pkt;
	__le32 rx_ocast_good_pkt;
पूर्ण;

/**
 * काष्ठा brcmf_gtk_keyinfo_le - GTP rekey data
 *
 * @kck: key confirmation key.
 * @kek: key encryption key.
 * @replay_counter: replay counter.
 */
काष्ठा brcmf_gtk_keyinfo_le अणु
	u8 kck[BRCMF_RSN_KCK_LENGTH];
	u8 kek[BRCMF_RSN_KEK_LENGTH];
	u8 replay_counter[BRCMF_RSN_REPLAY_LEN];
पूर्ण;

#घोषणा BRCMF_PNO_REPORT_NO_BATCH	BIT(2)

/**
 * काष्ठा brcmf_gscan_bucket_config - configuration data क्रम channel bucket.
 *
 * @bucket_end_index: last channel index in @channel_list in
 *	@काष्ठा brcmf_pno_config_le.
 * @bucket_freq_multiple: scan पूर्णांकerval expressed in N * @scan_freq.
 * @flag: channel bucket report flags.
 * @reserved: क्रम future use.
 * @repeat: number of scan at पूर्णांकerval क्रम exponential scan.
 * @max_freq_multiple: maximum scan पूर्णांकerval क्रम exponential scan.
 */
काष्ठा brcmf_gscan_bucket_config अणु
	u8 bucket_end_index;
	u8 bucket_freq_multiple;
	u8 flag;
	u8 reserved;
	__le16 repeat;
	__le16 max_freq_multiple;
पूर्ण;

/* version supported which must match firmware */
#घोषणा BRCMF_GSCAN_CFG_VERSION                     2

/**
 * क्रमागत brcmf_gscan_cfg_flags - bit values क्रम gscan flags.
 *
 * @BRCMF_GSCAN_CFG_FLAGS_ALL_RESULTS: send probe responses/beacons to host.
 * @BRCMF_GSCAN_CFG_ALL_BUCKETS_IN_1ST_SCAN: all buckets will be included in
 *	first scan cycle.
 * @BRCMF_GSCAN_CFG_FLAGS_CHANGE_ONLY: indicated only flags member is changed.
 */
क्रमागत brcmf_gscan_cfg_flags अणु
	BRCMF_GSCAN_CFG_FLAGS_ALL_RESULTS = BIT(0),
	BRCMF_GSCAN_CFG_ALL_BUCKETS_IN_1ST_SCAN = BIT(3),
	BRCMF_GSCAN_CFG_FLAGS_CHANGE_ONLY = BIT(7),
पूर्ण;

/**
 * काष्ठा brcmf_gscan_config - configuration data क्रम gscan.
 *
 * @version: version of the api to match firmware.
 * @flags: flags according %क्रमागत brcmf_gscan_cfg_flags.
 * @buffer_threshold: percentage threshold of buffer to generate an event.
 * @swc_nbssid_threshold: number of BSSIDs with signअगरicant change that
 *	will generate an event.
 * @swc_rssi_winकरोw_size: size of rssi cache buffer (max=8).
 * @count_of_channel_buckets: number of array members in @bucket.
 * @retry_threshold: !unknown!
 * @lost_ap_winकरोw: !unknown!
 * @bucket: array of channel buckets.
 */
काष्ठा brcmf_gscan_config अणु
	__le16 version;
	u8 flags;
	u8 buffer_threshold;
	u8 swc_nbssid_threshold;
	u8 swc_rssi_winकरोw_size;
	u8 count_of_channel_buckets;
	u8 retry_threshold;
	__le16  lost_ap_winकरोw;
	काष्ठा brcmf_gscan_bucket_config bucket[1];
पूर्ण;

#पूर्ण_अगर /* FWIL_TYPES_H_ */
