<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2003 Herbert Valerio Riedel <hvr@gnu.org>
 *  Copyright (C) 2004 Luis R. Rodriguez <mcgrof@ruslug.rutgers.edu>
 *  Copyright (C) 2004 Aurelien Alleaume <slts@मुक्त.fr>
 */

#अगर !defined(_ISL_OID_H)
#घोषणा _ISL_OID_H

/*
 * MIB related स्थिरant and काष्ठाure definitions क्रम communicating
 * with the device firmware
 */

काष्ठा obj_ssid अणु
	u8 length;
	अक्षर octets[33];
पूर्ण __packed;

काष्ठा obj_key अणु
	u8 type;		/* करोt11_priv_t */
	u8 length;
	अक्षर key[32];
पूर्ण __packed;

काष्ठा obj_mlme अणु
	u8 address[6];
	u16 id;
	u16 state;
	u16 code;
पूर्ण __packed;

काष्ठा obj_mlmeex अणु
	u8 address[6];
	u16 id;
	u16 state;
	u16 code;
	u16 size;
	u8 data[];
पूर्ण __packed;

काष्ठा obj_buffer अणु
	u32 size;
	u32 addr;		/* 32bit bus address */
पूर्ण __packed;

काष्ठा obj_bss अणु
	u8 address[6];
	पूर्णांक:16;			/* padding */

	अक्षर state;
	अक्षर reserved;
	लघु age;

	अक्षर quality;
	अक्षर rssi;

	काष्ठा obj_ssid ssid;
	लघु channel;
	अक्षर beacon_period;
	अक्षर dtim_period;
	लघु capinfo;
	लघु rates;
	लघु basic_rates;
	पूर्णांक:16;			/* padding */
पूर्ण __packed;

काष्ठा obj_bsslist अणु
	u32 nr;
	काष्ठा obj_bss bsslist[];
पूर्ण __packed;

काष्ठा obj_frequencies अणु
	u16 nr;
	u16 mhz[];
पूर्ण __packed;

काष्ठा obj_attachment अणु
	अक्षर type;
	अक्षर reserved;
	लघु id;
	लघु size;
	अक्षर data[];
पूर्ण __packed;

/*
 * in हाल everything's ok, the अंतरभूतd function below will be
 * optimized away by the compiler...
 */
अटल अंतरभूत व्योम
__bug_on_wrong_काष्ठा_sizes(व्योम)
अणु
	BUILD_BUG_ON(माप (काष्ठा obj_ssid) != 34);
	BUILD_BUG_ON(माप (काष्ठा obj_key) != 34);
	BUILD_BUG_ON(माप (काष्ठा obj_mlme) != 12);
	BUILD_BUG_ON(माप (काष्ठा obj_mlmeex) != 14);
	BUILD_BUG_ON(माप (काष्ठा obj_buffer) != 8);
	BUILD_BUG_ON(माप (काष्ठा obj_bss) != 60);
	BUILD_BUG_ON(माप (काष्ठा obj_bsslist) != 4);
	BUILD_BUG_ON(माप (काष्ठा obj_frequencies) != 2);
पूर्ण

क्रमागत करोt11_state_t अणु
	DOT11_STATE_NONE = 0,
	DOT11_STATE_AUTHING = 1,
	DOT11_STATE_AUTH = 2,
	DOT11_STATE_ASSOCING = 3,

	DOT11_STATE_ASSOC = 5,
	DOT11_STATE_IBSS = 6,
	DOT11_STATE_WDS = 7
पूर्ण;

क्रमागत करोt11_bsstype_t अणु
	DOT11_BSSTYPE_NONE = 0,
	DOT11_BSSTYPE_INFRA = 1,
	DOT11_BSSTYPE_IBSS = 2,
	DOT11_BSSTYPE_ANY = 3
पूर्ण;

क्रमागत करोt11_auth_t अणु
	DOT11_AUTH_NONE = 0,
	DOT11_AUTH_OS = 1,
	DOT11_AUTH_SK = 2,
	DOT11_AUTH_BOTH = 3
पूर्ण;

क्रमागत करोt11_mlme_t अणु
	DOT11_MLME_AUTO = 0,
	DOT11_MLME_INTERMEDIATE = 1,
	DOT11_MLME_EXTENDED = 2
पूर्ण;

