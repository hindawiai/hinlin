<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1) */
/* p80211mgmt.h
 *
 * Macros, types, and functions to handle 802.11 mgmt frames
 *
 * Copyright (C) 1999 AbsoluteValue Systems, Inc.  All Rights Reserved.
 * --------------------------------------------------------------------
 *
 * linux-wlan
 *
 *   The contents of this file are subject to the Mozilla Public
 *   License Version 1.1 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.mozilla.org/MPL/
 *
 *   Software distributed under the License is distributed on an "AS
 *   IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 *   implied. See the License क्रम the specअगरic language governing
 *   rights and limitations under the License.
 *
 *   Alternatively, the contents of this file may be used under the
 *   terms of the GNU Public License version 2 (the "GPL"), in which
 *   हाल the provisions of the GPL are applicable instead of the
 *   above.  If you wish to allow the use of your version of this file
 *   only under the terms of the GPL and not to allow others to use
 *   your version of this file under the MPL, indicate your decision
 *   by deleting the provisions above and replace them with the notice
 *   and other provisions required by the GPL.  If you करो not delete
 *   the provisions above, a recipient may use your version of this
 *   file under either the MPL or the GPL.
 *
 * --------------------------------------------------------------------
 *
 * Inquiries regarding the linux-wlan Open Source project can be
 * made directly to:
 *
 * AbsoluteValue Systems Inc.
 * info@linux-wlan.com
 * http://www.linux-wlan.com
 *
 * --------------------------------------------------------------------
 *
 * Portions of the development of this software were funded by
 * Intersil Corporation as part of PRISM(R) chipset product development.
 *
 * --------------------------------------------------------------------
 *
 * This file declares the स्थिरants and types used in the पूर्णांकerface
 * between a wlan driver and the user mode utilities.
 *
 * Notes:
 *  - Constant values are always in HOST byte order.  To assign
 *    values to multi-byte fields they _must_ be converted to
 *    ieee byte order.  To retrieve multi-byte values from incoming
 *    frames, they must be converted to host order.
 *
 *  - The len member of the frame काष्ठाure करोes NOT!!! include
 *    the MAC CRC.  Thereक्रमe, the len field on rx'd frames should
 *    have 4 subtracted from it.
 *
 * All functions declared here are implemented in p80211.c
 *
 * The types, macros, and functions defined here are primarily
 * used क्रम encoding and decoding management frames.  They are
 * deचिन्हित to follow these patterns of use:
 *
 * DECODE:
 * 1) a frame of length len is received पूर्णांकo buffer b
 * 2) using the hdr काष्ठाure and macros, we determine the type
 * 3) an appropriate mgmt frame काष्ठाure, mf, is allocated and zeroed
 * 4) mf.hdr = b
 *    mf.buf = b
 *    mf.len = len
 * 5) call mgmt_decode( mf )
 * 6) the frame field poपूर्णांकers in mf are now set.  Note that any
 *    multi-byte frame field values accessed using the frame field
 *    poपूर्णांकers are in ieee byte order and will have to be converted
 *    to host order.
 *
 * ENCODE:
 * 1) Library client allocates buffer space क्रम maximum length
 *    frame of the desired type
 * 2) Library client allocates a mgmt frame काष्ठाure, called mf,
 *    of the desired type
 * 3) Set the following:
 *    mf.type = <desired type>
 *    mf.buf = <allocated buffer address>
 * 4) call mgmt_encode( mf )
 * 5) all of the fixed field poपूर्णांकers and fixed length inक्रमmation element
 *    poपूर्णांकers in mf are now set to their respective locations in the
 *    allocated space (क्रमtunately, all variable length inक्रमmation elements
 *    fall at the end of their respective frames).
 * 5a) The length field is set to include the last of the fixed and fixed
 *     length fields.  It may have to be updated क्रम optional or variable
 *	length inक्रमmation elements.
 * 6) Optional and variable length inक्रमmation elements are special हालs
 *    and must be handled inभागidually by the client code.
 * --------------------------------------------------------------------
 */

