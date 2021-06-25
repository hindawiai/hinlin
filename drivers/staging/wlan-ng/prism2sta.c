<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1)
/* src/prism2/driver/prism2sta.c
 *
 * Implements the station functionality क्रम prism2
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
 * This file implements the module and linux pcmcia routines क्रम the
 * prism2 driver.
 *
 * --------------------------------------------------------------------
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/wireless.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/etherdevice.h>

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/bitops.h>

#समावेश "p80211types.h"
#समावेश "p80211hdr.h"
#समावेश "p80211mgmt.h"
#समावेश "p80211conv.h"
#समावेश "p80211msg.h"
#समावेश "p80211netdev.h"
#समावेश "p80211req.h"
#समावेश "p80211metadef.h"
#समावेश "p80211metastruct.h"
#समावेश "hfa384x.h"
#समावेश "prism2mgmt.h"

अटल अक्षर *dev_info = "prism2_usb";
अटल काष्ठा wlandevice *create_wlan(व्योम);

पूर्णांक prism2_reset_holdसमय = 30;	/* Reset hold समय in ms */
पूर्णांक prism2_reset_settleसमय = 100;	/* Reset settle समय in ms */

अटल पूर्णांक prism2_करोreset;	/* Do a reset at init? */

module_param(prism2_करोreset, पूर्णांक, 0644);
MODULE_PARM_DESC(prism2_करोreset, "Issue a reset on initialization");

module_param(prism2_reset_holdसमय, पूर्णांक, 0644);
MODULE_PARM_DESC(prism2_reset_holdसमय, "reset hold time in ms");
module_param(prism2_reset_settleसमय, पूर्णांक, 0644);
MODULE_PARM_DESC(prism2_reset_settleसमय, "reset settle time in ms");

MODULE_LICENSE("Dual MPL/GPL");

अटल पूर्णांक prism2sta_खोलो(काष्ठा wlandevice *wlandev);
अटल पूर्णांक prism2sta_बंद(काष्ठा wlandevice *wlandev);
अटल व्योम prism2sta_reset(काष्ठा wlandevice *wlandev);
अटल पूर्णांक prism2sta_txframe(काष्ठा wlandevice *wlandev, काष्ठा sk_buff *skb,
			     जोड़ p80211_hdr *p80211_hdr,
			     काष्ठा p80211_metawep *p80211_wep);
अटल पूर्णांक prism2sta_mlmerequest(काष्ठा wlandevice *wlandev,
				 काष्ठा p80211msg *msg);
अटल पूर्णांक prism2sta_अ_लोardinfo(काष्ठा wlandevice *wlandev);
अटल पूर्णांक prism2sta_globalsetup(काष्ठा wlandevice *wlandev);
अटल पूर्णांक prism2sta_seपंचांगulticast(काष्ठा wlandevice *wlandev,
				  काष्ठा net_device *dev);

अटल व्योम prism2sta_inf_hanकरोver(काष्ठा wlandevice *wlandev,
				   काष्ठा hfa384x_inf_frame *inf);
अटल व्योम prism2sta_inf_tallies(काष्ठा wlandevice *wlandev,
				  काष्ठा hfa384x_inf_frame *inf);
अटल व्योम prism2sta_inf_hostscanresults(काष्ठा wlandevice *wlandev,
					  काष्ठा hfa384x_inf_frame *inf);
अटल व्योम prism2sta_inf_scanresults(काष्ठा wlandevice *wlandev,
				      काष्ठा hfa384x_inf_frame *inf);
अटल व्योम prism2sta_inf_chinक्रमesults(काष्ठा wlandevice *wlandev,
					काष्ठा hfa384x_inf_frame *inf);
अटल व्योम prism2sta_inf_linkstatus(काष्ठा wlandevice *wlandev,
				     काष्ठा hfa384x_inf_frame *inf);
अटल व्योम prism2sta_inf_assocstatus(काष्ठा wlandevice *wlandev,
				      काष्ठा hfa384x_inf_frame *inf);
अटल व्योम prism2sta_inf_authreq(काष्ठा wlandevice *wlandev,
				  काष्ठा hfa384x_inf_frame *inf);
अटल व्योम prism2sta_inf_authreq_defer(काष्ठा wlandevice *wlandev,
					काष्ठा hfa384x_inf_frame *inf);
अटल व्योम prism2sta_inf_psusercnt(काष्ठा wlandevice *wlandev,
				    काष्ठा hfa384x_inf_frame *inf);

/*
 * prism2sta_खोलो
 *
 * WLAN device खोलो method.  Called from p80211netdev when kernel
 * device खोलो (start) method is called in response to the
 * SIOCSIIFFLAGS ioctl changing the flags bit IFF_UP
 * from clear to set.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *
 * Returns:
 *	0	success
 *	>0	f/w reported error
 *	<0	driver reported error
 *
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो
 */
अटल पूर्णांक prism2sta_खोलो(काष्ठा wlandevice *wlandev)
अणु
	/* We करोn't currently have to करो anything अन्यथा.
	 * The setup of the MAC should be subsequently completed via
	 * the mlme commands.
	 * Higher layers know we're पढ़ोy from dev->start==1 and
	 * dev->tbusy==0.  Our rx path knows to pass up received/
	 * frames because of dev->flags&IFF_UP is true.
	 */

	वापस 0;
पूर्ण

/*
 * prism2sta_बंद
 *
 * WLAN device बंद method.  Called from p80211netdev when kernel
 * device बंद method is called in response to the
 * SIOCSIIFFLAGS ioctl changing the flags bit IFF_UP
 * from set to clear.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *
 * Returns:
 *	0	success
 *	>0	f/w reported error
 *	<0	driver reported error
 *
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो
 */
अटल पूर्णांक prism2sta_बंद(काष्ठा wlandevice *wlandev)
अणु
	/* We करोn't currently have to करो anything अन्यथा.
	 * Higher layers know we're not पढ़ोy from dev->start==0 and
	 * dev->tbusy==1.  Our rx path knows to not pass up received
	 * frames because of dev->flags&IFF_UP is false.
	 */

	वापस 0;
पूर्ण

/*
 * prism2sta_reset
 *
 * Currently not implemented.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	none
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो
 */
अटल व्योम prism2sta_reset(काष्ठा wlandevice *wlandev)
अणु
पूर्ण

/*
 * prism2sta_txframe
 *
 * Takes a frame from p80211 and queues it क्रम transmission.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	pb		packet buffer काष्ठा.  Contains an 802.11
 *			data frame.
 *       p80211_hdr      poपूर्णांकs to the 802.11 header क्रम the packet.
 * Returns:
 *	0		Success and more buffs available
 *	1		Success but no more buffs
 *	2		Allocation failure
 *	4		Buffer full or queue busy
 *
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो
 */
अटल पूर्णांक prism2sta_txframe(काष्ठा wlandevice *wlandev, काष्ठा sk_buff *skb,
			     जोड़ p80211_hdr *p80211_hdr,
			     काष्ठा p80211_metawep *p80211_wep)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;

	/* If necessary, set the 802.11 WEP bit */
	अगर ((wlandev->hostwep & (HOSTWEP_PRIVACYINVOKED | HOSTWEP_ENCRYPT)) ==
	    HOSTWEP_PRIVACYINVOKED) अणु
		p80211_hdr->a3.fc |= cpu_to_le16(WLAN_SET_FC_ISWEP(1));
	पूर्ण

	वापस hfa384x_drvr_txframe(hw, skb, p80211_hdr, p80211_wep);
पूर्ण

/*
 * prism2sta_mlmerequest
 *
 * wlan command message handler.  All we करो here is pass the message
 * over to the prism2sta_mgmt_handler.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	msg		wlan command message
 * Returns:
 *	0		success
 *	<0		successful acceptance of message, but we're
 *			रुकोing क्रम an async process to finish beक्रमe
 *			we're करोne with the msg.  When the asynch
 *			process is करोne, we'll call the p80211
 *			function p80211req_confirm() .
 *	>0		An error occurred जबतक we were handling
 *			the message.
 *
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो
 */
