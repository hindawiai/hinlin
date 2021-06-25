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
#अगर_अघोषित _WIFI_H_
#घोषणा _WIFI_H_

#समावेश <linux/compiler.h>
#समावेश <linux/ieee80211.h>

#घोषणा WLAN_HDR_A3_LEN		24
#घोषणा WLAN_HDR_A3_QOS_LEN	26

#घोषणा P80211CAPTURE_VERSION	0x80211001

क्रमागत WIFI_FRAME_TYPE अणु
	WIFI_QOS_DATA_TYPE	= (BIT(7) | BIT(3)),	/*!< QoS Data */
पूर्ण;

क्रमागत WIFI_REG_DOMAIN अणु
	DOMAIN_FCC	= 1,
	DOMAIN_IC	= 2,
	DOMAIN_ETSI	= 3,
	DOMAIN_SPAIN	= 4,
	DOMAIN_FRANCE	= 5,
	DOMAIN_MKK	= 6,
	DOMAIN_ISRAEL	= 7,
	DOMAIN_MKK1	= 8,
	DOMAIN_MKK2	= 9,
	DOMAIN_MKK3	= 10,
	DOMAIN_MAX
पूर्ण;

#घोषणा SetToDs(pbuf) (अणु \
	*(__le16 *)(pbuf) |= cpu_to_le16(IEEE80211_FCTL_TODS); \
पूर्ण)

#घोषणा GetToDs(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(IEEE80211_FCTL_TODS)) != 0)

#घोषणा ClearToDs(pbuf)	(अणु \
	*(__le16 *)(pbuf) &= (~cpu_to_le16(IEEE80211_FCTL_TODS)); \
पूर्ण)

#घोषणा SetFrDs(pbuf) (अणु \
	*(__le16 *)(pbuf) |= cpu_to_le16(IEEE80211_FCTL_FROMDS); \
पूर्ण)

#घोषणा GetFrDs(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(IEEE80211_FCTL_FROMDS)) != 0)

#घोषणा ClearFrDs(pbuf)	(अणु \
	*(__le16 *)(pbuf) &= (~cpu_to_le16(IEEE80211_FCTL_FROMDS)); \
पूर्ण)

अटल अंतरभूत अचिन्हित अक्षर get_tofr_ds(अचिन्हित अक्षर *pframe)
अणु
	वापस ((GetToDs(pframe) << 1) | GetFrDs(pframe));
पूर्ण

#घोषणा SetMFrag(pbuf) (अणु \
	*(__le16 *)(pbuf) |= cpu_to_le16(IEEE80211_FCTL_MOREFRAGS); \
पूर्ण)

#घोषणा GetMFrag(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(IEEE80211_FCTL_MOREFRAGS)) != 0)

#घोषणा ClearMFrag(pbuf) (अणु \
	*(__le16 *)(pbuf) &= (~cpu_to_le16(IEEE80211_FCTL_MOREFRAGS)); \
पूर्ण)

#घोषणा SetRetry(pbuf) (अणु \
	*(__le16 *)(pbuf) |= cpu_to_le16(IEEE80211_FCTL_RETRY); \
पूर्ण)

#घोषणा GetRetry(pbuf)	(((*(__le16 *)(pbuf)) & cpu_to_le16(IEEE80211_FCTL_RETRY)) != 0)

#घोषणा ClearRetry(pbuf) (अणु \
	*(__le16 *)(pbuf) &= (~cpu_to_le16(IEEE80211_FCTL_RETRY)); \
पूर्ण)

#घोषणा SetPwrMgt(pbuf) (अणु \
	*(__le16 *)(pbuf) |= cpu_to_le16(IEEE80211_FCTL_PM); \
पूर्ण)

#घोषणा GetPwrMgt(pbuf)	(((*(__le16 *)(pbuf)) & \
			cpu_to_le16(IEEE80211_FCTL_PM)) != 0)

#घोषणा ClearPwrMgt(pbuf) (अणु \
	*(__le16 *)(pbuf) &= (~cpu_to_le16(IEEE80211_FCTL_PM)); \
पूर्ण)

#घोषणा SetMData(pbuf) (अणु \
	*(__le16 *)(pbuf) |= cpu_to_le16(IEEE80211_FCTL_MOREDATA); \
पूर्ण)

#घोषणा GetMData(pbuf)	(((*(__le16 *)(pbuf)) & \
			cpu_to_le16(IEEE80211_FCTL_MOREDATA)) != 0)

#घोषणा ClearMData(pbuf) (अणु \
	*(__le16 *)(pbuf) &= (~cpu_to_le16(IEEE80211_FCTL_MOREDATA)); \
पूर्ण)

#घोषणा SetPrivacy(pbuf) (अणु \
	*(__le16 *)(pbuf) |= cpu_to_le16(IEEE80211_FCTL_PROTECTED); \
पूर्ण)

#घोषणा GetPrivacy(pbuf)	(((*(__le16 *)(pbuf)) & \
				cpu_to_le16(IEEE80211_FCTL_PROTECTED)) != 0)

#घोषणा GetOrder(pbuf)	(((*(__le16 *)(pbuf)) & \
			cpu_to_le16(IEEE80211_FCTL_ORDER)) != 0)

#घोषणा GetFrameType(pbuf)	(le16_to_cpu(*(__le16 *)(pbuf)) & \
				(BIT(3) | BIT(2)))

