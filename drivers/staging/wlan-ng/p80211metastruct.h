<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1) */
/* --------------------------------------------------------------------
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
 */

#अगर_अघोषित _P80211MKMETASTRUCT_H
#घोषणा _P80211MKMETASTRUCT_H

काष्ठा p80211msg_करोt11req_mibget अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_unk392 mibattribute;
	काष्ठा p80211item_uपूर्णांक32 resultcode;
पूर्ण __packed;

काष्ठा p80211msg_करोt11req_mibset अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_unk392 mibattribute;
	काष्ठा p80211item_uपूर्णांक32 resultcode;
पूर्ण __packed;

काष्ठा p80211msg_करोt11req_scan अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_uपूर्णांक32 bsstype;
	काष्ठा p80211item_pstr6 bssid;
	u8 pad_0C[1];
	काष्ठा p80211item_pstr32 ssid;
	u8 pad_1D[3];
	काष्ठा p80211item_uपूर्णांक32 scantype;
	काष्ठा p80211item_uपूर्णांक32 probedelay;
	काष्ठा p80211item_pstr14 channellist;
	u8 pad_2C[1];
	काष्ठा p80211item_uपूर्णांक32 minchannelसमय;
	काष्ठा p80211item_uपूर्णांक32 maxchannelसमय;
	काष्ठा p80211item_uपूर्णांक32 resultcode;
	काष्ठा p80211item_uपूर्णांक32 numbss;
	काष्ठा p80211item_uपूर्णांक32 append;
पूर्ण __packed;

काष्ठा p80211msg_करोt11req_scan_results अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_uपूर्णांक32 bssindex;
	काष्ठा p80211item_uपूर्णांक32 resultcode;
	काष्ठा p80211item_uपूर्णांक32 संकेत;
	काष्ठा p80211item_uपूर्णांक32 noise;
	काष्ठा p80211item_pstr6 bssid;
	u8 pad_3C[1];
	काष्ठा p80211item_pstr32 ssid;
	u8 pad_4D[3];
	काष्ठा p80211item_uपूर्णांक32 bsstype;
	काष्ठा p80211item_uपूर्णांक32 beaconperiod;
	काष्ठा p80211item_uपूर्णांक32 dtimperiod;
	काष्ठा p80211item_uपूर्णांक32 बारtamp;
	काष्ठा p80211item_uपूर्णांक32 स_स्थानीय;
	काष्ठा p80211item_uपूर्णांक32 fhdwellसमय;
	काष्ठा p80211item_uपूर्णांक32 fhhopset;
	काष्ठा p80211item_uपूर्णांक32 fhhoppattern;
	काष्ठा p80211item_uपूर्णांक32 fhhopindex;
	काष्ठा p80211item_uपूर्णांक32 dschannel;
	काष्ठा p80211item_uपूर्णांक32 cfpcount;
	काष्ठा p80211item_uपूर्णांक32 cfpperiod;
	काष्ठा p80211item_uपूर्णांक32 cfpmaxduration;
	काष्ठा p80211item_uपूर्णांक32 cfpdurreमुख्यing;
	काष्ठा p80211item_uपूर्णांक32 ibssatimwinकरोw;
	काष्ठा p80211item_uपूर्णांक32 cfpollable;
	काष्ठा p80211item_uपूर्णांक32 cfpollreq;
	काष्ठा p80211item_uपूर्णांक32 privacy;
	काष्ठा p80211item_uपूर्णांक32 capinfo;
	काष्ठा p80211item_uपूर्णांक32 basicrate1;
	काष्ठा p80211item_uपूर्णांक32 basicrate2;
	काष्ठा p80211item_uपूर्णांक32 basicrate3;
	काष्ठा p80211item_uपूर्णांक32 basicrate4;
	काष्ठा p80211item_uपूर्णांक32 basicrate5;
	काष्ठा p80211item_uपूर्णांक32 basicrate6;
	काष्ठा p80211item_uपूर्णांक32 basicrate7;
	काष्ठा p80211item_uपूर्णांक32 basicrate8;
	काष्ठा p80211item_uपूर्णांक32 supprate1;
	काष्ठा p80211item_uपूर्णांक32 supprate2;
	काष्ठा p80211item_uपूर्णांक32 supprate3;
	काष्ठा p80211item_uपूर्णांक32 supprate4;
	काष्ठा p80211item_uपूर्णांक32 supprate5;
	काष्ठा p80211item_uपूर्णांक32 supprate6;
	काष्ठा p80211item_uपूर्णांक32 supprate7;
	काष्ठा p80211item_uपूर्णांक32 supprate8;
पूर्ण __packed;

