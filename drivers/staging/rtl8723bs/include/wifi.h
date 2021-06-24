<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित _WIFI_H_
#घोषणा _WIFI_H_


#अगर_घोषित BIT
/* error	"BIT define occurred earlier elsewhere!\n" */
#अघोषित BIT
#पूर्ण_अगर
#घोषणा BIT(x)	(1 << (x))


#घोषणा WLAN_ETHHDR_LEN		14
#घोषणा WLAN_ETHADDR_LEN	6
#घोषणा WLAN_IEEE_OUI_LEN	3
#घोषणा WLAN_ADDR_LEN		6
#घोषणा WLAN_CRC_LEN		4
#घोषणा WLAN_BSSID_LEN		6
#घोषणा WLAN_BSS_TS_LEN		8
#घोषणा WLAN_HDR_A3_LEN		24
#घोषणा WLAN_HDR_A4_LEN		30
#घोषणा WLAN_HDR_A3_QOS_LEN	26
#घोषणा WLAN_HDR_A4_QOS_LEN	32
#घोषणा WLAN_SSID_MAXLEN	32
#घोषणा WLAN_DATA_MAXLEN	2312

#घोषणा WLAN_A3_PN_OFFSET	24
#घोषणा WLAN_A4_PN_OFFSET	30

#घोषणा WLAN_MIN_ETHFRM_LEN	60
#घोषणा WLAN_MAX_ETHFRM_LEN	1514
#घोषणा WLAN_ETHHDR_LEN		14
#घोषणा WLAN_WMM_LEN		24

#घोषणा P80211CAPTURE_VERSION	0x80211001

/*  This value is tested by WiFi 11n Test Plan 5.2.3. */
/*  This test verअगरies the WLAN NIC can update the NAV through sending the CTS with large duration. */
#घोषणा	WiFiNavUpperUs				30000	/*  30 ms */

क्रमागत अणु
	WIFI_MGT_TYPE  =	(0),
	WIFI_CTRL_TYPE =	(BIT(2)),
	WIFI_DATA_TYPE =	(BIT(3)),
	WIFI_QOS_DATA_TYPE	= (BIT(7)|BIT(3)),	/*  QoS Data */
पूर्ण;

क्रमागत अणु

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
    WIFI_ACTION_NOACK = (BIT(7) | BIT(6) | BIT(5) | WIFI_MGT_TYPE),

    /*  below is क्रम control frame */
    WIFI_NDPA         = (BIT(6) | BIT(4) | WIFI_CTRL_TYPE),
    WIFI_PSPOLL         = (BIT(7) | BIT(5) | WIFI_CTRL_TYPE),
    WIFI_RTS            = (BIT(7) | BIT(5) | BIT(4) | WIFI_CTRL_TYPE),
    WIFI_CTS            = (BIT(7) | BIT(6) | WIFI_CTRL_TYPE),
    WIFI_ACK            = (BIT(7) | BIT(6) | BIT(4) | WIFI_CTRL_TYPE),
    WIFI_CFEND          = (BIT(7) | BIT(6) | BIT(5) | WIFI_CTRL_TYPE),
    WIFI_CFEND_CFACK    = (BIT(7) | BIT(6) | BIT(5) | BIT(4) | WIFI_CTRL_TYPE),

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

#घोषणा _TO_DS_		BIT(8)
#घोषणा _FROM_DS_	BIT(9)
#घोषणा _MORE_FRAG_	BIT(10)
#घोषणा _RETRY_		BIT(11)
#घोषणा _PWRMGT_	BIT(12)
#घोषणा _MORE_DATA_	BIT(13)
#घोषणा _PRIVACY_	BIT(14)
#घोषणा _ORDER_			BIT(15)

#घोषणा SetToDs(pbuf)	\
	(*(__le16 *)(pbuf) |= cpu_to_le16(_TO_DS_))

#घोषणा GetToDs(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(_TO_DS_)) != 0)

#घोषणा SetFrDs(pbuf)	\
	(*(__le16 *)(pbuf) |= cpu_to_le16(_FROM_DS_))

#घोषणा GetFrDs(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(_FROM_DS_)) != 0)

#घोषणा get_tofr_ds(pframe)	((GetToDs(pframe) << 1) | GetFrDs(pframe))

#घोषणा SetMFrag(pbuf)	\
	(*(__le16 *)(pbuf) |= cpu_to_le16(_MORE_FRAG_))

#घोषणा GetMFrag(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(_MORE_FRAG_)) != 0)

#घोषणा ClearMFrag(pbuf)	\
	(*(__le16 *)(pbuf) &= (~cpu_to_le16(_MORE_FRAG_)))

#घोषणा GetRetry(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(_RETRY_)) != 0)

#घोषणा ClearRetry(pbuf)	\
	(*(__le16 *)(pbuf) &= (~cpu_to_le16(_RETRY_)))

#घोषणा SetPwrMgt(pbuf)	\
	(*(__le16 *)(pbuf) |= cpu_to_le16(_PWRMGT_))

#घोषणा GetPwrMgt(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(_PWRMGT_)) != 0)

