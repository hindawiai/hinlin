<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित _WIFI_H_
#घोषणा _WIFI_H_

#घोषणा WLAN_HDR_A3_LEN		24
#घोषणा WLAN_HDR_A3_QOS_LEN	26

#घोषणा P80211CAPTURE_VERSION	0x80211001

/*  This value is tested by WiFi 11n Test Plan 5.2.3. */
/*  This test verअगरies the WLAN NIC can update the NAV through sending
 *  the CTS with large duration.
 */
#घोषणा	WiFiNavUpperUs				30000	/*  30 ms */

क्रमागत WIFI_FRAME_TYPE अणु
	WIFI_MGT_TYPE  =	(0),
	WIFI_CTRL_TYPE =	(BIT(2)),
	WIFI_DATA_TYPE =	(BIT(3)),
	WIFI_QOS_DATA_TYPE	= (BIT(7) | BIT(3)),	/*  QoS Data */
पूर्ण;

क्रमागत WIFI_FRAME_SUBTYPE अणु
	/*  below is क्रम mgt frame */
	WIFI_ASSOCREQ       = (0 | WIFI_MGT_TYPE),
	WIFI_ASSOCRSP       = (BIT(4) | WIFI_MGT_TYPE),
	WIFI_REASSOCREQ     = (BIT(5) | WIFI_MGT_TYPE),
	WIFI_REASSOCRSP     = (BIT(5) | BIT(4) | WIFI_MGT_TYPE),
	WIFI_PROBEREQ       = (BIT(6) | WIFI_MGT_TYPE),
	WIFI_PROBERSP       = (BIT(6) | BIT(4) | WIFI_MGT_TYPE),
	WIFI_BEACON         = (BIT(7) | WIFI_MGT_TYPE),
	WIFI_ATIM           = (BIT(7) | BIT(4) | WIFI_MGT_TYPE),
	WIFI_DISASSOC       = (BIT(7) | BIT(5) | WIFI_MGT_TYPE),
	WIFI_AUTH           = (BIT(7) | BIT(5) | BIT(4) | WIFI_MGT_TYPE),
	WIFI_DEAUTH         = (BIT(7) | BIT(6) | WIFI_MGT_TYPE),
	WIFI_ACTION         = (BIT(7) | BIT(6) | BIT(4) | WIFI_MGT_TYPE),

	/*  below is क्रम control frame */
	WIFI_PSPOLL         = (BIT(7) | BIT(5) | WIFI_CTRL_TYPE),
	WIFI_RTS            = (BIT(7) | BIT(5) | BIT(4) | WIFI_CTRL_TYPE),
	WIFI_CTS            = (BIT(7) | BIT(6) | WIFI_CTRL_TYPE),
	WIFI_ACK            = (BIT(7) | BIT(6) | BIT(4) | WIFI_CTRL_TYPE),
	WIFI_CFEND          = (BIT(7) | BIT(6) | BIT(5) | WIFI_CTRL_TYPE),
	WIFI_CFEND_CFACK    = (BIT(7) | BIT(6) | BIT(5) | BIT(4) |
	WIFI_CTRL_TYPE),

	/*  below is क्रम data frame */
	WIFI_DATA           = (0 | WIFI_DATA_TYPE),
	WIFI_DATA_CFACK     = (BIT(4) | WIFI_DATA_TYPE),
	WIFI_DATA_CFPOLL    = (BIT(5) | WIFI_DATA_TYPE),
	WIFI_DATA_CFACKPOLL = (BIT(5) | BIT(4) | WIFI_DATA_TYPE),
	WIFI_DATA_शून्य      = (BIT(6) | WIFI_DATA_TYPE),
	WIFI_CF_ACK         = (BIT(6) | BIT(4) | WIFI_DATA_TYPE),
	WIFI_CF_POLL        = (BIT(6) | BIT(5) | WIFI_DATA_TYPE),
	WIFI_CF_ACKPOLL     = (BIT(6) | BIT(5) | BIT(4) | WIFI_DATA_TYPE),
	WIFI_QOS_DATA_शून्य	= (BIT(6) | WIFI_QOS_DATA_TYPE),
पूर्ण;

#घोषणा SetToDs(pbuf)	\
	*(__le16 *)(pbuf) |= cpu_to_le16(IEEE80211_FCTL_TODS)

#घोषणा GetToDs(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(IEEE80211_FCTL_TODS)) != 0)

#घोषणा ClearToDs(pbuf)	\
	*(__le16 *)(pbuf) &= (~cpu_to_le16(IEEE80211_FCTL_TODS))