अटल पूर्णांक prism2sta_mlmerequest(काष्ठा wlandevice *wlandev,
				 काष्ठा p80211msg *msg)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;

	पूर्णांक result = 0;

	चयन (msg->msgcode) अणु
	हाल DIDMSG_DOT11REQ_MIBGET:
		pr_debug("Received mibget request\n");
		result = prism2mgmt_mibset_mibget(wlandev, msg);
		अवरोध;
	हाल DIDMSG_DOT11REQ_MIBSET:
		pr_debug("Received mibset request\n");
		result = prism2mgmt_mibset_mibget(wlandev, msg);
		अवरोध;
	हाल DIDMSG_DOT11REQ_SCAN:
		pr_debug("Received scan request\n");
		result = prism2mgmt_scan(wlandev, msg);
		अवरोध;
	हाल DIDMSG_DOT11REQ_SCAN_RESULTS:
		pr_debug("Received scan_results request\n");
		result = prism2mgmt_scan_results(wlandev, msg);
		अवरोध;
	हाल DIDMSG_DOT11REQ_START:
		pr_debug("Received mlme start request\n");
		result = prism2mgmt_start(wlandev, msg);
		अवरोध;
		/*
		 * Prism2 specअगरic messages
		 */
	हाल DIDMSG_P2REQ_READPDA:
		pr_debug("Received mlme readpda request\n");
		result = prism2mgmt_पढ़ोpda(wlandev, msg);
		अवरोध;
	हाल DIDMSG_P2REQ_RAMDL_STATE:
		pr_debug("Received mlme ramdl_state request\n");
		result = prism2mgmt_ramdl_state(wlandev, msg);
		अवरोध;
	हाल DIDMSG_P2REQ_RAMDL_WRITE:
		pr_debug("Received mlme ramdl_write request\n");
		result = prism2mgmt_ramdl_ग_लिखो(wlandev, msg);
		अवरोध;
	हाल DIDMSG_P2REQ_FLASHDL_STATE:
		pr_debug("Received mlme flashdl_state request\n");
		result = prism2mgmt_flashdl_state(wlandev, msg);
		अवरोध;
	हाल DIDMSG_P2REQ_FLASHDL_WRITE:
		pr_debug("Received mlme flashdl_write request\n");
		result = prism2mgmt_flashdl_ग_लिखो(wlandev, msg);
		अवरोध;
		/*
		 * Linux specअगरic messages
		 */
	हाल DIDMSG_LNXREQ_HOSTWEP:
		अवरोध;		/* ignore me. */
	हाल DIDMSG_LNXREQ_IFSTATE: अणु
		काष्ठा p80211msg_lnxreq_अगरstate *अगरstatemsg;

		pr_debug("Received mlme ifstate request\n");
		अगरstatemsg = (काष्ठा p80211msg_lnxreq_अगरstate *)msg;
		result = prism2sta_अगरstate(wlandev,
					   अगरstatemsg->अगरstate.data);
		अगरstatemsg->resultcode.status =
			P80211ENUM_msgitem_status_data_ok;
		अगरstatemsg->resultcode.data = result;
		result = 0;
		अवरोध;
	पूर्ण
	हाल DIDMSG_LNXREQ_WLANSNIFF:
		pr_debug("Received mlme wlansniff request\n");
		result = prism2mgmt_wlansnअगरf(wlandev, msg);
		अवरोध;
	हाल DIDMSG_LNXREQ_AUTOJOIN:
		pr_debug("Received mlme autojoin request\n");
		result = prism2mgmt_स्वतःjoin(wlandev, msg);
		अवरोध;
	हाल DIDMSG_LNXREQ_COMMSQUALITY: अणु
		काष्ठा p80211msg_lnxreq_commsquality *qualmsg;

		pr_debug("Received commsquality request\n");

		qualmsg = (काष्ठा p80211msg_lnxreq_commsquality *)msg;

		qualmsg->link.status = P80211ENUM_msgitem_status_data_ok;
		qualmsg->level.status = P80211ENUM_msgitem_status_data_ok;
		qualmsg->noise.status = P80211ENUM_msgitem_status_data_ok;

		qualmsg->link.data = le16_to_cpu(hw->qual.cq_curr_bss);
		qualmsg->level.data = le16_to_cpu(hw->qual.asl_curr_bss);
		qualmsg->noise.data = le16_to_cpu(hw->qual.anl_curr_fc);
		qualmsg->txrate.data = hw->txrate;

		अवरोध;
	पूर्ण
	शेष:
		netdev_warn(wlandev->netdev,
			    "Unknown mgmt request message 0x%08x",
			    msg->msgcode);
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

/*
 * prism2sta_अगरstate
 *
 * Interface state.  This is the primary WLAN पूर्णांकerface enable/disable
 * handler.  Following the driver/load/deviceprobe sequence, this
 * function must be called with a state of "enable" beक्रमe any other
 * commands will be accepted.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	msgp		ptr to msg buffer
 *
 * Returns:
 *	A p80211 message resultcode value.
 *
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो  (usually)
 *	पूर्णांकerrupt
 */
u32 prism2sta_अगरstate(काष्ठा wlandevice *wlandev, u32 अगरstate)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	u32 result;

	result = P80211ENUM_resultcode_implementation_failure;

	pr_debug("Current MSD state(%d), requesting(%d)\n",
		 wlandev->msdstate, अगरstate);
	चयन (अगरstate) अणु
	हाल P80211ENUM_अगरstate_fwload:
		चयन (wlandev->msdstate) अणु
		हाल WLAN_MSD_HWPRESENT:
			wlandev->msdstate = WLAN_MSD_FWLOAD_PENDING;
			/*
			 * Initialize the device+driver sufficiently
			 * क्रम firmware loading.
			 */
			result = hfa384x_drvr_start(hw);
			अगर (result) अणु
				netdev_err(wlandev->netdev,
					   "hfa384x_drvr_start() failed,result=%d\n",
					   (पूर्णांक)result);
				result =
				 P80211ENUM_resultcode_implementation_failure;
				wlandev->msdstate = WLAN_MSD_HWPRESENT;
				अवरोध;
			पूर्ण
			wlandev->msdstate = WLAN_MSD_FWLOAD;
			result = P80211ENUM_resultcode_success;
			अवरोध;
		हाल WLAN_MSD_FWLOAD:
			hfa384x_cmd_initialize(hw);
			result = P80211ENUM_resultcode_success;
			अवरोध;
		हाल WLAN_MSD_RUNNING:
			netdev_warn(wlandev->netdev,
				    "Cannot enter fwload state from enable state, you must disable first.\n");
			result = P80211ENUM_resultcode_invalid_parameters;
			अवरोध;
		हाल WLAN_MSD_HWFAIL:
		शेष:
			/* probe() had a problem or the msdstate contains
			 * an unrecognized value, there's nothing we can करो.
			 */
			result = P80211ENUM_resultcode_implementation_failure;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल P80211ENUM_अगरstate_enable:
		चयन (wlandev->msdstate) अणु
		हाल WLAN_MSD_HWPRESENT:
		हाल WLAN_MSD_FWLOAD:
			wlandev->msdstate = WLAN_MSD_RUNNING_PENDING;
			/* Initialize the device+driver क्रम full
			 * operation. Note that this might me an FWLOAD
			 * to RUNNING transition so we must not करो a chip
			 * or board level reset.  Note that on failure,
			 * the MSD state is set to HWPRESENT because we
			 * can't make any assumptions about the state
			 * of the hardware or a previous firmware load.
			 */
			result = hfa384x_drvr_start(hw);
			अगर (result) अणु
				netdev_err(wlandev->netdev,
					   "hfa384x_drvr_start() failed,result=%d\n",
					   (पूर्णांक)result);
				result =
				  P80211ENUM_resultcode_implementation_failure;
				wlandev->msdstate = WLAN_MSD_HWPRESENT;
				अवरोध;
			पूर्ण

			result = prism2sta_अ_लोardinfo(wlandev);
			अगर (result) अणु
				netdev_err(wlandev->netdev,
					   "prism2sta_getcardinfo() failed,result=%d\n",
					   (पूर्णांक)result);
				result =
				  P80211ENUM_resultcode_implementation_failure;
				hfa384x_drvr_stop(hw);
				wlandev->msdstate = WLAN_MSD_HWPRESENT;
				अवरोध;
			पूर्ण
			result = prism2sta_globalsetup(wlandev);
			अगर (result) अणु
				netdev_err(wlandev->netdev,
					   "prism2sta_globalsetup() failed,result=%d\n",
					   (पूर्णांक)result);
				result =
				  P80211ENUM_resultcode_implementation_failure;
				hfa384x_drvr_stop(hw);
				wlandev->msdstate = WLAN_MSD_HWPRESENT;
				अवरोध;
			पूर्ण
			wlandev->msdstate = WLAN_MSD_RUNNING;
			hw->join_ap = 0;
			hw->join_retries = 60;
			result = P80211ENUM_resultcode_success;
			अवरोध;
		हाल WLAN_MSD_RUNNING:
			/* Do nothing, we're alपढ़ोy in this state. */
			result = P80211ENUM_resultcode_success;
			अवरोध;
		हाल WLAN_MSD_HWFAIL:
		शेष:
			/* probe() had a problem or the msdstate contains
			 * an unrecognized value, there's nothing we can करो.
			 */
			result = P80211ENUM_resultcode_implementation_failure;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल P80211ENUM_अगरstate_disable:
		चयन (wlandev->msdstate) अणु
		हाल WLAN_MSD_HWPRESENT:
			/* Do nothing, we're alपढ़ोy in this state. */
			result = P80211ENUM_resultcode_success;
			अवरोध;
		हाल WLAN_MSD_FWLOAD:
		हाल WLAN_MSD_RUNNING:
			wlandev->msdstate = WLAN_MSD_HWPRESENT_PENDING;
			/*
			 * TODO: Shut करोwn the MAC completely. Here a chip
			 * or board level reset is probably called क्रम.
			 * After a "disable" _all_ results are lost, even
			 * those from a fwload.
			 */
			अगर (!wlandev->hwहटाओd)
				netअगर_carrier_off(wlandev->netdev);

			hfa384x_drvr_stop(hw);

			wlandev->macmode = WLAN_MACMODE_NONE;
			wlandev->msdstate = WLAN_MSD_HWPRESENT;
			result = P80211ENUM_resultcode_success;
			अवरोध;
		हाल WLAN_MSD_HWFAIL:
		शेष:
			/* probe() had a problem or the msdstate contains
			 * an unrecognized value, there's nothing we can करो.
			 */
			result = P80211ENUM_resultcode_implementation_failure;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		result = P80211ENUM_resultcode_invalid_parameters;
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