#घोषणा ClearPwrMgt(pbuf)	\
	(*(__le16 *)(pbuf) &= (~cpu_to_le16(_PWRMGT_)))

#घोषणा SetMData(pbuf)	\
	(*(__le16 *)(pbuf) |= cpu_to_le16(_MORE_DATA_))

#घोषणा GetMData(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(_MORE_DATA_)) != 0)

#घोषणा ClearMData(pbuf)	\
	(*(__le16 *)(pbuf) &= (~cpu_to_le16(_MORE_DATA_)))

#घोषणा SetPrivacy(pbuf)	\
	(*(__le16 *)(pbuf) |= cpu_to_le16(_PRIVACY_))

#घोषणा GetPrivacy(pbuf)					\
	(((*(__le16 *)(pbuf)) & cpu_to_le16(_PRIVACY_)) != 0)

#घोषणा GetOrder(pbuf)					\
	(((*(__le16 *)(pbuf)) & cpu_to_le16(_ORDER_)) != 0)

#घोषणा GetFrameType(pbuf)				\
	(le16_to_cpu(*(__le16 *)(pbuf)) & (BIT(3) | BIT(2)))

#घोषणा SetFrameType(pbuf, type)	\
	करो अणु	\
		*(अचिन्हित लघु *)(pbuf) &= cpu_to_le16(~(BIT(3) | BIT(2))); \
		*(अचिन्हित लघु *)(pbuf) |= cpu_to_le16(type); \
	पूर्ण जबतक (0)

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

#घोषणा GetTupleCache(pbuf)			\
	(cpu_to_le16(*(अचिन्हित लघु *)((माप_प्रकार)(pbuf) + 22)))

#घोषणा SetFragNum(pbuf, num) \
	करो अणु    \
		*(अचिन्हित लघु *)((माप_प्रकार)(pbuf) + 22) = \
			((*(अचिन्हित लघु *)((माप_प्रकार)(pbuf) + 22)) &	\
			le16_to_cpu(~(0x000f))) | \
			cpu_to_le16(0x0f & (num));     \
	पूर्ण जबतक (0)

#घोषणा SetSeqNum(pbuf, num) \
	करो अणु    \
		*(__le16 *)((माप_प्रकार)(pbuf) + 22) = \
			((*(__le16 *)((माप_प्रकार)(pbuf) + 22)) & cpu_to_le16((अचिन्हित लघु)0x000f)) | \
			cpu_to_le16((अचिन्हित लघु)(0xfff0 & (num << 4))); \
	पूर्ण जबतक (0)

#घोषणा SetDuration(pbuf, dur) \
	(*(__le16 *)((माप_प्रकार)(pbuf) + 2) = cpu_to_le16(0xffff & (dur)))


#घोषणा SetPriority(pbuf, tid)	\
	(*(__le16 *)(pbuf) |= cpu_to_le16(tid & 0xf))

#घोषणा GetPriority(pbuf)	((le16_to_cpu(*(__le16 *)(pbuf))) & 0xf)

#घोषणा SetEOSP(pbuf, eosp)	\
		(*(__le16 *)(pbuf) |= cpu_to_le16((eosp & 1) << 4))

#घोषणा SetAckpolicy(pbuf, ack)	\
	(*(__le16 *)(pbuf) |= cpu_to_le16((ack & 3) << 5))

#घोषणा GetAckpolicy(pbuf) (((le16_to_cpu(*(__le16 *)pbuf)) >> 5) & 0x3)

#घोषणा GetAMsdu(pbuf) (((le16_to_cpu(*(__le16 *)pbuf)) >> 7) & 0x1)

#घोषणा GetAid(pbuf)	(le16_to_cpu(*(__le16 *)((माप_प्रकार)(pbuf) + 2)) & 0x3fff)

#घोषणा GetAddr1Ptr(pbuf)	((अचिन्हित अक्षर *)((माप_प्रकार)(pbuf) + 4))

#घोषणा GetAddr2Ptr(pbuf)	((अचिन्हित अक्षर *)((माप_प्रकार)(pbuf) + 10))

#घोषणा GetAddr3Ptr(pbuf)	((अचिन्हित अक्षर *)((माप_प्रकार)(pbuf) + 16))

#घोषणा GetAddr4Ptr(pbuf)	((अचिन्हित अक्षर *)((माप_प्रकार)(pbuf) + 24))

#घोषणा MacAddr_isBcst(addr) \
	(\
	((addr[0] == 0xff) && (addr[1] == 0xff) && \
	(addr[2] == 0xff) && (addr[3] == 0xff) && \
	(addr[4] == 0xff) && (addr[5] == 0xff))  ? true : false \
)

अटल अंतरभूत पूर्णांक IS_MCAST(अचिन्हित अक्षर *da)
अणु
	अगर ((*da) & 0x01)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *get_ra(अचिन्हित अक्षर *pframe)
अणु
	अचिन्हित अक्षर *ra;
	ra = GetAddr1Ptr(pframe);
	वापस ra;