#अगर_अघोषित _P80211MGMT_H
#घोषणा _P80211MGMT_H

#अगर_अघोषित _P80211HDR_H
#समावेश "p80211hdr.h"
#पूर्ण_अगर

/*-- Inक्रमmation Element IDs --------------------*/
#घोषणा WLAN_EID_SSID		0
#घोषणा WLAN_EID_SUPP_RATES	1
#घोषणा WLAN_EID_FH_PARMS	2
#घोषणा WLAN_EID_DS_PARMS	3
#घोषणा WLAN_EID_CF_PARMS	4
#घोषणा WLAN_EID_TIM		5
#घोषणा WLAN_EID_IBSS_PARMS	6
/*-- values 7-15 reserved --*/
#घोषणा WLAN_EID_CHALLENGE	16
/*-- values 17-31 reserved क्रम challenge text extension --*/
/*-- values 32-255 reserved --*/

/*-- Reason Codes -------------------------------*/
#घोषणा WLAN_MGMT_REASON_RSVD			0
#घोषणा WLAN_MGMT_REASON_UNSPEC			1
#घोषणा WLAN_MGMT_REASON_PRIOR_AUTH_INVALID	2
#घोषणा WLAN_MGMT_REASON_DEAUTH_LEAVING		3
#घोषणा WLAN_MGMT_REASON_DISASSOC_INACTIVE	4
#घोषणा WLAN_MGMT_REASON_DISASSOC_AP_BUSY	5
#घोषणा WLAN_MGMT_REASON_CLASS2_NONAUTH		6
#घोषणा WLAN_MGMT_REASON_CLASS3_NONASSOC	7
#घोषणा WLAN_MGMT_REASON_DISASSOC_STA_HASLEFT	8
#घोषणा WLAN_MGMT_REASON_CANT_ASSOC_NONAUTH	9

/*-- Status Codes -------------------------------*/
#घोषणा WLAN_MGMT_STATUS_SUCCESS		0
#घोषणा WLAN_MGMT_STATUS_UNSPEC_FAILURE		1
#घोषणा WLAN_MGMT_STATUS_CAPS_UNSUPPORTED	10
#घोषणा WLAN_MGMT_STATUS_REASSOC_NO_ASSOC	11
#घोषणा WLAN_MGMT_STATUS_ASSOC_DENIED_UNSPEC	12
#घोषणा WLAN_MGMT_STATUS_UNSUPPORTED_AUTHALG	13
#घोषणा WLAN_MGMT_STATUS_RX_AUTH_NOSEQ		14
#घोषणा WLAN_MGMT_STATUS_CHALLENGE_FAIL		15
#घोषणा WLAN_MGMT_STATUS_AUTH_TIMEOUT		16
#घोषणा WLAN_MGMT_STATUS_ASSOC_DENIED_BUSY	17
#घोषणा WLAN_MGMT_STATUS_ASSOC_DENIED_RATES	18
  /* p80211b additions */
#घोषणा WLAN_MGMT_STATUS_ASSOC_DENIED_NOSHORT	19
#घोषणा WLAN_MGMT_STATUS_ASSOC_DENIED_NOPBCC	20
#घोषणा WLAN_MGMT_STATUS_ASSOC_DENIED_NOAGILITY	21

/*-- Auth Algorithm Field ---------------------------*/
#घोषणा WLAN_AUTH_ALG_OPENSYSTEM		0
#घोषणा WLAN_AUTH_ALG_SHAREDKEY			1

/*-- Management Frame Field Offsets -------------*/
/* Note: Not all fields are listed because of variable lengths,   */
/*       see the code in p80211.c to see how we search क्रम fields */
/* Note: These offsets are from the start of the frame data       */