#घोषणा SetFrDs(pbuf)	\
	*(__le16 *)(pbuf) |= cpu_to_le16(IEEE80211_FCTL_FROMDS)

#घोषणा GetFrDs(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(IEEE80211_FCTL_FROMDS)) != 0)

#घोषणा ClearFrDs(pbuf)	\
	*(__le16 *)(pbuf) &= (~cpu_to_le16(IEEE80211_FCTL_FROMDS))

#घोषणा get_tofr_ds(pframe)	((GetToDs(pframe) << 1) | GetFrDs(pframe))

#घोषणा SetMFrag(pbuf)	\
	*(__le16 *)(pbuf) |= cpu_to_le16(IEEE80211_FCTL_MOREFRAGS)

#घोषणा GetMFrag(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(IEEE80211_FCTL_MOREFRAGS)) != 0)

#घोषणा ClearMFrag(pbuf)	\
	*(__le16 *)(pbuf) &= (~cpu_to_le16(IEEE80211_FCTL_MOREFRAGS))

#घोषणा SetRetry(pbuf)	\
	*(__le16 *)(pbuf) |= cpu_to_le16(IEEE80211_FCTL_RETRY)

#घोषणा GetRetry(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(IEEE80211_FCTL_RETRY)) != 0)

#घोषणा ClearRetry(pbuf)	\
	*(__le16 *)(pbuf) &= (~cpu_to_le16(IEEE80211_FCTL_RETRY))

#घोषणा SetPwrMgt(pbuf)	\
	*(__le16 *)(pbuf) |= cpu_to_le16(IEEE80211_FCTL_PM)

#घोषणा GetPwrMgt(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(IEEE80211_FCTL_PM)) != 0)

#घोषणा ClearPwrMgt(pbuf)	\
	*(__le16 *)(pbuf) &= (~cpu_to_le16(IEEE80211_FCTL_PM))

#घोषणा SetMData(pbuf)	\
	*(__le16 *)(pbuf) |= cpu_to_le16(IEEE80211_FCTL_MOREDATA)

#घोषणा GetMData(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(IEEE80211_FCTL_MOREDATA)) != 0)

#घोषणा ClearMData(pbuf)	\
	*(__le16 *)(pbuf) &= (~cpu_to_le16(IEEE80211_FCTL_MOREDATA))

#घोषणा SetPrivacy(pbuf)	\
	*(__le16 *)(pbuf) |= cpu_to_le16(IEEE80211_FCTL_PROTECTED)

#घोषणा GetPrivacy(pbuf)					\
	(((*(__le16 *)(pbuf)) & cpu_to_le16(IEEE80211_FCTL_PROTECTED)) != 0)

#घोषणा GetOrder(pbuf)					\
	(((*(__le16 *)(pbuf)) & cpu_to_le16(IEEE80211_FCTL_ORDER)) != 0)

#घोषणा GetFrameType(pbuf)				\
	(le16_to_cpu(*(__le16 *)(pbuf)) & (BIT(3) | BIT(2)))

#घोषणा GetFrameSubType(pbuf)	(le16_to_cpu(*(__le16 *)(pbuf)) & (BIT(7) |\
	 BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2)))

#घोषणा SetFrameSubType(pbuf, type) \
	करो अणु    \
		*(__le16 *)(pbuf) &= cpu_to_le16(~(BIT(7) | BIT(6) |	\
		 BIT(5) | BIT(4) | BIT(3) | BIT(2))); \
		*(__le16 *)(pbuf) |= cpu_to_le16(type); \
	पूर्ण जबतक (0)

#घोषणा GetSequence(pbuf)			\
	(le16_to_cpu(*(__le16 *)((माप_प्रकार)(pbuf) + 22)) >> 4)

#घोषणा GetFragNum(pbuf)			\
	(le16_to_cpu(*(__le16 *)((माप_प्रकार)(pbuf) + 22)) & 0x0f)

#घोषणा SetSeqNum(pbuf, num) \
	करो अणु    \
		*(__le16 *)((माप_प्रकार)(pbuf) + 22) = \
			((*(__le16 *)((माप_प्रकार)(pbuf) + 22)) & cpu_to_le16((अचिन्हित लघु)0x000f)) | \
			cpu_to_le16((अचिन्हित लघु)(0xfff0 & (num << 4))); \
	पूर्ण जबतक (0)

