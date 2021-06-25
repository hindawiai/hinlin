<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1) */
/* p80211conv.h
 *
 * Ether/802.11 conversions and packet buffer routines
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
 * This file declares the functions, types and macros that perक्रमm
 * Ethernet to/from 802.11 frame conversions.
 *
 * --------------------------------------------------------------------
 */

#अगर_अघोषित _LINUX_P80211CONV_H
#घोषणा _LINUX_P80211CONV_H

#घोषणा WLAN_IEEE_OUI_LEN	3

#घोषणा WLAN_ETHCONV_ENCAP	1
#घोषणा WLAN_ETHCONV_8021h	3

#घोषणा P80211CAPTURE_VERSION	0x80211001

#घोषणा	P80211_FRMMETA_MAGIC	0x802110

काष्ठा p80211_rxmeta अणु
	काष्ठा wlandevice *wlandev;

	u64 maस_समय;		/* Hi-rez MAC-supplied समय value */
	u64 hostसमय;		/* Best-rez host supplied समय value */

	अचिन्हित पूर्णांक rxrate;	/* Receive data rate in 100kbps */
	अचिन्हित पूर्णांक priority;	/* 0-15, 0=contention, 6=CF */
	पूर्णांक संकेत;		/* An SSI, see p80211netdev.h */
	पूर्णांक noise;		/* An SSI, see p80211netdev.h */
	अचिन्हित पूर्णांक channel;	/* Receive channel (mostly क्रम snअगरs) */
	अचिन्हित पूर्णांक preamble;	/* P80211ENUM_preambletype_* */
	अचिन्हित पूर्णांक encoding;	/* P80211ENUM_encoding_* */

पूर्ण;

काष्ठा p80211_frmmeta अणु
	अचिन्हित पूर्णांक magic;
	काष्ठा p80211_rxmeta *rx;
पूर्ण;

व्योम p80211skb_मुक्त(काष्ठा wlandevice *wlandev, काष्ठा sk_buff *skb);
पूर्णांक p80211skb_rxmeta_attach(काष्ठा wlandevice *wlandev, काष्ठा sk_buff *skb);
व्योम p80211skb_rxmeta_detach(काष्ठा sk_buff *skb);

अटल अंतरभूत काष्ठा p80211_frmmeta *p80211skb_frmmeta(काष्ठा sk_buff *skb)
अणु
	काष्ठा p80211_frmmeta *frmmeta = (काष्ठा p80211_frmmeta *)skb->cb;

	वापस frmmeta->magic == P80211_FRMMETA_MAGIC ? frmmeta : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा p80211_rxmeta *p80211skb_rxmeta(काष्ठा sk_buff *skb)
अणु
	काष्ठा p80211_frmmeta *frmmeta = p80211skb_frmmeta(skb);

	वापस frmmeta ? frmmeta->rx : शून्य;
पूर्ण

/*
 * Frame capture header.  (See करोc/capturefrm.txt)
 */
काष्ठा p80211_caphdr अणु
	__be32 version;
	__be32 length;
	__be64 maस_समय;
	__be64 hostसमय;
	__be32 phytype;
	__be32 channel;
	__be32 datarate;
	__be32 antenna;
	__be32 priority;
	__be32 ssi_type;
	__be32 ssi_संकेत;
	__be32 ssi_noise;
	__be32 preamble;
	__be32 encoding;
पूर्ण;

काष्ठा p80211_metawep अणु
	व्योम *data;
	u8 iv[4];
	u8 icv[4];
पूर्ण;

/* local ether header type */
काष्ठा wlan_ethhdr अणु
	u8 daddr[ETH_ALEN];
	u8 saddr[ETH_ALEN];
	__be16 type;
पूर्ण __packed;

/* local llc header type */
काष्ठा wlan_llc अणु
	u8 dsap;
	u8 ssap;
	u8 ctl;
पूर्ण __packed;

/* local snap header type */
काष्ठा wlan_snap अणु
	u8 oui[WLAN_IEEE_OUI_LEN];
	__be16 type;
पूर्ण __packed;

/* Circular include trick */
काष्ठा wlandevice;

पूर्णांक skb_p80211_to_ether(काष्ठा wlandevice *wlandev, u32 ethconv,
			काष्ठा sk_buff *skb);
पूर्णांक skb_ether_to_p80211(काष्ठा wlandevice *wlandev, u32 ethconv,
			काष्ठा sk_buff *skb, जोड़ p80211_hdr *p80211_hdr,
			काष्ठा p80211_metawep *p80211_wep);

पूर्णांक p80211_stt_findproto(u16 proto);

#पूर्ण_अगर
