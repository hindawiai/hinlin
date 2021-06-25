<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1)
/* src/prism2/driver/prism2mib.c
 *
 * Management request क्रम mibset/mibget
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
 * The functions in this file handle the mibset/mibget management
 * functions.
 *
 * --------------------------------------------------------------------
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/wireless.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <यंत्र/byteorder.h>
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

#घोषणा MIB_क्षणिक_उच्चLEN    200	/* Max length of RID record (in bytes). */

#घोषणा  F_STA        0x1	/* MIB is supported on stations. */
#घोषणा  F_READ       0x2	/* MIB may be पढ़ो. */
#घोषणा  F_WRITE      0x4	/* MIB may be written. */

काष्ठा mibrec अणु
	u32 did;
	u16 flag;
	u16 parm1;
	u16 parm2;
	u16 parm3;
	पूर्णांक (*func)(काष्ठा mibrec *mib,
		    पूर्णांक isget,
		    काष्ठा wlandevice *wlandev,
		    काष्ठा hfa384x *hw,
		    काष्ठा p80211msg_करोt11req_mibset *msg, व्योम *data);
पूर्ण;

अटल पूर्णांक prism2mib_bytearea2pstr(काष्ठा mibrec *mib,
				   पूर्णांक isget,
				   काष्ठा wlandevice *wlandev,
				   काष्ठा hfa384x *hw,
				   काष्ठा p80211msg_करोt11req_mibset *msg,
				   व्योम *data);

अटल पूर्णांक prism2mib_uपूर्णांक32(काष्ठा mibrec *mib,
			    पूर्णांक isget,
			    काष्ठा wlandevice *wlandev,
			    काष्ठा hfa384x *hw,
			    काष्ठा p80211msg_करोt11req_mibset *msg, व्योम *data);

अटल पूर्णांक prism2mib_flag(काष्ठा mibrec *mib,
			  पूर्णांक isget,
			  काष्ठा wlandevice *wlandev,
			  काष्ठा hfa384x *hw,
			  काष्ठा p80211msg_करोt11req_mibset *msg, व्योम *data);

अटल पूर्णांक prism2mib_wepशेषkey(काष्ठा mibrec *mib,
				   पूर्णांक isget,
				   काष्ठा wlandevice *wlandev,
				   काष्ठा hfa384x *hw,
				   काष्ठा p80211msg_करोt11req_mibset *msg,
				   व्योम *data);

अटल पूर्णांक prism2mib_privacyinvoked(काष्ठा mibrec *mib,
				    पूर्णांक isget,
				    काष्ठा wlandevice *wlandev,
				    काष्ठा hfa384x *hw,
				    काष्ठा p80211msg_करोt11req_mibset *msg,
				    व्योम *data);

अटल पूर्णांक
prism2mib_fragmentationthreshold(काष्ठा mibrec *mib,
				 पूर्णांक isget,
				 काष्ठा wlandevice *wlandev,
				 काष्ठा hfa384x *hw,
				 काष्ठा p80211msg_करोt11req_mibset *msg,
				 व्योम *data);

अटल पूर्णांक prism2mib_priv(काष्ठा mibrec *mib,
			  पूर्णांक isget,
			  काष्ठा wlandevice *wlandev,
			  काष्ठा hfa384x *hw,
			  काष्ठा p80211msg_करोt11req_mibset *msg, व्योम *data);

अटल काष्ठा mibrec mibtab[] = अणु
	/* करोt11smt MIB's */
	अणुdidmib_करोt11smt_wepशेषkeystable_key(1),
	 F_STA | F_WRITE,
	 HFA384x_RID_CNFWEPDEFAULTKEY0, 0, 0,
	 prism2mib_wepशेषkeyपूर्ण,
	अणुdidmib_करोt11smt_wepशेषkeystable_key(2),
	 F_STA | F_WRITE,
	 HFA384x_RID_CNFWEPDEFAULTKEY1, 0, 0,
	 prism2mib_wepशेषkeyपूर्ण,
	अणुdidmib_करोt11smt_wepशेषkeystable_key(3),
	 F_STA | F_WRITE,
	 HFA384x_RID_CNFWEPDEFAULTKEY2, 0, 0,
	 prism2mib_wepशेषkeyपूर्ण,
	अणुdidmib_करोt11smt_wepशेषkeystable_key(4),
	 F_STA | F_WRITE,
	 HFA384x_RID_CNFWEPDEFAULTKEY3, 0, 0,
	 prism2mib_wepशेषkeyपूर्ण,
	अणुDIDMIB_DOT11SMT_PRIVACYTABLE_PRIVACYINVOKED,
	 F_STA | F_READ | F_WRITE,
	 HFA384x_RID_CNFWEPFLAGS, HFA384x_WEPFLAGS_PRIVINVOKED, 0,
	 prism2mib_privacyinvokedपूर्ण,
	अणुDIDMIB_DOT11SMT_PRIVACYTABLE_WEPDEFAULTKEYID,
	 F_STA | F_READ | F_WRITE,
	 HFA384x_RID_CNFWEPDEFAULTKEYID, 0, 0,
	 prism2mib_uपूर्णांक32पूर्ण,
	अणुDIDMIB_DOT11SMT_PRIVACYTABLE_EXCLUDEUNENCRYPTED,
	 F_STA | F_READ | F_WRITE,
	 HFA384x_RID_CNFWEPFLAGS, HFA384x_WEPFLAGS_EXCLUDE, 0,
	 prism2mib_flagपूर्ण,

	/* करोt11mac MIB's */

	अणुDIDMIB_DOT11MAC_OPERATIONTABLE_MACADDRESS,
	 F_STA | F_READ | F_WRITE,
	 HFA384x_RID_CNFOWNMACADDR, HFA384x_RID_CNFOWNMACADDR_LEN, 0,
	 prism2mib_bytearea2pstrपूर्ण,
	अणुDIDMIB_DOT11MAC_OPERATIONTABLE_RTSTHRESHOLD,
	 F_STA | F_READ | F_WRITE,
	 HFA384x_RID_RTSTHRESH, 0, 0,
	 prism2mib_uपूर्णांक32पूर्ण,
	अणुDIDMIB_DOT11MAC_OPERATIONTABLE_SHORTRETRYLIMIT,
	 F_STA | F_READ,
	 HFA384x_RID_SHORTRETRYLIMIT, 0, 0,
	 prism2mib_uपूर्णांक32पूर्ण,
	अणुDIDMIB_DOT11MAC_OPERATIONTABLE_LONGRETRYLIMIT,
	 F_STA | F_READ,
	 HFA384x_RID_LONGRETRYLIMIT, 0, 0,
	 prism2mib_uपूर्णांक32पूर्ण,
	अणुDIDMIB_DOT11MAC_OPERATIONTABLE_FRAGMENTATIONTHRESHOLD,
	 F_STA | F_READ | F_WRITE,
	 HFA384x_RID_FRAGTHRESH, 0, 0,
	 prism2mib_fragmentationthresholdपूर्ण,
	अणुDIDMIB_DOT11MAC_OPERATIONTABLE_MAXTRANSMITMSDULIFETIME,
	 F_STA | F_READ,
	 HFA384x_RID_MAXTXLIFETIME, 0, 0,
	 prism2mib_uपूर्णांक32पूर्ण,

	/* करोt11phy MIB's */

	अणुDIDMIB_DOT11PHY_DSSSTABLE_CURRENTCHANNEL,
	 F_STA | F_READ,
	 HFA384x_RID_CURRENTCHANNEL, 0, 0,
	 prism2mib_uपूर्णांक32पूर्ण,
	अणुDIDMIB_DOT11PHY_TXPOWERTABLE_CURRENTTXPOWERLEVEL,
	 F_STA | F_READ | F_WRITE,
	 HFA384x_RID_TXPOWERMAX, 0, 0,
	 prism2mib_uपूर्णांक32पूर्ण,

	/* p2Static MIB's */

	अणुDIDMIB_P2_STATIC_CNFPORTTYPE,
	 F_STA | F_READ | F_WRITE,
	 HFA384x_RID_CNFPORTTYPE, 0, 0,
	 prism2mib_uपूर्णांक32पूर्ण,

	/* p2MAC MIB's */

	अणुDIDMIB_P2_MAC_CURRENTTXRATE,
	 F_STA | F_READ,
	 HFA384x_RID_CURRENTTXRATE, 0, 0,
	 prism2mib_uपूर्णांक32पूर्ण,

	/* And finally, lnx mibs */
	अणुDIDMIB_LNX_CONFIGTABLE_RSNAIE,
	 F_STA | F_READ | F_WRITE,
	 HFA384x_RID_CNFWPADATA, 0, 0,
	 prism2mib_privपूर्ण,
	अणु0, 0, 0, 0, 0, शून्यपूर्ण
पूर्ण;

/*
 * prism2mgmt_mibset_mibget
 *
 * Set the value of a mib item.
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
 */

पूर्णांक prism2mgmt_mibset_mibget(काष्ठा wlandevice *wlandev, व्योम *msgp)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	पूर्णांक result, isget;
	काष्ठा mibrec *mib;

	u16 which;

	काष्ठा p80211msg_करोt11req_mibset *msg = msgp;
	काष्ठा p80211itemd *mibitem;

	msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
	msg->resultcode.data = P80211ENUM_resultcode_success;

	/*
	 ** Determine अगर this is an Access Poपूर्णांक or a station.
	 */

	which = F_STA;

	/*
	 ** Find the MIB in the MIB table.  Note that a MIB may be in the
	 ** table twice...once क्रम an AP and once क्रम a station.  Make sure
	 ** to get the correct one.  Note that DID=0 marks the end of the
	 ** MIB table.
	 */

	mibitem = (काष्ठा p80211itemd *)msg->mibattribute.data;

	क्रम (mib = mibtab; mib->did != 0; mib++)
		अगर (mib->did == mibitem->did && (mib->flag & which))
			अवरोध;

	अगर (mib->did == 0) अणु
		msg->resultcode.data = P80211ENUM_resultcode_not_supported;
		जाओ करोne;
	पूर्ण

	/*
	 ** Determine अगर this is a "mibget" or a "mibset".  If this is a
	 ** "mibget", then make sure that the MIB may be पढ़ो.  Otherwise,
	 ** this is a "mibset" so make sure that the MIB may be written.
	 */

	isget = (msg->msgcode == DIDMSG_DOT11REQ_MIBGET);

	अगर (isget) अणु
		अगर (!(mib->flag & F_READ)) अणु
			msg->resultcode.data =
			    P80211ENUM_resultcode_cant_get_ग_लिखोonly_mib;
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(mib->flag & F_WRITE)) अणु
			msg->resultcode.data =
			    P80211ENUM_resultcode_cant_set_पढ़ोonly_mib;
			जाओ करोne;
		पूर्ण
	पूर्ण

	/*
	 ** Execute the MIB function.  If things worked okay, then make
	 ** sure that the MIB function also worked okay.  If so, and this
	 ** is a "mibget", then the status value must be set क्रम both the
	 ** "mibattribute" parameter and the mib item within the data
	 ** portion of the "mibattribute".
	 */

	result = mib->func(mib, isget, wlandev, hw, msg, (व्योम *)mibitem->data);

	अगर (msg->resultcode.data == P80211ENUM_resultcode_success) अणु
		अगर (result != 0) अणु
			pr_debug("get/set failure, result=%d\n", result);
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
		पूर्ण अन्यथा अणु
			अगर (isget) अणु
				msg->mibattribute.status =
				    P80211ENUM_msgitem_status_data_ok;
				mibitem->status =
				    P80211ENUM_msgitem_status_data_ok;
			पूर्ण
		पूर्ण
	पूर्ण

करोne:
	वापस 0;
पूर्ण

/*
 * prism2mib_bytearea2pstr
 *
 * Get/set pstr data to/from a byte area.
 *
 * MIB record parameters:
 *       parm1    Prism2 RID value.
 *       parm2    Number of bytes of RID data.
 *       parm3    Not used.
 *
 * Arguments:
 *       mib      MIB record.
 *       isget    MIBGET/MIBSET flag.
 *       wlandev  wlan device काष्ठाure.
 *       priv     "priv" काष्ठाure.
 *       hw       "hw" काष्ठाure.
 *       msg      Message काष्ठाure.
 *       data     Data buffer.
 *
 * Returns:
 *       0   - Success.
 *       ~0  - Error.
 *
 */

अटल पूर्णांक prism2mib_bytearea2pstr(काष्ठा mibrec *mib,
				   पूर्णांक isget,
				   काष्ठा wlandevice *wlandev,
				   काष्ठा hfa384x *hw,
				   काष्ठा p80211msg_करोt11req_mibset *msg,
				   व्योम *data)
अणु
	पूर्णांक result;
	काष्ठा p80211pstrd *pstr = data;
	u8 bytebuf[MIB_क्षणिक_उच्चLEN];

	अगर (isget) अणु
		result =
		    hfa384x_drvr_अ_लोonfig(hw, mib->parm1, bytebuf, mib->parm2);
		prism2mgmt_bytearea2pstr(bytebuf, pstr, mib->parm2);
	पूर्ण अन्यथा अणु
		स_रखो(bytebuf, 0, mib->parm2);
		स_नकल(bytebuf, pstr->data, pstr->len);
		result =
		    hfa384x_drvr_setconfig(hw, mib->parm1, bytebuf, mib->parm2);
	पूर्ण

	वापस result;
पूर्ण

/*
 * prism2mib_uपूर्णांक32
 *
 * Get/set uपूर्णांक32 data.
 *
 * MIB record parameters:
 *       parm1    Prism2 RID value.
 *       parm2    Not used.
 *       parm3    Not used.
 *
 * Arguments:
 *       mib      MIB record.
 *       isget    MIBGET/MIBSET flag.
 *       wlandev  wlan device काष्ठाure.
 *       priv     "priv" काष्ठाure.
 *       hw       "hw" काष्ठाure.
 *       msg      Message काष्ठाure.
 *       data     Data buffer.
 *
 * Returns:
 *       0   - Success.
 *       ~0  - Error.
 *
 */

अटल पूर्णांक prism2mib_uपूर्णांक32(काष्ठा mibrec *mib,
			    पूर्णांक isget,
			    काष्ठा wlandevice *wlandev,
			    काष्ठा hfa384x *hw,
			    काष्ठा p80211msg_करोt11req_mibset *msg, व्योम *data)
अणु
	पूर्णांक result;
	u32 *uपूर्णांक32 = data;
	u8 bytebuf[MIB_क्षणिक_उच्चLEN];
	u16 *wordbuf = (u16 *)bytebuf;

	अगर (isget) अणु
		result = hfa384x_drvr_अ_लोonfig16(hw, mib->parm1, wordbuf);
		*uपूर्णांक32 = *wordbuf;
	पूर्ण अन्यथा अणु
		*wordbuf = *uपूर्णांक32;
		result = hfa384x_drvr_setconfig16(hw, mib->parm1, *wordbuf);
	पूर्ण

	वापस result;
पूर्ण

/*
 * prism2mib_flag
 *
 * Get/set a flag.
 *
 * MIB record parameters:
 *       parm1    Prism2 RID value.
 *       parm2    Bit to get/set.
 *       parm3    Not used.
 *
 * Arguments:
 *       mib      MIB record.
 *       isget    MIBGET/MIBSET flag.
 *       wlandev  wlan device काष्ठाure.
 *       priv     "priv" काष्ठाure.
 *       hw       "hw" काष्ठाure.
 *       msg      Message काष्ठाure.
 *       data     Data buffer.
 *
 * Returns:
 *       0   - Success.
 *       ~0  - Error.
 *
 */

अटल पूर्णांक prism2mib_flag(काष्ठा mibrec *mib,
			  पूर्णांक isget,
			  काष्ठा wlandevice *wlandev,
			  काष्ठा hfa384x *hw,
			  काष्ठा p80211msg_करोt11req_mibset *msg, व्योम *data)
अणु
	पूर्णांक result;
	u32 *uपूर्णांक32 = data;
	u8 bytebuf[MIB_क्षणिक_उच्चLEN];
	u16 *wordbuf = (u16 *)bytebuf;
	u32 flags;

	result = hfa384x_drvr_अ_लोonfig16(hw, mib->parm1, wordbuf);
	अगर (result == 0) अणु
		flags = *wordbuf;
		अगर (isget) अणु
			*uपूर्णांक32 = (flags & mib->parm2) ?
			    P80211ENUM_truth_true : P80211ENUM_truth_false;
		पूर्ण अन्यथा अणु
			अगर ((*uपूर्णांक32) == P80211ENUM_truth_true)
				flags |= mib->parm2;
			अन्यथा
				flags &= ~mib->parm2;
			*wordbuf = flags;
			result =
			    hfa384x_drvr_setconfig16(hw, mib->parm1, *wordbuf);
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

/*
 * prism2mib_wepशेषkey
 *
 * Get/set WEP शेष keys.
 *
 * MIB record parameters:
 *       parm1    Prism2 RID value.
 *       parm2    Number of bytes of RID data.
 *       parm3    Not used.
 *
 * Arguments:
 *       mib      MIB record.
 *       isget    MIBGET/MIBSET flag.
 *       wlandev  wlan device काष्ठाure.
 *       priv     "priv" काष्ठाure.
 *       hw       "hw" काष्ठाure.
 *       msg      Message काष्ठाure.
 *       data     Data buffer.
 *
 * Returns:
 *       0   - Success.
 *       ~0  - Error.
 *
 */

अटल पूर्णांक prism2mib_wepशेषkey(काष्ठा mibrec *mib,
				   पूर्णांक isget,
				   काष्ठा wlandevice *wlandev,
				   काष्ठा hfa384x *hw,
				   काष्ठा p80211msg_करोt11req_mibset *msg,
				   व्योम *data)
अणु
	पूर्णांक result;
	काष्ठा p80211pstrd *pstr = data;
	u8 bytebuf[MIB_क्षणिक_उच्चLEN];
	u16 len;

	अगर (isget) अणु
		result = 0;	/* Should never happen. */
	पूर्ण अन्यथा अणु
		len = (pstr->len > 5) ? HFA384x_RID_CNFWEP128DEFAULTKEY_LEN :
		    HFA384x_RID_CNFWEPDEFAULTKEY_LEN;
		स_रखो(bytebuf, 0, len);
		स_नकल(bytebuf, pstr->data, pstr->len);
		result = hfa384x_drvr_setconfig(hw, mib->parm1, bytebuf, len);
	पूर्ण

	वापस result;
पूर्ण

/*
 * prism2mib_privacyinvoked
 *
 * Get/set the करोt11PrivacyInvoked value.
 *
 * MIB record parameters:
 *       parm1    Prism2 RID value.
 *       parm2    Bit value क्रम PrivacyInvoked flag.
 *       parm3    Not used.
 *
 * Arguments:
 *       mib      MIB record.
 *       isget    MIBGET/MIBSET flag.
 *       wlandev  wlan device काष्ठाure.
 *       priv     "priv" काष्ठाure.
 *       hw       "hw" काष्ठाure.
 *       msg      Message काष्ठाure.
 *       data     Data buffer.
 *
 * Returns:
 *       0   - Success.
 *       ~0  - Error.
 *
 */

अटल पूर्णांक prism2mib_privacyinvoked(काष्ठा mibrec *mib,
				    पूर्णांक isget,
				    काष्ठा wlandevice *wlandev,
				    काष्ठा hfa384x *hw,
				    काष्ठा p80211msg_करोt11req_mibset *msg,
				    व्योम *data)
अणु
	अगर (wlandev->hostwep & HOSTWEP_DECRYPT) अणु
		अगर (wlandev->hostwep & HOSTWEP_DECRYPT)
			mib->parm2 |= HFA384x_WEPFLAGS_DISABLE_RXCRYPT;
		अगर (wlandev->hostwep & HOSTWEP_ENCRYPT)
			mib->parm2 |= HFA384x_WEPFLAGS_DISABLE_TXCRYPT;
	पूर्ण

	वापस prism2mib_flag(mib, isget, wlandev, hw, msg, data);
पूर्ण

/*
 * prism2mib_fragmentationthreshold
 *
 * Get/set the fragmentation threshold.
 *
 * MIB record parameters:
 *       parm1    Prism2 RID value.
 *       parm2    Not used.
 *       parm3    Not used.
 *
 * Arguments:
 *       mib      MIB record.
 *       isget    MIBGET/MIBSET flag.
 *       wlandev  wlan device काष्ठाure.
 *       priv     "priv" काष्ठाure.
 *       hw       "hw" काष्ठाure.
 *       msg      Message काष्ठाure.
 *       data     Data buffer.
 *
 * Returns:
 *       0   - Success.
 *       ~0  - Error.
 *
 */

अटल पूर्णांक
prism2mib_fragmentationthreshold(काष्ठा mibrec *mib,
				 पूर्णांक isget,
				 काष्ठा wlandevice *wlandev,
				 काष्ठा hfa384x *hw,
				 काष्ठा p80211msg_करोt11req_mibset *msg,
				 व्योम *data)
अणु
	u32 *uपूर्णांक32 = data;

	अगर (!isget)
		अगर ((*uपूर्णांक32) % 2) अणु
			netdev_warn(wlandev->netdev,
				    "Attempt to set odd number FragmentationThreshold\n");
			msg->resultcode.data =
			    P80211ENUM_resultcode_not_supported;
			वापस 0;
		पूर्ण

	वापस prism2mib_uपूर्णांक32(mib, isget, wlandev, hw, msg, data);
पूर्ण

/*
 * prism2mib_priv
 *
 * Get/set values in the "priv" data काष्ठाure.
 *
 * MIB record parameters:
 *       parm1    Not used.
 *       parm2    Not used.
 *       parm3    Not used.
 *
 * Arguments:
 *       mib      MIB record.
 *       isget    MIBGET/MIBSET flag.
 *       wlandev  wlan device काष्ठाure.
 *       priv     "priv" काष्ठाure.
 *       hw       "hw" काष्ठाure.
 *       msg      Message काष्ठाure.
 *       data     Data buffer.
 *
 * Returns:
 *       0   - Success.
 *       ~0  - Error.
 *
 */

अटल पूर्णांक prism2mib_priv(काष्ठा mibrec *mib,
			  पूर्णांक isget,
			  काष्ठा wlandevice *wlandev,
			  काष्ठा hfa384x *hw,
			  काष्ठा p80211msg_करोt11req_mibset *msg, व्योम *data)
अणु
	काष्ठा p80211pstrd *pstr = data;

	चयन (mib->did) अणु
	हाल DIDMIB_LNX_CONFIGTABLE_RSNAIE: अणु
		काष्ठा hfa384x_wpa_data wpa;

		अगर (isget) अणु
			hfa384x_drvr_अ_लोonfig(hw,
					       HFA384x_RID_CNFWPADATA,
					       (u8 *)&wpa,
					       माप(wpa));
			pstr->len = le16_to_cpu(wpa.datalen);
			स_नकल(pstr->data, wpa.data, pstr->len);
		पूर्ण अन्यथा अणु
			wpa.datalen = cpu_to_le16(pstr->len);
			स_नकल(wpa.data, pstr->data, pstr->len);

			hfa384x_drvr_setconfig(hw,
					       HFA384x_RID_CNFWPADATA,
					       (u8 *)&wpa,
					       माप(wpa));
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		netdev_err(wlandev->netdev, "Unhandled DID 0x%08x\n", mib->did);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * prism2mgmt_pstr2bytestr
 *
 * Convert the pstr data in the WLAN message काष्ठाure पूर्णांकo an hfa384x
 * byte string क्रमmat.
 *
 * Arguments:
 *	bytestr		hfa384x byte string data type
 *	pstr		wlan message data
 *
 * Returns:
 *	Nothing
 *
 */

व्योम prism2mgmt_pstr2bytestr(काष्ठा hfa384x_bytestr *bytestr,
			     काष्ठा p80211pstrd *pstr)
अणु
	bytestr->len = cpu_to_le16((u16)(pstr->len));
	स_नकल(bytestr->data, pstr->data, pstr->len);
पूर्ण

/*
 * prism2mgmt_bytestr2pstr
 *
 * Convert the data in an hfa384x byte string क्रमmat पूर्णांकo a
 * pstr in the WLAN message.
 *
 * Arguments:
 *	bytestr		hfa384x byte string data type
 *	msg		wlan message
 *
 * Returns:
 *	Nothing
 *
 */

व्योम prism2mgmt_bytestr2pstr(काष्ठा hfa384x_bytestr *bytestr,
			     काष्ठा p80211pstrd *pstr)
अणु
	pstr->len = (u8)(le16_to_cpu(bytestr->len));
	स_नकल(pstr->data, bytestr->data, pstr->len);
पूर्ण

/*
 * prism2mgmt_bytearea2pstr
 *
 * Convert the data in an hfa384x byte area क्रमmat पूर्णांकo a pstr
 * in the WLAN message.
 *
 * Arguments:
 *	bytearea	hfa384x byte area data type
 *	msg		wlan message
 *
 * Returns:
 *	Nothing
 *
 */

व्योम prism2mgmt_bytearea2pstr(u8 *bytearea, काष्ठा p80211pstrd *pstr, पूर्णांक len)
अणु
	pstr->len = (u8)len;
	स_नकल(pstr->data, bytearea, len);
पूर्ण
