<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __WLAN_BSSDEF_H__
#घोषणा __WLAN_BSSDEF_H__

#घोषणा MAX_IE_SZ			768

#घोषणा NDIS_802_11_LENGTH_SSID         32
#घोषणा NDIS_802_11_LENGTH_RATES        8
#घोषणा NDIS_802_11_LENGTH_RATES_EX     16

#घोषणा NDIS_802_11_RSSI दीर्घ           /*  in dBm */

काष्ठा ndis_802_11_ssid अणु
	u32  ssid_length;
	u8  ssid[32];
पूर्ण;

क्रमागत NDIS_802_11_NETWORK_TYPE अणु
	Ndis802_11FH,
	Ndis802_11DS,
	Ndis802_11OFDM5,
	Ndis802_11OFDM24,
	Ndis802_11NetworkTypeMax    /*  dummy upper bound */
पूर्ण;

काष्ठा ndis_802_11_config_fh अणु
	u32           Length;		/*  Length of काष्ठाure */
	u32           HopPattern;	/*  As defined by 802.11, MSB set */
	u32           HopSet;		/*  to one अगर non-802.11 */
	u32           DwellTime;	/*  units are Kusec */
पूर्ण;

/*
 *	FW will only save the channel number in DSConfig.
 *	ODI Handler will convert the channel number to freq. number.
 */
काष्ठा ndis_802_11_config अणु
	u32           Length;             /*  Length of काष्ठाure */
	u32           BeaconPeriod;       /*  units are Kusec */
	u32           ATIMWinकरोw;         /*  units are Kusec */
	u32           DSConfig;           /*  Frequency, units are kHz */
	काष्ठा ndis_802_11_config_fh    FHConfig;
पूर्ण;

क्रमागत ndis_802_11_network_infra अणु
	Ndis802_11IBSS,
	Ndis802_11Infraकाष्ठाure,
	Ndis802_11AutoUnknown,
	Ndis802_11Infraकाष्ठाureMax,     /*  dummy upper bound */
	Ndis802_11APMode
पूर्ण;

काष्ठा ndis_802_11_fixed_ie अणु
	u8  Timestamp[8];
	u16  BeaconInterval;
	u16  Capabilities;
पूर्ण;

काष्ठा ndis_802_11_var_ie अणु
	u8  ElementID;
	u8  Length;
	u8  data[];
पूर्ण;

/*
 * Length is the 4 bytes multiples of the sume of
 *	[ETH_ALEN] + 2 + माप (काष्ठा ndis_802_11_ssid) + माप (u32)
 *	+ माप (NDIS_802_11_RSSI) + माप (क्रमागत NDIS_802_11_NETWORK_TYPE)
 *	+ माप (काष्ठा ndis_802_11_config)
 *	+ NDIS_802_11_LENGTH_RATES_EX + ie_length
 *
 * Except the ie_length, all other fields are fixed length.
 * Thereक्रमe, we can define a macro to represent the partial sum.
 */

क्रमागत ndis_802_11_auth_mode अणु
	Ndis802_11AuthModeOpen,
	Ndis802_11AuthModeShared,
	Ndis802_11AuthModeAutoSwitch,
	Ndis802_11AuthModeWPA,
	Ndis802_11AuthModeWPAPSK,
	Ndis802_11AuthModeWPANone,
	Ndis802_11AuthModeWAPI,
	Ndis802_11AuthModeMax	/*  Not a real mode, upper bound */
पूर्ण;

क्रमागत ndis_802_11_wep_status अणु
	Ndis802_11WEPEnabled,
	Ndis802_11Encryption1Enabled = Ndis802_11WEPEnabled,
	Ndis802_11WEPDisabled,
	Ndis802_11EncryptionDisabled = Ndis802_11WEPDisabled,
	Ndis802_11WEPKeyAbsent,
	Ndis802_11Encryption1KeyAbsent = Ndis802_11WEPKeyAbsent,
	Ndis802_11WEPNotSupported,
	Ndis802_11EncryptionNotSupported = Ndis802_11WEPNotSupported,
	Ndis802_11Encryption2Enabled,
	Ndis802_11Encryption2KeyAbsent,
	Ndis802_11Encryption3Enabled,
	Ndis802_11Encryption3KeyAbsent,
	Ndis802_11_EncryptionWAPI
पूर्ण;

#घोषणा NDIS_802_11_AI_REQFI_CAPABILITIES      1
#घोषणा NDIS_802_11_AI_REQFI_LISTENINTERVAL    2
#घोषणा NDIS_802_11_AI_REQFI_CURRENTAPADDRESS  4

#घोषणा NDIS_802_11_AI_RESFI_CAPABILITIES      1
#घोषणा NDIS_802_11_AI_RESFI_STATUSCODE        2
#घोषणा NDIS_802_11_AI_RESFI_ASSOCIATIONID     4

क्रमागत ndis_802_11_reload_def अणु
	Ndis802_11ReloadWEPKeys
पूर्ण;

काष्ठा ndis_802_11_wep अणु
	u32     Length;        /*  Length of this काष्ठाure */
	u32     KeyIndex;      /*  0 is the per-client key,
				* 1-N are the global keys
				*/
	u32     KeyLength;     /*  length of key in bytes */
	u8     KeyMaterial[16];/*  variable len depending on above field */
