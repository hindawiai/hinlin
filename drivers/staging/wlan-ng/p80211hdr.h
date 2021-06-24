<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1) */
/* p80211hdr.h
 *
 * Macros, types, and functions क्रम handling 802.11 MAC headers
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
 * Note:
 *  - Constant values are always in HOST byte order.  To assign
 *    values to multi-byte fields they _must_ be converted to
 *    ieee byte order.  To retrieve multi-byte values from incoming
 *    frames, they must be converted to host order.
 *
 * All functions declared here are implemented in p80211.c
 * --------------------------------------------------------------------
 */

#अगर_अघोषित _P80211HDR_H
#घोषणा _P80211HDR_H

#समावेश <linux/अगर_ether.h>

/*--- Sizes -----------------------------------------------*/
#घोषणा WLAN_CRC_LEN			4
#घोषणा WLAN_BSSID_LEN			6
#घोषणा WLAN_HDR_A3_LEN			24
#घोषणा WLAN_HDR_A4_LEN			30
#घोषणा WLAN_SSID_MAXLEN		32
#घोषणा WLAN_DATA_MAXLEN		2312
#घोषणा WLAN_WEP_IV_LEN			4
#घोषणा WLAN_WEP_ICV_LEN		4

/*--- Frame Control Field -------------------------------------*/
/* Frame Types */
#घोषणा WLAN_FTYPE_MGMT			0x00
#घोषणा WLAN_FTYPE_CTL			0x01
#घोषणा WLAN_FTYPE_DATA			0x02

/* Frame subtypes */
/* Management */
#घोषणा WLAN_FSTYPE_ASSOCREQ		0x00
#घोषणा WLAN_FSTYPE_ASSOCRESP		0x01
#घोषणा WLAN_FSTYPE_REASSOCREQ		0x02
#घोषणा WLAN_FSTYPE_REASSOCRESP		0x03
#घोषणा WLAN_FSTYPE_PROBEREQ		0x04
#घोषणा WLAN_FSTYPE_PROBERESP		0x05
#घोषणा WLAN_FSTYPE_BEACON		0x08
#घोषणा WLAN_FSTYPE_ATIM		0x09
#घोषणा WLAN_FSTYPE_DISASSOC		0x0a
#घोषणा WLAN_FSTYPE_AUTHEN		0x0b
#घोषणा WLAN_FSTYPE_DEAUTHEN		0x0c

/* Control */
#घोषणा WLAN_FSTYPE_BLOCKACKREQ		0x8
#घोषणा WLAN_FSTYPE_BLOCKACK		0x9
#घोषणा WLAN_FSTYPE_PSPOLL		0x0a
#घोषणा WLAN_FSTYPE_RTS			0x0b
#घोषणा WLAN_FSTYPE_CTS			0x0c
#घोषणा WLAN_FSTYPE_ACK			0x0d
#घोषणा WLAN_FSTYPE_CFEND		0x0e
#घोषणा WLAN_FSTYPE_CFENDCFACK		0x0f

/* Data */
#घोषणा WLAN_FSTYPE_DATAONLY		0x00
#घोषणा WLAN_FSTYPE_DATA_CFACK		0x01
#घोषणा WLAN_FSTYPE_DATA_CFPOLL		0x02
#घोषणा WLAN_FSTYPE_DATA_CFACK_CFPOLL	0x03
#घोषणा WLAN_FSTYPE_शून्य		0x04
#घोषणा WLAN_FSTYPE_CFACK		0x05
#घोषणा WLAN_FSTYPE_CFPOLL		0x06
#घोषणा WLAN_FSTYPE_CFACK_CFPOLL	0x07

/*--- FC Macros ----------------------------------------------*/
/* Macros to get/set the bitfields of the Frame Control Field */
/*  GET_FC_??? - takes the host byte-order value of an FC     */
/*               and retrieves the value of one of the        */
/*               bitfields and moves that value so its lsb is */
/*               in bit 0.                                    */
/*  SET_FC_??? - takes a host order value क्रम one of the FC   */
/*               bitfields and moves it to the proper bit     */
/*               location क्रम ORing पूर्णांकo a host order FC.     */
/*               To send the FC produced from SET_FC_???,     */
/*               one must put the bytes in IEEE order.        */
/*  e.g.                                                      */
/*     म_लिखो("the frame subtype is %x",                      */
/*                 GET_FC_FTYPE( ieee2host( rx.fc )))         */
/*                                                            */
/*     tx.fc = host2ieee( SET_FC_FTYPE(WLAN_FTYP_CTL) |       */
/*                        SET_FC_FSTYPE(WLAN_FSTYPE_RTS) );   */
/*------------------------------------------------------------*/