क्रमागत करोt11_priv_t अणु
	DOT11_PRIV_WEP = 0,
	DOT11_PRIV_TKIP = 1
पूर्ण;

/* Prism "Nitro" / Frameburst / "Packet Frame Grouping"
 * Value is in microseconds. Represents the # microseconds
 * the firmware will take to group frames beक्रमe sending out then out
 * together with a CSMA contention. Without this all frames are
 * sent with a CSMA contention.
 * Bibliography:
 * https://www.hpl.hp.com/personal/Jean_Tourrilhes/Papers/Packet.Frame.Grouping.hपंचांगl
 */
क्रमागत करोt11_maxframeburst_t अणु
	/* Values क्रम DOT11_OID_MAXFRAMEBURST */
	DOT11_MAXFRAMEBURST_OFF = 0, /* Card firmware शेष */
	DOT11_MAXFRAMEBURST_MIXED_SAFE = 650, /* 802.11 a,b,g safe */
	DOT11_MAXFRAMEBURST_IDEAL = 1300, /* Theoretical ideal level */
	DOT11_MAXFRAMEBURST_MAX = 5000, /* Use this as max,
		* Note: firmware allows क्रम greater values. This is a
		* recommended max. I'll update this as I find
		* out what the real MAX is. Also note that you करोn't necessarily
		* get better results with a greater value here.
		*/
पूर्ण;

/* Support क्रम 802.11 दीर्घ and लघु frame preambles.
 * Long	 preamble uses 128-bit sync field, 8-bit  CRC
 * Short preamble uses 56-bit  sync field, 16-bit CRC
 *
 * 802.11a -- not sure, both optionally ?
 * 802.11b supports दीर्घ and optionally लघु
 * 802.11g supports both */
क्रमागत करोt11_preamblesettings_t अणु
	DOT11_PREAMBLESETTING_LONG = 0,
		/* Allows *only* दीर्घ 802.11 preambles */
	DOT11_PREAMBLESETTING_SHORT = 1,
		/* Allows *only* लघु 802.11 preambles */
	DOT11_PREAMBLESETTING_DYNAMIC = 2
		/* AutomatiGically set */
पूर्ण;

/* Support क्रम 802.11 slot timing (समय between packets).
 *
 * Long uses 802.11a slot timing  (9 usec ?)
 * Short uses 802.11b slot timing (20 use ?) */
क्रमागत करोt11_slotsettings_t अणु
	DOT11_SLOTSETTINGS_LONG = 0,
		/* Allows *only* दीर्घ 802.11b slot timing */
	DOT11_SLOTSETTINGS_SHORT = 1,
		/* Allows *only* दीर्घ 802.11a slot timing */
	DOT11_SLOTSETTINGS_DYNAMIC = 2
		/* AutomatiGically set */
पूर्ण;

/* All you need to know, ERP is "Extended Rate PHY".
 * An Extended Rate PHY (ERP) STA or AP shall support three dअगरferent
 * preamble and header क्रमmats:
 * Long  preamble (refer to above)
 * Short preamble (refer to above)
 * OFDM  preamble ( ? )
 *
 * I'm assuming here Protection tells the AP
 * to be careful, a STA which cannot handle the दीर्घ pre-amble
 * has joined.
 */
क्रमागत करो11_nonerpstatus_t अणु
	DOT11_ERPSTAT_NONEPRESENT = 0,
	DOT11_ERPSTAT_USEPROTECTION = 1
पूर्ण;

/* (ERP is "Extended Rate PHY") Way to पढ़ो NONERP is NON-ERP-*
 * The key here is DOT11 NON ERP NEVER protects against
 * NON ERP STA's. You *don't* want this unless
 * you know what you are करोing. It means you will only
 * get Extended Rate capabilities */
क्रमागत करोt11_nonerpprotection_t अणु
	DOT11_NONERP_NEVER = 0,
	DOT11_NONERP_ALWAYS = 1,
	DOT11_NONERP_DYNAMIC = 2
पूर्ण;

/* Preset OID configuration क्रम 802.11 modes
 * Note: DOT11_OID_CW[MIN|MAX] hold the values of the
 * DCS MIN|MAX backoff used */