पूर्ण
अटल अंतरभूत अचिन्हित अक्षर *get_ta(अचिन्हित अक्षर *pframe)
अणु
	अचिन्हित अक्षर *ta;
	ta = GetAddr2Ptr(pframe);
	वापस ta;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *get_da(अचिन्हित अक्षर *pframe)
अणु
	अचिन्हित अक्षर *da;
	अचिन्हित पूर्णांक	to_fr_ds	= (GetToDs(pframe) << 1) | GetFrDs(pframe);

	चयन (to_fr_ds) अणु
	हाल 0x00:	/*  ToDs = 0, FromDs = 0 */
		da = GetAddr1Ptr(pframe);
		अवरोध;
	हाल 0x01:	/*  ToDs = 0, FromDs = 1 */
		da = GetAddr1Ptr(pframe);
		अवरोध;
	हाल 0x02:	/*  ToDs = 1, FromDs = 0 */
		da = GetAddr3Ptr(pframe);
		अवरोध;
	शेष:	/*  ToDs = 1, FromDs = 1 */
		da = GetAddr3Ptr(pframe);
		अवरोध;
	पूर्ण

	वापस da;
पूर्ण


अटल अंतरभूत अचिन्हित अक्षर *get_sa(अचिन्हित अक्षर *pframe)
अणु
	अचिन्हित अक्षर *sa;
	अचिन्हित पूर्णांक	to_fr_ds	= (GetToDs(pframe) << 1) | GetFrDs(pframe);

	चयन (to_fr_ds) अणु
	हाल 0x00:	/*  ToDs = 0, FromDs = 0 */
		sa = GetAddr2Ptr(pframe);
		अवरोध;
	हाल 0x01:	/*  ToDs = 0, FromDs = 1 */
		sa = GetAddr3Ptr(pframe);
		अवरोध;
	हाल 0x02:	/*  ToDs = 1, FromDs = 0 */
		sa = GetAddr2Ptr(pframe);
		अवरोध;
	शेष:	/*  ToDs = 1, FromDs = 1 */
		sa = GetAddr4Ptr(pframe);
		अवरोध;
	पूर्ण

	वापस sa;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *get_hdr_bssid(अचिन्हित अक्षर *pframe)
अणु
	अचिन्हित अक्षर *sa = शून्य;
	अचिन्हित पूर्णांक	to_fr_ds	= (GetToDs(pframe) << 1) | GetFrDs(pframe);

	चयन (to_fr_ds) अणु
	हाल 0x00:	/*  ToDs = 0, FromDs = 0 */
		sa = GetAddr3Ptr(pframe);
		अवरोध;
	हाल 0x01:	/*  ToDs = 0, FromDs = 1 */
		sa = GetAddr2Ptr(pframe);
		अवरोध;
	हाल 0x02:	/*  ToDs = 1, FromDs = 0 */
		sa = GetAddr1Ptr(pframe);
		अवरोध;
	हाल 0x03:	/*  ToDs = 1, FromDs = 1 */
		sa = GetAddr1Ptr(pframe);
		अवरोध;
	पूर्ण

	वापस sa;
पूर्ण


अटल अंतरभूत पूर्णांक IsFrameTypeCtrl(अचिन्हित अक्षर *pframe)
अणु
	अगर (WIFI_CTRL_TYPE == GetFrameType(pframe))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण
/*-----------------------------------------------------------------------------
			Below is क्रम the security related definition
------------------------------------------------------------------------------*/
#घोषणा _RESERVED_FRAME_TYPE_	0
#घोषणा _SKB_FRAME_TYPE_		2
#घोषणा _PRE_ALLOCMEM_			1
#घोषणा _PRE_ALLOCHDR_			3
#घोषणा _PRE_ALLOCLLCHDR_		4
#घोषणा _PRE_ALLOCICVHDR_		5
#घोषणा _PRE_ALLOCMICHDR_		6

#घोषणा _SIFSTIME_				((priv->pmib->करोt11BssType.net_work_type&WIRELESS_11A)?16:10)
#घोषणा _ACKCTSLNG_				14	/* 14 bytes दीर्घ, including crclng */
#घोषणा _CRCLNG_				4

#घोषणा _ASOCREQ_IE_OFFSET_		4	/*  excluding wlan_hdr */
#घोषणा	_ASOCRSP_IE_OFFSET_		6
#घोषणा _REASOCREQ_IE_OFFSET_	10
#घोषणा _REASOCRSP_IE_OFFSET_	6
#घोषणा _PROBEREQ_IE_OFFSET_	0
#घोषणा	_PROBERSP_IE_OFFSET_	12
#घोषणा _AUTH_IE_OFFSET_		6
#घोषणा _DEAUTH_IE_OFFSET_		0
#घोषणा _BEACON_IE_OFFSET_		12
#घोषणा _PUBLIC_ACTION_IE_OFFSET_	8

#घोषणा _FIXED_IE_LENGTH_			_BEACON_IE_OFFSET_

