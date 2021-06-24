<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1)
/* src/prism2/driver/prism2mgmt.c
 *
 * Management request handler functions.
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
 * The functions in this file handle management requests sent from
 * user mode.
 *
 * Most of these functions have two separate blocks of code that are
 * conditional on whether this is a station or an AP.  This is used
 * to separate out the STA and AP responses to these management primitives.
 * It's a choice (good, bad, indअगरferent?) to have the code in the same
 * place so it's clear that the same primitive is implemented in both
 * हालs but has dअगरferent behavior.
 *
 * --------------------------------------------------------------------
 */

#समावेश <linux/अगर_arp.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/wireless.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/usb.h>
#समावेश <linux/bitops.h>

#समावेश "p80211types.h"
#समावेश "p80211hdr.h"
#समावेश "p80211mgmt.h"
#समावेश "p80211conv.h"
#समावेश "p80211msg.h"
#समावेश "p80211netdev.h"
#समावेश "p80211metadef.h"
#समावेश "p80211metastruct.h"
#समावेश "hfa384x.h"
#समावेश "prism2mgmt.h"

/* Converts 802.11 क्रमmat rate specअगरications to prism2 */
अटल अंतरभूत u16 p80211rate_to_p2bit(u32 rate)
अणु
	चयन (rate & ~BIT(7)) अणु
	हाल 2:
		वापस BIT(0);
	हाल 4:
		वापस BIT(1);
	हाल 11:
		वापस BIT(2);
	हाल 22:
		वापस BIT(3);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*----------------------------------------------------------------
 * prism2mgmt_scan
 *
 * Initiate a scan क्रम BSSs.
 *
 * This function corresponds to MLME-scan.request and part of
 * MLME-scan.confirm.  As far as I can tell in the standard, there
 * are no restrictions on when a scan.request may be issued.  We have
 * to handle in whatever state the driver/MAC happen to be.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	msgp		ptr to msg buffer
 *
 * Returns:
 *	0	success and करोne
 *	<0	success, but we're रुकोing क्रम something to finish.
 *	>0	an error occurred जबतक handling the message.
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो  (usually)
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
पूर्णांक prism2mgmt_scan(काष्ठा wlandevice *wlandev, व्योम *msgp)
अणु
	पूर्णांक result = 0;
	काष्ठा hfa384x *hw = wlandev->priv;
	काष्ठा p80211msg_करोt11req_scan *msg = msgp;
	u16 roamingmode, word;
	पूर्णांक i, समयout;
	पूर्णांक isपंचांगpenable = 0;

	काष्ठा hfa384x_host_scan_request_data scanreq;

	/* gatekeeper check */
	अगर (HFA384x_FIRMWARE_VERSION(hw->ident_sta_fw.major,
				     hw->ident_sta_fw.minor,
				     hw->ident_sta_fw.variant) <
	    HFA384x_FIRMWARE_VERSION(1, 3, 2)) अणु
		netdev_err(wlandev->netdev,
			   "HostScan not supported with current firmware (<1.3.2).\n");
		result = 1;
		msg->resultcode.data = P80211ENUM_resultcode_not_supported;
		जाओ निकास;
	पूर्ण

	स_रखो(&scanreq, 0, माप(scanreq));

	/* save current roaming mode */
	result = hfa384x_drvr_अ_लोonfig16(hw,
					  HFA384x_RID_CNFROAMINGMODE,
					  &roamingmode);
	अगर (result) अणु
		netdev_err(wlandev->netdev,
			   "getconfig(ROAMMODE) failed. result=%d\n", result);
		msg->resultcode.data =
		    P80211ENUM_resultcode_implementation_failure;
		जाओ निकास;
	पूर्ण

	/* drop पूर्णांकo mode 3 क्रम the scan */
	result = hfa384x_drvr_setconfig16(hw,
					  HFA384x_RID_CNFROAMINGMODE,
					  HFA384x_ROAMMODE_HOSTSCAN_HOSTROAM);
	अगर (result) अणु
		netdev_err(wlandev->netdev,
			   "setconfig(ROAMINGMODE) failed. result=%d\n",
			   result);
		msg->resultcode.data =
		    P80211ENUM_resultcode_implementation_failure;
		जाओ निकास;
	पूर्ण

	/* active or passive? */
	अगर (HFA384x_FIRMWARE_VERSION(hw->ident_sta_fw.major,
				     hw->ident_sta_fw.minor,
				     hw->ident_sta_fw.variant) >
	    HFA384x_FIRMWARE_VERSION(1, 5, 0)) अणु
		अगर (msg->scantype.data != P80211ENUM_scantype_active)
			word = msg->maxchannelसमय.data;
		अन्यथा
			word = 0;

		result =
		    hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFPASSIVESCANCTRL,
					     word);
		अगर (result) अणु
			netdev_warn(wlandev->netdev,
				    "Passive scan not supported with current firmware.  (<1.5.1)\n");
		पूर्ण
	पूर्ण

	/* set up the txrate to be 2MBPS. Should be fastest basicrate... */
	word = HFA384x_RATEBIT_2;
	scanreq.tx_rate = cpu_to_le16(word);

	/* set up the channel list */
	word = 0;
	क्रम (i = 0; i < msg->channellist.data.len; i++) अणु
		u8 channel = msg->channellist.data.data[i];

		अगर (channel > 14)
			जारी;
		/* channel 1 is BIT 0 ... channel 14 is BIT 13 */
		word |= (1 << (channel - 1));
	पूर्ण
	scanreq.channel_list = cpu_to_le16(word);

	/* set up the ssid, अगर present. */
	scanreq.ssid.len = cpu_to_le16(msg->ssid.data.len);
	स_नकल(scanreq.ssid.data, msg->ssid.data.data, msg->ssid.data.len);

	/* Enable the MAC port अगर it's not alपढ़ोy enabled  */
	result = hfa384x_drvr_अ_लोonfig16(hw, HFA384x_RID_PORTSTATUS, &word);
	अगर (result) अणु
		netdev_err(wlandev->netdev,
			   "getconfig(PORTSTATUS) failed. result=%d\n", result);
		msg->resultcode.data =
		    P80211ENUM_resultcode_implementation_failure;
		जाओ निकास;
	पूर्ण
	अगर (word == HFA384x_PORTSTATUS_DISABLED) अणु
		__le16 wordbuf[17];

		result = hfa384x_drvr_setconfig16(hw,
						  HFA384x_RID_CNFROAMINGMODE,
						  HFA384x_ROAMMODE_HOSTSCAN_HOSTROAM);
		अगर (result) अणु
			netdev_err(wlandev->netdev,
				   "setconfig(ROAMINGMODE) failed. result=%d\n",
				   result);
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
			जाओ निकास;
		पूर्ण
		/* Conकाष्ठा a bogus SSID and assign it to OwnSSID and
		 * DesiredSSID
		 */
		wordbuf[0] = cpu_to_le16(WLAN_SSID_MAXLEN);
		get_अक्रमom_bytes(&wordbuf[1], WLAN_SSID_MAXLEN);
		result = hfa384x_drvr_setconfig(hw, HFA384x_RID_CNFOWNSSID,
						wordbuf,
						HFA384x_RID_CNFOWNSSID_LEN);
		अगर (result) अणु
			netdev_err(wlandev->netdev, "Failed to set OwnSSID.\n");
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
			जाओ निकास;
		पूर्ण
		result = hfa384x_drvr_setconfig(hw, HFA384x_RID_CNFDESIREDSSID,
						wordbuf,
						HFA384x_RID_CNFDESIREDSSID_LEN);
		अगर (result) अणु
			netdev_err(wlandev->netdev,
				   "Failed to set DesiredSSID.\n");
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
			जाओ निकास;
		पूर्ण
		/* bsstype */
		result = hfa384x_drvr_setconfig16(hw,
						  HFA384x_RID_CNFPORTTYPE,
						  HFA384x_PORTTYPE_IBSS);
		अगर (result) अणु
			netdev_err(wlandev->netdev,
				   "Failed to set CNFPORTTYPE.\n");
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
			जाओ निकास;
		पूर्ण
		/* ibss options */
		result = hfa384x_drvr_setconfig16(hw,
						  HFA384x_RID_CREATEIBSS,
						  HFA384x_CREATEIBSS_JOINCREATEIBSS);
		अगर (result) अणु
			netdev_err(wlandev->netdev,
				   "Failed to set CREATEIBSS.\n");
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
			जाओ निकास;
		पूर्ण
		result = hfa384x_drvr_enable(hw, 0);
		अगर (result) अणु
			netdev_err(wlandev->netdev,
				   "drvr_enable(0) failed. result=%d\n",
				   result);
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
			जाओ निकास;
		पूर्ण
		isपंचांगpenable = 1;
	पूर्ण

	/* Figure out our समयout first Kus, then HZ */
	समयout = msg->channellist.data.len * msg->maxchannelसमय.data;
	समयout = (समयout * HZ) / 1000;

	/* Issue the scan request */
	hw->म_पूछोlag = 0;

	result = hfa384x_drvr_setconfig(hw,
					HFA384x_RID_HOSTSCAN, &scanreq,
					माप(scanreq));
	अगर (result) अणु
		netdev_err(wlandev->netdev,
			   "setconfig(SCANREQUEST) failed. result=%d\n",
			   result);
		msg->resultcode.data =
		    P80211ENUM_resultcode_implementation_failure;
		जाओ निकास;
	पूर्ण

	/* sleep until info frame arrives */
	रुको_event_पूर्णांकerruptible_समयout(hw->cmdq, hw->म_पूछोlag, समयout);

	msg->numbss.status = P80211ENUM_msgitem_status_data_ok;
	अगर (hw->म_पूछोlag == -1)
		hw->म_पूछोlag = 0;

	msg->numbss.data = hw->म_पूछोlag;

	hw->म_पूछोlag = 0;

	/* Disable port अगर we temporarily enabled it. */
	अगर (isपंचांगpenable) अणु
		result = hfa384x_drvr_disable(hw, 0);
		अगर (result) अणु
			netdev_err(wlandev->netdev,
				   "drvr_disable(0) failed. result=%d\n",
				   result);
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
			जाओ निकास;
		पूर्ण
	पूर्ण

	/* restore original roaming mode */
	result = hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFROAMINGMODE,
					  roamingmode);
	अगर (result) अणु
		netdev_err(wlandev->netdev,
			   "setconfig(ROAMMODE) failed. result=%d\n", result);
		msg->resultcode.data =
		    P80211ENUM_resultcode_implementation_failure;
		जाओ निकास;
	पूर्ण

	result = 0;
	msg->resultcode.data = P80211ENUM_resultcode_success;