#घोषणा SetDuration(pbuf, dur) \
	*(__le16 *)((माप_प्रकार)(pbuf) + 2) = cpu_to_le16(0xffff & (dur))

#घोषणा SetPriority(pbuf, tid)	\
	*(__le16 *)(pbuf) |= cpu_to_le16(tid & 0xf)

#घोषणा GetPriority(pbuf)	((le16_to_cpu(*(__le16 *)(pbuf))) & 0xf)

#घोषणा SetEOSP(pbuf, eosp)	\
		*(__le16 *)(pbuf) |= cpu_to_le16((eosp & 1) << 4)

#घोषणा SetAckpolicy(pbuf, ack)	\
	*(__le16 *)(pbuf) |= cpu_to_le16((ack & 3) << 5)

#घोषणा GetAckpolicy(pbuf) (((le16_to_cpu(*(__le16 *)pbuf)) >> 5) & 0x3)

#घोषणा GetAMsdu(pbuf) (((le16_to_cpu(*(__le16 *)pbuf)) >> 7) & 0x1)

#घोषणा GetAid(pbuf)	(le16_to_cpu(*(__le16 *)((माप_प्रकार)(pbuf) + 2)) & 0x3fff)

#घोषणा GetAddr1Ptr(pbuf)	((अचिन्हित अक्षर *)((माप_प्रकार)(pbuf) + 4))

#घोषणा GetAddr2Ptr(pbuf)	((अचिन्हित अक्षर *)((माप_प्रकार)(pbuf) + 10))

#घोषणा GetAddr3Ptr(pbuf)	((अचिन्हित अक्षर *)((माप_प्रकार)(pbuf) + 16))

अटल अंतरभूत अचिन्हित अक्षर *get_hdr_bssid(अचिन्हित अक्षर *pframe)
अणु
	अचिन्हित अक्षर	*sa;
	अचिन्हित पूर्णांक	to_fr_ds = (GetToDs(pframe) << 1) | GetFrDs(pframe);

	चयन (to_fr_ds) अणु
	हाल 0x00:	/*  ToDs=0, FromDs=0 */
		sa = GetAddr3Ptr(pframe);
		अवरोध;
	हाल 0x01:	/*  ToDs=0, FromDs=1 */
		sa = GetAddr2Ptr(pframe);
		अवरोध;
	हाल 0x02:	/*  ToDs=1, FromDs=0 */
		sa = GetAddr1Ptr(pframe);
		अवरोध;
	हाल 0x03:	/*  ToDs=1, FromDs=1 */
		sa = GetAddr1Ptr(pframe);
		अवरोध;
	शेष:
		sa = शून्य; /*  */
		अवरोध;
	पूर्ण
	वापस sa;
पूर्ण

/*-----------------------------------------------------------------------------
			Below is क्रम the security related definition
------------------------------------------------------------------------------*/
#घोषणा _ASOCREQ_IE_OFFSET_	4	/*  excluding wlan_hdr */
#घोषणा	_ASOCRSP_IE_OFFSET_	6
#घोषणा _REASOCREQ_IE_OFFSET_	10
#घोषणा _REASOCRSP_IE_OFFSET_	6
#घोषणा _PROBEREQ_IE_OFFSET_	0
#घोषणा	_PROBERSP_IE_OFFSET_	12
#घोषणा _AUTH_IE_OFFSET_	6
#घोषणा _DEAUTH_IE_OFFSET_	0
#घोषणा _BEACON_IE_OFFSET_	12
#घोषणा _PUBLIC_ACTION_IE_OFFSET_	8

#घोषणा _FIXED_IE_LENGTH_	_BEACON_IE_OFFSET_

/* ---------------------------------------------------------------------------
					Below is the fixed elements...
-----------------------------------------------------------------------------*/
#घोषणा _AUTH_ALGM_NUM_		2
#घोषणा _AUTH_SEQ_NUM_		2
#घोषणा _BEACON_ITERVAL_	2
#घोषणा _CAPABILITY_		2
#घोषणा _CURRENT_APADDR_	6
#घोषणा _LISTEN_INTERVAL_	2
#घोषणा _RSON_CODE_		2
#घोषणा _ASOC_ID_		2
#घोषणा _STATUS_CODE_		2
#घोषणा _TIMESTAMP_		8

#घोषणा AUTH_ODD_TO		0
#घोषणा AUTH_EVEN_TO		1

/*-----------------------------------------------------------------------------
				Below is the definition क्रम 802.11i / 802.1x
------------------------------------------------------------------------------*/
#घोषणा _IEEE8021X_MGT_			1	/*  WPA */
#घोषणा _IEEE8021X_PSK_			2	/*  WPA with pre-shared key */