/* ---------------------------------------------------------------------------
					Below is the fixed elements...
-----------------------------------------------------------------------------*/
#घोषणा _AUTH_ALGM_NUM_			2
#घोषणा _AUTH_SEQ_NUM_			2
#घोषणा _BEACON_ITERVAL_		2
#घोषणा _CAPABILITY_			2
#घोषणा _CURRENT_APADDR_		6
#घोषणा _LISTEN_INTERVAL_		2
#घोषणा _RSON_CODE_				2
#घोषणा _ASOC_ID_				2
#घोषणा _STATUS_CODE_			2
#घोषणा _TIMESTAMP_				8

#घोषणा AUTH_ODD_TO				0
#घोषणा AUTH_EVEN_TO			1

#घोषणा WLAN_ETHCONV_ENCAP		1
#घोषणा WLAN_ETHCONV_RFC1042	2
#घोषणा WLAN_ETHCONV_8021h		3

/*-----------------------------------------------------------------------------
				Below is the definition क्रम 802.11i / 802.1x
------------------------------------------------------------------------------*/
#घोषणा _IEEE8021X_MGT_			1		/*  WPA */
#घोषणा _IEEE8021X_PSK_			2		/*  WPA with pre-shared key */

#घोषणा _MME_IE_LENGTH_  18
/*-----------------------------------------------------------------------------
				Below is the definition क्रम WMM
------------------------------------------------------------------------------*/
#घोषणा _WMM_IE_Length_				7  /*  क्रम WMM STA */
#घोषणा _WMM_Para_Element_Length_		24


/*-----------------------------------------------------------------------------
				Below is the definition क्रम 802.11n
------------------------------------------------------------------------------*/

#घोषणा SetOrderBit(pbuf)	\
	करो	अणु	\
		*(अचिन्हित लघु *)(pbuf) |= cpu_to_le16(_ORDER_); \
	पूर्ण जबतक (0)

#घोषणा GetOrderBit(pbuf)	(((*(अचिन्हित लघु *)(pbuf)) & cpu_to_le16(_ORDER_)) != 0)

#घोषणा ACT_CAT_VENDOR				0x7F/* 127 */

/**
 * काष्ठा rtw_ieee80211_ht_cap - HT additional inक्रमmation
 *
 * This काष्ठाure refers to "HT information element" as
 * described in 802.11n draft section 7.3.2.53
 */
काष्ठा ieee80211_ht_addt_info अणु
	अचिन्हित अक्षर control_chan;
	अचिन्हित अक्षर 	ht_param;
	__le16	operation_mode;
	__le16	stbc_param;
	अचिन्हित अक्षर 	basic_set[16];
पूर्ण __attribute__ ((packed));


काष्ठा HT_caps_element अणु
	जोड़ अणु
		काष्ठा अणु
			__le16	HT_caps_info;
			अचिन्हित अक्षर AMPDU_para;
			अचिन्हित अक्षर MCS_rate[16];
			__le16	HT_ext_caps;
			__le16	Beamक्रमming_caps;
			अचिन्हित अक्षर ASEL_caps;
		पूर्ण HT_cap_element;
		अचिन्हित अक्षर HT_cap[26];
	पूर्ण u;
पूर्ण __attribute__ ((packed));

काष्ठा HT_info_element अणु
	अचिन्हित अक्षर primary_channel;
	अचिन्हित अक्षर infos[5];
	अचिन्हित अक्षर MCS_rate[16];
पूर्ण  __attribute__ ((packed));

काष्ठा AC_param अणु
	अचिन्हित अक्षर 	ACI_AIFSN;
	अचिन्हित अक्षर 	CW;
	__le16	TXOP_limit;
पूर्ण  __attribute__ ((packed));

काष्ठा WMM_para_element अणु
	अचिन्हित अक्षर 	QoS_info;
	अचिन्हित अक्षर 	reserved;
	काष्ठा AC_param	ac_param[4];
पूर्ण  __attribute__ ((packed));

काष्ठा ADDBA_request अणु
	अचिन्हित अक्षर 	dialog_token;
	__le16	BA_para_set;
	__le16	BA_समयout_value;
	__le16	BA_starting_seqctrl;
पूर्ण  __attribute__ ((packed));