निकास:
	msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * prism2mgmt_scan_results
 *
 * Retrieve the BSS description क्रम one of the BSSs identअगरied in
 * a scan.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	msgp		ptr to msg buffer
 *
 * Returns:
 *	0	success and करोne
 *	<0	success, but we're रुकोing क्रम something to finish.
 *	>0	an error occurred जबतक handling the message.
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो  (usually)
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
पूर्णांक prism2mgmt_scan_results(काष्ठा wlandevice *wlandev, व्योम *msgp)
अणु
	पूर्णांक result = 0;
	काष्ठा p80211msg_करोt11req_scan_results *req;
	काष्ठा hfa384x *hw = wlandev->priv;
	काष्ठा hfa384x_hscan_result_sub *item = शून्य;

	पूर्णांक count;

	req = msgp;

	req->resultcode.status = P80211ENUM_msgitem_status_data_ok;

	अगर (!hw->scanresults) अणु
		netdev_err(wlandev->netdev,
			   "dot11req_scan_results can only be used after a successful dot11req_scan.\n");
		result = 2;
		req->resultcode.data = P80211ENUM_resultcode_invalid_parameters;
		जाओ निकास;
	पूर्ण

	count = (hw->scanresults->framelen - 3) / 32;
	अगर (count > HFA384x_SCANRESULT_MAX)
		count = HFA384x_SCANRESULT_MAX;

	अगर (req->bssindex.data >= count) अणु
		netdev_dbg(wlandev->netdev,
			   "requested index (%d) out of range (%d)\n",
			   req->bssindex.data, count);
		result = 2;
		req->resultcode.data = P80211ENUM_resultcode_invalid_parameters;
		जाओ निकास;
	पूर्ण

	item = &hw->scanresults->info.hscanresult.result[req->bssindex.data];
	/* संकेत and noise */
	req->संकेत.status = P80211ENUM_msgitem_status_data_ok;
	req->noise.status = P80211ENUM_msgitem_status_data_ok;
	req->संकेत.data = le16_to_cpu(item->sl);
	req->noise.data = le16_to_cpu(item->anl);

	/* BSSID */
	req->bssid.status = P80211ENUM_msgitem_status_data_ok;
	req->bssid.data.len = WLAN_BSSID_LEN;
	स_नकल(req->bssid.data.data, item->bssid, WLAN_BSSID_LEN);

	/* SSID */
	req->ssid.status = P80211ENUM_msgitem_status_data_ok;
	req->ssid.data.len = le16_to_cpu(item->ssid.len);
	req->ssid.data.len = min_t(u16, req->ssid.data.len, WLAN_SSID_MAXLEN);
	स_नकल(req->ssid.data.data, item->ssid.data, req->ssid.data.len);

	/* supported rates */
	क्रम (count = 0; count < 10; count++)
		अगर (item->supprates[count] == 0)
			अवरोध;

#घोषणा REQBASICRATE(N) \
	करो अणु \
		अगर ((count >= (N)) && DOT11_RATE5_ISBASIC_GET(	\
			item->supprates[(N) - 1])) अणु \
			req->basicrate ## N .data = item->supprates[(N) - 1]; \
			req->basicrate ## N .status = \
				P80211ENUM_msgitem_status_data_ok; \
		पूर्ण \
	पूर्ण जबतक (0)

	REQBASICRATE(1);
	REQBASICRATE(2);
	REQBASICRATE(3);
	REQBASICRATE(4);
	REQBASICRATE(5);
	REQBASICRATE(6);
	REQBASICRATE(7);
	REQBASICRATE(8);

#घोषणा REQSUPPRATE(N) \
	करो अणु \
		अगर (count >= (N)) अणु					\
			req->supprate ## N .data = item->supprates[(N) - 1]; \
			req->supprate ## N .status = \
				P80211ENUM_msgitem_status_data_ok; \
		पूर्ण \
	पूर्ण जबतक (0)

	REQSUPPRATE(1);
	REQSUPPRATE(2);
	REQSUPPRATE(3);
	REQSUPPRATE(4);
	REQSUPPRATE(5);
	REQSUPPRATE(6);
	REQSUPPRATE(7);
	REQSUPPRATE(8);

	/* beacon period */
	req->beaconperiod.status = P80211ENUM_msgitem_status_data_ok;
	req->beaconperiod.data = le16_to_cpu(item->bcnपूर्णांक);

	/* बारtamps */
	req->बारtamp.status = P80211ENUM_msgitem_status_data_ok;
	req->बारtamp.data = jअगरfies;
	req->स_स्थानीय.status = P80211ENUM_msgitem_status_data_ok;
	req->स_स्थानीय.data = jअगरfies;

	/* atim winकरोw */
	req->ibssatimwinकरोw.status = P80211ENUM_msgitem_status_data_ok;
	req->ibssatimwinकरोw.data = le16_to_cpu(item->atim);

	/* Channel */
	req->dschannel.status = P80211ENUM_msgitem_status_data_ok;
	req->dschannel.data = le16_to_cpu(item->chid);

	/* capinfo bits */
	count = le16_to_cpu(item->capinfo);
	req->capinfo.status = P80211ENUM_msgitem_status_data_ok;
	req->capinfo.data = count;

	/* privacy flag */
	req->privacy.status = P80211ENUM_msgitem_status_data_ok;
	req->privacy.data = WLAN_GET_MGMT_CAP_INFO_PRIVACY(count);

	/* cfpollable */
	req->cfpollable.status = P80211ENUM_msgitem_status_data_ok;
	req->cfpollable.data = WLAN_GET_MGMT_CAP_INFO_CFPOLLABLE(count);

	/* cfpollreq */
	req->cfpollreq.status = P80211ENUM_msgitem_status_data_ok;
	req->cfpollreq.data = WLAN_GET_MGMT_CAP_INFO_CFPOLLREQ(count);

	/* bsstype */
	req->bsstype.status = P80211ENUM_msgitem_status_data_ok;
	req->bsstype.data = (WLAN_GET_MGMT_CAP_INFO_ESS(count)) ?
	    P80211ENUM_bsstype_infraकाष्ठाure : P80211ENUM_bsstype_independent;

	result = 0;
	req->resultcode.data = P80211ENUM_resultcode_success;

निकास:
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * prism2mgmt_start
 *
 * Start a BSS.  Any station can करो this क्रम IBSS, only AP क्रम ESS.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	msgp		ptr to msg buffer
 *
 * Returns:
 *	0	success and करोne
 *	<0	success, but we're रुकोing क्रम something to finish.
 *	>0	an error occurred जबतक handling the message.
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो  (usually)
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
पूर्णांक prism2mgmt_start(काष्ठा wlandevice *wlandev, व्योम *msgp)
अणु
	पूर्णांक result = 0;
	काष्ठा hfa384x *hw = wlandev->priv;
	काष्ठा p80211msg_करोt11req_start *msg = msgp;

	काष्ठा p80211pstrd *pstr;
	u8 bytebuf[80];
	काष्ठा hfa384x_bytestr *p2bytestr = (काष्ठा hfa384x_bytestr *)bytebuf;
	u16 word;

	wlandev->macmode = WLAN_MACMODE_NONE;

	/* Set the SSID */
	स_नकल(&wlandev->ssid, &msg->ssid.data, माप(msg->ssid.data));

	/*** ADHOC IBSS ***/
	/* see अगर current f/w is less than 8c3 */
	अगर (HFA384x_FIRMWARE_VERSION(hw->ident_sta_fw.major,
				     hw->ident_sta_fw.minor,
				     hw->ident_sta_fw.variant) <
	    HFA384x_FIRMWARE_VERSION(0, 8, 3)) अणु
		/* Ad-Hoc not quite supported on Prism2 */
		msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
		msg->resultcode.data = P80211ENUM_resultcode_not_supported;
		जाओ करोne;
	पूर्ण

	msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;

	/*** STATION ***/
	/* Set the REQUIRED config items */
	/* SSID */
	pstr = (काष्ठा p80211pstrd *)&msg->ssid.data;
	prism2mgmt_pstr2bytestr(p2bytestr, pstr);
	result = hfa384x_drvr_setconfig(hw, HFA384x_RID_CNFOWNSSID,
					bytebuf, HFA384x_RID_CNFOWNSSID_LEN);
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to set CnfOwnSSID\n");
		जाओ failed;
	पूर्ण
	result = hfa384x_drvr_setconfig(hw, HFA384x_RID_CNFDESIREDSSID,
					bytebuf,
					HFA384x_RID_CNFDESIREDSSID_LEN);
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to set CnfDesiredSSID\n");
		जाओ failed;
	पूर्ण

	/* bsstype - we use the शेष in the ap firmware */
	/* IBSS port */
	hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFPORTTYPE, 0);

	/* beacon period */
	word = msg->beaconperiod.data;
	result = hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFAPBCNINT, word);
	अगर (result) अणु
		netdev_err(wlandev->netdev,
			   "Failed to set beacon period=%d.\n", word);
		जाओ failed;
	पूर्ण

	/* dschannel */
	word = msg->dschannel.data;
	result = hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFOWNCHANNEL, word);
	अगर (result) अणु
		netdev_err(wlandev->netdev,
			   "Failed to set channel=%d.\n", word);
		जाओ failed;
	पूर्ण
	/* Basic rates */
	word = p80211rate_to_p2bit(msg->basicrate1.data);
	अगर (msg->basicrate2.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->basicrate2.data);

	अगर (msg->basicrate3.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->basicrate3.data);

	अगर (msg->basicrate4.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->basicrate4.data);

	अगर (msg->basicrate5.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->basicrate5.data);

	अगर (msg->basicrate6.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->basicrate6.data);

	अगर (msg->basicrate7.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->basicrate7.data);

	अगर (msg->basicrate8.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->basicrate8.data);

	result = hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFBASICRATES, word);
	अगर (result) अणु
		netdev_err(wlandev->netdev,
			   "Failed to set basicrates=%d.\n", word);
		जाओ failed;
	पूर्ण

	/* Operational rates (supprates and txratecontrol) */
	word = p80211rate_to_p2bit(msg->operationalrate1.data);
	अगर (msg->operationalrate2.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->operationalrate2.data);

	अगर (msg->operationalrate3.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->operationalrate3.data);

	अगर (msg->operationalrate4.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->operationalrate4.data);

	अगर (msg->operationalrate5.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->operationalrate5.data);

	अगर (msg->operationalrate6.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->operationalrate6.data);

	अगर (msg->operationalrate7.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->operationalrate7.data);

	अगर (msg->operationalrate8.status == P80211ENUM_msgitem_status_data_ok)
		word |= p80211rate_to_p2bit(msg->operationalrate8.data);

	result = hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFSUPPRATES, word);
	अगर (result) अणु
		netdev_err(wlandev->netdev,
			   "Failed to set supprates=%d.\n", word);
		जाओ failed;
	पूर्ण

	result = hfa384x_drvr_setconfig16(hw, HFA384x_RID_TXRATECNTL, word);
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to set txrates=%d.\n",
			   word);
		जाओ failed;
	पूर्ण

	/* Set the macmode so the frame setup code knows what to करो */
	अगर (msg->bsstype.data == P80211ENUM_bsstype_independent) अणु
		wlandev->macmode = WLAN_MACMODE_IBSS_STA;
		/* lets extend the data length a bit */
		hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFMAXDATALEN, 2304);
	पूर्ण

	/* Enable the Port */
	result = hfa384x_drvr_enable(hw, 0);
	अगर (result) अणु
		netdev_err(wlandev->netdev,
			   "Enable macport failed, result=%d.\n", result);
		जाओ failed;
	पूर्ण

	msg->resultcode.data = P80211ENUM_resultcode_success;

	जाओ करोne;
failed:
	netdev_dbg(wlandev->netdev,
		   "Failed to set a config option, result=%d\n", result);
	msg->resultcode.data = P80211ENUM_resultcode_invalid_parameters;

करोne:
	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * prism2mgmt_पढ़ोpda
 *
 * Collect the PDA data and put it in the message.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	msgp		ptr to msg buffer
 *
 * Returns:
 *	0	success and करोne
 *	<0	success, but we're रुकोing क्रम something to finish.
 *	>0	an error occurred जबतक handling the message.
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो  (usually)
 *----------------------------------------------------------------
 */
पूर्णांक prism2mgmt_पढ़ोpda(काष्ठा wlandevice *wlandev, व्योम *msgp)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	काष्ठा p80211msg_p2req_पढ़ोpda *msg = msgp;
	पूर्णांक result;

	/* We only support collecting the PDA when in the FWLOAD
	 * state.
	 */
	अगर (wlandev->msdstate != WLAN_MSD_FWLOAD) अणु
		netdev_err(wlandev->netdev,
			   "PDA may only be read in the fwload state.\n");
		msg->resultcode.data =
		    P80211ENUM_resultcode_implementation_failure;
		msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
	पूर्ण अन्यथा अणु
		/*  Call drvr_पढ़ोpda(), it handles the auxport enable
		 *  and validating the वापसed PDA.
		 */
		result = hfa384x_drvr_पढ़ोpda(hw,
					      msg->pda.data,
					      HFA384x_PDA_LEN_MAX);
		अगर (result) अणु
			netdev_err(wlandev->netdev,
				   "hfa384x_drvr_readpda() failed, result=%d\n",
				   result);

			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
			msg->resultcode.status =
			    P80211ENUM_msgitem_status_data_ok;
			वापस 0;
		पूर्ण
		msg->pda.status = P80211ENUM_msgitem_status_data_ok;
		msg->resultcode.data = P80211ENUM_resultcode_success;
		msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
	पूर्ण

	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * prism2mgmt_ramdl_state
 *
 * Establishes the beginning/end of a card RAM करोwnload session.
 *
 * It is expected that the ramdl_ग_लिखो() function will be called
 * one or more बार between the 'enable' and 'disable' calls to
 * this function.
 *
 * Note: This function should not be called when a mac comm port
 *       is active.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	msgp		ptr to msg buffer
 *
 * Returns:
 *	0	success and करोne
 *	<0	success, but we're रुकोing क्रम something to finish.
 *	>0	an error occurred जबतक handling the message.
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो  (usually)
 *----------------------------------------------------------------
 */
पूर्णांक prism2mgmt_ramdl_state(काष्ठा wlandevice *wlandev, व्योम *msgp)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	काष्ठा p80211msg_p2req_ramdl_state *msg = msgp;

	अगर (wlandev->msdstate != WLAN_MSD_FWLOAD) अणु
		netdev_err(wlandev->netdev,
			   "ramdl_state(): may only be called in the fwload state.\n");
		msg->resultcode.data =
		    P80211ENUM_resultcode_implementation_failure;
		msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
		वापस 0;
	पूर्ण

	/*
	 ** Note: Interrupts are locked out अगर this is an AP and are NOT
	 ** locked out अगर this is a station.
	 */

	msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
	अगर (msg->enable.data == P80211ENUM_truth_true) अणु
		अगर (hfa384x_drvr_ramdl_enable(hw, msg->exeaddr.data)) अणु
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
		पूर्ण अन्यथा अणु
			msg->resultcode.data = P80211ENUM_resultcode_success;
		पूर्ण
	पूर्ण अन्यथा अणु
		hfa384x_drvr_ramdl_disable(hw);
		msg->resultcode.data = P80211ENUM_resultcode_success;
	पूर्ण

	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * prism2mgmt_ramdl_ग_लिखो
 *
 * Writes a buffer to the card RAM using the करोwnload state.  This
 * is क्रम writing code to card RAM.  To just पढ़ो or ग_लिखो raw data
 * use the aux functions.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	msgp		ptr to msg buffer
 *
 * Returns:
 *	0	success and करोne
 *	<0	success, but we're रुकोing क्रम something to finish.
 *	>0	an error occurred जबतक handling the message.
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो  (usually)
 *----------------------------------------------------------------
 */
पूर्णांक prism2mgmt_ramdl_ग_लिखो(काष्ठा wlandevice *wlandev, व्योम *msgp)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	काष्ठा p80211msg_p2req_ramdl_ग_लिखो *msg = msgp;
	u32 addr;
	u32 len;
	u8 *buf;

	अगर (wlandev->msdstate != WLAN_MSD_FWLOAD) अणु
		netdev_err(wlandev->netdev,
			   "ramdl_write(): may only be called in the fwload state.\n");
		msg->resultcode.data =
		    P80211ENUM_resultcode_implementation_failure;
		msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
		वापस 0;
	पूर्ण

	msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
	/* first validate the length */
	अगर (msg->len.data > माप(msg->data.data)) अणु
		msg->resultcode.status =
		    P80211ENUM_resultcode_invalid_parameters;
		वापस 0;
	पूर्ण
	/* call the hfa384x function to करो the ग_लिखो */
	addr = msg->addr.data;
	len = msg->len.data;
	buf = msg->data.data;
	अगर (hfa384x_drvr_ramdl_ग_लिखो(hw, addr, buf, len))
		msg->resultcode.data = P80211ENUM_resultcode_refused;

	msg->resultcode.data = P80211ENUM_resultcode_success;

	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * prism2mgmt_flashdl_state
 *
 * Establishes the beginning/end of a card Flash करोwnload session.
 *
 * It is expected that the flashdl_ग_लिखो() function will be called
 * one or more बार between the 'enable' and 'disable' calls to
 * this function.
 *
 * Note: This function should not be called when a mac comm port
 *       is active.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	msgp		ptr to msg buffer
 *
 * Returns:
 *	0	success and करोne
 *	<0	success, but we're रुकोing क्रम something to finish.
 *	>0	an error occurred जबतक handling the message.
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो  (usually)
 *----------------------------------------------------------------
 */
पूर्णांक prism2mgmt_flashdl_state(काष्ठा wlandevice *wlandev, व्योम *msgp)
अणु
	पूर्णांक result = 0;
	काष्ठा hfa384x *hw = wlandev->priv;
	काष्ठा p80211msg_p2req_flashdl_state *msg = msgp;

	अगर (wlandev->msdstate != WLAN_MSD_FWLOAD) अणु
		netdev_err(wlandev->netdev,
			   "flashdl_state(): may only be called in the fwload state.\n");
		msg->resultcode.data =
		    P80211ENUM_resultcode_implementation_failure;
		msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
		वापस 0;
	पूर्ण

	/*
	 ** Note: Interrupts are locked out अगर this is an AP and are NOT
	 ** locked out अगर this is a station.
	 */

	msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
	अगर (msg->enable.data == P80211ENUM_truth_true) अणु
		अगर (hfa384x_drvr_flashdl_enable(hw)) अणु
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
		पूर्ण अन्यथा अणु
			msg->resultcode.data = P80211ENUM_resultcode_success;
		पूर्ण
	पूर्ण अन्यथा अणु
		hfa384x_drvr_flashdl_disable(hw);
		msg->resultcode.data = P80211ENUM_resultcode_success;
		/* NOTE: At this poपूर्णांक, the MAC is in the post-reset
		 * state and the driver is in the fwload state.
		 * We need to get the MAC back पूर्णांकo the fwload
		 * state.  To करो this, we set the nsdstate to HWPRESENT
		 * and then call the अगरstate function to reकरो everything
		 * that got us पूर्णांकo the fwload state.
		 */
		wlandev->msdstate = WLAN_MSD_HWPRESENT;
		result = prism2sta_अगरstate(wlandev, P80211ENUM_अगरstate_fwload);
		अगर (result != P80211ENUM_resultcode_success) अणु
			netdev_err(wlandev->netdev,
				   "prism2sta_ifstate(fwload) failed, P80211ENUM_resultcode=%d\n",
				   result);
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
			result = -1;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * prism2mgmt_flashdl_ग_लिखो
 *
 *
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	msgp		ptr to msg buffer
 *
 * Returns:
 *	0	success and करोne
 *	<0	success, but we're रुकोing क्रम something to finish.
 *	>0	an error occurred जबतक handling the message.
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो  (usually)
 *----------------------------------------------------------------
 */
पूर्णांक prism2mgmt_flashdl_ग_लिखो(काष्ठा wlandevice *wlandev, व्योम *msgp)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	काष्ठा p80211msg_p2req_flashdl_ग_लिखो *msg = msgp;
	u32 addr;
	u32 len;
	u8 *buf;

	अगर (wlandev->msdstate != WLAN_MSD_FWLOAD) अणु
		netdev_err(wlandev->netdev,
			   "flashdl_write(): may only be called in the fwload state.\n");
		msg->resultcode.data =
		    P80211ENUM_resultcode_implementation_failure;
		msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
		वापस 0;
	पूर्ण

	/*
	 ** Note: Interrupts are locked out अगर this is an AP and are NOT
	 ** locked out अगर this is a station.
	 */

	msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
	/* first validate the length */
	अगर (msg->len.data > माप(msg->data.data)) अणु
		msg->resultcode.status =
		    P80211ENUM_resultcode_invalid_parameters;
		वापस 0;
	पूर्ण
	/* call the hfa384x function to करो the ग_लिखो */
	addr = msg->addr.data;
	len = msg->len.data;
	buf = msg->data.data;
	अगर (hfa384x_drvr_flashdl_ग_लिखो(hw, addr, buf, len))
		msg->resultcode.data = P80211ENUM_resultcode_refused;

	msg->resultcode.data = P80211ENUM_resultcode_success;

	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * prism2mgmt_स्वतःjoin
 *
 * Associate with an ESS.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	msgp		ptr to msg buffer
 *
 * Returns:
 *	0	success and करोne
 *	<0	success, but we're रुकोing क्रम something to finish.
 *	>0	an error occurred जबतक handling the message.
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो  (usually)
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
पूर्णांक prism2mgmt_स्वतःjoin(काष्ठा wlandevice *wlandev, व्योम *msgp)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	पूर्णांक result = 0;
	u16 reg;
	u16 port_type;
	काष्ठा p80211msg_lnxreq_स्वतःjoin *msg = msgp;
	काष्ठा p80211pstrd *pstr;
	u8 bytebuf[256];
	काष्ठा hfa384x_bytestr *p2bytestr = (काष्ठा hfa384x_bytestr *)bytebuf;

	wlandev->macmode = WLAN_MACMODE_NONE;

	/* Set the SSID */
	स_नकल(&wlandev->ssid, &msg->ssid.data, माप(msg->ssid.data));

	/* Disable the Port */
	hfa384x_drvr_disable(hw, 0);

	/*** STATION ***/
	/* Set the TxRates */
	hfa384x_drvr_setconfig16(hw, HFA384x_RID_TXRATECNTL, 0x000f);

	/* Set the auth type */
	अगर (msg->authtype.data == P80211ENUM_authalg_sharedkey)
		reg = HFA384x_CNFAUTHENTICATION_SHAREDKEY;
	अन्यथा
		reg = HFA384x_CNFAUTHENTICATION_OPENSYSTEM;

	hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFAUTHENTICATION, reg);

	/* Set the ssid */
	स_रखो(bytebuf, 0, 256);
	pstr = (काष्ठा p80211pstrd *)&msg->ssid.data;
	prism2mgmt_pstr2bytestr(p2bytestr, pstr);
	result = hfa384x_drvr_setconfig(hw, HFA384x_RID_CNFDESIREDSSID,
					bytebuf,
					HFA384x_RID_CNFDESIREDSSID_LEN);
	port_type = HFA384x_PORTTYPE_BSS;
	/* Set the PortType */
	hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFPORTTYPE, port_type);

	/* Enable the Port */
	hfa384x_drvr_enable(hw, 0);

	/* Set the resultcode */
	msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
	msg->resultcode.data = P80211ENUM_resultcode_success;

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * prism2mgmt_wlansnअगरf
 *
 * Start or stop snअगरfing.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	msgp		ptr to msg buffer
 *
 * Returns:
 *	0	success and करोne
 *	<0	success, but we're रुकोing क्रम something to finish.
 *	>0	an error occurred जबतक handling the message.
 * Side effects:
 *
 * Call context:
 *	process thपढ़ो  (usually)
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
पूर्णांक prism2mgmt_wlansnअगरf(काष्ठा wlandevice *wlandev, व्योम *msgp)
अणु
	पूर्णांक result = 0;
	काष्ठा p80211msg_lnxreq_wlansnअगरf *msg = msgp;

	काष्ठा hfa384x *hw = wlandev->priv;
	u16 word;

	msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
	चयन (msg->enable.data) अणु
	हाल P80211ENUM_truth_false:
		/* Confirm that we're in monitor mode */
		अगर (wlandev->netdev->type == ARPHRD_ETHER) अणु
			msg->resultcode.data =
			    P80211ENUM_resultcode_invalid_parameters;
			वापस 0;
		पूर्ण
		/* Disable monitor mode */
		result = hfa384x_cmd_monitor(hw, HFA384x_MONITOR_DISABLE);
		अगर (result) अणु
			netdev_dbg(wlandev->netdev,
				   "failed to disable monitor mode, result=%d\n",
				   result);
			जाओ failed;
		पूर्ण
		/* Disable port 0 */
		result = hfa384x_drvr_disable(hw, 0);
		अगर (result) अणु
			netdev_dbg
			(wlandev->netdev,
			     "failed to disable port 0 after sniffing, result=%d\n",
			     result);
			जाओ failed;
		पूर्ण
		/* Clear the driver state */
		wlandev->netdev->type = ARPHRD_ETHER;

		/* Restore the wepflags */
		result = hfa384x_drvr_setconfig16(hw,
						  HFA384x_RID_CNFWEPFLAGS,
						  hw->presnअगरf_wepflags);
		अगर (result) अणु
			netdev_dbg
			    (wlandev->netdev,
			     "failed to restore wepflags=0x%04x, result=%d\n",
			     hw->presnअगरf_wepflags, result);
			जाओ failed;
		पूर्ण

		/* Set the port to its prior type and enable (अगर necessary) */
		अगर (hw->presnअगरf_port_type != 0) अणु
			word = hw->presnअगरf_port_type;
			result = hfa384x_drvr_setconfig16(hw,
							  HFA384x_RID_CNFPORTTYPE,
							  word);
			अगर (result) अणु
				netdev_dbg
				    (wlandev->netdev,
				     "failed to restore porttype, result=%d\n",
				     result);
				जाओ failed;
			पूर्ण

			/* Enable the port */
			result = hfa384x_drvr_enable(hw, 0);
			अगर (result) अणु
				netdev_dbg(wlandev->netdev,
					   "failed to enable port to presniff setting, result=%d\n",
					   result);
				जाओ failed;
			पूर्ण
		पूर्ण अन्यथा अणु
			result = hfa384x_drvr_disable(hw, 0);
		पूर्ण

		netdev_info(wlandev->netdev, "monitor mode disabled\n");
		msg->resultcode.data = P80211ENUM_resultcode_success;
		वापस 0;
	हाल P80211ENUM_truth_true:
		/* Disable the port (अगर enabled), only check Port 0 */
		अगर (hw->port_enabled[0]) अणु
			अगर (wlandev->netdev->type == ARPHRD_ETHER) अणु
				/* Save macport 0 state */
				result = hfa384x_drvr_अ_लोonfig16(hw,
								  HFA384x_RID_CNFPORTTYPE,
								  &hw->presnअगरf_port_type);
				अगर (result) अणु
					netdev_dbg
					(wlandev->netdev,
					     "failed to read porttype, result=%d\n",
					     result);
					जाओ failed;
				पूर्ण
				/* Save the wepflags state */
				result = hfa384x_drvr_अ_लोonfig16(hw,
								  HFA384x_RID_CNFWEPFLAGS,
								  &hw->presnअगरf_wepflags);
				अगर (result) अणु
					netdev_dbg
					(wlandev->netdev,
					     "failed to read wepflags, result=%d\n",
					     result);
					जाओ failed;
				पूर्ण
				hfa384x_drvr_stop(hw);
				result = hfa384x_drvr_start(hw);
				अगर (result) अणु
					netdev_dbg(wlandev->netdev,
						   "failed to restart the card for sniffing, result=%d\n",
						   result);
					जाओ failed;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Disable the port */
				result = hfa384x_drvr_disable(hw, 0);
				अगर (result) अणु
					netdev_dbg(wlandev->netdev,
						   "failed to enable port for sniffing, result=%d\n",
						   result);
					जाओ failed;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			hw->presnअगरf_port_type = 0;
		पूर्ण

		/* Set the channel we wish to snअगरf  */
		word = msg->channel.data;
		result = hfa384x_drvr_setconfig16(hw,
						  HFA384x_RID_CNFOWNCHANNEL,
						  word);
		hw->snअगरf_channel = word;

		अगर (result) अणु
			netdev_dbg(wlandev->netdev,
				   "failed to set channel %d, result=%d\n",
				   word, result);
			जाओ failed;
		पूर्ण

		/* Now अगर we're alपढ़ोy snअगरfing, we can skip the rest */
		अगर (wlandev->netdev->type != ARPHRD_ETHER) अणु
			/* Set the port type to pIbss */
			word = HFA384x_PORTTYPE_PSUEDOIBSS;
			result = hfa384x_drvr_setconfig16(hw,
							  HFA384x_RID_CNFPORTTYPE,
							  word);
			अगर (result) अणु
				netdev_dbg
				    (wlandev->netdev,
				     "failed to set porttype %d, result=%d\n",
				     word, result);
				जाओ failed;
			पूर्ण
			अगर ((msg->keepwepflags.status ==
			     P80211ENUM_msgitem_status_data_ok) &&
			    (msg->keepwepflags.data != P80211ENUM_truth_true)) अणु
				/* Set the wepflags क्रम no decryption */
				word = HFA384x_WEPFLAGS_DISABLE_TXCRYPT |
				    HFA384x_WEPFLAGS_DISABLE_RXCRYPT;
				result =
				    hfa384x_drvr_setconfig16(hw,
							     HFA384x_RID_CNFWEPFLAGS,
							     word);
			पूर्ण

			अगर (result) अणु
				netdev_dbg
				  (wlandev->netdev,
				   "failed to set wepflags=0x%04x, result=%d\n",
				   word, result);
				जाओ failed;
			पूर्ण
		पूर्ण

		/* Do we want to strip the FCS in monitor mode? */
		अगर ((msg->stripfcs.status ==
		     P80211ENUM_msgitem_status_data_ok) &&
		    (msg->stripfcs.data == P80211ENUM_truth_true)) अणु
			hw->snअगरf_fcs = 0;
		पूर्ण अन्यथा अणु
			hw->snअगरf_fcs = 1;
		पूर्ण

		/* Do we want to truncate the packets? */
		अगर (msg->packet_trunc.status ==
		    P80211ENUM_msgitem_status_data_ok) अणु
			hw->snअगरf_truncate = msg->packet_trunc.data;
		पूर्ण अन्यथा अणु
			hw->snअगरf_truncate = 0;
		पूर्ण

		/* Enable the port */
		result = hfa384x_drvr_enable(hw, 0);
		अगर (result) अणु
			netdev_dbg
			    (wlandev->netdev,
			     "failed to enable port for sniffing, result=%d\n",
			     result);
			जाओ failed;
		पूर्ण
		/* Enable monitor mode */
		result = hfa384x_cmd_monitor(hw, HFA384x_MONITOR_ENABLE);
		अगर (result) अणु
			netdev_dbg(wlandev->netdev,
				   "failed to enable monitor mode, result=%d\n",
				   result);
			जाओ failed;
		पूर्ण

		अगर (wlandev->netdev->type == ARPHRD_ETHER)
			netdev_info(wlandev->netdev, "monitor mode enabled\n");

		/* Set the driver state */
		/* Do we want the prism2 header? */
		अगर ((msg->prismheader.status ==
		     P80211ENUM_msgitem_status_data_ok) &&
		    (msg->prismheader.data == P80211ENUM_truth_true)) अणु
			hw->snअगरfhdr = 0;
			wlandev->netdev->type = ARPHRD_IEEE80211_PRISM;
		पूर्ण अन्यथा अगर ((msg->wlanheader.status ==
			    P80211ENUM_msgitem_status_data_ok) &&
			   (msg->wlanheader.data == P80211ENUM_truth_true)) अणु
			hw->snअगरfhdr = 1;
			wlandev->netdev->type = ARPHRD_IEEE80211_PRISM;
		पूर्ण अन्यथा अणु
			wlandev->netdev->type = ARPHRD_IEEE80211;
		पूर्ण

		msg->resultcode.data = P80211ENUM_resultcode_success;
		वापस 0;
	शेष:
		msg->resultcode.data = P80211ENUM_resultcode_invalid_parameters;
		वापस 0;
	पूर्ण

failed:
	msg->resultcode.data = P80211ENUM_resultcode_refused;
	वापस 0;
पूर्ण