/*
 * prism2sta_अ_लोardinfo
 *
 * Collect the NICID, firmware version and any other identअगरiers
 * we'd like to have in host-side data काष्ठाures.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *
 * Returns:
 *	0	success
 *	>0	f/w reported error
 *	<0	driver reported error
 *
 * Side effects:
 *
 * Call context:
 *	Either.
 */
अटल पूर्णांक prism2sta_अ_लोardinfo(काष्ठा wlandevice *wlandev)
अणु
	पूर्णांक result = 0;
	काष्ठा hfa384x *hw = wlandev->priv;
	u16 temp;
	u8 snum[HFA384x_RID_NICSERIALNUMBER_LEN];

	/* Collect version and compatibility info */
	/*  Some are critical, some are not */
	/* NIC identity */
	result = hfa384x_drvr_अ_लोonfig(hw, HFA384x_RID_NICIDENTITY,
					&hw->ident_nic,
					माप(काष्ठा hfa384x_compident));
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to retrieve NICIDENTITY\n");
		जाओ failed;
	पूर्ण

	/* get all the nic id fields in host byte order */
	le16_to_cpus(&hw->ident_nic.id);
	le16_to_cpus(&hw->ident_nic.variant);
	le16_to_cpus(&hw->ident_nic.major);
	le16_to_cpus(&hw->ident_nic.minor);

	netdev_info(wlandev->netdev, "ident: nic h/w: id=0x%02x %d.%d.%d\n",
		    hw->ident_nic.id, hw->ident_nic.major,
		    hw->ident_nic.minor, hw->ident_nic.variant);

	/* Primary f/w identity */
	result = hfa384x_drvr_अ_लोonfig(hw, HFA384x_RID_PRIIDENTITY,
					&hw->ident_pri_fw,
					माप(काष्ठा hfa384x_compident));
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to retrieve PRIIDENTITY\n");
		जाओ failed;
	पूर्ण

	/* get all the निजी fw id fields in host byte order */
	le16_to_cpus(&hw->ident_pri_fw.id);
	le16_to_cpus(&hw->ident_pri_fw.variant);
	le16_to_cpus(&hw->ident_pri_fw.major);
	le16_to_cpus(&hw->ident_pri_fw.minor);

	netdev_info(wlandev->netdev, "ident: pri f/w: id=0x%02x %d.%d.%d\n",
		    hw->ident_pri_fw.id, hw->ident_pri_fw.major,
		    hw->ident_pri_fw.minor, hw->ident_pri_fw.variant);

	/* Station (Secondary?) f/w identity */
	result = hfa384x_drvr_अ_लोonfig(hw, HFA384x_RID_STAIDENTITY,
					&hw->ident_sta_fw,
					माप(काष्ठा hfa384x_compident));
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to retrieve STAIDENTITY\n");
		जाओ failed;
	पूर्ण

	अगर (hw->ident_nic.id < 0x8000) अणु
		netdev_err(wlandev->netdev,
			   "FATAL: Card is not an Intersil Prism2/2.5/3\n");
		result = -1;
		जाओ failed;
	पूर्ण

	/* get all the station fw id fields in host byte order */
	le16_to_cpus(&hw->ident_sta_fw.id);
	le16_to_cpus(&hw->ident_sta_fw.variant);
	le16_to_cpus(&hw->ident_sta_fw.major);
	le16_to_cpus(&hw->ident_sta_fw.minor);

	/* strip out the 'special' variant bits */
	hw->mm_mods = hw->ident_sta_fw.variant & GENMASK(15, 14);
	hw->ident_sta_fw.variant &= ~((u16)GENMASK(15, 14));

	अगर (hw->ident_sta_fw.id == 0x1f) अणु
		netdev_info(wlandev->netdev,
			    "ident: sta f/w: id=0x%02x %d.%d.%d\n",
			    hw->ident_sta_fw.id, hw->ident_sta_fw.major,
			    hw->ident_sta_fw.minor, hw->ident_sta_fw.variant);
	पूर्ण अन्यथा अणु
		netdev_info(wlandev->netdev,
			    "ident:  ap f/w: id=0x%02x %d.%d.%d\n",
			    hw->ident_sta_fw.id, hw->ident_sta_fw.major,
			    hw->ident_sta_fw.minor, hw->ident_sta_fw.variant);
		netdev_err(wlandev->netdev, "Unsupported Tertiary AP firmware loaded!\n");
		जाओ failed;
	पूर्ण

	/* Compatibility range, Modem supplier */
	result = hfa384x_drvr_अ_लोonfig(hw, HFA384x_RID_MFISUPRANGE,
					&hw->cap_sup_mfi,
					माप(काष्ठा hfa384x_caplevel));
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to retrieve MFISUPRANGE\n");
		जाओ failed;
	पूर्ण

	/* get all the Compatibility range, modem पूर्णांकerface supplier
	 * fields in byte order
	 */
	le16_to_cpus(&hw->cap_sup_mfi.role);
	le16_to_cpus(&hw->cap_sup_mfi.id);
	le16_to_cpus(&hw->cap_sup_mfi.variant);
	le16_to_cpus(&hw->cap_sup_mfi.bottom);
	le16_to_cpus(&hw->cap_sup_mfi.top);

	netdev_info(wlandev->netdev,
		    "MFI:SUP:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
		    hw->cap_sup_mfi.role, hw->cap_sup_mfi.id,
		    hw->cap_sup_mfi.variant, hw->cap_sup_mfi.bottom,
		    hw->cap_sup_mfi.top);

	/* Compatibility range, Controller supplier */
	result = hfa384x_drvr_अ_लोonfig(hw, HFA384x_RID_CFISUPRANGE,
					&hw->cap_sup_cfi,
					माप(काष्ठा hfa384x_caplevel));
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to retrieve CFISUPRANGE\n");
		जाओ failed;
	पूर्ण

	/* get all the Compatibility range, controller पूर्णांकerface supplier
	 * fields in byte order
	 */
	le16_to_cpus(&hw->cap_sup_cfi.role);
	le16_to_cpus(&hw->cap_sup_cfi.id);
	le16_to_cpus(&hw->cap_sup_cfi.variant);
	le16_to_cpus(&hw->cap_sup_cfi.bottom);
	le16_to_cpus(&hw->cap_sup_cfi.top);

	netdev_info(wlandev->netdev,
		    "CFI:SUP:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
		    hw->cap_sup_cfi.role, hw->cap_sup_cfi.id,
		    hw->cap_sup_cfi.variant, hw->cap_sup_cfi.bottom,
		    hw->cap_sup_cfi.top);

	/* Compatibility range, Primary f/w supplier */
	result = hfa384x_drvr_अ_लोonfig(hw, HFA384x_RID_PRISUPRANGE,
					&hw->cap_sup_pri,
					माप(काष्ठा hfa384x_caplevel));
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to retrieve PRISUPRANGE\n");
		जाओ failed;
	पूर्ण

	/* get all the Compatibility range, primary firmware supplier
	 * fields in byte order
	 */
	le16_to_cpus(&hw->cap_sup_pri.role);
	le16_to_cpus(&hw->cap_sup_pri.id);
	le16_to_cpus(&hw->cap_sup_pri.variant);
	le16_to_cpus(&hw->cap_sup_pri.bottom);
	le16_to_cpus(&hw->cap_sup_pri.top);

	netdev_info(wlandev->netdev,
		    "PRI:SUP:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
		    hw->cap_sup_pri.role, hw->cap_sup_pri.id,
		    hw->cap_sup_pri.variant, hw->cap_sup_pri.bottom,
		    hw->cap_sup_pri.top);

	/* Compatibility range, Station f/w supplier */
	result = hfa384x_drvr_अ_लोonfig(hw, HFA384x_RID_STASUPRANGE,
					&hw->cap_sup_sta,
					माप(काष्ठा hfa384x_caplevel));
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to retrieve STASUPRANGE\n");
		जाओ failed;
	पूर्ण

	/* get all the Compatibility range, station firmware supplier
	 * fields in byte order
	 */
	le16_to_cpus(&hw->cap_sup_sta.role);
	le16_to_cpus(&hw->cap_sup_sta.id);
	le16_to_cpus(&hw->cap_sup_sta.variant);
	le16_to_cpus(&hw->cap_sup_sta.bottom);
	le16_to_cpus(&hw->cap_sup_sta.top);

	अगर (hw->cap_sup_sta.id == 0x04) अणु
		netdev_info(wlandev->netdev,
			    "STA:SUP:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
			    hw->cap_sup_sta.role, hw->cap_sup_sta.id,
			    hw->cap_sup_sta.variant, hw->cap_sup_sta.bottom,
			    hw->cap_sup_sta.top);
	पूर्ण अन्यथा अणु
		netdev_info(wlandev->netdev,
			    "AP:SUP:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
			    hw->cap_sup_sta.role, hw->cap_sup_sta.id,
			    hw->cap_sup_sta.variant, hw->cap_sup_sta.bottom,
			    hw->cap_sup_sta.top);
	पूर्ण

	/* Compatibility range, primary f/w actor, CFI supplier */
	result = hfa384x_drvr_अ_लोonfig(hw, HFA384x_RID_PRI_CFIACTRANGES,
					&hw->cap_act_pri_cfi,
					माप(काष्ठा hfa384x_caplevel));
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to retrieve PRI_CFIACTRANGES\n");
		जाओ failed;
	पूर्ण

	/* get all the Compatibility range, primary f/w actor, CFI supplier
	 * fields in byte order
	 */
	le16_to_cpus(&hw->cap_act_pri_cfi.role);
	le16_to_cpus(&hw->cap_act_pri_cfi.id);
	le16_to_cpus(&hw->cap_act_pri_cfi.variant);
	le16_to_cpus(&hw->cap_act_pri_cfi.bottom);
	le16_to_cpus(&hw->cap_act_pri_cfi.top);

	netdev_info(wlandev->netdev,
		    "PRI-CFI:ACT:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
		    hw->cap_act_pri_cfi.role, hw->cap_act_pri_cfi.id,
		    hw->cap_act_pri_cfi.variant, hw->cap_act_pri_cfi.bottom,
		    hw->cap_act_pri_cfi.top);

	/* Compatibility range, sta f/w actor, CFI supplier */
	result = hfa384x_drvr_अ_लोonfig(hw, HFA384x_RID_STA_CFIACTRANGES,
					&hw->cap_act_sta_cfi,
					माप(काष्ठा hfa384x_caplevel));
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to retrieve STA_CFIACTRANGES\n");
		जाओ failed;
	पूर्ण

	/* get all the Compatibility range, station f/w actor, CFI supplier
	 * fields in byte order
	 */
	le16_to_cpus(&hw->cap_act_sta_cfi.role);
	le16_to_cpus(&hw->cap_act_sta_cfi.id);
	le16_to_cpus(&hw->cap_act_sta_cfi.variant);
	le16_to_cpus(&hw->cap_act_sta_cfi.bottom);
	le16_to_cpus(&hw->cap_act_sta_cfi.top);

	netdev_info(wlandev->netdev,
		    "STA-CFI:ACT:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
		    hw->cap_act_sta_cfi.role, hw->cap_act_sta_cfi.id,
		    hw->cap_act_sta_cfi.variant, hw->cap_act_sta_cfi.bottom,
		    hw->cap_act_sta_cfi.top);

	/* Compatibility range, sta f/w actor, MFI supplier */
	result = hfa384x_drvr_अ_लोonfig(hw, HFA384x_RID_STA_MFIACTRANGES,
					&hw->cap_act_sta_mfi,
					माप(काष्ठा hfa384x_caplevel));
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to retrieve STA_MFIACTRANGES\n");
		जाओ failed;
	पूर्ण

	/* get all the Compatibility range, station f/w actor, MFI supplier
	 * fields in byte order
	 */
	le16_to_cpus(&hw->cap_act_sta_mfi.role);
	le16_to_cpus(&hw->cap_act_sta_mfi.id);
	le16_to_cpus(&hw->cap_act_sta_mfi.variant);
	le16_to_cpus(&hw->cap_act_sta_mfi.bottom);
	le16_to_cpus(&hw->cap_act_sta_mfi.top);

	netdev_info(wlandev->netdev,
		    "STA-MFI:ACT:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
		    hw->cap_act_sta_mfi.role, hw->cap_act_sta_mfi.id,
		    hw->cap_act_sta_mfi.variant, hw->cap_act_sta_mfi.bottom,
		    hw->cap_act_sta_mfi.top);

	/* Serial Number */
	result = hfa384x_drvr_अ_लोonfig(hw, HFA384x_RID_NICSERIALNUMBER,
					snum, HFA384x_RID_NICSERIALNUMBER_LEN);
	अगर (!result) अणु
		netdev_info(wlandev->netdev, "Prism2 card SN: %*pE\n",
			    HFA384x_RID_NICSERIALNUMBER_LEN, snum);
	पूर्ण अन्यथा अणु
		netdev_err(wlandev->netdev, "Failed to retrieve Prism2 Card SN\n");
		जाओ failed;
	पूर्ण

	/* Collect the MAC address */
	result = hfa384x_drvr_अ_लोonfig(hw, HFA384x_RID_CNFOWNMACADDR,
					wlandev->netdev->dev_addr, ETH_ALEN);
	अगर (result != 0) अणु
		netdev_err(wlandev->netdev, "Failed to retrieve mac address\n");
		जाओ failed;
	पूर्ण

	/* लघु preamble is always implemented */
	wlandev->nsdcaps |= P80211_NSDCAP_SHORT_PREAMBLE;

	/* find out अगर hardware wep is implemented */
	hfa384x_drvr_अ_लोonfig16(hw, HFA384x_RID_PRIVACYOPTIMP, &temp);
	अगर (temp)
		wlandev->nsdcaps |= P80211_NSDCAP_HARDWAREWEP;

	/* get the dBm Scaling स्थिरant */
	hfa384x_drvr_अ_लोonfig16(hw, HFA384x_RID_CNFDBMADJUST, &temp);
	hw->dbmadjust = temp;

	/* Only enable scan by शेष on newer firmware */
	अगर (HFA384x_FIRMWARE_VERSION(hw->ident_sta_fw.major,
				     hw->ident_sta_fw.minor,
				     hw->ident_sta_fw.variant) <
	    HFA384x_FIRMWARE_VERSION(1, 5, 5)) अणु
		wlandev->nsdcaps |= P80211_NSDCAP_NOSCAN;
	पूर्ण

	/* TODO: Set any पूर्णांकernally managed config items */

	जाओ करोne;