#घोषणा WLAN_BEACON_OFF_TS			0
#घोषणा WLAN_BEACON_OFF_BCN_पूर्णांक			8
#घोषणा WLAN_BEACON_OFF_CAPINFO			10
#घोषणा WLAN_BEACON_OFF_SSID			12

#घोषणा WLAN_DISASSOC_OFF_REASON		0

#घोषणा WLAN_ASSOCREQ_OFF_CAP_INFO		0
#घोषणा WLAN_ASSOCREQ_OFF_LISTEN_पूर्णांक		2
#घोषणा WLAN_ASSOCREQ_OFF_SSID			4

#घोषणा WLAN_ASSOCRESP_OFF_CAP_INFO		0
#घोषणा WLAN_ASSOCRESP_OFF_STATUS		2
#घोषणा WLAN_ASSOCRESP_OFF_AID			4
#घोषणा WLAN_ASSOCRESP_OFF_SUPP_RATES		6

#घोषणा WLAN_REASSOCREQ_OFF_CAP_INFO		0
#घोषणा WLAN_REASSOCREQ_OFF_LISTEN_पूर्णांक		2
#घोषणा WLAN_REASSOCREQ_OFF_CURR_AP		4
#घोषणा WLAN_REASSOCREQ_OFF_SSID		10

#घोषणा WLAN_REASSOCRESP_OFF_CAP_INFO		0
#घोषणा WLAN_REASSOCRESP_OFF_STATUS		2
#घोषणा WLAN_REASSOCRESP_OFF_AID		4
#घोषणा WLAN_REASSOCRESP_OFF_SUPP_RATES		6

#घोषणा WLAN_PROBEREQ_OFF_SSID			0

#घोषणा WLAN_PROBERESP_OFF_TS			0
#घोषणा WLAN_PROBERESP_OFF_BCN_पूर्णांक		8
#घोषणा WLAN_PROBERESP_OFF_CAP_INFO		10
#घोषणा WLAN_PROBERESP_OFF_SSID			12

#घोषणा WLAN_AUTHEN_OFF_AUTH_ALG		0
#घोषणा WLAN_AUTHEN_OFF_AUTH_SEQ		2
#घोषणा WLAN_AUTHEN_OFF_STATUS			4
#घोषणा WLAN_AUTHEN_OFF_CHALLENGE		6

#घोषणा WLAN_DEAUTHEN_OFF_REASON		0

/*-- Capability Field ---------------------------*/
#घोषणा WLAN_GET_MGMT_CAP_INFO_ESS(n)		((n) & BIT(0))
#घोषणा WLAN_GET_MGMT_CAP_INFO_IBSS(n)		(((n) & BIT(1)) >> 1)
#घोषणा WLAN_GET_MGMT_CAP_INFO_CFPOLLABLE(n)	(((n) & BIT(2)) >> 2)
#घोषणा WLAN_GET_MGMT_CAP_INFO_CFPOLLREQ(n)	(((n) & BIT(3)) >> 3)
#घोषणा WLAN_GET_MGMT_CAP_INFO_PRIVACY(n)	(((n) & BIT(4)) >> 4)
  /* p80211b additions */
#घोषणा WLAN_GET_MGMT_CAP_INFO_SHORT(n)		(((n) & BIT(5)) >> 5)
#घोषणा WLAN_GET_MGMT_CAP_INFO_PBCC(n)		(((n) & BIT(6)) >> 6)
#घोषणा WLAN_GET_MGMT_CAP_INFO_AGILITY(n)	(((n) & BIT(7)) >> 7)

#घोषणा WLAN_SET_MGMT_CAP_INFO_ESS(n)		(n)
#घोषणा WLAN_SET_MGMT_CAP_INFO_IBSS(n)		((n) << 1)
#घोषणा WLAN_SET_MGMT_CAP_INFO_CFPOLLABLE(n)	((n) << 2)
#घोषणा WLAN_SET_MGMT_CAP_INFO_CFPOLLREQ(n)	((n) << 3)
#घोषणा WLAN_SET_MGMT_CAP_INFO_PRIVACY(n)	((n) << 4)
  /* p80211b additions */