/* 802.11n HT capabilities masks */
#घोषणा IEEE80211_HT_CAP_LDPC_CODING		0x0001
#घोषणा IEEE80211_HT_CAP_SUP_WIDTH		0x0002
#घोषणा IEEE80211_HT_CAP_SM_PS			0x000C
#घोषणा IEEE80211_HT_CAP_GRN_FLD		0x0010
#घोषणा IEEE80211_HT_CAP_SGI_20			0x0020
#घोषणा IEEE80211_HT_CAP_SGI_40			0x0040
#घोषणा IEEE80211_HT_CAP_TX_STBC			0x0080
#घोषणा IEEE80211_HT_CAP_RX_STBC_1R		0x0100
#घोषणा IEEE80211_HT_CAP_RX_STBC_2R		0x0200
#घोषणा IEEE80211_HT_CAP_RX_STBC_3R		0x0300
#घोषणा IEEE80211_HT_CAP_DELAY_BA		0x0400
#घोषणा IEEE80211_HT_CAP_MAX_AMSDU		0x0800
#घोषणा IEEE80211_HT_CAP_DSSSCCK40		0x1000
/* 802.11n HT capability AMPDU settings */
#घोषणा IEEE80211_HT_CAP_AMPDU_FACTOR		0x03
#घोषणा IEEE80211_HT_CAP_AMPDU_DENSITY		0x1C
/* 802.11n HT capability MSC set */
#घोषणा IEEE80211_SUPP_MCS_SET_UEQM		4
#घोषणा IEEE80211_HT_CAP_MAX_STREAMS		4
#घोषणा IEEE80211_SUPP_MCS_SET_LEN		10
/* maximum streams the spec allows */
#घोषणा IEEE80211_HT_CAP_MCS_TX_DEFINED		0x01
#घोषणा IEEE80211_HT_CAP_MCS_TX_RX_DIFF		0x02
#घोषणा IEEE80211_HT_CAP_MCS_TX_STREAMS		0x0C
#घोषणा IEEE80211_HT_CAP_MCS_TX_UEQM		0x10
/* 802.11n HT capability TXBF capability */
#घोषणा IEEE80211_HT_CAP_TXBF_RX_NDP		0x00000008
#घोषणा IEEE80211_HT_CAP_TXBF_TX_NDP		0x00000010
#घोषणा IEEE80211_HT_CAP_TXBF_EXPLICIT_COMP_STEERING_CAP	0x00000400

/* endअगर */

/* 	===============WPS Section =============== */
/* 	For WPSv1.0 */
#घोषणा WPSOUI							0x0050f204
/* 	WPS attribute ID */
#घोषणा WPS_ATTR_VER1					0x104A
#घोषणा WPS_ATTR_SIMPLE_CONF_STATE	0x1044
#घोषणा WPS_ATTR_RESP_TYPE			0x103B
#घोषणा WPS_ATTR_UUID_E				0x1047
#घोषणा WPS_ATTR_MANUFACTURER		0x1021
#घोषणा WPS_ATTR_MODEL_NAME			0x1023
#घोषणा WPS_ATTR_MODEL_NUMBER		0x1024
#घोषणा WPS_ATTR_SERIAL_NUMBER		0x1042
#घोषणा WPS_ATTR_PRIMARY_DEV_TYPE	0x1054
#घोषणा WPS_ATTR_SEC_DEV_TYPE_LIST	0x1055
#घोषणा WPS_ATTR_DEVICE_NAME			0x1011
#घोषणा WPS_ATTR_CONF_METHOD			0x1008
#घोषणा WPS_ATTR_RF_BANDS				0x103C
#घोषणा WPS_ATTR_DEVICE_PWID			0x1012
#घोषणा WPS_ATTR_REQUEST_TYPE			0x103A
#घोषणा WPS_ATTR_ASSOCIATION_STATE	0x1002
#घोषणा WPS_ATTR_CONFIG_ERROR			0x1009
#घोषणा WPS_ATTR_VENDOR_EXT			0x1049
#घोषणा WPS_ATTR_SELECTED_REGISTRAR	0x1041

/* 	Value of WPS attribute "WPS_ATTR_DEVICE_NAME */
#घोषणा WPS_MAX_DEVICE_NAME_LEN		32

/* 	Value of WPS Request Type Attribute */
#घोषणा WPS_REQ_TYPE_ENROLLEE_INFO_ONLY			0x00
#घोषणा WPS_REQ_TYPE_ENROLLEE_OPEN_8021X		0x01
#घोषणा WPS_REQ_TYPE_REGISTRAR					0x02
#घोषणा WPS_REQ_TYPE_WLAN_MANAGER_REGISTRAR	0x03

/* 	Value of WPS Response Type Attribute */
#घोषणा WPS_RESPONSE_TYPE_INFO_ONLY	0x00
#घोषणा WPS_RESPONSE_TYPE_8021X		0x01
#घोषणा WPS_RESPONSE_TYPE_REGISTRAR	0x02
#घोषणा WPS_RESPONSE_TYPE_AP			0x03

/* 	Value of WPS WiFi Simple Configuration State Attribute */
#घोषणा WPS_WSC_STATE_NOT_CONFIG	0x01
#घोषणा WPS_WSC_STATE_CONFIG			0x02

/* 	Value of WPS Version Attribute */
#घोषणा WPS_VERSION_1					0x10

/* 	Value of WPS Configuration Method Attribute */
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

/* 	Value of Category ID of WPS Primary Device Type Attribute */
#घोषणा WPS_PDT_CID_DISPLAYS			0x0007
#घोषणा WPS_PDT_CID_MULIT_MEDIA		0x0008
#घोषणा WPS_PDT_CID_RTK_WIDI			WPS_PDT_CID_MULIT_MEDIA

/* 	Value of Sub Category ID of WPS Primary Device Type Attribute */
#घोषणा WPS_PDT_SCID_MEDIA_SERVER	0x0005
#घोषणा WPS_PDT_SCID_RTK_DMP			WPS_PDT_SCID_MEDIA_SERVER