#घोषणा SetFrameType(pbuf, type)	\
	करो अणु	\
		*(__le16 *)(pbuf) &= cpu_to_le16(~(BIT(3) | \
		BIT(2))); \
		*(__le16 *)(pbuf) |= cpu_to_le16(type); \
	पूर्ण जबतक (0)

#घोषणा GetFrameSubType(pbuf)	(le16_to_cpu(*(__le16 *)(pbuf)) & \
				(BIT(7) | BIT(6) | BIT(5) | BIT(4) | BIT(3) | \
				BIT(2)))

#घोषणा SetFrameSubType(pbuf, type) \
	करो अणु    \
		*(__le16 *)(pbuf) &= cpu_to_le16(~(BIT(7) | BIT(6) | \
		BIT(5) | BIT(4) | BIT(3) | BIT(2))); \
		*(__le16 *)(pbuf) |= cpu_to_le16(type); \
	पूर्ण जबतक (0)

#घोषणा GetSequence(pbuf)	(le16_to_cpu(*(__le16 *)\
				((addr_t)(pbuf) + 22)) >> 4)

#घोषणा GetFragNum(pbuf)	(le16_to_cpu(*(__le16 *)((addr_t)\
				(pbuf) + 22)) & 0x0f)

#घोषणा SetSeqNum(pbuf, num) (अणु \
	*(__le16 *)((addr_t)(pbuf) + 22) = \
	cpu_to_le16((le16_to_cpu(*(__le16 *)((addr_t)(pbuf) + 22)) & \
	0x000f) | (0xfff0 & (num << 4))); \
पूर्ण)

#घोषणा SetPriority(pbuf, tid) (अणु \
	*(__le16 *)(pbuf) |= cpu_to_le16(tid & 0xf); \
पूर्ण)

#घोषणा GetPriority(pbuf)	((le16_to_cpu(*(__le16 *)(pbuf))) & 0xf)

#घोषणा SetAckpolicy(pbuf, ack) (अणु \
	*(__le16 *)(pbuf) |= cpu_to_le16((ack & 3) << 5); \
पूर्ण)

#घोषणा GetAckpolicy(pbuf) (((le16_to_cpu(*(__le16 *)pbuf)) >> 5) & 0x3)

#घोषणा GetAMsdu(pbuf) (((le16_to_cpu(*(__le16 *)pbuf)) >> 7) & 0x1)

#घोषणा GetAddr1Ptr(pbuf)	((अचिन्हित अक्षर *)((addr_t)(pbuf) + 4))

#घोषणा GetAddr2Ptr(pbuf)	((अचिन्हित अक्षर *)((addr_t)(pbuf) + 10))

#घोषणा GetAddr3Ptr(pbuf)	((अचिन्हित अक्षर *)((addr_t)(pbuf) + 16))

#घोषणा GetAddr4Ptr(pbuf)	((अचिन्हित अक्षर *)((addr_t)(pbuf) + 24))

अटल अंतरभूत अचिन्हित अक्षर *get_hdr_bssid(अचिन्हित अक्षर *pframe)
अणु
	अचिन्हित अक्षर	*sa;
	अचिन्हित पूर्णांक	to_fr_ds = (GetToDs(pframe) << 1) | GetFrDs(pframe);

	चयन (to_fr_ds) अणु
	हाल 0x00:	/* ToDs=0, FromDs=0 */
		sa = GetAddr3Ptr(pframe);
		अवरोध;
	हाल 0x01:	/* ToDs=0, FromDs=1 */
		sa = GetAddr2Ptr(pframe);
		अवरोध;
	हाल 0x02:	/* ToDs=1, FromDs=0 */
		sa = GetAddr1Ptr(pframe);
		अवरोध;
	शेष:	/* ToDs=1, FromDs=1 */
		sa = शून्य;
		अवरोध;
	पूर्ण
	वापस sa;
पूर्ण

/*-----------------------------------------------------------------------------
 *		Below is क्रम the security related definition
 *-----------------------------------------------------------------------------
 */
#घोषणा _ASOCREQ_IE_OFFSET_	4	/* excluding wlan_hdr */
#घोषणा	_ASOCRSP_IE_OFFSET_	6
#घोषणा _REASOCREQ_IE_OFFSET_	10
#घोषणा _REASOCRSP_IE_OFFSET_	6
#घोषणा _PROBEREQ_IE_OFFSET_	0
#घोषणा	_PROBERSP_IE_OFFSET_	12
#घोषणा _AUTH_IE_OFFSET_	6
#घोषणा _DEAUTH_IE_OFFSET_	0
#घोषणा _BEACON_IE_OFFSET_	12

#घोषणा _FIXED_IE_LENGTH_	_BEACON_IE_OFFSET_

/* ---------------------------------------------------------------------------
 *			Below is the fixed elements...
 * ---------------------------------------------------------------------------
 */
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

/*-----------------------------------------------------------------------------
 *			Below is the definition क्रम 802.11i / 802.1x
 *------------------------------------------------------------------------------
 */
#घोषणा _IEEE8021X_MGT_			1	/*WPA */
#घोषणा _IEEE8021X_PSK_			2	/* WPA with pre-shared key */

/*-----------------------------------------------------------------------------
 *			Below is the definition क्रम WMM
 *------------------------------------------------------------------------------
 */
#घोषणा _WMM_IE_Length_				7  /* क्रम WMM STA */

#पूर्ण_अगर /* _WIFI_H_ */