#घोषणा WLAN_SET_MGMT_CAP_INFO_SHORT(n)		((n) << 5)
#घोषणा WLAN_SET_MGMT_CAP_INFO_PBCC(n)		((n) << 6)
#घोषणा WLAN_SET_MGMT_CAP_INFO_AGILITY(n)	((n) << 7)

/*-- Inक्रमmation Element Types --------------------*/
/* prototype काष्ठाure, all IEs start with these members */

काष्ठा wlan_ie अणु
	u8 eid;
	u8 len;
पूर्ण __packed;

/*-- Service Set Identity (SSID)  -----------------*/
काष्ठा wlan_ie_ssid अणु
	u8 eid;
	u8 len;
	u8 ssid[1];		/* may be zero, ptrs may overlap */
पूर्ण __packed;

/*-- Supported Rates  -----------------------------*/
काष्ठा wlan_ie_supp_rates अणु
	u8 eid;
	u8 len;
	u8 rates[1];		/* had better be at LEAST one! */
पूर्ण __packed;

/*-- FH Parameter Set  ----------------------------*/
काष्ठा wlan_ie_fh_parms अणु
	u8 eid;
	u8 len;
	u16 dwell;
	u8 hopset;
	u8 hoppattern;
	u8 hopindex;
पूर्ण __packed;

/*-- DS Parameter Set  ----------------------------*/
काष्ठा wlan_ie_ds_parms अणु
	u8 eid;
	u8 len;
	u8 curr_ch;
पूर्ण __packed;

/*-- CF Parameter Set  ----------------------------*/

काष्ठा wlan_ie_cf_parms अणु
	u8 eid;
	u8 len;
	u8 cfp_cnt;
	u8 cfp_period;
	u16 cfp_maxdur;
	u16 cfp_durreमुख्यing;
पूर्ण __packed;

/*-- TIM ------------------------------------------*/
काष्ठा wlan_ie_tim अणु
	u8 eid;
	u8 len;
	u8 dtim_cnt;
	u8 dtim_period;
	u8 biपंचांगap_ctl;
	u8 virt_bm[1];
पूर्ण __packed;

/*-- IBSS Parameter Set ---------------------------*/
काष्ठा wlan_ie_ibss_parms अणु
	u8 eid;
	u8 len;
	u16 atim_win;
पूर्ण __packed;

/*-- Challenge Text  ------------------------------*/
काष्ठा wlan_ie_challenge अणु
	u8 eid;
	u8 len;
	u8 challenge[1];
पूर्ण __packed;

/*-------------------------------------------------*/
/*  Frame Types  */

/* prototype काष्ठाure, all mgmt frame types will start with these members */
काष्ठा wlan_fr_mgmt अणु
	u16 type;
	u16 len;		/* DOES NOT include CRC !!!! */
	u8 *buf;
	जोड़ p80211_hdr *hdr;
	/* used क्रम target specअगरic data, skb in Linux */
	व्योम *priv;
	/*-- fixed fields -----------*/
	/*-- info elements ----------*/
पूर्ण;

/*-- Beacon ---------------------------------------*/
काष्ठा wlan_fr_beacon अणु
	u16 type;
	u16 len;
	u8 *buf;
	जोड़ p80211_hdr *hdr;
	/* used क्रम target specअगरic data, skb in Linux */
	व्योम *priv;
	/*-- fixed fields -----------*/
	u64 *ts;
	u16 *bcn_पूर्णांक;
	u16 *cap_info;
	/*-- info elements ----------*/
	काष्ठा wlan_ie_ssid *ssid;
	काष्ठा wlan_ie_supp_rates *supp_rates;
	काष्ठा wlan_ie_fh_parms *fh_parms;
	काष्ठा wlan_ie_ds_parms *ds_parms;
	काष्ठा wlan_ie_cf_parms *cf_parms;
	काष्ठा wlan_ie_ibss_parms *ibss_parms;
	काष्ठा wlan_ie_tim *tim;