failed:
	netdev_err(wlandev->netdev, "Failed, result=%d\n", result);
करोne:
	वापस result;
पूर्ण

/*
 * prism2sta_globalsetup
 *
 * Set any global RIDs that we want to set at device activation.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *
 * Returns:
 *	0	success
 *	>0	f/w reported error
 *	<0	driver reported error
 *
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो
 */
अटल पूर्णांक prism2sta_globalsetup(काष्ठा wlandevice *wlandev)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;

	/* Set the maximum frame size */
	वापस hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFMAXDATALEN,
					WLAN_DATA_MAXLEN);
पूर्ण

अटल पूर्णांक prism2sta_seपंचांगulticast(काष्ठा wlandevice *wlandev,
				  काष्ठा net_device *dev)
अणु
	पूर्णांक result = 0;
	काष्ठा hfa384x *hw = wlandev->priv;

	u16 promisc;

	/* If we're not ready, what's the poपूर्णांक? */
	अगर (hw->state != HFA384x_STATE_RUNNING)
		जाओ निकास;

	अगर ((dev->flags & (IFF_PROMISC | IFF_ALLMULTI)) != 0)
		promisc = P80211ENUM_truth_true;
	अन्यथा
		promisc = P80211ENUM_truth_false;

	result =
	    hfa384x_drvr_setconfig16_async(hw, HFA384x_RID_PROMISCMODE,
					   promisc);