#घोषणा WLAN_GET_FC_FTYPE(n)	((((u16)(n)) & GENMASK(3, 2)) >> 2)
#घोषणा WLAN_GET_FC_FSTYPE(n)	((((u16)(n)) & GENMASK(7, 4)) >> 4)
#घोषणा WLAN_GET_FC_TODS(n)	((((u16)(n)) & (BIT(8))) >> 8)
#घोषणा WLAN_GET_FC_FROMDS(n)	((((u16)(n)) & (BIT(9))) >> 9)
#घोषणा WLAN_GET_FC_ISWEP(n)	((((u16)(n)) & (BIT(14))) >> 14)

#घोषणा WLAN_SET_FC_FTYPE(n)	(((u16)(n)) << 2)
#घोषणा WLAN_SET_FC_FSTYPE(n)	(((u16)(n)) << 4)
#घोषणा WLAN_SET_FC_TODS(n)	(((u16)(n)) << 8)
#घोषणा WLAN_SET_FC_FROMDS(n)	(((u16)(n)) << 9)
#घोषणा WLAN_SET_FC_ISWEP(n)	(((u16)(n)) << 14)

#घोषणा DOT11_RATE5_ISBASIC_GET(r)     (((u8)(r)) & BIT(7))

/* Generic 802.11 Header types */

काष्ठा p80211_hdr_a3 अणु
	__le16 fc;
	u16 dur;
	u8 a1[ETH_ALEN];
	u8 a2[ETH_ALEN];
	u8 a3[ETH_ALEN];
	u16 seq;
पूर्ण __packed;

काष्ठा p80211_hdr_a4 अणु
	u16 fc;
	u16 dur;
	u8 a1[ETH_ALEN];
	u8 a2[ETH_ALEN];
	u8 a3[ETH_ALEN];
	u16 seq;
	u8 a4[ETH_ALEN];
पूर्ण __packed;

जोड़ p80211_hdr अणु
	काष्ठा p80211_hdr_a3 a3;
	काष्ठा p80211_hdr_a4 a4;
पूर्ण __packed;

/* Frame and header length macros */

अटल अंतरभूत u16 wlan_ctl_framelen(u16 fstype)
अणु
	चयन (fstype)	अणु
	हाल WLAN_FSTYPE_BLOCKACKREQ:
		वापस 24;
	हाल WLAN_FSTYPE_BLOCKACK:
		वापस 152;
	हाल WLAN_FSTYPE_PSPOLL:
	हाल WLAN_FSTYPE_RTS:
	हाल WLAN_FSTYPE_CFEND:
	हाल WLAN_FSTYPE_CFENDCFACK:
		वापस 20;
	हाल WLAN_FSTYPE_CTS:
	हाल WLAN_FSTYPE_ACK:
		वापस 14;
	शेष:
		वापस 4;
	पूर्ण
पूर्ण

#घोषणा WLAN_FCS_LEN			4

/* ftcl in HOST order */
अटल अंतरभूत u16 p80211_headerlen(u16 fctl)
अणु
	u16 hdrlen = 0;

	चयन (WLAN_GET_FC_FTYPE(fctl)) अणु
	हाल WLAN_FTYPE_MGMT:
		hdrlen = WLAN_HDR_A3_LEN;
		अवरोध;
	हाल WLAN_FTYPE_DATA:
		hdrlen = WLAN_HDR_A3_LEN;
		अगर (WLAN_GET_FC_TODS(fctl) && WLAN_GET_FC_FROMDS(fctl))
			hdrlen += ETH_ALEN;
		अवरोध;
	हाल WLAN_FTYPE_CTL:
		hdrlen = wlan_ctl_framelen(WLAN_GET_FC_FSTYPE(fctl)) -
		    WLAN_FCS_LEN;
		अवरोध;
	शेष:
		hdrlen = WLAN_HDR_A3_LEN;
	पूर्ण

	वापस hdrlen;
पूर्ण

#पूर्ण_अगर /* _P80211HDR_H */