/* 	Value of Device Password ID */
#घोषणा WPS_DPID_PIN					0x0000
#घोषणा WPS_DPID_USER_SPEC			0x0001
#घोषणा WPS_DPID_MACHINE_SPEC			0x0002
#घोषणा WPS_DPID_REKEY					0x0003
#घोषणा WPS_DPID_PBC					0x0004
#घोषणा WPS_DPID_REGISTRAR_SPEC		0x0005

/* 	Value of WPS RF Bands Attribute */
#घोषणा WPS_RF_BANDS_2_4_GHZ		0x01
#घोषणा WPS_RF_BANDS_5_GHZ		0x02

/* 	Value of WPS Association State Attribute */
#घोषणा WPS_ASSOC_STATE_NOT_ASSOCIATED			0x00
#घोषणा WPS_ASSOC_STATE_CONNECTION_SUCCESS		0x01
#घोषणा WPS_ASSOC_STATE_CONFIGURATION_FAILURE	0x02
#घोषणा WPS_ASSOC_STATE_ASSOCIATION_FAILURE		0x03
#घोषणा WPS_ASSOC_STATE_IP_FAILURE				0x04

/* 	=====================P2P Section ===================== */
/* 	For P2P */
#घोषणा	P2POUI							0x506F9A09

/* 	P2P Attribute ID */
#घोषणा	P2P_ATTR_STATUS					0x00
#घोषणा	P2P_ATTR_MINOR_REASON_CODE		0x01
#घोषणा	P2P_ATTR_CAPABILITY				0x02
#घोषणा	P2P_ATTR_DEVICE_ID				0x03
#घोषणा	P2P_ATTR_GO_INTENT				0x04
#घोषणा	P2P_ATTR_CONF_TIMEOUT			0x05
#घोषणा	P2P_ATTR_LISTEN_CH				0x06
#घोषणा	P2P_ATTR_GROUP_BSSID				0x07
#घोषणा	P2P_ATTR_EX_LISTEN_TIMING		0x08
#घोषणा	P2P_ATTR_INTENTED_IF_ADDR		0x09
#घोषणा	P2P_ATTR_MANAGEABILITY			0x0A
#घोषणा	P2P_ATTR_CH_LIST					0x0B
#घोषणा	P2P_ATTR_NOA						0x0C
#घोषणा	P2P_ATTR_DEVICE_INFO				0x0D
#घोषणा	P2P_ATTR_GROUP_INFO				0x0E
#घोषणा	P2P_ATTR_GROUP_ID					0x0F
#घोषणा	P2P_ATTR_INTERFACE				0x10
#घोषणा	P2P_ATTR_OPERATING_CH			0x11
#घोषणा	P2P_ATTR_INVITATION_FLAGS		0x12

/* 	Value of Status Attribute */
#घोषणा	P2P_STATUS_SUCCESS						0x00
#घोषणा	P2P_STATUS_FAIL_INFO_UNAVAILABLE		0x01
#घोषणा	P2P_STATUS_FAIL_INCOMPATIBLE_PARAM		0x02
#घोषणा	P2P_STATUS_FAIL_LIMIT_REACHED			0x03
#घोषणा	P2P_STATUS_FAIL_INVALID_PARAM			0x04
#घोषणा	P2P_STATUS_FAIL_REQUEST_UNABLE			0x05
#घोषणा	P2P_STATUS_FAIL_PREVOUS_PROTO_ERR		0x06
#घोषणा	P2P_STATUS_FAIL_NO_COMMON_CH			0x07
#घोषणा	P2P_STATUS_FAIL_UNKNOWN_P2PGROUP		0x08
#घोषणा	P2P_STATUS_FAIL_BOTH_GOINTENT_15		0x09
#घोषणा	P2P_STATUS_FAIL_INCOMPATIBLE_PROVSION	0x0A
#घोषणा	P2P_STATUS_FAIL_USER_REJECT				0x0B

/* 	Value of Invitation Flags Attribute */
#घोषणा	P2P_INVITATION_FLAGS_PERSISTENT			BIT(0)

#घोषणा	DMP_P2P_DEVCAP_SUPPORT	(P2P_DEVCAP_SERVICE_DISCOVERY | \
									P2P_DEVCAP_CLIENT_DISCOVERABILITY | \
									P2P_DEVCAP_CONCURRENT_OPERATION | \
									P2P_DEVCAP_INVITATION_PROC)

#घोषणा	DMP_P2P_GRPCAP_SUPPORT	(P2P_GRPCAP_INTRABSS)

/* 	Value of Device Capability Biपंचांगap */
#घोषणा	P2P_DEVCAP_SERVICE_DISCOVERY		BIT(0)
#घोषणा	P2P_DEVCAP_CLIENT_DISCOVERABILITY	BIT(1)
#घोषणा	P2P_DEVCAP_CONCURRENT_OPERATION	BIT(2)
#घोषणा	P2P_DEVCAP_INFRA_MANAGED			BIT(3)
#घोषणा	P2P_DEVCAP_DEVICE_LIMIT				BIT(4)
#घोषणा	P2P_DEVCAP_INVITATION_PROC			BIT(5)

