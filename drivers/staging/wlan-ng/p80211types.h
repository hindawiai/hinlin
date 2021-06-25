<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1) */
/*
 * p80211types.h
 *
 * Macros, स्थिरants, types, and funcs क्रम p80211 data types
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
 * This file declares some of the स्थिरants and types used in various
 * parts of the linux-wlan प्रणाली.
 *
 * Notes:
 *   - Constant values are always in HOST byte order.
 *
 * All functions and अटलs declared here are implemented in p80211types.c
 *   --------------------------------------------------------------------
 */

#अगर_अघोषित _P80211TYPES_H
#घोषणा _P80211TYPES_H

/*----------------------------------------------------------------*/
/* The following स्थिरants are indexes पूर्णांकo the Mib Category List */
/* and the Message Category List */

/* Mib Category List */
#घोषणा P80211_MIB_CAT_DOT11SMT		1
#घोषणा P80211_MIB_CAT_DOT11MAC		2
#घोषणा P80211_MIB_CAT_DOT11PHY		3

#घोषणा P80211SEC_DOT11SMT		P80211_MIB_CAT_DOT11SMT
#घोषणा P80211SEC_DOT11MAC		P80211_MIB_CAT_DOT11MAC
#घोषणा P80211SEC_DOT11PHY		P80211_MIB_CAT_DOT11PHY

/* Message Category List */
#घोषणा P80211_MSG_CAT_DOT11REQ		1
#घोषणा P80211_MSG_CAT_DOT11IND		2

/*----------------------------------------------------------------*/
/* p80211 क्रमागतeration स्थिरants.  The value to text mappings क्रम */
/*  these is in p80211types.c.  These defines were generated */
/*  from the mappings. */

/* error codes क्रम lookups */

#घोषणा P80211ENUM_truth_false			0
#घोषणा P80211ENUM_truth_true			1
#घोषणा P80211ENUM_अगरstate_disable		0
#घोषणा P80211ENUM_अगरstate_fwload		1
#घोषणा P80211ENUM_अगरstate_enable		2
#घोषणा P80211ENUM_bsstype_infraकाष्ठाure	1
#घोषणा P80211ENUM_bsstype_independent		2
#घोषणा P80211ENUM_bsstype_any			3
#घोषणा P80211ENUM_authalg_खोलोप्रणाली		1
#घोषणा P80211ENUM_authalg_sharedkey		2
#घोषणा P80211ENUM_scantype_active		1
#घोषणा P80211ENUM_resultcode_success		1
#घोषणा P80211ENUM_resultcode_invalid_parameters	2
#घोषणा P80211ENUM_resultcode_not_supported	3
#घोषणा P80211ENUM_resultcode_refused		6
#घोषणा P80211ENUM_resultcode_cant_set_पढ़ोonly_mib	10
#घोषणा P80211ENUM_resultcode_implementation_failure	11
#घोषणा P80211ENUM_resultcode_cant_get_ग_लिखोonly_mib	12
#घोषणा P80211ENUM_status_successful		0
#घोषणा P80211ENUM_status_unspec_failure	1
#घोषणा P80211ENUM_status_ap_full		17
#घोषणा P80211ENUM_msgitem_status_data_ok		0
#घोषणा P80211ENUM_msgitem_status_no_value		1

/*----------------------------------------------------------------*/
/* p80211 max length स्थिरants क्रम the dअगरferent pascal strings. */

#घोषणा MAXLEN_PSTR6		(6)	/* pascal array of 6 bytes */
#घोषणा MAXLEN_PSTR14		(14)	/* pascal array of 14 bytes */
#घोषणा MAXLEN_PSTR32		(32)	/* pascal array of 32 bytes */
#घोषणा MAXLEN_PSTR255		(255)	/* pascal array of 255 bytes */
#घोषणा MAXLEN_MIBATTRIBUTE	(392)	/* maximum mibattribute */
					/* where the size of the DATA itself */
					/* is a DID-LEN-DATA triple */
					/* with a max size of 4+4+384 */

/*----------------------------------------------------------------
 * The following स्थिरants and macros are used to स्थिरruct and
 * deस्थिरruct the Data ID codes.  The coding is as follows:
 *
 *     ...rwtnnnnnnnniiiiiiggggggssssss      s - Section
 *                                           g - Group
 *                                           i - Item
 *                                           n - Index
 *                                           t - Table flag
 *                                           w - Write flag
 *                                           r - Read flag
 *                                           . - Unused
 */

#घोषणा P80211DID_LSB_SECTION		(0)
#घोषणा P80211DID_LSB_GROUP		(6)
#घोषणा P80211DID_LSB_ITEM		(12)
#घोषणा P80211DID_LSB_INDEX		(18)
#घोषणा P80211DID_LSB_ISTABLE		(26)
#घोषणा P80211DID_LSB_ACCESS		(27)

#घोषणा P80211DID_MASK_SECTION		(0x0000003fUL)
#घोषणा P80211DID_MASK_GROUP		(0x0000003fUL)
#घोषणा P80211DID_MASK_ITEM		(0x0000003fUL)
#घोषणा P80211DID_MASK_INDEX		(0x000000ffUL)
#घोषणा P80211DID_MASK_ISTABLE		(0x00000001UL)
#घोषणा P80211DID_MASK_ACCESS		(0x00000003UL)

#घोषणा P80211DID_MK(a, m, l)	((((u32)(a)) & (m)) << (l))

#घोषणा P80211DID_MKSECTION(a)	P80211DID_MK(a, \
					P80211DID_MASK_SECTION, \
					P80211DID_LSB_SECTION)