क्रमागत करोt11_profile_t अणु /* And set/allowed values */
	/* Allowed values क्रम DOT11_OID_PROखाताS */
	DOT11_PROखाता_B_ONLY = 0,
		/* DOT11_OID_RATES: 1, 2, 5.5, 11Mbps
		 * DOT11_OID_PREAMBLESETTINGS: DOT11_PREAMBLESETTING_DYNAMIC
		 * DOT11_OID_CWMIN: 31
		 * DOT11_OID_NONEPROTECTION: DOT11_NOERP_DYNAMIC
		 * DOT11_OID_SLOTSETTINGS: DOT11_SLOTSETTINGS_LONG
		 */
	DOT11_PROखाता_MIXED_G_WIFI = 1,
		/* DOT11_OID_RATES: 1, 2, 5.5, 11, 6, 9, 12, 18, 24, 36, 48, 54Mbs
		 * DOT11_OID_PREAMBLESETTINGS: DOT11_PREAMBLESETTING_DYNAMIC
		 * DOT11_OID_CWMIN: 15
		 * DOT11_OID_NONEPROTECTION: DOT11_NOERP_DYNAMIC
		 * DOT11_OID_SLOTSETTINGS: DOT11_SLOTSETTINGS_DYNAMIC
		 */
	DOT11_PROखाता_MIXED_LONG = 2, /* "Long range" */
		/* Same as Profile MIXED_G_WIFI */
	DOT11_PROखाता_G_ONLY = 3,
		/* Same as Profile MIXED_G_WIFI */
	DOT11_PROखाता_TEST = 4,
		/* Same as Profile MIXED_G_WIFI except:
		 * DOT11_OID_PREAMBLESETTINGS: DOT11_PREAMBLESETTING_SHORT
		 * DOT11_OID_NONEPROTECTION: DOT11_NOERP_NEVER
		 * DOT11_OID_SLOTSETTINGS: DOT11_SLOTSETTINGS_SHORT
		 */
	DOT11_PROखाता_B_WIFI = 5,
		/* Same as Profile B_ONLY */
	DOT11_PROखाता_A_ONLY = 6,
		/* Same as Profile MIXED_G_WIFI except:
		 * DOT11_OID_RATES: 6, 9, 12, 18, 24, 36, 48, 54Mbs
		 */
	DOT11_PROखाता_MIXED_SHORT = 7
		/* Same as MIXED_G_WIFI */
पूर्ण;


/* The करोt11d conक्रमmance level configures the 802.11d conक्रमmance levels.
 * The following conक्रमmance levels exist:*/
क्रमागत oid_inl_conक्रमmance_t अणु
	OID_INL_CONFORMANCE_NONE = 0,	/* Perक्रमm active scanning */
	OID_INL_CONFORMANCE_STRICT = 1,	/* Strictly adhere to 802.11d */
	OID_INL_CONFORMANCE_FLEXIBLE = 2,	/* Use passed 802.11d info to
		* determine channel AND/OR just make assumption that active
		* channels are valid  channels */
पूर्ण;

क्रमागत oid_inl_mode_t अणु
	INL_MODE_NONE = -1,
	INL_MODE_PROMISCUOUS = 0,
	INL_MODE_CLIENT = 1,
	INL_MODE_AP = 2,
	INL_MODE_SNIFFER = 3
पूर्ण;

क्रमागत oid_inl_config_t अणु
	INL_CONFIG_NOTHING = 0x00,
	INL_CONFIG_MANUALRUN = 0x01,
	INL_CONFIG_FRAMETRAP = 0x02,
	INL_CONFIG_RXANNEX = 0x04,
	INL_CONFIG_TXANNEX = 0x08,
	INL_CONFIG_WDS = 0x10
पूर्ण;

क्रमागत oid_inl_phycap_t अणु
	INL_PHYCAP_2400MHZ = 1,
	INL_PHYCAP_5000MHZ = 2,
	INL_PHYCAP_FAA = 0x80000000,	/* Means card supports the FAA चयन */
पूर्ण;