/* 	Value of Group Capability Biपंचांगap */
#घोषणा	P2P_GRPCAP_GO							BIT(0)
#घोषणा	P2P_GRPCAP_PERSISTENT_GROUP			BIT(1)
#घोषणा	P2P_GRPCAP_GROUP_LIMIT				BIT(2)
#घोषणा	P2P_GRPCAP_INTRABSS					BIT(3)
#घोषणा	P2P_GRPCAP_CROSS_CONN				BIT(4)
#घोषणा	P2P_GRPCAP_PERSISTENT_RECONN		BIT(5)
#घोषणा	P2P_GRPCAP_GROUP_FORMATION			BIT(6)

/* 	P2P Public Action Frame (Management Frame) */
#घोषणा	P2P_PUB_ACTION_ACTION				0x09

/* 	P2P Public Action Frame Type */
#घोषणा	P2P_GO_NEGO_REQ						0
#घोषणा	P2P_GO_NEGO_RESP						1
#घोषणा	P2P_GO_NEGO_CONF						2
#घोषणा	P2P_INVIT_REQ							3
#घोषणा	P2P_INVIT_RESP							4
#घोषणा	P2P_DEVDISC_REQ						5
#घोषणा	P2P_DEVDISC_RESP						6
#घोषणा	P2P_PROVISION_DISC_REQ				7
#घोषणा	P2P_PROVISION_DISC_RESP				8

/* 	P2P Action Frame Type */
#घोषणा	P2P_NOTICE_OF_ABSENCE	0
#घोषणा	P2P_PRESENCE_REQUEST		1
#घोषणा	P2P_PRESENCE_RESPONSE	2
#घोषणा	P2P_GO_DISC_REQUEST		3


#घोषणा	P2P_MAX_PERSISTENT_GROUP_NUM		10

#घोषणा	P2P_PROVISIONING_SCAN_CNT			3

#घोषणा	P2P_WILDCARD_SSID_LEN				7

#घोषणा	P2P_FINDPHASE_EX_NONE				0	/*  शेष value, used when: (1)p2p disabled or (2)p2p enabled but only करो 1 scan phase */
#घोषणा	P2P_FINDPHASE_EX_FULL				1	/*  used when p2p enabled and want to करो 1 scan phase and P2P_FINDPHASE_EX_MAX-1 find phase */
#घोषणा	P2P_FINDPHASE_EX_SOCIAL_FIRST		(P2P_FINDPHASE_EX_FULL+1)
#घोषणा	P2P_FINDPHASE_EX_MAX					4
#घोषणा	P2P_FINDPHASE_EX_SOCIAL_LAST		P2P_FINDPHASE_EX_MAX

#घोषणा	P2P_PROVISION_TIMEOUT				5000	/* 	5 seconds समयout क्रम sending the provision discovery request */
#घोषणा	P2P_CONCURRENT_PROVISION_TIMEOUT	3000	/* 	3 seconds समयout क्रम sending the provision discovery request under concurrent mode */
#घोषणा	P2P_GO_NEGO_TIMEOUT					5000	/* 	5 seconds समयout क्रम receiving the group negotiation response */
#घोषणा	P2P_CONCURRENT_GO_NEGO_TIMEOUT		3000	/* 	3 seconds समयout क्रम sending the negotiation request under concurrent mode */
#घोषणा	P2P_TX_PRESCAN_TIMEOUT				100		/* 	100ms */
#घोषणा	P2P_INVITE_TIMEOUT					5000	/* 	5 seconds समयout क्रम sending the invitation request */
#घोषणा	P2P_CONCURRENT_INVITE_TIMEOUT		3000	/* 	3 seconds समयout क्रम sending the invitation request under concurrent mode */
#घोषणा	P2P_RESET_SCAN_CH						25000	/* 	25 seconds समयout to reset the scan channel (based on channel plan) */
#घोषणा	P2P_MAX_INTENT						15

#घोषणा	P2P_MAX_NOA_NUM						2

/* 	WPS Configuration Method */
#घोषणा	WPS_CM_NONE							0x0000
#घोषणा	WPS_CM_LABEL							0x0004
#घोषणा	WPS_CM_DISPLYA						0x0008
#घोषणा	WPS_CM_EXTERNAL_NFC_TOKEN			0x0010
#घोषणा	WPS_CM_INTEGRATED_NFC_TOKEN		0x0020
#घोषणा	WPS_CM_NFC_INTERFACE					0x0040
#घोषणा	WPS_CM_PUSH_BUTTON					0x0080
#घोषणा	WPS_CM_KEYPAD						0x0100
#घोषणा	WPS_CM_SW_PUHS_BUTTON				0x0280
#घोषणा	WPS_CM_HW_PUHS_BUTTON				0x0480
#घोषणा	WPS_CM_SW_DISPLAY_PIN				0x2008
#घोषणा	WPS_CM_LCD_DISPLAY_PIN				0x4008

क्रमागत p2p_role अणु
	P2P_ROLE_DISABLE = 0,
	P2P_ROLE_DEVICE = 1,
	P2P_ROLE_CLIENT = 2,
	P2P_ROLE_GO = 3
पूर्ण;

