<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1) */
/* prism2mgmt.h
 *
 * Declares the mgmt command handler functions
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
 * This file contains the स्थिरants and data काष्ठाures क्रम पूर्णांकeraction
 * with the hfa384x Wireless LAN (WLAN) Media Access Controller (MAC).
 * The hfa384x is a portion of the Harris PRISM(पंचांग) WLAN chipset.
 *
 * [Implementation and usage notes]
 *
 * [References]
 *   CW10 Programmer's Manual v1.5
 *   IEEE 802.11 D10.0
 *
 *    --------------------------------------------------------------------
 */

#अगर_अघोषित _PRISM2MGMT_H
#घोषणा _PRISM2MGMT_H

बाह्य पूर्णांक prism2_reset_holdसमय;
बाह्य पूर्णांक prism2_reset_settleसमय;

u32 prism2sta_अगरstate(काष्ठा wlandevice *wlandev, u32 अगरstate);

व्योम prism2sta_ev_info(काष्ठा wlandevice *wlandev,
		       काष्ठा hfa384x_inf_frame *inf);
व्योम prism2sta_ev_txexc(काष्ठा wlandevice *wlandev, u16 status);
व्योम prism2sta_ev_tx(काष्ठा wlandevice *wlandev, u16 status);
व्योम prism2sta_ev_alloc(काष्ठा wlandevice *wlandev);

पूर्णांक prism2mgmt_mibset_mibget(काष्ठा wlandevice *wlandev, व्योम *msgp);
पूर्णांक prism2mgmt_scan(काष्ठा wlandevice *wlandev, व्योम *msgp);
पूर्णांक prism2mgmt_scan_results(काष्ठा wlandevice *wlandev, व्योम *msgp);
पूर्णांक prism2mgmt_start(काष्ठा wlandevice *wlandev, व्योम *msgp);
पूर्णांक prism2mgmt_wlansnअगरf(काष्ठा wlandevice *wlandev, व्योम *msgp);
पूर्णांक prism2mgmt_पढ़ोpda(काष्ठा wlandevice *wlandev, व्योम *msgp);
पूर्णांक prism2mgmt_ramdl_state(काष्ठा wlandevice *wlandev, व्योम *msgp);
पूर्णांक prism2mgmt_ramdl_ग_लिखो(काष्ठा wlandevice *wlandev, व्योम *msgp);
पूर्णांक prism2mgmt_flashdl_state(काष्ठा wlandevice *wlandev, व्योम *msgp);
पूर्णांक prism2mgmt_flashdl_ग_लिखो(काष्ठा wlandevice *wlandev, व्योम *msgp);
पूर्णांक prism2mgmt_स्वतःjoin(काष्ठा wlandevice *wlandev, व्योम *msgp);

/*---------------------------------------------------------------
 * conversion functions going between wlan message data types and
 * Prism2 data types
 *---------------------------------------------------------------
 */

/* byte area conversion functions*/
व्योम prism2mgmt_bytearea2pstr(u8 *bytearea, काष्ठा p80211pstrd *pstr, पूर्णांक len);

/* byte string conversion functions*/
व्योम prism2mgmt_pstr2bytestr(काष्ठा hfa384x_bytestr *bytestr,
			     काष्ठा p80211pstrd *pstr);
व्योम prism2mgmt_bytestr2pstr(काष्ठा hfa384x_bytestr *bytestr,
			     काष्ठा p80211pstrd *pstr);

/* functions to convert Group Addresses */
व्योम prism2mgmt_get_grpaddr(u32 did, काष्ठा p80211pstrd *pstr,
			    काष्ठा hfa384x *priv);
पूर्णांक prism2mgmt_set_grpaddr(u32 did,
			   u8 *prism2buf, काष्ठा p80211pstrd *pstr,
			   काष्ठा hfa384x *priv);
पूर्णांक prism2mgmt_get_grpaddr_index(u32 did);

व्योम prism2sta_processing_defer(काष्ठा work_काष्ठा *data);

व्योम prism2sta_commsqual_defer(काष्ठा work_काष्ठा *data);
व्योम prism2sta_commsqual_समयr(काष्ठा समयr_list *t);

/* Interface callback functions, passing data back up to the cfg80211 layer */
व्योम prism2_connect_result(काष्ठा wlandevice *wlandev, u8 failed);
व्योम prism2_disconnected(काष्ठा wlandevice *wlandev);
व्योम prism2_roamed(काष्ठा wlandevice *wlandev);

#पूर्ण_अगर