क्रमागत oid_num_t अणु
	GEN_OID_MACADDRESS = 0,
	GEN_OID_LINKSTATE,
	GEN_OID_WATCHDOG,
	GEN_OID_MIBOP,
	GEN_OID_OPTIONS,
	GEN_OID_LEDCONFIG,

	/* 802.11 */
	DOT11_OID_BSSTYPE,
	DOT11_OID_BSSID,
	DOT11_OID_SSID,
	DOT11_OID_STATE,
	DOT11_OID_AID,
	DOT11_OID_COUNTRYSTRING,
	DOT11_OID_SSIDOVERRIDE,

	DOT11_OID_MEDIUMLIMIT,
	DOT11_OID_BEACONPERIOD,
	DOT11_OID_DTIMPERIOD,
	DOT11_OID_ATIMWINDOW,
	DOT11_OID_LISTENINTERVAL,
	DOT11_OID_CFPPERIOD,
	DOT11_OID_CFPDURATION,

	DOT11_OID_AUTHENABLE,
	DOT11_OID_PRIVACYINVOKED,
	DOT11_OID_EXUNENCRYPTED,
	DOT11_OID_DEFKEYID,
	DOT11_OID_DEFKEYX,	/* DOT11_OID_DEFKEY1,...DOT11_OID_DEFKEY4 */
	DOT11_OID_STAKEY,
	DOT11_OID_REKEYTHRESHOLD,
	DOT11_OID_STASC,

	DOT11_OID_PRIVTXREJECTED,
	DOT11_OID_PRIVRXPLAIN,
	DOT11_OID_PRIVRXFAILED,
	DOT11_OID_PRIVRXNOKEY,

	DOT11_OID_RTSTHRESH,
	DOT11_OID_FRAGTHRESH,
	DOT11_OID_SHORTRETRIES,
	DOT11_OID_LONGRETRIES,
	DOT11_OID_MAXTXLIFETIME,
	DOT11_OID_MAXRXLIFETIME,
	DOT11_OID_AUTHRESPTIMEOUT,
	DOT11_OID_ASSOCRESPTIMEOUT,

	DOT11_OID_ALOFT_TABLE,
	DOT11_OID_ALOFT_CTRL_TABLE,
	DOT11_OID_ALOFT_RETREAT,
	DOT11_OID_ALOFT_PROGRESS,
	DOT11_OID_ALOFT_FIXEDRATE,
	DOT11_OID_ALOFT_RSSIGRAPH,
	DOT11_OID_ALOFT_CONFIG,

	DOT11_OID_VDCFX,
	DOT11_OID_MAXFRAMEBURST,

	DOT11_OID_PSM,
	DOT11_OID_CAMTIMEOUT,
	DOT11_OID_RECEIVEDTIMS,
	DOT11_OID_ROAMPREFERENCE,

	DOT11_OID_BRIDGELOCAL,
	DOT11_OID_CLIENTS,
	DOT11_OID_CLIENTSASSOCIATED,
	DOT11_OID_CLIENTX,	/* DOT11_OID_CLIENTX,...DOT11_OID_CLIENT2007 */

	DOT11_OID_CLIENTFIND,
	DOT11_OID_WDSLINKADD,
	DOT11_OID_WDSLINKREMOVE,
	DOT11_OID_EAPAUTHSTA,
	DOT11_OID_EAPUNAUTHSTA,
	DOT11_OID_DOT1XENABLE,
	DOT11_OID_MICFAILURE,
	DOT11_OID_REKEYINDICATE,

	DOT11_OID_MPDUTXSUCCESSFUL,
	DOT11_OID_MPDUTXONERETRY,
	DOT11_OID_MPDUTXMULTIPLERETRIES,
	DOT11_OID_MPDUTXFAILED,
	DOT11_OID_MPDURXSUCCESSFUL,
	DOT11_OID_MPDURXDUPS,
	DOT11_OID_RTSSUCCESSFUL,
	DOT11_OID_RTSFAILED,
	DOT11_OID_ACKFAILED,
	DOT11_OID_FRAMERECEIVES,
	DOT11_OID_FRAMEERRORS,
	DOT11_OID_FRAMEABORTS,
	DOT11_OID_FRAMEABORTSPHY,

	DOT11_OID_SLOTTIME,
	DOT11_OID_CWMIN, /* MIN DCS backoff */
	DOT11_OID_CWMAX, /* MAX DCS backoff */
	DOT11_OID_ACKWINDOW,
	DOT11_OID_ANTENNARX,
	DOT11_OID_ANTENNATX,
	DOT11_OID_ANTENNADIVERSITY,
	DOT11_OID_CHANNEL,
	DOT11_OID_EDTHRESHOLD,
	DOT11_OID_PREAMBLESETTINGS,
	DOT11_OID_RATES,
	DOT11_OID_CCAMODESUPPORTED,
	DOT11_OID_CCAMODE,
	DOT11_OID_RSSIVECTOR,
	DOT11_OID_OUTPUTPOWERTABLE,
	DOT11_OID_OUTPUTPOWER,
	DOT11_OID_SUPPORTEDRATES,
	DOT11_OID_FREQUENCY,
	DOT11_OID_SUPPORTEDFREQUENCIES,
	DOT11_OID_NOISEFLOOR,
	DOT11_OID_FREQUENCYACTIVITY,
	DOT11_OID_IQCALIBRATIONTABLE,
	DOT11_OID_NONERPPROTECTION,
	DOT11_OID_SLOTSETTINGS,
	DOT11_OID_NONERPTIMEOUT,
	DOT11_OID_PROखाताS,
	DOT11_OID_EXTENDEDRATES,

	DOT11_OID_DEAUTHENTICATE,
	DOT11_OID_AUTHENTICATE,
	DOT11_OID_DISASSOCIATE,
	DOT11_OID_ASSOCIATE,
	DOT11_OID_SCAN,
	DOT11_OID_BEACON,
	DOT11_OID_PROBE,
	DOT11_OID_DEAUTHENTICATEEX,
	DOT11_OID_AUTHENTICATEEX,
	DOT11_OID_DISASSOCIATEEX,
	DOT11_OID_ASSOCIATEEX,
	DOT11_OID_REASSOCIATE,
	DOT11_OID_REASSOCIATEEX,

	DOT11_OID_NONERPSTATUS,

	DOT11_OID_STATIMEOUT,
	DOT11_OID_MLMEAUTOLEVEL,
	DOT11_OID_BSSTIMEOUT,
	DOT11_OID_ATTACHMENT,
	DOT11_OID_PSMBUFFER,

	DOT11_OID_BSSS,
	DOT11_OID_BSSX,		/*DOT11_OID_BSS1,...,DOT11_OID_BSS64 */
	DOT11_OID_BSSFIND,
	DOT11_OID_BSSLIST,

	OID_INL_TUNNEL,
	OID_INL_MEMADDR,
	OID_INL_MEMORY,
	OID_INL_MODE,
	OID_INL_COMPONENT_NR,
	OID_INL_VERSION,
	OID_INL_INTERFACE_ID,
	OID_INL_COMPONENT_ID,
	OID_INL_CONFIG,
	OID_INL_DOT11D_CONFORMANCE,
	OID_INL_PHYCAPABILITIES,
	OID_INL_OUTPUTPOWER,

	OID_NUM_LAST
