<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1)
/* src/p80211/p80211req.c
 *
 * Request/Indication/MacMgmt पूर्णांकerface handling functions
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
 * This file contains the functions, types, and macros to support the
 * MLME request पूर्णांकerface that's implemented via the device ioctls.
 *
 * --------------------------------------------------------------------
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/wireless.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/sock.h>
#समावेश <linux/netlink.h>

#समावेश "p80211types.h"
#समावेश "p80211hdr.h"
#समावेश "p80211mgmt.h"
#समावेश "p80211conv.h"
#समावेश "p80211msg.h"
#समावेश "p80211netdev.h"
#समावेश "p80211ioctl.h"
#समावेश "p80211metadef.h"
#समावेश "p80211metastruct.h"
#समावेश "p80211req.h"

अटल व्योम p80211req_handlemsg(काष्ठा wlandevice *wlandev,
				काष्ठा p80211msg *msg);
अटल व्योम p80211req_mibset_mibget(काष्ठा wlandevice *wlandev,
				    काष्ठा p80211msg_करोt11req_mibget *mib_msg,
				    पूर्णांक isget);

अटल व्योम p80211req_handle_action(काष्ठा wlandevice *wlandev, u32 *data,
				    पूर्णांक isget, u32 flag)
अणु
	अगर (isget) अणु
		अगर (wlandev->hostwep & flag)
			*data = P80211ENUM_truth_true;
		अन्यथा
			*data = P80211ENUM_truth_false;
	पूर्ण अन्यथा अणु
		wlandev->hostwep &= ~flag;
		अगर (*data == P80211ENUM_truth_true)
			wlandev->hostwep |= flag;
	पूर्ण
पूर्ण

/*----------------------------------------------------------------
 * p80211req_करोrequest
 *
 * Handles an MLME request/confirm message.
 *
 * Arguments:
 *	wlandev		WLAN device काष्ठा
 *	msgbuf		Buffer containing a request message
 *
 * Returns:
 *	0 on success, an त्रुटि_सं otherwise
 *
 * Call context:
 *	Potentially blocks the caller, so it's a good idea to
 *	not call this function from an पूर्णांकerrupt context.
 *----------------------------------------------------------------
 */
पूर्णांक p80211req_करोrequest(काष्ठा wlandevice *wlandev, u8 *msgbuf)
अणु
	काष्ठा p80211msg *msg = (काष्ठा p80211msg *)msgbuf;

	/* Check to make sure the MSD is running */
	अगर (!((wlandev->msdstate == WLAN_MSD_HWPRESENT &&
	       msg->msgcode == DIDMSG_LNXREQ_IFSTATE) ||
	      wlandev->msdstate == WLAN_MSD_RUNNING ||
	      wlandev->msdstate == WLAN_MSD_FWLOAD)) अणु
		वापस -ENODEV;
	पूर्ण

	/* Check Permissions */
	अगर (!capable(CAP_NET_ADMIN) &&
	    (msg->msgcode != DIDMSG_DOT11REQ_MIBGET)) अणु
		netdev_err(wlandev->netdev,
			   "%s: only dot11req_mibget allowed for non-root.\n",
			   wlandev->name);
		वापस -EPERM;
	पूर्ण

	/* Check क्रम busy status */
	अगर (test_and_set_bit(1, &wlandev->request_pending))
		वापस -EBUSY;

	/* Allow p80211 to look at msg and handle अगर desired. */
	/* So far, all p80211 msgs are immediate, no रुकोq/समयr necessary */
	/* This may change. */
	p80211req_handlemsg(wlandev, msg);

	/* Pass it करोwn to wlandev via wlandev->mlmerequest */
	अगर (wlandev->mlmerequest)
		wlandev->mlmerequest(wlandev, msg);

	clear_bit(1, &wlandev->request_pending);
	वापस 0;	/* अगर result==0, msg->status still may contain an err */
पूर्ण