/*
 * #घोषणा _NO_PRIVACY_			0
 * #घोषणा _WEP_40_PRIVACY_		1
 * #घोषणा _TKIP_PRIVACY_		2
 * #घोषणा _WRAP_PRIVACY_		3
 * #घोषणा _CCMP_PRIVACY_		4
 * #घोषणा _WEP_104_PRIVACY_		5
 * #घोषणा _WEP_WPA_MIXED_PRIVACY_ 6	WEP + WPA
 */

/*-----------------------------------------------------------------------------
				Below is the definition क्रम WMM
------------------------------------------------------------------------------*/
#घोषणा _WMM_IE_Length_				7  /*  क्रम WMM STA */

/*-----------------------------------------------------------------------------
				Below is the definition क्रम 802.11n
------------------------------------------------------------------------------*/

/**
 * काष्ठा rtw_ieee80211_ht_cap - HT additional inक्रमmation
 *
 * This काष्ठाure refers to "HT information element" as
 * described in 802.11n draft section 7.3.2.53
 */
काष्ठा ieee80211_ht_addt_info अणु
	अचिन्हित अक्षर	control_chan;
	अचिन्हित अक्षर	ht_param;
	अचिन्हित लघु	operation_mode;
	अचिन्हित लघु	stbc_param;
	अचिन्हित अक्षर	basic_set[16];
पूर्ण __packed;

काष्ठा HT_info_element अणु
	अचिन्हित अक्षर	primary_channel;
	अचिन्हित अक्षर	infos[5];
	अचिन्हित अक्षर	MCS_rate[16];
पूर्ण __packed;

काष्ठा AC_param अणु
	अचिन्हित अक्षर		ACI_AIFSN;
	अचिन्हित अक्षर		CW;
	__le16	TXOP_limit;
पूर्ण __packed;

काष्ठा WMM_para_element अणु
	अचिन्हित अक्षर		QoS_info;
	अचिन्हित अक्षर		reserved;
	काष्ठा AC_param	ac_param[4];
पूर्ण __packed;

काष्ठा ADDBA_request अणु
	अचिन्हित अक्षर	dialog_token;
	__le16		BA_para_set;
	अचिन्हित लघु	BA_समयout_value;
	अचिन्हित लघु	BA_starting_seqctrl;
पूर्ण __packed;

क्रमागत ht_cap_ampdu_factor अणु
	MAX_AMPDU_FACTOR_8K	= 0,
	MAX_AMPDU_FACTOR_16K	= 1,
	MAX_AMPDU_FACTOR_32K	= 2,
	MAX_AMPDU_FACTOR_64K	= 3,
पूर्ण;

#घोषणा OP_MODE_PURE                    0
#घोषणा OP_MODE_MAY_BE_LEGACY_STAS      1
#घोषणा OP_MODE_20MHZ_HT_STA_ASSOCED    2
#घोषणा OP_MODE_MIXED                   3

#घोषणा HT_INFO_HT_PARAM_SECONDARY_CHNL_OFF_MASK	((u8)BIT(0) | BIT(1))
#घोषणा HT_INFO_HT_PARAM_SECONDARY_CHNL_ABOVE		((u8)BIT(0))
#घोषणा HT_INFO_HT_PARAM_SECONDARY_CHNL_BELOW		((u8)BIT(0) | BIT(1))
#घोषणा HT_INFO_HT_PARAM_REC_TRANS_CHNL_WIDTH		((u8)BIT(2))
#घोषणा HT_INFO_HT_PARAM_RIFS_MODE			((u8)BIT(3))
#घोषणा HT_INFO_HT_PARAM_CTRL_ACCESS_ONLY		((u8)BIT(4))
#घोषणा HT_INFO_HT_PARAM_SRV_INTERVAL_GRANULARITY	((u8)BIT(5))

#घोषणा HT_INFO_OPERATION_MODE_OP_MODE_MASK	\
		((u16)(0x0001 | 0x0002))
#घोषणा HT_INFO_OPERATION_MODE_OP_MODE_OFFSET		0
#घोषणा HT_INFO_OPERATION_MODE_NON_GF_DEVS_PRESENT	((u8)BIT(2))
#घोषणा HT_INFO_OPERATION_MODE_TRANSMIT_BURST_LIMIT	((u8)BIT(3))
#घोषणा HT_INFO_OPERATION_MODE_NON_HT_STA_PRESENT	((u8)BIT(4))