काष्ठा p80211msg_करोt11req_start अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_pstr32 ssid;
	u8 pad_12D[3];
	काष्ठा p80211item_uपूर्णांक32 bsstype;
	काष्ठा p80211item_uपूर्णांक32 beaconperiod;
	काष्ठा p80211item_uपूर्णांक32 dtimperiod;
	काष्ठा p80211item_uपूर्णांक32 cfpperiod;
	काष्ठा p80211item_uपूर्णांक32 cfpmaxduration;
	काष्ठा p80211item_uपूर्णांक32 fhdwellसमय;
	काष्ठा p80211item_uपूर्णांक32 fhhopset;
	काष्ठा p80211item_uपूर्णांक32 fhhoppattern;
	काष्ठा p80211item_uपूर्णांक32 dschannel;
	काष्ठा p80211item_uपूर्णांक32 ibssatimwinकरोw;
	काष्ठा p80211item_uपूर्णांक32 probedelay;
	काष्ठा p80211item_uपूर्णांक32 cfpollable;
	काष्ठा p80211item_uपूर्णांक32 cfpollreq;
	काष्ठा p80211item_uपूर्णांक32 basicrate1;
	काष्ठा p80211item_uपूर्णांक32 basicrate2;
	काष्ठा p80211item_uपूर्णांक32 basicrate3;
	काष्ठा p80211item_uपूर्णांक32 basicrate4;
	काष्ठा p80211item_uपूर्णांक32 basicrate5;
	काष्ठा p80211item_uपूर्णांक32 basicrate6;
	काष्ठा p80211item_uपूर्णांक32 basicrate7;
	काष्ठा p80211item_uपूर्णांक32 basicrate8;
	काष्ठा p80211item_uपूर्णांक32 operationalrate1;
	काष्ठा p80211item_uपूर्णांक32 operationalrate2;
	काष्ठा p80211item_uपूर्णांक32 operationalrate3;
	काष्ठा p80211item_uपूर्णांक32 operationalrate4;
	काष्ठा p80211item_uपूर्णांक32 operationalrate5;
	काष्ठा p80211item_uपूर्णांक32 operationalrate6;
	काष्ठा p80211item_uपूर्णांक32 operationalrate7;
	काष्ठा p80211item_uपूर्णांक32 operationalrate8;
	काष्ठा p80211item_uपूर्णांक32 resultcode;
पूर्ण __packed;

काष्ठा p80211msg_lnxreq_अगरstate अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_uपूर्णांक32 अगरstate;
	काष्ठा p80211item_uपूर्णांक32 resultcode;
पूर्ण __packed;

काष्ठा p80211msg_lnxreq_wlansnअगरf अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_uपूर्णांक32 enable;
	काष्ठा p80211item_uपूर्णांक32 channel;
	काष्ठा p80211item_uपूर्णांक32 prismheader;
	काष्ठा p80211item_uपूर्णांक32 wlanheader;
	काष्ठा p80211item_uपूर्णांक32 keepwepflags;
	काष्ठा p80211item_uपूर्णांक32 stripfcs;
	काष्ठा p80211item_uपूर्णांक32 packet_trunc;
	काष्ठा p80211item_uपूर्णांक32 resultcode;
पूर्ण __packed;

काष्ठा p80211msg_lnxreq_hostwep अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_uपूर्णांक32 resultcode;
	काष्ठा p80211item_uपूर्णांक32 decrypt;
	काष्ठा p80211item_uपूर्णांक32 encrypt;
पूर्ण __packed;

काष्ठा p80211msg_lnxreq_commsquality अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_uपूर्णांक32 resultcode;
	काष्ठा p80211item_uपूर्णांक32 dbm;
	काष्ठा p80211item_uपूर्णांक32 link;
	काष्ठा p80211item_uपूर्णांक32 level;
	काष्ठा p80211item_uपूर्णांक32 noise;
	काष्ठा p80211item_uपूर्णांक32 txrate;
पूर्ण __packed;

काष्ठा p80211msg_lnxreq_स्वतःjoin अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_pstr32 ssid;
	u8 pad_19D[3];
	काष्ठा p80211item_uपूर्णांक32 authtype;
	काष्ठा p80211item_uपूर्णांक32 resultcode;
पूर्ण __packed;

काष्ठा p80211msg_p2req_पढ़ोpda अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_unk1024 pda;
	काष्ठा p80211item_uपूर्णांक32 resultcode;
पूर्ण __packed;

काष्ठा p80211msg_p2req_ramdl_state अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_uपूर्णांक32 enable;
	काष्ठा p80211item_uपूर्णांक32 exeaddr;
	काष्ठा p80211item_uपूर्णांक32 resultcode;
पूर्ण __packed;

काष्ठा p80211msg_p2req_ramdl_ग_लिखो अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_uपूर्णांक32 addr;
	काष्ठा p80211item_uपूर्णांक32 len;
	काष्ठा p80211item_unk4096 data;
	काष्ठा p80211item_uपूर्णांक32 resultcode;
पूर्ण __packed;

काष्ठा p80211msg_p2req_flashdl_state अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_uपूर्णांक32 enable;
	काष्ठा p80211item_uपूर्णांक32 resultcode;
पूर्ण __packed;

काष्ठा p80211msg_p2req_flashdl_ग_लिखो अणु
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
	काष्ठा p80211item_uपूर्णांक32 addr;
	काष्ठा p80211item_uपूर्णांक32 len;
	काष्ठा p80211item_unk4096 data;
	काष्ठा p80211item_uपूर्णांक32 resultcode;
पूर्ण __packed;

#पूर्ण_अगर