/*----------------------------------------------------------------
 * p80211req_handlemsg
 *
 * p80211 message handler.  Primarily looks क्रम messages that
 * beदीर्घ to p80211 and then dispatches the appropriate response.
 * TODO: we करोn't करो anything yet.  Once the linuxMIB is better
 *	defined we'll need a get/set handler.
 *
 * Arguments:
 *	wlandev		WLAN device काष्ठा
 *	msg		message काष्ठाure
 *
 * Returns:
 *	nothing (any results are set in the status field of the msg)
 *
 * Call context:
 *	Process thपढ़ो
 *----------------------------------------------------------------
 */
अटल व्योम p80211req_handlemsg(काष्ठा wlandevice *wlandev,
				काष्ठा p80211msg *msg)
अणु
	चयन (msg->msgcode) अणु
	हाल DIDMSG_LNXREQ_HOSTWEP: अणु
		काष्ठा p80211msg_lnxreq_hostwep *req =
			(काष्ठा p80211msg_lnxreq_hostwep *)msg;
		wlandev->hostwep &=
				~(HOSTWEP_DECRYPT | HOSTWEP_ENCRYPT);
		अगर (req->decrypt.data == P80211ENUM_truth_true)
			wlandev->hostwep |= HOSTWEP_DECRYPT;
		अगर (req->encrypt.data == P80211ENUM_truth_true)
			wlandev->hostwep |= HOSTWEP_ENCRYPT;

		अवरोध;
	पूर्ण
	हाल DIDMSG_DOT11REQ_MIBGET:
	हाल DIDMSG_DOT11REQ_MIBSET: अणु
		पूर्णांक isget = (msg->msgcode == DIDMSG_DOT11REQ_MIBGET);
		काष्ठा p80211msg_करोt11req_mibget *mib_msg =
			(काष्ठा p80211msg_करोt11req_mibget *)msg;
		p80211req_mibset_mibget(wlandev, mib_msg, isget);
		अवरोध;
	पूर्ण
	पूर्ण			/* चयन msg->msgcode */
पूर्ण

अटल व्योम p80211req_mibset_mibget(काष्ठा wlandevice *wlandev,
				    काष्ठा p80211msg_करोt11req_mibget *mib_msg,
				    पूर्णांक isget)
अणु
	काष्ठा p80211itemd *mibitem =
		(काष्ठा p80211itemd *)mib_msg->mibattribute.data;
	काष्ठा p80211pstrd *pstr = (काष्ठा p80211pstrd *)mibitem->data;
	u8 *key = mibitem->data + माप(काष्ठा p80211pstrd);

	चयन (mibitem->did) अणु
	हाल didmib_करोt11smt_wepशेषkeystable_key(1):
	हाल didmib_करोt11smt_wepशेषkeystable_key(2):
	हाल didmib_करोt11smt_wepशेषkeystable_key(3):
	हाल didmib_करोt11smt_wepशेषkeystable_key(4):
		अगर (!isget)
			wep_change_key(wlandev,
				       P80211DID_ITEM(mibitem->did) - 1,
				       key, pstr->len);
		अवरोध;

	हाल DIDMIB_DOT11SMT_PRIVACYTABLE_WEPDEFAULTKEYID: अणु
		u32 *data = (u32 *)mibitem->data;

		अगर (isget) अणु
			*data = wlandev->hostwep & HOSTWEP_DEFAULTKEY_MASK;
		पूर्ण अन्यथा अणु
			wlandev->hostwep &= ~(HOSTWEP_DEFAULTKEY_MASK);
			wlandev->hostwep |= (*data & HOSTWEP_DEFAULTKEY_MASK);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल DIDMIB_DOT11SMT_PRIVACYTABLE_PRIVACYINVOKED: अणु
		u32 *data = (u32 *)mibitem->data;

		p80211req_handle_action(wlandev, data, isget,
					HOSTWEP_PRIVACYINVOKED);
		अवरोध;
	पूर्ण
	हाल DIDMIB_DOT11SMT_PRIVACYTABLE_EXCLUDEUNENCRYPTED: अणु
		u32 *data = (u32 *)mibitem->data;

		p80211req_handle_action(wlandev, data, isget,
					HOSTWEP_EXCLUDEUNENCRYPTED);
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण
