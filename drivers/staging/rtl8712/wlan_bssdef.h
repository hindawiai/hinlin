<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित __WLAN_BSSDEF_H__
#घोषणा __WLAN_BSSDEF_H__

#घोषणा MAX_IE_SZ	768

#घोषणा NDIS_802_11_LENGTH_SSID         32
#घोषणा NDIS_802_11_LENGTH_RATES        8
#घोषणा NDIS_802_11_LENGTH_RATES_EX     16

काष्ठा ndis_802_11_ssid अणु
	u32 SsidLength;
	u8  Ssid[32];
पूर्ण;

क्रमागत NDIS_802_11_NETWORK_TYPE अणु
	Ndis802_11FH,
	Ndis802_11DS,
	Ndis802_11OFDM5,
	Ndis802_11OFDM24,
	Ndis802_11NetworkTypeMax /* not a real type, defined as an upper bound*/
पूर्ण;

काष्ठा NDIS_802_11_CONFIGURATION_FH अणु
	u32 Length;             /* Length of काष्ठाure */
	u32 HopPattern;         /* As defined by 802.11, MSB set */
	u32 HopSet;             /* to one अगर non-802.11 */
	u32 DwellTime;          /* units are Kusec */
पूर्ण;

/*
 * FW will only save the channel number in DSConfig.
 * ODI Handler will convert the channel number to freq. number.
 */
काष्ठा NDIS_802_11_CONFIGURATION अणु
	u32 Length;             /* Length of काष्ठाure */
	u32 BeaconPeriod;       /* units are Kusec */
	u32 ATIMWinकरोw;         /* units are Kusec */
	u32 DSConfig;           /* Frequency, units are kHz */
	काष्ठा NDIS_802_11_CONFIGURATION_FH FHConfig;
पूर्ण;

क्रमागत NDIS_802_11_NETWORK_INFRASTRUCTURE अणु
	Ndis802_11IBSS,
	Ndis802_11Infraकाष्ठाure,
	Ndis802_11AutoUnknown,
	Ndis802_11Infraकाष्ठाureMax, /*Not a real value,defined as upper bound*/
	Ndis802_11APMode
पूर्ण;

काष्ठा NDIS_802_11_FIXED_IEs अणु
	u8  Timestamp[8];
	u16 BeaconInterval;
	u16 Capabilities;
पूर्ण;

काष्ठा wlan_bssid_ex अणु
	u32 Length;
	अचिन्हित अक्षर  MacAddress[6];
	u8  Reserved[2];
	काष्ठा ndis_802_11_ssid  Ssid;
	__le32 Privacy;
	s32 Rssi;
	क्रमागत NDIS_802_11_NETWORK_TYPE  NetworkTypeInUse;
	काष्ठा NDIS_802_11_CONFIGURATION  Configuration;
	क्रमागत NDIS_802_11_NETWORK_INFRASTRUCTURE  Infraकाष्ठाureMode;
	u8 rates[NDIS_802_11_LENGTH_RATES_EX];
	/* number of content bytes in EIs, which varies */
	u32 IELength;
	/*(बारtamp, beacon पूर्णांकerval, and capability inक्रमmation) */
	u8 IEs[MAX_IE_SZ];
पूर्ण;

क्रमागत NDIS_802_11_AUTHENTICATION_MODE अणु
	Ndis802_11AuthModeOpen,
	Ndis802_11AuthModeShared,
	Ndis802_11AuthModeAutoSwitch,
	Ndis802_11AuthModeWPA,
	Ndis802_11AuthModeWPAPSK,
	Ndis802_11AuthModeWPANone,
	Ndis802_11AuthModeMax      /* Not a real mode, defined as upper bound */
पूर्ण;

क्रमागत अणु
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
	Ndis802_11Encryption3KeyAbsent
पूर्ण;