#घोषणा P80211DID_MKGROUP(a)	P80211DID_MK(a, \
					P80211DID_MASK_GROUP, \
					P80211DID_LSB_GROUP)
#घोषणा P80211DID_MKITEM(a)	P80211DID_MK(a, \
					P80211DID_MASK_ITEM, \
					P80211DID_LSB_ITEM)
#घोषणा P80211DID_MKINDEX(a)	P80211DID_MK(a, \
					P80211DID_MASK_INDEX, \
					P80211DID_LSB_INDEX)
#घोषणा P80211DID_MKISTABLE(a)	P80211DID_MK(a, \
					P80211DID_MASK_ISTABLE, \
					P80211DID_LSB_ISTABLE)

#घोषणा P80211DID_MKID(s, g, i, n, t, a)	(P80211DID_MKSECTION(s) | \
					P80211DID_MKGROUP(g) | \
					P80211DID_MKITEM(i) | \
					P80211DID_MKINDEX(n) | \
					P80211DID_MKISTABLE(t) | \
					(a))

#घोषणा P80211DID_GET(a, m, l)	((((u32)(a)) >> (l)) & (m))

#घोषणा P80211DID_SECTION(a)	P80211DID_GET(a, \
					P80211DID_MASK_SECTION, \
					P80211DID_LSB_SECTION)
#घोषणा P80211DID_GROUP(a)	P80211DID_GET(a, \
					P80211DID_MASK_GROUP, \
					P80211DID_LSB_GROUP)
#घोषणा P80211DID_ITEM(a)	P80211DID_GET(a, \
					P80211DID_MASK_ITEM, \
					P80211DID_LSB_ITEM)
#घोषणा P80211DID_INDEX(a)	P80211DID_GET(a, \
					P80211DID_MASK_INDEX, \
					P80211DID_LSB_INDEX)
#घोषणा P80211DID_ISTABLE(a)	P80211DID_GET(a, \
					P80211DID_MASK_ISTABLE, \
					P80211DID_LSB_ISTABLE)
#घोषणा P80211DID_ACCESS(a)	P80211DID_GET(a, \
					P80211DID_MASK_ACCESS, \
					P80211DID_LSB_ACCESS)

/*----------------------------------------------------------------*/
/* The following काष्ठाure types are used to store data items in */
/*  messages. */

/* Template pascal string */
काष्ठा p80211pstr अणु
	u8 len;
पूर्ण __packed;

काष्ठा p80211pstrd अणु
	u8 len;
	u8 data[];
पूर्ण __packed;

/* Maximum pascal string */
काष्ठा p80211pstr255 अणु
	u8 len;
	u8 data[MAXLEN_PSTR255];
पूर्ण __packed;

/* pascal string क्रम macaddress and bssid */
काष्ठा p80211pstr6 अणु
	u8 len;
	u8 data[MAXLEN_PSTR6];
पूर्ण __packed;

/* pascal string क्रम channel list */
काष्ठा p80211pstr14 अणु
	u8 len;
	u8 data[MAXLEN_PSTR14];
पूर्ण __packed;

/* pascal string क्रम ssid */
काष्ठा p80211pstr32 अणु
	u8 len;
	u8 data[MAXLEN_PSTR32];
पूर्ण __packed;

/* MAC address array */
काष्ठा p80211macarray अणु
	u32 cnt;
	u8 data[1][MAXLEN_PSTR6];
पूर्ण __packed;

/* prototype ढाँचा */
काष्ठा p80211item अणु
	u32 did;
	u16 status;
	u16 len;
पूर्ण __packed;

/* prototype ढाँचा w/ data item */
काष्ठा p80211itemd अणु
	u32 did;
	u16 status;
	u16 len;
	u8 data[];
पूर्ण __packed;

/* message data item क्रम पूर्णांक, BOUNDEDINT, ENUMINT */
काष्ठा p80211item_uपूर्णांक32 अणु
	u32 did;
	u16 status;
	u16 len;
	u32 data;
पूर्ण __packed;

/* message data item क्रम OCTETSTR, DISPLAYSTR */
काष्ठा p80211item_pstr6 अणु
	u32 did;
	u16 status;
	u16 len;
	काष्ठा p80211pstr6 data;
पूर्ण __packed;

/* message data item क्रम OCTETSTR, DISPLAYSTR */
काष्ठा p80211item_pstr14 अणु
	u32 did;
	u16 status;
	u16 len;
	काष्ठा p80211pstr14 data;
पूर्ण __packed;

/* message data item क्रम OCTETSTR, DISPLAYSTR */
काष्ठा p80211item_pstr32 अणु
	u32 did;
	u16 status;
	u16 len;
	काष्ठा p80211pstr32 data;
पूर्ण __packed;

/* message data item क्रम OCTETSTR, DISPLAYSTR */
काष्ठा p80211item_pstr255 अणु
	u32 did;
	u16 status;
	u16 len;
	काष्ठा p80211pstr255 data;
पूर्ण __packed;

/* message data item क्रम UNK 392, namely mib items */
काष्ठा p80211item_unk392 अणु
	u32 did;
	u16 status;
	u16 len;
	u8 data[MAXLEN_MIBATTRIBUTE];
पूर्ण __packed;

/* message data item क्रम UNK 1025, namely p2 pdas */
काष्ठा p80211item_unk1024 अणु
	u32 did;
	u16 status;
	u16 len;
	u8 data[1024];
पूर्ण __packed;

/* message data item क्रम UNK 4096, namely p2 करोwnload chunks */
काष्ठा p80211item_unk4096 अणु
	u32 did;
	u16 status;
	u16 len;
	u8 data[4096];
पूर्ण __packed;

#पूर्ण_अगर /* _P80211TYPES_H */
