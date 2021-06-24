<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header file contains definition क्रम global types
 */
#अगर_अघोषित _LBS_TYPES_H_
#घोषणा _LBS_TYPES_H_

#समावेश <linux/अगर_ether.h>
#समावेश <linux/ieee80211.h>
#समावेश <यंत्र/byteorder.h>

काष्ठा ieee_ie_header अणु
	u8 id;
	u8 len;
पूर्ण __packed;

काष्ठा ieee_ie_cf_param_set अणु
	काष्ठा ieee_ie_header header;

	u8 cfpcnt;
	u8 cfpperiod;
	__le16 cfpmaxduration;
	__le16 cfpdurationreमुख्यing;
पूर्ण __packed;


काष्ठा ieee_ie_ibss_param_set अणु
	काष्ठा ieee_ie_header header;

	__le16 atimwinकरोw;
पूर्ण __packed;

जोड़ ieee_ss_param_set अणु
	काष्ठा ieee_ie_cf_param_set cf;
	काष्ठा ieee_ie_ibss_param_set ibss;
पूर्ण __packed;

काष्ठा ieee_ie_fh_param_set अणु
	काष्ठा ieee_ie_header header;

	__le16 dwellसमय;
	u8 hopset;
	u8 hoppattern;
	u8 hopindex;
पूर्ण __packed;

काष्ठा ieee_ie_ds_param_set अणु
	काष्ठा ieee_ie_header header;

	u8 channel;
पूर्ण __packed;

जोड़ ieee_phy_param_set अणु
	काष्ठा ieee_ie_fh_param_set fh;
	काष्ठा ieee_ie_ds_param_set ds;
पूर्ण __packed;

/* TLV  type ID definition */
#घोषणा PROPRIETARY_TLV_BASE_ID		0x0100

/* Terminating TLV type */
#घोषणा MRVL_TERMINATE_TLV_ID		0xffff

#घोषणा TLV_TYPE_SSID				0x0000
#घोषणा TLV_TYPE_RATES				0x0001
#घोषणा TLV_TYPE_PHY_FH				0x0002
#घोषणा TLV_TYPE_PHY_DS				0x0003
#घोषणा TLV_TYPE_CF				    0x0004
#घोषणा TLV_TYPE_IBSS				0x0006

#घोषणा TLV_TYPE_DOMAIN				0x0007

#घोषणा TLV_TYPE_POWER_CAPABILITY	0x0021

#घोषणा TLV_TYPE_KEY_MATERIAL       (PROPRIETARY_TLV_BASE_ID + 0)
#घोषणा TLV_TYPE_CHANLIST           (PROPRIETARY_TLV_BASE_ID + 1)
#घोषणा TLV_TYPE_NUMPROBES          (PROPRIETARY_TLV_BASE_ID + 2)
#घोषणा TLV_TYPE_RSSI_LOW           (PROPRIETARY_TLV_BASE_ID + 4)
#घोषणा TLV_TYPE_SNR_LOW            (PROPRIETARY_TLV_BASE_ID + 5)
#घोषणा TLV_TYPE_FAILCOUNT          (PROPRIETARY_TLV_BASE_ID + 6)
#घोषणा TLV_TYPE_BCNMISS            (PROPRIETARY_TLV_BASE_ID + 7)
#घोषणा TLV_TYPE_LED_GPIO           (PROPRIETARY_TLV_BASE_ID + 8)
#घोषणा TLV_TYPE_LEDBEHAVIOR        (PROPRIETARY_TLV_BASE_ID + 9)
#घोषणा TLV_TYPE_PASSTHROUGH        (PROPRIETARY_TLV_BASE_ID + 10)
#घोषणा TLV_TYPE_REASSOCAP          (PROPRIETARY_TLV_BASE_ID + 11)
#घोषणा TLV_TYPE_POWER_TBL_2_4GHZ   (PROPRIETARY_TLV_BASE_ID + 12)
#घोषणा TLV_TYPE_POWER_TBL_5GHZ     (PROPRIETARY_TLV_BASE_ID + 13)
#घोषणा TLV_TYPE_BCASTPROBE	    (PROPRIETARY_TLV_BASE_ID + 14)
#घोषणा TLV_TYPE_NUMSSID_PROBE	    (PROPRIETARY_TLV_BASE_ID + 15)
#घोषणा TLV_TYPE_WMMQSTATUS   	    (PROPRIETARY_TLV_BASE_ID + 16)
#घोषणा TLV_TYPE_CRYPTO_DATA	    (PROPRIETARY_TLV_BASE_ID + 17)
#घोषणा TLV_TYPE_WILDCARDSSID	    (PROPRIETARY_TLV_BASE_ID + 18)
#घोषणा TLV_TYPE_TSFTIMESTAMP	    (PROPRIETARY_TLV_BASE_ID + 19)
#घोषणा TLV_TYPE_RSSI_HIGH          (PROPRIETARY_TLV_BASE_ID + 22)
#घोषणा TLV_TYPE_SNR_HIGH           (PROPRIETARY_TLV_BASE_ID + 23)
#घोषणा TLV_TYPE_AUTH_TYPE          (PROPRIETARY_TLV_BASE_ID + 31)
#घोषणा TLV_TYPE_MESH_ID            (PROPRIETARY_TLV_BASE_ID + 37)
#घोषणा TLV_TYPE_OLD_MESH_ID        (PROPRIETARY_TLV_BASE_ID + 291)

/* TLV related data काष्ठाures */
काष्ठा mrvl_ie_header अणु
	__le16 type;
	__le16 len;
पूर्ण __packed;

काष्ठा mrvl_ie_data अणु
	काष्ठा mrvl_ie_header header;
	u8 Data[1];
पूर्ण __packed;

काष्ठा mrvl_ie_rates_param_set अणु
	काष्ठा mrvl_ie_header header;
	u8 rates[1];
पूर्ण __packed;

काष्ठा mrvl_ie_ssid_param_set अणु
	काष्ठा mrvl_ie_header header;
	u8 ssid[1];
पूर्ण __packed;

काष्ठा mrvl_ie_wildcard_ssid_param_set अणु
	काष्ठा mrvl_ie_header header;
	u8 MaxSsidlength;
	u8 ssid[1];
पूर्ण __packed;

काष्ठा chanscanmode अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u8 reserved_2_7:6;
	u8 disablechanfilt:1;
	u8 passivescan:1;
#अन्यथा
	u8 passivescan:1;
	u8 disablechanfilt:1;
	u8 reserved_2_7:6;
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा chanscanparamset अणु
	u8 radiotype;
	u8 channumber;
	काष्ठा chanscanmode chanscanmode;
	__le16 minscanसमय;
	__le16 maxscanसमय;
पूर्ण __packed;

काष्ठा mrvl_ie_chanlist_param_set अणु
	काष्ठा mrvl_ie_header header;
	काष्ठा chanscanparamset chanscanparam[1];
पूर्ण __packed;

काष्ठा mrvl_ie_cf_param_set अणु
	काष्ठा mrvl_ie_header header;
	u8 cfpcnt;
	u8 cfpperiod;
	__le16 cfpmaxduration;
	__le16 cfpdurationreमुख्यing;
पूर्ण __packed;

काष्ठा mrvl_ie_ds_param_set अणु
	काष्ठा mrvl_ie_header header;
	u8 channel;
पूर्ण __packed;

काष्ठा mrvl_ie_rsn_param_set अणु
	काष्ठा mrvl_ie_header header;
	u8 rsnie[1];
पूर्ण __packed;

काष्ठा mrvl_ie_tsf_बारtamp अणु
	काष्ठा mrvl_ie_header header;
	__le64 tsftable[1];
पूर्ण __packed;

/* v9 and later firmware only */
काष्ठा mrvl_ie_auth_type अणु
	काष्ठा mrvl_ie_header header;
	__le16 auth;
पूर्ण __packed;

/*  Local Power capability */
काष्ठा mrvl_ie_घातer_capability अणु
	काष्ठा mrvl_ie_header header;
	s8 minघातer;
	s8 maxघातer;
पूर्ण __packed;

/* used in CMD_802_11_SUBSCRIBE_EVENT क्रम SNR, RSSI and Failure */
काष्ठा mrvl_ie_thresholds अणु
	काष्ठा mrvl_ie_header header;
	u8 value;
	u8 freq;
पूर्ण __packed;

काष्ठा mrvl_ie_beacons_missed अणु
	काष्ठा mrvl_ie_header header;
	u8 beaconmissed;
	u8 reserved;
पूर्ण __packed;

काष्ठा mrvl_ie_num_probes अणु
	काष्ठा mrvl_ie_header header;
	__le16 numprobes;
पूर्ण __packed;

काष्ठा mrvl_ie_bcast_probe अणु
	काष्ठा mrvl_ie_header header;
	__le16 bcastprobe;
पूर्ण __packed;

काष्ठा mrvl_ie_num_ssid_probe अणु
	काष्ठा mrvl_ie_header header;
	__le16 numssidprobe;
पूर्ण __packed;

काष्ठा led_pin अणु
	u8 led;
	u8 pin;
पूर्ण __packed;

काष्ठा mrvl_ie_ledgpio अणु
	काष्ठा mrvl_ie_header header;
	काष्ठा led_pin ledpin[1];
पूर्ण __packed;

काष्ठा led_bhv अणु
	uपूर्णांक8_t	firmwarestate;
	uपूर्णांक8_t	led;
	uपूर्णांक8_t	ledstate;
	uपूर्णांक8_t	ledarg;
पूर्ण __packed;


काष्ठा mrvl_ie_ledbhv अणु
	काष्ठा mrvl_ie_header header;
	काष्ठा led_bhv ledbhv[1];
पूर्ण __packed;

/*
 * Meant to be packed as the value member of a काष्ठा ieee80211_info_element.
 * Note that the len member of the ieee80211_info_element varies depending on
 * the mesh_id_len
 */
काष्ठा mrvl_meshie_val अणु
	uपूर्णांक8_t oui[3];
	uपूर्णांक8_t type;
	uपूर्णांक8_t subtype;
	uपूर्णांक8_t version;
	uपूर्णांक8_t active_protocol_id;
	uपूर्णांक8_t active_metric_id;
	uपूर्णांक8_t mesh_capability;
	uपूर्णांक8_t mesh_id_len;
	uपूर्णांक8_t mesh_id[IEEE80211_MAX_SSID_LEN];
पूर्ण __packed;

काष्ठा mrvl_meshie अणु
	u8 id, len;
	काष्ठा mrvl_meshie_val val;
पूर्ण __packed;

काष्ठा mrvl_mesh_शेषs अणु
	__le32 bootflag;
	uपूर्णांक8_t bootसमय;
	uपूर्णांक8_t reserved;
	__le16 channel;
	काष्ठा mrvl_meshie meshie;
पूर्ण __packed;

#पूर्ण_अगर