#घोषणा NDIS_802_11_AI_REQFI_CAPABILITIES      1
#घोषणा NDIS_802_11_AI_REQFI_LISTENINTERVAL    2
#घोषणा NDIS_802_11_AI_REQFI_CURRENTAPADDRESS  4

#घोषणा NDIS_802_11_AI_RESFI_CAPABILITIES      1
#घोषणा NDIS_802_11_AI_RESFI_STATUSCODE        2
#घोषणा NDIS_802_11_AI_RESFI_ASSOCIATIONID     4

काष्ठा NDIS_802_11_AI_REQFI अणु
	u16 Capabilities;
	u16 ListenInterval;
	अचिन्हित अक्षर CurrentAPAddress[6];
पूर्ण;

काष्ठा NDIS_802_11_AI_RESFI अणु
	u16 Capabilities;
	u16 StatusCode;
	u16 AssociationId;
पूर्ण;

काष्ठा NDIS_802_11_ASSOCIATION_INFORMATION अणु
	u32 Length;
	u16 AvailableRequestFixedIEs;
	काष्ठा NDIS_802_11_AI_REQFI RequestFixedIEs;
	u32 RequestIELength;
	u32 OffsetRequestIEs;
	u16 AvailableResponseFixedIEs;
	काष्ठा NDIS_802_11_AI_RESFI ResponseFixedIEs;
	u32 ResponseIELength;
	u32 OffsetResponseIEs;
पूर्ण;

/* Key mapping keys require a BSSID*/
काष्ठा NDIS_802_11_KEY अणु
	u32 Length;			/* Length of this काष्ठाure */
	u32 KeyIndex;
	u32 KeyLength;			/* length of key in bytes */
	अचिन्हित अक्षर BSSID[6];
	अचिन्हित दीर्घ दीर्घ KeyRSC;
	u8  KeyMaterial[32];		/* variable length */
पूर्ण;

काष्ठा NDIS_802_11_REMOVE_KEY अणु
	u32 Length;			/* Length of this काष्ठाure */
	u32 KeyIndex;
	अचिन्हित अक्षर BSSID[6];
पूर्ण;

काष्ठा NDIS_802_11_WEP अणु
	u32 Length;		  /* Length of this काष्ठाure */
	u32 KeyIndex;		  /* 0 is the per-client key,
				   * 1-N are the global keys
				   */
	u32 KeyLength;		  /* length of key in bytes */
	u8  KeyMaterial[16];      /* variable length depending on above field */
पूर्ण;

/* mask क्रम authentication/पूर्णांकegrity fields */
#घोषणा NDIS_802_11_AUTH_REQUEST_AUTH_FIELDS        0x0f
#घोषणा NDIS_802_11_AUTH_REQUEST_REAUTH			0x01
#घोषणा NDIS_802_11_AUTH_REQUEST_KEYUPDATE		0x02
#घोषणा NDIS_802_11_AUTH_REQUEST_PAIRWISE_ERROR		0x06
#घोषणा NDIS_802_11_AUTH_REQUEST_GROUP_ERROR		0x0E

/* MIC check समय, 60 seconds. */
#घोषणा MIC_CHECK_TIME	60000000

#अगर_अघोषित Ndis802_11APMode
#घोषणा Ndis802_11APMode (Ndis802_11Infraकाष्ठाureMax + 1)
#पूर्ण_अगर

काष्ठा	wlan_network अणु
	काष्ठा list_head list;
	पूर्णांक	network_type;	/*refer to ieee80211.h क्रम WIRELESS_11A/B/G */
	पूर्णांक	fixed;		/* set to fixed when not to be हटाओd asi
				 * site-surveying
				 */
	अचिन्हित पूर्णांक	last_scanned; /*बारtamp क्रम the network */
	पूर्णांक	aid;		/*will only be valid when a BSS is joined. */
	पूर्णांक	join_res;
	काष्ठा wlan_bssid_ex network; /*must be the last item */
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

#पूर्ण_अगर /* #अगर_अघोषित WLAN_BSSDEF_H_ */