पूर्ण;

क्रमागत ndis_802_11_status_type अणु
	Ndis802_11StatusType_Authentication,
	Ndis802_11StatusType_MediaStreamMode,
	Ndis802_11StatusType_PMKID_CandidateList,
	Ndis802_11StatusTypeMax    /*  not a real type, defined as
				    * an upper bound
				    */
पूर्ण;

/*  mask क्रम authentication/पूर्णांकegrity fields */
#घोषणा NDIS_802_11_AUTH_REQUEST_AUTH_FIELDS        	0x0f
#घोषणा NDIS_802_11_AUTH_REQUEST_REAUTH			0x01
#घोषणा NDIS_802_11_AUTH_REQUEST_KEYUPDATE		0x02
#घोषणा NDIS_802_11_AUTH_REQUEST_PAIRWISE_ERROR		0x06
#घोषणा NDIS_802_11_AUTH_REQUEST_GROUP_ERROR		0x0E

/*  MIC check समय, 60 seconds. */
#घोषणा MIC_CHECK_TIME	60000000

#अगर_अघोषित Ndis802_11APMode
#घोषणा Ndis802_11APMode (Ndis802_11Infraकाष्ठाureMax + 1)
#पूर्ण_अगर

काष्ठा wlan_phy_info अणु
	u8	SignalStrength;/* in percentage) */
	u8	SignalQuality;/* in percentage) */
	u8	Optimum_antenna;  /* क्रम Antenna भागersity */
	u8	Reserved_0;
पूर्ण;

काष्ठा wlan_bcn_info अणु
	/* these inक्रम get from rtw_get_encrypt_info when
	 *	 * translate scan to UI
	 */
	u8 encryp_protocol;/* ENCRYP_PROTOCOL_E: OPEN/WEP/WPA/WPA2/WAPI */
	पूर्णांक group_cipher; /* WPA/WPA2 group cipher */
	पूर्णांक pairwise_cipher;/* WPA/WPA2/WEP pairwise cipher */
	पूर्णांक is_8021x;

	/* bwmode 20/40 and ch_offset UP/LOW */
	अचिन्हित लघु	ht_cap_info;
	अचिन्हित अक्षर	ht_info_infos_0;
पूर्ण;

/* temporally add #आशय pack क्रम काष्ठाure alignment issue of
 *   काष्ठा wlan_bssid_ex and get_काष्ठा wlan_bssid_ex_sz()
 */
काष्ठा wlan_bssid_ex अणु
	u32  Length;
	अचिन्हित अक्षर MacAddress[ETH_ALEN];
	u8  Reserved[2];/* 0]: IS beacon frame */
	काष्ठा ndis_802_11_ssid  ssid;
	u32  Privacy;
	NDIS_802_11_RSSI  Rssi;/* in dBM,raw data ,get from PHY) */
	क्रमागत  NDIS_802_11_NETWORK_TYPE  NetworkTypeInUse;
	काष्ठा ndis_802_11_config  Configuration;
	क्रमागत ndis_802_11_network_infra  Infraकाष्ठाureMode;
	अचिन्हित अक्षर SupportedRates[NDIS_802_11_LENGTH_RATES_EX];
	काष्ठा wlan_phy_info	PhyInfo;
	u32  ie_length;
	u8  ies[MAX_IE_SZ];	/* बारtamp, beacon पूर्णांकerval, and
				 * capability inक्रमmation)
				 */
पूर्ण __packed;

अटल अंतरभूत uपूर्णांक get_wlan_bssid_ex_sz(काष्ठा wlan_bssid_ex *bss)
अणु
	वापस माप(काष्ठा wlan_bssid_ex) - MAX_IE_SZ + bss->ie_length;
पूर्ण

काष्ठा	wlan_network अणु
	काष्ठा list_head list;
	पूर्णांक	network_type;	/* refer to ieee80211.h क्रम WIRELESS_11A/B/G */
	पूर्णांक	fixed;		/*  set fixed when not to be हटाओd
				 *  in site-surveying
				 */
	अचिन्हित दीर्घ	last_scanned; /* बारtamp क्रम the network */
	पूर्णांक	aid;		/* will only be valid when a BSS is joinned. */
	पूर्णांक	join_res;
	काष्ठा wlan_bssid_ex	network; /* must be the last item */
	काष्ठा wlan_bcn_info	BcnInfo;
पूर्ण;

क्रमागत VRTL_CARRIER_SENSE अणु
	DISABLE_VCS,
	ENABLE_VCS,
	AUTO_VCS
पूर्ण;

क्रमागत VCS_TYPE अणु
	NONE_VCS,
	RTS_CTS,
	CTS_TO_SELF
पूर्ण;

#घोषणा PWR_CAM 0
#घोषणा PWR_MINPS 1
#घोषणा PWR_MAXPS 2
#घोषणा PWR_UAPSD 3
#घोषणा PWR_VOIP 4

क्रमागत UAPSD_MAX_SP अणु
	NO_LIMIT,
	TWO_MSDU,
	FOUR_MSDU,
	SIX_MSDU
पूर्ण;

#घोषणा NUM_PRE_AUTH_KEY 16
#घोषणा NUM_PMKID_CACHE NUM_PRE_AUTH_KEY

#पूर्ण_अगर /* अगरndef WLAN_BSSDEF_H_ */