पूर्ण;

#घोषणा OID_FLAG_CACHED		0x80
#घोषणा OID_FLAG_TYPE		0x7f

#घोषणा OID_TYPE_U32		0x01
#घोषणा OID_TYPE_SSID		0x02
#घोषणा OID_TYPE_KEY		0x03
#घोषणा OID_TYPE_BUFFER		0x04
#घोषणा OID_TYPE_BSS		0x05
#घोषणा OID_TYPE_BSSLIST	0x06
#घोषणा OID_TYPE_FREQUENCIES	0x07
#घोषणा OID_TYPE_MLME		0x08
#घोषणा OID_TYPE_MLMEEX		0x09
#घोषणा OID_TYPE_ADDR		0x0A
#घोषणा OID_TYPE_RAW		0x0B
#घोषणा OID_TYPE_ATTACH		0x0C

/* OID_TYPE_MLMEEX is special because of a variable size field when sending.
 * Not yet implemented (not used in driver anyway).
 */

काष्ठा oid_t अणु
	क्रमागत oid_num_t oid;
	लघु range;		/* to define a range of oid */
	लघु size;		/* max size of the associated data */
	अक्षर flags;
पूर्ण;

जोड़ oid_res_t अणु
	व्योम *ptr;
	u32 u;
पूर्ण;

#घोषणा	IWMAX_BITRATES	20
#घोषणा	IWMAX_BSS	24
#घोषणा IWMAX_FREQ	30
#घोषणा PRIV_STR_SIZE	1024

#पूर्ण_अगर				/* !defined(_ISL_OID_H) */
/* खातापूर्ण */