निकास:
	वापस result;
पूर्ण

/*
 * prism2sta_inf_hanकरोver
 *
 * Handles the receipt of a Hanकरोver info frame. Should only be present
 * in APs only.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	inf		ptr to info frame (contents in hfa384x order)
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 */
अटल व्योम prism2sta_inf_hanकरोver(काष्ठा wlandevice *wlandev,
				   काष्ठा hfa384x_inf_frame *inf)
अणु
	pr_debug("received infoframe:HANDOVER (unhandled)\n");
पूर्ण

/*
 * prism2sta_inf_tallies
 *
 * Handles the receipt of a CommTallies info frame.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	inf		ptr to info frame (contents in hfa384x order)
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 */
अटल व्योम prism2sta_inf_tallies(काष्ठा wlandevice *wlandev,
				  काष्ठा hfa384x_inf_frame *inf)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	__le16 *src16;
	u32 *dst;
	__le32 *src32;
	पूर्णांक i;
	पूर्णांक cnt;

	/*
	 * Determine अगर these are 16-bit or 32-bit tallies, based on the
	 * record length of the info record.
	 */

	cnt = माप(काष्ठा hfa384x_comm_tallies_32) / माप(u32);
	अगर (inf->framelen > 22) अणु
		dst = (u32 *)&hw->tallies;
		src32 = (__le32 *)&inf->info.commtallies32;
		क्रम (i = 0; i < cnt; i++, dst++, src32++)
			*dst += le32_to_cpu(*src32);
	पूर्ण अन्यथा अणु
		dst = (u32 *)&hw->tallies;
		src16 = (__le16 *)&inf->info.commtallies16;
		क्रम (i = 0; i < cnt; i++, dst++, src16++)
			*dst += le16_to_cpu(*src16);
	पूर्ण
पूर्ण

/*
 * prism2sta_inf_scanresults
 *
 * Handles the receipt of a Scan Results info frame.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	inf		ptr to info frame (contents in hfa384x order)
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 */
अटल व्योम prism2sta_inf_scanresults(काष्ठा wlandevice *wlandev,
				      काष्ठा hfa384x_inf_frame *inf)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	पूर्णांक nbss;
	काष्ठा hfa384x_scan_result *sr = &inf->info.scanresult;
	पूर्णांक i;
	काष्ठा hfa384x_join_request_data joinreq;
	पूर्णांक result;

	/* Get the number of results, first in bytes, then in results */
	nbss = (inf->framelen * माप(u16)) -
	    माप(inf->infotype) - माप(inf->info.scanresult.scanreason);
	nbss /= माप(काष्ठा hfa384x_scan_result_sub);

	/* Prपूर्णांक em */
	pr_debug("rx scanresults, reason=%d, nbss=%d:\n",
		 inf->info.scanresult.scanreason, nbss);
	क्रम (i = 0; i < nbss; i++) अणु
		pr_debug("chid=%d anl=%d sl=%d bcnint=%d\n",
			 sr->result[i].chid,
			 sr->result[i].anl,
			 sr->result[i].sl, sr->result[i].bcnपूर्णांक);
		pr_debug("  capinfo=0x%04x proberesp_rate=%d\n",
			 sr->result[i].capinfo, sr->result[i].proberesp_rate);
	पूर्ण
	/* issue a join request */
	joinreq.channel = sr->result[0].chid;
	स_नकल(joinreq.bssid, sr->result[0].bssid, WLAN_BSSID_LEN);
	result = hfa384x_drvr_setconfig(hw,
					HFA384x_RID_JOINREQUEST,
					&joinreq, HFA384x_RID_JOINREQUEST_LEN);
	अगर (result) अणु
		netdev_err(wlandev->netdev, "setconfig(joinreq) failed, result=%d\n",
			   result);
	पूर्ण
पूर्ण

/*
 * prism2sta_inf_hostscanresults
 *
 * Handles the receipt of a Scan Results info frame.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	inf		ptr to info frame (contents in hfa384x order)
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 */
अटल व्योम prism2sta_inf_hostscanresults(काष्ठा wlandevice *wlandev,
					  काष्ठा hfa384x_inf_frame *inf)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	पूर्णांक nbss;

	nbss = (inf->framelen - 3) / 32;
	pr_debug("Received %d hostscan results\n", nbss);

	अगर (nbss > 32)
		nbss = 32;

	kमुक्त(hw->scanresults);

	hw->scanresults = kmemdup(inf, माप(*inf), GFP_ATOMIC);

	अगर (nbss == 0)
		nbss = -1;

	/* Notअगरy/wake the sleeping caller. */
	hw->म_पूछोlag = nbss;
	wake_up_पूर्णांकerruptible(&hw->cmdq);
पूर्ण;

/*
 * prism2sta_inf_chinक्रमesults
 *
 * Handles the receipt of a Channel Info Results info frame.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	inf		ptr to info frame (contents in hfa384x order)
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 */
अटल व्योम prism2sta_inf_chinक्रमesults(काष्ठा wlandevice *wlandev,
					काष्ठा hfa384x_inf_frame *inf)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	अचिन्हित पूर्णांक i, n;

	hw->channel_info.results.scanchannels =
	    inf->info.chinक्रमesult.scanchannels;

	क्रम (i = 0, n = 0; i < HFA384x_CHINFORESULT_MAX; i++) अणु
		काष्ठा hfa384x_ch_info_result_sub *result;
		काष्ठा hfa384x_ch_info_result_sub *chinक्रमesult;
		पूर्णांक chan;

		अगर (!(hw->channel_info.results.scanchannels & (1 << i)))
			जारी;

		result = &inf->info.chinक्रमesult.result[n];
		chan = result->chid - 1;

		अगर (chan < 0 || chan >= HFA384x_CHINFORESULT_MAX)
			जारी;

		chinक्रमesult = &hw->channel_info.results.result[chan];
		chinक्रमesult->chid = chan;
		chinक्रमesult->anl = result->anl;
		chinक्रमesult->pnl = result->pnl;
		chinक्रमesult->active = result->active;

		pr_debug("chinfo: channel %d, %s level (avg/peak)=%d/%d dB, pcf %d\n",
			 chan + 1,
			 (chinक्रमesult->active & HFA384x_CHINFORESULT_BSSACTIVE)
				? "signal" : "noise",
			 chinक्रमesult->anl, chinक्रमesult->pnl,
			 (chinक्रमesult->active & HFA384x_CHINFORESULT_PCFACTIVE)
				? 1 : 0);
		n++;
	पूर्ण
	atomic_set(&hw->channel_info.करोne, 2);

	hw->channel_info.count = n;
पूर्ण