/*	===============WPS Section=============== */
/*	For WPSv1.0 */
#घोषणा WPSOUI					0x0050f204
/*	WPS attribute ID */
#घोषणा WPS_ATTR_VER1				0x104A
#घोषणा WPS_ATTR_SIMPLE_CONF_STATE		0x1044
#घोषणा WPS_ATTR_RESP_TYPE			0x103B
#घोषणा WPS_ATTR_UUID_E				0x1047
#घोषणा WPS_ATTR_MANUFACTURER			0x1021
#घोषणा WPS_ATTR_MODEL_NAME			0x1023
#घोषणा WPS_ATTR_MODEL_NUMBER			0x1024
#घोषणा WPS_ATTR_SERIAL_NUMBER			0x1042
#घोषणा WPS_ATTR_PRIMARY_DEV_TYPE		0x1054
#घोषणा WPS_ATTR_SEC_DEV_TYPE_LIST		0x1055
#घोषणा WPS_ATTR_DEVICE_NAME			0x1011
#घोषणा WPS_ATTR_CONF_METHOD			0x1008
#घोषणा WPS_ATTR_RF_BANDS			0x103C
#घोषणा WPS_ATTR_DEVICE_PWID			0x1012
#घोषणा WPS_ATTR_REQUEST_TYPE			0x103A
#घोषणा WPS_ATTR_ASSOCIATION_STATE		0x1002
#घोषणा WPS_ATTR_CONFIG_ERROR			0x1009
#घोषणा WPS_ATTR_VENDOR_EXT			0x1049
#घोषणा WPS_ATTR_SELECTED_REGISTRAR		0x1041

/*	Value of WPS Request Type Attribute */
#घोषणा WPS_REQ_TYPE_ENROLLEE_INFO_ONLY		0x00
#घोषणा WPS_REQ_TYPE_ENROLLEE_OPEN_8021X	0x01
#घोषणा WPS_REQ_TYPE_REGISTRAR			0x02
#घोषणा WPS_REQ_TYPE_WLAN_MANAGER_REGISTRAR	0x03

/*	Value of WPS Response Type Attribute */
#घोषणा WPS_RESPONSE_TYPE_INFO_ONLY	0x00
#घोषणा WPS_RESPONSE_TYPE_8021X		0x01
#घोषणा WPS_RESPONSE_TYPE_REGISTRAR	0x02
#घोषणा WPS_RESPONSE_TYPE_AP		0x03

/*	Value of WPS WiFi Simple Configuration State Attribute */
#घोषणा WPS_WSC_STATE_NOT_CONFIG	0x01
#घोषणा WPS_WSC_STATE_CONFIG		0x02

/*	Value of WPS Version Attribute */
#घोषणा WPS_VERSION_1			0x10

/*	Value of WPS Configuration Method Attribute */
#घोषणा WPS_CONFIG_METHOD_FLASH		0x0001
#घोषणा WPS_CONFIG_METHOD_ETHERNET	0x0002
#घोषणा WPS_CONFIG_METHOD_LABEL		0x0004
#घोषणा WPS_CONFIG_METHOD_DISPLAY	0x0008
#घोषणा WPS_CONFIG_METHOD_E_NFC		0x0010
#घोषणा WPS_CONFIG_METHOD_I_NFC		0x0020
#घोषणा WPS_CONFIG_METHOD_NFC		0x0040
#घोषणा WPS_CONFIG_METHOD_PBC		0x0080
#घोषणा WPS_CONFIG_METHOD_KEYPAD	0x0100
#घोषणा WPS_CONFIG_METHOD_VPBC		0x0280
#घोषणा WPS_CONFIG_METHOD_PPBC		0x0480
#घोषणा WPS_CONFIG_METHOD_VDISPLAY	0x2008
#घोषणा WPS_CONFIG_METHOD_PDISPLAY	0x4008

/*	Value of WPS RF Bands Attribute */
#घोषणा WPS_RF_BANDS_2_4_GHZ		0x01
#घोषणा WPS_RF_BANDS_5_GHZ		0x02

#घोषणा IP_MCAST_MAC(mac)				\
	((mac[0] == 0x01) && (mac[1] == 0x00) && (mac[2] == 0x5e))
#घोषणा ICMPV6_MCAST_MAC(mac)				\
	((mac[0] == 0x33) && (mac[1] == 0x33) && (mac[2] != 0xff))

#पूर्ण_अगर /*  _WIFI_H_ */