क्रमागत p2p_state अणु
	P2P_STATE_NONE = 0,							/* 	P2P disable */
	P2P_STATE_IDLE = 1,								/* 	P2P had enabled and करो nothing */
	P2P_STATE_LISTEN = 2,							/* 	In pure listen state */
	P2P_STATE_SCAN = 3,							/* 	In scan phase */
	P2P_STATE_FIND_PHASE_LISTEN = 4,				/* 	In the listen state of find phase */
	P2P_STATE_FIND_PHASE_SEARCH = 5,				/* 	In the search state of find phase */
	P2P_STATE_TX_PROVISION_DIS_REQ = 6,			/* 	In P2P provisioning discovery */
	P2P_STATE_RX_PROVISION_DIS_RSP = 7,
	P2P_STATE_RX_PROVISION_DIS_REQ = 8,
	P2P_STATE_GONEGO_ING = 9,						/* 	Doing the group owner negotiation handshake */
	P2P_STATE_GONEGO_OK = 10,						/* 	finish the group negotiation handshake with success */
	P2P_STATE_GONEGO_FAIL = 11,					/* 	finish the group negotiation handshake with failure */
	P2P_STATE_RECV_INVITE_REQ_MATCH = 12,		/* 	receiving the P2P Invitation request and match with the profile. */
	P2P_STATE_PROVISIONING_ING = 13,				/* 	Doing the P2P WPS */
	P2P_STATE_PROVISIONING_DONE = 14,			/* 	Finish the P2P WPS */
	P2P_STATE_TX_INVITE_REQ = 15,					/* 	Transmit the P2P Invitation request */
	P2P_STATE_RX_INVITE_RESP_OK = 16,				/* 	Receiving the P2P Invitation response */
	P2P_STATE_RECV_INVITE_REQ_DISMATCH = 17,	/* 	receiving the P2P Invitation request and mismatch with the profile. */
	P2P_STATE_RECV_INVITE_REQ_GO = 18,			/* 	receiving the P2P Invitation request and this wअगरi is GO. */
	P2P_STATE_RECV_INVITE_REQ_JOIN = 19,			/* 	receiving the P2P Invitation request to join an existing P2P Group. */
	P2P_STATE_RX_INVITE_RESP_FAIL = 20,			/* 	recveing the P2P Invitation response with failure */
	P2P_STATE_RX_INFOR_NOREADY = 21,			/*  receiving p2p negotiation response with inक्रमmation is not available */
	P2P_STATE_TX_INFOR_NOREADY = 22,			/*  sending p2p negotiation response with inक्रमmation is not available */
पूर्ण;

क्रमागत p2p_wpsinfo अणु
	P2P_NO_WPSINFO						= 0,
	P2P_GOT_WPSINFO_PEER_DISPLAY_PIN	= 1,
	P2P_GOT_WPSINFO_SELF_DISPLAY_PIN	= 2,
	P2P_GOT_WPSINFO_PBC					= 3,
पूर्ण;

#घोषणा	P2P_PRIVATE_IOCTL_SET_LEN		64

/* 	=====================WFD Section ===================== */
/* 	For Wi-Fi Display */
#घोषणा	WFD_ATTR_DEVICE_INFO			0x00
#घोषणा	WFD_ATTR_ASSOC_BSSID			0x01
#घोषणा	WFD_ATTR_COUPLED_SINK_INFO	0x06
#घोषणा	WFD_ATTR_LOCAL_IP_ADDR		0x08
#घोषणा	WFD_ATTR_SESSION_INFO		0x09
#घोषणा	WFD_ATTR_ALTER_MAC			0x0a

/* 	For WFD Device Inक्रमmation Attribute */
#घोषणा	WFD_DEVINFO_SOURCE					0x0000
#घोषणा	WFD_DEVINFO_PSINK					0x0001
#घोषणा	WFD_DEVINFO_SSINK					0x0002
#घोषणा	WFD_DEVINFO_DUAL					0x0003

#घोषणा	WFD_DEVINFO_SESSION_AVAIL			0x0010
#घोषणा	WFD_DEVINFO_WSD						0x0040
#घोषणा	WFD_DEVINFO_PC_TDLS					0x0080
#घोषणा	WFD_DEVINFO_HDCP_SUPPORT			0x0100

#घोषणा IP_MCAST_MAC(mac)		((mac[0] == 0x01) && (mac[1] == 0x00) && (mac[2] == 0x5e))
#घोषणा ICMPV6_MCAST_MAC(mac)	((mac[0] == 0x33) && (mac[1] == 0x33) && (mac[2] != 0xff))

/* Regulatroy Doमुख्य */
काष्ठा regd_pair_mapping अणु
	u16 reg_dmnक्रमागत;
	u16 reg_2ghz_ctl;
पूर्ण;

काष्ठा rtw_regulatory अणु
	अक्षर alpha2[2];
	u16 country_code;
	u16 max_घातer_level;
	u32 tp_scale;
	u16 current_rd;
	u16 current_rd_ext;
	पूर्णांक16_t घातer_limit;
	काष्ठा regd_pair_mapping *regpair;
पूर्ण;

#पूर्ण_अगर /*  _WIFI_H_ */