व्योम prism2sta_processing_defer(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा hfa384x *hw = container_of(data, काष्ठा hfa384x, link_bh);
	काष्ठा wlandevice *wlandev = hw->wlandev;
	काष्ठा hfa384x_bytestr32 ssid;
	पूर्णांक result;

	/* First let's process the auth frames */
	अणु
		काष्ठा sk_buff *skb;
		काष्ठा hfa384x_inf_frame *inf;

		जबतक ((skb = skb_dequeue(&hw->authq))) अणु
			inf = (काष्ठा hfa384x_inf_frame *)skb->data;
			prism2sta_inf_authreq_defer(wlandev, inf);
		पूर्ण
	पूर्ण

	/* Now let's handle the linkstatus stuff */
	अगर (hw->link_status == hw->link_status_new)
		वापस;

	hw->link_status = hw->link_status_new;

	चयन (hw->link_status) अणु
	हाल HFA384x_LINK_NOTCONNECTED:
		/* I'm currently assuming that this is the initial link
		 * state.  It should only be possible immediately
		 * following an Enable command.
		 * Response:
		 * Block Transmits, Ignore receives of data frames
		 */
		netअगर_carrier_off(wlandev->netdev);

		netdev_info(wlandev->netdev, "linkstatus=NOTCONNECTED (unhandled)\n");
		अवरोध;

	हाल HFA384x_LINK_CONNECTED:
		/* This one indicates a successful scan/join/auth/assoc.
		 * When we have the full MLME complement, this event will
		 * signअगरy successful completion of both mlme_authenticate
		 * and mlme_associate.  State management will get a little
		 * ugly here.
		 * Response:
		 * Indicate authentication and/or association
		 * Enable Transmits, Receives and pass up data frames
		 */

		netअगर_carrier_on(wlandev->netdev);

		/* If we are joining a specअगरic AP, set our
		 * state and reset retries
		 */
		अगर (hw->join_ap == 1)
			hw->join_ap = 2;
		hw->join_retries = 60;

		/* Don't call this in monitor mode */
		अगर (wlandev->netdev->type == ARPHRD_ETHER) अणु
			u16 portstatus;

			netdev_info(wlandev->netdev, "linkstatus=CONNECTED\n");

			/* For non-usb devices, we can use the sync versions */
			/* Collect the BSSID, and set state to allow tx */

			result = hfa384x_drvr_अ_लोonfig(hw,
							HFA384x_RID_CURRENTBSSID,
							wlandev->bssid,
							WLAN_BSSID_LEN);
			अगर (result) अणु
				pr_debug
				    ("getconfig(0x%02x) failed, result = %d\n",
				     HFA384x_RID_CURRENTBSSID, result);
				वापस;
			पूर्ण

			result = hfa384x_drvr_अ_लोonfig(hw,
							HFA384x_RID_CURRENTSSID,
							&ssid, माप(ssid));
			अगर (result) अणु
				pr_debug
				    ("getconfig(0x%02x) failed, result = %d\n",
				     HFA384x_RID_CURRENTSSID, result);
				वापस;
			पूर्ण
			prism2mgmt_bytestr2pstr((काष्ठा hfa384x_bytestr *)&ssid,
						(काष्ठा p80211pstrd *)&wlandev->ssid);

			/* Collect the port status */
			result = hfa384x_drvr_अ_लोonfig16(hw,
							  HFA384x_RID_PORTSTATUS,
							  &portstatus);
			अगर (result) अणु
				pr_debug
				    ("getconfig(0x%02x) failed, result = %d\n",
				     HFA384x_RID_PORTSTATUS, result);
				वापस;
			पूर्ण
			wlandev->macmode =
			    (portstatus == HFA384x_PSTATUS_CONN_IBSS) ?
			    WLAN_MACMODE_IBSS_STA : WLAN_MACMODE_ESS_STA;

			/* संकेत back up to cfg80211 layer */
			prism2_connect_result(wlandev, P80211ENUM_truth_false);

			/* Get the ball rolling on the comms quality stuff */
			prism2sta_commsqual_defer(&hw->commsqual_bh);
		पूर्ण
		अवरोध;

	हाल HFA384x_LINK_DISCONNECTED:
		/* This one indicates that our association is gone.  We've
		 * lost connection with the AP and/or been disassociated.
		 * This indicates that the MAC has completely cleared it's
		 * associated state.  We * should send a deauth indication
		 * (implying disassoc) up * to the MLME.
		 * Response:
		 * Indicate Deauthentication
		 * Block Transmits, Ignore receives of data frames
		 */
		अगर (wlandev->netdev->type == ARPHRD_ETHER)
			netdev_info(wlandev->netdev,
				    "linkstatus=DISCONNECTED (unhandled)\n");
		wlandev->macmode = WLAN_MACMODE_NONE;

		netअगर_carrier_off(wlandev->netdev);

		/* संकेत back up to cfg80211 layer */
		prism2_disconnected(wlandev);

		अवरोध;

	हाल HFA384x_LINK_AP_CHANGE:
		/* This one indicates that the MAC has decided to and
		 * successfully completed a change to another AP.  We
		 * should probably implement a reassociation indication
		 * in response to this one.  I'm thinking that the
		 * p80211 layer needs to be notअगरied in हाल of
		 * buffering/queueing issues.  User mode also needs to be
		 * notअगरied so that any BSS dependent elements can be
		 * updated.
		 * associated state.  We * should send a deauth indication
		 * (implying disassoc) up * to the MLME.
		 * Response:
		 * Indicate Reassociation
		 * Enable Transmits, Receives and pass up data frames
		 */
		netdev_info(wlandev->netdev, "linkstatus=AP_CHANGE\n");

		result = hfa384x_drvr_अ_लोonfig(hw,
						HFA384x_RID_CURRENTBSSID,
						wlandev->bssid, WLAN_BSSID_LEN);
		अगर (result) अणु
			pr_debug("getconfig(0x%02x) failed, result = %d\n",
				 HFA384x_RID_CURRENTBSSID, result);
			वापस;
		पूर्ण

		result = hfa384x_drvr_अ_लोonfig(hw,
						HFA384x_RID_CURRENTSSID,
						&ssid, माप(ssid));
		अगर (result) अणु
			pr_debug("getconfig(0x%02x) failed, result = %d\n",
				 HFA384x_RID_CURRENTSSID, result);
			वापस;
		पूर्ण
		prism2mgmt_bytestr2pstr((काष्ठा hfa384x_bytestr *)&ssid,
					(काष्ठा p80211pstrd *)&wlandev->ssid);

		hw->link_status = HFA384x_LINK_CONNECTED;
		netअगर_carrier_on(wlandev->netdev);

		/* संकेत back up to cfg80211 layer */
		prism2_roamed(wlandev);

		अवरोध;

	हाल HFA384x_LINK_AP_OUTOFRANGE:
		/* This one indicates that the MAC has decided that the
		 * AP is out of range, but hasn't found a better candidate
		 * so the MAC मुख्यtains its "associated" state in हाल
		 * we get back in range.  We should block transmits and
		 * receives in this state.  Do we need an indication here?
		 * Probably not since a polling user-mode element would
		 * get this status from p2PortStatus(FD40). What about
		 * p80211?
		 * Response:
		 * Block Transmits, Ignore receives of data frames
		 */
		netdev_info(wlandev->netdev, "linkstatus=AP_OUTOFRANGE (unhandled)\n");

		netअगर_carrier_off(wlandev->netdev);

		अवरोध;

	हाल HFA384x_LINK_AP_INRANGE:
		/* This one indicates that the MAC has decided that the
		 * AP is back in range.  We जारी working with our
		 * existing association.
		 * Response:
		 * Enable Transmits, Receives and pass up data frames
		 */
		netdev_info(wlandev->netdev, "linkstatus=AP_INRANGE\n");

		hw->link_status = HFA384x_LINK_CONNECTED;
		netअगर_carrier_on(wlandev->netdev);

		अवरोध;

	हाल HFA384x_LINK_ASSOCFAIL:
		/* This one is actually a peer to CONNECTED.  We've
		 * requested a join क्रम a given SSID and optionally BSSID.
		 * We can use this one to indicate authentication and
		 * association failures.  The trick is going to be
		 * 1) identअगरying the failure, and 2) state management.
		 * Response:
		 * Disable Transmits, Ignore receives of data frames
		 */
		अगर (hw->join_ap && --hw->join_retries > 0) अणु
			काष्ठा hfa384x_join_request_data joinreq;

			joinreq = hw->joinreq;
			/* Send the join request */
			hfa384x_drvr_setconfig(hw,
					       HFA384x_RID_JOINREQUEST,
					       &joinreq,
					       HFA384x_RID_JOINREQUEST_LEN);
			netdev_info(wlandev->netdev,
				    "linkstatus=ASSOCFAIL (re-submitting join)\n");
		पूर्ण अन्यथा अणु
			netdev_info(wlandev->netdev, "linkstatus=ASSOCFAIL (unhandled)\n");
		पूर्ण

		netअगर_carrier_off(wlandev->netdev);

		/* संकेत back up to cfg80211 layer */
		prism2_connect_result(wlandev, P80211ENUM_truth_true);

		अवरोध;

	शेष:
		/* This is bad, IO port problems? */
		netdev_warn(wlandev->netdev,
			    "unknown linkstatus=0x%02x\n", hw->link_status);
		वापस;
	पूर्ण

	wlandev->linkstatus = (hw->link_status == HFA384x_LINK_CONNECTED);
पूर्ण

/*
 * prism2sta_inf_linkstatus
 *
 * Handles the receipt of a Link Status info frame.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	inf		ptr to info frame (contents in hfa384x order)
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 */
अटल व्योम prism2sta_inf_linkstatus(काष्ठा wlandevice *wlandev,
				     काष्ठा hfa384x_inf_frame *inf)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;

	hw->link_status_new = le16_to_cpu(inf->info.linkstatus.linkstatus);

	schedule_work(&hw->link_bh);
पूर्ण

/*
 * prism2sta_inf_assocstatus
 *
 * Handles the receipt of an Association Status info frame. Should
 * be present in APs only.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	inf		ptr to info frame (contents in hfa384x order)
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 */
अटल व्योम prism2sta_inf_assocstatus(काष्ठा wlandevice *wlandev,
				      काष्ठा hfa384x_inf_frame *inf)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	काष्ठा hfa384x_assoc_status rec;
	पूर्णांक i;

	स_नकल(&rec, &inf->info.assocstatus, माप(rec));
	le16_to_cpus(&rec.assocstatus);
	le16_to_cpus(&rec.reason);

	/*
	 * Find the address in the list of authenticated stations.
	 * If it wasn't found, then this address has not been previously
	 * authenticated and something weird has happened अगर this is
	 * anything other than an "authentication failed" message.
	 * If the address was found, then set the "associated" flag क्रम
	 * that station, based on whether the station is associating or
	 * losing its association.  Something weird has also happened
	 * अगर we find the address in the list of authenticated stations
	 * but we are getting an "authentication failed" message.
	 */

	क्रम (i = 0; i < hw->authlist.cnt; i++)
		अगर (ether_addr_equal(rec.sta_addr, hw->authlist.addr[i]))
			अवरोध;

	अगर (i >= hw->authlist.cnt) अणु
		अगर (rec.assocstatus != HFA384x_ASSOCSTATUS_AUTHFAIL)
			netdev_warn(wlandev->netdev,
				    "assocstatus info frame received for non-authenticated station.\n");
	पूर्ण अन्यथा अणु
		hw->authlist.assoc[i] =
		    (rec.assocstatus == HFA384x_ASSOCSTATUS_STAASSOC ||
		     rec.assocstatus == HFA384x_ASSOCSTATUS_REASSOC);

		अगर (rec.assocstatus == HFA384x_ASSOCSTATUS_AUTHFAIL)
			netdev_warn(wlandev->netdev,
				    "authfail assocstatus info frame received for authenticated station.\n");
	पूर्ण
पूर्ण

/*
 * prism2sta_inf_authreq
 *
 * Handles the receipt of an Authentication Request info frame. Should
 * be present in APs only.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	inf		ptr to info frame (contents in hfa384x order)
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 *
 */
अटल व्योम prism2sta_inf_authreq(काष्ठा wlandevice *wlandev,
				  काष्ठा hfa384x_inf_frame *inf)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	काष्ठा sk_buff *skb;

	skb = dev_alloc_skb(माप(*inf));
	अगर (skb) अणु
		skb_put(skb, माप(*inf));
		स_नकल(skb->data, inf, माप(*inf));
		skb_queue_tail(&hw->authq, skb);
		schedule_work(&hw->link_bh);
	पूर्ण
पूर्ण

अटल व्योम prism2sta_inf_authreq_defer(काष्ठा wlandevice *wlandev,
					काष्ठा hfa384x_inf_frame *inf)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	काष्ठा hfa384x_authenticate_station_data rec;

	पूर्णांक i, added, result, cnt;
	u8 *addr;

	/*
	 * Build the AuthenticateStation record.  Initialize it क्रम denying
	 * authentication.
	 */

	ether_addr_copy(rec.address, inf->info.authreq.sta_addr);
	rec.status = cpu_to_le16(P80211ENUM_status_unspec_failure);

	/*
	 * Authenticate based on the access mode.
	 */

	चयन (hw->accessmode) अणु
	हाल WLAN_ACCESS_NONE:

		/*
		 * Deny all new authentications.  However, अगर a station
		 * is ALREADY authenticated, then accept it.
		 */

		क्रम (i = 0; i < hw->authlist.cnt; i++)
			अगर (ether_addr_equal(rec.address,
					     hw->authlist.addr[i])) अणु
				rec.status = cpu_to_le16(P80211ENUM_status_successful);
				अवरोध;
			पूर्ण

		अवरोध;

	हाल WLAN_ACCESS_ALL:

		/*
		 * Allow all authentications.
		 */

		rec.status = cpu_to_le16(P80211ENUM_status_successful);
		अवरोध;

	हाल WLAN_ACCESS_ALLOW:

		/*
		 * Only allow the authentication अगर the MAC address
		 * is in the list of allowed addresses.
		 *
		 * Since this is the पूर्णांकerrupt handler, we may be here
		 * जबतक the access list is in the middle of being
		 * updated.  Choose the list which is currently okay.
		 * See "prism2mib_priv_accessallow()" क्रम details.
		 */

		अगर (hw->allow.modअगरy == 0) अणु
			cnt = hw->allow.cnt;
			addr = hw->allow.addr[0];
		पूर्ण अन्यथा अणु
			cnt = hw->allow.cnt1;
			addr = hw->allow.addr1[0];
		पूर्ण

		क्रम (i = 0; i < cnt; i++, addr += ETH_ALEN)
			अगर (ether_addr_equal(rec.address, addr)) अणु
				rec.status = cpu_to_le16(P80211ENUM_status_successful);
				अवरोध;
			पूर्ण

		अवरोध;

	हाल WLAN_ACCESS_DENY:

		/*
		 * Allow the authentication UNLESS the MAC address is
		 * in the list of denied addresses.
		 *
		 * Since this is the पूर्णांकerrupt handler, we may be here
		 * जबतक the access list is in the middle of being
		 * updated.  Choose the list which is currently okay.
		 * See "prism2mib_priv_accessdeny()" क्रम details.
		 */

		अगर (hw->deny.modअगरy == 0) अणु
			cnt = hw->deny.cnt;
			addr = hw->deny.addr[0];
		पूर्ण अन्यथा अणु
			cnt = hw->deny.cnt1;
			addr = hw->deny.addr1[0];
		पूर्ण

		rec.status = cpu_to_le16(P80211ENUM_status_successful);

		क्रम (i = 0; i < cnt; i++, addr += ETH_ALEN)
			अगर (ether_addr_equal(rec.address, addr)) अणु
				rec.status = cpu_to_le16(P80211ENUM_status_unspec_failure);
				अवरोध;
			पूर्ण

		अवरोध;
	पूर्ण

	/*
	 * If the authentication is okay, then add the MAC address to the
	 * list of authenticated stations.  Don't add the address अगर it
	 * is alपढ़ोy in the list. (802.11b करोes not seem to disallow
	 * a station from issuing an authentication request when the
	 * station is alपढ़ोy authenticated. Does this sort of thing
	 * ever happen?  We might as well करो the check just in हाल.)
	 */

	added = 0;

	अगर (rec.status == cpu_to_le16(P80211ENUM_status_successful)) अणु
		क्रम (i = 0; i < hw->authlist.cnt; i++)
			अगर (ether_addr_equal(rec.address,
					     hw->authlist.addr[i]))
				अवरोध;

		अगर (i >= hw->authlist.cnt) अणु
			अगर (hw->authlist.cnt >= WLAN_AUTH_MAX) अणु
				rec.status = cpu_to_le16(P80211ENUM_status_ap_full);
			पूर्ण अन्यथा अणु
				ether_addr_copy(hw->authlist.addr[hw->authlist.cnt],
						rec.address);
				hw->authlist.cnt++;
				added = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Send back the results of the authentication.  If this करोesn't work,
	 * then make sure to हटाओ the address from the authenticated list अगर
	 * it was added.
	 */

	rec.algorithm = inf->info.authreq.algorithm;

	result = hfa384x_drvr_setconfig(hw, HFA384x_RID_AUTHENTICATESTA,
					&rec, माप(rec));
	अगर (result) अणु
		अगर (added)
			hw->authlist.cnt--;
		netdev_err(wlandev->netdev,
			   "setconfig(authenticatestation) failed, result=%d\n",
			   result);
	पूर्ण
पूर्ण

/*
 * prism2sta_inf_psusercnt
 *
 * Handles the receipt of a PowerSaveUserCount info frame. Should
 * be present in APs only.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	inf		ptr to info frame (contents in hfa384x order)
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 */
अटल व्योम prism2sta_inf_psusercnt(काष्ठा wlandevice *wlandev,
				    काष्ठा hfa384x_inf_frame *inf)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;

	hw->psusercount = le16_to_cpu(inf->info.psusercnt.usercnt);
पूर्ण

/*
 * prism2sta_ev_info
 *
 * Handles the Info event.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	inf		ptr to a generic info frame
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 */
व्योम prism2sta_ev_info(काष्ठा wlandevice *wlandev,
		       काष्ठा hfa384x_inf_frame *inf)
अणु
	le16_to_cpus(&inf->infotype);
	/* Dispatch */
	चयन (inf->infotype) अणु
	हाल HFA384x_IT_HANDOVERADDR:
		prism2sta_inf_hanकरोver(wlandev, inf);
		अवरोध;
	हाल HFA384x_IT_COMMTALLIES:
		prism2sta_inf_tallies(wlandev, inf);
		अवरोध;
	हाल HFA384x_IT_HOSTSCANRESULTS:
		prism2sta_inf_hostscanresults(wlandev, inf);
		अवरोध;
	हाल HFA384x_IT_SCANRESULTS:
		prism2sta_inf_scanresults(wlandev, inf);
		अवरोध;
	हाल HFA384x_IT_CHINFORESULTS:
		prism2sta_inf_chinक्रमesults(wlandev, inf);
		अवरोध;
	हाल HFA384x_IT_LINKSTATUS:
		prism2sta_inf_linkstatus(wlandev, inf);
		अवरोध;
	हाल HFA384x_IT_ASSOCSTATUS:
		prism2sta_inf_assocstatus(wlandev, inf);
		अवरोध;
	हाल HFA384x_IT_AUTHREQ:
		prism2sta_inf_authreq(wlandev, inf);
		अवरोध;
	हाल HFA384x_IT_PSUSERCNT:
		prism2sta_inf_psusercnt(wlandev, inf);
		अवरोध;
	हाल HFA384x_IT_KEYIDCHANGED:
		netdev_warn(wlandev->netdev, "Unhandled IT_KEYIDCHANGED\n");
		अवरोध;
	हाल HFA384x_IT_ASSOCREQ:
		netdev_warn(wlandev->netdev, "Unhandled IT_ASSOCREQ\n");
		अवरोध;
	हाल HFA384x_IT_MICFAILURE:
		netdev_warn(wlandev->netdev, "Unhandled IT_MICFAILURE\n");
		अवरोध;
	शेष:
		netdev_warn(wlandev->netdev,
			    "Unknown info type=0x%02x\n", inf->infotype);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * prism2sta_ev_txexc
 *
 * Handles the TxExc event.  A Transmit Exception event indicates
 * that the MAC's TX process was unsuccessful - so the packet did
 * not get transmitted.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	status		tx frame status word
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 */
व्योम prism2sta_ev_txexc(काष्ठा wlandevice *wlandev, u16 status)
अणु
	pr_debug("TxExc status=0x%x.\n", status);
पूर्ण

/*
 * prism2sta_ev_tx
 *
 * Handles the Tx event.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	status		tx frame status word
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 */
व्योम prism2sta_ev_tx(काष्ठा wlandevice *wlandev, u16 status)
अणु
	pr_debug("Tx Complete, status=0x%04x\n", status);
	/* update linux network stats */
	wlandev->netdev->stats.tx_packets++;
पूर्ण

/*
 * prism2sta_ev_alloc
 *
 * Handles the Alloc event.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 */
व्योम prism2sta_ev_alloc(काष्ठा wlandevice *wlandev)
अणु
	netअगर_wake_queue(wlandev->netdev);
पूर्ण

/*
 * create_wlan
 *
 * Called at module init समय.  This creates the काष्ठा wlandevice काष्ठाure
 * and initializes it with relevant bits.
 *
 * Arguments:
 *	none
 *
 * Returns:
 *	the created काष्ठा wlandevice काष्ठाure.
 *
 * Side effects:
 *	also allocates the priv/hw काष्ठाures.
 *
 * Call context:
 *	process thपढ़ो
 *
 */
अटल काष्ठा wlandevice *create_wlan(व्योम)
अणु
	काष्ठा wlandevice *wlandev = शून्य;
	काष्ठा hfa384x *hw = शून्य;

	/* Alloc our काष्ठाures */
	wlandev = kzalloc(माप(*wlandev), GFP_KERNEL);
	hw = kzalloc(माप(*hw), GFP_KERNEL);

	अगर (!wlandev || !hw) अणु
		kमुक्त(wlandev);
		kमुक्त(hw);
		वापस शून्य;
	पूर्ण

	/* Initialize the network device object. */
	wlandev->nsdname = dev_info;
	wlandev->msdstate = WLAN_MSD_HWPRESENT_PENDING;
	wlandev->priv = hw;
	wlandev->खोलो = prism2sta_खोलो;
	wlandev->बंद = prism2sta_बंद;
	wlandev->reset = prism2sta_reset;
	wlandev->txframe = prism2sta_txframe;
	wlandev->mlmerequest = prism2sta_mlmerequest;
	wlandev->set_multicast_list = prism2sta_seपंचांगulticast;
	wlandev->tx_समयout = hfa384x_tx_समयout;

	wlandev->nsdcaps = P80211_NSDCAP_HWFRAGMENT | P80211_NSDCAP_AUTOJOIN;

	/* Initialize the device निजी data काष्ठाure. */
	hw->करोt11_desired_bss_type = 1;

	वापस wlandev;
पूर्ण

व्योम prism2sta_commsqual_defer(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा hfa384x *hw = container_of(data, काष्ठा hfa384x, commsqual_bh);
	काष्ठा wlandevice *wlandev = hw->wlandev;
	काष्ठा hfa384x_bytestr32 ssid;
	काष्ठा p80211msg_करोt11req_mibget msg;
	काष्ठा p80211item_uपूर्णांक32 *mibitem = (काष्ठा p80211item_uपूर्णांक32 *)
						&msg.mibattribute.data;
	पूर्णांक result = 0;

	अगर (hw->wlandev->hwहटाओd)
		वापस;

	/* we करोn't care if we're in AP mode */
	अगर ((wlandev->macmode == WLAN_MACMODE_NONE) ||
	    (wlandev->macmode == WLAN_MACMODE_ESS_AP)) अणु
		वापस;
	पूर्ण

	/* It only makes sense to poll these in non-IBSS */
	अगर (wlandev->macmode != WLAN_MACMODE_IBSS_STA) अणु
		result = hfa384x_drvr_अ_लोonfig(hw, HFA384x_RID_DBMCOMMSQUALITY,
						&hw->qual, HFA384x_RID_DBMCOMMSQUALITY_LEN);

		अगर (result) अणु
			netdev_err(wlandev->netdev, "error fetching commsqual\n");
			वापस;
		पूर्ण

		pr_debug("commsqual %d %d %d\n",
			 le16_to_cpu(hw->qual.cq_curr_bss),
			 le16_to_cpu(hw->qual.asl_curr_bss),
			 le16_to_cpu(hw->qual.anl_curr_fc));
	पूर्ण

	/* Get the संकेत rate */
	msg.msgcode = DIDMSG_DOT11REQ_MIBGET;
	mibitem->did = DIDMIB_P2_MAC_CURRENTTXRATE;
	result = p80211req_करोrequest(wlandev, (u8 *)&msg);

	अगर (result) अणु
		pr_debug("get signal rate failed, result = %d\n",
			 result);
		वापस;
	पूर्ण

	चयन (mibitem->data) अणु
	हाल HFA384x_RATEBIT_1:
		hw->txrate = 10;
		अवरोध;
	हाल HFA384x_RATEBIT_2:
		hw->txrate = 20;
		अवरोध;
	हाल HFA384x_RATEBIT_5करोt5:
		hw->txrate = 55;
		अवरोध;
	हाल HFA384x_RATEBIT_11:
		hw->txrate = 110;
		अवरोध;
	शेष:
		pr_debug("Bad ratebit (%d)\n", mibitem->data);
	पूर्ण

	/* Lastly, we need to make sure the BSSID didn't change on us */
	result = hfa384x_drvr_अ_लोonfig(hw,
					HFA384x_RID_CURRENTBSSID,
					wlandev->bssid, WLAN_BSSID_LEN);
	अगर (result) अणु
		pr_debug("getconfig(0x%02x) failed, result = %d\n",
			 HFA384x_RID_CURRENTBSSID, result);
		वापस;
	पूर्ण

	result = hfa384x_drvr_अ_लोonfig(hw,
					HFA384x_RID_CURRENTSSID,
					&ssid, माप(ssid));
	अगर (result) अणु
		pr_debug("getconfig(0x%02x) failed, result = %d\n",
			 HFA384x_RID_CURRENTSSID, result);
		वापस;
	पूर्ण
	prism2mgmt_bytestr2pstr((काष्ठा hfa384x_bytestr *)&ssid,
				(काष्ठा p80211pstrd *)&wlandev->ssid);

	/* Reschedule समयr */
	mod_समयr(&hw->commsqual_समयr, jअगरfies + HZ);
पूर्ण

व्योम prism2sta_commsqual_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा hfa384x *hw = from_समयr(hw, t, commsqual_समयr);

	schedule_work(&hw->commsqual_bh);
पूर्ण