पूर्ण;

/*-- IBSS ATIM ------------------------------------*/
काष्ठा wlan_fr_ibssatim अणु
	u16 type;
	u16 len;
	u8 *buf;
	जोड़ p80211_hdr *hdr;
	/* used क्रम target specअगरic data, skb in Linux */
	व्योम *priv;

	/*-- fixed fields -----------*/
	/*-- info elements ----------*/

	/* this frame type has a null body */

पूर्ण;

/*-- Disassociation -------------------------------*/
काष्ठा wlan_fr_disassoc अणु
	u16 type;
	u16 len;
	u8 *buf;
	जोड़ p80211_hdr *hdr;
	/* used क्रम target specअगरic data, skb in Linux */
	व्योम *priv;
	/*-- fixed fields -----------*/
	u16 *reason;

	/*-- info elements ----------*/

पूर्ण;

/*-- Association Request --------------------------*/
काष्ठा wlan_fr_assocreq अणु
	u16 type;
	u16 len;
	u8 *buf;
	जोड़ p80211_hdr *hdr;
	/* used क्रम target specअगरic data, skb in Linux */
	व्योम *priv;
	/*-- fixed fields -----------*/
	u16 *cap_info;
	u16 *listen_पूर्णांक;
	/*-- info elements ----------*/
	काष्ठा wlan_ie_ssid *ssid;
	काष्ठा wlan_ie_supp_rates *supp_rates;

पूर्ण;

/*-- Association Response -------------------------*/
काष्ठा wlan_fr_assocresp अणु
	u16 type;
	u16 len;
	u8 *buf;
	जोड़ p80211_hdr *hdr;
	/* used क्रम target specअगरic data, skb in Linux */
	व्योम *priv;
	/*-- fixed fields -----------*/
	u16 *cap_info;
	u16 *status;
	u16 *aid;
	/*-- info elements ----------*/
	काष्ठा wlan_ie_supp_rates *supp_rates;

पूर्ण;

/*-- Reassociation Request ------------------------*/
काष्ठा wlan_fr_reassocreq अणु
	u16 type;
	u16 len;
	u8 *buf;
	जोड़ p80211_hdr *hdr;
	/* used क्रम target specअगरic data, skb in Linux */
	व्योम *priv;
	/*-- fixed fields -----------*/
	u16 *cap_info;
	u16 *listen_पूर्णांक;
	u8 *curr_ap;
	/*-- info elements ----------*/
	काष्ठा wlan_ie_ssid *ssid;
	काष्ठा wlan_ie_supp_rates *supp_rates;

पूर्ण;

/*-- Reassociation Response -----------------------*/
काष्ठा wlan_fr_reassocresp अणु
	u16 type;
	u16 len;
	u8 *buf;
	जोड़ p80211_hdr *hdr;
	/* used क्रम target specअगरic data, skb in Linux */
	व्योम *priv;
	/*-- fixed fields -----------*/
	u16 *cap_info;
	u16 *status;
	u16 *aid;
	/*-- info elements ----------*/
	काष्ठा wlan_ie_supp_rates *supp_rates;

पूर्ण;

/*-- Probe Request --------------------------------*/
काष्ठा wlan_fr_probereq अणु
	u16 type;
	u16 len;
	u8 *buf;
	जोड़ p80211_hdr *hdr;
	/* used क्रम target specअगरic data, skb in Linux */
	व्योम *priv;
	/*-- fixed fields -----------*/
	/*-- info elements ----------*/
	काष्ठा wlan_ie_ssid *ssid;
	काष्ठा wlan_ie_supp_rates *supp_rates;

पूर्ण;

/*-- Probe Response -------------------------------*/
काष्ठा wlan_fr_proberesp अणु
	u16 type;
	u16 len;
	u8 *buf;
	जोड़ p80211_hdr *hdr;
	/* used क्रम target specअगरic data, skb in Linux */
	व्योम *priv;
	/*-- fixed fields -----------*/
	u64 *ts;
	u16 *bcn_पूर्णांक;
	u16 *cap_info;
	/*-- info elements ----------*/
	काष्ठा wlan_ie_ssid *ssid;
	काष्ठा wlan_ie_supp_rates *supp_rates;
	काष्ठा wlan_ie_fh_parms *fh_parms;
	काष्ठा wlan_ie_ds_parms *ds_parms;
	काष्ठा wlan_ie_cf_parms *cf_parms;
	काष्ठा wlan_ie_ibss_parms *ibss_parms;
पूर्ण;

/*-- Authentication -------------------------------*/
काष्ठा wlan_fr_authen अणु
	u16 type;
	u16 len;
	u8 *buf;
	जोड़ p80211_hdr *hdr;
	/* used क्रम target specअगरic data, skb in Linux */
	व्योम *priv;
	/*-- fixed fields -----------*/
	u16 *auth_alg;
	u16 *auth_seq;
	u16 *status;
	/*-- info elements ----------*/
	काष्ठा wlan_ie_challenge *challenge;

पूर्ण;

/*-- Deauthenication -----------------------------*/
काष्ठा wlan_fr_deauthen अणु
	u16 type;
	u16 len;
	u8 *buf;
	जोड़ p80211_hdr *hdr;
	/* used क्रम target specअगरic data, skb in Linux */
	व्योम *priv;
	/*-- fixed fields -----------*/
	u16 *reason;

	/*-- info elements ----------*/

पूर्ण;

व्योम wlan_mgmt_encode_beacon(काष्ठा wlan_fr_beacon *f);
व्योम wlan_mgmt_decode_beacon(काष्ठा wlan_fr_beacon *f);
व्योम wlan_mgmt_encode_disassoc(काष्ठा wlan_fr_disassoc *f);
व्योम wlan_mgmt_decode_disassoc(काष्ठा wlan_fr_disassoc *f);
व्योम wlan_mgmt_encode_assocreq(काष्ठा wlan_fr_assocreq *f);
व्योम wlan_mgmt_decode_assocreq(काष्ठा wlan_fr_assocreq *f);
व्योम wlan_mgmt_encode_assocresp(काष्ठा wlan_fr_assocresp *f);
व्योम wlan_mgmt_decode_assocresp(काष्ठा wlan_fr_assocresp *f);
व्योम wlan_mgmt_encode_reassocreq(काष्ठा wlan_fr_reassocreq *f);
व्योम wlan_mgmt_decode_reassocreq(काष्ठा wlan_fr_reassocreq *f);
व्योम wlan_mgmt_encode_reassocresp(काष्ठा wlan_fr_reassocresp *f);
व्योम wlan_mgmt_decode_reassocresp(काष्ठा wlan_fr_reassocresp *f);
व्योम wlan_mgmt_encode_probereq(काष्ठा wlan_fr_probereq *f);
व्योम wlan_mgmt_decode_probereq(काष्ठा wlan_fr_probereq *f);
व्योम wlan_mgmt_encode_proberesp(काष्ठा wlan_fr_proberesp *f);
व्योम wlan_mgmt_decode_proberesp(काष्ठा wlan_fr_proberesp *f);
व्योम wlan_mgmt_encode_authen(काष्ठा wlan_fr_authen *f);
व्योम wlan_mgmt_decode_authen(काष्ठा wlan_fr_authen *f);
व्योम wlan_mgmt_encode_deauthen(काष्ठा wlan_fr_deauthen *f);
व्योम wlan_mgmt_decode_deauthen(काष्ठा wlan_fr_deauthen *f);

#पूर्ण_अगर /* _P80211MGMT_H */
